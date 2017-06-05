
#include <cstdlib> 
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <tuple> 
namespace MyPatterns

{
	typedef std::string stringm;
	namespace Combine
	{

		class A
		{
			//friend class ICombined;
		public:
			A(){ x = 1; }
		
			int x;
		private:
			int u;
		protected:
			int j;

		};
		class B
		{
		public:
			B(){ y = 1; }
		
			int y;

		};
		class C
		{
		public:
			C(){ z = 1; }
			int z;

		};
		class ICombined
		{
		public:
			A a;
			
			B b;
			C c;
			//virtual void Adapting(ICombined* ic){ic->};
			int Combine(){ return a.x + b.y + c.z; }


		};
	}
	namespace Forge
	{
		class BaseMaterial
		{
		public:
			int prop;
			virtual ~BaseMaterial(){}
		};
		class Iron :public BaseMaterial
		{
		public:
			Iron(){ prop = 10; }


		};
		class Material
		{
		public:
			Material(){}
			virtual ~Material(){}


		};
		class Plastine :public Material
		{
		public:
			Plastine() {};
			int prop;
			void MakePlane(){ prop -= 5; };
			//	virtual ~Plastine();


		private:
		};
		class Tools
		{
		public:
			virtual void ChangeProperties() = 0;
			virtual Material* CreateOutputMaterial() = 0;
			Tools(BaseMaterial* p) : pmat(p) {}
			BaseMaterial * pmat;

		};


		class Molot :public Tools
		{
		public:

			Molot(BaseMaterial * p) : Tools(p) {}
			Plastine pplas;
			void ChangeProperties(){ pmat->prop = 9; }
			Material* CreateOutputMaterial(){
				Plastine* plas = new Plastine();
				plas->prop = pmat->prop;
				pplas = *plas;
				return plas;
				delete plas;
			}
			~Molot(){ delete pmat; }

		};


	}

	namespace BinaryTree
	{
		template <class NODETYPE> class TreeNode
		{
			template <class NODETYPE>
			friend class Tree;

		public:
			TreeNode(const NODETYPE &);
			NODETYPE get_data();
		protected:
			TreeNode* left;           /* указатель на левого ребенка */
			TreeNode* right;          /* указатель на правого ребенка */
			TreeNode* parent;         /* указатель на родителя */
			NODETYPE data;            /* ключ */
		};

		template<class NODETYPE>
		TreeNode <NODETYPE>::TreeNode(const NODETYPE &a)
		{
			data = a;
			left = right = 0;
		}
		template <class NODETYPE>
		NODETYPE TreeNode <NODETYPE>::get_data()
		{
			return data;
		}

		/////////////////////////////////////////////////////
		template <class NODETYPE>
		class Tree
		{
		public:
			Tree();                                                    /* конструктор */
			int insert_node(const NODETYPE &);                         /* вставляет узел */
			TreeNode<NODETYPE>* delete_node(TreeNode<NODETYPE> *);     /* удаляет узел */
			void inorder_walk(TreeNode<NODETYPE>*);                    /* печатает все ключи в неубывающем порядке */
			TreeNode<NODETYPE>* find_max(TreeNode<NODETYPE>*);         /* находит узел с минимальным значением ключа и возвращает указатель на него */
			TreeNode<NODETYPE>* find_min(TreeNode<NODETYPE>*);
			TreeNode<NODETYPE>* find_node(TreeNode<NODETYPE>*, const NODETYPE &);
			TreeNode<NODETYPE>* find_succsessor(const NODETYPE &);     /* находит элемент с ключем, следующим за данным числом */
			TreeNode<NODETYPE> *get_root();                            /* возвращает указатель на корень дерева */
		private:
			TreeNode<NODETYPE> *root;
			TreeNode<NODETYPE> *ptr1;
			/* собственно, сам корень */
		};
		template<class NODETYPE>
		Tree<NODETYPE>::Tree()
		{
			root = 0;                      /* в начале дерево пусто */
		}
		template<class NODETYPE>
		int Tree<NODETYPE>::insert_node(const NODETYPE &x)
		{
			TreeNode<NODETYPE>* n = new TreeNode<NODETYPE>(x);  /* создаем новый узел, его мы будем вставлять */
			TreeNode<NODETYPE>* ptr;
			//TreeNode<NODETYPE>* ptr1;

			n->parent = n->left = n->right = 0;          /* он - лист */
			ptr = root;
			while (ptr != 0)                     /* идем от корня и ищем подходящее место для нашего нового элемента, оно должно быть свободно */
			{
				ptr1 = ptr;                 /* будущий родитель нового узла */
				if (x < ptr->get_data())  /* по определению нашего дерева - слева значение ключа меньше родителя, */
					ptr = ptr->left;
				else
					ptr = ptr->right;   /* справа - больше */
			}

			n->parent = ptr1;
			if (ptr1 == 0)                       /* дерево было пусто? */
				root = n;
			else
			{
				if (x < ptr1->get_data())
					ptr1->left = n;
				else
					ptr1->right = n;
			}
			return 0;
		}

		/* возможны три случая - если у z нет детей, то помещаем 0 в соответствующее поле
		* родителя z, если у z есть один ребенок, то можно вырезать z, соединив его родителя напрямую с
		* его ребенком. Если же детей двое, то требуются некоторые приготовления: мы находим следующий
		* (в смысле порядка на ключах) за z элемент y; у него нет левого ребенка (всегда). Теперь можно
		* скопировать ключ и дополнительные данные из вершины y в вершину z, а саму вершину y удалить
		* описанным выше способом */

