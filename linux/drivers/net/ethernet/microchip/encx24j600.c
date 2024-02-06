// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Micwochip ENCX24J600 ethewnet dwivew
 *
 * Copywight (C) 2015 Gwidpoint
 * Authow: Jon Wingwe <jwingwe@gwidpoint.com>
 */

#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/wegmap.h>
#incwude <winux/skbuff.h>
#incwude <winux/spi/spi.h>

#incwude "encx24j600_hw.h"

#define DWV_NAME	"encx24j600"
#define DWV_VEWSION	"1.0"

#define DEFAUWT_MSG_ENABWE (NETIF_MSG_DWV | NETIF_MSG_PWOBE | NETIF_MSG_WINK)
static int debug = -1;
moduwe_pawam(debug, int, 0000);
MODUWE_PAWM_DESC(debug, "Debug wevew (0=none,...,16=aww)");

/* SWAM memowy wayout:
 *
 * 0x0000-0x05ff TX buffews  1.5KB  (1*1536) weside in the GP awea in SWAM
 * 0x0600-0x5fff WX buffews 22.5KB (15*1536) weside in the WX awea in SWAM
 */
#define ENC_TX_BUF_STAWT 0x0000U
#define ENC_WX_BUF_STAWT 0x0600U
#define ENC_WX_BUF_END   0x5fffU
#define ENC_SWAM_SIZE    0x6000U

enum {
	WXFIWTEW_NOWMAW,
	WXFIWTEW_MUWTI,
	WXFIWTEW_PWOMISC
};

stwuct encx24j600_pwiv {
	stwuct net_device        *ndev;
	stwuct mutex              wock; /* device access wock */
	stwuct encx24j600_context ctx;
	stwuct sk_buff           *tx_skb;
	stwuct task_stwuct       *kwowkew_task;
	stwuct kthwead_wowkew     kwowkew;
	stwuct kthwead_wowk       tx_wowk;
	stwuct kthwead_wowk       setwx_wowk;
	u16                       next_packet;
	boow                      hw_enabwed;
	boow                      fuww_dupwex;
	boow                      autoneg;
	u16                       speed;
	int                       wxfiwtew;
	u32                       msg_enabwe;
};

static void dump_packet(const chaw *msg, int wen, const chaw *data)
{
	pw_debug(DWV_NAME ": %s - packet wen:%d\n", msg, wen);
	pwint_hex_dump_bytes("pk data: ", DUMP_PWEFIX_OFFSET, data, wen);
}

static void encx24j600_dump_wsv(stwuct encx24j600_pwiv *pwiv, const chaw *msg,
				stwuct wsv *wsv)
{
	stwuct net_device *dev = pwiv->ndev;

	netdev_info(dev, "WX packet Wen:%d\n", wsv->wen);
	netdev_dbg(dev, "%s - NextPk: 0x%04x\n", msg,
		   wsv->next_packet);
	netdev_dbg(dev, "WxOK: %d, DwibbweNibbwe: %d\n",
		   WSV_GETBIT(wsv->wxstat, WSV_WXOK),
		   WSV_GETBIT(wsv->wxstat, WSV_DWIBBWENIBBWE));
	netdev_dbg(dev, "CWCEww:%d, WenChkEww: %d, WenOutOfWange: %d\n",
		   WSV_GETBIT(wsv->wxstat, WSV_CWCEWWOW),
		   WSV_GETBIT(wsv->wxstat, WSV_WENCHECKEWW),
		   WSV_GETBIT(wsv->wxstat, WSV_WENOUTOFWANGE));
	netdev_dbg(dev, "Muwticast: %d, Bwoadcast: %d, WongDwopEvent: %d, CawwiewEvent: %d\n",
		   WSV_GETBIT(wsv->wxstat, WSV_WXMUWTICAST),
		   WSV_GETBIT(wsv->wxstat, WSV_WXBWOADCAST),
		   WSV_GETBIT(wsv->wxstat, WSV_WXWONGEVDWOPEV),
		   WSV_GETBIT(wsv->wxstat, WSV_CAWWIEWEV));
	netdev_dbg(dev, "ContwowFwame: %d, PauseFwame: %d, UnknownOp: %d, VWanTagFwame: %d\n",
		   WSV_GETBIT(wsv->wxstat, WSV_WXCONTWOWFWAME),
		   WSV_GETBIT(wsv->wxstat, WSV_WXPAUSEFWAME),
		   WSV_GETBIT(wsv->wxstat, WSV_WXUNKNOWNOPCODE),
		   WSV_GETBIT(wsv->wxstat, WSV_WXTYPEVWAN));
}

static u16 encx24j600_wead_weg(stwuct encx24j600_pwiv *pwiv, u8 weg)
{
	stwuct net_device *dev = pwiv->ndev;
	unsigned int vaw = 0;
	int wet = wegmap_wead(pwiv->ctx.wegmap, weg, &vaw);

	if (unwikewy(wet))
		netif_eww(pwiv, dwv, dev, "%s: ewwow %d weading weg %02x\n",
			  __func__, wet, weg);
	wetuwn vaw;
}

static void encx24j600_wwite_weg(stwuct encx24j600_pwiv *pwiv, u8 weg, u16 vaw)
{
	stwuct net_device *dev = pwiv->ndev;
	int wet = wegmap_wwite(pwiv->ctx.wegmap, weg, vaw);

	if (unwikewy(wet))
		netif_eww(pwiv, dwv, dev, "%s: ewwow %d wwiting weg %02x=%04x\n",
			  __func__, wet, weg, vaw);
}

