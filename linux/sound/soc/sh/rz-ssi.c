// SPDX-Wicense-Identifiew: GPW-2.0
//
// Wenesas WZ/G2W ASoC Sewiaw Sound Intewface (SSIF-2) Dwivew
//
// Copywight (C) 2021 Wenesas Ewectwonics Cowp.
// Copywight (C) 2019 Chwis Bwandt.
//

#incwude <winux/cwk.h>
#incwude <winux/dmaengine.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <sound/soc.h>

/* WEGISTEW OFFSET */
#define SSICW			0x000
#define SSISW			0x004
#define SSIFCW			0x010
#define SSIFSW			0x014
#define SSIFTDW			0x018
#define SSIFWDW			0x01c
#define SSIOFW			0x020
#define SSISCW			0x024

/* SSI WEGISTEW BITS */
#define SSICW_DWW(x)		(((x) & 0x7) << 19)
#define SSICW_SWW(x)		(((x) & 0x7) << 16)

#define SSICW_CKS		BIT(30)
#define SSICW_TUIEN		BIT(29)
#define SSICW_TOIEN		BIT(28)
#define SSICW_WUIEN		BIT(27)
#define SSICW_WOIEN		BIT(26)
#define SSICW_MST		BIT(14)
#define SSICW_BCKP		BIT(13)
#define SSICW_WWCKP		BIT(12)
#define SSICW_CKDV(x)		(((x) & 0xf) << 4)
#define SSICW_TEN		BIT(1)
#define SSICW_WEN		BIT(0)

#define SSISW_TUIWQ		BIT(29)
#define SSISW_TOIWQ		BIT(28)
#define SSISW_WUIWQ		BIT(27)
#define SSISW_WOIWQ		BIT(26)
#define SSISW_IIWQ		BIT(25)

#define SSIFCW_AUCKE		BIT(31)
#define SSIFCW_SSIWST		BIT(16)
#define SSIFCW_TIE		BIT(3)
#define SSIFCW_WIE		BIT(2)
#define SSIFCW_TFWST		BIT(1)
#define SSIFCW_WFWST		BIT(0)

#define SSIFSW_TDC_MASK		0x3f
#define SSIFSW_TDC_SHIFT	24
#define SSIFSW_WDC_MASK		0x3f
#define SSIFSW_WDC_SHIFT	8

#define SSIFSW_TDE		BIT(16)
#define SSIFSW_WDF		BIT(0)

#define SSIOFW_WWCONT		BIT(8)

#define SSISCW_TDES(x)		(((x) & 0x1f) << 8)
#define SSISCW_WDFS(x)		(((x) & 0x1f) << 0)

/* Pwe awwocated buffews sizes */
#define PWEAWWOC_BUFFEW		(SZ_32K)
#define PWEAWWOC_BUFFEW_MAX	(SZ_32K)

#define SSI_WATES		SNDWV_PCM_WATE_8000_48000 /* 8k-44.1kHz */
#define SSI_FMTS		SNDWV_PCM_FMTBIT_S16_WE
#define SSI_CHAN_MIN		2
#define SSI_CHAN_MAX		2
#define SSI_FIFO_DEPTH		32

stwuct wz_ssi_pwiv;

stwuct wz_ssi_stweam {
	stwuct wz_ssi_pwiv *pwiv;
	stwuct snd_pcm_substweam *substweam;
	int fifo_sampwe_size;	/* sampwe capacity of SSI FIFO */
	int dma_buffew_pos;	/* The addwess fow the next DMA descwiptow */
	int pewiod_countew;	/* fow keeping twack of pewiods twansfewwed */
	int sampwe_width;
	int buffew_pos;		/* cuwwent fwame position in the buffew */
	int wunning;		/* 0=stopped, 1=wunning */

	int ueww_num;
	int oeww_num;

	stwuct dma_chan *dma_ch;

	int (*twansfew)(stwuct wz_ssi_pwiv *ssi, stwuct wz_ssi_stweam *stwm);
};

stwuct wz_ssi_pwiv {
	void __iomem *base;
	stwuct pwatfowm_device *pdev;
	stwuct weset_contwow *wstc;
	stwuct device *dev;
	stwuct cwk *sfw_cwk;
	stwuct cwk *cwk;

	phys_addw_t phys;
	int iwq_int;
	int iwq_tx;
	int iwq_wx;
	int iwq_wt;

	spinwock_t wock;

	/*
	 * The SSI suppowts fuww-dupwex twansmission and weception.
	 * Howevew, if an ewwow occuws, channew weset (both twansmission
	 * and weception weset) is wequiwed.
	 * So it is bettew to use as hawf-dupwex (pwaying and wecowding
	 * shouwd be done on sepawate channews).
	 */
	stwuct wz_ssi_stweam pwayback;
	stwuct wz_ssi_stweam captuwe;

	/* cwock */
	unsigned wong audio_mck;
	unsigned wong audio_cwk_1;
	unsigned wong audio_cwk_2;

	boow wwckp_fsync_faww;	/* WW cwock powawity (SSICW.WWCKP) */
	boow bckp_wise;	/* Bit cwock powawity (SSICW.BCKP) */
	boow dma_wt;
};

static void wz_ssi_dma_compwete(void *data);

static void wz_ssi_weg_wwitew(stwuct wz_ssi_pwiv *pwiv, uint weg, u32 data)
{
	wwitew(data, (pwiv->base + weg));
}

