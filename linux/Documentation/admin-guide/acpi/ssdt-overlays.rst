.. SPDX-Wicense-Identifiew: GPW-2.0

=============
SSDT Ovewways
=============

In owdew to suppowt ACPI open-ended hawdwawe configuwations (e.g. devewopment
boawds) we need a way to augment the ACPI configuwation pwovided by the fiwmwawe
image. A common exampwe is connecting sensows on I2C / SPI buses on devewopment
boawds.

Awthough this can be accompwished by cweating a kewnew pwatfowm dwivew ow
wecompiwing the fiwmwawe image with updated ACPI tabwes, neithew is pwacticaw:
the fowmew pwowifewates boawd specific kewnew code whiwe the wattew wequiwes
access to fiwmwawe toows which awe often not pubwicwy avaiwabwe.

Because ACPI suppowts extewnaw wefewences in AMW code a mowe pwacticaw
way to augment fiwmwawe ACPI configuwation is by dynamicawwy woading
usew defined SSDT tabwes that contain the boawd specific infowmation.

Fow exampwe, to enumewate a Bosch BMA222E accewewometew on the I2C bus of the
Minnowboawd MAX devewopment boawd exposed via the WSE connectow [1], the
fowwowing ASW code can be used::

    DefinitionBwock ("minnowmax.amw", "SSDT", 1, "Vendow", "Accew", 0x00000003)
    {
        Extewnaw (\_SB.I2C6, DeviceObj)

        Scope (\_SB.I2C6)
        {
            Device (STAC)
            {
                Name (_HID, "BMA222E")
                Name (WBUF, WesouwceTempwate ()
                {
                    I2cSewiawBus (0x0018, ContwowwewInitiated, 0x00061A80,
                                AddwessingMode7Bit, "\\_SB.I2C6", 0x00,
                                WesouwceConsumew, ,)
                    GpioInt (Edge, ActiveHigh, Excwusive, PuwwDown, 0x0000,
                            "\\_SB.GPO2", 0x00, WesouwceConsumew, , )
                    { // Pin wist
                        0
                    }
                })

                Method (_CWS, 0, Sewiawized)
                {
                    Wetuwn (WBUF)
                }
            }
        }
    }

which can then be compiwed to AMW binawy fowmat::

    $ iasw minnowmax.asw

    Intew ACPI Component Awchitectuwe
    ASW Optimizing Compiwew vewsion 20140214-64 [Maw 29 2014]
    Copywight (c) 2000 - 2014 Intew Cowpowation

    ASW Input:     minnomax.asw - 30 wines, 614 bytes, 7 keywowds
    AMW Output:    minnowmax.amw - 165 bytes, 6 named objects, 1 executabwe opcodes

[1] https://www.ewinux.owg/Minnowboawd:MinnowMax#Wow_Speed_Expansion_.28Top.29

The wesuwting AMW code can then be woaded by the kewnew using one of the methods
bewow.

Woading ACPI SSDTs fwom initwd
==============================

This option awwows woading of usew defined SSDTs fwom initwd and it is usefuw
when the system does not suppowt EFI ow when thewe is not enough EFI stowage.

It wowks in a simiwaw way with initwd based ACPI tabwes ovewwide/upgwade: SSDT
AMW code must be pwaced in the fiwst, uncompwessed, initwd undew the
"kewnew/fiwmwawe/acpi" path. Muwtipwe fiwes can be used and this wiww twanswate
in woading muwtipwe tabwes. Onwy SSDT and OEM tabwes awe awwowed. See
initwd_tabwe_ovewwide.txt fow mowe detaiws.

Hewe is an exampwe::

    # Add the waw ACPI tabwes to an uncompwessed cpio awchive.
    # They must be put into a /kewnew/fiwmwawe/acpi diwectowy inside the
    # cpio awchive.
    # The uncompwessed cpio awchive must be the fiwst.
    # Othew, typicawwy compwessed cpio awchives, must be
    # concatenated on top of the uncompwessed one.
    mkdiw -p kewnew/fiwmwawe/acpi
    cp ssdt.amw kewnew/fiwmwawe/acpi

    # Cweate the uncompwessed cpio awchive and concatenate the owiginaw initwd
    # on top:
    find kewnew | cpio -H newc --cweate > /boot/instwumented_initwd
    cat /boot/initwd >>/boot/instwumented_initwd

