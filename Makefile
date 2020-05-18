################
#   Makefile   # 
################

#Name, headers, sources
TARGET=Drone
_DEPS=cmp.hh size.hh Vector.hh Matrix.hh Dr3D_gnuplot_api.hh Draw3D_api_interface.hh Rotation.hh Drawable.hh Solid.hh Cuboid.hh Stone.hh Drone.hh Screw.hh Surface.hh
_OBJ=main.o cmp.o VectorComp.o MatrixComp.o Dr3D_gnuplot_api.o Cuboid.o Drone.o

####DIRS###
TRG_DIR=./
OBJ_DIR=./obj
INC_DIR=./inc
SRC_DIR=./src

###COMPILER###
CC = g++
CFLAGS = -Wall -pedantic -std=c++17 -iquote $(INC_DIR)
LFLAGS = -Wall -pedantic -std=c++17 -iquote $(INC_DIR) -lpthread

###FORMULA###
DEPS = $(patsubst %,$(INC_DIR)/%,$(_DEPS))
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

all: build start

build: $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LFLAGS)

.PHONY: clean

clean:
	rm -f ${TRGDIR}$(TARGET) ${OBJ_DIR}/*

start:
	./${TARGET}