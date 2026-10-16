#include <msclr/marshal.h>
#include "Player.h"
#include "Playlist.h"

#define	WATER_STREAM_0		"Ruisseau_Escattes_01.wav"
#define	WATER_STREAM_1		"Ruisseau_Escattes_02.wav"
#pragma once

namespace WinformCplusplus {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	bool isDraggingTimer;

	/// <summary>
	/// Description résumée de MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:

		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
			init();
			currentPlaylist = gcnew Playlist();
			currentIndex = -1;
			hoverIndex = -1;
			SetupTrackList();
			RefreshTrackList();
		}


	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	protected:

	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ fichierToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ savePlaylistToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ addPlaylistToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ clearPlaylistToolStripMenuItem;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::TrackBar^ trackBar1;
	private: System::Windows::Forms::TrackBar^ trackBar2;
	private: System::Windows::Forms::Button^ button3;

	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Timer^ timer2;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;

	private: Playlist^ currentPlaylist;
	private: System::String^ currentPlaylistPath;
	private: System::Windows::Forms::ListView^ listViewTracks;
	private: System::Windows::Forms::TextBox^ labelPlaylist;
	private: System::Windows::Forms::Button^ buttonAddTrack;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::ColumnHeader^ columnNum;
	private: System::Windows::Forms::ColumnHeader^ columnTitle;
	private: System::Windows::Forms::ColumnHeader^ columnDuration;
	private: System::Windows::Forms::ImageList^ imageListRowHeight;
	private: System::Windows::Forms::Button^ LoopButton;
	private: System::Windows::Forms::Label^ SonText;
	private: System::Windows::Forms::Label^ TimerUpdateText;
	private: System::Windows::Forms::Label^ TimerText;





	private: System::ComponentModel::IContainer^ components;
	private: System::Void SelectTrack(int index);
	private: int currentIndex;


	private:
		/// <summary>
		/// Variable nécessaire au concepteur.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
		/// le contenu de cette méthode avec l'éditeur de code.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fichierToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->savePlaylistToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->addPlaylistToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearPlaylistToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->listViewTracks = (gcnew System::Windows::Forms::ListView());
			this->columnNum = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnTitle = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnDuration = (gcnew System::Windows::Forms::ColumnHeader());
			this->imageListRowHeight = (gcnew System::Windows::Forms::ImageList(this->components));
			this->labelPlaylist = (gcnew System::Windows::Forms::TextBox());
			this->buttonAddTrack = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->LoopButton = (gcnew System::Windows::Forms::Button());
			this->SonText = (gcnew System::Windows::Forms::Label());
			this->TimerUpdateText = (gcnew System::Windows::Forms::Label());
			this->TimerText = (gcnew System::Windows::Forms::Label());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->BeginInit();
			this->SuspendLayout();
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// button1
			// 
			this->button1->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->button1->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(52)));
			this->button1->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)),
				static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 30, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->ForeColor = System::Drawing::SystemColors::Control;
			this->button1->Location = System::Drawing::Point(602, 614);
			this->button1->Margin = System::Windows::Forms::Padding(0);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(60, 60);
			this->button1->TabIndex = 1;
			this->button1->Text = L"▶";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fichierToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1373, 24);
			this->menuStrip1->TabIndex = 2;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fichierToolStripMenuItem
			// 
			this->fichierToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->openToolStripMenuItem,
					this->savePlaylistToolStripMenuItem, this->addPlaylistToolStripMenuItem, this->clearPlaylistToolStripMenuItem
			});
			this->fichierToolStripMenuItem->Name = L"fichierToolStripMenuItem";
			this->fichierToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fichierToolStripMenuItem->Text = L"File";
			this->fichierToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::fichierToolStripMenuItem_Click);
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->openToolStripMenuItem->Text = L"Open Playlist";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::openToolStripMenuItem_Click);
			// 
			// savePlaylistToolStripMenuItem
			// 
			this->savePlaylistToolStripMenuItem->Name = L"savePlaylistToolStripMenuItem";
			this->savePlaylistToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->savePlaylistToolStripMenuItem->Text = L"Save Playlist";
			this->savePlaylistToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::savePlaylistToolStripMenuItem_Click);
			// 
			// addPlaylistToolStripMenuItem
			// 
			this->addPlaylistToolStripMenuItem->Name = L"addPlaylistToolStripMenuItem";
			this->addPlaylistToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->addPlaylistToolStripMenuItem->Text = L"Add Playlist";
			// 
			// clearPlaylistToolStripMenuItem
			// 
			this->clearPlaylistToolStripMenuItem->Name = L"clearPlaylistToolStripMenuItem";
			this->clearPlaylistToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->clearPlaylistToolStripMenuItem->Text = L"Clear Playlist";
			this->clearPlaylistToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::clearPlaylistToolStripMenuItem_Click);
			// 
			// button2
			// 
			this->button2->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->button2->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->button2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button2->FlatAppearance->BorderSize = 0;
			this->button2->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(52)));
			this->button2->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)),
				static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 30, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->ForeColor = System::Drawing::SystemColors::Control;
			this->button2->Location = System::Drawing::Point(662, 614);
			this->button2->Margin = System::Windows::Forms::Padding(0);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(60, 60);
			this->button2->TabIndex = 3;
			this->button2->Text = L"⏹";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click_1);
			// 
			// trackBar1
			// 
			this->trackBar1->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->trackBar1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->trackBar1->Location = System::Drawing::Point(381, 677);
			this->trackBar1->Maximum = 10000;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(612, 45);
			this->trackBar1->TabIndex = 4;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &MyForm::trackBar1_Scroll);
			this->trackBar1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::trackBar1_MouseDown);
			this->trackBar1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::trackBar1_MouseMove);
			this->trackBar1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::trackBar1_MouseUp);
			// 
			// trackBar2
			// 
			this->trackBar2->Location = System::Drawing::Point(12, 46);
			this->trackBar2->Maximum = 100;
			this->trackBar2->Name = L"trackBar2";
			this->trackBar2->Orientation = System::Windows::Forms::Orientation::Vertical;
			this->trackBar2->Size = System::Drawing::Size(45, 188);
			this->trackBar2->TabIndex = 5;
			this->trackBar2->Value = 100;
			this->trackBar2->Scroll += gcnew System::EventHandler(this, &MyForm::trackBar2_Scroll);
			// 
			// button3
			// 
			this->button3->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->button3->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->button3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button3->FlatAppearance->BorderSize = 0;
			this->button3->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(52)));
			this->button3->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)),
				static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 30, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button3->ForeColor = System::Drawing::SystemColors::Control;
			this->button3->Location = System::Drawing::Point(783, 614);
			this->button3->Margin = System::Windows::Forms::Padding(0);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(60, 60);
			this->button3->TabIndex = 6;
			this->button3->Text = L"";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::NextMusic);
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// textBox1
			// 
			this->textBox1->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->textBox1->BackColor = System::Drawing::SystemColors::InactiveCaptionText;
			this->textBox1->Enabled = false;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->ForeColor = System::Drawing::SystemColors::Window;
			this->textBox1->Location = System::Drawing::Point(381, 581);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(612, 30);
			this->textBox1->TabIndex = 8;
			this->textBox1->Text = L"No Current Music ";
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
			// 
			// listViewTracks
			// 
			this->listViewTracks->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->listViewTracks->BackColor = System::Drawing::Color::Black;
			this->listViewTracks->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->listViewTracks->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {
				this->columnNum, this->columnTitle,
					this->columnDuration
			});
			this->listViewTracks->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->listViewTracks->ForeColor = System::Drawing::Color::WhiteSmoke;
			this->listViewTracks->FullRowSelect = true;
			this->listViewTracks->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->listViewTracks->HideSelection = false;
			this->listViewTracks->Location = System::Drawing::Point(93, 98);
			this->listViewTracks->MultiSelect = false;
			this->listViewTracks->Name = L"listViewTracks";
			this->listViewTracks->OwnerDraw = true;
			this->listViewTracks->Size = System::Drawing::Size(1193, 448);
			this->listViewTracks->SmallImageList = this->imageListRowHeight;
			this->listViewTracks->TabIndex = 11;
			this->listViewTracks->UseCompatibleStateImageBehavior = false;
			this->listViewTracks->View = System::Windows::Forms::View::Details;
			this->listViewTracks->DrawColumnHeader += gcnew System::Windows::Forms::DrawListViewColumnHeaderEventHandler(this, &MyForm::listViewTracks_DrawColumnHeader);
			this->listViewTracks->DrawItem += gcnew System::Windows::Forms::DrawListViewItemEventHandler(this, &MyForm::listViewTracks_DrawItem);
			this->listViewTracks->DrawSubItem += gcnew System::Windows::Forms::DrawListViewSubItemEventHandler(this, &MyForm::listViewTracks_DrawSubItem);
			this->listViewTracks->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listViewTracks_SelectedIndexChanged);
			this->listViewTracks->DoubleClick += gcnew System::EventHandler(this, &MyForm::listViewTracks_DoubleClick);
			this->listViewTracks->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::listViewTracks_KeyDown);
			this->listViewTracks->MouseLeave += gcnew System::EventHandler(this, &MyForm::listViewTracks_MouseLeave);
			this->listViewTracks->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::listViewTracks_MouseMove);
			this->listViewTracks->Resize += gcnew System::EventHandler(this, &MyForm::listViewTracks_Resize);
			// 
			// columnNum
			// 
			this->columnNum->Text = L"#";
			this->columnNum->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->columnNum->Width = 50;
			// 
			// columnTitle
			// 
			this->columnTitle->Text = L"TITRE";
			this->columnTitle->Width = 300;
			// 
			// columnDuration
			// 
			this->columnDuration->Text = L"DURÉE";
			this->columnDuration->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->columnDuration->Width = 80;
			// 
			// imageListRowHeight
			// 
			this->imageListRowHeight->ColorDepth = System::Windows::Forms::ColorDepth::Depth8Bit;
			this->imageListRowHeight->ImageSize = System::Drawing::Size(1, 36);
			this->imageListRowHeight->TransparentColor = System::Drawing::Color::Transparent;
			// 
			// labelPlaylist
			// 
			this->labelPlaylist->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->labelPlaylist->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->labelPlaylist->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->labelPlaylist->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelPlaylist->ForeColor = System::Drawing::Color::White;
			this->labelPlaylist->Location = System::Drawing::Point(538, 55);
			this->labelPlaylist->Name = L"labelPlaylist";
			this->labelPlaylist->ReadOnly = true;
			this->labelPlaylist->Size = System::Drawing::Size(285, 25);
			this->labelPlaylist->TabIndex = 12;
			this->labelPlaylist->TabStop = false;
			this->labelPlaylist->Text = L"Label Playlist";
			this->labelPlaylist->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// buttonAddTrack
			// 
			this->buttonAddTrack->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->buttonAddTrack->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(162)), static_cast<System::Int32>(static_cast<System::Byte>(56)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->buttonAddTrack->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonAddTrack->FlatAppearance->BorderSize = 0;
			this->buttonAddTrack->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonAddTrack->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonAddTrack->ForeColor = System::Drawing::Color::White;
			this->buttonAddTrack->Location = System::Drawing::Point(1224, 54);
			this->buttonAddTrack->Margin = System::Windows::Forms::Padding(0);
			this->buttonAddTrack->Name = L"buttonAddTrack";
			this->buttonAddTrack->Size = System::Drawing::Size(125, 21);
			this->buttonAddTrack->TabIndex = 13;
			this->buttonAddTrack->Text = L"add track";
			this->buttonAddTrack->TextImageRelation = System::Windows::Forms::TextImageRelation::TextAboveImage;
			this->buttonAddTrack->UseVisualStyleBackColor = false;
			this->buttonAddTrack->Click += gcnew System::EventHandler(this, &MyForm::buttonAddTrack_Click);
			// 
			// button4
			// 
			this->button4->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->button4->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->button4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button4->FlatAppearance->BorderSize = 0;
			this->button4->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(52)));
			this->button4->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)),
				static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button4->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 30, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button4->ForeColor = System::Drawing::SystemColors::Control;
			this->button4->Location = System::Drawing::Point(542, 614);
			this->button4->Margin = System::Windows::Forms::Padding(0);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(60, 60);
			this->button4->TabIndex = 7;
			this->button4->Text = L"";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::lastTrack);
			// 
			// LoopButton
			// 
			this->LoopButton->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->LoopButton->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->LoopButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->LoopButton->FlatAppearance->BorderSize = 0;
			this->LoopButton->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(52)));
			this->LoopButton->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)),
				static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->LoopButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->LoopButton->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 30, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->LoopButton->ForeColor = System::Drawing::SystemColors::Control;
			this->LoopButton->Location = System::Drawing::Point(722, 614);
			this->LoopButton->Margin = System::Windows::Forms::Padding(0);
			this->LoopButton->Name = L"LoopButton";
			this->LoopButton->Size = System::Drawing::Size(60, 60);
			this->LoopButton->TabIndex = 15;
			this->LoopButton->Text = L"🔁";
			this->LoopButton->UseVisualStyleBackColor = false;
			this->LoopButton->Click += gcnew System::EventHandler(this, &MyForm::LoopButton_Click);
			// 
			// SonText
			// 
			this->SonText->AutoSize = true;
			this->SonText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 25, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SonText->Location = System::Drawing::Point(5, 237);
			this->SonText->Name = L"SonText";
			this->SonText->Size = System::Drawing::Size(55, 39);
			this->SonText->TabIndex = 17;
			this->SonText->Text = L"🔊";
			// 
			// TimerUpdateText
			// 
			this->TimerUpdateText->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->TimerUpdateText->AutoSize = true;
			this->TimerUpdateText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TimerUpdateText->Location = System::Drawing::Point(329, 677);
			this->TimerUpdateText->Name = L"TimerUpdateText";
			this->TimerUpdateText->Size = System::Drawing::Size(46, 25);
			this->TimerUpdateText->TabIndex = 19;
			this->TimerUpdateText->Text = L"--:--";
			// 
			// TimerText
			// 
			this->TimerText->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->TimerText->AutoSize = true;
			this->TimerText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TimerText->Location = System::Drawing::Point(999, 677);
			this->TimerText->Name = L"TimerText";
			this->TimerText->Size = System::Drawing::Size(46, 25);
			this->TimerText->TabIndex = 20;
			this->TimerText->Text = L"--:--";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1373, 716);
			this->Controls->Add(this->TimerText);
			this->Controls->Add(this->TimerUpdateText);
			this->Controls->Add(this->SonText);
			this->Controls->Add(this->LoopButton);
			this->Controls->Add(this->buttonAddTrack);
			this->Controls->Add(this->labelPlaylist);
			this->Controls->Add(this->listViewTracks);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->trackBar2);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->menuStrip1);
			this->ForeColor = System::Drawing::SystemColors::Control;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->MinimumSize = System::Drawing::Size(800, 500);
			this->Name = L"MyForm";
			this->Text = L"Audio Playlist Maker";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void LoadPlaylist(String^ filePath);

	private: System::Void openToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void fichierToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void AddTrack();
	private: int hoverIndex;
	private: System::Void SetupTrackList();
	private: System::Void RefreshTrackList();
	private: bool LoadTrack(int index);
	private: System::Void PlayTrack(int index);
	private: System::Void listViewTracks_DoubleClick(System::Object^ sender, System::EventArgs^ e);
	private: System::Void listViewTracks_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);
	private: System::Void listViewTracks_DrawColumnHeader(System::Object^ sender, System::Windows::Forms::DrawListViewColumnHeaderEventArgs^ e);
	private: System::Void listViewTracks_DrawItem(System::Object^ sender, System::Windows::Forms::DrawListViewItemEventArgs^ e) {}
	private: System::Void listViewTracks_DrawSubItem(System::Object^ sender, System::Windows::Forms::DrawListViewSubItemEventArgs^ e);
	private: System::Void listViewTracks_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void listViewTracks_MouseLeave(System::Object^ sender, System::EventArgs^ e);
	private: System::Void listViewTracks_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void listViewTracks_Resize(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonAddTrack_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button2_Click_1(System::Object^ sender, System::EventArgs^ e);
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e);
	private: System::Void trackBar1_Scroll(System::Object^ sender, System::EventArgs^ e);
	private: System::Void trackBar1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void trackBar1_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void trackBar1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void SeekToMouse(int x);
	private: System::Void SavePlayList();
	private: System::Void UpdateVolume(float volume);
	private: System::Void trackBar2_Scroll(System::Object^ sender, System::EventArgs^ e);
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void savePlaylistToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void lastTrack(System::Object^ sender, System::EventArgs^ e);
	private: System::Void NextMusic(System::Object^ sender, System::EventArgs^ e);

	private: System::Void LoopButton_Click(System::Object^ sender, System::EventArgs^ e);

private: System::Void clearPlaylistToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
};
}

