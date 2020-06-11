/***********************************************************************
 * Program:
 *    Lab 06, Sanitization
 *    Brother Wilson, CSE 453
 * Author:
 *    Timothy Bohman
 *    Alex Johnson
 *    John Batty
 *    Abdias Baldiviezo Aguilar
 * Summary:
 *    Please include a detailed description of:
 *    1. What this program is designed to do
 *    2. How this program will go about solving the problem
 *    3. What assumptions about input (file or user) is made
 *    4. Citations if the algorithm was borrowed or inspired from any source
 ************************************************************************/

/***************
 * TODO
 *   - generateVulnerableSQL
 *   - generateWeakSQL
 *   - generateStrongSQL
 *   - Comment blocks for functions
 * *************/

/*******************
 * Example execution:
 *   ./a.exe myusername mypassword
 * *****************/

#include <iostream>
#include <string>
#include <algorithm>
#include <regex>
using namespace std;

#define DEBUG true
#define CLEAN_MODE true

void promptUser(string &, string &);
string generateVulnerableSQL(string, string); // TODO
string generateWeakSQL(string, string); // TODO
string generateStrongSQL(string, string); // TODO
void displayHeader(bool cool_mode = false);
void commentFeed();
void statementFeed();
void tautologyFeed();
void unionFeed();


/**********************************************************
 * Function:
 *   main(int argc, char *argv[])
 * Purpose:
 *   Provide entry to the program and drive the execution
 * Returns:
 *   int - status code
 **********************************************************/
int main(int argc, char *argv[])
{
    if (!CLEAN_MODE)
    {
        displayHeader();
    }

    string username = "";
    string password = "";
    bool areArgs = false;

    // Check for command line args
    if (argc > 1)
    {
        areArgs = true;
        username = argv[1];
        password = argv[2];

        if (DEBUG)
            cout << "\nexe args: " + username + " " + password + "\n";
    }
    else // if no command line args
    {
        if(areArgs == false) {
            int testSelection = 0;
            bool keep_going = true;
            bool keep_going_manual_test = true;
            int selection_manual_test = 0;
            
            while (keep_going)
            {
                cout << "\nWhat do you want to do?\n\n";
                cout << "  1  Tautology Attack Test Cases\n";
                cout << "  2  Union Attack Test Cases\n";
                cout << "  3  Comment Attack Test Cases\n";
                cout << "  4  Statement Attack Test Cases\n";
                cout << "  5  Manual Test\n";
                cout << "  6  Quit\n";

                cout << ">> ";
                cin >> testSelection;

                switch (testSelection)
                {
                case 1:
                    tautologyFeed();
                    break;
                case 2:
                    unionFeed();
                    break;
                case 3:
                    commentFeed();
                    break;
                case 4:
                    statementFeed();
                    break;
                case 5:
                    promptUser(username, password);

                    while (keep_going_manual_test)
                    {
                        cout << "\nWhat do you want to do?\n\n";
                        cout << "  1  Generate vulnerable SQL query\n";
                        cout << "  2  Generate SQL query with weak mitigation\n";
                        cout << "  3  Generate SQL query with strong mitigation\n";
                        cout << "  4  Quit\n";

                        cout << ">> ";
                        cin >> selection_manual_test;

                        switch (selection_manual_test)
                        {
                        case 1:
                            cout << "\nSQL statement: \n" << "  " + generateVulnerableSQL(username, password) << "\n";
                            break;
                        case 2:
                            cout << "\nSQL statement: \n" << "  " + generateWeakSQL(username, password) << "\n";
                            break;
                        case 3:
                            cout << "\nSQL statement: \n" << "  " + generateStrongSQL(username, password) << "\n";
                            break;
                        case 4:
                            keep_going_manual_test = false;
                            break;
                        default:
                            cout << "Please enter a selection between 1 and 3.\n\n";
                        }
                    }
                    break;
                case 6:
                    keep_going = false;
                    break;
                default:
                    cout << "Please enter a selection between 1 and 6.\n\n";
                }
            }
        }
    }
}

/**********************************************************
 * Function:
 *   generateVulnerableSQL(string username, string password)
 * Purpose:
 *   Generate an SQL statement vulnerable to SQL injection attacks.
 * Returns:
 *   string - for potential future purposes
 **********************************************************/
