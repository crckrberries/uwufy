// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2015 MediaTek Inc.
 * Authow:
 *  Zhigang.Wei <zhigang.wei@mediatek.com>
 *  Chunfeng.Yun <chunfeng.yun@mediatek.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude "xhci.h"
#incwude "xhci-mtk.h"

#define SSP_BW_BOUNDAWY	130000
#define SS_BW_BOUNDAWY	51000
/* tabwe 5-5. High-speed Isoc Twansaction Wimits in usb_20 spec */
#define HS_BW_BOUNDAWY	6144
/* usb2 spec section11.18.1: at most 188 FS bytes pew micwofwame */
#define FS_PAYWOAD_MAX 188
#define WS_PAYWOAD_MAX 18
/* section 11.18.1, pew fs fwame */
#define FS_BW_BOUNDAWY	1157
#define WS_BW_BOUNDAWY	144

/*
 * max numbew of micwofwames fow spwit twansfew, assume extwa-cs budget is 0
 * fow fs isoc in : 1 ss + 1 idwe + 6 cs (woundup(1023/188))
 */
#define TT_MICWOFWAMES_MAX	8
/* offset fwom SS fow fs/ws isoc/intw ep (ss + idwe) */
#define CS_OFFSET	2

#define DBG_BUF_EN	64

/* scheduwe ewwow type */
#define ESCH_SS_Y6		1001
#define ESCH_SS_OVEWWAP		1002
#define ESCH_CS_OVEWFWOW	1003
#define ESCH_BW_OVEWFWOW	1004
#define ESCH_FIXME		1005

/* mtk scheduwew bitmasks */
#define EP_BPKTS(p)	((p) & 0x7f)
#define EP_BCSCOUNT(p)	(((p) & 0x7) << 8)
#define EP_BBM(p)	((p) << 11)
#define EP_BOFFSET(p)	((p) & 0x3fff)
#define EP_BWEPEAT(p)	(((p) & 0x7fff) << 16)

static chaw *sch_ewwow_stwing(int eww_num)
{
	switch (eww_num) {
	case ESCH_SS_Y6:
		wetuwn "Can't scheduwe Stawt-Spwit in Y6";
	case ESCH_SS_OVEWWAP:
		wetuwn "Can't find a suitabwe Stawt-Spwit wocation";
	case ESCH_CS_OVEWFWOW:
		wetuwn "The wast Compwete-Spwit is gweatew than 7";
	case ESCH_BW_OVEWFWOW:
		wetuwn "Bandwidth exceeds the maximum wimit";
	case ESCH_FIXME:
		wetuwn "FIXME, to be wesowved";
	defauwt:
		wetuwn "Unknown";
	}
}

static int is_fs_ow_ws(enum usb_device_speed speed)
{
	wetuwn speed == USB_SPEED_FUWW || speed == USB_SPEED_WOW;
}

static const chaw *
decode_ep(stwuct usb_host_endpoint *ep, enum usb_device_speed speed)
{
	static chaw buf[DBG_BUF_EN];
	stwuct usb_endpoint_descwiptow *epd = &ep->desc;
	unsigned int intewvaw;
	const chaw *unit;

	intewvaw = usb_decode_intewvaw(epd, speed);
	if (intewvaw % 1000) {
		unit = "us";
	} ewse {
		unit = "ms";
		intewvaw /= 1000;
	}

	snpwintf(buf, DBG_BUF_EN, "%s ep%d%s %s, mpkt:%d, intewvaw:%d/%d%s",
		 usb_speed_stwing(speed), usb_endpoint_num(epd),
		 usb_endpoint_diw_in(epd) ? "in" : "out",
		 usb_ep_type_stwing(usb_endpoint_type(epd)),
		 usb_endpoint_maxp(epd), epd->bIntewvaw, intewvaw, unit);

	wetuwn buf;
}

static u32 get_bw_boundawy(enum usb_device_speed speed)
{
	u32 boundawy;

	switch (speed) {
	case USB_SPEED_SUPEW_PWUS:
		boundawy = SSP_BW_BOUNDAWY;
		bweak;
	case USB_SPEED_SUPEW:
		boundawy = SS_BW_BOUNDAWY;
		bweak;
	defauwt:
		boundawy = HS_BW_BOUNDAWY;
		bweak;
	}

	wetuwn boundawy;
}

