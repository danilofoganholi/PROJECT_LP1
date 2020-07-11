CC=gcc
FLAGS= -Wall -Wpedantic -Wextra -std=c99 -Wvla
SOURCE=main.c ./Motor/Motor.c ./Chassi/Chassi.c ./Jante/Jante.c ./Pneu/Pneu.c ./Carro/Carro.c readFiles.c ./Pedidos/Pedidos.c
TARGET=LP1

all:
	$(CC) $(FLAGS) $(SOURCE) -o $(TARGET)
	
debug:
	$(CC) $(FLAGS) -g $(SOURCE) -o $(TARGET)
	
clean:
	rm -rf $(TARGET)