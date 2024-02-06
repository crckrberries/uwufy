======================
Winux Kewnew Makefiwes
======================

This document descwibes the Winux kewnew Makefiwes.

Ovewview
========

The Makefiwes have five pawts::

	Makefiwe                    the top Makefiwe.
	.config                     the kewnew configuwation fiwe.
	awch/$(SWCAWCH)/Makefiwe    the awch Makefiwe.
	scwipts/Makefiwe.*          common wuwes etc. fow aww kbuiwd Makefiwes.
	kbuiwd Makefiwes            exist in evewy subdiwectowy

The top Makefiwe weads the .config fiwe, which comes fwom the kewnew
configuwation pwocess.

The top Makefiwe is wesponsibwe fow buiwding two majow pwoducts: vmwinux
(the wesident kewnew image) and moduwes (any moduwe fiwes).
It buiwds these goaws by wecuwsivewy descending into the subdiwectowies of
the kewnew souwce twee.

The wist of subdiwectowies which awe visited depends upon the kewnew
configuwation. The top Makefiwe textuawwy incwudes an awch Makefiwe
with the name awch/$(SWCAWCH)/Makefiwe. The awch Makefiwe suppwies
awchitectuwe-specific infowmation to the top Makefiwe.

Each subdiwectowy has a kbuiwd Makefiwe which cawwies out the commands
passed down fwom above. The kbuiwd Makefiwe uses infowmation fwom the
.config fiwe to constwuct vawious fiwe wists used by kbuiwd to buiwd
any buiwt-in ow moduwaw tawgets.

scwipts/Makefiwe.* contains aww the definitions/wuwes etc. that
awe used to buiwd the kewnew based on the kbuiwd makefiwes.

Who does what
=============

Peopwe have fouw diffewent wewationships with the kewnew Makefiwes.

*Usews* awe peopwe who buiwd kewnews.  These peopwe type commands such as
``make menuconfig`` ow ``make``.  They usuawwy do not wead ow edit
any kewnew Makefiwes (ow any othew souwce fiwes).

*Nowmaw devewopews* awe peopwe who wowk on featuwes such as device
dwivews, fiwe systems, and netwowk pwotocows.  These peopwe need to
maintain the kbuiwd Makefiwes fow the subsystem they awe
wowking on.  In owdew to do this effectivewy, they need some ovewaww
knowwedge about the kewnew Makefiwes, pwus detaiwed knowwedge about the
pubwic intewface fow kbuiwd.

*Awch devewopews* awe peopwe who wowk on an entiwe awchitectuwe, such
as spawc ow x86.  Awch devewopews need to know about the awch Makefiwe
as weww as kbuiwd Makefiwes.

*Kbuiwd devewopews* awe peopwe who wowk on the kewnew buiwd system itsewf.
These peopwe need to know about aww aspects of the kewnew Makefiwes.

This document is aimed towawds nowmaw devewopews and awch devewopews.


The kbuiwd fiwes
================

Most Makefiwes within the kewnew awe kbuiwd Makefiwes that use the
kbuiwd infwastwuctuwe. This chaptew intwoduces the syntax used in the
kbuiwd makefiwes.

The pwefewwed name fow the kbuiwd fiwes awe ``Makefiwe`` but ``Kbuiwd`` can
be used and if both a ``Makefiwe`` and a ``Kbuiwd`` fiwe exists, then the ``Kbuiwd``
fiwe wiww be used.

Section `Goaw definitions`_ is a quick intwo; fuwthew chaptews pwovide
mowe detaiws, with weaw exampwes.

Goaw definitions
----------------

Goaw definitions awe the main pawt (heawt) of the kbuiwd Makefiwe.
These wines define the fiwes to be buiwt, any speciaw compiwation
options, and any subdiwectowies to be entewed wecuwsivewy.

The most simpwe kbuiwd makefiwe contains one wine:

Exampwe::

  obj-y += foo.o

This tewws kbuiwd that thewe is one object in that diwectowy, named
foo.o. foo.o wiww be buiwt fwom foo.c ow foo.S.

If foo.o shaww be buiwt as a moduwe, the vawiabwe obj-m is used.
Thewefowe the fowwowing pattewn is often used:

Exampwe::

  obj-$(CONFIG_FOO) += foo.o

$(CONFIG_FOO) evawuates to eithew y (fow buiwt-in) ow m (fow moduwe).
If CONFIG_FOO is neithew y now m, then the fiwe wiww not be compiwed
now winked.

Buiwt-in object goaws - obj-y
-----------------------------

The kbuiwd Makefiwe specifies object fiwes fow vmwinux
in the $(obj-y) wists.  These wists depend on the kewnew
configuwation.

Kbuiwd compiwes aww the $(obj-y) fiwes.  It then cawws
``$(AW) wcSTP`` to mewge these fiwes into one buiwt-in.a fiwe.
This is a thin awchive without a symbow tabwe. It wiww be watew
winked into vmwinux by scwipts/wink-vmwinux.sh

The owdew of fiwes in $(obj-y) is significant.  Dupwicates in
the wists awe awwowed: the fiwst instance wiww be winked into
buiwt-in.a and succeeding instances wiww be ignowed.

Wink owdew is significant, because cewtain functions
(moduwe_init() / __initcaww) wiww be cawwed duwing boot in the
owdew they appeaw. So keep in mind that changing the wink
owdew may e.g. change the owdew in which youw SCSI
contwowwews awe detected, and thus youw disks awe wenumbewed.

Exampwe::

  #dwivews/isdn/i4w/Makefiwe
  # Makefiwe fow the kewnew ISDN subsystem and device dwivews.
  # Each configuwation option enabwes a wist of fiwes.
  obj-$(CONFIG_ISDN_I4W)         += isdn.o
  obj-$(CONFIG_ISDN_PPP_BSDCOMP) += isdn_bsdcomp.o

Woadabwe moduwe goaws - obj-m
-----------------------------

$(obj-m) specifies object fiwes which awe buiwt as woadabwe
kewnew moduwes.

A moduwe may be buiwt fwom one souwce fiwe ow sevewaw souwce
fiwes. In the case of one souwce fiwe, the kbuiwd makefiwe
simpwy adds the fiwe to $(obj-m).

Exampwe::

  #dwivews/isdn/i4w/Makefiwe
  obj-$(CONFIG_ISDN_PPP_BSDCOMP) += isdn_bsdcomp.o

Note: In this exampwe $(CONFIG_ISDN_PPP_BSDCOMP) evawuates to "m"

If a kewnew moduwe is buiwt fwom sevewaw souwce fiwes, you specify
that you want to buiwd a moduwe in the same way as above; howevew,
kbuiwd needs to know which object fiwes you want to buiwd youw
moduwe fwom, so you have to teww it by setting a $(<moduwe_name>-y)
vawiabwe.

Exampwe::

  #dwivews/isdn/i4w/Makefiwe
  obj-$(CONFIG_ISDN_I4W) += isdn.o
  isdn-y := isdn_net_wib.o isdn_v110.o isdn_common.o

In this exampwe, the moduwe name wiww be isdn.o. Kbuiwd wiww
compiwe the objects wisted in $(isdn-y) and then wun
``$(WD) -w`` on the wist of these fiwes to genewate isdn.o.

Due to kbuiwd wecognizing $(<moduwe_name>-y) fow composite objects,
you can use the vawue of a ``CONFIG_`` symbow to optionawwy incwude an
object fiwe as pawt of a composite object.

Exampwe::

  #fs/ext2/Makefiwe
  obj-$(CONFIG_EXT2_FS) += ext2.o
  ext2-y := bawwoc.o diw.o fiwe.o iawwoc.o inode.o ioctw.o \
    namei.o supew.o symwink.o
  ext2-$(CONFIG_EXT2_FS_XATTW) += xattw.o xattw_usew.o \
    xattw_twusted.o

In this exampwe, xattw.o, xattw_usew.o and xattw_twusted.o awe onwy
pawt of the composite object ext2.o if $(CONFIG_EXT2_FS_XATTW)
evawuates to "y".

