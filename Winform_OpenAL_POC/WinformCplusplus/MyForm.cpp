#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	WinformCplusplus::MyForm form;
	Application::Run(% form);

}

System::Void WinformCplusplus::MyForm::SelectTrack(int index)
{
	if (index < 0 || index >= currentPlaylist->Tracks->Count)
	{
		textBox1->Text = "No Current Music";
		currentIndex = -1;
		return;
	}

	currentIndex = index;
	textBox1->Text = System::IO::Path::GetFileNameWithoutExtension(currentPlaylist->Tracks[index]);
}
System::Void WinformCplusplus::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (IsPlaying())
	{
		Pause();
		button1->Text = L"▶";
	}
	else
	{
		Resume();
		button1->Text =L"";
	}
}

System::Void WinformCplusplus::MyForm::LoadPlaylist(String^ filePath)
{
	String^ json = System::IO::File::ReadAllText(filePath, System::Text::Encoding::UTF8);
	auto serializer = gcnew System::Web::Script::Serialization::JavaScriptSerializer();

	currentPlaylist = serializer->Deserialize<Playlist^>(json);  
	currentPlaylistPath = filePath;

	if (String::IsNullOrEmpty(currentPlaylist->Name))
		currentPlaylist->Name = System::IO::Path::GetFileNameWithoutExtension(filePath);

	currentIndex = -1;
	RefreshTrackList();
	if (currentPlaylist->Tracks->Count > 0)
		LoadTrack(0);
	else
		SelectTrack(-1);
}

System::Void WinformCplusplus::MyForm::openToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	OpenFileDialog^ ofd = gcnew OpenFileDialog();
	ofd->InitialDirectory = System::IO::Path::Combine(Application::StartupPath, "Data Json");
	ofd->Filter = "Playlist (*.json)|*.json";

	if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		LoadPlaylist(ofd->FileName);
	}
}

System::Void WinformCplusplus::MyForm::AddTrack()
{
	String^ musicDir = System::IO::Path::Combine(Application::StartupPath, "Data Musique");

	OpenFileDialog^ ofd = gcnew OpenFileDialog();
	ofd->InitialDirectory = musicDir;
	ofd->Filter = "Audio (*.wav;*.ogg)|*.wav;*.ogg";
	ofd->Multiselect = true;

	if (ofd->ShowDialog() != System::Windows::Forms::DialogResult::OK)
		return;

	String^ root = Application::StartupPath + "\\";

	for each(String ^ file in ofd->FileNames)
	{
		String^ path = file;
		if (path->StartsWith(root, StringComparison::OrdinalIgnoreCase))
			path = path->Substring(root->Length);

		currentPlaylist->Tracks->Add(path);
	}

	RefreshTrackList();
}

#define DZ_PURPLE	System::Drawing::Color::FromArgb(162, 56, 255)
#define DZ_HOVER	System::Drawing::Color::FromArgb(32, 32, 36)
#define DZ_SELECT	System::Drawing::Color::FromArgb(45, 45, 52)
#define DZ_GREY		System::Drawing::Color::FromArgb(160, 160, 165)
#define DZ_LINE		System::Drawing::Color::FromArgb(40, 40, 40)

static String^ FormatDuration(double seconds)
{
	if (seconds <= 0)
		return "--:--";

	int total = (int)Math::Round(seconds);
	return String::Format("{0}:{1:00}", total / 60, total % 60);
}

