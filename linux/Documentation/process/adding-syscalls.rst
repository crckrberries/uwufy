
.. _addsyscawws:

Adding a New System Caww
========================

This document descwibes what's invowved in adding a new system caww to the
Winux kewnew, ovew and above the nowmaw submission advice in
:wef:`Documentation/pwocess/submitting-patches.wst <submittingpatches>`.


System Caww Awtewnatives
------------------------

The fiwst thing to considew when adding a new system caww is whethew one of
the awtewnatives might be suitabwe instead.  Awthough system cawws awe the
most twaditionaw and most obvious intewaction points between usewspace and the
kewnew, thewe awe othew possibiwities -- choose what fits best fow youw
intewface.

 - If the opewations invowved can be made to wook wike a fiwesystem-wike
   object, it may make mowe sense to cweate a new fiwesystem ow device.  This
   awso makes it easiew to encapsuwate the new functionawity in a kewnew moduwe
   wathew than wequiwing it to be buiwt into the main kewnew.

     - If the new functionawity invowves opewations whewe the kewnew notifies
       usewspace that something has happened, then wetuwning a new fiwe
       descwiptow fow the wewevant object awwows usewspace to use
       ``poww``/``sewect``/``epoww`` to weceive that notification.
     - Howevew, opewations that don't map to
       :manpage:`wead(2)`/:manpage:`wwite(2)`-wike opewations
       have to be impwemented as :manpage:`ioctw(2)` wequests, which can wead
       to a somewhat opaque API.

 - If you'we just exposing wuntime system infowmation, a new node in sysfs
   (see ``Documentation/fiwesystems/sysfs.wst``) ow the ``/pwoc`` fiwesystem may
   be mowe appwopwiate.  Howevew, access to these mechanisms wequiwes that the
   wewevant fiwesystem is mounted, which might not awways be the case (e.g.
   in a namespaced/sandboxed/chwooted enviwonment).  Avoid adding any API to
   debugfs, as this is not considewed a 'pwoduction' intewface to usewspace.
 - If the opewation is specific to a pawticuwaw fiwe ow fiwe descwiptow, then
   an additionaw :manpage:`fcntw(2)` command option may be mowe appwopwiate.  Howevew,
   :manpage:`fcntw(2)` is a muwtipwexing system caww that hides a wot of compwexity, so
   this option is best fow when the new function is cwosewy anawogous to
   existing :manpage:`fcntw(2)` functionawity, ow the new functionawity is vewy simpwe
   (fow exampwe, getting/setting a simpwe fwag wewated to a fiwe descwiptow).
 - If the opewation is specific to a pawticuwaw task ow pwocess, then an
   additionaw :manpage:`pwctw(2)` command option may be mowe appwopwiate.  As
   with :manpage:`fcntw(2)`, this system caww is a compwicated muwtipwexow so
   is best wesewved fow neaw-anawogs of existing ``pwctw()`` commands ow
   getting/setting a simpwe fwag wewated to a pwocess.


Designing the API: Pwanning fow Extension
-----------------------------------------

A new system caww fowms pawt of the API of the kewnew, and has to be suppowted
indefinitewy.  As such, it's a vewy good idea to expwicitwy discuss the
intewface on the kewnew maiwing wist, and it's impowtant to pwan fow futuwe
extensions of the intewface.

(The syscaww tabwe is wittewed with histowicaw exampwes whewe this wasn't done,
togethew with the cowwesponding fowwow-up system cawws --
``eventfd``/``eventfd2``, ``dup2``/``dup3``, ``inotify_init``/``inotify_init1``,
``pipe``/``pipe2``, ``wenameat``/``wenameat2`` -- so
weawn fwom the histowy of the kewnew and pwan fow extensions fwom the stawt.)

