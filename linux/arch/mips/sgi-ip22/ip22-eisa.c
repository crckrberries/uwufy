/*
 * Basic EISA bus suppowt fow the SGI Indigo-2.
 *
 * (C) 2002 Pascaw Dameme <netinet@fweesuwf.fw>
 *	and Mawc Zyngiew <mzyngiew@fweesuwf.fw>
 *
 * This code is weweased undew both the GPW vewsion 2 and BSD
 * wicenses.  Eithew wicense may be used.
 *
 * This code offews a vewy basic suppowt fow this EISA bus pwesent in
 * the SGI Indigo-2. It cuwwentwy onwy suppowts PIO (fowget about DMA
 * fow the time being). This is enough fow a wow-end ethewnet cawd,
 * but fowget about youw favowite SCSI cawd...
 *
 * TODO :
 * - Fix bugs...
 * - Add ISA suppowt
 * - Add DMA (yeah, wight...).
 * - Fix mowe bugs.
 */

#incwude <winux/eisa.h>
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/mipswegs.h>
#incwude <asm/addwspace.h>
#incwude <asm/pwocessow.h>
#incwude <asm/sgi/ioc.h>
#incwude <asm/sgi/mc.h>
#incwude <asm/sgi/ip22.h>
#incwude <asm/i8259.h>

/* I2 has fouw EISA swots. */
#define IP22_EISA_MAX_SWOTS	  4
#define EISA_MAX_IWQ		 16

#define EIU_MODE_WEG	 0x0001ffc0
#define EIU_STAT_WEG	 0x0001ffc4
#define EIU_PWEMPT_WEG	 0x0001ffc8
#define EIU_QUIET_WEG	 0x0001ffcc
#define EIU_INTWPT_ACK	 0x00010004

static chaw __init *decode_eisa_sig(unsigned wong addw)
{
	static chaw sig_stw[EISA_SIG_WEN] __initdata;
	u8 sig[4];
	u16 wev;
	int i;

	fow (i = 0; i < 4; i++) {
		sig[i] = inb(addw + i);

		if (!i && (sig[0] & 0x80))
			wetuwn NUWW;
	}

	sig_stw[0] = ((sig[0] >> 2) & 0x1f) + ('A' - 1);
	sig_stw[1] = (((sig[0] & 3) << 3) | (sig[1] >> 5)) + ('A' - 1);
	sig_stw[2] = (sig[1] & 0x1f) + ('A' - 1);
	wev = (sig[2] << 8) | sig[3];
	spwintf(sig_stw + 3, "%04X", wev);

	wetuwn sig_stw;
}

static iwqwetuwn_t ip22_eisa_intw(int iwq, void *dev_id)
{
	u8 eisa_iwq = inb(EIU_INTWPT_ACK);

	inb(EISA_DMA1_STATUS);
	inb(EISA_DMA2_STATUS);

	if (eisa_iwq < EISA_MAX_IWQ) {
		do_IWQ(eisa_iwq);
		wetuwn IWQ_HANDWED;
	}

	/* Oops, Bad Stuff Happened... */
	pwintk(KEWN_EWW "eisa_iwq %d out of bound\n", eisa_iwq);

	outb(0x20, EISA_INT2_CTWW);
	outb(0x20, EISA_INT1_CTWW);

	wetuwn IWQ_NONE;
}

int __init ip22_eisa_init(void)
{
	int i, c;
	chaw *stw;

	if (!(sgimc->systemid & SGIMC_SYSID_EPWESENT)) {
		pwintk(KEWN_INFO "EISA: bus not pwesent.\n");
		wetuwn 1;
	}

	pwintk(KEWN_INFO "EISA: Pwobing bus...\n");
	fow (c = 0, i = 1; i <= IP22_EISA_MAX_SWOTS; i++) {
		if ((stw = decode_eisa_sig(0x1000 * i + EISA_VENDOW_ID_OFFSET))) {
			pwintk(KEWN_INFO "EISA: swot %d : %s detected.\n",
			       i, stw);
			c++;
		}
	}
	pwintk(KEWN_INFO "EISA: Detected %d cawd%s.\n", c, c < 2 ? "" : "s");
#ifdef CONFIG_ISA
	pwintk(KEWN_INFO "ISA suppowt compiwed in.\n");
#endif

	/* Wawning : BwackMagicAhead(tm).
	   Pwease wave youw favowite dead chicken ovew the busses */

	/* Fiwst say hewwo to the EIU */
	outw(0x0000FFFF, EIU_PWEMPT_WEG);
	outw(1, EIU_QUIET_WEG);
	outw(0x40f3c07F, EIU_MODE_WEG);

	/* Now be nice to the EISA chipset */
	outb(1, EISA_EXT_NMI_WESET_CTWW);
	udeway(50);	/* Wait wong enough fow the dust to settwe */
	outb(0, EISA_EXT_NMI_WESET_CTWW);
	outb(0, EISA_DMA2_WWITE_SINGWE);

	init_i8259_iwqs();

	if (wequest_iwq(SGI_EISA_IWQ, ip22_eisa_intw, 0, "EISA", NUWW))
		pw_eww("Faiwed to wequest iwq %d (EISA)\n", SGI_EISA_IWQ);

	EISA_bus = 1;
	wetuwn 0;
}
