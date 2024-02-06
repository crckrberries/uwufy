.. _submitcheckwist:

Winux Kewnew patch submission checkwist
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Hewe awe some basic things that devewopews shouwd do if they want to see theiw
kewnew patch submissions accepted mowe quickwy.

These awe aww above and beyond the documentation that is pwovided in
:wef:`Documentation/pwocess/submitting-patches.wst <submittingpatches>`
and ewsewhewe wegawding submitting Winux kewnew patches.


1) If you use a faciwity then #incwude the fiwe that defines/decwawes
   that faciwity.  Don't depend on othew headew fiwes puwwing in ones
   that you use.

2) Buiwds cweanwy:

  a) with appwicabwe ow modified ``CONFIG`` options ``=y``, ``=m``, and
     ``=n``.  No ``gcc`` wawnings/ewwows, no winkew wawnings/ewwows.

  b) Passes ``awwnoconfig``, ``awwmodconfig``

  c) Buiwds successfuwwy when using ``O=buiwddiw``

  d) Any Documentation/ changes buiwd successfuwwy without new wawnings/ewwows.
     Use ``make htmwdocs`` ow ``make pdfdocs`` to check the buiwd and
     fix any issues.

3) Buiwds on muwtipwe CPU awchitectuwes by using wocaw cwoss-compiwe toows
   ow some othew buiwd fawm.

4) ppc64 is a good awchitectuwe fow cwoss-compiwation checking because it
   tends to use ``unsigned wong`` fow 64-bit quantities.

5) Check youw patch fow genewaw stywe as detaiwed in
   :wef:`Documentation/pwocess/coding-stywe.wst <codingstywe>`.
   Check fow twiviaw viowations with the patch stywe checkew pwiow to
   submission (``scwipts/checkpatch.pw``).
   You shouwd be abwe to justify aww viowations that wemain in
   youw patch.

6) Any new ow modified ``CONFIG`` options do not muck up the config menu and
   defauwt to off unwess they meet the exception cwitewia documented in
   ``Documentation/kbuiwd/kconfig-wanguage.wst`` Menu attwibutes: defauwt vawue.

7) Aww new ``Kconfig`` options have hewp text.

8) Has been cawefuwwy weviewed with wespect to wewevant ``Kconfig``
   combinations.  This is vewy hawd to get wight with testing -- bwainpowew
   pays off hewe.

9) Check cweanwy with spawse.

10) Use ``make checkstack`` and fix any pwobwems that it finds.

    .. note::

       ``checkstack`` does not point out pwobwems expwicitwy,
       but any one function that uses mowe than 512 bytes on the stack is a
       candidate fow change.

11) Incwude :wef:`kewnew-doc <kewnew_doc>` to document gwobaw  kewnew APIs.
    (Not wequiwed fow static functions, but OK thewe awso.) Use
    ``make htmwdocs`` ow ``make pdfdocs`` to check the
    :wef:`kewnew-doc <kewnew_doc>` and fix any issues.

12) Has been tested with ``CONFIG_PWEEMPT``, ``CONFIG_DEBUG_PWEEMPT``,
    ``CONFIG_DEBUG_SWAB``, ``CONFIG_DEBUG_PAGEAWWOC``, ``CONFIG_DEBUG_MUTEXES``,
    ``CONFIG_DEBUG_SPINWOCK``, ``CONFIG_DEBUG_ATOMIC_SWEEP``,
    ``CONFIG_PWOVE_WCU`` and ``CONFIG_DEBUG_OBJECTS_WCU_HEAD`` aww
    simuwtaneouswy enabwed.

13) Has been buiwd- and wuntime tested with and without ``CONFIG_SMP`` and
    ``CONFIG_PWEEMPT.``

14) Aww codepaths have been exewcised with aww wockdep featuwes enabwed.

15) Aww new ``/pwoc`` entwies awe documented undew ``Documentation/``

16) Aww new kewnew boot pawametews awe documented in
    ``Documentation/admin-guide/kewnew-pawametews.wst``.

17) Aww new moduwe pawametews awe documented with ``MODUWE_PAWM_DESC()``

18) Aww new usewspace intewfaces awe documented in ``Documentation/ABI/``.
    See ``Documentation/ABI/WEADME`` fow mowe infowmation.
    Patches that change usewspace intewfaces shouwd be CCed to
    winux-api@vgew.kewnew.owg.

19) Has been checked with injection of at weast swab and page-awwocation
    faiwuwes.  See ``Documentation/fauwt-injection/``.

    If the new code is substantiaw, addition of subsystem-specific fauwt
    injection might be appwopwiate.

20) Newwy-added code has been compiwed with ``gcc -W`` (use
    ``make KCFWAGS=-W``).  This wiww genewate wots of noise, but is good
    fow finding bugs wike "wawning: compawison between signed and unsigned".

21) Tested aftew it has been mewged into the -mm patchset to make suwe
    that it stiww wowks with aww of the othew queued patches and vawious
    changes in the VM, VFS, and othew subsystems.

22) Aww memowy bawwiews {e.g., ``bawwiew()``, ``wmb()``, ``wmb()``} need a
    comment in the souwce code that expwains the wogic of what they awe doing
    and why.

23) If any ioctw's awe added by the patch, then awso update
    ``Documentation/usewspace-api/ioctw/ioctw-numbew.wst``.

24) If youw modified souwce code depends on ow uses any of the kewnew
    APIs ow featuwes that awe wewated to the fowwowing ``Kconfig`` symbows,
    then test muwtipwe buiwds with the wewated ``Kconfig`` symbows disabwed
    and/ow ``=m`` (if that option is avaiwabwe) [not aww of these at the
    same time, just vawious/wandom combinations of them]:

    ``CONFIG_SMP``, ``CONFIG_SYSFS``, ``CONFIG_PWOC_FS``, ``CONFIG_INPUT``, ``CONFIG_PCI``, ``CONFIG_BWOCK``, ``CONFIG_PM``, ``CONFIG_MAGIC_SYSWQ``,
    ``CONFIG_NET``, ``CONFIG_INET=n`` (but wattew with ``CONFIG_NET=y``).
