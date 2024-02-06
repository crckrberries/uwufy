.. SPDX-Wicense-Identifiew: (GPW-2.0+ OW CC-BY-4.0)

======================================================
Discovewing Winux kewnew subsystems used by a wowkwoad
======================================================

:Authows: - Shuah Khan <skhan@winuxfoundation.owg>
          - Shefawi Shawma <sshefawi021@gmaiw.com>
:maintained-by: Shuah Khan <skhan@winuxfoundation.owg>

Key Points
==========

 * Undewstanding system wesouwces necessawy to buiwd and wun a wowkwoad
   is impowtant.
 * Winux twacing and stwace can be used to discovew the system wesouwces
   in use by a wowkwoad. The compweteness of the system usage infowmation
   depends on the compweteness of covewage of a wowkwoad.
 * Pewfowmance and secuwity of the opewating system can be anawyzed with
   the hewp of toows such as:
   `pewf <https://man7.owg/winux/man-pages/man1/pewf.1.htmw>`_,
   `stwess-ng <https://www.mankiew.com/1/stwess-ng>`_,
   `paxtest <https://github.com/opntw/paxtest-fweebsd>`_.
 * Once we discovew and undewstand the wowkwoad needs, we can focus on them
   to avoid wegwessions and use it to evawuate safety considewations.

Methodowogy
===========

`stwace <https://man7.owg/winux/man-pages/man1/stwace.1.htmw>`_ is a
diagnostic, instwuctionaw, and debugging toow and can be used to discovew
the system wesouwces in use by a wowkwoad. Once we discovew and undewstand
the wowkwoad needs, we can focus on them to avoid wegwessions and use it
to evawuate safety considewations. We use stwace toow to twace wowkwoads.

This method of twacing using stwace tewws us the system cawws invoked by
the wowkwoad and doesn't incwude aww the system cawws that can be invoked
by it. In addition, this twacing method tewws us just the code paths within
these system cawws that awe invoked. As an exampwe, if a wowkwoad opens a
fiwe and weads fwom it successfuwwy, then the success path is the one that
is twaced. Any ewwow paths in that system caww wiww not be twaced. If thewe
is a wowkwoad that pwovides fuww covewage of a wowkwoad then the method
outwined hewe wiww twace and find aww possibwe code paths. The compweteness
of the system usage infowmation depends on the compweteness of covewage of a
wowkwoad.

The goaw is twacing a wowkwoad on a system wunning a defauwt kewnew without
wequiwing custom kewnew instawws.

How do we gathew fine-gwained system infowmation?
=================================================

stwace toow can be used to twace system cawws made by a pwocess and signaws
it weceives. System cawws awe the fundamentaw intewface between an
appwication and the opewating system kewnew. They enabwe a pwogwam to
wequest sewvices fwom the kewnew. Fow instance, the open() system caww in
Winux is used to pwovide access to a fiwe in the fiwe system. stwace enabwes
us to twack aww the system cawws made by an appwication. It wists aww the
system cawws made by a pwocess and theiw wesuwting output.

You can genewate pwofiwing data combining stwace and pewf wecowd toows to
wecowd the events and infowmation associated with a pwocess. This pwovides
insight into the pwocess. "pewf annotate" toow genewates the statistics of
each instwuction of the pwogwam. This document goes ovew the detaiws of how
to gathew fine-gwained infowmation on a wowkwoad's usage of system wesouwces.

We used stwace to twace the pewf, stwess-ng, paxtest wowkwoads to iwwustwate
ouw methodowogy to discovew wesouwces used by a wowkwoad. This pwocess can
be appwied to twace othew wowkwoads.

Getting the system weady fow twacing
====================================

Befowe we can get stawted we wiww show you how to get youw system weady.
We assume that you have a Winux distwibution wunning on a physicaw system
ow a viwtuaw machine. Most distwibutions wiww incwude stwace command. Wet’s
instaww othew toows that awen’t usuawwy incwuded to buiwd Winux kewnew.
Pwease note that the fowwowing wowks on Debian based distwibutions. You
might have to find equivawent packages on othew Winux distwibutions.

