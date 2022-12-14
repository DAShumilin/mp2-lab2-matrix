#include "tmatrix.h"
#include <gtest.h>

class VectorFixture : public ::testing::Test {

public:

	TDynamicVector <int> v1, v2, res;
	VectorFixture() : v1(10), v2(10), res(10) {
		for (int i = 0; i < 10; ++i) {
			res[i] = 1;
			if (i % 2 == 0) {
				v1[i] = 1;
			}
			else if (i % 2 == 1) {
				v2[i] = 1;
			}
		}
	};
};

TEST_F(VectorFixture, test_1) {
	EXPECT_EQ(v1 + v2, res);
}

TEST_F(VectorFixture, test_2) {
	EXPECT_EQ(res - v1, v2);
}

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	double arr[] = { 1.0, -2.0, 3.0, 4.0 };
	size_t size = 4;
	TDynamicVector<double> v(arr, size);
	TDynamicVector<double> copy(v);

	EXPECT_TRUE(v == copy);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	double arr[] = { 1.0, -2.0, 3.0, 4.0 };
	size_t size = 4;
	TDynamicVector<double> v(arr, size);
	TDynamicVector<double> copy(v);

	EXPECT_TRUE(&v[0] != &copy[0]);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> vector(4);

	EXPECT_ANY_THROW(vector.at(-1));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> vector(4);

	EXPECT_ANY_THROW(vector.at(4));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> vector(4);

	EXPECT_NO_THROW(vector = vector);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v1(4), v2(4);
	v1 = v2;

	EXPECT_EQ(v2, v1);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v1(4), v2(5);
	v1 = v2;

	EXPECT_EQ(v1.size(), 5);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(4), v2(5);
	v1 = v2;

	EXPECT_EQ(v2, v1);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	int arr[] = { 1, -1, 2, 0 };
	TDynamicVector<int> v1(arr, 4), v2(arr, 4);

	EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> vector(3);

	EXPECT_TRUE(vector == vector);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(4), v2(5);

	EXPECT_TRUE(v1 != v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> vector(3), exp(3);
	vector[0] = 2;
	vector[1] = -1;
	vector[2] = 0;
	vector = vector + 2;
	exp[0] = 4;
	exp[1] = 1;
	exp[2] = 2;

	EXPECT_EQ(exp, vector);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> vector(3), exp(3);
	vector[0] = 2;
	vector[1] = -1;
	vector[2] = 0;
	vector = vector - 2;
	exp[0] = 0;
	exp[1] = -3;
	exp[2] = -2;

	EXPECT_EQ(exp, vector);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> vector(3), exp(3);
	vector[0] = 2;
	vector[1] = -1;
	vector[2] = 0;
	vector = vector * 2;
	exp[0] = 4;
	exp[1] = -2;
	exp[2] = 0;

	EXPECT_EQ(exp, vector);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v1(2), v2(2), exp(2);
	v1[0] = 1; v1[1] = 2;
	v2[0] = 3; v2[1] = 4;
	exp[0] = 4, exp[1] = 6;

	EXPECT_EQ(exp, v1 + v2);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3), v2(4);

	EXPECT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v1(2), v2(2), exp(2);
	v1[0] = 1; v1[1] = 2;
	v2[0] = 3; v2[1] = 4;
	exp[0] = -2, exp[1] = -2;

	EXPECT_EQ(exp, v1 - v2);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3), v2(4);

	EXPECT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v1(2), v2(2);
	v1[0] = 1; v1[1] = 2;
	v2[0] = 3; v2[1] = 4;
	int exp = 11;

	EXPECT_EQ(exp, v1 * v2);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3), v2(4);

	EXPECT_ANY_THROW(v1 * v2);
}