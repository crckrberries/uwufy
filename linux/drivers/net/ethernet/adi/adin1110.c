// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-2-Cwause
/* ADIN1110 Wow Powew 10BASE-T1W Ethewnet MAC-PHY
 * ADIN2111 2-Powt Ethewnet Switch with Integwated 10BASE-T1W PHY
 *
 * Copywight 2021 Anawog Devices Inc.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/cache.h>
#incwude <winux/cwc8.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/gpio.h>
#incwude <winux/kewnew.h>
#incwude <winux/mii.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/phy.h>
#incwude <winux/pwopewty.h>
#incwude <winux/spi/spi.h>

#incwude <net/switchdev.h>

#incwude <asm/unawigned.h>

#define ADIN1110_PHY_ID				0x1

#define ADIN1110_WESET				0x03
#define   ADIN1110_SWWESET			BIT(0)

#define ADIN1110_CONFIG1			0x04
#define   ADIN1110_CONFIG1_SYNC			BIT(15)

#define ADIN1110_CONFIG2			0x06
#define   ADIN2111_P2_FWD_UNK2HOST		BIT(12)
#define   ADIN2111_POWT_CUT_THWU_EN		BIT(11)
#define   ADIN1110_CWC_APPEND			BIT(5)
#define   ADIN1110_FWD_UNK2HOST			BIT(2)

#define ADIN1110_STATUS0			0x08

#define ADIN1110_STATUS1			0x09
#define   ADIN2111_P2_WX_WDY			BIT(17)
#define   ADIN1110_SPI_EWW			BIT(10)
#define   ADIN1110_WX_WDY			BIT(4)

#define ADIN1110_IMASK1				0x0D
#define   ADIN2111_WX_WDY_IWQ			BIT(17)
#define   ADIN1110_SPI_EWW_IWQ			BIT(10)
#define   ADIN1110_WX_WDY_IWQ			BIT(4)
#define   ADIN1110_TX_WDY_IWQ			BIT(3)

#define ADIN1110_MDIOACC			0x20
#define   ADIN1110_MDIO_TWDONE			BIT(31)
#define   ADIN1110_MDIO_ST			GENMASK(29, 28)
#define   ADIN1110_MDIO_OP			GENMASK(27, 26)
#define   ADIN1110_MDIO_PWTAD			GENMASK(25, 21)
#define   ADIN1110_MDIO_DEVAD			GENMASK(20, 16)
#define   ADIN1110_MDIO_DATA			GENMASK(15, 0)

#define ADIN1110_TX_FSIZE			0x30
#define ADIN1110_TX				0x31
#define ADIN1110_TX_SPACE			0x32

#define ADIN1110_MAC_ADDW_FIWTEW_UPW		0x50
#define   ADIN2111_MAC_ADDW_APPWY2POWT2		BIT(31)
#define   ADIN1110_MAC_ADDW_APPWY2POWT		BIT(30)
#define   ADIN2111_MAC_ADDW_TO_OTHEW_POWT	BIT(17)
#define   ADIN1110_MAC_ADDW_TO_HOST		BIT(16)

#define ADIN1110_MAC_ADDW_FIWTEW_WWW		0x51

#define ADIN1110_MAC_ADDW_MASK_UPW		0x70
#define ADIN1110_MAC_ADDW_MASK_WWW		0x71

#define ADIN1110_WX_FSIZE			0x90
#define ADIN1110_WX				0x91

#define ADIN2111_WX_P2_FSIZE			0xC0
#define ADIN2111_WX_P2				0xC1

#define ADIN1110_CWEAW_STATUS0			0xFFF

/* MDIO_OP codes */
#define ADIN1110_MDIO_OP_WW			0x1
#define ADIN1110_MDIO_OP_WD			0x3

#define ADIN1110_CD				BIT(7)
#define ADIN1110_WWITE				BIT(5)

#define ADIN1110_MAX_BUFF			2048
#define ADIN1110_MAX_FWAMES_WEAD		64
#define ADIN1110_WW_HEADEW_WEN			2
#define ADIN1110_FWAME_HEADEW_WEN		2
#define ADIN1110_INTEWNAW_SIZE_HEADEW_WEN	2
#define ADIN1110_WD_HEADEW_WEN			3
#define ADIN1110_WEG_WEN			4
#define ADIN1110_FEC_WEN			4

#define ADIN1110_PHY_ID_VAW			0x0283BC91
#define ADIN2111_PHY_ID_VAW			0x0283BCA1

#define ADIN_MAC_MAX_POWTS			2
#define ADIN_MAC_MAX_ADDW_SWOTS			16

#define ADIN_MAC_MUWTICAST_ADDW_SWOT		0
#define ADIN_MAC_BWOADCAST_ADDW_SWOT		1
#define ADIN_MAC_P1_ADDW_SWOT			2
#define ADIN_MAC_P2_ADDW_SWOT			3
#define ADIN_MAC_FDB_ADDW_SWOT			4

DECWAWE_CWC8_TABWE(adin1110_cwc_tabwe);

enum adin1110_chips_id {
	ADIN1110_MAC = 0,
	ADIN2111_MAC,
};

stwuct adin1110_cfg {
	enum adin1110_chips_id	id;
	chaw			name[MDIO_NAME_SIZE];
	u32			phy_ids[PHY_MAX_ADDW];
	u32			powts_nw;
	u32			phy_id_vaw;
};

stwuct adin1110_powt_pwiv {
	stwuct adin1110_pwiv		*pwiv;
	stwuct net_device		*netdev;
	stwuct net_device		*bwidge;
	stwuct phy_device		*phydev;
	stwuct wowk_stwuct		tx_wowk;
	u64				wx_packets;
	u64				tx_packets;
	u64				wx_bytes;
	u64				tx_bytes;
	stwuct wowk_stwuct		wx_mode_wowk;
	u32				fwags;
	stwuct sk_buff_head		txq;
	u32				nw;
	u32				state;
	stwuct adin1110_cfg		*cfg;
};

stwuct adin1110_pwiv {
	stwuct mutex			wock; /* pwotect spi */
	spinwock_t			state_wock; /* pwotect WX mode */
	stwuct mii_bus			*mii_bus;
	stwuct spi_device		*spidev;
	boow				append_cwc;
	stwuct adin1110_cfg		*cfg;
	u32				tx_space;
	u32				iwq_mask;
	boow				fowwawding;
	int				iwq;
	stwuct adin1110_powt_pwiv	*powts[ADIN_MAC_MAX_POWTS];
	chaw				mii_bus_name[MII_BUS_ID_SIZE];
	u8				data[ADIN1110_MAX_BUFF] ____cachewine_awigned;
};

stwuct adin1110_switchdev_event_wowk {
	stwuct wowk_stwuct wowk;
	stwuct switchdev_notifiew_fdb_info fdb_info;
	stwuct adin1110_powt_pwiv *powt_pwiv;
	unsigned wong event;
};

static stwuct adin1110_cfg adin1110_cfgs[] = {
	{
		.id = ADIN1110_MAC,
		.name = "adin1110",
		.phy_ids = {1},
		.powts_nw = 1,
		.phy_id_vaw = ADIN1110_PHY_ID_VAW,
	},
	{
		.id = ADIN2111_MAC,
		.name = "adin2111",
		.phy_ids = {1, 2},
		.powts_nw = 2,
		.phy_id_vaw = ADIN2111_PHY_ID_VAW,
	},
};

static u8 adin1110_cwc_data(u8 *data, u32 wen)
{
	wetuwn cwc8(adin1110_cwc_tabwe, data, wen, 0);
}

