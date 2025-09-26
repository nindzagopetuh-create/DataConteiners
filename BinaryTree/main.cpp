#include<iostream>
#include <chrono>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

#define DEBUG

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :
			Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree() :Root(nullptr)
	{
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
			insert(*it, Root);
		cout << "ILConstructor:\t" << this << endl;
	}
	~Tree()
	{
		clear();
		cout << "TDestructor:\t" << this << endl;
	}
	void clear()
	{
		clear(Root);
	}
	void insert(int Data)
	{
		insert(Data, Root);
	}
	void erase(int Data)
	{
		erase(Data, Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int sum()const
	{
		return sum(Root);
	}
	int count()const
	{
		return count(Root);
	}
	double avg()const
	{
		return (double)sum(Root) / count(Root);
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}

	// 1. ����� depth() - ���������� ������� ������
	int depth() const
	{
		return depth(Root);
	}

	// 3. ����� tree_print() - ������� ������ � ���� ������
	void tree_print() const
	{
		tree_print(Root, 0);
	}

	// 4. ����� Balance() - ����������� �������� ������
	void Balance()
	{
		Balance(Root);
	}

	// 2. ������ ��� ��������� ������������������
	void measure_performance() const
	{
		cout << "��������� ������������������ �������:" << endl;

		// ��������� minValue()
		auto start = std::chrono::high_resolution_clock::now();
		int min_val = minValue();
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		cout << "minValue(): " << min_val << " (�����: " << duration.count() << " ���)" << endl;

		// ��������� maxValue()
		start = std::chrono::high_resolution_clock::now();
		int max_val = maxValue();
		end = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		cout << "maxValue(): " << max_val << " (�����: " << duration.count() << " ���)" << endl;

		// ��������� sum()
		start = std::chrono::high_resolution_clock::now();
		int sum_val = sum();
		end = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		cout << "sum(): " << sum_val << " (�����: " << duration.count() << " ���)" << endl;

		// ��������� count()
		start = std::chrono::high_resolution_clock::now();
		int count_val = count();
		end = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		cout << "count(): " << count_val << " (�����: " << duration.count() << " ���)" << endl;

		// ��������� depth()
		start = std::chrono::high_resolution_clock::now();
		int depth_val = depth();
		end = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		cout << "depth(): " << depth_val << " (�����: " << duration.count() << " ���)" << endl;

		// ��������� avg()
		start = std::chrono::high_resolution_clock::now();
		double avg_val = avg();
		end = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		cout << "avg(): " << avg_val << " (�����: " << duration.count() << " ���)" << endl;

		cout << endl;
	}

private:
	void clear(Element*& Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
		Root = nullptr;
	}
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr) this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->pLeft == Root->pRight)
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (count(Root->pLeft) > count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}
	int minValue(Element* Root)const
	{
		return Root == nullptr ? INT_MIN : Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		return !Root ? INT_MIN : Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
	int count(Element* Root)const
	{
		return !Root ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
	}
	int sum(Element* Root)const
	{
		return Root == nullptr ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}

	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}

	// 1. ��������������� ����� ��� ���������� �������
	int depth(Element* Root) const
	{
		if (Root == nullptr) return 0;
		int left_depth = depth(Root->pLeft);
		int right_depth = depth(Root->pRight);
		return 1 + (left_depth > right_depth ? left_depth : right_depth);
	}

	// 3. ��������������� ����� ��� ������ ������ � ���� ������
	void tree_print(Element* Root, int level) const
	{
		if (Root == nullptr) return;

		tree_print(Root->pRight, level + 1);

		for (int i = 0; i < level; i++)
			cout << "    ";
		cout << Root->Data << endl;

		tree_print(Root->pLeft, level + 1);
	}

	// 4. ��������������� ������ ��� ������������ ������
	void storeInorder(Element* Root, int* arr, int& index)
	{
		if (Root == nullptr) return;
		storeInorder(Root->pLeft, arr, index);
		arr[index++] = Root->Data;
		storeInorder(Root->pRight, arr, index);
	}

	Element* buildBalancedTree(int* arr, int start, int end)
	{
		if (start > end) return nullptr;

		int mid = (start + end) / 2;
		Element* Root = new Element(arr[mid]);

		Root->pLeft = buildBalancedTree(arr, start, mid - 1);
		Root->pRight = buildBalancedTree(arr, mid + 1, end);

		return Root;
	}

	void Balance(Element*& Root)
	{
		if (Root == nullptr) return;

		int n = count(Root);
		int* arr = new int[n];
		int index = 0;

		storeInorder(Root, arr, index);

		// ������� ������ ������
		clear(Root);

		// ������ ���������������� ������
		Root = buildBalancedTree(arr, 0, n - 1);

		delete[] arr;
	}
};

class UniqueTree :public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr) this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "������� ���������� ���������: "; cin >> n;
	Tree tree;
	cout << "����������� �������� � ������: " << tree.minValue() << endl;
	cout << "������������ �������� � ������: " << tree.maxValue() << endl;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;
	cout << "����������� �������� � ������: " << tree.minValue() << endl;
	cout << "������������ �������� � ������: " << tree.maxValue() << endl;
	cout << "���������� ��������� ������: " << tree.count() << endl;
	cout << "����� ��������� ������: " << tree.sum() << endl;
	cout << "�������-�������������� ��������� ������: " << tree.avg() << endl;

	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	u_tree.print();
	cout << "����������� �������� � ������: " << u_tree.minValue() << endl;
	cout << "������������ �������� � ������: " << u_tree.maxValue() << endl;
	cout << "���������� ��������� ������: " << u_tree.count() << endl;
	cout << "����� ��������� ������: " << u_tree.sum() << endl;
	cout << "�������-�������������� ��������� ������: " << u_tree.avg() << endl;
#endif // BASE_CHECK

	Tree tree =
	{
					50,

			25,				75,

		16,		32,		58,		85
	};

	cout << "�������� ������:" << endl;
	tree.print();
	cout << "������� ������: " << tree.depth() << endl;
	cout << endl;

	cout << "������ � ���� ������:" << endl;
	tree.tree_print();
	cout << endl;

	// �������� ������������������
	tree.measure_performance();

	int value;
	//cout << "������� ��������� ��������: "; cin >> value;
	tree.erase(25);
	tree.erase(32);
	tree.erase(50);
	tree.erase(75);

	cout << "������ ����� �������� ���������:" << endl;
	tree.print();
	cout << "������� ������ ����� ��������: " << tree.depth() << endl;
	cout << endl;

	cout << "������������ ������..." << endl;
	tree.Balance();

	cout << "������ ����� ������������:" << endl;
	tree.tree_print();
	cout << "������� ������ ����� ������������: " << tree.depth() << endl;
	cout << endl;

	// �������� ������������������ ����� ������������
	tree.measure_performance();

}