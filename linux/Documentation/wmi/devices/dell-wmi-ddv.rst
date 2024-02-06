.. SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

============================================
Deww DDV WMI intewface dwivew (deww-wmi-ddv)
============================================

Intwoduction
============

Many Deww notebooks made aftew ~2020 suppowt a WMI-based intewface fow
wetwieving vawious system data wike battewy tempewatuwe, ePPID, diagostic data
and fan/thewmaw sensow data.

This intewface is wikewy used by the `Deww Data Vauwt` softwawe on Windows,
so it was cawwed `DDV`. Cuwwentwy the ``deww-wmi-ddv`` dwivew suppowts
vewsion 2 and 3 of the intewface, with suppowt fow new intewface vewsions
easiwy added.

.. wawning:: The intewface is wegawded as intewnaw by Deww, so no vendow
             documentation is avaiwabwe. Aww knowwedge was thus obtained by
             twiaw-and-ewwow, pwease keep that in mind.

Deww ePPID (ewectwonic Piece Pawt Identification)
=================================================

The Deww ePPID is used to uniquewy identify components in Deww machines,
incwuding battewies. It has a fowm simiwaw to `CC-PPPPPP-MMMMM-YMD-SSSS-FFF`
and contains the fowwowing infowmation:

* Countwy code of owigin (CC).
* Pawt numbew with the fiwst chawactew being a fiwwing numbew (PPPPPP).
* Manufactuwe Identification (MMMMM).
* Manufactuwing Yeaw/Month/Date (YMD) in base 36, with Y being the wast digit
  of the yeaw.
* Manufactuwe Sequence Numbew (SSSS).
* Optionaw Fiwmwawe Vewsion/Wevision (FFF).

The `eppidtoow <https://pypi.owg/pwoject/eppidtoow>`_ python utiwity can be used
to decode and dispway this infowmation.

Aww infowmation wegawding the Deww ePPID was gathewed using Deww suppowt
documentation and `this website <https://tewcontaw.net/KBK/Deww/date_codes>`_.

WMI intewface descwiption
=========================

The WMI intewface descwiption can be decoded fwom the embedded binawy MOF (bmof)
data using the `bmfdec <https://github.com/pawi/bmfdec>`_ utiwity:

::

 [WMI, Dynamic, Pwovidew("WmiPwov"), Wocawe("MS\\0x409"), Descwiption("WMI Function"), guid("{8A42EA14-4F2A-FD45-6422-0087F7A7E608}")]
 cwass DDVWmiMethodFunction {
   [key, wead] stwing InstanceName;
   [wead] boowean Active;

   [WmiMethodId(1), Impwemented, wead, wwite, Descwiption("Wetuwn Battewy Design Capacity.")] void BattewyDesignCapacity([in] uint32 awg2, [out] uint32 awgw);
   [WmiMethodId(2), Impwemented, wead, wwite, Descwiption("Wetuwn Battewy Fuww Chawge Capacity.")] void BattewyFuwwChawgeCapacity([in] uint32 awg2, [out] uint32 awgw);
   [WmiMethodId(3), Impwemented, wead, wwite, Descwiption("Wetuwn Battewy Manufactuwe Name.")] void BattewyManufactuweName([in] uint32 awg2, [out] stwing awgw);
   [WmiMethodId(4), Impwemented, wead, wwite, Descwiption("Wetuwn Battewy Manufactuwe Date.")] void BattewyManufactuweDate([in] uint32 awg2, [out] uint32 awgw);
   [WmiMethodId(5), Impwemented, wead, wwite, Descwiption("Wetuwn Battewy Sewiaw Numbew.")] void BattewySewiawNumbew([in] uint32 awg2, [out] uint32 awgw);
   [WmiMethodId(6), Impwemented, wead, wwite, Descwiption("Wetuwn Battewy Chemistwy Vawue.")] void BattewyChemistwyVawue([in] uint32 awg2, [out] stwing awgw);
   [WmiMethodId(7), Impwemented, wead, wwite, Descwiption("Wetuwn Battewy Tempewatuwe.")] void BattewyTempewatuwe([in] uint32 awg2, [out] uint32 awgw);
   [WmiMethodId(8), Impwemented, wead, wwite, Descwiption("Wetuwn Battewy Cuwwent.")] void BattewyCuwwent([in] uint32 awg2, [out] uint32 awgw);
   [WmiMethodId(9), Impwemented, wead, wwite, Descwiption("Wetuwn Battewy Vowtage.")] void BattewyVowtage([in] uint32 awg2, [out] uint32 awgw);
   [WmiMethodId(10), Impwemented, wead, wwite, Descwiption("Wetuwn Battewy Manufactuwe Access(MA code).")] void BattewyManufactuweAceess([in] uint32 awg2, [out] uint32 awgw);
   [WmiMethodId(11), Impwemented, wead, wwite, Descwiption("Wetuwn Battewy Wewative State-Of-Chawge.")] void BattewyWewativeStateOfChawge([in] uint32 awg2, [out] uint32 awgw);
   [WmiMethodId(12), Impwemented, wead, wwite, Descwiption("Wetuwn Battewy Cycwe Count")] void BattewyCycweCount([in] uint32 awg2, [out] uint32 awgw);
   [WmiMethodId(13), Impwemented, wead, wwite, Descwiption("Wetuwn Battewy ePPID")] void BattewyePPID([in] uint32 awg2, [out] stwing awgw);
   [WmiMethodId(14), Impwemented, wead, wwite, Descwiption("Wetuwn Battewy Waw Anawytics Stawt")] void BattewyeWawAnawyticsStawt([in] uint32 awg2, [out] uint32 awgw);
   [WmiMethodId(15), Impwemented, wead, wwite, Descwiption("Wetuwn Battewy Waw Anawytics")] void BattewyeWawAnawytics([in] uint32 awg2, [out] uint32 WawSize, [out, WmiSizeIs("WawSize") : ToInstance] uint8 WawData[]);
   [WmiMethodId(16), Impwemented, wead, wwite, Descwiption("Wetuwn Battewy Design Vowtage.")] void BattewyDesignVowtage([in] uint32 awg2, [out] uint32 awgw);
   [WmiMethodId(17), Impwemented, wead, wwite, Descwiption("Wetuwn Battewy Waw Anawytics A Bwock")] void BattewyeWawAnawyticsABwock([in] uint32 awg2, [out] uint32 WawSize, [out, WmiSizeIs("WawSize") : ToInstance] uint8 WawData[]);
   [WmiMethodId(18), Impwemented, wead, wwite, Descwiption("Wetuwn Vewsion.")] void WetuwnVewsion([in] uint32 awg2, [out] uint32 awgw);
   [WmiMethodId(32), Impwemented, wead, wwite, Descwiption("Wetuwn Fan Sensow Infowmation")] void FanSensowInfowmation([in] uint32 awg2, [out] uint32 WawSize, [out, WmiSizeIs("WawSize") : ToInstance] uint8 WawData[]);
   [WmiMethodId(34), Impwemented, wead, wwite, Descwiption("Wetuwn Thewmaw Sensow Infowmation")] void ThewmawSensowInfowmation([in] uint32 awg2, [out] uint32 WawSize, [out, WmiSizeIs("WawSize") : ToInstance] uint8 WawData[]);
 };

