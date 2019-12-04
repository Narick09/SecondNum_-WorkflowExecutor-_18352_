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
	IWorker * worker = nullptr;

	try {
		map<size_t, pair<IWorker*, vector<string>>> programm; // num-> Worker, agrs
		Parser parser("instruction_list_name.txt"); // progr		//зависает, если не может открыть файл
		char endOfBlock = '\0';
		std::map<size_t, std::string> toValid;
		//в большом трае чтобы ес чо отловить крит ошибку, и чтобы все на**й удалилось, если эта крит ошибка произойдет, ибо не**й
	
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
				worker = nullptr;
				//try
				worker = inst.at(com);
				
				try {
					programm.at(num);
					MyError Equalnums;// если у нас будут одинаковые номера, то програм ат не кинет оут оф рейндж - кидаем ошибку одинаковых чисел
					throw Equalnums;	//если не будет одинаковых номеров, то ловим оут оф рейндж и там 
				}
				catch (MyError const& e) {
					throw e;//если есть одинковые циферки, ловим и обрабатываем выше(чтобы все остальное удалилось)
				}
				catch (std::out_of_range const&) {
//					std::cout << "tried----------------------------------------------------------------------------------------------------";
					programm[num] = pair<IWorker*, vector<string>>(worker, arg);
				}
				//отправлеяется в валидатор, которые чекает чтобы 1м был рид, последним - врайт(+ можно прописать, чтобы он чекал, что послед перед ридом идет врайт)
				if ((com == "read") || (com == "write")) {
					toValid[num] = com;
				}
			}
		}

		Validator check(toValid, parser);
		check.correctBlocks();

		size_t sizeOfNumsOfProg = parser.getsize();
		std::cout << sizeOfNumsOfProg;
		
		for (size_t i = 0; i < sizeOfNumsOfProg; i++) {
			size_t com_num = parser.getNum(i);
			pair<IWorker*, vector<string>> & s = programm[com_num];
			s.first->toDo(s.second);
		}
	}
	catch (std::exception const& Er) {
		std::cout << Er.what() << "\n";
	}
	catch (...) {
		std::cout << "unknown error\n";
	}

	delete inst["read"];
	delete inst["write"];
	delete inst["replace"];
	delete inst["sort"];
	delete inst["dump"];
	delete inst["grep"];
//	delete worker;
//	system("pause");
	return 0;
}

//dump <filename> - сохраняет строку в указанном файле и передает ее дальше
//writefile <filename> – запись текста в файл => после, удаляем строку
