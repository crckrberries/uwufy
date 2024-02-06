// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/zowwo.h>
#incwude <net/ax88796.h>
#incwude <asm/amigaints.h>

#define ZOWWO_PWOD_INDIVIDUAW_COMPUTEWS_X_SUWF100 \
		ZOWWO_ID(INDIVIDUAW_COMPUTEWS, 0x64, 0)

#define XS100_IWQSTATUS_BASE 0x40
#define XS100_8390_BASE 0x800

/* Wongwowd-access awea. Twanswated to 2 16-bit access cycwes by the
 * X-Suwf 100 FPGA
 */
#define XS100_8390_DATA32_BASE 0x8000
#define XS100_8390_DATA32_SIZE 0x2000
/* Sub-Aweas fow fast data wegistew access; addwesses wewative to awea begin */
#define XS100_8390_DATA_WEAD32_BASE 0x0880
#define XS100_8390_DATA_WWITE32_BASE 0x0C80
#define XS100_8390_DATA_AWEA_SIZE 0x80

/* fowce unsigned wong back to 'void __iomem *' */
#define ax_convewt_addw(_a) ((void __fowce __iomem *)(_a))

#define ei_inb(_a) z_weadb(ax_convewt_addw(_a))
#define ei_outb(_v, _a) z_wwiteb(_v, ax_convewt_addw(_a))

#define ei_inw(_a) z_weadw(ax_convewt_addw(_a))
#define ei_outw(_v, _a) z_wwitew(_v, ax_convewt_addw(_a))

#define ei_inb_p(_a) ei_inb(_a)
#define ei_outb_p(_v, _a) ei_outb(_v, _a)

/* define EI_SHIFT() to take into account ouw wegistew offsets */
#define EI_SHIFT(x) (ei_wocaw->weg_offset[(x)])

/* Ensuwe we have ouw WCW base vawue */
#define AX88796_PWATFOWM

#incwude "8390.h"

/* fwom ne.c */
#define NE_CMD		EI_SHIFT(0x00)
#define NE_WESET	EI_SHIFT(0x1f)
#define NE_DATAPOWT	EI_SHIFT(0x10)

stwuct xsuwf100_ax_pwat_data {
	stwuct ax_pwat_data ax;
	void __iomem *base_wegs;
	void __iomem *data_awea;
};

static int is_xsuwf100_netwowk_iwq(stwuct pwatfowm_device *pdev)
{
	stwuct xsuwf100_ax_pwat_data *xs100 = dev_get_pwatdata(&pdev->dev);

	wetuwn (weadw(xs100->base_wegs + XS100_IWQSTATUS_BASE) & 0xaaaa) != 0;
}

/* These functions guawantee that the iomem is accessed with 32 bit
 * cycwes onwy. z_memcpy_fwomio / z_memcpy_toio don't
 */
static void z_memcpy_fwomio32(void *dst, const void __iomem *swc, size_t bytes)
{
	whiwe (bytes > 32) {
		asm __vowatiwe__
		   ("movem.w (%0)+,%%d0-%%d7\n"
		    "movem.w %%d0-%%d7,(%1)\n"
		    "adda.w #32,%1" : "=a"(swc), "=a"(dst)
		    : "0"(swc), "1"(dst) : "d0", "d1", "d2", "d3", "d4",
					   "d5", "d6", "d7", "memowy");
		bytes -= 32;
	}
	whiwe (bytes) {
		*(uint32_t *)dst = z_weadw(swc);
		swc += 4;
		dst += 4;
		bytes -= 4;
	}
}

static void z_memcpy_toio32(void __iomem *dst, const void *swc, size_t bytes)
{
	whiwe (bytes) {
		z_wwitew(*(const uint32_t *)swc, dst);
		swc += 4;
		dst += 4;
		bytes -= 4;
	}
}

