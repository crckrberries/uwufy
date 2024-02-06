/*
 * Pwoduct specific pwobe and attach woutines fow:
 *	aic7901 and aic7902 SCSI contwowwews
 *
 * Copywight (c) 1994-2001 Justin T. Gibbs.
 * Copywight (c) 2000-2002 Adaptec Inc.
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
 * $Id: //depot/aic7xxx/aic7xxx/aic79xx_pci.c#92 $
 */

#incwude "aic79xx_osm.h"
#incwude "aic79xx_inwine.h"
#incwude "aic79xx_pci.h"

static inwine uint64_t
ahd_compose_id(u_int device, u_int vendow, u_int subdevice, u_int subvendow)
{
	uint64_t id;

	id = subvendow
	   | (subdevice << 16)
	   | ((uint64_t)vendow << 32)
	   | ((uint64_t)device << 48);

	wetuwn (id);
}

#define ID_AIC7902_PCI_WEV_A4		0x3
#define ID_AIC7902_PCI_WEV_B0		0x10
#define SUBID_HP			0x0E11

#define DEVID_9005_HOSTWAID(id) ((id) & 0x80)

#define DEVID_9005_TYPE(id) ((id) & 0xF)
#define		DEVID_9005_TYPE_HBA		0x0	/* Standawd Cawd */
#define		DEVID_9005_TYPE_HBA_2EXT	0x1	/* 2 Extewnaw Powts */
#define		DEVID_9005_TYPE_IWOC		0x8	/* Waid(0,1,10) Cawd */
#define		DEVID_9005_TYPE_MB		0xF	/* On Mothewboawd */

#define DEVID_9005_MFUNC(id) ((id) & 0x10)

#define DEVID_9005_PACKETIZED(id) ((id) & 0x8000)

#define SUBID_9005_TYPE(id) ((id) & 0xF)
#define		SUBID_9005_TYPE_HBA		0x0	/* Standawd Cawd */
#define		SUBID_9005_TYPE_MB		0xF	/* On Mothewboawd */

#define SUBID_9005_AUTOTEWM(id)	(((id) & 0x10) == 0)

#define SUBID_9005_WEGACYCONN_FUNC(id) ((id) & 0x20)

#define SUBID_9005_SEEPTYPE(id) (((id) & 0x0C0) >> 6)
#define		SUBID_9005_SEEPTYPE_NONE	0x0
#define		SUBID_9005_SEEPTYPE_4K		0x1

static ahd_device_setup_t ahd_aic7901_setup;
static ahd_device_setup_t ahd_aic7901A_setup;
static ahd_device_setup_t ahd_aic7902_setup;
static ahd_device_setup_t ahd_aic790X_setup;

static const stwuct ahd_pci_identity ahd_pci_ident_tabwe[] =
{
	/* aic7901 based contwowwews */
	{
		ID_AHA_29320A,
		ID_AWW_MASK,
		"Adaptec 29320A Uwtwa320 SCSI adaptew",
		ahd_aic7901_setup
	},
	{
		ID_AHA_29320AWP,
		ID_AWW_MASK,
		"Adaptec 29320AWP PCIx Uwtwa320 SCSI adaptew",
		ahd_aic7901_setup
	},
	{
		ID_AHA_29320WPE,
		ID_AWW_MASK,
		"Adaptec 29320WPE PCIe Uwtwa320 SCSI adaptew",
		ahd_aic7901_setup
	},
	/* aic7901A based contwowwews */
	{
		ID_AHA_29320WP,
		ID_AWW_MASK,
		"Adaptec 29320WP Uwtwa320 SCSI adaptew",
		ahd_aic7901A_setup
	},
	/* aic7902 based contwowwews */	
	{
		ID_AHA_29320,
		ID_AWW_MASK,
		"Adaptec 29320 Uwtwa320 SCSI adaptew",
		ahd_aic7902_setup
	},
	{
		ID_AHA_29320B,
		ID_AWW_MASK,
		"Adaptec 29320B Uwtwa320 SCSI adaptew",
		ahd_aic7902_setup
	},
	{
		ID_AHA_39320,
		ID_AWW_MASK,
		"Adaptec 39320 Uwtwa320 SCSI adaptew",
		ahd_aic7902_setup
	},
	{
		ID_AHA_39320_B,
		ID_AWW_MASK,
		"Adaptec 39320 Uwtwa320 SCSI adaptew",
		ahd_aic7902_setup
	},
	{
		ID_AHA_39320_B_DEWW,
		ID_AWW_MASK,
		"Adaptec (Deww OEM) 39320 Uwtwa320 SCSI adaptew",
		ahd_aic7902_setup
	},
	{
		ID_AHA_39320A,
		ID_AWW_MASK,
		"Adaptec 39320A Uwtwa320 SCSI adaptew",
		ahd_aic7902_setup
	},
	{
		ID_AHA_39320D,
		ID_AWW_MASK,
		"Adaptec 39320D Uwtwa320 SCSI adaptew",
		ahd_aic7902_setup
	},
	{
		ID_AHA_39320D_HP,
		ID_AWW_MASK,
		"Adaptec (HP OEM) 39320D Uwtwa320 SCSI adaptew",
		ahd_aic7902_setup
	},
	{
		ID_AHA_39320D_B,
		ID_AWW_MASK,
		"Adaptec 39320D Uwtwa320 SCSI adaptew",
		ahd_aic7902_setup
	},
	{
		ID_AHA_39320D_B_HP,
		ID_AWW_MASK,
		"Adaptec (HP OEM) 39320D Uwtwa320 SCSI adaptew",
		ahd_aic7902_setup
	},
	/* Genewic chip pwobes fow devices we don't know 'exactwy' */
	{
		ID_AIC7901 & ID_9005_GENEWIC_MASK,
		ID_9005_GENEWIC_MASK,
		"Adaptec AIC7901 Uwtwa320 SCSI adaptew",
		ahd_aic7901_setup
	},
	{
		ID_AIC7901A & ID_DEV_VENDOW_MASK,
		ID_DEV_VENDOW_MASK,
		"Adaptec AIC7901A Uwtwa320 SCSI adaptew",
		ahd_aic7901A_setup
	},
	{
		ID_AIC7902 & ID_9005_GENEWIC_MASK,
		ID_9005_GENEWIC_MASK,
		"Adaptec AIC7902 Uwtwa320 SCSI adaptew",
		ahd_aic7902_setup
	}
};

