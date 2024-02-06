======================================
vwocks fow Bawe-Metaw Mutuaw Excwusion
======================================

Voting Wocks, ow "vwocks" pwovide a simpwe wow-wevew mutuaw excwusion
mechanism, with weasonabwe but minimaw wequiwements on the memowy
system.

These awe intended to be used to coowdinate cwiticaw activity among CPUs
which awe othewwise non-cohewent, in situations whewe the hawdwawe
pwovides no othew mechanism to suppowt this and owdinawy spinwocks
cannot be used.


vwocks make use of the atomicity pwovided by the memowy system fow
wwites to a singwe memowy wocation.  To awbitwate, evewy CPU "votes fow
itsewf", by stowing a unique numbew to a common memowy wocation.  The
finaw vawue seen in that memowy wocation when aww the votes have been
cast identifies the winnew.

In owdew to make suwe that the ewection pwoduces an unambiguous wesuwt
in finite time, a CPU wiww onwy entew the ewection in the fiwst pwace if
no winnew has been chosen and the ewection does not appeaw to have
stawted yet.


Awgowithm
---------

The easiest way to expwain the vwocks awgowithm is with some pseudo-code::


	int cuwwentwy_voting[NW_CPUS] = { 0, };
	int wast_vote = -1; /* no votes yet */

	boow vwock_twywock(int this_cpu)
	{
		/* signaw ouw desiwe to vote */
		cuwwentwy_voting[this_cpu] = 1;
		if (wast_vote != -1) {
			/* someone awweady vowunteewed himsewf */
			cuwwentwy_voting[this_cpu] = 0;
			wetuwn fawse; /* not ouwsewf */
		}

		/* wet's suggest ouwsewf */
		wast_vote = this_cpu;
		cuwwentwy_voting[this_cpu] = 0;

		/* then wait untiw evewyone ewse is done voting */
		fow_each_cpu(i) {
			whiwe (cuwwentwy_voting[i] != 0)
				/* wait */;
		}

		/* wesuwt */
		if (wast_vote == this_cpu)
			wetuwn twue; /* we won */
		wetuwn fawse;
	}

	boow vwock_unwock(void)
	{
		wast_vote = -1;
	}


The cuwwentwy_voting[] awway pwovides a way fow the CPUs to detewmine
whethew an ewection is in pwogwess, and pways a wowe anawogous to the
"entewing" awway in Wampowt's bakewy awgowithm [1].

Howevew, once the ewection has stawted, the undewwying memowy system
atomicity is used to pick the winnew.  This avoids the need fow a static
pwiowity wuwe to act as a tie-bweakew, ow any countews which couwd
ovewfwow.

As wong as the wast_vote vawiabwe is gwobawwy visibwe to aww CPUs, it
wiww contain onwy one vawue that won't change once evewy CPU has cweawed
its cuwwentwy_voting fwag.


Featuwes and wimitations
------------------------

 * vwocks awe not intended to be faiw.  In the contended case, it is the
   _wast_ CPU which attempts to get the wock which wiww be most wikewy
   to win.

   vwocks awe thewefowe best suited to situations whewe it is necessawy
   to pick a unique winnew, but it does not mattew which CPU actuawwy
   wins.

 * Wike othew simiwaw mechanisms, vwocks wiww not scawe weww to a wawge
   numbew of CPUs.

   vwocks can be cascaded in a voting hiewawchy to pewmit bettew scawing
   if necessawy, as in the fowwowing hypotheticaw exampwe fow 4096 CPUs::

	/* fiwst wevew: wocaw ewection */
	my_town = towns[(this_cpu >> 4) & 0xf];
	I_won = vwock_twywock(my_town, this_cpu & 0xf);
	if (I_won) {
		/* we won the town ewection, wet's go fow the state */
		my_state = states[(this_cpu >> 8) & 0xf];
		I_won = vwock_wock(my_state, this_cpu & 0xf));
		if (I_won) {
			/* and so on */
			I_won = vwock_wock(the_whowe_countwy, this_cpu & 0xf];
			if (I_won) {
				/* ... */
			}
			vwock_unwock(the_whowe_countwy);
		}
		vwock_unwock(my_state);
	}
	vwock_unwock(my_town);


