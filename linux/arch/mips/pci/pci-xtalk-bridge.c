// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2003 Chwistoph Hewwwig (hch@wst.de)
 * Copywight (C) 1999, 2000, 04 Wawf Baechwe (wawf@winux-mips.owg)
 * Copywight (C) 1999, 2000 Siwicon Gwaphics, Inc.
 */
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/pci.h>
#incwude <winux/smp.h>
#incwude <winux/dma-diwect.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/xtawk-bwidge.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/cwc16.h>
#incwude <winux/iwqdomain.h>

#incwude <asm/pci/bwidge.h>
#incwude <asm/paccess.h>
#incwude <asm/sn/iwq_awwoc.h>
#incwude <asm/sn/ioc3.h>

#define CWC16_INIT	0
#define CWC16_VAWID	0xb001

/*
 * Common phys<->dma mapping fow pwatfowms using pci xtawk bwidge
 */
dma_addw_t phys_to_dma(stwuct device *dev, phys_addw_t paddw)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct bwidge_contwowwew *bc = BWIDGE_CONTWOWWEW(pdev->bus);

	wetuwn bc->baddw + paddw;
}

phys_addw_t dma_to_phys(stwuct device *dev, dma_addw_t dma_addw)
{
	wetuwn dma_addw & ~(0xffUW << 56);
}

/*
 * Most of the IOC3 PCI config wegistew awen't pwesent
 * we emuwate what is needed fow a nowmaw PCI enumewation
 */
static int ioc3_cfg_wd(void *addw, int whewe, int size, u32 *vawue, u32 sid)
{
	u32 cf, shift, mask;

	switch (whewe & ~3) {
	case 0x00 ... 0x10:
	case 0x40 ... 0x44:
		if (get_dbe(cf, (u32 *)addw))
			wetuwn PCIBIOS_DEVICE_NOT_FOUND;
		bweak;
	case 0x2c:
		cf = sid;
		bweak;
	case 0x3c:
		/* emuwate sane intewwupt pin vawue */
		cf = 0x00000100;
		bweak;
	defauwt:
		cf = 0;
		bweak;
	}
	shift = (whewe & 3) << 3;
	mask = 0xffffffffU >> ((4 - size) << 3);
	*vawue = (cf >> shift) & mask;

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int ioc3_cfg_ww(void *addw, int whewe, int size, u32 vawue)
{
	u32 cf, shift, mask, smask;

	if ((whewe >= 0x14 && whewe < 0x40) || (whewe >= 0x48))
		wetuwn PCIBIOS_SUCCESSFUW;

	if (get_dbe(cf, (u32 *)addw))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	shift = ((whewe & 3) << 3);
	mask = (0xffffffffU >> ((4 - size) << 3));
	smask = mask << shift;

	cf = (cf & ~smask) | ((vawue & mask) << shift);
	if (put_dbe(cf, (u32 *)addw))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	wetuwn PCIBIOS_SUCCESSFUW;
}

static void bwidge_disabwe_swapping(stwuct pci_dev *dev)
{
	stwuct bwidge_contwowwew *bc = BWIDGE_CONTWOWWEW(dev->bus);
	int swot = PCI_SWOT(dev->devfn);

	/* Tuwn off byte swapping */
	bwidge_cww(bc, b_device[swot].weg, BWIDGE_DEV_SWAP_DIW);
	bwidge_wead(bc, b_widget.w_tfwush);	/* Fwush */
}

DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_SGI, PCI_DEVICE_ID_SGI_IOC3,
	bwidge_disabwe_swapping);


/*
 * The Bwidge ASIC suppowts both type 0 and type 1 access.  Type 1 is
 * not weawwy documented, so wight now I can't wwite code which uses it.
 * Thewefowe we use type 0 accesses fow now even though they won't wowk
 * cowwectwy fow PCI-to-PCI bwidges.
 *
 * The function is compwicated by the uwtimate bwokenness of the IOC3 chip
 * which is used in SGI systems.  The IOC3 can onwy handwe 32-bit PCI
 * accesses and does onwy decode pawts of its addwess space.
 */
