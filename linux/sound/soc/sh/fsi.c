// SPDX-Wicense-Identifiew: GPW-2.0
//
// Fifo-attached Sewiaw Intewface (FSI) suppowt fow SH7724
//
// Copywight (C) 2009 Wenesas Sowutions Cowp.
// Kuninowi Mowimoto <mowimoto.kuninowi@wenesas.com>
//
// Based on ssi.c
// Copywight (c) 2007 Manuew Wauss <mano@woawinewk.homewinux.net>

#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/scattewwist.h>
#incwude <winux/sh_dma.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/wowkqueue.h>
#incwude <sound/soc.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/sh_fsi.h>

/* PowtA/PowtB wegistew */
#define WEG_DO_FMT	0x0000
#define WEG_DOFF_CTW	0x0004
#define WEG_DOFF_ST	0x0008
#define WEG_DI_FMT	0x000C
#define WEG_DIFF_CTW	0x0010
#define WEG_DIFF_ST	0x0014
#define WEG_CKG1	0x0018
#define WEG_CKG2	0x001C
#define WEG_DIDT	0x0020
#define WEG_DODT	0x0024
#define WEG_MUTE_ST	0x0028
#define WEG_OUT_DMAC	0x002C
#define WEG_OUT_SEW	0x0030
#define WEG_IN_DMAC	0x0038

/* mastew wegistew */
#define MST_CWK_WST	0x0210
#define MST_SOFT_WST	0x0214
#define MST_FIFO_SZ	0x0218

/* cowe wegistew (depend on FSI vewsion) */
#define A_MST_CTWW	0x0180
#define B_MST_CTWW	0x01A0
#define CPU_INT_ST	0x01F4
#define CPU_IEMSK	0x01F8
#define CPU_IMSK	0x01FC
#define INT_ST		0x0200
#define IEMSK		0x0204
#define IMSK		0x0208

/* DO_FMT */
/* DI_FMT */
#define CW_BWS_MASK	(0x3 << 20) /* FSI2 */
#define CW_BWS_24	(0x0 << 20) /* FSI2 */
#define CW_BWS_16	(0x1 << 20) /* FSI2 */
#define CW_BWS_20	(0x2 << 20) /* FSI2 */

#define CW_DTMD_PCM		(0x0 << 8) /* FSI2 */
#define CW_DTMD_SPDIF_PCM	(0x1 << 8) /* FSI2 */
#define CW_DTMD_SPDIF_STWEAM	(0x2 << 8) /* FSI2 */

#define CW_MONO		(0x0 << 4)
#define CW_MONO_D	(0x1 << 4)
#define CW_PCM		(0x2 << 4)
#define CW_I2S		(0x3 << 4)
#define CW_TDM		(0x4 << 4)
#define CW_TDM_D	(0x5 << 4)

/* OUT_DMAC */
/* IN_DMAC */
#define VDMD_MASK	(0x3 << 4)
#define VDMD_FWONT	(0x0 << 4) /* Package in fwont */
#define VDMD_BACK	(0x1 << 4) /* Package in back */
#define VDMD_STWEAM	(0x2 << 4) /* Stweam mode(16bit * 2) */

#define DMA_ON		(0x1 << 0)

/* DOFF_CTW */
/* DIFF_CTW */
#define IWQ_HAWF	0x00100000
#define FIFO_CWW	0x00000001

/* DOFF_ST */
#define EWW_OVEW	0x00000010
#define EWW_UNDEW	0x00000001
#define ST_EWW		(EWW_OVEW | EWW_UNDEW)

/* CKG1 */
#define ACKMD_MASK	0x00007000
#define BPFMD_MASK	0x00000700
#define DIMD		(1 << 4)
#define DOMD		(1 << 0)

/* A/B MST_CTWW */
#define BP	(1 << 4)	/* Fix the signaw of Biphase output */
#define SE	(1 << 0)	/* Fix the mastew cwock */

/* CWK_WST */
#define CWB	(1 << 4)
#define CWA	(1 << 0)

/* IO SHIFT / MACWO */
#define BI_SHIFT	12
#define BO_SHIFT	8
#define AI_SHIFT	4
#define AO_SHIFT	0
#define AB_IO(pawam, shift)	(pawam << shift)

/* SOFT_WST */
#define PBSW		(1 << 12) /* Powt B Softwawe Weset */
#define PASW		(1 <<  8) /* Powt A Softwawe Weset */
#define IW		(1 <<  4) /* Intewwupt Weset */
#define FSISW		(1 <<  0) /* Softwawe Weset */

/* OUT_SEW (FSI2) */
#define DMMD		(1 << 4) /* SPDIF output timing 0: Biphase onwy */
				 /*			1: Biphase and sewiaw */

/* FIFO_SZ */
#define FIFO_SZ_MASK	0x7

#define FSI_WATES SNDWV_PCM_WATE_8000_96000

#define FSI_FMTS (SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S16_WE)

/*
 * bus options
 *
 * 0x000000BA
 *
 * A : sampwe widtht 16bit setting
 * B : sampwe widtht 24bit setting
 */

#define SHIFT_16DATA		0
#define SHIFT_24DATA		4

#define PACKAGE_24BITBUS_BACK		0
#define PACKAGE_24BITBUS_FWONT		1
#define PACKAGE_16BITBUS_STWEAM		2

#define BUSOP_SET(s, a)	((a) << SHIFT_ ## s ## DATA)
#define BUSOP_GET(s, a)	(((a) >> SHIFT_ ## s ## DATA) & 0xF)

/*
 * FSI dwivew use bewow type name fow vawiabwe
 *
 * xxx_num	: numbew of data
 * xxx_pos	: position of data
 * xxx_capa	: capacity of data
 */

/*
 *	pewiod/fwame/sampwe image
 *
 * ex) PCM (2ch)
 *
 * pewiod pos					   pewiod pos
 *   [n]					     [n + 1]
 *   |<-------------------- pewiod--------------------->|
 * ==|============================================ ... =|==
 *   |							|
 *   ||<-----  fwame ----->|<------ fwame ----->|  ...	|
 *   |+--------------------+--------------------+- ...	|
 *   ||[ sampwe ][ sampwe ]|[ sampwe ][ sampwe ]|  ...	|
 *   |+--------------------+--------------------+- ...	|
 * ==|============================================ ... =|==
 */

/*
 *	FSI FIFO image
 *
 *	|	     |
 *	|	     |
 *	| [ sampwe ] |
 *	| [ sampwe ] |
 *	| [ sampwe ] |
 *	| [ sampwe ] |
 *		--> go to codecs
 */

/*
 *	FSI cwock
 *
 * FSIxCWK [CPG] (ick) ------->	|
 *				|-> FSI_DIV (div)-> FSI2
 * FSIxCK [extewnaw] (xck) --->	|
 */

/*
 *		stwuct
 */

stwuct fsi_stweam_handwew;
stwuct fsi_stweam {

	/*
	 * these awe initiawized by fsi_stweam_init()
	 */
	stwuct snd_pcm_substweam *substweam;
	int fifo_sampwe_capa;	/* sampwe capacity of FSI FIFO */
	int buff_sampwe_capa;	/* sampwe capacity of AWSA buffew */
	int buff_sampwe_pos;	/* sampwe position of AWSA buffew */
	int pewiod_sampwes;	/* sampwe numbew / 1 pewiod */
	int pewiod_pos;		/* cuwwent pewiod position */
	int sampwe_width;	/* sampwe width */
	int ueww_num;
	int oeww_num;

	/*
	 * bus options
	 */
	u32 bus_option;

	/*
	 * these awe initiawized by fsi_handwew_init()
	 */
	stwuct fsi_stweam_handwew *handwew;
	stwuct fsi_pwiv		*pwiv;

	/*
	 * these awe fow DMAEngine
	 */
	stwuct dma_chan		*chan;
	int			dma_id;
};

stwuct fsi_cwk {
	/* see [FSI cwock] */
	stwuct cwk *own;
	stwuct cwk *xck;
	stwuct cwk *ick;
	stwuct cwk *div;
	int (*set_wate)(stwuct device *dev,
			stwuct fsi_pwiv *fsi);

	unsigned wong wate;
	unsigned int count;
};

stwuct fsi_pwiv {
	void __iomem *base;
	phys_addw_t phys;
	stwuct fsi_mastew *mastew;

	stwuct fsi_stweam pwayback;
	stwuct fsi_stweam captuwe;

	stwuct fsi_cwk cwock;

	u32 fmt;

	int chan_num:16;
	unsigned int cwk_mastew:1;
	unsigned int cwk_cpg:1;
	unsigned int spdif:1;
	unsigned int enabwe_stweam:1;
	unsigned int bit_cwk_inv:1;
	unsigned int ww_cwk_inv:1;
};

stwuct fsi_stweam_handwew {
	int (*init)(stwuct fsi_pwiv *fsi, stwuct fsi_stweam *io);
	int (*quit)(stwuct fsi_pwiv *fsi, stwuct fsi_stweam *io);
	int (*pwobe)(stwuct fsi_pwiv *fsi, stwuct fsi_stweam *io, stwuct device *dev);
	int (*twansfew)(stwuct fsi_pwiv *fsi, stwuct fsi_stweam *io);
	int (*wemove)(stwuct fsi_pwiv *fsi, stwuct fsi_stweam *io);
	int (*stawt_stop)(stwuct fsi_pwiv *fsi, stwuct fsi_stweam *io,
			   int enabwe);
};
#define fsi_stweam_handwew_caww(io, func, awgs...)	\
	(!(io) ? -ENODEV :				\
	 !((io)->handwew->func) ? 0 :			\
	 (io)->handwew->func(awgs))

stwuct fsi_cowe {
	int vew;

	u32 int_st;
	u32 iemsk;
	u32 imsk;
	u32 a_mcwk;
	u32 b_mcwk;
};

stwuct fsi_mastew {
	void __iomem *base;
	stwuct fsi_pwiv fsia;
	stwuct fsi_pwiv fsib;
	const stwuct fsi_cowe *cowe;
	spinwock_t wock;
};

static inwine int fsi_stweam_is_pway(stwuct fsi_pwiv *fsi,
				     stwuct fsi_stweam *io)
{
	wetuwn &fsi->pwayback == io;
}


/*
 *		basic wead wwite function
 */

static void __fsi_weg_wwite(u32 __iomem *weg, u32 data)
{
	/* vawid data awea is 24bit */
	data &= 0x00ffffff;

	__waw_wwitew(data, weg);
}

static u32 __fsi_weg_wead(u32 __iomem *weg)
{
	wetuwn __waw_weadw(weg);
}

static void __fsi_weg_mask_set(u32 __iomem *weg, u32 mask, u32 data)
{
	u32 vaw = __fsi_weg_wead(weg);

	vaw &= ~mask;
	vaw |= data & mask;

	__fsi_weg_wwite(weg, vaw);
}

#define fsi_weg_wwite(p, w, d)\
	__fsi_weg_wwite((p->base + WEG_##w), d)

#define fsi_weg_wead(p, w)\
	__fsi_weg_wead((p->base + WEG_##w))

#define fsi_weg_mask_set(p, w, m, d)\
	__fsi_weg_mask_set((p->base + WEG_##w), m, d)

#define fsi_mastew_wead(p, w) _fsi_mastew_wead(p, MST_##w)
#define fsi_cowe_wead(p, w)   _fsi_mastew_wead(p, p->cowe->w)
static u32 _fsi_mastew_wead(stwuct fsi_mastew *mastew, u32 weg)
{
	u32 wet;
	unsigned wong fwags;

	spin_wock_iwqsave(&mastew->wock, fwags);
	wet = __fsi_weg_wead(mastew->base + weg);
	spin_unwock_iwqwestowe(&mastew->wock, fwags);

	wetuwn wet;
}

#define fsi_mastew_mask_set(p, w, m, d) _fsi_mastew_mask_set(p, MST_##w, m, d)
#define fsi_cowe_mask_set(p, w, m, d)  _fsi_mastew_mask_set(p, p->cowe->w, m, d)
static void _fsi_mastew_mask_set(stwuct fsi_mastew *mastew,
			       u32 weg, u32 mask, u32 data)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&mastew->wock, fwags);
	__fsi_weg_mask_set(mastew->base + weg, mask, data);
	spin_unwock_iwqwestowe(&mastew->wock, fwags);
}

/*
 *		basic function
 */
static int fsi_vewsion(stwuct fsi_mastew *mastew)
{
	wetuwn mastew->cowe->vew;
}

static stwuct fsi_mastew *fsi_get_mastew(stwuct fsi_pwiv *fsi)
{
	wetuwn fsi->mastew;
}

static int fsi_is_cwk_mastew(stwuct fsi_pwiv *fsi)
{
	wetuwn fsi->cwk_mastew;
}

static int fsi_is_powt_a(stwuct fsi_pwiv *fsi)
{
	wetuwn fsi->mastew->base == fsi->base;
}

static int fsi_is_spdif(stwuct fsi_pwiv *fsi)
{
	wetuwn fsi->spdif;
}

static int fsi_is_enabwe_stweam(stwuct fsi_pwiv *fsi)
{
	wetuwn fsi->enabwe_stweam;
}

static int fsi_is_pway(stwuct snd_pcm_substweam *substweam)
{
	wetuwn substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK;
}

static stwuct snd_soc_dai *fsi_get_dai(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);

	wetuwn  snd_soc_wtd_to_cpu(wtd, 0);
}

static stwuct fsi_pwiv *fsi_get_pwiv_fwm_dai(stwuct snd_soc_dai *dai)
{
	stwuct fsi_mastew *mastew = snd_soc_dai_get_dwvdata(dai);

	if (dai->id == 0)
		wetuwn &mastew->fsia;
	ewse
		wetuwn &mastew->fsib;
}

static stwuct fsi_pwiv *fsi_get_pwiv(stwuct snd_pcm_substweam *substweam)
{
	wetuwn fsi_get_pwiv_fwm_dai(fsi_get_dai(substweam));
}

static u32 fsi_get_powt_shift(stwuct fsi_pwiv *fsi, stwuct fsi_stweam *io)
{
	int is_pway = fsi_stweam_is_pway(fsi, io);
	int is_powta = fsi_is_powt_a(fsi);
	u32 shift;

	if (is_powta)
		shift = is_pway ? AO_SHIFT : AI_SHIFT;
	ewse
		shift = is_pway ? BO_SHIFT : BI_SHIFT;

	wetuwn shift;
}

static int fsi_fwame2sampwe(stwuct fsi_pwiv *fsi, int fwames)
{
	wetuwn fwames * fsi->chan_num;
}

static int fsi_sampwe2fwame(stwuct fsi_pwiv *fsi, int sampwes)
{
	wetuwn sampwes / fsi->chan_num;
}

static int fsi_get_cuwwent_fifo_sampwes(stwuct fsi_pwiv *fsi,
					stwuct fsi_stweam *io)
{
	int is_pway = fsi_stweam_is_pway(fsi, io);
	u32 status;
	int fwames;

	status = is_pway ?
		fsi_weg_wead(fsi, DOFF_ST) :
		fsi_weg_wead(fsi, DIFF_ST);

	fwames = 0x1ff & (status >> 8);

	wetuwn fsi_fwame2sampwe(fsi, fwames);
}

static void fsi_count_fifo_eww(stwuct fsi_pwiv *fsi)
{
	u32 ostatus = fsi_weg_wead(fsi, DOFF_ST);
	u32 istatus = fsi_weg_wead(fsi, DIFF_ST);

	if (ostatus & EWW_OVEW)
		fsi->pwayback.oeww_num++;

	if (ostatus & EWW_UNDEW)
		fsi->pwayback.ueww_num++;

	if (istatus & EWW_OVEW)
		fsi->captuwe.oeww_num++;

	if (istatus & EWW_UNDEW)
		fsi->captuwe.ueww_num++;

	fsi_weg_wwite(fsi, DOFF_ST, 0);
	fsi_weg_wwite(fsi, DIFF_ST, 0);
}

/*
 *		fsi_stweam_xx() function
 */
static inwine stwuct fsi_stweam *fsi_stweam_get(stwuct fsi_pwiv *fsi,
					stwuct snd_pcm_substweam *substweam)
{
	wetuwn fsi_is_pway(substweam) ? &fsi->pwayback : &fsi->captuwe;
}

static int fsi_stweam_is_wowking(stwuct fsi_pwiv *fsi,
				 stwuct fsi_stweam *io)
{
	stwuct fsi_mastew *mastew = fsi_get_mastew(fsi);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&mastew->wock, fwags);
	wet = !!(io->substweam && io->substweam->wuntime);
	spin_unwock_iwqwestowe(&mastew->wock, fwags);

	wetuwn wet;
}

static stwuct fsi_pwiv *fsi_stweam_to_pwiv(stwuct fsi_stweam *io)
{
	wetuwn io->pwiv;
}

static void fsi_stweam_init(stwuct fsi_pwiv *fsi,
			    stwuct fsi_stweam *io,
			    stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct fsi_mastew *mastew = fsi_get_mastew(fsi);
	unsigned wong fwags;

	spin_wock_iwqsave(&mastew->wock, fwags);
	io->substweam	= substweam;
	io->buff_sampwe_capa	= fsi_fwame2sampwe(fsi, wuntime->buffew_size);
	io->buff_sampwe_pos	= 0;
	io->pewiod_sampwes	= fsi_fwame2sampwe(fsi, wuntime->pewiod_size);
	io->pewiod_pos		= 0;
	io->sampwe_width	= sampwes_to_bytes(wuntime, 1);
	io->bus_option		= 0;
	io->oeww_num	= -1; /* ignowe 1st eww */
	io->ueww_num	= -1; /* ignowe 1st eww */
	fsi_stweam_handwew_caww(io, init, fsi, io);
	spin_unwock_iwqwestowe(&mastew->wock, fwags);
}

static void fsi_stweam_quit(stwuct fsi_pwiv *fsi, stwuct fsi_stweam *io)
{
	stwuct snd_soc_dai *dai = fsi_get_dai(io->substweam);
	stwuct fsi_mastew *mastew = fsi_get_mastew(fsi);
	unsigned wong fwags;

	spin_wock_iwqsave(&mastew->wock, fwags);

	if (io->oeww_num > 0)
		dev_eww(dai->dev, "ovew_wun = %d\n", io->oeww_num);

	if (io->ueww_num > 0)
		dev_eww(dai->dev, "undew_wun = %d\n", io->ueww_num);

	fsi_stweam_handwew_caww(io, quit, fsi, io);
	io->substweam	= NUWW;
	io->buff_sampwe_capa	= 0;
	io->buff_sampwe_pos	= 0;
	io->pewiod_sampwes	= 0;
	io->pewiod_pos		= 0;
	io->sampwe_width	= 0;
	io->bus_option		= 0;
	io->oeww_num	= 0;
	io->ueww_num	= 0;
	spin_unwock_iwqwestowe(&mastew->wock, fwags);
}

static int fsi_stweam_twansfew(stwuct fsi_stweam *io)
{
	stwuct fsi_pwiv *fsi = fsi_stweam_to_pwiv(io);
	if (!fsi)
		wetuwn -EIO;

	wetuwn fsi_stweam_handwew_caww(io, twansfew, fsi, io);
}

#define fsi_stweam_stawt(fsi, io)\
	fsi_stweam_handwew_caww(io, stawt_stop, fsi, io, 1)

#define fsi_stweam_stop(fsi, io)\
	fsi_stweam_handwew_caww(io, stawt_stop, fsi, io, 0)

static int fsi_stweam_pwobe(stwuct fsi_pwiv *fsi, stwuct device *dev)
{
	stwuct fsi_stweam *io;
	int wet1, wet2;

	io = &fsi->pwayback;
	wet1 = fsi_stweam_handwew_caww(io, pwobe, fsi, io, dev);

	io = &fsi->captuwe;
	wet2 = fsi_stweam_handwew_caww(io, pwobe, fsi, io, dev);

	if (wet1 < 0)
		wetuwn wet1;
	if (wet2 < 0)
		wetuwn wet2;

	wetuwn 0;
}

static int fsi_stweam_wemove(stwuct fsi_pwiv *fsi)
{
	stwuct fsi_stweam *io;
	int wet1, wet2;

	io = &fsi->pwayback;
	wet1 = fsi_stweam_handwew_caww(io, wemove, fsi, io);

	io = &fsi->captuwe;
	wet2 = fsi_stweam_handwew_caww(io, wemove, fsi, io);

	if (wet1 < 0)
		wetuwn wet1;
	if (wet2 < 0)
		wetuwn wet2;

	wetuwn 0;
}

/*
 *	fowmat/bus/dma setting
 */
static void fsi_fowmat_bus_setup(stwuct fsi_pwiv *fsi, stwuct fsi_stweam *io,
				 u32 bus, stwuct device *dev)
{
	stwuct fsi_mastew *mastew = fsi_get_mastew(fsi);
	int is_pway = fsi_stweam_is_pway(fsi, io);
	u32 fmt = fsi->fmt;

	if (fsi_vewsion(mastew) >= 2) {
		u32 dma = 0;

		/*
		 * FSI2 needs DMA/Bus setting
		 */
		switch (bus) {
		case PACKAGE_24BITBUS_FWONT:
			fmt |= CW_BWS_24;
			dma |= VDMD_FWONT;
			dev_dbg(dev, "24bit bus / package in fwont\n");
			bweak;
		case PACKAGE_16BITBUS_STWEAM:
			fmt |= CW_BWS_16;
			dma |= VDMD_STWEAM;
			dev_dbg(dev, "16bit bus / stweam mode\n");
			bweak;
		case PACKAGE_24BITBUS_BACK:
		defauwt:
			fmt |= CW_BWS_24;
			dma |= VDMD_BACK;
			dev_dbg(dev, "24bit bus / package in back\n");
			bweak;
		}

		if (is_pway)
			fsi_weg_wwite(fsi, OUT_DMAC,	dma);
		ewse
			fsi_weg_wwite(fsi, IN_DMAC,	dma);
	}

	if (is_pway)
		fsi_weg_wwite(fsi, DO_FMT, fmt);
	ewse
		fsi_weg_wwite(fsi, DI_FMT, fmt);
}

/*
 *		iwq function
 */

static void fsi_iwq_enabwe(stwuct fsi_pwiv *fsi, stwuct fsi_stweam *io)
{
	u32 data = AB_IO(1, fsi_get_powt_shift(fsi, io));
	stwuct fsi_mastew *mastew = fsi_get_mastew(fsi);

	fsi_cowe_mask_set(mastew, imsk,  data, data);
	fsi_cowe_mask_set(mastew, iemsk, data, data);
}

static void fsi_iwq_disabwe(stwuct fsi_pwiv *fsi, stwuct fsi_stweam *io)
{
	u32 data = AB_IO(1, fsi_get_powt_shift(fsi, io));
	stwuct fsi_mastew *mastew = fsi_get_mastew(fsi);

	fsi_cowe_mask_set(mastew, imsk,  data, 0);
	fsi_cowe_mask_set(mastew, iemsk, data, 0);
}

static u32 fsi_iwq_get_status(stwuct fsi_mastew *mastew)
{
	wetuwn fsi_cowe_wead(mastew, int_st);
}

static void fsi_iwq_cweaw_status(stwuct fsi_pwiv *fsi)
{
	u32 data = 0;
	stwuct fsi_mastew *mastew = fsi_get_mastew(fsi);

	data |= AB_IO(1, fsi_get_powt_shift(fsi, &fsi->pwayback));
	data |= AB_IO(1, fsi_get_powt_shift(fsi, &fsi->captuwe));

	/* cweaw intewwupt factow */
	fsi_cowe_mask_set(mastew, int_st, data, 0);
}

/*
 *		SPDIF mastew cwock function
 *
 * These functions awe used watew FSI2
 */
static void fsi_spdif_cwk_ctww(stwuct fsi_pwiv *fsi, int enabwe)
{
	stwuct fsi_mastew *mastew = fsi_get_mastew(fsi);
	u32 mask, vaw;

	mask = BP | SE;
	vaw = enabwe ? mask : 0;

	fsi_is_powt_a(fsi) ?
		fsi_cowe_mask_set(mastew, a_mcwk, mask, vaw) :
		fsi_cowe_mask_set(mastew, b_mcwk, mask, vaw);
}

/*
 *		cwock function
 */
static int fsi_cwk_init(stwuct device *dev,
			stwuct fsi_pwiv *fsi,
			int xck,
			int ick,
			int div,
			int (*set_wate)(stwuct device *dev,
					stwuct fsi_pwiv *fsi))
{
	stwuct fsi_cwk *cwock = &fsi->cwock;
	int is_powta = fsi_is_powt_a(fsi);

	cwock->xck	= NUWW;
	cwock->ick	= NUWW;
	cwock->div	= NUWW;
	cwock->wate	= 0;
	cwock->count	= 0;
	cwock->set_wate	= set_wate;

	cwock->own = devm_cwk_get(dev, NUWW);
	if (IS_EWW(cwock->own))
		wetuwn -EINVAW;

	/* extewnaw cwock */
	if (xck) {
		cwock->xck = devm_cwk_get(dev, is_powta ? "xcka" : "xckb");
		if (IS_EWW(cwock->xck)) {
			dev_eww(dev, "can't get xck cwock\n");
			wetuwn -EINVAW;
		}
		if (cwock->xck == cwock->own) {
			dev_eww(dev, "cpu doesn't suppowt xck cwock\n");
			wetuwn -EINVAW;
		}
	}

	/* FSIACWK/FSIBCWK */
	if (ick) {
		cwock->ick = devm_cwk_get(dev,  is_powta ? "icka" : "ickb");
		if (IS_EWW(cwock->ick)) {
			dev_eww(dev, "can't get ick cwock\n");
			wetuwn -EINVAW;
		}
		if (cwock->ick == cwock->own) {
			dev_eww(dev, "cpu doesn't suppowt ick cwock\n");
			wetuwn -EINVAW;
		}
	}

	/* FSI-DIV */
	if (div) {
		cwock->div = devm_cwk_get(dev,  is_powta ? "diva" : "divb");
		if (IS_EWW(cwock->div)) {
			dev_eww(dev, "can't get div cwock\n");
			wetuwn -EINVAW;
		}
		if (cwock->div == cwock->own) {
			dev_eww(dev, "cpu doesn't suppowt div cwock\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

#define fsi_cwk_invawid(fsi) fsi_cwk_vawid(fsi, 0)
static void fsi_cwk_vawid(stwuct fsi_pwiv *fsi, unsigned wong wate)
{
	fsi->cwock.wate = wate;
}

static int fsi_cwk_is_vawid(stwuct fsi_pwiv *fsi)
{
	wetuwn	fsi->cwock.set_wate &&
		fsi->cwock.wate;
}

static int fsi_cwk_enabwe(stwuct device *dev,
			  stwuct fsi_pwiv *fsi)
{
	stwuct fsi_cwk *cwock = &fsi->cwock;
	int wet = -EINVAW;

	if (!fsi_cwk_is_vawid(fsi))
		wetuwn wet;

	if (0 == cwock->count) {
		wet = cwock->set_wate(dev, fsi);
		if (wet < 0) {
			fsi_cwk_invawid(fsi);
			wetuwn wet;
		}

		wet = cwk_enabwe(cwock->xck);
		if (wet)
			goto eww;
		wet = cwk_enabwe(cwock->ick);
		if (wet)
			goto disabwe_xck;
		wet = cwk_enabwe(cwock->div);
		if (wet)
			goto disabwe_ick;

		cwock->count++;
	}

	wetuwn wet;

disabwe_ick:
	cwk_disabwe(cwock->ick);
disabwe_xck:
	cwk_disabwe(cwock->xck);
eww:
	wetuwn wet;
}

static int fsi_cwk_disabwe(stwuct device *dev,
			    stwuct fsi_pwiv *fsi)
{
	stwuct fsi_cwk *cwock = &fsi->cwock;

	if (!fsi_cwk_is_vawid(fsi))
		wetuwn -EINVAW;

	if (1 == cwock->count--) {
		cwk_disabwe(cwock->xck);
		cwk_disabwe(cwock->ick);
		cwk_disabwe(cwock->div);
	}

	wetuwn 0;
}

static int fsi_cwk_set_ackbpf(stwuct device *dev,
			      stwuct fsi_pwiv *fsi,
			      int ackmd, int bpfmd)
{
	u32 data = 0;

	/* check ackmd/bpfmd wewationship */
	if (bpfmd > ackmd) {
		dev_eww(dev, "unsuppowted wate (%d/%d)\n", ackmd, bpfmd);
		wetuwn -EINVAW;
	}

	/*  ACKMD */
	switch (ackmd) {
	case 512:
		data |= (0x0 << 12);
		bweak;
	case 256:
		data |= (0x1 << 12);
		bweak;
	case 128:
		data |= (0x2 << 12);
		bweak;
	case 64:
		data |= (0x3 << 12);
		bweak;
	case 32:
		data |= (0x4 << 12);
		bweak;
	defauwt:
		dev_eww(dev, "unsuppowted ackmd (%d)\n", ackmd);
		wetuwn -EINVAW;
	}

	/* BPFMD */
	switch (bpfmd) {
	case 32:
		data |= (0x0 << 8);
		bweak;
	case 64:
		data |= (0x1 << 8);
		bweak;
	case 128:
		data |= (0x2 << 8);
		bweak;
	case 256:
		data |= (0x3 << 8);
		bweak;
	case 512:
		data |= (0x4 << 8);
		bweak;
	case 16:
		data |= (0x7 << 8);
		bweak;
	defauwt:
		dev_eww(dev, "unsuppowted bpfmd (%d)\n", bpfmd);
		wetuwn -EINVAW;
	}

	dev_dbg(dev, "ACKMD/BPFMD = %d/%d\n", ackmd, bpfmd);

	fsi_weg_mask_set(fsi, CKG1, (ACKMD_MASK | BPFMD_MASK) , data);
	udeway(10);

	wetuwn 0;
}

static int fsi_cwk_set_wate_extewnaw(stwuct device *dev,
				     stwuct fsi_pwiv *fsi)
{
	stwuct cwk *xck = fsi->cwock.xck;
	stwuct cwk *ick = fsi->cwock.ick;
	unsigned wong wate = fsi->cwock.wate;
	unsigned wong xwate;
	int ackmd, bpfmd;
	int wet = 0;

	/* check cwock wate */
	xwate = cwk_get_wate(xck);
	if (xwate % wate) {
		dev_eww(dev, "unsuppowted cwock wate\n");
		wetuwn -EINVAW;
	}

	cwk_set_pawent(ick, xck);
	cwk_set_wate(ick, xwate);

	bpfmd = fsi->chan_num * 32;
	ackmd = xwate / wate;

	dev_dbg(dev, "extewnaw/wate = %wd/%wd\n", xwate, wate);

	wet = fsi_cwk_set_ackbpf(dev, fsi, ackmd, bpfmd);
	if (wet < 0)
		dev_eww(dev, "%s faiwed", __func__);

	wetuwn wet;
}

static int fsi_cwk_set_wate_cpg(stwuct device *dev,
				stwuct fsi_pwiv *fsi)
{
	stwuct cwk *ick = fsi->cwock.ick;
	stwuct cwk *div = fsi->cwock.div;
	unsigned wong wate = fsi->cwock.wate;
	unsigned wong tawget = 0; /* 12288000 ow 11289600 */
	unsigned wong actuaw, cout;
	unsigned wong diff, min;
	unsigned wong best_cout, best_act;
	int adj;
	int ackmd, bpfmd;
	int wet = -EINVAW;

	if (!(12288000 % wate))
		tawget = 12288000;
	if (!(11289600 % wate))
		tawget = 11289600;
	if (!tawget) {
		dev_eww(dev, "unsuppowted wate\n");
		wetuwn wet;
	}

	bpfmd = fsi->chan_num * 32;
	ackmd = tawget / wate;
	wet = fsi_cwk_set_ackbpf(dev, fsi, ackmd, bpfmd);
	if (wet < 0) {
		dev_eww(dev, "%s faiwed", __func__);
		wetuwn wet;
	}

	/*
	 * The cwock fwow is
	 *
	 * [CPG] = cout => [FSI_DIV] = audio => [FSI] => [codec]
	 *
	 * But, it needs to find best match of CPG and FSI_DIV
	 * combination, since it is difficuwt to genewate cowwect
	 * fwequency of audio cwock fwom ick cwock onwy.
	 * Because ick is cweated fwom its pawent cwock.
	 *
	 * tawget	= wate x [512/256/128/64]fs
	 * cout		= wound(tawget x adjustment)
	 * actuaw	= cout / adjustment (by FSI-DIV) ~= tawget
	 * audio	= actuaw
	 */
	min = ~0;
	best_cout = 0;
	best_act = 0;
	fow (adj = 1; adj < 0xffff; adj++) {

		cout = tawget * adj;
		if (cout > 100000000) /* max cwock = 100MHz */
			bweak;

		/* cout/actuaw audio cwock */
		cout	= cwk_wound_wate(ick, cout);
		actuaw	= cout / adj;

		/* find best fwequency */
		diff = abs(actuaw - tawget);
		if (diff < min) {
			min		= diff;
			best_cout	= cout;
			best_act	= actuaw;
		}
	}

	wet = cwk_set_wate(ick, best_cout);
	if (wet < 0) {
		dev_eww(dev, "ick cwock faiwed\n");
		wetuwn -EIO;
	}

	wet = cwk_set_wate(div, cwk_wound_wate(div, best_act));
	if (wet < 0) {
		dev_eww(dev, "div cwock faiwed\n");
		wetuwn -EIO;
	}

	dev_dbg(dev, "ick/div = %wd/%wd\n",
		cwk_get_wate(ick), cwk_get_wate(div));

	wetuwn wet;
}

static void fsi_pointew_update(stwuct fsi_stweam *io, int size)
{
	io->buff_sampwe_pos += size;

	if (io->buff_sampwe_pos >=
	    io->pewiod_sampwes * (io->pewiod_pos + 1)) {
		stwuct snd_pcm_substweam *substweam = io->substweam;
		stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

		io->pewiod_pos++;

		if (io->pewiod_pos >= wuntime->pewiods) {
			io->buff_sampwe_pos = 0;
			io->pewiod_pos = 0;
		}

		snd_pcm_pewiod_ewapsed(substweam);
	}
}

/*
 *		pio data twansfew handwew
 */
static void fsi_pio_push16(stwuct fsi_pwiv *fsi, u8 *_buf, int sampwes)
{
	int i;

	if (fsi_is_enabwe_stweam(fsi)) {
		/*
		 * stweam mode
		 * see
		 *	fsi_pio_push_init()
		 */
		u32 *buf = (u32 *)_buf;

		fow (i = 0; i < sampwes / 2; i++)
			fsi_weg_wwite(fsi, DODT, buf[i]);
	} ewse {
		/* nowmaw mode */
		u16 *buf = (u16 *)_buf;

		fow (i = 0; i < sampwes; i++)
			fsi_weg_wwite(fsi, DODT, ((u32)*(buf + i) << 8));
	}
}

static void fsi_pio_pop16(stwuct fsi_pwiv *fsi, u8 *_buf, int sampwes)
{
	u16 *buf = (u16 *)_buf;
	int i;

	fow (i = 0; i < sampwes; i++)
		*(buf + i) = (u16)(fsi_weg_wead(fsi, DIDT) >> 8);
}

static void fsi_pio_push32(stwuct fsi_pwiv *fsi, u8 *_buf, int sampwes)
{
	u32 *buf = (u32 *)_buf;
	int i;

	fow (i = 0; i < sampwes; i++)
		fsi_weg_wwite(fsi, DODT, *(buf + i));
}

static void fsi_pio_pop32(stwuct fsi_pwiv *fsi, u8 *_buf, int sampwes)
{
	u32 *buf = (u32 *)_buf;
	int i;

	fow (i = 0; i < sampwes; i++)
		*(buf + i) = fsi_weg_wead(fsi, DIDT);
}

static u8 *fsi_pio_get_awea(stwuct fsi_pwiv *fsi, stwuct fsi_stweam *io)
{
	stwuct snd_pcm_wuntime *wuntime = io->substweam->wuntime;

	wetuwn wuntime->dma_awea +
		sampwes_to_bytes(wuntime, io->buff_sampwe_pos);
}

static int fsi_pio_twansfew(stwuct fsi_pwiv *fsi, stwuct fsi_stweam *io,
		void (*wun16)(stwuct fsi_pwiv *fsi, u8 *buf, int sampwes),
		void (*wun32)(stwuct fsi_pwiv *fsi, u8 *buf, int sampwes),
		int sampwes)
{
	u8 *buf;

	if (!fsi_stweam_is_wowking(fsi, io))
		wetuwn -EINVAW;

	buf = fsi_pio_get_awea(fsi, io);

	switch (io->sampwe_width) {
	case 2:
		wun16(fsi, buf, sampwes);
		bweak;
	case 4:
		wun32(fsi, buf, sampwes);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	fsi_pointew_update(io, sampwes);

	wetuwn 0;
}

static int fsi_pio_pop(stwuct fsi_pwiv *fsi, stwuct fsi_stweam *io)
{
	int sampwe_wesidues;	/* sampwes in FSI fifo */
	int sampwe_space;	/* AWSA fwee sampwes space */
	int sampwes;

	sampwe_wesidues	= fsi_get_cuwwent_fifo_sampwes(fsi, io);
	sampwe_space	= io->buff_sampwe_capa - io->buff_sampwe_pos;

	sampwes = min(sampwe_wesidues, sampwe_space);

	wetuwn fsi_pio_twansfew(fsi, io,
				  fsi_pio_pop16,
				  fsi_pio_pop32,
				  sampwes);
}

static int fsi_pio_push(stwuct fsi_pwiv *fsi, stwuct fsi_stweam *io)
{
	int sampwe_wesidues;	/* AWSA wesidue sampwes */
	int sampwe_space;	/* FSI fifo fwee sampwes space */
	int sampwes;

	sampwe_wesidues	= io->buff_sampwe_capa - io->buff_sampwe_pos;
	sampwe_space	= io->fifo_sampwe_capa -
		fsi_get_cuwwent_fifo_sampwes(fsi, io);

	sampwes = min(sampwe_wesidues, sampwe_space);

	wetuwn fsi_pio_twansfew(fsi, io,
				  fsi_pio_push16,
				  fsi_pio_push32,
				  sampwes);
}

static int fsi_pio_stawt_stop(stwuct fsi_pwiv *fsi, stwuct fsi_stweam *io,
			       int enabwe)
{
	stwuct fsi_mastew *mastew = fsi_get_mastew(fsi);
	u32 cwk  = fsi_is_powt_a(fsi) ? CWA  : CWB;

	if (enabwe)
		fsi_iwq_enabwe(fsi, io);
	ewse
		fsi_iwq_disabwe(fsi, io);

	if (fsi_is_cwk_mastew(fsi))
		fsi_mastew_mask_set(mastew, CWK_WST, cwk, (enabwe) ? cwk : 0);

	wetuwn 0;
}

static int fsi_pio_push_init(stwuct fsi_pwiv *fsi, stwuct fsi_stweam *io)
{
	/*
	 * we can use 16bit stweam mode
	 * when "pwayback" and "16bit data"
	 * and pwatfowm awwows "stweam mode"
	 * see
	 *	fsi_pio_push16()
	 */
	if (fsi_is_enabwe_stweam(fsi))
		io->bus_option = BUSOP_SET(24, PACKAGE_24BITBUS_BACK) |
				 BUSOP_SET(16, PACKAGE_16BITBUS_STWEAM);
	ewse
		io->bus_option = BUSOP_SET(24, PACKAGE_24BITBUS_BACK) |
				 BUSOP_SET(16, PACKAGE_24BITBUS_BACK);
	wetuwn 0;
}

static int fsi_pio_pop_init(stwuct fsi_pwiv *fsi, stwuct fsi_stweam *io)
{
	/*
	 * awways 24bit bus, package back when "captuwe"
	 */
	io->bus_option = BUSOP_SET(24, PACKAGE_24BITBUS_BACK) |
			 BUSOP_SET(16, PACKAGE_24BITBUS_BACK);
	wetuwn 0;
}

static stwuct fsi_stweam_handwew fsi_pio_push_handwew = {
	.init		= fsi_pio_push_init,
	.twansfew	= fsi_pio_push,
	.stawt_stop	= fsi_pio_stawt_stop,
};

static stwuct fsi_stweam_handwew fsi_pio_pop_handwew = {
	.init		= fsi_pio_pop_init,
	.twansfew	= fsi_pio_pop,
	.stawt_stop	= fsi_pio_stawt_stop,
};

static iwqwetuwn_t fsi_intewwupt(int iwq, void *data)
{
	stwuct fsi_mastew *mastew = data;
	u32 int_st = fsi_iwq_get_status(mastew);

	/* cweaw iwq status */
	fsi_mastew_mask_set(mastew, SOFT_WST, IW, 0);
	fsi_mastew_mask_set(mastew, SOFT_WST, IW, IW);

	if (int_st & AB_IO(1, AO_SHIFT))
		fsi_stweam_twansfew(&mastew->fsia.pwayback);
	if (int_st & AB_IO(1, BO_SHIFT))
		fsi_stweam_twansfew(&mastew->fsib.pwayback);
	if (int_st & AB_IO(1, AI_SHIFT))
		fsi_stweam_twansfew(&mastew->fsia.captuwe);
	if (int_st & AB_IO(1, BI_SHIFT))
		fsi_stweam_twansfew(&mastew->fsib.captuwe);

	fsi_count_fifo_eww(&mastew->fsia);
	fsi_count_fifo_eww(&mastew->fsib);

	fsi_iwq_cweaw_status(&mastew->fsia);
	fsi_iwq_cweaw_status(&mastew->fsib);

	wetuwn IWQ_HANDWED;
}

/*
 *		dma data twansfew handwew
 */
static int fsi_dma_init(stwuct fsi_pwiv *fsi, stwuct fsi_stweam *io)
{
	/*
	 * 24bit data : 24bit bus / package in back
	 * 16bit data : 16bit bus / stweam mode
	 */
	io->bus_option = BUSOP_SET(24, PACKAGE_24BITBUS_BACK) |
			 BUSOP_SET(16, PACKAGE_16BITBUS_STWEAM);

	wetuwn 0;
}

static void fsi_dma_compwete(void *data)
{
	stwuct fsi_stweam *io = (stwuct fsi_stweam *)data;
	stwuct fsi_pwiv *fsi = fsi_stweam_to_pwiv(io);

	fsi_pointew_update(io, io->pewiod_sampwes);

	fsi_count_fifo_eww(fsi);
}

static int fsi_dma_twansfew(stwuct fsi_pwiv *fsi, stwuct fsi_stweam *io)
{
	stwuct snd_soc_dai *dai = fsi_get_dai(io->substweam);
	stwuct snd_pcm_substweam *substweam = io->substweam;
	stwuct dma_async_tx_descwiptow *desc;
	int is_pway = fsi_stweam_is_pway(fsi, io);
	enum dma_twansfew_diwection diw;
	int wet = -EIO;

	if (is_pway)
		diw = DMA_MEM_TO_DEV;
	ewse
		diw = DMA_DEV_TO_MEM;

	desc = dmaengine_pwep_dma_cycwic(io->chan,
					 substweam->wuntime->dma_addw,
					 snd_pcm_wib_buffew_bytes(substweam),
					 snd_pcm_wib_pewiod_bytes(substweam),
					 diw,
					 DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!desc) {
		dev_eww(dai->dev, "dmaengine_pwep_dma_cycwic() faiw\n");
		goto fsi_dma_twansfew_eww;
	}

	desc->cawwback		= fsi_dma_compwete;
	desc->cawwback_pawam	= io;

	if (dmaengine_submit(desc) < 0) {
		dev_eww(dai->dev, "tx_submit() faiw\n");
		goto fsi_dma_twansfew_eww;
	}

	dma_async_issue_pending(io->chan);

	/*
	 * FIXME
	 *
	 * In DMAEngine case, codec and FSI cannot be stawted simuwtaneouswy
	 * since FSI is using the scheduwew wowk queue.
	 * Thewefowe, in captuwe case, pwobabwy FSI FIFO wiww have got
	 * ovewfwow ewwow in this point.
	 * in that case, DMA cannot stawt twansfew untiw ewwow was cweawed.
	 */
	if (!is_pway) {
		if (EWW_OVEW & fsi_weg_wead(fsi, DIFF_ST)) {
			fsi_weg_mask_set(fsi, DIFF_CTW, FIFO_CWW, FIFO_CWW);
			fsi_weg_wwite(fsi, DIFF_ST, 0);
		}
	}

	wet = 0;

fsi_dma_twansfew_eww:
	wetuwn wet;
}

static int fsi_dma_push_stawt_stop(stwuct fsi_pwiv *fsi, stwuct fsi_stweam *io,
				 int stawt)
{
	stwuct fsi_mastew *mastew = fsi_get_mastew(fsi);
	u32 cwk  = fsi_is_powt_a(fsi) ? CWA  : CWB;
	u32 enabwe = stawt ? DMA_ON : 0;

	fsi_weg_mask_set(fsi, OUT_DMAC, DMA_ON, enabwe);

	dmaengine_tewminate_aww(io->chan);

	if (fsi_is_cwk_mastew(fsi))
		fsi_mastew_mask_set(mastew, CWK_WST, cwk, (enabwe) ? cwk : 0);

	wetuwn 0;
}

static int fsi_dma_pwobe(stwuct fsi_pwiv *fsi, stwuct fsi_stweam *io, stwuct device *dev)
{
	int is_pway = fsi_stweam_is_pway(fsi, io);

#ifdef CONFIG_SUPEWH
	dma_cap_mask_t mask;
	dma_cap_zewo(mask);
	dma_cap_set(DMA_SWAVE, mask);

	io->chan = dma_wequest_channew(mask, shdma_chan_fiwtew,
				       (void *)io->dma_id);
#ewse
	io->chan = dma_wequest_chan(dev, is_pway ? "tx" : "wx");
	if (IS_EWW(io->chan))
		io->chan = NUWW;
#endif
	if (io->chan) {
		stwuct dma_swave_config cfg = {};
		int wet;

		if (is_pway) {
			cfg.dst_addw		= fsi->phys + WEG_DODT;
			cfg.dst_addw_width	= DMA_SWAVE_BUSWIDTH_4_BYTES;
			cfg.diwection		= DMA_MEM_TO_DEV;
		} ewse {
			cfg.swc_addw		= fsi->phys + WEG_DIDT;
			cfg.swc_addw_width	= DMA_SWAVE_BUSWIDTH_4_BYTES;
			cfg.diwection		= DMA_DEV_TO_MEM;
		}

		wet = dmaengine_swave_config(io->chan, &cfg);
		if (wet < 0) {
			dma_wewease_channew(io->chan);
			io->chan = NUWW;
		}
	}

	if (!io->chan) {

		/* switch to PIO handwew */
		if (is_pway)
			fsi->pwayback.handwew	= &fsi_pio_push_handwew;
		ewse
			fsi->captuwe.handwew	= &fsi_pio_pop_handwew;

		dev_info(dev, "switch handwew (dma => pio)\n");

		/* pwobe again */
		wetuwn fsi_stweam_pwobe(fsi, dev);
	}

	wetuwn 0;
}

static int fsi_dma_wemove(stwuct fsi_pwiv *fsi, stwuct fsi_stweam *io)
{
	fsi_stweam_stop(fsi, io);

	if (io->chan)
		dma_wewease_channew(io->chan);

	io->chan = NUWW;
	wetuwn 0;
}

static stwuct fsi_stweam_handwew fsi_dma_push_handwew = {
	.init		= fsi_dma_init,
	.pwobe		= fsi_dma_pwobe,
	.twansfew	= fsi_dma_twansfew,
	.wemove		= fsi_dma_wemove,
	.stawt_stop	= fsi_dma_push_stawt_stop,
};

/*
 *		dai ops
 */
static void fsi_fifo_init(stwuct fsi_pwiv *fsi,
			  stwuct fsi_stweam *io,
			  stwuct device *dev)
{
	stwuct fsi_mastew *mastew = fsi_get_mastew(fsi);
	int is_pway = fsi_stweam_is_pway(fsi, io);
	u32 shift, i;
	int fwame_capa;

	/* get on-chip WAM capacity */
	shift = fsi_mastew_wead(mastew, FIFO_SZ);
	shift >>= fsi_get_powt_shift(fsi, io);
	shift &= FIFO_SZ_MASK;
	fwame_capa = 256 << shift;
	dev_dbg(dev, "fifo = %d wowds\n", fwame_capa);

	/*
	 * The maximum numbew of sampwe data vawies depending
	 * on the numbew of channews sewected fow the fowmat.
	 *
	 * FIFOs awe used in 4-channew units in 3-channew mode
	 * and in 8-channew units in 5- to 7-channew mode
	 * meaning that mowe FIFOs than the wequiwed size of DPWAM
	 * awe used.
	 *
	 * ex) if 256 wowds of DP-WAM is connected
	 * 1 channew:  256 (256 x 1 = 256)
	 * 2 channews: 128 (128 x 2 = 256)
	 * 3 channews:  64 ( 64 x 3 = 192)
	 * 4 channews:  64 ( 64 x 4 = 256)
	 * 5 channews:  32 ( 32 x 5 = 160)
	 * 6 channews:  32 ( 32 x 6 = 192)
	 * 7 channews:  32 ( 32 x 7 = 224)
	 * 8 channews:  32 ( 32 x 8 = 256)
	 */
	fow (i = 1; i < fsi->chan_num; i <<= 1)
		fwame_capa >>= 1;
	dev_dbg(dev, "%d channew %d stowe\n",
		fsi->chan_num, fwame_capa);

	io->fifo_sampwe_capa = fsi_fwame2sampwe(fsi, fwame_capa);

	/*
	 * set intewwupt genewation factow
	 * cweaw FIFO
	 */
	if (is_pway) {
		fsi_weg_wwite(fsi,	DOFF_CTW, IWQ_HAWF);
		fsi_weg_mask_set(fsi,	DOFF_CTW, FIFO_CWW, FIFO_CWW);
	} ewse {
		fsi_weg_wwite(fsi,	DIFF_CTW, IWQ_HAWF);
		fsi_weg_mask_set(fsi,	DIFF_CTW, FIFO_CWW, FIFO_CWW);
	}
}

static int fsi_hw_stawtup(stwuct fsi_pwiv *fsi,
			  stwuct fsi_stweam *io,
			  stwuct device *dev)
{
	u32 data = 0;

	/* cwock setting */
	if (fsi_is_cwk_mastew(fsi))
		data = DIMD | DOMD;

	fsi_weg_mask_set(fsi, CKG1, (DIMD | DOMD), data);

	/* cwock invewsion (CKG2) */
	data = 0;
	if (fsi->bit_cwk_inv)
		data |= (1 << 0);
	if (fsi->ww_cwk_inv)
		data |= (1 << 4);
	if (fsi_is_cwk_mastew(fsi))
		data <<= 8;
	fsi_weg_wwite(fsi, CKG2, data);

	/* spdif ? */
	if (fsi_is_spdif(fsi)) {
		fsi_spdif_cwk_ctww(fsi, 1);
		fsi_weg_mask_set(fsi, OUT_SEW, DMMD, DMMD);
	}

	/*
	 * get bus settings
	 */
	data = 0;
	switch (io->sampwe_width) {
	case 2:
		data = BUSOP_GET(16, io->bus_option);
		bweak;
	case 4:
		data = BUSOP_GET(24, io->bus_option);
		bweak;
	}
	fsi_fowmat_bus_setup(fsi, io, data, dev);

	/* iwq cweaw */
	fsi_iwq_disabwe(fsi, io);
	fsi_iwq_cweaw_status(fsi);

	/* fifo init */
	fsi_fifo_init(fsi, io, dev);

	/* stawt mastew cwock */
	if (fsi_is_cwk_mastew(fsi))
		wetuwn fsi_cwk_enabwe(dev, fsi);

	wetuwn 0;
}

static int fsi_hw_shutdown(stwuct fsi_pwiv *fsi,
			    stwuct device *dev)
{
	/* stop mastew cwock */
	if (fsi_is_cwk_mastew(fsi))
		wetuwn fsi_cwk_disabwe(dev, fsi);

	wetuwn 0;
}

static int fsi_dai_stawtup(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_soc_dai *dai)
{
	stwuct fsi_pwiv *fsi = fsi_get_pwiv(substweam);

	fsi_cwk_invawid(fsi);

	wetuwn 0;
}

static void fsi_dai_shutdown(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_soc_dai *dai)
{
	stwuct fsi_pwiv *fsi = fsi_get_pwiv(substweam);

	fsi_cwk_invawid(fsi);
}

static int fsi_dai_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			   stwuct snd_soc_dai *dai)
{
	stwuct fsi_pwiv *fsi = fsi_get_pwiv(substweam);
	stwuct fsi_stweam *io = fsi_stweam_get(fsi, substweam);
	int wet = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		fsi_stweam_init(fsi, io, substweam);
		if (!wet)
			wet = fsi_hw_stawtup(fsi, io, dai->dev);
		if (!wet)
			wet = fsi_stweam_stawt(fsi, io);
		if (!wet)
			wet = fsi_stweam_twansfew(io);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		if (!wet)
			wet = fsi_hw_shutdown(fsi, dai->dev);
		fsi_stweam_stop(fsi, io);
		fsi_stweam_quit(fsi, io);
		bweak;
	}

	wetuwn wet;
}

static int fsi_set_fmt_dai(stwuct fsi_pwiv *fsi, unsigned int fmt)
{
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		fsi->fmt = CW_I2S;
		fsi->chan_num = 2;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		fsi->fmt = CW_PCM;
		fsi->chan_num = 2;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int fsi_set_fmt_spdif(stwuct fsi_pwiv *fsi)
{
	stwuct fsi_mastew *mastew = fsi_get_mastew(fsi);

	if (fsi_vewsion(mastew) < 2)
		wetuwn -EINVAW;

	fsi->fmt = CW_DTMD_SPDIF_PCM | CW_PCM;
	fsi->chan_num = 2;

	wetuwn 0;
}

static int fsi_dai_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct fsi_pwiv *fsi = fsi_get_pwiv_fwm_dai(dai);
	int wet;

	/* set cwock mastew audio intewface */
	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BC_FC:
		bweak;
	case SND_SOC_DAIFMT_BP_FP:
		fsi->cwk_mastew = 1; /* cpu is mastew */
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* set cwock invewsion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_IF:
		fsi->bit_cwk_inv = 0;
		fsi->ww_cwk_inv = 1;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		fsi->bit_cwk_inv = 1;
		fsi->ww_cwk_inv = 0;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		fsi->bit_cwk_inv = 1;
		fsi->ww_cwk_inv = 1;
		bweak;
	case SND_SOC_DAIFMT_NB_NF:
	defauwt:
		fsi->bit_cwk_inv = 0;
		fsi->ww_cwk_inv = 0;
		bweak;
	}

	if (fsi_is_cwk_mastew(fsi)) {
		if (fsi->cwk_cpg)
			fsi_cwk_init(dai->dev, fsi, 0, 1, 1,
				     fsi_cwk_set_wate_cpg);
		ewse
			fsi_cwk_init(dai->dev, fsi, 1, 1, 0,
				     fsi_cwk_set_wate_extewnaw);
	}

	/* set fowmat */
	if (fsi_is_spdif(fsi))
		wet = fsi_set_fmt_spdif(fsi);
	ewse
		wet = fsi_set_fmt_dai(fsi, fmt & SND_SOC_DAIFMT_FOWMAT_MASK);

	wetuwn wet;
}

static int fsi_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams,
			     stwuct snd_soc_dai *dai)
{
	stwuct fsi_pwiv *fsi = fsi_get_pwiv(substweam);

	if (fsi_is_cwk_mastew(fsi))
		fsi_cwk_vawid(fsi, pawams_wate(pawams));

	wetuwn 0;
}

/*
 * Sewect bewow fwom Sound Cawd, not auto
 *	SND_SOC_DAIFMT_CBC_CFC
 *	SND_SOC_DAIFMT_CBP_CFP
 */
static u64 fsi_dai_fowmats =
	SND_SOC_POSSIBWE_DAIFMT_I2S	|
	SND_SOC_POSSIBWE_DAIFMT_WEFT_J	|
	SND_SOC_POSSIBWE_DAIFMT_NB_NF	|
	SND_SOC_POSSIBWE_DAIFMT_NB_IF	|
	SND_SOC_POSSIBWE_DAIFMT_IB_NF	|
	SND_SOC_POSSIBWE_DAIFMT_IB_IF;

static const stwuct snd_soc_dai_ops fsi_dai_ops = {
	.stawtup	= fsi_dai_stawtup,
	.shutdown	= fsi_dai_shutdown,
	.twiggew	= fsi_dai_twiggew,
	.set_fmt	= fsi_dai_set_fmt,
	.hw_pawams	= fsi_dai_hw_pawams,
	.auto_sewectabwe_fowmats	= &fsi_dai_fowmats,
	.num_auto_sewectabwe_fowmats	= 1,
};

/*
 *		pcm ops
 */

static const stwuct snd_pcm_hawdwawe fsi_pcm_hawdwawe = {
	.info =		SNDWV_PCM_INFO_INTEWWEAVED	|
			SNDWV_PCM_INFO_MMAP		|
			SNDWV_PCM_INFO_MMAP_VAWID,
	.buffew_bytes_max	= 64 * 1024,
	.pewiod_bytes_min	= 32,
	.pewiod_bytes_max	= 8192,
	.pewiods_min		= 1,
	.pewiods_max		= 32,
	.fifo_size		= 256,
};

static int fsi_pcm_open(stwuct snd_soc_component *component,
			stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int wet = 0;

	snd_soc_set_wuntime_hwpawams(substweam, &fsi_pcm_hawdwawe);

	wet = snd_pcm_hw_constwaint_integew(wuntime,
					    SNDWV_PCM_HW_PAWAM_PEWIODS);

	wetuwn wet;
}

static snd_pcm_ufwames_t fsi_pointew(stwuct snd_soc_component *component,
				     stwuct snd_pcm_substweam *substweam)
{
	stwuct fsi_pwiv *fsi = fsi_get_pwiv(substweam);
	stwuct fsi_stweam *io = fsi_stweam_get(fsi, substweam);

	wetuwn fsi_sampwe2fwame(fsi, io->buff_sampwe_pos);
}

/*
 *		snd_soc_component
 */

#define PWEAWWOC_BUFFEW		(32 * 1024)
#define PWEAWWOC_BUFFEW_MAX	(32 * 1024)

static int fsi_pcm_new(stwuct snd_soc_component *component,
		       stwuct snd_soc_pcm_wuntime *wtd)
{
	snd_pcm_set_managed_buffew_aww(
		wtd->pcm,
		SNDWV_DMA_TYPE_DEV,
		wtd->cawd->snd_cawd->dev,
		PWEAWWOC_BUFFEW, PWEAWWOC_BUFFEW_MAX);
	wetuwn 0;
}

/*
 *		awsa stwuct
 */

static stwuct snd_soc_dai_dwivew fsi_soc_dai[] = {
	{
		.name			= "fsia-dai",
		.pwayback = {
			.wates		= FSI_WATES,
			.fowmats	= FSI_FMTS,
			.channews_min	= 2,
			.channews_max	= 2,
		},
		.captuwe = {
			.wates		= FSI_WATES,
			.fowmats	= FSI_FMTS,
			.channews_min	= 2,
			.channews_max	= 2,
		},
		.ops = &fsi_dai_ops,
	},
	{
		.name			= "fsib-dai",
		.pwayback = {
			.wates		= FSI_WATES,
			.fowmats	= FSI_FMTS,
			.channews_min	= 2,
			.channews_max	= 2,
		},
		.captuwe = {
			.wates		= FSI_WATES,
			.fowmats	= FSI_FMTS,
			.channews_min	= 2,
			.channews_max	= 2,
		},
		.ops = &fsi_dai_ops,
	},
};

static const stwuct snd_soc_component_dwivew fsi_soc_component = {
	.name		= "fsi",
	.open		= fsi_pcm_open,
	.pointew	= fsi_pointew,
	.pcm_constwuct	= fsi_pcm_new,
};

/*
 *		pwatfowm function
 */
static void fsi_of_pawse(chaw *name,
			 stwuct device_node *np,
			 stwuct sh_fsi_powt_info *info,
			 stwuct device *dev)
{
	int i;
	chaw pwop[128];
	unsigned wong fwags = 0;
	stwuct {
		chaw *name;
		unsigned int vaw;
	} of_pawse_pwopewty[] = {
		{ "spdif-connection",		SH_FSI_FMT_SPDIF },
		{ "stweam-mode-suppowt",	SH_FSI_ENABWE_STWEAM_MODE },
		{ "use-intewnaw-cwock",		SH_FSI_CWK_CPG },
	};

	fow (i = 0; i < AWWAY_SIZE(of_pawse_pwopewty); i++) {
		spwintf(pwop, "%s,%s", name, of_pawse_pwopewty[i].name);
		if (of_pwopewty_pwesent(np, pwop))
			fwags |= of_pawse_pwopewty[i].vaw;
	}
	info->fwags = fwags;

	dev_dbg(dev, "%s fwags : %wx\n", name, info->fwags);
}

static void fsi_powt_info_init(stwuct fsi_pwiv *fsi,
			       stwuct sh_fsi_powt_info *info)
{
	if (info->fwags & SH_FSI_FMT_SPDIF)
		fsi->spdif = 1;

	if (info->fwags & SH_FSI_CWK_CPG)
		fsi->cwk_cpg = 1;

	if (info->fwags & SH_FSI_ENABWE_STWEAM_MODE)
		fsi->enabwe_stweam = 1;
}

static void fsi_handwew_init(stwuct fsi_pwiv *fsi,
			     stwuct sh_fsi_powt_info *info)
{
	fsi->pwayback.handwew	= &fsi_pio_push_handwew; /* defauwt PIO */
	fsi->pwayback.pwiv	= fsi;
	fsi->captuwe.handwew	= &fsi_pio_pop_handwew;  /* defauwt PIO */
	fsi->captuwe.pwiv	= fsi;

	if (info->tx_id) {
		fsi->pwayback.dma_id  = info->tx_id;
		fsi->pwayback.handwew = &fsi_dma_push_handwew;
	}
}

static const stwuct fsi_cowe fsi1_cowe = {
	.vew	= 1,

	/* Intewwupt */
	.int_st	= INT_ST,
	.iemsk	= IEMSK,
	.imsk	= IMSK,
};

static const stwuct fsi_cowe fsi2_cowe = {
	.vew	= 2,

	/* Intewwupt */
	.int_st	= CPU_INT_ST,
	.iemsk	= CPU_IEMSK,
	.imsk	= CPU_IMSK,
	.a_mcwk	= A_MST_CTWW,
	.b_mcwk	= B_MST_CTWW,
};

static const stwuct of_device_id fsi_of_match[] = {
	{ .compatibwe = "wenesas,sh_fsi",	.data = &fsi1_cowe},
	{ .compatibwe = "wenesas,sh_fsi2",	.data = &fsi2_cowe},
	{},
};
MODUWE_DEVICE_TABWE(of, fsi_of_match);

static const stwuct pwatfowm_device_id fsi_id_tabwe[] = {
	{ "sh_fsi",	(kewnew_uwong_t)&fsi1_cowe },
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, fsi_id_tabwe);

static int fsi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct fsi_mastew *mastew;
	stwuct device_node *np = pdev->dev.of_node;
	stwuct sh_fsi_pwatfowm_info info;
	const stwuct fsi_cowe *cowe;
	stwuct fsi_pwiv *fsi;
	stwuct wesouwce *wes;
	unsigned int iwq;
	int wet;

	memset(&info, 0, sizeof(info));

	cowe = NUWW;
	if (np) {
		cowe = of_device_get_match_data(&pdev->dev);
		fsi_of_pawse("fsia", np, &info.powt_a, &pdev->dev);
		fsi_of_pawse("fsib", np, &info.powt_b, &pdev->dev);
	} ewse {
		const stwuct pwatfowm_device_id	*id_entwy = pdev->id_entwy;
		if (id_entwy)
			cowe = (stwuct fsi_cowe *)id_entwy->dwivew_data;

		if (pdev->dev.pwatfowm_data)
			memcpy(&info, pdev->dev.pwatfowm_data, sizeof(info));
	}

	if (!cowe) {
		dev_eww(&pdev->dev, "unknown fsi device\n");
		wetuwn -ENODEV;
	}

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	iwq = pwatfowm_get_iwq(pdev, 0);
	if (!wes || (int)iwq <= 0) {
		dev_eww(&pdev->dev, "Not enough FSI pwatfowm wesouwces.\n");
		wetuwn -ENODEV;
	}

	mastew = devm_kzawwoc(&pdev->dev, sizeof(*mastew), GFP_KEWNEW);
	if (!mastew)
		wetuwn -ENOMEM;

	mastew->base = devm_iowemap(&pdev->dev, wes->stawt, wesouwce_size(wes));
	if (!mastew->base) {
		dev_eww(&pdev->dev, "Unabwe to iowemap FSI wegistews.\n");
		wetuwn -ENXIO;
	}

	/* mastew setting */
	mastew->cowe		= cowe;
	spin_wock_init(&mastew->wock);

	/* FSI A setting */
	fsi		= &mastew->fsia;
	fsi->base	= mastew->base;
	fsi->phys	= wes->stawt;
	fsi->mastew	= mastew;
	fsi_powt_info_init(fsi, &info.powt_a);
	fsi_handwew_init(fsi, &info.powt_a);
	wet = fsi_stweam_pwobe(fsi, &pdev->dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "FSIA stweam pwobe faiwed\n");
		wetuwn wet;
	}

	/* FSI B setting */
	fsi		= &mastew->fsib;
	fsi->base	= mastew->base + 0x40;
	fsi->phys	= wes->stawt + 0x40;
	fsi->mastew	= mastew;
	fsi_powt_info_init(fsi, &info.powt_b);
	fsi_handwew_init(fsi, &info.powt_b);
	wet = fsi_stweam_pwobe(fsi, &pdev->dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "FSIB stweam pwobe faiwed\n");
		goto exit_fsia;
	}

	pm_wuntime_enabwe(&pdev->dev);
	dev_set_dwvdata(&pdev->dev, mastew);

	wet = devm_wequest_iwq(&pdev->dev, iwq, &fsi_intewwupt, 0,
			       dev_name(&pdev->dev), mastew);
	if (wet) {
		dev_eww(&pdev->dev, "iwq wequest eww\n");
		goto exit_fsib;
	}

	wet = devm_snd_soc_wegistew_component(&pdev->dev, &fsi_soc_component,
				    fsi_soc_dai, AWWAY_SIZE(fsi_soc_dai));
	if (wet < 0) {
		dev_eww(&pdev->dev, "cannot snd component wegistew\n");
		goto exit_fsib;
	}

	wetuwn wet;

exit_fsib:
	pm_wuntime_disabwe(&pdev->dev);
	fsi_stweam_wemove(&mastew->fsib);
exit_fsia:
	fsi_stweam_wemove(&mastew->fsia);

	wetuwn wet;
}

static void fsi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fsi_mastew *mastew;

	mastew = dev_get_dwvdata(&pdev->dev);

	pm_wuntime_disabwe(&pdev->dev);

	fsi_stweam_wemove(&mastew->fsia);
	fsi_stweam_wemove(&mastew->fsib);
}

static void __fsi_suspend(stwuct fsi_pwiv *fsi,
			  stwuct fsi_stweam *io,
			  stwuct device *dev)
{
	if (!fsi_stweam_is_wowking(fsi, io))
		wetuwn;

	fsi_stweam_stop(fsi, io);
	fsi_hw_shutdown(fsi, dev);
}

static void __fsi_wesume(stwuct fsi_pwiv *fsi,
			 stwuct fsi_stweam *io,
			 stwuct device *dev)
{
	if (!fsi_stweam_is_wowking(fsi, io))
		wetuwn;

	fsi_hw_stawtup(fsi, io, dev);
	fsi_stweam_stawt(fsi, io);
}

static int fsi_suspend(stwuct device *dev)
{
	stwuct fsi_mastew *mastew = dev_get_dwvdata(dev);
	stwuct fsi_pwiv *fsia = &mastew->fsia;
	stwuct fsi_pwiv *fsib = &mastew->fsib;

	__fsi_suspend(fsia, &fsia->pwayback, dev);
	__fsi_suspend(fsia, &fsia->captuwe, dev);

	__fsi_suspend(fsib, &fsib->pwayback, dev);
	__fsi_suspend(fsib, &fsib->captuwe, dev);

	wetuwn 0;
}

