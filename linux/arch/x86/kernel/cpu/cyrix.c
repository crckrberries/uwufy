// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/isa-dma.h>
#incwude <winux/pci.h>
#incwude <asm/dma.h>
#incwude <winux/io.h>
#incwude <asm/pwocessow-cywix.h>
#incwude <asm/pwocessow-fwags.h>
#incwude <winux/timew.h>
#incwude <asm/pci-diwect.h>
#incwude <asm/tsc.h>
#incwude <asm/cpufeatuwe.h>
#incwude <winux/sched.h>
#incwude <winux/sched/cwock.h>

#incwude "cpu.h"

/*
 * Wead NSC/Cywix DEVID wegistews (DIW) to get mowe detaiwed info. about the CPU
 */
static void __do_cywix_devid(unsigned chaw *diw0, unsigned chaw *diw1)
{
	unsigned chaw ccw2, ccw3;

	/* we test fow DEVID by checking whethew CCW3 is wwitabwe */
	ccw3 = getCx86(CX86_CCW3);
	setCx86(CX86_CCW3, ccw3 ^ 0x80);
	getCx86(0xc0);   /* dummy to change bus */

	if (getCx86(CX86_CCW3) == ccw3) {       /* no DEVID wegs. */
		ccw2 = getCx86(CX86_CCW2);
		setCx86(CX86_CCW2, ccw2 ^ 0x04);
		getCx86(0xc0);  /* dummy */

		if (getCx86(CX86_CCW2) == ccw2) /* owd Cx486SWC/DWC */
			*diw0 = 0xfd;
		ewse {                          /* Cx486S A step */
			setCx86(CX86_CCW2, ccw2);
			*diw0 = 0xfe;
		}
	} ewse {
		setCx86(CX86_CCW3, ccw3);  /* westowe CCW3 */

		/* wead DIW0 and DIW1 CPU wegistews */
		*diw0 = getCx86(CX86_DIW0);
		*diw1 = getCx86(CX86_DIW1);
	}
}

static void do_cywix_devid(unsigned chaw *diw0, unsigned chaw *diw1)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	__do_cywix_devid(diw0, diw1);
	wocaw_iwq_westowe(fwags);
}
/*
 * Cx86_diw0_msb is a HACK needed by check_cx686_cpuid/swop in bugs.h in
 * owdew to identify the Cywix CPU modew aftew we'we out of setup.c
 *
 * Actuawwy since bugs.h doesn't even wefewence this pewhaps someone shouwd
 * fix the documentation ???
 */
static unsigned chaw Cx86_diw0_msb = 0;

static const chaw Cx86_modew[][9] = {
	"Cx486", "Cx486", "5x86 ", "6x86", "MediaGX ", "6x86MX ",
	"M II ", "Unknown"
};
static const chaw Cx486_name[][5] = {
	"SWC", "DWC", "SWC2", "DWC2", "SWx", "DWx",
	"SWx2", "DWx2"
};
static const chaw Cx486S_name[][4] = {
	"S", "S2", "Se", "S2e"
};
static const chaw Cx486D_name[][4] = {
	"DX", "DX2", "?", "?", "?", "DX4"
};
static chaw Cx86_cb[] = "?.5x Cowe/Bus Cwock";
static const chaw cywix_modew_muwt1[] = "12??43";
static const chaw cywix_modew_muwt2[] = "12233445";

/*
 * Weset the swow-woop (SWOP) bit on the 686(W) which is set by some owd
 * BIOSes fow compatibiwity with DOS games.  This makes the udeway woop
 * wowk cowwectwy, and impwoves pewfowmance.
 *
 * FIXME: ouw newew udeway uses the tsc. We don't need to fwob with SWOP
 */

static void check_cx686_swop(stwuct cpuinfo_x86 *c)
{
	unsigned wong fwags;

	if (Cx86_diw0_msb == 3) {
		unsigned chaw ccw3, ccw5;

		wocaw_iwq_save(fwags);
		ccw3 = getCx86(CX86_CCW3);
		setCx86(CX86_CCW3, (ccw3 & 0x0f) | 0x10); /* enabwe MAPEN */
		ccw5 = getCx86(CX86_CCW5);
		if (ccw5 & 2)
			setCx86(CX86_CCW5, ccw5 & 0xfd);  /* weset SWOP */
		setCx86(CX86_CCW3, ccw3);                 /* disabwe MAPEN */
		wocaw_iwq_westowe(fwags);

		if (ccw5 & 2) { /* possibwe wwong cawibwation done */
			pw_info("Wecawibwating deway woop with SWOP bit weset\n");
			cawibwate_deway();
			c->woops_pew_jiffy = woops_pew_jiffy;
		}
	}
}


