TOP=../../..

include $(TOP)/configure/CONFIG

MYSQL_DIR=$(MYSQL)/install
CMAKE_CONFIG_FLAGS=-DCMAKE_BUILD_TYPE:STRING=Debug
CMAKE_BUILD_FLAGS=

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

ifdef T_A
install:
	cmake .. -G "Visual Studio 10 Win64" -DCMAKE_INSTALL_PREFIX:PATH=$(MYSQL_DIR) $(CMAKE_CONFIG_FLAGS)
	cmake --build . --target INSTALL --config RelWithDebInfo $(CMAKE_BUILD_FLAGS)
	$(CP) $(MYSQL_DIR)/bin/*.* $(TOP)/bin/$(EPICS_HOST_ARCH)
	$(CP) $(MYSQL_DIR)/lib/*.* $(TOP)/lib/$(EPICS_HOST_ARCH)
endif

#clean::

uninstall:


