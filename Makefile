COMPILE.C=$(COMPILE.cc)
COMPILE.cc=$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
CXXFLAGS=-g3 -I headers -I rapidjson/include/rapidjson
CPPFLAGS= -Wall -Wextra -Wpedantic 
CXX= g++
OUTPUT_OPTION = -o $@
#Linking:
LINK.o = $(CC) $(LDFLAGS) $(TARGET_ARCH)
CC= g++

vpath %.cc sources
vpath %.h headers

#rules:

%: %.o 
	$(LINK.o) $(OUTPUT_OPTION) $^
%.o: %.c++
	$(COMPILE.C) $(OUTPUT_OPTION) $<

run: c++
	valgrind ./c++
c++: c++.o string_op.o entry.o print_m.o manage_entries.o

manage_entries.o: manage_entries.cc
string_op.o: string_op.cc
entry.o: entry.cc
print_m.o: print_m.cc
c++.o: c++.cc c++.h

.INTERMEDIATE: *.o

.PHONY: depend #Now the file will be updated each time it is called.
depend: c++.cc
	g++ -I headers -M $(CPPFLAGS) $^ > $@
	more depend

.PHONY:clean
clean:
	rm -rf *.o c++