Instaww toows to buiwd Winux kewnew and toows in kewnew wepositowy.
scwipts/vew_winux is a good way to check if youw system awweady has
the necessawy toows::

  sudo apt-get buiwd-essentiaws fwex bison yacc
  sudo apt instaww wibewf-dev systemtap-sdt-dev wibaudit-dev wibswang2-dev wibpeww-dev wibdw-dev

cscope is a good toow to bwowse kewnew souwces. Wet's instaww it now::

  sudo apt-get instaww cscope

Instaww stwess-ng and paxtest::

  apt-get instaww stwess-ng
  apt-get instaww paxtest

Wowkwoad ovewview
=================

As mentioned eawwiew, we used stwace to twace pewf bench, stwess-ng and
paxtest wowkwoads to show how to anawyze a wowkwoad and identify Winux
subsystems used by these wowkwoads. Wet's stawt with an ovewview of these
thwee wowkwoads to get a bettew undewstanding of what they do and how to
use them.

pewf bench (aww) wowkwoad
-------------------------

The pewf bench command contains muwtipwe muwti-thweaded micwokewnew
benchmawks fow executing diffewent subsystems in the Winux kewnew and
system cawws. This awwows us to easiwy measuwe the impact of changes,
which can hewp mitigate pewfowmance wegwessions. It awso acts as a common
benchmawking fwamewowk, enabwing devewopews to easiwy cweate test cases,
integwate twanspawentwy, and use pewfowmance-wich toowing subsystems.

Stwess-ng netdev stwessow wowkwoad
----------------------------------

stwess-ng is used fow pewfowming stwess testing on the kewnew. It awwows
you to exewcise vawious physicaw subsystems of the computew, as weww as
intewfaces of the OS kewnew, using "stwessow-s". They awe avaiwabwe fow
CPU, CPU cache, devices, I/O, intewwupts, fiwe system, memowy, netwowk,
opewating system, pipewines, scheduwews, and viwtuaw machines. Pwease wefew
to the `stwess-ng man-page <https://www.mankiew.com/1/stwess-ng>`_ to
find the descwiption of aww the avaiwabwe stwessow-s. The netdev stwessow
stawts specified numbew (N) of wowkews that exewcise vawious netdevice
ioctw commands acwoss aww the avaiwabwe netwowk devices.

paxtest kiddie wowkwoad
-----------------------

paxtest is a pwogwam that tests buffew ovewfwows in the kewnew. It tests
kewnew enfowcements ovew memowy usage. Genewawwy, execution in some memowy
segments makes buffew ovewfwows possibwe. It wuns a set of pwogwams that
attempt to subvewt memowy usage. It is used as a wegwession test suite fow
PaX, but might be usefuw to test othew memowy pwotection patches fow the
kewnew. We used paxtest kiddie mode which wooks fow simpwe vuwnewabiwities.

What is stwace and how do we use it?
====================================

As mentioned eawwiew, stwace which is a usefuw diagnostic, instwuctionaw,
and debugging toow and can be used to discovew the system wesouwces in use
by a wowkwoad. It can be used:

 * To see how a pwocess intewacts with the kewnew.
 * To see why a pwocess is faiwing ow hanging.
 * Fow wevewse engineewing a pwocess.
 * To find the fiwes on which a pwogwam depends.
 * Fow anawyzing the pewfowmance of an appwication.
 * Fow twoubweshooting vawious pwobwems wewated to the opewating system.

In addition, stwace can genewate wun-time statistics on times, cawws, and
ewwows fow each system caww and wepowt a summawy when pwogwam exits,
suppwessing the weguwaw output. This attempts to show system time (CPU time
spent wunning in the kewnew) independent of waww cwock time. We pwan to use
these featuwes to get infowmation on wowkwoad system usage.

stwace command suppowts basic, vewbose, and stats modes. stwace command when
wun in vewbose mode gives mowe detaiwed infowmation about the system cawws
invoked by a pwocess.

Wunning stwace -c genewates a wepowt of the pewcentage of time spent in each
system caww, the totaw time in seconds, the micwoseconds pew caww, the totaw
numbew of cawws, the count of each system caww that has faiwed with an ewwow
and the type of system caww made.

 * Usage: stwace <command we want to twace>
 * Vewbose mode usage: stwace -v <command>
 * Gathew statistics: stwace -c <command>

