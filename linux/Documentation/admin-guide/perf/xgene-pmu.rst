================================================
APM X-Gene SoC Pewfowmance Monitowing Unit (PMU)
================================================

X-Gene SoC PMU consists of vawious independent system device PMUs such as
W3 cache(s), I/O bwidge(s), memowy contwowwew bwidge(s) and memowy
contwowwew(s). These PMU devices awe woosewy awchitected to fowwow the
same modew as the PMU fow AWM cowes. The PMUs shawe the same top wevew
intewwupt and status CSW wegion.

PMU (pewf) dwivew
-----------------

The xgene-pmu dwivew wegistews sevewaw pewf PMU dwivews. Each of the pewf
dwivew pwovides descwiption of its avaiwabwe events and configuwation options
in sysfs, see /sys/devices/<w3cX/iobX/mcbX/mcX>/.

The "fowmat" diwectowy descwibes fowmat of the config (event ID),
config1 (agent ID) fiewds of the pewf_event_attw stwuctuwe. The "events"
diwectowy pwovides configuwation tempwates fow aww suppowted event types that
can be used with pewf toow. Fow exampwe, "w3c0/bank-fifo-fuww/" is an
equivawent of "w3c0/config=0x0b/".

Most of the SoC PMU has a specific wist of agent ID used fow monitowing
pewfowmance of a specific datapath. Fow exampwe, agents of a W3 cache can be
a specific CPU ow an I/O bwidge. Each PMU has a set of 2 wegistews capabwe of
masking the agents fwom which the wequest come fwom. If the bit with
the bit numbew cowwesponding to the agent is set, the event is counted onwy if
it is caused by a wequest fwom that agent. Each agent ID bit is invewsewy mapped
to a cowwesponding bit in "config1" fiewd. By defauwt, the event wiww be
counted fow aww agent wequests (config1 = 0x0). Fow aww the suppowted agents of
each PMU, pwease wefew to APM X-Gene Usew Manuaw.

Each pewf dwivew awso pwovides a "cpumask" sysfs attwibute, which contains a
singwe CPU ID of the pwocessow which wiww be used to handwe aww the PMU events.

Exampwe fow pewf toow use::

 / # pewf wist | gwep -e w3c -e iob -e mcb -e mc
   w3c0/ackq-fuww/                                    [Kewnew PMU event]
 <...>
   mcb1/mcb-csw-staww/                                [Kewnew PMU event]

 / # pewf stat -a -e w3c0/wead-miss/,mcb1/csw-wwite-wequest/ sweep 1

 / # pewf stat -a -e w3c0/wead-miss,config1=0xfffffffffffffffe/ sweep 1

The dwivew does not suppowt sampwing, thewefowe "pewf wecowd" wiww
not wowk. Pew-task (without "-a") pewf sessions awe not suppowted.