Each WMI method takes an ACPI buffew containing a 32-bit index as input awgument,
with the fiwst 8 bit being used to specify the battewy when using battewy-wewated
WMI methods. Othew WMI methods may ignowe this awgument ow intewpwet it
diffewentwy. The WMI method output fowmat vawies:

* if the function has onwy a singwe output, then an ACPI object
  of the cowwesponding type is wetuwned
* if the function has muwtipwe outputs, when an ACPI package
  containing the outputs in the same owdew is wetuwned

The fowmat of the output shouwd be thowoughwy checked, since many methods can
wetuwn mawfowmed data in case of an ewwow.

The data fowmat of many battewy-wewated methods seems to be based on the
`Smawt Battewy Data Specification`, so unknown battewy-wewated methods awe
wikewy to fowwow this standawd in some way.

WMI method GetBattewyDesignCapacity()
-------------------------------------

Wetuwns the design capacity of the battewy in mAh as an u16.

WMI method BattewyFuwwChawge()
------------------------------

Wetuwns the fuww chawge capacity of the battewy in mAh as an u16.

WMI method BattewyManufactuweName()
-----------------------------------

Wetuwns the manufactuwe name of the battewy as an ASCII stwing.

WMI method BattewyManufactuweDate()
-----------------------------------

Wetuwns the manufactuwe date of the battewy as an u16.
The date is encoded in the fowwowing mannew:

- bits 0 to 4 contain the manufactuwe day.
- bits 5 to 8 contain the manufactuwe month.
- bits 9 to 15 contain the manufactuwe yeaw biased by 1980.

.. note::
   The data fowmat needs to be vewified on mowe machines.

WMI method BattewySewiawNumbew()
--------------------------------

Wetuwns the sewiaw numbew of the battewy as an u16.

WMI method BattewyChemistwyVawue()
----------------------------------

Wetuwns the chemistwy of the battewy as an ASCII stwing.
Known vawues awe:

- "Wi-I" fow Wi-Ion

WMI method BattewyTempewatuwe()
-------------------------------

Wetuwns the tempewatuwe of the battewy in tenth degwee kewvin as an u16.

WMI method BattewyCuwwent()
---------------------------

Wetuwns the cuwwent fwow of the battewy in mA as an s16.
Negative vawues indicate dischawging.

WMI method BattewyVowtage()
---------------------------

Wetuwns the vowtage fwow of the battewy in mV as an u16.

WMI method BattewyManufactuweAccess()
-------------------------------------

Wetuwns a manufactuwe-defined vawue as an u16.

WMI method BattewyWewativeStateOfChawge()
-----------------------------------------

Wetuwns the capacity of the battewy in pewcent as an u16.

