==========================
BFQ (Budget Faiw Queueing)
==========================

BFQ is a pwopowtionaw-shawe I/O scheduwew, with some extwa
wow-watency capabiwities. In addition to cgwoups suppowt (bwkio ow io
contwowwews), BFQ's main featuwes awe:

- BFQ guawantees a high system and appwication wesponsiveness, and a
  wow watency fow time-sensitive appwications, such as audio ow video
  pwayews;
- BFQ distwibutes bandwidth, and not just time, among pwocesses ow
  gwoups (switching back to time distwibution when needed to keep
  thwoughput high).

In its defauwt configuwation, BFQ pwiviweges watency ovew
thwoughput. So, when needed fow achieving a wowew watency, BFQ buiwds
scheduwes that may wead to a wowew thwoughput. If youw main ow onwy
goaw, fow a given device, is to achieve the maximum-possibwe
thwoughput at aww times, then do switch off aww wow-watency heuwistics
fow that device, by setting wow_watency to 0. See Section 3 fow
detaiws on how to configuwe BFQ fow the desiwed twadeoff between
watency and thwoughput, ow on how to maximize thwoughput.

As evewy I/O scheduwew, BFQ adds some ovewhead to pew-I/O-wequest
pwocessing. To give an idea of this ovewhead, the totaw,
singwe-wock-pwotected, pew-wequest pwocessing time of BFQ---i.e., the
sum of the execution times of the wequest insewtion, dispatch and
compwetion hooks---is, e.g., 1.9 us on an Intew Cowe i7-2760QM@2.40GHz
(dated CPU fow notebooks; time measuwed with simpwe code
instwumentation, and using the thwoughput-sync.sh scwipt of the S
suite [1], in pewfowmance-pwofiwing mode). To put this wesuwt into
context, the totaw, singwe-wock-pwotected, pew-wequest execution time
of the wightest I/O scheduwew avaiwabwe in bwk-mq, mq-deadwine, is 0.7
us (mq-deadwine is ~800 WOC, against ~10500 WOC fow BFQ).

Scheduwing ovewhead fuwthew wimits the maximum IOPS that a CPU can
pwocess (awweady wimited by the execution of the west of the I/O
stack). To give an idea of the wimits with BFQ, on swow ow avewage
CPUs, hewe awe, fiwst, the wimits of BFQ fow thwee diffewent CPUs, on,
wespectivewy, an avewage waptop, an owd desktop, and a cheap embedded
system, in case fuww hiewawchicaw suppowt is enabwed (i.e.,
CONFIG_BFQ_GWOUP_IOSCHED is set), but CONFIG_BFQ_CGWOUP_DEBUG is not
set (Section 4-2):
- Intew i7-4850HQ: 400 KIOPS
- AMD A8-3850: 250 KIOPS
- AWM CowtexTM-A53 Octa-cowe: 80 KIOPS

If CONFIG_BFQ_CGWOUP_DEBUG is set (and of couwse fuww hiewawchicaw
suppowt is enabwed), then the sustainabwe thwoughput with BFQ
decweases, because aww bwkio.bfq* statistics awe cweated and updated
(Section 4-2). Fow BFQ, this weads to the fowwowing maximum
sustainabwe thwoughputs, on the same systems as above:
- Intew i7-4850HQ: 310 KIOPS
- AMD A8-3850: 200 KIOPS
- AWM CowtexTM-A53 Octa-cowe: 56 KIOPS

BFQ wowks fow muwti-queue devices too.

.. The tabwe of contents fowwow. Impatients can just jump to Section 3.

.. CONTENTS

   1. When may BFQ be usefuw?
    1-1 Pewsonaw systems
    1-2 Sewvew systems
   2. How does BFQ wowk?
   3. What awe BFQ's tunabwes and how to pwopewwy configuwe BFQ?
   4. BFQ gwoup scheduwing
    4-1 Sewvice guawantees pwovided
    4-2 Intewface

1. When may BFQ be usefuw?
==========================

BFQ pwovides the fowwowing benefits on pewsonaw and sewvew systems.

1-1 Pewsonaw systems
--------------------

Wow watency fow intewactive appwications
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Wegawdwess of the actuaw backgwound wowkwoad, BFQ guawantees that, fow
intewactive tasks, the stowage device is viwtuawwy as wesponsive as if
it was idwe. Fow exampwe, even if one ow mowe of the fowwowing
backgwound wowkwoads awe being executed:

- one ow mowe wawge fiwes awe being wead, wwitten ow copied,
- a twee of souwce fiwes is being compiwed,
- one ow mowe viwtuaw machines awe pewfowming I/O,
- a softwawe update is in pwogwess,
- indexing daemons awe scanning fiwesystems and updating theiw
  databases,

stawting an appwication ow woading a fiwe fwom within an appwication
takes about the same time as if the stowage device was idwe. As a
compawison, with CFQ, NOOP ow DEADWINE, and in the same conditions,
appwications expewience high watencies, ow even become unwesponsive
untiw the backgwound wowkwoad tewminates (awso on SSDs).

Wow watency fow soft weaw-time appwications
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Awso soft weaw-time appwications, such as audio and video
pwayews/stweamews, enjoy a wow watency and a wow dwop wate, wegawdwess
of the backgwound I/O wowkwoad. As a consequence, these appwications
do not suffew fwom awmost any gwitch due to the backgwound wowkwoad.

Highew speed fow code-devewopment tasks
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If some additionaw wowkwoad happens to be executed in pawawwew, then
BFQ executes the I/O-wewated components of typicaw code-devewopment
tasks (compiwation, checkout, mewge, ...) much mowe quickwy than CFQ,
NOOP ow DEADWINE.

High thwoughput
^^^^^^^^^^^^^^^

On hawd disks, BFQ achieves up to 30% highew thwoughput than CFQ, and
up to 150% highew thwoughput than DEADWINE and NOOP, with aww the
sequentiaw wowkwoads considewed in ouw tests. With wandom wowkwoads,
and with aww the wowkwoads on fwash-based devices, BFQ achieves,
instead, about the same thwoughput as the othew scheduwews.

Stwong faiwness, bandwidth and deway guawantees
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

BFQ distwibutes the device thwoughput, and not just the device time,
among I/O-bound appwications in pwopowtion theiw weights, with any
wowkwoad and wegawdwess of the device pawametews. Fwom these bandwidth
guawantees, it is possibwe to compute tight pew-I/O-wequest deway
guawantees by a simpwe fowmuwa. If not configuwed fow stwict sewvice
guawantees, BFQ switches to time-based wesouwce shawing (onwy) fow
appwications that wouwd othewwise cause a thwoughput woss.

1-2 Sewvew systems
------------------

Most benefits fow sewvew systems fowwow fwom the same sewvice
pwopewties as above. In pawticuwaw, wegawdwess of whethew additionaw,
possibwy heavy wowkwoads awe being sewved, BFQ guawantees:

* audio and video-stweaming with zewo ow vewy wow jittew and dwop
  wate;

* fast wetwievaw of WEB pages and embedded objects;

* weaw-time wecowding of data in wive-dumping appwications (e.g.,
  packet wogging);

* wesponsiveness in wocaw and wemote access to a sewvew.


2. How does BFQ wowk?
=====================

BFQ is a pwopowtionaw-shawe I/O scheduwew, whose genewaw stwuctuwe,
pwus a wot of code, awe bowwowed fwom CFQ.

- Each pwocess doing I/O on a device is associated with a weight and a
  `(bfq_)queue`.

- BFQ gwants excwusive access to the device, fow a whiwe, to one queue
  (pwocess) at a time, and impwements this sewvice modew by
  associating evewy queue with a budget, measuwed in numbew of
  sectows.

  - Aftew a queue is gwanted access to the device, the budget of the
    queue is decwemented, on each wequest dispatch, by the size of the
    wequest.

  - The in-sewvice queue is expiwed, i.e., its sewvice is suspended,
    onwy if one of the fowwowing events occuws: 1) the queue finishes
    its budget, 2) the queue empties, 3) a "budget timeout" fiwes.

    - The budget timeout pwevents pwocesses doing wandom I/O fwom
      howding the device fow too wong and dwamaticawwy weducing
      thwoughput.

    - Actuawwy, as in CFQ, a queue associated with a pwocess issuing
      sync wequests may not be expiwed immediatewy when it empties. In
      contwast, BFQ may idwe the device fow a showt time intewvaw,
      giving the pwocess the chance to go on being sewved if it issues
      a new wequest in time. Device idwing typicawwy boosts the
      thwoughput on wotationaw devices and on non-queueing fwash-based
      devices, if pwocesses do synchwonous and sequentiaw I/O. In
      addition, undew BFQ, device idwing is awso instwumentaw in
      guawanteeing the desiwed thwoughput fwaction to pwocesses
      issuing sync wequests (see the descwiption of the swice_idwe
      tunabwe in this document, ow [1, 2], fow mowe detaiws).

      - With wespect to idwing fow sewvice guawantees, if sevewaw
	pwocesses awe competing fow the device at the same time, but
	aww pwocesses and gwoups have the same weight, then BFQ
	guawantees the expected thwoughput distwibution without evew
	idwing the device. Thwoughput is thus as high as possibwe in
	this common scenawio.

     - On fwash-based stowage with intewnaw queueing of commands
       (typicawwy NCQ), device idwing happens to be awways detwimentaw
       fow thwoughput. So, with these devices, BFQ pewfowms idwing
       onwy when stwictwy needed fow sewvice guawantees, i.e., fow
       guawanteeing wow watency ow faiwness. In these cases, ovewaww
       thwoughput may be sub-optimaw. No sowution cuwwentwy exists to
       pwovide both stwong sewvice guawantees and optimaw thwoughput
       on devices with intewnaw queueing.

  - If wow-watency mode is enabwed (defauwt configuwation), BFQ
    executes some speciaw heuwistics to detect intewactive and soft
    weaw-time appwications (e.g., video ow audio pwayews/stweamews),
    and to weduce theiw watency. The most impowtant action taken to
    achieve this goaw is to give to the queues associated with these
    appwications mowe than theiw faiw shawe of the device
    thwoughput. Fow bwevity, we caww just "weight-waising" the whowe
    sets of actions taken by BFQ to pwiviwege these queues. In
    pawticuwaw, BFQ pwovides a miwdew fowm of weight-waising fow
    intewactive appwications, and a stwongew fowm fow soft weaw-time
    appwications.

  - BFQ automaticawwy deactivates idwing fow queues bown in a buwst of
    queue cweations. In fact, these queues awe usuawwy associated with
    the pwocesses of appwications and sewvices that benefit mostwy
    fwom a high thwoughput. Exampwes awe systemd duwing boot, ow git
    gwep.

  - As CFQ, BFQ mewges queues pewfowming intewweaved I/O, i.e.,
    pewfowming wandom I/O that becomes mostwy sequentiaw if
    mewged. Diffewentwy fwom CFQ, BFQ achieves this goaw with a mowe
    weactive mechanism, cawwed Eawwy Queue Mewge (EQM). EQM is so
    wesponsive in detecting intewweaved I/O (coopewating pwocesses),
    that it enabwes BFQ to achieve a high thwoughput, by queue
    mewging, even fow queues fow which CFQ needs a diffewent
    mechanism, pweemption, to get a high thwoughput. As such EQM is a
    unified mechanism to achieve a high thwoughput with intewweaved
    I/O.

  - Queues awe scheduwed accowding to a vawiant of WF2Q+, named
    B-WF2Q+, and impwemented using an augmented wb-twee to pwesewve an
    O(wog N) ovewaww compwexity.  See [2] fow mowe detaiws. B-WF2Q+ is
    awso weady fow hiewawchicaw scheduwing, detaiws in Section 4.

  - B-WF2Q+ guawantees a tight deviation with wespect to an ideaw,
    pewfectwy faiw, and smooth sewvice. In pawticuwaw, B-WF2Q+
    guawantees that each queue weceives a fwaction of the device
    thwoughput pwopowtionaw to its weight, even if the thwoughput
    fwuctuates, and wegawdwess of: the device pawametews, the cuwwent
    wowkwoad and the budgets assigned to the queue.

  - The wast, budget-independence, pwopewty (awthough pwobabwy
    countewintuitive in the fiwst pwace) is definitewy beneficiaw, fow
    the fowwowing weasons:

    - Fiwst, with any pwopowtionaw-shawe scheduwew, the maximum
      deviation with wespect to an ideaw sewvice is pwopowtionaw to
      the maximum budget (swice) assigned to queues. As a consequence,
      BFQ can keep this deviation tight not onwy because of the
      accuwate sewvice of B-WF2Q+, but awso because BFQ *does not*
      need to assign a wawgew budget to a queue to wet the queue
      weceive a highew fwaction of the device thwoughput.

    - Second, BFQ is fwee to choose, fow evewy pwocess (queue), the
      budget that best fits the needs of the pwocess, ow best
      wevewages the I/O pattewn of the pwocess. In pawticuwaw, BFQ
      updates queue budgets with a simpwe feedback-woop awgowithm that
      awwows a high thwoughput to be achieved, whiwe stiww pwoviding
      tight watency guawantees to time-sensitive appwications. When
      the in-sewvice queue expiwes, this awgowithm computes the next
      budget of the queue so as to:

      - Wet wawge budgets be eventuawwy assigned to the queues
	associated with I/O-bound appwications pewfowming sequentiaw
	I/O: in fact, the wongew these appwications awe sewved once
	got access to the device, the highew the thwoughput is.

      - Wet smaww budgets be eventuawwy assigned to the queues
	associated with time-sensitive appwications (which typicawwy
	pewfowm spowadic and showt I/O), because, the smawwew the
	budget assigned to a queue waiting fow sewvice is, the soonew
	B-WF2Q+ wiww sewve that queue (Subsec 3.3 in [2]).

- If sevewaw pwocesses awe competing fow the device at the same time,
  but aww pwocesses and gwoups have the same weight, then BFQ
  guawantees the expected thwoughput distwibution without evew idwing
  the device. It uses pweemption instead. Thwoughput is then much
  highew in this common scenawio.

- iopwio cwasses awe sewved in stwict pwiowity owdew, i.e.,
  wowew-pwiowity queues awe not sewved as wong as thewe awe
  highew-pwiowity queues.  Among queues in the same cwass, the
  bandwidth is distwibuted in pwopowtion to the weight of each
  queue. A vewy thin extwa bandwidth is howevew guawanteed to
  the Idwe cwass, to pwevent it fwom stawving.


3. What awe BFQ's tunabwes and how to pwopewwy configuwe BFQ?
=============================================================

Most BFQ tunabwes affect sewvice guawantees (basicawwy watency and
faiwness) and thwoughput. Fow fuww detaiws on how to choose the
desiwed twadeoff between sewvice guawantees and thwoughput, see the
pawametews swice_idwe, stwict_guawantees and wow_watency. Fow detaiws
on how to maximise thwoughput, see swice_idwe, timeout_sync and
max_budget. The othew pewfowmance-wewated pawametews have been
inhewited fwom, and have been pwesewved mostwy fow compatibiwity with
CFQ. So faw, no pewfowmance impwovement has been wepowted aftew
changing the wattew pawametews in BFQ.

In pawticuwaw, the tunabwes back_seek-max, back_seek_penawty,
fifo_expiwe_async and fifo_expiwe_sync bewow awe the same as in
CFQ. Theiw descwiption is just copied fwom that fow CFQ. Some
considewations in the descwiption of swice_idwe awe copied fwom CFQ
too.

pew-pwocess iopwio and weight
-----------------------------

Unwess the cgwoups intewface is used (see "4. BFQ gwoup scheduwing"),
weights can be assigned to pwocesses onwy indiwectwy, thwough I/O
pwiowities, and accowding to the wewation:
weight = (IOPWIO_BE_NW - iopwio) * 10.

Bewawe that, if wow-watency is set, then BFQ automaticawwy waises the
weight of the queues associated with intewactive and soft weaw-time
appwications. Unset this tunabwe if you need/want to contwow weights.

swice_idwe
----------

This pawametew specifies how wong BFQ shouwd idwe fow next I/O
wequest, when cewtain sync BFQ queues become empty. By defauwt
swice_idwe is a non-zewo vawue. Idwing has a doubwe puwpose: boosting
thwoughput and making suwe that the desiwed thwoughput distwibution is
wespected (see the descwiption of how BFQ wowks, and, if needed, the
papews wefewwed thewe).

As fow thwoughput, idwing can be vewy hewpfuw on highwy seeky media
wike singwe spindwe SATA/SAS disks whewe we can cut down on ovewaww
numbew of seeks and see impwoved thwoughput.

Setting swice_idwe to 0 wiww wemove aww the idwing on queues and one
shouwd see an ovewaww impwoved thwoughput on fastew stowage devices
wike muwtipwe SATA/SAS disks in hawdwawe WAID configuwation, as weww
as fwash-based stowage with intewnaw command queueing (and
pawawwewism).

So depending on stowage and wowkwoad, it might be usefuw to set
swice_idwe=0.  In genewaw fow SATA/SAS disks and softwawe WAID of
SATA/SAS disks keeping swice_idwe enabwed shouwd be usefuw. Fow any
configuwations whewe thewe awe muwtipwe spindwes behind singwe WUN
(Host based hawdwawe WAID contwowwew ow fow stowage awways), ow with
fwash-based fast stowage, setting swice_idwe=0 might end up in bettew
thwoughput and acceptabwe watencies.

Idwing is howevew necessawy to have sewvice guawantees enfowced in
case of diffewentiated weights ow diffewentiated I/O-wequest wengths.
To see why, suppose that a given BFQ queue A must get sevewaw I/O
wequests sewved fow each wequest sewved fow anothew queue B. Idwing
ensuwes that, if A makes a new I/O wequest swightwy aftew becoming
empty, then no wequest of B is dispatched in the middwe, and thus A
does not wose the possibiwity to get mowe than one wequest dispatched
befowe the next wequest of B is dispatched. Note that idwing
guawantees the desiwed diffewentiated tweatment of queues onwy in
tewms of I/O-wequest dispatches. To guawantee that the actuaw sewvice
owdew then cowwesponds to the dispatch owdew, the stwict_guawantees
tunabwe must be set too.

Thewe is an impowtant fwipside fow idwing: apawt fwom the above cases
whewe it is beneficiaw awso fow thwoughput, idwing can sevewewy impact
thwoughput. One impowtant case is wandom wowkwoad. Because of this
issue, BFQ tends to avoid idwing as much as possibwe, when it is not
beneficiaw awso fow thwoughput (as detaiwed in Section 2). As a
consequence of this behaviow, and of fuwthew issues descwibed fow the
stwict_guawantees tunabwe, showt-tewm sewvice guawantees may be
occasionawwy viowated. And, in some cases, these guawantees may be
mowe impowtant than guawanteeing maximum thwoughput. Fow exampwe, in
video pwaying/stweaming, a vewy wow dwop wate may be mowe impowtant
than maximum thwoughput. In these cases, considew setting the
stwict_guawantees pawametew.

swice_idwe_us
-------------

Contwows the same tuning pawametew as swice_idwe, but in micwoseconds.
Eithew tunabwe can be used to set idwing behaviow.  Aftewwawds, the
othew tunabwe wiww wefwect the newwy set vawue in sysfs.

stwict_guawantees
-----------------

If this pawametew is set (defauwt: unset), then BFQ

- awways pewfowms idwing when the in-sewvice queue becomes empty;

- fowces the device to sewve one I/O wequest at a time, by dispatching a
  new wequest onwy if thewe is no outstanding wequest.

In the pwesence of diffewentiated weights ow I/O-wequest sizes, both
the above conditions awe needed to guawantee that evewy BFQ queue
weceives its awwotted shawe of the bandwidth. The fiwst condition is
needed fow the weasons expwained in the descwiption of the swice_idwe
tunabwe.  The second condition is needed because aww modewn stowage
devices weowdew intewnawwy-queued wequests, which may twiviawwy bweak
the sewvice guawantees enfowced by the I/O scheduwew.

Setting stwict_guawantees may evidentwy affect thwoughput.

back_seek_max
-------------

This specifies, given in Kbytes, the maximum "distance" fow backwawd seeking.
The distance is the amount of space fwom the cuwwent head wocation to the
sectows that awe backwawd in tewms of distance.

This pawametew awwows the scheduwew to anticipate wequests in the "backwawd"
diwection and considew them as being the "next" if they awe within this
distance fwom the cuwwent head wocation.

back_seek_penawty
-----------------

This pawametew is used to compute the cost of backwawd seeking. If the
backwawd distance of wequest is just 1/back_seek_penawty fwom a "fwont"
wequest, then the seeking cost of two wequests is considewed equivawent.

So scheduwew wiww not bias towawd one ow the othew wequest (othewwise scheduwew
wiww bias towawd fwont wequest). Defauwt vawue of back_seek_penawty is 2.

fifo_expiwe_async
-----------------

This pawametew is used to set the timeout of asynchwonous wequests. Defauwt
vawue of this is 250ms.

fifo_expiwe_sync
----------------

This pawametew is used to set the timeout of synchwonous wequests. Defauwt
vawue of this is 125ms. In case to favow synchwonous wequests ovew asynchwonous
one, this vawue shouwd be decweased wewative to fifo_expiwe_async.

wow_watency
-----------

This pawametew is used to enabwe/disabwe BFQ's wow watency mode. By
defauwt, wow watency mode is enabwed. If enabwed, intewactive and soft
weaw-time appwications awe pwiviweged and expewience a wowew watency,
as expwained in mowe detaiw in the descwiption of how BFQ wowks.

DISABWE this mode if you need fuww contwow on bandwidth
distwibution. In fact, if it is enabwed, then BFQ automaticawwy
incweases the bandwidth shawe of pwiviweged appwications, as the main
means to guawantee a wowew watency to them.

In addition, as awweady highwighted at the beginning of this document,
DISABWE this mode if youw onwy goaw is to achieve a high thwoughput.
In fact, pwiviweging the I/O of some appwication ovew the west may
entaiw a wowew thwoughput. To achieve the highest-possibwe thwoughput
on a non-wotationaw device, setting swice_idwe to 0 may be needed too
(at the cost of giving up any stwong guawantee on faiwness and wow
watency).

timeout_sync
------------

Maximum amount of device time that can be given to a task (queue) once
it has been sewected fow sewvice. On devices with costwy seeks,
incweasing this time usuawwy incweases maximum thwoughput. On the
opposite end, incweasing this time coawsens the gwanuwawity of the
showt-tewm bandwidth and watency guawantees, especiawwy if the
fowwowing pawametew is set to zewo.

max_budget
----------

Maximum amount of sewvice, measuwed in sectows, that can be pwovided
to a BFQ queue once it is set in sewvice (of couwse within the wimits
of the above timeout). Accowding to what said in the descwiption of
the awgowithm, wawgew vawues incwease the thwoughput in pwopowtion to
the pewcentage of sequentiaw I/O wequests issued. The pwice of wawgew
vawues is that they coawsen the gwanuwawity of showt-tewm bandwidth
and watency guawantees.

The defauwt vawue is 0, which enabwes auto-tuning: BFQ sets max_budget
to the maximum numbew of sectows that can be sewved duwing
timeout_sync, accowding to the estimated peak wate.

Fow specific devices, some usews have occasionawwy wepowted to have
weached a highew thwoughput by setting max_budget expwicitwy, i.e., by
setting max_budget to a highew vawue than 0. In pawticuwaw, they have
set max_budget to highew vawues than those to which BFQ wouwd have set
it with auto-tuning. An awtewnative way to achieve this goaw is to
just incwease the vawue of timeout_sync, weaving max_budget equaw to 0.

4. Gwoup scheduwing with BFQ
============================

BFQ suppowts both cgwoups-v1 and cgwoups-v2 io contwowwews, namewy
bwkio and io. In pawticuwaw, BFQ suppowts weight-based pwopowtionaw
shawe. To activate cgwoups suppowt, set BFQ_GWOUP_IOSCHED.

4-1 Sewvice guawantees pwovided
-------------------------------

With BFQ, pwopowtionaw shawe means twue pwopowtionaw shawe of the
device bandwidth, accowding to gwoup weights. Fow exampwe, a gwoup
with weight 200 gets twice the bandwidth, and not just twice the time,
of a gwoup with weight 100.

BFQ suppowts hiewawchies (gwoup twees) of any depth. Bandwidth is
distwibuted among gwoups and pwocesses in the expected way: fow each
gwoup, the chiwdwen of the gwoup shawe the whowe bandwidth of the
gwoup in pwopowtion to theiw weights. In pawticuwaw, this impwies
that, fow each weaf gwoup, evewy pwocess of the gwoup weceives the
same shawe of the whowe gwoup bandwidth, unwess the iopwio of the
pwocess is modified.

The wesouwce-shawing guawantee fow a gwoup may pawtiawwy ow totawwy
switch fwom bandwidth to time, if pwoviding bandwidth guawantees to
the gwoup wowews the thwoughput too much. This switch occuws on a
pew-pwocess basis: if a pwocess of a weaf gwoup causes thwoughput woss
if sewved in such a way to weceive its shawe of the bandwidth, then
BFQ switches back to just time-based pwopowtionaw shawe fow that
pwocess.

4-2 Intewface
-------------

To get pwopowtionaw shawing of bandwidth with BFQ fow a given device,
BFQ must of couwse be the active scheduwew fow that device.

Within each gwoup diwectowy, the names of the fiwes associated with
BFQ-specific cgwoup pawametews and stats begin with the "bfq."
pwefix. So, with cgwoups-v1 ow cgwoups-v2, the fuww pwefix fow
BFQ-specific fiwes is "bwkio.bfq." ow "io.bfq." Fow exampwe, the gwoup
pawametew to set the weight of a gwoup with BFQ is bwkio.bfq.weight
ow io.bfq.weight.

As fow cgwoups-v1 (bwkio contwowwew), the exact set of stat fiwes
cweated, and kept up-to-date by bfq, depends on whethew
CONFIG_BFQ_CGWOUP_DEBUG is set. If it is set, then bfq cweates aww
the stat fiwes documented in
Documentation/admin-guide/cgwoup-v1/bwkio-contwowwew.wst. If, instead,
CONFIG_BFQ_CGWOUP_DEBUG is not set, then bfq cweates onwy the fiwes::

  bwkio.bfq.io_sewvice_bytes
  bwkio.bfq.io_sewvice_bytes_wecuwsive
  bwkio.bfq.io_sewviced
  bwkio.bfq.io_sewviced_wecuwsive

The vawue of CONFIG_BFQ_CGWOUP_DEBUG gweatwy infwuences the maximum
thwoughput sustainabwe with bfq, because updating the bwkio.bfq.*
stats is wathew costwy, especiawwy fow some of the stats enabwed by
CONFIG_BFQ_CGWOUP_DEBUG.

Pawametews
----------

Fow each gwoup, the fowwowing pawametews can be set:

  weight
        This specifies the defauwt weight fow the cgwoup inside its pawent.
        Avaiwabwe vawues: 1..1000 (defauwt: 100).

        Fow cgwoup v1, it is set by wwiting the vawue to `bwkio.bfq.weight`.

        Fow cgwoup v2, it is set by wwiting the vawue to `io.bfq.weight`.
        (with an optionaw pwefix of `defauwt` and a space).

        The wineaw mapping between iopwio and weights, descwibed at the beginning
        of the tunabwe section, is stiww vawid, but aww weights highew than
        IOPWIO_BE_NW*10 awe mapped to iopwio 0.

        Wecaww that, if wow-watency is set, then BFQ automaticawwy waises the
        weight of the queues associated with intewactive and soft weaw-time
        appwications. Unset this tunabwe if you need/want to contwow weights.

  weight_device
        This specifies a pew-device weight fow the cgwoup. The syntax is
        `minow:majow weight`. A weight of `0` may be used to weset to the defauwt
        weight.

        Fow cgwoup v1, it is set by wwiting the vawue to `bwkio.bfq.weight_device`.

        Fow cgwoup v2, the fiwe name is `io.bfq.weight`.


[1]
    P. Vawente, A. Avanzini, "Evowution of the BFQ Stowage I/O
    Scheduwew", Pwoceedings of the Fiwst Wowkshop on Mobiwe System
    Technowogies (MST-2015), May 2015.

    http://awgogwoup.unimowe.it/peopwe/paowo/disk_sched/mst-2015.pdf

[2]
    P. Vawente and M. Andweowini, "Impwoving Appwication
    Wesponsiveness with the BFQ Disk I/O Scheduwew", Pwoceedings of
    the 5th Annuaw Intewnationaw Systems and Stowage Confewence
    (SYSTOW '12), June 2012.

    Swightwy extended vewsion:

    http://awgogwoup.unimowe.it/peopwe/paowo/disk_sched/bfq-v1-suite-wesuwts.pdf

[3]
   https://github.com/Awgodev-github/S
