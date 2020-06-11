/**********************************************************************
* Program:
*   Lab 08, Vulnerabilities and Exploits
*   Brother Wilson, CSE453
*
* Authors:
*   Timothy Bohman
*   Alex Johnson
*   John Batty
*   Abdias Baldiviezo Aguilar
*
* Summary:
*
* Sources:
*   
*************************************************************************/
#include <iostream>
using namespace std;

#define arraySize 4

/*************************************
 * ARRAY VULNERABILTY
 * 1. There must be an array and an array index variable
 * 2. The array index variable must be reachable through external input.
 * 3. There must not be bounds checking on the array index variable.
 ****************************************/
void arrayVulnerability(int index, int value)
{

    int array[arraySize];
    bool authenticated = false;

    array[index] = value;

    cout << "Array Content at index " << index << " has been changed to " << value << endl;

    for(int i = 0; i < arraySize + 1; i++ ) {
        cout << "Array at Index " << i << ": " << array[i] << endl;
    }
    
    if(authenticated) {
        cout << "Welcome! You have successfully been authenticated" << endl;
    }
    else {
        cout << "You are not authenticated." << endl;
    }


}

/**************************************
 * ARRAY WORKING
 * Call arrayVulnerability() in a way that does
 * not yield unexpected behavior
 *************************************/
void arrayWorking()
{
   arrayVulnerability(1,256);
}

/**************************************
 * ARRAY EXPLOIT
 * 1. The attacker provides an array index value outside the expected range
 * 2. The attacker must be able to provide input or redirect
 *    existing input into the array at the index he provided
 * 3. The injected value must alter program state in a way
 *    that is desirable to the attacker
 *************************************/
void arrayExploit()
{
   arrayVulnerability(arraySize, -1);
}



/*************************************
 * ARC VULNERABILTY
 * 1. There must be a function pointer used in the code.
 * 2. Through some vulnerability, there must be a way for user input to
 *    overwrite the function pointer. This typically happens through a stack
 *    buffer vulnerability.
 * 3. After the memory is overwritten, the function pointer must be
 *    dereferenced.
 ****************************************/
void arcVulnerability()
{
/*
{
 long buffer[4];
 void (* pointerFunction)() = safe;
 cin >> buffer[4]; // input references pointerFunction
 pointerFunction(); // here we are not executing safe()
 // but rather whatever function
// specified by the user in the
// cin statement
}
*/
}

/**************************************
 * ARC WORKING
 * Call arcVulnerability() in a way that does
 * not yield unexpected behavior
 *************************************/
void arcWorking()
{
   arcVulnerability(/* parameters with non-malicious data */);
}

/**************************************
 * ARC EXPLOIT
 * 1. The attacker must exploit a vulnerability allowing unintended access to
 *    the function pointer.
 * 2. The attacker must have the address to another function which is to be
 *    used to replace the existing function pointer.
 *************************************/
void arcExploit()
{
   arcVulnerability(/* parameters with malicious data */);
}

/****************************************************************************************************************
 * 
 * *************************************************************************************************************/
/*************************************
 * V-TABLE VULNERABILTY
 * 1. The vulnerable class must be polymorphic.
 * 2. The class must have a buffer as a member variable.
 * 3. Through some vulnerability, there must be a way for user input to
 *    overwrite parts of the V-Table.
 * 4. After a virtual function pointer is overwritten, the virtual function must
 *    be called.
 ****************************************/
void vtableVulnerability()
{

/*
class Vulnerable
{
public:
 virtual void safe(); // polymorphic function
private:
 long buffer[2]; // an array in the class that has
}; // a buffer overrun vulnerability

void Vulnerable :: safeSet(long value, int index)
{ // set the buffer[index] value checking for buffer overruns
 if (index >= 0 && index < sizeof(buffer)/sizeof(buffer[0]))
 buffer[index] = value;
}
*/
}

/**************************************
 * V-TABLE WORKING
 * Call arcVulnerability() in a way that does
 * not yield unexpected behavior
 *************************************/
void vtableWorking()
{
   vtableVulnerability(/* parameters with non-malicious data */);
}

/**************************************
 * V-TABLE EXPLOIT
 * 1. Through some vulnerability, the V-Table pointer or a function pointer
 *    within the V-Table must be overwritten.
 * 2. The attacker must have the address to another V-Table pointer or a
 *    function pointer.
 *************************************/
void vtableExploit()
{
   vtableVulnerability(/* parameters with malicious data */);
}

/****************************************************************************************************************
 * 
 * *************************************************************************************************************/
/*************************************
 * STACK VULNERABILTY
 * 1. There must be a buffer (such as an array) on the stack.
 * 2. The buffer must be reachable from an external input.
 * 3. The mechanism to fill the buffer from the external input must not
 *    correctly check for the buffer size.
 * 4. The buffer must be overrun (extend beyond the intended limits of the
 *    array).
 ****************************************/
void stackVulnerability()
{
/*
{
 char text[256]; // stack variable
 cin >> text; // no validation on buffer size
}
*/

}

