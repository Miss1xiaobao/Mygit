#simple makefile

objects = test1.o

test1:$(objects)
	@gcc -o test1 $(objects)

test1.o:test1.h


.PHONY:clean exec
clean:
	@echo "clean *.o ELF"
	-rm *.o test1
	@echo "over"
exec:
	cd ..;pwd
	pwd