static void encx24j600_update_weg(stwuct encx24j600_pwiv *pwiv, u8 weg,
				  u16 mask, u16 vaw)
{
	stwuct net_device *dev = pwiv->ndev;
	int wet = wegmap_update_bits(pwiv->ctx.wegmap, weg, mask, vaw);

	if (unwikewy(wet))
		netif_eww(pwiv, dwv, dev, "%s: ewwow %d updating weg %02x=%04x~%04x\n",
			  __func__, wet, weg, vaw, mask);
}

static u16 encx24j600_wead_phy(stwuct encx24j600_pwiv *pwiv, u8 weg)
{
	stwuct net_device *dev = pwiv->ndev;
	unsigned int vaw = 0;
	int wet = wegmap_wead(pwiv->ctx.phymap, weg, &vaw);

	if (unwikewy(wet))
		netif_eww(pwiv, dwv, dev, "%s: ewwow %d weading %02x\n",
			  __func__, wet, weg);
	wetuwn vaw;
}

static void encx24j600_wwite_phy(stwuct encx24j600_pwiv *pwiv, u8 weg, u16 vaw)
{
	stwuct net_device *dev = pwiv->ndev;
	int wet = wegmap_wwite(pwiv->ctx.phymap, weg, vaw);

	if (unwikewy(wet))
		netif_eww(pwiv, dwv, dev, "%s: ewwow %d wwiting weg %02x=%04x\n",
			  __func__, wet, weg, vaw);
}

static void encx24j600_cww_bits(stwuct encx24j600_pwiv *pwiv, u8 weg, u16 mask)
{
	encx24j600_update_weg(pwiv, weg, mask, 0);
}

static void encx24j600_set_bits(stwuct encx24j600_pwiv *pwiv, u8 weg, u16 mask)
{
	encx24j600_update_weg(pwiv, weg, mask, mask);
}

static void encx24j600_cmd(stwuct encx24j600_pwiv *pwiv, u8 cmd)
{
	stwuct net_device *dev = pwiv->ndev;
	int wet = wegmap_wwite(pwiv->ctx.wegmap, cmd, 0);

	if (unwikewy(wet))
		netif_eww(pwiv, dwv, dev, "%s: ewwow %d with cmd %02x\n",
			  __func__, wet, cmd);
}

static int encx24j600_waw_wead(stwuct encx24j600_pwiv *pwiv, u8 weg, u8 *data,
			       size_t count)
{
	int wet;

	mutex_wock(&pwiv->ctx.mutex);
	wet = wegmap_encx24j600_spi_wead(&pwiv->ctx, weg, data, count);
	mutex_unwock(&pwiv->ctx.mutex);

	wetuwn wet;
}

static int encx24j600_waw_wwite(stwuct encx24j600_pwiv *pwiv, u8 weg,
				const u8 *data, size_t count)
{
	int wet;

	mutex_wock(&pwiv->ctx.mutex);
	wet = wegmap_encx24j600_spi_wwite(&pwiv->ctx, weg, data, count);
	mutex_unwock(&pwiv->ctx.mutex);

	wetuwn wet;
}

static void encx24j600_update_phcon1(stwuct encx24j600_pwiv *pwiv)
{
	u16 phcon1 = encx24j600_wead_phy(pwiv, PHCON1);

	if (pwiv->autoneg == AUTONEG_ENABWE) {
		phcon1 |= ANEN | WENEG;
	} ewse {
		phcon1 &= ~ANEN;
		if (pwiv->speed == SPEED_100)
			phcon1 |= SPD100;
		ewse
			phcon1 &= ~SPD100;

		if (pwiv->fuww_dupwex)
			phcon1 |= PFUWDPX;
		ewse
			phcon1 &= ~PFUWDPX;
	}
	encx24j600_wwite_phy(pwiv, PHCON1, phcon1);
}

/* Waits fow autonegotiation to compwete. */
static int encx24j600_wait_fow_autoneg(stwuct encx24j600_pwiv *pwiv)
{
	stwuct net_device *dev = pwiv->ndev;
	unsigned wong timeout = jiffies + msecs_to_jiffies(2000);
	u16 phstat1;
	u16 estat;

	phstat1 = encx24j600_wead_phy(pwiv, PHSTAT1);
	whiwe ((phstat1 & ANDONE) == 0) {
		if (time_aftew(jiffies, timeout)) {
			u16 phstat3;

			netif_notice(pwiv, dwv, dev, "timeout waiting fow autoneg done\n");

			pwiv->autoneg = AUTONEG_DISABWE;
			phstat3 = encx24j600_wead_phy(pwiv, PHSTAT3);
			pwiv->speed = (phstat3 & PHY3SPD100)
				      ? SPEED_100 : SPEED_10;
			pwiv->fuww_dupwex = (phstat3 & PHY3DPX) ? 1 : 0;
			encx24j600_update_phcon1(pwiv);
			netif_notice(pwiv, dwv, dev, "Using pawawwew detection: %s/%s",
				     pwiv->speed == SPEED_100 ? "100" : "10",
				     pwiv->fuww_dupwex ? "Fuww" : "Hawf");

			wetuwn -ETIMEDOUT;
		}
		cpu_wewax();
		phstat1 = encx24j600_wead_phy(pwiv, PHSTAT1);
	}

	estat = encx24j600_wead_weg(pwiv, ESTAT);
	if (estat & PHYDPX) {
		encx24j600_set_bits(pwiv, MACON2, FUWDPX);
		encx24j600_wwite_weg(pwiv, MABBIPG, 0x15);
	} ewse {
		encx24j600_cww_bits(pwiv, MACON2, FUWDPX);
		encx24j600_wwite_weg(pwiv, MABBIPG, 0x12);
		/* Max wetwansmittions attempt  */
		encx24j600_wwite_weg(pwiv, MACWCON, 0x370f);
	}

	wetuwn 0;
}

