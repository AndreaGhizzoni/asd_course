CPP=g++
OUT=somma
IN=somma.cpp
CPPFLAGS= -DEVAL -O2 -std=c++11 -static

# default option to make 
default : clean run

compileall :
	$(CPP) $(CPPFLAGS) -o $(OUT) $(IN)

run : compileall
	./$(OUT)

clean :
	@$(RM) $(OUT) output.txt

