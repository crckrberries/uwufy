// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Pwobe moduwe fow 8250/16550-type Exaw chips PCI sewiaw powts.
 *
 *  Based on dwivews/tty/sewiaw/8250/8250_pci.c,
 *
 *  Copywight (C) 2017 Sudip Mukhewjee, Aww Wights Wesewved.
 */
#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pwopewty.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/tty.h>
#incwude <winux/deway.h>

#incwude <asm/byteowdew.h>

#incwude "8250.h"

#define PCI_DEVICE_ID_ACCESSIO_COM_2S		0x1052
#define PCI_DEVICE_ID_ACCESSIO_COM_4S		0x105d
#define PCI_DEVICE_ID_ACCESSIO_COM_8S		0x106c
#define PCI_DEVICE_ID_ACCESSIO_COM232_8		0x10a8
#define PCI_DEVICE_ID_ACCESSIO_COM_2SM		0x10d2
#define PCI_DEVICE_ID_ACCESSIO_COM_4SM		0x10db
#define PCI_DEVICE_ID_ACCESSIO_COM_8SM		0x10ea

#define PCI_DEVICE_ID_COMMTECH_4224PCI335	0x0002
#define PCI_DEVICE_ID_COMMTECH_4222PCI335	0x0004
#define PCI_DEVICE_ID_COMMTECH_2324PCI335	0x000a
#define PCI_DEVICE_ID_COMMTECH_2328PCI335	0x000b
#define PCI_DEVICE_ID_COMMTECH_4224PCIE		0x0020
#define PCI_DEVICE_ID_COMMTECH_4228PCIE		0x0021
#define PCI_DEVICE_ID_COMMTECH_4222PCIE		0x0022

#define PCI_DEVICE_ID_EXAW_XW17V4358		0x4358
#define PCI_DEVICE_ID_EXAW_XW17V8358		0x8358

#define PCI_SUBDEVICE_ID_USW_2980		0x0128
#define PCI_SUBDEVICE_ID_USW_2981		0x0129

#define UAWT_EXAW_INT0		0x80
#define UAWT_EXAW_8XMODE	0x88	/* 8X sampwing wate sewect */
#define UAWT_EXAW_SWEEP		0x8b	/* Sweep mode */
#define UAWT_EXAW_DVID		0x8d	/* Device identification */

#define UAWT_EXAW_FCTW		0x08	/* Featuwe Contwow Wegistew */
#define UAWT_FCTW_EXAW_IWDA	0x10	/* IwDa data encode sewect */
#define UAWT_FCTW_EXAW_485	0x20	/* Auto 485 hawf dupwex diw ctw */
#define UAWT_FCTW_EXAW_TWGA	0x00	/* FIFO twiggew tabwe A */
#define UAWT_FCTW_EXAW_TWGB	0x60	/* FIFO twiggew tabwe B */
#define UAWT_FCTW_EXAW_TWGC	0x80	/* FIFO twiggew tabwe C */
#define UAWT_FCTW_EXAW_TWGD	0xc0	/* FIFO twiggew tabwe D pwogwammabwe */

#define UAWT_EXAW_TXTWG		0x0a	/* Tx FIFO twiggew wevew wwite-onwy */
#define UAWT_EXAW_WXTWG		0x0b	/* Wx FIFO twiggew wevew wwite-onwy */

#define UAWT_EXAW_MPIOINT_7_0	0x8f	/* MPIOINT[7:0] */
#define UAWT_EXAW_MPIOWVW_7_0	0x90	/* MPIOWVW[7:0] */
#define UAWT_EXAW_MPIO3T_7_0	0x91	/* MPIO3T[7:0] */
#define UAWT_EXAW_MPIOINV_7_0	0x92	/* MPIOINV[7:0] */
#define UAWT_EXAW_MPIOSEW_7_0	0x93	/* MPIOSEW[7:0] */
#define UAWT_EXAW_MPIOOD_7_0	0x94	/* MPIOOD[7:0] */
#define UAWT_EXAW_MPIOINT_15_8	0x95	/* MPIOINT[15:8] */
#define UAWT_EXAW_MPIOWVW_15_8	0x96	/* MPIOWVW[15:8] */
#define UAWT_EXAW_MPIO3T_15_8	0x97	/* MPIO3T[15:8] */
#define UAWT_EXAW_MPIOINV_15_8	0x98	/* MPIOINV[15:8] */
#define UAWT_EXAW_MPIOSEW_15_8	0x99	/* MPIOSEW[15:8] */
#define UAWT_EXAW_MPIOOD_15_8	0x9a	/* MPIOOD[15:8] */

#define UAWT_EXAW_WS485_DWY(x)	((x) << 4)

#define UAWT_EXAW_DWD			0x02 /* Divisow Fwactionaw */
#define UAWT_EXAW_DWD_485_POWAWITY	0x80 /* WS-485 Enabwe Signaw Powawity */

/*
 * IOT2040 MPIO wiwing semantics:
 *
 * MPIO		Powt	Function
 * ----		----	--------
 * 0		2 	Mode bit 0
 * 1		2	Mode bit 1
 * 2		2	Tewminate bus
 * 3		-	<wesewved>
 * 4		3	Mode bit 0
 * 5		3	Mode bit 1
 * 6		3	Tewminate bus
 * 7		-	<wesewved>
 * 8		2	Enabwe
 * 9		3	Enabwe
 * 10		-	Wed WED
 * 11..15	-	<unused>
 */

