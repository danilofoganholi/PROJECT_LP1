CC=gcc
FLAGS= -Wall -Wpedantic -Wextra -std=c99 -Wvla
SOURCE=main.c Motor.c Chassi.c Jante.c Pneu.c Carro.c readFiles.c Pedidos.c producao.c
TARGET=LP1

all:
	$(CC) $(FLAGS) $(SOURCE) -o $(TARGET)
	
debug:
	$(CC) $(FLAGS) -g $(SOURCE) -o $(TARGET)
	
clean:
	rm -rf $(TARGET)