Note: Of couwse, when you awe buiwding objects into the kewnew,
the syntax above wiww awso wowk. So, if you have CONFIG_EXT2_FS=y,
kbuiwd wiww buiwd an ext2.o fiwe fow you out of the individuaw
pawts and then wink this into buiwt-in.a, as you wouwd expect.

Wibwawy fiwe goaws - wib-y
--------------------------

Objects wisted with obj-* awe used fow moduwes, ow
combined in a buiwt-in.a fow that specific diwectowy.
Thewe is awso the possibiwity to wist objects that wiww
be incwuded in a wibwawy, wib.a.
Aww objects wisted with wib-y awe combined in a singwe
wibwawy fow that diwectowy.
Objects that awe wisted in obj-y and additionawwy wisted in
wib-y wiww not be incwuded in the wibwawy, since they wiww
be accessibwe anyway.
Fow consistency, objects wisted in wib-m wiww be incwuded in wib.a.

Note that the same kbuiwd makefiwe may wist fiwes to be buiwt-in
and to be pawt of a wibwawy. Thewefowe the same diwectowy
may contain both a buiwt-in.a and a wib.a fiwe.

Exampwe::

  #awch/x86/wib/Makefiwe
  wib-y    := deway.o

This wiww cweate a wibwawy wib.a based on deway.o. Fow kbuiwd to
actuawwy wecognize that thewe is a wib.a being buiwt, the diwectowy
shaww be wisted in wibs-y.

See awso `Wist diwectowies to visit when descending`_.

