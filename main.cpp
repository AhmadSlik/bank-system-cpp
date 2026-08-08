#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

enum enUserChoise{enShowClientList = 1, enAddNewClient =2, enDeleteClient = 3, enUpdateClientInfo = 4, enFindClient = 5};

struct stReadinfo
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    int AccountBalance;
    bool MarkeDeleted = false;
    bool MarkeUpdate = false;
};

const string FileName = "ClientRecord.txt";
void StartProgram(enUserChoise UserChoise);

void PrintMainMenueScreen()
{
    system("clear");
    cout << "____________________________________________________\n";
    cout << "____________________________________________________\n";
    cout << "\t\tMain Menue Screen \n";
    cout << "____________________________________________________\n";
    cout << "____________________________________________________\n";
    cout << "\t[1] Show Client List." << endl;
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Exit.\n";
    cout << "____________________________________________________\n";
    cout << "____________________________________________________" << endl;
}

enUserChoise UserChoise()
{
    PrintMainMenueScreen();
    short UserChoise = 0;
    do
    {
        cout << "Choose what do you want to do? [1 to 6]? ";
        cin >> UserChoise;
    } while (UserChoise < 1 || UserChoise > 6);
    return (enUserChoise)UserChoise;
}

void PringHeadar(int count)
{
    cout << "\t\t\t\t" << "Client List (" << count << ") Client(s)\t\t\n";
    cout << "___________________________________________________________________________________________\n";
    cout << "|Account Number    ";
    cout << "|PinCode     ";
    cout << "|Client Name        ";
    cout << "|Phone          ";
    cout << "|Account Balance   \n";
    cout << "___________________________________________________________________________________________\n";
}

vector <string> SplitRecord(string Record, string Seperater)
{
    short Pos= 0;
    string word = "";
    vector <string> Vword;
    while((Pos = Record.find(Seperater)) != string::npos)
    {
        word = Record.substr(0, Pos);
        if(word != "")
        {
        Vword.push_back(word);
        Record.erase(0, Pos + Seperater.length());
        }
    }
    if(Record != "")
    {
        Vword.push_back(Record);
    }
    return Vword;
}
stReadinfo FillStructByRecord(string Record)
{
    stReadinfo info;
    vector <string> vClineData;
    vClineData = SplitRecord(Record, "#//#");
    info.AccountNumber = vClineData[0];
    info.PinCode = vClineData[1];
    info.Name = vClineData[2];
    info.Phone = vClineData[3];
    info.AccountBalance = stoi(vClineData[4]);
    return info;
}
void PringClientRecordForList(stReadinfo info)
{
    cout << "| " << left << setw(17) << info.AccountNumber;
    cout << "| " << left << setw(11) << info.PinCode;
    cout << "| " << left << setw(18) << info.Name ;
    cout << "| " << left << setw(14) << info.Phone;
    cout << "| " << left << setw(7)  << info.AccountBalance << endl;
}

vector<stReadinfo> LoadClientsDataFromFile(string FileName)
{
    vector<stReadinfo> vClients;
    string Record;
    fstream ClientRecordFile;
    ClientRecordFile.open(FileName, ios::in);
    
    if(ClientRecordFile.is_open())
    {
        while (getline(ClientRecordFile, Record))
        {
            stReadinfo info = FillStructByRecord(Record);
            vClients.push_back(info);
        }
        ClientRecordFile.close();
    }
    return vClients;
}

bool ChechAccountIfExist(vector<stReadinfo> &vClients, string AccountNumber)
{
        for (stReadinfo info : vClients)
        {
           if(AccountNumber == info.AccountNumber)
            {
                cout << "Client with Account Number (" << AccountNumber << ") is already, exists, Input anther Acount Number ";
                return false;
            }
        }
        return true;
}

stReadinfo FillStructForAddNew()
{
    stReadinfo info;
    string AccountNumber = "";
    vector<stReadinfo> vClients;
    cout << "Please Input Clien Data:\n";
    cout << "Input your Account Number? " <<endl;
    do
    {
        getline(cin >> ws, info.AccountNumber);
        AccountNumber  = info.AccountNumber;
        vClients = LoadClientsDataFromFile(FileName);
    } while (!ChechAccountIfExist(vClients , AccountNumber));

    cout << "Input your PinCode ?" <<endl;
    getline(cin,info.PinCode);
    cout << "Input your Name? " <<endl;
    getline(cin, info.Name);
    cout << "Input your Phone? " <<endl;
    getline(cin,info.Phone);
    cout << "Input your Account Balance? " <<endl;
    cin >> info.AccountBalance;
    cin.ignore();
    return info;
}

