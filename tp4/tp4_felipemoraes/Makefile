
# Parametros de Ambiente

CC = gcc
 
CFLAGS = -Wall


# Parametros de Projeto

# TODO: altere a lista de forma que contenha todos os arquivos .c 
#       do seu projeto, que devem estar nos locais correspondentes
#       do diretorio src/
SRC_EMULADOR = main.c func.c
SRC_MONTADOR = main.c lista.c assembler.c io.c
SRC_EXPANSOR = main.c expander.c io.c
SRC_LIGADOR = main.c linker.c lista.c

OBJS_EMULADOR = $(SRC_EMULADOR:%.c=build/emulador/%.o)
OBJS_MONTADOR = $(SRC_MONTADOR:%.c=build/montador/%.o)
OBJS_EXPANSOR = $(SRC_EXPANSOR:%.c=build/expansor/%.o)
OBJS_LIGADOR = $(SRC_LIGADOR:%.c=build/ligador/%.o)


# Executaveis

all: bin/emulador bin/montador bin/expansor bin/ligador

bin/emulador: $(OBJS_EMULADOR)
	@echo "+ Compilando programa \"$@\""
	@$(CC) $(CFLAGS) $(OBJS_EMULADOR) -o bin/emulador

bin/montador: $(OBJS_MONTADOR)
	@echo "+ Compilando programa \"$@\""
	@$(CC) $(CFLAGS) $(OBJS_MONTADOR) -o bin/montador

bin/expansor: $(OBJS_EXPANSOR)
	@echo "+ Compilando programa \"$@\""
	@$(CC) $(CFLAGS) $(OBJS_EXPANSOR) -o bin/expansor

bin/ligador: $(OBJS_LIGADOR)
	@echo "+ Compilando programa \"$@\""
	@$(CC) $(CFLAGS) $(OBJS_LIGADOR) -o bin/ligador


# Objetos

build/%.o: src/%.c src/%.h
	@echo "- Compilando objeto \"$@\""
	@$(CC) -c $(CFLAGS) $< -o $@

build/%.o: src/%.c
	@echo "- Compilando objeto \"$@\""
	@$(CC) -c $(CFLAGS) $< -o $@


# Auxiliares

clean:
	rm -f bin/* $(OBJS_EMULADOR) $(OBJS_MONTADOR) $(OBJS_EXPANSOR) $(OBJS_LIGADOR)

