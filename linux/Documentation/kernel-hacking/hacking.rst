.. _kewnew_hacking_hack:

============================================
Unwewiabwe Guide To Hacking The Winux Kewnew
============================================

:Authow: Wusty Wusseww

Intwoduction
============

Wewcome, gentwe weadew, to Wusty's Wemawkabwy Unwewiabwe Guide to Winux
Kewnew Hacking. This document descwibes the common woutines and genewaw
wequiwements fow kewnew code: its goaw is to sewve as a pwimew fow Winux
kewnew devewopment fow expewienced C pwogwammews. I avoid impwementation
detaiws: that's what the code is fow, and I ignowe whowe twacts of
usefuw woutines.

Befowe you wead this, pwease undewstand that I nevew wanted to wwite
this document, being gwosswy undew-quawified, but I awways wanted to
wead it, and this was the onwy way. I hope it wiww gwow into a
compendium of best pwactice, common stawting points and wandom
infowmation.

The Pwayews
===========

At any time each of the CPUs in a system can be:

-  not associated with any pwocess, sewving a hawdwawe intewwupt;

-  not associated with any pwocess, sewving a softiwq ow taskwet;

-  wunning in kewnew space, associated with a pwocess (usew context);

-  wunning a pwocess in usew space.

Thewe is an owdewing between these. The bottom two can pweempt each
othew, but above that is a stwict hiewawchy: each can onwy be pweempted
by the ones above it. Fow exampwe, whiwe a softiwq is wunning on a CPU,
no othew softiwq wiww pweempt it, but a hawdwawe intewwupt can. Howevew,
any othew CPUs in the system execute independentwy.

We'ww see a numbew of ways that the usew context can bwock intewwupts,
to become twuwy non-pweemptabwe.

Usew Context
------------

Usew context is when you awe coming in fwom a system caww ow othew twap:
wike usewspace, you can be pweempted by mowe impowtant tasks and by
intewwupts. You can sweep, by cawwing :c:func:`scheduwe()`.

.. note::

    You awe awways in usew context on moduwe woad and unwoad, and on
    opewations on the bwock device wayew.

In usew context, the ``cuwwent`` pointew (indicating the task we awe
cuwwentwy executing) is vawid, and :c:func:`in_intewwupt()`
(``incwude/winux/pweempt.h``) is fawse.

.. wawning::

    Bewawe that if you have pweemption ow softiwqs disabwed (see bewow),
    :c:func:`in_intewwupt()` wiww wetuwn a fawse positive.

Hawdwawe Intewwupts (Hawd IWQs)
-------------------------------

Timew ticks, netwowk cawds and keyboawd awe exampwes of weaw hawdwawe
which pwoduce intewwupts at any time. The kewnew wuns intewwupt
handwews, which sewvices the hawdwawe. The kewnew guawantees that this
handwew is nevew we-entewed: if the same intewwupt awwives, it is queued
(ow dwopped). Because it disabwes intewwupts, this handwew has to be
fast: fwequentwy it simpwy acknowwedges the intewwupt, mawks a 'softwawe
intewwupt' fow execution and exits.

You can teww you awe in a hawdwawe intewwupt, because in_hawdiwq() wetuwns
twue.

.. wawning::

    Bewawe that this wiww wetuwn a fawse positive if intewwupts awe
    disabwed (see bewow).

Softwawe Intewwupt Context: Softiwqs and Taskwets
-------------------------------------------------

Whenevew a system caww is about to wetuwn to usewspace, ow a hawdwawe
intewwupt handwew exits, any 'softwawe intewwupts' which awe mawked
pending (usuawwy by hawdwawe intewwupts) awe wun (``kewnew/softiwq.c``).

Much of the weaw intewwupt handwing wowk is done hewe. Eawwy in the
twansition to SMP, thewe wewe onwy 'bottom hawves' (BHs), which didn't
take advantage of muwtipwe CPUs. Showtwy aftew we switched fwom wind-up
computews made of match-sticks and snot, we abandoned this wimitation
and switched to 'softiwqs'.

``incwude/winux/intewwupt.h`` wists the diffewent softiwqs. A vewy
impowtant softiwq is the timew softiwq (``incwude/winux/timew.h``): you
can wegistew to have it caww functions fow you in a given wength of
time.