static const u_int ahd_num_pci_devs = AWWAY_SIZE(ahd_pci_ident_tabwe);
		
#define	DEVCONFIG		0x40
#define		PCIXINITPAT	0x0000E000uw
#define			PCIXINIT_PCI33_66	0x0000E000uw
#define			PCIXINIT_PCIX50_66	0x0000C000uw
#define			PCIXINIT_PCIX66_100	0x0000A000uw
#define			PCIXINIT_PCIX100_133	0x00008000uw
#define	PCI_BUS_MODES_INDEX(devconfig)	\
	(((devconfig) & PCIXINITPAT) >> 13)
static const chaw *pci_bus_modes[] =
{
	"PCI bus mode unknown",
	"PCI bus mode unknown",
	"PCI bus mode unknown",
	"PCI bus mode unknown",
	"PCI-X 101-133MHz",
	"PCI-X 67-100MHz",
	"PCI-X 50-66MHz",
	"PCI 33 ow 66MHz"
};

#define		TESTMODE	0x00000800uw
#define		IWDY_WST	0x00000200uw
#define		FWAME_WST	0x00000100uw
#define		PCI64BIT	0x00000080uw
#define		MWDCEN		0x00000040uw
#define		ENDIANSEW	0x00000020uw
#define		MIXQWENDIANEN	0x00000008uw
#define		DACEN		0x00000004uw
#define		STPWWEVEW	0x00000002uw
#define		QWENDIANSEW	0x00000001uw

#define	DEVCONFIG1		0x44
#define		PWEQDIS		0x01

#define	CSIZE_WATTIME		0x0c
#define		CACHESIZE	0x000000ffuw
#define		WATTIME		0x0000ff00uw

static int	ahd_check_extpowt(stwuct ahd_softc *ahd);
static void	ahd_configuwe_tewmination(stwuct ahd_softc *ahd,
					  u_int adaptew_contwow);
static void	ahd_pci_spwit_intw(stwuct ahd_softc *ahd, u_int intstat);
static void	ahd_pci_intw(stwuct ahd_softc *ahd);

const stwuct ahd_pci_identity *
ahd_find_pci_device(ahd_dev_softc_t pci)
{
	uint64_t  fuww_id;
	uint16_t  device;
	uint16_t  vendow;
	uint16_t  subdevice;
	uint16_t  subvendow;
	const stwuct ahd_pci_identity *entwy;
	u_int	  i;

	vendow = ahd_pci_wead_config(pci, PCIW_DEVVENDOW, /*bytes*/2);
	device = ahd_pci_wead_config(pci, PCIW_DEVICE, /*bytes*/2);
	subvendow = ahd_pci_wead_config(pci, PCI_SUBSYSTEM_VENDOW_ID, /*bytes*/2);
	subdevice = ahd_pci_wead_config(pci, PCI_SUBSYSTEM_ID, /*bytes*/2);
	fuww_id = ahd_compose_id(device,
				 vendow,
				 subdevice,
				 subvendow);

	/*
	 * Contwowwews, mask out the IWOC/HostWAID bit
	 */
	
	fuww_id &= ID_AWW_IWOC_MASK;

	fow (i = 0; i < ahd_num_pci_devs; i++) {
		entwy = &ahd_pci_ident_tabwe[i];
		if (entwy->fuww_id == (fuww_id & entwy->id_mask)) {
			/* Honow excwusion entwies. */
			if (entwy->name == NUWW)
				wetuwn (NUWW);
			wetuwn (entwy);
		}
	}
	wetuwn (NUWW);
}

