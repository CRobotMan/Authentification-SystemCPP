#include <iostream>																					/// Input/Output functions library.
#include <string>																					/// String operations library.
#include <stdio.h>                                        ///standard Input Output library like in C
#include <ctype.h>                              
//we love to code, thats our passion
// Excellent.  
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;

///////////////////// Function prototypes /////////////////////
void Menu_AddUser();																				/// Function for adding a new user.
void Menu_EditUser();																				/// Function for editing a currently existant user.
void Menu_DeleteUser();																				/// Function for deleteing a user.
void Menu_ListAllUsers();																			/// Function for listing all of the users on screen.
void Menu_Login();																					/// Function for logging in to an existing account.
bool Ask_Quit();																					/// Function for verifying exit by asking confirmation.
int Check_LegitPassword(string pswrd);


int FindUserByID(string userName);																	/// Helper function for finding a user based on its username and returnring the ID. On failure, return -1.

int Ask_Authentication(int user_ID);																/// Helper function for asking authentication from the user when required to enter a password.
///////////////////////////////////////////////////////////////

class client																						/// Encapsulates all of the information required for our Client object.
{
	public:																							/// Public accessor.
		int ID;																					    /// The ID of the client. (Program-Based)
		
		void setUsername(string userName)															/// Setter for Username property.
		{
			this->username = userName;																/// Set this object's username to the name given within this function.
		}
		string getUsername()																		/// Getter for username property.
		{
			return this->username;																	/// Return this client's username.
		}
		
		void setPassword(string passWord)															/// Seter for Password property.
		{
			this->password = passWord;																/// Set this object's password to the password given within this function.
		}
		string getPassword()																		/// Getter for password property.
		{
			return this->password;																	/// Return this client's password.
		}
		
	private:																						/// Private accessor.
		string username;																			/// Variable that keeps our username.
		string password;																			/// Variable that keeps our password.
};

const int MAX_USERS = 1000;																			/// Defines the maximum number of users allowed.
client *Users[1000];																				/// Main array for storing all of our user's data.

int main(int argc, char** argv) {																	/// MAIN PROGRAM ENTRY POINT.
	
	while(true)																						/// Infinite loop until we break it.
	{
		system("CLS");																				/// Clear console's screen.
		
		cout << "******************************" << endl;											/// [Decorations]
		cout << "     Rome Rez productions" << endl;												/// [Decorations]
		cout << "******************************" << endl << endl;									/// [Decorations]
		cout << "TIP: Type \"XXX\" at any time to get one level back!" << endl << endl;				/// [Tip on how to exit a process]
		
		cout << "What would you like me to do?" << endl << "(G: Login | N: Add new user | E: Edit user | D: Delete user | L: List all users | X: Exit)\t";
																									/// Main menu entry.
		
		char response;																				/// Variable for receiving a response.
		cin >> response;																			/// Inputs the response from the user into our char variable.
		
		switch(response)																			/// Switch case for response.
		{
			case 'n':
			case 'N':
				Menu_AddUser();																		/// If 'N' character is entered, add a new user.
				break;
			case 'e':
			case 'E':
				Menu_EditUser();																	/// If 'E' character is entered, edit a user.
				break;
			case 'd':
			case 'D':
				Menu_DeleteUser();																	/// If 'N' character is entered, delete a user.
				break;
			case 'l':
			case 'L':
				Menu_ListAllUsers();																/// If 'L' character is entered, list all users.
				break;
			case 'g':
			case 'G':
				Menu_Login();																		/// If 'G' character is entered, ask for login information.
				break;
			case 'x':
			case 'X':
			default:
				if(Ask_Quit()) 
        {
          return 0;
        }
				break;
		}
	}
		
	return 0;																						/// Exit code (0) for our app.
}

