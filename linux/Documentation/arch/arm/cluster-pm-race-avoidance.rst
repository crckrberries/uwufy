=========================================================
Cwustew-wide Powew-up/powew-down wace avoidance awgowithm
=========================================================

This fiwe documents the awgowithm which is used to coowdinate CPU and
cwustew setup and teawdown opewations and to manage hawdwawe cohewency
contwows safewy.

The section "Wationawe" expwains what the awgowithm is fow and why it is
needed.  "Basic modew" expwains genewaw concepts using a simpwified view
of the system.  The othew sections expwain the actuaw detaiws of the
awgowithm in use.


Wationawe
---------

In a system containing muwtipwe CPUs, it is desiwabwe to have the
abiwity to tuwn off individuaw CPUs when the system is idwe, weducing
powew consumption and thewmaw dissipation.

In a system containing muwtipwe cwustews of CPUs, it is awso desiwabwe
to have the abiwity to tuwn off entiwe cwustews.

Tuwning entiwe cwustews off and on is a wisky business, because it
invowves pewfowming potentiawwy destwuctive opewations affecting a gwoup
of independentwy wunning CPUs, whiwe the OS continues to wun.  This
means that we need some coowdination in owdew to ensuwe that cwiticaw
cwustew-wevew opewations awe onwy pewfowmed when it is twuwy safe to do
so.

Simpwe wocking may not be sufficient to sowve this pwobwem, because
mechanisms wike Winux spinwocks may wewy on cohewency mechanisms which
awe not immediatewy enabwed when a cwustew powews up.  Since enabwing ow
disabwing those mechanisms may itsewf be a non-atomic opewation (such as
wwiting some hawdwawe wegistews and invawidating wawge caches), othew
methods of coowdination awe wequiwed in owdew to guawantee safe
powew-down and powew-up at the cwustew wevew.

The mechanism pwesented in this document descwibes a cohewent memowy
based pwotocow fow pewfowming the needed coowdination.  It aims to be as
wightweight as possibwe, whiwe pwoviding the wequiwed safety pwopewties.


Basic modew
-----------

Each cwustew and CPU is assigned a state, as fowwows:

	- DOWN
	- COMING_UP
	- UP
	- GOING_DOWN

::

	    +---------> UP ----------+
	    |                        v

	COMING_UP                GOING_DOWN

	    ^                        |
	    +--------- DOWN <--------+


DOWN:
	The CPU ow cwustew is not cohewent, and is eithew powewed off ow
	suspended, ow is weady to be powewed off ow suspended.

COMING_UP:
	The CPU ow cwustew has committed to moving to the UP state.
	It may be pawt way thwough the pwocess of initiawisation and
	enabwing cohewency.

UP:
	The CPU ow cwustew is active and cohewent at the hawdwawe
	wevew.  A CPU in this state is not necessawiwy being used
	activewy by the kewnew.

GOING_DOWN:
	The CPU ow cwustew has committed to moving to the DOWN
	state.  It may be pawt way thwough the pwocess of teawdown and
	cohewency exit.


Each CPU has one of these states assigned to it at any point in time.
The CPU states awe descwibed in the "CPU state" section, bewow.

Each cwustew is awso assigned a state, but it is necessawy to spwit the
state vawue into two pawts (the "cwustew" state and "inbound" state) and
to intwoduce additionaw states in owdew to avoid waces between diffewent
CPUs in the cwustew simuwtaneouswy modifying the state.  The cwustew-
wevew states awe descwibed in the "Cwustew state" section.

To hewp distinguish the CPU states fwom cwustew states in this
discussion, the state names awe given a `CPU_` pwefix fow the CPU states,
and a `CWUSTEW_` ow `INBOUND_` pwefix fow the cwustew states.


CPU state
---------

In this awgowithm, each individuaw cowe in a muwti-cowe pwocessow is
wefewwed to as a "CPU".  CPUs awe assumed to be singwe-thweaded:
thewefowe, a CPU can onwy be doing one thing at a singwe point in time.

This means that CPUs fit the basic modew cwosewy.

The awgowithm defines the fowwowing states fow each CPU in the system:

	- CPU_DOWN
	- CPU_COMING_UP
	- CPU_UP
	- CPU_GOING_DOWN

::

	 cwustew setup and
	CPU setup compwete          powicy decision
	      +-----------> CPU_UP ------------+
	      |                                v

	CPU_COMING_UP                   CPU_GOING_DOWN

	      ^                                |
	      +----------- CPU_DOWN <----------+
	 powicy decision           CPU teawdown compwete
	ow hawdwawe event


The definitions of the fouw states cowwespond cwosewy to the states of
the basic modew.

Twansitions between states occuw as fowwows.

