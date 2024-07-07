#pragma once
#include<string.h>
#include <winsock2.h>
#include <msclr\marshal_cppstd.h>
#include <thread>

#pragma comment(lib, "Ws2_32.lib")

namespace ChatAppofficel {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Net;
	using namespace System::Net::Sockets;
	using namespace MySql::Data::MySqlClient;

	public ref class FormDiscuss : public System::Windows::Forms::Form
	{
		delegate void ReceiveMessagesDelegate();
	public:
		String^ username;
	public:
		FormDiscuss(String^ user)
		{
			std::string clientName = msclr::interop::marshal_as<std::string>(user);
			this->username = user;
			InitializeComponent();
			receiveMessagesDelegate = gcnew ReceiveMessagesDelegate(this, &FormDiscuss::ReceiveMessages);
			clientSocket = InitializeSocket(clientName); // Assign the value to the member variable

		}
		void UpdateTextBox3(String^ newText)
		{
			// Ensure that this code runs on the UI thread
			if (textBox3->InvokeRequired)
			{
				// Use a delegate to update the UI on the UI thread
				textBox3->Invoke(gcnew Action<String^>(this, &FormDiscuss::UpdateTextBox3), newText);
			}
			else
			{
				// Update the text of textBox3
				textBox3->Text = textBox3->Text + "\r\n" + newText + "\r\n";
			}
		}
	private:
		ReceiveMessagesDelegate^ receiveMessagesDelegate;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox3;
	private: System::Windows::Forms::PictureBox^ pictureBox4;
	private: System::Windows::Forms::PictureBox^ pictureBox5;
	private: System::Windows::Forms::PictureBox^ pictureBox7;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::PictureBox^ pictureBox_search;
	private: System::Windows::Forms::Button^ pers_search;
             SOCKET clientSocket;
	protected:
		~FormDiscuss()
		{
			if (clientSocket != INVALID_SOCKET) {
				closesocket(clientSocket);
			}
			WSACleanup();
			if (components)
			{
				delete components;
			}
		}

		void SendMessageToServer(SOCKET clientSocket, const std::string& message) {
			if (send(clientSocket, message.c_str(), message.size(), 0) == SOCKET_ERROR) {
				MessageBox::Show("error sending");
			}
		}

		void ReceiveMessages() {
			char buffer[1024]; // Adjust the buffer size as needed

			while (true) {
				int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
				if (bytesReceived > 0) {
					buffer[bytesReceived] = '\0'; // Null-terminate the received data
					String^ receivedMessage = gcnew String(buffer);
					// Split the received message into name and message
					array<String^>^ parts = receivedMessage->Split(':');
					// Check if the message has the expected format
					String^ name = parts[0];
					String^ recMessage = parts[1];

					array<String^>^ parts1 = recMessage->Split('/');
					String^ toname = parts1[0];
					String^ message = parts1[1];
					String^ otheruser = label6->Text;
					if (name == otheruser && toname == username) {
						UpdateTextBox3(message);
					}
				}
			}
		}
		SOCKET InitializeSocket(std::string clientName) {
			// Initialize Winsock
			WSADATA wsaData;
			if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
				return INVALID_SOCKET; // Use a special value to indicate failure
			}

			// Create socket
			SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
			if (clientSocket == INVALID_SOCKET) {
				WSACleanup();
				return INVALID_SOCKET;
			}

			// Connect to the server
			sockaddr_in serverAddr;
			serverAddr.sin_family = AF_INET;
			serverAddr.sin_addr.s_addr = inet_addr("10.10.44.123");
			serverAddr.sin_port = htons(12345);

			if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
				closesocket(clientSocket);
				WSACleanup();
				return INVALID_SOCKET;
			}
			// Send client's name to the server
			SendMessageToServer(clientSocket, clientName);

