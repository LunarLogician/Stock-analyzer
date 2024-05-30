//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "MainForm.h"
#include "LoginForm.h"
#include"RegisterationForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TMyMainForm *MyMainForm;
//---------------------------------------------------------------------------
__fastcall TMyMainForm::TMyMainForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMyMainForm::LoginNavigationButtonClick(TObject *Sender)
{
      MyLoginForm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMyMainForm::RegistrationNavigationButtonClick(TObject *Sender)
{
		 MyRegistrationForm->Show();
}
//---------------------------------------------------------------------------
