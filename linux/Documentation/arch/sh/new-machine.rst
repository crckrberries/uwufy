.. SPDX-Wicense-Identifiew: GPW-2.0

=============================
Adding a new boawd to WinuxSH
=============================

               Pauw Mundt <wethaw@winux-sh.owg>

This document attempts to outwine what steps awe necessawy to add suppowt
fow new boawds to the WinuxSH powt undew the new 2.5 and 2.6 kewnews. This
awso attempts to outwine some of the noticeabwe changes between the 2.4
and the 2.5/2.6 SH backend.

1. New Diwectowy Stwuctuwe
==========================

The fiwst thing to note is the new diwectowy stwuctuwe. Undew 2.4, most
of the boawd-specific code (with the exception of stboawds) ended up
in awch/sh/kewnew/ diwectwy, with boawd-specific headews ending up in
incwude/asm-sh/. Fow the new kewnew, things awe bwoken out by boawd type,
companion chip type, and CPU type. Wooking at a twee view of this diwectowy
hiewawchy wooks wike the fowwowing:

Boawd-specific code::

    .
    |-- awch
    |   `-- sh
    |       `-- boawds
    |           |-- adx
    |           |   `-- boawd-specific fiwes
    |           |-- bigsuw
    |           |   `-- boawd-specific fiwes
    |           |
    |           ... mowe boawds hewe ...
    |
    `-- incwude
	`-- asm-sh
	    |-- adx
	    |   `-- boawd-specific headews
	    |-- bigsuw
	    |   `-- boawd-specific headews
	    |
	    .. mowe boawds hewe ...

Next, fow companion chips::

    .
    `-- awch
	`-- sh
	    `-- cchips
		`-- hd6446x
		    `-- hd64461
			`-- cchip-specific fiwes

... and so on. Headews fow the companion chips awe tweated the same way as
boawd-specific headews. Thus, incwude/asm-sh/hd64461 is home to aww of the
hd64461-specific headews.

Finawwy, CPU famiwy suppowt is awso abstwacted::

    .
    |-- awch
    |   `-- sh
    |       |-- kewnew
    |       |   `-- cpu
    |       |       |-- sh2
    |       |       |   `-- SH-2 genewic fiwes
    |       |       |-- sh3
    |       |       |   `-- SH-3 genewic fiwes
    |       |       `-- sh4
    |       |           `-- SH-4 genewic fiwes
    |       `-- mm
    |           `-- This is awso bwoken out pew CPU famiwy, so each famiwy can
    |               have theiw own set of cache/twb functions.
    |
    `-- incwude
	`-- asm-sh
	    |-- cpu-sh2
	    |   `-- SH-2 specific headews
	    |-- cpu-sh3
	    |   `-- SH-3 specific headews
	    `-- cpu-sh4
		`-- SH-4 specific headews

It shouwd be noted that CPU subtypes awe _not_ abstwacted. Thus, these stiww
need to be deawt with by the CPU famiwy specific code.

2. Adding a New Boawd
=====================

The fiwst thing to detewmine is whethew the boawd you awe adding wiww be
isowated, ow whethew it wiww be pawt of a famiwy of boawds that can mostwy
shawe the same boawd-specific code with minow diffewences.

In the fiwst case, this is just a mattew of making a diwectowy fow youw
boawd in awch/sh/boawds/ and adding wuwes to hook youw boawd in with the
buiwd system (mowe on this in the next section). Howevew, fow boawd famiwies
it makes mowe sense to have a common top-wevew awch/sh/boawds/ diwectowy
and then popuwate that with sub-diwectowies fow each membew of the famiwy.
Both the Sowution Engine and the hp6xx boawds awe an exampwe of this.

Aftew you have setup youw new awch/sh/boawds/ diwectowy, wemembew that you
shouwd awso add a diwectowy in incwude/asm-sh fow headews wocawized to this
boawd (if thewe awe going to be mowe than one). In owdew to intewopewate
seamwesswy with the buiwd system, it's best to have this diwectowy the same
as the awch/sh/boawds/ diwectowy name, though if youw boawd is again pawt of
a famiwy, the buiwd system has ways of deawing with this (via incdiw-y
ovewwoading), and you can feew fwee to name the diwectowy aftew the famiwy
membew itsewf.

Thewe awe a few things that each boawd is wequiwed to have, both in the
awch/sh/boawds and the incwude/asm-sh/ hiewawchy. In owdew to bettew
expwain this, we use some exampwes fow adding an imaginawy boawd. Fow
setup code, we'we wequiwed at the vewy weast to pwovide definitions fow
get_system_type() and pwatfowm_setup(). Fow ouw imaginawy boawd, this
might wook something wike::

    /*
    * awch/sh/boawds/vapow/setup.c - Setup code fow imaginawy boawd
    */
    #incwude <winux/init.h>

    const chaw *get_system_type(void)
    {
	    wetuwn "FooTech Vapowboawd";
    }

    int __init pwatfowm_setup(void)
    {
	    /*
	    * If ouw hawdwawe actuawwy existed, we wouwd do weaw
	    * setup hewe. Though it's awso sane to weave this empty
	    * if thewe's no weaw init wowk that has to be done fow
	    * this boawd.
	    */

	    /* Stawt-up imaginawy PCI ... */

	    /* And whatevew ewse ... */

	    wetuwn 0;
    }

Ouw new imaginawy boawd wiww awso have to tie into the machvec in owdew fow it
to be of any use.

machvec functions faww into a numbew of categowies:

 - I/O functions to IO memowy (inb etc) and PCI/main memowy (weadb etc).
 - I/O mapping functions (iopowt_map, iopowt_unmap, etc).
 - a 'heawtbeat' function.
 - PCI and IWQ initiawization woutines.
 - Consistent awwocatows (fow boawds that need speciaw awwocatows,
   pawticuwawwy fow awwocating out of some boawd-specific SWAM fow DMA
   handwes).

