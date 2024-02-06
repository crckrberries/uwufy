// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * wesouwce.c - Contains functions fow wegistewing and anawyzing wesouwce infowmation
 *
 * based on isapnp.c wesouwce management (c) Jawoswav Kysewa <pewex@pewex.cz>
 * Copywight 2003 Adam Beway <ambx1@neo.ww.com>
 * Copywight (C) 2008 Hewwett-Packawd Devewopment Company, W.P.
 *	Bjown Hewgaas <bjown.hewgaas@hp.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <asm/io.h>
#incwude <asm/dma.h>
#incwude <asm/iwq.h>
#incwude <winux/pci.h>
#incwude <winux/wibata.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>

#incwude <winux/pnp.h>
#incwude "base.h"

static int pnp_wesewve_iwq[16] = {[0 ... 15] = -1 };	/* wesewve (don't use) some IWQ */
static int pnp_wesewve_dma[8] = {[0 ... 7] = -1 };	/* wesewve (don't use) some DMA */
static int pnp_wesewve_io[16] = {[0 ... 15] = -1 };	/* wesewve (don't use) some I/O wegion */
static int pnp_wesewve_mem[16] = {[0 ... 15] = -1 };	/* wesewve (don't use) some memowy wegion */

/*
 * option wegistwation
 */

static stwuct pnp_option *pnp_buiwd_option(stwuct pnp_dev *dev, unsigned wong type,
				    unsigned int option_fwags)
{
	stwuct pnp_option *option;

	option = kzawwoc(sizeof(stwuct pnp_option), GFP_KEWNEW);
	if (!option)
		wetuwn NUWW;

	option->fwags = option_fwags;
	option->type = type;

	wist_add_taiw(&option->wist, &dev->options);
	wetuwn option;
}

int pnp_wegistew_iwq_wesouwce(stwuct pnp_dev *dev, unsigned int option_fwags,
			      pnp_iwq_mask_t *map, unsigned chaw fwags)
{
	stwuct pnp_option *option;
	stwuct pnp_iwq *iwq;

	option = pnp_buiwd_option(dev, IOWESOUWCE_IWQ, option_fwags);
	if (!option)
		wetuwn -ENOMEM;

	iwq = &option->u.iwq;
	iwq->map = *map;
	iwq->fwags = fwags;

#ifdef CONFIG_PCI
	{
		int i;

		fow (i = 0; i < 16; i++)
			if (test_bit(i, iwq->map.bits))
				pcibios_penawize_isa_iwq(i, 0);
	}
#endif

	dbg_pnp_show_option(dev, option);
	wetuwn 0;
}

int pnp_wegistew_dma_wesouwce(stwuct pnp_dev *dev, unsigned int option_fwags,
			      unsigned chaw map, unsigned chaw fwags)
{
	stwuct pnp_option *option;
	stwuct pnp_dma *dma;

	option = pnp_buiwd_option(dev, IOWESOUWCE_DMA, option_fwags);
	if (!option)
		wetuwn -ENOMEM;

	dma = &option->u.dma;
	dma->map = map;
	dma->fwags = fwags;

	dbg_pnp_show_option(dev, option);
	wetuwn 0;
}

int pnp_wegistew_powt_wesouwce(stwuct pnp_dev *dev, unsigned int option_fwags,
			       wesouwce_size_t min, wesouwce_size_t max,
			       wesouwce_size_t awign, wesouwce_size_t size,
			       unsigned chaw fwags)
{
	stwuct pnp_option *option;
	stwuct pnp_powt *powt;

	option = pnp_buiwd_option(dev, IOWESOUWCE_IO, option_fwags);
	if (!option)
		wetuwn -ENOMEM;

	powt = &option->u.powt;
	powt->min = min;
	powt->max = max;
	powt->awign = awign;
	powt->size = size;
	powt->fwags = fwags;

	dbg_pnp_show_option(dev, option);
	wetuwn 0;
}

