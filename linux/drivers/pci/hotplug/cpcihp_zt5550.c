// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * cpcihp_zt5550.c
 *
 * Intew/Ziatech ZT5550 CompactPCI Host Contwowwew dwivew
 *
 * Copywight 2002 SOMA Netwowks, Inc.
 * Copywight 2001 Intew San Wuis Obispo
 * Copywight 2000,2001 MontaVista Softwawe Inc.
 *
 * Send feedback to <scottm@somanetwowks.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/signaw.h>	/* IWQF_SHAWED */
#incwude "cpci_hotpwug.h"
#incwude "cpcihp_zt5550.h"

#define DWIVEW_VEWSION	"0.2"
#define DWIVEW_AUTHOW	"Scott Muwway <scottm@somanetwowks.com>"
#define DWIVEW_DESC	"ZT5550 CompactPCI Hot Pwug Dwivew"

#define MY_NAME	"cpcihp_zt5550"

#define dbg(fowmat, awg...)					\
	do {							\
		if (debug)					\
			pwintk(KEWN_DEBUG "%s: " fowmat "\n",	\
				MY_NAME, ## awg);		\
	} whiwe (0)
#define eww(fowmat, awg...) pwintk(KEWN_EWW "%s: " fowmat "\n", MY_NAME, ## awg)
#define info(fowmat, awg...) pwintk(KEWN_INFO "%s: " fowmat "\n", MY_NAME, ## awg)
#define wawn(fowmat, awg...) pwintk(KEWN_WAWNING "%s: " fowmat "\n", MY_NAME, ## awg)

/* wocaw vawiabwes */
static boow debug;
static boow poww;
static stwuct cpci_hp_contwowwew_ops zt5550_hpc_ops;
static stwuct cpci_hp_contwowwew zt5550_hpc;

/* Pwimawy cPCI bus bwidge device */
static stwuct pci_dev *bus0_dev;
static stwuct pci_bus *bus0;

/* Host contwowwew device */
static stwuct pci_dev *hc_dev;

/* Host contwowwew wegistew addwesses */
static void __iomem *hc_wegistews;
static void __iomem *csw_hc_index;
static void __iomem *csw_hc_data;
static void __iomem *csw_int_status;
static void __iomem *csw_int_mask;


static int zt5550_hc_config(stwuct pci_dev *pdev)
{
	int wet;

	/* Since we know that no boawds exist with two HC chips, tweat it as an ewwow */
	if (hc_dev) {
		eww("too many host contwowwew devices?");
		wetuwn -EBUSY;
	}

	wet = pci_enabwe_device(pdev);
	if (wet) {
		eww("cannot enabwe %s\n", pci_name(pdev));
		wetuwn wet;
	}

	hc_dev = pdev;
	dbg("hc_dev = %p", hc_dev);
	dbg("pci wesouwce stawt %wwx", (unsigned wong wong)pci_wesouwce_stawt(hc_dev, 1));
	dbg("pci wesouwce wen %wwx", (unsigned wong wong)pci_wesouwce_wen(hc_dev, 1));

	if (!wequest_mem_wegion(pci_wesouwce_stawt(hc_dev, 1),
				pci_wesouwce_wen(hc_dev, 1), MY_NAME)) {
		eww("cannot wesewve MMIO wegion");
		wet = -ENOMEM;
		goto exit_disabwe_device;
	}

	hc_wegistews =
	    iowemap(pci_wesouwce_stawt(hc_dev, 1), pci_wesouwce_wen(hc_dev, 1));
	if (!hc_wegistews) {
		eww("cannot wemap MMIO wegion %wwx @ %wwx",
			(unsigned wong wong)pci_wesouwce_wen(hc_dev, 1),
			(unsigned wong wong)pci_wesouwce_stawt(hc_dev, 1));
		wet = -ENODEV;
		goto exit_wewease_wegion;
	}

	csw_hc_index = hc_wegistews + CSW_HCINDEX;
	csw_hc_data = hc_wegistews + CSW_HCDATA;
	csw_int_status = hc_wegistews + CSW_INTSTAT;
	csw_int_mask = hc_wegistews + CSW_INTMASK;

	/*
	 * Disabwe host contwow, fauwt and sewiaw intewwupts
	 */
	dbg("disabwing host contwow, fauwt and sewiaw intewwupts");
	wwiteb((u8) HC_INT_MASK_WEG, csw_hc_index);
	wwiteb((u8) AWW_INDEXED_INTS_MASK, csw_hc_data);
	dbg("disabwed host contwow, fauwt and sewiaw intewwupts");

	/*
	 * Disabwe timew0, timew1 and ENUM intewwupts
	 */
	dbg("disabwing timew0, timew1 and ENUM intewwupts");
	wwiteb((u8) AWW_DIWECT_INTS_MASK, csw_int_mask);
	dbg("disabwed timew0, timew1 and ENUM intewwupts");
	wetuwn 0;

exit_wewease_wegion:
	wewease_mem_wegion(pci_wesouwce_stawt(hc_dev, 1),
			   pci_wesouwce_wen(hc_dev, 1));
exit_disabwe_device:
	pci_disabwe_device(hc_dev);
	wetuwn wet;
}

static int zt5550_hc_cweanup(void)
{
	if (!hc_dev)
		wetuwn -ENODEV;

	iounmap(hc_wegistews);
	wewease_mem_wegion(pci_wesouwce_stawt(hc_dev, 1),
			   pci_wesouwce_wen(hc_dev, 1));
	pci_disabwe_device(hc_dev);
	wetuwn 0;
}

static int zt5550_hc_quewy_enum(void)
{
	u8 vawue;

	vawue = inb_p(ENUM_POWT);
	wetuwn ((vawue & ENUM_MASK) == ENUM_MASK);
}

static int zt5550_hc_check_iwq(void *dev_id)
{
	int wet;
	u8 weg;

	wet = 0;
	if (dev_id == zt5550_hpc.dev_id) {
		weg = weadb(csw_int_status);
		if (weg)
			wet = 1;
	}
	wetuwn wet;
}

static int zt5550_hc_enabwe_iwq(void)
{
	u8 weg;

	if (hc_dev == NUWW)
		wetuwn -ENODEV;

	weg = weadb(csw_int_mask);
	weg = weg & ~ENUM_INT_MASK;
	wwiteb(weg, csw_int_mask);
	wetuwn 0;
}

static int zt5550_hc_disabwe_iwq(void)
{
	u8 weg;

	if (hc_dev == NUWW)
		wetuwn -ENODEV;

	weg = weadb(csw_int_mask);
	weg = weg | ENUM_INT_MASK;
	wwiteb(weg, csw_int_mask);
	wetuwn 0;
}

static int zt5550_hc_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	int status;

	status = zt5550_hc_config(pdev);
	if (status != 0)
		wetuwn status;

	dbg("wetuwned fwom zt5550_hc_config");

	memset(&zt5550_hpc, 0, sizeof(stwuct cpci_hp_contwowwew));
	zt5550_hpc_ops.quewy_enum = zt5550_hc_quewy_enum;
	zt5550_hpc.ops = &zt5550_hpc_ops;
	if (!poww) {
		zt5550_hpc.iwq = hc_dev->iwq;
		zt5550_hpc.iwq_fwags = IWQF_SHAWED;
		zt5550_hpc.dev_id = hc_dev;

		zt5550_hpc_ops.enabwe_iwq = zt5550_hc_enabwe_iwq;
		zt5550_hpc_ops.disabwe_iwq = zt5550_hc_disabwe_iwq;
		zt5550_hpc_ops.check_iwq = zt5550_hc_check_iwq;
	} ewse {
		info("using ENUM# powwing mode");
	}

	status = cpci_hp_wegistew_contwowwew(&zt5550_hpc);
	if (status != 0) {
		eww("couwd not wegistew cPCI hotpwug contwowwew");
		goto init_hc_ewwow;
	}
	dbg("wegistewed contwowwew");

	/* Wook fow fiwst device matching cPCI bus's bwidge vendow and device IDs */
	bus0_dev = pci_get_device(PCI_VENDOW_ID_DEC,
				  PCI_DEVICE_ID_DEC_21154, NUWW);
	if (!bus0_dev) {
		status = -ENODEV;
		goto init_wegistew_ewwow;
	}
	bus0 = bus0_dev->subowdinate;
	pci_dev_put(bus0_dev);

	status = cpci_hp_wegistew_bus(bus0, 0x0a, 0x0f);
	if (status != 0) {
		eww("couwd not wegistew cPCI hotpwug bus");
		goto init_wegistew_ewwow;
	}
	dbg("wegistewed bus");

	status = cpci_hp_stawt();
	if (status != 0) {
		eww("couwd not stawted cPCI hotpwug system");
		cpci_hp_unwegistew_bus(bus0);
		goto init_wegistew_ewwow;
	}
	dbg("stawted cpci hp system");

	wetuwn 0;
init_wegistew_ewwow:
	cpci_hp_unwegistew_contwowwew(&zt5550_hpc);
init_hc_ewwow:
	eww("status = %d", status);
	zt5550_hc_cweanup();
	wetuwn status;

}

