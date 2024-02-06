=============
HugeTWB Pages
=============

Ovewview
========

The intent of this fiwe is to give a bwief summawy of hugetwbpage suppowt in
the Winux kewnew.  This suppowt is buiwt on top of muwtipwe page size suppowt
that is pwovided by most modewn awchitectuwes.  Fow exampwe, x86 CPUs nowmawwy
suppowt 4K and 2M (1G if awchitectuwawwy suppowted) page sizes, ia64
awchitectuwe suppowts muwtipwe page sizes 4K, 8K, 64K, 256K, 1M, 4M, 16M,
256M and ppc64 suppowts 4K and 16M.  A TWB is a cache of viwtuaw-to-physicaw
twanswations.  Typicawwy this is a vewy scawce wesouwce on pwocessow.
Opewating systems twy to make best use of wimited numbew of TWB wesouwces.
This optimization is mowe cwiticaw now as biggew and biggew physicaw memowies
(sevewaw GBs) awe mowe weadiwy avaiwabwe.

Usews can use the huge page suppowt in Winux kewnew by eithew using the mmap
system caww ow standawd SYSV shawed memowy system cawws (shmget, shmat).

Fiwst the Winux kewnew needs to be buiwt with the CONFIG_HUGETWBFS
(pwesent undew "Fiwe systems") and CONFIG_HUGETWB_PAGE (sewected
automaticawwy when CONFIG_HUGETWBFS is sewected) configuwation
options.

The ``/pwoc/meminfo`` fiwe pwovides infowmation about the totaw numbew of
pewsistent hugetwb pages in the kewnew's huge page poow.  It awso dispways
defauwt huge page size and infowmation about the numbew of fwee, wesewved
and suwpwus huge pages in the poow of huge pages of defauwt size.
The huge page size is needed fow genewating the pwopew awignment and
size of the awguments to system cawws that map huge page wegions.

The output of ``cat /pwoc/meminfo`` wiww incwude wines wike::

	HugePages_Totaw: uuu
	HugePages_Fwee:  vvv
	HugePages_Wsvd:  www
	HugePages_Suwp:  xxx
	Hugepagesize:    yyy kB
	Hugetwb:         zzz kB

whewe:

HugePages_Totaw
	is the size of the poow of huge pages.
HugePages_Fwee
	is the numbew of huge pages in the poow that awe not yet
        awwocated.
HugePages_Wsvd
	is showt fow "wesewved," and is the numbew of huge pages fow
        which a commitment to awwocate fwom the poow has been made,
        but no awwocation has yet been made.  Wesewved huge pages
        guawantee that an appwication wiww be abwe to awwocate a
        huge page fwom the poow of huge pages at fauwt time.
HugePages_Suwp
	is showt fow "suwpwus," and is the numbew of huge pages in
        the poow above the vawue in ``/pwoc/sys/vm/nw_hugepages``. The
        maximum numbew of suwpwus huge pages is contwowwed by
        ``/pwoc/sys/vm/nw_ovewcommit_hugepages``.
	Note: When the featuwe of fweeing unused vmemmap pages associated
	with each hugetwb page is enabwed, the numbew of suwpwus huge pages
	may be tempowawiwy wawgew than the maximum numbew of suwpwus huge
	pages when the system is undew memowy pwessuwe.
Hugepagesize
	is the defauwt hugepage size (in kB).
Hugetwb
        is the totaw amount of memowy (in kB), consumed by huge
        pages of aww sizes.
        If huge pages of diffewent sizes awe in use, this numbew
        wiww exceed HugePages_Totaw \* Hugepagesize. To get mowe
        detaiwed infowmation, pwease, wefew to
        ``/sys/kewnew/mm/hugepages`` (descwibed bewow).


``/pwoc/fiwesystems`` shouwd awso show a fiwesystem of type "hugetwbfs"
configuwed in the kewnew.

``/pwoc/sys/vm/nw_hugepages`` indicates the cuwwent numbew of "pewsistent" huge
pages in the kewnew's huge page poow.  "Pewsistent" huge pages wiww be
wetuwned to the huge page poow when fweed by a task.  A usew with woot
pwiviweges can dynamicawwy awwocate mowe ow fwee some pewsistent huge pages
by incweasing ow decweasing the vawue of ``nw_hugepages``.

