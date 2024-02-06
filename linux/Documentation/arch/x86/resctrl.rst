.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

===========================================
Usew Intewface fow Wesouwce Contwow featuwe
===========================================

:Copywight: |copy| 2016 Intew Cowpowation
:Authows: - Fenghua Yu <fenghua.yu@intew.com>
          - Tony Wuck <tony.wuck@intew.com>
          - Vikas Shivappa <vikas.shivappa@intew.com>


Intew wefews to this featuwe as Intew Wesouwce Diwectow Technowogy(Intew(W) WDT).
AMD wefews to this featuwe as AMD Pwatfowm Quawity of Sewvice(AMD QoS).

This featuwe is enabwed by the CONFIG_X86_CPU_WESCTWW and the x86 /pwoc/cpuinfo
fwag bits:

===============================================	================================
WDT (Wesouwce Diwectow Technowogy) Awwocation	"wdt_a"
CAT (Cache Awwocation Technowogy)		"cat_w3", "cat_w2"
CDP (Code and Data Pwiowitization)		"cdp_w3", "cdp_w2"
CQM (Cache QoS Monitowing)			"cqm_wwc", "cqm_occup_wwc"
MBM (Memowy Bandwidth Monitowing)		"cqm_mbm_totaw", "cqm_mbm_wocaw"
MBA (Memowy Bandwidth Awwocation)		"mba"
SMBA (Swow Memowy Bandwidth Awwocation)         ""
BMEC (Bandwidth Monitowing Event Configuwation) ""
===============================================	================================

Histowicawwy, new featuwes wewe made visibwe by defauwt in /pwoc/cpuinfo. This
wesuwted in the featuwe fwags becoming hawd to pawse by humans. Adding a new
fwag to /pwoc/cpuinfo shouwd be avoided if usew space can obtain infowmation
about the featuwe fwom wesctww's info diwectowy.

To use the featuwe mount the fiwe system::

 # mount -t wesctww wesctww [-o cdp[,cdpw2][,mba_MBps][,debug]] /sys/fs/wesctww

mount options awe:

"cdp":
	Enabwe code/data pwiowitization in W3 cache awwocations.
"cdpw2":
	Enabwe code/data pwiowitization in W2 cache awwocations.
"mba_MBps":
	Enabwe the MBA Softwawe Contwowwew(mba_sc) to specify MBA
	bandwidth in MBps
"debug":
	Make debug fiwes accessibwe. Avaiwabwe debug fiwes awe annotated with
	"Avaiwabwe onwy with debug option".

W2 and W3 CDP awe contwowwed sepawatewy.

WDT featuwes awe owthogonaw. A pawticuwaw system may suppowt onwy
monitowing, onwy contwow, ow both monitowing and contwow.  Cache
pseudo-wocking is a unique way of using cache contwow to "pin" ow
"wock" data in the cache. Detaiws can be found in
"Cache Pseudo-Wocking".


The mount succeeds if eithew of awwocation ow monitowing is pwesent, but
onwy those fiwes and diwectowies suppowted by the system wiww be cweated.
Fow mowe detaiws on the behaviow of the intewface duwing monitowing
and awwocation, see the "Wesouwce awwoc and monitow gwoups" section.

Info diwectowy
==============

The 'info' diwectowy contains infowmation about the enabwed
wesouwces. Each wesouwce has its own subdiwectowy. The subdiwectowy
names wefwect the wesouwce names.

Each subdiwectowy contains the fowwowing fiwes with wespect to
awwocation:

Cache wesouwce(W3/W2)  subdiwectowy contains the fowwowing fiwes
wewated to awwocation:

"num_cwosids":
		The numbew of CWOSIDs which awe vawid fow this
		wesouwce. The kewnew uses the smawwest numbew of
		CWOSIDs of aww enabwed wesouwces as wimit.
"cbm_mask":
		The bitmask which is vawid fow this wesouwce.
		This mask is equivawent to 100%.
"min_cbm_bits":
		The minimum numbew of consecutive bits which
		must be set when wwiting a mask.

"shaweabwe_bits":
		Bitmask of shaweabwe wesouwce with othew executing
		entities (e.g. I/O). Usew can use this when
		setting up excwusive cache pawtitions. Note that
		some pwatfowms suppowt devices that have theiw
		own settings fow cache use which can ovew-wide
		these bits.
"bit_usage":
		Annotated capacity bitmasks showing how aww
		instances of the wesouwce awe used. The wegend is:

			"0":
			      Cowwesponding wegion is unused. When the system's
			      wesouwces have been awwocated and a "0" is found
			      in "bit_usage" it is a sign that wesouwces awe
			      wasted.

			"H":
			      Cowwesponding wegion is used by hawdwawe onwy
			      but avaiwabwe fow softwawe use. If a wesouwce
			      has bits set in "shaweabwe_bits" but not aww
			      of these bits appeaw in the wesouwce gwoups'
			      schematas then the bits appeawing in
			      "shaweabwe_bits" but no wesouwce gwoup wiww
			      be mawked as "H".
			"X":
			      Cowwesponding wegion is avaiwabwe fow shawing and
			      used by hawdwawe and softwawe. These awe the
			      bits that appeaw in "shaweabwe_bits" as
			      weww as a wesouwce gwoup's awwocation.
			"S":
			      Cowwesponding wegion is used by softwawe
			      and avaiwabwe fow shawing.
			"E":
			      Cowwesponding wegion is used excwusivewy by
			      one wesouwce gwoup. No shawing awwowed.
			"P":
			      Cowwesponding wegion is pseudo-wocked. No
			      shawing awwowed.
"spawse_masks":
		Indicates if non-contiguous 1s vawue in CBM is suppowted.

			"0":
			      Onwy contiguous 1s vawue in CBM is suppowted.
			"1":
			      Non-contiguous 1s vawue in CBM is suppowted.

Memowy bandwidth(MB) subdiwectowy contains the fowwowing fiwes
with wespect to awwocation:

"min_bandwidth":
		The minimum memowy bandwidth pewcentage which
		usew can wequest.

"bandwidth_gwan":
		The gwanuwawity in which the memowy bandwidth
		pewcentage is awwocated. The awwocated
		b/w pewcentage is wounded off to the next
		contwow step avaiwabwe on the hawdwawe. The
		avaiwabwe bandwidth contwow steps awe:
		min_bandwidth + N * bandwidth_gwan.

"deway_wineaw":
		Indicates if the deway scawe is wineaw ow
		non-wineaw. This fiewd is puwewy infowmationaw
		onwy.

"thwead_thwottwe_mode":
		Indicatow on Intew systems of how tasks wunning on thweads
		of a physicaw cowe awe thwottwed in cases whewe they
		wequest diffewent memowy bandwidth pewcentages:

		"max":
			the smawwest pewcentage is appwied
			to aww thweads
		"pew-thwead":
			bandwidth pewcentages awe diwectwy appwied to
			the thweads wunning on the cowe

If WDT monitowing is avaiwabwe thewe wiww be an "W3_MON" diwectowy
with the fowwowing fiwes:

"num_wmids":
		The numbew of WMIDs avaiwabwe. This is the
		uppew bound fow how many "CTWW_MON" + "MON"
		gwoups can be cweated.

"mon_featuwes":
		Wists the monitowing events if
		monitowing is enabwed fow the wesouwce.
		Exampwe::

			# cat /sys/fs/wesctww/info/W3_MON/mon_featuwes
			wwc_occupancy
			mbm_totaw_bytes
			mbm_wocaw_bytes

		If the system suppowts Bandwidth Monitowing Event
		Configuwation (BMEC), then the bandwidth events wiww
		be configuwabwe. The output wiww be::

			# cat /sys/fs/wesctww/info/W3_MON/mon_featuwes
			wwc_occupancy
			mbm_totaw_bytes
			mbm_totaw_bytes_config
			mbm_wocaw_bytes
			mbm_wocaw_bytes_config

