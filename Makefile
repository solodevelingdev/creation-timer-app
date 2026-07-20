CC = clang
CFLAGS = $(shell pkg-config --cflags gtk4 libcurl)
LIBS = $(shell pkg-config --libs gtk4 libcurl)
TARGET = my_gtk_app

# MacOS 
APP = CreationTimer.app

all: $(TARGET)

$(TARGET): creation_timer_app.c
	glib-compile-resources --generate --generate-source resources.xml
	glib-compile-resources --generate --generate-header resources.xml
	$(CC) creation_timer_app.c resources.c -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm -rf $(TARGET) resources.c resources.h resources.gresource $(APP)

bundle: my_gtk_app
		./generate_icons.sh
		mkdir -p $(APP)
		mkdir -p $(APP)/Contents/MacOS
		mkdir -p $(APP)/Contents/Resources

		cp my_gtk_app $(APP)/Contents/MacOS/CreationTimer
		cp packaging/macos/Info.plist $(APP)/Contents/
		cp packaging/macos/AppIcon.icns $(APP)/Contents/Resources/