static double ReadTrackDuration(String^ path)
{
	try
	{
		System::IO::FileStream^ fs = System::IO::File::OpenRead(path);
		try
		{
			array<Byte>^ head = gcnew array<Byte>(4096);
			int n = fs->Read(head, 0, head->Length);
			String^ magic = System::Text::Encoding::ASCII->GetString(head, 0, 4);

			if (magic == "RIFF")
			{
				System::IO::BinaryReader^ br = gcnew System::IO::BinaryReader(fs);
				fs->Position = 12;
				int byteRate = 0;
				while (fs->Position + 8 <= fs->Length)
				{
					String^ id = System::Text::Encoding::ASCII->GetString(br->ReadBytes(4));
					unsigned int size = br->ReadUInt32();
					if (id == "fmt ")
					{
						br->ReadBytes(8);
						byteRate = br->ReadInt32();
						fs->Position += size - 12;
					}
					else if (id == "data")
						return byteRate > 0 ? (double)size / byteRate : 0;
					else
						fs->Position += size + (size & 1);
				}
			}
			else if (magic == "OggS")
			{
				int rate = 0;
				for (int i = 0; i + 16 < n; i++)
				{
					if (head[i] == 1 && head[i + 1] == 'v' && head[i + 2] == 'o' && head[i + 3] == 'r'
						&& head[i + 4] == 'b' && head[i + 5] == 'i' && head[i + 6] == 's')
					{
						rate = BitConverter::ToInt32(head, i + 12);
						break;
					}
				}
				if (rate <= 0)
					return 0;

				int tailLen = (int)Math::Min((Int64)65536, fs->Length);
				array<Byte>^ tail = gcnew array<Byte>(tailLen);
				fs->Position = fs->Length - tailLen;
				fs->Read(tail, 0, tailLen);
				for (int i = tailLen - 14; i >= 0; i--)
				{
					if (tail[i] == 'O' && tail[i + 1] == 'g' && tail[i + 2] == 'g' && tail[i + 3] == 'S')
						return (double)BitConverter::ToInt64(tail, i + 6) / rate;
				}
			}
		}
		finally
		{
			fs->Close();
		}
	}
	catch (Exception^)
	{
	}
	return 0;
}

System::Void WinformCplusplus::MyForm::SetupTrackList()
{

	listViewTracks->GetType()->GetProperty("DoubleBuffered",
		Reflection::BindingFlags::Instance | Reflection::BindingFlags::NonPublic)->SetValue(listViewTracks, true, nullptr);
	listViewTracks_Resize(nullptr, nullptr);
}

System::Void WinformCplusplus::MyForm::RefreshTrackList()
{
	listViewTracks->BeginUpdate();
	listViewTracks->Items->Clear();
	for (int i = 0; i < currentPlaylist->Tracks->Count; i++)
	{
		String^ track = currentPlaylist->Tracks[i];
		String^ fullPath = System::IO::Path::Combine(Application::StartupPath, track);

		ListViewItem^ item = gcnew ListViewItem((i + 1).ToString());
		item->SubItems->Add(System::IO::Path::GetFileNameWithoutExtension(track));
		item->SubItems->Add(FormatDuration(ReadTrackDuration(fullPath)));
		listViewTracks->Items->Add(item);
	}
	listViewTracks->EndUpdate();
	listViewTracks_Resize(nullptr, nullptr);

	String^ name = currentPlaylist->Name;
	if (String::IsNullOrEmpty(name))
		name = "Nouvelle playlist";

	int count = currentPlaylist->Tracks->Count;
	String^ text = name + L"  ·  " + count.ToString() + " titre";
	if (count > 1)
		text += "s";
	labelPlaylist->Text = text;
}

bool WinformCplusplus::MyForm::LoadTrack(int index)
{
	if (index < 0 || index >= currentPlaylist->Tracks->Count)
		return false;

	String^ fullPath = System::IO::Path::Combine(Application::StartupPath, currentPlaylist->Tracks[index]);
	if (!System::IO::File::Exists(fullPath))
	{
		MessageBox::Show("Fichier introuvable :\n" + fullPath);
		return false;
	}

	msclr::interop::marshal_context context;
	const char* filePath = context.marshal_as<const char*>(fullPath);

	Stop();
	Play(filePath);
	button1->Text = L"▶";
	SelectTrack(index);

	int duree = (int)(GetDuration() * 1000);
	if (duree < trackBar1->Minimum) duree = trackBar1->Minimum;
	trackBar1->Maximum = duree;
	trackBar1->Value = trackBar1->Minimum;

	listViewTracks->Items[index]->Selected = true;
	listViewTracks->EnsureVisible(index);
	listViewTracks->Invalidate();
	return true;
}

System::Void WinformCplusplus::MyForm::PlayTrack(int index)
{
	if (!LoadTrack(index))
		return;

	Resume();
	button1->Text =L"";
}

