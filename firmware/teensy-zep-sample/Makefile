            ZEPTEENSY = zepteensy
        ZEPTEENSY_SRC = $(ZEPTEENSY).cpp \
			Clock.cpp \
			CyclicQueue.cpp \
			EventQueue-impl.cpp \
			Events.cpp \
			register_inputs.cpp \
                        TeensyPackage.cpp
        ZEPTEENSY_OBJ = $(ZEPTEENSY).o \
			Clock.o \
			CyclicQueue.o \
			EventQueue-impl.o \
			Events.o \
			register_inputs.o \
                        TeensyPackage.o
       ZEPTEENSY_LIBS = $(CORE_LIB) $(EXT_LIB)
        ZEPTEENSY_ELF = $(ZEPTEENSY).elf
        ZEPTEENSY_HEX = $(ZEPTEENSY).hex
        ZEPTEENSY_EEP = $(ZEPTEENSY).eep

              OBJECTS = $(ZEPTEENSY_OBJ)
             BINARIES = $(ZEPTEENSY_ELF)
                HEXES = $(ZEPTEENSY_HEX)
                 EEPS = $(ZEPTEENSY_EEP)

                TIME := $(shell date +"%s")

                QUIET = @

# Teensy libraries used (directly or by dependency).
#            LIBRARIES = Audio Wire SPI SD
#            LIBRARIES = Snooze
#            LIBRARIES = ADC

# Teensy version (30, 31 or 32).
           TEENSY_VER = 32
                BOARD = TEENSY$(TEENSY_VER)

# CPU speed (48000000, 72000000 or 96000000).
            CPU_SPEED = 96000000

# USB type and keyboard layout.
             USB_DEFS = -DUSB_SERIAL_HID
        KEYBOARD_DEFS = -DLAYOUT_US_ENGLISH

# Arduino and Teensyduino version numbers.
#          ARDUINO_VER = 10603
#      TEENSYDUINO_VER = 124
          ARDUINO_VER = 10802
      TEENSYDUINO_VER = 136
#          ARDUINO_VER = 10804
#      TEENSYDUINO_VER = 139

# Symbols to be defined (opt.)
#        ZEPTEENSY_DEFS = -DSOMETHING=123

# Compiler & linker flags.
            OPT_FLAGS = -O
         COMMON_FLAGS = -Wall -ffunction-sections -fdata-sections -MMD -nostdlib
ifeq ($(TEENSY_VER), 32)
             CPU_DEFS = -D__MK20DX256__
             LDSCRIPT = $(COREPATH)/mk20dx256.ld
endif
ifeq ($(TEENSY_VER), 31)
             CPU_DEFS = -D__MK20DX256__
             LDSCRIPT = $(COREPATH)/mk20dx256.ld
endif
ifeq ($(TEENSY_VER), 30)
             CPU_DEFS = -D__MK20DX128__
             LDSCRIPT = $(COREPATH)/mk20dx128.ld
endif
            CPU_FLAGS = -mthumb -mcpu=cortex-m4
              DEFINES = $(CPU_DEFS) -DTEENSYDUINO=$(TEENSYDUINO_VER) -DARDUINO=$(ARDUINO_VER) -DF_CPU=$(CPU_SPEED) -DARDUINO_ARCH_AVR $(USB_DEFS) $(KEYBOARD_DEFS) $(ZEPTEENSY_DEFS)
             CXXFLAGS = $(OPT_FLAGS) $(COMMON_FLAGS) -fno-exceptions -felide-constructors -std=gnu++0x -fno-rtti $(CPU_FLAGS) $(DEFINES) $(INCLUDES)
               CFLAGS = $(OPT_FLAGS) $(COMMON_FLAGS) $(CPU_FLAGS) $(DEFINES) $(INCLUDES)
            CASMFLAGS = $(OPT_FLAGS) $(COMMON_FLAGS) -x assembler-with-cpp $(CPU_FLAGS) $(DEFINES) $(INCLUDES)
              ARFLAGS = rcs
