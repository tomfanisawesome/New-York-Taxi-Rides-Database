all:	dict1 dict2
	
dict_core.o:	dict_core.c dict_core.h
	gcc -c dict_core.c
	
dict1:	dict1.c dict1.h dict_core.h dict_core.o
	gcc dict1.c dict_core.o -o dict1
	
dict2:	dict2.c dict2.h dict_core.h dict_core.o
	gcc dict2.c dict_core.o -o dict2

clean:
	rm -f *.o
	rm -f dict1
	rm -f dict2

update:
	make clean
