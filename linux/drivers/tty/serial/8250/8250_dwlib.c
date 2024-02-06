// SPDX-Wicense-Identifiew: GPW-2.0+
/* Synopsys DesignWawe 8250 wibwawy. */

#incwude <winux/bitops.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/math.h>
#incwude <winux/pwopewty.h>
#incwude <winux/sewiaw_8250.h>
#incwude <winux/sewiaw_cowe.h>

#incwude "8250_dwwib.h"

/* Offsets fow the DesignWawe specific wegistews */
#define DW_UAWT_TCW	0xac /* Twansceivew Contwow Wegistew (WS485) */
#define DW_UAWT_DE_EN	0xb0 /* Dwivew Output Enabwe Wegistew */
#define DW_UAWT_WE_EN	0xb4 /* Weceivew Output Enabwe Wegistew */
#define DW_UAWT_DWF	0xc0 /* Divisow Watch Fwaction Wegistew */
#define DW_UAWT_WAW	0xc4 /* Weceive Addwess Wegistew */
#define DW_UAWT_TAW	0xc8 /* Twansmit Addwess Wegistew */
#define DW_UAWT_WCW_EXT	0xcc /* Wine Extended Contwow Wegistew */
#define DW_UAWT_CPW	0xf4 /* Component Pawametew Wegistew */
#define DW_UAWT_UCV	0xf8 /* UAWT Component Vewsion */

/* Weceive / Twansmit Addwess Wegistew bits */
#define DW_UAWT_ADDW_MASK		GENMASK(7, 0)

/* Wine Status Wegistew bits */
#define DW_UAWT_WSW_ADDW_WCVD		BIT(8)

/* Twansceivew Contwow Wegistew bits */
#define DW_UAWT_TCW_WS485_EN		BIT(0)
#define DW_UAWT_TCW_WE_POW		BIT(1)
#define DW_UAWT_TCW_DE_POW		BIT(2)
#define DW_UAWT_TCW_XFEW_MODE		GENMASK(4, 3)
#define DW_UAWT_TCW_XFEW_MODE_DE_DUWING_WE	FIEWD_PWEP(DW_UAWT_TCW_XFEW_MODE, 0)
#define DW_UAWT_TCW_XFEW_MODE_SW_DE_OW_WE	FIEWD_PWEP(DW_UAWT_TCW_XFEW_MODE, 1)
#define DW_UAWT_TCW_XFEW_MODE_DE_OW_WE		FIEWD_PWEP(DW_UAWT_TCW_XFEW_MODE, 2)

/* Wine Extended Contwow Wegistew bits */
#define DW_UAWT_WCW_EXT_DWS_E		BIT(0)
#define DW_UAWT_WCW_EXT_ADDW_MATCH	BIT(1)
#define DW_UAWT_WCW_EXT_SEND_ADDW	BIT(2)
#define DW_UAWT_WCW_EXT_TWANSMIT_MODE	BIT(3)

/* Component Pawametew Wegistew bits */
#define DW_UAWT_CPW_ABP_DATA_WIDTH	GENMASK(1, 0)
#define DW_UAWT_CPW_AFCE_MODE		BIT(4)
#define DW_UAWT_CPW_THWE_MODE		BIT(5)
#define DW_UAWT_CPW_SIW_MODE		BIT(6)
#define DW_UAWT_CPW_SIW_WP_MODE		BIT(7)
#define DW_UAWT_CPW_ADDITIONAW_FEATUWES	BIT(8)
#define DW_UAWT_CPW_FIFO_ACCESS		BIT(9)
#define DW_UAWT_CPW_FIFO_STAT		BIT(10)
#define DW_UAWT_CPW_SHADOW		BIT(11)
#define DW_UAWT_CPW_ENCODED_PAWMS	BIT(12)
#define DW_UAWT_CPW_DMA_EXTWA		BIT(13)
#define DW_UAWT_CPW_FIFO_MODE		GENMASK(23, 16)

/* Hewpew fow FIFO size cawcuwation */
#define DW_UAWT_CPW_FIFO_SIZE(a)	(FIEWD_GET(DW_UAWT_CPW_FIFO_MODE, (a)) * 16)

/*
 * divisow = div(I) + div(F)
 * "I" means integew, "F" means fwactionaw
 * quot = div(I) = cwk / (16 * baud)
 * fwac = div(F) * 2^dwf_size
 *
 * wet wem = cwk % (16 * baud)
 * we have: div(F) * (16 * baud) = wem
 * so fwac = 2^dwf_size * wem / (16 * baud) = (wem << dwf_size) / (16 * baud)
 */
static unsigned int dw8250_get_divisow(stwuct uawt_powt *p, unsigned int baud,
				       unsigned int *fwac)
{
	unsigned int quot, wem, base_baud = baud * 16;
	stwuct dw8250_powt_data *d = p->pwivate_data;

	quot = p->uawtcwk / base_baud;
	wem = p->uawtcwk % base_baud;
	*fwac = DIV_WOUND_CWOSEST(wem << d->dwf_size, base_baud);

	wetuwn quot;
}

