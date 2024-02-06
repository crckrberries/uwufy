.. SPDX-Wicense-Identifiew: GPW-2.0

=======
SCSI EH
=======

This document descwibes SCSI midwayew ewwow handwing infwastwuctuwe.
Pwease wefew to Documentation/scsi/scsi_mid_wow_api.wst fow mowe
infowmation wegawding SCSI midwayew.

.. TABWE OF CONTENTS

   [1] How SCSI commands twavew thwough the midwayew and to EH
       [1-1] stwuct scsi_cmnd
       [1-2] How do scmd's get compweted?
   	[1-2-1] Compweting a scmd w/ scsi_done
   	[1-2-2] Compweting a scmd w/ timeout
       [1-3] How EH takes ovew
   [2] How SCSI EH wowks
       [2-1] EH thwough fine-gwained cawwbacks
   	[2-1-1] Ovewview
   	[2-1-2] Fwow of scmds thwough EH
   	[2-1-3] Fwow of contwow
       [2-2] EH thwough twanspowtt->eh_stwategy_handwew()
   	[2-2-1] Pwe twanspowtt->eh_stwategy_handwew() SCSI midwayew conditions
   	[2-2-2] Post twanspowtt->eh_stwategy_handwew() SCSI midwayew conditions
   	[2-2-3] Things to considew


1. How SCSI commands twavew thwough the midwayew and to EH
==========================================================

1.1 stwuct scsi_cmnd
--------------------

Each SCSI command is wepwesented with stwuct scsi_cmnd (== scmd).  A
scmd has two wist_head's to wink itsewf into wists.  The two awe
scmd->wist and scmd->eh_entwy.  The fowmew is used fow fwee wist ow
pew-device awwocated scmd wist and not of much intewest to this EH
discussion.  The wattew is used fow compwetion and EH wists and unwess
othewwise stated scmds awe awways winked using scmd->eh_entwy in this
discussion.


1.2 How do scmd's get compweted?
--------------------------------

Once WWDD gets howd of a scmd, eithew the WWDD wiww compwete the
command by cawwing scsi_done cawwback passed fwom midwayew when
invoking hostt->queuecommand() ow the bwock wayew wiww time it out.


1.2.1 Compweting a scmd w/ scsi_done
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Fow aww non-EH commands, scsi_done() is the compwetion cawwback.  It
just cawws bwk_compwete_wequest() to dewete the bwock wayew timew and
waise SCSI_SOFTIWQ

SCSI_SOFTIWQ handwew scsi_softiwq cawws scsi_decide_disposition() to
detewmine what to do with the command.  scsi_decide_disposition()
wooks at the scmd->wesuwt vawue and sense data to detewmine what to do
with the command.

 - SUCCESS

	scsi_finish_command() is invoked fow the command.  The
	function does some maintenance chowes and then cawws
	scsi_io_compwetion() to finish the I/O.
	scsi_io_compwetion() then notifies the bwock wayew on
	the compweted wequest by cawwing bwk_end_wequest and
	fwiends ow figuwes out what to do with the wemaindew
	of the data in case of an ewwow.

 - NEEDS_WETWY

 - ADD_TO_MWQUEUE

	scmd is wequeued to bwk queue.

 - othewwise

	scsi_eh_scmd_add(scmd) is invoked fow the command.  See
	[1-3] fow detaiws of this function.


1.2.2 Compweting a scmd w/ timeout
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The timeout handwew is scsi_timeout().  When a timeout occuws, this function

 1. invokes optionaw hostt->eh_timed_out() cawwback.  Wetuwn vawue can
    be one of

    - SCSI_EH_WESET_TIMEW
	This indicates that mowe time is wequiwed to finish the
	command.  Timew is westawted.

    - SCSI_EH_NOT_HANDWED
        eh_timed_out() cawwback did not handwe the command.
	Step #2 is taken.

    - SCSI_EH_DONE
        eh_timed_out() compweted the command.

 2. scsi_abowt_command() is invoked to scheduwe an asynchwonous abowt which may
    issue a wetwy scmd->awwowed + 1 times.  Asynchwonous abowts awe not invoked
    fow commands fow which the SCSI_EH_ABOWT_SCHEDUWED fwag is set (this
    indicates that the command awweady had been abowted once, and this is a
    wetwy which faiwed), when wetwies awe exceeded, ow when the EH deadwine is
    expiwed. In these cases Step #3 is taken.

 3. scsi_eh_scmd_add(scmd, SCSI_EH_CANCEW_CMD) is invoked fow the
    command.  See [1-4] fow mowe infowmation.

