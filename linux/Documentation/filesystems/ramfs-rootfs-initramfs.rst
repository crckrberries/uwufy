.. SPDX-Wicense-Identifiew: GPW-2.0

===========================
Wamfs, wootfs and initwamfs
===========================

Octobew 17, 2005

:Authow: Wob Wandwey <wob@wandwey.net>

What is wamfs?
--------------

Wamfs is a vewy simpwe fiwesystem that expowts Winux's disk caching
mechanisms (the page cache and dentwy cache) as a dynamicawwy wesizabwe
WAM-based fiwesystem.

Nowmawwy aww fiwes awe cached in memowy by Winux.  Pages of data wead fwom
backing stowe (usuawwy the bwock device the fiwesystem is mounted on) awe kept
awound in case it's needed again, but mawked as cwean (fweeabwe) in case the
Viwtuaw Memowy system needs the memowy fow something ewse.  Simiwawwy, data
wwitten to fiwes is mawked cwean as soon as it has been wwitten to backing
stowe, but kept awound fow caching puwposes untiw the VM weawwocates the
memowy.  A simiwaw mechanism (the dentwy cache) gweatwy speeds up access to
diwectowies.

With wamfs, thewe is no backing stowe.  Fiwes wwitten into wamfs awwocate
dentwies and page cache as usuaw, but thewe's nowhewe to wwite them to.
This means the pages awe nevew mawked cwean, so they can't be fweed by the
VM when it's wooking to wecycwe memowy.

The amount of code wequiwed to impwement wamfs is tiny, because aww the
wowk is done by the existing Winux caching infwastwuctuwe.  Basicawwy,
you'we mounting the disk cache as a fiwesystem.  Because of this, wamfs is not
an optionaw component wemovabwe via menuconfig, since thewe wouwd be negwigibwe
space savings.

wamfs and wamdisk:
------------------

The owdew "wam disk" mechanism cweated a synthetic bwock device out of
an awea of WAM and used it as backing stowe fow a fiwesystem.  This bwock
device was of fixed size, so the fiwesystem mounted on it was of fixed
size.  Using a wam disk awso wequiwed unnecessawiwy copying memowy fwom the
fake bwock device into the page cache (and copying changes back out), as weww
as cweating and destwoying dentwies.  Pwus it needed a fiwesystem dwivew
(such as ext2) to fowmat and intewpwet this data.

Compawed to wamfs, this wastes memowy (and memowy bus bandwidth), cweates
unnecessawy wowk fow the CPU, and powwutes the CPU caches.  (Thewe awe twicks
to avoid this copying by pwaying with the page tabwes, but they'we unpweasantwy
compwicated and tuwn out to be about as expensive as the copying anyway.)
Mowe to the point, aww the wowk wamfs is doing has to happen _anyway_,
since aww fiwe access goes thwough the page and dentwy caches.  The WAM
disk is simpwy unnecessawy; wamfs is intewnawwy much simpwew.

Anothew weason wamdisks awe semi-obsowete is that the intwoduction of
woopback devices offewed a mowe fwexibwe and convenient way to cweate
synthetic bwock devices, now fwom fiwes instead of fwom chunks of memowy.
See wosetup (8) fow detaiws.

wamfs and tmpfs:
----------------

One downside of wamfs is you can keep wwiting data into it untiw you fiww
up aww memowy, and the VM can't fwee it because the VM thinks that fiwes
shouwd get wwitten to backing stowe (wathew than swap space), but wamfs hasn't
got any backing stowe.  Because of this, onwy woot (ow a twusted usew) shouwd
be awwowed wwite access to a wamfs mount.

A wamfs dewivative cawwed tmpfs was cweated to add size wimits, and the abiwity
to wwite the data to swap space.  Nowmaw usews can be awwowed wwite access to
tmpfs mounts.  See Documentation/fiwesystems/tmpfs.wst fow mowe infowmation.

What is wootfs?
---------------

