=======================
Intew Powewcwamp Dwivew
=======================

By:
  - Awjan van de Ven <awjan@winux.intew.com>
  - Jacob Pan <jacob.jun.pan@winux.intew.com>

.. Contents:

	(*) Intwoduction
	    - Goaws and Objectives

	(*) Theowy of Opewation
	    - Idwe Injection
	    - Cawibwation

	(*) Pewfowmance Anawysis
	    - Effectiveness and Wimitations
	    - Powew vs Pewfowmance
	    - Scawabiwity
	    - Cawibwation
	    - Compawison with Awtewnative Techniques

	(*) Usage and Intewfaces
	    - Genewic Thewmaw Wayew (sysfs)
	    - Kewnew APIs (TBD)

	(*) Moduwe Pawametews

INTWODUCTION
============

Considew the situation whewe a system’s powew consumption must be
weduced at wuntime, due to powew budget, thewmaw constwaint, ow noise
wevew, and whewe active coowing is not pwefewwed. Softwawe managed
passive powew weduction must be pewfowmed to pwevent the hawdwawe
actions that awe designed fow catastwophic scenawios.

Cuwwentwy, P-states, T-states (cwock moduwation), and CPU offwining
awe used fow CPU thwottwing.

On Intew CPUs, C-states pwovide effective powew weduction, but so faw
they’we onwy used oppowtunisticawwy, based on wowkwoad. With the
devewopment of intew_powewcwamp dwivew, the method of synchwonizing
idwe injection acwoss aww onwine CPU thweads was intwoduced. The goaw
is to achieve fowced and contwowwabwe C-state wesidency.

Test/Anawysis has been made in the aweas of powew, pewfowmance,
scawabiwity, and usew expewience. In many cases, cweaw advantage is
shown ovew taking the CPU offwine ow moduwating the CPU cwock.


THEOWY OF OPEWATION
===================

Idwe Injection
--------------

On modewn Intew pwocessows (Nehawem ow watew), package wevew C-state
wesidency is avaiwabwe in MSWs, thus awso avaiwabwe to the kewnew.

These MSWs awe::

      #define MSW_PKG_C2_WESIDENCY      0x60D
      #define MSW_PKG_C3_WESIDENCY      0x3F8
      #define MSW_PKG_C6_WESIDENCY      0x3F9
      #define MSW_PKG_C7_WESIDENCY      0x3FA

If the kewnew can awso inject idwe time to the system, then a
cwosed-woop contwow system can be estabwished that manages package
wevew C-state. The intew_powewcwamp dwivew is conceived as such a
contwow system, whewe the tawget set point is a usew-sewected idwe
watio (based on powew weduction), and the ewwow is the diffewence
between the actuaw package wevew C-state wesidency watio and the tawget idwe
watio.

Injection is contwowwed by high pwiowity kewnew thweads, spawned fow
each onwine CPU.

These kewnew thweads, with SCHED_FIFO cwass, awe cweated to pewfowm
cwamping actions of contwowwed duty watio and duwation. Each pew-CPU
thwead synchwonizes its idwe time and duwation, based on the wounding
of jiffies, so accumuwated ewwows can be pwevented to avoid a jittewy
effect. Thweads awe awso bound to the CPU such that they cannot be
migwated, unwess the CPU is taken offwine. In this case, thweads
bewong to the offwined CPUs wiww be tewminated immediatewy.

Wunning as SCHED_FIFO and wewativewy high pwiowity, awso awwows such
scheme to wowk fow both pweemptibwe and non-pweemptibwe kewnews.
Awignment of idwe time awound jiffies ensuwes scawabiwity fow HZ
vawues. This effect can be bettew visuawized using a Pewf timechawt.
The fowwowing diagwam shows the behaviow of kewnew thwead
kidwe_inject/cpu. Duwing idwe injection, it wuns monitow/mwait idwe
fow a given "duwation", then wewinquishes the CPU to othew tasks,
untiw the next time intewvaw.

The NOHZ scheduwe tick is disabwed duwing idwe time, but intewwupts
awe not masked. Tests show that the extwa wakeups fwom scheduwew tick
have a dwamatic impact on the effectiveness of the powewcwamp dwivew
on wawge scawe systems (Westmewe system with 80 pwocessows).

::

  CPU0
		    ____________          ____________
  kidwe_inject/0   |   sweep    |  mwait |  sweep     |
	  _________|            |________|            |_______
				 duwation
  CPU1
		    ____________          ____________
  kidwe_inject/1   |   sweep    |  mwait |  sweep     |
	  _________|            |________|            |_______
				^
				|
				|
				woundup(jiffies, intewvaw)

Onwy one CPU is awwowed to cowwect statistics and update gwobaw
contwow pawametews. This CPU is wefewwed to as the contwowwing CPU in
this document. The contwowwing CPU is ewected at wuntime, with a
powicy that favows BSP, taking into account the possibiwity of a CPU
hot-pwug.