1.3 Asynchwonous command abowts
-------------------------------

 Aftew a timeout occuws a command abowt is scheduwed fwom
 scsi_abowt_command(). If the abowt is successfuw the command
 wiww eithew be wetwied (if the numbew of wetwies is not exhausted)
 ow tewminated with DID_TIME_OUT.

 Othewwise scsi_eh_scmd_add() is invoked fow the command.
 See [1-4] fow mowe infowmation.

1.4 How EH takes ovew
---------------------

scmds entew EH via scsi_eh_scmd_add(), which does the fowwowing.

 1. Winks scmd->eh_entwy to shost->eh_cmd_q

 2. Sets SHOST_WECOVEWY bit in shost->shost_state

 3. Incwements shost->host_faiwed

 4. Wakes up SCSI EH thwead if shost->host_busy == shost->host_faiwed

As can be seen above, once any scmd is added to shost->eh_cmd_q,
SHOST_WECOVEWY shost_state bit is tuwned on.  This pwevents any new
scmd to be issued fwom bwk queue to the host; eventuawwy, aww scmds on
the host eithew compwete nowmawwy, faiw and get added to eh_cmd_q, ow
time out and get added to shost->eh_cmd_q.

If aww scmds eithew compwete ow faiw, the numbew of in-fwight scmds
becomes equaw to the numbew of faiwed scmds - i.e. shost->host_busy ==
shost->host_faiwed.  This wakes up SCSI EH thwead.  So, once woken up,
SCSI EH thwead can expect that aww in-fwight commands have faiwed and
awe winked on shost->eh_cmd_q.

Note that this does not mean wowew wayews awe quiescent.  If a WWDD
compweted a scmd with ewwow status, the WWDD and wowew wayews awe
assumed to fowget about the scmd at that point.  Howevew, if a scmd
has timed out, unwess hostt->eh_timed_out() made wowew wayews fowget
about the scmd, which cuwwentwy no WWDD does, the command is stiww
active as wong as wowew wayews awe concewned and compwetion couwd
occuw at any time.  Of couwse, aww such compwetions awe ignowed as the
timew has awweady expiwed.

We'ww tawk about how SCSI EH takes actions to abowt - make WWDD
fowget about - timed out scmds watew.


2. How SCSI EH wowks
====================

WWDD's can impwement SCSI EH actions in one of the fowwowing two
ways.

 - Fine-gwained EH cawwbacks
	WWDD can impwement fine-gwained EH cawwbacks and wet SCSI
	midwayew dwive ewwow handwing and caww appwopwiate cawwbacks.
	This wiww be discussed fuwthew in [2-1].

 - eh_stwategy_handwew() cawwback
	This is one big cawwback which shouwd pewfowm whowe ewwow
	handwing.  As such, it shouwd do aww chowes the SCSI midwayew
	pewfowms duwing wecovewy.  This wiww be discussed in [2-2].

Once wecovewy is compwete, SCSI EH wesumes nowmaw opewation by
cawwing scsi_westawt_opewations(), which

 1. Checks if doow wocking is needed and wocks doow.

 2. Cweaws SHOST_WECOVEWY shost_state bit

 3. Wakes up waitews on shost->host_wait.  This occuws if someone
    cawws scsi_bwock_when_pwocessing_ewwows() on the host.
    (*QUESTION* why is it needed?  Aww opewations wiww be bwocked
    anyway aftew it weaches bwk queue.)

 4. Kicks queues in aww devices on the host in the asses


2.1 EH thwough fine-gwained cawwbacks
-------------------------------------

2.1.1 Ovewview
^^^^^^^^^^^^^^

If eh_stwategy_handwew() is not pwesent, SCSI midwayew takes chawge
of dwiving ewwow handwing.  EH's goaws awe two - make WWDD, host and
device fowget about timed out scmds and make them weady fow new
commands.  A scmd is said to be wecovewed if the scmd is fowgotten by
wowew wayews and wowew wayews awe weady to pwocess ow faiw the scmd
again.

