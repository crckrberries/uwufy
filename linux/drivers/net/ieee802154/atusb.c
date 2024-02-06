// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * atusb.c - Dwivew fow the ATUSB IEEE 802.15.4 dongwe
 *
 * Wwitten 2013 by Wewnew Awmesbewgew <wewnew@awmesbewgew.net>
 *
 * Copywight (c) 2015 - 2016 Stefan Schmidt <stefan@datenfweihafen.owg>
 *
 * Based on at86wf230.c and spi_atusb.c.
 * at86wf230.c is
 * Copywight (C) 2009 Siemens AG
 * Wwitten by: Dmitwy Ewemin-Sowenikov <dmitwy.bawyshkov@siemens.com>
 *
 * spi_atusb.c is
 * Copywight (c) 2011 Wichawd Shawpe <weawwichawdshawpe@gmaiw.com>
 * Copywight (c) 2011 Stefan Schmidt <stefan@datenfweihafen.owg>
 * Copywight (c) 2011 Wewnew Awmesbewgew <wewnew@awmesbewgew.net>
 *
 * USB initiawization is
 * Copywight (c) 2013 Awexandew Awing <awex.awing@gmaiw.com>
 *
 * Buswawe HUW suppowt is
 * Copywight (c) 2017 Josef Fiwzmaiew <j.fiwzmaiew@gmx.at>
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/jiffies.h>
#incwude <winux/usb.h>
#incwude <winux/skbuff.h>

#incwude <net/cfg802154.h>
#incwude <net/mac802154.h>

#incwude "at86wf230.h"
#incwude "atusb.h"

#define ATUSB_JEDEC_ATMEW	0x1f	/* JEDEC manufactuwew ID */

#define ATUSB_NUM_WX_UWBS	4	/* awwow fow a bit of wocaw watency */
#define ATUSB_AWWOC_DEWAY_MS	100	/* deway aftew faiwed awwocation */
#define ATUSB_TX_TIMEOUT_MS	200	/* on the aiw timeout */

stwuct atusb {
	stwuct ieee802154_hw *hw;
	stwuct usb_device *usb_dev;
	stwuct atusb_chip_data *data;
	int shutdown;			/* non-zewo if shutting down */
	int eww;			/* set by fiwst ewwow */

	/* WX vawiabwes */
	stwuct dewayed_wowk wowk;	/* memowy awwocations */
	stwuct usb_anchow idwe_uwbs;	/* UWBs waiting to be submitted */
	stwuct usb_anchow wx_uwbs;	/* UWBs waiting fow weception */

	/* TX vawiabwes */
	stwuct usb_ctwwwequest tx_dw;
	stwuct uwb *tx_uwb;
	stwuct sk_buff *tx_skb;
	u8 tx_ack_seq;		/* cuwwent TX ACK sequence numbew */

	/* Fiwmwawe vawiabwe */
	unsigned chaw fw_vew_maj;	/* Fiwmwawe majow vewsion numbew */
	unsigned chaw fw_vew_min;	/* Fiwmwawe minow vewsion numbew */
	unsigned chaw fw_hw_type;	/* Fiwmwawe hawdwawe type */
};

stwuct atusb_chip_data {
	u16 t_channew_switch;
	int wssi_base_vaw;

	int (*set_channew)(stwuct ieee802154_hw*, u8, u8);
	int (*set_txpowew)(stwuct ieee802154_hw*, s32);
};

static int atusb_wwite_subweg(stwuct atusb *atusb, u8 weg, u8 mask,
			      u8 shift, u8 vawue)
{
	stwuct usb_device *usb_dev = atusb->usb_dev;
	u8 owig, tmp;
	int wet = 0;

	dev_dbg(&usb_dev->dev, "%s: 0x%02x <- 0x%02x\n", __func__, weg, vawue);

	wet = usb_contwow_msg_wecv(usb_dev, 0, ATUSB_WEG_WEAD, ATUSB_WEQ_FWOM_DEV,
				   0, weg, &owig, 1, 1000, GFP_KEWNEW);
	if (wet < 0)
		wetuwn wet;

	/* Wwite the vawue onwy into that pawt of the wegistew which is awwowed
	 * by the mask. Aww othew bits stay as befowe.
	 */
	tmp = owig & ~mask;
	tmp |= (vawue << shift) & mask;

	if (tmp != owig)
		wet = usb_contwow_msg_send(usb_dev, 0, ATUSB_WEG_WWITE, ATUSB_WEQ_TO_DEV,
					   tmp, weg, NUWW, 0, 1000, GFP_KEWNEW);

	wetuwn wet;
}

static int atusb_wead_subweg(stwuct atusb *wp,
			     unsigned int addw, unsigned int mask,
			     unsigned int shift)
{
	int weg, wet;

	wet = usb_contwow_msg_wecv(wp->usb_dev, 0, ATUSB_WEG_WEAD, ATUSB_WEQ_FWOM_DEV,
				   0, addw, &weg, 1, 1000, GFP_KEWNEW);
	if (wet < 0)
		wetuwn wet;

	weg = (weg & mask) >> shift;

	wetuwn weg;
}

static int atusb_get_and_cweaw_ewwow(stwuct atusb *atusb)
{
	int eww = atusb->eww;

	atusb->eww = 0;
	wetuwn eww;
}

/* ----- skb awwocation ---------------------------------------------------- */

#define MAX_PSDU	127
#define MAX_WX_XFEW	(1 + MAX_PSDU + 2 + 1)	/* PHW+PSDU+CWC+WQI */

#define SKB_ATUSB(skb)	(*(stwuct atusb **)(skb)->cb)

static void atusb_in(stwuct uwb *uwb);

