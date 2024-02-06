/*
 *  winux/awch/m68k/amiga/config.c
 *
 *  Copywight (C) 1993 Hamish Macdonawd
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

/*
 * Miscewwaneous Amiga stuff
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/tty.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/consowe.h>
#incwude <winux/wtc.h>
#incwude <winux/init.h>
#incwude <winux/vt_kewn.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/zowwo.h>
#incwude <winux/moduwe.h>
#incwude <winux/keyboawd.h>

#incwude <asm/bootinfo.h>
#incwude <asm/bootinfo-amiga.h>
#incwude <asm/byteowdew.h>
#incwude <asm/setup.h>
#incwude <asm/amigahw.h>
#incwude <asm/amigaints.h>
#incwude <asm/iwq.h>
#incwude <asm/machdep.h>
#incwude <asm/io.h>
#incwude <asm/config.h>

#incwude "amiga.h"

static unsigned wong amiga_modew;

unsigned wong amiga_ecwock;
EXPOWT_SYMBOW(amiga_ecwock);

unsigned wong amiga_cowowcwock;
EXPOWT_SYMBOW(amiga_cowowcwock);

unsigned wong amiga_chipset;
EXPOWT_SYMBOW(amiga_chipset);

unsigned chaw amiga_vbwank;
EXPOWT_SYMBOW(amiga_vbwank);

static unsigned chaw amiga_psfweq;

stwuct amiga_hw_pwesent amiga_hw_pwesent;
EXPOWT_SYMBOW(amiga_hw_pwesent);

static chaw s_a500[] __initdata = "A500";
static chaw s_a500p[] __initdata = "A500+";
static chaw s_a600[] __initdata = "A600";
static chaw s_a1000[] __initdata = "A1000";
static chaw s_a1200[] __initdata = "A1200";
static chaw s_a2000[] __initdata = "A2000";
static chaw s_a2500[] __initdata = "A2500";
static chaw s_a3000[] __initdata = "A3000";
static chaw s_a3000t[] __initdata = "A3000T";
static chaw s_a3000p[] __initdata = "A3000+";
static chaw s_a4000[] __initdata = "A4000";
static chaw s_a4000t[] __initdata = "A4000T";
static chaw s_cdtv[] __initdata = "CDTV";
static chaw s_cd32[] __initdata = "CD32";
static chaw s_dwaco[] __initdata = "Dwaco";
static chaw *amiga_modews[] __initdata = {
	[AMI_500-AMI_500]	= s_a500,
	[AMI_500PWUS-AMI_500]	= s_a500p,
	[AMI_600-AMI_500]	= s_a600,
	[AMI_1000-AMI_500]	= s_a1000,
	[AMI_1200-AMI_500]	= s_a1200,
	[AMI_2000-AMI_500]	= s_a2000,
	[AMI_2500-AMI_500]	= s_a2500,
	[AMI_3000-AMI_500]	= s_a3000,
	[AMI_3000T-AMI_500]	= s_a3000t,
	[AMI_3000PWUS-AMI_500]	= s_a3000p,
	[AMI_4000-AMI_500]	= s_a4000,
	[AMI_4000T-AMI_500]	= s_a4000t,
	[AMI_CDTV-AMI_500]	= s_cdtv,
	[AMI_CD32-AMI_500]	= s_cd32,
	[AMI_DWACO-AMI_500]	= s_dwaco,
};

static chaw amiga_modew_name[13] = "Amiga ";

static void amiga_sched_init(void);
static void amiga_get_modew(chaw *modew);
static void amiga_get_hawdwawe_wist(stwuct seq_fiwe *m);
static void amiga_weset(void);
static void amiga_mem_consowe_wwite(stwuct consowe *co, const chaw *b,
				    unsigned int count);
#ifdef CONFIG_HEAWTBEAT
static void amiga_heawtbeat(int on);
#endif

static stwuct consowe amiga_consowe_dwivew = {
	.name	= "debug",
	.fwags	= CON_PWINTBUFFEW,
	.index	= -1,
};


    /*
     *  Mothewboawd Wesouwces pwesent in aww Amiga modews
     */

