#include <iostream>
#include<string>
#include <vector>
#include <map>
#include <fstream>

class Parser {
	std::ifstream workFile;
	size_t* numbers;
	size_t sizeOfNumbers;
public:
	Parser(const std::string Name);
	bool endOfInstruction();
	std::string getNextComand();
	size_t getComandNum(std::string& str);
	std::string getComandName(std::string& str);
	std::vector<std::string> getArgs(std::string& str);
	~Parser();
};

class Validator {};

class IWorker {
	static size_t counter;
protected:
	std::string * resorce;//Res*
public:
	void initData()
	{
		resorce = new std::string;
		counter = 1;
		counter++;
	}
	//	IWorker() {};					//зочем?
	virtual void toDo(std::vector<std::string> V) = 0;
};

class Read : public IWorker {
public:
//	Read() {}
	void toDo(std::vector<std::string> V);
	~Read();
};
class Write : public IWorker {
public:
//	Write() {}
	void toDo(std::vector<std::string> V);
};
class Grep :public IWorker {
public:
//	Grep() {}
	void toDo(std::vector<std::string> V);

};
class Sort :public IWorker {
public:
//	Sort() {}
	void toDo(std::vector<std::string> V);
};
class Dump :public IWorker {
public:
//	Dump() {}
	void toDo(std::vector<std::string> V);
};
class Replace :public IWorker {
public:
//	Replace() {}
	void toDo(std::vector<std::string> V);
};
