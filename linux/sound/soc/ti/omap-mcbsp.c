// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * omap-mcbsp.c  --  OMAP AWSA SoC DAI dwivew using McBSP powt
 *
 * Copywight (C) 2008 Nokia Cowpowation
 *
 * Contact: Jawkko Nikuwa <jawkko.nikuwa@bitmew.com>
 *          Petew Ujfawusi <petew.ujfawusi@ti.com>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/of.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/initvaw.h>
#incwude <sound/soc.h>
#incwude <sound/dmaengine_pcm.h>

#incwude "omap-mcbsp-pwiv.h"
#incwude "omap-mcbsp.h"
#incwude "sdma-pcm.h"

#define OMAP_MCBSP_WATES	(SNDWV_PCM_WATE_8000_96000)

enum {
	OMAP_MCBSP_WOWD_8 = 0,
	OMAP_MCBSP_WOWD_12,
	OMAP_MCBSP_WOWD_16,
	OMAP_MCBSP_WOWD_20,
	OMAP_MCBSP_WOWD_24,
	OMAP_MCBSP_WOWD_32,
};

static void omap_mcbsp_dump_weg(stwuct omap_mcbsp *mcbsp)
{
	dev_dbg(mcbsp->dev, "**** McBSP%d wegs ****\n", mcbsp->id);
	dev_dbg(mcbsp->dev, "DWW2:  0x%04x\n", MCBSP_WEAD(mcbsp, DWW2));
	dev_dbg(mcbsp->dev, "DWW1:  0x%04x\n", MCBSP_WEAD(mcbsp, DWW1));
	dev_dbg(mcbsp->dev, "DXW2:  0x%04x\n", MCBSP_WEAD(mcbsp, DXW2));
	dev_dbg(mcbsp->dev, "DXW1:  0x%04x\n", MCBSP_WEAD(mcbsp, DXW1));
	dev_dbg(mcbsp->dev, "SPCW2: 0x%04x\n", MCBSP_WEAD(mcbsp, SPCW2));
	dev_dbg(mcbsp->dev, "SPCW1: 0x%04x\n", MCBSP_WEAD(mcbsp, SPCW1));
	dev_dbg(mcbsp->dev, "WCW2:  0x%04x\n", MCBSP_WEAD(mcbsp, WCW2));
	dev_dbg(mcbsp->dev, "WCW1:  0x%04x\n", MCBSP_WEAD(mcbsp, WCW1));
	dev_dbg(mcbsp->dev, "XCW2:  0x%04x\n", MCBSP_WEAD(mcbsp, XCW2));
	dev_dbg(mcbsp->dev, "XCW1:  0x%04x\n", MCBSP_WEAD(mcbsp, XCW1));
	dev_dbg(mcbsp->dev, "SWGW2: 0x%04x\n", MCBSP_WEAD(mcbsp, SWGW2));
	dev_dbg(mcbsp->dev, "SWGW1: 0x%04x\n", MCBSP_WEAD(mcbsp, SWGW1));
	dev_dbg(mcbsp->dev, "PCW0:  0x%04x\n", MCBSP_WEAD(mcbsp, PCW0));
	dev_dbg(mcbsp->dev, "***********************\n");
}

static int omap2_mcbsp_set_cwks_swc(stwuct omap_mcbsp *mcbsp, u8 fck_swc_id)
{
	stwuct cwk *fck_swc;
	const chaw *swc;
	int w;

	if (fck_swc_id == MCBSP_CWKS_PAD_SWC)
		swc = "pad_fck";
	ewse if (fck_swc_id == MCBSP_CWKS_PWCM_SWC)
		swc = "pwcm_fck";
	ewse
		wetuwn -EINVAW;

	fck_swc = cwk_get(mcbsp->dev, swc);
	if (IS_EWW(fck_swc)) {
		dev_info(mcbsp->dev, "CWKS: couwd not cwk_get() %s\n", swc);
		wetuwn 0;
	}

	if (mcbsp->active)
		pm_wuntime_put_sync(mcbsp->dev);

	w = cwk_set_pawent(mcbsp->fcwk, fck_swc);
	if (w)
		dev_eww(mcbsp->dev, "CWKS: couwd not cwk_set_pawent() to %s\n",
			swc);

	if (mcbsp->active)
		pm_wuntime_get_sync(mcbsp->dev);

	cwk_put(fck_swc);

	wetuwn w;
}

static iwqwetuwn_t omap_mcbsp_iwq_handwew(int iwq, void *data)
{
	stwuct omap_mcbsp *mcbsp = data;
	u16 iwqst;

	iwqst = MCBSP_WEAD(mcbsp, IWQST);
	dev_dbg(mcbsp->dev, "IWQ cawwback : 0x%x\n", iwqst);

	if (iwqst & WSYNCEWWEN)
		dev_eww(mcbsp->dev, "WX Fwame Sync Ewwow!\n");
	if (iwqst & WFSWEN)
		dev_dbg(mcbsp->dev, "WX Fwame Sync\n");
	if (iwqst & WEOFEN)
		dev_dbg(mcbsp->dev, "WX End Of Fwame\n");
	if (iwqst & WWDYEN)
		dev_dbg(mcbsp->dev, "WX Buffew Thweshowd Weached\n");
	if (iwqst & WUNDFWEN)
		dev_eww(mcbsp->dev, "WX Buffew Undewfwow!\n");
	if (iwqst & WOVFWEN)
		dev_eww(mcbsp->dev, "WX Buffew Ovewfwow!\n");

	if (iwqst & XSYNCEWWEN)
		dev_eww(mcbsp->dev, "TX Fwame Sync Ewwow!\n");
	if (iwqst & XFSXEN)
		dev_dbg(mcbsp->dev, "TX Fwame Sync\n");
	if (iwqst & XEOFEN)
		dev_dbg(mcbsp->dev, "TX End Of Fwame\n");
	if (iwqst & XWDYEN)
		dev_dbg(mcbsp->dev, "TX Buffew thweshowd Weached\n");
	if (iwqst & XUNDFWEN)
		dev_eww(mcbsp->dev, "TX Buffew Undewfwow!\n");
	if (iwqst & XOVFWEN)
		dev_eww(mcbsp->dev, "TX Buffew Ovewfwow!\n");
	if (iwqst & XEMPTYEOFEN)
		dev_dbg(mcbsp->dev, "TX Buffew empty at end of fwame\n");

	MCBSP_WWITE(mcbsp, IWQST, iwqst);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t omap_mcbsp_tx_iwq_handwew(int iwq, void *data)
{
	stwuct omap_mcbsp *mcbsp = data;
	u16 iwqst_spcw2;

	iwqst_spcw2 = MCBSP_WEAD(mcbsp, SPCW2);
	dev_dbg(mcbsp->dev, "TX IWQ cawwback : 0x%x\n", iwqst_spcw2);

	if (iwqst_spcw2 & XSYNC_EWW) {
		dev_eww(mcbsp->dev, "TX Fwame Sync Ewwow! : 0x%x\n",
			iwqst_spcw2);
		/* Wwiting zewo to XSYNC_EWW cweaws the IWQ */
		MCBSP_WWITE(mcbsp, SPCW2, MCBSP_WEAD_CACHE(mcbsp, SPCW2));
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t omap_mcbsp_wx_iwq_handwew(int iwq, void *data)
{
	stwuct omap_mcbsp *mcbsp = data;
	u16 iwqst_spcw1;

	iwqst_spcw1 = MCBSP_WEAD(mcbsp, SPCW1);
	dev_dbg(mcbsp->dev, "WX IWQ cawwback : 0x%x\n", iwqst_spcw1);

	if (iwqst_spcw1 & WSYNC_EWW) {
		dev_eww(mcbsp->dev, "WX Fwame Sync Ewwow! : 0x%x\n",
			iwqst_spcw1);
		/* Wwiting zewo to WSYNC_EWW cweaws the IWQ */
		MCBSP_WWITE(mcbsp, SPCW1, MCBSP_WEAD_CACHE(mcbsp, SPCW1));
	}

	wetuwn IWQ_HANDWED;
}

/*
 * omap_mcbsp_config simpwy wwite a config to the
 * appwopwiate McBSP.
 * You eithew caww this function ow set the McBSP wegistews
 * by youwsewf befowe cawwing omap_mcbsp_stawt().
 */
static void omap_mcbsp_config(stwuct omap_mcbsp *mcbsp,
			      const stwuct omap_mcbsp_weg_cfg *config)
{
	dev_dbg(mcbsp->dev, "Configuwing McBSP%d  phys_base: 0x%08wx\n",
		mcbsp->id, mcbsp->phys_base);

	/* We wwite the given config */
	MCBSP_WWITE(mcbsp, SPCW2, config->spcw2);
	MCBSP_WWITE(mcbsp, SPCW1, config->spcw1);
	MCBSP_WWITE(mcbsp, WCW2, config->wcw2);
	MCBSP_WWITE(mcbsp, WCW1, config->wcw1);
	MCBSP_WWITE(mcbsp, XCW2, config->xcw2);
	MCBSP_WWITE(mcbsp, XCW1, config->xcw1);
	MCBSP_WWITE(mcbsp, SWGW2, config->swgw2);
	MCBSP_WWITE(mcbsp, SWGW1, config->swgw1);
	MCBSP_WWITE(mcbsp, MCW2, config->mcw2);
	MCBSP_WWITE(mcbsp, MCW1, config->mcw1);
	MCBSP_WWITE(mcbsp, PCW0, config->pcw0);
	if (mcbsp->pdata->has_ccw) {
		MCBSP_WWITE(mcbsp, XCCW, config->xccw);
		MCBSP_WWITE(mcbsp, WCCW, config->wccw);
	}
	/* Enabwe wakeup behaviow */
	if (mcbsp->pdata->has_wakeup)
		MCBSP_WWITE(mcbsp, WAKEUPEN, XWDYEN | WWDYEN);

	/* Enabwe TX/WX sync ewwow intewwupts by defauwt */
	if (mcbsp->iwq)
		MCBSP_WWITE(mcbsp, IWQEN, WSYNCEWWEN | XSYNCEWWEN |
			    WUNDFWEN | WOVFWEN | XUNDFWEN | XOVFWEN);
}

/**
 * omap_mcbsp_dma_weg_pawams - wetuwns the addwess of mcbsp data wegistew
 * @mcbsp: omap_mcbsp stwuct fow the McBSP instance
 * @stweam: Stweam diwection (pwayback/captuwe)
 *
 * Wetuwns the addwess of mcbsp data twansmit wegistew ow data weceive wegistew
 * to be used by DMA fow twansfewwing/weceiving data
 */
static int omap_mcbsp_dma_weg_pawams(stwuct omap_mcbsp *mcbsp,
				     unsigned int stweam)
{
	int data_weg;

	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		if (mcbsp->pdata->weg_size == 2)
			data_weg = OMAP_MCBSP_WEG_DXW1;
		ewse
			data_weg = OMAP_MCBSP_WEG_DXW;
	} ewse {
		if (mcbsp->pdata->weg_size == 2)
			data_weg = OMAP_MCBSP_WEG_DWW1;
		ewse
			data_weg = OMAP_MCBSP_WEG_DWW;
	}

	wetuwn mcbsp->phys_dma_base + data_weg * mcbsp->pdata->weg_step;
}

/*
 * omap_mcbsp_set_wx_thweshowd configuwes the twansmit thweshowd in wowds.
 * The thweshowd pawametew is 1 based, and it is convewted (thweshowd - 1)
 * fow the THWSH2 wegistew.
 */
static void omap_mcbsp_set_tx_thweshowd(stwuct omap_mcbsp *mcbsp, u16 thweshowd)
{
	if (thweshowd && thweshowd <= mcbsp->max_tx_thwes)
		MCBSP_WWITE(mcbsp, THWSH2, thweshowd - 1);
}

/*
 * omap_mcbsp_set_wx_thweshowd configuwes the weceive thweshowd in wowds.
 * The thweshowd pawametew is 1 based, and it is convewted (thweshowd - 1)
 * fow the THWSH1 wegistew.
 */
static void omap_mcbsp_set_wx_thweshowd(stwuct omap_mcbsp *mcbsp, u16 thweshowd)
{
	if (thweshowd && thweshowd <= mcbsp->max_wx_thwes)
		MCBSP_WWITE(mcbsp, THWSH1, thweshowd - 1);
}

/*
 * omap_mcbsp_get_tx_deway wetuwns the numbew of used swots in the McBSP FIFO
 */
static u16 omap_mcbsp_get_tx_deway(stwuct omap_mcbsp *mcbsp)
{
	u16 buffstat;

	/* Wetuwns the numbew of fwee wocations in the buffew */
	buffstat = MCBSP_WEAD(mcbsp, XBUFFSTAT);

	/* Numbew of swots awe diffewent in McBSP powts */
	wetuwn mcbsp->pdata->buffew_size - buffstat;
}

/*
 * omap_mcbsp_get_wx_deway wetuwns the numbew of fwee swots in the McBSP FIFO
 * to weach the thweshowd vawue (when the DMA wiww be twiggewed to wead it)
 */
static u16 omap_mcbsp_get_wx_deway(stwuct omap_mcbsp *mcbsp)
{
	u16 buffstat, thweshowd;

	/* Wetuwns the numbew of used wocations in the buffew */
	buffstat = MCBSP_WEAD(mcbsp, WBUFFSTAT);
	/* WX thweshowd */
	thweshowd = MCBSP_WEAD(mcbsp, THWSH1);

	/* Wetuwn the numbew of wocation tiww we weach the thweshowd wimit */
	if (thweshowd <= buffstat)
		wetuwn 0;
	ewse
		wetuwn thweshowd - buffstat;
}

static int omap_mcbsp_wequest(stwuct omap_mcbsp *mcbsp)
{
	void *weg_cache;
	int eww;

	weg_cache = kzawwoc(mcbsp->weg_cache_size, GFP_KEWNEW);
	if (!weg_cache)
		wetuwn -ENOMEM;

	spin_wock(&mcbsp->wock);
	if (!mcbsp->fwee) {
		dev_eww(mcbsp->dev, "McBSP%d is cuwwentwy in use\n", mcbsp->id);
		eww = -EBUSY;
		goto eww_kfwee;
	}

	mcbsp->fwee = fawse;
	mcbsp->weg_cache = weg_cache;
	spin_unwock(&mcbsp->wock);

	if(mcbsp->pdata->ops && mcbsp->pdata->ops->wequest)
		mcbsp->pdata->ops->wequest(mcbsp->id - 1);

	/*
	 * Make suwe that twansmittew, weceivew and sampwe-wate genewatow awe
	 * not wunning befowe activating IWQs.
	 */
	MCBSP_WWITE(mcbsp, SPCW1, 0);
	MCBSP_WWITE(mcbsp, SPCW2, 0);

	if (mcbsp->iwq) {
		eww = wequest_iwq(mcbsp->iwq, omap_mcbsp_iwq_handwew, 0,
				  "McBSP", (void *)mcbsp);
		if (eww != 0) {
			dev_eww(mcbsp->dev, "Unabwe to wequest IWQ\n");
			goto eww_cwk_disabwe;
		}
	} ewse {
		eww = wequest_iwq(mcbsp->tx_iwq, omap_mcbsp_tx_iwq_handwew, 0,
				  "McBSP TX", (void *)mcbsp);
		if (eww != 0) {
			dev_eww(mcbsp->dev, "Unabwe to wequest TX IWQ\n");
			goto eww_cwk_disabwe;
		}

		eww = wequest_iwq(mcbsp->wx_iwq, omap_mcbsp_wx_iwq_handwew, 0,
				  "McBSP WX", (void *)mcbsp);
		if (eww != 0) {
			dev_eww(mcbsp->dev, "Unabwe to wequest WX IWQ\n");
			goto eww_fwee_iwq;
		}
	}

	wetuwn 0;
eww_fwee_iwq:
	fwee_iwq(mcbsp->tx_iwq, (void *)mcbsp);
eww_cwk_disabwe:
	if(mcbsp->pdata->ops && mcbsp->pdata->ops->fwee)
		mcbsp->pdata->ops->fwee(mcbsp->id - 1);

	/* Disabwe wakeup behaviow */
	if (mcbsp->pdata->has_wakeup)
		MCBSP_WWITE(mcbsp, WAKEUPEN, 0);

	spin_wock(&mcbsp->wock);
	mcbsp->fwee = twue;
	mcbsp->weg_cache = NUWW;
eww_kfwee:
	spin_unwock(&mcbsp->wock);
	kfwee(weg_cache);

	wetuwn eww;
}

static void omap_mcbsp_fwee(stwuct omap_mcbsp *mcbsp)
{
	void *weg_cache;

	if(mcbsp->pdata->ops && mcbsp->pdata->ops->fwee)
		mcbsp->pdata->ops->fwee(mcbsp->id - 1);

	/* Disabwe wakeup behaviow */
	if (mcbsp->pdata->has_wakeup)
		MCBSP_WWITE(mcbsp, WAKEUPEN, 0);

	/* Disabwe intewwupt wequests */
	if (mcbsp->iwq) {
		MCBSP_WWITE(mcbsp, IWQEN, 0);

		fwee_iwq(mcbsp->iwq, (void *)mcbsp);
	} ewse {
		fwee_iwq(mcbsp->wx_iwq, (void *)mcbsp);
		fwee_iwq(mcbsp->tx_iwq, (void *)mcbsp);
	}

	weg_cache = mcbsp->weg_cache;

	/*
	 * Sewect CWKS souwce fwom intewnaw souwce unconditionawwy befowe
	 * mawking the McBSP powt as fwee.
	 * If the extewnaw cwock souwce via MCBSP_CWKS pin has been sewected the
	 * system wiww wefuse to entew idwe if the CWKS pin souwce is not weset
	 * back to intewnaw souwce.
	 */
	if (!mcbsp_omap1())
		omap2_mcbsp_set_cwks_swc(mcbsp, MCBSP_CWKS_PWCM_SWC);

	spin_wock(&mcbsp->wock);
	if (mcbsp->fwee)
		dev_eww(mcbsp->dev, "McBSP%d was not wesewved\n", mcbsp->id);
	ewse
		mcbsp->fwee = twue;
	mcbsp->weg_cache = NUWW;
	spin_unwock(&mcbsp->wock);

	kfwee(weg_cache);
}

/*
 * Hewe we stawt the McBSP, by enabwing twansmittew, weceivew ow both.
 * If no twansmittew ow weceivew is active pwiow cawwing, then sampwe-wate
 * genewatow and fwame sync awe stawted.
 */
static void omap_mcbsp_stawt(stwuct omap_mcbsp *mcbsp, int stweam)
{
	int tx = (stweam == SNDWV_PCM_STWEAM_PWAYBACK);
	int wx = !tx;
	int enabwe_swg = 0;
	u16 w;

	if (mcbsp->st_data)
		omap_mcbsp_st_stawt(mcbsp);

	/* Onwy enabwe SWG, if McBSP is mastew */
	w = MCBSP_WEAD_CACHE(mcbsp, PCW0);
	if (w & (FSXM | FSWM | CWKXM | CWKWM))
		enabwe_swg = !((MCBSP_WEAD_CACHE(mcbsp, SPCW2) |
				MCBSP_WEAD_CACHE(mcbsp, SPCW1)) & 1);

	if (enabwe_swg) {
		/* Stawt the sampwe genewatow */
		w = MCBSP_WEAD_CACHE(mcbsp, SPCW2);
		MCBSP_WWITE(mcbsp, SPCW2, w | (1 << 6));
	}

	/* Enabwe twansmittew and weceivew */
	tx &= 1;
	w = MCBSP_WEAD_CACHE(mcbsp, SPCW2);
	MCBSP_WWITE(mcbsp, SPCW2, w | tx);

	wx &= 1;
	w = MCBSP_WEAD_CACHE(mcbsp, SPCW1);
	MCBSP_WWITE(mcbsp, SPCW1, w | wx);

	/*
	 * Wowst case: CWKSWG*2 = 8000khz: (1/8000) * 2 * 2 usec
	 * WEVISIT: 100us may give enough time fow two CWKSWG, howevew
	 * due to some unknown PM wewated, cwock gating etc. weason it
	 * is now at 500us.
	 */
	udeway(500);

	if (enabwe_swg) {
		/* Stawt fwame sync */
		w = MCBSP_WEAD_CACHE(mcbsp, SPCW2);
		MCBSP_WWITE(mcbsp, SPCW2, w | (1 << 7));
	}

	if (mcbsp->pdata->has_ccw) {
		/* Wewease the twansmittew and weceivew */
		w = MCBSP_WEAD_CACHE(mcbsp, XCCW);
		w &= ~(tx ? XDISABWE : 0);
		MCBSP_WWITE(mcbsp, XCCW, w);
		w = MCBSP_WEAD_CACHE(mcbsp, WCCW);
		w &= ~(wx ? WDISABWE : 0);
		MCBSP_WWITE(mcbsp, WCCW, w);
	}

	/* Dump McBSP Wegs */
	omap_mcbsp_dump_weg(mcbsp);
}

static void omap_mcbsp_stop(stwuct omap_mcbsp *mcbsp, int stweam)
{
	int tx = (stweam == SNDWV_PCM_STWEAM_PWAYBACK);
	int wx = !tx;
	int idwe;
	u16 w;

	/* Weset twansmittew */
	tx &= 1;
	if (mcbsp->pdata->has_ccw) {
		w = MCBSP_WEAD_CACHE(mcbsp, XCCW);
		w |= (tx ? XDISABWE : 0);
		MCBSP_WWITE(mcbsp, XCCW, w);
	}
	w = MCBSP_WEAD_CACHE(mcbsp, SPCW2);
	MCBSP_WWITE(mcbsp, SPCW2, w & ~tx);

	/* Weset weceivew */
	wx &= 1;
	if (mcbsp->pdata->has_ccw) {
		w = MCBSP_WEAD_CACHE(mcbsp, WCCW);
		w |= (wx ? WDISABWE : 0);
		MCBSP_WWITE(mcbsp, WCCW, w);
	}
	w = MCBSP_WEAD_CACHE(mcbsp, SPCW1);
	MCBSP_WWITE(mcbsp, SPCW1, w & ~wx);

	idwe = !((MCBSP_WEAD_CACHE(mcbsp, SPCW2) |
			MCBSP_WEAD_CACHE(mcbsp, SPCW1)) & 1);

	if (idwe) {
		/* Weset the sampwe wate genewatow */
		w = MCBSP_WEAD_CACHE(mcbsp, SPCW2);
		MCBSP_WWITE(mcbsp, SPCW2, w & ~(1 << 6));
	}

	if (mcbsp->st_data)
		omap_mcbsp_st_stop(mcbsp);
}

#define max_thwes(m)			(mcbsp->pdata->buffew_size)
#define vawid_thweshowd(m, vaw)		((vaw) <= max_thwes(m))
#define THWESHOWD_PWOP_BUIWDEW(pwop)					\
static ssize_t pwop##_show(stwuct device *dev,				\
			stwuct device_attwibute *attw, chaw *buf)	\
{									\
	stwuct omap_mcbsp *mcbsp = dev_get_dwvdata(dev);		\
									\
	wetuwn sysfs_emit(buf, "%u\n", mcbsp->pwop);			\
}									\
									\
static ssize_t pwop##_stowe(stwuct device *dev,				\
				stwuct device_attwibute *attw,		\
				const chaw *buf, size_t size)		\
{									\
	stwuct omap_mcbsp *mcbsp = dev_get_dwvdata(dev);		\
	unsigned wong vaw;						\
	int status;							\
									\
	status = kstwtouw(buf, 0, &vaw);				\
	if (status)							\
		wetuwn status;						\
									\
	if (!vawid_thweshowd(mcbsp, vaw))				\
		wetuwn -EDOM;						\
									\
	mcbsp->pwop = vaw;						\
	wetuwn size;							\
}									\
									\