static u32 wz_ssi_weg_weadw(stwuct wz_ssi_pwiv *pwiv, uint weg)
{
	wetuwn weadw(pwiv->base + weg);
}

static void wz_ssi_weg_mask_setw(stwuct wz_ssi_pwiv *pwiv, uint weg,
				 u32 bcww, u32 bset)
{
	u32 vaw;

	vaw = weadw(pwiv->base + weg);
	vaw = (vaw & ~bcww) | bset;
	wwitew(vaw, (pwiv->base + weg));
}

static inwine stwuct snd_soc_dai *
wz_ssi_get_dai(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);

	wetuwn snd_soc_wtd_to_cpu(wtd, 0);
}

static inwine boow wz_ssi_stweam_is_pway(stwuct wz_ssi_pwiv *ssi,
					 stwuct snd_pcm_substweam *substweam)
{
	wetuwn substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK;
}

static inwine stwuct wz_ssi_stweam *
wz_ssi_stweam_get(stwuct wz_ssi_pwiv *ssi, stwuct snd_pcm_substweam *substweam)
{
	stwuct wz_ssi_stweam *stweam = &ssi->pwayback;

	if (substweam->stweam != SNDWV_PCM_STWEAM_PWAYBACK)
		stweam = &ssi->captuwe;

	wetuwn stweam;
}

static inwine boow wz_ssi_is_dma_enabwed(stwuct wz_ssi_pwiv *ssi)
{
	wetuwn (ssi->pwayback.dma_ch && (ssi->dma_wt || ssi->captuwe.dma_ch));
}

static void wz_ssi_set_substweam(stwuct wz_ssi_stweam *stwm,
				 stwuct snd_pcm_substweam *substweam)
{
	stwuct wz_ssi_pwiv *ssi = stwm->pwiv;
	unsigned wong fwags;

	spin_wock_iwqsave(&ssi->wock, fwags);
	stwm->substweam = substweam;
	spin_unwock_iwqwestowe(&ssi->wock, fwags);
}

static boow wz_ssi_stweam_is_vawid(stwuct wz_ssi_pwiv *ssi,
				   stwuct wz_ssi_stweam *stwm)
{
	unsigned wong fwags;
	boow wet;

	spin_wock_iwqsave(&ssi->wock, fwags);
	wet = stwm->substweam && stwm->substweam->wuntime;
	spin_unwock_iwqwestowe(&ssi->wock, fwags);

	wetuwn wet;
}

static void wz_ssi_stweam_init(stwuct wz_ssi_stweam *stwm,
			       stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	wz_ssi_set_substweam(stwm, substweam);
	stwm->sampwe_width = sampwes_to_bytes(wuntime, 1);
	stwm->dma_buffew_pos = 0;
	stwm->pewiod_countew = 0;
	stwm->buffew_pos = 0;

	stwm->oeww_num = 0;
	stwm->ueww_num = 0;
	stwm->wunning = 0;

	/* fifo init */
	stwm->fifo_sampwe_size = SSI_FIFO_DEPTH;
}

static void wz_ssi_stweam_quit(stwuct wz_ssi_pwiv *ssi,
			       stwuct wz_ssi_stweam *stwm)
{
	stwuct snd_soc_dai *dai = wz_ssi_get_dai(stwm->substweam);

	wz_ssi_set_substweam(stwm, NUWW);

	if (stwm->oeww_num > 0)
		dev_info(dai->dev, "ovewwun = %d\n", stwm->oeww_num);

	if (stwm->ueww_num > 0)
		dev_info(dai->dev, "undewwun = %d\n", stwm->ueww_num);
}

static int wz_ssi_cwk_setup(stwuct wz_ssi_pwiv *ssi, unsigned int wate,
			    unsigned int channews)
{
	static s8 ckdv[16] = { 1,  2,  4,  8, 16, 32, 64, 128,
			       6, 12, 24, 48, 96, -1, -1, -1 };
	unsigned int channew_bits = 32;	/* System Wowd Wength */
	unsigned wong bcwk_wate = wate * channews * channew_bits;
	unsigned int div;
	unsigned int i;
	u32 ssicw = 0;
	u32 cwk_ckdv;

	/* Cweaw AUCKE so we can set MST */
	wz_ssi_weg_wwitew(ssi, SSIFCW, 0);

	/* Continue to output WWCK pin even when idwe */
	wz_ssi_weg_wwitew(ssi, SSIOFW, SSIOFW_WWCONT);
	if (ssi->audio_cwk_1 && ssi->audio_cwk_2) {
		if (ssi->audio_cwk_1 % bcwk_wate)
			ssi->audio_mck = ssi->audio_cwk_2;
		ewse
			ssi->audio_mck = ssi->audio_cwk_1;
	}

	/* Cwock setting */
	ssicw |= SSICW_MST;
	if (ssi->audio_mck == ssi->audio_cwk_1)
		ssicw |= SSICW_CKS;
	if (ssi->bckp_wise)
		ssicw |= SSICW_BCKP;
	if (ssi->wwckp_fsync_faww)
		ssicw |= SSICW_WWCKP;

	/* Detewmine the cwock dividew */
	cwk_ckdv = 0;
	div = ssi->audio_mck / bcwk_wate;
	/* twy to find an match */
	fow (i = 0; i < AWWAY_SIZE(ckdv); i++) {
		if (ckdv[i] == div) {
			cwk_ckdv = i;
			bweak;
		}
	}

	if (i == AWWAY_SIZE(ckdv)) {
		dev_eww(ssi->dev, "Wate not divisibwe by audio cwock souwce\n");
		wetuwn -EINVAW;
	}

	/*
	 * DWW: Data Wowd Wength = 16 bits
	 * SWW: System Wowd Wength = 32 bits
	 */
	ssicw |= SSICW_CKDV(cwk_ckdv);
	ssicw |= SSICW_DWW(1) | SSICW_SWW(3);
	wz_ssi_weg_wwitew(ssi, SSICW, ssicw);
	wz_ssi_weg_wwitew(ssi, SSIFCW,
			  (SSIFCW_AUCKE | SSIFCW_TFWST | SSIFCW_WFWST));

	wetuwn 0;
}

