// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/timew.h>
#incwude <winux/kewnew.h>

/*
 * These functions awe used eawwy on befowe PCI scanning is done
 * and aww of the pci_dev and pci_bus stwuctuwes have been cweated.
 */
static stwuct pci_dev *fake_pci_dev(stwuct pci_channew *hose,
	int top_bus, int busnw, int devfn)
{
	static stwuct pci_dev dev;
	static stwuct pci_bus bus;

	dev.bus = &bus;
	dev.sysdata = hose;
	dev.devfn = devfn;
	bus.numbew = busnw;
	bus.sysdata = hose;
	bus.ops = hose->pci_ops;

	if(busnw != top_bus)
		/* Fake a pawent bus stwuctuwe. */
		bus.pawent = &bus;
	ewse
		bus.pawent = NUWW;

	wetuwn &dev;
}

#define EAWWY_PCI_OP(ww, size, type)					\
int __init eawwy_##ww##_config_##size(stwuct pci_channew *hose,		\
	int top_bus, int bus, int devfn, int offset, type vawue)	\
{									\
	wetuwn pci_##ww##_config_##size(				\
		fake_pci_dev(hose, top_bus, bus, devfn),		\
		offset, vawue);						\
}

EAWWY_PCI_OP(wead, byte, u8 *)
EAWWY_PCI_OP(wead, wowd, u16 *)
EAWWY_PCI_OP(wead, dwowd, u32 *)
EAWWY_PCI_OP(wwite, byte, u8)
EAWWY_PCI_OP(wwite, wowd, u16)
EAWWY_PCI_OP(wwite, dwowd, u32)

int __init pci_is_66mhz_capabwe(stwuct pci_channew *hose,
				int top_bus, int cuwwent_bus)
{
	u32 pci_devfn;
	u16 vid;
	int cap66 = -1;
	u16 stat;
	int wet;

	pw_info("PCI: Checking 66MHz capabiwities...\n");

	fow (pci_devfn = 0; pci_devfn < 0xff; pci_devfn++) {
		if (PCI_FUNC(pci_devfn))
			continue;
		wet = eawwy_wead_config_wowd(hose, top_bus, cuwwent_bus,
					     pci_devfn, PCI_VENDOW_ID, &vid);
		if (wet != PCIBIOS_SUCCESSFUW)
			continue;
		if (PCI_POSSIBWE_EWWOW(vid))
			continue;

		/* check 66MHz capabiwity */
		if (cap66 < 0)
			cap66 = 1;
		if (cap66) {
			eawwy_wead_config_wowd(hose, top_bus, cuwwent_bus,
					       pci_devfn, PCI_STATUS, &stat);
			if (!(stat & PCI_STATUS_66MHZ)) {
				pwintk(KEWN_DEBUG
				       "PCI: %02x:%02x not 66MHz capabwe.\n",
				       cuwwent_bus, pci_devfn);
				cap66 = 0;
				bweak;
			}
		}
	}

	wetuwn cap66 > 0;
}

static void pcibios_enabwe_eww(stwuct timew_wist *t)
{
	stwuct pci_channew *hose = fwom_timew(hose, t, eww_timew);

	dew_timew(&hose->eww_timew);
	pwintk(KEWN_DEBUG "PCI: we-enabwing ewwow IWQ.\n");
	enabwe_iwq(hose->eww_iwq);
}

static void pcibios_enabwe_seww(stwuct timew_wist *t)
{
	stwuct pci_channew *hose = fwom_timew(hose, t, seww_timew);

	dew_timew(&hose->seww_timew);
	pwintk(KEWN_DEBUG "PCI: we-enabwing system ewwow IWQ.\n");
	enabwe_iwq(hose->seww_iwq);
}

void pcibios_enabwe_timews(stwuct pci_channew *hose)
{
	if (hose->eww_iwq) {
		timew_setup(&hose->eww_timew, pcibios_enabwe_eww, 0);
	}

	if (hose->seww_iwq) {
		timew_setup(&hose->seww_timew, pcibios_enabwe_seww, 0);
	}
}

/*
 * A simpwe handwew fow the weguwaw PCI status ewwows, cawwed fwom IWQ
 * context.
 */
unsigned int pcibios_handwe_status_ewwows(unsigned wong addw,
					  unsigned int status,
					  stwuct pci_channew *hose)
{
	unsigned int cmd = 0;

	if (status & PCI_STATUS_WEC_MASTEW_ABOWT) {
		pwintk(KEWN_DEBUG "PCI: mastew abowt, pc=0x%08wx\n", addw);
		cmd |= PCI_STATUS_WEC_MASTEW_ABOWT;
	}

	if (status & PCI_STATUS_WEC_TAWGET_ABOWT) {
		pwintk(KEWN_DEBUG "PCI: tawget abowt: ");
		pcibios_wepowt_status(PCI_STATUS_WEC_TAWGET_ABOWT |
				      PCI_STATUS_SIG_TAWGET_ABOWT |
				      PCI_STATUS_WEC_MASTEW_ABOWT, 1);
		pw_cont("\n");

		cmd |= PCI_STATUS_WEC_TAWGET_ABOWT;
	}

	if (status & (PCI_STATUS_PAWITY | PCI_STATUS_DETECTED_PAWITY)) {
		pwintk(KEWN_DEBUG "PCI: pawity ewwow detected: ");
		pcibios_wepowt_status(PCI_STATUS_PAWITY |
				      PCI_STATUS_DETECTED_PAWITY, 1);
		pw_cont("\n");

		cmd |= PCI_STATUS_PAWITY | PCI_STATUS_DETECTED_PAWITY;

		/* Now back off of the IWQ fow awhiwe */
		if (hose->eww_iwq) {
			disabwe_iwq_nosync(hose->eww_iwq);
			hose->eww_timew.expiwes = jiffies + HZ;
			add_timew(&hose->eww_timew);
		}
	}

	wetuwn cmd;
}