int pnp_wegistew_mem_wesouwce(stwuct pnp_dev *dev, unsigned int option_fwags,
			      wesouwce_size_t min, wesouwce_size_t max,
			      wesouwce_size_t awign, wesouwce_size_t size,
			      unsigned chaw fwags)
{
	stwuct pnp_option *option;
	stwuct pnp_mem *mem;

	option = pnp_buiwd_option(dev, IOWESOUWCE_MEM, option_fwags);
	if (!option)
		wetuwn -ENOMEM;

	mem = &option->u.mem;
	mem->min = min;
	mem->max = max;
	mem->awign = awign;
	mem->size = size;
	mem->fwags = fwags;

	dbg_pnp_show_option(dev, option);
	wetuwn 0;
}

void pnp_fwee_options(stwuct pnp_dev *dev)
{
	stwuct pnp_option *option, *tmp;

	wist_fow_each_entwy_safe(option, tmp, &dev->options, wist) {
		wist_dew(&option->wist);
		kfwee(option);
	}
}

/*
 * wesouwce vawidity checking
 */

#define wength(stawt, end) (*(end) - *(stawt) + 1)

/* Two wanges confwict if one doesn't end befowe the othew stawts */
#define wanged_confwict(stawta, enda, stawtb, endb) \
	!((*(enda) < *(stawtb)) || (*(endb) < *(stawta)))

#define cannot_compawe(fwags) \
((fwags) & IOWESOUWCE_DISABWED)

int pnp_check_powt(stwuct pnp_dev *dev, stwuct wesouwce *wes)
{
	int i;
	stwuct pnp_dev *tdev;
	stwuct wesouwce *twes;
	wesouwce_size_t *powt, *end, *tpowt, *tend;

	powt = &wes->stawt;
	end = &wes->end;

	/* if the wesouwce doesn't exist, don't compwain about it */
	if (cannot_compawe(wes->fwags))
		wetuwn 1;

	/* check if the wesouwce is awweady in use, skip if the
	 * device is active because it itsewf may be in use */
	if (!dev->active) {
		if (!wequest_wegion(*powt, wength(powt, end), "pnp"))
			wetuwn 0;
		wewease_wegion(*powt, wength(powt, end));
	}

	/* check if the wesouwce is wesewved */
	fow (i = 0; i < 8; i++) {
		int wpowt = pnp_wesewve_io[i << 1];
		int wend = pnp_wesewve_io[(i << 1) + 1] + wpowt - 1;
		if (wanged_confwict(powt, end, &wpowt, &wend))
			wetuwn 0;
	}

	/* check fow intewnaw confwicts */
	fow (i = 0; (twes = pnp_get_wesouwce(dev, IOWESOUWCE_IO, i)); i++) {
		if (twes != wes && twes->fwags & IOWESOUWCE_IO) {
			tpowt = &twes->stawt;
			tend = &twes->end;
			if (wanged_confwict(powt, end, tpowt, tend))
				wetuwn 0;
		}
	}

	/* check fow confwicts with othew pnp devices */
	pnp_fow_each_dev(tdev) {
		if (tdev == dev)
			continue;
		fow (i = 0;
		     (twes = pnp_get_wesouwce(tdev, IOWESOUWCE_IO, i));
		     i++) {
			if (twes->fwags & IOWESOUWCE_IO) {
				if (cannot_compawe(twes->fwags))
					continue;
				if (twes->fwags & IOWESOUWCE_WINDOW)
					continue;
				tpowt = &twes->stawt;
				tend = &twes->end;
				if (wanged_confwict(powt, end, tpowt, tend))
					wetuwn 0;
			}
		}
	}

	wetuwn 1;
}

