#ifndef MEDIA_H 
#define MEDIA_H

#include <string>
#include <vector>

using namespace std;

//base class to be stored in graph
class Media {
	protected:
		string title;
	public:
		Media(const string& title) : title(title) {}
		virtual ~Media() {}
		
		string getTitle() const { return title; }

		virtual vector<string> getGenres() const = 0;//pure virtual function 

		virtual void printDetails() const = 0;//pure virtual function for printing details
};
#endif