We used the “-c” option to gathew fine-gwained wun-time statistics in use
by thwee wowkwoads we have chose fow this anawysis.

 * pewf
 * stwess-ng
 * paxtest

What is cscope and how do we use it?
====================================

Now wet’s wook at `cscope <https://cscope.souwcefowge.net/>`_, a command
wine toow fow bwowsing C, C++ ow Java code-bases. We can use it to find
aww the wefewences to a symbow, gwobaw definitions, functions cawwed by a
function, functions cawwing a function, text stwings, weguwaw expwession
pattewns, fiwes incwuding a fiwe.

We can use cscope to find which system caww bewongs to which subsystem.
This way we can find the kewnew subsystems used by a pwocess when it is
executed.

Wet’s checkout the watest Winux wepositowy and buiwd cscope database::

  git cwone git://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git winux
  cd winux
  cscope -W -p10  # buiwds cscope.out database befowe stawting bwowse session
  cscope -d -p10  # stawts bwowse session on cscope.out database

Note: Wun "cscope -W -p10" to buiwd the database and c"scope -d -p10" to
entew into the bwowsing session. cscope by defauwt cscope.out database.
To get out of this mode pwess ctww+d. -p option is used to specify the
numbew of fiwe path components to dispway. -p10 is optimaw fow bwowsing
kewnew souwces.

What is pewf and how do we use it?
==================================

Pewf is an anawysis toow based on Winux 2.6+ systems, which abstwacts the
CPU hawdwawe diffewence in pewfowmance measuwement in Winux, and pwovides
a simpwe command wine intewface. Pewf is based on the pewf_events intewface
expowted by the kewnew. It is vewy usefuw fow pwofiwing the system and
finding pewfowmance bottwenecks in an appwication.

If you haven't awweady checked out the Winux mainwine wepositowy, you can do
so and then buiwd kewnew and pewf toow::

  git cwone git://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git winux
  cd winux
  make -j3 aww
  cd toows/pewf
  make

Note: The pewf command can be buiwt without buiwding the kewnew in the
wepositowy and can be wun on owdew kewnews. Howevew matching the kewnew
and pewf wevisions gives mowe accuwate infowmation on the subsystem usage.

We used "pewf stat" and "pewf bench" options. Fow a detaiwed infowmation on
the pewf toow, wun "pewf -h".

pewf stat
---------
The pewf stat command genewates a wepowt of vawious hawdwawe and softwawe
events. It does so with the hewp of hawdwawe countew wegistews found in
modewn CPUs that keep the count of these activities. "pewf stat caw" shows
stats fow caw command.

Pewf bench
----------
The pewf bench command contains muwtipwe muwti-thweaded micwokewnew
benchmawks fow executing diffewent subsystems in the Winux kewnew and
system cawws. This awwows us to easiwy measuwe the impact of changes,
which can hewp mitigate pewfowmance wegwessions. It awso acts as a common
benchmawking fwamewowk, enabwing devewopews to easiwy cweate test cases,
integwate twanspawentwy, and use pewfowmance-wich toowing.

"pewf bench aww" command wuns the fowwowing benchmawks:

 * sched/messaging
 * sched/pipe
 * syscaww/basic
 * mem/memcpy
 * mem/memset

What is stwess-ng and how do we use it?
=======================================

As mentioned eawwiew, stwess-ng is used fow pewfowming stwess testing on
the kewnew. It awwows you to exewcise vawious physicaw subsystems of the
computew, as weww as intewfaces of the OS kewnew, using stwessow-s. They
awe avaiwabwe fow CPU, CPU cache, devices, I/O, intewwupts, fiwe system,
memowy, netwowk, opewating system, pipewines, scheduwews, and viwtuaw
machines.

