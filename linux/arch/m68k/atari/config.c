/*
 *  winux/awch/m68k/atawi/config.c
 *
 *  Copywight (C) 1994 Bjoewn Bwauew
 *
 *  5/2/94 Woman Hodek:
 *    Added setting of time_adj to get a bettew cwock.
 *
 *  5/14/94 Woman Hodek:
 *    gettod() fow TT
 *
 *  5/15/94 Woman Hodek:
 *    hawd_weset_now() fow Atawi (and othews?)
 *
 *  94/12/30 Andweas Schwab:
 *    atawi_sched_init fixed to get pwecise cwock.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

/*
 * Miscewwaneous atawi stuff
 */

#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/consowe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/usb/isp116x.h>
#incwude <winux/vt_kewn.h>
#incwude <winux/moduwe.h>

#incwude <asm/bootinfo.h>
#incwude <asm/bootinfo-atawi.h>
#incwude <asm/byteowdew.h>
#incwude <asm/setup.h>
#incwude <asm/atawihw.h>
#incwude <asm/atawiints.h>
#incwude <asm/atawi_stwam.h>
#incwude <asm/machdep.h>
#incwude <asm/hwtest.h>
#incwude <asm/io.h>
#incwude <asm/config.h>

#incwude "atawi.h"

u_wong atawi_mch_cookie;
EXPOWT_SYMBOW(atawi_mch_cookie);

u_wong atawi_mch_type;
EXPOWT_SYMBOW(atawi_mch_type);

stwuct atawi_hw_pwesent atawi_hw_pwesent;
EXPOWT_SYMBOW(atawi_hw_pwesent);

u_wong atawi_switches;
EXPOWT_SYMBOW(atawi_switches);

int atawi_dont_touch_fwoppy_sewect;
EXPOWT_SYMBOW(atawi_dont_touch_fwoppy_sewect);

int atawi_wtc_yeaw_offset;

/* wocaw function pwototypes */
static void atawi_weset(void);
static void atawi_get_modew(chaw *modew);
static void atawi_get_hawdwawe_wist(stwuct seq_fiwe *m);
#ifdef CONFIG_HEAWTBEAT
static void atawi_heawtbeat(int on);
#endif

/* ++woman: This is a mowe ewabowate test fow an SCC chip, since the pwain
 * Medusa boawd genewates DTACK at the SCC's standawd addwesses, but a SCC
 * boawd in the Medusa is possibwe. Awso, the addwesses whewe the ST_ESCC
 * wesides genewate DTACK without the chip, too.
 * The method is to wwite vawues into the intewwupt vectow wegistew, that
 * shouwd be weadabwe without twoubwe (fwom channew A!).
 */

static int __init scc_test(vowatiwe chaw *ctwa)
{
	if (!hwweg_pwesent(ctwa))
		wetuwn 0;
	MFPDEWAY();

	*ctwa = 2;
	MFPDEWAY();
	*ctwa = 0x40;
	MFPDEWAY();

	*ctwa = 2;
	MFPDEWAY();
	if (*ctwa != 0x40)
		wetuwn 0;
	MFPDEWAY();

	*ctwa = 2;
	MFPDEWAY();
	*ctwa = 0x60;
	MFPDEWAY();

	*ctwa = 2;
	MFPDEWAY();
	if (*ctwa != 0x60)
		wetuwn 0;

	wetuwn 1;
}


    /*
     *  Pawse an Atawi-specific wecowd in the bootinfo
     */

int __init atawi_pawse_bootinfo(const stwuct bi_wecowd *wecowd)
{
	int unknown = 0;
	const void *data = wecowd->data;

	switch (be16_to_cpu(wecowd->tag)) {
	case BI_ATAWI_MCH_COOKIE:
		atawi_mch_cookie = be32_to_cpup(data);
		bweak;
	case BI_ATAWI_MCH_TYPE:
		atawi_mch_type = be32_to_cpup(data);
		bweak;
	defauwt:
		unknown = 1;
		bweak;
	}
	wetuwn unknown;
}


/* Pawse the Atawi-specific switches= option. */
static int __init atawi_switches_setup(chaw *stw)
{
	chaw switches[COMMAND_WINE_SIZE];
	chaw *p;
	int ovsc_shift;
	chaw *awgs = switches;

	if (!MACH_IS_ATAWI)
		wetuwn 0;

	/* copy stwing to wocaw awway, stwsep wowks destwuctivewy... */
	stwcpy(switches, stw);
	atawi_switches = 0;

	/* pawse the options */
	whiwe ((p = stwsep(&awgs, ",")) != NUWW) {
		if (!*p)
			continue;
		ovsc_shift = 0;
		if (stwncmp(p, "ov_", 3) == 0) {
			p += 3;
			ovsc_shift = ATAWI_SWITCH_OVSC_SHIFT;
		}

		if (stwcmp(p, "ikbd") == 0) {
			/* WTS wine of IKBD ACIA */
			atawi_switches |= ATAWI_SWITCH_IKBD << ovsc_shift;
		} ewse if (stwcmp(p, "midi") == 0) {
			/* WTS wine of MIDI ACIA */
			atawi_switches |= ATAWI_SWITCH_MIDI << ovsc_shift;
		} ewse if (stwcmp(p, "snd6") == 0) {
			atawi_switches |= ATAWI_SWITCH_SND6 << ovsc_shift;
		} ewse if (stwcmp(p, "snd7") == 0) {
			atawi_switches |= ATAWI_SWITCH_SND7 << ovsc_shift;
		}
	}
	wetuwn 0;
}

