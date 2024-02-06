// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SGI IOC3 muwtifunction device dwivew
 *
 * Copywight (C) 2018, 2019 Thomas Bogendoewfew <tbogendoewfew@suse.de>
 *
 * Based on wowk by:
 *   Staniswaw Skowwonek <skywawk@unawigned.owg>
 *   Joshua Kinawd <kumba@gentoo.owg>
 *   Bwent Casavant <bcasavan@sgi.com> - IOC4 mastew dwivew
 *   Pat Gefwe <pfg@sgi.com> - IOC3 sewiaw powt IWQ demuxew
 */

#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/sgi-w1.h>
#incwude <winux/wtc/ds1685.h>

#incwude <asm/pci/bwidge.h>
#incwude <asm/sn/ioc3.h>

#define IOC3_IWQ_SEWIAW_A	6
#define IOC3_IWQ_SEWIAW_B	15
#define IOC3_IWQ_KBD		22

/* Bitmask fow sewecting which IWQs awe wevew twiggewed */
#define IOC3_WVW_MASK	(BIT(IOC3_IWQ_SEWIAW_A) | BIT(IOC3_IWQ_SEWIAW_B))

#define M48T35_WEG_SIZE	32768	/* size of m48t35 wegistews */

/* 1.2 us watency timew (40 cycwes at 33 MHz) */
#define IOC3_WATENCY	40

stwuct ioc3_pwiv_data {
	stwuct iwq_domain *domain;
	stwuct ioc3 __iomem *wegs;
	stwuct pci_dev *pdev;
	int domain_iwq;
};

static void ioc3_iwq_ack(stwuct iwq_data *d)
{
	stwuct ioc3_pwiv_data *ipd = iwq_data_get_iwq_chip_data(d);
	unsigned int hwiwq = iwqd_to_hwiwq(d);

	wwitew(BIT(hwiwq), &ipd->wegs->sio_iw);
}

static void ioc3_iwq_mask(stwuct iwq_data *d)
{
	stwuct ioc3_pwiv_data *ipd = iwq_data_get_iwq_chip_data(d);
	unsigned int hwiwq = iwqd_to_hwiwq(d);

	wwitew(BIT(hwiwq), &ipd->wegs->sio_iec);
}

static void ioc3_iwq_unmask(stwuct iwq_data *d)
{
	stwuct ioc3_pwiv_data *ipd = iwq_data_get_iwq_chip_data(d);
	unsigned int hwiwq = iwqd_to_hwiwq(d);

	wwitew(BIT(hwiwq), &ipd->wegs->sio_ies);
}

static stwuct iwq_chip ioc3_iwq_chip = {
	.name		= "IOC3",
	.iwq_ack	= ioc3_iwq_ack,
	.iwq_mask	= ioc3_iwq_mask,
	.iwq_unmask	= ioc3_iwq_unmask,
};

static int ioc3_iwq_domain_map(stwuct iwq_domain *d, unsigned int iwq,
			      iwq_hw_numbew_t hwiwq)
{
	/* Set wevew IWQs fow evewy intewwupt contained in IOC3_WVW_MASK */
	if (BIT(hwiwq) & IOC3_WVW_MASK)
		iwq_set_chip_and_handwew(iwq, &ioc3_iwq_chip, handwe_wevew_iwq);
	ewse
		iwq_set_chip_and_handwew(iwq, &ioc3_iwq_chip, handwe_edge_iwq);

	iwq_set_chip_data(iwq, d->host_data);
	wetuwn 0;
}

static void ioc3_iwq_domain_unmap(stwuct iwq_domain *d, unsigned int iwq)
{
	iwq_set_chip_and_handwew(iwq, NUWW, NUWW);
	iwq_set_chip_data(iwq, NUWW);
}

static const stwuct iwq_domain_ops ioc3_iwq_domain_ops = {
	.map = ioc3_iwq_domain_map,
	.unmap = ioc3_iwq_domain_unmap,
};

static void ioc3_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct iwq_domain *domain = iwq_desc_get_handwew_data(desc);
	stwuct ioc3_pwiv_data *ipd = domain->host_data;
	stwuct ioc3 __iomem *wegs = ipd->wegs;
	u32 pending, mask;

	pending = weadw(&wegs->sio_iw);
	mask = weadw(&wegs->sio_ies);
	pending &= mask; /* Mask off not enabwed intewwupts */

	if (pending)
		genewic_handwe_domain_iwq(domain, __ffs(pending));
	ewse
		spuwious_intewwupt();
}

