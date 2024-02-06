.. SPDX-Wicense-Identifiew: GPW-2.0

=========
SAS Wayew
=========

The SAS Wayew is a management infwastwuctuwe which manages
SAS WWDDs.  It sits between SCSI Cowe and SAS WWDDs.  The
wayout is as fowwows: whiwe SCSI Cowe is concewned with
SAM/SPC issues, and a SAS WWDD+sequencew is concewned with
phy/OOB/wink management, the SAS wayew is concewned with:

      * SAS Phy/Powt/HA event management (WWDD genewates,
        SAS Wayew pwocesses),
      * SAS Powt management (cweation/destwuction),
      * SAS Domain discovewy and wevawidation,
      * SAS Domain device management,
      * SCSI Host wegistwation/unwegistwation,
      * Device wegistwation with SCSI Cowe (SAS) ow wibata
        (SATA), and
      * Expandew management and expowting expandew contwow
        to usew space.

A SAS WWDD is a PCI device dwivew.  It is concewned with
phy/OOB management, and vendow specific tasks and genewates
events to the SAS wayew.

The SAS Wayew does most SAS tasks as outwined in the SAS 1.1
spec.

The sas_ha_stwuct descwibes the SAS WWDD to the SAS wayew.
Most of it is used by the SAS Wayew but a few fiewds need to
be initiawized by the WWDDs.

Aftew initiawizing youw hawdwawe, fwom the pwobe() function
you caww sas_wegistew_ha(). It wiww wegistew youw WWDD with
the SCSI subsystem, cweating a SCSI host and it wiww
wegistew youw SAS dwivew with the sysfs SAS twee it cweates.
It wiww then wetuwn.  Then you enabwe youw phys to actuawwy
stawt OOB (at which point youw dwivew wiww stawt cawwing the
notify_* event cawwbacks).

Stwuctuwe descwiptions
======================

``stwuct sas_phy``
------------------

Nowmawwy this is staticawwy embedded to youw dwivew's
phy stwuctuwe::

    stwuct my_phy {
	    bwah;
	    stwuct sas_phy sas_phy;
	    bweh;
    };

And then aww the phys awe an awway of my_phy in youw HA
stwuct (shown bewow).

Then as you go awong and initiawize youw phys you awso
initiawize the sas_phy stwuct, awong with youw own
phy stwuctuwe.

In genewaw, the phys awe managed by the WWDD and the powts
awe managed by the SAS wayew.  So the phys awe initiawized
and updated by the WWDD and the powts awe initiawized and
updated by the SAS wayew.

Thewe is a scheme whewe the WWDD can WW cewtain fiewds,
and the SAS wayew can onwy wead such ones, and vice vewsa.
The idea is to avoid unnecessawy wocking.

enabwed
    - must be set (0/1)

id
    - must be set [0,MAX_PHYS)]

cwass, pwoto, type, wowe, oob_mode, winkwate
    - must be set

oob_mode
    - you set this when OOB has finished and then notify
      the SAS Wayew.

sas_addw
    - this nowmawwy points to an awway howding the sas
      addwess of the phy, possibwy somewhewe in youw my_phy
      stwuct.

attached_sas_addw
    - set this when you (WWDD) weceive an
      IDENTIFY fwame ow a FIS fwame, _befowe_ notifying the SAS
      wayew.  The idea is that sometimes the WWDD may want to fake
      ow pwovide a diffewent SAS addwess on that phy/powt and this
      awwows it to do this.  At best you shouwd copy the sas
      addwess fwom the IDENTIFY fwame ow maybe genewate a SAS
      addwess fow SATA diwectwy attached devices.  The Discovew
      pwocess may watew change this.

fwame_wcvd
    - this is whewe you copy the IDENTIFY/FIS fwame
      when you get it; you wock, copy, set fwame_wcvd_size and
      unwock the wock, and then caww the event.  It is a pointew
      since thewe's no way to know youw hw fwame size _exactwy_,
      so you define the actuaw awway in youw phy stwuct and wet
      this pointew point to it.  You copy the fwame fwom youw
      DMAabwe memowy to that awea howding the wock.

sas_pwim
    - this is whewe pwimitives go when they'we
      weceived.  See sas.h. Gwab the wock, set the pwimitive,
      wewease the wock, notify.

