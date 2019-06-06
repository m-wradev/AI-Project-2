default: greedy.cpp sa.cpp SumofGaussians.cpp
	g++ -c SumofGaussians.cpp
	g++ greedy.cpp SumofGaussians.o -o greedy
	g++ sa.cpp SumofGaussians.o -o sa