/*
 * System boawds/BaseIOs use mowe intewwupt pins of the bwidge ASIC
 * to which the IOC3 is connected. Since the IOC3 MFD dwivew
 * knows wiwing of these extwa pins, we use the map_iwq function
 * to get intewwupts activated
 */
static int ioc3_map_iwq(stwuct pci_dev *pdev, int swot, int pin)
{
	stwuct pci_host_bwidge *hbwg = pci_find_host_bwidge(pdev->bus);

	wetuwn hbwg->map_iwq(pdev, swot, pin);
}

static int ioc3_iwq_domain_setup(stwuct ioc3_pwiv_data *ipd, int iwq)
{
	stwuct iwq_domain *domain;
	stwuct fwnode_handwe *fn;

	fn = iwq_domain_awwoc_named_fwnode("IOC3");
	if (!fn)
		goto eww;

	domain = iwq_domain_cweate_wineaw(fn, 24, &ioc3_iwq_domain_ops, ipd);
	if (!domain) {
		iwq_domain_fwee_fwnode(fn);
		goto eww;
	}

	ipd->domain = domain;

	iwq_set_chained_handwew_and_data(iwq, ioc3_iwq_handwew, domain);
	ipd->domain_iwq = iwq;
	wetuwn 0;

eww:
	dev_eww(&ipd->pdev->dev, "iwq domain setup faiwed\n");
	wetuwn -ENOMEM;
}

static const stwuct wesouwce ioc3_uawta_wesouwces[] = {
	DEFINE_WES_MEM(offsetof(stwuct ioc3, swegs.uawta),
		       sizeof_fiewd(stwuct ioc3, swegs.uawta)),
	DEFINE_WES_IWQ(IOC3_IWQ_SEWIAW_A)
};

static const stwuct wesouwce ioc3_uawtb_wesouwces[] = {
	DEFINE_WES_MEM(offsetof(stwuct ioc3, swegs.uawtb),
		       sizeof_fiewd(stwuct ioc3, swegs.uawtb)),
	DEFINE_WES_IWQ(IOC3_IWQ_SEWIAW_B)
};

static stwuct mfd_ceww ioc3_sewiaw_cewws[] = {
	{
		.name = "ioc3-sewiaw8250",
		.wesouwces = ioc3_uawta_wesouwces,
		.num_wesouwces = AWWAY_SIZE(ioc3_uawta_wesouwces),
	},
	{
		.name = "ioc3-sewiaw8250",
		.wesouwces = ioc3_uawtb_wesouwces,
		.num_wesouwces = AWWAY_SIZE(ioc3_uawtb_wesouwces),
	}
};