void Menu_AddUser()																					/// Function body for adding a new user to our list.
{	
	while(true)
	{
		string input;																					/// Local variable for inputting user's response when necessary.
		
	beginning:																							/// Label tag for recursing the whole function.
		
		system("CLS");																					/// Clear console's screen.
		cout << "-------------------- ADD NEW USER --------------------\n\n" << "Enter a new Username:\t";
																										/// Asking the user to enter a new username.
		cin >> input;																					/// Input the user's response to our string variable.
		string temp_Username = input;																	/// Assign our input to our temporary username variable.
		
		if(temp_Username  == "XXX") 
    {
      break;
    }
    
		bool isIdentical = (FindUserByID(temp_Username) >= 0);											/// A condition to check whether a previously created user with that username exists or not.
		if(isIdentical)																					// If found...
		{
			cout << "\n\nERROR:  A username with that name already exists!\nPlease choose a different one.\n\n\n";
																										/// Tell the user to change the input username.
			system("PAUSE");																			/// Wait for ENTER key...
			goto beginning;																				/// Jump to the beginning of this function. (the beginning: label.)
		}
		
    int special_Check;
    string temp_Password;
    while(true)
    {
		  cout << "Please enter your new password:\t";													/// Else if everything went fine, let's ask a new password from our user.
		  cin >> input;																					/// Input that password.
		  temp_Password = input;																/// Assign our input to our temporary password variable.   
    
      special_Check = Check_LegitPassword(temp_Password);
      if(special_Check == 0)
      {
        continue;
      }
      else
      {
        break;
      }
    }
    
    if(special_Check == -1)
    {
      break;
    }
		
																										/// Check if there is a space availabe for a new user or not.
		int i;																							/// Remember the first free index in our array.
		bool foundSpace = false;																		/// A flag to set to true when we have found a free space in our array.
		for(i = 0; i < MAX_USERS; i++)																	/// Traverse through our array of users.
		{
			if(Users[i] == NULL) 																		/// Check if this index is free...
			{
				foundSpace = true;																		/// If it was, set the flag to true.
				break;																					/// There is no need to find another space, so break the loop.
			}
		}
		
		system("CLS");																					/// Clear console's screen.
		
		if(foundSpace)																					/// If we have found a new space...
		{
			Users[i] = new client();																	/// Then allocate free memomry for the index we have found.
			
			Users[i]->ID = i + 1;																		/// Set the one-based ID.
			Users[i]->setUsername(temp_Username);														/// Set the username.
			Users[i]->setPassword(temp_Password);														/// Set the password.
			
			cout << "Successfully created a new user with ID: " << Users[i]->ID << " ! Welcome back, " << Users[i]->getUsername() << "\n\n\n";
																										/// Return new user data using the object we have created for verification.
			system("PAUSE");																			/// Wait for ENTER key...
		}
		else																							/// Otherwise, if no free space was found...
		{
			cout << "ERROR! No more spaces left!\nTry deleting a user and try again.\n\n\n" ;			/// Then print the error to the screen...
			system("PAUSE");																			/// And wait for ENTER key...
		}
	}
}

void Menu_EditUser()																				/// Function body for editing an existing user.
{
	bool exit = false;																				/// A flag that is set to true when we want to get back to our main menu.
	
	while(!exit)																					/// Inifinite loop until exit is set to true.
	{	
		string temp_Username;																		/// Variable for storing the username we are looking for.
		system("CLS");																				/// Clear console's screen.
		cout << "-------------------- EDIT USER --------------------\n\n";							/// Title.
		cout << "Please enter your username:\t";													/// Ask the user to enter his/her username.
		cin >> temp_Username;																		/// Input the username into our temp variable.
		
    // Continue loop comes here and waits for person input automatically.
		if(temp_Username == "XXX") break;                       /// If we have entered XXX as a username, then break the loop immediately and get back to main menu.
		
		int userIndex = FindUserByID(temp_Username);												/// Get the ID of the user to look it up in our array.
		if(userIndex < 0)																			/// If this user with such username didn't exist...
		{
			cout << "User not found! Try again!\n\n";												/// Then print the error.
      
			system("PAUSE");																		/// Wait for ENTER key...
			continue;		                                  /// Go to the next iteration of our while loop.
		}
		else																						/// Else if we successfully found our user data,
		{
			while(true)																				/// Wait until the user enters the correct password.
			{
				int auth_Result = Ask_Authentication(userIndex);   /// Ask for authentication returns a result. -1 if the user has entered XXX and doesn't want to enter a password, 0 for wrong password, and 1 for true password. (0 = false and 1 = true).
				if(auth_Result == -1) { exit = true; break; }     /// If the user had entered "XXX", then exit the infinite loop.
				else if(auth_Result == true) { break; }           /// If the user had entered the true password, exit this infinite loop and jump to the next section of the code below ;)
			}
			
			while(!exit)																			/// Infinite loop until we want to exit.
			{
			redo_While:
				system("CLS");																		/// Clear console's screen.
				cout << "-------------------- EDIT USER --------------------\n\n";					/// Title.
				cout << "User found at index: " << Users[userIndex]->ID << "." << endl;				/// Tell the user's ID.
				cout << "Current Username:" << Users[userIndex]->getUsername() << endl;				/// Print our current username.
				cout << endl;																		/// Print a line terminator (0x0D)
				
				char input;																			/// Temporary input character for the menu.
				cout << "Which property would you like to edit? (U = Username / P = Password / X = Return to main menu):    ";
																									/// Ask the user which property does he/she want to change?
				cin >> input;																		/// Get the response from the user.
				switch(input)																		/// Decide which property to change.
				{
					case 'x':
					case 'X':																		/// On 'X' character,
						exit = true;																/// Exit to main menu.
						break;
						
					case 'u':
					case 'U':																		/// On 'U' character,
					{
						system("CLS");																/// Clear console's screen.
						string newUsername;															/// Temporary new username variable.
						cout << "Please enter the new username:    ";								/// Ask the user to enter the new username.
						cin >> newUsername;															/// Input the response to our temporary variable.
						if(newUsername == "XXX") goto redo_While;
						Users[userIndex]->setUsername(newUsername);									/// Set the user's username to the new string.
						cout << "\n\n\n";															/// Print out some line terminators.
						system("PAUSE");															/// Wait for ENTER key...
						break; 
					}
						
					case 'p':
					case 'P':																		/// On 'P' character,
					{
						system("CLS");	                          /// Clear console's screen.
            
            string newPassword;                    										/// Temporary new password variable.
            
            while(true)
            {
						  cout << "Please enter the new password:    ";								/// Ask the user to enter the new password.
						  cin >> newPassword;                    										/// Input the response to our temporary variable.
            
              if(newPassword == "XXX") goto redo_While;
            
              int special_Check;

            
              special_Check = Check_LegitPassword(newPassword);
              if(special_Check == 0)
              {
                continue;
              }
              else
              {
                break;
              }
            }
            
						Users[userIndex]->setPassword(newPassword);									/// Set the user's password to the new string.
						cout << "\n\n\n";                      										/// Print out some line terminators
						system("PAUSE");                                 							/// Wait for ENTER key...
						break;
					}
					
					default:																		/// Other than that,
							exit = true;															/// Exit to main menu.
							break;
				}
			}
		}
	}
}

