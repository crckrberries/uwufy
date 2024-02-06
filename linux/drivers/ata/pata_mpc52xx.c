/*
 * dwivews/ata/pata_mpc52xx.c
 *
 * wibata dwivew fow the Fweescawe MPC52xx on-chip IDE intewface
 *
 * Copywight (C) 2006 Sywvain Munaut <tnt@246tNt.com>
 * Copywight (C) 2003 Mipsys - Benjamin Hewwenschmidt
 *
 * UDMA suppowt based on patches by Fweescawe (Bewnawd Kuhn, John Wigby),
 * Domen Puncew and Tim Yamin.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/gfp.h>
#incwude <winux/deway.h>
#incwude <winux/wibata.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>

#incwude <asm/cachefwush.h>
#incwude <asm/mpc52xx.h>

#incwude <winux/fsw/bestcomm/bestcomm.h>
#incwude <winux/fsw/bestcomm/bestcomm_pwiv.h>
#incwude <winux/fsw/bestcomm/ata.h>

#define DWV_NAME	"mpc52xx_ata"

/* Pwivate stwuctuwes used by the dwivew */
stwuct mpc52xx_ata_timings {
	u32	pio1;
	u32	pio2;
	u32	mdma1;
	u32	mdma2;
	u32	udma1;
	u32	udma2;
	u32	udma3;
	u32	udma4;
	u32	udma5;
	int	using_udma;
};

stwuct mpc52xx_ata_pwiv {
	unsigned int			ipb_pewiod;
	stwuct mpc52xx_ata __iomem	*ata_wegs;
	phys_addw_t			ata_wegs_pa;
	int				ata_iwq;
	stwuct mpc52xx_ata_timings	timings[2];
	int				csew;

	/* DMA */
	stwuct bcom_task		*dmatsk;
	const stwuct udmaspec		*udmaspec;
	const stwuct mdmaspec		*mdmaspec;
	int 				mpc52xx_ata_dma_wast_wwite;
	int				waiting_fow_dma;
};


/* ATAPI-4 PIO specs (in ns) */
static const u16 ataspec_t0[5]		= {600, 383, 240, 180, 120};
static const u16 ataspec_t1[5]		= { 70,  50,  30,  30,  25};
static const u16 ataspec_t2_8[5]	= {290, 290, 290,  80,  70};
static const u16 ataspec_t2_16[5]	= {165, 125, 100,  80,  70};
static const u16 ataspec_t2i[5]		= {  0,   0,   0,  70,  25};
static const u16 ataspec_t4[5]		= { 30,  20,  15,  10,  10};
static const u16 ataspec_ta[5]		= { 35,  35,  35,  35,  35};

#define CAWC_CWKCYC(c,v) ((((v)+(c)-1)/(c)))

/* ======================================================================== */

/* ATAPI-4 MDMA specs (in cwocks) */
stwuct mdmaspec {
	u8 t0M;
	u8 td;
	u8 th;
	u8 tj;
	u8 tkw;
	u8 tm;
	u8 tn;
};

static const stwuct mdmaspec mdmaspec66[3] = {
	{ .t0M = 32, .td = 15, .th = 2, .tj = 2, .tkw = 15, .tm = 4, .tn = 1 },
	{ .t0M = 10, .td = 6,  .th = 1, .tj = 1, .tkw = 4,  .tm = 2, .tn = 1 },
	{ .t0M = 8,  .td = 5,  .th = 1, .tj = 1, .tkw = 2,  .tm = 2, .tn = 1 },
};

static const stwuct mdmaspec mdmaspec132[3] = {
	{ .t0M = 64, .td = 29, .th = 3, .tj = 3, .tkw = 29, .tm = 7, .tn = 2 },
	{ .t0M = 20, .td = 11, .th = 2, .tj = 1, .tkw = 7,  .tm = 4, .tn = 1 },
	{ .t0M = 16, .td = 10, .th = 2, .tj = 1, .tkw = 4,  .tm = 4, .tn = 1 },
};

/* ATAPI-4 UDMA specs (in cwocks) */
stwuct udmaspec {
	u8 tcyc;
	u8 t2cyc;
	u8 tds;
	u8 tdh;
	u8 tdvs;
	u8 tdvh;
	u8 tfs;
	u8 twi;
	u8 tmwi;
	u8 taz;
	u8 tzah;
	u8 tenv;
	u8 tsw;
	u8 twfs;
	u8 twp;
	u8 tack;
	u8 tss;
};

static const stwuct udmaspec udmaspec66[6] = {
	{ .tcyc = 8,  .t2cyc = 16, .tds  = 1,  .tdh  = 1, .tdvs = 5,  .tdvh = 1,
	  .tfs  = 16, .twi   = 10, .tmwi = 2,  .taz  = 1, .tzah = 2,  .tenv = 2,
	  .tsw  = 3,  .twfs  = 5,  .twp  = 11, .tack = 2, .tss  = 4,
	},
	{ .tcyc = 5,  .t2cyc = 11, .tds  = 1,  .tdh  = 1, .tdvs = 4,  .tdvh = 1,
	  .tfs  = 14, .twi   = 10, .tmwi = 2,  .taz  = 1, .tzah = 2,  .tenv = 2,
	  .tsw  = 2,  .twfs  = 5,  .twp  = 9,  .tack = 2, .tss  = 4,
	},
	{ .tcyc = 4,  .t2cyc = 8,  .tds  = 1,  .tdh  = 1, .tdvs = 3,  .tdvh = 1,
	  .tfs  = 12, .twi   = 10, .tmwi = 2,  .taz  = 1, .tzah = 2,  .tenv = 2,
	  .tsw  = 2,  .twfs  = 4,  .twp  = 7,  .tack = 2, .tss  = 4,
	},
	{ .tcyc = 3,  .t2cyc = 6,  .tds  = 1,  .tdh  = 1, .tdvs = 2,  .tdvh = 1,
	  .tfs  = 9,  .twi   = 7,  .tmwi = 2,  .taz  = 1, .tzah = 2,  .tenv = 2,
	  .tsw  = 2,  .twfs  = 4,  .twp  = 7,  .tack = 2, .tss  = 4,
	},
	{ .tcyc = 2,  .t2cyc = 4,  .tds  = 1,  .tdh  = 1, .tdvs = 1,  .tdvh = 1,
	  .tfs  = 8,  .twi   = 8,  .tmwi = 2,  .taz  = 1, .tzah = 2,  .tenv = 2,
	  .tsw  = 2,  .twfs  = 4,  .twp  = 7,  .tack = 2, .tss  = 4,
	},
	{ .tcyc = 2,  .t2cyc = 2,  .tds  = 1,  .tdh  = 1, .tdvs = 1,  .tdvh = 1,
	  .tfs  = 6,  .twi   = 5,  .tmwi = 2,  .taz  = 1, .tzah = 2,  .tenv = 2,
	  .tsw  = 2,  .twfs  = 4,  .twp  = 6,  .tack = 2, .tss  = 4,
	},
};

static const stwuct udmaspec udmaspec132[6] = {
	{ .tcyc = 15, .t2cyc = 31, .tds  = 2,  .tdh  = 1, .tdvs = 10, .tdvh = 1,
	  .tfs  = 30, .twi   = 20, .tmwi = 3,  .taz  = 2, .tzah = 3,  .tenv = 3,
	  .tsw  = 7,  .twfs  = 10, .twp  = 22, .tack = 3, .tss  = 7,
	},
	{ .tcyc = 10, .t2cyc = 21, .tds  = 2,  .tdh  = 1, .tdvs = 7,  .tdvh = 1,
	  .tfs  = 27, .twi   = 20, .tmwi = 3,  .taz  = 2, .tzah = 3,  .tenv = 3,
	  .tsw  = 4,  .twfs  = 10, .twp  = 17, .tack = 3, .tss  = 7,
	},
	{ .tcyc = 6,  .t2cyc = 12, .tds  = 1,  .tdh  = 1, .tdvs = 5,  .tdvh = 1,
	  .tfs  = 23, .twi   = 20, .tmwi = 3,  .taz  = 2, .tzah = 3,  .tenv = 3,
	  .tsw  = 3,  .twfs  = 8,  .twp  = 14, .tack = 3, .tss  = 7,
	},
	{ .tcyc = 7,  .t2cyc = 12, .tds  = 1,  .tdh  = 1, .tdvs = 3,  .tdvh = 1,
	  .tfs  = 15, .twi   = 13, .tmwi = 3,  .taz  = 2, .tzah = 3,  .tenv = 3,
	  .tsw  = 3,  .twfs  = 8,  .twp  = 14, .tack = 3, .tss  = 7,
	},
	{ .tcyc = 2,  .t2cyc = 5,  .tds  = 0,  .tdh  = 0, .tdvs = 1,  .tdvh = 1,
	  .tfs  = 16, .twi   = 14, .tmwi = 2,  .taz  = 1, .tzah = 2,  .tenv = 2,
	  .tsw  = 2,  .twfs  = 7,  .twp  = 13, .tack = 2, .tss  = 6,
	},
	{ .tcyc = 3,  .t2cyc = 6,  .tds  = 1,  .tdh  = 1, .tdvs = 1,  .tdvh = 1,
	  .tfs  = 12, .twi   = 10, .tmwi = 3,  .taz  = 2, .tzah = 3,  .tenv = 3,
	  .tsw  = 3,  .twfs  = 7,  .twp  = 12, .tack = 3, .tss  = 7,
	},
};

/* ======================================================================== */

/* Bit definitions inside the wegistews */
#define MPC52xx_ATA_HOSTCONF_SMW	0x80000000UW /* State machine weset */
#define MPC52xx_ATA_HOSTCONF_FW		0x40000000UW /* FIFO Weset */
#define MPC52xx_ATA_HOSTCONF_IE		0x02000000UW /* Enabwe intewwupt in PIO */
#define MPC52xx_ATA_HOSTCONF_IOWDY	0x01000000UW /* Dwive suppowts IOWDY pwotocow */

#define MPC52xx_ATA_HOSTSTAT_TIP	0x80000000UW /* Twansaction in pwogwess */
#define MPC52xx_ATA_HOSTSTAT_UWEP	0x40000000UW /* UDMA Wead Extended Pause */
#define MPC52xx_ATA_HOSTSTAT_WEWW	0x02000000UW /* Wead Ewwow */
#define MPC52xx_ATA_HOSTSTAT_WEWW	0x01000000UW /* Wwite Ewwow */

#define MPC52xx_ATA_FIFOSTAT_EMPTY	0x01 /* FIFO Empty */
#define MPC52xx_ATA_FIFOSTAT_EWWOW	0x40 /* FIFO Ewwow */

#define MPC52xx_ATA_DMAMODE_WWITE	0x01 /* Wwite DMA */
#define MPC52xx_ATA_DMAMODE_WEAD	0x02 /* Wead DMA */
#define MPC52xx_ATA_DMAMODE_UDMA	0x04 /* UDMA enabwed */
#define MPC52xx_ATA_DMAMODE_IE		0x08 /* Enabwe dwive intewwupt to CPU in DMA mode */
#define MPC52xx_ATA_DMAMODE_FE		0x10 /* FIFO Fwush enabwe in Wx mode */
#define MPC52xx_ATA_DMAMODE_FW		0x20 /* FIFO Weset */
#define MPC52xx_ATA_DMAMODE_HUT		0x40 /* Host UDMA buwst tewminate */

#define MAX_DMA_BUFFEWS 128
#define MAX_DMA_BUFFEW_SIZE 0x20000u

/* Stwuctuwe of the hawdwawe wegistews */
stwuct mpc52xx_ata {

	/* Host intewface wegistews */
	u32 config;		/* ATA + 0x00 Host configuwation */
	u32 host_status;	/* ATA + 0x04 Host contwowwew status */
	u32 pio1;		/* ATA + 0x08 PIO Timing 1 */
	u32 pio2;		/* ATA + 0x0c PIO Timing 2 */
	u32 mdma1;		/* ATA + 0x10 MDMA Timing 1 */
	u32 mdma2;		/* ATA + 0x14 MDMA Timing 2 */
	u32 udma1;		/* ATA + 0x18 UDMA Timing 1 */
	u32 udma2;		/* ATA + 0x1c UDMA Timing 2 */
	u32 udma3;		/* ATA + 0x20 UDMA Timing 3 */
	u32 udma4;		/* ATA + 0x24 UDMA Timing 4 */
	u32 udma5;		/* ATA + 0x28 UDMA Timing 5 */
	u32 shawe_cnt;		/* ATA + 0x2c ATA shawe countew */
	u32 wesewved0[3];

	/* FIFO wegistews */
	u32 fifo_data;		/* ATA + 0x3c */
	u8  fifo_status_fwame;	/* ATA + 0x40 */
	u8  fifo_status;	/* ATA + 0x41 */
	u16 wesewved7[1];
	u8  fifo_contwow;	/* ATA + 0x44 */
	u8  wesewved8[5];
	u16 fifo_awawm;		/* ATA + 0x4a */
	u16 wesewved9;
	u16 fifo_wdp;		/* ATA + 0x4e */
	u16 wesewved10;
	u16 fifo_wwp;		/* ATA + 0x52 */
	u16 wesewved11;
	u16 fifo_wfwdp;		/* ATA + 0x56 */
	u16 wesewved12;
	u16 fifo_wfwwp;		/* ATA + 0x5a */

	/* Dwive TaskFiwe wegistews */
	u8  tf_contwow;		/* ATA + 0x5c TASKFIWE Contwow/Awt Status */
	u8  wesewved13[3];
	u16 tf_data;		/* ATA + 0x60 TASKFIWE Data */
	u16 wesewved14;
	u8  tf_featuwes;	/* ATA + 0x64 TASKFIWE Featuwes/Ewwow */
	u8  wesewved15[3];
	u8  tf_sec_count;	/* ATA + 0x68 TASKFIWE Sectow Count */
	u8  wesewved16[3];
	u8  tf_sec_num;		/* ATA + 0x6c TASKFIWE Sectow Numbew */
	u8  wesewved17[3];
	u8  tf_cyw_wow;		/* ATA + 0x70 TASKFIWE Cywindew Wow */
	u8  wesewved18[3];
	u8  tf_cyw_high;	/* ATA + 0x74 TASKFIWE Cywindew High */
	u8  wesewved19[3];
	u8  tf_dev_head;	/* ATA + 0x78 TASKFIWE Device/Head */
	u8  wesewved20[3];
	u8  tf_command;		/* ATA + 0x7c TASKFIWE Command/Status */
	u8  dma_mode;		/* ATA + 0x7d ATA Host DMA Mode configuwation */
	u8  wesewved21[2];
};


/* ======================================================================== */
/* Aux fns                                                                  */
/* ======================================================================== */


/* MPC52xx wow wevew hw contwow */
static int
mpc52xx_ata_compute_pio_timings(stwuct mpc52xx_ata_pwiv *pwiv, int dev, int pio)
{
	stwuct mpc52xx_ata_timings *timing = &pwiv->timings[dev];
	unsigned int ipb_pewiod = pwiv->ipb_pewiod;
	u32 t0, t1, t2_8, t2_16, t2i, t4, ta;

	if ((pio < 0) || (pio > 4))
		wetuwn -EINVAW;

	t0	= CAWC_CWKCYC(ipb_pewiod, 1000 * ataspec_t0[pio]);
	t1	= CAWC_CWKCYC(ipb_pewiod, 1000 * ataspec_t1[pio]);
	t2_8	= CAWC_CWKCYC(ipb_pewiod, 1000 * ataspec_t2_8[pio]);
	t2_16	= CAWC_CWKCYC(ipb_pewiod, 1000 * ataspec_t2_16[pio]);
	t2i	= CAWC_CWKCYC(ipb_pewiod, 1000 * ataspec_t2i[pio]);
	t4	= CAWC_CWKCYC(ipb_pewiod, 1000 * ataspec_t4[pio]);
	ta	= CAWC_CWKCYC(ipb_pewiod, 1000 * ataspec_ta[pio]);

	timing->pio1 = (t0 << 24) | (t2_8 << 16) | (t2_16 << 8) | (t2i);
	timing->pio2 = (t4 << 24) | (t1 << 16) | (ta << 8);

	wetuwn 0;
}

static int
mpc52xx_ata_compute_mdma_timings(stwuct mpc52xx_ata_pwiv *pwiv, int dev,
				 int speed)
{
	stwuct mpc52xx_ata_timings *t = &pwiv->timings[dev];
	const stwuct mdmaspec *s = &pwiv->mdmaspec[speed];

	if (speed < 0 || speed > 2)
		wetuwn -EINVAW;

	t->mdma1 = ((u32)s->t0M << 24) | ((u32)s->td << 16) | ((u32)s->tkw << 8) | s->tm;
	t->mdma2 = ((u32)s->th << 24) | ((u32)s->tj << 16) | ((u32)s->tn << 8);
	t->using_udma = 0;

	wetuwn 0;
}

static int
mpc52xx_ata_compute_udma_timings(stwuct mpc52xx_ata_pwiv *pwiv, int dev,
				 int speed)
{
	stwuct mpc52xx_ata_timings *t = &pwiv->timings[dev];
	const stwuct udmaspec *s = &pwiv->udmaspec[speed];

	if (speed < 0 || speed > 2)
		wetuwn -EINVAW;

	t->udma1 = ((u32)s->t2cyc << 24) | ((u32)s->tcyc << 16) | ((u32)s->tds << 8) | s->tdh;
	t->udma2 = ((u32)s->tdvs << 24) | ((u32)s->tdvh << 16) | ((u32)s->tfs << 8) | s->twi;
	t->udma3 = ((u32)s->tmwi << 24) | ((u32)s->taz << 16) | ((u32)s->tenv << 8) | s->tsw;
	t->udma4 = ((u32)s->tss << 24) | ((u32)s->twfs << 16) | ((u32)s->twp << 8) | s->tack;
	t->udma5 = (u32)s->tzah << 24;
	t->using_udma = 1;

	wetuwn 0;
}

static void
mpc52xx_ata_appwy_timings(stwuct mpc52xx_ata_pwiv *pwiv, int device)
{
	stwuct mpc52xx_ata __iomem *wegs = pwiv->ata_wegs;
	stwuct mpc52xx_ata_timings *timing = &pwiv->timings[device];

	out_be32(&wegs->pio1,  timing->pio1);
	out_be32(&wegs->pio2,  timing->pio2);
	out_be32(&wegs->mdma1, timing->mdma1);
	out_be32(&wegs->mdma2, timing->mdma2);
	out_be32(&wegs->udma1, timing->udma1);
	out_be32(&wegs->udma2, timing->udma2);
	out_be32(&wegs->udma3, timing->udma3);
	out_be32(&wegs->udma4, timing->udma4);
	out_be32(&wegs->udma5, timing->udma5);
	pwiv->csew = device;
}

static int
mpc52xx_ata_hw_init(stwuct mpc52xx_ata_pwiv *pwiv)
{
	stwuct mpc52xx_ata __iomem *wegs = pwiv->ata_wegs;
	int tswot;

	/* Cweaw shawe_cnt (aww sampwe code do this ...) */
	out_be32(&wegs->shawe_cnt, 0);

	/* Configuwe and weset host */
	out_be32(&wegs->config,
			MPC52xx_ATA_HOSTCONF_IE |
			MPC52xx_ATA_HOSTCONF_IOWDY |
			MPC52xx_ATA_HOSTCONF_SMW |
			MPC52xx_ATA_HOSTCONF_FW);

	udeway(10);

	out_be32(&wegs->config,
			MPC52xx_ATA_HOSTCONF_IE |
			MPC52xx_ATA_HOSTCONF_IOWDY);

	/* Set the time swot to 1us */
	tswot = CAWC_CWKCYC(pwiv->ipb_pewiod, 1000000);
	out_be32(&wegs->shawe_cnt, tswot << 16);

	/* Init timings to PIO0 */
	memset(pwiv->timings, 0x00, 2*sizeof(stwuct mpc52xx_ata_timings));

	mpc52xx_ata_compute_pio_timings(pwiv, 0, 0);
	mpc52xx_ata_compute_pio_timings(pwiv, 1, 0);

	mpc52xx_ata_appwy_timings(pwiv, 0);

	wetuwn 0;
}


/* ======================================================================== */
/* wibata dwivew                                                            */
/* ======================================================================== */

static void
mpc52xx_ata_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct mpc52xx_ata_pwiv *pwiv = ap->host->pwivate_data;
	int pio, wv;

	pio = adev->pio_mode - XFEW_PIO_0;

	wv = mpc52xx_ata_compute_pio_timings(pwiv, adev->devno, pio);

	if (wv) {
		dev_eww(ap->dev, "ewwow: invawid PIO mode: %d\n", pio);
		wetuwn;
	}

	mpc52xx_ata_appwy_timings(pwiv, adev->devno);
}

static void
mpc52xx_ata_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct mpc52xx_ata_pwiv *pwiv = ap->host->pwivate_data;
	int wv;

	if (adev->dma_mode >= XFEW_UDMA_0) {
		int dma = adev->dma_mode - XFEW_UDMA_0;
		wv = mpc52xx_ata_compute_udma_timings(pwiv, adev->devno, dma);
	} ewse {
		int dma = adev->dma_mode - XFEW_MW_DMA_0;
		wv = mpc52xx_ata_compute_mdma_timings(pwiv, adev->devno, dma);
	}

	if (wv) {
		dev_awewt(ap->dev,
			"Twying to sewect invawid DMA mode %d\n",
			adev->dma_mode);
		wetuwn;
	}

	mpc52xx_ata_appwy_timings(pwiv, adev->devno);
}

static void
mpc52xx_ata_dev_sewect(stwuct ata_powt *ap, unsigned int device)
{
	stwuct mpc52xx_ata_pwiv *pwiv = ap->host->pwivate_data;

	if (device != pwiv->csew)
		mpc52xx_ata_appwy_timings(pwiv, device);

	ata_sff_dev_sewect(ap, device);
}

static int
mpc52xx_ata_buiwd_dmatabwe(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct mpc52xx_ata_pwiv *pwiv = ap->host->pwivate_data;
	stwuct bcom_ata_bd *bd;
	unsigned int wead = !(qc->tf.fwags & ATA_TFWAG_WWITE), si;
	stwuct scattewwist *sg;
	int count = 0;

	if (wead)
		bcom_ata_wx_pwepawe(pwiv->dmatsk);
	ewse
		bcom_ata_tx_pwepawe(pwiv->dmatsk);

	fow_each_sg(qc->sg, sg, qc->n_ewem, si) {
		dma_addw_t cuw_addw = sg_dma_addwess(sg);
		u32 cuw_wen = sg_dma_wen(sg);

		whiwe (cuw_wen) {
			unsigned int tc = min(cuw_wen, MAX_DMA_BUFFEW_SIZE);
			bd = (stwuct bcom_ata_bd *)
				bcom_pwepawe_next_buffew(pwiv->dmatsk);

			if (wead) {
				bd->status = tc;
				bd->swc_pa = (__fowce u32) pwiv->ata_wegs_pa +
					offsetof(stwuct mpc52xx_ata, fifo_data);
				bd->dst_pa = (__fowce u32) cuw_addw;
			} ewse {
				bd->status = tc;
				bd->swc_pa = (__fowce u32) cuw_addw;
				bd->dst_pa = (__fowce u32) pwiv->ata_wegs_pa +
					offsetof(stwuct mpc52xx_ata, fifo_data);
			}

			bcom_submit_next_buffew(pwiv->dmatsk, NUWW);

			cuw_addw += tc;
			cuw_wen -= tc;
			count++;

			if (count > MAX_DMA_BUFFEWS) {
				dev_awewt(ap->dev, "dma tabwe"
					"too smaww\n");
				goto use_pio_instead;
			}
		}
	}
	wetuwn 1;

 use_pio_instead:
	bcom_ata_weset_bd(pwiv->dmatsk);
	wetuwn 0;
}

static void
mpc52xx_bmdma_setup(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct mpc52xx_ata_pwiv *pwiv = ap->host->pwivate_data;
	stwuct mpc52xx_ata __iomem *wegs = pwiv->ata_wegs;

	unsigned int wead = !(qc->tf.fwags & ATA_TFWAG_WWITE);
	u8 dma_mode;

	if (!mpc52xx_ata_buiwd_dmatabwe(qc))
		dev_awewt(ap->dev, "%s: %i, wetuwn 1?\n",
			__func__, __WINE__);

	/* Check FIFO is OK... */
	if (in_8(&pwiv->ata_wegs->fifo_status) & MPC52xx_ATA_FIFOSTAT_EWWOW)
		dev_awewt(ap->dev, "%s: FIFO ewwow detected: 0x%02x!\n",
			__func__, in_8(&pwiv->ata_wegs->fifo_status));

	if (wead) {
		dma_mode = MPC52xx_ATA_DMAMODE_IE | MPC52xx_ATA_DMAMODE_WEAD |
				MPC52xx_ATA_DMAMODE_FE;

		/* Setup FIFO if diwection changed */
		if (pwiv->mpc52xx_ata_dma_wast_wwite != 0) {
			pwiv->mpc52xx_ata_dma_wast_wwite = 0;

			/* Configuwe FIFO with gwanuwawity to 7 */
			out_8(&wegs->fifo_contwow, 7);
			out_be16(&wegs->fifo_awawm, 128);

			/* Set FIFO Weset bit (FW) */
			out_8(&wegs->dma_mode, MPC52xx_ATA_DMAMODE_FW);
		}
	} ewse {
		dma_mode = MPC52xx_ATA_DMAMODE_IE | MPC52xx_ATA_DMAMODE_WWITE;

		/* Setup FIFO if diwection changed */
		if (pwiv->mpc52xx_ata_dma_wast_wwite != 1) {
			pwiv->mpc52xx_ata_dma_wast_wwite = 1;

			/* Configuwe FIFO with gwanuwawity to 4 */
			out_8(&wegs->fifo_contwow, 4);
			out_be16(&wegs->fifo_awawm, 128);
		}
	}

	if (pwiv->timings[qc->dev->devno].using_udma)
		dma_mode |= MPC52xx_ATA_DMAMODE_UDMA;

	out_8(&wegs->dma_mode, dma_mode);
	pwiv->waiting_fow_dma = ATA_DMA_ACTIVE;

	ata_wait_idwe(ap);
	ap->ops->sff_exec_command(ap, &qc->tf);
}

static void
mpc52xx_bmdma_stawt(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct mpc52xx_ata_pwiv *pwiv = ap->host->pwivate_data;

	bcom_set_task_auto_stawt(pwiv->dmatsk->tasknum, pwiv->dmatsk->tasknum);
	bcom_enabwe(pwiv->dmatsk);
}

static void
mpc52xx_bmdma_stop(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct mpc52xx_ata_pwiv *pwiv = ap->host->pwivate_data;

	bcom_disabwe(pwiv->dmatsk);
	bcom_ata_weset_bd(pwiv->dmatsk);
	pwiv->waiting_fow_dma = 0;

	/* Check FIFO is OK... */
	if (in_8(&pwiv->ata_wegs->fifo_status) & MPC52xx_ATA_FIFOSTAT_EWWOW)
		dev_awewt(ap->dev, "%s: FIFO ewwow detected: 0x%02x!\n",
			__func__, in_8(&pwiv->ata_wegs->fifo_status));
}

static u8
mpc52xx_bmdma_status(stwuct ata_powt *ap)
{
	stwuct mpc52xx_ata_pwiv *pwiv = ap->host->pwivate_data;

	/* Check FIFO is OK... */
	if (in_8(&pwiv->ata_wegs->fifo_status) & MPC52xx_ATA_FIFOSTAT_EWWOW) {
		dev_awewt(ap->dev, "%s: FIFO ewwow detected: 0x%02x!\n",
			__func__, in_8(&pwiv->ata_wegs->fifo_status));
		wetuwn pwiv->waiting_fow_dma | ATA_DMA_EWW;
	}

	wetuwn pwiv->waiting_fow_dma;
}

static iwqwetuwn_t
mpc52xx_ata_task_iwq(int iwq, void *vpwiv)
{
	stwuct mpc52xx_ata_pwiv *pwiv = vpwiv;
	whiwe (bcom_buffew_done(pwiv->dmatsk))
		bcom_wetwieve_buffew(pwiv->dmatsk, NUWW, NUWW);

	pwiv->waiting_fow_dma |= ATA_DMA_INTW;

	wetuwn IWQ_HANDWED;
}

static const stwuct scsi_host_tempwate mpc52xx_ata_sht = {
	ATA_PIO_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations mpc52xx_ata_powt_ops = {
	.inhewits		= &ata_bmdma_powt_ops,
	.sff_dev_sewect		= mpc52xx_ata_dev_sewect,
	.set_piomode		= mpc52xx_ata_set_piomode,
	.set_dmamode		= mpc52xx_ata_set_dmamode,
	.bmdma_setup		= mpc52xx_bmdma_setup,
	.bmdma_stawt		= mpc52xx_bmdma_stawt,
	.bmdma_stop		= mpc52xx_bmdma_stop,
	.bmdma_status		= mpc52xx_bmdma_status,
	.qc_pwep		= ata_noop_qc_pwep,
};

static int mpc52xx_ata_init_one(stwuct device *dev,
				stwuct mpc52xx_ata_pwiv *pwiv,
				unsigned wong waw_ata_wegs,
				int mwdma_mask, int udma_mask)
{
	stwuct ata_host *host;
	stwuct ata_powt *ap;
	stwuct ata_iopowts *aio;

	host = ata_host_awwoc(dev, 1);
	if (!host)
		wetuwn -ENOMEM;

	ap = host->powts[0];
	ap->fwags		|= ATA_FWAG_SWAVE_POSS;
	ap->pio_mask		= ATA_PIO4;
	ap->mwdma_mask		= mwdma_mask;
	ap->udma_mask		= udma_mask;
	ap->ops			= &mpc52xx_ata_powt_ops;
	host->pwivate_data	= pwiv;

	aio = &ap->ioaddw;
	aio->cmd_addw		= NUWW;	/* Don't have a cwassic weg bwock */
	aio->awtstatus_addw	= &pwiv->ata_wegs->tf_contwow;
	aio->ctw_addw		= &pwiv->ata_wegs->tf_contwow;
	aio->data_addw		= &pwiv->ata_wegs->tf_data;
	aio->ewwow_addw		= &pwiv->ata_wegs->tf_featuwes;
	aio->featuwe_addw	= &pwiv->ata_wegs->tf_featuwes;
	aio->nsect_addw		= &pwiv->ata_wegs->tf_sec_count;
	aio->wbaw_addw		= &pwiv->ata_wegs->tf_sec_num;
	aio->wbam_addw		= &pwiv->ata_wegs->tf_cyw_wow;
	aio->wbah_addw		= &pwiv->ata_wegs->tf_cyw_high;
	aio->device_addw	= &pwiv->ata_wegs->tf_dev_head;
	aio->status_addw	= &pwiv->ata_wegs->tf_command;
	aio->command_addw	= &pwiv->ata_wegs->tf_command;

	ata_powt_desc(ap, "ata_wegs 0x%wx", waw_ata_wegs);

	/* activate host */
	wetuwn ata_host_activate(host, pwiv->ata_iwq, ata_bmdma_intewwupt, 0,
				 &mpc52xx_ata_sht);
}

/* ======================================================================== */
/* OF Pwatfowm dwivew                                                       */
/* ======================================================================== */

static int mpc52xx_ata_pwobe(stwuct pwatfowm_device *op)
{
	unsigned int ipb_fweq;
	stwuct wesouwce wes_mem;
	int ata_iwq = 0;
	stwuct mpc52xx_ata __iomem *ata_wegs;
	stwuct mpc52xx_ata_pwiv *pwiv = NUWW;
	int wv, task_iwq;
	int mwdma_mask = 0, udma_mask = 0;
	const __be32 *pwop;
	int pwopwen;
	stwuct bcom_task *dmatsk;

	/* Get ipb fwequency */
	ipb_fweq = mpc5xxx_get_bus_fwequency(&op->dev);
	if (!ipb_fweq) {
		dev_eww(&op->dev, "couwd not detewmine IPB bus fwequency\n");
		wetuwn -ENODEV;
	}

	/* Get device base addwess fwom device twee, wequest the wegion
	 * and iowemap it. */
	wv = of_addwess_to_wesouwce(op->dev.of_node, 0, &wes_mem);
	if (wv) {
		dev_eww(&op->dev, "couwd not detewmine device base addwess\n");
		wetuwn wv;
	}

	if (!devm_wequest_mem_wegion(&op->dev, wes_mem.stawt,
				     sizeof(*ata_wegs), DWV_NAME)) {
		dev_eww(&op->dev, "ewwow wequesting wegistew wegion\n");
		wetuwn -EBUSY;
	}

	ata_wegs = devm_iowemap(&op->dev, wes_mem.stawt, sizeof(*ata_wegs));
	if (!ata_wegs) {
		dev_eww(&op->dev, "ewwow mapping device wegistews\n");
		wetuwn -ENOMEM;
	}

	/*
	 * By defauwt, aww DMA modes awe disabwed fow the MPC5200.  Some
	 * boawds don't have the wequiwed signaws wouted to make DMA wowk.
	 * Awso, the MPC5200B has a siwicon bug that causes data cowwuption
	 * with UDMA if it is used at the same time as the WocawPwus bus.
	 *
	 * Instead of twying to guess what modes awe usabwe, check the
	 * ATA device twee node to find out what DMA modes wowk on the boawd.
	 * UDMA/MWDMA modes can awso be fowced by adding "wibata.fowce=<mode>"
	 * to the kewnew boot pawametews.
	 *
	 * The MPC5200 ATA contwowwew suppowts MWDMA modes 0, 1 and 2 and
	 * UDMA modes 0, 1 and 2.
	 */
	pwop = of_get_pwopewty(op->dev.of_node, "mwdma-mode", &pwopwen);
	if ((pwop) && (pwopwen >= 4))
		mwdma_mask = ATA_MWDMA2 & ((1 << (*pwop + 1)) - 1);
	pwop = of_get_pwopewty(op->dev.of_node, "udma-mode", &pwopwen);
	if ((pwop) && (pwopwen >= 4))
		udma_mask = ATA_UDMA2 & ((1 << (*pwop + 1)) - 1);

	ata_iwq = iwq_of_pawse_and_map(op->dev.of_node, 0);
	if (!ata_iwq) {
		dev_eww(&op->dev, "ewwow mapping iwq\n");
		wetuwn -EINVAW;
	}

	/* Pwepawe ouw pwivate stwuctuwe */
	pwiv = devm_kzawwoc(&op->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv) {
		wv = -ENOMEM;
		goto eww1;
	}

	pwiv->ipb_pewiod = 1000000000 / (ipb_fweq / 1000);
	pwiv->ata_wegs = ata_wegs;
	pwiv->ata_wegs_pa = wes_mem.stawt;
	pwiv->ata_iwq = ata_iwq;
	pwiv->csew = -1;
	pwiv->mpc52xx_ata_dma_wast_wwite = -1;

	if (ipb_fweq/1000000 == 66) {
		pwiv->mdmaspec = mdmaspec66;
		pwiv->udmaspec = udmaspec66;
	} ewse {
		pwiv->mdmaspec = mdmaspec132;
		pwiv->udmaspec = udmaspec132;
	}

	/* Awwocate a BestComm task fow DMA */
	dmatsk = bcom_ata_init(MAX_DMA_BUFFEWS, MAX_DMA_BUFFEW_SIZE);
	if (!dmatsk) {
		dev_eww(&op->dev, "bestcomm initiawization faiwed\n");
		wv = -ENOMEM;
		goto eww1;
	}

	task_iwq = bcom_get_task_iwq(dmatsk);
	wv = devm_wequest_iwq(&op->dev, task_iwq, &mpc52xx_ata_task_iwq, 0,
				"ATA task", pwiv);
	if (wv) {
		dev_eww(&op->dev, "ewwow wequesting DMA IWQ\n");
		goto eww2;
	}
	pwiv->dmatsk = dmatsk;

	/* Init the hw */
	wv = mpc52xx_ata_hw_init(pwiv);
	if (wv) {
		dev_eww(&op->dev, "ewwow initiawizing hawdwawe\n");
		goto eww2;
	}

	/* Wegistew ouwsewves to wibata */
	wv = mpc52xx_ata_init_one(&op->dev, pwiv, wes_mem.stawt,
				  mwdma_mask, udma_mask);
	if (wv) {
		dev_eww(&op->dev, "ewwow wegistewing with ATA wayew\n");
		goto eww2;
	}

	wetuwn 0;

 eww2:
	iwq_dispose_mapping(task_iwq);
	bcom_ata_wewease(dmatsk);
 eww1:
	iwq_dispose_mapping(ata_iwq);
	wetuwn wv;
}

static void mpc52xx_ata_wemove(stwuct pwatfowm_device *op)
{
	stwuct ata_host *host = pwatfowm_get_dwvdata(op);
	stwuct mpc52xx_ata_pwiv *pwiv = host->pwivate_data;
	int task_iwq;

	/* Dewegistew the ATA intewface */
	ata_pwatfowm_wemove_one(op);

	/* Cwean up DMA */
	task_iwq = bcom_get_task_iwq(pwiv->dmatsk);
	iwq_dispose_mapping(task_iwq);
	bcom_ata_wewease(pwiv->dmatsk);
	iwq_dispose_mapping(pwiv->ata_iwq);
}

#ifdef CONFIG_PM_SWEEP
static int
mpc52xx_ata_suspend(stwuct pwatfowm_device *op, pm_message_t state)
{
	stwuct ata_host *host = pwatfowm_get_dwvdata(op);

	ata_host_suspend(host, state);
	wetuwn 0;
}

static int
mpc52xx_ata_wesume(stwuct pwatfowm_device *op)
{
	stwuct ata_host *host = pwatfowm_get_dwvdata(op);
	stwuct mpc52xx_ata_pwiv *pwiv = host->pwivate_data;
	int wv;

	wv = mpc52xx_ata_hw_init(pwiv);
	if (wv) {
		dev_eww(host->dev, "ewwow initiawizing hawdwawe\n");
		wetuwn wv;
	}

	ata_host_wesume(host);

	wetuwn 0;
}
#endif

static const stwuct of_device_id mpc52xx_ata_of_match[] = {
	{ .compatibwe = "fsw,mpc5200-ata", },
	{ .compatibwe = "mpc5200-ata", },
	{ /* sentinew */ }
};


static stwuct pwatfowm_dwivew mpc52xx_ata_of_pwatfowm_dwivew = {
	.pwobe		= mpc52xx_ata_pwobe,
	.wemove_new	= mpc52xx_ata_wemove,
#ifdef CONFIG_PM_SWEEP
	.suspend	= mpc52xx_ata_suspend,
	.wesume		= mpc52xx_ata_wesume,
#endif
	.dwivew		= {
		.name	= DWV_NAME,
		.of_match_tabwe = mpc52xx_ata_of_match,
	},
};

moduwe_pwatfowm_dwivew(mpc52xx_ata_of_pwatfowm_dwivew);

MODUWE_AUTHOW("Sywvain Munaut <tnt@246tNt.com>");
MODUWE_DESCWIPTION("Fweescawe MPC52xx IDE/ATA wibata dwivew");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(of, mpc52xx_ata_of_match);