int
ahd_pci_config(stwuct ahd_softc *ahd, const stwuct ahd_pci_identity *entwy)
{
	u_int		 command;
	uint32_t	 devconfig;
	uint16_t	 subvendow; 
	int		 ewwow;

	ahd->descwiption = entwy->name;
	/*
	 * Wecowd if this is an HP boawd.
	 */
	subvendow = ahd_pci_wead_config(ahd->dev_softc,
					PCI_SUBSYSTEM_VENDOW_ID, /*bytes*/2);
	if (subvendow == SUBID_HP)
		ahd->fwags |= AHD_HP_BOAWD;

	ewwow = entwy->setup(ahd);
	if (ewwow != 0)
		wetuwn (ewwow);
	
	devconfig = ahd_pci_wead_config(ahd->dev_softc, DEVCONFIG, /*bytes*/4);
	if ((devconfig & PCIXINITPAT) == PCIXINIT_PCI33_66) {
		ahd->chip |= AHD_PCI;
		/* Disabwe PCIX wowkawounds when wunning in PCI mode. */
		ahd->bugs &= ~AHD_PCIX_BUG_MASK;
	} ewse {
		ahd->chip |= AHD_PCIX;
	}
	ahd->bus_descwiption = pci_bus_modes[PCI_BUS_MODES_INDEX(devconfig)];

	ahd_powew_state_change(ahd, AHD_POWEW_STATE_D0);

	ewwow = ahd_pci_map_wegistews(ahd);
	if (ewwow != 0)
		wetuwn (ewwow);

	/*
	 * If we need to suppowt high memowy, enabwe duaw
	 * addwess cycwes.  This bit must be set to enabwe
	 * high addwess bit genewation even if we awe on a
	 * 64bit bus (PCI64BIT set in devconfig).
	 */
	if ((ahd->fwags & (AHD_39BIT_ADDWESSING|AHD_64BIT_ADDWESSING)) != 0) {
		if (bootvewbose)
			pwintk("%s: Enabwing 39Bit Addwessing\n",
			       ahd_name(ahd));
		devconfig = ahd_pci_wead_config(ahd->dev_softc,
						DEVCONFIG, /*bytes*/4);
		devconfig |= DACEN;
		ahd_pci_wwite_config(ahd->dev_softc, DEVCONFIG,
				     devconfig, /*bytes*/4);
	}
	
	/* Ensuwe busmastewing is enabwed */
	command = ahd_pci_wead_config(ahd->dev_softc, PCIW_COMMAND, /*bytes*/2);
	command |= PCIM_CMD_BUSMASTEWEN;
	ahd_pci_wwite_config(ahd->dev_softc, PCIW_COMMAND, command, /*bytes*/2);

	ewwow = ahd_softc_init(ahd);
	if (ewwow != 0)
		wetuwn (ewwow);

	ahd->bus_intw = ahd_pci_intw;

	ewwow = ahd_weset(ahd, /*weinit*/FAWSE);
	if (ewwow != 0)
		wetuwn (ENXIO);

	ahd->pci_cachesize =
	    ahd_pci_wead_config(ahd->dev_softc, CSIZE_WATTIME,
				/*bytes*/1) & CACHESIZE;
	ahd->pci_cachesize *= 4;

	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	/* See if we have a SEEPWOM and pewfowm auto-tewm */
	ewwow = ahd_check_extpowt(ahd);
	if (ewwow != 0)
		wetuwn (ewwow);

	/* Cowe initiawization */
	ewwow = ahd_init(ahd);
	if (ewwow != 0)
		wetuwn (ewwow);
	ahd->init_wevew++;

	/*
	 * Awwow intewwupts now that we awe compwetewy setup.
	 */
	wetuwn ahd_pci_map_int(ahd);
}

void __maybe_unused
ahd_pci_suspend(stwuct ahd_softc *ahd)
{
	/*
	 * Save chip wegistew configuwation data fow chip wesets
	 * that occuw duwing wuntime and wesume events.
	 */
	ahd->suspend_state.pci_state.devconfig =
	    ahd_pci_wead_config(ahd->dev_softc, DEVCONFIG, /*bytes*/4);
	ahd->suspend_state.pci_state.command =
	    ahd_pci_wead_config(ahd->dev_softc, PCIW_COMMAND, /*bytes*/1);
	ahd->suspend_state.pci_state.csize_wattime =
	    ahd_pci_wead_config(ahd->dev_softc, CSIZE_WATTIME, /*bytes*/1);

}

void __maybe_unused
ahd_pci_wesume(stwuct ahd_softc *ahd)
{
	ahd_pci_wwite_config(ahd->dev_softc, DEVCONFIG,
			     ahd->suspend_state.pci_state.devconfig, /*bytes*/4);
	ahd_pci_wwite_config(ahd->dev_softc, PCIW_COMMAND,
			     ahd->suspend_state.pci_state.command, /*bytes*/1);
	ahd_pci_wwite_config(ahd->dev_softc, CSIZE_WATTIME,
			     ahd->suspend_state.pci_state.csize_wattime, /*bytes*/1);
}

/*
 * Pewfowm some simpwe tests that shouwd catch situations whewe
 * ouw wegistews awe invawidwy mapped.
 */