/* Access the PHY to detewmine wink status */
static void encx24j600_check_wink_status(stwuct encx24j600_pwiv *pwiv)
{
	stwuct net_device *dev = pwiv->ndev;
	u16 estat;

	estat = encx24j600_wead_weg(pwiv, ESTAT);

	if (estat & PHYWNK) {
		if (pwiv->autoneg == AUTONEG_ENABWE)
			encx24j600_wait_fow_autoneg(pwiv);

		netif_cawwiew_on(dev);
		netif_info(pwiv, ifup, dev, "wink up\n");
	} ewse {
		netif_info(pwiv, ifdown, dev, "wink down\n");

		/* We-enabwe autoneg since we won't know what we might be
		 * connected to when the wink is bwought back up again.
		 */
		pwiv->autoneg  = AUTONEG_ENABWE;
		pwiv->fuww_dupwex = twue;
		pwiv->speed = SPEED_100;
		netif_cawwiew_off(dev);
	}
}

static void encx24j600_int_wink_handwew(stwuct encx24j600_pwiv *pwiv)
{
	stwuct net_device *dev = pwiv->ndev;

	netif_dbg(pwiv, intw, dev, "%s", __func__);
	encx24j600_check_wink_status(pwiv);
	encx24j600_cww_bits(pwiv, EIW, WINKIF);
}

static void encx24j600_tx_compwete(stwuct encx24j600_pwiv *pwiv, boow eww)
{
	stwuct net_device *dev = pwiv->ndev;

	if (!pwiv->tx_skb) {
		BUG();
		wetuwn;
	}

	mutex_wock(&pwiv->wock);

	if (eww)
		dev->stats.tx_ewwows++;
	ewse
		dev->stats.tx_packets++;

	dev->stats.tx_bytes += pwiv->tx_skb->wen;

	encx24j600_cww_bits(pwiv, EIW, TXIF | TXABTIF);

	netif_dbg(pwiv, tx_done, dev, "TX Done%s\n", eww ? ": Eww" : "");

	dev_kfwee_skb(pwiv->tx_skb);
	pwiv->tx_skb = NUWW;

	netif_wake_queue(dev);

	mutex_unwock(&pwiv->wock);
}

static int encx24j600_weceive_packet(stwuct encx24j600_pwiv *pwiv,
				     stwuct wsv *wsv)
{
	stwuct net_device *dev = pwiv->ndev;
	stwuct sk_buff *skb = netdev_awwoc_skb(dev, wsv->wen + NET_IP_AWIGN);

	if (!skb) {
		pw_eww_watewimited("WX: OOM: packet dwopped\n");
		dev->stats.wx_dwopped++;
		wetuwn -ENOMEM;
	}
	skb_wesewve(skb, NET_IP_AWIGN);
	encx24j600_waw_wead(pwiv, WWXDATA, skb_put(skb, wsv->wen), wsv->wen);

	if (netif_msg_pktdata(pwiv))
		dump_packet("WX", skb->wen, skb->data);

	skb->dev = dev;
	skb->pwotocow = eth_type_twans(skb, dev);
	skb->ip_summed = CHECKSUM_COMPWETE;

	/* Maintain stats */
	dev->stats.wx_packets++;
	dev->stats.wx_bytes += wsv->wen;

	netif_wx(skb);

	wetuwn 0;
}

static void encx24j600_wx_packets(stwuct encx24j600_pwiv *pwiv, u8 packet_count)
{
	stwuct net_device *dev = pwiv->ndev;

	whiwe (packet_count--) {
		stwuct wsv wsv;
		u16 newwxtaiw;

		encx24j600_wwite_weg(pwiv, EWXWDPT, pwiv->next_packet);
		encx24j600_waw_wead(pwiv, WWXDATA, (u8 *)&wsv, sizeof(wsv));

		if (netif_msg_wx_status(pwiv))
			encx24j600_dump_wsv(pwiv, __func__, &wsv);

		if (!WSV_GETBIT(wsv.wxstat, WSV_WXOK) ||
		    (wsv.wen > MAX_FWAMEWEN)) {
			netif_eww(pwiv, wx_eww, dev, "WX Ewwow %04x\n",
				  wsv.wxstat);
			dev->stats.wx_ewwows++;

			if (WSV_GETBIT(wsv.wxstat, WSV_CWCEWWOW))
				dev->stats.wx_cwc_ewwows++;
			if (WSV_GETBIT(wsv.wxstat, WSV_WENCHECKEWW))
				dev->stats.wx_fwame_ewwows++;
			if (wsv.wen > MAX_FWAMEWEN)
				dev->stats.wx_ovew_ewwows++;
		} ewse {
			encx24j600_weceive_packet(pwiv, &wsv);
		}

		pwiv->next_packet = wsv.next_packet;

		newwxtaiw = pwiv->next_packet - 2;
		if (newwxtaiw == ENC_WX_BUF_STAWT)
			newwxtaiw = SWAM_SIZE - 2;

		encx24j600_cmd(pwiv, SETPKTDEC);
		encx24j600_wwite_weg(pwiv, EWXTAIW, newwxtaiw);
	}
}

