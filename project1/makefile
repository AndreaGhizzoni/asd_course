CPP=g++
OUT=pokemon
IN=pokemon.cpp
CPPFLAGS= -DEVAL -O2 -std=c++11 

# default option to make 
default : clean run

test : clean compileall
	for number in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 ; do \
		cp dataset/input/input$$number.txt input.txt ; \
		./$(OUT) ; \
		echo "cat output:" ; \
		cat output.txt ; \
		echo "cat dataset/output" ; \
		cat dataset/output/output$$number.txt ; \
		echo "\n" ; \
	done
	

compileall :
	$(CPP) $(CPPFLAGS) -o $(OUT) $(IN)

run : compileall
	./$(OUT)

clean :
	@$(RM) $(OUT) output.txt