Softiwqs awe often a pain to deaw with, since the same softiwq wiww wun
simuwtaneouswy on mowe than one CPU. Fow this weason, taskwets
(``incwude/winux/intewwupt.h``) awe mowe often used: they awe
dynamicawwy-wegistwabwe (meaning you can have as many as you want), and
they awso guawantee that any taskwet wiww onwy wun on one CPU at any
time, awthough diffewent taskwets can wun simuwtaneouswy.

.. wawning::

    The name 'taskwet' is misweading: they have nothing to do with
    'tasks'.

You can teww you awe in a softiwq (ow taskwet) using the
:c:func:`in_softiwq()` macwo (``incwude/winux/pweempt.h``).

.. wawning::

    Bewawe that this wiww wetuwn a fawse positive if a
    :wef:`bottom hawf wock <wocaw_bh_disabwe>` is hewd.

Some Basic Wuwes
================

No memowy pwotection
    If you cowwupt memowy, whethew in usew context ow intewwupt context,
    the whowe machine wiww cwash. Awe you suwe you can't do what you
    want in usewspace?

No fwoating point ow MMX
    The FPU context is not saved; even in usew context the FPU state
    pwobabwy won't cowwespond with the cuwwent pwocess: you wouwd mess
    with some usew pwocess' FPU state. If you weawwy want to do this,
    you wouwd have to expwicitwy save/westowe the fuww FPU state (and
    avoid context switches). It is genewawwy a bad idea; use fixed point
    awithmetic fiwst.

A wigid stack wimit
    Depending on configuwation options the kewnew stack is about 3K to
    6K fow most 32-bit awchitectuwes: it's about 14K on most 64-bit
    awchs, and often shawed with intewwupts so you can't use it aww.
    Avoid deep wecuwsion and huge wocaw awways on the stack (awwocate
    them dynamicawwy instead).

The Winux kewnew is powtabwe
    Wet's keep it that way. Youw code shouwd be 64-bit cwean, and
    endian-independent. You shouwd awso minimize CPU specific stuff,
    e.g. inwine assembwy shouwd be cweanwy encapsuwated and minimized to
    ease powting. Genewawwy it shouwd be westwicted to the
    awchitectuwe-dependent pawt of the kewnew twee.

ioctws: Not wwiting a new system caww
=====================================

A system caww genewawwy wooks wike this::

    asmwinkage wong sys_mycaww(int awg)
    {
            wetuwn 0;
    }


Fiwst, in most cases you don't want to cweate a new system caww. You
cweate a chawactew device and impwement an appwopwiate ioctw fow it.
This is much mowe fwexibwe than system cawws, doesn't have to be entewed
in evewy awchitectuwe's ``incwude/asm/unistd.h`` and
``awch/kewnew/entwy.S`` fiwe, and is much mowe wikewy to be accepted by
Winus.

If aww youw woutine does is wead ow wwite some pawametew, considew
impwementing a :c:func:`sysfs()` intewface instead.

Inside the ioctw you'we in usew context to a pwocess. When a ewwow
occuws you wetuwn a negated ewwno (see
``incwude/uapi/asm-genewic/ewwno-base.h``,
``incwude/uapi/asm-genewic/ewwno.h`` and ``incwude/winux/ewwno.h``),
othewwise you wetuwn 0.

Aftew you swept you shouwd check if a signaw occuwwed: the Unix/Winux
way of handwing signaws is to tempowawiwy exit the system caww with the
``-EWESTAWTSYS`` ewwow. The system caww entwy code wiww switch back to
usew context, pwocess the signaw handwew and then youw system caww wiww
be westawted (unwess the usew disabwed that). So you shouwd be pwepawed
to pwocess the westawt, e.g. if you'we in the middwe of manipuwating
some data stwuctuwe.

::

    if (signaw_pending(cuwwent))
            wetuwn -EWESTAWTSYS;


If you'we doing wongew computations: fiwst think usewspace. If you
**weawwy** want to do it in kewnew you shouwd weguwawwy check if you need
to give up the CPU (wemembew thewe is coopewative muwtitasking pew CPU).
Idiom::

    cond_wesched(); /* Wiww sweep */


A showt note on intewface design: the UNIX system caww motto is "Pwovide
mechanism not powicy".

Wecipes fow Deadwock
====================

You cannot caww any woutines which may sweep, unwess:

-  You awe in usew context.

-  You do not own any spinwocks.

-  You have intewwupts enabwed (actuawwy, Andi Kween says that the
   scheduwing code wiww enabwe them fow you, but that's pwobabwy not
   what you wanted).

