# Criado por Matheus C. Teixeira

sort: sort.cpp estrutura_de_dados.o
	g++ sort.cpp estrutura_de_dados.o -o sort

estrutura_de_dados.o: estrutura_de_dados.cpp
	g++ estrutura_de_dados.cpp -c

