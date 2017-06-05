#include <iostream>
#include <vector>
#include <assert.h>
#include <memory>
namespace StructuralPatterns
{
	namespace Adapter
	{

		class Target
		{
		public:
			virtual void Request()
			{

			}
		};
		class Adaptee
		{
		public:
			void SpecificRequest()
			{

			}
		};


		class Adapter : Target
		{
		private:
			Adaptee adaptee;

		public:
			virtual void Request()
			{

				adaptee.SpecificRequest();
			}
		};

	}
	namespace Composite
	{
		// Component 
		class Component
		{
		public:

			virtual void addComponent(Component* p) {
				assert(false);
			}
			virtual ~Component() {}
		};

		// Primitives
		class Primitive : public Component
		{


		};
		// Composite
		class CompositeComponent : public Component
		{
		private:
			std::vector<Component*> c;
		public:
			void addComponent(Component* p) {
				c.push_back(p);
			}
			~CompositeComponent() {
				for (int i = 0; i < c.size(); ++i)
					delete c[i];
			}

		};



	}
	namespace Decorator
	{
		class IComponent {
		public:
			virtual void operation() = 0;
			virtual ~IComponent(){}
		};

		class Component : public IComponent {
		public:
			virtual void operation() {
				std::cout << "World!" << std::endl;
			}
		};

		class DecoratorOne : public IComponent {
			std::shared_ptr<IComponent> m_component;

		public:
			DecoratorOne(IComponent* component) : m_component(component) {}

			virtual void operation() {
				std::cout << ", ";
				m_component->operation();
			}
		};

		class DecoratorTwo : public IComponent {
			std::shared_ptr<IComponent> m_component;

		public:
			DecoratorTwo(IComponent* component) : m_component(component) {}

			virtual void operation() {
				std::cout << "Hello";
				m_component->operation();
			}
		};

	}
	namespace Facade
	{
		class Work1
		{
		public:
			void submitNetworkRequest()
			{
				_state = 0;
			}
			bool checkOnStatus()
			{
				_state++;
				if (_state == Complete)
					return 1;
				return 0;
			}
		private:
			enum States
			{
				Received, Process, Complete
			};
			int _state;
		};

		class Work2
		{
		public:
			void submitNetworkRequest()
			{
				_state = 0;
			}
			bool checkOnStatus()
			{
				_state++;
				if (_state == Complete)
					return 1;
				return 0;
			}
		private:
			enum States
			{
				Received, Process,Complete
			};
			int _state;
		};


		class FacilitiesFacade
		{
		public:
			FacilitiesFacade()
			{
				_count = 0;
			}
			void submitNetworkRequest()
			{
				_state = 0;
			}
			bool checkOnStatus()
			{
				_count++;
				
			
			
				if (_state == Received)
				{
					_state++;
				
					_electrician.submitNetworkRequest();
				}
				else if (_state == Process)
				{
					
					if (_electrician.checkOnStatus())
					{
						_state++;
						
					
					}
				if (_state == SubmitToWork2)
					{
				
						
							return 1;
					}
				}
			
				
				return 0;
			}
			int getNumberOfCalls()

			{
				return _count;
			}
		private:
			enum States
			{
				Received, Process, SubmitToWork2
				
			};
			int _state;
			int _count;
			Work2 _electrician;
			Work1 _technician;
		};

	}
	namespace FlyWeight
	{
		class Gazillion
		{
		public:
			 Gazillion(int value_one)
			{
				m_value_one = value_one;
				
			}
			~Gazillion()
			{
				
			}
			int  report(int value_two)
			{
				return m_value_one;
			}
		private:
			int m_value_one;
		};

		class Factory
		{
		public:
			static Gazillion *get_fly(int in)
			{
				if (!s_pool[in])
					s_pool[in] = new Gazillion(in);
				return s_pool[in];
			}
			static void clean_up()
			{
				
				for (int i = 0; i < X; ++i)
					if (s_pool[i])
						delete s_pool[i];
				
			}
			static int X, Y;
		private:
			static Gazillion *s_pool[];
		};

		int Factory::X = 6, Factory::Y = 10;
		Gazillion *Factory::s_pool[] =
		{
			0, 0, 0, 0, 0, 0
		};

	}
	namespace Proxy
	{
		class Subject
		{
		public:
			virtual std::string execute()=0 ;
		};

		class RealSubject : public Subject
		{
			std::string str;
		public:
			RealSubject(std::string s)
			{
				str = s;
			}
			/*virtual*/std::string execute()
			{
				return str;
			}
		};

		class ProxySubject : public Subject
		{
			std::string first, second, third;
			RealSubject *ptr;
		public:
			ProxySubject(std::string s)
			{
				int num = s.find_first_of(' ');
				first = s.substr(0, num);
				s = s.substr(num + 1);
				num = s.find_first_of(' ');
				second = s.substr(0, num);
				s = s.substr(num + 1);
				num = s.find_first_of(' ');
				third = s.substr(0, num);
				s = s.substr(num + 1);
				ptr = new RealSubject(s);
			}
			~ProxySubject()
			{
				delete ptr;
			}
			RealSubject *operator->()
			{
			//ShowMessage(first);
				return ptr;
			}
			/*virtual*/std::string execute()
			{
				//ShowMessage(second);
				return ptr->execute();
			}
		};

	}
}