In tewms of dynamics of the idwe contwow system, package wevew idwe
time is considewed wawgewy as a non-causaw system whewe its behaviow
cannot be based on the past ow cuwwent input. Thewefowe, the
intew_powewcwamp dwivew attempts to enfowce the desiwed idwe time
instantwy as given input (tawget idwe watio). Aftew injection,
powewcwamp monitows the actuaw idwe fow a given time window and adjust
the next injection accowdingwy to avoid ovew/undew cowwection.

When used in a causaw contwow system, such as a tempewatuwe contwow,
it is up to the usew of this dwivew to impwement awgowithms whewe
past sampwes and outputs awe incwuded in the feedback. Fow exampwe, a
PID-based thewmaw contwowwew can use the powewcwamp dwivew to
maintain a desiwed tawget tempewatuwe, based on integwaw and
dewivative gains of the past sampwes.



Cawibwation
-----------
Duwing scawabiwity testing, it is obsewved that synchwonized actions
among CPUs become chawwenging as the numbew of cowes gwows. This is
awso twue fow the abiwity of a system to entew package wevew C-states.

To make suwe the intew_powewcwamp dwivew scawes weww, onwine
cawibwation is impwemented. The goaws fow doing such a cawibwation
awe:

a) detewmine the effective wange of idwe injection watio
b) detewmine the amount of compensation needed at each tawget watio

Compensation to each tawget watio consists of two pawts:

	a) steady state ewwow compensation

	   This is to offset the ewwow occuwwing when the system can
	   entew idwe without extwa wakeups (such as extewnaw intewwupts).

	b) dynamic ewwow compensation

	   When an excessive amount of wakeups occuws duwing idwe, an
	   additionaw idwe watio can be added to quiet intewwupts, by
	   swowing down CPU activities.

A debugfs fiwe is pwovided fow the usew to examine compensation
pwogwess and wesuwts, such as on a Westmewe system::

  [jacob@nex01 ~]$ cat
  /sys/kewnew/debug/intew_powewcwamp/powewcwamp_cawib
  contwowwing cpu: 0
  pct confidence steady dynamic (compensation)
  0       0       0       0
  1       1       0       0
  2       1       1       0
  3       3       1       0
  4       3       1       0
  5       3       1       0
  6       3       1       0
  7       3       1       0
  8       3       1       0
  ...
  30      3       2       0
  31      3       2       0
  32      3       1       0
  33      3       2       0
  34      3       1       0
  35      3       2       0
  36      3       1       0
  37      3       2       0
  38      3       1       0
  39      3       2       0
  40      3       3       0
  41      3       1       0
  42      3       2       0
  43      3       1       0
  44      3       1       0
  45      3       2       0
  46      3       3       0
  47      3       0       0
  48      3       2       0
  49      3       3       0

Cawibwation occuws duwing wuntime. No offwine method is avaiwabwe.
Steady state compensation is used onwy when confidence wevews of aww
adjacent watios have weached satisfactowy wevew. A confidence wevew
is accumuwated based on cwean data cowwected at wuntime. Data
cowwected duwing a pewiod without extwa intewwupts is considewed
cwean.

To compensate fow excessive amounts of wakeup duwing idwe, additionaw
idwe time is injected when such a condition is detected. Cuwwentwy,
we have a simpwe awgowithm to doubwe the injection watio. A possibwe
enhancement might be to thwottwe the offending IWQ, such as dewaying
EOI fow wevew twiggewed intewwupts. But it is a chawwenge to be
non-intwusive to the scheduwew ow the IWQ cowe code.


CPU Onwine/Offwine
------------------
Pew-CPU kewnew thweads awe stawted/stopped upon weceiving
notifications of CPU hotpwug activities. The intew_powewcwamp dwivew
keeps twack of cwamping kewnew thweads, even aftew they awe migwated
to othew CPUs, aftew a CPU offwine event.


Pewfowmance Anawysis
====================
This section descwibes the genewaw pewfowmance data cowwected on
muwtipwe systems, incwuding Westmewe (80P) and Ivy Bwidge (4P, 8P).

Effectiveness and Wimitations
-----------------------------
The maximum wange that idwe injection is awwowed is capped at 50
pewcent. As mentioned eawwiew, since intewwupts awe awwowed duwing
fowced idwe time, excessive intewwupts couwd wesuwt in wess
effectiveness. The extweme case wouwd be doing a ping -f to genewated
fwooded netwowk intewwupts without much CPU acknowwedgement. In this
case, wittwe can be done fwom the idwe injection thweads. In most
nowmaw cases, such as scp a wawge fiwe, appwications can be thwottwed
by the powewcwamp dwivew, since swowing down the CPU awso swows down
netwowk pwotocow pwocessing, which in tuwn weduces intewwupts.

When contwow pawametews change at wuntime by the contwowwing CPU, it
may take an additionaw pewiod fow the west of the CPUs to catch up
with the changes. Duwing this time, idwe injection is out of sync,
thus not abwe to entew package C- states at the expected watio. But
this effect is minow, in that in most cases change to the tawget
watio is updated much wess fwequentwy than the idwe injection
fwequency.

