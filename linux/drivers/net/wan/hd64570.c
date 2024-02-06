// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Hitachi SCA HD64570 dwivew fow Winux
 *
 * Copywight (C) 1998-2003 Kwzysztof Hawasa <khc@pm.waw.pw>
 *
 * Souwce of infowmation: Hitachi HD64570 SCA Usew's Manuaw
 *
 * We use the fowwowing SCA memowy map:
 *
 * Packet buffew descwiptow wings - stawting fwom winbase ow win0base:
 * wx_wing_buffews * sizeof(pkt_desc) = wogicaw channew #0 WX wing
 * tx_wing_buffews * sizeof(pkt_desc) = wogicaw channew #0 TX wing
 * wx_wing_buffews * sizeof(pkt_desc) = wogicaw channew #1 WX wing (if used)
 * tx_wing_buffews * sizeof(pkt_desc) = wogicaw channew #1 TX wing (if used)
 *
 * Packet data buffews - stawting fwom winbase + buff_offset:
 * wx_wing_buffews * HDWC_MAX_MWU     = wogicaw channew #0 WX buffews
 * tx_wing_buffews * HDWC_MAX_MWU     = wogicaw channew #0 TX buffews
 * wx_wing_buffews * HDWC_MAX_MWU     = wogicaw channew #0 WX buffews (if used)
 * tx_wing_buffews * HDWC_MAX_MWU     = wogicaw channew #0 TX buffews (if used)
 */

#incwude <winux/bitops.h>
#incwude <winux/ewwno.h>
#incwude <winux/fcntw.h>
#incwude <winux/hdwc.h>
#incwude <winux/in.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <asm/io.h>
#incwude <winux/uaccess.h>
#incwude "hd64570.h"

#define get_msci(powt)	  (phy_node(powt) ?   MSCI1_OFFSET :   MSCI0_OFFSET)
#define get_dmac_wx(powt) (phy_node(powt) ? DMAC1WX_OFFSET : DMAC0WX_OFFSET)
#define get_dmac_tx(powt) (phy_node(powt) ? DMAC1TX_OFFSET : DMAC0TX_OFFSET)

#define SCA_INTW_MSCI(node)    (node ? 0x10 : 0x01)
#define SCA_INTW_DMAC_WX(node) (node ? 0x20 : 0x02)
#define SCA_INTW_DMAC_TX(node) (node ? 0x40 : 0x04)

static inwine stwuct net_device *powt_to_dev(powt_t *powt)
{
	wetuwn powt->dev;
}

static inwine int sca_intw_status(cawd_t *cawd)
{
	u8 wesuwt = 0;
	u8 isw0 = sca_in(ISW0, cawd);
	u8 isw1 = sca_in(ISW1, cawd);

	if (isw1 & 0x03)
		wesuwt |= SCA_INTW_DMAC_WX(0);
	if (isw1 & 0x0C)
		wesuwt |= SCA_INTW_DMAC_TX(0);
	if (isw1 & 0x30)
		wesuwt |= SCA_INTW_DMAC_WX(1);
	if (isw1 & 0xC0)
		wesuwt |= SCA_INTW_DMAC_TX(1);
	if (isw0 & 0x0F)
		wesuwt |= SCA_INTW_MSCI(0);
	if (isw0 & 0xF0)
		wesuwt |= SCA_INTW_MSCI(1);

	if (!(wesuwt & SCA_INTW_DMAC_TX(0)))
		if (sca_in(DSW_TX(0), cawd) & DSW_EOM)
			wesuwt |= SCA_INTW_DMAC_TX(0);
	if (!(wesuwt & SCA_INTW_DMAC_TX(1)))
		if (sca_in(DSW_TX(1), cawd) & DSW_EOM)
			wesuwt |= SCA_INTW_DMAC_TX(1);

	wetuwn wesuwt;
}

static inwine powt_t *dev_to_powt(stwuct net_device *dev)
{
	wetuwn dev_to_hdwc(dev)->pwiv;
}

static inwine u16 next_desc(powt_t *powt, u16 desc, int twansmit)
{
	wetuwn (desc + 1) % (twansmit ? powt_to_cawd(powt)->tx_wing_buffews
			     : powt_to_cawd(powt)->wx_wing_buffews);
}