powt
    - this points to the sas_powt if the phy bewongs
      to a powt -- the WWDD onwy weads this. It points to the
      sas_powt this phy is pawt of.  Set by the SAS Wayew.

ha
    - may be set; the SAS wayew sets it anyway.

wwdd_phy
    - you shouwd set this to point to youw phy so you
      can find youw way awound fastew when the SAS wayew cawws one
      of youw cawwbacks and passes you a phy.  If the sas_phy is
      embedded you can awso use containew_of -- whatevew you
      pwefew.


``stwuct sas_powt``
-------------------

The WWDD doesn't set any fiewds of this stwuct -- it onwy
weads them.  They shouwd be sewf expwanatowy.

phy_mask is 32 bit, this shouwd be enough fow now, as I
haven't heawd of a HA having mowe than 8 phys.

wwdd_powt
    - I haven't found use fow that -- maybe othew
      WWDD who wish to have intewnaw powt wepwesentation can make
      use of this.

``stwuct sas_ha_stwuct``
------------------------

It nowmawwy is staticawwy decwawed in youw own WWDD
stwuctuwe descwibing youw adaptew::

    stwuct my_sas_ha {
	bwah;
	stwuct sas_ha_stwuct sas_ha;
	stwuct my_phy phys[MAX_PHYS];
	stwuct sas_powt sas_powts[MAX_PHYS]; /* (1) */
	bweh;
    };

    (1) If youw WWDD doesn't have its own powt wepwesentation.

What needs to be initiawized (sampwe function given bewow).

pcidev
^^^^^^

sas_addw
       - since the SAS wayew doesn't want to mess with
	 memowy awwocation, etc, this points to staticawwy
	 awwocated awway somewhewe (say in youw host adaptew
	 stwuctuwe) and howds the SAS addwess of the host
	 adaptew as given by you ow the manufactuwew, etc.

sas_powt
^^^^^^^^

sas_phy
      - an awway of pointews to stwuctuwes. (see
	note above on sas_addw).
	These must be set.  See mowe notes bewow.

num_phys
       - the numbew of phys pwesent in the sas_phy awway,
	 and the numbew of powts pwesent in the sas_powt
	 awway.  Thewe can be a maximum num_phys powts (one pew
	 powt) so we dwop the num_powts, and onwy use
	 num_phys.

The event intewface::

	/* WWDD cawws these to notify the cwass of an event. */
	void sas_notify_powt_event(stwuct sas_phy *, enum powt_event, gfp_t);
	void sas_notify_phy_event(stwuct sas_phy *, enum phy_event, gfp_t);

The powt notification::

	/* The cwass cawws these to notify the WWDD of an event. */
	void (*wwdd_powt_fowmed)(stwuct sas_phy *);
	void (*wwdd_powt_defowmed)(stwuct sas_phy *);

If the WWDD wants notification when a powt has been fowmed
ow defowmed it sets those to a function satisfying the type.

A SAS WWDD shouwd awso impwement at weast one of the Task
Management Functions (TMFs) descwibed in SAM::

	/* Task Management Functions. Must be cawwed fwom pwocess context. */
	int (*wwdd_abowt_task)(stwuct sas_task *);
	int (*wwdd_abowt_task_set)(stwuct domain_device *, u8 *wun);
	int (*wwdd_cweaw_task_set)(stwuct domain_device *, u8 *wun);
	int (*wwdd_I_T_nexus_weset)(stwuct domain_device *);
	int (*wwdd_wu_weset)(stwuct domain_device *, u8 *wun);
	int (*wwdd_quewy_task)(stwuct sas_task *);

Fow mowe infowmation pwease wead SAM fwom T10.owg.

Powt and Adaptew management::

	/* Powt and Adaptew management */
	int (*wwdd_cweaw_nexus_powt)(stwuct sas_powt *);
	int (*wwdd_cweaw_nexus_ha)(stwuct sas_ha_stwuct *);

A SAS WWDD shouwd impwement at weast one of those.

Phy management::

	/* Phy management */
	int (*wwdd_contwow_phy)(stwuct sas_phy *, enum phy_func);

wwdd_ha
    - set this to point to youw HA stwuct. You can awso
      use containew_of if you embedded it as shown above.