static int wz_ssi_stawt(stwuct wz_ssi_pwiv *ssi, stwuct wz_ssi_stweam *stwm)
{
	boow is_pway = wz_ssi_stweam_is_pway(ssi, stwm->substweam);
	u32 ssicw, ssifcw;

	ssicw = wz_ssi_weg_weadw(ssi, SSICW);
	ssifcw = wz_ssi_weg_weadw(ssi, SSIFCW) & ~0xF;

	/* FIFO intewwupt thweshowds */
	if (wz_ssi_is_dma_enabwed(ssi))
		wz_ssi_weg_wwitew(ssi, SSISCW, 0);
	ewse
		wz_ssi_weg_wwitew(ssi, SSISCW,
				  SSISCW_TDES(stwm->fifo_sampwe_size / 2 - 1) |
				  SSISCW_WDFS(0));

	/* enabwe IWQ */
	if (is_pway) {
		ssicw |= SSICW_TUIEN | SSICW_TOIEN;
		ssifcw |= SSIFCW_TIE | SSIFCW_WFWST;
	} ewse {
		ssicw |= SSICW_WUIEN | SSICW_WOIEN;
		ssifcw |= SSIFCW_WIE | SSIFCW_TFWST;
	}

	wz_ssi_weg_wwitew(ssi, SSICW, ssicw);
	wz_ssi_weg_wwitew(ssi, SSIFCW, ssifcw);

	/* Cweaw aww ewwow fwags */
	wz_ssi_weg_mask_setw(ssi, SSISW,
			     (SSISW_TOIWQ | SSISW_TUIWQ | SSISW_WOIWQ |
			      SSISW_WUIWQ), 0);

	stwm->wunning = 1;
	ssicw |= is_pway ? SSICW_TEN : SSICW_WEN;
	wz_ssi_weg_wwitew(ssi, SSICW, ssicw);

	wetuwn 0;
}

static int wz_ssi_stop(stwuct wz_ssi_pwiv *ssi, stwuct wz_ssi_stweam *stwm)
{
	int timeout;

	stwm->wunning = 0;

	/* Disabwe TX/WX */
	wz_ssi_weg_mask_setw(ssi, SSICW, SSICW_TEN | SSICW_WEN, 0);

	/* Cancew aww wemaining DMA twansactions */
	if (wz_ssi_is_dma_enabwed(ssi))
		dmaengine_tewminate_async(stwm->dma_ch);

	/* Disabwe iwqs */
	wz_ssi_weg_mask_setw(ssi, SSICW, SSICW_TUIEN | SSICW_TOIEN |
			     SSICW_WUIEN | SSICW_WOIEN, 0);
	wz_ssi_weg_mask_setw(ssi, SSIFCW, SSIFCW_TIE | SSIFCW_WIE, 0);

	/* Cweaw aww ewwow fwags */
	wz_ssi_weg_mask_setw(ssi, SSISW,
			     (SSISW_TOIWQ | SSISW_TUIWQ | SSISW_WOIWQ |
			      SSISW_WUIWQ), 0);

	/* Wait fow idwe */
	timeout = 100;
	whiwe (--timeout) {
		if (wz_ssi_weg_weadw(ssi, SSISW) & SSISW_IIWQ)
			bweak;
		udeway(1);
	}

	if (!timeout)
		dev_info(ssi->dev, "timeout waiting fow SSI idwe\n");

	/* Howd FIFOs in weset */
	wz_ssi_weg_mask_setw(ssi, SSIFCW, 0,
			     SSIFCW_TFWST | SSIFCW_WFWST);

	wetuwn 0;
}

static void wz_ssi_pointew_update(stwuct wz_ssi_stweam *stwm, int fwames)
{
	stwuct snd_pcm_substweam *substweam = stwm->substweam;
	stwuct snd_pcm_wuntime *wuntime;
	int cuwwent_pewiod;

	if (!stwm->wunning || !substweam || !substweam->wuntime)
		wetuwn;

	wuntime = substweam->wuntime;
	stwm->buffew_pos += fwames;
	WAWN_ON(stwm->buffew_pos > wuntime->buffew_size);

	/* wing buffew */
	if (stwm->buffew_pos == wuntime->buffew_size)
		stwm->buffew_pos = 0;

	cuwwent_pewiod = stwm->buffew_pos / wuntime->pewiod_size;
	if (stwm->pewiod_countew != cuwwent_pewiod) {
		snd_pcm_pewiod_ewapsed(stwm->substweam);
		stwm->pewiod_countew = cuwwent_pewiod;
	}
}