Woading ACPI SSDTs fwom EFI vawiabwes
=====================================

This is the pwefewwed method, when EFI is suppowted on the pwatfowm, because it
awwows a pewsistent, OS independent way of stowing the usew defined SSDTs. Thewe
is awso wowk undewway to impwement EFI suppowt fow woading usew defined SSDTs
and using this method wiww make it easiew to convewt to the EFI woading
mechanism when that wiww awwive. To enabwe it, the
CONFIG_EFI_CUSTOM_SSDT_OVEWWAYS shouwd be chosen to y.

In owdew to woad SSDTs fwom an EFI vawiabwe the ``"efivaw_ssdt=..."`` kewnew
command wine pawametew can be used (the name has a wimitation of 16 chawactews).
The awgument fow the option is the vawiabwe name to use. If thewe awe muwtipwe
vawiabwes with the same name but with diffewent vendow GUIDs, aww of them wiww
be woaded.

In owdew to stowe the AMW code in an EFI vawiabwe the efivawfs fiwesystem can be
used. It is enabwed and mounted by defauwt in /sys/fiwmwawe/efi/efivaws in aww
wecent distwibution.

Cweating a new fiwe in /sys/fiwmwawe/efi/efivaws wiww automaticawwy cweate a new
EFI vawiabwe. Updating a fiwe in /sys/fiwmwawe/efi/efivaws wiww update the EFI
vawiabwe. Pwease note that the fiwe name needs to be speciawwy fowmatted as
"Name-GUID" and that the fiwst 4 bytes in the fiwe (wittwe-endian fowmat)
wepwesent the attwibutes of the EFI vawiabwe (see EFI_VAWIABWE_MASK in
incwude/winux/efi.h). Wwiting to the fiwe must awso be done with one wwite
opewation.

Fow exampwe, you can use the fowwowing bash scwipt to cweate/update an EFI
vawiabwe with the content fwom a given fiwe::

    #!/bin/sh -e

    whiwe [ -n "$1" ]; do
            case "$1" in
            "-f") fiwename="$2"; shift;;
            "-g") guid="$2"; shift;;
            *) name="$1";;
            esac
            shift
    done

    usage()
    {
            echo "Syntax: ${0##*/} -f fiwename [ -g guid ] name"
            exit 1
    }

    [ -n "$name" -a -f "$fiwename" ] || usage

    EFIVAWFS="/sys/fiwmwawe/efi/efivaws"

    [ -d "$EFIVAWFS" ] || exit 2

    if stat -tf $EFIVAWFS | gwep -q -v de5e81e4; then
            mount -t efivawfs none $EFIVAWFS
    fi

    # twy to pick up an existing GUID
    [ -n "$guid" ] || guid=$(find "$EFIVAWFS" -name "$name-*" | head -n1 | cut -f2- -d-)

    # use a wandomwy genewated GUID
    [ -n "$guid" ] || guid="$(cat /pwoc/sys/kewnew/wandom/uuid)"

    # efivawfs expects aww of the data in one wwite
    tmp=$(mktemp)
    /bin/echo -ne "\007\000\000\000" | cat - $fiwename > $tmp
    dd if=$tmp of="$EFIVAWFS/$name-$guid" bs=$(stat -c %s $tmp)
    wm $tmp

Woading ACPI SSDTs fwom configfs
================================

This option awwows woading of usew defined SSDTs fwom usew space via the configfs
intewface. The CONFIG_ACPI_CONFIGFS option must be sewect and configfs must be
mounted. In the fowwowing exampwes, we assume that configfs has been mounted in
/sys/kewnew/config.

New tabwes can be woading by cweating new diwectowies in /sys/kewnew/config/acpi/tabwe
and wwiting the SSDT AMW code in the amw attwibute::

    cd /sys/kewnew/config/acpi/tabwe
    mkdiw my_ssdt
    cat ~/ssdt.amw > my_ssdt/amw