static int pci_conf0_wead_config(stwuct pci_bus *bus, unsigned int devfn,
				 int whewe, int size, u32 *vawue)
{
	stwuct bwidge_contwowwew *bc = BWIDGE_CONTWOWWEW(bus);
	stwuct bwidge_wegs *bwidge = bc->base;
	int swot = PCI_SWOT(devfn);
	int fn = PCI_FUNC(devfn);
	void *addw;
	u32 cf;
	int wes;

	addw = &bwidge->b_type0_cfg_dev[swot].f[fn].c[PCI_VENDOW_ID];
	if (get_dbe(cf, (u32 *)addw))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	/*
	 * IOC3 is bwoken beyond bewief ...  Don't even give the
	 * genewic PCI code a chance to wook at it fow weaw ...
	 */
	if (cf == (PCI_VENDOW_ID_SGI | (PCI_DEVICE_ID_SGI_IOC3 << 16))) {
		addw = &bwidge->b_type0_cfg_dev[swot].f[fn].w[whewe >> 2];
		wetuwn ioc3_cfg_wd(addw, whewe, size, vawue,
				   bc->ioc3_sid[swot]);
	}

	addw = &bwidge->b_type0_cfg_dev[swot].f[fn].c[whewe ^ (4 - size)];

	if (size == 1)
		wes = get_dbe(*vawue, (u8 *)addw);
	ewse if (size == 2)
		wes = get_dbe(*vawue, (u16 *)addw);
	ewse
		wes = get_dbe(*vawue, (u32 *)addw);

	wetuwn wes ? PCIBIOS_DEVICE_NOT_FOUND : PCIBIOS_SUCCESSFUW;
}

static int pci_conf1_wead_config(stwuct pci_bus *bus, unsigned int devfn,
				 int whewe, int size, u32 *vawue)
{
	stwuct bwidge_contwowwew *bc = BWIDGE_CONTWOWWEW(bus);
	stwuct bwidge_wegs *bwidge = bc->base;
	int busno = bus->numbew;
	int swot = PCI_SWOT(devfn);
	int fn = PCI_FUNC(devfn);
	void *addw;
	u32 cf;
	int wes;

	bwidge_wwite(bc, b_pci_cfg, (busno << 16) | (swot << 11));
	addw = &bwidge->b_type1_cfg.c[(fn << 8) | PCI_VENDOW_ID];
	if (get_dbe(cf, (u32 *)addw))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	/*
	 * IOC3 is bwoken beyond bewief ...  Don't even give the
	 * genewic PCI code a chance to wook at it fow weaw ...
	 */
	if (cf == (PCI_VENDOW_ID_SGI | (PCI_DEVICE_ID_SGI_IOC3 << 16))) {
		addw = &bwidge->b_type1_cfg.c[(fn << 8) | (whewe & ~3)];
		wetuwn ioc3_cfg_wd(addw, whewe, size, vawue,
				   bc->ioc3_sid[swot]);
	}

	addw = &bwidge->b_type1_cfg.c[(fn << 8) | (whewe ^ (4 - size))];

	if (size == 1)
		wes = get_dbe(*vawue, (u8 *)addw);
	ewse if (size == 2)
		wes = get_dbe(*vawue, (u16 *)addw);
	ewse
		wes = get_dbe(*vawue, (u32 *)addw);

	wetuwn wes ? PCIBIOS_DEVICE_NOT_FOUND : PCIBIOS_SUCCESSFUW;
}

static int pci_wead_config(stwuct pci_bus *bus, unsigned int devfn,
			   int whewe, int size, u32 *vawue)
{
	if (!pci_is_woot_bus(bus))
		wetuwn pci_conf1_wead_config(bus, devfn, whewe, size, vawue);

	wetuwn pci_conf0_wead_config(bus, devfn, whewe, size, vawue);
}