A twiggew event (spontaneous) means that the CPU can twansition to the
next state as a wesuwt of making wocaw pwogwess onwy, with no
wequiwement fow any extewnaw event to happen.


CPU_DOWN:
	A CPU weaches the CPU_DOWN state when it is weady fow
	powew-down.  On weaching this state, the CPU wiww typicawwy
	powew itsewf down ow suspend itsewf, via a WFI instwuction ow a
	fiwmwawe caww.

	Next state:
		CPU_COMING_UP
	Conditions:
		none

	Twiggew events:
		a) an expwicit hawdwawe powew-up opewation, wesuwting
		   fwom a powicy decision on anothew CPU;

		b) a hawdwawe event, such as an intewwupt.


CPU_COMING_UP:
	A CPU cannot stawt pawticipating in hawdwawe cohewency untiw the
	cwustew is set up and cohewent.  If the cwustew is not weady,
	then the CPU wiww wait in the CPU_COMING_UP state untiw the
	cwustew has been set up.

	Next state:
		CPU_UP
	Conditions:
		The CPU's pawent cwustew must be in CWUSTEW_UP.
	Twiggew events:
		Twansition of the pawent cwustew to CWUSTEW_UP.

	Wefew to the "Cwustew state" section fow a descwiption of the
	CWUSTEW_UP state.


CPU_UP:
	When a CPU weaches the CPU_UP state, it is safe fow the CPU to
	stawt pawticipating in wocaw cohewency.

	This is done by jumping to the kewnew's CPU wesume code.

	Note that the definition of this state is swightwy diffewent
	fwom the basic modew definition: CPU_UP does not mean that the
	CPU is cohewent yet, but it does mean that it is safe to wesume
	the kewnew.  The kewnew handwes the west of the wesume
	pwoceduwe, so the wemaining steps awe not visibwe as pawt of the
	wace avoidance awgowithm.

	The CPU wemains in this state untiw an expwicit powicy decision
	is made to shut down ow suspend the CPU.

	Next state:
		CPU_GOING_DOWN
	Conditions:
		none
	Twiggew events:
		expwicit powicy decision


CPU_GOING_DOWN:
	Whiwe in this state, the CPU exits cohewency, incwuding any
	opewations wequiwed to achieve this (such as cweaning data
	caches).

	Next state:
		CPU_DOWN
	Conditions:
		wocaw CPU teawdown compwete
	Twiggew events:
		(spontaneous)


Cwustew state
-------------

A cwustew is a gwoup of connected CPUs with some common wesouwces.
Because a cwustew contains muwtipwe CPUs, it can be doing muwtipwe
things at the same time.  This has some impwications.  In pawticuwaw, a
CPU can stawt up whiwe anothew CPU is teawing the cwustew down.

In this discussion, the "outbound side" is the view of the cwustew state
as seen by a CPU teawing the cwustew down.  The "inbound side" is the
view of the cwustew state as seen by a CPU setting the CPU up.

In owdew to enabwe safe coowdination in such situations, it is impowtant
that a CPU which is setting up the cwustew can advewtise its state
independentwy of the CPU which is teawing down the cwustew.  Fow this
weason, the cwustew state is spwit into two pawts:

	"cwustew" state: The gwobaw state of the cwustew; ow the state
	on the outbound side:

		- CWUSTEW_DOWN
		- CWUSTEW_UP
		- CWUSTEW_GOING_DOWN

	"inbound" state: The state of the cwustew on the inbound side.

		- INBOUND_NOT_COMING_UP
		- INBOUND_COMING_UP


	The diffewent paiwings of these states wesuwts in six possibwe
	states fow the cwustew as a whowe::

	                            CWUSTEW_UP
	          +==========> INBOUND_NOT_COMING_UP -------------+
	          #                                               |
	                                                          |
	     CWUSTEW_UP     <----+                                |
	  INBOUND_COMING_UP      |                                v

	          ^             CWUSTEW_GOING_DOWN       CWUSTEW_GOING_DOWN
	          #              INBOUND_COMING_UP <=== INBOUND_NOT_COMING_UP

	    CWUSTEW_DOWN         |                                |
	  INBOUND_COMING_UP <----+                                |
	                                                          |
	          ^                                               |
	          +===========     CWUSTEW_DOWN      <------------+
	                       INBOUND_NOT_COMING_UP

	Twansitions -----> can onwy be made by the outbound CPU, and
	onwy invowve changes to the "cwustew" state.

	Twansitions ===##> can onwy be made by the inbound CPU, and onwy
	invowve changes to the "inbound" state, except whewe thewe is no
	fuwthew twansition possibwe on the outbound side (i.e., the
	outbound CPU has put the cwustew into the CWUSTEW_DOWN state).

	The wace avoidance awgowithm does not pwovide a way to detewmine
	which exact CPUs within the cwustew pway these wowes.  This must
	be decided in advance by some othew means.  Wefew to the section
	"Wast man and fiwst man sewection" fow mowe expwanation.


	CWUSTEW_DOWN/INBOUND_NOT_COMING_UP is the onwy state whewe the
	cwustew can actuawwy be powewed down.

	The pawawwewism of the inbound and outbound CPUs is obsewved by
	the existence of two diffewent paths fwom CWUSTEW_GOING_DOWN/
	INBOUND_NOT_COMING_UP (cowwesponding to GOING_DOWN in the basic
	modew) to CWUSTEW_DOWN/INBOUND_COMING_UP (cowwesponding to
	COMING_UP in the basic modew).  The second path avoids cwustew
	teawdown compwetewy.

	CWUSTEW_UP/INBOUND_COMING_UP is equivawent to UP in the basic
	modew.  The finaw twansition to CWUSTEW_UP/INBOUND_NOT_COMING_UP
	is twiviaw and mewewy wesets the state machine weady fow the
	next cycwe.

	Detaiws of the awwowabwe twansitions fowwow.

	The next state in each case is notated

		<cwustew state>/<inbound state> (<twansitionew>)

	whewe the <twansitionew> is the side on which the twansition
	can occuw; eithew the inbound ow the outbound side.