System::Void WinformCplusplus::MyForm::listViewTracks_DoubleClick(System::Object^ sender, System::EventArgs^ e)
{
	if (listViewTracks->SelectedIndices->Count > 0)
		PlayTrack(listViewTracks->SelectedIndices[0]);
}

System::Void WinformCplusplus::MyForm::listViewTracks_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
	if (e->KeyCode == Keys::Enter && listViewTracks->SelectedIndices->Count > 0)
	{
		PlayTrack(listViewTracks->SelectedIndices[0]);
		e->Handled = true;
	}
}

System::Void WinformCplusplus::MyForm::listViewTracks_DrawColumnHeader(System::Object^ sender, System::Windows::Forms::DrawListViewColumnHeaderEventArgs^ e)
{
	e->Graphics->FillRectangle(Brushes::Black, e->Bounds);

	TextFormatFlags align = TextFormatFlags::Left;
	if (e->Header->TextAlign == HorizontalAlignment::Center)
		align = TextFormatFlags::HorizontalCenter;
	else if (e->Header->TextAlign == HorizontalAlignment::Right)
		align = TextFormatFlags::Right;

	Drawing::Font headerFont("Segoe UI", 8, Drawing::FontStyle::Bold);
	TextRenderer::DrawText(e->Graphics, e->Header->Text, %headerFont, Drawing::Rectangle::Inflate(e->Bounds, -8, 0), DZ_GREY,
		align | TextFormatFlags::VerticalCenter);

	Pen line(DZ_LINE);
	e->Graphics->DrawLine(%line, e->Bounds.Left, e->Bounds.Bottom - 1, e->Bounds.Right, e->Bounds.Bottom - 1);
}

System::Void WinformCplusplus::MyForm::listViewTracks_DrawSubItem(System::Object^ sender, System::Windows::Forms::DrawListViewSubItemEventArgs^ e)
{
	int index = e->ItemIndex;
	bool isCurrent = (index == currentIndex);

	Drawing::Rectangle bounds = e->Bounds;
	if (e->ColumnIndex == 0)
		bounds.Width = listViewTracks->Columns[0]->Width;

	Drawing::Color backColor = Drawing::Color::Black;
	if (e->Item->Selected)
		backColor = DZ_SELECT;
	else if (index == hoverIndex)
		backColor = DZ_HOVER;

	SolidBrush back(backColor);
	e->Graphics->FillRectangle(%back, bounds);

	String^ text = e->SubItem->Text;
	Drawing::Color fore = Drawing::Color::White;
	TextFormatFlags align = TextFormatFlags::Left;

	switch (e->ColumnIndex)
	{
	case 0:
		align = TextFormatFlags::HorizontalCenter;
		fore = DZ_GREY;
		if (isCurrent)
		{
			text = L"♫";
			fore = DZ_PURPLE;
		}
		else if (index == hoverIndex)
		{
			text = L"▶";
			fore = Drawing::Color::White;
		}
		break;
	case 1:
		if (isCurrent)
			fore = DZ_PURPLE;
		break;
	case 2:
		align = TextFormatFlags::Right;
		fore = DZ_GREY;
		break;
	}

	TextRenderer::DrawText(e->Graphics, text, listViewTracks->Font, Drawing::Rectangle::Inflate(bounds, -8, 0), fore,
		align | TextFormatFlags::VerticalCenter | TextFormatFlags::EndEllipsis | TextFormatFlags::NoPrefix);
}

System::Void WinformCplusplus::MyForm::listViewTracks_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	ListViewItem^ item = listViewTracks->GetItemAt(e->X, e->Y);
	int index = item != nullptr ? item->Index : -1;
	if (index == hoverIndex)
		return;

	if (hoverIndex >= 0 && hoverIndex < listViewTracks->Items->Count)
		listViewTracks->Invalidate(listViewTracks->Items[hoverIndex]->Bounds);

	hoverIndex = index;
	if (item != nullptr)
		listViewTracks->Invalidate(item->Bounds);
}

System::Void WinformCplusplus::MyForm::listViewTracks_MouseLeave(System::Object^ sender, System::EventArgs^ e)
{
	hoverIndex = -1;
	listViewTracks->Invalidate();
}

System::Void WinformCplusplus::MyForm::listViewTracks_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	listViewTracks->Invalidate();
}

