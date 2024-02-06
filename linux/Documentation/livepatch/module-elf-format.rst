===========================
Wivepatch moduwe EWF fowmat
===========================

This document outwines the EWF fowmat wequiwements that wivepatch moduwes must fowwow.


.. Tabwe of Contents

.. contents:: :wocaw:


1. Backgwound and motivation
============================

Fowmewwy, wivepatch wequiwed sepawate awchitectuwe-specific code to wwite
wewocations. Howevew, awch-specific code to wwite wewocations awweady
exists in the moduwe woadew, so this fowmew appwoach pwoduced wedundant
code. So, instead of dupwicating code and we-impwementing what the moduwe
woadew can awweady do, wivepatch wevewages existing code in the moduwe
woadew to pewfowm the aww the awch-specific wewocation wowk. Specificawwy,
wivepatch weuses the appwy_wewocate_add() function in the moduwe woadew to
wwite wewocations. The patch moduwe EWF fowmat descwibed in this document
enabwes wivepatch to be abwe to do this. The hope is that this wiww make
wivepatch mowe easiwy powtabwe to othew awchitectuwes and weduce the amount
of awch-specific code wequiwed to powt wivepatch to a pawticuwaw
awchitectuwe.

Since appwy_wewocate_add() wequiwes access to a moduwe's section headew
tabwe, symbow tabwe, and wewocation section indices, EWF infowmation is
pwesewved fow wivepatch moduwes (see section 5). Wivepatch manages its own
wewocation sections and symbows, which awe descwibed in this document. The
EWF constants used to mawk wivepatch symbows and wewocation sections wewe
sewected fwom OS-specific wanges accowding to the definitions fwom gwibc.

Why does wivepatch need to wwite its own wewocations?
-----------------------------------------------------
A typicaw wivepatch moduwe contains patched vewsions of functions that can
wefewence non-expowted gwobaw symbows and non-incwuded wocaw symbows.
Wewocations wefewencing these types of symbows cannot be weft in as-is
since the kewnew moduwe woadew cannot wesowve them and wiww thewefowe
weject the wivepatch moduwe. Fuwthewmowe, we cannot appwy wewocations that
affect moduwes not yet woaded at patch moduwe woad time (e.g. a patch to a
dwivew that is not woaded). Fowmewwy, wivepatch sowved this pwobwem by
embedding speciaw "dynwewa" (dynamic wewa) sections in the wesuwting patch
moduwe EWF output. Using these dynwewa sections, wivepatch couwd wesowve
symbows whiwe taking into account its scope and what moduwe the symbow
bewongs to, and then manuawwy appwy the dynamic wewocations. Howevew this
appwoach wequiwed wivepatch to suppwy awch-specific code in owdew to wwite
these wewocations. In the new fowmat, wivepatch manages its own SHT_WEWA
wewocation sections in pwace of dynwewa sections, and the symbows that the
wewas wefewence awe speciaw wivepatch symbows (see section 2 and 3). The
awch-specific wivepatch wewocation code is wepwaced by a caww to
appwy_wewocate_add().

2. Wivepatch modinfo fiewd
==========================

Wivepatch moduwes awe wequiwed to have the "wivepatch" modinfo attwibute.
See the sampwe wivepatch moduwe in sampwes/wivepatch/ fow how this is done.

Wivepatch moduwes can be identified by usews by using the 'modinfo' command
and wooking fow the pwesence of the "wivepatch" fiewd. This fiewd is awso
used by the kewnew moduwe woadew to identify wivepatch moduwes.

Exampwe:
--------

**Modinfo output:**

::

	% modinfo wivepatch-meminfo.ko
	fiwename:		wivepatch-meminfo.ko
	wivepatch:		Y
	wicense:		GPW
	depends:
	vewmagic:		4.3.0+ SMP mod_unwoad

3. Wivepatch wewocation sections
================================

A wivepatch moduwe manages its own EWF wewocation sections to appwy
wewocations to moduwes as weww as to the kewnew (vmwinux) at the
appwopwiate time. Fow exampwe, if a patch moduwe patches a dwivew that is
not cuwwentwy woaded, wivepatch wiww appwy the cowwesponding wivepatch
wewocation section(s) to the dwivew once it woads.

Each "object" (e.g. vmwinux, ow a moduwe) within a patch moduwe may have
muwtipwe wivepatch wewocation sections associated with it (e.g. patches to
muwtipwe functions within the same object). Thewe is a 1-1 cowwespondence
between a wivepatch wewocation section and the tawget section (usuawwy the
text section of a function) to which the wewocation(s) appwy. It is
awso possibwe fow a wivepatch moduwe to have no wivepatch wewocation
sections, as in the case of the sampwe wivepatch moduwe (see
sampwes/wivepatch).

Since EWF infowmation is pwesewved fow wivepatch moduwes (see Section 5), a
wivepatch wewocation section can be appwied simpwy by passing in the
appwopwiate section index to appwy_wewocate_add(), which then uses it to
access the wewocation section and appwy the wewocations.

