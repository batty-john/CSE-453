/**********************************************************************
* Program:
*   Lab 05, Homographs
*   Brother Wilson, CSE453
*
* Authors:
*   Timothy Bohman
*   Alex Johnson
*   John Batty
*   Abdias Baldiviezo Aguilar
*
* Summary:
*   Accepts two file paths as input from the user and canonicalizes them
*   and compares the result in order to determine if they are homographs.
*************************************************************************/


#include <iostream>
#include <vector>
#include <string>
#include <direct.h>  // _getcwd
#include <stdio.h>   // printf
#include <stdlib.h>  // free, perror
#include <cstddef>   // std::size_t
#include <algorithm> // replace

using namespace std;

void canonicalizeFilePath(string file, string &canonicalizedFile) {


    if (file.at(0) == '.' && file.at(1) == '.') {
        file = string("./").append(file);
    }
    
    //cout << "_MAX_PATH: " << _MAX_PATH << endl;

    /******
     char* buffer;

    // Get the current working directory:
    if ( (buffer = _getcwd( NULL, 0 )) == NULL )
        perror( "_getcwd error" );
    else
    {
        printf( "Current working directory: %s \nLength: %zu\n", buffer, strlen(buffer) );
        free(buffer);
    }
    ********/

    string filename = file;
    string filepath;
    char* path = const_cast<char*>(file.c_str());
    //cout << "path: " << path << endl;

    replace( filename.begin(), filename.end(), '/', '\\');

        // Get the file directory:
    if ( (path = _getcwd( path, _MAX_PATH )) == NULL )
        perror( "_getcwd error" );
    else
    {
        //printf( "File Directory: %s \nLength: %zu\n", path, strlen(path) );

        if (filename.at(0) == '.' || ((filename.at(0) != '\\') && (filename.at(0) != '.') && (filename.at(1) != ':'))) {
            filepath = string(path);
            if (filename.at(0) != '\\') {
                filepath.append("\\");
            }
        }
        else
            filepath = "";

        //cout << "filepath: " << filepath << endl;
        

        while(filename != "") {

            while (filename.at(0) == '.') {
                //cout << endl << "Begins with . " << endl;
                size_t lastSlash =  filepath.find_last_of("\\");
                filepath = filepath.substr(0, lastSlash);
                filename.erase(0,1);
                //cout << "Filename: " << filename << endl;
            }

            //take the content of filename up until the first slash and append it to filepath
            size_t nextRelative = filename.find("..");

            filepath.append(filename.substr(0,nextRelative));
            filename.erase(0,nextRelative);
        }
        
        //cout << "Complete path: " << filepath << endl;
    }

    transform(filepath.begin(), filepath.end(), filepath.begin(), [](unsigned char c) {return tolower(c);});
    canonicalizedFile = filepath;
    return;
}

int main()
{
    cout << "Specify the first filename: ";
    string file1;
    cin >> file1;
    cout << "Specify the second filename: ";
    string file2;
    cin >> file2;

    string canonicalizedFile1;
    string canonicalizedFile2;
    canonicalizeFilePath(file1,canonicalizedFile1);
    canonicalizeFilePath(file2,canonicalizedFile2);

    cout << "File 1: " << canonicalizedFile1 << endl;
    cout << "File 2: " << canonicalizedFile2 << endl;
    
    if (canonicalizedFile1 == canonicalizedFile2) {
        cout << "The paths are homographs.\n";
    }
    else {
        cout << "The paths are not homographs.\n";
    }
    
    return 0;
}

/*
Sources:
https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/getcwd-wgetcwd?redirectedfrom=MSDN&view=vs-2019
http://www.cplusplus.com/reference/string/string/find_last_of/
https://stackoverflow.com/questions/313970/how-to-convert-stdstring-to-lower-case
*/