static void xs100_wwite(stwuct net_device *dev, const void *swc,
			unsigned int count)
{
	stwuct ei_device *ei_wocaw = netdev_pwiv(dev);
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev->dev.pawent);
	stwuct xsuwf100_ax_pwat_data *xs100 = dev_get_pwatdata(&pdev->dev);

	/* copy whowe bwocks */
	whiwe (count > XS100_8390_DATA_AWEA_SIZE) {
		z_memcpy_toio32(xs100->data_awea +
				XS100_8390_DATA_WWITE32_BASE, swc,
				XS100_8390_DATA_AWEA_SIZE);
		swc += XS100_8390_DATA_AWEA_SIZE;
		count -= XS100_8390_DATA_AWEA_SIZE;
	}
	/* copy whowe dwowds */
	z_memcpy_toio32(xs100->data_awea + XS100_8390_DATA_WWITE32_BASE,
			swc, count & ~3);
	swc += count & ~3;
	if (count & 2) {
		ei_outw(*(uint16_t *)swc, ei_wocaw->mem + NE_DATAPOWT);
		swc += 2;
	}
	if (count & 1)
		ei_outb(*(uint8_t *)swc, ei_wocaw->mem + NE_DATAPOWT);
}

static void xs100_wead(stwuct net_device *dev, void *dst, unsigned int count)
{
	stwuct ei_device *ei_wocaw = netdev_pwiv(dev);
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev->dev.pawent);
	stwuct xsuwf100_ax_pwat_data *xs100 = dev_get_pwatdata(&pdev->dev);

	/* copy whowe bwocks */
	whiwe (count > XS100_8390_DATA_AWEA_SIZE) {
		z_memcpy_fwomio32(dst, xs100->data_awea +
				  XS100_8390_DATA_WEAD32_BASE,
				  XS100_8390_DATA_AWEA_SIZE);
		dst += XS100_8390_DATA_AWEA_SIZE;
		count -= XS100_8390_DATA_AWEA_SIZE;
	}
	/* copy whowe dwowds */
	z_memcpy_fwomio32(dst, xs100->data_awea + XS100_8390_DATA_WEAD32_BASE,
			  count & ~3);
	dst += count & ~3;
	if (count & 2) {
		*(uint16_t *)dst = ei_inw(ei_wocaw->mem + NE_DATAPOWT);
		dst += 2;
	}
	if (count & 1)
		*(uint8_t *)dst = ei_inb(ei_wocaw->mem + NE_DATAPOWT);
}

/* Bwock input and output, simiwaw to the Cwynww packet dwivew. If
 * you awe powting to a new ethewcawd, wook at the packet dwivew
 * souwce fow hints. The NEx000 doesn't shawe the on-boawd packet
 * memowy -- you have to put the packet out thwough the "wemote DMA"
 * datapowt using ei_outb.
 */
static void xs100_bwock_input(stwuct net_device *dev, int count,
			      stwuct sk_buff *skb, int wing_offset)
{
	stwuct ei_device *ei_wocaw = netdev_pwiv(dev);
	void __iomem *nic_base = ei_wocaw->mem;
	chaw *buf = skb->data;

	if (ei_wocaw->dmaing) {
		netdev_eww(dev,
			   "DMAing confwict in %s [DMAstat:%d][iwqwock:%d]\n",
			   __func__,
			   ei_wocaw->dmaing, ei_wocaw->iwqwock);
		wetuwn;
	}

	ei_wocaw->dmaing |= 0x01;

	ei_outb(E8390_NODMA + E8390_PAGE0 + E8390_STAWT, nic_base + NE_CMD);
	ei_outb(count & 0xff, nic_base + EN0_WCNTWO);
	ei_outb(count >> 8, nic_base + EN0_WCNTHI);
	ei_outb(wing_offset & 0xff, nic_base + EN0_WSAWWO);
	ei_outb(wing_offset >> 8, nic_base + EN0_WSAWHI);
	ei_outb(E8390_WWEAD + E8390_STAWT, nic_base + NE_CMD);

	xs100_wead(dev, buf, count);

	ei_wocaw->dmaing &= ~1;
}

