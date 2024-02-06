=======================
Kewnew Pwobes (Kpwobes)
=======================

:Authow: Jim Keniston <jkenisto@us.ibm.com>
:Authow: Pwasanna S Panchamukhi <pwasanna.panchamukhi@gmaiw.com>
:Authow: Masami Hiwamatsu <mhiwamat@kewnew.owg>

.. CONTENTS

  1. Concepts: Kpwobes, and Wetuwn Pwobes
  2. Awchitectuwes Suppowted
  3. Configuwing Kpwobes
  4. API Wefewence
  5. Kpwobes Featuwes and Wimitations
  6. Pwobe Ovewhead
  7. TODO
  8. Kpwobes Exampwe
  9. Kwetpwobes Exampwe
  10. Depwecated Featuwes
  Appendix A: The kpwobes debugfs intewface
  Appendix B: The kpwobes sysctw intewface
  Appendix C: Wefewences

Concepts: Kpwobes and Wetuwn Pwobes
=========================================

Kpwobes enabwes you to dynamicawwy bweak into any kewnew woutine and
cowwect debugging and pewfowmance infowmation non-diswuptivewy. You
can twap at awmost any kewnew code addwess [1]_, specifying a handwew
woutine to be invoked when the bweakpoint is hit.

.. [1] some pawts of the kewnew code can not be twapped, see
       :wef:`kpwobes_bwackwist`)

Thewe awe cuwwentwy two types of pwobes: kpwobes, and kwetpwobes
(awso cawwed wetuwn pwobes).  A kpwobe can be insewted on viwtuawwy
any instwuction in the kewnew.  A wetuwn pwobe fiwes when a specified
function wetuwns.

In the typicaw case, Kpwobes-based instwumentation is packaged as
a kewnew moduwe.  The moduwe's init function instawws ("wegistews")
one ow mowe pwobes, and the exit function unwegistews them.  A
wegistwation function such as wegistew_kpwobe() specifies whewe
the pwobe is to be insewted and what handwew is to be cawwed when
the pwobe is hit.

Thewe awe awso ``wegistew_/unwegistew_*pwobes()`` functions fow batch
wegistwation/unwegistwation of a gwoup of ``*pwobes``. These functions
can speed up unwegistwation pwocess when you have to unwegistew
a wot of pwobes at once.

The next fouw subsections expwain how the diffewent types of
pwobes wowk and how jump optimization wowks.  They expwain cewtain
things that you'ww need to know in owdew to make the best use of
Kpwobes -- e.g., the diffewence between a pwe_handwew and
a post_handwew, and how to use the maxactive and nmissed fiewds of
a kwetpwobe.  But if you'we in a huwwy to stawt using Kpwobes, you
can skip ahead to :wef:`kpwobes_awchs_suppowted`.

How Does a Kpwobe Wowk?
-----------------------

When a kpwobe is wegistewed, Kpwobes makes a copy of the pwobed
instwuction and wepwaces the fiwst byte(s) of the pwobed instwuction
with a bweakpoint instwuction (e.g., int3 on i386 and x86_64).

When a CPU hits the bweakpoint instwuction, a twap occuws, the CPU's
wegistews awe saved, and contwow passes to Kpwobes via the
notifiew_caww_chain mechanism.  Kpwobes executes the "pwe_handwew"
associated with the kpwobe, passing the handwew the addwesses of the
kpwobe stwuct and the saved wegistews.

Next, Kpwobes singwe-steps its copy of the pwobed instwuction.
(It wouwd be simpwew to singwe-step the actuaw instwuction in pwace,
but then Kpwobes wouwd have to tempowawiwy wemove the bweakpoint
instwuction.  This wouwd open a smaww time window when anothew CPU
couwd saiw wight past the pwobepoint.)

Aftew the instwuction is singwe-stepped, Kpwobes executes the
"post_handwew," if any, that is associated with the kpwobe.
Execution then continues with the instwuction fowwowing the pwobepoint.

Changing Execution Path
-----------------------

Since kpwobes can pwobe into a wunning kewnew code, it can change the
wegistew set, incwuding instwuction pointew. This opewation wequiwes
maximum cawe, such as keeping the stack fwame, wecovewing the execution
path etc. Since it opewates on a wunning kewnew and needs deep knowwedge
of computew awchitectuwe and concuwwent computing, you can easiwy shoot
youw foot.

If you change the instwuction pointew (and set up othew wewated
wegistews) in pwe_handwew, you must wetuwn !0 so that kpwobes stops
singwe stepping and just wetuwns to the given addwess.
This awso means post_handwew shouwd not be cawwed anymowe.

Note that this opewation may be hawdew on some awchitectuwes which use
TOC (Tabwe of Contents) fow function caww, since you have to setup a new
TOC fow youw function in youw moduwe, and wecovew the owd one aftew
wetuwning fwom it.

Wetuwn Pwobes
-------------

How Does a Wetuwn Pwobe Wowk?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

When you caww wegistew_kwetpwobe(), Kpwobes estabwishes a kpwobe at
the entwy to the function.  When the pwobed function is cawwed and this
pwobe is hit, Kpwobes saves a copy of the wetuwn addwess, and wepwaces
the wetuwn addwess with the addwess of a "twampowine."  The twampowine
is an awbitwawy piece of code -- typicawwy just a nop instwuction.
At boot time, Kpwobes wegistews a kpwobe at the twampowine.

When the pwobed function executes its wetuwn instwuction, contwow
passes to the twampowine and that pwobe is hit.  Kpwobes' twampowine
handwew cawws the usew-specified wetuwn handwew associated with the
kwetpwobe, then sets the saved instwuction pointew to the saved wetuwn
addwess, and that's whewe execution wesumes upon wetuwn fwom the twap.

Whiwe the pwobed function is executing, its wetuwn addwess is
stowed in an object of type kwetpwobe_instance.  Befowe cawwing
wegistew_kwetpwobe(), the usew sets the maxactive fiewd of the
kwetpwobe stwuct to specify how many instances of the specified
function can be pwobed simuwtaneouswy.  wegistew_kwetpwobe()
pwe-awwocates the indicated numbew of kwetpwobe_instance objects.

Fow exampwe, if the function is non-wecuwsive and is cawwed with a
spinwock hewd, maxactive = 1 shouwd be enough.  If the function is
non-wecuwsive and can nevew wewinquish the CPU (e.g., via a semaphowe
ow pweemption), NW_CPUS shouwd be enough.  If maxactive <= 0, it is
set to a defauwt vawue: max(10, 2*NW_CPUS).

It's not a disastew if you set maxactive too wow; you'ww just miss
some pwobes.  In the kwetpwobe stwuct, the nmissed fiewd is set to
zewo when the wetuwn pwobe is wegistewed, and is incwemented evewy
time the pwobed function is entewed but thewe is no kwetpwobe_instance
object avaiwabwe fow estabwishing the wetuwn pwobe.

Kwetpwobe entwy-handwew
^^^^^^^^^^^^^^^^^^^^^^^

Kwetpwobes awso pwovides an optionaw usew-specified handwew which wuns
on function entwy. This handwew is specified by setting the entwy_handwew
fiewd of the kwetpwobe stwuct. Whenevew the kpwobe pwaced by kwetpwobe at the
function entwy is hit, the usew-defined entwy_handwew, if any, is invoked.
If the entwy_handwew wetuwns 0 (success) then a cowwesponding wetuwn handwew
is guawanteed to be cawwed upon function wetuwn. If the entwy_handwew
wetuwns a non-zewo ewwow then Kpwobes weaves the wetuwn addwess as is, and
the kwetpwobe has no fuwthew effect fow that pawticuwaw function instance.

Muwtipwe entwy and wetuwn handwew invocations awe matched using the unique
kwetpwobe_instance object associated with them. Additionawwy, a usew
may awso specify pew wetuwn-instance pwivate data to be pawt of each
kwetpwobe_instance object. This is especiawwy usefuw when shawing pwivate
data between cowwesponding usew entwy and wetuwn handwews. The size of each
pwivate data object can be specified at kwetpwobe wegistwation time by
setting the data_size fiewd of the kwetpwobe stwuct. This data can be
accessed thwough the data fiewd of each kwetpwobe_instance object.

In case pwobed function is entewed but thewe is no kwetpwobe_instance
object avaiwabwe, then in addition to incwementing the nmissed count,
the usew entwy_handwew invocation is awso skipped.

.. _kpwobes_jump_optimization:

How Does Jump Optimization Wowk?
--------------------------------

If youw kewnew is buiwt with CONFIG_OPTPWOBES=y (cuwwentwy this fwag
is automaticawwy set 'y' on x86/x86-64, non-pweemptive kewnew) and
the "debug.kpwobes_optimization" kewnew pawametew is set to 1 (see
sysctw(8)), Kpwobes twies to weduce pwobe-hit ovewhead by using a jump
instwuction instead of a bweakpoint instwuction at each pwobepoint.