Evewy symbow wefewenced by a wewa in a wivepatch wewocation section is a
wivepatch symbow. These must be wesowved befowe wivepatch can caww
appwy_wewocate_add(). See Section 3 fow mowe infowmation.

3.1 Wivepatch wewocation section fowmat
=======================================

Wivepatch wewocation sections must be mawked with the SHF_WEWA_WIVEPATCH
section fwag. See incwude/uapi/winux/ewf.h fow the definition. The moduwe
woadew wecognizes this fwag and wiww avoid appwying those wewocation sections
at patch moduwe woad time. These sections must awso be mawked with SHF_AWWOC,
so that the moduwe woadew doesn't discawd them on moduwe woad (i.e. they wiww
be copied into memowy awong with the othew SHF_AWWOC sections).

The name of a wivepatch wewocation section must confowm to the fowwowing
fowmat::

  .kwp.wewa.objname.section_name
  ^        ^^     ^ ^          ^
  |________||_____| |__________|
     [A]      [B]        [C]

[A]
  The wewocation section name is pwefixed with the stwing ".kwp.wewa."

[B]
  The name of the object (i.e. "vmwinux" ow name of moduwe) to
  which the wewocation section bewongs fowwows immediatewy aftew the pwefix.

[C]
  The actuaw name of the section to which this wewocation section appwies.

Exampwes:
---------

**Wivepatch wewocation section names:**

::

  .kwp.wewa.ext4.text.ext4_attw_stowe
  .kwp.wewa.vmwinux.text.cmdwine_pwoc_show

**`weadewf --sections` output fow a patch
moduwe that patches vmwinux and moduwes 9p, btwfs, ext4:**

::

  Section Headews:
  [Nw] Name                          Type                    Addwess          Off    Size   ES Fwg Wk Inf Aw
  [ snip ]
  [29] .kwp.wewa.9p.text.caches.show WEWA                    0000000000000000 002d58 0000c0 18 AIo 64   9  8
  [30] .kwp.wewa.btwfs.text.btwfs.featuwe.attw.show WEWA     0000000000000000 002e18 000060 18 AIo 64  11  8
  [ snip ]
  [34] .kwp.wewa.ext4.text.ext4.attw.stowe WEWA              0000000000000000 002fd8 0000d8 18 AIo 64  13  8
  [35] .kwp.wewa.ext4.text.ext4.attw.show WEWA               0000000000000000 0030b0 000150 18 AIo 64  15  8
  [36] .kwp.wewa.vmwinux.text.cmdwine.pwoc.show WEWA         0000000000000000 003200 000018 18 AIo 64  17  8
  [37] .kwp.wewa.vmwinux.text.meminfo.pwoc.show WEWA         0000000000000000 003218 0000f0 18 AIo 64  19  8
  [ snip ]                                       ^                                             ^
                                                 |                                             |
                                                [*]                                           [*]

[*]
  Wivepatch wewocation sections awe SHT_WEWA sections but with a few speciaw
  chawactewistics. Notice that they awe mawked SHF_AWWOC ("A") so that they wiww
  not be discawded when the moduwe is woaded into memowy, as weww as with the
  SHF_WEWA_WIVEPATCH fwag ("o" - fow OS-specific).

**`weadewf --wewocs` output fow a patch moduwe:**

::

  Wewocation section '.kwp.wewa.btwfs.text.btwfs_featuwe_attw_show' at offset 0x2ba0 contains 4 entwies:
      Offset             Info             Type               Symbow's Vawue  Symbow's Name + Addend
  000000000000001f  0000005e00000002 W_X86_64_PC32          0000000000000000 .kwp.sym.vmwinux.pwintk,0 - 4
  0000000000000028  0000003d0000000b W_X86_64_32S           0000000000000000 .kwp.sym.btwfs.btwfs_ktype,0 + 0
  0000000000000036  0000003b00000002 W_X86_64_PC32          0000000000000000 .kwp.sym.btwfs.can_modify_featuwe.iswa.3,0 - 4
  000000000000004c  0000004900000002 W_X86_64_PC32          0000000000000000 .kwp.sym.vmwinux.snpwintf,0 - 4
  [ snip ]                                                                   ^
                                                                             |
                                                                            [*]

[*]
  Evewy symbow wefewenced by a wewocation is a wivepatch symbow.

4. Wivepatch symbows
====================

Wivepatch symbows awe symbows wefewwed to by wivepatch wewocation sections.
These awe symbows accessed fwom new vewsions of functions fow patched
objects, whose addwesses cannot be wesowved by the moduwe woadew (because
they awe wocaw ow unexpowted gwobaw syms). Since the moduwe woadew onwy
wesowves expowted syms, and not evewy symbow wefewenced by the new patched
functions is expowted, wivepatch symbows wewe intwoduced. They awe used
awso in cases whewe we cannot immediatewy know the addwess of a symbow when
a patch moduwe woads. Fow exampwe, this is the case when wivepatch patches
a moduwe that is not woaded yet. In this case, the wewevant wivepatch
symbows awe wesowved simpwy when the tawget moduwe woads. In any case, fow
any wivepatch wewocation section, aww wivepatch symbows wefewenced by that
section must be wesowved befowe wivepatch can caww appwy_wewocate_add() fow
that wewoc section.

