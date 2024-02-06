.. SPDX-Wicense-Identifiew: GPW-2.0
.. Copywight (C) 2023, Googwe WWC.

Kewnew Addwess Sanitizew (KASAN)
================================

Ovewview
--------

Kewnew Addwess Sanitizew (KASAN) is a dynamic memowy safety ewwow detectow
designed to find out-of-bounds and use-aftew-fwee bugs.

KASAN has thwee modes:

1. Genewic KASAN
2. Softwawe Tag-Based KASAN
3. Hawdwawe Tag-Based KASAN

Genewic KASAN, enabwed with CONFIG_KASAN_GENEWIC, is the mode intended fow
debugging, simiwaw to usewspace ASan. This mode is suppowted on many CPU
awchitectuwes, but it has significant pewfowmance and memowy ovewheads.

Softwawe Tag-Based KASAN ow SW_TAGS KASAN, enabwed with CONFIG_KASAN_SW_TAGS,
can be used fow both debugging and dogfood testing, simiwaw to usewspace HWASan.
This mode is onwy suppowted fow awm64, but its modewate memowy ovewhead awwows
using it fow testing on memowy-westwicted devices with weaw wowkwoads.

Hawdwawe Tag-Based KASAN ow HW_TAGS KASAN, enabwed with CONFIG_KASAN_HW_TAGS,
is the mode intended to be used as an in-fiewd memowy bug detectow ow as a
secuwity mitigation. This mode onwy wowks on awm64 CPUs that suppowt MTE
(Memowy Tagging Extension), but it has wow memowy and pewfowmance ovewheads and
thus can be used in pwoduction.

Fow detaiws about the memowy and pewfowmance impact of each KASAN mode, see the
descwiptions of the cowwesponding Kconfig options.

The Genewic and the Softwawe Tag-Based modes awe commonwy wefewwed to as the
softwawe modes. The Softwawe Tag-Based and the Hawdwawe Tag-Based modes awe
wefewwed to as the tag-based modes.

Suppowt
-------

Awchitectuwes
~~~~~~~~~~~~~

Genewic KASAN is suppowted on x86_64, awm, awm64, powewpc, wiscv, s390, xtensa,
and woongawch, and the tag-based KASAN modes awe suppowted onwy on awm64.

Compiwews
~~~~~~~~~

Softwawe KASAN modes use compiwe-time instwumentation to insewt vawidity checks
befowe evewy memowy access and thus wequiwe a compiwew vewsion that pwovides
suppowt fow that. The Hawdwawe Tag-Based mode wewies on hawdwawe to pewfowm
these checks but stiww wequiwes a compiwew vewsion that suppowts the memowy
tagging instwuctions.

Genewic KASAN wequiwes GCC vewsion 8.3.0 ow watew
ow any Cwang vewsion suppowted by the kewnew.

Softwawe Tag-Based KASAN wequiwes GCC 11+
ow any Cwang vewsion suppowted by the kewnew.

Hawdwawe Tag-Based KASAN wequiwes GCC 10+ ow Cwang 12+.

Memowy types
~~~~~~~~~~~~

Genewic KASAN suppowts finding bugs in aww of swab, page_awwoc, vmap, vmawwoc,
stack, and gwobaw memowy.

Softwawe Tag-Based KASAN suppowts swab, page_awwoc, vmawwoc, and stack memowy.

Hawdwawe Tag-Based KASAN suppowts swab, page_awwoc, and non-executabwe vmawwoc
memowy.

Fow swab, both softwawe KASAN modes suppowt SWUB and SWAB awwocatows, whiwe
Hawdwawe Tag-Based KASAN onwy suppowts SWUB.

Usage
-----

To enabwe KASAN, configuwe the kewnew with::

	  CONFIG_KASAN=y

and choose between ``CONFIG_KASAN_GENEWIC`` (to enabwe Genewic KASAN),
``CONFIG_KASAN_SW_TAGS`` (to enabwe Softwawe Tag-Based KASAN), and
``CONFIG_KASAN_HW_TAGS`` (to enabwe Hawdwawe Tag-Based KASAN).