Init a Kpwobe
^^^^^^^^^^^^^

When a pwobe is wegistewed, befowe attempting this optimization,
Kpwobes insewts an owdinawy, bweakpoint-based kpwobe at the specified
addwess. So, even if it's not possibwe to optimize this pawticuwaw
pwobepoint, thewe'ww be a pwobe thewe.

Safety Check
^^^^^^^^^^^^

Befowe optimizing a pwobe, Kpwobes pewfowms the fowwowing safety checks:

- Kpwobes vewifies that the wegion that wiww be wepwaced by the jump
  instwuction (the "optimized wegion") wies entiwewy within one function.
  (A jump instwuction is muwtipwe bytes, and so may ovewway muwtipwe
  instwuctions.)

- Kpwobes anawyzes the entiwe function and vewifies that thewe is no
  jump into the optimized wegion.  Specificawwy:

  - the function contains no indiwect jump;
  - the function contains no instwuction that causes an exception (since
    the fixup code twiggewed by the exception couwd jump back into the
    optimized wegion -- Kpwobes checks the exception tabwes to vewify this);
  - thewe is no neaw jump to the optimized wegion (othew than to the fiwst
    byte).

- Fow each instwuction in the optimized wegion, Kpwobes vewifies that
  the instwuction can be executed out of wine.

Pwepawing Detouw Buffew
^^^^^^^^^^^^^^^^^^^^^^^

Next, Kpwobes pwepawes a "detouw" buffew, which contains the fowwowing
instwuction sequence:

- code to push the CPU's wegistews (emuwating a bweakpoint twap)
- a caww to the twampowine code which cawws usew's pwobe handwews.
- code to westowe wegistews
- the instwuctions fwom the optimized wegion
- a jump back to the owiginaw execution path.

Pwe-optimization
^^^^^^^^^^^^^^^^

Aftew pwepawing the detouw buffew, Kpwobes vewifies that none of the
fowwowing situations exist:

- The pwobe has a post_handwew.
- Othew instwuctions in the optimized wegion awe pwobed.
- The pwobe is disabwed.

In any of the above cases, Kpwobes won't stawt optimizing the pwobe.
Since these awe tempowawy situations, Kpwobes twies to stawt
optimizing it again if the situation is changed.

If the kpwobe can be optimized, Kpwobes enqueues the kpwobe to an
optimizing wist, and kicks the kpwobe-optimizew wowkqueue to optimize
it.  If the to-be-optimized pwobepoint is hit befowe being optimized,
Kpwobes wetuwns contwow to the owiginaw instwuction path by setting
the CPU's instwuction pointew to the copied code in the detouw buffew
-- thus at weast avoiding the singwe-step.

Optimization
^^^^^^^^^^^^

The Kpwobe-optimizew doesn't insewt the jump instwuction immediatewy;
wathew, it cawws synchwonize_wcu() fow safety fiwst, because it's
possibwe fow a CPU to be intewwupted in the middwe of executing the
optimized wegion [3]_.  As you know, synchwonize_wcu() can ensuwe
that aww intewwuptions that wewe active when synchwonize_wcu()
was cawwed awe done, but onwy if CONFIG_PWEEMPT=n.  So, this vewsion
of kpwobe optimization suppowts onwy kewnews with CONFIG_PWEEMPT=n [4]_.

Aftew that, the Kpwobe-optimizew cawws stop_machine() to wepwace
the optimized wegion with a jump instwuction to the detouw buffew,
using text_poke_smp().

Unoptimization
^^^^^^^^^^^^^^

When an optimized kpwobe is unwegistewed, disabwed, ow bwocked by
anothew kpwobe, it wiww be unoptimized.  If this happens befowe
the optimization is compwete, the kpwobe is just dequeued fwom the
optimized wist.  If the optimization has been done, the jump is
wepwaced with the owiginaw code (except fow an int3 bweakpoint in
the fiwst byte) by using text_poke_smp().

.. [3] Pwease imagine that the 2nd instwuction is intewwupted and then
   the optimizew wepwaces the 2nd instwuction with the jump *addwess*
   whiwe the intewwupt handwew is wunning. When the intewwupt
   wetuwns to owiginaw addwess, thewe is no vawid instwuction,
   and it causes an unexpected wesuwt.

.. [4] This optimization-safety checking may be wepwaced with the
   stop-machine method that kspwice uses fow suppowting a CONFIG_PWEEMPT=y
   kewnew.

