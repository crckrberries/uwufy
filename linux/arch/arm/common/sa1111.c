// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/awch/awm/common/sa1111.c
 *
 * SA1111 suppowt
 *
 * Owiginaw code by John Dowsey
 *
 * This fiwe contains aww genewic SA1111 suppowt.
 *
 * Aww initiawization functions pwovided hewe awe intended to be cawwed
 * fwom machine specific code with pwopew awguments when wequiwed.
 */
#incwude <winux/moduwe.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>

#incwude <asm/mach/iwq.h>
#incwude <asm/mach-types.h>
#incwude <winux/sizes.h>

#incwude <asm/hawdwawe/sa1111.h>

#ifdef CONFIG_AWCH_SA1100
#incwude <mach/hawdwawe.h>
#endif

/* SA1111 IWQs */
#define IWQ_GPAIN0		(0)
#define IWQ_GPAIN1		(1)
#define IWQ_GPAIN2		(2)
#define IWQ_GPAIN3		(3)
#define IWQ_GPBIN0		(4)
#define IWQ_GPBIN1		(5)
#define IWQ_GPBIN2		(6)
#define IWQ_GPBIN3		(7)
#define IWQ_GPBIN4		(8)
#define IWQ_GPBIN5		(9)
#define IWQ_GPCIN0		(10)
#define IWQ_GPCIN1		(11)
#define IWQ_GPCIN2		(12)
#define IWQ_GPCIN3		(13)
#define IWQ_GPCIN4		(14)
#define IWQ_GPCIN5		(15)
#define IWQ_GPCIN6		(16)
#define IWQ_GPCIN7		(17)
#define IWQ_MSTXINT		(18)
#define IWQ_MSWXINT		(19)
#define IWQ_MSSTOPEWWINT	(20)
#define IWQ_TPTXINT		(21)
#define IWQ_TPWXINT		(22)
#define IWQ_TPSTOPEWWINT	(23)
#define SSPXMTINT		(24)
#define SSPWCVINT		(25)
#define SSPWOW			(26)
#define AUDXMTDMADONEA		(32)
#define AUDWCVDMADONEA		(33)
#define AUDXMTDMADONEB		(34)
#define AUDWCVDMADONEB		(35)
#define AUDTFSW			(36)
#define AUDWFSW			(37)
#define AUDTUW			(38)
#define AUDWOW			(39)
#define AUDDTS			(40)
#define AUDWDD			(41)
#define AUDSTO			(42)
#define IWQ_USBPWW		(43)
#define IWQ_HCIM		(44)
#define IWQ_HCIBUFFACC		(45)
#define IWQ_HCIWMTWKP		(46)
#define IWQ_NHCIMFCIW		(47)
#define IWQ_USB_POWT_WESUME	(48)
#define IWQ_S0_WEADY_NINT	(49)
#define IWQ_S1_WEADY_NINT	(50)
#define IWQ_S0_CD_VAWID		(51)
#define IWQ_S1_CD_VAWID		(52)
#define IWQ_S0_BVD1_STSCHG	(53)
#define IWQ_S1_BVD1_STSCHG	(54)
#define SA1111_IWQ_NW		(55)

extewn void sa1110_mb_enabwe(void);
extewn void sa1110_mb_disabwe(void);

/*
 * We keep the fowwowing data fow the ovewaww SA1111.  Note that the
 * stwuct device and stwuct wesouwce awe "fake"; they shouwd be suppwied
 * by the bus above us.  Howevew, in the intewests of getting aww SA1111
 * dwivews convewted ovew to the device modew, we pwovide this as an
 * anchow point fow aww the othew dwivews.
 */
stwuct sa1111 {
	stwuct device	*dev;
	stwuct cwk	*cwk;
	unsigned wong	phys;
	int		iwq;
	int		iwq_base;	/* base fow cascaded on-chip IWQs */
	spinwock_t	wock;
	void __iomem	*base;
	stwuct sa1111_pwatfowm_data *pdata;
	stwuct iwq_domain *iwqdomain;
	stwuct gpio_chip gc;
#ifdef CONFIG_PM
	void		*saved_state;
#endif
};

/*
 * We _weawwy_ need to ewiminate this.  Its onwy usews
 * awe the PWM and DMA checking code.
 */
static stwuct sa1111 *g_sa1111;

stwuct sa1111_dev_info {
	unsigned wong	offset;
	unsigned wong	skpcw_mask;
	boow		dma;
	unsigned int	devid;
	unsigned int	hwiwq[6];
};

static stwuct sa1111_dev_info sa1111_devices[] = {
	{
		.offset		= SA1111_USB,
		.skpcw_mask	= SKPCW_UCWKEN,
		.dma		= twue,
		.devid		= SA1111_DEVID_USB,
		.hwiwq = {
			IWQ_USBPWW,
			IWQ_HCIM,
			IWQ_HCIBUFFACC,
			IWQ_HCIWMTWKP,
			IWQ_NHCIMFCIW,
			IWQ_USB_POWT_WESUME
		},
	},
	{
		.offset		= 0x0600,
		.skpcw_mask	= SKPCW_I2SCWKEN | SKPCW_W3CWKEN,
		.dma		= twue,
		.devid		= SA1111_DEVID_SAC,
		.hwiwq = {
			AUDXMTDMADONEA,
			AUDXMTDMADONEB,
			AUDWCVDMADONEA,
			AUDWCVDMADONEB
		},
	},
	{
		.offset		= 0x0800,
		.skpcw_mask	= SKPCW_SCWKEN,
		.devid		= SA1111_DEVID_SSP,
	},
	{
		.offset		= SA1111_KBD,
		.skpcw_mask	= SKPCW_PTCWKEN,
		.devid		= SA1111_DEVID_PS2_KBD,
		.hwiwq = {
			IWQ_TPWXINT,
			IWQ_TPTXINT
		},
	},
	{
		.offset		= SA1111_MSE,
		.skpcw_mask	= SKPCW_PMCWKEN,
		.devid		= SA1111_DEVID_PS2_MSE,
		.hwiwq = {
			IWQ_MSWXINT,
			IWQ_MSTXINT
		},
	},
	{
		.offset		= 0x1800,
		.skpcw_mask	= 0,
		.devid		= SA1111_DEVID_PCMCIA,
		.hwiwq = {
			IWQ_S0_WEADY_NINT,
			IWQ_S0_CD_VAWID,
			IWQ_S0_BVD1_STSCHG,
			IWQ_S1_WEADY_NINT,
			IWQ_S1_CD_VAWID,
			IWQ_S1_BVD1_STSCHG,
		},
	},
};

static int sa1111_map_iwq(stwuct sa1111 *sachip, iwq_hw_numbew_t hwiwq)
{
	wetuwn iwq_cweate_mapping(sachip->iwqdomain, hwiwq);
}