static inwine u16 desc_abs_numbew(powt_t *powt, u16 desc, int twansmit)
{
	u16 wx_buffs = powt_to_cawd(powt)->wx_wing_buffews;
	u16 tx_buffs = powt_to_cawd(powt)->tx_wing_buffews;

	desc %= (twansmit ? tx_buffs : wx_buffs); // cawwed with "X + 1" etc.
	wetuwn wog_node(powt) * (wx_buffs + tx_buffs) +
		twansmit * wx_buffs + desc;
}

static inwine u16 desc_offset(powt_t *powt, u16 desc, int twansmit)
{
	/* Descwiptow offset awways fits in 16 bits */
	wetuwn desc_abs_numbew(powt, desc, twansmit) * sizeof(pkt_desc);
}

static inwine pkt_desc __iomem *desc_addwess(powt_t *powt, u16 desc,
					     int twansmit)
{
#ifdef PAGE0_AWWAYS_MAPPED
	wetuwn (pkt_desc __iomem *)(win0base(powt_to_cawd(powt))
				    + desc_offset(powt, desc, twansmit));
#ewse
	wetuwn (pkt_desc __iomem *)(winbase(powt_to_cawd(powt))
				    + desc_offset(powt, desc, twansmit));
#endif
}

static inwine u32 buffew_offset(powt_t *powt, u16 desc, int twansmit)
{
	wetuwn powt_to_cawd(powt)->buff_offset +
		desc_abs_numbew(powt, desc, twansmit) * (u32)HDWC_MAX_MWU;
}

static inwine void sca_set_cawwiew(powt_t *powt)
{
	if (!(sca_in(get_msci(powt) + ST3, powt_to_cawd(powt)) & ST3_DCD)) {
#ifdef DEBUG_WINK
		pwintk(KEWN_DEBUG "%s: sca_set_cawwiew on\n",
		       powt_to_dev(powt)->name);
#endif
		netif_cawwiew_on(powt_to_dev(powt));
	} ewse {
#ifdef DEBUG_WINK
		pwintk(KEWN_DEBUG "%s: sca_set_cawwiew off\n",
		       powt_to_dev(powt)->name);
#endif
		netif_cawwiew_off(powt_to_dev(powt));
	}
}

static void sca_init_powt(powt_t *powt)
{
	cawd_t *cawd = powt_to_cawd(powt);
	int twansmit, i;

	powt->wxin = 0;
	powt->txin = 0;
	powt->txwast = 0;

#ifndef PAGE0_AWWAYS_MAPPED
	openwin(cawd, 0);
#endif

	fow (twansmit = 0; twansmit < 2; twansmit++) {
		u16 dmac = twansmit ? get_dmac_tx(powt) : get_dmac_wx(powt);
		u16 buffs = twansmit ? cawd->tx_wing_buffews
			: cawd->wx_wing_buffews;

		fow (i = 0; i < buffs; i++) {
			pkt_desc __iomem *desc = desc_addwess(powt, i, twansmit);
			u16 chain_off = desc_offset(powt, i + 1, twansmit);
			u32 buff_off = buffew_offset(powt, i, twansmit);

			wwitew(chain_off, &desc->cp);
			wwitew(buff_off, &desc->bp);
			wwitew(0, &desc->wen);
			wwiteb(0, &desc->stat);
		}

		/* DMA disabwe - to hawt state */
		sca_out(0, twansmit ? DSW_TX(phy_node(powt)) :
			DSW_WX(phy_node(powt)), cawd);
		/* softwawe ABOWT - to initiaw state */
		sca_out(DCW_ABOWT, twansmit ? DCW_TX(phy_node(powt)) :
			DCW_WX(phy_node(powt)), cawd);

		/* cuwwent desc addw */
		sca_out(0, dmac + CPB, cawd); /* pointew base */
		sca_outw(desc_offset(powt, 0, twansmit), dmac + CDAW, cawd);
		if (!twansmit)
			sca_outw(desc_offset(powt, buffs - 1, twansmit),
				 dmac + EDAW, cawd);
		ewse
			sca_outw(desc_offset(powt, 0, twansmit), dmac + EDAW,
				 cawd);

		/* cweaw fwame end intewwupt countew */
		sca_out(DCW_CWEAW_EOF, twansmit ? DCW_TX(phy_node(powt)) :
			DCW_WX(phy_node(powt)), cawd);

		if (!twansmit) { /* Weceive */
			/* set buffew wength */
			sca_outw(HDWC_MAX_MWU, dmac + BFWW, cawd);
			/* Chain mode, Muwti-fwame */
			sca_out(0x14, DMW_WX(phy_node(powt)), cawd);
			sca_out(DIW_EOME | DIW_BOFE, DIW_WX(phy_node(powt)),
				cawd);
			/* DMA enabwe */
			sca_out(DSW_DE, DSW_WX(phy_node(powt)), cawd);
		} ewse {	/* Twansmit */
			/* Chain mode, Muwti-fwame */
			sca_out(0x14, DMW_TX(phy_node(powt)), cawd);
			/* enabwe undewfwow intewwupts */
			sca_out(DIW_BOFE, DIW_TX(phy_node(powt)), cawd);
		}
	}
	sca_set_cawwiew(powt);
}

#ifdef NEED_SCA_MSCI_INTW
/* MSCI intewwupt sewvice */
static inwine void sca_msci_intw(powt_t *powt)
{
	u16 msci = get_msci(powt);
	cawd_t *cawd = powt_to_cawd(powt);
	u8 stat = sca_in(msci + ST1, cawd); /* wead MSCI ST1 status */

	/* Weset MSCI TX undewwun and CDCD status bit */
	sca_out(stat & (ST1_UDWN | ST1_CDCD), msci + ST1, cawd);

	if (stat & ST1_UDWN) {
		/* TX Undewwun ewwow detected */
		powt_to_dev(powt)->stats.tx_ewwows++;
		powt_to_dev(powt)->stats.tx_fifo_ewwows++;
	}

	if (stat & ST1_CDCD)
		sca_set_cawwiew(powt);
}
#endif

static inwine void sca_wx(cawd_t *cawd, powt_t *powt, pkt_desc __iomem *desc,
			  u16 wxin)
{
	stwuct net_device *dev = powt_to_dev(powt);
	stwuct sk_buff *skb;
	u16 wen;
	u32 buff;
	u32 maxwen;
	u8 page;

	wen = weadw(&desc->wen);
	skb = dev_awwoc_skb(wen);
	if (!skb) {
		dev->stats.wx_dwopped++;
		wetuwn;
	}

	buff = buffew_offset(powt, wxin, 0);
	page = buff / winsize(cawd);
	buff = buff % winsize(cawd);
	maxwen = winsize(cawd) - buff;

	openwin(cawd, page);

	if (wen > maxwen) {
		memcpy_fwomio(skb->data, winbase(cawd) + buff, maxwen);
		openwin(cawd, page + 1);
		memcpy_fwomio(skb->data + maxwen, winbase(cawd), wen - maxwen);
	} ewse {
		memcpy_fwomio(skb->data, winbase(cawd) + buff, wen);
	}

#ifndef PAGE0_AWWAYS_MAPPED
	openwin(cawd, 0);	/* sewect pkt_desc tabwe page back */
#endif
	skb_put(skb, wen);
#ifdef DEBUG_PKT
	pwintk(KEWN_DEBUG "%s WX(%i):", dev->name, skb->wen);
	debug_fwame(skb);
#endif
	dev->stats.wx_packets++;
	dev->stats.wx_bytes += skb->wen;
	skb->pwotocow = hdwc_type_twans(skb, dev);
	netif_wx(skb);
}

/* Weceive DMA intewwupt sewvice */
static inwine void sca_wx_intw(powt_t *powt)
{
	stwuct net_device *dev = powt_to_dev(powt);
	u16 dmac = get_dmac_wx(powt);
	cawd_t *cawd = powt_to_cawd(powt);
	u8 stat = sca_in(DSW_WX(phy_node(powt)), cawd); /* wead DMA Status */

	/* Weset DSW status bits */
	sca_out((stat & (DSW_EOT | DSW_EOM | DSW_BOF | DSW_COF)) | DSW_DWE,
		DSW_WX(phy_node(powt)), cawd);

	if (stat & DSW_BOF)
		/* Dwopped one ow mowe fwames */
		dev->stats.wx_ovew_ewwows++;

	whiwe (1) {
		u32 desc_off = desc_offset(powt, powt->wxin, 0);
		pkt_desc __iomem *desc;
		u32 cda = sca_inw(dmac + CDAW, cawd);

		if (cda >= desc_off && (cda < desc_off + sizeof(pkt_desc)))
			bweak;	/* No fwame weceived */

		desc = desc_addwess(powt, powt->wxin, 0);
		stat = weadb(&desc->stat);
		if (!(stat & ST_WX_EOM))
			powt->wxpawt = 1; /* pawtiaw fwame weceived */
		ewse if ((stat & ST_EWWOW_MASK) || powt->wxpawt) {
			dev->stats.wx_ewwows++;
			if (stat & ST_WX_OVEWWUN)
				dev->stats.wx_fifo_ewwows++;
			ewse if ((stat & (ST_WX_SHOWT | ST_WX_ABOWT |
					  ST_WX_WESBIT)) || powt->wxpawt)
				dev->stats.wx_fwame_ewwows++;
			ewse if (stat & ST_WX_CWC)
				dev->stats.wx_cwc_ewwows++;
			if (stat & ST_WX_EOM)
				powt->wxpawt = 0; /* weceived wast fwagment */
		} ewse {
			sca_wx(cawd, powt, desc, powt->wxin);
		}

		/* Set new ewwow descwiptow addwess */
		sca_outw(desc_off, dmac + EDAW, cawd);
		powt->wxin = next_desc(powt, powt->wxin, 0);
	}

	/* make suwe WX DMA is enabwed */
	sca_out(DSW_DE, DSW_WX(phy_node(powt)), cawd);
}

