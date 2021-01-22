// avl joaquin.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>
#include <iomanip>
#include <stdlib.h>
using std::vector;
using std::string;
using std::cout;
using namespace std;
template <typename T,class C>
class BinTree {
	struct Node {
		T value;
		int h_izq = 0;
		int h_der = 0;
		Node* nodes[2];
		Node(const T& dato)
		{
			value = dato;
			nodes[0] = NULL;
			nodes[1] = NULL;
		}
		// stack-abusing recursion everywhere, for small code
		~Node() { delete nodes[0]; delete nodes[1]; }
		int max_depth() const {
			const int left_depth = nodes[0] ? nodes[0]->max_depth() : 0;
			const int right_depth = nodes[1] ? nodes[1]->max_depth() : 0;
			return (left_depth > right_depth ? left_depth : right_depth) + 1;
		}
	};

	Node *root;

public:
	BinTree() : root(nullptr) {}
	~BinTree() { delete root; }
	C cmp;
	int get_max_depth() const { return root ? root->max_depth() : 0; }
	void clear() { delete root; root = nullptr; }
	void insert() {}
	template <typename ...Args>
	bool buscar(T x, Node **& p, vector<Node**>& res)
	{
		for (p = &root; (*p) && ((*p)->value != x); p = &((*p)->nodes[cmp((*p)->value, x)]))
		{
			res.push_back(p);
		}
		return (*p) != 0;
	}
	bool insert(const T& x) {
		Node** p;
		vector<Node**> recorrido;
		if (buscar(x, p, recorrido))
			return 0;
		*p = new Node(x);
		// reversa
		for (int i = recorrido.size() - 1; i >= 0; i--)
		{
			altura(recorrido[i]);
			balance(recorrido[i]);
		}
		return 1;
	}
	void altura(Node**& p)
	{
		if ((*p)->nodes[0])
		{
			if ((*p)->nodes[0]->h_izq < (*p)->nodes[0]->h_der)
			{
				(*p)->h_izq = (*p)->nodes[0]->h_der + 1;
			}
			else
			{
				(*p)->h_izq = (*p)->nodes[0]->h_izq + 1;
			}
		}
		else
		{
			(*p)->h_izq = 0;
		}
		if ((*p)->nodes[1])
		{
			if ((*p)->nodes[1]->h_izq < (*p)->nodes[1]->h_der)
			{
				(*p)->h_der = (*p)->nodes[1]->h_der + 1;
			}
			else
			{
				(*p)->h_der = (*p)->nodes[1]->h_izq + 1;
			}
		}
		else
		{
			(*p)->h_der = 0;
		}
	}

	// 0 1 2 ----- 0 -1 -2
	bool balance(Node**& p)
	{
		Node* nuevo;
		//-2 -1 0
		if ((*p)->h_der - (*p)->h_izq == -2)
		{
			if ((*p)->nodes[0]->h_izq >= (*p)->nodes[0]->h_der)
			{
				nuevo = (*p)->nodes[0];
				(*p)->nodes[0] = nuevo->nodes[1];
				nuevo->nodes[1] = (*p);
				(*p) = nuevo;
				Node** temp = &(*p)->nodes[0];
				Node** temp2 = &(*p)->nodes[1];
				altura(temp);
				altura(temp2);
				altura(p);
				return 1;
			}
			else
			{
				nuevo = (*p)->nodes[0]->nodes[1];
				(*p)->nodes[0]->nodes[1] = nuevo->nodes[0];
				nuevo->nodes[0] = (*p)->nodes[0];
				(*p)->nodes[0] = nuevo->nodes[1];
				nuevo->nodes[1] = (*p);
				(*p) = nuevo;
				Node** temp = &(*p)->nodes[0];
				Node** temp2 = &(*p)->nodes[1];
				altura(temp);
				altura(temp2);
				altura(p);
				return 1;
			}
		}
		//2 1 0
		else if ((*p)->h_der - (*p)->h_izq == 2)
		{
			if ((*p)->nodes[1]->h_der >= (*p)->nodes[1]->h_izq)
			{
				nuevo = (*p)->nodes[1];
				(*p)->nodes[1] = nuevo->nodes[0];
				nuevo->nodes[0] = (*p);
				(*p) = nuevo;
				Node** temp = &(*p)->nodes[0];
				Node** temp2 = &(*p)->nodes[1];
				altura(temp);
				altura(temp2);
				altura(p);
				return 1;
			}
			else
			{
				nuevo = (*p)->nodes[1]->nodes[0];
				(*p)->nodes[1]->nodes[0] = nuevo->nodes[1];
				nuevo->nodes[1] = (*p)->nodes[1];
				(*p)->nodes[1] = nuevo->nodes[0];
				nuevo->nodes[0] = (*p);
				(*p) = nuevo;
				Node** temp = &(*p)->nodes[0];
				Node** temp2 = &(*p)->nodes[1];
				altura(temp);
				altura(temp2);
				altura(p);
				return 1;
			}
		}
		return 0;
	}
	

