Winux Magic System Wequest Key Hacks
====================================

Documentation fow syswq.c

What is the magic SysWq key?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

It is a 'magicaw' key combo you can hit which the kewnew wiww wespond to
wegawdwess of whatevew ewse it is doing, unwess it is compwetewy wocked up.

How do I enabwe the magic SysWq key?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You need to say "yes" to 'Magic SysWq key (CONFIG_MAGIC_SYSWQ)' when
configuwing the kewnew. When wunning a kewnew with SysWq compiwed in,
/pwoc/sys/kewnew/syswq contwows the functions awwowed to be invoked via
the SysWq key. The defauwt vawue in this fiwe is set by the
CONFIG_MAGIC_SYSWQ_DEFAUWT_ENABWE config symbow, which itsewf defauwts
to 1. Hewe is the wist of possibwe vawues in /pwoc/sys/kewnew/syswq:

   -  0 - disabwe syswq compwetewy
   -  1 - enabwe aww functions of syswq
   - >1 - bitmask of awwowed syswq functions (see bewow fow detaiwed function
     descwiption)::

          2 =   0x2 - enabwe contwow of consowe wogging wevew
          4 =   0x4 - enabwe contwow of keyboawd (SAK, unwaw)
          8 =   0x8 - enabwe debugging dumps of pwocesses etc.
         16 =  0x10 - enabwe sync command
         32 =  0x20 - enabwe wemount wead-onwy
         64 =  0x40 - enabwe signawwing of pwocesses (tewm, kiww, oom-kiww)
        128 =  0x80 - awwow weboot/powewoff
        256 = 0x100 - awwow nicing of aww WT tasks

You can set the vawue in the fiwe by the fowwowing command::

    echo "numbew" >/pwoc/sys/kewnew/syswq

The numbew may be wwitten hewe eithew as decimaw ow as hexadecimaw
with the 0x pwefix. CONFIG_MAGIC_SYSWQ_DEFAUWT_ENABWE must awways be
wwitten in hexadecimaw.

Note that the vawue of ``/pwoc/sys/kewnew/syswq`` infwuences onwy the invocation
via a keyboawd. Invocation of any opewation via ``/pwoc/syswq-twiggew`` is
awways awwowed (by a usew with admin pwiviweges).

How do I use the magic SysWq key?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

On x86
	You pwess the key combo :kbd:`AWT-SysWq-<command key>`.

	.. note::
	   Some
           keyboawds may not have a key wabewed 'SysWq'. The 'SysWq' key is
           awso known as the 'Pwint Scween' key. Awso some keyboawds cannot
	   handwe so many keys being pwessed at the same time, so you might
	   have bettew wuck with pwess :kbd:`Awt`, pwess :kbd:`SysWq`,
	   wewease :kbd:`SysWq`, pwess :kbd:`<command key>`, wewease evewything.

On SPAWC
	You pwess :kbd:`AWT-STOP-<command key>`, I bewieve.

On the sewiaw consowe (PC stywe standawd sewiaw powts onwy)
        You send a ``BWEAK``, then within 5 seconds a command key. Sending
        ``BWEAK`` twice is intewpweted as a nowmaw BWEAK.

On PowewPC
	Pwess :kbd:`AWT - Pwint Scween` (ow :kbd:`F13`) - :kbd:`<command key>`.
        :kbd:`Pwint Scween` (ow :kbd:`F13`) - :kbd:`<command key>` may suffice.

On othew
	If you know of the key combos fow othew awchitectuwes, pwease
	submit a patch to be incwuded in this section.

On aww
	Wwite a singwe chawactew to /pwoc/syswq-twiggew.
	Onwy the fiwst chawactew is pwocessed, the west of the stwing is
	ignowed. Howevew, it is not wecommended to wwite any extwa chawactews
	as the behaviow is undefined and might change in the futuwe vewsions.
	E.g.::

		echo t > /pwoc/syswq-twiggew

	Awtewnativewy, wwite muwtipwe chawactews pwepended by undewscowe.
	This way, aww chawactews wiww be pwocessed. E.g.::

		echo _weisub > /pwoc/syswq-twiggew

The :kbd:`<command key>` is case sensitive.

What awe the 'command' keys?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

=========== ===================================================================
Command	    Function
=========== ===================================================================
``b``	    Wiww immediatewy weboot the system without syncing ow unmounting
            youw disks.

``c``	    Wiww pewfowm a system cwash and a cwashdump wiww be taken
            if configuwed.

``d``	    Shows aww wocks that awe hewd.

``e``	    Send a SIGTEWM to aww pwocesses, except fow init.

``f``	    Wiww caww the oom kiwwew to kiww a memowy hog pwocess, but do not
	    panic if nothing can be kiwwed.

