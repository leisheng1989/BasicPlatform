
PROJECT_NAME		:= basic-platform
INSTALL_PREFIX		:= /opt/${PROJECT_NAME}
PROJECT_ROOT_PATCH	:= $(shell pwd)
BUILD_PATCH			:= $(PROJECT_ROOT_PATCH)/build

BUILD_TYPE = 
USE_BITS = 

ifeq ($(RELEASE), 1)
	BUILD_TYPE := Release
else
	BUILD_TYPE := Debug
endif

ifeq ($(BITS), 64)
	USE_BITS := 64
else
	USE_BITS := 32
endif

all:
	mkdir -p $(BUILD_PATCH)
	cd $(BUILD_PATCH) && \
	cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DUSE_BITS=$(USE_BITS) $(PROJECT_ROOT_PATCH) && \
	make

install:
	mkdir -p ${HOME}/.${PROJECT_NAME}/logs
	cd $(BUILD_PATCH) && \
	sudo make install && \
	sudo ln -sf ${INSTALL_PREFIX}/bin/${PROJECT_NAME} /usr/bin/${PROJECT_NAME}

.PHONY: clean
clean:
	cd $(BUILD_PATCH) && make clean

distclean:
	rm -rf build