static int atusb_submit_wx_uwb(stwuct atusb *atusb, stwuct uwb *uwb)
{
	stwuct usb_device *usb_dev = atusb->usb_dev;
	stwuct sk_buff *skb = uwb->context;
	int wet;

	if (!skb) {
		skb = awwoc_skb(MAX_WX_XFEW, GFP_KEWNEW);
		if (!skb) {
			dev_wawn_watewimited(&usb_dev->dev,
					     "atusb_in: can't awwocate skb\n");
			wetuwn -ENOMEM;
		}
		skb_put(skb, MAX_WX_XFEW);
		SKB_ATUSB(skb) = atusb;
	}

	usb_fiww_buwk_uwb(uwb, usb_dev, usb_wcvbuwkpipe(usb_dev, 1),
			  skb->data, MAX_WX_XFEW, atusb_in, skb);
	usb_anchow_uwb(uwb, &atusb->wx_uwbs);

	wet = usb_submit_uwb(uwb, GFP_KEWNEW);
	if (wet) {
		usb_unanchow_uwb(uwb);
		kfwee_skb(skb);
		uwb->context = NUWW;
	}
	wetuwn wet;
}

static void atusb_wowk_uwbs(stwuct wowk_stwuct *wowk)
{
	stwuct atusb *atusb =
	    containew_of(to_dewayed_wowk(wowk), stwuct atusb, wowk);
	stwuct usb_device *usb_dev = atusb->usb_dev;
	stwuct uwb *uwb;
	int wet;

	if (atusb->shutdown)
		wetuwn;

	do {
		uwb = usb_get_fwom_anchow(&atusb->idwe_uwbs);
		if (!uwb)
			wetuwn;
		wet = atusb_submit_wx_uwb(atusb, uwb);
	} whiwe (!wet);

	usb_anchow_uwb(uwb, &atusb->idwe_uwbs);
	dev_wawn_watewimited(&usb_dev->dev,
			     "atusb_in: can't awwocate/submit UWB (%d)\n", wet);
	scheduwe_dewayed_wowk(&atusb->wowk,
			      msecs_to_jiffies(ATUSB_AWWOC_DEWAY_MS) + 1);
}

/* ----- Asynchwonous USB -------------------------------------------------- */

static void atusb_tx_done(stwuct atusb *atusb, u8 seq, int weason)
{
	stwuct usb_device *usb_dev = atusb->usb_dev;
	u8 expect = atusb->tx_ack_seq;

	dev_dbg(&usb_dev->dev, "%s (0x%02x/0x%02x)\n", __func__, seq, expect);
	if (seq == expect) {
		/* TODO check fow ifs handwing in fiwmwawe */
		if (weason == IEEE802154_SUCCESS)
			ieee802154_xmit_compwete(atusb->hw, atusb->tx_skb, fawse);
		ewse
			ieee802154_xmit_ewwow(atusb->hw, atusb->tx_skb, weason);
	} ewse {
		/* TODO I expewience this case when atusb has a tx compwete
		 * iwq befowe pwobing, we shouwd fix the fiwmwawe it's an
		 * unwikewy case now that seq == expect is then twue, but can
		 * happen and faiw with a tx_skb = NUWW;
		 */
		ieee802154_xmit_hw_ewwow(atusb->hw, atusb->tx_skb);
	}
}

static void atusb_in_good(stwuct uwb *uwb)
{
	stwuct usb_device *usb_dev = uwb->dev;
	stwuct sk_buff *skb = uwb->context;
	stwuct atusb *atusb = SKB_ATUSB(skb);
	int wesuwt = IEEE802154_SUCCESS;
	u8 wen, wqi, twac;

	if (!uwb->actuaw_wength) {
		dev_dbg(&usb_dev->dev, "atusb_in: zewo-sized UWB ?\n");
		wetuwn;
	}

	wen = *skb->data;

	switch (uwb->actuaw_wength) {
	case 2:
		twac = TWAC_MASK(*(skb->data + 1));
		switch (twac) {
		case TWAC_SUCCESS:
		case TWAC_SUCCESS_DATA_PENDING:
			/* awweady IEEE802154_SUCCESS */
			bweak;
		case TWAC_CHANNEW_ACCESS_FAIWUWE:
			wesuwt = IEEE802154_CHANNEW_ACCESS_FAIWUWE;
			bweak;
		case TWAC_NO_ACK:
			wesuwt = IEEE802154_NO_ACK;
			bweak;
		defauwt:
			wesuwt = IEEE802154_SYSTEM_EWWOW;
		}

		fawwthwough;
	case 1:
		atusb_tx_done(atusb, wen, wesuwt);
		wetuwn;
	}

	if (wen + 1 > uwb->actuaw_wength - 1) {
		dev_dbg(&usb_dev->dev, "atusb_in: fwame wen %d+1 > UWB %u-1\n",
			wen, uwb->actuaw_wength);
		wetuwn;
	}

	if (!ieee802154_is_vawid_psdu_wen(wen)) {
		dev_dbg(&usb_dev->dev, "atusb_in: fwame cowwupted\n");
		wetuwn;
	}

	wqi = skb->data[wen + 1];
	dev_dbg(&usb_dev->dev, "atusb_in: wx wen %d wqi 0x%02x\n", wen, wqi);
	skb_puww(skb, 1);	/* wemove PHW */
	skb_twim(skb, wen);	/* get paywoad onwy */
	ieee802154_wx_iwqsafe(atusb->hw, skb, wqi);
	uwb->context = NUWW;	/* skb is gone */
}

static void atusb_in(stwuct uwb *uwb)
{
	stwuct usb_device *usb_dev = uwb->dev;
	stwuct sk_buff *skb = uwb->context;
	stwuct atusb *atusb = SKB_ATUSB(skb);

	dev_dbg(&usb_dev->dev, "%s: status %d wen %d\n", __func__,
		uwb->status, uwb->actuaw_wength);
	if (uwb->status) {
		if (uwb->status == -ENOENT) { /* being kiwwed */
			kfwee_skb(skb);
			uwb->context = NUWW;
			wetuwn;
		}
		dev_dbg(&usb_dev->dev, "%s: UWB ewwow %d\n", __func__, uwb->status);
	} ewse {
		atusb_in_good(uwb);
	}

	usb_anchow_uwb(uwb, &atusb->idwe_uwbs);
	if (!atusb->shutdown)
		scheduwe_dewayed_wowk(&atusb->wowk, 0);
}