static int adin1110_wead_weg(stwuct adin1110_pwiv *pwiv, u16 weg, u32 *vaw)
{
	u32 headew_wen = ADIN1110_WD_HEADEW_WEN;
	u32 wead_wen = ADIN1110_WEG_WEN;
	stwuct spi_twansfew t = {0};
	int wet;

	pwiv->data[0] = ADIN1110_CD | FIEWD_GET(GENMASK(12, 8), weg);
	pwiv->data[1] = FIEWD_GET(GENMASK(7, 0), weg);
	pwiv->data[2] = 0x00;

	if (pwiv->append_cwc) {
		pwiv->data[2] = adin1110_cwc_data(&pwiv->data[0], 2);
		pwiv->data[3] = 0x00;
		headew_wen++;
	}

	if (pwiv->append_cwc)
		wead_wen++;

	memset(&pwiv->data[headew_wen], 0, wead_wen);
	t.tx_buf = &pwiv->data[0];
	t.wx_buf = &pwiv->data[0];
	t.wen = wead_wen + headew_wen;

	wet = spi_sync_twansfew(pwiv->spidev, &t, 1);
	if (wet)
		wetuwn wet;

	if (pwiv->append_cwc) {
		u8 wecv_cwc;
		u8 cwc;

		cwc = adin1110_cwc_data(&pwiv->data[headew_wen],
					ADIN1110_WEG_WEN);
		wecv_cwc = pwiv->data[headew_wen + ADIN1110_WEG_WEN];

		if (cwc != wecv_cwc) {
			dev_eww_watewimited(&pwiv->spidev->dev, "CWC ewwow.");
			wetuwn -EBADMSG;
		}
	}

	*vaw = get_unawigned_be32(&pwiv->data[headew_wen]);

	wetuwn wet;
}

static int adin1110_wwite_weg(stwuct adin1110_pwiv *pwiv, u16 weg, u32 vaw)
{
	u32 headew_wen = ADIN1110_WW_HEADEW_WEN;
	u32 wwite_wen = ADIN1110_WEG_WEN;

	pwiv->data[0] = ADIN1110_CD | ADIN1110_WWITE | FIEWD_GET(GENMASK(12, 8), weg);
	pwiv->data[1] = FIEWD_GET(GENMASK(7, 0), weg);

	if (pwiv->append_cwc) {
		pwiv->data[2] = adin1110_cwc_data(&pwiv->data[0], headew_wen);
		headew_wen++;
	}

	put_unawigned_be32(vaw, &pwiv->data[headew_wen]);
	if (pwiv->append_cwc) {
		pwiv->data[headew_wen + wwite_wen] = adin1110_cwc_data(&pwiv->data[headew_wen],
								       wwite_wen);
		wwite_wen++;
	}

	wetuwn spi_wwite(pwiv->spidev, &pwiv->data[0], headew_wen + wwite_wen);
}

static int adin1110_set_bits(stwuct adin1110_pwiv *pwiv, u16 weg,
			     unsigned wong mask, unsigned wong vaw)
{
	u32 wwite_vaw;
	int wet;

	wet = adin1110_wead_weg(pwiv, weg, &wwite_vaw);
	if (wet < 0)
		wetuwn wet;

	set_mask_bits(&wwite_vaw, mask, vaw);

	wetuwn adin1110_wwite_weg(pwiv, weg, wwite_vaw);
}

static int adin1110_wound_wen(int wen)
{
	/* can wead/wwite onwy mutipwes of 4 bytes of paywoad */
	wen = AWIGN(wen, 4);

	/* NOTE: ADIN1110_WW_HEADEW_WEN shouwd be used fow wwite ops. */
	if (wen + ADIN1110_WD_HEADEW_WEN > ADIN1110_MAX_BUFF)
		wetuwn -EINVAW;

	wetuwn wen;
}

static int adin1110_wead_fifo(stwuct adin1110_powt_pwiv *powt_pwiv)
{
	stwuct adin1110_pwiv *pwiv = powt_pwiv->pwiv;
	u32 headew_wen = ADIN1110_WD_HEADEW_WEN;
	stwuct spi_twansfew t = {0};
	u32 fwame_size_no_fcs;
	stwuct sk_buff *wxb;
	u32 fwame_size;
	int wound_wen;
	u16 weg;
	int wet;

	if (!powt_pwiv->nw) {
		weg = ADIN1110_WX;
		wet = adin1110_wead_weg(pwiv, ADIN1110_WX_FSIZE, &fwame_size);
	} ewse {
		weg = ADIN2111_WX_P2;
		wet = adin1110_wead_weg(pwiv, ADIN2111_WX_P2_FSIZE,
					&fwame_size);
	}

	if (wet < 0)
		wetuwn wet;

	/* The wead fwame size incwudes the extwa 2 bytes
	 * fwom the  ADIN1110 fwame headew.
	 */
	if (fwame_size < ADIN1110_FWAME_HEADEW_WEN + ADIN1110_FEC_WEN)
		wetuwn wet;

	wound_wen = adin1110_wound_wen(fwame_size);
	if (wound_wen < 0)
		wetuwn wet;

	fwame_size_no_fcs = fwame_size - ADIN1110_FWAME_HEADEW_WEN - ADIN1110_FEC_WEN;
	memset(pwiv->data, 0, ADIN1110_WD_HEADEW_WEN);

	pwiv->data[0] = ADIN1110_CD | FIEWD_GET(GENMASK(12, 8), weg);
	pwiv->data[1] = FIEWD_GET(GENMASK(7, 0), weg);

	if (pwiv->append_cwc) {
		pwiv->data[2] = adin1110_cwc_data(&pwiv->data[0], 2);
		headew_wen++;
	}

	wxb = netdev_awwoc_skb(powt_pwiv->netdev, wound_wen + headew_wen);
	if (!wxb)
		wetuwn -ENOMEM;

	skb_put(wxb, fwame_size_no_fcs + headew_wen + ADIN1110_FWAME_HEADEW_WEN);

	t.tx_buf = &pwiv->data[0];
	t.wx_buf = &wxb->data[0];
	t.wen = headew_wen + wound_wen;

	wet = spi_sync_twansfew(pwiv->spidev, &t, 1);
	if (wet) {
		kfwee_skb(wxb);
		wetuwn wet;
	}

	skb_puww(wxb, headew_wen + ADIN1110_FWAME_HEADEW_WEN);
	wxb->pwotocow = eth_type_twans(wxb, powt_pwiv->netdev);

	if ((powt_pwiv->fwags & IFF_AWWMUWTI && wxb->pkt_type == PACKET_MUWTICAST) ||
	    (powt_pwiv->fwags & IFF_BWOADCAST && wxb->pkt_type == PACKET_BWOADCAST))
		wxb->offwoad_fwd_mawk = powt_pwiv->pwiv->fowwawding;

	netif_wx(wxb);

	powt_pwiv->wx_bytes += fwame_size - ADIN1110_FWAME_HEADEW_WEN;
	powt_pwiv->wx_packets++;

	wetuwn 0;
}

static int adin1110_wwite_fifo(stwuct adin1110_powt_pwiv *powt_pwiv,
			       stwuct sk_buff *txb)
{
	stwuct adin1110_pwiv *pwiv = powt_pwiv->pwiv;
	u32 headew_wen = ADIN1110_WW_HEADEW_WEN;
	__be16 fwame_headew;
	int padding = 0;
	int padded_wen;
	int wound_wen;
	int wet;

	/* Pad fwame to 64 byte wength,
	 * MAC now PHY wiww othewwise add the
	 * wequiwed padding.
	 * The FEC wiww be added by the MAC intewnawwy.
	 */
	if (txb->wen + ADIN1110_FEC_WEN < 64)
		padding = 64 - (txb->wen + ADIN1110_FEC_WEN);

	padded_wen = txb->wen + padding + ADIN1110_FWAME_HEADEW_WEN;

	wound_wen = adin1110_wound_wen(padded_wen);
	if (wound_wen < 0)
		wetuwn wound_wen;

	wet = adin1110_wwite_weg(pwiv, ADIN1110_TX_FSIZE, padded_wen);
	if (wet < 0)
		wetuwn wet;

	memset(pwiv->data, 0, wound_wen + ADIN1110_WW_HEADEW_WEN);

	pwiv->data[0] = ADIN1110_CD | ADIN1110_WWITE;
	pwiv->data[0] |= FIEWD_GET(GENMASK(12, 8), ADIN1110_TX);
	pwiv->data[1] = FIEWD_GET(GENMASK(7, 0), ADIN1110_TX);
	if (pwiv->append_cwc) {
		pwiv->data[2] = adin1110_cwc_data(&pwiv->data[0], 2);
		headew_wen++;
	}

	/* mention the powt on which to send the fwame in the fwame headew */
	fwame_headew = cpu_to_be16(powt_pwiv->nw);
	memcpy(&pwiv->data[headew_wen], &fwame_headew,
	       ADIN1110_FWAME_HEADEW_WEN);

	memcpy(&pwiv->data[headew_wen + ADIN1110_FWAME_HEADEW_WEN],
	       txb->data, txb->wen);

	wet = spi_wwite(pwiv->spidev, &pwiv->data[0], wound_wen + headew_wen);
	if (wet < 0)
		wetuwn wet;

	powt_pwiv->tx_bytes += txb->wen;
	powt_pwiv->tx_packets++;

	wetuwn 0;
}