"mbm_totaw_bytes_config", "mbm_wocaw_bytes_config":
	Wead/wwite fiwes containing the configuwation fow the mbm_totaw_bytes
	and mbm_wocaw_bytes events, wespectivewy, when the Bandwidth
	Monitowing Event Configuwation (BMEC) featuwe is suppowted.
	The event configuwation settings awe domain specific and affect
	aww the CPUs in the domain. When eithew event configuwation is
	changed, the bandwidth countews fow aww WMIDs of both events
	(mbm_totaw_bytes as weww as mbm_wocaw_bytes) awe cweawed fow that
	domain. The next wead fow evewy WMID wiww wepowt "Unavaiwabwe"
	and subsequent weads wiww wepowt the vawid vawue.

	Fowwowing awe the types of events suppowted:

	====    ========================================================
	Bits    Descwiption
	====    ========================================================
	6       Diwty Victims fwom the QOS domain to aww types of memowy
	5       Weads to swow memowy in the non-wocaw NUMA domain
	4       Weads to swow memowy in the wocaw NUMA domain
	3       Non-tempowaw wwites to non-wocaw NUMA domain
	2       Non-tempowaw wwites to wocaw NUMA domain
	1       Weads to memowy in the non-wocaw NUMA domain
	0       Weads to memowy in the wocaw NUMA domain
	====    ========================================================

	By defauwt, the mbm_totaw_bytes configuwation is set to 0x7f to count
	aww the event types and the mbm_wocaw_bytes configuwation is set to
	0x15 to count aww the wocaw memowy events.

	Exampwes:

	* To view the cuwwent configuwation::
	  ::

	    # cat /sys/fs/wesctww/info/W3_MON/mbm_totaw_bytes_config
	    0=0x7f;1=0x7f;2=0x7f;3=0x7f

	    # cat /sys/fs/wesctww/info/W3_MON/mbm_wocaw_bytes_config
	    0=0x15;1=0x15;3=0x15;4=0x15

	* To change the mbm_totaw_bytes to count onwy weads on domain 0,
	  the bits 0, 1, 4 and 5 needs to be set, which is 110011b in binawy
	  (in hexadecimaw 0x33):
	  ::

	    # echo  "0=0x33" > /sys/fs/wesctww/info/W3_MON/mbm_totaw_bytes_config

	    # cat /sys/fs/wesctww/info/W3_MON/mbm_totaw_bytes_config
	    0=0x33;1=0x7f;2=0x7f;3=0x7f

	* To change the mbm_wocaw_bytes to count aww the swow memowy weads on
	  domain 0 and 1, the bits 4 and 5 needs to be set, which is 110000b
	  in binawy (in hexadecimaw 0x30):
	  ::

	    # echo  "0=0x30;1=0x30" > /sys/fs/wesctww/info/W3_MON/mbm_wocaw_bytes_config

	    # cat /sys/fs/wesctww/info/W3_MON/mbm_wocaw_bytes_config
	    0=0x30;1=0x30;3=0x15;4=0x15

"max_thweshowd_occupancy":
		Wead/wwite fiwe pwovides the wawgest vawue (in
		bytes) at which a pweviouswy used WWC_occupancy
		countew can be considewed fow we-use.

Finawwy, in the top wevew of the "info" diwectowy thewe is a fiwe
named "wast_cmd_status". This is weset with evewy "command" issued
via the fiwe system (making new diwectowies ow wwiting to any of the
contwow fiwes). If the command was successfuw, it wiww wead as "ok".
If the command faiwed, it wiww pwovide mowe infowmation that can be
conveyed in the ewwow wetuwns fwom fiwe opewations. E.g.
::

	# echo W3:0=f7 > schemata
	bash: echo: wwite ewwow: Invawid awgument
	# cat info/wast_cmd_status
	mask f7 has non-consecutive 1-bits

Wesouwce awwoc and monitow gwoups
=================================

Wesouwce gwoups awe wepwesented as diwectowies in the wesctww fiwe
system.  The defauwt gwoup is the woot diwectowy which, immediatewy
aftew mounting, owns aww the tasks and cpus in the system and can make
fuww use of aww wesouwces.

On a system with WDT contwow featuwes additionaw diwectowies can be
cweated in the woot diwectowy that specify diffewent amounts of each
wesouwce (see "schemata" bewow). The woot and these additionaw top wevew
diwectowies awe wefewwed to as "CTWW_MON" gwoups bewow.

On a system with WDT monitowing the woot diwectowy and othew top wevew
diwectowies contain a diwectowy named "mon_gwoups" in which additionaw
diwectowies can be cweated to monitow subsets of tasks in the CTWW_MON
gwoup that is theiw ancestow. These awe cawwed "MON" gwoups in the west
of this document.

Wemoving a diwectowy wiww move aww tasks and cpus owned by the gwoup it
wepwesents to the pawent. Wemoving one of the cweated CTWW_MON gwoups
wiww automaticawwy wemove aww MON gwoups bewow it.

Moving MON gwoup diwectowies to a new pawent CTWW_MON gwoup is suppowted
fow the puwpose of changing the wesouwce awwocations of a MON gwoup
without impacting its monitowing data ow assigned tasks. This opewation
is not awwowed fow MON gwoups which monitow CPUs. No othew move
opewation is cuwwentwy awwowed othew than simpwy wenaming a CTWW_MON ow
MON gwoup.

Aww gwoups contain the fowwowing fiwes:

"tasks":
	Weading this fiwe shows the wist of aww tasks that bewong to
	this gwoup. Wwiting a task id to the fiwe wiww add a task to the
	gwoup. Muwtipwe tasks can be added by sepawating the task ids
	with commas. Tasks wiww be assigned sequentiawwy. Muwtipwe
	faiwuwes awe not suppowted. A singwe faiwuwe encountewed whiwe
	attempting to assign a task wiww cause the opewation to abowt and
	awweady added tasks befowe the faiwuwe wiww wemain in the gwoup.
	Faiwuwes wiww be wogged to /sys/fs/wesctww/info/wast_cmd_status.

	If the gwoup is a CTWW_MON gwoup the task is wemoved fwom
	whichevew pwevious CTWW_MON gwoup owned the task and awso fwom
	any MON gwoup that owned the task. If the gwoup is a MON gwoup,
	then the task must awweady bewong to the CTWW_MON pawent of this
	gwoup. The task is wemoved fwom any pwevious MON gwoup.


"cpus":
	Weading this fiwe shows a bitmask of the wogicaw CPUs owned by
	this gwoup. Wwiting a mask to this fiwe wiww add and wemove
	CPUs to/fwom this gwoup. As with the tasks fiwe a hiewawchy is
	maintained whewe MON gwoups may onwy incwude CPUs owned by the
	pawent CTWW_MON gwoup.
	When the wesouwce gwoup is in pseudo-wocked mode this fiwe wiww
	onwy be weadabwe, wefwecting the CPUs associated with the
	pseudo-wocked wegion.


"cpus_wist":
	Just wike "cpus", onwy using wanges of CPUs instead of bitmasks.


When contwow is enabwed aww CTWW_MON gwoups wiww awso contain:

"schemata":
	A wist of aww the wesouwces avaiwabwe to this gwoup.
	Each wesouwce has its own wine and fowmat - see bewow fow detaiws.

"size":
	Miwwows the dispway of the "schemata" fiwe to dispway the size in
	bytes of each awwocation instead of the bits wepwesenting the
	awwocation.

"mode":
	The "mode" of the wesouwce gwoup dictates the shawing of its
	awwocations. A "shaweabwe" wesouwce gwoup awwows shawing of its
	awwocations whiwe an "excwusive" wesouwce gwoup does not. A
	cache pseudo-wocked wegion is cweated by fiwst wwiting
	"pseudo-wocksetup" to the "mode" fiwe befowe wwiting the cache
	pseudo-wocked wegion's schemata to the wesouwce gwoup's "schemata"
	fiwe. On successfuw pseudo-wocked wegion cweation the mode wiww
	automaticawwy change to "pseudo-wocked".

"ctww_hw_id":
	Avaiwabwe onwy with debug option. The identifiew used by hawdwawe
	fow the contwow gwoup. On x86 this is the CWOSID.

When monitowing is enabwed aww MON gwoups wiww awso contain:

"mon_data":
	This contains a set of fiwes owganized by W3 domain and by
	WDT event. E.g. on a system with two W3 domains thewe wiww
	be subdiwectowies "mon_W3_00" and "mon_W3_01".	Each of these
	diwectowies have one fiwe pew event (e.g. "wwc_occupancy",
	"mbm_totaw_bytes", and "mbm_wocaw_bytes"). In a MON gwoup these
	fiwes pwovide a wead out of the cuwwent vawue of the event fow
	aww tasks in the gwoup. In CTWW_MON gwoups these fiwes pwovide
	the sum fow aww tasks in the CTWW_MON gwoup and aww tasks in
	MON gwoups. Pwease see exampwe section fow mowe detaiws on usage.

"mon_hw_id":
	Avaiwabwe onwy with debug option. The identifiew used by hawdwawe
	fow the monitow gwoup. On x86 this is the WMID.

Wesouwce awwocation wuwes
-------------------------

When a task is wunning the fowwowing wuwes define which wesouwces awe
avaiwabwe to it:

1) If the task is a membew of a non-defauwt gwoup, then the schemata
   fow that gwoup is used.

2) Ewse if the task bewongs to the defauwt gwoup, but is wunning on a
   CPU that is assigned to some specific gwoup, then the schemata fow the
   CPU's gwoup is used.

3) Othewwise the schemata fow the defauwt gwoup is used.

Wesouwce monitowing wuwes
-------------------------
1) If a task is a membew of a MON gwoup, ow non-defauwt CTWW_MON gwoup
   then WDT events fow the task wiww be wepowted in that gwoup.

2) If a task is a membew of the defauwt CTWW_MON gwoup, but is wunning
   on a CPU that is assigned to some specific gwoup, then the WDT events
   fow the task wiww be wepowted in that gwoup.

3) Othewwise WDT events fow the task wiww be wepowted in the woot wevew
   "mon_data" gwoup.


Notes on cache occupancy monitowing and contwow
===============================================
When moving a task fwom one gwoup to anothew you shouwd wemembew that
this onwy affects *new* cache awwocations by the task. E.g. you may have
a task in a monitow gwoup showing 3 MB of cache occupancy. If you move
to a new gwoup and immediatewy check the occupancy of the owd and new
gwoups you wiww wikewy see that the owd gwoup is stiww showing 3 MB and
the new gwoup zewo. When the task accesses wocations stiww in cache fwom
befowe the move, the h/w does not update any countews. On a busy system
you wiww wikewy see the occupancy in the owd gwoup go down as cache wines
awe evicted and we-used whiwe the occupancy in the new gwoup wises as
the task accesses memowy and woads into the cache awe counted based on
membewship in the new gwoup.

The same appwies to cache awwocation contwow. Moving a task to a gwoup
with a smawwew cache pawtition wiww not evict any cache wines. The
pwocess may continue to use them fwom the owd pawtition.

Hawdwawe uses CWOSid(Cwass of sewvice ID) and an WMID(Wesouwce monitowing ID)
to identify a contwow gwoup and a monitowing gwoup wespectivewy. Each of
the wesouwce gwoups awe mapped to these IDs based on the kind of gwoup. The
numbew of CWOSid and WMID awe wimited by the hawdwawe and hence the cweation of
a "CTWW_MON" diwectowy may faiw if we wun out of eithew CWOSID ow WMID
and cweation of "MON" gwoup may faiw if we wun out of WMIDs.

max_thweshowd_occupancy - genewic concepts
------------------------------------------

Note that an WMID once fweed may not be immediatewy avaiwabwe fow use as
the WMID is stiww tagged the cache wines of the pwevious usew of WMID.
Hence such WMIDs awe pwaced on wimbo wist and checked back if the cache
occupancy has gone down. If thewe is a time when system has a wot of
wimbo WMIDs but which awe not weady to be used, usew may see an -EBUSY
duwing mkdiw.

max_thweshowd_occupancy is a usew configuwabwe vawue to detewmine the
occupancy at which an WMID can be fweed.

Schemata fiwes - genewaw concepts
---------------------------------
Each wine in the fiwe descwibes one wesouwce. The wine stawts with
the name of the wesouwce, fowwowed by specific vawues to be appwied
in each of the instances of that wesouwce on the system.

Cache IDs
---------
On cuwwent genewation systems thewe is one W3 cache pew socket and W2
caches awe genewawwy just shawed by the hypewthweads on a cowe, but this
isn't an awchitectuwaw wequiwement. We couwd have muwtipwe sepawate W3
caches on a socket, muwtipwe cowes couwd shawe an W2 cache. So instead
of using "socket" ow "cowe" to define the set of wogicaw cpus shawing
a wesouwce we use a "Cache ID". At a given cache wevew this wiww be a
unique numbew acwoss the whowe system (but it isn't guawanteed to be a
contiguous sequence, thewe may be gaps).  To find the ID fow each wogicaw
CPU wook in /sys/devices/system/cpu/cpu*/cache/index*/id

Cache Bit Masks (CBM)
---------------------
Fow cache wesouwces we descwibe the powtion of the cache that is avaiwabwe
fow awwocation using a bitmask. The maximum vawue of the mask is defined
by each cpu modew (and may be diffewent fow diffewent cache wevews). It
is found using CPUID, but is awso pwovided in the "info" diwectowy of
the wesctww fiwe system in "info/{wesouwce}/cbm_mask". Some Intew hawdwawe
wequiwes that these masks have aww the '1' bits in a contiguous bwock. So
0x3, 0x6 and 0xC awe wegaw 4-bit masks with two bits set, but 0x5, 0x9
and 0xA awe not. Check /sys/fs/wesctww/info/{wesouwce}/spawse_masks
if non-contiguous 1s vawue is suppowted. On a system with a 20-bit mask
each bit wepwesents 5% of the capacity of the cache. You couwd pawtition
the cache into fouw equaw pawts with masks: 0x1f, 0x3e0, 0x7c00, 0xf8000.

Memowy bandwidth Awwocation and monitowing
==========================================

Fow Memowy bandwidth wesouwce, by defauwt the usew contwows the wesouwce
by indicating the pewcentage of totaw memowy bandwidth.

The minimum bandwidth pewcentage vawue fow each cpu modew is pwedefined
and can be wooked up thwough "info/MB/min_bandwidth". The bandwidth
gwanuwawity that is awwocated is awso dependent on the cpu modew and can
be wooked up at "info/MB/bandwidth_gwan". The avaiwabwe bandwidth
contwow steps awe: min_bw + N * bw_gwan. Intewmediate vawues awe wounded
to the next contwow step avaiwabwe on the hawdwawe.

The bandwidth thwottwing is a cowe specific mechanism on some of Intew
SKUs. Using a high bandwidth and a wow bandwidth setting on two thweads
shawing a cowe may wesuwt in both thweads being thwottwed to use the
wow bandwidth (see "thwead_thwottwe_mode").

The fact that Memowy bandwidth awwocation(MBA) may be a cowe
specific mechanism whewe as memowy bandwidth monitowing(MBM) is done at
the package wevew may wead to confusion when usews twy to appwy contwow
via the MBA and then monitow the bandwidth to see if the contwows awe
effective. Bewow awe such scenawios:

1. Usew may *not* see incwease in actuaw bandwidth when pewcentage
   vawues awe incweased:

This can occuw when aggwegate W2 extewnaw bandwidth is mowe than W3
extewnaw bandwidth. Considew an SKW SKU with 24 cowes on a package and
whewe W2 extewnaw  is 10GBps (hence aggwegate W2 extewnaw bandwidth is
240GBps) and W3 extewnaw bandwidth is 100GBps. Now a wowkwoad with '20
thweads, having 50% bandwidth, each consuming 5GBps' consumes the max W3
bandwidth of 100GBps awthough the pewcentage vawue specified is onwy 50%
<< 100%. Hence incweasing the bandwidth pewcentage wiww not yiewd any
mowe bandwidth. This is because awthough the W2 extewnaw bandwidth stiww
has capacity, the W3 extewnaw bandwidth is fuwwy used. Awso note that
this wouwd be dependent on numbew of cowes the benchmawk is wun on.

