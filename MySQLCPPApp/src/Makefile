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

MYSQL_INSTALL_DIR = $(EPICS_ROOT)/ICP_Binaries/mysql/mysql-current

MYSQLCONN_DIR=$(MYSQL)/install/$(EPICS_HOST_ARCH)

CMAKE_CONFIG_FLAGS=-DWITH_SSL=$(OPENSSL)/install/$(EPICS_HOST_ARCH) -DWITH_JDBC=ON -DWITH_MYSQL=$(MYSQL_INSTALL_DIR) 

# this would use zlib bundled in ibex, we may nede this for static linking as mysql bindles a zlib and
# when not buildign a DLL we may get a conflict 
#-DZLIB_LIBRARY=zlib.lib -DZLIB_INCLUDE_DIR=$(ZLIB)/include -DZLIB_LIB_DIR=$(ZLIB)/lib/$(EPICS_HOST_ARCH)

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
INSTSUBDIR=debug
else
CMAKE_CONFIG=RelWithDebInfo
INSTSUBDIR=
endif
ifneq ($(findstring static,$(EPICS_HOST_ARCH)),)
CMAKE_CONFIG_FLAGS += -DBUILD_STATIC:BOOL=ON -DSTATIC_MSVCRT:BOOL=ON -DMYSQLCLIENT_STATIC_LINKING:BOOL=ON
endif

BIN_INSTALLS_WIN32 += $(MYSQL_INSTALL_DIR)/lib/libmysql.dll
BIN_INSTALLS_WIN32 += $(OPENSSL)/bin/$(EPICS_HOST_ARCH)/*.dll

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

ifdef T_A
install:
	$(CMAKE) ../mysql-connector-c++ -G "$(CMAKE_GENERATOR)" -A "$(PLATFORM)" -DCMAKE_INSTALL_PREFIX:PATH="$(MYSQLCONN_DIR)" $(CMAKE_CONFIG_FLAGS)
	$(CMAKE) --build . --target install --config $(CMAKE_CONFIG) $(CMAKE_BUILD_FLAGS)
	-$(MKDIR) $(TOP)/bin
	-$(MKDIR) $(TOP)/bin/$(EPICS_HOST_ARCH)
	-$(MKDIR) $(TOP)/lib
	-$(MKDIR) $(TOP)/lib/$(EPICS_HOST_ARCH)
	-$(MKDIR) $(TOP)/include
	-$(MKDIR) $(TOP)/include/cppconn
	$(CP) -f $(MYSQLCONN_DIR)/include/jdbc/*.h $(TOP)/include/
	$(CP) -f $(MYSQLCONN_DIR)/include/jdbc/cppconn/*.h $(TOP)/include/cppconn/
	$(CP) -f $(MYSQLCONN_DIR)/bin/* $(TOP)/bin/$(EPICS_HOST_ARCH)/
ifeq ($(findstring linux,$(EPICS_HOST_ARCH)),)
# dlls and pdbs need to be in bin not lib (and leaving copy in lib causes link errors)
	$(CP) -f $(MYSQLCONN_DIR)/lib64/$(INSTSUBDIR)/* $(TOP)/lib/$(EPICS_HOST_ARCH)/
	$(CP) -f $(MYSQLCONN_DIR)/lib64/vs14/$(INSTSUBDIR)/* $(TOP)/lib/$(EPICS_HOST_ARCH)/
	$(CP) -f $(MYSQLCONN_DIR)/lib64/$(INSTSUBDIR)/*.dll $(TOP)/bin/$(EPICS_HOST_ARCH)/
	$(CP) -f $(MYSQLCONN_DIR)/lib64/$(INSTSUBDIR)/*.pdb $(TOP)/bin/$(EPICS_HOST_ARCH)/
else
	if test -d $(MYSQLCONN_DIR)/lib; then find $(MYSQLCONN_DIR)/lib \( -type f -o -type l \) -exec $(CP) {} $(TOP)/lib/$(EPICS_HOST_ARCH)/ \; ; fi
	if test -d $(MYSQLCONN_DIR)/lib64; then find $(MYSQLCONN_DIR)/lib64 \( -type f -o -type l \) -exec $(CP) {} $(TOP)/lib/$(EPICS_HOST_ARCH)/ \; ; fi
endif
endif