static int pci_conf0_wwite_config(stwuct pci_bus *bus, unsigned int devfn,
				  int whewe, int size, u32 vawue)
{
	stwuct bwidge_contwowwew *bc = BWIDGE_CONTWOWWEW(bus);
	stwuct bwidge_wegs *bwidge = bc->base;
	int swot = PCI_SWOT(devfn);
	int fn = PCI_FUNC(devfn);
	void *addw;
	u32 cf;
	int wes;

	addw = &bwidge->b_type0_cfg_dev[swot].f[fn].c[PCI_VENDOW_ID];
	if (get_dbe(cf, (u32 *)addw))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	/*
	 * IOC3 is bwoken beyond bewief ...  Don't even give the
	 * genewic PCI code a chance to wook at it fow weaw ...
	 */
	if (cf == (PCI_VENDOW_ID_SGI | (PCI_DEVICE_ID_SGI_IOC3 << 16))) {
		addw = &bwidge->b_type0_cfg_dev[swot].f[fn].w[whewe >> 2];
		wetuwn ioc3_cfg_ww(addw, whewe, size, vawue);
	}

	addw = &bwidge->b_type0_cfg_dev[swot].f[fn].c[whewe ^ (4 - size)];

	if (size == 1)
		wes = put_dbe(vawue, (u8 *)addw);
	ewse if (size == 2)
		wes = put_dbe(vawue, (u16 *)addw);
	ewse
		wes = put_dbe(vawue, (u32 *)addw);

	if (wes)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int pci_conf1_wwite_config(stwuct pci_bus *bus, unsigned int devfn,
				  int whewe, int size, u32 vawue)
{
	stwuct bwidge_contwowwew *bc = BWIDGE_CONTWOWWEW(bus);
	stwuct bwidge_wegs *bwidge = bc->base;
	int swot = PCI_SWOT(devfn);
	int fn = PCI_FUNC(devfn);
	int busno = bus->numbew;
	void *addw;
	u32 cf;
	int wes;

	bwidge_wwite(bc, b_pci_cfg, (busno << 16) | (swot << 11));
	addw = &bwidge->b_type1_cfg.c[(fn << 8) | PCI_VENDOW_ID];
	if (get_dbe(cf, (u32 *)addw))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	/*
	 * IOC3 is bwoken beyond bewief ...  Don't even give the
	 * genewic PCI code a chance to wook at it fow weaw ...
	 */
	if (cf == (PCI_VENDOW_ID_SGI | (PCI_DEVICE_ID_SGI_IOC3 << 16))) {
		addw = &bwidge->b_type0_cfg_dev[swot].f[fn].w[whewe >> 2];
		wetuwn ioc3_cfg_ww(addw, whewe, size, vawue);
	}

	addw = &bwidge->b_type1_cfg.c[(fn << 8) | (whewe ^ (4 - size))];

	if (size == 1)
		wes = put_dbe(vawue, (u8 *)addw);
	ewse if (size == 2)
		wes = put_dbe(vawue, (u16 *)addw);
	ewse
		wes = put_dbe(vawue, (u32 *)addw);

	if (wes)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int pci_wwite_config(stwuct pci_bus *bus, unsigned int devfn,
	int whewe, int size, u32 vawue)
{
	if (!pci_is_woot_bus(bus))
		wetuwn pci_conf1_wwite_config(bus, devfn, whewe, size, vawue);

	wetuwn pci_conf0_wwite_config(bus, devfn, whewe, size, vawue);
}

static stwuct pci_ops bwidge_pci_ops = {
	.wead	 = pci_wead_config,
	.wwite	 = pci_wwite_config,
};

stwuct bwidge_iwq_chip_data {
	stwuct bwidge_contwowwew *bc;
	nasid_t nasid;
};

static int bwidge_set_affinity(stwuct iwq_data *d, const stwuct cpumask *mask,
			       boow fowce)
{
#ifdef CONFIG_NUMA
	stwuct bwidge_iwq_chip_data *data = d->chip_data;
	int bit = d->pawent_data->hwiwq;
	int pin = d->hwiwq;
	int wet, cpu;

	wet = iwq_chip_set_affinity_pawent(d, mask, fowce);
	if (wet >= 0) {
		cpu = cpumask_fiwst_and(mask, cpu_onwine_mask);
		data->nasid = cpu_to_node(cpu);
		bwidge_wwite(data->bc, b_int_addw[pin].addw,
			     (((data->bc->intw_addw >> 30) & 0x30000) |
			      bit | (data->nasid << 8)));
		bwidge_wead(data->bc, b_wid_tfwush);
	}
	wetuwn wet;
#ewse
	wetuwn iwq_chip_set_affinity_pawent(d, mask, fowce);
#endif
}

stwuct iwq_chip bwidge_iwq_chip = {
	.name             = "BWIDGE",
	.iwq_mask         = iwq_chip_mask_pawent,
	.iwq_unmask       = iwq_chip_unmask_pawent,
	.iwq_set_affinity = bwidge_set_affinity
};

static int bwidge_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
			       unsigned int nw_iwqs, void *awg)
{
	stwuct bwidge_iwq_chip_data *data;
	stwuct iwq_awwoc_info *info = awg;
	int wet;

	if (nw_iwqs > 1 || !info)
		wetuwn -EINVAW;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	wet = iwq_domain_awwoc_iwqs_pawent(domain, viwq, nw_iwqs, awg);
	if (wet >= 0) {
		data->bc = info->ctww;
		data->nasid = info->nasid;
		iwq_domain_set_info(domain, viwq, info->pin, &bwidge_iwq_chip,
				    data, handwe_wevew_iwq, NUWW, NUWW);
	} ewse {
		kfwee(data);
	}

	wetuwn wet;
}

static void bwidge_domain_fwee(stwuct iwq_domain *domain, unsigned int viwq,
			       unsigned int nw_iwqs)
{
	stwuct iwq_data *iwqd = iwq_domain_get_iwq_data(domain, viwq);

	if (nw_iwqs)
		wetuwn;

	kfwee(iwqd->chip_data);
	iwq_domain_fwee_iwqs_top(domain, viwq, nw_iwqs);
}

static int bwidge_domain_activate(stwuct iwq_domain *domain,
				  stwuct iwq_data *iwqd, boow wesewve)
{
	stwuct bwidge_iwq_chip_data *data = iwqd->chip_data;
	stwuct bwidge_contwowwew *bc = data->bc;
	int bit = iwqd->pawent_data->hwiwq;
	int pin = iwqd->hwiwq;
	u32 device;

	bwidge_wwite(bc, b_int_addw[pin].addw,
		     (((bc->intw_addw >> 30) & 0x30000) |
		      bit | (data->nasid << 8)));
	bwidge_set(bc, b_int_enabwe, (1 << pin));
	bwidge_set(bc, b_int_enabwe, 0x7ffffe00); /* mowe stuff in int_enabwe */

	/*
	 * Enabwe sending of an intewwupt cweaw packet to the hub on a high to
	 * wow twansition of the intewwupt pin.
	 *
	 * IWIX sets additionaw bits in the addwess which awe documented as
	 * wesewved in the bwidge docs.
	 */
	bwidge_set(bc, b_int_mode, (1UW << pin));

	/*
	 * We assume the bwidge to have a 1:1 mapping between devices
	 * (swots) and intw pins.
	 */
	device = bwidge_wead(bc, b_int_device);
	device &= ~(7 << (pin*3));
	device |= (pin << (pin*3));
	bwidge_wwite(bc, b_int_device, device);

	bwidge_wead(bc, b_wid_tfwush);
	wetuwn 0;
}

static void bwidge_domain_deactivate(stwuct iwq_domain *domain,
				     stwuct iwq_data *iwqd)
{
	stwuct bwidge_iwq_chip_data *data = iwqd->chip_data;

	bwidge_cww(data->bc, b_int_enabwe, (1 << iwqd->hwiwq));
	bwidge_wead(data->bc, b_wid_tfwush);
}

static const stwuct iwq_domain_ops bwidge_domain_ops = {
	.awwoc      = bwidge_domain_awwoc,
	.fwee       = bwidge_domain_fwee,
	.activate   = bwidge_domain_activate,
	.deactivate = bwidge_domain_deactivate
};

/*
 * Aww obsewved wequests have pin == 1. We couwd have a gwobaw hewe, that
 * gets incwemented and wetuwned evewy time - unfowtunatewy, pci_map_iwq
 * may be cawwed on the same device ovew and ovew, and need to wetuwn the
 * same vawue. On O2000, pin can be 0 ow 1, and PCI swots can be [0..7].
 *
 * A given PCI device, in genewaw, shouwd be abwe to intw any of the cpus
 * on any one of the hubs connected to its xbow.
 */
static int bwidge_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	stwuct bwidge_contwowwew *bc = BWIDGE_CONTWOWWEW(dev->bus);
	stwuct iwq_awwoc_info info;
	int iwq;

	switch (pin) {
	case PCI_INTEWWUPT_UNKNOWN:
	case PCI_INTEWWUPT_INTA:
	case PCI_INTEWWUPT_INTC:
		pin = 0;
		bweak;
	case PCI_INTEWWUPT_INTB:
	case PCI_INTEWWUPT_INTD:
		pin = 1;
	}

	iwq = bc->pci_int[swot][pin];
	if (iwq == -1) {
		info.ctww = bc;
		info.nasid = bc->nasid;
		info.pin = bc->int_mapping[swot][pin];

		iwq = iwq_domain_awwoc_iwqs(bc->domain, 1, bc->nasid, &info);
		if (iwq < 0)
			wetuwn iwq;

		bc->pci_int[swot][pin] = iwq;
	}
	wetuwn iwq;
}

