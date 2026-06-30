CC = clang
CFLAGS = $(shell pkg-config --cflags gtk4 libcurl)
LIBS = $(shell pkg-config --libs gtk4 libcurl)
TARGET = my_gtk_app

all: $(TARGET)

$(TARGET): main.c
	$(CC) main.c -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)
