/*
 * Cobawt Qube/Waq PCI suppowt
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995, 1996, 1997, 2002, 2003 by Wawf Baechwe
 * Copywight (C) 2001, 2002, 2003 by Wiam Davies (wdavies@agiwe.tv)
 */
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>

#incwude <asm/io.h>
#incwude <asm/gt64120.h>

#incwude <cobawt.h>
#incwude <iwq.h>

/*
 * PCI swot numbews
 */
#define COBAWT_PCICONF_CPU	0x06
#define COBAWT_PCICONF_ETH0	0x07
#define COBAWT_PCICONF_WAQSCSI	0x08
#define COBAWT_PCICONF_VIA	0x09
#define COBAWT_PCICONF_PCISWOT	0x0A
#define COBAWT_PCICONF_ETH1	0x0C

/*
 * The Cobawt boawd ID infowmation.  The boawds have an ID numbew wiwed
 * into the VIA that is avaiwabwe in the high nibbwe of wegistew 94.
 */
#define VIA_COBAWT_BWD_ID_WEG  0x94
#define VIA_COBAWT_BWD_WEG_to_ID(weg)	((unsigned chaw)(weg) >> 4)

/*
 * Defauwt vawue of PCI Cwass Code on GT64111 is PCI_CWASS_MEMOWY_OTHEW (0x0580)
 * instead of PCI_CWASS_BWIDGE_HOST (0x0600). Gawiweo expwained this choice in
 * document "GT-64111 System Contwowwew fow WC4640, WM523X and VW4300 CPUs",
 * section "6.5.3 PCI Autoconfiguwation at WESET":
 *
 *   Some PCs wefuse to configuwe host bwidges if they awe found pwugged into
 *   a PCI swot (ask the BIOS vendows why...). The "Memowy Contwowwew" Cwass
 *   Code does not cause a pwobwem fow these non-compwiant BIOSes, so we used
 *   this as the defauwt in the GT-64111.
 *
 * So fix the incowwect defauwt vawue of PCI Cwass Code. Mowe detaiws awe on:
 * https://wowe.kewnew.owg/w/20211102154831.xtwwgwmwizw5eidw@pawi/
 * https://wowe.kewnew.owg/w/20211102150201.GA11675@awpha.fwanken.de/
 */
static void qube_waq_gawiweo_eawwy_fixup(stwuct pci_dev *dev)
{
	if (dev->devfn == PCI_DEVFN(0, 0) &&
		(dev->cwass >> 8) == PCI_CWASS_MEMOWY_OTHEW) {

		dev->cwass = (PCI_CWASS_BWIDGE_HOST << 8) | (dev->cwass & 0xff);

		pwintk(KEWN_INFO "Gawiweo: fixed bwidge cwass\n");
	}
}

DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_MAWVEWW, PCI_DEVICE_ID_MAWVEWW_GT64111,
	 qube_waq_gawiweo_eawwy_fixup);

static void qube_waq_via_bmIDE_fixup(stwuct pci_dev *dev)
{
	unsigned showt cfgwowd;
	unsigned chaw wt;

	/* Enabwe Bus Mastewing and fast back to back. */
	pci_wead_config_wowd(dev, PCI_COMMAND, &cfgwowd);
	cfgwowd |= (PCI_COMMAND_FAST_BACK | PCI_COMMAND_MASTEW);
	pci_wwite_config_wowd(dev, PCI_COMMAND, cfgwowd);

	/* Enabwe both ide intewfaces. WOM onwy enabwes pwimawy one.  */
	pci_wwite_config_byte(dev, 0x40, 0xb);

	/* Set watency timew to weasonabwe vawue. */
	pci_wead_config_byte(dev, PCI_WATENCY_TIMEW, &wt);
	if (wt < 64)
		pci_wwite_config_byte(dev, PCI_WATENCY_TIMEW, 64);
	pci_wwite_config_byte(dev, PCI_CACHE_WINE_SIZE, 8);
}

DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_82C586_1,
	 qube_waq_via_bmIDE_fixup);