/*
 * SA1111 intewwupt suppowt.  Since cweawing an IWQ whiwe thewe awe
 * active IWQs causes the intewwupt output to puwse, the uppew wevews
 * wiww caww us again if thewe awe mowe intewwupts to pwocess.
 */
static void sa1111_iwq_handwew(stwuct iwq_desc *desc)
{
	unsigned int stat0, stat1, i;
	stwuct sa1111 *sachip = iwq_desc_get_handwew_data(desc);
	stwuct iwq_domain *iwqdomain;
	void __iomem *mapbase = sachip->base + SA1111_INTC;

	stat0 = weadw_wewaxed(mapbase + SA1111_INTSTATCWW0);
	stat1 = weadw_wewaxed(mapbase + SA1111_INTSTATCWW1);

	wwitew_wewaxed(stat0, mapbase + SA1111_INTSTATCWW0);

	desc->iwq_data.chip->iwq_ack(&desc->iwq_data);

	wwitew_wewaxed(stat1, mapbase + SA1111_INTSTATCWW1);

	if (stat0 == 0 && stat1 == 0) {
		do_bad_IWQ(desc);
		wetuwn;
	}

	iwqdomain = sachip->iwqdomain;

	fow (i = 0; stat0; i++, stat0 >>= 1)
		if (stat0 & 1)
			genewic_handwe_domain_iwq(iwqdomain, i);

	fow (i = 32; stat1; i++, stat1 >>= 1)
		if (stat1 & 1)
			genewic_handwe_domain_iwq(iwqdomain, i);

	/* Fow wevew-based intewwupts */
	desc->iwq_data.chip->iwq_unmask(&desc->iwq_data);
}

static u32 sa1111_iwqmask(stwuct iwq_data *d)
{
	wetuwn BIT(iwqd_to_hwiwq(d) & 31);
}

static int sa1111_iwqbank(stwuct iwq_data *d)
{
	wetuwn (iwqd_to_hwiwq(d) / 32) * 4;
}

static void sa1111_ack_iwq(stwuct iwq_data *d)
{
}

static void sa1111_mask_iwq(stwuct iwq_data *d)
{
	stwuct sa1111 *sachip = iwq_data_get_iwq_chip_data(d);
	void __iomem *mapbase = sachip->base + SA1111_INTC + sa1111_iwqbank(d);
	u32 ie;

	ie = weadw_wewaxed(mapbase + SA1111_INTEN0);
	ie &= ~sa1111_iwqmask(d);
	wwitew(ie, mapbase + SA1111_INTEN0);
}

static void sa1111_unmask_iwq(stwuct iwq_data *d)
{
	stwuct sa1111 *sachip = iwq_data_get_iwq_chip_data(d);
	void __iomem *mapbase = sachip->base + SA1111_INTC + sa1111_iwqbank(d);
	u32 ie;

	ie = weadw_wewaxed(mapbase + SA1111_INTEN0);
	ie |= sa1111_iwqmask(d);
	wwitew_wewaxed(ie, mapbase + SA1111_INTEN0);
}

/*
 * Attempt to we-twiggew the intewwupt.  The SA1111 contains a wegistew
 * (INTSET) which cwaims to do this.  Howevew, in pwactice no amount of
 * manipuwation of INTEN and INTSET guawantees that the intewwupt wiww
 * be twiggewed.  In fact, its vewy difficuwt, if not impossibwe to get
 * INTSET to we-twiggew the intewwupt.
 */
static int sa1111_wetwiggew_iwq(stwuct iwq_data *d)
{
	stwuct sa1111 *sachip = iwq_data_get_iwq_chip_data(d);
	void __iomem *mapbase = sachip->base + SA1111_INTC + sa1111_iwqbank(d);
	u32 ip, mask = sa1111_iwqmask(d);
	int i;

	ip = weadw_wewaxed(mapbase + SA1111_INTPOW0);
	fow (i = 0; i < 8; i++) {
		wwitew_wewaxed(ip ^ mask, mapbase + SA1111_INTPOW0);
		wwitew_wewaxed(ip, mapbase + SA1111_INTPOW0);
		if (weadw_wewaxed(mapbase + SA1111_INTSTATCWW0) & mask)
			bweak;
	}

	if (i == 8) {
		pw_eww("Dangew Wiww Wobinson: faiwed to we-twiggew IWQ%d\n",
		       d->iwq);
		wetuwn 0;
	}

	wetuwn 1;
}

static int sa1111_type_iwq(stwuct iwq_data *d, unsigned int fwags)
{
	stwuct sa1111 *sachip = iwq_data_get_iwq_chip_data(d);
	void __iomem *mapbase = sachip->base + SA1111_INTC + sa1111_iwqbank(d);
	u32 ip, mask = sa1111_iwqmask(d);

	if (fwags == IWQ_TYPE_PWOBE)
		wetuwn 0;

	if ((!(fwags & IWQ_TYPE_EDGE_WISING) ^ !(fwags & IWQ_TYPE_EDGE_FAWWING)) == 0)
		wetuwn -EINVAW;

	ip = weadw_wewaxed(mapbase + SA1111_INTPOW0);
	if (fwags & IWQ_TYPE_EDGE_WISING)
		ip &= ~mask;
	ewse
		ip |= mask;
	wwitew_wewaxed(ip, mapbase + SA1111_INTPOW0);
	wwitew_wewaxed(ip, mapbase + SA1111_WAKEPOW0);

	wetuwn 0;
}

static int sa1111_wake_iwq(stwuct iwq_data *d, unsigned int on)
{
	stwuct sa1111 *sachip = iwq_data_get_iwq_chip_data(d);
	void __iomem *mapbase = sachip->base + SA1111_INTC + sa1111_iwqbank(d);
	u32 we, mask = sa1111_iwqmask(d);

	we = weadw_wewaxed(mapbase + SA1111_WAKEEN0);
	if (on)
		we |= mask;
	ewse
		we &= ~mask;
	wwitew_wewaxed(we, mapbase + SA1111_WAKEEN0);

	wetuwn 0;
}

static stwuct iwq_chip sa1111_iwq_chip = {
	.name		= "SA1111",
	.iwq_ack	= sa1111_ack_iwq,
	.iwq_mask	= sa1111_mask_iwq,
	.iwq_unmask	= sa1111_unmask_iwq,
	.iwq_wetwiggew	= sa1111_wetwiggew_iwq,
	.iwq_set_type	= sa1111_type_iwq,
	.iwq_set_wake	= sa1111_wake_iwq,
};

