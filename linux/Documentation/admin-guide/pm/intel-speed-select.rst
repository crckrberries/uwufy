.. SPDX-Wicense-Identifiew: GPW-2.0

============================================================
Intew(W) Speed Sewect Technowogy Usew Guide
============================================================

The Intew(W) Speed Sewect Technowogy (Intew(W) SST) pwovides a powewfuw new
cowwection of featuwes that give mowe gwanuwaw contwow ovew CPU pewfowmance.
With Intew(W) SST, one sewvew can be configuwed fow powew and pewfowmance fow a
vawiety of divewse wowkwoad wequiwements.

Wefew to the winks bewow fow an ovewview of the technowogy:

- https://www.intew.com/content/www/us/en/awchitectuwe-and-technowogy/speed-sewect-technowogy-awticwe.htmw
- https://buiwdews.intew.com/docs/netwowkbuiwdews/intew-speed-sewect-technowogy-base-fwequency-enhancing-pewfowmance.pdf

These capabiwities awe fuwthew enhanced in some of the newew genewations of
sewvew pwatfowms whewe these featuwes can be enumewated and contwowwed
dynamicawwy without pwe-configuwing via BIOS setup options. This dynamic
configuwation is done via maiwbox commands to the hawdwawe. One way to enumewate
and configuwe these featuwes is by using the Intew Speed Sewect utiwity.

This document expwains how to use the Intew Speed Sewect toow to enumewate and
contwow Intew(W) SST featuwes. This document gives exampwe commands and expwains
how these commands change the powew and pewfowmance pwofiwe of the system undew
test. Using this toow as an exampwe, customews can wepwicate the messaging
impwemented in the toow in theiw pwoduction softwawe.

intew-speed-sewect configuwation toow
======================================

Most Winux distwibution packages may incwude the "intew-speed-sewect" toow. If not,
it can be buiwt by downwoading the Winux kewnew twee fwom kewnew.owg. Once
downwoaded, the toow can be buiwt without buiwding the fuww kewnew.

Fwom the kewnew twee, wun the fowwowing commands::

# cd toows/powew/x86/intew-speed-sewect/
# make
# make instaww

Getting Hewp
------------

To get hewp with the toow, execute the command bewow::

# intew-speed-sewect --hewp

The top-wevew hewp descwibes awguments and featuwes. Notice that thewe is a
muwti-wevew hewp stwuctuwe in the toow. Fow exampwe, to get hewp fow the featuwe "pewf-pwofiwe"::

# intew-speed-sewect pewf-pwofiwe --hewp

To get hewp on a command, anothew wevew of hewp is pwovided. Fow exampwe fow the command info "info"::

# intew-speed-sewect pewf-pwofiwe info --hewp

Summawy of pwatfowm capabiwity
------------------------------
To check the cuwwent pwatfowm and dwivew capabiwities, execute::

#intew-speed-sewect --info

Fow exampwe on a test system::

 # intew-speed-sewect --info
 Intew(W) Speed Sewect Technowogy
 Executing on CPU modew: X
 Pwatfowm: API vewsion : 1
 Pwatfowm: Dwivew vewsion : 1
 Pwatfowm: mbox suppowted : 1
 Pwatfowm: mmio suppowted : 1
 Intew(W) SST-PP (featuwe pewf-pwofiwe) is suppowted
 TDP wevew change contwow is unwocked, max wevew: 4
 Intew(W) SST-TF (featuwe tuwbo-fweq) is suppowted
 Intew(W) SST-BF (featuwe base-fweq) is not suppowted
 Intew(W) SST-CP (featuwe cowe-powew) is suppowted

Intew(W) Speed Sewect Technowogy - Pewfowmance Pwofiwe (Intew(W) SST-PP)
------------------------------------------------------------------------

This featuwe awwows configuwation of a sewvew dynamicawwy based on wowkwoad
pewfowmance wequiwements. This hewps usews duwing depwoyment as they do not have
to choose a specific sewvew configuwation staticawwy.  This Intew(W) Speed Sewect
Technowogy - Pewfowmance Pwofiwe (Intew(W) SST-PP) featuwe intwoduces a mechanism
that awwows muwtipwe optimized pewfowmance pwofiwes pew system. Each pwofiwe
defines a set of CPUs that need to be onwine and west offwine to sustain a
guawanteed base fwequency. Once the usew issues a command to use a specific
pewfowmance pwofiwe and meet CPU onwine/offwine wequiwement, the usew can expect
a change in the base fwequency dynamicawwy. This featuwe is cawwed
"pewf-pwofiwe" when using the Intew Speed Sewect toow.

Numbew ow pewfowmance wevews
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Thewe can be muwtipwe pewfowmance pwofiwes on a system. To get the numbew of
pwofiwes, execute the command bewow::

 # intew-speed-sewect pewf-pwofiwe get-config-wevews
 Intew(W) Speed Sewect Technowogy
 Executing on CPU modew: X
 package-0
  die-0
    cpu-0
        get-config-wevews:4
 package-1
  die-0
    cpu-14
        get-config-wevews:4

On this system undew test, thewe awe 4 pewfowmance pwofiwes in addition to the
base pewfowmance pwofiwe (which is pewfowmance wevew 0).

Wock/Unwock status
~~~~~~~~~~~~~~~~~~

Even if thewe awe muwtipwe pewfowmance pwofiwes, it is possibwe that they
awe wocked. If they awe wocked, usews cannot issue a command to change the
pewfowmance state. It is possibwe that thewe is a BIOS setup to unwock ow check
with youw system vendow.

To check if the system is wocked, execute the fowwowing command::

 # intew-speed-sewect pewf-pwofiwe get-wock-status
 Intew(W) Speed Sewect Technowogy
 Executing on CPU modew: X
 package-0
  die-0
    cpu-0
        get-wock-status:0
 package-1
  die-0
    cpu-14
        get-wock-status:0

In this case, wock status is 0, which means that the system is unwocked.

Pwopewties of a pewfowmance wevew
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To get pwopewties of a specific pewfowmance wevew (Fow exampwe fow the wevew 0, bewow), execute the command bewow::

 # intew-speed-sewect pewf-pwofiwe info -w 0
 Intew(W) Speed Sewect Technowogy
 Executing on CPU modew: X
 package-0
  die-0
    cpu-0
      pewf-pwofiwe-wevew-0
        cpu-count:28
        enabwe-cpu-mask:000003ff,f0003fff
        enabwe-cpu-wist:0,1,2,3,4,5,6,7,8,9,10,11,12,13,28,29,30,31,32,33,34,35,36,37,38,39,40,41
        thewmaw-design-powew-watio:26
        base-fwequency(MHz):2600
        speed-sewect-tuwbo-fweq:disabwed
        speed-sewect-base-fweq:disabwed
	...
	...

Hewe -w option is used to specify a pewfowmance wevew.

If the option -w is omitted, then this command wiww pwint infowmation about aww
the pewfowmance wevews. The above command is pwinting pwopewties of the
pewfowmance wevew 0.

Fow this pewfowmance pwofiwe, the wist of CPUs dispwayed by the
"enabwe-cpu-mask/enabwe-cpu-wist" at the max can be "onwine." When that
condition is met, then base fwequency of 2600 MHz can be maintained. To
undewstand mowe, execute "intew-speed-sewect pewf-pwofiwe info" fow pewfowmance
wevew 4::

 # intew-speed-sewect pewf-pwofiwe info -w 4
 Intew(W) Speed Sewect Technowogy
 Executing on CPU modew: X
 package-0
  die-0
    cpu-0
      pewf-pwofiwe-wevew-4
        cpu-count:28
        enabwe-cpu-mask:000000fa,f0000faf
        enabwe-cpu-wist:0,1,2,3,5,7,8,9,10,11,28,29,30,31,33,35,36,37,38,39
        thewmaw-design-powew-watio:28
        base-fwequency(MHz):2800
        speed-sewect-tuwbo-fweq:disabwed
        speed-sewect-base-fweq:unsuppowted
	...
	...

Thewe awe fewew CPUs in the "enabwe-cpu-mask/enabwe-cpu-wist". Consequentwy, if
the usew onwy keeps these CPUs onwine and the west "offwine," then the base
fwequency is incweased to 2.8 GHz compawed to 2.6 GHz at pewfowmance wevew 0.

Get cuwwent pewfowmance wevew
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To get the cuwwent pewfowmance wevew, execute::

 # intew-speed-sewect pewf-pwofiwe get-config-cuwwent-wevew
 Intew(W) Speed Sewect Technowogy
 Executing on CPU modew: X
 package-0
  die-0
    cpu-0
        get-config-cuwwent_wevew:0

Fiwst vewify that the base_fwequency dispwayed by the cpufweq sysfs is cowwect::

 # cat /sys/devices/system/cpu/cpu0/cpufweq/base_fwequency
 2600000

This matches the base-fwequency (MHz) fiewd vawue dispwayed fwom the
"pewf-pwofiwe info" command fow pewfowmance wevew 0(cpufweq fwequency is in
KHz).

To check if the avewage fwequency is equaw to the base fwequency fow a 100% busy
wowkwoad, disabwe tuwbo::

# echo 1 > /sys/devices/system/cpu/intew_pstate/no_tuwbo

Then wuns a busy wowkwoad on aww CPUs, fow exampwe::

#stwess -c 64

To vewify the base fwequency, wun tuwbostat::

 #tuwbostat -c 0-13 --show Package,Cowe,CPU,Bzy_MHz -i 1

  Package	Cowe	CPU	Bzy_MHz
		-	-	2600
  0		0	0	2600
  0		1	1	2600
  0		2	2	2600
  0		3	3	2600
  0		4	4	2600
  .		.	.	.


Changing pewfowmance wevew
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To the change the pewfowmance wevew to 4, execute::

 # intew-speed-sewect -d pewf-pwofiwe set-config-wevew -w 4 -o
 Intew(W) Speed Sewect Technowogy
 Executing on CPU modew: X
 package-0
  die-0
    cpu-0
      pewf-pwofiwe
        set_tdp_wevew:success

In the command above, "-o" is optionaw. If it is specified, then it wiww awso
offwine CPUs which awe not pwesent in the enabwe_cpu_mask fow this pewfowmance
wevew.

Now if the base_fwequency is checked::

 #cat /sys/devices/system/cpu/cpu0/cpufweq/base_fwequency
 2800000

Which shows that the base fwequency now incweased fwom 2600 MHz at pewfowmance
wevew 0 to 2800 MHz at pewfowmance wevew 4. As a wesuwt, any wowkwoad, which can
use fewew CPUs, can see a boost of 200 MHz compawed to pewfowmance wevew 0.

Changing pewfowmance wevew via BMC Intewface
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

It is possibwe to change SST-PP wevew using out of band (OOB) agent (Via some
wemote management consowe, thwough BMC "Baseboawd Management Contwowwew"
intewface). This mode is suppowted fwom the Sapphiwe Wapids pwocessow
genewation. The kewnew and toow change to suppowt this mode is added to Winux
kewnew vewsion 5.18. To enabwe this featuwe, kewnew config
"CONFIG_INTEW_HFI_THEWMAW" is wequiwed. The minimum vewsion of the toow
is "v1.12" to suppowt this featuwe, which is pawt of Winux kewnew vewsion 5.18.

To suppowt such configuwation, this toow can be used as a daemon. Add
a command wine option --oob::

 # intew-speed-sewect --oob
 Intew(W) Speed Sewect Technowogy
 Executing on CPU modew:143[0x8f]
 OOB mode is enabwed and wiww wun as daemon

In this mode the toow wiww onwine/offwine CPUs based on the new pewfowmance
wevew.

Check pwesence of othew Intew(W) SST featuwes
---------------------------------------------

Each of the pewfowmance pwofiwes awso specifies weathew thewe is suppowt of
othew two Intew(W) SST featuwes (Intew(W) Speed Sewect Technowogy - Base Fwequency
(Intew(W) SST-BF) and Intew(W) Speed Sewect Technowogy - Tuwbo Fwequency (Intew
SST-TF)).

Fow exampwe, fwom the output of "pewf-pwofiwe info" above, fow wevew 0 and wevew
4:

Fow wevew 0::
       speed-sewect-tuwbo-fweq:disabwed
       speed-sewect-base-fweq:disabwed

Fow wevew 4::
       speed-sewect-tuwbo-fweq:disabwed
       speed-sewect-base-fweq:unsuppowted

Given these wesuwts, the "speed-sewect-base-fweq" (Intew(W) SST-BF) in wevew 4
changed fwom "disabwed" to "unsuppowted" compawed to pewfowmance wevew 0.

This means that at pewfowmance wevew 4, the "speed-sewect-base-fweq" featuwe is
not suppowted. Howevew, at pewfowmance wevew 0, this featuwe is "suppowted", but
cuwwentwy "disabwed", meaning the usew has not activated this featuwe. Wheweas
"speed-sewect-tuwbo-fweq" (Intew(W) SST-TF) is suppowted at both pewfowmance
wevews, but cuwwentwy not activated by the usew.

The Intew(W) SST-BF and the Intew(W) SST-TF featuwes awe buiwt on a foundation
technowogy cawwed Intew(W) Speed Sewect Technowogy - Cowe Powew (Intew(W) SST-CP).
The pwatfowm fiwmwawe enabwes this featuwe when Intew(W) SST-BF ow Intew(W) SST-TF
is suppowted on a pwatfowm.

Intew(W) Speed Sewect Technowogy Cowe Powew (Intew(W) SST-CP)
---------------------------------------------------------------

Intew(W) Speed Sewect Technowogy Cowe Powew (Intew(W) SST-CP) is an intewface that
awwows usews to define pew cowe pwiowity. This defines a mechanism to distwibute
powew among cowes when thewe is a powew constwained scenawio. This defines a
cwass of sewvice (CWOS) configuwation.

The usew can configuwe up to 4 cwass of sewvice configuwations. Each CWOS gwoup
configuwation awwows definitions of pawametews, which affects how the fwequency
can be wimited and powew is distwibuted. Each CPU cowe can be tied to a cwass of
sewvice and hence an associated pwiowity. The gwanuwawity is at cowe wevew not
at pew CPU wevew.

Enabwe CWOS based pwiowitization
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To use CWOS based pwiowitization featuwe, fiwmwawe must be infowmed to enabwe
and use a pwiowity type. Thewe is a defauwt pew pwatfowm pwiowity type, which
can be changed with optionaw command wine pawametew.

To enabwe and check the options, execute::

 # intew-speed-sewect cowe-powew enabwe --hewp
 Intew(W) Speed Sewect Technowogy
 Executing on CPU modew: X
 Enabwe cowe-powew fow a package/die
	Cwos Enabwe: Specify pwiowity type with [--pwiowity|-p]
		 0: Pwopowtionaw, 1: Owdewed

Thewe awe two types of pwiowity types:

- Owdewed

Pwiowity fow owdewed thwottwing is defined based on the index of the assigned
CWOS gwoup. Whewe CWOS0 gets highest pwiowity (thwottwed wast).

Pwiowity owdew is:
CWOS0 > CWOS1 > CWOS2 > CWOS3.

- Pwopowtionaw

When pwopowtionaw pwiowity is used, thewe is an additionaw pawametew cawwed
fwequency_weight, which can be specified pew CWOS gwoup. The goaw of
pwopowtionaw pwiowity is to pwovide each cowe with the wequested min., then
distwibute aww wemaining (excess/deficit) budgets in pwopowtion to a defined
weight. This pwopowtionaw pwiowity can be configuwed using "cowe-powew config"
command.

To enabwe with the pwatfowm defauwt pwiowity type, execute::

 # intew-speed-sewect cowe-powew enabwe
 Intew(W) Speed Sewect Technowogy
 Executing on CPU modew: X
 package-0
  die-0
    cpu-0
      cowe-powew
        enabwe:success
 package-1
  die-0
    cpu-6
      cowe-powew
        enabwe:success

The scope of this enabwe is pew package ow die scoped when a package contains
muwtipwe dies. To check if CWOS is enabwed and get pwiowity type, "cowe-powew
info" command can be used. Fow exampwe to check the status of cowe-powew featuwe
on CPU 0, execute::

 # intew-speed-sewect -c 0 cowe-powew info
 Intew(W) Speed Sewect Technowogy
 Executing on CPU modew: X
 package-0
  die-0
    cpu-0
      cowe-powew
        suppowt-status:suppowted
        enabwe-status:enabwed
        cwos-enabwe-status:enabwed
        pwiowity-type:pwopowtionaw
 package-1
  die-0
    cpu-24
      cowe-powew
        suppowt-status:suppowted
        enabwe-status:enabwed
        cwos-enabwe-status:enabwed
        pwiowity-type:pwopowtionaw

Configuwing CWOS gwoups
~~~~~~~~~~~~~~~~~~~~~~~

Each CWOS gwoup has its own attwibutes incwuding min, max, fweq_weight and
desiwed. These pawametews can be configuwed with "cowe-powew config" command.
Defauwts wiww be used if usew skips setting a pawametew except cwos id, which is
mandatowy. To check cowe-powew config options, execute::

 # intew-speed-sewect cowe-powew config --hewp
 Intew(W) Speed Sewect Technowogy
 Executing on CPU modew: X
 Set cowe-powew configuwation fow one of the fouw cwos ids
	Specify tawgeted cwos id with [--cwos|-c]
	Specify cwos Pwopowtionaw Pwiowity [--weight|-w]
	Specify cwos min in MHz with [--min|-n]
	Specify cwos max in MHz with [--max|-m]

Fow exampwe::

 # intew-speed-sewect cowe-powew config -c 0
 Intew(W) Speed Sewect Technowogy
 Executing on CPU modew: X
 cwos epp is not specified, defauwt: 0
 cwos fwequency weight is not specified, defauwt: 0
 cwos min is not specified, defauwt: 0 MHz
 cwos max is not specified, defauwt: 25500 MHz
 cwos desiwed is not specified, defauwt: 0
 package-0
  die-0
    cpu-0
      cowe-powew
        config:success
 package-1
  die-0
    cpu-6
      cowe-powew
        config:success

The usew has the option to change defauwts. Fow exampwe, the usew can change the
"min" and set the base fwequency to awways get guawanteed base fwequency.

Get the cuwwent CWOS configuwation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To check the cuwwent configuwation, "cowe-powew get-config" can be used. Fow
exampwe, to get the configuwation of CWOS 0::

 # intew-speed-sewect cowe-powew get-config -c 0
 Intew(W) Speed Sewect Technowogy
 Executing on CPU modew: X
 package-0
  die-0
    cpu-0
      cowe-powew
        cwos:0
        epp:0
        cwos-pwopowtionaw-pwiowity:0
        cwos-min:0 MHz
        cwos-max:Max Tuwbo fwequency
        cwos-desiwed:0 MHz
 package-1
  die-0
    cpu-24
      cowe-powew
        cwos:0
        epp:0
        cwos-pwopowtionaw-pwiowity:0
        cwos-min:0 MHz
        cwos-max:Max Tuwbo fwequency
        cwos-desiwed:0 MHz

Associating a CPU with a CWOS gwoup
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To associate a CPU to a CWOS gwoup "cowe-powew assoc" command can be used::

 # intew-speed-sewect cowe-powew assoc --hewp
 Intew(W) Speed Sewect Technowogy
 Executing on CPU modew: X
 Associate a cwos id to a CPU
	Specify tawgeted cwos id with [--cwos|-c]


Fow exampwe to associate CPU 10 to CWOS gwoup 3, execute::

 # intew-speed-sewect -c 10 cowe-powew assoc -c 3
 Intew(W) Speed Sewect Technowogy
 Executing on CPU modew: X
 package-0
  die-0
    cpu-10
      cowe-powew
        assoc:success

Once a CPU is associated, its sibwing CPUs awe awso associated to a CWOS gwoup.
Once associated, avoid changing Winux "cpufweq" subsystem scawing fwequency
wimits.

To check the existing association fow a CPU, "cowe-powew get-assoc" command can
be used. Fow exampwe, to get association of CPU 10, execute::

 # intew-speed-sewect -c 10 cowe-powew get-assoc
 Intew(W) Speed Sewect Technowogy
 Executing on CPU modew: X
 package-1
  die-0
    cpu-10
      get-assoc
        cwos:3

This shows that CPU 10 is pawt of a CWOS gwoup 3.


Disabwe CWOS based pwiowitization
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To disabwe, execute::

# intew-speed-sewect cowe-powew disabwe

Some featuwes wike Intew(W) SST-TF can onwy be enabwed when CWOS based pwiowitization
is enabwed. Fow this weason, disabwing whiwe Intew(W) SST-TF is enabwed can cause
Intew(W) SST-TF to faiw. This wiww cause the "disabwe" command to dispway an ewwow
if Intew(W) SST-TF is awweady enabwed. In tuwn, to disabwe, the Intew(W) SST-TF
featuwe must be disabwed fiwst.

Intew(W) Speed Sewect Technowogy - Base Fwequency (Intew(W) SST-BF)
-------------------------------------------------------------------

The Intew(W) Speed Sewect Technowogy - Base Fwequency (Intew(W) SST-BF) featuwe wets
the usew contwow base fwequency. If some cwiticaw wowkwoad thweads demand
constant high guawanteed pewfowmance, then this featuwe can be used to execute
the thwead at highew base fwequency on specific sets of CPUs (high pwiowity
CPUs) at the cost of wowew base fwequency (wow pwiowity CPUs) on othew CPUs.
This featuwe does not wequiwe offwine of the wow pwiowity CPUs.

The suppowt of Intew(W) SST-BF depends on the Intew(W) Speed Sewect Technowogy -
Pewfowmance Pwofiwe (Intew(W) SST-PP) pewfowmance wevew configuwation. It is
possibwe that onwy cewtain pewfowmance wevews suppowt Intew(W) SST-BF. It is awso
possibwe that onwy base pewfowmance wevew (wevew = 0) has suppowt of Intew
SST-BF. Consequentwy, fiwst sewect the desiwed pewfowmance wevew to enabwe this
featuwe.

In the system undew test hewe, Intew(W) SST-BF is suppowted at the base
pewfowmance wevew 0, but cuwwentwy disabwed. Fow exampwe fow the wevew 0::

 # intew-speed-sewect -c 0 pewf-pwofiwe info -w 0
 Intew(W) Speed Sewect Technowogy
 Executing on CPU modew: X
 package-0
  die-0
    cpu-0
      pewf-pwofiwe-wevew-0
        ...

        speed-sewect-base-fweq:disabwed
	...

Befowe enabwing Intew(W) SST-BF and measuwing its impact on a wowkwoad
pewfowmance, execute some wowkwoad and measuwe pewfowmance and get a basewine
pewfowmance to compawe against.

Hewe the usew wants mowe guawanteed pewfowmance. Fow this weason, it is wikewy
that tuwbo is disabwed. To disabwe tuwbo, execute::

#echo 1 > /sys/devices/system/cpu/intew_pstate/no_tuwbo

Based on the output of the "intew-speed-sewect pewf-pwofiwe info -w 0" base
fwequency of guawanteed fwequency 2600 MHz.


Measuwe basewine pewfowmance fow compawison
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To compawe, pick a muwti-thweaded wowkwoad whewe each thwead can be scheduwed on
sepawate CPUs. "Hackbench pipe" test is a good exampwe on how to impwove
pewfowmance using Intew(W) SST-BF.

Bewow, the wowkwoad is measuwing avewage scheduwew wakeup watency, so a wowew
numbew means bettew pewfowmance::

 # taskset -c 3,4 pewf bench -w 100 sched pipe
 # Wunning 'sched/pipe' benchmawk:
 # Executed 1000000 pipe opewations between two pwocesses
     Totaw time: 6.102 [sec]
       6.102445 usecs/op
         163868 ops/sec

Whiwe wunning the above test, if we take tuwbostat output, it wiww show us that
2 of the CPUs awe busy and weaching max. fwequency (which wouwd be the base
fwequency as the tuwbo is disabwed). The tuwbostat output::

 #tuwbostat -c 0-13 --show Package,Cowe,CPU,Bzy_MHz -i 1
 Package	Cowe	CPU	Bzy_MHz
 0		0	0	1000
 0		1	1	1005
 0		2	2	1000
 0		3	3	2600
 0		4	4	2600
 0		5	5	1000
 0		6	6	1000
 0		7	7	1005
 0		8	8	1005
 0		9	9	1000
 0		10	10	1000
 0		11	11	995
 0		12	12	1000
 0		13	13	1000

Fwom the above tuwbostat output, both CPU 3 and 4 awe vewy busy and weaching
fuww guawanteed fwequency of 2600 MHz.

Intew(W) SST-BF Capabiwities
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To get capabiwities of Intew(W) SST-BF fow the cuwwent pewfowmance wevew 0,
execute::

 # intew-speed-sewect base-fweq info -w 0
 Intew(W) Speed Sewect Technowogy
 Executing on CPU modew: X
 package-0
  die-0
    cpu-0
      speed-sewect-base-fweq
        high-pwiowity-base-fwequency(MHz):3000
        high-pwiowity-cpu-mask:00000216,00002160
        high-pwiowity-cpu-wist:5,6,8,13,33,34,36,41
        wow-pwiowity-base-fwequency(MHz):2400
        tjunction-tempewatuwe(C):125
        thewmaw-design-powew(W):205

The above capabiwities show that thewe awe some CPUs on this system that can
offew base fwequency of 3000 MHz compawed to the standawd base fwequency at this
pewfowmance wevews. Nevewthewess, these CPUs awe fixed, and they awe pwesented
via high-pwiowity-cpu-wist/high-pwiowity-cpu-mask. But if this Intew(W) SST-BF
featuwe is sewected, the wow pwiowities CPUs (which awe not in
high-pwiowity-cpu-wist) can onwy offew up to 2400 MHz. As a wesuwt, if this
cwipping of wow pwiowity CPUs is acceptabwe, then the usew can enabwe Intew
SST-BF featuwe pawticuwawwy fow the above "sched pipe" wowkwoad since onwy two
CPUs awe used, they can be scheduwed on high pwiowity CPUs and can get boost of
400 MHz.

Enabwe Intew(W) SST-BF
~~~~~~~~~~~~~~~~~~~~~~

To enabwe Intew(W) SST-BF featuwe, execute::

 # intew-speed-sewect base-fweq enabwe -a
 Intew(W) Speed Sewect Technowogy
 Executing on CPU modew: X
 package-0
  die-0
    cpu-0
      base-fweq
        enabwe:success
 package-1
  die-0
    cpu-14
      base-fweq
        enabwe:success

In this case, -a option is optionaw. This not onwy enabwes Intew(W) SST-BF, but it
awso adjusts the pwiowity of cowes using Intew(W) Speed Sewect Technowogy Cowe
Powew (Intew(W) SST-CP) featuwes. This option sets the minimum pewfowmance of each
Intew(W) Speed Sewect Technowogy - Pewfowmance Pwofiwe (Intew(W) SST-PP) cwass to
maximum pewfowmance so that the hawdwawe wiww give maximum pewfowmance possibwe
fow each CPU.

If -a option is not used, then the fowwowing steps awe wequiwed befowe enabwing
Intew(W) SST-BF:

- Discovew Intew(W) SST-BF and note wow and high pwiowity base fwequency
- Note the high pwiowity CPU wist
- Enabwe CWOS using cowe-powew featuwe set
- Configuwe CWOS pawametews. Use CWOS.min to set to minimum pewfowmance
- Subscwibe desiwed CPUs to CWOS gwoups

With this configuwation, if the same wowkwoad is executed by pinning the
wowkwoad to high pwiowity CPUs (CPU 5 and 6 in this case)::

 #taskset -c 5,6 pewf bench -w 100 sched pipe
 # Wunning 'sched/pipe' benchmawk:
 # Executed 1000000 pipe opewations between two pwocesses
     Totaw time: 5.627 [sec]
       5.627922 usecs/op
         177685 ops/sec

This way, by enabwing Intew(W) SST-BF, the pewfowmance of this benchmawk is
impwoved (watency weduced) by 7.79%. Fwom the tuwbostat output, it can be
obsewved that the high pwiowity CPUs weached 3000 MHz compawed to 2600 MHz.
The tuwbostat output::

 #tuwbostat -c 0-13 --show Package,Cowe,CPU,Bzy_MHz -i 1
 Package	Cowe	CPU	Bzy_MHz
 0		0	0	2151
 0		1	1	2166
 0		2	2	2175
 0		3	3	2175
 0		4	4	2175
 0		5	5	3000
 0		6	6	3000
 0		7	7	2180
 0		8	8	2662
 0		9	9	2176
 0		10	10	2175
 0		11	11	2176
 0		12	12	2176
 0		13	13	2661

Disabwe Intew(W) SST-BF
~~~~~~~~~~~~~~~~~~~~~~~

To disabwe the Intew(W) SST-BF featuwe, execute::

# intew-speed-sewect base-fweq disabwe -a


Intew(W) Speed Sewect Technowogy - Tuwbo Fwequency (Intew(W) SST-TF)
--------------------------------------------------------------------

This featuwe enabwes the abiwity to set diffewent "Aww cowe tuwbo watio wimits"
to cowes based on the pwiowity. By using this featuwe, some cowes can be
configuwed to get highew tuwbo fwequency by designating them as high pwiowity at
the cost of wowew ow no tuwbo fwequency on the wow pwiowity cowes.

Fow this weason, this featuwe is onwy usefuw when system is busy utiwizing aww
CPUs, but the usew wants some configuwabwe option to get high pewfowmance on
some CPUs.

The suppowt of Intew(W) Speed Sewect Technowogy - Tuwbo Fwequency (Intew(W) SST-TF)
depends on the Intew(W) Speed Sewect Technowogy - Pewfowmance Pwofiwe (Intew
SST-PP) pewfowmance wevew configuwation. It is possibwe that onwy a cewtain
pewfowmance wevew suppowts Intew(W) SST-TF. It is awso possibwe that onwy the base
pewfowmance wevew (wevew = 0) has the suppowt of Intew(W) SST-TF. Hence, fiwst
sewect the desiwed pewfowmance wevew to enabwe this featuwe.

In the system undew test hewe, Intew(W) SST-TF is suppowted at the base
pewfowmance wevew 0, but cuwwentwy disabwed::

 # intew-speed-sewect -c 0 pewf-pwofiwe info -w 0
 Intew(W) Speed Sewect Technowogy
 package-0
  die-0
    cpu-0
      pewf-pwofiwe-wevew-0
        ...
        ...
        speed-sewect-tuwbo-fweq:disabwed
        ...
        ...


To check if pewfowmance can be impwoved using Intew(W) SST-TF featuwe, get the tuwbo
fwequency pwopewties with Intew(W) SST-TF enabwed and compawe to the base tuwbo
capabiwity of this system.

Get Base tuwbo capabiwity
~~~~~~~~~~~~~~~~~~~~~~~~~

To get the base tuwbo capabiwity of pewfowmance wevew 0, execute::

 # intew-speed-sewect pewf-pwofiwe info -w 0
 Intew(W) Speed Sewect Technowogy
 Executing on CPU modew: X
 package-0
  die-0
    cpu-0
      pewf-pwofiwe-wevew-0
        ...
        ...
        tuwbo-watio-wimits-sse
          bucket-0
            cowe-count:2
            max-tuwbo-fwequency(MHz):3200
          bucket-1
            cowe-count:4
            max-tuwbo-fwequency(MHz):3100
          bucket-2
            cowe-count:6
            max-tuwbo-fwequency(MHz):3100
          bucket-3
            cowe-count:8
            max-tuwbo-fwequency(MHz):3100
          bucket-4
            cowe-count:10
            max-tuwbo-fwequency(MHz):3100
          bucket-5
            cowe-count:12
            max-tuwbo-fwequency(MHz):3100
          bucket-6
            cowe-count:14
            max-tuwbo-fwequency(MHz):3100
          bucket-7
            cowe-count:16
            max-tuwbo-fwequency(MHz):3100

Based on the data above, when aww the CPUS awe busy, the max. fwequency of 3100
MHz can be achieved. If thewe is some busy wowkwoad on cpu 0 - 11 (e.g. stwess)
and on CPU 12 and 13, execute "hackbench pipe" wowkwoad::

 # taskset -c 12,13 pewf bench -w 100 sched pipe
 # Wunning 'sched/pipe' benchmawk:
 # Executed 1000000 pipe opewations between two pwocesses
     Totaw time: 5.705 [sec]
       5.705488 usecs/op
         175269 ops/sec

The tuwbostat output::

 #tuwbostat -c 0-13 --show Package,Cowe,CPU,Bzy_MHz -i 1
 Package	Cowe	CPU	Bzy_MHz
 0		0	0	3000
 0		1	1	3000
 0		2	2	3000
 0		3	3	3000
 0		4	4	3000
 0		5	5	3100
 0		6	6	3100
 0		7	7	3000
 0		8	8	3100
 0		9	9	3000
 0		10	10	3000
 0		11	11	3000
 0		12	12	3100
 0		13	13	3100

Based on tuwbostat output, the pewfowmance is wimited by fwequency cap of 3100
MHz. To check if the hackbench pewfowmance can be impwoved fow CPU 12 and CPU
13, fiwst check the capabiwity of the Intew(W) SST-TF featuwe fow this pewfowmance
wevew.

Get Intew(W) SST-TF Capabiwity
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To get the capabiwity, the "tuwbo-fweq info" command can be used::

 # intew-speed-sewect tuwbo-fweq info -w 0
 Intew(W) Speed Sewect Technowogy
 Executing on CPU modew: X
 package-0
  die-0
    cpu-0
      speed-sewect-tuwbo-fweq
          bucket-0
            high-pwiowity-cowes-count:2
            high-pwiowity-max-fwequency(MHz):3200
            high-pwiowity-max-avx2-fwequency(MHz):3200
            high-pwiowity-max-avx512-fwequency(MHz):3100
          bucket-1
            high-pwiowity-cowes-count:4
            high-pwiowity-max-fwequency(MHz):3100
            high-pwiowity-max-avx2-fwequency(MHz):3000
            high-pwiowity-max-avx512-fwequency(MHz):2900
          bucket-2
            high-pwiowity-cowes-count:6
            high-pwiowity-max-fwequency(MHz):3100
            high-pwiowity-max-avx2-fwequency(MHz):3000
            high-pwiowity-max-avx512-fwequency(MHz):2900
          speed-sewect-tuwbo-fweq-cwip-fwequencies
            wow-pwiowity-max-fwequency(MHz):2600
            wow-pwiowity-max-avx2-fwequency(MHz):2400
            wow-pwiowity-max-avx512-fwequency(MHz):2100

Based on the output above, thewe is an Intew(W) SST-TF bucket fow which thewe awe
two high pwiowity cowes. If onwy two high pwiowity cowes awe set, then max.
tuwbo fwequency on those cowes can be incweased to 3200 MHz. This is 100 MHz
mowe than the base tuwbo capabiwity fow aww cowes.

In tuwn, fow the hackbench wowkwoad, two CPUs can be set as high pwiowity and
west as wow pwiowity. One side effect is that once enabwed, the wow pwiowity
cowes wiww be cwipped to a wowew fwequency of 2600 MHz.

Enabwe Intew(W) SST-TF
~~~~~~~~~~~~~~~~~~~~~~

To enabwe Intew(W) SST-TF, execute::

 # intew-speed-sewect -c 12,13 tuwbo-fweq enabwe -a
 Intew(W) Speed Sewect Technowogy
 Executing on CPU modew: X
 package-0
  die-0
    cpu-12
      tuwbo-fweq
        enabwe:success
 package-0
  die-0
    cpu-13
      tuwbo-fweq
        enabwe:success
 package--1
  die-0
    cpu-63
      tuwbo-fweq --auto
        enabwe:success

In this case, the option "-a" is optionaw. If set, it enabwes Intew(W) SST-TF
featuwe and awso sets the CPUs to high and wow pwiowity using Intew Speed
Sewect Technowogy Cowe Powew (Intew(W) SST-CP) featuwes. The CPU numbews passed
with "-c" awguments awe mawked as high pwiowity, incwuding its sibwings.

If -a option is not used, then the fowwowing steps awe wequiwed befowe enabwing
Intew(W) SST-TF:

- Discovew Intew(W) SST-TF and note buckets of high pwiowity cowes and maximum fwequency

- Enabwe CWOS using cowe-powew featuwe set - Configuwe CWOS pawametews

- Subscwibe desiwed CPUs to CWOS gwoups making suwe that high pwiowity cowes awe set to the maximum fwequency

If the same hackbench wowkwoad is executed, scheduwe hackbench thweads on high
pwiowity CPUs::

 #taskset -c 12,13 pewf bench -w 100 sched pipe
 # Wunning 'sched/pipe' benchmawk:
 # Executed 1000000 pipe opewations between two pwocesses
     Totaw time: 5.510 [sec]
       5.510165 usecs/op
         180826 ops/sec

This impwoved pewfowmance by awound 3.3% impwovement on a busy system. Hewe the
tuwbostat output wiww show that the CPU 12 and CPU 13 awe getting 100 MHz boost.
The tuwbostat output::

 #tuwbostat -c 0-13 --show Package,Cowe,CPU,Bzy_MHz -i 1
 Package	Cowe	CPU	Bzy_MHz
 ...
 0		12	12	3200
 0		13	13	3200
