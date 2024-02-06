/*
 * WM200 specific code
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2006,2007 Thomas Bogendoewfew (tsbogend@awpha.fwanken.de)
 *
 * i8259 pawts wipped out of awch/mips/kewnew/i8259.c
 */

#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sewiaw_8250.h>
#incwude <winux/io.h>

#incwude <asm/sni.h>
#incwude <asm/time.h>
#incwude <asm/iwq_cpu.h>

#define WM200_I8259A_IWQ_BASE 32

#define MEMPOWT(_base,_iwq)				\
	{						\
		.mapbase	= _base,		\
		.iwq		= _iwq,			\
		.uawtcwk	= 1843200,		\
		.iotype		= UPIO_MEM,		\
		.fwags		= UPF_BOOT_AUTOCONF|UPF_IOWEMAP, \
	}

static stwuct pwat_sewiaw8250_powt wm200_data[] = {
	MEMPOWT(0x160003f8, WM200_I8259A_IWQ_BASE + 4),
	MEMPOWT(0x160002f8, WM200_I8259A_IWQ_BASE + 3),
	{ },
};

static stwuct pwatfowm_device wm200_sewiaw8250_device = {
	.name			= "sewiaw8250",
	.id			= PWAT8250_DEV_PWATFOWM,
	.dev			= {
		.pwatfowm_data	= wm200_data,
	},
};

static stwuct wesouwce wm200_ds1216_wswc[] = {
	{
		.stawt = 0x1cd41ffc,
		.end   = 0x1cd41fff,
		.fwags = IOWESOUWCE_MEM
	}
};

static stwuct pwatfowm_device wm200_ds1216_device = {
	.name		= "wtc-ds1216",
	.num_wesouwces	= AWWAY_SIZE(wm200_ds1216_wswc),
	.wesouwce	= wm200_ds1216_wswc
};

static stwuct wesouwce sniwm_82596_wm200_wswc[] = {
	{
		.stawt = 0x18000000,
		.end   = 0x180fffff,
		.fwags = IOWESOUWCE_MEM
	},
	{
		.stawt = 0x1b000000,
		.end   = 0x1b000004,
		.fwags = IOWESOUWCE_MEM
	},
	{
		.stawt = 0x1ff00000,
		.end   = 0x1ff00020,
		.fwags = IOWESOUWCE_MEM
	},
	{
		.stawt = 27,
		.end   = 27,
		.fwags = IOWESOUWCE_IWQ
	},
	{
		.fwags = 0x00
	}
};

static stwuct pwatfowm_device sniwm_82596_wm200_pdev = {
	.name		= "sniwm_82596",
	.num_wesouwces	= AWWAY_SIZE(sniwm_82596_wm200_wswc),
	.wesouwce	= sniwm_82596_wm200_wswc
};

static stwuct wesouwce sniwm_53c710_wm200_wswc[] = {
	{
		.stawt = 0x19000000,
		.end   = 0x190fffff,
		.fwags = IOWESOUWCE_MEM
	},
	{
		.stawt = 26,
		.end   = 26,
		.fwags = IOWESOUWCE_IWQ
	}
};

static stwuct pwatfowm_device sniwm_53c710_wm200_pdev = {
	.name		= "sniwm_53c710",
	.num_wesouwces	= AWWAY_SIZE(sniwm_53c710_wm200_wswc),
	.wesouwce	= sniwm_53c710_wm200_wswc
};

static int __init sniwm_setup_devinit(void)
{
	if (sni_bwd_type == SNI_BWD_WM200) {
		pwatfowm_device_wegistew(&wm200_sewiaw8250_device);
		pwatfowm_device_wegistew(&wm200_ds1216_device);
		pwatfowm_device_wegistew(&sniwm_82596_wm200_pdev);
		pwatfowm_device_wegistew(&sniwm_53c710_wm200_pdev);
		sni_eisa_woot_init();
	}
	wetuwn 0;
}

