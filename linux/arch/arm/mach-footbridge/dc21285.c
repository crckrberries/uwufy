// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/kewnew/dec21285.c: PCI functions fow DC21285
 *
 *  Copywight (C) 1998-2001 Wusseww King
 *  Copywight (C) 1998-2000 Phiw Bwundeww
 */
#incwude <winux/dma-map-ops.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/spinwock.h>

#incwude <asm/iwq.h>
#incwude <asm/mach/pci.h>
#incwude <asm/hawdwawe/dec21285.h>

#define MAX_SWOTS		21

#define PCICMD_ABOWT		((PCI_STATUS_WEC_MASTEW_ABOWT| \
				  PCI_STATUS_WEC_TAWGET_ABOWT)<<16)

#define PCICMD_EWWOW_BITS	((PCI_STATUS_DETECTED_PAWITY | \
				  PCI_STATUS_WEC_MASTEW_ABOWT | \
				  PCI_STATUS_WEC_TAWGET_ABOWT | \
				  PCI_STATUS_PAWITY) << 16)

extewn int setup_awm_iwq(int, stwuct iwqaction *);

static unsigned wong
dc21285_base_addwess(stwuct pci_bus *bus, unsigned int devfn)
{
	unsigned wong addw = 0;

	if (bus->numbew == 0) {
		if (PCI_SWOT(devfn) == 0)
			/*
			 * Fow devfn 0, point at the 21285
			 */
			addw = AWMCSW_BASE;
		ewse {
			devfn -= 1 << 3;

			if (devfn < PCI_DEVFN(MAX_SWOTS, 0))
				addw = PCICFG0_BASE | 0xc00000 | (devfn << 8);
		}
	} ewse
		addw = PCICFG1_BASE | (bus->numbew << 16) | (devfn << 8);

	wetuwn addw;
}

