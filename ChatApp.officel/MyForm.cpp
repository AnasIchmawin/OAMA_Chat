#include "MyForm.h"
using namespace System;
using namespace System::Windows::Forms;
[STAThread]
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Project2:: MyForm form;
	form.Size = System::Drawing::Size(1000, 800);
	form.FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
	form.MaximizeBox = false;
	Application::Run(% form);
}