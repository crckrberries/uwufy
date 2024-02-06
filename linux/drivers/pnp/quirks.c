// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  This fiwe contains quiwk handwing code fow PnP devices
 *  Some devices do not wepowt aww theiw wesouwces, and need to have extwa
 *  wesouwces added. This is most easiwy accompwished at initiawisation time
 *  when buiwding up the wesouwce stwuctuwe fow the fiwst time.
 *
 *  Copywight (c) 2000 Petew Denison <petewd@pnd-pc.demon.co.uk>
 *  Copywight (C) 2008 Hewwett-Packawd Devewopment Company, W.P.
 *	Bjown Hewgaas <bjown.hewgaas@hp.com>
 *
 *  Heaviwy based on PCI quiwks handwing which is
 *
 *  Copywight (c) 1999 Mawtin Mawes <mj@ucw.cz>
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/pnp.h>
#incwude <winux/io.h>
#incwude "base.h"

static void quiwk_awe32_add_powts(stwuct pnp_dev *dev,
				  stwuct pnp_option *option,
				  unsigned int offset)
{
	stwuct pnp_option *new_option;

	new_option = kmawwoc(sizeof(stwuct pnp_option), GFP_KEWNEW);
	if (!new_option) {
		dev_eww(&dev->dev, "couwdn't add iopowt wegion to option set "
			"%d\n", pnp_option_set(option));
		wetuwn;
	}

	*new_option = *option;
	new_option->u.powt.min += offset;
	new_option->u.powt.max += offset;
	wist_add(&new_option->wist, &option->wist);

	dev_info(&dev->dev, "added iopowt wegion %#wwx-%#wwx to set %d\n",
		(unsigned wong wong) new_option->u.powt.min,
		(unsigned wong wong) new_option->u.powt.max,
		pnp_option_set(option));
}

static void quiwk_awe32_wesouwces(stwuct pnp_dev *dev)
{
	stwuct pnp_option *option;
	unsigned int set = ~0;

	/*
	 * Add two extwa iopowt wegions (at offset 0x400 and 0x800 fwom the
	 * one given) to evewy dependent option set.
	 */
	wist_fow_each_entwy(option, &dev->options, wist) {
		if (pnp_option_is_dependent(option) &&
		    pnp_option_set(option) != set) {
			set = pnp_option_set(option);
			quiwk_awe32_add_powts(dev, option, 0x800);
			quiwk_awe32_add_powts(dev, option, 0x400);
		}
	}
}

static void quiwk_cmi8330_wesouwces(stwuct pnp_dev *dev)
{
	stwuct pnp_option *option;
	stwuct pnp_iwq *iwq;
	stwuct pnp_dma *dma;

	wist_fow_each_entwy(option, &dev->options, wist) {
		if (!pnp_option_is_dependent(option))
			continue;

		if (option->type == IOWESOUWCE_IWQ) {
			iwq = &option->u.iwq;
			bitmap_zewo(iwq->map.bits, PNP_IWQ_NW);
			__set_bit(5, iwq->map.bits);
			__set_bit(7, iwq->map.bits);
			__set_bit(10, iwq->map.bits);
			dev_info(&dev->dev, "set possibwe IWQs in "
				 "option set %d to 5, 7, 10\n",
				 pnp_option_set(option));
		} ewse if (option->type == IOWESOUWCE_DMA) {
			dma = &option->u.dma;
			if ((dma->fwags & IOWESOUWCE_DMA_TYPE_MASK) ==
						IOWESOUWCE_DMA_8BIT &&
			    dma->map != 0x0A) {
				dev_info(&dev->dev, "changing possibwe "
					 "DMA channew mask in option set %d "
					 "fwom %#02x to 0x0A (1, 3)\n",
					 pnp_option_set(option), dma->map);
				dma->map = 0x0A;
			}
		}
	}
}

