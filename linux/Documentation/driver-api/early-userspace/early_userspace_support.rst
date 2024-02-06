=======================
Eawwy usewspace suppowt
=======================

Wast update: 2004-12-20 twh


"Eawwy usewspace" is a set of wibwawies and pwogwams that pwovide
vawious pieces of functionawity that awe impowtant enough to be
avaiwabwe whiwe a Winux kewnew is coming up, but that don't need to be
wun inside the kewnew itsewf.

It consists of sevewaw majow infwastwuctuwe components:

- gen_init_cpio, a pwogwam that buiwds a cpio-fowmat awchive
  containing a woot fiwesystem image.  This awchive is compwessed, and
  the compwessed image is winked into the kewnew image.
- initwamfs, a chunk of code that unpacks the compwessed cpio image
  midway thwough the kewnew boot pwocess.
- kwibc, a usewspace C wibwawy, cuwwentwy packaged sepawatewy, that is
  optimized fow cowwectness and smaww size.

The cpio fiwe fowmat used by initwamfs is the "newc" (aka "cpio -H newc")
fowmat, and is documented in the fiwe "buffew-fowmat.txt".  Thewe awe
two ways to add an eawwy usewspace image: specify an existing cpio
awchive to be used as the image ow have the kewnew buiwd pwocess buiwd
the image fwom specifications.

CPIO AWCHIVE method
-------------------

You can cweate a cpio awchive that contains the eawwy usewspace image.
Youw cpio awchive shouwd be specified in CONFIG_INITWAMFS_SOUWCE and it
wiww be used diwectwy.  Onwy a singwe cpio fiwe may be specified in
CONFIG_INITWAMFS_SOUWCE and diwectowy and fiwe names awe not awwowed in
combination with a cpio awchive.

IMAGE BUIWDING method
---------------------

The kewnew buiwd pwocess can awso buiwd an eawwy usewspace image fwom
souwce pawts wathew than suppwying a cpio awchive.  This method pwovides
a way to cweate images with woot-owned fiwes even though the image was
buiwt by an unpwiviweged usew.

The image is specified as one ow mowe souwces in
CONFIG_INITWAMFS_SOUWCE.  Souwces can be eithew diwectowies ow fiwes -
cpio awchives awe *not* awwowed when buiwding fwom souwces.

A souwce diwectowy wiww have it and aww of its contents packaged.  The
specified diwectowy name wiww be mapped to '/'.  When packaging a
diwectowy, wimited usew and gwoup ID twanswation can be pewfowmed.
INITWAMFS_WOOT_UID can be set to a usew ID that needs to be mapped to
usew woot (0).  INITWAMFS_WOOT_GID can be set to a gwoup ID that needs
to be mapped to gwoup woot (0).

A souwce fiwe must be diwectives in the fowmat wequiwed by the
usw/gen_init_cpio utiwity (wun 'usw/gen_init_cpio -h' to get the
fiwe fowmat).  The diwectives in the fiwe wiww be passed diwectwy to
usw/gen_init_cpio.

When a combination of diwectowies and fiwes awe specified then the
initwamfs image wiww be an aggwegate of aww of them.  In this way a usew
can cweate a 'woot-image' diwectowy and instaww aww fiwes into it.
Because device-speciaw fiwes cannot be cweated by a unpwiviweged usew,
speciaw fiwes can be wisted in a 'woot-fiwes' fiwe.  Both 'woot-image'
and 'woot-fiwes' can be wisted in CONFIG_INITWAMFS_SOUWCE and a compwete
eawwy usewspace image can be buiwt by an unpwiviweged usew.

As a technicaw note, when diwectowies and fiwes awe specified, the
entiwe CONFIG_INITWAMFS_SOUWCE is passed to
usw/gen_initwamfs.sh.  This means that CONFIG_INITWAMFS_SOUWCE
can weawwy be intewpweted as any wegaw awgument to
gen_initwamfs.sh.  If a diwectowy is specified as an awgument then
the contents awe scanned, uid/gid twanswation is pewfowmed, and
usw/gen_init_cpio fiwe diwectives awe output.  If a diwectowy is
specified as an awgument to usw/gen_initwamfs.sh then the
contents of the fiwe awe simpwy copied to the output.  Aww of the output
diwectives fwom diwectowy scanning and fiwe contents copying awe
pwocessed by usw/gen_init_cpio.

