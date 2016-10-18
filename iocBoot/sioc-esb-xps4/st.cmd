#!../../bin/linux-x86_64/xps

< envPaths

cd ${TOP}

dbLoadDatabase("dbd/xps.dbd")
xps_registerRecordDeviceDriver(pdbbase)

epicsEnvSet("N","4")
epicsEnvSet("P","ESB:XPS$(N)")
epicsEnvSet("LOC","NLCTA Tunnel Roof #2")
epicsEnvSet("IP","sioc-esb-xps$(N)")

save_restoreSet_status_prefix( "")
save_restoreSet_IncompleteSetsOk( 1)
save_restoreSet_DatedBackupFiles( 1)
set_savefile_path( "/nfs/slac/g/testfac/esb/$(IOC)","autosave")
set_pass0_restoreFile( "xps.sav")
set_pass1_restoreFile( "xps.sav")

dbLoadRecords( "db/xps$(N).db","P=$(P),PORT=XPS$(N),LOC=$(LOC)")

# asyn port, IP address, IP port, number of axes,
# active poll period (ms), idle poll period (ms),
# enable set position, set position settling time (ms)
XPSCreateController("XPS$(N)", "$(IP)", 5001, 3, 20, 500, 0, 200)

# XPS asyn port, axis, groupName.positionerName, stepSize
XPSCreateAxis("XPS$(N)",0,"Group1.Pos",100)
XPSCreateAxis("XPS$(N)",1,"Group2.Pos",100)
XPSCreateAxis("XPS$(N)",2,"Group3.Pos",100)
#XPSCreateAxis("XPS$(N)",3,"Group4.Pos",20000)

#asynSetTraceIOMask("XPS$(N)", 0, 2)
#asynSetTraceMask("XPS$(N)", 0, 255)

cd ${AUTOSAVE}
dbLoadRecords( "db/save_restoreStatus.db","P=$(P):")

cd ${TOP}/iocBoot/${IOC}
iocInit

create_monitor_set( "xps.req",30)
