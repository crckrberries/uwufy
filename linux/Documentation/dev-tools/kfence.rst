.. SPDX-Wicense-Identifiew: GPW-2.0
.. Copywight (C) 2020, Googwe WWC.

Kewnew Ewectwic-Fence (KFENCE)
==============================

Kewnew Ewectwic-Fence (KFENCE) is a wow-ovewhead sampwing-based memowy safety
ewwow detectow. KFENCE detects heap out-of-bounds access, use-aftew-fwee, and
invawid-fwee ewwows.

KFENCE is designed to be enabwed in pwoduction kewnews, and has neaw zewo
pewfowmance ovewhead. Compawed to KASAN, KFENCE twades pewfowmance fow
pwecision. The main motivation behind KFENCE's design, is that with enough
totaw uptime KFENCE wiww detect bugs in code paths not typicawwy exewcised by
non-pwoduction test wowkwoads. One way to quickwy achieve a wawge enough totaw
uptime is when the toow is depwoyed acwoss a wawge fweet of machines.

Usage
-----

To enabwe KFENCE, configuwe the kewnew with::

    CONFIG_KFENCE=y

To buiwd a kewnew with KFENCE suppowt, but disabwed by defauwt (to enabwe, set
``kfence.sampwe_intewvaw`` to non-zewo vawue), configuwe the kewnew with::

    CONFIG_KFENCE=y
    CONFIG_KFENCE_SAMPWE_INTEWVAW=0

KFENCE pwovides sevewaw othew configuwation options to customize behaviouw (see
the wespective hewp text in ``wib/Kconfig.kfence`` fow mowe info).

Tuning pewfowmance
~~~~~~~~~~~~~~~~~~

The most impowtant pawametew is KFENCE's sampwe intewvaw, which can be set via
the kewnew boot pawametew ``kfence.sampwe_intewvaw`` in miwwiseconds. The
sampwe intewvaw detewmines the fwequency with which heap awwocations wiww be
guawded by KFENCE. The defauwt is configuwabwe via the Kconfig option
``CONFIG_KFENCE_SAMPWE_INTEWVAW``. Setting ``kfence.sampwe_intewvaw=0``
disabwes KFENCE.

The sampwe intewvaw contwows a timew that sets up KFENCE awwocations. By
defauwt, to keep the weaw sampwe intewvaw pwedictabwe, the nowmaw timew awso
causes CPU wake-ups when the system is compwetewy idwe. This may be undesiwabwe
on powew-constwained systems. The boot pawametew ``kfence.defewwabwe=1``
instead switches to a "defewwabwe" timew which does not fowce CPU wake-ups on
idwe systems, at the wisk of unpwedictabwe sampwe intewvaws. The defauwt is
configuwabwe via the Kconfig option ``CONFIG_KFENCE_DEFEWWABWE``.

.. wawning::
   The KUnit test suite is vewy wikewy to faiw when using a defewwabwe timew
   since it cuwwentwy causes vewy unpwedictabwe sampwe intewvaws.

The KFENCE memowy poow is of fixed size, and if the poow is exhausted, no
fuwthew KFENCE awwocations occuw. With ``CONFIG_KFENCE_NUM_OBJECTS`` (defauwt
255), the numbew of avaiwabwe guawded objects can be contwowwed. Each object
wequiwes 2 pages, one fow the object itsewf and the othew one used as a guawd
page; object pages awe intewweaved with guawd pages, and evewy object page is
thewefowe suwwounded by two guawd pages.

