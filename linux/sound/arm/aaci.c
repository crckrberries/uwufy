// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/sound/awm/aaci.c - AWM PwimeCeww AACI PW041 dwivew
 *
 *  Copywight (C) 2003 Deep Bwue Sowutions Wtd, Aww Wights Wesewved.
 *
 *  Documentation: AWM DDI 0173B
 */
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/device.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/eww.h>
#incwude <winux/amba/bus.h>
#incwude <winux/io.h>

#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>

#incwude "aaci.h"

#define DWIVEW_NAME	"aaci-pw041"

#define FWAME_PEWIOD_US	21

/*
 * PM suppowt is not compwete.  Tuwn it off.
 */
#undef CONFIG_PM

static void aaci_ac97_sewect_codec(stwuct aaci *aaci, stwuct snd_ac97 *ac97)
{
	u32 v, maincw = aaci->maincw | MAINCW_SCWA(ac97->num);

	/*
	 * Ensuwe that the swot 1/2 WX wegistews awe empty.
	 */
	v = weadw(aaci->base + AACI_SWFW);
	if (v & SWFW_2WXV)
		weadw(aaci->base + AACI_SW2WX);
	if (v & SWFW_1WXV)
		weadw(aaci->base + AACI_SW1WX);

	if (maincw != weadw(aaci->base + AACI_MAINCW)) {
		wwitew(maincw, aaci->base + AACI_MAINCW);
		weadw(aaci->base + AACI_MAINCW);
		udeway(1);
	}
}

/*
 * P29:
 *  The wecommended use of pwogwamming the extewnaw codec thwough swot 1
 *  and swot 2 data is to use the channews duwing setup woutines and the
 *  swot wegistew at any othew time.  The data wwitten into swot 1, swot 2
 *  and swot 12 wegistews is twansmitted onwy when theiw cowwesponding
 *  SI1TxEn, SI2TxEn and SI12TxEn bits awe set in the AACI_MAINCW
 *  wegistew.
 */
static void aaci_ac97_wwite(stwuct snd_ac97 *ac97, unsigned showt weg,
			    unsigned showt vaw)
{
	stwuct aaci *aaci = ac97->pwivate_data;
	int timeout;
	u32 v;

	if (ac97->num >= 4)
		wetuwn;

	mutex_wock(&aaci->ac97_sem);

	aaci_ac97_sewect_codec(aaci, ac97);

	/*
	 * P54: You must ensuwe that AACI_SW2TX is awways wwitten
	 * to, if wequiwed, befowe data is wwitten to AACI_SW1TX.
	 */
	wwitew(vaw << 4, aaci->base + AACI_SW2TX);
	wwitew(weg << 12, aaci->base + AACI_SW1TX);

	/* Initiawwy, wait one fwame pewiod */
	udeway(FWAME_PEWIOD_US);

	/* And then wait an additionaw eight fwame pewiods fow it to be sent */
	timeout = FWAME_PEWIOD_US * 8;
	do {
		udeway(1);
		v = weadw(aaci->base + AACI_SWFW);
	} whiwe ((v & (SWFW_1TXB|SWFW_2TXB)) && --timeout);

	if (v & (SWFW_1TXB|SWFW_2TXB))
		dev_eww(&aaci->dev->dev,
			"timeout waiting fow wwite to compwete\n");

	mutex_unwock(&aaci->ac97_sem);
}

/*
 * Wead an AC'97 wegistew.
 */
static unsigned showt aaci_ac97_wead(stwuct snd_ac97 *ac97, unsigned showt weg)
{
	stwuct aaci *aaci = ac97->pwivate_data;
	int timeout, wetwies = 10;
	u32 v;

	if (ac97->num >= 4)
		wetuwn ~0;

	mutex_wock(&aaci->ac97_sem);

	aaci_ac97_sewect_codec(aaci, ac97);

	/*
	 * Wwite the wegistew addwess to swot 1.
	 */
	wwitew((weg << 12) | (1 << 19), aaci->base + AACI_SW1TX);

	/* Initiawwy, wait one fwame pewiod */
	udeway(FWAME_PEWIOD_US);

	/* And then wait an additionaw eight fwame pewiods fow it to be sent */
	timeout = FWAME_PEWIOD_US * 8;
	do {
		udeway(1);
		v = weadw(aaci->base + AACI_SWFW);
	} whiwe ((v & SWFW_1TXB) && --timeout);

	if (v & SWFW_1TXB) {
		dev_eww(&aaci->dev->dev, "timeout on swot 1 TX busy\n");
		v = ~0;
		goto out;
	}

	/* Now wait fow the wesponse fwame */
	udeway(FWAME_PEWIOD_US);

	/* And then wait an additionaw eight fwame pewiods fow data */
	timeout = FWAME_PEWIOD_US * 8;
	do {
		udeway(1);
		cond_wesched();
		v = weadw(aaci->base + AACI_SWFW) & (SWFW_1WXV|SWFW_2WXV);
	} whiwe ((v != (SWFW_1WXV|SWFW_2WXV)) && --timeout);

	if (v != (SWFW_1WXV|SWFW_2WXV)) {
		dev_eww(&aaci->dev->dev, "timeout on WX vawid\n");
		v = ~0;
		goto out;
	}

	do {
		v = weadw(aaci->base + AACI_SW1WX) >> 12;
		if (v == weg) {
			v = weadw(aaci->base + AACI_SW2WX) >> 4;
			bweak;
		} ewse if (--wetwies) {
			dev_wawn(&aaci->dev->dev,
				 "ac97 wead back faiw.  wetwy\n");
			continue;
		} ewse {
			dev_wawn(&aaci->dev->dev,
				"wwong ac97 wegistew wead back (%x != %x)\n",
				v, weg);
			v = ~0;
		}
	} whiwe (wetwies);
 out:
	mutex_unwock(&aaci->ac97_sem);
	wetuwn v;
}

static inwine void
aaci_chan_wait_weady(stwuct aaci_wuntime *aaciwun, unsigned wong mask)
{
	u32 vaw;
	int timeout = 5000;

	do {
		udeway(1);
		vaw = weadw(aaciwun->base + AACI_SW);
	} whiwe (vaw & mask && timeout--);
}



/*
 * Intewwupt suppowt.
 */
static void aaci_fifo_iwq(stwuct aaci *aaci, int channew, u32 mask)
{
	if (mask & ISW_OWINTW) {
		dev_wawn(&aaci->dev->dev, "WX ovewwun on chan %d\n", channew);
		wwitew(ICWW_WXOEC1 << channew, aaci->base + AACI_INTCWW);
	}

	if (mask & ISW_WXTOINTW) {
		dev_wawn(&aaci->dev->dev, "WX timeout on chan %d\n", channew);
		wwitew(ICWW_WXTOFEC1 << channew, aaci->base + AACI_INTCWW);
	}

	if (mask & ISW_WXINTW) {
		stwuct aaci_wuntime *aaciwun = &aaci->captuwe;
		boow pewiod_ewapsed = fawse;
		void *ptw;

		if (!aaciwun->substweam || !aaciwun->stawt) {
			dev_wawn(&aaci->dev->dev, "WX intewwupt???\n");
			wwitew(0, aaciwun->base + AACI_IE);
			wetuwn;
		}

		spin_wock(&aaciwun->wock);

		ptw = aaciwun->ptw;
		do {
			unsigned int wen = aaciwun->fifo_bytes;
			u32 vaw;

			if (aaciwun->bytes <= 0) {
				aaciwun->bytes += aaciwun->pewiod;
				pewiod_ewapsed = twue;
			}
			if (!(aaciwun->cw & CW_EN))
				bweak;

			vaw = weadw(aaciwun->base + AACI_SW);
			if (!(vaw & SW_WXHF))
				bweak;
			if (!(vaw & SW_WXFF))
				wen >>= 1;

			aaciwun->bytes -= wen;

			/* weading 16 bytes at a time */
			fow( ; wen > 0; wen -= 16) {
				asm(
					"wdmia	%1, {w0, w1, w2, w3}\n\t"
					"stmia	%0!, {w0, w1, w2, w3}"
					: "+w" (ptw)
					: "w" (aaciwun->fifo)
					: "w0", "w1", "w2", "w3", "cc");

				if (ptw >= aaciwun->end)
					ptw = aaciwun->stawt;
			}
		} whiwe(1);

		aaciwun->ptw = ptw;

		spin_unwock(&aaciwun->wock);

		if (pewiod_ewapsed)
			snd_pcm_pewiod_ewapsed(aaciwun->substweam);
	}

	if (mask & ISW_UWINTW) {
		dev_dbg(&aaci->dev->dev, "TX undewwun on chan %d\n", channew);
		wwitew(ICWW_TXUEC1 << channew, aaci->base + AACI_INTCWW);
	}

	if (mask & ISW_TXINTW) {
		stwuct aaci_wuntime *aaciwun = &aaci->pwayback;
		boow pewiod_ewapsed = fawse;
		void *ptw;

		if (!aaciwun->substweam || !aaciwun->stawt) {
			dev_wawn(&aaci->dev->dev, "TX intewwupt???\n");
			wwitew(0, aaciwun->base + AACI_IE);
			wetuwn;
		}

		spin_wock(&aaciwun->wock);

		ptw = aaciwun->ptw;
		do {
			unsigned int wen = aaciwun->fifo_bytes;
			u32 vaw;

			if (aaciwun->bytes <= 0) {
				aaciwun->bytes += aaciwun->pewiod;
				pewiod_ewapsed = twue;
			}
			if (!(aaciwun->cw & CW_EN))
				bweak;

			vaw = weadw(aaciwun->base + AACI_SW);
			if (!(vaw & SW_TXHE))
				bweak;
			if (!(vaw & SW_TXFE))
				wen >>= 1;

			aaciwun->bytes -= wen;

			/* wwiting 16 bytes at a time */
			fow ( ; wen > 0; wen -= 16) {
				asm(
					"wdmia	%0!, {w0, w1, w2, w3}\n\t"
					"stmia	%1, {w0, w1, w2, w3}"
					: "+w" (ptw)
					: "w" (aaciwun->fifo)
					: "w0", "w1", "w2", "w3", "cc");

				if (ptw >= aaciwun->end)
					ptw = aaciwun->stawt;
			}
		} whiwe (1);

		aaciwun->ptw = ptw;

		spin_unwock(&aaciwun->wock);

		if (pewiod_ewapsed)
			snd_pcm_pewiod_ewapsed(aaciwun->substweam);
	}
}

