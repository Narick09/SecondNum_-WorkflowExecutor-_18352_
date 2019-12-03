#include "Interfaces.h"
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
		std::string numberString = this->getNextComand();
		//		std::cout << "string in csed: <" << numberString << ">\n";
		this->sizeOfNumbers = (numberString.size() / 2) + 1;
		numbers = new size_t[this->sizeOfNumbers];

		size_t NotANumber = 0;
		//		char* tmpString = new char[numberString.size()];
		size_t i = 0;

		while (i < numberString.size()) {
			while (!isdigit(numberString[0])) {
				std::string tmpString = numberString.erase(0, 1);
				numberString.swap(tmpString);
			}
			if (numberString.empty()) {
				//				std::cout<< "empty\n";
				break;
			}

			this->numbers[i] = static_cast<size_t>(stoi(numberString, &NotANumber));

			std::string tmpString = numberString.erase(0, NotANumber);
			numberString.swap(tmpString);
			i++;
		}

		//		i++;
		size_t* tmp = new size_t[i];
		for (size_t g = 0; g < i; g++)
			tmp[g] = this->numbers[g];
		this->sizeOfNumbers = i;
		delete[]numbers;
		numbers = tmp;

		for (size_t g = 0; g < i; g++)
			std::cout << this->numbers[g] << " ";
		std::cout << "\n";

		s = "\0";
		//		delete[]tmpString;
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
	//преобразование стринг в инт
	//ловим исключение из stoi();
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
	if (numbers != nullptr)
		delete[] numbers;
	workFile.close();
}