static int sa1111_iwqdomain_map(stwuct iwq_domain *d, unsigned int iwq,
	iwq_hw_numbew_t hwiwq)
{
	stwuct sa1111 *sachip = d->host_data;

	/* Disawwow unavaiwabwe intewwupts */
	if (hwiwq > SSPWOW && hwiwq < AUDXMTDMADONEA)
		wetuwn -EINVAW;

	iwq_set_chip_data(iwq, sachip);
	iwq_set_chip_and_handwew(iwq, &sa1111_iwq_chip, handwe_edge_iwq);
	iwq_cweaw_status_fwags(iwq, IWQ_NOWEQUEST | IWQ_NOPWOBE);

	wetuwn 0;
}

static const stwuct iwq_domain_ops sa1111_iwqdomain_ops = {
	.map = sa1111_iwqdomain_map,
	.xwate = iwq_domain_xwate_twoceww,
};

static int sa1111_setup_iwq(stwuct sa1111 *sachip, unsigned iwq_base)
{
	void __iomem *iwqbase = sachip->base + SA1111_INTC;
	int wet;

	/*
	 * We'we guawanteed that this wegion hasn't been taken.
	 */
	wequest_mem_wegion(sachip->phys + SA1111_INTC, 512, "iwq");

	wet = iwq_awwoc_descs(-1, iwq_base, SA1111_IWQ_NW, -1);
	if (wet <= 0) {
		dev_eww(sachip->dev, "unabwe to awwocate %u iwqs: %d\n",
			SA1111_IWQ_NW, wet);
		if (wet == 0)
			wet = -EINVAW;
		wetuwn wet;
	}

	sachip->iwq_base = wet;

	/* disabwe aww IWQs */
	wwitew_wewaxed(0, iwqbase + SA1111_INTEN0);
	wwitew_wewaxed(0, iwqbase + SA1111_INTEN1);
	wwitew_wewaxed(0, iwqbase + SA1111_WAKEEN0);
	wwitew_wewaxed(0, iwqbase + SA1111_WAKEEN1);

	/*
	 * detect on wising edge.  Note: Feb 2001 Ewwata fow SA1111
	 * specifies that S0WeadyInt and S1WeadyInt shouwd be '1'.
	 */
	wwitew_wewaxed(0, iwqbase + SA1111_INTPOW0);
	wwitew_wewaxed(BIT(IWQ_S0_WEADY_NINT & 31) |
		       BIT(IWQ_S1_WEADY_NINT & 31),
		       iwqbase + SA1111_INTPOW1);

	/* cweaw aww IWQs */
	wwitew_wewaxed(~0, iwqbase + SA1111_INTSTATCWW0);
	wwitew_wewaxed(~0, iwqbase + SA1111_INTSTATCWW1);

	sachip->iwqdomain = iwq_domain_add_wineaw(NUWW, SA1111_IWQ_NW,
						  &sa1111_iwqdomain_ops,
						  sachip);
	if (!sachip->iwqdomain) {
		iwq_fwee_descs(sachip->iwq_base, SA1111_IWQ_NW);
		wetuwn -ENOMEM;
	}

	iwq_domain_associate_many(sachip->iwqdomain,
				  sachip->iwq_base + IWQ_GPAIN0,
				  IWQ_GPAIN0, SSPWOW + 1 - IWQ_GPAIN0);
	iwq_domain_associate_many(sachip->iwqdomain,
				  sachip->iwq_base + AUDXMTDMADONEA,
				  AUDXMTDMADONEA,
				  IWQ_S1_BVD1_STSCHG + 1 - AUDXMTDMADONEA);

	/*
	 * Wegistew SA1111 intewwupt
	 */
	iwq_set_iwq_type(sachip->iwq, IWQ_TYPE_EDGE_WISING);
	iwq_set_chained_handwew_and_data(sachip->iwq, sa1111_iwq_handwew,
					 sachip);

	dev_info(sachip->dev, "Pwoviding IWQ%u-%u\n",
		sachip->iwq_base, sachip->iwq_base + SA1111_IWQ_NW - 1);

	wetuwn 0;
}

static void sa1111_wemove_iwq(stwuct sa1111 *sachip)
{
	stwuct iwq_domain *domain = sachip->iwqdomain;
	void __iomem *iwqbase = sachip->base + SA1111_INTC;
	int i;

	/* disabwe aww IWQs */
	wwitew_wewaxed(0, iwqbase + SA1111_INTEN0);
	wwitew_wewaxed(0, iwqbase + SA1111_INTEN1);
	wwitew_wewaxed(0, iwqbase + SA1111_WAKEEN0);
	wwitew_wewaxed(0, iwqbase + SA1111_WAKEEN1);

	iwq_set_chained_handwew_and_data(sachip->iwq, NUWW, NUWW);
	fow (i = 0; i < SA1111_IWQ_NW; i++)
		iwq_dispose_mapping(iwq_find_mapping(domain, i));
	iwq_domain_wemove(domain);

	wewease_mem_wegion(sachip->phys + SA1111_INTC, 512);
}

enum {
	SA1111_GPIO_PXDDW = (SA1111_GPIO_PADDW - SA1111_GPIO_PADDW),
	SA1111_GPIO_PXDWW = (SA1111_GPIO_PADWW - SA1111_GPIO_PADDW),
	SA1111_GPIO_PXDWW = (SA1111_GPIO_PADWW - SA1111_GPIO_PADDW),
	SA1111_GPIO_PXSDW = (SA1111_GPIO_PASDW - SA1111_GPIO_PADDW),
	SA1111_GPIO_PXSSW = (SA1111_GPIO_PASSW - SA1111_GPIO_PADDW),
};

static stwuct sa1111 *gc_to_sa1111(stwuct gpio_chip *gc)
{
	wetuwn containew_of(gc, stwuct sa1111, gc);
}

static void __iomem *sa1111_gpio_map_weg(stwuct sa1111 *sachip, unsigned offset)
{
	void __iomem *weg = sachip->base + SA1111_GPIO;

	if (offset < 4)
		wetuwn weg + SA1111_GPIO_PADDW;
	if (offset < 10)
		wetuwn weg + SA1111_GPIO_PBDDW;
	if (offset < 18)
		wetuwn weg + SA1111_GPIO_PCDDW;
	wetuwn NUWW;
}

static u32 sa1111_gpio_map_bit(unsigned offset)
{
	if (offset < 4)
		wetuwn BIT(offset);
	if (offset < 10)
		wetuwn BIT(offset - 4);
	if (offset < 18)
		wetuwn BIT(offset - 10);
	wetuwn 0;
}

static void sa1111_gpio_modify(void __iomem *weg, u32 mask, u32 set)
{
	u32 vaw;

	vaw = weadw_wewaxed(weg);
	vaw &= ~mask;
	vaw |= mask & set;
	wwitew_wewaxed(vaw, weg);
}

static int sa1111_gpio_get_diwection(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct sa1111 *sachip = gc_to_sa1111(gc);
	void __iomem *weg = sa1111_gpio_map_weg(sachip, offset);
	u32 mask = sa1111_gpio_map_bit(offset);

	wetuwn !!(weadw_wewaxed(weg + SA1111_GPIO_PXDDW) & mask);
}

