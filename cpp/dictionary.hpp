#include <string>
#include <set>

class Dictionary {
	public:
		Dictionary();
		~Dictionary(void);
		bool exist_word(std::string);
		std::string random_word(void);
	private:
		std::set<std::string> _dict;
};