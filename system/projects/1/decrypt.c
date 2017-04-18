#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


float givenFrequency[26];
float calcFrequency[26];

//Load array given with the letter frequencies for English from file LetFreq.txt
void readFreq(float given[], char fname[]){
    char str[20];
    int count = 0;
    FILE *fIn;
    //Open the file and read it
    fIn = fopen(fname, "r");
    //Checking to see if the file exists
    if(fIn == NULL){
        printf("File cannot be opened");
        exit(0);
    }
    //This converts each piece of the cipher to a double, and gives each number the correct value.
    while(fgets(str, 20, fIn) != NULL){
        givenFrequency[count] = atof(str+2);
        count++;
    }
    fclose(fIn);
}


// Read the encoded text from an input file and accumulate the letter frequency
// data for the encoded text. Store the frequency data in array found.
void calcFreq(float found[], char fname[]){
    FILE *fIn;
    char c;
    int count = 0;
    //open the file from the given parameter
    fIn = fopen(fname, "r");
    //Check and see if the file is successfully opened
    if(fIn == NULL){
        printf("Cannot Open File");
        exit(0);
    }
    //read the file til we get to the end
    while((c = fgetc(fIn)) != EOF){
        if(isalpha(c)){
            if(c >= 'a' && c <= 'z'){
                found[c - 'a']++;
                count++;
            }
            if(c >= 'A' && c <= 'Z'){
                found[c - 'A']++;
                count++;
            }
        }
    }

    for(int i = 0; i < 26; i++){
        found[i] = (found[i]/count);
    }
    fclose(fIn);
}

// Rotate the character in parameter ch down the alphabet for the number of
// positions as given in parameter num and return the resulting character.
char rotate( char ch, int num){
    if(islower(ch)){
        return((((ch - 'a') + num) % 26) + 'a');
    }else{
        return((((ch - 'A') + num) % 26) + 'A');

    }

}

/*******************************************************************************
* This function rotates the array by one
* @param{float[]} a - hhe array being rotated
* @param{int} n - the depth we will be rotating the array to
*******************************************************************************/
void rotateOne(float a[], int n){
    int i;
    int temp;
    temp = a[0];
    for (i = 0; i < n-1; i++){
        a[i] = a[i+1];
        a[i] = temp;
    }
}

/*******************************************************************************
* This function gets the difference between two floats
* @param{float} a - the number being subtracted from
* @param{float} b - the number being used to subtract
*******************************************************************************/
float diffBetweenSquares(float a, float b){
    float x = a - b;
    return x*x;
}

/*******************************************************************************
* This function will rotate the array a specified number of times
* @param{float []} a - the array of floats we are modifying
* @param{int} n - the number of letters available in total
* @param{int} d - the number of positions we rotate
*******************************************************************************/
void rotateArray(float a[], int n, int d){
    int i;
    for(i = 0; i< d; i++){
        rotateOne(a,n);
    }
}

/*******************************************************************************
* This method finds the smallest number in an array of floats
* @param{float []} arr - the array we are finding the smallest number in
* @param{int} length - the length of arr
*******************************************************************************/
int findLeast(float arr[], int length){
    int f;
    float temp;
    for(int i = 0; i < length; i++){
        if(arr[i] < temp){
            temp = arr[i];
            f = i;
        }
    }
    return f;
}

/*******************************************************************************
* Uses the array of floats taken from the LetFreq txt file and determines how
* many times we need to rotate to solve the cipher
* @param {float} given
*******************************************************************************/
int findKey(float given[], float found[]){

    float f;
    float difference[26];
    for(int x = 0; x < 26; x++){
        rotateArray(found, 26, x);
        f = 0;
        for( int y = 0; y < 26; y++){
            f += diffBetweenSquares(given[y], found[y]);
        }
        difference[x] = f;
    }
    return findLeast(difference, 26);
}


//Gets the input file and the output file, and does the decrypting
void decrypt(int key, char in[], char out[]){
    FILE *fIn, *fOut;
    char ch;
    fIn = fopen(in, "r");
    fOut = fopen(out, "w");

    if(fIn == NULL || fOut == NULL){
        printf("Error, file doesn't exist, or trouble opening\n");
        exit(-1);
    }

    while(fscanf(fIn, "%c", &ch) != EOF){
        fprintf(fOut, "%c", rotate(ch, key));
    }

    fclose(fIn);
    fclose(fOut);
}
/*******************************************************************************
* Main function, calls all the necessary methods to get the decryption ball
* rolling
* @param{int} argc - number of argumetns
* @param {char *[]} - array of arguments passed by the user.
*******************************************************************************/
int main(int argc, char * argv[]){
    int key;

    if (argc != 3){
        printf("REQUIRED INPUT AND OUTPUT FILE\n");
        exit(1);
    }
    readFreq(givenFrequency, "LetFreq.txt");
    calcFreq(calcFrequency, argv[1]);
    key = findKey(givenFrequency, calcFrequency);
    decrypt(key, argv[1], argv[2]);

    return 0;
}