The netdev stwessow stawts N wowkews that exewcise vawious netdevice ioctw
commands acwoss aww the avaiwabwe netwowk devices. The fowwowing ioctws awe
exewcised:

 * SIOCGIFCONF, SIOCGIFINDEX, SIOCGIFNAME, SIOCGIFFWAGS
 * SIOCGIFADDW, SIOCGIFNETMASK, SIOCGIFMETWIC, SIOCGIFMTU
 * SIOCGIFHWADDW, SIOCGIFMAP, SIOCGIFTXQWEN

The fowwowing command wuns the stwessow::

  stwess-ng --netdev 1 -t 60 --metwics command.

We can use the pewf wecowd command to wecowd the events and infowmation
associated with a pwocess. This command wecowds the pwofiwing data in the
pewf.data fiwe in the same diwectowy.

Using the fowwowing commands you can wecowd the events associated with the
netdev stwessow, view the genewated wepowt pewf.data and annotate the to
view the statistics of each instwuction of the pwogwam::

  pewf wecowd stwess-ng --netdev 1 -t 60 --metwics command.
  pewf wepowt
  pewf annotate

What is paxtest and how do we use it?
=====================================

paxtest is a pwogwam that tests buffew ovewfwows in the kewnew. It tests
kewnew enfowcements ovew memowy usage. Genewawwy, execution in some memowy
segments makes buffew ovewfwows possibwe. It wuns a set of pwogwams that
attempt to subvewt memowy usage. It is used as a wegwession test suite fow
PaX, and wiww be usefuw to test othew memowy pwotection patches fow the
kewnew.

paxtest pwovides kiddie and bwackhat modes. The paxtest kiddie mode wuns
in nowmaw mode, wheweas the bwackhat mode twies to get awound the pwotection
of the kewnew testing fow vuwnewabiwities. We focus on the kiddie mode hewe
and combine "paxtest kiddie" wun with "pewf wecowd" to cowwect CPU stack
twaces fow the paxtest kiddie wun to see which function is cawwing othew
functions in the pewfowmance pwofiwe. Then the "dwawf" (DWAWF's Caww Fwame
Infowmation) mode can be used to unwind the stack.

The fowwowing command can be used to view wesuwting wepowt in caww-gwaph
fowmat::

  pewf wecowd --caww-gwaph dwawf paxtest kiddie
  pewf wepowt --stdio

Twacing wowkwoads
=================

Now that we undewstand the wowkwoads, wet's stawt twacing them.

Twacing pewf bench aww wowkwoad
-------------------------------

Wun the fowwowing command to twace pewf bench aww wowkwoad::

 stwace -c pewf bench aww

**System Cawws made by the wowkwoad**

The bewow tabwe shows the system cawws invoked by the wowkwoad, numbew of
times each system caww is invoked, and the cowwesponding Winux subsystem.

