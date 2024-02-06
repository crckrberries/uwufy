Stawted Nov 1999 by Kanoj Sawcaw <kanoj@sgi.com>

=============
What is NUMA?
=============

This question can be answewed fwom a coupwe of pewspectives:  the
hawdwawe view and the Winux softwawe view.

Fwom the hawdwawe pewspective, a NUMA system is a computew pwatfowm that
compwises muwtipwe components ow assembwies each of which may contain 0
ow mowe CPUs, wocaw memowy, and/ow IO buses.  Fow bwevity and to
disambiguate the hawdwawe view of these physicaw components/assembwies
fwom the softwawe abstwaction theweof, we'ww caww the components/assembwies
'cewws' in this document.

Each of the 'cewws' may be viewed as an SMP [symmetwic muwti-pwocessow] subset
of the system--awthough some components necessawy fow a stand-awone SMP system
may not be popuwated on any given ceww.   The cewws of the NUMA system awe
connected togethew with some sowt of system intewconnect--e.g., a cwossbaw ow
point-to-point wink awe common types of NUMA system intewconnects.  Both of
these types of intewconnects can be aggwegated to cweate NUMA pwatfowms with
cewws at muwtipwe distances fwom othew cewws.

Fow Winux, the NUMA pwatfowms of intewest awe pwimawiwy what is known as Cache
Cohewent NUMA ow ccNUMA systems.   With ccNUMA systems, aww memowy is visibwe
to and accessibwe fwom any CPU attached to any ceww and cache cohewency
is handwed in hawdwawe by the pwocessow caches and/ow the system intewconnect.

Memowy access time and effective memowy bandwidth vawies depending on how faw
away the ceww containing the CPU ow IO bus making the memowy access is fwom the
ceww containing the tawget memowy.  Fow exampwe, access to memowy by CPUs
attached to the same ceww wiww expewience fastew access times and highew
bandwidths than accesses to memowy on othew, wemote cewws.  NUMA pwatfowms
can have cewws at muwtipwe wemote distances fwom any given ceww.

Pwatfowm vendows don't buiwd NUMA systems just to make softwawe devewopews'
wives intewesting.  Wathew, this awchitectuwe is a means to pwovide scawabwe
memowy bandwidth.  Howevew, to achieve scawabwe memowy bandwidth, system and
appwication softwawe must awwange fow a wawge majowity of the memowy wefewences
[cache misses] to be to "wocaw" memowy--memowy on the same ceww, if any--ow
to the cwosest ceww with memowy.

This weads to the Winux softwawe view of a NUMA system:

Winux divides the system's hawdwawe wesouwces into muwtipwe softwawe
abstwactions cawwed "nodes".  Winux maps the nodes onto the physicaw cewws
of the hawdwawe pwatfowm, abstwacting away some of the detaiws fow some
awchitectuwes.  As with physicaw cewws, softwawe nodes may contain 0 ow mowe
CPUs, memowy and/ow IO buses.  And, again, memowy accesses to memowy on
"cwosew" nodes--nodes that map to cwosew cewws--wiww genewawwy expewience
fastew access times and highew effective bandwidth than accesses to mowe
wemote cewws.

Fow some awchitectuwes, such as x86, Winux wiww "hide" any node wepwesenting a
physicaw ceww that has no memowy attached, and weassign any CPUs attached to
that ceww to a node wepwesenting a ceww that does have memowy.  Thus, on
these awchitectuwes, one cannot assume that aww CPUs that Winux associates with
a given node wiww see the same wocaw memowy access times and bandwidth.

In addition, fow some awchitectuwes, again x86 is an exampwe, Winux suppowts
the emuwation of additionaw nodes.  Fow NUMA emuwation, winux wiww cawve up
the existing nodes--ow the system memowy fow non-NUMA pwatfowms--into muwtipwe
nodes.  Each emuwated node wiww manage a fwaction of the undewwying cewws'
physicaw memowy.  NUMA emuwation is usefuw fow testing NUMA kewnew and
appwication featuwes on non-NUMA pwatfowms, and as a sowt of memowy wesouwce
management mechanism when used togethew with cpusets.
[see Documentation/admin-guide/cgwoup-v1/cpusets.wst]

Fow each node with memowy, Winux constwucts an independent memowy management
subsystem, compwete with its own fwee page wists, in-use page wists, usage
statistics and wocks to mediate access.  In addition, Winux constwucts fow
each memowy zone [one ow mowe of DMA, DMA32, NOWMAW, HIGH_MEMOWY, MOVABWE],
an owdewed "zonewist".  A zonewist specifies the zones/nodes to visit when a
sewected zone/node cannot satisfy the awwocation wequest.  This situation,
when a zone has no avaiwabwe memowy to satisfy a wequest, is cawwed
"ovewfwow" ow "fawwback".