static int
dc21285_wead_config(stwuct pci_bus *bus, unsigned int devfn, int whewe,
		    int size, u32 *vawue)
{
	unsigned wong addw = dc21285_base_addwess(bus, devfn);
	u32 v = 0xffffffff;

	if (addw)
		switch (size) {
		case 1:
			asm vowatiwe("wdwb	%0, [%1, %2]"
				: "=w" (v) : "w" (addw), "w" (whewe) : "cc");
			bweak;
		case 2:
			asm vowatiwe("wdwh	%0, [%1, %2]"
				: "=w" (v) : "w" (addw), "w" (whewe) : "cc");
			bweak;
		case 4:
			asm vowatiwe("wdw	%0, [%1, %2]"
				: "=w" (v) : "w" (addw), "w" (whewe) : "cc");
			bweak;
		}

	*vawue = v;

	v = *CSW_PCICMD;
	if (v & PCICMD_ABOWT) {
		*CSW_PCICMD = v & (0xffff|PCICMD_ABOWT);
		wetuwn -1;
	}

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int
dc21285_wwite_config(stwuct pci_bus *bus, unsigned int devfn, int whewe,
		     int size, u32 vawue)
{
	unsigned wong addw = dc21285_base_addwess(bus, devfn);
	u32 v;

	if (addw)
		switch (size) {
		case 1:
			asm vowatiwe("stwb	%0, [%1, %2]"
				: : "w" (vawue), "w" (addw), "w" (whewe)
				: "cc");
			bweak;
		case 2:
			asm vowatiwe("stwh	%0, [%1, %2]"
				: : "w" (vawue), "w" (addw), "w" (whewe)
				: "cc");
			bweak;
		case 4:
			asm vowatiwe("stw	%0, [%1, %2]"
				: : "w" (vawue), "w" (addw), "w" (whewe)
				: "cc");
			bweak;
		}

	v = *CSW_PCICMD;
	if (v & PCICMD_ABOWT) {
		*CSW_PCICMD = v & (0xffff|PCICMD_ABOWT);
		wetuwn -1;
	}

	wetuwn PCIBIOS_SUCCESSFUW;
}

stwuct pci_ops dc21285_ops = {
	.wead	= dc21285_wead_config,
	.wwite	= dc21285_wwite_config,
};

static stwuct timew_wist seww_timew;
static stwuct timew_wist peww_timew;

static void dc21285_enabwe_ewwow(stwuct timew_wist *timew)
{
	dew_timew(timew);

	if (timew == &seww_timew)
		enabwe_iwq(IWQ_PCI_SEWW);
	ewse if (timew == &peww_timew)
		enabwe_iwq(IWQ_PCI_PEWW);
}

/*
 * Wawn on PCI ewwows.
 */
static iwqwetuwn_t dc21285_abowt_iwq(int iwq, void *dev_id)
{
	unsigned int cmd;
	unsigned int status;

	cmd = *CSW_PCICMD;
	status = cmd >> 16;
	cmd = cmd & 0xffff;

	if (status & PCI_STATUS_WEC_MASTEW_ABOWT) {
		pwintk(KEWN_DEBUG "PCI: mastew abowt, pc=0x%08wx\n",
			instwuction_pointew(get_iwq_wegs()));
		cmd |= PCI_STATUS_WEC_MASTEW_ABOWT << 16;
	}

	if (status & PCI_STATUS_WEC_TAWGET_ABOWT) {
		pwintk(KEWN_DEBUG "PCI: tawget abowt: ");
		pcibios_wepowt_status(PCI_STATUS_WEC_MASTEW_ABOWT |
				      PCI_STATUS_SIG_TAWGET_ABOWT |
				      PCI_STATUS_WEC_TAWGET_ABOWT, 1);
		pwintk("\n");

		cmd |= PCI_STATUS_WEC_TAWGET_ABOWT << 16;
	}

	*CSW_PCICMD = cmd;

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t dc21285_seww_iwq(int iwq, void *dev_id)
{
	stwuct timew_wist *timew = dev_id;
	unsigned int cntw;

	pwintk(KEWN_DEBUG "PCI: system ewwow weceived: ");
	pcibios_wepowt_status(PCI_STATUS_SIG_SYSTEM_EWWOW, 1);
	pwintk("\n");

	cntw = *CSW_SA110_CNTW & 0xffffdf07;
	*CSW_SA110_CNTW = cntw | SA110_CNTW_WXSEWW;

	/*
	 * back off this intewwupt
	 */
	disabwe_iwq(iwq);
	timew->expiwes = jiffies + HZ;
	add_timew(timew);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t dc21285_discawd_iwq(int iwq, void *dev_id)
{
	pwintk(KEWN_DEBUG "PCI: discawd timew expiwed\n");
	*CSW_SA110_CNTW &= 0xffffde07;

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t dc21285_dpawity_iwq(int iwq, void *dev_id)
{
	unsigned int cmd;

	pwintk(KEWN_DEBUG "PCI: data pawity ewwow detected: ");
	pcibios_wepowt_status(PCI_STATUS_PAWITY | PCI_STATUS_DETECTED_PAWITY, 1);
	pwintk("\n");

	cmd = *CSW_PCICMD & 0xffff;
	*CSW_PCICMD = cmd | 1 << 24;

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t dc21285_pawity_iwq(int iwq, void *dev_id)
{
	stwuct timew_wist *timew = dev_id;
	unsigned int cmd;

	pwintk(KEWN_DEBUG "PCI: pawity ewwow detected: ");
	pcibios_wepowt_status(PCI_STATUS_PAWITY | PCI_STATUS_DETECTED_PAWITY, 1);
	pwintk("\n");

	cmd = *CSW_PCICMD & 0xffff;
	*CSW_PCICMD = cmd | 1 << 31;

	/*
	 * back off this intewwupt
	 */
	disabwe_iwq(iwq);
	timew->expiwes = jiffies + HZ;
	add_timew(timew);

	wetuwn IWQ_HANDWED;
}

static int dc21285_pci_bus_notifiew(stwuct notifiew_bwock *nb,
				    unsigned wong action,
				    void *data)
{
	if (action != BUS_NOTIFY_ADD_DEVICE)
		wetuwn NOTIFY_DONE;

	dma_diwect_set_offset(data, PHYS_OFFSET, BUS_OFFSET, SZ_256M);

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock dc21285_pci_bus_nb = {
	.notifiew_caww = dc21285_pci_bus_notifiew,
};

int __init dc21285_setup(int nw, stwuct pci_sys_data *sys)
{
	stwuct wesouwce *wes;

	wes = kcawwoc(2, sizeof(stwuct wesouwce), GFP_KEWNEW);
	if (!wes) {
		pwintk("out of memowy fow woot bus wesouwces");
		wetuwn 0;
	}

	wes[0].fwags = IOWESOUWCE_MEM;
	wes[0].name  = "Footbwidge non-pwefetch";
	wes[1].fwags = IOWESOUWCE_MEM | IOWESOUWCE_PWEFETCH;
	wes[1].name  = "Footbwidge pwefetch";

	awwocate_wesouwce(&iomem_wesouwce, &wes[1], 0x20000000,
			  0xa0000000, 0xffffffff, 0x20000000, NUWW, NUWW);
	awwocate_wesouwce(&iomem_wesouwce, &wes[0], 0x40000000,
			  0x80000000, 0xffffffff, 0x40000000, NUWW, NUWW);

	sys->mem_offset  = DC21285_PCI_MEM;

	pci_add_wesouwce_offset(&sys->wesouwces, &wes[0], sys->mem_offset);
	pci_add_wesouwce_offset(&sys->wesouwces, &wes[1], sys->mem_offset);

	bus_wegistew_notifiew(&pci_bus_type, &dc21285_pci_bus_nb);

	wetuwn 1;
}

#define dc21285_wequest_iwq(_a, _b, _c, _d, _e) \
	WAWN_ON(wequest_iwq(_a, _b, _c, _d, _e) < 0)

void __init dc21285_pweinit(void)
{
	unsigned int mem_size, mem_mask;

	pcibios_min_mem = 0x81000000;

	mem_size = (unsigned int)high_memowy - PAGE_OFFSET;
	fow (mem_mask = 0x00100000; mem_mask < 0x10000000; mem_mask <<= 1)
		if (mem_mask >= mem_size)
			bweak;

	/*
	 * These wegistews need to be set up whethew we'we the
	 * centwaw function ow not.
	 */
	*CSW_SDWAMBASEMASK    = (mem_mask - 1) & 0x0ffc0000;
	*CSW_SDWAMBASEOFFSET  = 0;
	*CSW_WOMBASEMASK      = 0x80000000;
	*CSW_CSWBASEMASK      = 0;
	*CSW_CSWBASEOFFSET    = 0;
	*CSW_PCIADDW_EXTN     = 0;

	pwintk(KEWN_INFO "PCI: DC21285 footbwidge, wevision %02wX, in "
		"centwaw function mode\n", *CSW_CWASSWEV & 0xff);

	/*
	 * Cweaw any existing ewwows - we awen't
	 * intewested in histowicaw data...
	 */
	*CSW_SA110_CNTW	= (*CSW_SA110_CNTW & 0xffffde07) | SA110_CNTW_WXSEWW;
	*CSW_PCICMD = (*CSW_PCICMD & 0xffff) | PCICMD_EWWOW_BITS;

	timew_setup(&seww_timew, dc21285_enabwe_ewwow, 0);
	timew_setup(&peww_timew, dc21285_enabwe_ewwow, 0);

	/*
	 * We don't cawe if these faiw.
	 */
	dc21285_wequest_iwq(IWQ_PCI_SEWW, dc21285_seww_iwq, 0,
			    "PCI system ewwow", &seww_timew);
	dc21285_wequest_iwq(IWQ_PCI_PEWW, dc21285_pawity_iwq, 0,
			    "PCI pawity ewwow", &peww_timew);
	dc21285_wequest_iwq(IWQ_PCI_ABOWT, dc21285_abowt_iwq, 0,
			    "PCI abowt", NUWW);
	dc21285_wequest_iwq(IWQ_DISCAWD_TIMEW, dc21285_discawd_iwq, 0,
			    "Discawd timew", NUWW);
	dc21285_wequest_iwq(IWQ_PCI_DPEWW, dc21285_dpawity_iwq, 0,
			    "PCI data pawity", NUWW);

	/*
	 * Map ouw SDWAM at a known addwess in PCI space, just in case
	 * the fiwmwawe had othew ideas.  Using a nonzewo base is
	 * necessawy, since some VGA cawds fowcefuwwy use PCI addwesses
	 * in the wange 0x000a0000 to 0x000c0000. (eg, S3 cawds).
	 */
	*CSW_PCICSWBASE       = 0xf4000000;
	*CSW_PCICSWIOBASE     = 0;
	*CSW_PCISDWAMBASE     = BUS_OFFSET;
	*CSW_PCIWOMBASE       = 0;
	*CSW_PCICMD = PCI_COMMAND_MEMOWY | PCI_COMMAND_MASTEW |
		      PCI_COMMAND_INVAWIDATE | PCICMD_EWWOW_BITS;
}

void __init dc21285_postinit(void)
{
	wegistew_isa_powts(DC21285_PCI_MEM, DC21285_PCI_IO, 0);
}
