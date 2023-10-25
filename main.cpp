#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

struct Person {
    int id;
    string firstName, lastName, emailAdress, adress, phoneNumber;
};
struct User {
    int id;
    string login, password;
};
void showPerson(Person person) {
    cout<<setw(30)<< left<<"1.ID: " << person.id << endl;
    cout<<setw(30)<< left<<"2.Imie: " <<person.firstName << endl;
    cout<<setw(30)<< left<<"3.Nazwisko: "<<person.lastName << endl;
    cout<<setw(30)<< left<<"4.Numer telefonu: " <<person.phoneNumber << endl;
    cout<<setw(30)<< left<<"5.Adres email: " <<person.emailAdress << endl;
    cout<<setw(30)<< left<<"6.Adres: " <<person.adress << endl << endl;
}
string loadText() {
    string result = "";
    cin.sync();
    getline(cin, result);

    return result;
}
int readInt() {
    int number;
    string input;
    while(true) {
        input = loadText();
        stringstream myStream(input);
        if(myStream >> number) {
            break;
        }
        cout << "To nie numer, spronuj ponownie" << endl;
    }
    return number;
}
char loadChar() {
    string input = "";
    char sign  = {0};
    cin.sync();
    while (true) {
        getline(cin, input);

        if (input.length() == 1) {
            sign = input[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
    }
    return sign;
}
void saveDataToFile(vector <Person> persons) {
    ofstream file;
    file.open("ksiazkaAdresowa.txt", ios::out);

    if(!file) {
        cout << "Nie udalo sie otworzyc pliku:";
        Sleep(1000);
    } else {
        for(Person person:persons) {
            file << person.id << "|";
            file << person.firstName << "|";
            file << person.lastName << "|";
            file << person.phoneNumber << "|";
            file << person.emailAdress << "|";
            file << person.adress << "|" ;
            file <<endl;
        }
    }
    file.close();
}
void addFriend(vector <Person> &persons, int userIdLogged ) {
    Person person;
    if (persons.size() == 0) {
        person.id =  1;
    } else {
        person.id = persons[persons.size() - 1].id + 1;
    }
    cout << "Podaj imie:  "<< endl;
    person.firstName = loadText();
    cout << "Podaj nazwisko:  "<< endl;
    person.lastName = loadText();
    cout << "Podaj numer telefonu:  "<< endl;
    person.phoneNumber = loadText();
    cout << "Podaj email:  "<< endl;
    person.emailAdress = loadText();
    cout << "Podaj swoj adres:  "<< endl;
    person.adress = loadText();
    persons.push_back(person);
    cout << endl << "Kontakt dodany pomyslnie" ;
    Sleep(1000);

    ofstream file;
    file.open("ksiazkaAdresowa.txt",ios::out | ios::app);

    if ( file.good() == true) {
        file << person.id << "|";
        file << userIdLogged << "|";
        file << person.firstName << "|";
        file << person.lastName << "|";
        file << person.phoneNumber << "|";
        file << person.emailAdress << "|";
        file << person.adress << "|" ;
        file <<endl;
        file.close();
    } else {
        cout << "Nie udalo sie otworzyc pliku";
        system("pause");
    }
}
void showFriends(vector <Person> &persons) {
    system("cls");
    if(persons.empty()) {
        cout << "Ksiazka adresowa jest pusta"<<endl;
    } else {
        for(Person person : persons) {
            showPerson(person);
        }
    }
    system("pause");
}
void searchByFirstName(vector <Person> &persons) {
    int found = 0;
    string name;
    if(persons.empty()) {
        cout << "Ksiazka adresowa jest pusta" << endl;
    } else {
        cout << "Podaj imie znajomego ktorego chcesz wyszukac: "<<endl;
        name = loadText();

        for(size_t i = 0; i < persons.size() ; i++) {
            if(persons[ i ].firstName == name ) {
                showPerson(persons[i]);
                found ++;
            }
        }
        if (found == 0)cout << "Nie znaleziono nikogo o imieniu " << name << endl;
    }
    system("pause");
}
void searchByLastName(vector <Person> &persons) {
    int found = 0;
    string name;
    if(persons.empty()) {
        cout << "Ksiazka adresowa jest pusta" << endl;
    } else {
        cout << "Podaj nazwisko znajomego ktorego chcesz wyszukac: "<<endl;
        name = loadText();

        for(size_t i = 0; i < persons.size() ; i++) {
            if(persons[ i ].lastName == name ) {
                showPerson(persons[i]);
                found ++;
            }
        }
        if ( found == 0)cout << "Nie znaleziono nikogo o nazwisku " <<name << endl;
    }
    system("pause");
}
vector <Person> loadFromFile(  ) {
    vector <Person> persons;
    Person person;
    string line;
    ifstream file;
    file.open("ksiazkaAdresowa.txt",ios::in);

    if (!file.good()) {
        return persons;
    } else {
        while(getline(file, line)) {
            string text = "";
            string texts[6];
            int counter = 0;
            int counter2 = 0;
            for(size_t i = 0 ; i < line.length() ; i++) {
                if(line[i] == '|') {
                    texts[counter2] = text;
                    counter2++;
                    text = "";
                    counter = i +1;
                    continue;
                }
                text += line[counter];
                counter++;
            }
            person.id = atoi(texts[0].c_str());
            person.firstName = texts[1];
            person.lastName = texts[2];
            person.phoneNumber = texts[3];
            person.emailAdress = texts[4];
            person.adress = texts[5];
            persons.push_back(person);
        }
    }
    file.close();

    return persons ;
}

int searchPersonByID(vector <Person> &persons, int idToSearch) {
    int searchedPersonId = -1;
    for(size_t i = 0 ; i < persons.size() ; i++) {
        if(idToSearch == persons[i].id) {
            searchedPersonId = i;
            break;
        }
    }
    return searchedPersonId;
}
void modifyPersonData(vector <Person> &persons) {
    int id;
    int indexToChange;
    char choice = 't';
    string dataToChange;
    system("cls");
    if(persons.empty()) {
        cout <<"Ksiazka adresowa jest pusta" << endl;

    } else {
        cout <<"Podaj numer ID uzytkownika, ktorego chcesz zmienic dane: ";
        id = readInt();
        indexToChange = searchPersonByID(persons, id);
        while(indexToChange == -1) {
            cout << "Podales nieistniejacy id, sprobuj ponownie: ";
            id = readInt();
            indexToChange = searchPersonByID(persons, id);
        }
        while(choice == 't') {
            cout << "Ktory parametr chcesz zmienic?" << endl;
            cout << "1 - Imie: "<< persons[indexToChange].firstName << endl;
            cout << "2 - Nazwisko: "<< persons[indexToChange].lastName << endl;
            cout << "3 - Numer telefonu: "<< persons[indexToChange].phoneNumber << endl;
            cout << "4 - Adres email: "<< persons[indexToChange].emailAdress << endl;
            cout << "5 - Adres: "<< persons[indexToChange].adress << endl ;
            cout << "6 - Powrot do menu" << endl;
            cin.sync();
            choice = loadChar();

            switch(choice) {
            case '1': {
                cout << "Podaj nowe imie: " << endl;
                persons[indexToChange].firstName = loadText();;
                cout << "Dane zmieniono pomyslnie" << endl;
                system("pause");
            }
            break;
            case '2': {
                cout << "Podaj nowe nazwisko: " << endl;
                dataToChange = loadText();
                persons[indexToChange].lastName = dataToChange;
                cout << "Dane zmieniono pomyslnie" <<endl;
                system("pause");
            }
            break;
            case '3': {
                cout << "Podaj nowy numer telefonu: " << endl;
                dataToChange = loadText();
                persons[indexToChange].phoneNumber = dataToChange;
                cout << "Dane zmieniono pomyslnie" << endl;
                system("pause");
            }
            break;
            case '4': {
                cout << "Podaj nowy adres email: " << endl;
                dataToChange = loadText();
                persons[indexToChange].emailAdress = dataToChange;
                cout << "Dane zmieniono pomyslnie" <<endl ;
                system("pause");
            }

            case '5': {
                cout << "Podaj nowy adres: " << endl;
                dataToChange = loadText();
                persons[indexToChange].adress = dataToChange;
                cout << "Dane zmieniono pomyslnie";
                system("pause");
            }
            break;
            case '6': {
                return;
            }
            break;
            default: {
                cout << "Zly wybor";
            }
            }
            saveDataToFile(persons);
            cout << endl << "Chcesz jeszcze cos edytowac? t/n" <<endl;
            choice = loadChar();
            choice = tolower(choice);
            system("cls");
        }
    }
    system("pause");
}
void deletePerson(vector <Person> &persons) {
    int id;
    char confirm;
    int indexPersonToDelete;
    if(persons.empty()) {
        cout << "Ksiazka adresowa jest pusta" << endl;
    } else {
        system("cls");
        cout << "Podaj id uzytkownika ktorego chcesz usunac: ";
        id = readInt();
        indexPersonToDelete = searchPersonByID(persons, id);
        while(indexPersonToDelete == -1) {
            cout << "Podales niewlasciwy id, sprobuj ponownie ";
            id = readInt();
            indexPersonToDelete = searchPersonByID(persons, id);
        }
        cout << "Jestes pewny ze chcesz usunac uzytkownika? t/n" << endl <<endl;
        showPerson(persons[indexPersonToDelete]);
        cout << endl;
        confirm = loadChar();
        confirm = tolower(confirm);
        if(confirm == 't') {
            persons.erase(persons.begin() + indexPersonToDelete);
            cout << "uzytkownik usuniety" << endl;
            saveDataToFile(persons);
        } else {
            cout << "uzytkownik nie zostal usuniety" << endl;
        }
    }
    system("pause");
}
void menu(int userIdLogged) {
    vector <Person> persons;
    char choice;
    persons = loadFromFile();

    while(1) {
        system("cls");
        cout<<"<<<<<Ksiazka adresowa>>>>>"<<endl;
        cout<<"1. Dodaj adresata"<<endl;
        cout<<"2. Wyszukaj po imieniu"<<endl;
        cout<<"3. Wyszukaj po nazwisku"<<endl;
        cout <<"4. Wyswietl wszystkich adresatow" << endl;
        cout <<"5. Usun adresata" << endl;
        cout<<"6. Edytuj adresata"<<endl;
        cout<<"7. Zakoncz program"<<endl;
        choice = loadChar();
        switch (choice) {
        case '1':
            addFriend(persons,userIdLogged);
            break;
        case '2':
            searchByFirstName(persons );
            break;
        case '3':
            searchByLastName(persons );
            break;
        case '4':
            showFriends(persons );
            break;
        case '5':
            deletePerson(persons );
            break;
        case '6':
            modifyPersonData(persons);
            break;
        case '7':
            exit(0);
            break;
        default:
            cout<<"Zly przycisk";
            Sleep(1000);
        }

    }

}
void loadUsersFromFile(vector <User> &users) {
    ifstream file;
    string line;
    User user;
    file.open("uzytkownicy.txt", ios::in);
    if(!file) {
        cout << "nie udalo sie otwowrzyc pliku";
    } else {
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            if (getline(ss, token, '|')) {
                user.id = stoi(token);
            }
            if (getline(ss, token, '|')) {
                user.login = token;
            }
            if (getline(ss, token, '|')) {
                user.password = token;
            }
            users.push_back(user);
        }
    }
}
int checkLoginData(vector <User> &users,User &userToCheck) {
    int userIdToLogin = 0;
    for(User user :users) {
        if(user.login == userToCheck.login &&user.password == userToCheck.password){userIdToLogin = user.id;}
    }
    return userIdToLogin;
}
void loginUser(vector <User> &users) {
    User user;
    system("cls");
    cout << setw(30) <<">>>>LOGOWANIE<<<<" << endl;
    cout << string(50, '~') << endl;
    cout << "Podaj login: " ;
    user.login = loadText();
    cout << "Podaj haslo: ";
    user.password  = loadText();
    int userId = checkLoginData(users,user);
    if(userId) {
        menu(userId);
    } else {
        cout << "Nieprawidlowe haslo albo login";
        Sleep(1500);
    }
}
void saveUserToFile(vector <User> &users) {
    ofstream file;

    file.open("uzytkownicy.txt", ios::out);

    if(!file) {
        cout << "nie udalo sie otworzyc pliku" ;
        Sleep(2000);
    } else {
        for(User user : users) {
            file << user.id << "|" << user.login << "|" << user.password << "|" <<endl;
        }
    }
    file.close();
}
void registartion(vector <User> &users) {
    User user;
    system("cls");
    if(users.empty()) {
        user.id = 1;
    } else {
        user.id = users.back().id +1;
    }
    cout << "Podaj login: ";
    user.login = loadText();;
    cout << endl << "Podaj haslo: ";
    user.password  = loadText();;
    Sleep(500);
    cout << endl<< "Rejestracja zakonczona sukcesem";
    Sleep(1000);
    system("cls");
    users.push_back(user);
    saveUserToFile(users);
}
void mainMenu() {
    vector <User> users;
    loadUsersFromFile(users);
    char choice;
    while(2) {
        system("cls");
        cout <<setw(30) <<"<<<< MENU GLOWNE >>>>"<<endl;
        cout << string(50, '-') <<endl;
        cout << "1.Rejestracja" << endl;
        cout << "2.Logowanie" << endl;
        cout<< "3.Wyjscie" << endl;
        cout << string(50, '-') <<endl;
        cout << "Twoj wybor: ";
        cin >>choice;
        switch(choice) {
        case '1':
            registartion(users);
            break;
        case '2':
            loginUser(users);
            break;
        case '3':
            exit(0);
            break;
        default:
            cout << "Zly przycisk, sprobuj ponownie";
        }
    }
}
int main() {
    //menu()
    mainMenu();

    return 0;
}