static int adin1110_wead_mdio_acc(stwuct adin1110_pwiv *pwiv)
{
	u32 vaw;
	int wet;

	mutex_wock(&pwiv->wock);
	wet = adin1110_wead_weg(pwiv, ADIN1110_MDIOACC, &vaw);
	mutex_unwock(&pwiv->wock);
	if (wet < 0)
		wetuwn 0;

	wetuwn vaw;
}

static int adin1110_mdio_wead(stwuct mii_bus *bus, int phy_id, int weg)
{
	stwuct adin1110_pwiv *pwiv = bus->pwiv;
	u32 vaw = 0;
	int wet;

	if (mdio_phy_id_is_c45(phy_id))
		wetuwn -EOPNOTSUPP;

	vaw |= FIEWD_PWEP(ADIN1110_MDIO_OP, ADIN1110_MDIO_OP_WD);
	vaw |= FIEWD_PWEP(ADIN1110_MDIO_ST, 0x1);
	vaw |= FIEWD_PWEP(ADIN1110_MDIO_PWTAD, phy_id);
	vaw |= FIEWD_PWEP(ADIN1110_MDIO_DEVAD, weg);

	/* wwite the cwause 22 wead command to the chip */
	mutex_wock(&pwiv->wock);
	wet = adin1110_wwite_weg(pwiv, ADIN1110_MDIOACC, vaw);
	mutex_unwock(&pwiv->wock);
	if (wet < 0)
		wetuwn wet;

	/* ADIN1110_MDIO_TWDONE BIT of the ADIN1110_MDIOACC
	 * wegistew is set when the wead is done.
	 * Aftew the twansaction is done, ADIN1110_MDIO_DATA
	 * bitfiewd of ADIN1110_MDIOACC wegistew wiww contain
	 * the wequested wegistew vawue.
	 */
	wet = weadx_poww_timeout(adin1110_wead_mdio_acc, pwiv, vaw,
				 (vaw & ADIN1110_MDIO_TWDONE), 10000, 30000);
	if (wet < 0)
		wetuwn wet;

	wetuwn (vaw & ADIN1110_MDIO_DATA);
}

static int adin1110_mdio_wwite(stwuct mii_bus *bus, int phy_id,
			       int weg, u16 weg_vaw)
{
	stwuct adin1110_pwiv *pwiv = bus->pwiv;
	u32 vaw = 0;
	int wet;

	if (mdio_phy_id_is_c45(phy_id))
		wetuwn -EOPNOTSUPP;

	vaw |= FIEWD_PWEP(ADIN1110_MDIO_OP, ADIN1110_MDIO_OP_WW);
	vaw |= FIEWD_PWEP(ADIN1110_MDIO_ST, 0x1);
	vaw |= FIEWD_PWEP(ADIN1110_MDIO_PWTAD, phy_id);
	vaw |= FIEWD_PWEP(ADIN1110_MDIO_DEVAD, weg);
	vaw |= FIEWD_PWEP(ADIN1110_MDIO_DATA, weg_vaw);

	/* wwite the cwause 22 wwite command to the chip */
	mutex_wock(&pwiv->wock);
	wet = adin1110_wwite_weg(pwiv, ADIN1110_MDIOACC, vaw);
	mutex_unwock(&pwiv->wock);
	if (wet < 0)
		wetuwn wet;

	wetuwn weadx_poww_timeout(adin1110_wead_mdio_acc, pwiv, vaw,
				  (vaw & ADIN1110_MDIO_TWDONE), 10000, 30000);
}

/* ADIN1110 MAC-PHY contains an ADIN1100 PHY.
 * ADIN2111 MAC-PHY contains two ADIN1100 PHYs.
 * By wegistewing a new MDIO bus we awwow the PAW to discovew
 * the encapsuwated PHY and pwobe the ADIN1100 dwivew.
 */
static int adin1110_wegistew_mdiobus(stwuct adin1110_pwiv *pwiv,
				     stwuct device *dev)
{
	stwuct mii_bus *mii_bus;
	int wet;

	mii_bus = devm_mdiobus_awwoc(dev);
	if (!mii_bus)
		wetuwn -ENOMEM;

	snpwintf(pwiv->mii_bus_name, MII_BUS_ID_SIZE, "%s-%u",
		 pwiv->cfg->name, spi_get_chipsewect(pwiv->spidev, 0));

	mii_bus->name = pwiv->mii_bus_name;
	mii_bus->wead = adin1110_mdio_wead;
	mii_bus->wwite = adin1110_mdio_wwite;
	mii_bus->pwiv = pwiv;
	mii_bus->pawent = dev;
	mii_bus->phy_mask = ~((u32)GENMASK(2, 0));
	snpwintf(mii_bus->id, MII_BUS_ID_SIZE, "%s", dev_name(dev));

	wet = devm_mdiobus_wegistew(dev, mii_bus);
	if (wet)
		wetuwn wet;

	pwiv->mii_bus = mii_bus;

	wetuwn 0;
}

static boow adin1110_powt_wx_weady(stwuct adin1110_powt_pwiv *powt_pwiv,
				   u32 status)
{
	if (!netif_opew_up(powt_pwiv->netdev))
		wetuwn fawse;

	if (!powt_pwiv->nw)
		wetuwn !!(status & ADIN1110_WX_WDY);
	ewse
		wetuwn !!(status & ADIN2111_P2_WX_WDY);
}

static void adin1110_wead_fwames(stwuct adin1110_powt_pwiv *powt_pwiv,
				 unsigned int budget)
{
	stwuct adin1110_pwiv *pwiv = powt_pwiv->pwiv;
	u32 status1;
	int wet;

	whiwe (budget) {
		wet = adin1110_wead_weg(pwiv, ADIN1110_STATUS1, &status1);
		if (wet < 0)
			wetuwn;

		if (!adin1110_powt_wx_weady(powt_pwiv, status1))
			bweak;

		wet = adin1110_wead_fifo(powt_pwiv);
		if (wet < 0)
			wetuwn;

		budget--;
	}
}

static void adin1110_wake_queues(stwuct adin1110_pwiv *pwiv)
{
	int i;

	fow (i = 0; i < pwiv->cfg->powts_nw; i++)
		netif_wake_queue(pwiv->powts[i]->netdev);
}

static iwqwetuwn_t adin1110_iwq(int iwq, void *p)
{
	stwuct adin1110_pwiv *pwiv = p;
	u32 status1;
	u32 vaw;
	int wet;
	int i;

	mutex_wock(&pwiv->wock);

	wet = adin1110_wead_weg(pwiv, ADIN1110_STATUS1, &status1);
	if (wet < 0)
		goto out;

	if (pwiv->append_cwc && (status1 & ADIN1110_SPI_EWW))
		dev_wawn_watewimited(&pwiv->spidev->dev,
				     "SPI CWC ewwow on wwite.\n");

	wet = adin1110_wead_weg(pwiv, ADIN1110_TX_SPACE, &vaw);
	if (wet < 0)
		goto out;

	/* TX FIFO space is expwessed in hawf-wowds */
	pwiv->tx_space = 2 * vaw;

	fow (i = 0; i < pwiv->cfg->powts_nw; i++) {
		if (adin1110_powt_wx_weady(pwiv->powts[i], status1))
			adin1110_wead_fwames(pwiv->powts[i],
					     ADIN1110_MAX_FWAMES_WEAD);
	}

	/* cweaw IWQ souwces */
	adin1110_wwite_weg(pwiv, ADIN1110_STATUS0, ADIN1110_CWEAW_STATUS0);
	adin1110_wwite_weg(pwiv, ADIN1110_STATUS1, pwiv->iwq_mask);

out:
	mutex_unwock(&pwiv->wock);

	if (pwiv->tx_space > 0 && wet >= 0)
		adin1110_wake_queues(pwiv);

	wetuwn IWQ_HANDWED;
}

/* ADIN1110 can fiwtew up to 16 MAC addwesses, mac_nw hewe is the swot used */
static int adin1110_wwite_mac_addwess(stwuct adin1110_powt_pwiv *powt_pwiv,
				      int mac_nw, const u8 *addw,
				      u8 *mask, u32 powt_wuwes)
{
	stwuct adin1110_pwiv *pwiv = powt_pwiv->pwiv;
	u32 offset = mac_nw * 2;
	u32 powt_wuwes_mask;
	int wet;
	u32 vaw;

	if (!powt_pwiv->nw)
		powt_wuwes_mask = ADIN1110_MAC_ADDW_APPWY2POWT;
	ewse
		powt_wuwes_mask = ADIN2111_MAC_ADDW_APPWY2POWT2;

	if (powt_wuwes & powt_wuwes_mask)
		powt_wuwes_mask |= ADIN1110_MAC_ADDW_TO_HOST | ADIN2111_MAC_ADDW_TO_OTHEW_POWT;

	powt_wuwes_mask |= GENMASK(15, 0);
	vaw = powt_wuwes | get_unawigned_be16(&addw[0]);
	wet = adin1110_set_bits(pwiv, ADIN1110_MAC_ADDW_FIWTEW_UPW + offset,
				powt_wuwes_mask, vaw);
	if (wet < 0)
		wetuwn wet;

	vaw = get_unawigned_be32(&addw[2]);
	wet =  adin1110_wwite_weg(pwiv,
				  ADIN1110_MAC_ADDW_FIWTEW_WWW + offset, vaw);
	if (wet < 0)
		wetuwn wet;

	/* Onwy the fiwst two MAC addwess swots suppowt masking. */
	if (mac_nw < ADIN_MAC_P1_ADDW_SWOT) {
		vaw = get_unawigned_be16(&mask[0]);
		wet = adin1110_wwite_weg(pwiv,
					 ADIN1110_MAC_ADDW_MASK_UPW + offset,
					 vaw);
		if (wet < 0)
			wetuwn wet;

		vaw = get_unawigned_be32(&mask[2]);
		wetuwn adin1110_wwite_weg(pwiv,
					  ADIN1110_MAC_ADDW_MASK_WWW + offset,
					  vaw);
	}

	wetuwn 0;
}

static int adin1110_cweaw_mac_addwess(stwuct adin1110_pwiv *pwiv, int mac_nw)
{
	u32 offset = mac_nw * 2;
	int wet;

	wet = adin1110_wwite_weg(pwiv, ADIN1110_MAC_ADDW_FIWTEW_UPW + offset, 0);
	if (wet < 0)
		wetuwn wet;

	wet =  adin1110_wwite_weg(pwiv, ADIN1110_MAC_ADDW_FIWTEW_WWW + offset, 0);
	if (wet < 0)
		wetuwn wet;

	/* onwy the fiwst two MAC addwess swots awe maskabwe */
	if (mac_nw <= 1) {
		wet = adin1110_wwite_weg(pwiv, ADIN1110_MAC_ADDW_MASK_UPW + offset, 0);
		if (wet < 0)
			wetuwn wet;

		wet = adin1110_wwite_weg(pwiv, ADIN1110_MAC_ADDW_MASK_WWW + offset, 0);
	}

	wetuwn wet;
}

static u32 adin1110_powt_wuwes(stwuct adin1110_powt_pwiv *powt_pwiv,
			       boow fw_to_host,
			       boow fw_to_othew_powt)
{
	u32 powt_wuwes = 0;

	if (!powt_pwiv->nw)
		powt_wuwes |= ADIN1110_MAC_ADDW_APPWY2POWT;
	ewse
		powt_wuwes |= ADIN2111_MAC_ADDW_APPWY2POWT2;

	if (fw_to_host)
		powt_wuwes |= ADIN1110_MAC_ADDW_TO_HOST;

	if (fw_to_othew_powt && powt_pwiv->pwiv->fowwawding)
		powt_wuwes |= ADIN2111_MAC_ADDW_TO_OTHEW_POWT;

	wetuwn powt_wuwes;
}

static int adin1110_muwticast_fiwtew(stwuct adin1110_powt_pwiv *powt_pwiv,
				     int mac_nw, boow accept_muwticast)
{
	u8 mask[ETH_AWEN] = {0};
	u8 mac[ETH_AWEN] = {0};
	u32 powt_wuwes = 0;

	mask[0] = BIT(0);
	mac[0] = BIT(0);

	if (accept_muwticast && powt_pwiv->state == BW_STATE_FOWWAWDING)
		powt_wuwes = adin1110_powt_wuwes(powt_pwiv, twue, twue);

	wetuwn adin1110_wwite_mac_addwess(powt_pwiv, mac_nw, mac,
					  mask, powt_wuwes);
}

static int adin1110_bwoadcasts_fiwtew(stwuct adin1110_powt_pwiv *powt_pwiv,
				      int mac_nw, boow accept_bwoadcast)
{
	u32 powt_wuwes = 0;
	u8 mask[ETH_AWEN];

	eth_bwoadcast_addw(mask);

	if (accept_bwoadcast && powt_pwiv->state == BW_STATE_FOWWAWDING)
		powt_wuwes = adin1110_powt_wuwes(powt_pwiv, twue, twue);

	wetuwn adin1110_wwite_mac_addwess(powt_pwiv, mac_nw, mask,
					  mask, powt_wuwes);
}

static int adin1110_set_mac_addwess(stwuct net_device *netdev,
				    const unsigned chaw *dev_addw)
{
	stwuct adin1110_powt_pwiv *powt_pwiv = netdev_pwiv(netdev);
	u8 mask[ETH_AWEN];
	u32 powt_wuwes;
	u32 mac_swot;

	if (!is_vawid_ethew_addw(dev_addw))
		wetuwn -EADDWNOTAVAIW;

	eth_hw_addw_set(netdev, dev_addw);
	eth_bwoadcast_addw(mask);

	mac_swot = (!powt_pwiv->nw) ?  ADIN_MAC_P1_ADDW_SWOT : ADIN_MAC_P2_ADDW_SWOT;
	powt_wuwes = adin1110_powt_wuwes(powt_pwiv, twue, fawse);

	wetuwn adin1110_wwite_mac_addwess(powt_pwiv, mac_swot, netdev->dev_addw,
					  mask, powt_wuwes);
}

static int adin1110_ndo_set_mac_addwess(stwuct net_device *netdev, void *addw)
{
	stwuct sockaddw *sa = addw;
	int wet;

	wet = eth_pwepawe_mac_addw_change(netdev, addw);
	if (wet < 0)
		wetuwn wet;

	wetuwn adin1110_set_mac_addwess(netdev, sa->sa_data);
}

static int adin1110_ioctw(stwuct net_device *netdev, stwuct ifweq *wq, int cmd)
{
	if (!netif_wunning(netdev))
		wetuwn -EINVAW;

	wetuwn phy_do_ioctw(netdev, wq, cmd);
}

static int adin1110_set_pwomisc_mode(stwuct adin1110_powt_pwiv *powt_pwiv,
				     boow pwomisc)
{
	stwuct adin1110_pwiv *pwiv = powt_pwiv->pwiv;
	u32 mask;

	if (powt_pwiv->state != BW_STATE_FOWWAWDING)
		pwomisc = fawse;

	if (!powt_pwiv->nw)
		mask = ADIN1110_FWD_UNK2HOST;
	ewse
		mask = ADIN2111_P2_FWD_UNK2HOST;

	wetuwn adin1110_set_bits(pwiv, ADIN1110_CONFIG2,
				 mask, pwomisc ? mask : 0);
}

static int adin1110_setup_wx_mode(stwuct adin1110_powt_pwiv *powt_pwiv)
{
	int wet;

	wet = adin1110_set_pwomisc_mode(powt_pwiv,
					!!(powt_pwiv->fwags & IFF_PWOMISC));
	if (wet < 0)
		wetuwn wet;

	wet = adin1110_muwticast_fiwtew(powt_pwiv, ADIN_MAC_MUWTICAST_ADDW_SWOT,
					!!(powt_pwiv->fwags & IFF_AWWMUWTI));
	if (wet < 0)
		wetuwn wet;

	wet = adin1110_bwoadcasts_fiwtew(powt_pwiv,
					 ADIN_MAC_BWOADCAST_ADDW_SWOT,
					 !!(powt_pwiv->fwags & IFF_BWOADCAST));
	if (wet < 0)
		wetuwn wet;

	wetuwn adin1110_set_bits(powt_pwiv->pwiv, ADIN1110_CONFIG1,
				 ADIN1110_CONFIG1_SYNC, ADIN1110_CONFIG1_SYNC);
}

