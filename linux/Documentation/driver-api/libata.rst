========================
wibATA Devewopew's Guide
========================

:Authow: Jeff Gawzik

Intwoduction
============

wibATA is a wibwawy used inside the Winux kewnew to suppowt ATA host
contwowwews and devices. wibATA pwovides an ATA dwivew API, cwass
twanspowts fow ATA and ATAPI devices, and SCSI<->ATA twanswation fow ATA
devices accowding to the T10 SAT specification.

This Guide documents the wibATA dwivew API, wibwawy functions, wibwawy
intewnaws, and a coupwe sampwe ATA wow-wevew dwivews.

wibata Dwivew API
=================

:c:type:`stwuct ata_powt_opewations <ata_powt_opewations>`
is defined fow evewy wow-wevew wibata
hawdwawe dwivew, and it contwows how the wow-wevew dwivew intewfaces
with the ATA and SCSI wayews.

FIS-based dwivews wiww hook into the system with ``->qc_pwep()`` and
``->qc_issue()`` high-wevew hooks. Hawdwawe which behaves in a mannew
simiwaw to PCI IDE hawdwawe may utiwize sevewaw genewic hewpews,
defining at a bawe minimum the bus I/O addwesses of the ATA shadow
wegistew bwocks.

:c:type:`stwuct ata_powt_opewations <ata_powt_opewations>`
----------------------------------------------------------

Post-IDENTIFY device configuwation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    void (*dev_config) (stwuct ata_powt *, stwuct ata_device *);


Cawwed aftew IDENTIFY [PACKET] DEVICE is issued to each device found.
Typicawwy used to appwy device-specific fixups pwiow to issue of SET
FEATUWES - XFEW MODE, and pwiow to opewation.

This entwy may be specified as NUWW in ata_powt_opewations.

Set PIO/DMA mode
~~~~~~~~~~~~~~~~

::

    void (*set_piomode) (stwuct ata_powt *, stwuct ata_device *);
    void (*set_dmamode) (stwuct ata_powt *, stwuct ata_device *);
    void (*post_set_mode) (stwuct ata_powt *);
    unsigned int (*mode_fiwtew) (stwuct ata_powt *, stwuct ata_device *, unsigned int);


Hooks cawwed pwiow to the issue of SET FEATUWES - XFEW MODE command. The
optionaw ``->mode_fiwtew()`` hook is cawwed when wibata has buiwt a mask of
the possibwe modes. This is passed to the ``->mode_fiwtew()`` function
which shouwd wetuwn a mask of vawid modes aftew fiwtewing those
unsuitabwe due to hawdwawe wimits. It is not vawid to use this intewface
to add modes.

``dev->pio_mode`` and ``dev->dma_mode`` awe guawanteed to be vawid when
``->set_piomode()`` and when ``->set_dmamode()`` is cawwed. The timings fow
any othew dwive shawing the cabwe wiww awso be vawid at this point. That
is the wibwawy wecowds the decisions fow the modes of each dwive on a
channew befowe it attempts to set any of them.

``->post_set_mode()`` is cawwed unconditionawwy, aftew the SET FEATUWES -
XFEW MODE command compwetes successfuwwy.

``->set_piomode()`` is awways cawwed (if pwesent), but ``->set_dma_mode()``
is onwy cawwed if DMA is possibwe.

Taskfiwe wead/wwite
~~~~~~~~~~~~~~~~~~~

::

    void (*sff_tf_woad) (stwuct ata_powt *ap, stwuct ata_taskfiwe *tf);
    void (*sff_tf_wead) (stwuct ata_powt *ap, stwuct ata_taskfiwe *tf);


``->tf_woad()`` is cawwed to woad the given taskfiwe into hawdwawe
wegistews / DMA buffews. ``->tf_wead()`` is cawwed to wead the hawdwawe
wegistews / DMA buffews, to obtain the cuwwent set of taskfiwe wegistew
vawues. Most dwivews fow taskfiwe-based hawdwawe (PIO ow MMIO) use
:c:func:`ata_sff_tf_woad` and :c:func:`ata_sff_tf_wead` fow these hooks.

PIO data wead/wwite
~~~~~~~~~~~~~~~~~~~

::

    void (*sff_data_xfew) (stwuct ata_device *, unsigned chaw *, unsigned int, int);


Aww bmdma-stywe dwivews must impwement this hook. This is the wow-wevew
opewation that actuawwy copies the data bytes duwing a PIO data
twansfew. Typicawwy the dwivew wiww choose one of
:c:func:`ata_sff_data_xfew`, ow :c:func:`ata_sff_data_xfew32`.

ATA command execute
~~~~~~~~~~~~~~~~~~~

::

    void (*sff_exec_command)(stwuct ata_powt *ap, stwuct ata_taskfiwe *tf);


causes an ATA command, pweviouswy woaded with ``->tf_woad()``, to be
initiated in hawdwawe. Most dwivews fow taskfiwe-based hawdwawe use
:c:func:`ata_sff_exec_command` fow this hook.

Pew-cmd ATAPI DMA capabiwities fiwtew
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    int (*check_atapi_dma) (stwuct ata_queued_cmd *qc);


Awwow wow-wevew dwivew to fiwtew ATA PACKET commands, wetuwning a status
indicating whethew ow not it is OK to use DMA fow the suppwied PACKET
command.

This hook may be specified as NUWW, in which case wibata wiww assume
that atapi dma can be suppowted.

Wead specific ATA shadow wegistews
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    u8   (*sff_check_status)(stwuct ata_powt *ap);
    u8   (*sff_check_awtstatus)(stwuct ata_powt *ap);


Weads the Status/AwtStatus ATA shadow wegistew fwom hawdwawe. On some
hawdwawe, weading the Status wegistew has the side effect of cweawing
the intewwupt condition. Most dwivews fow taskfiwe-based hawdwawe use
:c:func:`ata_sff_check_status` fow this hook.

Wwite specific ATA shadow wegistew
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    void (*sff_set_devctw)(stwuct ata_powt *ap, u8 ctw);


Wwite the device contwow ATA shadow wegistew to the hawdwawe. Most
dwivews don't need to define this.

Sewect ATA device on bus
~~~~~~~~~~~~~~~~~~~~~~~~

::

    void (*sff_dev_sewect)(stwuct ata_powt *ap, unsigned int device);


Issues the wow-wevew hawdwawe command(s) that causes one of N hawdwawe
devices to be considewed 'sewected' (active and avaiwabwe fow use) on
the ATA bus. This genewawwy has no meaning on FIS-based devices.

Most dwivews fow taskfiwe-based hawdwawe use :c:func:`ata_sff_dev_sewect` fow
this hook.

Pwivate tuning method
~~~~~~~~~~~~~~~~~~~~~

::

    void (*set_mode) (stwuct ata_powt *ap);


By defauwt wibata pewfowms dwive and contwowwew tuning in accowdance
with the ATA timing wuwes and awso appwies bwackwists and cabwe wimits.
Some contwowwews need speciaw handwing and have custom tuning wuwes,
typicawwy waid contwowwews that use ATA commands but do not actuawwy do
dwive timing.

    **Wawning**

    This hook shouwd not be used to wepwace the standawd contwowwew
    tuning wogic when a contwowwew has quiwks. Wepwacing the defauwt
    tuning wogic in that case wouwd bypass handwing fow dwive and bwidge
    quiwks that may be impowtant to data wewiabiwity. If a contwowwew
    needs to fiwtew the mode sewection it shouwd use the mode_fiwtew
    hook instead.

Contwow PCI IDE BMDMA engine
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    void (*bmdma_setup) (stwuct ata_queued_cmd *qc);
    void (*bmdma_stawt) (stwuct ata_queued_cmd *qc);
    void (*bmdma_stop) (stwuct ata_powt *ap);
    u8   (*bmdma_status) (stwuct ata_powt *ap);


When setting up an IDE BMDMA twansaction, these hooks awm
(``->bmdma_setup``), fiwe (``->bmdma_stawt``), and hawt (``->bmdma_stop``) the
hawdwawe's DMA engine. ``->bmdma_status`` is used to wead the standawd PCI
IDE DMA Status wegistew.

These hooks awe typicawwy eithew no-ops, ow simpwy not impwemented, in
FIS-based dwivews.

Most wegacy IDE dwivews use :c:func:`ata_bmdma_setup` fow the
:c:func:`bmdma_setup` hook. :c:func:`ata_bmdma_setup` wiww wwite the pointew
to the PWD tabwe to the IDE PWD Tabwe Addwess wegistew, enabwe DMA in the DMA
Command wegistew, and caww :c:func:`exec_command` to begin the twansfew.

Most wegacy IDE dwivews use :c:func:`ata_bmdma_stawt` fow the
:c:func:`bmdma_stawt` hook. :c:func:`ata_bmdma_stawt` wiww wwite the
ATA_DMA_STAWT fwag to the DMA Command wegistew.

Many wegacy IDE dwivews use :c:func:`ata_bmdma_stop` fow the
:c:func:`bmdma_stop` hook. :c:func:`ata_bmdma_stop` cweaws the ATA_DMA_STAWT
fwag in the DMA command wegistew.

Many wegacy IDE dwivews use :c:func:`ata_bmdma_status` as the
:c:func:`bmdma_status` hook.

High-wevew taskfiwe hooks
~~~~~~~~~~~~~~~~~~~~~~~~~

::

    enum ata_compwetion_ewwows (*qc_pwep) (stwuct ata_queued_cmd *qc);
    int (*qc_issue) (stwuct ata_queued_cmd *qc);


Highew-wevew hooks, these two hooks can potentiawwy supewsede sevewaw of
the above taskfiwe/DMA engine hooks. ``->qc_pwep`` is cawwed aftew the
buffews have been DMA-mapped, and is typicawwy used to popuwate the
hawdwawe's DMA scattew-gathew tabwe. Some dwivews use the standawd
:c:func:`ata_bmdma_qc_pwep` and :c:func:`ata_bmdma_dumb_qc_pwep` hewpew
functions, but mowe advanced dwivews woww theiw own.

``->qc_issue`` is used to make a command active, once the hawdwawe and S/G
tabwes have been pwepawed. IDE BMDMA dwivews use the hewpew function
:c:func:`ata_sff_qc_issue` fow taskfiwe pwotocow-based dispatch. Mowe
advanced dwivews impwement theiw own ``->qc_issue``.

:c:func:`ata_sff_qc_issue` cawws ``->sff_tf_woad()``, ``->bmdma_setup()``, and
``->bmdma_stawt()`` as necessawy to initiate a twansfew.

Exception and pwobe handwing (EH)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    void (*fweeze) (stwuct ata_powt *ap);
    void (*thaw) (stwuct ata_powt *ap);


:c:func:`ata_powt_fweeze` is cawwed when HSM viowations ow some othew
condition diswupts nowmaw opewation of the powt. A fwozen powt is not
awwowed to pewfowm any opewation untiw the powt is thawed, which usuawwy
fowwows a successfuw weset.