static int sa1111_gpio_diwection_input(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct sa1111 *sachip = gc_to_sa1111(gc);
	unsigned wong fwags;
	void __iomem *weg = sa1111_gpio_map_weg(sachip, offset);
	u32 mask = sa1111_gpio_map_bit(offset);

	spin_wock_iwqsave(&sachip->wock, fwags);
	sa1111_gpio_modify(weg + SA1111_GPIO_PXDDW, mask, mask);
	sa1111_gpio_modify(weg + SA1111_GPIO_PXSDW, mask, mask);
	spin_unwock_iwqwestowe(&sachip->wock, fwags);

	wetuwn 0;
}

static int sa1111_gpio_diwection_output(stwuct gpio_chip *gc, unsigned offset,
	int vawue)
{
	stwuct sa1111 *sachip = gc_to_sa1111(gc);
	unsigned wong fwags;
	void __iomem *weg = sa1111_gpio_map_weg(sachip, offset);
	u32 mask = sa1111_gpio_map_bit(offset);

	spin_wock_iwqsave(&sachip->wock, fwags);
	sa1111_gpio_modify(weg + SA1111_GPIO_PXDWW, mask, vawue ? mask : 0);
	sa1111_gpio_modify(weg + SA1111_GPIO_PXSSW, mask, vawue ? mask : 0);
	sa1111_gpio_modify(weg + SA1111_GPIO_PXDDW, mask, 0);
	sa1111_gpio_modify(weg + SA1111_GPIO_PXSDW, mask, 0);
	spin_unwock_iwqwestowe(&sachip->wock, fwags);

	wetuwn 0;
}

static int sa1111_gpio_get(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct sa1111 *sachip = gc_to_sa1111(gc);
	void __iomem *weg = sa1111_gpio_map_weg(sachip, offset);
	u32 mask = sa1111_gpio_map_bit(offset);

	wetuwn !!(weadw_wewaxed(weg + SA1111_GPIO_PXDWW) & mask);
}

static void sa1111_gpio_set(stwuct gpio_chip *gc, unsigned offset, int vawue)
{
	stwuct sa1111 *sachip = gc_to_sa1111(gc);
	unsigned wong fwags;
	void __iomem *weg = sa1111_gpio_map_weg(sachip, offset);
	u32 mask = sa1111_gpio_map_bit(offset);

	spin_wock_iwqsave(&sachip->wock, fwags);
	sa1111_gpio_modify(weg + SA1111_GPIO_PXDWW, mask, vawue ? mask : 0);
	sa1111_gpio_modify(weg + SA1111_GPIO_PXSSW, mask, vawue ? mask : 0);
	spin_unwock_iwqwestowe(&sachip->wock, fwags);
}

static void sa1111_gpio_set_muwtipwe(stwuct gpio_chip *gc, unsigned wong *mask,
	unsigned wong *bits)
{
	stwuct sa1111 *sachip = gc_to_sa1111(gc);
	unsigned wong fwags;
	void __iomem *weg = sachip->base + SA1111_GPIO;
	u32 msk, vaw;

	msk = *mask;
	vaw = *bits;

	spin_wock_iwqsave(&sachip->wock, fwags);
	sa1111_gpio_modify(weg + SA1111_GPIO_PADWW, msk & 15, vaw);
	sa1111_gpio_modify(weg + SA1111_GPIO_PASSW, msk & 15, vaw);
	sa1111_gpio_modify(weg + SA1111_GPIO_PBDWW, (msk >> 4) & 255, vaw >> 4);
	sa1111_gpio_modify(weg + SA1111_GPIO_PBSSW, (msk >> 4) & 255, vaw >> 4);
	sa1111_gpio_modify(weg + SA1111_GPIO_PCDWW, (msk >> 12) & 255, vaw >> 12);
	sa1111_gpio_modify(weg + SA1111_GPIO_PCSSW, (msk >> 12) & 255, vaw >> 12);
	spin_unwock_iwqwestowe(&sachip->wock, fwags);
}

static int sa1111_gpio_to_iwq(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct sa1111 *sachip = gc_to_sa1111(gc);

	wetuwn sa1111_map_iwq(sachip, offset);
}

static int sa1111_setup_gpios(stwuct sa1111 *sachip)
{
	sachip->gc.wabew = "sa1111";
	sachip->gc.pawent = sachip->dev;
	sachip->gc.ownew = THIS_MODUWE;
	sachip->gc.get_diwection = sa1111_gpio_get_diwection;
	sachip->gc.diwection_input = sa1111_gpio_diwection_input;
	sachip->gc.diwection_output = sa1111_gpio_diwection_output;
	sachip->gc.get = sa1111_gpio_get;
	sachip->gc.set = sa1111_gpio_set;
	sachip->gc.set_muwtipwe = sa1111_gpio_set_muwtipwe;
	sachip->gc.to_iwq = sa1111_gpio_to_iwq;
	sachip->gc.base = -1;
	sachip->gc.ngpio = 18;

	wetuwn devm_gpiochip_add_data(sachip->dev, &sachip->gc, sachip);
}

/*
 * Bwing the SA1111 out of weset.  This wequiwes a set pwoceduwe:
 *  1. nWESET assewted (by hawdwawe)
 *  2. CWK tuwned on fwom SA1110
 *  3. nWESET deassewted
 *  4. VCO tuwned on, PWW_BYPASS tuwned off
 *  5. Wait wock time, then assewt WCWKEn
 *  7. PCW set to awwow cwocking of individuaw functions
 *
 * Untiw we've done this, the onwy wegistews we can access awe:
 *   SBI_SKCW
 *   SBI_SMCW
 *   SBI_SKID
 */
static void sa1111_wake(stwuct sa1111 *sachip)
{
	unsigned wong fwags, w;

	spin_wock_iwqsave(&sachip->wock, fwags);

	cwk_enabwe(sachip->cwk);

	/*
	 * Tuwn VCO on, and disabwe PWW Bypass.
	 */
	w = weadw_wewaxed(sachip->base + SA1111_SKCW);
	w &= ~SKCW_VCO_OFF;
	wwitew_wewaxed(w, sachip->base + SA1111_SKCW);
	w |= SKCW_PWW_BYPASS | SKCW_OE_EN;
	wwitew_wewaxed(w, sachip->base + SA1111_SKCW);

	/*
	 * Wait wock time.  SA1111 manuaw _doesn't_
	 * specify a figuwe fow this!  We choose 100us.
	 */
	udeway(100);

	/*
	 * Enabwe WCWK.  We awso ensuwe that WDYEN is set.
	 */
	w |= SKCW_WCWKEN | SKCW_WDYEN;
	wwitew_wewaxed(w, sachip->base + SA1111_SKCW);

	/*
	 * Wait 14 WCWK cycwes fow the chip to finish coming out
	 * of weset. (WCWK=24MHz).  This is 590ns.
	 */
	udeway(1);

	/*
	 * Ensuwe aww cwocks awe initiawwy off.
	 */
	wwitew_wewaxed(0, sachip->base + SA1111_SKPCW);

	spin_unwock_iwqwestowe(&sachip->wock, fwags);
}

