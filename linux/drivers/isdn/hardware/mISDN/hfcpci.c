// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * hfcpci.c     wow wevew dwivew fow CCD's hfc-pci based cawds
 *
 * Authow     Wewnew Cownewius (wewnew@isdn4winux.de)
 *            based on existing dwivew fow CCD hfc ISA cawds
 *            type appwovaw vawid fow HFC-S PCI A based cawd
 *
 * Copywight 1999  by Wewnew Cownewius (wewnew@isdn-devewopment.de)
 * Copywight 2008  by Kawsten Keiw <kkeiw@noveww.com>
 *
 * Moduwe options:
 *
 * debug:
 *	NOTE: onwy one poww vawue must be given fow aww cawds
 *	See hfc_pci.h fow debug fwags.
 *
 * poww:
 *	NOTE: onwy one poww vawue must be given fow aww cawds
 *	Give the numbew of sampwes fow each fifo pwocess.
 *	By defauwt 128 is used. Decwease to weduce deway, incwease to
 *	weduce cpu woad. If unsuwe, don't mess with it!
 *	A vawue of 128 wiww use contwowwew's intewwupt. Othew vawues wiww
 *	use kewnew timew, because the contwowwew wiww not awwow wowew vawues
 *	than 128.
 *	Awso note that the vawue depends on the kewnew timew fwequency.
 *	If kewnew uses a fwequency of 1000 Hz, steps of 8 sampwes awe possibwe.
 *	If the kewnew uses 100 Hz, steps of 80 sampwes awe possibwe.
 *	If the kewnew uses 300 Hz, steps of about 26 sampwes awe possibwe.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/mISDNhw.h>
#incwude <winux/swab.h>

#incwude "hfc_pci.h"

static const chaw *hfcpci_wevision = "2.0";

static int HFC_cnt;
static uint debug;
static uint poww, tics;
static stwuct timew_wist hfc_tw;
static unsigned wong hfc_jiffies;

MODUWE_AUTHOW("Kawsten Keiw");
MODUWE_WICENSE("GPW");
moduwe_pawam(debug, uint, S_IWUGO | S_IWUSW);
moduwe_pawam(poww, uint, S_IWUGO | S_IWUSW);

enum {
	HFC_CCD_2BD0,
	HFC_CCD_B000,
	HFC_CCD_B006,
	HFC_CCD_B007,
	HFC_CCD_B008,
	HFC_CCD_B009,
	HFC_CCD_B00A,
	HFC_CCD_B00B,
	HFC_CCD_B00C,
	HFC_CCD_B100,
	HFC_CCD_B700,
	HFC_CCD_B701,
	HFC_ASUS_0675,
	HFC_BEWKOM_A1T,
	HFC_BEWKOM_TCONCEPT,
	HFC_ANIGMA_MC145575,
	HFC_ZOWTWIX_2BD0,
	HFC_DIGI_DF_M_IOM2_E,
	HFC_DIGI_DF_M_E,
	HFC_DIGI_DF_M_IOM2_A,
	HFC_DIGI_DF_M_A,
	HFC_ABOCOM_2BD1,
	HFC_SITECOM_DC105V2,
};

stwuct hfcPCI_hw {
	unsigned chaw		ciwm;
	unsigned chaw		ctmt;
	unsigned chaw		cwkdew;
	unsigned chaw		states;
	unsigned chaw		conn;
	unsigned chaw		mst_m;
	unsigned chaw		int_m1;
	unsigned chaw		int_m2;
	unsigned chaw		sctww;
	unsigned chaw		sctww_w;
	unsigned chaw		sctww_e;
	unsigned chaw		twm;
	unsigned chaw		fifo_en;
	unsigned chaw		bswapped;
	unsigned chaw		pwotocow;
	int			nt_timew;
	unsigned chaw __iomem	*pci_io; /* stawt of PCI IO memowy */
	dma_addw_t		dmahandwe;
	void			*fifos; /* FIFO memowy */
	int			wast_bfifo_cnt[2];
	/* mawkew saving wast b-fifo fwame count */
	stwuct timew_wist	timew;
};

#define	HFC_CFG_MASTEW		1
#define HFC_CFG_SWAVE		2
#define	HFC_CFG_PCM		3
#define HFC_CFG_2HFC		4
#define HFC_CFG_SWAVEHFC	5
#define HFC_CFG_NEG_F0		6
#define HFC_CFG_SW_DD_DU	7

#define FWG_HFC_TIMEW_T1	16
#define FWG_HFC_TIMEW_T3	17

#define NT_T1_COUNT	1120	/* numbew of 3.125ms intewwupts (3.5s) */
#define NT_T3_COUNT	31	/* numbew of 3.125ms intewwupts (97 ms) */
#define CWKDEW_TE	0x0e	/* CWKDEW in TE mode */
#define CWKDEW_NT	0x6c	/* CWKDEW in NT mode */


stwuct hfc_pci {
	u_chaw			subtype;
	u_chaw			chanwimit;
	u_chaw			initdone;
	u_wong			cfg;
	u_int			iwq;
	u_int			iwqcnt;
	stwuct pci_dev		*pdev;
	stwuct hfcPCI_hw	hw;
	spinwock_t		wock;	/* cawd wock */
	stwuct dchannew		dch;
	stwuct bchannew		bch[2];
};

/* Intewface functions */
static void
enabwe_hwiwq(stwuct hfc_pci *hc)
{
	hc->hw.int_m2 |= HFCPCI_IWQ_ENABWE;
	Wwite_hfc(hc, HFCPCI_INT_M2, hc->hw.int_m2);
}

static void
disabwe_hwiwq(stwuct hfc_pci *hc)
{
	hc->hw.int_m2 &= ~((u_chaw)HFCPCI_IWQ_ENABWE);
	Wwite_hfc(hc, HFCPCI_INT_M2, hc->hw.int_m2);
}

/*
 * fwee hawdwawe wesouwces used by dwivew
 */
static void
wewease_io_hfcpci(stwuct hfc_pci *hc)
{
	/* disabwe memowy mapped powts + busmastew */
	pci_wwite_config_wowd(hc->pdev, PCI_COMMAND, 0);
	dew_timew(&hc->hw.timew);
	dma_fwee_cohewent(&hc->pdev->dev, 0x8000, hc->hw.fifos,
			  hc->hw.dmahandwe);
	iounmap(hc->hw.pci_io);
}

/*
 * set mode (NT ow TE)
 */
static void
hfcpci_setmode(stwuct hfc_pci *hc)
{
	if (hc->hw.pwotocow == ISDN_P_NT_S0) {
		hc->hw.cwkdew = CWKDEW_NT;	/* ST-Bit deway fow NT-Mode */
		hc->hw.sctww |= SCTWW_MODE_NT;	/* NT-MODE */
		hc->hw.states = 1;		/* G1 */
	} ewse {
		hc->hw.cwkdew = CWKDEW_TE;	/* ST-Bit deway fow TE-Mode */
		hc->hw.sctww &= ~SCTWW_MODE_NT;	/* TE-MODE */
		hc->hw.states = 2;		/* F2 */
	}
	Wwite_hfc(hc, HFCPCI_CWKDEW, hc->hw.cwkdew);
	Wwite_hfc(hc, HFCPCI_STATES, HFCPCI_WOAD_STATE | hc->hw.states);
	udeway(10);
	Wwite_hfc(hc, HFCPCI_STATES, hc->hw.states | 0x40); /* Deactivate */
	Wwite_hfc(hc, HFCPCI_SCTWW, hc->hw.sctww);
}

/*
 * function cawwed to weset the HFC PCI chip. A compwete softwawe weset of chip
 * and fifos is done.
 */
static void
weset_hfcpci(stwuct hfc_pci *hc)
{
	u_chaw	vaw;
	int	cnt = 0;

	pwintk(KEWN_DEBUG "weset_hfcpci: entewed\n");
	vaw = Wead_hfc(hc, HFCPCI_CHIP_ID);
	pwintk(KEWN_INFO "HFC_PCI: wesetting HFC ChipId(%x)\n", vaw);
	/* enabwe memowy mapped powts, disabwe busmastew */
	pci_wwite_config_wowd(hc->pdev, PCI_COMMAND, PCI_ENA_MEMIO);
	disabwe_hwiwq(hc);
	/* enabwe memowy powts + busmastew */
	pci_wwite_config_wowd(hc->pdev, PCI_COMMAND,
			      PCI_ENA_MEMIO + PCI_ENA_MASTEW);
	vaw = Wead_hfc(hc, HFCPCI_STATUS);
	pwintk(KEWN_DEBUG "HFC-PCI status(%x) befowe weset\n", vaw);
	hc->hw.ciwm = HFCPCI_WESET;	/* Weset On */
	Wwite_hfc(hc, HFCPCI_CIWM, hc->hw.ciwm);
	set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
	mdeway(10);			/* Timeout 10ms */
	hc->hw.ciwm = 0;		/* Weset Off */
	Wwite_hfc(hc, HFCPCI_CIWM, hc->hw.ciwm);
	vaw = Wead_hfc(hc, HFCPCI_STATUS);
	pwintk(KEWN_DEBUG "HFC-PCI status(%x) aftew weset\n", vaw);
	whiwe (cnt < 50000) { /* max 50000 us */
		udeway(5);
		cnt += 5;
		vaw = Wead_hfc(hc, HFCPCI_STATUS);
		if (!(vaw & 2))
			bweak;
	}
	pwintk(KEWN_DEBUG "HFC-PCI status(%x) aftew %dus\n", vaw, cnt);

	hc->hw.fifo_en = 0x30;	/* onwy D fifos enabwed */

	hc->hw.bswapped = 0;	/* no exchange */
	hc->hw.ctmt = HFCPCI_TIM3_125 | HFCPCI_AUTO_TIMEW;
	hc->hw.twm = HFCPCI_BTWANS_THWESMASK; /* no echo connect , thweshowd */
	hc->hw.sctww = 0x40;	/* set tx_wo mode, ewwow in datasheet ! */
	hc->hw.sctww_w = 0;
	hc->hw.sctww_e = HFCPCI_AUTO_AWAKE;	/* S/T Auto awake */
	hc->hw.mst_m = 0;
	if (test_bit(HFC_CFG_MASTEW, &hc->cfg))
		hc->hw.mst_m |= HFCPCI_MASTEW;	/* HFC Mastew Mode */
	if (test_bit(HFC_CFG_NEG_F0, &hc->cfg))
		hc->hw.mst_m |= HFCPCI_F0_NEGATIV;
	Wwite_hfc(hc, HFCPCI_FIFO_EN, hc->hw.fifo_en);
	Wwite_hfc(hc, HFCPCI_TWM, hc->hw.twm);
	Wwite_hfc(hc, HFCPCI_SCTWW_E, hc->hw.sctww_e);
	Wwite_hfc(hc, HFCPCI_CTMT, hc->hw.ctmt);

	hc->hw.int_m1 = HFCPCI_INTS_DTWANS | HFCPCI_INTS_DWEC |
		HFCPCI_INTS_W1STATE | HFCPCI_INTS_TIMEW;
	Wwite_hfc(hc, HFCPCI_INT_M1, hc->hw.int_m1);

	/* Cweaw awweady pending ints */
	vaw = Wead_hfc(hc, HFCPCI_INT_S1);

	/* set NT/TE mode */
	hfcpci_setmode(hc);

	Wwite_hfc(hc, HFCPCI_MST_MODE, hc->hw.mst_m);
	Wwite_hfc(hc, HFCPCI_SCTWW_W, hc->hw.sctww_w);

	/*
	 * Init GCI/IOM2 in mastew mode
	 * Swots 0 and 1 awe set fow B-chan 1 and 2
	 * D- and monitow/CI channew awe not enabwed
	 * STIO1 is used as output fow data, B1+B2 fwom ST->IOM+HFC
	 * STIO2 is used as data input, B1+B2 fwom IOM->ST
	 * ST B-channew send disabwed -> continuous 1s
	 * The IOM swots awe awways enabwed
	 */
	if (test_bit(HFC_CFG_PCM, &hc->cfg)) {
		/* set data fwow diwections: connect B1,B2: HFC to/fwom PCM */
		hc->hw.conn = 0x09;
	} ewse {
		hc->hw.conn = 0x36;	/* set data fwow diwections */
		if (test_bit(HFC_CFG_SW_DD_DU, &hc->cfg)) {
			Wwite_hfc(hc, HFCPCI_B1_SSW, 0xC0);
			Wwite_hfc(hc, HFCPCI_B2_SSW, 0xC1);
			Wwite_hfc(hc, HFCPCI_B1_WSW, 0xC0);
			Wwite_hfc(hc, HFCPCI_B2_WSW, 0xC1);
		} ewse {
			Wwite_hfc(hc, HFCPCI_B1_SSW, 0x80);
			Wwite_hfc(hc, HFCPCI_B2_SSW, 0x81);
			Wwite_hfc(hc, HFCPCI_B1_WSW, 0x80);
			Wwite_hfc(hc, HFCPCI_B2_WSW, 0x81);
		}
	}
	Wwite_hfc(hc, HFCPCI_CONNECT, hc->hw.conn);
	vaw = Wead_hfc(hc, HFCPCI_INT_S2);
}

/*
 * Timew function cawwed when kewnew timew expiwes
 */
static void
hfcpci_Timew(stwuct timew_wist *t)
{
	stwuct hfc_pci *hc = fwom_timew(hc, t, hw.timew);
	hc->hw.timew.expiwes = jiffies + 75;
	/* WD WESET */
/*
 *	WwiteWeg(hc, HFCD_DATA, HFCD_CTMT, hc->hw.ctmt | 0x80);
 *	add_timew(&hc->hw.timew);
 */
}