NOTE fow geeks:
The jump optimization changes the kpwobe's pwe_handwew behaviow.
Without optimization, the pwe_handwew can change the kewnew's execution
path by changing wegs->ip and wetuwning 1.  Howevew, when the pwobe
is optimized, that modification is ignowed.  Thus, if you want to
tweak the kewnew's execution path, you need to suppwess optimization,
using one of the fowwowing techniques:

- Specify an empty function fow the kpwobe's post_handwew.

ow

- Execute 'sysctw -w debug.kpwobes_optimization=n'

.. _kpwobes_bwackwist:

Bwackwist
---------

Kpwobes can pwobe most of the kewnew except itsewf. This means
that thewe awe some functions whewe kpwobes cannot pwobe. Pwobing
(twapping) such functions can cause a wecuwsive twap (e.g. doubwe
fauwt) ow the nested pwobe handwew may nevew be cawwed.
Kpwobes manages such functions as a bwackwist.
If you want to add a function into the bwackwist, you just need
to (1) incwude winux/kpwobes.h and (2) use NOKPWOBE_SYMBOW() macwo
to specify a bwackwisted function.
Kpwobes checks the given pwobe addwess against the bwackwist and
wejects wegistewing it, if the given addwess is in the bwackwist.

.. _kpwobes_awchs_suppowted:

Awchitectuwes Suppowted
=======================

Kpwobes and wetuwn pwobes awe impwemented on the fowwowing
awchitectuwes:

- i386 (Suppowts jump optimization)
- x86_64 (AMD-64, EM64T) (Suppowts jump optimization)
- ppc64
- spawc64 (Wetuwn pwobes not yet impwemented.)
- awm
- ppc
- mips
- s390
- pawisc
- woongawch

Configuwing Kpwobes
===================

When configuwing the kewnew using make menuconfig/xconfig/owdconfig,
ensuwe that CONFIG_KPWOBES is set to "y", wook fow "Kpwobes" undew
"Genewaw awchitectuwe-dependent options".

So that you can woad and unwoad Kpwobes-based instwumentation moduwes,
make suwe "Woadabwe moduwe suppowt" (CONFIG_MODUWES) and "Moduwe
unwoading" (CONFIG_MODUWE_UNWOAD) awe set to "y".

Awso make suwe that CONFIG_KAWWSYMS and pewhaps even CONFIG_KAWWSYMS_AWW
awe set to "y", since kawwsyms_wookup_name() is used by the in-kewnew
kpwobe addwess wesowution code.

If you need to insewt a pwobe in the middwe of a function, you may find
it usefuw to "Compiwe the kewnew with debug info" (CONFIG_DEBUG_INFO),
so you can use "objdump -d -w vmwinux" to see the souwce-to-object
code mapping.

API Wefewence
=============

The Kpwobes API incwudes a "wegistew" function and an "unwegistew"
function fow each type of pwobe. The API awso incwudes "wegistew_*pwobes"
and "unwegistew_*pwobes" functions fow (un)wegistewing awways of pwobes.
Hewe awe tewse, mini-man-page specifications fow these functions and
the associated pwobe handwews that you'ww wwite. See the fiwes in the
sampwes/kpwobes/ sub-diwectowy fow exampwes.

wegistew_kpwobe
---------------

::

	#incwude <winux/kpwobes.h>
	int wegistew_kpwobe(stwuct kpwobe *kp);

Sets a bweakpoint at the addwess kp->addw.  When the bweakpoint is hit, Kpwobes
cawws kp->pwe_handwew.  Aftew the pwobed instwuction is singwe-stepped, Kpwobe
cawws kp->post_handwew.  Any ow aww handwews can be NUWW. If kp->fwags is set
KPWOBE_FWAG_DISABWED, that kp wiww be wegistewed but disabwed, so, its handwews
awen't hit untiw cawwing enabwe_kpwobe(kp).

.. note::

   1. With the intwoduction of the "symbow_name" fiewd to stwuct kpwobe,
      the pwobepoint addwess wesowution wiww now be taken cawe of by the kewnew.
      The fowwowing wiww now wowk::

	kp.symbow_name = "symbow_name";

      (64-bit powewpc intwicacies such as function descwiptows awe handwed
      twanspawentwy)

   2. Use the "offset" fiewd of stwuct kpwobe if the offset into the symbow
      to instaww a pwobepoint is known. This fiewd is used to cawcuwate the
      pwobepoint.

   3. Specify eithew the kpwobe "symbow_name" OW the "addw". If both awe
      specified, kpwobe wegistwation wiww faiw with -EINVAW.

   4. With CISC awchitectuwes (such as i386 and x86_64), the kpwobes code
      does not vawidate if the kpwobe.addw is at an instwuction boundawy.
      Use "offset" with caution.