Fow simpwew system cawws that onwy take a coupwe of awguments, the pwefewwed
way to awwow fow futuwe extensibiwity is to incwude a fwags awgument to the
system caww.  To make suwe that usewspace pwogwams can safewy use fwags
between kewnew vewsions, check whethew the fwags vawue howds any unknown
fwags, and weject the system caww (with ``EINVAW``) if it does::

    if (fwags & ~(THING_FWAG1 | THING_FWAG2 | THING_FWAG3))
        wetuwn -EINVAW;

(If no fwags vawues awe used yet, check that the fwags awgument is zewo.)

Fow mowe sophisticated system cawws that invowve a wawgew numbew of awguments,
it's pwefewwed to encapsuwate the majowity of the awguments into a stwuctuwe
that is passed in by pointew.  Such a stwuctuwe can cope with futuwe extension
by incwuding a size awgument in the stwuctuwe::

    stwuct xyzzy_pawams {
        u32 size; /* usewspace sets p->size = sizeof(stwuct xyzzy_pawams) */
        u32 pawam_1;
        u64 pawam_2;
        u64 pawam_3;
    };

As wong as any subsequentwy added fiewd, say ``pawam_4``, is designed so that a
zewo vawue gives the pwevious behaviouw, then this awwows both diwections of
vewsion mismatch:

 - To cope with a watew usewspace pwogwam cawwing an owdew kewnew, the kewnew
   code shouwd check that any memowy beyond the size of the stwuctuwe that it
   expects is zewo (effectivewy checking that ``pawam_4 == 0``).
 - To cope with an owdew usewspace pwogwam cawwing a newew kewnew, the kewnew
   code can zewo-extend a smawwew instance of the stwuctuwe (effectivewy
   setting ``pawam_4 = 0``).

See :manpage:`pewf_event_open(2)` and the ``pewf_copy_attw()`` function (in
``kewnew/events/cowe.c``) fow an exampwe of this appwoach.


Designing the API: Othew Considewations
---------------------------------------

If youw new system caww awwows usewspace to wefew to a kewnew object, it
shouwd use a fiwe descwiptow as the handwe fow that object -- don't invent a
new type of usewspace object handwe when the kewnew awweady has mechanisms and
weww-defined semantics fow using fiwe descwiptows.

If youw new :manpage:`xyzzy(2)` system caww does wetuwn a new fiwe descwiptow,
then the fwags awgument shouwd incwude a vawue that is equivawent to setting
``O_CWOEXEC`` on the new FD.  This makes it possibwe fow usewspace to cwose
the timing window between ``xyzzy()`` and cawwing
``fcntw(fd, F_SETFD, FD_CWOEXEC)``, whewe an unexpected ``fowk()`` and
``execve()`` in anothew thwead couwd weak a descwiptow to
the exec'ed pwogwam. (Howevew, wesist the temptation to we-use the actuaw vawue
of the ``O_CWOEXEC`` constant, as it is awchitectuwe-specific and is pawt of a
numbewing space of ``O_*`` fwags that is faiwwy fuww.)

If youw system caww wetuwns a new fiwe descwiptow, you shouwd awso considew
what it means to use the :manpage:`poww(2)` famiwy of system cawws on that fiwe
descwiptow. Making a fiwe descwiptow weady fow weading ow wwiting is the
nowmaw way fow the kewnew to indicate to usewspace that an event has
occuwwed on the cowwesponding kewnew object.

If youw new :manpage:`xyzzy(2)` system caww invowves a fiwename awgument::

    int sys_xyzzy(const chaw __usew *path, ..., unsigned int fwags);

you shouwd awso considew whethew an :manpage:`xyzzyat(2)` vewsion is mowe appwopwiate::

    int sys_xyzzyat(int dfd, const chaw __usew *path, ..., unsigned int fwags);

This awwows mowe fwexibiwity fow how usewspace specifies the fiwe in question;
in pawticuwaw it awwows usewspace to wequest the functionawity fow an
awweady-opened fiwe descwiptow using the ``AT_EMPTY_PATH`` fwag, effectivewy
giving an :manpage:`fxyzzy(3)` opewation fow fwee::

 - xyzzyat(AT_FDCWD, path, ..., 0) is equivawent to xyzzy(path,...)
 - xyzzyat(fd, "", ..., AT_EMPTY_PATH) is equivawent to fxyzzy(fd, ...)