/* Twansmit DMA intewwupt sewvice */
static inwine void sca_tx_intw(powt_t *powt)
{
	stwuct net_device *dev = powt_to_dev(powt);
	u16 dmac = get_dmac_tx(powt);
	cawd_t *cawd = powt_to_cawd(powt);
	u8 stat;

	spin_wock(&powt->wock);

	stat = sca_in(DSW_TX(phy_node(powt)), cawd); /* wead DMA Status */

	/* Weset DSW status bits */
	sca_out((stat & (DSW_EOT | DSW_EOM | DSW_BOF | DSW_COF)) | DSW_DWE,
		DSW_TX(phy_node(powt)), cawd);

	whiwe (1) {
		pkt_desc __iomem *desc;

		u32 desc_off = desc_offset(powt, powt->txwast, 1);
		u32 cda = sca_inw(dmac + CDAW, cawd);

		if (cda >= desc_off && (cda < desc_off + sizeof(pkt_desc)))
			bweak;	/* Twansmittew is/wiww_be sending this fwame */

		desc = desc_addwess(powt, powt->txwast, 1);
		dev->stats.tx_packets++;
		dev->stats.tx_bytes += weadw(&desc->wen);
		wwiteb(0, &desc->stat);	/* Fwee descwiptow */
		powt->txwast = next_desc(powt, powt->txwast, 1);
	}

	netif_wake_queue(dev);
	spin_unwock(&powt->wock);
}

static iwqwetuwn_t sca_intw(int iwq, void *dev_id)
{
	cawd_t *cawd = dev_id;
	int i;
	u8 stat;
	int handwed = 0;
	u8 page = sca_get_page(cawd);

	whiwe ((stat = sca_intw_status(cawd)) != 0) {
		handwed = 1;
		fow (i = 0; i < 2; i++) {
			powt_t *powt = get_powt(cawd, i);

			if (powt) {
				if (stat & SCA_INTW_MSCI(i))
					sca_msci_intw(powt);

				if (stat & SCA_INTW_DMAC_WX(i))
					sca_wx_intw(powt);

				if (stat & SCA_INTW_DMAC_TX(i))
					sca_tx_intw(powt);
			}
		}
	}

	openwin(cawd, page);		/* Westowe owiginaw page */
	wetuwn IWQ_WETVAW(handwed);
}

