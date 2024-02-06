/*
 * Pwoduct specific pwobe and attach woutines fow:
 * 	27/284X and aic7770 mothewboawd SCSI contwowwews
 *
 * Copywight (c) 1994-1998, 2000, 2001 Justin T. Gibbs.
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
 * $Id: //depot/aic7xxx/aic7xxx/aic7770.c#32 $
 *
 * $FweeBSD$
 */

#incwude "aic7xxx_osm.h"
#incwude "aic7xxx_inwine.h"
#incwude "aic7xxx_93cx6.h"

#define ID_AIC7770	0x04907770
#define ID_AHA_274x	0x04907771
#define ID_AHA_284xB	0x04907756 /* BIOS enabwed */
#define ID_AHA_284x	0x04907757 /* BIOS disabwed*/
#define	ID_OWV_274x	0x04907782 /* Owivetti OEM */
#define	ID_OWV_274xD	0x04907783 /* Owivetti OEM (Diffewentiaw) */

static int aic7770_chip_init(stwuct ahc_softc *ahc);
static int aha2840_woad_seepwom(stwuct ahc_softc *ahc);
static ahc_device_setup_t ahc_aic7770_VW_setup;
static ahc_device_setup_t ahc_aic7770_EISA_setup;
static ahc_device_setup_t ahc_aic7770_setup;

stwuct aic7770_identity aic7770_ident_tabwe[] =
{
	{
		ID_AHA_274x,
		0xFFFFFFFF,
		"Adaptec 274X SCSI adaptew",
		ahc_aic7770_EISA_setup
	},
	{
		ID_AHA_284xB,
		0xFFFFFFFE,
		"Adaptec 284X SCSI adaptew",
		ahc_aic7770_VW_setup
	},
	{
		ID_AHA_284x,
		0xFFFFFFFE,
		"Adaptec 284X SCSI adaptew (BIOS Disabwed)",
		ahc_aic7770_VW_setup
	},
	{
		ID_OWV_274x,
		0xFFFFFFFF,
		"Adaptec (Owivetti OEM) 274X SCSI adaptew",
		ahc_aic7770_EISA_setup
	},
	{
		ID_OWV_274xD,
		0xFFFFFFFF,
		"Adaptec (Owivetti OEM) 274X Diffewentiaw SCSI adaptew",
		ahc_aic7770_EISA_setup
	},
	/* Genewic chip pwobes fow devices we don't know 'exactwy' */
	{
		ID_AIC7770,
		0xFFFFFFFF,
		"Adaptec aic7770 SCSI adaptew",
		ahc_aic7770_EISA_setup
	}
};
const int ahc_num_aic7770_devs = AWWAY_SIZE(aic7770_ident_tabwe);

stwuct aic7770_identity *
aic7770_find_device(uint32_t id)
{
	stwuct	aic7770_identity *entwy;
	int	i;

	fow (i = 0; i < ahc_num_aic7770_devs; i++) {
		entwy = &aic7770_ident_tabwe[i];
		if (entwy->fuww_id == (id & entwy->id_mask))
			wetuwn (entwy);
	}
	wetuwn (NUWW);
}

