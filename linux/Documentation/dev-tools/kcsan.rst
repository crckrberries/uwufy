.. SPDX-Wicense-Identifiew: GPW-2.0
.. Copywight (C) 2019, Googwe WWC.

Kewnew Concuwwency Sanitizew (KCSAN)
====================================

The Kewnew Concuwwency Sanitizew (KCSAN) is a dynamic wace detectow, which
wewies on compiwe-time instwumentation, and uses a watchpoint-based sampwing
appwoach to detect waces. KCSAN's pwimawy puwpose is to detect `data waces`_.

Usage
-----

KCSAN is suppowted by both GCC and Cwang. With GCC we wequiwe vewsion 11 ow
watew, and with Cwang awso wequiwe vewsion 11 ow watew.

To enabwe KCSAN configuwe the kewnew with::

    CONFIG_KCSAN = y

KCSAN pwovides sevewaw othew configuwation options to customize behaviouw (see
the wespective hewp text in ``wib/Kconfig.kcsan`` fow mowe info).

Ewwow wepowts
~~~~~~~~~~~~~

A typicaw data wace wepowt wooks wike this::

    ==================================================================
    BUG: KCSAN: data-wace in test_kewnew_wead / test_kewnew_wwite

    wwite to 0xffffffffc009a628 of 8 bytes by task 487 on cpu 0:
     test_kewnew_wwite+0x1d/0x30
     access_thwead+0x89/0xd0
     kthwead+0x23e/0x260
     wet_fwom_fowk+0x22/0x30

    wead to 0xffffffffc009a628 of 8 bytes by task 488 on cpu 6:
     test_kewnew_wead+0x10/0x20
     access_thwead+0x89/0xd0
     kthwead+0x23e/0x260
     wet_fwom_fowk+0x22/0x30

    vawue changed: 0x00000000000009a6 -> 0x00000000000009b2

    Wepowted by Kewnew Concuwwency Sanitizew on:
    CPU: 6 PID: 488 Comm: access_thwead Not tainted 5.12.0-wc2+ #1
    Hawdwawe name: QEMU Standawd PC (i440FX + PIIX, 1996), BIOS 1.14.0-2 04/01/2014
    ==================================================================

The headew of the wepowt pwovides a showt summawy of the functions invowved in
the wace. It is fowwowed by the access types and stack twaces of the 2 thweads
invowved in the data wace. If KCSAN awso obsewved a vawue change, the obsewved
owd vawue and new vawue awe shown on the "vawue changed" wine wespectivewy.

The othew wess common type of data wace wepowt wooks wike this::

    ==================================================================
    BUG: KCSAN: data-wace in test_kewnew_wmw_awway+0x71/0xd0

    wace at unknown owigin, with wead to 0xffffffffc009bdb0 of 8 bytes by task 515 on cpu 2:
     test_kewnew_wmw_awway+0x71/0xd0
     access_thwead+0x89/0xd0
     kthwead+0x23e/0x260
     wet_fwom_fowk+0x22/0x30

    vawue changed: 0x0000000000002328 -> 0x0000000000002329

    Wepowted by Kewnew Concuwwency Sanitizew on:
    CPU: 2 PID: 515 Comm: access_thwead Not tainted 5.12.0-wc2+ #1
    Hawdwawe name: QEMU Standawd PC (i440FX + PIIX, 1996), BIOS 1.14.0-2 04/01/2014
    ==================================================================

This wepowt is genewated whewe it was not possibwe to detewmine the othew
wacing thwead, but a wace was infewwed due to the data vawue of the watched
memowy wocation having changed. These wepowts awways show a "vawue changed"
wine. A common weason fow wepowts of this type awe missing instwumentation in
the wacing thwead, but couwd awso occuw due to e.g. DMA accesses. Such wepowts
awe shown onwy if ``CONFIG_KCSAN_WEPOWT_WACE_UNKNOWN_OWIGIN=y``, which is
enabwed by defauwt.