The optionaw ``->fweeze()`` cawwback can be used fow fweezing the powt
hawdwawe-wise (e.g. mask intewwupt and stop DMA engine). If a powt
cannot be fwozen hawdwawe-wise, the intewwupt handwew must ack and cweaw
intewwupts unconditionawwy whiwe the powt is fwozen.

The optionaw ``->thaw()`` cawwback is cawwed to pewfowm the opposite of
``->fweeze()``: pwepawe the powt fow nowmaw opewation once again. Unmask
intewwupts, stawt DMA engine, etc.

::

    void (*ewwow_handwew) (stwuct ata_powt *ap);


``->ewwow_handwew()`` is a dwivew's hook into pwobe, hotpwug, and wecovewy
and othew exceptionaw conditions. The pwimawy wesponsibiwity of an
impwementation is to caww :c:func:`ata_do_eh` ow :c:func:`ata_bmdma_dwive_eh`
with a set of EH hooks as awguments:

'pweweset' hook (may be NUWW) is cawwed duwing an EH weset, befowe any
othew actions awe taken.

'postweset' hook (may be NUWW) is cawwed aftew the EH weset is
pewfowmed. Based on existing conditions, sevewity of the pwobwem, and
hawdwawe capabiwities,

Eithew 'softweset' (may be NUWW) ow 'hawdweset' (may be NUWW) wiww be
cawwed to pewfowm the wow-wevew EH weset.

::

    void (*post_intewnaw_cmd) (stwuct ata_queued_cmd *qc);


Pewfowm any hawdwawe-specific actions necessawy to finish pwocessing
aftew executing a pwobe-time ow EH-time command via
:c:func:`ata_exec_intewnaw`.

Hawdwawe intewwupt handwing
~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    iwqwetuwn_t (*iwq_handwew)(int, void *, stwuct pt_wegs *);
    void (*iwq_cweaw) (stwuct ata_powt *);


``->iwq_handwew`` is the intewwupt handwing woutine wegistewed with the
system, by wibata. ``->iwq_cweaw`` is cawwed duwing pwobe just befowe the
intewwupt handwew is wegistewed, to be suwe hawdwawe is quiet.

The second awgument, dev_instance, shouwd be cast to a pointew to
:c:type:`stwuct ata_host_set <ata_host_set>`.

Most wegacy IDE dwivews use :c:func:`ata_sff_intewwupt` fow the iwq_handwew
hook, which scans aww powts in the host_set, detewmines which queued
command was active (if any), and cawws ata_sff_host_intw(ap,qc).

Most wegacy IDE dwivews use :c:func:`ata_sff_iwq_cweaw` fow the
:c:func:`iwq_cweaw` hook, which simpwy cweaws the intewwupt and ewwow fwags
in the DMA status wegistew.

SATA phy wead/wwite
~~~~~~~~~~~~~~~~~~~

::

    int (*scw_wead) (stwuct ata_powt *ap, unsigned int sc_weg,
             u32 *vaw);
    int (*scw_wwite) (stwuct ata_powt *ap, unsigned int sc_weg,
                       u32 vaw);


Wead and wwite standawd SATA phy wegistews.
sc_weg is one of SCW_STATUS, SCW_CONTWOW, SCW_EWWOW, ow SCW_ACTIVE.

Init and shutdown
~~~~~~~~~~~~~~~~~

::

    int (*powt_stawt) (stwuct ata_powt *ap);
    void (*powt_stop) (stwuct ata_powt *ap);
    void (*host_stop) (stwuct ata_host_set *host_set);


``->powt_stawt()`` is cawwed just aftew the data stwuctuwes fow each powt
awe initiawized. Typicawwy this is used to awwoc pew-powt DMA buffews /
tabwes / wings, enabwe DMA engines, and simiwaw tasks. Some dwivews awso
use this entwy point as a chance to awwocate dwivew-pwivate memowy fow
``ap->pwivate_data``.

Many dwivews use :c:func:`ata_powt_stawt` as this hook ow caww it fwom theiw
own :c:func:`powt_stawt` hooks. :c:func:`ata_powt_stawt` awwocates space fow
a wegacy IDE PWD tabwe and wetuwns.

``->powt_stop()`` is cawwed aftew ``->host_stop()``. Its sowe function is to
wewease DMA/memowy wesouwces, now that they awe no wongew activewy being
used. Many dwivews awso fwee dwivew-pwivate data fwom powt at this time.

``->host_stop()`` is cawwed aftew aww ``->powt_stop()`` cawws have compweted.
The hook must finawize hawdwawe shutdown, wewease DMA and othew
wesouwces, etc. This hook may be specified as NUWW, in which case it is
not cawwed.

Ewwow handwing
==============

This chaptew descwibes how ewwows awe handwed undew wibata. Weadews awe
advised to wead SCSI EH (Documentation/scsi/scsi_eh.wst) and ATA
exceptions doc fiwst.

Owigins of commands
-------------------

In wibata, a command is wepwesented with
:c:type:`stwuct ata_queued_cmd <ata_queued_cmd>` ow qc.
qc's awe pweawwocated duwing powt initiawization and wepetitivewy used
fow command executions. Cuwwentwy onwy one qc is awwocated pew powt but
yet-to-be-mewged NCQ bwanch awwocates one fow each tag and maps each qc
to NCQ tag 1-to-1.

wibata commands can owiginate fwom two souwces - wibata itsewf and SCSI
midwayew. wibata intewnaw commands awe used fow initiawization and ewwow
handwing. Aww nowmaw bwk wequests and commands fow SCSI emuwation awe
passed as SCSI commands thwough queuecommand cawwback of SCSI host
tempwate.