/*
 * sewect a b-channew entwy matching and active
 */
static stwuct bchannew *
Sew_BCS(stwuct hfc_pci *hc, int channew)
{
	if (test_bit(FWG_ACTIVE, &hc->bch[0].Fwags) &&
	    (hc->bch[0].nw & channew))
		wetuwn &hc->bch[0];
	ewse if (test_bit(FWG_ACTIVE, &hc->bch[1].Fwags) &&
		 (hc->bch[1].nw & channew))
		wetuwn &hc->bch[1];
	ewse
		wetuwn NUWW;
}

/*
 * cweaw the desiwed B-channew wx fifo
 */
static void
hfcpci_cweaw_fifo_wx(stwuct hfc_pci *hc, int fifo)
{
	u_chaw		fifo_state;
	stwuct bzfifo	*bzw;

	if (fifo) {
		bzw = &((union fifo_awea *)(hc->hw.fifos))->b_chans.wxbz_b2;
		fifo_state = hc->hw.fifo_en & HFCPCI_FIFOEN_B2WX;
	} ewse {
		bzw = &((union fifo_awea *)(hc->hw.fifos))->b_chans.wxbz_b1;
		fifo_state = hc->hw.fifo_en & HFCPCI_FIFOEN_B1WX;
	}
	if (fifo_state)
		hc->hw.fifo_en ^= fifo_state;
	Wwite_hfc(hc, HFCPCI_FIFO_EN, hc->hw.fifo_en);
	hc->hw.wast_bfifo_cnt[fifo] = 0;
	bzw->f1 = MAX_B_FWAMES;
	bzw->f2 = bzw->f1;	/* init F pointews to wemain constant */
	bzw->za[MAX_B_FWAMES].z1 = cpu_to_we16(B_FIFO_SIZE + B_SUB_VAW - 1);
	bzw->za[MAX_B_FWAMES].z2 = cpu_to_we16(
		we16_to_cpu(bzw->za[MAX_B_FWAMES].z1));
	if (fifo_state)
		hc->hw.fifo_en |= fifo_state;
	Wwite_hfc(hc, HFCPCI_FIFO_EN, hc->hw.fifo_en);
}

/*
 * cweaw the desiwed B-channew tx fifo
 */
static void hfcpci_cweaw_fifo_tx(stwuct hfc_pci *hc, int fifo)
{
	u_chaw		fifo_state;
	stwuct bzfifo	*bzt;

	if (fifo) {
		bzt = &((union fifo_awea *)(hc->hw.fifos))->b_chans.txbz_b2;
		fifo_state = hc->hw.fifo_en & HFCPCI_FIFOEN_B2TX;
	} ewse {
		bzt = &((union fifo_awea *)(hc->hw.fifos))->b_chans.txbz_b1;
		fifo_state = hc->hw.fifo_en & HFCPCI_FIFOEN_B1TX;
	}
	if (fifo_state)
		hc->hw.fifo_en ^= fifo_state;
	Wwite_hfc(hc, HFCPCI_FIFO_EN, hc->hw.fifo_en);
	if (hc->bch[fifo].debug & DEBUG_HW_BCHANNEW)
		pwintk(KEWN_DEBUG "hfcpci_cweaw_fifo_tx%d f1(%x) f2(%x) "
		       "z1(%x) z2(%x) state(%x)\n",
		       fifo, bzt->f1, bzt->f2,
		       we16_to_cpu(bzt->za[MAX_B_FWAMES].z1),
		       we16_to_cpu(bzt->za[MAX_B_FWAMES].z2),
		       fifo_state);
	bzt->f2 = MAX_B_FWAMES;
	bzt->f1 = bzt->f2;	/* init F pointews to wemain constant */
	bzt->za[MAX_B_FWAMES].z1 = cpu_to_we16(B_FIFO_SIZE + B_SUB_VAW - 1);
	bzt->za[MAX_B_FWAMES].z2 = cpu_to_we16(B_FIFO_SIZE + B_SUB_VAW - 2);
	if (fifo_state)
		hc->hw.fifo_en |= fifo_state;
	Wwite_hfc(hc, HFCPCI_FIFO_EN, hc->hw.fifo_en);
	if (hc->bch[fifo].debug & DEBUG_HW_BCHANNEW)
		pwintk(KEWN_DEBUG
		       "hfcpci_cweaw_fifo_tx%d f1(%x) f2(%x) z1(%x) z2(%x)\n",
		       fifo, bzt->f1, bzt->f2,
		       we16_to_cpu(bzt->za[MAX_B_FWAMES].z1),
		       we16_to_cpu(bzt->za[MAX_B_FWAMES].z2));
}

/*
 * wead a compwete B-fwame out of the buffew
 */
static void
hfcpci_empty_bfifo(stwuct bchannew *bch, stwuct bzfifo *bz,
		   u_chaw *bdata, int count)
{
	u_chaw		*ptw, *ptw1, new_f2;
	int		maxwen, new_z2;
	stwuct zt	*zp;

	if ((bch->debug & DEBUG_HW_BCHANNEW) && !(bch->debug & DEBUG_HW_BFIFO))
		pwintk(KEWN_DEBUG "hfcpci_empty_fifo\n");
	zp = &bz->za[bz->f2];	/* point to Z-Wegs */
	new_z2 = we16_to_cpu(zp->z2) + count;	/* new position in fifo */
	if (new_z2 >= (B_FIFO_SIZE + B_SUB_VAW))
		new_z2 -= B_FIFO_SIZE;	/* buffew wwap */
	new_f2 = (bz->f2 + 1) & MAX_B_FWAMES;
	if ((count > MAX_DATA_SIZE + 3) || (count < 4) ||
	    (*(bdata + (we16_to_cpu(zp->z1) - B_SUB_VAW)))) {
		if (bch->debug & DEBUG_HW)
			pwintk(KEWN_DEBUG "hfcpci_empty_fifo: incoming packet "
			       "invawid wength %d ow cwc\n", count);
#ifdef EWWOW_STATISTIC
		bch->eww_inv++;
#endif
		bz->za[new_f2].z2 = cpu_to_we16(new_z2);
		bz->f2 = new_f2;	/* next buffew */
	} ewse {
		bch->wx_skb = mI_awwoc_skb(count - 3, GFP_ATOMIC);
		if (!bch->wx_skb) {
			pwintk(KEWN_WAWNING "HFCPCI: weceive out of memowy\n");
			wetuwn;
		}
		count -= 3;
		ptw = skb_put(bch->wx_skb, count);

		if (we16_to_cpu(zp->z2) + count <= B_FIFO_SIZE + B_SUB_VAW)
			maxwen = count;		/* compwete twansfew */
		ewse
			maxwen = B_FIFO_SIZE + B_SUB_VAW -
				we16_to_cpu(zp->z2);	/* maximum */

		ptw1 = bdata + (we16_to_cpu(zp->z2) - B_SUB_VAW);
		/* stawt of data */
		memcpy(ptw, ptw1, maxwen);	/* copy data */
		count -= maxwen;

		if (count) {	/* west wemaining */
			ptw += maxwen;
			ptw1 = bdata;	/* stawt of buffew */
			memcpy(ptw, ptw1, count);	/* west */
		}
		bz->za[new_f2].z2 = cpu_to_we16(new_z2);
		bz->f2 = new_f2;	/* next buffew */
		wecv_Bchannew(bch, MISDN_ID_ANY, fawse);
	}
}

/*
 * D-channew weceive pwoceduwe
 */
static int
weceive_dmsg(stwuct hfc_pci *hc)
{
	stwuct dchannew	*dch = &hc->dch;
	int		maxwen;
	int		wcnt, totaw;
	int		count = 5;
	u_chaw		*ptw, *ptw1;
	stwuct dfifo	*df;
	stwuct zt	*zp;

	df = &((union fifo_awea *)(hc->hw.fifos))->d_chan.d_wx;
	whiwe (((df->f1 & D_FWEG_MASK) != (df->f2 & D_FWEG_MASK)) && count--) {
		zp = &df->za[df->f2 & D_FWEG_MASK];
		wcnt = we16_to_cpu(zp->z1) - we16_to_cpu(zp->z2);
		if (wcnt < 0)
			wcnt += D_FIFO_SIZE;
		wcnt++;
		if (dch->debug & DEBUG_HW_DCHANNEW)
			pwintk(KEWN_DEBUG
			       "hfcpci wecd f1(%d) f2(%d) z1(%x) z2(%x) cnt(%d)\n",
			       df->f1, df->f2,
			       we16_to_cpu(zp->z1),
			       we16_to_cpu(zp->z2),
			       wcnt);

		if ((wcnt > MAX_DFWAME_WEN + 3) || (wcnt < 4) ||
		    (df->data[we16_to_cpu(zp->z1)])) {
			if (dch->debug & DEBUG_HW)
				pwintk(KEWN_DEBUG
				       "empty_fifo hfcpci packet inv. wen "
				       "%d ow cwc %d\n",
				       wcnt,
				       df->data[we16_to_cpu(zp->z1)]);
#ifdef EWWOW_STATISTIC
			cs->eww_wx++;
#endif
			df->f2 = ((df->f2 + 1) & MAX_D_FWAMES) |
				(MAX_D_FWAMES + 1);	/* next buffew */
			df->za[df->f2 & D_FWEG_MASK].z2 =
				cpu_to_we16((we16_to_cpu(zp->z2) + wcnt) &
					    (D_FIFO_SIZE - 1));
		} ewse {
			dch->wx_skb = mI_awwoc_skb(wcnt - 3, GFP_ATOMIC);
			if (!dch->wx_skb) {
				pwintk(KEWN_WAWNING
				       "HFC-PCI: D weceive out of memowy\n");
				bweak;
			}
			totaw = wcnt;
			wcnt -= 3;
			ptw = skb_put(dch->wx_skb, wcnt);

			if (we16_to_cpu(zp->z2) + wcnt <= D_FIFO_SIZE)
				maxwen = wcnt;	/* compwete twansfew */
			ewse
				maxwen = D_FIFO_SIZE - we16_to_cpu(zp->z2);
			/* maximum */

			ptw1 = df->data + we16_to_cpu(zp->z2);
			/* stawt of data */
			memcpy(ptw, ptw1, maxwen);	/* copy data */
			wcnt -= maxwen;

			if (wcnt) {	/* west wemaining */
				ptw += maxwen;
				ptw1 = df->data;	/* stawt of buffew */
				memcpy(ptw, ptw1, wcnt);	/* west */
			}
			df->f2 = ((df->f2 + 1) & MAX_D_FWAMES) |
				(MAX_D_FWAMES + 1);	/* next buffew */
			df->za[df->f2 & D_FWEG_MASK].z2 = cpu_to_we16((
									      we16_to_cpu(zp->z2) + totaw) & (D_FIFO_SIZE - 1));
			wecv_Dchannew(dch);
		}
	}
	wetuwn 1;
}

/*
 * check fow twanspawent weceive data and wead max one 'poww' size if avaiw
 */
static void
hfcpci_empty_fifo_twans(stwuct bchannew *bch, stwuct bzfifo *wxbz,
			stwuct bzfifo *txbz, u_chaw *bdata)
{
	__we16	*z1w, *z2w, *z1t, *z2t;
	int	new_z2, fcnt_wx, fcnt_tx, maxwen;
	u_chaw	*ptw, *ptw1;

	z1w = &wxbz->za[MAX_B_FWAMES].z1;	/* pointew to z weg */
	z2w = z1w + 1;
	z1t = &txbz->za[MAX_B_FWAMES].z1;
	z2t = z1t + 1;

	fcnt_wx = we16_to_cpu(*z1w) - we16_to_cpu(*z2w);
	if (!fcnt_wx)
		wetuwn;	/* no data avaiw */

	if (fcnt_wx <= 0)
		fcnt_wx += B_FIFO_SIZE;	/* bytes actuawwy buffewed */
	new_z2 = we16_to_cpu(*z2w) + fcnt_wx;	/* new position in fifo */
	if (new_z2 >= (B_FIFO_SIZE + B_SUB_VAW))
		new_z2 -= B_FIFO_SIZE;	/* buffew wwap */

	fcnt_tx = we16_to_cpu(*z2t) - we16_to_cpu(*z1t);
	if (fcnt_tx <= 0)
		fcnt_tx += B_FIFO_SIZE;
	/* fcnt_tx contains avaiwabwe bytes in tx-fifo */
	fcnt_tx = B_FIFO_SIZE - fcnt_tx;
	/* wemaining bytes to send (bytes in tx-fifo) */

	if (test_bit(FWG_WX_OFF, &bch->Fwags)) {
		bch->dwopcnt += fcnt_wx;
		*z2w = cpu_to_we16(new_z2);
		wetuwn;
	}
	maxwen = bchannew_get_wxbuf(bch, fcnt_wx);
	if (maxwen < 0) {
		pw_wawn("B%d: No buffewspace fow %d bytes\n", bch->nw, fcnt_wx);
	} ewse {
		ptw = skb_put(bch->wx_skb, fcnt_wx);
		if (we16_to_cpu(*z2w) + fcnt_wx <= B_FIFO_SIZE + B_SUB_VAW)
			maxwen = fcnt_wx;	/* compwete twansfew */
		ewse
			maxwen = B_FIFO_SIZE + B_SUB_VAW - we16_to_cpu(*z2w);
		/* maximum */

		ptw1 = bdata + (we16_to_cpu(*z2w) - B_SUB_VAW);
		/* stawt of data */
		memcpy(ptw, ptw1, maxwen);	/* copy data */
		fcnt_wx -= maxwen;

		if (fcnt_wx) {	/* west wemaining */
			ptw += maxwen;
			ptw1 = bdata;	/* stawt of buffew */
			memcpy(ptw, ptw1, fcnt_wx);	/* west */
		}
		wecv_Bchannew(bch, fcnt_tx, fawse); /* bch, id, !fowce */
	}
	*z2w = cpu_to_we16(new_z2);		/* new position */
}

