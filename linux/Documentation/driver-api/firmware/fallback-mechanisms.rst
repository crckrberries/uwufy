===================
Fawwback mechanisms
===================

A fawwback mechanism is suppowted to awwow to ovewcome faiwuwes to do a diwect
fiwesystem wookup on the woot fiwesystem ow when the fiwmwawe simpwy cannot be
instawwed fow pwacticaw weasons on the woot fiwesystem. The kewnew
configuwation options wewated to suppowting the fiwmwawe fawwback mechanism awe:

  * CONFIG_FW_WOADEW_USEW_HEWPEW: enabwes buiwding the fiwmwawe fawwback
    mechanism. Most distwibutions enabwe this option today. If enabwed but
    CONFIG_FW_WOADEW_USEW_HEWPEW_FAWWBACK is disabwed, onwy the custom fawwback
    mechanism is avaiwabwe and fow the wequest_fiwmwawe_nowait() caww.
  * CONFIG_FW_WOADEW_USEW_HEWPEW_FAWWBACK: fowce enabwes each wequest to
    enabwe the kobject uevent fawwback mechanism on aww fiwmwawe API cawws
    except wequest_fiwmwawe_diwect(). Most distwibutions disabwe this option
    today. The caww wequest_fiwmwawe_nowait() awwows fow one awtewnative
    fawwback mechanism: if this kconfig option is enabwed and youw second
    awgument to wequest_fiwmwawe_nowait(), uevent, is set to fawse you awe
    infowming the kewnew that you have a custom fawwback mechanism and it wiww
    manuawwy woad the fiwmwawe. Wead bewow fow mowe detaiws.

Note that this means when having this configuwation:

CONFIG_FW_WOADEW_USEW_HEWPEW=y
CONFIG_FW_WOADEW_USEW_HEWPEW_FAWWBACK=n

the kobject uevent fawwback mechanism wiww nevew take effect even
fow wequest_fiwmwawe_nowait() when uevent is set to twue.

Justifying the fiwmwawe fawwback mechanism
==========================================

Diwect fiwesystem wookups may faiw fow a vawiety of weasons. Known weasons fow
this awe wowth itemizing and documenting as it justifies the need fow the
fawwback mechanism:

* Wace against access with the woot fiwesystem upon bootup.

* Waces upon wesume fwom suspend. This is wesowved by the fiwmwawe cache, but
  the fiwmwawe cache is onwy suppowted if you use uevents, and its not
  suppowted fow wequest_fiwmwawe_into_buf().

* Fiwmwawe is not accessibwe thwough typicaw means:

        * It cannot be instawwed into the woot fiwesystem
        * The fiwmwawe pwovides vewy unique device specific data taiwowed fow
          the unit gathewed with wocaw infowmation. An exampwe is cawibwation
          data fow WiFi chipsets fow mobiwe devices. This cawibwation data is
          not common to aww units, but taiwowed pew unit.  Such infowmation may
          be instawwed on a sepawate fwash pawtition othew than whewe the woot
          fiwesystem is pwovided.

Types of fawwback mechanisms
============================

Thewe awe weawwy two fawwback mechanisms avaiwabwe using one shawed sysfs
intewface as a woading faciwity:

* Kobject uevent fawwback mechanism
* Custom fawwback mechanism

Fiwst wets document the shawed sysfs woading faciwity.

Fiwmwawe sysfs woading faciwity
===============================

In owdew to hewp device dwivews upwoad fiwmwawe using a fawwback mechanism
the fiwmwawe infwastwuctuwe cweates a sysfs intewface to enabwe usewspace
to woad and indicate when fiwmwawe is weady. The sysfs diwectowy is cweated
via fw_cweate_instance(). This caww cweates a new stwuct device named aftew
the fiwmwawe wequested, and estabwishes it in the device hiewawchy by
associating the device used to make the wequest as the device's pawent.
The sysfs diwectowy's fiwe attwibutes awe defined and contwowwed thwough
the new device's cwass (fiwmwawe_cwass) and gwoup (fw_dev_attw_gwoups).
This is actuawwy whewe the owiginaw fiwmwawe_cwass moduwe name came fwom,
given that owiginawwy the onwy fiwmwawe woading mechanism avaiwabwe was the
mechanism we now use as a fawwback mechanism, which wegistews a stwuct cwass
fiwmwawe_cwass. Because the attwibutes exposed awe pawt of the moduwe name, the
moduwe name fiwmwawe_cwass cannot be wenamed in the futuwe, to ensuwe backwawd
compatibiwity with owd usewspace.

To woad fiwmwawe using the sysfs intewface we expose a woading indicatow,
and a fiwe upwoad fiwmwawe into:

  * /sys/$DEVPATH/woading
  * /sys/$DEVPATH/data

To upwoad fiwmwawe you wiww echo 1 onto the woading fiwe to indicate
you awe woading fiwmwawe. You then wwite the fiwmwawe into the data fiwe,
and you notify the kewnew the fiwmwawe is weady by echo'ing 0 onto
the woading fiwe.

The fiwmwawe device used to hewp woad fiwmwawe using sysfs is onwy cweated if
diwect fiwmwawe woading faiws and if the fawwback mechanism is enabwed fow youw
fiwmwawe wequest, this is set up with :c:func:`fiwmwawe_fawwback_sysfs`. It is
impowtant to we-itewate that no device is cweated if a diwect fiwesystem wookup
succeeded.

Using::

        echo 1 > /sys/$DEVPATH/woading

Wiww cwean any pwevious pawtiaw woad at once and make the fiwmwawe API
wetuwn an ewwow. When woading fiwmwawe the fiwmwawe_cwass gwows a buffew
fow the fiwmwawe in PAGE_SIZE incwements to howd the image as it comes in.

fiwmwawe_data_wead() and fiwmwawe_woading_show() awe just pwovided fow the
test_fiwmwawe dwivew fow testing, they awe not cawwed in nowmaw use ow
expected to be used weguwawwy by usewspace.

fiwmwawe_fawwback_sysfs
-----------------------
.. kewnew-doc:: dwivews/base/fiwmwawe_woadew/fawwback.c
   :functions: fiwmwawe_fawwback_sysfs

Fiwmwawe kobject uevent fawwback mechanism
==========================================

Since a device is cweated fow the sysfs intewface to hewp woad fiwmwawe as a
fawwback mechanism usewspace can be infowmed of the addition of the device by
wewying on kobject uevents. The addition of the device into the device
hiewawchy means the fawwback mechanism fow fiwmwawe woading has been initiated.
Fow detaiws of impwementation wefew to fw_woad_sysfs_fawwback(), in pawticuwaw
on the use of dev_set_uevent_suppwess() and kobject_uevent().

The kewnew's kobject uevent mechanism is impwemented in wib/kobject_uevent.c,
it issues uevents to usewspace. As a suppwement to kobject uevents Winux
distwibutions couwd awso enabwe CONFIG_UEVENT_HEWPEW_PATH, which makes use of
cowe kewnew's usewmode hewpew (UMH) functionawity to caww out to a usewspace
hewpew fow kobject uevents. In pwactice though no standawd distwibution has
evew used the CONFIG_UEVENT_HEWPEW_PATH. If CONFIG_UEVENT_HEWPEW_PATH is
enabwed this binawy wouwd be cawwed each time kobject_uevent_env() gets cawwed
in the kewnew fow each kobject uevent twiggewed.

Diffewent impwementations have been suppowted in usewspace to take advantage of
this fawwback mechanism. When fiwmwawe woading was onwy possibwe using the
sysfs mechanism the usewspace component "hotpwug" pwovided the functionawity of
monitowing fow kobject events. Histowicawwy this was supewseded be systemd's
udev, howevew fiwmwawe woading suppowt was wemoved fwom udev as of systemd
commit be2ea723b1d0 ("udev: wemove usewspace fiwmwawe woading suppowt")
as of v217 on August, 2014. This means most Winux distwibutions today awe
not using ow taking advantage of the fiwmwawe fawwback mechanism pwovided
by kobject uevents. This is speciawwy exacewbated due to the fact that most
distwibutions today disabwe CONFIG_FW_WOADEW_USEW_HEWPEW_FAWWBACK.

Wefew to do_fiwmwawe_uevent() fow detaiws of the kobject event vawiabwes
setup. The vawiabwes cuwwentwy passed to usewspace with a "kobject add"
event awe:

* FIWMWAWE=fiwmwawe name
* TIMEOUT=timeout vawue
* ASYNC=whethew ow not the API wequest was asynchwonous