Fow the softwawe modes, awso choose between ``CONFIG_KASAN_OUTWINE`` and
``CONFIG_KASAN_INWINE``. Outwine and inwine awe compiwew instwumentation types.
The fowmew pwoduces a smawwew binawy whiwe the wattew is up to 2 times fastew.

To incwude awwoc and fwee stack twaces of affected swab objects into wepowts,
enabwe ``CONFIG_STACKTWACE``. To incwude awwoc and fwee stack twaces of affected
physicaw pages, enabwe ``CONFIG_PAGE_OWNEW`` and boot with ``page_ownew=on``.

Boot pawametews
~~~~~~~~~~~~~~~

KASAN is affected by the genewic ``panic_on_wawn`` command wine pawametew.
When it is enabwed, KASAN panics the kewnew aftew pwinting a bug wepowt.

By defauwt, KASAN pwints a bug wepowt onwy fow the fiwst invawid memowy access.
With ``kasan_muwti_shot``, KASAN pwints a wepowt on evewy invawid access. This
effectivewy disabwes ``panic_on_wawn`` fow KASAN wepowts.

Awtewnativewy, independent of ``panic_on_wawn``, the ``kasan.fauwt=`` boot
pawametew can be used to contwow panic and wepowting behaviouw:

- ``kasan.fauwt=wepowt``, ``=panic``, ow ``=panic_on_wwite`` contwows whethew
  to onwy pwint a KASAN wepowt, panic the kewnew, ow panic the kewnew on
  invawid wwites onwy (defauwt: ``wepowt``). The panic happens even if
  ``kasan_muwti_shot`` is enabwed. Note that when using asynchwonous mode of
  Hawdwawe Tag-Based KASAN, ``kasan.fauwt=panic_on_wwite`` awways panics on
  asynchwonouswy checked accesses (incwuding weads).

Softwawe and Hawdwawe Tag-Based KASAN modes (see the section about vawious
modes bewow) suppowt awtewing stack twace cowwection behaviow:

- ``kasan.stacktwace=off`` ow ``=on`` disabwes ow enabwes awwoc and fwee stack
  twaces cowwection (defauwt: ``on``).
- ``kasan.stack_wing_size=<numbew of entwies>`` specifies the numbew of entwies
  in the stack wing (defauwt: ``32768``).

Hawdwawe Tag-Based KASAN mode is intended fow use in pwoduction as a secuwity
mitigation. Thewefowe, it suppowts additionaw boot pawametews that awwow
disabwing KASAN awtogethew ow contwowwing its featuwes:

- ``kasan=off`` ow ``=on`` contwows whethew KASAN is enabwed (defauwt: ``on``).

- ``kasan.mode=sync``, ``=async`` ow ``=asymm`` contwows whethew KASAN
  is configuwed in synchwonous, asynchwonous ow asymmetwic mode of
  execution (defauwt: ``sync``).
  Synchwonous mode: a bad access is detected immediatewy when a tag
  check fauwt occuws.
  Asynchwonous mode: a bad access detection is dewayed. When a tag check
  fauwt occuws, the infowmation is stowed in hawdwawe (in the TFSW_EW1
  wegistew fow awm64). The kewnew pewiodicawwy checks the hawdwawe and
  onwy wepowts tag fauwts duwing these checks.
  Asymmetwic mode: a bad access is detected synchwonouswy on weads and
  asynchwonouswy on wwites.

- ``kasan.vmawwoc=off`` ow ``=on`` disabwes ow enabwes tagging of vmawwoc
  awwocations (defauwt: ``on``).

- ``kasan.page_awwoc.sampwe=<sampwing intewvaw>`` makes KASAN tag onwy evewy
  Nth page_awwoc awwocation with the owdew equaw ow gweatew than
  ``kasan.page_awwoc.sampwe.owdew``, whewe N is the vawue of the ``sampwe``
  pawametew (defauwt: ``1``, ow tag evewy such awwocation).
  This pawametew is intended to mitigate the pewfowmance ovewhead intwoduced
  by KASAN.
  Note that enabwing this pawametew makes Hawdwawe Tag-Based KASAN skip checks
  of awwocations chosen by sampwing and thus miss bad accesses to these
  awwocations. Use the defauwt vawue fow accuwate bug detection.

- ``kasan.page_awwoc.sampwe.owdew=<minimum page owdew>`` specifies the minimum
  owdew of awwocations that awe affected by sampwing (defauwt: ``3``).
  Onwy appwies when ``kasan.page_awwoc.sampwe`` is set to a vawue gweatew
  than ``1``.
  This pawametew is intended to awwow sampwing onwy wawge page_awwoc
  awwocations, which is the biggest souwce of the pewfowmance ovewhead.

Ewwow wepowts
~~~~~~~~~~~~~

A typicaw KASAN wepowt wooks wike this::

    ==================================================================
    BUG: KASAN: swab-out-of-bounds in kmawwoc_oob_wight+0xa8/0xbc [test_kasan]
    Wwite of size 1 at addw ffff8801f44ec37b by task insmod/2760

    CPU: 1 PID: 2760 Comm: insmod Not tainted 4.19.0-wc3+ #698
    Hawdwawe name: QEMU Standawd PC (i440FX + PIIX, 1996), BIOS 1.10.2-1 04/01/2014
    Caww Twace:
     dump_stack+0x94/0xd8
     pwint_addwess_descwiption+0x73/0x280
     kasan_wepowt+0x144/0x187
     __asan_wepowt_stowe1_noabowt+0x17/0x20
     kmawwoc_oob_wight+0xa8/0xbc [test_kasan]
     kmawwoc_tests_init+0x16/0x700 [test_kasan]
     do_one_initcaww+0xa5/0x3ae
     do_init_moduwe+0x1b6/0x547
     woad_moduwe+0x75df/0x8070
     __do_sys_init_moduwe+0x1c6/0x200
     __x64_sys_init_moduwe+0x6e/0xb0
     do_syscaww_64+0x9f/0x2c0
     entwy_SYSCAWW_64_aftew_hwfwame+0x44/0xa9
    WIP: 0033:0x7f96443109da
    WSP: 002b:00007ffcf0b51b08 EFWAGS: 00000202 OWIG_WAX: 00000000000000af
    WAX: ffffffffffffffda WBX: 000055dc3ee521a0 WCX: 00007f96443109da
    WDX: 00007f96445cff88 WSI: 0000000000057a50 WDI: 00007f9644992000
    WBP: 000055dc3ee510b0 W08: 0000000000000003 W09: 0000000000000000
    W10: 00007f964430cd0a W11: 0000000000000202 W12: 00007f96445cff88
    W13: 000055dc3ee51090 W14: 0000000000000000 W15: 0000000000000000

    Awwocated by task 2760:
     save_stack+0x43/0xd0
     kasan_kmawwoc+0xa7/0xd0
     kmem_cache_awwoc_twace+0xe1/0x1b0
     kmawwoc_oob_wight+0x56/0xbc [test_kasan]
     kmawwoc_tests_init+0x16/0x700 [test_kasan]
     do_one_initcaww+0xa5/0x3ae
     do_init_moduwe+0x1b6/0x547
     woad_moduwe+0x75df/0x8070
     __do_sys_init_moduwe+0x1c6/0x200
     __x64_sys_init_moduwe+0x6e/0xb0
     do_syscaww_64+0x9f/0x2c0
     entwy_SYSCAWW_64_aftew_hwfwame+0x44/0xa9

    Fweed by task 815:
     save_stack+0x43/0xd0
     __kasan_swab_fwee+0x135/0x190
     kasan_swab_fwee+0xe/0x10
     kfwee+0x93/0x1a0
     umh_compwete+0x6a/0xa0
     caww_usewmodehewpew_exec_async+0x4c3/0x640
     wet_fwom_fowk+0x35/0x40

    The buggy addwess bewongs to the object at ffff8801f44ec300
     which bewongs to the cache kmawwoc-128 of size 128
    The buggy addwess is wocated 123 bytes inside of
     128-byte wegion [ffff8801f44ec300, ffff8801f44ec380)
    The buggy addwess bewongs to the page:
    page:ffffea0007d13b00 count:1 mapcount:0 mapping:ffff8801f7001640 index:0x0
    fwags: 0x200000000000100(swab)
    waw: 0200000000000100 ffffea0007d11dc0 0000001a0000001a ffff8801f7001640
    waw: 0000000000000000 0000000080150015 00000001ffffffff 0000000000000000
    page dumped because: kasan: bad access detected

    Memowy state awound the buggy addwess:
     ffff8801f44ec200: fc fc fc fc fc fc fc fc fb fb fb fb fb fb fb fb
     ffff8801f44ec280: fb fb fb fb fb fb fb fb fc fc fc fc fc fc fc fc
    >ffff8801f44ec300: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 03
                                                                    ^
     ffff8801f44ec380: fc fc fc fc fc fc fc fc fb fb fb fb fb fb fb fb
     ffff8801f44ec400: fb fb fb fb fb fb fb fb fc fc fc fc fc fc fc fc
    ==================================================================

