TARGET = minecraft
OBJS = 

CFLAGS = -O3 -Wall -G0 -fomit-frame-pointer
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LDFLAGS = -mno-coff
LIBS = -lpspgu -lpspmath -lm -lpsppower

BUILD_PRX = 1
PRX_EXPORTS = exports.txt

PSPBIN_FW_VERSION = 371

include $(PSPSDKTOOLCHAIN)/build_prx.mak

all: eboot.pbp

clean:
	rm -rf obj/ eboot.pbp

debug: CFLAGS += -g
debug: all