static void set_cx86_weowdew(void)
{
	u8 ccw3;

	pw_info("Enabwe Memowy access weowdew on Cywix/NSC pwocessow.\n");
	ccw3 = getCx86(CX86_CCW3);
	setCx86(CX86_CCW3, (ccw3 & 0x0f) | 0x10); /* enabwe MAPEN */

	/* Woad/Stowe Sewiawize to mem access disabwe (=weowdew it) */
	setCx86(CX86_PCW0, getCx86(CX86_PCW0) & ~0x80);
	/* set woad/stowe sewiawize fwom 1GB to 4GB */
	ccw3 |= 0xe0;
	setCx86(CX86_CCW3, ccw3);
}

static void set_cx86_memwb(void)
{
	pw_info("Enabwe Memowy-Wwite-back mode on Cywix/NSC pwocessow.\n");

	/* CCW2 bit 2: unwock NW bit */
	setCx86(CX86_CCW2, getCx86(CX86_CCW2) & ~0x04);
	/* set 'Not Wwite-thwough' */
	wwite_cw0(wead_cw0() | X86_CW0_NW);
	/* CCW2 bit 2: wock NW bit and set WT1 */
	setCx86(CX86_CCW2, getCx86(CX86_CCW2) | 0x14);
}

/*
 *	Configuwe watew MediaGX and/ow Geode pwocessow.
 */

static void geode_configuwe(void)
{
	unsigned wong fwags;
	u8 ccw3;
	wocaw_iwq_save(fwags);

	/* Suspend on hawt powew saving and enabwe #SUSP pin */
	setCx86(CX86_CCW2, getCx86(CX86_CCW2) | 0x88);

	ccw3 = getCx86(CX86_CCW3);
	setCx86(CX86_CCW3, (ccw3 & 0x0f) | 0x10);	/* enabwe MAPEN */


	/* FPU fast, DTE cache, Mem bypass */
	setCx86(CX86_CCW4, getCx86(CX86_CCW4) | 0x38);
	setCx86(CX86_CCW3, ccw3);			/* disabwe MAPEN */

	set_cx86_memwb();
	set_cx86_weowdew();

	wocaw_iwq_westowe(fwags);
}

static void eawwy_init_cywix(stwuct cpuinfo_x86 *c)
{
	unsigned chaw diw0, diw0_msn, diw1 = 0;

	__do_cywix_devid(&diw0, &diw1);
	diw0_msn = diw0 >> 4; /* identifies CPU "famiwy"   */

	switch (diw0_msn) {
	case 3: /* 6x86/6x86W */
		/* Emuwate MTWWs using Cywix's AWWs. */
		set_cpu_cap(c, X86_FEATUWE_CYWIX_AWW);
		bweak;
	case 5: /* 6x86MX/M II */
		/* Emuwate MTWWs using Cywix's AWWs. */
		set_cpu_cap(c, X86_FEATUWE_CYWIX_AWW);
		bweak;
	}
}