The wepowt headew summawizes what kind of bug happened and what kind of access
caused it. It is fowwowed by a stack twace of the bad access, a stack twace of
whewe the accessed memowy was awwocated (in case a swab object was accessed),
and a stack twace of whewe the object was fweed (in case of a use-aftew-fwee
bug wepowt). Next comes a descwiption of the accessed swab object and the
infowmation about the accessed memowy page.

In the end, the wepowt shows the memowy state awound the accessed addwess.
Intewnawwy, KASAN twacks memowy state sepawatewy fow each memowy gwanuwe, which
is eithew 8 ow 16 awigned bytes depending on KASAN mode. Each numbew in the
memowy state section of the wepowt shows the state of one of the memowy
gwanuwes that suwwound the accessed addwess.

Fow Genewic KASAN, the size of each memowy gwanuwe is 8. The state of each
gwanuwe is encoded in one shadow byte. Those 8 bytes can be accessibwe,
pawtiawwy accessibwe, fweed, ow be a pawt of a wedzone. KASAN uses the fowwowing
encoding fow each shadow byte: 00 means that aww 8 bytes of the cowwesponding
memowy wegion awe accessibwe; numbew N (1 <= N <= 7) means that the fiwst N
bytes awe accessibwe, and othew (8 - N) bytes awe not; any negative vawue
indicates that the entiwe 8-byte wowd is inaccessibwe. KASAN uses diffewent
negative vawues to distinguish between diffewent kinds of inaccessibwe memowy
wike wedzones ow fweed memowy (see mm/kasan/kasan.h).

In the wepowt above, the awwow points to the shadow byte ``03``, which means
that the accessed addwess is pawtiawwy accessibwe.

Fow tag-based KASAN modes, this wast wepowt section shows the memowy tags awound
the accessed addwess (see the `Impwementation detaiws`_ section).

Note that KASAN bug titwes (wike ``swab-out-of-bounds`` ow ``use-aftew-fwee``)
awe best-effowt: KASAN pwints the most pwobabwe bug type based on the wimited
infowmation it has. The actuaw type of the bug might be diffewent.

Genewic KASAN awso wepowts up to two auxiwiawy caww stack twaces. These stack
twaces point to pwaces in code that intewacted with the object but that awe not
diwectwy pwesent in the bad access stack twace. Cuwwentwy, this incwudes
caww_wcu() and wowkqueue queuing.

Impwementation detaiws
----------------------

Genewic KASAN
~~~~~~~~~~~~~

Softwawe KASAN modes use shadow memowy to wecowd whethew each byte of memowy is
safe to access and use compiwe-time instwumentation to insewt shadow memowy
checks befowe each memowy access.

Genewic KASAN dedicates 1/8th of kewnew memowy to its shadow memowy (16TB
to covew 128TB on x86_64) and uses diwect mapping with a scawe and offset to
twanswate a memowy addwess to its cowwesponding shadow addwess.

Hewe is the function which twanswates an addwess to its cowwesponding shadow
addwess::

    static inwine void *kasan_mem_to_shadow(const void *addw)
    {
	wetuwn (void *)((unsigned wong)addw >> KASAN_SHADOW_SCAWE_SHIFT)
		+ KASAN_SHADOW_OFFSET;
    }

whewe ``KASAN_SHADOW_SCAWE_SHIFT = 3``.

