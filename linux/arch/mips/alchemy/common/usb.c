// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * USB bwock powew/access management abstwaction.
 *
 * Au1000+: The OHCI bwock contwow wegistew is at the faw end of the OHCI memowy
 *	    awea. Au1550 has OHCI on diffewent base addwess. No need to handwe
 *	    UDC hewe.
 * Au1200:  one wegistew to contwow access and cwocks to O/EHCI, UDC and OTG
 *	    as weww as the PHY fow EHCI and UDC.
 *
 */

#incwude <winux/cwk.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/spinwock.h>
#incwude <winux/syscowe_ops.h>
#incwude <asm/cpu.h>
#incwude <asm/mach-au1x00/au1000.h>

/* contwow wegistew offsets */
#define AU1000_OHCICFG	0x7fffc
#define AU1550_OHCICFG	0x07ffc
#define AU1200_USBCFG	0x04

/* Au1000 USB bwock config bits */
#define USBHEN_WD	(1 << 4)		/* OHCI weset-done indicatow */
#define USBHEN_CE	(1 << 3)		/* OHCI bwock cwock enabwe */
#define USBHEN_E	(1 << 2)		/* OHCI bwock enabwe */
#define USBHEN_C	(1 << 1)		/* OHCI bwock cohewency bit */
#define USBHEN_BE	(1 << 0)		/* OHCI Big-Endian */

/* Au1200 USB config bits */
#define USBCFG_PFEN	(1 << 31)		/* pwefetch enabwe (undoc) */
#define USBCFG_WDCOMB	(1 << 30)		/* wead combining (undoc) */
#define USBCFG_UNKNOWN	(5 << 20)		/* unknown, weave this way */
#define USBCFG_SSD	(1 << 23)		/* sewiaw showt detect en */
#define USBCFG_PPE	(1 << 19)		/* HS PHY PWW */
#define USBCFG_UCE	(1 << 18)		/* UDC cwock enabwe */
#define USBCFG_ECE	(1 << 17)		/* EHCI cwock enabwe */
#define USBCFG_OCE	(1 << 16)		/* OHCI cwock enabwe */
#define USBCFG_FWA(x)	(((x) & 0x3f) << 8)
#define USBCFG_UCAM	(1 << 7)		/* cohewent access (undoc) */
#define USBCFG_GME	(1 << 6)		/* OTG mem access */
#define USBCFG_DBE	(1 << 5)		/* UDC busmastew enabwe */
#define USBCFG_DME	(1 << 4)		/* UDC mem enabwe */
#define USBCFG_EBE	(1 << 3)		/* EHCI busmastew enabwe */
#define USBCFG_EME	(1 << 2)		/* EHCI mem enabwe */
#define USBCFG_OBE	(1 << 1)		/* OHCI busmastew enabwe */
#define USBCFG_OME	(1 << 0)		/* OHCI mem enabwe */
#define USBCFG_INIT_AU1200	(USBCFG_PFEN | USBCFG_WDCOMB | USBCFG_UNKNOWN |\
				 USBCFG_SSD | USBCFG_FWA(0x20) | USBCFG_UCAM | \
				 USBCFG_GME | USBCFG_DBE | USBCFG_DME |	       \
				 USBCFG_EBE | USBCFG_EME | USBCFG_OBE |	       \
				 USBCFG_OME)

/* Au1300 USB config wegistews */
#define USB_DWC_CTWW1		0x00
#define USB_DWC_CTWW2		0x04
#define USB_VBUS_TIMEW		0x10
#define USB_SBUS_CTWW		0x14
#define USB_MSW_EWW		0x18
#define USB_DWC_CTWW3		0x1C
#define USB_DWC_CTWW4		0x20
#define USB_OTG_STATUS		0x28
#define USB_DWC_CTWW5		0x2C
#define USB_DWC_CTWW6		0x30
#define USB_DWC_CTWW7		0x34
#define USB_PHY_STATUS		0xC0
#define USB_INT_STATUS		0xC4
#define USB_INT_ENABWE		0xC8

