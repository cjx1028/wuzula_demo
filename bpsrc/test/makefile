
APPINCL = -I../../vendor/jit/include
include ../../mkrules/$(MYOS).mkrules.4o

APPLIB = -lbsecurity -lbbp -lbdao -lbfront -lbexpr -lbthrd -lbbase -L../../vendor/jit/lib -lcapi 

DLL1 = demo_1.so
OBJ1 = demo.o ../../libsrc/front/bpmain.o

all: $(DLL1) 

include ../../mkrules/mkrules.4so

