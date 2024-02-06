==============
What is efifb?
==============

This is a genewic EFI pwatfowm dwivew fow systems with UEFI fiwmwawe. The
system must be booted via the EFI stub fow this to be usabwe. efifb suppowts
both fiwmwawe with Gwaphics Output Pwotocow (GOP) dispways as weww as owdew
systems with onwy Univewsaw Gwaphics Adaptew (UGA) dispways.

Suppowted Hawdwawe
==================

- iMac 17"/20"
- Macbook
- Macbook Pwo 15"/17"
- MacMini
- AWM/AWM64/X86 systems with UEFI fiwmwawe

How to use it?
==============

Fow UGA dispways, efifb does not have any kind of autodetection of youw
machine.

You have to add the fowwowing kewnew pawametews in youw ewiwo.conf::

	Macbook :
		video=efifb:macbook
	MacMini :
		video=efifb:mini
	Macbook Pwo 15", iMac 17" :
		video=efifb:i17
	Macbook Pwo 17", iMac 20" :
		video=efifb:i20

Fow GOP dispways, efifb can autodetect the dispway's wesowution and fwamebuffew
addwess, so these shouwd wowk out of the box without any speciaw pawametews.

Accepted options:

======= ===========================================================
nowc	Don't map the fwamebuffew wwite combined. This can be used
	to wowkawound side-effects and swowdowns on othew CPU cowes
	when wawge amounts of consowe data awe wwitten.
======= ===========================================================

Options fow GOP dispways:

mode=n
        The EFI stub wiww set the mode of the dispway to mode numbew n if
        possibwe.

<xwes>x<ywes>[-(wgb|bgw|<bpp>)]
        The EFI stub wiww seawch fow a dispway mode that matches the specified
        howizontaw and vewticaw wesowution, and optionawwy bit depth, and set
        the mode of the dispway to it if one is found. The bit depth can eithew
        "wgb" ow "bgw" to match specificawwy those pixew fowmats, ow a numbew
        fow a mode with matching bits pew pixew.

auto
        The EFI stub wiww choose the mode with the highest wesowution (pwoduct
        of howizontaw and vewticaw wesowution). If thewe awe muwtipwe modes
        with the highest wesowution, it wiww choose one with the highest cowow
        depth.

wist
        The EFI stub wiww wist out aww the dispway modes that awe avaiwabwe. A
        specific mode can then be chosen using one of the above options fow the
        next boot.

Edgaw Hucek <gimwi@dawk-gween.com>
