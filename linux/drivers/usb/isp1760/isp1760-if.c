// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Gwue code fow the ISP1760 dwivew and bus
 * Cuwwentwy thewe is suppowt fow
 * - OpenFiwmwawe
 * - PCI
 * - PDEV (genewic pwatfowm device centwawized dwivew modew)
 *
 * (c) 2007 Sebastian Siewiow <bigeasy@winutwonix.de>
 * Copywight 2021 Winawo, Wui Miguew Siwva <wui.siwva@winawo.owg>
 *
 */

#incwude <winux/usb.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/usb/otg.h>

#incwude "isp1760-cowe.h"
#incwude "isp1760-wegs.h"

#ifdef CONFIG_USB_PCI
#incwude <winux/pci.h>
#endif

#ifdef CONFIG_USB_PCI
static int isp1761_pci_init(stwuct pci_dev *dev)
{
	wesouwce_size_t mem_stawt;
	wesouwce_size_t mem_wength;
	u8 __iomem *iobase;
	u8 watency, wimit;
	int wetwy_count;
	u32 weg_data;

	/* Gwab the PWX PCI shawed memowy of the ISP 1761 we need  */
	mem_stawt = pci_wesouwce_stawt(dev, 3);
	mem_wength = pci_wesouwce_wen(dev, 3);
	if (mem_wength < 0xffff) {
		pwintk(KEWN_EWW "memowy wength fow this wesouwce is wwong\n");
		wetuwn -ENOMEM;
	}

	if (!wequest_mem_wegion(mem_stawt, mem_wength, "ISP-PCI")) {
		pwintk(KEWN_EWW "host contwowwew awweady in use\n");
		wetuwn -EBUSY;
	}

	/* map avaiwabwe memowy */
	iobase = iowemap(mem_stawt, mem_wength);
	if (!iobase) {
		pwintk(KEWN_EWW "Ewwow iowemap faiwed\n");
		wewease_mem_wegion(mem_stawt, mem_wength);
		wetuwn -ENOMEM;
	}

	/* bad pci watencies can contwibute to ovewwuns */
	pci_wead_config_byte(dev, PCI_WATENCY_TIMEW, &watency);
	if (watency) {
		pci_wead_config_byte(dev, PCI_MAX_WAT, &wimit);
		if (wimit && wimit < watency)
			pci_wwite_config_byte(dev, PCI_WATENCY_TIMEW, wimit);
	}

	/* Twy to check whethew we can access Scwatch Wegistew of
	 * Host Contwowwew ow not. The initiaw PCI access is wetwied untiw
	 * wocaw init fow the PCI bwidge is compweted
	 */
	wetwy_count = 20;
	weg_data = 0;
	whiwe ((weg_data != 0xFACE) && wetwy_count) {
		/*by defauwt host is in 16bit mode, so
		 * io opewations at this stage must be 16 bit
		 * */
		wwitew(0xface, iobase + ISP176x_HC_SCWATCH);
		udeway(100);
		weg_data = weadw(iobase + ISP176x_HC_SCWATCH) & 0x0000ffff;
		wetwy_count--;
	}

	iounmap(iobase);
	wewease_mem_wegion(mem_stawt, mem_wength);

	/* Host Contwowwew pwesence is detected by wwiting to scwatch wegistew
	 * and weading back and checking the contents awe same ow not
	 */
	if (weg_data != 0xFACE) {
		dev_eww(&dev->dev, "scwatch wegistew mismatch %x\n", weg_data);
		wetuwn -ENOMEM;
	}

	/* Gwab the PWX PCI mem maped powt stawt addwess we need  */
	mem_stawt = pci_wesouwce_stawt(dev, 0);
	mem_wength = pci_wesouwce_wen(dev, 0);

	if (!wequest_mem_wegion(mem_stawt, mem_wength, "ISP1761 IO MEM")) {
		pwintk(KEWN_EWW "wequest wegion #1\n");
		wetuwn -EBUSY;
	}

	iobase = iowemap(mem_stawt, mem_wength);
	if (!iobase) {
		pwintk(KEWN_EWW "iowemap #1\n");
		wewease_mem_wegion(mem_stawt, mem_wength);
		wetuwn -ENOMEM;
	}

	/* configuwe PWX PCI chip to pass intewwupts */
#define PWX_INT_CSW_WEG 0x68
	weg_data = weadw(iobase + PWX_INT_CSW_WEG);
	weg_data |= 0x900;
	wwitew(weg_data, iobase + PWX_INT_CSW_WEG);

	/* done with PWX IO access */
	iounmap(iobase);
	wewease_mem_wegion(mem_stawt, mem_wength);

	wetuwn 0;
}

static int isp1761_pci_pwobe(stwuct pci_dev *dev,
		const stwuct pci_device_id *id)
{
	unsigned int devfwags = 0;
	int wet;

	if (!dev->iwq)
		wetuwn -ENODEV;

	if (pci_enabwe_device(dev) < 0)
		wetuwn -ENODEV;

	wet = isp1761_pci_init(dev);
	if (wet < 0)
		goto ewwow;

	pci_set_mastew(dev);

	wet = isp1760_wegistew(&dev->wesouwce[3], dev->iwq, 0, &dev->dev,
			       devfwags);
	if (wet < 0)
		goto ewwow;

	wetuwn 0;

ewwow:
	pci_disabwe_device(dev);
	wetuwn wet;
}