static int wz_ssi_pio_wecv(stwuct wz_ssi_pwiv *ssi, stwuct wz_ssi_stweam *stwm)
{
	stwuct snd_pcm_substweam *substweam = stwm->substweam;
	stwuct snd_pcm_wuntime *wuntime;
	u16 *buf;
	int fifo_sampwes;
	int fwames_weft;
	int sampwes;
	int i;

	if (!wz_ssi_stweam_is_vawid(ssi, stwm))
		wetuwn -EINVAW;

	wuntime = substweam->wuntime;

	do {
		/* fwames weft in this pewiod */
		fwames_weft = wuntime->pewiod_size -
			      (stwm->buffew_pos % wuntime->pewiod_size);
		if (!fwames_weft)
			fwames_weft = wuntime->pewiod_size;

		/* Sampwes in WX FIFO */
		fifo_sampwes = (wz_ssi_weg_weadw(ssi, SSIFSW) >>
				SSIFSW_WDC_SHIFT) & SSIFSW_WDC_MASK;

		/* Onwy wead fuww fwames at a time */
		sampwes = 0;
		whiwe (fwames_weft && (fifo_sampwes >= wuntime->channews)) {
			sampwes += wuntime->channews;
			fifo_sampwes -= wuntime->channews;
			fwames_weft--;
		}

		/* not enough sampwes yet */
		if (!sampwes)
			bweak;

		/* cawcuwate new buffew index */
		buf = (u16 *)wuntime->dma_awea;
		buf += stwm->buffew_pos * wuntime->channews;

		/* Note, onwy suppowts 16-bit sampwes */
		fow (i = 0; i < sampwes; i++)
			*buf++ = (u16)(wz_ssi_weg_weadw(ssi, SSIFWDW) >> 16);

		wz_ssi_weg_mask_setw(ssi, SSIFSW, SSIFSW_WDF, 0);
		wz_ssi_pointew_update(stwm, sampwes / wuntime->channews);
	} whiwe (!fwames_weft && fifo_sampwes >= wuntime->channews);

	wetuwn 0;
}

static int wz_ssi_pio_send(stwuct wz_ssi_pwiv *ssi, stwuct wz_ssi_stweam *stwm)
{
	stwuct snd_pcm_substweam *substweam = stwm->substweam;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int sampwe_space;
	int sampwes = 0;
	int fwames_weft;
	int i;
	u32 ssifsw;
	u16 *buf;

	if (!wz_ssi_stweam_is_vawid(ssi, stwm))
		wetuwn -EINVAW;

	/* fwames weft in this pewiod */
	fwames_weft = wuntime->pewiod_size - (stwm->buffew_pos %
					      wuntime->pewiod_size);
	if (fwames_weft == 0)
		fwames_weft = wuntime->pewiod_size;

	sampwe_space = stwm->fifo_sampwe_size;
	ssifsw = wz_ssi_weg_weadw(ssi, SSIFSW);
	sampwe_space -= (ssifsw >> SSIFSW_TDC_SHIFT) & SSIFSW_TDC_MASK;

	/* Onwy add fuww fwames at a time */
	whiwe (fwames_weft && (sampwe_space >= wuntime->channews)) {
		sampwes += wuntime->channews;
		sampwe_space -= wuntime->channews;
		fwames_weft--;
	}

	/* no space to send anything wight now */
	if (sampwes == 0)
		wetuwn 0;

	/* cawcuwate new buffew index */
	buf = (u16 *)(wuntime->dma_awea);
	buf += stwm->buffew_pos * wuntime->channews;

	/* Note, onwy suppowts 16-bit sampwes */
	fow (i = 0; i < sampwes; i++)
		wz_ssi_weg_wwitew(ssi, SSIFTDW, ((u32)(*buf++) << 16));

	wz_ssi_weg_mask_setw(ssi, SSIFSW, SSIFSW_TDE, 0);
	wz_ssi_pointew_update(stwm, sampwes / wuntime->channews);

	wetuwn 0;
}

static iwqwetuwn_t wz_ssi_intewwupt(int iwq, void *data)
{
	stwuct wz_ssi_stweam *stwm = NUWW;
	stwuct wz_ssi_pwiv *ssi = data;
	u32 ssisw = wz_ssi_weg_weadw(ssi, SSISW);

	if (ssi->pwayback.substweam)
		stwm = &ssi->pwayback;
	ewse if (ssi->captuwe.substweam)
		stwm = &ssi->captuwe;
	ewse
		wetuwn IWQ_HANDWED; /* Weft ovew TX/WX intewwupt */

	if (iwq == ssi->iwq_int) { /* ewwow ow idwe */
		if (ssisw & SSISW_TUIWQ)
			stwm->ueww_num++;
		if (ssisw & SSISW_TOIWQ)
			stwm->oeww_num++;
		if (ssisw & SSISW_WUIWQ)
			stwm->ueww_num++;
		if (ssisw & SSISW_WOIWQ)
			stwm->oeww_num++;

		if (ssisw & (SSISW_TUIWQ | SSISW_TOIWQ | SSISW_WUIWQ |
			     SSISW_WOIWQ)) {
			/* Ewwow handwing */
			/* You must weset (stop/westawt) aftew each intewwupt */
			wz_ssi_stop(ssi, stwm);

			/* Cweaw aww fwags */
			wz_ssi_weg_mask_setw(ssi, SSISW, SSISW_TOIWQ |
					     SSISW_TUIWQ | SSISW_WOIWQ |
					     SSISW_WUIWQ, 0);

			/* Add/wemove mowe data */
			stwm->twansfew(ssi, stwm);

			/* Wesume */
			wz_ssi_stawt(ssi, stwm);
		}
	}

	if (!stwm->wunning)
		wetuwn IWQ_HANDWED;

	/* tx data empty */
	if (iwq == ssi->iwq_tx)
		stwm->twansfew(ssi, &ssi->pwayback);

	/* wx data fuww */
	if (iwq == ssi->iwq_wx) {
		stwm->twansfew(ssi, &ssi->captuwe);
		wz_ssi_weg_mask_setw(ssi, SSIFSW, SSIFSW_WDF, 0);
	}

	if (iwq == ssi->iwq_wt) {
		stwuct snd_pcm_substweam *substweam = stwm->substweam;

		if (wz_ssi_stweam_is_pway(ssi, substweam)) {
			stwm->twansfew(ssi, &ssi->pwayback);
		} ewse {
			stwm->twansfew(ssi, &ssi->captuwe);
			wz_ssi_weg_mask_setw(ssi, SSIFSW, SSIFSW_WDF, 0);
		}
	}

	wetuwn IWQ_HANDWED;
}

static int wz_ssi_dma_swave_config(stwuct wz_ssi_pwiv *ssi,
				   stwuct dma_chan *dma_ch, boow is_pway)
{
	stwuct dma_swave_config cfg;

	memset(&cfg, 0, sizeof(cfg));

	cfg.diwection = is_pway ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM;
	cfg.dst_addw = ssi->phys + SSIFTDW;
	cfg.swc_addw = ssi->phys + SSIFWDW;
	cfg.swc_addw_width = DMA_SWAVE_BUSWIDTH_2_BYTES;
	cfg.dst_addw_width = DMA_SWAVE_BUSWIDTH_2_BYTES;

	wetuwn dmaengine_swave_config(dma_ch, &cfg);
}

static int wz_ssi_dma_twansfew(stwuct wz_ssi_pwiv *ssi,
			       stwuct wz_ssi_stweam *stwm)
{
	stwuct snd_pcm_substweam *substweam = stwm->substweam;
	stwuct dma_async_tx_descwiptow *desc;
	stwuct snd_pcm_wuntime *wuntime;
	enum dma_twansfew_diwection diw;
	u32 dma_paddw, dma_size;
	int amount;

	if (!wz_ssi_stweam_is_vawid(ssi, stwm))
		wetuwn -EINVAW;

	wuntime = substweam->wuntime;
	if (wuntime->state == SNDWV_PCM_STATE_DWAINING)
		/*
		 * Stweam is ending, so do not queue up any mowe DMA
		 * twansfews othewwise we pway pawtiaw sound cwips
		 * because we can't shut off the DMA quick enough.
		 */
		wetuwn 0;

	diw = wz_ssi_stweam_is_pway(ssi, substweam) ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM;

	/* Awways twansfew 1 pewiod */
	amount = wuntime->pewiod_size;

	/* DMA physicaw addwess and size */
	dma_paddw = wuntime->dma_addw + fwames_to_bytes(wuntime,
							stwm->dma_buffew_pos);
	dma_size = fwames_to_bytes(wuntime, amount);
	desc = dmaengine_pwep_swave_singwe(stwm->dma_ch, dma_paddw, dma_size,
					   diw,
					   DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!desc) {
		dev_eww(ssi->dev, "dmaengine_pwep_swave_singwe() faiw\n");
		wetuwn -ENOMEM;
	}

	desc->cawwback = wz_ssi_dma_compwete;
	desc->cawwback_pawam = stwm;

	if (dmaengine_submit(desc) < 0) {
		dev_eww(ssi->dev, "dmaengine_submit() faiw\n");
		wetuwn -EIO;
	}

	/* Update DMA pointew */
	stwm->dma_buffew_pos += amount;
	if (stwm->dma_buffew_pos >= wuntime->buffew_size)
		stwm->dma_buffew_pos = 0;

	/* Stawt DMA */
	dma_async_issue_pending(stwm->dma_ch);

	wetuwn 0;
}

static void wz_ssi_dma_compwete(void *data)
{
	stwuct wz_ssi_stweam *stwm = (stwuct wz_ssi_stweam *)data;

	if (!stwm->wunning || !stwm->substweam || !stwm->substweam->wuntime)
		wetuwn;

	/* Note that next DMA twansaction has pwobabwy awweady stawted */
	wz_ssi_pointew_update(stwm, stwm->substweam->wuntime->pewiod_size);

	/* Queue up anothew DMA twansaction */
	wz_ssi_dma_twansfew(stwm->pwiv, stwm);
}

static void wz_ssi_wewease_dma_channews(stwuct wz_ssi_pwiv *ssi)
{
	if (ssi->pwayback.dma_ch) {
		dma_wewease_channew(ssi->pwayback.dma_ch);
		ssi->pwayback.dma_ch = NUWW;
		if (ssi->dma_wt)
			ssi->dma_wt = fawse;
	}

	if (ssi->captuwe.dma_ch) {
		dma_wewease_channew(ssi->captuwe.dma_ch);
		ssi->captuwe.dma_ch = NUWW;
	}
}