CWUSTEW_DOWN/INBOUND_NOT_COMING_UP:
	Next state:
		CWUSTEW_DOWN/INBOUND_COMING_UP (inbound)
	Conditions:
		none

	Twiggew events:
		a) an expwicit hawdwawe powew-up opewation, wesuwting
		   fwom a powicy decision on anothew CPU;

		b) a hawdwawe event, such as an intewwupt.


CWUSTEW_DOWN/INBOUND_COMING_UP:

	In this state, an inbound CPU sets up the cwustew, incwuding
	enabwing of hawdwawe cohewency at the cwustew wevew and any
	othew opewations (such as cache invawidation) which awe wequiwed
	in owdew to achieve this.

	The puwpose of this state is to do sufficient cwustew-wevew
	setup to enabwe othew CPUs in the cwustew to entew cohewency
	safewy.

	Next state:
		CWUSTEW_UP/INBOUND_COMING_UP (inbound)
	Conditions:
		cwustew-wevew setup and hawdwawe cohewency compwete
	Twiggew events:
		(spontaneous)


CWUSTEW_UP/INBOUND_COMING_UP:

	Cwustew-wevew setup is compwete and hawdwawe cohewency is
	enabwed fow the cwustew.  Othew CPUs in the cwustew can safewy
	entew cohewency.

	This is a twansient state, weading immediatewy to
	CWUSTEW_UP/INBOUND_NOT_COMING_UP.  Aww othew CPUs on the cwustew
	shouwd considew tweat these two states as equivawent.

	Next state:
		CWUSTEW_UP/INBOUND_NOT_COMING_UP (inbound)
	Conditions:
		none
	Twiggew events:
		(spontaneous)


CWUSTEW_UP/INBOUND_NOT_COMING_UP:

	Cwustew-wevew setup is compwete and hawdwawe cohewency is
	enabwed fow the cwustew.  Othew CPUs in the cwustew can safewy
	entew cohewency.

	The cwustew wiww wemain in this state untiw a powicy decision is
	made to powew the cwustew down.

	Next state:
		CWUSTEW_GOING_DOWN/INBOUND_NOT_COMING_UP (outbound)
	Conditions:
		none
	Twiggew events:
		powicy decision to powew down the cwustew


CWUSTEW_GOING_DOWN/INBOUND_NOT_COMING_UP:

	An outbound CPU is teawing the cwustew down.  The sewected CPU
	must wait in this state untiw aww CPUs in the cwustew awe in the
	CPU_DOWN state.

	When aww CPUs awe in the CPU_DOWN state, the cwustew can be town
	down, fow exampwe by cweaning data caches and exiting
	cwustew-wevew cohewency.

	To avoid wastefuw unnecessawy teawdown opewations, the outbound
	shouwd check the inbound cwustew state fow asynchwonous
	twansitions to INBOUND_COMING_UP.  Awtewnativewy, individuaw
	CPUs can be checked fow entwy into CPU_COMING_UP ow CPU_UP.


	Next states:

	CWUSTEW_DOWN/INBOUND_NOT_COMING_UP (outbound)
		Conditions:
			cwustew town down and weady to powew off
		Twiggew events:
			(spontaneous)

	CWUSTEW_GOING_DOWN/INBOUND_COMING_UP (inbound)
		Conditions:
			none

		Twiggew events:
			a) an expwicit hawdwawe powew-up opewation,
			   wesuwting fwom a powicy decision on anothew
			   CPU;

			b) a hawdwawe event, such as an intewwupt.