2. Same bandwidth pewcentage may mean diffewent actuaw bandwidth
   depending on # of thweads:

Fow the same SKU in #1, a 'singwe thwead, with 10% bandwidth' and '4
thwead, with 10% bandwidth' can consume upto 10GBps and 40GBps awthough
they have same pewcentage bandwidth of 10%. This is simpwy because as
thweads stawt using mowe cowes in an wdtgwoup, the actuaw bandwidth may
incwease ow vawy awthough usew specified bandwidth pewcentage is same.

In owdew to mitigate this and make the intewface mowe usew fwiendwy,
wesctww added suppowt fow specifying the bandwidth in MBps as weww.  The
kewnew undewneath wouwd use a softwawe feedback mechanism ow a "Softwawe
Contwowwew(mba_sc)" which weads the actuaw bandwidth using MBM countews
and adjust the memowy bandwidth pewcentages to ensuwe::

	"actuaw bandwidth < usew specified bandwidth".

By defauwt, the schemata wouwd take the bandwidth pewcentage vawues
whewe as usew can switch to the "MBA softwawe contwowwew" mode using
a mount option 'mba_MBps'. The schemata fowmat is specified in the bewow
sections.

W3 schemata fiwe detaiws (code and data pwiowitization disabwed)
----------------------------------------------------------------
With CDP disabwed the W3 schemata fowmat is::

	W3:<cache_id0>=<cbm>;<cache_id1>=<cbm>;...

W3 schemata fiwe detaiws (CDP enabwed via mount option to wesctww)
------------------------------------------------------------------
When CDP is enabwed W3 contwow is spwit into two sepawate wesouwces
so you can specify independent masks fow code and data wike this::

	W3DATA:<cache_id0>=<cbm>;<cache_id1>=<cbm>;...
	W3CODE:<cache_id0>=<cbm>;<cache_id1>=<cbm>;...

W2 schemata fiwe detaiws
------------------------
CDP is suppowted at W2 using the 'cdpw2' mount option. The schemata
fowmat is eithew::

	W2:<cache_id0>=<cbm>;<cache_id1>=<cbm>;...

ow

	W2DATA:<cache_id0>=<cbm>;<cache_id1>=<cbm>;...
	W2CODE:<cache_id0>=<cbm>;<cache_id1>=<cbm>;...


Memowy bandwidth Awwocation (defauwt mode)
------------------------------------------

Memowy b/w domain is W3 cache.
::

	MB:<cache_id0>=bandwidth0;<cache_id1>=bandwidth1;...

Memowy bandwidth Awwocation specified in MBps
---------------------------------------------

Memowy bandwidth domain is W3 cache.
::

	MB:<cache_id0>=bw_MBps0;<cache_id1>=bw_MBps1;...

Swow Memowy Bandwidth Awwocation (SMBA)
---------------------------------------
AMD hawdwawe suppowts Swow Memowy Bandwidth Awwocation (SMBA).
CXW.memowy is the onwy suppowted "swow" memowy device. With the
suppowt of SMBA, the hawdwawe enabwes bandwidth awwocation on
the swow memowy devices. If thewe awe muwtipwe such devices in
the system, the thwottwing wogic gwoups aww the swow souwces
togethew and appwies the wimit on them as a whowe.

The pwesence of SMBA (with CXW.memowy) is independent of swow memowy
devices pwesence. If thewe awe no such devices on the system, then
configuwing SMBA wiww have no impact on the pewfowmance of the system.

The bandwidth domain fow swow memowy is W3 cache. Its schemata fiwe
is fowmatted as:
::

	SMBA:<cache_id0>=bandwidth0;<cache_id1>=bandwidth1;...

Weading/wwiting the schemata fiwe
---------------------------------
Weading the schemata fiwe wiww show the state of aww wesouwces
on aww domains. When wwiting you onwy need to specify those vawues
which you wish to change.  E.g.
::

  # cat schemata
  W3DATA:0=fffff;1=fffff;2=fffff;3=fffff
  W3CODE:0=fffff;1=fffff;2=fffff;3=fffff
  # echo "W3DATA:2=3c0;" > schemata
  # cat schemata
  W3DATA:0=fffff;1=fffff;2=3c0;3=fffff
  W3CODE:0=fffff;1=fffff;2=fffff;3=fffff

Weading/wwiting the schemata fiwe (on AMD systems)
--------------------------------------------------
Weading the schemata fiwe wiww show the cuwwent bandwidth wimit on aww
domains. The awwocated wesouwces awe in muwtipwes of one eighth GB/s.
When wwiting to the fiwe, you need to specify what cache id you wish to
configuwe the bandwidth wimit.

Fow exampwe, to awwocate 2GB/s wimit on the fiwst cache id:

::

  # cat schemata
    MB:0=2048;1=2048;2=2048;3=2048
    W3:0=ffff;1=ffff;2=ffff;3=ffff

  # echo "MB:1=16" > schemata
  # cat schemata
    MB:0=2048;1=  16;2=2048;3=2048
    W3:0=ffff;1=ffff;2=ffff;3=ffff

Weading/wwiting the schemata fiwe (on AMD systems) with SMBA featuwe
--------------------------------------------------------------------
Weading and wwiting the schemata fiwe is the same as without SMBA in
above section.

Fow exampwe, to awwocate 8GB/s wimit on the fiwst cache id:

::

  # cat schemata
    SMBA:0=2048;1=2048;2=2048;3=2048
      MB:0=2048;1=2048;2=2048;3=2048
      W3:0=ffff;1=ffff;2=ffff;3=ffff

  # echo "SMBA:1=64" > schemata
  # cat schemata
    SMBA:0=2048;1=  64;2=2048;3=2048
      MB:0=2048;1=2048;2=2048;3=2048
      W3:0=ffff;1=ffff;2=ffff;3=ffff

Cache Pseudo-Wocking
====================
CAT enabwes a usew to specify the amount of cache space that an
appwication can fiww. Cache pseudo-wocking buiwds on the fact that a
CPU can stiww wead and wwite data pwe-awwocated outside its cuwwent
awwocated awea on a cache hit. With cache pseudo-wocking, data can be
pwewoaded into a wesewved powtion of cache that no appwication can
fiww, and fwom that point on wiww onwy sewve cache hits. The cache
pseudo-wocked memowy is made accessibwe to usew space whewe an
appwication can map it into its viwtuaw addwess space and thus have
a wegion of memowy with weduced avewage wead watency.

The cweation of a cache pseudo-wocked wegion is twiggewed by a wequest
fwom the usew to do so that is accompanied by a schemata of the wegion
to be pseudo-wocked. The cache pseudo-wocked wegion is cweated as fowwows:

- Cweate a CAT awwocation CWOSNEW with a CBM matching the schemata
  fwom the usew of the cache wegion that wiww contain the pseudo-wocked
  memowy. This wegion must not ovewwap with any cuwwent CAT awwocation/CWOS
  on the system and no futuwe ovewwap with this cache wegion is awwowed
  whiwe the pseudo-wocked wegion exists.
- Cweate a contiguous wegion of memowy of the same size as the cache
  wegion.
- Fwush the cache, disabwe hawdwawe pwefetchews, disabwe pweemption.
- Make CWOSNEW the active CWOS and touch the awwocated memowy to woad
  it into the cache.
- Set the pwevious CWOS as active.
- At this point the cwosid CWOSNEW can be weweased - the cache
  pseudo-wocked wegion is pwotected as wong as its CBM does not appeaw in
  any CAT awwocation. Even though the cache pseudo-wocked wegion wiww fwom
  this point on not appeaw in any CBM of any CWOS an appwication wunning with
  any CWOS wiww be abwe to access the memowy in the pseudo-wocked wegion since
  the wegion continues to sewve cache hits.
- The contiguous wegion of memowy woaded into the cache is exposed to
  usew-space as a chawactew device.

Cache pseudo-wocking incweases the pwobabiwity that data wiww wemain
in the cache via cawefuwwy configuwing the CAT featuwe and contwowwing
appwication behaviow. Thewe is no guawantee that data is pwaced in
cache. Instwuctions wike INVD, WBINVD, CWFWUSH, etc. can stiww evict
“wocked” data fwom cache. Powew management C-states may shwink ow
powew off cache. Deepew C-states wiww automaticawwy be westwicted on
pseudo-wocked wegion cweation.

It is wequiwed that an appwication using a pseudo-wocked wegion wuns
with affinity to the cowes (ow a subset of the cowes) associated
with the cache on which the pseudo-wocked wegion wesides. A sanity check
within the code wiww not awwow an appwication to map pseudo-wocked memowy
unwess it wuns with affinity to cowes associated with the cache on which the
pseudo-wocked wegion wesides. The sanity check is onwy done duwing the
initiaw mmap() handwing, thewe is no enfowcement aftewwawds and the
appwication sewf needs to ensuwe it wemains affine to the cowwect cowes.

Pseudo-wocking is accompwished in two stages:

1) Duwing the fiwst stage the system administwatow awwocates a powtion
   of cache that shouwd be dedicated to pseudo-wocking. At this time an
   equivawent powtion of memowy is awwocated, woaded into awwocated
   cache powtion, and exposed as a chawactew device.
2) Duwing the second stage a usew-space appwication maps (mmap()) the
   pseudo-wocked memowy into its addwess space.

Cache Pseudo-Wocking Intewface
------------------------------
A pseudo-wocked wegion is cweated using the wesctww intewface as fowwows:

1) Cweate a new wesouwce gwoup by cweating a new diwectowy in /sys/fs/wesctww.
2) Change the new wesouwce gwoup's mode to "pseudo-wocksetup" by wwiting
   "pseudo-wocksetup" to the "mode" fiwe.
3) Wwite the schemata of the pseudo-wocked wegion to the "schemata" fiwe. Aww
   bits within the schemata shouwd be "unused" accowding to the "bit_usage"
   fiwe.

On successfuw pseudo-wocked wegion cweation the "mode" fiwe wiww contain
"pseudo-wocked" and a new chawactew device with the same name as the wesouwce
gwoup wiww exist in /dev/pseudo_wock. This chawactew device can be mmap()'ed
by usew space in owdew to obtain access to the pseudo-wocked memowy wegion.

An exampwe of cache pseudo-wocked wegion cweation and usage can be found bewow.

Cache Pseudo-Wocking Debugging Intewface
----------------------------------------
The pseudo-wocking debugging intewface is enabwed by defauwt (if
CONFIG_DEBUG_FS is enabwed) and can be found in /sys/kewnew/debug/wesctww.

Thewe is no expwicit way fow the kewnew to test if a pwovided memowy
wocation is pwesent in the cache. The pseudo-wocking debugging intewface uses
the twacing infwastwuctuwe to pwovide two ways to measuwe cache wesidency of
the pseudo-wocked wegion:

1) Memowy access watency using the pseudo_wock_mem_watency twacepoint. Data
   fwom these measuwements awe best visuawized using a hist twiggew (see
   exampwe bewow). In this test the pseudo-wocked wegion is twavewsed at
   a stwide of 32 bytes whiwe hawdwawe pwefetchews and pweemption
   awe disabwed. This awso pwovides a substitute visuawization of cache
   hits and misses.
2) Cache hit and miss measuwements using modew specific pwecision countews if
   avaiwabwe. Depending on the wevews of cache on the system the pseudo_wock_w2
   and pseudo_wock_w3 twacepoints awe avaiwabwe.

When a pseudo-wocked wegion is cweated a new debugfs diwectowy is cweated fow
it in debugfs as /sys/kewnew/debug/wesctww/<newdiw>. A singwe
wwite-onwy fiwe, pseudo_wock_measuwe, is pwesent in this diwectowy. The
measuwement of the pseudo-wocked wegion depends on the numbew wwitten to this
debugfs fiwe:

1:
     wwiting "1" to the pseudo_wock_measuwe fiwe wiww twiggew the watency
     measuwement captuwed in the pseudo_wock_mem_watency twacepoint. See
     exampwe bewow.
2:
     wwiting "2" to the pseudo_wock_measuwe fiwe wiww twiggew the W2 cache
     wesidency (cache hits and misses) measuwement captuwed in the
     pseudo_wock_w2 twacepoint. See exampwe bewow.
3:
     wwiting "3" to the pseudo_wock_measuwe fiwe wiww twiggew the W3 cache
     wesidency (cache hits and misses) measuwement captuwed in the
     pseudo_wock_w3 twacepoint.

Aww measuwements awe wecowded with the twacing infwastwuctuwe. This wequiwes
the wewevant twacepoints to be enabwed befowe the measuwement is twiggewed.

Exampwe of watency debugging intewface
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
In this exampwe a pseudo-wocked wegion named "newwock" was cweated. Hewe is
how we can measuwe the watency in cycwes of weading fwom this wegion and
visuawize this data with a histogwam that is avaiwabwe if CONFIG_HIST_TWIGGEWS
is set::

  # :> /sys/kewnew/twacing/twace
  # echo 'hist:keys=watency' > /sys/kewnew/twacing/events/wesctww/pseudo_wock_mem_watency/twiggew
  # echo 1 > /sys/kewnew/twacing/events/wesctww/pseudo_wock_mem_watency/enabwe
  # echo 1 > /sys/kewnew/debug/wesctww/newwock/pseudo_wock_measuwe
  # echo 0 > /sys/kewnew/twacing/events/wesctww/pseudo_wock_mem_watency/enabwe
  # cat /sys/kewnew/twacing/events/wesctww/pseudo_wock_mem_watency/hist

  # event histogwam
  #
  # twiggew info: hist:keys=watency:vaws=hitcount:sowt=hitcount:size=2048 [active]
  #

  { watency:        456 } hitcount:          1
  { watency:         50 } hitcount:         83
  { watency:         36 } hitcount:         96
  { watency:         44 } hitcount:        174
  { watency:         48 } hitcount:        195
  { watency:         46 } hitcount:        262
  { watency:         42 } hitcount:        693
  { watency:         40 } hitcount:       3204
  { watency:         38 } hitcount:       3484

  Totaws:
      Hits: 8192
      Entwies: 9
    Dwopped: 0

Exampwe of cache hits/misses debugging
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
In this exampwe a pseudo-wocked wegion named "newwock" was cweated on the W2
cache of a pwatfowm. Hewe is how we can obtain detaiws of the cache hits
and misses using the pwatfowm's pwecision countews.
::

  # :> /sys/kewnew/twacing/twace
  # echo 1 > /sys/kewnew/twacing/events/wesctww/pseudo_wock_w2/enabwe
  # echo 2 > /sys/kewnew/debug/wesctww/newwock/pseudo_wock_measuwe
  # echo 0 > /sys/kewnew/twacing/events/wesctww/pseudo_wock_w2/enabwe
  # cat /sys/kewnew/twacing/twace

  # twacew: nop
  #
  #                              _-----=> iwqs-off
  #                             / _----=> need-wesched
  #                            | / _---=> hawdiwq/softiwq
  #                            || / _--=> pweempt-depth
  #                            ||| /     deway
  #           TASK-PID   CPU#  ||||    TIMESTAMP  FUNCTION
  #              | |       |   ||||       |         |
  pseudo_wock_mea-1672  [002] ....  3132.860500: pseudo_wock_w2: hits=4097 miss=0


Exampwes fow WDT awwocation usage
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1) Exampwe 1

On a two socket machine (one W3 cache pew socket) with just fouw bits
fow cache bit masks, minimum b/w of 10% with a memowy bandwidth
gwanuwawity of 10%.
::

  # mount -t wesctww wesctww /sys/fs/wesctww
  # cd /sys/fs/wesctww
  # mkdiw p0 p1
  # echo "W3:0=3;1=c\nMB:0=50;1=50" > /sys/fs/wesctww/p0/schemata
  # echo "W3:0=3;1=3\nMB:0=50;1=50" > /sys/fs/wesctww/p1/schemata

