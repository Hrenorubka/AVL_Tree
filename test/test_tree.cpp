#include <gtest.h>
#include <Tree.h>

/*TEST(TNode, can_create_node)
{
	ASSERT_NO_THROW(TNode<int> a);
}
*/

TEST(VTree, can_create_tree)
{
	ASSERT_NO_THROW(AVL_Tree<int> t);
}

TEST(VTree, can_create_tree_with_param)
{
	Val_Collum<int> param = { 12, 11 };
	ASSERT_NO_THROW(AVL_Tree<Val_Collum<int>> t(param));
}

TEST(VTree, can_insert_elem_to_tree)
{
	AVL_Tree<int> t;
	ASSERT_NO_THROW(t.insert(9));
}

TEST(VTree, can_do_small_rotate_left)
{
	AVL_Tree<int> t;
	t.insert(5);
	t.insert(7);
	ASSERT_NO_THROW(t.insert(9));
}

TEST(VTree, can_do_small_rotate_right)
{
	AVL_Tree<int> t;
	t.insert(9);
	t.insert(7);
	ASSERT_NO_THROW(t.insert(5));
}

TEST(VTree, can_do_big_rotate_left_t_1)
{
	AVL_Tree<int> t;
	t.insert(5);
	t.insert(9);
	ASSERT_NO_THROW(t.insert(7));
}

TEST(VTree, can_do_big_rotate_left_t_2)
{
	AVL_Tree<int> t;
	t.insert(7);
	t.insert(5);
	t.insert(12);
	t.insert(15);
	t.insert(10);
	ASSERT_NO_THROW(t.insert(8));
}

TEST(VTree, can_do_big_rotate_right_t_1)
{
	AVL_Tree<int> t;
	t.insert(9);
	t.insert(5);
	ASSERT_NO_THROW(t.insert(7));
}

TEST(VTree, can_do_big_rotate_right_t_2)
{
	AVL_Tree<int> t;
	t.insert(13);
	t.insert(15);
	t.insert(8);
	t.insert(5);
	t.insert(9);
	ASSERT_NO_THROW(t.insert(12));
}

TEST(VTree, can_find_elem_in_tree_t_1)
{
	AVL_Tree<int> t;
	t.insert(13);
	t.insert(15);
	t.insert(8);
	int exp = t.find(8);
	EXPECT_EQ(8, exp);
}

TEST(VTree, can_find_elem_in_tree_t_2)
{
	AVL_Tree<int> t;
	t.insert(13);
	t.insert(15);
	t.insert(8);
	t.insert(5);
	t.insert(9);
	t.insert(12);
	int exp = t.find(9);
	EXPECT_EQ(9, exp);
}

TEST(VTree, can_find_elem_in_tree_t_3)
{
	AVL_Tree<int> t;
	t.insert(7);
	t.insert(5);
	t.insert(12);
	t.insert(15);
	t.insert(10);
	t.insert(8);
	int exp = t.find(10);
	EXPECT_EQ(10, exp);
}

TEST(VTree, can_find_elem_in_tree_t_4)
{
	AVL_Tree<int> t;
	t.insert(9);
	t.insert(5);
	t.insert(7);
	int exp = t.find(5);
	EXPECT_EQ(5, exp);
}


TEST(VTree, can_delete_elem_in_tree_t_1)
{
	AVL_Tree<int> t;
	t.insert(9);
	t.insert(5);
	t.insert(7);
	t.erase(5);
	ASSERT_NO_THROW(t.print(t.get_head()));
}

TEST(VTree, can_delete_elem_in_tree_t_2)
{
	AVL_Tree<int> t;
	t.insert(5);
	t.insert(7);
	t.insert(9);
	t.erase(9);
	ASSERT_NO_THROW(t.print(t.get_head()));
}

TEST(VTree, can_delete_elem_in_tree_t_3)
{
	AVL_Tree<int> t;
	t.insert(13);
	t.insert(15);
	t.insert(8);
	t.insert(5);
	t.insert(9);
	t.insert(12);
	t.erase(12);
	ASSERT_NO_THROW(t.print(t.get_head()));
}

TEST(VTree, can_print_tree)
{
	AVL_Tree<int> t;
	t.insert(7);
	t.insert(5);
	t.insert(12);
	t.insert(15);
	t.insert(10);
	t.insert(8);
	t.insert(11);
	ASSERT_NO_THROW(t.print(t.get_head()));
}

TEST(VTree, can_print_tree_v2)
{
	AVL_Tree< Val_Collum<int> > t;
	t.insert({ 7, 4 });
	t.insert({ 5, 4 });
	t.insert({ 12, 13 });
	t.insert({ 15, 34 });
	t.insert({ 10, 32 });
	t.insert({ 8, 65 });
	t.insert({ 11, 25 });
	ASSERT_NO_THROW(t.print(t.get_head()));
}

TEST(VTree, can_swap)
{
	AVL_Tree<int> t;
	t.insert(7);
	t.insert(5);
	t.insert(8);
	t.insert(4);
	ASSERT_NO_THROW(t.swap_pointer(t.get_head(), t.get_head()->left));
}
TEST(VTree, can_erase_t_1)
{
	AVL_Tree<int> t;
	t.insert(5);
	t.insert(7);
	t.insert(9);
	t.erase(5);
	ASSERT_NO_THROW(t.print(t.get_head()));
}

TEST(VTree, can_erase_t_2)
{
	AVL_Tree<int> t;
	t.insert(13);
	t.insert(15);
	t.insert(8);
	t.insert(5);
	t.insert(9);
	t.insert(12);
	t.erase(12);
	ASSERT_NO_THROW(t.print(t.get_head()));
}

TEST(VTree, can_erase_t_3)
{
	AVL_Tree<int> t;
	t.insert(9);
	t.insert(7);
	t.insert(11);
	t.insert(6);
	t.erase(11);
	ASSERT_NO_THROW(t.print(t.get_head()));
}

TEST(VTree, can_erase_t_4)
{
	AVL_Tree<int> t;
	t.insert(9);
	t.insert(7);
	t.insert(11);
	t.insert(14);
	t.erase(7);
	ASSERT_NO_THROW(t.print(t.get_head()));
}

TEST(VTree, can_erase_t_5)
{
	AVL_Tree<int> t;
	t.insert(10);
	t.insert(6);
	t.insert(4);
	t.insert(15);
	t.insert(20);
	t.insert(1);
	t.insert(8);
	t.insert(11);
	t.insert(12);
	t.print(t.get_head());
	t.erase(4);
	t.erase(12);
	t.erase(10);

	ASSERT_NO_THROW(t.print(t.get_head()));

}


//Сделать повороты при удалении.