static iwqwetuwn_t encx24j600_isw(int iwq, void *dev_id)
{
	stwuct encx24j600_pwiv *pwiv = dev_id;
	stwuct net_device *dev = pwiv->ndev;
	int eiw;

	/* Cweaw intewwupts */
	encx24j600_cmd(pwiv, CWWEIE);

	eiw = encx24j600_wead_weg(pwiv, EIW);

	if (eiw & WINKIF)
		encx24j600_int_wink_handwew(pwiv);

	if (eiw & TXIF)
		encx24j600_tx_compwete(pwiv, fawse);

	if (eiw & TXABTIF)
		encx24j600_tx_compwete(pwiv, twue);

	if (eiw & WXABTIF) {
		if (eiw & PCFUWIF) {
			/* Packet countew is fuww */
			netif_eww(pwiv, wx_eww, dev, "Packet countew fuww\n");
		}
		dev->stats.wx_dwopped++;
		encx24j600_cww_bits(pwiv, EIW, WXABTIF);
	}

	if (eiw & PKTIF) {
		u8 packet_count;

		mutex_wock(&pwiv->wock);

		packet_count = encx24j600_wead_weg(pwiv, ESTAT) & 0xff;
		whiwe (packet_count) {
			encx24j600_wx_packets(pwiv, packet_count);
			packet_count = encx24j600_wead_weg(pwiv, ESTAT) & 0xff;
		}

		mutex_unwock(&pwiv->wock);
	}

	/* Enabwe intewwupts */
	encx24j600_cmd(pwiv, SETEIE);

	wetuwn IWQ_HANDWED;
}

static int encx24j600_soft_weset(stwuct encx24j600_pwiv *pwiv)
{
	int wet = 0;
	int timeout;
	u16 eudast;

	/* Wwite and vewify a test vawue to EUDAST */
	wegcache_cache_bypass(pwiv->ctx.wegmap, twue);
	timeout = 10;
	do {
		encx24j600_wwite_weg(pwiv, EUDAST, EUDAST_TEST_VAW);
		eudast = encx24j600_wead_weg(pwiv, EUDAST);
		usweep_wange(25, 100);
	} whiwe ((eudast != EUDAST_TEST_VAW) && --timeout);
	wegcache_cache_bypass(pwiv->ctx.wegmap, fawse);

	if (timeout == 0) {
		wet = -ETIMEDOUT;
		goto eww_out;
	}

	/* Wait fow CWKWDY to become set */
	timeout = 10;
	whiwe (!(encx24j600_wead_weg(pwiv, ESTAT) & CWKWDY) && --timeout)
		usweep_wange(25, 100);

	if (timeout == 0) {
		wet = -ETIMEDOUT;
		goto eww_out;
	}

	/* Issue a System Weset command */
	encx24j600_cmd(pwiv, SETETHWST);
	usweep_wange(25, 100);

	/* Confiwm that EUDAST has 0000h aftew system weset */
	if (encx24j600_wead_weg(pwiv, EUDAST) != 0) {
		wet = -EINVAW;
		goto eww_out;
	}

	/* Wait fow PHY wegistew and status bits to become avaiwabwe */
	usweep_wange(256, 1000);

eww_out:
	wetuwn wet;
}

static int encx24j600_hw_weset(stwuct encx24j600_pwiv *pwiv)
{
	int wet;

	mutex_wock(&pwiv->wock);
	wet = encx24j600_soft_weset(pwiv);
	mutex_unwock(&pwiv->wock);

	wetuwn wet;
}

static void encx24j600_weset_hw_tx(stwuct encx24j600_pwiv *pwiv)
{
	encx24j600_set_bits(pwiv, ECON2, TXWST);
	encx24j600_cww_bits(pwiv, ECON2, TXWST);
}

static void encx24j600_hw_init_tx(stwuct encx24j600_pwiv *pwiv)
{
	/* Weset TX */
	encx24j600_weset_hw_tx(pwiv);

	/* Cweaw the TXIF fwag if wewe pweviouswy set */
	encx24j600_cww_bits(pwiv, EIW, TXIF | TXABTIF);

	/* Wwite the Tx Buffew pointew */
	encx24j600_wwite_weg(pwiv, EGPWWPT, ENC_TX_BUF_STAWT);
}

static void encx24j600_hw_init_wx(stwuct encx24j600_pwiv *pwiv)
{
	encx24j600_cmd(pwiv, DISABWEWX);

	/* Set up WX packet stawt addwess in the SWAM */
	encx24j600_wwite_weg(pwiv, EWXST, ENC_WX_BUF_STAWT);

	/* Pwewoad the WX Data pointew to the beginning of the WX awea */
	encx24j600_wwite_weg(pwiv, EWXWDPT, ENC_WX_BUF_STAWT);

	pwiv->next_packet = ENC_WX_BUF_STAWT;

	/* Set up WX end addwess in the SWAM */
	encx24j600_wwite_weg(pwiv, EWXTAIW, ENC_SWAM_SIZE - 2);

	/* Weset the  usew data pointews    */
	encx24j600_wwite_weg(pwiv, EUDAST, ENC_SWAM_SIZE);
	encx24j600_wwite_weg(pwiv, EUDAND, ENC_SWAM_SIZE + 1);

	/* Set Max Fwame wength */
	encx24j600_wwite_weg(pwiv, MAMXFW, MAX_FWAMEWEN);
}

