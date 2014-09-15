#pragma once

namespace oscontrols {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
  using namespace System::Resources;
  using namespace System::Reflection;

	/// <summary>
	/// Summary for NativeUI
	/// </summary>
	public ref class NativeUIWin : public System::Windows::Forms::Form
	{
	public:
    NativeUIWin(void)
		{
			InitializeComponent();
			
      ResourceManager^ rm = gcnew ResourceManager("oscontrols.Resource", Assembly::GetExecutingAssembly());
      System::Drawing::Bitmap^ bmp = (System::Drawing::Bitmap^) rm->GetObject("icon_512x512");

      auto icon = System::Drawing::Icon::FromHandle(bmp->GetHicon());
      this->notificationIcon->Icon = icon;
      this->Icon = icon;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
    ~NativeUIWin()
		{
			if (components)
			{
				delete components;
			}
		}
  private: System::Windows::Forms::NotifyIcon^  notificationIcon;
  protected:

  protected:
  private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip1;
  private: System::Windows::Forms::ToolStripMenuItem^  configToolStripMenuItem;
  private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;


  protected:
  private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
      this->components = (gcnew System::ComponentModel::Container());
      this->notificationIcon = (gcnew System::Windows::Forms::NotifyIcon(this->components));
      this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
      this->configToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->contextMenuStrip1->SuspendLayout();
      this->SuspendLayout();
      // 
      // notificationIcon
      // 
      this->notificationIcon->Text = L"Leap Hand Control";
      this->notificationIcon->Visible = true;
      // 
      // contextMenuStrip1
      // 
      this->contextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
        this->configToolStripMenuItem,
          this->exitToolStripMenuItem
      });
      this->contextMenuStrip1->Name = L"contextMenuStrip1";
      this->contextMenuStrip1->ShowImageMargin = false;
      this->contextMenuStrip1->Size = System::Drawing::Size(92, 48);
      // 
      // configToolStripMenuItem
      // 
      this->configToolStripMenuItem->Name = L"configToolStripMenuItem";
      this->configToolStripMenuItem->Size = System::Drawing::Size(91, 22);
      this->configToolStripMenuItem->Text = L"Config..";
      // 
      // exitToolStripMenuItem
      // 
      this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
      this->exitToolStripMenuItem->Size = System::Drawing::Size(91, 22);
      this->exitToolStripMenuItem->Text = L"Quit";
      // 
      // NativeUIWin
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(284, 262);
      this->Name = L"NativeUIWin";
      this->Text = L"NativeUI";
      this->contextMenuStrip1->ResumeLayout(false);
      this->ResumeLayout(false);

    }
#pragma endregion
	};
}