		template<class NODETYPE>
		TreeNode<NODETYPE>* Tree<NODETYPE>::delete_node(TreeNode<NODETYPE> *z)
		{
			TreeNode<NODETYPE>* y;
			TreeNode<NODETYPE>* x;
			if (z->left == 0 || z->right == 0)               /* в этой и следующих двух строках ищем вершину y, которую мы потом вырежем из дерева. Это либо z, либо следующий за z */
				y = z;
			else
				y = find_succsessor(z->get_data());
			if (y->left != 0)                                  /* x - указатель на существующего ребенка y или 0 если таковых нет */
				x = y->left;
			else
				x = y->right;
			if (x != 0)                                        /* эта и следующие 9 строк - вырезание y */
				x->parent = y->parent;
			if (y->parent == 0)
				root = x;
			else
			{
				if (y == (y->parent)->left)
					(y->parent)->left = x;
				else
					(y->parent)->right = x;
			}
			if (y != z)                                        /* если мы вырезали вершин, отличную от z, то ее данные перемещаем в z */
				z->data = y->get_data();
			return y;
		}
		template<class NODETYPE>
		TreeNode<NODETYPE>* Tree<NODETYPE>::find_max(TreeNode<NODETYPE>* x)
		{
			while (x->right != 0)                              /* здесь все очевидно - самыое максимальное значение у самого правого */
				x = x->right;
			return x;
		}

		template<class NODETYPE>
		TreeNode<NODETYPE>* Tree<NODETYPE>::find_min(TreeNode<NODETYPE>* x)
		{
			while (x->left != 0)
				x = x->left;
			return x;
		}

		template<class NODETYPE>
		TreeNode<NODETYPE>* Tree<NODETYPE>::find_succsessor(const NODETYPE & val)
		{
			TreeNode<NODETYPE>* x = find_node(root, val);                     /* получим указатель на ноду с ключем val */
			TreeNode<NODETYPE>* y;
			if (x == 0)
				return 0;
			if (x->right != 0)                                                /* если у нее есть правые дети, то следующий элемент - минимальный в правом поддереве */
				return find_min(x->right);
			y = x->parent;
			while (y != 0 && x == y->right)                                   /* иначе - идем вверх и ищем первый элемент, являющийся левым
																			  потомком своего родителя */
			{
				x = y;
				y = y->parent;
			}
			return y;
		}
		template<class NODETYPE>
		TreeNode<NODETYPE>* Tree<NODETYPE>::find_node(TreeNode<NODETYPE>* n,
			const NODETYPE & val)
		{
			if (n == 0 || val == n->get_data())
				return n;
			if (val > n->get_data())
				return find_node(n->right, val);
			else
				return find_node(n->left, val);
		}
		template<class NODETYPE>
		void Tree<NODETYPE>::inorder_walk(TreeNode<NODETYPE>* n)
		{
			if (n != 0)
			{
				inorder_walk(n->left);
				cout << n->get_data() << endl;
				inorder_walk(n->right);
			}
		}

		template<class NODETYPE>
		TreeNode<NODETYPE>* Tree<NODETYPE>::get_root()
		{
			return root;
		}
	}
	
	

	namespace VariableCycle
	{
		static int balancevalue = 100;

		class A
		{
		public:
			A(){}
			virtual ~A(){}
			int x;
			void eat(){ x--;  balancevalue--; };
		};
		class B :public A
		{
		public:
			int y;
			void move(){ y--; balancevalue--; };
		};
		class C :public B
		{
		public:
			int z;
			void fuck(){ z--; balancevalue--; };;
		};
		class ICycling
		{
		public:
			void reborn()
			{
				A a;
				a.x = 999;
				B *bp = (B*)&a;
				B b;
				b = *bp;
				b.y = 99;
				b.eat();
				b.move();
				C *cp = (C*)&b;
				C c;
				c = *cp;
				c.z = 9;
				c.fuck();
				std::cout << "ax" << (a.x);
				std::cout << "bp" << (bp->x);
				std::cout << "bx" << (b.x);
				std::cout << "by" << (b.y);
				std::cout << "cp" << (cp->x);
				std::cout << "cx" << (c.x);
				std::cout << "cy" << (c.y);
				std::cout << "cz" << (c.z);
				std::cout << "bv" << (balancevalue);
				delete bp, cp;
			}
		};





	};
	namespace Radiator
	{
		//Abstract entity+itirator
		class IRadiatorable
		{
		public:
			virtual ~IRadiatorable(){}
			int x = 10;
			virtual void ChangeTemperature() = 0;

		};
		class Material :public IRadiatorable
		{
		public:
			Material(float, float);
			float temperature;
			float durability;
			void ChangeTemperature(){ temperature -= x / durability; }

		};


	}
	namespace Grower
	{
		class Seed
		{
		public:
			Seed(){ test = 1; conditioned = false; }
			int test;
			virtual void NextGrow(){ test++; };
			int  condition = 20;
			bool conditioned;
		};

		class Condition
		{
		public:
			virtual ~Condition() {}
			virtual bool GrowUp(int) = 0;
		protected:
			Condition(Seed* p) : pseed(p) {}
			Seed * pseed;
		};
		class GrowCondition : public Condition
		{

		public:
			GrowCondition(Seed * p) : Condition(p) {}
			bool GrowUp(int);

		};
	}
}