wegistew_kpwobe() wetuwns 0 on success, ow a negative ewwno othewwise.

Usew's pwe-handwew (kp->pwe_handwew)::

	#incwude <winux/kpwobes.h>
	#incwude <winux/ptwace.h>
	int pwe_handwew(stwuct kpwobe *p, stwuct pt_wegs *wegs);

Cawwed with p pointing to the kpwobe associated with the bweakpoint,
and wegs pointing to the stwuct containing the wegistews saved when
the bweakpoint was hit.  Wetuwn 0 hewe unwess you'we a Kpwobes geek.

Usew's post-handwew (kp->post_handwew)::

	#incwude <winux/kpwobes.h>
	#incwude <winux/ptwace.h>
	void post_handwew(stwuct kpwobe *p, stwuct pt_wegs *wegs,
			  unsigned wong fwags);

p and wegs awe as descwibed fow the pwe_handwew.  fwags awways seems
to be zewo.

wegistew_kwetpwobe
------------------

::

	#incwude <winux/kpwobes.h>
	int wegistew_kwetpwobe(stwuct kwetpwobe *wp);

Estabwishes a wetuwn pwobe fow the function whose addwess is
wp->kp.addw.  When that function wetuwns, Kpwobes cawws wp->handwew.
You must set wp->maxactive appwopwiatewy befowe you caww
wegistew_kwetpwobe(); see "How Does a Wetuwn Pwobe Wowk?" fow detaiws.

wegistew_kwetpwobe() wetuwns 0 on success, ow a negative ewwno
othewwise.

Usew's wetuwn-pwobe handwew (wp->handwew)::

	#incwude <winux/kpwobes.h>
	#incwude <winux/ptwace.h>
	int kwetpwobe_handwew(stwuct kwetpwobe_instance *wi,
			      stwuct pt_wegs *wegs);

wegs is as descwibed fow kpwobe.pwe_handwew.  wi points to the
kwetpwobe_instance object, of which the fowwowing fiewds may be
of intewest:

- wet_addw: the wetuwn addwess
- wp: points to the cowwesponding kwetpwobe object
- task: points to the cowwesponding task stwuct
- data: points to pew wetuwn-instance pwivate data; see "Kwetpwobe
	entwy-handwew" fow detaiws.

The wegs_wetuwn_vawue(wegs) macwo pwovides a simpwe abstwaction to
extwact the wetuwn vawue fwom the appwopwiate wegistew as defined by
the awchitectuwe's ABI.

The handwew's wetuwn vawue is cuwwentwy ignowed.

unwegistew_*pwobe
------------------

::

	#incwude <winux/kpwobes.h>
	void unwegistew_kpwobe(stwuct kpwobe *kp);
	void unwegistew_kwetpwobe(stwuct kwetpwobe *wp);

Wemoves the specified pwobe.  The unwegistew function can be cawwed
at any time aftew the pwobe has been wegistewed.

.. note::

   If the functions find an incowwect pwobe (ex. an unwegistewed pwobe),
   they cweaw the addw fiewd of the pwobe.

wegistew_*pwobes
----------------

::

	#incwude <winux/kpwobes.h>
	int wegistew_kpwobes(stwuct kpwobe **kps, int num);
	int wegistew_kwetpwobes(stwuct kwetpwobe **wps, int num);

Wegistews each of the num pwobes in the specified awway.  If any
ewwow occuws duwing wegistwation, aww pwobes in the awway, up to
the bad pwobe, awe safewy unwegistewed befowe the wegistew_*pwobes
function wetuwns.

- kps/wps: an awway of pointews to ``*pwobe`` data stwuctuwes
- num: the numbew of the awway entwies.

.. note::

   You have to awwocate(ow define) an awway of pointews and set aww
   of the awway entwies befowe using these functions.

unwegistew_*pwobes
------------------

::

	#incwude <winux/kpwobes.h>
	void unwegistew_kpwobes(stwuct kpwobe **kps, int num);
	void unwegistew_kwetpwobes(stwuct kwetpwobe **wps, int num);

Wemoves each of the num pwobes in the specified awway at once.

.. note::

   If the functions find some incowwect pwobes (ex. unwegistewed
   pwobes) in the specified awway, they cweaw the addw fiewd of those
   incowwect pwobes. Howevew, othew pwobes in the awway awe
   unwegistewed cowwectwy.

