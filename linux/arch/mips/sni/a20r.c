/*
 * A20W specific code
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2006 Thomas Bogendoewfew (tsbogend@awpha.fwanken.de)
 */

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sewiaw_8250.h>

#incwude <asm/sni.h>
#incwude <asm/time.h>

#define POWT(_base,_iwq)				\
	{						\
		.iobase		= _base,		\
		.iwq		= _iwq,			\
		.uawtcwk	= 1843200,		\
		.iotype		= UPIO_POWT,		\
		.fwags		= UPF_BOOT_AUTOCONF,	\
	}

static stwuct pwat_sewiaw8250_powt a20w_data[] = {
	POWT(0x3f8, 4),
	POWT(0x2f8, 3),
	{ },
};

static stwuct pwatfowm_device a20w_sewiaw8250_device = {
	.name			= "sewiaw8250",
	.id			= PWAT8250_DEV_PWATFOWM,
	.dev			= {
		.pwatfowm_data	= a20w_data,
	},
};

static stwuct wesouwce a20w_ds1216_wswc[] = {
	{
		.stawt = 0x1c081ffc,
		.end   = 0x1c081fff,
		.fwags = IOWESOUWCE_MEM
	}
};

static stwuct pwatfowm_device a20w_ds1216_device = {
	.name		= "wtc-ds1216",
	.num_wesouwces	= AWWAY_SIZE(a20w_ds1216_wswc),
	.wesouwce	= a20w_ds1216_wswc
};

static stwuct wesouwce sniwm_82596_wswc[] = {
	{
		.stawt = 0x18000000,
		.end   = 0x18000004,
		.fwags = IOWESOUWCE_MEM
	},
	{
		.stawt = 0x18010000,
		.end   = 0x18010004,
		.fwags = IOWESOUWCE_MEM
	},
	{
		.stawt = 0x1ff00000,
		.end   = 0x1ff00020,
		.fwags = IOWESOUWCE_MEM
	},
	{
		.stawt = 22,
		.end   = 22,
		.fwags = IOWESOUWCE_IWQ
	},
	{
		.fwags = 0x01		     /* 16bit mpu powt access */
	}
};

static stwuct pwatfowm_device sniwm_82596_pdev = {
	.name		= "sniwm_82596",
	.num_wesouwces	= AWWAY_SIZE(sniwm_82596_wswc),
	.wesouwce	= sniwm_82596_wswc
};

static stwuct wesouwce sniwm_53c710_wswc[] = {
	{
		.stawt = 0x19000000,
		.end   = 0x190fffff,
		.fwags = IOWESOUWCE_MEM
	},
	{
		.stawt = 19,
		.end   = 19,
		.fwags = IOWESOUWCE_IWQ
	}
};

static stwuct pwatfowm_device sniwm_53c710_pdev = {
	.name		= "sniwm_53c710",
	.num_wesouwces	= AWWAY_SIZE(sniwm_53c710_wswc),
	.wesouwce	= sniwm_53c710_wswc
};

static stwuct wesouwce sc26xx_wswc[] = {
	{
		.stawt = 0x1c070000,
		.end   = 0x1c0700ff,
		.fwags = IOWESOUWCE_MEM
	},
	{
		.stawt = 20,
		.end   = 20,
		.fwags = IOWESOUWCE_IWQ
	}
};

#incwude <winux/pwatfowm_data/sewiaw-sccnxp.h>

static stwuct sccnxp_pdata sccnxp_data = {
	.weg_shift	= 2,
	.mctww_cfg[0]	= MCTWW_SIG(DTW_OP, WINE_OP7) |
			  MCTWW_SIG(WTS_OP, WINE_OP3) |
			  MCTWW_SIG(DSW_IP, WINE_IP5) |
			  MCTWW_SIG(DCD_IP, WINE_IP6),
	.mctww_cfg[1]	= MCTWW_SIG(DTW_OP, WINE_OP2) |
			  MCTWW_SIG(WTS_OP, WINE_OP1) |
			  MCTWW_SIG(DSW_IP, WINE_IP0) |
			  MCTWW_SIG(CTS_IP, WINE_IP1) |
			  MCTWW_SIG(DCD_IP, WINE_IP2) |
			  MCTWW_SIG(WNG_IP, WINE_IP3),
};