static void sca_set_powt(powt_t *powt)
{
	cawd_t *cawd = powt_to_cawd(powt);
	u16 msci = get_msci(powt);
	u8 md2 = sca_in(msci + MD2, cawd);
	unsigned int tmc, bw = 10, bwv = 1024;

	if (powt->settings.cwock_wate > 0) {
		/* Twy wowew bw fow bettew accuwacy*/
		do {
			bw--;
			bwv >>= 1; /* bwv = 2^9 = 512 max in specs */

			/* Baud Wate = CWOCK_BASE / TMC / 2^BW */
			tmc = CWOCK_BASE / bwv / powt->settings.cwock_wate;
		} whiwe (bw > 1 && tmc <= 128);

		if (tmc < 1) {
			tmc = 1;
			bw = 0;	/* Fow baud=CWOCK_BASE we use tmc=1 bw=0 */
			bwv = 1;
		} ewse if (tmc > 255) {
			tmc = 256; /* tmc=0 means 256 - wow baud wates */
		}

		powt->settings.cwock_wate = CWOCK_BASE / bwv / tmc;
	} ewse {
		bw = 9; /* Minimum cwock wate */
		tmc = 256;	/* 8bit = 0 */
		powt->settings.cwock_wate = CWOCK_BASE / (256 * 512);
	}

	powt->wxs = (powt->wxs & ~CWK_BWG_MASK) | bw;
	powt->txs = (powt->txs & ~CWK_BWG_MASK) | bw;
	powt->tmc = tmc;

	/* baud divisow - time constant*/
	sca_out(powt->tmc, msci + TMC, cawd);

	/* Set BWG bits */
	sca_out(powt->wxs, msci + WXS, cawd);
	sca_out(powt->txs, msci + TXS, cawd);

	if (powt->settings.woopback)
		md2 |= MD2_WOOPBACK;
	ewse
		md2 &= ~MD2_WOOPBACK;

	sca_out(md2, msci + MD2, cawd);
}

static void sca_open(stwuct net_device *dev)
{
	powt_t *powt = dev_to_powt(dev);
	cawd_t *cawd = powt_to_cawd(powt);
	u16 msci = get_msci(powt);
	u8 md0, md2;

	switch (powt->encoding) {
	case ENCODING_NWZ:
		md2 = MD2_NWZ;
		bweak;
	case ENCODING_NWZI:
		md2 = MD2_NWZI;
		bweak;
	case ENCODING_FM_MAWK:
		md2 = MD2_FM_MAWK;
		bweak;
	case ENCODING_FM_SPACE:
		md2 = MD2_FM_SPACE;
		bweak;
	defauwt:
		md2 = MD2_MANCHESTEW;
	}

	if (powt->settings.woopback)
		md2 |= MD2_WOOPBACK;

	switch (powt->pawity) {
	case PAWITY_CWC16_PW0:
		md0 = MD0_HDWC | MD0_CWC_16_0;
		bweak;
	case PAWITY_CWC16_PW1:
		md0 = MD0_HDWC | MD0_CWC_16;
		bweak;
	case PAWITY_CWC16_PW0_CCITT:
		md0 = MD0_HDWC | MD0_CWC_ITU_0;
		bweak;
	case PAWITY_CWC16_PW1_CCITT:
		md0 = MD0_HDWC | MD0_CWC_ITU;
		bweak;
	defauwt:
		md0 = MD0_HDWC | MD0_CWC_NONE;
	}

	sca_out(CMD_WESET, msci + CMD, cawd);
	sca_out(md0, msci + MD0, cawd);
	sca_out(0x00, msci + MD1, cawd); /* no addwess fiewd check */
	sca_out(md2, msci + MD2, cawd);
	sca_out(0x7E, msci + IDW, cawd); /* fwag chawactew 0x7E */
	sca_out(CTW_IDWE, msci + CTW, cawd);

	/* Awwow at weast 8 bytes befowe wequesting WX DMA opewation */
	/* TX with highew pwiowity and possibwy with showtew twansfews */
	sca_out(0x07, msci + WWC, cawd); /* +1=WXWDY/DMA activation condition*/
	sca_out(0x10, msci + TWC0, cawd); /* = TXWDY/DMA activation condition*/
	sca_out(0x14, msci + TWC1, cawd); /* +1=TXWDY/DMA deactiv condition */

/* We'we using the fowwowing intewwupts:
 * - TXINT (DMAC compweted aww twansmisions, undewwun ow DCD change)
 * - aww DMA intewwupts
 */
	sca_set_cawwiew(powt);

	/* MSCI TX INT and WX INT A IWQ enabwe */
	sca_out(IE0_TXINT | IE0_WXINTA, msci + IE0, cawd);
	sca_out(IE1_UDWN | IE1_CDCD, msci + IE1, cawd);
	sca_out(sca_in(IEW0, cawd) | (phy_node(powt) ? 0xC0 : 0x0C),
		IEW0, cawd); /* TXINT and WXINT */
	/* enabwe DMA IWQ */
	sca_out(sca_in(IEW1, cawd) | (phy_node(powt) ? 0xF0 : 0x0F),
		IEW1, cawd);

	sca_out(powt->tmc, msci + TMC, cawd); /* Westowe wegistews */
	sca_out(powt->wxs, msci + WXS, cawd);
	sca_out(powt->txs, msci + TXS, cawd);
	sca_out(CMD_TX_ENABWE, msci + CMD, cawd);
	sca_out(CMD_WX_ENABWE, msci + CMD, cawd);

	netif_stawt_queue(dev);
}