	bool eliminar(T x)
	{
		Node** p;
		vector<Node**> recorrido;
		if (!buscar(x, p, recorrido)) return 0;
		if ((*p)->nodes[0] && (*p)->nodes[1])
		{
			Node** q = p;
			q = &((*q)->nodes[1]);
			while ((*q)->nodes[0])
			{
				recorrido.push_back(q);
				q = &((*q)->nodes[0]);
			}

			(*p)->val = (*q)->val;
			p = q;

		}

		Node* t = *p;
		*p = (*p)->nodes[(*p)->nodes[1] != 0];
		delete t;
		// reverse
		for (int i = recorrido.size() - 1; i >= 0; i--)
		{
			altura(recorrido[i]);
			balance(recorrido[i]);
		}
		return 1;
	}
	/// altura del arbol
	struct cell_display {
		string   valstr;
		bool     present;
		cell_display() : present(false) {}
		cell_display(std::string valstr) : valstr(valstr), present(true) {}
	};

	using display_rows = vector< vector< cell_display > >;

	// The text tree generation code below is all iterative, to avoid stack faults.

	// get_row_display builds a vector of vectors of cell_display structs
	// each vector of cell_display structs represents one row, starting at the root
	display_rows get_row_display() const {
		// start off by traversing the tree to
		// build a vector of vectors of Node pointers
		vector<Node*> traversal_stack;
		vector< std::vector<Node*> > rows;
		if (!root) return display_rows();

		Node *p = root;
		const int max_depth = root->max_depth();
		rows.resize(max_depth);
		int depth = 0;
		for (;;) {
			// Max-depth Nodes are always a leaf or null
			// This special case blocks deeper traversal
			if (depth == max_depth - 1) {
				rows[depth].push_back(p);
				if (depth == 0) break;
				--depth;
				continue;
			}

			// First visit to node?  Go to left child.
			if (traversal_stack.size() == depth) {
				rows[depth].push_back(p);
				traversal_stack.push_back(p);
				if (p) p = p->nodes[1];
				++depth;
				continue;
			}

			// Odd child count? Go to right child.
			if (rows[depth + 1].size() % 2) {
				p = traversal_stack.back();
				if (p) p = p->nodes[0];
				++depth;
				continue;
			}

			// Time to leave if we get here

			// Exit loop if this is the root
			if (depth == 0) break;

			traversal_stack.pop_back();
			p = traversal_stack.back();
			--depth;
		}

		// Use rows of Node pointers to populate rows of cell_display structs.
		// All possible slots in the tree get a cell_display struct,
		// so if there is no actual Node at a struct's location,
		// its boolean "present" field is set to false.
		// The struct also contains a string representation of
		// its Node's value, created using a std::stringstream object.
		display_rows rows_disp;
		std::stringstream ss;
		for (const auto& row : rows) {
			rows_disp.emplace_back();
			for (Node* pn : row) {
				if (pn) {
					ss << pn->value;
					rows_disp.back().push_back(cell_display(ss.str()));
					ss = std::stringstream();
				}
				else {
					rows_disp.back().push_back(cell_display());
				}
			}
		}
		return rows_disp;
	}

