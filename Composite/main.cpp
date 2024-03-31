#include <iostream>
#include <vector>

using namespace std;

class IMenuComponent
{
public:
    virtual IMenuComponent* Get(int index) = 0;

    virtual void Add(IMenuComponent* menuComponent) = 0;

    virtual void Delete(int index) = 0;

    virtual void Print() = 0;

    virtual ~IMenuComponent() {}
};

class AbstractMenuComponent
    : public IMenuComponent
{
    vector<IMenuComponent*> _menus;
protected:
    AbstractMenuComponent() {}
public:
    virtual IMenuComponent* Get(int index) override
    {
        return _menus[index];
    }

    virtual void Add(IMenuComponent* menuComponent) override
    {
        _menus.push_back(menuComponent);
    }

    virtual void Delete(int index) override
    {
        _menus.erase(_menus.begin() + index);
    }

    virtual void Print() override
    {
        for (auto& val : _menus)
            val->Print();
    }
};

class MenuItem
    : public AbstractMenuComponent
{
    string _name;
    string _description;
    float _price;
public:
    MenuItem(string name, string description, float price)
        : _name(name)
        , _description(description)
        , _price(price)
    {
    }

    virtual void Print() override
    {
        cout << "Dish name: " << _name << endl;
        cout << "Description: " << _description << endl;
        cout << "Price: " << _price << endl << endl;

        AbstractMenuComponent::Print();
    }
};

class Menu
    : public AbstractMenuComponent
{
    string _menuName;
public:
    Menu(string menuName)
        : _menuName(menuName) {}

    virtual void Print() override
    {
        cout << "Menu: " << _menuName << endl << endl;

        AbstractMenuComponent::Print();
    }
};

class CafeMenu
{
    IMenuComponent* _allMenus;
public:
    CafeMenu(IMenuComponent* allMenus)
        : _allMenus(allMenus)
    {

    }

    void Print() 
    {
        _allMenus->Print();
    }
};


// The main purpose of this pattern is to use a Tree.
// Useful for creating desktop applications, like Qt takes 'QWidget* parent' parameter for its constructor to display this parent widget as a sub window.
int main()
{
    // Breakfast
    IMenuComponent* yogurt = new MenuItem("Yogurt", "Yogurt with strawberry", 1.5);
    IMenuComponent* coffee = new MenuItem("Coffee", "Coffe with milk", 1);
    IMenuComponent* tea = new MenuItem("tea", "Tea with sugar", 0.5);
    
    IMenuComponent* breakfast = new Menu("Breakfast");
    breakfast->Add(yogurt);
    breakfast->Add(coffee);
    breakfast->Add(tea);

    // Lunch
    IMenuComponent* steak = new MenuItem("Steak", "Beef stake", 3);
    IMenuComponent* macaroni = new MenuItem("Macaroni", "Macaroni with tomato", 1.9);
    
    IMenuComponent* lunch = new Menu("Lunch");
    lunch->Add(steak);
    lunch->Add(macaroni);



    // Dinner
    // Sub menu / Desserts
    IMenuComponent* iceCream= new MenuItem("Ice cream", "Chocolate ice cream", 2.4);
    IMenuComponent* donut = new MenuItem("Donut", "Chocolate Donut", 2.2);

    IMenuComponent* dinnerDesserts = new Menu("Dinner desserts");
    dinnerDesserts->Add(iceCream);
    dinnerDesserts->Add(donut);
    // Main dishes
    IMenuComponent* rabbit = new MenuItem("Rabbit", "Rabbit with mozzarella", 4);

    IMenuComponent* dinner = new Menu("Dinner");
    dinner->Add(rabbit);
    dinner->Add(dinnerDesserts);



    // All menus
    IMenuComponent* AllMenus = new Menu("Menu");
    AllMenus->Add(breakfast);
    AllMenus->Add(lunch);
    AllMenus->Add(dinner);



    // Cafe menu
    CafeMenu cafeMenu(AllMenus);
    cafeMenu.Print();
}