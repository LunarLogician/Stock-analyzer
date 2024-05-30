#ifndef LoginFormH
#define LoginFormH

#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include "User.h"
#include"Interface.h"

class TMyLoginForm : public TForm
{
__published:    // IDE-managed Components
    TEdit *UsernameEdit;
    TLabel *UsernameLabel;
    TEdit *PasswordEdit;
    TLabel *PasswordLabel;
    TButton *LoginButton;
    TLabel *StatusLabel;

    void __fastcall LoginButtonClick(TObject *Sender);

private:    // User declarations
    User* root;
    void insert(User* &node, std::string name, int age, std::string username, std::string password);
    User* search(User* node, std::string username, std::string password);
    void loadUsers();
    std::string decrypt(std::string data);

public:        // User declarations
    __fastcall TMyLoginForm(TComponent* Owner);
};

extern PACKAGE TMyLoginForm *MyLoginForm;

#endif // LoginFormH

