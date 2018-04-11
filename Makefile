OPCOES_COMPILADOR=-I./lib -lglut -lGLU -lSOIL -lGLEW -lGL -lm
LIB=./lib/
SRC=./src/
TODOS_ARQUIVOS_OBJ = $(SRC)main.o $(LIB)texto.o $(LIB)texturas.o

$(LIB)%.o: $(LIB)%.c
	@echo "Compilando as bibliotecas.."
	@gcc -o $@ -c $< $(OPCOES_COMPILADOR)

$(SRC)%.o: $(SRC)%.c
	@echo "Compilando componentes do jogo.."
	@gcc -o $@ -c $< $(OPCOES_COMPILADOR)

all: $(TODOS_ARQUIVOS_OBJ)
	@echo "Compilando o jogo.."
	@gcc -o start $(TODOS_ARQUIVOS_OBJ) $(OPCOES_COMPILADOR)

run: all
	@echo "Inciando.."
	@./start
	
clean:
	@echo "Limpando arquivos.."
	@rm -f start
	@rm -f *.o
	@rm -f ./src/*.o
	@rm -f ./lib/*.o