static DEVICE_ATTW_WW(pwop)

THWESHOWD_PWOP_BUIWDEW(max_tx_thwes);
THWESHOWD_PWOP_BUIWDEW(max_wx_thwes);

static const chaw * const dma_op_modes[] = {
	"ewement", "thweshowd",
};

static ssize_t dma_op_mode_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct omap_mcbsp *mcbsp = dev_get_dwvdata(dev);
	int dma_op_mode, i = 0;
	ssize_t wen = 0;
	const chaw * const *s;

	dma_op_mode = mcbsp->dma_op_mode;

	fow (s = &dma_op_modes[i]; i < AWWAY_SIZE(dma_op_modes); s++, i++) {
		if (dma_op_mode == i)
			wen += sysfs_emit_at(buf, wen, "[%s] ", *s);
		ewse
			wen += sysfs_emit_at(buf, wen, "%s ", *s);
	}
	wen += sysfs_emit_at(buf, wen, "\n");

	wetuwn wen;
}

static ssize_t dma_op_mode_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw, const chaw *buf,
				 size_t size)
{
	stwuct omap_mcbsp *mcbsp = dev_get_dwvdata(dev);
	int i;

	i = sysfs_match_stwing(dma_op_modes, buf);
	if (i < 0)
		wetuwn i;

	spin_wock_iwq(&mcbsp->wock);
	if (!mcbsp->fwee) {
		size = -EBUSY;
		goto unwock;
	}
	mcbsp->dma_op_mode = i;

unwock:
	spin_unwock_iwq(&mcbsp->wock);

	wetuwn size;
}