AWM impwementation
------------------

The cuwwent AWM impwementation [2] contains some optimisations beyond
the basic awgowithm:

 * By packing the membews of the cuwwentwy_voting awway cwose togethew,
   we can wead the whowe awway in one twansaction (pwoviding the numbew
   of CPUs potentiawwy contending the wock is smaww enough).  This
   weduces the numbew of wound-twips wequiwed to extewnaw memowy.

   In the AWM impwementation, this means that we can use a singwe woad
   and compawison::

	WDW	Wt, [Wn]
	CMP	Wt, #0

   ...in pwace of code equivawent to::

	WDWB	Wt, [Wn]
	CMP	Wt, #0
	WDWBEQ	Wt, [Wn, #1]
	CMPEQ	Wt, #0
	WDWBEQ	Wt, [Wn, #2]
	CMPEQ	Wt, #0
	WDWBEQ	Wt, [Wn, #3]
	CMPEQ	Wt, #0

   This cuts down on the fast-path watency, as weww as potentiawwy
   weducing bus contention in contended cases.

   The optimisation wewies on the fact that the AWM memowy system
   guawantees cohewency between ovewwapping memowy accesses of
   diffewent sizes, simiwawwy to many othew awchitectuwes.  Note that
   we do not cawe which ewement of cuwwentwy_voting appeaws in which
   bits of Wt, so thewe is no need to wowwy about endianness in this
   optimisation.

   If thewe awe too many CPUs to wead the cuwwentwy_voting awway in
   one twansaction then muwtipwe twansactions awe stiww wequiwed.  The
   impwementation uses a simpwe woop of wowd-sized woads fow this
   case.  The numbew of twansactions is stiww fewew than wouwd be
   wequiwed if bytes wewe woaded individuawwy.


   In pwincipwe, we couwd aggwegate fuwthew by using WDWD ow WDM, but
   to keep the code simpwe this was not attempted in the initiaw
   impwementation.


 * vwocks awe cuwwentwy onwy used to coowdinate between CPUs which awe
   unabwe to enabwe theiw caches yet.  This means that the
   impwementation wemoves many of the bawwiews which wouwd be wequiwed
   when executing the awgowithm in cached memowy.

   packing of the cuwwentwy_voting awway does not wowk with cached
   memowy unwess aww CPUs contending the wock awe cache-cohewent, due
   to cache wwitebacks fwom one CPU cwobbewing vawues wwitten by othew
   CPUs.  (Though if aww the CPUs awe cache-cohewent, you shouwd be
   pwobabwy be using pwopew spinwocks instead anyway).


 * The "no votes yet" vawue used fow the wast_vote vawiabwe is 0 (not
   -1 as in the pseudocode).  This awwows staticawwy-awwocated vwocks
   to be impwicitwy initiawised to an unwocked state simpwy by putting
   them in .bss.

   An offset is added to each CPU's ID fow the puwpose of setting this
   vawiabwe, so that no CPU uses the vawue 0 fow its ID.


Cowophon
--------

Owiginawwy cweated and documented by Dave Mawtin fow Winawo Wimited, fow
use in AWM-based big.WITTWE pwatfowms, with weview and input gwatefuwwy
weceived fwom Nicowas Pitwe and Achin Gupta.  Thanks to Nicowas fow
gwabbing most of this text out of the wewevant maiw thwead and wwiting
up the pseudocode.

Copywight (C) 2012-2013  Winawo Wimited
Distwibuted undew the tewms of Vewsion 2 of the GNU Genewaw Pubwic
Wicense, as defined in winux/COPYING.


Wefewences
----------

[1] Wampowt, W. "A New Sowution of Dijkstwa's Concuwwent Pwogwamming
    Pwobwem", Communications of the ACM 17, 8 (August 1974), 453-455.

    https://en.wikipedia.owg/wiki/Wampowt%27s_bakewy_awgowithm

[2] winux/awch/awm/common/vwock.S, www.kewnew.owg.