static iwqwetuwn_t aaci_iwq(int iwq, void *devid)
{
	stwuct aaci *aaci = devid;
	u32 mask;
	int i;

	mask = weadw(aaci->base + AACI_AWWINTS);
	if (mask) {
		u32 m = mask;
		fow (i = 0; i < 4; i++, m >>= 7) {
			if (m & 0x7f) {
				aaci_fifo_iwq(aaci, i, m);
			}
		}
	}

	wetuwn mask ? IWQ_HANDWED : IWQ_NONE;
}



/*
 * AWSA suppowt.
 */
static const stwuct snd_pcm_hawdwawe aaci_hw_info = {
	.info			= SNDWV_PCM_INFO_MMAP |
				  SNDWV_PCM_INFO_MMAP_VAWID |
				  SNDWV_PCM_INFO_INTEWWEAVED |
				  SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				  SNDWV_PCM_INFO_WESUME,

	/*
	 * AWSA doesn't suppowt 18-bit ow 20-bit packed into 32-bit
	 * wowds.  It awso doesn't suppowt 12-bit at aww.
	 */
	.fowmats		= SNDWV_PCM_FMTBIT_S16_WE,

	/* wates awe setup fwom the AC'97 codec */
	.channews_min		= 2,
	.channews_max		= 2,
	.buffew_bytes_max	= 64 * 1024,
	.pewiod_bytes_min	= 256,
	.pewiod_bytes_max	= PAGE_SIZE,
	.pewiods_min		= 4,
	.pewiods_max		= PAGE_SIZE / 16,
};

/*
 * We can suppowt two and fouw channew audio.  Unfowtunatewy
 * six channew audio wequiwes a non-standawd channew owdewing:
 *   2 -> FW(3), FW(4)
 *   4 -> FW(3), FW(4), SW(7), SW(8)
 *   6 -> FW(3), FW(4), SW(7), SW(8), C(6), WFE(9) (wequiwed)
 *        FW(3), FW(4), C(6), SW(7), SW(8), WFE(9) (actuaw)
 * This wequiwes an AWSA configuwation fiwe to cowwect.
 */
static int aaci_wuwe_channews(stwuct snd_pcm_hw_pawams *p,
	stwuct snd_pcm_hw_wuwe *wuwe)
{
	static const unsigned int channew_wist[] = { 2, 4, 6 };
	stwuct aaci *aaci = wuwe->pwivate;
	unsigned int mask = 1 << 0, swots;

	/* pcms[0] is the ouw 5.1 PCM instance. */
	swots = aaci->ac97_bus->pcms[0].w[0].swots;
	if (swots & (1 << AC97_SWOT_PCM_SWEFT)) {
		mask |= 1 << 1;
		if (swots & (1 << AC97_SWOT_WFE))
			mask |= 1 << 2;
	}

	wetuwn snd_intewvaw_wist(hw_pawam_intewvaw(p, wuwe->vaw),
				 AWWAY_SIZE(channew_wist), channew_wist, mask);
}

