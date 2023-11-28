#include "pch.h"
#include "CppUnitTest.h"
#include "../LAB9.2/LAB9.2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest92A
{
	TEST_CLASS(UnitTest92A)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			const int N = 3;
			Student students[N] = {
				{ "Student1", 1, PHYSICS, 5, 5, 0 },
				{ "Student2", 2, MATH, 5, 5, 0 },
				{ "Student3", 3, PHYSICS, 5, 5, 0 }
			};

			double result = CalculatePercentGoodPhysicsMath(students, N);
			Assert::AreEqual(100.0 , result);
		}
	};
}
