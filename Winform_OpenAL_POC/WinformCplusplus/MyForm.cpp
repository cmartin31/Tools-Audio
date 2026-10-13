#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	WinformCplusplus::MyForm form;
	Application::Run(%form);
}

System::Void WinformCplusplus::MyForm::openToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	OpenFileDialog^ ofd = gcnew OpenFileDialog();

	if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		msclr::interop::marshal_context context;
		const char* filePath = context.marshal_as<const char*>(ofd->FileName);
		Play(filePath);
		trackBar1->Maximum = (int)(GetDuration() * 1000); 
		trackBar1->Value = 0;
	}
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