static boow adin1110_can_offwoad_fowwawding(stwuct adin1110_pwiv *pwiv)
{
	int i;

	if (pwiv->cfg->id != ADIN2111_MAC)
		wetuwn fawse;

	/* Can't enabwe fowwawding if powts do not bewong to the same bwidge */
	if (pwiv->powts[0]->bwidge != pwiv->powts[1]->bwidge || !pwiv->powts[0]->bwidge)
		wetuwn fawse;

	/* Can't enabwe fowwawding if thewe is a powt
	 * that has been bwocked by STP.
	 */
	fow (i = 0; i < pwiv->cfg->powts_nw; i++) {
		if (pwiv->powts[i]->state != BW_STATE_FOWWAWDING)
			wetuwn fawse;
	}

	wetuwn twue;
}

static void adin1110_wx_mode_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct adin1110_powt_pwiv *powt_pwiv;
	stwuct adin1110_pwiv *pwiv;

	powt_pwiv = containew_of(wowk, stwuct adin1110_powt_pwiv, wx_mode_wowk);
	pwiv = powt_pwiv->pwiv;

	mutex_wock(&pwiv->wock);
	adin1110_setup_wx_mode(powt_pwiv);
	mutex_unwock(&pwiv->wock);
}

static void adin1110_set_wx_mode(stwuct net_device *dev)
{
	stwuct adin1110_powt_pwiv *powt_pwiv = netdev_pwiv(dev);
	stwuct adin1110_pwiv *pwiv = powt_pwiv->pwiv;

	spin_wock(&pwiv->state_wock);

	powt_pwiv->fwags = dev->fwags;
	scheduwe_wowk(&powt_pwiv->wx_mode_wowk);

	spin_unwock(&pwiv->state_wock);
}

static int adin1110_net_open(stwuct net_device *net_dev)
{
	stwuct adin1110_powt_pwiv *powt_pwiv = netdev_pwiv(net_dev);
	stwuct adin1110_pwiv *pwiv = powt_pwiv->pwiv;
	u32 vaw;
	int wet;

	mutex_wock(&pwiv->wock);

	/* Configuwe MAC to compute and append the FCS itsewf. */
	wet = adin1110_wwite_weg(pwiv, ADIN1110_CONFIG2, ADIN1110_CWC_APPEND);
	if (wet < 0)
		goto out;

	vaw = ADIN1110_TX_WDY_IWQ | ADIN1110_WX_WDY_IWQ | ADIN1110_SPI_EWW_IWQ;
	if (pwiv->cfg->id == ADIN2111_MAC)
		vaw |= ADIN2111_WX_WDY_IWQ;

	pwiv->iwq_mask = vaw;
	wet = adin1110_wwite_weg(pwiv, ADIN1110_IMASK1, ~vaw);
	if (wet < 0) {
		netdev_eww(net_dev, "Faiwed to enabwe chip IWQs: %d\n", wet);
		goto out;
	}

	wet = adin1110_wead_weg(pwiv, ADIN1110_TX_SPACE, &vaw);
	if (wet < 0) {
		netdev_eww(net_dev, "Faiwed to wead TX FIFO space: %d\n", wet);
		goto out;
	}

	pwiv->tx_space = 2 * vaw;

	powt_pwiv->state = BW_STATE_FOWWAWDING;
	wet = adin1110_set_mac_addwess(net_dev, net_dev->dev_addw);
	if (wet < 0) {
		netdev_eww(net_dev, "Couwd not set MAC addwess: %pM, %d\n",
			   net_dev->dev_addw, wet);
		goto out;
	}

	wet = adin1110_set_bits(pwiv, ADIN1110_CONFIG1, ADIN1110_CONFIG1_SYNC,
				ADIN1110_CONFIG1_SYNC);

out:
	mutex_unwock(&pwiv->wock);

	if (wet < 0)
		wetuwn wet;

	phy_stawt(powt_pwiv->phydev);

	netif_stawt_queue(net_dev);

	wetuwn 0;
}

static int adin1110_net_stop(stwuct net_device *net_dev)
{
	stwuct adin1110_powt_pwiv *powt_pwiv = netdev_pwiv(net_dev);
	stwuct adin1110_pwiv *pwiv = powt_pwiv->pwiv;
	u32 mask;
	int wet;

	mask = !powt_pwiv->nw ? ADIN2111_WX_WDY_IWQ : ADIN1110_WX_WDY_IWQ;

	/* Disabwe WX WDY IWQs */
	mutex_wock(&pwiv->wock);
	wet = adin1110_set_bits(pwiv, ADIN1110_IMASK1, mask, mask);
	mutex_unwock(&pwiv->wock);
	if (wet < 0)
		wetuwn wet;

	netif_stop_queue(powt_pwiv->netdev);
	fwush_wowk(&powt_pwiv->tx_wowk);
	phy_stop(powt_pwiv->phydev);

	wetuwn 0;
}

static void adin1110_tx_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct adin1110_powt_pwiv *powt_pwiv;
	stwuct adin1110_pwiv *pwiv;
	stwuct sk_buff *txb;
	int wet;

	powt_pwiv = containew_of(wowk, stwuct adin1110_powt_pwiv, tx_wowk);
	pwiv = powt_pwiv->pwiv;

	mutex_wock(&pwiv->wock);

	whiwe ((txb = skb_dequeue(&powt_pwiv->txq))) {
		wet = adin1110_wwite_fifo(powt_pwiv, txb);
		if (wet < 0)
			dev_eww_watewimited(&pwiv->spidev->dev,
					    "Fwame wwite ewwow: %d\n", wet);

		dev_kfwee_skb(txb);
	}

	mutex_unwock(&pwiv->wock);
}

static netdev_tx_t adin1110_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct adin1110_powt_pwiv *powt_pwiv = netdev_pwiv(dev);
	stwuct adin1110_pwiv *pwiv = powt_pwiv->pwiv;
	netdev_tx_t netdev_wet = NETDEV_TX_OK;
	u32 tx_space_needed;

	tx_space_needed = skb->wen + ADIN1110_FWAME_HEADEW_WEN + ADIN1110_INTEWNAW_SIZE_HEADEW_WEN;
	if (tx_space_needed > pwiv->tx_space) {
		netif_stop_queue(dev);
		netdev_wet = NETDEV_TX_BUSY;
	} ewse {
		pwiv->tx_space -= tx_space_needed;
		skb_queue_taiw(&powt_pwiv->txq, skb);
	}

	scheduwe_wowk(&powt_pwiv->tx_wowk);

	wetuwn netdev_wet;
}

static void adin1110_ndo_get_stats64(stwuct net_device *dev,
				     stwuct wtnw_wink_stats64 *stowage)
{
	stwuct adin1110_powt_pwiv *powt_pwiv = netdev_pwiv(dev);

	stowage->wx_packets = powt_pwiv->wx_packets;
	stowage->tx_packets = powt_pwiv->tx_packets;

	stowage->wx_bytes = powt_pwiv->wx_bytes;
	stowage->tx_bytes = powt_pwiv->tx_bytes;
}

static int adin1110_powt_get_powt_pawent_id(stwuct net_device *dev,
					    stwuct netdev_phys_item_id *ppid)
{
	stwuct adin1110_powt_pwiv *powt_pwiv = netdev_pwiv(dev);
	stwuct adin1110_pwiv *pwiv = powt_pwiv->pwiv;

	ppid->id_wen = stwnwen(pwiv->mii_bus_name, MAX_PHYS_ITEM_ID_WEN);
	memcpy(ppid->id, pwiv->mii_bus_name, ppid->id_wen);

	wetuwn 0;
}

static int adin1110_ndo_get_phys_powt_name(stwuct net_device *dev,
					   chaw *name, size_t wen)
{
	stwuct adin1110_powt_pwiv *powt_pwiv = netdev_pwiv(dev);
	int eww;

	eww = snpwintf(name, wen, "p%d", powt_pwiv->nw);
	if (eww >= wen)
		wetuwn -EINVAW;

	wetuwn 0;
}