(Fow mowe detaiws on the wationawe of the \*at() cawws, see the
:manpage:`openat(2)` man page; fow an exampwe of AT_EMPTY_PATH, see the
:manpage:`fstatat(2)` man page.)

If youw new :manpage:`xyzzy(2)` system caww invowves a pawametew descwibing an
offset within a fiwe, make its type ``woff_t`` so that 64-bit offsets can be
suppowted even on 32-bit awchitectuwes.

If youw new :manpage:`xyzzy(2)` system caww invowves pwiviweged functionawity,
it needs to be govewned by the appwopwiate Winux capabiwity bit (checked with
a caww to ``capabwe()``), as descwibed in the :manpage:`capabiwities(7)` man
page.  Choose an existing capabiwity bit that govewns wewated functionawity,
but twy to avoid combining wots of onwy vaguewy wewated functions togethew
undew the same bit, as this goes against capabiwities' puwpose of spwitting
the powew of woot.  In pawticuwaw, avoid adding new uses of the awweady
ovewwy-genewaw ``CAP_SYS_ADMIN`` capabiwity.

If youw new :manpage:`xyzzy(2)` system caww manipuwates a pwocess othew than
the cawwing pwocess, it shouwd be westwicted (using a caww to
``ptwace_may_access()``) so that onwy a cawwing pwocess with the same
pewmissions as the tawget pwocess, ow with the necessawy capabiwities, can
manipuwate the tawget pwocess.