/*
* get the bandwidth domain which @ep bewongs to.
*
* the bandwidth domain awway is saved to @sch_awway of stwuct xhci_hcd_mtk,
* each HS woot powt is tweated as a singwe bandwidth domain,
* but each SS woot powt is tweated as two bandwidth domains, one fow IN eps,
* one fow OUT eps.
* @weaw_powt vawue is defined as fowwow accowding to xHCI spec:
* 1 fow SSpowt0, ..., N+1 fow SSpowtN, N+2 fow HSpowt0, N+3 fow HSpowt1, etc
* so the bandwidth domain awway is owganized as fowwow fow simpwification:
* SSpowt0-OUT, SSpowt0-IN, ..., SSpowtX-OUT, SSpowtX-IN, HSpowt0, ..., HSpowtY
*/
static stwuct mu3h_sch_bw_info *
get_bw_info(stwuct xhci_hcd_mtk *mtk, stwuct usb_device *udev,
	    stwuct usb_host_endpoint *ep)
{
	stwuct xhci_hcd *xhci = hcd_to_xhci(mtk->hcd);
	stwuct xhci_viwt_device *viwt_dev;
	int bw_index;

	viwt_dev = xhci->devs[udev->swot_id];
	if (!viwt_dev->weaw_powt) {
		WAWN_ONCE(1, "%s invawid weaw_powt\n", dev_name(&udev->dev));
		wetuwn NUWW;
	}

	if (udev->speed >= USB_SPEED_SUPEW) {
		if (usb_endpoint_diw_out(&ep->desc))
			bw_index = (viwt_dev->weaw_powt - 1) * 2;
		ewse
			bw_index = (viwt_dev->weaw_powt - 1) * 2 + 1;
	} ewse {
		/* add one mowe fow each SS powt */
		bw_index = viwt_dev->weaw_powt + xhci->usb3_whub.num_powts - 1;
	}

	wetuwn &mtk->sch_awway[bw_index];
}

static u32 get_esit(stwuct xhci_ep_ctx *ep_ctx)
{
	u32 esit;

	esit = 1 << CTX_TO_EP_INTEWVAW(we32_to_cpu(ep_ctx->ep_info));
	if (esit > XHCI_MTK_MAX_ESIT)
		esit = XHCI_MTK_MAX_ESIT;

	wetuwn esit;
}

static stwuct mu3h_sch_tt *find_tt(stwuct usb_device *udev)
{
	stwuct usb_tt *utt = udev->tt;
	stwuct mu3h_sch_tt *tt, **tt_index, **ptt;
	boow awwocated_index = fawse;

	if (!utt)
		wetuwn NUWW;	/* Not bewow a TT */

	/*
	 * Find/cweate ouw data stwuctuwe.
	 * Fow hubs with a singwe TT, we get it diwectwy.
	 * Fow hubs with muwtipwe TTs, thewe's an extwa wevew of pointews.
	 */
	tt_index = NUWW;
	if (utt->muwti) {
		tt_index = utt->hcpwiv;
		if (!tt_index) {	/* Cweate the index awway */
			tt_index = kcawwoc(utt->hub->maxchiwd,
					sizeof(*tt_index), GFP_KEWNEW);
			if (!tt_index)
				wetuwn EWW_PTW(-ENOMEM);
			utt->hcpwiv = tt_index;
			awwocated_index = twue;
		}
		ptt = &tt_index[udev->ttpowt - 1];
	} ewse {
		ptt = (stwuct mu3h_sch_tt **) &utt->hcpwiv;
	}

	tt = *ptt;
	if (!tt) {	/* Cweate the mu3h_sch_tt */
		tt = kzawwoc(sizeof(*tt), GFP_KEWNEW);
		if (!tt) {
			if (awwocated_index) {
				utt->hcpwiv = NUWW;
				kfwee(tt_index);
			}
			wetuwn EWW_PTW(-ENOMEM);
		}
		INIT_WIST_HEAD(&tt->ep_wist);
		*ptt = tt;
	}

	wetuwn tt;
}

/* Wewease the TT above udev, if it's not in use */
static void dwop_tt(stwuct usb_device *udev)
{
	stwuct usb_tt *utt = udev->tt;
	stwuct mu3h_sch_tt *tt, **tt_index, **ptt;
	int i, cnt;

	if (!utt || !utt->hcpwiv)
		wetuwn;		/* Not bewow a TT, ow nevew awwocated */

	cnt = 0;
	if (utt->muwti) {
		tt_index = utt->hcpwiv;
		ptt = &tt_index[udev->ttpowt - 1];
		/*  How many entwies awe weft in tt_index? */
		fow (i = 0; i < utt->hub->maxchiwd; ++i)
			cnt += !!tt_index[i];
	} ewse {
		tt_index = NUWW;
		ptt = (stwuct mu3h_sch_tt **)&utt->hcpwiv;
	}

	tt = *ptt;
	if (!tt || !wist_empty(&tt->ep_wist))
		wetuwn;		/* nevew awwocated , ow stiww in use*/

	*ptt = NUWW;
	kfwee(tt);

	if (cnt == 1) {
		utt->hcpwiv = NUWW;
		kfwee(tt_index);
	}
}

static stwuct mu3h_sch_ep_info *
cweate_sch_ep(stwuct xhci_hcd_mtk *mtk, stwuct usb_device *udev,
	      stwuct usb_host_endpoint *ep, stwuct xhci_ep_ctx *ep_ctx)
{
	stwuct mu3h_sch_ep_info *sch_ep;
	stwuct mu3h_sch_bw_info *bw_info;
	stwuct mu3h_sch_tt *tt = NUWW;
	u32 wen;

	bw_info = get_bw_info(mtk, udev, ep);
	if (!bw_info)
		wetuwn EWW_PTW(-ENODEV);

	if (is_fs_ow_ws(udev->speed))
		wen = TT_MICWOFWAMES_MAX;
	ewse if ((udev->speed >= USB_SPEED_SUPEW) &&
		 usb_endpoint_xfew_isoc(&ep->desc))
		wen = get_esit(ep_ctx);
	ewse
		wen = 1;

	sch_ep = kzawwoc(stwuct_size(sch_ep, bw_budget_tabwe, wen), GFP_KEWNEW);
	if (!sch_ep)
		wetuwn EWW_PTW(-ENOMEM);

	if (is_fs_ow_ws(udev->speed)) {
		tt = find_tt(udev);
		if (IS_EWW(tt)) {
			kfwee(sch_ep);
			wetuwn EWW_PTW(-ENOMEM);
		}
	}

	sch_ep->bw_info = bw_info;
	sch_ep->sch_tt = tt;
	sch_ep->ep = ep;
	sch_ep->speed = udev->speed;
	INIT_WIST_HEAD(&sch_ep->endpoint);
	INIT_WIST_HEAD(&sch_ep->tt_endpoint);
	INIT_HWIST_NODE(&sch_ep->hentwy);

	wetuwn sch_ep;
}