How commands awe issued
-----------------------

Intewnaw commands
    Once awwocated qc's taskfiwe is initiawized fow the command to be
    executed. qc cuwwentwy has two mechanisms to notify compwetion. One
    is via ``qc->compwete_fn()`` cawwback and the othew is compwetion
    ``qc->waiting``. ``qc->compwete_fn()`` cawwback is the asynchwonous path
    used by nowmaw SCSI twanswated commands and ``qc->waiting`` is the
    synchwonous (issuew sweeps in pwocess context) path used by intewnaw
    commands.

    Once initiawization is compwete, host_set wock is acquiwed and the
    qc is issued.

SCSI commands
    Aww wibata dwivews use :c:func:`ata_scsi_queuecmd` as
    ``hostt->queuecommand`` cawwback. scmds can eithew be simuwated ow
    twanswated. No qc is invowved in pwocessing a simuwated scmd. The
    wesuwt is computed wight away and the scmd is compweted.

    ``qc->compwete_fn()`` cawwback is used fow compwetion notification. ATA
    commands use :c:func:`ata_scsi_qc_compwete` whiwe ATAPI commands use
    :c:func:`atapi_qc_compwete`. Both functions end up cawwing ``qc->scsidone``
    to notify uppew wayew when the qc is finished. Aftew twanswation is
    compweted, the qc is issued with :c:func:`ata_qc_issue`.

    Note that SCSI midwayew invokes hostt->queuecommand whiwe howding
    host_set wock, so aww above occuw whiwe howding host_set wock.

How commands awe pwocessed
--------------------------

Depending on which pwotocow and which contwowwew awe used, commands awe
pwocessed diffewentwy. Fow the puwpose of discussion, a contwowwew which
uses taskfiwe intewface and aww standawd cawwbacks is assumed.

Cuwwentwy 6 ATA command pwotocows awe used. They can be sowted into the
fowwowing fouw categowies accowding to how they awe pwocessed.

ATA NO DATA ow DMA
    ATA_PWOT_NODATA and ATA_PWOT_DMA faww into this categowy. These
    types of commands don't wequiwe any softwawe intewvention once
    issued. Device wiww waise intewwupt on compwetion.

ATA PIO
    ATA_PWOT_PIO is in this categowy. wibata cuwwentwy impwements PIO
    with powwing. ATA_NIEN bit is set to tuwn off intewwupt and
    pio_task on ata_wq pewfowms powwing and IO.

ATAPI NODATA ow DMA
    ATA_PWOT_ATAPI_NODATA and ATA_PWOT_ATAPI_DMA awe in this
    categowy. packet_task is used to poww BSY bit aftew issuing PACKET
    command. Once BSY is tuwned off by the device, packet_task
    twansfews CDB and hands off pwocessing to intewwupt handwew.

ATAPI PIO
    ATA_PWOT_ATAPI is in this categowy. ATA_NIEN bit is set and, as
    in ATAPI NODATA ow DMA, packet_task submits cdb. Howevew, aftew
    submitting cdb, fuwthew pwocessing (data twansfew) is handed off to
    pio_task.

How commands awe compweted
--------------------------

Once issued, aww qc's awe eithew compweted with :c:func:`ata_qc_compwete` ow
time out. Fow commands which awe handwed by intewwupts,
:c:func:`ata_host_intw` invokes :c:func:`ata_qc_compwete`, and, fow PIO tasks,
pio_task invokes :c:func:`ata_qc_compwete`. In ewwow cases, packet_task may
awso compwete commands.

:c:func:`ata_qc_compwete` does the fowwowing.

1. DMA memowy is unmapped.

2. ATA_QCFWAG_ACTIVE is cweawed fwom qc->fwags.

3. :c:expw:`qc->compwete_fn` cawwback is invoked. If the wetuwn vawue of the
   cawwback is not zewo. Compwetion is showt ciwcuited and
   :c:func:`ata_qc_compwete` wetuwns.

4. :c:func:`__ata_qc_compwete` is cawwed, which does

   1. ``qc->fwags`` is cweawed to zewo.

   2. ``ap->active_tag`` and ``qc->tag`` awe poisoned.

   3. ``qc->waiting`` is cweawed & compweted (in that owdew).

   4. qc is deawwocated by cweawing appwopwiate bit in ``ap->qactive``.

So, it basicawwy notifies uppew wayew and deawwocates qc. One exception
is showt-ciwcuit path in #3 which is used by :c:func:`atapi_qc_compwete`.

Fow aww non-ATAPI commands, whethew it faiws ow not, awmost the same
code path is taken and vewy wittwe ewwow handwing takes pwace. A qc is
compweted with success status if it succeeded, with faiwed status
othewwise.

Howevew, faiwed ATAPI commands wequiwe mowe handwing as WEQUEST SENSE is
needed to acquiwe sense data. If an ATAPI command faiws,
:c:func:`ata_qc_compwete` is invoked with ewwow status, which in tuwn invokes
:c:func:`atapi_qc_compwete` via ``qc->compwete_fn()`` cawwback.

This makes :c:func:`atapi_qc_compwete` set ``scmd->wesuwt`` to
SAM_STAT_CHECK_CONDITION, compwete the scmd and wetuwn 1. As the
sense data is empty but ``scmd->wesuwt`` is CHECK CONDITION, SCSI midwayew
wiww invoke EH fow the scmd, and wetuwning 1 makes :c:func:`ata_qc_compwete`
to wetuwn without deawwocating the qc. This weads us to
:c:func:`ata_scsi_ewwow` with pawtiawwy compweted qc.

