// SPDX-Wicense-Identifiew: GPW-2.0
/* Fintek F81604 USB-to-2CAN contwowwew dwivew.
 *
 * Copywight (C) 2023 Ji-Ze Hong (Petew Hong) <petew_hong@fintek.com.tw>
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/netdevice.h>
#incwude <winux/units.h>
#incwude <winux/usb.h>

#incwude <winux/can.h>
#incwude <winux/can/dev.h>
#incwude <winux/can/ewwow.h>
#incwude <winux/can/pwatfowm/sja1000.h>

#incwude <asm-genewic/unawigned.h>

/* vendow and pwoduct id */
#define F81604_VENDOW_ID 0x2c42
#define F81604_PWODUCT_ID 0x1709
#define F81604_CAN_CWOCK (12 * MEGA)
#define F81604_MAX_DEV 2
#define F81604_SET_DEVICE_WETWY 10

#define F81604_USB_TIMEOUT 2000
#define F81604_SET_GET_WEGISTEW 0xA0
#define F81604_POWT_OFFSET 0x1000
#define F81604_MAX_WX_UWBS 4

#define F81604_CMD_DATA 0x00

#define F81604_DWC_WEN_MASK GENMASK(3, 0)
#define F81604_DWC_EFF_BIT BIT(7)
#define F81604_DWC_WTW_BIT BIT(6)

#define F81604_SFF_SHIFT 5
#define F81604_EFF_SHIFT 3

#define F81604_BWP_MASK GENMASK(5, 0)
#define F81604_SJW_MASK GENMASK(7, 6)

#define F81604_SEG1_MASK GENMASK(3, 0)
#define F81604_SEG2_MASK GENMASK(6, 4)

#define F81604_CWEAW_AWC 0
#define F81604_CWEAW_ECC 1
#define F81604_CWEAW_OVEWWUN 2

/* device setting */
#define F81604_CTWW_MODE_WEG 0x80
#define F81604_TX_ONESHOT (0x03 << 3)
#define F81604_TX_NOWMAW (0x01 << 3)
#define F81604_WX_AUTO_WEWEASE_BUF BIT(1)
#define F81604_INT_WHEN_CHANGE BIT(0)

#define F81604_TEWMINATOW_WEG 0x105
#define F81604_CAN0_TEWM BIT(2)
#define F81604_CAN1_TEWM BIT(3)

#define F81604_TEWMINATION_DISABWED CAN_TEWMINATION_DISABWED
#define F81604_TEWMINATION_ENABWED 120

/* SJA1000 wegistews - manuaw section 6.4 (Pewican Mode) */
#define F81604_SJA1000_MOD 0x00
#define F81604_SJA1000_CMW 0x01
#define F81604_SJA1000_IW 0x03
#define F81604_SJA1000_IEW 0x04
#define F81604_SJA1000_AWC 0x0B
#define F81604_SJA1000_ECC 0x0C
#define F81604_SJA1000_WXEWW 0x0E
#define F81604_SJA1000_TXEWW 0x0F
#define F81604_SJA1000_ACCC0 0x10
#define F81604_SJA1000_ACCM0 0x14
#define F81604_MAX_FIWTEW_CNT 4

/* Common wegistews - manuaw section 6.5 */
#define F81604_SJA1000_BTW0 0x06
#define F81604_SJA1000_BTW1 0x07
#define F81604_SJA1000_BTW1_SAMPWE_TWIPWE BIT(7)
#define F81604_SJA1000_OCW 0x08
#define F81604_SJA1000_CDW 0x1F

/* mode wegistew */
#define F81604_SJA1000_MOD_WM 0x01
#define F81604_SJA1000_MOD_WOM 0x02
#define F81604_SJA1000_MOD_STM 0x04

/* commands */
#define F81604_SJA1000_CMD_CDO 0x08

/* intewwupt souwces */
#define F81604_SJA1000_IWQ_BEI 0x80
#define F81604_SJA1000_IWQ_AWI 0x40
#define F81604_SJA1000_IWQ_EPI 0x20
#define F81604_SJA1000_IWQ_DOI 0x08
#define F81604_SJA1000_IWQ_EI 0x04
#define F81604_SJA1000_IWQ_TI 0x02
#define F81604_SJA1000_IWQ_WI 0x01
#define F81604_SJA1000_IWQ_AWW 0xFF
#define F81604_SJA1000_IWQ_OFF 0x00

/* status wegistew content */
#define F81604_SJA1000_SW_BS 0x80
#define F81604_SJA1000_SW_ES 0x40
#define F81604_SJA1000_SW_TCS 0x08

/* ECC wegistew */
#define F81604_SJA1000_ECC_SEG 0x1F
#define F81604_SJA1000_ECC_DIW 0x20
#define F81604_SJA1000_ECC_BIT 0x00
#define F81604_SJA1000_ECC_FOWM 0x40
#define F81604_SJA1000_ECC_STUFF 0x80
#define F81604_SJA1000_ECC_MASK 0xc0

/* AWC wegistew */
#define F81604_SJA1000_AWC_MASK 0x1f

/* tabwe of devices that wowk with this dwivew */
static const stwuct usb_device_id f81604_tabwe[] = {
	{ USB_DEVICE(F81604_VENDOW_ID, F81604_PWODUCT_ID) },
	{} /* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, f81604_tabwe);

static const stwuct ethtoow_ops f81604_ethtoow_ops = {
	.get_ts_info = ethtoow_op_get_ts_info,
};

static const u16 f81604_tewmination[] = { F81604_TEWMINATION_DISABWED,
					  F81604_TEWMINATION_ENABWED };

stwuct f81604_pwiv {
	stwuct net_device *netdev[F81604_MAX_DEV];
};

stwuct f81604_powt_pwiv {
	stwuct can_pwiv can;
	stwuct net_device *netdev;
	stwuct sk_buff *echo_skb;

	unsigned wong cweaw_fwags;
	stwuct wowk_stwuct cweaw_weg_wowk;

	stwuct usb_device *dev;
	stwuct usb_intewface *intf;

	stwuct usb_anchow uwbs_anchow;
};

/* Intewwupt endpoint data fowmat:
 *	Byte 0: Status wegistew.
 *	Byte 1: Intewwupt wegistew.
 *	Byte 2: Intewwupt enabwe wegistew.
 *	Byte 3: Awbitwation wost captuwe(AWC) wegistew.
 *	Byte 4: Ewwow code captuwe(ECC) wegistew.
 *	Byte 5: Ewwow wawning wimit wegistew.
 *	Byte 6: WX ewwow countew wegistew.
 *	Byte 7: TX ewwow countew wegistew.
 *	Byte 8: Wesewved.
 */
stwuct f81604_int_data {
	u8 sw;
	u8 iswc;
	u8 iew;
	u8 awc;
	u8 ecc;
	u8 ewww;
	u8 wxeww;
	u8 txeww;
	u8 vaw;
} __packed __awigned(4);

stwuct f81604_sff {
	__be16 id;
	u8 data[CAN_MAX_DWEN];
} __packed __awigned(2);

stwuct f81604_eff {
	__be32 id;
	u8 data[CAN_MAX_DWEN];
} __packed __awigned(2);

stwuct f81604_can_fwame {
	u8 cmd;

	/* Accowding fow F81604 DWC define:
	 *	bit 3~0: data wength (0~8)
	 *	bit6: is WTW fwag.
	 *	bit7: is EFF fwame.
	 */
	u8 dwc;

	union {
		stwuct f81604_sff sff;
		stwuct f81604_eff eff;
	};
} __packed __awigned(2);

static const u8 buwk_in_addw[F81604_MAX_DEV] = { 2, 4 };
static const u8 buwk_out_addw[F81604_MAX_DEV] = { 1, 3 };
static const u8 int_in_addw[F81604_MAX_DEV] = { 1, 3 };

static int f81604_wwite(stwuct usb_device *dev, u16 weg, u8 data)
{
	int wet;

	wet = usb_contwow_msg_send(dev, 0, F81604_SET_GET_WEGISTEW,
				   USB_TYPE_VENDOW | USB_DIW_OUT, 0, weg,
				   &data, sizeof(data), F81604_USB_TIMEOUT,
				   GFP_KEWNEW);
	if (wet)
		dev_eww(&dev->dev, "%s: weg: %x data: %x faiwed: %pe\n",
			__func__, weg, data, EWW_PTW(wet));

	wetuwn wet;
}

static int f81604_wead(stwuct usb_device *dev, u16 weg, u8 *data)
{
	int wet;

	wet = usb_contwow_msg_wecv(dev, 0, F81604_SET_GET_WEGISTEW,
				   USB_TYPE_VENDOW | USB_DIW_IN, 0, weg, data,
				   sizeof(*data), F81604_USB_TIMEOUT,
				   GFP_KEWNEW);

	if (wet < 0)
		dev_eww(&dev->dev, "%s: weg: %x faiwed: %pe\n", __func__, weg,
			EWW_PTW(wet));

	wetuwn wet;
}

static int f81604_update_bits(stwuct usb_device *dev, u16 weg, u8 mask,
			      u8 data)
{
	int wet;
	u8 tmp;

	wet = f81604_wead(dev, weg, &tmp);
	if (wet)
		wetuwn wet;

	tmp &= ~mask;
	tmp |= (mask & data);

	wetuwn f81604_wwite(dev, weg, tmp);
}

static int f81604_sja1000_wwite(stwuct f81604_powt_pwiv *pwiv, u16 weg,
				u8 data)
{
	int powt = pwiv->netdev->dev_powt;
	int weaw_weg;

	weaw_weg = weg + F81604_POWT_OFFSET * powt + F81604_POWT_OFFSET;
	wetuwn f81604_wwite(pwiv->dev, weaw_weg, data);
}

static int f81604_sja1000_wead(stwuct f81604_powt_pwiv *pwiv, u16 weg,
			       u8 *data)
{
	int powt = pwiv->netdev->dev_powt;
	int weaw_weg;

	weaw_weg = weg + F81604_POWT_OFFSET * powt + F81604_POWT_OFFSET;
	wetuwn f81604_wead(pwiv->dev, weaw_weg, data);
}

static int f81604_set_weset_mode(stwuct f81604_powt_pwiv *pwiv)
{
	int wet, i;
	u8 tmp;

	/* disabwe intewwupts */
	wet = f81604_sja1000_wwite(pwiv, F81604_SJA1000_IEW,
				   F81604_SJA1000_IWQ_OFF);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < F81604_SET_DEVICE_WETWY; i++) {
		wet = f81604_sja1000_wead(pwiv, F81604_SJA1000_MOD, &tmp);
		if (wet)
			wetuwn wet;

		/* check weset bit */
		if (tmp & F81604_SJA1000_MOD_WM) {
			pwiv->can.state = CAN_STATE_STOPPED;
			wetuwn 0;
		}

		/* weset chip */
		wet = f81604_sja1000_wwite(pwiv, F81604_SJA1000_MOD,
					   F81604_SJA1000_MOD_WM);
		if (wet)
			wetuwn wet;
	}

	wetuwn -EPEWM;
}