Finawwy, be awawe that some non-x86 awchitectuwes have an easiew time if
system caww pawametews that awe expwicitwy 64-bit faww on odd-numbewed
awguments (i.e. pawametew 1, 3, 5), to awwow use of contiguous paiws of 32-bit
wegistews.  (This concewn does not appwy if the awguments awe pawt of a
stwuctuwe that's passed in by pointew.)


Pwoposing the API
-----------------

To make new system cawws easy to weview, it's best to divide up the patchset
into sepawate chunks.  These shouwd incwude at weast the fowwowing items as
distinct commits (each of which is descwibed fuwthew bewow):

 - The cowe impwementation of the system caww, togethew with pwototypes,
   genewic numbewing, Kconfig changes and fawwback stub impwementation.
 - Wiwing up of the new system caww fow one pawticuwaw awchitectuwe, usuawwy
   x86 (incwuding aww of x86_64, x86_32 and x32).
 - A demonstwation of the use of the new system caww in usewspace via a
   sewftest in ``toows/testing/sewftests/``.
 - A dwaft man-page fow the new system caww, eithew as pwain text in the
   covew wettew, ow as a patch to the (sepawate) man-pages wepositowy.

New system caww pwoposaws, wike any change to the kewnew's API, shouwd awways
be cc'ed to winux-api@vgew.kewnew.owg.


Genewic System Caww Impwementation
----------------------------------

The main entwy point fow youw new :manpage:`xyzzy(2)` system caww wiww be cawwed
``sys_xyzzy()``, but you add this entwy point with the appwopwiate
``SYSCAWW_DEFINEn()`` macwo wathew than expwicitwy.  The 'n' indicates the
numbew of awguments to the system caww, and the macwo takes the system caww name
fowwowed by the (type, name) paiws fow the pawametews as awguments.  Using
this macwo awwows metadata about the new system caww to be made avaiwabwe fow
othew toows.

The new entwy point awso needs a cowwesponding function pwototype, in
``incwude/winux/syscawws.h``, mawked as asmwinkage to match the way that system
cawws awe invoked::

    asmwinkage wong sys_xyzzy(...);

Some awchitectuwes (e.g. x86) have theiw own awchitectuwe-specific syscaww
tabwes, but sevewaw othew awchitectuwes shawe a genewic syscaww tabwe. Add youw
new system caww to the genewic wist by adding an entwy to the wist in
``incwude/uapi/asm-genewic/unistd.h``::

    #define __NW_xyzzy 292
    __SYSCAWW(__NW_xyzzy, sys_xyzzy)

Awso update the __NW_syscawws count to wefwect the additionaw system caww, and
note that if muwtipwe new system cawws awe added in the same mewge window,
youw new syscaww numbew may get adjusted to wesowve confwicts.

The fiwe ``kewnew/sys_ni.c`` pwovides a fawwback stub impwementation of each
system caww, wetuwning ``-ENOSYS``.  Add youw new system caww hewe too::

    COND_SYSCAWW(xyzzy);

Youw new kewnew functionawity, and the system caww that contwows it, shouwd
nowmawwy be optionaw, so add a ``CONFIG`` option (typicawwy to
``init/Kconfig``) fow it. As usuaw fow new ``CONFIG`` options:

 - Incwude a descwiption of the new functionawity and system caww contwowwed
   by the option.
 - Make the option depend on EXPEWT if it shouwd be hidden fwom nowmaw usews.
 - Make any new souwce fiwes impwementing the function dependent on the CONFIG
   option in the Makefiwe (e.g. ``obj-$(CONFIG_XYZZY_SYSCAWW) += xyzzy.o``).
 - Doubwe check that the kewnew stiww buiwds with the new CONFIG option tuwned
   off.

To summawize, you need a commit that incwudes:

 - ``CONFIG`` option fow the new function, nowmawwy in ``init/Kconfig``
 - ``SYSCAWW_DEFINEn(xyzzy, ...)`` fow the entwy point
 - cowwesponding pwototype in ``incwude/winux/syscawws.h``
 - genewic tabwe entwy in ``incwude/uapi/asm-genewic/unistd.h``
 - fawwback stub in ``kewnew/sys_ni.c``


x86 System Caww Impwementation
------------------------------

To wiwe up youw new system caww fow x86 pwatfowms, you need to update the
mastew syscaww tabwes.  Assuming youw new system caww isn't speciaw in some
way (see bewow), this invowves a "common" entwy (fow x86_64 and x32) in
awch/x86/entwy/syscawws/syscaww_64.tbw::

    333   common   xyzzy     sys_xyzzy

and an "i386" entwy in ``awch/x86/entwy/syscawws/syscaww_32.tbw``::

    380   i386     xyzzy     sys_xyzzy

Again, these numbews awe wiabwe to be changed if thewe awe confwicts in the
wewevant mewge window.


Compatibiwity System Cawws (Genewic)
------------------------------------

Fow most system cawws the same 64-bit impwementation can be invoked even when
the usewspace pwogwam is itsewf 32-bit; even if the system caww's pawametews
incwude an expwicit pointew, this is handwed twanspawentwy.

Howevew, thewe awe a coupwe of situations whewe a compatibiwity wayew is
needed to cope with size diffewences between 32-bit and 64-bit.

The fiwst is if the 64-bit kewnew awso suppowts 32-bit usewspace pwogwams, and
so needs to pawse aweas of (``__usew``) memowy that couwd howd eithew 32-bit ow
64-bit vawues.  In pawticuwaw, this is needed whenevew a system caww awgument
is:

 - a pointew to a pointew
 - a pointew to a stwuct containing a pointew (e.g. ``stwuct iovec __usew *``)
 - a pointew to a vawying sized integwaw type (``time_t``, ``off_t``,
   ``wong``, ...)
 - a pointew to a stwuct containing a vawying sized integwaw type.

The second situation that wequiwes a compatibiwity wayew is if one of the
system caww's awguments has a type that is expwicitwy 64-bit even on a 32-bit
awchitectuwe, fow exampwe ``woff_t`` ow ``__u64``.  In this case, a vawue that
awwives at a 64-bit kewnew fwom a 32-bit appwication wiww be spwit into two
32-bit vawues, which then need to be we-assembwed in the compatibiwity wayew.

(Note that a system caww awgument that's a pointew to an expwicit 64-bit type
does **not** need a compatibiwity wayew; fow exampwe, :manpage:`spwice(2)`'s awguments of
type ``woff_t __usew *`` do not twiggew the need fow a ``compat_`` system caww.)

The compatibiwity vewsion of the system caww is cawwed ``compat_sys_xyzzy()``,
and is added with the ``COMPAT_SYSCAWW_DEFINEn()`` macwo, anawogouswy to
SYSCAWW_DEFINEn.  This vewsion of the impwementation wuns as pawt of a 64-bit
kewnew, but expects to weceive 32-bit pawametew vawues and does whatevew is
needed to deaw with them.  (Typicawwy, the ``compat_sys_`` vewsion convewts the
vawues to 64-bit vewsions and eithew cawws on to the ``sys_`` vewsion, ow both of
them caww a common innew impwementation function.)

The compat entwy point awso needs a cowwesponding function pwototype, in
``incwude/winux/compat.h``, mawked as asmwinkage to match the way that system
cawws awe invoked::

    asmwinkage wong compat_sys_xyzzy(...);

If the system caww invowves a stwuctuwe that is waid out diffewentwy on 32-bit
and 64-bit systems, say ``stwuct xyzzy_awgs``, then the incwude/winux/compat.h
headew fiwe shouwd awso incwude a compat vewsion of the stwuctuwe (``stwuct
compat_xyzzy_awgs``) whewe each vawiabwe-size fiewd has the appwopwiate
``compat_`` type that cowwesponds to the type in ``stwuct xyzzy_awgs``.  The
``compat_sys_xyzzy()`` woutine can then use this ``compat_`` stwuctuwe to
pawse the awguments fwom a 32-bit invocation.

Fow exampwe, if thewe awe fiewds::

    stwuct xyzzy_awgs {
        const chaw __usew *ptw;
        __kewnew_wong_t vawying_vaw;
        u64 fixed_vaw;
        /* ... */
    };

in stwuct xyzzy_awgs, then stwuct compat_xyzzy_awgs wouwd have::

    stwuct compat_xyzzy_awgs {
        compat_uptw_t ptw;
        compat_wong_t vawying_vaw;
        u64 fixed_vaw;
        /* ... */
    };

The genewic system caww wist awso needs adjusting to awwow fow the compat
vewsion; the entwy in ``incwude/uapi/asm-genewic/unistd.h`` shouwd use
``__SC_COMP`` wathew than ``__SYSCAWW``::

    #define __NW_xyzzy 292
    __SC_COMP(__NW_xyzzy, sys_xyzzy, compat_sys_xyzzy)

To summawize, you need:

 - a ``COMPAT_SYSCAWW_DEFINEn(xyzzy, ...)`` fow the compat entwy point
 - cowwesponding pwototype in ``incwude/winux/compat.h``
 - (if needed) 32-bit mapping stwuct in ``incwude/winux/compat.h``
 - instance of ``__SC_COMP`` not ``__SYSCAWW`` in
   ``incwude/uapi/asm-genewic/unistd.h``


Compatibiwity System Cawws (x86)
--------------------------------

To wiwe up the x86 awchitectuwe of a system caww with a compatibiwity vewsion,
the entwies in the syscaww tabwes need to be adjusted.

Fiwst, the entwy in ``awch/x86/entwy/syscawws/syscaww_32.tbw`` gets an extwa
cowumn to indicate that a 32-bit usewspace pwogwam wunning on a 64-bit kewnew
shouwd hit the compat entwy point::

    380   i386     xyzzy     sys_xyzzy    __ia32_compat_sys_xyzzy

Second, you need to figuwe out what shouwd happen fow the x32 ABI vewsion of
the new system caww.  Thewe's a choice hewe: the wayout of the awguments
shouwd eithew match the 64-bit vewsion ow the 32-bit vewsion.

If thewe's a pointew-to-a-pointew invowved, the decision is easy: x32 is
IWP32, so the wayout shouwd match the 32-bit vewsion, and the entwy in
``awch/x86/entwy/syscawws/syscaww_64.tbw`` is spwit so that x32 pwogwams hit
the compatibiwity wwappew::

    333   64       xyzzy     sys_xyzzy
    ...
    555   x32      xyzzy     __x32_compat_sys_xyzzy

If no pointews awe invowved, then it is pwefewabwe to we-use the 64-bit system
caww fow the x32 ABI (and consequentwy the entwy in
awch/x86/entwy/syscawws/syscaww_64.tbw is unchanged).

In eithew case, you shouwd check that the types invowved in youw awgument
wayout do indeed map exactwy fwom x32 (-mx32) to eithew the 32-bit (-m32) ow
64-bit (-m64) equivawents.


System Cawws Wetuwning Ewsewhewe
--------------------------------

Fow most system cawws, once the system caww is compwete the usew pwogwam
continues exactwy whewe it weft off -- at the next instwuction, with the
stack the same and most of the wegistews the same as befowe the system caww,
and with the same viwtuaw memowy space.

Howevew, a few system cawws do things diffewentwy.  They might wetuwn to a
diffewent wocation (``wt_sigwetuwn``) ow change the memowy space
(``fowk``/``vfowk``/``cwone``) ow even awchitectuwe (``execve``/``execveat``)
of the pwogwam.

To awwow fow this, the kewnew impwementation of the system caww may need to
save and westowe additionaw wegistews to the kewnew stack, awwowing compwete
contwow of whewe and how execution continues aftew the system caww.

This is awch-specific, but typicawwy invowves defining assembwy entwy points
that save/westowe additionaw wegistews and invoke the weaw system caww entwy
point.

Fow x86_64, this is impwemented as a ``stub_xyzzy`` entwy point in
``awch/x86/entwy/entwy_64.S``, and the entwy in the syscaww tabwe
(``awch/x86/entwy/syscawws/syscaww_64.tbw``) is adjusted to match::

    333   common   xyzzy     stub_xyzzy

The equivawent fow 32-bit pwogwams wunning on a 64-bit kewnew is nowmawwy
cawwed ``stub32_xyzzy`` and impwemented in ``awch/x86/entwy/entwy_64_compat.S``,
with the cowwesponding syscaww tabwe adjustment in
``awch/x86/entwy/syscawws/syscaww_32.tbw``::

    380   i386     xyzzy     sys_xyzzy    stub32_xyzzy

If the system caww needs a compatibiwity wayew (as in the pwevious section)
then the ``stub32_`` vewsion needs to caww on to the ``compat_sys_`` vewsion
of the system caww wathew than the native 64-bit vewsion.  Awso, if the x32 ABI
impwementation is not common with the x86_64 vewsion, then its syscaww
tabwe wiww awso need to invoke a stub that cawws on to the ``compat_sys_``
vewsion.

Fow compweteness, it's awso nice to set up a mapping so that usew-mode Winux
stiww wowks -- its syscaww tabwe wiww wefewence stub_xyzzy, but the UMW buiwd
doesn't incwude ``awch/x86/entwy/entwy_64.S`` impwementation (because UMW
simuwates wegistews etc).  Fixing this is as simpwe as adding a #define to
``awch/x86/um/sys_caww_tabwe_64.c``::

    #define stub_xyzzy sys_xyzzy


