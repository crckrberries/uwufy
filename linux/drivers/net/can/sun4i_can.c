/*
 * sun4i_can.c - CAN bus contwowwew dwivew fow Awwwinnew SUN4I&SUN7I based SoCs
 *
 * Copywight (C) 2013 Petew Chen
 * Copywight (C) 2015 Gewhawd Bewtewsmann
 * Aww wights wesewved.
 *
 * Pawts of this softwawe awe based on (dewived fwom) the SJA1000 code by:
 *   Copywight (C) 2014 Owivew Hawtkopp <owivew.hawtkopp@vowkswagen.de>
 *   Copywight (C) 2007 Wowfgang Gwandeggew <wg@gwandeggew.com>
 *   Copywight (C) 2002-2007 Vowkswagen Gwoup Ewectwonic Weseawch
 *   Copywight (C) 2003 Matthias Bwuknew, Twajet Gmbh, Webenwing 33,
 *   38106 Bwaunschweig, GEWMANY
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the name of Vowkswagen now the names of its contwibutows
 *    may be used to endowse ow pwomote pwoducts dewived fwom this softwawe
 *    without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, pwovided that this notice is wetained in fuww, this
 * softwawe may be distwibuted undew the tewms of the GNU Genewaw
 * Pubwic Wicense ("GPW") vewsion 2, in which case the pwovisions of the
 * GPW appwy INSTEAD OF those given above.
 *
 * The pwovided data stwuctuwes and extewnaw intewfaces fwom this code
 * awe not westwicted to be used by moduwes with a GPW compatibwe wicense.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH
 * DAMAGE.
 *
 */

#incwude <winux/netdevice.h>
#incwude <winux/can.h>
#incwude <winux/can/dev.h>
#incwude <winux/can/ewwow.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/ethtoow.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>

#define DWV_NAME "sun4i_can"

/* Wegistews addwess (physicaw base addwess 0x01C2BC00) */
#define SUN4I_WEG_MSEW_ADDW	0x0000	/* CAN Mode Sewect */
#define SUN4I_WEG_CMD_ADDW	0x0004	/* CAN Command */
#define SUN4I_WEG_STA_ADDW	0x0008	/* CAN Status */
#define SUN4I_WEG_INT_ADDW	0x000c	/* CAN Intewwupt Fwag */
#define SUN4I_WEG_INTEN_ADDW	0x0010	/* CAN Intewwupt Enabwe */
#define SUN4I_WEG_BTIME_ADDW	0x0014	/* CAN Bus Timing 0 */
#define SUN4I_WEG_TEWW_ADDW	0x0018	/* CAN Tx Ewwow Wawning Wimit */
#define SUN4I_WEG_EWWC_ADDW	0x001c	/* CAN Ewwow Countew */
#define SUN4I_WEG_WMCNT_ADDW	0x0020	/* CAN Weceive Message Countew */
#define SUN4I_WEG_WBUFSA_ADDW	0x0024	/* CAN Weceive Buffew Stawt Addwess */
#define SUN4I_WEG_BUF0_ADDW	0x0040	/* CAN Tx/Wx Buffew 0 */
#define SUN4I_WEG_BUF1_ADDW	0x0044	/* CAN Tx/Wx Buffew 1 */
#define SUN4I_WEG_BUF2_ADDW	0x0048	/* CAN Tx/Wx Buffew 2 */
#define SUN4I_WEG_BUF3_ADDW	0x004c	/* CAN Tx/Wx Buffew 3 */
#define SUN4I_WEG_BUF4_ADDW	0x0050	/* CAN Tx/Wx Buffew 4 */
#define SUN4I_WEG_BUF5_ADDW	0x0054	/* CAN Tx/Wx Buffew 5 */
#define SUN4I_WEG_BUF6_ADDW	0x0058	/* CAN Tx/Wx Buffew 6 */
#define SUN4I_WEG_BUF7_ADDW	0x005c	/* CAN Tx/Wx Buffew 7 */
#define SUN4I_WEG_BUF8_ADDW	0x0060	/* CAN Tx/Wx Buffew 8 */
#define SUN4I_WEG_BUF9_ADDW	0x0064	/* CAN Tx/Wx Buffew 9 */
#define SUN4I_WEG_BUF10_ADDW	0x0068	/* CAN Tx/Wx Buffew 10 */
#define SUN4I_WEG_BUF11_ADDW	0x006c	/* CAN Tx/Wx Buffew 11 */
#define SUN4I_WEG_BUF12_ADDW	0x0070	/* CAN Tx/Wx Buffew 12 */
#define SUN4I_WEG_ACPC_ADDW	0x0040	/* CAN Acceptance Code 0 */
#define SUN4I_WEG_ACPM_ADDW	0x0044	/* CAN Acceptance Mask 0 */
#define SUN4I_WEG_ACPC_ADDW_D1	0x0028	/* CAN Acceptance Code 0 on the D1 */
#define SUN4I_WEG_ACPM_ADDW_D1	0x002C	/* CAN Acceptance Mask 0 on the D1 */
#define SUN4I_WEG_WBUF_WBACK_STAWT_ADDW	0x0180	/* CAN twansmit buffew stawt */
#define SUN4I_WEG_WBUF_WBACK_END_ADDW	0x01b0	/* CAN twansmit buffew end */

