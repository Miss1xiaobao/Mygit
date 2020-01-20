
objects = student_control.o student_dispatch.o student_module.o student_main.o slist.o

student_main: $(objects)
	gcc $^ -o $@

student_control.o : student_control.h student_dispatch.h student_module.h slist.h student.h
student_dispatch.o : student_control.h student_dispatch.h student_module.h slist.h student.h
student_module.o : student_control.h student_dispatch.h student_module.h slist.h student.h
student_main.o : student_control.h student_dispatch.h student_module.h slist.h student.h
slist.o: student_control.h student_dispatch.h student_module.h slist.h student.h

.PHONY: clean
clean:
	-rm *.o
