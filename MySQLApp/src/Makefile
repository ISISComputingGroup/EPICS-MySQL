TOP = ../..
include $(TOP)/configure/CONFIG

DIRS := mysql-connector-c-6_1_5
ifeq ($(findstring linux,$(EPICS_HOST_ARCH)),)
DIRS += mysql-connector-c++-1_1_4
endif

include $(TOP)/configure/RULES_DIRS