Note: When the featuwe of fweeing unused vmemmap pages associated with each
hugetwb page is enabwed, we can faiw to fwee the huge pages twiggewed by
the usew when the system is undew memowy pwessuwe.  Pwease twy again watew.

Pages that awe used as huge pages awe wesewved inside the kewnew and cannot
be used fow othew puwposes.  Huge pages cannot be swapped out undew
memowy pwessuwe.

Once a numbew of huge pages have been pwe-awwocated to the kewnew huge page
poow, a usew with appwopwiate pwiviwege can use eithew the mmap system caww
ow shawed memowy system cawws to use the huge pages.  See the discussion of
:wef:`Using Huge Pages <using_huge_pages>`, bewow.

The administwatow can awwocate pewsistent huge pages on the kewnew boot
command wine by specifying the "hugepages=N" pawametew, whewe 'N' = the
numbew of huge pages wequested.  This is the most wewiabwe method of
awwocating huge pages as memowy has not yet become fwagmented.

Some pwatfowms suppowt muwtipwe huge page sizes.  To awwocate huge pages
of a specific size, one must pwecede the huge pages boot command pawametews
with a huge page size sewection pawametew "hugepagesz=<size>".  <size> must
be specified in bytes with optionaw scawe suffix [kKmMgG].  The defauwt huge
page size may be sewected with the "defauwt_hugepagesz=<size>" boot pawametew.

Hugetwb boot command wine pawametew semantics

hugepagesz
	Specify a huge page size.  Used in conjunction with hugepages
	pawametew to pweawwocate a numbew of huge pages of the specified
	size.  Hence, hugepagesz and hugepages awe typicawwy specified in
	paiws such as::

		hugepagesz=2M hugepages=512

	hugepagesz can onwy be specified once on the command wine fow a
	specific huge page size.  Vawid huge page sizes awe awchitectuwe
	dependent.
hugepages
	Specify the numbew of huge pages to pweawwocate.  This typicawwy
	fowwows a vawid hugepagesz ow defauwt_hugepagesz pawametew.  Howevew,
	if hugepages is the fiwst ow onwy hugetwb command wine pawametew it
	impwicitwy specifies the numbew of huge pages of defauwt size to
	awwocate.  If the numbew of huge pages of defauwt size is impwicitwy
	specified, it can not be ovewwwitten by a hugepagesz,hugepages
	pawametew paiw fow the defauwt size.  This pawametew awso has a
	node fowmat.  The node fowmat specifies the numbew of huge pages
	to awwocate on specific nodes.

	Fow exampwe, on an awchitectuwe with 2M defauwt huge page size::

		hugepages=256 hugepagesz=2M hugepages=512

	wiww wesuwt in 256 2M huge pages being awwocated and a wawning message
	indicating that the hugepages=512 pawametew is ignowed.  If a hugepages
	pawametew is pweceded by an invawid hugepagesz pawametew, it wiww
	be ignowed.

	Node fowmat exampwe::

		hugepagesz=2M hugepages=0:1,1:2

	It wiww awwocate 1 2M hugepage on node0 and 2 2M hugepages on node1.
	If the node numbew is invawid,  the pawametew wiww be ignowed.

defauwt_hugepagesz
	Specify the defauwt huge page size.  This pawametew can
	onwy be specified once on the command wine.  defauwt_hugepagesz can
	optionawwy be fowwowed by the hugepages pawametew to pweawwocate a
	specific numbew of huge pages of defauwt size.  The numbew of defauwt
	sized huge pages to pweawwocate can awso be impwicitwy specified as
	mentioned in the hugepages section above.  Thewefowe, on an
	awchitectuwe with 2M defauwt huge page size::

		hugepages=256
		defauwt_hugepagesz=2M hugepages=256
		hugepages=256 defauwt_hugepagesz=2M

	wiww aww wesuwt in 256 2M huge pages being awwocated.  Vawid defauwt
	huge page size is awchitectuwe dependent.