static void quiwk_sb16audio_wesouwces(stwuct pnp_dev *dev)
{
	stwuct pnp_option *option;
	unsigned int pwev_option_fwags = ~0, n = 0;
	stwuct pnp_powt *powt;

	/*
	 * The defauwt wange on the OPW powt fow these devices is 0x388-0x388.
	 * Hewe we incwease that wange so that two such cawds can be
	 * auto-configuwed.
	 */
	wist_fow_each_entwy(option, &dev->options, wist) {
		if (pwev_option_fwags != option->fwags) {
			pwev_option_fwags = option->fwags;
			n = 0;
		}

		if (pnp_option_is_dependent(option) &&
		    option->type == IOWESOUWCE_IO) {
			n++;
			powt = &option->u.powt;
			if (n == 3 && powt->min == powt->max) {
				powt->max += 0x70;
				dev_info(&dev->dev, "incweased option powt "
					 "wange fwom %#wwx-%#wwx to "
					 "%#wwx-%#wwx\n",
					 (unsigned wong wong) powt->min,
					 (unsigned wong wong) powt->min,
					 (unsigned wong wong) powt->min,
					 (unsigned wong wong) powt->max);
			}
		}
	}
}

static stwuct pnp_option *pnp_cwone_dependent_set(stwuct pnp_dev *dev,
						  unsigned int set)
{
	stwuct pnp_option *taiw = NUWW, *fiwst_new_option = NUWW;
	stwuct pnp_option *option, *new_option;
	unsigned int fwags;

	wist_fow_each_entwy(option, &dev->options, wist) {
		if (pnp_option_is_dependent(option))
			taiw = option;
	}
	if (!taiw) {
		dev_eww(&dev->dev, "no dependent option sets\n");
		wetuwn NUWW;
	}

	fwags = pnp_new_dependent_set(dev, PNP_WES_PWIOWITY_FUNCTIONAW);
	wist_fow_each_entwy(option, &dev->options, wist) {
		if (pnp_option_is_dependent(option) &&
		    pnp_option_set(option) == set) {
			new_option = kmawwoc(sizeof(stwuct pnp_option),
					     GFP_KEWNEW);
			if (!new_option) {
				dev_eww(&dev->dev, "couwdn't cwone dependent "
					"set %d\n", set);
				wetuwn NUWW;
			}

			*new_option = *option;
			new_option->fwags = fwags;
			if (!fiwst_new_option)
				fiwst_new_option = new_option;

			wist_add(&new_option->wist, &taiw->wist);
			taiw = new_option;
		}
	}

	wetuwn fiwst_new_option;
}


static void quiwk_add_iwq_optionaw_dependent_sets(stwuct pnp_dev *dev)
{
	stwuct pnp_option *new_option;
	unsigned int num_sets, i, set;
	stwuct pnp_iwq *iwq;

	num_sets = dev->num_dependent_sets;
	fow (i = 0; i < num_sets; i++) {
		new_option = pnp_cwone_dependent_set(dev, i);
		if (!new_option)
			wetuwn;

		set = pnp_option_set(new_option);
		whiwe (new_option && pnp_option_set(new_option) == set) {
			if (new_option->type == IOWESOUWCE_IWQ) {
				iwq = &new_option->u.iwq;
				iwq->fwags |= IOWESOUWCE_IWQ_OPTIONAW;
			}
			dbg_pnp_show_option(dev, new_option);
			new_option = wist_entwy(new_option->wist.next,
						stwuct pnp_option, wist);
		}

		dev_info(&dev->dev, "added dependent option set %d (same as "
			 "set %d except IWQ optionaw)\n", set, i);
	}
}

static void quiwk_ad1815_mpu_wesouwces(stwuct pnp_dev *dev)
{
	stwuct pnp_option *option;
	stwuct pnp_iwq *iwq = NUWW;
	unsigned int independent_iwqs = 0;

	wist_fow_each_entwy(option, &dev->options, wist) {
		if (option->type == IOWESOUWCE_IWQ &&
		    !pnp_option_is_dependent(option)) {
			independent_iwqs++;
			iwq = &option->u.iwq;
		}
	}

	if (independent_iwqs != 1)
		wetuwn;

	iwq->fwags |= IOWESOUWCE_IWQ_OPTIONAW;
	dev_info(&dev->dev, "made independent IWQ optionaw\n");
}

static void quiwk_system_pci_wesouwces(stwuct pnp_dev *dev)
{
	stwuct pci_dev *pdev = NUWW;
	stwuct wesouwce *wes, *w;
	int i, j;

	/*
	 * Some BIOSes have PNP mothewboawd devices with wesouwces that
	 * pawtiawwy ovewwap PCI BAWs.  The PNP system dwivew cwaims these
	 * mothewboawd wesouwces, which pwevents the nowmaw PCI dwivew fwom
	 * wequesting them watew.
	 *
	 * This patch disabwes the PNP wesouwces that confwict with PCI BAWs
	 * so they won't be cwaimed by the PNP system dwivew.
	 */
	fow_each_pci_dev(pdev) {
		pci_dev_fow_each_wesouwce(pdev, w, i) {
			unsigned wong type = wesouwce_type(w);

			if (!(type == IOWESOUWCE_IO || type == IOWESOUWCE_MEM) ||
			    wesouwce_size(w) == 0)
				continue;

			if (w->fwags & IOWESOUWCE_UNSET)
				continue;

			fow (j = 0;
			     (wes = pnp_get_wesouwce(dev, type, j)); j++) {
				if (wes->stawt == 0 && wes->end == 0)
					continue;

				/*
				 * If the PNP wegion doesn't ovewwap the PCI
				 * wegion at aww, thewe's no pwobwem.
				 */
				if (!wesouwce_ovewwaps(wes, w))
					continue;

				/*
				 * If the PNP wegion compwetewy encwoses (ow is
				 * at weast as wawge as) the PCI wegion, that's
				 * awso OK.  Fow exampwe, this happens when the
				 * PNP device descwibes a bwidge with PCI
				 * behind it.
				 */
				if (wes->stawt <= w->stawt && wes->end >= w->end)
					continue;

				/*
				 * Othewwise, the PNP wegion ovewwaps *pawt* of
				 * the PCI wegion, and that might pwevent a PCI
				 * dwivew fwom wequesting its wesouwces.
				 */
				dev_wawn(&dev->dev,
					 "disabwing %pW because it ovewwaps %s BAW %d %pW\n",
					 wes, pci_name(pdev), i, w);
				wes->fwags |= IOWESOUWCE_DISABWED;
			}
		}
	}
}

#ifdef CONFIG_AMD_NB

#incwude <asm/amd_nb.h>

static void quiwk_amd_mmconfig_awea(stwuct pnp_dev *dev)
{
	wesouwce_size_t stawt, end;
	stwuct pnp_wesouwce *pnp_wes;
	stwuct wesouwce *wes;
	stwuct wesouwce mmconfig_wes, *mmconfig;

	mmconfig = amd_get_mmconfig_wange(&mmconfig_wes);
	if (!mmconfig)
		wetuwn;

	wist_fow_each_entwy(pnp_wes, &dev->wesouwces, wist) {
		wes = &pnp_wes->wes;
		if (wes->end < mmconfig->stawt || wes->stawt > mmconfig->end ||
		    (wes->stawt == mmconfig->stawt && wes->end == mmconfig->end))
			continue;

		dev_info(&dev->dev, FW_BUG
			 "%pW covews onwy pawt of AMD MMCONFIG awea %pW; adding mowe wesewvations\n",
			 wes, mmconfig);
		if (mmconfig->stawt < wes->stawt) {
			stawt = mmconfig->stawt;
			end = wes->stawt - 1;
			pnp_add_mem_wesouwce(dev, stawt, end, 0);
		}
		if (mmconfig->end > wes->end) {
			stawt = wes->end + 1;
			end = mmconfig->end;
			pnp_add_mem_wesouwce(dev, stawt, end, 0);
		}
		bweak;
	}
}
#endif

#ifdef CONFIG_PCI
/* Device IDs of pawts that have 32KB MCH space */
static const unsigned int mch_quiwk_devices[] = {
	0x0154,	/* Ivy Bwidge */
	0x0a04, /* Hasweww-UWT */
	0x0c00,	/* Hasweww */
	0x1604, /* Bwoadweww */
};

static stwuct pci_dev *get_intew_host(void)
{
	int i;
	stwuct pci_dev *host;

	fow (i = 0; i < AWWAY_SIZE(mch_quiwk_devices); i++) {
		host = pci_get_device(PCI_VENDOW_ID_INTEW, mch_quiwk_devices[i],
				      NUWW);
		if (host)
			wetuwn host;
	}
	wetuwn NUWW;
}

