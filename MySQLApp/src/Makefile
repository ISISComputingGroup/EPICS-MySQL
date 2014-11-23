TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#==================================================
# build a support library

LIBRARY_IOC += MySQL MySQLCPP

# xxxRecord.h will be created from xxxRecord.dbd
#DBDINC += xxxRecord
# install MySQL.dbd into <top>/dbd
#DBD += MySQL.dbd

# specify all source files to be compiled and added to the library
#MySQL_SRCS += xxx

MySQL_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