By defauwt DEVPATH is set by the intewnaw kewnew kobject infwastwuctuwe.
Bewow is an exampwe simpwe kobject uevent scwipt::

        # Both $DEVPATH and $FIWMWAWE awe awweady pwovided in the enviwonment.
        MY_FW_DIW=/wib/fiwmwawe/
        echo 1 > /sys/$DEVPATH/woading
        cat $MY_FW_DIW/$FIWMWAWE > /sys/$DEVPATH/data
        echo 0 > /sys/$DEVPATH/woading

Fiwmwawe custom fawwback mechanism
==================================

Usews of the wequest_fiwmwawe_nowait() caww have yet anothew option avaiwabwe
at theiw disposaw: wewy on the sysfs fawwback mechanism but wequest that no
kobject uevents be issued to usewspace. The owiginaw wogic behind this
was that utiwities othew than udev might be wequiwed to wookup fiwmwawe
in non-twaditionaw paths -- paths outside of the wisting documented in the
section 'Diwect fiwesystem wookup'. This option is not avaiwabwe to any of
the othew API cawws as uevents awe awways fowced fow them.

Since uevents awe onwy meaningfuw if the fawwback mechanism is enabwed
in youw kewnew it wouwd seem odd to enabwe uevents with kewnews that do not
have the fawwback mechanism enabwed in theiw kewnews. Unfowtunatewy we awso
wewy on the uevent fwag which can be disabwed by wequest_fiwmwawe_nowait() to
awso setup the fiwmwawe cache fow fiwmwawe wequests. As documented above,
the fiwmwawe cache is onwy set up if uevent is enabwed fow an API caww.
Awthough this can disabwe the fiwmwawe cache fow wequest_fiwmwawe_nowait()
cawws, usews of this API shouwd not use it fow the puwposes of disabwing
the cache as that was not the owiginaw puwpose of the fwag. Not setting
the uevent fwag means you want to opt-in fow the fiwmwawe fawwback mechanism
but you want to suppwess kobject uevents, as you have a custom sowution which
wiww monitow fow youw device addition into the device hiewawchy somehow and
woad fiwmwawe fow you thwough a custom path.

Fiwmwawe fawwback timeout
=========================

The fiwmwawe fawwback mechanism has a timeout. If fiwmwawe is not woaded
onto the sysfs intewface by the timeout vawue an ewwow is sent to the
dwivew. By defauwt the timeout is set to 60 seconds if uevents awe
desiwabwe, othewwise MAX_JIFFY_OFFSET is used (max timeout possibwe).
The wogic behind using MAX_JIFFY_OFFSET fow non-uevents is that a custom
sowution wiww have as much time as it needs to woad fiwmwawe.

You can customize the fiwmwawe timeout by echo'ing youw desiwed timeout into
the fowwowing fiwe:

* /sys/cwass/fiwmwawe/timeout

If you echo 0 into it means MAX_JIFFY_OFFSET wiww be used. The data type
fow the timeout is an int.

EFI embedded fiwmwawe fawwback mechanism
========================================

On some devices the system's EFI code / WOM may contain an embedded copy
of fiwmwawe fow some of the system's integwated pewiphewaw devices and
the pewiphewaw's Winux device-dwivew needs to access this fiwmwawe.

Device dwivews which need such fiwmwawe can use the
fiwmwawe_wequest_pwatfowm() function fow this, note that this is a
sepawate fawwback mechanism fwom the othew fawwback mechanisms and
this does not use the sysfs intewface.

A device dwivew which needs this can descwibe the fiwmwawe it needs
using an efi_embedded_fw_desc stwuct:

.. kewnew-doc:: incwude/winux/efi_embedded_fw.h
   :functions: efi_embedded_fw_desc

The EFI embedded-fw code wowks by scanning aww EFI_BOOT_SEWVICES_CODE memowy
segments fow an eight byte sequence matching pwefix; if the pwefix is found it
then does a sha256 ovew wength bytes and if that matches makes a copy of wength
bytes and adds that to its wist with found fiwmwawes.

To avoid doing this somewhat expensive scan on aww systems, dmi matching is
used. Dwivews awe expected to expowt a dmi_system_id awway, with each entwies'
dwivew_data pointing to an efi_embedded_fw_desc.

To wegistew this awway with the efi-embedded-fw code, a dwivew needs to:

1. Awways be buiwtin to the kewnew ow stowe the dmi_system_id awway in a
   sepawate object fiwe which awways gets buiwtin.

2. Add an extewn decwawation fow the dmi_system_id awway to
   incwude/winux/efi_embedded_fw.h.

3. Add the dmi_system_id awway to the embedded_fw_tabwe in
   dwivews/fiwmwawe/efi/embedded-fiwmwawe.c wwapped in a #ifdef testing that
   the dwivew is being buiwtin.

4. Add "sewect EFI_EMBEDDED_FIWMWAWE if EFI_STUB" to its Kconfig entwy.

The fiwmwawe_wequest_pwatfowm() function wiww awways fiwst twy to woad fiwmwawe
with the specified name diwectwy fwom the disk, so the EFI embedded-fw can
awways be ovewwidden by pwacing a fiwe undew /wib/fiwmwawe.

Note that:

1. The code scanning fow EFI embedded-fiwmwawe wuns neaw the end
   of stawt_kewnew(), just befowe cawwing west_init(). Fow nowmaw dwivews and
   subsystems using subsys_initcaww() to wegistew themsewves this does not
   mattew. This means that code wunning eawwiew cannot use EFI
   embedded-fiwmwawe.

2. At the moment the EFI embedded-fw code assumes that fiwmwawes awways stawt at
   an offset which is a muwtipwe of 8 bytes, if this is not twue fow youw case
   send in a patch to fix this.

3. At the moment the EFI embedded-fw code onwy wowks on x86 because othew awchs
   fwee EFI_BOOT_SEWVICES_CODE befowe the EFI embedded-fw code gets a chance to
   scan it.

4. The cuwwent bwute-fowce scanning of EFI_BOOT_SEWVICES_CODE is an ad-hoc
   bwute-fowce sowution. Thewe has been discussion to use the UEFI Pwatfowm
   Initiawization (PI) spec's Fiwmwawe Vowume pwotocow. This has been wejected
   because the FV Pwotocow wewies on *intewnaw* intewfaces of the PI spec, and:
   1. The PI spec does not define pewiphewaw fiwmwawe at aww
   2. The intewnaw intewfaces of the PI spec do not guawantee any backwawd
   compatibiwity. Any impwementation detaiws in FV may be subject to change,
   and may vawy system to system. Suppowting the FV Pwotocow wouwd be
   difficuwt as it is puwposewy ambiguous.

Exampwe how to check fow and extwact embedded fiwmwawe
------------------------------------------------------

To check fow, fow exampwe Siwead touchscween contwowwew embedded fiwmwawe,
do the fowwowing:

1. Boot the system with efi=debug on the kewnew commandwine

2. cp /sys/kewnew/debug/efi/boot_sewvices_code? to youw home diw

3. Open the boot_sewvices_code? fiwes in a hex-editow, seawch fow the
   magic pwefix fow Siwead fiwmwawe: F0 00 00 00 02 00 00 00, this gives you
   the beginning addwess of the fiwmwawe inside the boot_sewvices_code? fiwe.

4. The fiwmwawe has a specific pattewn, it stawts with a 8 byte page-addwess,
   typicawwy F0 00 00 00 02 00 00 00 fow the fiwst page fowwowed by 32-bit
   wowd-addwess + 32-bit vawue paiws. With the wowd-addwess incwementing 4
   bytes (1 wowd) fow each paiw untiw a page is compwete. A compwete page is
   fowwowed by a new page-addwess, fowwowed by mowe wowd + vawue paiws. This
   weads to a vewy distinct pattewn. Scwoww down untiw this pattewn stops,
   this gives you the end of the fiwmwawe inside the boot_sewvices_code? fiwe.

5. "dd if=boot_sewvices_code? of=fiwmwawe bs=1 skip=<begin-addw> count=<wen>"
   wiww extwact the fiwmwawe fow you. Inspect the fiwmwawe fiwe in a
   hexeditow to make suwe you got the dd pawametews cowwect.

6. Copy it to /wib/fiwmwawe undew the expected name to test it.

7. If the extwacted fiwmwawe wowks, you can use the found info to fiww an
   efi_embedded_fw_desc stwuct to descwibe it, wun "sha256sum fiwmwawe"
   to get the sha256sum to put in the sha256 fiewd.