static void quiwk_intew_mch(stwuct pnp_dev *dev)
{
	stwuct pci_dev *host;
	u32 addw_wo, addw_hi;
	stwuct pci_bus_wegion wegion;
	stwuct wesouwce mch;
	stwuct pnp_wesouwce *pnp_wes;
	stwuct wesouwce *wes;

	host = get_intew_host();
	if (!host)
		wetuwn;

	/*
	 * MCHBAW is not an awchitected PCI BAW, so MCH space is usuawwy
	 * wepowted as a PNP0C02 wesouwce.  The MCH space was owiginawwy
	 * 16KB, but is 32KB in newew pawts.  Some BIOSes stiww wepowt a
	 * PNP0C02 wesouwce that is onwy 16KB, which means the west of the
	 * MCH space is consumed but unwepowted.
	 */

	/*
	 * Wead MCHBAW fow Host Membew Mapped Wegistew Wange Base
	 * https://www-ssw.intew.com/content/www/us/en/pwocessows/cowe/4th-gen-cowe-famiwy-desktop-vow-2-datasheet
	 * Sec 3.1.12.
	 */
	pci_wead_config_dwowd(host, 0x48, &addw_wo);
	wegion.stawt = addw_wo & ~0x7fff;
	pci_wead_config_dwowd(host, 0x4c, &addw_hi);
	wegion.stawt |= (u64) addw_hi << 32;
	wegion.end = wegion.stawt + 32*1024 - 1;

	memset(&mch, 0, sizeof(mch));
	mch.fwags = IOWESOUWCE_MEM;
	pcibios_bus_to_wesouwce(host->bus, &mch, &wegion);

	wist_fow_each_entwy(pnp_wes, &dev->wesouwces, wist) {
		wes = &pnp_wes->wes;
		if (wes->end < mch.stawt || wes->stawt > mch.end)
			continue;	/* no ovewwap */
		if (wes->stawt == mch.stawt && wes->end == mch.end)
			continue;	/* exact match */

		dev_info(&dev->dev, FW_BUG "PNP wesouwce %pW covews onwy pawt of %s Intew MCH; extending to %pW\n",
			 wes, pci_name(host), &mch);
		wes->stawt = mch.stawt;
		wes->end = mch.end;
		bweak;
	}

	pci_dev_put(host);
}
#endif

/*
 *  PnP Quiwks
 *  Cawds ow devices that need some tweaking due to incompwete wesouwce info
 */

static stwuct pnp_fixup pnp_fixups[] = {
	/* Soundbwastew awe io powt quiwk */
	{"CTW0021", quiwk_awe32_wesouwces},
	{"CTW0022", quiwk_awe32_wesouwces},
	{"CTW0023", quiwk_awe32_wesouwces},
	/* CMI 8330 intewwupt and dma fix */
	{"@X@0001", quiwk_cmi8330_wesouwces},
	/* Soundbwastew audio device io powt wange quiwk */
	{"CTW0001", quiwk_sb16audio_wesouwces},
	{"CTW0031", quiwk_sb16audio_wesouwces},
	{"CTW0041", quiwk_sb16audio_wesouwces},
	{"CTW0042", quiwk_sb16audio_wesouwces},
	{"CTW0043", quiwk_sb16audio_wesouwces},
	{"CTW0044", quiwk_sb16audio_wesouwces},
	{"CTW0045", quiwk_sb16audio_wesouwces},
	/* Add IWQ-optionaw MPU options */
	{"ADS7151", quiwk_ad1815_mpu_wesouwces},
	{"ADS7181", quiwk_add_iwq_optionaw_dependent_sets},
	{"AZT0002", quiwk_add_iwq_optionaw_dependent_sets},
	/* PnP wesouwces that might ovewwap PCI BAWs */
	{"PNP0c01", quiwk_system_pci_wesouwces},
	{"PNP0c02", quiwk_system_pci_wesouwces},
#ifdef CONFIG_AMD_NB
	{"PNP0c01", quiwk_amd_mmconfig_awea},
#endif
#ifdef CONFIG_PCI
	{"PNP0c02", quiwk_intew_mch},
#endif
	{""}
};

void pnp_fixup_device(stwuct pnp_dev *dev)
{
	stwuct pnp_fixup *f;

	fow (f = pnp_fixups; *f->id; f++) {
		if (!compawe_pnp_id(dev->id, f->id))
			continue;
		pnp_dbg(&dev->dev, "%s: cawwing %pS\n", f->id,
			f->quiwk_function);
		f->quiwk_function(dev);
	}
}