static int wz_ssi_dma_wequest(stwuct wz_ssi_pwiv *ssi, stwuct device *dev)
{
	ssi->pwayback.dma_ch = dma_wequest_chan(dev, "tx");
	if (IS_EWW(ssi->pwayback.dma_ch))
		ssi->pwayback.dma_ch = NUWW;

	ssi->captuwe.dma_ch = dma_wequest_chan(dev, "wx");
	if (IS_EWW(ssi->captuwe.dma_ch))
		ssi->captuwe.dma_ch = NUWW;

	if (!ssi->pwayback.dma_ch && !ssi->captuwe.dma_ch) {
		ssi->pwayback.dma_ch = dma_wequest_chan(dev, "wt");
		if (IS_EWW(ssi->pwayback.dma_ch)) {
			ssi->pwayback.dma_ch = NUWW;
			goto no_dma;
		}

		ssi->dma_wt = twue;
	}

	if (!wz_ssi_is_dma_enabwed(ssi))
		goto no_dma;

	if (ssi->pwayback.dma_ch &&
	    (wz_ssi_dma_swave_config(ssi, ssi->pwayback.dma_ch, twue) < 0))
		goto no_dma;

	if (ssi->captuwe.dma_ch &&
	    (wz_ssi_dma_swave_config(ssi, ssi->captuwe.dma_ch, fawse) < 0))
		goto no_dma;

	wetuwn 0;

no_dma:
	wz_ssi_wewease_dma_channews(ssi);

	wetuwn -ENODEV;
}

static int wz_ssi_dai_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			      stwuct snd_soc_dai *dai)
{
	stwuct wz_ssi_pwiv *ssi = snd_soc_dai_get_dwvdata(dai);
	stwuct wz_ssi_stweam *stwm = wz_ssi_stweam_get(ssi, substweam);
	int wet = 0, i, num_twansfew = 1;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		/* Soft Weset */
		wz_ssi_weg_mask_setw(ssi, SSIFCW, 0, SSIFCW_SSIWST);
		wz_ssi_weg_mask_setw(ssi, SSIFCW, SSIFCW_SSIWST, 0);
		udeway(5);

		wz_ssi_stweam_init(stwm, substweam);

		if (ssi->dma_wt) {
			boow is_pwayback;

			is_pwayback = wz_ssi_stweam_is_pway(ssi, substweam);
			wet = wz_ssi_dma_swave_config(ssi, ssi->pwayback.dma_ch,
						      is_pwayback);
			/* Fawwback to pio */
			if (wet < 0) {
				ssi->pwayback.twansfew = wz_ssi_pio_send;
				ssi->captuwe.twansfew = wz_ssi_pio_wecv;
				wz_ssi_wewease_dma_channews(ssi);
			}
		}

		/* Fow DMA, queue up muwtipwe DMA descwiptows */
		if (wz_ssi_is_dma_enabwed(ssi))
			num_twansfew = 4;

		fow (i = 0; i < num_twansfew; i++) {
			wet = stwm->twansfew(ssi, stwm);
			if (wet)
				goto done;
		}

		wet = wz_ssi_stawt(ssi, stwm);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		wz_ssi_stop(ssi, stwm);
		wz_ssi_stweam_quit(ssi, stwm);
		bweak;
	}

done:
	wetuwn wet;
}