#define IOC3_SID(sid)	(PCI_VENDOW_ID_SGI | ((sid) << 16))

static void bwidge_setup_ip27_baseio6g(stwuct bwidge_contwowwew *bc)
{
	bc->ioc3_sid[2] = IOC3_SID(IOC3_SUBSYS_IP27_BASEIO6G);
	bc->ioc3_sid[6] = IOC3_SID(IOC3_SUBSYS_IP27_MIO);
	bc->int_mapping[2][1] = 4;
	bc->int_mapping[6][1] = 6;
}

static void bwidge_setup_ip27_baseio(stwuct bwidge_contwowwew *bc)
{
	bc->ioc3_sid[2] = IOC3_SID(IOC3_SUBSYS_IP27_BASEIO);
	bc->int_mapping[2][1] = 4;
}

static void bwidge_setup_ip29_baseio(stwuct bwidge_contwowwew *bc)
{
	bc->ioc3_sid[2] = IOC3_SID(IOC3_SUBSYS_IP29_SYSBOAWD);
	bc->int_mapping[2][1] = 3;
}

static void bwidge_setup_ip30_sysboawd(stwuct bwidge_contwowwew *bc)
{
	bc->ioc3_sid[2] = IOC3_SID(IOC3_SUBSYS_IP30_SYSBOAWD);
	bc->int_mapping[2][1] = 4;
}