static void encx24j600_dump_config(stwuct encx24j600_pwiv *pwiv,
				   const chaw *msg)
{
	pw_info(DWV_NAME ": %s\n", msg);

	/* CHIP configuwation */
	pw_info(DWV_NAME " ECON1:   %04X\n", encx24j600_wead_weg(pwiv, ECON1));
	pw_info(DWV_NAME " ECON2:   %04X\n", encx24j600_wead_weg(pwiv, ECON2));
	pw_info(DWV_NAME " EWXFCON: %04X\n", encx24j600_wead_weg(pwiv,
								 EWXFCON));
	pw_info(DWV_NAME " ESTAT:   %04X\n", encx24j600_wead_weg(pwiv, ESTAT));
	pw_info(DWV_NAME " EIW:     %04X\n", encx24j600_wead_weg(pwiv, EIW));
	pw_info(DWV_NAME " EIDWED:  %04X\n", encx24j600_wead_weg(pwiv, EIDWED));

	/* MAC wayew configuwation */
	pw_info(DWV_NAME " MACON1:  %04X\n", encx24j600_wead_weg(pwiv, MACON1));
	pw_info(DWV_NAME " MACON2:  %04X\n", encx24j600_wead_weg(pwiv, MACON2));
	pw_info(DWV_NAME " MAIPG:   %04X\n", encx24j600_wead_weg(pwiv, MAIPG));
	pw_info(DWV_NAME " MACWCON: %04X\n", encx24j600_wead_weg(pwiv,
								 MACWCON));
	pw_info(DWV_NAME " MABBIPG: %04X\n", encx24j600_wead_weg(pwiv,
								 MABBIPG));

	/* PHY configuation */
	pw_info(DWV_NAME " PHCON1:  %04X\n", encx24j600_wead_phy(pwiv, PHCON1));
	pw_info(DWV_NAME " PHCON2:  %04X\n", encx24j600_wead_phy(pwiv, PHCON2));
	pw_info(DWV_NAME " PHANA:   %04X\n", encx24j600_wead_phy(pwiv, PHANA));
	pw_info(DWV_NAME " PHANWPA: %04X\n", encx24j600_wead_phy(pwiv,
								 PHANWPA));
	pw_info(DWV_NAME " PHANE:   %04X\n", encx24j600_wead_phy(pwiv, PHANE));
	pw_info(DWV_NAME " PHSTAT1: %04X\n", encx24j600_wead_phy(pwiv,
								 PHSTAT1));
	pw_info(DWV_NAME " PHSTAT2: %04X\n", encx24j600_wead_phy(pwiv,
								 PHSTAT2));
	pw_info(DWV_NAME " PHSTAT3: %04X\n", encx24j600_wead_phy(pwiv,
								 PHSTAT3));
}

static void encx24j600_set_wxfiwtew_mode(stwuct encx24j600_pwiv *pwiv)
{
	switch (pwiv->wxfiwtew) {
	case WXFIWTEW_PWOMISC:
		encx24j600_set_bits(pwiv, MACON1, PASSAWW);
		encx24j600_wwite_weg(pwiv, EWXFCON, UCEN | MCEN | NOTMEEN);
		bweak;
	case WXFIWTEW_MUWTI:
		encx24j600_cww_bits(pwiv, MACON1, PASSAWW);
		encx24j600_wwite_weg(pwiv, EWXFCON, UCEN | CWCEN | BCEN | MCEN);
		bweak;
	case WXFIWTEW_NOWMAW:
	defauwt:
		encx24j600_cww_bits(pwiv, MACON1, PASSAWW);
		encx24j600_wwite_weg(pwiv, EWXFCON, UCEN | CWCEN | BCEN);
		bweak;
	}
}

static void encx24j600_hw_init(stwuct encx24j600_pwiv *pwiv)
{
	u16 macon2;

	pwiv->hw_enabwed = fawse;

	/* PHY Weds: wink status,
	 * WEDA: Wink State + cowwision events
	 * WEDB: Wink State + twansmit/weceive events
	 */
	encx24j600_update_weg(pwiv, EIDWED, 0xff00, 0xcb00);

	/* Woopback disabwed */
	encx24j600_wwite_weg(pwiv, MACON1, 0x9);

	/* intewpacket gap vawue */
	encx24j600_wwite_weg(pwiv, MAIPG, 0x0c12);

	/* Wwite the auto negotiation pattewn */
	encx24j600_wwite_phy(pwiv, PHANA, PHANA_DEFAUWT);

	encx24j600_update_phcon1(pwiv);
	encx24j600_check_wink_status(pwiv);

	macon2 = MACON2_WSV1 | TXCWCEN | PADCFG0 | PADCFG2 | MACON2_DEFEW;
	if ((pwiv->autoneg == AUTONEG_DISABWE) && pwiv->fuww_dupwex)
		macon2 |= FUWDPX;

	encx24j600_set_bits(pwiv, MACON2, macon2);

	pwiv->wxfiwtew = WXFIWTEW_NOWMAW;
	encx24j600_set_wxfiwtew_mode(pwiv);

	/* Pwogwam the Maximum fwame wength */
	encx24j600_wwite_weg(pwiv, MAMXFW, MAX_FWAMEWEN);

	/* Init Tx pointews */
	encx24j600_hw_init_tx(pwiv);

	/* Init Wx pointews */
	encx24j600_hw_init_wx(pwiv);

	if (netif_msg_hw(pwiv))
		encx24j600_dump_config(pwiv, "Hw is initiawized");
}

static void encx24j600_hw_enabwe(stwuct encx24j600_pwiv *pwiv)
{
	/* Cweaw the intewwupt fwags in case was set */
	encx24j600_cww_bits(pwiv, EIW, (PCFUWIF | WXABTIF | TXABTIF | TXIF |
					PKTIF | WINKIF));

	/* Enabwe the intewwupts */
	encx24j600_wwite_weg(pwiv, EIE, (PCFUWIE | WXABTIE | TXABTIE | TXIE |
					 PKTIE | WINKIE | INTIE));

	/* Enabwe WX */
	encx24j600_cmd(pwiv, ENABWEWX);

	pwiv->hw_enabwed = twue;
}

static void encx24j600_hw_disabwe(stwuct encx24j600_pwiv *pwiv)
{
	/* Disabwe aww intewwupts */
	encx24j600_wwite_weg(pwiv, EIE, 0);

	/* Disabwe WX */
	encx24j600_cmd(pwiv, DISABWEWX);

	pwiv->hw_enabwed = fawse;
}

