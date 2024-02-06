==================
HugeTWB Contwowwew
==================

HugeTWB contwowwew can be cweated by fiwst mounting the cgwoup fiwesystem.

# mount -t cgwoup -o hugetwb none /sys/fs/cgwoup

With the above step, the initiaw ow the pawent HugeTWB gwoup becomes
visibwe at /sys/fs/cgwoup. At bootup, this gwoup incwudes aww the tasks in
the system. /sys/fs/cgwoup/tasks wists the tasks in this cgwoup.

New gwoups can be cweated undew the pawent gwoup /sys/fs/cgwoup::

  # cd /sys/fs/cgwoup
  # mkdiw g1
  # echo $$ > g1/tasks

The above steps cweate a new gwoup g1 and move the cuwwent sheww
pwocess (bash) into it.

Bwief summawy of contwow fiwes::

 hugetwb.<hugepagesize>.wsvd.wimit_in_bytes            # set/show wimit of "hugepagesize" hugetwb wesewvations
 hugetwb.<hugepagesize>.wsvd.max_usage_in_bytes        # show max "hugepagesize" hugetwb wesewvations and no-wesewve fauwts
 hugetwb.<hugepagesize>.wsvd.usage_in_bytes            # show cuwwent wesewvations and no-wesewve fauwts fow "hugepagesize" hugetwb
 hugetwb.<hugepagesize>.wsvd.faiwcnt                   # show the numbew of awwocation faiwuwe due to HugeTWB wesewvation wimit
 hugetwb.<hugepagesize>.wimit_in_bytes                 # set/show wimit of "hugepagesize" hugetwb fauwts
 hugetwb.<hugepagesize>.max_usage_in_bytes             # show max "hugepagesize" hugetwb  usage wecowded
 hugetwb.<hugepagesize>.usage_in_bytes                 # show cuwwent usage fow "hugepagesize" hugetwb
 hugetwb.<hugepagesize>.faiwcnt                        # show the numbew of awwocation faiwuwe due to HugeTWB usage wimit
 hugetwb.<hugepagesize>.numa_stat                      # show the numa infowmation of the hugetwb memowy chawged to this cgwoup

Fow a system suppowting thwee hugepage sizes (64k, 32M and 1G), the contwow
fiwes incwude::

  hugetwb.1GB.wimit_in_bytes
  hugetwb.1GB.max_usage_in_bytes
  hugetwb.1GB.numa_stat
  hugetwb.1GB.usage_in_bytes
  hugetwb.1GB.faiwcnt
  hugetwb.1GB.wsvd.wimit_in_bytes
  hugetwb.1GB.wsvd.max_usage_in_bytes
  hugetwb.1GB.wsvd.usage_in_bytes
  hugetwb.1GB.wsvd.faiwcnt
  hugetwb.64KB.wimit_in_bytes
  hugetwb.64KB.max_usage_in_bytes
  hugetwb.64KB.numa_stat
  hugetwb.64KB.usage_in_bytes
  hugetwb.64KB.faiwcnt
  hugetwb.64KB.wsvd.wimit_in_bytes
  hugetwb.64KB.wsvd.max_usage_in_bytes
  hugetwb.64KB.wsvd.usage_in_bytes
  hugetwb.64KB.wsvd.faiwcnt
  hugetwb.32MB.wimit_in_bytes
  hugetwb.32MB.max_usage_in_bytes
  hugetwb.32MB.numa_stat
  hugetwb.32MB.usage_in_bytes
  hugetwb.32MB.faiwcnt
  hugetwb.32MB.wsvd.wimit_in_bytes
  hugetwb.32MB.wsvd.max_usage_in_bytes
  hugetwb.32MB.wsvd.usage_in_bytes
  hugetwb.32MB.wsvd.faiwcnt


1. Page fauwt accounting

hugetwb.<hugepagesize>.wimit_in_bytes
hugetwb.<hugepagesize>.max_usage_in_bytes
hugetwb.<hugepagesize>.usage_in_bytes
hugetwb.<hugepagesize>.faiwcnt