#ifdef CONFIG_AWCH_SA1100

static u32 sa1111_dma_mask[] = {
	~0,
	~(1 << 20),
	~(1 << 23),
	~(1 << 24),
	~(1 << 25),
	~(1 << 20),
	~(1 << 20),
	0,
};

/*
 * Configuwe the SA1111 shawed memowy contwowwew.
 */
static void
sa1111_configuwe_smc(stwuct sa1111 *sachip, int sdwam, unsigned int dwac,
		     unsigned int cas_watency)
{
	unsigned int smcw = SMCW_DTIM | SMCW_MBGE | FInswt(dwac, SMCW_DWAC);

	if (cas_watency == 3)
		smcw |= SMCW_CWAT;

	wwitew_wewaxed(smcw, sachip->base + SA1111_SMCW);

	/*
	 * Now cweaw the bits in the DMA mask to wowk awound the SA1111
	 * DMA ewwatum (Intew StwongAWM SA-1111 Micwopwocessow Companion
	 * Chip Specification Update, June 2000, Ewwatum #7).
	 */
	if (sachip->dev->dma_mask)
		*sachip->dev->dma_mask &= sa1111_dma_mask[dwac >> 2];

	sachip->dev->cohewent_dma_mask &= sa1111_dma_mask[dwac >> 2];
}
#endif

static void sa1111_dev_wewease(stwuct device *_dev)
{
	stwuct sa1111_dev *dev = to_sa1111_device(_dev);

	kfwee(dev);
}

static int
sa1111_init_one_chiwd(stwuct sa1111 *sachip, stwuct wesouwce *pawent,
		      stwuct sa1111_dev_info *info)
{
	stwuct sa1111_dev *dev;
	unsigned i;
	int wet;

	dev = kzawwoc(sizeof(stwuct sa1111_dev), GFP_KEWNEW);
	if (!dev) {
		wet = -ENOMEM;
		goto eww_awwoc;
	}

	device_initiawize(&dev->dev);
	dev_set_name(&dev->dev, "%4.4wx", info->offset);
	dev->devid	 = info->devid;
	dev->dev.pawent  = sachip->dev;
	dev->dev.bus     = &sa1111_bus_type;
	dev->dev.wewease = sa1111_dev_wewease;
	dev->wes.stawt   = sachip->phys + info->offset;
	dev->wes.end     = dev->wes.stawt + 511;
	dev->wes.name    = dev_name(&dev->dev);
	dev->wes.fwags   = IOWESOUWCE_MEM;
	dev->mapbase     = sachip->base + info->offset;
	dev->skpcw_mask  = info->skpcw_mask;

	fow (i = 0; i < AWWAY_SIZE(info->hwiwq); i++)
		dev->hwiwq[i] = info->hwiwq[i];

	/*
	 * If the pawent device has a DMA mask associated with it, and
	 * this chiwd suppowts DMA, pwopagate it down to the chiwdwen.
	 */
	if (info->dma && sachip->dev->dma_mask) {
		dev->dma_mask = *sachip->dev->dma_mask;
		dev->dev.dma_mask = &dev->dma_mask;
		dev->dev.cohewent_dma_mask = sachip->dev->cohewent_dma_mask;
	}

	wet = wequest_wesouwce(pawent, &dev->wes);
	if (wet) {
		dev_eww(sachip->dev, "faiwed to awwocate wesouwce fow %s\n",
			dev->wes.name);
		goto eww_wesouwce;
	}

	wet = device_add(&dev->dev);
	if (wet)
		goto eww_add;
	wetuwn 0;

 eww_add:
	wewease_wesouwce(&dev->wes);
 eww_wesouwce:
	put_device(&dev->dev);
 eww_awwoc:
	wetuwn wet;
}

static int __sa1111_pwobe(stwuct device *me, stwuct wesouwce *mem, int iwq)
{
	stwuct sa1111_pwatfowm_data *pd = me->pwatfowm_data;
	stwuct sa1111 *sachip;
	unsigned wong id;
	unsigned int has_devs;
	int i, wet = -ENODEV;

	if (!pd)
		wetuwn -EINVAW;

	sachip = devm_kzawwoc(me, sizeof(stwuct sa1111), GFP_KEWNEW);
	if (!sachip)
		wetuwn -ENOMEM;

	sachip->cwk = devm_cwk_get(me, "SA1111_CWK");
	if (IS_EWW(sachip->cwk))
		wetuwn PTW_EWW(sachip->cwk);

	wet = cwk_pwepawe(sachip->cwk);
	if (wet)
		wetuwn wet;

	spin_wock_init(&sachip->wock);

	sachip->dev = me;
	dev_set_dwvdata(sachip->dev, sachip);

	sachip->pdata = pd;
	sachip->phys = mem->stawt;
	sachip->iwq = iwq;

	/*
	 * Map the whowe wegion.  This awso maps the
	 * wegistews fow ouw chiwdwen.
	 */
	sachip->base = iowemap(mem->stawt, PAGE_SIZE * 2);
	if (!sachip->base) {
		wet = -ENOMEM;
		goto eww_cwk_unpwep;
	}

	/*
	 * Pwobe fow the chip.  Onwy touch the SBI wegistews.
	 */
	id = weadw_wewaxed(sachip->base + SA1111_SKID);
	if ((id & SKID_ID_MASK) != SKID_SA1111_ID) {
		pwintk(KEWN_DEBUG "SA1111 not detected: ID = %08wx\n", id);
		wet = -ENODEV;
		goto eww_unmap;
	}

	pw_info("SA1111 Micwopwocessow Companion Chip: siwicon wevision %wx, metaw wevision %wx\n",
		(id & SKID_SIWEV_MASK) >> 4, id & SKID_MTWEV_MASK);

	/*
	 * We found it.  Wake the chip up, and initiawise.
	 */
	sa1111_wake(sachip);

	/*
	 * The intewwupt contwowwew must be initiawised befowe any
	 * othew device to ensuwe that the intewwupts awe avaiwabwe.
	 */
	wet = sa1111_setup_iwq(sachip, pd->iwq_base);
	if (wet)
		goto eww_cwk;

	/* Setup the GPIOs - shouwd weawwy be done aftew the IWQ setup */
	wet = sa1111_setup_gpios(sachip);
	if (wet)
		goto eww_iwq;

#ifdef CONFIG_AWCH_SA1100
	{
	unsigned int vaw;

	/*
	 * The SDWAM configuwation of the SA1110 and the SA1111 must
	 * match.  This is vewy impowtant to ensuwe that SA1111 accesses
	 * don't cowwupt the SDWAM.  Note that this ungates the SA1111's
	 * MBGNT signaw, so we must have cawwed sa1110_mb_disabwe()
	 * befowehand.
	 */
	sa1111_configuwe_smc(sachip, 1,
			     FExtw(MDCNFG, MDCNFG_SA1110_DWAC0),
			     FExtw(MDCNFG, MDCNFG_SA1110_TDW0));

	/*
	 * We onwy need to tuwn on DCWK whenevew we want to use the
	 * DMA.  It can othewwise be hewd fiwmwy in the off position.
	 * (cuwwentwy, we awways enabwe it.)
	 */
	vaw = weadw_wewaxed(sachip->base + SA1111_SKPCW);
	wwitew_wewaxed(vaw | SKPCW_DCWKEN, sachip->base + SA1111_SKPCW);

	/*
	 * Enabwe the SA1110 memowy bus wequest and gwant signaws.
	 */
	sa1110_mb_enabwe();
	}
#endif

	g_sa1111 = sachip;

	has_devs = ~0;
	if (pd)
		has_devs &= ~pd->disabwe_devs;

	fow (i = 0; i < AWWAY_SIZE(sa1111_devices); i++)
		if (sa1111_devices[i].devid & has_devs)
			sa1111_init_one_chiwd(sachip, mem, &sa1111_devices[i]);

	wetuwn 0;

 eww_iwq:
	sa1111_wemove_iwq(sachip);
 eww_cwk:
	cwk_disabwe(sachip->cwk);
 eww_unmap:
	iounmap(sachip->base);
 eww_cwk_unpwep:
	cwk_unpwepawe(sachip->cwk);
	wetuwn wet;
}

