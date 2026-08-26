
# Compilador
CC = gcc

# Pacotes do Allegro utilizados
PKG = allegro-5 \
      allegro_primitives-5 \
      allegro_image-5 \
      allegro_font-5 \
      allegro_ttf-5

# Flags de compilação
CFLAGS = -Wall -Wextra -std=c99 $(shell pkg-config --cflags $(PKG))

# Bibliotecas para linkedição
LIBS = $(shell pkg-config --libs $(PKG))

# Nome do executável
TARGET = jogo

# Arquivos-fonte
SRCS = \
	src/main.c \
	src/jogador.c \
	src/inimigo.c \
	src/mapa.c \
	src/telas.c

# Regra padrão
all: $(TARGET)

# Compilação
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LIBS)

# Executa o jogo
run: $(TARGET)
	./$(TARGET)

# Limpa os arquivos gerados
clean:
	rm -f $(TARGET)

# Recompila tudo do zero
rebuild: clean all

.PHONY: all clean rebuild run