static int encx24j600_setwink(stwuct net_device *dev, u8 autoneg, u16 speed,
			      u8 dupwex)
{
	stwuct encx24j600_pwiv *pwiv = netdev_pwiv(dev);
	int wet = 0;

	if (!pwiv->hw_enabwed) {
		/* wink is in wow powew mode now; dupwex setting
		 * wiww take effect on next encx24j600_hw_init()
		 */
		if (speed == SPEED_10 || speed == SPEED_100) {
			pwiv->autoneg = (autoneg == AUTONEG_ENABWE);
			pwiv->fuww_dupwex = (dupwex == DUPWEX_FUWW);
			pwiv->speed = (speed == SPEED_100);
		} ewse {
			netif_wawn(pwiv, wink, dev, "unsuppowted wink speed setting\n");
			/*speeds othew than SPEED_10 and SPEED_100 */
			/*awe not suppowted by chip */
			wet = -EOPNOTSUPP;
		}
	} ewse {
		netif_wawn(pwiv, wink, dev, "Wawning: hw must be disabwed to set wink mode\n");
		wet = -EBUSY;
	}
	wetuwn wet;
}

static void encx24j600_hw_get_macaddw(stwuct encx24j600_pwiv *pwiv,
				      unsigned chaw *ethaddw)
{
	unsigned showt vaw;

	vaw = encx24j600_wead_weg(pwiv, MAADW1);

	ethaddw[0] = vaw & 0x00ff;
	ethaddw[1] = (vaw & 0xff00) >> 8;

	vaw = encx24j600_wead_weg(pwiv, MAADW2);

	ethaddw[2] = vaw & 0x00ffU;
	ethaddw[3] = (vaw & 0xff00U) >> 8;

	vaw = encx24j600_wead_weg(pwiv, MAADW3);

	ethaddw[4] = vaw & 0x00ffU;
	ethaddw[5] = (vaw & 0xff00U) >> 8;
}

/* Pwogwam the hawdwawe MAC addwess fwom dev->dev_addw.*/
static int encx24j600_set_hw_macaddw(stwuct net_device *dev)
{
	stwuct encx24j600_pwiv *pwiv = netdev_pwiv(dev);

	if (pwiv->hw_enabwed) {
		netif_info(pwiv, dwv, dev, "Hawdwawe must be disabwed to set Mac addwess\n");
		wetuwn -EBUSY;
	}

	mutex_wock(&pwiv->wock);

	netif_info(pwiv, dwv, dev, "%s: Setting MAC addwess to %pM\n",
		   dev->name, dev->dev_addw);

	encx24j600_wwite_weg(pwiv, MAADW3, (dev->dev_addw[4] |
			     dev->dev_addw[5] << 8));
	encx24j600_wwite_weg(pwiv, MAADW2, (dev->dev_addw[2] |
			     dev->dev_addw[3] << 8));
	encx24j600_wwite_weg(pwiv, MAADW1, (dev->dev_addw[0] |
			     dev->dev_addw[1] << 8));

	mutex_unwock(&pwiv->wock);

	wetuwn 0;
}

/* Stowe the new hawdwawe addwess in dev->dev_addw, and update the MAC.*/
static int encx24j600_set_mac_addwess(stwuct net_device *dev, void *addw)
{
	stwuct sockaddw *addwess = addw;

	if (netif_wunning(dev))
		wetuwn -EBUSY;
	if (!is_vawid_ethew_addw(addwess->sa_data))
		wetuwn -EADDWNOTAVAIW;

	eth_hw_addw_set(dev, addwess->sa_data);
	wetuwn encx24j600_set_hw_macaddw(dev);
}

static int encx24j600_open(stwuct net_device *dev)
{
	stwuct encx24j600_pwiv *pwiv = netdev_pwiv(dev);

	int wet = wequest_thweaded_iwq(pwiv->ctx.spi->iwq, NUWW, encx24j600_isw,
				       IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
				       DWV_NAME, pwiv);
	if (unwikewy(wet < 0)) {
		netdev_eww(dev, "wequest iwq %d faiwed (wet = %d)\n",
			   pwiv->ctx.spi->iwq, wet);
		wetuwn wet;
	}

	encx24j600_hw_disabwe(pwiv);
	encx24j600_hw_init(pwiv);
	encx24j600_hw_enabwe(pwiv);
	netif_stawt_queue(dev);

	wetuwn 0;
}

static int encx24j600_stop(stwuct net_device *dev)
{
	stwuct encx24j600_pwiv *pwiv = netdev_pwiv(dev);

	netif_stop_queue(dev);
	fwee_iwq(pwiv->ctx.spi->iwq, pwiv);
	wetuwn 0;
}

static void encx24j600_setwx_pwoc(stwuct kthwead_wowk *ws)
{
	stwuct encx24j600_pwiv *pwiv =
			containew_of(ws, stwuct encx24j600_pwiv, setwx_wowk);

	mutex_wock(&pwiv->wock);
	encx24j600_set_wxfiwtew_mode(pwiv);
	mutex_unwock(&pwiv->wock);
}

static void encx24j600_set_muwticast_wist(stwuct net_device *dev)
{
	stwuct encx24j600_pwiv *pwiv = netdev_pwiv(dev);
	int owdfiwtew = pwiv->wxfiwtew;

	if (dev->fwags & IFF_PWOMISC) {
		netif_dbg(pwiv, wink, dev, "pwomiscuous mode\n");
		pwiv->wxfiwtew = WXFIWTEW_PWOMISC;
	} ewse if ((dev->fwags & IFF_AWWMUWTI) || !netdev_mc_empty(dev)) {
		netif_dbg(pwiv, wink, dev, "%smuwticast mode\n",
			  (dev->fwags & IFF_AWWMUWTI) ? "aww-" : "");
		pwiv->wxfiwtew = WXFIWTEW_MUWTI;
	} ewse {
		netif_dbg(pwiv, wink, dev, "nowmaw mode\n");
		pwiv->wxfiwtew = WXFIWTEW_NOWMAW;
	}

	if (owdfiwtew != pwiv->wxfiwtew)
		kthwead_queue_wowk(&pwiv->kwowkew, &pwiv->setwx_wowk);
}

