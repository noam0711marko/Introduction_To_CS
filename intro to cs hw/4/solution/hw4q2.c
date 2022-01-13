/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/*-------------------------------------------------------------------------
  Constants and definitions:
--------------------------------------------------------------------------*/

#define MASCULINE (1)
#define FEMININE (2)

#define UN (1)
#define UNO (2)
#define UNA (3)
#define UN_APOSTROPHE (4)


/* put your #defines and typedefs here*/

/*===================== your asked functions ===================== */

//returns gender of noun: 1 if noun is masculine, 2 if noun is feminine.
int get_gender(char* noun);

//returns a symbol for correct indefinite article for noun:
// 1 for "un", 2 for "uno", 3 for "una" and 4 for "un'"
int get_indefinite_article(char* noun);

//returns the length of the noun with the indefinite article addition
int get_length_indefinite_article(char* noun);

//gets a noun and an array of characters in size of noun+indefinite article, and puts
//the noun in the correct form (with the indefinite article) in this array.
void add_indefinite_article(char* noun, char* noun_with_article);

//gets a number for maximum length of word, collect the noun from user, and prints it in it's
//correct form (with the indefinite article)
void handle_indefinite_article(int max_length);


/*===================== added by me functions ===================== */

//returns if a letter is a vowel
bool isVowel(char letter, int place_in_word);

////returns if a letter is a consonant
bool isConsonant(char letter, int place_in_word);

////returns if a letter is a whistler
bool isWhistler(char letter1, char letter2);


/*-------------------------------------------------------------------------
  Your implementation of the functions (describe what each function does)
 -------------------------------------------------------------------------*/
int get_gender(char* noun){
    int len=(int)strlen(noun);
    if(noun[len-1]=='a'){
        return FEMININE;
    }
    return MASCULINE;
}

bool isVowel(char letter, int place_in_word){
    if(letter=='a' || letter=='e' || letter=='i' || letter=='o' || letter=='u' || (letter=='h' && place_in_word==0)){
        return true;
    }
    return false;
}

bool isConsonant(char letter, int place_in_word){
    if(isVowel(letter, place_in_word)){
        return false;
    }
    return true;
}

bool isWhistler(char letter1, char letter2){
    if(letter1=='z' || letter1=='x' || letter1=='y' || (letter1=='g' && letter2=='n') || (letter1=='p' && letter2=='s')
    || (letter1=='s' && isConsonant(letter2, 1)) || (letter1=='i' && isVowel(letter2, 1))){
        return true;
    }
    return false;
}

int get_indefinite_article(char* noun){
    int gender= get_gender(noun);
    if(gender==MASCULINE && isWhistler(noun[0],noun[1])){
        return UNO;
    }
    else if(gender==MASCULINE && !isWhistler(noun[0],noun[1])){
        return UN;
    }
    else if(gender==FEMININE && isVowel(noun[0],0)){
        return UN_APOSTROPHE;
    }
    return UNA;
}

int get_length_indefinite_article(char* noun){
    int len=(int)strlen(noun);
    int indefinite_article= get_indefinite_article(noun);
    if(indefinite_article==UN || indefinite_article==UN_APOSTROPHE){
        return len+3;
    }
    return len+4;
}

void add_indefinite_article(char* noun, char* noun_with_article){
    int len_with_indefinite_article= get_length_indefinite_article(noun);
    int indefinite_article= get_indefinite_article(noun);
    int len_without_article=(int) strlen(noun);
    for(int i=len_without_article; i>=0; i--){
        noun_with_article[len_with_indefinite_article--]=noun[i];
    }
    if (indefinite_article==UN_APOSTROPHE){
        noun_with_article[len_with_indefinite_article--]=(char)*"'";
        noun_with_article[len_with_indefinite_article--]='n';
        noun_with_article[len_with_indefinite_article]='u';
    }
    else{
        noun_with_article[len_with_indefinite_article--]=' ';
        if(indefinite_article==UNO){
            noun_with_article[len_with_indefinite_article--]='o';
        }
        else if(indefinite_article==UNA){
            noun_with_article[len_with_indefinite_article--]='a';
        }
        noun_with_article[len_with_indefinite_article--]='n';
        noun_with_article[len_with_indefinite_article]='u';
    }
}

void handle_indefinite_article(int max_length){
    char* noun=(char*)malloc(sizeof(char)*(max_length+1));
    scanf(" %s", noun);
    int len_with_indefinite_article= get_length_indefinite_article(noun);
    char* noun_with_indefinite_article= (char*)malloc(sizeof(char)*(len_with_indefinite_article+1));
    add_indefinite_article(noun, noun_with_indefinite_article);
    printf("%s\n", noun_with_indefinite_article);
    free(noun_with_indefinite_article);
    free(noun);
}

/*-------------------------------------------------------------------------
  The main program
 -------------------------------------------------------------------------*/

/**
 * main - reads two integers and calls handle_indefinite_article() accordingly.
 * 
 * @returns the status, for the operating system.
 */
int main() {
    int max_length, num_of_nouns;
    scanf("%d %d", &max_length, &num_of_nouns);
    for(int i = 0; i < num_of_nouns; i++) {
        handle_indefinite_article(max_length);
    }
    return 0;
}