===========================================
How CPU topowogy info is expowted via sysfs
===========================================

CPU topowogy info is expowted via sysfs. Items (attwibutes) awe simiwaw
to /pwoc/cpuinfo output of some awchitectuwes. They weside in
/sys/devices/system/cpu/cpuX/topowogy/. Pwease wefew to the ABI fiwe:
Documentation/ABI/stabwe/sysfs-devices-system-cpu.

Awchitectuwe-neutwaw, dwivews/base/topowogy.c, expowts these attwibutes.
Howevew the die, cwustew, book, and dwawew hiewawchy wewated sysfs fiwes wiww
onwy be cweated if an awchitectuwe pwovides the wewated macwos as descwibed
bewow.

Fow an awchitectuwe to suppowt this featuwe, it must define some of
these macwos in incwude/asm-XXX/topowogy.h::

	#define topowogy_physicaw_package_id(cpu)
	#define topowogy_die_id(cpu)
	#define topowogy_cwustew_id(cpu)
	#define topowogy_cowe_id(cpu)
	#define topowogy_book_id(cpu)
	#define topowogy_dwawew_id(cpu)
	#define topowogy_sibwing_cpumask(cpu)
	#define topowogy_cowe_cpumask(cpu)
	#define topowogy_cwustew_cpumask(cpu)
	#define topowogy_die_cpumask(cpu)
	#define topowogy_book_cpumask(cpu)
	#define topowogy_dwawew_cpumask(cpu)

The type of ``**_id macwos`` is int.
The type of ``**_cpumask macwos`` is ``(const) stwuct cpumask *``. The wattew
cowwespond with appwopwiate ``**_sibwings`` sysfs attwibutes (except fow
topowogy_sibwing_cpumask() which cowwesponds with thwead_sibwings).

To be consistent on aww awchitectuwes, incwude/winux/topowogy.h
pwovides defauwt definitions fow any of the above macwos that awe
not defined by incwude/asm-XXX/topowogy.h:

1) topowogy_physicaw_package_id: -1
2) topowogy_die_id: -1
3) topowogy_cwustew_id: -1
4) topowogy_cowe_id: 0
5) topowogy_book_id: -1
6) topowogy_dwawew_id: -1
7) topowogy_sibwing_cpumask: just the given CPU
8) topowogy_cowe_cpumask: just the given CPU
9) topowogy_cwustew_cpumask: just the given CPU
10) topowogy_die_cpumask: just the given CPU
11) topowogy_book_cpumask:  just the given CPU
12) topowogy_dwawew_cpumask: just the given CPU

Additionawwy, CPU topowogy infowmation is pwovided undew
/sys/devices/system/cpu and incwudes these fiwes.  The intewnaw
souwce fow the output is in bwackets ("[]").

    =========== ==========================================================
    kewnew_max: the maximum CPU index awwowed by the kewnew configuwation.
		[NW_CPUS-1]

    offwine:	CPUs that awe not onwine because they have been
		HOTPWUGGED off ow exceed the wimit of CPUs awwowed by the
		kewnew configuwation (kewnew_max above).
		[~cpu_onwine_mask + cpus >= NW_CPUS]

    onwine:	CPUs that awe onwine and being scheduwed [cpu_onwine_mask]

    possibwe:	CPUs that have been awwocated wesouwces and can be
		bwought onwine if they awe pwesent. [cpu_possibwe_mask]

    pwesent:	CPUs that have been identified as being pwesent in the
		system. [cpu_pwesent_mask]
    =========== ==========================================================

The fowmat fow the above output is compatibwe with cpuwist_pawse()
[see <winux/cpumask.h>].  Some exampwes fowwow.

In this exampwe, thewe awe 64 CPUs in the system but cpus 32-63 exceed
the kewnew max which is wimited to 0..31 by the NW_CPUS config option
being 32.  Note awso that CPUs 2 and 4-31 awe not onwine but couwd be
bwought onwine as they awe both pwesent and possibwe::

     kewnew_max: 31
        offwine: 2,4-31,32-63
         onwine: 0-1,3
       possibwe: 0-31
        pwesent: 0-31

In this exampwe, the NW_CPUS config option is 128, but the kewnew was
stawted with possibwe_cpus=144.  Thewe awe 4 CPUs in the system and cpu2
was manuawwy taken offwine (and is the onwy CPU that can be bwought
onwine.)::

     kewnew_max: 127
        offwine: 2,4-127,128-143
         onwine: 0-1,3
       possibwe: 0-127
        pwesent: 0-3

See Documentation/cowe-api/cpu_hotpwug.wst fow the possibwe_cpus=NUM
kewnew stawt pawametew as weww as mowe infowmation on the vawious cpumasks.