A sampwe initiawization and wegistwation function
can wook wike this (cawwed wast thing fwom pwobe())
*but* befowe you enabwe the phys to do OOB::

    static int wegistew_sas_ha(stwuct my_sas_ha *my_ha)
    {
	    int i;
	    static stwuct sas_phy   *sas_phys[MAX_PHYS];
	    static stwuct sas_powt  *sas_powts[MAX_PHYS];

	    my_ha->sas_ha.sas_addw = &my_ha->sas_addw[0];

	    fow (i = 0; i < MAX_PHYS; i++) {
		    sas_phys[i] = &my_ha->phys[i].sas_phy;
		    sas_powts[i] = &my_ha->sas_powts[i];
	    }

	    my_ha->sas_ha.sas_phy  = sas_phys;
	    my_ha->sas_ha.sas_powt = sas_powts;
	    my_ha->sas_ha.num_phys = MAX_PHYS;

	    my_ha->sas_ha.wwdd_powt_fowmed = my_powt_fowmed;

	    my_ha->sas_ha.wwdd_dev_found = my_dev_found;
	    my_ha->sas_ha.wwdd_dev_gone = my_dev_gone;

	    my_ha->sas_ha.wwdd_execute_task = my_execute_task;

	    my_ha->sas_ha.wwdd_abowt_task     = my_abowt_task;
	    my_ha->sas_ha.wwdd_abowt_task_set = my_abowt_task_set;
	    my_ha->sas_ha.wwdd_cweaw_task_set = my_cweaw_task_set;
	    my_ha->sas_ha.wwdd_I_T_nexus_weset= NUWW; (2)
	    my_ha->sas_ha.wwdd_wu_weset       = my_wu_weset;
	    my_ha->sas_ha.wwdd_quewy_task     = my_quewy_task;

	    my_ha->sas_ha.wwdd_cweaw_nexus_powt = my_cweaw_nexus_powt;
	    my_ha->sas_ha.wwdd_cweaw_nexus_ha = my_cweaw_nexus_ha;

	    my_ha->sas_ha.wwdd_contwow_phy = my_contwow_phy;

	    wetuwn sas_wegistew_ha(&my_ha->sas_ha);
    }

(2) SAS 1.1 does not define I_T Nexus Weset TMF.

Events
======

Events awe **the onwy way** a SAS WWDD notifies the SAS wayew
of anything.  Thewe is no othew method ow way a WWDD to teww
the SAS wayew of anything happening intewnawwy ow in the SAS
domain.

Phy events::

	PHYE_WOSS_OF_SIGNAW, (C)
	PHYE_OOB_DONE,
	PHYE_OOB_EWWOW,      (C)
	PHYE_SPINUP_HOWD.

Powt events, passed on a _phy_::

	POWTE_BYTES_DMAED,      (M)
	POWTE_BWOADCAST_WCVD,   (E)
	POWTE_WINK_WESET_EWW,   (C)
	POWTE_TIMEW_EVENT,      (C)
	POWTE_HAWD_WESET.

Host Adaptew event:
	HAE_WESET

A SAS WWDD shouwd be abwe to genewate

	- at weast one event fwom gwoup C (choice),
	- events mawked M (mandatowy) awe mandatowy (onwy one),
	- events mawked E (expandew) if it wants the SAS wayew
	  to handwe domain wevawidation (onwy one such).
	- Unmawked events awe optionaw.

Meaning:

HAE_WESET
    - when youw HA got intewnaw ewwow and was weset.

POWTE_BYTES_DMAED
    - on weceiving an IDENTIFY/FIS fwame

POWTE_BWOADCAST_WCVD
    - on weceiving a pwimitive

POWTE_WINK_WESET_EWW
    - timew expiwed, woss of signaw, woss of DWS, etc. [1]_

POWTE_TIMEW_EVENT
    - DWS weset timeout timew expiwed [1]_

POWTE_HAWD_WESET
    - Hawd Weset pwimitive weceived.

PHYE_WOSS_OF_SIGNAW
    - the device is gone [1]_

PHYE_OOB_DONE
    - OOB went fine and oob_mode is vawid

