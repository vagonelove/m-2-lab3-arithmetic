// тесты для вычисления арифметических выражений

#include <gtest.h>
#include <arithmetic.h>

TEST(Arithmetic, can_create_Arithmetic)
{
	ASSERT_NO_THROW(Arithmetic a);
}
TEST(Arithmetic, simple_sum)
{
	Arithmetic a;
	string s;
	s = "12+8+9-9";
	a.divide(s);
	a.ToPostfix();
	EXPECT_EQ(20.0, a.calculate());
}
TEST(Arithmetic, unary_minus_with_brackets)
{
	Arithmetic a;
	string s;
	s = "-12.5+(-12.5)";
	a.divide(s);
	a.ToPostfix();
	EXPECT_EQ(-25.0, a.calculate());
}
TEST(Arithmetic, unary_minus_with_division)
{
	Arithmetic a;
	string s;
	s = "2/-2";
	a.divide(s);
	a.ToPostfix();
	EXPECT_EQ(-1.0, a.calculate());
}
TEST(Arithmetic, unary_minus_with_division_with_brackets)
{
	Arithmetic a;
	string s;
	s = "1/-(4+6)";
	a.divide(s);
	a.ToPostfix();
	EXPECT_EQ(-0.1, a.calculate());
}
TEST(Arithmetic, unary_minus_with_brackets_more_complex)
{
	Arithmetic a;
	string s;
	s = "1+(-2+3/4-2)";
	a.divide(s);
	a.ToPostfix();
	EXPECT_EQ(-2.25, a.calculate());
}
TEST(Arithmetic, lots_of_unary_minus)
{
	Arithmetic a;
	string s;
	s = "2-------2";
	a.divide(s);
	a.ToPostfix();
	a.print();
	EXPECT_EQ(0.0, a.calculate());
}
TEST(Arithmetic, unary_minus_before_brackets)
{
	Arithmetic a;
	string s;
	s = "-(2+1)";
	a.divide(s);
	a.ToPostfix();
	EXPECT_EQ(-3.0, a.calculate());
}
TEST(Arithmetic, throw_when_first_character_is_closing_bracket)
{
	Arithmetic a;
	string s;
	s = ")4*3";
	a.divide(s);
	ASSERT_ANY_THROW(a.ToPostfix());
}
TEST(Arithmetic, throw_when_first_character_is_operation)
{
	string s = "/4*3";
	ASSERT_ANY_THROW(isCorrect(s));
}
TEST(Arithmetic, throw_when_opening_bracket_goes_after_number)
{
	string s = "8(34+3)";
	ASSERT_ANY_THROW(isCorrect(s));
}
TEST(Arithmetic, throw_wrong_amounts_of_brackets)
{
	Arithmetic a;
	string s;
	s = "(8.0))";
	a.divide(s);
	ASSERT_ANY_THROW(isCorrect(s));
}
TEST(Arithmetic, throw_operation_after_opening_bracket)
{
	Arithmetic a;
	string s;
	s = "3+1*(/4)";
	a.divide(s);
	ASSERT_ANY_THROW(isCorrect(s));
}
TEST(Arithmetic, no_throw_unary_minus_after_opening_bracket)
{
	Arithmetic a;
	string s;
	s = "3+1*(-4)";
	a.divide(s);
	ASSERT_NO_THROW(a.ToPostfix());
}
TEST(Arithmetic, throw_last_character_is_operation)
{
	string s = "3+1*";
	ASSERT_ANY_THROW(isCorrect(s));
}
TEST(Arithmetic, throw_last_character_is_opening_bracket)
{
	string s = "3+1*(";
	ASSERT_ANY_THROW(isCorrect(s));
}