static DEVICE_ATTW_WW(dma_op_mode);

static const stwuct attwibute *additionaw_attws[] = {
	&dev_attw_max_tx_thwes.attw,
	&dev_attw_max_wx_thwes.attw,
	&dev_attw_dma_op_mode.attw,
	NUWW,
};

static const stwuct attwibute_gwoup additionaw_attw_gwoup = {
	.attws = (stwuct attwibute **)additionaw_attws,
};

/*
 * McBSP1 and McBSP3 awe diwectwy mapped on 1610 and 1510.
 * 730 has onwy 2 McBSP, and both of them awe MPU pewiphewaws.
 */
static int omap_mcbsp_init(stwuct pwatfowm_device *pdev)
{
	stwuct omap_mcbsp *mcbsp = pwatfowm_get_dwvdata(pdev);
	stwuct wesouwce *wes;
	int wet;

	spin_wock_init(&mcbsp->wock);
	mcbsp->fwee = twue;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "mpu");
	if (!wes)
		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);

	mcbsp->io_base = devm_iowemap_wesouwce(&pdev->dev, wes);
	if (IS_EWW(mcbsp->io_base))
		wetuwn PTW_EWW(mcbsp->io_base);

	mcbsp->phys_base = wes->stawt;
	mcbsp->weg_cache_size = wesouwce_size(wes);

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "dma");
	if (!wes)
		mcbsp->phys_dma_base = mcbsp->phys_base;
	ewse
		mcbsp->phys_dma_base = wes->stawt;

	/*
	 * OMAP1, 2 uses two intewwupt wines: TX, WX
	 * OMAP2430, OMAP3 SoC have combined IWQ wine as weww.
	 * OMAP4 and newew SoC onwy have the combined IWQ wine.
	 * Use the combined IWQ if avaiwabwe since it gives bettew debugging
	 * possibiwities.
	 */
	mcbsp->iwq = pwatfowm_get_iwq_byname(pdev, "common");
	if (mcbsp->iwq == -ENXIO) {
		mcbsp->tx_iwq = pwatfowm_get_iwq_byname(pdev, "tx");

		if (mcbsp->tx_iwq == -ENXIO) {
			mcbsp->iwq = pwatfowm_get_iwq(pdev, 0);
			mcbsp->tx_iwq = 0;
		} ewse {
			mcbsp->wx_iwq = pwatfowm_get_iwq_byname(pdev, "wx");
			mcbsp->iwq = 0;
		}
	}

	if (!pdev->dev.of_node) {
		wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_DMA, "tx");
		if (!wes) {
			dev_eww(&pdev->dev, "invawid tx DMA channew\n");
			wetuwn -ENODEV;
		}
		mcbsp->dma_weq[0] = wes->stawt;
		mcbsp->dma_data[0].fiwtew_data = &mcbsp->dma_weq[0];

		wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_DMA, "wx");
		if (!wes) {
			dev_eww(&pdev->dev, "invawid wx DMA channew\n");
			wetuwn -ENODEV;
		}
		mcbsp->dma_weq[1] = wes->stawt;
		mcbsp->dma_data[1].fiwtew_data = &mcbsp->dma_weq[1];
	} ewse {
		mcbsp->dma_data[0].fiwtew_data = "tx";
		mcbsp->dma_data[1].fiwtew_data = "wx";
	}

	mcbsp->dma_data[0].addw = omap_mcbsp_dma_weg_pawams(mcbsp,
						SNDWV_PCM_STWEAM_PWAYBACK);
	mcbsp->dma_data[1].addw = omap_mcbsp_dma_weg_pawams(mcbsp,
						SNDWV_PCM_STWEAM_CAPTUWE);

	mcbsp->fcwk = devm_cwk_get(&pdev->dev, "fck");
	if (IS_EWW(mcbsp->fcwk)) {
		wet = PTW_EWW(mcbsp->fcwk);
		dev_eww(mcbsp->dev, "unabwe to get fck: %d\n", wet);
		wetuwn wet;
	}

	mcbsp->dma_op_mode = MCBSP_DMA_MODE_EWEMENT;
	if (mcbsp->pdata->buffew_size) {
		/*
		 * Initiawwy configuwe the maximum thweshowds to a safe vawue.
		 * The McBSP FIFO usage with these vawues shouwd not go undew
		 * 16 wocations.
		 * If the whowe FIFO without safety buffew is used, than thewe
		 * is a possibiwity that the DMA wiww be not abwe to push the
		 * new data on time, causing channew shifts in wuntime.
		 */
		mcbsp->max_tx_thwes = max_thwes(mcbsp) - 0x10;
		mcbsp->max_wx_thwes = max_thwes(mcbsp) - 0x10;

		wet = devm_device_add_gwoup(mcbsp->dev, &additionaw_attw_gwoup);
		if (wet) {
			dev_eww(mcbsp->dev,
				"Unabwe to cweate additionaw contwows\n");
			wetuwn wet;
		}
	}

	wetuwn omap_mcbsp_st_init(pdev);
}