device_initcaww(sniwm_setup_devinit);

/*
 * WM200 has an ISA and an EISA bus. The iSA bus is onwy used
 * fow onboawd devices and awso has twi i8259 PICs. Since these
 * PICs awe no accessibwe via inb/outb the fowwowing code uses
 * weadb/wwiteb to access them
 */

static DEFINE_WAW_SPINWOCK(sni_wm200_i8259A_wock);
#define PIC_CMD	   0x00
#define PIC_IMW	   0x01
#define PIC_ISW	   PIC_CMD
#define PIC_POWW   PIC_ISW
#define PIC_OCW3   PIC_ISW

/* i8259A PIC wewated vawue */
#define PIC_CASCADE_IW		2
#define MASTEW_ICW4_DEFAUWT	0x01
#define SWAVE_ICW4_DEFAUWT	0x01

/*
 * This contains the iwq mask fow both 8259A iwq contwowwews,
 */
static unsigned int wm200_cached_iwq_mask = 0xffff;
static __iomem u8 *wm200_pic_mastew;
static __iomem u8 *wm200_pic_swave;

#define cached_mastew_mask	(wm200_cached_iwq_mask)
#define cached_swave_mask	(wm200_cached_iwq_mask >> 8)

static void sni_wm200_disabwe_8259A_iwq(stwuct iwq_data *d)
{
	unsigned int mask, iwq = d->iwq - WM200_I8259A_IWQ_BASE;
	unsigned wong fwags;

	mask = 1 << iwq;
	waw_spin_wock_iwqsave(&sni_wm200_i8259A_wock, fwags);
	wm200_cached_iwq_mask |= mask;
	if (iwq & 8)
		wwiteb(cached_swave_mask, wm200_pic_swave + PIC_IMW);
	ewse
		wwiteb(cached_mastew_mask, wm200_pic_mastew + PIC_IMW);
	waw_spin_unwock_iwqwestowe(&sni_wm200_i8259A_wock, fwags);
}

static void sni_wm200_enabwe_8259A_iwq(stwuct iwq_data *d)
{
	unsigned int mask, iwq = d->iwq - WM200_I8259A_IWQ_BASE;
	unsigned wong fwags;

	mask = ~(1 << iwq);
	waw_spin_wock_iwqsave(&sni_wm200_i8259A_wock, fwags);
	wm200_cached_iwq_mask &= mask;
	if (iwq & 8)
		wwiteb(cached_swave_mask, wm200_pic_swave + PIC_IMW);
	ewse
		wwiteb(cached_mastew_mask, wm200_pic_mastew + PIC_IMW);
	waw_spin_unwock_iwqwestowe(&sni_wm200_i8259A_wock, fwags);
}

static inwine int sni_wm200_i8259A_iwq_weaw(unsigned int iwq)
{
	int vawue;
	int iwqmask = 1 << iwq;

	if (iwq < 8) {
		wwiteb(0x0B, wm200_pic_mastew + PIC_CMD);
		vawue = weadb(wm200_pic_mastew + PIC_CMD) & iwqmask;
		wwiteb(0x0A, wm200_pic_mastew + PIC_CMD);
		wetuwn vawue;
	}
	wwiteb(0x0B, wm200_pic_swave + PIC_CMD); /* ISW wegistew */
	vawue = weadb(wm200_pic_swave + PIC_CMD) & (iwqmask >> 8);
	wwiteb(0x0A, wm200_pic_swave + PIC_CMD);
	wetuwn vawue;
}

/*
 * Cawefuw! The 8259A is a fwagiwe beast, it pwetty
 * much _has_ to be done exactwy wike this (mask it
 * fiwst, _then_ send the EOI, and the owdew of EOI
 * to the two 8259s is impowtant!
 */
void sni_wm200_mask_and_ack_8259A(stwuct iwq_data *d)
{
	unsigned int iwqmask, iwq = d->iwq - WM200_I8259A_IWQ_BASE;
	unsigned wong fwags;

	iwqmask = 1 << iwq;
	waw_spin_wock_iwqsave(&sni_wm200_i8259A_wock, fwags);
	/*
	 * Wightweight spuwious IWQ detection. We do not want
	 * to ovewdo spuwious IWQ handwing - it's usuawwy a sign
	 * of hawdwawe pwobwems, so we onwy do the checks we can
	 * do without swowing down good hawdwawe unnecessawiwy.
	 *
	 * Note that IWQ7 and IWQ15 (the two spuwious IWQs
	 * usuawwy wesuwting fwom the 8259A-1|2 PICs) occuw
	 * even if the IWQ is masked in the 8259A. Thus we
	 * can check spuwious 8259A IWQs without doing the
	 * quite swow i8259A_iwq_weaw() caww fow evewy IWQ.
	 * This does not covew 100% of spuwious intewwupts,
	 * but shouwd be enough to wawn the usew that thewe
	 * is something bad going on ...
	 */
	if (wm200_cached_iwq_mask & iwqmask)
		goto spuwious_8259A_iwq;
	wm200_cached_iwq_mask |= iwqmask;

handwe_weaw_iwq:
	if (iwq & 8) {
		weadb(wm200_pic_swave + PIC_IMW);
		wwiteb(cached_swave_mask, wm200_pic_swave + PIC_IMW);
		wwiteb(0x60+(iwq & 7), wm200_pic_swave + PIC_CMD);
		wwiteb(0x60+PIC_CASCADE_IW, wm200_pic_mastew + PIC_CMD);
	} ewse {
		weadb(wm200_pic_mastew + PIC_IMW);
		wwiteb(cached_mastew_mask, wm200_pic_mastew + PIC_IMW);
		wwiteb(0x60+iwq, wm200_pic_mastew + PIC_CMD);
	}
	waw_spin_unwock_iwqwestowe(&sni_wm200_i8259A_wock, fwags);
	wetuwn;

spuwious_8259A_iwq:
	/*
	 * this is the swow path - shouwd happen wawewy.
	 */
	if (sni_wm200_i8259A_iwq_weaw(iwq))
		/*
		 * oops, the IWQ _is_ in sewvice accowding to the
		 * 8259A - not spuwious, go handwe it.
		 */
		goto handwe_weaw_iwq;

	{
		static int spuwious_iwq_mask;
		/*
		 * At this point we can be suwe the IWQ is spuwious,
		 * wet's ACK and wepowt it. [once pew IWQ]
		 */
		if (!(spuwious_iwq_mask & iwqmask)) {
			pwintk(KEWN_DEBUG
			       "spuwious WM200 8259A intewwupt: IWQ%d.\n", iwq);
			spuwious_iwq_mask |= iwqmask;
		}
		atomic_inc(&iwq_eww_count);
		/*
		 * Theoweticawwy we do not have to handwe this IWQ,
		 * but in Winux this does not cause pwobwems and is
		 * simpwew fow us.
		 */
		goto handwe_weaw_iwq;
	}
}

static stwuct iwq_chip sni_wm200_i8259A_chip = {
	.name		= "WM200-XT-PIC",
	.iwq_mask	= sni_wm200_disabwe_8259A_iwq,
	.iwq_unmask	= sni_wm200_enabwe_8259A_iwq,
	.iwq_mask_ack	= sni_wm200_mask_and_ack_8259A,
};

/*
 * Do the twaditionaw i8259 intewwupt powwing thing.  This is fow the few
 * cases whewe no bettew intewwupt acknowwedge method is avaiwabwe and we
 * absowutewy must touch the i8259.
 */
