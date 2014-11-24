TOP=../../..

include $(TOP)/configure/CONFIG

MYSQL_DIR=$(MYSQL)/install
CMAKE_CONFIG_FLAGS=-DCMAKE_BUILD_TYPE:STRING=Debug -DBOOST_ROOT:STRING=$(EPICS_ROOT)/libraries/boost
CMAKE_BUILD_FLAGS=

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

ifdef T_A
install:
	cmake .. -G "Visual Studio 10 Win64" -DCMAKE_INSTALL_PREFIX:PATH=$(MYSQL_DIR) $(CMAKE_CONFIG_FLAGS)
	cmake --build . --target INSTALL --config RelWithDebInfo $(CMAKE_BUILD_FLAGS)
	-$(MKDIR) $(TOP)/bin
	-$(MKDIR) $(TOP)/bin/$(EPICS_HOST_ARCH)
	-$(MKDIR) $(TOP)/lib
	-$(MKDIR) $(TOP)/lib/$(EPICS_HOST_ARCH)
	-$(MKDIR) $(TOP)/include
	-$(MKDIR) $(TOP)/include/mysql
	-$(MKDIR) $(TOP)/include/mysql/psi
	$(CP) -f $(MYSQL_DIR)/bin/* $(TOP)/bin/$(EPICS_HOST_ARCH)/
	$(CP) -f $(MYSQL_DIR)/lib/* $(TOP)/lib/$(EPICS_HOST_ARCH)/
	$(CP) -f $(MYSQL_DIR)/include/* $(TOP)/include/
	$(CP) -f $(MYSQL_DIR)/include/mysql/* $(TOP)/include/mysql/
	$(CP) -f $(MYSQL_DIR)/include/mysql/psi/* $(TOP)/include/mysql/psi/
endif

#clean::

uninstall:
