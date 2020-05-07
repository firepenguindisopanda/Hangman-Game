/*
	Name: Hangman game!
	Student Name: Nicholas Smith
	Description: Program that reads categories and words from a file and ask the user to enter a category to guess a word from the selected category.
				 Displays the hangman design to the console everytime a letter is guessed incorrectly.
	Still need to provide comments in this program! :(
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

#define NUMROWS 10				// for drawing hangman diagram
#define NUMCOLS 12				// for drawing hangman diagram

struct Word {
	char word [30];
	char category [30] ;
	bool used;
};

int randomNumber (int max) {
	return rand() % max;
}

int readCharacters(char data[]) {        
 
    ifstream fin;     				
	char ch;     
	int i;             
	
	fin.open("words.txt");     
	
	if (!fin.is_open()) {         
		cout << "Error -- words.txt could not be opened." << endl;         
		return -1;
	}         
	
	i = 0;
	
	fin >> noskipws;          
	fin >> ch;  
	   
	while (!fin.eof()) {           
		data[i] = ch;          
		i = i + 1;           
		fin >> ch;     
	}          
	
	data[i] = '\0';          
	fin.close();
	                
	return i; 

} 
void lowerCase(char data[]){
      int i=0;
      while(data[i] !='\0'){
          if(data[i] >='A' && data[i]<='Z' ){
              data[i] = data[i]+32;
              }
            i++;
      }    
}
char lowerCaseCharacter(char character){
	if(character >= 'A' && character <= 'Z'){
		character = character + 32;
		return character;
	}else{
		return character;
	}
}
bool isLetter (char c) {
	if ((c >= 'A' && c <= 'Z') ||
	    (c >= 'a' && c <= 'z'))
		return true;
	else
		return false;
}

int getWord (char words[], int start, char word[]) { 
 
    int i, j, length;         
	
	length = strlen (words);			// find how many characters in words
	
	i = start;
	while (i < length && !isLetter(words[i]))
		i = i + 1;             
		
	if (i == length)					// there are no more words
		return -1;						
		
	j = 0;     							// copy characters to word
	while (isLetter(words[i])) {
		word[j]= words[i];
		i = i + 1;
		j = j + 1;     
	}       
 
    word[j]= '\0';          
    
	return i;							// starting position to look for next word
}
int getWords(char allWords[], Word words[]){

int i=0, j=0, wordcount=0, length;
length=strlen(allWords);

	while(i<length){
	i=getWord(allWords, i, words[j].word);
	i=getWord(allWords, i, words[j].category);
		i++;
		j++;     
	wordcount++;
	}
return wordcount;
}
void drawWord(char displayWord[]){
	for(int i=0; i<=strlen(displayWord); i++){
		cout<<displayWord[i]<<" ";
	}
	
}
void setWordToUsed(Word words[], int numWords, char wordSelected[]){
	for(int i=0; i<numWords; i++){
		if(strcmp(wordSelected,words[i].word)==0)
			words[i].used=true;
	}
}
bool findCategoryWord(Word words[], int numWords, char category[], char wordSelected[]){
	Word another[30];
	char tempDestination[numWords], newDest[numWords];
	
	
	int j=0, r, tot=0, ndLength, a= 0;
	
	for(int i=0; i<numWords; i++){
		
		if(strcmp(words[i].category, category)==0){
			if(words[i].used==false){
				strcpy(another[a].word, words[i].word);
				a++;
			}
		}
		
		
	}
	
	if(a==0){
		cout<<"No available words from this category"<<endl;
		return false;
	}
	
	r=randomNumber(numWords);
	int anotherLength = strlen(another->word);
	ndLength = strlen(newDest);
	wordSelected[ndLength];
	
	
	int rando = randomNumber(a);
	
	int stopCondition = strlen(another[rando].word);
	for(int pos =0; pos < stopCondition; pos++){
		//cout<<another[pos].word;
		wordSelected[tot] = another[rando].word[pos];
		tot++;
	}
	
	
	
	/*for(int q=0; q<=strlen(newDest); q++){
		
		wordSelected[tot]=newDest[q];
		//cout<<wordSelected[tot]<<"\n";
		tot++;
		
	}*/
	
		
	return true;
}
bool checkLetter(char guessWord[], char displayWord[], char letter){
	int p=0;
	for(int i=0; i<strlen(guessWord); i++){
		if(guessWord[i]==letter){
			displayWord[i]=letter;
			p++;
		}
	}	
	if(p>0)
		return true;
	else
		return false;
}
void initWord(char guessWord[], char displayWord[]){
	int length;
	length = strlen(guessWord);
	
	for(int o=0; o<length; o++){
		displayWord[o]='_';
		//cout<<strlen(displayWord)<<"\n";
		checkLetter(guessWord, displayWord, 'r');
		checkLetter(guessWord, displayWord, 's');
		checkLetter(guessWord, displayWord, 't');
		checkLetter(guessWord, displayWord, 'l');
		checkLetter(guessWord, displayWord, 'n');
		checkLetter(guessWord, displayWord, 'e');
		
	}
	
		
}
void prepareGallows(char drawing[NUMROWS][NUMCOLS]) {
	int i, j;
	
	for (i=0; i<NUMROWS; i++) {
		for (j=0; j<NUMCOLS; j++) {
			drawing[i][j] = ' ';
		}
	}
		
	for (j=3; j<7; j++)
		drawing[0][j] = '_';

	for (i=1; i<7; i++)
		drawing[i][2] = '|';
	
	for (j=5; j<11; j++)
		drawing[7][j] = '_';
			
	for (j=1; j<11; j++)
		drawing[9][j] = '_';
	
	drawing[1][7] = '|';
	
	drawing[6][1] = '_';
	drawing[6][3] = '_';
	
	drawing[7][0] = '|';
	drawing[8][0] = '|';
	drawing[9][0] = '|';

	drawing[7][4] = '|';	

	drawing[8][11] = '|';	
	drawing[9][11] = '|';	
}
int lettersMissing(char displayWord[]){
	int t=0, y, length;
	length = strlen(displayWord);
	for(int i=0; i<length; i++){
		
		if(displayWord[i]=='_')
			t++;
	}
	y = t-1;
	return y;
}
void drawHangman (int livesLost) {
	char drawing [NUMROWS][NUMCOLS];
	int i, j;
	int lives;
	
	prepareGallows(drawing);
		
	if (livesLost >= 1)
		drawing[2][7] = 'o';

	if (livesLost >= 2) {
		drawing[3][7] = 'X';
		drawing[4][7] = 'X';				
	}

	if (livesLost >= 3)
		drawing[3][6] = '/';

	if (livesLost >= 4)
		drawing[3][8] = '\\';

	if (livesLost >= 5)
		drawing[5][6] = '/';

	if (livesLost == 6)
		drawing[5][8] = '\\';
	
	for (i=0; i<NUMROWS; i++) {
		for (j=0; j<NUMCOLS; j++) {
			cout << drawing[i][j];
		}
		cout << endl;
	}
	cout << endl;

	if (livesLost == 6)					// sound the alarm if player loses
		cout << "\a" << endl;
		
}
void displayCategories(Word words[]){
	int sizeOfCategory, l=0, top = 0, bot = 0;
	
	sizeOfCategory = sizeof(words->category);
	string arr[sizeOfCategory]= " ", word=" ", tempWord = " ", temp[sizeOfCategory];
	for(int lm =0; lm<sizeOfCategory;lm++){
		temp[lm] = words[lm].category;
	}
	for(int i=0;i<sizeOfCategory;++i){
		for(int j=i+1;j<sizeOfCategory;)
		{
			if(temp[i] == temp[j])
			{
				for(int k=j;k<sizeOfCategory-1;++k)
					temp[k]=temp[k+1];
					
				--sizeOfCategory;
			}
			else
				++j;
		}
		
	}
		

	cout<<"\n====================Please select One of the cateories listed below===================="<<endl;
	for(l ; l < sizeOfCategory; l++){
		if(l%5 == 0){
			cout<<endl;
		}else{
			cout<<temp[l]<<"\t\t";
			
		}
			
		
	}
	
}
int playGame(Word words[]){
	char data[500], category[30], some[30]={0}, temp[30]={0}, temp2[30], ch;
	int number, numbers, score=0, livesLost=0;
	bool rcategory, guessed;
	rcategory=false;
	guessed=false;
	number= readCharacters(data);
	numbers= getWords(data, words);	
	bool start=true;
	while(start==true){
		
		
		while(rcategory!=true){
			displayCategories(words);
			cout<<"\nEnter category name: ";
			cin>>category;
			rcategory=findCategoryWord(words, numbers, category, some);
		}
		
		initWord(some, temp);
		setWordToUsed(words, numbers, some);
		
		while(guessed!=true){
			drawHangman (livesLost);
			drawWord(temp);
			cout<<"Enter guess: ";
			cin>>ch;
			if(!(ch=='#')&&!(checkLetter(some, temp, ch))){
				livesLost++;
			}
				
				
			if(ch=='#'){
				initWord(some, temp2);
				cout<<"Enter word guess: ";
				cin>>temp2;
				
				if(temp2==some)
					score=score+4;
				else
					livesLost=livesLost+2;
			}
			
			if(lettersMissing(temp)<0){
				drawHangman (livesLost);
				drawWord(temp);
				score=score+2;
				cout<<endl<<"You win!";
				guessed=true;
				start = false;
			}
			
			if(livesLost>=6){
				drawHangman (livesLost);
				start=false;
				cout<<endl<<"You lose!";
				return score;	
			}
		}
		cout<<endl;
	}
	
	return score;
}

