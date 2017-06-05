#include <iostream>
#include <string>
#include <vector>
//#include  <clocale>
namespace appinterface
{

	template <typename T>
	 void ShowMessage(T msg)
	{
		T temp;
		temp =msg;
		std::cout << temp<<"\n";
	};

	template <typename T>
	 void ShowMessage(std::vector<T> MessageVector)
	{
		for each (T temp in MessageVector)
		{
			std::cout << "<Vector>" <<temp<<"</Vector>"<<"\n";
		}
	
	};
	 char GetInput_Keyboard()
	 {
		 char c;
		 std::cin >> c;
		 return c;
	 
	 };
	 class  Menu
	 {
	 private:
		 std::string menu_Title="Menu";
		 std::vector<std::string>Items;
		 void ReadItems();
	 public:
		 Menu(){};
		 ~Menu();
		 Menu& operator= (Menu const&) = delete;
		 void AddItem(std::string);
		 std::string GetTitle() { return menu_Title; };
		 void SetTitle(std::string _name) { this->menu_Title = _name; }
		 void CreateMenu();
		 Menu ReturnMenu(Menu);
		 static Menu& getInstance()
		 {

			 static Menu instance;

			 return instance;
		 }
		 enum menutype
		 {
			 default, simple

		 };
		 Menu(menutype);

	 };
	Menu Menu::ReturnMenu(Menu m)
	 {
		 return m;
	 
	 }
	

	 Menu::Menu(Menu::menutype mt)
	 {

		 switch (mt)
		 {
		 case appinterface::Menu::default:
			 break;
		 case appinterface::Menu::simple:
			 break;
		 default:
			 break;
		 }
	 }

	 Menu::~Menu()
	 {

	 }
	void Menu::ReadItems()
	 {
		 int i=1;
		 for each (std::string temptitle in Items)
		 {
			 std::cout << i << ":" << temptitle << "\n";
			 i++;
		 }
		
	 }
	 void Menu::CreateMenu()
	 {
		 
		 std::cout << "----" << menu_Title << "----" << "\n";
		 ReadItems();
	 
	 }
	 void Menu::AddItem(std::string item)
	 {
		 Items.push_back(item);
	 };
	
}