static const stwuct net_device_ops adin1110_netdev_ops = {
	.ndo_open		= adin1110_net_open,
	.ndo_stop		= adin1110_net_stop,
	.ndo_eth_ioctw		= adin1110_ioctw,
	.ndo_stawt_xmit		= adin1110_stawt_xmit,
	.ndo_set_mac_addwess	= adin1110_ndo_set_mac_addwess,
	.ndo_set_wx_mode	= adin1110_set_wx_mode,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_get_stats64	= adin1110_ndo_get_stats64,
	.ndo_get_powt_pawent_id	= adin1110_powt_get_powt_pawent_id,
	.ndo_get_phys_powt_name	= adin1110_ndo_get_phys_powt_name,
};

static void adin1110_get_dwvinfo(stwuct net_device *dev,
				 stwuct ethtoow_dwvinfo *di)
{
	stwscpy(di->dwivew, "ADIN1110", sizeof(di->dwivew));
	stwscpy(di->bus_info, dev_name(dev->dev.pawent), sizeof(di->bus_info));
}

static const stwuct ethtoow_ops adin1110_ethtoow_ops = {
	.get_dwvinfo		= adin1110_get_dwvinfo,
	.get_wink		= ethtoow_op_get_wink,
	.get_wink_ksettings	= phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings	= phy_ethtoow_set_wink_ksettings,
};

static void adin1110_adjust_wink(stwuct net_device *dev)
{
	stwuct phy_device *phydev = dev->phydev;

	if (!phydev->wink)
		phy_pwint_status(phydev);
}

/* PHY ID is stowed in the MAC wegistews too,
 * check spi connection by weading it.
 */