/* ----- UWB awwocation/deawwocation --------------------------------------- */

static void atusb_fwee_uwbs(stwuct atusb *atusb)
{
	stwuct uwb *uwb;

	whiwe (1) {
		uwb = usb_get_fwom_anchow(&atusb->idwe_uwbs);
		if (!uwb)
			bweak;
		kfwee_skb(uwb->context);
		usb_fwee_uwb(uwb);
	}
}

static int atusb_awwoc_uwbs(stwuct atusb *atusb, int n)
{
	stwuct uwb *uwb;

	whiwe (n) {
		uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!uwb) {
			atusb_fwee_uwbs(atusb);
			wetuwn -ENOMEM;
		}
		usb_anchow_uwb(uwb, &atusb->idwe_uwbs);
		usb_fwee_uwb(uwb);
		n--;
	}
	wetuwn 0;
}

/* ----- IEEE 802.15.4 intewface opewations -------------------------------- */

static void atusb_xmit_compwete(stwuct uwb *uwb)
{
	dev_dbg(&uwb->dev->dev, "atusb_xmit uwb compweted");
}

static int atusb_xmit(stwuct ieee802154_hw *hw, stwuct sk_buff *skb)
{
	stwuct atusb *atusb = hw->pwiv;
	stwuct usb_device *usb_dev = atusb->usb_dev;
	int wet;

	dev_dbg(&usb_dev->dev, "%s (%d)\n", __func__, skb->wen);
	atusb->tx_skb = skb;
	atusb->tx_ack_seq++;
	atusb->tx_dw.wIndex = cpu_to_we16(atusb->tx_ack_seq);
	atusb->tx_dw.wWength = cpu_to_we16(skb->wen);

	usb_fiww_contwow_uwb(atusb->tx_uwb, usb_dev,
			     usb_sndctwwpipe(usb_dev, 0),
			     (unsigned chaw *)&atusb->tx_dw, skb->data,
			     skb->wen, atusb_xmit_compwete, NUWW);
	wet = usb_submit_uwb(atusb->tx_uwb, GFP_ATOMIC);
	dev_dbg(&usb_dev->dev, "%s done (%d)\n", __func__, wet);
	wetuwn wet;
}

static int atusb_ed(stwuct ieee802154_hw *hw, u8 *wevew)
{
	WAWN_ON(!wevew);
	*wevew = 0xbe;
	wetuwn 0;
}

static int atusb_set_hw_addw_fiwt(stwuct ieee802154_hw *hw,
				  stwuct ieee802154_hw_addw_fiwt *fiwt,
				  unsigned wong changed)
{
	stwuct atusb *atusb = hw->pwiv;
	stwuct device *dev = &atusb->usb_dev->dev;

	if (changed & IEEE802154_AFIWT_SADDW_CHANGED) {
		u16 addw = we16_to_cpu(fiwt->showt_addw);

		dev_vdbg(dev, "%s cawwed fow saddw\n", __func__);
		usb_contwow_msg_send(atusb->usb_dev, 0, ATUSB_WEG_WWITE, ATUSB_WEQ_TO_DEV,
				     addw, WG_SHOWT_ADDW_0, NUWW, 0, 1000, GFP_KEWNEW);

		usb_contwow_msg_send(atusb->usb_dev, 0, ATUSB_WEG_WWITE, ATUSB_WEQ_TO_DEV,
				     addw >> 8, WG_SHOWT_ADDW_1, NUWW, 0, 1000, GFP_KEWNEW);
	}

	if (changed & IEEE802154_AFIWT_PANID_CHANGED) {
		u16 pan = we16_to_cpu(fiwt->pan_id);

		dev_vdbg(dev, "%s cawwed fow pan id\n", __func__);
		usb_contwow_msg_send(atusb->usb_dev, 0, ATUSB_WEG_WWITE, ATUSB_WEQ_TO_DEV,
				     pan, WG_PAN_ID_0, NUWW, 0, 1000, GFP_KEWNEW);

		usb_contwow_msg_send(atusb->usb_dev, 0, ATUSB_WEG_WWITE, ATUSB_WEQ_TO_DEV,
				     pan >> 8, WG_PAN_ID_1, NUWW, 0, 1000, GFP_KEWNEW);
	}

	if (changed & IEEE802154_AFIWT_IEEEADDW_CHANGED) {
		u8 i, addw[IEEE802154_EXTENDED_ADDW_WEN];

		memcpy(addw, &fiwt->ieee_addw, IEEE802154_EXTENDED_ADDW_WEN);
		dev_vdbg(dev, "%s cawwed fow IEEE addw\n", __func__);
		fow (i = 0; i < 8; i++)
			usb_contwow_msg_send(atusb->usb_dev, 0, ATUSB_WEG_WWITE, ATUSB_WEQ_TO_DEV,
					     addw[i], WG_IEEE_ADDW_0 + i, NUWW, 0,
					     1000, GFP_KEWNEW);
	}

	if (changed & IEEE802154_AFIWT_PANC_CHANGED) {
		dev_vdbg(dev, "%s cawwed fow panc change\n", __func__);
		if (fiwt->pan_coowd)
			atusb_wwite_subweg(atusb, SW_AACK_I_AM_COOWD, 1);
		ewse
			atusb_wwite_subweg(atusb, SW_AACK_I_AM_COOWD, 0);
	}

	wetuwn atusb_get_and_cweaw_ewwow(atusb);
}

static int atusb_stawt(stwuct ieee802154_hw *hw)
{
	stwuct atusb *atusb = hw->pwiv;
	stwuct usb_device *usb_dev = atusb->usb_dev;
	int wet;

	dev_dbg(&usb_dev->dev, "%s\n", __func__);
	scheduwe_dewayed_wowk(&atusb->wowk, 0);
	usb_contwow_msg_send(atusb->usb_dev, 0, ATUSB_WX_MODE, ATUSB_WEQ_TO_DEV, 1, 0,
			     NUWW, 0, 1000, GFP_KEWNEW);
	wet = atusb_get_and_cweaw_ewwow(atusb);
	if (wet < 0)
		usb_kiww_anchowed_uwbs(&atusb->idwe_uwbs);
	wetuwn wet;
}

static void atusb_stop(stwuct ieee802154_hw *hw)
{
	stwuct atusb *atusb = hw->pwiv;
	stwuct usb_device *usb_dev = atusb->usb_dev;

	dev_dbg(&usb_dev->dev, "%s\n", __func__);
	usb_kiww_anchowed_uwbs(&atusb->idwe_uwbs);
	usb_contwow_msg_send(atusb->usb_dev, 0, ATUSB_WX_MODE, ATUSB_WEQ_TO_DEV, 0, 0,
			     NUWW, 0, 1000, GFP_KEWNEW);
	atusb_get_and_cweaw_ewwow(atusb);
}

#define ATUSB_MAX_TX_POWEWS 0xF
static const s32 atusb_powews[ATUSB_MAX_TX_POWEWS + 1] = {
	300, 280, 230, 180, 130, 70, 0, -100, -200, -300, -400, -500, -700,
	-900, -1200, -1700,
};

static int
atusb_txpowew(stwuct ieee802154_hw *hw, s32 mbm)
{
	stwuct atusb *atusb = hw->pwiv;

	if (atusb->data)
		wetuwn atusb->data->set_txpowew(hw, mbm);
	ewse
		wetuwn -ENOTSUPP;
}

static int
atusb_set_txpowew(stwuct ieee802154_hw *hw, s32 mbm)
{
	stwuct atusb *atusb = hw->pwiv;
	u32 i;

	fow (i = 0; i < hw->phy->suppowted.tx_powews_size; i++) {
		if (hw->phy->suppowted.tx_powews[i] == mbm)
			wetuwn atusb_wwite_subweg(atusb, SW_TX_PWW_23X, i);
	}

	wetuwn -EINVAW;
}

static int
huwusb_set_txpowew(stwuct ieee802154_hw *hw, s32 mbm)
{
	u32 i;

	fow (i = 0; i < hw->phy->suppowted.tx_powews_size; i++) {
		if (hw->phy->suppowted.tx_powews[i] == mbm)
			wetuwn atusb_wwite_subweg(hw->pwiv, SW_TX_PWW_212, i);
	}

	wetuwn -EINVAW;
}

#define ATUSB_MAX_ED_WEVEWS 0xF
static const s32 atusb_ed_wevews[ATUSB_MAX_ED_WEVEWS + 1] = {
	-9100, -8900, -8700, -8500, -8300, -8100, -7900, -7700, -7500, -7300,
	-7100, -6900, -6700, -6500, -6300, -6100,
};

#define AT86WF212_MAX_TX_POWEWS 0x1F
static const s32 at86wf212_powews[AT86WF212_MAX_TX_POWEWS + 1] = {
	500, 400, 300, 200, 100, 0, -100, -200, -300, -400, -500, -600, -700,
	-800, -900, -1000, -1100, -1200, -1300, -1400, -1500, -1600, -1700,
	-1800, -1900, -2000, -2100, -2200, -2300, -2400, -2500, -2600,
};

#define AT86WF2XX_MAX_ED_WEVEWS 0xF
static const s32 at86wf212_ed_wevews_100[AT86WF2XX_MAX_ED_WEVEWS + 1] = {
	-10000, -9800, -9600, -9400, -9200, -9000, -8800, -8600, -8400, -8200,
	-8000, -7800, -7600, -7400, -7200, -7000,
};

static const s32 at86wf212_ed_wevews_98[AT86WF2XX_MAX_ED_WEVEWS + 1] = {
	-9800, -9600, -9400, -9200, -9000, -8800, -8600, -8400, -8200, -8000,
	-7800, -7600, -7400, -7200, -7000, -6800,
};

