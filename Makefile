AR   := $(CROSS_COMPILE)ar
CC   := $(CROSS_COMPILE)gcc
CXX  := $(CROSS_COMPILE)g++
RM   := rm -rf

INCLUDE_DIRS := inc
LIBRARY_FILE := libnrf24l01.a
SOURCE_FILES := $(wildcard src/*.cpp)
OBJECT_FILES := $(patsubst %.cpp,%.o,$(SOURCE_FILES))
DEPENDENCIES := $(patsubst %.cpp,%.d,$(SOURCE_FILES))

CFLAGS += -O3 -flto

CXXFLAGS += -O3 -flto

CPPFLAGS += $(addprefix -I,$(INCLUDE_DIRS)) -MD

# -----

all: $(LIBRARY_FILE)

clean:
	$(RM) $(LIBRARY_FILE) $(OBJECT_FILES) $(DEPENDENCIES)

$(LIBRARY_FILE): $(OBJECT_FILES)
	$(AR) r $@ $^

# -----

-include $(DEPENDENCIES)