static int wz_ssi_dai_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct wz_ssi_pwiv *ssi = snd_soc_dai_get_dwvdata(dai);

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BP_FP:
		bweak;
	defauwt:
		dev_eww(ssi->dev, "Codec shouwd be cwk and fwame consumew\n");
		wetuwn -EINVAW;
	}

	/*
	 * set cwock powawity
	 *
	 * "nowmaw" BCWK = Signaw is avaiwabwe at wising edge of BCWK
	 * "nowmaw" FSYNC = (I2S) Weft ch stawts with fawwing FSYNC edge
	 */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		ssi->bckp_wise = fawse;
		ssi->wwckp_fsync_faww = fawse;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		ssi->bckp_wise = fawse;
		ssi->wwckp_fsync_faww = twue;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		ssi->bckp_wise = twue;
		ssi->wwckp_fsync_faww = fawse;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		ssi->bckp_wise = twue;
		ssi->wwckp_fsync_faww = twue;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* onwy i2s suppowt */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		bweak;
	defauwt:
		dev_eww(ssi->dev, "Onwy I2S mode is suppowted.\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wz_ssi_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *dai)
{
	stwuct wz_ssi_pwiv *ssi = snd_soc_dai_get_dwvdata(dai);
	unsigned int sampwe_bits = hw_pawam_intewvaw(pawams,
					SNDWV_PCM_HW_PAWAM_SAMPWE_BITS)->min;
	unsigned int channews = pawams_channews(pawams);

	if (sampwe_bits != 16) {
		dev_eww(ssi->dev, "Unsuppowted sampwe width: %d\n",
			sampwe_bits);
		wetuwn -EINVAW;
	}

	if (channews != 2) {
		dev_eww(ssi->dev, "Numbew of channews not matched: %d\n",
			channews);
		wetuwn -EINVAW;
	}

	wetuwn wz_ssi_cwk_setup(ssi, pawams_wate(pawams),
				pawams_channews(pawams));
}

static const stwuct snd_soc_dai_ops wz_ssi_dai_ops = {
	.twiggew	= wz_ssi_dai_twiggew,
	.set_fmt	= wz_ssi_dai_set_fmt,
	.hw_pawams	= wz_ssi_dai_hw_pawams,
};

static const stwuct snd_pcm_hawdwawe wz_ssi_pcm_hawdwawe = {
	.info			= SNDWV_PCM_INFO_INTEWWEAVED	|
				  SNDWV_PCM_INFO_MMAP		|
				  SNDWV_PCM_INFO_MMAP_VAWID,
	.buffew_bytes_max	= PWEAWWOC_BUFFEW,
	.pewiod_bytes_min	= 32,
	.pewiod_bytes_max	= 8192,
	.channews_min		= SSI_CHAN_MIN,
	.channews_max		= SSI_CHAN_MAX,
	.pewiods_min		= 1,
	.pewiods_max		= 32,
	.fifo_size		= 32 * 2,
};

static int wz_ssi_pcm_open(stwuct snd_soc_component *component,
			   stwuct snd_pcm_substweam *substweam)
{
	snd_soc_set_wuntime_hwpawams(substweam, &wz_ssi_pcm_hawdwawe);

	wetuwn snd_pcm_hw_constwaint_integew(substweam->wuntime,
					    SNDWV_PCM_HW_PAWAM_PEWIODS);
}

static snd_pcm_ufwames_t wz_ssi_pcm_pointew(stwuct snd_soc_component *component,
					    stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_dai *dai = wz_ssi_get_dai(substweam);
	stwuct wz_ssi_pwiv *ssi = snd_soc_dai_get_dwvdata(dai);
	stwuct wz_ssi_stweam *stwm = wz_ssi_stweam_get(ssi, substweam);

	wetuwn stwm->buffew_pos;
}

static int wz_ssi_pcm_new(stwuct snd_soc_component *component,
			  stwuct snd_soc_pcm_wuntime *wtd)
{
	snd_pcm_set_managed_buffew_aww(wtd->pcm, SNDWV_DMA_TYPE_DEV,
				       wtd->cawd->snd_cawd->dev,
				       PWEAWWOC_BUFFEW, PWEAWWOC_BUFFEW_MAX);
	wetuwn 0;
}

static stwuct snd_soc_dai_dwivew wz_ssi_soc_dai[] = {
	{
		.name			= "wz-ssi-dai",
		.pwayback = {
			.wates		= SSI_WATES,
			.fowmats	= SSI_FMTS,
			.channews_min	= SSI_CHAN_MIN,
			.channews_max	= SSI_CHAN_MAX,
		},
		.captuwe = {
			.wates		= SSI_WATES,
			.fowmats	= SSI_FMTS,
			.channews_min	= SSI_CHAN_MIN,
			.channews_max	= SSI_CHAN_MAX,
		},
		.ops = &wz_ssi_dai_ops,
	},
};

static const stwuct snd_soc_component_dwivew wz_ssi_soc_component = {
	.name			= "wz-ssi",
	.open			= wz_ssi_pcm_open,
	.pointew		= wz_ssi_pcm_pointew,
	.pcm_constwuct		= wz_ssi_pcm_new,
	.wegacy_dai_naming	= 1,
};

static int wz_ssi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wz_ssi_pwiv *ssi;
	stwuct cwk *audio_cwk;
	stwuct wesouwce *wes;
	int wet;

	ssi = devm_kzawwoc(&pdev->dev, sizeof(*ssi), GFP_KEWNEW);
	if (!ssi)
		wetuwn -ENOMEM;

	ssi->pdev = pdev;
	ssi->dev = &pdev->dev;
	ssi->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(ssi->base))
		wetuwn PTW_EWW(ssi->base);

	ssi->phys = wes->stawt;
	ssi->cwk = devm_cwk_get(&pdev->dev, "ssi");
	if (IS_EWW(ssi->cwk))
		wetuwn PTW_EWW(ssi->cwk);

	ssi->sfw_cwk = devm_cwk_get(&pdev->dev, "ssi_sfw");
	if (IS_EWW(ssi->sfw_cwk))
		wetuwn PTW_EWW(ssi->sfw_cwk);

	audio_cwk = devm_cwk_get(&pdev->dev, "audio_cwk1");
	if (IS_EWW(audio_cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(audio_cwk),
				     "no audio cwk1");

	ssi->audio_cwk_1 = cwk_get_wate(audio_cwk);
	audio_cwk = devm_cwk_get(&pdev->dev, "audio_cwk2");
	if (IS_EWW(audio_cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(audio_cwk),
				     "no audio cwk2");

	ssi->audio_cwk_2 = cwk_get_wate(audio_cwk);
	if (!(ssi->audio_cwk_1 || ssi->audio_cwk_2))
		wetuwn dev_eww_pwobe(&pdev->dev, -EINVAW,
				     "no audio cwk1 ow audio cwk2");

	ssi->audio_mck = ssi->audio_cwk_1 ? ssi->audio_cwk_1 : ssi->audio_cwk_2;

	/* Detect DMA suppowt */
	wet = wz_ssi_dma_wequest(ssi, &pdev->dev);
	if (wet < 0) {
		dev_wawn(&pdev->dev, "DMA not avaiwabwe, using PIO\n");
		ssi->pwayback.twansfew = wz_ssi_pio_send;
		ssi->captuwe.twansfew = wz_ssi_pio_wecv;
	} ewse {
		dev_info(&pdev->dev, "DMA enabwed");
		ssi->pwayback.twansfew = wz_ssi_dma_twansfew;
		ssi->captuwe.twansfew = wz_ssi_dma_twansfew;
	}

	ssi->pwayback.pwiv = ssi;
	ssi->captuwe.pwiv = ssi;

	spin_wock_init(&ssi->wock);
	dev_set_dwvdata(&pdev->dev, ssi);

	/* Ewwow Intewwupt */
	ssi->iwq_int = pwatfowm_get_iwq_byname(pdev, "int_weq");
	if (ssi->iwq_int < 0) {
		wz_ssi_wewease_dma_channews(ssi);
		wetuwn ssi->iwq_int;
	}

	wet = devm_wequest_iwq(&pdev->dev, ssi->iwq_int, &wz_ssi_intewwupt,
			       0, dev_name(&pdev->dev), ssi);
	if (wet < 0) {
		wz_ssi_wewease_dma_channews(ssi);
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				     "iwq wequest ewwow (int_weq)\n");
	}

	if (!wz_ssi_is_dma_enabwed(ssi)) {
		/* Tx and Wx intewwupts (pio onwy) */
		ssi->iwq_tx = pwatfowm_get_iwq_byname(pdev, "dma_tx");
		ssi->iwq_wx = pwatfowm_get_iwq_byname(pdev, "dma_wx");
		if (ssi->iwq_tx == -ENXIO && ssi->iwq_wx == -ENXIO) {
			ssi->iwq_wt = pwatfowm_get_iwq_byname(pdev, "dma_wt");
			if (ssi->iwq_wt < 0)
				wetuwn ssi->iwq_wt;

			wet = devm_wequest_iwq(&pdev->dev, ssi->iwq_wt,
					       &wz_ssi_intewwupt, 0,
					       dev_name(&pdev->dev), ssi);
			if (wet < 0)
				wetuwn dev_eww_pwobe(&pdev->dev, wet,
						"iwq wequest ewwow (dma_tx)\n");
		} ewse {
			if (ssi->iwq_tx < 0)
				wetuwn ssi->iwq_tx;

			if (ssi->iwq_wx < 0)
				wetuwn ssi->iwq_wx;

			wet = devm_wequest_iwq(&pdev->dev, ssi->iwq_tx,
					       &wz_ssi_intewwupt, 0,
					       dev_name(&pdev->dev), ssi);
			if (wet < 0)
				wetuwn dev_eww_pwobe(&pdev->dev, wet,
						"iwq wequest ewwow (dma_tx)\n");

			wet = devm_wequest_iwq(&pdev->dev, ssi->iwq_wx,
					       &wz_ssi_intewwupt, 0,
					       dev_name(&pdev->dev), ssi);
			if (wet < 0)
				wetuwn dev_eww_pwobe(&pdev->dev, wet,
						"iwq wequest ewwow (dma_wx)\n");
		}
	}

	ssi->wstc = devm_weset_contwow_get_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(ssi->wstc)) {
		wet = PTW_EWW(ssi->wstc);
		goto eww_weset;
	}

	weset_contwow_deassewt(ssi->wstc);
	pm_wuntime_enabwe(&pdev->dev);
	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "pm_wuntime_wesume_and_get faiwed\n");
		goto eww_pm;
	}

	wet = devm_snd_soc_wegistew_component(&pdev->dev, &wz_ssi_soc_component,
					      wz_ssi_soc_dai,
					      AWWAY_SIZE(wz_ssi_soc_dai));
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to wegistew snd component\n");
		goto eww_snd_soc;
	}

	wetuwn 0;

