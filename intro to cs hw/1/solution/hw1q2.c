#include <stdio.h>

#define FAIl 2
#define SUCCESS 3
#define TRUE 0
#define FALSE 1

/*print a message which asks the user to insert the letter he would like to count*/
void askForLetterToCountFromUser()
{
    printf("Enter letter to count:\n");
}

/*check that the user truly insert a letter*/
int checkScannedLetter(char letter)
{
    if ((letter>='a' && letter<='z') || (letter>='A' && letter<='Z'))
        return TRUE;

    return FALSE;
}

/*scans a char from user and then checks that it is really a letter*/
int scanTheLetterFromUser(char* letter)
{
    if(scanf(" %c",letter)!=1 || checkScannedLetter(*letter)==FALSE)
        return FAIl;

    return SUCCESS;
}

/*print a message which asks the user to enter sequence*/
void askForSequenceFromUser()
{
    printf("Enter the char sequence:\n");
}

/*scans one char at a time - if it is equals to the letter the user wanted to count (upper or lower case)
 * the counter will be added one.
 * in each scanning - the scan overwrite the variable 'sequence', so the user can insert a sequence in every
 * length he would like.
 * when the scan receive the '#' sign - the process will stop and return the counter*/
int scanSequenceAndCountLetter (char letter, char sequence)
{
    int counter=0;
    while (1){
        scanf(" %c", &sequence);
        if (sequence=='#')
            break;
        if(sequence==letter || sequence==((letter-'a')+'A') || sequence==((letter-'A')+'a'))
            counter++;
    }

    return counter;
}

/*prints a message with the number of times that the letter shown*/
void ptintHowManyTimesTheLetterAppeared(int counter)
{
    printf("The letter appeared %d times\n", counter);
}


int main() {
    char letter='\n';
    char sequence='\n';
    askForLetterToCountFromUser();
    if(scanTheLetterFromUser(&letter)==FAIl)
        return 1;
    askForSequenceFromUser();
    int counter = scanSequenceAndCountLetter(letter, sequence);
    ptintHowManyTimesTheLetterAppeared(counter);
    return 0;
}