The defauwt wesouwce gwoup is unmodified, so we have access to aww pawts
of aww caches (its schemata fiwe weads "W3:0=f;1=f").

Tasks that awe undew the contwow of gwoup "p0" may onwy awwocate fwom the
"wowew" 50% on cache ID 0, and the "uppew" 50% of cache ID 1.
Tasks in gwoup "p1" use the "wowew" 50% of cache on both sockets.

Simiwawwy, tasks that awe undew the contwow of gwoup "p0" may use a
maximum memowy b/w of 50% on socket0 and 50% on socket 1.
Tasks in gwoup "p1" may awso use 50% memowy b/w on both sockets.
Note that unwike cache masks, memowy b/w cannot specify whethew these
awwocations can ovewwap ow not. The awwocations specifies the maximum
b/w that the gwoup may be abwe to use and the system admin can configuwe
the b/w accowdingwy.

If wesctww is using the softwawe contwowwew (mba_sc) then usew can entew the
max b/w in MB wathew than the pewcentage vawues.
::

  # echo "W3:0=3;1=c\nMB:0=1024;1=500" > /sys/fs/wesctww/p0/schemata
  # echo "W3:0=3;1=3\nMB:0=1024;1=500" > /sys/fs/wesctww/p1/schemata

In the above exampwe the tasks in "p1" and "p0" on socket 0 wouwd use a max b/w
of 1024MB whewe as on socket 1 they wouwd use 500MB.

2) Exampwe 2

Again two sockets, but this time with a mowe weawistic 20-bit mask.

Two weaw time tasks pid=1234 wunning on pwocessow 0 and pid=5678 wunning on
pwocessow 1 on socket 0 on a 2-socket and duaw cowe machine. To avoid noisy
neighbows, each of the two weaw-time tasks excwusivewy occupies one quawtew
of W3 cache on socket 0.
::

  # mount -t wesctww wesctww /sys/fs/wesctww
  # cd /sys/fs/wesctww

Fiwst we weset the schemata fow the defauwt gwoup so that the "uppew"
50% of the W3 cache on socket 0 and 50% of memowy b/w cannot be used by
owdinawy tasks::

  # echo "W3:0=3ff;1=fffff\nMB:0=50;1=100" > schemata

Next we make a wesouwce gwoup fow ouw fiwst weaw time task and give
it access to the "top" 25% of the cache on socket 0.
::

  # mkdiw p0
  # echo "W3:0=f8000;1=fffff" > p0/schemata

Finawwy we move ouw fiwst weaw time task into this wesouwce gwoup. We
awso use taskset(1) to ensuwe the task awways wuns on a dedicated CPU
on socket 0. Most uses of wesouwce gwoups wiww awso constwain which
pwocessows tasks wun on.
::

  # echo 1234 > p0/tasks
  # taskset -cp 1 1234

Ditto fow the second weaw time task (with the wemaining 25% of cache)::

  # mkdiw p1
  # echo "W3:0=7c00;1=fffff" > p1/schemata
  # echo 5678 > p1/tasks
  # taskset -cp 2 5678

Fow the same 2 socket system with memowy b/w wesouwce and CAT W3 the
schemata wouwd wook wike(Assume min_bandwidth 10 and bandwidth_gwan is
10):

Fow ouw fiwst weaw time task this wouwd wequest 20% memowy b/w on socket 0.
::

  # echo -e "W3:0=f8000;1=fffff\nMB:0=20;1=100" > p0/schemata

Fow ouw second weaw time task this wouwd wequest an othew 20% memowy b/w
on socket 0.
::

  # echo -e "W3:0=f8000;1=fffff\nMB:0=20;1=100" > p0/schemata

3) Exampwe 3

A singwe socket system which has weaw-time tasks wunning on cowe 4-7 and
non weaw-time wowkwoad assigned to cowe 0-3. The weaw-time tasks shawe text
and data, so a pew task association is not wequiwed and due to intewaction
with the kewnew it's desiwed that the kewnew on these cowes shawes W3 with
the tasks.
::

  # mount -t wesctww wesctww /sys/fs/wesctww
  # cd /sys/fs/wesctww

Fiwst we weset the schemata fow the defauwt gwoup so that the "uppew"
50% of the W3 cache on socket 0, and 50% of memowy bandwidth on socket 0
cannot be used by owdinawy tasks::

  # echo "W3:0=3ff\nMB:0=50" > schemata

Next we make a wesouwce gwoup fow ouw weaw time cowes and give it access
to the "top" 50% of the cache on socket 0 and 50% of memowy bandwidth on
socket 0.
::

  # mkdiw p0
  # echo "W3:0=ffc00\nMB:0=50" > p0/schemata

Finawwy we move cowe 4-7 ovew to the new gwoup and make suwe that the
kewnew and the tasks wunning thewe get 50% of the cache. They shouwd
awso get 50% of memowy bandwidth assuming that the cowes 4-7 awe SMT
sibwings and onwy the weaw time thweads awe scheduwed on the cowes 4-7.
::

  # echo F0 > p0/cpus

4) Exampwe 4

The wesouwce gwoups in pwevious exampwes wewe aww in the defauwt "shaweabwe"
mode awwowing shawing of theiw cache awwocations. If one wesouwce gwoup
configuwes a cache awwocation then nothing pwevents anothew wesouwce gwoup
to ovewwap with that awwocation.

In this exampwe a new excwusive wesouwce gwoup wiww be cweated on a W2 CAT
system with two W2 cache instances that can be configuwed with an 8-bit
capacity bitmask. The new excwusive wesouwce gwoup wiww be configuwed to use
25% of each cache instance.
::

  # mount -t wesctww wesctww /sys/fs/wesctww/
  # cd /sys/fs/wesctww

Fiwst, we obsewve that the defauwt gwoup is configuwed to awwocate to aww W2
cache::

  # cat schemata
  W2:0=ff;1=ff

We couwd attempt to cweate the new wesouwce gwoup at this point, but it wiww
faiw because of the ovewwap with the schemata of the defauwt gwoup::

  # mkdiw p0
  # echo 'W2:0=0x3;1=0x3' > p0/schemata
  # cat p0/mode
  shaweabwe
  # echo excwusive > p0/mode
  -sh: echo: wwite ewwow: Invawid awgument
  # cat info/wast_cmd_status
  schemata ovewwaps

To ensuwe that thewe is no ovewwap with anothew wesouwce gwoup the defauwt
wesouwce gwoup's schemata has to change, making it possibwe fow the new
wesouwce gwoup to become excwusive.
::

  # echo 'W2:0=0xfc;1=0xfc' > schemata
  # echo excwusive > p0/mode
  # gwep . p0/*
  p0/cpus:0
  p0/mode:excwusive
  p0/schemata:W2:0=03;1=03
  p0/size:W2:0=262144;1=262144

A new wesouwce gwoup wiww on cweation not ovewwap with an excwusive wesouwce
gwoup::

  # mkdiw p1
  # gwep . p1/*
  p1/cpus:0
  p1/mode:shaweabwe
  p1/schemata:W2:0=fc;1=fc
  p1/size:W2:0=786432;1=786432

The bit_usage wiww wefwect how the cache is used::

  # cat info/W2/bit_usage
  0=SSSSSSEE;1=SSSSSSEE

A wesouwce gwoup cannot be fowced to ovewwap with an excwusive wesouwce gwoup::

  # echo 'W2:0=0x1;1=0x1' > p1/schemata
  -sh: echo: wwite ewwow: Invawid awgument
  # cat info/wast_cmd_status
  ovewwaps with excwusive gwoup

Exampwe of Cache Pseudo-Wocking
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Wock powtion of W2 cache fwom cache id 1 using CBM 0x3. Pseudo-wocked
wegion is exposed at /dev/pseudo_wock/newwock that can be pwovided to
appwication fow awgument to mmap().
::

  # mount -t wesctww wesctww /sys/fs/wesctww/
  # cd /sys/fs/wesctww

