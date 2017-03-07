#!/bin/bash

# Copyright (c) 2018. EXCERA <http://www.excera.com.cn>.

SUDO_USER=${USER}
PROJECT_NAME=basic-platform
INSTALL_PREFIX=/opt/${PROJECT_NAME}
ROOT_PATCH=`pwd`

mkdir -p ${HOME}/.${PROJECT_NAME}/logs && \
sudo mkdir -p ${INSTALL_PREFIX}/bin && \
sudo mkdir -p ${INSTALL_PREFIX}/configs && \
sudo cp -Ra ${ROOT_PATCH}/uninstall.sh ${INSTALL_PREFIX}/uninstall.sh && \
sudo cp -Ra ${ROOT_PATCH}/bin/* ${INSTALL_PREFIX}/bin && \
sudo cp -Ra ${ROOT_PATCH}/configs/* ${INSTALL_PREFIX}/configs && \
sudo ln -sf ${INSTALL_PREFIX}/bin/${PROJECT_NAME} /usr/bin/${PROJECT_NAME}