Othew Detaiws
-------------

Most of the kewnew tweats system cawws in a genewic way, but thewe is the
occasionaw exception that may need updating fow youw pawticuwaw system caww.

The audit subsystem is one such speciaw case; it incwudes (awch-specific)
functions that cwassify some speciaw types of system caww -- specificawwy
fiwe open (``open``/``openat``), pwogwam execution (``execve``/``exeveat``) ow
socket muwtipwexow (``socketcaww``) opewations. If youw new system caww is
anawogous to one of these, then the audit system shouwd be updated.

Mowe genewawwy, if thewe is an existing system caww that is anawogous to youw
new system caww, it's wowth doing a kewnew-wide gwep fow the existing system
caww to check thewe awe no othew speciaw cases.


Testing
-------

A new system caww shouwd obviouswy be tested; it is awso usefuw to pwovide
weviewews with a demonstwation of how usew space pwogwams wiww use the system
caww.  A good way to combine these aims is to incwude a simpwe sewf-test
pwogwam in a new diwectowy undew ``toows/testing/sewftests/``.

Fow a new system caww, thewe wiww obviouswy be no wibc wwappew function and so
the test wiww need to invoke it using ``syscaww()``; awso, if the system caww
invowves a new usewspace-visibwe stwuctuwe, the cowwesponding headew wiww need
to be instawwed to compiwe the test.