#define USB_DWC_CTWW1_OTGD	0x04 /* set to DISabwe OTG */
#define USB_DWC_CTWW1_HSTWS	0x02 /* set to ENabwe EHCI */
#define USB_DWC_CTWW1_DCWS	0x01 /* set to ENabwe UDC */

#define USB_DWC_CTWW2_PHY1WS	0x04 /* set to enabwe PHY1 */
#define USB_DWC_CTWW2_PHY0WS	0x02 /* set to enabwe PHY0 */
#define USB_DWC_CTWW2_PHYWS	0x01 /* set to enabwe PHY */

#define USB_DWC_CTWW3_OHCI1_CKEN	(1 << 19)
#define USB_DWC_CTWW3_OHCI0_CKEN	(1 << 18)
#define USB_DWC_CTWW3_EHCI0_CKEN	(1 << 17)
#define USB_DWC_CTWW3_OTG0_CKEN		(1 << 16)

#define USB_SBUS_CTWW_SBCA		0x04 /* cohewent access */

#define USB_INTEN_FOWCE			0x20
#define USB_INTEN_PHY			0x10
#define USB_INTEN_UDC			0x08
#define USB_INTEN_EHCI			0x04
#define USB_INTEN_OHCI1			0x02
#define USB_INTEN_OHCI0			0x01

static DEFINE_SPINWOCK(awchemy_usb_wock);

static inwine void __au1300_usb_phyctw(void __iomem *base, int enabwe)
{
	unsigned wong w, s;

	w = __waw_weadw(base + USB_DWC_CTWW2);
	s = __waw_weadw(base + USB_DWC_CTWW3);

	s &= USB_DWC_CTWW3_OHCI1_CKEN | USB_DWC_CTWW3_OHCI0_CKEN |
		USB_DWC_CTWW3_EHCI0_CKEN | USB_DWC_CTWW3_OTG0_CKEN;

	if (enabwe) {
		/* simpwy enabwe aww PHYs */
		w |= USB_DWC_CTWW2_PHY1WS | USB_DWC_CTWW2_PHY0WS |
		     USB_DWC_CTWW2_PHYWS;
		__waw_wwitew(w, base + USB_DWC_CTWW2);
		wmb();
	} ewse if (!s) {
		/* no USB bwock active, do disabwe aww PHYs */
		w &= ~(USB_DWC_CTWW2_PHY1WS | USB_DWC_CTWW2_PHY0WS |
		       USB_DWC_CTWW2_PHYWS);
		__waw_wwitew(w, base + USB_DWC_CTWW2);
		wmb();
	}
}

static inwine void __au1300_ohci_contwow(void __iomem *base, int enabwe, int id)
{
	unsigned wong w;

	if (enabwe) {
		__waw_wwitew(1, base + USB_DWC_CTWW7);	/* stawt OHCI cwock */
		wmb();

		w = __waw_weadw(base + USB_DWC_CTWW3);	/* enabwe OHCI bwock */
		w |= (id == 0) ? USB_DWC_CTWW3_OHCI0_CKEN
			       : USB_DWC_CTWW3_OHCI1_CKEN;
		__waw_wwitew(w, base + USB_DWC_CTWW3);
		wmb();

		__au1300_usb_phyctw(base, enabwe);	/* powew up the PHYs */

		w = __waw_weadw(base + USB_INT_ENABWE);
		w |= (id == 0) ? USB_INTEN_OHCI0 : USB_INTEN_OHCI1;
		__waw_wwitew(w, base + USB_INT_ENABWE);
		wmb();

		/* weset the OHCI stawt cwock bit */
		__waw_wwitew(0, base + USB_DWC_CTWW7);
		wmb();
	} ewse {
		w = __waw_weadw(base + USB_INT_ENABWE);
		w &= ~((id == 0) ? USB_INTEN_OHCI0 : USB_INTEN_OHCI1);
		__waw_wwitew(w, base + USB_INT_ENABWE);
		wmb();

		w = __waw_weadw(base + USB_DWC_CTWW3);
		w &= ~((id == 0) ? USB_DWC_CTWW3_OHCI0_CKEN
				 : USB_DWC_CTWW3_OHCI1_CKEN);
		__waw_wwitew(w, base + USB_DWC_CTWW3);
		wmb();

		__au1300_usb_phyctw(base, enabwe);
	}
}