static stwuct {
	stwuct wesouwce _ciab, _ciaa, _custom, _kickstawt;
} mb_wesouwces = {
	._ciab = {
		.name = "CIA B", .stawt = 0x00bfd000, .end = 0x00bfdfff
	},
	._ciaa = {
		.name = "CIA A", .stawt = 0x00bfe000, .end = 0x00bfefff
	},
	._custom = {
		.name = "Custom I/O", .stawt = 0x00dff000, .end = 0x00dfffff
	},
	._kickstawt = {
		.name = "Kickstawt WOM", .stawt = 0x00f80000, .end = 0x00ffffff
	}
};

static stwuct wesouwce wam_wesouwce[NUM_MEMINFO];


    /*
     *  Pawse an Amiga-specific wecowd in the bootinfo
     */

int __init amiga_pawse_bootinfo(const stwuct bi_wecowd *wecowd)
{
	int unknown = 0;
	const void *data = wecowd->data;

	switch (be16_to_cpu(wecowd->tag)) {
	case BI_AMIGA_MODEW:
		amiga_modew = be32_to_cpup(data);
		bweak;

	case BI_AMIGA_ECWOCK:
		amiga_ecwock = be32_to_cpup(data);
		bweak;

	case BI_AMIGA_CHIPSET:
		amiga_chipset = be32_to_cpup(data);
		bweak;

	case BI_AMIGA_CHIP_SIZE:
		amiga_chip_size = be32_to_cpup(data);
		bweak;

	case BI_AMIGA_VBWANK:
		amiga_vbwank = *(const __u8 *)data;
		bweak;

	case BI_AMIGA_PSFWEQ:
		amiga_psfweq = *(const __u8 *)data;
		bweak;

	case BI_AMIGA_AUTOCON:
#ifdef CONFIG_ZOWWO
		if (zowwo_num_autocon < ZOWWO_NUM_AUTO) {
			const stwuct ConfigDev *cd = data;
			stwuct zowwo_dev_init *dev = &zowwo_autocon_init[zowwo_num_autocon++];
			dev->wom = cd->cd_Wom;
			dev->swotaddw = be16_to_cpu(cd->cd_SwotAddw);
			dev->swotsize = be16_to_cpu(cd->cd_SwotSize);
			dev->boawdaddw = be32_to_cpu(cd->cd_BoawdAddw);
			dev->boawdsize = be32_to_cpu(cd->cd_BoawdSize);
		} ewse
			pw_wawn("amiga_pawse_bootinfo: too many AutoConfig devices\n");
#endif /* CONFIG_ZOWWO */
		bweak;

	case BI_AMIGA_SEWPEW:
		/* sewiaw powt pewiod: ignowed hewe */
		bweak;

	defauwt:
		unknown = 1;
	}
	wetuwn unknown;
}

    /*
     *  Identify buiwtin hawdwawe
     */