void Menu_DeleteUser()																				/// Function body to remove the user from our array.
{
	bool exitToMain = false;
  string delUsername;
  int findResult;
  char confirmation;
  
  while(!exitToMain)
  {
    system("CLS");
    
    cout << "-------------- !!! DELETE A USER !!! --------------" << endl << endl;
    cout << "Which Account would you like to delete? Please insert the name: " << endl;
    cin >> delUsername;
    
    if(delUsername == "XXX")
    {
      exitToMain = true;
      break;
    }
    
    findResult = FindUserByID(delUsername);
    
    if(findResult < 0)
    {
      cout << "Accountname doesn't exist!" << endl;
      system("PAUSE");
      continue;
    }
    
    bool auth_OK;
    
    while(true)																				/// Wait until the user enters the correct password.
			{
				int auth_Result = Ask_Authentication(findResult);   /// Ask for authentication returns a result. -1 if the user has entered XXX and doesn't want to enter a password, 0 for wrong password, and 1 for true password. (0 = false and 1 = true).
				if(auth_Result == -1) 
        { 
          auth_OK = false;
          break;
        }     /// If the user had entered "XXX", then exit the infinite loop.
				else if(auth_Result == true) 
        { 
          auth_OK = true;
          break; 
        }           /// If the user had entered the true password, exit this infinite loop and jump to the next section of the code below ;)
			}
    if(auth_OK == false)
    {
      continue;
    }
    /////////////////////////////////////////////////// 4th session : 29 / 7 / 2020 ///////////////////////////////////////////////
    system("CLS");
    
    cout << "Are you sure you want to delete user with these properties?" << endl;
    
    cout <<"User ID:" << Users[findResult]->ID << endl;
    cout <<"Username:" <<Users[findResult]->getUsername() << endl;
    
    cout << "Y:Yes | N:No\t" << endl;
    cin >> confirmation;
    
    switch(confirmation)
    {
       case 'Y':
       case 'y':
       {
         // In this part of the code, we need to use the delete operator to delete a member from our array stored in RAM.
         delete Users[findResult];
         Users[findResult] = NULL;
         
         cout << "-----------Account deleted-----------" << endl;
         
         system("PAUSE");
         break;
         
       }
      case 'n':
      case 'N':
        {
          cout << "-----------Operation cancelled-----------" << endl;
          
          system("PAUSE");
          continue; 
          
          break;   
        }
    }
  }
}

void Menu_ListAllUsers()																			/// Function body to list all of the registered users on screen.
{
	while(1)
  {
    system("CLS");
       
    cout <<  "List of all users are as follows: " << endl << endl;
    
    int userCount = 0;
    for(int i=0; i<MAX_USERS; i++)
    {
      if(Users[i] == NULL) continue;
      
      cout << "[User Info]" << endl;
      cout << "User ID:      " << Users[i]->ID << endl;
      cout << "Username:     " << Users[i]->getUsername() << endl;
      cout << "[End User Info]" << endl << endl;
      
      userCount++;
    }
    
    cout << endl << "*****************************" << endl << endl;
    
    cout << "Maximum Accountspaces: " << MAX_USERS << endl;
    cout << "Number of Accounts used " << userCount << endl;
    cout << "Free Accountspaces " << MAX_USERS - userCount << endl;
    
    cout << endl << endl;
    system("PAUSE");
    break;
  }
}

