# 定義編譯器
CC=gcc

# 定義編譯器標誌
CFLAGS = -O1 -g -Wall -Werror -Idudect -I.

# 定義鏈接器標誌
LDFLAGS=-lm

# 定義目標執行檔名稱
TARGET=mcts

# 定義源文件
SOURCES=mcts.c fpmath.c

# 定義對象文件
OBJS=$(SOURCES:.c=.o)

# 定義頭文件
HEADERS=mcts.h fpmath.h

# 預設目標
all: $(TARGET)

# 依賴於對象文件的目標
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) -lm

# 將 .c 文件編譯成 .o 文件，並添加頭文件依賴
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# 定義 'make clean' 命令來清理編譯產生的文件
clean:
	rm -f $(TARGET) $(OBJS)

