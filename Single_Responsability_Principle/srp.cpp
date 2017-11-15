#include <boost/lexical_cast.hpp> // convert things to strings
#include <vector>		  // std::vector
#include <string> 		  // std::string
#include <fstream> 		  // std::ofstream

/* 
 *	Lecture 3 - Designer Patterns in Modern C++:
 *	Single Responsibility Principle.
 *
 *	"A class should have only one reason to change." - Martin, Robert C. (2003).
 *	In another words, the module or class have a responsibility over a single
 *	part of the functionality provided by the program.
 *
 */

struct Journal{
	std::string title;
	std::vector<std::string> entries;
	
	Journal(const std::string &title) : title(title){}

	void add_entry(const std::string& entry){
		static int count = 1;
		entries.push_back(boost::lexical_cast<std::string>(count++) + ": " + entry);
	}

/*
 *	The save method violates the Single Responsibility Principle, because if the class 
 * 	Journal changes, there will be more than one reason to edit it.
 *
 */
	void save(const std::string& filename){
		std::ofstream ofs(filename);
		for (auto& e : entries){
			ofs << e << std::endl;
		}
	}
};

/*
 *	The PersistenceMeneger class performs the same task as the save method, however 
 * 	because it is isolated, The Single Responsibility Principle is respected.
 *
 */
 
struct PersistenceManeger{
	static void save(const Journal& j, const std::string &filename){
		std::ofstream ofs(filename);
		for (auto& e : j.entries){
			ofs << e << std::endl;
		}
	}
};


int main(){
	
	Journal journal{"Dear Diary"};
	journal.add_entry("I ate a bug");
	journal.add_entry("I cried today");
	
//	journal.save("diary.txt");

	PersistenceManeger pm;

	pm.save(journal, "diary.txt");

	return 0;
}
