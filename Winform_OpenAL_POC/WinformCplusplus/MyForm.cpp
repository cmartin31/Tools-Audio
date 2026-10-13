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
		button1->Text = L"⏸";
	}
}

System::Void WinformCplusplus::MyForm::LoadPlaylist(String^ filePath)
{
	String^ json = System::IO::File::ReadAllText(filePath, System::Text::Encoding::UTF8);
	auto serializer = gcnew System::Web::Script::Serialization::JavaScriptSerializer();

	currentPlaylist = serializer->Deserialize<Playlist^>(json);  
	currentPlaylistPath = filePath;                              

	RefreshComboBox();        
	if (currentPlaylist->Tracks->Count > 0)
		comboBox1->SelectedIndex = 0;   
	else
		SelectTrack(-1);                
}

System::Void WinformCplusplus::MyForm::openToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	OpenFileDialog^ ofd = gcnew OpenFileDialog();
	ofd->InitialDirectory = System::IO::Path::Combine(Application::StartupPath, "Data Json Playlist");
	ofd->Filter = "Playlist (*.json)|*.json";

	if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		LoadPlaylist(ofd->FileName);
		comboBox1_SelectedIndexChanged(sender,e);
	}
}

System::Void WinformCplusplus::MyForm::comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (isRefreshingCombo) return;

	int index = comboBox1->SelectedIndex;
	if (index < 0) return;

	if (index == currentPlaylist->Tracks->Count)
	{
		AddTrack();
		comboBox1->SelectedIndex = -1;
		return;
	}
	else
	{
		SelectTrack(index);
	}

	String^ fullPath = System::IO::Path::Combine(Application::StartupPath, currentPlaylist->Tracks[index]);

	if (!System::IO::File::Exists(fullPath))
	{
		MessageBox::Show("Fichier introuvable :\n" + fullPath);
		return;
	}

	msclr::interop::marshal_context context;
	const char* filePath = context.marshal_as<const char*>(fullPath);

	Stop();
	Play(filePath);
	button1->Text = L"▶";

	textBox1->Text = System::IO::Path::GetFileNameWithoutExtension(fullPath);

	int duree = (int)(GetDuration() * 1000);
	if (duree < trackBar1->Minimum) duree = trackBar1->Minimum;
	trackBar1->Maximum = duree;
	trackBar1->Value = trackBar1->Minimum;
}

System::Void WinformCplusplus::MyForm::RefreshComboBox()
{
	isRefreshingCombo = true;

	comboBox1->Items->Clear();
	for each(String ^ track in currentPlaylist->Tracks)
		comboBox1->Items->Add(System::IO::Path::GetFileNameWithoutExtension(track));

	comboBox1->Items->Add("+ Ajouter une musique");

	isRefreshingCombo = false;
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

	RefreshComboBox();
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
	}
}

System::Void WinformCplusplus::MyForm::button4_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (comboBox1->SelectedIndex > 0)
	{
		SelectTrack(comboBox1->SelectedIndex - 1);
		comboBox1->SelectedIndex--;
	}
}

System::Void WinformCplusplus::MyForm::NextMusic(System::Object^ sender, System::EventArgs^ e)
{
	int count = currentPlaylist->Tracks->Count;
	if (count == 0) return;

	int index = comboBox1->SelectedIndex;

	if (index >= count - 1) return;
	comboBox1->SelectedIndex++;
}