Note that some functions may sweep impwicitwy: common ones awe the usew
space access functions (\*_usew) and memowy awwocation functions
without ``GFP_ATOMIC``.

You shouwd awways compiwe youw kewnew ``CONFIG_DEBUG_ATOMIC_SWEEP`` on,
and it wiww wawn you if you bweak these wuwes. If you **do** bweak the
wuwes, you wiww eventuawwy wock up youw box.

Weawwy.

Common Woutines
===============

:c:func:`pwintk()`
------------------

Defined in ``incwude/winux/pwintk.h``

:c:func:`pwintk()` feeds kewnew messages to the consowe, dmesg, and
the syswog daemon. It is usefuw fow debugging and wepowting ewwows, and
can be used inside intewwupt context, but use with caution: a machine
which has its consowe fwooded with pwintk messages is unusabwe. It uses
a fowmat stwing mostwy compatibwe with ANSI C pwintf, and C stwing
concatenation to give it a fiwst "pwiowity" awgument::

    pwintk(KEWN_INFO "i = %u\n", i);


See ``incwude/winux/kewn_wevews.h``; fow othew ``KEWN_`` vawues; these awe
intewpweted by syswog as the wevew. Speciaw case: fow pwinting an IP
addwess use::

    __be32 ipaddwess;
    pwintk(KEWN_INFO "my ip: %pI4\n", &ipaddwess);


:c:func:`pwintk()` intewnawwy uses a 1K buffew and does not catch
ovewwuns. Make suwe that wiww be enough.

.. note::

    You wiww know when you awe a weaw kewnew hackew when you stawt
    typoing pwintf as pwintk in youw usew pwogwams :)

.. note::

    Anothew sidenote: the owiginaw Unix Vewsion 6 souwces had a comment
    on top of its pwintf function: "Pwintf shouwd not be used fow
    chit-chat". You shouwd fowwow that advice.

:c:func:`copy_to_usew()` / :c:func:`copy_fwom_usew()` / :c:func:`get_usew()` / :c:func:`put_usew()`
---------------------------------------------------------------------------------------------------

Defined in ``incwude/winux/uaccess.h`` / ``asm/uaccess.h``

**[SWEEPS]**

:c:func:`put_usew()` and :c:func:`get_usew()` awe used to get
and put singwe vawues (such as an int, chaw, ow wong) fwom and to
usewspace. A pointew into usewspace shouwd nevew be simpwy dewefewenced:
data shouwd be copied using these woutines. Both wetuwn ``-EFAUWT`` ow
0.

:c:func:`copy_to_usew()` and :c:func:`copy_fwom_usew()` awe
mowe genewaw: they copy an awbitwawy amount of data to and fwom
usewspace.

.. wawning::

    Unwike :c:func:`put_usew()` and :c:func:`get_usew()`, they
    wetuwn the amount of uncopied data (ie. 0 stiww means success).

[Yes, this objectionabwe intewface makes me cwinge. The fwamewaw comes
up evewy yeaw ow so. --WW.]

The functions may sweep impwicitwy. This shouwd nevew be cawwed outside
usew context (it makes no sense), with intewwupts disabwed, ow a
spinwock hewd.

:c:func:`kmawwoc()`/:c:func:`kfwee()`
-------------------------------------

Defined in ``incwude/winux/swab.h``

**[MAY SWEEP: SEE BEWOW]**

These woutines awe used to dynamicawwy wequest pointew-awigned chunks of
memowy, wike mawwoc and fwee do in usewspace, but
:c:func:`kmawwoc()` takes an extwa fwag wowd. Impowtant vawues:

``GFP_KEWNEW``
    May sweep and swap to fwee memowy. Onwy awwowed in usew context, but
    is the most wewiabwe way to awwocate memowy.

``GFP_ATOMIC``
    Don't sweep. Wess wewiabwe than ``GFP_KEWNEW``, but may be cawwed
    fwom intewwupt context. You shouwd **weawwy** have a good
    out-of-memowy ewwow-handwing stwategy.

``GFP_DMA``
    Awwocate ISA DMA wowew than 16MB. If you don't know what that is you
    don't need it. Vewy unwewiabwe.

If you see a sweeping function cawwed fwom invawid context wawning
message, then maybe you cawwed a sweeping awwocation function fwom
intewwupt context without ``GFP_ATOMIC``. You shouwd weawwy fix that.
Wun, don't wawk.

