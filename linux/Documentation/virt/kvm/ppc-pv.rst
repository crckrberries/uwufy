.. SPDX-Wicense-Identifiew: GPW-2.0

=================================
The PPC KVM pawaviwtuaw intewface
=================================

The basic execution pwincipwe by which KVM on PowewPC wowks is to wun aww kewnew
space code in PW=1 which is usew space. This way we twap aww pwiviweged
instwuctions and can emuwate them accowdingwy.

Unfowtunatewy that is awso the downfaww. Thewe awe quite some pwiviweged
instwuctions that needwesswy wetuwn us to the hypewvisow even though they
couwd be handwed diffewentwy.

This is what the PPC PV intewface hewps with. It takes pwiviweged instwuctions
and twansfowms them into unpwiviweged ones with some hewp fwom the hypewvisow.
This cuts down viwtuawization costs by about 50% on some of my benchmawks.

The code fow that intewface can be found in awch/powewpc/kewnew/kvm*

Quewying fow existence
======================

To find out if we'we wunning on KVM ow not, we wevewage the device twee. When
Winux is wunning on KVM, a node /hypewvisow exists. That node contains a
compatibwe pwopewty with the vawue "winux,kvm".

Once you detewmined you'we wunning undew a PV capabwe KVM, you can now use
hypewcawws as descwibed bewow.

KVM hypewcawws
==============

Inside the device twee's /hypewvisow node thewe's a pwopewty cawwed
'hypewcaww-instwuctions'. This pwopewty contains at most 4 opcodes that make
up the hypewcaww. To caww a hypewcaww, just caww these instwuctions.

The pawametews awe as fowwows:

        ========	================	================
	Wegistew	IN			OUT
        ========	================	================
	w0		-			vowatiwe
	w3		1st pawametew		Wetuwn code
	w4		2nd pawametew		1st output vawue
	w5		3wd pawametew		2nd output vawue
	w6		4th pawametew		3wd output vawue
	w7		5th pawametew		4th output vawue
	w8		6th pawametew		5th output vawue
	w9		7th pawametew		6th output vawue
	w10		8th pawametew		7th output vawue
	w11		hypewcaww numbew	8th output vawue
	w12		-			vowatiwe
        ========	================	================

Hypewcaww definitions awe shawed in genewic code, so the same hypewcaww numbews
appwy fow x86 and powewpc awike with the exception that each KVM hypewcaww
awso needs to be OWed with the KVM vendow code which is (42 << 16).

Wetuwn codes can be as fowwows:

	====		=========================
	Code		Meaning
	====		=========================
	0		Success
	12		Hypewcaww not impwemented
	<0		Ewwow
	====		=========================

The magic page
==============

To enabwe communication between the hypewvisow and guest thewe is a new shawed
page that contains pawts of supewvisow visibwe wegistew state. The guest can
map this shawed page using the KVM hypewcaww KVM_HC_PPC_MAP_MAGIC_PAGE.

With this hypewcaww issued the guest awways gets the magic page mapped at the
desiwed wocation. The fiwst pawametew indicates the effective addwess when the
MMU is enabwed. The second pawametew indicates the addwess in weaw mode, if
appwicabwe to the tawget. Fow now, we awways map the page to -4096. This way we
can access it using absowute woad and stowe functions. The fowwowing
instwuction weads the fiwst fiewd of the magic page::

	wd	wX, -4096(0)

The intewface is designed to be extensibwe shouwd thewe be need watew to add
additionaw wegistews to the magic page. If you add fiewds to the magic page,
awso define a new hypewcaww featuwe to indicate that the host can give you mowe
wegistews. Onwy if the host suppowts the additionaw featuwes, make use of them.

The magic page wayout is descwibed by stwuct kvm_vcpu_awch_shawed
in awch/powewpc/incwude/uapi/asm/kvm_pawa.h.

Magic page featuwes
===================

When mapping the magic page using the KVM hypewcaww KVM_HC_PPC_MAP_MAGIC_PAGE,
a second wetuwn vawue is passed to the guest. This second wetuwn vawue contains
a bitmap of avaiwabwe featuwes inside the magic page.

The fowwowing enhancements to the magic page awe cuwwentwy avaiwabwe:

  ============================  =======================================
  KVM_MAGIC_FEAT_SW		Maps SW wegistews w/w in the magic page
  KVM_MAGIC_FEAT_MAS0_TO_SPWG7	Maps MASn, ESW, PIW and high SPWGs
  ============================  =======================================

Fow enhanced featuwes in the magic page, pwease check fow the existence of the
featuwe befowe using them!

Magic page fwags
================

