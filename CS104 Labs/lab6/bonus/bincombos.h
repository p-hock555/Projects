#include <vector>
#include <string>

class BinaryCombos {
	public:
	/**
		Returns a vector of all possible binary 
		strings of a certain length. 
		generate(1) should return ["0", "1"]
		generate(2) should return ["00", "01", "10", "11"]
		etc.

		Order does not matter.
	*/
	std::vector<std::string> generate(int length);
};