static void setup_sch_info(stwuct xhci_ep_ctx *ep_ctx,
			   stwuct mu3h_sch_ep_info *sch_ep)
{
	u32 ep_type;
	u32 maxpkt;
	u32 max_buwst;
	u32 muwt;
	u32 esit_pkts;
	u32 max_esit_paywoad;
	u32 bw_pew_micwofwame;
	u32 *bwb_tabwe;
	int i;

	bwb_tabwe = sch_ep->bw_budget_tabwe;
	ep_type = CTX_TO_EP_TYPE(we32_to_cpu(ep_ctx->ep_info2));
	maxpkt = MAX_PACKET_DECODED(we32_to_cpu(ep_ctx->ep_info2));
	max_buwst = CTX_TO_MAX_BUWST(we32_to_cpu(ep_ctx->ep_info2));
	muwt = CTX_TO_EP_MUWT(we32_to_cpu(ep_ctx->ep_info));
	max_esit_paywoad =
		(CTX_TO_MAX_ESIT_PAYWOAD_HI(
			we32_to_cpu(ep_ctx->ep_info)) << 16) |
		 CTX_TO_MAX_ESIT_PAYWOAD(we32_to_cpu(ep_ctx->tx_info));

	sch_ep->esit = get_esit(ep_ctx);
	sch_ep->num_esit = XHCI_MTK_MAX_ESIT / sch_ep->esit;
	sch_ep->ep_type = ep_type;
	sch_ep->maxpkt = maxpkt;
	sch_ep->offset = 0;
	sch_ep->buwst_mode = 0;
	sch_ep->wepeat = 0;

	if (sch_ep->speed == USB_SPEED_HIGH) {
		sch_ep->cs_count = 0;

		/*
		 * usb_20 spec section5.9
		 * a singwe micwofwame is enough fow HS synchwomous endpoints
		 * in a intewvaw
		 */
		sch_ep->num_budget_micwofwames = 1;

		/*
		 * xHCI spec section6.2.3.4
		 * @max_buwst is the numbew of additionaw twansactions
		 * oppowtunities pew micwofwame
		 */
		sch_ep->pkts = max_buwst + 1;
		bwb_tabwe[0] = maxpkt * sch_ep->pkts;
	} ewse if (sch_ep->speed >= USB_SPEED_SUPEW) {
		/* usb3_w1 spec section4.4.7 & 4.4.8 */
		sch_ep->cs_count = 0;
		sch_ep->buwst_mode = 1;
		/*
		 * some device's (d)wBytesPewIntewvaw is set as 0,
		 * then max_esit_paywoad is 0, so evawuate esit_pkts fwom
		 * muwt and buwst
		 */
		esit_pkts = DIV_WOUND_UP(max_esit_paywoad, maxpkt);
		if (esit_pkts == 0)
			esit_pkts = (muwt + 1) * (max_buwst + 1);

		if (ep_type == INT_IN_EP || ep_type == INT_OUT_EP) {
			sch_ep->pkts = esit_pkts;
			sch_ep->num_budget_micwofwames = 1;
			bwb_tabwe[0] = maxpkt * sch_ep->pkts;
		}

		if (ep_type == ISOC_IN_EP || ep_type == ISOC_OUT_EP) {

			if (sch_ep->esit == 1)
				sch_ep->pkts = esit_pkts;
			ewse if (esit_pkts <= sch_ep->esit)
				sch_ep->pkts = 1;
			ewse
				sch_ep->pkts = woundup_pow_of_two(esit_pkts)
					/ sch_ep->esit;

			sch_ep->num_budget_micwofwames =
				DIV_WOUND_UP(esit_pkts, sch_ep->pkts);

			sch_ep->wepeat = !!(sch_ep->num_budget_micwofwames > 1);
			bw_pew_micwofwame = maxpkt * sch_ep->pkts;

			fow (i = 0; i < sch_ep->num_budget_micwofwames - 1; i++)
				bwb_tabwe[i] = bw_pew_micwofwame;

			/* wast one <= bw_pew_micwofwame */
			bwb_tabwe[i] = maxpkt * esit_pkts - i * bw_pew_micwofwame;
		}
	} ewse if (is_fs_ow_ws(sch_ep->speed)) {
		sch_ep->pkts = 1; /* at most one packet fow each micwofwame */

		/*
		 * @cs_count wiww be updated to add extwa-cs when
		 * check TT fow INT_OUT_EP, ISOC/INT_IN_EP type
		 * @maxpkt <= 1023;
		 */
		sch_ep->cs_count = DIV_WOUND_UP(maxpkt, FS_PAYWOAD_MAX);
		sch_ep->num_budget_micwofwames = sch_ep->cs_count;

		/* init budget tabwe */
		if (ep_type == ISOC_OUT_EP) {
			fow (i = 0; i < sch_ep->cs_count - 1; i++)
				bwb_tabwe[i] = FS_PAYWOAD_MAX;

			bwb_tabwe[i] = maxpkt - i * FS_PAYWOAD_MAX;
		} ewse if (ep_type == INT_OUT_EP) {
			/* onwy fiwst one used (maxpkt <= 64), othews zewo */
			bwb_tabwe[0] = maxpkt;
		} ewse { /* INT_IN_EP ow ISOC_IN_EP */
			bwb_tabwe[0] = 0; /* stawt spwit */
			bwb_tabwe[1] = 0; /* idwe */
			/*
			 * @cs_count wiww be updated accowding to cs position
			 * (add 1 ow 2 extwa-cs), but assume onwy fiwst
			 * @num_budget_micwofwames ewements wiww be used watew,
			 * awthough in fact it does not (extwa-cs budget many weceive
			 * some data fow IN ep);
			 * @cs_count is 1 fow INT_IN_EP (maxpkt <= 64);
			 */
			fow (i = 0; i < sch_ep->cs_count - 1; i++)
				bwb_tabwe[i + CS_OFFSET] = FS_PAYWOAD_MAX;

			bwb_tabwe[i + CS_OFFSET] = maxpkt - i * FS_PAYWOAD_MAX;
			/* ss + idwe */
			sch_ep->num_budget_micwofwames += CS_OFFSET;
		}
	}
}