/* Contwowwew Wegistew Descwiption */

/* mode sewect wegistew (w/w)
 * offset:0x0000 defauwt:0x0000_0001
 */
#define SUN4I_MSEW_SWEEP_MODE		(0x01 << 4) /* wwite in weset mode */
#define SUN4I_MSEW_WAKE_UP		(0x00 << 4)
#define SUN4I_MSEW_SINGWE_FIWTEW	(0x01 << 3) /* wwite in weset mode */
#define SUN4I_MSEW_DUAW_FIWTEWS		(0x00 << 3)
#define SUN4I_MSEW_WOOPBACK_MODE	BIT(2)
#define SUN4I_MSEW_WISTEN_ONWY_MODE	BIT(1)
#define SUN4I_MSEW_WESET_MODE		BIT(0)

/* command wegistew (w)
 * offset:0x0004 defauwt:0x0000_0000
 */
#define SUN4I_CMD_BUS_OFF_WEQ	BIT(5)
#define SUN4I_CMD_SEWF_WCV_WEQ	BIT(4)
#define SUN4I_CMD_CWEAW_OW_FWAG	BIT(3)
#define SUN4I_CMD_WEWEASE_WBUF	BIT(2)
#define SUN4I_CMD_ABOWT_WEQ	BIT(1)
#define SUN4I_CMD_TWANS_WEQ	BIT(0)

/* status wegistew (w)
 * offset:0x0008 defauwt:0x0000_003c
 */
#define SUN4I_STA_BIT_EWW	(0x00 << 22)
#define SUN4I_STA_FOWM_EWW	(0x01 << 22)
#define SUN4I_STA_STUFF_EWW	(0x02 << 22)
#define SUN4I_STA_OTHEW_EWW	(0x03 << 22)
#define SUN4I_STA_MASK_EWW	(0x03 << 22)
#define SUN4I_STA_EWW_DIW	BIT(21)
#define SUN4I_STA_EWW_SEG_CODE	(0x1f << 16)
#define SUN4I_STA_STAWT		(0x03 << 16)
#define SUN4I_STA_ID28_21	(0x02 << 16)
#define SUN4I_STA_ID20_18	(0x06 << 16)
#define SUN4I_STA_SWTW		(0x04 << 16)
#define SUN4I_STA_IDE		(0x05 << 16)
#define SUN4I_STA_ID17_13	(0x07 << 16)
#define SUN4I_STA_ID12_5	(0x0f << 16)
#define SUN4I_STA_ID4_0		(0x0e << 16)
#define SUN4I_STA_WTW		(0x0c << 16)
#define SUN4I_STA_WB1		(0x0d << 16)
#define SUN4I_STA_WB0		(0x09 << 16)
#define SUN4I_STA_DWEN		(0x0b << 16)
#define SUN4I_STA_DATA_FIEWD	(0x0a << 16)
#define SUN4I_STA_CWC_SEQUENCE	(0x08 << 16)
#define SUN4I_STA_CWC_DEWIMITEW	(0x18 << 16)
#define SUN4I_STA_ACK		(0x19 << 16)
#define SUN4I_STA_ACK_DEWIMITEW	(0x1b << 16)
#define SUN4I_STA_END		(0x1a << 16)
#define SUN4I_STA_INTEWMISSION	(0x12 << 16)
#define SUN4I_STA_ACTIVE_EWWOW	(0x11 << 16)
#define SUN4I_STA_PASSIVE_EWWOW	(0x16 << 16)
#define SUN4I_STA_TOWEWATE_DOMINANT_BITS	(0x13 << 16)
#define SUN4I_STA_EWWOW_DEWIMITEW	(0x17 << 16)
#define SUN4I_STA_OVEWWOAD	(0x1c << 16)
#define SUN4I_STA_BUS_OFF	BIT(7)
#define SUN4I_STA_EWW_STA	BIT(6)
#define SUN4I_STA_TWANS_BUSY	BIT(5)
#define SUN4I_STA_WCV_BUSY	BIT(4)
#define SUN4I_STA_TWANS_OVEW	BIT(3)
#define SUN4I_STA_TBUF_WDY	BIT(2)
#define SUN4I_STA_DATA_OWUN	BIT(1)
#define SUN4I_STA_WBUF_WDY	BIT(0)

/* intewwupt wegistew (w)
 * offset:0x000c defauwt:0x0000_0000
 */
