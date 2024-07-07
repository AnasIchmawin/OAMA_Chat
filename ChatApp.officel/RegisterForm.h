namespace ChatAppofficel {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace MySql::Data::MySqlClient;
	public ref class RegisterForm : public System::Windows::Forms::Form
	{
	public:
		RegisterForm(void)
		{
			InitializeComponent();
		}
	protected:
		~RegisterForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
    private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Panel^ panel3;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Panel^ panel4;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox3;
	private: System::Windows::Forms::PictureBox^ pictureBox4;
	private: System::ComponentModel::Container ^components;
	
    void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(RegisterForm::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->panel3->SuspendLayout();
			this->panel4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(1052, 645);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(176, 69);
			this->button1->TabIndex = 8;
			this->button1->Text = L"REGISTER";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &RegisterForm::button1_Click);
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::Silver;
			this->panel1->Controls->Add(this->textBox1);
			this->panel1->Location = System::Drawing::Point(865, 263);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(507, 74);
			this->panel1->TabIndex = 13;
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::Color::Silver;
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(16, 18);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(371, 39);
			this->textBox1->TabIndex = 12;
			this->textBox1->Text = L"Email";
			this->textBox1->Click += gcnew System::EventHandler(this, &RegisterForm::textBox1_Click);
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &RegisterForm::textBox1_TextChanged);
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::Color::Silver;
			this->panel2->Controls->Add(this->textBox2);
			this->panel2->Location = System::Drawing::Point(865, 353);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(507, 72);
			this->panel2->TabIndex = 14;
			// 
			// textBox2
			// 
			this->textBox2->BackColor = System::Drawing::Color::Silver;
			this->textBox2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox2->Location = System::Drawing::Point(15, 19);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(464, 39);
			this->textBox2->TabIndex = 12;
			this->textBox2->Text = L"Username";
			this->textBox2->Click += gcnew System::EventHandler(this, &RegisterForm::textBox2_Click);
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &RegisterForm::textBox2_TextChanged);
			// 
			// panel3
			// 
			this->panel3->BackColor = System::Drawing::Color::Silver;
			this->panel3->Controls->Add(this->textBox3);
			this->panel3->Location = System::Drawing::Point(865, 444);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(507, 74);
			this->panel3->TabIndex = 15;
			// 
			// textBox3
			// 
			this->textBox3->BackColor = System::Drawing::Color::Silver;
			this->textBox3->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox3->Location = System::Drawing::Point(17, 19);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(462, 37);
			this->textBox3->TabIndex = 12;
			this->textBox3->Text = L"Password";
			this->textBox3->UseSystemPasswordChar = true;
			this->textBox3->Click += gcnew System::EventHandler(this, &RegisterForm::textBox3_Click);
			// 
			// panel4
			// 
			this->panel4->BackColor = System::Drawing::Color::Silver;
			this->panel4->Controls->Add(this->textBox4);
			this->panel4->Location = System::Drawing::Point(866, 537);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(506, 72);
			this->panel4->TabIndex = 16;
			// 
			// textBox4
			// 
			this->textBox4->BackColor = System::Drawing::Color::Silver;
			this->textBox4->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox4->Location = System::Drawing::Point(17, 19);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(380, 37);
			this->textBox4->TabIndex = 12;
			this->textBox4->Text = L"Password";
			this->textBox4->UseSystemPasswordChar = true;
			this->textBox4->Click += gcnew System::EventHandler(this, &RegisterForm::textBox4_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::Transparent;
			this->button2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button2.BackgroundImage")));
			this->button2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->ForeColor = System::Drawing::Color::Silver;
			this->button2->Location = System::Drawing::Point(29, 130);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 64);
			this->button2->TabIndex = 17;
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &RegisterForm::button2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(107, 140);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(169, 47);
			this->label1->TabIndex = 18;
			this->label1->Text = L"Go Back";
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(799, 263);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(67, 74);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 20;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(799, 353);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(67, 72);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 21;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox3
			// 
			this->pictureBox3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.Image")));
			this->pictureBox3->Location = System::Drawing::Point(798, 444);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(67, 74);
			this->pictureBox3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox3->TabIndex = 22;
			this->pictureBox3->TabStop = false;
			// 
			// pictureBox4
			// 
			this->pictureBox4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox4.Image")));
			this->pictureBox4->Location = System::Drawing::Point(799, 537);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(67, 72);
			this->pictureBox4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox4->TabIndex = 23;
			this->pictureBox4->TabStop = false;
			// 
			// RegisterForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::DarkSlateGray;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1384, 711);
			this->Controls->Add(this->pictureBox4);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->panel4);
			this->Controls->Add(this->panel3);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->button1);
			this->DoubleBuffered = true;
			this->ForeColor = System::Drawing::Color::Teal;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"RegisterForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"RegisterForm";
			this->Load += gcnew System::EventHandler(this, &RegisterForm::RegisterForm_Load);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();
		}
	private: System::Void label4_Click(System::Object^ sender, System::EventArgs^ e) {}
    private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {}
    private: System::Void bunifuImageButton1_Click(System::Object^ sender, System::EventArgs^ e) {}
    private: System::Void RegisterForm_Load(System::Object^ sender, System::EventArgs^ e) {}
    private: System::Void textBox2_Click(System::Object^ sender, System::EventArgs^ e) {
	if (textBox2->Text == "Username") {
		textBox2->Text = "";
	}
}
    private: System::Void textBox1_Click(System::Object^ sender, System::EventArgs^ e) {
	        if (textBox1->Text == "Email") {
		         textBox1->Text = "";
	}
}
    private: System::Void textBox3_Click(System::Object^ sender, System::EventArgs^ e) {
	         if (textBox3->Text == "Password") {
		         textBox3->Text = "";
	}
}
    private: System::Void textBox4_Click(System::Object^ sender, System::EventArgs^ e) {
	      if (textBox4->Text == "Password") {
		         textBox4->Text = "";
	}
}
private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {}
private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ Email = this->textBox1->Text;
	String^ Username = this->textBox2->Text;
	String^ password = this->textBox3->Text;
	String^ confPass = this->textBox4->Text;
	if (Email->Length == 0 || Username->Length == 0 || confPass != password || Email=="Email") {
		MessageBox::Show("Please Enter email and password", "Email or Password is incorrect", MessageBoxButtons::OK);
		return;
	}
	try
	{
		String^ connectionString = "server=sql8.freesqldatabase.com;Uid=sql8670602;Password=VbbEPLEMNch6xufa;Database=sql8670602";
		MySqlConnection^ con = gcnew MySqlConnection(connectionString);
		String^ Email = this->textBox1->Text;
		String^ Username = this->textBox2->Text;
		MySqlCommand^ cmd = gcnew MySqlCommand("insert into register values('" + Email + "','" + Username + "','" +password+"')", con);
		MySqlDataReader^ dr;
		con->Open();
		try
		{
			dr = cmd->ExecuteReader();
			MessageBox::Show("Sign Up success\n Go to back for login !");
		}
		catch (Exception^ ex)
		{
			MessageBox::Show("Error: " + ex->Message);
		}

	}
	catch (Exception^ ex)
	{
		MessageBox::Show("Error: " + ex->Message);
	}
}
	 public: 
		 bool  switchtologin = false;
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	this->switchtologin = true;
	this->Close();
}
};
}