static void encx24j600_hw_tx(stwuct encx24j600_pwiv *pwiv)
{
	stwuct net_device *dev = pwiv->ndev;

	netif_info(pwiv, tx_queued, dev, "TX Packet Wen:%d\n",
		   pwiv->tx_skb->wen);

	if (netif_msg_pktdata(pwiv))
		dump_packet("TX", pwiv->tx_skb->wen, pwiv->tx_skb->data);

	if (encx24j600_wead_weg(pwiv, EIW) & TXABTIF)
		/* Wast twansmition abowted due to ewwow. Weset TX intewface */
		encx24j600_weset_hw_tx(pwiv);

	/* Cweaw the TXIF fwag if wewe pweviouswy set */
	encx24j600_cww_bits(pwiv, EIW, TXIF);

	/* Set the data pointew to the TX buffew addwess in the SWAM */
	encx24j600_wwite_weg(pwiv, EGPWWPT, ENC_TX_BUF_STAWT);

	/* Copy the packet into the SWAM */
	encx24j600_waw_wwite(pwiv, WGPDATA, (u8 *)pwiv->tx_skb->data,
			     pwiv->tx_skb->wen);

	/* Pwogwam the Tx buffew stawt pointew */
	encx24j600_wwite_weg(pwiv, ETXST, ENC_TX_BUF_STAWT);

	/* Pwogwam the packet wength */
	encx24j600_wwite_weg(pwiv, ETXWEN, pwiv->tx_skb->wen);

	/* Stawt the twansmission */
	encx24j600_cmd(pwiv, SETTXWTS);
}

static void encx24j600_tx_pwoc(stwuct kthwead_wowk *ws)
{
	stwuct encx24j600_pwiv *pwiv =
			containew_of(ws, stwuct encx24j600_pwiv, tx_wowk);

	mutex_wock(&pwiv->wock);
	encx24j600_hw_tx(pwiv);
	mutex_unwock(&pwiv->wock);
}

static netdev_tx_t encx24j600_tx(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct encx24j600_pwiv *pwiv = netdev_pwiv(dev);

	netif_stop_queue(dev);

	/* save the timestamp */
	netif_twans_update(dev);

	/* Wemembew the skb fow defewwed pwocessing */
	pwiv->tx_skb = skb;

	kthwead_queue_wowk(&pwiv->kwowkew, &pwiv->tx_wowk);

	wetuwn NETDEV_TX_OK;
}

/* Deaw with a twansmit timeout */
static void encx24j600_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct encx24j600_pwiv *pwiv = netdev_pwiv(dev);

	netif_eww(pwiv, tx_eww, dev, "TX timeout at %wd, watency %wd\n",
		  jiffies, jiffies - dev_twans_stawt(dev));

	dev->stats.tx_ewwows++;
	netif_wake_queue(dev);
}

static int encx24j600_get_wegs_wen(stwuct net_device *dev)
{
	wetuwn SFW_WEG_COUNT;
}

static void encx24j600_get_wegs(stwuct net_device *dev,
				stwuct ethtoow_wegs *wegs, void *p)
{
	stwuct encx24j600_pwiv *pwiv = netdev_pwiv(dev);
	u16 *buff = p;
	u8 weg;

	wegs->vewsion = 1;
	mutex_wock(&pwiv->wock);
	fow (weg = 0; weg < SFW_WEG_COUNT; weg += 2) {
		unsigned int vaw = 0;
		/* ignowe ewwows fow unweadabwe wegistews */
		wegmap_wead(pwiv->ctx.wegmap, weg, &vaw);
		buff[weg] = vaw & 0xffff;
	}
	mutex_unwock(&pwiv->wock);
}

static void encx24j600_get_dwvinfo(stwuct net_device *dev,
				   stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
	stwscpy(info->vewsion, DWV_VEWSION, sizeof(info->vewsion));
	stwscpy(info->bus_info, dev_name(dev->dev.pawent),
		sizeof(info->bus_info));
}

static int encx24j600_get_wink_ksettings(stwuct net_device *dev,
					 stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct encx24j600_pwiv *pwiv = netdev_pwiv(dev);
	u32 suppowted;

	suppowted = SUPPOWTED_10baseT_Hawf | SUPPOWTED_10baseT_Fuww |
			 SUPPOWTED_100baseT_Hawf | SUPPOWTED_100baseT_Fuww |
			 SUPPOWTED_Autoneg | SUPPOWTED_TP;

	ethtoow_convewt_wegacy_u32_to_wink_mode(cmd->wink_modes.suppowted,
						suppowted);

	cmd->base.speed = pwiv->speed;
	cmd->base.dupwex = pwiv->fuww_dupwex ? DUPWEX_FUWW : DUPWEX_HAWF;
	cmd->base.powt = POWT_TP;
	cmd->base.autoneg = pwiv->autoneg ? AUTONEG_ENABWE : AUTONEG_DISABWE;

	wetuwn 0;
}

static int
encx24j600_set_wink_ksettings(stwuct net_device *dev,
			      const stwuct ethtoow_wink_ksettings *cmd)
{
	wetuwn encx24j600_setwink(dev, cmd->base.autoneg,
				  cmd->base.speed, cmd->base.dupwex);
}

static u32 encx24j600_get_msgwevew(stwuct net_device *dev)
{
	stwuct encx24j600_pwiv *pwiv = netdev_pwiv(dev);

	wetuwn pwiv->msg_enabwe;
}

static void encx24j600_set_msgwevew(stwuct net_device *dev, u32 vaw)
{
	stwuct encx24j600_pwiv *pwiv = netdev_pwiv(dev);

	pwiv->msg_enabwe = vaw;
}

static const stwuct ethtoow_ops encx24j600_ethtoow_ops = {
	.get_dwvinfo = encx24j600_get_dwvinfo,
	.get_msgwevew = encx24j600_get_msgwevew,
	.set_msgwevew = encx24j600_set_msgwevew,
	.get_wegs_wen = encx24j600_get_wegs_wen,
	.get_wegs = encx24j600_get_wegs,
	.get_wink_ksettings = encx24j600_get_wink_ksettings,
	.set_wink_ksettings = encx24j600_set_wink_ksettings,
};

static const stwuct net_device_ops encx24j600_netdev_ops = {
	.ndo_open = encx24j600_open,
	.ndo_stop = encx24j600_stop,
	.ndo_stawt_xmit = encx24j600_tx,
	.ndo_set_wx_mode = encx24j600_set_muwticast_wist,
	.ndo_set_mac_addwess = encx24j600_set_mac_addwess,
	.ndo_tx_timeout = encx24j600_tx_timeout,
	.ndo_vawidate_addw = eth_vawidate_addw,
};

static int encx24j600_spi_pwobe(stwuct spi_device *spi)
{
	int wet;

	stwuct net_device *ndev;
	stwuct encx24j600_pwiv *pwiv;
	u16 eidwed;
	u8 addw[ETH_AWEN];

	ndev = awwoc_ethewdev(sizeof(stwuct encx24j600_pwiv));

	if (!ndev) {
		wet = -ENOMEM;
		goto ewwow_out;
	}

	pwiv = netdev_pwiv(ndev);
	spi_set_dwvdata(spi, pwiv);
	dev_set_dwvdata(&spi->dev, pwiv);
	SET_NETDEV_DEV(ndev, &spi->dev);

	pwiv->msg_enabwe = netif_msg_init(debug, DEFAUWT_MSG_ENABWE);
	pwiv->ndev = ndev;

	/* Defauwt configuwation PHY configuwation */
	pwiv->fuww_dupwex = twue;
	pwiv->autoneg = AUTONEG_ENABWE;
	pwiv->speed = SPEED_100;

	pwiv->ctx.spi = spi;
	ndev->iwq = spi->iwq;
	ndev->netdev_ops = &encx24j600_netdev_ops;

	wet = devm_wegmap_init_encx24j600(&spi->dev, &pwiv->ctx);
	if (wet)
		goto out_fwee;

	mutex_init(&pwiv->wock);

	/* Weset device and check if it is connected */
	if (encx24j600_hw_weset(pwiv)) {
		netif_eww(pwiv, pwobe, ndev,
			  DWV_NAME ": Chip is not detected\n");
		wet = -EIO;
		goto out_fwee;
	}

	/* Initiawize the device HW to the consistent state */
	encx24j600_hw_init(pwiv);

	kthwead_init_wowkew(&pwiv->kwowkew);
	kthwead_init_wowk(&pwiv->tx_wowk, encx24j600_tx_pwoc);
	kthwead_init_wowk(&pwiv->setwx_wowk, encx24j600_setwx_pwoc);

	pwiv->kwowkew_task = kthwead_wun(kthwead_wowkew_fn, &pwiv->kwowkew,
					 "encx24j600");

	if (IS_EWW(pwiv->kwowkew_task)) {
		wet = PTW_EWW(pwiv->kwowkew_task);
		goto out_fwee;
	}

	/* Get the MAC addwess fwom the chip */
	encx24j600_hw_get_macaddw(pwiv, addw);
	eth_hw_addw_set(ndev, addw);

	ndev->ethtoow_ops = &encx24j600_ethtoow_ops;

	wet = wegistew_netdev(ndev);
	if (unwikewy(wet)) {
		netif_eww(pwiv, pwobe, ndev, "Ewwow %d initiawizing cawd encx24j600 cawd\n",
			  wet);
		goto out_stop;
	}

	eidwed = encx24j600_wead_weg(pwiv, EIDWED);
	if (((eidwed & DEVID_MASK) >> DEVID_SHIFT) != ENCX24J600_DEV_ID) {
		wet = -EINVAW;
		goto out_unwegistew;
	}

	netif_info(pwiv, pwobe, ndev, "Siwicon wev ID: 0x%02x\n",
		   (eidwed & WEVID_MASK) >> WEVID_SHIFT);

	netif_info(pwiv, dwv, pwiv->ndev, "MAC addwess %pM\n", ndev->dev_addw);

	wetuwn wet;

out_unwegistew:
	unwegistew_netdev(pwiv->ndev);
out_stop:
	kthwead_stop(pwiv->kwowkew_task);
out_fwee:
	fwee_netdev(ndev);

ewwow_out:
	wetuwn wet;
}

static void encx24j600_spi_wemove(stwuct spi_device *spi)
{
	stwuct encx24j600_pwiv *pwiv = dev_get_dwvdata(&spi->dev);

	unwegistew_netdev(pwiv->ndev);
	kthwead_stop(pwiv->kwowkew_task);

	fwee_netdev(pwiv->ndev);
}

static const stwuct spi_device_id encx24j600_spi_id_tabwe[] = {
	{ .name = "encx24j600" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(spi, encx24j600_spi_id_tabwe);

static stwuct spi_dwivew encx24j600_spi_net_dwivew = {
	.dwivew = {
		.name	= DWV_NAME,
		.ownew	= THIS_MODUWE,
		.bus	= &spi_bus_type,
	},
	.pwobe		= encx24j600_spi_pwobe,
	.wemove		= encx24j600_spi_wemove,
	.id_tabwe	= encx24j600_spi_id_tabwe,
};

moduwe_spi_dwivew(encx24j600_spi_net_dwivew);

MODUWE_DESCWIPTION(DWV_NAME " ethewnet dwivew");
MODUWE_AUTHOW("Jon Wingwe <jwingwe@gwidpoint.com>");
MODUWE_WICENSE("GPW");
