TOP = ../..
include $(TOP)/configure/CONFIG

## setting MAKEFLAGS causes cmake issues
override MAKEFLAGS=

CMAKE ?= cmake

# extract visual studio major version number from path
# unfortunately cannot use %.% so using %.0 but may not match minor version number changes e.g. 10.1
ifneq ($(VisualStudioVersion),)
VS_VERS=$(filter %.0,$(subst \, ,$(VisualStudioVersion)))
else
VS_VERS=$(filter %.0,$(subst \, ,$(VSINSTALLDIR)))
endif

VS_MAJOR=$(word 1,$(subst ., ,$(VS_VERS)))

MYSQL_DIR=$(MYSQL)/install/$(EPICS_HOST_ARCH)
CMAKE_CONFIG_FLAGS=-DBOOST_ROOT:STRING=$(EPICS_ROOT)/libraries/master/boost -DWITH_SSL=$(OPENSSL)/install/$(EPICS_HOST_ARCH) -DWITH_JDBC=ON -DWITH_MYSQL=c:\instrument\apps\mysql
CMAKE_BUILD_FLAGS=
ifneq ($(findstring linux,$(EPICS_HOST_ARCH)),)
CMAKE_GENERATOR=Unix Makefiles
else
ifneq ($(findstring windows,$(EPICS_HOST_ARCH)),)
VS_ARCH=$(VS_MAJOR)
PLATFORM=x64
else
VS_ARCH=$(VS_MAJOR)
PLATFORM=Win32
endif
CMAKE_GENERATOR=Visual Studio $(VS_ARCH)
endif
ifneq ($(findstring debug,$(EPICS_HOST_ARCH)),)
CMAKE_CONFIG_FLAGS += -DCMAKE_BUILD_TYPE:STRING=Debug
CMAKE_CONFIG=Debug
else
CMAKE_CONFIG=RelWithDebInfo
endif

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

ifdef T_A
install:
	$(CMAKE) ../mysql-connector-c++ -G "$(CMAKE_GENERATOR)" -A "$(PLATFORM)" -DCMAKE_INSTALL_PREFIX:PATH="$(MYSQL_DIR)" $(CMAKE_CONFIG_FLAGS)
	$(CMAKE) --build . --target install --config $(CMAKE_CONFIG) $(CMAKE_BUILD_FLAGS)
	-$(MKDIR) $(TOP)/bin
	-$(MKDIR) $(TOP)/bin/$(EPICS_HOST_ARCH)
	-$(MKDIR) $(TOP)/lib
	-$(MKDIR) $(TOP)/lib/$(EPICS_HOST_ARCH)
	-$(MKDIR) $(TOP)/include
	-$(MKDIR) $(TOP)/include/mysql
	-$(MKDIR) $(TOP)/include/mysql/psi
	-$(MKDIR) $(TOP)/include/jdbc
	-$(MKDIR) $(TOP)/include/jdbc/cppconn
	-$(MKDIR) $(TOP)/include/mysqlx
	-$(MKDIR) $(TOP)/include/mysqlx/common
	-$(MKDIR) $(TOP)/include/mysqlx/devapi
	-$(MKDIR) $(TOP)/include/mysqlx/devapi/detail
	$(CP) -f $(MYSQL_DIR)/include/*.h* $(TOP)/include/
	$(CP) -f $(MYSQL_DIR)/include/mysql/*.h* $(TOP)/include/mysql/
	$(CP) -f $(MYSQL_DIR)/include/mysql/psi/*.h* $(TOP)/include/mysql/psi/
	$(CP) -f $(MYSQL_DIR)/include/jdbc/*.h* $(TOP)/include/jdbc/
	$(CP) -f $(MYSQL_DIR)/include/jdbc/cppconn/*.h* $(TOP)/include/jdbc/cppconn/
	$(CP) -f $(MYSQL_DIR)/include/mysqlx/*.h* $(TOP)/include/mysqlx/
	$(CP) -f $(MYSQL_DIR)/include/mysqlx/common/*.h* $(TOP)/include/mysqlx/common/
	$(CP) -f $(MYSQL_DIR)/include/mysqlx/devapi/*.h* $(TOP)/include/mysqlx/devapi/
	$(CP) -f $(MYSQL_DIR)/include/mysqlx/devapi/detail/*.h* $(TOP)/include/mysqlx/devapi/detail/
	$(CP) -f $(MYSQL_DIR)/bin/* $(TOP)/bin/$(EPICS_HOST_ARCH)/
# this directory (on windows) causes cp from lib to fail
	-$(RMDIR) $(MYSQL_DIR)/lib/debug
ifeq ($(findstring linux,$(EPICS_HOST_ARCH)),)
# dlls and pdbs need to be in bin not lib (and leaving copy in lib causes link errors)
	$(CP) -f $(MYSQL_DIR)/lib64/* $(TOP)/lib/$(EPICS_HOST_ARCH)/
	$(CP) -f $(MYSQL_DIR)/lib64/vs14/* $(TOP)/lib/$(EPICS_HOST_ARCH)/
	$(CP) -f $(MYSQL_DIR)/lib64/*.dll $(TOP)/bin/$(EPICS_HOST_ARCH)/
	$(CP) -f $(MYSQL_DIR)/lib64/*.pdb $(TOP)/bin/$(EPICS_HOST_ARCH)/
else
	if test -d $(MYSQL_DIR)/lib; then find $(MYSQL_DIR)/lib \( -type f -o -type l \) -exec $(CP) {} $(TOP)/lib/$(EPICS_HOST_ARCH)/ \; ; fi
	if test -d $(MYSQL_DIR)/lib64; then find $(MYSQL_DIR)/lib64 \( -type f -o -type l \) -exec $(CP) {} $(TOP)/lib/$(EPICS_HOST_ARCH)/ \; ; fi
endif
endif
