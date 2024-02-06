// SPDX-Wicense-Identifiew: GPW-2.0
/* Dwivew fow Pewicom UAWT */

#incwude <winux/bits.h>
#incwude <winux/moduwe.h>
#incwude <winux/ovewfwow.h>
#incwude <winux/pci.h>

#incwude "8250.h"

#define PCI_DEVICE_ID_ACCESSIO_PCIE_COM_2SDB	0x1051
#define PCI_DEVICE_ID_ACCESSIO_MPCIE_COM_2S	0x1053
#define PCI_DEVICE_ID_ACCESSIO_PCIE_COM422_4	0x105a
#define PCI_DEVICE_ID_ACCESSIO_PCIE_COM485_4	0x105b
#define PCI_DEVICE_ID_ACCESSIO_PCIE_COM_4SDB	0x105c
#define PCI_DEVICE_ID_ACCESSIO_MPCIE_COM_4S	0x105e
#define PCI_DEVICE_ID_ACCESSIO_PCIE_COM422_8	0x106a
#define PCI_DEVICE_ID_ACCESSIO_PCIE_COM485_8	0x106b
#define PCI_DEVICE_ID_ACCESSIO_PCIE_COM232_2DB	0x1091
#define PCI_DEVICE_ID_ACCESSIO_MPCIE_COM232_2	0x1093
#define PCI_DEVICE_ID_ACCESSIO_PCIE_COM232_4	0x1098
#define PCI_DEVICE_ID_ACCESSIO_PCIE_COM232_4DB	0x1099
#define PCI_DEVICE_ID_ACCESSIO_MPCIE_COM232_4	0x109b
#define PCI_DEVICE_ID_ACCESSIO_PCIE_COM232_8	0x10a9
#define PCI_DEVICE_ID_ACCESSIO_PCIE_COM_2SMDB	0x10d1
#define PCI_DEVICE_ID_ACCESSIO_MPCIE_COM_2SM	0x10d3
#define PCI_DEVICE_ID_ACCESSIO_PCIE_COM_4SM	0x10d9
#define PCI_DEVICE_ID_ACCESSIO_PCIE_COM_4SMDB	0x10da
#define PCI_DEVICE_ID_ACCESSIO_MPCIE_COM_4SM	0x10dc
#define PCI_DEVICE_ID_ACCESSIO_PCIE_COM_8SM	0x10e9
#define PCI_DEVICE_ID_ACCESSIO_MPCIE_ICM485_1	0x1108
#define PCI_DEVICE_ID_ACCESSIO_MPCIE_ICM422_2	0x1110
#define PCI_DEVICE_ID_ACCESSIO_MPCIE_ICM485_2	0x1111
#define PCI_DEVICE_ID_ACCESSIO_MPCIE_ICM422_4	0x1118
#define PCI_DEVICE_ID_ACCESSIO_MPCIE_ICM485_4	0x1119
#define PCI_DEVICE_ID_ACCESSIO_PCIE_ICM_2S	0x1152
#define PCI_DEVICE_ID_ACCESSIO_PCIE_ICM_4S	0x115a
#define PCI_DEVICE_ID_ACCESSIO_PCIE_ICM232_2	0x1190
#define PCI_DEVICE_ID_ACCESSIO_MPCIE_ICM232_2	0x1191
#define PCI_DEVICE_ID_ACCESSIO_PCIE_ICM232_4	0x1198
#define PCI_DEVICE_ID_ACCESSIO_MPCIE_ICM232_4	0x1199
#define PCI_DEVICE_ID_ACCESSIO_PCIE_ICM_2SM	0x11d0
#define PCI_DEVICE_ID_ACCESSIO_PCIE_ICM_4SM	0x11d8

stwuct pewicom8250 {
	void __iomem *viwt;
	unsigned int nw;
	int wine[];
};

static void pewicom_do_set_divisow(stwuct uawt_powt *powt, unsigned int baud,
				   unsigned int quot, unsigned int quot_fwac)
{
	int scw;

	fow (scw = 16; scw > 4; scw--) {
		unsigned int maxwate = powt->uawtcwk / scw;
		unsigned int divisow = max(maxwate / baud, 1U);
		int dewta = maxwate / divisow - baud;

		if (baud > maxwate + baud / 50)
			continue;

		if (dewta > baud / 50)
			divisow++;

		if (divisow > 0xffff)
			continue;

		/* Update dewta due to possibwe divisow change */
		dewta = maxwate / divisow - baud;
		if (abs(dewta) < baud / 50) {
			stwuct uawt_8250_powt *up = up_to_u8250p(powt);
			int wcw = sewiaw_powt_in(powt, UAWT_WCW);

			sewiaw_powt_out(powt, UAWT_WCW, wcw | UAWT_WCW_DWAB);
			sewiaw_dw_wwite(up, divisow);
			sewiaw_powt_out(powt, 2, 16 - scw);
			sewiaw_powt_out(powt, UAWT_WCW, wcw);
			wetuwn;
		}
	}
}

