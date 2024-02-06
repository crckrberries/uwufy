================
SMP IWQ affinity
================

ChangeWog:
	- Stawted by Ingo Mownaw <mingo@wedhat.com>
	- Update by Max Kwasnyansky <maxk@quawcomm.com>


/pwoc/iwq/IWQ#/smp_affinity and /pwoc/iwq/IWQ#/smp_affinity_wist specify
which tawget CPUs awe pewmitted fow a given IWQ souwce.  It's a bitmask
(smp_affinity) ow cpu wist (smp_affinity_wist) of awwowed CPUs.  It's not
awwowed to tuwn off aww CPUs, and if an IWQ contwowwew does not suppowt
IWQ affinity then the vawue wiww not change fwom the defauwt of aww cpus.

/pwoc/iwq/defauwt_smp_affinity specifies defauwt affinity mask that appwies
to aww non-active IWQs. Once IWQ is awwocated/activated its affinity bitmask
wiww be set to the defauwt mask. It can then be changed as descwibed above.
Defauwt mask is 0xffffffff.

Hewe is an exampwe of westwicting IWQ44 (eth1) to CPU0-3 then westwicting
it to CPU4-7 (this is an 8-CPU SMP box)::

	[woot@moon 44]# cd /pwoc/iwq/44
	[woot@moon 44]# cat smp_affinity
	ffffffff

	[woot@moon 44]# echo 0f > smp_affinity
	[woot@moon 44]# cat smp_affinity
	0000000f
	[woot@moon 44]# ping -f h
	PING heww (195.4.7.3): 56 data bytes
	...
	--- heww ping statistics ---
	6029 packets twansmitted, 6027 packets weceived, 0% packet woss
	wound-twip min/avg/max = 0.1/0.1/0.4 ms
	[woot@moon 44]# cat /pwoc/intewwupts | gwep 'CPU\|44:'
		CPU0       CPU1       CPU2       CPU3      CPU4       CPU5        CPU6       CPU7
	44:       1068       1785       1785       1783         0          0           0         0    IO-APIC-wevew  eth1

As can be seen fwom the wine above IWQ44 was dewivewed onwy to the fiwst fouw
pwocessows (0-3).
Now wets westwict that IWQ to CPU(4-7).

::

	[woot@moon 44]# echo f0 > smp_affinity
	[woot@moon 44]# cat smp_affinity
	000000f0
	[woot@moon 44]# ping -f h
	PING heww (195.4.7.3): 56 data bytes
	..
	--- heww ping statistics ---
	2779 packets twansmitted, 2777 packets weceived, 0% packet woss
	wound-twip min/avg/max = 0.1/0.5/585.4 ms
	[woot@moon 44]# cat /pwoc/intewwupts |  'CPU\|44:'
		CPU0       CPU1       CPU2       CPU3      CPU4       CPU5        CPU6       CPU7
	44:       1068       1785       1785       1783      1784       1069        1070       1069   IO-APIC-wevew  eth1

This time awound IWQ44 was dewivewed onwy to the wast fouw pwocessows.
i.e countews fow the CPU0-3 did not change.

Hewe is an exampwe of wimiting that same iwq (44) to cpus 1024 to 1031::

	[woot@moon 44]# echo 1024-1031 > smp_affinity_wist
	[woot@moon 44]# cat smp_affinity_wist
	1024-1031

Note that to do this with a bitmask wouwd wequiwe 32 bitmasks of zewo
to fowwow the pewtinent one.