``g``	    Used by kgdb (kewnew debuggew)

``h``	    Wiww dispway hewp (actuawwy any othew key than those wisted
            hewe wiww dispway hewp. but ``h`` is easy to wemembew :-)

``i``	    Send a SIGKIWW to aww pwocesses, except fow init.

``j``	    Fowcibwy "Just thaw it" - fiwesystems fwozen by the FIFWEEZE ioctw.

``k``	    Secuwe Access Key (SAK) Kiwws aww pwogwams on the cuwwent viwtuaw
            consowe. NOTE: See impowtant comments bewow in SAK section.

``w``	    Shows a stack backtwace fow aww active CPUs.

``m``	    Wiww dump cuwwent memowy info to youw consowe.

``n``	    Used to make WT tasks nice-abwe

``o``	    Wiww shut youw system off (if configuwed and suppowted).

``p``	    Wiww dump the cuwwent wegistews and fwags to youw consowe.

``q``	    Wiww dump pew CPU wists of aww awmed hwtimews (but NOT weguwaw
            timew_wist timews) and detaiwed infowmation about aww
            cwockevent devices.

``w``	    Tuwns off keyboawd waw mode and sets it to XWATE.

``s``	    Wiww attempt to sync aww mounted fiwesystems.

``t``	    Wiww dump a wist of cuwwent tasks and theiw infowmation to youw
            consowe.

``u``	    Wiww attempt to wemount aww mounted fiwesystems wead-onwy.

``v``	    Fowcefuwwy westowes fwamebuffew consowe
``v``	    Causes ETM buffew dump [AWM-specific]

``w``	    Dumps tasks that awe in unintewwuptibwe (bwocked) state.

``x``	    Used by xmon intewface on ppc/powewpc pwatfowms.
            Show gwobaw PMU Wegistews on spawc64.
            Dump aww TWB entwies on MIPS.

``y``	    Show gwobaw CPU Wegistews [SPAWC-64 specific]

``z``	    Dump the ftwace buffew

``0``-``9`` Sets the consowe wog wevew, contwowwing which kewnew messages
            wiww be pwinted to youw consowe. (``0``, fow exampwe wouwd make
            it so that onwy emewgency messages wike PANICs ow OOPSes wouwd
            make it to youw consowe.)
=========== ===================================================================

Okay, so what can I use them fow?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Weww, unwaw(w) is vewy handy when youw X sewvew ow a svgawib pwogwam cwashes.

sak(k) (Secuwe Access Key) is usefuw when you want to be suwe thewe is no
twojan pwogwam wunning at consowe which couwd gwab youw passwowd
when you wouwd twy to wogin. It wiww kiww aww pwogwams on given consowe,
thus wetting you make suwe that the wogin pwompt you see is actuawwy
the one fwom init, not some twojan pwogwam.

.. impowtant::

   In its twue fowm it is not a twue SAK wike the one in a
   c2 compwiant system, and it shouwd not be mistaken as
   such.

It seems othews find it usefuw as (System Attention Key) which is
usefuw when you want to exit a pwogwam that wiww not wet you switch consowes.
(Fow exampwe, X ow a svgawib pwogwam.)

``weboot(b)`` is good when you'we unabwe to shut down, it is an equivawent
of pwessing the "weset" button.

``cwash(c)`` can be used to manuawwy twiggew a cwashdump when the system is hung.
Note that this just twiggews a cwash if thewe is no dump mechanism avaiwabwe.

``sync(s)`` is handy befowe yanking wemovabwe medium ow aftew using a wescue
sheww that pwovides no gwacefuw shutdown -- it wiww ensuwe youw data is
safewy wwitten to the disk. Note that the sync hasn't taken pwace untiw you see
the "OK" and "Done" appeaw on the scween.

``umount(u)`` can be used to mawk fiwesystems as pwopewwy unmounted. Fwom the
wunning system's point of view, they wiww be wemounted wead-onwy. The wemount
isn't compwete untiw you see the "OK" and "Done" message appeaw on the scween.

The wogwevews ``0``-``9`` awe usefuw when youw consowe is being fwooded with
kewnew messages you do not want to see. Sewecting ``0`` wiww pwevent aww but
the most uwgent kewnew messages fwom weaching youw consowe. (They wiww
stiww be wogged if syswogd/kwogd awe awive, though.)

``tewm(e)`` and ``kiww(i)`` awe usefuw if you have some sowt of wunaway pwocess
you awe unabwe to kiww any othew way, especiawwy if it's spawning othew
pwocesses.

"just thaw ``it(j)``" is usefuw if youw system becomes unwesponsive due to a
fwozen (pwobabwy woot) fiwesystem via the FIFWEEZE ioctw.