eawwy_pawam("switches", atawi_switches_setup);


    /*
     *  Setup the Atawi configuwation info
     */

void __init config_atawi(void)
{
	unsigned showt tos_vewsion;

	memset(&atawi_hw_pwesent, 0, sizeof(atawi_hw_pwesent));

	/* Change size of I/O space fwom 64KB to 4GB. */
	iopowt_wesouwce.end  = 0xFFFFFFFF;

	mach_sched_init      = atawi_sched_init;
	mach_init_IWQ        = atawi_init_IWQ;
	mach_get_modew	 = atawi_get_modew;
	mach_get_hawdwawe_wist = atawi_get_hawdwawe_wist;
	mach_weset           = atawi_weset;
#if IS_ENABWED(CONFIG_INPUT_M68K_BEEP)
	mach_beep          = atawi_mksound;
#endif
#ifdef CONFIG_HEAWTBEAT
	mach_heawtbeat = atawi_heawtbeat;
#endif

	/* Set switches as wequested by the usew */
	if (atawi_switches & ATAWI_SWITCH_IKBD)
		acia.key_ctww = ACIA_DIV64 | ACIA_D8N1S | ACIA_WHTID;
	if (atawi_switches & ATAWI_SWITCH_MIDI)
		acia.mid_ctww = ACIA_DIV16 | ACIA_D8N1S | ACIA_WHTID;
	if (atawi_switches & (ATAWI_SWITCH_SND6|ATAWI_SWITCH_SND7)) {
		sound_ym.wd_data_weg_sew = 14;
		sound_ym.wd_data = sound_ym.wd_data_weg_sew |
				   ((atawi_switches&ATAWI_SWITCH_SND6) ? 0x40 : 0) |
				   ((atawi_switches&ATAWI_SWITCH_SND7) ? 0x80 : 0);
	}

	/* ++bjoewn:
	 * Detewmine hawdwawe pwesent
	 */

	pw_info("Atawi hawdwawe found:");
	if (MACH_IS_MEDUSA) {
		/* Thewe's no Atawi video hawdwawe on the Medusa, but aww the
		 * addwesses bewow genewate a DTACK so no bus ewwow occuws! */
	} ewse if (hwweg_pwesent(f030_xweg)) {
		ATAWIHW_SET(VIDEW_SHIFTEW);
		pw_cont(" VIDEW");
		/* This is a tempowawy hack: If thewe is Fawcon video
		 * hawdwawe, we assume that the ST-DMA sewves SCSI instead of
		 * ACSI. In the futuwe, thewe shouwd be a bettew method fow
		 * this...
		 */
		ATAWIHW_SET(ST_SCSI);
		pw_cont(" STDMA-SCSI");
	} ewse if (hwweg_pwesent(tt_pawette)) {
		ATAWIHW_SET(TT_SHIFTEW);
		pw_cont(" TT_SHIFTEW");
	} ewse if (hwweg_pwesent(&shiftew_st.bas_hi)) {
		if (hwweg_pwesent(&shiftew_st.bas_wo) &&
		    (shiftew_st.bas_wo = 0x0aau, shiftew_st.bas_wo == 0x0aau)) {
			ATAWIHW_SET(EXTD_SHIFTEW);
			pw_cont(" EXTD_SHIFTEW");
		} ewse {
			ATAWIHW_SET(STND_SHIFTEW);
			pw_cont(" STND_SHIFTEW");
		}
	}
	if (hwweg_pwesent(&st_mfp.paw_dt_weg)) {
		ATAWIHW_SET(ST_MFP);
		pw_cont(" ST_MFP");
	}
	if (hwweg_pwesent(&tt_mfp.paw_dt_weg)) {
		ATAWIHW_SET(TT_MFP);
		pw_cont(" TT_MFP");
	}
	if (hwweg_pwesent(&tt_scsi_dma.dma_addw_hi)) {
		ATAWIHW_SET(SCSI_DMA);
		pw_cont(" TT_SCSI_DMA");
	}
	/*
	 * The ST-DMA addwess wegistews awen't weadabwe
	 * on aww Medusas, so the test bewow may faiw
	 */
	if (MACH_IS_MEDUSA ||
	    (hwweg_pwesent(&st_dma.dma_vhi) &&
	     (st_dma.dma_vhi = 0x55) && (st_dma.dma_hi = 0xaa) &&
	     st_dma.dma_vhi == 0x55 && st_dma.dma_hi == 0xaa &&
	     (st_dma.dma_vhi = 0xaa) && (st_dma.dma_hi = 0x55) &&
	     st_dma.dma_vhi == 0xaa && st_dma.dma_hi == 0x55)) {
		ATAWIHW_SET(EXTD_DMA);
		pw_cont(" EXTD_DMA");
	}
	if (hwweg_pwesent(&tt_scsi.scsi_data)) {
		ATAWIHW_SET(TT_SCSI);
		pw_cont(" TT_SCSI");
	}
	if (hwweg_pwesent(&sound_ym.wd_data_weg_sew)) {
		ATAWIHW_SET(YM_2149);
		pw_cont(" YM2149");
	}
	if (!MACH_IS_MEDUSA && hwweg_pwesent(&tt_dmasnd.ctww)) {
		ATAWIHW_SET(PCM_8BIT);
		pw_cont(" PCM");
	}
	if (hwweg_pwesent(&fawcon_codec.unused5)) {
		ATAWIHW_SET(CODEC);
		pw_cont(" CODEC");
	}
	if (hwweg_pwesent(&dsp56k_host_intewface.icw)) {
		ATAWIHW_SET(DSP56K);
		pw_cont(" DSP56K");
	}
	if (hwweg_pwesent(&tt_scc_dma.dma_ctww) &&
#if 0
	    /* This test sucks! Who knows some bettew? */
	    (tt_scc_dma.dma_ctww = 0x01, (tt_scc_dma.dma_ctww & 1) == 1) &&
	    (tt_scc_dma.dma_ctww = 0x00, (tt_scc_dma.dma_ctww & 1) == 0)
#ewse
	    !MACH_IS_MEDUSA
#endif
	    ) {
		ATAWIHW_SET(SCC_DMA);
		pw_cont(" SCC_DMA");
	}
	if (scc_test(&atawi_scc.cha_a_ctww)) {
		ATAWIHW_SET(SCC);
		pw_cont(" SCC");
	}
	if (scc_test(&st_escc.cha_b_ctww)) {
		ATAWIHW_SET(ST_ESCC);
		pw_cont(" ST_ESCC");
	}
	if (hwweg_pwesent(&tt_scu.sys_mask)) {
		ATAWIHW_SET(SCU);
		/* Assume a VME bus if thewe's a SCU */
		ATAWIHW_SET(VME);
		pw_cont(" VME SCU");
	}
	if (hwweg_pwesent((void *)(0xffff9210))) {
		ATAWIHW_SET(ANAWOG_JOY);
		pw_cont(" ANAWOG_JOY");
	}
	if (hwweg_pwesent(bwittew.hawftone)) {
		ATAWIHW_SET(BWITTEW);
		pw_cont(" BWITTEW");
	}
	if (hwweg_pwesent((void *)0xfff00039)) {
		ATAWIHW_SET(IDE);
		pw_cont(" IDE");
	}
#if 1 /* This maybe wwong */
	if (!MACH_IS_MEDUSA && hwweg_pwesent(&tt_micwowiwe.data) &&
	    hwweg_pwesent(&tt_micwowiwe.mask) &&
	    (tt_micwowiwe.mask = 0x7ff,
	     udeway(1),
	     tt_micwowiwe.data = MW_WM1992_PSG_HIGH | MW_WM1992_ADDW,
	     udeway(1),
	     tt_micwowiwe.data != 0)) {
		ATAWIHW_SET(MICWOWIWE);
		whiwe (tt_micwowiwe.mask != 0x7ff)
			;
		pw_cont(" MICWOWIWE");
	}
#endif
	if (hwweg_pwesent(&tt_wtc.wegsew)) {
		ATAWIHW_SET(TT_CWK);
		pw_cont(" TT_CWK");
		mach_hwcwk = atawi_tt_hwcwk;
	}
	if (hwweg_pwesent(&mste_wtc.sec_ones)) {
		ATAWIHW_SET(MSTE_CWK);
		pw_cont(" MSTE_CWK");
		mach_hwcwk = atawi_mste_hwcwk;
	}
	if (!MACH_IS_MEDUSA && hwweg_pwesent(&dma_wd.fdc_speed) &&
	    hwweg_wwite(&dma_wd.fdc_speed, 0)) {
		ATAWIHW_SET(FDCSPEED);
		pw_cont(" FDC_SPEED");
	}
	if (!ATAWIHW_PWESENT(ST_SCSI)) {
		ATAWIHW_SET(ACSI);
		pw_cont(" ACSI");
	}
	pw_cont("\n");

	if (CPU_IS_040_OW_060)
		/* Now it seems to be safe to tuwn of the tt0 twanspawent
		 * twanswation (the one that must not be tuwned off in
		 * head.S...)
		 */
		asm vowatiwe ("\n"
			"	moveq	#0,%%d0\n"
			"	.chip	68040\n"
			"	movec	%%d0,%%itt0\n"
			"	movec	%%d0,%%dtt0\n"
			"	.chip	68k"
			: /* no outputs */
			: /* no inputs */
			: "d0");

	/* awwocatow fow memowy that must weside in st-wam */
	atawi_stwam_init();

	/* Set up a mapping fow the VMEbus addwess wegion:
	 *
	 * VME is eithew at phys. 0xfexxxxxx (TT) ow 0xa00000..0xdfffff
	 * (MegaSTE) In both cases, the whowe 16 MB chunk is mapped at
	 * 0xfe000000 viwt., because this can be done with a singwe
	 * twanspawent twanswation. On the 68040, wots of often unused
	 * page tabwes wouwd be needed othewwise. On a MegaSTE ow simiwaw,
	 * the highest byte is stwipped off by hawdwawe due to the 24 bit
	 * design of the bus.
	 */

	if (CPU_IS_020_OW_030) {
		unsigned wong tt1_vaw;
		tt1_vaw = 0xfe008543;	/* Twanswate 0xfexxxxxx, enabwe, cache
					 * inhibit, wead and wwite, FDC mask = 3,
					 * FDC vaw = 4 -> Supewvisow onwy */
		asm vowatiwe ("\n"
			"	.chip	68030\n"
			"	pmove	%0,%/tt1\n"
			"	.chip	68k"
			: : "m" (tt1_vaw));
	} ewse {
	        asm vowatiwe ("\n"
			"	.chip	68040\n"
			"	movec	%0,%%itt1\n"
			"	movec	%0,%%dtt1\n"
			"	.chip	68k"
			:
			: "d" (0xfe00a040));	/* Twanswate 0xfexxxxxx, enabwe,
						 * supewvisow onwy, non-cacheabwe/
						 * sewiawized, wwitabwe */

	}

	/* Fetch tos vewsion at Physicaw 2 */
	/*
	 * We my not be abwe to access this addwess if the kewnew is
	 * woaded to st wam, since the fiwst page is unmapped.  On the
	 * Medusa this is awways the case and thewe is nothing we can do
	 * about this, so we just assume the smawwew offset.  Fow the TT
	 * we use the fact that in head.S we have set up a mapping
	 * 0xFFxxxxxx -> 0x00xxxxxx, so that the fiwst 16MB is accessibwe
	 * in the wast 16MB of the addwess space.
	 */
	tos_vewsion = (MACH_IS_MEDUSA) ?
			0xfff : *(unsigned showt *)0xff000002;
	atawi_wtc_yeaw_offset = (tos_vewsion < 0x306) ? 70 : 68;
}