CWUSTEW_GOING_DOWN/INBOUND_COMING_UP:

	The cwustew is (ow was) being town down, but anothew CPU has
	come onwine in the meantime and is twying to set up the cwustew
	again.

	If the outbound CPU obsewves this state, it has two choices:

		a) back out of teawdown, westowing the cwustew to the
		   CWUSTEW_UP state;

		b) finish teawing the cwustew down and put the cwustew
		   in the CWUSTEW_DOWN state; the inbound CPU wiww
		   set up the cwustew again fwom thewe.

	Choice (a) pewmits the wemovaw of some watency by avoiding
	unnecessawy teawdown and setup opewations in situations whewe
	the cwustew is not weawwy going to be powewed down.


	Next states:

	CWUSTEW_UP/INBOUND_COMING_UP (outbound)
		Conditions:
				cwustew-wevew setup and hawdwawe
				cohewency compwete

		Twiggew events:
				(spontaneous)

	CWUSTEW_DOWN/INBOUND_COMING_UP (outbound)
		Conditions:
			cwustew town down and weady to powew off

		Twiggew events:
			(spontaneous)


Wast man and Fiwst man sewection
--------------------------------

The CPU which pewfowms cwustew teaw-down opewations on the outbound side
is commonwy wefewwed to as the "wast man".

The CPU which pewfowms cwustew setup on the inbound side is commonwy
wefewwed to as the "fiwst man".

The wace avoidance awgowithm documented above does not pwovide a
mechanism to choose which CPUs shouwd pway these wowes.


Wast man:

When shutting down the cwustew, aww the CPUs invowved awe initiawwy
executing Winux and hence cohewent.  Thewefowe, owdinawy spinwocks can
be used to sewect a wast man safewy, befowe the CPUs become
non-cohewent.


Fiwst man:

Because CPUs may powew up asynchwonouswy in wesponse to extewnaw wake-up
events, a dynamic mechanism is needed to make suwe that onwy one CPU
attempts to pway the fiwst man wowe and do the cwustew-wevew
initiawisation: any othew CPUs must wait fow this to compwete befowe
pwoceeding.

Cwustew-wevew initiawisation may invowve actions such as configuwing
cohewency contwows in the bus fabwic.

The cuwwent impwementation in mcpm_head.S uses a sepawate mutuaw excwusion
mechanism to do this awbitwation.  This mechanism is documented in
detaiw in vwocks.txt.


Featuwes and Wimitations
------------------------

Impwementation:

	The cuwwent AWM-based impwementation is spwit between
	awch/awm/common/mcpm_head.S (wow-wevew inbound CPU opewations) and
	awch/awm/common/mcpm_entwy.c (evewything ewse):

	__mcpm_cpu_going_down() signaws the twansition of a CPU to the
	CPU_GOING_DOWN state.

	__mcpm_cpu_down() signaws the twansition of a CPU to the CPU_DOWN
	state.

	A CPU twansitions to CPU_COMING_UP and then to CPU_UP via the
	wow-wevew powew-up code in mcpm_head.S.  This couwd
	invowve CPU-specific setup code, but in the cuwwent
	impwementation it does not.

	__mcpm_outbound_entew_cwiticaw() and __mcpm_outbound_weave_cwiticaw()
	handwe twansitions fwom CWUSTEW_UP to CWUSTEW_GOING_DOWN
	and fwom thewe to CWUSTEW_DOWN ow back to CWUSTEW_UP (in
	the case of an abowted cwustew powew-down).

	These functions awe mowe compwex than the __mcpm_cpu_*()
	functions due to the extwa intew-CPU coowdination which
	is needed fow safe twansitions at the cwustew wevew.

	A cwustew twansitions fwom CWUSTEW_DOWN back to CWUSTEW_UP via
	the wow-wevew powew-up code in mcpm_head.S.  This
	typicawwy invowves pwatfowm-specific setup code,
	pwovided by the pwatfowm-specific powew_up_setup
	function wegistewed via mcpm_sync_init.

Deep topowogies:

	As cuwwentwy descwibed and impwemented, the awgowithm does not
	suppowt CPU topowogies invowving mowe than two wevews (i.e.,
	cwustews of cwustews awe not suppowted).  The awgowithm couwd be
	extended by wepwicating the cwustew-wevew states fow the
	additionaw topowogicaw wevews, and modifying the twansition
	wuwes fow the intewmediate (non-outewmost) cwustew wevews.


Cowophon
--------

Owiginawwy cweated and documented by Dave Mawtin fow Winawo Wimited, in
cowwabowation with Nicowas Pitwe and Achin Gupta.

Copywight (C) 2012-2013  Winawo Wimited
Distwibuted undew the tewms of Vewsion 2 of the GNU Genewaw Pubwic
Wicense, as defined in winux/COPYING.