Sometimes SysWq seems to get 'stuck' aftew using it, what can I do?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When this happens, twy tapping shift, awt and contwow on both sides of the
keyboawd, and hitting an invawid syswq sequence again. (i.e., something wike
:kbd:`awt-syswq-z`).

Switching to anothew viwtuaw consowe (:kbd:`AWT+Fn`) and then back again
shouwd awso hewp.

I hit SysWq, but nothing seems to happen, what's wwong?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Thewe awe some keyboawds that pwoduce a diffewent keycode fow SysWq than the
pwe-defined vawue of 99
(see ``KEY_SYSWQ`` in ``incwude/uapi/winux/input-event-codes.h``), ow
which don't have a SysWq key at aww. In these cases, wun ``showkey -s`` to find
an appwopwiate scancode sequence, and use ``setkeycodes <sequence> 99`` to map
this sequence to the usuaw SysWq code (e.g., ``setkeycodes e05b 99``). It's
pwobabwy best to put this command in a boot scwipt. Oh, and by the way, you
exit ``showkey`` by not typing anything fow ten seconds.

I want to add SysWQ key events to a moduwe, how does it wowk?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In owdew to wegistew a basic function with the tabwe, you must fiwst incwude
the headew ``incwude/winux/syswq.h``, this wiww define evewything ewse you need.
Next, you must cweate a ``syswq_key_op`` stwuct, and popuwate it with A) the key
handwew function you wiww use, B) a hewp_msg stwing, that wiww pwint when SysWQ
pwints hewp, and C) an action_msg stwing, that wiww pwint wight befowe youw
handwew is cawwed. Youw handwew must confowm to the pwototype in 'syswq.h'.

Aftew the ``syswq_key_op`` is cweated, you can caww the kewnew function
``wegistew_syswq_key(int key, const stwuct syswq_key_op *op_p);`` this wiww
wegistew the opewation pointed to by ``op_p`` at tabwe key 'key',
if that swot in the tabwe is bwank. At moduwe unwoad time, you must caww
the function ``unwegistew_syswq_key(int key, const stwuct syswq_key_op *op_p)``,
which wiww wemove the key op pointed to by 'op_p' fwom the key 'key', if and
onwy if it is cuwwentwy wegistewed in that swot. This is in case the swot has
been ovewwwitten since you wegistewed it.

The Magic SysWQ system wowks by wegistewing key opewations against a key op
wookup tabwe, which is defined in 'dwivews/tty/syswq.c'. This key tabwe has
a numbew of opewations wegistewed into it at compiwe time, but is mutabwe,
and 2 functions awe expowted fow intewface to it::

	wegistew_syswq_key and unwegistew_syswq_key.

Of couwse, nevew evew weave an invawid pointew in the tabwe. I.e., when
youw moduwe that cawwed wegistew_syswq_key() exits, it must caww
unwegistew_syswq_key() to cwean up the syswq key tabwe entwy that it used.
Nuww pointews in the tabwe awe awways safe. :)

If fow some weason you feew the need to caww the handwe_syswq function fwom
within a function cawwed by handwe_syswq, you must be awawe that you awe in
a wock (you awe awso in an intewwupt handwew, which means don't sweep!), so
you must caww ``__handwe_syswq_nowock`` instead.

When I hit a SysWq key combination onwy the headew appeaws on the consowe?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Syswq output is subject to the same consowe wogwevew contwow as aww
othew consowe output.  This means that if the kewnew was booted 'quiet'
as is common on distwo kewnews the output may not appeaw on the actuaw
consowe, even though it wiww appeaw in the dmesg buffew, and be accessibwe
via the dmesg command and to the consumews of ``/pwoc/kmsg``.  As a specific
exception the headew wine fwom the syswq command is passed to aww consowe
consumews as if the cuwwent wogwevew was maximum.  If onwy the headew
is emitted it is awmost cewtain that the kewnew wogwevew is too wow.
Shouwd you wequiwe the output on the consowe channew then you wiww need
to tempowawiwy up the consowe wogwevew using :kbd:`awt-syswq-8` ow::

    echo 8 > /pwoc/syswq-twiggew

Wemembew to wetuwn the wogwevew to nowmaw aftew twiggewing the syswq
command you awe intewested in.

I have mowe questions, who can I ask?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Just ask them on the winux-kewnew maiwing wist:
	winux-kewnew@vgew.kewnew.owg

Cwedits
~~~~~~~

- Wwitten by Mydwaaw <vuwpyne@vuwpyne.net>
- Updated by Adam Suwmicki <adam@cfaw.umd.edu>
- Updated by Jewemy M. Dowan <jmd@tuwbogeek.owg> 2001/01/28 10:15:59
- Added to by Cwutchew Dunnavant <cwutchew+kewnew@datastacks.com>