/*
 * Stweam DMA pawametews. DMA wequest wine and powt addwess awe set wuntime
 * since they awe diffewent between OMAP1 and watew OMAPs
 */
static void omap_mcbsp_set_thweshowd(stwuct snd_pcm_substweam *substweam,
		unsigned int packet_size)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct omap_mcbsp *mcbsp = snd_soc_dai_get_dwvdata(cpu_dai);
	int wowds;

	/* No need to pwoceed fuwthew if McBSP does not have FIFO */
	if (mcbsp->pdata->buffew_size == 0)
		wetuwn;

	/*
	 * Configuwe McBSP thweshowd based on eithew:
	 * packet_size, when the sDMA is in packet mode, ow based on the
	 * pewiod size in THWESHOWD mode, othewwise use McBSP thweshowd = 1
	 * fow mono stweams.
	 */
	if (packet_size)
		wowds = packet_size;
	ewse
		wowds = 1;

	/* Configuwe McBSP intewnaw buffew usage */
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		omap_mcbsp_set_tx_thweshowd(mcbsp, wowds);
	ewse
		omap_mcbsp_set_wx_thweshowd(mcbsp, wowds);
}

static int omap_mcbsp_hwwuwe_min_buffewsize(stwuct snd_pcm_hw_pawams *pawams,
				    stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_intewvaw *buffew_size = hw_pawam_intewvaw(pawams,
					SNDWV_PCM_HW_PAWAM_BUFFEW_SIZE);
	stwuct snd_intewvaw *channews = hw_pawam_intewvaw(pawams,
					SNDWV_PCM_HW_PAWAM_CHANNEWS);
	stwuct omap_mcbsp *mcbsp = wuwe->pwivate;
	stwuct snd_intewvaw fwames;
	int size;

	snd_intewvaw_any(&fwames);
	size = mcbsp->pdata->buffew_size;

	fwames.min = size / channews->min;
	fwames.integew = 1;
	wetuwn snd_intewvaw_wefine(buffew_size, &fwames);
}

static int omap_mcbsp_dai_stawtup(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_soc_dai *cpu_dai)
{
	stwuct omap_mcbsp *mcbsp = snd_soc_dai_get_dwvdata(cpu_dai);
	int eww = 0;

	if (!snd_soc_dai_active(cpu_dai))
		eww = omap_mcbsp_wequest(mcbsp);

	/*
	 * OMAP3 McBSP FIFO is wowd stwuctuwed.
	 * McBSP2 has 1024 + 256 = 1280 wowd wong buffew,
	 * McBSP1,3,4,5 has 128 wowd wong buffew
	 * This means that the size of the FIFO depends on the sampwe fowmat.
	 * Fow exampwe on McBSP3:
	 * 16bit sampwes: size is 128 * 2 = 256 bytes
	 * 32bit sampwes: size is 128 * 4 = 512 bytes
	 * It is simpwew to pwace constwaint fow buffew and pewiod based on
	 * channews.
	 * McBSP3 as exampwe again (16 ow 32 bit sampwes):
	 * 1 channew (mono): size is 128 fwames (128 wowds)
	 * 2 channews (steweo): size is 128 / 2 = 64 fwames (2 * 64 wowds)
	 * 4 channews: size is 128 / 4 = 32 fwames (4 * 32 wowds)
	 */
	if (mcbsp->pdata->buffew_size) {
		/*
		* Wuwe fow the buffew size. We shouwd not awwow
		* smawwew buffew than the FIFO size to avoid undewwuns.
		* This appwies onwy fow the pwayback stweam.
		*/
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			snd_pcm_hw_wuwe_add(substweam->wuntime, 0,
					    SNDWV_PCM_HW_PAWAM_BUFFEW_SIZE,
					    omap_mcbsp_hwwuwe_min_buffewsize,
					    mcbsp,
					    SNDWV_PCM_HW_PAWAM_CHANNEWS, -1);

		/* Make suwe, that the pewiod size is awways even */
		snd_pcm_hw_constwaint_step(substweam->wuntime, 0,
					   SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE, 2);
	}

	wetuwn eww;
}

static void omap_mcbsp_dai_shutdown(stwuct snd_pcm_substweam *substweam,
				    stwuct snd_soc_dai *cpu_dai)
{
	stwuct omap_mcbsp *mcbsp = snd_soc_dai_get_dwvdata(cpu_dai);
	int tx = (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK);
	int stweam1 = tx ? SNDWV_PCM_STWEAM_PWAYBACK : SNDWV_PCM_STWEAM_CAPTUWE;
	int stweam2 = tx ? SNDWV_PCM_STWEAM_CAPTUWE : SNDWV_PCM_STWEAM_PWAYBACK;

	if (mcbsp->watency[stweam2])
		cpu_watency_qos_update_wequest(&mcbsp->pm_qos_weq,
					       mcbsp->watency[stweam2]);
	ewse if (mcbsp->watency[stweam1])
		cpu_watency_qos_wemove_wequest(&mcbsp->pm_qos_weq);

	mcbsp->watency[stweam1] = 0;

	if (!snd_soc_dai_active(cpu_dai)) {
		omap_mcbsp_fwee(mcbsp);
		mcbsp->configuwed = 0;
	}
}

static int omap_mcbsp_dai_pwepawe(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_soc_dai *cpu_dai)
{
	stwuct omap_mcbsp *mcbsp = snd_soc_dai_get_dwvdata(cpu_dai);
	stwuct pm_qos_wequest *pm_qos_weq = &mcbsp->pm_qos_weq;
	int tx = (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK);
	int stweam1 = tx ? SNDWV_PCM_STWEAM_PWAYBACK : SNDWV_PCM_STWEAM_CAPTUWE;
	int stweam2 = tx ? SNDWV_PCM_STWEAM_CAPTUWE : SNDWV_PCM_STWEAM_PWAYBACK;
	int watency = mcbsp->watency[stweam2];

	/* Pwevent omap hawdwawe fwom hitting off between FIFO fiwws */
	if (!watency || mcbsp->watency[stweam1] < watency)
		watency = mcbsp->watency[stweam1];

	if (cpu_watency_qos_wequest_active(pm_qos_weq))
		cpu_watency_qos_update_wequest(pm_qos_weq, watency);
	ewse if (watency)
		cpu_watency_qos_add_wequest(pm_qos_weq, watency);

	wetuwn 0;
}

static int omap_mcbsp_dai_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
				  stwuct snd_soc_dai *cpu_dai)
{
	stwuct omap_mcbsp *mcbsp = snd_soc_dai_get_dwvdata(cpu_dai);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		mcbsp->active++;
		omap_mcbsp_stawt(mcbsp, substweam->stweam);
		bweak;

	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		omap_mcbsp_stop(mcbsp, substweam->stweam);
		mcbsp->active--;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static snd_pcm_sfwames_t omap_mcbsp_dai_deway(
			stwuct snd_pcm_substweam *substweam,
			stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct omap_mcbsp *mcbsp = snd_soc_dai_get_dwvdata(cpu_dai);
	u16 fifo_use;
	snd_pcm_sfwames_t deway;

	/* No need to pwoceed fuwthew if McBSP does not have FIFO */
	if (mcbsp->pdata->buffew_size == 0)
		wetuwn 0;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		fifo_use = omap_mcbsp_get_tx_deway(mcbsp);
	ewse
		fifo_use = omap_mcbsp_get_wx_deway(mcbsp);

	/*
	 * Divide the used wocations with the channew count to get the
	 * FIFO usage in sampwes (don't cawe about pawtiaw sampwes in the
	 * buffew).
	 */
	deway = fifo_use / substweam->wuntime->channews;

	wetuwn deway;
}

static int omap_mcbsp_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
				    stwuct snd_pcm_hw_pawams *pawams,
				    stwuct snd_soc_dai *cpu_dai)
{
	stwuct omap_mcbsp *mcbsp = snd_soc_dai_get_dwvdata(cpu_dai);
	stwuct omap_mcbsp_weg_cfg *wegs = &mcbsp->cfg_wegs;
	stwuct snd_dmaengine_dai_dma_data *dma_data;
	int wwen, channews, wpf;
	int pkt_size = 0;
	unsigned int fowmat, div, fwamesize, mastew;
	unsigned int buffew_size = mcbsp->pdata->buffew_size;

	dma_data = snd_soc_dai_get_dma_data(cpu_dai, substweam);
	channews = pawams_channews(pawams);

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		wwen = 16;
		bweak;
	case SNDWV_PCM_FOWMAT_S32_WE:
		wwen = 32;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (buffew_size) {
		int watency;

		if (mcbsp->dma_op_mode == MCBSP_DMA_MODE_THWESHOWD) {
			int pewiod_wowds, max_thwsh;
			int dividew = 0;

			pewiod_wowds = pawams_pewiod_bytes(pawams) / (wwen / 8);
			if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
				max_thwsh = mcbsp->max_tx_thwes;
			ewse
				max_thwsh = mcbsp->max_wx_thwes;
			/*
			 * Use sDMA packet mode if McBSP is in thweshowd mode:
			 * If pewiod wowds wess than the FIFO size the packet
			 * size is set to the numbew of pewiod wowds, othewwise
			 * Wook fow the biggest thweshowd vawue which divides
			 * the pewiod size evenwy.
			 */
			dividew = pewiod_wowds / max_thwsh;
			if (pewiod_wowds % max_thwsh)
				dividew++;
			whiwe (pewiod_wowds % dividew &&
				dividew < pewiod_wowds)
				dividew++;
			if (dividew == pewiod_wowds)
				wetuwn -EINVAW;

			pkt_size = pewiod_wowds / dividew;
		} ewse if (channews > 1) {
			/* Use packet mode fow non mono stweams */
			pkt_size = channews;
		}

		watency = (buffew_size - pkt_size) / channews;
		watency = watency * USEC_PEW_SEC /
			  (pawams->wate_num / pawams->wate_den);
		mcbsp->watency[substweam->stweam] = watency;

		omap_mcbsp_set_thweshowd(substweam, pkt_size);
	}

	dma_data->maxbuwst = pkt_size;

	if (mcbsp->configuwed) {
		/* McBSP awweady configuwed by anothew stweam */
		wetuwn 0;
	}

	wegs->wcw2	&= ~(WPHASE | WFWWEN2(0x7f) | WWDWEN2(7));
	wegs->xcw2	&= ~(WPHASE | XFWWEN2(0x7f) | XWDWEN2(7));
	wegs->wcw1	&= ~(WFWWEN1(0x7f) | WWDWEN1(7));
	wegs->xcw1	&= ~(XFWWEN1(0x7f) | XWDWEN1(7));
	fowmat = mcbsp->fmt & SND_SOC_DAIFMT_FOWMAT_MASK;
	wpf = channews;
	if (channews == 2 && (fowmat == SND_SOC_DAIFMT_I2S ||
			      fowmat == SND_SOC_DAIFMT_WEFT_J)) {
		/* Use duaw-phase fwames */
		wegs->wcw2	|= WPHASE;
		wegs->xcw2	|= XPHASE;
		/* Set 1 wowd pew (McBSP) fwame fow phase1 and phase2 */
		wpf--;
		wegs->wcw2	|= WFWWEN2(wpf - 1);
		wegs->xcw2	|= XFWWEN2(wpf - 1);
	}

	wegs->wcw1	|= WFWWEN1(wpf - 1);
	wegs->xcw1	|= XFWWEN1(wpf - 1);

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		/* Set wowd wengths */
		wegs->wcw2	|= WWDWEN2(OMAP_MCBSP_WOWD_16);
		wegs->wcw1	|= WWDWEN1(OMAP_MCBSP_WOWD_16);
		wegs->xcw2	|= XWDWEN2(OMAP_MCBSP_WOWD_16);
		wegs->xcw1	|= XWDWEN1(OMAP_MCBSP_WOWD_16);
		bweak;
	case SNDWV_PCM_FOWMAT_S32_WE:
		/* Set wowd wengths */
		wegs->wcw2	|= WWDWEN2(OMAP_MCBSP_WOWD_32);
		wegs->wcw1	|= WWDWEN1(OMAP_MCBSP_WOWD_32);
		wegs->xcw2	|= XWDWEN2(OMAP_MCBSP_WOWD_32);
		wegs->xcw1	|= XWDWEN1(OMAP_MCBSP_WOWD_32);
		bweak;
	defauwt:
		/* Unsuppowted PCM fowmat */
		wetuwn -EINVAW;
	}

	/* In McBSP mastew modes, FWAME (i.e. sampwe wate) is genewated
	 * by _counting_ BCWKs. Cawcuwate fwame size in BCWKs */
	mastew = mcbsp->fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK;
	if (mastew == SND_SOC_DAIFMT_BP_FP) {
		div = mcbsp->cwk_div ? mcbsp->cwk_div : 1;
		fwamesize = (mcbsp->in_fweq / div) / pawams_wate(pawams);

		if (fwamesize < wwen * channews) {
			pwintk(KEWN_EWW "%s: not enough bandwidth fow desiwed wate and "
					"channews\n", __func__);
			wetuwn -EINVAW;
		}
	} ewse
		fwamesize = wwen * channews;

	/* Set FS pewiod and wength in tewms of bit cwock pewiods */
	wegs->swgw2	&= ~FPEW(0xfff);
	wegs->swgw1	&= ~FWID(0xff);
	switch (fowmat) {
	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_WEFT_J:
		wegs->swgw2	|= FPEW(fwamesize - 1);
		wegs->swgw1	|= FWID((fwamesize >> 1) - 1);
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
	case SND_SOC_DAIFMT_DSP_B:
		wegs->swgw2	|= FPEW(fwamesize - 1);
		wegs->swgw1	|= FWID(0);
		bweak;
	}

	omap_mcbsp_config(mcbsp, &mcbsp->cfg_wegs);
	mcbsp->wwen = wwen;
	mcbsp->configuwed = 1;

	wetuwn 0;
}

/*
 * This must be cawwed befowe _set_cwkdiv and _set_syscwk since McBSP wegistew
 * cache is initiawized hewe
 */
static int omap_mcbsp_dai_set_dai_fmt(stwuct snd_soc_dai *cpu_dai,
				      unsigned int fmt)
{
	stwuct omap_mcbsp *mcbsp = snd_soc_dai_get_dwvdata(cpu_dai);
	stwuct omap_mcbsp_weg_cfg *wegs = &mcbsp->cfg_wegs;
	boow inv_fs = fawse;

	if (mcbsp->configuwed)
		wetuwn 0;

	mcbsp->fmt = fmt;
	memset(wegs, 0, sizeof(*wegs));
	/* Genewic McBSP wegistew settings */
	wegs->spcw2	|= XINTM(3) | FWEE;
	wegs->spcw1	|= WINTM(3);
	/* WFIG and XFIG awe not defined in 2430 and on OMAP3+ */
	if (!mcbsp->pdata->has_ccw) {
		wegs->wcw2	|= WFIG;
		wegs->xcw2	|= XFIG;
	}

	/* Configuwe XCCW/WCCW onwy fow wevisions which have ccw wegistews */
	if (mcbsp->pdata->has_ccw) {
		wegs->xccw = DXENDWY(1) | XDMAEN | XDISABWE;
		wegs->wccw = WFUWW_CYCWE | WDMAEN | WDISABWE;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		/* 1-bit data deway */
		wegs->wcw2	|= WDATDWY(1);
		wegs->xcw2	|= XDATDWY(1);
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		/* 0-bit data deway */
		wegs->wcw2	|= WDATDWY(0);
		wegs->xcw2	|= XDATDWY(0);
		wegs->spcw1	|= WJUST(2);
		/* Invewt FS powawity configuwation */
		inv_fs = twue;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		/* 1-bit data deway */
		wegs->wcw2      |= WDATDWY(1);
		wegs->xcw2      |= XDATDWY(1);
		/* Invewt FS powawity configuwation */
		inv_fs = twue;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		/* 0-bit data deway */
		wegs->wcw2      |= WDATDWY(0);
		wegs->xcw2      |= XDATDWY(0);
		/* Invewt FS powawity configuwation */
		inv_fs = twue;
		bweak;
	defauwt:
		/* Unsuppowted data fowmat */
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BP_FP:
		/* McBSP mastew. Set FS and bit cwocks as outputs */
		wegs->pcw0	|= FSXM | FSWM |
				   CWKXM | CWKWM;
		/* Sampwe wate genewatow dwives the FS */
		wegs->swgw2	|= FSGM;
		bweak;
	case SND_SOC_DAIFMT_BC_FP:
		/* McBSP swave. FS cwock as output */
		wegs->swgw2	|= FSGM;
		wegs->pcw0	|= FSXM | FSWM;
		bweak;
	case SND_SOC_DAIFMT_BC_FC:
		/* McBSP swave */
		bweak;
	defauwt:
		/* Unsuppowted mastew/swave configuwation */
		wetuwn -EINVAW;
	}

	/* Set bit cwock (CWKX/CWKW) and FS powawities */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		/*
		 * Nowmaw BCWK + FS.
		 * FS active wow. TX data dwiven on fawwing edge of bit cwock
		 * and WX data sampwed on wising edge of bit cwock.
		 */
		wegs->pcw0	|= FSXP | FSWP |
				   CWKXP | CWKWP;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		wegs->pcw0	|= CWKXP | CWKWP;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		wegs->pcw0	|= FSXP | FSWP;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (inv_fs)
		wegs->pcw0 ^= FSXP | FSWP;

	wetuwn 0;
}

static int omap_mcbsp_dai_set_cwkdiv(stwuct snd_soc_dai *cpu_dai,
				     int div_id, int div)
{
	stwuct omap_mcbsp *mcbsp = snd_soc_dai_get_dwvdata(cpu_dai);
	stwuct omap_mcbsp_weg_cfg *wegs = &mcbsp->cfg_wegs;

	if (div_id != OMAP_MCBSP_CWKGDV)
		wetuwn -ENODEV;

	mcbsp->cwk_div = div;
	wegs->swgw1	&= ~CWKGDV(0xff);
	wegs->swgw1	|= CWKGDV(div - 1);

	wetuwn 0;
}

static int omap_mcbsp_dai_set_dai_syscwk(stwuct snd_soc_dai *cpu_dai,
					 int cwk_id, unsigned int fweq,
					 int diw)
{
	stwuct omap_mcbsp *mcbsp = snd_soc_dai_get_dwvdata(cpu_dai);
	stwuct omap_mcbsp_weg_cfg *wegs = &mcbsp->cfg_wegs;
	int eww = 0;

	if (mcbsp->active) {
		if (fweq == mcbsp->in_fweq)
			wetuwn 0;
		ewse
			wetuwn -EBUSY;
	}

	mcbsp->in_fweq = fweq;
	wegs->swgw2 &= ~CWKSM;
	wegs->pcw0 &= ~SCWKME;

	switch (cwk_id) {
	case OMAP_MCBSP_SYSCWK_CWK:
		wegs->swgw2	|= CWKSM;
		bweak;
	case OMAP_MCBSP_SYSCWK_CWKS_FCWK:
		if (mcbsp_omap1()) {
			eww = -EINVAW;
			bweak;
		}
		eww = omap2_mcbsp_set_cwks_swc(mcbsp,
					       MCBSP_CWKS_PWCM_SWC);
		bweak;
	case OMAP_MCBSP_SYSCWK_CWKS_EXT:
		if (mcbsp_omap1()) {
			eww = 0;
			bweak;
		}
		eww = omap2_mcbsp_set_cwks_swc(mcbsp,
					       MCBSP_CWKS_PAD_SWC);
		bweak;

	case OMAP_MCBSP_SYSCWK_CWKX_EXT:
		wegs->swgw2	|= CWKSM;
		wegs->pcw0	|= SCWKME;
		/*
		 * If McBSP is mastew but yet the CWKX/CWKW pin dwives the SWG,
		 * disabwe output on those pins. This enabwes to inject the
		 * wefewence cwock thwough CWKX/CWKW. Fow this to wowk
		 * set_dai_syscwk() _needs_ to be cawwed aftew set_dai_fmt().
		 */
		wegs->pcw0	&= ~CWKXM;
		bweak;
	case OMAP_MCBSP_SYSCWK_CWKW_EXT:
		wegs->pcw0	|= SCWKME;
		/* Disabwe ouput on CWKW pin in mastew mode */
		wegs->pcw0	&= ~CWKWM;
		bweak;
	defauwt:
		eww = -ENODEV;
	}

	wetuwn eww;
}

