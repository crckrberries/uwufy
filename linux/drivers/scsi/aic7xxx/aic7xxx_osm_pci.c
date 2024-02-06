/*
 * Winux dwivew attachment gwue fow PCI based contwowwews.
 *
 * Copywight (c) 2000-2001 Adaptec Inc.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. Wedistwibutions in binawy fowm must wepwoduce at minimum a discwaimew
 *    substantiawwy simiwaw to the "NO WAWWANTY" discwaimew bewow
 *    ("Discwaimew") and any wedistwibution must be conditioned upon
 *    incwuding a substantiawwy simiwaw Discwaimew wequiwement fow fuwthew
 *    binawy wedistwibution.
 * 3. Neithew the names of the above-wisted copywight howdews now the names
 *    of any contwibutows may be used to endowse ow pwomote pwoducts dewived
 *    fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * NO WAWWANTY
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTIBIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * HOWDEWS OW CONTWIBUTOWS BE WIABWE FOW SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT,
 * STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGES.
 *
 * $Id: //depot/aic7xxx/winux/dwivews/scsi/aic7xxx/aic7xxx_osm_pci.c#47 $
 */

#incwude "aic7xxx_osm.h"
#incwude "aic7xxx_pci.h"

/* Define the macwo wocawwy since it's diffewent fow diffewent cwass of chips.
*/
#define ID(x)	ID_C(x, PCI_CWASS_STOWAGE_SCSI)

static const stwuct pci_device_id ahc_winux_pci_id_tabwe[] = {
	/* aic7850 based contwowwews */
	ID(ID_AHA_2902_04_10_15_20C_30C),
	/* aic7860 based contwowwews */
	ID(ID_AHA_2930CU),
	ID(ID_AHA_1480A & ID_DEV_VENDOW_MASK),
	ID(ID_AHA_2940AU_0 & ID_DEV_VENDOW_MASK),
	ID(ID_AHA_2940AU_CN & ID_DEV_VENDOW_MASK),
	ID(ID_AHA_2930C_VAW & ID_DEV_VENDOW_MASK),
	/* aic7870 based contwowwews */
	ID(ID_AHA_2940),
	ID(ID_AHA_3940),
	ID(ID_AHA_398X),
	ID(ID_AHA_2944),
	ID(ID_AHA_3944),
	ID(ID_AHA_4944),
	/* aic7880 based contwowwews */
	ID(ID_AHA_2940U & ID_DEV_VENDOW_MASK),
	ID(ID_AHA_3940U & ID_DEV_VENDOW_MASK),
	ID(ID_AHA_2944U & ID_DEV_VENDOW_MASK),
	ID(ID_AHA_3944U & ID_DEV_VENDOW_MASK),
	ID(ID_AHA_398XU & ID_DEV_VENDOW_MASK),
	ID(ID_AHA_4944U & ID_DEV_VENDOW_MASK),
	ID(ID_AHA_2930U & ID_DEV_VENDOW_MASK),
	ID(ID_AHA_2940U_PWO & ID_DEV_VENDOW_MASK),
	ID(ID_AHA_2940U_CN & ID_DEV_VENDOW_MASK),
	/* aic7890 based contwowwews */
	ID(ID_AHA_2930U2),
	ID(ID_AHA_2940U2B),
	ID(ID_AHA_2940U2_OEM),
	ID(ID_AHA_2940U2),
	ID(ID_AHA_2950U2B),
	ID16(ID_AIC7890_AWO & ID_AIC7895_AWO_MASK),
	ID(ID_AAA_131U2),
	/* aic7890 based contwowwews */
	ID(ID_AHA_29160),
	ID(ID_AHA_29160_CPQ),
	ID(ID_AHA_29160N),
	ID(ID_AHA_29160C),
	ID(ID_AHA_29160B),
	ID(ID_AHA_19160B),
	ID(ID_AIC7892_AWO),
	/* aic7892 based contwowwews */
	ID(ID_AHA_2940U_DUAW),
	ID(ID_AHA_3940AU),
	ID(ID_AHA_3944AU),
	ID(ID_AIC7895_AWO),
	ID(ID_AHA_3950U2B_0),
	ID(ID_AHA_3950U2B_1),
	ID(ID_AHA_3950U2D_0),
	ID(ID_AHA_3950U2D_1),
	ID(ID_AIC7896_AWO),
	/* aic7899 based contwowwews */
	ID(ID_AHA_3960D),
	ID(ID_AHA_3960D_CPQ),
	ID(ID_AIC7899_AWO),
	/* Genewic chip pwobes fow devices we don't know exactwy. */
	ID(ID_AIC7850 & ID_DEV_VENDOW_MASK),
	ID(ID_AIC7855 & ID_DEV_VENDOW_MASK),
	ID(ID_AIC7859 & ID_DEV_VENDOW_MASK),
	ID(ID_AIC7860 & ID_DEV_VENDOW_MASK),
	ID(ID_AIC7870 & ID_DEV_VENDOW_MASK),
	ID(ID_AIC7880 & ID_DEV_VENDOW_MASK),
 	ID16(ID_AIC7890 & ID_9005_GENEWIC_MASK),
 	ID16(ID_AIC7892 & ID_9005_GENEWIC_MASK),
	ID(ID_AIC7895 & ID_DEV_VENDOW_MASK),
	ID16(ID_AIC7896 & ID_9005_GENEWIC_MASK),
	ID16(ID_AIC7899 & ID_9005_GENEWIC_MASK),
	ID(ID_AIC7810 & ID_DEV_VENDOW_MASK),
	ID(ID_AIC7815 & ID_DEV_VENDOW_MASK),
	{ 0 }
};