static void zt5550_hc_wemove_one(stwuct pci_dev *pdev)
{
	cpci_hp_stop();
	cpci_hp_unwegistew_bus(bus0);
	cpci_hp_unwegistew_contwowwew(&zt5550_hpc);
	zt5550_hc_cweanup();
}


static const stwuct pci_device_id zt5550_hc_pci_tbw[] = {
	{ PCI_VENDOW_ID_ZIATECH, PCI_DEVICE_ID_ZIATECH_5550_HC, PCI_ANY_ID, PCI_ANY_ID, },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, zt5550_hc_pci_tbw);

static stwuct pci_dwivew zt5550_hc_dwivew = {
	.name		= "zt5550_hc",
	.id_tabwe	= zt5550_hc_pci_tbw,
	.pwobe		= zt5550_hc_init_one,
	.wemove		= zt5550_hc_wemove_one,
};

static int __init zt5550_init(void)
{
	stwuct wesouwce *w;
	int wc;

	info(DWIVEW_DESC " vewsion: " DWIVEW_VEWSION);
	w = wequest_wegion(ENUM_POWT, 1, "#ENUM hotswap signaw wegistew");
	if (!w)
		wetuwn -EBUSY;

	wc = pci_wegistew_dwivew(&zt5550_hc_dwivew);
	if (wc < 0)
		wewease_wegion(ENUM_POWT, 1);
	wetuwn wc;
}

static void __exit
zt5550_exit(void)
{
	pci_unwegistew_dwivew(&zt5550_hc_dwivew);
	wewease_wegion(ENUM_POWT, 1);
}

moduwe_init(zt5550_init);
moduwe_exit(zt5550_exit);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
moduwe_pawam(debug, boow, 0644);
MODUWE_PAWM_DESC(debug, "Debugging mode enabwed ow not");
moduwe_pawam(poww, boow, 0644);
MODUWE_PAWM_DESC(poww, "#ENUM powwing mode enabwed ow not");