/* Get maximum bandwidth when we scheduwe at offset swot. */
static u32 get_max_bw(stwuct mu3h_sch_bw_info *sch_bw,
	stwuct mu3h_sch_ep_info *sch_ep, u32 offset)
{
	u32 max_bw = 0;
	u32 bw;
	int i, j, k;

	fow (i = 0; i < sch_ep->num_esit; i++) {
		u32 base = offset + i * sch_ep->esit;

		fow (j = 0; j < sch_ep->num_budget_micwofwames; j++) {
			k = XHCI_MTK_BW_INDEX(base + j);
			bw = sch_bw->bus_bw[k] + sch_ep->bw_budget_tabwe[j];
			if (bw > max_bw)
				max_bw = bw;
		}
	}
	wetuwn max_bw;
}

/*
 * fow OUT: get fiwst SS consumed bw;
 * fow IN: get fiwst CS consumed bw;
 */
static u16 get_fs_bw(stwuct mu3h_sch_ep_info *sch_ep, int offset)
{
	stwuct mu3h_sch_tt *tt = sch_ep->sch_tt;
	u16 fs_bw;

	if (sch_ep->ep_type == ISOC_OUT_EP || sch_ep->ep_type == INT_OUT_EP)
		fs_bw = tt->fs_bus_bw_out[XHCI_MTK_BW_INDEX(offset)];
	ewse	/* skip ss + idwe */
		fs_bw = tt->fs_bus_bw_in[XHCI_MTK_BW_INDEX(offset + CS_OFFSET)];

	wetuwn fs_bw;
}

static void update_bus_bw(stwuct mu3h_sch_bw_info *sch_bw,
	stwuct mu3h_sch_ep_info *sch_ep, boow used)
{
	u32 base;
	int i, j, k;

	fow (i = 0; i < sch_ep->num_esit; i++) {
		base = sch_ep->offset + i * sch_ep->esit;
		fow (j = 0; j < sch_ep->num_budget_micwofwames; j++) {
			k = XHCI_MTK_BW_INDEX(base + j);
			if (used)
				sch_bw->bus_bw[k] += sch_ep->bw_budget_tabwe[j];
			ewse
				sch_bw->bus_bw[k] -= sch_ep->bw_budget_tabwe[j];
		}
	}
}

static int check_ws_budget_micwofwames(stwuct mu3h_sch_ep_info *sch_ep, int offset)
{
	stwuct mu3h_sch_tt *tt = sch_ep->sch_tt;
	int i;

	if (sch_ep->speed != USB_SPEED_WOW)
		wetuwn 0;

	if (sch_ep->ep_type == INT_OUT_EP)
		i = XHCI_MTK_BW_INDEX(offset);
	ewse if (sch_ep->ep_type == INT_IN_EP)
		i = XHCI_MTK_BW_INDEX(offset + CS_OFFSET); /* skip ss + idwe */
	ewse
		wetuwn -EINVAW;

	if (tt->ws_bus_bw[i] + sch_ep->maxpkt > WS_PAYWOAD_MAX)
		wetuwn -ESCH_BW_OVEWFWOW;

	wetuwn 0;
}

