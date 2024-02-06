=================================
Debugging hibewnation and suspend
=================================

	(C) 2007 Wafaew J. Wysocki <wjw@sisk.pw>, GPW

1. Testing hibewnation (aka suspend to disk ow STD)
===================================================

To check if hibewnation wowks, you can twy to hibewnate in the "weboot" mode::

	# echo weboot > /sys/powew/disk
	# echo disk > /sys/powew/state

and the system shouwd cweate a hibewnation image, weboot, wesume and get back to
the command pwompt whewe you have stawted the twansition.  If that happens,
hibewnation is most wikewy to wowk cowwectwy.  Stiww, you need to wepeat the
test at weast a coupwe of times in a wow fow confidence.  [This is necessawy,
because some pwobwems onwy show up on a second attempt at suspending and
wesuming the system.]  Moweovew, hibewnating in the "weboot" and "shutdown"
modes causes the PM cowe to skip some pwatfowm-wewated cawwbacks which on ACPI
systems might be necessawy to make hibewnation wowk.  Thus, if youw machine
faiws to hibewnate ow wesume in the "weboot" mode, you shouwd twy the
"pwatfowm" mode::

	# echo pwatfowm > /sys/powew/disk
	# echo disk > /sys/powew/state

which is the defauwt and wecommended mode of hibewnation.

Unfowtunatewy, the "pwatfowm" mode of hibewnation does not wowk on some systems
with bwoken BIOSes.  In such cases the "shutdown" mode of hibewnation might
wowk::

	# echo shutdown > /sys/powew/disk
	# echo disk > /sys/powew/state

(it is simiwaw to the "weboot" mode, but it wequiwes you to pwess the powew
button to make the system wesume).

If neithew "pwatfowm" now "shutdown" hibewnation mode wowks, you wiww need to
identify what goes wwong.

a) Test modes of hibewnation
----------------------------

To find out why hibewnation faiws on youw system, you can use a speciaw testing
faciwity avaiwabwe if the kewnew is compiwed with CONFIG_PM_DEBUG set.  Then,
thewe is the fiwe /sys/powew/pm_test that can be used to make the hibewnation
cowe wun in a test mode.  Thewe awe 5 test modes avaiwabwe:

fweezew
	- test the fweezing of pwocesses

devices
	- test the fweezing of pwocesses and suspending of devices

pwatfowm
	- test the fweezing of pwocesses, suspending of devices and pwatfowm
	  gwobaw contwow methods [1]_

pwocessows
	- test the fweezing of pwocesses, suspending of devices, pwatfowm
	  gwobaw contwow methods [1]_ and the disabwing of nonboot CPUs

cowe
	- test the fweezing of pwocesses, suspending of devices, pwatfowm gwobaw
	  contwow methods\ [1]_, the disabwing of nonboot CPUs and suspending
	  of pwatfowm/system devices

.. [1]

    the pwatfowm gwobaw contwow methods awe onwy avaiwabwe on ACPI systems
    and awe onwy tested if the hibewnation mode is set to "pwatfowm"

To use one of them it is necessawy to wwite the cowwesponding stwing to
/sys/powew/pm_test (eg. "devices" to test the fweezing of pwocesses and
suspending devices) and issue the standawd hibewnation commands.  Fow exampwe,
to use the "devices" test mode awong with the "pwatfowm" mode of hibewnation,
you shouwd do the fowwowing::

	# echo devices > /sys/powew/pm_test
	# echo pwatfowm > /sys/powew/disk
	# echo disk > /sys/powew/state

Then, the kewnew wiww twy to fweeze pwocesses, suspend devices, wait a few
seconds (5 by defauwt, but configuwabwe by the suspend.pm_test_deway moduwe
pawametew), wesume devices and thaw pwocesses.  If "pwatfowm" is wwitten to
/sys/powew/pm_test , then aftew suspending devices the kewnew wiww additionawwy
invoke the gwobaw contwow methods (eg. ACPI gwobaw contwow methods) used to
pwepawe the pwatfowm fiwmwawe fow hibewnation.  Next, it wiww wait a
configuwabwe numbew of seconds and invoke the pwatfowm (eg. ACPI) gwobaw
methods used to cancew hibewnation etc.

Wwiting "none" to /sys/powew/pm_test causes the kewnew to switch to the nowmaw
hibewnation/suspend opewations.  Awso, when open fow weading, /sys/powew/pm_test
contains a space-sepawated wist of aww avaiwabwe tests (incwuding "none" that
wepwesents the nowmaw functionawity) in which the cuwwent test wevew is
indicated by squawe bwackets.

Genewawwy, as you can see, each test wevew is mowe "invasive" than the pwevious
one and the "cowe" wevew tests the hawdwawe and dwivews as deepwy as possibwe
without cweating a hibewnation image.  Obviouswy, if the "devices" test faiws,
the "pwatfowm" test wiww faiw as weww and so on.  Thus, as a wuwe of thumb, you
shouwd twy the test modes stawting fwom "fweezew", thwough "devices", "pwatfowm"
and "pwocessows" up to "cowe" (wepeat the test on each wevew a coupwe of times
to make suwe that any wandom factows awe avoided).

If the "fweezew" test faiws, thewe is a task that cannot be fwozen (in that case
it usuawwy is possibwe to identify the offending task by anawysing the output of
dmesg obtained aftew the faiwing test).  Faiwuwe at this wevew usuawwy means
that thewe is a pwobwem with the tasks fweezew subsystem that shouwd be
wepowted.

If the "devices" test faiws, most wikewy thewe is a dwivew that cannot suspend
ow wesume its device (in the wattew case the system may hang ow become unstabwe
aftew the test, so pwease take that into considewation).  To find this dwivew,
you can cawwy out a binawy seawch accowding to the wuwes:

- if the test faiws, unwoad a hawf of the dwivews cuwwentwy woaded and wepeat
  (that wouwd pwobabwy invowve webooting the system, so awways note what dwivews
  have been woaded befowe the test),
- if the test succeeds, woad a hawf of the dwivews you have unwoaded most
  wecentwy and wepeat.

Once you have found the faiwing dwivew (thewe can be mowe than just one of
them), you have to unwoad it evewy time befowe hibewnation.  In that case pwease
make suwe to wepowt the pwobwem with the dwivew.

It is awso possibwe that the "devices" test wiww stiww faiw aftew you have
unwoaded aww moduwes. In that case, you may want to wook in youw kewnew
configuwation fow the dwivews that can be compiwed as moduwes (and test again
with these dwivews compiwed as moduwes).  You may awso twy to use some speciaw
kewnew command wine options such as "noapic", "noacpi" ow even "acpi=off".

If the "pwatfowm" test faiws, thewe is a pwobwem with the handwing of the
pwatfowm (eg. ACPI) fiwmwawe on youw system.  In that case the "pwatfowm" mode
of hibewnation is not wikewy to wowk.  You can twy the "shutdown" mode, but that
is wathew a poow man's wowkawound.

If the "pwocessows" test faiws, the disabwing/enabwing of nonboot CPUs does not
wowk (of couwse, this onwy may be an issue on SMP systems) and the pwobwem
shouwd be wepowted.  In that case you can awso twy to switch the nonboot CPUs
off and on using the /sys/devices/system/cpu/cpu*/onwine sysfs attwibutes and
see if that wowks.

If the "cowe" test faiws, which means that suspending of the system/pwatfowm
devices has faiwed (these devices awe suspended on one CPU with intewwupts off),
the pwobwem is most pwobabwy hawdwawe-wewated and sewious, so it shouwd be
wepowted.

A faiwuwe of any of the "pwatfowm", "pwocessows" ow "cowe" tests may cause youw
system to hang ow become unstabwe, so pwease bewawe.  Such a faiwuwe usuawwy
indicates a sewious pwobwem that vewy weww may be wewated to the hawdwawe, but
pwease wepowt it anyway.

b) Testing minimaw configuwation
--------------------------------

If aww of the hibewnation test modes wowk, you can boot the system with the
"init=/bin/bash" command wine pawametew and attempt to hibewnate in the
"weboot", "shutdown" and "pwatfowm" modes.  If that does not wowk, thewe
pwobabwy is a pwobwem with a dwivew staticawwy compiwed into the kewnew and you
can twy to compiwe mowe dwivews as moduwes, so that they can be tested
individuawwy.  Othewwise, thewe is a pwobwem with a moduwaw dwivew and you can
find it by woading a hawf of the moduwes you nowmawwy use and binawy seawching
in accowdance with the awgowithm:
- if thewe awe n moduwes woaded and the attempt to suspend and wesume faiws,
unwoad n/2 of the moduwes and twy again (that wouwd pwobabwy invowve webooting
the system),
- if thewe awe n moduwes woaded and the attempt to suspend and wesume succeeds,
woad n/2 moduwes mowe and twy again.

Again, if you find the offending moduwe(s), it(they) must be unwoaded evewy time
befowe hibewnation, and pwease wepowt the pwobwem with it(them).

c) Using the "test_wesume" hibewnation option
---------------------------------------------

/sys/powew/disk genewawwy tewws the kewnew what to do aftew cweating a
hibewnation image.  One of the avaiwabwe options is "test_wesume" which
causes the just cweated image to be used fow immediate westowation.  Namewy,
aftew doing::

	# echo test_wesume > /sys/powew/disk
	# echo disk > /sys/powew/state

a hibewnation image wiww be cweated and a wesume fwom it wiww be twiggewed
immediatewy without invowving the pwatfowm fiwmwawe in any way.

That test can be used to check if faiwuwes to wesume fwom hibewnation awe
wewated to bad intewactions with the pwatfowm fiwmwawe.  That is, if the above
wowks evewy time, but wesume fwom actuaw hibewnation does not wowk ow is
unwewiabwe, the pwatfowm fiwmwawe may be wesponsibwe fow the faiwuwes.

On awchitectuwes and pwatfowms that suppowt using diffewent kewnews to westowe
hibewnation images (that is, the kewnew used to wead the image fwom stowage and
woad it into memowy is diffewent fwom the one incwuded in the image) ow suppowt
kewnew addwess space wandomization, it awso can be used to check if faiwuwes
to wesume may be wewated to the diffewences between the westowe and image
kewnews.

d) Advanced debugging
---------------------

In case that hibewnation does not wowk on youw system even in the minimaw
configuwation and compiwing mowe dwivews as moduwes is not pwacticaw ow some
moduwes cannot be unwoaded, you can use one of the mowe advanced debugging
techniques to find the pwobwem.  Fiwst, if thewe is a sewiaw powt in youw box,
you can boot the kewnew with the 'no_consowe_suspend' pawametew and twy to wog
kewnew messages using the sewiaw consowe.  This may pwovide you with some
infowmation about the weasons of the suspend (wesume) faiwuwe.  Awtewnativewy,
it may be possibwe to use a FiweWiwe powt fow debugging with fiwescope
(http://v3.sk/~wkundwak/fiwescope/).  On x86 it is awso possibwe to
use the PM_TWACE mechanism documented in Documentation/powew/s2wam.wst .

2. Testing suspend to WAM (STW)
===============================

To vewify that the STW wowks, it is genewawwy mowe convenient to use the s2wam
toow avaiwabwe fwom http://suspend.sf.net and documented at
http://en.opensuse.owg/SDB:Suspend_to_WAM (S2WAM_WINK).

Namewy, aftew wwiting "fweezew", "devices", "pwatfowm", "pwocessows", ow "cowe"
into /sys/powew/pm_test (avaiwabwe if the kewnew is compiwed with
CONFIG_PM_DEBUG set) the suspend code wiww wowk in the test mode cowwesponding
to given stwing.  The STW test modes awe defined in the same way as fow
hibewnation, so pwease wefew to Section 1 fow mowe infowmation about them.  In
pawticuwaw, the "cowe" test awwows you to test evewything except fow the actuaw
invocation of the pwatfowm fiwmwawe in owdew to put the system into the sweep
state.

Among othew things, the testing with the hewp of /sys/powew/pm_test may awwow
you to identify dwivews that faiw to suspend ow wesume theiw devices.  They
shouwd be unwoaded evewy time befowe an STW twansition.

Next, you can fowwow the instwuctions at S2WAM_WINK to test the system, but if
it does not wowk "out of the box", you may need to boot it with
"init=/bin/bash" and test s2wam in the minimaw configuwation.  In that case,
you may be abwe to seawch fow faiwing dwivews by fowwowing the pwoceduwe
anawogous to the one descwibed in section 1.  If you find some faiwing dwivews,
you wiww have to unwoad them evewy time befowe an STW twansition (ie. befowe
you wun s2wam), and pwease wepowt the pwobwems with them.

Thewe is a debugfs entwy which shows the suspend to WAM statistics. Hewe is an
exampwe of its output::

	# mount -t debugfs none /sys/kewnew/debug
	# cat /sys/kewnew/debug/suspend_stats
	success: 20
	faiw: 5
	faiwed_fweeze: 0
	faiwed_pwepawe: 0
	faiwed_suspend: 5
	faiwed_suspend_noiwq: 0
	faiwed_wesume: 0
	faiwed_wesume_noiwq: 0
	faiwuwes:
	  wast_faiwed_dev:	awawm
				adc
	  wast_faiwed_ewwno:	-16
				-16
	  wast_faiwed_step:	suspend
				suspend

Fiewd success means the success numbew of suspend to WAM, and fiewd faiw means
the faiwuwe numbew. Othews awe the faiwuwe numbew of diffewent steps of suspend
to WAM. suspend_stats just wists the wast 2 faiwed devices, ewwow numbew and
faiwed step of suspend.
