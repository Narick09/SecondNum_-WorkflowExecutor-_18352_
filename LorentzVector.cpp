#include"LorentzVector.h"

Parser::Parser(const std::string FileName) {
	workFile.open(FileName, std::ios_base::in);
	if (!workFile.is_open()) {
		//throw ...
		std::cout << "file is not open";
	}
	numbers = nullptr;
}
bool Parser::endOfInstruction() {
	return workFile.eof();
}

std::string Parser::getNextComand() {				//change if we need more than 1 block
	std::string s;

	workFile >> s;

	if (s == "csed") {								//change if we need more than 1 block 
//		std::cout << "csed--------------------------------------------------------------------------------------\n";
		std::string numberString = this->getNextComand();

		this->sizeOfNumbers = (numberString.size() / 2) + 1;			//may be too many member
		numbers = new size_t[this->sizeOfNumbers];

		size_t NotANumber = 0;
		char* tmpString = new char[numberString.size()];
		size_t i = 0;
		for (i = 0; i < numberString.size(); i++) {
			while (!isdigit(numberString[0])) {
				std::string tmpString = numberString.erase(0, 1);
				numberString.swap(tmpString);
			}
			this->numbers[i] = static_cast<size_t>(stoi(numberString, &NotANumber));

			std::string tmpString = numberString.erase(0, NotANumber);
			numberString.swap(tmpString);
		}
//		i++;
		size_t* tmp = new size_t[i];
		for (size_t g = 0; g < i; g++)
			tmp[g] = this->numbers[g];
		delete[]numbers;
		numbers = tmp;

//		for (size_t g = 0; g < i; g++)
//			std::cout << this->numbers[g] << " ";
//		std::cout << "\n";

		s = "\0";
		delete[]tmpString;
	}
	else if (s == "desc") {
		s = this->getNextComand();
	}
	else {
		//throw if first are not number, second are not "=", 3rd are not name etc.
		char tempChar = 0;

		workFile.get(tempChar);
		for (int i = 0; (tempChar != '\n') /*&& (tempChar != '\0')*/ && !workFile.eof(); i++) {		//may be changed to std::getline(workFile, 
			s += tempChar;
//			std::cout << "<" << tempChar << ">\n" << s <<"\n";
			workFile.get(tempChar);
		}
	}
	return s;
}

size_t Parser::getComandNum(std::string& str) {
	//try from stoi();
	size_t num = 0;
	size_t tmp = static_cast<size_t>(stoi(str, &num));
	std::string tmpStr = str.substr(num);				//substr returned substring 
	tmpStr.swap(str);
	
	size_t i = 0;
	while (str[i] != '=') {
		if (str[i] != ' ') {
		//	throw exp
			std::cout << "/a/n/a/n/a/n/a/nti chto tvorish?..\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		}
		i++;
	}
	i++;
	tmpStr = str.substr(i);				//substr returned substring 
	tmpStr.swap(str);

//	std::cout << "after getComandName\n" << str << "\n";
	return tmp;
}

std::string Parser::getComandName(std::string& str) {
	size_t i = 0;
	while (str[i] == ' ') {
		i++;
	}
	std::string tmp = str.substr(i);
	size_t j = 0;
	for (j = 0; (tmp[j] != ' ') && (j < tmp.size()); j++) {}
	tmp.erase(j);
	str = str.substr(i + j);
	j = 0;
	while (str[j] == ' ') {
		if (j == str.size()) {
			str.clear();
			j = 0;
			break;
		}
		j++;
	}

	str = str.substr(j);
//	std::cout << str << "\n";
	return tmp;
}

std::vector<std::string> Parser::getArgs(std::string& str) {
	std::string tmp;												//doesnt work if between args 2 or more spaces		Ps максимально кривой алгоритм
	std::vector<std::string> Args;
	size_t j = 0;
	std::string::size_type q = 0;

	while (j < 2) {
		q = str.find(' ');
		tmp = str.substr(0, q);
//		Args.resize(j + 1);
		Args.push_back(tmp);
		j++;
		if (q == std::string::npos) {
			str.clear();
			if (j == 0) {
				Args.clear();
			}
			break;
		}
		str = str.substr(q + 1);
	}
//	for (size_t t = 0; t < Args.size(); t++) {
//		std::cout << Args[t] << "\n";
//	}
	return Args;
}

Parser::~Parser() {
	if(numbers != nullptr)
		delete[] numbers;
	workFile.close();
}
//----------------------------------------------------------------------------------------------------------------------

void Read::toDo(std::vector<std::string> V) {
	std::ifstream inputFile(V[0]);
	std::string some;
	std::string someTmp;
	int i = 0;
	resorce = new std::string;
	inputFile >> some;
	while (!inputFile.eof()) {
		*resorce += (some + '\n');
		inputFile >> some;
	}
	std::cout << *resorce << "\n";
	inputFile.close();
}

void Write::toDo(std::vector<std::string> V) {
	std::ofstream OutFile(V[0]);

	OutFile << *resorce;					//how it will work??
	OutFile.close();
}

void Grep::toDo(std::vector<std::string> V) {

}