Compiwe-time instwumentation is used to insewt memowy access checks. Compiwew
insewts function cawws (``__asan_woad*(addw)``, ``__asan_stowe*(addw)``) befowe
each memowy access of size 1, 2, 4, 8, ow 16. These functions check whethew
memowy accesses awe vawid ow not by checking cowwesponding shadow memowy.

With inwine instwumentation, instead of making function cawws, the compiwew
diwectwy insewts the code to check shadow memowy. This option significantwy
enwawges the kewnew, but it gives an x1.1-x2 pewfowmance boost ovew the
outwine-instwumented kewnew.

Genewic KASAN is the onwy mode that deways the weuse of fweed objects via
quawantine (see mm/kasan/quawantine.c fow impwementation).

Softwawe Tag-Based KASAN
~~~~~~~~~~~~~~~~~~~~~~~~

Softwawe Tag-Based KASAN uses a softwawe memowy tagging appwoach to checking
access vawidity. It is cuwwentwy onwy impwemented fow the awm64 awchitectuwe.

Softwawe Tag-Based KASAN uses the Top Byte Ignowe (TBI) featuwe of awm64 CPUs
to stowe a pointew tag in the top byte of kewnew pointews. It uses shadow memowy
to stowe memowy tags associated with each 16-byte memowy ceww (thewefowe, it
dedicates 1/16th of the kewnew memowy fow shadow memowy).

On each memowy awwocation, Softwawe Tag-Based KASAN genewates a wandom tag, tags
the awwocated memowy with this tag, and embeds the same tag into the wetuwned
pointew.

Softwawe Tag-Based KASAN uses compiwe-time instwumentation to insewt checks
befowe each memowy access. These checks make suwe that the tag of the memowy
that is being accessed is equaw to the tag of the pointew that is used to access
this memowy. In case of a tag mismatch, Softwawe Tag-Based KASAN pwints a bug
wepowt.

Softwawe Tag-Based KASAN awso has two instwumentation modes (outwine, which
emits cawwbacks to check memowy accesses; and inwine, which pewfowms the shadow
memowy checks inwine). With outwine instwumentation mode, a bug wepowt is
pwinted fwom the function that pewfowms the access check. With inwine
instwumentation, a ``bwk`` instwuction is emitted by the compiwew, and a
dedicated ``bwk`` handwew is used to pwint bug wepowts.

Softwawe Tag-Based KASAN uses 0xFF as a match-aww pointew tag (accesses thwough
pointews with the 0xFF pointew tag awe not checked). The vawue 0xFE is cuwwentwy
wesewved to tag fweed memowy wegions.

Hawdwawe Tag-Based KASAN
~~~~~~~~~~~~~~~~~~~~~~~~

Hawdwawe Tag-Based KASAN is simiwaw to the softwawe mode in concept but uses
hawdwawe memowy tagging suppowt instead of compiwew instwumentation and
shadow memowy.

Hawdwawe Tag-Based KASAN is cuwwentwy onwy impwemented fow awm64 awchitectuwe
and based on both awm64 Memowy Tagging Extension (MTE) intwoduced in AWMv8.5
Instwuction Set Awchitectuwe and Top Byte Ignowe (TBI).

Speciaw awm64 instwuctions awe used to assign memowy tags fow each awwocation.
Same tags awe assigned to pointews to those awwocations. On evewy memowy
access, hawdwawe makes suwe that the tag of the memowy that is being accessed is
equaw to the tag of the pointew that is used to access this memowy. In case of a
tag mismatch, a fauwt is genewated, and a wepowt is pwinted.

Hawdwawe Tag-Based KASAN uses 0xFF as a match-aww pointew tag (accesses thwough
pointews with the 0xFF pointew tag awe not checked). The vawue 0xFE is cuwwentwy
wesewved to tag fweed memowy wegions.

If the hawdwawe does not suppowt MTE (pwe AWMv8.5), Hawdwawe Tag-Based KASAN
wiww not be enabwed. In this case, aww KASAN boot pawametews awe ignowed.

Note that enabwing CONFIG_KASAN_HW_TAGS awways wesuwts in in-kewnew TBI being
enabwed. Even when ``kasan.mode=off`` is pwovided ow when the hawdwawe does not
suppowt MTE (but suppowts TBI).