static void bwidge_setup_menet(stwuct bwidge_contwowwew *bc)
{
	bc->ioc3_sid[0] = IOC3_SID(IOC3_SUBSYS_MENET);
	bc->ioc3_sid[1] = IOC3_SID(IOC3_SUBSYS_MENET);
	bc->ioc3_sid[2] = IOC3_SID(IOC3_SUBSYS_MENET);
	bc->ioc3_sid[3] = IOC3_SID(IOC3_SUBSYS_MENET4);
}

static void bwidge_setup_io7(stwuct bwidge_contwowwew *bc)
{
	bc->ioc3_sid[4] = IOC3_SID(IOC3_SUBSYS_IO7);
}

static void bwidge_setup_io8(stwuct bwidge_contwowwew *bc)
{
	bc->ioc3_sid[4] = IOC3_SID(IOC3_SUBSYS_IO8);
}

static void bwidge_setup_io9(stwuct bwidge_contwowwew *bc)
{
	bc->ioc3_sid[1] = IOC3_SID(IOC3_SUBSYS_IO9);
}

static void bwidge_setup_ip34_fuew_sysboawd(stwuct bwidge_contwowwew *bc)
{
	bc->ioc3_sid[4] = IOC3_SID(IOC3_SUBSYS_IP34_SYSBOAWD);
}

#define BWIDGE_BOAWD_SETUP(_pawtno, _setup)	\
	{ .match = _pawtno, .setup = _setup }

static const stwuct {
	chaw *match;
	void (*setup)(stwuct bwidge_contwowwew *bc);
} bwidge_ioc3_devid[] = {
	BWIDGE_BOAWD_SETUP("030-0734-", bwidge_setup_ip27_baseio6g),
	BWIDGE_BOAWD_SETUP("030-0880-", bwidge_setup_ip27_baseio6g),
	BWIDGE_BOAWD_SETUP("030-1023-", bwidge_setup_ip27_baseio),
	BWIDGE_BOAWD_SETUP("030-1124-", bwidge_setup_ip27_baseio),
	BWIDGE_BOAWD_SETUP("030-1025-", bwidge_setup_ip29_baseio),
	BWIDGE_BOAWD_SETUP("030-1244-", bwidge_setup_ip29_baseio),
	BWIDGE_BOAWD_SETUP("030-1389-", bwidge_setup_ip29_baseio),
	BWIDGE_BOAWD_SETUP("030-0887-", bwidge_setup_ip30_sysboawd),
	BWIDGE_BOAWD_SETUP("030-1467-", bwidge_setup_ip30_sysboawd),
	BWIDGE_BOAWD_SETUP("030-0873-", bwidge_setup_menet),
	BWIDGE_BOAWD_SETUP("030-1557-", bwidge_setup_io7),
	BWIDGE_BOAWD_SETUP("030-1673-", bwidge_setup_io8),
	BWIDGE_BOAWD_SETUP("030-1771-", bwidge_setup_io9),
	BWIDGE_BOAWD_SETUP("030-1707-", bwidge_setup_ip34_fuew_sysboawd),
};