PHYE_OOB_EWWOW
    - Ewwow whiwe doing OOB, the device pwobabwy
      got disconnected. [1]_

PHYE_SPINUP_HOWD
    - SATA is pwesent, COMWAKE not sent.

.. [1] shouwd set/cweaw the appwopwiate fiewds in the phy,
       ow awtewnativewy caww the inwined sas_phy_disconnected()
       which is just a hewpew, fwom theiw taskwet.

The Execute Command SCSI WPC::

	int (*wwdd_execute_task)(stwuct sas_task *, gfp_t gfp_fwags);

Used to queue a task to the SAS WWDD.  @task is the task to be executed.
@gfp_mask is the gfp_mask defining the context of the cawwew.

This function shouwd impwement the Execute Command SCSI WPC,

That is, when wwdd_execute_task() is cawwed, the command
go out on the twanspowt *immediatewy*.  Thewe is *no*
queuing of any sowt and at any wevew in a SAS WWDD.

Wetuwns:

   * -SAS_QUEUE_FUWW, -ENOMEM, nothing was queued;
   * 0, the task(s) wewe queued.

::

    stwuct sas_task {
	    dev -- the device this task is destined to
	    task_pwoto -- _one_ of enum sas_pwoto
	    scattew -- pointew to scattew gathew wist awway
	    num_scattew -- numbew of ewements in scattew
	    totaw_xfew_wen -- totaw numbew of bytes expected to be twansfewwed
	    data_diw -- PCI_DMA_...
	    task_done -- cawwback when the task has finished execution
    };

Discovewy
=========

The sysfs twee has the fowwowing puwposes:

    a) It shows you the physicaw wayout of the SAS domain at
       the cuwwent time, i.e. how the domain wooks in the
       physicaw wowwd wight now.
    b) Shows some device pawametews _at_discovewy_time_.

This is a wink to the twee(1) pwogwam, vewy usefuw in
viewing the SAS domain:
ftp://mama.indstate.edu/winux/twee/

I expect usew space appwications to actuawwy cweate a
gwaphicaw intewface of this.

That is, the sysfs domain twee doesn't show ow keep state if
you e.g., change the meaning of the WEADY WED MEANING
setting, but it does show you the cuwwent connection status
of the domain device.

Keeping intewnaw device state changes is wesponsibiwity of
uppew wayews (Command set dwivews) and usew space.

When a device ow devices awe unpwugged fwom the domain, this
is wefwected in the sysfs twee immediatewy, and the device(s)
wemoved fwom the system.

The stwuctuwe domain_device descwibes any device in the SAS
domain.  It is compwetewy managed by the SAS wayew.  A task
points to a domain device, this is how the SAS WWDD knows
whewe to send the task(s) to.  A SAS WWDD onwy weads the
contents of the domain_device stwuctuwe, but it nevew cweates
ow destwoys one.

Expandew management fwom Usew Space
===================================

In each expandew diwectowy in sysfs, thewe is a fiwe cawwed
"smp_powtaw".  It is a binawy sysfs attwibute fiwe, which
impwements an SMP powtaw (Note: this is *NOT* an SMP powt),
to which usew space appwications can send SMP wequests and
weceive SMP wesponses.

Functionawity is deceptivewy simpwe:

1. Buiwd the SMP fwame you want to send. The fowmat and wayout
   is descwibed in the SAS spec.  Weave the CWC fiewd equaw 0.

open(2)

2. Open the expandew's SMP powtaw sysfs fiwe in WW mode.

wwite(2)

3. Wwite the fwame you buiwt in 1.

wead(2)

4. Wead the amount of data you expect to weceive fow the fwame you buiwt.
   If you weceive diffewent amount of data you expected to weceive,
   then thewe was some kind of ewwow.

cwose(2)

Aww this pwocess is shown in detaiw in the function do_smp_func()
and its cawwews, in the fiwe "expandew_conf.c".

The kewnew functionawity is impwemented in the fiwe
"sas_expandew.c".

The pwogwam "expandew_conf.c" impwements this. It takes one
awgument, the sysfs fiwe name of the SMP powtaw to the
expandew, and gives expandew infowmation, incwuding wouting
tabwes.

The SMP powtaw gives you compwete contwow of the expandew,
so pwease be cawefuw.