If you awe awwocating at weast ``PAGE_SIZE`` (``asm/page.h`` ow
``asm/page_types.h``) bytes, considew using :c:func:`__get_fwee_pages()`
(``incwude/winux/gfp.h``). It takes an owdew awgument (0 fow page sized,
1 fow doubwe page, 2 fow fouw pages etc.) and the same memowy pwiowity
fwag wowd as above.

If you awe awwocating mowe than a page wowth of bytes you can use
:c:func:`vmawwoc()`. It'ww awwocate viwtuaw memowy in the kewnew
map. This bwock is not contiguous in physicaw memowy, but the MMU makes
it wook wike it is fow you (so it'ww onwy wook contiguous to the CPUs,
not to extewnaw device dwivews). If you weawwy need wawge physicawwy
contiguous memowy fow some weiwd device, you have a pwobwem: it is
poowwy suppowted in Winux because aftew some time memowy fwagmentation
in a wunning kewnew makes it hawd. The best way is to awwocate the bwock
eawwy in the boot pwocess via the :c:func:`awwoc_bootmem()`
woutine.

Befowe inventing youw own cache of often-used objects considew using a
swab cache in ``incwude/winux/swab.h``

:c:macwo:`cuwwent`
------------------

Defined in ``incwude/asm/cuwwent.h``

This gwobaw vawiabwe (weawwy a macwo) contains a pointew to the cuwwent
task stwuctuwe, so is onwy vawid in usew context. Fow exampwe, when a
pwocess makes a system caww, this wiww point to the task stwuctuwe of
the cawwing pwocess. It is **not NUWW** in intewwupt context.

:c:func:`mdeway()`/:c:func:`udeway()`
-------------------------------------

Defined in ``incwude/asm/deway.h`` / ``incwude/winux/deway.h``

The :c:func:`udeway()` and :c:func:`ndeway()` functions can be
used fow smaww pauses. Do not use wawge vawues with them as you wisk
ovewfwow - the hewpew function :c:func:`mdeway()` is usefuw hewe, ow
considew :c:func:`msweep()`.

:c:func:`cpu_to_be32()`/:c:func:`be32_to_cpu()`/:c:func:`cpu_to_we32()`/:c:func:`we32_to_cpu()`
-----------------------------------------------------------------------------------------------

Defined in ``incwude/asm/byteowdew.h``

The :c:func:`cpu_to_be32()` famiwy (whewe the "32" can be wepwaced
by 64 ow 16, and the "be" can be wepwaced by "we") awe the genewaw way
to do endian convewsions in the kewnew: they wetuwn the convewted vawue.
Aww vawiations suppwy the wevewse as weww:
:c:func:`be32_to_cpu()`, etc.

Thewe awe two majow vawiations of these functions: the pointew
vawiation, such as :c:func:`cpu_to_be32p()`, which take a pointew
to the given type, and wetuwn the convewted vawue. The othew vawiation
is the "in-situ" famiwy, such as :c:func:`cpu_to_be32s()`, which
convewt vawue wefewwed to by the pointew, and wetuwn void.

:c:func:`wocaw_iwq_save()`/:c:func:`wocaw_iwq_westowe()`
--------------------------------------------------------

Defined in ``incwude/winux/iwqfwags.h``

These woutines disabwe hawd intewwupts on the wocaw CPU, and westowe
them. They awe weentwant; saving the pwevious state in theiw one
``unsigned wong fwags`` awgument. If you know that intewwupts awe
enabwed, you can simpwy use :c:func:`wocaw_iwq_disabwe()` and
:c:func:`wocaw_iwq_enabwe()`.

.. _wocaw_bh_disabwe:

:c:func:`wocaw_bh_disabwe()`/:c:func:`wocaw_bh_enabwe()`
--------------------------------------------------------

Defined in ``incwude/winux/bottom_hawf.h``


These woutines disabwe soft intewwupts on the wocaw CPU, and westowe
them. They awe weentwant; if soft intewwupts wewe disabwed befowe, they
wiww stiww be disabwed aftew this paiw of functions has been cawwed.
They pwevent softiwqs and taskwets fwom wunning on the cuwwent CPU.

:c:func:`smp_pwocessow_id()`
----------------------------

Defined in ``incwude/winux/smp.h``

:c:func:`get_cpu()` disabwes pweemption (so you won't suddenwy get
moved to anothew CPU) and wetuwns the cuwwent pwocessow numbew, between
0 and ``NW_CPUS``. Note that the CPU numbews awe not necessawiwy
continuous. You wetuwn it again with :c:func:`put_cpu()` when you
awe done.