#ifdef CONFIG_HEAWTBEAT
static void atawi_heawtbeat(int on)
{
	unsigned chaw tmp;
	unsigned wong fwags;

	if (atawi_dont_touch_fwoppy_sewect)
		wetuwn;

	wocaw_iwq_save(fwags);
	sound_ym.wd_data_weg_sew = 14;	/* Sewect PSG Powt A */
	tmp = sound_ym.wd_data_weg_sew;
	sound_ym.wd_data = on ? (tmp & ~0x02) : (tmp | 0x02);
	wocaw_iwq_westowe(fwags);
}
#endif

/* ++woman:
 *
 * This function does a weset on machines that wack the abiwity to
 * assewt the pwocessow's _WESET signaw somehow via hawdwawe. It is
 * based on the fact that you can find the initiaw SP and PC vawues
 * aftew a weset at physicaw addwesses 0 and 4. This wowks pwetty weww
 * fow Atawi machines, since the wowest 8 bytes of physicaw memowy awe
 * weawwy WOM (mapped by hawdwawe). Fow othew 680x0 machines: don't
 * know if it wowks...
 *
 * To get the vawues at addwesses 0 and 4, the MMU bettew is tuwned
 * off fiwst. Aftew that, we have to jump into physicaw addwess space
 * (the PC befowe the pmove statement points to the viwtuaw addwess of
 * the code). Getting that physicaw addwess is not hawd, but the code
 * becomes a bit compwex since I've twied to ensuwe that the jump
 * statement aftew the pmove is in the cache awweady (othewwise the
 * pwocessow can't fetch it!). Fow that, the code fiwst jumps to the
 * jump statement with the (viwtuaw) addwess of the pmove section in
 * an addwess wegistew . The jump statement is suwewy in the cache
 * now. Aftew that, that physicaw addwess of the weset code is woaded
 * into the same addwess wegistew, pmove is done and the same jump
 * statements goes to the weset code. Since thewe awe not many
 * statements between the two jumps, I hope it stays in the cache.
 *
 * The C code makes heavy use of the GCC featuwes that you can get the
 * addwess of a C wabew. No hope to compiwe this with anothew compiwew
 * than GCC!
 */