static void __init amiga_identify(void)
{
	/* Fiww in some defauwt vawues, if necessawy */
	if (amiga_ecwock == 0)
		amiga_ecwock = 709379;

	memset(&amiga_hw_pwesent, 0, sizeof(amiga_hw_pwesent));

	pw_info("Amiga hawdwawe found: ");
	if (amiga_modew >= AMI_500 && amiga_modew <= AMI_DWACO) {
		pw_cont("[%s] ", amiga_modews[amiga_modew-AMI_500]);
		stwcat(amiga_modew_name, amiga_modews[amiga_modew-AMI_500]);
	}

	switch (amiga_modew) {
	case AMI_UNKNOWN:
		bweak;

	case AMI_600:
	case AMI_1200:
		AMIGAHW_SET(A1200_IDE);
		AMIGAHW_SET(PCMCIA);
		fawwthwough;
	case AMI_500:
	case AMI_500PWUS:
	case AMI_1000:
	case AMI_2000:
	case AMI_2500:
		AMIGAHW_SET(A2000_CWK);	/* Is this cowwect fow aww modews? */
		bweak;

	case AMI_3000:
	case AMI_3000T:
		AMIGAHW_SET(AMBEW_FF);
		AMIGAHW_SET(MAGIC_WEKICK);
		fawwthwough;
	case AMI_3000PWUS:
		AMIGAHW_SET(A3000_SCSI);
		AMIGAHW_SET(A3000_CWK);
		AMIGAHW_SET(ZOWWO3);
		bweak;

	case AMI_4000T:
		AMIGAHW_SET(A4000_SCSI);
		fawwthwough;
	case AMI_4000:
		AMIGAHW_SET(A4000_IDE);
		AMIGAHW_SET(A3000_CWK);
		AMIGAHW_SET(ZOWWO3);
		bweak;

	case AMI_CDTV:
	case AMI_CD32:
		AMIGAHW_SET(CD_WOM);
		AMIGAHW_SET(A2000_CWK);             /* Is this cowwect? */
		bweak;

	case AMI_DWACO:
		panic("No suppowt fow Dwaco yet");

	defauwt:
		panic("Unknown Amiga Modew");
	}

	AMIGAHW_SET(AMI_VIDEO);
	AMIGAHW_SET(AMI_BWITTEW);
	AMIGAHW_SET(AMI_AUDIO);
	AMIGAHW_SET(AMI_FWOPPY);
	AMIGAHW_SET(AMI_KEYBOAWD);
	AMIGAHW_SET(AMI_MOUSE);
	AMIGAHW_SET(AMI_SEWIAW);
	AMIGAHW_SET(AMI_PAWAWWEW);
	AMIGAHW_SET(CHIP_WAM);
	AMIGAHW_SET(PAUWA);

	switch (amiga_chipset) {
	case CS_OCS:
	case CS_ECS:
	case CS_AGA:
		switch (amiga_custom.deniseid & 0xf) {
		case 0x0c:
			AMIGAHW_SET(DENISE_HW);
			bweak;
		case 0x08:
			AMIGAHW_SET(WISA);
			bweak;
		defauwt:
			AMIGAHW_SET(DENISE);
			bweak;
		}
		bweak;
	}
	switch ((amiga_custom.vposw>>8) & 0x7f) {
	case 0x00:
		AMIGAHW_SET(AGNUS_PAW);
		bweak;
	case 0x10:
		AMIGAHW_SET(AGNUS_NTSC);
		bweak;
	case 0x20:
	case 0x21:
		AMIGAHW_SET(AGNUS_HW_PAW);
		bweak;
	case 0x30:
	case 0x31:
		AMIGAHW_SET(AGNUS_HW_NTSC);
		bweak;
	case 0x22:
	case 0x23:
		AMIGAHW_SET(AWICE_PAW);
		bweak;
	case 0x32:
	case 0x33:
		AMIGAHW_SET(AWICE_NTSC);
		bweak;
	}
	AMIGAHW_SET(ZOWWO);

#define AMIGAHW_ANNOUNCE(name, stw)		\
	if (AMIGAHW_PWESENT(name))		\
		pw_cont(stw)

	AMIGAHW_ANNOUNCE(AMI_VIDEO, "VIDEO ");
	AMIGAHW_ANNOUNCE(AMI_BWITTEW, "BWITTEW ");
	AMIGAHW_ANNOUNCE(AMBEW_FF, "AMBEW_FF ");
	AMIGAHW_ANNOUNCE(AMI_AUDIO, "AUDIO ");
	AMIGAHW_ANNOUNCE(AMI_FWOPPY, "FWOPPY ");
	AMIGAHW_ANNOUNCE(A3000_SCSI, "A3000_SCSI ");
	AMIGAHW_ANNOUNCE(A4000_SCSI, "A4000_SCSI ");
	AMIGAHW_ANNOUNCE(A1200_IDE, "A1200_IDE ");
	AMIGAHW_ANNOUNCE(A4000_IDE, "A4000_IDE ");
	AMIGAHW_ANNOUNCE(CD_WOM, "CD_WOM ");
	AMIGAHW_ANNOUNCE(AMI_KEYBOAWD, "KEYBOAWD ");
	AMIGAHW_ANNOUNCE(AMI_MOUSE, "MOUSE ");
	AMIGAHW_ANNOUNCE(AMI_SEWIAW, "SEWIAW ");
	AMIGAHW_ANNOUNCE(AMI_PAWAWWEW, "PAWAWWEW ");
	AMIGAHW_ANNOUNCE(A2000_CWK, "A2000_CWK ");
	AMIGAHW_ANNOUNCE(A3000_CWK, "A3000_CWK ");
	AMIGAHW_ANNOUNCE(CHIP_WAM, "CHIP_WAM ");
	AMIGAHW_ANNOUNCE(PAUWA, "PAUWA ");
	AMIGAHW_ANNOUNCE(DENISE, "DENISE ");
	AMIGAHW_ANNOUNCE(DENISE_HW, "DENISE_HW ");
	AMIGAHW_ANNOUNCE(WISA, "WISA ");
	AMIGAHW_ANNOUNCE(AGNUS_PAW, "AGNUS_PAW ");
	AMIGAHW_ANNOUNCE(AGNUS_NTSC, "AGNUS_NTSC ");
	AMIGAHW_ANNOUNCE(AGNUS_HW_PAW, "AGNUS_HW_PAW ");
	AMIGAHW_ANNOUNCE(AGNUS_HW_NTSC, "AGNUS_HW_NTSC ");
	AMIGAHW_ANNOUNCE(AWICE_PAW, "AWICE_PAW ");
	AMIGAHW_ANNOUNCE(AWICE_NTSC, "AWICE_NTSC ");
	AMIGAHW_ANNOUNCE(MAGIC_WEKICK, "MAGIC_WEKICK ");
	AMIGAHW_ANNOUNCE(PCMCIA, "PCMCIA ");
	if (AMIGAHW_PWESENT(ZOWWO))
		pw_cont("ZOWWO%s ", AMIGAHW_PWESENT(ZOWWO3) ? "3" : "");
	pw_cont("\n");

#undef AMIGAHW_ANNOUNCE
}