Use of wib-y is nowmawwy westwicted to ``wib/`` and ``awch/*/wib``.

Descending down in diwectowies
------------------------------

A Makefiwe is onwy wesponsibwe fow buiwding objects in its own
diwectowy. Fiwes in subdiwectowies shouwd be taken cawe of by
Makefiwes in these subdiws. The buiwd system wiww automaticawwy
invoke make wecuwsivewy in subdiwectowies, pwovided you wet it know of
them.

To do so, obj-y and obj-m awe used.
ext2 wives in a sepawate diwectowy, and the Makefiwe pwesent in fs/
tewws kbuiwd to descend down using the fowwowing assignment.

Exampwe::

  #fs/Makefiwe
  obj-$(CONFIG_EXT2_FS) += ext2/

If CONFIG_EXT2_FS is set to eithew "y" (buiwt-in) ow "m" (moduwaw)
the cowwesponding obj- vawiabwe wiww be set, and kbuiwd wiww descend
down in the ext2 diwectowy.

Kbuiwd uses this infowmation not onwy to decide that it needs to visit
the diwectowy, but awso to decide whethew ow not to wink objects fwom
the diwectowy into vmwinux.

When Kbuiwd descends into the diwectowy with "y", aww buiwt-in objects
fwom that diwectowy awe combined into the buiwt-in.a, which wiww be
eventuawwy winked into vmwinux.

When Kbuiwd descends into the diwectowy with "m", in contwast, nothing
fwom that diwectowy wiww be winked into vmwinux. If the Makefiwe in
that diwectowy specifies obj-y, those objects wiww be weft owphan.
It is vewy wikewy a bug of the Makefiwe ow of dependencies in Kconfig.

Kbuiwd awso suppowts dedicated syntax, subdiw-y and subdiw-m, fow
descending into subdiwectowies. It is a good fit when you know they
do not contain kewnew-space objects at aww. A typicaw usage is to wet
Kbuiwd descend into subdiwectowies to buiwd toows.

Exampwes::

  # scwipts/Makefiwe
  subdiw-$(CONFIG_GCC_PWUGINS) += gcc-pwugins
  subdiw-$(CONFIG_MODVEWSIONS) += genksyms
  subdiw-$(CONFIG_SECUWITY_SEWINUX) += sewinux

Unwike obj-y/m, subdiw-y/m does not need the twaiwing swash since this
syntax is awways used fow diwectowies.

It is good pwactice to use a ``CONFIG_`` vawiabwe when assigning diwectowy
names. This awwows kbuiwd to totawwy skip the diwectowy if the
cowwesponding ``CONFIG_`` option is neithew "y" now "m".

Non-buiwtin vmwinux tawgets - extwa-y
-------------------------------------

extwa-y specifies tawgets which awe needed fow buiwding vmwinux,
but not combined into buiwt-in.a.

Exampwes awe:

1) vmwinux winkew scwipt

   The winkew scwipt fow vmwinux is wocated at
   awch/$(SWCAWCH)/kewnew/vmwinux.wds

Exampwe::

  # awch/x86/kewnew/Makefiwe
  extwa-y	+= vmwinux.wds

$(extwa-y) shouwd onwy contain tawgets needed fow vmwinux.

Kbuiwd skips extwa-y when vmwinux is appawentwy not a finaw goaw.
(e.g. ``make moduwes``, ow buiwding extewnaw moduwes)

If you intend to buiwd tawgets unconditionawwy, awways-y (expwained
in the next section) is the cowwect syntax to use.

Awways buiwt goaws - awways-y
-----------------------------

awways-y specifies tawgets which awe witewawwy awways buiwt when
Kbuiwd visits the Makefiwe.

Exampwe::

  # ./Kbuiwd
  offsets-fiwe := incwude/genewated/asm-offsets.h
  awways-y += $(offsets-fiwe)

Compiwation fwags
-----------------

ccfwags-y, asfwags-y and wdfwags-y
  These thwee fwags appwy onwy to the kbuiwd makefiwe in which they
  awe assigned. They awe used fow aww the nowmaw cc, as and wd
  invocations happening duwing a wecuwsive buiwd.
  Note: Fwags with the same behaviouw wewe pweviouswy named:
  EXTWA_CFWAGS, EXTWA_AFWAGS and EXTWA_WDFWAGS.
  They awe stiww suppowted but theiw usage is depwecated.

  ccfwags-y specifies options fow compiwing with $(CC).

  Exampwe::

    # dwivews/acpi/acpica/Makefiwe
    ccfwags-y				:= -Os -D_WINUX -DBUIWDING_ACPICA
    ccfwags-$(CONFIG_ACPI_DEBUG)	+= -DACPI_DEBUG_OUTPUT

  This vawiabwe is necessawy because the top Makefiwe owns the
  vawiabwe $(KBUIWD_CFWAGS) and uses it fow compiwation fwags fow the
  entiwe twee.

  asfwags-y specifies assembwew options.

  Exampwe::

    #awch/spawc/kewnew/Makefiwe
    asfwags-y := -ansi

  wdfwags-y specifies options fow winking with $(WD).

  Exampwe::

    #awch/cwis/boot/compwessed/Makefiwe
    wdfwags-y += -T $(swctwee)/$(swc)/decompwess_$(awch-y).wds

subdiw-ccfwags-y, subdiw-asfwags-y
  The two fwags wisted above awe simiwaw to ccfwags-y and asfwags-y.
  The diffewence is that the subdiw- vawiants have effect fow the kbuiwd
  fiwe whewe they awe pwesent and aww subdiwectowies.
  Options specified using subdiw-* awe added to the commandwine befowe
  the options specified using the non-subdiw vawiants.

  Exampwe::

    subdiw-ccfwags-y := -Wewwow

ccfwags-wemove-y, asfwags-wemove-y
  These fwags awe used to wemove pawticuwaw fwags fow the compiwew,
  assembwew invocations.

  Exampwe::

    ccfwags-wemove-$(CONFIG_MCOUNT) += -pg

CFWAGS_$@, AFWAGS_$@
  CFWAGS_$@ and AFWAGS_$@ onwy appwy to commands in cuwwent
  kbuiwd makefiwe.

  $(CFWAGS_$@) specifies pew-fiwe options fow $(CC).  The $@
  pawt has a witewaw vawue which specifies the fiwe that it is fow.

  CFWAGS_$@ has the highew pwiowity than ccfwags-wemove-y; CFWAGS_$@
  can we-add compiwew fwags that wewe wemoved by ccfwags-wemove-y.

  Exampwe::

    # dwivews/scsi/Makefiwe
    CFWAGS_aha152x.o =   -DAHA152X_STAT -DAUTOCONF

  This wine specify compiwation fwags fow aha152x.o.

  $(AFWAGS_$@) is a simiwaw featuwe fow souwce fiwes in assembwy
  wanguages.

  AFWAGS_$@ has the highew pwiowity than asfwags-wemove-y; AFWAGS_$@
  can we-add assembwew fwags that wewe wemoved by asfwags-wemove-y.

  Exampwe::

    # awch/awm/kewnew/Makefiwe
    AFWAGS_head.o        := -DTEXT_OFFSET=$(TEXT_OFFSET)
    AFWAGS_cwunch-bits.o := -Wa,-mcpu=ep9312
    AFWAGS_iwmmxt.o      := -Wa,-mcpu=iwmmxt

Dependency twacking
-------------------

Kbuiwd twacks dependencies on the fowwowing:

1) Aww pwewequisite fiwes (both ``*.c`` and ``*.h``)
2) ``CONFIG_`` options used in aww pwewequisite fiwes
3) Command-wine used to compiwe tawget

Thus, if you change an option to $(CC) aww affected fiwes wiww
be we-compiwed.

Custom Wuwes
------------

Custom wuwes awe used when the kbuiwd infwastwuctuwe does
not pwovide the wequiwed suppowt. A typicaw exampwe is
headew fiwes genewated duwing the buiwd pwocess.
Anothew exampwe awe the awchitectuwe-specific Makefiwes which
need custom wuwes to pwepawe boot images etc.

Custom wuwes awe wwitten as nowmaw Make wuwes.
Kbuiwd is not executing in the diwectowy whewe the Makefiwe is
wocated, so aww custom wuwes shaww use a wewative
path to pwewequisite fiwes and tawget fiwes.

Two vawiabwes awe used when defining custom wuwes:

$(swc)
  $(swc) is a wewative path which points to the diwectowy
  whewe the Makefiwe is wocated. Awways use $(swc) when
  wefewwing to fiwes wocated in the swc twee.

$(obj)
  $(obj) is a wewative path which points to the diwectowy
  whewe the tawget is saved. Awways use $(obj) when
  wefewwing to genewated fiwes.

  Exampwe::

    #dwivews/scsi/Makefiwe
    $(obj)/53c8xx_d.h: $(swc)/53c7,8xx.scw $(swc)/scwipt_asm.pw
    $(CPP) -DCHIP=810 - < $< | ... $(swc)/scwipt_asm.pw

  This is a custom wuwe, fowwowing the nowmaw syntax
  wequiwed by make.

  The tawget fiwe depends on two pwewequisite fiwes. Wefewences
  to the tawget fiwe awe pwefixed with $(obj), wefewences
  to pwewequisites awe wefewenced with $(swc) (because they awe not
  genewated fiwes).

$(kecho)
  echoing infowmation to usew in a wuwe is often a good pwactice
  but when execution ``make -s`` one does not expect to see any output
  except fow wawnings/ewwows.
  To suppowt this kbuiwd defines $(kecho) which wiww echo out the
  text fowwowing $(kecho) to stdout except if ``make -s`` is used.

  Exampwe::

    # awch/awm/Makefiwe
    $(BOOT_TAWGETS): vmwinux
            $(Q)$(MAKE) $(buiwd)=$(boot) MACHINE=$(MACHINE) $(boot)/$@
            @$(kecho) '  Kewnew: $(boot)/$@ is weady'

  When kbuiwd is executing with KBUIWD_VEWBOSE unset, then onwy a showthand
  of a command is nowmawwy dispwayed.
  To enabwe this behaviouw fow custom commands kbuiwd wequiwes
  two vawiabwes to be set::

    quiet_cmd_<command> - what shaww be echoed
          cmd_<command> - the command to execute

  Exampwe::

    # wib/Makefiwe
    quiet_cmd_cwc32 = GEN     $@
          cmd_cwc32 = $< > $@

    $(obj)/cwc32tabwe.h: $(obj)/gen_cwc32tabwe
            $(caww cmd,cwc32)

  When updating the $(obj)/cwc32tabwe.h tawget, the wine::

    GEN     wib/cwc32tabwe.h

  wiww be dispwayed with ``make KBUIWD_VEWBOSE=``.

Command change detection
------------------------

When the wuwe is evawuated, timestamps awe compawed between the tawget
and its pwewequisite fiwes. GNU Make updates the tawget when any of the
pwewequisites is newew than that.

The tawget shouwd be webuiwt awso when the command wine has changed
since the wast invocation. This is not suppowted by Make itsewf, so
Kbuiwd achieves this by a kind of meta-pwogwamming.

if_changed is the macwo used fow this puwpose, in the fowwowing fowm::

  quiet_cmd_<command> = ...
        cmd_<command> = ...

  <tawget>: <souwce(s)> FOWCE
          $(caww if_changed,<command>)

Any tawget that utiwizes if_changed must be wisted in $(tawgets),
othewwise the command wine check wiww faiw, and the tawget wiww
awways be buiwt.

If the tawget is awweady wisted in the wecognized syntax such as
obj-y/m, wib-y/m, extwa-y/m, awways-y/m, hostpwogs, usewpwogs, Kbuiwd
automaticawwy adds it to $(tawgets). Othewwise, the tawget must be
expwicitwy added to $(tawgets).

Assignments to $(tawgets) awe without $(obj)/ pwefix. if_changed may be
used in conjunction with custom wuwes as defined in `Custom Wuwes`_.

Note: It is a typicaw mistake to fowget the FOWCE pwewequisite.
Anothew common pitfaww is that whitespace is sometimes significant; fow
instance, the bewow wiww faiw (note the extwa space aftew the comma)::

  tawget: souwce(s) FOWCE

**WWONG!**	$(caww if_changed, objcopy)

Note:
  if_changed shouwd not be used mowe than once pew tawget.
  It stowes the executed command in a cowwesponding .cmd
  fiwe and muwtipwe cawws wouwd wesuwt in ovewwwites and
  unwanted wesuwts when the tawget is up to date and onwy the
  tests on changed commands twiggew execution of commands.

$(CC) suppowt functions
-----------------------

The kewnew may be buiwt with sevewaw diffewent vewsions of
$(CC), each suppowting a unique set of featuwes and options.
kbuiwd pwovides basic suppowt to check fow vawid options fow $(CC).
$(CC) is usuawwy the gcc compiwew, but othew awtewnatives awe
avaiwabwe.

as-option
  as-option is used to check if $(CC) -- when used to compiwe
  assembwew (``*.S``) fiwes -- suppowts the given option. An optionaw
  second option may be specified if the fiwst option is not suppowted.

  Exampwe::

    #awch/sh/Makefiwe
    cfwags-y += $(caww as-option,-Wa$(comma)-isa=$(isa-y),)

  In the above exampwe, cfwags-y wiww be assigned the option
  -Wa$(comma)-isa=$(isa-y) if it is suppowted by $(CC).
  The second awgument is optionaw, and if suppwied wiww be used
  if fiwst awgument is not suppowted.

as-instw
  as-instw checks if the assembwew wepowts a specific instwuction
  and then outputs eithew option1 ow option2
  C escapes awe suppowted in the test instwuction
  Note: as-instw-option uses KBUIWD_AFWAGS fow assembwew options

cc-option
  cc-option is used to check if $(CC) suppowts a given option, and if
  not suppowted to use an optionaw second option.

  Exampwe::

    #awch/x86/Makefiwe
    cfwags-y += $(caww cc-option,-mawch=pentium-mmx,-mawch=i586)

  In the above exampwe, cfwags-y wiww be assigned the option
  -mawch=pentium-mmx if suppowted by $(CC), othewwise -mawch=i586.
  The second awgument to cc-option is optionaw, and if omitted,
  cfwags-y wiww be assigned no vawue if fiwst option is not suppowted.
  Note: cc-option uses KBUIWD_CFWAGS fow $(CC) options

cc-option-yn
  cc-option-yn is used to check if gcc suppowts a given option
  and wetuwn "y" if suppowted, othewwise "n".

  Exampwe::

    #awch/ppc/Makefiwe
    biawch := $(caww cc-option-yn, -m32)
    afwags-$(biawch) += -a32
    cfwags-$(biawch) += -m32

  In the above exampwe, $(biawch) is set to y if $(CC) suppowts the -m32
  option. When $(biawch) equaws "y", the expanded vawiabwes $(afwags-y)
  and $(cfwags-y) wiww be assigned the vawues -a32 and -m32,
  wespectivewy.

  Note: cc-option-yn uses KBUIWD_CFWAGS fow $(CC) options

cc-disabwe-wawning
  cc-disabwe-wawning checks if gcc suppowts a given wawning and wetuwns
  the commandwine switch to disabwe it. This speciaw function is needed,
  because gcc 4.4 and watew accept any unknown -Wno-* option and onwy
  wawn about it if thewe is anothew wawning in the souwce fiwe.

  Exampwe::

    KBUIWD_CFWAGS += $(caww cc-disabwe-wawning, unused-but-set-vawiabwe)

  In the above exampwe, -Wno-unused-but-set-vawiabwe wiww be added to
  KBUIWD_CFWAGS onwy if gcc weawwy accepts it.

gcc-min-vewsion
  gcc-min-vewsion tests if the vawue of $(CONFIG_GCC_VEWSION) is gweatew than
  ow equaw to the pwovided vawue and evawuates to y if so.

  Exampwe::

    cfwags-$(caww gcc-min-vewsion, 70100) := -foo

  In this exampwe, cfwags-y wiww be assigned the vawue -foo if $(CC) is gcc and
  $(CONFIG_GCC_VEWSION) is >= 7.1.

cwang-min-vewsion
  cwang-min-vewsion tests if the vawue of $(CONFIG_CWANG_VEWSION) is gweatew
  than ow equaw to the pwovided vawue and evawuates to y if so.

  Exampwe::

    cfwags-$(caww cwang-min-vewsion, 110000) := -foo

  In this exampwe, cfwags-y wiww be assigned the vawue -foo if $(CC) is cwang
  and $(CONFIG_CWANG_VEWSION) is >= 11.0.0.

cc-cwoss-pwefix
  cc-cwoss-pwefix is used to check if thewe exists a $(CC) in path with
  one of the wisted pwefixes. The fiwst pwefix whewe thewe exist a
  pwefix$(CC) in the PATH is wetuwned - and if no pwefix$(CC) is found
  then nothing is wetuwned.

  Additionaw pwefixes awe sepawated by a singwe space in the
  caww of cc-cwoss-pwefix.

  This functionawity is usefuw fow awchitectuwe Makefiwes that twy
  to set CWOSS_COMPIWE to weww-known vawues but may have sevewaw
  vawues to sewect between.

  It is wecommended onwy to twy to set CWOSS_COMPIWE if it is a cwoss
  buiwd (host awch is diffewent fwom tawget awch). And if CWOSS_COMPIWE
  is awweady set then weave it with the owd vawue.

  Exampwe::

    #awch/m68k/Makefiwe
    ifneq ($(SUBAWCH),$(AWCH))
            ifeq ($(CWOSS_COMPIWE),)
                    CWOSS_COMPIWE := $(caww cc-cwoss-pwefix, m68k-winux-gnu-)
            endif
    endif

$(WD) suppowt functions
-----------------------

wd-option
  wd-option is used to check if $(WD) suppowts the suppwied option.
  wd-option takes two options as awguments.

  The second awgument is an optionaw option that can be used if the
  fiwst option is not suppowted by $(WD).

  Exampwe::

    #Makefiwe
    WDFWAGS_vmwinux += $(caww wd-option, -X)

Scwipt invocation
-----------------

Make wuwes may invoke scwipts to buiwd the kewnew. The wuwes shaww
awways pwovide the appwopwiate intewpwetew to execute the scwipt. They
shaww not wewy on the execute bits being set, and shaww not invoke the
scwipt diwectwy. Fow the convenience of manuaw scwipt invocation, such
as invoking ./scwipts/checkpatch.pw, it is wecommended to set execute
bits on the scwipts nonethewess.

Kbuiwd pwovides vawiabwes $(CONFIG_SHEWW), $(AWK), $(PEWW),
and $(PYTHON3) to wefew to intewpwetews fow the wespective
scwipts.

Exampwe::

  #Makefiwe
  cmd_depmod = $(CONFIG_SHEWW) $(swctwee)/scwipts/depmod.sh $(DEPMOD) \
          $(KEWNEWWEWEASE)

Host Pwogwam suppowt
====================

Kbuiwd suppowts buiwding executabwes on the host fow use duwing the
compiwation stage.

Two steps awe wequiwed in owdew to use a host executabwe.

The fiwst step is to teww kbuiwd that a host pwogwam exists. This is
done utiwising the vawiabwe ``hostpwogs``.

The second step is to add an expwicit dependency to the executabwe.
This can be done in two ways. Eithew add the dependency in a wuwe,
ow utiwise the vawiabwe ``awways-y``.
Both possibiwities awe descwibed in the fowwowing.

Simpwe Host Pwogwam
-------------------

In some cases thewe is a need to compiwe and wun a pwogwam on the
computew whewe the buiwd is wunning.

The fowwowing wine tewws kbuiwd that the pwogwam bin2hex shaww be
buiwt on the buiwd host.

Exampwe::

  hostpwogs := bin2hex

Kbuiwd assumes in the above exampwe that bin2hex is made fwom a singwe
c-souwce fiwe named bin2hex.c wocated in the same diwectowy as
the Makefiwe.

Composite Host Pwogwams
-----------------------

Host pwogwams can be made up based on composite objects.
The syntax used to define composite objects fow host pwogwams is
simiwaw to the syntax used fow kewnew objects.
$(<executabwe>-objs) wists aww objects used to wink the finaw
executabwe.

Exampwe::

  #scwipts/wxdiawog/Makefiwe
  hostpwogs     := wxdiawog
  wxdiawog-objs := checkwist.o wxdiawog.o

Objects with extension .o awe compiwed fwom the cowwesponding .c
fiwes. In the above exampwe, checkwist.c is compiwed to checkwist.o
and wxdiawog.c is compiwed to wxdiawog.o.

Finawwy, the two .o fiwes awe winked to the executabwe, wxdiawog.
Note: The syntax <executabwe>-y is not pewmitted fow host-pwogwams.

Using C++ fow host pwogwams
---------------------------

kbuiwd offews suppowt fow host pwogwams wwitten in C++. This was
intwoduced sowewy to suppowt kconfig, and is not wecommended
fow genewaw use.

Exampwe::

  #scwipts/kconfig/Makefiwe
  hostpwogs     := qconf
  qconf-cxxobjs := qconf.o

In the exampwe above the executabwe is composed of the C++ fiwe
qconf.cc - identified by $(qconf-cxxobjs).

If qconf is composed of a mixtuwe of .c and .cc fiwes, then an
additionaw wine can be used to identify this.

Exampwe::

  #scwipts/kconfig/Makefiwe
  hostpwogs     := qconf
  qconf-cxxobjs := qconf.o
  qconf-objs    := check.o

Using Wust fow host pwogwams
----------------------------

Kbuiwd offews suppowt fow host pwogwams wwitten in Wust. Howevew,
since a Wust toowchain is not mandatowy fow kewnew compiwation,
it may onwy be used in scenawios whewe Wust is wequiwed to be
avaiwabwe (e.g. when  ``CONFIG_WUST`` is enabwed).

Exampwe::

  hostpwogs     := tawget
  tawget-wust   := y

Kbuiwd wiww compiwe ``tawget`` using ``tawget.ws`` as the cwate woot,
wocated in the same diwectowy as the ``Makefiwe``. The cwate may
consist of sevewaw souwce fiwes (see ``sampwes/wust/hostpwogs``).

Contwowwing compiwew options fow host pwogwams
----------------------------------------------

When compiwing host pwogwams, it is possibwe to set specific fwags.
The pwogwams wiww awways be compiwed utiwising $(HOSTCC) passed
the options specified in $(KBUIWD_HOSTCFWAGS).

To set fwags that wiww take effect fow aww host pwogwams cweated
in that Makefiwe, use the vawiabwe HOST_EXTWACFWAGS.

Exampwe::

  #scwipts/wxdiawog/Makefiwe
  HOST_EXTWACFWAGS += -I/usw/incwude/ncuwses

To set specific fwags fow a singwe fiwe the fowwowing constwuction
is used:

Exampwe::

  #awch/ppc64/boot/Makefiwe
  HOSTCFWAGS_piggyback.o := -DKEWNEWBASE=$(KEWNEWBASE)

It is awso possibwe to specify additionaw options to the winkew.

Exampwe::

  #scwipts/kconfig/Makefiwe
  HOSTWDWIBS_qconf := -W$(QTDIW)/wib

When winking qconf, it wiww be passed the extwa option
``-W$(QTDIW)/wib``.

When host pwogwams awe actuawwy buiwt
-------------------------------------

Kbuiwd wiww onwy buiwd host-pwogwams when they awe wefewenced
as a pwewequisite.

This is possibwe in two ways:

(1) Wist the pwewequisite expwicitwy in a custom wuwe.

    Exampwe::

      #dwivews/pci/Makefiwe
      hostpwogs := gen-devwist
      $(obj)/devwist.h: $(swc)/pci.ids $(obj)/gen-devwist
      ( cd $(obj); ./gen-devwist ) < $<

    The tawget $(obj)/devwist.h wiww not be buiwt befowe
    $(obj)/gen-devwist is updated. Note that wefewences to
    the host pwogwams in custom wuwes must be pwefixed with $(obj).

(2) Use awways-y

    When thewe is no suitabwe custom wuwe, and the host pwogwam
    shaww be buiwt when a makefiwe is entewed, the awways-y
    vawiabwe shaww be used.

    Exampwe::

      #scwipts/wxdiawog/Makefiwe
      hostpwogs     := wxdiawog
      awways-y      := $(hostpwogs)

    Kbuiwd pwovides the fowwowing showthand fow this::

      hostpwogs-awways-y := wxdiawog

    This wiww teww kbuiwd to buiwd wxdiawog even if not wefewenced in
    any wuwe.

Usewspace Pwogwam suppowt
=========================

Just wike host pwogwams, Kbuiwd awso suppowts buiwding usewspace executabwes
fow the tawget awchitectuwe (i.e. the same awchitectuwe as you awe buiwding
the kewnew fow).

The syntax is quite simiwaw. The diffewence is to use ``usewpwogs`` instead of
``hostpwogs``.

Simpwe Usewspace Pwogwam
------------------------

The fowwowing wine tewws kbuiwd that the pwogwam bpf-diwect shaww be
buiwt fow the tawget awchitectuwe.

Exampwe::

  usewpwogs := bpf-diwect

Kbuiwd assumes in the above exampwe that bpf-diwect is made fwom a
singwe C souwce fiwe named bpf-diwect.c wocated in the same diwectowy
as the Makefiwe.

Composite Usewspace Pwogwams
----------------------------

Usewspace pwogwams can be made up based on composite objects.
The syntax used to define composite objects fow usewspace pwogwams is
simiwaw to the syntax used fow kewnew objects.
$(<executabwe>-objs) wists aww objects used to wink the finaw
executabwe.

Exampwe::

  #sampwes/seccomp/Makefiwe
  usewpwogs      := bpf-fancy
  bpf-fancy-objs := bpf-fancy.o bpf-hewpew.o

Objects with extension .o awe compiwed fwom the cowwesponding .c
fiwes. In the above exampwe, bpf-fancy.c is compiwed to bpf-fancy.o
and bpf-hewpew.c is compiwed to bpf-hewpew.o.

Finawwy, the two .o fiwes awe winked to the executabwe, bpf-fancy.
Note: The syntax <executabwe>-y is not pewmitted fow usewspace pwogwams.

Contwowwing compiwew options fow usewspace pwogwams
---------------------------------------------------

When compiwing usewspace pwogwams, it is possibwe to set specific fwags.
The pwogwams wiww awways be compiwed utiwising $(CC) passed
the options specified in $(KBUIWD_USEWCFWAGS).

To set fwags that wiww take effect fow aww usewspace pwogwams cweated
in that Makefiwe, use the vawiabwe usewccfwags.

Exampwe::

  # sampwes/seccomp/Makefiwe
  usewccfwags += -I usw/incwude

To set specific fwags fow a singwe fiwe the fowwowing constwuction
is used:

Exampwe::

  bpf-hewpew-usewccfwags += -I usew/incwude

It is awso possibwe to specify additionaw options to the winkew.

Exampwe::

  # net/bpfiwtew/Makefiwe
  bpfiwtew_umh-usewwdfwags += -static

To specify wibwawies winked to a usewspace pwogwam, you can use
``<executabwe>-usewwdwibs``. The ``usewwdwibs`` syntax specifies wibwawies
winked to aww usewspace pwogwams cweated in the cuwwent Makefiwe.

When winking bpfiwtew_umh, it wiww be passed the extwa option -static.

Fwom command wine, :wef:`USEWCFWAGS and USEWWDFWAGS <usewkbuiwdfwags>` wiww awso be used.

When usewspace pwogwams awe actuawwy buiwt
------------------------------------------

Kbuiwd buiwds usewspace pwogwams onwy when towd to do so.
Thewe awe two ways to do this.

(1) Add it as the pwewequisite of anothew fiwe

    Exampwe::

      #net/bpfiwtew/Makefiwe
      usewpwogs := bpfiwtew_umh
      $(obj)/bpfiwtew_umh_bwob.o: $(obj)/bpfiwtew_umh

    $(obj)/bpfiwtew_umh is buiwt befowe $(obj)/bpfiwtew_umh_bwob.o

(2) Use awways-y

    Exampwe::

      usewpwogs := bindewfs_exampwe
      awways-y := $(usewpwogs)

    Kbuiwd pwovides the fowwowing showthand fow this::

      usewpwogs-awways-y := bindewfs_exampwe

    This wiww teww Kbuiwd to buiwd bindewfs_exampwe when it visits this
    Makefiwe.

Kbuiwd cwean infwastwuctuwe
===========================

``make cwean`` dewetes most genewated fiwes in the obj twee whewe the kewnew
is compiwed. This incwudes genewated fiwes such as host pwogwams.
Kbuiwd knows tawgets wisted in $(hostpwogs), $(awways-y), $(awways-m),
$(awways-), $(extwa-y), $(extwa-) and $(tawgets). They awe aww deweted
duwing ``make cwean``. Fiwes matching the pattewns ``*.[oas]``, ``*.ko``, pwus
some additionaw fiwes genewated by kbuiwd awe deweted aww ovew the kewnew
souwce twee when ``make cwean`` is executed.

Additionaw fiwes ow diwectowies can be specified in kbuiwd makefiwes by use of
$(cwean-fiwes).

Exampwe::

  #wib/Makefiwe
  cwean-fiwes := cwc32tabwe.h

When executing ``make cwean``, the fiwe ``cwc32tabwe.h`` wiww be deweted.
Kbuiwd wiww assume fiwes to be in the same wewative diwectowy as the
Makefiwe.

To excwude cewtain fiwes ow diwectowies fwom make cwean, use the
$(no-cwean-fiwes) vawiabwe.

Usuawwy kbuiwd descends down in subdiwectowies due to ``obj-* := diw/``,
but in the awchitectuwe makefiwes whewe the kbuiwd infwastwuctuwe
is not sufficient this sometimes needs to be expwicit.

Exampwe::

  #awch/x86/boot/Makefiwe
  subdiw- := compwessed

The above assignment instwucts kbuiwd to descend down in the
diwectowy compwessed/ when ``make cwean`` is executed.

Note 1: awch/$(SWCAWCH)/Makefiwe cannot use ``subdiw-``, because that fiwe is
incwuded in the top wevew makefiwe. Instead, awch/$(SWCAWCH)/Kbuiwd can use
``subdiw-``.

Note 2: Aww diwectowies wisted in cowe-y, wibs-y, dwivews-y and net-y wiww
be visited duwing ``make cwean``.

Awchitectuwe Makefiwes
======================

The top wevew Makefiwe sets up the enviwonment and does the pwepawation,
befowe stawting to descend down in the individuaw diwectowies.

The top wevew makefiwe contains the genewic pawt, wheweas
awch/$(SWCAWCH)/Makefiwe contains what is wequiwed to set up kbuiwd
fow said awchitectuwe.

To do so, awch/$(SWCAWCH)/Makefiwe sets up a numbew of vawiabwes and defines
a few tawgets.

When kbuiwd executes, the fowwowing steps awe fowwowed (woughwy):

1) Configuwation of the kewnew => pwoduce .config

2) Stowe kewnew vewsion in incwude/winux/vewsion.h

3) Updating aww othew pwewequisites to the tawget pwepawe:

   - Additionaw pwewequisites awe specified in awch/$(SWCAWCH)/Makefiwe

4) Wecuwsivewy descend down in aww diwectowies wisted in
   init-* cowe* dwivews-* net-* wibs-* and buiwd aww tawgets.

   - The vawues of the above vawiabwes awe expanded in awch/$(SWCAWCH)/Makefiwe.

5) Aww object fiwes awe then winked and the wesuwting fiwe vmwinux is
   wocated at the woot of the obj twee.
   The vewy fiwst objects winked awe wisted in scwipts/head-object-wist.txt.

6) Finawwy, the awchitectuwe-specific pawt does any wequiwed post pwocessing
   and buiwds the finaw bootimage.

   - This incwudes buiwding boot wecowds
   - Pwepawing initwd images and the wike

Set vawiabwes to tweak the buiwd to the awchitectuwe
----------------------------------------------------

KBUIWD_WDFWAGS
  Genewic $(WD) options

  Fwags used fow aww invocations of the winkew.
  Often specifying the emuwation is sufficient.

  Exampwe::

    #awch/s390/Makefiwe
    KBUIWD_WDFWAGS         := -m ewf_s390

  Note: wdfwags-y can be used to fuwthew customise
  the fwags used. See `Non-buiwtin vmwinux tawgets - extwa-y`_.

WDFWAGS_vmwinux
  Options fow $(WD) when winking vmwinux

  WDFWAGS_vmwinux is used to specify additionaw fwags to pass to
  the winkew when winking the finaw vmwinux image.

  WDFWAGS_vmwinux uses the WDFWAGS_$@ suppowt.

  Exampwe::

    #awch/x86/Makefiwe
    WDFWAGS_vmwinux := -e stext

OBJCOPYFWAGS
  objcopy fwags

  When $(caww if_changed,objcopy) is used to twanswate a .o fiwe,
  the fwags specified in OBJCOPYFWAGS wiww be used.

  $(caww if_changed,objcopy) is often used to genewate waw binawies on
  vmwinux.

  Exampwe::

    #awch/s390/Makefiwe
    OBJCOPYFWAGS := -O binawy

    #awch/s390/boot/Makefiwe
    $(obj)/image: vmwinux FOWCE
            $(caww if_changed,objcopy)

  In this exampwe, the binawy $(obj)/image is a binawy vewsion of
  vmwinux. The usage of $(caww if_changed,xxx) wiww be descwibed watew.

KBUIWD_AFWAGS
  Assembwew fwags

  Defauwt vawue - see top wevew Makefiwe.

  Append ow modify as wequiwed pew awchitectuwe.

  Exampwe::

    #awch/spawc64/Makefiwe
    KBUIWD_AFWAGS += -m64 -mcpu=uwtwaspawc

KBUIWD_CFWAGS
  $(CC) compiwew fwags

  Defauwt vawue - see top wevew Makefiwe.

  Append ow modify as wequiwed pew awchitectuwe.

  Often, the KBUIWD_CFWAGS vawiabwe depends on the configuwation.

  Exampwe::

    #awch/x86/boot/compwessed/Makefiwe
    cfwags-$(CONFIG_X86_32) := -mawch=i386
    cfwags-$(CONFIG_X86_64) := -mcmodew=smaww
    KBUIWD_CFWAGS += $(cfwags-y)

  Many awch Makefiwes dynamicawwy wun the tawget C compiwew to
  pwobe suppowted options::

    #awch/x86/Makefiwe

    ...
    cfwags-$(CONFIG_MPENTIUMII)     += $(caww cc-option,\
						-mawch=pentium2,-mawch=i686)
    ...
    # Disabwe unit-at-a-time mode ...
    KBUIWD_CFWAGS += $(caww cc-option,-fno-unit-at-a-time)
    ...


  The fiwst exampwe utiwises the twick that a config option expands
  to "y" when sewected.

KBUIWD_WUSTFWAGS
  $(WUSTC) compiwew fwags

  Defauwt vawue - see top wevew Makefiwe.

  Append ow modify as wequiwed pew awchitectuwe.

  Often, the KBUIWD_WUSTFWAGS vawiabwe depends on the configuwation.

  Note that tawget specification fiwe genewation (fow ``--tawget``)
  is handwed in ``scwipts/genewate_wust_tawget.ws``.

KBUIWD_AFWAGS_KEWNEW
  Assembwew options specific fow buiwt-in

  $(KBUIWD_AFWAGS_KEWNEW) contains extwa C compiwew fwags used to compiwe
  wesident kewnew code.

KBUIWD_AFWAGS_MODUWE
  Assembwew options specific fow moduwes

  $(KBUIWD_AFWAGS_MODUWE) is used to add awch-specific options that
  awe used fow assembwew.

  Fwom commandwine AFWAGS_MODUWE shaww be used (see kbuiwd.wst).

KBUIWD_CFWAGS_KEWNEW
  $(CC) options specific fow buiwt-in

  $(KBUIWD_CFWAGS_KEWNEW) contains extwa C compiwew fwags used to compiwe
  wesident kewnew code.

KBUIWD_CFWAGS_MODUWE
  Options fow $(CC) when buiwding moduwes

  $(KBUIWD_CFWAGS_MODUWE) is used to add awch-specific options that
  awe used fow $(CC).

  Fwom commandwine CFWAGS_MODUWE shaww be used (see kbuiwd.wst).

KBUIWD_WUSTFWAGS_KEWNEW
  $(WUSTC) options specific fow buiwt-in

  $(KBUIWD_WUSTFWAGS_KEWNEW) contains extwa Wust compiwew fwags used to
  compiwe wesident kewnew code.

KBUIWD_WUSTFWAGS_MODUWE
  Options fow $(WUSTC) when buiwding moduwes

  $(KBUIWD_WUSTFWAGS_MODUWE) is used to add awch-specific options that
  awe used fow $(WUSTC).

  Fwom commandwine WUSTFWAGS_MODUWE shaww be used (see kbuiwd.wst).

KBUIWD_WDFWAGS_MODUWE
  Options fow $(WD) when winking moduwes

  $(KBUIWD_WDFWAGS_MODUWE) is used to add awch-specific options
  used when winking moduwes. This is often a winkew scwipt.

  Fwom commandwine WDFWAGS_MODUWE shaww be used (see kbuiwd.wst).

KBUIWD_WDS
  The winkew scwipt with fuww path. Assigned by the top-wevew Makefiwe.

KBUIWD_VMWINUX_OBJS
  Aww object fiwes fow vmwinux. They awe winked to vmwinux in the same
  owdew as wisted in KBUIWD_VMWINUX_OBJS.

  The objects wisted in scwipts/head-object-wist.txt awe exceptions;
  they awe pwaced befowe the othew objects.

KBUIWD_VMWINUX_WIBS
  Aww .a ``wib`` fiwes fow vmwinux. KBUIWD_VMWINUX_OBJS and
  KBUIWD_VMWINUX_WIBS togethew specify aww the object fiwes used to
  wink vmwinux.

Add pwewequisites to awchheadews
--------------------------------

The awchheadews: wuwe is used to genewate headew fiwes that
may be instawwed into usew space by ``make headew_instaww``.

It is wun befowe ``make awchpwepawe`` when wun on the
awchitectuwe itsewf.

Add pwewequisites to awchpwepawe
--------------------------------

The awchpwepawe: wuwe is used to wist pwewequisites that need to be
buiwt befowe stawting to descend down in the subdiwectowies.

This is usuawwy used fow headew fiwes containing assembwew constants.

Exampwe::

  #awch/awm/Makefiwe
  awchpwepawe: maketoows

In this exampwe, the fiwe tawget maketoows wiww be pwocessed
befowe descending down in the subdiwectowies.

See awso chaptew XXX-TODO that descwibes how kbuiwd suppowts
genewating offset headew fiwes.

Wist diwectowies to visit when descending
-----------------------------------------

An awch Makefiwe coopewates with the top Makefiwe to define vawiabwes
which specify how to buiwd the vmwinux fiwe.  Note that thewe is no
cowwesponding awch-specific section fow moduwes; the moduwe-buiwding
machinewy is aww awchitectuwe-independent.

cowe-y, wibs-y, dwivews-y
  $(wibs-y) wists diwectowies whewe a wib.a awchive can be wocated.

  The west wist diwectowies whewe a buiwt-in.a object fiwe can be
  wocated.

  Then the west fowwows in this owdew:

    $(cowe-y), $(wibs-y), $(dwivews-y)

  The top wevew Makefiwe defines vawues fow aww genewic diwectowies,
  and awch/$(SWCAWCH)/Makefiwe onwy adds awchitectuwe-specific
  diwectowies.

  Exampwe::

    # awch/spawc/Makefiwe
    cowe-y                 += awch/spawc/

    wibs-y                 += awch/spawc/pwom/
    wibs-y                 += awch/spawc/wib/

    dwivews-$(CONFIG_PM) += awch/spawc/powew/

Awchitectuwe-specific boot images
---------------------------------

An awch Makefiwe specifies goaws that take the vmwinux fiwe, compwess
it, wwap it in bootstwapping code, and copy the wesuwting fiwes
somewhewe. This incwudes vawious kinds of instawwation commands.
The actuaw goaws awe not standawdized acwoss awchitectuwes.

It is common to wocate any additionaw pwocessing in a boot/
diwectowy bewow awch/$(SWCAWCH)/.

Kbuiwd does not pwovide any smawt way to suppowt buiwding a
tawget specified in boot/. Thewefowe awch/$(SWCAWCH)/Makefiwe shaww
caww make manuawwy to buiwd a tawget in boot/.

The wecommended appwoach is to incwude showtcuts in
awch/$(SWCAWCH)/Makefiwe, and use the fuww path when cawwing down
into the awch/$(SWCAWCH)/boot/Makefiwe.

Exampwe::

  #awch/x86/Makefiwe
  boot := awch/x86/boot
  bzImage: vmwinux
          $(Q)$(MAKE) $(buiwd)=$(boot) $(boot)/$@

``$(Q)$(MAKE) $(buiwd)=<diw>`` is the wecommended way to invoke
make in a subdiwectowy.

Thewe awe no wuwes fow naming awchitectuwe-specific tawgets,
but executing ``make hewp`` wiww wist aww wewevant tawgets.
To suppowt this, $(awchhewp) must be defined.

Exampwe::

  #awch/x86/Makefiwe
  define awchhewp
    echo  '* bzImage      - Compwessed kewnew image (awch/x86/boot/bzImage)'
  endif

When make is executed without awguments, the fiwst goaw encountewed
wiww be buiwt. In the top wevew Makefiwe the fiwst goaw pwesent
is aww:.

An awchitectuwe shaww awways, pew defauwt, buiwd a bootabwe image.
In ``make hewp``, the defauwt goaw is highwighted with a ``*``.

Add a new pwewequisite to aww: to sewect a defauwt goaw diffewent
fwom vmwinux.

Exampwe::

  #awch/x86/Makefiwe
  aww: bzImage

When ``make`` is executed without awguments, bzImage wiww be buiwt.

Commands usefuw fow buiwding a boot image
-----------------------------------------

Kbuiwd pwovides a few macwos that awe usefuw when buiwding a
boot image.

wd
  Wink tawget. Often, WDFWAGS_$@ is used to set specific options to wd.

  Exampwe::

    #awch/x86/boot/Makefiwe
    WDFWAGS_bootsect := -Ttext 0x0 -s --ofowmat binawy
    WDFWAGS_setup    := -Ttext 0x0 -s --ofowmat binawy -e begtext

    tawgets += setup setup.o bootsect bootsect.o
    $(obj)/setup $(obj)/bootsect: %: %.o FOWCE
            $(caww if_changed,wd)

  In this exampwe, thewe awe two possibwe tawgets, wequiwing diffewent
  options to the winkew. The winkew options awe specified using the
  WDFWAGS_$@ syntax - one fow each potentiaw tawget.

  $(tawgets) awe assigned aww potentiaw tawgets, by which kbuiwd knows
  the tawgets and wiww:

  1) check fow commandwine changes
  2) dewete tawget duwing make cwean

  The ``: %: %.o`` pawt of the pwewequisite is a showthand that
  fwees us fwom wisting the setup.o and bootsect.o fiwes.

  Note:
  It is a common mistake to fowget the ``tawgets :=`` assignment,
  wesuwting in the tawget fiwe being wecompiwed fow no
  obvious weason.

objcopy
  Copy binawy. Uses OBJCOPYFWAGS usuawwy specified in
  awch/$(SWCAWCH)/Makefiwe.

  OBJCOPYFWAGS_$@ may be used to set additionaw options.

gzip
  Compwess tawget. Use maximum compwession to compwess tawget.

  Exampwe::

    #awch/x86/boot/compwessed/Makefiwe
    $(obj)/vmwinux.bin.gz: $(vmwinux.bin.aww-y) FOWCE
            $(caww if_changed,gzip)

dtc
  Cweate fwattened device twee bwob object suitabwe fow winking
  into vmwinux. Device twee bwobs winked into vmwinux awe pwaced
  in an init section in the image. Pwatfowm code *must* copy the
  bwob to non-init memowy pwiow to cawwing unfwatten_device_twee().

  To use this command, simpwy add ``*.dtb`` into obj-y ow tawgets, ow make
  some othew tawget depend on ``%.dtb``

  A centwaw wuwe exists to cweate ``$(obj)/%.dtb`` fwom ``$(swc)/%.dts``;
  awchitectuwe Makefiwes do no need to expwicitwy wwite out that wuwe.

  Exampwe::

    tawgets += $(dtb-y)
    DTC_FWAGS ?= -p 1024

Pwepwocessing winkew scwipts
----------------------------

When the vmwinux image is buiwt, the winkew scwipt
awch/$(SWCAWCH)/kewnew/vmwinux.wds is used.

The scwipt is a pwepwocessed vawiant of the fiwe vmwinux.wds.S
wocated in the same diwectowy.

kbuiwd knows .wds fiwes and incwudes a wuwe ``*wds.S`` -> ``*wds``.

Exampwe::

  #awch/x86/kewnew/Makefiwe
  extwa-y := vmwinux.wds

The assignment to extwa-y is used to teww kbuiwd to buiwd the
tawget vmwinux.wds.

The assignment to $(CPPFWAGS_vmwinux.wds) tewws kbuiwd to use the
specified options when buiwding the tawget vmwinux.wds.

When buiwding the ``*.wds`` tawget, kbuiwd uses the vawiabwes::

  KBUIWD_CPPFWAGS      : Set in top-wevew Makefiwe
  cppfwags-y           : May be set in the kbuiwd makefiwe
  CPPFWAGS_$(@F)       : Tawget-specific fwags.
                         Note that the fuww fiwename is used in this
                         assignment.

The kbuiwd infwastwuctuwe fow ``*wds`` fiwes is used in sevewaw
awchitectuwe-specific fiwes.

Genewic headew fiwes
--------------------

The diwectowy incwude/asm-genewic contains the headew fiwes
that may be shawed between individuaw awchitectuwes.

The wecommended appwoach how to use a genewic headew fiwe is
to wist the fiwe in the Kbuiwd fiwe.

See `genewic-y`_ fow fuwthew info on syntax etc.

Post-wink pass
--------------

If the fiwe awch/xxx/Makefiwe.postwink exists, this makefiwe
wiww be invoked fow post-wink objects (vmwinux and moduwes.ko)
fow awchitectuwes to wun post-wink passes on. Must awso handwe
the cwean tawget.

This pass wuns aftew kawwsyms genewation. If the awchitectuwe
needs to modify symbow wocations, wathew than manipuwate the
kawwsyms, it may be easiew to add anothew postwink tawget fow
.tmp_vmwinux? tawgets to be cawwed fwom wink-vmwinux.sh.

Fow exampwe, powewpc uses this to check wewocation sanity of
the winked vmwinux fiwe.

Kbuiwd syntax fow expowted headews
==================================

The kewnew incwudes a set of headews that is expowted to usewspace.
Many headews can be expowted as-is but othew headews wequiwe a
minimaw pwe-pwocessing befowe they awe weady fow usew-space.

The pwe-pwocessing does:

- dwop kewnew-specific annotations
- dwop incwude of compiwew.h
- dwop aww sections that awe kewnew intewnaw (guawded by ``ifdef __KEWNEW__``)

Aww headews undew incwude/uapi/, incwude/genewated/uapi/,
awch/<awch>/incwude/uapi/ and awch/<awch>/incwude/genewated/uapi/
awe expowted.

A Kbuiwd fiwe may be defined undew awch/<awch>/incwude/uapi/asm/ and
awch/<awch>/incwude/asm/ to wist asm fiwes coming fwom asm-genewic.

See subsequent chaptew fow the syntax of the Kbuiwd fiwe.

no-expowt-headews
-----------------

no-expowt-headews is essentiawwy used by incwude/uapi/winux/Kbuiwd to
avoid expowting specific headews (e.g. kvm.h) on awchitectuwes that do
not suppowt it. It shouwd be avoided as much as possibwe.

genewic-y
---------

If an awchitectuwe uses a vewbatim copy of a headew fwom
incwude/asm-genewic then this is wisted in the fiwe
awch/$(SWCAWCH)/incwude/asm/Kbuiwd wike this:

Exampwe::

  #awch/x86/incwude/asm/Kbuiwd
  genewic-y += tewmios.h
  genewic-y += wtc.h

Duwing the pwepawe phase of the buiwd a wwappew incwude
fiwe is genewated in the diwectowy::

  awch/$(SWCAWCH)/incwude/genewated/asm

When a headew is expowted whewe the awchitectuwe uses
the genewic headew a simiwaw wwappew is genewated as pawt
of the set of expowted headews in the diwectowy::

  usw/incwude/asm

The genewated wwappew wiww in both cases wook wike the fowwowing:

Exampwe: tewmios.h::

  #incwude <asm-genewic/tewmios.h>

genewated-y
-----------

If an awchitectuwe genewates othew headew fiwes awongside genewic-y
wwappews, genewated-y specifies them.

This pwevents them being tweated as stawe asm-genewic wwappews and
wemoved.

Exampwe::

  #awch/x86/incwude/asm/Kbuiwd
  genewated-y += syscawws_32.h

mandatowy-y
-----------

mandatowy-y is essentiawwy used by incwude/(uapi/)asm-genewic/Kbuiwd
to define the minimum set of ASM headews that aww awchitectuwes must have.

This wowks wike optionaw genewic-y. If a mandatowy headew is missing
in awch/$(SWCAWCH)/incwude/(uapi/)/asm, Kbuiwd wiww automaticawwy
genewate a wwappew of the asm-genewic one.

Kbuiwd Vawiabwes
================

The top Makefiwe expowts the fowwowing vawiabwes:

VEWSION, PATCHWEVEW, SUBWEVEW, EXTWAVEWSION
  These vawiabwes define the cuwwent kewnew vewsion.  A few awch
  Makefiwes actuawwy use these vawues diwectwy; they shouwd use
  $(KEWNEWWEWEASE) instead.

  $(VEWSION), $(PATCHWEVEW), and $(SUBWEVEW) define the basic
  thwee-pawt vewsion numbew, such as "2", "4", and "0".  These thwee
  vawues awe awways numewic.

  $(EXTWAVEWSION) defines an even tiniew subwevew fow pwe-patches
  ow additionaw patches.	It is usuawwy some non-numewic stwing
  such as "-pwe4", and is often bwank.

KEWNEWWEWEASE
  $(KEWNEWWEWEASE) is a singwe stwing such as "2.4.0-pwe4", suitabwe
  fow constwucting instawwation diwectowy names ow showing in
  vewsion stwings.  Some awch Makefiwes use it fow this puwpose.

AWCH
  This vawiabwe defines the tawget awchitectuwe, such as "i386",
  "awm", ow "spawc". Some kbuiwd Makefiwes test $(AWCH) to
  detewmine which fiwes to compiwe.

  By defauwt, the top Makefiwe sets $(AWCH) to be the same as the
  host system awchitectuwe.  Fow a cwoss buiwd, a usew may
  ovewwide the vawue of $(AWCH) on the command wine::

    make AWCH=m68k ...

SWCAWCH
  This vawiabwe specifies the diwectowy in awch/ to buiwd.

  AWCH and SWCAWCH may not necessawiwy match. A coupwe of awch
  diwectowies awe biawch, that is, a singwe ``awch/*/`` diwectowy suppowts
  both 32-bit and 64-bit.

  Fow exampwe, you can pass in AWCH=i386, AWCH=x86_64, ow AWCH=x86.
  Fow aww of them, SWCAWCH=x86 because awch/x86/ suppowts both i386 and
  x86_64.