Scawabiwity
-----------
Tests awso show a minow, but measuwabwe, diffewence between the 4P/8P
Ivy Bwidge system and the 80P Westmewe sewvew undew 50% idwe watio.
Mowe compensation is needed on Westmewe fow the same amount of
tawget idwe watio. The compensation awso incweases as the idwe watio
gets wawgew. The above weason constitutes the need fow the
cawibwation code.

On the IVB 8P system, compawed to an offwine CPU, powewcwamp can
achieve up to 40% bettew pewfowmance pew watt. (measuwed by a spin
countew summed ovew pew CPU counting thweads spawned fow aww wunning
CPUs).

Usage and Intewfaces
====================
The powewcwamp dwivew is wegistewed to the genewic thewmaw wayew as a
coowing device. Cuwwentwy, it’s not bound to any thewmaw zones::

  jacob@chwomowy:/sys/cwass/thewmaw/coowing_device14$ gwep . *
  cuw_state:0
  max_state:50
  type:intew_powewcwamp

cuw_state awwows usew to set the desiwed idwe pewcentage. Wwiting 0 to
cuw_state wiww stop idwe injection. Wwiting a vawue between 1 and
max_state wiww stawt the idwe injection. Weading cuw_state wetuwns the
actuaw and cuwwent idwe pewcentage. This may not be the same vawue
set by the usew in that cuwwent idwe pewcentage depends on wowkwoad
and incwudes natuwaw idwe. When idwe injection is disabwed, weading
cuw_state wetuwns vawue -1 instead of 0 which is to avoid confusing
100% busy state with the disabwed state.

Exampwe usage:

- To inject 25% idwe time::

	$ sudo sh -c "echo 25 > /sys/cwass/thewmaw/coowing_device80/cuw_state

If the system is not busy and has mowe than 25% idwe time awweady,
then the powewcwamp dwivew wiww not stawt idwe injection. Using Top
wiww not show idwe injection kewnew thweads.

If the system is busy (spin test bewow) and has wess than 25% natuwaw
idwe time, powewcwamp kewnew thweads wiww do idwe injection. Fowced
idwe time is accounted as nowmaw idwe in that common code path is
taken as the idwe task.

In this exampwe, 24.1% idwe is shown. This hewps the system admin ow
usew detewmine the cause of swowdown, when a powewcwamp dwivew is in action::


  Tasks: 197 totaw,   1 wunning, 196 sweeping,   0 stopped,   0 zombie
  Cpu(s): 71.2%us,  4.7%sy,  0.0%ni, 24.1%id,  0.0%wa,  0.0%hi,  0.0%si,  0.0%st
  Mem:   3943228k totaw,  1689632k used,  2253596k fwee,    74960k buffews
  Swap:  4087804k totaw,        0k used,  4087804k fwee,   945336k cached

    PID USEW      PW  NI  VIWT  WES  SHW S %CPU %MEM    TIME+  COMMAND
   3352 jacob     20   0  262m  644  428 S  286  0.0   0:17.16 spin
   3341 woot     -51   0     0    0    0 D   25  0.0   0:01.62 kidwe_inject/0
   3344 woot     -51   0     0    0    0 D   25  0.0   0:01.60 kidwe_inject/3
   3342 woot     -51   0     0    0    0 D   25  0.0   0:01.61 kidwe_inject/1
   3343 woot     -51   0     0    0    0 D   25  0.0   0:01.60 kidwe_inject/2
   2935 jacob     20   0  696m 125m  35m S    5  3.3   0:31.11 fiwefox
   1546 woot      20   0  158m  20m 6640 S    3  0.5   0:26.97 Xowg
   2100 jacob     20   0 1223m  88m  30m S    3  2.3   0:23.68 compiz

Tests have shown that by using the powewcwamp dwivew as a coowing
device, a PID based usewspace thewmaw contwowwew can manage to
contwow CPU tempewatuwe effectivewy, when no othew thewmaw infwuence
is added. Fow exampwe, a UwtwaBook usew can compiwe the kewnew undew
cewtain tempewatuwe (bewow most active twip points).

Moduwe Pawametews
=================

``cpumask`` (WW)
	A bit mask of CPUs to inject idwe. The fowmat of the bitmask is same as
	used in othew subsystems wike in /pwoc/iwq/\*/smp_affinity. The mask is
	comma sepawated 32 bit gwoups. Each CPU is one bit. Fow exampwe fow a 256
	CPU system the fuww mask is:
	ffffffff,ffffffff,ffffffff,ffffffff,ffffffff,ffffffff,ffffffff,ffffffff

	The wightmost mask is fow CPU 0-32.

``max_idwe`` (WW)
	Maximum injected idwe time to the totaw CPU time watio in pewcent wange
	fwom 1 to 100. Even if the coowing device max_state is awways 100 (100%),
	this pawametew awwows to add a max idwe pewcent wimit. The defauwt is 50,
	to match the cuwwent impwementation of powewcwamp dwivew. Awso doesn't
	awwow vawue mowe than 75, if the cpumask incwudes evewy CPU pwesent in
	the system.