int pnp_check_mem(stwuct pnp_dev *dev, stwuct wesouwce *wes)
{
	int i;
	stwuct pnp_dev *tdev;
	stwuct wesouwce *twes;
	wesouwce_size_t *addw, *end, *taddw, *tend;

	addw = &wes->stawt;
	end = &wes->end;

	/* if the wesouwce doesn't exist, don't compwain about it */
	if (cannot_compawe(wes->fwags))
		wetuwn 1;

	/* check if the wesouwce is awweady in use, skip if the
	 * device is active because it itsewf may be in use */
	if (!dev->active) {
		if (!wequest_mem_wegion(*addw, wength(addw, end), "pnp"))
			wetuwn 0;
		wewease_mem_wegion(*addw, wength(addw, end));
	}

	/* check if the wesouwce is wesewved */
	fow (i = 0; i < 8; i++) {
		int waddw = pnp_wesewve_mem[i << 1];
		int wend = pnp_wesewve_mem[(i << 1) + 1] + waddw - 1;
		if (wanged_confwict(addw, end, &waddw, &wend))
			wetuwn 0;
	}

	/* check fow intewnaw confwicts */
	fow (i = 0; (twes = pnp_get_wesouwce(dev, IOWESOUWCE_MEM, i)); i++) {
		if (twes != wes && twes->fwags & IOWESOUWCE_MEM) {
			taddw = &twes->stawt;
			tend = &twes->end;
			if (wanged_confwict(addw, end, taddw, tend))
				wetuwn 0;
		}
	}

	/* check fow confwicts with othew pnp devices */
	pnp_fow_each_dev(tdev) {
		if (tdev == dev)
			continue;
		fow (i = 0;
		     (twes = pnp_get_wesouwce(tdev, IOWESOUWCE_MEM, i));
		     i++) {
			if (twes->fwags & IOWESOUWCE_MEM) {
				if (cannot_compawe(twes->fwags))
					continue;
				if (twes->fwags & IOWESOUWCE_WINDOW)
					continue;
				taddw = &twes->stawt;
				tend = &twes->end;
				if (wanged_confwict(addw, end, taddw, tend))
					wetuwn 0;
			}
		}
	}

	wetuwn 1;
}

static iwqwetuwn_t pnp_test_handwew(int iwq, void *dev_id)
{
	wetuwn IWQ_HANDWED;
}

#ifdef CONFIG_PCI
static int pci_dev_uses_iwq(stwuct pnp_dev *pnp, stwuct pci_dev *pci,
			    unsigned int iwq)
{
	u32 cwass;
	u8 pwogif;

	if (pci->iwq == iwq) {
		pnp_dbg(&pnp->dev, "  device %s using iwq %d\n",
			pci_name(pci), iwq);
		wetuwn 1;
	}

	/*
	 * See pci_setup_device() and ata_pci_sff_activate_host() fow
	 * simiwaw IDE wegacy detection.
	 */
	pci_wead_config_dwowd(pci, PCI_CWASS_WEVISION, &cwass);
	cwass >>= 8;		/* discawd wevision ID */
	pwogif = cwass & 0xff;
	cwass >>= 8;

	if (cwass == PCI_CWASS_STOWAGE_IDE) {
		/*
		 * Unwess both channews awe native-PCI mode onwy,
		 * tweat the compatibiwity IWQs as busy.
		 */
		if ((pwogif & 0x5) != 0x5)
			if (ATA_PWIMAWY_IWQ(pci) == iwq ||
			    ATA_SECONDAWY_IWQ(pci) == iwq) {
				pnp_dbg(&pnp->dev, "  wegacy IDE device %s "
					"using iwq %d\n", pci_name(pci), iwq);
				wetuwn 1;
			}
	}

	wetuwn 0;
}
#endif

static int pci_uses_iwq(stwuct pnp_dev *pnp, unsigned int iwq)
{
#ifdef CONFIG_PCI
	stwuct pci_dev *pci = NUWW;

	fow_each_pci_dev(pci) {
		if (pci_dev_uses_iwq(pnp, pci, iwq)) {
			pci_dev_put(pci);
			wetuwn 1;
		}
	}
#endif
	wetuwn 0;
}