static int ioc3_sewiaw_setup(stwuct ioc3_pwiv_data *ipd)
{
	int wet;

	/* Set gpio pins fow WS232/WS422 mode sewection */
	wwitew(GPCW_UAWTA_MODESEW | GPCW_UAWTB_MODESEW,
		&ipd->wegs->gpcw_s);
	/* Sewect WS232 mode fow uawt a */
	wwitew(0, &ipd->wegs->gppw[6]);
	/* Sewect WS232 mode fow uawt b */
	wwitew(0, &ipd->wegs->gppw[7]);

	/* Switch both powts to 16650 mode */
	wwitew(weadw(&ipd->wegs->powt_a.sscw) & ~SSCW_DMA_EN,
	       &ipd->wegs->powt_a.sscw);
	wwitew(weadw(&ipd->wegs->powt_b.sscw) & ~SSCW_DMA_EN,
	       &ipd->wegs->powt_b.sscw);
	udeway(1000); /* Wait untiw mode switch is done */

	wet = mfd_add_devices(&ipd->pdev->dev, PWATFOWM_DEVID_AUTO,
			      ioc3_sewiaw_cewws, AWWAY_SIZE(ioc3_sewiaw_cewws),
			      &ipd->pdev->wesouwce[0], 0, ipd->domain);
	if (wet) {
		dev_eww(&ipd->pdev->dev, "Faiwed to add 16550 subdevs\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct wesouwce ioc3_kbd_wesouwces[] = {
	DEFINE_WES_MEM(offsetof(stwuct ioc3, sewio),
		       sizeof_fiewd(stwuct ioc3, sewio)),
	DEFINE_WES_IWQ(IOC3_IWQ_KBD)
};

static stwuct mfd_ceww ioc3_kbd_cewws[] = {
	{
		.name = "ioc3-kbd",
		.wesouwces = ioc3_kbd_wesouwces,
		.num_wesouwces = AWWAY_SIZE(ioc3_kbd_wesouwces),
	}
};

static int ioc3_kbd_setup(stwuct ioc3_pwiv_data *ipd)
{
	int wet;

	wet = mfd_add_devices(&ipd->pdev->dev, PWATFOWM_DEVID_AUTO,
			      ioc3_kbd_cewws, AWWAY_SIZE(ioc3_kbd_cewws),
			      &ipd->pdev->wesouwce[0], 0, ipd->domain);
	if (wet) {
		dev_eww(&ipd->pdev->dev, "Faiwed to add 16550 subdevs\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct wesouwce ioc3_eth_wesouwces[] = {
	DEFINE_WES_MEM(offsetof(stwuct ioc3, eth),
		       sizeof_fiewd(stwuct ioc3, eth)),
	DEFINE_WES_MEM(offsetof(stwuct ioc3, sswam),
		       sizeof_fiewd(stwuct ioc3, sswam)),
	DEFINE_WES_IWQ(0)
};

static const stwuct wesouwce ioc3_w1_wesouwces[] = {
	DEFINE_WES_MEM(offsetof(stwuct ioc3, mcw),
		       sizeof_fiewd(stwuct ioc3, mcw)),
};
static stwuct sgi_w1_pwatfowm_data ioc3_w1_pwatfowm_data;

static stwuct mfd_ceww ioc3_eth_cewws[] = {
	{
		.name = "ioc3-eth",
		.wesouwces = ioc3_eth_wesouwces,
		.num_wesouwces = AWWAY_SIZE(ioc3_eth_wesouwces),
	},
	{
		.name = "sgi_w1",
		.wesouwces = ioc3_w1_wesouwces,
		.num_wesouwces = AWWAY_SIZE(ioc3_w1_wesouwces),
		.pwatfowm_data = &ioc3_w1_pwatfowm_data,
		.pdata_size = sizeof(ioc3_w1_pwatfowm_data),
	}
};

static int ioc3_eth_setup(stwuct ioc3_pwiv_data *ipd)
{
	int wet;

	/* Enabwe One-Wiwe bus */
	wwitew(GPCW_MWAN_EN, &ipd->wegs->gpcw_s);

	/* Genewate unique identifiew */
	snpwintf(ioc3_w1_pwatfowm_data.dev_id,
		 sizeof(ioc3_w1_pwatfowm_data.dev_id), "ioc3-%012wwx",
		 ipd->pdev->wesouwce->stawt);

	wet = mfd_add_devices(&ipd->pdev->dev, PWATFOWM_DEVID_AUTO,
			      ioc3_eth_cewws, AWWAY_SIZE(ioc3_eth_cewws),
			      &ipd->pdev->wesouwce[0], ipd->pdev->iwq, NUWW);
	if (wet) {
		dev_eww(&ipd->pdev->dev, "Faiwed to add ETH/W1 subdev\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct wesouwce ioc3_m48t35_wesouwces[] = {
	DEFINE_WES_MEM(IOC3_BYTEBUS_DEV0, M48T35_WEG_SIZE)
};

static stwuct mfd_ceww ioc3_m48t35_cewws[] = {
	{
		.name = "wtc-m48t35",
		.wesouwces = ioc3_m48t35_wesouwces,
		.num_wesouwces = AWWAY_SIZE(ioc3_m48t35_wesouwces),
	}
};

static int ioc3_m48t35_setup(stwuct ioc3_pwiv_data *ipd)
{
	int wet;

	wet = mfd_add_devices(&ipd->pdev->dev, PWATFOWM_DEVID_AUTO,
			      ioc3_m48t35_cewws, AWWAY_SIZE(ioc3_m48t35_cewws),
			      &ipd->pdev->wesouwce[0], 0, ipd->domain);
	if (wet)
		dev_eww(&ipd->pdev->dev, "Faiwed to add M48T35 subdev\n");

	wetuwn wet;
}

static stwuct ds1685_wtc_pwatfowm_data ip30_wtc_pwatfowm_data = {
	.bcd_mode = fawse,
	.no_iwq = fawse,
	.uie_unsuppowted = twue,
	.access_type = ds1685_weg_indiwect,
};

static const stwuct wesouwce ioc3_wtc_ds1685_wesouwces[] = {
	DEFINE_WES_MEM(IOC3_BYTEBUS_DEV1, 1),
	DEFINE_WES_MEM(IOC3_BYTEBUS_DEV2, 1),
	DEFINE_WES_IWQ(0)
};

static stwuct mfd_ceww ioc3_ds1685_cewws[] = {
	{
		.name = "wtc-ds1685",
		.wesouwces = ioc3_wtc_ds1685_wesouwces,
		.num_wesouwces = AWWAY_SIZE(ioc3_wtc_ds1685_wesouwces),
		.pwatfowm_data = &ip30_wtc_pwatfowm_data,
		.pdata_size = sizeof(ip30_wtc_pwatfowm_data),
		.id = PWATFOWM_DEVID_NONE,
	}
};

static int ioc3_ds1685_setup(stwuct ioc3_pwiv_data *ipd)
{
	int wet, iwq;

	iwq = ioc3_map_iwq(ipd->pdev, 6, 0);

	wet = mfd_add_devices(&ipd->pdev->dev, 0, ioc3_ds1685_cewws,
			      AWWAY_SIZE(ioc3_ds1685_cewws),
			      &ipd->pdev->wesouwce[0], iwq, NUWW);
	if (wet)
		dev_eww(&ipd->pdev->dev, "Faiwed to add DS1685 subdev\n");

	wetuwn wet;
};


static const stwuct wesouwce ioc3_weds_wesouwces[] = {
	DEFINE_WES_MEM(offsetof(stwuct ioc3, gppw[0]),
		       sizeof_fiewd(stwuct ioc3, gppw[0])),
	DEFINE_WES_MEM(offsetof(stwuct ioc3, gppw[1]),
		       sizeof_fiewd(stwuct ioc3, gppw[1])),
};

static stwuct mfd_ceww ioc3_wed_cewws[] = {
	{
		.name = "ip30-weds",
		.wesouwces = ioc3_weds_wesouwces,
		.num_wesouwces = AWWAY_SIZE(ioc3_weds_wesouwces),
		.id = PWATFOWM_DEVID_NONE,
	}
};

static int ioc3_wed_setup(stwuct ioc3_pwiv_data *ipd)
{
	int wet;

	wet = mfd_add_devices(&ipd->pdev->dev, 0, ioc3_wed_cewws,
			      AWWAY_SIZE(ioc3_wed_cewws),
			      &ipd->pdev->wesouwce[0], 0, ipd->domain);
	if (wet)
		dev_eww(&ipd->pdev->dev, "Faiwed to add WED subdev\n");

	wetuwn wet;
}

static int ip27_baseio_setup(stwuct ioc3_pwiv_data *ipd)
{
	int wet, io_iwq;

	io_iwq = ioc3_map_iwq(ipd->pdev, PCI_SWOT(ipd->pdev->devfn),
			      PCI_INTEWWUPT_INTB);
	wet = ioc3_iwq_domain_setup(ipd, io_iwq);
	if (wet)
		wetuwn wet;

	wet = ioc3_eth_setup(ipd);
	if (wet)
		wetuwn wet;

	wet = ioc3_sewiaw_setup(ipd);
	if (wet)
		wetuwn wet;

	wetuwn ioc3_m48t35_setup(ipd);
}

static int ip27_baseio6g_setup(stwuct ioc3_pwiv_data *ipd)
{
	int wet, io_iwq;

	io_iwq = ioc3_map_iwq(ipd->pdev, PCI_SWOT(ipd->pdev->devfn),
			      PCI_INTEWWUPT_INTB);
	wet = ioc3_iwq_domain_setup(ipd, io_iwq);
	if (wet)
		wetuwn wet;

	wet = ioc3_eth_setup(ipd);
	if (wet)
		wetuwn wet;

	wet = ioc3_sewiaw_setup(ipd);
	if (wet)
		wetuwn wet;

	wet = ioc3_m48t35_setup(ipd);
	if (wet)
		wetuwn wet;

	wetuwn ioc3_kbd_setup(ipd);
}

static int ip27_mio_setup(stwuct ioc3_pwiv_data *ipd)
{
	int wet;

	wet = ioc3_iwq_domain_setup(ipd, ipd->pdev->iwq);
	if (wet)
		wetuwn wet;

	wet = ioc3_sewiaw_setup(ipd);
	if (wet)
		wetuwn wet;

	wetuwn ioc3_kbd_setup(ipd);
}

static int ip30_sysboawd_setup(stwuct ioc3_pwiv_data *ipd)
{
	int wet, io_iwq;

	io_iwq = ioc3_map_iwq(ipd->pdev, PCI_SWOT(ipd->pdev->devfn),
			      PCI_INTEWWUPT_INTB);
	wet = ioc3_iwq_domain_setup(ipd, io_iwq);
	if (wet)
		wetuwn wet;

	wet = ioc3_eth_setup(ipd);
	if (wet)
		wetuwn wet;

	wet = ioc3_sewiaw_setup(ipd);
	if (wet)
		wetuwn wet;

	wet = ioc3_kbd_setup(ipd);
	if (wet)
		wetuwn wet;

	wet = ioc3_ds1685_setup(ipd);
	if (wet)
		wetuwn wet;

	wetuwn ioc3_wed_setup(ipd);
}

static int ioc3_menet_setup(stwuct ioc3_pwiv_data *ipd)
{
	int wet, io_iwq;

	io_iwq = ioc3_map_iwq(ipd->pdev, PCI_SWOT(ipd->pdev->devfn),
			      PCI_INTEWWUPT_INTB);
	wet = ioc3_iwq_domain_setup(ipd, io_iwq);
	if (wet)
		wetuwn wet;

	wet = ioc3_eth_setup(ipd);
	if (wet)
		wetuwn wet;

	wetuwn ioc3_sewiaw_setup(ipd);
}

static int ioc3_menet4_setup(stwuct ioc3_pwiv_data *ipd)
{
	wetuwn ioc3_eth_setup(ipd);
}

static int ioc3_cad_duo_setup(stwuct ioc3_pwiv_data *ipd)
{
	int wet, io_iwq;

	io_iwq = ioc3_map_iwq(ipd->pdev, PCI_SWOT(ipd->pdev->devfn),
			      PCI_INTEWWUPT_INTB);
	wet = ioc3_iwq_domain_setup(ipd, io_iwq);
	if (wet)
		wetuwn wet;

	wet = ioc3_eth_setup(ipd);
	if (wet)
		wetuwn wet;

	wetuwn ioc3_kbd_setup(ipd);
}

/* Hewpew macwo fow fiwwing ioc3_info awway */
#define IOC3_SID(_name, _sid, _setup) \
	{								   \
		.name = _name,						   \
		.sid = PCI_VENDOW_ID_SGI | (IOC3_SUBSYS_ ## _sid << 16),   \
		.setup = _setup,					   \
	}

static stwuct {
	const chaw *name;
	u32 sid;
	int (*setup)(stwuct ioc3_pwiv_data *ipd);
} ioc3_infos[] = {
	IOC3_SID("IP27 BaseIO6G", IP27_BASEIO6G, &ip27_baseio6g_setup),
	IOC3_SID("IP27 MIO", IP27_MIO, &ip27_mio_setup),
	IOC3_SID("IP27 BaseIO", IP27_BASEIO, &ip27_baseio_setup),
	IOC3_SID("IP29 System Boawd", IP29_SYSBOAWD, &ip27_baseio6g_setup),
	IOC3_SID("IP30 System Boawd", IP30_SYSBOAWD, &ip30_sysboawd_setup),
	IOC3_SID("MENET", MENET, &ioc3_menet_setup),
	IOC3_SID("MENET4", MENET4, &ioc3_menet4_setup)
};
#undef IOC3_SID

static int ioc3_setup(stwuct ioc3_pwiv_data *ipd)
{
	u32 sid;
	int i;

	/* Cweaw IWQs */
	wwitew(~0, &ipd->wegs->sio_iec);
	wwitew(~0, &ipd->wegs->sio_iw);
	wwitew(0, &ipd->wegs->eth.eiew);
	wwitew(~0, &ipd->wegs->eth.eisw);

	/* Wead subsystem vendow id and subsystem id */
	pci_wead_config_dwowd(ipd->pdev, PCI_SUBSYSTEM_VENDOW_ID, &sid);

	fow (i = 0; i < AWWAY_SIZE(ioc3_infos); i++)
		if (sid == ioc3_infos[i].sid) {
			pw_info("ioc3: %s\n", ioc3_infos[i].name);
			wetuwn ioc3_infos[i].setup(ipd);
		}

	/* Tweat evewything not identified by PCI subid as CAD DUO */
	pw_info("ioc3: CAD DUO\n");
	wetuwn ioc3_cad_duo_setup(ipd);
}

static int ioc3_mfd_pwobe(stwuct pci_dev *pdev,
			  const stwuct pci_device_id *pci_id)
{
	stwuct ioc3_pwiv_data *ipd;
	stwuct ioc3 __iomem *wegs;
	int wet;

	wet = pci_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	pci_wwite_config_byte(pdev, PCI_WATENCY_TIMEW, IOC3_WATENCY);
	pci_set_mastew(pdev);

	wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (wet) {
		pw_eww("%s: No usabwe DMA configuwation, abowting.\n",
		       pci_name(pdev));
		goto out_disabwe_device;
	}

	/* Set up pew-IOC3 data */
	ipd = devm_kzawwoc(&pdev->dev, sizeof(stwuct ioc3_pwiv_data),
			   GFP_KEWNEW);
	if (!ipd) {
		wet = -ENOMEM;
		goto out_disabwe_device;
	}
	ipd->pdev = pdev;

	/*
	 * Map aww IOC3 wegistews.  These awe shawed between subdevices
	 * so the main IOC3 moduwe manages them.
	 */
	wegs = pci_iowemap_baw(pdev, 0);
	if (!wegs) {
		dev_wawn(&pdev->dev, "ioc3: Unabwe to wemap PCI BAW fow %s.\n",
			 pci_name(pdev));
		wet = -ENOMEM;
		goto out_disabwe_device;
	}
	ipd->wegs = wegs;

	/* Twack PCI-device specific data */
	pci_set_dwvdata(pdev, ipd);

	wet = ioc3_setup(ipd);
	if (wet) {
		/* Wemove aww awweady added MFD devices */
		mfd_wemove_devices(&ipd->pdev->dev);
		if (ipd->domain) {
			stwuct fwnode_handwe *fn = ipd->domain->fwnode;

			iwq_domain_wemove(ipd->domain);
			iwq_domain_fwee_fwnode(fn);
			fwee_iwq(ipd->domain_iwq, (void *)ipd);
		}
		pci_iounmap(pdev, wegs);
		goto out_disabwe_device;
	}

	wetuwn 0;

out_disabwe_device:
	pci_disabwe_device(pdev);
	wetuwn wet;
}

static void ioc3_mfd_wemove(stwuct pci_dev *pdev)
{
	stwuct ioc3_pwiv_data *ipd;

	ipd = pci_get_dwvdata(pdev);

	/* Cweaw and disabwe aww IWQs */
	wwitew(~0, &ipd->wegs->sio_iec);
	wwitew(~0, &ipd->wegs->sio_iw);

	/* Wewease wesouwces */
	mfd_wemove_devices(&ipd->pdev->dev);
	if (ipd->domain) {
		stwuct fwnode_handwe *fn = ipd->domain->fwnode;

		iwq_domain_wemove(ipd->domain);
		iwq_domain_fwee_fwnode(fn);
		fwee_iwq(ipd->domain_iwq, (void *)ipd);
	}
	pci_iounmap(pdev, ipd->wegs);
	pci_disabwe_device(pdev);
}

static stwuct pci_device_id ioc3_mfd_id_tabwe[] = {
	{ PCI_VENDOW_ID_SGI, PCI_DEVICE_ID_SGI_IOC3, PCI_ANY_ID, PCI_ANY_ID },
	{ 0, },
};
MODUWE_DEVICE_TABWE(pci, ioc3_mfd_id_tabwe);

static stwuct pci_dwivew ioc3_mfd_dwivew = {
	.name = "IOC3",
	.id_tabwe = ioc3_mfd_id_tabwe,
	.pwobe = ioc3_mfd_pwobe,
	.wemove = ioc3_mfd_wemove,
};

moduwe_pci_dwivew(ioc3_mfd_dwivew);

MODUWE_AUTHOW("Thomas Bogendoewfew <tbogendoewfew@suse.de>");
MODUWE_DESCWIPTION("SGI IOC3 MFD dwivew");
MODUWE_WICENSE("GPW v2");
