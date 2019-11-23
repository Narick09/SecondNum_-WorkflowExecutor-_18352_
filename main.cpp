#include"LorentzVector.h"

//class Res {}; // class for resources

// IN FILE instruction_list_name
// 1 = read 1.txt
// 2 = grep hello
// 4 = sort
// 4 = write 2.txt
// 1->4->2->3

using namespace std;
int main() {
	setlocale(LC_ALL, "");
	//надо будет еще отлавливать мап на неизвестном слове, на одном и том же номере(цифры не должны повторяться)
	std::map<std::string, IWorker *> inst; // Workers storage
							//сначала реализовать блок 
	inst["read"] = new Read;
	/*
	inst["write"] = new Write;
	inst["grep"] = new Grep;
	inst["sort"] = new Sort;
	inst["replace"] = new Replace;
	inst["dump"] = new Dump;
	*/
	std::string * resorce = new string;
	map<size_t, pair<IWorker*, vector<string>>> programm; // num-> Worker, agrs
	// std::iterator
	Parser parser("instruction_list_name.txt"); // progr
//	int i = 0;
	char endOfBlock = '\0';
	while (!parser.endOfInstruction()) // TRUE if END OF INSTRUCTION
	{
//		i++;
		std::string C = parser.getNextComand(); //1 = read 1.txt = std::regexp
		std::cout << C << "\n";
		if (C[0] != endOfBlock) {
			//try
			size_t num = parser.getComandNum(C);// 1
			std::cout << num << "\n";
			std::string com = parser.getComandName(C);// read
			std::cout << com << "\n";
			std::vector<std::string> arg = parser.getArgs(C); //{"1.txt"}
//			std::cout << com << "\n";
			IWorker * worker = nullptr;
//			worker = inst[com];

			programm[num] = pair<IWorker*, vector<string>>(worker, arg);
		}
		
	}

	// validator

	size_t com_num = 0; //1->4->2->3


//	pair<IWorker*, vector<string>> & s = programm[com_num];
//	s.first->toDo(s.second);
/*
	int t = 4;
	std::ifstream some("instruction_list_name.txt");
	some >> t;

	std::cout << t << "\n";
*/
	system("pause");
	return 0;
}