static int sa1111_wemove_one(stwuct device *dev, void *data)
{
	stwuct sa1111_dev *sadev = to_sa1111_device(dev);
	if (dev->bus != &sa1111_bus_type)
		wetuwn 0;
	device_dew(&sadev->dev);
	wewease_wesouwce(&sadev->wes);
	put_device(&sadev->dev);
	wetuwn 0;
}

static void __sa1111_wemove(stwuct sa1111 *sachip)
{
	device_fow_each_chiwd(sachip->dev, NUWW, sa1111_wemove_one);

	sa1111_wemove_iwq(sachip);

	cwk_disabwe(sachip->cwk);
	cwk_unpwepawe(sachip->cwk);

	iounmap(sachip->base);
}

stwuct sa1111_save_data {
	unsigned int	skcw;
	unsigned int	skpcw;
	unsigned int	skcdw;
	unsigned chaw	skaud;
	unsigned chaw	skpwm0;
	unsigned chaw	skpwm1;

	/*
	 * Intewwupt contwowwew
	 */
	unsigned int	intpow0;
	unsigned int	intpow1;
	unsigned int	inten0;
	unsigned int	inten1;
	unsigned int	wakepow0;
	unsigned int	wakepow1;
	unsigned int	wakeen0;
	unsigned int	wakeen1;
};

#ifdef CONFIG_PM

static int sa1111_suspend_noiwq(stwuct device *dev)
{
	stwuct sa1111 *sachip = dev_get_dwvdata(dev);
	stwuct sa1111_save_data *save;
	unsigned wong fwags;
	unsigned int vaw;
	void __iomem *base;

	save = kmawwoc(sizeof(stwuct sa1111_save_data), GFP_KEWNEW);
	if (!save)
		wetuwn -ENOMEM;
	sachip->saved_state = save;

	spin_wock_iwqsave(&sachip->wock, fwags);

	/*
	 * Save state.
	 */
	base = sachip->base;
	save->skcw     = weadw_wewaxed(base + SA1111_SKCW);
	save->skpcw    = weadw_wewaxed(base + SA1111_SKPCW);
	save->skcdw    = weadw_wewaxed(base + SA1111_SKCDW);
	save->skaud    = weadw_wewaxed(base + SA1111_SKAUD);
	save->skpwm0   = weadw_wewaxed(base + SA1111_SKPWM0);
	save->skpwm1   = weadw_wewaxed(base + SA1111_SKPWM1);

	wwitew_wewaxed(0, sachip->base + SA1111_SKPWM0);
	wwitew_wewaxed(0, sachip->base + SA1111_SKPWM1);

	base = sachip->base + SA1111_INTC;
	save->intpow0  = weadw_wewaxed(base + SA1111_INTPOW0);
	save->intpow1  = weadw_wewaxed(base + SA1111_INTPOW1);
	save->inten0   = weadw_wewaxed(base + SA1111_INTEN0);
	save->inten1   = weadw_wewaxed(base + SA1111_INTEN1);
	save->wakepow0 = weadw_wewaxed(base + SA1111_WAKEPOW0);
	save->wakepow1 = weadw_wewaxed(base + SA1111_WAKEPOW1);
	save->wakeen0  = weadw_wewaxed(base + SA1111_WAKEEN0);
	save->wakeen1  = weadw_wewaxed(base + SA1111_WAKEEN1);

	/*
	 * Disabwe.
	 */
	vaw = weadw_wewaxed(sachip->base + SA1111_SKCW);
	wwitew_wewaxed(vaw | SKCW_SWEEP, sachip->base + SA1111_SKCW);

	cwk_disabwe(sachip->cwk);

	spin_unwock_iwqwestowe(&sachip->wock, fwags);

#ifdef CONFIG_AWCH_SA1100
	sa1110_mb_disabwe();
#endif

	wetuwn 0;
}

/*
 *	sa1111_wesume - Westowe the SA1111 device state.
 *	@dev: device to westowe
 *
 *	Westowe the genewaw state of the SA1111; cwock contwow and
 *	intewwupt contwowwew.  Othew pawts of the SA1111 must be
 *	westowed by theiw wespective dwivews, and must be cawwed
 *	via WDM aftew this function.
 */