/**************************************
 * STACK WORKING
 * Call arcVulnerability() in a way that does
 * not yield unexpected behavior
 *************************************/
void stackWorking()
{
   stackVulnerability(/* parameters with non-malicious data */);
}

/**************************************
 * STACK EXPLOIT
 * 1. The attacker must provide more data into the outwardly facing buffer
 *    than the buffer is designed to hold.
 * 2. The attacker must know where the stack pointer resides on the stack.
 *    This should be just beyond the end of the buffer.
 * 3. The attacker must insert machine language instructions in the buffer.
 *    This may occur before, after, or even around the stack pointer. The
 *    machine language could be already compiled code in the program.
 * 4. The attacker must overwrite the stack pointer. The old value, directing
 *    the flow of the program after the function is returned, must be changed
 *    from the calling function to the provided machine language in step 3.
 *************************************/
void stackExploit()
{
   stackVulnerability(/* parameters with malicious data */);
}

/****************************************************************************************************************
 * 
 * *************************************************************************************************************/
/*************************************
 * HEAP VULNERABILTY
 * 1. There must be two adjacent heap buffers.
 * 2. The first buffer must be reachable through external input.
 * 3. The mechanism to fill the buffer from the external input must not
 *    correctly check for the buffer size.
 * 4. The second buffer must be released before the first.
 * 5. The first buffer must be overrun (extend beyond the intended limits of
 *    the array).
 ****************************************/
void heapVulnerability()
{
    /*
   char *text1 = new char[256];
   char *text2 = new char[256];
   cin >> text1;
   delete [] text2;
   */
}

/**************************************
 * HEAP WORKING
 * Call arcVulnerability() in a way that does
 * not yield unexpected behavior
 *************************************/
void heapWorking()
{
   heapVulnerability(/* parameters with non-malicious data */);
}

/**************************************
 * HEAP EXPLOIT
 * 1. The attacker must provide more data into the outwardly facing heap
 *    buffer than the buffer is designed to hold.
 * 2. The attacker must know the layout of the Memory Control Block (MCB)
 *    (essentially a linked list) residing just after the buffer.
 * 3. The attacker must provide a new MCB containing both the location of
 *    the memory overwrite and the new data to be overwritten.
 *************************************/
void heapExploit()
{
   heapVulnerability(/* parameters with malicious data */);
}

/****************************************************************************************************************
 * 
 * *************************************************************************************************************/
/*************************************
 * INTGER VULNERABILTY
 * 1. There must be a security check represented by an expression.
 * 2. The expression must have the potential for overflow.
 * 3. At least one of the numbers used to compute the sentinel must be
 *    reachable through external input. This sentinel is a variable used to make
 *    the security decision from the first requirement.
 ****************************************/
void integerVulnerability()
{
}

/**************************************
 * INTGER WORKING
 * Call arcVulnerability() in a way that does
 * not yield unexpected behavior
 *************************************/
void integerWorking()
{
   integerVulnerability(/* parameters with non-malicious data */);
}

/**************************************
 * INTGER EXPLOIT
 * 1. Provide input, either a buffer size or a single value, that is directly or
 *    indirectly used in the vulnerable expression.
 * 2. The input must exceed the valid bounds of the data-type, resulting in an
 *    overflow or underflow condition.
 *************************************/
void integerExploit()
{
   integerVulnerability(/* parameters with malicious data */);
}

/****************************************************************************************************************
 * 
 * *************************************************************************************************************/
/*************************************
 * ANSI_UNICODE CONVERSION VULNERABILTY
 * 1. There must be a buffer where the basetype is greater than one.
 * 2. Validation of the buffer must check the size of the buffer rather than the
 *    number of elements in the buffer.
 ****************************************/
void ansiVulnerability()
{
}

/**************************************
 * ANSI_UNICODE CONVERSION WORKING
 * Call arcVulnerability() in a way that does
 * not yield unexpected behavior
 *************************************/
void ansiWorking()
{
   ansiVulnerability(/* parameters with non-malicious data */);
}

/**************************************
 * ANSI_UNICODE CONVERSION EXPLOIT
 * 1. The attacker must provide more than half as much data into the
 *    outwardly facing buffer as it is designed to hold.
 * 2. From here, a variety of injection attacks are possible. The most likely
 *    candidates are stack smashing or heap smashing. In the above example,
 *    the third parameter of the copyUnicodeText() function is the number
 *    of elements in the string (256 elements), not the size of the string (512
 *    bytes). The end result is a buffer overrun of 256 bytes
 *************************************/
void ansiExploit()
{
   ansiVulnerability(/* parameters with malicious data */);
}



/**************************************
 * MAIN
 * 
 *************************************/
int main() {
    
    arrayWorking();
    arrayExploit();

    arcWorking();
    arcExploit();

    vtableWorking();
    vtableExploit();

    stackWorking();
    stackExploit();

    heapWorking();
    heapExploit();

    integerWorking();
    integerExploit();

    ansiWorking();
    ansiExploit();
}