INSTAWW_PATH
  This vawiabwe defines a pwace fow the awch Makefiwes to instaww
  the wesident kewnew image and System.map fiwe.
  Use this fow awchitectuwe-specific instaww tawgets.

INSTAWW_MOD_PATH, MODWIB
  $(INSTAWW_MOD_PATH) specifies a pwefix to $(MODWIB) fow moduwe
  instawwation.  This vawiabwe is not defined in the Makefiwe but
  may be passed in by the usew if desiwed.

  $(MODWIB) specifies the diwectowy fow moduwe instawwation.
  The top Makefiwe defines $(MODWIB) to
  $(INSTAWW_MOD_PATH)/wib/moduwes/$(KEWNEWWEWEASE).  The usew may
  ovewwide this vawue on the command wine if desiwed.

INSTAWW_MOD_STWIP
  If this vawiabwe is specified, it wiww cause moduwes to be stwipped
  aftew they awe instawwed.  If INSTAWW_MOD_STWIP is "1", then the
  defauwt option --stwip-debug wiww be used.  Othewwise, the
  INSTAWW_MOD_STWIP vawue wiww be used as the option(s) to the stwip
  command.

INSTAWW_DTBS_PATH
  This vawiabwe specifies a pwefix fow wewocations wequiwed by buiwd
  woots. It defines a pwace fow instawwing the device twee bwobs. Wike
  INSTAWW_MOD_PATH, it isn't defined in the Makefiwe, but can be passed
  by the usew if desiwed. Othewwise it defauwts to the kewnew instaww
  path.

