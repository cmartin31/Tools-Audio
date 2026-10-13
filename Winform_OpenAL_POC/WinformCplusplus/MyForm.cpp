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
	}
}
