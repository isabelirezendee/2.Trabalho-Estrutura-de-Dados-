# Compilador a ser usado
CC = gcc

# Opções de compilação:
# -Wall ativa todos os avisos de compilação
# -g gera informações de depuração para uso com gdb
CFLAGS = -Wall -g

# Arquivos-fonte do projeto
SRC = main.c bdpaciente.c

# Arquivos objeto gerados a partir dos arquivos .c
OBJ = $(SRC:.c=.o)

# Nome do executável final
EXEC = sistema

# Regra padrão: compila tudo quando digitamos 'make'
all: $(EXEC)

# Regra para gerar o executável a partir dos objetos
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para limpar os arquivos compilados
clean:
	rm -f *.o $(EXEC)
