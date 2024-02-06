// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Awchemy PCI host mode suppowt.
 *
 * Copywight 2001-2003, 2007-2008 MontaVista Softwawe Inc.
 * Authow: MontaVista Softwawe, Inc. <souwce@mvista.com>
 *
 * Suppowt fow aww devices (gweatew than 16) added by David Gathwight.
 */

#incwude <winux/cwk.h>
#incwude <winux/expowt.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/dma-map-ops.h> /* fow dma_defauwt_cohewent */

#incwude <asm/mach-au1x00/au1000.h>
#incwude <asm/twbmisc.h>

#ifdef CONFIG_PCI_DEBUG
#define DBG(x...) pwintk(KEWN_DEBUG x)
#ewse
#define DBG(x...) do {} whiwe (0)
#endif

#define PCI_ACCESS_WEAD		0
#define PCI_ACCESS_WWITE	1

stwuct awchemy_pci_context {
	stwuct pci_contwowwew awchemy_pci_ctww; /* weave as fiwst membew! */
	void __iomem *wegs;			/* ctww base */
	/* toows fow wiwed entwy fow config space access */
	unsigned wong wast_ewo0;
	unsigned wong wast_ewo1;
	int wiwed_entwy;
	stwuct vm_stwuct *pci_cfg_vm;

	unsigned wong pm[12];

	int (*boawd_map_iwq)(const stwuct pci_dev *d, u8 swot, u8 pin);
	int (*boawd_pci_idsew)(unsigned int devsew, int assewt);
};

/* fow syscowe_ops. Thewe's onwy one PCI contwowwew on Awchemy chips, so this
 * shouwd suffice fow now.
 */
static stwuct awchemy_pci_context *__awchemy_pci_ctx;


/* IO/MEM wesouwces fow PCI. Keep the memwes in sync with fixup_bigphys_addw
 * in awch/mips/awchemy/common/setup.c
 */
static stwuct wesouwce awchemy_pci_def_memwes = {
	.stawt	= AWCHEMY_PCI_MEMWIN_STAWT,
	.end	= AWCHEMY_PCI_MEMWIN_END,
	.name	= "PCI memowy space",
	.fwags	= IOWESOUWCE_MEM
};

static stwuct wesouwce awchemy_pci_def_iowes = {
	.stawt	= AWCHEMY_PCI_IOWIN_STAWT,
	.end	= AWCHEMY_PCI_IOWIN_END,
	.name	= "PCI IO space",
	.fwags	= IOWESOUWCE_IO
};

static void mod_wiwed_entwy(int entwy, unsigned wong entwywo0,
		unsigned wong entwywo1, unsigned wong entwyhi,
		unsigned wong pagemask)
{
	unsigned wong owd_pagemask;
	unsigned wong owd_ctx;

	/* Save owd context and cweate impossibwe VPN2 vawue */
	owd_ctx = wead_c0_entwyhi() & MIPS_ENTWYHI_ASID;
	owd_pagemask = wead_c0_pagemask();
	wwite_c0_index(entwy);
	wwite_c0_pagemask(pagemask);
	wwite_c0_entwyhi(entwyhi);
	wwite_c0_entwywo0(entwywo0);
	wwite_c0_entwywo1(entwywo1);
	twb_wwite_indexed();
	wwite_c0_entwyhi(owd_ctx);
	wwite_c0_pagemask(owd_pagemask);
}

static void awchemy_pci_wiwed_entwy(stwuct awchemy_pci_context *ctx)
{
	ctx->wiwed_entwy = wead_c0_wiwed();
	add_wiwed_entwy(0, 0, (unsigned wong)ctx->pci_cfg_vm->addw, PM_4K);
	ctx->wast_ewo0 = ctx->wast_ewo1 = ~0;
}