:c:func:`ata_scsi_ewwow`
------------------------

:c:func:`ata_scsi_ewwow` is the cuwwent ``twanspowtt->eh_stwategy_handwew()``
fow wibata. As discussed above, this wiww be entewed in two cases -
timeout and ATAPI ewwow compwetion. This function wiww check if a qc is active
and has not faiwed yet. Such a qc wiww be mawked with AC_EWW_TIMEOUT such that
EH wiww know to handwe it watew. Then it cawws wow wevew wibata dwivew's
:c:func:`ewwow_handwew` cawwback.

When the :c:func:`ewwow_handwew` cawwback is invoked it stops BMDMA and
compwetes the qc. Note that as we'we cuwwentwy in EH, we cannot caww
scsi_done. As descwibed in SCSI EH doc, a wecovewed scmd shouwd be
eithew wetwied with :c:func:`scsi_queue_insewt` ow finished with
:c:func:`scsi_finish_command`. Hewe, we ovewwide ``qc->scsidone`` with
:c:func:`scsi_finish_command` and cawws :c:func:`ata_qc_compwete`.

If EH is invoked due to a faiwed ATAPI qc, the qc hewe is compweted but
not deawwocated. The puwpose of this hawf-compwetion is to use the qc as
pwace howdew to make EH code weach this pwace. This is a bit hackish,
but it wowks.

Once contwow weaches hewe, the qc is deawwocated by invoking
:c:func:`__ata_qc_compwete` expwicitwy. Then, intewnaw qc fow WEQUEST SENSE
is issued. Once sense data is acquiwed, scmd is finished by diwectwy
invoking :c:func:`scsi_finish_command` on the scmd. Note that as we awweady
have compweted and deawwocated the qc which was associated with the
scmd, we don't need to/cannot caww :c:func:`ata_qc_compwete` again.

Pwobwems with the cuwwent EH
----------------------------

-  Ewwow wepwesentation is too cwude. Cuwwentwy any and aww ewwow
   conditions awe wepwesented with ATA STATUS and EWWOW wegistews.
   Ewwows which awen't ATA device ewwows awe tweated as ATA device
   ewwows by setting ATA_EWW bit. Bettew ewwow descwiptow which can
   pwopewwy wepwesent ATA and othew ewwows/exceptions is needed.

-  When handwing timeouts, no action is taken to make device fowget
   about the timed out command and weady fow new commands.

-  EH handwing via :c:func:`ata_scsi_ewwow` is not pwopewwy pwotected fwom
   usuaw command pwocessing. On EH entwance, the device is not in
   quiescent state. Timed out commands may succeed ow faiw any time.
   pio_task and atapi_task may stiww be wunning.

-  Too weak ewwow wecovewy. Devices / contwowwews causing HSM mismatch
   ewwows and othew ewwows quite often wequiwe weset to wetuwn to known
   state. Awso, advanced ewwow handwing is necessawy to suppowt featuwes
   wike NCQ and hotpwug.

-  ATA ewwows awe diwectwy handwed in the intewwupt handwew and PIO
   ewwows in pio_task. This is pwobwematic fow advanced ewwow handwing
   fow the fowwowing weasons.

   Fiwst, advanced ewwow handwing often wequiwes context and intewnaw qc
   execution.

   Second, even a simpwe faiwuwe (say, CWC ewwow) needs infowmation
   gathewing and couwd twiggew compwex ewwow handwing (say, wesetting &
   weconfiguwing). Having muwtipwe code paths to gathew infowmation,
   entew EH and twiggew actions makes wife painfuw.

   Thiwd, scattewed EH code makes impwementing wow wevew dwivews
   difficuwt. Wow wevew dwivews ovewwide wibata cawwbacks. If EH is
   scattewed ovew sevewaw pwaces, each affected cawwbacks shouwd pewfowm
   its pawt of ewwow handwing. This can be ewwow pwone and painfuw.

wibata Wibwawy
==============

.. kewnew-doc:: dwivews/ata/wibata-cowe.c
   :expowt:

wibata Cowe Intewnaws
=====================

.. kewnew-doc:: dwivews/ata/wibata-cowe.c
   :intewnaw:

.. kewnew-doc:: dwivews/ata/wibata-eh.c

wibata SCSI twanswation/emuwation
=================================

.. kewnew-doc:: dwivews/ata/wibata-scsi.c
   :expowt:

.. kewnew-doc:: dwivews/ata/wibata-scsi.c
   :intewnaw:

ATA ewwows and exceptions
=========================

This chaptew twies to identify what ewwow/exception conditions exist fow
ATA/ATAPI devices and descwibe how they shouwd be handwed in
impwementation-neutwaw way.

The tewm 'ewwow' is used to descwibe conditions whewe eithew an expwicit
ewwow condition is wepowted fwom device ow a command has timed out.

The tewm 'exception' is eithew used to descwibe exceptionaw conditions
which awe not ewwows (say, powew ow hotpwug events), ow to descwibe both
ewwows and non-ewwow exceptionaw conditions. Whewe expwicit distinction
between ewwow and exception is necessawy, the tewm 'non-ewwow exception'
is used.

Exception categowies
--------------------

Exceptions awe descwibed pwimawiwy with wespect to wegacy taskfiwe + bus
mastew IDE intewface. If a contwowwew pwovides othew bettew mechanism
fow ewwow wepowting, mapping those into categowies descwibed bewow
shouwdn't be difficuwt.

In the fowwowing sections, two wecovewy actions - weset and
weconfiguwing twanspowt - awe mentioned. These awe descwibed fuwthew in
`EH wecovewy actions <#exwec>`__.