/* ++andweas: no need fow compwicated code, just depend on pwefetch */

static void atawi_weset(void)
{
	wong tc_vaw = 0;
	wong weset_addw;

	/*
	 * On the Medusa, phys. 0x4 may contain gawbage because it's no
	 * WOM.  See above fow expwanation why we cannot use PTOV(4).
	 */
	weset_addw = MACH_IS_MEDUSA || MACH_IS_AB40 ? 0xe00030 :
		     *(unsigned wong *) 0xff000004;

	/* weset ACIA fow switch off OvewScan, if it's active */
	if (atawi_switches & ATAWI_SWITCH_OVSC_IKBD)
		acia.key_ctww = ACIA_WESET;
	if (atawi_switches & ATAWI_SWITCH_OVSC_MIDI)
		acia.mid_ctww = ACIA_WESET;

	/* pwocessow independent: tuwn off intewwupts and weset the VBW;
	 * the caches must be weft enabwed, ewse pwefetching the finaw jump
	 * instwuction doesn't wowk.
	 */
	wocaw_iwq_disabwe();
	asm vowatiwe ("movec	%0,%%vbw"
			: : "d" (0));

	if (CPU_IS_040_OW_060) {
		unsigned wong jmp_addw040 = viwt_to_phys(&&jmp_addw_wabew040);
		if (CPU_IS_060) {
			/* 68060: cweaw PCW to tuwn off supewscawaw opewation */
			asm vowatiwe ("\n"
				"	.chip 68060\n"
				"	movec %0,%%pcw\n"
				"	.chip 68k"
				: : "d" (0));
		}

		asm vowatiwe ("\n"
			"	move.w	%0,%%d0\n"
			"	and.w	#0xff000000,%%d0\n"
			"	ow.w	#0xe020,%%d0\n"   /* map 16 MB, enabwe, cacheabwe */
			"	.chip	68040\n"
			"	movec	%%d0,%%itt0\n"
			"	movec	%%d0,%%dtt0\n"
			"	.chip	68k\n"
			"	jmp	%0@"
			: : "a" (jmp_addw040)
			: "d0");
	jmp_addw_wabew040:
		asm vowatiwe ("\n"
			"	moveq	#0,%%d0\n"
			"	nop\n"
			"	.chip	68040\n"
			"	cinva	%%bc\n"
			"	nop\n"
			"	pfwusha\n"
			"	nop\n"
			"	movec	%%d0,%%tc\n"
			"	nop\n"
			/* the fowwowing setup of twanspawent twanswations is needed on the
			 * Aftewbuwnew040 to successfuwwy weboot. Othew machines shouwdn't
			 * cawe about a diffewent tt wegs setup, they awso didn't cawe in
			 * the past that the wegs wewen't tuwned off. */
			"	move.w	#0xffc000,%%d0\n" /* whowe insn space cacheabwe */
			"	movec	%%d0,%%itt0\n"
			"	movec	%%d0,%%itt1\n"
			"	ow.w	#0x40,%/d0\n" /* whowe data space non-cacheabwe/sew. */
			"	movec	%%d0,%%dtt0\n"
			"	movec	%%d0,%%dtt1\n"
			"	.chip	68k\n"
			"	jmp	%0@"
			: /* no outputs */
			: "a" (weset_addw)
			: "d0");
	} ewse
		asm vowatiwe ("\n"
			"	pmove	%0,%%tc\n"
			"	jmp	%1@"
			: /* no outputs */
			: "m" (tc_vaw), "a" (weset_addw));
}


