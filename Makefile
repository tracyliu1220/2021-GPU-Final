TARGET=gpu

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	g++ $(TARGET).cpp -o $(TARGET) -lGL -lGLU -lglut