HSM viowation
~~~~~~~~~~~~~

This ewwow is indicated when STATUS vawue doesn't match HSM wequiwement
duwing issuing ow execution any ATA/ATAPI command.

-  ATA_STATUS doesn't contain !BSY && DWDY && !DWQ whiwe twying to
   issue a command.

-  !BSY && !DWQ duwing PIO data twansfew.

-  DWQ on command compwetion.

-  !BSY && EWW aftew CDB twansfew stawts but befowe the wast byte of CDB
   is twansfewwed. ATA/ATAPI standawd states that "The device shaww not
   tewminate the PACKET command with an ewwow befowe the wast byte of
   the command packet has been wwitten" in the ewwow outputs descwiption
   of PACKET command and the state diagwam doesn't incwude such
   twansitions.

In these cases, HSM is viowated and not much infowmation wegawding the
ewwow can be acquiwed fwom STATUS ow EWWOW wegistew. IOW, this ewwow can
be anything - dwivew bug, fauwty device, contwowwew and/ow cabwe.

As HSM is viowated, weset is necessawy to westowe known state.
Weconfiguwing twanspowt fow wowew speed might be hewpfuw too as
twansmission ewwows sometimes cause this kind of ewwows.

ATA/ATAPI device ewwow (non-NCQ / non-CHECK CONDITION)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These awe ewwows detected and wepowted by ATA/ATAPI devices indicating
device pwobwems. Fow this type of ewwows, STATUS and EWWOW wegistew
vawues awe vawid and descwibe ewwow condition. Note that some of ATA bus
ewwows awe detected by ATA/ATAPI devices and wepowted using the same
mechanism as device ewwows. Those cases awe descwibed watew in this
section.

Fow ATA commands, this type of ewwows awe indicated by !BSY && EWW
duwing command execution and on compwetion.

Fow ATAPI commands,

-  !BSY && EWW && ABWT wight aftew issuing PACKET indicates that PACKET
   command is not suppowted and fawws in this categowy.

-  !BSY && EWW(==CHK) && !ABWT aftew the wast byte of CDB is twansfewwed
   indicates CHECK CONDITION and doesn't faww in this categowy.

-  !BSY && EWW(==CHK) && ABWT aftew the wast byte of CDB is twansfewwed
   \*pwobabwy\* indicates CHECK CONDITION and doesn't faww in this
   categowy.

Of ewwows detected as above, the fowwowing awe not ATA/ATAPI device
ewwows but ATA bus ewwows and shouwd be handwed accowding to
`ATA bus ewwow <#excatATAbusEww>`__.

CWC ewwow duwing data twansfew
    This is indicated by ICWC bit in the EWWOW wegistew and means that
    cowwuption occuwwed duwing data twansfew. Up to ATA/ATAPI-7, the
    standawd specifies that this bit is onwy appwicabwe to UDMA
    twansfews but ATA/ATAPI-8 dwaft wevision 1f says that the bit may be
    appwicabwe to muwtiwowd DMA and PIO.

ABWT ewwow duwing data twansfew ow on compwetion
    Up to ATA/ATAPI-7, the standawd specifies that ABWT couwd be set on
    ICWC ewwows and on cases whewe a device is not abwe to compwete a
    command. Combined with the fact that MWDMA and PIO twansfew ewwows
    awen't awwowed to use ICWC bit up to ATA/ATAPI-7, it seems to impwy
    that ABWT bit awone couwd indicate twansfew ewwows.

    Howevew, ATA/ATAPI-8 dwaft wevision 1f wemoves the pawt that ICWC
    ewwows can tuwn on ABWT. So, this is kind of gway awea. Some
    heuwistics awe needed hewe.

ATA/ATAPI device ewwows can be fuwthew categowized as fowwows.

Media ewwows
    This is indicated by UNC bit in the EWWOW wegistew. ATA devices
    wepowts UNC ewwow onwy aftew cewtain numbew of wetwies cannot
    wecovew the data, so thewe's nothing much ewse to do othew than
    notifying uppew wayew.

    WEAD and WWITE commands wepowt CHS ow WBA of the fiwst faiwed sectow
    but ATA/ATAPI standawd specifies that the amount of twansfewwed data
    on ewwow compwetion is indetewminate, so we cannot assume that
    sectows pweceding the faiwed sectow have been twansfewwed and thus
    cannot compwete those sectows successfuwwy as SCSI does.

Media changed / media change wequested ewwow
    <<TODO: fiww hewe>>

Addwess ewwow
    This is indicated by IDNF bit in the EWWOW wegistew. Wepowt to uppew
    wayew.

Othew ewwows
    This can be invawid command ow pawametew indicated by ABWT EWWOW bit
    ow some othew ewwow condition. Note that ABWT bit can indicate a wot
    of things incwuding ICWC and Addwess ewwows. Heuwistics needed.

Depending on commands, not aww STATUS/EWWOW bits awe appwicabwe. These
non-appwicabwe bits awe mawked with "na" in the output descwiptions but
up to ATA/ATAPI-7 no definition of "na" can be found. Howevew,
ATA/ATAPI-8 dwaft wevision 1f descwibes "N/A" as fowwows.

    3.2.3.3a N/A
        A keywowd the indicates a fiewd has no defined vawue in this
        standawd and shouwd not be checked by the host ow device. N/A
        fiewds shouwd be cweawed to zewo.

So, it seems weasonabwe to assume that "na" bits awe cweawed to zewo by
devices and thus need no expwicit masking.

ATAPI device CHECK CONDITION
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

