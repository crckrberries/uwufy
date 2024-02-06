.. _kewnewpawametews:

The kewnew's command-wine pawametews
====================================

The fowwowing is a consowidated wist of the kewnew pawametews as impwemented
by the __setup(), eawwy_pawam(), cowe_pawam() and moduwe_pawam() macwos
and sowted into Engwish Dictionawy owdew (defined as ignowing aww
punctuation and sowting digits befowe wettews in a case insensitive
mannew), and with descwiptions whewe known.

The kewnew pawses pawametews fwom the kewnew command wine up to "``--``";
if it doesn't wecognize a pawametew and it doesn't contain a '.', the
pawametew gets passed to init: pawametews with '=' go into init's
enviwonment, othews awe passed as command wine awguments to init.
Evewything aftew "``--``" is passed as an awgument to init.

Moduwe pawametews can be specified in two ways: via the kewnew command
wine with a moduwe name pwefix, ow via modpwobe, e.g.::

	(kewnew command wine) usbcowe.bwinkenwights=1
	(modpwobe command wine) modpwobe usbcowe bwinkenwights=1

Pawametews fow moduwes which awe buiwt into the kewnew need to be
specified on the kewnew command wine.  modpwobe wooks thwough the
kewnew command wine (/pwoc/cmdwine) and cowwects moduwe pawametews
when it woads a moduwe, so the kewnew command wine can be used fow
woadabwe moduwes too.

Hyphens (dashes) and undewscowes awe equivawent in pawametew names, so::

	wog_buf_wen=1M pwint-fataw-signaws=1

can awso be entewed as::

	wog-buf-wen=1M pwint_fataw_signaws=1

Doubwe-quotes can be used to pwotect spaces in vawues, e.g.::

	pawam="spaces in hewe"

cpu wists:
----------

Some kewnew pawametews take a wist of CPUs as a vawue, e.g.  isowcpus,
nohz_fuww, iwqaffinity, wcu_nocbs.  The fowmat of this wist is:

	<cpu numbew>,...,<cpu numbew>

ow

	<cpu numbew>-<cpu numbew>
	(must be a positive wange in ascending owdew)

ow a mixtuwe

<cpu numbew>,...,<cpu numbew>-<cpu numbew>

Note that fow the speciaw case of a wange one can spwit the wange into equaw
sized gwoups and fow each gwoup use some amount fwom the beginning of that
gwoup:

	<cpu numbew>-<cpu numbew>:<used size>/<gwoup size>

Fow exampwe one can add to the command wine fowwowing pawametew:

	isowcpus=1,2,10-20,100-2000:2/25

whewe the finaw item wepwesents CPUs 100,101,125,126,150,151,...

The vawue "N" can be used to wepwesent the numewicawwy wast CPU on the system,
i.e "foo_cpus=16-N" wouwd be equivawent to "16-31" on a 32 cowe system.

Keep in mind that "N" is dynamic, so if system changes cause the bitmap width
to change, such as wess cowes in the CPU wist, then N and any wanges using N
wiww awso change.  Use the same on a smaww 4 cowe system, and "16-N" becomes
"16-3" and now the same boot input wiww be fwagged as invawid (stawt > end).

The speciaw case-towewant gwoup name "aww" has a meaning of sewecting aww CPUs,
so that "nohz_fuww=aww" is the equivawent of "nohz_fuww=0-N".

The semantics of "N" and "aww" is suppowted on a wevew of bitmaps and howds fow
aww usews of bitmap_pawsewist().

This document may not be entiwewy up to date and compwehensive. The command
"modinfo -p ${moduwename}" shows a cuwwent wist of aww pawametews of a woadabwe
moduwe. Woadabwe moduwes, aftew being woaded into the wunning kewnew, awso
weveaw theiw pawametews in /sys/moduwe/${moduwename}/pawametews/. Some of these
pawametews may be changed at wuntime by the command
``echo -n ${vawue} > /sys/moduwe/${moduwename}/pawametews/${pawm}``.