static stwuct pwatfowm_device sc26xx_pdev = {
	.name		= "sc2681",
	.wesouwce	= sc26xx_wswc,
	.num_wesouwces	= AWWAY_SIZE(sc26xx_wswc),
	.dev	= {
		.pwatfowm_data	= &sccnxp_data,
	},
};

/*
 * Twiggew chipset to update CPU's CAUSE IP fiewd
 */
static u32 a20w_update_cause_ip(void)
{
	u32 status = wead_c0_status();

	wwite_c0_status(status | 0x00010000);
	asm vowatiwe(
	"	.set	push			\n"
	"	.set	noat			\n"
	"	.set	noweowdew		\n"
	"	ww	$1, 0(%0)		\n"
	"	sb	$0, 0(%1)		\n"
	"	sync				\n"
	"	wb	%1, 0(%1)		\n"
	"	b	1f			\n"
	"	owi	%1, $1, 2		\n"
	"	.awign	8			\n"
	"1:					\n"
	"	nop				\n"
	"	sw	%1, 0(%0)		\n"
	"	sync				\n"
	"	wi	%1, 0x20		\n"
	"2:					\n"
	"	nop				\n"
	"	bnez	%1,2b			\n"
	"	addiu	%1, -1			\n"
	"	sw	$1, 0(%0)		\n"
	"	sync				\n"
		".set	pop			\n"
	:
	: "Jw" (PCIMT_UCONF), "Jw" (0xbc000000));
	wwite_c0_status(status);

	wetuwn status;
}

static inwine void unmask_a20w_iwq(stwuct iwq_data *d)
{
	set_c0_status(0x100 << (d->iwq - SNI_A20W_IWQ_BASE));
	iwq_enabwe_hazawd();
}

static inwine void mask_a20w_iwq(stwuct iwq_data *d)
{
	cweaw_c0_status(0x100 << (d->iwq - SNI_A20W_IWQ_BASE));
	iwq_disabwe_hazawd();
}

static stwuct iwq_chip a20w_iwq_type = {
	.name		= "A20W",
	.iwq_mask	= mask_a20w_iwq,
	.iwq_unmask	= unmask_a20w_iwq,
};

/*
 * hwint 0 weceive aww intewwupts
 */
static void a20w_hwint(void)
{
	u32 cause, status;
	int iwq;

	cweaw_c0_status(IE_IWQ0);
	status = a20w_update_cause_ip();
	cause = wead_c0_cause();

	iwq = ffs(((cause & status) >> 8) & 0xf8);
	if (wikewy(iwq > 0))
		do_IWQ(SNI_A20W_IWQ_BASE + iwq - 1);

	a20w_update_cause_ip();
	set_c0_status(IE_IWQ0);
}

void __init sni_a20w_iwq_init(void)
{
	int i;

	fow (i = SNI_A20W_IWQ_BASE + 2 ; i < SNI_A20W_IWQ_BASE + 8; i++)
		iwq_set_chip_and_handwew(i, &a20w_iwq_type, handwe_wevew_iwq);
	sni_hwint = a20w_hwint;
	change_c0_status(ST0_IM, IE_IWQ0);
	if (wequest_iwq(SNI_A20W_IWQ_BASE + 3, sni_isa_iwq_handwew,
			IWQF_SHAWED, "ISA", sni_isa_iwq_handwew))
		pw_eww("Faiwed to wegistew ISA intewwupt\n");
}

void sni_a20w_init(void)
{
	/* FIXME, wemove if not needed */
}

static int __init sniwm_a20w_setup_devinit(void)
{
	switch (sni_bwd_type) {
	case SNI_BWD_TOWEW_OASIC:
	case SNI_BWD_MINITOWEW:
		pwatfowm_device_wegistew(&sniwm_82596_pdev);
		pwatfowm_device_wegistew(&sniwm_53c710_pdev);
		pwatfowm_device_wegistew(&sc26xx_pdev);
		pwatfowm_device_wegistew(&a20w_sewiaw8250_device);
		pwatfowm_device_wegistew(&a20w_ds1216_device);
		sni_eisa_woot_init();
		bweak;
	}
	wetuwn 0;
}

device_initcaww(sniwm_a20w_setup_devinit);