	// row_formatter takes the vector of rows of cell_display structs 
	// generated by get_row_display and formats it into a test representation
	// as a vector of strings
	vector<string> row_formatter(const display_rows& rows_disp) const {
		using s_t = string::size_type;

		// First find the maximum value string length and put it in cell_width
		s_t cell_width = 0;
		for (const auto& row_disp : rows_disp) {
			for (const auto& cd : row_disp) {
				if (cd.present && cd.valstr.length() > cell_width) {
					cell_width = cd.valstr.length();
				}
			}
		}

		// make sure the cell_width is an odd number
		if (cell_width % 2 == 0) ++cell_width;

		// formatted_rows will hold the results
		vector<string> formatted_rows;

		// some of these counting variables are related,
		// so its should be possible to eliminate some of them.
		s_t row_count = rows_disp.size();

		// this row's element count, a power of two
		s_t row_elem_count = 1 << (row_count - 1);

		// left_pad holds the number of space charactes at the beginning of the bottom row
		s_t left_pad = 0;

		// Work from the level of maximum depth, up to the root
		// ("formatted_rows" will need to be reversed when done) 
		for (s_t r = 0; r < row_count; ++r) {
			const auto& cd_row = rows_disp[row_count - r - 1]; // r reverse-indexes the row
			// "space" will be the number of rows of slashes needed to get
			// from this row to the next.  It is also used to determine other
			// text offsets.
			s_t space = (s_t(1) << r) * (cell_width + 1) / 2 - 1;
			// "row" holds the line of text currently being assembled
			string row;
			// iterate over each element in this row
			for (s_t c = 0; c < row_elem_count; ++c) {
				// add padding, more when this is not the leftmost element
				row += string(c ? left_pad * 2 + 1 : left_pad, ' ');
				if (cd_row[c].present) {
					// This position corresponds to an existing Node
					const string& valstr = cd_row[c].valstr;
					// Try to pad the left and right sides of the value string
					// with the same number of spaces.  If padding requires an
					// odd number of spaces, right-sided children get the longer
					// padding on the right side, while left-sided children
					// get it on the left side.
					s_t long_padding = cell_width - valstr.length();
					s_t short_padding = long_padding / 2;
					long_padding -= short_padding;
					row += string(c % 2 ? short_padding : long_padding, ' ');
					row += valstr;
					row += string(c % 2 ? long_padding : short_padding, ' ');
				}
				else {
					// This position is empty, Nodeless...
					row += string(cell_width, ' ');
				}
			}
			// A row of spaced-apart value strings is ready, add it to the result vector
			formatted_rows.push_back(row);

			// The root has been added, so this loop is finsished
			if (row_elem_count == 1) break;

			// Add rows of forward- and back- slash characters, spaced apart
			// to "connect" two rows' Node value strings.
			// The "space" variable counts the number of rows needed here.
			s_t left_space = space + 1;
			s_t right_space = space - 1;
			for (s_t sr = 0; sr < space; ++sr) {
				string row;
				for (s_t c = 0; c < row_elem_count; ++c) {
					if (c % 2 == 0) {
						row += string(c ? left_space * 2 + 1 : left_space, ' ');
						row += cd_row[c].present ? '/' : ' ';
						row += string(right_space + 1, ' ');
					}
					else {
						row += string(right_space, ' ');
						row += cd_row[c].present ? '\\' : ' ';
					}
				}
				formatted_rows.push_back(row);
				++left_space;
				--right_space;
			}
			left_pad += space + 1;
			row_elem_count /= 2;
		}

		// Reverse the result, placing the root node at the beginning (top)
		std::reverse(formatted_rows.begin(), formatted_rows.end());

		return formatted_rows;
	}

	// Trims an equal number of space characters from
	// the beginning of each string in the vector.
	// At least one string in the vector will end up beginning
	// with no space characters.
	static void trim_rows_left(vector<string>& rows) {
		if (!rows.size()) return;
		auto min_space = rows.front().length();
		for (const auto& row : rows) {
			auto i = row.find_first_not_of(' ');
			if (i == string::npos) i = row.length();
			if (i == 0) return;
			if (i < min_space) min_space = i;
		}
		for (auto& row : rows) {
			row.erase(0, min_space);
		}
	}

	// Dumps a representation of the tree to cout
	void Dump() const {
		const int d = get_max_depth();

		// If this tree is empty, tell someone
		if (d == 0) {
			cout << " <empty tree>\n";
			return;
		}

		// This tree is not empty, so get a list of node values...
		const auto rows_disp = get_row_display();
		// then format these into a text representation...
		auto formatted_rows = row_formatter(rows_disp);
		// then trim excess space characters from the left sides of the text...
		trim_rows_left(formatted_rows);
		// then dump the text to cout.
		for (const auto& row : formatted_rows) {
			std::cout << ' ' << row << '\n';
		}
	}
	void Oldprint(Node *p = NULL, int aux = 0)
	{
		bool condition=false;
		if (p == 0)
		{
			p = root;
			condition = true;
		}
		if (p != NULL && condition==true)
		{
			if (p->nodes[1])
			{
				Oldprint(p->nodes[1], aux + 6);
			}
			if (aux)
			{
				cout << setw(aux) << ' ';
			}
			if (p->nodes[1])
				cout << " /\n" << setw(aux) << ' ';
			cout << p->value << "\n ";
			if (p->nodes[0])
			{
				cout << setw(aux) << ' ' << " \\\n";
				Oldprint(p->nodes[0], aux + 6);
			}
		}
	}
	
};
template <typename T>
struct cmp_mayor
{
	inline bool operator()(T a, T b)
	{
		return (a > b);
	}
};

template <typename T>
struct cmp_menor
{
	inline bool operator()(T a, T b)
	{
		return (a < b);
	}
};

int main() {
	BinTree<int, cmp_menor<int> > bt;


	cout << "Ingrese sus numeros, para ya no agregar mas ingrese -1 como input" << endl;
	int x;
	cin >> x;
	for (int i = 0; i != -1; i = x)
	{

		bt.insert(x);
		cin >> x;
	}
	/*bt.insert(1);
	bt.insert(10);
	bt.insert(8);
	bt.insert(3);
	bt.insert(5);
	bt.insert(2);*/
	bt.Dump();
	cout << "OLDPRINT:" << endl;
	bt.Oldprint();
	cout << "\n\n";

}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