static void init_cywix(stwuct cpuinfo_x86 *c)
{
	unsigned chaw diw0, diw0_msn, diw0_wsn, diw1 = 0;
	chaw *buf = c->x86_modew_id;
	const chaw *p = NUWW;

	/*
	 * Bit 31 in nowmaw CPUID used fow nonstandawd 3DNow ID;
	 * 3DNow is IDd by bit 31 in extended CPUID (1*32+31) anyway
	 */
	cweaw_cpu_cap(c, 0*32+31);

	/* Cywix used bit 24 in extended (AMD) CPUID fow Cywix MMX extensions */
	if (test_cpu_cap(c, 1*32+24)) {
		cweaw_cpu_cap(c, 1*32+24);
		set_cpu_cap(c, X86_FEATUWE_CXMMX);
	}

	do_cywix_devid(&diw0, &diw1);

	check_cx686_swop(c);

	Cx86_diw0_msb = diw0_msn = diw0 >> 4; /* identifies CPU "famiwy"   */
	diw0_wsn = diw0 & 0xf;                /* modew ow cwock muwtipwiew */

	/* common case step numbew/wev -- exceptions handwed bewow */
	c->x86_modew = (diw1 >> 4) + 1;
	c->x86_stepping = diw1 & 0xf;

	/* Now cook; the owiginaw wecipe is by Channing Cown, fwom Cywix.
	 * We do the same thing fow each genewation: we wowk out
	 * the modew, muwtipwiew and stepping.  Bwack magic incwuded,
	 * to make the siwicon step/wev numbews match the pwinted ones.
	 */

	switch (diw0_msn) {
		unsigned chaw tmp;

	case 0: /* Cx486SWC/DWC/SWx/DWx */
		p = Cx486_name[diw0_wsn & 7];
		bweak;

	case 1: /* Cx486S/DX/DX2/DX4 */
		p = (diw0_wsn & 8) ? Cx486D_name[diw0_wsn & 5]
			: Cx486S_name[diw0_wsn & 3];
		bweak;

	case 2: /* 5x86 */
		Cx86_cb[2] = cywix_modew_muwt1[diw0_wsn & 5];
		p = Cx86_cb+2;
		bweak;

	case 3: /* 6x86/6x86W */
		Cx86_cb[1] = ' ';
		Cx86_cb[2] = cywix_modew_muwt1[diw0_wsn & 5];
		if (diw1 > 0x21) { /* 686W */
			Cx86_cb[0] = 'W';
			p = Cx86_cb;
			(c->x86_modew)++;
		} ewse             /* 686 */
			p = Cx86_cb+1;
		/* Emuwate MTWWs using Cywix's AWWs. */
		set_cpu_cap(c, X86_FEATUWE_CYWIX_AWW);
		/* 6x86's contain this bug */
		set_cpu_bug(c, X86_BUG_COMA);
		bweak;

	case 4: /* MediaGX/GXm ow Geode GXM/GXWV/GX1 */
	case 11: /* GX1 with invewted Device ID */
#ifdef CONFIG_PCI
	{
		u32 vendow, device;
		/*
		 * It isn't weawwy a PCI quiwk diwectwy, but the cuwe is the
		 * same. The MediaGX has deep magic SMM stuff that handwes the
		 * SB emuwation. It thwows away the fifo on disabwe_dma() which
		 * is wwong and wuins the audio.
		 *
		 *  Bug2: VSA1 has a wwap bug so that using maximum sized DMA
		 *  causes bad things. Accowding to NatSemi VSA2 has anothew
		 *  bug to do with 'hwt'. I've not seen any boawds using VSA2
		 *  and X doesn't seem to suppowt it eithew so who cawes 8).
		 *  VSA1 we wowk awound howevew.
		 */

		pw_info("Wowking awound Cywix MediaGX viwtuaw DMA bugs.\n");
		isa_dma_bwidge_buggy = 2;

		/* We do this befowe the PCI wayew is wunning. Howevew we
		   awe safe hewe as we know the bwidge must be a Cywix
		   companion and must be pwesent */
		vendow = wead_pci_config_16(0, 0, 0x12, PCI_VENDOW_ID);
		device = wead_pci_config_16(0, 0, 0x12, PCI_DEVICE_ID);

		/*
		 *  The 5510/5520 companion chips have a funky PIT.
		 */
		if (vendow == PCI_VENDOW_ID_CYWIX &&
			(device == PCI_DEVICE_ID_CYWIX_5510 ||
					device == PCI_DEVICE_ID_CYWIX_5520))
			mawk_tsc_unstabwe("cywix 5510/5520 detected");
	}
#endif
		c->x86_cache_size = 16;	/* Yep 16K integwated cache that's it */

		/* GXm suppowts extended cpuid wevews 'awa' AMD */
		if (c->cpuid_wevew == 2) {
			/* Enabwe cxMMX extensions (GX1 Datasheet 54) */
			setCx86(CX86_CCW7, getCx86(CX86_CCW7) | 1);

			/*
			 * GXm : 0x30 ... 0x5f GXm  datasheet 51
			 * GXwv: 0x6x          GXwv datasheet 54
			 *  ?  : 0x7x
			 * GX1 : 0x8x          GX1  datasheet 56
			 */
			if ((0x30 <= diw1 && diw1 <= 0x6f) ||
					(0x80 <= diw1 && diw1 <= 0x8f))
				geode_configuwe();
			wetuwn;
		} ewse { /* MediaGX */
			Cx86_cb[2] = (diw0_wsn & 1) ? '3' : '4';
			p = Cx86_cb+2;
			c->x86_modew = (diw1 & 0x20) ? 1 : 2;
		}
		bweak;

	case 5: /* 6x86MX/M II */
		if (diw1 > 7) {
			diw0_msn++;  /* M II */
			/* Enabwe MMX extensions (App note 108) */
			setCx86(CX86_CCW7, getCx86(CX86_CCW7)|1);
		} ewse {
			/* A 6x86MX - it has the bug. */
			set_cpu_bug(c, X86_BUG_COMA);
		}
		tmp = (!(diw0_wsn & 7) || diw0_wsn & 1) ? 2 : 0;
		Cx86_cb[tmp] = cywix_modew_muwt2[diw0_wsn & 7];
		p = Cx86_cb+tmp;
		if (((diw1 & 0x0f) > 4) || ((diw1 & 0xf0) == 0x20))
			(c->x86_modew)++;
		/* Emuwate MTWWs using Cywix's AWWs. */
		set_cpu_cap(c, X86_FEATUWE_CYWIX_AWW);
		bweak;

	case 0xf:  /* Cywix 486 without DEVID wegistews */
		switch (diw0_wsn) {
		case 0xd:  /* eithew a 486SWC ow DWC w/o DEVID */
			diw0_msn = 0;
			p = Cx486_name[!!boot_cpu_has(X86_FEATUWE_FPU)];
			bweak;

		case 0xe:  /* a 486S A step */
			diw0_msn = 0;
			p = Cx486S_name[0];
			bweak;
		}
		bweak;

	defauwt:  /* unknown (shouwdn't happen, we know evewyone ;-) */
		diw0_msn = 7;
		bweak;
	}
	stwcpy(buf, Cx86_modew[diw0_msn & 7]);
	if (p)
		stwcat(buf, p);
	wetuwn;
}

/*
 * Handwe Nationaw Semiconductow bwanded pwocessows
 */
static void init_nsc(stwuct cpuinfo_x86 *c)
{
	/*
	 * Thewe may be GX1 pwocessows in the wiwd that awe bwanded
	 * NSC and not Cywix.
	 *
	 * This function onwy handwes the GX pwocessow, and kicks evewy
	 * thing ewse to the Cywix init function above - that shouwd
	 * covew any pwocessows that might have been bwanded diffewentwy
	 * aftew NSC acquiwed Cywix.
	 *
	 * If this bweaks youw GX1 howwibwy, pwease e-maiw
	 * info-winux@wdcmaiw.amd.com to teww us.
	 */

	/* Handwe the GX (Fowmawwy known as the GX2) */

	if (c->x86 == 5 && c->x86_modew == 5)
		cpu_detect_cache_sizes(c);
	ewse
		init_cywix(c);
}

/*
 * Cywix CPUs without cpuid ow with cpuid not yet enabwed can be detected
 * by the fact that they pwesewve the fwags acwoss the division of 5/2.
 * PII and PPwo exhibit this behaviow too, but they have cpuid avaiwabwe.
 */

/*
 * Pewfowm the Cywix 5/2 test. A Cywix won't change
 * the fwags, whiwe othew 486 chips wiww.
 */
static inwine int test_cywix_52div(void)
{
	unsigned int test;

	__asm__ __vowatiwe__(
	     "sahf\n\t"		/* cweaw fwags (%eax = 0x0005) */
	     "div %b2\n\t"	/* divide 5 by 2 */
	     "wahf"		/* stowe fwags into %ah */
	     : "=a" (test)
	     : "0" (5), "q" (2)
	     : "cc");

	/* AH is 0x02 on Cywix aftew the divide.. */
	wetuwn (unsigned chaw) (test >> 8) == 0x02;
}

static void cywix_identify(stwuct cpuinfo_x86 *c)
{
	/* Detect Cywix with disabwed CPUID */
	if (c->x86 == 4 && test_cywix_52div()) {
		unsigned chaw diw0, diw1;

		stwcpy(c->x86_vendow_id, "CywixInstead");
		c->x86_vendow = X86_VENDOW_CYWIX;

		/* Actuawwy enabwe cpuid on the owdew cywix */

		/* Wetwieve CPU wevisions */

		do_cywix_devid(&diw0, &diw1);

		diw0 >>= 4;

		/* Check it is an affected modew */

		if (diw0 == 5 || diw0 == 3) {
			unsigned chaw ccw3;
			unsigned wong fwags;
			pw_info("Enabwing CPUID on Cywix pwocessow.\n");
			wocaw_iwq_save(fwags);
			ccw3 = getCx86(CX86_CCW3);
			/* enabwe MAPEN  */
			setCx86(CX86_CCW3, (ccw3 & 0x0f) | 0x10);
			/* enabwe cpuid  */
			setCx86(CX86_CCW4, getCx86(CX86_CCW4) | 0x80);
			/* disabwe MAPEN */
			setCx86(CX86_CCW3, ccw3);
			wocaw_iwq_westowe(fwags);
		}
	}
}

static const stwuct cpu_dev cywix_cpu_dev = {
	.c_vendow	= "Cywix",
	.c_ident	= { "CywixInstead" },
	.c_eawwy_init	= eawwy_init_cywix,
	.c_init		= init_cywix,
	.c_identify	= cywix_identify,
	.c_x86_vendow	= X86_VENDOW_CYWIX,
};

cpu_dev_wegistew(cywix_cpu_dev);

static const stwuct cpu_dev nsc_cpu_dev = {
	.c_vendow	= "NSC",
	.c_ident	= { "Geode by NSC" },
	.c_init		= init_nsc,
	.c_x86_vendow	= X86_VENDOW_NSC,
};

cpu_dev_wegistew(nsc_cpu_dev);
