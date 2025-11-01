# Variables
LUA_SRC = lua-5.4.8/src
LUA_OBJS = $(LUA_SRC)/lapi.o $(LUA_SRC)/lauxlib.o $(LUA_SRC)/lbaselib.o \
           $(LUA_SRC)/lcode.o $(LUA_SRC)/lcorolib.o $(LUA_SRC)/lctype.o \
           $(LUA_SRC)/ldebug.o $(LUA_SRC)/ldo.o $(LUA_SRC)/ldump.o \
           $(LUA_SRC)/lfunc.o $(LUA_SRC)/lgc.o $(LUA_SRC)/linit.o \
           $(LUA_SRC)/liolib.o $(LUA_SRC)/llex.o $(LUA_SRC)/lmathlib.o \
           $(LUA_SRC)/lmem.o $(LUA_SRC)/loadlib.o $(LUA_SRC)/lobject.o \
           $(LUA_SRC)/lopcodes.o $(LUA_SRC)/loslib.o $(LUA_SRC)/lparser.o \
           $(LUA_SRC)/lstate.o $(LUA_SRC)/lstring.o $(LUA_SRC)/lstrlib.o \
           $(LUA_SRC)/ltable.o $(LUA_SRC)/ltablib.o $(LUA_SRC)/ltm.o \
           $(LUA_SRC)/lundump.o $(LUA_SRC)/lutf8lib.o $(LUA_SRC)/lvm.o \
           $(LUA_SRC)/lzio.o

NUKLEAR_SRC = nuklear

SDL2_SRC = /usr/include/SDL2

APP_OBJS = src/main.o
APP_SRC = src/headers
TARGET = HWOpenBuilder

CFLAGS = -I$(LUA_SRC) -I$(NUKLEAR_SRC) -I$(SDL2_SRC) -I$(APP_SRC)

# Compilar tu aplicación
src/%.o: src/%.c
	gcc -c -O2 -Wall -Wextra $(CFLAGS) $< -o $@

# Linkar todo
$(TARGET): $(LUA_OBJS) $(APP_OBJS)
	gcc -o $@ $(LUA_OBJS) $(APP_OBJS) -lm -ldl -lSDL2

# Limpiar
clean:
	rm -f $(LUA_OBJS) $(APP_OBJS) $(TARGET)

.PHONY: clean