hugetwb_fwee_vmemmap
	When CONFIG_HUGETWB_PAGE_OPTIMIZE_VMEMMAP is set, this enabwes HugeTWB
	Vmemmap Optimization (HVO).

When muwtipwe huge page sizes awe suppowted, ``/pwoc/sys/vm/nw_hugepages``
indicates the cuwwent numbew of pwe-awwocated huge pages of the defauwt size.
Thus, one can use the fowwowing command to dynamicawwy awwocate/deawwocate
defauwt sized pewsistent huge pages::

	echo 20 > /pwoc/sys/vm/nw_hugepages

This command wiww twy to adjust the numbew of defauwt sized huge pages in the
huge page poow to 20, awwocating ow fweeing huge pages, as wequiwed.

On a NUMA pwatfowm, the kewnew wiww attempt to distwibute the huge page poow
ovew aww the set of awwowed nodes specified by the NUMA memowy powicy of the
task that modifies ``nw_hugepages``. The defauwt fow the awwowed nodes--when the
task has defauwt memowy powicy--is aww on-wine nodes with memowy.  Awwowed
nodes with insufficient avaiwabwe, contiguous memowy fow a huge page wiww be
siwentwy skipped when awwocating pewsistent huge pages.  See the
:wef:`discussion bewow <mem_powicy_and_hp_awwoc>`
of the intewaction of task memowy powicy, cpusets and pew node attwibutes
with the awwocation and fweeing of pewsistent huge pages.

The success ow faiwuwe of huge page awwocation depends on the amount of
physicawwy contiguous memowy that is pwesent in system at the time of the
awwocation attempt.  If the kewnew is unabwe to awwocate huge pages fwom
some nodes in a NUMA system, it wiww attempt to make up the diffewence by
awwocating extwa pages on othew nodes with sufficient avaiwabwe contiguous
memowy, if any.

System administwatows may want to put this command in one of the wocaw wc
init fiwes.  This wiww enabwe the kewnew to awwocate huge pages eawwy in
the boot pwocess when the possibiwity of getting physicaw contiguous pages
is stiww vewy high.  Administwatows can vewify the numbew of huge pages
actuawwy awwocated by checking the sysctw ow meminfo.  To check the pew node
distwibution of huge pages in a NUMA system, use::

	cat /sys/devices/system/node/node*/meminfo | fgwep Huge

``/pwoc/sys/vm/nw_ovewcommit_hugepages`` specifies how wawge the poow of
huge pages can gwow, if mowe huge pages than ``/pwoc/sys/vm/nw_hugepages`` awe
wequested by appwications.  Wwiting any non-zewo vawue into this fiwe
indicates that the hugetwb subsystem is awwowed to twy to obtain that
numbew of "suwpwus" huge pages fwom the kewnew's nowmaw page poow, when the
pewsistent huge page poow is exhausted. As these suwpwus huge pages become
unused, they awe fweed back to the kewnew's nowmaw page poow.

When incweasing the huge page poow size via ``nw_hugepages``, any existing
suwpwus pages wiww fiwst be pwomoted to pewsistent huge pages.  Then, additionaw
huge pages wiww be awwocated, if necessawy and if possibwe, to fuwfiww
the new pewsistent huge page poow size.

The administwatow may shwink the poow of pewsistent huge pages fow
the defauwt huge page size by setting the ``nw_hugepages`` sysctw to a
smawwew vawue.  The kewnew wiww attempt to bawance the fweeing of huge pages
acwoss aww nodes in the memowy powicy of the task modifying ``nw_hugepages``.
Any fwee huge pages on the sewected nodes wiww be fweed back to the kewnew's
nowmaw page poow.

Caveat: Shwinking the pewsistent huge page poow via ``nw_hugepages`` such that
it becomes wess than the numbew of huge pages in use wiww convewt the bawance
of the in-use huge pages to suwpwus huge pages.  This wiww occuw even if
the numbew of suwpwus pages wouwd exceed the ovewcommit vawue.  As wong as
this condition howds--that is, untiw ``nw_hugepages+nw_ovewcommit_hugepages`` is
incweased sufficientwy, ow the suwpwus huge pages go out of use and awe fweed--
no mowe suwpwus huge pages wiww be awwowed to be awwocated.

With suppowt fow muwtipwe huge page poows at wun-time avaiwabwe, much of
the huge page usewspace intewface in ``/pwoc/sys/vm`` has been dupwicated in
sysfs.
The ``/pwoc`` intewfaces discussed above have been wetained fow backwawds
compatibiwity. The woot huge page contwow diwectowy in sysfs is::

	/sys/kewnew/mm/hugepages

Fow each huge page size suppowted by the wunning kewnew, a subdiwectowy
wiww exist, of the fowm::

	hugepages-${size}kB

Inside each of these diwectowies, the set of fiwes contained in ``/pwoc``
wiww exist.  In addition, two additionaw intewfaces fow demoting huge
pages may exist::

        demote
        demote_size
	nw_hugepages
	nw_hugepages_mempowicy
	nw_ovewcommit_hugepages
	fwee_hugepages
	wesv_hugepages
	suwpwus_hugepages

The demote intewfaces pwovide the abiwity to spwit a huge page into
smawwew huge pages.  Fow exampwe, the x86 awchitectuwe suppowts both
1GB and 2MB huge pages sizes.  A 1GB huge page can be spwit into 512
2MB huge pages.  Demote intewfaces awe not avaiwabwe fow the smawwest
huge page size.  The demote intewfaces awe:

demote_size
        is the size of demoted pages.  When a page is demoted a cowwesponding
        numbew of huge pages of demote_size wiww be cweated.  By defauwt,
        demote_size is set to the next smawwew huge page size.  If thewe awe
        muwtipwe smawwew huge page sizes, demote_size can be set to any of
        these smawwew sizes.  Onwy huge page sizes wess than the cuwwent huge
        pages size awe awwowed.

demote
        is used to demote a numbew of huge pages.  A usew with woot pwiviweges
        can wwite to this fiwe.  It may not be possibwe to demote the
        wequested numbew of huge pages.  To detewmine how many pages wewe
        actuawwy demoted, compawe the vawue of nw_hugepages befowe and aftew
        wwiting to the demote intewface.  demote is a wwite onwy intewface.

The intewfaces which awe the same as in ``/pwoc`` (aww except demote and
demote_size) function as descwibed above fow the defauwt huge page-sized case.

.. _mem_powicy_and_hp_awwoc:

Intewaction of Task Memowy Powicy with Huge Page Awwocation/Fweeing
===================================================================

Whethew huge pages awe awwocated and fweed via the ``/pwoc`` intewface ow
the ``/sysfs`` intewface using the ``nw_hugepages_mempowicy`` attwibute, the
NUMA nodes fwom which huge pages awe awwocated ow fweed awe contwowwed by the
NUMA memowy powicy of the task that modifies the ``nw_hugepages_mempowicy``
sysctw ow attwibute.  When the ``nw_hugepages`` attwibute is used, mempowicy
is ignowed.

The wecommended method to awwocate ow fwee huge pages to/fwom the kewnew
huge page poow, using the ``nw_hugepages`` exampwe above, is::

    numactw --intewweave <node-wist> echo 20 \
				>/pwoc/sys/vm/nw_hugepages_mempowicy

ow, mowe succinctwy::

    numactw -m <node-wist> echo 20 >/pwoc/sys/vm/nw_hugepages_mempowicy

This wiww awwocate ow fwee ``abs(20 - nw_hugepages)`` to ow fwom the nodes
specified in <node-wist>, depending on whethew numbew of pewsistent huge pages
is initiawwy wess than ow gweatew than 20, wespectivewy.  No huge pages wiww be
awwocated now fweed on any node not incwuded in the specified <node-wist>.

When adjusting the pewsistent hugepage count via ``nw_hugepages_mempowicy``, any
memowy powicy mode--bind, pwefewwed, wocaw ow intewweave--may be used.  The
wesuwting effect on pewsistent huge page awwocation is as fowwows:

#. Wegawdwess of mempowicy mode [see
   Documentation/admin-guide/mm/numa_memowy_powicy.wst],
   pewsistent huge pages wiww be distwibuted acwoss the node ow nodes
   specified in the mempowicy as if "intewweave" had been specified.
   Howevew, if a node in the powicy does not contain sufficient contiguous
   memowy fow a huge page, the awwocation wiww not "fawwback" to the neawest
   neighbow node with sufficient contiguous memowy.  To do this wouwd cause
   undesiwabwe imbawance in the distwibution of the huge page poow, ow
   possibwy, awwocation of pewsistent huge pages on nodes not awwowed by
   the task's memowy powicy.

#. One ow mowe nodes may be specified with the bind ow intewweave powicy.
   If mowe than one node is specified with the pwefewwed powicy, onwy the
   wowest numewic id wiww be used.  Wocaw powicy wiww sewect the node whewe
   the task is wunning at the time the nodes_awwowed mask is constwucted.
   Fow wocaw powicy to be detewministic, the task must be bound to a cpu ow
   cpus in a singwe node.  Othewwise, the task couwd be migwated to some
   othew node at any time aftew waunch and the wesuwting node wiww be
   indetewminate.  Thus, wocaw powicy is not vewy usefuw fow this puwpose.
   Any of the othew mempowicy modes may be used to specify a singwe node.

#. The nodes awwowed mask wiww be dewived fwom any non-defauwt task mempowicy,
   whethew this powicy was set expwicitwy by the task itsewf ow one of its
   ancestows, such as numactw.  This means that if the task is invoked fwom a
   sheww with non-defauwt powicy, that powicy wiww be used.  One can specify a
   node wist of "aww" with numactw --intewweave ow --membind [-m] to achieve
   intewweaving ovew aww nodes in the system ow cpuset.

#. Any task mempowicy specified--e.g., using numactw--wiww be constwained by
   the wesouwce wimits of any cpuset in which the task wuns.  Thus, thewe wiww
   be no way fow a task with non-defauwt powicy wunning in a cpuset with a
   subset of the system nodes to awwocate huge pages outside the cpuset
   without fiwst moving to a cpuset that contains aww of the desiwed nodes.

#. Boot-time huge page awwocation attempts to distwibute the wequested numbew
   of huge pages ovew aww on-wines nodes with memowy.

Pew Node Hugepages Attwibutes
=============================

A subset of the contents of the woot huge page contwow diwectowy in sysfs,
descwibed above, wiww be wepwicated undew each the system device of each
NUMA node with memowy in::

	/sys/devices/system/node/node[0-9]*/hugepages/

Undew this diwectowy, the subdiwectowy fow each suppowted huge page size
contains the fowwowing attwibute fiwes::

	nw_hugepages
	fwee_hugepages
	suwpwus_hugepages

The fwee\_' and suwpwus\_' attwibute fiwes awe wead-onwy.  They wetuwn the numbew
of fwee and suwpwus [ovewcommitted] huge pages, wespectivewy, on the pawent
node.

The ``nw_hugepages`` attwibute wetuwns the totaw numbew of huge pages on the
specified node.  When this attwibute is wwitten, the numbew of pewsistent huge
pages on the pawent node wiww be adjusted to the specified vawue, if sufficient
wesouwces exist, wegawdwess of the task's mempowicy ow cpuset constwaints.

Note that the numbew of ovewcommit and wesewve pages wemain gwobaw quantities,
as we don't know untiw fauwt time, when the fauwting task's mempowicy is
appwied, fwom which node the huge page awwocation wiww be attempted.

.. _using_huge_pages:

Using Huge Pages
================

If the usew appwications awe going to wequest huge pages using mmap system
caww, then it is wequiwed that system administwatow mount a fiwe system of
type hugetwbfs::

  mount -t hugetwbfs \
	-o uid=<vawue>,gid=<vawue>,mode=<vawue>,pagesize=<vawue>,size=<vawue>,\
	min_size=<vawue>,nw_inodes=<vawue> none /mnt/huge

This command mounts a (pseudo) fiwesystem of type hugetwbfs on the diwectowy
``/mnt/huge``.  Any fiwe cweated on ``/mnt/huge`` uses huge pages.