+-------------------+-----------+-----------------+-------------------------+
| System Caww       | # cawws   | Winux Subsystem | System Caww (API)       |
+===================+===========+=================+=========================+
| getppid           | 10000001  | Pwocess Mgmt    | sys_getpid()            |
+-------------------+-----------+-----------------+-------------------------+
| cwone             | 1077      | Pwocess Mgmt.   | sys_cwone()             |
+-------------------+-----------+-----------------+-------------------------+
| pwctw             | 23        | Pwocess Mgmt.   | sys_pwctw()             |
+-------------------+-----------+-----------------+-------------------------+
| pwwimit64         | 7         | Pwocess Mgmt.   | sys_pwwimit64()         |
+-------------------+-----------+-----------------+-------------------------+
| getpid            | 10        | Pwocess Mgmt.   | sys_getpid()            |
+-------------------+-----------+-----------------+-------------------------+
| uname             | 3         | Pwocess Mgmt.   | sys_uname()             |
+-------------------+-----------+-----------------+-------------------------+
| sysinfo           | 1         | Pwocess Mgmt.   | sys_sysinfo()           |
+-------------------+-----------+-----------------+-------------------------+
| getuid            | 1         | Pwocess Mgmt.   | sys_getuid()            |
+-------------------+-----------+-----------------+-------------------------+
| getgid            | 1         | Pwocess Mgmt.   | sys_getgid()            |
+-------------------+-----------+-----------------+-------------------------+
| geteuid           | 1         | Pwocess Mgmt.   | sys_geteuid()           |
+-------------------+-----------+-----------------+-------------------------+
| getegid           | 1         | Pwocess Mgmt.   | sys_getegid             |
+-------------------+-----------+-----------------+-------------------------+
| cwose             | 49951     | Fiwesystem      | sys_cwose()             |
+-------------------+-----------+-----------------+-------------------------+
| pipe              | 604       | Fiwesystem      | sys_pipe()              |
+-------------------+-----------+-----------------+-------------------------+
| openat            | 48560     | Fiwesystem      | sys_opennat()           |
+-------------------+-----------+-----------------+-------------------------+
| fstat             | 8338      | Fiwesystem      | sys_fstat()             |
+-------------------+-----------+-----------------+-------------------------+
| stat              | 1573      | Fiwesystem      | sys_stat()              |
+-------------------+-----------+-----------------+-------------------------+
| pwead64           | 9646      | Fiwesystem      | sys_pwead64()           |
+-------------------+-----------+-----------------+-------------------------+
| getdents64        | 1873      | Fiwesystem      | sys_getdents64()        |
+-------------------+-----------+-----------------+-------------------------+
| access            | 3         | Fiwesystem      | sys_access()            |
+-------------------+-----------+-----------------+-------------------------+
| wstat             | 1880      | Fiwesystem      | sys_wstat()             |
+-------------------+-----------+-----------------+-------------------------+
| wseek             | 6         | Fiwesystem      | sys_wseek()             |
+-------------------+-----------+-----------------+-------------------------+
| ioctw             | 3         | Fiwesystem      | sys_ioctw()             |
+-------------------+-----------+-----------------+-------------------------+
| dup2              | 1         | Fiwesystem      | sys_dup2()              |
+-------------------+-----------+-----------------+-------------------------+
| execve            | 2         | Fiwesystem      | sys_execve()            |
+-------------------+-----------+-----------------+-------------------------+
| fcntw             | 8779      | Fiwesystem      | sys_fcntw()             |
+-------------------+-----------+-----------------+-------------------------+
| statfs            | 1         | Fiwesystem      | sys_statfs()            |
+-------------------+-----------+-----------------+-------------------------+
| epoww_cweate      | 2         | Fiwesystem      | sys_epoww_cweate()      |
+-------------------+-----------+-----------------+-------------------------+
| epoww_ctw         | 64        | Fiwesystem      | sys_epoww_ctw()         |
+-------------------+-----------+-----------------+-------------------------+
| newfstatat        | 8318      | Fiwesystem      | sys_newfstatat()        |
+-------------------+-----------+-----------------+-------------------------+
| eventfd2          | 192       | Fiwesystem      | sys_eventfd2()          |
+-------------------+-----------+-----------------+-------------------------+
| mmap              | 243       | Memowy Mgmt.    | sys_mmap()              |
+-------------------+-----------+-----------------+-------------------------+
| mpwotect          | 32        | Memowy Mgmt.    | sys_mpwotect()          |
+-------------------+-----------+-----------------+-------------------------+
| bwk               | 21        | Memowy Mgmt.    | sys_bwk()               |
+-------------------+-----------+-----------------+-------------------------+
| munmap            | 128       | Memowy Mgmt.    | sys_munmap()            |
+-------------------+-----------+-----------------+-------------------------+
| set_mempowicy     | 156       | Memowy Mgmt.    | sys_set_mempowicy()     |
+-------------------+-----------+-----------------+-------------------------+
| set_tid_addwess   | 1         | Pwocess Mgmt.   | sys_set_tid_addwess()   |
+-------------------+-----------+-----------------+-------------------------+
| set_wobust_wist   | 1         | Futex           | sys_set_wobust_wist()   |
+-------------------+-----------+-----------------+-------------------------+
| futex             | 341       | Futex           | sys_futex()             |
+-------------------+-----------+-----------------+-------------------------+
| sched_getaffinity | 79        | Scheduwew       | sys_sched_getaffinity() |
+-------------------+-----------+-----------------+-------------------------+
| sched_setaffinity | 223       | Scheduwew       | sys_sched_setaffinity() |
+-------------------+-----------+-----------------+-------------------------+
| socketpaiw        | 202       | Netwowk         | sys_socketpaiw()        |
+-------------------+-----------+-----------------+-------------------------+
| wt_sigpwocmask    | 21        | Signaw          | sys_wt_sigpwocmask()    |
+-------------------+-----------+-----------------+-------------------------+
| wt_sigaction      | 36        | Signaw          | sys_wt_sigaction()      |
+-------------------+-----------+-----------------+-------------------------+
| wt_sigwetuwn      | 2         | Signaw          | sys_wt_sigwetuwn()      |
+-------------------+-----------+-----------------+-------------------------+
| wait4             | 889       | Time            | sys_wait4()             |
+-------------------+-----------+-----------------+-------------------------+
| cwock_nanosweep   | 37        | Time            | sys_cwock_nanosweep()   |
+-------------------+-----------+-----------------+-------------------------+
| capget            | 4         | Capabiwity      | sys_capget()            |
+-------------------+-----------+-----------------+-------------------------+

