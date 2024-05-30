#ifndef RegisterationFormH
#define RegisterationFormH

#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include "User.h"

class TMyRegistrationForm : public TForm
{
__published:    // IDE-managed Components
	TEdit *NameEdit;
	TLabel *NameLabel;
	TEdit *AgeEdit;
	TLabel *AgeLabel;
	TEdit *UsernameEdit;
	TLabel *UsernameLabel;
	TEdit *PasswordEdit;
	TLabel *PasswordLabel;
	TButton *SaveButton;
	TLabel *StatusLabel;

	void __fastcall SaveButtonClick(TObject *Sender);

private:    // User declarations
	User* root;
	void insert(User* &node, std::string name, int age, std::string username, std::string password);
    User* search(User* node, std::string username, std::string password);
	void saveToFile(User* user);
	void saveToPortfolio(User* user);
    void loadUsers();
	std::string encrypt(std::string data);
    std::string decrypt(std::string data);

public:        // User declarations
	__fastcall TMyRegistrationForm(TComponent* Owner);
};

extern PACKAGE TMyRegistrationForm *MyRegistrationForm;

#endif // RegisterationFormH