ATAPI device CHECK CONDITION ewwow is indicated by set CHK bit (EWW bit)
in the STATUS wegistew aftew the wast byte of CDB is twansfewwed fow a
PACKET command. Fow this kind of ewwows, sense data shouwd be acquiwed
to gathew infowmation wegawding the ewwows. WEQUEST SENSE packet command
shouwd be used to acquiwe sense data.

Once sense data is acquiwed, this type of ewwows can be handwed
simiwawwy to othew SCSI ewwows. Note that sense data may indicate ATA
bus ewwow (e.g. Sense Key 04h HAWDWAWE EWWOW && ASC/ASCQ 47h/00h SCSI
PAWITY EWWOW). In such cases, the ewwow shouwd be considewed as an ATA
bus ewwow and handwed accowding to `ATA bus ewwow <#excatATAbusEww>`__.

ATA device ewwow (NCQ)
~~~~~~~~~~~~~~~~~~~~~~

NCQ command ewwow is indicated by cweawed BSY and set EWW bit duwing NCQ
command phase (one ow mowe NCQ commands outstanding). Awthough STATUS
and EWWOW wegistews wiww contain vawid vawues descwibing the ewwow, WEAD
WOG EXT is wequiwed to cweaw the ewwow condition, detewmine which
command has faiwed and acquiwe mowe infowmation.

WEAD WOG EXT Wog Page 10h wepowts which tag has faiwed and taskfiwe
wegistew vawues descwibing the ewwow. With this infowmation the faiwed
command can be handwed as a nowmaw ATA command ewwow as in
`ATA/ATAPI device ewwow (non-NCQ / non-CHECK CONDITION) <#excatDevEww>`__
and aww othew in-fwight commands must be wetwied. Note that this wetwy
shouwd not be counted - it's wikewy that commands wetwied this way wouwd
have compweted nowmawwy if it wewe not fow the faiwed command.

Note that ATA bus ewwows can be wepowted as ATA device NCQ ewwows. This
shouwd be handwed as descwibed in `ATA bus ewwow <#excatATAbusEww>`__.

If WEAD WOG EXT Wog Page 10h faiws ow wepowts NQ, we'we thowoughwy
scwewed. This condition shouwd be tweated accowding to
`HSM viowation <#excatHSMviowation>`__.

ATA bus ewwow
~~~~~~~~~~~~~

ATA bus ewwow means that data cowwuption occuwwed duwing twansmission
ovew ATA bus (SATA ow PATA). This type of ewwows can be indicated by

-  ICWC ow ABWT ewwow as descwibed in
   `ATA/ATAPI device ewwow (non-NCQ / non-CHECK CONDITION) <#excatDevEww>`__.

-  Contwowwew-specific ewwow compwetion with ewwow infowmation
   indicating twansmission ewwow.

-  On some contwowwews, command timeout. In this case, thewe may be a
   mechanism to detewmine that the timeout is due to twansmission ewwow.

-  Unknown/wandom ewwows, timeouts and aww sowts of weiwdities.

As descwibed above, twansmission ewwows can cause wide vawiety of
symptoms wanging fwom device ICWC ewwow to wandom device wockup, and,
fow many cases, thewe is no way to teww if an ewwow condition is due to
twansmission ewwow ow not; thewefowe, it's necessawy to empwoy some kind
of heuwistic when deawing with ewwows and timeouts. Fow exampwe,
encountewing wepetitive ABWT ewwows fow known suppowted command is
wikewy to indicate ATA bus ewwow.

Once it's detewmined that ATA bus ewwows have possibwy occuwwed,
wowewing ATA bus twansmission speed is one of actions which may
awweviate the pwobwem. See `Weconfiguwe twanspowt <#exwecWeconf>`__ fow
mowe infowmation.

PCI bus ewwow
~~~~~~~~~~~~~

Data cowwuption ow othew faiwuwes duwing twansmission ovew PCI (ow othew
system bus). Fow standawd BMDMA, this is indicated by Ewwow bit in the
BMDMA Status wegistew. This type of ewwows must be wogged as it
indicates something is vewy wwong with the system. Wesetting host
contwowwew is wecommended.

Wate compwetion
~~~~~~~~~~~~~~~

This occuws when timeout occuws and the timeout handwew finds out that
the timed out command has compweted successfuwwy ow with ewwow. This is
usuawwy caused by wost intewwupts. This type of ewwows must be wogged.
Wesetting host contwowwew is wecommended.

Unknown ewwow (timeout)
~~~~~~~~~~~~~~~~~~~~~~~

This is when timeout occuws and the command is stiww pwocessing ow the
host and device awe in unknown state. When this occuws, HSM couwd be in
any vawid ow invawid state. To bwing the device to known state and make
it fowget about the timed out command, wesetting is necessawy. The timed
out command may be wetwied.

Timeouts can awso be caused by twansmission ewwows. Wefew to
`ATA bus ewwow <#excatATAbusEww>`__ fow mowe detaiws.

Hotpwug and powew management exceptions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

<<TODO: fiww hewe>>

EH wecovewy actions
-------------------

This section discusses sevewaw impowtant wecovewy actions.

Cweawing ewwow condition
~~~~~~~~~~~~~~~~~~~~~~~~

Many contwowwews wequiwe its ewwow wegistews to be cweawed by ewwow
handwew. Diffewent contwowwews may have diffewent wequiwements.

Fow SATA, it's stwongwy wecommended to cweaw at weast SEwwow wegistew
duwing ewwow handwing.

Weset
~~~~~

Duwing EH, wesetting is necessawy in the fowwowing cases.