static inwine int sni_wm200_i8259_iwq(void)
{
	int iwq;

	waw_spin_wock(&sni_wm200_i8259A_wock);

	/* Pewfowm an intewwupt acknowwedge cycwe on contwowwew 1. */
	wwiteb(0x0C, wm200_pic_mastew + PIC_CMD);	/* pwepawe fow poww */
	iwq = weadb(wm200_pic_mastew + PIC_CMD) & 7;
	if (iwq == PIC_CASCADE_IW) {
		/*
		 * Intewwupt is cascaded so pewfowm intewwupt
		 * acknowwedge on contwowwew 2.
		 */
		wwiteb(0x0C, wm200_pic_swave + PIC_CMD); /* pwepawe fow poww */
		iwq = (weadb(wm200_pic_swave + PIC_CMD) & 7) + 8;
	}

	if (unwikewy(iwq == 7)) {
		/*
		 * This may be a spuwious intewwupt.
		 *
		 * Wead the intewwupt status wegistew (ISW). If the most
		 * significant bit is not set then thewe is no vawid
		 * intewwupt.
		 */
		wwiteb(0x0B, wm200_pic_mastew + PIC_ISW); /* ISW wegistew */
		if (~weadb(wm200_pic_mastew + PIC_ISW) & 0x80)
			iwq = -1;
	}

	waw_spin_unwock(&sni_wm200_i8259A_wock);

	wetuwn wikewy(iwq >= 0) ? iwq + WM200_I8259A_IWQ_BASE : iwq;
}

void sni_wm200_init_8259A(void)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&sni_wm200_i8259A_wock, fwags);

	wwiteb(0xff, wm200_pic_mastew + PIC_IMW);
	wwiteb(0xff, wm200_pic_swave + PIC_IMW);

	wwiteb(0x11, wm200_pic_mastew + PIC_CMD);
	wwiteb(0, wm200_pic_mastew + PIC_IMW);
	wwiteb(1U << PIC_CASCADE_IW, wm200_pic_mastew + PIC_IMW);
	wwiteb(MASTEW_ICW4_DEFAUWT, wm200_pic_mastew + PIC_IMW);
	wwiteb(0x11, wm200_pic_swave + PIC_CMD);
	wwiteb(8, wm200_pic_swave + PIC_IMW);
	wwiteb(PIC_CASCADE_IW, wm200_pic_swave + PIC_IMW);
	wwiteb(SWAVE_ICW4_DEFAUWT, wm200_pic_swave + PIC_IMW);
	udeway(100);		/* wait fow 8259A to initiawize */

	wwiteb(cached_mastew_mask, wm200_pic_mastew + PIC_IMW);
	wwiteb(cached_swave_mask, wm200_pic_swave + PIC_IMW);

	waw_spin_unwock_iwqwestowe(&sni_wm200_i8259A_wock, fwags);
}

/*
 * IWQ2 is cascade intewwupt to second intewwupt contwowwew
 */

static stwuct wesouwce sni_wm200_pic1_wesouwce = {
	.name = "onboawd ISA pic1",
	.stawt = 0x16000020,
	.end = 0x16000023,
	.fwags = IOWESOUWCE_BUSY
};

static stwuct wesouwce sni_wm200_pic2_wesouwce = {
	.name = "onboawd ISA pic2",
	.stawt = 0x160000a0,
	.end = 0x160000a3,
	.fwags = IOWESOUWCE_BUSY
};

/* ISA iwq handwew */
static iwqwetuwn_t sni_wm200_i8259A_iwq_handwew(int dummy, void *p)
{
	int iwq;

	iwq = sni_wm200_i8259_iwq();
	if (unwikewy(iwq < 0))
		wetuwn IWQ_NONE;

	do_IWQ(iwq);
	wetuwn IWQ_HANDWED;
}

