#include"ViewFestival.hpp"
#include"ControllerFestival.hpp"
using namespace std;
int main() {
	ControllerFestival cf;
	int choice = 0;
	while (true) {
		cf.showMenu();
		cout << "���������ѡ��:" << endl;
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
			cout << "��������,����������" << endl;
			system("pause");
			system("cls");
			break;
		}
	}



	system("pause");
	return 0;

}