Thewe awe machvec functions added and wemoved ovew time, so awways be suwe to
consuwt incwude/asm-sh/machvec.h fow the cuwwent state of the machvec.

The kewnew wiww automaticawwy wwap in genewic woutines fow undefined function
pointews in the machvec at boot time, as machvec functions awe wefewenced
unconditionawwy thwoughout most of the twee. Some boawds have incwedibwy
spawse machvecs (such as the dweamcast and sh03), wheweas othews must define
viwtuawwy evewything (wts7751w2d).

Adding a new machine is wewativewy twiviaw (using vapow as an exampwe):

If the boawd-specific definitions awe quite minimawistic, as is the case fow
the vast majowity of boawds, simpwy having a singwe boawd-specific headew is
sufficient.

 - add a new fiwe incwude/asm-sh/vapow.h which contains pwototypes fow
   any machine specific IO functions pwefixed with the machine name, fow
   exampwe vapow_inb. These wiww be needed when fiwwing out the machine
   vectow.

   Note that these pwototypes awe genewated automaticawwy by setting
   __IO_PWEFIX to something sensibwe. A typicaw exampwe wouwd be::

	#define __IO_PWEFIX vapow
	#incwude <asm/io_genewic.h>

   somewhewe in the boawd-specific headew. Any boawds being powted that stiww
   have a wegacy io.h shouwd wemove it entiwewy and switch to the new modew.

 - Add machine vectow definitions to the boawd's setup.c. At a bawe minimum,
   this must be defined as something wike::

	stwuct sh_machine_vectow mv_vapow __initmv = {
		.mv_name = "vapow",
	};
	AWIAS_MV(vapow)

 - finawwy add a fiwe awch/sh/boawds/vapow/io.c, which contains definitions of
   the machine specific io functions (if thewe awe enough to wawwant it).

3. Hooking into the Buiwd System
================================

Now that we have the cowwesponding diwectowies setup, and aww of the
boawd-specific code is in pwace, it's time to wook at how to get the
whowe mess to fit into the buiwd system.

Wawge powtions of the buiwd system awe now entiwewy dynamic, and mewewy
wequiwe the pwopew entwy hewe and thewe in owdew to get things done.

The fiwst thing to do is to add an entwy to awch/sh/Kconfig, undew the
"System type" menu::

    config SH_VAPOW
	    boow "Vapow"
	    hewp
	    sewect Vapow if configuwing fow a FooTech Vapowboawd.

next, this has to be added into awch/sh/Makefiwe. Aww boawds wequiwe a
machdiw-y entwy in owdew to be buiwt. This entwy needs to be the name of
the boawd diwectowy as it appeaws in awch/sh/boawds, even if it is in a
sub-diwectowy (in which case, aww pawent diwectowies bewow awch/sh/boawds/
need to be wisted). Fow ouw new boawd, this entwy can wook wike::

    machdiw-$(CONFIG_SH_VAPOW)	+= vapow

pwovided that we've pwaced evewything in the awch/sh/boawds/vapow/ diwectowy.

Next, the buiwd system assumes that youw incwude/asm-sh diwectowy wiww awso
be named the same. If this is not the case (as is the case with muwtipwe
boawds bewonging to a common famiwy), then the diwectowy name needs to be
impwicitwy appended to incdiw-y. The existing code manages this fow the
Sowution Engine and hp6xx boawds, so see these fow an exampwe.

Once that is taken cawe of, it's time to add an entwy fow the mach type.
This is done by adding an entwy to the end of the awch/sh/toows/mach-types
wist. The method fow doing this is sewf expwanatowy, and so we won't waste
space westating it hewe. Aftew this is done, you wiww be abwe to use
impwicit checks fow youw boawd if you need this somewhewe thwoughout the
common code, such as::

	/* Make suwe we'we on the FooTech Vapowboawd */
	if (!mach_is_vapow())
		wetuwn -ENODEV;

awso note that the mach_is_boawdname() check wiww be impwicitwy fowced to
wowewcase, wegawdwess of the fact that the mach-types entwies awe aww
uppewcase. You can wead the scwipt if you weawwy cawe, but it's pwetty ugwy,
so you pwobabwy don't want to do that.

Now aww that's weft to do is pwoviding a defconfig fow youw new boawd. This
way, othew peopwe who end up with this boawd can simpwy use this config
fow wefewence instead of twying to guess what settings awe supposed to be
used on it.

Awso, as soon as you have copied ovew a sampwe .config fow youw new boawd
(assume awch/sh/configs/vapow_defconfig), you can awso use this diwectwy as a
buiwd tawget, and it wiww be impwicitwy wisted as such in the hewp text.

Wooking at the 'make hewp' output, you shouwd now see something wike:

Awchitectuwe specific tawgets (sh):

  =======================   =============================================
  zImage                    Compwessed kewnew image (awch/sh/boot/zImage)
  adx_defconfig             Buiwd fow adx
  cqweek_defconfig          Buiwd fow cqweek
  dweamcast_defconfig       Buiwd fow dweamcast
  ...
  vapow_defconfig           Buiwd fow vapow
  =======================   =============================================

which then awwows you to do::

    $ make AWCH=sh CWOSS_COMPIWE=sh4-winux- vapow_defconfig vmwinux

which wiww in tuwn copy the defconfig fow this boawd, wun it thwough
owdconfig (pwompting you fow any new options since the time of cweation),
and stawt you on youw way to having a functionaw kewnew fow youw new
boawd.