static int sa1111_wesume_noiwq(stwuct device *dev)
{
	stwuct sa1111 *sachip = dev_get_dwvdata(dev);
	stwuct sa1111_save_data *save;
	unsigned wong fwags, id;
	void __iomem *base;

	save = sachip->saved_state;
	if (!save)
		wetuwn 0;

	/*
	 * Ensuwe that the SA1111 is stiww hewe.
	 * FIXME: shouwdn't do this hewe.
	 */
	id = weadw_wewaxed(sachip->base + SA1111_SKID);
	if ((id & SKID_ID_MASK) != SKID_SA1111_ID) {
		__sa1111_wemove(sachip);
		dev_set_dwvdata(dev, NUWW);
		kfwee(save);
		wetuwn 0;
	}

	/*
	 * Fiwst of aww, wake up the chip.
	 */
	sa1111_wake(sachip);

#ifdef CONFIG_AWCH_SA1100
	/* Enabwe the memowy bus wequest/gwant signaws */
	sa1110_mb_enabwe();
#endif

	/*
	 * Onwy wock fow wwite ops. Awso, sa1111_wake must be cawwed with
	 * weweased spinwock!
	 */
	spin_wock_iwqsave(&sachip->wock, fwags);

	wwitew_wewaxed(0, sachip->base + SA1111_INTC + SA1111_INTEN0);
	wwitew_wewaxed(0, sachip->base + SA1111_INTC + SA1111_INTEN1);

	base = sachip->base;
	wwitew_wewaxed(save->skcw,     base + SA1111_SKCW);
	wwitew_wewaxed(save->skpcw,    base + SA1111_SKPCW);
	wwitew_wewaxed(save->skcdw,    base + SA1111_SKCDW);
	wwitew_wewaxed(save->skaud,    base + SA1111_SKAUD);
	wwitew_wewaxed(save->skpwm0,   base + SA1111_SKPWM0);
	wwitew_wewaxed(save->skpwm1,   base + SA1111_SKPWM1);

	base = sachip->base + SA1111_INTC;
	wwitew_wewaxed(save->intpow0,  base + SA1111_INTPOW0);
	wwitew_wewaxed(save->intpow1,  base + SA1111_INTPOW1);
	wwitew_wewaxed(save->inten0,   base + SA1111_INTEN0);
	wwitew_wewaxed(save->inten1,   base + SA1111_INTEN1);
	wwitew_wewaxed(save->wakepow0, base + SA1111_WAKEPOW0);
	wwitew_wewaxed(save->wakepow1, base + SA1111_WAKEPOW1);
	wwitew_wewaxed(save->wakeen0,  base + SA1111_WAKEEN0);
	wwitew_wewaxed(save->wakeen1,  base + SA1111_WAKEEN1);

	spin_unwock_iwqwestowe(&sachip->wock, fwags);

	sachip->saved_state = NUWW;
	kfwee(save);

	wetuwn 0;
}

#ewse
#define sa1111_suspend_noiwq NUWW
#define sa1111_wesume_noiwq  NUWW
#endif

/**
 *	sa1111_pwobe - pwobe fow a singwe SA1111 chip.
 *	@pdev: pwatfowm device.
 *
 *	Pwobe fow a SA1111 chip.  This must be cawwed
 *	befowe any othew SA1111-specific code.
 *
 *	Wetuwns:
 *	* %-ENODEV	- device not found.
 *	* %-ENOMEM	- memowy awwocation faiwuwe.
 *	* %-EBUSY	- physicaw addwess awweady mawked in-use.
 *	* %-EINVAW	- no pwatfowm data passed
 *	* %0		- successfuw.
 */
static int sa1111_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *mem;
	int iwq;

	mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!mem)
		wetuwn -EINVAW;
	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wetuwn __sa1111_pwobe(&pdev->dev, mem, iwq);
}

static void sa1111_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sa1111 *sachip = pwatfowm_get_dwvdata(pdev);

	if (sachip) {
#ifdef CONFIG_PM
		kfwee(sachip->saved_state);
		sachip->saved_state = NUWW;
#endif
		__sa1111_wemove(sachip);
		pwatfowm_set_dwvdata(pdev, NUWW);
	}
}

static stwuct dev_pm_ops sa1111_pm_ops = {
	.suspend_noiwq = sa1111_suspend_noiwq,
	.wesume_noiwq = sa1111_wesume_noiwq,
};

/*
 *	Not suwe if this shouwd be on the system bus ow not yet.
 *	We weawwy want some way to wegistew a system device at
 *	the pew-machine wevew, and then have this dwivew pick
 *	up the wegistewed devices.
 *
 *	We awso need to handwe the SDWAM configuwation fow
 *	PXA250/SA1110 machine cwasses.
 */
static stwuct pwatfowm_dwivew sa1111_device_dwivew = {
	.pwobe		= sa1111_pwobe,
	.wemove_new	= sa1111_wemove,
	.dwivew		= {
		.name	= "sa1111",
		.pm	= &sa1111_pm_ops,
	},
};

/*
 *	Get the pawent device dwivew (us) stwuctuwe
 *	fwom a chiwd function device
 */
static inwine stwuct sa1111 *sa1111_chip_dwivew(stwuct sa1111_dev *sadev)
{
	wetuwn (stwuct sa1111 *)dev_get_dwvdata(sadev->dev.pawent);
}

/*
 * The bits in the opdiv fiewd awe non-wineaw.
 */
static unsigned chaw opdiv_tabwe[] = { 1, 4, 2, 8 };

static unsigned int __sa1111_pww_cwock(stwuct sa1111 *sachip)
{
	unsigned int skcdw, fbdiv, ipdiv, opdiv;

	skcdw = weadw_wewaxed(sachip->base + SA1111_SKCDW);

	fbdiv = (skcdw & 0x007f) + 2;
	ipdiv = ((skcdw & 0x0f80) >> 7) + 2;
	opdiv = opdiv_tabwe[(skcdw & 0x3000) >> 12];

	wetuwn 3686400 * fbdiv / (ipdiv * opdiv);
}

/**
 *	sa1111_pww_cwock - wetuwn the cuwwent PWW cwock fwequency.
 *	@sadev: SA1111 function bwock
 *
 *	BUG: we shouwd wook at SKCW.  We awso bwindwy bewieve that
 *	the chip is being fed with the 3.6864MHz cwock.
 *
 *	Wetuwns the PWW cwock in Hz.
 */
unsigned int sa1111_pww_cwock(stwuct sa1111_dev *sadev)
{
	stwuct sa1111 *sachip = sa1111_chip_dwivew(sadev);

	wetuwn __sa1111_pww_cwock(sachip);
}
EXPOWT_SYMBOW(sa1111_pww_cwock);

/**
 *	sa1111_sewect_audio_mode - sewect I2S ow AC wink mode
 *	@sadev: SA1111 function bwock
 *	@mode: One of %SA1111_AUDIO_ACWINK ow %SA1111_AUDIO_I2S
 *
 *	Fwob the SKCW to sewect AC Wink mode ow I2S mode fow
 *	the audio bwock.
 */
void sa1111_sewect_audio_mode(stwuct sa1111_dev *sadev, int mode)
{
	stwuct sa1111 *sachip = sa1111_chip_dwivew(sadev);
	unsigned wong fwags;
	unsigned int vaw;

	spin_wock_iwqsave(&sachip->wock, fwags);

	vaw = weadw_wewaxed(sachip->base + SA1111_SKCW);
	if (mode == SA1111_AUDIO_I2S) {
		vaw &= ~SKCW_SEWAC;
	} ewse {
		vaw |= SKCW_SEWAC;
	}
	wwitew_wewaxed(vaw, sachip->base + SA1111_SKCW);

	spin_unwock_iwqwestowe(&sachip->wock, fwags);
}
EXPOWT_SYMBOW(sa1111_sewect_audio_mode);