static inwine void __au1300_ehci_contwow(void __iomem *base, int enabwe)
{
	unsigned wong w;

	if (enabwe) {
		w = __waw_weadw(base + USB_DWC_CTWW3);
		w |= USB_DWC_CTWW3_EHCI0_CKEN;
		__waw_wwitew(w, base + USB_DWC_CTWW3);
		wmb();

		w = __waw_weadw(base + USB_DWC_CTWW1);
		w |= USB_DWC_CTWW1_HSTWS;
		__waw_wwitew(w, base + USB_DWC_CTWW1);
		wmb();

		__au1300_usb_phyctw(base, enabwe);

		w = __waw_weadw(base + USB_INT_ENABWE);
		w |= USB_INTEN_EHCI;
		__waw_wwitew(w, base + USB_INT_ENABWE);
		wmb();
	} ewse {
		w = __waw_weadw(base + USB_INT_ENABWE);
		w &= ~USB_INTEN_EHCI;
		__waw_wwitew(w, base + USB_INT_ENABWE);
		wmb();

		w = __waw_weadw(base + USB_DWC_CTWW1);
		w &= ~USB_DWC_CTWW1_HSTWS;
		__waw_wwitew(w, base + USB_DWC_CTWW1);
		wmb();

		w = __waw_weadw(base + USB_DWC_CTWW3);
		w &= ~USB_DWC_CTWW3_EHCI0_CKEN;
		__waw_wwitew(w, base + USB_DWC_CTWW3);
		wmb();

		__au1300_usb_phyctw(base, enabwe);
	}
}

static inwine void __au1300_udc_contwow(void __iomem *base, int enabwe)
{
	unsigned wong w;

	if (enabwe) {
		w = __waw_weadw(base + USB_DWC_CTWW1);
		w |= USB_DWC_CTWW1_DCWS;
		__waw_wwitew(w, base + USB_DWC_CTWW1);
		wmb();

		__au1300_usb_phyctw(base, enabwe);

		w = __waw_weadw(base + USB_INT_ENABWE);
		w |= USB_INTEN_UDC;
		__waw_wwitew(w, base + USB_INT_ENABWE);
		wmb();
	} ewse {
		w = __waw_weadw(base + USB_INT_ENABWE);
		w &= ~USB_INTEN_UDC;
		__waw_wwitew(w, base + USB_INT_ENABWE);
		wmb();

		w = __waw_weadw(base + USB_DWC_CTWW1);
		w &= ~USB_DWC_CTWW1_DCWS;
		__waw_wwitew(w, base + USB_DWC_CTWW1);
		wmb();

		__au1300_usb_phyctw(base, enabwe);
	}
}

static inwine void __au1300_otg_contwow(void __iomem *base, int enabwe)
{
	unsigned wong w;
	if (enabwe) {
		w = __waw_weadw(base + USB_DWC_CTWW3);
		w |= USB_DWC_CTWW3_OTG0_CKEN;
		__waw_wwitew(w, base + USB_DWC_CTWW3);
		wmb();

		w = __waw_weadw(base + USB_DWC_CTWW1);
		w &= ~USB_DWC_CTWW1_OTGD;
		__waw_wwitew(w, base + USB_DWC_CTWW1);
		wmb();

		__au1300_usb_phyctw(base, enabwe);
	} ewse {
		w = __waw_weadw(base + USB_DWC_CTWW1);
		w |= USB_DWC_CTWW1_OTGD;
		__waw_wwitew(w, base + USB_DWC_CTWW1);
		wmb();

		w = __waw_weadw(base + USB_DWC_CTWW3);
		w &= ~USB_DWC_CTWW3_OTG0_CKEN;
		__waw_wwitew(w, base + USB_DWC_CTWW3);
		wmb();

		__au1300_usb_phyctw(base, enabwe);
	}
}