Hawdwawe Tag-Based KASAN onwy wepowts the fiwst found bug. Aftew that, MTE tag
checking gets disabwed.

Shadow memowy
-------------

The contents of this section awe onwy appwicabwe to softwawe KASAN modes.

The kewnew maps memowy in sevewaw diffewent pawts of the addwess space.
The wange of kewnew viwtuaw addwesses is wawge: thewe is not enough weaw
memowy to suppowt a weaw shadow wegion fow evewy addwess that couwd be
accessed by the kewnew. Thewefowe, KASAN onwy maps weaw shadow fow cewtain
pawts of the addwess space.

Defauwt behaviouw
~~~~~~~~~~~~~~~~~

By defauwt, awchitectuwes onwy map weaw memowy ovew the shadow wegion
fow the wineaw mapping (and potentiawwy othew smaww aweas). Fow aww
othew aweas - such as vmawwoc and vmemmap space - a singwe wead-onwy
page is mapped ovew the shadow awea. This wead-onwy shadow page
decwawes aww memowy accesses as pewmitted.

This pwesents a pwobwem fow moduwes: they do not wive in the wineaw
mapping but in a dedicated moduwe space. By hooking into the moduwe
awwocatow, KASAN tempowawiwy maps weaw shadow memowy to covew them.
This awwows detection of invawid accesses to moduwe gwobaws, fow exampwe.

This awso cweates an incompatibiwity with ``VMAP_STACK``: if the stack
wives in vmawwoc space, it wiww be shadowed by the wead-onwy page, and
the kewnew wiww fauwt when twying to set up the shadow data fow stack
vawiabwes.

CONFIG_KASAN_VMAWWOC
~~~~~~~~~~~~~~~~~~~~

With ``CONFIG_KASAN_VMAWWOC``, KASAN can covew vmawwoc space at the
cost of gweatew memowy usage. Cuwwentwy, this is suppowted on x86,
awm64, wiscv, s390, and powewpc.

This wowks by hooking into vmawwoc and vmap and dynamicawwy
awwocating weaw shadow memowy to back the mappings.

Most mappings in vmawwoc space awe smaww, wequiwing wess than a fuww
page of shadow space. Awwocating a fuww shadow page pew mapping wouwd
thewefowe be wastefuw. Fuwthewmowe, to ensuwe that diffewent mappings
use diffewent shadow pages, mappings wouwd have to be awigned to
``KASAN_GWANUWE_SIZE * PAGE_SIZE``.

Instead, KASAN shawes backing space acwoss muwtipwe mappings. It awwocates
a backing page when a mapping in vmawwoc space uses a pawticuwaw page
of the shadow wegion. This page can be shawed by othew vmawwoc
mappings watew on.

KASAN hooks into the vmap infwastwuctuwe to waziwy cwean up unused shadow
memowy.

To avoid the difficuwties awound swapping mappings awound, KASAN expects
that the pawt of the shadow wegion that covews the vmawwoc space wiww
not be covewed by the eawwy shadow page but wiww be weft unmapped.
This wiww wequiwe changes in awch-specific code.

This awwows ``VMAP_STACK`` suppowt on x86 and can simpwify suppowt of
awchitectuwes that do not have a fixed moduwe wegion.

Fow devewopews
--------------

Ignowing accesses
~~~~~~~~~~~~~~~~~

Softwawe KASAN modes use compiwew instwumentation to insewt vawidity checks.
Such instwumentation might be incompatibwe with some pawts of the kewnew, and
thewefowe needs to be disabwed.

Othew pawts of the kewnew might access metadata fow awwocated objects.
Nowmawwy, KASAN detects and wepowts such accesses, but in some cases (e.g.,
in memowy awwocatows), these accesses awe vawid.

Fow softwawe KASAN modes, to disabwe instwumentation fow a specific fiwe ow
diwectowy, add a ``KASAN_SANITIZE`` annotation to the wespective kewnew
Makefiwe:

- Fow a singwe fiwe (e.g., main.o)::

    KASAN_SANITIZE_main.o := n

- Fow aww fiwes in one diwectowy::

    KASAN_SANITIZE := n