void Menu_Login()																					/// Function body for the user to log in to his/her account.
{
	
}

bool Ask_Quit()																						/// Function for verifying exitting the program.
{
	char shut_down;
  system("CLS");
  
  cout << "Are you sure you want to exit the program?(Y=Yes | N=No):\t" << endl;
  cin >> shut_down;
  
  
  if(shut_down == 'Y' || shut_down == 'y')
  {
    return true;
  }
  else
  {
    return false;
  }
  
}

int FindUserByID(string userName)																	/// Helper function body for finding a user based on its username and returning its ID.
{
	int index;																						/// An integer variable to remember the index we have found.
	bool foundIndice = false;																		/// A boolean value to indicate whether we have found a user based on the given username.
	
	for(index = 0; index < MAX_USERS; index++ )														/// A for-loop for traversing through each item of the array.
	{
		if(Users[index] == NULL) continue;															/// IMPORTANT: If the current user has not yet been assigned and if it's a dangling pointer, continue to the next iteration of the for-loop.
		
		if(Users[index]->getUsername() == userName)													/// Otherwise, if current username given matches the current user's data,
		{
			foundIndice = true;																		/// Set the found indice flag to true.
			break;																					/// And break the loop, since there is no use in searching the rest of the array.
		}
	}
	
	if(foundIndice)																					/// At the end, check if we have found a real user or not.
		return index;																				/// If found, return the index of the user.
	else
		return -1;																					/// But if not, return -1. (So we can check whether we succeded in finding a real user or not.)
}

int Ask_Authentication(int user_ID)																	/// Helper function for asking the user to enter the password.
{
	string pswrd;																					/// A temp string for asking the password.
	cout << "\nAuthentication required!\nPlease enter password for user:  \" " << Users[user_ID]->getUsername() << " \" :\t";
																									/// Request the user to enter his/her password.
	cin >> pswrd;																					/// Input the password to our string variable.
	
	if(pswrd == "XXX") return -1;
	
	if(Users[user_ID]->getPassword() == pswrd) return true;											/// Check if the entered string mathes the user's password. If yes, return true.
	else 																							/// Otherwise...
	{
		cout << "\nWrong password entered! Please try again!";										/// Tell the user that he/she has entered the wrong password.
		return false;																				/// Return false.
	}
}

int Check_LegitPassword(string pswrd)
{
  string myPswrd = pswrd;
  
  int pswrd_Length = myPswrd.length();
  bool found_SpecialSign = false;
  bool found_Lower = false;
  bool found_Upper = false;
  bool found_Num = false;
  
  if(myPswrd == "xxx" || myPswrd == "XXX")
  {
    return -1;
  }
  
  if(pswrd_Length<9)
  {
    cout << "---------------" << endl;
    cout << "Your password must at least have the length of 9 letters." << endl << "---------------" << endl;
    
    system("PAUSE");
    return 0;
  }  
  
  for(int i=0; i<pswrd_Length; i++)
  {
    char temp_specSign = myPswrd[i];
    
    if(temp_specSign == '!' || temp_specSign == '@' || temp_specSign == '+' || temp_specSign == '-' || temp_specSign == '§' ||                temp_specSign == '!' || temp_specSign == '$' || temp_specSign == '%' || temp_specSign == '/' || temp_specSign == '(' ||                temp_specSign   == ')' || temp_specSign == '=' || temp_specSign == '?' || temp_specSign == '{' || temp_specSign == '}' ||              temp_specSign == '[' ||       temp_specSign == ']' || temp_specSign == 'ß' || temp_specSign == '*' || temp_specSign == '&' ||          temp_specSign == '^' || temp_specSign     == '\\')
    {
      found_SpecialSign = true;
    }
    
    if(temp_specSign >= 65 && temp_specSign <= 90 )
    {
      found_Upper = true;
    }
    
    if(temp_specSign >= 97 && temp_specSign <= 122 )
    {
      found_Lower = true;
    }
    if(temp_specSign >= 48 && temp_specSign <= 57 )
    {
      found_Num = true;
    }
  }
  
  if(found_SpecialSign == false)
  {
    cout << endl << "No special signs were found. Your password must at least contain one special letter." << endl;
    system("PAUSE");
    return 0;
  }
  
  if(found_Lower == false)
  {
    cout << endl << "No lower letters were found. Your password must at least contain one lower letter." << endl;
    system("PAUSE");
    return 0;
  }
  
  if(found_Upper == false)
  {
    cout << endl << "No capital letters were found. Your password must at least contain one capital letter." << endl;
    system("PAUSE");
    return 0;
  }
  
  if(found_Num == false)
  {
    cout << endl << "No numbers were found. Your password must at least contain one number." << endl;
    system("PAUSE");
    return 0;
  }
  
  return 1;
}