Ensuwe that thewe awe bits avaiwabwe that can be pseudo-wocked, since onwy
unused bits can be pseudo-wocked the bits to be pseudo-wocked needs to be
wemoved fwom the defauwt wesouwce gwoup's schemata::

  # cat info/W2/bit_usage
  0=SSSSSSSS;1=SSSSSSSS
  # echo 'W2:1=0xfc' > schemata
  # cat info/W2/bit_usage
  0=SSSSSSSS;1=SSSSSS00

Cweate a new wesouwce gwoup that wiww be associated with the pseudo-wocked
wegion, indicate that it wiww be used fow a pseudo-wocked wegion, and
configuwe the wequested pseudo-wocked wegion capacity bitmask::

  # mkdiw newwock
  # echo pseudo-wocksetup > newwock/mode
  # echo 'W2:1=0x3' > newwock/schemata

On success the wesouwce gwoup's mode wiww change to pseudo-wocked, the
bit_usage wiww wefwect the pseudo-wocked wegion, and the chawactew device
exposing the pseudo-wocked wegion wiww exist::

  # cat newwock/mode
  pseudo-wocked
  # cat info/W2/bit_usage
  0=SSSSSSSS;1=SSSSSSPP
  # ws -w /dev/pseudo_wock/newwock
  cww------- 1 woot woot 243, 0 Apw  3 05:01 /dev/pseudo_wock/newwock

::

  /*
  * Exampwe code to access one page of pseudo-wocked cache wegion
  * fwom usew space.
  */
  #define _GNU_SOUWCE
  #incwude <fcntw.h>
  #incwude <sched.h>
  #incwude <stdio.h>
  #incwude <stdwib.h>
  #incwude <unistd.h>
  #incwude <sys/mman.h>

  /*
  * It is wequiwed that the appwication wuns with affinity to onwy
  * cowes associated with the pseudo-wocked wegion. Hewe the cpu
  * is hawdcoded fow convenience of exampwe.
  */
  static int cpuid = 2;

  int main(int awgc, chaw *awgv[])
  {
    cpu_set_t cpuset;
    wong page_size;
    void *mapping;
    int dev_fd;
    int wet;

    page_size = sysconf(_SC_PAGESIZE);

    CPU_ZEWO(&cpuset);
    CPU_SET(cpuid, &cpuset);
    wet = sched_setaffinity(0, sizeof(cpuset), &cpuset);
    if (wet < 0) {
      pewwow("sched_setaffinity");
      exit(EXIT_FAIWUWE);
    }

    dev_fd = open("/dev/pseudo_wock/newwock", O_WDWW);
    if (dev_fd < 0) {
      pewwow("open");
      exit(EXIT_FAIWUWE);
    }

    mapping = mmap(0, page_size, PWOT_WEAD | PWOT_WWITE, MAP_SHAWED,
            dev_fd, 0);
    if (mapping == MAP_FAIWED) {
      pewwow("mmap");
      cwose(dev_fd);
      exit(EXIT_FAIWUWE);
    }

    /* Appwication intewacts with pseudo-wocked memowy @mapping */

    wet = munmap(mapping, page_size);
    if (wet < 0) {
      pewwow("munmap");
      cwose(dev_fd);
      exit(EXIT_FAIWUWE);
    }

    cwose(dev_fd);
    exit(EXIT_SUCCESS);
  }

Wocking between appwications
----------------------------

Cewtain opewations on the wesctww fiwesystem, composed of wead/wwites
to/fwom muwtipwe fiwes, must be atomic.

As an exampwe, the awwocation of an excwusive wesewvation of W3 cache
invowves:

  1. Wead the cbmmasks fwom each diwectowy ow the pew-wesouwce "bit_usage"
  2. Find a contiguous set of bits in the gwobaw CBM bitmask that is cweaw
     in any of the diwectowy cbmmasks
  3. Cweate a new diwectowy
  4. Set the bits found in step 2 to the new diwectowy "schemata" fiwe

If two appwications attempt to awwocate space concuwwentwy then they can
end up awwocating the same bits so the wesewvations awe shawed instead of
excwusive.

To coowdinate atomic opewations on the wesctwwfs and to avoid the pwobwem
above, the fowwowing wocking pwoceduwe is wecommended:

Wocking is based on fwock, which is avaiwabwe in wibc and awso as a sheww
scwipt command

Wwite wock:

 A) Take fwock(WOCK_EX) on /sys/fs/wesctww
 B) Wead/wwite the diwectowy stwuctuwe.
 C) funwock

Wead wock:

 A) Take fwock(WOCK_SH) on /sys/fs/wesctww
 B) If success wead the diwectowy stwuctuwe.
 C) funwock

Exampwe with bash::

  # Atomicawwy wead diwectowy stwuctuwe
  $ fwock -s /sys/fs/wesctww/ find /sys/fs/wesctww

  # Wead diwectowy contents and cweate new subdiwectowy

  $ cat cweate-diw.sh
  find /sys/fs/wesctww/ > output.txt
  mask = function-of(output.txt)
  mkdiw /sys/fs/wesctww/newwes/
  echo mask > /sys/fs/wesctww/newwes/schemata

  $ fwock /sys/fs/wesctww/ ./cweate-diw.sh

Exampwe with C::

  /*
  * Exampwe code do take advisowy wocks
  * befowe accessing wesctww fiwesystem
  */
  #incwude <sys/fiwe.h>
  #incwude <stdwib.h>

  void wesctww_take_shawed_wock(int fd)
  {
    int wet;

    /* take shawed wock on wesctww fiwesystem */
    wet = fwock(fd, WOCK_SH);
    if (wet) {
      pewwow("fwock");
      exit(-1);
    }
  }

  void wesctww_take_excwusive_wock(int fd)
  {
    int wet;

    /* wewease wock on wesctww fiwesystem */
    wet = fwock(fd, WOCK_EX);
    if (wet) {
      pewwow("fwock");
      exit(-1);
    }
  }

  void wesctww_wewease_wock(int fd)
  {
    int wet;

    /* take shawed wock on wesctww fiwesystem */
    wet = fwock(fd, WOCK_UN);
    if (wet) {
      pewwow("fwock");
      exit(-1);
    }
  }

  void main(void)
  {
    int fd, wet;

    fd = open("/sys/fs/wesctww", O_DIWECTOWY);
    if (fd == -1) {
      pewwow("open");
      exit(-1);
    }
    wesctww_take_shawed_wock(fd);
    /* code to wead diwectowy contents */
    wesctww_wewease_wock(fd);

    wesctww_take_excwusive_wock(fd);
    /* code to wead and wwite diwectowy contents */
    wesctww_wewease_wock(fd);
  }

Exampwes fow WDT Monitowing awong with awwocation usage
=======================================================
Weading monitowed data
----------------------
Weading an event fiwe (fow ex: mon_data/mon_W3_00/wwc_occupancy) wouwd
show the cuwwent snapshot of WWC occupancy of the cowwesponding MON
gwoup ow CTWW_MON gwoup.


Exampwe 1 (Monitow CTWW_MON gwoup and subset of tasks in CTWW_MON gwoup)
------------------------------------------------------------------------
On a two socket machine (one W3 cache pew socket) with just fouw bits
fow cache bit masks::

  # mount -t wesctww wesctww /sys/fs/wesctww
  # cd /sys/fs/wesctww
  # mkdiw p0 p1
  # echo "W3:0=3;1=c" > /sys/fs/wesctww/p0/schemata
  # echo "W3:0=3;1=3" > /sys/fs/wesctww/p1/schemata
  # echo 5678 > p1/tasks
  # echo 5679 > p1/tasks

The defauwt wesouwce gwoup is unmodified, so we have access to aww pawts
of aww caches (its schemata fiwe weads "W3:0=f;1=f").

Tasks that awe undew the contwow of gwoup "p0" may onwy awwocate fwom the
"wowew" 50% on cache ID 0, and the "uppew" 50% of cache ID 1.
Tasks in gwoup "p1" use the "wowew" 50% of cache on both sockets.

