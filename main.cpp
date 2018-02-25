#include <iostream>
#include <map>
#include <string>
using namespace std;

/*class StartMenu
{
public:
	//This is a basic interface
	void start()
	{
		cout << "Hello, new guest\n";
		cout << "Please choose your pizza\n";
		cout << "We have 3 size of pizza\n";
	}
};
*/

class Ingridient
{
private:
	string name;
public:
	Ingridient(string name1)
	{
		name = name1;
		// был добавлен ингридиент name
	}
	bool operator<(const Ingridient& ingr)
	{
		return name > ingr.name;
	}
};


class CPizza
{
	// Пицца хранится в виде map ингридиентов в неё входящих
public:
	map <Ingridient, int> Sostav;
	string size;
	string name;
	CPizza()
	{

	}
	void add_new_ingridient(Ingridient name1, int cnt)
	{
		Sostav[name1] = cnt;
		// Добавление ингридиента name1 в количестве cnt
	}
	void del_old_ingridient(Ingridient name1, int cnt)
	{
		Sostav.erase(name1);
		//Если ингридиент присутствует в нужном количестве, то удалить,
		//иначе выдать сообщение об ошибке
	}
	void write_ingridients()
	{
		cout << "Список ингридиентов\n";
		// Выдаёт список ингридиентов, входящих в пиццу
		//for (auto it = Sostav.begin(); it != Sostav.end(); it++)
		//{
			//cout << (*it).first.name << ' ' << (*it).second << "\n";
		//}
	}
};

class CPizzaBuilder
{
protected:
	CPizza* cur_pizza;
public:
	virtual ~CPizzaBuilder()
	{

	}
	CPizza* create()
	{
		cur_pizza = new CPizza;
		return cur_pizza;
	}
	virtual void build_meat() = 0;
	virtual void build_cheese() = 0;
	virtual void build_tomatoes() = 0;
	virtual void build_mushrooms() = 0;
	virtual void build_name() = 0;
};

class CPizzaSizeFactory
{
public:
	CPizza* pizza;
	CPizzaSizeFactory()
	{

	}
	~CPizzaSizeFactory()
	{

	}
	virtual void SetSize() = 0;
};

class CPizzaBigFactory: public CPizzaSizeFactory
{
public:
	CPizzaBigFactory(CPizza* pizza1)
	{
		pizza = pizza1;
	}
	void SetSize()
	{
		pizza->size = "Big";
		cout << "There is a big pizza\n";
	}
};

class CPizzaMiddleFactory : public CPizzaSizeFactory
{
public:
	CPizzaMiddleFactory(CPizza* pizza1)
	{
		pizza = pizza1;
	}
	void SetSize()
	{
		pizza->size = "Middle";
		cout << "There is a middle pizza\n";
	}
};

class CPizzaSmallFactory : public CPizzaSizeFactory
{
public:
	CPizzaSmallFactory(CPizza* pizza1)
	{
		pizza = pizza1;
	}
	void SetSize()
	{
		pizza->size = "Small";
		cout << "There is a small pizza\n";
	}
};

class CPizzaPepperoniBuilder: public CPizzaBuilder
{
	CPizzaPepperoniBuilder() : CPizzaBuilder()
	{

	}
	~CPizzaPepperoniBuilder()
	{

	}
	void build_meat()
	{
		cout << "было добавлено 100 грамм Пепперони\n";
		cur_pizza->add_new_ingridient(Ingridient("kolbaca Pepperoni"), 100);
	}
	void build_cheese()
	{
		cout << "было добавлено 200 грамм сыра Моцарелла\n";
		cur_pizza->add_new_ingridient(Ingridient("cheese Mocarela"), 200);
	}
	void build_tomatoes()
	{
		cout << "было добавлено 100 грамм томатов\n";
		cur_pizza->add_new_ingridient(Ingridient("tomatoes"), 100);
	}
	void build_name()
	{
		cout << "пицца называется Пепперони\n";
		cur_pizza->name = "Pepperoni";
	}
};

class CPizzaFourCheesesBuilder: public CPizzaBuilder
{
	CPizzaFourCheesesBuilder() : CPizzaBuilder()
	{

	}
	~CPizzaFourCheesesBuilder()
	{

	}
	void build_cheese()
	{
		cur_pizza->add_new_ingridient(Ingridient("cheese Mocarela"), 150);
		cur_pizza->add_new_ingridient(Ingridient("cheese Chedder"), 150);
		cur_pizza->add_new_ingridient(Ingridient("cheese Parmezan"), 150);
		cur_pizza->add_new_ingridient(Ingridient("cheese Dor-Blu"), 150);
		// был добавлен сыр Моцарелла
		// был добавлен сыр Чеддер
		// был добавлен сыр Пармезан
		// был добавлен сыр Пармезан
	}
	void build_name()
	{
		cout << "пицца называется 4 сыра\n";
		cur_pizza->name = "Four Cheeses";
	}
};

class CPizzaMargaritaBuilder: public CPizzaBuilder
{
	CPizzaMargaritaBuilder() : CPizzaBuilder()
	{

	}
	~CPizzaMargaritaBuilder()
	{
		cout << "Пицца Маргарита была удалена\n";
	}
	void build_cheese()
	{
		cur_pizza->add_new_ingridient(Ingridient("cheese Mocarela"), 200);
	}
	void build_tomatoes()
	{
		cur_pizza->add_new_ingridient(Ingridient("tomatoes"), 100);
	}
	void build_name()
	{
		cout << "пицца называется Маргарита\n";
		cur_pizza->name = "Margarita";
	}
};

class User
{
private:
	CPizza* Pizza_name;
	CPizzaBuilder* builder_name;
public:
	User()
	{
		Pizza_name = NULL;
		builder_name = NULL;
	}
	~User()
	{
	}
	void set_pizza_builder(CPizzaBuilder* qwer)
	{
		builder_name = qwer;
	}
	string pizza_name()
	{
		cout << Pizza_name << "\n";
		return Pizza_name->name;
	}
	void Create_Pizza(string size_of_pizza)
	{
		Pizza_name = builder_name->create();
		builder_name->build_meat();
		builder_name->build_cheese();
		builder_name->build_tomatoes();
		builder_name->build_mushrooms();
		builder_name->build_name();
		if (size_of_pizza == "Small")
		{
			CPizzaSmallFactory factory(Pizza_name);
			(&factory)->SetSize(); 
		}
		if (size_of_pizza == "middle")
		{
			CPizzaMiddleFactory factory(Pizza_name);
			(&factory)->SetSize();
		}
		if (size_of_pizza == "big")
		{
			CPizzaBigFactory factory(Pizza_name);
			(&factory)->SetSize();
		}
	}
};