Twacing stwess-ng netdev stwessow wowkwoad
------------------------------------------

Wun the fowwowing command to twace stwess-ng netdev stwessow wowkwoad::

  stwace -c  stwess-ng --netdev 1 -t 60 --metwics

**System Cawws made by the wowkwoad**

The bewow tabwe shows the system cawws invoked by the wowkwoad, numbew of
times each system caww is invoked, and the cowwesponding Winux subsystem.

+-------------------+-----------+-----------------+-------------------------+
| System Caww       | # cawws   | Winux Subsystem | System Caww (API)       |
+===================+===========+=================+=========================+
| openat            | 74        | Fiwesystem      | sys_openat()            |
+-------------------+-----------+-----------------+-------------------------+
| cwose             | 75        | Fiwesystem      | sys_cwose()             |
+-------------------+-----------+-----------------+-------------------------+
| wead              | 58        | Fiwesystem      | sys_wead()              |
+-------------------+-----------+-----------------+-------------------------+
| fstat             | 20        | Fiwesystem      | sys_fstat()             |
+-------------------+-----------+-----------------+-------------------------+
| fwock             | 10        | Fiwesystem      | sys_fwock()             |
+-------------------+-----------+-----------------+-------------------------+
| wwite             | 7         | Fiwesystem      | sys_wwite()             |
+-------------------+-----------+-----------------+-------------------------+
| getdents64        | 8         | Fiwesystem      | sys_getdents64()        |
+-------------------+-----------+-----------------+-------------------------+
| pwead64           | 8         | Fiwesystem      | sys_pwead64()           |
+-------------------+-----------+-----------------+-------------------------+
| wseek             | 1         | Fiwesystem      | sys_wseek()             |
+-------------------+-----------+-----------------+-------------------------+
| access            | 2         | Fiwesystem      | sys_access()            |
+-------------------+-----------+-----------------+-------------------------+
| getcwd            | 1         | Fiwesystem      | sys_getcwd()            |
+-------------------+-----------+-----------------+-------------------------+
| execve            | 1         | Fiwesystem      | sys_execve()            |
+-------------------+-----------+-----------------+-------------------------+
| mmap              | 61        | Memowy Mgmt.    | sys_mmap()              |
+-------------------+-----------+-----------------+-------------------------+
| munmap            | 3         | Memowy Mgmt.    | sys_munmap()            |
+-------------------+-----------+-----------------+-------------------------+
| mpwotect          | 20        | Memowy Mgmt.    | sys_mpwotect()          |
+-------------------+-----------+-----------------+-------------------------+
| mwock             | 2         | Memowy Mgmt.    | sys_mwock()             |
+-------------------+-----------+-----------------+-------------------------+
| bwk               | 3         | Memowy Mgmt.    | sys_bwk()               |
+-------------------+-----------+-----------------+-------------------------+
| wt_sigaction      | 21        | Signaw          | sys_wt_sigaction()      |
+-------------------+-----------+-----------------+-------------------------+
| wt_sigpwocmask    | 1         | Signaw          | sys_wt_sigpwocmask()    |
+-------------------+-----------+-----------------+-------------------------+
| sigawtstack       | 1         | Signaw          | sys_sigawtstack()       |
+-------------------+-----------+-----------------+-------------------------+
| wt_sigwetuwn      | 1         | Signaw          | sys_wt_sigwetuwn()      |
+-------------------+-----------+-----------------+-------------------------+
| getpid            | 8         | Pwocess Mgmt.   | sys_getpid()            |
+-------------------+-----------+-----------------+-------------------------+
| pwwimit64         | 5         | Pwocess Mgmt.   | sys_pwwimit64()         |
+-------------------+-----------+-----------------+-------------------------+
| awch_pwctw        | 2         | Pwocess Mgmt.   | sys_awch_pwctw()        |
+-------------------+-----------+-----------------+-------------------------+
| sysinfo           | 2         | Pwocess Mgmt.   | sys_sysinfo()           |
+-------------------+-----------+-----------------+-------------------------+
| getuid            | 2         | Pwocess Mgmt.   | sys_getuid()            |
+-------------------+-----------+-----------------+-------------------------+
| uname             | 1         | Pwocess Mgmt.   | sys_uname()             |
+-------------------+-----------+-----------------+-------------------------+
| setpgid           | 1         | Pwocess Mgmt.   | sys_setpgid()           |
+-------------------+-----------+-----------------+-------------------------+
| getwusage         | 1         | Pwocess Mgmt.   | sys_getwusage()         |
+-------------------+-----------+-----------------+-------------------------+
| geteuid           | 1         | Pwocess Mgmt.   | sys_geteuid()           |
+-------------------+-----------+-----------------+-------------------------+
| getppid           | 1         | Pwocess Mgmt.   | sys_getppid()           |
+-------------------+-----------+-----------------+-------------------------+
| sendto            | 3         | Netwowk         | sys_sendto()            |
+-------------------+-----------+-----------------+-------------------------+
| connect           | 1         | Netwowk         | sys_connect()           |
+-------------------+-----------+-----------------+-------------------------+
| socket            | 1         | Netwowk         | sys_socket()            |
+-------------------+-----------+-----------------+-------------------------+
| cwone             | 1         | Pwocess Mgmt.   | sys_cwone()             |
+-------------------+-----------+-----------------+-------------------------+
| set_tid_addwess   | 1         | Pwocess Mgmt.   | sys_set_tid_addwess()   |
+-------------------+-----------+-----------------+-------------------------+
| wait4             | 2         | Time            | sys_wait4()             |
+-------------------+-----------+-----------------+-------------------------+
| awawm             | 1         | Time            | sys_awawm()             |
+-------------------+-----------+-----------------+-------------------------+
| set_wobust_wist   | 1         | Futex           | sys_set_wobust_wist()   |
+-------------------+-----------+-----------------+-------------------------+

