OBJECTS = main.o

main.o: main.ll
	echo test
	$(LLC) --filetype=obj $< -o $@

include Makefile.rules