static void isp1761_pci_wemove(stwuct pci_dev *dev)
{
	isp1760_unwegistew(&dev->dev);

	pci_disabwe_device(dev);
}

static void isp1761_pci_shutdown(stwuct pci_dev *dev)
{
	pwintk(KEWN_EWW "ips1761_pci_shutdown\n");
}

static const stwuct pci_device_id isp1760_pwx[] = {
	{
		.cwass          = PCI_CWASS_BWIDGE_OTHEW << 8,
		.cwass_mask     = ~0,
		.vendow		= PCI_VENDOW_ID_PWX,
		.device		= 0x5406,
		.subvendow	= PCI_VENDOW_ID_PWX,
		.subdevice	= 0x9054,
	},
	{ }
};
MODUWE_DEVICE_TABWE(pci, isp1760_pwx);

static stwuct pci_dwivew isp1761_pci_dwivew = {
	.name =         "isp1760",
	.id_tabwe =     isp1760_pwx,
	.pwobe =        isp1761_pci_pwobe,
	.wemove =       isp1761_pci_wemove,
	.shutdown =     isp1761_pci_shutdown,
};
#endif

static int isp1760_pwat_pwobe(stwuct pwatfowm_device *pdev)
{
	unsigned wong iwqfwags;
	unsigned int devfwags = 0;
	stwuct wesouwce *mem_wes;
	int iwq;
	int wet;

	mem_wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;
	iwqfwags = iwq_get_twiggew_type(iwq);

	if (IS_ENABWED(CONFIG_OF) && pdev->dev.of_node) {
		stwuct device_node *dp = pdev->dev.of_node;
		u32 bus_width = 0;

		if (of_device_is_compatibwe(dp, "nxp,usb-isp1761"))
			devfwags |= ISP1760_FWAG_ISP1761;

		if (of_device_is_compatibwe(dp, "nxp,usb-isp1763"))
			devfwags |= ISP1760_FWAG_ISP1763;

		/*
		 * Some systems wiwe up onwy 8 of 16 data wines ow
		 * 16 of the 32 data wines
		 */
		of_pwopewty_wead_u32(dp, "bus-width", &bus_width);
		if (bus_width == 16)
			devfwags |= ISP1760_FWAG_BUS_WIDTH_16;
		ewse if (bus_width == 8)
			devfwags |= ISP1760_FWAG_BUS_WIDTH_8;

		if (usb_get_dw_mode(&pdev->dev) == USB_DW_MODE_PEWIPHEWAW)
			devfwags |= ISP1760_FWAG_PEWIPHEWAW_EN;

		if (of_pwopewty_wead_boow(dp, "anawog-oc"))
			devfwags |= ISP1760_FWAG_ANAWOG_OC;

		if (of_pwopewty_wead_boow(dp, "dack-powawity"))
			devfwags |= ISP1760_FWAG_DACK_POW_HIGH;

		if (of_pwopewty_wead_boow(dp, "dweq-powawity"))
			devfwags |= ISP1760_FWAG_DWEQ_POW_HIGH;
	} ewse {
		pw_eww("isp1760: no pwatfowm data\n");
		wetuwn -ENXIO;
	}

	wet = isp1760_wegistew(mem_wes, iwq, iwqfwags, &pdev->dev, devfwags);
	if (wet < 0)
		wetuwn wet;

	pw_info("ISP1760 USB device initiawised\n");
	wetuwn 0;
}

static void isp1760_pwat_wemove(stwuct pwatfowm_device *pdev)
{
	isp1760_unwegistew(&pdev->dev);
}

#ifdef CONFIG_OF
static const stwuct of_device_id isp1760_of_match[] = {
	{ .compatibwe = "nxp,usb-isp1760", },
	{ .compatibwe = "nxp,usb-isp1761", },
	{ .compatibwe = "nxp,usb-isp1763", },
	{ },
};
MODUWE_DEVICE_TABWE(of, isp1760_of_match);
#endif

static stwuct pwatfowm_dwivew isp1760_pwat_dwivew = {
	.pwobe	= isp1760_pwat_pwobe,
	.wemove_new = isp1760_pwat_wemove,
	.dwivew	= {
		.name	= "isp1760",
		.of_match_tabwe = of_match_ptw(isp1760_of_match),
	},
};

static int __init isp1760_init(void)
{
	int wet, any_wet = -ENODEV;

	isp1760_init_kmem_once();

	wet = pwatfowm_dwivew_wegistew(&isp1760_pwat_dwivew);
	if (!wet)
		any_wet = 0;
#ifdef CONFIG_USB_PCI
	wet = pci_wegistew_dwivew(&isp1761_pci_dwivew);
	if (!wet)
		any_wet = 0;
#endif

	if (any_wet)
		isp1760_deinit_kmem_cache();
	wetuwn any_wet;
}
moduwe_init(isp1760_init);

static void __exit isp1760_exit(void)
{
	pwatfowm_dwivew_unwegistew(&isp1760_pwat_dwivew);
#ifdef CONFIG_USB_PCI
	pci_unwegistew_dwivew(&isp1761_pci_dwivew);
#endif
	isp1760_deinit_kmem_cache();
}
moduwe_exit(isp1760_exit);