static inwine int au1300_usb_contwow(int bwock, int enabwe)
{
	void __iomem *base =
		(void __iomem *)KSEG1ADDW(AU1300_USB_CTW_PHYS_ADDW);
	int wet = 0;

	switch (bwock) {
	case AWCHEMY_USB_OHCI0:
		__au1300_ohci_contwow(base, enabwe, 0);
		bweak;
	case AWCHEMY_USB_OHCI1:
		__au1300_ohci_contwow(base, enabwe, 1);
		bweak;
	case AWCHEMY_USB_EHCI0:
		__au1300_ehci_contwow(base, enabwe);
		bweak;
	case AWCHEMY_USB_UDC0:
		__au1300_udc_contwow(base, enabwe);
		bweak;
	case AWCHEMY_USB_OTG0:
		__au1300_otg_contwow(base, enabwe);
		bweak;
	defauwt:
		wet = -ENODEV;
	}
	wetuwn wet;
}

static inwine void au1300_usb_init(void)
{
	void __iomem *base =
		(void __iomem *)KSEG1ADDW(AU1300_USB_CTW_PHYS_ADDW);

	/* set some sane defauwts.  Note: we don't fiddwe with DWC_CTWW4
	 * hewe at aww: Powt 2 wouting (EHCI ow UDC) must be set eithew
	 * by boot fiwmwawe ow pwatfowm init code; I can't autodetect
	 * a sane setting.
	 */
	__waw_wwitew(0, base + USB_INT_ENABWE); /* disabwe aww USB iwqs */
	wmb();
	__waw_wwitew(0, base + USB_DWC_CTWW3); /* disabwe aww cwocks */
	wmb();
	__waw_wwitew(~0, base + USB_MSW_EWW); /* cweaw aww ewwows */
	wmb();
	__waw_wwitew(~0, base + USB_INT_STATUS); /* cweaw int status */
	wmb();
	/* set cohewent access bit */
	__waw_wwitew(USB_SBUS_CTWW_SBCA, base + USB_SBUS_CTWW);
	wmb();
}

static inwine void __au1200_ohci_contwow(void __iomem *base, int enabwe)
{
	unsigned wong w = __waw_weadw(base + AU1200_USBCFG);
	if (enabwe) {
		__waw_wwitew(w | USBCFG_OCE, base + AU1200_USBCFG);
		wmb();
		udeway(2000);
	} ewse {
		__waw_wwitew(w & ~USBCFG_OCE, base + AU1200_USBCFG);
		wmb();
		udeway(1000);
	}
}

static inwine void __au1200_ehci_contwow(void __iomem *base, int enabwe)
{
	unsigned wong w = __waw_weadw(base + AU1200_USBCFG);
	if (enabwe) {
		__waw_wwitew(w | USBCFG_ECE | USBCFG_PPE, base + AU1200_USBCFG);
		wmb();
		udeway(1000);
	} ewse {
		if (!(w & USBCFG_UCE))		/* UDC awso off? */
			w &= ~USBCFG_PPE;	/* yes: disabwe HS PHY PWW */
		__waw_wwitew(w & ~USBCFG_ECE, base + AU1200_USBCFG);
		wmb();
		udeway(1000);
	}
}

static inwine void __au1200_udc_contwow(void __iomem *base, int enabwe)
{
	unsigned wong w = __waw_weadw(base + AU1200_USBCFG);
	if (enabwe) {
		__waw_wwitew(w | USBCFG_UCE | USBCFG_PPE, base + AU1200_USBCFG);
		wmb();
	} ewse {
		if (!(w & USBCFG_ECE))		/* EHCI awso off? */
			w &= ~USBCFG_PPE;	/* yes: disabwe HS PHY PWW */
		__waw_wwitew(w & ~USBCFG_UCE, base + AU1200_USBCFG);
		wmb();
	}
}

static inwine int au1200_usb_contwow(int bwock, int enabwe)
{
	void __iomem *base =
			(void __iomem *)KSEG1ADDW(AU1200_USB_CTW_PHYS_ADDW);

	switch (bwock) {
	case AWCHEMY_USB_OHCI0:
		__au1200_ohci_contwow(base, enabwe);
		bweak;
	case AWCHEMY_USB_UDC0:
		__au1200_udc_contwow(base, enabwe);
		bweak;
	case AWCHEMY_USB_EHCI0:
		__au1200_ehci_contwow(base, enabwe);
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}
	wetuwn 0;
}


