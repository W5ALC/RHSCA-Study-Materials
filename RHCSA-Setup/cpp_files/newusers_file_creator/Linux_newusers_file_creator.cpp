//*********************************************************************************************************************
// Linux Newusers File Creator: creates a file needed to batch add users with Linux "newusers" command.               *
// Each line in output file holds data for 1 user.                                                                    *
// Author: Rex Djere.                                                                                                 *
// © 2018-Present, Rex Djere.                                                                                         *
// License: GPL version 3 or later.                                                                                   *
// Requirements: C++ 11 or later.                                                                                     *
// Version: Friday 08/17/18 08:11:41 PM                                                                               *
// Generate version: date '+%A %D %X'                                                                                 *
//*********************************************************************************************************************

// output line format: <Username>:<Password>:<UID>:<GID>:<User Info>:<Home Directory>:<Default Shell>

// library header files
#include <iostream>
#include <random> // provides random numbers
#include <chrono> // provides date functions
#include <ctime> //  provides time functions
#include <string>
#include <algorithm> // provides transform functions
#include <fstream>
#include <sstream> // provides stringstream
#include <iomanip> // provides put_time

// namespaces
using namespace std;

// function prototypes
int get_num_users(); // nickname "gnu": get number of users the sysadmin wants to add
std::string get_name_first(); // nickname "gnf": gets first name
std::string get_name_last(); // nickname "gnl": gets last name
std::string create_username(std::string cu_name_first, std::string cu_name_last); // nickname "cu": returns username
std::string create_password(); // nickname "cp": creates password
uint32_t get_starting_uid(); // nickname "gsu": gets starting UID
uint32_t get_gid(); // nickname "gg": gets GID
std::string get_date_time(); // nickname "gdt": gets date and time

// main function
int main()
{
    int counter = 0;
    int user_index;
    int num_users = get_num_users();
    uint32_t uid;
    uint32_t gid;
    std::string date_time = get_date_time();
    bool file_open_success; // check if output file opens correctly

    // for loop iterates for number of new users added
    for (counter = 0; counter < num_users; counter++)
    {
        user_index = counter + 1;
        std::cout << std::endl;
        std::cout << "***************************************************************************";
        std::cout << std::endl << "You are making Record Entry " << user_index << " of " << num_users << ":" << std::endl;
        std::cout << "***************************************************************************" << std::endl;

        // building username
        std::string name_first = get_name_first();
        std::string name_last = get_name_last();
        std::string username = create_username(name_first, name_last);
        std::transform(username.begin(), username.end(), username.begin(), ::tolower); // transforms username to lowercase

        // create password
        std::string password = create_password();

        // get starting UID and GID
        if (counter == 0)
        {
            uid = get_starting_uid();
            gid = get_gid();
        }
        else
        {
            uid = uid + 1;
        }

        // create User Info
        std::string user_info = name_first + " " + name_last;

        // name Home Directory
        std::string home_directory = "/home/" + username;
        std::string default_shell = "/bin/bash";

        // creating records
        std::cout << std::endl << "<<<< Record " << user_index << " details >>>>" << std::endl;
        std::cout << "________________________________________________" << std::endl;
        std::cout << std::endl << "Username: " << username << std::endl;
        std::cout << "Password: xxxxxxxxxxxxxxx" << std::endl;
        std::cout << "UID: " << uid << std::endl;
        std::cout << "GID: " << gid << std::endl;
        std::cout << "User Info: " << user_info << std:: endl;
        std::cout << "Home Directory: " << home_directory << std::endl;
        std::cout << "Default Shell: " << default_shell << std::endl << std::endl;
        std::cout << "________________________________________________" << std::endl;
        std::cout << "<<<< Writing Record " << user_index << " to file. >>>>"  << std::endl;

        // naming Records file
        std::string filename = "newusers_file_";

        // writing Record to file
        std::string full_filename = "output_files/" + filename + date_time + ".txt";
        std::ofstream file;
        // NOTE: If not already done, create a folder in newusers_file_creator called "output_files" before running the code below.
        file.open (full_filename, file.app);

        // checks if output file was opened successfully
        if (file.is_open())
        {
            file_open_success  = 1;
        }
        else file_open_success = 0;

        // sends output data to file
        std::string c = ":"; // c stands for colon
        //     <Username>  :   <Password>   :   <UID>   :  <GID>    :  <User Info>    :   <Home Directory>   :    <Default Shell>
       file << username << c << password << c << uid << c << gid << c << user_info << c << home_directory << c << default_shell << std::endl;

        // success/failure messages
        if (counter==(num_users-1) && file_open_success == 1)
        {
            std::cout << std::endl;
            std::cout << "Number of Records successfully written: " << num_users << std::endl;
            std::cout << "Output file location: " << full_filename << std::endl << std::endl;
        }
        else if (file_open_success == 0)
        {
            std::cout << std::endl;
            std::cout << "ERROR: the output file could not be written!" << std::endl;
            std::cout << "Check that the 'output_files' folder exists in 'newusers_file_creator'." << std::endl;
            std::cout << "If not, create it." << std::endl << std::endl;
        }

        // close file and say goodbye
        file.close();
        if (counter==(num_users-1)) std::cout << "Goodbye!" << std::endl;
    }
   return 0;
}

// functions
int get_num_users() // gets and returns number of users that the sysadmin wants to add
{
    int gnu_num_users = 0;
    while ((gnu_num_users < 1) || (gnu_num_users > 1000))
    {
        std::cout << "How many users would you like to add to your system (1 to 1000)? ";
        std::cin >> gnu_num_users;
        if ((gnu_num_users < 1) || (gnu_num_users > 1000))
        {
            cout << "ERROR: your entry was not in range (1-1000). Try again." << std::endl << std::endl;
            gnu_num_users = 0;
        }
    }
    return gnu_num_users;
}

std::string get_name_first() // gets and returns first name
{
   std::string gnf_name_first;
   std::cout << "Enter first name: ";
   std::cin >> gnf_name_first;
   return gnf_name_first;
}

std::string get_name_last() // gets and returns last name
{
   std::string gnl_name_last;
   std::cout << "Enter last name: ";
   std::cin >> gnl_name_last;
   return gnl_name_last;
}

std::string create_username(std::string cu_name_first, std::string cu_name_last) // concatenates first name and last name into username
{
    string cu_username = cu_name_first + "." + cu_name_last;
    return cu_username;
}

std::string create_password() // creates random string password
{
    std::string cp_password="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::random_device rd;
    mt19937_64 mt_rand_64(rd());
    std::shuffle(cp_password.begin(), cp_password.end(), mt_rand_64);
    return cp_password.substr(0,32); // change 2nd number (default = 32) for longer/shorter password
}

uint32_t get_starting_uid() // gets and returns starting user id for batch of new users
{
    uint32_t gsu_uid_start;
    std::cout << "Enter unused starting UID: ";
    std::cin >> gsu_uid_start;
    return gsu_uid_start;
}

uint32_t get_gid() // gets and returns group id for batch of new users
{
    uint32_t gg_gid;
    std::cout << "Enter unused GID: ";
    std::cin >> gg_gid;
    return gg_gid;
}

std::string get_date_time() // gets and returns date and time from system
{
    std::stringstream gdt_date_time;
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    gdt_date_time << std::put_time(std::localtime(&in_time_t), "%m%d%Y.%H%M%S");
    return gdt_date_time.str();
}