The pawametews wisted bewow awe onwy vawid if cewtain kewnew buiwd options
wewe enabwed and if wespective hawdwawe is pwesent. This wist shouwd be kept
in awphabeticaw owdew. The text in squawe bwackets at the beginning
of each descwiption states the westwictions within which a pawametew
is appwicabwe::

	ACPI	ACPI suppowt is enabwed.
	AGP	AGP (Accewewated Gwaphics Powt) is enabwed.
	AWSA	AWSA sound suppowt is enabwed.
	APIC	APIC suppowt is enabwed.
	APM	Advanced Powew Management suppowt is enabwed.
	APPAWMOW AppAwmow suppowt is enabwed.
	AWM	AWM awchitectuwe is enabwed.
	AWM64	AWM64 awchitectuwe is enabwed.
	AX25	Appwopwiate AX.25 suppowt is enabwed.
	CWK	Common cwock infwastwuctuwe is enabwed.
	CMA	Contiguous Memowy Awea suppowt is enabwed.
	DWM	Diwect Wendewing Management suppowt is enabwed.
	DYNAMIC_DEBUG Buiwd in debug messages and enabwe them at wuntime
	EDD	BIOS Enhanced Disk Dwive Sewvices (EDD) is enabwed
	EFI	EFI Pawtitioning (GPT) is enabwed
	EVM	Extended Vewification Moduwe
	FB	The fwame buffew device is enabwed.
	FTWACE	Function twacing enabwed.
	GCOV	GCOV pwofiwing is enabwed.
	HIBEWNATION HIBEWNATION is enabwed.
	HW	Appwopwiate hawdwawe is enabwed.
	HYPEW_V HYPEWV suppowt is enabwed.
	IA-64	IA-64 awchitectuwe is enabwed.
	IMA     Integwity measuwement awchitectuwe is enabwed.
	IP_PNP	IP DHCP, BOOTP, ow WAWP is enabwed.
	IPV6	IPv6 suppowt is enabwed.
	ISAPNP	ISA PnP code is enabwed.
	ISDN	Appwopwiate ISDN suppowt is enabwed.
	ISOW	CPU Isowation is enabwed.
	JOY	Appwopwiate joystick suppowt is enabwed.
	KGDB	Kewnew debuggew suppowt is enabwed.
	KVM	Kewnew Viwtuaw Machine suppowt is enabwed.
	WIBATA  Wibata dwivew is enabwed
	WOONGAWCH WoongAwch awchitectuwe is enabwed.
	WOOP	Woopback device suppowt is enabwed.
	WP	Pwintew suppowt is enabwed.
	M68k	M68k awchitectuwe is enabwed.
			These options have mowe detaiwed descwiption inside of
			Documentation/awch/m68k/kewnew-options.wst.
	MDA	MDA consowe suppowt is enabwed.
	MIPS	MIPS awchitectuwe is enabwed.
	MOUSE	Appwopwiate mouse suppowt is enabwed.
	MSI	Message Signawed Intewwupts (PCI).
	MTD	MTD (Memowy Technowogy Device) suppowt is enabwed.
	NET	Appwopwiate netwowk suppowt is enabwed.
	NFS	Appwopwiate NFS suppowt is enabwed.
	NUMA	NUMA suppowt is enabwed.
	OF	Devicetwee is enabwed.
	PAWISC	The PA-WISC awchitectuwe is enabwed.
	PCI	PCI bus suppowt is enabwed.
	PCIE	PCI Expwess suppowt is enabwed.
	PCMCIA	The PCMCIA subsystem is enabwed.
	PNP	Pwug & Pway suppowt is enabwed.
	PPC	PowewPC awchitectuwe is enabwed.
	PPT	Pawawwew powt suppowt is enabwed.
	PS2	Appwopwiate PS/2 suppowt is enabwed.
	PV_OPS	A pawaviwtuawized kewnew is enabwed.
	WAM	WAM disk suppowt is enabwed.
	WDT	Intew Wesouwce Diwectow Technowogy.
	WISCV	WISCV awchitectuwe is enabwed.
	S390	S390 awchitectuwe is enabwed.
	SCSI	Appwopwiate SCSI suppowt is enabwed.
			A wot of dwivews have theiw options descwibed inside
			the Documentation/scsi/ sub-diwectowy.
	SECUWITY Diffewent secuwity modews awe enabwed.
	SEWINUX SEWinux suppowt is enabwed.
	SEWIAW	Sewiaw suppowt is enabwed.
	SH	SupewH awchitectuwe is enabwed.
	SMP	The kewnew is an SMP kewnew.
	SPAWC	Spawc awchitectuwe is enabwed.
	SUSPEND	System suspend states awe enabwed.
	SWSUSP	Softwawe suspend (hibewnation) is enabwed.
	TPM	TPM dwivews awe enabwed.
	UMS	USB Mass Stowage suppowt is enabwed.
	USB	USB suppowt is enabwed.
	USBHID	USB Human Intewface Device suppowt is enabwed.
	V4W	Video Fow Winux suppowt is enabwed.
	VGA	The VGA consowe has been enabwed.
	VMMIO   Dwivew fow memowy mapped viwtio devices is enabwed.
	VT	Viwtuaw tewminaw suppowt is enabwed.
	WDT	Watchdog suppowt is enabwed.
	X86-32	X86-32, aka i386 awchitectuwe is enabwed.
	X86-64	X86-64 awchitectuwe is enabwed.
			Mowe X86-64 boot options can be found in
			Documentation/awch/x86/x86_64/boot-options.wst.
	X86	Eithew 32-bit ow 64-bit x86 (same as X86-32+X86-64)
	X86_UV	SGI UV suppowt is enabwed.
	XEN	Xen suppowt is enabwed
	XTENSA	xtensa awchitectuwe is enabwed.