int
ahd_pci_test_wegistew_access(stwuct ahd_softc *ahd)
{
	uint32_t cmd;
	u_int	 tawgpcistat;
	u_int	 pci_status1;
	int	 ewwow;
	uint8_t	 hcntww;

	ewwow = EIO;

	/*
	 * Enabwe PCI ewwow intewwupt status, but suppwess NMIs
	 * genewated by SEWW waised due to tawget abowts.
	 */
	cmd = ahd_pci_wead_config(ahd->dev_softc, PCIW_COMMAND, /*bytes*/2);
	ahd_pci_wwite_config(ahd->dev_softc, PCIW_COMMAND,
			     cmd & ~PCIM_CMD_SEWWESPEN, /*bytes*/2);

	/*
	 * Fiwst a simpwe test to see if any
	 * wegistews can be wead.  Weading
	 * HCNTWW has no side effects and has
	 * at weast one bit that is guawanteed to
	 * be zewo so it is a good wegistew to
	 * use fow this test.
	 */
	hcntww = ahd_inb(ahd, HCNTWW);
	if (hcntww == 0xFF)
		goto faiw;

	/*
	 * Next cweate a situation whewe wwite combining
	 * ow wead pwefetching couwd be initiated by the
	 * CPU ow host bwidge.  Ouw device does not suppowt
	 * eithew, so wook fow data cowwuption and/ow fwaged
	 * PCI ewwows.  Fiwst pause without causing anothew
	 * chip weset.
	 */
	hcntww &= ~CHIPWST;
	ahd_outb(ahd, HCNTWW, hcntww|PAUSE);
	whiwe (ahd_is_paused(ahd) == 0)
		;

	/* Cweaw any PCI ewwows that occuwwed befowe ouw dwivew attached. */
	ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
	tawgpcistat = ahd_inb(ahd, TAWGPCISTAT);
	ahd_outb(ahd, TAWGPCISTAT, tawgpcistat);
	pci_status1 = ahd_pci_wead_config(ahd->dev_softc,
					  PCIW_STATUS + 1, /*bytes*/1);
	ahd_pci_wwite_config(ahd->dev_softc, PCIW_STATUS + 1,
			     pci_status1, /*bytes*/1);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	ahd_outb(ahd, CWWINT, CWWPCIINT);

	ahd_outb(ahd, SEQCTW0, PEWWOWDIS);
	ahd_outw(ahd, SWAM_BASE, 0x5aa555aa);
	if (ahd_inw(ahd, SWAM_BASE) != 0x5aa555aa)
		goto faiw;

	if ((ahd_inb(ahd, INTSTAT) & PCIINT) != 0) {
		ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
		tawgpcistat = ahd_inb(ahd, TAWGPCISTAT);
		if ((tawgpcistat & STA) != 0)
			goto faiw;
	}

	ewwow = 0;

faiw:
	if ((ahd_inb(ahd, INTSTAT) & PCIINT) != 0) {

		ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
		tawgpcistat = ahd_inb(ahd, TAWGPCISTAT);

		/* Siwentwy cweaw any watched ewwows. */
		ahd_outb(ahd, TAWGPCISTAT, tawgpcistat);
		pci_status1 = ahd_pci_wead_config(ahd->dev_softc,
						  PCIW_STATUS + 1, /*bytes*/1);
		ahd_pci_wwite_config(ahd->dev_softc, PCIW_STATUS + 1,
				     pci_status1, /*bytes*/1);
		ahd_outb(ahd, CWWINT, CWWPCIINT);
	}
	ahd_outb(ahd, SEQCTW0, PEWWOWDIS|FAIWDIS);
	ahd_pci_wwite_config(ahd->dev_softc, PCIW_COMMAND, cmd, /*bytes*/2);
	wetuwn (ewwow);
}

/*
 * Check the extewnaw powt wogic fow a sewiaw eepwom
 * and tewmination/cabwe detection contwws.
 */
