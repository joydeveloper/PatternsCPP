
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
			TreeNode* left;           /* ��������� �� ������ ������� */
			TreeNode* right;          /* ��������� �� ������� ������� */
			TreeNode* parent;         /* ��������� �� �������� */
			NODETYPE data;            /* ���� */
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
			Tree();                                                    /* ����������� */
			int insert_node(const NODETYPE &);                         /* ��������� ���� */
			TreeNode<NODETYPE>* delete_node(TreeNode<NODETYPE> *);     /* ������� ���� */
			void inorder_walk(TreeNode<NODETYPE>*);                    /* �������� ��� ����� � ����������� ������� */
			TreeNode<NODETYPE>* find_max(TreeNode<NODETYPE>*);         /* ������� ���� � ����������� ��������� ����� � ���������� ��������� �� ���� */
			TreeNode<NODETYPE>* find_min(TreeNode<NODETYPE>*);
			TreeNode<NODETYPE>* find_node(TreeNode<NODETYPE>*, const NODETYPE &);
			TreeNode<NODETYPE>* find_succsessor(const NODETYPE &);     /* ������� ������� � ������, ��������� �� ������ ������ */
			TreeNode<NODETYPE> *get_root();                            /* ���������� ��������� �� ������ ������ */
		private:
			TreeNode<NODETYPE> *root;
			TreeNode<NODETYPE> *ptr1;
			/* ����������, ��� ������ */
		};
		template<class NODETYPE>
		Tree<NODETYPE>::Tree()
		{
			root = 0;                      /* � ������ ������ ����� */
		}
		template<class NODETYPE>
		int Tree<NODETYPE>::insert_node(const NODETYPE &x)
		{
			TreeNode<NODETYPE>* n = new TreeNode<NODETYPE>(x);  /* ������� ����� ����, ��� �� ����� ��������� */
			TreeNode<NODETYPE>* ptr;
			//TreeNode<NODETYPE>* ptr1;

			n->parent = n->left = n->right = 0;          /* �� - ���� */
			ptr = root;
			while (ptr != 0)                     /* ���� �� ����� � ���� ���������� ����� ��� ������ ������ ��������, ��� ������ ���� �������� */
			{
				ptr1 = ptr;                 /* ������� �������� ������ ���� */
				if (x < ptr->get_data())  /* �� ����������� ������ ������ - ����� �������� ����� ������ ��������, */
					ptr = ptr->left;
				else
					ptr = ptr->right;   /* ������ - ������ */
			}

			n->parent = ptr1;
			if (ptr1 == 0)                       /* ������ ���� �����? */
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

		/* �������� ��� ������ - ���� � z ��� �����, �� �������� 0 � ��������������� ����
		* �������� z, ���� � z ���� ���� �������, �� ����� �������� z, �������� ��� �������� �������� �
		* ��� ��������. ���� �� ����� ����, �� ��������� ��������� �������������: �� ������� ���������
		* (� ������ ������� �� ������) �� z ������� y; � ���� ��� ������ ������� (������). ������ �����
		* ����������� ���� � �������������� ������ �� ������� y � ������� z, � ���� ������� y �������
		* ��������� ���� �������� */

		template<class NODETYPE>
		TreeNode<NODETYPE>* Tree<NODETYPE>::delete_node(TreeNode<NODETYPE> *z)
		{
			TreeNode<NODETYPE>* y;
			TreeNode<NODETYPE>* x;
			if (z->left == 0 || z->right == 0)               /* � ���� � ��������� ���� ������� ���� ������� y, ������� �� ����� ������� �� ������. ��� ���� z, ���� ��������� �� z */
				y = z;
			else
				y = find_succsessor(z->get_data());
			if (y->left != 0)                                  /* x - ��������� �� ������������� ������� y ��� 0 ���� ������� ��� */
				x = y->left;
			else
				x = y->right;
			if (x != 0)                                        /* ��� � ��������� 9 ����� - ��������� y */
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
			if (y != z)                                        /* ���� �� �������� ������, �������� �� z, �� �� ������ ���������� � z */
				z->data = y->get_data();
			return y;
		}
		template<class NODETYPE>
		TreeNode<NODETYPE>* Tree<NODETYPE>::find_max(TreeNode<NODETYPE>* x)
		{
			while (x->right != 0)                              /* ����� ��� �������� - ������ ������������ �������� � ������ ������� */
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
			TreeNode<NODETYPE>* x = find_node(root, val);                     /* ������� ��������� �� ���� � ������ val */
			TreeNode<NODETYPE>* y;
			if (x == 0)
				return 0;
			if (x->right != 0)                                                /* ���� � ��� ���� ������ ����, �� ��������� ������� - ����������� � ������ ��������� */
				return find_min(x->right);
			y = x->parent;
			while (y != 0 && x == y->right)                                   /* ����� - ���� ����� � ���� ������ �������, ���������� �����
																			  �������� ������ �������� */
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