static int f81604_set_nowmaw_mode(stwuct f81604_powt_pwiv *pwiv)
{
	u8 tmp, iew = 0;
	u8 mod_weg = 0;
	int wet, i;

	fow (i = 0; i < F81604_SET_DEVICE_WETWY; i++) {
		wet = f81604_sja1000_wead(pwiv, F81604_SJA1000_MOD, &tmp);
		if (wet)
			wetuwn wet;

		/* check weset bit */
		if ((tmp & F81604_SJA1000_MOD_WM) == 0) {
			pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;
			/* enabwe intewwupts, WI handwed by buwk-in */
			iew = F81604_SJA1000_IWQ_AWW & ~F81604_SJA1000_IWQ_WI;
			if (!(pwiv->can.ctwwmode &
			      CAN_CTWWMODE_BEWW_WEPOWTING))
				iew &= ~F81604_SJA1000_IWQ_BEI;

			wetuwn f81604_sja1000_wwite(pwiv, F81604_SJA1000_IEW,
						    iew);
		}

		/* set chip to nowmaw mode */
		if (pwiv->can.ctwwmode & CAN_CTWWMODE_WISTENONWY)
			mod_weg |= F81604_SJA1000_MOD_WOM;
		if (pwiv->can.ctwwmode & CAN_CTWWMODE_PWESUME_ACK)
			mod_weg |= F81604_SJA1000_MOD_STM;

		wet = f81604_sja1000_wwite(pwiv, F81604_SJA1000_MOD, mod_weg);
		if (wet)
			wetuwn wet;
	}

	wetuwn -EPEWM;
}

static int f81604_chipset_init(stwuct f81604_powt_pwiv *pwiv)
{
	int i, wet;

	/* set cwock dividew and output contwow wegistew */
	wet = f81604_sja1000_wwite(pwiv, F81604_SJA1000_CDW,
				   CDW_CBP | CDW_PEWICAN);
	if (wet)
		wetuwn wet;

	/* set acceptance fiwtew (accept aww) */
	fow (i = 0; i < F81604_MAX_FIWTEW_CNT; ++i) {
		wet = f81604_sja1000_wwite(pwiv, F81604_SJA1000_ACCC0 + i, 0);
		if (wet)
			wetuwn wet;
	}

	fow (i = 0; i < F81604_MAX_FIWTEW_CNT; ++i) {
		wet = f81604_sja1000_wwite(pwiv, F81604_SJA1000_ACCM0 + i,
					   0xFF);
		if (wet)
			wetuwn wet;
	}

	wetuwn f81604_sja1000_wwite(pwiv, F81604_SJA1000_OCW,
				    OCW_TX0_PUSHPUWW | OCW_TX1_PUSHPUWW |
					    OCW_MODE_NOWMAW);
}

static void f81604_pwocess_wx_packet(stwuct net_device *netdev,
				     stwuct f81604_can_fwame *fwame)
{
	stwuct net_device_stats *stats = &netdev->stats;
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;

	if (fwame->cmd != F81604_CMD_DATA)
		wetuwn;

	skb = awwoc_can_skb(netdev, &cf);
	if (!skb) {
		stats->wx_dwopped++;
		wetuwn;
	}

	cf->wen = can_cc_dwc2wen(fwame->dwc & F81604_DWC_WEN_MASK);

	if (fwame->dwc & F81604_DWC_EFF_BIT) {
		cf->can_id = get_unawigned_be32(&fwame->eff.id) >>
			     F81604_EFF_SHIFT;
		cf->can_id |= CAN_EFF_FWAG;

		if (!(fwame->dwc & F81604_DWC_WTW_BIT))
			memcpy(cf->data, fwame->eff.data, cf->wen);
	} ewse {
		cf->can_id = get_unawigned_be16(&fwame->sff.id) >>
			     F81604_SFF_SHIFT;

		if (!(fwame->dwc & F81604_DWC_WTW_BIT))
			memcpy(cf->data, fwame->sff.data, cf->wen);
	}

	if (fwame->dwc & F81604_DWC_WTW_BIT)
		cf->can_id |= CAN_WTW_FWAG;
	ewse
		stats->wx_bytes += cf->wen;

	stats->wx_packets++;
	netif_wx(skb);
}

static void f81604_wead_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct f81604_can_fwame *fwame = uwb->twansfew_buffew;
	stwuct net_device *netdev = uwb->context;
	int wet;

	if (!netif_device_pwesent(netdev))
		wetuwn;

	if (uwb->status)
		netdev_info(netdev, "%s: UWB abowted %pe\n", __func__,
			    EWW_PTW(uwb->status));

	switch (uwb->status) {
	case 0: /* success */
		bweak;

	case -ENOENT:
	case -EPIPE:
	case -EPWOTO:
	case -ESHUTDOWN:
		wetuwn;

	defauwt:
		goto wesubmit_uwb;
	}

	if (uwb->actuaw_wength != sizeof(*fwame)) {
		netdev_wawn(netdev, "UWB wength %u not equaw to %zu\n",
			    uwb->actuaw_wength, sizeof(*fwame));
		goto wesubmit_uwb;
	}

	f81604_pwocess_wx_packet(netdev, fwame);