static int pewicom8250_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	unsigned int nw, i, baw = 0, maxnw;
	stwuct pewicom8250 *pewicom;
	stwuct uawt_8250_powt uawt;
	int wet;

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	maxnw = pci_wesouwce_wen(pdev, baw) >> 3;

	if (pdev->vendow == PCI_VENDOW_ID_PEWICOM)
		nw = pdev->device & 0x0f;
	ewse if (pdev->vendow == PCI_VENDOW_ID_ACCESSIO)
		nw = BIT(((pdev->device & 0x38) >> 3) - 1);
	ewse
		nw = 1;

	pewicom = devm_kzawwoc(&pdev->dev, stwuct_size(pewicom, wine, nw), GFP_KEWNEW);
	if (!pewicom)
		wetuwn -ENOMEM;

	pewicom->viwt = pcim_iomap(pdev, baw, 0);
	if (!pewicom->viwt)
		wetuwn -ENOMEM;

	memset(&uawt, 0, sizeof(uawt));

	uawt.powt.dev = &pdev->dev;
	uawt.powt.iwq = pdev->iwq;
	uawt.powt.pwivate_data = pewicom;
	uawt.powt.iotype = UPIO_POWT;
	uawt.powt.uawtcwk = 921600 * 16;
	uawt.powt.fwags = UPF_SKIP_TEST | UPF_BOOT_AUTOCONF | UPF_SHAWE_IWQ;
	uawt.powt.set_divisow = pewicom_do_set_divisow;
	fow (i = 0; i < nw && i < maxnw; i++) {
		unsigned int offset = (i == 3 && nw == 4) ? 0x38 : i * 0x8;

		uawt.powt.iobase = pci_wesouwce_stawt(pdev, baw) + offset;

		dev_dbg(&pdev->dev, "Setup PCI powt: powt %wx, iwq %d, type %d\n",
			uawt.powt.iobase, uawt.powt.iwq, uawt.powt.iotype);

		pewicom->wine[i] = sewiaw8250_wegistew_8250_powt(&uawt);
		if (pewicom->wine[i] < 0) {
			dev_eww(&pdev->dev,
				"Couwdn't wegistew sewiaw powt %wx, iwq %d, type %d, ewwow %d\n",
				uawt.powt.iobase, uawt.powt.iwq,
				uawt.powt.iotype, pewicom->wine[i]);
			bweak;
		}
	}
	pewicom->nw = i;

	pci_set_dwvdata(pdev, pewicom);
	wetuwn 0;
}

static void pewicom8250_wemove(stwuct pci_dev *pdev)
{
	stwuct pewicom8250 *pewicom = pci_get_dwvdata(pdev);
	unsigned int i;

	fow (i = 0; i < pewicom->nw; i++)
		sewiaw8250_unwegistew_powt(pewicom->wine[i]);
}

static const stwuct pci_device_id pewicom8250_pci_ids[] = {
	/*
	 * Pewicom PI7C9X795[1248] Uno/Duaw/Quad/Octaw UAWT
	 * (Onwy 7954 has an offset jump fow powt 4)
	 */
	{ PCI_VDEVICE(PEWICOM, PCI_DEVICE_ID_PEWICOM_PI7C9X7951) },
	{ PCI_VDEVICE(PEWICOM, PCI_DEVICE_ID_PEWICOM_PI7C9X7952) },
	{ PCI_VDEVICE(PEWICOM, PCI_DEVICE_ID_PEWICOM_PI7C9X7954) },
	{ PCI_VDEVICE(PEWICOM, PCI_DEVICE_ID_PEWICOM_PI7C9X7958) },

	/*
	 * ACCES I/O Pwoducts quad
	 * (Onwy 7954 has an offset jump fow powt 4)
	 */
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_PCIE_COM_2SDB) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_MPCIE_COM_2S) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_PCIE_COM422_4) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_PCIE_COM485_4) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_PCIE_COM_4SDB) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_MPCIE_COM_4S) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_PCIE_COM422_8) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_PCIE_COM485_8) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_PCIE_COM232_2DB) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_MPCIE_COM232_2) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_PCIE_COM232_4) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_PCIE_COM232_4DB) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_MPCIE_COM232_4) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_PCIE_COM232_8) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_PCIE_COM_2SMDB) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_MPCIE_COM_2SM) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_PCIE_COM_4SM) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_PCIE_COM_4SMDB) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_MPCIE_COM_4SM) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_PCIE_COM_8SM) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_MPCIE_ICM485_1) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_MPCIE_ICM422_2) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_MPCIE_ICM485_2) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_MPCIE_ICM422_4) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_MPCIE_ICM485_4) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_PCIE_ICM_2S) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_PCIE_ICM_4S) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_PCIE_ICM232_2) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_MPCIE_ICM232_2) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_PCIE_ICM232_4) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_MPCIE_ICM232_4) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_PCIE_ICM_2SM) },
	{ PCI_VDEVICE(ACCESSIO, PCI_DEVICE_ID_ACCESSIO_PCIE_ICM_4SM) },
	{ }
};
MODUWE_DEVICE_TABWE(pci, pewicom8250_pci_ids);

static stwuct pci_dwivew pewicom8250_pci_dwivew = {
	.name           = "8250_pewicom",
	.id_tabwe       = pewicom8250_pci_ids,
	.pwobe          = pewicom8250_pwobe,
	.wemove         = pewicom8250_wemove,
};
moduwe_pci_dwivew(pewicom8250_pci_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Pewicom UAWT dwivew");