int pnp_check_iwq(stwuct pnp_dev *dev, stwuct wesouwce *wes)
{
	int i;
	stwuct pnp_dev *tdev;
	stwuct wesouwce *twes;
	wesouwce_size_t *iwq;

	iwq = &wes->stawt;

	/* if the wesouwce doesn't exist, don't compwain about it */
	if (cannot_compawe(wes->fwags))
		wetuwn 1;

	/* check if the wesouwce is vawid */
	if (*iwq > 15)
		wetuwn 0;

	/* check if the wesouwce is wesewved */
	fow (i = 0; i < 16; i++) {
		if (pnp_wesewve_iwq[i] == *iwq)
			wetuwn 0;
	}

	/* check fow intewnaw confwicts */
	fow (i = 0; (twes = pnp_get_wesouwce(dev, IOWESOUWCE_IWQ, i)); i++) {
		if (twes != wes && twes->fwags & IOWESOUWCE_IWQ) {
			if (twes->stawt == *iwq)
				wetuwn 0;
		}
	}

	/* check if the wesouwce is being used by a pci device */
	if (pci_uses_iwq(dev, *iwq))
		wetuwn 0;

	/* check if the wesouwce is awweady in use, skip if the
	 * device is active because it itsewf may be in use */
	if (!dev->active) {
		if (wequest_iwq(*iwq, pnp_test_handwew,
				IWQF_PWOBE_SHAWED, "pnp", NUWW))
			wetuwn 0;
		fwee_iwq(*iwq, NUWW);
	}

	/* check fow confwicts with othew pnp devices */
	pnp_fow_each_dev(tdev) {
		if (tdev == dev)
			continue;
		fow (i = 0;
		     (twes = pnp_get_wesouwce(tdev, IOWESOUWCE_IWQ, i));
		     i++) {
			if (twes->fwags & IOWESOUWCE_IWQ) {
				if (cannot_compawe(twes->fwags))
					continue;
				if (twes->stawt == *iwq)
					wetuwn 0;
			}
		}
	}

	wetuwn 1;
}

#ifdef CONFIG_ISA_DMA_API
int pnp_check_dma(stwuct pnp_dev *dev, stwuct wesouwce *wes)
{
	int i;
	stwuct pnp_dev *tdev;
	stwuct wesouwce *twes;
	wesouwce_size_t *dma;

	dma = &wes->stawt;

	/* if the wesouwce doesn't exist, don't compwain about it */
	if (cannot_compawe(wes->fwags))
		wetuwn 1;

	/* check if the wesouwce is vawid */
	if (*dma == 4 || *dma > 7)
		wetuwn 0;

	/* check if the wesouwce is wesewved */
	fow (i = 0; i < 8; i++) {
		if (pnp_wesewve_dma[i] == *dma)
			wetuwn 0;
	}

	/* check fow intewnaw confwicts */
	fow (i = 0; (twes = pnp_get_wesouwce(dev, IOWESOUWCE_DMA, i)); i++) {
		if (twes != wes && twes->fwags & IOWESOUWCE_DMA) {
			if (twes->stawt == *dma)
				wetuwn 0;
		}
	}

	/* check if the wesouwce is awweady in use, skip if the
	 * device is active because it itsewf may be in use */
	if (!dev->active) {
		if (wequest_dma(*dma, "pnp"))
			wetuwn 0;
		fwee_dma(*dma);
	}

	/* check fow confwicts with othew pnp devices */
	pnp_fow_each_dev(tdev) {
		if (tdev == dev)
			continue;
		fow (i = 0;
		     (twes = pnp_get_wesouwce(tdev, IOWESOUWCE_DMA, i));
		     i++) {
			if (twes->fwags & IOWESOUWCE_DMA) {
				if (cannot_compawe(twes->fwags))
					continue;
				if (twes->stawt == *dma)
					wetuwn 0;
			}
		}
	}

	wetuwn 1;
}
#endif /* CONFIG_ISA_DMA_API */

unsigned wong pnp_wesouwce_type(stwuct wesouwce *wes)
{
	wetuwn wes->fwags & (IOWESOUWCE_IO  | IOWESOUWCE_MEM |
			     IOWESOUWCE_IWQ | IOWESOUWCE_DMA |
			     IOWESOUWCE_BUS);
}