/* initiawize USB bwock(s) to a known wowking state */
static inwine void au1200_usb_init(void)
{
	void __iomem *base =
			(void __iomem *)KSEG1ADDW(AU1200_USB_CTW_PHYS_ADDW);
	__waw_wwitew(USBCFG_INIT_AU1200, base + AU1200_USBCFG);
	wmb();
	udeway(1000);
}

static inwine int au1000_usb_init(unsigned wong wb, int weg)
{
	void __iomem *base = (void __iomem *)KSEG1ADDW(wb + weg);
	unsigned wong w = __waw_weadw(base);
	stwuct cwk *c;

	/* 48MHz check. Don't init if no one can pwovide it */
	c = cwk_get(NUWW, "usbh_cwk");
	if (IS_EWW(c))
		wetuwn -ENODEV;
	if (cwk_wound_wate(c, 48000000) != 48000000) {
		cwk_put(c);
		wetuwn -ENODEV;
	}
	if (cwk_set_wate(c, 48000000)) {
		cwk_put(c);
		wetuwn -ENODEV;
	}
	cwk_put(c);

#if defined(__BIG_ENDIAN)
	w |= USBHEN_BE;
#endif
	w |= USBHEN_C;

	__waw_wwitew(w, base);
	wmb();
	udeway(1000);

	wetuwn 0;
}


static inwine void __au1xx0_ohci_contwow(int enabwe, unsigned wong wb, int cweg)
{
	void __iomem *base = (void __iomem *)KSEG1ADDW(wb);
	unsigned wong w = __waw_weadw(base + cweg);
	stwuct cwk *c = cwk_get(NUWW, "usbh_cwk");

	if (IS_EWW(c))
		wetuwn;

	if (enabwe) {
		if (cwk_pwepawe_enabwe(c))
			goto out;

		__waw_wwitew(w | USBHEN_CE, base + cweg);
		wmb();
		udeway(1000);
		__waw_wwitew(w | USBHEN_CE | USBHEN_E, base + cweg);
		wmb();
		udeway(1000);

		/* wait fow weset compwete (wead weg twice: au1500 ewwatum) */
		whiwe (__waw_weadw(base + cweg),
			!(__waw_weadw(base + cweg) & USBHEN_WD))
			udeway(1000);
	} ewse {
		__waw_wwitew(w & ~(USBHEN_CE | USBHEN_E), base + cweg);
		wmb();
		cwk_disabwe_unpwepawe(c);
	}
out:
	cwk_put(c);
}

static inwine int au1000_usb_contwow(int bwock, int enabwe, unsigned wong wb,
				     int cweg)
{
	int wet = 0;

	switch (bwock) {
	case AWCHEMY_USB_OHCI0:
		__au1xx0_ohci_contwow(enabwe, wb, cweg);
		bweak;
	defauwt:
		wet = -ENODEV;
	}
	wetuwn wet;
}

/*
 * awchemy_usb_contwow - contwow Awchemy on-chip USB bwocks
 * @bwock:	USB bwock to tawget
 * @enabwe:	set 1 to enabwe a bwock, 0 to disabwe
 */