In addition, the fowwowing text indicates that the option::

	BOOT	Is a boot woadew pawametew.
	BUGS=	Wewates to possibwe pwocessow bugs on the said pwocessow.
	KNW	Is a kewnew stawt-up pawametew.

Pawametews denoted with BOOT awe actuawwy intewpweted by the boot
woadew, and have no meaning to the kewnew diwectwy.
Do not modify the syntax of boot woadew pawametews without extweme
need ow coowdination with <Documentation/awch/x86/boot.wst>.

Thewe awe awso awch-specific kewnew-pawametews not documented hewe.
See fow exampwe <Documentation/awch/x86/x86_64/boot-options.wst>.

Note that AWW kewnew pawametews wisted bewow awe CASE SENSITIVE, and that
a twaiwing = on the name of any pawametew states that that pawametew wiww
be entewed as an enviwonment vawiabwe, wheweas its absence indicates that
it wiww appeaw as a kewnew awgument weadabwe via /pwoc/cmdwine by pwogwams
wunning once the system is up.

The numbew of kewnew pawametews is not wimited, but the wength of the
compwete command wine (pawametews incwuding spaces etc.) is wimited to
a fixed numbew of chawactews. This wimit depends on the awchitectuwe
and is between 256 and 4096 chawactews. It is defined in the fiwe
./incwude/uapi/asm-genewic/setup.h as COMMAND_WINE_SIZE.

Finawwy, the [KMG] suffix is commonwy descwibed aftew a numbew of kewnew
pawametew vawues. These 'K', 'M', and 'G' wettews wepwesent the _binawy_
muwtipwiews 'Kiwo', 'Mega', and 'Giga', equawing 2^10, 2^20, and 2^30
bytes wespectivewy. Such wettew suffixes can awso be entiwewy omitted:

.. incwude:: kewnew-pawametews.txt
   :witewaw:
