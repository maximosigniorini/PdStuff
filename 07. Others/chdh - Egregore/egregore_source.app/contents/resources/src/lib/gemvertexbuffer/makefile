PD_DIR = /home/u32/pd
GEM_DIR = /home/u32/gem

# build flags

INCLUDES =  -I$(PD_DIR)/src -I.  -I$(GEM_DIR)/src -I$(PD_DIR)/src
CPPFLAGS  = -fPIC -DPD -O2 -funroll-loops -fomit-frame-pointer  -ffast-math \
    -Wall -W -Wno-unused -Wno-parentheses -Wno-switch -g


UNAME := $(shell uname -s)
ifeq ($(UNAME),Linux)
 CPPFLAGS += -DLINUX
 INCLUDES += 
 LDFLAGS =  -Wl,--export-dynamic -shared
 LIBS = 
 EXTENSION = pd_linux
 SOURCES_OPT = 
endif

ifeq (MINGW,$(findstring MINGW,$(UNAME)))
 CPPFLAGS += 
 INCLUDES += $(SOURCES_windows)
 LDFLAGS = -s -shared -Wl,--enable-auto-import
 LIBS += -L"$(PD_PATH)/src" -L"$(PD_PATH)/bin" -L"$(PD_PATH)/obj" \
	-lpd -lwsock32 -lkernel32 -luser32 -lgdi32 -liberty $(LIBS_windows) 
 EXTENSION = dll
 SOURCES_OPT = 
 PD_DIR = $(shell cd "$$PROGRAMFILES/pd" && pwd)
 ALL_CFLAGS += -mms-bitfields
endif

.SUFFIXES = $(EXTENSION)

SOURCES = gemvertexbuffer.cpp

all: $(SOURCES:.cpp=.$(EXTENSION)) $(SOURCES_OPT:.cpp=.$(EXTENSION))

%.$(EXTENSION): %.o
	gcc $(LDFLAGS) -o $*.$(EXTENSION) $*.o $(LIBS)

.cpp.o:
	g++ $(CPPFLAGS) $(INCLUDES) -o $*.o -c $*.cpp

.c.o:
	gcc $(CPPFLAGS) $(INCLUDES) -o $*.o -c $*.c

install:
	

clean:
	rm -f *.o
	rm -f *.$(EXTENSION)

distro: clean all
	rm *.o