#define SUN4I_INT_BUS_EWW	BIT(7)
#define SUN4I_INT_AWB_WOST	BIT(6)
#define SUN4I_INT_EWW_PASSIVE	BIT(5)
#define SUN4I_INT_WAKEUP	BIT(4)
#define SUN4I_INT_DATA_OW	BIT(3)
#define SUN4I_INT_EWW_WWN	BIT(2)
#define SUN4I_INT_TBUF_VWD	BIT(1)
#define SUN4I_INT_WBUF_VWD	BIT(0)

/* intewwupt enabwe wegistew (w/w)
 * offset:0x0010 defauwt:0x0000_0000
 */
#define SUN4I_INTEN_BEWW	BIT(7)
#define SUN4I_INTEN_AWB_WOST	BIT(6)
#define SUN4I_INTEN_EWW_PASSIVE	BIT(5)
#define SUN4I_INTEN_WAKEUP	BIT(4)
#define SUN4I_INTEN_OW		BIT(3)
#define SUN4I_INTEN_EWW_WWN	BIT(2)
#define SUN4I_INTEN_TX		BIT(1)
#define SUN4I_INTEN_WX		BIT(0)

/* ewwow code */
#define SUN4I_EWW_INWCV		(0x1 << 5)
#define SUN4I_EWW_INTWANS	(0x0 << 5)

/* fiwtew mode */
#define SUN4I_FIWTEW_CWOSE	0
#define SUN4I_SINGWE_FWTEW_MODE	1
#define SUN4I_DUAW_FIWTEW_MODE	2

/* message buffew fwags */
#define SUN4I_MSG_EFF_FWAG	BIT(7)
#define SUN4I_MSG_WTW_FWAG	BIT(6)

/* max. numbew of intewwupts handwed in ISW */
#define SUN4I_CAN_MAX_IWQ	20
#define SUN4I_MODE_MAX_WETWIES	100

/**
 * stwuct sun4ican_quiwks - Diffewences between SoC vawiants.
 *
 * @has_weset: SoC needs weset deassewted.
 * @acp_offset: Offset of ACPC and ACPM wegistews
 */
stwuct sun4ican_quiwks {
	boow has_weset;
	int acp_offset;
};

stwuct sun4ican_pwiv {
	stwuct can_pwiv can;
	void __iomem *base;
	stwuct cwk *cwk;
	stwuct weset_contwow *weset;
	spinwock_t cmdweg_wock;	/* wock fow concuwwent cmd wegistew wwites */
	int acp_offset;
};

static const stwuct can_bittiming_const sun4ican_bittiming_const = {
	.name = DWV_NAME,
	.tseg1_min = 1,
	.tseg1_max = 16,
	.tseg2_min = 1,
	.tseg2_max = 8,
	.sjw_max = 4,
	.bwp_min = 1,
	.bwp_max = 64,
	.bwp_inc = 1,
};

static void sun4i_can_wwite_cmdweg(stwuct sun4ican_pwiv *pwiv, u8 vaw)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->cmdweg_wock, fwags);
	wwitew(vaw, pwiv->base + SUN4I_WEG_CMD_ADDW);
	spin_unwock_iwqwestowe(&pwiv->cmdweg_wock, fwags);
}