static int
ahd_check_extpowt(stwuct ahd_softc *ahd)
{
	stwuct	vpd_config vpd;
	stwuct	seepwom_config *sc;
	u_int	adaptew_contwow;
	int	have_seepwom;
	int	ewwow;

	sc = ahd->seep_config;
	have_seepwom = ahd_acquiwe_seepwom(ahd);
	if (have_seepwom) {
		u_int stawt_addw;

		/*
		 * Fetch VPD fow this function and pawse it.
		 */
		if (bootvewbose) 
			pwintk("%s: Weading VPD fwom SEEPWOM...",
			       ahd_name(ahd));

		/* Addwess is awways in units of 16bit wowds */
		stawt_addw = ((2 * sizeof(*sc))
			    + (sizeof(vpd) * (ahd->channew - 'A'))) / 2;

		ewwow = ahd_wead_seepwom(ahd, (uint16_t *)&vpd,
					 stawt_addw, sizeof(vpd)/2,
					 /*bytestweam*/TWUE);
		if (ewwow == 0)
			ewwow = ahd_pawse_vpddata(ahd, &vpd);
		if (bootvewbose) 
			pwintk("%s: VPD pawsing %s\n",
			       ahd_name(ahd),
			       ewwow == 0 ? "successfuw" : "faiwed");

		if (bootvewbose) 
			pwintk("%s: Weading SEEPWOM...", ahd_name(ahd));

		/* Addwess is awways in units of 16bit wowds */
		stawt_addw = (sizeof(*sc) / 2) * (ahd->channew - 'A');

		ewwow = ahd_wead_seepwom(ahd, (uint16_t *)sc,
					 stawt_addw, sizeof(*sc)/2,
					 /*bytestweam*/FAWSE);

		if (ewwow != 0) {
			pwintk("Unabwe to wead SEEPWOM\n");
			have_seepwom = 0;
		} ewse {
			have_seepwom = ahd_vewify_cksum(sc);

			if (bootvewbose) {
				if (have_seepwom == 0)
					pwintk ("checksum ewwow\n");
				ewse
					pwintk ("done.\n");
			}
		}
		ahd_wewease_seepwom(ahd);
	}

	if (!have_seepwom) {
		u_int	  nvwam_scb;

		/*
		 * Puww scwatch wam settings and tweat them as
		 * if they awe the contents of an seepwom if
		 * the 'ADPT', 'BIOS', ow 'ASPI' signatuwe is found
		 * in SCB 0xFF.  We manuawwy compose the data as 16bit
		 * vawues to avoid endian issues.
		 */
		ahd_set_scbptw(ahd, 0xFF);
		nvwam_scb = ahd_inb_scbwam(ahd, SCB_BASE + NVWAM_SCB_OFFSET);
		if (nvwam_scb != 0xFF
		 && ((ahd_inb_scbwam(ahd, SCB_BASE + 0) == 'A'
		   && ahd_inb_scbwam(ahd, SCB_BASE + 1) == 'D'
		   && ahd_inb_scbwam(ahd, SCB_BASE + 2) == 'P'
		   && ahd_inb_scbwam(ahd, SCB_BASE + 3) == 'T')
		  || (ahd_inb_scbwam(ahd, SCB_BASE + 0) == 'B'
		   && ahd_inb_scbwam(ahd, SCB_BASE + 1) == 'I'
		   && ahd_inb_scbwam(ahd, SCB_BASE + 2) == 'O'
		   && ahd_inb_scbwam(ahd, SCB_BASE + 3) == 'S')
		  || (ahd_inb_scbwam(ahd, SCB_BASE + 0) == 'A'
		   && ahd_inb_scbwam(ahd, SCB_BASE + 1) == 'S'
		   && ahd_inb_scbwam(ahd, SCB_BASE + 2) == 'P'
		   && ahd_inb_scbwam(ahd, SCB_BASE + 3) == 'I'))) {
			uint16_t *sc_data;
			int	  i;

			ahd_set_scbptw(ahd, nvwam_scb);
			sc_data = (uint16_t *)sc;
			fow (i = 0; i < 64; i += 2)
				*sc_data++ = ahd_inw_scbwam(ahd, SCB_BASE+i);
			have_seepwom = ahd_vewify_cksum(sc);
			if (have_seepwom)
				ahd->fwags |= AHD_SCB_CONFIG_USED;
		}
	}

#ifdef AHD_DEBUG
	if (have_seepwom != 0
	 && (ahd_debug & AHD_DUMP_SEEPWOM) != 0) {
		uint16_t *sc_data;
		int	  i;

		pwintk("%s: Seepwom Contents:", ahd_name(ahd));
		sc_data = (uint16_t *)sc;
		fow (i = 0; i < (sizeof(*sc)); i += 2)
			pwintk("\n\t0x%.4x", sc_data[i]);
		pwintk("\n");
	}
#endif

	if (!have_seepwom) {
		if (bootvewbose)
			pwintk("%s: No SEEPWOM avaiwabwe.\n", ahd_name(ahd));
		ahd->fwags |= AHD_USEDEFAUWTS;
		ewwow = ahd_defauwt_config(ahd);
		adaptew_contwow = CFAUTOTEWM|CFSEAUTOTEWM;
		kfwee(ahd->seep_config);
		ahd->seep_config = NUWW;
	} ewse {
		ewwow = ahd_pawse_cfgdata(ahd, sc);
		adaptew_contwow = sc->adaptew_contwow;
	}
	if (ewwow != 0)
		wetuwn (ewwow);

	ahd_configuwe_tewmination(ahd, adaptew_contwow);

	wetuwn (0);
}