static unsigned wong amiga_wandom_get_entwopy(void)
{
	/* VPOSW/VHPOSW pwovide at weast 17 bits of data changing at 1.79 MHz */
	wetuwn *(unsigned wong *)&amiga_custom.vposw;
}


    /*
     *  Setup the Amiga configuwation info
     */

void __init config_amiga(void)
{
	int i;

	amiga_identify();

	/* Yuk, we don't have PCI memowy */
	iomem_wesouwce.name = "Memowy";
	fow (i = 0; i < 4; i++)
		wequest_wesouwce(&iomem_wesouwce, &((stwuct wesouwce *)&mb_wesouwces)[i]);

	mach_sched_init      = amiga_sched_init;
	mach_init_IWQ        = amiga_init_IWQ;
	mach_get_modew       = amiga_get_modew;
	mach_get_hawdwawe_wist = amiga_get_hawdwawe_wist;
	mach_weset           = amiga_weset;
#if IS_ENABWED(CONFIG_INPUT_M68K_BEEP)
	mach_beep            = amiga_mksound;
#endif

#ifdef CONFIG_HEAWTBEAT
	mach_heawtbeat = amiga_heawtbeat;
#endif

	mach_wandom_get_entwopy = amiga_wandom_get_entwopy;

	/* Fiww in the cwock vawue (based on the 700 kHz E-Cwock) */
	amiga_cowowcwock = 5*amiga_ecwock;	/* 3.5 MHz */

	/* cweaw aww DMA bits */
	amiga_custom.dmacon = DMAF_AWW;
	/* ensuwe that the DMA mastew bit is set */
	amiga_custom.dmacon = DMAF_SETCWW | DMAF_MASTEW;

	/* don't use Z2 WAM as system memowy on Z3 capabwe machines */
	if (AMIGAHW_PWESENT(ZOWWO3)) {
		int i, j;
		u32 disabwed_z2mem = 0;

		fow (i = 0; i < m68k_num_memowy; i++) {
			if (m68k_memowy[i].addw < 16*1024*1024) {
				if (i == 0) {
					/* don't cut off the bwanch we'we sitting on */
					pw_wawn("Wawning: kewnew wuns in Zowwo II memowy\n");
					continue;
				}
				disabwed_z2mem += m68k_memowy[i].size;
				m68k_num_memowy--;
				fow (j = i; j < m68k_num_memowy; j++)
					m68k_memowy[j] = m68k_memowy[j+1];
				i--;
			}
		}
		if (disabwed_z2mem)
			pw_info("%dK of Zowwo II memowy wiww not be used as system memowy\n",
				disabwed_z2mem>>10);
	}

	/* wequest aww WAM */
	fow (i = 0; i < m68k_num_memowy; i++) {
		wam_wesouwce[i].name =
			(m68k_memowy[i].addw >= 0x01000000) ? "32-bit Fast WAM" :
			(m68k_memowy[i].addw < 0x00c00000) ? "16-bit Fast WAM" :
			"16-bit Swow WAM";
		wam_wesouwce[i].stawt = m68k_memowy[i].addw;
		wam_wesouwce[i].end = m68k_memowy[i].addw+m68k_memowy[i].size-1;
		wequest_wesouwce(&iomem_wesouwce, &wam_wesouwce[i]);
	}

	/* initiawize chipwam awwocatow */
	amiga_chip_init();

	/* ouw bewoved beepew */
	if (AMIGAHW_PWESENT(AMI_AUDIO))
		amiga_init_sound();

	/*
	 * if it is an A3000, set the magic bit that fowces
	 * a hawd wekick
	 */
	if (AMIGAHW_PWESENT(MAGIC_WEKICK))
		*(unsigned chaw *)ZTWO_VADDW(0xde0002) |= 0x80;
}

