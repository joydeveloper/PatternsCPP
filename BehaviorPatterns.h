
#include <cstdlib> 
#include <iostream>
#include <vector>
#include <list>
using namespace std;
namespace BehaviorPatterns
{
	namespace ChainOfResponsible
	{
		class Base
		{
			// 1. Указатель "next" в базовом классе
			Base *next;
		public:
			Base()
			{
				next = 0;
			}
			void setNext(Base *n)
			{
				next = n;
			}
			void add(Base *n)
			{
				if (next)
					next->add(n);
				else
					next = n;
			}
			// 2. Метод базового класса, делегирующий запрос next-объекту
			virtual void handle(int i)
			{
				next->handle(i);
			}
		};

		class Handler1 : public Base
		{
		public:
			/*virtual*/void handle(int i)
			{
				if (std::rand() % 3)
				{
					// 3. 3 из 4 запросов не обрабатываем

					// 3. и делегируем базовому классу
					Base::handle(i);
				}
				else
					std::cout << "H1 handled " << i << "  ";
			}
		};

		class Handler2 : public Base
		{
		public:
			/*virtual*/void handle(int i)
			{
				if (std::rand() % 3)
				{
					std::cout << "H2 passsed " << i << "  ";
					Base::handle(i);
				}
				else
					std::cout << "H2 handled " << i << "  ";
			}
		};

		class Handler3 : public Base
		{
		public:
			/*virtual*/void handle(int i)
			{
				if (std::rand() % 3)
				{
					std::cout << "H3 passsed " << i << "  ";
					Base::handle(i);
				}
				else
					std::cout << "H3 handled " << i << "  ";
			}
		};

	}
	namespace Command
	{
		class Game
		{
		public:
			void create() {
				cout << "Create game " << endl;
			}
			void open(string file) {
				cout << "Open game from " << file << endl;
			}
			void save(string file) {
				cout << "Save game in " << file << endl;
			}
			void make_move(string move) {
				cout << "Make move " << move << endl;
			}
		};

		string getPlayerInput(string prompt) {
			string input;
			cout << prompt;
			cin >> input;
			return input;
		}

		// Базовый класс
		class Command
		{
		public:
			virtual ~Command() {}
			virtual void execute() = 0;
		protected:
			Command(Game* p) : pgame(p) {}
			Game * pgame;
		};

		class CreateGameCommand : public Command
		{
		public:
			CreateGameCommand(Game * p) : Command(p) {}
			void execute() {
				pgame->create();
			}
		};

		class OpenGameCommand : public Command
		{
		public:
			OpenGameCommand(Game * p) : Command(p) {}
			void execute() {
				string file_name;
				file_name = getPlayerInput("Enter file name:");
				pgame->open(file_name);
			}
		};

		class SaveGameCommand : public Command
		{
		public:
			SaveGameCommand(Game * p) : Command(p) {}
			void execute() {
				string file_name;
				file_name = getPlayerInput("Enter file name:");
				pgame->save(file_name);
			}
		};

		class MakeMoveCommand : public Command
		{
		public:
			MakeMoveCommand(Game * p) : Command(p) {}
			void execute() {
				// Сохраним игру для возможного последующего отката
				pgame->save("TEMP_FILE");
				string move;
				move = getPlayerInput("Enter your move:");
				pgame->make_move(move);
			}
		};

		class UndoCommand : public Command
		{
		public:
			UndoCommand(Game * p) : Command(p) {}
			void execute() {
				// Восстановим игру из временного файла
				pgame->open("TEMP_FILE");
			}
		};
	}
	namespace Interpreter
	{
		class Thousand;
		class Hundred;
		class Ten;
		class One;

		class RNInterpreter
		{
		public:
			RNInterpreter(); // ctor for client
			RNInterpreter(int){}
			// ctor for subclasses, avoids infinite loop
			int interpret(char*); // interpret() for client
			virtual void interpret(char *input, int &total)
			{
				// for internal use
				int index;
				index = 0;
				if (!strncmp(input, nine(), 2))
				{
					total += 9 * multiplier();
					index += 2;
				}
				else if (!strncmp(input, four(), 2))
				{
					total += 4 * multiplier();
					index += 2;
				}
				else
				{
					if (input[0] == five())
					{
						total += 5 * multiplier();
						index = 1;
					}
					else
						index = 0;
					for (int end = index + 3; index < end; index++)
						if (input[index] == one())
							total += 1 * multiplier();
						else
							break;
				}
				strcpy_s(input,20, &(input[index]));
			} // remove leading chars processed
		protected:
			// cannot be pure virtual because client asks for instance
			virtual char one(){ return 0; }
			virtual char *four(){ return 0; }
			virtual char five(){ return 0; }
			virtual char *nine(){ return 0; }
			virtual int multiplier(){ return 0; }
		private:
			RNInterpreter *thousands;
			RNInterpreter *hundreds;
			RNInterpreter *tens;
			RNInterpreter *ones;
		};

		class Thousand : public RNInterpreter
		{
		public:
			// provide 1-arg ctor to avoid infinite loop in base class ctor
			Thousand(int) : RNInterpreter(1){}
		protected:
			char one()
			{
				return 'M';
			}
			char *four()
			{
				return "";
			}
			char five()
			{
				return '\0';
			}
			char *nine()
			{
				return "";
			}
			int multiplier()
			{
				return 1000;
			}
		};

		class Hundred : public RNInterpreter
		{
		public:
			Hundred(int) : RNInterpreter(1){}
		protected:
			char one()
			{
				return 'C';
			}
			char *four()
			{
				return "CD";
			}
			char five()
			{
				return 'D';
			}
			char *nine()
			{
				return "CM";
			}
			int multiplier()
			{
				return 100;
			}
		};

		class Ten : public RNInterpreter
		{
		public:
			Ten(int) : RNInterpreter(1){}
		protected:
			char one()
			{
				return 'X';
			}
			char *four()
			{
				return "XL";
			}
			char five()
			{
				return 'L';
			}
			char *nine()
			{
				return "XC";
			}
			int multiplier()
			{
				return 10;
			}
		};

		class One : public RNInterpreter
		{
		public:
			One(int) : RNInterpreter(1){}
		protected:
			char one()
			{
				return 'I';
			}
			char *four()
			{
				return "IV";
			}
			char five()
			{
				return 'V';
			}
			char *nine()
			{
				return "IX";
			}
			int multiplier()
			{
				return 1;
			}
		};

		RNInterpreter::RNInterpreter()
		{
			// use 1-arg ctor to avoid infinite loop
			thousands = new Thousand(1);
			hundreds = new Hundred(1);
			tens = new Ten(1);
			ones = new One(1);
		}

		int RNInterpreter::interpret(char *input)
		{
			int total;
			total = 0;
			thousands->interpret(input, total);
			hundreds->interpret(input, total);
			tens->interpret(input, total);
			ones->interpret(input, total);
			if (strcmp(input, ""))
				// if input was invalid, return 0
				return 0;
			return total;
		}
	}
	namespace Iterator
	{
//use std::iterator
	}
	namespace Mediator
	{
		class Node
		{
		public:
			Node(int v)
			{
				m_val = v;
			}
			int get_val()
			{
				return m_val;
			}
		private:
			int m_val;
		};

		class List
		{
		public:
			void add_node(Node *n)
			{
				m_arr.push_back(*n);
			}
			void traverse()
			{
				for (int i = 0; i < m_arr.size(); ++i)
					cout << m_arr[i].get_val() << "  ";
				cout << '\n';
			}
			void remove_node(int v)
			{
				for (vector<Node>::iterator it = m_arr.begin();
					it != m_arr.end(); ++it)
					if ((it)->get_val() == v)
					{
						m_arr.erase(it);
						break;
					}
			}
		private:
			vector<Node> m_arr;
		};

	}
	namespace Memento
	{
		class Originator {

			int state;

		public:

			Originator();

			class Memento;

			Memento* getMemento();
			void setState(int);
			void dumpState();

			class Memento {

				friend class Originator;

			private:

				int state;
				Originator* org;

			public:

				Memento();
				void restoreState();

			};


		};

		Originator::Originator() : state(0) {

		}

		void Originator::setState(int s) {
			state = s;
		}

		void Originator::dumpState() {
			cout << "State: " << state << endl;
		}

		Originator::Memento::Memento() : state(0) {

		}

		Originator::Memento* Originator::getMemento() {
			Originator::Memento* m = new Originator::Memento();
			m->org = this;
			m->state = state;
			return m;
		}


		void Originator::Memento::restoreState() {

			org->state = state;
		}
	}
	namespace Observer
	{
		class SupervisedString;
		class IObserver
		{
		public:
			virtual void handleEvent(const SupervisedString&) = 0;
		};

		class SupervisedString // Observable class
		{
			string _str;
			list<IObserver*> _observers;

			void _Notify()
			{
				for (auto iter : _observers)
				{
					iter->handleEvent(*this);
				}
			}

		public:
			void add(IObserver& ref)
			{
				_observers.push_back(&ref);
			}

			void remove(IObserver& ref)
			{
				_observers.remove(&ref);
			}

			const string& get() const
			{
				return _str;
			}

			void reset(string str)
			{
				_str = str;
				_Notify();
			}
		};

		class Reflector : public IObserver // Prints the observed string into cout
		{
		public:
			virtual void handleEvent(const SupervisedString& ref)
			{
				cout << ref.get() << endl;
			}
		};

		class Counter : public IObserver // Prints the length of observed string into cout
		{
		public:
			virtual void handleEvent(const SupervisedString& ref)
			{
				cout << "length = " << ref.get().length() << endl;
			}
		};
	}
	namespace State
	{
#define DECLARE_GET_INSTANCE( ClassName ) \
    static ClassName* getInstance() {\
        static ClassName instance;\
        return &instance;\
	    }


		class WebCamera {
		public:
			typedef std::string Frame;

		public:
			// **************************************************
			// Exceptions
			// **************************************************

			class NotSupported : public std::exception { };

		public:
			// **************************************************
			// States
			// **************************************************

			class NotConnectedState;
			class ReadyState;
			class ActiveState;

			class State {
			public:
				virtual ~State() { }

				virtual void connect(WebCamera*) {
					throw NotSupported();
				}

				virtual void disconnect(WebCamera* cam) {
					std::cout << "Деинициализируем камеру..." << std::endl;
					// ...

					cam->changeState(NotConnectedState::getInstance());
				}

				virtual void start(WebCamera*) {
					throw NotSupported();
				}

				virtual void stop(WebCamera*) {
					throw NotSupported();
				}

				virtual Frame getFrame(WebCamera*) {
					throw NotSupported();
				}

			protected:
				State() { }

			};

			// **************************************************
			class NotConnectedState : public State {
			public:
				DECLARE_GET_INSTANCE(NotConnectedState)

				void connect(WebCamera* cam) {
					std::cout << "Инициализируем камеру..." << std::endl;
					// ...

					cam->changeState(ReadyState::getInstance());
				}

				void disconnect(WebCamera*) {
					throw NotSupported();
				}

			private:
				NotConnectedState() { }
			};

			// **************************************************
			class ReadyState : public State {
			public:
				DECLARE_GET_INSTANCE(ReadyState)

				void start(WebCamera* cam) {
					std::cout << "Запускаем видео-поток..." << std::endl;
					// ...

					cam->changeState(ActiveState::getInstance());
				}

			private:
				ReadyState() { }
			};

			// **************************************************
			class ActiveState : public State {
			public:
				DECLARE_GET_INSTANCE(ActiveState)

				void stop(WebCamera* cam) {
					std::cout << "Останавливаем видео-поток..." << std::endl;
					// ...

					cam->changeState(ReadyState::getInstance());
				}

