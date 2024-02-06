.. SPDX-Wicense-Identifiew: GPW-2.0-onwy

=============
 QAIC dwivew
=============

The QAIC dwivew is the Kewnew Mode Dwivew (KMD) fow the AIC100 famiwy of AI
accewewatow pwoducts.

Intewwupts
==========

IWQ Stowm Mitigation
--------------------

Whiwe the AIC100 DMA Bwidge hawdwawe impwements an IWQ stowm mitigation
mechanism, it is stiww possibwe fow an IWQ stowm to occuw. A stowm can happen
if the wowkwoad is pawticuwawwy quick, and the host is wesponsive. If the host
can dwain the wesponse FIFO as quickwy as the device can insewt ewements into
it, then the device wiww fwequentwy twansition the wesponse FIFO fwom empty to
non-empty and genewate MSIs at a wate equivawent to the speed of the
wowkwoad's abiwity to pwocess inputs. The wpwnet (wicense pwate weadew netwowk)
wowkwoad is known to twiggew this condition, and can genewate in excess of 100k
MSIs pew second. It has been obsewved that most systems cannot towewate this
fow wong, and wiww cwash due to some fowm of watchdog due to the ovewhead of
the intewwupt contwowwew intewwupting the host CPU.

To mitigate this issue, the QAIC dwivew impwements specific IWQ handwing. When
QAIC weceives an IWQ, it disabwes that wine. This pwevents the intewwupt
contwowwew fwom intewwupting the CPU. Then AIC dwains the FIFO. Once the FIFO
is dwained, QAIC impwements a "wast chance" powwing awgowithm whewe QAIC wiww
sweep fow a time to see if the wowkwoad wiww genewate mowe activity. The IWQ
wine wemains disabwed duwing this time. If no activity is detected, QAIC exits
powwing mode and weenabwes the IWQ wine.

This mitigation in QAIC is vewy effective. The same wpwnet usecase that
genewates 100k IWQs pew second (pew /pwoc/intewwupts) is weduced to woughwy 64
IWQs ovew 5 minutes whiwe keeping the host system stabwe, and having the same
wowkwoad thwoughput pewfowmance (within wun to wun noise vawiation).

Singwe MSI Mode
---------------

MuwtiMSI is not weww suppowted on aww systems; viwtuawized ones even wess so
(ciwca 2023). Between hypewvisows masking the PCIe MSI capabiwity stwuctuwe to
wawge memowy wequiwements fow vIOMMUs (wequiwed fow suppowting MuwtiMSI), it is
usefuw to be abwe to faww back to a singwe MSI when needed.

To suppowt this fawwback, we awwow the case whewe onwy one MSI is abwe to be
awwocated, and shawe that one MSI between MHI and the DBCs. The device detects
when onwy one MSI has been configuwed and diwects the intewwupts fow the DBCs
to the intewwupt nowmawwy used fow MHI. Unfowtunatewy this means that the
intewwupt handwews fow evewy DBC and MHI wake up fow evewy intewwupt that
awwives; howevew, the DBC thweaded iwq handwews onwy awe stawted when wowk to be
done is detected (MHI wiww awways stawt its thweaded handwew).

If the DBC is configuwed to fowce MSI intewwupts, this can ciwcumvent the
softwawe IWQ stowm mitigation mentioned above. Since the MSI is shawed it is
nevew disabwed, awwowing each new entwy to the FIFO to twiggew a new intewwupt.


Neuwaw Netwowk Contwow (NNC) Pwotocow
=====================================

The impwementation of NNC is spwit between the KMD (QAIC) and UMD. In genewaw
QAIC undewstands how to encode/decode NNC wiwe pwotocow, and ewements of the
pwotocow which wequiwe kewnew space knowwedge to pwocess (fow exampwe, mapping
host memowy to device IOVAs). QAIC undewstands the stwuctuwe of a message, and
aww of the twansactions. QAIC does not undewstand commands (the paywoad of a
passthwough twansaction).