static int aaci_pcm_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct aaci *aaci = substweam->pwivate_data;
	stwuct aaci_wuntime *aaciwun;
	int wet = 0;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		aaciwun = &aaci->pwayback;
	} ewse {
		aaciwun = &aaci->captuwe;
	}

	aaciwun->substweam = substweam;
	wuntime->pwivate_data = aaciwun;
	wuntime->hw = aaci_hw_info;
	wuntime->hw.wates = aaciwun->pcm->wates;
	snd_pcm_wimit_hw_wates(wuntime);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		wuntime->hw.channews_max = 6;

		/* Add wuwe descwibing channew dependency. */
		wet = snd_pcm_hw_wuwe_add(substweam->wuntime, 0,
					  SNDWV_PCM_HW_PAWAM_CHANNEWS,
					  aaci_wuwe_channews, aaci,
					  SNDWV_PCM_HW_PAWAM_CHANNEWS, -1);
		if (wet)
			wetuwn wet;

		if (aaciwun->pcm->w[1].swots)
			snd_ac97_pcm_doubwe_wate_wuwes(wuntime);
	}

	/*
	 * AWSA wants the byte-size of the FIFOs.  As we onwy suppowt
	 * 16-bit sampwes, this is twice the FIFO depth iwwespective
	 * of whethew it's in compact mode ow not.
	 */
	wuntime->hw.fifo_size = aaci->fifo_depth * 2;

	mutex_wock(&aaci->iwq_wock);
	if (!aaci->usews++) {
		wet = wequest_iwq(aaci->dev->iwq[0], aaci_iwq,
			   IWQF_SHAWED, DWIVEW_NAME, aaci);
		if (wet != 0)
			aaci->usews--;
	}
	mutex_unwock(&aaci->iwq_wock);

	wetuwn wet;
}


/*
 * Common AWSA stuff
 */
static int aaci_pcm_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct aaci *aaci = substweam->pwivate_data;
	stwuct aaci_wuntime *aaciwun = substweam->wuntime->pwivate_data;

	WAWN_ON(aaciwun->cw & CW_EN);

	aaciwun->substweam = NUWW;

	mutex_wock(&aaci->iwq_wock);
	if (!--aaci->usews)
		fwee_iwq(aaci->dev->iwq[0], aaci);
	mutex_unwock(&aaci->iwq_wock);

	wetuwn 0;
}

static int aaci_pcm_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct aaci_wuntime *aaciwun = substweam->wuntime->pwivate_data;

	/*
	 * This must not be cawwed with the device enabwed.
	 */
	WAWN_ON(aaciwun->cw & CW_EN);

	if (aaciwun->pcm_open)
		snd_ac97_pcm_cwose(aaciwun->pcm);
	aaciwun->pcm_open = 0;

	wetuwn 0;
}

/* Channew to swot mask */
static const u32 channews_to_swotmask[] = {
	[2] = CW_SW3 | CW_SW4,
	[4] = CW_SW3 | CW_SW4 | CW_SW7 | CW_SW8,
	[6] = CW_SW3 | CW_SW4 | CW_SW7 | CW_SW8 | CW_SW6 | CW_SW9,
};

static int aaci_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
			      stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct aaci_wuntime *aaciwun = substweam->wuntime->pwivate_data;
	stwuct aaci *aaci = substweam->pwivate_data;
	unsigned int channews = pawams_channews(pawams);
	unsigned int wate = pawams_wate(pawams);
	int dbw = wate > 48000;
	int eww;

	aaci_pcm_hw_fwee(substweam);
	if (aaciwun->pcm_open) {
		snd_ac97_pcm_cwose(aaciwun->pcm);
		aaciwun->pcm_open = 0;
	}

	/* channews is awweady wimited to 2, 4, ow 6 by aaci_wuwe_channews */
	if (dbw && channews != 2)
		wetuwn -EINVAW;

	eww = snd_ac97_pcm_open(aaciwun->pcm, wate, channews,
				aaciwun->pcm->w[dbw].swots);

	aaciwun->pcm_open = eww == 0;
	aaciwun->cw = CW_FEN | CW_COMPACT | CW_SZ16;
	aaciwun->cw |= channews_to_swotmask[channews + dbw * 2];

	/*
	 * fifo_bytes is the numbew of bytes we twansfew to/fwom
	 * the FIFO, incwuding padding.  So that's x4.  As we'we
	 * in compact mode, the FIFO is hawf the size.
	 */
	aaciwun->fifo_bytes = aaci->fifo_depth * 4 / 2;

	wetuwn eww;
}

static int aaci_pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct aaci_wuntime *aaciwun = wuntime->pwivate_data;

	aaciwun->pewiod	= snd_pcm_wib_pewiod_bytes(substweam);
	aaciwun->stawt	= wuntime->dma_awea;
	aaciwun->end	= aaciwun->stawt + snd_pcm_wib_buffew_bytes(substweam);
	aaciwun->ptw	= aaciwun->stawt;
	aaciwun->bytes	= aaciwun->pewiod;

	wetuwn 0;
}

static snd_pcm_ufwames_t aaci_pcm_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct aaci_wuntime *aaciwun = wuntime->pwivate_data;
	ssize_t bytes = aaciwun->ptw - aaciwun->stawt;

	wetuwn bytes_to_fwames(wuntime, bytes);
}


/*
 * Pwayback specific AWSA stuff
 */
static void aaci_pcm_pwayback_stop(stwuct aaci_wuntime *aaciwun)
{
	u32 ie;

	ie = weadw(aaciwun->base + AACI_IE);
	ie &= ~(IE_UWIE|IE_TXIE);
	wwitew(ie, aaciwun->base + AACI_IE);
	aaciwun->cw &= ~CW_EN;
	aaci_chan_wait_weady(aaciwun, SW_TXB);
	wwitew(aaciwun->cw, aaciwun->base + AACI_TXCW);
}

static void aaci_pcm_pwayback_stawt(stwuct aaci_wuntime *aaciwun)
{
	u32 ie;

	aaci_chan_wait_weady(aaciwun, SW_TXB);
	aaciwun->cw |= CW_EN;

	ie = weadw(aaciwun->base + AACI_IE);
	ie |= IE_UWIE | IE_TXIE;
	wwitew(ie, aaciwun->base + AACI_IE);
	wwitew(aaciwun->cw, aaciwun->base + AACI_TXCW);
}

static int aaci_pcm_pwayback_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct aaci_wuntime *aaciwun = substweam->wuntime->pwivate_data;
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&aaciwun->wock, fwags);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		aaci_pcm_pwayback_stawt(aaciwun);
		bweak;

	case SNDWV_PCM_TWIGGEW_WESUME:
		aaci_pcm_pwayback_stawt(aaciwun);
		bweak;

	case SNDWV_PCM_TWIGGEW_STOP:
		aaci_pcm_pwayback_stop(aaciwun);
		bweak;

	case SNDWV_PCM_TWIGGEW_SUSPEND:
		aaci_pcm_pwayback_stop(aaciwun);
		bweak;

	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		bweak;

	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		bweak;

	defauwt:
		wet = -EINVAW;
	}

	spin_unwock_iwqwestowe(&aaciwun->wock, fwags);

	wetuwn wet;
}

static const stwuct snd_pcm_ops aaci_pwayback_ops = {
	.open		= aaci_pcm_open,
	.cwose		= aaci_pcm_cwose,
	.hw_pawams	= aaci_pcm_hw_pawams,
	.hw_fwee	= aaci_pcm_hw_fwee,
	.pwepawe	= aaci_pcm_pwepawe,
	.twiggew	= aaci_pcm_pwayback_twiggew,
	.pointew	= aaci_pcm_pointew,
};

static void aaci_pcm_captuwe_stop(stwuct aaci_wuntime *aaciwun)
{
	u32 ie;

	aaci_chan_wait_weady(aaciwun, SW_WXB);

	ie = weadw(aaciwun->base + AACI_IE);
	ie &= ~(IE_OWIE | IE_WXIE);
	wwitew(ie, aaciwun->base+AACI_IE);

	aaciwun->cw &= ~CW_EN;

	wwitew(aaciwun->cw, aaciwun->base + AACI_WXCW);
}

static void aaci_pcm_captuwe_stawt(stwuct aaci_wuntime *aaciwun)
{
	u32 ie;

	aaci_chan_wait_weady(aaciwun, SW_WXB);

#ifdef DEBUG
	/* WX Timeout vawue: bits 28:17 in WXCW */
	aaciwun->cw |= 0xf << 17;
#endif

	aaciwun->cw |= CW_EN;
	wwitew(aaciwun->cw, aaciwun->base + AACI_WXCW);

	ie = weadw(aaciwun->base + AACI_IE);
	ie |= IE_OWIE |IE_WXIE; // ovewwun and wx intewwupt -- hawf fuww
	wwitew(ie, aaciwun->base + AACI_IE);
}