			System::Threading::Thread^ receiveThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(receiveMessagesDelegate, &ReceiveMessagesDelegate::Invoke));
			receiveThread->Start();
			return clientSocket;
		}


	private: System::Windows::Forms::Button^ button_othmane;
	private: System::Windows::Forms::Button^ button_amine;
	private: System::Windows::Forms::Button^ button_mourad;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button_anas;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::PictureBox^ pictureBox10;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ textBox6;
	private:
		String^ getusername(String^ Email, String^ Password) {

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
					String^ userI = Username->ToString();
					return userI;
				}
			}
			catch (Exception^ ex) {
				MessageBox::Show("Email or password is incorrect!", "Warning", MessageBoxButtons::OK);
			}
			finally {
				con->Close();
			}

		}
	public:	System::ComponentModel::Container^ components;
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(FormDiscuss::typeid));
			this->button_othmane = (gcnew System::Windows::Forms::Button());
			this->button_amine = (gcnew System::Windows::Forms::Button());
			this->button_mourad = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button_anas = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox10 = (gcnew System::Windows::Forms::PictureBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox7 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->pictureBox_search = (gcnew System::Windows::Forms::PictureBox());
			this->pers_search = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox10))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->BeginInit();
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_search))->BeginInit();
			this->SuspendLayout();
			// 
			// button_othmane
			// 
			this->button_othmane->BackColor = System::Drawing::Color::WhiteSmoke;
			this->button_othmane->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 21.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button_othmane->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->button_othmane->Location = System::Drawing::Point(83, 511);
			this->button_othmane->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button_othmane->Name = L"button_othmane";
			this->button_othmane->Size = System::Drawing::Size(384, 108);
			this->button_othmane->TabIndex = 8;
			this->button_othmane->Text = getusername("othmane@gmail.com", "123");
			this->button_othmane->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button_othmane->UseVisualStyleBackColor = false;
			this->button_othmane->BackColorChanged += gcnew System::EventHandler(this, &FormDiscuss::label7_BackColorChanged);
			this->button_othmane->Click += gcnew System::EventHandler(this, &FormDiscuss::othmane_Click);
			// 
			// button_amine
			// 
			this->button_amine->BackColor = System::Drawing::Color::WhiteSmoke;
			this->button_amine->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 21.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button_amine->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->button_amine->Location = System::Drawing::Point(83, 646);
			this->button_amine->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button_amine->Name = L"button_amine";
			this->button_amine->Size = System::Drawing::Size(384, 108);
			this->button_amine->TabIndex = 9;
			this->button_amine->Text = getusername("Amine@gmail.com", "Amine123");;
			this->button_amine->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button_amine->UseVisualStyleBackColor = false;
			this->button_amine->BackColorChanged += gcnew System::EventHandler(this, &FormDiscuss::label7_BackColorChanged);
			this->button_amine->Click += gcnew System::EventHandler(this, &FormDiscuss::amine_Click);
			// 
			// button_mourad
			// 
			this->button_mourad->BackColor = System::Drawing::Color::WhiteSmoke;
			this->button_mourad->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 21.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button_mourad->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->button_mourad->Location = System::Drawing::Point(82, 789);
			this->button_mourad->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button_mourad->Name = L"button_mourad";
			this->button_mourad->Size = System::Drawing::Size(384, 108);
			this->button_mourad->TabIndex = 11;
			this->button_mourad->Text = getusername("Mourad@gmail.com", "123456789");;
			this->button_mourad->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button_mourad->UseVisualStyleBackColor = false;
			this->button_mourad->Click += gcnew System::EventHandler(this, &FormDiscuss::mourad_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Myanmar Text", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(142, 159);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(0, 50);
			this->label1->TabIndex = 12;
			this->label1->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->label1->Click += gcnew System::EventHandler(this, &FormDiscuss::textBox1_Click_1);
			this->label1->Text = username;
			// 
			// button_anas
			// 
			this->button_anas->BackColor = System::Drawing::Color::WhiteSmoke;
			this->button_anas->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 21.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button_anas->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->button_anas->Location = System::Drawing::Point(82, 381);
			this->button_anas->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button_anas->Name = L"button_anas";
			this->button_anas->Size = System::Drawing::Size(384, 108);
			this->button_anas->TabIndex = 15;
			this->button_anas->Text = getusername("anasichmawin87@gmail", "anas");
			this->button_anas->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button_anas->UseVisualStyleBackColor = false;
			this->button_anas->BackColorChanged += gcnew System::EventHandler(this, &FormDiscuss::label7_BackColorChanged);
			this->button_anas->Click += gcnew System::EventHandler(this, &FormDiscuss::anas_Click);
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox2->ForeColor = System::Drawing::Color::Gray;
			this->textBox2->Location = System::Drawing::Point(477, 879);
			this->textBox2->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox2->Size = System::Drawing::Size(933, 83);
			this->textBox2->TabIndex = 25;
			this->textBox2->Text = L"    Write Your Message";
			this->textBox2->Click += gcnew System::EventHandler(this, &FormDiscuss::message_click);
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &FormDiscuss::textBox2_TextChanged_1);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Ebrima", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(1140, 662);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(0, 32);
			this->label2->TabIndex = 26;
			this->label2->BackColorChanged += gcnew System::EventHandler(this, &FormDiscuss::label7_BackColorChanged);
			this->label2->Click += gcnew System::EventHandler(this, &FormDiscuss::textBox1_Click_1);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Ebrima", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(489, 615);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(0, 32);
			this->label3->TabIndex = 27;
			this->label3->BackColorChanged += gcnew System::EventHandler(this, &FormDiscuss::label7_BackColorChanged);
			this->label3->Click += gcnew System::EventHandler(this, &FormDiscuss::textBox1_Click_1);
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(0, 1);
			this->pictureBox2->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(117, 78);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 49;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Click += gcnew System::EventHandler(this, &FormDiscuss::textBox1_Click_1);
			// 
			// pictureBox10
			// 
			this->pictureBox10->BackColor = System::Drawing::Color::DarkGray;
			this->pictureBox10->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox10.Image")));
			this->pictureBox10->Location = System::Drawing::Point(1389, 778);
			this->pictureBox10->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->pictureBox10->Name = L"pictureBox10";
			this->pictureBox10->Size = System::Drawing::Size(74, 75);
			this->pictureBox10->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox10->TabIndex = 60;
			this->pictureBox10->TabStop = false;
			this->pictureBox10->Click += gcnew System::EventHandler(this, &FormDiscuss::pictureBox10_Click);
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::SystemColors::MenuBar;
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(478, 194);
			this->textBox1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(524, 680);
			this->textBox1->TabIndex = 61;
			this->textBox1->Click += gcnew System::EventHandler(this, &FormDiscuss::textBox1_Click_1);
			this->textBox1->BackColorChanged += gcnew System::EventHandler(this, &FormDiscuss::label7_BackColorChanged);
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &FormDiscuss::textBox1_TextChanged_2);
			// 
			// textBox3
			// 
			this->textBox3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->textBox3->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox3->Location = System::Drawing::Point(976, 194);
			this->textBox3->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->textBox3->Multiline = true;
			this->textBox3->Name = L"textBox3";
			this->textBox3->ReadOnly = true;
			this->textBox3->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox3->Size = System::Drawing::Size(524, 680);
			this->textBox3->TabIndex = 66;
			this->textBox3->Click += gcnew System::EventHandler(this, &FormDiscuss::textBox1_Click_1);
			this->textBox3->BackColorChanged += gcnew System::EventHandler(this, &FormDiscuss::label7_BackColorChanged);
			// 
			// textBox4
			// 
			this->textBox4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->textBox4->Location = System::Drawing::Point(976, 108);
			this->textBox4->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->textBox4->Multiline = true;
			this->textBox4->Name = L"textBox4";
			this->textBox4->ReadOnly = true;
			this->textBox4->Size = System::Drawing::Size(499, 85);
			this->textBox4->TabIndex = 68;
			this->textBox4->Click += gcnew System::EventHandler(this, &FormDiscuss::textBox1_Click_1);
			this->textBox4->BackColorChanged += gcnew System::EventHandler(this, &FormDiscuss::label7_BackColorChanged);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 21.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(1000, 124);
			this->label6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(421, 52);
			this->label6->TabIndex = 69;
			this->label6->Text = "";
			this->label6->BackColorChanged += gcnew System::EventHandler(this, &FormDiscuss::label7_BackColorChanged);
			this->label6->Click += gcnew System::EventHandler(this, &FormDiscuss::textBox1_Click_1);

			// 
			// textBox5
			// 
			this->textBox5->BackColor = System::Drawing::SystemColors::MenuBar;
			this->textBox5->Location = System::Drawing::Point(478, 108);
			this->textBox5->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->textBox5->Multiline = true;
			this->textBox5->Name = L"textBox5";
			this->textBox5->ReadOnly = true;
			this->textBox5->Size = System::Drawing::Size(499, 85);
			this->textBox5->TabIndex = 71;
			this->textBox5->Click += gcnew System::EventHandler(this, &FormDiscuss::textBox1_Click_1);
			this->textBox5->BackColorChanged += gcnew System::EventHandler(this, &FormDiscuss::label7_BackColorChanged);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->BackColor = System::Drawing::SystemColors::MenuBar;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 21.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(698, 116);
			this->label7->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(117, 52);
			this->label7->TabIndex = 72;
			this->label7->Text = L"YOU";
			this->label7->BackColorChanged += gcnew System::EventHandler(this, &FormDiscuss::label7_BackColorChanged);
			this->label7->Click += gcnew System::EventHandler(this, &FormDiscuss::textBox1_Click_1);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::LightGray;
			this->button2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button2.BackgroundImage")));
			this->button2->Location = System::Drawing::Point(367, 0);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 74);
			this->button2->TabIndex = 89;
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &FormDiscuss::button4_Click);
			// 
			// textBox6
			// 
			this->textBox6->BackColor = System::Drawing::Color::Silver;
			this->textBox6->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox6->ForeColor = System::Drawing::Color::Black;
			this->textBox6->Location = System::Drawing::Point(7, 17);
			this->textBox6->Multiline = true;
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(249, 39);
			this->textBox6->TabIndex = 12;
			this->textBox6->Click += gcnew System::EventHandler(this, &FormDiscuss::textBox6_Click);
			this->textBox6->TextChanged += gcnew System::EventHandler(this, &FormDiscuss::textBox6_TextChanged);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(149, 68);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(122, 100);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 83;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &FormDiscuss::textBox1_Click_1);
			// 
			// pictureBox3
			// 
			this->pictureBox3->BackColor = System::Drawing::Color::IndianRed;
			this->pictureBox3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.Image")));
			this->pictureBox3->InitialImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.InitialImage")));
			this->pictureBox3->Location = System::Drawing::Point(0, 381);
			this->pictureBox3->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(84, 108);
			this->pictureBox3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox3->TabIndex = 84;
			this->pictureBox3->TabStop = false;
			this->pictureBox3->Click += gcnew System::EventHandler(this, &FormDiscuss::textBox1_Click_1);
			// 
			// pictureBox4
			// 
			this->pictureBox4->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox4.Image")));
			this->pictureBox4->Location = System::Drawing::Point(1, 511);
			this->pictureBox4->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(84, 108);
			this->pictureBox4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox4->TabIndex = 85;
			this->pictureBox4->TabStop = false;
			this->pictureBox4->Click += gcnew System::EventHandler(this, &FormDiscuss::textBox1_Click_1);
			// 
			// pictureBox5
			// 
			this->pictureBox5->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox5->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox5.Image")));
			this->pictureBox5->Location = System::Drawing::Point(1, 646);
			this->pictureBox5->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->Size = System::Drawing::Size(84, 108);
			this->pictureBox5->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox5->TabIndex = 86;
			this->pictureBox5->TabStop = false;
			this->pictureBox5->Click += gcnew System::EventHandler(this, &FormDiscuss::textBox1_Click_1);
			// 
			// pictureBox7
			// 
			this->pictureBox7->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox7->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox7.Image")));
			this->pictureBox7->Location = System::Drawing::Point(-5, 789);
			this->pictureBox7->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->pictureBox7->Name = L"pictureBox7";
			this->pictureBox7->Size = System::Drawing::Size(89, 108);
			this->pictureBox7->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox7->TabIndex = 87;
			this->pictureBox7->TabStop = false;
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->button1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button1.Image")));
			this->button1->Location = System::Drawing::Point(1379, 879);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(96, 87);
			this->button1->TabIndex = 88;
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &FormDiscuss::button1_Click_2);
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::Silver;
			this->panel1->Controls->Add(this->textBox6);
			this->panel1->Controls->Add(this->button2);
			this->panel1->Location = System::Drawing::Point(15, 258);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(442, 74);
			this->panel1->TabIndex = 80;
			this->panel1->Click += gcnew System::EventHandler(this, &FormDiscuss::textBox1_Click_1);
			this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &FormDiscuss::panel1_Paint);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(18, 226);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(190, 29);
			this->label4->TabIndex = 89;
			this->label4->Text = L"Search a friend";
			// 
			// pictureBox_search
			// 
			this->pictureBox_search->BackColor = System::Drawing::Color::IndianRed;
			this->pictureBox_search->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox_search.Image")));
			this->pictureBox_search->InitialImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox_search.InitialImage")));
			this->pictureBox_search->Location = System::Drawing::Point(0, 381);
			this->pictureBox_search->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->pictureBox_search->Name = L"pictureBox_search";
			this->pictureBox_search->Size = System::Drawing::Size(84, 108);
			this->pictureBox_search->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox_search->TabIndex = 91;
			this->pictureBox_search->TabStop = false;
			this->pictureBox_search->Visible = false;
			// 
			// pers_search
			// 
			this->pers_search->BackColor = System::Drawing::Color::WhiteSmoke;
			this->pers_search->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 21.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->pers_search->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->pers_search->Location = System::Drawing::Point(82, 381);
			this->pers_search->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pers_search->Name = L"pers_search";
			this->pers_search->Size = System::Drawing::Size(384, 108);
			this->pers_search->TabIndex = 90;
			this->pers_search->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->pers_search->UseVisualStyleBackColor = false;
			this->pers_search->Visible = false;
			this->pers_search->Click += gcnew System::EventHandler(this, &FormDiscuss::search_click);
			// 
			// FormDiscuss
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::WhiteSmoke;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(1476, 966);
			this->Controls->Add(this->pictureBox_search);
			this->Controls->Add(this->pers_search);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox7);
			this->Controls->Add(this->pictureBox5);
			this->Controls->Add(this->pictureBox4);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button_anas);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->pictureBox10);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button_mourad);
			this->Controls->Add(this->button_amine);
			this->Controls->Add(this->button_othmane);
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"FormDiscuss";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &FormDiscuss::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox10))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_search))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
    private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void ICHMAWIN_Anas(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void label2_Click_1(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void textBox1_TextChanged_1(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void backgroundWorker2_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {}
	private: System::Void backgroundWorker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {}
	private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void button1_Click_1(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void label2_Click_2(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void textBox2_TextChanged_1(System::Object^ sender, System::EventArgs^ e) {

		if (textBox2->Text == "    Write Your Message") {
			textBox2->Text = "";
		}

	}
	private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void label2_Click_3(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void pictureBox2_Click(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void pictureBox1_Click_1(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void button7_Click(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void textBox1_TextChanged_2(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void pictureBox10_Click(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void label6_Click(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void label1_Click_1(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void label4_Click(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void pictureBox1_Click_2(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void textBox6_TextChanged(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {}
	private: System::Void textBox6_Click(System::Object^ sender, System::EventArgs^ e) {
		if (textBox6->Text == "Search a friend") {
			textBox6->Text = "";
		}
	}
	private: System::Void label7_BackColorChanged(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void textBox5_Click(System::Object^ sender, System::EventArgs^ e) {
		if (textBox6->Text == "") {
			textBox6->Text = "Search a friend";
		}
		if (textBox2->Text == "") {
			textBox2->Text = "    Write Your Message";
		}
	}
	private: System::Void textBox1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (textBox6->Text == "") {
			textBox6->Text = "Search a friend";
		}
	}
	private: System::Void radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ user = this->textBox6->Text;
		if (user == "Anas Ichmawin" || user == "Othmane Bochta" || user == "Amine Fatih" || user == "Mourad Imani") {
			if (user == "Anas Ichmawin") {
				this->button_othmane->Visible = false;
				this->pictureBox4->Visible = false;


				this->button_amine->Visible = false;
				this->pictureBox5->Visible = false;

				this->button_mourad->Visible = false;
				this->pictureBox7->Visible = false;

				this->button_anas->Visible = true;
				this->pictureBox3->Visible = true;

			}
			if (user == "Othmane Bochta") {
				this->button_anas->Visible = false;
				this->pictureBox3->Visible = false;


				this->button_amine->Visible = false;
				this->pictureBox5->Visible = false;


				this->button_mourad->Visible = false;
				this->pictureBox7->Visible = false;


				this->button_othmane->Visible = true;
				this->pictureBox4->Visible = true;
			}
			if (user == "Amine Fatih") {
				this->button_anas->Visible = false;
				this->pictureBox3->Visible = false;


				this->button_othmane->Visible = false;
				this->pictureBox4->Visible = false;


				this->button_mourad->Visible = false;
				this->pictureBox7->Visible = false;


				this->button_amine->Visible = true;
				this->pictureBox5->Visible = true;

			}
			if (user == "Mourad Imani") {
				this->button_anas->Visible = false;
				this->pictureBox3->Visible = false;


				this->button_othmane->Visible = false;
				this->pictureBox4->Visible = false;


				this->button_amine->Visible = false;
				this->pictureBox5->Visible = false;


				this->button_mourad->Visible = true;
				this->pictureBox7->Visible = true;

			}
		}
		else {
			String^ connectionString = "server=sql8.freesqldatabase.com;Uid=sql8670602;Password=VbbEPLEMNch6xufa;Database=sql8670602";
			MySqlConnection^ con = gcnew MySqlConnection(connectionString);

			String^ usernameAsearche = this->textBox6->Text;
			String^ query = "SELECT Username FROM register WHERE Username = @Username";
			MySqlCommand^ command = gcnew MySqlCommand(query, con);
			command->Parameters->AddWithValue("@Username", usernameAsearche);

			con->Open();

			try {
				Object^ Username = command->ExecuteScalar();

				if (Username != nullptr) {
					// Utiliser le nom d'utilisateur récupéré
					String^ usernameString = Username->ToString();  // Utilise un nom différent pour éviter la confusion

					this->pers_search->Text = usernameString;
					this->pictureBox_search->Visible = true;
					this->pers_search->Visible = true;
					this->button_anas->Visible = false;
					this->pictureBox3->Visible = false;
					this->button_othmane->Visible = false;
					this->pictureBox4->Visible = false;
					this->button_amine->Visible = false;
					this->pictureBox5->Visible = false;
					this->button_mourad->Visible = false;
					this->pictureBox7->Visible = false;
				}
				else {
					this->button_anas->Visible = false;
					this->pictureBox3->Visible = false;


					this->button_othmane->Visible = false;
					this->pictureBox4->Visible = false;


					this->button_amine->Visible = false;
					this->pictureBox5->Visible = false;


					this->button_mourad->Visible = false;
					this->pictureBox7->Visible = false;


					MessageBox::Show("NO DATA !", "Information", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
			}
			catch (Exception^ ex) {
				MessageBox::Show("Une erreur s'est produite : " + ex->Message, "Erreur", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			finally {
				con->Close();
			}

		}
	}
	private: System::Void anas_Click(System::Object^ sender, System::EventArgs^ e) {
		//	label4->Text = button_anas->Text;
		label6->Text = button_anas->Text;
		textBox3->Text = "";
		textBox1->Text = "";

	}
	private: System::Void othmane_Click(System::Object^ sender, System::EventArgs^ e) {
		//	label4->Text = button_othmane->Text;
		label6->Text = button_othmane->Text;
		textBox3->Text = "";
		textBox1->Text = "";
	}
	private: System::Void amine_Click(System::Object^ sender, System::EventArgs^ e) {
		//label4->Text = button_amine->Text;
		label6->Text = button_amine->Text;
		textBox3->Text = "";
		textBox1->Text = "";
	}
	private: System::Void mourad_Click(System::Object^ sender, System::EventArgs^ e) {
		//label4->Text = button_othmane->Text;
		label6->Text = button_mourad->Text;
		textBox3->Text = "";
		textBox1->Text = "";
	}
	private: System::Void message_click(System::Object^ sender, System::EventArgs^ e) {
		if (textBox2->Text == "    Write Your Message") {
			textBox2->Text = "";
		}
	}
	private: System::Void textBox1_Click_1(System::Object^ sender, System::EventArgs^ e) {
		if (textBox2->Text == "") {
			textBox2->Text = "    Write Your Message";
		}
	}
	private: System::Void search_click(System::Object^ sender, System::EventArgs^ e) {

		label6->Text = pers_search->Text;
		textBox3->Text = "";
		textBox1->Text = "";


	}
	private: System::Void button1_Click_2(System::Object^ sender, System::EventArgs^ e) {

		String^ mString = textBox2->Text;
		String^ other = label6->Text;
		String^ newstring = other + "/" + mString;
		std::string message = msclr::interop::marshal_as<std::string>(newstring);
		SendMessageToServer(clientSocket, message);
		textBox1->Text = textBox1->Text + "\r\n" + textBox2->Text + "\r\n";
		textBox2->Text = "";

	}
	};
}
// langage de programmation C++/CLI (Common Language Infrastructure), 
// qui est une extension de C++ permettant le développement d'applica
// tions pour la plateforme .NET
//C++ / CLI est une variante du langage C++ qui facilite le développement d'applications .NET 
// en permettant l'utilisation de fonctionnalités spécifiques à.NET tout en conservant la possibilité d'utiliser
//  des concepts C++ traditionnels. Cela permet aux développeurs de tirer parti de la plateforme .NET tout en intégrant du code existant en C++.