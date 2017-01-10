#ifndef WORDSMITH_H
#define WORDSMITH_H
#include <string>
#include "pair.h"
#include "xstring.h"
#include "ovector.h"
#include "list.h"
#include "olist.h"
#include "oaa.h"


class WordSmith{
public:
	WordSmith() :totalWords(0){ }
	bool   ReadText(const fsu::String& infile);
	bool   WriteReport(const fsu::String& outfile, unsigned short c1 = 15, unsigned short c2 = 15) const;
	void   ShowSummary() const;
	void   ClearData();
        typedef fsu::OAA             < fsu::String, unsigned long>      SetType;

private:
	// the internal class terminology:
	typedef fsu::Pair      < fsu::String, unsigned long >  EntryType;
	typedef fsu::LessThan  < EntryType >                   PredicateType;

	// choose one associative container class for SetType:
	// typedef fsu::UOList          < EntryType , PredicateType >      SetType;
	// typedef fsu::MOList          < EntryType , PredicateType >      SetType;
	// typedef fsu::UOVector        < EntryType, PredicateType >      SetType;
	// typedef fsu::MOVector        < EntryType , PredicateType >      SetType;
	// typedef fsu::RBLLT           < EntryType , PredicateType >      SetType;
 
	// declare the two class variables:
	SetType                    wordset_;
	fsu::List < fsu::String >  infiles_;
	unsigned long totalWords;


}; // end of class wordsmith{

#endif 