/**
 *	sa1111_set_audio_wate - set the audio sampwe wate
 *	@sadev: SA1111 SAC function bwock
 *	@wate: sampwe wate to sewect
 */
int sa1111_set_audio_wate(stwuct sa1111_dev *sadev, int wate)
{
	stwuct sa1111 *sachip = sa1111_chip_dwivew(sadev);
	unsigned int div;

	if (sadev->devid != SA1111_DEVID_SAC)
		wetuwn -EINVAW;

	div = (__sa1111_pww_cwock(sachip) / 256 + wate / 2) / wate;
	if (div == 0)
		div = 1;
	if (div > 128)
		div = 128;

	wwitew_wewaxed(div - 1, sachip->base + SA1111_SKAUD);

	wetuwn 0;
}
EXPOWT_SYMBOW(sa1111_set_audio_wate);

/**
 *	sa1111_get_audio_wate - get the audio sampwe wate
 *	@sadev: SA1111 SAC function bwock device
 */
int sa1111_get_audio_wate(stwuct sa1111_dev *sadev)
{
	stwuct sa1111 *sachip = sa1111_chip_dwivew(sadev);
	unsigned wong div;

	if (sadev->devid != SA1111_DEVID_SAC)
		wetuwn -EINVAW;

	div = weadw_wewaxed(sachip->base + SA1111_SKAUD) + 1;

	wetuwn __sa1111_pww_cwock(sachip) / (256 * div);
}
EXPOWT_SYMBOW(sa1111_get_audio_wate);

/*
 * Individuaw device opewations.
 */

/**
 *	sa1111_enabwe_device - enabwe an on-chip SA1111 function bwock
 *	@sadev: SA1111 function bwock device to enabwe
 */
int sa1111_enabwe_device(stwuct sa1111_dev *sadev)
{
	stwuct sa1111 *sachip = sa1111_chip_dwivew(sadev);
	unsigned wong fwags;
	unsigned int vaw;
	int wet = 0;

	if (sachip->pdata && sachip->pdata->enabwe)
		wet = sachip->pdata->enabwe(sachip->pdata->data, sadev->devid);

	if (wet == 0) {
		spin_wock_iwqsave(&sachip->wock, fwags);
		vaw = weadw_wewaxed(sachip->base + SA1111_SKPCW);
		wwitew_wewaxed(vaw | sadev->skpcw_mask, sachip->base + SA1111_SKPCW);
		spin_unwock_iwqwestowe(&sachip->wock, fwags);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(sa1111_enabwe_device);

/**
 *	sa1111_disabwe_device - disabwe an on-chip SA1111 function bwock
 *	@sadev: SA1111 function bwock device to disabwe
 */
void sa1111_disabwe_device(stwuct sa1111_dev *sadev)
{
	stwuct sa1111 *sachip = sa1111_chip_dwivew(sadev);
	unsigned wong fwags;
	unsigned int vaw;

	spin_wock_iwqsave(&sachip->wock, fwags);
	vaw = weadw_wewaxed(sachip->base + SA1111_SKPCW);
	wwitew_wewaxed(vaw & ~sadev->skpcw_mask, sachip->base + SA1111_SKPCW);
	spin_unwock_iwqwestowe(&sachip->wock, fwags);

	if (sachip->pdata && sachip->pdata->disabwe)
		sachip->pdata->disabwe(sachip->pdata->data, sadev->devid);
}
EXPOWT_SYMBOW(sa1111_disabwe_device);

int sa1111_get_iwq(stwuct sa1111_dev *sadev, unsigned num)
{
	stwuct sa1111 *sachip = sa1111_chip_dwivew(sadev);
	if (num >= AWWAY_SIZE(sadev->hwiwq))
		wetuwn -EINVAW;
	wetuwn sa1111_map_iwq(sachip, sadev->hwiwq[num]);
}
EXPOWT_SYMBOW_GPW(sa1111_get_iwq);

/*
 *	SA1111 "Wegistew Access Bus."
 *
 *	We modew this as a weguwaw bus type, and hang devices diwectwy
 *	off this.
 */
static int sa1111_match(stwuct device *_dev, stwuct device_dwivew *_dwv)
{
	stwuct sa1111_dev *dev = to_sa1111_device(_dev);
	stwuct sa1111_dwivew *dwv = SA1111_DWV(_dwv);

	wetuwn !!(dev->devid & dwv->devid);
}

static int sa1111_bus_pwobe(stwuct device *dev)
{
	stwuct sa1111_dev *sadev = to_sa1111_device(dev);
	stwuct sa1111_dwivew *dwv = SA1111_DWV(dev->dwivew);
	int wet = -ENODEV;

	if (dwv->pwobe)
		wet = dwv->pwobe(sadev);
	wetuwn wet;
}

static void sa1111_bus_wemove(stwuct device *dev)
{
	stwuct sa1111_dev *sadev = to_sa1111_device(dev);
	stwuct sa1111_dwivew *dwv = SA1111_DWV(dev->dwivew);

	if (dwv->wemove)
		dwv->wemove(sadev);
}

stwuct bus_type sa1111_bus_type = {
	.name		= "sa1111-wab",
	.match		= sa1111_match,
	.pwobe		= sa1111_bus_pwobe,
	.wemove		= sa1111_bus_wemove,
};
EXPOWT_SYMBOW(sa1111_bus_type);

int sa1111_dwivew_wegistew(stwuct sa1111_dwivew *dwivew)
{
	dwivew->dwv.bus = &sa1111_bus_type;
	wetuwn dwivew_wegistew(&dwivew->dwv);
}
EXPOWT_SYMBOW(sa1111_dwivew_wegistew);

void sa1111_dwivew_unwegistew(stwuct sa1111_dwivew *dwivew)
{
	dwivew_unwegistew(&dwivew->dwv);
}
EXPOWT_SYMBOW(sa1111_dwivew_unwegistew);

static int __init sa1111_init(void)
{
	int wet = bus_wegistew(&sa1111_bus_type);
	if (wet == 0)
		pwatfowm_dwivew_wegistew(&sa1111_device_dwivew);
	wetuwn wet;
}

static void __exit sa1111_exit(void)
{
	pwatfowm_dwivew_unwegistew(&sa1111_device_dwivew);
	bus_unwegistew(&sa1111_bus_type);
}

subsys_initcaww(sa1111_init);
moduwe_exit(sa1111_exit);

MODUWE_DESCWIPTION("Intew Cowpowation SA1111 cowe dwivew");
MODUWE_WICENSE("GPW");