				Frame getFrame(WebCamera*) {
					std::cout << "Получаем текущий кадр..." << std::endl;
					// ...

					return "Current frame";
				}

			private:
				ActiveState() { }
			};

		public:
			explicit WebCamera(int camID) :
				m_camID(camID),
				m_state(NotConnectedState::getInstance()) {
			}

			~WebCamera() {
				try {
					disconnect();
				}
				catch (const NotSupported& e) {
					// Обрабатываем исключение
				}
				catch (...) {
					// Обрабатываем исключение
				}
			}

			void connect() {
				m_state->connect(this);
			}

			void disconnect() {
				m_state->disconnect(this);
			}

			void start() {
				m_state->start(this);
			}

			void stop() {
				m_state->stop(this);
			}

			Frame getFrame() {
				return m_state->getFrame(this);
			}

		private:
			void changeState(State* newState) {
				m_state = newState;
			}

		private:
			int m_camID;
			State* m_state;

		};
	}
	namespace Strategy
	{
		class Compression
		{
		public:
			virtual ~Compression() {}
			virtual void compress(const string & file) = 0;
		};

		class ZIP_Compression : public Compression
		{
		public:
			void compress(const string & file) {
				cout << "ZIP compression" << endl;
			}
		};

		class ARJ_Compression : public Compression
		{
		public:
			void compress(const string & file) {
				cout << "ARJ compression" << endl;
			}
		};

		class RAR_Compression : public Compression
		{
		public:
			void compress(const string & file) {
				cout << "RAR compression" << endl;
			}
		};


		// Класс для использования
		class Compressor
		{
		public:
			Compressor(Compression* comp) : p(comp) {}
			~Compressor() { delete p; }
			void compress(const string & file) {
				p->compress(file);
			}
		private:
			Compression* p;
		};
	}
	namespace TemplateMethod
	{
		class Base
		{
			void a()
			{
				cout << "a  ";
			}
			void c()
			{
				cout << "c  ";
			}
			void e()
			{
				cout << "e  ";
			}
			// 2. Для шагов, требующих особенной реализации, определите 
			//    "замещающие" методы.
			virtual void ph1() = 0;
			virtual void ph2() = 0;
		public:
			// 1. Стандартизуйте основу алгоритма в шаблонном методе 
			//    базового класса
			void execute()
			{
				a();
				ph1();
				c();
				ph2();
				e();
			}
		};

		class One : public Base
		{
			// 3. Производные классы реализуют "замещающие" методы.
			/*virtual*/void ph1()
			{
				cout << "b  ";
			}
			/*virtual*/void ph2()
			{
				cout << "d  ";
			}
		};

		class Two : public Base
		{
			/*virtual*/void ph1()
			{
				cout << "2  ";
			}
			/*virtual*/void ph2()
			{
				cout << "4  ";
			}
		};
	}
	namespace Visitor
	{
		template<typename TYPE, size_t COUNT>
		inline size_t lenof(TYPE(&)[COUNT]){ return COUNT; }

		class Foo;
		class Bar;
		class Baz;

		class Visitor{
		public:
			virtual void visit(Foo&ref) = 0;
			virtual void visit(Bar&ref) = 0;
			virtual void visit(Baz&ref) = 0;
		};

		class Element{
		public:
			virtual void accept(Visitor&v) = 0;
		};

		class Foo :public Element{
		public:
			void accept(Visitor&v){ v.visit(*this); }
		};

		class Bar :public Element{
		public:
			void accept(Visitor&v){ v.visit(*this); }
		};

		class Baz :public Element{
		public:
			void accept(Visitor&v){ v.visit(*this); }
		};

		class GetType :public Visitor{
		public:
			std::string value;
		public:
			void visit(Foo&ref){ value = "Foo"; }
			void visit(Bar&ref){ value = "Bar"; }
			void visit(Baz&ref){ value = "Baz"; }
		};
	}
}