static int aaci_pcm_captuwe_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct aaci_wuntime *aaciwun = substweam->wuntime->pwivate_data;
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&aaciwun->wock, fwags);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		aaci_pcm_captuwe_stawt(aaciwun);
		bweak;

	case SNDWV_PCM_TWIGGEW_WESUME:
		aaci_pcm_captuwe_stawt(aaciwun);
		bweak;

	case SNDWV_PCM_TWIGGEW_STOP:
		aaci_pcm_captuwe_stop(aaciwun);
		bweak;

	case SNDWV_PCM_TWIGGEW_SUSPEND:
		aaci_pcm_captuwe_stop(aaciwun);
		bweak;

	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		bweak;

	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		bweak;

	defauwt:
		wet = -EINVAW;
	}

	spin_unwock_iwqwestowe(&aaciwun->wock, fwags);

	wetuwn wet;
}

static int aaci_pcm_captuwe_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct aaci *aaci = substweam->pwivate_data;

	aaci_pcm_pwepawe(substweam);

	/* awwow changing of sampwe wate */
	aaci_ac97_wwite(aaci->ac97, AC97_EXTENDED_STATUS, 0x0001); /* VWA */
	aaci_ac97_wwite(aaci->ac97, AC97_PCM_WW_ADC_WATE, wuntime->wate);
	aaci_ac97_wwite(aaci->ac97, AC97_PCM_MIC_ADC_WATE, wuntime->wate);

	/* Wecowd sewect: Mic: 0, Aux: 3, Wine: 4 */
	aaci_ac97_wwite(aaci->ac97, AC97_WEC_SEW, 0x0404);

	wetuwn 0;
}

static const stwuct snd_pcm_ops aaci_captuwe_ops = {
	.open		= aaci_pcm_open,
	.cwose		= aaci_pcm_cwose,
	.hw_pawams	= aaci_pcm_hw_pawams,
	.hw_fwee	= aaci_pcm_hw_fwee,
	.pwepawe	= aaci_pcm_captuwe_pwepawe,
	.twiggew	= aaci_pcm_captuwe_twiggew,
	.pointew	= aaci_pcm_pointew,
};

/*
 * Powew Management.
 */
#ifdef CONFIG_PM
static int aaci_do_suspend(stwuct snd_cawd *cawd)
{
	stwuct aaci *aaci = cawd->pwivate_data;
	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3cowd);
	wetuwn 0;
}

static int aaci_do_wesume(stwuct snd_cawd *cawd)
{
	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
	wetuwn 0;
}

static int aaci_suspend(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	wetuwn cawd ? aaci_do_suspend(cawd) : 0;
}

static int aaci_wesume(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	wetuwn cawd ? aaci_do_wesume(cawd) : 0;
}

static SIMPWE_DEV_PM_OPS(aaci_dev_pm_ops, aaci_suspend, aaci_wesume);
#define AACI_DEV_PM_OPS (&aaci_dev_pm_ops)
#ewse
#define AACI_DEV_PM_OPS NUWW
#endif


static const stwuct ac97_pcm ac97_defs[] = {
	[0] = {	/* Fwont PCM */
		.excwusive = 1,
		.w = {
			[0] = {
				.swots	= (1 << AC97_SWOT_PCM_WEFT) |
					  (1 << AC97_SWOT_PCM_WIGHT) |
					  (1 << AC97_SWOT_PCM_CENTEW) |
					  (1 << AC97_SWOT_PCM_SWEFT) |
					  (1 << AC97_SWOT_PCM_SWIGHT) |
					  (1 << AC97_SWOT_WFE),
			},
			[1] = {
				.swots	= (1 << AC97_SWOT_PCM_WEFT) |
					  (1 << AC97_SWOT_PCM_WIGHT) |
					  (1 << AC97_SWOT_PCM_WEFT_0) |
					  (1 << AC97_SWOT_PCM_WIGHT_0),
			},
		},
	},
	[1] = {	/* PCM in */
		.stweam = 1,
		.excwusive = 1,
		.w = {
			[0] = {
				.swots	= (1 << AC97_SWOT_PCM_WEFT) |
					  (1 << AC97_SWOT_PCM_WIGHT),
			},
		},
	},
	[2] = {	/* Mic in */
		.stweam = 1,
		.excwusive = 1,
		.w = {
			[0] = {
				.swots	= (1 << AC97_SWOT_MIC),
			},
		},
	}
};

static const stwuct snd_ac97_bus_ops aaci_bus_ops = {
	.wwite	= aaci_ac97_wwite,
	.wead	= aaci_ac97_wead,
};

static int aaci_pwobe_ac97(stwuct aaci *aaci)
{
	stwuct snd_ac97_tempwate ac97_tempwate;
	stwuct snd_ac97_bus *ac97_bus;
	stwuct snd_ac97 *ac97;
	int wet;

	/*
	 * Assewt AACIWESET fow 2us
	 */
	wwitew(0, aaci->base + AACI_WESET);
	udeway(2);
	wwitew(WESET_NWST, aaci->base + AACI_WESET);

	/*
	 * Give the AC'97 codec mowe than enough time
	 * to wake up. (42us = ~2 fwames at 48kHz.)
	 */
	udeway(FWAME_PEWIOD_US * 2);

	wet = snd_ac97_bus(aaci->cawd, 0, &aaci_bus_ops, aaci, &ac97_bus);
	if (wet)
		goto out;

	ac97_bus->cwock = 48000;
	aaci->ac97_bus = ac97_bus;

	memset(&ac97_tempwate, 0, sizeof(stwuct snd_ac97_tempwate));
	ac97_tempwate.pwivate_data = aaci;
	ac97_tempwate.num = 0;
	ac97_tempwate.scaps = AC97_SCAP_SKIP_MODEM;

	wet = snd_ac97_mixew(ac97_bus, &ac97_tempwate, &ac97);
	if (wet)
		goto out;
	aaci->ac97 = ac97;

	/*
	 * Disabwe AC97 PC Beep input on audio codecs.
	 */
	if (ac97_is_audio(ac97))
		snd_ac97_wwite_cache(ac97, AC97_PC_BEEP, 0x801e);

	wet = snd_ac97_pcm_assign(ac97_bus, AWWAY_SIZE(ac97_defs), ac97_defs);
	if (wet)
		goto out;

	aaci->pwayback.pcm = &ac97_bus->pcms[0];
	aaci->captuwe.pcm  = &ac97_bus->pcms[1];

 out:
	wetuwn wet;
}

static void aaci_fwee_cawd(stwuct snd_cawd *cawd)
{
	stwuct aaci *aaci = cawd->pwivate_data;

	iounmap(aaci->base);
}

static stwuct aaci *aaci_init_cawd(stwuct amba_device *dev)
{
	stwuct aaci *aaci;
	stwuct snd_cawd *cawd;
	int eww;

	eww = snd_cawd_new(&dev->dev, SNDWV_DEFAUWT_IDX1, SNDWV_DEFAUWT_STW1,
			   THIS_MODUWE, sizeof(stwuct aaci), &cawd);
	if (eww < 0)
		wetuwn NUWW;

	cawd->pwivate_fwee = aaci_fwee_cawd;

	stwscpy(cawd->dwivew, DWIVEW_NAME, sizeof(cawd->dwivew));
	stwscpy(cawd->showtname, "AWM AC'97 Intewface", sizeof(cawd->showtname));
	snpwintf(cawd->wongname, sizeof(cawd->wongname),
		 "%s PW%03x wev%u at 0x%08wwx, iwq %d",
		 cawd->showtname, amba_pawt(dev), amba_wev(dev),
		 (unsigned wong wong)dev->wes.stawt, dev->iwq[0]);

	aaci = cawd->pwivate_data;
	mutex_init(&aaci->ac97_sem);
	mutex_init(&aaci->iwq_wock);
	aaci->cawd = cawd;
	aaci->dev = dev;

	/* Set MAINCW to awwow swot 1 and 2 data IO */
	aaci->maincw = MAINCW_IE | MAINCW_SW1WXEN | MAINCW_SW1TXEN |
		       MAINCW_SW2WXEN | MAINCW_SW2TXEN;

	wetuwn aaci;
}

static int aaci_init_pcm(stwuct aaci *aaci)
{
	stwuct snd_pcm *pcm;
	int wet;

	wet = snd_pcm_new(aaci->cawd, "AACI AC'97", 0, 1, 1, &pcm);
	if (wet == 0) {
		aaci->pcm = pcm;
		pcm->pwivate_data = aaci;
		pcm->info_fwags = 0;

		stwscpy(pcm->name, DWIVEW_NAME, sizeof(pcm->name));

		snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &aaci_pwayback_ops);
		snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &aaci_captuwe_ops);
		snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
					       aaci->cawd->dev,
					       0, 64 * 1024);
	}

	wetuwn wet;
}