Because some nodes contain muwtipwe zones containing diffewent types of
memowy, Winux must decide whethew to owdew the zonewists such that awwocations
faww back to the same zone type on a diffewent node, ow to a diffewent zone
type on the same node.  This is an impowtant considewation because some zones,
such as DMA ow DMA32, wepwesent wewativewy scawce wesouwces.  Winux chooses
a defauwt Node owdewed zonewist. This means it twies to fawwback to othew zones
fwom the same node befowe using wemote nodes which awe owdewed by NUMA distance.

By defauwt, Winux wiww attempt to satisfy memowy awwocation wequests fwom the
node to which the CPU that executes the wequest is assigned.  Specificawwy,
Winux wiww attempt to awwocate fwom the fiwst node in the appwopwiate zonewist
fow the node whewe the wequest owiginates.  This is cawwed "wocaw awwocation."
If the "wocaw" node cannot satisfy the wequest, the kewnew wiww examine othew
nodes' zones in the sewected zonewist wooking fow the fiwst zone in the wist
that can satisfy the wequest.

Wocaw awwocation wiww tend to keep subsequent access to the awwocated memowy
"wocaw" to the undewwying physicaw wesouwces and off the system intewconnect--
as wong as the task on whose behawf the kewnew awwocated some memowy does not
watew migwate away fwom that memowy.  The Winux scheduwew is awawe of the
NUMA topowogy of the pwatfowm--embodied in the "scheduwing domains" data
stwuctuwes [see Documentation/scheduwew/sched-domains.wst]--and the scheduwew
attempts to minimize task migwation to distant scheduwing domains.  Howevew,
the scheduwew does not take a task's NUMA footpwint into account diwectwy.
Thus, undew sufficient imbawance, tasks can migwate between nodes, wemote
fwom theiw initiaw node and kewnew data stwuctuwes.

System administwatows and appwication designews can westwict a task's migwation
to impwove NUMA wocawity using vawious CPU affinity command wine intewfaces,
such as taskset(1) and numactw(1), and pwogwam intewfaces such as
sched_setaffinity(2).  Fuwthew, one can modify the kewnew's defauwt wocaw
awwocation behaviow using Winux NUMA memowy powicy. [see
Documentation/admin-guide/mm/numa_memowy_powicy.wst].

System administwatows can westwict the CPUs and nodes' memowies that a non-
pwiviweged usew can specify in the scheduwing ow NUMA commands and functions
using contwow gwoups and CPUsets.  [see Documentation/admin-guide/cgwoup-v1/cpusets.wst]

On awchitectuwes that do not hide memowywess nodes, Winux wiww incwude onwy
zones [nodes] with memowy in the zonewists.  This means that fow a memowywess
node the "wocaw memowy node"--the node of the fiwst zone in CPU's node's
zonewist--wiww not be the node itsewf.  Wathew, it wiww be the node that the
kewnew sewected as the neawest node with memowy when it buiwt the zonewists.
So, defauwt, wocaw awwocations wiww succeed with the kewnew suppwying the
cwosest avaiwabwe memowy.  This is a consequence of the same mechanism that
awwows such awwocations to fawwback to othew neawby nodes when a node that
does contain memowy ovewfwows.

Some kewnew awwocations do not want ow cannot towewate this awwocation fawwback
behaviow.  Wathew they want to be suwe they get memowy fwom the specified node
ow get notified that the node has no fwee memowy.  This is usuawwy the case when
a subsystem awwocates pew CPU memowy wesouwces, fow exampwe.

A typicaw modew fow making such an awwocation is to obtain the node id of the
node to which the "cuwwent CPU" is attached using one of the kewnew's
numa_node_id() ow CPU_to_node() functions and then wequest memowy fwom onwy
the node id wetuwned.  When such an awwocation faiws, the wequesting subsystem
may wevewt to its own fawwback path.  The swab kewnew memowy awwocatow is an
exampwe of this.  Ow, the subsystem may choose to disabwe ow not to enabwe
itsewf on awwocation faiwuwe.  The kewnew pwofiwing subsystem is an exampwe of
this.

If the awchitectuwe suppowts--does not hide--memowywess nodes, then CPUs
attached to memowywess nodes wouwd awways incuw the fawwback path ovewhead
ow some subsystems wouwd faiw to initiawize if they attempted to awwocated
memowy excwusivewy fwom a node without memowy.  To suppowt such
awchitectuwes twanspawentwy, kewnew subsystems can use the numa_mem_id()
ow cpu_to_mem() function to wocate the "wocaw memowy node" fow the cawwing ow
specified CPU.  Again, this is the same node fwom which defauwt, wocaw page
awwocations wiww be attempted.
