// Patterns.cpp: определяет точку входа для консольного приложения.

#include "stdafx.h"
#include "CreationalPatterns.h"
#include "AppInterface.h"
#include "Loger.h"
#include "StructuralPatterns.h"
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include  <clocale>
#include "BehaviorPatterns.h"
#include "MyPatterns.h"
using namespace CreationalPatterns;
using namespace StructuralPatterns;
using namespace BehaviorPatterns;
using namespace std;
using namespace appinterface;
using namespace MyPatterns;
void AbstractPaternsT()
{
	//AbstractFactory::EntityAFactory* _Afactory = new AbstractFactory::EntityAFactory;
	//vector<AbstractFactory::AbstractEntity*> ae;
	vector<Prototype::Entity*> pe;
	//ae.push_back(AbstractFactory::AbstractEntity::createObject(AbstractFactory::AbstractEntity::object1, "Jopa"));
	//ae.push_back(AbstractFactory::AbstractEntity::createObject(AbstractFactory::AbstractEntity::object2));
	//ae.push_back(_Afactory->FactoryObject());
	pe.push_back(Prototype::Entity::createEntity(Prototype::Entity1_ID));
	//ShowMessage(ae[0]->info());
	//ShowMessage(ae[1]->info());
	//ShowMessage(ae[2]->info());
	//ae[2]->SetName("ReName");
	//ShowMessage(ae[2]->info());
	/*Builder::Director dir;
	Builder::ExampleBuilderA ra_builder;
	Builder::ExampleBuilderB ca_builder;
	Builder::Parts *ra = dir.DeployParts(ra_builder);
	Builder::Parts *ca = dir.DeployParts(ca_builder);
	ShowMessage(ra->info());
	ShowMessage(ca->info());*/
	ShowMessage(pe[0]->info());
	//ShowMessage(pe[1]->info());


};
int ObjectPoolT()
{
	ObjectPool::ObjectPool pool;
	for (size_t i = 0; i < 1000; ++i)
	{
		ObjectPool::Object* object = pool.AddToPool();
	
		pool.ReturnObject(object);

	}
	return pool.GetPoolSize();
};
void LoggerT()
{
	Logger * p = new FileLogger(string("log.txt"));
	p->log(string("message"));
	delete p;

};
void DecoratorT()
{
	
	Decorator::DecoratorTwo obj(new Decorator::DecoratorOne(new Decorator::Component()));
	obj.operation(); // prints "Hello, World!\n"
};
void FacadeT()
{
	Facade::FacilitiesFacade facilities;
	facilities.submitNetworkRequest();
	/* Звоним, пока работа не выполнена полностью */
	while (!facilities.checkOnStatus());
	ShowMessage("job completed after");
	ShowMessage(facilities.getNumberOfCalls());
	ShowMessage("tasks");
};
void FlyWeightT()
{
	for (int i = 0; i < FlyWeight::Factory::X; ++i)
	{
		for (int j = 0; j < FlyWeight::Factory::Y; ++j)
			ShowMessage(FlyWeight::Factory::get_fly(i)->report(j));

	}
	FlyWeight::Factory::clean_up();

};
void ProxyT()
{
	Proxy::ProxySubject obj(string("the quick brown fox jumped over the dog"));
	ShowMessage(obj->execute());
	ShowMessage(obj.execute());

};
void ChainT()
{
	srand(0);
	ChainOfResponsible::Handler1 root;
	ChainOfResponsible::Handler2 two;
	ChainOfResponsible::Handler3 thr;
	root.add(&two);
	root.add(&thr);
	thr.setNext(&root);
	for (int i = 1; i < 10; i++)
	{
		root.handle(i);
		cout << '\n';
	}


};
void CommandT()
{
	Command::Game game;
	// Имитация действий игрока
	vector<Command::Command*> v;
	// Создаем новую игру 
	v.push_back(new Command::CreateGameCommand(&game));
	// Делаем несколько ходов
	v.push_back(new Command::MakeMoveCommand(&game));
	v.push_back(new Command::MakeMoveCommand(&game));
	// Последний ход отменяем
	v.push_back(new Command::UndoCommand(&game));
	// Сохраняем игру
	v.push_back(new Command::SaveGameCommand(&game));

	for (size_t i = 0; i < v.size(); ++i)
		v[i]->execute();

	for (size_t i = 0; i < v.size(); ++i)
		delete v[i];

};
void InterpreterT()
{
	Interpreter::RNInterpreter interpreter;
	char input[20];
	ShowMessage("Enter Roman Numeral: ");
	cin >> input;
	ShowMessage(interpreter.interpret(input));

}
void MediatorT()
{
	Mediator::List lst;
	Mediator::Node one(11), two(22);
	Mediator::Node thr(33), fou(44);
	lst.add_node(&one);
	lst.add_node(&two);
	lst.add_node(&thr);
	lst.add_node(&fou);
	lst.traverse();
	lst.remove_node(44);
	lst.traverse();
	lst.remove_node(22);
	lst.traverse();
	lst.remove_node(11);
	lst.traverse();

};
void MementoT()
{
	Memento::Originator org;
	org.setState(1);
	org.dumpState();

	Memento::Originator::Memento* m1 = org.getMemento();

	org.setState(2);
	org.dumpState();

	m1->restoreState();
	org.dumpState();
};
void ObserverT()
{
	Observer::SupervisedString str;
	Observer::Reflector refl;
	Observer::Counter cnt;

	str.add(refl);
	str.reset("Hello, World!");
	cout << endl;

	str.remove(refl);
	str.add(cnt);
	str.reset("World, Hello!");
	cout << endl;

};
void StateT()
{
	State::WebCamera cam(0);


	// cam в Состоянии NotConnectedState
	cam.connect();
	// cam в Состоянии ReadyState
	cam.start();
	// cam в Состоянии ActiveState
	std::cout << cam.getFrame() << std::endl;
	cam.stop(); // Можно было сразу вызвать disconnect()
	// cam в Состоянии ReadyState
	cam.disconnect();
	// cam в Состоянии NotConnectedState
};
void StrategyT()
{
	Strategy::Compressor* p = new Strategy::Compressor(new Strategy::ZIP_Compression);
	p->compress("file.txt");
	delete p;
};
void TemplateMethodT()
{
	TemplateMethod::Base *array[] =
	{
		&TemplateMethod::One(), &TemplateMethod::Two()
	};
	for (int i = 0; i < 2; i++)
	{
		array[i]->execute();
		cout << '\n';
	}
};
void VisitorT()
{
	Visitor::Foo foo; Visitor::Bar bar; Visitor::Baz baz;
	Visitor::Element*elements[] = { &foo, &bar, &baz };
	for (size_t i = 0; i < lenof(elements); i++)
	{
		Visitor::GetType visitor;
		elements[i]->accept(visitor);
		ShowMessage(visitor.value);
	}
};
void GrowerT()
{
	Grower::Seed seed;
	Grower::GrowCondition* gc = new Grower::GrowCondition(&seed);
	//ShowMessage(gc->GrowUp());

	clock_t startTime = clock(); //Start timer
	double secondsPassed;
	int i = 0;
	bool flag = true;
	while (!seed.conditioned)
	{
		i++;
		secondsPassed = (clock() - startTime) / CLOCKS_PER_SEC;
		ShowMessage(i);
		gc->GrowUp(i);
		


	}
	ShowMessage(seed.test);
	ShowMessage(secondsPassed);


};
void TreeT()
{
	BinaryTree::Tree<int> intTree;           /* создаем новой бинароное дерево с ключем типа int */
	int a;
	cout << "4 numbers:" << endl;   /* заполняем его */
	for (int i = 0; i<4; i++)
	{
		cin >> a;
		intTree.insert_node(a);
	}
	cout << endl << "inorder_walk:" << endl;              /* обходим */
	intTree.inorder_walk(intTree.get_root());       /* вот для этого понадобился метод get_root() :-) */
	cout << endl << "Minimum is: " << (intTree.find_min(intTree.get_root()))->get_data() << endl;
	cout << endl << "Maximum is: " << (intTree.find_max(intTree.get_root()))->get_data() << endl;
	cout << "Enter node value U want to delete:";     /* попробуем удалить узел с ключем a */
	cin >> a;
	intTree.delete_node(intTree.find_node(intTree.get_root(), a));    /* если их несколько, то удалится первй найденный */
	cout << endl << "Now inorder_walk:" << endl;
	intTree.inorder_walk(intTree.get_root());
}
void NTreeT()
{
	
	
	//LightQuest.ShowStandInfo(1);
	//LightQuest.ShowStandInfo(2);
	
	
//	cout << "---------------------"<<'\n';
	
	//sec1.ShowBookInfo("A");

}
void References()
{
	int a = 10;
	int* p = &a;
	int b = *p;
	ShowMessage(b);
};
int _tmain(int argc, _TCHAR* argv[])
{
	std::setlocale(LC_ALL, "Russian");
	Singletons::StateController& sc = Singletons::StateController::getInstance();//Singleton example
	sc.SwitchButton(Singletons::StateController::on);
	appinterface::Menu& menu = appinterface::Menu::getInstance();
	menu.AddItem("Abstract Paterns");
	menu.AddItem("Object pool");
	menu.AddItem("Loger");
	menu.AddItem("Decorator");
	menu.AddItem("Facade");
	menu.AddItem("FlyWeight");
	menu.AddItem("Proxy");
	menu.AddItem("Chain");
	menu.AddItem("Command");
	menu.AddItem("Interpreter(i)");
	menu.AddItem("Mediator(m)");
	menu.AddItem("Memento(e)");
	menu.AddItem("Observer(o)");
	menu.AddItem("State(s)");
	menu.AddItem("Strategy(y)");
	menu.AddItem("Template(t)");
	menu.AddItem("Visitor(v)");
	menu.AddItem("References(f)");
	menu.AddItem("Grower(g)");
	menu.AddItem("Combine(n)");
	menu.AddItem("Forge(z)");
	menu.AddItem("Tree(q)");
	menu.CreateMenu();
	while (sc._state == 0)
	{
		switch (GetInput_Keyboard())
		{
		case '1':
		{
			/***************Abstract Patterns****************/
			sc.SwitchButton(Singletons::StateController::pause);
			AbstractPaternsT();
			sc.SwitchButton(Singletons::StateController::on);
			break;
		}
		case '2':
		{
			/***************Object Pool****************/
			sc.SwitchButton(Singletons::StateController::pause);
			ShowMessage(ObjectPoolT());
			sc.SwitchButton(Singletons::StateController::on);
			break;
		}
		case '3':
		{
			/***************Loger****************/

			sc.SwitchButton(Singletons::StateController::pause);
			LoggerT();
			sc.SwitchButton(Singletons::StateController::on);
			break;
		}
		case '4':
		{
			/***************Decorator****************/
			sc.SwitchButton(Singletons::StateController::pause);
			DecoratorT();
			sc.SwitchButton(Singletons::StateController::on);
			break;
		}
		//default:
		case '5':
		{
			/***************Facade****************/
			sc.SwitchButton(Singletons::StateController::pause);
			FacadeT();
			sc.SwitchButton(Singletons::StateController::on);
			break;
		}
		case '6':
		{
			/***************FlyWeight****************/
			sc.SwitchButton(Singletons::StateController::pause);
			FlyWeightT();
			sc.SwitchButton(Singletons::StateController::on);
			break;
		}
		case '7':
		{
			/***************Proxy****************/
			sc.SwitchButton(Singletons::StateController::pause);
			ProxyT();
			sc.SwitchButton(Singletons::StateController::on);
			break;
		}
		case '8':
		{
			/***************Chain****************/
			sc.SwitchButton(Singletons::StateController::pause);
			ChainT();
			sc.SwitchButton(Singletons::StateController::on);
			break;
		}
		case '9':
		{
			/***************Command****************/
			sc.SwitchButton(Singletons::StateController::pause);
			CommandT();
			sc.SwitchButton(Singletons::StateController::on);
			break;
		}
		case 'i':
		{
			/***************Interpreter****************/
			sc.SwitchButton(Singletons::StateController::pause);
			InterpreterT();
			sc.SwitchButton(Singletons::StateController::on);
			break;
		}
		case 'm':
		{
			/***************Mediator****************/
			sc.SwitchButton(Singletons::StateController::pause);
			MediatorT();
			sc.SwitchButton(Singletons::StateController::on);
			break;
		}
		case 'e':
		{
			/***************Memento****************/
			sc.SwitchButton(Singletons::StateController::pause);
			MementoT();
			sc.SwitchButton(Singletons::StateController::on);
			break;
		}
		case 'o':
		{
			/***************Observer****************/
			sc.SwitchButton(Singletons::StateController::pause);
			ObserverT();
			sc.SwitchButton(Singletons::StateController::on);
			break;
		}
		case 's':
		{
			/***************State****************/
			sc.SwitchButton(Singletons::StateController::pause);
			StateT();
			sc.SwitchButton(Singletons::StateController::on);
			break;
		}
		case 'y':
		{
			/***************Strategy****************/
			sc.SwitchButton(Singletons::StateController::pause);
			StrategyT();
			sc.SwitchButton(Singletons::StateController::on);
			break;
		}
		case 't':
		{
			/***************TemplateMethod****************/
			sc.SwitchButton(Singletons::StateController::pause);
			TemplateMethodT();
			sc.SwitchButton(Singletons::StateController::on);
			break;
		}
		case 'v':
		{
			/***************Visitor****************/
			sc.SwitchButton(Singletons::StateController::pause);
			VisitorT();
			sc.SwitchButton(Singletons::StateController::on);
			break;
		}
		case 'f':
		{
			/***************References****************/
			sc.SwitchButton(Singletons::StateController::pause);
			References();
			sc.SwitchButton(Singletons::StateController::on);
			ShowMessage('c');
			break;
		}
		case 'g':
		{
			/***************Grower****************/
			sc.SwitchButton(Singletons::StateController::pause);
			GrowerT();
			sc.SwitchButton(Singletons::StateController::on);
			break;
		}
		case 'n':
		{
			/***************Combine****************/
			sc.SwitchButton(Singletons::StateController::pause);
			Combine::ICombined ic;
			ShowMessage(ic.Combine());
			sc.SwitchButton(Singletons::StateController::on);
			break;
		}
		case 'z':
		{
			/***************Forge****************/
			sc.SwitchButton(Singletons::StateController::pause);
			Forge::Iron ir;
			Forge::Molot * molot = new Forge::Molot(&ir);
			molot->ChangeProperties();

			Forge::Material* p=molot->CreateOutputMaterial();
			cout << typeid(*p).name();
			 molot->pplas.MakePlane();
			 cout << molot->pplas.prop;
			sc.SwitchButton(Singletons::StateController::on);
			break;
		}
		case 'q':
		{
			/***************Tree****************/
			sc.SwitchButton(Singletons::StateController::pause);
			TreeT();
			sc.SwitchButton(Singletons::StateController::on);
			break;
		}
	


		}
		menu.CreateMenu();
	}
	//system("pause");
	return 0;
}