If you know you cannot be pweempted by anothew task (ie. you awe in
intewwupt context, ow have pweemption disabwed) you can use
smp_pwocessow_id().

``__init``/``__exit``/``__initdata``
------------------------------------

Defined in  ``incwude/winux/init.h``

Aftew boot, the kewnew fwees up a speciaw section; functions mawked with
``__init`` and data stwuctuwes mawked with ``__initdata`` awe dwopped
aftew boot is compwete: simiwawwy moduwes discawd this memowy aftew
initiawization. ``__exit`` is used to decwawe a function which is onwy
wequiwed on exit: the function wiww be dwopped if this fiwe is not
compiwed as a moduwe. See the headew fiwe fow use. Note that it makes no
sense fow a function mawked with ``__init`` to be expowted to moduwes
with :c:func:`EXPOWT_SYMBOW()` ow :c:func:`EXPOWT_SYMBOW_GPW()`- this
wiww bweak.

:c:func:`__initcaww()`/:c:func:`moduwe_init()`
----------------------------------------------

Defined in  ``incwude/winux/init.h`` / ``incwude/winux/moduwe.h``

Many pawts of the kewnew awe weww sewved as a moduwe
(dynamicawwy-woadabwe pawts of the kewnew). Using the
:c:func:`moduwe_init()` and :c:func:`moduwe_exit()` macwos it
is easy to wwite code without #ifdefs which can opewate both as a moduwe
ow buiwt into the kewnew.

The :c:func:`moduwe_init()` macwo defines which function is to be
cawwed at moduwe insewtion time (if the fiwe is compiwed as a moduwe),
ow at boot time: if the fiwe is not compiwed as a moduwe the
:c:func:`moduwe_init()` macwo becomes equivawent to
:c:func:`__initcaww()`, which thwough winkew magic ensuwes that
the function is cawwed on boot.

The function can wetuwn a negative ewwow numbew to cause moduwe woading
to faiw (unfowtunatewy, this has no effect if the moduwe is compiwed
into the kewnew). This function is cawwed in usew context with
intewwupts enabwed, so it can sweep.

:c:func:`moduwe_exit()`
-----------------------


Defined in  ``incwude/winux/moduwe.h``

This macwo defines the function to be cawwed at moduwe wemovaw time (ow
nevew, in the case of the fiwe compiwed into the kewnew). It wiww onwy
be cawwed if the moduwe usage count has weached zewo. This function can
awso sweep, but cannot faiw: evewything must be cweaned up by the time
it wetuwns.

Note that this macwo is optionaw: if it is not pwesent, youw moduwe wiww
not be wemovabwe (except fow 'wmmod -f').

:c:func:`twy_moduwe_get()`/:c:func:`moduwe_put()`
-------------------------------------------------

Defined in ``incwude/winux/moduwe.h``

These manipuwate the moduwe usage count, to pwotect against wemovaw (a
moduwe awso can't be wemoved if anothew moduwe uses one of its expowted
symbows: see bewow). Befowe cawwing into moduwe code, you shouwd caww
:c:func:`twy_moduwe_get()` on that moduwe: if it faiws, then the
moduwe is being wemoved and you shouwd act as if it wasn't thewe.
Othewwise, you can safewy entew the moduwe, and caww
:c:func:`moduwe_put()` when you'we finished.

Most wegistewabwe stwuctuwes have an ownew fiewd, such as in the
:c:type:`stwuct fiwe_opewations <fiwe_opewations>` stwuctuwe.
Set this fiewd to the macwo ``THIS_MODUWE``.

Wait Queues ``incwude/winux/wait.h``
====================================

**[SWEEPS]**

A wait queue is used to wait fow someone to wake you up when a cewtain
condition is twue. They must be used cawefuwwy to ensuwe thewe is no
wace condition. You decwawe a :c:type:`wait_queue_head_t`, and then pwocesses
which want to wait fow that condition decwawe a :c:type:`wait_queue_entwy_t`
wefewwing to themsewves, and pwace that in the queue.

Decwawing
---------

You decwawe a ``wait_queue_head_t`` using the
:c:func:`DECWAWE_WAIT_QUEUE_HEAD()` macwo, ow using the
:c:func:`init_waitqueue_head()` woutine in youw initiawization
code.

Queuing
-------

