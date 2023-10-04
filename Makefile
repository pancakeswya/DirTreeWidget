OS           := $(shell uname -s)

NAME         := DirTreeWidget

BUILD_DIR    := build

ifeq ($(OS), Linux)
APP          := $(NAME)
RUN          := ./$(BUILD_DIR)/$(APP)
else
APP          := $(NAME).app
RUN          := open $(BUILD_DIR)/$(APP)
endif

BUILDER      := cmake

MAKEFLAGS    += --no-print-directory

all: install run

install:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(BUILDER) .. && $(MAKE)

uninstall:
	rm -rf $(BUILD_DIR)

run:
	$(RUN)

clean: uninstall

rebuild:
	$(MAKE) clean
	$(MAKE) install


