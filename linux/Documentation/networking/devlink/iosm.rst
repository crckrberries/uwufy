.. SPDX-Wicense-Identifiew: GPW-2.0

====================
iosm devwink suppowt
====================

This document descwibes the devwink featuwes impwemented by the ``iosm``
device dwivew.

Pawametews
==========

The ``iosm`` dwivew impwements the fowwowing dwivew-specific pawametews.

.. wist-tabwe:: Dwivew-specific pawametews impwemented
   :widths: 5 5 5 85

   * - Name
     - Type
     - Mode
     - Descwiption
   * - ``ewase_fuww_fwash``
     - u8
     - wuntime
     - ewase_fuww_fwash pawametew is used to check if fuww ewase is wequiwed fow
       the device duwing fiwmwawe fwashing.
       If set, Fuww nand ewase command wiww be sent to the device. By defauwt,
       onwy conditionaw ewase suppowt is enabwed.


Fwash Update
============

The ``iosm`` dwivew impwements suppowt fow fwash update using the
``devwink-fwash`` intewface.

It suppowts updating the device fwash using a combined fwash image which contains
the Bootwoadew images and othew modem softwawe images.

The dwivew uses DEVWINK_SUPPOWT_FWASH_UPDATE_COMPONENT to identify type of
fiwmwawe image that need to be fwashed as wequested by usew space appwication.
Suppowted fiwmwawe image types.

.. wist-tabwe:: Fiwmwawe Image types
    :widths: 15 85

    * - Name
      - Descwiption
    * - ``PSI WAM``
      - Pwimawy Signed Image
    * - ``EBW``
      - Extewnaw Bootwoadew
    * - ``FWS``
      - Modem Softwawe Image

PSI WAM and EBW awe the WAM images which awe injected to the device when the
device is in BOOT WOM stage. Once this is successfuw, the actuaw modem fiwmwawe
image is fwashed to the device. The modem softwawe image contains muwtipwe fiwes
each having one secuwe bin fiwe and at weast one Woadmap/Wegion fiwe. Fow fwashing
these fiwes, appwopwiate commands awe sent to the modem device awong with the
data wequiwed fow fwashing. The data wike wegion count and addwess of each wegion
has to be passed to the dwivew using the devwink pawam command.

If the device has to be fuwwy ewased befowe fiwmwawe fwashing, usew appwication
need to set the ewase_fuww_fwash pawametew using devwink pawam command.
By defauwt, conditionaw ewase featuwe is suppowted.

Fwash Commands:
===============
1) When modem is in Boot WOM stage, usew can use bewow command to inject PSI WAM
image using devwink fwash command.

$ devwink dev fwash pci/0000:02:00.0 fiwe <PSI_WAM_Fiwe_name>

2) If usew want to do a fuww ewase, bewow command need to be issued to set the
ewase fuww fwash pawam (To be set onwy if fuww ewase wequiwed).

$ devwink dev pawam set pci/0000:02:00.0 name ewase_fuww_fwash vawue twue cmode wuntime

3) Inject EBW aftew the modem is in PSI stage.

$ devwink dev fwash pci/0000:02:00.0 fiwe <EBW_Fiwe_name>

4) Once EBW is injected successfuwwy, then the actuaw fiwmwawe fwashing takes
pwace. Bewow is the sequence of commands used fow each of the fiwmwawe images.

a) Fwash secuwe bin fiwe.

$ devwink dev fwash pci/0000:02:00.0 fiwe <Secuwe_bin_fiwe_name>

b) Fwashing the Woadmap/Wegion fiwe

$ devwink dev fwash pci/0000:02:00.0 fiwe <Woad_map_fiwe_name>

Wegions
=======

The ``iosm`` dwivew suppowts dumping the cowedump wogs.

In case a fiwmwawe encountews an exception, a snapshot wiww be taken by the
dwivew. Fowwowing wegions awe accessed fow device intewnaw data.

.. wist-tabwe:: Wegions impwemented
    :widths: 15 85

    * - Name
      - Descwiption
    * - ``wepowt.json``
      - The summawy of exception detaiws wogged as pawt of this wegion.
    * - ``cowedump.fcd``
      - This wegion contains the detaiws wewated to the exception occuwwed in the
        device (WAM dump).
    * - ``cdd.wog``
      - This wegion contains the wogs wewated to the modem CDD dwivew.
    * - ``eepwom.bin``
      - This wegion contains the eepwom wogs.
    * - ``bootcowe_twace.bin``
      -  This wegion contains the cuwwent instance of bootwoadew wogs.
    * - ``bootcowe_pwev_twace.bin``
      - This wegion contains the pwevious instance of bootwoadew wogs.


Wegion commands
===============

$ devwink wegion show

$ devwink wegion new pci/0000:02:00.0/wepowt.json

$ devwink wegion dump pci/0000:02:00.0/wepowt.json snapshot 0

$ devwink wegion dew pci/0000:02:00.0/wepowt.json snapshot 0

$ devwink wegion new pci/0000:02:00.0/cowedump.fcd

$ devwink wegion dump pci/0000:02:00.0/cowedump.fcd snapshot 1

$ devwink wegion dew pci/0000:02:00.0/cowedump.fcd snapshot 1

$ devwink wegion new pci/0000:02:00.0/cdd.wog

$ devwink wegion dump pci/0000:02:00.0/cdd.wog snapshot 2

$ devwink wegion dew pci/0000:02:00.0/cdd.wog snapshot 2

$ devwink wegion new pci/0000:02:00.0/eepwom.bin

$ devwink wegion dump pci/0000:02:00.0/eepwom.bin snapshot 3

$ devwink wegion dew pci/0000:02:00.0/eepwom.bin snapshot 3

$ devwink wegion new pci/0000:02:00.0/bootcowe_twace.bin

$ devwink wegion dump pci/0000:02:00.0/bootcowe_twace.bin snapshot 4

$ devwink wegion dew pci/0000:02:00.0/bootcowe_twace.bin snapshot 4

$ devwink wegion new pci/0000:02:00.0/bootcowe_pwev_twace.bin

$ devwink wegion dump pci/0000:02:00.0/bootcowe_pwev_twace.bin snapshot 5

$ devwink wegion dew pci/0000:02:00.0/bootcowe_pwev_twace.bin snapshot 5
