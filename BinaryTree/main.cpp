#include<iostream>
using namespace std;

#define tab "\t"

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
            cout << "EConstructor:\t" << this << endl;
        }
        ~Element()
        {
            cout << "EDestructor:\t" << this << endl;
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
    virtual ~Tree()
    {
        cout << "TDestructor:\t" << this << endl;
    }

    // 1. ����� Sum - ���������� ����� ��������� ������
    int Sum(Element* Root)
    {
        return !Root ? 0 : Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;
    }

    // 2. ����� Avg - ���������� �������-�������������� ��������� ������
    double Avg(Element* Root)
    {
        int count = this->count(Root);
        if (count == 0) return 0.0;
        return (double)Sum(Root) / count;
    }

    virtual void insert(int Data, Element* Root)
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

    int minValue(Element* Root)
    {
        return Root == nullptr ? INT_MIN : Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
    }

    int maxValue(Element* Root)
    {
        return !Root ? INT_MIN : Root->pRight ? maxValue(Root->pRight) : Root->Data;
    }

    int count(Element* Root)
    {
        return !Root ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
    }

    void print(Element* Root)const
    {
        if (Root == nullptr)return;
        print(Root->pLeft);
        cout << Root->Data << tab;
        print(Root->pRight);
    }
};

// 3. ����� UniqueTree - ������ ������ ���������� ��������
class UniqueTree : public Tree
{
private:
    bool contains(int Data, Element* Root)
    {
        if (Root == nullptr) return false;
        if (Root->Data == Data) return true;
        if (Data < Root->Data) return contains(Data, Root->pLeft);
        else return contains(Data, Root->pRight);
    }

public:
    void insert(int Data, Element* Root) override
    {
        if (this->Root == nullptr)
        {
            this->Root = new Element(Data);
            return;
        }
        if (Root == nullptr) return;

        // ���������, ���������� �� ��� ����� ��������
        if (contains(Data, this->Root))
        {
            cout << "�������� " << Data << " ��� ���������� � ������. ����������." << endl;
            return;
        }

        // ��������� ������ ���������� ��������
        if (Data < Root->Data)
        {
            if (Root->pLeft == nullptr) Root->pLeft = new Element(Data);
            else insert(Data, Root->pLeft);
        }
        else
        {
            if (Root->pRight == nullptr) Root->pRight = new Element(Data);
            else insert(Data, Root->pRight);
        }
    }
};

void main()
{
    setlocale(LC_ALL, "");
    int n;
    cout << "������� ���������� ���������: "; cin >> n;

    // ������������ �������� ������
    cout << "\n=== ������� ������ ===" << endl;
    Tree tree;
    for (int i = 0; i < n; i++)
    {
        int value = rand() % 100;
        cout << "���������: " << value << endl;
        tree.insert(value, tree.getRoot());
    }

    tree.print(tree.getRoot());
    cout << endl;
    cout << "����������� �������� � ������: " << tree.minValue(tree.getRoot()) << endl;
    cout << "������������ �������� � ������: " << tree.maxValue(tree.getRoot()) << endl;
    cout << "���������� ��������� ������: " << tree.count(tree.getRoot()) << endl;
    cout << "����� ��������� ������: " << tree.Sum(tree.getRoot()) << endl;
    cout << "�������-�������������� ��������� ������: " << tree.Avg(tree.getRoot()) << endl;

    // ������������ ������ � ����������� ����������
    cout << "\n=== ������ � ����������� ���������� ===" << endl;
    UniqueTree uniqueTree;
    for (int i = 0; i < n; i++)
    {
        int value = rand() % 100;
        cout << "���������: " << value << endl;
        uniqueTree.insert(value, uniqueTree.getRoot());
    }

    uniqueTree.print(uniqueTree.getRoot());
    cout << endl;
    cout << "����������� �������� � ������: " << uniqueTree.minValue(uniqueTree.getRoot()) << endl;
    cout << "������������ �������� � ������: " << uniqueTree.maxValue(uniqueTree.getRoot()) << endl;
    cout << "���������� ��������� ������: " << uniqueTree.count(uniqueTree.getRoot()) << endl;
    cout << "����� ��������� ������: " << uniqueTree.Sum(uniqueTree.getRoot()) << endl;
    cout << "�������-�������������� ��������� ������: " << uniqueTree.Avg(uniqueTree.getRoot()) << endl;
}