string generateVulnerableSQL(string username, string password)
{
    string SQL_statement = "SELECT * FROM Users WHERE username='" + username + 
        "' AND password='" + password +"'";
    
    //cout << "\nSQL statement: \n";
    //cout << "  " + SQL_statement + "\n";
    
    return SQL_statement;
}
/**********************************************************
 * Function:
 *   tautologyFeed()
 * Purpose:
 *   Feed Tautology Attacks tests cases into the generateVulnerableSQL()
 * Returns:
 *   void
 **********************************************************/
 void tautologyFeed(){
     int numTestCases = 5;
     string userTestCases[numTestCases] = {"james\' OR 1=1","sam\'","michael\' OR \'x\'=\'x","jim\' OR 1=1",
                                "pam\' OR \'a\'=\'a"};
     string pwdTestCases[numTestCases] = {"secret\' OR 1=1","passwort\' OR \'x\'=\'x","jelszó\' OR 1=1",
                                "parola \' OR \'a\'=\'a","contraseña\' OR id=1"};
     cout << "Tautology Attacks:\n";
     for (size_t i = 0; i < numTestCases; i++)
     {
         cout << "test case #" << i << '\n' 
         << "Vulnerable: " << generateVulnerableSQL(userTestCases[i], pwdTestCases[i]) << '\n'
         << "Weak Mitigation: " << generateWeakSQL(userTestCases[i], pwdTestCases[i]) << '\n'
         << "Strong Mitigation: " << generateStrongSQL(userTestCases[i], pwdTestCases[i]) << '\n' << '\n';
     } 
 }


/**********************************************************
 * Function:
 *   unionFeed()
 * Purpose:
 *   Feed Union Query Attacks tests cases into the generateVulnerableSQL()
 * Returns:
 *   void
 **********************************************************/
 void unionFeed(){
     int numTestCases = 5;
     string userTestCases[numTestCases] = { "admin\'",
                                            "aUser",
                                            "hello_world",
                                            "test@gmail.com",
                                            "sadams"};
     string pwdTestCases[numTestCases] = {"\' UNION SELECT * from Users",
                                             "doesnt matter\' UNION SELECT 1--",
                                            "something\' UNION ALL SELECT * from users WHERE username = \'admin\'",
                                            "81dc9bdb52d04dc20036dbd8313ed055\' UNION ALL SELECT password, username from users",
                                            "1=2\' union select 1,group_concat(username,0x3a,password),3,4 from user-- -"};
     cout << "Union Query Attacks:\n";
     for (size_t i = 0; i < numTestCases; i++)
     {
         cout << "test case #" << i << '\n' 
         << "Vulnerable: " << generateVulnerableSQL(userTestCases[i], pwdTestCases[i]) << '\n'
         << "Weak Mitigation: " << generateWeakSQL(userTestCases[i], pwdTestCases[i]) << '\n'
         << "Strong Mitigation: " << generateStrongSQL(userTestCases[i], pwdTestCases[i]) << '\n' << '\n';
     } 
 }


/**********************************************************
 * Function:
 *   statementFeed()
 * Purpose:
 *   Feed Statement Attacks tests cases into the generateVulnerableSQL()
 * Returns:
 *   void
 **********************************************************/
 void statementFeed(){
     int numTestCases = 5;
     string userTestCases[numTestCases] = {"adams","smith","hello123!","byuidaho","michael@yahoo.com"};
     string pwdTestCases[numTestCases] = {"1\'; DELETE FROM users WHERE 1=1","nothing\'; INSERT INTO users (name, passwd) VALUES \'Bob\', \'1234",
                                "WHERE id = \'username\' UNION SELECT Username, Password FROM users;",
                                "\'; SELECT * FROM users WHERE user_id = Username; DROP TABLE users",
                                "\'; SELECT * FROM users WHERE id = 0 OR 1=1"};
     cout << "Statement Attacks:\n";
     for (size_t i = 0; i < numTestCases; i++)
     {
         cout << "test case #" << i << '\n' 
         << "Vulnerable: " << generateVulnerableSQL(userTestCases[i], pwdTestCases[i]) << '\n'
         << "Weak Mitigation: " << generateWeakSQL(userTestCases[i], pwdTestCases[i]) << '\n'
         << "Strong Mitigation: " << generateStrongSQL(userTestCases[i], pwdTestCases[i]) << '\n' << '\n';
     } 
 }