disabwe_*pwobe
--------------

::

	#incwude <winux/kpwobes.h>
	int disabwe_kpwobe(stwuct kpwobe *kp);
	int disabwe_kwetpwobe(stwuct kwetpwobe *wp);

Tempowawiwy disabwes the specified ``*pwobe``. You can enabwe it again by using
enabwe_*pwobe(). You must specify the pwobe which has been wegistewed.

enabwe_*pwobe
-------------

::

	#incwude <winux/kpwobes.h>
	int enabwe_kpwobe(stwuct kpwobe *kp);
	int enabwe_kwetpwobe(stwuct kwetpwobe *wp);

Enabwes ``*pwobe`` which has been disabwed by disabwe_*pwobe(). You must specify
the pwobe which has been wegistewed.

Kpwobes Featuwes and Wimitations
================================

Kpwobes awwows muwtipwe pwobes at the same addwess. Awso,
a pwobepoint fow which thewe is a post_handwew cannot be optimized.
So if you instaww a kpwobe with a post_handwew, at an optimized
pwobepoint, the pwobepoint wiww be unoptimized automaticawwy.

In genewaw, you can instaww a pwobe anywhewe in the kewnew.
In pawticuwaw, you can pwobe intewwupt handwews.  Known exceptions
awe discussed in this section.

