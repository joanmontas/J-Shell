# Copyright Joan Montas
# All rights reserved.
# License under GNU General Public License v3.0

CC = gcc
CFLAGS = --std=gnu11 -Wextra -Wpedantic -g -Wformat -Wshadow -Wconversion -Wall -fsanitize=address
EXECUTABLE_NAME = jshell

TEST_FRAMEWORK = -lcunit

all: $(EXECUTABLE_NAME) tests

$(EXECUTABLE_NAME): main.o Token.o String.o List.o Lexer.o Parser.o Ast.o Evaluator.o
	$(CC) $(CFLAGS) -o $(EXECUTABLE_NAME) main.o Token.o String.o List.o Lexer.o Parser.o Ast.o Evaluator.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

Lexer.o: ./Lexer/Lexer.c ./Lexer/Lexer.h
	$(CC) $(CFLAGS) -c ./Lexer/Lexer.c

Parser.o: ./Parser/Parser.c ./Parser/Parser.h
	$(CC) $(CFLAGS) -c ./Parser/Parser.c

Ast.o: ./Ast/Ast.c ./Ast/Ast.h
	$(CC) $(CFLAGS) -c ./Ast/Ast.c

Evaluator.o: ./Evaluator/Evaluator.c ./Evaluator/Evaluator.h
	$(CC) $(CFLAGS) -c ./Evaluator/Evaluator.c

String.o: ./String/String.c ./String/String.h
	$(CC) $(CFLAGS) -c ./String/String.c

List.o: ./List/List.c ./List/List.h
	$(CC) $(CFLAGS) -c ./List/List.c

Token.o: ./Token/Token.c ./Token/Token.h
	$(CC) $(CFLAGS) -c ./Token/Token.c

tests: Tests.o String.o List.o Lexer.o Parser.o Ast.o Evaluator.o string_test.o list_test.o token_test.o lexer_test.o parser_test.o ast_test.o evaluator_test.o
	$(CC) $(CFLAGS) -o tests Tests.o String.o List.o Lexer.o Parser.o Token.o Ast.o Evaluator.o string_test.o list_test.o token_test.o lexer_test.o parser_test.o ast_test.o evaluator_test.o $(TEST_FRAMEWORK)

Tests.o: ./Test/Tests.c
	$(CC) $(CFLAGS) -c ./Test/Tests.c

string_test.o: ./Test/string_test/string_test.c ./Test/string_test/string_test.h
	$(CC) $(CFLAGS) -c ./Test/string_test/string_test.c

list_test.o: ./Test/list_test/list_test.c ./Test/list_test/list_test.h
	$(CC) $(CFLAGS) -c ./Test/list_test/list_test.c

token_test.o: ./Test/token_test/token_test.c ./Test/token_test/token_test.h
	$(CC) $(CFLAGS) -c ./Test/token_test/token_test.c

lexer_test.o: ./Test/lexer_test/lexer_test.c ./Test/lexer_test/lexer_test.h
	$(CC) $(CFLAGS) -c ./Test/lexer_test/lexer_test.c

parser_test.o: ./Test/parser_test/parser_test.c ./Test/parser_test/parser_test.h
	$(CC) $(CFLAGS) -c ./Test/parser_test/parser_test.c

ast_test.o: ./Test/ast_test/ast_test.c ./Test/ast_test/ast_test.h
	$(CC) $(CFLAGS) -c ./Test/ast_test/ast_test.c

evaluator_test.o: ./Test/evaluator_test/evaluator_test.c ./Test/evaluator_test/evaluator_test.h
	$(CC) $(CFLAGS) -c ./Test/evaluator_test/evaluator_test.c

clean:
	rm ./*.o ./$(EXECUTABLE_NAME) ./tests