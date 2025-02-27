



default:
	@g++ -std=c++11 main.cpp -o  test test.h cards.h deck.h handEvaluator.h player.h winningOdds.h 
	@ ./test


test: main.cpp test.h cards.h deck.h handEvaluator.h player.h winningOdds.h
	@g++ -g -o test main.cpp test.h cards.h deck.h handEvaluator.h player.h winningOdds.h 
	@valgrind --leak-check=full ./test

clear-drivers:
	@rm drivers/*.out

clean:
	@rm *.out drivers/*.out