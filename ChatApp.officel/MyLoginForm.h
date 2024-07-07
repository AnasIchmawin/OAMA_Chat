#include"FormDiscuss.h"
#include"User.h"
namespace ChatAppofficel {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace MySql::Data::MySqlClient;
	public ref class MyLoginForm : public System::Windows::Forms::Form
	{
	public:
		MyLoginForm(void)
		{
			InitializeComponent();
		}

	protected:
		~MyLoginForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: Bunifu::Framework::UI::BunifuTextbox^ bunifuTextbox2;
	private: Bunifu::Framework::UI::BunifuTextbox^ bunifuTextbox1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Panel^ panel3;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::ComponentModel::Container ^components;

	void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyLoginForm::typeid));
			this->bunifuTextbox2 = (gcnew Bunifu::Framework::UI::BunifuTextbox());
			this->bunifuTextbox1 = (gcnew Bunifu::Framework::UI::BunifuTextbox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->panel2->SuspendLayout();
			this->panel3->SuspendLayout();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// bunifuTextbox2
			// 
			this->bunifuTextbox2->BackColor = System::Drawing::Color::Silver;
			this->bunifuTextbox2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"bunifuTextbox2.BackgroundImage")));
			this->bunifuTextbox2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->bunifuTextbox2->ForeColor = System::Drawing::Color::Black;
			this->bunifuTextbox2->Icon = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"bunifuTextbox2.Icon")));
			this->bunifuTextbox2->Location = System::Drawing::Point(2, 182);
			this->bunifuTextbox2->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->bunifuTextbox2->Name = L"bunifuTextbox2";
			this->bunifuTextbox2->Size = System::Drawing::Size(492, 74);
			this->bunifuTextbox2->TabIndex = 4;
			this->bunifuTextbox2->text = L"Password";
			this->bunifuTextbox2->OnTextChange += gcnew System::EventHandler(this, &MyLoginForm::bunifuTextbox2_OnTextChange);
			// 
			// bunifuTextbox1
			// 
			this->bunifuTextbox1->BackColor = System::Drawing::Color::Silver;
			this->bunifuTextbox1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"bunifuTextbox1.BackgroundImage")));
			this->bunifuTextbox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->bunifuTextbox1->ForeColor = System::Drawing::Color::Black;
			this->bunifuTextbox1->Icon = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"bunifuTextbox1.Icon")));
			this->bunifuTextbox1->Location = System::Drawing::Point(2, 64);
			this->bunifuTextbox1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->bunifuTextbox1->Name = L"bunifuTextbox1";
			this->bunifuTextbox1->Size = System::Drawing::Size(492, 74);
			this->bunifuTextbox1->TabIndex = 3;
			this->bunifuTextbox1->text = L"Email";
			this->bunifuTextbox1->OnTextChange += gcnew System::EventHandler(this, &MyLoginForm::bunifuTextbox1_OnTextChange);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->Location = System::Drawing::Point(217, 303);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(176, 74);
			this->button2->TabIndex = 9;
			this->button2->Text = L"LOG IN";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyLoginForm::button2_Click);
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::Color::White;
			this->panel2->Controls->Add(this->panel3);
			this->panel2->Controls->Add(this->panel1);
			this->panel2->Controls->Add(this->button2);
			this->panel2->Controls->Add(this->bunifuTextbox1);
			this->panel2->Controls->Add(this->bunifuTextbox2);
			this->panel2->Location = System::Drawing::Point(180, 462);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(602, 528);
			this->panel2->TabIndex = 10;
			this->panel2->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyLoginForm::panel2_Paint);
			// 
			// panel3
			// 
			this->panel3->BackColor = System::Drawing::Color::Silver;
			this->panel3->Controls->Add(this->textBox2);
			this->panel3->Location = System::Drawing::Point(61, 182);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(507, 74);
			this->panel3->TabIndex = 13;
			// 
			// textBox2
			// 
			this->textBox2->BackColor = System::Drawing::Color::Silver;
			this->textBox2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox2->Location = System::Drawing::Point(12, 22);
			this->textBox2->Name = L"textBox2";
			this->textBox2->PasswordChar = '*';
			this->textBox2->Size = System::Drawing::Size(489, 37);
			this->textBox2->TabIndex = 12;
			this->textBox2->Text = L"Password";
			this->textBox2->UseSystemPasswordChar = true;
			this->textBox2->Click += gcnew System::EventHandler(this, &MyLoginForm::textBox2_Click);
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::Silver;
			this->panel1->Controls->Add(this->textBox1);
			this->panel1->Location = System::Drawing::Point(61, 64);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(507, 74);
			this->panel1->TabIndex = 12;
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::Color::Silver;
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(12, 19);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(492, 39);
			this->textBox1->TabIndex = 12;
			this->textBox1->Text = L"Email";
			this->textBox1->Click += gcnew System::EventHandler(this, &MyLoginForm::textBox1_Click);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(1036, 566);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(188, 76);
			this->button1->TabIndex = 11;
			this->button1->Text = L"SIGN UP";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyLoginForm::button1_Click_1);
			// 
			// MyLoginForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1384, 794);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->panel2);
			this->DoubleBuffered = true;
			this->Name = L"MyLoginForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MyLoginForm";
			this->Load += gcnew System::EventHandler(this, &MyLoginForm::MyLoginForm_Load);
			this->panel2->ResumeLayout(false);
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);}

	private: System::Void MyLoginForm_Load(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {}
    private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {}
    private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {}
    private: System::Void panel2_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {}
	public:User^ user = nullptr;
    public:
			 bool switchtodiscuss = false;
			 String^ usernameValue = "";

private:System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ Email = this->textBox1->Text;
		String^ Password = this->textBox2->Text;
		if (Email->Length == 0 || Password->Length == 0) {
			MessageBox::Show("Please Enter email and password", "Email or Password is incorrect", MessageBoxButtons::OK);
			return;
		}

		String^ connectionString = "server=sql8.freesqldatabase.com;Uid=sql8670602;Password=VbbEPLEMNch6xufa;Database=sql8670602";
		MySqlConnection^ con = gcnew MySqlConnection(connectionString);

		String^ query = "SELECT Username FROM register WHERE Email = @Email AND Password = @Password";
		MySqlCommand^ command = gcnew MySqlCommand(query, con);
		command->Parameters->AddWithValue("@Email", Email);
		command->Parameters->AddWithValue("@Password", Password);
		con->Open();

		try {
			Object^ Username = command->ExecuteScalar();

			if (Username != nullptr) {
				// Utiliser le nom d'utilisateur récupéré
				this->usernameValue = Username->ToString();
				this->switchtodiscuss = true;
				this->usernameValue = Username->ToString();
			this->Close();
		}
		else {
			MessageBox::Show("Username and password are incorrect!\nTry again...");
		}
	}
	catch (Exception^ ex) {
		MessageBox::Show("Email or password is incorrect!", "Warning", MessageBoxButtons::OK);
	}
	finally {
		con->Close();
	}
}

    private: System::Void bunifuTextbox5_OnTextChange(System::Object^ sender, System::EventArgs^ e) {}
    private: System::Void bunifuImageButton1_Click(System::Object^ sender, System::EventArgs^ e) {}
    private: System::Void bunifuImageButton2_Click(System::Object^ sender, System::EventArgs^ e) {}	
    private: System::Void bunifuTextbox1_OnTextChange(System::Object^ sender, System::EventArgs^ e) {}
    private: System::Void bunifuTextbox2_OnTextChange(System::Object^ sender, System::EventArgs^ e) {}
    private: System::Void textBox1_Click(System::Object^ sender, System::EventArgs^ e) {
	if (textBox1->Text == "Email") {
		textBox1->Text = "";
	}
}
private: System::Void textBox2_Click(System::Object^ sender, System::EventArgs^ e) {
	if (textBox2->Text == "Password") {
		textBox2->Text = "";
	}
}
	public: bool switchtoregister = false;

private: System::Void button1_Click_1(System::Object^ sender, System::EventArgs^ e) {
	this->switchtoregister = true;
	this->Close();
}
};
}