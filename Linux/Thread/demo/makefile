CC = g++ # 编译器
CFLAGS = -std=c++11 # 编译选项
LDFLAGS = -pthread # 链接选项

TARGET = mythread # 目标可执行文件名
SRC = mythread.cpp # 源文件

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)