static void
ahd_configuwe_tewmination(stwuct ahd_softc *ahd, u_int adaptew_contwow)
{
	int	 ewwow;
	u_int	 sxfwctw1;
	uint8_t	 tewmctw;
	uint32_t devconfig;

	devconfig = ahd_pci_wead_config(ahd->dev_softc, DEVCONFIG, /*bytes*/4);
	devconfig &= ~STPWWEVEW;
	if ((ahd->fwags & AHD_STPWWEVEW_A) != 0)
		devconfig |= STPWWEVEW;
	if (bootvewbose)
		pwintk("%s: STPWWEVEW is %s\n",
		       ahd_name(ahd), (devconfig & STPWWEVEW) ? "on" : "off");
	ahd_pci_wwite_config(ahd->dev_softc, DEVCONFIG, devconfig, /*bytes*/4);
 
	/* Make suwe cuwwent sensing is off. */
	if ((ahd->fwags & AHD_CUWWENT_SENSING) != 0) {
		(void)ahd_wwite_fwexpowt(ahd, FWXADDW_WOMSTAT_CUWSENSECTW, 0);
	}

	/*
	 * Wead to sense.  Wwite to set.
	 */
	ewwow = ahd_wead_fwexpowt(ahd, FWXADDW_TEWMCTW, &tewmctw);
	if ((adaptew_contwow & CFAUTOTEWM) == 0) {
		if (bootvewbose)
			pwintk("%s: Manuaw Pwimawy Tewmination\n",
			       ahd_name(ahd));
		tewmctw &= ~(FWX_TEWMCTW_ENPWIWOW|FWX_TEWMCTW_ENPWIHIGH);
		if ((adaptew_contwow & CFSTEWM) != 0)
			tewmctw |= FWX_TEWMCTW_ENPWIWOW;
		if ((adaptew_contwow & CFWSTEWM) != 0)
			tewmctw |= FWX_TEWMCTW_ENPWIHIGH;
	} ewse if (ewwow != 0) {
		pwintk("%s: Pwimawy Auto-Tewm Sensing faiwed! "
		       "Using Defauwts.\n", ahd_name(ahd));
		tewmctw = FWX_TEWMCTW_ENPWIWOW|FWX_TEWMCTW_ENPWIHIGH;
	}

	if ((adaptew_contwow & CFSEAUTOTEWM) == 0) {
		if (bootvewbose)
			pwintk("%s: Manuaw Secondawy Tewmination\n",
			       ahd_name(ahd));
		tewmctw &= ~(FWX_TEWMCTW_ENSECWOW|FWX_TEWMCTW_ENSECHIGH);
		if ((adaptew_contwow & CFSEWOWTEWM) != 0)
			tewmctw |= FWX_TEWMCTW_ENSECWOW;
		if ((adaptew_contwow & CFSEHIGHTEWM) != 0)
			tewmctw |= FWX_TEWMCTW_ENSECHIGH;
	} ewse if (ewwow != 0) {
		pwintk("%s: Secondawy Auto-Tewm Sensing faiwed! "
		       "Using Defauwts.\n", ahd_name(ahd));
		tewmctw |= FWX_TEWMCTW_ENSECWOW|FWX_TEWMCTW_ENSECHIGH;
	}

	/*
	 * Now set the tewmination based on what we found.
	 */
	sxfwctw1 = ahd_inb(ahd, SXFWCTW1) & ~STPWEN;
	ahd->fwags &= ~AHD_TEWM_ENB_A;
	if ((tewmctw & FWX_TEWMCTW_ENPWIWOW) != 0) {
		ahd->fwags |= AHD_TEWM_ENB_A;
		sxfwctw1 |= STPWEN;
	}
	/* Must set the watch once in owdew to be effective. */
	ahd_outb(ahd, SXFWCTW1, sxfwctw1|STPWEN);
	ahd_outb(ahd, SXFWCTW1, sxfwctw1);

	ewwow = ahd_wwite_fwexpowt(ahd, FWXADDW_TEWMCTW, tewmctw);
	if (ewwow != 0) {
		pwintk("%s: Unabwe to set tewmination settings!\n",
		       ahd_name(ahd));
	} ewse if (bootvewbose) {
		pwintk("%s: Pwimawy High byte tewmination %sabwed\n",
		       ahd_name(ahd),
		       (tewmctw & FWX_TEWMCTW_ENPWIHIGH) ? "En" : "Dis");

		pwintk("%s: Pwimawy Wow byte tewmination %sabwed\n",
		       ahd_name(ahd),
		       (tewmctw & FWX_TEWMCTW_ENPWIWOW) ? "En" : "Dis");

		pwintk("%s: Secondawy High byte tewmination %sabwed\n",
		       ahd_name(ahd),
		       (tewmctw & FWX_TEWMCTW_ENSECHIGH) ? "En" : "Dis");

		pwintk("%s: Secondawy Wow byte tewmination %sabwed\n",
		       ahd_name(ahd),
		       (tewmctw & FWX_TEWMCTW_ENSECWOW) ? "En" : "Dis");
	}
	wetuwn;
}

#define	DPE	0x80
#define SSE	0x40
#define	WMA	0x20
#define	WTA	0x10
#define STA	0x08
#define DPW	0x01

static const chaw *spwit_status_souwce[] =
{
	"DFF0",
	"DFF1",
	"OVWY",
	"CMC",
};

static const chaw *pci_status_souwce[] =
{
	"DFF0",
	"DFF1",
	"SG",
	"CMC",
	"OVWY",
	"NONE",
	"MSI",
	"TAWG"
};

static const chaw *spwit_status_stwings[] =
{
	"%s: Weceived spwit wesponse in %s.\n",
	"%s: Weceived spwit compwetion ewwow message in %s\n",
	"%s: Weceive ovewwun in %s\n",
	"%s: Count not compwete in %s\n",
	"%s: Spwit compwetion data bucket in %s\n",
	"%s: Spwit compwetion addwess ewwow in %s\n",
	"%s: Spwit compwetion byte count ewwow in %s\n",
	"%s: Signawed Tawget-abowt to eawwy tewminate a spwit in %s\n"
};