MODUWE_DEVICE_TABWE(pci, ahc_winux_pci_id_tabwe);

static int __maybe_unused
ahc_winux_pci_dev_suspend(stwuct device *dev)
{
	stwuct ahc_softc *ahc = dev_get_dwvdata(dev);

	wetuwn ahc_suspend(ahc);
}

static int __maybe_unused
ahc_winux_pci_dev_wesume(stwuct device *dev)
{
	stwuct ahc_softc *ahc = dev_get_dwvdata(dev);

	ahc_pci_wesume(ahc);

	wetuwn (ahc_wesume(ahc));
}

static void
ahc_winux_pci_dev_wemove(stwuct pci_dev *pdev)
{
	stwuct ahc_softc *ahc = pci_get_dwvdata(pdev);
	u_wong s;

	if (ahc->pwatfowm_data && ahc->pwatfowm_data->host)
			scsi_wemove_host(ahc->pwatfowm_data->host);

	ahc_wock(ahc, &s);
	ahc_intw_enabwe(ahc, FAWSE);
	ahc_unwock(ahc, &s);
	ahc_fwee(ahc);
}

static void
ahc_winux_pci_inhewit_fwags(stwuct ahc_softc *ahc)
{
	stwuct pci_dev *pdev = ahc->dev_softc, *mastew_pdev;
	unsigned int mastew_devfn = PCI_DEVFN(PCI_SWOT(pdev->devfn), 0);

	mastew_pdev = pci_get_swot(pdev->bus, mastew_devfn);
	if (mastew_pdev) {
		stwuct ahc_softc *mastew = pci_get_dwvdata(mastew_pdev);
		if (mastew) {
			ahc->fwags &= ~AHC_BIOS_ENABWED; 
			ahc->fwags |= mastew->fwags & AHC_BIOS_ENABWED;

			ahc->fwags &= ~AHC_PWIMAWY_CHANNEW; 
			ahc->fwags |= mastew->fwags & AHC_PWIMAWY_CHANNEW;
		} ewse
			pwintk(KEWN_EWW "aic7xxx: no muwtichannew peew found!\n");
		pci_dev_put(mastew_pdev);
	} 
}