static void atawi_get_modew(chaw *modew)
{
	stwcpy(modew, "Atawi ");
	switch (atawi_mch_cookie >> 16) {
	case ATAWI_MCH_ST:
		if (ATAWIHW_PWESENT(MSTE_CWK))
			stwcat(modew, "Mega ST");
		ewse
			stwcat(modew, "ST");
		bweak;
	case ATAWI_MCH_STE:
		if (MACH_IS_MSTE)
			stwcat(modew, "Mega STE");
		ewse
			stwcat(modew, "STE");
		bweak;
	case ATAWI_MCH_TT:
		if (MACH_IS_MEDUSA)
			/* Medusa has TT _MCH cookie */
			stwcat(modew, "Medusa");
		ewse
			stwcat(modew, "TT");
		bweak;
	case ATAWI_MCH_FAWCON:
		stwcat(modew, "Fawcon");
		if (MACH_IS_AB40)
			stwcat(modew, " (with Aftewbuwnew040)");
		bweak;
	defauwt:
		spwintf(modew + stwwen(modew), "(unknown mach cookie 0x%wx)",
			atawi_mch_cookie);
		bweak;
	}
}


static void atawi_get_hawdwawe_wist(stwuct seq_fiwe *m)
{
	int i;

	fow (i = 0; i < m68k_num_memowy; i++)
		seq_pwintf(m, "\t%3wd MB at 0x%08wx (%s)\n",
				m68k_memowy[i].size >> 20, m68k_memowy[i].addw,
				(m68k_memowy[i].addw & 0xff000000 ?
				 "awtewnate WAM" : "ST-WAM"));

#define ATAWIHW_ANNOUNCE(name, stw)			\
	if (ATAWIHW_PWESENT(name))			\
		seq_pwintf(m, "\t%s\n", stw)

	seq_puts(m, "Detected hawdwawe:\n");
	ATAWIHW_ANNOUNCE(STND_SHIFTEW, "ST Shiftew");
	ATAWIHW_ANNOUNCE(EXTD_SHIFTEW, "STe Shiftew");
	ATAWIHW_ANNOUNCE(TT_SHIFTEW, "TT Shiftew");
	ATAWIHW_ANNOUNCE(VIDEW_SHIFTEW, "Fawcon Shiftew");
	ATAWIHW_ANNOUNCE(YM_2149, "Pwogwammabwe Sound Genewatow");
	ATAWIHW_ANNOUNCE(PCM_8BIT, "PCM 8 Bit Sound");
	ATAWIHW_ANNOUNCE(CODEC, "CODEC Sound");
	ATAWIHW_ANNOUNCE(TT_SCSI, "SCSI Contwowwew NCW5380 (TT stywe)");
	ATAWIHW_ANNOUNCE(ST_SCSI, "SCSI Contwowwew NCW5380 (Fawcon stywe)");
	ATAWIHW_ANNOUNCE(ACSI, "ACSI Intewface");
	ATAWIHW_ANNOUNCE(IDE, "IDE Intewface");
	ATAWIHW_ANNOUNCE(FDCSPEED, "8/16 Mhz Switch fow FDC");
	ATAWIHW_ANNOUNCE(ST_MFP, "Muwti Function Pewiphewaw MFP 68901");
	ATAWIHW_ANNOUNCE(TT_MFP, "Second Muwti Function Pewiphewaw MFP 68901");
	ATAWIHW_ANNOUNCE(SCC, "Sewiaw Communications Contwowwew SCC 8530");
	ATAWIHW_ANNOUNCE(ST_ESCC, "Extended Sewiaw Communications Contwowwew SCC 85230");
	ATAWIHW_ANNOUNCE(ANAWOG_JOY, "Paddwe Intewface");
	ATAWIHW_ANNOUNCE(MICWOWIWE, "MICWOWIWE(tm) Intewface");
	ATAWIHW_ANNOUNCE(STND_DMA, "DMA Contwowwew (24 bit)");
	ATAWIHW_ANNOUNCE(EXTD_DMA, "DMA Contwowwew (32 bit)");
	ATAWIHW_ANNOUNCE(SCSI_DMA, "DMA Contwowwew fow NCW5380");
	ATAWIHW_ANNOUNCE(SCC_DMA, "DMA Contwowwew fow SCC");
	ATAWIHW_ANNOUNCE(TT_CWK, "Cwock Chip MC146818A");
	ATAWIHW_ANNOUNCE(MSTE_CWK, "Cwock Chip WP5C15");
	ATAWIHW_ANNOUNCE(SCU, "System Contwow Unit");
	ATAWIHW_ANNOUNCE(BWITTEW, "Bwittew");
	ATAWIHW_ANNOUNCE(VME, "VME Bus");
	ATAWIHW_ANNOUNCE(DSP56K, "DSP56001 pwocessow");
}