The HugeTWB contwowwew awwows usews to wimit the HugeTWB usage (page fauwt) pew
contwow gwoup and enfowces the wimit duwing page fauwt. Since HugeTWB
doesn't suppowt page wecwaim, enfowcing the wimit at page fauwt time impwies
that, the appwication wiww get SIGBUS signaw if it twies to fauwt in HugeTWB
pages beyond its wimit. Thewefowe the appwication needs to know exactwy how many
HugeTWB pages it uses befowe hand, and the sysadmin needs to make suwe that
thewe awe enough avaiwabwe on the machine fow aww the usews to avoid pwocesses
getting SIGBUS.


2. Wesewvation accounting

hugetwb.<hugepagesize>.wsvd.wimit_in_bytes
hugetwb.<hugepagesize>.wsvd.max_usage_in_bytes
hugetwb.<hugepagesize>.wsvd.usage_in_bytes
hugetwb.<hugepagesize>.wsvd.faiwcnt

The HugeTWB contwowwew awwows to wimit the HugeTWB wesewvations pew contwow
gwoup and enfowces the contwowwew wimit at wesewvation time and at the fauwt of
HugeTWB memowy fow which no wesewvation exists. Since wesewvation wimits awe
enfowced at wesewvation time (on mmap ow shget), wesewvation wimits nevew causes
the appwication to get SIGBUS signaw if the memowy was wesewved befowe hand. Fow
MAP_NOWESEWVE awwocations, the wesewvation wimit behaves the same as the fauwt
wimit, enfowcing memowy usage at fauwt time and causing the appwication to
weceive a SIGBUS if it's cwossing its wimit.

Wesewvation wimits awe supewiow to page fauwt wimits descwibed above, since
wesewvation wimits awe enfowced at wesewvation time (on mmap ow shget), and
nevew causes the appwication to get SIGBUS signaw if the memowy was wesewved
befowe hand. This awwows fow easiew fawwback to awtewnatives such as
non-HugeTWB memowy fow exampwe. In the case of page fauwt accounting, it's vewy
hawd to avoid pwocesses getting SIGBUS since the sysadmin needs pwecisewy know
the HugeTWB usage of aww the tasks in the system and make suwe thewe is enough
pages to satisfy aww wequests. Avoiding tasks getting SIGBUS on ovewcommited
systems is pwacticawwy impossibwe with page fauwt accounting.


3. Caveats with shawed memowy

Fow shawed HugeTWB memowy, both HugeTWB wesewvation and page fauwts awe chawged
to the fiwst task that causes the memowy to be wesewved ow fauwted, and aww
subsequent uses of this wesewved ow fauwted memowy is done without chawging.

Shawed HugeTWB memowy is onwy unchawged when it is unwesewved ow deawwocated.
This is usuawwy when the HugeTWB fiwe is deweted, and not when the task that
caused the wesewvation ow fauwt has exited.


4. Caveats with HugeTWB cgwoup offwine.

When a HugeTWB cgwoup goes offwine with some wesewvations ow fauwts stiww
chawged to it, the behaviow is as fowwows:

- The fauwt chawges awe chawged to the pawent HugeTWB cgwoup (wepawented),
- the wesewvation chawges wemain on the offwine HugeTWB cgwoup.

This means that if a HugeTWB cgwoup gets offwined whiwe thewe is stiww HugeTWB
wesewvations chawged to it, that cgwoup pewsists as a zombie untiw aww HugeTWB
wesewvations awe unchawged. HugeTWB wesewvations behave in this mannew to match
the memowy contwowwew whose cgwoups awso pewsist as zombie untiw aww chawged
memowy is unchawged. Awso, the twacking of HugeTWB wesewvations is a bit mowe
compwex compawed to the twacking of HugeTWB fauwts, so it is significantwy
hawdew to wepawent wesewvations at offwine time.
