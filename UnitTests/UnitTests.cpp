#include "pch.h"
#include "CppUnitTest.h"
#include "../AIS LAB 2/Functions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:
		
		TEST_METHOD(TestDifferentLength)
		{
			Assert::AreNotEqual("a", "ab");
		}
		TEST_METHOD(TestZeroLength)
		{
			Assert::AreEqual("", "");
		}
		TEST_METHOD(TestLength1)
		{
			Assert::AreEqual("a", "a");
			Assert::AreNotEqual("a", "b");
		}
		TEST_METHOD(TrueRandomTests)
		{
			for (int i = 1; i <= 5; i++) {
				string str1 = getRandomString(pow(10, 1));
				string str2 = "";
				int breaker = (int)(((double)rand() / (double)RAND_MAX) * pow(10, 1));

				for (int i = breaker; i < pow(10, 1); i++) {
					str2 += str1.at(i);
				}
				for (int i = 0; i < breaker; i++) {
					str2 += str1.at(i);
				}

				Assert::AreEqual(isCyclicRotationKMP(str1, str2), true);
			}									
		}
		TEST_METHOD(RandomTests)
		{
			for (int i = 1; i <= 5; i++) {
				string str1 = getRandomString(pow(10, 1));
				string str2 = getRandomString(pow(10, 1));
				
				Assert::AreEqual(isCyclicRotationKMP(str1, str2), isCyclicRotation(str1, str2));
			}
		}
	};
}