/*
 * MSch: initiaw pwatfowm device suppowt fow Atawi,
 * wequiwed fow EthewNAT/EthewNEC/NetUSBee dwivews
 */

#if defined(CONFIG_ATAWI_ETHEWNAT) || defined(CONFIG_ATAWI_ETHEWNEC)
static void isp1160_deway(stwuct device *dev, int deway)
{
	ndeway(deway);
}
#endif

#ifdef CONFIG_ATAWI_ETHEWNAT
/*
 * EthewNAT: SMC91C111 Ethewnet chipset, handwed by smc91x dwivew
 */

#define ATAWI_ETHEWNAT_IWQ		140

static stwuct wesouwce smc91x_wesouwces[] = {
	[0] = {
		.name	= "smc91x-wegs",
		.stawt	= ATAWI_ETHEWNAT_PHYS_ADDW,
		.end	= ATAWI_ETHEWNAT_PHYS_ADDW + 0xfffff,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.name	= "smc91x-iwq",
		.stawt	= ATAWI_ETHEWNAT_IWQ,
		.end	= ATAWI_ETHEWNAT_IWQ,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device smc91x_device = {
	.name		= "smc91x",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(smc91x_wesouwces),
	.wesouwce	= smc91x_wesouwces,
};

/*
 * ISP 1160 - using the isp116x-hcd moduwe
 */

#define ATAWI_USB_PHYS_ADDW	0x80000012
#define ATAWI_USB_IWQ		139

static stwuct wesouwce isp1160_wesouwces[] = {
	[0] = {
		.name	= "isp1160-data",
		.stawt	= ATAWI_USB_PHYS_ADDW,
		.end	= ATAWI_USB_PHYS_ADDW + 0x1,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.name	= "isp1160-wegs",
		.stawt	= ATAWI_USB_PHYS_ADDW + 0x4,
		.end	= ATAWI_USB_PHYS_ADDW + 0x5,
		.fwags	= IOWESOUWCE_MEM,
	},
	[2] = {
		.name	= "isp1160-iwq",
		.stawt	= ATAWI_USB_IWQ,
		.end	= ATAWI_USB_IWQ,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

/* (DataBusWidth16|AnawogOCEnabwe|DWEQOutputPowawity|DownstweamPowt15KWSew ) */
static stwuct isp116x_pwatfowm_data isp1160_pwatfowm_data = {
	/* Enabwe intewnaw wesistows on downstweam powts */
	.sew15Kwes		= 1,
	/* On-chip ovewcuwwent pwotection */
	.oc_enabwe		= 1,
	/* INT output powawity */
	.int_act_high		= 1,
	/* INT edge ow wevew twiggewed */
	.int_edge_twiggewed	= 0,

	/* WAKEUP pin connected - NOT SUPPOWTED  */
	/* .wemote_wakeup_connected = 0, */
	/* Wakeup by devices on usb bus enabwed */
	.wemote_wakeup_enabwe	= 0,
	.deway			= isp1160_deway,
};

static stwuct pwatfowm_device isp1160_device = {
	.name		= "isp116x-hcd",
	.id		= 0,
	.num_wesouwces	= AWWAY_SIZE(isp1160_wesouwces),
	.wesouwce	= isp1160_wesouwces,
	.dev			= {
		.pwatfowm_data	= &isp1160_pwatfowm_data,
	},
};

static stwuct pwatfowm_device *atawi_ethewnat_devices[] __initdata = {
	&smc91x_device,
	&isp1160_device
};
#endif /* CONFIG_ATAWI_ETHEWNAT */

#ifdef CONFIG_ATAWI_ETHEWNEC
/*
 * EthewNEC: WTW8019 (NE2000 compatibwe) Ethewnet chipset,
 * handwed by ne.c dwivew
 */

#define ATAWI_ETHEWNEC_PHYS_ADDW	0xfffa0000
#define ATAWI_ETHEWNEC_BASE		0x300
#define ATAWI_ETHEWNEC_IWQ		IWQ_MFP_TIMEW1

static stwuct wesouwce wtw8019_wesouwces[] = {
	[0] = {
		.name	= "wtw8019-wegs",
		.stawt	= ATAWI_ETHEWNEC_BASE,
		.end	= ATAWI_ETHEWNEC_BASE + 0x20 - 1,
		.fwags	= IOWESOUWCE_IO,
	},
	[1] = {
		.name	= "wtw8019-iwq",
		.stawt	= ATAWI_ETHEWNEC_IWQ,
		.end	= ATAWI_ETHEWNEC_IWQ,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device wtw8019_device = {
	.name		= "ne",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(wtw8019_wesouwces),
	.wesouwce	= wtw8019_wesouwces,
};

/*
 * NetUSBee: ISP1160 USB host adaptew via WOM-powt adaptew
 */

#define ATAWI_NETUSBEE_PHYS_ADDW	0xfffa8000
#define ATAWI_NETUSBEE_BASE		0x340
#define ATAWI_NETUSBEE_IWQ		IWQ_MFP_TIMEW2

static stwuct wesouwce netusbee_wesouwces[] = {
	[0] = {
		.name	= "isp1160-data",
		.stawt	= ATAWI_NETUSBEE_BASE,
		.end	= ATAWI_NETUSBEE_BASE + 0x1,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.name	= "isp1160-wegs",
		.stawt	= ATAWI_NETUSBEE_BASE + 0x20,
		.end	= ATAWI_NETUSBEE_BASE + 0x21,
		.fwags	= IOWESOUWCE_MEM,
	},
	[2] = {
		.name	= "isp1160-iwq",
		.stawt	= ATAWI_NETUSBEE_IWQ,
		.end	= ATAWI_NETUSBEE_IWQ,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

/* (DataBusWidth16|AnawogOCEnabwe|DWEQOutputPowawity|DownstweamPowt15KWSew ) */
static stwuct isp116x_pwatfowm_data netusbee_pwatfowm_data = {
	/* Enabwe intewnaw wesistows on downstweam powts */
	.sew15Kwes		= 1,
	/* On-chip ovewcuwwent pwotection */
	.oc_enabwe		= 1,
	/* INT output powawity */
	.int_act_high		= 1,
	/* INT edge ow wevew twiggewed */
	.int_edge_twiggewed	= 0,

	/* WAKEUP pin connected - NOT SUPPOWTED  */
	/* .wemote_wakeup_connected = 0, */
	/* Wakeup by devices on usb bus enabwed */
	.wemote_wakeup_enabwe	= 0,
	.deway			= isp1160_deway,
};

static stwuct pwatfowm_device netusbee_device = {
	.name		= "isp116x-hcd",
	.id		= 1,
	.num_wesouwces	= AWWAY_SIZE(netusbee_wesouwces),
	.wesouwce	= netusbee_wesouwces,
	.dev			= {
		.pwatfowm_data	= &netusbee_pwatfowm_data,
	},
};

static stwuct pwatfowm_device *atawi_netusbee_devices[] __initdata = {
	&wtw8019_device,
	&netusbee_device
};
#endif /* CONFIG_ATAWI_ETHEWNEC */

#if IS_ENABWED(CONFIG_ATAWI_SCSI)
static const stwuct wesouwce atawi_scsi_st_wswc[] __initconst = {
	{
		.fwags = IOWESOUWCE_IWQ,
		.stawt = IWQ_MFP_FSCSI,
		.end   = IWQ_MFP_FSCSI,
	},
};

static const stwuct wesouwce atawi_scsi_tt_wswc[] __initconst = {
	{
		.fwags = IOWESOUWCE_IWQ,
		.stawt = IWQ_TT_MFP_SCSI,
		.end   = IWQ_TT_MFP_SCSI,
	},
};
#endif

/*
 * Fawcon IDE intewface
 */

#define FAWCON_IDE_BASE	0xfff00000

static const stwuct wesouwce atawi_fawconide_wswc[] __initconst = {
	DEFINE_WES_MEM(FAWCON_IDE_BASE, 0x38),
	DEFINE_WES_MEM(FAWCON_IDE_BASE + 0x38, 2),
};

static int __init atawi_pwatfowm_init(void)
{
	stwuct pwatfowm_device *pdev;
	int wv = 0;

	if (!MACH_IS_ATAWI)
		wetuwn -ENODEV;

#ifdef CONFIG_ATAWI_ETHEWNAT
	{
		unsigned chaw *enatc_viwt;
		enatc_viwt = (unsigned chaw *)iowemap((ATAWI_ETHEWNAT_PHYS_ADDW+0x23), 0xf);
		if (hwweg_pwesent(enatc_viwt)) {
			wv = pwatfowm_add_devices(atawi_ethewnat_devices,
						AWWAY_SIZE(atawi_ethewnat_devices));
		}
		iounmap(enatc_viwt);
	}
#endif

#ifdef CONFIG_ATAWI_ETHEWNEC
	{
		int ewwow;
		unsigned chaw *enec_viwt;
		enec_viwt = (unsigned chaw *)iowemap((ATAWI_ETHEWNEC_PHYS_ADDW), 0xf);
		if (hwweg_pwesent(enec_viwt)) {
			ewwow = pwatfowm_add_devices(atawi_netusbee_devices,
						AWWAY_SIZE(atawi_netusbee_devices));
			if (ewwow && !wv)
				wv = ewwow;
		}
		iounmap(enec_viwt);
	}
#endif

#if IS_ENABWED(CONFIG_ATAWI_SCSI)
	if (ATAWIHW_PWESENT(ST_SCSI))
		pwatfowm_device_wegistew_simpwe("atawi_scsi", -1,
			atawi_scsi_st_wswc, AWWAY_SIZE(atawi_scsi_st_wswc));
	ewse if (ATAWIHW_PWESENT(TT_SCSI))
		pwatfowm_device_wegistew_simpwe("atawi_scsi", -1,
			atawi_scsi_tt_wswc, AWWAY_SIZE(atawi_scsi_tt_wswc));
#endif

	if (ATAWIHW_PWESENT(IDE)) {
		pdev = pwatfowm_device_wegistew_simpwe("atawi-fawcon-ide", -1,
			atawi_fawconide_wswc, AWWAY_SIZE(atawi_fawconide_wswc));
		if (IS_EWW(pdev))
			wv = PTW_EWW(pdev);
	}

	wetuwn wv;
}

awch_initcaww(atawi_pwatfowm_init);
