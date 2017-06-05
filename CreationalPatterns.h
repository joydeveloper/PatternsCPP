#include <string>
#include <vector>
#include <map>
namespace CreationalPatterns
{ 
namespace Singletons
{
	class Singleton
	{
	private:
		Singleton() {}
		Singleton(Singleton const&) = delete;
		Singleton& operator= (Singleton const&) = delete;
	public:

		static Singleton& getInstance()
		{

			static Singleton  instance;

			return instance;
		}
	};
	class StateController
	{
	private:
		StateController() {}
		StateController(const Singleton&);
		StateController & operator= (Singleton const&) = delete;
	public:
		static StateController& getInstance()
		{

			static StateController  instance;
			return instance;
		}
		enum state
		{
			on, off, restart, pause,
		} _state;
		int GetState()
		{
			return this->_state;

		}
		void SwitchButton(state st)
		{

			switch (st)
			{
			case CreationalPatterns::Singletons::StateController::on:
				SwitchOn();
				break;
			case CreationalPatterns::Singletons::StateController::off:
				SwitchOff();
				break;
			case CreationalPatterns::Singletons::StateController::restart:
				SwitchRestart();
				break;
			case CreationalPatterns::Singletons::StateController::pause:
				SwitchPause();
				break;
			default:
				break;
			}
		}
	private:
		void SwitchOn()
		{
			this->_state = state::on;
		}
		void SwitchOff()
		{
			this->_state = state::off;
		}
		void SwitchRestart()
		{
			this->_state = state::restart;
		}
		void SwitchPause()
		{
			this->_state = state::pause;
		}

	};
}
namespace AbstractFactory
{
    class AbstractEntity
	{

	public:
		enum Object_ID { object1, object2 };
		virtual std::string info() = 0;
		virtual ~AbstractEntity() {};
		std::string name;
		std::string GetName() { return name; };
		void SetName(std::string _name) { name = _name; }
		static AbstractEntity *createObject(Object_ID id, std::string _name);
		static AbstractEntity *createObject(Object_ID id);
	};

	class EntityA : public AbstractEntity
	{

	public:

		std::string info() { if (name != "") return name; else return "EntityA"; };

	};

	class EntityB : public AbstractEntity
	{
	public:
		std::string info() { if (name != "") return name; else return "EntityB"; };

	};
	AbstractEntity *AbstractEntity::createObject(Object_ID id, std::string _name)
	{
		AbstractEntity *p;
		switch (id)
		{
		case object1:
			p = new EntityA();
			p->SetName(_name);
			return p;
			break;
		case object2:
			p = new EntityB();
			p->SetName(_name);
			return p;

			break;

		default:
			return NULL;
			break;
		}
		delete[]p;
	}
	AbstractEntity *AbstractEntity::createObject(Object_ID id)
	{

		switch (id)
		{
		case object1:

			return new EntityA();
			break;
		case object2:
			return new EntityB();
			break;

		default:
			return NULL;
			break;
		}

	}
	class Factory
	{
	public:
		virtual AbstractEntity* FactoryObject() = 0;
		virtual ~Factory() {}
	};

	class EntityAFactory : public Factory
	{
	public:
		AbstractEntity* FactoryObject() {
			return new EntityA;
		}

	};
	class EntityBFactory : public Factory
	{

	public:
		AbstractEntity* FactoryObject() {
			return new EntityB;
		}

	};

}
namespace Prototype
{
	enum Entity_ID { Entity1_ID, Entity2_ID};

	class Entity;  // ќпережающее объ€вление
	typedef std::map<Entity_ID, Entity*> Registry;

	
	Registry& getRegistry()
	{
		static Registry _instance;
		return _instance;
	}

	
	class Dummy { };

	class Entity
	{
	public:
		virtual Entity* clone() = 0;
		virtual std::string info() = 0;
		virtual ~Entity() {}
	
		static Entity* createEntity(Entity_ID id) {
			Registry& r = getRegistry();
			if (r.find(id) != r.end())
				return r[id]->clone();
			return 0;
		}
	protected:
		
		static void addPrototype(Entity_ID id, Entity* prototype) {
			Registry& r = getRegistry();
			r[id] = prototype;
		}
		
		static void removePrototype(Entity_ID id) {
			Registry& r = getRegistry();
			r.erase(r.find(id));
		}
	};



	class Entity1 : public Entity
	{
	public:
		std::string name;
		Entity* clone() {
			return new Entity1(*this);
		}
		std::string info() { if (name != "") return name; else return "EntityA"; }; 
		
		
	private:
		Entity1(Dummy) {
			Entity::addPrototype(Entity1_ID, this);
		}
		Entity1() {}
		static Entity1 prototype;
	};
	Entity1 Entity1::prototype = Entity1(Dummy());
}
namespace Builder
{
	class Parts
	{
	public:
		std::vector<CreationalPatterns::AbstractFactory::EntityA> vEntityA;
		std::vector<CreationalPatterns::AbstractFactory::EntityB> vEntityB;

		std::vector<std::string> info()
		{
			std::vector<std::string> infovector;
			for (int i = 0; i < vEntityA.size(); ++i)  infovector.push_back(vEntityA[i].info());
			for (int i = 0; i < vEntityB.size(); ++i)  infovector.push_back(vEntityB[i].info());
			return infovector;
		}
	};

	class PartsBuilder
	{
	protected:
		Parts* p;
	public:
		PartsBuilder() : p(0) {}
		virtual ~PartsBuilder() {}
		virtual void createParts() {}
		virtual void buildEntityA() {}
		virtual void buildEntityB() {}
		virtual Parts* getParts() { return p; }
	};



	class ExampleBuilderA : public PartsBuilder
	{
	public:
		void createParts() { p = new Parts; }
		void buildEntityA() { p->vEntityA.push_back(CreationalPatterns::AbstractFactory::EntityA()); }
		void buildEntityB() { p->vEntityB.push_back(CreationalPatterns::AbstractFactory::EntityB()); }

	};
	class ExampleBuilderB : public PartsBuilder
	{
	public:
		void createParts() { p = new Parts; }
		void buildEntityA() { p->vEntityA.push_back(CreationalPatterns::AbstractFactory::EntityA()); }


	};

	class Director
	{
	public:
		Parts* DeployParts(PartsBuilder & builder)
		{
			builder.createParts();
			builder.buildEntityA();
			builder.buildEntityB();
			return(builder.getParts());
		}
	/*	Parts* UpgradeParts()
		{
			Parts *_parts;
			return _parts;
		}*/
	
	};
	
};
namespace ObjectPool
{
	
	class Object
	{
		// ...
	};


	class ObjectPool
	{
	private:
		struct PoolRecord
		{
			Object* instance;
			bool    in_use;
		};

		std::vector<PoolRecord> m_pool;

	public:
	
	
		Object* AddToPool()
		{
			for (size_t i = 0; i < m_pool.size(); ++i)
			{
				if (!m_pool[i].in_use)
				{
					m_pool[i].in_use = true; // переводим объект в список используемых
					return m_pool[i].instance;
				}
			}
			// если не нашли свободный объект, то расшир€ем пул
			PoolRecord record;
			record.instance = new Object;
			record.in_use = true;

			m_pool.push_back(record);

			return record.instance;
		}
		template<typename T>
		Object* AddToPool(std::vector<T> _Objects)
		{
            int i = 0;
			for each (T temp in _Objects)
			{
				if (!m_pool[i].in_use)
				{
					m_pool[i].in_use = true; // переводим объект в список используемых
					return m_pool[i].instance;
				}
				i++;
			}
		}
		void ReturnObject(Object* object)
		{
			
			for (size_t i = 0; i < m_pool.size(); ++i)
			{
				if (m_pool[i].instance == object)
				{
					m_pool[i].in_use = false;
					break;
				}
			}
		}
		void GetObject(Object* object)
		{
			
			for (size_t i = 0; i < m_pool.size(); ++i)
			{
				if (m_pool[i].instance == object)
				{
					m_pool[i].in_use = true;
					break;
				}
			}
		}
		virtual ~ObjectPool()
		{
			// теперь уже "по-насто€щему" удал€ем объекты
			for (size_t i = 0; i < m_pool.size(); ++i)
				delete m_pool[i].instance;
		}
		int GetPoolSize()
		{
			return m_pool.size();
		}
	};

}
}