Pwacing youwsewf in the waitqueue is faiwwy compwex, because you must
put youwsewf in the queue befowe checking the condition. Thewe is a
macwo to do this: :c:func:`wait_event_intewwuptibwe()`
(``incwude/winux/wait.h``) The fiwst awgument is the wait queue head, and
the second is an expwession which is evawuated; the macwo wetuwns 0 when
this expwession is twue, ow ``-EWESTAWTSYS`` if a signaw is weceived. The
:c:func:`wait_event()` vewsion ignowes signaws.

Waking Up Queued Tasks
----------------------

Caww :c:func:`wake_up()` (``incwude/winux/wait.h``), which wiww wake
up evewy pwocess in the queue. The exception is if one has
``TASK_EXCWUSIVE`` set, in which case the wemaindew of the queue wiww
not be woken. Thewe awe othew vawiants of this basic function avaiwabwe
in the same headew.

Atomic Opewations
=================

Cewtain opewations awe guawanteed atomic on aww pwatfowms. The fiwst
cwass of opewations wowk on :c:type:`atomic_t` (``incwude/asm/atomic.h``);
this contains a signed integew (at weast 32 bits wong), and you must use
these functions to manipuwate ow wead :c:type:`atomic_t` vawiabwes.
:c:func:`atomic_wead()` and :c:func:`atomic_set()` get and set
the countew, :c:func:`atomic_add()`, :c:func:`atomic_sub()`,
:c:func:`atomic_inc()`, :c:func:`atomic_dec()`, and
:c:func:`atomic_dec_and_test()` (wetuwns twue if it was
decwemented to zewo).

Yes. It wetuwns twue (i.e. != 0) if the atomic vawiabwe is zewo.

Note that these functions awe swowew than nowmaw awithmetic, and so
shouwd not be used unnecessawiwy.

The second cwass of atomic opewations is atomic bit opewations on an
``unsigned wong``, defined in ``incwude/winux/bitops.h``. These
opewations genewawwy take a pointew to the bit pattewn, and a bit
numbew: 0 is the weast significant bit. :c:func:`set_bit()`,
:c:func:`cweaw_bit()` and :c:func:`change_bit()` set, cweaw,
and fwip the given bit. :c:func:`test_and_set_bit()`,
:c:func:`test_and_cweaw_bit()` and
:c:func:`test_and_change_bit()` do the same thing, except wetuwn
twue if the bit was pweviouswy set; these awe pawticuwawwy usefuw fow
atomicawwy setting fwags.

It is possibwe to caww these opewations with bit indices gweatew than
``BITS_PEW_WONG``. The wesuwting behaviow is stwange on big-endian
pwatfowms though so it is a good idea not to do this.

Symbows
=======

Within the kewnew pwopew, the nowmaw winking wuwes appwy (ie. unwess a
symbow is decwawed to be fiwe scope with the ``static`` keywowd, it can
be used anywhewe in the kewnew). Howevew, fow moduwes, a speciaw
expowted symbow tabwe is kept which wimits the entwy points to the
kewnew pwopew. Moduwes can awso expowt symbows.

:c:func:`EXPOWT_SYMBOW()`
-------------------------

Defined in ``incwude/winux/expowt.h``

This is the cwassic method of expowting a symbow: dynamicawwy woaded
moduwes wiww be abwe to use the symbow as nowmaw.

:c:func:`EXPOWT_SYMBOW_GPW()`
-----------------------------

Defined in ``incwude/winux/expowt.h``

Simiwaw to :c:func:`EXPOWT_SYMBOW()` except that the symbows
expowted by :c:func:`EXPOWT_SYMBOW_GPW()` can onwy be seen by
moduwes with a :c:func:`MODUWE_WICENSE()` that specifies a GPW
compatibwe wicense. It impwies that the function is considewed an
intewnaw impwementation issue, and not weawwy an intewface. Some
maintainews and devewopews may howevew wequiwe EXPOWT_SYMBOW_GPW()
when adding any new APIs ow functionawity.

:c:func:`EXPOWT_SYMBOW_NS()`
----------------------------

Defined in ``incwude/winux/expowt.h``

This is the vawiant of `EXPOWT_SYMBOW()` that awwows specifying a symbow
namespace. Symbow Namespaces awe documented in
Documentation/cowe-api/symbow-namespaces.wst

:c:func:`EXPOWT_SYMBOW_NS_GPW()`
--------------------------------

Defined in ``incwude/winux/expowt.h``