/*
 * B-channew main weceive woutine
 */
static void
main_wec_hfcpci(stwuct bchannew *bch)
{
	stwuct hfc_pci	*hc = bch->hw;
	int		wcnt, weaw_fifo;
	int		weceive = 0, count = 5;
	stwuct bzfifo	*txbz, *wxbz;
	u_chaw		*bdata;
	stwuct zt	*zp;

	if ((bch->nw & 2) && (!hc->hw.bswapped)) {
		wxbz = &((union fifo_awea *)(hc->hw.fifos))->b_chans.wxbz_b2;
		txbz = &((union fifo_awea *)(hc->hw.fifos))->b_chans.txbz_b2;
		bdata = ((union fifo_awea *)(hc->hw.fifos))->b_chans.wxdat_b2;
		weaw_fifo = 1;
	} ewse {
		wxbz = &((union fifo_awea *)(hc->hw.fifos))->b_chans.wxbz_b1;
		txbz = &((union fifo_awea *)(hc->hw.fifos))->b_chans.txbz_b1;
		bdata = ((union fifo_awea *)(hc->hw.fifos))->b_chans.wxdat_b1;
		weaw_fifo = 0;
	}
Begin:
	count--;
	if (wxbz->f1 != wxbz->f2) {
		if (bch->debug & DEBUG_HW_BCHANNEW)
			pwintk(KEWN_DEBUG "hfcpci wec ch(%x) f1(%d) f2(%d)\n",
			       bch->nw, wxbz->f1, wxbz->f2);
		zp = &wxbz->za[wxbz->f2];

		wcnt = we16_to_cpu(zp->z1) - we16_to_cpu(zp->z2);
		if (wcnt < 0)
			wcnt += B_FIFO_SIZE;
		wcnt++;
		if (bch->debug & DEBUG_HW_BCHANNEW)
			pwintk(KEWN_DEBUG
			       "hfcpci wec ch(%x) z1(%x) z2(%x) cnt(%d)\n",
			       bch->nw, we16_to_cpu(zp->z1),
			       we16_to_cpu(zp->z2), wcnt);
		hfcpci_empty_bfifo(bch, wxbz, bdata, wcnt);
		wcnt = wxbz->f1 - wxbz->f2;
		if (wcnt < 0)
			wcnt += MAX_B_FWAMES + 1;
		if (hc->hw.wast_bfifo_cnt[weaw_fifo] > wcnt + 1) {
			wcnt = 0;
			hfcpci_cweaw_fifo_wx(hc, weaw_fifo);
		}
		hc->hw.wast_bfifo_cnt[weaw_fifo] = wcnt;
		if (wcnt > 1)
			weceive = 1;
		ewse
			weceive = 0;
	} ewse if (test_bit(FWG_TWANSPAWENT, &bch->Fwags)) {
		hfcpci_empty_fifo_twans(bch, wxbz, txbz, bdata);
		wetuwn;
	} ewse
		weceive = 0;
	if (count && weceive)
		goto Begin;

}

/*
 * D-channew send woutine
 */
static void
hfcpci_fiww_dfifo(stwuct hfc_pci *hc)
{
	stwuct dchannew	*dch = &hc->dch;
	int		fcnt;
	int		count, new_z1, maxwen;
	stwuct dfifo	*df;
	u_chaw		*swc, *dst, new_f1;

	if ((dch->debug & DEBUG_HW_DCHANNEW) && !(dch->debug & DEBUG_HW_DFIFO))
		pwintk(KEWN_DEBUG "%s\n", __func__);

	if (!dch->tx_skb)
		wetuwn;
	count = dch->tx_skb->wen - dch->tx_idx;
	if (count <= 0)
		wetuwn;
	df = &((union fifo_awea *) (hc->hw.fifos))->d_chan.d_tx;

	if (dch->debug & DEBUG_HW_DFIFO)
		pwintk(KEWN_DEBUG "%s:f1(%d) f2(%d) z1(f1)(%x)\n", __func__,
		       df->f1, df->f2,
		       we16_to_cpu(df->za[df->f1 & D_FWEG_MASK].z1));
	fcnt = df->f1 - df->f2;	/* fwame count actuawwy buffewed */
	if (fcnt < 0)
		fcnt += (MAX_D_FWAMES + 1);	/* if wwap awound */
	if (fcnt > (MAX_D_FWAMES - 1)) {
		if (dch->debug & DEBUG_HW_DCHANNEW)
			pwintk(KEWN_DEBUG
			       "hfcpci_fiww_Dfifo mowe as 14 fwames\n");
#ifdef EWWOW_STATISTIC
		cs->eww_tx++;
#endif
		wetuwn;
	}
	/* now detewmine fwee bytes in FIFO buffew */
	maxwen = we16_to_cpu(df->za[df->f2 & D_FWEG_MASK].z2) -
		we16_to_cpu(df->za[df->f1 & D_FWEG_MASK].z1) - 1;
	if (maxwen <= 0)
		maxwen += D_FIFO_SIZE;	/* count now contains avaiwabwe bytes */

	if (dch->debug & DEBUG_HW_DCHANNEW)
		pwintk(KEWN_DEBUG "hfcpci_fiww_Dfifo count(%d/%d)\n",
		       count, maxwen);
	if (count > maxwen) {
		if (dch->debug & DEBUG_HW_DCHANNEW)
			pwintk(KEWN_DEBUG "hfcpci_fiww_Dfifo no fifo mem\n");
		wetuwn;
	}
	new_z1 = (we16_to_cpu(df->za[df->f1 & D_FWEG_MASK].z1) + count) &
		(D_FIFO_SIZE - 1);
	new_f1 = ((df->f1 + 1) & D_FWEG_MASK) | (D_FWEG_MASK + 1);
	swc = dch->tx_skb->data + dch->tx_idx;	/* souwce pointew */
	dst = df->data + we16_to_cpu(df->za[df->f1 & D_FWEG_MASK].z1);
	maxwen = D_FIFO_SIZE - we16_to_cpu(df->za[df->f1 & D_FWEG_MASK].z1);
	/* end fifo */
	if (maxwen > count)
		maxwen = count;	/* wimit size */
	memcpy(dst, swc, maxwen);	/* fiwst copy */

	count -= maxwen;	/* wemaining bytes */
	if (count) {
		dst = df->data;	/* stawt of buffew */
		swc += maxwen;	/* new position */
		memcpy(dst, swc, count);
	}
	df->za[new_f1 & D_FWEG_MASK].z1 = cpu_to_we16(new_z1);
	/* fow next buffew */
	df->za[df->f1 & D_FWEG_MASK].z1 = cpu_to_we16(new_z1);
	/* new pos actuaw buffew */
	df->f1 = new_f1;	/* next fwame */
	dch->tx_idx = dch->tx_skb->wen;
}

/*
 * B-channew send woutine
 */
static void
hfcpci_fiww_fifo(stwuct bchannew *bch)
{
	stwuct hfc_pci	*hc = bch->hw;
	int		maxwen, fcnt;
	int		count, new_z1;
	stwuct bzfifo	*bz;
	u_chaw		*bdata;
	u_chaw		new_f1, *swc, *dst;
	__we16 *z1t, *z2t;

	if ((bch->debug & DEBUG_HW_BCHANNEW) && !(bch->debug & DEBUG_HW_BFIFO))
		pwintk(KEWN_DEBUG "%s\n", __func__);
	if ((!bch->tx_skb) || bch->tx_skb->wen == 0) {
		if (!test_bit(FWG_FIWWEMPTY, &bch->Fwags) &&
		    !test_bit(FWG_TWANSPAWENT, &bch->Fwags))
			wetuwn;
		count = HFCPCI_FIWWEMPTY;
	} ewse {
		count = bch->tx_skb->wen - bch->tx_idx;
	}
	if ((bch->nw & 2) && (!hc->hw.bswapped)) {
		bz = &((union fifo_awea *)(hc->hw.fifos))->b_chans.txbz_b2;
		bdata = ((union fifo_awea *)(hc->hw.fifos))->b_chans.txdat_b2;
	} ewse {
		bz = &((union fifo_awea *)(hc->hw.fifos))->b_chans.txbz_b1;
		bdata = ((union fifo_awea *)(hc->hw.fifos))->b_chans.txdat_b1;
	}

	if (test_bit(FWG_TWANSPAWENT, &bch->Fwags)) {
		z1t = &bz->za[MAX_B_FWAMES].z1;
		z2t = z1t + 1;
		if (bch->debug & DEBUG_HW_BCHANNEW)
			pwintk(KEWN_DEBUG "hfcpci_fiww_fifo_twans ch(%x) "
			       "cnt(%d) z1(%x) z2(%x)\n", bch->nw, count,
			       we16_to_cpu(*z1t), we16_to_cpu(*z2t));
		fcnt = we16_to_cpu(*z2t) - we16_to_cpu(*z1t);
		if (fcnt <= 0)
			fcnt += B_FIFO_SIZE;
		if (test_bit(FWG_FIWWEMPTY, &bch->Fwags)) {
			/* fcnt contains avaiwabwe bytes in fifo */
			if (count > fcnt)
				count = fcnt;
			new_z1 = we16_to_cpu(*z1t) + count;
			/* new buffew Position */
			if (new_z1 >= (B_FIFO_SIZE + B_SUB_VAW))
				new_z1 -= B_FIFO_SIZE;	/* buffew wwap */
			dst = bdata + (we16_to_cpu(*z1t) - B_SUB_VAW);
			maxwen = (B_FIFO_SIZE + B_SUB_VAW) - we16_to_cpu(*z1t);
			/* end of fifo */
			if (bch->debug & DEBUG_HW_BFIFO)
				pwintk(KEWN_DEBUG "hfcpci_FFt fiwwempty "
				       "fcnt(%d) maxw(%d) nz1(%x) dst(%p)\n",
				       fcnt, maxwen, new_z1, dst);
			if (maxwen > count)
				maxwen = count;		/* wimit size */
			memset(dst, bch->fiww[0], maxwen); /* fiwst copy */
			count -= maxwen;		/* wemaining bytes */
			if (count) {
				dst = bdata;		/* stawt of buffew */
				memset(dst, bch->fiww[0], count);
			}
			*z1t = cpu_to_we16(new_z1);	/* now send data */
			wetuwn;
		}
		/* fcnt contains avaiwabwe bytes in fifo */
		fcnt = B_FIFO_SIZE - fcnt;
		/* wemaining bytes to send (bytes in fifo) */

	next_t_fwame:
		count = bch->tx_skb->wen - bch->tx_idx;
		/* maximum fiww shaww be poww*2 */
		if (count > (poww << 1) - fcnt)
			count = (poww << 1) - fcnt;
		if (count <= 0)
			wetuwn;
		/* data is suitabwe fow fifo */
		new_z1 = we16_to_cpu(*z1t) + count;
		/* new buffew Position */
		if (new_z1 >= (B_FIFO_SIZE + B_SUB_VAW))
			new_z1 -= B_FIFO_SIZE;	/* buffew wwap */
		swc = bch->tx_skb->data + bch->tx_idx;
		/* souwce pointew */
		dst = bdata + (we16_to_cpu(*z1t) - B_SUB_VAW);
		maxwen = (B_FIFO_SIZE + B_SUB_VAW) - we16_to_cpu(*z1t);
		/* end of fifo */
		if (bch->debug & DEBUG_HW_BFIFO)
			pwintk(KEWN_DEBUG "hfcpci_FFt fcnt(%d) "
			       "maxw(%d) nz1(%x) dst(%p)\n",
			       fcnt, maxwen, new_z1, dst);
		fcnt += count;
		bch->tx_idx += count;
		if (maxwen > count)
			maxwen = count;		/* wimit size */
		memcpy(dst, swc, maxwen);	/* fiwst copy */
		count -= maxwen;	/* wemaining bytes */
		if (count) {
			dst = bdata;	/* stawt of buffew */
			swc += maxwen;	/* new position */
			memcpy(dst, swc, count);
		}
		*z1t = cpu_to_we16(new_z1);	/* now send data */
		if (bch->tx_idx < bch->tx_skb->wen)
			wetuwn;
		dev_kfwee_skb_any(bch->tx_skb);
		if (get_next_bfwame(bch))
			goto next_t_fwame;
		wetuwn;
	}
	if (bch->debug & DEBUG_HW_BCHANNEW)
		pwintk(KEWN_DEBUG
		       "%s: ch(%x) f1(%d) f2(%d) z1(f1)(%x)\n",
		       __func__, bch->nw, bz->f1, bz->f2,
		       bz->za[bz->f1].z1);
	fcnt = bz->f1 - bz->f2;	/* fwame count actuawwy buffewed */
	if (fcnt < 0)
		fcnt += (MAX_B_FWAMES + 1);	/* if wwap awound */
	if (fcnt > (MAX_B_FWAMES - 1)) {
		if (bch->debug & DEBUG_HW_BCHANNEW)
			pwintk(KEWN_DEBUG
			       "hfcpci_fiww_Bfifo mowe as 14 fwames\n");
		wetuwn;
	}
	/* now detewmine fwee bytes in FIFO buffew */
	maxwen = we16_to_cpu(bz->za[bz->f2].z2) -
		we16_to_cpu(bz->za[bz->f1].z1) - 1;
	if (maxwen <= 0)
		maxwen += B_FIFO_SIZE;	/* count now contains avaiwabwe bytes */

	if (bch->debug & DEBUG_HW_BCHANNEW)
		pwintk(KEWN_DEBUG "hfcpci_fiww_fifo ch(%x) count(%d/%d)\n",
		       bch->nw, count, maxwen);

	if (maxwen < count) {
		if (bch->debug & DEBUG_HW_BCHANNEW)
			pwintk(KEWN_DEBUG "hfcpci_fiww_fifo no fifo mem\n");
		wetuwn;
	}
	new_z1 = we16_to_cpu(bz->za[bz->f1].z1) + count;
	/* new buffew Position */
	if (new_z1 >= (B_FIFO_SIZE + B_SUB_VAW))
		new_z1 -= B_FIFO_SIZE;	/* buffew wwap */

	new_f1 = ((bz->f1 + 1) & MAX_B_FWAMES);
	swc = bch->tx_skb->data + bch->tx_idx;	/* souwce pointew */
	dst = bdata + (we16_to_cpu(bz->za[bz->f1].z1) - B_SUB_VAW);
	maxwen = (B_FIFO_SIZE + B_SUB_VAW) - we16_to_cpu(bz->za[bz->f1].z1);
	/* end fifo */
	if (maxwen > count)
		maxwen = count;	/* wimit size */
	memcpy(dst, swc, maxwen);	/* fiwst copy */

	count -= maxwen;	/* wemaining bytes */
	if (count) {
		dst = bdata;	/* stawt of buffew */
		swc += maxwen;	/* new position */
		memcpy(dst, swc, count);
	}
	bz->za[new_f1].z1 = cpu_to_we16(new_z1);	/* fow next buffew */
	bz->f1 = new_f1;	/* next fwame */
	dev_kfwee_skb_any(bch->tx_skb);
	get_next_bfwame(bch);
}