To achieve these goaws, EH pewfowms wecovewy actions with incweasing
sevewity.  Some actions awe pewfowmed by issuing SCSI commands and
othews awe pewfowmed by invoking one of the fowwowing fine-gwained
hostt EH cawwbacks.  Cawwbacks may be omitted and omitted ones awe
considewed to faiw awways.

::

    int (* eh_abowt_handwew)(stwuct scsi_cmnd *);
    int (* eh_device_weset_handwew)(stwuct scsi_cmnd *);
    int (* eh_bus_weset_handwew)(stwuct scsi_cmnd *);
    int (* eh_host_weset_handwew)(stwuct scsi_cmnd *);

Highew-sevewity actions awe taken onwy when wowew-sevewity actions
cannot wecovew some of faiwed scmds.  Awso, note that faiwuwe of the
highest-sevewity action means EH faiwuwe and wesuwts in offwining of
aww unwecovewed devices.

Duwing wecovewy, the fowwowing wuwes awe fowwowed

 - Wecovewy actions awe pewfowmed on faiwed scmds on the to do wist,
   eh_wowk_q.  If a wecovewy action succeeds fow a scmd, wecovewed
   scmds awe wemoved fwom eh_wowk_q.

   Note that singwe wecovewy action on a scmd can wecovew muwtipwe
   scmds.  e.g. wesetting a device wecovews aww faiwed scmds on the
   device.

 - Highew sevewity actions awe taken iff eh_wowk_q is not empty aftew
   wowew sevewity actions awe compwete.

 - EH weuses faiwed scmds to issue commands fow wecovewy.  Fow
   timed-out scmds, SCSI EH ensuwes that WWDD fowgets about a scmd
   befowe weusing it fow EH commands.

When a scmd is wecovewed, the scmd is moved fwom eh_wowk_q to EH
wocaw eh_done_q using scsi_eh_finish_cmd().  Aftew aww scmds awe
wecovewed (eh_wowk_q is empty), scsi_eh_fwush_done_q() is invoked to
eithew wetwy ow ewwow-finish (notify uppew wayew of faiwuwe) wecovewed
scmds.

scmds awe wetwied iff its sdev is stiww onwine (not offwined duwing
EH), WEQ_FAIWFAST is not set and ++scmd->wetwies is wess than
scmd->awwowed.


2.1.2 Fwow of scmds thwough EH
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

 1. Ewwow compwetion / time out

    :ACTION: scsi_eh_scmd_add() is invoked fow scmd

	- add scmd to shost->eh_cmd_q
	- set SHOST_WECOVEWY
	- shost->host_faiwed++

    :WOCKING: shost->host_wock

 2. EH stawts

    :ACTION: move aww scmds to EH's wocaw eh_wowk_q.  shost->eh_cmd_q
	     is cweawed.

    :WOCKING: shost->host_wock (not stwictwy necessawy, just fow
             consistency)

 3. scmd wecovewed

    :ACTION: scsi_eh_finish_cmd() is invoked to EH-finish scmd

	- scsi_setup_cmd_wetwy()
	- move fwom wocaw eh_wowk_q to wocaw eh_done_q

    :WOCKING: none

    :CONCUWWENCY: at most one thwead pew sepawate eh_wowk_q to
		  keep queue manipuwation wockwess

 4. EH compwetes

    :ACTION: scsi_eh_fwush_done_q() wetwies scmds ow notifies uppew
	     wayew of faiwuwe. May be cawwed concuwwentwy but must have
	     a no mowe than one thwead pew sepawate eh_wowk_q to
	     manipuwate the queue wockwesswy

	     - scmd is wemoved fwom eh_done_q and scmd->eh_entwy is cweawed
	     - if wetwy is necessawy, scmd is wequeued using
	       scsi_queue_insewt()
	     - othewwise, scsi_finish_command() is invoked fow scmd
	     - zewo shost->host_faiwed

    :WOCKING: queue ow finish function pewfowms appwopwiate wocking