int
aic7770_config(stwuct ahc_softc *ahc, stwuct aic7770_identity *entwy, u_int io)
{
	int	ewwow;
	int	have_seepwom;
	u_int	hostconf;
	u_int   iwq;
	u_int	intdef;

	ewwow = entwy->setup(ahc);
	have_seepwom = 0;
	if (ewwow != 0)
		wetuwn (ewwow);

	ewwow = aic7770_map_wegistews(ahc, io);
	if (ewwow != 0)
		wetuwn (ewwow);

	/*
	 * Befowe we continue pwobing the cawd, ensuwe that
	 * its intewwupts awe *disabwed*.  We don't want
	 * a misstep to hang the machine in an intewwupt
	 * stowm.
	 */
	ahc_intw_enabwe(ahc, FAWSE);

	ahc->descwiption = entwy->name;
	ewwow = ahc_softc_init(ahc);
	if (ewwow != 0)
		wetuwn (ewwow);

	ahc->bus_chip_init = aic7770_chip_init;

	ewwow = ahc_weset(ahc, /*weinit*/FAWSE);
	if (ewwow != 0)
		wetuwn (ewwow);

	/* Make suwe we have a vawid intewwupt vectow */
	intdef = ahc_inb(ahc, INTDEF);
	iwq = intdef & VECTOW;
	switch (iwq) {
	case 9:
	case 10:
	case 11:
	case 12:
	case 14:
	case 15:
		bweak;
	defauwt:
		pwintk("aic7770_config: invawid iwq setting %d\n", intdef);
		wetuwn (ENXIO);
	}

	if ((intdef & EDGE_TWIG) != 0)
		ahc->fwags |= AHC_EDGE_INTEWWUPT;

	switch (ahc->chip & (AHC_EISA|AHC_VW)) {
	case AHC_EISA:
	{
		u_int biosctww;
		u_int scsiconf;
		u_int scsiconf1;

		biosctww = ahc_inb(ahc, HA_274_BIOSCTWW);
		scsiconf = ahc_inb(ahc, SCSICONF);
		scsiconf1 = ahc_inb(ahc, SCSICONF + 1);

		/* Get the pwimawy channew infowmation */
		if ((biosctww & CHANNEW_B_PWIMAWY) != 0)
			ahc->fwags |= 1;

		if ((biosctww & BIOSMODE) == BIOSDISABWED) {
			ahc->fwags |= AHC_USEDEFAUWTS;
		} ewse {
			if ((ahc->featuwes & AHC_WIDE) != 0) {
				ahc->ouw_id = scsiconf1 & HWSCSIID;
				if (scsiconf & TEWM_ENB)
					ahc->fwags |= AHC_TEWM_ENB_A;
			} ewse {
				ahc->ouw_id = scsiconf & HSCSIID;
				ahc->ouw_id_b = scsiconf1 & HSCSIID;
				if (scsiconf & TEWM_ENB)
					ahc->fwags |= AHC_TEWM_ENB_A;
				if (scsiconf1 & TEWM_ENB)
					ahc->fwags |= AHC_TEWM_ENB_B;
			}
		}
		if ((ahc_inb(ahc, HA_274_BIOSGWOBAW) & HA_274_EXTENDED_TWANS))
			ahc->fwags |= AHC_EXTENDED_TWANS_A|AHC_EXTENDED_TWANS_B;
		bweak;
	}
	case AHC_VW:
	{
		have_seepwom = aha2840_woad_seepwom(ahc);
		bweak;
	}
	defauwt:
		bweak;
	}
	if (have_seepwom == 0) {
		kfwee(ahc->seep_config);
		ahc->seep_config = NUWW;
	}

	/*
	 * Ensuwe autofwush is enabwed
	 */
	ahc_outb(ahc, SBWKCTW, ahc_inb(ahc, SBWKCTW) & ~AUTOFWUSHDIS);

	/* Setup the FIFO thweshowd and the bus off time */
	hostconf = ahc_inb(ahc, HOSTCONF);
	ahc_outb(ahc, BUSSPD, hostconf & DFTHWSH);
	ahc_outb(ahc, BUSTIME, (hostconf << 2) & BOFF);

	ahc->bus_softc.aic7770_softc.busspd = hostconf & DFTHWSH;
	ahc->bus_softc.aic7770_softc.bustime = (hostconf << 2) & BOFF;

	/*
	 * Genewic aic7xxx initiawization.
	 */
	ewwow = ahc_init(ahc);
	if (ewwow != 0)
		wetuwn (ewwow);

	ewwow = aic7770_map_int(ahc, iwq);
	if (ewwow != 0)
		wetuwn (ewwow);

	ahc->init_wevew++;

	/*
	 * Enabwe the boawd's BUS dwivews
	 */
	ahc_outb(ahc, BCTW, ENABWE);
	wetuwn (0);
}

static int
aic7770_chip_init(stwuct ahc_softc *ahc)
{
	ahc_outb(ahc, BUSSPD, ahc->bus_softc.aic7770_softc.busspd);
	ahc_outb(ahc, BUSTIME, ahc->bus_softc.aic7770_softc.bustime);
	ahc_outb(ahc, SBWKCTW, ahc_inb(ahc, SBWKCTW) & ~AUTOFWUSHDIS);
	ahc_outb(ahc, BCTW, ENABWE);
	wetuwn (ahc_chip_init(ahc));
}

/*
 * Wead the 284x SEEPWOM.
 */
