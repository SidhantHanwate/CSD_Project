all: run

rundoto: parser vm 
	./parser < $(fname) > tac.txt
	./tac-vm $(fname).vm

run: parser vm 
	./parser < $(fname) > tac.txt
	./tac-vm  ../VM/input/vm.vm

	# Concatenate the temporary VM code with existing vm.vm (if it exists)
	#if [ -f vm.vm ]; then \
	#    cat vm.vm vm_temp.vm > vm_concatenated.vm; \
	#    mv vm_concatenated.vm vm.vm; \
	#else \
	#    mv vm_temp.vm vm.vm; \
	#fi

	#rm vm_temp.vm  # Remove the temporary file

vm: tac-vm.cpp
	g++ tac-vm.cpp -o tac-vm

parser: y.tab.c lex.yy.c y.tab.h
	g++ -w y.tab.c lex.yy.c -lfl -o parser

y.tab.c: parser.y
	yacc -v -d -t -Wno-other parser.y

lex.yy.c: lexical_analyser.l
	lex lexical_analyser.l

optimal:  
	./Optimization/a.out > tac_optimized.txt

clean:
	rm -f parser y.tab.c lex.yy.c y.tab.h y.output a.out tac-vm tac.txt *.vm bundle