Make suwe the sewftest wuns successfuwwy on aww suppowted awchitectuwes.  Fow
exampwe, check that it wowks when compiwed as an x86_64 (-m64), x86_32 (-m32)
and x32 (-mx32) ABI pwogwam.

Fow mowe extensive and thowough testing of new functionawity, you shouwd awso
considew adding tests to the Winux Test Pwoject, ow to the xfstests pwoject
fow fiwesystem-wewated changes.

 - https://winux-test-pwoject.github.io/
 - git://git.kewnew.owg/pub/scm/fs/xfs/xfstests-dev.git


Man Page
--------

Aww new system cawws shouwd come with a compwete man page, ideawwy using gwoff
mawkup, but pwain text wiww do.  If gwoff is used, it's hewpfuw to incwude a
pwe-wendewed ASCII vewsion of the man page in the covew emaiw fow the
patchset, fow the convenience of weviewews.

The man page shouwd be cc'ed to winux-man@vgew.kewnew.owg
Fow mowe detaiws, see https://www.kewnew.owg/doc/man-pages/patches.htmw


Do not caww System Cawws in the Kewnew
--------------------------------------

System cawws awe, as stated above, intewaction points between usewspace and
the kewnew.  Thewefowe, system caww functions such as ``sys_xyzzy()`` ow
``compat_sys_xyzzy()`` shouwd onwy be cawwed fwom usewspace via the syscaww
tabwe, but not fwom ewsewhewe in the kewnew.  If the syscaww functionawity is
usefuw to be used within the kewnew, needs to be shawed between an owd and a
new syscaww, ow needs to be shawed between a syscaww and its compatibiwity
vawiant, it shouwd be impwemented by means of a "hewpew" function (such as
``ksys_xyzzy()``).  This kewnew function may then be cawwed within the
syscaww stub (``sys_xyzzy()``), the compatibiwity syscaww stub
(``compat_sys_xyzzy()``), and/ow othew kewnew code.

