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

System::Void WinformCplusplus::MyForm::openToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	/*OpenFileDialog^ ofd = gcnew OpenFileDialog();

	ofd->Filter = "ogg/wav files (*.ogg);(*.wav)|*.ogg;*.wav|All files (*.*)|*.*";

	if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		msclr::interop::marshal_context context;
		const char* filePath = context.marshal_as<const char*>(ofd->FileName);
		Stop();
		button1->Text = L"▶";
		Play(filePath);
		String^ musicName = System::IO::Path::GetFileNameWithoutExtension(ofd->FileName);
		textBox1->Text = musicName;
		trackBar1->Maximum = (int)(GetDuration() * 1000);
		trackBar1->Value = 0;
	}*/

	OpenFileDialog^ ofd = gcnew OpenFileDialog();

	ofd->Filter = "jason files (*.json)|*.json;|All files (*.*)|*.*";

	if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		String^ json = System::IO::File::ReadAllText(ofd->FileName, System::Text::Encoding::UTF8);
		auto serializer = gcnew System::Web::Script::Serialization::JavaScriptSerializer();
		auto obj = safe_cast<System::Collections::Generic::Dictionary<String^, Object^>^>(
			serializer->DeserializeObject(json));

		// "Tracks" est un tableau : on le lit comme une simple énumération
		auto tracks = safe_cast<System::Collections::IEnumerable^>(obj["Tracks"]);

		comboBox1->Items->Clear();
		for each(Object ^ entry in tracks)
		{
			comboBox1->Items->Add(entry->ToString());
		}

		if (comboBox1->Items->Count > 0)
			comboBox1->SelectedIndex = 0;

		RefreshComboBox();
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
	}

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
