TOP=../..

include $(TOP)/configure/CONFIG

PROD_IOC = xps

DBD += xps.dbd

xps_DBD += base.dbd
xps_DBD += asyn.dbd
xps_DBD += asSupport.dbd
xps_DBD += drvAsynSerialPort.dbd
xps_DBD += motorSupport.dbd
xps_DBD += devNewport.dbd
xps_DBD += xpsSup.dbd

xps_LIBS += Newport
xps_LIBS += motor
xps_LIBS += asyn
xps_LIBS += autosave

xps_SRCS += xps_registerRecordDeviceDriver.cpp

xps_SRCS_DEFAULT += xpsMain.cpp xpsASub.c
xps_SRCS_vxWorks += -nil-

xps_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