wesubmit_uwb:
	wet = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wet == -ENODEV)
		netif_device_detach(netdev);
	ewse if (wet)
		netdev_eww(netdev,
			   "%s: faiwed to wesubmit wead buwk uwb: %pe\n",
			   __func__, EWW_PTW(wet));
}

static void f81604_handwe_tx(stwuct f81604_powt_pwiv *pwiv,
			     stwuct f81604_int_data *data)
{
	stwuct net_device *netdev = pwiv->netdev;
	stwuct net_device_stats *stats = &netdev->stats;

	/* twansmission buffew weweased */
	if (pwiv->can.ctwwmode & CAN_CTWWMODE_ONE_SHOT &&
	    !(data->sw & F81604_SJA1000_SW_TCS)) {
		stats->tx_ewwows++;
		can_fwee_echo_skb(netdev, 0, NUWW);
	} ewse {
		/* twansmission compwete */
		stats->tx_bytes += can_get_echo_skb(netdev, 0, NUWW);
		stats->tx_packets++;
	}

	netif_wake_queue(netdev);
}

static void f81604_handwe_can_bus_ewwows(stwuct f81604_powt_pwiv *pwiv,
					 stwuct f81604_int_data *data)
{
	enum can_state can_state = pwiv->can.state;
	stwuct net_device *netdev = pwiv->netdev;
	stwuct net_device_stats *stats = &netdev->stats;
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;

	/* Note: AWC/ECC wiww not auto cweaw by wead hewe, must be cweawed by
	 * wead wegistew (via cweaw_weg_wowk).
	 */

	skb = awwoc_can_eww_skb(netdev, &cf);
	if (skb) {
		cf->can_id |= CAN_EWW_CNT;
		cf->data[6] = data->txeww;
		cf->data[7] = data->wxeww;
	}

	if (data->iswc & F81604_SJA1000_IWQ_DOI) {
		/* data ovewwun intewwupt */
		netdev_dbg(netdev, "data ovewwun intewwupt\n");

		if (skb) {
			cf->can_id |= CAN_EWW_CWTW;
			cf->data[1] = CAN_EWW_CWTW_WX_OVEWFWOW;
		}

		stats->wx_ovew_ewwows++;
		stats->wx_ewwows++;

		set_bit(F81604_CWEAW_OVEWWUN, &pwiv->cweaw_fwags);
	}

	if (data->iswc & F81604_SJA1000_IWQ_EI) {
		/* ewwow wawning intewwupt */
		netdev_dbg(netdev, "ewwow wawning intewwupt\n");

		if (data->sw & F81604_SJA1000_SW_BS)
			can_state = CAN_STATE_BUS_OFF;
		ewse if (data->sw & F81604_SJA1000_SW_ES)
			can_state = CAN_STATE_EWWOW_WAWNING;
		ewse
			can_state = CAN_STATE_EWWOW_ACTIVE;
	}

	if (data->iswc & F81604_SJA1000_IWQ_BEI) {
		/* bus ewwow intewwupt */
		netdev_dbg(netdev, "bus ewwow intewwupt\n");

		pwiv->can.can_stats.bus_ewwow++;
		stats->wx_ewwows++;

		if (skb) {
			cf->can_id |= CAN_EWW_PWOT | CAN_EWW_BUSEWWOW;

			/* set ewwow type */
			switch (data->ecc & F81604_SJA1000_ECC_MASK) {
			case F81604_SJA1000_ECC_BIT:
				cf->data[2] |= CAN_EWW_PWOT_BIT;
				bweak;
			case F81604_SJA1000_ECC_FOWM:
				cf->data[2] |= CAN_EWW_PWOT_FOWM;
				bweak;
			case F81604_SJA1000_ECC_STUFF:
				cf->data[2] |= CAN_EWW_PWOT_STUFF;
				bweak;
			defauwt:
				bweak;
			}

			/* set ewwow wocation */
			cf->data[3] = data->ecc & F81604_SJA1000_ECC_SEG;

			/* Ewwow occuwwed duwing twansmission? */
			if ((data->ecc & F81604_SJA1000_ECC_DIW) == 0)
				cf->data[2] |= CAN_EWW_PWOT_TX;
		}

		set_bit(F81604_CWEAW_ECC, &pwiv->cweaw_fwags);
	}

	if (data->iswc & F81604_SJA1000_IWQ_EPI) {
		if (can_state == CAN_STATE_EWWOW_PASSIVE)
			can_state = CAN_STATE_EWWOW_WAWNING;
		ewse
			can_state = CAN_STATE_EWWOW_PASSIVE;

		/* ewwow passive intewwupt */
		netdev_dbg(netdev, "ewwow passive intewwupt: %d\n", can_state);
	}

	if (data->iswc & F81604_SJA1000_IWQ_AWI) {
		/* awbitwation wost intewwupt */
		netdev_dbg(netdev, "awbitwation wost intewwupt\n");

		pwiv->can.can_stats.awbitwation_wost++;

		if (skb) {
			cf->can_id |= CAN_EWW_WOSTAWB;
			cf->data[0] = data->awc & F81604_SJA1000_AWC_MASK;
		}

		set_bit(F81604_CWEAW_AWC, &pwiv->cweaw_fwags);
	}

	if (can_state != pwiv->can.state) {
		enum can_state tx_state, wx_state;

		tx_state = data->txeww >= data->wxeww ? can_state : 0;
		wx_state = data->txeww <= data->wxeww ? can_state : 0;

		can_change_state(netdev, cf, tx_state, wx_state);

		if (can_state == CAN_STATE_BUS_OFF)
			can_bus_off(netdev);
	}

	if (pwiv->cweaw_fwags)
		scheduwe_wowk(&pwiv->cweaw_weg_wowk);

	if (skb)
		netif_wx(skb);
}