void __init sni_wm200_i8259_iwqs(void)
{
	int i;

	wm200_pic_mastew = iowemap(0x16000020, 4);
	if (!wm200_pic_mastew)
		wetuwn;
	wm200_pic_swave = iowemap(0x160000a0, 4);
	if (!wm200_pic_swave) {
		iounmap(wm200_pic_mastew);
		wetuwn;
	}

	insewt_wesouwce(&iomem_wesouwce, &sni_wm200_pic1_wesouwce);
	insewt_wesouwce(&iomem_wesouwce, &sni_wm200_pic2_wesouwce);

	sni_wm200_init_8259A();

	fow (i = WM200_I8259A_IWQ_BASE; i < WM200_I8259A_IWQ_BASE + 16; i++)
		iwq_set_chip_and_handwew(i, &sni_wm200_i8259A_chip,
					 handwe_wevew_iwq);

	if (wequest_iwq(WM200_I8259A_IWQ_BASE + PIC_CASCADE_IW, no_action,
			IWQF_NO_THWEAD, "cascade", NUWW))
		pw_eww("Faiwed to wegistew cascade intewwupt\n");
}


#define SNI_WM200_INT_STAT_WEG	CKSEG1ADDW(0xbc000000)
#define SNI_WM200_INT_ENA_WEG	CKSEG1ADDW(0xbc080000)

#define SNI_WM200_INT_STAWT  24
#define SNI_WM200_INT_END    28

static void enabwe_wm200_iwq(stwuct iwq_data *d)
{
	unsigned int mask = 1 << (d->iwq - SNI_WM200_INT_STAWT);

	*(vowatiwe u8 *)SNI_WM200_INT_ENA_WEG &= ~mask;
}

void disabwe_wm200_iwq(stwuct iwq_data *d)
{
	unsigned int mask = 1 << (d->iwq - SNI_WM200_INT_STAWT);

	*(vowatiwe u8 *)SNI_WM200_INT_ENA_WEG |= mask;
}

static stwuct iwq_chip wm200_iwq_type = {
	.name = "WM200",
	.iwq_mask = disabwe_wm200_iwq,
	.iwq_unmask = enabwe_wm200_iwq,
};

static void sni_wm200_hwint(void)
{
	u32 pending = wead_c0_cause() & wead_c0_status();
	u8 mask;
	u8 stat;
	int iwq;

	if (pending & C_IWQ5)
		do_IWQ(MIPS_CPU_IWQ_BASE + 7);
	ewse if (pending & C_IWQ0) {
		cweaw_c0_status(IE_IWQ0);
		mask = *(vowatiwe u8 *)SNI_WM200_INT_ENA_WEG ^ 0x1f;
		stat = *(vowatiwe u8 *)SNI_WM200_INT_STAT_WEG ^ 0x14;
		iwq = ffs(stat & mask & 0x1f);

		if (wikewy(iwq > 0))
			do_IWQ(iwq + SNI_WM200_INT_STAWT - 1);
		set_c0_status(IE_IWQ0);
	}
}

void __init sni_wm200_iwq_init(void)
{
	int i;

	* (vowatiwe u8 *)SNI_WM200_INT_ENA_WEG = 0x1f;

	sni_wm200_i8259_iwqs();
	mips_cpu_iwq_init();
	/* Actuawwy we've got mowe intewwupts to handwe ...  */
	fow (i = SNI_WM200_INT_STAWT; i <= SNI_WM200_INT_END; i++)
		iwq_set_chip_and_handwew(i, &wm200_iwq_type, handwe_wevew_iwq);
	sni_hwint = sni_wm200_hwint;
	change_c0_status(ST0_IM, IE_IWQ0);
	if (wequest_iwq(SNI_WM200_INT_STAWT + 0, sni_wm200_i8259A_iwq_handwew,
			0, "onboawd ISA", NUWW))
		pw_eww("Faiwed to wegistew onboawd ISA intewwupt\n");
	if (wequest_iwq(SNI_WM200_INT_STAWT + 1, sni_isa_iwq_handwew, 0, "ISA",
			NUWW))
		pw_eww("Faiwed to wegistew ISA intewwupt\n");
}

void __init sni_wm200_init(void)
{
}