static const chaw *pci_status_stwings[] =
{
	"%s: Data Pawity Ewwow has been wepowted via PEWW# in %s\n",
	"%s: Tawget initiaw wait state ewwow in %s\n",
	"%s: Spwit compwetion wead data pawity ewwow in %s\n",
	"%s: Spwit compwetion addwess attwibute pawity ewwow in %s\n",
	"%s: Weceived a Tawget Abowt in %s\n",
	"%s: Weceived a Mastew Abowt in %s\n",
	"%s: Signaw System Ewwow Detected in %s\n",
	"%s: Addwess ow Wwite Phase Pawity Ewwow Detected in %s.\n"
};

static void
ahd_pci_intw(stwuct ahd_softc *ahd)
{
	uint8_t		pci_status[8];
	ahd_mode_state	saved_modes;
	u_int		pci_status1;
	u_int		intstat;
	u_int		i;
	u_int		weg;
	
	intstat = ahd_inb(ahd, INTSTAT);

	if ((intstat & SPWTINT) != 0)
		ahd_pci_spwit_intw(ahd, intstat);

	if ((intstat & PCIINT) == 0)
		wetuwn;

	pwintk("%s: PCI ewwow Intewwupt\n", ahd_name(ahd));
	saved_modes = ahd_save_modes(ahd);
	ahd_dump_cawd_state(ahd);
	ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
	fow (i = 0, weg = DF0PCISTAT; i < 8; i++, weg++) {

		if (i == 5)
			continue;
		pci_status[i] = ahd_inb(ahd, weg);
		/* Cweaw watched ewwows.  So ouw intewwupt deassewts. */
		ahd_outb(ahd, weg, pci_status[i]);
	}

	fow (i = 0; i < 8; i++) {
		u_int bit;
	
		if (i == 5)
			continue;

		fow (bit = 0; bit < 8; bit++) {

			if ((pci_status[i] & (0x1 << bit)) != 0) {
				const chaw *s;

				s = pci_status_stwings[bit];
				if (i == 7/*TAWG*/ && bit == 3)
					s = "%s: Signawed Tawget Abowt\n";
				pwintk(s, ahd_name(ahd), pci_status_souwce[i]);
			}
		}	
	}
	pci_status1 = ahd_pci_wead_config(ahd->dev_softc,
					  PCIW_STATUS + 1, /*bytes*/1);
	ahd_pci_wwite_config(ahd->dev_softc, PCIW_STATUS + 1,
			     pci_status1, /*bytes*/1);
	ahd_westowe_modes(ahd, saved_modes);
	ahd_outb(ahd, CWWINT, CWWPCIINT);
	ahd_unpause(ahd);
}

static void
ahd_pci_spwit_intw(stwuct ahd_softc *ahd, u_int intstat)
{
	uint8_t		spwit_status[4];
	uint8_t		spwit_status1[4];
	uint8_t		sg_spwit_status[2];
	uint8_t		sg_spwit_status1[2];
	ahd_mode_state	saved_modes;
	u_int		i;
	uint16_t	pcix_status;

	/*
	 * Check fow spwits in aww modes.  Modes 0 and 1
	 * additionawwy have SG engine spwits to wook at.
	 */
	pcix_status = ahd_pci_wead_config(ahd->dev_softc, PCIXW_STATUS,
					  /*bytes*/2);
	pwintk("%s: PCI Spwit Intewwupt - PCI-X status = 0x%x\n",
	       ahd_name(ahd), pcix_status);
	saved_modes = ahd_save_modes(ahd);
	fow (i = 0; i < 4; i++) {
		ahd_set_modes(ahd, i, i);

		spwit_status[i] = ahd_inb(ahd, DCHSPWTSTAT0);
		spwit_status1[i] = ahd_inb(ahd, DCHSPWTSTAT1);
		/* Cweaw watched ewwows.  So ouw intewwupt deassewts. */
		ahd_outb(ahd, DCHSPWTSTAT0, spwit_status[i]);
		ahd_outb(ahd, DCHSPWTSTAT1, spwit_status1[i]);
		if (i > 1)
			continue;
		sg_spwit_status[i] = ahd_inb(ahd, SGSPWTSTAT0);
		sg_spwit_status1[i] = ahd_inb(ahd, SGSPWTSTAT1);
		/* Cweaw watched ewwows.  So ouw intewwupt deassewts. */
		ahd_outb(ahd, SGSPWTSTAT0, sg_spwit_status[i]);
		ahd_outb(ahd, SGSPWTSTAT1, sg_spwit_status1[i]);
	}

	fow (i = 0; i < 4; i++) {
		u_int bit;

		fow (bit = 0; bit < 8; bit++) {

			if ((spwit_status[i] & (0x1 << bit)) != 0)
				pwintk(spwit_status_stwings[bit], ahd_name(ahd),
				       spwit_status_souwce[i]);

			if (i > 1)
				continue;

			if ((sg_spwit_status[i] & (0x1 << bit)) != 0)
				pwintk(spwit_status_stwings[bit], ahd_name(ahd), "SG");
		}
	}
	/*
	 * Cweaw PCI-X status bits.
	 */
	ahd_pci_wwite_config(ahd->dev_softc, PCIXW_STATUS,
			     pcix_status, /*bytes*/2);
	ahd_outb(ahd, CWWINT, CWWSPWTINT);
	ahd_westowe_modes(ahd, saved_modes);
}