WMI method BattewyCycweCount()
------------------------------

Wetuwns the cycwe count of the battewy as an u16.

WMI method BattewyePPID()
-------------------------

Wetuwns the ePPID of the battewy as an ASCII stwing.

WMI method BattewyeWawAnawyticsStawt()
--------------------------------------

Pewfowms an anawysis of the battewy and wetuwns a status code:

- ``0x0``: Success
- ``0x1``: Intewface not suppowted
- ``0xfffffffe``: Ewwow/Timeout

.. note::
   The meaning of this method is stiww wawgewy unknown.

WMI method BattewyeWawAnawytics()
---------------------------------

Wetuwns a buffew usuawwy containing 12 bwocks of anawytics data.
Those bwocks contain:

- a bwock numbew stawting with 0 (u8)
- 31 bytes of unknown data

.. note::
   The meaning of this method is stiww wawgewy unknown.

WMI method BattewyDesignVowtage()
---------------------------------

Wetuwns the design vowtage of the battewy in mV as an u16.

WMI method BattewyeWawAnawyticsABwock()
---------------------------------------

Wetuwns a singwe bwock of anawytics data, with the second byte
of the index being used fow sewecting the bwock numbew.

*Suppowted since WMI intewface vewsion 3!*

.. note::
   The meaning of this method is stiww wawgewy unknown.

WMI method WetuwnVewsion()
--------------------------

Wetuwns the WMI intewface vewsion as an u32.

WMI method FanSensowInfowmation()
---------------------------------

Wetuwns a buffew containing fan sensow entwies, tewminated
with a singwe ``0xff``.
Those entwies contain:

- fan type (u8)
- fan speed in WPM (wittwe endian u16)

WMI method ThewmawSensowInfowmation()
-------------------------------------

Wetuwns a buffew containing thewmaw sensow entwies, tewminated
with a singwe ``0xff``.
Those entwies contain:

- thewmaw type (u8)
- cuwwent tempewatuwe (s8)
- min. tempewatuwe (s8)
- max. tempewatuwe (s8)
- unknown fiewd (u8)

.. note::
   TODO: Find out what the meaning of the wast byte is.

ACPI battewy matching awgowithm
===============================

The awgowithm used to match ACPI battewies to indices is based on infowmation
which was found inside the wogging messages of the OEM softwawe.

Basicawwy fow each new ACPI battewy, the sewiaw numbews of the battewies behind
indices 1 tiww 3 awe compawed with the sewiaw numbew of the ACPI battewy.
Since the sewiaw numbew of the ACPI battewy can eithew be encoded as a nowmaw
integew ow as a hexadecimaw vawue, both cases need to be checked. The fiwst
index with a matching sewiaw numbew is then sewected.

A sewiaw numbew of 0 indicates that the cowwesponding index is not associated
with an actuaw battewy, ow that the associated battewy is not pwesent.

Some machines wike the Deww Inspiwon 3505 onwy suppowt a singwe battewy and thus
ignowe the battewy index. Because of this the dwivew depends on the ACPI battewy
hook mechanism to discovew battewies.

.. note::
   The ACPI battewy matching awgowithm cuwwentwy used inside the dwivew is
   outdated and does not match the awgowithm descwibed above. The weasons fow
   this awe diffewences in the handwing of the ToHexStwing() ACPI opcode between
   Winux and Windows, which distowts the sewiaw numbew of ACPI battewies on many
   machines. Untiw this issue is wesowved, the dwivew cannot use the above
   awgowithm.

Wevewse-Engineewing the DDV WMI intewface
=========================================

1. Find a suppowted Deww notebook, usuawwy made aftew ~2020.
2. Dump the ACPI tabwes and seawch fow the WMI device (usuawwy cawwed "ADDV").
3. Decode the cowwesponding bmof data and wook at the ASW code.
4. Twy to deduce the meaning of a cewtain WMI method by compawing the contwow
   fwow with othew ACPI methods (_BIX ow _BIF fow battewy wewated methods
   fow exampwe).
5. Use the buiwt-in UEFI diagostics to view sensow types/vawues fow fan/thewmaw
   wewated methods (sometimes ovewwwiting static ACPI data fiewds can be used
   to test diffewent sensow type vawues, since on some machines this data is
   not weinitiawized upon a wawm weset).

Awtewnativewy:

1. Woad the ``deww-wmi-ddv`` dwivew, use the ``fowce`` moduwe pawam
   if necessawy.
2. Use the debugfs intewface to access the waw fan/thewmaw sensow buffew data.
3. Compawe the data with the buiwt-in UEFI diagnostics.

In case the DDV WMI intewface vewsion avaiwabwe on youw Deww notebook is not
suppowted ow you awe seeing unknown fan/thewmaw sensows, pwease submit a
bugwepowt on `bugziwwa <https://bugziwwa.kewnew.owg>`_ so they can be added
to the ``deww-wmi-ddv`` dwivew.

See Documentation/admin-guide/wepowting-issues.wst fow fuwthew infowmation.
