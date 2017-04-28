#include <Tree.hpp>
#include <catch.hpp>

SCENARIO("default constructor") 
{
	Tree<int> node;
	REQUIRE(node.root_() == nullptr);
}

SCENARIO("insert")
{
	Tree<int> tree;
	tree.insert(7);
	REQUIRE(tree.value_() == 7);
	REQUIRE(tree.left_() == nullptr);
	REQUIRE(tree.right_() == nullptr);
}

SCENARIO("search")
{
	Tree<int> tree;
	bool b;
	tree.insert(7);
	b = tree.check_search(7);
	REQUIRE(b == true);
}

SCENARIO("size")
{
	Tree<int> tree;
	int size = 0;
	tree.insert(7);
	size = tree.size(tree.root_());
	REQUIRE(size == 1);
}

SCENARIO("pred_")
{
	Tree<int> tree;
	Node<int> * node;
	tree.insert(3);
	tree.insert(4);
	tree.insert(2);
	node = tree.pred_(4);
	REQUIRE(node->value == 3);
}

SCENARIO("print_to_file", "fIn")
{
	Tree<int> tree1, tree2;
	int size1, size2;
	tree1.insert(3);
	tree1.insert(4);
	tree1.print_to_file("TreeOut.txt");
	size1 = tree1.size(tree1.root_());
	tree2.fIn("TreeOut.txt");
	size2 = tree2.size(tree2.root_());
	REQUIRE(size1 == 2);
	REQUIRE(size2 == 2);
	REQUIRE(tree2.x_() == 3);
}

SCENARIO("delete_value")
{
	Tree<int> tree;
	int size1, size2, size3, size4;
	tree.insert(5);
	tree.insert(3);
	tree.insert(2);
	tree.insert(4);
	tree.insert(7);
	tree.insert(6);
	tree.insert(8);
	size1 = tree.size(tree.root_());
	tree.delete_value(8);
	size2 = tree.size(tree.root_());
	tree.delete_value(7);
	size3 = tree.size(tree.root_());
	tree.delete_value(3);
	size4 = tree.size(tree.root_());
	REQUIRE(size1 == 7);
	REQUIRE(size2 == 6);
	REQUIRE(size3 == 5);
	REQUIRE(size4 == 4);
}