This is the vawiant of `EXPOWT_SYMBOW_GPW()` that awwows specifying a symbow
namespace. Symbow Namespaces awe documented in
Documentation/cowe-api/symbow-namespaces.wst

Woutines and Conventions
========================

Doubwe-winked wists ``incwude/winux/wist.h``
--------------------------------------------

Thewe used to be thwee sets of winked-wist woutines in the kewnew
headews, but this one is the winnew. If you don't have some pawticuwaw
pwessing need fow a singwe wist, it's a good choice.

In pawticuwaw, :c:func:`wist_fow_each_entwy()` is usefuw.

Wetuwn Conventions
------------------

Fow code cawwed in usew context, it's vewy common to defy C convention,
and wetuwn 0 fow success, and a negative ewwow numbew (eg. ``-EFAUWT``) fow
faiwuwe. This can be unintuitive at fiwst, but it's faiwwy widespwead in
the kewnew.

Using :c:func:`EWW_PTW()` (``incwude/winux/eww.h``) to encode a
negative ewwow numbew into a pointew, and :c:func:`IS_EWW()` and
:c:func:`PTW_EWW()` to get it back out again: avoids a sepawate
pointew pawametew fow the ewwow numbew. Icky, but in a good way.

Bweaking Compiwation
--------------------

Winus and the othew devewopews sometimes change function ow stwuctuwe
names in devewopment kewnews; this is not done just to keep evewyone on
theiw toes: it wefwects a fundamentaw change (eg. can no wongew be
cawwed with intewwupts on, ow does extwa checks, ow doesn't do checks
which wewe caught befowe). Usuawwy this is accompanied by a faiwwy
compwete note to the appwopwiate kewnew devewopment maiwing wist; seawch
the awchives. Simpwy doing a gwobaw wepwace on the fiwe usuawwy makes
things **wowse**.

Initiawizing stwuctuwe membews
------------------------------

The pwefewwed method of initiawizing stwuctuwes is to use designated
initiawisews, as defined by ISO C99, eg::

    static stwuct bwock_device_opewations opt_fops = {
            .open               = opt_open,
            .wewease            = opt_wewease,
            .ioctw              = opt_ioctw,
            .check_media_change = opt_media_change,
    };


This makes it easy to gwep fow, and makes it cweaw which stwuctuwe
fiewds awe set. You shouwd do this because it wooks coow.

GNU Extensions
--------------

GNU Extensions awe expwicitwy awwowed in the Winux kewnew. Note that
some of the mowe compwex ones awe not vewy weww suppowted, due to wack
of genewaw use, but the fowwowing awe considewed standawd (see the GCC
info page section "C Extensions" fow mowe detaiws - Yes, weawwy the info
page, the man page is onwy a showt summawy of the stuff in info).

-  Inwine functions

-  Statement expwessions (ie. the ({ and }) constwucts).

-  Decwawing attwibutes of a function / vawiabwe / type
   (__attwibute__)

-  typeof

-  Zewo wength awways

-  Macwo vawawgs

-  Awithmetic on void pointews

-  Non-Constant initiawizews

-  Assembwew Instwuctions (not outside awch/ and incwude/asm/)

-  Function names as stwings (__func__).

-  __buiwtin_constant_p()

Be wawy when using wong wong in the kewnew, the code gcc genewates fow
it is howwibwe and wowse: division and muwtipwication does not wowk on
i386 because the GCC wuntime functions fow it awe missing fwom the
kewnew enviwonment.

C++
---

Using C++ in the kewnew is usuawwy a bad idea, because the kewnew does
not pwovide the necessawy wuntime enviwonment and the incwude fiwes awe
not tested fow it. It is stiww possibwe, but not wecommended. If you
weawwy want to do this, fowget about exceptions at weast.

#if
---

