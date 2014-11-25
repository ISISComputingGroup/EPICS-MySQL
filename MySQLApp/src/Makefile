TOP = ../..
include $(TOP)/configure/CONFIG

# extract visual studio major version number from path
# unfortunately cannot use %.% so using %.0 but may not match minor version number changes e.g. 10.1
VS_VERS=$(filter %.0,$(subst \, ,$(VSINSTALLDIR)))
VS_MAJOR=$(word 1,$(subst ., ,$(VS_VERS)))

MYSQL_DIR=$(MYSQL)/install
CMAKE_CONFIG_FLAGS=-DBOOST_ROOT:STRING=$(EPICS_ROOT)/libraries/boost
CMAKE_BUILD_FLAGS=
ifneq ($(findstring linux,$(EPICS_HOST_ARCH)),)
CMAKE_GENERATOR=Unix Makefiles
else
ifneq ($(findstring windows,$(EPICS_HOST_ARCH)),)
VS_ARCH=Win64
else
VS_ARCH=
endif
CMAKE_GENERATOR=Visual Studio $(VS_MAJOR) $(VS_ARCH)
endif
ifneq ($(findstring debug,$(EPICS_HOST_ARCH)),)
CMAKE_CONFIG_FLAGS += -DCMAKE_BUILD_TYPE:STRING=Debug
CMAKE_CONFIG = Debug
else
CMAKE_CONFIG = Release # RelWithDebInfo
endif

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

ifdef T_A
install:
	$(MAKE) -C ../mysql-connector-c-6_1_5 -f Makefile.epics install T_A=$(T_A) CMAKE_CONFIG=$(CMAKE_CONFIG) CMAKE_CONFIG_FLAGS="$(CMAKE_CONFIG_FLAGS)" CMAKE_GENERATOR="$(CMAKE_GENERATOR)" CMAKE_BUILD_FLAGS="$(CMAKE_BUILD_FLAGS)" MYSQL_DIR="$(MYSQL_DIR)"
	-$(MKDIR) $(TOP)/bin
	-$(MKDIR) $(TOP)/bin/$(EPICS_HOST_ARCH)
	-$(MKDIR) $(TOP)/lib
	-$(MKDIR) $(TOP)/lib/$(EPICS_HOST_ARCH)
	-$(MKDIR) $(TOP)/include
	-$(MKDIR) $(TOP)/include/mysql
	-$(MKDIR) $(TOP)/include/mysql/psi
	-$(MKDIR) $(TOP)/include/cppconn
	$(CP) -f $(MYSQL_DIR)/bin/* $(TOP)/bin/$(EPICS_HOST_ARCH)/
	$(CP) -f $(MYSQL_DIR)/lib/* $(TOP)/lib/$(EPICS_HOST_ARCH)/
	$(CP) -f $(MYSQL_DIR)/include/*.h* $(TOP)/include/
	$(CP) -f $(MYSQL_DIR)/include/mysql/*.h* $(TOP)/include/mysql/
	$(CP) -f $(MYSQL_DIR)/include/mysql/psi/*.h* $(TOP)/include/mysql/psi/
	$(MAKE) -C ../mysql-connector-c++-1_1_4 -f Makefile.epics install T_A=$(T_A) CMAKE_CONFIG=$(CMAKE_CONFIG) CMAKE_CONFIG_FLAGS="$(CMAKE_CONFIG_FLAGS)" CMAKE_GENERATOR="$(CMAKE_GENERATOR)" CMAKE_BUILD_FLAGS="$(CMAKE_BUILD_FLAGS)" MYSQL_DIR="$(MYSQL_DIR)"
	$(CP) -f $(MYSQL_DIR)/bin/* $(TOP)/bin/$(EPICS_HOST_ARCH)/
	$(CP) -f $(MYSQL_DIR)/lib/* $(TOP)/lib/$(EPICS_HOST_ARCH)/
	$(CP) -f $(MYSQL_DIR)/include/*.h* $(TOP)/include/
	$(CP) -f $(MYSQL_DIR)/include/mysql/*.h* $(TOP)/include/mysql/
	$(CP) -f $(MYSQL_DIR)/include/mysql/psi/*.h* $(TOP)/include/mysql/psi/
	$(CP) -f $(MYSQL_DIR)/include/cppconn/*.h* $(TOP)/include/cppconn/
endif

clean::
	$(MAKE) -C mysql-connector-c-6_1_5 -f Makefile.epics clean CMAKE_CONFIG=$(CMAKE_CONFIG)
	$(MAKE) -C mysql-connector-c++-1_1_4 -f Makefile.epics clean CMAKE_CONFIG=$(CMAKE_CONFIG)

uninstall:


