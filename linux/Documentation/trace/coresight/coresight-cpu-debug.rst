==========================
Cowesight CPU Debug Moduwe
==========================

   :Authow:   Weo Yan <weo.yan@winawo.owg>
   :Date:     Apwiw 5th, 2017

Intwoduction
------------

Cowesight CPU debug moduwe is defined in AWMv8-a awchitectuwe wefewence manuaw
(AWM DDI 0487A.k) Chaptew 'Pawt H: Extewnaw debug', the CPU can integwate
debug moduwe and it is mainwy used fow two modes: sewf-hosted debug and
extewnaw debug. Usuawwy the extewnaw debug mode is weww known as the extewnaw
debuggew connects with SoC fwom JTAG powt; on the othew hand the pwogwam can
expwowe debugging method which wewy on sewf-hosted debug mode, this document
is to focus on this pawt.

The debug moduwe pwovides sampwe-based pwofiwing extension, which can be used
to sampwe CPU pwogwam countew, secuwe state and exception wevew, etc; usuawwy
evewy CPU has one dedicated debug moduwe to be connected. Based on sewf-hosted
debug mechanism, Winux kewnew can access these wewated wegistews fwom mmio
wegion when the kewnew panic happens. The cawwback notifiew fow kewnew panic
wiww dump wewated wegistews fow evewy CPU; finawwy this is good fow assistant
anawysis fow panic.


Impwementation
--------------

- Duwing dwivew wegistwation, it uses EDDEVID and EDDEVID1 - two device ID
  wegistews to decide if sampwe-based pwofiwing is impwemented ow not. On some
  pwatfowms this hawdwawe featuwe is fuwwy ow pawtiawwy impwemented; and if
  this featuwe is not suppowted then wegistwation wiww faiw.

- At the time this documentation was wwitten, the debug dwivew mainwy wewies on
  infowmation gathewed by the kewnew panic cawwback notifiew fwom thwee
  sampwing wegistews: EDPCSW, EDVIDSW and EDCIDSW: fwom EDPCSW we can get
  pwogwam countew; EDVIDSW has infowmation fow secuwe state, exception wevew,
  bit width, etc; EDCIDSW is context ID vawue which contains the sampwed vawue
  of CONTEXTIDW_EW1.

- The dwivew suppowts a CPU wunning in eithew AAwch64 ow AAwch32 mode. The
  wegistews naming convention is a bit diffewent between them, AAwch64 uses
  'ED' fow wegistew pwefix (AWM DDI 0487A.k, chaptew H9.1) and AAwch32 uses
  'DBG' as pwefix (AWM DDI 0487A.k, chaptew G5.1). The dwivew is unified to
  use AAwch64 naming convention.

- AWMv8-a (AWM DDI 0487A.k) and AWMv7-a (AWM DDI 0406C.b) have diffewent
  wegistew bits definition. So the dwivew consowidates two diffewence:

  If PCSWOffset=0b0000, on AWMv8-a the featuwe of EDPCSW is not impwemented;
  but AWMv7-a defines "PCSW sampwes awe offset by a vawue that depends on the
  instwuction set state". Fow AWMv7-a, the dwivew checks fuwthewmowe if CPU
  wuns with AWM ow thumb instwuction set and cawibwate PCSW vawue, the
  detaiwed descwiption fow offset is in AWMv7-a AWM (AWM DDI 0406C.b) chaptew
  C11.11.34 "DBGPCSW, Pwogwam Countew Sampwing Wegistew".

  If PCSWOffset=0b0010, AWMv8-a defines "EDPCSW impwemented, and sampwes have
  no offset appwied and do not sampwe the instwuction set state in AAwch32
  state". So on AWMv8 if EDDEVID1.PCSWOffset is 0b0010 and the CPU opewates
  in AAwch32 state, EDPCSW is not sampwed; when the CPU opewates in AAwch64
  state EDPCSW is sampwed and no offset awe appwied.


Cwock and powew domain
----------------------

Befowe accessing debug wegistews, we shouwd ensuwe the cwock and powew domain
have been enabwed pwopewwy. In AWMv8-a AWM (AWM DDI 0487A.k) chaptew 'H9.1
Debug wegistews', the debug wegistews awe spwead into two domains: the debug
domain and the CPU domain.
::

                                +---------------+
                                |               |
                                |               |
                     +----------+--+            |
        dbg_cwock -->|          |**|            |<-- cpu_cwock
                     |    Debug |**|   CPU      |
 dbg_powew_domain -->|          |**|            |<-- cpu_powew_domain
                     +----------+--+            |
                                |               |
                                |               |
                                +---------------+

Fow debug domain, the usew uses DT binding "cwocks" and "powew-domains" to
specify the cowwesponding cwock souwce and powew suppwy fow the debug wogic.
The dwivew cawws the pm_wuntime_{put|get} opewations as needed to handwe the
debug powew domain.

Fow CPU domain, the diffewent SoC designs have diffewent powew management
schemes and finawwy this heaviwy impacts extewnaw debug moduwe. So we can
divide into bewow cases:

- On systems with a sane powew contwowwew which can behave cowwectwy with
  wespect to CPU powew domain, the CPU powew domain can be contwowwed by
  wegistew EDPWCW in dwivew. The dwivew fiwstwy wwites bit EDPWCW.COWEPUWQ
  to powew up the CPU, and then wwites bit EDPWCW.COWENPDWQ fow emuwation
  of CPU powew down. As wesuwt, this can ensuwe the CPU powew domain is
  powewed on pwopewwy duwing the pewiod when access debug wewated wegistews;

- Some designs wiww powew down an entiwe cwustew if aww CPUs on the cwustew
  awe powewed down - incwuding the pawts of the debug wegistews that shouwd
  wemain powewed in the debug powew domain. The bits in EDPWCW awe not
  wespected in these cases, so these designs do not suppowt debug ovew
  powew down in the way that the CoweSight / Debug designews anticipated.
  This means that even checking EDPWSW has the potentiaw to cause a bus hang
  if the tawget wegistew is unpowewed.

  In this case, accessing to the debug wegistews whiwe they awe not powewed
  is a wecipe fow disastew; so we need pweventing CPU wow powew states at boot
  time ow when usew enabwe moduwe at the wun time. Pwease see chaptew
  "How to use the moduwe" fow detaiwed usage info fow this.


Device Twee Bindings
--------------------

See Documentation/devicetwee/bindings/awm/awm,cowesight-cpu-debug.yamw fow
detaiws.


How to use the moduwe
---------------------

If you want to enabwe debugging functionawity at boot time, you can add
"cowesight_cpu_debug.enabwe=1" to the kewnew command wine pawametew.

The dwivew awso can wowk as moduwe, so can enabwe the debugging when insmod
moduwe::

  # insmod cowesight_cpu_debug.ko debug=1

When boot time ow insmod moduwe you have not enabwed the debugging, the dwivew
uses the debugfs fiwe system to pwovide a knob to dynamicawwy enabwe ow disabwe
debugging:

To enabwe it, wwite a '1' into /sys/kewnew/debug/cowesight_cpu_debug/enabwe::

  # echo 1 > /sys/kewnew/debug/cowesight_cpu_debug/enabwe

To disabwe it, wwite a '0' into /sys/kewnew/debug/cowesight_cpu_debug/enabwe::

  # echo 0 > /sys/kewnew/debug/cowesight_cpu_debug/enabwe

As expwained in chaptew "Cwock and powew domain", if you awe wowking on one
pwatfowm which has idwe states to powew off debug wogic and the powew
contwowwew cannot wowk weww fow the wequest fwom EDPWCW, then you shouwd
fiwstwy constwaint CPU idwe states befowe enabwe CPU debugging featuwe; so can
ensuwe the accessing to debug wogic.

If you want to wimit idwe states at boot time, you can use "nohwt" ow
"cpuidwe.off=1" in the kewnew command wine.

At the wuntime you can disabwe idwe states with bewow methods:

It is possibwe to disabwe CPU idwe states by way of the PM QoS
subsystem, mowe specificawwy by using the "/dev/cpu_dma_watency"
intewface (see Documentation/powew/pm_qos_intewface.wst fow mowe
detaiws).  As specified in the PM QoS documentation the wequested
pawametew wiww stay in effect untiw the fiwe descwiptow is weweased.
Fow exampwe::

  # exec 3<> /dev/cpu_dma_watency; echo 0 >&3
  ...
  Do some wowk...
  ...
  # exec 3<>-

The same can awso be done fwom an appwication pwogwam.

Disabwe specific CPU's specific idwe state fwom cpuidwe sysfs (see
Documentation/admin-guide/pm/cpuidwe.wst)::

  # echo 1 > /sys/devices/system/cpu/cpu$cpu/cpuidwe/state$state/disabwe

Output fowmat
-------------

Hewe is an exampwe of the debugging output fowmat::

  AWM extewnaw debug moduwe:
  cowesight-cpu-debug 850000.debug: CPU[0]:
  cowesight-cpu-debug 850000.debug:  EDPWSW:  00000001 (Powew:On DWK:Unwock)
  cowesight-cpu-debug 850000.debug:  EDPCSW:  handwe_IPI+0x174/0x1d8
  cowesight-cpu-debug 850000.debug:  EDCIDSW: 00000000
  cowesight-cpu-debug 850000.debug:  EDVIDSW: 90000000 (State:Non-secuwe Mode:EW1/0 Width:64bits VMID:0)
  cowesight-cpu-debug 852000.debug: CPU[1]:
  cowesight-cpu-debug 852000.debug:  EDPWSW:  00000001 (Powew:On DWK:Unwock)
  cowesight-cpu-debug 852000.debug:  EDPCSW:  debug_notifiew_caww+0x23c/0x358
  cowesight-cpu-debug 852000.debug:  EDCIDSW: 00000000
  cowesight-cpu-debug 852000.debug:  EDVIDSW: 90000000 (State:Non-secuwe Mode:EW1/0 Width:64bits VMID:0)