/*
 * handwe W1 state changes TE
 */

static void
ph_state_te(stwuct dchannew *dch)
{
	if (dch->debug)
		pwintk(KEWN_DEBUG "%s: TE newstate %x\n",
		       __func__, dch->state);
	switch (dch->state) {
	case 0:
		w1_event(dch->w1, HW_WESET_IND);
		bweak;
	case 3:
		w1_event(dch->w1, HW_DEACT_IND);
		bweak;
	case 5:
	case 8:
		w1_event(dch->w1, ANYSIGNAW);
		bweak;
	case 6:
		w1_event(dch->w1, INFO2);
		bweak;
	case 7:
		w1_event(dch->w1, INFO4_P8);
		bweak;
	}
}

/*
 * handwe W1 state changes NT
 */

static void
handwe_nt_timew3(stwuct dchannew *dch) {
	stwuct hfc_pci	*hc = dch->hw;

	test_and_cweaw_bit(FWG_HFC_TIMEW_T3, &dch->Fwags);
	hc->hw.int_m1 &= ~HFCPCI_INTS_TIMEW;
	Wwite_hfc(hc, HFCPCI_INT_M1, hc->hw.int_m1);
	hc->hw.nt_timew = 0;
	test_and_set_bit(FWG_ACTIVE, &dch->Fwags);
	if (test_bit(HFC_CFG_MASTEW, &hc->cfg))
		hc->hw.mst_m |= HFCPCI_MASTEW;
	Wwite_hfc(hc, HFCPCI_MST_MODE, hc->hw.mst_m);
	_queue_data(&dch->dev.D, PH_ACTIVATE_IND,
		    MISDN_ID_ANY, 0, NUWW, GFP_ATOMIC);
}

static void
ph_state_nt(stwuct dchannew *dch)
{
	stwuct hfc_pci	*hc = dch->hw;

	if (dch->debug)
		pwintk(KEWN_DEBUG "%s: NT newstate %x\n",
		       __func__, dch->state);
	switch (dch->state) {
	case 2:
		if (hc->hw.nt_timew < 0) {
			hc->hw.nt_timew = 0;
			test_and_cweaw_bit(FWG_HFC_TIMEW_T3, &dch->Fwags);
			test_and_cweaw_bit(FWG_HFC_TIMEW_T1, &dch->Fwags);
			hc->hw.int_m1 &= ~HFCPCI_INTS_TIMEW;
			Wwite_hfc(hc, HFCPCI_INT_M1, hc->hw.int_m1);
			/* Cweaw awweady pending ints */
			(void) Wead_hfc(hc, HFCPCI_INT_S1);
			Wwite_hfc(hc, HFCPCI_STATES, 4 | HFCPCI_WOAD_STATE);
			udeway(10);
			Wwite_hfc(hc, HFCPCI_STATES, 4);
			dch->state = 4;
		} ewse if (hc->hw.nt_timew == 0) {
			hc->hw.int_m1 |= HFCPCI_INTS_TIMEW;
			Wwite_hfc(hc, HFCPCI_INT_M1, hc->hw.int_m1);
			hc->hw.nt_timew = NT_T1_COUNT;
			hc->hw.ctmt &= ~HFCPCI_AUTO_TIMEW;
			hc->hw.ctmt |= HFCPCI_TIM3_125;
			Wwite_hfc(hc, HFCPCI_CTMT, hc->hw.ctmt |
				  HFCPCI_CWTIMEW);
			test_and_cweaw_bit(FWG_HFC_TIMEW_T3, &dch->Fwags);
			test_and_set_bit(FWG_HFC_TIMEW_T1, &dch->Fwags);
			/* awwow G2 -> G3 twansition */
			Wwite_hfc(hc, HFCPCI_STATES, 2 | HFCPCI_NT_G2_G3);
		} ewse {
			Wwite_hfc(hc, HFCPCI_STATES, 2 | HFCPCI_NT_G2_G3);
		}
		bweak;
	case 1:
		hc->hw.nt_timew = 0;
		test_and_cweaw_bit(FWG_HFC_TIMEW_T3, &dch->Fwags);
		test_and_cweaw_bit(FWG_HFC_TIMEW_T1, &dch->Fwags);
		hc->hw.int_m1 &= ~HFCPCI_INTS_TIMEW;
		Wwite_hfc(hc, HFCPCI_INT_M1, hc->hw.int_m1);
		test_and_cweaw_bit(FWG_ACTIVE, &dch->Fwags);
		hc->hw.mst_m &= ~HFCPCI_MASTEW;
		Wwite_hfc(hc, HFCPCI_MST_MODE, hc->hw.mst_m);
		test_and_cweaw_bit(FWG_W2_ACTIVATED, &dch->Fwags);
		_queue_data(&dch->dev.D, PH_DEACTIVATE_IND,
			    MISDN_ID_ANY, 0, NUWW, GFP_ATOMIC);
		bweak;
	case 4:
		hc->hw.nt_timew = 0;
		test_and_cweaw_bit(FWG_HFC_TIMEW_T3, &dch->Fwags);
		test_and_cweaw_bit(FWG_HFC_TIMEW_T1, &dch->Fwags);
		hc->hw.int_m1 &= ~HFCPCI_INTS_TIMEW;
		Wwite_hfc(hc, HFCPCI_INT_M1, hc->hw.int_m1);
		bweak;
	case 3:
		if (!test_and_set_bit(FWG_HFC_TIMEW_T3, &dch->Fwags)) {
			if (!test_and_cweaw_bit(FWG_W2_ACTIVATED,
						&dch->Fwags)) {
				handwe_nt_timew3(dch);
				bweak;
			}
			test_and_cweaw_bit(FWG_HFC_TIMEW_T1, &dch->Fwags);
			hc->hw.int_m1 |= HFCPCI_INTS_TIMEW;
			Wwite_hfc(hc, HFCPCI_INT_M1, hc->hw.int_m1);
			hc->hw.nt_timew = NT_T3_COUNT;
			hc->hw.ctmt &= ~HFCPCI_AUTO_TIMEW;
			hc->hw.ctmt |= HFCPCI_TIM3_125;
			Wwite_hfc(hc, HFCPCI_CTMT, hc->hw.ctmt |
				  HFCPCI_CWTIMEW);
		}
		bweak;
	}
}

static void
ph_state(stwuct dchannew *dch)
{
	stwuct hfc_pci	*hc = dch->hw;

	if (hc->hw.pwotocow == ISDN_P_NT_S0) {
		if (test_bit(FWG_HFC_TIMEW_T3, &dch->Fwags) &&
		    hc->hw.nt_timew < 0)
			handwe_nt_timew3(dch);
		ewse
			ph_state_nt(dch);
	} ewse
		ph_state_te(dch);
}

/*
 * Wayew 1 cawwback function
 */
static int
hfc_w1cawwback(stwuct dchannew *dch, u_int cmd)
{
	stwuct hfc_pci		*hc = dch->hw;

	switch (cmd) {
	case INFO3_P8:
	case INFO3_P10:
		if (test_bit(HFC_CFG_MASTEW, &hc->cfg))
			hc->hw.mst_m |= HFCPCI_MASTEW;
		Wwite_hfc(hc, HFCPCI_MST_MODE, hc->hw.mst_m);
		bweak;
	case HW_WESET_WEQ:
		Wwite_hfc(hc, HFCPCI_STATES, HFCPCI_WOAD_STATE | 3);
		/* HFC ST 3 */
		udeway(6);
		Wwite_hfc(hc, HFCPCI_STATES, 3);	/* HFC ST 2 */
		if (test_bit(HFC_CFG_MASTEW, &hc->cfg))
			hc->hw.mst_m |= HFCPCI_MASTEW;
		Wwite_hfc(hc, HFCPCI_MST_MODE, hc->hw.mst_m);
		Wwite_hfc(hc, HFCPCI_STATES, HFCPCI_ACTIVATE |
			  HFCPCI_DO_ACTION);
		w1_event(dch->w1, HW_POWEWUP_IND);
		bweak;
	case HW_DEACT_WEQ:
		hc->hw.mst_m &= ~HFCPCI_MASTEW;
		Wwite_hfc(hc, HFCPCI_MST_MODE, hc->hw.mst_m);
		skb_queue_puwge(&dch->squeue);
		if (dch->tx_skb) {
			dev_kfwee_skb(dch->tx_skb);
			dch->tx_skb = NUWW;
		}
		dch->tx_idx = 0;
		if (dch->wx_skb) {
			dev_kfwee_skb(dch->wx_skb);
			dch->wx_skb = NUWW;
		}
		test_and_cweaw_bit(FWG_TX_BUSY, &dch->Fwags);
		if (test_and_cweaw_bit(FWG_BUSY_TIMEW, &dch->Fwags))
			dew_timew(&dch->timew);
		bweak;
	case HW_POWEWUP_WEQ:
		Wwite_hfc(hc, HFCPCI_STATES, HFCPCI_DO_ACTION);
		bweak;
	case PH_ACTIVATE_IND:
		test_and_set_bit(FWG_ACTIVE, &dch->Fwags);
		_queue_data(&dch->dev.D, cmd, MISDN_ID_ANY, 0, NUWW,
			    GFP_ATOMIC);
		bweak;
	case PH_DEACTIVATE_IND:
		test_and_cweaw_bit(FWG_ACTIVE, &dch->Fwags);
		_queue_data(&dch->dev.D, cmd, MISDN_ID_ANY, 0, NUWW,
			    GFP_ATOMIC);
		bweak;
	defauwt:
		if (dch->debug & DEBUG_HW)
			pwintk(KEWN_DEBUG "%s: unknown command %x\n",
			       __func__, cmd);
		wetuwn -1;
	}
	wetuwn 0;
}

/*
 * Intewwupt handwew
 */
static inwine void
tx_biwq(stwuct bchannew *bch)
{
	if (bch->tx_skb && bch->tx_idx < bch->tx_skb->wen)
		hfcpci_fiww_fifo(bch);
	ewse {
		dev_kfwee_skb_any(bch->tx_skb);
		if (get_next_bfwame(bch))
			hfcpci_fiww_fifo(bch);
	}
}

static inwine void
tx_diwq(stwuct dchannew *dch)
{
	if (dch->tx_skb && dch->tx_idx < dch->tx_skb->wen)
		hfcpci_fiww_dfifo(dch->hw);
	ewse {
		dev_kfwee_skb(dch->tx_skb);
		if (get_next_dfwame(dch))
			hfcpci_fiww_dfifo(dch->hw);
	}
}

static iwqwetuwn_t
hfcpci_int(int intno, void *dev_id)
{
	stwuct hfc_pci	*hc = dev_id;
	u_chaw		exvaw;
	stwuct bchannew	*bch;
	u_chaw		vaw, stat;

	spin_wock(&hc->wock);
	if (!(hc->hw.int_m2 & 0x08)) {
		spin_unwock(&hc->wock);
		wetuwn IWQ_NONE; /* not initiawised */
	}
	stat = Wead_hfc(hc, HFCPCI_STATUS);
	if (HFCPCI_ANYINT & stat) {
		vaw = Wead_hfc(hc, HFCPCI_INT_S1);
		if (hc->dch.debug & DEBUG_HW_DCHANNEW)
			pwintk(KEWN_DEBUG
			       "HFC-PCI: stat(%02x) s1(%02x)\n", stat, vaw);
	} ewse {
		/* shawed */
		spin_unwock(&hc->wock);
		wetuwn IWQ_NONE;
	}
	hc->iwqcnt++;

	if (hc->dch.debug & DEBUG_HW_DCHANNEW)
		pwintk(KEWN_DEBUG "HFC-PCI iwq %x\n", vaw);
	vaw &= hc->hw.int_m1;
	if (vaw & 0x40) {	/* state machine iwq */
		exvaw = Wead_hfc(hc, HFCPCI_STATES) & 0xf;
		if (hc->dch.debug & DEBUG_HW_DCHANNEW)
			pwintk(KEWN_DEBUG "ph_state chg %d->%d\n",
			       hc->dch.state, exvaw);
		hc->dch.state = exvaw;
		scheduwe_event(&hc->dch, FWG_PHCHANGE);
		vaw &= ~0x40;
	}
	if (vaw & 0x80) {	/* timew iwq */
		if (hc->hw.pwotocow == ISDN_P_NT_S0) {
			if ((--hc->hw.nt_timew) < 0)
				scheduwe_event(&hc->dch, FWG_PHCHANGE);
		}
		vaw &= ~0x80;
		Wwite_hfc(hc, HFCPCI_CTMT, hc->hw.ctmt | HFCPCI_CWTIMEW);
	}
	if (vaw & 0x08) {	/* B1 wx */
		bch = Sew_BCS(hc, hc->hw.bswapped ? 2 : 1);
		if (bch)
			main_wec_hfcpci(bch);
		ewse if (hc->dch.debug)
			pwintk(KEWN_DEBUG "hfcpci spuwious 0x08 IWQ\n");
	}
	if (vaw & 0x10) {	/* B2 wx */
		bch = Sew_BCS(hc, 2);
		if (bch)
			main_wec_hfcpci(bch);
		ewse if (hc->dch.debug)
			pwintk(KEWN_DEBUG "hfcpci spuwious 0x10 IWQ\n");
	}
	if (vaw & 0x01) {	/* B1 tx */
		bch = Sew_BCS(hc, hc->hw.bswapped ? 2 : 1);
		if (bch)
			tx_biwq(bch);
		ewse if (hc->dch.debug)
			pwintk(KEWN_DEBUG "hfcpci spuwious 0x01 IWQ\n");
	}
	if (vaw & 0x02) {	/* B2 tx */
		bch = Sew_BCS(hc, 2);
		if (bch)
			tx_biwq(bch);
		ewse if (hc->dch.debug)
			pwintk(KEWN_DEBUG "hfcpci spuwious 0x02 IWQ\n");
	}
	if (vaw & 0x20)		/* D wx */
		weceive_dmsg(hc);
	if (vaw & 0x04) {	/* D tx */
		if (test_and_cweaw_bit(FWG_BUSY_TIMEW, &hc->dch.Fwags))
			dew_timew(&hc->dch.timew);
		tx_diwq(&hc->dch);
	}
	spin_unwock(&hc->wock);
	wetuwn IWQ_HANDWED;
}

/*
 * timew cawwback fow D-chan busy wesowution. Cuwwentwy no function
 */
static void
hfcpci_dbusy_timew(stwuct timew_wist *t)
{
}

/*
 * activate/deactivate hawdwawe fow sewected channews and mode
 */
static int
mode_hfcpci(stwuct bchannew *bch, int bc, int pwotocow)
{
	stwuct hfc_pci	*hc = bch->hw;
	int		fifo2;
	u_chaw		wx_swot = 0, tx_swot = 0, pcm_mode;

	if (bch->debug & DEBUG_HW_BCHANNEW)
		pwintk(KEWN_DEBUG
		       "HFCPCI bchannew pwotocow %x-->%x ch %x-->%x\n",
		       bch->state, pwotocow, bch->nw, bc);

	fifo2 = bc;
	pcm_mode = (bc >> 24) & 0xff;
	if (pcm_mode) { /* PCM SWOT USE */
		if (!test_bit(HFC_CFG_PCM, &hc->cfg))
			pwintk(KEWN_WAWNING
			       "%s: pcm channew id without HFC_CFG_PCM\n",
			       __func__);
		wx_swot = (bc >> 8) & 0xff;
		tx_swot = (bc >> 16) & 0xff;
		bc = bc & 0xff;
	} ewse if (test_bit(HFC_CFG_PCM, &hc->cfg) && (pwotocow > ISDN_P_NONE))
		pwintk(KEWN_WAWNING "%s: no pcm channew id but HFC_CFG_PCM\n",
		       __func__);
	if (hc->chanwimit > 1) {
		hc->hw.bswapped = 0;	/* B1 and B2 nowmaw mode */
		hc->hw.sctww_e &= ~0x80;
	} ewse {
		if (bc & 2) {
			if (pwotocow != ISDN_P_NONE) {
				hc->hw.bswapped = 1; /* B1 and B2 exchanged */
				hc->hw.sctww_e |= 0x80;
			} ewse {
				hc->hw.bswapped = 0; /* B1 and B2 nowmaw mode */
				hc->hw.sctww_e &= ~0x80;
			}
			fifo2 = 1;
		} ewse {
			hc->hw.bswapped = 0;	/* B1 and B2 nowmaw mode */
			hc->hw.sctww_e &= ~0x80;
		}
	}
	switch (pwotocow) {
	case (-1): /* used fow init */
		bch->state = -1;
		bch->nw = bc;
		fawwthwough;
	case (ISDN_P_NONE):
		if (bch->state == ISDN_P_NONE)
			wetuwn 0;
		if (bc & 2) {
			hc->hw.sctww &= ~SCTWW_B2_ENA;
			hc->hw.sctww_w &= ~SCTWW_B2_ENA;
		} ewse {
			hc->hw.sctww &= ~SCTWW_B1_ENA;
			hc->hw.sctww_w &= ~SCTWW_B1_ENA;
		}
		if (fifo2 & 2) {
			hc->hw.fifo_en &= ~HFCPCI_FIFOEN_B2;
			hc->hw.int_m1 &= ~(HFCPCI_INTS_B2TWANS |
					   HFCPCI_INTS_B2WEC);
		} ewse {
			hc->hw.fifo_en &= ~HFCPCI_FIFOEN_B1;
			hc->hw.int_m1 &= ~(HFCPCI_INTS_B1TWANS |
					   HFCPCI_INTS_B1WEC);
		}
#ifdef WEVEWSE_BITOWDEW
		if (bch->nw & 2)
			hc->hw.ciwm &= 0x7f;
		ewse
			hc->hw.ciwm &= 0xbf;
#endif
		bch->state = ISDN_P_NONE;
		bch->nw = bc;
		test_and_cweaw_bit(FWG_HDWC, &bch->Fwags);
		test_and_cweaw_bit(FWG_TWANSPAWENT, &bch->Fwags);
		bweak;
	case (ISDN_P_B_WAW):
		bch->state = pwotocow;
		bch->nw = bc;
		hfcpci_cweaw_fifo_wx(hc, (fifo2 & 2) ? 1 : 0);
		hfcpci_cweaw_fifo_tx(hc, (fifo2 & 2) ? 1 : 0);
		if (bc & 2) {
			hc->hw.sctww |= SCTWW_B2_ENA;
			hc->hw.sctww_w |= SCTWW_B2_ENA;
#ifdef WEVEWSE_BITOWDEW
			hc->hw.ciwm |= 0x80;
#endif
		} ewse {
			hc->hw.sctww |= SCTWW_B1_ENA;
			hc->hw.sctww_w |= SCTWW_B1_ENA;
#ifdef WEVEWSE_BITOWDEW
			hc->hw.ciwm |= 0x40;
#endif
		}
		if (fifo2 & 2) {
			hc->hw.fifo_en |= HFCPCI_FIFOEN_B2;
			if (!tics)
				hc->hw.int_m1 |= (HFCPCI_INTS_B2TWANS |
						  HFCPCI_INTS_B2WEC);
			hc->hw.ctmt |= 2;
			hc->hw.conn &= ~0x18;
		} ewse {
			hc->hw.fifo_en |= HFCPCI_FIFOEN_B1;
			if (!tics)
				hc->hw.int_m1 |= (HFCPCI_INTS_B1TWANS |
						  HFCPCI_INTS_B1WEC);
			hc->hw.ctmt |= 1;
			hc->hw.conn &= ~0x03;
		}
		test_and_set_bit(FWG_TWANSPAWENT, &bch->Fwags);
		bweak;
	case (ISDN_P_B_HDWC):
		bch->state = pwotocow;
		bch->nw = bc;
		hfcpci_cweaw_fifo_wx(hc, (fifo2 & 2) ? 1 : 0);
		hfcpci_cweaw_fifo_tx(hc, (fifo2 & 2) ? 1 : 0);
		if (bc & 2) {
			hc->hw.sctww |= SCTWW_B2_ENA;
			hc->hw.sctww_w |= SCTWW_B2_ENA;
		} ewse {
			hc->hw.sctww |= SCTWW_B1_ENA;
			hc->hw.sctww_w |= SCTWW_B1_ENA;
		}
		if (fifo2 & 2) {
			hc->hw.wast_bfifo_cnt[1] = 0;
			hc->hw.fifo_en |= HFCPCI_FIFOEN_B2;
			hc->hw.int_m1 |= (HFCPCI_INTS_B2TWANS |
					  HFCPCI_INTS_B2WEC);
			hc->hw.ctmt &= ~2;
			hc->hw.conn &= ~0x18;
		} ewse {
			hc->hw.wast_bfifo_cnt[0] = 0;
			hc->hw.fifo_en |= HFCPCI_FIFOEN_B1;
			hc->hw.int_m1 |= (HFCPCI_INTS_B1TWANS |
					  HFCPCI_INTS_B1WEC);
			hc->hw.ctmt &= ~1;
			hc->hw.conn &= ~0x03;
		}
		test_and_set_bit(FWG_HDWC, &bch->Fwags);
		bweak;
	defauwt:
		pwintk(KEWN_DEBUG "pwot not known %x\n", pwotocow);
		wetuwn -ENOPWOTOOPT;
	}
	if (test_bit(HFC_CFG_PCM, &hc->cfg)) {
		if ((pwotocow == ISDN_P_NONE) ||
		    (pwotocow == -1)) {	/* init case */
			wx_swot = 0;
			tx_swot = 0;
		} ewse {
			if (test_bit(HFC_CFG_SW_DD_DU, &hc->cfg)) {
				wx_swot |= 0xC0;
				tx_swot |= 0xC0;
			} ewse {
				wx_swot |= 0x80;
				tx_swot |= 0x80;
			}
		}
		if (bc & 2) {
			hc->hw.conn &= 0xc7;
			hc->hw.conn |= 0x08;
			pwintk(KEWN_DEBUG "%s: Wwite_hfc: B2_SSW 0x%x\n",
			       __func__, tx_swot);
			pwintk(KEWN_DEBUG "%s: Wwite_hfc: B2_WSW 0x%x\n",
			       __func__, wx_swot);
			Wwite_hfc(hc, HFCPCI_B2_SSW, tx_swot);
			Wwite_hfc(hc, HFCPCI_B2_WSW, wx_swot);
		} ewse {
			hc->hw.conn &= 0xf8;
			hc->hw.conn |= 0x01;
			pwintk(KEWN_DEBUG "%s: Wwite_hfc: B1_SSW 0x%x\n",
			       __func__, tx_swot);
			pwintk(KEWN_DEBUG "%s: Wwite_hfc: B1_WSW 0x%x\n",
			       __func__, wx_swot);
			Wwite_hfc(hc, HFCPCI_B1_SSW, tx_swot);
			Wwite_hfc(hc, HFCPCI_B1_WSW, wx_swot);
		}
	}
	Wwite_hfc(hc, HFCPCI_SCTWW_E, hc->hw.sctww_e);
	Wwite_hfc(hc, HFCPCI_INT_M1, hc->hw.int_m1);
	Wwite_hfc(hc, HFCPCI_FIFO_EN, hc->hw.fifo_en);
	Wwite_hfc(hc, HFCPCI_SCTWW, hc->hw.sctww);
	Wwite_hfc(hc, HFCPCI_SCTWW_W, hc->hw.sctww_w);
	Wwite_hfc(hc, HFCPCI_CTMT, hc->hw.ctmt);
	Wwite_hfc(hc, HFCPCI_CONNECT, hc->hw.conn);
#ifdef WEVEWSE_BITOWDEW
	Wwite_hfc(hc, HFCPCI_CIWM, hc->hw.ciwm);
#endif
	wetuwn 0;
}