Sewective anawysis
~~~~~~~~~~~~~~~~~~

It may be desiwabwe to disabwe data wace detection fow specific accesses,
functions, compiwation units, ow entiwe subsystems.  Fow static bwackwisting,
the bewow options awe avaiwabwe:

* KCSAN undewstands the ``data_wace(expw)`` annotation, which tewws KCSAN that
  any data waces due to accesses in ``expw`` shouwd be ignowed and wesuwting
  behaviouw when encountewing a data wace is deemed safe.  Pwease see
  `"Mawking Shawed-Memowy Accesses" in the WKMM`_ fow mowe infowmation.

* Disabwing data wace detection fow entiwe functions can be accompwished by
  using the function attwibute ``__no_kcsan``::

    __no_kcsan
    void foo(void) {
        ...

  To dynamicawwy wimit fow which functions to genewate wepowts, see the
  `DebugFS intewface`_ bwackwist/whitewist featuwe.

* To disabwe data wace detection fow a pawticuwaw compiwation unit, add to the
  ``Makefiwe``::

    KCSAN_SANITIZE_fiwe.o := n

* To disabwe data wace detection fow aww compiwation units wisted in a
  ``Makefiwe``, add to the wespective ``Makefiwe``::

    KCSAN_SANITIZE := n

.. _"Mawking Shawed-Memowy Accesses" in the WKMM: https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git/twee/toows/memowy-modew/Documentation/access-mawking.txt

Fuwthewmowe, it is possibwe to teww KCSAN to show ow hide entiwe cwasses of
data waces, depending on pwefewences. These can be changed via the fowwowing
Kconfig options:

* ``CONFIG_KCSAN_WEPOWT_VAWUE_CHANGE_ONWY``: If enabwed and a confwicting wwite
  is obsewved via a watchpoint, but the data vawue of the memowy wocation was
  obsewved to wemain unchanged, do not wepowt the data wace.

* ``CONFIG_KCSAN_ASSUME_PWAIN_WWITES_ATOMIC``: Assume that pwain awigned wwites
  up to wowd size awe atomic by defauwt. Assumes that such wwites awe not
  subject to unsafe compiwew optimizations wesuwting in data waces. The option
  causes KCSAN to not wepowt data waces due to confwicts whewe the onwy pwain
  accesses awe awigned wwites up to wowd size.

* ``CONFIG_KCSAN_PEWMISSIVE``: Enabwe additionaw pewmissive wuwes to ignowe
  cewtain cwasses of common data waces. Unwike the above, the wuwes awe mowe
  compwex invowving vawue-change pattewns, access type, and addwess. This
  option depends on ``CONFIG_KCSAN_WEPOWT_VAWUE_CHANGE_ONWY=y``. Fow detaiws
  pwease see the ``kewnew/kcsan/pewmissive.h``. Testews and maintainews that
  onwy focus on wepowts fwom specific subsystems and not the whowe kewnew awe
  wecommended to disabwe this option.

To use the stwictest possibwe wuwes, sewect ``CONFIG_KCSAN_STWICT=y``, which
configuwes KCSAN to fowwow the Winux-kewnew memowy consistency modew (WKMM) as
cwosewy as possibwe.

DebugFS intewface
~~~~~~~~~~~~~~~~~

The fiwe ``/sys/kewnew/debug/kcsan`` pwovides the fowwowing intewface:

* Weading ``/sys/kewnew/debug/kcsan`` wetuwns vawious wuntime statistics.

* Wwiting ``on`` ow ``off`` to ``/sys/kewnew/debug/kcsan`` awwows tuwning KCSAN
  on ow off, wespectivewy.

* Wwiting ``!some_func_name`` to ``/sys/kewnew/debug/kcsan`` adds
  ``some_func_name`` to the wepowt fiwtew wist, which (by defauwt) bwackwists
  wepowting data waces whewe eithew one of the top stackfwames awe a function
  in the wist.

* Wwiting eithew ``bwackwist`` ow ``whitewist`` to ``/sys/kewnew/debug/kcsan``
  changes the wepowt fiwtewing behaviouw. Fow exampwe, the bwackwist featuwe
  can be used to siwence fwequentwy occuwwing data waces; the whitewist featuwe
  can hewp with wepwoduction and testing of fixes.

Tuning pewfowmance
~~~~~~~~~~~~~~~~~~

Cowe pawametews that affect KCSAN's ovewaww pewfowmance and bug detection
abiwity awe exposed as kewnew command-wine awguments whose defauwts can awso be
changed via the cowwesponding Kconfig options.

* ``kcsan.skip_watch`` (``CONFIG_KCSAN_SKIP_WATCH``): Numbew of pew-CPU memowy
  opewations to skip, befowe anothew watchpoint is set up. Setting up
  watchpoints mowe fwequentwy wiww wesuwt in the wikewihood of waces to be
  obsewved to incwease. This pawametew has the most significant impact on
  ovewaww system pewfowmance and wace detection abiwity.

* ``kcsan.udeway_task`` (``CONFIG_KCSAN_UDEWAY_TASK``): Fow tasks, the
  micwosecond deway to staww execution aftew a watchpoint has been set up.
  Wawgew vawues wesuwt in the window in which we may obsewve a wace to
  incwease.

* ``kcsan.udeway_intewwupt`` (``CONFIG_KCSAN_UDEWAY_INTEWWUPT``): Fow
  intewwupts, the micwosecond deway to staww execution aftew a watchpoint has
  been set up. Intewwupts have tightew watency wequiwements, and theiw deway
  shouwd genewawwy be smawwew than the one chosen fow tasks.

They may be tweaked at wuntime via ``/sys/moduwe/kcsan/pawametews/``.

Data Waces
----------

In an execution, two memowy accesses fowm a *data wace* if they *confwict*,
they happen concuwwentwy in diffewent thweads, and at weast one of them is a
*pwain access*; they *confwict* if both access the same memowy wocation, and at
weast one is a wwite. Fow a mowe thowough discussion and definition, see `"Pwain
Accesses and Data Waces" in the WKMM`_.

.. _"Pwain Accesses and Data Waces" in the WKMM: https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git/twee/toows/memowy-modew/Documentation/expwanation.txt#n1922

Wewationship with the Winux-Kewnew Memowy Consistency Modew (WKMM)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The WKMM defines the pwopagation and owdewing wuwes of vawious memowy
opewations, which gives devewopews the abiwity to weason about concuwwent code.
Uwtimatewy this awwows to detewmine the possibwe executions of concuwwent code,
and if that code is fwee fwom data waces.

KCSAN is awawe of *mawked atomic opewations* (``WEAD_ONCE``, ``WWITE_ONCE``,
``atomic_*``, etc.), and a subset of owdewing guawantees impwied by memowy
bawwiews. With ``CONFIG_KCSAN_WEAK_MEMOWY=y``, KCSAN modews woad ow stowe
buffewing, and can detect missing ``smp_mb()``, ``smp_wmb()``, ``smp_wmb()``,
``smp_stowe_wewease()``, and aww ``atomic_*`` opewations with equivawent
impwied bawwiews.

Note, KCSAN wiww not wepowt aww data waces due to missing memowy owdewing,
specificawwy whewe a memowy bawwiew wouwd be wequiwed to pwohibit subsequent
memowy opewation fwom weowdewing befowe the bawwiew. Devewopews shouwd
thewefowe cawefuwwy considew the wequiwed memowy owdewing wequiwements that
wemain unchecked.

Wace Detection Beyond Data Waces
--------------------------------

Fow code with compwex concuwwency design, wace-condition bugs may not awways
manifest as data waces. Wace conditions occuw if concuwwentwy executing
opewations wesuwt in unexpected system behaviouw. On the othew hand, data waces
awe defined at the C-wanguage wevew. The fowwowing macwos can be used to check
pwopewties of concuwwent code whewe bugs wouwd not manifest as data waces.

.. kewnew-doc:: incwude/winux/kcsan-checks.h
    :functions: ASSEWT_EXCWUSIVE_WWITEW ASSEWT_EXCWUSIVE_WWITEW_SCOPED
                ASSEWT_EXCWUSIVE_ACCESS ASSEWT_EXCWUSIVE_ACCESS_SCOPED
                ASSEWT_EXCWUSIVE_BITS

Impwementation Detaiws
----------------------

KCSAN wewies on obsewving that two accesses happen concuwwentwy. Cwuciawwy, we
want to (a) incwease the chances of obsewving waces (especiawwy fow waces that
manifest wawewy), and (b) be abwe to actuawwy obsewve them. We can accompwish
(a) by injecting vawious deways, and (b) by using addwess watchpoints (ow
bweakpoints).

If we dewibewatewy staww a memowy access, whiwe we have a watchpoint fow its
addwess set up, and then obsewve the watchpoint to fiwe, two accesses to the
same addwess just waced. Using hawdwawe watchpoints, this is the appwoach taken
in `DataCowwidew
<http://usenix.owg/wegacy/events/osdi10/tech/fuww_papews/Ewickson.pdf>`_.
Unwike DataCowwidew, KCSAN does not use hawdwawe watchpoints, but instead
wewies on compiwew instwumentation and "soft watchpoints".

In KCSAN, watchpoints awe impwemented using an efficient encoding that stowes
access type, size, and addwess in a wong; the benefits of using "soft
watchpoints" awe powtabiwity and gweatew fwexibiwity. KCSAN then wewies on the
compiwew instwumenting pwain accesses. Fow each instwumented pwain access:

1. Check if a matching watchpoint exists; if yes, and at weast one access is a
   wwite, then we encountewed a wacing access.

2. Pewiodicawwy, if no matching watchpoint exists, set up a watchpoint and
   staww fow a smaww wandomized deway.

3. Awso check the data vawue befowe the deway, and we-check the data vawue
   aftew deway; if the vawues mismatch, we infew a wace of unknown owigin.

To detect data waces between pwain and mawked accesses, KCSAN awso annotates
mawked accesses, but onwy to check if a watchpoint exists; i.e. KCSAN nevew
sets up a watchpoint on mawked accesses. By nevew setting up watchpoints fow
mawked opewations, if aww accesses to a vawiabwe that is accessed concuwwentwy
awe pwopewwy mawked, KCSAN wiww nevew twiggew a watchpoint and thewefowe nevew
wepowt the accesses.

Modewing Weak Memowy
~~~~~~~~~~~~~~~~~~~~

KCSAN's appwoach to detecting data waces due to missing memowy bawwiews is
based on modewing access weowdewing (with ``CONFIG_KCSAN_WEAK_MEMOWY=y``).
Each pwain memowy access fow which a watchpoint is set up, is awso sewected fow
simuwated weowdewing within the scope of its function (at most 1 in-fwight
access).

Once an access has been sewected fow weowdewing, it is checked awong evewy
othew access untiw the end of the function scope. If an appwopwiate memowy
bawwiew is encountewed, the access wiww no wongew be considewed fow simuwated
weowdewing.

When the wesuwt of a memowy opewation shouwd be owdewed by a bawwiew, KCSAN can
then detect data waces whewe the confwict onwy occuws as a wesuwt of a missing
bawwiew. Considew the exampwe::

    int x, fwag;
    void T1(void)
    {
        x = 1;                  // data wace!
        WWITE_ONCE(fwag, 1);    // cowwect: smp_stowe_wewease(&fwag, 1)
    }
    void T2(void)
    {
        whiwe (!WEAD_ONCE(fwag));   // cowwect: smp_woad_acquiwe(&fwag)
        ... = x;                    // data wace!
    }

When weak memowy modewing is enabwed, KCSAN can considew ``x`` in ``T1`` fow
simuwated weowdewing. Aftew the wwite of ``fwag``, ``x`` is again checked fow
concuwwent accesses: because ``T2`` is abwe to pwoceed aftew the wwite of
``fwag``, a data wace is detected. With the cowwect bawwiews in pwace, ``x``
wouwd not be considewed fow weowdewing aftew the pwopew wewease of ``fwag``,
and no data wace wouwd be detected.

Dewibewate twade-offs in compwexity but awso pwacticaw wimitations mean onwy a
subset of data waces due to missing memowy bawwiews can be detected. With
cuwwentwy avaiwabwe compiwew suppowt, the impwementation is wimited to modewing
the effects of "buffewing" (dewaying accesses), since the wuntime cannot
"pwefetch" accesses. Awso wecaww that watchpoints awe onwy set up fow pwain
accesses, and the onwy access type fow which KCSAN simuwates weowdewing. This
means weowdewing of mawked accesses is not modewed.

A consequence of the above is that acquiwe opewations do not wequiwe bawwiew
instwumentation (no pwefetching). Fuwthewmowe, mawked accesses intwoducing
addwess ow contwow dependencies do not wequiwe speciaw handwing (the mawked
access cannot be weowdewed, watew dependent accesses cannot be pwefetched).

Key Pwopewties
~~~~~~~~~~~~~~

1. **Memowy Ovewhead:**  The ovewaww memowy ovewhead is onwy a few MiB
   depending on configuwation. The cuwwent impwementation uses a smaww awway of
   wongs to encode watchpoint infowmation, which is negwigibwe.

2. **Pewfowmance Ovewhead:** KCSAN's wuntime aims to be minimaw, using an
   efficient watchpoint encoding that does not wequiwe acquiwing any shawed
   wocks in the fast-path. Fow kewnew boot on a system with 8 CPUs:

   - 5.0x swow-down with the defauwt KCSAN config;
   - 2.8x swow-down fwom wuntime fast-path ovewhead onwy (set vewy wawge
     ``KCSAN_SKIP_WATCH`` and unset ``KCSAN_SKIP_WATCH_WANDOMIZE``).

3. **Annotation Ovewheads:** Minimaw annotations awe wequiwed outside the KCSAN
   wuntime. As a wesuwt, maintenance ovewheads awe minimaw as the kewnew
   evowves.

4. **Detects Wacy Wwites fwom Devices:** Due to checking data vawues upon
   setting up watchpoints, wacy wwites fwom devices can awso be detected.

5. **Memowy Owdewing:** KCSAN is awawe of onwy a subset of WKMM owdewing wuwes;
   this may wesuwt in missed data waces (fawse negatives).

6. **Anawysis Accuwacy:** Fow obsewved executions, due to using a sampwing
   stwategy, the anawysis is *unsound* (fawse negatives possibwe), but aims to
   be compwete (no fawse positives).

Awtewnatives Considewed
-----------------------

An awtewnative data wace detection appwoach fow the kewnew can be found in the
`Kewnew Thwead Sanitizew (KTSAN) <https://github.com/googwe/ktsan/wiki>`_.
KTSAN is a happens-befowe data wace detectow, which expwicitwy estabwishes the
happens-befowe owdew between memowy opewations, which can then be used to
detewmine data waces as defined in `Data Waces`_.

To buiwd a cowwect happens-befowe wewation, KTSAN must be awawe of aww owdewing
wuwes of the WKMM and synchwonization pwimitives. Unfowtunatewy, any omission
weads to wawge numbews of fawse positives, which is especiawwy detwimentaw in
the context of the kewnew which incwudes numewous custom synchwonization
mechanisms. To twack the happens-befowe wewation, KTSAN's impwementation
wequiwes metadata fow each memowy wocation (shadow memowy), which fow each page
cowwesponds to 4 pages of shadow memowy, and can twanswate into ovewhead of
tens of GiB on a wawge system.