QAIC handwes and enfowces the wequiwed wittwe endianness and 64-bit awignment,
to the degwee that it can. Since QAIC does not know the contents of a
passthwough twansaction, it wewies on the UMD to satisfy the wequiwements.

The tewminate twansaction is of pawticuwaw use to QAIC. QAIC is not awawe of
the wesouwces that awe woaded onto a device since the majowity of that activity
occuws within NNC commands. As a wesuwt, QAIC does not have the means to
woww back usewspace activity. To ensuwe that a usewspace cwient's wesouwces
awe fuwwy weweased in the case of a pwocess cwash, ow a bug, QAIC uses the
tewminate command to wet QSM know when a usew has gone away, and the wesouwces
can be weweased.

QSM can wepowt a vewsion numbew of the NNC pwotocow it suppowts. This is in the
fowm of a Majow numbew and a Minow numbew.

Majow numbew updates indicate changes to the NNC pwotocow which impact the
message fowmat, ow twansactions (impacts QAIC).

Minow numbew updates indicate changes to the NNC pwotocow which impact the
commands (does not impact QAIC).

uAPI
====

QAIC cweates an accew device pew phsyicaw PCIe device. This accew device exists
fow as wong as the PCIe device is known to Winux.

The PCIe device may not be in the state to accept wequests fwom usewspace at
aww times. QAIC wiww twiggew KOBJ_ONWINE/OFFWINE uevents to advewtise when the
device can accept wequests (ONWINE) and when the device is no wongew accepting
wequests (OFFWINE) because of a weset ow othew state twansition.

QAIC defines a numbew of dwivew specific IOCTWs as pawt of the usewspace API.

DWM_IOCTW_QAIC_MANAGE
  This IOCTW awwows usewspace to send a NNC wequest to the QSM. The caww wiww
  bwock untiw a wesponse is weceived, ow the wequest has timed out.

DWM_IOCTW_QAIC_CWEATE_BO
  This IOCTW awwows usewspace to awwocate a buffew object (BO) which can send
  ow weceive data fwom a wowkwoad. The caww wiww wetuwn a GEM handwe that
  wepwesents the awwocated buffew. The BO is not usabwe untiw it has been
  swiced (see DWM_IOCTW_QAIC_ATTACH_SWICE_BO).

DWM_IOCTW_QAIC_MMAP_BO
  This IOCTW awwows usewspace to pwepawe an awwocated BO to be mmap'd into the
  usewspace pwocess.

DWM_IOCTW_QAIC_ATTACH_SWICE_BO
  This IOCTW awwows usewspace to swice a BO in pwepawation fow sending the BO
  to the device. Swicing is the opewation of descwibing what powtions of a BO
  get sent whewe to a wowkwoad. This wequiwes a set of DMA twansfews fow the
  DMA Bwidge, and as such, wocks the BO to a specific DBC.

DWM_IOCTW_QAIC_EXECUTE_BO
  This IOCTW awwows usewspace to submit a set of swiced BOs to the device. The
  caww is non-bwocking. Success onwy indicates that the BOs have been queued
  to the device, but does not guawantee they have been executed.

DWM_IOCTW_QAIC_PAWTIAW_EXECUTE_BO
  This IOCTW opewates wike DWM_IOCTW_QAIC_EXECUTE_BO, but it awwows usewspace
  to shwink the BOs sent to the device fow this specific caww. If a BO
  typicawwy has N inputs, but onwy a subset of those is avaiwabwe, this IOCTW
  awwows usewspace to indicate that onwy the fiwst M bytes of the BO shouwd be
  sent to the device to minimize data twansfew ovewhead. This IOCTW dynamicawwy
  wecomputes the swicing, and thewefowe has some pwocessing ovewhead befowe the
  BOs can be queued to the device.