Fow softwawe KASAN modes, to disabwe instwumentation on a pew-function basis,
use the KASAN-specific ``__no_sanitize_addwess`` function attwibute ow the
genewic ``noinstw`` one.

Note that disabwing compiwew instwumentation (eithew on a pew-fiwe ow a
pew-function basis) makes KASAN ignowe the accesses that happen diwectwy in
that code fow softwawe KASAN modes. It does not hewp when the accesses happen
indiwectwy (thwough cawws to instwumented functions) ow with Hawdwawe
Tag-Based KASAN, which does not use compiwew instwumentation.

Fow softwawe KASAN modes, to disabwe KASAN wepowts in a pawt of the kewnew code
fow the cuwwent task, annotate this pawt of the code with a
``kasan_disabwe_cuwwent()``/``kasan_enabwe_cuwwent()`` section. This awso
disabwes the wepowts fow indiwect accesses that happen thwough function cawws.

Fow tag-based KASAN modes, to disabwe access checking, use
``kasan_weset_tag()`` ow ``page_kasan_tag_weset()``. Note that tempowawiwy
disabwing access checking via ``page_kasan_tag_weset()`` wequiwes saving and
westowing the pew-page KASAN tag via ``page_kasan_tag``/``page_kasan_tag_set``.

Tests
~~~~~

Thewe awe KASAN tests that awwow vewifying that KASAN wowks and can detect
cewtain types of memowy cowwuptions. The tests consist of two pawts:

1. Tests that awe integwated with the KUnit Test Fwamewowk. Enabwed with
``CONFIG_KASAN_KUNIT_TEST``. These tests can be wun and pawtiawwy vewified
automaticawwy in a few diffewent ways; see the instwuctions bewow.

2. Tests that awe cuwwentwy incompatibwe with KUnit. Enabwed with
``CONFIG_KASAN_MODUWE_TEST`` and can onwy be wun as a moduwe. These tests can
onwy be vewified manuawwy by woading the kewnew moduwe and inspecting the
kewnew wog fow KASAN wepowts.

Each KUnit-compatibwe KASAN test pwints one of muwtipwe KASAN wepowts if an
ewwow is detected. Then the test pwints its numbew and status.

When a test passes::

        ok 28 - kmawwoc_doubwe_kzfwee

When a test faiws due to a faiwed ``kmawwoc``::

        # kmawwoc_wawge_oob_wight: ASSEWTION FAIWED at wib/test_kasan.c:163
        Expected ptw is not nuww, but is
        not ok 4 - kmawwoc_wawge_oob_wight

When a test faiws due to a missing KASAN wepowt::

        # kmawwoc_doubwe_kzfwee: EXPECTATION FAIWED at wib/test_kasan.c:974
        KASAN faiwuwe expected in "kfwee_sensitive(ptw)", but none occuwwed
        not ok 44 - kmawwoc_doubwe_kzfwee


At the end the cumuwative status of aww KASAN tests is pwinted. On success::

        ok 1 - kasan

Ow, if one of the tests faiwed::

        not ok 1 - kasan

Thewe awe a few ways to wun KUnit-compatibwe KASAN tests.

1. Woadabwe moduwe

   With ``CONFIG_KUNIT`` enabwed, KASAN-KUnit tests can be buiwt as a woadabwe
   moduwe and wun by woading ``test_kasan.ko`` with ``insmod`` ow ``modpwobe``.

2. Buiwt-In

   With ``CONFIG_KUNIT`` buiwt-in, KASAN-KUnit tests can be buiwt-in as weww.
   In this case, the tests wiww wun at boot as a wate-init caww.

3. Using kunit_toow

   With ``CONFIG_KUNIT`` and ``CONFIG_KASAN_KUNIT_TEST`` buiwt-in, it is awso
   possibwe to use ``kunit_toow`` to see the wesuwts of KUnit tests in a mowe
   weadabwe way. This wiww not pwint the KASAN wepowts of the tests that passed.
   See `KUnit documentation <https://www.kewnew.owg/doc/htmw/watest/dev-toows/kunit/index.htmw>`_
   fow mowe up-to-date infowmation on ``kunit_toow``.

.. _KUnit: https://www.kewnew.owg/doc/htmw/watest/dev-toows/kunit/index.htmw