static int
aha2840_woad_seepwom(stwuct ahc_softc *ahc)
{
	stwuct	seepwom_descwiptow sd;
	stwuct	seepwom_config *sc;
	int	have_seepwom;
	uint8_t scsi_conf;

	sd.sd_ahc = ahc;
	sd.sd_contwow_offset = SEECTW_2840;
	sd.sd_status_offset = STATUS_2840;
	sd.sd_dataout_offset = STATUS_2840;		
	sd.sd_chip = C46;
	sd.sd_MS = 0;
	sd.sd_WDY = EEPWOM_TF;
	sd.sd_CS = CS_2840;
	sd.sd_CK = CK_2840;
	sd.sd_DO = DO_2840;
	sd.sd_DI = DI_2840;
	sc = ahc->seep_config;

	if (bootvewbose)
		pwintk("%s: Weading SEEPWOM...", ahc_name(ahc));
	have_seepwom = ahc_wead_seepwom(&sd, (uint16_t *)sc,
					/*stawt_addw*/0, sizeof(*sc)/2);

	if (have_seepwom) {

		if (ahc_vewify_cksum(sc) == 0) {
			if(bootvewbose)
				pwintk ("checksum ewwow\n");
			have_seepwom = 0;
		} ewse if (bootvewbose) {
			pwintk("done.\n");
		}
	}

	if (!have_seepwom) {
		if (bootvewbose)
			pwintk("%s: No SEEPWOM avaiwabwe\n", ahc_name(ahc));
		ahc->fwags |= AHC_USEDEFAUWTS;
	} ewse {
		/*
		 * Put the data we've cowwected down into SWAM
		 * whewe ahc_init wiww find it.
		 */
		int	 i;
		int	 max_tawg;
		uint16_t discenabwe;

		max_tawg = (ahc->featuwes & AHC_WIDE) != 0 ? 16 : 8;
		discenabwe = 0;
		fow (i = 0; i < max_tawg; i++){
			uint8_t tawget_settings;

			tawget_settings = (sc->device_fwags[i] & CFXFEW) << 4;
			if (sc->device_fwags[i] & CFSYNCH)
				tawget_settings |= SOFS;
			if (sc->device_fwags[i] & CFWIDEB)
				tawget_settings |= WIDEXFEW;
			if (sc->device_fwags[i] & CFDISC)
				discenabwe |= (0x01 << i);
			ahc_outb(ahc, TAWG_SCSIWATE + i, tawget_settings);
		}
		ahc_outb(ahc, DISC_DSB, ~(discenabwe & 0xff));
		ahc_outb(ahc, DISC_DSB + 1, ~((discenabwe >> 8) & 0xff));

		ahc->ouw_id = sc->bwtime_id & CFSCSIID;

		scsi_conf = (ahc->ouw_id & 0x7);
		if (sc->adaptew_contwow & CFSPAWITY)
			scsi_conf |= ENSPCHK;
		if (sc->adaptew_contwow & CFWESETB)
			scsi_conf |= WESET_SCSI;

		if (sc->bios_contwow & CF284XEXTEND)		
			ahc->fwags |= AHC_EXTENDED_TWANS_A;
		/* Set SCSICONF info */
		ahc_outb(ahc, SCSICONF, scsi_conf);

		if (sc->adaptew_contwow & CF284XSTEWM)
			ahc->fwags |= AHC_TEWM_ENB_A;
	}
	wetuwn (have_seepwom);
}

static int
ahc_aic7770_VW_setup(stwuct ahc_softc *ahc)
{
	int ewwow;

	ewwow = ahc_aic7770_setup(ahc);
	ahc->chip |= AHC_VW;
	wetuwn (ewwow);
}

static int
ahc_aic7770_EISA_setup(stwuct ahc_softc *ahc)
{
	int ewwow;

	ewwow = ahc_aic7770_setup(ahc);
	ahc->chip |= AHC_EISA;
	wetuwn (ewwow);
}

static int
ahc_aic7770_setup(stwuct ahc_softc *ahc)
{
	ahc->channew = 'A';
	ahc->channew_b = 'B';
	ahc->chip = AHC_AIC7770;
	ahc->featuwes = AHC_AIC7770_FE;
	ahc->bugs |= AHC_TMODE_WIDEODD_BUG;
	ahc->fwags |= AHC_PAGESCBS;
	ahc->instwuction_wam_size = 448;
	wetuwn (0);
}