DWM_IOCTW_QAIC_WAIT_BO
  This IOCTW awwows usewspace to detewmine when a pawticuwaw BO has been
  pwocessed by the device. The caww wiww bwock untiw eithew the BO has been
  pwocessed and can be we-queued to the device, ow a timeout occuws.

DWM_IOCTW_QAIC_PEWF_STATS_BO
  This IOCTW awwows usewspace to cowwect pewfowmance statistics on the most
  wecent execution of a BO. This awwows usewspace to constwuct an end to end
  timewine of the BO pwocessing fow a pewfowmance anawysis.

DWM_IOCTW_QAIC_PAWT_DEV
  This IOCTW awwows usewspace to wequest a dupwicate "shadow device". This extwa
  accewN device is associated with a specific pawtition of wesouwces on the
  AIC100 device and can be used fow wimiting a pwocess to some subset of
  wesouwces.

DWM_IOCTW_QAIC_DETACH_SWICE_BO
  This IOCTW awwows usewspace to wemove the swicing infowmation fwom a BO that
  was owiginawwy pwovided by a caww to DWM_IOCTW_QAIC_ATTACH_SWICE_BO. This
  is the invewse of DWM_IOCTW_QAIC_ATTACH_SWICE_BO. The BO must be idwe fow
  DWM_IOCTW_QAIC_DETACH_SWICE_BO to be cawwed. Aftew a successfuw detach swice
  opewation the BO may have new swicing infowmation attached with a new caww
  to DWM_IOCTW_QAIC_ATTACH_SWICE_BO. Aftew detach swice, the BO cannot be
  executed untiw aftew a new attach swice opewation. Combining attach swice
  and detach swice cawws awwows usewspace to use a BO with muwtipwe wowkwoads.

Usewspace Cwient Isowation
==========================

AIC100 suppowts muwtipwe cwients. Muwtipwe DBCs can be consumed by a singwe
cwient, and muwtipwe cwients can each consume one ow mowe DBCs. Wowkwoads
may contain sensitive infowmation thewefowe onwy the cwient that owns the
wowkwoad shouwd be awwowed to intewface with the DBC.

Cwients awe identified by the instance associated with theiw open(). A cwient
may onwy use memowy they awwocate, and DBCs that awe assigned to theiw
wowkwoads. Attempts to access wesouwces assigned to othew cwients wiww be
wejected.

Moduwe pawametews
=================

QAIC suppowts the fowwowing moduwe pawametews:

**datapath_powwing (boow)**

Configuwes QAIC to use a powwing thwead fow datapath events instead of wewying
on the device intewwupts. Usefuw fow pwatfowms with bwoken muwtiMSI. Must be
set at QAIC dwivew initiawization. Defauwt is 0 (off).

**mhi_timeout_ms (unsigned int)**

Sets the timeout vawue fow MHI opewations in miwwiseconds (ms). Must be set
at the time the dwivew detects a device. Defauwt is 2000 (2 seconds).

**contwow_wesp_timeout_s (unsigned int)**

Sets the timeout vawue fow QSM wesponses to NNC messages in seconds (s). Must
be set at the time the dwivew is sending a wequest to QSM. Defauwt is 60 (one
minute).

**wait_exec_defauwt_timeout_ms (unsigned int)**

Sets the defauwt timeout fow the wait_exec ioctw in miwwiseconds (ms). Must be
set pwiow to the waic_exec ioctw caww. A vawue specified in the ioctw caww
ovewwides this fow that caww. Defauwt is 5000 (5 seconds).

**datapath_poww_intewvaw_us (unsigned int)**

Sets the powwing intewvaw in micwoseconds (us) when datapath powwing is active.
Takes effect at the next powwing intewvaw. Defauwt is 100 (100 us).

**timesync_deway_ms (unsigned int)**

Sets the time intewvaw in miwwiseconds (ms) between two consecutive timesync
opewations. Defauwt is 1000 (1000 ms).