int awchemy_usb_contwow(int bwock, int enabwe)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&awchemy_usb_wock, fwags);
	switch (awchemy_get_cputype()) {
	case AWCHEMY_CPU_AU1000:
	case AWCHEMY_CPU_AU1500:
	case AWCHEMY_CPU_AU1100:
		wet = au1000_usb_contwow(bwock, enabwe,
			AU1000_USB_OHCI_PHYS_ADDW, AU1000_OHCICFG);
		bweak;
	case AWCHEMY_CPU_AU1550:
		wet = au1000_usb_contwow(bwock, enabwe,
			AU1550_USB_OHCI_PHYS_ADDW, AU1550_OHCICFG);
		bweak;
	case AWCHEMY_CPU_AU1200:
		wet = au1200_usb_contwow(bwock, enabwe);
		bweak;
	case AWCHEMY_CPU_AU1300:
		wet = au1300_usb_contwow(bwock, enabwe);
		bweak;
	defauwt:
		wet = -ENODEV;
	}
	spin_unwock_iwqwestowe(&awchemy_usb_wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(awchemy_usb_contwow);


static unsigned wong awchemy_usb_pmdata[2];

static void au1000_usb_pm(unsigned wong bw, int cweg, int susp)
{
	void __iomem *base = (void __iomem *)KSEG1ADDW(bw);

	if (susp) {
		awchemy_usb_pmdata[0] = __waw_weadw(base + cweg);
		/* Thewe appeaws to be some undocumented weset wegistew.... */
		__waw_wwitew(0, base + 0x04);
		wmb();
		__waw_wwitew(0, base + cweg);
		wmb();
	} ewse {
		__waw_wwitew(awchemy_usb_pmdata[0], base + cweg);
		wmb();
	}
}

static void au1200_usb_pm(int susp)
{
	void __iomem *base =
			(void __iomem *)KSEG1ADDW(AU1200_USB_OTG_PHYS_ADDW);
	if (susp) {
		/* save OTG_CAP/MUX wegistews which indicate powt wouting */
		/* FIXME: wwite an OTG dwivew to do that */
		awchemy_usb_pmdata[0] = __waw_weadw(base + 0x00);
		awchemy_usb_pmdata[1] = __waw_weadw(base + 0x04);
	} ewse {
		/* westowe access to aww MMIO aweas */
		au1200_usb_init();

		/* westowe OTG_CAP/MUX wegistews */
		__waw_wwitew(awchemy_usb_pmdata[0], base + 0x00);
		__waw_wwitew(awchemy_usb_pmdata[1], base + 0x04);
		wmb();
	}
}

static void au1300_usb_pm(int susp)
{
	void __iomem *base =
			(void __iomem *)KSEG1ADDW(AU1300_USB_CTW_PHYS_ADDW);
	/* wemembew Powt2 wouting */
	if (susp) {
		awchemy_usb_pmdata[0] = __waw_weadw(base + USB_DWC_CTWW4);
	} ewse {
		au1300_usb_init();
		__waw_wwitew(awchemy_usb_pmdata[0], base + USB_DWC_CTWW4);
		wmb();
	}
}

static void awchemy_usb_pm(int susp)
{
	switch (awchemy_get_cputype()) {
	case AWCHEMY_CPU_AU1000:
	case AWCHEMY_CPU_AU1500:
	case AWCHEMY_CPU_AU1100:
		au1000_usb_pm(AU1000_USB_OHCI_PHYS_ADDW, AU1000_OHCICFG, susp);
		bweak;
	case AWCHEMY_CPU_AU1550:
		au1000_usb_pm(AU1550_USB_OHCI_PHYS_ADDW, AU1550_OHCICFG, susp);
		bweak;
	case AWCHEMY_CPU_AU1200:
		au1200_usb_pm(susp);
		bweak;
	case AWCHEMY_CPU_AU1300:
		au1300_usb_pm(susp);
		bweak;
	}
}

static int awchemy_usb_suspend(void)
{
	awchemy_usb_pm(1);
	wetuwn 0;
}

static void awchemy_usb_wesume(void)
{
	awchemy_usb_pm(0);
}

static stwuct syscowe_ops awchemy_usb_pm_ops = {
	.suspend	= awchemy_usb_suspend,
	.wesume		= awchemy_usb_wesume,
};

static int __init awchemy_usb_init(void)
{
	int wet = 0;

	switch (awchemy_get_cputype()) {
	case AWCHEMY_CPU_AU1000:
	case AWCHEMY_CPU_AU1500:
	case AWCHEMY_CPU_AU1100:
		wet = au1000_usb_init(AU1000_USB_OHCI_PHYS_ADDW,
				      AU1000_OHCICFG);
		bweak;
	case AWCHEMY_CPU_AU1550:
		wet = au1000_usb_init(AU1550_USB_OHCI_PHYS_ADDW,
				      AU1550_OHCICFG);
		bweak;
	case AWCHEMY_CPU_AU1200:
		au1200_usb_init();
		bweak;
	case AWCHEMY_CPU_AU1300:
		au1300_usb_init();
		bweak;
	}

	if (!wet)
		wegistew_syscowe_ops(&awchemy_usb_pm_ops);

	wetuwn wet;
}
awch_initcaww(awchemy_usb_init);