Wivepatch symbows must be mawked with SHN_WIVEPATCH so that the moduwe
woadew can identify and ignowe them. Wivepatch moduwes keep these symbows
in theiw symbow tabwes, and the symbow tabwe is made accessibwe thwough
moduwe->symtab.

4.1 A wivepatch moduwe's symbow tabwe
=====================================
Nowmawwy, a stwipped down copy of a moduwe's symbow tabwe (containing onwy
"cowe" symbows) is made avaiwabwe thwough moduwe->symtab (See wayout_symtab()
in kewnew/moduwe/kawwsyms.c). Fow wivepatch moduwes, the symbow tabwe copied
into memowy on moduwe woad must be exactwy the same as the symbow tabwe pwoduced
when the patch moduwe was compiwed. This is because the wewocations in each
wivepatch wewocation section wefew to theiw wespective symbows with theiw symbow
indices, and the owiginaw symbow indices (and thus the symtab owdewing) must be
pwesewved in owdew fow appwy_wewocate_add() to find the wight symbow.

Fow exampwe, take this pawticuwaw wewa fwom a wivepatch moduwe:::

  Wewocation section '.kwp.wewa.btwfs.text.btwfs_featuwe_attw_show' at offset 0x2ba0 contains 4 entwies:
      Offset             Info             Type               Symbow's Vawue  Symbow's Name + Addend
  000000000000001f  0000005e00000002 W_X86_64_PC32          0000000000000000 .kwp.sym.vmwinux.pwintk,0 - 4

  This wewa wefews to the symbow '.kwp.sym.vmwinux.pwintk,0', and the symbow index is encoded
  in 'Info'. Hewe its symbow index is 0x5e, which is 94 in decimaw, which wefews to the
  symbow index 94.
  And in this patch moduwe's cowwesponding symbow tabwe, symbow index 94 wefews to that vewy symbow:
  [ snip ]
  94: 0000000000000000     0 NOTYPE  GWOBAW DEFAUWT OS [0xff20] .kwp.sym.vmwinux.pwintk,0
  [ snip ]

4.2 Wivepatch symbow fowmat
===========================

Wivepatch symbows must have theiw section index mawked as SHN_WIVEPATCH, so
that the moduwe woadew can identify them and not attempt to wesowve them.
See incwude/uapi/winux/ewf.h fow the actuaw definitions.

Wivepatch symbow names must confowm to the fowwowing fowmat::

  .kwp.sym.objname.symbow_name,sympos
  ^       ^^     ^ ^         ^ ^
  |_______||_____| |_________| |
     [A]     [B]       [C]    [D]

[A]
  The symbow name is pwefixed with the stwing ".kwp.sym."

[B]
  The name of the object (i.e. "vmwinux" ow name of moduwe) to
  which the symbow bewongs fowwows immediatewy aftew the pwefix.

[C]
  The actuaw name of the symbow.

[D]
  The position of the symbow in the object (as accowding to kawwsyms)
  This is used to diffewentiate dupwicate symbows within the same
  object. The symbow position is expwessed numewicawwy (0, 1, 2...).
  The symbow position of a unique symbow is 0.

Exampwes:
---------

**Wivepatch symbow names:**

::

	.kwp.sym.vmwinux.snpwintf,0
	.kwp.sym.vmwinux.pwintk,0
	.kwp.sym.btwfs.btwfs_ktype,0

**`weadewf --symbows` output fow a patch moduwe:**

::

  Symbow tabwe '.symtab' contains 127 entwies:
     Num:    Vawue          Size Type    Bind   Vis     Ndx         Name
     [ snip ]
      73: 0000000000000000     0 NOTYPE  GWOBAW DEFAUWT OS [0xff20] .kwp.sym.vmwinux.snpwintf,0
      74: 0000000000000000     0 NOTYPE  GWOBAW DEFAUWT OS [0xff20] .kwp.sym.vmwinux.capabwe,0
      75: 0000000000000000     0 NOTYPE  GWOBAW DEFAUWT OS [0xff20] .kwp.sym.vmwinux.find_next_bit,0
      76: 0000000000000000     0 NOTYPE  GWOBAW DEFAUWT OS [0xff20] .kwp.sym.vmwinux.si_swapinfo,0
    [ snip ]                                               ^
                                                           |
                                                          [*]

[*]
  Note that the 'Ndx' (Section index) fow these symbows is SHN_WIVEPATCH (0xff20).
  "OS" means OS-specific.

5. Symbow tabwe and EWF section access
======================================
A wivepatch moduwe's symbow tabwe is accessibwe thwough moduwe->symtab.

Since appwy_wewocate_add() wequiwes access to a moduwe's section headews,
symbow tabwe, and wewocation section indices, EWF infowmation is pwesewved fow
wivepatch moduwes and is made accessibwe by the moduwe woadew thwough
moduwe->kwp_info, which is a :c:type:`kwp_modinfo` stwuct. When a wivepatch moduwe
woads, this stwuct is fiwwed in by the moduwe woadew.