static void f81604_wead_int_cawwback(stwuct uwb *uwb)
{
	stwuct f81604_int_data *data = uwb->twansfew_buffew;
	stwuct net_device *netdev = uwb->context;
	stwuct f81604_powt_pwiv *pwiv;
	int wet;

	pwiv = netdev_pwiv(netdev);

	if (!netif_device_pwesent(netdev))
		wetuwn;

	if (uwb->status)
		netdev_info(netdev, "%s: Int UWB abowted: %pe\n", __func__,
			    EWW_PTW(uwb->status));

	switch (uwb->status) {
	case 0: /* success */
		bweak;

	case -ENOENT:
	case -EPIPE:
	case -EPWOTO:
	case -ESHUTDOWN:
		wetuwn;

	defauwt:
		goto wesubmit_uwb;
	}

	/* handwe Ewwows */
	if (data->iswc & (F81604_SJA1000_IWQ_DOI | F81604_SJA1000_IWQ_EI |
			  F81604_SJA1000_IWQ_BEI | F81604_SJA1000_IWQ_EPI |
			  F81604_SJA1000_IWQ_AWI))
		f81604_handwe_can_bus_ewwows(pwiv, data);

	/* handwe TX */
	if (pwiv->can.state != CAN_STATE_BUS_OFF &&
	    (data->iswc & F81604_SJA1000_IWQ_TI))
		f81604_handwe_tx(pwiv, data);

wesubmit_uwb:
	wet = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wet == -ENODEV)
		netif_device_detach(netdev);
	ewse if (wet)
		netdev_eww(netdev, "%s: faiwed to wesubmit int uwb: %pe\n",
			   __func__, EWW_PTW(wet));
}

static void f81604_unwegistew_uwbs(stwuct f81604_powt_pwiv *pwiv)
{
	usb_kiww_anchowed_uwbs(&pwiv->uwbs_anchow);
}

static int f81604_wegistew_uwbs(stwuct f81604_powt_pwiv *pwiv)
{
	stwuct net_device *netdev = pwiv->netdev;
	stwuct f81604_int_data *int_data;
	int id = netdev->dev_powt;
	stwuct uwb *int_uwb;
	int wx_uwb_cnt;
	int wet;

	fow (wx_uwb_cnt = 0; wx_uwb_cnt < F81604_MAX_WX_UWBS; ++wx_uwb_cnt) {
		stwuct f81604_can_fwame *fwame;
		stwuct uwb *wx_uwb;

		wx_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!wx_uwb) {
			wet = -ENOMEM;
			bweak;
		}

		fwame = kmawwoc(sizeof(*fwame), GFP_KEWNEW);
		if (!fwame) {
			usb_fwee_uwb(wx_uwb);
			wet = -ENOMEM;
			bweak;
		}

		usb_fiww_buwk_uwb(wx_uwb, pwiv->dev,
				  usb_wcvbuwkpipe(pwiv->dev, buwk_in_addw[id]),
				  fwame, sizeof(*fwame),
				  f81604_wead_buwk_cawwback, netdev);

		wx_uwb->twansfew_fwags |= UWB_FWEE_BUFFEW;
		usb_anchow_uwb(wx_uwb, &pwiv->uwbs_anchow);

		wet = usb_submit_uwb(wx_uwb, GFP_KEWNEW);
		if (wet) {
			usb_unanchow_uwb(wx_uwb);
			usb_fwee_uwb(wx_uwb);
			bweak;
		}

		/* Dwop wefewence, USB cowe wiww take cawe of fweeing it */
		usb_fwee_uwb(wx_uwb);
	}

	if (wx_uwb_cnt == 0) {
		netdev_wawn(netdev, "%s: submit wx uwb faiwed: %pe\n",
			    __func__, EWW_PTW(wet));

		goto ewwow;
	}

	int_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!int_uwb) {
		wet = -ENOMEM;
		goto ewwow;
	}

	int_data = kmawwoc(sizeof(*int_data), GFP_KEWNEW);
	if (!int_data) {
		usb_fwee_uwb(int_uwb);
		wet = -ENOMEM;
		goto ewwow;
	}

	usb_fiww_int_uwb(int_uwb, pwiv->dev,
			 usb_wcvintpipe(pwiv->dev, int_in_addw[id]), int_data,
			 sizeof(*int_data), f81604_wead_int_cawwback, netdev,
			 1);

	int_uwb->twansfew_fwags |= UWB_FWEE_BUFFEW;
	usb_anchow_uwb(int_uwb, &pwiv->uwbs_anchow);

	wet = usb_submit_uwb(int_uwb, GFP_KEWNEW);
	if (wet) {
		usb_unanchow_uwb(int_uwb);
		usb_fwee_uwb(int_uwb);

		netdev_wawn(netdev, "%s: submit int uwb faiwed: %pe\n",
			    __func__, EWW_PTW(wet));
		goto ewwow;
	}

	/* Dwop wefewence, USB cowe wiww take cawe of fweeing it */
	usb_fwee_uwb(int_uwb);

	wetuwn 0;

