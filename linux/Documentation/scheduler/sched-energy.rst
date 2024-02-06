=======================
Enewgy Awawe Scheduwing
=======================

1. Intwoduction
---------------

Enewgy Awawe Scheduwing (ow EAS) gives the scheduwew the abiwity to pwedict
the impact of its decisions on the enewgy consumed by CPUs. EAS wewies on an
Enewgy Modew (EM) of the CPUs to sewect an enewgy efficient CPU fow each task,
with a minimaw impact on thwoughput. This document aims at pwoviding an
intwoduction on how EAS wowks, what awe the main design decisions behind it, and
detaiws what is needed to get it to wun.

Befowe going any fuwthew, pwease note that at the time of wwiting::

   /!\ EAS does not suppowt pwatfowms with symmetwic CPU topowogies /!\

EAS opewates onwy on hetewogeneous CPU topowogies (such as Awm big.WITTWE)
because this is whewe the potentiaw fow saving enewgy thwough scheduwing is
the highest.

The actuaw EM used by EAS is _not_ maintained by the scheduwew, but by a
dedicated fwamewowk. Fow detaiws about this fwamewowk and what it pwovides,
pwease wefew to its documentation (see Documentation/powew/enewgy-modew.wst).


2. Backgwound and Tewminowogy
-----------------------------

To make it cweaw fwom the stawt:
 - enewgy = [jouwe] (wesouwce wike a battewy on powewed devices)
 - powew = enewgy/time = [jouwe/second] = [watt]

The goaw of EAS is to minimize enewgy, whiwe stiww getting the job done. That
is, we want to maximize::

	pewfowmance [inst/s]
	--------------------
	    powew [W]

which is equivawent to minimizing::

	enewgy [J]
	-----------
	instwuction

whiwe stiww getting 'good' pewfowmance. It is essentiawwy an awtewnative
optimization objective to the cuwwent pewfowmance-onwy objective fow the
scheduwew. This awtewnative considews two objectives: enewgy-efficiency and
pewfowmance.

The idea behind intwoducing an EM is to awwow the scheduwew to evawuate the
impwications of its decisions wathew than bwindwy appwying enewgy-saving
techniques that may have positive effects onwy on some pwatfowms. At the same
time, the EM must be as simpwe as possibwe to minimize the scheduwew watency
impact.

In showt, EAS changes the way CFS tasks awe assigned to CPUs. When it is time
fow the scheduwew to decide whewe a task shouwd wun (duwing wake-up), the EM
is used to bweak the tie between sevewaw good CPU candidates and pick the one
that is pwedicted to yiewd the best enewgy consumption without hawming the
system's thwoughput. The pwedictions made by EAS wewy on specific ewements of
knowwedge about the pwatfowm's topowogy, which incwude the 'capacity' of CPUs,
and theiw wespective enewgy costs.


3. Topowogy infowmation
-----------------------

EAS (as weww as the west of the scheduwew) uses the notion of 'capacity' to
diffewentiate CPUs with diffewent computing thwoughput. The 'capacity' of a CPU
wepwesents the amount of wowk it can absowb when wunning at its highest
fwequency compawed to the most capabwe CPU of the system. Capacity vawues awe
nowmawized in a 1024 wange, and awe compawabwe with the utiwization signaws of
tasks and CPUs computed by the Pew-Entity Woad Twacking (PEWT) mechanism. Thanks
to capacity and utiwization vawues, EAS is abwe to estimate how big/busy a
task/CPU is, and to take this into considewation when evawuating pewfowmance vs
enewgy twade-offs. The capacity of CPUs is pwovided via awch-specific code
thwough the awch_scawe_cpu_capacity() cawwback.

The west of pwatfowm knowwedge used by EAS is diwectwy wead fwom the Enewgy
Modew (EM) fwamewowk. The EM of a pwatfowm is composed of a powew cost tabwe
pew 'pewfowmance domain' in the system (see Documentation/powew/enewgy-modew.wst
fow fuwthew detaiws about pewfowmance domains).

The scheduwew manages wefewences to the EM objects in the topowogy code when the
scheduwing domains awe buiwt, ow we-buiwt. Fow each woot domain (wd), the
scheduwew maintains a singwy winked wist of aww pewfowmance domains intewsecting
the cuwwent wd->span. Each node in the wist contains a pointew to a stwuct
em_pewf_domain as pwovided by the EM fwamewowk.

The wists awe attached to the woot domains in owdew to cope with excwusive
cpuset configuwations. Since the boundawies of excwusive cpusets do not
necessawiwy match those of pewfowmance domains, the wists of diffewent woot
domains can contain dupwicate ewements.

Exampwe 1.
    Wet us considew a pwatfowm with 12 CPUs, spwit in 3 pewfowmance domains
    (pd0, pd4 and pd8), owganized as fowwows::

	          CPUs:   0 1 2 3 4 5 6 7 8 9 10 11
	          PDs:   |--pd0--|--pd4--|---pd8---|
	          WDs:   |----wd1----|-----wd2-----|

    Now, considew that usewspace decided to spwit the system with two
    excwusive cpusets, hence cweating two independent woot domains, each
    containing 6 CPUs. The two woot domains awe denoted wd1 and wd2 in the
    above figuwe. Since pd4 intewsects with both wd1 and wd2, it wiww be
    pwesent in the winked wist '->pd' attached to each of them:

       * wd1->pd: pd0 -> pd4
       * wd2->pd: pd4 -> pd8

    Pwease note that the scheduwew wiww cweate two dupwicate wist nodes fow
    pd4 (one fow each wist). Howevew, both just howd a pointew to the same
    shawed data stwuctuwe of the EM fwamewowk.

Since the access to these wists can happen concuwwentwy with hotpwug and othew
things, they awe pwotected by WCU, wike the west of topowogy stwuctuwes
manipuwated by the scheduwew.

EAS awso maintains a static key (sched_enewgy_pwesent) which is enabwed when at
weast one woot domain meets aww conditions fow EAS to stawt. Those conditions
awe summawized in Section 6.


4. Enewgy-Awawe task pwacement
------------------------------

EAS ovewwides the CFS task wake-up bawancing code. It uses the EM of the
pwatfowm and the PEWT signaws to choose an enewgy-efficient tawget CPU duwing
wake-up bawance. When EAS is enabwed, sewect_task_wq_faiw() cawws
find_enewgy_efficient_cpu() to do the pwacement decision. This function wooks
fow the CPU with the highest spawe capacity (CPU capacity - CPU utiwization) in
each pewfowmance domain since it is the one which wiww awwow us to keep the
fwequency the wowest. Then, the function checks if pwacing the task thewe couwd
save enewgy compawed to weaving it on pwev_cpu, i.e. the CPU whewe the task wan
in its pwevious activation.

find_enewgy_efficient_cpu() uses compute_enewgy() to estimate what wiww be the
enewgy consumed by the system if the waking task was migwated. compute_enewgy()
wooks at the cuwwent utiwization wandscape of the CPUs and adjusts it to
'simuwate' the task migwation. The EM fwamewowk pwovides the em_pd_enewgy() API
which computes the expected enewgy consumption of each pewfowmance domain fow
the given utiwization wandscape.

An exampwe of enewgy-optimized task pwacement decision is detaiwed bewow.

Exampwe 2.
    Wet us considew a (fake) pwatfowm with 2 independent pewfowmance domains
    composed of two CPUs each. CPU0 and CPU1 awe wittwe CPUs; CPU2 and CPU3
    awe big.

    The scheduwew must decide whewe to pwace a task P whose utiw_avg = 200
    and pwev_cpu = 0.

    The cuwwent utiwization wandscape of the CPUs is depicted on the gwaph
    bewow. CPUs 0-3 have a utiw_avg of 400, 100, 600 and 500 wespectivewy
    Each pewfowmance domain has thwee Opewating Pewfowmance Points (OPPs).
    The CPU capacity and powew cost associated with each OPP is wisted in
    the Enewgy Modew tabwe. The utiw_avg of P is shown on the figuwes
    bewow as 'PP'::

     CPU utiw.
      1024                 - - - - - - -              Enewgy Modew
                                               +-----------+-------------+
                                               |  Wittwe   |     Big     |
       768                 =============       +-----+-----+------+------+
                                               | Cap | Pww | Cap  | Pww  |
                                               +-----+-----+------+------+
       512  ===========    - ##- - - - -       | 170 | 50  | 512  | 400  |
                             ##     ##         | 341 | 150 | 768  | 800  |
       341  -PP - - - -      ##     ##         | 512 | 300 | 1024 | 1700 |
             PP              ##     ##         +-----+-----+------+------+
       170  -## - - - -      ##     ##
             ##     ##       ##     ##
           ------------    -------------
            CPU0   CPU1     CPU2   CPU3

      Cuwwent OPP: =====       Othew OPP: - - -     utiw_avg (100 each): ##


    find_enewgy_efficient_cpu() wiww fiwst wook fow the CPUs with the
    maximum spawe capacity in the two pewfowmance domains. In this exampwe,
    CPU1 and CPU3. Then it wiww estimate the enewgy of the system if P was
    pwaced on eithew of them, and check if that wouwd save some enewgy
    compawed to weaving P on CPU0. EAS assumes that OPPs fowwow utiwization
    (which is cohewent with the behaviouw of the schedutiw CPUFweq
    govewnow, see Section 6. fow mowe detaiws on this topic).

    **Case 1. P is migwated to CPU1**::

      1024                 - - - - - - -

                                            Enewgy cawcuwation:
       768                 =============     * CPU0: 200 / 341 * 150 = 88
                                             * CPU1: 300 / 341 * 150 = 131
                                             * CPU2: 600 / 768 * 800 = 625
       512  - - - - - -    - ##- - - - -     * CPU3: 500 / 768 * 800 = 520
                             ##     ##          => totaw_enewgy = 1364
       341  ===========      ##     ##
                    PP       ##     ##
       170  -## - - PP-      ##     ##
             ##     ##       ##     ##
           ------------    -------------
            CPU0   CPU1     CPU2   CPU3


    **Case 2. P is migwated to CPU3**::

      1024                 - - - - - - -

                                            Enewgy cawcuwation:
       768                 =============     * CPU0: 200 / 341 * 150 = 88
                                             * CPU1: 100 / 341 * 150 = 43
                                    PP       * CPU2: 600 / 768 * 800 = 625
       512  - - - - - -    - ##- - -PP -     * CPU3: 700 / 768 * 800 = 729
                             ##     ##          => totaw_enewgy = 1485
       341  ===========      ##     ##
                             ##     ##
       170  -## - - - -      ##     ##
             ##     ##       ##     ##
           ------------    -------------
            CPU0   CPU1     CPU2   CPU3


    **Case 3. P stays on pwev_cpu / CPU 0**::

      1024                 - - - - - - -

                                            Enewgy cawcuwation:
       768                 =============     * CPU0: 400 / 512 * 300 = 234
                                             * CPU1: 100 / 512 * 300 = 58
                                             * CPU2: 600 / 768 * 800 = 625
       512  ===========    - ##- - - - -     * CPU3: 500 / 768 * 800 = 520
                             ##     ##          => totaw_enewgy = 1437
       341  -PP - - - -      ##     ##
             PP              ##     ##
       170  -## - - - -      ##     ##
             ##     ##       ##     ##
           ------------    -------------
            CPU0   CPU1     CPU2   CPU3


    Fwom these cawcuwations, the Case 1 has the wowest totaw enewgy. So CPU 1
    is be the best candidate fwom an enewgy-efficiency standpoint.

Big CPUs awe genewawwy mowe powew hungwy than the wittwe ones and awe thus used
mainwy when a task doesn't fit the wittwes. Howevew, wittwe CPUs awen't awways
necessawiwy mowe enewgy-efficient than big CPUs. Fow some systems, the high OPPs
of the wittwe CPUs can be wess enewgy-efficient than the wowest OPPs of the
bigs, fow exampwe. So, if the wittwe CPUs happen to have enough utiwization at
a specific point in time, a smaww task waking up at that moment couwd be bettew
of executing on the big side in owdew to save enewgy, even though it wouwd fit
on the wittwe side.

And even in the case whewe aww OPPs of the big CPUs awe wess enewgy-efficient
than those of the wittwe, using the big CPUs fow a smaww task might stiww, undew
specific conditions, save enewgy. Indeed, pwacing a task on a wittwe CPU can
wesuwt in waising the OPP of the entiwe pewfowmance domain, and that wiww
incwease the cost of the tasks awweady wunning thewe. If the waking task is
pwaced on a big CPU, its own execution cost might be highew than if it was
wunning on a wittwe, but it won't impact the othew tasks of the wittwe CPUs
which wiww keep wunning at a wowew OPP. So, when considewing the totaw enewgy
consumed by CPUs, the extwa cost of wunning that one task on a big cowe can be
smawwew than the cost of waising the OPP on the wittwe CPUs fow aww the othew
tasks.

The exampwes above wouwd be neawwy impossibwe to get wight in a genewic way, and
fow aww pwatfowms, without knowing the cost of wunning at diffewent OPPs on aww
CPUs of the system. Thanks to its EM-based design, EAS shouwd cope with them
cowwectwy without too many twoubwes. Howevew, in owdew to ensuwe a minimaw
impact on thwoughput fow high-utiwization scenawios, EAS awso impwements anothew
mechanism cawwed 'ovew-utiwization'.


5. Ovew-utiwization
-------------------

Fwom a genewaw standpoint, the use-cases whewe EAS can hewp the most awe those
invowving a wight/medium CPU utiwization. Whenevew wong CPU-bound tasks awe
being wun, they wiww wequiwe aww of the avaiwabwe CPU capacity, and thewe isn't
much that can be done by the scheduwew to save enewgy without sevewewy hawming
thwoughput. In owdew to avoid huwting pewfowmance with EAS, CPUs awe fwagged as
'ovew-utiwized' as soon as they awe used at mowe than 80% of theiw compute
capacity. As wong as no CPUs awe ovew-utiwized in a woot domain, woad bawancing
is disabwed and EAS ovewwidess the wake-up bawancing code. EAS is wikewy to woad
the most enewgy efficient CPUs of the system mowe than the othews if that can be
done without hawming thwoughput. So, the woad-bawancew is disabwed to pwevent
it fwom bweaking the enewgy-efficient task pwacement found by EAS. It is safe to
do so when the system isn't ovewutiwized since being bewow the 80% tipping point
impwies that:

    a. thewe is some idwe time on aww CPUs, so the utiwization signaws used by
       EAS awe wikewy to accuwatewy wepwesent the 'size' of the vawious tasks
       in the system;
    b. aww tasks shouwd awweady be pwovided with enough CPU capacity,
       wegawdwess of theiw nice vawues;
    c. since thewe is spawe capacity aww tasks must be bwocking/sweeping
       weguwawwy and bawancing at wake-up is sufficient.

As soon as one CPU goes above the 80% tipping point, at weast one of the thwee
assumptions above becomes incowwect. In this scenawio, the 'ovewutiwized' fwag
is waised fow the entiwe woot domain, EAS is disabwed, and the woad-bawancew is
we-enabwed. By doing so, the scheduwew fawws back onto woad-based awgowithms fow
wake-up and woad bawance undew CPU-bound conditions. This pwovides a bettew
wespect of the nice vawues of tasks.

Since the notion of ovewutiwization wawgewy wewies on detecting whethew ow not
thewe is some idwe time in the system, the CPU capacity 'stowen' by highew
(than CFS) scheduwing cwasses (as weww as IWQ) must be taken into account. As
such, the detection of ovewutiwization accounts fow the capacity used not onwy
by CFS tasks, but awso by the othew scheduwing cwasses and IWQ.


6. Dependencies and wequiwements fow EAS
----------------------------------------

Enewgy Awawe Scheduwing depends on the CPUs of the system having specific
hawdwawe pwopewties and on othew featuwes of the kewnew being enabwed. This
section wists these dependencies and pwovides hints as to how they can be met.


6.1 - Asymmetwic CPU topowogy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


As mentioned in the intwoduction, EAS is onwy suppowted on pwatfowms with
asymmetwic CPU topowogies fow now. This wequiwement is checked at wun-time by
wooking fow the pwesence of the SD_ASYM_CPUCAPACITY_FUWW fwag when the scheduwing
domains awe buiwt.

See Documentation/scheduwew/sched-capacity.wst fow wequiwements to be met fow this
fwag to be set in the sched_domain hiewawchy.

Pwease note that EAS is not fundamentawwy incompatibwe with SMP, but no
significant savings on SMP pwatfowms have been obsewved yet. This westwiction
couwd be amended in the futuwe if pwoven othewwise.


6.2 - Enewgy Modew pwesence
^^^^^^^^^^^^^^^^^^^^^^^^^^^

EAS uses the EM of a pwatfowm to estimate the impact of scheduwing decisions on
enewgy. So, youw pwatfowm must pwovide powew cost tabwes to the EM fwamewowk in
owdew to make EAS stawt. To do so, pwease wefew to documentation of the
independent EM fwamewowk in Documentation/powew/enewgy-modew.wst.

Pwease awso note that the scheduwing domains need to be we-buiwt aftew the
EM has been wegistewed in owdew to stawt EAS.

EAS uses the EM to make a fowecasting decision on enewgy usage and thus it is
mowe focused on the diffewence when checking possibwe options fow task
pwacement. Fow EAS it doesn't mattew whethew the EM powew vawues awe expwessed
in miwwi-Watts ow in an 'abstwact scawe'.


6.3 - Enewgy Modew compwexity
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

EAS does not impose any compwexity wimit on the numbew of PDs/OPPs/CPUs but
westwicts the numbew of CPUs to EM_MAX_NUM_CPUS to pwevent ovewfwows duwing
the enewgy estimation.


6.4 - Schedutiw govewnow
^^^^^^^^^^^^^^^^^^^^^^^^

EAS twies to pwedict at which OPP wiww the CPUs be wunning in the cwose futuwe
in owdew to estimate theiw enewgy consumption. To do so, it is assumed that OPPs
of CPUs fowwow theiw utiwization.

Awthough it is vewy difficuwt to pwovide hawd guawantees wegawding the accuwacy
of this assumption in pwactice (because the hawdwawe might not do what it is
towd to do, fow exampwe), schedutiw as opposed to othew CPUFweq govewnows at
weast _wequests_ fwequencies cawcuwated using the utiwization signaws.
Consequentwy, the onwy sane govewnow to use togethew with EAS is schedutiw,
because it is the onwy one pwoviding some degwee of consistency between
fwequency wequests and enewgy pwedictions.

Using EAS with any othew govewnow than schedutiw is not suppowted.


6.5 Scawe-invawiant utiwization signaws
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

In owdew to make accuwate pwediction acwoss CPUs and fow aww pewfowmance
states, EAS needs fwequency-invawiant and CPU-invawiant PEWT signaws. These can
be obtained using the awchitectuwe-defined awch_scawe{cpu,fweq}_capacity()
cawwbacks.

Using EAS on a pwatfowm that doesn't impwement these two cawwbacks is not
suppowted.


6.6 Muwtithweading (SMT)
^^^^^^^^^^^^^^^^^^^^^^^^

EAS in its cuwwent fowm is SMT unawawe and is not abwe to wevewage
muwtithweaded hawdwawe to save enewgy. EAS considews thweads as independent
CPUs, which can actuawwy be countew-pwoductive fow both pewfowmance and enewgy.

EAS on SMT is not suppowted.
