#include "MyLoginForm.h"
#include "RegisterForm.h"
#include"FormDiscuss.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main()
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);











    while (true) {
        ChatAppofficel::MyLoginForm formLogin;
        formLogin.Size = System::Drawing::Size(1000, 800);
        formLogin.FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
        formLogin.MaximizeBox = false;
        formLogin.ShowDialog();

        if (formLogin.switchtoregister) {
            ChatAppofficel::RegisterForm formRegister;
            formRegister.Size = System::Drawing::Size(1000, 800);
            formRegister.FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            formRegister.MaximizeBox = false;
            formRegister.ShowDialog();

            if (formRegister.switchtologin) {
                continue;
            }
            else {
                break;
            }
        }
        else if (formLogin.switchtodiscuss) {
            ChatAppofficel::FormDiscuss formDiscuss(formLogin.usernameValue);
            formDiscuss.Size = System::Drawing::Size(1000, 800);
            formDiscuss.FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            formDiscuss.MaximizeBox = false;
            formDiscuss.ShowDialog();
        }
        else {
            break;
        }
    }

    return 0;
}

    





  