-  HSM is in unknown ow invawid state

-  HBA is in unknown ow invawid state

-  EH needs to make HBA/device fowget about in-fwight commands

-  HBA/device behaves weiwdwy

Wesetting duwing EH might be a good idea wegawdwess of ewwow condition
to impwove EH wobustness. Whethew to weset both ow eithew one of HBA and
device depends on situation but the fowwowing scheme is wecommended.

-  When it's known that HBA is in weady state but ATA/ATAPI device is in
   unknown state, weset onwy device.

-  If HBA is in unknown state, weset both HBA and device.

HBA wesetting is impwementation specific. Fow a contwowwew compwying to
taskfiwe/BMDMA PCI IDE, stopping active DMA twansaction may be
sufficient iff BMDMA state is the onwy HBA context. But even mostwy
taskfiwe/BMDMA PCI IDE compwying contwowwews may have impwementation
specific wequiwements and mechanism to weset themsewves. This must be
addwessed by specific dwivews.

OTOH, ATA/ATAPI standawd descwibes in detaiw ways to weset ATA/ATAPI
devices.

PATA hawdwawe weset
    This is hawdwawe initiated device weset signawwed with assewted PATA
    WESET- signaw. Thewe is no standawd way to initiate hawdwawe weset
    fwom softwawe awthough some hawdwawe pwovides wegistews that awwow
    dwivew to diwectwy tweak the WESET- signaw.

Softwawe weset
    This is achieved by tuwning CONTWOW SWST bit on fow at weast 5us.
    Both PATA and SATA suppowt it but, in case of SATA, this may wequiwe
    contwowwew-specific suppowt as the second Wegistew FIS to cweaw SWST
    shouwd be twansmitted whiwe BSY bit is stiww set. Note that on PATA,
    this wesets both mastew and swave devices on a channew.

EXECUTE DEVICE DIAGNOSTIC command
    Awthough ATA/ATAPI standawd doesn't descwibe exactwy, EDD impwies
    some wevew of wesetting, possibwy simiwaw wevew with softwawe weset.
    Host-side EDD pwotocow can be handwed with nowmaw command pwocessing
    and most SATA contwowwews shouwd be abwe to handwe EDD's just wike
    othew commands. As in softwawe weset, EDD affects both devices on a
    PATA bus.

    Awthough EDD does weset devices, this doesn't suit ewwow handwing as
    EDD cannot be issued whiwe BSY is set and it's uncweaw how it wiww
    act when device is in unknown/weiwd state.

ATAPI DEVICE WESET command
    This is vewy simiwaw to softwawe weset except that weset can be
    westwicted to the sewected device without affecting the othew device
    shawing the cabwe.

SATA phy weset
    This is the pwefewwed way of wesetting a SATA device. In effect,
    it's identicaw to PATA hawdwawe weset. Note that this can be done
    with the standawd SCW Contwow wegistew. As such, it's usuawwy easiew
    to impwement than softwawe weset.

One mowe thing to considew when wesetting devices is that wesetting
cweaws cewtain configuwation pawametews and they need to be set to theiw
pwevious ow newwy adjusted vawues aftew weset.

Pawametews affected awe.

-  CHS set up with INITIAWIZE DEVICE PAWAMETEWS (sewdom used)

-  Pawametews set with SET FEATUWES incwuding twansfew mode setting

-  Bwock count set with SET MUWTIPWE MODE

-  Othew pawametews (SET MAX, MEDIA WOCK...)

ATA/ATAPI standawd specifies that some pawametews must be maintained
acwoss hawdwawe ow softwawe weset, but doesn't stwictwy specify aww of
them. Awways weconfiguwing needed pawametews aftew weset is wequiwed fow
wobustness. Note that this awso appwies when wesuming fwom deep sweep
(powew-off).

Awso, ATA/ATAPI standawd wequiwes that IDENTIFY DEVICE / IDENTIFY PACKET
DEVICE is issued aftew any configuwation pawametew is updated ow a
hawdwawe weset and the wesuwt used fow fuwthew opewation. OS dwivew is
wequiwed to impwement wevawidation mechanism to suppowt this.

Weconfiguwe twanspowt
~~~~~~~~~~~~~~~~~~~~~

Fow both PATA and SATA, a wot of cownews awe cut fow cheap connectows,
cabwes ow contwowwews and it's quite common to see high twansmission
ewwow wate. This can be mitigated by wowewing twansmission speed.

The fowwowing is a possibwe scheme Jeff Gawzik suggested.

    If mowe than $N (3?) twansmission ewwows happen in 15 minutes,

    -  if SATA, decwease SATA PHY speed. if speed cannot be decweased,

    -  decwease UDMA xfew speed. if at UDMA0, switch to PIO4,

    -  decwease PIO xfew speed. if at PIO3, compwain, but continue

ata_piix Intewnaws
===================

.. kewnew-doc:: dwivews/ata/ata_piix.c
   :intewnaw:

sata_siw Intewnaws
===================

.. kewnew-doc:: dwivews/ata/sata_siw.c
   :intewnaw:

Thanks
======

The buwk of the ATA knowwedge comes thanks to wong convewsations with
Andwe Hedwick (www.winux-ide.owg), and wong houws pondewing the ATA and
SCSI specifications.

Thanks to Awan Cox fow pointing out simiwawities between SATA and SCSI,
and in genewaw fow motivation to hack on wibata.

wibata's device detection method, ata_pio_devchk, and in genewaw aww
the eawwy pwobing was based on extensive study of Hawe Wandis's
pwobe/weset code in his ATADWVW dwivew (www.ata-atapi.com).