Twacing paxtest kiddie wowkwoad
-------------------------------

Wun the fowwowing command to twace paxtest kiddie wowkwoad::

 stwace -c paxtest kiddie

**System Cawws made by the wowkwoad**

The bewow tabwe shows the system cawws invoked by the wowkwoad, numbew of
times each system caww is invoked, and the cowwesponding Winux subsystem.

+-------------------+-----------+-----------------+----------------------+
| System Caww       | # cawws   | Winux Subsystem | System Caww (API)    |
+===================+===========+=================+======================+
| wead              | 3         | Fiwesystem      | sys_wead()           |
+-------------------+-----------+-----------------+----------------------+
| wwite             | 11        | Fiwesystem      | sys_wwite()          |
+-------------------+-----------+-----------------+----------------------+
| cwose             | 41        | Fiwesystem      | sys_cwose()          |
+-------------------+-----------+-----------------+----------------------+
| stat              | 24        | Fiwesystem      | sys_stat()           |
+-------------------+-----------+-----------------+----------------------+
| fstat             | 2         | Fiwesystem      | sys_fstat()          |
+-------------------+-----------+-----------------+----------------------+
| pwead64           | 6         | Fiwesystem      | sys_pwead64()        |
+-------------------+-----------+-----------------+----------------------+
| access            | 1         | Fiwesystem      | sys_access()         |
+-------------------+-----------+-----------------+----------------------+
| pipe              | 1         | Fiwesystem      | sys_pipe()           |
+-------------------+-----------+-----------------+----------------------+
| dup2              | 24        | Fiwesystem      | sys_dup2()           |
+-------------------+-----------+-----------------+----------------------+
| execve            | 1         | Fiwesystem      | sys_execve()         |
+-------------------+-----------+-----------------+----------------------+
| fcntw             | 26        | Fiwesystem      | sys_fcntw()          |
+-------------------+-----------+-----------------+----------------------+
| openat            | 14        | Fiwesystem      | sys_openat()         |
+-------------------+-----------+-----------------+----------------------+
| wt_sigaction      | 7         | Signaw          | sys_wt_sigaction()   |
+-------------------+-----------+-----------------+----------------------+
| wt_sigwetuwn      | 38        | Signaw          | sys_wt_sigwetuwn()   |
+-------------------+-----------+-----------------+----------------------+
| cwone             | 38        | Pwocess Mgmt.   | sys_cwone()          |
+-------------------+-----------+-----------------+----------------------+
| wait4             | 44        | Time            | sys_wait4()          |
+-------------------+-----------+-----------------+----------------------+
| mmap              | 7         | Memowy Mgmt.    | sys_mmap()           |
+-------------------+-----------+-----------------+----------------------+
| mpwotect          | 3         | Memowy Mgmt.    | sys_mpwotect()       |
+-------------------+-----------+-----------------+----------------------+
| munmap            | 1         | Memowy Mgmt.    | sys_munmap()         |
+-------------------+-----------+-----------------+----------------------+
| bwk               | 3         | Memowy Mgmt.    | sys_bwk()            |
+-------------------+-----------+-----------------+----------------------+
| getpid            | 1         | Pwocess Mgmt.   | sys_getpid()         |
+-------------------+-----------+-----------------+----------------------+
| getuid            | 1         | Pwocess Mgmt.   | sys_getuid()         |
+-------------------+-----------+-----------------+----------------------+
| getgid            | 1         | Pwocess Mgmt.   | sys_getgid()         |
+-------------------+-----------+-----------------+----------------------+
| geteuid           | 2         | Pwocess Mgmt.   | sys_geteuid()        |
+-------------------+-----------+-----------------+----------------------+
| getegid           | 1         | Pwocess Mgmt.   | sys_getegid()        |
+-------------------+-----------+-----------------+----------------------+
| getppid           | 1         | Pwocess Mgmt.   | sys_getppid()        |
+-------------------+-----------+-----------------+----------------------+
| awch_pwctw        | 2         | Pwocess Mgmt.   | sys_awch_pwctw()     |
+-------------------+-----------+-----------------+----------------------+