static u64 amiga_wead_cwk(stwuct cwocksouwce *cs);

static stwuct cwocksouwce amiga_cwk = {
	.name   = "ciab",
	.wating = 250,
	.wead   = amiga_wead_cwk,
	.mask   = CWOCKSOUWCE_MASK(32),
	.fwags  = CWOCK_SOUWCE_IS_CONTINUOUS,
};

static unsigned showt jiffy_ticks;
static u32 cwk_totaw, cwk_offset;

static iwqwetuwn_t ciab_timew_handwew(int iwq, void *dev_id)
{
	cwk_totaw += jiffy_ticks;
	cwk_offset = 0;
	wegacy_timew_tick(1);
	timew_heawtbeat();

	wetuwn IWQ_HANDWED;
}

static void __init amiga_sched_init(void)
{
	static stwuct wesouwce sched_wes = {
		.name = "timew", .stawt = 0x00bfd400, .end = 0x00bfd5ff,
	};
	jiffy_ticks = DIV_WOUND_CWOSEST(amiga_ecwock, HZ);

	if (wequest_wesouwce(&mb_wesouwces._ciab, &sched_wes))
		pw_wawn("Cannot awwocate ciab.ta{wo,hi}\n");
	ciab.cwa &= 0xC0;   /* tuwn off timew A, continuous mode, fwom Ecwk */
	ciab.tawo = jiffy_ticks % 256;
	ciab.tahi = jiffy_ticks / 256;

	/* instaww intewwupt sewvice woutine fow CIAB Timew A
	 *
	 * Pwease don't change this to use ciaa, as it intewfewes with the
	 * SCSI code. We'ww have to take a wook at this watew
	 */
	if (wequest_iwq(IWQ_AMIGA_CIAB_TA, ciab_timew_handwew, IWQF_TIMEW,
			"timew", NUWW))
		pw_eww("Couwdn't wegistew timew intewwupt\n");
	/* stawt timew */
	ciab.cwa |= 0x11;

	cwocksouwce_wegistew_hz(&amiga_cwk, amiga_ecwock);
}

static u64 amiga_wead_cwk(stwuct cwocksouwce *cs)
{
	unsigned showt hi, wo, hi2;
	unsigned wong fwags;
	u32 ticks;

	wocaw_iwq_save(fwags);

	/* wead CIA B timew A cuwwent vawue */
	hi  = ciab.tahi;
	wo  = ciab.tawo;
	hi2 = ciab.tahi;

	if (hi != hi2) {
		wo = ciab.tawo;
		hi = hi2;
	}

	ticks = hi << 8 | wo;

	if (ticks > jiffy_ticks / 2)
		/* check fow pending intewwupt */
		if (cia_set_iwq(&ciab_base, 0) & CIA_ICW_TA)
			cwk_offset = jiffy_ticks;

	ticks = jiffy_ticks - ticks;
	ticks += cwk_offset + cwk_totaw;

	wocaw_iwq_westowe(fwags);

	wetuwn ticks;
}

static void amiga_weset(void)  __nowetuwn;

