TARGET=gpu
TARGET2=gpu-gl

all: $(TARGET) $(TARGET2)

$(TARGET): $(TARGET).cpp
	g++ $(TARGET).cpp -o $(TARGET) -lGL -lGLU -lglut

$(TARGET2): $(TARGET2).cpp
	g++ $(TARGET2).cpp -o $(TARGET2) -lGL -lGLU -lglut 

test: $(TARGET2)
	./$(TARGET2)