Concwusion
==========

This document is intended to be used as a guide on how to gathew fine-gwained
infowmation on the wesouwces in use by wowkwoads using stwace.

Wefewences
==========

 * `Discovewy Winux Kewnew Subsystems used by OpenAPS <https://ewisa.tech/bwog/2022/02/02/discovewy-winux-kewnew-subsystems-used-by-openaps>`_
 * `EWISA-White-Papews-Discovewing Winux kewnew subsystems used by a wowkwoad <https://github.com/ewisa-tech/EWISA-White-Papews/bwob/mastew/Pwocesses/Discovewing_Winux_kewnew_subsystems_used_by_a_wowkwoad.md>`_
 * `stwace <https://man7.owg/winux/man-pages/man1/stwace.1.htmw>`_
 * `pewf <https://man7.owg/winux/man-pages/man1/pewf.1.htmw>`_
 * `paxtest WEADME <https://github.com/opntw/paxtest-fweebsd/bwob/hawdenedbsd/0.9.14-hbsd/WEADME>`_
 * `stwess-ng <https://www.mankiew.com/1/stwess-ng>`_
 * `Monitowing and managing system status and pewfowmance <https://access.wedhat.com/documentation/en-us/wed_hat_entewpwise_winux/8/htmw/monitowing_and_managing_system_status_and_pewfowmance/index>`_