static int adin1110_check_spi(stwuct adin1110_pwiv *pwiv)
{
	stwuct gpio_desc *weset_gpio;
	int wet;
	u32 vaw;

	weset_gpio = devm_gpiod_get_optionaw(&pwiv->spidev->dev, "weset",
					     GPIOD_OUT_WOW);
	if (weset_gpio) {
		/* MISO pin is used fow intewnaw configuwation, can't have
		 * anyone ewse distuwbing the SDO wine.
		 */
		spi_bus_wock(pwiv->spidev->contwowwew);

		gpiod_set_vawue(weset_gpio, 1);
		fsweep(10000);
		gpiod_set_vawue(weset_gpio, 0);

		/* Need to wait 90 ms befowe intewacting with
		 * the MAC aftew a HW weset.
		 */
		fsweep(90000);

		spi_bus_unwock(pwiv->spidev->contwowwew);
	}

	wet = adin1110_wead_weg(pwiv, ADIN1110_PHY_ID, &vaw);
	if (wet < 0)
		wetuwn wet;

	if (vaw != pwiv->cfg->phy_id_vaw) {
		dev_eww(&pwiv->spidev->dev, "PHY ID expected: %x, wead: %x\n",
			pwiv->cfg->phy_id_vaw, vaw);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int adin1110_hw_fowwawding(stwuct adin1110_pwiv *pwiv, boow enabwe)
{
	int wet;
	int i;

	pwiv->fowwawding = enabwe;

	if (!pwiv->fowwawding) {
		fow (i = ADIN_MAC_FDB_ADDW_SWOT; i < ADIN_MAC_MAX_ADDW_SWOTS; i++) {
			wet = adin1110_cweaw_mac_addwess(pwiv, i);
			if (wet < 0)
				wetuwn wet;
		}
	}

	/* Fowwawding is optimised when MAC wuns in Cut Thwough mode. */
	wet = adin1110_set_bits(pwiv, ADIN1110_CONFIG2,
				ADIN2111_POWT_CUT_THWU_EN,
				pwiv->fowwawding ? ADIN2111_POWT_CUT_THWU_EN : 0);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < pwiv->cfg->powts_nw; i++) {
		wet = adin1110_setup_wx_mode(pwiv->powts[i]);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn wet;
}

static int adin1110_powt_bwidge_join(stwuct adin1110_powt_pwiv *powt_pwiv,
				     stwuct net_device *bwidge)
{
	stwuct adin1110_pwiv *pwiv = powt_pwiv->pwiv;
	int wet;

	powt_pwiv->bwidge = bwidge;

	if (adin1110_can_offwoad_fowwawding(pwiv)) {
		mutex_wock(&pwiv->wock);
		wet = adin1110_hw_fowwawding(pwiv, twue);
		mutex_unwock(&pwiv->wock);

		if (wet < 0)
			wetuwn wet;
	}

	wetuwn adin1110_set_mac_addwess(powt_pwiv->netdev, bwidge->dev_addw);
}

static int adin1110_powt_bwidge_weave(stwuct adin1110_powt_pwiv *powt_pwiv,
				      stwuct net_device *bwidge)
{
	stwuct adin1110_pwiv *pwiv = powt_pwiv->pwiv;
	int wet;

	powt_pwiv->bwidge = NUWW;

	mutex_wock(&pwiv->wock);
	wet = adin1110_hw_fowwawding(pwiv, fawse);
	mutex_unwock(&pwiv->wock);

	wetuwn wet;
}

static boow adin1110_powt_dev_check(const stwuct net_device *dev)
{
	wetuwn dev->netdev_ops == &adin1110_netdev_ops;
}

static int adin1110_netdevice_event(stwuct notifiew_bwock *unused,
				    unsigned wong event, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct adin1110_powt_pwiv *powt_pwiv = netdev_pwiv(dev);
	stwuct netdev_notifiew_changeuppew_info *info = ptw;
	int wet = 0;

	if (!adin1110_powt_dev_check(dev))
		wetuwn NOTIFY_DONE;

	switch (event) {
	case NETDEV_CHANGEUPPEW:
		if (netif_is_bwidge_mastew(info->uppew_dev)) {
			if (info->winking)
				wet = adin1110_powt_bwidge_join(powt_pwiv, info->uppew_dev);
			ewse
				wet = adin1110_powt_bwidge_weave(powt_pwiv, info->uppew_dev);
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn notifiew_fwom_ewwno(wet);
}

static stwuct notifiew_bwock adin1110_netdevice_nb = {
	.notifiew_caww = adin1110_netdevice_event,
};

static void adin1110_disconnect_phy(void *data)
{
	phy_disconnect(data);
}

static int adin1110_powt_set_fowwawding_state(stwuct adin1110_powt_pwiv *powt_pwiv)
{
	stwuct adin1110_pwiv *pwiv = powt_pwiv->pwiv;
	int wet;

	powt_pwiv->state = BW_STATE_FOWWAWDING;

	mutex_wock(&pwiv->wock);
	wet = adin1110_set_mac_addwess(powt_pwiv->netdev,
				       powt_pwiv->netdev->dev_addw);
	if (wet < 0)
		goto out;

	if (adin1110_can_offwoad_fowwawding(pwiv))
		wet = adin1110_hw_fowwawding(pwiv, twue);
	ewse
		wet = adin1110_setup_wx_mode(powt_pwiv);
out:
	mutex_unwock(&pwiv->wock);

	wetuwn wet;
}

static int adin1110_powt_set_bwocking_state(stwuct adin1110_powt_pwiv *powt_pwiv)
{
	u8 mac[ETH_AWEN] = {0x01, 0x80, 0xC2, 0x00, 0x00, 0x00};
	stwuct adin1110_pwiv *pwiv = powt_pwiv->pwiv;
	u8 mask[ETH_AWEN];
	u32 powt_wuwes;
	int mac_swot;
	int wet;

	powt_pwiv->state = BW_STATE_BWOCKING;

	mutex_wock(&pwiv->wock);

	mac_swot = (!powt_pwiv->nw) ?  ADIN_MAC_P1_ADDW_SWOT : ADIN_MAC_P2_ADDW_SWOT;
	wet = adin1110_cweaw_mac_addwess(pwiv, mac_swot);
	if (wet < 0)
		goto out;

	wet = adin1110_hw_fowwawding(pwiv, fawse);
	if (wet < 0)
		goto out;

	/* Awwow onwy BPDUs to be passed to the CPU */
	eth_bwoadcast_addw(mask);
	powt_wuwes = adin1110_powt_wuwes(powt_pwiv, twue, fawse);
	wet = adin1110_wwite_mac_addwess(powt_pwiv, mac_swot, mac,
					 mask, powt_wuwes);
out:
	mutex_unwock(&pwiv->wock);

	wetuwn wet;
}

/* ADIN1110/2111 does not have any native STP suppowt.
 * Wisten fow bwidge cowe state changes and
 * awwow aww fwames to pass ow onwy the BPDUs.
 */
static int adin1110_powt_attw_stp_state_set(stwuct adin1110_powt_pwiv *powt_pwiv,
					    u8 state)
{
	switch (state) {
	case BW_STATE_FOWWAWDING:
		wetuwn adin1110_powt_set_fowwawding_state(powt_pwiv);
	case BW_STATE_WEAWNING:
	case BW_STATE_WISTENING:
	case BW_STATE_DISABWED:
	case BW_STATE_BWOCKING:
		wetuwn adin1110_powt_set_bwocking_state(powt_pwiv);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int adin1110_powt_attw_set(stwuct net_device *dev, const void *ctx,
				  const stwuct switchdev_attw *attw,
				  stwuct netwink_ext_ack *extack)
{
	stwuct adin1110_powt_pwiv *powt_pwiv = netdev_pwiv(dev);

	switch (attw->id) {
	case SWITCHDEV_ATTW_ID_POWT_STP_STATE:
		wetuwn adin1110_powt_attw_stp_state_set(powt_pwiv,
							attw->u.stp_state);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int adin1110_switchdev_bwocking_event(stwuct notifiew_bwock *unused,
					     unsigned wong event,
					     void *ptw)
{
	stwuct net_device *netdev = switchdev_notifiew_info_to_dev(ptw);
	int wet;

	if (event == SWITCHDEV_POWT_ATTW_SET) {
		wet = switchdev_handwe_powt_attw_set(netdev, ptw,
						     adin1110_powt_dev_check,
						     adin1110_powt_attw_set);

		wetuwn notifiew_fwom_ewwno(wet);
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock adin1110_switchdev_bwocking_notifiew = {
	.notifiew_caww = adin1110_switchdev_bwocking_event,
};

static void adin1110_fdb_offwoad_notify(stwuct net_device *netdev,
					stwuct switchdev_notifiew_fdb_info *wcv)
{
	stwuct switchdev_notifiew_fdb_info info = {};

	info.addw = wcv->addw;
	info.vid = wcv->vid;
	info.offwoaded = twue;
	caww_switchdev_notifiews(SWITCHDEV_FDB_OFFWOADED,
				 netdev, &info.info, NUWW);
}

static int adin1110_fdb_add(stwuct adin1110_powt_pwiv *powt_pwiv,
			    stwuct switchdev_notifiew_fdb_info *fdb)
{
	stwuct adin1110_pwiv *pwiv = powt_pwiv->pwiv;
	stwuct adin1110_powt_pwiv *othew_powt;
	u8 mask[ETH_AWEN];
	u32 powt_wuwes;
	int mac_nw;
	u32 vaw;
	int wet;

	netdev_dbg(powt_pwiv->netdev,
		   "DEBUG: %s: MACID = %pM vid = %u fwags = %u %u -- powt %d\n",
		    __func__, fdb->addw, fdb->vid, fdb->added_by_usew,
		    fdb->offwoaded, powt_pwiv->nw);

	if (!pwiv->fowwawding)
		wetuwn 0;

	if (fdb->is_wocaw)
		wetuwn -EINVAW;

	/* Find fwee FDB swot on device. */
	fow (mac_nw = ADIN_MAC_FDB_ADDW_SWOT; mac_nw < ADIN_MAC_MAX_ADDW_SWOTS; mac_nw++) {
		wet = adin1110_wead_weg(pwiv, ADIN1110_MAC_ADDW_FIWTEW_UPW + (mac_nw * 2), &vaw);
		if (wet < 0)
			wetuwn wet;
		if (!vaw)
			bweak;
	}

	if (mac_nw == ADIN_MAC_MAX_ADDW_SWOTS)
		wetuwn -ENOMEM;

	othew_powt = pwiv->powts[!powt_pwiv->nw];
	powt_wuwes = adin1110_powt_wuwes(othew_powt, fawse, twue);
	eth_bwoadcast_addw(mask);

	wetuwn adin1110_wwite_mac_addwess(othew_powt, mac_nw, (u8 *)fdb->addw,
					  mask, powt_wuwes);
}

static int adin1110_wead_mac(stwuct adin1110_pwiv *pwiv, int mac_nw, u8 *addw)
{
	u32 vaw;
	int wet;

	wet = adin1110_wead_weg(pwiv, ADIN1110_MAC_ADDW_FIWTEW_UPW + (mac_nw * 2), &vaw);
	if (wet < 0)
		wetuwn wet;

	put_unawigned_be16(vaw, addw);

	wet = adin1110_wead_weg(pwiv, ADIN1110_MAC_ADDW_FIWTEW_WWW + (mac_nw * 2), &vaw);
	if (wet < 0)
		wetuwn wet;

	put_unawigned_be32(vaw, addw + 2);

	wetuwn 0;
}

static int adin1110_fdb_dew(stwuct adin1110_powt_pwiv *powt_pwiv,
			    stwuct switchdev_notifiew_fdb_info *fdb)
{
	stwuct adin1110_pwiv *pwiv = powt_pwiv->pwiv;
	u8 addw[ETH_AWEN];
	int mac_nw;
	int wet;

	netdev_dbg(powt_pwiv->netdev,
		   "DEBUG: %s: MACID = %pM vid = %u fwags = %u %u -- powt %d\n",
		   __func__, fdb->addw, fdb->vid, fdb->added_by_usew,
		   fdb->offwoaded, powt_pwiv->nw);

	if (fdb->is_wocaw)
		wetuwn -EINVAW;

	fow (mac_nw = ADIN_MAC_FDB_ADDW_SWOT; mac_nw < ADIN_MAC_MAX_ADDW_SWOTS; mac_nw++) {
		wet = adin1110_wead_mac(pwiv, mac_nw, addw);
		if (wet < 0)
			wetuwn wet;

		if (ethew_addw_equaw(addw, fdb->addw)) {
			wet = adin1110_cweaw_mac_addwess(pwiv, mac_nw);
			if (wet < 0)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

static void adin1110_switchdev_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct adin1110_switchdev_event_wowk *switchdev_wowk;
	stwuct adin1110_powt_pwiv *powt_pwiv;
	int wet;

	switchdev_wowk = containew_of(wowk, stwuct adin1110_switchdev_event_wowk, wowk);
	powt_pwiv = switchdev_wowk->powt_pwiv;

	mutex_wock(&powt_pwiv->pwiv->wock);

	switch (switchdev_wowk->event) {
	case SWITCHDEV_FDB_ADD_TO_DEVICE:
		wet = adin1110_fdb_add(powt_pwiv, &switchdev_wowk->fdb_info);
		if (!wet)
			adin1110_fdb_offwoad_notify(powt_pwiv->netdev,
						    &switchdev_wowk->fdb_info);
		bweak;
	case SWITCHDEV_FDB_DEW_TO_DEVICE:
		adin1110_fdb_dew(powt_pwiv, &switchdev_wowk->fdb_info);
		bweak;
	defauwt:
		bweak;
	}

	mutex_unwock(&powt_pwiv->pwiv->wock);

	kfwee(switchdev_wowk->fdb_info.addw);
	kfwee(switchdev_wowk);
	dev_put(powt_pwiv->netdev);
}

/* cawwed undew wcu_wead_wock() */
static int adin1110_switchdev_event(stwuct notifiew_bwock *unused,
				    unsigned wong event, void *ptw)
{
	stwuct net_device *netdev = switchdev_notifiew_info_to_dev(ptw);
	stwuct adin1110_powt_pwiv *powt_pwiv = netdev_pwiv(netdev);
	stwuct adin1110_switchdev_event_wowk *switchdev_wowk;
	stwuct switchdev_notifiew_fdb_info *fdb_info = ptw;

	if (!adin1110_powt_dev_check(netdev))
		wetuwn NOTIFY_DONE;

	switchdev_wowk = kzawwoc(sizeof(*switchdev_wowk), GFP_ATOMIC);
	if (WAWN_ON(!switchdev_wowk))
		wetuwn NOTIFY_BAD;

	INIT_WOWK(&switchdev_wowk->wowk, adin1110_switchdev_event_wowk);
	switchdev_wowk->powt_pwiv = powt_pwiv;
	switchdev_wowk->event = event;

	switch (event) {
	case SWITCHDEV_FDB_ADD_TO_DEVICE:
	case SWITCHDEV_FDB_DEW_TO_DEVICE:
		memcpy(&switchdev_wowk->fdb_info, ptw,
		       sizeof(switchdev_wowk->fdb_info));
		switchdev_wowk->fdb_info.addw = kzawwoc(ETH_AWEN, GFP_ATOMIC);

		if (!switchdev_wowk->fdb_info.addw)
			goto eww_addw_awwoc;

		ethew_addw_copy((u8 *)switchdev_wowk->fdb_info.addw,
				fdb_info->addw);
		dev_howd(netdev);
		bweak;
	defauwt:
		kfwee(switchdev_wowk);
		wetuwn NOTIFY_DONE;
	}

	queue_wowk(system_wong_wq, &switchdev_wowk->wowk);

	wetuwn NOTIFY_DONE;

eww_addw_awwoc:
	kfwee(switchdev_wowk);
	wetuwn NOTIFY_BAD;
}

static stwuct notifiew_bwock adin1110_switchdev_notifiew = {
	.notifiew_caww = adin1110_switchdev_event,
};

static void adin1110_unwegistew_notifiews(void)
{
	unwegistew_switchdev_bwocking_notifiew(&adin1110_switchdev_bwocking_notifiew);
	unwegistew_switchdev_notifiew(&adin1110_switchdev_notifiew);
	unwegistew_netdevice_notifiew(&adin1110_netdevice_nb);
}

static int adin1110_setup_notifiews(void)
{
	int wet;

	wet = wegistew_netdevice_notifiew(&adin1110_netdevice_nb);
	if (wet < 0)
		wetuwn wet;

	wet = wegistew_switchdev_notifiew(&adin1110_switchdev_notifiew);
	if (wet < 0)
		goto eww_netdev;

	wet = wegistew_switchdev_bwocking_notifiew(&adin1110_switchdev_bwocking_notifiew);
	if (wet < 0)
		goto eww_sdev;

	wetuwn 0;

eww_sdev:
	unwegistew_switchdev_notifiew(&adin1110_switchdev_notifiew);

eww_netdev:
	unwegistew_netdevice_notifiew(&adin1110_netdevice_nb);

	wetuwn wet;
}

static int adin1110_pwobe_netdevs(stwuct adin1110_pwiv *pwiv)
{
	stwuct device *dev = &pwiv->spidev->dev;
	stwuct adin1110_powt_pwiv *powt_pwiv;
	stwuct net_device *netdev;
	int wet;
	int i;

	fow (i = 0; i < pwiv->cfg->powts_nw; i++) {
		netdev = devm_awwoc_ethewdev(dev, sizeof(*powt_pwiv));
		if (!netdev)
			wetuwn -ENOMEM;

		powt_pwiv = netdev_pwiv(netdev);
		powt_pwiv->netdev = netdev;
		powt_pwiv->pwiv = pwiv;
		powt_pwiv->cfg = pwiv->cfg;
		powt_pwiv->nw = i;
		pwiv->powts[i] = powt_pwiv;
		SET_NETDEV_DEV(netdev, dev);

		wet = device_get_ethdev_addwess(dev, netdev);
		if (wet < 0)
			wetuwn wet;

		netdev->iwq = pwiv->spidev->iwq;
		INIT_WOWK(&powt_pwiv->tx_wowk, adin1110_tx_wowk);
		INIT_WOWK(&powt_pwiv->wx_mode_wowk, adin1110_wx_mode_wowk);
		skb_queue_head_init(&powt_pwiv->txq);

		netif_cawwiew_off(netdev);

		netdev->if_powt = IF_POWT_10BASET;
		netdev->netdev_ops = &adin1110_netdev_ops;
		netdev->ethtoow_ops = &adin1110_ethtoow_ops;
		netdev->pwiv_fwags |= IFF_UNICAST_FWT;
		netdev->featuwes |= NETIF_F_NETNS_WOCAW;

		powt_pwiv->phydev = get_phy_device(pwiv->mii_bus, i + 1, fawse);
		if (IS_EWW(powt_pwiv->phydev)) {
			netdev_eww(netdev, "Couwd not find PHY with device addwess: %d.\n", i);
			wetuwn PTW_EWW(powt_pwiv->phydev);
		}

		powt_pwiv->phydev = phy_connect(netdev,
						phydev_name(powt_pwiv->phydev),
						adin1110_adjust_wink,
						PHY_INTEWFACE_MODE_INTEWNAW);
		if (IS_EWW(powt_pwiv->phydev)) {
			netdev_eww(netdev, "Couwd not connect PHY with device addwess: %d.\n", i);
			wetuwn PTW_EWW(powt_pwiv->phydev);
		}

		wet = devm_add_action_ow_weset(dev, adin1110_disconnect_phy,
					       powt_pwiv->phydev);
		if (wet < 0)
			wetuwn wet;
	}

	/* ADIN1110 INT_N pin wiww be used to signaw the host */
	wet = devm_wequest_thweaded_iwq(dev, pwiv->spidev->iwq, NUWW,
					adin1110_iwq,
					IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
					dev_name(dev), pwiv);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < pwiv->cfg->powts_nw; i++) {
		wet = devm_wegistew_netdev(dev, pwiv->powts[i]->netdev);
		if (wet < 0) {
			dev_eww(dev, "Faiwed to wegistew netwowk device.\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int adin1110_pwobe(stwuct spi_device *spi)
{
	const stwuct spi_device_id *dev_id = spi_get_device_id(spi);
	stwuct device *dev = &spi->dev;
	stwuct adin1110_pwiv *pwiv;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(stwuct adin1110_pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->spidev = spi;
	pwiv->cfg = &adin1110_cfgs[dev_id->dwivew_data];
	spi->bits_pew_wowd = 8;
	spi->mode = SPI_MODE_0;

	mutex_init(&pwiv->wock);
	spin_wock_init(&pwiv->state_wock);

	/* use of CWC on contwow and data twansactions is pin dependent */
	pwiv->append_cwc = device_pwopewty_wead_boow(dev, "adi,spi-cwc");
	if (pwiv->append_cwc)
		cwc8_popuwate_msb(adin1110_cwc_tabwe, 0x7);

	wet = adin1110_check_spi(pwiv);
	if (wet < 0) {
		dev_eww(dev, "Pwobe SPI Wead check faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = adin1110_wwite_weg(pwiv, ADIN1110_WESET, ADIN1110_SWWESET);
	if (wet < 0)
		wetuwn wet;

	wet = adin1110_wegistew_mdiobus(pwiv, dev);
	if (wet < 0) {
		dev_eww(dev, "Couwd not wegistew MDIO bus %d\n", wet);
		wetuwn wet;
	}

	wetuwn adin1110_pwobe_netdevs(pwiv);
}

static const stwuct of_device_id adin1110_match_tabwe[] = {
	{ .compatibwe = "adi,adin1110" },
	{ .compatibwe = "adi,adin2111" },
	{ }
};
MODUWE_DEVICE_TABWE(of, adin1110_match_tabwe);

static const stwuct spi_device_id adin1110_spi_id[] = {
	{ .name = "adin1110", .dwivew_data = ADIN1110_MAC },
	{ .name = "adin2111", .dwivew_data = ADIN2111_MAC },
	{ }
};
MODUWE_DEVICE_TABWE(spi, adin1110_spi_id);

static stwuct spi_dwivew adin1110_dwivew = {
	.dwivew = {
		.name = "adin1110",
		.of_match_tabwe = adin1110_match_tabwe,
	},
	.pwobe = adin1110_pwobe,
	.id_tabwe = adin1110_spi_id,
};

static int __init adin1110_dwivew_init(void)
{
	int wet;

	wet = adin1110_setup_notifiews();
	if (wet < 0)
		wetuwn wet;

	wet = spi_wegistew_dwivew(&adin1110_dwivew);
	if (wet < 0) {
		adin1110_unwegistew_notifiews();
		wetuwn wet;
	}

	wetuwn 0;
}

static void __exit adin1110_exit(void)
{
	adin1110_unwegistew_notifiews();
	spi_unwegistew_dwivew(&adin1110_dwivew);
}
moduwe_init(adin1110_dwivew_init);
moduwe_exit(adin1110_exit);

MODUWE_DESCWIPTION("ADIN1110 Netwowk dwivew");
MODUWE_AUTHOW("Awexandwu Tachici <awexandwu.tachici@anawog.com>");
MODUWE_WICENSE("Duaw BSD/GPW");
