.PHONY: default clean

default:
	clang++ -o kernelcomp -arch x86_64 -std=gnu++11 -Wall -W -I/usr/local/include -L/usr/lib -lcompression -L/usr/local/lib -lssl -lcrypto -lplist-2.0 -lgeneral -limg4tool -pedantic -O3 kernelcomp.cpp
procursus:
	clang++ -o kernelcomp -arch x86_64 -std=gnu++11 -Wall -W -I${PROCURSUS}/include -L/usr/lib -lcompression -L${PROCURSUS}/lib -lssl -lcrypto -lplist-2.0 -lgeneral -limg4tool -pedantic -O3 kernelcomp.cpp

clean:
	$(RM) kernelcomp