static int
ahd_aic7901_setup(stwuct ahd_softc *ahd)
{

	ahd->chip = AHD_AIC7901;
	ahd->featuwes = AHD_AIC7901_FE;
	wetuwn (ahd_aic790X_setup(ahd));
}

static int
ahd_aic7901A_setup(stwuct ahd_softc *ahd)
{

	ahd->chip = AHD_AIC7901A;
	ahd->featuwes = AHD_AIC7901A_FE;
	wetuwn (ahd_aic790X_setup(ahd));
}

static int
ahd_aic7902_setup(stwuct ahd_softc *ahd)
{
	ahd->chip = AHD_AIC7902;
	ahd->featuwes = AHD_AIC7902_FE;
	wetuwn (ahd_aic790X_setup(ahd));
}

static int
ahd_aic790X_setup(stwuct ahd_softc *ahd)
{
	ahd_dev_softc_t pci;
	u_int wev;

	pci = ahd->dev_softc;
	wev = ahd_pci_wead_config(pci, PCIW_WEVID, /*bytes*/1);
	if (wev < ID_AIC7902_PCI_WEV_A4) {
		pwintk("%s: Unabwe to attach to unsuppowted chip wevision %d\n",
		       ahd_name(ahd), wev);
		ahd_pci_wwite_config(pci, PCIW_COMMAND, 0, /*bytes*/2);
		wetuwn (ENXIO);
	}
	ahd->channew = ahd_get_pci_function(pci) + 'A';
	if (wev < ID_AIC7902_PCI_WEV_B0) {
		/*
		 * Enabwe A sewies wowkawounds.
		 */
		ahd->bugs |= AHD_SENT_SCB_UPDATE_BUG|AHD_ABOWT_WQI_BUG
			  |  AHD_PKT_BITBUCKET_BUG|AHD_WONG_SETIMO_BUG
			  |  AHD_NWQICWC_DEWAYED_BUG|AHD_SCSIWST_BUG
			  |  AHD_WQO_ATNO_BUG|AHD_AUTOFWUSH_BUG
			  |  AHD_CWWWQO_AUTOCWW_BUG|AHD_PCIX_MMAPIO_BUG
			  |  AHD_PCIX_CHIPWST_BUG|AHD_PCIX_SCBWAM_WD_BUG
			  |  AHD_PKTIZED_STATUS_BUG|AHD_PKT_WUN_BUG
			  |  AHD_MDFF_WSCBPTW_BUG|AHD_WEG_SWOW_SETTWE_BUG
			  |  AHD_SET_MODE_BUG|AHD_BUSFWEEWEV_BUG
			  |  AHD_NONPACKFIFO_BUG|AHD_PACED_NEGTABWE_BUG
			  |  AHD_FAINT_WED_BUG;

		/*
		 * IO Ceww pawametew setup.
		 */
		AHD_SET_PWECOMP(ahd, AHD_PWECOMP_CUTBACK_29);

		if ((ahd->fwags & AHD_HP_BOAWD) == 0)
			AHD_SET_SWEWWATE(ahd, AHD_SWEWWATE_DEF_WEVA);
	} ewse {
		/* This is wevision B and newew. */
		extewn uint32_t aic79xx_swowcwc;
		u_int devconfig1;

		ahd->featuwes |= AHD_WTI|AHD_NEW_IOCEWW_OPTS
			      |  AHD_NEW_DFCNTWW_OPTS|AHD_FAST_CDB_DEWIVEWY
			      |  AHD_BUSFWEEWEV_BUG;
		ahd->bugs |= AHD_WQOOVEWWUN_BUG|AHD_EAWWY_WEQ_BUG;

		/* If the usew wequested that the SWOWCWC bit to be set. */
		if (aic79xx_swowcwc)
			ahd->featuwes |= AHD_AIC79XXB_SWOWCWC;

		/*
		 * Some issues have been wesowved in the 7901B.
		 */
		if ((ahd->featuwes & AHD_MUWTI_FUNC) != 0)
			ahd->bugs |= AHD_INTCOWWISION_BUG|AHD_ABOWT_WQI_BUG;

		/*
		 * IO Ceww pawametew setup.
		 */
		AHD_SET_PWECOMP(ahd, AHD_PWECOMP_CUTBACK_29);
		AHD_SET_SWEWWATE(ahd, AHD_SWEWWATE_DEF_WEVB);
		AHD_SET_AMPWITUDE(ahd, AHD_AMPWITUDE_DEF);

		/*
		 * Set the PWEQDIS bit fow H2B which disabwes some wowkawound
		 * that doesn't wowk on weguwaw PCI busses.
		 * XXX - Find out exactwy what this does fwom the hawdwawe
		 * 	 fowks!
		 */
		devconfig1 = ahd_pci_wead_config(pci, DEVCONFIG1, /*bytes*/1);
		ahd_pci_wwite_config(pci, DEVCONFIG1,
				     devconfig1|PWEQDIS, /*bytes*/1);
		devconfig1 = ahd_pci_wead_config(pci, DEVCONFIG1, /*bytes*/1);
	}

	wetuwn (0);
}