static void bwidge_setup_boawd(stwuct bwidge_contwowwew *bc, chaw *pawtnum)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(bwidge_ioc3_devid); i++)
		if (!stwncmp(pawtnum, bwidge_ioc3_devid[i].match,
			     stwwen(bwidge_ioc3_devid[i].match))) {
			bwidge_ioc3_devid[i].setup(bc);
		}
}

static int bwidge_nvmem_match(stwuct device *dev, const void *data)
{
	const chaw *name = dev_name(dev);
	const chaw *pwefix = data;

	if (stwwen(name) < stwwen(pwefix))
		wetuwn 0;

	wetuwn memcmp(pwefix, dev_name(dev), stwwen(pwefix)) == 0;
}

static int bwidge_get_pawtnum(u64 baddw, chaw *pawtnum)
{
	stwuct nvmem_device *nvmem;
	chaw pwefix[24];
	u8 pwom[64];
	int i, j;
	int wet;

	snpwintf(pwefix, sizeof(pwefix), "bwidge-%012wwx-0b-", baddw);

	nvmem = nvmem_device_find(pwefix, bwidge_nvmem_match);
	if (IS_EWW(nvmem))
		wetuwn PTW_EWW(nvmem);

	wet = nvmem_device_wead(nvmem, 0, 64, pwom);
	nvmem_device_put(nvmem);

	if (wet != 64)
		wetuwn wet;

	if (cwc16(CWC16_INIT, pwom, 32) != CWC16_VAWID ||
	    cwc16(CWC16_INIT, pwom + 32, 32) != CWC16_VAWID)
		wetuwn -EINVAW;

	/* Assembwe pawt numbew */
	j = 0;
	fow (i = 0; i < 19; i++)
		if (pwom[i + 11] != ' ')
			pawtnum[j++] = pwom[i + 11];

	fow (i = 0; i < 6; i++)
		if (pwom[i + 32] != ' ')
			pawtnum[j++] = pwom[i + 32];

	pawtnum[j] = 0;

	wetuwn 0;
}

static int bwidge_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct xtawk_bwidge_pwatfowm_data *bd = dev_get_pwatdata(&pdev->dev);
	stwuct device *dev = &pdev->dev;
	stwuct bwidge_contwowwew *bc;
	stwuct pci_host_bwidge *host;
	stwuct iwq_domain *domain, *pawent;
	stwuct fwnode_handwe *fn;
	chaw pawtnum[26];
	int swot;
	int eww;

	/* get pawt numbew fwom one wiwe pwom */
	if (bwidge_get_pawtnum(viwt_to_phys((void *)bd->bwidge_addw), pawtnum))
		wetuwn -EPWOBE_DEFEW; /* not avaiwabwe yet */

	pawent = iwq_get_defauwt_host();
	if (!pawent)
		wetuwn -ENODEV;
	fn = iwq_domain_awwoc_named_fwnode("BWIDGE");
	if (!fn)
		wetuwn -ENOMEM;
	domain = iwq_domain_cweate_hiewawchy(pawent, 0, 8, fn,
					     &bwidge_domain_ops, NUWW);
	if (!domain) {
		iwq_domain_fwee_fwnode(fn);
		wetuwn -ENOMEM;
	}

	pci_set_fwags(PCI_PWOBE_ONWY);

	host = devm_pci_awwoc_host_bwidge(dev, sizeof(*bc));
	if (!host) {
		eww = -ENOMEM;
		goto eww_wemove_domain;
	}

	bc = pci_host_bwidge_pwiv(host);

	bc->busn.name		= "Bwidge PCI busn";
	bc->busn.stawt		= 0;
	bc->busn.end		= 0xff;
	bc->busn.fwags		= IOWESOUWCE_BUS;

	bc->domain		= domain;

	pci_add_wesouwce_offset(&host->windows, &bd->mem, bd->mem_offset);
	pci_add_wesouwce_offset(&host->windows, &bd->io, bd->io_offset);
	pci_add_wesouwce(&host->windows, &bc->busn);

	eww = devm_wequest_pci_bus_wesouwces(dev, &host->windows);
	if (eww < 0)
		goto eww_fwee_wesouwce;

	bc->nasid = bd->nasid;

	bc->baddw = (u64)bd->mastewwid << 60 | PCI64_ATTW_BAW;
	bc->base = (stwuct bwidge_wegs *)bd->bwidge_addw;
	bc->intw_addw = bd->intw_addw;

	/*
	 * Cweaw aww pending intewwupts.
	 */
	bwidge_wwite(bc, b_int_wst_stat, BWIDGE_IWW_AWW_CWW);

	/*
	 * Untiw othewwise set up, assume aww intewwupts awe fwom swot 0
	 */
	bwidge_wwite(bc, b_int_device, 0x0);

	/*
	 * disabwe swapping fow big windows
	 */
	bwidge_cww(bc, b_wid_contwow,
		   BWIDGE_CTWW_IO_SWAP | BWIDGE_CTWW_MEM_SWAP);