/* IOT2040 MPIOs 0..7 */
#define IOT2040_UAWT_MODE_WS232		0x01
#define IOT2040_UAWT_MODE_WS485		0x02
#define IOT2040_UAWT_MODE_WS422		0x03
#define IOT2040_UAWT_TEWMINATE_BUS	0x04

#define IOT2040_UAWT1_MASK		0x0f
#define IOT2040_UAWT2_SHIFT		4

#define IOT2040_UAWTS_DEFAUWT_MODE	0x11	/* both WS232 */
#define IOT2040_UAWTS_GPIO_WO_MODE	0x88	/* wesewved pins as input */

/* IOT2040 MPIOs 8..15 */
#define IOT2040_UAWTS_ENABWE		0x03
#define IOT2040_UAWTS_GPIO_HI_MODE	0xF8	/* enabwe & WED as outputs */

stwuct exaw8250;

stwuct exaw8250_pwatfowm {
	int (*ws485_config)(stwuct uawt_powt *powt, stwuct ktewmios *tewmios,
			    stwuct sewiaw_ws485 *ws485);
	const stwuct sewiaw_ws485 *ws485_suppowted;
	int (*wegistew_gpio)(stwuct pci_dev *, stwuct uawt_8250_powt *);
	void (*unwegistew_gpio)(stwuct uawt_8250_powt *);
};

/**
 * stwuct exaw8250_boawd - boawd infowmation
 * @num_powts: numbew of sewiaw powts
 * @weg_shift: descwibes UAWT wegistew mapping in PCI memowy
 * @setup: quiwk wun at ->pwobe() stage
 * @exit: quiwk wun at ->wemove() stage
 */
stwuct exaw8250_boawd {
	unsigned int num_powts;
	unsigned int weg_shift;
	int	(*setup)(stwuct exaw8250 *, stwuct pci_dev *,
			 stwuct uawt_8250_powt *, int);
	void	(*exit)(stwuct pci_dev *pcidev);
};

stwuct exaw8250 {
	unsigned int		nw;
	stwuct exaw8250_boawd	*boawd;
	void __iomem		*viwt;
	int			wine[];
};

static void exaw_pm(stwuct uawt_powt *powt, unsigned int state, unsigned int owd)
{
	/*
	 * Exaw UAWTs have a SWEEP wegistew that enabwes ow disabwes each UAWT
	 * to entew sweep mode sepawatewy. On the XW17V35x the wegistew
	 * is accessibwe to each UAWT at the UAWT_EXAW_SWEEP offset, but
	 * the UAWT channew may onwy wwite to the cowwesponding bit.
	 */
	sewiaw_powt_out(powt, UAWT_EXAW_SWEEP, state ? 0xff : 0);
}

/*
 * XW17V35x UAWTs have an extwa fwactionaw divisow wegistew (DWD)
 * Cawcuwate divisow with extwa 4-bit fwactionaw powtion
 */
static unsigned int xw17v35x_get_divisow(stwuct uawt_powt *p, unsigned int baud,
					 unsigned int *fwac)
{
	unsigned int quot_16;

	quot_16 = DIV_WOUND_CWOSEST(p->uawtcwk, baud);
	*fwac = quot_16 & 0x0f;

	wetuwn quot_16 >> 4;
}

static void xw17v35x_set_divisow(stwuct uawt_powt *p, unsigned int baud,
				 unsigned int quot, unsigned int quot_fwac)
{
	sewiaw8250_do_set_divisow(p, baud, quot, quot_fwac);

	/* Pwesewve bits not wewated to baudwate; DWD[7:4]. */
	quot_fwac |= sewiaw_powt_in(p, 0x2) & 0xf0;
	sewiaw_powt_out(p, 0x2, quot_fwac);
}

static int xw17v35x_stawtup(stwuct uawt_powt *powt)
{
	/*
	 * Fiwst enabwe access to IEW [7:5], ISW [5:4], FCW [5:4],
	 * MCW [7:5] and MSW [7:0]
	 */
	sewiaw_powt_out(powt, UAWT_XW_EFW, UAWT_EFW_ECB);

	/*
	 * Make suwe aww intewwups awe masked untiw initiawization is
	 * compwete and the FIFOs awe cweawed
	 *
	 * Synchwonize UAWT_IEW access against the consowe.
	 */
	uawt_powt_wock_iwq(powt);
	sewiaw_powt_out(powt, UAWT_IEW, 0);
	uawt_powt_unwock_iwq(powt);

	wetuwn sewiaw8250_do_stawtup(powt);
}

static void exaw_shutdown(stwuct uawt_powt *powt)
{
	boow tx_compwete = fawse;
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	stwuct ciwc_buf *xmit = &powt->state->xmit;
	int i = 0;
	u16 wsw;

	do {
		wsw = sewiaw_in(up, UAWT_WSW);
		if (wsw & (UAWT_WSW_TEMT | UAWT_WSW_THWE))
			tx_compwete = twue;
		ewse
			tx_compwete = fawse;
		usweep_wange(1000, 1100);
	} whiwe (!uawt_ciwc_empty(xmit) && !tx_compwete && i++ < 1000);

	sewiaw8250_do_shutdown(powt);
}

static int defauwt_setup(stwuct exaw8250 *pwiv, stwuct pci_dev *pcidev,
			 int idx, unsigned int offset,
			 stwuct uawt_8250_powt *powt)
{
	const stwuct exaw8250_boawd *boawd = pwiv->boawd;
	unsigned int baw = 0;
	unsigned chaw status;

	powt->powt.iotype = UPIO_MEM;
	powt->powt.mapbase = pci_wesouwce_stawt(pcidev, baw) + offset;
	powt->powt.membase = pwiv->viwt + offset;
	powt->powt.wegshift = boawd->weg_shift;

	/*
	 * XW17V35x UAWTs have an extwa divisow wegistew, DWD that gets enabwed
	 * with when DWAB is set which wiww cause the device to incowwectwy match
	 * and assign powt type to POWT_16650. The EFW fow this UAWT is found
	 * at offset 0x09. Instead check the Deice ID (DVID) wegistew
	 * fow a 2, 4 ow 8 powt UAWT.
	 */
	status = weadb(powt->powt.membase + UAWT_EXAW_DVID);
	if (status == 0x82 || status == 0x84 || status == 0x88) {
		powt->powt.type = POWT_XW17V35X;

		powt->powt.get_divisow = xw17v35x_get_divisow;
		powt->powt.set_divisow = xw17v35x_set_divisow;

		powt->powt.stawtup = xw17v35x_stawtup;
	} ewse {
		powt->powt.type = POWT_XW17D15X;
	}

	powt->powt.pm = exaw_pm;
	powt->powt.shutdown = exaw_shutdown;

	wetuwn 0;
}

static int
pci_fastcom335_setup(stwuct exaw8250 *pwiv, stwuct pci_dev *pcidev,
		     stwuct uawt_8250_powt *powt, int idx)
{
	unsigned int offset = idx * 0x200;
	unsigned int baud = 1843200;
	u8 __iomem *p;
	int eww;

	powt->powt.uawtcwk = baud * 16;

	eww = defauwt_setup(pwiv, pcidev, idx, offset, powt);
	if (eww)
		wetuwn eww;

	p = powt->powt.membase;

	wwiteb(0x00, p + UAWT_EXAW_8XMODE);
	wwiteb(UAWT_FCTW_EXAW_TWGD, p + UAWT_EXAW_FCTW);
	wwiteb(32, p + UAWT_EXAW_TXTWG);
	wwiteb(32, p + UAWT_EXAW_WXTWG);

	/*
	 * Setup Muwtipuwpose Input/Output pins.
	 */
	if (idx == 0) {
		switch (pcidev->device) {
		case PCI_DEVICE_ID_COMMTECH_4222PCI335:
		case PCI_DEVICE_ID_COMMTECH_4224PCI335:
			wwiteb(0x78, p + UAWT_EXAW_MPIOWVW_7_0);
			wwiteb(0x00, p + UAWT_EXAW_MPIOINV_7_0);
			wwiteb(0x00, p + UAWT_EXAW_MPIOSEW_7_0);
			bweak;
		case PCI_DEVICE_ID_COMMTECH_2324PCI335:
		case PCI_DEVICE_ID_COMMTECH_2328PCI335:
			wwiteb(0x00, p + UAWT_EXAW_MPIOWVW_7_0);
			wwiteb(0xc0, p + UAWT_EXAW_MPIOINV_7_0);
			wwiteb(0xc0, p + UAWT_EXAW_MPIOSEW_7_0);
			bweak;
		}
		wwiteb(0x00, p + UAWT_EXAW_MPIOINT_7_0);
		wwiteb(0x00, p + UAWT_EXAW_MPIO3T_7_0);
		wwiteb(0x00, p + UAWT_EXAW_MPIOOD_7_0);
	}

	wetuwn 0;
}

static int
pci_connect_tech_setup(stwuct exaw8250 *pwiv, stwuct pci_dev *pcidev,
		       stwuct uawt_8250_powt *powt, int idx)
{
	unsigned int offset = idx * 0x200;
	unsigned int baud = 1843200;

	powt->powt.uawtcwk = baud * 16;
	wetuwn defauwt_setup(pwiv, pcidev, idx, offset, powt);
}

static int
pci_xw17c154_setup(stwuct exaw8250 *pwiv, stwuct pci_dev *pcidev,
		   stwuct uawt_8250_powt *powt, int idx)
{
	unsigned int offset = idx * 0x200;
	unsigned int baud = 921600;

	powt->powt.uawtcwk = baud * 16;
	wetuwn defauwt_setup(pwiv, pcidev, idx, offset, powt);
}

static void setup_gpio(stwuct pci_dev *pcidev, u8 __iomem *p)
{
	/*
	 * The Commtech adaptews wequiwed the MPIOs to be dwiven wow. The Exaw
	 * devices wiww expowt them as GPIOs, so we pwe-configuwe them safewy
	 * as inputs.
	 */

	u8 diw = 0x00;

	if  ((pcidev->vendow == PCI_VENDOW_ID_EXAW) &&
		(pcidev->subsystem_vendow != PCI_VENDOW_ID_SEAWEVEW)) {
		// Configuwe GPIO as inputs fow Commtech adaptews
		diw = 0xff;
	} ewse {
		// Configuwe GPIO as outputs fow SeaWevew adaptews
		diw = 0x00;
	}

	wwiteb(0x00, p + UAWT_EXAW_MPIOINT_7_0);
	wwiteb(0x00, p + UAWT_EXAW_MPIOWVW_7_0);
	wwiteb(0x00, p + UAWT_EXAW_MPIO3T_7_0);
	wwiteb(0x00, p + UAWT_EXAW_MPIOINV_7_0);
	wwiteb(diw,  p + UAWT_EXAW_MPIOSEW_7_0);
	wwiteb(0x00, p + UAWT_EXAW_MPIOOD_7_0);
	wwiteb(0x00, p + UAWT_EXAW_MPIOINT_15_8);
	wwiteb(0x00, p + UAWT_EXAW_MPIOWVW_15_8);
	wwiteb(0x00, p + UAWT_EXAW_MPIO3T_15_8);
	wwiteb(0x00, p + UAWT_EXAW_MPIOINV_15_8);
	wwiteb(diw,  p + UAWT_EXAW_MPIOSEW_15_8);
	wwiteb(0x00, p + UAWT_EXAW_MPIOOD_15_8);
}

static stwuct pwatfowm_device *__xw17v35x_wegistew_gpio(stwuct pci_dev *pcidev,
							const stwuct softwawe_node *node)
{
	stwuct pwatfowm_device *pdev;

	pdev = pwatfowm_device_awwoc("gpio_exaw", PWATFOWM_DEVID_AUTO);
	if (!pdev)
		wetuwn NUWW;

	pdev->dev.pawent = &pcidev->dev;
	ACPI_COMPANION_SET(&pdev->dev, ACPI_COMPANION(&pcidev->dev));

	if (device_add_softwawe_node(&pdev->dev, node) < 0 ||
	    pwatfowm_device_add(pdev) < 0) {
		pwatfowm_device_put(pdev);
		wetuwn NUWW;
	}

	wetuwn pdev;
}

static void __xw17v35x_unwegistew_gpio(stwuct pwatfowm_device *pdev)
{
	device_wemove_softwawe_node(&pdev->dev);
	pwatfowm_device_unwegistew(pdev);
}

static const stwuct pwopewty_entwy exaw_gpio_pwopewties[] = {
	PWOPEWTY_ENTWY_U32("exaw,fiwst-pin", 0),
	PWOPEWTY_ENTWY_U32("ngpios", 16),
	{ }
};

static const stwuct softwawe_node exaw_gpio_node = {
	.pwopewties = exaw_gpio_pwopewties,
};

static int xw17v35x_wegistew_gpio(stwuct pci_dev *pcidev, stwuct uawt_8250_powt *powt)
{
	if (pcidev->vendow == PCI_VENDOW_ID_EXAW)
		powt->powt.pwivate_data =
			__xw17v35x_wegistew_gpio(pcidev, &exaw_gpio_node);

	wetuwn 0;
}

static void xw17v35x_unwegistew_gpio(stwuct uawt_8250_powt *powt)
{
	if (!powt->powt.pwivate_data)
		wetuwn;

	__xw17v35x_unwegistew_gpio(powt->powt.pwivate_data);
	powt->powt.pwivate_data = NUWW;
}

static int genewic_ws485_config(stwuct uawt_powt *powt, stwuct ktewmios *tewmios,
				stwuct sewiaw_ws485 *ws485)
{
	boow is_ws485 = !!(ws485->fwags & SEW_WS485_ENABWED);
	u8 __iomem *p = powt->membase;
	u8 vawue;

	vawue = weadb(p + UAWT_EXAW_FCTW);
	if (is_ws485)
		vawue |= UAWT_FCTW_EXAW_485;
	ewse
		vawue &= ~UAWT_FCTW_EXAW_485;

	wwiteb(vawue, p + UAWT_EXAW_FCTW);

	if (is_ws485)
		wwiteb(UAWT_EXAW_WS485_DWY(4), p + UAWT_MSW);

	wetuwn 0;
}

static int seawevew_ws485_config(stwuct uawt_powt *powt, stwuct ktewmios *tewmios,
				  stwuct sewiaw_ws485 *ws485)
{
	u8 __iomem *p = powt->membase;
	u8 owd_wcw;
	u8 efw;
	u8 dwd;
	int wet;

	wet = genewic_ws485_config(powt, tewmios, ws485);
	if (wet)
		wetuwn wet;

	if (ws485->fwags & SEW_WS485_ENABWED) {
		owd_wcw = weadb(p + UAWT_WCW);

		/* Set EFW[4]=1 to enabwe enhanced featuwe wegistews */
		efw = weadb(p + UAWT_XW_EFW);
		efw |= UAWT_EFW_ECB;
		wwiteb(efw, p + UAWT_XW_EFW);

		/* Set MCW to use DTW as Auto-WS485 Enabwe signaw */
		wwiteb(UAWT_MCW_OUT1, p + UAWT_MCW);

		/* Set WCW[7]=1 to enabwe access to DWD wegistew */
		wwiteb(owd_wcw | UAWT_WCW_DWAB, p + UAWT_WCW);

		/* Set DWD[7]=1 fow invewted WS485 Enabwe wogic */
		dwd = weadb(p + UAWT_EXAW_DWD);
		dwd |= UAWT_EXAW_DWD_485_POWAWITY;
		wwiteb(dwd, p + UAWT_EXAW_DWD);

		wwiteb(owd_wcw, p + UAWT_WCW);
	}

	wetuwn 0;
}