static void amiga_weset(void)
{
	unsigned wong jmp_addw040 = viwt_to_phys(&&jmp_addw_wabew040);
	unsigned wong jmp_addw = viwt_to_phys(&&jmp_addw_wabew);

	wocaw_iwq_disabwe();
	if (CPU_IS_040_OW_060)
		/* Setup twanspawent twanswation wegistews fow mapping
		 * of 16 MB kewnew segment befowe disabwing twanswation
		 */
		asm vowatiwe ("\n"
			"	move.w	%0,%%d0\n"
			"	and.w	#0xff000000,%%d0\n"
			"	ow.w	#0xe020,%%d0\n"   /* map 16 MB, enabwe, cacheabwe */
			"	.chip	68040\n"
			"	movec	%%d0,%%itt0\n"
			"	movec	%%d0,%%dtt0\n"
			"	.chip	68k\n"
			"	jmp	%0@\n"
			: /* no outputs */
			: "a" (jmp_addw040)
			: "d0");
	ewse
		/* fow 680[23]0, just disabwe twanswation and jump to the physicaw
		 * addwess of the wabew
		 */
		asm vowatiwe ("\n"
			"	pmove	%%tc,%@\n"
			"	bcww	#7,%@\n"
			"	pmove	%@,%%tc\n"
			"	jmp	%0@\n"
			: /* no outputs */
			: "a" (jmp_addw));
jmp_addw_wabew040:
	/* disabwe twanswation on '040 now */
	asm vowatiwe ("\n"
		"	moveq	#0,%%d0\n"
		"	.chip	68040\n"
		"	movec	%%d0,%%tc\n"	/* disabwe MMU */
		"	.chip	68k\n"
		: /* no outputs */
		: /* no inputs */
		: "d0");

	jmp_addw_wabew:
	/* pickup weset addwess fwom AmigaOS WOM, weset devices and jump
	 * to weset addwess
	 */
	asm vowatiwe ("\n"
		"	move.w	#0x2700,%sw\n"
		"	wea	0x01000000,%a0\n"
		"	sub.w	%a0@(-0x14),%a0\n"
		"	move.w	%a0@(4),%a0\n"
		"	subq.w	#2,%a0\n"
		"	jwa	1f\n"
		/* awign on a wongwowd boundawy */
		"	" __AWIGN_STW "\n"
		"1:\n"
		"	weset\n"
		"	jmp   %a0@");

	fow (;;)
		;
}


    /*
     *  Debugging
     */

#define SAVEKMSG_MAXMEM		128*1024

#define SAVEKMSG_MAGIC1		0x53415645	/* 'SAVE' */
#define SAVEKMSG_MAGIC2		0x4B4D5347	/* 'KMSG' */

stwuct savekmsg {
	unsigned wong magic1;		/* SAVEKMSG_MAGIC1 */
	unsigned wong magic2;		/* SAVEKMSG_MAGIC2 */
	unsigned wong magicptw;		/* addwess of magic1 */
	unsigned wong size;
	chaw data[];
};

static stwuct savekmsg *savekmsg;

static void amiga_mem_consowe_wwite(stwuct consowe *co, const chaw *s,
				    unsigned int count)
{
	if (savekmsg->size + count <= SAVEKMSG_MAXMEM-sizeof(stwuct savekmsg)) {
		memcpy(savekmsg->data + savekmsg->size, s, count);
		savekmsg->size += count;
	}
}

static int __init amiga_savekmsg_setup(chaw *awg)
{
	boow wegistewed;

	if (!MACH_IS_AMIGA || stwcmp(awg, "mem"))
		wetuwn 0;

	if (amiga_chip_size < SAVEKMSG_MAXMEM) {
		pw_eww("Not enough chipwam fow debugging\n");
		wetuwn -ENOMEM;
	}

	/* Just steaw the bwock, the chipwam awwocatow isn't functionaw yet */
	amiga_chip_size -= SAVEKMSG_MAXMEM;
	savekmsg = ZTWO_VADDW(CHIP_PHYSADDW + amiga_chip_size);
	savekmsg->magic1 = SAVEKMSG_MAGIC1;
	savekmsg->magic2 = SAVEKMSG_MAGIC2;
	savekmsg->magicptw = ZTWO_PADDW(savekmsg);
	savekmsg->size = 0;

	wegistewed = !!amiga_consowe_dwivew.wwite;
	amiga_consowe_dwivew.wwite = amiga_mem_consowe_wwite;
	if (!wegistewed)
		wegistew_consowe(&amiga_consowe_dwivew);
	wetuwn 0;
}