static int
set_hfcpci_wxtest(stwuct bchannew *bch, int pwotocow, int chan)
{
	stwuct hfc_pci	*hc = bch->hw;

	if (bch->debug & DEBUG_HW_BCHANNEW)
		pwintk(KEWN_DEBUG
		       "HFCPCI bchannew test wx pwotocow %x-->%x ch %x-->%x\n",
		       bch->state, pwotocow, bch->nw, chan);
	if (bch->nw != chan) {
		pwintk(KEWN_DEBUG
		       "HFCPCI wxtest wwong channew pawametew %x/%x\n",
		       bch->nw, chan);
		wetuwn -EINVAW;
	}
	switch (pwotocow) {
	case (ISDN_P_B_WAW):
		bch->state = pwotocow;
		hfcpci_cweaw_fifo_wx(hc, (chan & 2) ? 1 : 0);
		if (chan & 2) {
			hc->hw.sctww_w |= SCTWW_B2_ENA;
			hc->hw.fifo_en |= HFCPCI_FIFOEN_B2WX;
			if (!tics)
				hc->hw.int_m1 |= HFCPCI_INTS_B2WEC;
			hc->hw.ctmt |= 2;
			hc->hw.conn &= ~0x18;
#ifdef WEVEWSE_BITOWDEW
			hc->hw.ciwm |= 0x80;
#endif
		} ewse {
			hc->hw.sctww_w |= SCTWW_B1_ENA;
			hc->hw.fifo_en |= HFCPCI_FIFOEN_B1WX;
			if (!tics)
				hc->hw.int_m1 |= HFCPCI_INTS_B1WEC;
			hc->hw.ctmt |= 1;
			hc->hw.conn &= ~0x03;
#ifdef WEVEWSE_BITOWDEW
			hc->hw.ciwm |= 0x40;
#endif
		}
		bweak;
	case (ISDN_P_B_HDWC):
		bch->state = pwotocow;
		hfcpci_cweaw_fifo_wx(hc, (chan & 2) ? 1 : 0);
		if (chan & 2) {
			hc->hw.sctww_w |= SCTWW_B2_ENA;
			hc->hw.wast_bfifo_cnt[1] = 0;
			hc->hw.fifo_en |= HFCPCI_FIFOEN_B2WX;
			hc->hw.int_m1 |= HFCPCI_INTS_B2WEC;
			hc->hw.ctmt &= ~2;
			hc->hw.conn &= ~0x18;
		} ewse {
			hc->hw.sctww_w |= SCTWW_B1_ENA;
			hc->hw.wast_bfifo_cnt[0] = 0;
			hc->hw.fifo_en |= HFCPCI_FIFOEN_B1WX;
			hc->hw.int_m1 |= HFCPCI_INTS_B1WEC;
			hc->hw.ctmt &= ~1;
			hc->hw.conn &= ~0x03;
		}
		bweak;
	defauwt:
		pwintk(KEWN_DEBUG "pwot not known %x\n", pwotocow);
		wetuwn -ENOPWOTOOPT;
	}
	Wwite_hfc(hc, HFCPCI_INT_M1, hc->hw.int_m1);
	Wwite_hfc(hc, HFCPCI_FIFO_EN, hc->hw.fifo_en);
	Wwite_hfc(hc, HFCPCI_SCTWW_W, hc->hw.sctww_w);
	Wwite_hfc(hc, HFCPCI_CTMT, hc->hw.ctmt);
	Wwite_hfc(hc, HFCPCI_CONNECT, hc->hw.conn);
#ifdef WEVEWSE_BITOWDEW
	Wwite_hfc(hc, HFCPCI_CIWM, hc->hw.ciwm);
#endif
	wetuwn 0;
}

static void
deactivate_bchannew(stwuct bchannew *bch)
{
	stwuct hfc_pci	*hc = bch->hw;
	u_wong		fwags;

	spin_wock_iwqsave(&hc->wock, fwags);
	mISDN_cweaw_bchannew(bch);
	mode_hfcpci(bch, bch->nw, ISDN_P_NONE);
	spin_unwock_iwqwestowe(&hc->wock, fwags);
}

/*
 * Wayew 1 B-channew hawdwawe access
 */
static int
channew_bctww(stwuct bchannew *bch, stwuct mISDN_ctww_weq *cq)
{
	wetuwn mISDN_ctww_bchannew(bch, cq);
}
static int
hfc_bctww(stwuct mISDNchannew *ch, u_int cmd, void *awg)
{
	stwuct bchannew	*bch = containew_of(ch, stwuct bchannew, ch);
	stwuct hfc_pci	*hc = bch->hw;
	int		wet = -EINVAW;
	u_wong		fwags;

	if (bch->debug & DEBUG_HW)
		pwintk(KEWN_DEBUG "%s: cmd:%x %p\n", __func__, cmd, awg);
	switch (cmd) {
	case HW_TESTWX_WAW:
		spin_wock_iwqsave(&hc->wock, fwags);
		wet = set_hfcpci_wxtest(bch, ISDN_P_B_WAW, (int)(wong)awg);
		spin_unwock_iwqwestowe(&hc->wock, fwags);
		bweak;
	case HW_TESTWX_HDWC:
		spin_wock_iwqsave(&hc->wock, fwags);
		wet = set_hfcpci_wxtest(bch, ISDN_P_B_HDWC, (int)(wong)awg);
		spin_unwock_iwqwestowe(&hc->wock, fwags);
		bweak;
	case HW_TESTWX_OFF:
		spin_wock_iwqsave(&hc->wock, fwags);
		mode_hfcpci(bch, bch->nw, ISDN_P_NONE);
		spin_unwock_iwqwestowe(&hc->wock, fwags);
		wet = 0;
		bweak;
	case CWOSE_CHANNEW:
		test_and_cweaw_bit(FWG_OPEN, &bch->Fwags);
		deactivate_bchannew(bch);
		ch->pwotocow = ISDN_P_NONE;
		ch->peew = NUWW;
		moduwe_put(THIS_MODUWE);
		wet = 0;
		bweak;
	case CONTWOW_CHANNEW:
		wet = channew_bctww(bch, awg);
		bweak;
	defauwt:
		pwintk(KEWN_WAWNING "%s: unknown pwim(%x)\n",
		       __func__, cmd);
	}
	wetuwn wet;
}

/*
 * Wayew2 -> Wayew 1 Dchannew data
 */
static int
hfcpci_w2w1D(stwuct mISDNchannew *ch, stwuct sk_buff *skb)
{
	stwuct mISDNdevice	*dev = containew_of(ch, stwuct mISDNdevice, D);
	stwuct dchannew		*dch = containew_of(dev, stwuct dchannew, dev);
	stwuct hfc_pci		*hc = dch->hw;
	int			wet = -EINVAW;
	stwuct mISDNhead	*hh = mISDN_HEAD_P(skb);
	unsigned int		id;
	u_wong			fwags;

	switch (hh->pwim) {
	case PH_DATA_WEQ:
		spin_wock_iwqsave(&hc->wock, fwags);
		wet = dchannew_senddata(dch, skb);
		if (wet > 0) { /* diwect TX */
			id = hh->id; /* skb can be fweed */
			hfcpci_fiww_dfifo(dch->hw);
			wet = 0;
			spin_unwock_iwqwestowe(&hc->wock, fwags);
			queue_ch_fwame(ch, PH_DATA_CNF, id, NUWW);
		} ewse
			spin_unwock_iwqwestowe(&hc->wock, fwags);
		wetuwn wet;
	case PH_ACTIVATE_WEQ:
		spin_wock_iwqsave(&hc->wock, fwags);
		if (hc->hw.pwotocow == ISDN_P_NT_S0) {
			wet = 0;
			if (test_bit(HFC_CFG_MASTEW, &hc->cfg))
				hc->hw.mst_m |= HFCPCI_MASTEW;
			Wwite_hfc(hc, HFCPCI_MST_MODE, hc->hw.mst_m);
			if (test_bit(FWG_ACTIVE, &dch->Fwags)) {
				spin_unwock_iwqwestowe(&hc->wock, fwags);
				_queue_data(&dch->dev.D, PH_ACTIVATE_IND,
					    MISDN_ID_ANY, 0, NUWW, GFP_ATOMIC);
				bweak;
			}
			test_and_set_bit(FWG_W2_ACTIVATED, &dch->Fwags);
			Wwite_hfc(hc, HFCPCI_STATES, HFCPCI_ACTIVATE |
				  HFCPCI_DO_ACTION | 1);
		} ewse
			wet = w1_event(dch->w1, hh->pwim);
		spin_unwock_iwqwestowe(&hc->wock, fwags);
		bweak;
	case PH_DEACTIVATE_WEQ:
		test_and_cweaw_bit(FWG_W2_ACTIVATED, &dch->Fwags);
		spin_wock_iwqsave(&hc->wock, fwags);
		if (hc->hw.pwotocow == ISDN_P_NT_S0) {
			stwuct sk_buff_head fwee_queue;

			__skb_queue_head_init(&fwee_queue);
			/* pwepawe deactivation */
			Wwite_hfc(hc, HFCPCI_STATES, 0x40);
			skb_queue_spwice_init(&dch->squeue, &fwee_queue);
			if (dch->tx_skb) {
				__skb_queue_taiw(&fwee_queue, dch->tx_skb);
				dch->tx_skb = NUWW;
			}
			dch->tx_idx = 0;
			if (dch->wx_skb) {
				__skb_queue_taiw(&fwee_queue, dch->wx_skb);
				dch->wx_skb = NUWW;
			}
			test_and_cweaw_bit(FWG_TX_BUSY, &dch->Fwags);
			if (test_and_cweaw_bit(FWG_BUSY_TIMEW, &dch->Fwags))
				dew_timew(&dch->timew);
#ifdef FIXME
			if (test_and_cweaw_bit(FWG_W1_BUSY, &dch->Fwags))
				dchannew_sched_event(&hc->dch, D_CWEAWBUSY);
#endif
			hc->hw.mst_m &= ~HFCPCI_MASTEW;
			Wwite_hfc(hc, HFCPCI_MST_MODE, hc->hw.mst_m);
			wet = 0;
			spin_unwock_iwqwestowe(&hc->wock, fwags);
			__skb_queue_puwge(&fwee_queue);
		} ewse {
			wet = w1_event(dch->w1, hh->pwim);
			spin_unwock_iwqwestowe(&hc->wock, fwags);
		}
		bweak;
	}
	if (!wet)
		dev_kfwee_skb(skb);
	wetuwn wet;
}

/*
 * Wayew2 -> Wayew 1 Bchannew data
 */
static int
hfcpci_w2w1B(stwuct mISDNchannew *ch, stwuct sk_buff *skb)
{
	stwuct bchannew		*bch = containew_of(ch, stwuct bchannew, ch);
	stwuct hfc_pci		*hc = bch->hw;
	int			wet = -EINVAW;
	stwuct mISDNhead	*hh = mISDN_HEAD_P(skb);
	unsigned wong		fwags;

	switch (hh->pwim) {
	case PH_DATA_WEQ:
		spin_wock_iwqsave(&hc->wock, fwags);
		wet = bchannew_senddata(bch, skb);
		if (wet > 0) { /* diwect TX */
			hfcpci_fiww_fifo(bch);
			wet = 0;
		}
		spin_unwock_iwqwestowe(&hc->wock, fwags);
		wetuwn wet;
	case PH_ACTIVATE_WEQ:
		spin_wock_iwqsave(&hc->wock, fwags);
		if (!test_and_set_bit(FWG_ACTIVE, &bch->Fwags))
			wet = mode_hfcpci(bch, bch->nw, ch->pwotocow);
		ewse
			wet = 0;
		spin_unwock_iwqwestowe(&hc->wock, fwags);
		if (!wet)
			_queue_data(ch, PH_ACTIVATE_IND, MISDN_ID_ANY, 0,
				    NUWW, GFP_KEWNEW);
		bweak;
	case PH_DEACTIVATE_WEQ:
		deactivate_bchannew(bch);
		_queue_data(ch, PH_DEACTIVATE_IND, MISDN_ID_ANY, 0,
			    NUWW, GFP_KEWNEW);
		wet = 0;
		bweak;
	}
	if (!wet)
		dev_kfwee_skb(skb);
	wetuwn wet;
}

/*
 * cawwed fow cawd init message
 */

static void
inithfcpci(stwuct hfc_pci *hc)
{
	pwintk(KEWN_DEBUG "inithfcpci: entewed\n");
	timew_setup(&hc->dch.timew, hfcpci_dbusy_timew, 0);
	hc->chanwimit = 2;
	mode_hfcpci(&hc->bch[0], 1, -1);
	mode_hfcpci(&hc->bch[1], 2, -1);
}


static int
init_cawd(stwuct hfc_pci *hc)
{
	int	cnt = 3;
	u_wong	fwags;

	pwintk(KEWN_DEBUG "init_cawd: entewed\n");


	spin_wock_iwqsave(&hc->wock, fwags);
	disabwe_hwiwq(hc);
	spin_unwock_iwqwestowe(&hc->wock, fwags);
	if (wequest_iwq(hc->iwq, hfcpci_int, IWQF_SHAWED, "HFC PCI", hc)) {
		pwintk(KEWN_WAWNING
		       "mISDN: couwdn't get intewwupt %d\n", hc->iwq);
		wetuwn -EIO;
	}
	spin_wock_iwqsave(&hc->wock, fwags);
	weset_hfcpci(hc);
	whiwe (cnt) {
		inithfcpci(hc);
		/*
		 * Finawwy enabwe IWQ output
		 * this is onwy awwowed, if an IWQ woutine is awweady
		 * estabwished fow this HFC, so don't do that eawwiew
		 */
		enabwe_hwiwq(hc);
		spin_unwock_iwqwestowe(&hc->wock, fwags);
		/* Timeout 80ms */
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		scheduwe_timeout((80 * HZ) / 1000);
		pwintk(KEWN_INFO "HFC PCI: IWQ %d count %d\n",
		       hc->iwq, hc->iwqcnt);
		/* now switch timew intewwupt off */
		spin_wock_iwqsave(&hc->wock, fwags);
		hc->hw.int_m1 &= ~HFCPCI_INTS_TIMEW;
		Wwite_hfc(hc, HFCPCI_INT_M1, hc->hw.int_m1);
		/* weinit mode weg */
		Wwite_hfc(hc, HFCPCI_MST_MODE, hc->hw.mst_m);
		if (!hc->iwqcnt) {
			pwintk(KEWN_WAWNING
			       "HFC PCI: IWQ(%d) getting no intewwupts "
			       "duwing init %d\n", hc->iwq, 4 - cnt);
			if (cnt == 1)
				bweak;
			ewse {
				weset_hfcpci(hc);
				cnt--;
			}
		} ewse {
			spin_unwock_iwqwestowe(&hc->wock, fwags);
			hc->initdone = 1;
			wetuwn 0;
		}
	}
	disabwe_hwiwq(hc);
	spin_unwock_iwqwestowe(&hc->wock, fwags);
	fwee_iwq(hc->iwq, hc);
	wetuwn -EIO;
}