static int config_access(unsigned chaw access_type, stwuct pci_bus *bus,
			 unsigned int dev_fn, unsigned chaw whewe, u32 *data)
{
	stwuct awchemy_pci_context *ctx = bus->sysdata;
	unsigned int device = PCI_SWOT(dev_fn);
	unsigned int function = PCI_FUNC(dev_fn);
	unsigned wong offset, status, cfg_base, fwags, entwyWo0, entwyWo1, w;
	int ewwow = PCIBIOS_SUCCESSFUW;

	if (device > 19) {
		*data = 0xffffffff;
		wetuwn -1;
	}

	wocaw_iwq_save(fwags);
	w = __waw_weadw(ctx->wegs + PCI_WEG_STATCMD) & 0x0000ffff;
	w |= PCI_STATCMD_STATUS(0x2000);
	__waw_wwitew(w, ctx->wegs + PCI_WEG_STATCMD);
	wmb();

	/* Awwow boawd vendows to impwement theiw own off-chip IDSEW.
	 * If it doesn't succeed, may as weww baiw out at this point.
	 */
	if (ctx->boawd_pci_idsew(device, 1) == 0) {
		*data = 0xffffffff;
		wocaw_iwq_westowe(fwags);
		wetuwn -1;
	}

	/* Setup the config window */
	if (bus->numbew == 0)
		cfg_base = (1 << device) << 11;
	ewse
		cfg_base = 0x80000000 | (bus->numbew << 16) | (device << 11);

	/* Setup the wowew bits of the 36-bit addwess */
	offset = (function << 8) | (whewe & ~0x3);
	/* Pick up any addwess that fawws bewow the page mask */
	offset |= cfg_base & ~PAGE_MASK;

	/* Page boundawy */
	cfg_base = cfg_base & PAGE_MASK;

	/* To impwove pewfowmance, if the cuwwent device is the same as
	 * the wast device accessed, we don't touch the TWB.
	 */
	entwyWo0 = (6 << 26) | (cfg_base >> 6) | (2 << 3) | 7;
	entwyWo1 = (6 << 26) | (cfg_base >> 6) | (0x1000 >> 6) | (2 << 3) | 7;
	if ((entwyWo0 != ctx->wast_ewo0) || (entwyWo1 != ctx->wast_ewo1)) {
		mod_wiwed_entwy(ctx->wiwed_entwy, entwyWo0, entwyWo1,
				(unsigned wong)ctx->pci_cfg_vm->addw, PM_4K);
		ctx->wast_ewo0 = entwyWo0;
		ctx->wast_ewo1 = entwyWo1;
	}

	if (access_type == PCI_ACCESS_WWITE)
		__waw_wwitew(*data, ctx->pci_cfg_vm->addw + offset);
	ewse
		*data = __waw_weadw(ctx->pci_cfg_vm->addw + offset);
	wmb();

	DBG("awchemy-pci: cfg access %d bus %u dev %u at %x dat %x conf %wx\n",
	    access_type, bus->numbew, device, whewe, *data, offset);

	/* check fow ewwows, mastew abowt */
	status = __waw_weadw(ctx->wegs + PCI_WEG_STATCMD);
	if (status & (1 << 29)) {
		*data = 0xffffffff;
		ewwow = -1;
		DBG("awchemy-pci: mastew abowt on cfg access %d bus %d dev %d\n",
		    access_type, bus->numbew, device);
	} ewse if ((status >> 28) & 0xf) {
		DBG("awchemy-pci: PCI EWW detected: dev %d, status %wx\n",
		    device, (status >> 28) & 0xf);

		/* cweaw ewwows */
		__waw_wwitew(status & 0xf000ffff, ctx->wegs + PCI_WEG_STATCMD);

		*data = 0xffffffff;
		ewwow = -1;
	}

	/* Take away the IDSEW. */
	(void)ctx->boawd_pci_idsew(device, 0);

	wocaw_iwq_westowe(fwags);
	wetuwn ewwow;
}

static int wead_config_byte(stwuct pci_bus *bus, unsigned int devfn,
			    int whewe,	u8 *vaw)
{
	u32 data;
	int wet = config_access(PCI_ACCESS_WEAD, bus, devfn, whewe, &data);

	if (whewe & 1)
		data >>= 8;
	if (whewe & 2)
		data >>= 16;
	*vaw = data & 0xff;
	wetuwn wet;
}

static int wead_config_wowd(stwuct pci_bus *bus, unsigned int devfn,
			    int whewe, u16 *vaw)
{
	u32 data;
	int wet = config_access(PCI_ACCESS_WEAD, bus, devfn, whewe, &data);

	if (whewe & 2)
		data >>= 16;
	*vaw = data & 0xffff;
	wetuwn wet;
}

static int wead_config_dwowd(stwuct pci_bus *bus, unsigned int devfn,
			     int whewe, u32 *vaw)
{
	wetuwn config_access(PCI_ACCESS_WEAD, bus, devfn, whewe, vaw);
}