#              LDSPECS = --specs=nano.specs
              LDSPECS =
              LDFLAGS = $(OPT_FLAGS) -Wl,--gc-sections,--relax,--defsym=__rtc_localtime=$(TIME) $(LDSPECS) -T$(LDSCRIPT) $(CPU_FLAGS)
             SYS_LIBS = -larm_cortexM4l_math -lm

# Directory to build libraries and core in.
             BUILDDIR = ../build

# Base directory for arduino  and teensyduino.
#          ARDUINOPATH = $(HOME)/arduino-1.6.3
          ARDUINOPATH = $(HOME)/arduino-1.8.2
#          ARDUINOPATH = $(HOME)/arduino-1.8.4

# Location of Teensy Loader, teensy_post_compile and teensy_reboot.
            TOOLSPATH = $(ARDUINOPATH)/hardware/tools

# Location of Teensy 3 core.
             COREPATH = $(ARDUINOPATH)/hardware/teensy/avr/cores/teensy3

# Location of Teensy libraries.
          LIBRARYPATH = $(ARDUINOPATH)/hardware/teensy/avr/libraries

# Location of the arm-none-eabi compiler.
         COMPILERPATH = $(TOOLSPATH)/arm/bin

# Compiler tools.
                   CC = $(COMPILERPATH)/arm-none-eabi-gcc
                  CXX = $(COMPILERPATH)/arm-none-eabi-g++
                   AR = $(COMPILERPATH)/arm-none-eabi-gcc-ar
              OBJCOPY = $(COMPILERPATH)/arm-none-eabi-objcopy
                 SIZE = $(COMPILERPATH)/arm-none-eabi-size