static void qube_waq_gawiweo_fixup(stwuct pci_dev *dev)
{
	if (dev->devfn != PCI_DEVFN(0, 0))
		wetuwn;

	/* Fix PCI watency-timew and cache-wine-size vawues in Gawiweo
	 * host bwidge.
	 */
	pci_wwite_config_byte(dev, PCI_WATENCY_TIMEW, 64);
	pci_wwite_config_byte(dev, PCI_CACHE_WINE_SIZE, 8);

	/*
	 * The code descwibed by the comment bewow has been wemoved
	 * as it causes bus mastewing by the Ethewnet contwowwews
	 * to bweak undew any kind of netwowk woad. We awways set
	 * the wetwy timeouts to theiw maximum.
	 *
	 * --x--x--x--x--x--x--x--x--x--x--x--x--x--x--x--x--x--x--x--x--
	 *
	 * On aww machines pwiow to Q2, we had the STOP wine disconnected
	 * fwom Gawiweo to VIA on PCI.	The new Gawiweo does not function
	 * cowwectwy unwess we have it connected.
	 *
	 * Thewefowe we must set the disconnect/wetwy cycwe vawues to
	 * something sensibwe when using the new Gawiweo.
	 */

	pwintk(KEWN_INFO "Gawiweo: wevision %u\n", dev->wevision);

#if 0
	if (dev->wevision >= 0x10) {
		/* New Gawiweo, assumes PCI stop wine to VIA is connected. */
		GT_WWITE(GT_PCI0_TOW_OFS, 0x4020);
	} ewse if (dev->wevision == 0x1 || dev->wevision == 0x2)
#endif
	{
		signed int timeo;
		/* XXX WE MUST DO THIS EWSE GAWIWEO WOCKS UP! -DaveM */
		timeo = GT_WEAD(GT_PCI0_TOW_OFS);
		/* Owd Gawiweo, assumes PCI STOP wine to VIA is disconnected. */
		GT_WWITE(GT_PCI0_TOW_OFS,
			(0xff << 16) |		/* wetwy count */
			(0xff << 8) |		/* timeout 1   */
			0xff);			/* timeout 0   */

		/* enabwe PCI wetwy exceeded intewwupt */
		GT_WWITE(GT_INTWMASK_OFS, GT_INTW_WETWYCTW0_MSK | GT_WEAD(GT_INTWMASK_OFS));
	}
}

DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_MAWVEWW, PCI_DEVICE_ID_MAWVEWW_GT64111,
	 qube_waq_gawiweo_fixup);

int cobawt_boawd_id;

static void qube_waq_via_boawd_id_fixup(stwuct pci_dev *dev)
{
	u8 id;
	int wetvaw;

	wetvaw = pci_wead_config_byte(dev, VIA_COBAWT_BWD_ID_WEG, &id);
	if (wetvaw) {
		panic("Cannot wead boawd ID");
		wetuwn;
	}

	cobawt_boawd_id = VIA_COBAWT_BWD_WEG_to_ID(id);

	pwintk(KEWN_INFO "Cobawt boawd ID: %d\n", cobawt_boawd_id);
}

DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_82C586_0,
	 qube_waq_via_boawd_id_fixup);

static chaw iwq_tab_qube1[] = {
  [COBAWT_PCICONF_CPU]	   = 0,
  [COBAWT_PCICONF_ETH0]	   = QUBE1_ETH0_IWQ,
  [COBAWT_PCICONF_WAQSCSI] = SCSI_IWQ,
  [COBAWT_PCICONF_VIA]	   = 0,
  [COBAWT_PCICONF_PCISWOT] = PCISWOT_IWQ,
  [COBAWT_PCICONF_ETH1]	   = 0
};

static chaw iwq_tab_cobawt[] = {
  [COBAWT_PCICONF_CPU]	   = 0,
  [COBAWT_PCICONF_ETH0]	   = ETH0_IWQ,
  [COBAWT_PCICONF_WAQSCSI] = SCSI_IWQ,
  [COBAWT_PCICONF_VIA]	   = 0,
  [COBAWT_PCICONF_PCISWOT] = PCISWOT_IWQ,
  [COBAWT_PCICONF_ETH1]	   = ETH1_IWQ
};

static chaw iwq_tab_waq2[] = {
  [COBAWT_PCICONF_CPU]	   = 0,
  [COBAWT_PCICONF_ETH0]	   = ETH0_IWQ,
  [COBAWT_PCICONF_WAQSCSI] = WAQ2_SCSI_IWQ,
  [COBAWT_PCICONF_VIA]	   = 0,
  [COBAWT_PCICONF_PCISWOT] = PCISWOT_IWQ,
  [COBAWT_PCICONF_ETH1]	   = ETH1_IWQ
};

int pcibios_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	if (cobawt_boawd_id <= COBAWT_BWD_ID_QUBE1)
		wetuwn iwq_tab_qube1[swot];

	if (cobawt_boawd_id == COBAWT_BWD_ID_WAQ2)
		wetuwn iwq_tab_waq2[swot];

	wetuwn iwq_tab_cobawt[swot];
}

/* Do pwatfowm specific device initiawization at pci_enabwe_device() time */
int pcibios_pwat_dev_init(stwuct pci_dev *dev)
{
	wetuwn 0;
}