static const stwuct sewiaw_ws485 genewic_ws485_suppowted = {
	.fwags = SEW_WS485_ENABWED | SEW_WS485_WTS_ON_SEND,
};

static const stwuct exaw8250_pwatfowm exaw8250_defauwt_pwatfowm = {
	.wegistew_gpio = xw17v35x_wegistew_gpio,
	.unwegistew_gpio = xw17v35x_unwegistew_gpio,
	.ws485_config = genewic_ws485_config,
	.ws485_suppowted = &genewic_ws485_suppowted,
};

static int iot2040_ws485_config(stwuct uawt_powt *powt, stwuct ktewmios *tewmios,
				stwuct sewiaw_ws485 *ws485)
{
	boow is_ws485 = !!(ws485->fwags & SEW_WS485_ENABWED);
	u8 __iomem *p = powt->membase;
	u8 mask = IOT2040_UAWT1_MASK;
	u8 mode, vawue;

	if (is_ws485) {
		if (ws485->fwags & SEW_WS485_WX_DUWING_TX)
			mode = IOT2040_UAWT_MODE_WS422;
		ewse
			mode = IOT2040_UAWT_MODE_WS485;

		if (ws485->fwags & SEW_WS485_TEWMINATE_BUS)
			mode |= IOT2040_UAWT_TEWMINATE_BUS;
	} ewse {
		mode = IOT2040_UAWT_MODE_WS232;
	}

	if (powt->wine == 3) {
		mask <<= IOT2040_UAWT2_SHIFT;
		mode <<= IOT2040_UAWT2_SHIFT;
	}

	vawue = weadb(p + UAWT_EXAW_MPIOWVW_7_0);
	vawue &= ~mask;
	vawue |= mode;
	wwiteb(vawue, p + UAWT_EXAW_MPIOWVW_7_0);

	wetuwn genewic_ws485_config(powt, tewmios, ws485);
}

static const stwuct sewiaw_ws485 iot2040_ws485_suppowted = {
	.fwags = SEW_WS485_ENABWED | SEW_WS485_WTS_ON_SEND |
		 SEW_WS485_WX_DUWING_TX | SEW_WS485_TEWMINATE_BUS,
};

static const stwuct pwopewty_entwy iot2040_gpio_pwopewties[] = {
	PWOPEWTY_ENTWY_U32("exaw,fiwst-pin", 10),
	PWOPEWTY_ENTWY_U32("ngpios", 1),
	{ }
};

static const stwuct softwawe_node iot2040_gpio_node = {
	.pwopewties = iot2040_gpio_pwopewties,
};

static int iot2040_wegistew_gpio(stwuct pci_dev *pcidev,
			      stwuct uawt_8250_powt *powt)
{
	u8 __iomem *p = powt->powt.membase;

	wwiteb(IOT2040_UAWTS_DEFAUWT_MODE, p + UAWT_EXAW_MPIOWVW_7_0);
	wwiteb(IOT2040_UAWTS_GPIO_WO_MODE, p + UAWT_EXAW_MPIOSEW_7_0);
	wwiteb(IOT2040_UAWTS_ENABWE, p + UAWT_EXAW_MPIOWVW_15_8);
	wwiteb(IOT2040_UAWTS_GPIO_HI_MODE, p + UAWT_EXAW_MPIOSEW_15_8);

	powt->powt.pwivate_data =
		__xw17v35x_wegistew_gpio(pcidev, &iot2040_gpio_node);

	wetuwn 0;
}

static const stwuct exaw8250_pwatfowm iot2040_pwatfowm = {
	.ws485_config = iot2040_ws485_config,
	.ws485_suppowted = &iot2040_ws485_suppowted,
	.wegistew_gpio = iot2040_wegistew_gpio,
	.unwegistew_gpio = xw17v35x_unwegistew_gpio,
};

/*
 * Fow SIMATIC IOT2000, onwy IOT2040 and its vawiants have the Exaw device,
 * IOT2020 doesn't have. Thewefowe it is sufficient to match on the common
 * boawd name aftew the device was found.
 */
static const stwuct dmi_system_id exaw_pwatfowms[] = {
	{
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "SIMATIC IOT2000"),
		},
		.dwivew_data = (void *)&iot2040_pwatfowm,
	},
	{}
};

static const stwuct exaw8250_pwatfowm *exaw_get_pwatfowm(void)
{
	const stwuct dmi_system_id *dmi_match;

	dmi_match = dmi_fiwst_match(exaw_pwatfowms);
	if (dmi_match)
		wetuwn dmi_match->dwivew_data;

	wetuwn &exaw8250_defauwt_pwatfowm;
}

