//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class TMyMainForm : public TForm
{
__published:	// IDE-managed Components
	TButton *LoginNavigationButton;
	TButton *RegistrationNavigationButton;
	void __fastcall LoginNavigationButtonClick(TObject *Sender);
	void __fastcall RegistrationNavigationButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TMyMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMyMainForm *MyMainForm;
//---------------------------------------------------------------------------
#endif