/**********************************************************
 * Function:
 *   commentFeed()
 * Purpose:
 *   Feed Comment Attacks tests cases into the generateVulnerableSQL()
 * Returns:
 *   void
 **********************************************************/
 void commentFeed(){
     int numTestCases = 5;
     string userTestCases[numTestCases] = {"Root\'; --","\';shutdown --",
                                "DROP sampletable;--","DROP sampletable;#",
                                "admin'--"};
     string pwdTestCases[numTestCases] = {"secret","@##$$","gadams","secretpass!","smiths645"};
     cout << "Comment Attacks:\n";
     for (size_t i = 0; i < numTestCases; i++)
     {
         cout << "test case #" << i << '\n' 
         << "Vulnerable: " << generateVulnerableSQL(userTestCases[i], pwdTestCases[i]) << '\n'
         << "Weak Mitigation: " << generateWeakSQL(userTestCases[i], pwdTestCases[i]) << '\n'
         << "Strong Mitigation: " << generateStrongSQL(userTestCases[i], pwdTestCases[i]) << '\n' << '\n';
    } 
 }


/**********************************************************
 * Function:
 *   replaceAll(std::string& str, const std::string& from, const std::string& to)
 * Purpose:
 *   Replaces illegal characters with escaped characters
 * Returns:
 *   void
 **********************************************************/
void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}


/**********************************************************
 * Function:
 *   generateWeakSQL(string username, string password)
 * Purpose:
 *   Generate an SQL statement using weak mitigation techniques
 * Returns:
 *   string - for potential future purposes
 **********************************************************/
string generateWeakSQL(string username, string password)
{
    username = username.substr(0, username.find(";"));
    password = password.substr(0, password.find(";"));

    username = username.substr(0, username.find("\""));
    password = password.substr(0, password.find("\""));

    replaceAll(username, "\'", "\'\'");
    replaceAll(password,  "\'", "\'\'");    

    string SQL_statement = "SELECT * FROM Users WHERE username='" + username + 
        "' AND password='" + password +"'";
    
    return SQL_statement;
}

/**********************************************************
 * Function
 *   generateStrongSQL(string username, string password)
 * Purpose:
 *   Generate an SQL statement using strong mitigation techniques
 * Returns:
 *   string - for potential future purposes
 **********************************************************/
string generateStrongSQL(string username, string password)
{
    
    regex usernameWhitelist("[^ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890@\\.]");
    regex pwdWhitelist("[^ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890 `~!@#%&\\-=_\\^\\$\\.\\|\\?\\*\\+\\(\\)\\{\\}<>\\.,]");
    
    
    stringstream usernameResult;
    stringstream passwordResult;
    regex_replace(ostream_iterator<char>(usernameResult), username.begin(), username.end(), usernameWhitelist, "");
    regex_replace(ostream_iterator<char>(passwordResult), password.begin(), password.end(), pwdWhitelist, "");

    string SQL_statement = "SELECT * FROM Users WHERE username='" + usernameResult.str() + 
        "' AND password='" + passwordResult.str() +"'";
    
    return SQL_statement;
}

/**********************************************************
 * Function:
 *   promptUser(string &username, string &password)
 * Purpose:
 *   Get a username and password from the user if no command line
 *   arguments were provided
 * Returns:
 *   string - for potential future purposes
 **********************************************************/
void promptUser(string &username, string &password)
{
    string temp_username = "";
    string temp_password = "";

    cout << "\nPlease enter a username and password to create an SQL query.\n\n";
    cout << ">> Username: ";
    cin >> temp_username;

    cout << ">> Password: ";
    cin.ignore();
    getline(cin, temp_password);

    if (DEBUG)
    {
        cout << "User provided info: " + temp_username + " " + temp_password + "\n";
    }

    username = temp_username;
    password = temp_password;

    return;
}

void displayHeader(bool cool_mode)
{
    if (cool_mode)
    {
        cout << " _           _       _____  ____\n";
        cout << "| |         | |     |  _  |/ ___|\n";
        cout << "| |     __ _| |__   | |/' / /___ \n";
        cout << "| |    / _` | '_ \\  |  /| | ___ \\\n";
        cout << "| |___| (_| | |_) | \\ |_/ / \\_/ |\n";
        cout << "\\_____/\\__,_|_.__/   \\___/\\_____/\n";
    }

    cout << "\nLab 06 - Sanitization\n";
    cout << "  Timothy Bohman\n";
    cout << "  John Batty\n";
    cout << "  Abdias Baldiviezo\n";
    cout << "  Alex Johnson\n";

    return;
}