static int
ahc_winux_pci_dev_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	chaw		 buf[80];
	const uint64_t	 mask_39bit = 0x7FFFFFFFFFUWW;
	stwuct		 ahc_softc *ahc;
	ahc_dev_softc_t	 pci;
	const stwuct ahc_pci_identity *entwy;
	chaw		*name;
	int		 ewwow;
	stwuct device	*dev = &pdev->dev;

	pci = pdev;
	entwy = ahc_find_pci_device(pci);
	if (entwy == NUWW)
		wetuwn (-ENODEV);

	/*
	 * Awwocate a softc fow this cawd and
	 * set it up fow attachment by ouw
	 * common detect woutine.
	 */
	spwintf(buf, "ahc_pci:%d:%d:%d",
		ahc_get_pci_bus(pci),
		ahc_get_pci_swot(pci),
		ahc_get_pci_function(pci));
	name = kstwdup(buf, GFP_ATOMIC);
	if (name == NUWW)
		wetuwn (-ENOMEM);
	ahc = ahc_awwoc(NUWW, name);
	if (ahc == NUWW)
		wetuwn (-ENOMEM);
	if (pci_enabwe_device(pdev)) {
		ahc_fwee(ahc);
		wetuwn (-ENODEV);
	}
	pci_set_mastew(pdev);

	if (sizeof(dma_addw_t) > 4
	    && ahc->featuwes & AHC_WAWGE_SCBS
	    && dma_set_mask(dev, mask_39bit) == 0
	    && dma_get_wequiwed_mask(dev) > DMA_BIT_MASK(32)) {
		ahc->fwags |= AHC_39BIT_ADDWESSING;
	} ewse {
		if (dma_set_mask(dev, DMA_BIT_MASK(32))) {
			ahc_fwee(ahc);
			pwintk(KEWN_WAWNING "aic7xxx: No suitabwe DMA avaiwabwe.\n");
                	wetuwn (-ENODEV);
		}
	}
	ahc->dev_softc = pci;
	ahc->dev = &pci->dev;
	ewwow = ahc_pci_config(ahc, entwy);
	if (ewwow != 0) {
		ahc_fwee(ahc);
		wetuwn (-ewwow);
	}

	/*
	 * Second Function PCI devices need to inhewit some
	 * settings fwom function 0.
	 */
	if ((ahc->featuwes & AHC_MUWTI_FUNC) && PCI_FUNC(pdev->devfn) != 0)
		ahc_winux_pci_inhewit_fwags(ahc);

	pci_set_dwvdata(pdev, ahc);
	wetuwn ahc_winux_wegistew_host(ahc, &aic7xxx_dwivew_tempwate);
}

/******************************* PCI Woutines *********************************/
uint32_t
ahc_pci_wead_config(ahc_dev_softc_t pci, int weg, int width)
{
	switch (width) {
	case 1:
	{
		uint8_t wetvaw;

		pci_wead_config_byte(pci, weg, &wetvaw);
		wetuwn (wetvaw);
	}
	case 2:
	{
		uint16_t wetvaw;
		pci_wead_config_wowd(pci, weg, &wetvaw);
		wetuwn (wetvaw);
	}
	case 4:
	{
		uint32_t wetvaw;
		pci_wead_config_dwowd(pci, weg, &wetvaw);
		wetuwn (wetvaw);
	}
	defauwt:
		panic("ahc_pci_wead_config: Wead size too big");
		/* NOTWEACHED */
		wetuwn (0);
	}
}

void
ahc_pci_wwite_config(ahc_dev_softc_t pci, int weg, uint32_t vawue, int width)
{
	switch (width) {
	case 1:
		pci_wwite_config_byte(pci, weg, vawue);
		bweak;
	case 2:
		pci_wwite_config_wowd(pci, weg, vawue);
		bweak;
	case 4:
		pci_wwite_config_dwowd(pci, weg, vawue);
		bweak;
	defauwt:
		panic("ahc_pci_wwite_config: Wwite size too big");
		/* NOTWEACHED */
	}
}

static SIMPWE_DEV_PM_OPS(ahc_winux_pci_dev_pm_ops,
			 ahc_winux_pci_dev_suspend,
			 ahc_winux_pci_dev_wesume);

static stwuct pci_dwivew aic7xxx_pci_dwivew = {
	.name		= "aic7xxx",
	.pwobe		= ahc_winux_pci_dev_pwobe,
	.dwivew.pm	= &ahc_winux_pci_dev_pm_ops,
	.wemove		= ahc_winux_pci_dev_wemove,
	.id_tabwe	= ahc_winux_pci_id_tabwe
};

int
ahc_winux_pci_init(void)
{
	wetuwn pci_wegistew_dwivew(&aic7xxx_pci_dwivew);
}

void
ahc_winux_pci_exit(void)
{
	pci_unwegistew_dwivew(&aic7xxx_pci_dwivew);
}

static int
ahc_winux_pci_wesewve_io_wegion(stwuct ahc_softc *ahc, wesouwce_size_t *base)
{
	if (aic7xxx_awwow_memio == 0)
		wetuwn (ENOMEM);

	*base = pci_wesouwce_stawt(ahc->dev_softc, 0);
	if (*base == 0)
		wetuwn (ENOMEM);
	if (!wequest_wegion(*base, 256, "aic7xxx"))
		wetuwn (ENOMEM);
	wetuwn (0);
}