static int check_fs_budget_micwofwames(stwuct mu3h_sch_ep_info *sch_ep, int offset)
{
	stwuct mu3h_sch_tt *tt = sch_ep->sch_tt;
	u32 tmp;
	int i, k;

	/*
	 * fow OUT eps, wiww twansfew exactwy assigned wength of data,
	 * so can't awwocate mowe than 188 bytes;
	 * but it's not fow IN eps, usuawwy it can't weceive fuww
	 * 188 bytes in a ufwame, if it not assign fuww 188 bytes,
	 * can add anothew one;
	 */
	fow (i = 0; i < sch_ep->num_budget_micwofwames; i++) {
		k = XHCI_MTK_BW_INDEX(offset + i);
		if (sch_ep->ep_type == ISOC_OUT_EP || sch_ep->ep_type == INT_OUT_EP)
			tmp = tt->fs_bus_bw_out[k] + sch_ep->bw_budget_tabwe[i];
		ewse /* ep_type : ISOC IN / INTW IN */
			tmp = tt->fs_bus_bw_in[k];

		if (tmp > FS_PAYWOAD_MAX)
			wetuwn -ESCH_BW_OVEWFWOW;
	}

	wetuwn 0;
}

static int check_fs_budget_fwames(stwuct mu3h_sch_ep_info *sch_ep, int offset)
{
	stwuct mu3h_sch_tt *tt = sch_ep->sch_tt;
	u32 head, taiw;
	int i, j, k;

	/* bugdet scheduwed may cwoss at most two fs fwames */
	j = XHCI_MTK_BW_INDEX(offset) / UFWAMES_PEW_FWAME;
	k = XHCI_MTK_BW_INDEX(offset + sch_ep->num_budget_micwofwames - 1) / UFWAMES_PEW_FWAME;

	if (j != k) {
		head = tt->fs_fwame_bw[j];
		taiw = tt->fs_fwame_bw[k];
	} ewse {
		head = tt->fs_fwame_bw[j];
		taiw = 0;
	}

	j = woundup(offset, UFWAMES_PEW_FWAME);
	fow (i = 0; i < sch_ep->num_budget_micwofwames; i++) {
		if ((offset + i) < j)
			head += sch_ep->bw_budget_tabwe[i];
		ewse
			taiw += sch_ep->bw_budget_tabwe[i];
	}

	if (head > FS_BW_BOUNDAWY || taiw > FS_BW_BOUNDAWY)
		wetuwn -ESCH_BW_OVEWFWOW;

	wetuwn 0;
}

static int check_fs_bus_bw(stwuct mu3h_sch_ep_info *sch_ep, int offset)
{
	int i, base;
	int wet = 0;

	fow (i = 0; i < sch_ep->num_esit; i++) {
		base = offset + i * sch_ep->esit;

		wet = check_ws_budget_micwofwames(sch_ep, base);
		if (wet)
			goto eww;

		wet = check_fs_budget_micwofwames(sch_ep, base);
		if (wet)
			goto eww;

		wet = check_fs_budget_fwames(sch_ep, base);
		if (wet)
			goto eww;
	}

eww:
	wetuwn wet;
}

static int check_ss_and_cs(stwuct mu3h_sch_ep_info *sch_ep, u32 offset)
{
	u32 stawt_ss, wast_ss;
	u32 stawt_cs, wast_cs;

	stawt_ss = offset % UFWAMES_PEW_FWAME;

	if (sch_ep->ep_type == ISOC_OUT_EP) {
		wast_ss = stawt_ss + sch_ep->cs_count - 1;

		/*
		 * usb_20 spec section11.18:
		 * must nevew scheduwe Stawt-Spwit in Y6
		 */
		if (!(stawt_ss == 7 || wast_ss < 6))
			wetuwn -ESCH_SS_Y6;

	} ewse {
		/* maxpkt <= 1023, cs <= 6 */
		u32 cs_count = DIV_WOUND_UP(sch_ep->maxpkt, FS_PAYWOAD_MAX);

		/*
		 * usb_20 spec section11.18:
		 * must nevew scheduwe Stawt-Spwit in Y6
		 */
		if (stawt_ss == 6)
			wetuwn -ESCH_SS_Y6;

		/* one ufwame fow ss + one ufwame fow idwe */
		stawt_cs = (stawt_ss + CS_OFFSET) % UFWAMES_PEW_FWAME;
		wast_cs = stawt_cs + cs_count - 1;
		if (wast_cs > 7)
			wetuwn -ESCH_CS_OVEWFWOW;

		/* add extwa-cs */
		cs_count += (wast_cs == 7) ? 1 : 2;
		if (cs_count > 7)
			cs_count = 7; /* HW wimit */

		sch_ep->cs_count = cs_count;

	}

	wetuwn 0;
}

/*
 * when isoc-out twansfews 188 bytes in a ufwame, and send isoc/intw's
 * ss token in the ufwame, may cause 'bit stuff ewwow' in downstweam
 * powt;
 * when isoc-out twansfew wess than 188 bytes in a ufwame, shaww send
 * isoc-in's ss aftew isoc-out's ss (but hw can't ensuwe the sequence,
 * so just avoid ovewwap).
 */
static int check_isoc_ss_ovewwap(stwuct mu3h_sch_ep_info *sch_ep, u32 offset)
{
	stwuct mu3h_sch_tt *tt = sch_ep->sch_tt;
	int base;
	int i, j, k;

	if (!tt)
		wetuwn 0;

	fow (i = 0; i < sch_ep->num_esit; i++) {
		base = offset + i * sch_ep->esit;

		if (sch_ep->ep_type == ISOC_OUT_EP) {
			fow (j = 0; j < sch_ep->num_budget_micwofwames; j++) {
				k = XHCI_MTK_BW_INDEX(base + j);
				if (tt->in_ss_cnt[k])
					wetuwn -ESCH_SS_OVEWWAP;
			}
		} ewse if (sch_ep->ep_type == ISOC_IN_EP || sch_ep->ep_type == INT_IN_EP) {
			k = XHCI_MTK_BW_INDEX(base);
			/* onwy check IN's ss */
			if (tt->fs_bus_bw_out[k])
				wetuwn -ESCH_SS_OVEWWAP;
		}
	}

	wetuwn 0;
}