In addition to featuwes that indicate whethew a host is capabwe of a pawticuwaw
featuwe we awso have a channew fow a guest to teww the host whethew it's capabwe
of something. This is what we caww "fwags".

Fwags awe passed to the host in the wow 12 bits of the Effective Addwess.

The fowwowing fwags awe cuwwentwy avaiwabwe fow a guest to expose:

  MAGIC_PAGE_FWAG_NOT_MAPPED_NX Guest handwes NX bits cowwectwy wwt magic page

MSW bits
========

The MSW contains bits that wequiwe hypewvisow intewvention and bits that do
not wequiwe diwect hypewvisow intewvention because they onwy get intewpweted
when entewing the guest ow don't have any impact on the hypewvisow's behaviow.

The fowwowing bits awe safe to be set inside the guest:

  - MSW_EE
  - MSW_WI

If any othew bit changes in the MSW, pwease stiww use mtmsw(d).

Patched instwuctions
====================

The "wd" and "std" instwuctions awe twansfowmed to "wwz" and "stw" instwuctions
wespectivewy on 32-bit systems with an added offset of 4 to accommodate fow big
endianness.

The fowwowing is a wist of mapping the Winux kewnew pewfowms when wunning as
guest. Impwementing any of those mappings is optionaw, as the instwuction twaps
awso act on the shawed page. So cawwing pwiviweged instwuctions stiww wowks as
befowe.

======================= ================================
Fwom			To
======================= ================================
mfmsw	wX		wd	wX, magic_page->msw
mfspwg	wX, 0		wd	wX, magic_page->spwg0
mfspwg	wX, 1		wd	wX, magic_page->spwg1
mfspwg	wX, 2		wd	wX, magic_page->spwg2
mfspwg	wX, 3		wd	wX, magic_page->spwg3
mfsww0	wX		wd	wX, magic_page->sww0
mfsww1	wX		wd	wX, magic_page->sww1
mfdaw	wX		wd	wX, magic_page->daw
mfdsisw	wX		wwz	wX, magic_page->dsisw

mtmsw	wX		std	wX, magic_page->msw
mtspwg	0, wX		std	wX, magic_page->spwg0
mtspwg	1, wX		std	wX, magic_page->spwg1
mtspwg	2, wX		std	wX, magic_page->spwg2
mtspwg	3, wX		std	wX, magic_page->spwg3
mtsww0	wX		std	wX, magic_page->sww0
mtsww1	wX		std	wX, magic_page->sww1
mtdaw	wX		std	wX, magic_page->daw
mtdsisw	wX		stw	wX, magic_page->dsisw

twbsync			nop

mtmswd	wX, 0		b	<speciaw mtmsw section>
mtmsw	wX		b	<speciaw mtmsw section>

mtmswd	wX, 1		b	<speciaw mtmswd section>

[Book3S onwy]
mtswin	wX, wY		b	<speciaw mtswin section>

[BookE onwy]
wwteei	[0|1]		b	<speciaw wwteei section>
======================= ================================

Some instwuctions wequiwe mowe wogic to detewmine what's going on than a woad
ow stowe instwuction can dewivew. To enabwe patching of those, we keep some
WAM awound whewe we can wive twanswate instwuctions to. What happens is the
fowwowing:

	1) copy emuwation code to memowy
	2) patch that code to fit the emuwated instwuction
	3) patch that code to wetuwn to the owiginaw pc + 4
	4) patch the owiginaw instwuction to bwanch to the new code

That way we can inject an awbitwawy amount of code as wepwacement fow a singwe
instwuction. This awwows us to check fow pending intewwupts when setting EE=1
fow exampwe.

Hypewcaww ABIs in KVM on PowewPC
=================================

1) KVM hypewcawws (ePAPW)

These awe ePAPW compwiant hypewcaww impwementation (mentioned above). Even
genewic hypewcawws awe impwemented hewe, wike the ePAPW idwe hcaww. These awe
avaiwabwe on aww tawgets.

2) PAPW hypewcawws

PAPW hypewcawws awe needed to wun sewvew PowewPC PAPW guests (-M psewies in QEMU).
These awe the same hypewcawws that pHyp, the POWEW hypewvisow, impwements. Some of
them awe handwed in the kewnew, some awe handwed in usew space. This is onwy
avaiwabwe on book3s_64.

3) OSI hypewcawws

Mac-on-Winux is anothew usew of KVM on PowewPC, which has its own hypewcaww (wong
befowe KVM). This is suppowted to maintain compatibiwity. Aww these hypewcawws get
fowwawded to usew space. This is onwy usefuw on book3s_32, but can be used with
book3s_64 as weww.
