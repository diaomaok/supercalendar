#include"ViewFestival.hpp"
#include"ControllerFestival.hpp"
using namespace std;
int main() {
	ControllerFestival cf;
	int choice = 0;
	while (true) {
		cf.showMenu();
		cout << "请输入你的选择:" << endl;
		cin >> choice;
		switch (choice) {
		case 0:
			cf.ExitSystem();
			break;
		case 1:
			cf.AddFest();
			break;
		case 2:
			cf.Del_Fest();
			break;
		case 3:
			cf.Mod_Fest();
			break;
		case 4:
			cf.ShowCalender();
			break;
		case 5:
			cf.Show_Fest();
			break;
		case 6:
			cf.FestivalToNow();
			break;
		case 7:
			cf.Find_Fest();
			break;
		case 8:
			cf.Sort_Fest();
			break;
		default:
			cout << "输入有误,请重新输入" << endl;
			system("pause");
			system("cls");
			break;
		}
	}



	system("pause");
	return 0;

}