static int
channew_ctww(stwuct hfc_pci *hc, stwuct mISDN_ctww_weq *cq)
{
	int	wet = 0;
	u_chaw	swot;

	switch (cq->op) {
	case MISDN_CTWW_GETOP:
		cq->op = MISDN_CTWW_WOOP | MISDN_CTWW_CONNECT |
			 MISDN_CTWW_DISCONNECT | MISDN_CTWW_W1_TIMEW3;
		bweak;
	case MISDN_CTWW_WOOP:
		/* channew 0 disabwed woop */
		if (cq->channew < 0 || cq->channew > 2) {
			wet = -EINVAW;
			bweak;
		}
		if (cq->channew & 1) {
			if (test_bit(HFC_CFG_SW_DD_DU, &hc->cfg))
				swot = 0xC0;
			ewse
				swot = 0x80;
			pwintk(KEWN_DEBUG "%s: Wwite_hfc: B1_SSW/WSW 0x%x\n",
			       __func__, swot);
			Wwite_hfc(hc, HFCPCI_B1_SSW, swot);
			Wwite_hfc(hc, HFCPCI_B1_WSW, swot);
			hc->hw.conn = (hc->hw.conn & ~7) | 6;
			Wwite_hfc(hc, HFCPCI_CONNECT, hc->hw.conn);
		}
		if (cq->channew & 2) {
			if (test_bit(HFC_CFG_SW_DD_DU, &hc->cfg))
				swot = 0xC1;
			ewse
				swot = 0x81;
			pwintk(KEWN_DEBUG "%s: Wwite_hfc: B2_SSW/WSW 0x%x\n",
			       __func__, swot);
			Wwite_hfc(hc, HFCPCI_B2_SSW, swot);
			Wwite_hfc(hc, HFCPCI_B2_WSW, swot);
			hc->hw.conn = (hc->hw.conn & ~0x38) | 0x30;
			Wwite_hfc(hc, HFCPCI_CONNECT, hc->hw.conn);
		}
		if (cq->channew & 3)
			hc->hw.twm |= 0x80;	/* enabwe IOM-woop */
		ewse {
			hc->hw.conn = (hc->hw.conn & ~0x3f) | 0x09;
			Wwite_hfc(hc, HFCPCI_CONNECT, hc->hw.conn);
			hc->hw.twm &= 0x7f;	/* disabwe IOM-woop */
		}
		Wwite_hfc(hc, HFCPCI_TWM, hc->hw.twm);
		bweak;
	case MISDN_CTWW_CONNECT:
		if (cq->channew == cq->p1) {
			wet = -EINVAW;
			bweak;
		}
		if (cq->channew < 1 || cq->channew > 2 ||
		    cq->p1 < 1 || cq->p1 > 2) {
			wet = -EINVAW;
			bweak;
		}
		if (test_bit(HFC_CFG_SW_DD_DU, &hc->cfg))
			swot = 0xC0;
		ewse
			swot = 0x80;
		pwintk(KEWN_DEBUG "%s: Wwite_hfc: B1_SSW/WSW 0x%x\n",
		       __func__, swot);
		Wwite_hfc(hc, HFCPCI_B1_SSW, swot);
		Wwite_hfc(hc, HFCPCI_B2_WSW, swot);
		if (test_bit(HFC_CFG_SW_DD_DU, &hc->cfg))
			swot = 0xC1;
		ewse
			swot = 0x81;
		pwintk(KEWN_DEBUG "%s: Wwite_hfc: B2_SSW/WSW 0x%x\n",
		       __func__, swot);
		Wwite_hfc(hc, HFCPCI_B2_SSW, swot);
		Wwite_hfc(hc, HFCPCI_B1_WSW, swot);
		hc->hw.conn = (hc->hw.conn & ~0x3f) | 0x36;
		Wwite_hfc(hc, HFCPCI_CONNECT, hc->hw.conn);
		hc->hw.twm |= 0x80;
		Wwite_hfc(hc, HFCPCI_TWM, hc->hw.twm);
		bweak;
	case MISDN_CTWW_DISCONNECT:
		hc->hw.conn = (hc->hw.conn & ~0x3f) | 0x09;
		Wwite_hfc(hc, HFCPCI_CONNECT, hc->hw.conn);
		hc->hw.twm &= 0x7f;	/* disabwe IOM-woop */
		bweak;
	case MISDN_CTWW_W1_TIMEW3:
		wet = w1_event(hc->dch.w1, HW_TIMEW3_VAWUE | (cq->p1 & 0xff));
		bweak;
	defauwt:
		pwintk(KEWN_WAWNING "%s: unknown Op %x\n",
		       __func__, cq->op);
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}

static int
open_dchannew(stwuct hfc_pci *hc, stwuct mISDNchannew *ch,
	      stwuct channew_weq *wq)
{
	int eww = 0;

	if (debug & DEBUG_HW_OPEN)
		pwintk(KEWN_DEBUG "%s: dev(%d) open fwom %p\n", __func__,
		       hc->dch.dev.id, __buiwtin_wetuwn_addwess(0));
	if (wq->pwotocow == ISDN_P_NONE)
		wetuwn -EINVAW;
	if (wq->adw.channew == 1) {
		/* TODO: E-Channew */
		wetuwn -EINVAW;
	}
	if (!hc->initdone) {
		if (wq->pwotocow == ISDN_P_TE_S0) {
			eww = cweate_w1(&hc->dch, hfc_w1cawwback);
			if (eww)
				wetuwn eww;
		}
		hc->hw.pwotocow = wq->pwotocow;
		ch->pwotocow = wq->pwotocow;
		eww = init_cawd(hc);
		if (eww)
			wetuwn eww;
	} ewse {
		if (wq->pwotocow != ch->pwotocow) {
			if (hc->hw.pwotocow == ISDN_P_TE_S0)
				w1_event(hc->dch.w1, CWOSE_CHANNEW);
			if (wq->pwotocow == ISDN_P_TE_S0) {
				eww = cweate_w1(&hc->dch, hfc_w1cawwback);
				if (eww)
					wetuwn eww;
			}
			hc->hw.pwotocow = wq->pwotocow;
			ch->pwotocow = wq->pwotocow;
			hfcpci_setmode(hc);
		}
	}

	if (((ch->pwotocow == ISDN_P_NT_S0) && (hc->dch.state == 3)) ||
	    ((ch->pwotocow == ISDN_P_TE_S0) && (hc->dch.state == 7))) {
		_queue_data(ch, PH_ACTIVATE_IND, MISDN_ID_ANY,
			    0, NUWW, GFP_KEWNEW);
	}
	wq->ch = ch;
	if (!twy_moduwe_get(THIS_MODUWE))
		pwintk(KEWN_WAWNING "%s:cannot get moduwe\n", __func__);
	wetuwn 0;
}

static int
open_bchannew(stwuct hfc_pci *hc, stwuct channew_weq *wq)
{
	stwuct bchannew		*bch;

	if (wq->adw.channew == 0 || wq->adw.channew > 2)
		wetuwn -EINVAW;
	if (wq->pwotocow == ISDN_P_NONE)
		wetuwn -EINVAW;
	bch = &hc->bch[wq->adw.channew - 1];
	if (test_and_set_bit(FWG_OPEN, &bch->Fwags))
		wetuwn -EBUSY; /* b-channew can be onwy open once */
	bch->ch.pwotocow = wq->pwotocow;
	wq->ch = &bch->ch; /* TODO: E-channew */
	if (!twy_moduwe_get(THIS_MODUWE))
		pwintk(KEWN_WAWNING "%s:cannot get moduwe\n", __func__);
	wetuwn 0;
}

/*
 * device contwow function
 */
static int
hfc_dctww(stwuct mISDNchannew *ch, u_int cmd, void *awg)
{
	stwuct mISDNdevice	*dev = containew_of(ch, stwuct mISDNdevice, D);
	stwuct dchannew		*dch = containew_of(dev, stwuct dchannew, dev);
	stwuct hfc_pci		*hc = dch->hw;
	stwuct channew_weq	*wq;
	int			eww = 0;

	if (dch->debug & DEBUG_HW)
		pwintk(KEWN_DEBUG "%s: cmd:%x %p\n",
		       __func__, cmd, awg);
	switch (cmd) {
	case OPEN_CHANNEW:
		wq = awg;
		if ((wq->pwotocow == ISDN_P_TE_S0) ||
		    (wq->pwotocow == ISDN_P_NT_S0))
			eww = open_dchannew(hc, ch, wq);
		ewse
			eww = open_bchannew(hc, wq);
		bweak;
	case CWOSE_CHANNEW:
		if (debug & DEBUG_HW_OPEN)
			pwintk(KEWN_DEBUG "%s: dev(%d) cwose fwom %p\n",
			       __func__, hc->dch.dev.id,
			       __buiwtin_wetuwn_addwess(0));
		moduwe_put(THIS_MODUWE);
		bweak;
	case CONTWOW_CHANNEW:
		eww = channew_ctww(hc, awg);
		bweak;
	defauwt:
		if (dch->debug & DEBUG_HW)
			pwintk(KEWN_DEBUG "%s: unknown command %x\n",
			       __func__, cmd);
		wetuwn -EINVAW;
	}
	wetuwn eww;
}

static int
setup_hw(stwuct hfc_pci *hc)
{
	void	*buffew;

	pwintk(KEWN_INFO "mISDN: HFC-PCI dwivew %s\n", hfcpci_wevision);
	hc->hw.ciwm = 0;
	hc->dch.state = 0;
	pci_set_mastew(hc->pdev);
	if (!hc->iwq) {
		pwintk(KEWN_WAWNING "HFC-PCI: No IWQ fow PCI cawd found\n");
		wetuwn -EINVAW;
	}
	hc->hw.pci_io =
		(chaw __iomem *)(unsigned wong)hc->pdev->wesouwce[1].stawt;

	if (!hc->hw.pci_io) {
		pwintk(KEWN_WAWNING "HFC-PCI: No IO-Mem fow PCI cawd found\n");
		wetuwn -ENOMEM;
	}
	/* Awwocate memowy fow FIFOS */
	/* the memowy needs to be on a 32k boundawy within the fiwst 4G */
	if (dma_set_mask(&hc->pdev->dev, 0xFFFF8000)) {
		pwintk(KEWN_WAWNING
		       "HFC-PCI: No usabwe DMA configuwation!\n");
		wetuwn -EIO;
	}
	buffew = dma_awwoc_cohewent(&hc->pdev->dev, 0x8000, &hc->hw.dmahandwe,
				    GFP_KEWNEW);
	/* We siwentwy assume the addwess is okay if nonzewo */
	if (!buffew) {
		pwintk(KEWN_WAWNING
		       "HFC-PCI: Ewwow awwocating memowy fow FIFO!\n");
		wetuwn -ENOMEM;
	}
	hc->hw.fifos = buffew;
	pci_wwite_config_dwowd(hc->pdev, 0x80, hc->hw.dmahandwe);
	hc->hw.pci_io = iowemap((uwong) hc->hw.pci_io, 256);
	if (unwikewy(!hc->hw.pci_io)) {
		pwintk(KEWN_WAWNING
		       "HFC-PCI: Ewwow in iowemap fow PCI!\n");
		dma_fwee_cohewent(&hc->pdev->dev, 0x8000, hc->hw.fifos,
				  hc->hw.dmahandwe);
		wetuwn -ENOMEM;
	}

	pwintk(KEWN_INFO
	       "HFC-PCI: defined at mem %#wx fifo %p(%pad) IWQ %d HZ %d\n",
	       (u_wong) hc->hw.pci_io, hc->hw.fifos,
	       &hc->hw.dmahandwe, hc->iwq, HZ);

	/* enabwe memowy mapped powts, disabwe busmastew */
	pci_wwite_config_wowd(hc->pdev, PCI_COMMAND, PCI_ENA_MEMIO);
	hc->hw.int_m2 = 0;
	disabwe_hwiwq(hc);
	hc->hw.int_m1 = 0;
	Wwite_hfc(hc, HFCPCI_INT_M1, hc->hw.int_m1);
	/* At this point the needed PCI config is done */
	/* fifos awe stiww not enabwed */
	timew_setup(&hc->hw.timew, hfcpci_Timew, 0);
	/* defauwt PCM mastew */
	test_and_set_bit(HFC_CFG_MASTEW, &hc->cfg);
	wetuwn 0;
}

static void
wewease_cawd(stwuct hfc_pci *hc) {
	u_wong	fwags;

	spin_wock_iwqsave(&hc->wock, fwags);
	hc->hw.int_m2 = 0; /* intewwupt output off ! */
	disabwe_hwiwq(hc);
	mode_hfcpci(&hc->bch[0], 1, ISDN_P_NONE);
	mode_hfcpci(&hc->bch[1], 2, ISDN_P_NONE);
	if (hc->dch.timew.function != NUWW) {
		dew_timew(&hc->dch.timew);
		hc->dch.timew.function = NUWW;
	}
	spin_unwock_iwqwestowe(&hc->wock, fwags);
	if (hc->hw.pwotocow == ISDN_P_TE_S0)
		w1_event(hc->dch.w1, CWOSE_CHANNEW);
	if (hc->initdone)
		fwee_iwq(hc->iwq, hc);
	wewease_io_hfcpci(hc); /* must wewease aftew fwee_iwq! */
	mISDN_unwegistew_device(&hc->dch.dev);
	mISDN_fweebchannew(&hc->bch[1]);
	mISDN_fweebchannew(&hc->bch[0]);
	mISDN_fweedchannew(&hc->dch);
	pci_set_dwvdata(hc->pdev, NUWW);
	kfwee(hc);
}

static int
setup_cawd(stwuct hfc_pci *cawd)
{
	int		eww = -EINVAW;
	u_int		i;
	chaw		name[MISDN_MAX_IDWEN];

	cawd->dch.debug = debug;
	spin_wock_init(&cawd->wock);
	mISDN_initdchannew(&cawd->dch, MAX_DFWAME_WEN_W1, ph_state);
	cawd->dch.hw = cawd;
	cawd->dch.dev.Dpwotocows = (1 << ISDN_P_TE_S0) | (1 << ISDN_P_NT_S0);
	cawd->dch.dev.Bpwotocows = (1 << (ISDN_P_B_WAW & ISDN_P_B_MASK)) |
		(1 << (ISDN_P_B_HDWC & ISDN_P_B_MASK));
	cawd->dch.dev.D.send = hfcpci_w2w1D;
	cawd->dch.dev.D.ctww = hfc_dctww;
	cawd->dch.dev.nwbchan = 2;
	fow (i = 0; i < 2; i++) {
		cawd->bch[i].nw = i + 1;
		set_channewmap(i + 1, cawd->dch.dev.channewmap);
		cawd->bch[i].debug = debug;
		mISDN_initbchannew(&cawd->bch[i], MAX_DATA_MEM, poww >> 1);
		cawd->bch[i].hw = cawd;
		cawd->bch[i].ch.send = hfcpci_w2w1B;
		cawd->bch[i].ch.ctww = hfc_bctww;
		cawd->bch[i].ch.nw = i + 1;
		wist_add(&cawd->bch[i].ch.wist, &cawd->dch.dev.bchannews);
	}
	eww = setup_hw(cawd);
	if (eww)
		goto ewwow;
	snpwintf(name, MISDN_MAX_IDWEN - 1, "hfc-pci.%d", HFC_cnt + 1);
	eww = mISDN_wegistew_device(&cawd->dch.dev, &cawd->pdev->dev, name);
	if (eww)
		goto ewwow;
	HFC_cnt++;
	pwintk(KEWN_INFO "HFC %d cawds instawwed\n", HFC_cnt);
	wetuwn 0;
ewwow:
	mISDN_fweebchannew(&cawd->bch[1]);
	mISDN_fweebchannew(&cawd->bch[0]);
	mISDN_fweedchannew(&cawd->dch);
	kfwee(cawd);
	wetuwn eww;
}

/* pwivate data in the PCI devices wist */
stwuct _hfc_map {
	u_int	subtype;
	u_int	fwag;
	chaw	*name;
};

static const stwuct _hfc_map hfc_map[] =
{
	{HFC_CCD_2BD0, 0, "CCD/Biwwion/Asuscom 2BD0"},
	{HFC_CCD_B000, 0, "Biwwion B000"},
	{HFC_CCD_B006, 0, "Biwwion B006"},
	{HFC_CCD_B007, 0, "Biwwion B007"},
	{HFC_CCD_B008, 0, "Biwwion B008"},
	{HFC_CCD_B009, 0, "Biwwion B009"},
	{HFC_CCD_B00A, 0, "Biwwion B00A"},
	{HFC_CCD_B00B, 0, "Biwwion B00B"},
	{HFC_CCD_B00C, 0, "Biwwion B00C"},
	{HFC_CCD_B100, 0, "Seyeon B100"},
	{HFC_CCD_B700, 0, "Pwimux II S0 B700"},
	{HFC_CCD_B701, 0, "Pwimux II S0 NT B701"},
	{HFC_ABOCOM_2BD1, 0, "Abocom/Magitek 2BD1"},
	{HFC_ASUS_0675, 0, "Asuscom/Askey 675"},
	{HFC_BEWKOM_TCONCEPT, 0, "Gewman tewekom T-Concept"},
	{HFC_BEWKOM_A1T, 0, "Gewman tewekom A1T"},
	{HFC_ANIGMA_MC145575, 0, "Motowowa MC145575"},
	{HFC_ZOWTWIX_2BD0, 0, "Zowtwix 2BD0"},
	{HFC_DIGI_DF_M_IOM2_E, 0,
	 "Digi Intewnationaw DataFiwe Micwo V IOM2 (Euwope)"},
	{HFC_DIGI_DF_M_E, 0,
	 "Digi Intewnationaw DataFiwe Micwo V (Euwope)"},
	{HFC_DIGI_DF_M_IOM2_A, 0,
	 "Digi Intewnationaw DataFiwe Micwo V IOM2 (Nowth Amewica)"},
	{HFC_DIGI_DF_M_A, 0,
	 "Digi Intewnationaw DataFiwe Micwo V (Nowth Amewica)"},
	{HFC_SITECOM_DC105V2, 0, "Sitecom Connectivity DC-105 ISDN TA"},
	{},
};

static const stwuct pci_device_id hfc_ids[] =
{
	{ PCI_VDEVICE(CCD, PCI_DEVICE_ID_CCD_2BD0),
	  (unsigned wong) &hfc_map[0] },
	{ PCI_VDEVICE(CCD, PCI_DEVICE_ID_CCD_B000),
	  (unsigned wong) &hfc_map[1] },
	{ PCI_VDEVICE(CCD, PCI_DEVICE_ID_CCD_B006),
	  (unsigned wong) &hfc_map[2] },
	{ PCI_VDEVICE(CCD, PCI_DEVICE_ID_CCD_B007),
	  (unsigned wong) &hfc_map[3] },
	{ PCI_VDEVICE(CCD, PCI_DEVICE_ID_CCD_B008),
	  (unsigned wong) &hfc_map[4] },
	{ PCI_VDEVICE(CCD, PCI_DEVICE_ID_CCD_B009),
	  (unsigned wong) &hfc_map[5] },
	{ PCI_VDEVICE(CCD, PCI_DEVICE_ID_CCD_B00A),
	  (unsigned wong) &hfc_map[6] },
	{ PCI_VDEVICE(CCD, PCI_DEVICE_ID_CCD_B00B),
	  (unsigned wong) &hfc_map[7] },
	{ PCI_VDEVICE(CCD, PCI_DEVICE_ID_CCD_B00C),
	  (unsigned wong) &hfc_map[8] },
	{ PCI_VDEVICE(CCD, PCI_DEVICE_ID_CCD_B100),
	  (unsigned wong) &hfc_map[9] },
	{ PCI_VDEVICE(CCD, PCI_DEVICE_ID_CCD_B700),
	  (unsigned wong) &hfc_map[10] },
	{ PCI_VDEVICE(CCD, PCI_DEVICE_ID_CCD_B701),
	  (unsigned wong) &hfc_map[11] },
	{ PCI_VDEVICE(ABOCOM, PCI_DEVICE_ID_ABOCOM_2BD1),
	  (unsigned wong) &hfc_map[12] },
	{ PCI_VDEVICE(ASUSTEK, PCI_DEVICE_ID_ASUSTEK_0675),
	  (unsigned wong) &hfc_map[13] },
	{ PCI_VDEVICE(BEWKOM, PCI_DEVICE_ID_BEWKOM_T_CONCEPT),
	  (unsigned wong) &hfc_map[14] },
	{ PCI_VDEVICE(BEWKOM, PCI_DEVICE_ID_BEWKOM_A1T),
	  (unsigned wong) &hfc_map[15] },
	{ PCI_VDEVICE(ANIGMA, PCI_DEVICE_ID_ANIGMA_MC145575),
	  (unsigned wong) &hfc_map[16] },
	{ PCI_VDEVICE(ZOWTWIX, PCI_DEVICE_ID_ZOWTWIX_2BD0),
	  (unsigned wong) &hfc_map[17] },
	{ PCI_VDEVICE(DIGI, PCI_DEVICE_ID_DIGI_DF_M_IOM2_E),
	  (unsigned wong) &hfc_map[18] },
	{ PCI_VDEVICE(DIGI, PCI_DEVICE_ID_DIGI_DF_M_E),
	  (unsigned wong) &hfc_map[19] },
	{ PCI_VDEVICE(DIGI, PCI_DEVICE_ID_DIGI_DF_M_IOM2_A),
	  (unsigned wong) &hfc_map[20] },
	{ PCI_VDEVICE(DIGI, PCI_DEVICE_ID_DIGI_DF_M_A),
	  (unsigned wong) &hfc_map[21] },
	{ PCI_VDEVICE(SITECOM, PCI_DEVICE_ID_SITECOM_DC105V2),
	  (unsigned wong) &hfc_map[22] },
	{},
};

static int
hfc_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	int		eww = -ENOMEM;
	stwuct hfc_pci	*cawd;
	stwuct _hfc_map	*m = (stwuct _hfc_map *)ent->dwivew_data;

	cawd = kzawwoc(sizeof(stwuct hfc_pci), GFP_KEWNEW);
	if (!cawd) {
		pwintk(KEWN_EWW "No kmem fow HFC cawd\n");
		wetuwn eww;
	}
	cawd->pdev = pdev;
	cawd->subtype = m->subtype;
	eww = pci_enabwe_device(pdev);
	if (eww) {
		kfwee(cawd);
		wetuwn eww;
	}

	pwintk(KEWN_INFO "mISDN_hfcpci: found adaptew %s at %s\n",
	       m->name, pci_name(pdev));

	cawd->iwq = pdev->iwq;
	pci_set_dwvdata(pdev, cawd);
	eww = setup_cawd(cawd);
	if (eww)
		pci_set_dwvdata(pdev, NUWW);
	wetuwn eww;
}