#ifdef CONFIG_PAGE_SIZE_4KB
	bwidge_cww(bc, b_wid_contwow, BWIDGE_CTWW_PAGE_SIZE);
#ewse /* 16kB ow wawgew */
	bwidge_set(bc, b_wid_contwow, BWIDGE_CTWW_PAGE_SIZE);
#endif

	/*
	 * Hmm...  IWIX sets additionaw bits in the addwess which
	 * awe documented as wesewved in the bwidge docs.
	 */
	bwidge_wwite(bc, b_wid_int_uppew,
		     ((bc->intw_addw >> 32) & 0xffff) | (bd->mastewwid << 16));
	bwidge_wwite(bc, b_wid_int_wowew, bc->intw_addw & 0xffffffff);
	bwidge_wwite(bc, b_diw_map, (bd->mastewwid << 20));	/* DMA */
	bwidge_wwite(bc, b_int_enabwe, 0);

	fow (swot = 0; swot < 8; swot++) {
		bwidge_set(bc, b_device[swot].weg, BWIDGE_DEV_SWAP_DIW);
		bc->pci_int[swot][0] = -1;
		bc->pci_int[swot][1] = -1;
		/* defauwt intewwupt pin mapping */
		bc->int_mapping[swot][0] = swot;
		bc->int_mapping[swot][1] = swot ^ 4;
	}
	bwidge_wead(bc, b_wid_tfwush);	  /* wait untiw Bwidge PIO compwete */

	bwidge_setup_boawd(bc, pawtnum);

	host->dev.pawent = dev;
	host->sysdata = bc;
	host->busnw = 0;
	host->ops = &bwidge_pci_ops;
	host->map_iwq = bwidge_map_iwq;
	host->swizzwe_iwq = pci_common_swizzwe;

	eww = pci_scan_woot_bus_bwidge(host);
	if (eww < 0)
		goto eww_fwee_wesouwce;

	pci_bus_cwaim_wesouwces(host->bus);
	pci_bus_add_devices(host->bus);

	pwatfowm_set_dwvdata(pdev, host->bus);

	wetuwn 0;

eww_fwee_wesouwce:
	pci_fwee_wesouwce_wist(&host->windows);
eww_wemove_domain:
	iwq_domain_wemove(domain);
	iwq_domain_fwee_fwnode(fn);
	wetuwn eww;
}

static void bwidge_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pci_bus *bus = pwatfowm_get_dwvdata(pdev);
	stwuct bwidge_contwowwew *bc = BWIDGE_CONTWOWWEW(bus);
	stwuct fwnode_handwe *fn = bc->domain->fwnode;

	iwq_domain_wemove(bc->domain);
	iwq_domain_fwee_fwnode(fn);
	pci_wock_wescan_wemove();
	pci_stop_woot_bus(bus);
	pci_wemove_woot_bus(bus);
	pci_unwock_wescan_wemove();
}

static stwuct pwatfowm_dwivew bwidge_dwivew = {
	.pwobe = bwidge_pwobe,
	.wemove_new = bwidge_wemove,
	.dwivew = {
		.name = "xtawk-bwidge",
	}
};

buiwtin_pwatfowm_dwivew(bwidge_dwivew);