System::Void WinformCplusplus::MyForm::listViewTracks_Resize(System::Object^ sender, System::EventArgs^ e)
{
	if (listViewTracks->Columns->Count < 3)
		return;

	int width = listViewTracks->ClientSize.Width - listViewTracks->Columns[0]->Width - listViewTracks->Columns[2]->Width;
	listViewTracks->Columns[1]->Width = Math::Max(width, 100);
}

System::Void WinformCplusplus::MyForm::buttonAddTrack_Click(System::Object^ sender, System::EventArgs^ e)
{
	AddTrack();
}

System::Void WinformCplusplus::MyForm::button2_Click_1(System::Object^ sender, System::EventArgs^ e)
{
	Stop();
	button1->Text = L"▶";
}

System::Void WinformCplusplus::MyForm::timer1_Tick(System::Object^ sender, System::EventArgs^ e)
{
	int pos = (int)(GetPosition() * 1000);
	if (pos <= trackBar1->Maximum && !isDraggingTimer)
		trackBar1->Value = pos;
}

System::Void WinformCplusplus::MyForm::trackBar1_Scroll(System::Object^ sender, System::EventArgs^ e)
{
	SetPosition(trackBar1->Value / 1000.0f);
}

System::Void WinformCplusplus::MyForm::trackBar1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	isDraggingTimer = true;
	if (e->Button == System::Windows::Forms::MouseButtons::Left)
		SeekToMouse(e->X);
}

System::Void WinformCplusplus::MyForm::trackBar1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	// Bouton gauche enfoncé : le curseur suit la souris
	if (e->Button == System::Windows::Forms::MouseButtons::Left)
		SeekToMouse(e->X);
}

// Place le curseur de la barre (et la lecture) à l'endroit cliqué
System::Void WinformCplusplus::MyForm::SeekToMouse(int x)
{
	// Le curseur ne va pas jusqu'aux bords du TrackBar : on retire environ sa demi-largeur de chaque côté
	const int margin = 13;
	int usable = trackBar1->Width - 2 * margin;
	if (usable <= 0)
		return;

	double ratio = (double)(x - margin) / usable;
	ratio = Math::Max(0.0, Math::Min(1.0, ratio));

	int value = trackBar1->Minimum + (int)Math::Round(ratio * (trackBar1->Maximum - trackBar1->Minimum));
	if (value == trackBar1->Value)
		return;

	trackBar1->Value = value;
	SetPosition(value / 1000.0f);
}

System::Void WinformCplusplus::MyForm::trackBar1_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	isDraggingTimer = false;

}

System::Void WinformCplusplus::MyForm::SavePlayList()
{
	auto serializer = gcnew System::Web::Script::Serialization::JavaScriptSerializer();
	String^ json = serializer->Serialize(currentPlaylist);
	System::IO::File::WriteAllText(currentPlaylistPath, json);
}


System::Void WinformCplusplus::MyForm::trackBar2_Scroll(System::Object^ sender, System::EventArgs^ e)
{
	float v = trackBar2->Value / 100.0f;
	SetVolume(v * v);
}

System::Void WinformCplusplus::MyForm::savePlaylistToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	String^ jsonDir = System::IO::Path::Combine(Application::StartupPath, "Data Json");
	System::IO::Directory::CreateDirectory(jsonDir);

	SaveFileDialog^ sfd = gcnew SaveFileDialog();
	sfd->InitialDirectory = jsonDir;
	sfd->Filter = "Playlist (*.json)|*.json";
	sfd->DefaultExt = "json";

	if (sfd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		currentPlaylistPath = sfd->FileName;
		currentPlaylist->Name = System::IO::Path::GetFileNameWithoutExtension(sfd->FileName);
		SavePlayList();
		RefreshTrackList();
	}
}

System::Void WinformCplusplus::MyForm::lastTrack(System::Object^ sender, System::EventArgs^ e)
{
	if (currentIndex > 0)
		PlayTrack(currentIndex - 1);
}

System::Void WinformCplusplus::MyForm::NextMusic(System::Object^ sender, System::EventArgs^ e)
{
	if (currentIndex < currentPlaylist->Tracks->Count - 1)
		PlayTrack(currentIndex + 1);
}