stReadinfo FillStructForUpdate(string AccountNumber)
{
    stReadinfo info;
    cout << "Please Input Clien Data:\n\n";
    info.AccountNumber = AccountNumber;
    cout << "Input your PinCode ?" <<endl;
    getline(cin >> ws, info.PinCode);
    cout << "Input your Name? " <<endl;
    getline(cin, info.Name);
    cout << "Input your Phone? " <<endl;
    getline(cin,info.Phone);
    cout << "Input your Account Balance? " <<endl;
    cin >> info.AccountBalance;
    cin.ignore();
    return info;
}

string ConvertRecordToLine(stReadinfo info, string Seperator = "#//#")
{
    string ClientRecord ="";
    ClientRecord += info.AccountNumber + Seperator;
    ClientRecord += info.PinCode + Seperator;
    ClientRecord += info.Name + Seperator;
    ClientRecord += info.Phone + Seperator;
    ClientRecord += to_string(info.AccountBalance);
    return ClientRecord;
}

void SaveClientRecordInFile(string ClientRecord, string FileName)
{
    fstream ClientRecordFile;
    ClientRecordFile.open(FileName, ios::out | ios::app);
    if(ClientRecordFile.is_open())
    {
        ClientRecordFile << ClientRecord << endl;
    }
    ClientRecordFile.close();
}

string ReadAccountNumber()
{
    string AccountNumber;
    cout << "Input AccountNumber? ";
    cin >> AccountNumber;
    cout << "\n";
    return AccountNumber;
}

void PringClientRecord(stReadinfo info)
{
    cout << "Account Number: " << info.AccountNumber << endl;
    cout << "PinCode : " <<  info.PinCode << endl;
    cout << "Name : " <<  info.Name << endl;
    cout << "Phone : " <<  info.Phone << endl;
    cout << "Account Balance : " <<  info.AccountBalance << endl;
}

bool PrintInfoAccoutNumber(vector<stReadinfo> &vClients, string AccountNumber)
{
        for (stReadinfo info : vClients)
        {
           if(AccountNumber == info.AccountNumber)
            {
                cout << "The following are the client details : \n\n";  
                PringClientRecord(info);
                return true;
            }
        }
        cout << "Client with Account Number (" << AccountNumber << ") Is Not Found!";
        return false;
}

bool MarkForDeletedOrUpdate(vector<stReadinfo> &vClients, string AccountNumber)
{
    for(stReadinfo &Clinet : vClients)
    {
        if(Clinet.AccountNumber == AccountNumber)
        {
            Clinet.MarkeDeleted = true;
            Clinet.MarkeUpdate = true;
        }
    }
    return false;
}

vector <stReadinfo> SaveCleintsDataToFileFromDelete(string FileName, vector <stReadinfo> &vClients)
{
fstream ClientRecordFile;
ClientRecordFile.open(FileName, ios::out);
string DataLine;
if (ClientRecordFile.is_open())
{
    for (stReadinfo Clinet : vClients)
    {
        if (Clinet.MarkeDeleted == false)
    {
        DataLine = ConvertRecordToLine(Clinet);
        ClientRecordFile << DataLine << endl;
    }
    } 
    ClientRecordFile.close();
}
return vClients;
}

void DeletCline(vector<stReadinfo> &vClients, string AccountNumber)
{
    char Answer;
    if(PrintInfoAccoutNumber(vClients, AccountNumber))
    {
        cout << "\nAre ou sure you want to delete this clint y/n ? ";
        cin >> Answer;
        if(tolower(Answer) == 'y')
        {
        MarkForDeletedOrUpdate(vClients,AccountNumber);
        SaveCleintsDataToFileFromDelete(FileName, vClients);
        vClients = LoadClientsDataFromFile(FileName);
        cout << "Clinet deleted successflly. ";
        return;
        }
        else
        {
        return;
        }
    }
}


