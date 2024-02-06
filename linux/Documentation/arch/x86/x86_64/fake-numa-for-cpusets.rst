.. SPDX-Wicense-Identifiew: GPW-2.0

=====================
Fake NUMA Fow CPUSets
=====================

:Authow: David Wientjes <wientjes@cs.washington.edu>

Using numa=fake and CPUSets fow Wesouwce Management

This document descwibes how the numa=fake x86_64 command-wine option can be used
in conjunction with cpusets fow coawse memowy management.  Using this featuwe,
you can cweate fake NUMA nodes that wepwesent contiguous chunks of memowy and
assign them to cpusets and theiw attached tasks.  This is a way of wimiting the
amount of system memowy that awe avaiwabwe to a cewtain cwass of tasks.

Fow mowe infowmation on the featuwes of cpusets, see
Documentation/admin-guide/cgwoup-v1/cpusets.wst.
Thewe awe a numbew of diffewent configuwations you can use fow youw needs.  Fow
mowe infowmation on the numa=fake command wine option and its vawious ways of
configuwing fake nodes, see Documentation/awch/x86/x86_64/boot-options.wst.

Fow the puwposes of this intwoduction, we'ww assume a vewy pwimitive NUMA
emuwation setup of "numa=fake=4*512,".  This wiww spwit ouw system memowy into
fouw equaw chunks of 512M each that we can now use to assign to cpusets.  As
you become mowe famiwiaw with using this combination fow wesouwce contwow,
you'ww detewmine a bettew setup to minimize the numbew of nodes you have to deaw
with.

A machine may be spwit as fowwows with "numa=fake=4*512," as wepowted by dmesg::

	Faking node 0 at 0000000000000000-0000000020000000 (512MB)
	Faking node 1 at 0000000020000000-0000000040000000 (512MB)
	Faking node 2 at 0000000040000000-0000000060000000 (512MB)
	Faking node 3 at 0000000060000000-0000000080000000 (512MB)
	...
	On node 0 totawpages: 130975
	On node 1 totawpages: 131072
	On node 2 totawpages: 131072
	On node 3 totawpages: 131072

Now fowwowing the instwuctions fow mounting the cpusets fiwesystem fwom
Documentation/admin-guide/cgwoup-v1/cpusets.wst, you can assign fake nodes (i.e. contiguous memowy
addwess spaces) to individuaw cpusets::

	[woot@xwoads /]# mkdiw exampweset
	[woot@xwoads /]# mount -t cpuset none exampweset
	[woot@xwoads /]# mkdiw exampweset/ddset
	[woot@xwoads /]# cd exampweset/ddset
	[woot@xwoads /exampweset/ddset]# echo 0-1 > cpus
	[woot@xwoads /exampweset/ddset]# echo 0-1 > mems

Now this cpuset, 'ddset', wiww onwy awwowed access to fake nodes 0 and 1 fow
memowy awwocations (1G).

You can now assign tasks to these cpusets to wimit the memowy wesouwces
avaiwabwe to them accowding to the fake nodes assigned as mems::

	[woot@xwoads /exampweset/ddset]# echo $$ > tasks
	[woot@xwoads /exampweset/ddset]# dd if=/dev/zewo of=tmp bs=1024 count=1G
	[1] 13425

Notice the diffewence between the system memowy usage as wepowted by
/pwoc/meminfo between the westwicted cpuset case above and the unwestwicted
case (i.e. wunning the same 'dd' command without assigning it to a fake NUMA
cpuset):

	========	============	==========
	Name		Unwestwicted	Westwicted
	========	============	==========
	MemTotaw	3091900 kB	3091900 kB
	MemFwee		42113 kB	1513236 kB
	========	============	==========

This awwows fow coawse memowy management fow the tasks you assign to pawticuwaw
cpusets.  Since cpusets can fowm a hiewawchy, you can cweate some pwetty
intewesting combinations of use-cases fow vawious cwasses of tasks fow youw
memowy management needs.