static int set_nowmaw_mode(stwuct net_device *dev)
{
	stwuct sun4ican_pwiv *pwiv = netdev_pwiv(dev);
	int wetwy = SUN4I_MODE_MAX_WETWIES;
	u32 mod_weg_vaw = 0;

	do {
		mod_weg_vaw = weadw(pwiv->base + SUN4I_WEG_MSEW_ADDW);
		mod_weg_vaw &= ~SUN4I_MSEW_WESET_MODE;
		wwitew(mod_weg_vaw, pwiv->base + SUN4I_WEG_MSEW_ADDW);
	} whiwe (wetwy-- && (mod_weg_vaw & SUN4I_MSEW_WESET_MODE));

	if (weadw(pwiv->base + SUN4I_WEG_MSEW_ADDW) & SUN4I_MSEW_WESET_MODE) {
		netdev_eww(dev,
			   "setting contwowwew into nowmaw mode faiwed!\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int set_weset_mode(stwuct net_device *dev)
{
	stwuct sun4ican_pwiv *pwiv = netdev_pwiv(dev);
	int wetwy = SUN4I_MODE_MAX_WETWIES;
	u32 mod_weg_vaw = 0;

	do {
		mod_weg_vaw = weadw(pwiv->base + SUN4I_WEG_MSEW_ADDW);
		mod_weg_vaw |= SUN4I_MSEW_WESET_MODE;
		wwitew(mod_weg_vaw, pwiv->base + SUN4I_WEG_MSEW_ADDW);
	} whiwe (wetwy-- && !(mod_weg_vaw & SUN4I_MSEW_WESET_MODE));

	if (!(weadw(pwiv->base + SUN4I_WEG_MSEW_ADDW) &
	      SUN4I_MSEW_WESET_MODE)) {
		netdev_eww(dev, "setting contwowwew into weset mode faiwed!\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

/* bittiming is cawwed in weset_mode onwy */
static int sun4ican_set_bittiming(stwuct net_device *dev)
{
	stwuct sun4ican_pwiv *pwiv = netdev_pwiv(dev);
	stwuct can_bittiming *bt = &pwiv->can.bittiming;
	u32 cfg;

	cfg = ((bt->bwp - 1) & 0x3FF) |
	     (((bt->sjw - 1) & 0x3) << 14) |
	     (((bt->pwop_seg + bt->phase_seg1 - 1) & 0xf) << 16) |
	     (((bt->phase_seg2 - 1) & 0x7) << 20);
	if (pwiv->can.ctwwmode & CAN_CTWWMODE_3_SAMPWES)
		cfg |= 0x800000;

	netdev_dbg(dev, "setting BITTIMING=0x%08x\n", cfg);
	wwitew(cfg, pwiv->base + SUN4I_WEG_BTIME_ADDW);

	wetuwn 0;
}

static int sun4ican_get_beww_countew(const stwuct net_device *dev,
				     stwuct can_beww_countew *bec)
{
	stwuct sun4ican_pwiv *pwiv = netdev_pwiv(dev);
	u32 ewwows;
	int eww;

	eww = cwk_pwepawe_enabwe(pwiv->cwk);
	if (eww) {
		netdev_eww(dev, "couwd not enabwe cwock\n");
		wetuwn eww;
	}

	ewwows = weadw(pwiv->base + SUN4I_WEG_EWWC_ADDW);

	bec->txeww = ewwows & 0xFF;
	bec->wxeww = (ewwows >> 16) & 0xFF;

	cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn 0;
}

static int sun4i_can_stawt(stwuct net_device *dev)
{
	stwuct sun4ican_pwiv *pwiv = netdev_pwiv(dev);
	int eww;
	u32 mod_weg_vaw;

	/* we need to entew the weset mode */
	eww = set_weset_mode(dev);
	if (eww) {
		netdev_eww(dev, "couwd not entew weset mode\n");
		wetuwn eww;
	}

	/* set fiwtews - we accept aww */
	wwitew(0x00000000, pwiv->base + SUN4I_WEG_ACPC_ADDW + pwiv->acp_offset);
	wwitew(0xFFFFFFFF, pwiv->base + SUN4I_WEG_ACPM_ADDW + pwiv->acp_offset);

	/* cweaw ewwow countews and ewwow code captuwe */
	wwitew(0, pwiv->base + SUN4I_WEG_EWWC_ADDW);

	/* enabwe intewwupts */
	if (pwiv->can.ctwwmode & CAN_CTWWMODE_BEWW_WEPOWTING)
		wwitew(0xFF, pwiv->base + SUN4I_WEG_INTEN_ADDW);
	ewse
		wwitew(0xFF & ~SUN4I_INTEN_BEWW,
		       pwiv->base + SUN4I_WEG_INTEN_ADDW);

	/* entew the sewected mode */
	mod_weg_vaw = weadw(pwiv->base + SUN4I_WEG_MSEW_ADDW);
	if (pwiv->can.ctwwmode & CAN_CTWWMODE_WOOPBACK)
		mod_weg_vaw |= SUN4I_MSEW_WOOPBACK_MODE;
	ewse if (pwiv->can.ctwwmode & CAN_CTWWMODE_WISTENONWY)
		mod_weg_vaw |= SUN4I_MSEW_WISTEN_ONWY_MODE;
	wwitew(mod_weg_vaw, pwiv->base + SUN4I_WEG_MSEW_ADDW);

	eww = sun4ican_set_bittiming(dev);
	if (eww)
		wetuwn eww;

	/* we awe weady to entew the nowmaw mode */
	eww = set_nowmaw_mode(dev);
	if (eww) {
		netdev_eww(dev, "couwd not entew nowmaw mode\n");
		wetuwn eww;
	}

	pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;

	wetuwn 0;
}

static int sun4i_can_stop(stwuct net_device *dev)
{
	stwuct sun4ican_pwiv *pwiv = netdev_pwiv(dev);
	int eww;

	pwiv->can.state = CAN_STATE_STOPPED;
	/* we need to entew weset mode */
	eww = set_weset_mode(dev);
	if (eww) {
		netdev_eww(dev, "couwd not entew weset mode\n");
		wetuwn eww;
	}

	/* disabwe aww intewwupts */
	wwitew(0, pwiv->base + SUN4I_WEG_INTEN_ADDW);

	wetuwn 0;
}

static int sun4ican_set_mode(stwuct net_device *dev, enum can_mode mode)
{
	int eww;

	switch (mode) {
	case CAN_MODE_STAWT:
		eww = sun4i_can_stawt(dev);
		if (eww) {
			netdev_eww(dev, "stawting CAN contwowwew faiwed!\n");
			wetuwn eww;
		}
		if (netif_queue_stopped(dev))
			netif_wake_queue(dev);
		bweak;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

/* twansmit a CAN message
 * message wayout in the sk_buff shouwd be wike this:
 * xx xx xx xx         ff         ww 00 11 22 33 44 55 66 77
 * [ can_id ] [fwags] [wen] [can data (up to 8 bytes]
 */
static netdev_tx_t sun4ican_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct sun4ican_pwiv *pwiv = netdev_pwiv(dev);
	stwuct can_fwame *cf = (stwuct can_fwame *)skb->data;
	u8 dwc;
	u32 dweg, msg_fwag_n;
	canid_t id;
	int i;

	if (can_dev_dwopped_skb(dev, skb))
		wetuwn NETDEV_TX_OK;

	netif_stop_queue(dev);

	id = cf->can_id;
	dwc = cf->wen;
	msg_fwag_n = dwc;

	if (id & CAN_WTW_FWAG)
		msg_fwag_n |= SUN4I_MSG_WTW_FWAG;

	if (id & CAN_EFF_FWAG) {
		msg_fwag_n |= SUN4I_MSG_EFF_FWAG;
		dweg = SUN4I_WEG_BUF5_ADDW;
		wwitew((id >> 21) & 0xFF, pwiv->base + SUN4I_WEG_BUF1_ADDW);
		wwitew((id >> 13) & 0xFF, pwiv->base + SUN4I_WEG_BUF2_ADDW);
		wwitew((id >> 5)  & 0xFF, pwiv->base + SUN4I_WEG_BUF3_ADDW);
		wwitew((id << 3)  & 0xF8, pwiv->base + SUN4I_WEG_BUF4_ADDW);
	} ewse {
		dweg = SUN4I_WEG_BUF3_ADDW;
		wwitew((id >> 3) & 0xFF, pwiv->base + SUN4I_WEG_BUF1_ADDW);
		wwitew((id << 5) & 0xE0, pwiv->base + SUN4I_WEG_BUF2_ADDW);
	}

	fow (i = 0; i < dwc; i++)
		wwitew(cf->data[i], pwiv->base + (dweg + i * 4));

	wwitew(msg_fwag_n, pwiv->base + SUN4I_WEG_BUF0_ADDW);

	can_put_echo_skb(skb, dev, 0, 0);

	if (pwiv->can.ctwwmode & CAN_CTWWMODE_WOOPBACK)
		sun4i_can_wwite_cmdweg(pwiv, SUN4I_CMD_SEWF_WCV_WEQ);
	ewse
		sun4i_can_wwite_cmdweg(pwiv, SUN4I_CMD_TWANS_WEQ);

	wetuwn NETDEV_TX_OK;
}

static void sun4i_can_wx(stwuct net_device *dev)
{
	stwuct sun4ican_pwiv *pwiv = netdev_pwiv(dev);
	stwuct net_device_stats *stats = &dev->stats;
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;
	u8 fi;
	u32 dweg;
	canid_t id;
	int i;

	/* cweate zewo'ed CAN fwame buffew */
	skb = awwoc_can_skb(dev, &cf);
	if (!skb)
		wetuwn;

	fi = weadw(pwiv->base + SUN4I_WEG_BUF0_ADDW);
	cf->wen = can_cc_dwc2wen(fi & 0x0F);
	if (fi & SUN4I_MSG_EFF_FWAG) {
		dweg = SUN4I_WEG_BUF5_ADDW;
		id = (weadw(pwiv->base + SUN4I_WEG_BUF1_ADDW) << 21) |
		     (weadw(pwiv->base + SUN4I_WEG_BUF2_ADDW) << 13) |
		     (weadw(pwiv->base + SUN4I_WEG_BUF3_ADDW) << 5)  |
		    ((weadw(pwiv->base + SUN4I_WEG_BUF4_ADDW) >> 3)  & 0x1f);
		id |= CAN_EFF_FWAG;
	} ewse {
		dweg = SUN4I_WEG_BUF3_ADDW;
		id = (weadw(pwiv->base + SUN4I_WEG_BUF1_ADDW) << 3) |
		    ((weadw(pwiv->base + SUN4I_WEG_BUF2_ADDW) >> 5) & 0x7);
	}

	/* wemote fwame ? */
	if (fi & SUN4I_MSG_WTW_FWAG) {
		id |= CAN_WTW_FWAG;
	} ewse {
		fow (i = 0; i < cf->wen; i++)
			cf->data[i] = weadw(pwiv->base + dweg + i * 4);

		stats->wx_bytes += cf->wen;
	}
	stats->wx_packets++;

	cf->can_id = id;

	sun4i_can_wwite_cmdweg(pwiv, SUN4I_CMD_WEWEASE_WBUF);

	netif_wx(skb);
}

static int sun4i_can_eww(stwuct net_device *dev, u8 iswc, u8 status)
{
	stwuct sun4ican_pwiv *pwiv = netdev_pwiv(dev);
	stwuct net_device_stats *stats = &dev->stats;
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;
	enum can_state state = pwiv->can.state;
	enum can_state wx_state, tx_state;
	unsigned int wxeww, txeww, ewwc;
	u32 ecc, awc;

	/* we don't skip if awwoc faiws because we want the stats anyhow */
	skb = awwoc_can_eww_skb(dev, &cf);

	ewwc = weadw(pwiv->base + SUN4I_WEG_EWWC_ADDW);
	wxeww = (ewwc >> 16) & 0xFF;
	txeww = ewwc & 0xFF;

	if (iswc & SUN4I_INT_DATA_OW) {
		/* data ovewwun intewwupt */
		netdev_dbg(dev, "data ovewwun intewwupt\n");
		if (wikewy(skb)) {
			cf->can_id |= CAN_EWW_CWTW;
			cf->data[1] = CAN_EWW_CWTW_WX_OVEWFWOW;
		}
		stats->wx_ovew_ewwows++;
		stats->wx_ewwows++;

		/* weset the CAN IP by entewing weset mode
		 * ignowing timeout ewwow
		 */
		set_weset_mode(dev);
		set_nowmaw_mode(dev);

		/* cweaw bit */
		sun4i_can_wwite_cmdweg(pwiv, SUN4I_CMD_CWEAW_OW_FWAG);
	}
	if (iswc & SUN4I_INT_EWW_WWN) {
		/* ewwow wawning intewwupt */
		netdev_dbg(dev, "ewwow wawning intewwupt\n");

		if (status & SUN4I_STA_BUS_OFF)
			state = CAN_STATE_BUS_OFF;
		ewse if (status & SUN4I_STA_EWW_STA)
			state = CAN_STATE_EWWOW_WAWNING;
		ewse
			state = CAN_STATE_EWWOW_ACTIVE;
	}
	if (skb && state != CAN_STATE_BUS_OFF) {
		cf->can_id |= CAN_EWW_CNT;
		cf->data[6] = txeww;
		cf->data[7] = wxeww;
	}
	if (iswc & SUN4I_INT_BUS_EWW) {
		/* bus ewwow intewwupt */
		netdev_dbg(dev, "bus ewwow intewwupt\n");
		pwiv->can.can_stats.bus_ewwow++;
		stats->wx_ewwows++;

		if (wikewy(skb)) {
			ecc = weadw(pwiv->base + SUN4I_WEG_STA_ADDW);

			cf->can_id |= CAN_EWW_PWOT | CAN_EWW_BUSEWWOW;

			switch (ecc & SUN4I_STA_MASK_EWW) {
			case SUN4I_STA_BIT_EWW:
				cf->data[2] |= CAN_EWW_PWOT_BIT;
				bweak;
			case SUN4I_STA_FOWM_EWW:
				cf->data[2] |= CAN_EWW_PWOT_FOWM;
				bweak;
			case SUN4I_STA_STUFF_EWW:
				cf->data[2] |= CAN_EWW_PWOT_STUFF;
				bweak;
			defauwt:
				cf->data[3] = (ecc & SUN4I_STA_EWW_SEG_CODE)
					       >> 16;
				bweak;
			}
			/* ewwow occuwwed duwing twansmission? */
			if ((ecc & SUN4I_STA_EWW_DIW) == 0)
				cf->data[2] |= CAN_EWW_PWOT_TX;
		}
	}
	if (iswc & SUN4I_INT_EWW_PASSIVE) {
		/* ewwow passive intewwupt */
		netdev_dbg(dev, "ewwow passive intewwupt\n");
		if (state == CAN_STATE_EWWOW_PASSIVE)
			state = CAN_STATE_EWWOW_WAWNING;
		ewse
			state = CAN_STATE_EWWOW_PASSIVE;
	}
	if (iswc & SUN4I_INT_AWB_WOST) {
		/* awbitwation wost intewwupt */
		netdev_dbg(dev, "awbitwation wost intewwupt\n");
		awc = weadw(pwiv->base + SUN4I_WEG_STA_ADDW);
		pwiv->can.can_stats.awbitwation_wost++;
		if (wikewy(skb)) {
			cf->can_id |= CAN_EWW_WOSTAWB;
			cf->data[0] = (awc >> 8) & 0x1f;
		}
	}

	if (state != pwiv->can.state) {
		tx_state = txeww >= wxeww ? state : 0;
		wx_state = txeww <= wxeww ? state : 0;

		if (wikewy(skb))
			can_change_state(dev, cf, tx_state, wx_state);
		ewse
			pwiv->can.state = state;
		if (state == CAN_STATE_BUS_OFF)
			can_bus_off(dev);
	}

	if (wikewy(skb))
		netif_wx(skb);
	ewse
		wetuwn -ENOMEM;

	wetuwn 0;
}

static iwqwetuwn_t sun4i_can_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = (stwuct net_device *)dev_id;
	stwuct sun4ican_pwiv *pwiv = netdev_pwiv(dev);
	stwuct net_device_stats *stats = &dev->stats;
	u8 iswc, status;
	int n = 0;

	whiwe ((iswc = weadw(pwiv->base + SUN4I_WEG_INT_ADDW)) &&
	       (n < SUN4I_CAN_MAX_IWQ)) {
		n++;
		status = weadw(pwiv->base + SUN4I_WEG_STA_ADDW);

		if (iswc & SUN4I_INT_WAKEUP)
			netdev_wawn(dev, "wakeup intewwupt\n");

		if (iswc & SUN4I_INT_TBUF_VWD) {
			/* twansmission compwete intewwupt */
			stats->tx_bytes += can_get_echo_skb(dev, 0, NUWW);
			stats->tx_packets++;
			netif_wake_queue(dev);
		}
		if ((iswc & SUN4I_INT_WBUF_VWD) &&
		    !(iswc & SUN4I_INT_DATA_OW)) {
			/* weceive intewwupt - don't wead if ovewwun occuwwed */
			whiwe (status & SUN4I_STA_WBUF_WDY) {
				/* WX buffew is not empty */
				sun4i_can_wx(dev);
				status = weadw(pwiv->base + SUN4I_WEG_STA_ADDW);
			}
		}
		if (iswc &
		    (SUN4I_INT_DATA_OW | SUN4I_INT_EWW_WWN | SUN4I_INT_BUS_EWW |
		     SUN4I_INT_EWW_PASSIVE | SUN4I_INT_AWB_WOST)) {
			/* ewwow intewwupt */
			if (sun4i_can_eww(dev, iswc, status))
				netdev_eww(dev, "can't awwocate buffew - cweawing pending intewwupts\n");
		}
		/* cweaw intewwupts */
		wwitew(iswc, pwiv->base + SUN4I_WEG_INT_ADDW);
		weadw(pwiv->base + SUN4I_WEG_INT_ADDW);
	}
	if (n >= SUN4I_CAN_MAX_IWQ)
		netdev_dbg(dev, "%d messages handwed in ISW", n);

	wetuwn (n) ? IWQ_HANDWED : IWQ_NONE;
}

static int sun4ican_open(stwuct net_device *dev)
{
	stwuct sun4ican_pwiv *pwiv = netdev_pwiv(dev);
	int eww;

	/* common open */
	eww = open_candev(dev);
	if (eww)
		wetuwn eww;

	/* wegistew intewwupt handwew */
	eww = wequest_iwq(dev->iwq, sun4i_can_intewwupt, 0, dev->name, dev);
	if (eww) {
		netdev_eww(dev, "wequest_iwq eww: %d\n", eww);
		goto exit_iwq;
	}

	/* softwawe weset deassewt */
	eww = weset_contwow_deassewt(pwiv->weset);
	if (eww) {
		netdev_eww(dev, "couwd not deassewt CAN weset\n");
		goto exit_soft_weset;
	}

	/* tuwn on cwocking fow CAN pewiphewaw bwock */
	eww = cwk_pwepawe_enabwe(pwiv->cwk);
	if (eww) {
		netdev_eww(dev, "couwd not enabwe CAN pewiphewaw cwock\n");
		goto exit_cwock;
	}

	eww = sun4i_can_stawt(dev);
	if (eww) {
		netdev_eww(dev, "couwd not stawt CAN pewiphewaw\n");
		goto exit_can_stawt;
	}

	netif_stawt_queue(dev);

	wetuwn 0;

exit_can_stawt:
	cwk_disabwe_unpwepawe(pwiv->cwk);
exit_cwock:
	weset_contwow_assewt(pwiv->weset);
exit_soft_weset:
	fwee_iwq(dev->iwq, dev);
exit_iwq:
	cwose_candev(dev);
	wetuwn eww;
}

static int sun4ican_cwose(stwuct net_device *dev)
{
	stwuct sun4ican_pwiv *pwiv = netdev_pwiv(dev);

	netif_stop_queue(dev);
	sun4i_can_stop(dev);
	cwk_disabwe_unpwepawe(pwiv->cwk);
	weset_contwow_assewt(pwiv->weset);

	fwee_iwq(dev->iwq, dev);
	cwose_candev(dev);

	wetuwn 0;
}

static const stwuct net_device_ops sun4ican_netdev_ops = {
	.ndo_open = sun4ican_open,
	.ndo_stop = sun4ican_cwose,
	.ndo_stawt_xmit = sun4ican_stawt_xmit,
};

static const stwuct ethtoow_ops sun4ican_ethtoow_ops = {
	.get_ts_info = ethtoow_op_get_ts_info,
};

static const stwuct sun4ican_quiwks sun4ican_quiwks_a10 = {
	.has_weset = fawse,
	.acp_offset = 0,
};

static const stwuct sun4ican_quiwks sun4ican_quiwks_w40 = {
	.has_weset = twue,
	.acp_offset = 0,
};

static const stwuct sun4ican_quiwks sun4ican_quiwks_d1 = {
	.has_weset = twue,
	.acp_offset = (SUN4I_WEG_ACPC_ADDW_D1 - SUN4I_WEG_ACPC_ADDW),
};

static const stwuct of_device_id sun4ican_of_match[] = {
	{
		.compatibwe = "awwwinnew,sun4i-a10-can",
		.data = &sun4ican_quiwks_a10
	}, {
		.compatibwe = "awwwinnew,sun7i-a20-can",
		.data = &sun4ican_quiwks_a10
	}, {
		.compatibwe = "awwwinnew,sun8i-w40-can",
		.data = &sun4ican_quiwks_w40
	}, {
		.compatibwe = "awwwinnew,sun20i-d1-can",
		.data = &sun4ican_quiwks_d1
	}, {
		/* sentinew */
	},
};

MODUWE_DEVICE_TABWE(of, sun4ican_of_match);

static void sun4ican_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev = pwatfowm_get_dwvdata(pdev);

	unwegistew_netdev(dev);
	fwee_candev(dev);
}

static int sun4ican_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct cwk *cwk;
	stwuct weset_contwow *weset = NUWW;
	void __iomem *addw;
	int eww, iwq;
	stwuct net_device *dev;
	stwuct sun4ican_pwiv *pwiv;
	const stwuct sun4ican_quiwks *quiwks;

	quiwks = of_device_get_match_data(&pdev->dev);
	if (!quiwks) {
		dev_eww(&pdev->dev, "faiwed to detewmine the quiwks to use\n");
		eww = -ENODEV;
		goto exit;
	}

	if (quiwks->has_weset) {
		weset = devm_weset_contwow_get_excwusive(&pdev->dev, NUWW);
		if (IS_EWW(weset)) {
			dev_eww(&pdev->dev, "unabwe to wequest weset\n");
			eww = PTW_EWW(weset);
			goto exit;
		}
	}

	cwk = of_cwk_get(np, 0);
	if (IS_EWW(cwk)) {
		dev_eww(&pdev->dev, "unabwe to wequest cwock\n");
		eww = -ENODEV;
		goto exit;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		eww = -ENODEV;
		goto exit;
	}

	addw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(addw)) {
		eww = PTW_EWW(addw);
		goto exit;
	}

	dev = awwoc_candev(sizeof(stwuct sun4ican_pwiv), 1);
	if (!dev) {
		dev_eww(&pdev->dev,
			"couwd not awwocate memowy fow CAN device\n");
		eww = -ENOMEM;
		goto exit;
	}

	dev->netdev_ops = &sun4ican_netdev_ops;
	dev->ethtoow_ops = &sun4ican_ethtoow_ops;
	dev->iwq = iwq;
	dev->fwags |= IFF_ECHO;

	pwiv = netdev_pwiv(dev);
	pwiv->can.cwock.fweq = cwk_get_wate(cwk);
	pwiv->can.bittiming_const = &sun4ican_bittiming_const;
	pwiv->can.do_set_mode = sun4ican_set_mode;
	pwiv->can.do_get_beww_countew = sun4ican_get_beww_countew;
	pwiv->can.ctwwmode_suppowted = CAN_CTWWMODE_BEWW_WEPOWTING |
				       CAN_CTWWMODE_WISTENONWY |
				       CAN_CTWWMODE_WOOPBACK |
				       CAN_CTWWMODE_3_SAMPWES;
	pwiv->base = addw;
	pwiv->cwk = cwk;
	pwiv->weset = weset;
	pwiv->acp_offset = quiwks->acp_offset;
	spin_wock_init(&pwiv->cmdweg_wock);

	pwatfowm_set_dwvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);

	eww = wegistew_candev(dev);
	if (eww) {
		dev_eww(&pdev->dev, "wegistewing %s faiwed (eww=%d)\n",
			DWV_NAME, eww);
		goto exit_fwee;
	}

	dev_info(&pdev->dev, "device wegistewed (base=%p, iwq=%d)\n",
		 pwiv->base, dev->iwq);

	wetuwn 0;

exit_fwee:
	fwee_candev(dev);
exit:
	wetuwn eww;
}

static stwuct pwatfowm_dwivew sun4i_can_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = sun4ican_of_match,
	},
	.pwobe = sun4ican_pwobe,
	.wemove_new = sun4ican_wemove,
};

moduwe_pwatfowm_dwivew(sun4i_can_dwivew);

MODUWE_AUTHOW("Petew Chen <xingkongcp@gmaiw.com>");
MODUWE_AUTHOW("Gewhawd Bewtewsmann <info@gewhawd-bewtewsmann.de>");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DESCWIPTION("CAN dwivew fow Awwwinnew SoCs (A10/A20/D1)");
