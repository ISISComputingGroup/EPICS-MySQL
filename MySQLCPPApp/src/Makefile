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
CMAKE_CONFIG_FLAGS=-DBOOST_ROOT:STRING=$(EPICS_ROOT)/libraries/master/boost
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
	$(CMAKE) ../mysql-connector-c++ -G "$(CMAKE_GENERATOR)" -A "$(PLATFORM)" -DCMAKE_INSTALL_PREFIX:PATH="$(MYSQL_DIR)" -DMYSQL_DIR:PATH="$(MYSQL_DIR)" $(CMAKE_CONFIG_FLAGS)
	$(CMAKE) --build . --target install --config $(CMAKE_CONFIG) $(CMAKE_BUILD_FLAGS)
	-$(MKDIR) $(TOP)/bin
	-$(MKDIR) $(TOP)/bin/$(EPICS_HOST_ARCH)
	-$(MKDIR) $(TOP)/lib
	-$(MKDIR) $(TOP)/lib/$(EPICS_HOST_ARCH)
	-$(MKDIR) $(TOP)/include
	-$(MKDIR) $(TOP)/include/mysql
	-$(MKDIR) $(TOP)/include/mysql/psi
	-$(MKDIR) $(TOP)/include/cppconn
	$(CP) -f $(MYSQL_DIR)/include/*.h* $(TOP)/include/
	$(CP) -f $(MYSQL_DIR)/include/mysql/*.h* $(TOP)/include/mysql/
	$(CP) -f $(MYSQL_DIR)/include/mysql/psi/*.h* $(TOP)/include/mysql/psi/
	$(CP) -f $(MYSQL_DIR)/include/cppconn/*.h* $(TOP)/include/cppconn/
	$(CP) -f $(MYSQL_DIR)/bin/* $(TOP)/bin/$(EPICS_HOST_ARCH)/
# this directory (on windows) causes cp from lib to fail
	-$(RMDIR) $(MYSQL_DIR)/lib/debug
ifeq ($(findstring linux,$(EPICS_HOST_ARCH)),)
# dlls and pdbs need to be in bin not lib (and leaving copy in lib causes link errors)
	$(CP) -f $(MYSQL_DIR)/lib/* $(TOP)/lib/$(EPICS_HOST_ARCH)/
	$(CP) -f $(MYSQL_DIR)/lib/*.dll $(TOP)/bin/$(EPICS_HOST_ARCH)/
	$(CP) -f $(MYSQL_DIR)/lib/*.pdb $(TOP)/bin/$(EPICS_HOST_ARCH)/
	$(RM) -f $(TOP)/lib/$(EPICS_HOST_ARCH)/*.dll
	$(RM) -f $(TOP)/lib/$(EPICS_HOST_ARCH)/*.pdb
else
	if test -d $(MYSQL_DIR)/lib; then find $(MYSQL_DIR)/lib \( -type f -o -type l \) -exec $(CP) {} $(TOP)/lib/$(EPICS_HOST_ARCH)/ \; ; fi
	if test -d $(MYSQL_DIR)/lib64; then find $(MYSQL_DIR)/lib64 \( -type f -o -type l \) -exec $(CP) {} $(TOP)/lib/$(EPICS_HOST_ARCH)/ \; ; fi
endif
endif

#clean::
#	$(MAKE) -C mysql-connector-c -f Makefile.epics clean T_A=$(T_A) CMAKE_CONFIG=$(CMAKE_CONFIG) PLATFORM=$(PLATFORM) MYSQL_DIR="$(MYSQL_DIR)"
#	$(MAKE) -C mysql-connector-c++ -f Makefile.epics clean T_A=$(T_A) CMAKE_CONFIG=$(CMAKE_CONFIG) PLATFORM=$(PLATFORM) MYSQL_DIR="$(MYSQL_DIR)"
#clean::
#ifneq ($(findstring linux,$(EPICS_HOST_ARCH)),)
#	$(MAKE) -f Makefile clean
#else
#	-msbuild MYSQLCPPCONN.sln /t:clean /nologo /verbosity:quiet /p:Configuration=$(CMAKE_CONFIG) /p:Platform=$(PLATFORM)
#endif
#	-$(RM) CMakeCache.txt cmake_install.cmake
#	-$(RM) $(call rfind, ., *.sln *.vcxproj *.vcxproj.filters cmake_install.cmake)
#	-$(RMDIR) CMakeFiles


#uninstall:
#	$(RMDIR) $(MYSQL_DIR)