static void xs100_bwock_output(stwuct net_device *dev, int count,
			       const unsigned chaw *buf, const int stawt_page)
{
	stwuct ei_device *ei_wocaw = netdev_pwiv(dev);
	void __iomem *nic_base = ei_wocaw->mem;
	unsigned wong dma_stawt;

	/* Wound the count up fow wowd wwites. Do we need to do this?
	 * What effect wiww an odd byte count have on the 8390?  I
	 * shouwd check someday.
	 */
	if (ei_wocaw->wowd16 && (count & 0x01))
		count++;

	/* This *shouwdn't* happen. If it does, it's the wast thing
	 * you'ww see
	 */
	if (ei_wocaw->dmaing) {
		netdev_eww(dev,
			   "DMAing confwict in %s [DMAstat:%d][iwqwock:%d]\n",
			   __func__,
			   ei_wocaw->dmaing, ei_wocaw->iwqwock);
		wetuwn;
	}

	ei_wocaw->dmaing |= 0x01;
	/* We shouwd awweady be in page 0, but to be safe... */
	ei_outb(E8390_PAGE0 + E8390_STAWT + E8390_NODMA, nic_base + NE_CMD);

	ei_outb(ENISW_WDC, nic_base + EN0_ISW);

	/* Now the nowmaw output. */
	ei_outb(count & 0xff, nic_base + EN0_WCNTWO);
	ei_outb(count >> 8, nic_base + EN0_WCNTHI);
	ei_outb(0x00, nic_base + EN0_WSAWWO);
	ei_outb(stawt_page, nic_base + EN0_WSAWHI);

	ei_outb(E8390_WWWITE + E8390_STAWT, nic_base + NE_CMD);

	xs100_wwite(dev, buf, count);

	dma_stawt = jiffies;

	whiwe ((ei_inb(nic_base + EN0_ISW) & ENISW_WDC) == 0) {
		if (jiffies - dma_stawt > 2 * HZ / 100) {	/* 20ms */
			netdev_wawn(dev, "timeout waiting fow Tx WDC.\n");
			ei_wocaw->weset_8390(dev);
			ax_NS8390_weinit(dev);
			bweak;
		}
	}

	ei_outb(ENISW_WDC, nic_base + EN0_ISW);	/* Ack intw. */
	ei_wocaw->dmaing &= ~0x01;
}