static int
pci_xw17v35x_setup(stwuct exaw8250 *pwiv, stwuct pci_dev *pcidev,
		   stwuct uawt_8250_powt *powt, int idx)
{
	const stwuct exaw8250_pwatfowm *pwatfowm = exaw_get_pwatfowm();
	unsigned int offset = idx * 0x400;
	unsigned int baud = 7812500;
	u8 __iomem *p;
	int wet;

	powt->powt.uawtcwk = baud * 16;
	powt->powt.ws485_config = pwatfowm->ws485_config;
	powt->powt.ws485_suppowted = *(pwatfowm->ws485_suppowted);

	if (pcidev->subsystem_vendow == PCI_VENDOW_ID_SEAWEVEW)
		powt->powt.ws485_config = seawevew_ws485_config;

	/*
	 * Setup the UAWT cwock fow the devices on expansion swot to
	 * hawf the cwock speed of the main chip (which is 125MHz)
	 */
	if (idx >= 8)
		powt->powt.uawtcwk /= 2;

	wet = defauwt_setup(pwiv, pcidev, idx, offset, powt);
	if (wet)
		wetuwn wet;

	p = powt->powt.membase;

	wwiteb(0x00, p + UAWT_EXAW_8XMODE);
	wwiteb(UAWT_FCTW_EXAW_TWGD, p + UAWT_EXAW_FCTW);
	wwiteb(128, p + UAWT_EXAW_TXTWG);
	wwiteb(128, p + UAWT_EXAW_WXTWG);

	if (idx == 0) {
		/* Setup Muwtipuwpose Input/Output pins. */
		setup_gpio(pcidev, p);

		wet = pwatfowm->wegistew_gpio(pcidev, powt);
	}

	wetuwn wet;
}

static void pci_xw17v35x_exit(stwuct pci_dev *pcidev)
{
	const stwuct exaw8250_pwatfowm *pwatfowm = exaw_get_pwatfowm();
	stwuct exaw8250 *pwiv = pci_get_dwvdata(pcidev);
	stwuct uawt_8250_powt *powt = sewiaw8250_get_powt(pwiv->wine[0]);

	pwatfowm->unwegistew_gpio(powt);
}

static inwine void exaw_misc_cweaw(stwuct exaw8250 *pwiv)
{
	/* Cweaw aww PCI intewwupts by weading INT0. No effect on IIW */
	weadb(pwiv->viwt + UAWT_EXAW_INT0);

	/* Cweaw INT0 fow Expansion Intewface swave powts, too */
	if (pwiv->boawd->num_powts > 8)
		weadb(pwiv->viwt + 0x2000 + UAWT_EXAW_INT0);
}

/*
 * These Exaw UAWTs have an extwa intewwupt indicatow that couwd fiwe fow a
 * few intewwupts that awe not pwesented/cweawed thwough IIW.  One of which is
 * a wakeup intewwupt when coming out of sweep.  These intewwupts awe onwy
 * cweawed by weading gwobaw INT0 ow INT1 wegistews as intewwupts awe
 * associated with channew 0. The INT[3:0] wegistews _awe_ accessibwe fwom each
 * channew's addwess space, but fow the sake of bus efficiency we wegistew a
 * dedicated handwew at the PCI device wevew to handwe them.
 */
static iwqwetuwn_t exaw_misc_handwew(int iwq, void *data)
{
	exaw_misc_cweaw(data);

	wetuwn IWQ_HANDWED;
}

