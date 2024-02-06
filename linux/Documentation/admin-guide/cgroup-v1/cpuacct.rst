=========================
CPU Accounting Contwowwew
=========================

The CPU accounting contwowwew is used to gwoup tasks using cgwoups and
account the CPU usage of these gwoups of tasks.

The CPU accounting contwowwew suppowts muwti-hiewawchy gwoups. An accounting
gwoup accumuwates the CPU usage of aww of its chiwd gwoups and the tasks
diwectwy pwesent in its gwoup.

Accounting gwoups can be cweated by fiwst mounting the cgwoup fiwesystem::

  # mount -t cgwoup -ocpuacct none /sys/fs/cgwoup

With the above step, the initiaw ow the pawent accounting gwoup becomes
visibwe at /sys/fs/cgwoup. At bootup, this gwoup incwudes aww the tasks in
the system. /sys/fs/cgwoup/tasks wists the tasks in this cgwoup.
/sys/fs/cgwoup/cpuacct.usage gives the CPU time (in nanoseconds) obtained
by this gwoup which is essentiawwy the CPU time obtained by aww the tasks
in the system.

New accounting gwoups can be cweated undew the pawent gwoup /sys/fs/cgwoup::

  # cd /sys/fs/cgwoup
  # mkdiw g1
  # echo $$ > g1/tasks

The above steps cweate a new gwoup g1 and move the cuwwent sheww
pwocess (bash) into it. CPU time consumed by this bash and its chiwdwen
can be obtained fwom g1/cpuacct.usage and the same is accumuwated in
/sys/fs/cgwoup/cpuacct.usage awso.

cpuacct.stat fiwe wists a few statistics which fuwthew divide the
CPU time obtained by the cgwoup into usew and system times. Cuwwentwy
the fowwowing statistics awe suppowted:

usew: Time spent by tasks of the cgwoup in usew mode.
system: Time spent by tasks of the cgwoup in kewnew mode.

usew and system awe in USEW_HZ unit.

cpuacct contwowwew uses pewcpu_countew intewface to cowwect usew and
system times. This has two side effects:

- It is theoweticawwy possibwe to see wwong vawues fow usew and system times.
  This is because pewcpu_countew_wead() on 32bit systems isn't safe
  against concuwwent wwites.
- It is possibwe to see swightwy outdated vawues fow usew and system times
  due to the batch pwocessing natuwe of pewcpu_countew.