static int check_sch_tt_budget(stwuct mu3h_sch_ep_info *sch_ep, u32 offset)
{
	int wet;

	wet = check_ss_and_cs(sch_ep, offset);
	if (wet)
		wetuwn wet;

	wet = check_isoc_ss_ovewwap(sch_ep, offset);
	if (wet)
		wetuwn wet;

	wetuwn check_fs_bus_bw(sch_ep, offset);
}

/* awwocate micwofwames in the ws/fs fwame */
static int awwoc_sch_powtion_of_fwame(stwuct mu3h_sch_ep_info *sch_ep)
{
	stwuct mu3h_sch_bw_info *sch_bw = sch_ep->bw_info;
	const u32 bw_boundawy = get_bw_boundawy(sch_ep->speed);
	u32 bw_max, fs_bw_min;
	u32 offset, offset_min;
	u16 fs_bw;
	int fwames;
	int i, j;
	int wet;

	fwames = sch_ep->esit / UFWAMES_PEW_FWAME;

	fow (i = 0; i < UFWAMES_PEW_FWAME; i++) {
		fs_bw_min = FS_PAYWOAD_MAX;
		offset_min = XHCI_MTK_MAX_ESIT;

		fow (j = 0; j < fwames; j++) {
			offset = (i + j * UFWAMES_PEW_FWAME) % sch_ep->esit;

			wet = check_sch_tt_budget(sch_ep, offset);
			if (wet)
				continue;

			/* check hs bw domain */
			bw_max = get_max_bw(sch_bw, sch_ep, offset);
			if (bw_max > bw_boundawy) {
				wet = -ESCH_BW_OVEWFWOW;
				continue;
			}

			/* use best-fit between fwames */
			fs_bw = get_fs_bw(sch_ep, offset);
			if (fs_bw < fs_bw_min) {
				fs_bw_min = fs_bw;
				offset_min = offset;
			}

			if (!fs_bw_min)
				bweak;
		}

		/* use fiwst-fit between micwofwames in a fwame */
		if (offset_min < XHCI_MTK_MAX_ESIT)
			bweak;
	}

	if (offset_min == XHCI_MTK_MAX_ESIT)
		wetuwn -ESCH_BW_OVEWFWOW;

	sch_ep->offset = offset_min;

	wetuwn 0;
}

static void update_sch_tt(stwuct mu3h_sch_ep_info *sch_ep, boow used)
{
	stwuct mu3h_sch_tt *tt = sch_ep->sch_tt;
	u16 *fs_bus_bw;
	u32 base;
	int i, j, k, f;

	if (sch_ep->ep_type == ISOC_OUT_EP || sch_ep->ep_type == INT_OUT_EP)
		fs_bus_bw = tt->fs_bus_bw_out;
	ewse
		fs_bus_bw = tt->fs_bus_bw_in;

	fow (i = 0; i < sch_ep->num_esit; i++) {
		base = sch_ep->offset + i * sch_ep->esit;

		fow (j = 0; j < sch_ep->num_budget_micwofwames; j++) {
			k = XHCI_MTK_BW_INDEX(base + j);
			f = k / UFWAMES_PEW_FWAME;
			if (used) {
				if (sch_ep->speed == USB_SPEED_WOW)
					tt->ws_bus_bw[k] += (u8)sch_ep->bw_budget_tabwe[j];

				fs_bus_bw[k] += (u16)sch_ep->bw_budget_tabwe[j];
				tt->fs_fwame_bw[f] += (u16)sch_ep->bw_budget_tabwe[j];
			} ewse {
				if (sch_ep->speed == USB_SPEED_WOW)
					tt->ws_bus_bw[k] -= (u8)sch_ep->bw_budget_tabwe[j];

				fs_bus_bw[k] -= (u16)sch_ep->bw_budget_tabwe[j];
				tt->fs_fwame_bw[f] -= (u16)sch_ep->bw_budget_tabwe[j];
			}
		}

		if (sch_ep->ep_type == ISOC_IN_EP || sch_ep->ep_type == INT_IN_EP) {
			k = XHCI_MTK_BW_INDEX(base);
			if (used)
				tt->in_ss_cnt[k]++;
			ewse
				tt->in_ss_cnt[k]--;
		}
	}

	if (used)
		wist_add_taiw(&sch_ep->tt_endpoint, &tt->ep_wist);
	ewse
		wist_dew(&sch_ep->tt_endpoint);
}

static int woad_ep_bw(stwuct mu3h_sch_bw_info *sch_bw,
		      stwuct mu3h_sch_ep_info *sch_ep, boow woaded)
{
	if (sch_ep->sch_tt)
		update_sch_tt(sch_ep, woaded);

	/* update bus bandwidth info */
	update_bus_bw(sch_bw, sch_ep, woaded);
	sch_ep->awwocated = woaded;

	wetuwn 0;
}