// The following is the new version of the drawHangman function.
//  It calls the prepareGallows function above.



int main() {
	
	//This is the actual code to play the game

	Word w;
	Word wd[100];
	bool ans;
	int ws, o, q=0, length, f, g, val, totalScore;
	string fn, ln, category;

	char words[10000], word[30], choice;
	srand(time(NULL));					// for better random number generation
	

	

	cout<<"Enter your first name and last name: "<<endl;
	cin>>fn>>ln;
	
	cout<<endl;
	
	cout<<"Would you like to play a game?(Y/N)"<<endl;
	cin>>choice;
	choice = lowerCaseCharacter(choice);
	cout<<choice;
	while((choice != 'y' && choice != 'n')){
		cout<<"Please enter a valid Choice.\nThe choice you entered was:\t"<<choice<<endl;
		
		cin>>choice;
		choice = lowerCaseCharacter(choice);
	}
	
	while(choice != 'n'){
		g = playGame(wd);
		totalScore = totalScore + g;
		cout<<"score:\t"<<totalScore<<"\n";
		
		
		
		
		cout<<"Would you like to play again?(Y/N)"<<endl;
		cin>>choice;
		lowerCaseCharacter(choice);
	}
	cout<<"Player2\nName:\t"<<fn<<"\t"<<ln<<"\nScore: "<<totalScore<<endl;


	return 0;

}