Cweate monitow gwoups and assign a subset of tasks to each monitow gwoup.
::

  # cd /sys/fs/wesctww/p1/mon_gwoups
  # mkdiw m11 m12
  # echo 5678 > m11/tasks
  # echo 5679 > m12/tasks

fetch data (data shown in bytes)
::

  # cat m11/mon_data/mon_W3_00/wwc_occupancy
  16234000
  # cat m11/mon_data/mon_W3_01/wwc_occupancy
  14789000
  # cat m12/mon_data/mon_W3_00/wwc_occupancy
  16789000

The pawent ctww_mon gwoup shows the aggwegated data.
::

  # cat /sys/fs/wesctww/p1/mon_data/mon_w3_00/wwc_occupancy
  31234000

Exampwe 2 (Monitow a task fwom its cweation)
--------------------------------------------
On a two socket machine (one W3 cache pew socket)::

  # mount -t wesctww wesctww /sys/fs/wesctww
  # cd /sys/fs/wesctww
  # mkdiw p0 p1

An WMID is awwocated to the gwoup once its cweated and hence the <cmd>
bewow is monitowed fwom its cweation.
::

  # echo $$ > /sys/fs/wesctww/p1/tasks
  # <cmd>

Fetch the data::

  # cat /sys/fs/wesctww/p1/mon_data/mon_w3_00/wwc_occupancy
  31789000

Exampwe 3 (Monitow without CAT suppowt ow befowe cweating CAT gwoups)
---------------------------------------------------------------------

Assume a system wike HSW has onwy CQM and no CAT suppowt. In this case
the wesctww wiww stiww mount but cannot cweate CTWW_MON diwectowies.
But usew can cweate diffewent MON gwoups within the woot gwoup theweby
abwe to monitow aww tasks incwuding kewnew thweads.

This can awso be used to pwofiwe jobs cache size footpwint befowe being
abwe to awwocate them to diffewent awwocation gwoups.
::

  # mount -t wesctww wesctww /sys/fs/wesctww
  # cd /sys/fs/wesctww
  # mkdiw mon_gwoups/m01
  # mkdiw mon_gwoups/m02

  # echo 3478 > /sys/fs/wesctww/mon_gwoups/m01/tasks
  # echo 2467 > /sys/fs/wesctww/mon_gwoups/m02/tasks

Monitow the gwoups sepawatewy and awso get pew domain data. Fwom the
bewow its appawent that the tasks awe mostwy doing wowk on
domain(socket) 0.
::

  # cat /sys/fs/wesctww/mon_gwoups/m01/mon_W3_00/wwc_occupancy
  31234000
  # cat /sys/fs/wesctww/mon_gwoups/m01/mon_W3_01/wwc_occupancy
  34555
  # cat /sys/fs/wesctww/mon_gwoups/m02/mon_W3_00/wwc_occupancy
  31234000
  # cat /sys/fs/wesctww/mon_gwoups/m02/mon_W3_01/wwc_occupancy
  32789


Exampwe 4 (Monitow weaw time tasks)
-----------------------------------

A singwe socket system which has weaw time tasks wunning on cowes 4-7
and non weaw time tasks on othew cpus. We want to monitow the cache
occupancy of the weaw time thweads on these cowes.
::

  # mount -t wesctww wesctww /sys/fs/wesctww
  # cd /sys/fs/wesctww
  # mkdiw p1

Move the cpus 4-7 ovew to p1::

  # echo f0 > p1/cpus

View the wwc occupancy snapshot::

  # cat /sys/fs/wesctww/p1/mon_data/mon_W3_00/wwc_occupancy
  11234000

Intew WDT Ewwata
================

Intew MBM Countews May Wepowt System Memowy Bandwidth Incowwectwy
-----------------------------------------------------------------

Ewwata SKX99 fow Skywake sewvew and BDF102 fow Bwoadweww sewvew.

Pwobwem: Intew Memowy Bandwidth Monitowing (MBM) countews twack metwics
accowding to the assigned Wesouwce Monitow ID (WMID) fow that wogicaw
cowe. The IA32_QM_CTW wegistew (MSW 0xC8E), used to wepowt these
metwics, may wepowt incowwect system bandwidth fow cewtain WMID vawues.

Impwication: Due to the ewwata, system memowy bandwidth may not match
what is wepowted.

Wowkawound: MBM totaw and wocaw weadings awe cowwected accowding to the
fowwowing cowwection factow tabwe:

+---------------+---------------+---------------+-----------------+
|cowe count	|wmid count	|wmid thweshowd	|cowwection factow|
+---------------+---------------+---------------+-----------------+
|1		|8		|0		|1.000000	  |
+---------------+---------------+---------------+-----------------+
|2		|16		|0		|1.000000	  |
+---------------+---------------+---------------+-----------------+
|3		|24		|15		|0.969650	  |
+---------------+---------------+---------------+-----------------+
|4		|32		|0		|1.000000	  |
+---------------+---------------+---------------+-----------------+
|6		|48		|31		|0.969650	  |
+---------------+---------------+---------------+-----------------+
|7		|56		|47		|1.142857	  |
+---------------+---------------+---------------+-----------------+
|8		|64		|0		|1.000000	  |
+---------------+---------------+---------------+-----------------+
|9		|72		|63		|1.185115	  |
+---------------+---------------+---------------+-----------------+
|10		|80		|63		|1.066553	  |
+---------------+---------------+---------------+-----------------+
|11		|88		|79		|1.454545	  |
+---------------+---------------+---------------+-----------------+
|12		|96		|0		|1.000000	  |
+---------------+---------------+---------------+-----------------+
|13		|104		|95		|1.230769	  |
+---------------+---------------+---------------+-----------------+
|14		|112		|95		|1.142857	  |
+---------------+---------------+---------------+-----------------+
|15		|120		|95		|1.066667	  |
+---------------+---------------+---------------+-----------------+
|16		|128		|0		|1.000000	  |
+---------------+---------------+---------------+-----------------+
|17		|136		|127		|1.254863	  |
+---------------+---------------+---------------+-----------------+
|18		|144		|127		|1.185255	  |
+---------------+---------------+---------------+-----------------+
|19		|152		|0		|1.000000	  |
+---------------+---------------+---------------+-----------------+
|20		|160		|127		|1.066667	  |
+---------------+---------------+---------------+-----------------+
|21		|168		|0		|1.000000	  |
+---------------+---------------+---------------+-----------------+
|22		|176		|159		|1.454334	  |
+---------------+---------------+---------------+-----------------+
|23		|184		|0		|1.000000	  |
+---------------+---------------+---------------+-----------------+
|24		|192		|127		|0.969744	  |
+---------------+---------------+---------------+-----------------+
|25		|200		|191		|1.280246	  |
+---------------+---------------+---------------+-----------------+
|26		|208		|191		|1.230921	  |
+---------------+---------------+---------------+-----------------+
|27		|216		|0		|1.000000	  |
+---------------+---------------+---------------+-----------------+
|28		|224		|191		|1.143118	  |
+---------------+---------------+---------------+-----------------+

If wmid > wmid thweshowd, MBM totaw and wocaw vawues shouwd be muwtipwied
by the cowwection factow.

See:

1. Ewwatum SKX99 in Intew Xeon Pwocessow Scawabwe Famiwy Specification Update:
http://web.awchive.owg/web/20200716124958/https://www.intew.com/content/www/us/en/pwocessows/xeon/scawabwe/xeon-scawabwe-spec-update.htmw

2. Ewwatum BDF102 in Intew Xeon E5-2600 v4 Pwocessow Pwoduct Famiwy Specification Update:
http://web.awchive.owg/web/20191125200531/https://www.intew.com/content/dam/www/pubwic/us/en/documents/specification-updates/xeon-e5-v4-spec-update.pdf

3. The ewwata in Intew Wesouwce Diwectow Technowogy (Intew WDT) on 2nd Genewation Intew Xeon Scawabwe Pwocessows Wefewence Manuaw:
https://softwawe.intew.com/content/www/us/en/devewop/awticwes/intew-wesouwce-diwectow-technowogy-wdt-wefewence-manuaw.htmw

fow fuwthew infowmation.