const size_t Parser::getNum(size_t ind) const {
	//	size_t q = numbers[ind];
	return numbers[ind];
}
const size_t Parser::getsize() const {
	return sizeOfNumbers;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------
std::string * IWorker::resorce = nullptr;
void IWorker::initData()
{
	delete resorce;
	resorce = new std::string;
	//		std::cout << "initData\n";
}
Read::~Read() {
	delete[]this->resorce;
}
Read::Read() {
	//	delete resorce;
	initData();
	//	resorce = new std::string;
	//	std::cout << "initData\n";
}

void Read::toDo(std::vector<std::string> V) {
	std::ifstream inputFile(V[0]);
	std::string some;
	std::string someTmp;
	size_t i = 0;
	//	this->initData();
	//	resorce = new std::string;
	inputFile >> some;				//форматирует строку(если вначале пробел, удаляет его)
	char tmpC = inputFile.peek();
	while (!inputFile.eof()) {
		someTmp += (some + tmpC);
		inputFile >> some;
		tmpC = inputFile.peek();
	}
	//	(resorce)->resize(someTmp.size());
	//	for (i = 0; i < someTmp.size(); i++) {
	//		(*resorce)[i] = someTmp[i];
	//	}
	*resorce = someTmp;
	std::cout << *resorce << "\nadress of string: " << resorce << "\n";

	inputFile.close();
}

void Write::toDo(std::vector<std::string> V) {
	std::ofstream OutFile(V[0]);
	if (OutFile.is_open()) {
		OutFile << *resorce;
		OutFile.close();
		initData();
	}
	else
		std::cout << "\nOutPut File Not Found\n";
}

void Dump::toDo(std::vector<std::string> V) {
	std::ofstream OutFile(V[0]);
	if (OutFile.is_open()) {
		OutFile << *resorce;
		OutFile.close();
	}
	else
		std::cout << "\nOutPut File Not Found\n";
}

//нид ту чейнджЖ
void Replace::toDo(std::vector<std::string> V) {
	size_t position_in_str = 0;
	size_t position_next_start = 0;

	while (position_next_start < std::string::npos) {
		position_in_str = resorce->find(V[0], position_next_start);
		if (position_in_str == std::string::npos) {
			break;
		}
		position_next_start = position_in_str + V[0].size();
		//		std::cout << "from replace: from "<< position_in_str <<" to " << position_next_start <<" <" << resorce->substr(position_in_str, V[0].size()) << ">\n";
		char tmp = (*resorce)[position_next_start];
		if (tmp == ' ' || tmp == '\n' || tmp == '\0')
			resorce->replace(position_in_str, V[0].size(), V[1]);
	}
}

//not worked
void Grep::toDo(std::vector<std::string> V) {
	/*	std::vector<std::string> s;
		size_t i = 0;
		size_t q = 0;
		std::cout << "sort----------------------------------------------\n" << *resorce << "\n";
		//	std::stringstream sw;
		while (q != std::string::npos) {
			q = resorce->find('\n', i);
			std::cout << q << "\n";
			if (q != std::string::npos) {
				s.push_back(resorce->substr(i, q - i + 1));

			}
			else {
				s.push_back(resorce->substr(i));
				break;
			}
			if (q == std::string::npos) {
				break;
			}

			++q;
			i = q;
		}
		std::string tmpStr;
		//	s.shrink_to_fit();
		size_t tmp = s.size();

		//	for (i = 0; i < tmp; i++) {
		//		std::cout << s[i];
		//		tmpStr += s[i];
		//	}
		std::cout << *resorce << " \nnot sorted\n";

		std::sort(s.begin(), s.end());
		for (i = 0; i < tmp; i++) {
			//		std::cout << "2";
			tmpStr += s[i];
		}

		std::cout << tmpStr << " \nsorted\n";
		*resorce = tmpStr;
		*/
}

//not correct(there are no '\n' before the end of string 
void Sort::toDo(std::vector<std::string> V) {
	std::vector<std::string> s;
	size_t i = 0;
	size_t q = 0;
	std::cout << "sort----------------------------------------------\n" << *resorce << "\n";
	//	std::stringstream sw;
	while (q != std::string::npos) {
		q = resorce->find('\n', i);
		std::cout << q << "\n";
		if (q != std::string::npos) {
			s.push_back(resorce->substr(i, q - i + 1));

		}
		else {
			s.push_back(resorce->substr(i));
			break;
		}
		if (q == std::string::npos) {
			break;
		}

		++q;
		i = q;
	}
	std::string tmpStr;
	//	s.shrink_to_fit();
	size_t tmp = s.size();

	//	for (i = 0; i < tmp; i++) {
	//		std::cout << s[i];
	//		tmpStr += s[i];
	//	}
	std::cout << *resorce << " \nnot sorted\n";

	std::sort(s.begin(), s.end());
	for (i = 0; i < tmp; i++) {
		//		std::cout << "2";
		tmpStr += s[i];
	}
	//	i++;
	//	tmpStr += ('\n' + s[i + 1]);
	std::cout << tmpStr << " \nsorted\n";
	*resorce = tmpStr;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------

Validator::Validator(std::map<size_t, std::string> & other, const Parser& otherP) : check(other), p(otherP) {}

void Validator::correctBlocks() {
	size_t tmpSize = p.getsize();//check.capacity();
//	m.find()
//	size_t countRead = 0;
//	size_t countWrite = 0;

	if ((check[p.getNum(0)] != "read") || (check[p.getNum(p.getsize() - 1)] != "write")) {			//out of range
		//throw error of "read -> write"
		std::cout << "error of read - > write--------------------------------------------------------------------------\n";
	}

	for (size_t i = 1; i < tmpSize - 1; i++) {								//for several(нескольких) blocks
		//тут нужно чисто риды врайты проверить или с дампом что-то тоже сделать надо?
		//size_t tmpInd = check[i].first;//check[i].first;//p.getNum(i);//check[i].first;
//		check[p.getNum(i)];

//		m[tmpInd].first;
//		std::string tmpStr = check[i].second;			//out of range
//		m.find(tmpInd);
//		if ((tmpStr == "read") && (check[check[i - 1].first].second != "write")){
			//throw error "read -> write"
//			std::cout << "error of read - > write------------------------------------------------------------------------------------------------------------\n";
//		}

	}
}
//---------------------------------------------------------------------------------------------------------------
const char *MyError::what() {
	return "Equal nums of commands\n";
}