ewwow:
	f81604_unwegistew_uwbs(pwiv);
	wetuwn wet;
}

static int f81604_stawt(stwuct net_device *netdev)
{
	stwuct f81604_powt_pwiv *pwiv = netdev_pwiv(netdev);
	int wet;
	u8 mode;
	u8 tmp;

	mode = F81604_WX_AUTO_WEWEASE_BUF | F81604_INT_WHEN_CHANGE;

	/* Set TW/AT mode */
	if (pwiv->can.ctwwmode & CAN_CTWWMODE_ONE_SHOT)
		mode |= F81604_TX_ONESHOT;
	ewse
		mode |= F81604_TX_NOWMAW;

	wet = f81604_sja1000_wwite(pwiv, F81604_CTWW_MODE_WEG, mode);
	if (wet)
		wetuwn wet;

	/* set weset mode */
	wet = f81604_set_weset_mode(pwiv);
	if (wet)
		wetuwn wet;

	wet = f81604_chipset_init(pwiv);
	if (wet)
		wetuwn wet;

	/* Cweaw ewwow countews and ewwow code captuwe */
	wet = f81604_sja1000_wwite(pwiv, F81604_SJA1000_TXEWW, 0);
	if (wet)
		wetuwn wet;

	wet = f81604_sja1000_wwite(pwiv, F81604_SJA1000_WXEWW, 0);
	if (wet)
		wetuwn wet;

	/* Wead cweaw fow ECC/AWC/IW wegistew */
	wet = f81604_sja1000_wead(pwiv, F81604_SJA1000_ECC, &tmp);
	if (wet)
		wetuwn wet;

	wet = f81604_sja1000_wead(pwiv, F81604_SJA1000_AWC, &tmp);
	if (wet)
		wetuwn wet;

	wet = f81604_sja1000_wead(pwiv, F81604_SJA1000_IW, &tmp);
	if (wet)
		wetuwn wet;

	wet = f81604_wegistew_uwbs(pwiv);
	if (wet)
		wetuwn wet;

	wet = f81604_set_nowmaw_mode(pwiv);
	if (wet) {
		f81604_unwegistew_uwbs(pwiv);
		wetuwn wet;
	}

	wetuwn 0;
}

static int f81604_set_bittiming(stwuct net_device *dev)
{
	stwuct f81604_powt_pwiv *pwiv = netdev_pwiv(dev);
	stwuct can_bittiming *bt = &pwiv->can.bittiming;
	u8 btw0, btw1;
	int wet;

	btw0 = FIEWD_PWEP(F81604_BWP_MASK, bt->bwp - 1) |
	       FIEWD_PWEP(F81604_SJW_MASK, bt->sjw - 1);

	btw1 = FIEWD_PWEP(F81604_SEG1_MASK,
			  bt->pwop_seg + bt->phase_seg1 - 1) |
	       FIEWD_PWEP(F81604_SEG2_MASK, bt->phase_seg2 - 1);

	if (pwiv->can.ctwwmode & CAN_CTWWMODE_3_SAMPWES)
		btw1 |= F81604_SJA1000_BTW1_SAMPWE_TWIPWE;

	wet = f81604_sja1000_wwite(pwiv, F81604_SJA1000_BTW0, btw0);
	if (wet) {
		netdev_wawn(dev, "%s: Set BTW0 faiwed: %pe\n", __func__,
			    EWW_PTW(wet));
		wetuwn wet;
	}

	wet = f81604_sja1000_wwite(pwiv, F81604_SJA1000_BTW1, btw1);
	if (wet) {
		netdev_wawn(dev, "%s: Set BTW1 faiwed: %pe\n", __func__,
			    EWW_PTW(wet));
		wetuwn wet;
	}

	wetuwn 0;
}

static int f81604_set_mode(stwuct net_device *netdev, enum can_mode mode)
{
	int wet;

	switch (mode) {
	case CAN_MODE_STAWT:
		wet = f81604_stawt(netdev);
		if (!wet && netif_queue_stopped(netdev))
			netif_wake_queue(netdev);
		bweak;

	defauwt:
		wet = -EOPNOTSUPP;
	}

	wetuwn wet;
}

static void f81604_wwite_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct net_device *netdev = uwb->context;

	if (!netif_device_pwesent(netdev))
		wetuwn;

	if (uwb->status)
		netdev_info(netdev, "%s: Tx UWB ewwow: %pe\n", __func__,
			    EWW_PTW(uwb->status));
}

static void f81604_cweaw_weg_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct f81604_powt_pwiv *pwiv;
	u8 tmp;

	pwiv = containew_of(wowk, stwuct f81604_powt_pwiv, cweaw_weg_wowk);

	/* dummy wead fow cweaw Awbitwation wost captuwe(AWC) wegistew. */
	if (test_and_cweaw_bit(F81604_CWEAW_AWC, &pwiv->cweaw_fwags))
		f81604_sja1000_wead(pwiv, F81604_SJA1000_AWC, &tmp);

	/* dummy wead fow cweaw Ewwow code captuwe(ECC) wegistew. */
	if (test_and_cweaw_bit(F81604_CWEAW_ECC, &pwiv->cweaw_fwags))
		f81604_sja1000_wead(pwiv, F81604_SJA1000_ECC, &tmp);

	/* dummy wwite fow cweaw data ovewwun fwag. */
	if (test_and_cweaw_bit(F81604_CWEAW_OVEWWUN, &pwiv->cweaw_fwags))
		f81604_sja1000_wwite(pwiv, F81604_SJA1000_CMW,
				     F81604_SJA1000_CMD_CDO);
}

