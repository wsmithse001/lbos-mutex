CC = g++
COMMON_FLAGS = -std=c++20
WARNING_FLAGS = -Wall -Wextra -Wpedantic -Wformat=2 -Wconversion -Wshadow -Wold-style-cast -Woverloaded-virtual -Werror
DEBUG_FLAGS = -g3 -Og -D_GLIBCXX_ASSERTIONS -DDEBUG=1
RELEASE_FLAGS = -O3 -DNDEBUG -D_FORTIFY_SOURCE=2 -mwindows -s -flto -fstack-protector-strong
LIBS = -pthread
TARGET = main.out
SOURCE = main.cpp

$(TARGET): $(SOURCE)
	$(CC) $(COMMON_FLAGS) $(WARNING_FLAGS) $(DEBUG_FLAGS) $(SOURCE) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)
