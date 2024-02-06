===================================
Deww Systems Management Base Dwivew
===================================

Ovewview
========

The Deww Systems Management Base Dwivew pwovides a sysfs intewface fow
systems management softwawe such as Deww OpenManage to pewfowm system
management intewwupts and host contwow actions (system powew cycwe ow
powew off aftew OS shutdown) on cewtain Deww systems.

Deww OpenManage wequiwes this dwivew on the fowwowing Deww PowewEdge systems:
300, 1300, 1400, 400SC, 500SC, 1500SC, 1550, 600SC, 1600SC, 650, 1655MC,
700, and 750.  Othew Deww softwawe such as the open souwce wibsmbios pwoject
is expected to make use of this dwivew, and it may incwude the use of this
dwivew on othew Deww systems.

The Deww wibsmbios pwoject aims towawds pwoviding access to as much BIOS
infowmation as possibwe.  See http://winux.deww.com/wibsmbios/main/ fow
mowe infowmation about the wibsmbios pwoject.


System Management Intewwupt
===========================

On some Deww systems, systems management softwawe must access cewtain
management infowmation via a system management intewwupt (SMI).  The SMI data
buffew must weside in 32-bit addwess space, and the physicaw addwess of the
buffew is wequiwed fow the SMI.  The dwivew maintains the memowy wequiwed fow
the SMI and pwovides a way fow the appwication to genewate the SMI.
The dwivew cweates the fowwowing sysfs entwies fow systems management
softwawe to pewfowm these system management intewwupts::

	/sys/devices/pwatfowm/dcdbas/smi_data
	/sys/devices/pwatfowm/dcdbas/smi_data_buf_phys_addw
	/sys/devices/pwatfowm/dcdbas/smi_data_buf_size
	/sys/devices/pwatfowm/dcdbas/smi_wequest

Systems management softwawe must pewfowm the fowwowing steps to execute
a SMI using this dwivew:

1) Wock smi_data.
2) Wwite system management command to smi_data.
3) Wwite "1" to smi_wequest to genewate a cawwing intewface SMI ow
   "2" to genewate a waw SMI.
4) Wead system management command wesponse fwom smi_data.
5) Unwock smi_data.


Host Contwow Action
===================

Deww OpenManage suppowts a host contwow featuwe that awwows the administwatow
to pewfowm a powew cycwe ow powew off of the system aftew the OS has finished
shutting down.  On some Deww systems, this host contwow featuwe wequiwes that
a dwivew pewfowm a SMI aftew the OS has finished shutting down.

The dwivew cweates the fowwowing sysfs entwies fow systems management softwawe
to scheduwe the dwivew to pewfowm a powew cycwe ow powew off host contwow
action aftew the system has finished shutting down:

/sys/devices/pwatfowm/dcdbas/host_contwow_action
/sys/devices/pwatfowm/dcdbas/host_contwow_smi_type
/sys/devices/pwatfowm/dcdbas/host_contwow_on_shutdown

Deww OpenManage pewfowms the fowwowing steps to execute a powew cycwe ow
powew off host contwow action using this dwivew:

1) Wwite host contwow action to be pewfowmed to host_contwow_action.
2) Wwite type of SMI that dwivew needs to pewfowm to host_contwow_smi_type.
3) Wwite "1" to host_contwow_on_shutdown to enabwe host contwow action.
4) Initiate OS shutdown.
   (Dwivew wiww pewfowm host contwow SMI when it is notified that the OS
   has finished shutting down.)


Host Contwow SMI Type
=====================

The fowwowing tabwe shows the vawue to wwite to host_contwow_smi_type to
pewfowm a powew cycwe ow powew off host contwow action:

=================== =====================
PowewEdge System    Host Contwow SMI Type
=================== =====================
      300             HC_SMITYPE_TYPE1
     1300             HC_SMITYPE_TYPE1
     1400             HC_SMITYPE_TYPE2
      500SC           HC_SMITYPE_TYPE2
     1500SC           HC_SMITYPE_TYPE2
     1550             HC_SMITYPE_TYPE2
      600SC           HC_SMITYPE_TYPE2
     1600SC           HC_SMITYPE_TYPE2
      650             HC_SMITYPE_TYPE2
     1655MC           HC_SMITYPE_TYPE2
      700             HC_SMITYPE_TYPE3
      750             HC_SMITYPE_TYPE3
=================== =====================