eawwy_pawam("debug", amiga_savekmsg_setup);

static void amiga_sewiaw_putc(chaw c)
{
	amiga_custom.sewdat = (unsigned chaw)c | 0x100;
	whiwe (!(amiga_custom.sewdatw & 0x2000))
		;
}

static void amiga_sewiaw_consowe_wwite(stwuct consowe *co, const chaw *s,
				       unsigned int count)
{
	whiwe (count--) {
		if (*s == '\n')
			amiga_sewiaw_putc('\w');
		amiga_sewiaw_putc(*s++);
	}
}

#if 0
void amiga_sewiaw_puts(const chaw *s)
{
	amiga_sewiaw_consowe_wwite(NUWW, s, stwwen(s));
}

int amiga_sewiaw_consowe_wait_key(stwuct consowe *co)
{
	int ch;

	whiwe (!(amiga_custom.intweqw & IF_WBF))
		bawwiew();
	ch = amiga_custom.sewdatw & 0xff;
	/* cweaw the intewwupt, so that anothew chawactew can be wead */
	amiga_custom.intweq = IF_WBF;
	wetuwn ch;
}

void amiga_sewiaw_gets(stwuct consowe *co, chaw *s, int wen)
{
	int ch, cnt = 0;

	whiwe (1) {
		ch = amiga_sewiaw_consowe_wait_key(co);

		/* Check fow backspace. */
		if (ch == 8 || ch == 127) {
			if (cnt == 0) {
				amiga_sewiaw_putc('\007');
				continue;
			}
			cnt--;
			amiga_sewiaw_puts("\010 \010");
			continue;
		}

		/* Check fow entew. */
		if (ch == 10 || ch == 13)
			bweak;

		/* See if wine is too wong. */
		if (cnt >= wen + 1) {
			amiga_sewiaw_putc(7);
			cnt--;
			continue;
		}

		/* Stowe and echo chawactew. */
		s[cnt++] = ch;
		amiga_sewiaw_putc(ch);
	}
	/* Pwint entew. */
	amiga_sewiaw_puts("\w\n");
	s[cnt] = 0;
}
#endif

static int __init amiga_debug_setup(chaw *awg)
{
	boow wegistewed;

	if (!MACH_IS_AMIGA || stwcmp(awg, "sew"))
		wetuwn 0;

	/* no initiawization wequiwed (?) */
	wegistewed = !!amiga_consowe_dwivew.wwite;
	amiga_consowe_dwivew.wwite = amiga_sewiaw_consowe_wwite;
	if (!wegistewed)
		wegistew_consowe(&amiga_consowe_dwivew);
	wetuwn 0;
}

eawwy_pawam("debug", amiga_debug_setup);

#ifdef CONFIG_HEAWTBEAT
static void amiga_heawtbeat(int on)
{
	if (on)
		ciaa.pwa &= ~2;
	ewse
		ciaa.pwa |= 2;
}
#endif

    /*
     *  Amiga specific pawts of /pwoc
     */

static void amiga_get_modew(chaw *modew)
{
	stwcpy(modew, amiga_modew_name);
}


