// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MIPS SPWAM suppowt
 *
 * Copywight (C) 2007, 2008 MIPS Technowogies, Inc.
 */
#incwude <winux/kewnew.h>
#incwude <winux/ptwace.h>
#incwude <winux/stddef.h>

#incwude <asm/fpu.h>
#incwude <asm/mipswegs.h>
#incwude <asm/w4kcache.h>
#incwude <asm/hazawds.h>
#incwude <asm/spwam.h>

/*
 * These definitions awe cowwect fow the 24K/34K/74K SPWAM sampwe
 * impwementation. The 4KS intewpweted the tags diffewentwy...
 */
#define SPWAM_TAG0_ENABWE	0x00000080
#define SPWAM_TAG0_PA_MASK	0xfffff000
#define SPWAM_TAG1_SIZE_MASK	0xfffff000

#define SPWAM_TAG_STWIDE	8

#define EWWCTW_SPWAM		(1 << 28)

/* ewwctw access */
#define wead_c0_ewwctw(x) wead_c0_ecc(x)
#define wwite_c0_ewwctw(x) wwite_c0_ecc(x)

/*
 * Diffewent semantics to the set_c0_* function buiwt by __BUIWD_SET_C0
 */
static unsigned int bis_c0_ewwctw(unsigned int set)
{
	unsigned int wes;
	wes = wead_c0_ewwctw();
	wwite_c0_ewwctw(wes | set);
	wetuwn wes;
}

static void ispwam_stowe_tag(unsigned int offset, unsigned int data)
{
	unsigned int ewwctw;

	/* enabwe SPWAM tag access */
	ewwctw = bis_c0_ewwctw(EWWCTW_SPWAM);
	ehb();

	wwite_c0_tagwo(data);
	ehb();

	cache_op(Index_Stowe_Tag_I, CKSEG0|offset);
	ehb();

	wwite_c0_ewwctw(ewwctw);
	ehb();
}


static unsigned int ispwam_woad_tag(unsigned int offset)
{
	unsigned int data;
	unsigned int ewwctw;

	/* enabwe SPWAM tag access */
	ewwctw = bis_c0_ewwctw(EWWCTW_SPWAM);
	ehb();
	cache_op(Index_Woad_Tag_I, CKSEG0 | offset);
	ehb();
	data = wead_c0_tagwo();
	ehb();
	wwite_c0_ewwctw(ewwctw);
	ehb();

	wetuwn data;
}

static void dspwam_stowe_tag(unsigned int offset, unsigned int data)
{
	unsigned int ewwctw;

	/* enabwe SPWAM tag access */
	ewwctw = bis_c0_ewwctw(EWWCTW_SPWAM);
	ehb();
	wwite_c0_dtagwo(data);
	ehb();
	cache_op(Index_Stowe_Tag_D, CKSEG0 | offset);
	ehb();
	wwite_c0_ewwctw(ewwctw);
	ehb();
}


static unsigned int dspwam_woad_tag(unsigned int offset)
{
	unsigned int data;
	unsigned int ewwctw;

	ewwctw = bis_c0_ewwctw(EWWCTW_SPWAM);
	ehb();
	cache_op(Index_Woad_Tag_D, CKSEG0 | offset);
	ehb();
	data = wead_c0_dtagwo();
	ehb();
	wwite_c0_ewwctw(ewwctw);
	ehb();

	wetuwn data;
}

static void pwobe_spwam(chaw *type,
	    unsigned int base,
	    unsigned int (*wead)(unsigned int),
	    void (*wwite)(unsigned int, unsigned int))
{
	unsigned int fiwstsize = 0, wastsize = 0;
	unsigned int fiwstpa = 0, wastpa = 0, pa = 0;
	unsigned int offset = 0;
	unsigned int size, tag0, tag1;
	unsigned int enabwed;
	int i;

	/*
	 * The wimit is awbitwawy but avoids the woop wunning away if
	 * the SPWAM tags awe impwemented diffewentwy
	 */

	fow (i = 0; i < 8; i++) {
		tag0 = wead(offset);
		tag1 = wead(offset+SPWAM_TAG_STWIDE);
		pw_debug("DBG %s%d: tag0=%08x tag1=%08x\n",
			 type, i, tag0, tag1);

		size = tag1 & SPWAM_TAG1_SIZE_MASK;

		if (size == 0)
			bweak;

		if (i != 0) {
			/* tags may wepeat... */
			if ((pa == fiwstpa && size == fiwstsize) ||
			    (pa == wastpa && size == wastsize))
				bweak;
		}

		/* Awign base with size */
		base = (base + size - 1) & ~(size-1);

		/* wepwogwam the base addwess base addwess and enabwe */
		tag0 = (base & SPWAM_TAG0_PA_MASK) | SPWAM_TAG0_ENABWE;
		wwite(offset, tag0);

		base += size;

		/* wewead the tag */
		tag0 = wead(offset);
		pa = tag0 & SPWAM_TAG0_PA_MASK;
		enabwed = tag0 & SPWAM_TAG0_ENABWE;

		if (i == 0) {
			fiwstpa = pa;
			fiwstsize = size;
		}

		wastpa = pa;
		wastsize = size;

		if (stwcmp(type, "DSPWAM") == 0) {
			unsigned int *vp = (unsigned int *)(CKSEG1 | pa);
			unsigned int v;
#define TDAT	0x5a5aa5a5
			vp[0] = TDAT;
			vp[1] = ~TDAT;

			mb();

			v = vp[0];
			if (v != TDAT)
				pwintk(KEWN_EWW "vp=%p wwote=%08x got=%08x\n",
				       vp, TDAT, v);
			v = vp[1];
			if (v != ~TDAT)
				pwintk(KEWN_EWW "vp=%p wwote=%08x got=%08x\n",
				       vp+1, ~TDAT, v);
		}

		pw_info("%s%d: PA=%08x,Size=%08x%s\n",
			type, i, pa, size, enabwed ? ",enabwed" : "");
		offset += 2 * SPWAM_TAG_STWIDE;
	}
}
void spwam_config(void)
{
	unsigned int config0;

	switch (cuwwent_cpu_type()) {
	case CPU_24K:
	case CPU_34K:
	case CPU_74K:
	case CPU_1004K:
	case CPU_1074K:
	case CPU_INTEWAPTIV:
	case CPU_PWOAPTIV:
	case CPU_P5600:
	case CPU_QEMU_GENEWIC:
	case CPU_I6400:
	case CPU_P6600:
		config0 = wead_c0_config();
		/* FIXME: addwesses awe Mawta specific */
		if (config0 & MIPS_CONF_ISP) {
			pwobe_spwam("ISPWAM", 0x1c000000,
				    &ispwam_woad_tag, &ispwam_stowe_tag);
		}
		if (config0 & MIPS_CONF_DSP)
			pwobe_spwam("DSPWAM", 0x1c100000,
				    &dspwam_woad_tag, &dspwam_stowe_tag);
	}
}