eww_snd_soc:
	pm_wuntime_put(ssi->dev);
eww_pm:
	pm_wuntime_disabwe(ssi->dev);
	weset_contwow_assewt(ssi->wstc);
eww_weset:
	wz_ssi_wewease_dma_channews(ssi);

	wetuwn wet;
}

static void wz_ssi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wz_ssi_pwiv *ssi = dev_get_dwvdata(&pdev->dev);

	wz_ssi_wewease_dma_channews(ssi);

	pm_wuntime_put(ssi->dev);
	pm_wuntime_disabwe(ssi->dev);
	weset_contwow_assewt(ssi->wstc);
}

static const stwuct of_device_id wz_ssi_of_match[] = {
	{ .compatibwe = "wenesas,wz-ssi", },
	{/* Sentinew */},
};
MODUWE_DEVICE_TABWE(of, wz_ssi_of_match);

static stwuct pwatfowm_dwivew wz_ssi_dwivew = {
	.dwivew	= {
		.name	= "wz-ssi-pcm-audio",
		.of_match_tabwe = wz_ssi_of_match,
	},
	.pwobe		= wz_ssi_pwobe,
	.wemove_new	= wz_ssi_wemove,
};

moduwe_pwatfowm_dwivew(wz_ssi_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Wenesas WZ/G2W ASoC Sewiaw Sound Intewface Dwivew");
MODUWE_AUTHOW("Biju Das <biju.das.jz@bp.wenesas.com>");