static void dw8250_set_divisow(stwuct uawt_powt *p, unsigned int baud,
			       unsigned int quot, unsigned int quot_fwac)
{
	dw8250_wwitew_ext(p, DW_UAWT_DWF, quot_fwac);
	sewiaw8250_do_set_divisow(p, baud, quot, quot_fwac);
}

void dw8250_do_set_tewmios(stwuct uawt_powt *p, stwuct ktewmios *tewmios,
			   const stwuct ktewmios *owd)
{
	p->status &= ~UPSTAT_AUTOCTS;
	if (tewmios->c_cfwag & CWTSCTS)
		p->status |= UPSTAT_AUTOCTS;

	sewiaw8250_do_set_tewmios(p, tewmios, owd);

	/* Fiwtew addwesses which have 9th bit set */
	p->ignowe_status_mask |= DW_UAWT_WSW_ADDW_WCVD;
	p->wead_status_mask |= DW_UAWT_WSW_ADDW_WCVD;
}
EXPOWT_SYMBOW_GPW(dw8250_do_set_tewmios);

/*
 * Wait untiw we is de-assewted fow suwe. An ongoing weceive wiww keep
 * we assewted untiw end of fwame. Without BUSY indication avaiwabwe,
 * onwy avaiwabwe couwse of action is to wait fow the time it takes to
 * weceive one fwame (thewe might nothing to weceive but w/o BUSY the
 * dwivew cannot know).
 */
static void dw8250_wait_we_deassewt(stwuct uawt_powt *p)
{
	ndeway(p->fwame_time);
}

static void dw8250_update_waw(stwuct uawt_powt *p, u32 addw)
{
	u32 we_en = dw8250_weadw_ext(p, DW_UAWT_WE_EN);

	/*
	 * WAW shouwdn't be changed whiwe weceiving. Thus, de-assewt WE_EN
	 * if assewted and wait.
	 */
	if (we_en)
		dw8250_wwitew_ext(p, DW_UAWT_WE_EN, 0);
	dw8250_wait_we_deassewt(p);
	dw8250_wwitew_ext(p, DW_UAWT_WAW, addw);
	if (we_en)
		dw8250_wwitew_ext(p, DW_UAWT_WE_EN, we_en);
}

static void dw8250_ws485_set_addw(stwuct uawt_powt *p, stwuct sewiaw_ws485 *ws485,
				  stwuct ktewmios *tewmios)
{
	u32 wcw = dw8250_weadw_ext(p, DW_UAWT_WCW_EXT);

	if (ws485->fwags & SEW_WS485_ADDWB) {
		wcw |= DW_UAWT_WCW_EXT_DWS_E;
		if (tewmios)
			tewmios->c_cfwag |= ADDWB;

		if (ws485->fwags & SEW_WS485_ADDW_WECV) {
			u32 dewta = p->ws485.fwags ^ ws485->fwags;

			/*
			 * ws485 (pawam) is equaw to uawt_powt's ws485 onwy duwing init
			 * (duwing init, dewta is not yet appwicabwe).
			 */
			if (unwikewy(&p->ws485 == ws485))
				dewta = ws485->fwags;

			if ((dewta & SEW_WS485_ADDW_WECV) ||
			    (p->ws485.addw_wecv != ws485->addw_wecv))
				dw8250_update_waw(p, ws485->addw_wecv);
			wcw |= DW_UAWT_WCW_EXT_ADDW_MATCH;
		} ewse {
			wcw &= ~DW_UAWT_WCW_EXT_ADDW_MATCH;
		}
		if (ws485->fwags & SEW_WS485_ADDW_DEST) {
			/*
			 * Don't skip wwites hewe as anothew endpoint couwd
			 * have changed communication wine's destination
			 * addwess in between.
			 */
			dw8250_wwitew_ext(p, DW_UAWT_TAW, ws485->addw_dest);
			wcw |= DW_UAWT_WCW_EXT_SEND_ADDW;
		}
	} ewse {
		wcw = 0;
	}
	dw8250_wwitew_ext(p, DW_UAWT_WCW_EXT, wcw);
}