# Core sources and objects.
        CORE_C_FILES := $(wildcard $(COREPATH)/*.c)
      CORE_CPP_FILES := $(wildcard $(COREPATH)/*.cpp)
        CORE_S_FILES := $(wildcard $(COREPATH)/*.S)
        CORE_OBJECTS := $(foreach src,$(CORE_C_FILES:.c=.o) $(CORE_CPP_FILES:.cpp=.o) $(CORE_S_FILES:.S=.o), $(BUILDDIR)/$(src))
             CORE_LIB = corelib.a

# Lists of sources and objects for Teensy libraries used.
         EXT_C_FILES := $(foreach libdir,$(LIBRARIES), $(wildcard $(LIBRARYPATH)/$(libdir)/*.c) $(wildcard $(LIBRARYPATH)/$(libdir)/utility/*.c))
       EXT_CPP_FILES := $(foreach libdir,$(LIBRARIES), $(wildcard $(LIBRARYPATH)/$(libdir)/*.cpp) $(wildcard $(LIBRARYPATH)/$(libdir)/utility/*.cpp))
         EXT_OBJECTS := $(foreach src,$(EXT_C_FILES:.c=.o) $(EXT_CPP_FILES:.cpp=.o), $(BUILDDIR)/$(src))
           UTIL_DIRS := $(foreach libdir,$(LIBRARIES), $(wildcard $(LIBRARYPATH)/$(libdir)/utility) $(wildcard $(LIBRARYPATH)/$(libdir)/util))
           UTILS_INC := $(foreach dir,$(UTIL_DIRS), -I$(dir))
              EXT_LIB = extlib.a

# Include search paths.
             EXT_INC := $(foreach libdir,$(LIBRARIES), -I$(LIBRARYPATH)/$(libdir))
             INCLUDES = -I. -I$(COREPATH) $(EXT_INC)

all: hex

clean:
	@echo "Cleaning up"
	$(QUIET)rm -f *.o *.d

tidy: clean
	$(QUIET)rm -f $(CORE_LIB) $(EXT_LIB) $(BINARIES) $(EEPS) $(HEXES)
	$(QUIET)rm -rf "$(BUILDDIR)"

build: $(BINARIES)

hex: $(EEPS) $(HEXES) sizes

sizes: $(BINARIES) 
	@echo "text: code and read-only data"
	@echo "data: read-write data"
	@echo "bss:  zero initialized data"
	@echo "dec:  total of 'text', 'data', 'bss'"
	@echo "hex:  hexidecimal equivalent of 'dec'"
	$(QUIET)$(SIZE) $?

test:
	@echo $(UTILS_INC)

upload: $(ZEPTEENSY_HEX)
	@echo "Uploading to teensy"
	$(QUIET)-$(TOOLSPATH)/teensy_post_compile -file=$(ZEPTEENSY) -path=$(CURDIR) -tools=$(TOOLSPATH) -board=$(BOARD) -reboot 
#	@echo "Rebooting teensy"
#	$(QUIET)-$(TOOLSPATH)/teensy_reboot

reboot:
	@echo "Rebooting teensy"
	$(QUIET)-$(TOOLSPATH)/teensy_reboot

$(ZEPTEENSY_ELF): $(ZEPTEENSY_OBJ) $(ZEPTEENSY_LIBS) $(LDSCRIPT)
	@echo "[LD]\t$@"
	$(QUIET)$(CC) $(LDFLAGS) -o $@ $(ZEPTEENSY_OBJ) $(ZEPTEENSY_LIBS) $(SYS_LIBS)

$(CORE_LIB): $(CORE_OBJECTS)
	@echo "[AR]\t$@"
	$(QUIET)$(AR) $(ARFLAGS) $@ $?
	
$(EXT_LIB): $(EXT_OBJECTS)
	@echo "[AR]\t$@"
	$(QUIET)$(AR) $(ARFLAGS) $@ $?

$(BUILDDIR)/%.o: %.c
	@echo "[CC]\t$<"
	$(QUIET)mkdir -p "$(dir $@)"
	$(QUIET)$(CC) -c $(CFLAGS) $(UTILS_INC) -o $@ $<

$(BUILDDIR)/%.o: %.cpp
	@echo "[CXX]\t$<"
	$(QUIET)mkdir -p "$(dir $@)"
	$(QUIET)$(CXX) -c $(CXXFLAGS) $(UTILS_INC) -o $@ $<

$(BUILDDIR)/%.o: %.ino
	@echo "[CXX]\t$<"
	$(QUIET)mkdir -p "$(dir $@)"
	$(QUIET)$(CXX) -c $(CXXFLAGS) $(UTILS_INC) -o $@ -x c++ -include Arduino.h $<

$(BUILDDIR)/%.o: %.S
	@echo "[CC]\t$<"
	$(QUIET)mkdir -p "$(dir $@)"
	$(QUIET)$(CC) -c $(CASMFLAGS) -o $@ $<

%.o: %.c
	@echo "[CC]\t$<"
	$(QUIET)$(CC) -c $(CFLAGS) -o $@ $<

%.o: %.cpp
	@echo "[CXX]\t$<"
	$(QUIET)$(CXX) -c $(CXXFLAGS) -o $@ $<

%.o: %.ino
	@echo "[CXX]\t$<"
	$(QUIET)$(CXX) -c $(CXXFLAGS) -o $@ -x c++ -include Arduino.h $<

%.o: %.S
	@echo "[CC]\t$<"
	$(QUIET)$(CC) -c $(CASMFLAGS) -o $@ $<

%.eep: %.elf
	@echo "[EEP]\t$@"
	$(QUIET)$(OBJCOPY) -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 $< $@

%.hex: %.elf
	@echo "[HEX]\t$@"
	$(QUIET)$(OBJCOPY) -O ihex -R .eeprom $< $@

-include $(CORE_OBJECTS:.o=.d)
-include $(EXT_OBJECTS:.o=.d)
-include $(OBJECTS:.o=.d)
