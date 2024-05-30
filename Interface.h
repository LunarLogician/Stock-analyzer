#ifndef InterfaceH
#define InterfaceH

#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMXTee.Chart.hpp>
#include <FMXTee.Engine.hpp>
#include <FMXTee.Procs.hpp>
#include <FMXTee.Series.hpp>
#include <FMX.Edit.hpp>
#include <FMX.ListBox.hpp>
#include <vector>
#include <string>

class TMyInterfaceForm : public TForm
{
__published:    // IDE-managed Components
    TLabel *NameLabel;
    TLabel *AgeLabel;
    TLabel *UsernameLabel;
    TButton *LogoutButton;
    TLabel *BalanceLabel;
    TLabel *StockLabel;
    TButton *BuyButton;
    TButton *SellButton;
    TChart *ChartStocks;
    TComboBox *StockListBox;

    void __fastcall BuyButtonClick(TObject *Sender);
    void __fastcall SellButtonClick(TObject *Sender);

private:    // User declarations
    void loadAndDisplayPortfolio();
    void updateGraph();
    void readStockData(const std::string& filename);
    void savePortfolioData(const std::string& filename);
    void buyStock(int stockIndex);
    void sellStock(int stockIndex);
    void createStockDataCSV(const std::string& filename); // Declare the function here

    struct Stock {
        std::string company;
        double price;
        double marketCap;
        int volume;
        std::string sector;
    };
    std::vector<Stock> stocks;
    double balance;
    int totalStock;

public:        // User declarations
    __fastcall TMyInterfaceForm(TComponent* Owner);
};

extern PACKAGE TMyInterfaceForm *MyInterfaceForm;

#endif // InterfaceH


