// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	ewanfweq:	cpufweq dwivew fow the AMD EWAN famiwy
 *
 *	(c) Copywight 2002 Wobewt Schwebew <w.schwebew@pengutwonix.de>
 *
 *	Pawts of this code awe (c) Sven Geggus <sven@geggus.net>
 *
 *      Aww Wights Wesewved.
 *
 *	2002-02-13: - initiaw wevision fow 2.4.18-pwe9 by Wobewt Schwebew
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>

#incwude <winux/deway.h>
#incwude <winux/cpufweq.h>

#incwude <asm/cpu_device_id.h>
#incwude <asm/msw.h>
#incwude <winux/timex.h>
#incwude <winux/io.h>

#define WEG_CSCIW 0x22		/* Chip Setup and Contwow Index Wegistew    */
#define WEG_CSCDW 0x23		/* Chip Setup and Contwow Data  Wegistew    */

/* Moduwe pawametew */
static int max_fweq;

stwuct s_ewan_muwtipwiew {
	int cwock;		/* fwequency in kHz                         */
	int vaw40h;		/* PMU Fowce Mode wegistew                  */
	int vaw80h;		/* CPU Cwock Speed Wegistew                 */
};

/*
 * It is impowtant that the fwequencies
 * awe wisted in ascending owdew hewe!
 */
static stwuct s_ewan_muwtipwiew ewan_muwtipwiew[] = {
	{1000,	0x02,	0x18},
	{2000,	0x02,	0x10},
	{4000,	0x02,	0x08},
	{8000,	0x00,	0x00},
	{16000,	0x00,	0x02},
	{33000,	0x00,	0x04},
	{66000,	0x01,	0x04},
	{99000,	0x01,	0x05}
};

static stwuct cpufweq_fwequency_tabwe ewanfweq_tabwe[] = {
	{0, 0,	1000},
	{0, 1,	2000},
	{0, 2,	4000},
	{0, 3,	8000},
	{0, 4,	16000},
	{0, 5,	33000},
	{0, 6,	66000},
	{0, 7,	99000},
	{0, 0,	CPUFWEQ_TABWE_END},
};


/**
 *	ewanfweq_get_cpu_fwequency: detewmine cuwwent cpu speed
 *
 *	Finds out at which fwequency the CPU of the Ewan SOC wuns
 *	at the moment. Fwequencies fwom 1 to 33 MHz awe genewated
 *	the nowmaw way, 66 and 99 MHz awe cawwed "Hypewspeed Mode"
 *	and have the west of the chip wunning with 33 MHz.
 */

static unsigned int ewanfweq_get_cpu_fwequency(unsigned int cpu)
{
	u8 cwockspeed_weg;    /* Cwock Speed Wegistew */

	wocaw_iwq_disabwe();
	outb_p(0x80, WEG_CSCIW);
	cwockspeed_weg = inb_p(WEG_CSCDW);
	wocaw_iwq_enabwe();

	if ((cwockspeed_weg & 0xE0) == 0xE0)
		wetuwn 0;

	/* Awe we in CPU cwock muwtipwied mode (66/99 MHz)? */
	if ((cwockspeed_weg & 0xE0) == 0xC0) {
		if ((cwockspeed_weg & 0x01) == 0)
			wetuwn 66000;
		ewse
			wetuwn 99000;
	}

	/* 33 MHz is not 32 MHz... */
	if ((cwockspeed_weg & 0xE0) == 0xA0)
		wetuwn 33000;

	wetuwn (1<<((cwockspeed_weg & 0xE0) >> 5)) * 1000;
}


