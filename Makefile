
PROJECT_NAME		:= basic-platform
INSTALL_PREFIX		:= /opt/${PROJECT_NAME}
PROJECT_ROOT_PATCH	:= $(shell pwd)
BUILD_PATCH			:= $(PROJECT_ROOT_PATCH)/build

SUDO_USER	:= ${USER}
BUILD_TYPE = 
USE_BITS = 

ifeq ($(RELEASE), 1)
	BUILD_TYPE := Release
else
	BUILD_TYPE := Debug
endif

ifeq ($(BITS), 64)
	USE_BITS := x86_64
else
	USE_BITS := i386
endif

all:
	mkdir -p $(BUILD_PATCH)
	cd $(BUILD_PATCH) && \
	cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DUSE_BITS=$(USE_BITS) $(PROJECT_ROOT_PATCH) && \
	make

install:
	mkdir -p ${HOME}/.${PROJECT_NAME}/logs
	cd $(BUILD_PATCH) && \
	make install && \
	sudo mkdir -p ${INSTALL_PREFIX}/bin && \
	sudo mkdir -p ${INSTALL_PREFIX}/configs && \
	sudo cp -Ra $(PROJECT_ROOT_PATCH)/target/bin/* ${INSTALL_PREFIX}/bin && \
	sudo cp -Ra $(PROJECT_ROOT_PATCH)/target/configs/* ${INSTALL_PREFIX}/configs && \
	sudo ln -sf ${INSTALL_PREFIX}/bin/${PROJECT_NAME} /usr/bin/${PROJECT_NAME}

packe:
	cd $(BUILD_PATCH) && \
	cpack -C CPackConfig.cmake && \
	mkdir -p $(PROJECT_ROOT_PATCH)/release && \
	cp -Ra $(BUILD_PATCH)/*.tar* $(PROJECT_ROOT_PATCH)/release

clean:
	cd $(BUILD_PATCH) && make clean

distclean:
	rm -rf build

.PHONY: clean install distclean