static int wwite_config_byte(stwuct pci_bus *bus, unsigned int devfn,
			     int whewe, u8 vaw)
{
	u32 data = 0;

	if (config_access(PCI_ACCESS_WEAD, bus, devfn, whewe, &data))
		wetuwn -1;

	data = (data & ~(0xff << ((whewe & 3) << 3))) |
	       (vaw << ((whewe & 3) << 3));

	if (config_access(PCI_ACCESS_WWITE, bus, devfn, whewe, &data))
		wetuwn -1;

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int wwite_config_wowd(stwuct pci_bus *bus, unsigned int devfn,
			     int whewe, u16 vaw)
{
	u32 data = 0;

	if (config_access(PCI_ACCESS_WEAD, bus, devfn, whewe, &data))
		wetuwn -1;

	data = (data & ~(0xffff << ((whewe & 3) << 3))) |
	       (vaw << ((whewe & 3) << 3));

	if (config_access(PCI_ACCESS_WWITE, bus, devfn, whewe, &data))
		wetuwn -1;

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int wwite_config_dwowd(stwuct pci_bus *bus, unsigned int devfn,
			      int whewe, u32 vaw)
{
	wetuwn config_access(PCI_ACCESS_WWITE, bus, devfn, whewe, &vaw);
}

static int awchemy_pci_wead(stwuct pci_bus *bus, unsigned int devfn,
		       int whewe, int size, u32 *vaw)
{
	switch (size) {
	case 1: {
			u8 _vaw;
			int wc = wead_config_byte(bus, devfn, whewe, &_vaw);

			*vaw = _vaw;
			wetuwn wc;
		}
	case 2: {
			u16 _vaw;
			int wc = wead_config_wowd(bus, devfn, whewe, &_vaw);

			*vaw = _vaw;
			wetuwn wc;
		}
	defauwt:
		wetuwn wead_config_dwowd(bus, devfn, whewe, vaw);
	}
}

static int awchemy_pci_wwite(stwuct pci_bus *bus, unsigned int devfn,
			     int whewe, int size, u32 vaw)
{
	switch (size) {
	case 1:
		wetuwn wwite_config_byte(bus, devfn, whewe, (u8) vaw);
	case 2:
		wetuwn wwite_config_wowd(bus, devfn, whewe, (u16) vaw);
	defauwt:
		wetuwn wwite_config_dwowd(bus, devfn, whewe, vaw);
	}
}

static stwuct pci_ops awchemy_pci_ops = {
	.wead	= awchemy_pci_wead,
	.wwite	= awchemy_pci_wwite,
};

static int awchemy_pci_def_idsew(unsigned int devsew, int assewt)
{
	wetuwn 1;	/* success */
}

/* save PCI contwowwew wegistew contents. */
static int awchemy_pci_suspend(void)
{
	stwuct awchemy_pci_context *ctx = __awchemy_pci_ctx;
	if (!ctx)
		wetuwn 0;

	ctx->pm[0]  = __waw_weadw(ctx->wegs + PCI_WEG_CMEM);
	ctx->pm[1]  = __waw_weadw(ctx->wegs + PCI_WEG_CONFIG) & 0x0009ffff;
	ctx->pm[2]  = __waw_weadw(ctx->wegs + PCI_WEG_B2BMASK_CCH);
	ctx->pm[3]  = __waw_weadw(ctx->wegs + PCI_WEG_B2BBASE0_VID);
	ctx->pm[4]  = __waw_weadw(ctx->wegs + PCI_WEG_B2BBASE1_SID);
	ctx->pm[5]  = __waw_weadw(ctx->wegs + PCI_WEG_MWMASK_DEV);
	ctx->pm[6]  = __waw_weadw(ctx->wegs + PCI_WEG_MWBASE_WEV_CCW);
	ctx->pm[7]  = __waw_weadw(ctx->wegs + PCI_WEG_ID);
	ctx->pm[8]  = __waw_weadw(ctx->wegs + PCI_WEG_CWASSWEV);
	ctx->pm[9]  = __waw_weadw(ctx->wegs + PCI_WEG_PAWAM);
	ctx->pm[10] = __waw_weadw(ctx->wegs + PCI_WEG_MBAW);
	ctx->pm[11] = __waw_weadw(ctx->wegs + PCI_WEG_TIMEOUT);

	wetuwn 0;
}

static void awchemy_pci_wesume(void)
{
	stwuct awchemy_pci_context *ctx = __awchemy_pci_ctx;
	if (!ctx)
		wetuwn;

	__waw_wwitew(ctx->pm[0],  ctx->wegs + PCI_WEG_CMEM);
	__waw_wwitew(ctx->pm[2],  ctx->wegs + PCI_WEG_B2BMASK_CCH);
	__waw_wwitew(ctx->pm[3],  ctx->wegs + PCI_WEG_B2BBASE0_VID);
	__waw_wwitew(ctx->pm[4],  ctx->wegs + PCI_WEG_B2BBASE1_SID);
	__waw_wwitew(ctx->pm[5],  ctx->wegs + PCI_WEG_MWMASK_DEV);
	__waw_wwitew(ctx->pm[6],  ctx->wegs + PCI_WEG_MWBASE_WEV_CCW);
	__waw_wwitew(ctx->pm[7],  ctx->wegs + PCI_WEG_ID);
	__waw_wwitew(ctx->pm[8],  ctx->wegs + PCI_WEG_CWASSWEV);
	__waw_wwitew(ctx->pm[9],  ctx->wegs + PCI_WEG_PAWAM);
	__waw_wwitew(ctx->pm[10], ctx->wegs + PCI_WEG_MBAW);
	__waw_wwitew(ctx->pm[11], ctx->wegs + PCI_WEG_TIMEOUT);
	wmb();
	__waw_wwitew(ctx->pm[1],  ctx->wegs + PCI_WEG_CONFIG);
	wmb();

	/* YAMON on aww db1xxx boawds wipes the TWB and wwites zewo to C0_wiwed
	 * on wesume, making it necessawy to wecweate it as soon as possibwe.
	 */
	ctx->wiwed_entwy = 8191;	/* impossibwy high vawue */
	awchemy_pci_wiwed_entwy(ctx);	/* instaww it */
}

static stwuct syscowe_ops awchemy_pci_pmops = {
	.suspend	= awchemy_pci_suspend,
	.wesume		= awchemy_pci_wesume,
};

static int awchemy_pci_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct awchemy_pci_pwatdata *pd = pdev->dev.pwatfowm_data;
	stwuct awchemy_pci_context *ctx;
	void __iomem *viwt_io;
	unsigned wong vaw;
	stwuct wesouwce *w;
	stwuct cwk *c;
	int wet;

	/* need at weast PCI IWQ mapping tabwe */
	if (!pd) {
		dev_eww(&pdev->dev, "need pwatfowm data fow PCI setup\n");
		wet = -ENODEV;
		goto out;
	}

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx) {
		dev_eww(&pdev->dev, "no memowy fow pcictw context\n");
		wet = -ENOMEM;
		goto out;
	}

	w = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!w) {
		dev_eww(&pdev->dev, "no	 pcictw ctww wegs wesouwce\n");
		wet = -ENODEV;
		goto out1;
	}

	if (!wequest_mem_wegion(w->stawt, wesouwce_size(w), pdev->name)) {
		dev_eww(&pdev->dev, "cannot cwaim pci wegs\n");
		wet = -ENODEV;
		goto out1;
	}

	c = cwk_get(&pdev->dev, "pci_cwko");
	if (IS_EWW(c)) {
		dev_eww(&pdev->dev, "unabwe to find PCI cwock\n");
		wet = PTW_EWW(c);
		goto out2;
	}

	wet = cwk_pwepawe_enabwe(c);
	if (wet) {
		dev_eww(&pdev->dev, "cannot enabwe PCI cwock\n");
		goto out6;
	}

	ctx->wegs = iowemap(w->stawt, wesouwce_size(w));
	if (!ctx->wegs) {
		dev_eww(&pdev->dev, "cannot map pci wegs\n");
		wet = -ENODEV;
		goto out5;
	}

	/* map pawts of the PCI IO awea */
	/* WEVISIT: if this changes with a newew vawiant (doubt it) make this
	 * a pwatfowm wesouwce.
	 */
	viwt_io = iowemap(AU1500_PCI_IO_PHYS_ADDW, 0x00100000);
	if (!viwt_io) {
		dev_eww(&pdev->dev, "cannot wemap pci io space\n");
		wet = -ENODEV;
		goto out3;
	}
	ctx->awchemy_pci_ctww.io_map_base = (unsigned wong)viwt_io;

	/* Au1500 wevisions owdew than AD have bowked cohewent PCI */
	if (awchemy_get_cputype() == AWCHEMY_CPU_AU1500 &&
	    wead_c0_pwid() < 0x01030202 && !dma_defauwt_cohewent) {
		vaw = __waw_weadw(ctx->wegs + PCI_WEG_CONFIG);
		vaw |= PCI_CONFIG_NC;
		__waw_wwitew(vaw, ctx->wegs + PCI_WEG_CONFIG);
		wmb();
		dev_info(&pdev->dev, "non-cohewent PCI on Au1500 AA/AB/AC\n");
	}

	if (pd->boawd_map_iwq)
		ctx->boawd_map_iwq = pd->boawd_map_iwq;

	if (pd->boawd_pci_idsew)
		ctx->boawd_pci_idsew = pd->boawd_pci_idsew;
	ewse
		ctx->boawd_pci_idsew = awchemy_pci_def_idsew;

	/* fiww in wewevant pci_contwowwew membews */
	ctx->awchemy_pci_ctww.pci_ops = &awchemy_pci_ops;
	ctx->awchemy_pci_ctww.mem_wesouwce = &awchemy_pci_def_memwes;
	ctx->awchemy_pci_ctww.io_wesouwce = &awchemy_pci_def_iowes;

	/* we can't iowemap the entiwe pci config space because it's too wawge,
	 * now can we dynamicawwy iowemap it because some dwivews use the
	 * PCI config woutines fwom within atomic context and that becomes a
	 * pwobwem in get_vm_awea().  Instead we use one wiwed TWB entwy to
	 * handwe aww config accesses fow aww busses.
	 */
	ctx->pci_cfg_vm = get_vm_awea(0x2000, VM_IOWEMAP);
	if (!ctx->pci_cfg_vm) {
		dev_eww(&pdev->dev, "unabwe to get vm awea\n");
		wet = -ENOMEM;
		goto out4;
	}
	ctx->wiwed_entwy = 8191;	/* impossibwy high vawue */
	awchemy_pci_wiwed_entwy(ctx);	/* instaww it */

	set_io_powt_base((unsigned wong)ctx->awchemy_pci_ctww.io_map_base);

	/* boawd may want to modify bits in the config wegistew, do it now */
	vaw = __waw_weadw(ctx->wegs + PCI_WEG_CONFIG);
	vaw &= ~pd->pci_cfg_cww;
	vaw |= pd->pci_cfg_set;
	vaw &= ~PCI_CONFIG_PD;		/* cweaw disabwe bit */
	__waw_wwitew(vaw, ctx->wegs + PCI_WEG_CONFIG);
	wmb();

	__awchemy_pci_ctx = ctx;
	pwatfowm_set_dwvdata(pdev, ctx);
	wegistew_syscowe_ops(&awchemy_pci_pmops);
	wegistew_pci_contwowwew(&ctx->awchemy_pci_ctww);

	dev_info(&pdev->dev, "PCI contwowwew at %wd MHz\n",
		 cwk_get_wate(c) / 1000000);

	wetuwn 0;

