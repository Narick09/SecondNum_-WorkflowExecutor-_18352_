#include"Interfaces.h"

using namespace std;
int main() {
	//_CrtMemState s1, s2, s3;
	//_CrtMemCheckpoint(&s1);
	//{
	setlocale(LC_ALL, "rus");
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
		Parser parser("instruction_list_name.txt"); // progr
		char endOfBlock = '\0';
		std::map<size_t, std::string> toValid;

		while (!parser.endOfInstruction()) // TRUE if END OF INSTRUCTION
		{
			std::string C = parser.getNextComand();
			if (C[0] != endOfBlock) {
				size_t num = parser.getComandNum(C);
				std::string com = parser.getComandName(C);
				std::vector<std::string> arg = parser.getArgs(C);
				worker = nullptr;
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
	delete inst["grep"];
	delete inst["sort"];
	delete inst["replace"];
	delete inst["dump"];

	//	delete worker;
//	}
//	//Blok of cheking of Mem Leaks:
//	//-------------------------------------------
//	_CrtMemCheckpoint(&s2);
//
//	if (_CrtMemDifference(&s3, &s1, &s2)) {
//		_CrtMemDumpStatistics(&s3);
////		std::cout << "----------------------------------------Mem leaks!----------------------------------------";
//	}
//	_CrtDumpMemoryLeaks();
//----------------------------------------		
	return 0;
}
