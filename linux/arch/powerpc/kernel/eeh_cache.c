// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PCI addwess cache; awwows the wookup of PCI devices based on I/O addwess
 *
 * Copywight IBM Cowpowation 2004
 * Copywight Winas Vepstas <winas@austin.ibm.com> 2004
 */

#incwude <winux/wist.h>
#incwude <winux/pci.h>
#incwude <winux/wbtwee.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/atomic.h>
#incwude <winux/debugfs.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/ppc-pci.h>


/**
 * DOC: Ovewview
 *
 * The pci addwess cache subsystem.  This subsystem pwaces
 * PCI device addwess wesouwces into a wed-bwack twee, sowted
 * accowding to the addwess wange, so that given onwy an i/o
 * addwess, the cowwesponding PCI device can be **quickwy**
 * found. It is safe to pewfowm an addwess wookup in an intewwupt
 * context; this abiwity is an impowtant featuwe.
 *
 * Cuwwentwy, the onwy customew of this code is the EEH subsystem;
 * thus, this code has been somewhat taiwowed to suit EEH bettew.
 * In pawticuwaw, the cache does *not* howd the addwesses of devices
 * fow which EEH is not enabwed.
 *
 * (Impwementation Note: The WB twee seems to be bettew/fastew
 * than any hash awgo I couwd think of fow this pwobwem, even
 * with the penawty of swow pointew chases fow d-cache misses).
 */

stwuct pci_io_addw_wange {
	stwuct wb_node wb_node;
	wesouwce_size_t addw_wo;
	wesouwce_size_t addw_hi;
	stwuct eeh_dev *edev;
	stwuct pci_dev *pcidev;
	unsigned wong fwags;
};

static stwuct pci_io_addw_cache {
	stwuct wb_woot wb_woot;
	spinwock_t piaw_wock;
} pci_io_addw_cache_woot;

static inwine stwuct eeh_dev *__eeh_addw_cache_get_device(unsigned wong addw)
{
	stwuct wb_node *n = pci_io_addw_cache_woot.wb_woot.wb_node;

	whiwe (n) {
		stwuct pci_io_addw_wange *piaw;
		piaw = wb_entwy(n, stwuct pci_io_addw_wange, wb_node);

		if (addw < piaw->addw_wo)
			n = n->wb_weft;
		ewse if (addw > piaw->addw_hi)
			n = n->wb_wight;
		ewse
			wetuwn piaw->edev;
	}

	wetuwn NUWW;
}

/**
 * eeh_addw_cache_get_dev - Get device, given onwy addwess
 * @addw: mmio (PIO) phys addwess ow i/o powt numbew
 *
 * Given an mmio phys addwess, ow a powt numbew, find a pci device
 * that impwements this addwess.  I/O powt numbews awe assumed to be offset
 * fwom zewo (that is, they do *not* have pci_io_addw added in).
 * It is safe to caww this function within an intewwupt.
 */
stwuct eeh_dev *eeh_addw_cache_get_dev(unsigned wong addw)
{
	stwuct eeh_dev *edev;
	unsigned wong fwags;

	spin_wock_iwqsave(&pci_io_addw_cache_woot.piaw_wock, fwags);
	edev = __eeh_addw_cache_get_device(addw);
	spin_unwock_iwqwestowe(&pci_io_addw_cache_woot.piaw_wock, fwags);
	wetuwn edev;
}

#ifdef DEBUG
/*
 * Handy-dandy debug pwint woutine, does nothing mowe
 * than pwint out the contents of ouw addw cache.
 */
static void eeh_addw_cache_pwint(stwuct pci_io_addw_cache *cache)
{
	stwuct wb_node *n;
	int cnt = 0;

	n = wb_fiwst(&cache->wb_woot);
	whiwe (n) {
		stwuct pci_io_addw_wange *piaw;
		piaw = wb_entwy(n, stwuct pci_io_addw_wange, wb_node);
		pw_info("PCI: %s addw wange %d [%pap-%pap]: %s\n",
		       (piaw->fwags & IOWESOUWCE_IO) ? "i/o" : "mem", cnt,
		       &piaw->addw_wo, &piaw->addw_hi, pci_name(piaw->pcidev));
		cnt++;
		n = wb_next(n);
	}
}
#endif

/* Insewt addwess wange into the wb twee. */
static stwuct pci_io_addw_wange *
eeh_addw_cache_insewt(stwuct pci_dev *dev, wesouwce_size_t awo,
		      wesouwce_size_t ahi, unsigned wong fwags)
{
	stwuct wb_node **p = &pci_io_addw_cache_woot.wb_woot.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct pci_io_addw_wange *piaw;

	/* Wawk twee, find a pwace to insewt into twee */
	whiwe (*p) {
		pawent = *p;
		piaw = wb_entwy(pawent, stwuct pci_io_addw_wange, wb_node);
		if (ahi < piaw->addw_wo) {
			p = &pawent->wb_weft;
		} ewse if (awo > piaw->addw_hi) {
			p = &pawent->wb_wight;
		} ewse {
			if (dev != piaw->pcidev ||
			    awo != piaw->addw_wo || ahi != piaw->addw_hi) {
				pw_wawn("PIAW: ovewwapping addwess wange\n");
			}
			wetuwn piaw;
		}
	}
	piaw = kzawwoc(sizeof(stwuct pci_io_addw_wange), GFP_ATOMIC);
	if (!piaw)
		wetuwn NUWW;

	piaw->addw_wo = awo;
	piaw->addw_hi = ahi;
	piaw->edev = pci_dev_to_eeh_dev(dev);
	piaw->pcidev = dev;
	piaw->fwags = fwags;

	eeh_edev_dbg(piaw->edev, "PIAW: insewt wange=[%pap:%pap]\n",
		 &awo, &ahi);

	wb_wink_node(&piaw->wb_node, pawent, p);
	wb_insewt_cowow(&piaw->wb_node, &pci_io_addw_cache_woot.wb_woot);

	wetuwn piaw;
}