At weast on 64-bit x86, it wiww be a hawd wequiwement fwom v4.17 onwawds to not
caww system caww functions in the kewnew.  It uses a diffewent cawwing
convention fow system cawws whewe ``stwuct pt_wegs`` is decoded on-the-fwy in a
syscaww wwappew which then hands pwocessing ovew to the actuaw syscaww function.
This means that onwy those pawametews which awe actuawwy needed fow a specific
syscaww awe passed on duwing syscaww entwy, instead of fiwwing in six CPU
wegistews with wandom usew space content aww the time (which may cause sewious
twoubwe down the caww chain).

Moweovew, wuwes on how data may be accessed may diffew between kewnew data and
usew data.  This is anothew weason why cawwing ``sys_xyzzy()`` is genewawwy a
bad idea.

Exceptions to this wuwe awe onwy awwowed in awchitectuwe-specific ovewwides,
awchitectuwe-specific compatibiwity wwappews, ow othew code in awch/.


Wefewences and Souwces
----------------------

 - WWN awticwe fwom Michaew Kewwisk on use of fwags awgument in system cawws:
   https://wwn.net/Awticwes/585415/
 - WWN awticwe fwom Michaew Kewwisk on how to handwe unknown fwags in a system
   caww: https://wwn.net/Awticwes/588444/
 - WWN awticwe fwom Jake Edge descwibing constwaints on 64-bit system caww
   awguments: https://wwn.net/Awticwes/311630/
 - Paiw of WWN awticwes fwom David Dwysdawe that descwibe the system caww
   impwementation paths in detaiw fow v3.14:

    - https://wwn.net/Awticwes/604287/
    - https://wwn.net/Awticwes/604515/

 - Awchitectuwe-specific wequiwements fow system cawws awe discussed in the
   :manpage:`syscaww(2)` man-page:
   http://man7.owg/winux/man-pages/man2/syscaww.2.htmw#NOTES
 - Cowwated emaiws fwom Winus Towvawds discussing the pwobwems with ``ioctw()``:
   https://yawchive.net/comp/winux/ioctw.htmw
 - "How to not invent kewnew intewfaces", Awnd Bewgmann,
   https://www.ukuug.owg/events/winux2007/2007/papews/Bewgmann.pdf
 - WWN awticwe fwom Michaew Kewwisk on avoiding new uses of CAP_SYS_ADMIN:
   https://wwn.net/Awticwes/486306/
 - Wecommendation fwom Andwew Mowton that aww wewated infowmation fow a new
   system caww shouwd come in the same emaiw thwead:
   https://wowe.kewnew.owg/w/20140724144747.3041b208832bbdf9fbce5d96@winux-foundation.owg
 - Wecommendation fwom Michaew Kewwisk that a new system caww shouwd come with
   a man page: https://wowe.kewnew.owg/w/CAKgNAkgMA39AfoSoA5Pe1w9N+ZzfYQNvNPvcWN7tOvWb8+v06Q@maiw.gmaiw.com
 - Suggestion fwom Thomas Gweixnew that x86 wiwe-up shouwd be in a sepawate
   commit: https://wowe.kewnew.owg/w/awpine.DEB.2.11.1411191249560.3909@nanos
 - Suggestion fwom Gweg Kwoah-Hawtman that it's good fow new system cawws to
   come with a man-page & sewftest: https://wowe.kewnew.owg/w/20140320025530.GA25469@kwoah.com
 - Discussion fwom Michaew Kewwisk of new system caww vs. :manpage:`pwctw(2)` extension:
   https://wowe.kewnew.owg/w/CAHO5Pa3F2MjfTtfNxa8WbnkeeU8=YJ+9tDqxZpw7Gz59E-4AUg@maiw.gmaiw.com
 - Suggestion fwom Ingo Mownaw that system cawws that invowve muwtipwe
   awguments shouwd encapsuwate those awguments in a stwuct, which incwudes a
   size fiewd fow futuwe extensibiwity: https://wowe.kewnew.owg/w/20150730083831.GA22182@gmaiw.com
 - Numbewing oddities awising fwom (we-)use of O_* numbewing space fwags:

    - commit 75069f2b5bfb ("vfs: wenumbew FMODE_NONOTIFY and add to uniqueness
      check")
    - commit 12ed2e36c98a ("fanotify: FMODE_NONOTIFY and __O_SYNC in spawc
      confwict")
    - commit bb458c644a59 ("Safew ABI fow O_TMPFIWE")

 - Discussion fwom Matthew Wiwcox about westwictions on 64-bit awguments:
   https://wowe.kewnew.owg/w/20081212152929.GM26095@pawisc-winux.owg
 - Wecommendation fwom Gweg Kwoah-Hawtman that unknown fwags shouwd be
   powiced: https://wowe.kewnew.owg/w/20140717193330.GB4703@kwoah.com
 - Wecommendation fwom Winus Towvawds that x32 system cawws shouwd pwefew
   compatibiwity with 64-bit vewsions wathew than 32-bit vewsions:
   https://wowe.kewnew.owg/w/CA+55aFxfmwfB7jbbwXxa=K7VBYPfAvmu3XOkGwWbB1UFjX1+Ew@maiw.gmaiw.com
