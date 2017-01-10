#include "wordsmith.h"
#include <fstream>
#include <iomanip>
using namespace std;


fsu::String cleanWord(fsu::String words){
	
	//fsu::String copy;
	unsigned int j = 0;

	for (unsigned int i = 0; i < words.Size(); ++i){

		if (isalnum(words[i]) || words[i] == '-' || words[i] == '\\'){

			//copy.PushBack(tolower(words[i]));
			words[j] = tolower(words[i]);
			++j;
		} // end of if (isalnum(words[i]) || words[i] == '-')

		else if (j != 0 && (words[i] == '\'' || words[i] == '`')){

			if (i == words.Size() - 1 || words[i + 1] !=  words[i]){

				words[j] = words[i];
				++j;
			}
			else{

				++i;
			}
		} // end of else if (words[i] == '\'')
		else if (j != 0 && words[i] == '.'){

			words[j] = words[i];
			++j;

		}
	} // end of for (unsigned int i = 0; i < words.Size(); ++i)

	while (j > 0 && (words[j - 1] == '.' || words[j - 1] == '\'' || words[j - 1] == '`' || words[j - 1] == '\\')){

		--j;
	}


	words.SetSize(j);

	return words;
} // end of fsu::String cleanWord(fsu::String words)

bool WordSmith::ReadText(const fsu::String& infile){

	unsigned int currWords = 0;
	ifstream read(infile.Cstr());
	if (!read){ return false; }
	fsu::String words;

	infiles_.PushBack(infile);

	// as long as there are words in the file keep reading file
	while (read >> words){

		words = cleanWord(words);

		// if the word is empty continue with next loop
		if (words.Size() == 0){
	
			continue;
		}


		++totalWords;
		++currWords;
		

		// defines what should be searched for
		EntryType entry(words, 1);
		
		// searches inside wordset for the word and compares if the entry
		// is the same value and if it is the same word it returns iterator
		// for the pair otherwise it returns "end" iterator
		SetType::Iterator i = wordset_.Includes(entry);

		if (i != wordset_.End()){

			// i iterator points to a pair u
			entry.second_=(*i).second_+1;

		} // end of if (i != wordset_.End())

			wordset_.Insert(entry);
	
	} // end of while (read >> words){

	cout << "Number of Words read: " << currWords << endl;
	cout << "Current vocabulary size: " << wordset_.Size() << endl;
	
	return true;

} // end of bool WordSmith::ReadText(const fsu::String& infile){

bool WordSmith::WriteReport(const fsu::String& outfile, unsigned short c1, unsigned short c2) const{

	ofstream report(outfile.Cstr());
	if (!report){ return false; }

	report << "Text Analysis for files: ";

	for (fsu::List < fsu::String >::ConstIterator i = infiles_.Begin(); i != infiles_.End(); ++i){

		report << *i << " ";

	} // end of for (fsu::List < fsu::String >::Iterator i = infiles_.Begin(); i != infiles_.End(); ++i)

	report << endl;

	report << "word                 frequency \n";
	report << "----                 --------- \n";
	
	for (SetType::ConstIterator i = wordset_.Begin(); i != wordset_.End(); ++i){

		report << setw(21) << left << (*i).first_ << setw(9) << right << (*i).second_ << endl;
	}

	report << "Number of words: " << totalWords << endl;
	report << "Vocabulary size: " << wordset_.Size() << endl;

	cout << "Number of words: " << totalWords << endl;
	cout << "Vocabulary size: " << wordset_.Size() << endl;
	cout << "Analysis written to file: " << outfile << endl;

	return true;

} // end of bool fsu::WordSmith::WriteReport(const fsu::String& outfile, unsigned short c1 = 15, unsigned short c2 = 15) const

void WordSmith::ShowSummary() const{

	cout << "Current files: ";

	for (fsu::List < fsu::String >::ConstIterator i = infiles_.Begin(); i != infiles_.End(); ++i){

		cout << *i << " ";

	} // end of for (fsu::List < fsu::String >::Iterator i = infiles_.Begin(); i != infiles_.End(); ++i)

	cout << endl;
	cout << "Current word count: " << totalWords << endl;
	cout << "Current vocabulary size: " << wordset_.Size() << endl;

} // end of void WordSmith::ShowSummary() const

void WordSmith::ClearData(){

	totalWords = 0;
	wordset_.Clear();
	infiles_.Clear();

} // end of void WordSmith::ClearData()