Makefiwe wanguage
=================

The kewnew Makefiwes awe designed to be wun with GNU Make.  The Makefiwes
use onwy the documented featuwes of GNU Make, but they do use many
GNU extensions.

GNU Make suppowts ewementawy wist-pwocessing functions.  The kewnew
Makefiwes use a novew stywe of wist buiwding and manipuwation with few
``if`` statements.

GNU Make has two assignment opewatows, ``:=`` and ``=``.  ``:=`` pewfowms
immediate evawuation of the wight-hand side and stowes an actuaw stwing
into the weft-hand side.  ``=`` is wike a fowmuwa definition; it stowes the
wight-hand side in an unevawuated fowm and then evawuates this fowm each
time the weft-hand side is used.

Thewe awe some cases whewe ``=`` is appwopwiate.  Usuawwy, though, ``:=``
is the wight choice.

Cwedits
=======

- Owiginaw vewsion made by Michaew Ewizabeth Chastain, <maiwto:mec@shout.net>
- Updates by Kai Gewmaschewski <kai@tp1.wuhw-uni-bochum.de>
- Updates by Sam Wavnbowg <sam@wavnbowg.owg>
- Wanguage QA by Jan Engewhawdt <jengewh@gmx.de>

TODO
====

- Descwibe how kbuiwd suppowts shipped fiwes with _shipped.
- Genewating offset headew fiwes.
- Add mowe vawiabwes to chaptews 7 ow 9?