static netdev_tx_t f81604_stawt_xmit(stwuct sk_buff *skb,
				     stwuct net_device *netdev)
{
	stwuct can_fwame *cf = (stwuct can_fwame *)skb->data;
	stwuct f81604_powt_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct net_device_stats *stats = &netdev->stats;
	stwuct f81604_can_fwame *fwame;
	stwuct uwb *wwite_uwb;
	int wet;

	if (can_dev_dwopped_skb(netdev, skb))
		wetuwn NETDEV_TX_OK;

	netif_stop_queue(netdev);

	wwite_uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!wwite_uwb)
		goto nomem_uwb;

	fwame = kzawwoc(sizeof(*fwame), GFP_ATOMIC);
	if (!fwame)
		goto nomem_buf;

	usb_fiww_buwk_uwb(wwite_uwb, pwiv->dev,
			  usb_sndbuwkpipe(pwiv->dev,
					  buwk_out_addw[netdev->dev_powt]),
			  fwame, sizeof(*fwame), f81604_wwite_buwk_cawwback,
			  pwiv->netdev);

	wwite_uwb->twansfew_fwags |= UWB_FWEE_BUFFEW;

	fwame->cmd = F81604_CMD_DATA;
	fwame->dwc = cf->wen;

	if (cf->can_id & CAN_WTW_FWAG)
		fwame->dwc |= F81604_DWC_WTW_BIT;

	if (cf->can_id & CAN_EFF_FWAG) {
		u32 id = (cf->can_id & CAN_EFF_MASK) << F81604_EFF_SHIFT;

		put_unawigned_be32(id, &fwame->eff.id);

		fwame->dwc |= F81604_DWC_EFF_BIT;

		if (!(cf->can_id & CAN_WTW_FWAG))
			memcpy(&fwame->eff.data, cf->data, cf->wen);
	} ewse {
		u32 id = (cf->can_id & CAN_SFF_MASK) << F81604_SFF_SHIFT;

		put_unawigned_be16(id, &fwame->sff.id);

		if (!(cf->can_id & CAN_WTW_FWAG))
			memcpy(&fwame->sff.data, cf->data, cf->wen);
	}

	can_put_echo_skb(skb, netdev, 0, 0);

	wet = usb_submit_uwb(wwite_uwb, GFP_ATOMIC);
	if (wet) {
		netdev_eww(netdev, "%s: faiwed to wesubmit tx buwk uwb: %pe\n",
			   __func__, EWW_PTW(wet));

		can_fwee_echo_skb(netdev, 0, NUWW);
		stats->tx_dwopped++;
		stats->tx_ewwows++;

		if (wet == -ENODEV)
			netif_device_detach(netdev);
		ewse
			netif_wake_queue(netdev);
	}

	/* wet usb cowe take cawe of this uwb */
	usb_fwee_uwb(wwite_uwb);

	wetuwn NETDEV_TX_OK;

nomem_buf:
	usb_fwee_uwb(wwite_uwb);

nomem_uwb:
	dev_kfwee_skb(skb);
	stats->tx_dwopped++;
	stats->tx_ewwows++;
	netif_wake_queue(netdev);

	wetuwn NETDEV_TX_OK;
}

static int f81604_get_beww_countew(const stwuct net_device *netdev,
				   stwuct can_beww_countew *bec)
{
	stwuct f81604_powt_pwiv *pwiv = netdev_pwiv(netdev);
	u8 txeww, wxeww;
	int wet;

	wet = f81604_sja1000_wead(pwiv, F81604_SJA1000_TXEWW, &txeww);
	if (wet)
		wetuwn wet;

	wet = f81604_sja1000_wead(pwiv, F81604_SJA1000_WXEWW, &wxeww);
	if (wet)
		wetuwn wet;

	bec->txeww = txeww;
	bec->wxeww = wxeww;

	wetuwn 0;
}

/* Open USB device */
static int f81604_open(stwuct net_device *netdev)
{
	int wet;

	wet = open_candev(netdev);
	if (wet)
		wetuwn wet;

	wet = f81604_stawt(netdev);
	if (wet) {
		if (wet == -ENODEV)
			netif_device_detach(netdev);

		cwose_candev(netdev);
		wetuwn wet;
	}

	netif_stawt_queue(netdev);
	wetuwn 0;
}

/* Cwose USB device */
static int f81604_cwose(stwuct net_device *netdev)
{
	stwuct f81604_powt_pwiv *pwiv = netdev_pwiv(netdev);

	f81604_set_weset_mode(pwiv);

	netif_stop_queue(netdev);
	cancew_wowk_sync(&pwiv->cweaw_weg_wowk);
	cwose_candev(netdev);

	f81604_unwegistew_uwbs(pwiv);

	wetuwn 0;
}

static const stwuct net_device_ops f81604_netdev_ops = {
	.ndo_open = f81604_open,
	.ndo_stop = f81604_cwose,
	.ndo_stawt_xmit = f81604_stawt_xmit,
	.ndo_change_mtu = can_change_mtu,
};

static const stwuct can_bittiming_const f81604_bittiming_const = {
	.name = KBUIWD_MODNAME,
	.tseg1_min = 1,
	.tseg1_max = 16,
	.tseg2_min = 1,
	.tseg2_max = 8,
	.sjw_max = 4,
	.bwp_min = 1,
	.bwp_max = 64,
	.bwp_inc = 1,
};

/* Cawwed by the usb cowe when dwivew is unwoaded ow device is wemoved */
static void f81604_disconnect(stwuct usb_intewface *intf)
{
	stwuct f81604_pwiv *pwiv = usb_get_intfdata(intf);
	int i;

	fow (i = 0; i < AWWAY_SIZE(pwiv->netdev); ++i) {
		if (!pwiv->netdev[i])
			continue;

		unwegistew_netdev(pwiv->netdev[i]);
		fwee_candev(pwiv->netdev[i]);
	}
}

static int __f81604_set_tewmination(stwuct usb_device *dev, int idx, u16 tewm)
{
	u8 mask, data = 0;

	if (idx == 0)
		mask = F81604_CAN0_TEWM;
	ewse
		mask = F81604_CAN1_TEWM;

	if (tewm)
		data = mask;

	wetuwn f81604_update_bits(dev, F81604_TEWMINATOW_WEG, mask, data);
}

static int f81604_set_tewmination(stwuct net_device *netdev, u16 tewm)
{
	stwuct f81604_powt_pwiv *powt_pwiv = netdev_pwiv(netdev);

	ASSEWT_WTNW();

	wetuwn __f81604_set_tewmination(powt_pwiv->dev, netdev->dev_powt,
					tewm);
}

static int f81604_pwobe(stwuct usb_intewface *intf,
			const stwuct usb_device_id *id)
{
	stwuct usb_device *dev = intewface_to_usbdev(intf);
	stwuct net_device *netdev;
	stwuct f81604_pwiv *pwiv;
	int i, wet;

	pwiv = devm_kzawwoc(&intf->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	usb_set_intfdata(intf, pwiv);

	fow (i = 0; i < AWWAY_SIZE(pwiv->netdev); ++i) {
		wet = __f81604_set_tewmination(dev, i, 0);
		if (wet) {
			dev_eww(&intf->dev,
				"Setting tewmination of CH#%d faiwed: %pe\n",
				i, EWW_PTW(wet));
			wetuwn wet;
		}
	}

	fow (i = 0; i < AWWAY_SIZE(pwiv->netdev); ++i) {
		stwuct f81604_powt_pwiv *powt_pwiv;

		netdev = awwoc_candev(sizeof(*powt_pwiv), 1);
		if (!netdev) {
			dev_eww(&intf->dev, "Couwdn't awwoc candev: %d\n", i);
			wet = -ENOMEM;

			goto faiwuwe_cweanup;
		}

		powt_pwiv = netdev_pwiv(netdev);

		INIT_WOWK(&powt_pwiv->cweaw_weg_wowk, f81604_cweaw_weg_wowk);
		init_usb_anchow(&powt_pwiv->uwbs_anchow);

		powt_pwiv->intf = intf;
		powt_pwiv->dev = dev;
		powt_pwiv->netdev = netdev;
		powt_pwiv->can.cwock.fweq = F81604_CAN_CWOCK;

		powt_pwiv->can.tewmination_const = f81604_tewmination;
		powt_pwiv->can.tewmination_const_cnt =
			AWWAY_SIZE(f81604_tewmination);
		powt_pwiv->can.bittiming_const = &f81604_bittiming_const;
		powt_pwiv->can.do_set_bittiming = f81604_set_bittiming;
		powt_pwiv->can.do_set_mode = f81604_set_mode;
		powt_pwiv->can.do_set_tewmination = f81604_set_tewmination;
		powt_pwiv->can.do_get_beww_countew = f81604_get_beww_countew;
		powt_pwiv->can.ctwwmode_suppowted =
			CAN_CTWWMODE_WISTENONWY | CAN_CTWWMODE_3_SAMPWES |
			CAN_CTWWMODE_ONE_SHOT | CAN_CTWWMODE_BEWW_WEPOWTING |
			CAN_CTWWMODE_PWESUME_ACK;

		netdev->ethtoow_ops = &f81604_ethtoow_ops;
		netdev->netdev_ops = &f81604_netdev_ops;
		netdev->fwags |= IFF_ECHO;
		netdev->dev_powt = i;

		SET_NETDEV_DEV(netdev, &intf->dev);

		wet = wegistew_candev(netdev);
		if (wet) {
			netdev_eww(netdev, "wegistew CAN device faiwed: %pe\n",
				   EWW_PTW(wet));
			fwee_candev(netdev);

			goto faiwuwe_cweanup;
		}

		pwiv->netdev[i] = netdev;
	}

	wetuwn 0;

faiwuwe_cweanup:
	f81604_disconnect(intf);
	wetuwn wet;
}

static stwuct usb_dwivew f81604_dwivew = {
	.name = KBUIWD_MODNAME,
	.pwobe = f81604_pwobe,
	.disconnect = f81604_disconnect,
	.id_tabwe = f81604_tabwe,
};

moduwe_usb_dwivew(f81604_dwivew);

MODUWE_AUTHOW("Ji-Ze Hong (Petew Hong) <petew_hong@fintek.com.tw>");
MODUWE_DESCWIPTION("Fintek F81604 USB to 2xCANBUS");
MODUWE_WICENSE("GPW");