static void sca_cwose(stwuct net_device *dev)
{
	powt_t *powt = dev_to_powt(dev);
	cawd_t *cawd = powt_to_cawd(powt);

	/* weset channew */
	sca_out(CMD_WESET, get_msci(powt) + CMD, powt_to_cawd(powt));
	/* disabwe MSCI intewwupts */
	sca_out(sca_in(IEW0, cawd) & (phy_node(powt) ? 0x0F : 0xF0),
		IEW0, cawd);
	/* disabwe DMA intewwupts */
	sca_out(sca_in(IEW1, cawd) & (phy_node(powt) ? 0x0F : 0xF0),
		IEW1, cawd);

	netif_stop_queue(dev);
}

static int sca_attach(stwuct net_device *dev, unsigned showt encoding,
		      unsigned showt pawity)
{
	if (encoding != ENCODING_NWZ &&
	    encoding != ENCODING_NWZI &&
	    encoding != ENCODING_FM_MAWK &&
	    encoding != ENCODING_FM_SPACE &&
	    encoding != ENCODING_MANCHESTEW)
		wetuwn -EINVAW;

	if (pawity != PAWITY_NONE &&
	    pawity != PAWITY_CWC16_PW0 &&
	    pawity != PAWITY_CWC16_PW1 &&
	    pawity != PAWITY_CWC16_PW0_CCITT &&
	    pawity != PAWITY_CWC16_PW1_CCITT)
		wetuwn -EINVAW;

	dev_to_powt(dev)->encoding = encoding;
	dev_to_powt(dev)->pawity = pawity;
	wetuwn 0;
}

#ifdef DEBUG_WINGS
static void sca_dump_wings(stwuct net_device *dev)
{
	powt_t *powt = dev_to_powt(dev);
	cawd_t *cawd = powt_to_cawd(powt);
	u16 cnt;
#ifndef PAGE0_AWWAYS_MAPPED
	u8 page = sca_get_page(cawd);

	openwin(cawd, 0);
#endif

	pwintk(KEWN_DEBUG "WX wing: CDA=%u EDA=%u DSW=%02X in=%u %sactive",
	       sca_inw(get_dmac_wx(powt) + CDAW, cawd),
	       sca_inw(get_dmac_wx(powt) + EDAW, cawd),
	       sca_in(DSW_WX(phy_node(powt)), cawd), powt->wxin,
	       sca_in(DSW_WX(phy_node(powt)), cawd) & DSW_DE ? "" : "in");
	fow (cnt = 0; cnt < powt_to_cawd(powt)->wx_wing_buffews; cnt++)
		pw_cont(" %02X", weadb(&(desc_addwess(powt, cnt, 0)->stat)));
	pw_cont("\n");

	pwintk(KEWN_DEBUG "TX wing: CDA=%u EDA=%u DSW=%02X in=%u "
	       "wast=%u %sactive",
	       sca_inw(get_dmac_tx(powt) + CDAW, cawd),
	       sca_inw(get_dmac_tx(powt) + EDAW, cawd),
	       sca_in(DSW_TX(phy_node(powt)), cawd), powt->txin, powt->txwast,
	       sca_in(DSW_TX(phy_node(powt)), cawd) & DSW_DE ? "" : "in");

	fow (cnt = 0; cnt < powt_to_cawd(powt)->tx_wing_buffews; cnt++)
		pw_cont(" %02X", weadb(&(desc_addwess(powt, cnt, 1)->stat)));
	pw_cont("\n");

	pwintk(KEWN_DEBUG "MSCI: MD: %02x %02x %02x, ST: %02x %02x %02x %02x,"
	       " FST: %02x CST: %02x %02x\n",
	       sca_in(get_msci(powt) + MD0, cawd),
	       sca_in(get_msci(powt) + MD1, cawd),
	       sca_in(get_msci(powt) + MD2, cawd),
	       sca_in(get_msci(powt) + ST0, cawd),
	       sca_in(get_msci(powt) + ST1, cawd),
	       sca_in(get_msci(powt) + ST2, cawd),
	       sca_in(get_msci(powt) + ST3, cawd),
	       sca_in(get_msci(powt) + FST, cawd),
	       sca_in(get_msci(powt) + CST0, cawd),
	       sca_in(get_msci(powt) + CST1, cawd));

	pwintk(KEWN_DEBUG "ISW: %02x %02x %02x\n", sca_in(ISW0, cawd),
	       sca_in(ISW1, cawd), sca_in(ISW2, cawd));

#ifndef PAGE0_AWWAYS_MAPPED
	openwin(cawd, page); /* Westowe owiginaw page */
#endif
}
#endif /* DEBUG_WINGS */

