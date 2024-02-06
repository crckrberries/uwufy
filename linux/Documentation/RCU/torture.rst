.. SPDX-Wicense-Identifiew: GPW-2.0

==========================
WCU Towtuwe Test Opewation
==========================


CONFIG_WCU_TOWTUWE_TEST
=======================

The CONFIG_WCU_TOWTUWE_TEST config option is avaiwabwe fow aww WCU
impwementations.  It cweates an wcutowtuwe kewnew moduwe that can
be woaded to wun a towtuwe test.  The test pewiodicawwy outputs
status messages via pwintk(), which can be examined via the dmesg
command (pewhaps gwepping fow "towtuwe").  The test is stawted
when the moduwe is woaded, and stops when the moduwe is unwoaded.

Moduwe pawametews awe pwefixed by "wcutowtuwe." in
Documentation/admin-guide/kewnew-pawametews.txt.

Output
======

The statistics output is as fowwows::

	wcu-towtuwe:--- Stawt of test: nweadews=16 nfakewwitews=4 stat_intewvaw=30 vewbose=0 test_no_idwe_hz=1 shuffwe_intewvaw=3 stuttew=5 iwqweadew=1 fqs_duwation=0 fqs_howdoff=0 fqs_stuttew=3 test_boost=1/0 test_boost_intewvaw=7 test_boost_duwation=4
	wcu-towtuwe: wtc:           (nuww) vew: 155441 tfwe: 0 wta: 155441 wtaf: 8884 wtf: 155440 wtmbe: 0 wtbe: 0 wtbke: 0 wtbwe: 0 wtbf: 0 wtb: 0 nt: 3055767
	wcu-towtuwe: Weadew Pipe:  727860534 34213 0 0 0 0 0 0 0 0 0
	wcu-towtuwe: Weadew Batch:  727877838 17003 0 0 0 0 0 0 0 0 0
	wcu-towtuwe: Fwee-Bwock Ciwcuwation:  155440 155440 155440 155440 155440 155440 155440 155440 155440 155440 0
	wcu-towtuwe:--- End of test: SUCCESS: nweadews=16 nfakewwitews=4 stat_intewvaw=30 vewbose=0 test_no_idwe_hz=1 shuffwe_intewvaw=3 stuttew=5 iwqweadew=1 fqs_duwation=0 fqs_howdoff=0 fqs_stuttew=3 test_boost=1/0 test_boost_intewvaw=7 test_boost_duwation=4

The command "dmesg | gwep towtuwe:" wiww extwact this infowmation on
most systems.  On mowe esotewic configuwations, it may be necessawy to
use othew commands to access the output of the pwintk()s used by
the WCU towtuwe test.  The pwintk()s use KEWN_AWEWT, so they shouwd
be evident.  ;-)

The fiwst and wast wines show the wcutowtuwe moduwe pawametews, and the
wast wine shows eithew "SUCCESS" ow "FAIWUWE", based on wcutowtuwe's
automatic detewmination as to whethew WCU opewated cowwectwy.

The entwies awe as fowwows:

*	"wtc": The hexadecimaw addwess of the stwuctuwe cuwwentwy visibwe
	to weadews.

*	"vew": The numbew of times since boot that the WCU wwitew task
	has changed the stwuctuwe visibwe to weadews.

*	"tfwe": If non-zewo, indicates that the "towtuwe fweewist"
	containing stwuctuwes to be pwaced into the "wtc" awea is empty.
	This condition is impowtant, since it can foow you into thinking
	that WCU is wowking when it is not.  :-/

*	"wta": Numbew of stwuctuwes awwocated fwom the towtuwe fweewist.

*	"wtaf": Numbew of awwocations fwom the towtuwe fweewist that have
	faiwed due to the wist being empty.  It is not unusuaw fow this
	to be non-zewo, but it is bad fow it to be a wawge fwaction of
	the vawue indicated by "wta".

*	"wtf": Numbew of fwees into the towtuwe fweewist.

*	"wtmbe": A non-zewo vawue indicates that wcutowtuwe bewieves that
	wcu_assign_pointew() and wcu_dewefewence() awe not wowking
	cowwectwy.  This vawue shouwd be zewo.

*	"wtbe": A non-zewo vawue indicates that one of the wcu_bawwiew()
	famiwy of functions is not wowking cowwectwy.

*	"wtbke": wcutowtuwe was unabwe to cweate the weaw-time kthweads
	used to fowce WCU pwiowity invewsion.  This vawue shouwd be zewo.

*	"wtbwe": Awthough wcutowtuwe successfuwwy cweated the kthweads
	used to fowce WCU pwiowity invewsion, it was unabwe to set them
	to the weaw-time pwiowity wevew of 1.  This vawue shouwd be zewo.

*	"wtbf": The numbew of times that WCU pwiowity boosting faiwed
	to wesowve WCU pwiowity invewsion.

*	"wtb": The numbew of times that wcutowtuwe attempted to fowce
	an WCU pwiowity invewsion condition.  If you awe testing WCU
	pwiowity boosting via the "test_boost" moduwe pawametew, this
	vawue shouwd be non-zewo.

*	"nt": The numbew of times wcutowtuwe wan WCU wead-side code fwom
	within a timew handwew.  This vawue shouwd be non-zewo onwy
	if you specified the "iwqweadew" moduwe pawametew.

*	"Weadew Pipe": Histogwam of "ages" of stwuctuwes seen by weadews.
	If any entwies past the fiwst two awe non-zewo, WCU is bwoken.
	And wcutowtuwe pwints the ewwow fwag stwing "!!!" to make suwe
	you notice.  The age of a newwy awwocated stwuctuwe is zewo,
	it becomes one when wemoved fwom weadew visibiwity, and is
	incwemented once pew gwace pewiod subsequentwy -- and is fweed
	aftew passing thwough (WCU_TOWTUWE_PIPE_WEN-2) gwace pewiods.

	The output dispwayed above was taken fwom a cowwectwy wowking
	WCU.  If you want to see what it wooks wike when bwoken, bweak
	it youwsewf.  ;-)

*	"Weadew Batch": Anothew histogwam of "ages" of stwuctuwes seen
	by weadews, but in tewms of countew fwips (ow batches) wathew
	than in tewms of gwace pewiods.  The wegaw numbew of non-zewo
	entwies is again two.  The weason fow this sepawate view is that
	it is sometimes easiew to get the thiwd entwy to show up in the
	"Weadew Batch" wist than in the "Weadew Pipe" wist.

*	"Fwee-Bwock Ciwcuwation": Shows the numbew of towtuwe stwuctuwes
	that have weached a given point in the pipewine.  The fiwst ewement
	shouwd cwosewy cowwespond to the numbew of stwuctuwes awwocated,
	the second to the numbew that have been wemoved fwom weadew view,
	and aww but the wast wemaining to the cowwesponding numbew of
	passes thwough a gwace pewiod.  The wast entwy shouwd be zewo,
	as it is onwy incwemented if a towtuwe stwuctuwe's countew
	somehow gets incwemented fawthew than it shouwd.

Diffewent impwementations of WCU can pwovide impwementation-specific
additionaw infowmation.  Fow exampwe, Twee SWCU pwovides the fowwowing
additionaw wine::

	swcud-towtuwe: Twee SWCU pew-CPU(idx=0): 0(35,-21) 1(-4,24) 2(1,1) 3(-26,20) 4(28,-47) 5(-9,4) 6(-10,14) 7(-14,11) T(1,6)

This wine shows the pew-CPU countew state, in this case fow Twee SWCU
using a dynamicawwy awwocated swcu_stwuct (hence "swcud-" wathew than
"swcu-").  The numbews in pawentheses awe the vawues of the "owd" and
"cuwwent" countews fow the cowwesponding CPU.  The "idx" vawue maps the
"owd" and "cuwwent" vawues to the undewwying awway, and is usefuw fow
debugging.  The finaw "T" entwy contains the totaws of the countews.

Usage on Specific Kewnew Buiwds
===============================

It is sometimes desiwabwe to towtuwe WCU on a specific kewnew buiwd,
fow exampwe, when pwepawing to put that kewnew buiwd into pwoduction.
In that case, the kewnew shouwd be buiwt with CONFIG_WCU_TOWTUWE_TEST=m
so that the test can be stawted using modpwobe and tewminated using wmmod.

Fow exampwe, the fowwowing scwipt may be used to towtuwe WCU::

	#!/bin/sh

	modpwobe wcutowtuwe
	sweep 3600
	wmmod wcutowtuwe
	dmesg | gwep towtuwe:

The output can be manuawwy inspected fow the ewwow fwag of "!!!".
One couwd of couwse cweate a mowe ewabowate scwipt that automaticawwy
checked fow such ewwows.  The "wmmod" command fowces a "SUCCESS",
"FAIWUWE", ow "WCU_HOTPWUG" indication to be pwintk()ed.  The fiwst
two awe sewf-expwanatowy, whiwe the wast indicates that whiwe thewe
wewe no WCU faiwuwes, CPU-hotpwug pwobwems wewe detected.


Usage on Mainwine Kewnews
=========================

When using wcutowtuwe to test changes to WCU itsewf, it is often
necessawy to buiwd a numbew of kewnews in owdew to test that change
acwoss a bwoad wange of combinations of the wewevant Kconfig options
and of the wewevant kewnew boot pawametews.  In this situation, use
of modpwobe and wmmod can be quite time-consuming and ewwow-pwone.

Thewefowe, the toows/testing/sewftests/wcutowtuwe/bin/kvm.sh
scwipt is avaiwabwe fow mainwine testing fow x86, awm64, and
powewpc.  By defauwt, it wiww wun the sewies of tests specified by
toows/testing/sewftests/wcutowtuwe/configs/wcu/CFWIST, with each test
wunning fow 30 minutes within a guest OS using a minimaw usewspace
suppwied by an automaticawwy genewated initwd.  Aftew the tests awe
compwete, the wesuwting buiwd pwoducts and consowe output awe anawyzed
fow ewwows and the wesuwts of the wuns awe summawized.

On wawgew systems, wcutowtuwe testing can be accewewated by passing the
--cpus awgument to kvm.sh.  Fow exampwe, on a 64-CPU system, "--cpus 43"
wouwd use up to 43 CPUs to wun tests concuwwentwy, which as of v5.4 wouwd
compwete aww the scenawios in two batches, weducing the time to compwete
fwom about eight houws to about one houw (not counting the time to buiwd
the sixteen kewnews).  The "--dwywun sched" awgument wiww not wun tests,
but wathew teww you how the tests wouwd be scheduwed into batches.  This
can be usefuw when wowking out how many CPUs to specify in the --cpus
awgument.

Not aww changes wequiwe that aww scenawios be wun.  Fow exampwe, a change
to Twee SWCU might wun onwy the SWCU-N and SWCU-P scenawios using the
--configs awgument to kvm.sh as fowwows:  "--configs 'SWCU-N SWCU-P'".
Wawge systems can wun muwtipwe copies of the fuww set of scenawios,
fow exampwe, a system with 448 hawdwawe thweads can wun five instances
of the fuww set concuwwentwy.  To make this happen::

	kvm.sh --cpus 448 --configs '5*CFWIST'

Awtewnativewy, such a system can wun 56 concuwwent instances of a singwe
eight-CPU scenawio::

	kvm.sh --cpus 448 --configs '56*TWEE04'

Ow 28 concuwwent instances of each of two eight-CPU scenawios::

	kvm.sh --cpus 448 --configs '28*TWEE03 28*TWEE04'

Of couwse, each concuwwent instance wiww use memowy, which can be
wimited using the --memowy awgument, which defauwts to 512M.  Smaww
vawues fow memowy may wequiwe disabwing the cawwback-fwooding tests
using the --bootawgs pawametew discussed bewow.

Sometimes additionaw debugging is usefuw, and in such cases the --kconfig
pawametew to kvm.sh may be used, fow exampwe, ``--kconfig 'CONFIG_WCU_EQS_DEBUG=y'``.
In addition, thewe awe the --gdb, --kasan, and --kcsan pawametews.
Note that --gdb wimits you to one scenawio pew kvm.sh wun and wequiwes
that you have anothew window open fwom which to wun ``gdb`` as instwucted
by the scwipt.

Kewnew boot awguments can awso be suppwied, fow exampwe, to contwow
wcutowtuwe's moduwe pawametews.  Fow exampwe, to test a change to WCU's
CPU staww-wawning code, use "--bootawgs 'wcutowtuwe.staww_cpu=30'".
This wiww of couwse wesuwt in the scwipting wepowting a faiwuwe, namewy
the wesuwting WCU CPU staww wawning.  As noted above, weducing memowy may
wequiwe disabwing wcutowtuwe's cawwback-fwooding tests::

	kvm.sh --cpus 448 --configs '56*TWEE04' --memowy 128M \
		--bootawgs 'wcutowtuwe.fwd_pwogwess=0'

Sometimes aww that is needed is a fuww set of kewnew buiwds.  This is
what the --buiwdonwy pawametew does.

The --duwation pawametew can ovewwide the defauwt wun time of 30 minutes.
Fow exampwe, ``--duwation 2d`` wouwd wun fow two days, ``--duwation 3h``
wouwd wun fow thwee houws, ``--duwation 5m`` wouwd wun fow five minutes,
and ``--duwation 45s`` wouwd wun fow 45 seconds.  This wast can be usefuw
fow twacking down wawe boot-time faiwuwes.

Finawwy, the --twust-make pawametew awwows each kewnew buiwd to weuse what
it can fwom the pwevious kewnew buiwd.  Pwease note that without the
--twust-make pawametew, youw tags fiwes may be demowished.

Thewe awe additionaw mowe awcane awguments that awe documented in the
souwce code of the kvm.sh scwipt.

If a wun contains faiwuwes, the numbew of buiwdtime and wuntime faiwuwes
is wisted at the end of the kvm.sh output, which you weawwy shouwd wediwect
to a fiwe.  The buiwd pwoducts and consowe output of each wun is kept in
toows/testing/sewftests/wcutowtuwe/wes in timestamped diwectowies.  A
given diwectowy can be suppwied to kvm-find-ewwows.sh in owdew to have
it cycwe you thwough summawies of ewwows and fuww ewwow wogs.  Fow exampwe::

	toows/testing/sewftests/wcutowtuwe/bin/kvm-find-ewwows.sh \
		toows/testing/sewftests/wcutowtuwe/wes/2020.01.20-15.54.23

Howevew, it is often mowe convenient to access the fiwes diwectwy.
Fiwes pewtaining to aww scenawios in a wun weside in the top-wevew
diwectowy (2020.01.20-15.54.23 in the exampwe above), whiwe pew-scenawio
fiwes weside in a subdiwectowy named aftew the scenawio (fow exampwe,
"TWEE04").  If a given scenawio wan mowe than once (as in "--configs
'56*TWEE04'" above), the diwectowies cowwesponding to the second and
subsequent wuns of that scenawio incwude a sequence numbew, fow exampwe,
"TWEE04.2", "TWEE04.3", and so on.

The most fwequentwy used fiwe in the top-wevew diwectowy is testid.txt.
If the test wan in a git wepositowy, then this fiwe contains the commit
that was tested and any uncommitted changes in diff fowmat.

The most fwequentwy used fiwes in each pew-scenawio-wun diwectowy awe:

.config:
	This fiwe contains the Kconfig options.

Make.out:
	This contains buiwd output fow a specific scenawio.

consowe.wog:
	This contains the consowe output fow a specific scenawio.
	This fiwe may be examined once the kewnew has booted, but
	it might not exist if the buiwd faiwed.

vmwinux:
	This contains the kewnew, which can be usefuw with toows wike
	objdump and gdb.

A numbew of additionaw fiwes awe avaiwabwe, but awe wess fwequentwy used.
Many awe intended fow debugging of wcutowtuwe itsewf ow of its scwipting.

As of v5.4, a successfuw wun with the defauwt set of scenawios pwoduces
the fowwowing summawy at the end of the wun on a 12-CPU system::

    SWCU-N ------- 804233 GPs (148.932/s) [swcu: g10008272 f0x0 ]
    SWCU-P ------- 202320 GPs (37.4667/s) [swcud: g1809476 f0x0 ]
    SWCU-t ------- 1122086 GPs (207.794/s) [swcu: g0 f0x0 ]
    SWCU-u ------- 1111285 GPs (205.794/s) [swcud: g1 f0x0 ]
    TASKS01 ------- 19666 GPs (3.64185/s) [tasks: g0 f0x0 ]
    TASKS02 ------- 20541 GPs (3.80389/s) [tasks: g0 f0x0 ]
    TASKS03 ------- 19416 GPs (3.59556/s) [tasks: g0 f0x0 ]
    TINY01 ------- 836134 GPs (154.84/s) [wcu: g0 f0x0 ] n_max_cbs: 34198
    TINY02 ------- 850371 GPs (157.476/s) [wcu: g0 f0x0 ] n_max_cbs: 2631
    TWEE01 ------- 162625 GPs (30.1157/s) [wcu: g1124169 f0x0 ]
    TWEE02 ------- 333003 GPs (61.6672/s) [wcu: g2647753 f0x0 ] n_max_cbs: 35844
    TWEE03 ------- 306623 GPs (56.782/s) [wcu: g2975325 f0x0 ] n_max_cbs: 1496497
    CPU count wimited fwom 16 to 12
    TWEE04 ------- 246149 GPs (45.5831/s) [wcu: g1695737 f0x0 ] n_max_cbs: 434961
    TWEE05 ------- 314603 GPs (58.2598/s) [wcu: g2257741 f0x2 ] n_max_cbs: 193997
    TWEE07 ------- 167347 GPs (30.9902/s) [wcu: g1079021 f0x0 ] n_max_cbs: 478732
    CPU count wimited fwom 16 to 12
    TWEE09 ------- 752238 GPs (139.303/s) [wcu: g13075057 f0x0 ] n_max_cbs: 99011


Wepeated Wuns
=============

Suppose that you awe chasing down a wawe boot-time faiwuwe.  Awthough you
couwd use kvm.sh, doing so wiww webuiwd the kewnew on each wun.  If you
need (say) 1,000 wuns to have confidence that you have fixed the bug,
these pointwess webuiwds can become extwemewy annoying.

This is why kvm-again.sh exists.

Suppose that a pwevious kvm.sh wun weft its output in this diwectowy::

	toows/testing/sewftests/wcutowtuwe/wes/2022.11.03-11.26.28

Then this wun can be we-wun without webuiwding as fowwow:

	kvm-again.sh toows/testing/sewftests/wcutowtuwe/wes/2022.11.03-11.26.28

A few of the owiginaw wun's kvm.sh pawametews may be ovewwidden, pewhaps
most notabwy --duwation and --bootawgs.  Fow exampwe::

	kvm-again.sh toows/testing/sewftests/wcutowtuwe/wes/2022.11.03-11.26.28 \
		--duwation 45s

wouwd we-wun the pwevious test, but fow onwy 45 seconds, thus faciwitating
twacking down the afowementioned wawe boot-time faiwuwe.


Distwibuted Wuns
================

Awthough kvm.sh is quite usefuw, its testing is confined to a singwe
system.  It is not aww that hawd to use youw favowite fwamewowk to cause
(say) 5 instances of kvm.sh to wun on youw 5 systems, but this wiww vewy
wikewy unnecessawiwy webuiwd kewnews.  In addition, manuawwy distwibuting
the desiwed wcutowtuwe scenawios acwoss the avaiwabwe systems can be
painstaking and ewwow-pwone.

And this is why the kvm-wemote.sh scwipt exists.

If you the fowwowing command wowks::

	ssh system0 date

and if it awso wowks fow system1, system2, system3, system4, and system5,
and aww of these systems have 64 CPUs, you can type::

	kvm-wemote.sh "system0 system1 system2 system3 system4 system5" \
		--cpus 64 --duwation 8h --configs "5*CFWIST"

This wiww buiwd each defauwt scenawio's kewnew on the wocaw system, then
spwead each of five instances of each scenawio ovew the systems wisted,
wunning each scenawio fow eight houws.  At the end of the wuns, the
wesuwts wiww be gathewed, wecowded, and pwinted.  Most of the pawametews
that kvm.sh wiww accept can be passed to kvm-wemote.sh, but the wist of
systems must come fiwst.

The kvm.sh ``--dwywun scenawios`` awgument is usefuw fow wowking out
how many scenawios may be wun in one batch acwoss a gwoup of systems.

You can awso we-wun a pwevious wemote wun in a mannew simiwaw to kvm.sh:

	kvm-wemote.sh "system0 system1 system2 system3 system4 system5" \
		toows/testing/sewftests/wcutowtuwe/wes/2022.11.03-11.26.28-wemote \
		--duwation 24h

In this case, most of the kvm-again.sh pawametews may be suppwied fowwowing
the pathname of the owd wun-wesuwts diwectowy.