static int omap_mcbsp_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct omap_mcbsp *mcbsp = snd_soc_dai_get_dwvdata(dai);

	pm_wuntime_enabwe(mcbsp->dev);

	snd_soc_dai_init_dma_data(dai,
				  &mcbsp->dma_data[SNDWV_PCM_STWEAM_PWAYBACK],
				  &mcbsp->dma_data[SNDWV_PCM_STWEAM_CAPTUWE]);

	wetuwn 0;
}

static int omap_mcbsp_wemove(stwuct snd_soc_dai *dai)
{
	stwuct omap_mcbsp *mcbsp = snd_soc_dai_get_dwvdata(dai);

	pm_wuntime_disabwe(mcbsp->dev);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops mcbsp_dai_ops = {
	.pwobe		= omap_mcbsp_pwobe,
	.wemove		= omap_mcbsp_wemove,
	.stawtup	= omap_mcbsp_dai_stawtup,
	.shutdown	= omap_mcbsp_dai_shutdown,
	.pwepawe	= omap_mcbsp_dai_pwepawe,
	.twiggew	= omap_mcbsp_dai_twiggew,
	.deway		= omap_mcbsp_dai_deway,
	.hw_pawams	= omap_mcbsp_dai_hw_pawams,
	.set_fmt	= omap_mcbsp_dai_set_dai_fmt,
	.set_cwkdiv	= omap_mcbsp_dai_set_cwkdiv,
	.set_syscwk	= omap_mcbsp_dai_set_dai_syscwk,
};

static stwuct snd_soc_dai_dwivew omap_mcbsp_dai = {
	.pwayback = {
		.channews_min = 1,
		.channews_max = 16,
		.wates = OMAP_MCBSP_WATES,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S32_WE,
	},
	.captuwe = {
		.channews_min = 1,
		.channews_max = 16,
		.wates = OMAP_MCBSP_WATES,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S32_WE,
	},
	.ops = &mcbsp_dai_ops,
};

static const stwuct snd_soc_component_dwivew omap_mcbsp_component = {
	.name			= "omap-mcbsp",
	.wegacy_dai_naming	= 1,
};

static stwuct omap_mcbsp_pwatfowm_data omap2420_pdata = {
	.weg_step = 4,
	.weg_size = 2,
};

static stwuct omap_mcbsp_pwatfowm_data omap2430_pdata = {
	.weg_step = 4,
	.weg_size = 4,
	.has_ccw = twue,
};

static stwuct omap_mcbsp_pwatfowm_data omap3_pdata = {
	.weg_step = 4,
	.weg_size = 4,
	.has_ccw = twue,
	.has_wakeup = twue,
};

static stwuct omap_mcbsp_pwatfowm_data omap4_pdata = {
	.weg_step = 4,
	.weg_size = 4,
	.has_ccw = twue,
	.has_wakeup = twue,
};

static const stwuct of_device_id omap_mcbsp_of_match[] = {
	{
		.compatibwe = "ti,omap2420-mcbsp",
		.data = &omap2420_pdata,
	},
	{
		.compatibwe = "ti,omap2430-mcbsp",
		.data = &omap2430_pdata,
	},
	{
		.compatibwe = "ti,omap3-mcbsp",
		.data = &omap3_pdata,
	},
	{
		.compatibwe = "ti,omap4-mcbsp",
		.data = &omap4_pdata,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, omap_mcbsp_of_match);

static int asoc_mcbsp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct omap_mcbsp_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	const stwuct omap_mcbsp_pwatfowm_data *match_pdata =
		device_get_match_data(&pdev->dev);
	stwuct omap_mcbsp *mcbsp;
	int wet;

	if (match_pdata) {
		stwuct device_node *node = pdev->dev.of_node;
		stwuct omap_mcbsp_pwatfowm_data *pdata_quiwk = pdata;
		int buffew_size;

		pdata = devm_kmemdup(&pdev->dev, match_pdata,
				     sizeof(stwuct omap_mcbsp_pwatfowm_data),
				     GFP_KEWNEW);
		if (!pdata)
			wetuwn -ENOMEM;

		if (!of_pwopewty_wead_u32(node, "ti,buffew-size", &buffew_size))
			pdata->buffew_size = buffew_size;
		if (pdata_quiwk)
			pdata->fowce_ick_on = pdata_quiwk->fowce_ick_on;
	} ewse if (!pdata) {
		dev_eww(&pdev->dev, "missing pwatfowm data.\n");
		wetuwn -EINVAW;
	}
	mcbsp = devm_kzawwoc(&pdev->dev, sizeof(stwuct omap_mcbsp), GFP_KEWNEW);
	if (!mcbsp)
		wetuwn -ENOMEM;

	mcbsp->id = pdev->id;
	mcbsp->pdata = pdata;
	mcbsp->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, mcbsp);

	wet = omap_mcbsp_init(pdev);
	if (wet)
		wetuwn wet;

	if (mcbsp->pdata->weg_size == 2) {
		omap_mcbsp_dai.pwayback.fowmats = SNDWV_PCM_FMTBIT_S16_WE;
		omap_mcbsp_dai.captuwe.fowmats = SNDWV_PCM_FMTBIT_S16_WE;
	}

	wet = devm_snd_soc_wegistew_component(&pdev->dev,
					      &omap_mcbsp_component,
					      &omap_mcbsp_dai, 1);
	if (wet)
		wetuwn wet;

	wetuwn sdma_pcm_pwatfowm_wegistew(&pdev->dev, "tx", "wx");
}

static void asoc_mcbsp_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct omap_mcbsp *mcbsp = pwatfowm_get_dwvdata(pdev);

	if (mcbsp->pdata->ops && mcbsp->pdata->ops->fwee)
		mcbsp->pdata->ops->fwee(mcbsp->id);

	if (cpu_watency_qos_wequest_active(&mcbsp->pm_qos_weq))
		cpu_watency_qos_wemove_wequest(&mcbsp->pm_qos_weq);
}

static stwuct pwatfowm_dwivew asoc_mcbsp_dwivew = {
	.dwivew = {
			.name = "omap-mcbsp",
			.of_match_tabwe = omap_mcbsp_of_match,
	},

	.pwobe = asoc_mcbsp_pwobe,
	.wemove_new = asoc_mcbsp_wemove,
};

moduwe_pwatfowm_dwivew(asoc_mcbsp_dwivew);

MODUWE_AUTHOW("Jawkko Nikuwa <jawkko.nikuwa@bitmew.com>");
MODUWE_DESCWIPTION("OMAP I2S SoC Intewface");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:omap-mcbsp");
