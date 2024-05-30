#include <fmx.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <random>
#include <stdexcept>
#pragma hdrstop

#include "Interface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TMyInterfaceForm *MyInterfaceForm;

__fastcall TMyInterfaceForm::TMyInterfaceForm(TComponent* Owner)
    : TForm(Owner)
{
	loadAndDisplayPortfolio();
    createStockDataCSV("stockdata.csv");
    readStockData("stockdata.csv");

    // Ensure there is at least one series in the chart
    TLineSeries *series = new TLineSeries(ChartStocks);
    ChartStocks->AddSeries(series);

	updateGraph();
}

void TMyInterfaceForm::loadAndDisplayPortfolio() {
    std::ifstream file("portfolio.txt");
	std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string name, username, password;
            int age;
            double balance;
			int totalStock;

            try {
                ss >> name >> age >> username >> password >> balance >> totalStock;

				// Set the labels
                NameLabel->Text = (UnicodeString("Name: ") + name.c_str());
                AgeLabel->Text = (UnicodeString("Age: ") + age);
                UsernameLabel->Text = (UnicodeString("Username: ") + username.c_str());
                BalanceLabel->Text = (UnicodeString("Balance: ") + balance);
                StockLabel->Text = (UnicodeString("Total Stock: ") + totalStock);

                // Set member variables
				this->balance = balance;
                this->totalStock = totalStock;
            } catch (const std::exception& e) {
                ShowMessage("Error parsing portfolio data: " + UnicodeString(e.what()));
            }
		}
        file.close();
    } else {
        NameLabel->Text = "Unable to open portfolio.txt";
    }
}

void TMyInterfaceForm::createStockDataCSV(const std::string& filename) {
	std::ofstream file(filename);

    if (file.is_open()) {
        file << "Company,Stock Price,Market Cap,Volume,Sector\n";

		std::vector<std::string> companies(100);
        std::vector<double> stockPrices(100);
        std::vector<double> marketCaps(100);
        std::vector<int> volumes(100);
        std::vector<std::string> sectors = {"Technology", "Healthcare", "Finance", "Energy", "Consumer Goods"};

        std::mt19937 gen(42);  // Random number generator
        std::uniform_real_distribution<> priceDist(10, 1000);
		std::uniform_real_distribution<> capDist(1000, 100000);
        std::uniform_int_distribution<> volumeDist(1000, 1000000);
        std::uniform_int_distribution<> sectorDist(0, sectors.size() - 1);

        for (int i = 0; i < 100; ++i) {
			companies[i] = "Company_" + std::to_string(i + 1);
            stockPrices[i] = priceDist(gen);
            marketCaps[i] = capDist(gen);
            volumes[i] = volumeDist(gen);
        }

        for (int i = 0; i < 100; ++i) {
            file << companies[i] << "," << stockPrices[i] << "," << marketCaps[i] << "," << volumes[i] << "," << sectors[sectorDist(gen)] << "\n";
		}

        file.close();
    } else {
        ShowMessage("Unable to create stockdata.csv");
	}
}

void TMyInterfaceForm::readStockData(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    bool firstLine = true;

	if (file.is_open()) {
        while (std::getline(file, line)) {
            if (firstLine) {
                firstLine = false;
                continue;  // Skip the header line
			}

            std::stringstream ss(line);
            Stock stock;
            std::getline(ss, stock.company, ',');
            ss >> stock.price;
            ss.ignore();
            ss >> stock.marketCap;
			ss.ignore();
            ss >> stock.volume;
            ss.ignore();
            std::getline(ss, stock.sector, ',');

			stocks.push_back(stock);
            StockListBox->Items->Add(stock.company.c_str());
        }
        file.close();
    } else {
        ShowMessage("Unable to open stockdata.csv");
    }
}

void TMyInterfaceForm::updateGraph() {
    if (ChartStocks->SeriesCount() == 0) {
        TLineSeries *series = new TLineSeries(ChartStocks);
        ChartStocks->AddSeries(series);
	}

    ChartStocks->Series[0]->Clear();
    for (const auto& stock : stocks) {
        ChartStocks->Series[0]->Add(stock.price, stock.company.c_str(), clTeeColor);
    }
}

void TMyInterfaceForm::buyStock(int stockIndex) {
    if (stockIndex < 0 || stockIndex >= stocks.size()) {
        ShowMessage("Invalid stock index.");
        return;
    }

    Stock& stock = stocks[stockIndex];
    if (balance < stock.price) {
        ShowMessage("Insufficient balance to buy this stock.");
        return;
    }

	balance -= stock.price;
    totalStock += 1;

    BalanceLabel->Text = (UnicodeString("Balance: ") + balance);
    StockLabel->Text = (UnicodeString("Total Stock: ") + totalStock);
    savePortfolioData("portfolio.txt");

    // Debugging message
    ShowMessage("Stock purchased successfully!");
}

void TMyInterfaceForm::sellStock(int stockIndex) {
    if (stockIndex < 0 || stockIndex >= stocks.size()) {
        ShowMessage("Invalid stock index.");
        return;
    }

    Stock& stock = stocks[stockIndex];
    if (totalStock <= 0) {
		ShowMessage("No stocks to sell.");
		return;
    }

    balance += stock.price;
    totalStock -= 1;

    BalanceLabel->Text = (UnicodeString("Balance: ") + balance);
	StockLabel->Text = (UnicodeString("Total Stock: ") + totalStock);
    savePortfolioData("portfolio.txt");

	// Debugging message
	ShowMessage("Stock sold successfully!");
}

void __fastcall TMyInterfaceForm::BuyButtonClick(TObject *Sender) {
    int stockIndex = StockListBox->ItemIndex;
    if (stockIndex == -1) {
		ShowMessage("Please select a stock to buy.");
		return;
	}
	buyStock(stockIndex);
    updateGraph();
}

void __fastcall TMyInterfaceForm::SellButtonClick(TObject *Sender) {
	int stockIndex = StockListBox->ItemIndex;
    if (stockIndex == -1) {
		ShowMessage("Please select a stock to sell.");
        return;
    }
	sellStock(stockIndex);
	updateGraph();
}

void TMyInterfaceForm::savePortfolioData(const std::string& filename) {
	std::ofstream file(filename);
	if (file.is_open()) {
        file << NameLabel->Text.SubString(6, NameLabel->Text.Length()).c_str() << " "
			 << AgeLabel->Text.SubString(6, AgeLabel->Text.Length()).ToInt() << " "
			 << UsernameLabel->Text.SubString(10, UsernameLabel->Text.Length()).c_str() << " "
             << BalanceLabel->Text.SubString(9, BalanceLabel->Text.Length()).ToDouble() << " "
			 << StockLabel->Text.SubString(14, StockLabel->Text.Length()).ToInt() << std::endl;
		file.close();
	} else {
		ShowMessage("Unable to open portfolio.txt for writing.");
	}
}