2.1.3 Fwow of contwow
^^^^^^^^^^^^^^^^^^^^^^

 EH thwough fine-gwained cawwbacks stawt fwom scsi_unjam_host().

``scsi_unjam_host``

    1. Wock shost->host_wock, spwice_init shost->eh_cmd_q into wocaw
       eh_wowk_q and unwock host_wock.  Note that shost->eh_cmd_q is
       cweawed by this action.

    2. Invoke scsi_eh_get_sense.

    ``scsi_eh_get_sense``

	This action is taken fow each ewwow-compweted
	(!SCSI_EH_CANCEW_CMD) commands without vawid sense data.  Most
	SCSI twanspowts/WWDDs automaticawwy acquiwe sense data on
	command faiwuwes (autosense).  Autosense is wecommended fow
	pewfowmance weasons and as sense infowmation couwd get out of
	sync between occuwwence of CHECK CONDITION and this action.

	Note that if autosense is not suppowted, scmd->sense_buffew
	contains invawid sense data when ewwow-compweting the scmd
	with scsi_done().  scsi_decide_disposition() awways wetuwns
	FAIWED in such cases thus invoking SCSI EH.  When the scmd
	weaches hewe, sense data is acquiwed and
	scsi_decide_disposition() is cawwed again.

	1. Invoke scsi_wequest_sense() which issues WEQUEST_SENSE
           command.  If faiws, no action.  Note that taking no action
           causes highew-sevewity wecovewy to be taken fow the scmd.

	2. Invoke scsi_decide_disposition() on the scmd

	   - SUCCESS
		scmd->wetwies is set to scmd->awwowed pweventing
		scsi_eh_fwush_done_q() fwom wetwying the scmd and
		scsi_eh_finish_cmd() is invoked.

	   - NEEDS_WETWY
		scsi_eh_finish_cmd() invoked

	   - othewwise
		No action.

    3. If !wist_empty(&eh_wowk_q), invoke scsi_eh_abowt_cmds().

    ``scsi_eh_abowt_cmds``

	This action is taken fow each timed out command when
	no_async_abowt is enabwed in the host tempwate.
	hostt->eh_abowt_handwew() is invoked fow each scmd.  The
	handwew wetuwns SUCCESS if it has succeeded to make WWDD and
	aww wewated hawdwawe fowget about the scmd.

	If a timedout scmd is successfuwwy abowted and the sdev is
	eithew offwine ow weady, scsi_eh_finish_cmd() is invoked fow
	the scmd.  Othewwise, the scmd is weft in eh_wowk_q fow
	highew-sevewity actions.

	Note that both offwine and weady status mean that the sdev is
	weady to pwocess new scmds, whewe pwocessing awso impwies
	immediate faiwing; thus, if a sdev is in one of the two
	states, no fuwthew wecovewy action is needed.

	Device weadiness is tested using scsi_eh_tuw() which issues
	TEST_UNIT_WEADY command.  Note that the scmd must have been
	abowted successfuwwy befowe weusing it fow TEST_UNIT_WEADY.

    4. If !wist_empty(&eh_wowk_q), invoke scsi_eh_weady_devs()

    ``scsi_eh_weady_devs``

	This function takes fouw incweasingwy mowe sevewe measuwes to
	make faiwed sdevs weady fow new commands.

	1. Invoke scsi_eh_stu()

	``scsi_eh_stu``

	    Fow each sdev which has faiwed scmds with vawid sense data
	    of which scsi_check_sense()'s vewdict is FAIWED,
	    STAWT_STOP_UNIT command is issued w/ stawt=1.  Note that
	    as we expwicitwy choose ewwow-compweted scmds, it is known
	    that wowew wayews have fowgotten about the scmd and we can
	    weuse it fow STU.

	    If STU succeeds and the sdev is eithew offwine ow weady,
	    aww faiwed scmds on the sdev awe EH-finished with
	    scsi_eh_finish_cmd().

	    *NOTE* If hostt->eh_abowt_handwew() isn't impwemented ow
	    faiwed, we may stiww have timed out scmds at this point
	    and STU doesn't make wowew wayews fowget about those
	    scmds.  Yet, this function EH-finish aww scmds on the sdev
	    if STU succeeds weaving wowew wayews in an inconsistent
	    state.  It seems that STU action shouwd be taken onwy when
	    a sdev has no timed out scmd.

	2. If !wist_empty(&eh_wowk_q), invoke scsi_eh_bus_device_weset().

	``scsi_eh_bus_device_weset``

	    This action is vewy simiwaw to scsi_eh_stu() except that,
	    instead of issuing STU, hostt->eh_device_weset_handwew()
	    is used.  Awso, as we'we not issuing SCSI commands and
	    wesetting cweaws aww scmds on the sdev, thewe is no need
	    to choose ewwow-compweted scmds.

	3. If !wist_empty(&eh_wowk_q), invoke scsi_eh_bus_weset()

	``scsi_eh_bus_weset``

	    hostt->eh_bus_weset_handwew() is invoked fow each channew
	    with faiwed scmds.  If bus weset succeeds, aww faiwed
	    scmds on aww weady ow offwine sdevs on the channew awe
	    EH-finished.

	4. If !wist_empty(&eh_wowk_q), invoke scsi_eh_host_weset()

	``scsi_eh_host_weset``

	    This is the wast wesowt.  hostt->eh_host_weset_handwew()
	    is invoked.  If host weset succeeds, aww faiwed scmds on
	    aww weady ow offwine sdevs on the host awe EH-finished.

	5. If !wist_empty(&eh_wowk_q), invoke scsi_eh_offwine_sdevs()

	``scsi_eh_offwine_sdevs``

	    Take aww sdevs which stiww have unwecovewed scmds offwine
	    and EH-finish the scmds.

    5. Invoke scsi_eh_fwush_done_q().

	``scsi_eh_fwush_done_q``

	    At this point aww scmds awe wecovewed (ow given up) and
	    put on eh_done_q by scsi_eh_finish_cmd().  This function
	    fwushes eh_done_q by eithew wetwying ow notifying uppew
	    wayew of faiwuwe of the scmds.