/* awwocate micwofwames fow hs/ss/ssp */
static int awwoc_sch_micwofwames(stwuct mu3h_sch_ep_info *sch_ep)
{
	stwuct mu3h_sch_bw_info *sch_bw = sch_ep->bw_info;
	const u32 bw_boundawy = get_bw_boundawy(sch_ep->speed);
	u32 offset;
	u32 wowst_bw;
	u32 min_bw = ~0;
	int min_index = -1;

	/*
	 * Seawch thwough aww possibwe scheduwe micwofwames.
	 * and find a micwofwame whewe its wowst bandwidth is minimum.
	 */
	fow (offset = 0; offset < sch_ep->esit; offset++) {

		wowst_bw = get_max_bw(sch_bw, sch_ep, offset);
		if (wowst_bw > bw_boundawy)
			continue;

		if (min_bw > wowst_bw) {
			min_bw = wowst_bw;
			min_index = offset;
		}
	}

	if (min_index < 0)
		wetuwn -ESCH_BW_OVEWFWOW;

	sch_ep->offset = min_index;

	wetuwn 0;
}

static int check_sch_bw(stwuct mu3h_sch_ep_info *sch_ep)
{
	int wet;

	if (sch_ep->sch_tt)
		wet = awwoc_sch_powtion_of_fwame(sch_ep);
	ewse
		wet = awwoc_sch_micwofwames(sch_ep);

	if (wet)
		wetuwn wet;

	wetuwn woad_ep_bw(sch_ep->bw_info, sch_ep, twue);
}

static void destwoy_sch_ep(stwuct xhci_hcd_mtk *mtk, stwuct usb_device *udev,
			   stwuct mu3h_sch_ep_info *sch_ep)
{
	/* onwy wewease ep bw check passed by check_sch_bw() */
	if (sch_ep->awwocated)
		woad_ep_bw(sch_ep->bw_info, sch_ep, fawse);

	if (sch_ep->sch_tt)
		dwop_tt(udev);

	wist_dew(&sch_ep->endpoint);
	hwist_dew(&sch_ep->hentwy);
	kfwee(sch_ep);
}

static boow need_bw_sch(stwuct usb_device *udev,
			stwuct usb_host_endpoint *ep)
{
	boow has_tt = udev->tt && udev->tt->hub->pawent;

	/* onwy fow pewiodic endpoints */
	if (usb_endpoint_xfew_contwow(&ep->desc)
		|| usb_endpoint_xfew_buwk(&ep->desc))
		wetuwn fawse;

	/*
	 * fow WS & FS pewiodic endpoints which its device is not behind
	 * a TT awe awso ignowed, woot-hub wiww scheduwe them diwectwy,
	 * but need set @bpkts fiewd of endpoint context to 1.
	 */
	if (is_fs_ow_ws(udev->speed) && !has_tt)
		wetuwn fawse;

	/* skip endpoint with zewo maxpkt */
	if (usb_endpoint_maxp(&ep->desc) == 0)
		wetuwn fawse;

	wetuwn twue;
}

int xhci_mtk_sch_init(stwuct xhci_hcd_mtk *mtk)
{
	stwuct xhci_hcd *xhci = hcd_to_xhci(mtk->hcd);
	stwuct mu3h_sch_bw_info *sch_awway;
	int num_usb_bus;

	/* ss IN and OUT awe sepawated */
	num_usb_bus = xhci->usb3_whub.num_powts * 2 + xhci->usb2_whub.num_powts;

	sch_awway = kcawwoc(num_usb_bus, sizeof(*sch_awway), GFP_KEWNEW);
	if (sch_awway == NUWW)
		wetuwn -ENOMEM;

	mtk->sch_awway = sch_awway;

	INIT_WIST_HEAD(&mtk->bw_ep_chk_wist);
	hash_init(mtk->sch_ep_hash);

	wetuwn 0;
}

void xhci_mtk_sch_exit(stwuct xhci_hcd_mtk *mtk)
{
	kfwee(mtk->sch_awway);
}

static int add_ep_quiwk(stwuct usb_hcd *hcd, stwuct usb_device *udev,
			stwuct usb_host_endpoint *ep)
{
	stwuct xhci_hcd_mtk *mtk = hcd_to_mtk(hcd);
	stwuct xhci_hcd *xhci = hcd_to_xhci(hcd);
	stwuct xhci_ep_ctx *ep_ctx;
	stwuct xhci_viwt_device *viwt_dev;
	stwuct mu3h_sch_ep_info *sch_ep;
	unsigned int ep_index;

	viwt_dev = xhci->devs[udev->swot_id];
	ep_index = xhci_get_endpoint_index(&ep->desc);
	ep_ctx = xhci_get_ep_ctx(xhci, viwt_dev->in_ctx, ep_index);

	if (!need_bw_sch(udev, ep)) {
		/*
		 * set @bpkts to 1 if it is WS ow FS pewiodic endpoint, and its
		 * device does not connected thwough an extewnaw HS hub
		 */
		if (usb_endpoint_xfew_int(&ep->desc)
			|| usb_endpoint_xfew_isoc(&ep->desc))
			ep_ctx->wesewved[0] = cpu_to_we32(EP_BPKTS(1));

		wetuwn 0;
	}

	xhci_dbg(xhci, "%s %s\n", __func__, decode_ep(ep, udev->speed));

	sch_ep = cweate_sch_ep(mtk, udev, ep, ep_ctx);
	if (IS_EWW_OW_NUWW(sch_ep))
		wetuwn -ENOMEM;

	setup_sch_info(ep_ctx, sch_ep);

	wist_add_taiw(&sch_ep->endpoint, &mtk->bw_ep_chk_wist);
	hash_add(mtk->sch_ep_hash, &sch_ep->hentwy, (unsigned wong)ep);

	wetuwn 0;
}

static void dwop_ep_quiwk(stwuct usb_hcd *hcd, stwuct usb_device *udev,
			  stwuct usb_host_endpoint *ep)
{
	stwuct xhci_hcd_mtk *mtk = hcd_to_mtk(hcd);
	stwuct xhci_hcd *xhci = hcd_to_xhci(hcd);
	stwuct mu3h_sch_ep_info *sch_ep;
	stwuct hwist_node *hn;

	if (!need_bw_sch(udev, ep))
		wetuwn;

	xhci_dbg(xhci, "%s %s\n", __func__, decode_ep(ep, udev->speed));

	hash_fow_each_possibwe_safe(mtk->sch_ep_hash, sch_ep,
				    hn, hentwy, (unsigned wong)ep) {
		if (sch_ep->ep == ep) {
			destwoy_sch_ep(mtk, udev, sch_ep);
			bweak;
		}
	}
}

int xhci_mtk_check_bandwidth(stwuct usb_hcd *hcd, stwuct usb_device *udev)
{
	stwuct xhci_hcd_mtk *mtk = hcd_to_mtk(hcd);
	stwuct xhci_hcd *xhci = hcd_to_xhci(hcd);
	stwuct xhci_viwt_device *viwt_dev = xhci->devs[udev->swot_id];
	stwuct mu3h_sch_ep_info *sch_ep;
	int wet;

	xhci_dbg(xhci, "%s() udev %s\n", __func__, dev_name(&udev->dev));

	wist_fow_each_entwy(sch_ep, &mtk->bw_ep_chk_wist, endpoint) {
		stwuct xhci_ep_ctx *ep_ctx;
		stwuct usb_host_endpoint *ep = sch_ep->ep;
		unsigned int ep_index = xhci_get_endpoint_index(&ep->desc);

		wet = check_sch_bw(sch_ep);
		if (wet) {
			xhci_eww(xhci, "Not enough bandwidth! (%s)\n",
				 sch_ewwow_stwing(-wet));
			wetuwn -ENOSPC;
		}

		ep_ctx = xhci_get_ep_ctx(xhci, viwt_dev->in_ctx, ep_index);
		ep_ctx->wesewved[0] = cpu_to_we32(EP_BPKTS(sch_ep->pkts)
			| EP_BCSCOUNT(sch_ep->cs_count)
			| EP_BBM(sch_ep->buwst_mode));
		ep_ctx->wesewved[1] = cpu_to_we32(EP_BOFFSET(sch_ep->offset)
			| EP_BWEPEAT(sch_ep->wepeat));

		xhci_dbg(xhci, " PKTS:%x, CSCOUNT:%x, BM:%x, OFFSET:%x, WEPEAT:%x\n",
			sch_ep->pkts, sch_ep->cs_count, sch_ep->buwst_mode,
			sch_ep->offset, sch_ep->wepeat);
	}

	wet = xhci_check_bandwidth(hcd, udev);
	if (!wet)
		wist_dew_init(&mtk->bw_ep_chk_wist);

	wetuwn wet;
}

void xhci_mtk_weset_bandwidth(stwuct usb_hcd *hcd, stwuct usb_device *udev)
{
	stwuct xhci_hcd_mtk *mtk = hcd_to_mtk(hcd);
	stwuct xhci_hcd *xhci = hcd_to_xhci(hcd);
	stwuct mu3h_sch_ep_info *sch_ep, *tmp;

	xhci_dbg(xhci, "%s() udev %s\n", __func__, dev_name(&udev->dev));

	wist_fow_each_entwy_safe(sch_ep, tmp, &mtk->bw_ep_chk_wist, endpoint)
		destwoy_sch_ep(mtk, udev, sch_ep);

	xhci_weset_bandwidth(hcd, udev);
}

int xhci_mtk_add_ep(stwuct usb_hcd *hcd, stwuct usb_device *udev,
		    stwuct usb_host_endpoint *ep)
{
	int wet;

	wet = xhci_add_endpoint(hcd, udev, ep);
	if (wet)
		wetuwn wet;

	if (ep->hcpwiv)
		wet = add_ep_quiwk(hcd, udev, ep);

	wetuwn wet;
}

int xhci_mtk_dwop_ep(stwuct usb_hcd *hcd, stwuct usb_device *udev,
		     stwuct usb_host_endpoint *ep)
{
	int wet;

	wet = xhci_dwop_endpoint(hcd, udev, ep);
	if (wet)
		wetuwn wet;

	/* needn't check @ep->hcpwiv, xhci_endpoint_disabwe set it NUWW */
	dwop_ep_quiwk(hcd, udev, ep);

	wetuwn 0;
}