vector <stReadinfo> SaveCleintsDataToFileFromUpdate(string FileName, vector <stReadinfo> &vClients, string AccountNumber)
{
fstream ClientRecordFile;
ClientRecordFile.open(FileName, ios::out);
string DataLine;
if (ClientRecordFile.is_open())
{
    for (stReadinfo &info : vClients)
    {
        if (info.MarkeUpdate == false)
    {
        DataLine = ConvertRecordToLine(info);
        ClientRecordFile << DataLine << endl;
    }
    else
    {
        stReadinfo info = FillStructForUpdate(AccountNumber);
        DataLine = ConvertRecordToLine(info);
        ClientRecordFile << DataLine << endl;
    }
    } 
    ClientRecordFile.close();
}
return vClients;
}

void ShowInfoAllClinte()
{
    vector <stReadinfo> Vcount = LoadClientsDataFromFile(FileName);
    PringHeadar(Vcount.size());
    for(stReadinfo &info :Vcount)
    {
        PringClientRecordForList(info);
    }
    cout << "___________________________________________________________________________________________\n";
}

void AddNewClient()
{
    char AddMoreClient = 'y';
    cout << "____________________________________________________\n";
    cout << "\t\tAdd Client Screen\n";
    cout << "____________________________________________________\n\n";
    while(AddMoreClient == 'Y' || AddMoreClient == 'y')
    {
    stReadinfo info;
    info =  FillStructForAddNew();
    cout << "Cline Record For Savinf Is :\n";
    string ClientRecord = ConvertRecordToLine(info);
    cout << ClientRecord;
    SaveClientRecordInFile(ClientRecord, FileName);
    cout << "\nDo you want to add more clients? y/n \n";
    cin >> AddMoreClient;
    cin.ignore();
    }
}

void StartDeletCline()
{
    cout << "____________________________________________________\n";
    cout << "\t\tDelet Client Screen\n";
    cout << "____________________________________________________\n\n";
    string AccountNumber = ReadAccountNumber();
    vector<stReadinfo> vClients = LoadClientsDataFromFile(FileName);
    DeletCline(vClients, AccountNumber);
}

void UpdetInfoCline(vector<stReadinfo> &vClients, string AccountNumber)
{
    char Answer;
    if(PrintInfoAccoutNumber(vClients, AccountNumber))
    {
        cout << "\nAre ou sure you want to Update this clint y/n ? ";
        cin >> Answer;
        if(tolower(Answer) == 'y')
        {
        MarkForDeletedOrUpdate(vClients,AccountNumber);
        SaveCleintsDataToFileFromUpdate(FileName, vClients, AccountNumber);
        vClients = LoadClientsDataFromFile(FileName);
        cout << "Clinet Updated successflly. ";
        }
        return;
    }
}

void StrarUpdetInfoCline()
{
    cout << "____________________________________________________\n";
    cout << "\t\tUpdate Client Screen\n";
    cout << "____________________________________________________\n\n";
    string AccountNumber = ReadAccountNumber();
    vector<stReadinfo> vClients = LoadClientsDataFromFile(FileName);
    UpdetInfoCline(vClients, AccountNumber);
}

void showInfoOneClinte()
{
    cout << "____________________________________________________\n";
    cout << "\t\tFind Client Screen\n";
    cout << "____________________________________________________\n\n";
    string AccountNumber = ReadAccountNumber();
    vector<stReadinfo> vClients = LoadClientsDataFromFile(FileName);
    PrintInfoAccoutNumber(vClients, AccountNumber);
}
void EndProgram()
{
    cout << "____________________________________________________\n";
    cout << "\tProgram Ends :-)" << endl;
    cout << "____________________________________________________\n";
}
void BackToMenue()
{
    cout << "\nPress Enter to go back to Main Menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    StartProgram(UserChoise());
}
void StartProgram(enUserChoise UserChoise)
{
    system("clear");
    switch (UserChoise)
{
case enShowClientList:
    ShowInfoAllClinte();
    BackToMenue();
    break;

case enAddNewClient:
    AddNewClient();
    BackToMenue();
    break;

case enDeleteClient:
    StartDeletCline();
    BackToMenue();
    break;

case enUpdateClientInfo:
    StrarUpdetInfoCline();
    BackToMenue();
    break;

case enFindClient:
    showInfoOneClinte();
    BackToMenue();
    break;

default:
    EndProgram();
    break;
}
}

int main()
{
    StartProgram(UserChoise());
}