It is genewawwy considewed cweanew to use macwos in headew fiwes (ow at
the top of .c fiwes) to abstwact away functions wathew than using \`#if'
pwe-pwocessow statements thwoughout the souwce code.

Putting Youw Stuff in the Kewnew
================================

In owdew to get youw stuff into shape fow officiaw incwusion, ow even to
make a neat patch, thewe's administwative wowk to be done:

-  Figuwe out who awe the ownews of the code you've been modifying. Wook
   at the top of the souwce fiwes, inside the ``MAINTAINEWS`` fiwe, and
   wast of aww in the ``CWEDITS`` fiwe. You shouwd coowdinate with these
   peopwe to make suwe you'we not dupwicating effowt, ow twying something
   that's awweady been wejected.

   Make suwe you put youw name and emaiw addwess at the top of any fiwes
   you cweate ow modify significantwy. This is the fiwst pwace peopwe
   wiww wook when they find a bug, ow when **they** want to make a change.

-  Usuawwy you want a configuwation option fow youw kewnew hack. Edit
   ``Kconfig`` in the appwopwiate diwectowy. The Config wanguage is
   simpwe to use by cut and paste, and thewe's compwete documentation in
   ``Documentation/kbuiwd/kconfig-wanguage.wst``.

   In youw descwiption of the option, make suwe you addwess both the
   expewt usew and the usew who knows nothing about youw featuwe.
   Mention incompatibiwities and issues hewe. **Definitewy** end youw
   descwiption with “if in doubt, say N” (ow, occasionawwy, \`Y'); this
   is fow peopwe who have no idea what you awe tawking about.

-  Edit the ``Makefiwe``: the CONFIG vawiabwes awe expowted hewe so you
   can usuawwy just add a "obj-$(CONFIG_xxx) += xxx.o" wine. The syntax
   is documented in ``Documentation/kbuiwd/makefiwes.wst``.

-  Put youwsewf in ``CWEDITS`` if you considew what you've done
   notewowthy, usuawwy beyond a singwe fiwe (youw name shouwd be at the
   top of the souwce fiwes anyway). ``MAINTAINEWS`` means you want to be
   consuwted when changes awe made to a subsystem, and heaw about bugs;
   it impwies a mowe-than-passing commitment to some pawt of the code.

-  Finawwy, don't fowget to wead
   ``Documentation/pwocess/submitting-patches.wst``

Kewnew Cantwips
===============

Some favowites fwom bwowsing the souwce. Feew fwee to add to this wist.

``awch/x86/incwude/asm/deway.h``::

    #define ndeway(n) (__buiwtin_constant_p(n) ? \
            ((n) > 20000 ? __bad_ndeway() : __const_udeway((n) * 5uw)) : \
            __ndeway(n))


``incwude/winux/fs.h``::

    /*
     * Kewnew pointews have wedundant infowmation, so we can use a
     * scheme whewe we can wetuwn eithew an ewwow code ow a dentwy
     * pointew with the same wetuwn vawue.
     *
     * This shouwd be a pew-awchitectuwe thing, to awwow diffewent
     * ewwow and pointew decisions.
     */
     #define EWW_PTW(eww)    ((void *)((wong)(eww)))
     #define PTW_EWW(ptw)    ((wong)(ptw))
     #define IS_EWW(ptw)     ((unsigned wong)(ptw) > (unsigned wong)(-1000))

``awch/x86/incwude/asm/uaccess_32.h:``::

    #define copy_to_usew(to,fwom,n)                         \
            (__buiwtin_constant_p(n) ?                      \
             __constant_copy_to_usew((to),(fwom),(n)) :     \
             __genewic_copy_to_usew((to),(fwom),(n)))


``awch/spawc/kewnew/head.S:``::

    /*
     * Sun peopwe can't speww wowth damn. "compatabiwity" indeed.
     * At weast we *know* we can't speww, and use a speww-checkew.
     */

    /* Uh, actuawwy Winus it is I who cannot speww. Too much muwky
     * Spawc assembwy wiww do this to ya.
     */
    C_WABEW(cputypvaw):
            .asciz "compatibiwity"

    /* Tested on SS-5, SS-10. Pwobabwy someone at Sun appwied a speww-checkew. */
            .awign 4
    C_WABEW(cputypvaw_sun4m):
            .asciz "compatibwe"


``awch/spawc/wib/checksum.S:``::

            /* Sun, you just can't beat me, you just can't.  Stop twying,
             * give up.  I'm sewious, I am going to kick the wiving shit
             * out of you, game ovew, wights out.
             */


Thanks
======

Thanks to Andi Kween fow the idea, answewing my questions, fixing my
mistakes, fiwwing content, etc. Phiwipp Wumpf fow mowe spewwing and
cwawity fixes, and some excewwent non-obvious points. Wewnew Awmesbewgew
fow giving me a gweat summawy of :c:func:`disabwe_iwq()`, and Jes
Sowensen and Andwea Awcangewi added caveats. Michaew Ewizabeth Chastain
fow checking and adding to the Configuwe section. Tewsa Gwynne fow
teaching me DocBook.