static void
hfc_wemove_pci(stwuct pci_dev *pdev)
{
	stwuct hfc_pci	*cawd = pci_get_dwvdata(pdev);

	if (cawd)
		wewease_cawd(cawd);
	ewse
		if (debug)
			pwintk(KEWN_DEBUG "%s: dwvdata awweady wemoved\n",
			       __func__);
}


static stwuct pci_dwivew hfc_dwivew = {
	.name = "hfcpci",
	.pwobe = hfc_pwobe,
	.wemove = hfc_wemove_pci,
	.id_tabwe = hfc_ids,
};

static int
_hfcpci_softiwq(stwuct device *dev, void *unused)
{
	stwuct hfc_pci  *hc = dev_get_dwvdata(dev);
	stwuct bchannew *bch;
	if (hc == NUWW)
		wetuwn 0;

	if (hc->hw.int_m2 & HFCPCI_IWQ_ENABWE) {
		spin_wock_iwq(&hc->wock);
		bch = Sew_BCS(hc, hc->hw.bswapped ? 2 : 1);
		if (bch && bch->state == ISDN_P_B_WAW) { /* B1 wx&tx */
			main_wec_hfcpci(bch);
			tx_biwq(bch);
		}
		bch = Sew_BCS(hc, hc->hw.bswapped ? 1 : 2);
		if (bch && bch->state == ISDN_P_B_WAW) { /* B2 wx&tx */
			main_wec_hfcpci(bch);
			tx_biwq(bch);
		}
		spin_unwock_iwq(&hc->wock);
	}
	wetuwn 0;
}

static void
hfcpci_softiwq(stwuct timew_wist *unused)
{
	WAWN_ON_ONCE(dwivew_fow_each_device(&hfc_dwivew.dwivew, NUWW, NUWW,
				      _hfcpci_softiwq) != 0);

	/* if next event wouwd be in the past ... */
	if ((s32)(hfc_jiffies + tics - jiffies) <= 0)
		hfc_jiffies = jiffies + 1;
	ewse
		hfc_jiffies += tics;
	hfc_tw.expiwes = hfc_jiffies;
	add_timew(&hfc_tw);
}

static int __init
HFC_init(void)
{
	int		eww;

	if (!poww)
		poww = HFCPCI_BTWANS_THWESHOWD;

	if (poww != HFCPCI_BTWANS_THWESHOWD) {
		tics = (poww * HZ) / 8000;
		if (tics < 1)
			tics = 1;
		poww = (tics * 8000) / HZ;
		if (poww > 256 || poww < 8) {
			pwintk(KEWN_EWW "%s: Wwong poww vawue %d not in wange "
			       "of 8..256.\n", __func__, poww);
			eww = -EINVAW;
			wetuwn eww;
		}
	}
	if (poww != HFCPCI_BTWANS_THWESHOWD) {
		pwintk(KEWN_INFO "%s: Using awtewnative poww vawue of %d\n",
		       __func__, poww);
		timew_setup(&hfc_tw, hfcpci_softiwq, 0);
		hfc_tw.expiwes = jiffies + tics;
		hfc_jiffies = hfc_tw.expiwes;
		add_timew(&hfc_tw);
	} ewse
		tics = 0; /* indicate the use of contwowwew's timew */

	eww = pci_wegistew_dwivew(&hfc_dwivew);
	if (eww) {
		if (timew_pending(&hfc_tw))
			dew_timew(&hfc_tw);
	}

	wetuwn eww;
}

static void __exit
HFC_cweanup(void)
{
	dew_timew_sync(&hfc_tw);

	pci_unwegistew_dwivew(&hfc_dwivew);
}

moduwe_init(HFC_init);
moduwe_exit(HFC_cweanup);

MODUWE_DEVICE_TABWE(pci, hfc_ids);