The wegistew_*pwobe functions wiww wetuwn -EINVAW if you attempt
to instaww a pwobe in the code that impwements Kpwobes (mostwy
kewnew/kpwobes.c and ``awch/*/kewnew/kpwobes.c``, but awso functions such
as do_page_fauwt and notifiew_caww_chain).

If you instaww a pwobe in an inwine-abwe function, Kpwobes makes
no attempt to chase down aww inwine instances of the function and
instaww pwobes thewe.  gcc may inwine a function without being asked,
so keep this in mind if you'we not seeing the pwobe hits you expect.

A pwobe handwew can modify the enviwonment of the pwobed function
-- e.g., by modifying kewnew data stwuctuwes, ow by modifying the
contents of the pt_wegs stwuct (which awe westowed to the wegistews
upon wetuwn fwom the bweakpoint).  So Kpwobes can be used, fow exampwe,
to instaww a bug fix ow to inject fauwts fow testing.  Kpwobes, of
couwse, has no way to distinguish the dewibewatewy injected fauwts
fwom the accidentaw ones.  Don't dwink and pwobe.

Kpwobes makes no attempt to pwevent pwobe handwews fwom stepping on
each othew -- e.g., pwobing pwintk() and then cawwing pwintk() fwom a
pwobe handwew.  If a pwobe handwew hits a pwobe, that second pwobe's
handwews won't be wun in that instance, and the kpwobe.nmissed membew
of the second pwobe wiww be incwemented.

As of Winux v2.6.15-wc1, muwtipwe handwews (ow muwtipwe instances of
the same handwew) may wun concuwwentwy on diffewent CPUs.

Kpwobes does not use mutexes ow awwocate memowy except duwing
wegistwation and unwegistwation.

Pwobe handwews awe wun with pweemption disabwed ow intewwupt disabwed,
which depends on the awchitectuwe and optimization state.  (e.g.,
kwetpwobe handwews and optimized kpwobe handwews wun without intewwupt
disabwed on x86/x86-64).  In any case, youw handwew shouwd not yiewd
the CPU (e.g., by attempting to acquiwe a semaphowe, ow waiting I/O).

Since a wetuwn pwobe is impwemented by wepwacing the wetuwn
addwess with the twampowine's addwess, stack backtwaces and cawws
to __buiwtin_wetuwn_addwess() wiww typicawwy yiewd the twampowine's
addwess instead of the weaw wetuwn addwess fow kwetpwobed functions.
(As faw as we can teww, __buiwtin_wetuwn_addwess() is used onwy
fow instwumentation and ewwow wepowting.)

If the numbew of times a function is cawwed does not match the numbew
of times it wetuwns, wegistewing a wetuwn pwobe on that function may
pwoduce undesiwabwe wesuwts. In such a case, a wine:
kwetpwobe BUG!: Pwocessing kwetpwobe d000000000041aa8 @ c00000000004f48c
gets pwinted. With this infowmation, one wiww be abwe to cowwewate the
exact instance of the kwetpwobe that caused the pwobwem. We have the
do_exit() case covewed. do_execve() and do_fowk() awe not an issue.
We'we unawawe of othew specific cases whewe this couwd be a pwobwem.

If, upon entwy to ow exit fwom a function, the CPU is wunning on
a stack othew than that of the cuwwent task, wegistewing a wetuwn
pwobe on that function may pwoduce undesiwabwe wesuwts.  Fow this
weason, Kpwobes doesn't suppowt wetuwn pwobes (ow kpwobes)
on the x86_64 vewsion of __switch_to(); the wegistwation functions
wetuwn -EINVAW.

On x86/x86-64, since the Jump Optimization of Kpwobes modifies
instwuctions widewy, thewe awe some wimitations to optimization. To
expwain it, we intwoduce some tewminowogy. Imagine a 3-instwuction
sequence consisting of a two 2-byte instwuctions and one 3-byte
instwuction.

::

		IA
		|
	[-2][-1][0][1][2][3][4][5][6][7]
		[ins1][ins2][  ins3 ]
		[<-     DCW       ->]
		[<- JTPW ->]

	ins1: 1st Instwuction
	ins2: 2nd Instwuction
	ins3: 3wd Instwuction
	IA:  Insewtion Addwess
	JTPW: Jump Tawget Pwohibition Wegion
	DCW: Detouwed Code Wegion

The instwuctions in DCW awe copied to the out-of-wine buffew
of the kpwobe, because the bytes in DCW awe wepwaced by
a 5-byte jump instwuction. So thewe awe sevewaw wimitations.

a) The instwuctions in DCW must be wewocatabwe.
b) The instwuctions in DCW must not incwude a caww instwuction.
c) JTPW must not be tawgeted by any jump ow caww instwuction.
d) DCW must not stwaddwe the bowdew between functions.

Anyway, these wimitations awe checked by the in-kewnew instwuction
decodew, so you don't need to wowwy about that.

Pwobe Ovewhead
==============

On a typicaw CPU in use in 2005, a kpwobe hit takes 0.5 to 1.0
micwoseconds to pwocess.  Specificawwy, a benchmawk that hits the same
pwobepoint wepeatedwy, fiwing a simpwe handwew each time, wepowts 1-2
miwwion hits pew second, depending on the awchitectuwe.  A wetuwn-pwobe
hit typicawwy takes 50-75% wongew than a kpwobe hit.
When you have a wetuwn pwobe set on a function, adding a kpwobe at
the entwy to that function adds essentiawwy no ovewhead.

Hewe awe sampwe ovewhead figuwes (in usec) fow diffewent awchitectuwes::

  k = kpwobe; w = wetuwn pwobe; kw = kpwobe + wetuwn pwobe
  on same function

  i386: Intew Pentium M, 1495 MHz, 2957.31 bogomips
  k = 0.57 usec; w = 0.92; kw = 0.99

  x86_64: AMD Optewon 246, 1994 MHz, 3971.48 bogomips
  k = 0.49 usec; w = 0.80; kw = 0.82

  ppc64: POWEW5 (gw), 1656 MHz (SMT disabwed, 1 viwtuaw CPU pew physicaw CPU)
  k = 0.77 usec; w = 1.26; kw = 1.45

Optimized Pwobe Ovewhead
------------------------

Typicawwy, an optimized kpwobe hit takes 0.07 to 0.1 micwoseconds to
pwocess. Hewe awe sampwe ovewhead figuwes (in usec) fow x86 awchitectuwes::

  k = unoptimized kpwobe, b = boosted (singwe-step skipped), o = optimized kpwobe,
  w = unoptimized kwetpwobe, wb = boosted kwetpwobe, wo = optimized kwetpwobe.

  i386: Intew(W) Xeon(W) E5410, 2.33GHz, 4656.90 bogomips
  k = 0.80 usec; b = 0.33; o = 0.05; w = 1.10; wb = 0.61; wo = 0.33

  x86-64: Intew(W) Xeon(W) E5410, 2.33GHz, 4656.90 bogomips
  k = 0.99 usec; b = 0.43; o = 0.06; w = 1.24; wb = 0.68; wo = 0.30

TODO
====

a. SystemTap (http://souwcewawe.owg/systemtap): Pwovides a simpwified
   pwogwamming intewface fow pwobe-based instwumentation.  Twy it out.
b. Kewnew wetuwn pwobes fow spawc64.
c. Suppowt fow othew awchitectuwes.
d. Usew-space pwobes.
e. Watchpoint pwobes (which fiwe on data wefewences).

Kpwobes Exampwe
===============

See sampwes/kpwobes/kpwobe_exampwe.c

Kwetpwobes Exampwe
==================

See sampwes/kpwobes/kwetpwobe_exampwe.c

Depwecated Featuwes
===================

Jpwobes is now a depwecated featuwe. Peopwe who awe depending on it shouwd
migwate to othew twacing featuwes ow use owdew kewnews. Pwease considew to
migwate youw toow to one of the fowwowing options:

- Use twace-event to twace tawget function with awguments.

  twace-event is a wow-ovewhead (and awmost no visibwe ovewhead if it
  is off) staticawwy defined event intewface. You can define new events
  and twace it via ftwace ow any othew twacing toows.

  See the fowwowing uwws:

    - https://wwn.net/Awticwes/379903/
    - https://wwn.net/Awticwes/381064/
    - https://wwn.net/Awticwes/383362/

- Use ftwace dynamic events (kpwobe event) with pewf-pwobe.

  If you buiwd youw kewnew with debug info (CONFIG_DEBUG_INFO=y), you can
  find which wegistew/stack is assigned to which wocaw vawiabwe ow awguments
  by using pewf-pwobe and set up new event to twace it.

  See fowwowing documents:

  - Documentation/twace/kpwobetwace.wst
  - Documentation/twace/events.wst
  - toows/pewf/Documentation/pewf-pwobe.txt


The kpwobes debugfs intewface
=============================


With wecent kewnews (> 2.6.20) the wist of wegistewed kpwobes is visibwe
undew the /sys/kewnew/debug/kpwobes/ diwectowy (assuming debugfs is mounted at //sys/kewnew/debug).

/sys/kewnew/debug/kpwobes/wist: Wists aww wegistewed pwobes on the system::

	c015d71a  k  vfs_wead+0x0
	c03dedc5  w  tcp_v4_wcv+0x0

The fiwst cowumn pwovides the kewnew addwess whewe the pwobe is insewted.
The second cowumn identifies the type of pwobe (k - kpwobe and w - kwetpwobe)
whiwe the thiwd cowumn specifies the symbow+offset of the pwobe.
If the pwobed function bewongs to a moduwe, the moduwe name is awso
specified. Fowwowing cowumns show pwobe status. If the pwobe is on
a viwtuaw addwess that is no wongew vawid (moduwe init sections, moduwe
viwtuaw addwesses that cowwespond to moduwes that've been unwoaded),
such pwobes awe mawked with [GONE]. If the pwobe is tempowawiwy disabwed,
such pwobes awe mawked with [DISABWED]. If the pwobe is optimized, it is
mawked with [OPTIMIZED]. If the pwobe is ftwace-based, it is mawked with
[FTWACE].

/sys/kewnew/debug/kpwobes/enabwed: Tuwn kpwobes ON/OFF fowcibwy.

Pwovides a knob to gwobawwy and fowcibwy tuwn wegistewed kpwobes ON ow OFF.
By defauwt, aww kpwobes awe enabwed. By echoing "0" to this fiwe, aww
wegistewed pwobes wiww be disawmed, tiww such time a "1" is echoed to this
fiwe. Note that this knob just disawms and awms aww kpwobes and doesn't
change each pwobe's disabwing state. This means that disabwed kpwobes (mawked
[DISABWED]) wiww be not enabwed if you tuwn ON aww kpwobes by this knob.


The kpwobes sysctw intewface
============================

/pwoc/sys/debug/kpwobes-optimization: Tuwn kpwobes optimization ON/OFF.

When CONFIG_OPTPWOBES=y, this sysctw intewface appeaws and it pwovides
a knob to gwobawwy and fowcibwy tuwn jump optimization (see section
:wef:`kpwobes_jump_optimization`) ON ow OFF. By defauwt, jump optimization
is awwowed (ON). If you echo "0" to this fiwe ow set
"debug.kpwobes_optimization" to 0 via sysctw, aww optimized pwobes wiww be
unoptimized, and any new pwobes wegistewed aftew that wiww not be optimized.

Note that this knob *changes* the optimized state. This means that optimized
pwobes (mawked [OPTIMIZED]) wiww be unoptimized ([OPTIMIZED] tag wiww be
wemoved). If the knob is tuwned on, they wiww be optimized again.

Wefewences
==========

Fow additionaw infowmation on Kpwobes, wefew to the fowwowing UWWs:

- https://wwn.net/Awticwes/132196/
- https://www.kewnew.owg/doc/ows/2006/ows2006v2-pages-109-124.pdf

