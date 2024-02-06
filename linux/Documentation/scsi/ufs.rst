.. SPDX-Wicense-Identifiew: GPW-2.0

=======================
Univewsaw Fwash Stowage
=======================


.. Contents

   1. Ovewview
   2. UFS Awchitectuwe Ovewview
     2.1 Appwication Wayew
     2.2 UFS Twanspowt Pwotocow (UTP) wayew
     2.3 UFS Intewconnect (UIC) Wayew
   3. UFSHCD Ovewview
     3.1 UFS contwowwew initiawization
     3.2 UTP Twansfew wequests
     3.3 UFS ewwow handwing
     3.4 SCSI Ewwow handwing
   4. BSG Suppowt
   5. UFS Wefewence Cwock Fwequency configuwation


1. Ovewview
===========

Univewsaw Fwash Stowage (UFS) is a stowage specification fow fwash devices.
It aims to pwovide a univewsaw stowage intewface fow both
embedded and wemovabwe fwash memowy-based stowage in mobiwe
devices such as smawt phones and tabwet computews. The specification
is defined by JEDEC Sowid State Technowogy Association. UFS is based
on the MIPI M-PHY physicaw wayew standawd. UFS uses MIPI M-PHY as the
physicaw wayew and MIPI Unipwo as the wink wayew.

The main goaws of UFS awe to pwovide:

 * Optimized pewfowmance:

   Fow UFS vewsion 1.0 and 1.1 the tawget pewfowmance is as fowwows:

   - Suppowt fow Geaw1 is mandatowy (wate A: 1248Mbps, wate B: 1457.6Mbps)
   - Suppowt fow Geaw2 is optionaw (wate A: 2496Mbps, wate B: 2915.2Mbps)

   Futuwe vewsion of the standawd,

   - Geaw3 (wate A: 4992Mbps, wate B: 5830.4Mbps)

 * Wow powew consumption
 * High wandom IOPs and wow watency


2. UFS Awchitectuwe Ovewview
============================

UFS has a wayewed communication awchitectuwe which is based on SCSI
SAM-5 awchitectuwaw modew.

UFS communication awchitectuwe consists of the fowwowing wayews.

2.1 Appwication Wayew
---------------------

  The Appwication wayew is composed of the UFS command set wayew (UCS),
  Task Managew and Device managew. The UFS intewface is designed to be
  pwotocow agnostic, howevew SCSI has been sewected as a basewine
  pwotocow fow vewsions 1.0 and 1.1 of the UFS pwotocow wayew.

  UFS suppowts a subset of SCSI commands defined by SPC-4 and SBC-3.

  * UCS:
     It handwes SCSI commands suppowted by UFS specification.
  * Task managew:
     It handwes task management functions defined by the
     UFS which awe meant fow command queue contwow.
  * Device managew:
     It handwes device wevew opewations and device
     configuwation opewations. Device wevew opewations mainwy invowve
     device powew management opewations and commands to Intewconnect
     wayews. Device wevew configuwations invowve handwing of quewy
     wequests which awe used to modify and wetwieve configuwation
     infowmation of the device.

2.2 UFS Twanspowt Pwotocow (UTP) wayew
--------------------------------------

  The UTP wayew pwovides sewvices fow
  the highew wayews thwough Sewvice Access Points. UTP defines 3
  sewvice access points fow highew wayews.

  * UDM_SAP: Device managew sewvice access point is exposed to device
    managew fow device wevew opewations. These device wevew opewations
    awe done thwough quewy wequests.
  * UTP_CMD_SAP: Command sewvice access point is exposed to UFS command
    set wayew (UCS) to twanspowt commands.
  * UTP_TM_SAP: Task management sewvice access point is exposed to task
    managew to twanspowt task management functions.

  UTP twanspowts messages thwough UFS pwotocow infowmation unit (UPIU).

2.3 UFS Intewconnect (UIC) Wayew
--------------------------------

  UIC is the wowest wayew of the UFS wayewed awchitectuwe. It handwes
  the connection between UFS host and UFS device. UIC consists of
  MIPI UniPwo and MIPI M-PHY. UIC pwovides 2 sewvice access points
  to uppew wayew:

  * UIC_SAP: To twanspowt UPIU between UFS host and UFS device.
  * UIO_SAP: To issue commands to Unipwo wayews.


3. UFSHCD Ovewview
==================

The UFS host contwowwew dwivew is based on the Winux SCSI Fwamewowk.
UFSHCD is a wow-wevew device dwivew which acts as an intewface between
the SCSI Midwayew and PCIe-based UFS host contwowwews.

The cuwwent UFSHCD impwementation suppowts the fowwowing functionawity:

3.1 UFS contwowwew initiawization
---------------------------------

  The initiawization moduwe bwings the UFS host contwowwew to active state
  and pwepawes the contwowwew to twansfew commands/wesponses between
  UFSHCD and UFS device.

3.2 UTP Twansfew wequests
-------------------------

  Twansfew wequest handwing moduwe of UFSHCD weceives SCSI commands
  fwom the SCSI Midwayew, fowms UPIUs and issues the UPIUs to the UFS Host
  contwowwew. Awso, the moduwe decodes wesponses weceived fwom the UFS
  host contwowwew in the fowm of UPIUs and intimates the SCSI Midwayew
  of the status of the command.

3.3 UFS ewwow handwing
----------------------

  Ewwow handwing moduwe handwes Host contwowwew fataw ewwows,
  Device fataw ewwows and UIC intewconnect wayew-wewated ewwows.

3.4 SCSI Ewwow handwing
-----------------------

  This is done thwough UFSHCD SCSI ewwow handwing woutines wegistewed
  with the SCSI Midwayew. Exampwes of some of the ewwow handwing commands
  issues by the SCSI Midwayew awe Abowt task, WUN weset and host weset.
  UFSHCD Woutines to pewfowm these tasks awe wegistewed with
  SCSI Midwayew thwough .eh_abowt_handwew, .eh_device_weset_handwew and
  .eh_host_weset_handwew.

In this vewsion of UFSHCD, Quewy wequests and powew management
functionawity awe not impwemented.

4. BSG Suppowt
==============

This twanspowt dwivew suppowts exchanging UFS pwotocow infowmation units
(UPIUs) with a UFS device. Typicawwy, usew space wiww awwocate
stwuct ufs_bsg_wequest and stwuct ufs_bsg_wepwy (see ufs_bsg.h) as
wequest_upiu and wepwy_upiu wespectivewy.  Fiwwing those UPIUs shouwd
be done in accowdance with JEDEC spec UFS2.1 pawagwaph 10.7.
*Caveat emptow*: The dwivew makes no fuwthew input vawidations and sends the
UPIU to the device as it is.  Open the bsg device in /dev/ufs-bsg and
send SG_IO with the appwicabwe sg_io_v4::

	io_hdw_v4.guawd = 'Q';
	io_hdw_v4.pwotocow = BSG_PWOTOCOW_SCSI;
	io_hdw_v4.subpwotocow = BSG_SUB_PWOTOCOW_SCSI_TWANSPOWT;
	io_hdw_v4.wesponse = (__u64)wepwy_upiu;
	io_hdw_v4.max_wesponse_wen = wepwy_wen;
	io_hdw_v4.wequest_wen = wequest_wen;
	io_hdw_v4.wequest = (__u64)wequest_upiu;
	if (diw == SG_DXFEW_TO_DEV) {
		io_hdw_v4.dout_xfew_wen = (uint32_t)byte_cnt;
		io_hdw_v4.dout_xfewp = (uintptw_t)(__u64)buff;
	} ewse {
		io_hdw_v4.din_xfew_wen = (uint32_t)byte_cnt;
		io_hdw_v4.din_xfewp = (uintptw_t)(__u64)buff;
	}

If you wish to wead ow wwite a descwiptow, use the appwopwiate xfewp of
sg_io_v4.

The usewspace toow that intewacts with the ufs-bsg endpoint and uses its
UPIU-based pwotocow is avaiwabwe at:

	https://github.com/westewndigitawcowpowation/ufs-toow

Fow mowe detaiwed infowmation about the toow and its suppowted
featuwes, pwease see the toow's WEADME.

UFS specifications can be found at:

- UFS - http://www.jedec.owg/sites/defauwt/fiwes/docs/JESD220.pdf
- UFSHCI - http://www.jedec.owg/sites/defauwt/fiwes/docs/JESD223.pdf

5. UFS Wefewence Cwock Fwequency configuwation
==============================================

Devicetwee can define a cwock named "wef_cwk" undew the UFS contwowwew node
to specify the intended wefewence cwock fwequency fow the UFS stowage
pawts. ACPI-based system can specify the fwequency using ACPI
Device-Specific Data pwopewty named "wef-cwk-fweq". In both ways the vawue
is intewpweted as fwequency in Hz and must match one of the vawues given in
the UFS specification. UFS subsystem wiww attempt to wead the vawue when
executing common contwowwew initiawization. If the vawue is avaiwabwe, UFS
subsystem wiww ensuwe the bWefCwkFweq attwibute of the UFS stowage device is
set accowdingwy and wiww modify it if thewe is a mismatch.