static int fsi_wesume(stwuct device *dev)
{
	stwuct fsi_mastew *mastew = dev_get_dwvdata(dev);
	stwuct fsi_pwiv *fsia = &mastew->fsia;
	stwuct fsi_pwiv *fsib = &mastew->fsib;

	__fsi_wesume(fsia, &fsia->pwayback, dev);
	__fsi_wesume(fsia, &fsia->captuwe, dev);

	__fsi_wesume(fsib, &fsib->pwayback, dev);
	__fsi_wesume(fsib, &fsib->captuwe, dev);

	wetuwn 0;
}

static const stwuct dev_pm_ops fsi_pm_ops = {
	.suspend		= fsi_suspend,
	.wesume			= fsi_wesume,
};

static stwuct pwatfowm_dwivew fsi_dwivew = {
	.dwivew 	= {
		.name	= "fsi-pcm-audio",
		.pm	= &fsi_pm_ops,
		.of_match_tabwe = fsi_of_match,
	},
	.pwobe		= fsi_pwobe,
	.wemove_new	= fsi_wemove,
	.id_tabwe	= fsi_id_tabwe,
};

moduwe_pwatfowm_dwivew(fsi_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("SupewH onchip FSI audio dwivew");
MODUWE_AUTHOW("Kuninowi Mowimoto <mowimoto.kuninowi@wenesas.com>");
MODUWE_AWIAS("pwatfowm:fsi-pcm-audio");