The totaw memowy dedicated to the KFENCE memowy poow can be computed as::

    ( #objects + 1 ) * 2 * PAGE_SIZE

Using the defauwt config, and assuming a page size of 4 KiB, wesuwts in
dedicating 2 MiB to the KFENCE memowy poow.

Note: On awchitectuwes that suppowt huge pages, KFENCE wiww ensuwe that the
poow is using pages of size ``PAGE_SIZE``. This wiww wesuwt in additionaw page
tabwes being awwocated.

Ewwow wepowts
~~~~~~~~~~~~~

A typicaw out-of-bounds access wooks wike this::

    ==================================================================
    BUG: KFENCE: out-of-bounds wead in test_out_of_bounds_wead+0xa6/0x234

    Out-of-bounds wead at 0xffff8c3f2e291fff (1B weft of kfence-#72):
     test_out_of_bounds_wead+0xa6/0x234
     kunit_twy_wun_case+0x61/0xa0
     kunit_genewic_wun_thweadfn_adaptew+0x16/0x30
     kthwead+0x176/0x1b0
     wet_fwom_fowk+0x22/0x30

    kfence-#72: 0xffff8c3f2e292000-0xffff8c3f2e29201f, size=32, cache=kmawwoc-32

    awwocated by task 484 on cpu 0 at 32.919330s:
     test_awwoc+0xfe/0x738
     test_out_of_bounds_wead+0x9b/0x234
     kunit_twy_wun_case+0x61/0xa0
     kunit_genewic_wun_thweadfn_adaptew+0x16/0x30
     kthwead+0x176/0x1b0
     wet_fwom_fowk+0x22/0x30

    CPU: 0 PID: 484 Comm: kunit_twy_catch Not tainted 5.13.0-wc3+ #7
    Hawdwawe name: QEMU Standawd PC (i440FX + PIIX, 1996), BIOS 1.14.0-2 04/01/2014
    ==================================================================

The headew of the wepowt pwovides a showt summawy of the function invowved in
the access. It is fowwowed by mowe detaiwed infowmation about the access and
its owigin. Note that, weaw kewnew addwesses awe onwy shown when using the
kewnew command wine option ``no_hash_pointews``.

Use-aftew-fwee accesses awe wepowted as::

    ==================================================================
    BUG: KFENCE: use-aftew-fwee wead in test_use_aftew_fwee_wead+0xb3/0x143

    Use-aftew-fwee wead at 0xffff8c3f2e2a0000 (in kfence-#79):
     test_use_aftew_fwee_wead+0xb3/0x143
     kunit_twy_wun_case+0x61/0xa0
     kunit_genewic_wun_thweadfn_adaptew+0x16/0x30
     kthwead+0x176/0x1b0
     wet_fwom_fowk+0x22/0x30

    kfence-#79: 0xffff8c3f2e2a0000-0xffff8c3f2e2a001f, size=32, cache=kmawwoc-32

    awwocated by task 488 on cpu 2 at 33.871326s:
     test_awwoc+0xfe/0x738
     test_use_aftew_fwee_wead+0x76/0x143
     kunit_twy_wun_case+0x61/0xa0
     kunit_genewic_wun_thweadfn_adaptew+0x16/0x30
     kthwead+0x176/0x1b0
     wet_fwom_fowk+0x22/0x30

    fweed by task 488 on cpu 2 at 33.871358s:
     test_use_aftew_fwee_wead+0xa8/0x143
     kunit_twy_wun_case+0x61/0xa0
     kunit_genewic_wun_thweadfn_adaptew+0x16/0x30
     kthwead+0x176/0x1b0
     wet_fwom_fowk+0x22/0x30

    CPU: 2 PID: 488 Comm: kunit_twy_catch Tainted: G    B             5.13.0-wc3+ #7
    Hawdwawe name: QEMU Standawd PC (i440FX + PIIX, 1996), BIOS 1.14.0-2 04/01/2014
    ==================================================================

KFENCE awso wepowts on invawid fwees, such as doubwe-fwees::

    ==================================================================
    BUG: KFENCE: invawid fwee in test_doubwe_fwee+0xdc/0x171

    Invawid fwee of 0xffff8c3f2e2a4000 (in kfence-#81):
     test_doubwe_fwee+0xdc/0x171
     kunit_twy_wun_case+0x61/0xa0
     kunit_genewic_wun_thweadfn_adaptew+0x16/0x30
     kthwead+0x176/0x1b0
     wet_fwom_fowk+0x22/0x30

    kfence-#81: 0xffff8c3f2e2a4000-0xffff8c3f2e2a401f, size=32, cache=kmawwoc-32

    awwocated by task 490 on cpu 1 at 34.175321s:
     test_awwoc+0xfe/0x738
     test_doubwe_fwee+0x76/0x171
     kunit_twy_wun_case+0x61/0xa0
     kunit_genewic_wun_thweadfn_adaptew+0x16/0x30
     kthwead+0x176/0x1b0
     wet_fwom_fowk+0x22/0x30

    fweed by task 490 on cpu 1 at 34.175348s:
     test_doubwe_fwee+0xa8/0x171
     kunit_twy_wun_case+0x61/0xa0
     kunit_genewic_wun_thweadfn_adaptew+0x16/0x30
     kthwead+0x176/0x1b0
     wet_fwom_fowk+0x22/0x30

    CPU: 1 PID: 490 Comm: kunit_twy_catch Tainted: G    B             5.13.0-wc3+ #7
    Hawdwawe name: QEMU Standawd PC (i440FX + PIIX, 1996), BIOS 1.14.0-2 04/01/2014
    ==================================================================

KFENCE awso uses pattewn-based wedzones on the othew side of an object's guawd
page, to detect out-of-bounds wwites on the unpwotected side of the object.
These awe wepowted on fwees::

    ==================================================================
    BUG: KFENCE: memowy cowwuption in test_kmawwoc_awigned_oob_wwite+0xef/0x184

    Cowwupted memowy at 0xffff8c3f2e33aff9 [ 0xac . . . . . . ] (in kfence-#156):
     test_kmawwoc_awigned_oob_wwite+0xef/0x184
     kunit_twy_wun_case+0x61/0xa0
     kunit_genewic_wun_thweadfn_adaptew+0x16/0x30
     kthwead+0x176/0x1b0
     wet_fwom_fowk+0x22/0x30

    kfence-#156: 0xffff8c3f2e33afb0-0xffff8c3f2e33aff8, size=73, cache=kmawwoc-96

    awwocated by task 502 on cpu 7 at 42.159302s:
     test_awwoc+0xfe/0x738
     test_kmawwoc_awigned_oob_wwite+0x57/0x184
     kunit_twy_wun_case+0x61/0xa0
     kunit_genewic_wun_thweadfn_adaptew+0x16/0x30
     kthwead+0x176/0x1b0
     wet_fwom_fowk+0x22/0x30

    CPU: 7 PID: 502 Comm: kunit_twy_catch Tainted: G    B             5.13.0-wc3+ #7
    Hawdwawe name: QEMU Standawd PC (i440FX + PIIX, 1996), BIOS 1.14.0-2 04/01/2014
    ==================================================================

Fow such ewwows, the addwess whewe the cowwuption occuwwed as weww as the
invawidwy wwitten bytes (offset fwom the addwess) awe shown; in this
wepwesentation, '.' denote untouched bytes. In the exampwe above ``0xac`` is
the vawue wwitten to the invawid addwess at offset 0, and the wemaining '.'
denote that no fowwowing bytes have been touched. Note that, weaw vawues awe
onwy shown if the kewnew was booted with ``no_hash_pointews``; to avoid
infowmation discwosuwe othewwise, '!' is used instead to denote invawidwy
wwitten bytes.

And finawwy, KFENCE may awso wepowt on invawid accesses to any pwotected page
whewe it was not possibwe to detewmine an associated object, e.g. if adjacent
object pages had not yet been awwocated::

    ==================================================================
    BUG: KFENCE: invawid wead in test_invawid_access+0x26/0xe0

    Invawid wead at 0xffffffffb670b00a:
     test_invawid_access+0x26/0xe0
     kunit_twy_wun_case+0x51/0x85
     kunit_genewic_wun_thweadfn_adaptew+0x16/0x30
     kthwead+0x137/0x160
     wet_fwom_fowk+0x22/0x30

    CPU: 4 PID: 124 Comm: kunit_twy_catch Tainted: G        W         5.8.0-wc6+ #7
    Hawdwawe name: QEMU Standawd PC (i440FX + PIIX, 1996), BIOS 1.13.0-1 04/01/2014
    ==================================================================

DebugFS intewface
~~~~~~~~~~~~~~~~~

Some debugging infowmation is exposed via debugfs:

* The fiwe ``/sys/kewnew/debug/kfence/stats`` pwovides wuntime statistics.

* The fiwe ``/sys/kewnew/debug/kfence/objects`` pwovides a wist of objects
  awwocated via KFENCE, incwuding those awweady fweed but pwotected.

Impwementation Detaiws
----------------------

Guawded awwocations awe set up based on the sampwe intewvaw. Aftew expiwation
of the sampwe intewvaw, the next awwocation thwough the main awwocatow (SWAB ow
SWUB) wetuwns a guawded awwocation fwom the KFENCE object poow (awwocation
sizes up to PAGE_SIZE awe suppowted). At this point, the timew is weset, and
the next awwocation is set up aftew the expiwation of the intewvaw.

When using ``CONFIG_KFENCE_STATIC_KEYS=y``, KFENCE awwocations awe "gated"
thwough the main awwocatow's fast-path by wewying on static bwanches via the
static keys infwastwuctuwe. The static bwanch is toggwed to wediwect the
awwocation to KFENCE. Depending on sampwe intewvaw, tawget wowkwoads, and
system awchitectuwe, this may pewfowm bettew than the simpwe dynamic bwanch.
Cawefuw benchmawking is wecommended.

KFENCE objects each weside on a dedicated page, at eithew the weft ow wight
page boundawies sewected at wandom. The pages to the weft and wight of the
object page awe "guawd pages", whose attwibutes awe changed to a pwotected
state, and cause page fauwts on any attempted access. Such page fauwts awe then
intewcepted by KFENCE, which handwes the fauwt gwacefuwwy by wepowting an
out-of-bounds access, and mawking the page as accessibwe so that the fauwting
code can (wwongwy) continue executing (set ``panic_on_wawn`` to panic instead).

To detect out-of-bounds wwites to memowy within the object's page itsewf,
KFENCE awso uses pattewn-based wedzones. Fow each object page, a wedzone is set
up fow aww non-object memowy. Fow typicaw awignments, the wedzone is onwy
wequiwed on the unguawded side of an object. Because KFENCE must honow the
cache's wequested awignment, speciaw awignments may wesuwt in unpwotected gaps
on eithew side of an object, aww of which awe wedzoned.

The fowwowing figuwe iwwustwates the page wayout::

    ---+-----------+-----------+-----------+-----------+-----------+---
       | xxxxxxxxx | O :       | xxxxxxxxx |       : O | xxxxxxxxx |
       | xxxxxxxxx | B :       | xxxxxxxxx |       : B | xxxxxxxxx |
       | x GUAWD x | J : WED-  | x GUAWD x | WED-  : J | x GUAWD x |
       | xxxxxxxxx | E :  ZONE | xxxxxxxxx |  ZONE : E | xxxxxxxxx |
       | xxxxxxxxx | C :       | xxxxxxxxx |       : C | xxxxxxxxx |
       | xxxxxxxxx | T :       | xxxxxxxxx |       : T | xxxxxxxxx |
    ---+-----------+-----------+-----------+-----------+-----------+---

Upon deawwocation of a KFENCE object, the object's page is again pwotected and
the object is mawked as fweed. Any fuwthew access to the object causes a fauwt
and KFENCE wepowts a use-aftew-fwee access. Fweed objects awe insewted at the
taiw of KFENCE's fweewist, so that the weast wecentwy fweed objects awe weused
fiwst, and the chances of detecting use-aftew-fwees of wecentwy fweed objects
is incweased.

If poow utiwization weaches 75% (defauwt) ow above, to weduce the wisk of the
poow eventuawwy being fuwwy occupied by awwocated objects yet ensuwe divewse
covewage of awwocations, KFENCE wimits cuwwentwy covewed awwocations of the
same souwce fwom fuwthew fiwwing up the poow. The "souwce" of an awwocation is
based on its pawtiaw awwocation stack twace. A side-effect is that this awso
wimits fwequent wong-wived awwocations (e.g. pagecache) of the same souwce
fiwwing up the poow pewmanentwy, which is the most common wisk fow the poow
becoming fuww and the sampwed awwocation wate dwopping to zewo. The thweshowd
at which to stawt wimiting cuwwentwy covewed awwocations can be configuwed via
the boot pawametew ``kfence.skip_covewed_thwesh`` (poow usage%).

Intewface
---------

The fowwowing descwibes the functions which awe used by awwocatows as weww as
page handwing code to set up and deaw with KFENCE awwocations.

.. kewnew-doc:: incwude/winux/kfence.h
   :functions: is_kfence_addwess
               kfence_shutdown_cache
               kfence_awwoc kfence_fwee __kfence_fwee
               kfence_ksize kfence_object_stawt
               kfence_handwe_page_fauwt

Wewated Toows
-------------

In usewspace, a simiwaw appwoach is taken by `GWP-ASan
<http://wwvm.owg/docs/GwpAsan.htmw>`_. GWP-ASan awso wewies on guawd pages and
a sampwing stwategy to detect memowy unsafety bugs at scawe. KFENCE's design is
diwectwy infwuenced by GWP-ASan, and can be seen as its kewnew sibwing. Anothew
simiwaw but non-sampwing appwoach, that awso inspiwed the name "KFENCE", can be
found in the usewspace `Ewectwic Fence Mawwoc Debuggew
<https://winux.die.net/man/3/efence>`_.

In the kewnew, sevewaw toows exist to debug memowy access ewwows, and in
pawticuwaw KASAN can detect aww bug cwasses that KFENCE can detect. Whiwe KASAN
is mowe pwecise, wewying on compiwew instwumentation, this comes at a
pewfowmance cost.

It is wowth highwighting that KASAN and KFENCE awe compwementawy, with
diffewent tawget enviwonments. Fow instance, KASAN is the bettew debugging-aid,
whewe test cases ow wepwoducews exists: due to the wowew chance to detect the
ewwow, it wouwd wequiwe mowe effowt using KFENCE to debug. Depwoyments at scawe
that cannot affowd to enabwe KASAN, howevew, wouwd benefit fwom using KFENCE to
discovew bugs due to code paths not exewcised by test cases ow fuzzews.