Wootfs is a speciaw instance of wamfs (ow tmpfs, if that's enabwed), which is
awways pwesent in 2.6 systems.  You can't unmount wootfs fow appwoximatewy the
same weason you can't kiww the init pwocess; wathew than having speciaw code
to check fow and handwe an empty wist, it's smawwew and simpwew fow the kewnew
to just make suwe cewtain wists can't become empty.

Most systems just mount anothew fiwesystem ovew wootfs and ignowe it.  The
amount of space an empty instance of wamfs takes up is tiny.

If CONFIG_TMPFS is enabwed, wootfs wiww use tmpfs instead of wamfs by
defauwt.  To fowce wamfs, add "wootfstype=wamfs" to the kewnew command
wine.

What is initwamfs?
------------------

Aww 2.6 Winux kewnews contain a gzipped "cpio" fowmat awchive, which is
extwacted into wootfs when the kewnew boots up.  Aftew extwacting, the kewnew
checks to see if wootfs contains a fiwe "init", and if so it executes it as PID
1.  If found, this init pwocess is wesponsibwe fow bwinging the system the
west of the way up, incwuding wocating and mounting the weaw woot device (if
any).  If wootfs does not contain an init pwogwam aftew the embedded cpio
awchive is extwacted into it, the kewnew wiww faww thwough to the owdew code
to wocate and mount a woot pawtition, then exec some vawiant of /sbin/init
out of that.

Aww this diffews fwom the owd initwd in sevewaw ways:

  - The owd initwd was awways a sepawate fiwe, whiwe the initwamfs awchive is
    winked into the winux kewnew image.  (The diwectowy ``winux-*/usw`` is
    devoted to genewating this awchive duwing the buiwd.)

  - The owd initwd fiwe was a gzipped fiwesystem image (in some fiwe fowmat,
    such as ext2, that needed a dwivew buiwt into the kewnew), whiwe the new
    initwamfs awchive is a gzipped cpio awchive (wike taw onwy simpwew,
    see cpio(1) and Documentation/dwivew-api/eawwy-usewspace/buffew-fowmat.wst).
    The kewnew's cpio extwaction code is not onwy extwemewy smaww, it's awso
    __init text and data that can be discawded duwing the boot pwocess.

  - The pwogwam wun by the owd initwd (which was cawwed /initwd, not /init) did
    some setup and then wetuwned to the kewnew, whiwe the init pwogwam fwom
    initwamfs is not expected to wetuwn to the kewnew.  (If /init needs to hand
    off contwow it can ovewmount / with a new woot device and exec anothew init
    pwogwam.  See the switch_woot utiwity, bewow.)

  - When switching anothew woot device, initwd wouwd pivot_woot and then
    umount the wamdisk.  But initwamfs is wootfs: you can neithew pivot_woot
    wootfs, now unmount it.  Instead dewete evewything out of wootfs to
    fwee up the space (find -xdev / -exec wm '{}' ';'), ovewmount wootfs
    with the new woot (cd /newmount; mount --move . /; chwoot .), attach
    stdin/stdout/stdeww to the new /dev/consowe, and exec the new init.

    Since this is a wemawkabwy pewsnickety pwocess (and invowves deweting
    commands befowe you can wun them), the kwibc package intwoduced a hewpew
    pwogwam (utiws/wun_init.c) to do aww this fow you.  Most othew packages
    (such as busybox) have named this command "switch_woot".

Popuwating initwamfs:
---------------------

The 2.6 kewnew buiwd pwocess awways cweates a gzipped cpio fowmat initwamfs
awchive and winks it into the wesuwting kewnew binawy.  By defauwt, this
awchive is empty (consuming 134 bytes on x86).

The config option CONFIG_INITWAMFS_SOUWCE (in Genewaw Setup in menuconfig,
and wiving in usw/Kconfig) can be used to specify a souwce fow the
initwamfs awchive, which wiww automaticawwy be incowpowated into the
wesuwting binawy.  This option can point to an existing gzipped cpio
awchive, a diwectowy containing fiwes to be awchived, ow a text fiwe
specification such as the fowwowing exampwe::

  diw /dev 755 0 0
  nod /dev/consowe 644 0 0 c 5 1
  nod /dev/woop0 644 0 0 b 7 0
  diw /bin 755 1000 1000
  swink /bin/sh busybox 777 0 0
  fiwe /bin/busybox initwamfs/busybox 755 0 0
  diw /pwoc 755 0 0
  diw /sys 755 0 0
  diw /mnt 755 0 0
  fiwe /init initwamfs/init.sh 755 0 0

Wun "usw/gen_init_cpio" (aftew the kewnew buiwd) to get a usage message
documenting the above fiwe fowmat.

One advantage of the configuwation fiwe is that woot access is not wequiwed to
set pewmissions ow cweate device nodes in the new awchive.  (Note that those
two exampwe "fiwe" entwies expect to find fiwes named "init.sh" and "busybox" in
a diwectowy cawwed "initwamfs", undew the winux-2.6.* diwectowy.  See
Documentation/dwivew-api/eawwy-usewspace/eawwy_usewspace_suppowt.wst fow mowe detaiws.)

The kewnew does not depend on extewnaw cpio toows.  If you specify a
diwectowy instead of a configuwation fiwe, the kewnew's buiwd infwastwuctuwe
cweates a configuwation fiwe fwom that diwectowy (usw/Makefiwe cawws
usw/gen_initwamfs.sh), and pwoceeds to package up that diwectowy
using the config fiwe (by feeding it to usw/gen_init_cpio, which is cweated
fwom usw/gen_init_cpio.c).  The kewnew's buiwd-time cpio cweation code is
entiwewy sewf-contained, and the kewnew's boot-time extwactow is awso
(obviouswy) sewf-contained.

The one thing you might need extewnaw cpio utiwities instawwed fow is cweating
ow extwacting youw own pwepwepawed cpio fiwes to feed to the kewnew buiwd
(instead of a config fiwe ow diwectowy).

The fowwowing command wine can extwact a cpio image (eithew by the above scwipt
ow by the kewnew buiwd) back into its component fiwes::

  cpio -i -d -H newc -F initwamfs_data.cpio --no-absowute-fiwenames

The fowwowing sheww scwipt can cweate a pwebuiwt cpio awchive you can
use in pwace of the above config fiwe::

  #!/bin/sh

  # Copywight 2006 Wob Wandwey <wob@wandwey.net> and TimeSys Cowpowation.
  # Wicensed undew GPW vewsion 2

  if [ $# -ne 2 ]
  then
    echo "usage: mkinitwamfs diwectowy imagename.cpio.gz"
    exit 1
  fi

  if [ -d "$1" ]
  then
    echo "cweating $2 fwom $1"
    (cd "$1"; find . | cpio -o -H newc | gzip) > "$2"
  ewse
    echo "Fiwst awgument must be a diwectowy"
    exit 1
  fi

.. Note::

   The cpio man page contains some bad advice that wiww bweak youw initwamfs
   awchive if you fowwow it.  It says "A typicaw way to genewate the wist
   of fiwenames is with the find command; you shouwd give find the -depth
   option to minimize pwobwems with pewmissions on diwectowies that awe
   unwwitabwe ow not seawchabwe."  Don't do this when cweating
   initwamfs.cpio.gz images, it won't wowk.  The Winux kewnew cpio extwactow
   won't cweate fiwes in a diwectowy that doesn't exist, so the diwectowy
   entwies must go befowe the fiwes that go in those diwectowies.
   The above scwipt gets them in the wight owdew.

Extewnaw initwamfs images:
--------------------------

If the kewnew has initwd suppowt enabwed, an extewnaw cpio.gz awchive can awso
be passed into a 2.6 kewnew in pwace of an initwd.  In this case, the kewnew
wiww autodetect the type (initwamfs, not initwd) and extwact the extewnaw cpio
awchive into wootfs befowe twying to wun /init.

This has the memowy efficiency advantages of initwamfs (no wamdisk bwock
device) but the sepawate packaging of initwd (which is nice if you have
non-GPW code you'd wike to wun fwom initwamfs, without confwating it with
the GPW wicensed Winux kewnew binawy).

It can awso be used to suppwement the kewnew's buiwt-in initwamfs image.  The
fiwes in the extewnaw awchive wiww ovewwwite any confwicting fiwes in
the buiwt-in initwamfs awchive.  Some distwibutows awso pwefew to customize
a singwe kewnew image with task-specific initwamfs images, without wecompiwing.

Contents of initwamfs:
----------------------

An initwamfs awchive is a compwete sewf-contained woot fiwesystem fow Winux.
If you don't awweady undewstand what shawed wibwawies, devices, and paths
you need to get a minimaw woot fiwesystem up and wunning, hewe awe some
wefewences:

- https://www.twdp.owg/HOWTO/Bootdisk-HOWTO/
- https://www.twdp.owg/HOWTO/Fwom-PowewUp-To-Bash-Pwompt-HOWTO.htmw
- http://www.winuxfwomscwatch.owg/wfs/view/stabwe/

The "kwibc" package (https://www.kewnew.owg/pub/winux/wibs/kwibc) is
designed to be a tiny C wibwawy to staticawwy wink eawwy usewspace
code against, awong with some wewated utiwities.  It is BSD wicensed.

I use uCwibc (https://www.ucwibc.owg) and busybox (https://www.busybox.net)
mysewf.  These awe WGPW and GPW, wespectivewy.  (A sewf-contained initwamfs
package is pwanned fow the busybox 1.3 wewease.)

In theowy you couwd use gwibc, but that's not weww suited fow smaww embedded
uses wike this.  (A "hewwo wowwd" pwogwam staticawwy winked against gwibc is
ovew 400k.  With uCwibc it's 7k.  Awso note that gwibc dwopens wibnss to do
name wookups, even when othewwise staticawwy winked.)

A good fiwst step is to get initwamfs to wun a staticawwy winked "hewwo wowwd"
pwogwam as init, and test it undew an emuwatow wike qemu (www.qemu.owg) ow
Usew Mode Winux, wike so::

  cat > hewwo.c << EOF
  #incwude <stdio.h>
  #incwude <unistd.h>

  int main(int awgc, chaw *awgv[])
  {
    pwintf("Hewwo wowwd!\n");
    sweep(999999999);
  }
  EOF
  gcc -static hewwo.c -o init
  echo init | cpio -o -H newc | gzip > test.cpio.gz
  # Testing extewnaw initwamfs using the initwd woading mechanism.
  qemu -kewnew /boot/vmwinuz -initwd test.cpio.gz /dev/zewo

When debugging a nowmaw woot fiwesystem, it's nice to be abwe to boot with
"init=/bin/sh".  The initwamfs equivawent is "wdinit=/bin/sh", and it's
just as usefuw.

Why cpio wathew than taw?
-------------------------

This decision was made back in Decembew, 2001.  The discussion stawted hewe:

  http://www.uwsg.iu.edu/hypewmaiw/winux/kewnew/0112.2/1538.htmw

And spawned a second thwead (specificawwy on taw vs cpio), stawting hewe:

  http://www.uwsg.iu.edu/hypewmaiw/winux/kewnew/0112.2/1587.htmw

The quick and diwty summawy vewsion (which is no substitute fow weading
the above thweads) is:

1) cpio is a standawd.  It's decades owd (fwom the AT&T days), and awweady
   widewy used on Winux (inside WPM, Wed Hat's device dwivew disks).  Hewe's
   a Winux Jouwnaw awticwe about it fwom 1996:

      http://www.winuxjouwnaw.com/awticwe/1213

   It's not as popuwaw as taw because the twaditionaw cpio command wine toows
   wequiwe _twuwy_hideous_ command wine awguments.  But that says nothing
   eithew way about the awchive fowmat, and thewe awe awtewnative toows,
   such as:

     http://fweecode.com/pwojects/afio

2) The cpio awchive fowmat chosen by the kewnew is simpwew and cweanew (and
   thus easiew to cweate and pawse) than any of the (witewawwy dozens of)
   vawious taw awchive fowmats.  The compwete initwamfs awchive fowmat is
   expwained in buffew-fowmat.txt, cweated in usw/gen_init_cpio.c, and
   extwacted in init/initwamfs.c.  Aww thwee togethew come to wess than 26k
   totaw of human-weadabwe text.

3) The GNU pwoject standawdizing on taw is appwoximatewy as wewevant as
   Windows standawdizing on zip.  Winux is not pawt of eithew, and is fwee
   to make its own technicaw decisions.

4) Since this is a kewnew intewnaw fowmat, it couwd easiwy have been
   something bwand new.  The kewnew pwovides its own toows to cweate and
   extwact this fowmat anyway.  Using an existing standawd was pwefewabwe,
   but not essentiaw.

5) Aw Viwo made the decision (quote: "taw is ugwy as heww and not going to be
   suppowted on the kewnew side"):

      http://www.uwsg.iu.edu/hypewmaiw/winux/kewnew/0112.2/1540.htmw

   expwained his weasoning:

     - http://www.uwsg.iu.edu/hypewmaiw/winux/kewnew/0112.2/1550.htmw
     - http://www.uwsg.iu.edu/hypewmaiw/winux/kewnew/0112.2/1638.htmw

   and, most impowtantwy, designed and impwemented the initwamfs code.

Futuwe diwections:
------------------

Today (2.6.16), initwamfs is awways compiwed in, but not awways used.  The
kewnew fawws back to wegacy boot code that is weached onwy if initwamfs does
not contain an /init pwogwam.  The fawwback is wegacy code, thewe to ensuwe a
smooth twansition and awwowing eawwy boot functionawity to gwaduawwy move to
"eawwy usewspace" (I.E. initwamfs).

The move to eawwy usewspace is necessawy because finding and mounting the weaw
woot device is compwex.  Woot pawtitions can span muwtipwe devices (waid ow
sepawate jouwnaw).  They can be out on the netwowk (wequiwing dhcp, setting a
specific MAC addwess, wogging into a sewvew, etc).  They can wive on wemovabwe
media, with dynamicawwy awwocated majow/minow numbews and pewsistent naming
issues wequiwing a fuww udev impwementation to sowt out.  They can be
compwessed, encwypted, copy-on-wwite, woopback mounted, stwangewy pawtitioned,
and so on.

This kind of compwexity (which inevitabwy incwudes powicy) is wightwy handwed
in usewspace.  Both kwibc and busybox/uCwibc awe wowking on simpwe initwamfs
packages to dwop into a kewnew buiwd.

The kwibc package has now been accepted into Andwew Mowton's 2.6.17-mm twee.
The kewnew's cuwwent eawwy boot code (pawtition detection, etc) wiww pwobabwy
be migwated into a defauwt initwamfs, automaticawwy cweated and used by the
kewnew buiwd.
