#include "pch.h"
#include "CppUnitTest.h"

#include "../RingBuffer/RingBuffer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests {

	TEST_CLASS(TRingBuffer)	{
	public:		
		TEST_METHOD(Ctor)
		{
			RingBuffer<int, 4> buf;

			Assert::IsTrue(buf.Empty(), L"0");
			Assert::IsTrue(buf.Size() == 0, L"1");
			Assert::IsTrue(buf.Capacity() == 4, L"2");
		}

		TEST_METHOD(Push)
		{
			RingBuffer<int, 4> buf;

			buf.Push(0);
			Assert::IsTrue(buf.Size() == 1, L"0");
			Assert::IsTrue(buf.Front() == 0, L"1");
		}

		TEST_METHOD(PushPop)
		{
			RingBuffer<int, 4> buf;

			buf.Push(0);
			Assert::IsTrue(buf.Size() == 1, L"0");
			buf.Pop();
			Assert::IsTrue(buf.Size() == 0, L"1");
		}

		TEST_METHOD(Full)
		{
			const size_t n = 4;
			RingBuffer<int, n> buf;

			for (size_t i = 0; i < n; ++i) buf.Push(0);
			Assert::IsTrue(buf.Size() == n, L"0");
			Assert::IsTrue(buf.Full(), L"1");
		}

		TEST_METHOD(LoopingFront)
		{
			const size_t n = 4;
			RingBuffer<int, n> buf;

			for (size_t i = 0; i < n; ++i)
				buf.Push(i);

			for (size_t i = 0; i < n; ++i) {
				auto x = buf.Front();
				buf.Pop();
				Assert::IsTrue(x == i, L"0");
			}
			Assert::IsTrue(buf.Empty(), L"1");
		}
	};
}
