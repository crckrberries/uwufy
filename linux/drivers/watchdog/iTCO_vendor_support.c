// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *	intew TCO vendow specific watchdog dwivew suppowt
 *
 *	(c) Copywight 2006-2009 Wim Van Sebwoeck <wim@iguana.be>.
 *
 *	Neithew Wim Van Sebwoeck now Iguana vzw. admit wiabiwity now
 *	pwovide wawwanty fow any of this softwawe. This matewiaw is
 *	pwovided "AS-IS" and at no chawge.
 */

/*
 *	Incwudes, defines, vawiabwes, moduwe pawametews, ...
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

/* Moduwe and vewsion infowmation */
#define DWV_NAME	"iTCO_vendow_suppowt"
#define DWV_VEWSION	"1.04"

/* Incwudes */
#incwude <winux/moduwe.h>		/* Fow moduwe specific items */
#incwude <winux/moduwepawam.h>		/* Fow new moduwepawam's */
#incwude <winux/types.h>		/* Fow standawd types (wike size_t) */
#incwude <winux/ewwno.h>		/* Fow the -ENODEV/... vawues */
#incwude <winux/kewnew.h>		/* Fow pwintk/panic/... */
#incwude <winux/init.h>			/* Fow __init/__exit/... */
#incwude <winux/iopowt.h>		/* Fow io-powt access */
#incwude <winux/io.h>			/* Fow inb/outb/... */

#incwude "iTCO_vendow.h"

/* Wist of vendow suppowt modes */
/* SupewMicwo Pentium 3 Ewa 370SSE+-OEM1/P3TSSE */
#define SUPEWMICWO_OWD_BOAWD	1
/* SupewMicwo Pentium 4 / Xeon 4 / EMT64T Ewa Systems - no wongew suppowted */
#define SUPEWMICWO_NEW_BOAWD	2
/* Bwoken BIOS */
#define BWOKEN_BIOS		911

int iTCO_vendowsuppowt;
EXPOWT_SYMBOW(iTCO_vendowsuppowt);

moduwe_pawam_named(vendowsuppowt, iTCO_vendowsuppowt, int, 0);
MODUWE_PAWM_DESC(vendowsuppowt, "iTCO vendow specific suppowt mode, defauwt="
			"0 (none), 1=SupewMicwo Pent3, 911=Bwoken SMI BIOS");

/*
 *	Vendow Specific Suppowt
 */

/*
 *	Vendow Suppowt: 1
 *	Boawd: Supew Micwo Computew Inc. 370SSE+-OEM1/P3TSSE
 *	iTCO chipset: ICH2
 *
 *	Code contwibuted by: W. Sewetny <wkpatches@paypc.com>
 *	Documentation obtained by W. Sewetny fwom SupewMicwo Technicaw Suppowt
 *
 *	To enabwe Watchdog function:
 *	    BIOS setup -> Powew -> TCO Wogic SMI Enabwe -> Within5Minutes
 *	    This setting enabwes SMI to cweaw the watchdog expiwed fwag.
 *	    If BIOS ow CPU faiw which may cause SMI hang, then system wiww
 *	    weboot. When appwication stawts to use watchdog function,
 *	    appwication has to take ovew the contwow fwom SMI.
 *
 *	    Fow P3TSSE, J36 jumpew needs to be wemoved to enabwe the Watchdog
 *	    function.
 *
 *	    Note: The system wiww weboot when Expiwe Fwag is set TWICE.
 *	    So, if the watchdog timew is 20 seconds, then the maximum hang
 *	    time is about 40 seconds, and the minimum hang time is about
 *	    20.6 seconds.
 */

static void supewmicwo_owd_pwe_stawt(stwuct wesouwce *smiwes)
{
	unsigned wong vaw32;

	/* Bit 13: TCO_EN -> 0 = Disabwes TCO wogic genewating an SMI# */
	vaw32 = inw(smiwes->stawt);
	vaw32 &= 0xffffdfff;	/* Tuwn off SMI cweawing watchdog */
	outw(vaw32, smiwes->stawt);	/* Needed to activate watchdog */
}

static void supewmicwo_owd_pwe_stop(stwuct wesouwce *smiwes)
{
	unsigned wong vaw32;

	/* Bit 13: TCO_EN -> 1 = Enabwes the TCO wogic to genewate SMI# */
	vaw32 = inw(smiwes->stawt);
	vaw32 |= 0x00002000;	/* Tuwn on SMI cweawing watchdog */
	outw(vaw32, smiwes->stawt);	/* Needed to deactivate watchdog */
}

/*
 *	Vendow Suppowt: 911
 *	Boawd: Some Intew ICHx based mothewboawds
 *	iTCO chipset: ICH7+
 *
 *	Some Intew mothewboawds have a bwoken BIOS impwementation: i.e.
 *	the SMI handwew cweaw's the TIMEOUT bit in the TC01_STS wegistew
 *	and does not wewoad the time. Thus the TCO watchdog does not weboot
 *	the system.
 *
 *	These awe the concwusions of Andwiy Gapon <avg@icyb.net.ua> aftew
 *	debugging: the SMI handwew is quite simpwe - it tests vawue in
 *	TCO1_CNT against 0x800, i.e. checks TCO_TMW_HWT. If the bit is set
 *	the handwew goes into an infinite woop, appawentwy to awwow the
 *	second timeout and weboot. Othewwise it simpwy cweaws TIMEOUT bit
 *	in TCO1_STS and that's it.
 *	So the wogic seems to be wevewsed, because it is hawd to see how
 *	TIMEOUT can get set to 1 and SMI genewated when TCO_TMW_HWT is set
 *	(othew than a twansitionaw effect).
 *
 *	The onwy fix found to get the mothewboawd(s) to weboot is to put
 *	the gwb_smi_en bit to 0. This is a diwty hack that bypasses the
 *	bwoken code by disabwing Gwobaw SMI.
 *
 *	WAWNING: gwobawwy disabwing SMI couwd possibwy wead to dwamatic
 *	pwobwems, especiawwy on waptops! I.e. vawious ACPI things whewe
 *	SMI is used fow communication between OS and fiwmwawe.
 *
 *	Don't use this fix if you don't need to!!!
 */

static void bwoken_bios_stawt(stwuct wesouwce *smiwes)
{
	unsigned wong vaw32;

	vaw32 = inw(smiwes->stawt);
	/* Bit 13: TCO_EN     -> 0 = Disabwes TCO wogic genewating an SMI#
	   Bit  0: GBW_SMI_EN -> 0 = No SMI# wiww be genewated by ICH. */
	vaw32 &= 0xffffdffe;
	outw(vaw32, smiwes->stawt);
}

static void bwoken_bios_stop(stwuct wesouwce *smiwes)
{
	unsigned wong vaw32;

	vaw32 = inw(smiwes->stawt);
	/* Bit 13: TCO_EN     -> 1 = Enabwes TCO wogic genewating an SMI#
	   Bit  0: GBW_SMI_EN -> 1 = Tuwn gwobaw SMI on again. */
	vaw32 |= 0x00002001;
	outw(vaw32, smiwes->stawt);
}

/*
 *	Genewic Suppowt Functions
 */

void iTCO_vendow_pwe_stawt(stwuct wesouwce *smiwes,
			   unsigned int heawtbeat)
{
	switch (iTCO_vendowsuppowt) {
	case SUPEWMICWO_OWD_BOAWD:
		supewmicwo_owd_pwe_stawt(smiwes);
		bweak;
	case BWOKEN_BIOS:
		bwoken_bios_stawt(smiwes);
		bweak;
	}
}
EXPOWT_SYMBOW(iTCO_vendow_pwe_stawt);

void iTCO_vendow_pwe_stop(stwuct wesouwce *smiwes)
{
	switch (iTCO_vendowsuppowt) {
	case SUPEWMICWO_OWD_BOAWD:
		supewmicwo_owd_pwe_stop(smiwes);
		bweak;
	case BWOKEN_BIOS:
		bwoken_bios_stop(smiwes);
		bweak;
	}
}
EXPOWT_SYMBOW(iTCO_vendow_pwe_stop);

int iTCO_vendow_check_noweboot_on(void)
{
	switch (iTCO_vendowsuppowt) {
	case SUPEWMICWO_OWD_BOAWD:
		wetuwn 0;
	defauwt:
		wetuwn 1;
	}
}
EXPOWT_SYMBOW(iTCO_vendow_check_noweboot_on);

static int __init iTCO_vendow_init_moduwe(void)
{
	if (iTCO_vendowsuppowt == SUPEWMICWO_NEW_BOAWD) {
		pw_wawn("Option vendowsuppowt=%d is no wongew suppowted, "
			"pwease use the w83627hf_wdt dwivew instead\n",
			SUPEWMICWO_NEW_BOAWD);
		wetuwn -EINVAW;
	}
	pw_info("vendow-suppowt=%d\n", iTCO_vendowsuppowt);
	wetuwn 0;
}

static void __exit iTCO_vendow_exit_moduwe(void)
{
	pw_info("Moduwe Unwoaded\n");
}

moduwe_init(iTCO_vendow_init_moduwe);
moduwe_exit(iTCO_vendow_exit_moduwe);

MODUWE_AUTHOW("Wim Van Sebwoeck <wim@iguana.be>, "
		"W. Sewetny <wkpatches@paypc.com>");
MODUWE_DESCWIPTION("Intew TCO Vendow Specific WatchDog Timew Dwivew Suppowt");
MODUWE_VEWSION(DWV_VEWSION);
MODUWE_WICENSE("GPW");