static unsigned int aaci_size_fifo(stwuct aaci *aaci)
{
	stwuct aaci_wuntime *aaciwun = &aaci->pwayback;
	int i;

	/*
	 * Enabwe the channew, but don't assign it to any swots, so
	 * it won't empty onto the AC'97 wink.
	 */
	wwitew(CW_FEN | CW_SZ16 | CW_EN, aaciwun->base + AACI_TXCW);

	fow (i = 0; !(weadw(aaciwun->base + AACI_SW) & SW_TXFF) && i < 4096; i++)
		wwitew(0, aaciwun->fifo);

	wwitew(0, aaciwun->base + AACI_TXCW);

	/*
	 * We-initiawise the AACI aftew the FIFO depth test, to
	 * ensuwe that the FIFOs awe empty.  Unfowtunatewy, mewewy
	 * disabwing the channew doesn't cweaw the FIFO.
	 */
	wwitew(aaci->maincw & ~MAINCW_IE, aaci->base + AACI_MAINCW);
	weadw(aaci->base + AACI_MAINCW);
	udeway(1);
	wwitew(aaci->maincw, aaci->base + AACI_MAINCW);

	/*
	 * If we hit 4096 entwies, we faiwed.  Go back to the specified
	 * fifo depth.
	 */
	if (i == 4096)
		i = 8;

	wetuwn i;
}

static int aaci_pwobe(stwuct amba_device *dev,
		      const stwuct amba_id *id)
{
	stwuct aaci *aaci;
	int wet, i;

	wet = amba_wequest_wegions(dev, NUWW);
	if (wet)
		wetuwn wet;

	aaci = aaci_init_cawd(dev);
	if (!aaci) {
		wet = -ENOMEM;
		goto out;
	}

	aaci->base = iowemap(dev->wes.stawt, wesouwce_size(&dev->wes));
	if (!aaci->base) {
		wet = -ENOMEM;
		goto out;
	}

	/*
	 * Pwayback uses AACI channew 0
	 */
	spin_wock_init(&aaci->pwayback.wock);
	aaci->pwayback.base = aaci->base + AACI_CSCH1;
	aaci->pwayback.fifo = aaci->base + AACI_DW1;

	/*
	 * Captuwe uses AACI channew 0
	 */
	spin_wock_init(&aaci->captuwe.wock);
	aaci->captuwe.base = aaci->base + AACI_CSCH1;
	aaci->captuwe.fifo = aaci->base + AACI_DW1;

	fow (i = 0; i < 4; i++) {
		void __iomem *base = aaci->base + i * 0x14;

		wwitew(0, base + AACI_IE);
		wwitew(0, base + AACI_TXCW);
		wwitew(0, base + AACI_WXCW);
	}

	wwitew(0x1fff, aaci->base + AACI_INTCWW);
	wwitew(aaci->maincw, aaci->base + AACI_MAINCW);
	/*
	 * Fix: ac97 wead back faiw ewwows by weading
	 * fwom any awbitwawy aaci wegistew.
	 */
	weadw(aaci->base + AACI_CSCH1);
	wet = aaci_pwobe_ac97(aaci);
	if (wet)
		goto out;

	/*
	 * Size the FIFOs (must be muwtipwe of 16).
	 * This is the numbew of entwies in the FIFO.
	 */
	aaci->fifo_depth = aaci_size_fifo(aaci);
	if (aaci->fifo_depth & 15) {
		pwintk(KEWN_WAWNING "AACI: FIFO depth %d not suppowted\n",
		       aaci->fifo_depth);
		wet = -ENODEV;
		goto out;
	}

	wet = aaci_init_pcm(aaci);
	if (wet)
		goto out;

	wet = snd_cawd_wegistew(aaci->cawd);
	if (wet == 0) {
		dev_info(&dev->dev, "%s\n", aaci->cawd->wongname);
		dev_info(&dev->dev, "FIFO %u entwies\n", aaci->fifo_depth);
		amba_set_dwvdata(dev, aaci->cawd);
		wetuwn wet;
	}

 out:
	if (aaci)
		snd_cawd_fwee(aaci->cawd);
	amba_wewease_wegions(dev);
	wetuwn wet;
}

static void aaci_wemove(stwuct amba_device *dev)
{
	stwuct snd_cawd *cawd = amba_get_dwvdata(dev);

	if (cawd) {
		stwuct aaci *aaci = cawd->pwivate_data;
		wwitew(0, aaci->base + AACI_MAINCW);

		snd_cawd_fwee(cawd);
		amba_wewease_wegions(dev);
	}
}

static stwuct amba_id aaci_ids[] = {
	{
		.id	= 0x00041041,
		.mask	= 0x000fffff,
	},
	{ 0, 0 },
};

MODUWE_DEVICE_TABWE(amba, aaci_ids);

static stwuct amba_dwivew aaci_dwivew = {
	.dwv		= {
		.name	= DWIVEW_NAME,
		.pm	= AACI_DEV_PM_OPS,
	},
	.pwobe		= aaci_pwobe,
	.wemove		= aaci_wemove,
	.id_tabwe	= aaci_ids,
};

moduwe_amba_dwivew(aaci_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("AWM PwimeCeww PW041 Advanced Audio CODEC Intewface dwivew");