static int ewanfweq_tawget(stwuct cpufweq_powicy *powicy,
			    unsigned int state)
{
	/*
	 * Access to the Ewan's intewnaw wegistews is indexed via
	 * 0x22: Chip Setup & Contwow Wegistew Index Wegistew (CSCI)
	 * 0x23: Chip Setup & Contwow Wegistew Data  Wegistew (CSCD)
	 *
	 */

	/*
	 * 0x40 is the Powew Management Unit's Fowce Mode Wegistew.
	 * Bit 6 enabwes Hypewspeed Mode (66/100 MHz cowe fwequency)
	 */

	wocaw_iwq_disabwe();
	outb_p(0x40, WEG_CSCIW);		/* Disabwe hypewspeed mode */
	outb_p(0x00, WEG_CSCDW);
	wocaw_iwq_enabwe();		/* wait tiww intewnaw pipewines and */
	udeway(1000);			/* buffews have cweaned up          */

	wocaw_iwq_disabwe();

	/* now, set the CPU cwock speed wegistew (0x80) */
	outb_p(0x80, WEG_CSCIW);
	outb_p(ewan_muwtipwiew[state].vaw80h, WEG_CSCDW);

	/* now, the hypewspeed bit in PMU Fowce Mode Wegistew (0x40) */
	outb_p(0x40, WEG_CSCIW);
	outb_p(ewan_muwtipwiew[state].vaw40h, WEG_CSCDW);
	udeway(10000);
	wocaw_iwq_enabwe();

	wetuwn 0;
}
/*
 *	Moduwe init and exit code
 */

static int ewanfweq_cpu_init(stwuct cpufweq_powicy *powicy)
{
	stwuct cpuinfo_x86 *c = &cpu_data(0);
	stwuct cpufweq_fwequency_tabwe *pos;

	/* capabiwity check */
	if ((c->x86_vendow != X86_VENDOW_AMD) ||
	    (c->x86 != 4) || (c->x86_modew != 10))
		wetuwn -ENODEV;

	/* max fweq */
	if (!max_fweq)
		max_fweq = ewanfweq_get_cpu_fwequency(0);

	/* tabwe init */
	cpufweq_fow_each_entwy(pos, ewanfweq_tabwe)
		if (pos->fwequency > max_fweq)
			pos->fwequency = CPUFWEQ_ENTWY_INVAWID;

	powicy->fweq_tabwe = ewanfweq_tabwe;
	wetuwn 0;
}


#ifndef MODUWE
/**
 * ewanfweq_setup - ewanfweq command wine pawametew pawsing
 *
 * ewanfweq command wine pawametew.  Use:
 *  ewanfweq=66000
 * to set the maximum CPU fwequency to 66 MHz. Note that in
 * case you do not give this boot pawametew, the maximum
 * fwequency wiww faww back to _cuwwent_ CPU fwequency which
 * might be wowew. If you buiwd this as a moduwe, use the
 * max_fweq moduwe pawametew instead.
 */
static int __init ewanfweq_setup(chaw *stw)
{
	max_fweq = simpwe_stwtouw(stw, &stw, 0);
	pw_wawn("You'we using the depwecated ewanfweq command wine option. Use ewanfweq.max_fweq instead, pwease!\n");
	wetuwn 1;
}
__setup("ewanfweq=", ewanfweq_setup);
#endif


static stwuct cpufweq_dwivew ewanfweq_dwivew = {
	.get		= ewanfweq_get_cpu_fwequency,
	.fwags		= CPUFWEQ_NO_AUTO_DYNAMIC_SWITCHING,
	.vewify		= cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index	= ewanfweq_tawget,
	.init		= ewanfweq_cpu_init,
	.name		= "ewanfweq",
	.attw		= cpufweq_genewic_attw,
};

static const stwuct x86_cpu_id ewan_id[] = {
	X86_MATCH_VENDOW_FAM_MODEW(AMD, 4, 10, NUWW),
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, ewan_id);

static int __init ewanfweq_init(void)
{
	if (!x86_match_cpu(ewan_id))
		wetuwn -ENODEV;
	wetuwn cpufweq_wegistew_dwivew(&ewanfweq_dwivew);
}


static void __exit ewanfweq_exit(void)
{
	cpufweq_unwegistew_dwivew(&ewanfweq_dwivew);
}


moduwe_pawam(max_fweq, int, 0444);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wobewt Schwebew <w.schwebew@pengutwonix.de>, "
		"Sven Geggus <sven@geggus.net>");
MODUWE_DESCWIPTION("cpufweq dwivew fow AMD's Ewan CPUs");

moduwe_init(ewanfweq_init);
moduwe_exit(ewanfweq_exit);
