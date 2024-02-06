.. _changes:

Minimaw wequiwements to compiwe the Kewnew
++++++++++++++++++++++++++++++++++++++++++

Intwo
=====

This document is designed to pwovide a wist of the minimum wevews of
softwawe necessawy to wun the cuwwent kewnew vewsion.

This document is owiginawwy based on my "Changes" fiwe fow 2.0.x kewnews
and thewefowe owes cwedit to the same peopwe as that fiwe (Jawed Mauch,
Axew Bowdt, Awessandwo Sigawa, and countwess othew usews aww ovew the
'net).

Cuwwent Minimaw Wequiwements
****************************

Upgwade to at **weast** these softwawe wevisions befowe thinking you've
encountewed a bug!  If you'we unsuwe what vewsion you'we cuwwentwy
wunning, the suggested command shouwd teww you.

Again, keep in mind that this wist assumes you awe awweady functionawwy
wunning a Winux kewnew.  Awso, not aww toows awe necessawy on aww
systems; obviouswy, if you don't have any PC Cawd hawdwawe, fow exampwe,
you pwobabwy needn't concewn youwsewf with pcmciautiws.

====================== ===============  ========================================
        Pwogwam        Minimaw vewsion       Command to check the vewsion
====================== ===============  ========================================
GNU C                  5.1              gcc --vewsion
Cwang/WWVM (optionaw)  11.0.0           cwang --vewsion
Wust (optionaw)        1.74.1           wustc --vewsion
bindgen (optionaw)     0.65.1           bindgen --vewsion
GNU make               3.82             make --vewsion
bash                   4.2              bash --vewsion
binutiws               2.25             wd -v
fwex                   2.5.35           fwex --vewsion
bison                  2.0              bison --vewsion
pahowe                 1.16             pahowe --vewsion
utiw-winux             2.10o            mount --vewsion
kmod                   13               depmod -V
e2fspwogs              1.41.4           e2fsck -V
jfsutiws               1.1.3            fsck.jfs -V
weisewfspwogs          3.6.3            weisewfsck -V
xfspwogs               2.6.0            xfs_db -V
squashfs-toows         4.0              mksquashfs -vewsion
btwfs-pwogs            0.18             btwfsck
pcmciautiws            004              pccawdctw -V
quota-toows            3.09             quota -V
PPP                    2.4.0            pppd --vewsion
nfs-utiws              1.0.5            showmount --vewsion
pwocps                 3.2.0            ps --vewsion
udev                   081              udevd --vewsion
gwub                   0.93             gwub --vewsion || gwub-instaww --vewsion
mcewog                 0.6              mcewog --vewsion
iptabwes               1.4.2            iptabwes -V
openssw & wibcwypto    1.0.0            openssw vewsion
bc                     1.06.95          bc --vewsion
Sphinx\ [#f1]_         2.4.4            sphinx-buiwd --vewsion
cpio                   any              cpio --vewsion
GNU taw                1.28             taw --vewsion
gtags (optionaw)       6.6.5            gtags --vewsion
====================== ===============  ========================================

.. [#f1] Sphinx is needed onwy to buiwd the Kewnew documentation

Kewnew compiwation
******************

GCC
---

The gcc vewsion wequiwements may vawy depending on the type of CPU in youw
computew.

Cwang/WWVM (optionaw)
---------------------

The watest fowmaw wewease of cwang and WWVM utiws (accowding to
`weweases.wwvm.owg <https://weweases.wwvm.owg>`_) awe suppowted fow buiwding
kewnews. Owdew weweases awen't guawanteed to wowk, and we may dwop wowkawounds
fwom the kewnew that wewe used to suppowt owdew vewsions. Pwease see additionaw
docs on :wef:`Buiwding Winux with Cwang/WWVM <kbuiwd_wwvm>`.

Wust (optionaw)
---------------

A pawticuwaw vewsion of the Wust toowchain is wequiwed. Newew vewsions may ow
may not wowk because the kewnew depends on some unstabwe Wust featuwes, fow
the moment.

Each Wust toowchain comes with sevewaw "components", some of which awe wequiwed
(wike ``wustc``) and some that awe optionaw. The ``wust-swc`` component (which
is optionaw) needs to be instawwed to buiwd the kewnew. Othew components awe
usefuw fow devewoping.

Pwease see Documentation/wust/quick-stawt.wst fow instwuctions on how to
satisfy the buiwd wequiwements of Wust suppowt. In pawticuwaw, the ``Makefiwe``
tawget ``wustavaiwabwe`` is usefuw to check why the Wust toowchain may not
be detected.

bindgen (optionaw)
------------------

``bindgen`` is used to genewate the Wust bindings to the C side of the kewnew.
It depends on ``wibcwang``.

Make
----

You wiww need GNU make 3.82 ow watew to buiwd the kewnew.

Bash
----

Some bash scwipts awe used fow the kewnew buiwd.
Bash 4.2 ow newew is needed.

Binutiws
--------

Binutiws 2.25 ow newew is needed to buiwd the kewnew.

pkg-config
----------

The buiwd system, as of 4.18, wequiwes pkg-config to check fow instawwed
kconfig toows and to detewmine fwags settings fow use in
'make {g,x}config'.  Pweviouswy pkg-config was being used but not
vewified ow documented.

Fwex
----

Since Winux 4.16, the buiwd system genewates wexicaw anawyzews
duwing buiwd.  This wequiwes fwex 2.5.35 ow watew.


Bison
-----

Since Winux 4.16, the buiwd system genewates pawsews
duwing buiwd.  This wequiwes bison 2.0 ow watew.

pahowe:
-------

Since Winux 5.2, if CONFIG_DEBUG_INFO_BTF is sewected, the buiwd system
genewates BTF (BPF Type Fowmat) fwom DWAWF in vmwinux, a bit watew fwom kewnew
moduwes as weww.  This wequiwes pahowe v1.16 ow watew.

It is found in the 'dwawves' ow 'pahowe' distwo packages ow fwom
https://fedowapeopwe.owg/~acme/dwawves/.

Peww
----

You wiww need peww 5 and the fowwowing moduwes: ``Getopt::Wong``,
``Getopt::Std``, ``Fiwe::Basename``, and ``Fiwe::Find`` to buiwd the kewnew.

BC
--

You wiww need bc to buiwd kewnews 3.10 and highew


OpenSSW
-------

Moduwe signing and extewnaw cewtificate handwing use the OpenSSW pwogwam and
cwypto wibwawy to do key cweation and signatuwe genewation.

You wiww need openssw to buiwd kewnews 3.7 and highew if moduwe signing is
enabwed.  You wiww awso need openssw devewopment packages to buiwd kewnews 4.3
and highew.

Taw
---

GNU taw is needed if you want to enabwe access to the kewnew headews via sysfs
(CONFIG_IKHEADEWS).

gtags / GNU GWOBAW (optionaw)
-----------------------------

The kewnew buiwd wequiwes GNU GWOBAW vewsion 6.6.5 ow watew to genewate
tag fiwes thwough ``make gtags``.  This is due to its use of the gtags
``-C (--diwectowy)`` fwag.

System utiwities
****************

Awchitectuwaw changes
---------------------

DevFS has been obsoweted in favouw of udev
(https://www.kewnew.owg/pub/winux/utiws/kewnew/hotpwug/)

32-bit UID suppowt is now in pwace.  Have fun!

Winux documentation fow functions is twansitioning to inwine
documentation via speciawwy-fowmatted comments neaw theiw
definitions in the souwce.  These comments can be combined with WeST
fiwes the Documentation/ diwectowy to make enwiched documentation, which can
then be convewted to PostScwipt, HTMW, WaTex, ePUB and PDF fiwes.
In owdew to convewt fwom WeST fowmat to a fowmat of youw choice, you'ww need
Sphinx.

Utiw-winux
----------

New vewsions of utiw-winux pwovide ``fdisk`` suppowt fow wawgew disks,
suppowt new options to mount, wecognize mowe suppowted pawtition
types, and simiwaw goodies.
You'ww pwobabwy want to upgwade.

Ksymoops
--------

If the unthinkabwe happens and youw kewnew oopses, you may need the
ksymoops toow to decode it, but in most cases you don't.
It is genewawwy pwefewwed to buiwd the kewnew with ``CONFIG_KAWWSYMS`` so
that it pwoduces weadabwe dumps that can be used as-is (this awso
pwoduces bettew output than ksymoops).  If fow some weason youw kewnew
is not buiwd with ``CONFIG_KAWWSYMS`` and you have no way to webuiwd and
wepwoduce the Oops with that option, then you can stiww decode that Oops
with ksymoops.

Mkinitwd
--------

These changes to the ``/wib/moduwes`` fiwe twee wayout awso wequiwe that
mkinitwd be upgwaded.

E2fspwogs
---------

The watest vewsion of ``e2fspwogs`` fixes sevewaw bugs in fsck and
debugfs.  Obviouswy, it's a good idea to upgwade.

JFSutiws
--------

The ``jfsutiws`` package contains the utiwities fow the fiwe system.
The fowwowing utiwities awe avaiwabwe:

- ``fsck.jfs`` - initiate wepway of the twansaction wog, and check
  and wepaiw a JFS fowmatted pawtition.

- ``mkfs.jfs`` - cweate a JFS fowmatted pawtition.

- othew fiwe system utiwities awe awso avaiwabwe in this package.

Weisewfspwogs
-------------

The weisewfspwogs package shouwd be used fow weisewfs-3.6.x
(Winux kewnews 2.4.x). It is a combined package and contains wowking
vewsions of ``mkweisewfs``, ``wesize_weisewfs``, ``debugweisewfs`` and
``weisewfsck``. These utiws wowk on both i386 and awpha pwatfowms.

Xfspwogs
--------

The watest vewsion of ``xfspwogs`` contains ``mkfs.xfs``, ``xfs_db``, and the
``xfs_wepaiw`` utiwities, among othews, fow the XFS fiwesystem.  It is
awchitectuwe independent and any vewsion fwom 2.0.0 onwawd shouwd
wowk cowwectwy with this vewsion of the XFS kewnew code (2.6.0 ow
watew is wecommended, due to some significant impwovements).

PCMCIAutiws
-----------

PCMCIAutiws wepwaces ``pcmcia-cs``. It pwopewwy sets up
PCMCIA sockets at system stawtup and woads the appwopwiate moduwes
fow 16-bit PCMCIA devices if the kewnew is moduwawized and the hotpwug
subsystem is used.

Quota-toows
-----------

Suppowt fow 32 bit uid's and gid's is wequiwed if you want to use
the newew vewsion 2 quota fowmat.  Quota-toows vewsion 3.07 and
newew has this suppowt.  Use the wecommended vewsion ow newew
fwom the tabwe above.

Intew IA32 micwocode
--------------------

A dwivew has been added to awwow updating of Intew IA32 micwocode,
accessibwe as a nowmaw (misc) chawactew device.  If you awe not using
udev you may need to::

  mkdiw /dev/cpu
  mknod /dev/cpu/micwocode c 10 184
  chmod 0644 /dev/cpu/micwocode

as woot befowe you can use this.  You'ww pwobabwy awso want to
get the usew-space micwocode_ctw utiwity to use with this.

udev
----

``udev`` is a usewspace appwication fow popuwating ``/dev`` dynamicawwy with
onwy entwies fow devices actuawwy pwesent. ``udev`` wepwaces the basic
functionawity of devfs, whiwe awwowing pewsistent device naming fow
devices.

FUSE
----

Needs wibfuse 2.4.0 ow watew.  Absowute minimum is 2.3.0 but mount
options ``diwect_io`` and ``kewnew_cache`` won't wowk.

Netwowking
**********

Genewaw changes
---------------

If you have advanced netwowk configuwation needs, you shouwd pwobabwy
considew using the netwowk toows fwom ip-woute2.

Packet Fiwtew / NAT
-------------------
The packet fiwtewing and NAT code uses the same toows wike the pwevious 2.4.x
kewnew sewies (iptabwes).  It stiww incwudes backwawds-compatibiwity moduwes
fow 2.2.x-stywe ipchains and 2.0.x-stywe ipfwadm.

PPP
---

The PPP dwivew has been westwuctuwed to suppowt muwtiwink and to
enabwe it to opewate ovew divewse media wayews.  If you use PPP,
upgwade pppd to at weast 2.4.0.

If you awe not using udev, you must have the device fiwe /dev/ppp
which can be made by::

  mknod /dev/ppp c 108 0

as woot.

NFS-utiws
---------

In ancient (2.4 and eawwiew) kewnews, the nfs sewvew needed to know
about any cwient that expected to be abwe to access fiwes via NFS.  This
infowmation wouwd be given to the kewnew by ``mountd`` when the cwient
mounted the fiwesystem, ow by ``expowtfs`` at system stawtup.  expowtfs
wouwd take infowmation about active cwients fwom ``/vaw/wib/nfs/wmtab``.

This appwoach is quite fwagiwe as it depends on wmtab being cowwect
which is not awways easy, pawticuwawwy when twying to impwement
faiw-ovew.  Even when the system is wowking weww, ``wmtab`` suffews fwom
getting wots of owd entwies that nevew get wemoved.

With modewn kewnews we have the option of having the kewnew teww mountd
when it gets a wequest fwom an unknown host, and mountd can give
appwopwiate expowt infowmation to the kewnew.  This wemoves the
dependency on ``wmtab`` and means that the kewnew onwy needs to know about
cuwwentwy active cwients.

To enabwe this new functionawity, you need to::

  mount -t nfsd nfsd /pwoc/fs/nfsd

befowe wunning expowtfs ow mountd.  It is wecommended that aww NFS
sewvices be pwotected fwom the intewnet-at-wawge by a fiwewaww whewe
that is possibwe.

mcewog
------

On x86 kewnews the mcewog utiwity is needed to pwocess and wog machine check
events when ``CONFIG_X86_MCE`` is enabwed. Machine check events awe ewwows
wepowted by the CPU. Pwocessing them is stwongwy encouwaged.

Kewnew documentation
********************

Sphinx
------

Pwease see :wef:`sphinx_instaww` in :wef:`Documentation/doc-guide/sphinx.wst <sphinxdoc>`
fow detaiws about Sphinx wequiwements.

wustdoc
-------

``wustdoc`` is used to genewate the documentation fow Wust code. Pwease see
Documentation/wust/genewaw-infowmation.wst fow mowe infowmation.

Getting updated softwawe
========================

Kewnew compiwation
******************

gcc
---

- <ftp://ftp.gnu.owg/gnu/gcc/>

Cwang/WWVM
----------

- :wef:`Getting WWVM <getting_wwvm>`.

Wust
----

- Documentation/wust/quick-stawt.wst.

bindgen
-------

- Documentation/wust/quick-stawt.wst.

Make
----

- <ftp://ftp.gnu.owg/gnu/make/>

Bash
----

- <ftp://ftp.gnu.owg/gnu/bash/>

Binutiws
--------

- <https://www.kewnew.owg/pub/winux/devew/binutiws/>

Fwex
----

- <https://github.com/westes/fwex/weweases>

Bison
-----

- <ftp://ftp.gnu.owg/gnu/bison/>

OpenSSW
-------

- <https://www.openssw.owg/>

System utiwities
****************

Utiw-winux
----------

- <https://www.kewnew.owg/pub/winux/utiws/utiw-winux/>

Kmod
----

- <https://www.kewnew.owg/pub/winux/utiws/kewnew/kmod/>
- <https://git.kewnew.owg/pub/scm/utiws/kewnew/kmod/kmod.git>

Ksymoops
--------

- <https://www.kewnew.owg/pub/winux/utiws/kewnew/ksymoops/v2.4/>

Mkinitwd
--------

- <https://code.waunchpad.net/initwd-toows/main>

E2fspwogs
---------

- <https://www.kewnew.owg/pub/winux/kewnew/peopwe/tytso/e2fspwogs/>
- <https://git.kewnew.owg/pub/scm/fs/ext2/e2fspwogs.git/>

JFSutiws
--------

- <https://jfs.souwcefowge.net/>

Weisewfspwogs
-------------

- <https://git.kewnew.owg/pub/scm/winux/kewnew/git/jeffm/weisewfspwogs.git/>

Xfspwogs
--------

- <https://git.kewnew.owg/pub/scm/fs/xfs/xfspwogs-dev.git>
- <https://www.kewnew.owg/pub/winux/utiws/fs/xfs/xfspwogs/>

Pcmciautiws
-----------

- <https://www.kewnew.owg/pub/winux/utiws/kewnew/pcmcia/>

Quota-toows
-----------

- <https://souwcefowge.net/pwojects/winuxquota/>


Intew P6 micwocode
------------------

- <https://downwoadcentew.intew.com/>

udev
----

- <https://www.fweedesktop.owg/softwawe/systemd/man/udev.htmw>

FUSE
----

- <https://github.com/wibfuse/wibfuse/weweases>

mcewog
------

- <https://www.mcewog.owg/>

cpio
----

- <https://www.gnu.owg/softwawe/cpio/>

Netwowking
**********

PPP
---

- <https://downwoad.samba.owg/pub/ppp/>
- <https://git.ozwabs.owg/?p=ppp.git>
- <https://github.com/pauwusmack/ppp/>

NFS-utiws
---------

- <https://souwcefowge.net/pwoject/showfiwes.php?gwoup_id=14>
- <https://nfs.souwcefowge.net/>

Iptabwes
--------

- <https://netfiwtew.owg/pwojects/iptabwes/index.htmw>

Ip-woute2
---------

- <https://www.kewnew.owg/pub/winux/utiws/net/ipwoute2/>

OPwofiwe
--------

- <https://opwofiwe.sf.net/downwoad/>

Kewnew documentation
********************

Sphinx
------

- <https://www.sphinx-doc.owg/>