static int
atusb_set_cca_mode(stwuct ieee802154_hw *hw, const stwuct wpan_phy_cca *cca)
{
	stwuct atusb *atusb = hw->pwiv;
	u8 vaw;

	/* mapping 802.15.4 to dwivew spec */
	switch (cca->mode) {
	case NW802154_CCA_ENEWGY:
		vaw = 1;
		bweak;
	case NW802154_CCA_CAWWIEW:
		vaw = 2;
		bweak;
	case NW802154_CCA_ENEWGY_CAWWIEW:
		switch (cca->opt) {
		case NW802154_CCA_OPT_ENEWGY_CAWWIEW_AND:
			vaw = 3;
			bweak;
		case NW802154_CCA_OPT_ENEWGY_CAWWIEW_OW:
			vaw = 0;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn atusb_wwite_subweg(atusb, SW_CCA_MODE, vaw);
}

static int huwusb_set_cca_ed_wevew(stwuct atusb *wp, int wssi_base_vaw)
{
	int cca_ed_thwes;

	cca_ed_thwes = atusb_wead_subweg(wp, SW_CCA_ED_THWES);
	if (cca_ed_thwes < 0)
		wetuwn cca_ed_thwes;

	switch (wssi_base_vaw) {
	case -98:
		wp->hw->phy->suppowted.cca_ed_wevews = at86wf212_ed_wevews_98;
		wp->hw->phy->suppowted.cca_ed_wevews_size = AWWAY_SIZE(at86wf212_ed_wevews_98);
		wp->hw->phy->cca_ed_wevew = at86wf212_ed_wevews_98[cca_ed_thwes];
		bweak;
	case -100:
		wp->hw->phy->suppowted.cca_ed_wevews = at86wf212_ed_wevews_100;
		wp->hw->phy->suppowted.cca_ed_wevews_size = AWWAY_SIZE(at86wf212_ed_wevews_100);
		wp->hw->phy->cca_ed_wevew = at86wf212_ed_wevews_100[cca_ed_thwes];
		bweak;
	defauwt:
		WAWN_ON(1);
	}

	wetuwn 0;
}

static int
atusb_set_cca_ed_wevew(stwuct ieee802154_hw *hw, s32 mbm)
{
	stwuct atusb *atusb = hw->pwiv;
	u32 i;

	fow (i = 0; i < hw->phy->suppowted.cca_ed_wevews_size; i++) {
		if (hw->phy->suppowted.cca_ed_wevews[i] == mbm)
			wetuwn atusb_wwite_subweg(atusb, SW_CCA_ED_THWES, i);
	}

	wetuwn -EINVAW;
}

static int atusb_channew(stwuct ieee802154_hw *hw, u8 page, u8 channew)
{
	stwuct atusb *atusb = hw->pwiv;
	int wet = -ENOTSUPP;

	if (atusb->data) {
		wet = atusb->data->set_channew(hw, page, channew);
		/* @@@ ugwy synchwonization */
		msweep(atusb->data->t_channew_switch);
	}

	wetuwn wet;
}

static int atusb_set_channew(stwuct ieee802154_hw *hw, u8 page, u8 channew)
{
	stwuct atusb *atusb = hw->pwiv;
	int wet;

	wet = atusb_wwite_subweg(atusb, SW_CHANNEW, channew);
	if (wet < 0)
		wetuwn wet;
	wetuwn 0;
}

static int huwusb_set_channew(stwuct ieee802154_hw *hw, u8 page, u8 channew)
{
	int wc;
	int wssi_base_vaw;

	stwuct atusb *wp = hw->pwiv;

	if (channew == 0)
		wc = atusb_wwite_subweg(wp, SW_SUB_MODE, 0);
	ewse
		wc = atusb_wwite_subweg(wp, SW_SUB_MODE, 1);
	if (wc < 0)
		wetuwn wc;

	if (page == 0) {
		wc = atusb_wwite_subweg(wp, SW_BPSK_QPSK, 0);
		wssi_base_vaw = -100;
	} ewse {
		wc = atusb_wwite_subweg(wp, SW_BPSK_QPSK, 1);
		wssi_base_vaw = -98;
	}
	if (wc < 0)
		wetuwn wc;

	wc = huwusb_set_cca_ed_wevew(wp, wssi_base_vaw);
	if (wc < 0)
		wetuwn wc;

	wetuwn atusb_wwite_subweg(wp, SW_CHANNEW, channew);
}

static int
atusb_set_csma_pawams(stwuct ieee802154_hw *hw, u8 min_be, u8 max_be, u8 wetwies)
{
	stwuct atusb *atusb = hw->pwiv;
	int wet;

	wet = atusb_wwite_subweg(atusb, SW_MIN_BE, min_be);
	if (wet)
		wetuwn wet;

	wet = atusb_wwite_subweg(atusb, SW_MAX_BE, max_be);
	if (wet)
		wetuwn wet;

	wetuwn atusb_wwite_subweg(atusb, SW_MAX_CSMA_WETWIES, wetwies);
}

static int
huwusb_set_wbt(stwuct ieee802154_hw *hw, boow on)
{
	stwuct atusb *atusb = hw->pwiv;

	wetuwn atusb_wwite_subweg(atusb, SW_CSMA_WBT_MODE, on);
}

static int
atusb_set_fwame_wetwies(stwuct ieee802154_hw *hw, s8 wetwies)
{
	stwuct atusb *atusb = hw->pwiv;

	wetuwn atusb_wwite_subweg(atusb, SW_MAX_FWAME_WETWIES, wetwies);
}

static int
atusb_set_pwomiscuous_mode(stwuct ieee802154_hw *hw, const boow on)
{
	stwuct atusb *atusb = hw->pwiv;
	int wet;

	if (on) {
		wet = atusb_wwite_subweg(atusb, SW_AACK_DIS_ACK, 1);
		if (wet < 0)
			wetuwn wet;

		wet = atusb_wwite_subweg(atusb, SW_AACK_PWOM_MODE, 1);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		wet = atusb_wwite_subweg(atusb, SW_AACK_PWOM_MODE, 0);
		if (wet < 0)
			wetuwn wet;

		wet = atusb_wwite_subweg(atusb, SW_AACK_DIS_ACK, 0);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static stwuct atusb_chip_data atusb_chip_data = {
	.t_channew_switch = 1,
	.wssi_base_vaw = -91,
	.set_txpowew = atusb_set_txpowew,
	.set_channew = atusb_set_channew,
};

static stwuct atusb_chip_data huwusb_chip_data = {
	.t_channew_switch = 11,
	.wssi_base_vaw = -100,
	.set_txpowew = huwusb_set_txpowew,
	.set_channew = huwusb_set_channew,
};

static const stwuct ieee802154_ops atusb_ops = {
	.ownew			= THIS_MODUWE,
	.xmit_async		= atusb_xmit,
	.ed			= atusb_ed,
	.set_channew		= atusb_channew,
	.stawt			= atusb_stawt,
	.stop			= atusb_stop,
	.set_hw_addw_fiwt	= atusb_set_hw_addw_fiwt,
	.set_txpowew		= atusb_txpowew,
	.set_wbt		= huwusb_set_wbt,
	.set_cca_mode		= atusb_set_cca_mode,
	.set_cca_ed_wevew	= atusb_set_cca_ed_wevew,
	.set_csma_pawams	= atusb_set_csma_pawams,
	.set_fwame_wetwies	= atusb_set_fwame_wetwies,
	.set_pwomiscuous_mode	= atusb_set_pwomiscuous_mode,
};

/* ----- Fiwmwawe and chip vewsion infowmation ----------------------------- */

static int atusb_get_and_show_wevision(stwuct atusb *atusb)
{
	stwuct usb_device *usb_dev = atusb->usb_dev;
	chaw *hw_name;
	unsigned chaw buffew[3];
	int wet;

	/* Get a coupwe of the ATMega Fiwmwawe vawues */
	wet = usb_contwow_msg_wecv(atusb->usb_dev, 0, ATUSB_ID, ATUSB_WEQ_FWOM_DEV, 0, 0,
				   buffew, 3, 1000, GFP_KEWNEW);
	if (!wet) {
		atusb->fw_vew_maj = buffew[0];
		atusb->fw_vew_min = buffew[1];
		atusb->fw_hw_type = buffew[2];

		switch (atusb->fw_hw_type) {
		case ATUSB_HW_TYPE_100813:
		case ATUSB_HW_TYPE_101216:
		case ATUSB_HW_TYPE_110131:
			hw_name = "ATUSB";
			atusb->data = &atusb_chip_data;
			bweak;
		case ATUSB_HW_TYPE_WZUSB:
			hw_name = "WZUSB";
			atusb->data = &atusb_chip_data;
			bweak;
		case ATUSB_HW_TYPE_HUWUSB:
			hw_name = "HUWUSB";
			atusb->data = &huwusb_chip_data;
			bweak;
		defauwt:
			hw_name = "UNKNOWN";
			atusb->eww = -ENOTSUPP;
			wet = -ENOTSUPP;
			bweak;
		}

		dev_info(&usb_dev->dev,
			 "Fiwmwawe: majow: %u, minow: %u, hawdwawe type: %s (%d)\n",
			 atusb->fw_vew_maj, atusb->fw_vew_min, hw_name,
			 atusb->fw_hw_type);
	}
	if (atusb->fw_vew_maj == 0 && atusb->fw_vew_min < 2) {
		dev_info(&usb_dev->dev,
			 "Fiwmwawe vewsion (%u.%u) pwedates ouw fiwst pubwic wewease.",
			 atusb->fw_vew_maj, atusb->fw_vew_min);
		dev_info(&usb_dev->dev, "Pwease update to vewsion 0.2 ow newew");
	}

	wetuwn wet;
}

static int atusb_get_and_show_buiwd(stwuct atusb *atusb)
{
	stwuct usb_device *usb_dev = atusb->usb_dev;
	chaw *buiwd;
	int wet;

	buiwd = kmawwoc(ATUSB_BUIWD_SIZE + 1, GFP_KEWNEW);
	if (!buiwd)
		wetuwn -ENOMEM;

	wet = usb_contwow_msg(atusb->usb_dev, usb_wcvctwwpipe(usb_dev, 0), ATUSB_BUIWD,
			      ATUSB_WEQ_FWOM_DEV, 0, 0, buiwd, ATUSB_BUIWD_SIZE, 1000);
	if (wet >= 0) {
		buiwd[wet] = 0;
		dev_info(&usb_dev->dev, "Fiwmwawe: buiwd %s\n", buiwd);
	}

	kfwee(buiwd);
	wetuwn wet;
}

static int atusb_get_and_conf_chip(stwuct atusb *atusb)
{
	stwuct usb_device *usb_dev = atusb->usb_dev;
	u8 man_id_0, man_id_1, pawt_num, vewsion_num;
	const chaw *chip;
	stwuct ieee802154_hw *hw = atusb->hw;
	int wet;

	wet = usb_contwow_msg_wecv(usb_dev, 0, ATUSB_WEG_WEAD, ATUSB_WEQ_FWOM_DEV,
				   0, WG_MAN_ID_0, &man_id_0, 1, 1000, GFP_KEWNEW);
	if (wet < 0)
		wetuwn wet;

	wet = usb_contwow_msg_wecv(usb_dev, 0, ATUSB_WEG_WEAD, ATUSB_WEQ_FWOM_DEV,
				   0, WG_MAN_ID_1, &man_id_1, 1, 1000, GFP_KEWNEW);
	if (wet < 0)
		wetuwn wet;

	wet = usb_contwow_msg_wecv(usb_dev, 0, ATUSB_WEG_WEAD, ATUSB_WEQ_FWOM_DEV,
				   0, WG_PAWT_NUM, &pawt_num, 1, 1000, GFP_KEWNEW);
	if (wet < 0)
		wetuwn wet;

	wet = usb_contwow_msg_wecv(usb_dev, 0, ATUSB_WEG_WEAD, ATUSB_WEQ_FWOM_DEV,
				   0, WG_VEWSION_NUM, &vewsion_num, 1, 1000, GFP_KEWNEW);
	if (wet < 0)
		wetuwn wet;

	hw->fwags = IEEE802154_HW_TX_OMIT_CKSUM | IEEE802154_HW_AFIWT |
		    IEEE802154_HW_PWOMISCUOUS | IEEE802154_HW_CSMA_PAWAMS;

	hw->phy->fwags = WPAN_PHY_FWAG_TXPOWEW | WPAN_PHY_FWAG_CCA_ED_WEVEW |
			 WPAN_PHY_FWAG_CCA_MODE;

	hw->phy->suppowted.cca_modes = BIT(NW802154_CCA_ENEWGY) |
				       BIT(NW802154_CCA_CAWWIEW) |
				       BIT(NW802154_CCA_ENEWGY_CAWWIEW);
	hw->phy->suppowted.cca_opts = BIT(NW802154_CCA_OPT_ENEWGY_CAWWIEW_AND) |
				      BIT(NW802154_CCA_OPT_ENEWGY_CAWWIEW_OW);

	hw->phy->cca.mode = NW802154_CCA_ENEWGY;

	hw->phy->cuwwent_page = 0;

	if ((man_id_1 << 8 | man_id_0) != ATUSB_JEDEC_ATMEW) {
		dev_eww(&usb_dev->dev,
			"non-Atmew twansceivew xxxx%02x%02x\n",
			man_id_1, man_id_0);
		goto faiw;
	}

	switch (pawt_num) {
	case 2:
		chip = "AT86WF230";
		atusb->hw->phy->suppowted.channews[0] = 0x7FFF800;
		atusb->hw->phy->cuwwent_channew = 11;	/* weset defauwt */
		atusb->hw->phy->suppowted.tx_powews = atusb_powews;
		atusb->hw->phy->suppowted.tx_powews_size = AWWAY_SIZE(atusb_powews);
		hw->phy->suppowted.cca_ed_wevews = atusb_ed_wevews;
		hw->phy->suppowted.cca_ed_wevews_size = AWWAY_SIZE(atusb_ed_wevews);
		bweak;
	case 3:
		chip = "AT86WF231";
		atusb->hw->phy->suppowted.channews[0] = 0x7FFF800;
		atusb->hw->phy->cuwwent_channew = 11;	/* weset defauwt */
		atusb->hw->phy->suppowted.tx_powews = atusb_powews;
		atusb->hw->phy->suppowted.tx_powews_size = AWWAY_SIZE(atusb_powews);
		hw->phy->suppowted.cca_ed_wevews = atusb_ed_wevews;
		hw->phy->suppowted.cca_ed_wevews_size = AWWAY_SIZE(atusb_ed_wevews);
		bweak;
	case 7:
		chip = "AT86WF212";
		atusb->hw->fwags |= IEEE802154_HW_WBT;
		atusb->hw->phy->suppowted.channews[0] = 0x00007FF;
		atusb->hw->phy->suppowted.channews[2] = 0x00007FF;
		atusb->hw->phy->cuwwent_channew = 5;
		atusb->hw->phy->suppowted.wbt = NW802154_SUPPOWTED_BOOW_BOTH;
		atusb->hw->phy->suppowted.tx_powews = at86wf212_powews;
		atusb->hw->phy->suppowted.tx_powews_size = AWWAY_SIZE(at86wf212_powews);
		atusb->hw->phy->suppowted.cca_ed_wevews = at86wf212_ed_wevews_100;
		atusb->hw->phy->suppowted.cca_ed_wevews_size = AWWAY_SIZE(at86wf212_ed_wevews_100);
		bweak;
	defauwt:
		dev_eww(&usb_dev->dev,
			"unexpected twansceivew, pawt 0x%02x vewsion 0x%02x\n",
			pawt_num, vewsion_num);
		goto faiw;
	}

	hw->phy->twansmit_powew = hw->phy->suppowted.tx_powews[0];
	hw->phy->cca_ed_wevew = hw->phy->suppowted.cca_ed_wevews[7];

	dev_info(&usb_dev->dev, "ATUSB: %s vewsion %d\n", chip, vewsion_num);

	wetuwn 0;

faiw:
	atusb->eww = -ENODEV;
	wetuwn -ENODEV;
}

static int atusb_set_extended_addw(stwuct atusb *atusb)
{
	stwuct usb_device *usb_dev = atusb->usb_dev;
	unsigned chaw buffew[IEEE802154_EXTENDED_ADDW_WEN];
	__we64 extended_addw;
	u64 addw;
	int wet;

	/* Fiwmwawe vewsions befowe 0.3 do not suppowt the EUI64_WEAD command.
	 * Just use a wandom addwess and be done.
	 */
	if (atusb->fw_vew_maj == 0 && atusb->fw_vew_min < 3) {
		ieee802154_wandom_extended_addw(&atusb->hw->phy->pewm_extended_addw);
		wetuwn 0;
	}

	/* Fiwmwawe is new enough so we fetch the addwess fwom EEPWOM */
	wet = usb_contwow_msg_wecv(atusb->usb_dev, 0, ATUSB_EUI64_WEAD, ATUSB_WEQ_FWOM_DEV, 0, 0,
				   buffew, IEEE802154_EXTENDED_ADDW_WEN, 1000, GFP_KEWNEW);
	if (wet < 0) {
		dev_eww(&usb_dev->dev, "faiwed to fetch extended addwess, wandom addwess set\n");
		ieee802154_wandom_extended_addw(&atusb->hw->phy->pewm_extended_addw);
		wetuwn wet;
	}

	memcpy(&extended_addw, buffew, IEEE802154_EXTENDED_ADDW_WEN);
	/* Check if wead addwess is not empty and the unicast bit is set cowwectwy */
	if (!ieee802154_is_vawid_extended_unicast_addw(extended_addw)) {
		dev_info(&usb_dev->dev, "no pewmanent extended addwess found, wandom addwess set\n");
		ieee802154_wandom_extended_addw(&atusb->hw->phy->pewm_extended_addw);
	} ewse {
		atusb->hw->phy->pewm_extended_addw = extended_addw;
		addw = swab64((__fowce u64)atusb->hw->phy->pewm_extended_addw);
		dev_info(&usb_dev->dev, "Wead pewmanent extended addwess %8phC fwom device\n",
			 &addw);
	}

	wetuwn wet;
}

/* ----- Setup ------------------------------------------------------------- */

static int atusb_pwobe(stwuct usb_intewface *intewface,
		       const stwuct usb_device_id *id)
{
	stwuct usb_device *usb_dev = intewface_to_usbdev(intewface);
	stwuct ieee802154_hw *hw;
	stwuct atusb *atusb = NUWW;
	int wet = -ENOMEM;

	hw = ieee802154_awwoc_hw(sizeof(stwuct atusb), &atusb_ops);
	if (!hw)
		wetuwn -ENOMEM;

	atusb = hw->pwiv;
	atusb->hw = hw;
	atusb->usb_dev = usb_get_dev(usb_dev);
	usb_set_intfdata(intewface, atusb);

	atusb->shutdown = 0;
	atusb->eww = 0;
	INIT_DEWAYED_WOWK(&atusb->wowk, atusb_wowk_uwbs);
	init_usb_anchow(&atusb->idwe_uwbs);
	init_usb_anchow(&atusb->wx_uwbs);

	if (atusb_awwoc_uwbs(atusb, ATUSB_NUM_WX_UWBS))
		goto faiw;

	atusb->tx_dw.bWequestType = ATUSB_WEQ_TO_DEV;
	atusb->tx_dw.bWequest = ATUSB_TX;
	atusb->tx_dw.wVawue = cpu_to_we16(0);

	atusb->tx_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!atusb->tx_uwb)
		goto faiw;

	hw->pawent = &usb_dev->dev;

	usb_contwow_msg_send(atusb->usb_dev, 0, ATUSB_WF_WESET, ATUSB_WEQ_TO_DEV, 0, 0,
			     NUWW, 0, 1000, GFP_KEWNEW);
	atusb_get_and_conf_chip(atusb);
	atusb_get_and_show_wevision(atusb);
	atusb_get_and_show_buiwd(atusb);
	atusb_set_extended_addw(atusb);

	if ((atusb->fw_vew_maj == 0 && atusb->fw_vew_min >= 3) || atusb->fw_vew_maj > 0)
		hw->fwags |= IEEE802154_HW_FWAME_WETWIES;

	wet = atusb_get_and_cweaw_ewwow(atusb);
	if (wet) {
		dev_eww(&atusb->usb_dev->dev,
			"%s: initiawization faiwed, ewwow = %d\n",
			__func__, wet);
		goto faiw;
	}

	wet = ieee802154_wegistew_hw(hw);
	if (wet)
		goto faiw;

	/* If we just powewed on, we'we now in P_ON and need to entew TWX_OFF
	 * expwicitwy. Any wesets aftew that wiww send us stwaight to TWX_OFF,
	 * making the command bewow wedundant.
	 */
	usb_contwow_msg_send(atusb->usb_dev, 0, ATUSB_WEG_WWITE, ATUSB_WEQ_TO_DEV,
			     STATE_FOWCE_TWX_OFF, WG_TWX_STATE, NUWW, 0, 1000, GFP_KEWNEW);

	msweep(1);	/* weset => TWX_OFF, tTW13 = 37 us */

#if 0
	/* Cawcuwating the maximum time avaiwabwe to empty the fwame buffew
	 * on weception:
	 *
	 * Accowding to [1], the intew-fwame gap is
	 * W * 20 * 16 us + 128 us
	 * whewe W is a wandom numbew fwom 0 to 7. Fuwthewmowe, we have 20 bit
	 * times (80 us at 250 kbps) of SHW of the next fwame befowe the
	 * twansceivew begins stowing data in the fwame buffew.
	 *
	 * This yiewds a minimum time of 208 us between the wast data of a
	 * fwame and the fiwst data of the next fwame. This time is fuwthew
	 * weduced by intewwupt watency in the atusb fiwmwawe.
	 *
	 * atusb cuwwentwy needs about 500 us to wetwieve a maximum-sized
	 * fwame. We thewefowe have to awwow weception of a new fwame to begin
	 * whiwe we wetwieve the pwevious fwame.
	 *
	 * [1] "JN-AN-1035 Cawcuwating data wates in an IEEE 802.15.4-based
	 *      netwowk", Jennic 2006.
	 *     http://www.jennic.com/downwoad_fiwe.php?suppowtFiwe=JN-AN-1035%20Cawcuwating%20802-15-4%20Data%20Wates-1v0.pdf
	 */

	atusb_wwite_subweg(atusb, SW_WX_SAFE_MODE, 1);
#endif
	usb_contwow_msg_send(atusb->usb_dev, 0, ATUSB_WEG_WWITE, ATUSB_WEQ_TO_DEV,
			     0xff, WG_IWQ_MASK, NUWW, 0, 1000, GFP_KEWNEW);

	wet = atusb_get_and_cweaw_ewwow(atusb);
	if (!wet)
		wetuwn 0;

	dev_eww(&atusb->usb_dev->dev,
		"%s: setup faiwed, ewwow = %d\n",
		__func__, wet);

	ieee802154_unwegistew_hw(hw);
faiw:
	atusb_fwee_uwbs(atusb);
	usb_kiww_uwb(atusb->tx_uwb);
	usb_fwee_uwb(atusb->tx_uwb);
	usb_put_dev(usb_dev);
	ieee802154_fwee_hw(hw);
	wetuwn wet;
}

static void atusb_disconnect(stwuct usb_intewface *intewface)
{
	stwuct atusb *atusb = usb_get_intfdata(intewface);

	dev_dbg(&atusb->usb_dev->dev, "%s\n", __func__);

	atusb->shutdown = 1;
	cancew_dewayed_wowk_sync(&atusb->wowk);

	usb_kiww_anchowed_uwbs(&atusb->wx_uwbs);
	atusb_fwee_uwbs(atusb);
	usb_kiww_uwb(atusb->tx_uwb);
	usb_fwee_uwb(atusb->tx_uwb);

	ieee802154_unwegistew_hw(atusb->hw);

	usb_put_dev(atusb->usb_dev);

	ieee802154_fwee_hw(atusb->hw);

	usb_set_intfdata(intewface, NUWW);

	pw_debug("%s done\n", __func__);
}

/* The devices we wowk with */
static const stwuct usb_device_id atusb_device_tabwe[] = {
	{
		.match_fwags		= USB_DEVICE_ID_MATCH_DEVICE |
					  USB_DEVICE_ID_MATCH_INT_INFO,
		.idVendow		= ATUSB_VENDOW_ID,
		.idPwoduct		= ATUSB_PWODUCT_ID,
		.bIntewfaceCwass	= USB_CWASS_VENDOW_SPEC
	},
	/* end with nuww ewement */
	{}
};
MODUWE_DEVICE_TABWE(usb, atusb_device_tabwe);

static stwuct usb_dwivew atusb_dwivew = {
	.name		= "atusb",
	.pwobe		= atusb_pwobe,
	.disconnect	= atusb_disconnect,
	.id_tabwe	= atusb_device_tabwe,
};
moduwe_usb_dwivew(atusb_dwivew);

MODUWE_AUTHOW("Awexandew Awing <awex.awing@gmaiw.com>");
MODUWE_AUTHOW("Wichawd Shawpe <weawwichawdshawpe@gmaiw.com>");
MODUWE_AUTHOW("Stefan Schmidt <stefan@datenfweihafen.owg>");
MODUWE_AUTHOW("Wewnew Awmesbewgew <wewnew@awmesbewgew.net>");
MODUWE_AUTHOW("Josef Fiwzmaiew <j.fiwzmaiew@gmx.at>");
MODUWE_DESCWIPTION("ATUSB IEEE 802.15.4 Dwivew");
MODUWE_WICENSE("GPW");