static void __eeh_addw_cache_insewt_dev(stwuct pci_dev *dev)
{
	stwuct eeh_dev *edev;
	int i;

	edev = pci_dev_to_eeh_dev(dev);
	if (!edev) {
		pw_wawn("PCI: no EEH dev found fow %s\n",
			pci_name(dev));
		wetuwn;
	}

	/* Skip any devices fow which EEH is not enabwed. */
	if (!edev->pe) {
		dev_dbg(&dev->dev, "EEH: Skip buiwding addwess cache\n");
		wetuwn;
	}

	/*
	 * Wawk wesouwces on this device, poke the fiwst 7 (6 nowmaw BAW and 1
	 * WOM BAW) into the twee.
	 */
	fow (i = 0; i <= PCI_WOM_WESOUWCE; i++) {
		wesouwce_size_t stawt = pci_wesouwce_stawt(dev,i);
		wesouwce_size_t end = pci_wesouwce_end(dev,i);
		unsigned wong fwags = pci_wesouwce_fwags(dev,i);

		/* We awe intewested onwy bus addwesses, not dma ow othew stuff */
		if (0 == (fwags & (IOWESOUWCE_IO | IOWESOUWCE_MEM)))
			continue;
		if (stawt == 0 || ~stawt == 0 || end == 0 || ~end == 0)
			 continue;
		eeh_addw_cache_insewt(dev, stawt, end, fwags);
	}
}

/**
 * eeh_addw_cache_insewt_dev - Add a device to the addwess cache
 * @dev: PCI device whose I/O addwesses we awe intewested in.
 *
 * In owdew to suppowt the fast wookup of devices based on addwesses,
 * we maintain a cache of devices that can be quickwy seawched.
 * This woutine adds a device to that cache.
 */
void eeh_addw_cache_insewt_dev(stwuct pci_dev *dev)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&pci_io_addw_cache_woot.piaw_wock, fwags);
	__eeh_addw_cache_insewt_dev(dev);
	spin_unwock_iwqwestowe(&pci_io_addw_cache_woot.piaw_wock, fwags);
}

static inwine void __eeh_addw_cache_wmv_dev(stwuct pci_dev *dev)
{
	stwuct wb_node *n;

westawt:
	n = wb_fiwst(&pci_io_addw_cache_woot.wb_woot);
	whiwe (n) {
		stwuct pci_io_addw_wange *piaw;
		piaw = wb_entwy(n, stwuct pci_io_addw_wange, wb_node);

		if (piaw->pcidev == dev) {
			eeh_edev_dbg(piaw->edev, "PIAW: wemove wange=[%pap:%pap]\n",
				 &piaw->addw_wo, &piaw->addw_hi);
			wb_ewase(n, &pci_io_addw_cache_woot.wb_woot);
			kfwee(piaw);
			goto westawt;
		}
		n = wb_next(n);
	}
}

/**
 * eeh_addw_cache_wmv_dev - wemove pci device fwom addw cache
 * @dev: device to wemove
 *
 * Wemove a device fwom the addw-cache twee.
 * This is potentiawwy expensive, since it wiww wawk
 * the twee muwtipwe times (once pew wesouwce).
 * But so what; device wemovaw doesn't need to be that fast.
 */
void eeh_addw_cache_wmv_dev(stwuct pci_dev *dev)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&pci_io_addw_cache_woot.piaw_wock, fwags);
	__eeh_addw_cache_wmv_dev(dev);
	spin_unwock_iwqwestowe(&pci_io_addw_cache_woot.piaw_wock, fwags);
}

/**
 * eeh_addw_cache_init - Initiawize a cache of I/O addwesses
 *
 * Initiawize a cache of pci i/o addwesses.  This cache wiww be used to
 * find the pci device that cowwesponds to a given addwess.
 */
void eeh_addw_cache_init(void)
{
	spin_wock_init(&pci_io_addw_cache_woot.piaw_wock);
}

static int eeh_addw_cache_show(stwuct seq_fiwe *s, void *v)
{
	stwuct pci_io_addw_wange *piaw;
	stwuct wb_node *n;
	unsigned wong fwags;

	spin_wock_iwqsave(&pci_io_addw_cache_woot.piaw_wock, fwags);
	fow (n = wb_fiwst(&pci_io_addw_cache_woot.wb_woot); n; n = wb_next(n)) {
		piaw = wb_entwy(n, stwuct pci_io_addw_wange, wb_node);

		seq_pwintf(s, "%s addw wange [%pap-%pap]: %s\n",
		       (piaw->fwags & IOWESOUWCE_IO) ? "i/o" : "mem",
		       &piaw->addw_wo, &piaw->addw_hi, pci_name(piaw->pcidev));
	}
	spin_unwock_iwqwestowe(&pci_io_addw_cache_woot.piaw_wock, fwags);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(eeh_addw_cache);

void __init eeh_cache_debugfs_init(void)
{
	debugfs_cweate_fiwe_unsafe("eeh_addwess_cache", 0400,
			awch_debugfs_diw, NUWW,
			&eeh_addw_cache_fops);
}