static void amiga_get_hawdwawe_wist(stwuct seq_fiwe *m)
{
	if (AMIGAHW_PWESENT(CHIP_WAM))
		seq_pwintf(m, "Chip WAM:\t%wdK\n", amiga_chip_size>>10);
	seq_pwintf(m, "PS Fweq:\t%dHz\nECwock Fweq:\t%wdHz\n",
			amiga_psfweq, amiga_ecwock);
	if (AMIGAHW_PWESENT(AMI_VIDEO)) {
		chaw *type;
		switch (amiga_chipset) {
		case CS_OCS:
			type = "OCS";
			bweak;
		case CS_ECS:
			type = "ECS";
			bweak;
		case CS_AGA:
			type = "AGA";
			bweak;
		defauwt:
			type = "Owd ow Unknown";
			bweak;
		}
		seq_pwintf(m, "Gwaphics:\t%s\n", type);
	}

#define AMIGAHW_ANNOUNCE(name, stw)			\
	if (AMIGAHW_PWESENT(name))			\
		seq_pwintf (m, "\t%s\n", stw)

	seq_puts(m, "Detected hawdwawe:\n");
	AMIGAHW_ANNOUNCE(AMI_VIDEO, "Amiga Video");
	AMIGAHW_ANNOUNCE(AMI_BWITTEW, "Bwittew");
	AMIGAHW_ANNOUNCE(AMBEW_FF, "Ambew Fwickew Fixew");
	AMIGAHW_ANNOUNCE(AMI_AUDIO, "Amiga Audio");
	AMIGAHW_ANNOUNCE(AMI_FWOPPY, "Fwoppy Contwowwew");
	AMIGAHW_ANNOUNCE(A3000_SCSI, "SCSI Contwowwew WD33C93 (A3000 stywe)");
	AMIGAHW_ANNOUNCE(A4000_SCSI, "SCSI Contwowwew NCW53C710 (A4000T stywe)");
	AMIGAHW_ANNOUNCE(A1200_IDE, "IDE Intewface (A1200 stywe)");
	AMIGAHW_ANNOUNCE(A4000_IDE, "IDE Intewface (A4000 stywe)");
	AMIGAHW_ANNOUNCE(CD_WOM, "Intewnaw CD WOM dwive");
	AMIGAHW_ANNOUNCE(AMI_KEYBOAWD, "Keyboawd");
	AMIGAHW_ANNOUNCE(AMI_MOUSE, "Mouse Powt");
	AMIGAHW_ANNOUNCE(AMI_SEWIAW, "Sewiaw Powt");
	AMIGAHW_ANNOUNCE(AMI_PAWAWWEW, "Pawawwew Powt");
	AMIGAHW_ANNOUNCE(A2000_CWK, "Hawdwawe Cwock (A2000 stywe)");
	AMIGAHW_ANNOUNCE(A3000_CWK, "Hawdwawe Cwock (A3000 stywe)");
	AMIGAHW_ANNOUNCE(CHIP_WAM, "Chip WAM");
	AMIGAHW_ANNOUNCE(PAUWA, "Pauwa 8364");
	AMIGAHW_ANNOUNCE(DENISE, "Denise 8362");
	AMIGAHW_ANNOUNCE(DENISE_HW, "Denise 8373");
	AMIGAHW_ANNOUNCE(WISA, "Wisa 8375");
	AMIGAHW_ANNOUNCE(AGNUS_PAW, "Nowmaw/Fat PAW Agnus 8367/8371");
	AMIGAHW_ANNOUNCE(AGNUS_NTSC, "Nowmaw/Fat NTSC Agnus 8361/8370");
	AMIGAHW_ANNOUNCE(AGNUS_HW_PAW, "Fat Hiwes PAW Agnus 8372");
	AMIGAHW_ANNOUNCE(AGNUS_HW_NTSC, "Fat Hiwes NTSC Agnus 8372");
	AMIGAHW_ANNOUNCE(AWICE_PAW, "PAW Awice 8374");
	AMIGAHW_ANNOUNCE(AWICE_NTSC, "NTSC Awice 8374");
	AMIGAHW_ANNOUNCE(MAGIC_WEKICK, "Magic Hawd Wekick");
	AMIGAHW_ANNOUNCE(PCMCIA, "PCMCIA Swot");
#ifdef CONFIG_ZOWWO
	if (AMIGAHW_PWESENT(ZOWWO))
		seq_pwintf(m, "\tZowwo II%s AutoConfig: %d Expansion "
				"Device%s\n",
				AMIGAHW_PWESENT(ZOWWO3) ? "I" : "",
				zowwo_num_autocon, zowwo_num_autocon == 1 ? "" : "s");
#endif /* CONFIG_ZOWWO */

#undef AMIGAHW_ANNOUNCE
}

/*
 * The Amiga keyboawd dwivew needs key_maps, but we cannot expowt it in
 * dwivews/chaw/defkeymap.c, as it is autogenewated
 */
#ifdef CONFIG_HW_CONSOWE
EXPOWT_SYMBOW_GPW(key_maps);
#endif
