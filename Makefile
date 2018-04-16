OPCOES_COMPILADOR=-I./lib -lglut -lGLU -lSOIL -lGLEW -lSDL_mixer -lGL -lm -w
LIB=./lib/
SRC=./src/
TODOS_ARQUIVOS_OBJ = $(SRC)main.o $(LIB)texto.o $(LIB)texturas.o $(LIB)pontuacao.o

$(LIB)%.o: $(LIB)%.c
	@echo "Compilando as bibliotecas.."
	@gcc -o $@ -c $< $(OPCOES_COMPILADOR)

$(SRC)%.o: $(SRC)%.c
	@echo "Compilando componentes do jogo.."
	@gcc -o $@ -c $< $(OPCOES_COMPILADOR)

all: $(TODOS_ARQUIVOS_OBJ)
	@echo "Compilando o jogo.."
	@chmod 777 pontuacoes.txt
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