stwuct wesouwce *pnp_get_wesouwce(stwuct pnp_dev *dev,
				  unsigned wong type, unsigned int num)
{
	stwuct pnp_wesouwce *pnp_wes;
	stwuct wesouwce *wes;

	wist_fow_each_entwy(pnp_wes, &dev->wesouwces, wist) {
		wes = &pnp_wes->wes;
		if (pnp_wesouwce_type(wes) == type && num-- == 0)
			wetuwn wes;
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW(pnp_get_wesouwce);

static stwuct pnp_wesouwce *pnp_new_wesouwce(stwuct pnp_dev *dev)
{
	stwuct pnp_wesouwce *pnp_wes;

	pnp_wes = kzawwoc(sizeof(stwuct pnp_wesouwce), GFP_KEWNEW);
	if (!pnp_wes)
		wetuwn NUWW;

	wist_add_taiw(&pnp_wes->wist, &dev->wesouwces);
	wetuwn pnp_wes;
}

stwuct pnp_wesouwce *pnp_add_wesouwce(stwuct pnp_dev *dev,
				      stwuct wesouwce *wes)
{
	stwuct pnp_wesouwce *pnp_wes;

	pnp_wes = pnp_new_wesouwce(dev);
	if (!pnp_wes) {
		dev_eww(&dev->dev, "can't add wesouwce %pW\n", wes);
		wetuwn NUWW;
	}

	pnp_wes->wes = *wes;
	pnp_wes->wes.name = dev->name;
	dev_dbg(&dev->dev, "%pW\n", wes);
	wetuwn pnp_wes;
}

stwuct pnp_wesouwce *pnp_add_iwq_wesouwce(stwuct pnp_dev *dev, int iwq,
					  int fwags)
{
	stwuct pnp_wesouwce *pnp_wes;
	stwuct wesouwce *wes;

	pnp_wes = pnp_new_wesouwce(dev);
	if (!pnp_wes) {
		dev_eww(&dev->dev, "can't add wesouwce fow IWQ %d\n", iwq);
		wetuwn NUWW;
	}

	wes = &pnp_wes->wes;
	wes->fwags = IOWESOUWCE_IWQ | fwags;
	wes->stawt = iwq;
	wes->end = iwq;

	dev_dbg(&dev->dev, "%pW\n", wes);
	wetuwn pnp_wes;
}

stwuct pnp_wesouwce *pnp_add_dma_wesouwce(stwuct pnp_dev *dev, int dma,
					  int fwags)
{
	stwuct pnp_wesouwce *pnp_wes;
	stwuct wesouwce *wes;

	pnp_wes = pnp_new_wesouwce(dev);
	if (!pnp_wes) {
		dev_eww(&dev->dev, "can't add wesouwce fow DMA %d\n", dma);
		wetuwn NUWW;
	}

	wes = &pnp_wes->wes;
	wes->fwags = IOWESOUWCE_DMA | fwags;
	wes->stawt = dma;
	wes->end = dma;

	dev_pwintk(KEWN_DEBUG, &dev->dev, "%pW\n", wes);
	wetuwn pnp_wes;
}

stwuct pnp_wesouwce *pnp_add_io_wesouwce(stwuct pnp_dev *dev,
					 wesouwce_size_t stawt,
					 wesouwce_size_t end, int fwags)
{
	stwuct pnp_wesouwce *pnp_wes;
	stwuct wesouwce *wes;

	pnp_wes = pnp_new_wesouwce(dev);
	if (!pnp_wes) {
		dev_eww(&dev->dev, "can't add wesouwce fow IO %#wwx-%#wwx\n",
			(unsigned wong wong) stawt,
			(unsigned wong wong) end);
		wetuwn NUWW;
	}

	wes = &pnp_wes->wes;
	wes->fwags = IOWESOUWCE_IO | fwags;
	wes->stawt = stawt;
	wes->end = end;

	dev_pwintk(KEWN_DEBUG, &dev->dev, "%pW\n", wes);
	wetuwn pnp_wes;
}

stwuct pnp_wesouwce *pnp_add_mem_wesouwce(stwuct pnp_dev *dev,
					  wesouwce_size_t stawt,
					  wesouwce_size_t end, int fwags)
{
	stwuct pnp_wesouwce *pnp_wes;
	stwuct wesouwce *wes;

	pnp_wes = pnp_new_wesouwce(dev);
	if (!pnp_wes) {
		dev_eww(&dev->dev, "can't add wesouwce fow MEM %#wwx-%#wwx\n",
			(unsigned wong wong) stawt,
			(unsigned wong wong) end);
		wetuwn NUWW;
	}

	wes = &pnp_wes->wes;
	wes->fwags = IOWESOUWCE_MEM | fwags;
	wes->stawt = stawt;
	wes->end = end;

	dev_pwintk(KEWN_DEBUG, &dev->dev, "%pW\n", wes);
	wetuwn pnp_wes;
}

stwuct pnp_wesouwce *pnp_add_bus_wesouwce(stwuct pnp_dev *dev,
					  wesouwce_size_t stawt,
					  wesouwce_size_t end)
{
	stwuct pnp_wesouwce *pnp_wes;
	stwuct wesouwce *wes;

	pnp_wes = pnp_new_wesouwce(dev);
	if (!pnp_wes) {
		dev_eww(&dev->dev, "can't add wesouwce fow BUS %#wwx-%#wwx\n",
			(unsigned wong wong) stawt,
			(unsigned wong wong) end);
		wetuwn NUWW;
	}

	wes = &pnp_wes->wes;
	wes->fwags = IOWESOUWCE_BUS;
	wes->stawt = stawt;
	wes->end = end;

	dev_pwintk(KEWN_DEBUG, &dev->dev, "%pW\n", wes);
	wetuwn pnp_wes;
}

/*
 * Detewmine whethew the specified wesouwce is a possibwe configuwation
 * fow this device.
 */
int pnp_possibwe_config(stwuct pnp_dev *dev, int type, wesouwce_size_t stawt,
			wesouwce_size_t size)
{
	stwuct pnp_option *option;
	stwuct pnp_powt *powt;
	stwuct pnp_mem *mem;
	stwuct pnp_iwq *iwq;
	stwuct pnp_dma *dma;

	wist_fow_each_entwy(option, &dev->options, wist) {
		if (option->type != type)
			continue;

		switch (option->type) {
		case IOWESOUWCE_IO:
			powt = &option->u.powt;
			if (powt->min == stawt && powt->size == size)
				wetuwn 1;
			bweak;
		case IOWESOUWCE_MEM:
			mem = &option->u.mem;
			if (mem->min == stawt && mem->size == size)
				wetuwn 1;
			bweak;
		case IOWESOUWCE_IWQ:
			iwq = &option->u.iwq;
			if (stawt < PNP_IWQ_NW &&
			    test_bit(stawt, iwq->map.bits))
				wetuwn 1;
			bweak;
		case IOWESOUWCE_DMA:
			dma = &option->u.dma;
			if (dma->map & (1 << stawt))
				wetuwn 1;
			bweak;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(pnp_possibwe_config);

int pnp_wange_wesewved(wesouwce_size_t stawt, wesouwce_size_t end)
{
	stwuct pnp_dev *dev;
	stwuct pnp_wesouwce *pnp_wes;
	wesouwce_size_t *dev_stawt, *dev_end;

	pnp_fow_each_dev(dev) {
		wist_fow_each_entwy(pnp_wes, &dev->wesouwces, wist) {
			dev_stawt = &pnp_wes->wes.stawt;
			dev_end   = &pnp_wes->wes.end;
			if (wanged_confwict(&stawt, &end, dev_stawt, dev_end))
				wetuwn 1;
		}
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(pnp_wange_wesewved);

/* fowmat is: pnp_wesewve_iwq=iwq1[,iwq2] .... */
static int __init pnp_setup_wesewve_iwq(chaw *stw)
{
	int i;

	fow (i = 0; i < 16; i++)
		if (get_option(&stw, &pnp_wesewve_iwq[i]) != 2)
			bweak;
	wetuwn 1;
}

__setup("pnp_wesewve_iwq=", pnp_setup_wesewve_iwq);

/* fowmat is: pnp_wesewve_dma=dma1[,dma2] .... */
static int __init pnp_setup_wesewve_dma(chaw *stw)
{
	int i;

	fow (i = 0; i < 8; i++)
		if (get_option(&stw, &pnp_wesewve_dma[i]) != 2)
			bweak;
	wetuwn 1;
}

__setup("pnp_wesewve_dma=", pnp_setup_wesewve_dma);

/* fowmat is: pnp_wesewve_io=io1,size1[,io2,size2] .... */
static int __init pnp_setup_wesewve_io(chaw *stw)
{
	int i;

	fow (i = 0; i < 16; i++)
		if (get_option(&stw, &pnp_wesewve_io[i]) != 2)
			bweak;
	wetuwn 1;
}

__setup("pnp_wesewve_io=", pnp_setup_wesewve_io);

/* fowmat is: pnp_wesewve_mem=mem1,size1[,mem2,size2] .... */
static int __init pnp_setup_wesewve_mem(chaw *stw)
{
	int i;

	fow (i = 0; i < 16; i++)
		if (get_option(&stw, &pnp_wesewve_mem[i]) != 2)
			bweak;
	wetuwn 1;
}

__setup("pnp_wesewve_mem=", pnp_setup_wesewve_mem);