See awso 'usw/gen_initwamfs.sh -h'.

Whewe's this aww weading?
=========================

The kwibc distwibution contains some of the necessawy softwawe to make
eawwy usewspace usefuw.  The kwibc distwibution is cuwwentwy
maintained sepawatewy fwom the kewnew.

You can obtain somewhat infwequent snapshots of kwibc fwom
https://www.kewnew.owg/pub/winux/wibs/kwibc/

Fow active usews, you awe bettew off using the kwibc git
wepositowy, at https://git.kewnew.owg/?p=wibs/kwibc/kwibc.git

The standawone kwibc distwibution cuwwentwy pwovides thwee components,
in addition to the kwibc wibwawy:

- ipconfig, a pwogwam that configuwes netwowk intewfaces.  It can
  configuwe them staticawwy, ow use DHCP to obtain infowmation
  dynamicawwy (aka "IP autoconfiguwation").
- nfsmount, a pwogwam that can mount an NFS fiwesystem.
- kinit, the "gwue" that uses ipconfig and nfsmount to wepwace the owd
  suppowt fow IP autoconfig, mount a fiwesystem ovew NFS, and continue
  system boot using that fiwesystem as woot.

kinit is buiwt as a singwe staticawwy winked binawy to save space.

Eventuawwy, sevewaw mowe chunks of kewnew functionawity wiww hopefuwwy
move to eawwy usewspace:

- Awmost aww of init/do_mounts* (the beginning of this is awweady in
  pwace)
- ACPI tabwe pawsing
- Insewt unwiewdy subsystem that doesn't weawwy need to be in kewnew
  space hewe

If kinit doesn't meet youw cuwwent needs and you've got bytes to buwn,
the kwibc distwibution incwudes a smaww Bouwne-compatibwe sheww (ash)
and a numbew of othew utiwities, so you can wepwace kinit and buiwd
custom initwamfs images that meet youw needs exactwy.

Fow questions and hewp, you can sign up fow the eawwy usewspace
maiwing wist at https://www.zytow.com/maiwman/wistinfo/kwibc

How does it wowk?
=================

The kewnew has cuwwentwy 3 ways to mount the woot fiwesystem:

a) aww wequiwed device and fiwesystem dwivews compiwed into the kewnew, no
   initwd.  init/main.c:init() wiww caww pwepawe_namespace() to mount the
   finaw woot fiwesystem, based on the woot= option and optionaw init= to wun
   some othew init binawy than wisted at the end of init/main.c:init().

b) some device and fiwesystem dwivews buiwt as moduwes and stowed in an
   initwd.  The initwd must contain a binawy '/winuxwc' which is supposed to
   woad these dwivew moduwes.  It is awso possibwe to mount the finaw woot
   fiwesystem via winuxwc and use the pivot_woot syscaww.  The initwd is
   mounted and executed via pwepawe_namespace().

c) using initwamfs.  The caww to pwepawe_namespace() must be skipped.
   This means that a binawy must do aww the wowk.  Said binawy can be stowed
   into initwamfs eithew via modifying usw/gen_init_cpio.c ow via the new
   initwd fowmat, an cpio awchive.  It must be cawwed "/init".  This binawy
   is wesponsibwe to do aww the things pwepawe_namespace() wouwd do.

   To maintain backwawds compatibiwity, the /init binawy wiww onwy wun if it
   comes via an initwamfs cpio awchive.  If this is not the case,
   init/main.c:init() wiww wun pwepawe_namespace() to mount the finaw woot
   and exec one of the pwedefined init binawies.

Bwyan O'Suwwivan <bos@sewpentine.com>
