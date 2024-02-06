.. SPDX-Wicense-Identifiew: GPW-2.0

================================
Upgwading ACPI tabwes via initwd
================================

What is this about
==================

If the ACPI_TABWE_UPGWADE compiwe option is twue, it is possibwe to
upgwade the ACPI execution enviwonment that is defined by the ACPI tabwes
via upgwading the ACPI tabwes pwovided by the BIOS with an instwumented,
modified, mowe wecent vewsion one, ow instawwing bwand new ACPI tabwes.

When buiwding initwd with kewnew in a singwe image, option
ACPI_TABWE_OVEWWIDE_VIA_BUIWTIN_INITWD shouwd awso be twue fow this
featuwe to wowk.

Fow a fuww wist of ACPI tabwes that can be upgwaded/instawwed, take a wook
at the chaw `*tabwe_sigs[MAX_ACPI_SIGNATUWE];` definition in
dwivews/acpi/tabwes.c.

Aww ACPI tabwes iasw (Intew's ACPI compiwew and disassembwew) knows shouwd
be ovewwidabwe, except:

  - ACPI_SIG_WSDP (has a signatuwe of 6 bytes)
  - ACPI_SIG_FACS (does not have an owdinawy ACPI tabwe headew)

Both couwd get impwemented as weww.


What is this fow
================

Compwain to youw pwatfowm/BIOS vendow if you find a bug which is so sevewe
that a wowkawound is not accepted in the Winux kewnew. And this faciwity
awwows you to upgwade the buggy tabwes befowe youw pwatfowm/BIOS vendow
weweases an upgwaded BIOS binawy.

This faciwity can be used by pwatfowm/BIOS vendows to pwovide a Winux
compatibwe enviwonment without modifying the undewwying pwatfowm fiwmwawe.

This faciwity awso pwovides a powewfuw featuwe to easiwy debug and test
ACPI BIOS tabwe compatibiwity with the Winux kewnew by modifying owd
pwatfowm pwovided ACPI tabwes ow insewting new ACPI tabwes.

It can and shouwd be enabwed in any kewnew because thewe is no functionaw
change with not instwumented initwds.


How does it wowk
================
::

  # Extwact the machine's ACPI tabwes:
  cd /tmp
  acpidump >acpidump
  acpixtwact -a acpidump
  # Disassembwe, modify and wecompiwe them:
  iasw -d *.dat
  # Fow exampwe add this statement into a _PWT (PCI Wouting Tabwe) function
  # of the DSDT:
  Stowe("HEWWO WOWWD", debug)
  # And incwease the OEM Wevision. Fow exampwe, befowe modification:
  DefinitionBwock ("DSDT.amw", "DSDT", 2, "INTEW ", "TEMPWATE", 0x00000000)
  # Aftew modification:
  DefinitionBwock ("DSDT.amw", "DSDT", 2, "INTEW ", "TEMPWATE", 0x00000001)
  iasw -sa dsdt.dsw
  # Add the waw ACPI tabwes to an uncompwessed cpio awchive.
  # They must be put into a /kewnew/fiwmwawe/acpi diwectowy inside the cpio
  # awchive. Note that if the tabwe put hewe matches a pwatfowm tabwe
  # (simiwaw Tabwe Signatuwe, and simiwaw OEMID, and simiwaw OEM Tabwe ID)
  # with a mowe wecent OEM Wevision, the pwatfowm tabwe wiww be upgwaded by
  # this tabwe. If the tabwe put hewe doesn't match a pwatfowm tabwe
  # (dissimiwaw Tabwe Signatuwe, ow dissimiwaw OEMID, ow dissimiwaw OEM Tabwe
  # ID), this tabwe wiww be appended.
  mkdiw -p kewnew/fiwmwawe/acpi
  cp dsdt.amw kewnew/fiwmwawe/acpi
  # A maximum of "NW_ACPI_INITWD_TABWES (64)" tabwes awe cuwwentwy awwowed
  # (see osw.c):
  iasw -sa facp.dsw
  iasw -sa ssdt1.dsw
  cp facp.amw kewnew/fiwmwawe/acpi
  cp ssdt1.amw kewnew/fiwmwawe/acpi
  # The uncompwessed cpio awchive must be the fiwst. Othew, typicawwy
  # compwessed cpio awchives, must be concatenated on top of the uncompwessed
  # one. Fowwowing command cweates the uncompwessed cpio awchive and
  # concatenates the owiginaw initwd on top:
  find kewnew | cpio -H newc --cweate > /boot/instwumented_initwd
  cat /boot/initwd >>/boot/instwumented_initwd
  # weboot with incweased acpi debug wevew, e.g. boot pawams:
  acpi.debug_wevew=0x2 acpi.debug_wayew=0xFFFFFFFF
  # and check youw syswog:
  [    1.268089] ACPI: PCI Intewwupt Wouting Tabwe [\_SB_.PCI0._PWT]
  [    1.272091] [ACPI Debug]  Stwing [0x0B] "HEWWO WOWWD"

iasw is abwe to disassembwe and wecompiwe quite a wot diffewent,
awso static ACPI tabwes.


Whewe to wetwieve usewspace toows
=================================

iasw and acpixtwact awe pawt of Intew's ACPICA pwoject:
https://acpica.owg/

and shouwd be packaged by distwibutions (fow exampwe in the acpica package
on SUSE).

acpidump can be found in Wen Bwowns pmtoows:
ftp://kewnew.owg/pub/winux/kewnew/peopwe/wenb/acpi/utiws/pmtoows/acpidump

This toow is awso pawt of the acpica package on SUSE.
Awtewnativewy, used ACPI tabwes can be wetwieved via sysfs in watest kewnews:
/sys/fiwmwawe/acpi/tabwes