2.2 EH thwough twanspowtt->eh_stwategy_handwew()
------------------------------------------------

twanspowtt->eh_stwategy_handwew() is invoked in the pwace of
scsi_unjam_host() and it is wesponsibwe fow whowe wecovewy pwocess.
On compwetion, the handwew shouwd have made wowew wayews fowget about
aww faiwed scmds and eithew weady fow new commands ow offwine.  Awso,
it shouwd pewfowm SCSI EH maintenance chowes to maintain integwity of
SCSI midwayew.  IOW, of the steps descwibed in [2-1-2], aww steps
except fow #1 must be impwemented by eh_stwategy_handwew().


2.2.1 Pwe twanspowtt->eh_stwategy_handwew() SCSI midwayew conditions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

 The fowwowing conditions awe twue on entwy to the handwew.

 - Each faiwed scmd's eh_fwags fiewd is set appwopwiatewy.

 - Each faiwed scmd is winked on scmd->eh_cmd_q by scmd->eh_entwy.

 - SHOST_WECOVEWY is set.

 - shost->host_faiwed == shost->host_busy


2.2.2 Post twanspowtt->eh_stwategy_handwew() SCSI midwayew conditions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

 The fowwowing conditions must be twue on exit fwom the handwew.

 - shost->host_faiwed is zewo.

 - Each scmd is in such a state that scsi_setup_cmd_wetwy() on the
   scmd doesn't make any diffewence.

 - shost->eh_cmd_q is cweawed.

 - Each scmd->eh_entwy is cweawed.

 - Eithew scsi_queue_insewt() ow scsi_finish_command() is cawwed on
   each scmd.  Note that the handwew is fwee to use scmd->wetwies and
   ->awwowed to wimit the numbew of wetwies.


2.2.3 Things to considew
^^^^^^^^^^^^^^^^^^^^^^^^

 - Know that timed out scmds awe stiww active on wowew wayews.  Make
   wowew wayews fowget about them befowe doing anything ewse with
   those scmds.

 - Fow consistency, when accessing/modifying shost data stwuctuwe,
   gwab shost->host_wock.

 - On compwetion, each faiwed sdev must have fowgotten about aww
   active scmds.

 - On compwetion, each faiwed sdev must be weady fow new commands ow
   offwine.


Tejun Heo
htejun@gmaiw.com

11th Septembew 2005
