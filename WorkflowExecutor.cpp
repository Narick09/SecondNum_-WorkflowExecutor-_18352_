#include"Interfaces.h"

using namespace std;
int main() {
	setlocale(LC_ALL, "");
	//надо будет еще отлавливать мап на неизвестном слове, на одном и том же номере(цифры не должны повторяться)
	std::map<std::string, IWorker *> inst; // Workers storage
	inst["read"] = new Read;
	inst["write"] = new Write;
	inst["grep"] = new Grep;
	inst["sort"] = new Sort;
	inst["replace"] = new Replace;
	inst["dump"] = new Dump;

	map<size_t, pair<IWorker*, vector<string>>> programm; // num-> Worker, agrs
	Parser parser("instruction_list_name.txt"); // progr
	char endOfBlock = '\0';
	std::map<size_t, std::string> toValid;
	//надо будет запихать в еще больший тхроу, чтобы ес чо отловить крит ошибку, и чтобы все на**й удалилось, если эта крит ошибка произойдетЮ ибо не**й
	try {
		while (!parser.endOfInstruction()) // TRUE if END OF INSTRUCTION
		{
			std::string C = parser.getNextComand(); //1 = read 1.txt = std::regexp
	//		std::cout << C << "\n";
			if (C[0] != endOfBlock) {
				//try expressions
				size_t num = parser.getComandNum(C);// 1
	//			std::cout << num << "\n";
				std::string com = parser.getComandName(C);// read
	//			std::cout << com << "\n";
				std::vector<std::string> arg = parser.getArgs(C); //{"1.txt"}
	//			std::cout << com << "\n";
	//			for (size_t i = 0; i < arg.size(); i++) {
	//				std::cout << i << ": <" << arg[i] << ">\n";
	//			}
				IWorker * worker = nullptr;
				//try
				worker = inst.at(com);

				try {
					programm.at(num);
					MyError Equalnums; // если у нас будут одинаковые номера, то програм ат не кинет оут оф рейндж - кидаем ошибку одинаковых чисел
					throw Equalnums;	//если не будет одинаковых номеров, то ловим оут оф рейндж и там 
				}
				catch (MyError const& e) {
					throw e;//если есть одинковые циферки, ловим и обрабатываем выше(чтобы все остальное удалилось к х**м
				}
				catch (std::out_of_range const& e) {
					programm[num] = pair<IWorker*, vector<string>>(worker, arg);
				}

				if ((com == "read") || (com == "write")) {
					toValid[num] = com;
				}
			}
		}
	}
	catch (...) {
		std::cout << "unknown error\n";
	}
	
	//try
	Validator check(toValid, parser);
	check.correctBlocks();


	size_t sizeOfNumsOfProg = parser.getsize();
	std::cout << sizeOfNumsOfProg;

	for (size_t i = 0; i < sizeOfNumsOfProg; i++) {
		size_t com_num = parser.getNum(i);
		pair<IWorker*, vector<string>> & s = programm[com_num];
		s.first->toDo(s.second);
	}

	delete inst["read"];
	delete inst["write"];
	delete inst["replace"];
	delete inst["sort"];
	delete inst["dump"];
	delete inst["grep"];
//	system("pause");
	return 0;
}


//dump <filename> - сохраняет строку в указанном файле и передает ее дальше
//writefile <filename> – запись текста в файл => после, удаляем строку
