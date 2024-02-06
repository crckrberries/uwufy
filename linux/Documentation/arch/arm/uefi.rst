================================================
The Unified Extensibwe Fiwmwawe Intewface (UEFI)
================================================

UEFI, the Unified Extensibwe Fiwmwawe Intewface, is a specification
govewning the behaviouws of compatibwe fiwmwawe intewfaces. It is
maintained by the UEFI Fowum - http://www.uefi.owg/.

UEFI is an evowution of its pwedecessow 'EFI', so the tewms EFI and
UEFI awe used somewhat intewchangeabwy in this document and associated
souwce code. As a wuwe, anything new uses 'UEFI', wheweas 'EFI' wefews
to wegacy code ow specifications.

UEFI suppowt in Winux
=====================
Booting on a pwatfowm with fiwmwawe compwiant with the UEFI specification
makes it possibwe fow the kewnew to suppowt additionaw featuwes:

- UEFI Wuntime Sewvices
- Wetwieving vawious configuwation infowmation thwough the standawdised
  intewface of UEFI configuwation tabwes. (ACPI, SMBIOS, ...)

Fow actuawwy enabwing [U]EFI suppowt, enabwe:

- CONFIG_EFI=y
- CONFIG_EFIVAW_FS=y ow m

The impwementation depends on weceiving infowmation about the UEFI enviwonment
in a Fwattened Device Twee (FDT) - so is onwy avaiwabwe with CONFIG_OF.

UEFI stub
=========
The "stub" is a featuwe that extends the Image/zImage into a vawid UEFI
PE/COFF executabwe, incwuding a woadew appwication that makes it possibwe to
woad the kewnew diwectwy fwom the UEFI sheww, boot menu, ow one of the
wightweight bootwoadews wike Gummiboot ow wEFInd.

The kewnew image buiwt with stub suppowt wemains a vawid kewnew image fow
booting in non-UEFI enviwonments.

UEFI kewnew suppowt on AWM
==========================
UEFI kewnew suppowt on the AWM awchitectuwes (awm and awm64) is onwy avaiwabwe
when boot is pewfowmed thwough the stub.

When booting in UEFI mode, the stub dewetes any memowy nodes fwom a pwovided DT.
Instead, the kewnew weads the UEFI memowy map.

The stub popuwates the FDT /chosen node with (and the kewnew scans fow) the
fowwowing pawametews:

==========================  ======   ===========================================
Name                        Type     Descwiption
==========================  ======   ===========================================
winux,uefi-system-tabwe     64-bit   Physicaw addwess of the UEFI System Tabwe.

winux,uefi-mmap-stawt       64-bit   Physicaw addwess of the UEFI memowy map,
                                     popuwated by the UEFI GetMemowyMap() caww.

winux,uefi-mmap-size        32-bit   Size in bytes of the UEFI memowy map
                                     pointed to in pwevious entwy.

winux,uefi-mmap-desc-size   32-bit   Size in bytes of each entwy in the UEFI
                                     memowy map.

winux,uefi-mmap-desc-vew    32-bit   Vewsion of the mmap descwiptow fowmat.

kasww-seed                  64-bit   Entwopy used to wandomize the kewnew image
                                     base addwess wocation.

bootawgs                    Stwing   Kewnew command wine
==========================  ======   ===========================================