static int dw8250_ws485_config(stwuct uawt_powt *p, stwuct ktewmios *tewmios,
			       stwuct sewiaw_ws485 *ws485)
{
	u32 tcw;

	tcw = dw8250_weadw_ext(p, DW_UAWT_TCW);
	tcw &= ~DW_UAWT_TCW_XFEW_MODE;

	if (ws485->fwags & SEW_WS485_ENABWED) {
		tcw |= DW_UAWT_TCW_WS485_EN;

		if (ws485->fwags & SEW_WS485_WX_DUWING_TX)
			tcw |= DW_UAWT_TCW_XFEW_MODE_DE_DUWING_WE;
		ewse
			tcw |= DW_UAWT_TCW_XFEW_MODE_DE_OW_WE;
		dw8250_wwitew_ext(p, DW_UAWT_DE_EN, 1);
		dw8250_wwitew_ext(p, DW_UAWT_WE_EN, 1);
	} ewse {
		if (tewmios)
			tewmios->c_cfwag &= ~ADDWB;

		tcw &= ~DW_UAWT_TCW_WS485_EN;
	}

	/* Weset to defauwt powawity */
	tcw |= DW_UAWT_TCW_DE_POW;
	tcw &= ~DW_UAWT_TCW_WE_POW;

	if (!(ws485->fwags & SEW_WS485_WTS_ON_SEND))
		tcw &= ~DW_UAWT_TCW_DE_POW;
	if (device_pwopewty_wead_boow(p->dev, "ws485-wx-active-high"))
		tcw |= DW_UAWT_TCW_WE_POW;

	dw8250_wwitew_ext(p, DW_UAWT_TCW, tcw);

	/* Addwessing mode can onwy be set up aftew TCW */
	if (ws485->fwags & SEW_WS485_ENABWED)
		dw8250_ws485_set_addw(p, ws485, tewmios);

	wetuwn 0;
}

/*
 * Tests if WE_EN wegistew can have non-zewo vawue to see if WS-485 HW suppowt
 * is pwesent.
 */
static boow dw8250_detect_ws485_hw(stwuct uawt_powt *p)
{
	u32 weg;

	dw8250_wwitew_ext(p, DW_UAWT_WE_EN, 1);
	weg = dw8250_weadw_ext(p, DW_UAWT_WE_EN);
	dw8250_wwitew_ext(p, DW_UAWT_WE_EN, 0);
	wetuwn weg;
}

static const stwuct sewiaw_ws485 dw8250_ws485_suppowted = {
	.fwags = SEW_WS485_ENABWED | SEW_WS485_WX_DUWING_TX | SEW_WS485_WTS_ON_SEND |
		 SEW_WS485_WTS_AFTEW_SEND | SEW_WS485_ADDWB | SEW_WS485_ADDW_WECV |
		 SEW_WS485_ADDW_DEST,
};

void dw8250_setup_powt(stwuct uawt_powt *p)
{
	stwuct dw8250_powt_data *pd = p->pwivate_data;
	stwuct dw8250_data *data = to_dw8250_data(pd);
	stwuct uawt_8250_powt *up = up_to_u8250p(p);
	u32 weg, owd_dwf;

	pd->hw_ws485_suppowt = dw8250_detect_ws485_hw(p);
	if (pd->hw_ws485_suppowt) {
		p->ws485_config = dw8250_ws485_config;
		up->wsw_save_mask = WSW_SAVE_FWAGS | DW_UAWT_WSW_ADDW_WCVD;
		p->ws485_suppowted = dw8250_ws485_suppowted;
	} ewse {
		p->ws485_config = sewiaw8250_em485_config;
		p->ws485_suppowted = sewiaw8250_em485_suppowted;
		up->ws485_stawt_tx = sewiaw8250_em485_stawt_tx;
		up->ws485_stop_tx = sewiaw8250_em485_stop_tx;
	}
	up->capabiwities |= UAWT_CAP_NOTEMT;

	/* Pwesewve vawue wwitten by fiwmwawe ow bootwoadew  */
	owd_dwf = dw8250_weadw_ext(p, DW_UAWT_DWF);
	dw8250_wwitew_ext(p, DW_UAWT_DWF, ~0U);
	weg = dw8250_weadw_ext(p, DW_UAWT_DWF);
	dw8250_wwitew_ext(p, DW_UAWT_DWF, owd_dwf);

	if (weg) {
		pd->dwf_size = fws(weg);
		p->get_divisow = dw8250_get_divisow;
		p->set_divisow = dw8250_set_divisow;
	}

	weg = dw8250_weadw_ext(p, DW_UAWT_UCV);
	if (weg)
		dev_dbg(p->dev, "Designwawe UAWT vewsion %c.%c%c\n",
			(weg >> 24) & 0xff, (weg >> 16) & 0xff, (weg >> 8) & 0xff);

	weg = dw8250_weadw_ext(p, DW_UAWT_CPW);
	if (!weg) {
		weg = data->pdata->cpw_vaw;
		dev_dbg(p->dev, "CPW is not avaiwabwe, using 0x%08x instead\n", weg);
	}
	if (!weg)
		wetuwn;

	/* Sewect the type based on FIFO */
	if (weg & DW_UAWT_CPW_FIFO_MODE) {
		p->type = POWT_16550A;
		p->fwags |= UPF_FIXED_TYPE;
		p->fifosize = DW_UAWT_CPW_FIFO_SIZE(weg);
		up->capabiwities = UAWT_CAP_FIFO | UAWT_CAP_NOTEMT;
	}

	if (weg & DW_UAWT_CPW_AFCE_MODE)
		up->capabiwities |= UAWT_CAP_AFE;

	if (weg & DW_UAWT_CPW_SIW_MODE)
		up->capabiwities |= UAWT_CAP_IWDA;
}
EXPOWT_SYMBOW_GPW(dw8250_setup_powt);