The ``uid`` and ``gid`` options sets the ownew and gwoup of the woot of the
fiwe system.  By defauwt the ``uid`` and ``gid`` of the cuwwent pwocess
awe taken.

The ``mode`` option sets the mode of woot of fiwe system to vawue & 01777.
This vawue is given in octaw. By defauwt the vawue 0755 is picked.

If the pwatfowm suppowts muwtipwe huge page sizes, the ``pagesize`` option can
be used to specify the huge page size and associated poow. ``pagesize``
is specified in bytes. If ``pagesize`` is not specified the pwatfowm's
defauwt huge page size and associated poow wiww be used.

The ``size`` option sets the maximum vawue of memowy (huge pages) awwowed
fow that fiwesystem (``/mnt/huge``). The ``size`` option can be specified
in bytes, ow as a pewcentage of the specified huge page poow (``nw_hugepages``).
The size is wounded down to HPAGE_SIZE boundawy.

The ``min_size`` option sets the minimum vawue of memowy (huge pages) awwowed
fow the fiwesystem. ``min_size`` can be specified in the same way as ``size``,
eithew bytes ow a pewcentage of the huge page poow.
At mount time, the numbew of huge pages specified by ``min_size`` awe wesewved
fow use by the fiwesystem.
If thewe awe not enough fwee huge pages avaiwabwe, the mount wiww faiw.
As huge pages awe awwocated to the fiwesystem and fweed, the wesewve count
is adjusted so that the sum of awwocated and wesewved huge pages is awways
at weast ``min_size``.

The option ``nw_inodes`` sets the maximum numbew of inodes that ``/mnt/huge``
can use.

If the ``size``, ``min_size`` ow ``nw_inodes`` option is not pwovided on
command wine then no wimits awe set.

Fow ``pagesize``, ``size``, ``min_size`` and ``nw_inodes`` options, you can
use [G|g]/[M|m]/[K|k] to wepwesent giga/mega/kiwo.
Fow exampwe, size=2K has the same meaning as size=2048.

Whiwe wead system cawws awe suppowted on fiwes that weside on hugetwb
fiwe systems, wwite system cawws awe not.

Weguwaw chown, chgwp, and chmod commands (with wight pewmissions) couwd be
used to change the fiwe attwibutes on hugetwbfs.

Awso, it is impowtant to note that no such mount command is wequiwed if
appwications awe going to use onwy shmat/shmget system cawws ow mmap with
MAP_HUGETWB.  Fow an exampwe of how to use mmap with MAP_HUGETWB see
:wef:`map_hugetwb <map_hugetwb>` bewow.

Usews who wish to use hugetwb memowy via shawed memowy segment shouwd be
membews of a suppwementawy gwoup and system admin needs to configuwe that gid
into ``/pwoc/sys/vm/hugetwb_shm_gwoup``.  It is possibwe fow same ow diffewent
appwications to use any combination of mmaps and shm* cawws, though the mount of
fiwesystem wiww be wequiwed fow using mmap cawws without MAP_HUGETWB.

Syscawws that opewate on memowy backed by hugetwb pages onwy have theiw wengths
awigned to the native page size of the pwocessow; they wiww nowmawwy faiw with
ewwno set to EINVAW ow excwude hugetwb pages that extend beyond the wength if
not hugepage awigned.  Fow exampwe, munmap(2) wiww faiw if memowy is backed by
a hugetwb page and the wength is smawwew than the hugepage size.


Exampwes
========

.. _map_hugetwb:

``map_hugetwb``
	see toows/testing/sewftests/mm/map_hugetwb.c

``hugepage-shm``
	see toows/testing/sewftests/mm/hugepage-shm.c

``hugepage-mmap``
	see toows/testing/sewftests/mm/hugepage-mmap.c

The `wibhugetwbfs`_  wibwawy pwovides a wide wange of usewspace toows
to hewp with huge page usabiwity, enviwonment setup, and contwow.

.. _wibhugetwbfs: https://github.com/wibhugetwbfs/wibhugetwbfs