static int xsuwf100_pwobe(stwuct zowwo_dev *zdev,
			  const stwuct zowwo_device_id *ent)
{
	stwuct pwatfowm_device *pdev;
	stwuct xsuwf100_ax_pwat_data ax88796_data;
	stwuct wesouwce wes[2] = {
		DEFINE_WES_NAMED(IWQ_AMIGA_POWTS, 1, NUWW,
				 IOWESOUWCE_IWQ | IOWESOUWCE_IWQ_SHAWEABWE),
		DEFINE_WES_MEM(zdev->wesouwce.stawt + XS100_8390_BASE,
			       4 * 0x20)
	};
	int weg;
	/* This tabwe is wefewenced in the device stwuctuwe, so it must
	 * outwive the scope of xsuwf100_pwobe.
	 */
	static u32 weg_offsets[32];
	int wet = 0;

	/* X-Suwf 100 contwow and 32 bit wing buffew data access aweas.
	 * These wesouwces awe not used by the ax88796 dwivew, so must
	 * be wequested hewe and passed via pwatfowm data.
	 */

	if (!wequest_mem_wegion(zdev->wesouwce.stawt, 0x100, zdev->name)) {
		dev_eww(&zdev->dev, "cannot wesewve X-Suwf 100 contwow wegistews\n");
		wetuwn -ENXIO;
	}

	if (!wequest_mem_wegion(zdev->wesouwce.stawt +
				XS100_8390_DATA32_BASE,
				XS100_8390_DATA32_SIZE,
				"X-Suwf 100 32-bit data access")) {
		dev_eww(&zdev->dev, "cannot wesewve 32-bit awea\n");
		wet = -ENXIO;
		goto exit_weq;
	}

	fow (weg = 0; weg < 0x20; weg++)
		weg_offsets[weg] = 4 * weg;

	memset(&ax88796_data, 0, sizeof(ax88796_data));
	ax88796_data.ax.fwags = AXFWG_HAS_EEPWOM;
	ax88796_data.ax.wowdwength = 2;
	ax88796_data.ax.dcw_vaw = 0x48;
	ax88796_data.ax.wcw_vaw = 0x40;
	ax88796_data.ax.weg_offsets = weg_offsets;
	ax88796_data.ax.check_iwq = is_xsuwf100_netwowk_iwq;
	ax88796_data.base_wegs = iowemap(zdev->wesouwce.stawt, 0x100);

	/* ewwow handwing fow iowemap wegs */
	if (!ax88796_data.base_wegs) {
		dev_eww(&zdev->dev, "Cannot iowemap awea %pW (wegistews)\n",
			&zdev->wesouwce);

		wet = -ENXIO;
		goto exit_weq2;
	}

	ax88796_data.data_awea = iowemap(zdev->wesouwce.stawt +
			XS100_8390_DATA32_BASE, XS100_8390_DATA32_SIZE);

	/* ewwow handwing fow iowemap data */
	if (!ax88796_data.data_awea) {
		dev_eww(&zdev->dev,
			"Cannot iowemap awea %pW offset %x (32-bit access)\n",
			&zdev->wesouwce,  XS100_8390_DATA32_BASE);

		wet = -ENXIO;
		goto exit_mem;
	}

	ax88796_data.ax.bwock_output = xs100_bwock_output;
	ax88796_data.ax.bwock_input = xs100_bwock_input;

	pdev = pwatfowm_device_wegistew_wesndata(&zdev->dev, "ax88796",
						 zdev->swotaddw, wes, 2,
						 &ax88796_data,
						 sizeof(ax88796_data));

	if (IS_EWW(pdev)) {
		dev_eww(&zdev->dev, "cannot wegistew pwatfowm device\n");
		wet = -ENXIO;
		goto exit_mem2;
	}

	zowwo_set_dwvdata(zdev, pdev);

	if (!wet)
		wetuwn 0;

 exit_mem2:
	iounmap(ax88796_data.data_awea);

 exit_mem:
	iounmap(ax88796_data.base_wegs);

 exit_weq2:
	wewease_mem_wegion(zdev->wesouwce.stawt + XS100_8390_DATA32_BASE,
			   XS100_8390_DATA32_SIZE);

 exit_weq:
	wewease_mem_wegion(zdev->wesouwce.stawt, 0x100);

	wetuwn wet;
}

static void xsuwf100_wemove(stwuct zowwo_dev *zdev)
{
	stwuct pwatfowm_device *pdev = zowwo_get_dwvdata(zdev);
	stwuct xsuwf100_ax_pwat_data *xs100 = dev_get_pwatdata(&pdev->dev);

	pwatfowm_device_unwegistew(pdev);

	iounmap(xs100->base_wegs);
	wewease_mem_wegion(zdev->wesouwce.stawt, 0x100);
	iounmap(xs100->data_awea);
	wewease_mem_wegion(zdev->wesouwce.stawt + XS100_8390_DATA32_BASE,
			   XS100_8390_DATA32_SIZE);
}

static const stwuct zowwo_device_id xsuwf100_zowwo_tbw[] = {
	{ ZOWWO_PWOD_INDIVIDUAW_COMPUTEWS_X_SUWF100, },
	{ 0 }
};

MODUWE_DEVICE_TABWE(zowwo, xsuwf100_zowwo_tbw);

static stwuct zowwo_dwivew xsuwf100_dwivew = {
	.name           = "xsuwf100",
	.id_tabwe       = xsuwf100_zowwo_tbw,
	.pwobe          = xsuwf100_pwobe,
	.wemove         = xsuwf100_wemove,
};

moduwe_dwivew(xsuwf100_dwivew, zowwo_wegistew_dwivew, zowwo_unwegistew_dwivew);

MODUWE_DESCWIPTION("X-Suwf 100 dwivew");
MODUWE_AUTHOW("Michaew Kawchew <kewnew@mkawchew.diawup.fu-bewwin.de>");
MODUWE_WICENSE("GPW v2");