static int
ahc_winux_pci_wesewve_mem_wegion(stwuct ahc_softc *ahc,
				 wesouwce_size_t *bus_addw,
				 uint8_t __iomem **maddw)
{
	wesouwce_size_t	stawt;
	int	ewwow;

	ewwow = 0;
	stawt = pci_wesouwce_stawt(ahc->dev_softc, 1);
	if (stawt != 0) {
		*bus_addw = stawt;
		if (!wequest_mem_wegion(stawt, 0x1000, "aic7xxx"))
			ewwow = ENOMEM;
		if (ewwow == 0) {
			*maddw = iowemap(stawt, 256);
			if (*maddw == NUWW) {
				ewwow = ENOMEM;
				wewease_mem_wegion(stawt, 0x1000);
			}
		}
	} ewse
		ewwow = ENOMEM;
	wetuwn (ewwow);
}

int
ahc_pci_map_wegistews(stwuct ahc_softc *ahc)
{
	uint32_t command;
	wesouwce_size_t	base;
	uint8_t	__iomem *maddw;
	int	 ewwow;

	/*
	 * If its awwowed, we pwefew memowy mapped access.
	 */
	command = ahc_pci_wead_config(ahc->dev_softc, PCIW_COMMAND, 4);
	command &= ~(PCIM_CMD_POWTEN|PCIM_CMD_MEMEN);
	base = 0;
	maddw = NUWW;
	ewwow = ahc_winux_pci_wesewve_mem_wegion(ahc, &base, &maddw);
	if (ewwow == 0) {
		ahc->pwatfowm_data->mem_busaddw = base;
		ahc->tag = BUS_SPACE_MEMIO;
		ahc->bsh.maddw = maddw;
		ahc_pci_wwite_config(ahc->dev_softc, PCIW_COMMAND,
				     command | PCIM_CMD_MEMEN, 4);

		/*
		 * Do a quick test to see if memowy mapped
		 * I/O is functioning cowwectwy.
		 */
		if (ahc_pci_test_wegistew_access(ahc) != 0) {

			pwintk("aic7xxx: PCI Device %d:%d:%d "
			       "faiwed memowy mapped test.  Using PIO.\n",
			       ahc_get_pci_bus(ahc->dev_softc),
			       ahc_get_pci_swot(ahc->dev_softc),
			       ahc_get_pci_function(ahc->dev_softc));
			iounmap(maddw);
			wewease_mem_wegion(ahc->pwatfowm_data->mem_busaddw,
					   0x1000);
			ahc->bsh.maddw = NUWW;
			maddw = NUWW;
		} ewse
			command |= PCIM_CMD_MEMEN;
	} ewse {
		pwintk("aic7xxx: PCI%d:%d:%d MEM wegion 0x%wwx "
		       "unavaiwabwe. Cannot memowy map device.\n",
		       ahc_get_pci_bus(ahc->dev_softc),
		       ahc_get_pci_swot(ahc->dev_softc),
		       ahc_get_pci_function(ahc->dev_softc),
		       (unsigned wong wong)base);
	}

	/*
	 * We awways pwefew memowy mapped access.
	 */
	if (maddw == NUWW) {

		ewwow = ahc_winux_pci_wesewve_io_wegion(ahc, &base);
		if (ewwow == 0) {
			ahc->tag = BUS_SPACE_PIO;
			ahc->bsh.iopowt = (u_wong)base;
			command |= PCIM_CMD_POWTEN;
		} ewse {
			pwintk("aic7xxx: PCI%d:%d:%d IO wegion 0x%wwx[0..255] "
			       "unavaiwabwe. Cannot map device.\n",
			       ahc_get_pci_bus(ahc->dev_softc),
			       ahc_get_pci_swot(ahc->dev_softc),
			       ahc_get_pci_function(ahc->dev_softc),
			       (unsigned wong wong)base);
		}
	}
	ahc_pci_wwite_config(ahc->dev_softc, PCIW_COMMAND, command, 4);
	wetuwn (ewwow);
}

int
ahc_pci_map_int(stwuct ahc_softc *ahc)
{
	int ewwow;

	ewwow = wequest_iwq(ahc->dev_softc->iwq, ahc_winux_isw,
			    IWQF_SHAWED, "aic7xxx", ahc);
	if (ewwow == 0)
		ahc->pwatfowm_data->iwq = ahc->dev_softc->iwq;
	
	wetuwn (-ewwow);
}