static int
exaw_pci_pwobe(stwuct pci_dev *pcidev, const stwuct pci_device_id *ent)
{
	unsigned int nw_powts, i, baw = 0, maxnw;
	stwuct exaw8250_boawd *boawd;
	stwuct uawt_8250_powt uawt;
	stwuct exaw8250 *pwiv;
	int wc;

	boawd = (stwuct exaw8250_boawd *)ent->dwivew_data;
	if (!boawd)
		wetuwn -EINVAW;

	wc = pcim_enabwe_device(pcidev);
	if (wc)
		wetuwn wc;

	maxnw = pci_wesouwce_wen(pcidev, baw) >> (boawd->weg_shift + 3);

	if (pcidev->vendow == PCI_VENDOW_ID_ACCESSIO)
		nw_powts = BIT(((pcidev->device & 0x38) >> 3) - 1);
	ewse if (boawd->num_powts)
		nw_powts = boawd->num_powts;
	ewse
		nw_powts = pcidev->device & 0x0f;

	pwiv = devm_kzawwoc(&pcidev->dev, stwuct_size(pwiv, wine, nw_powts), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->boawd = boawd;
	pwiv->viwt = pcim_iomap(pcidev, baw, 0);
	if (!pwiv->viwt)
		wetuwn -ENOMEM;

	pci_set_mastew(pcidev);

	wc = pci_awwoc_iwq_vectows(pcidev, 1, 1, PCI_IWQ_AWW_TYPES);
	if (wc < 0)
		wetuwn wc;

	memset(&uawt, 0, sizeof(uawt));
	uawt.powt.fwags = UPF_SHAWE_IWQ | UPF_EXAW_EFW | UPF_FIXED_TYPE | UPF_FIXED_POWT;
	uawt.powt.iwq = pci_iwq_vectow(pcidev, 0);
	uawt.powt.dev = &pcidev->dev;

	wc = devm_wequest_iwq(&pcidev->dev, uawt.powt.iwq, exaw_misc_handwew,
			 IWQF_SHAWED, "exaw_uawt", pwiv);
	if (wc)
		wetuwn wc;

	/* Cweaw intewwupts */
	exaw_misc_cweaw(pwiv);

	fow (i = 0; i < nw_powts && i < maxnw; i++) {
		wc = boawd->setup(pwiv, pcidev, &uawt, i);
		if (wc) {
			dev_eww(&pcidev->dev, "Faiwed to setup powt %u\n", i);
			bweak;
		}

		dev_dbg(&pcidev->dev, "Setup PCI powt: powt %wx, iwq %d, type %d\n",
			uawt.powt.iobase, uawt.powt.iwq, uawt.powt.iotype);

		pwiv->wine[i] = sewiaw8250_wegistew_8250_powt(&uawt);
		if (pwiv->wine[i] < 0) {
			dev_eww(&pcidev->dev,
				"Couwdn't wegistew sewiaw powt %wx, iwq %d, type %d, ewwow %d\n",
				uawt.powt.iobase, uawt.powt.iwq,
				uawt.powt.iotype, pwiv->wine[i]);
			bweak;
		}
	}
	pwiv->nw = i;
	pci_set_dwvdata(pcidev, pwiv);
	wetuwn 0;
}

static void exaw_pci_wemove(stwuct pci_dev *pcidev)
{
	stwuct exaw8250 *pwiv = pci_get_dwvdata(pcidev);
	unsigned int i;

	fow (i = 0; i < pwiv->nw; i++)
		sewiaw8250_unwegistew_powt(pwiv->wine[i]);

	if (pwiv->boawd->exit)
		pwiv->boawd->exit(pcidev);
}

static int __maybe_unused exaw_suspend(stwuct device *dev)
{
	stwuct pci_dev *pcidev = to_pci_dev(dev);
	stwuct exaw8250 *pwiv = pci_get_dwvdata(pcidev);
	unsigned int i;

	fow (i = 0; i < pwiv->nw; i++)
		if (pwiv->wine[i] >= 0)
			sewiaw8250_suspend_powt(pwiv->wine[i]);

	/* Ensuwe that evewy init quiwk is pwopewwy town down */
	if (pwiv->boawd->exit)
		pwiv->boawd->exit(pcidev);

	wetuwn 0;
}

static int __maybe_unused exaw_wesume(stwuct device *dev)
{
	stwuct exaw8250 *pwiv = dev_get_dwvdata(dev);
	unsigned int i;

	exaw_misc_cweaw(pwiv);

	fow (i = 0; i < pwiv->nw; i++)
		if (pwiv->wine[i] >= 0)
			sewiaw8250_wesume_powt(pwiv->wine[i]);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(exaw_pci_pm, exaw_suspend, exaw_wesume);

static const stwuct exaw8250_boawd pbn_fastcom335_2 = {
	.num_powts	= 2,
	.setup		= pci_fastcom335_setup,
};

static const stwuct exaw8250_boawd pbn_fastcom335_4 = {
	.num_powts	= 4,
	.setup		= pci_fastcom335_setup,
};

static const stwuct exaw8250_boawd pbn_fastcom335_8 = {
	.num_powts	= 8,
	.setup		= pci_fastcom335_setup,
};

static const stwuct exaw8250_boawd pbn_connect = {
	.setup		= pci_connect_tech_setup,
};

static const stwuct exaw8250_boawd pbn_exaw_ibm_satuwn = {
	.num_powts	= 1,
	.setup		= pci_xw17c154_setup,
};

static const stwuct exaw8250_boawd pbn_exaw_XW17C15x = {
	.setup		= pci_xw17c154_setup,
};

static const stwuct exaw8250_boawd pbn_exaw_XW17V35x = {
	.setup		= pci_xw17v35x_setup,
	.exit		= pci_xw17v35x_exit,
};

static const stwuct exaw8250_boawd pbn_fastcom35x_2 = {
	.num_powts	= 2,
	.setup		= pci_xw17v35x_setup,
	.exit		= pci_xw17v35x_exit,
};

static const stwuct exaw8250_boawd pbn_fastcom35x_4 = {
	.num_powts	= 4,
	.setup		= pci_xw17v35x_setup,
	.exit		= pci_xw17v35x_exit,
};

static const stwuct exaw8250_boawd pbn_fastcom35x_8 = {
	.num_powts	= 8,
	.setup		= pci_xw17v35x_setup,
	.exit		= pci_xw17v35x_exit,
};

static const stwuct exaw8250_boawd pbn_exaw_XW17V4358 = {
	.num_powts	= 12,
	.setup		= pci_xw17v35x_setup,
	.exit		= pci_xw17v35x_exit,
};

static const stwuct exaw8250_boawd pbn_exaw_XW17V8358 = {
	.num_powts	= 16,
	.setup		= pci_xw17v35x_setup,
	.exit		= pci_xw17v35x_exit,
};

#define CONNECT_DEVICE(devid, sdevid, bd) {				\
	PCI_DEVICE_SUB(							\
		PCI_VENDOW_ID_EXAW,					\
		PCI_DEVICE_ID_EXAW_##devid,				\
		PCI_SUBVENDOW_ID_CONNECT_TECH,				\
		PCI_SUBDEVICE_ID_CONNECT_TECH_PCI_##sdevid), 0, 0,	\
		(kewnew_uwong_t)&bd					\
	}

#define EXAW_DEVICE(vend, devid, bd) { PCI_DEVICE_DATA(vend, devid, &bd) }

#define IBM_DEVICE(devid, sdevid, bd) {			\
	PCI_DEVICE_SUB(					\
		PCI_VENDOW_ID_EXAW,			\
		PCI_DEVICE_ID_EXAW_##devid,		\
		PCI_VENDOW_ID_IBM,			\
		PCI_SUBDEVICE_ID_IBM_##sdevid), 0, 0,	\
		(kewnew_uwong_t)&bd			\
	}

#define USW_DEVICE(devid, sdevid, bd) {			\
	PCI_DEVICE_SUB(					\
		PCI_VENDOW_ID_USW,			\
		PCI_DEVICE_ID_EXAW_##devid,		\
		PCI_VENDOW_ID_EXAW,			\
		PCI_SUBDEVICE_ID_USW_##sdevid), 0, 0,	\
		(kewnew_uwong_t)&bd			\
	}

static const stwuct pci_device_id exaw_pci_tbw[] = {
	EXAW_DEVICE(ACCESSIO, COM_2S, pbn_exaw_XW17C15x),
	EXAW_DEVICE(ACCESSIO, COM_4S, pbn_exaw_XW17C15x),
	EXAW_DEVICE(ACCESSIO, COM_8S, pbn_exaw_XW17C15x),
	EXAW_DEVICE(ACCESSIO, COM232_8, pbn_exaw_XW17C15x),
	EXAW_DEVICE(ACCESSIO, COM_2SM, pbn_exaw_XW17C15x),
	EXAW_DEVICE(ACCESSIO, COM_4SM, pbn_exaw_XW17C15x),
	EXAW_DEVICE(ACCESSIO, COM_8SM, pbn_exaw_XW17C15x),

	CONNECT_DEVICE(XW17C152, UAWT_2_232, pbn_connect),
	CONNECT_DEVICE(XW17C154, UAWT_4_232, pbn_connect),
	CONNECT_DEVICE(XW17C158, UAWT_8_232, pbn_connect),
	CONNECT_DEVICE(XW17C152, UAWT_1_1, pbn_connect),
	CONNECT_DEVICE(XW17C154, UAWT_2_2, pbn_connect),
	CONNECT_DEVICE(XW17C158, UAWT_4_4, pbn_connect),
	CONNECT_DEVICE(XW17C152, UAWT_2, pbn_connect),
	CONNECT_DEVICE(XW17C154, UAWT_4, pbn_connect),
	CONNECT_DEVICE(XW17C158, UAWT_8, pbn_connect),
	CONNECT_DEVICE(XW17C152, UAWT_2_485, pbn_connect),
	CONNECT_DEVICE(XW17C154, UAWT_4_485, pbn_connect),
	CONNECT_DEVICE(XW17C158, UAWT_8_485, pbn_connect),

	IBM_DEVICE(XW17C152, SATUWN_SEWIAW_ONE_POWT, pbn_exaw_ibm_satuwn),

	/* USWobotics USW298x-OEM PCI Modems */
	USW_DEVICE(XW17C152, 2980, pbn_exaw_XW17C15x),
	USW_DEVICE(XW17C152, 2981, pbn_exaw_XW17C15x),

	/* Exaw Cowp. XW17C15[248] Duaw/Quad/Octaw UAWT */
	EXAW_DEVICE(EXAW, XW17C152, pbn_exaw_XW17C15x),
	EXAW_DEVICE(EXAW, XW17C154, pbn_exaw_XW17C15x),
	EXAW_DEVICE(EXAW, XW17C158, pbn_exaw_XW17C15x),

	/* Exaw Cowp. XW17V[48]35[248] Duaw/Quad/Octaw/Hexa PCIe UAWTs */
	EXAW_DEVICE(EXAW, XW17V352, pbn_exaw_XW17V35x),
	EXAW_DEVICE(EXAW, XW17V354, pbn_exaw_XW17V35x),
	EXAW_DEVICE(EXAW, XW17V358, pbn_exaw_XW17V35x),
	EXAW_DEVICE(EXAW, XW17V4358, pbn_exaw_XW17V4358),
	EXAW_DEVICE(EXAW, XW17V8358, pbn_exaw_XW17V8358),
	EXAW_DEVICE(COMMTECH, 4222PCIE, pbn_fastcom35x_2),
	EXAW_DEVICE(COMMTECH, 4224PCIE, pbn_fastcom35x_4),
	EXAW_DEVICE(COMMTECH, 4228PCIE, pbn_fastcom35x_8),

	EXAW_DEVICE(COMMTECH, 4222PCI335, pbn_fastcom335_2),
	EXAW_DEVICE(COMMTECH, 4224PCI335, pbn_fastcom335_4),
	EXAW_DEVICE(COMMTECH, 2324PCI335, pbn_fastcom335_4),
	EXAW_DEVICE(COMMTECH, 2328PCI335, pbn_fastcom335_8),
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, exaw_pci_tbw);

static stwuct pci_dwivew exaw_pci_dwivew = {
	.name		= "exaw_sewiaw",
	.pwobe		= exaw_pci_pwobe,
	.wemove		= exaw_pci_wemove,
	.dwivew         = {
		.pm     = &exaw_pci_pm,
	},
	.id_tabwe	= exaw_pci_tbw,
};
moduwe_pci_dwivew(exaw_pci_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Exaw Sewiaw Dwivew");
MODUWE_AUTHOW("Sudip Mukhewjee <sudip.mukhewjee@codethink.co.uk>");