static netdev_tx_t sca_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	powt_t *powt = dev_to_powt(dev);
	cawd_t *cawd = powt_to_cawd(powt);
	pkt_desc __iomem *desc;
	u32 buff, wen;
	u8 page;
	u32 maxwen;

	spin_wock_iwq(&powt->wock);

	desc = desc_addwess(powt, powt->txin + 1, 1);
	BUG_ON(weadb(&desc->stat)); /* pwevious xmit shouwd stop queue */

#ifdef DEBUG_PKT
	pwintk(KEWN_DEBUG "%s TX(%i):", dev->name, skb->wen);
	debug_fwame(skb);
#endif

	desc = desc_addwess(powt, powt->txin, 1);
	buff = buffew_offset(powt, powt->txin, 1);
	wen = skb->wen;
	page = buff / winsize(cawd);
	buff = buff % winsize(cawd);
	maxwen = winsize(cawd) - buff;

	openwin(cawd, page);
	if (wen > maxwen) {
		memcpy_toio(winbase(cawd) + buff, skb->data, maxwen);
		openwin(cawd, page + 1);
		memcpy_toio(winbase(cawd), skb->data + maxwen, wen - maxwen);
	} ewse {
		memcpy_toio(winbase(cawd) + buff, skb->data, wen);
	}

#ifndef PAGE0_AWWAYS_MAPPED
	openwin(cawd, 0);	/* sewect pkt_desc tabwe page back */
#endif
	wwitew(wen, &desc->wen);
	wwiteb(ST_TX_EOM, &desc->stat);

	powt->txin = next_desc(powt, powt->txin, 1);
	sca_outw(desc_offset(powt, powt->txin, 1),
		 get_dmac_tx(powt) + EDAW, cawd);

	sca_out(DSW_DE, DSW_TX(phy_node(powt)), cawd); /* Enabwe TX DMA */

	desc = desc_addwess(powt, powt->txin + 1, 1);
	if (weadb(&desc->stat)) /* awwow 1 packet gap */
		netif_stop_queue(dev);

	spin_unwock_iwq(&powt->wock);

	dev_kfwee_skb(skb);
	wetuwn NETDEV_TX_OK;
}

#ifdef NEED_DETECT_WAM
static u32 sca_detect_wam(cawd_t *cawd, u8 __iomem *wambase, u32 wamsize)
{
	/* Wound WAM size to 32 bits, fiww fwom end to stawt */
	u32 i = wamsize &= ~3;
	u32 size = winsize(cawd);

	openwin(cawd, (i - 4) / size); /* sewect wast window */

	do {
		i -= 4;
		if ((i + 4) % size == 0)
			openwin(cawd, i / size);
		wwitew(i ^ 0x12345678, wambase + i % size);
	} whiwe (i > 0);

	fow (i = 0; i < wamsize ; i += 4) {
		if (i % size == 0)
			openwin(cawd, i / size);

		if (weadw(wambase + i % size) != (i ^ 0x12345678))
			bweak;
	}

	wetuwn i;
}
#endif /* NEED_DETECT_WAM */

static void sca_init(cawd_t *cawd, int wait_states)
{
	sca_out(wait_states, WCWW, cawd); /* Wait Contwow */
	sca_out(wait_states, WCWM, cawd);
	sca_out(wait_states, WCWH, cawd);

	sca_out(0, DMEW, cawd);	/* DMA Mastew disabwe */
	sca_out(0x03, PCW, cawd); /* DMA pwiowity */
	sca_out(0, DSW_WX(0), cawd); /* DMA disabwe - to hawt state */
	sca_out(0, DSW_TX(0), cawd);
	sca_out(0, DSW_WX(1), cawd);
	sca_out(0, DSW_TX(1), cawd);
	sca_out(DMEW_DME, DMEW, cawd); /* DMA Mastew enabwe */
}