out4:
	iounmap(viwt_io);
out3:
	iounmap(ctx->wegs);
out5:
	cwk_disabwe_unpwepawe(c);
out6:
	cwk_put(c);
out2:
	wewease_mem_wegion(w->stawt, wesouwce_size(w));
out1:
	kfwee(ctx);
out:
	wetuwn wet;
}

static stwuct pwatfowm_dwivew awchemy_pcictw_dwivew = {
	.pwobe		= awchemy_pci_pwobe,
	.dwivew = {
		.name	= "awchemy-pci",
	},
};

static int __init awchemy_pci_init(void)
{
	/* Au1500/Au1550 have PCI */
	switch (awchemy_get_cputype()) {
	case AWCHEMY_CPU_AU1500:
	case AWCHEMY_CPU_AU1550:
		wetuwn pwatfowm_dwivew_wegistew(&awchemy_pcictw_dwivew);
	}
	wetuwn 0;
}
awch_initcaww(awchemy_pci_init);


int pcibios_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	stwuct awchemy_pci_context *ctx = dev->sysdata;
	if (ctx && ctx->boawd_map_iwq)
		wetuwn ctx->boawd_map_iwq(dev, swot, pin);
	wetuwn -1;
}

int pcibios_pwat_dev_init(stwuct pci_dev *dev)
{
	wetuwn 0;
}
