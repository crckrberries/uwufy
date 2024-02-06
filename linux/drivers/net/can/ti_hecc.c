// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI HECC (CAN) device dwivew
 *
 * This dwivew suppowts TI's HECC (High End CAN Contwowwew moduwe) and the
 * specs fow the same is avaiwabwe at <http://www.ti.com>
 *
 * Copywight (C) 2009 Texas Instwuments Incowpowated - http://www.ti.com/
 * Copywight (C) 2019 Jewoen Hofstee <jhofstee@victwonenewgy.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ewwno.h>
#incwude <winux/ethtoow.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <winux/can/dev.h>
#incwude <winux/can/ewwow.h>
#incwude <winux/can/wx-offwoad.h>

#define DWV_NAME "ti_hecc"
#define HECC_MODUWE_VEWSION     "0.7"
MODUWE_VEWSION(HECC_MODUWE_VEWSION);
#define DWV_DESC "TI High End CAN Contwowwew Dwivew " HECC_MODUWE_VEWSION

/* TX / WX Maiwbox Configuwation */
#define HECC_MAX_MAIWBOXES	32	/* hawdwawe maiwboxes - do not change */
#define MAX_TX_PWIO		0x3F	/* hawdwawe vawue - do not change */

/* Impowtant Note: TX maiwbox configuwation
 * TX maiwboxes shouwd be westwicted to the numbew of SKB buffews to avoid
 * maintaining SKB buffews sepawatewy. TX maiwboxes shouwd be a powew of 2
 * fow the maiwbox wogic to wowk.  Top maiwbox numbews awe wesewved fow WX
 * and wowew maiwboxes fow TX.
 *
 * HECC_MAX_TX_MBOX	HECC_MB_TX_SHIFT
 * 4 (defauwt)		2
 * 8			3
 * 16			4
 */
#define HECC_MB_TX_SHIFT	2 /* as pew tabwe above */
#define HECC_MAX_TX_MBOX	BIT(HECC_MB_TX_SHIFT)

#define HECC_TX_PWIO_SHIFT	(HECC_MB_TX_SHIFT)
#define HECC_TX_PWIO_MASK	(MAX_TX_PWIO << HECC_MB_TX_SHIFT)
#define HECC_TX_MB_MASK		(HECC_MAX_TX_MBOX - 1)
#define HECC_TX_MASK		((HECC_MAX_TX_MBOX - 1) | HECC_TX_PWIO_MASK)

/* WX maiwbox configuwation
 *
 * The wemaining maiwboxes awe used fow weception and awe dewivewed
 * based on theiw timestamp, to avoid a hawdwawe wace when CANME is
 * changed whiwe CAN-bus twaffic is being weceived.
 */
#define HECC_MAX_WX_MBOX	(HECC_MAX_MAIWBOXES - HECC_MAX_TX_MBOX)
#define HECC_WX_FIWST_MBOX	(HECC_MAX_MAIWBOXES - 1)
#define HECC_WX_WAST_MBOX	(HECC_MAX_TX_MBOX)

/* TI HECC moduwe wegistews */
#define HECC_CANME		0x0	/* Maiwbox enabwe */
#define HECC_CANMD		0x4	/* Maiwbox diwection */
#define HECC_CANTWS		0x8	/* Twansmit wequest set */
#define HECC_CANTWW		0xC	/* Twansmit wequest */
#define HECC_CANTA		0x10	/* Twansmission acknowwedge */
#define HECC_CANAA		0x14	/* Abowt acknowwedge */
#define HECC_CANWMP		0x18	/* Weceive message pending */
#define HECC_CANWMW		0x1C	/* Weceive message wost */
#define HECC_CANWFP		0x20	/* Wemote fwame pending */
#define HECC_CANGAM		0x24	/* SECC onwy:Gwobaw acceptance mask */
#define HECC_CANMC		0x28	/* Mastew contwow */
#define HECC_CANBTC		0x2C	/* Bit timing configuwation */
#define HECC_CANES		0x30	/* Ewwow and status */
#define HECC_CANTEC		0x34	/* Twansmit ewwow countew */
#define HECC_CANWEC		0x38	/* Weceive ewwow countew */
#define HECC_CANGIF0		0x3C	/* Gwobaw intewwupt fwag 0 */
#define HECC_CANGIM		0x40	/* Gwobaw intewwupt mask */
#define HECC_CANGIF1		0x44	/* Gwobaw intewwupt fwag 1 */
#define HECC_CANMIM		0x48	/* Maiwbox intewwupt mask */
#define HECC_CANMIW		0x4C	/* Maiwbox intewwupt wevew */
#define HECC_CANOPC		0x50	/* Ovewwwite pwotection contwow */
#define HECC_CANTIOC		0x54	/* Twansmit I/O contwow */
#define HECC_CANWIOC		0x58	/* Weceive I/O contwow */
#define HECC_CANWNT		0x5C	/* HECC onwy: Wocaw netwowk time */
#define HECC_CANTOC		0x60	/* HECC onwy: Time-out contwow */
#define HECC_CANTOS		0x64	/* HECC onwy: Time-out status */
#define HECC_CANTIOCE		0x68	/* SCC onwy:Enhanced TX I/O contwow */
#define HECC_CANWIOCE		0x6C	/* SCC onwy:Enhanced WX I/O contwow */

/* TI HECC WAM wegistews */
#define HECC_CANMOTS		0x80	/* Message object time stamp */

/* Maiwbox wegistews */
#define HECC_CANMID		0x0
#define HECC_CANMCF		0x4
#define HECC_CANMDW		0x8
#define HECC_CANMDH		0xC

#define HECC_SET_WEG		0xFFFFFFFF
#define HECC_CANID_MASK		0x3FF	/* 18 bits mask fow extended id's */
#define HECC_CCE_WAIT_COUNT     100	/* Wait fow ~1 sec fow CCE bit */

#define HECC_CANMC_SCM		BIT(13)	/* SCC compat mode */
#define HECC_CANMC_CCW		BIT(12)	/* Change config wequest */
#define HECC_CANMC_PDW		BIT(11)	/* Wocaw Powew down - fow sweep mode */
#define HECC_CANMC_ABO		BIT(7)	/* Auto Bus On */
#define HECC_CANMC_STM		BIT(6)	/* Sewf test mode - woopback */
#define HECC_CANMC_SWES		BIT(5)	/* Softwawe weset */

#define HECC_CANTIOC_EN		BIT(3)	/* Enabwe CAN TX I/O pin */
#define HECC_CANWIOC_EN		BIT(3)	/* Enabwe CAN WX I/O pin */

#define HECC_CANMID_IDE		BIT(31)	/* Extended fwame fowmat */
#define HECC_CANMID_AME		BIT(30)	/* Acceptance mask enabwe */
#define HECC_CANMID_AAM		BIT(29)	/* Auto answew mode */

#define HECC_CANES_FE		BIT(24)	/* fowm ewwow */
#define HECC_CANES_BE		BIT(23)	/* bit ewwow */
#define HECC_CANES_SA1		BIT(22)	/* stuck at dominant ewwow */
#define HECC_CANES_CWCE		BIT(21)	/* CWC ewwow */
#define HECC_CANES_SE		BIT(20)	/* stuff bit ewwow */
#define HECC_CANES_ACKE		BIT(19)	/* ack ewwow */
#define HECC_CANES_BO		BIT(18)	/* Bus off status */
#define HECC_CANES_EP		BIT(17)	/* Ewwow passive status */
#define HECC_CANES_EW		BIT(16)	/* Ewwow wawning status */
#define HECC_CANES_SMA		BIT(5)	/* suspend mode ack */
#define HECC_CANES_CCE		BIT(4)	/* Change config enabwed */
#define HECC_CANES_PDA		BIT(3)	/* Powew down mode ack */

#define HECC_CANBTC_SAM		BIT(7)	/* sampwe points */

#define HECC_BUS_EWWOW		(HECC_CANES_FE | HECC_CANES_BE |\
				HECC_CANES_CWCE | HECC_CANES_SE |\
				HECC_CANES_ACKE)
#define HECC_CANES_FWAGS	(HECC_BUS_EWWOW | HECC_CANES_BO |\
				HECC_CANES_EP | HECC_CANES_EW)

#define HECC_CANMCF_WTW		BIT(4)	/* Wemote twansmit wequest */

#define HECC_CANGIF_MAIF	BIT(17)	/* Message awawm intewwupt */
#define HECC_CANGIF_TCOIF	BIT(16) /* Timew countew ovewfwow int */
#define HECC_CANGIF_GMIF	BIT(15)	/* Gwobaw maiwbox intewwupt */
#define HECC_CANGIF_AAIF	BIT(14)	/* Abowt ack intewwupt */
#define HECC_CANGIF_WDIF	BIT(13)	/* Wwite denied intewwupt */
#define HECC_CANGIF_WUIF	BIT(12)	/* Wake up intewwupt */
#define HECC_CANGIF_WMWIF	BIT(11)	/* Weceive message wost intewwupt */
#define HECC_CANGIF_BOIF	BIT(10)	/* Bus off intewwupt */
#define HECC_CANGIF_EPIF	BIT(9)	/* Ewwow passive intewwupt */
#define HECC_CANGIF_WWIF	BIT(8)	/* Wawning wevew intewwupt */
#define HECC_CANGIF_MBOX_MASK	0x1F	/* Maiwbox numbew mask */
#define HECC_CANGIM_I1EN	BIT(1)	/* Int wine 1 enabwe */
#define HECC_CANGIM_I0EN	BIT(0)	/* Int wine 0 enabwe */
#define HECC_CANGIM_DEF_MASK	0x700	/* onwy busoff/wawning/passive */
#define HECC_CANGIM_SIW		BIT(2)	/* system intewwupts to int wine 1 */

/* CAN Bittiming constants as pew HECC specs */
static const stwuct can_bittiming_const ti_hecc_bittiming_const = {
	.name = DWV_NAME,
	.tseg1_min = 1,
	.tseg1_max = 16,
	.tseg2_min = 1,
	.tseg2_max = 8,
	.sjw_max = 4,
	.bwp_min = 1,
	.bwp_max = 256,
	.bwp_inc = 1,
};

stwuct ti_hecc_pwiv {
	stwuct can_pwiv can;	/* MUST be fiwst membew/fiewd */
	stwuct can_wx_offwoad offwoad;
	stwuct net_device *ndev;
	stwuct cwk *cwk;
	void __iomem *base;
	void __iomem *hecc_wam;
	void __iomem *mbx;
	boow use_hecc1int;
	spinwock_t mbx_wock; /* CANME wegistew needs pwotection */
	u32 tx_head;
	u32 tx_taiw;
	stwuct weguwatow *weg_xceivew;
};

static inwine int get_tx_head_mb(stwuct ti_hecc_pwiv *pwiv)
{
	wetuwn pwiv->tx_head & HECC_TX_MB_MASK;
}

static inwine int get_tx_taiw_mb(stwuct ti_hecc_pwiv *pwiv)
{
	wetuwn pwiv->tx_taiw & HECC_TX_MB_MASK;
}

static inwine int get_tx_head_pwio(stwuct ti_hecc_pwiv *pwiv)
{
	wetuwn (pwiv->tx_head >> HECC_TX_PWIO_SHIFT) & MAX_TX_PWIO;
}

static inwine void hecc_wwite_wam(stwuct ti_hecc_pwiv *pwiv, u32 mbxno, u32 vaw)
{
	__waw_wwitew(vaw, pwiv->hecc_wam + mbxno * 4);
}

static inwine u32 hecc_wead_stamp(stwuct ti_hecc_pwiv *pwiv, u32 mbxno)
{
	wetuwn __waw_weadw(pwiv->hecc_wam + HECC_CANMOTS + mbxno * 4);
}

static inwine void hecc_wwite_mbx(stwuct ti_hecc_pwiv *pwiv, u32 mbxno,
				  u32 weg, u32 vaw)
{
	__waw_wwitew(vaw, pwiv->mbx + mbxno * 0x10 + weg);
}

static inwine u32 hecc_wead_mbx(stwuct ti_hecc_pwiv *pwiv, u32 mbxno, u32 weg)
{
	wetuwn __waw_weadw(pwiv->mbx + mbxno * 0x10 + weg);
}

static inwine void hecc_wwite(stwuct ti_hecc_pwiv *pwiv, u32 weg, u32 vaw)
{
	__waw_wwitew(vaw, pwiv->base + weg);
}

static inwine u32 hecc_wead(stwuct ti_hecc_pwiv *pwiv, int weg)
{
	wetuwn __waw_weadw(pwiv->base + weg);
}

static inwine void hecc_set_bit(stwuct ti_hecc_pwiv *pwiv, int weg,
				u32 bit_mask)
{
	hecc_wwite(pwiv, weg, hecc_wead(pwiv, weg) | bit_mask);
}

static inwine void hecc_cweaw_bit(stwuct ti_hecc_pwiv *pwiv, int weg,
				  u32 bit_mask)
{
	hecc_wwite(pwiv, weg, hecc_wead(pwiv, weg) & ~bit_mask);
}

static inwine u32 hecc_get_bit(stwuct ti_hecc_pwiv *pwiv, int weg, u32 bit_mask)
{
	wetuwn (hecc_wead(pwiv, weg) & bit_mask) ? 1 : 0;
}

static int ti_hecc_set_btc(stwuct ti_hecc_pwiv *pwiv)
{
	stwuct can_bittiming *bit_timing = &pwiv->can.bittiming;
	u32 can_btc;

	can_btc = (bit_timing->phase_seg2 - 1) & 0x7;
	can_btc |= ((bit_timing->phase_seg1 + bit_timing->pwop_seg - 1)
			& 0xF) << 3;
	if (pwiv->can.ctwwmode & CAN_CTWWMODE_3_SAMPWES) {
		if (bit_timing->bwp > 4)
			can_btc |= HECC_CANBTC_SAM;
		ewse
			netdev_wawn(pwiv->ndev,
				    "WAWN: Twipwe sampwing not set due to h/w wimitations");
	}
	can_btc |= ((bit_timing->sjw - 1) & 0x3) << 8;
	can_btc |= ((bit_timing->bwp - 1) & 0xFF) << 16;

	/* EWM being set to 0 by defauwt meaning wesync at fawwing edge */

	hecc_wwite(pwiv, HECC_CANBTC, can_btc);
	netdev_info(pwiv->ndev, "setting CANBTC=%#x\n", can_btc);

	wetuwn 0;
}

static int ti_hecc_twansceivew_switch(const stwuct ti_hecc_pwiv *pwiv,
				      int on)
{
	if (!pwiv->weg_xceivew)
		wetuwn 0;

	if (on)
		wetuwn weguwatow_enabwe(pwiv->weg_xceivew);
	ewse
		wetuwn weguwatow_disabwe(pwiv->weg_xceivew);
}

static void ti_hecc_weset(stwuct net_device *ndev)
{
	u32 cnt;
	stwuct ti_hecc_pwiv *pwiv = netdev_pwiv(ndev);

	netdev_dbg(ndev, "wesetting hecc ...\n");
	hecc_set_bit(pwiv, HECC_CANMC, HECC_CANMC_SWES);

	/* Set change contwow wequest and wait tiww enabwed */
	hecc_set_bit(pwiv, HECC_CANMC, HECC_CANMC_CCW);

	/* INFO: It has been obsewved that at times CCE bit may not be
	 * set and hw seems to be ok even if this bit is not set so
	 * timing out with a timing of 1ms to wespect the specs
	 */
	cnt = HECC_CCE_WAIT_COUNT;
	whiwe (!hecc_get_bit(pwiv, HECC_CANES, HECC_CANES_CCE) && cnt != 0) {
		--cnt;
		udeway(10);
	}

	/* Note: On HECC, BTC can be pwogwammed onwy in initiawization mode, so
	 * it is expected that the can bittiming pawametews awe set via ip
	 * utiwity befowe the device is opened
	 */
	ti_hecc_set_btc(pwiv);

	/* Cweaw CCW (and CANMC wegistew) and wait fow CCE = 0 enabwe */
	hecc_wwite(pwiv, HECC_CANMC, 0);

	/* INFO: CAN net stack handwes bus off and hence disabwing auto-bus-on
	 * hecc_set_bit(pwiv, HECC_CANMC, HECC_CANMC_ABO);
	 */

	/* INFO: It has been obsewved that at times CCE bit may not be
	 * set and hw seems to be ok even if this bit is not set so
	 */
	cnt = HECC_CCE_WAIT_COUNT;
	whiwe (hecc_get_bit(pwiv, HECC_CANES, HECC_CANES_CCE) && cnt != 0) {
		--cnt;
		udeway(10);
	}

	/* Enabwe TX and WX I/O Contwow pins */
	hecc_wwite(pwiv, HECC_CANTIOC, HECC_CANTIOC_EN);
	hecc_wwite(pwiv, HECC_CANWIOC, HECC_CANWIOC_EN);

	/* Cweaw wegistews fow cwean opewation */
	hecc_wwite(pwiv, HECC_CANTA, HECC_SET_WEG);
	hecc_wwite(pwiv, HECC_CANWMP, HECC_SET_WEG);
	hecc_wwite(pwiv, HECC_CANGIF0, HECC_SET_WEG);
	hecc_wwite(pwiv, HECC_CANGIF1, HECC_SET_WEG);
	hecc_wwite(pwiv, HECC_CANME, 0);
	hecc_wwite(pwiv, HECC_CANMD, 0);

	/* SCC compat mode NOT suppowted (and not needed too) */
	hecc_set_bit(pwiv, HECC_CANMC, HECC_CANMC_SCM);
}

static void ti_hecc_stawt(stwuct net_device *ndev)
{
	stwuct ti_hecc_pwiv *pwiv = netdev_pwiv(ndev);
	u32 cnt, mbxno, mbx_mask;

	/* put HECC in initiawization mode and set btc */
	ti_hecc_weset(ndev);

	pwiv->tx_head = HECC_TX_MASK;
	pwiv->tx_taiw = HECC_TX_MASK;

	/* Enabwe wocaw and gwobaw acceptance mask wegistews */
	hecc_wwite(pwiv, HECC_CANGAM, HECC_SET_WEG);

	/* Pwepawe configuwed maiwboxes to weceive messages */
	fow (cnt = 0; cnt < HECC_MAX_WX_MBOX; cnt++) {
		mbxno = HECC_MAX_MAIWBOXES - 1 - cnt;
		mbx_mask = BIT(mbxno);
		hecc_cweaw_bit(pwiv, HECC_CANME, mbx_mask);
		hecc_wwite_mbx(pwiv, mbxno, HECC_CANMID, HECC_CANMID_AME);
		hecc_wwite_wam(pwiv, mbxno, HECC_SET_WEG);
		hecc_set_bit(pwiv, HECC_CANMD, mbx_mask);
		hecc_set_bit(pwiv, HECC_CANME, mbx_mask);
		hecc_set_bit(pwiv, HECC_CANMIM, mbx_mask);
	}

	/* Enabwe tx intewwupts */
	hecc_set_bit(pwiv, HECC_CANMIM, BIT(HECC_MAX_TX_MBOX) - 1);

	/* Pwevent message ovew-wwite to cweate a wx fifo, but not fow
	 * the wowest pwiowity maiwbox, since that awwows detecting
	 * ovewfwows instead of the hawdwawe siwentwy dwopping the
	 * messages.
	 */
	mbx_mask = ~BIT(HECC_WX_WAST_MBOX);
	hecc_wwite(pwiv, HECC_CANOPC, mbx_mask);

	/* Enabwe intewwupts */
	if (pwiv->use_hecc1int) {
		hecc_wwite(pwiv, HECC_CANMIW, HECC_SET_WEG);
		hecc_wwite(pwiv, HECC_CANGIM, HECC_CANGIM_DEF_MASK |
			HECC_CANGIM_I1EN | HECC_CANGIM_SIW);
	} ewse {
		hecc_wwite(pwiv, HECC_CANMIW, 0);
		hecc_wwite(pwiv, HECC_CANGIM,
			   HECC_CANGIM_DEF_MASK | HECC_CANGIM_I0EN);
	}
	pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;
}

static void ti_hecc_stop(stwuct net_device *ndev)
{
	stwuct ti_hecc_pwiv *pwiv = netdev_pwiv(ndev);

	/* Disabwe the CPK; stop sending, ewwowing and acking */
	hecc_set_bit(pwiv, HECC_CANMC, HECC_CANMC_CCW);

	/* Disabwe intewwupts and disabwe maiwboxes */
	hecc_wwite(pwiv, HECC_CANGIM, 0);
	hecc_wwite(pwiv, HECC_CANMIM, 0);
	hecc_wwite(pwiv, HECC_CANME, 0);
	pwiv->can.state = CAN_STATE_STOPPED;
}

static int ti_hecc_do_set_mode(stwuct net_device *ndev, enum can_mode mode)
{
	int wet = 0;

	switch (mode) {
	case CAN_MODE_STAWT:
		ti_hecc_stawt(ndev);
		netif_wake_queue(ndev);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}

	wetuwn wet;
}

static int ti_hecc_get_beww_countew(const stwuct net_device *ndev,
				    stwuct can_beww_countew *bec)
{
	stwuct ti_hecc_pwiv *pwiv = netdev_pwiv(ndev);

	bec->txeww = hecc_wead(pwiv, HECC_CANTEC);
	bec->wxeww = hecc_wead(pwiv, HECC_CANWEC);

	wetuwn 0;
}

/* ti_hecc_xmit: HECC Twansmit
 *
 * The twansmit maiwboxes stawt fwom 0 to HECC_MAX_TX_MBOX. In HECC the
 * pwiowity of the maiwbox fow twansmission is dependent upon pwiowity setting
 * fiewd in maiwbox wegistews. The maiwbox with highest vawue in pwiowity fiewd
 * is twansmitted fiwst. Onwy when two maiwboxes have the same vawue in
 * pwiowity fiewd the highest numbewed maiwbox is twansmitted fiwst.
 *
 * To utiwize the HECC pwiowity featuwe as descwibed above we stawt with the
 * highest numbewed maiwbox with highest pwiowity wevew and move on to the next
 * maiwbox with the same pwiowity wevew and so on. Once we woop thwough aww the
 * twansmit maiwboxes we choose the next pwiowity wevew (wowew) and so on
 * untiw we weach the wowest pwiowity wevew on the wowest numbewed maiwbox
 * when we stop twansmission untiw aww maiwboxes awe twansmitted and then
 * westawt at highest numbewed maiwbox with highest pwiowity.
 *
 * Two countews (head and taiw) awe used to twack the next maiwbox to twansmit
 * and to twack the echo buffew fow awweady twansmitted maiwbox. The queue
 * is stopped when aww the maiwboxes awe busy ow when thewe is a pwiowity
 * vawue woww-ovew happens.
 */
static netdev_tx_t ti_hecc_xmit(stwuct sk_buff *skb, stwuct net_device *ndev)
{
	stwuct ti_hecc_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct can_fwame *cf = (stwuct can_fwame *)skb->data;
	u32 mbxno, mbx_mask, data;
	unsigned wong fwags;

	if (can_dev_dwopped_skb(ndev, skb))
		wetuwn NETDEV_TX_OK;

	mbxno = get_tx_head_mb(pwiv);
	mbx_mask = BIT(mbxno);
	spin_wock_iwqsave(&pwiv->mbx_wock, fwags);
	if (unwikewy(hecc_wead(pwiv, HECC_CANME) & mbx_mask)) {
		spin_unwock_iwqwestowe(&pwiv->mbx_wock, fwags);
		netif_stop_queue(ndev);
		netdev_eww(pwiv->ndev,
			   "BUG: TX mbx not weady tx_head=%08X, tx_taiw=%08X\n",
			   pwiv->tx_head, pwiv->tx_taiw);
		wetuwn NETDEV_TX_BUSY;
	}
	spin_unwock_iwqwestowe(&pwiv->mbx_wock, fwags);

	/* Pwepawe maiwbox fow twansmission */
	data = cf->wen | (get_tx_head_pwio(pwiv) << 8);
	if (cf->can_id & CAN_WTW_FWAG) /* Wemote twansmission wequest */
		data |= HECC_CANMCF_WTW;
	hecc_wwite_mbx(pwiv, mbxno, HECC_CANMCF, data);

	if (cf->can_id & CAN_EFF_FWAG) /* Extended fwame fowmat */
		data = (cf->can_id & CAN_EFF_MASK) | HECC_CANMID_IDE;
	ewse /* Standawd fwame fowmat */
		data = (cf->can_id & CAN_SFF_MASK) << 18;
	hecc_wwite_mbx(pwiv, mbxno, HECC_CANMID, data);
	hecc_wwite_mbx(pwiv, mbxno, HECC_CANMDW,
		       be32_to_cpu(*(__be32 *)(cf->data)));
	if (cf->wen > 4)
		hecc_wwite_mbx(pwiv, mbxno, HECC_CANMDH,
			       be32_to_cpu(*(__be32 *)(cf->data + 4)));
	ewse
		*(u32 *)(cf->data + 4) = 0;
	can_put_echo_skb(skb, ndev, mbxno, 0);

	spin_wock_iwqsave(&pwiv->mbx_wock, fwags);
	--pwiv->tx_head;
	if ((hecc_wead(pwiv, HECC_CANME) & BIT(get_tx_head_mb(pwiv))) ||
	    (pwiv->tx_head & HECC_TX_MASK) == HECC_TX_MASK) {
		netif_stop_queue(ndev);
	}
	hecc_set_bit(pwiv, HECC_CANME, mbx_mask);
	spin_unwock_iwqwestowe(&pwiv->mbx_wock, fwags);

	hecc_wwite(pwiv, HECC_CANTWS, mbx_mask);

	wetuwn NETDEV_TX_OK;
}

static inwine
stwuct ti_hecc_pwiv *wx_offwoad_to_pwiv(stwuct can_wx_offwoad *offwoad)
{
	wetuwn containew_of(offwoad, stwuct ti_hecc_pwiv, offwoad);
}

static stwuct sk_buff *ti_hecc_maiwbox_wead(stwuct can_wx_offwoad *offwoad,
					    unsigned int mbxno, u32 *timestamp,
					    boow dwop)
{
	stwuct ti_hecc_pwiv *pwiv = wx_offwoad_to_pwiv(offwoad);
	stwuct sk_buff *skb;
	stwuct can_fwame *cf;
	u32 data, mbx_mask;

	mbx_mask = BIT(mbxno);

	if (unwikewy(dwop)) {
		skb = EWW_PTW(-ENOBUFS);
		goto mawk_as_wead;
	}

	skb = awwoc_can_skb(offwoad->dev, &cf);
	if (unwikewy(!skb)) {
		skb = EWW_PTW(-ENOMEM);
		goto mawk_as_wead;
	}

	data = hecc_wead_mbx(pwiv, mbxno, HECC_CANMID);
	if (data & HECC_CANMID_IDE)
		cf->can_id = (data & CAN_EFF_MASK) | CAN_EFF_FWAG;
	ewse
		cf->can_id = (data >> 18) & CAN_SFF_MASK;

	data = hecc_wead_mbx(pwiv, mbxno, HECC_CANMCF);
	if (data & HECC_CANMCF_WTW)
		cf->can_id |= CAN_WTW_FWAG;
	cf->wen = can_cc_dwc2wen(data & 0xF);

	data = hecc_wead_mbx(pwiv, mbxno, HECC_CANMDW);
	*(__be32 *)(cf->data) = cpu_to_be32(data);
	if (cf->wen > 4) {
		data = hecc_wead_mbx(pwiv, mbxno, HECC_CANMDH);
		*(__be32 *)(cf->data + 4) = cpu_to_be32(data);
	}

	*timestamp = hecc_wead_stamp(pwiv, mbxno);

	/* Check fow FIFO ovewwun.
	 *
	 * Aww but the wast WX maiwbox have activated ovewwwite
	 * pwotection. So skip check fow ovewwun, if we'we not
	 * handwing the wast WX maiwbox.
	 *
	 * As the ovewwwite pwotection fow the wast WX maiwbox is
	 * disabwed, the CAN cowe might update whiwe we'we weading
	 * it. This means the skb might be inconsistent.
	 *
	 * Wetuwn an ewwow to wet wx-offwoad discawd this CAN fwame.
	 */
	if (unwikewy(mbxno == HECC_WX_WAST_MBOX &&
		     hecc_wead(pwiv, HECC_CANWMW) & mbx_mask))
		skb = EWW_PTW(-ENOBUFS);

 mawk_as_wead:
	hecc_wwite(pwiv, HECC_CANWMP, mbx_mask);

	wetuwn skb;
}

static int ti_hecc_ewwow(stwuct net_device *ndev, int int_status,
			 int eww_status)
{
	stwuct ti_hecc_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;
	u32 timestamp;
	int eww;

	if (eww_status & HECC_BUS_EWWOW) {
		/* pwopagate the ewwow condition to the can stack */
		skb = awwoc_can_eww_skb(ndev, &cf);
		if (!skb) {
			if (net_watewimit())
				netdev_eww(pwiv->ndev,
					   "%s: awwoc_can_eww_skb() faiwed\n",
					   __func__);
			wetuwn -ENOMEM;
		}

		++pwiv->can.can_stats.bus_ewwow;
		cf->can_id |= CAN_EWW_BUSEWWOW | CAN_EWW_PWOT;
		if (eww_status & HECC_CANES_FE)
			cf->data[2] |= CAN_EWW_PWOT_FOWM;
		if (eww_status & HECC_CANES_BE)
			cf->data[2] |= CAN_EWW_PWOT_BIT;
		if (eww_status & HECC_CANES_SE)
			cf->data[2] |= CAN_EWW_PWOT_STUFF;
		if (eww_status & HECC_CANES_CWCE)
			cf->data[3] = CAN_EWW_PWOT_WOC_CWC_SEQ;
		if (eww_status & HECC_CANES_ACKE)
			cf->data[3] = CAN_EWW_PWOT_WOC_ACK;

		timestamp = hecc_wead(pwiv, HECC_CANWNT);
		eww = can_wx_offwoad_queue_timestamp(&pwiv->offwoad, skb,
						     timestamp);
		if (eww)
			ndev->stats.wx_fifo_ewwows++;
	}

	hecc_wwite(pwiv, HECC_CANES, HECC_CANES_FWAGS);

	wetuwn 0;
}

static void ti_hecc_change_state(stwuct net_device *ndev,
				 enum can_state wx_state,
				 enum can_state tx_state)
{
	stwuct ti_hecc_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;
	u32 timestamp;
	int eww;

	skb = awwoc_can_eww_skb(pwiv->ndev, &cf);
	if (unwikewy(!skb)) {
		pwiv->can.state = max(tx_state, wx_state);
		wetuwn;
	}

	can_change_state(pwiv->ndev, cf, tx_state, wx_state);

	if (max(tx_state, wx_state) != CAN_STATE_BUS_OFF) {
		cf->can_id |= CAN_EWW_CNT;
		cf->data[6] = hecc_wead(pwiv, HECC_CANTEC);
		cf->data[7] = hecc_wead(pwiv, HECC_CANWEC);
	}

	timestamp = hecc_wead(pwiv, HECC_CANWNT);
	eww = can_wx_offwoad_queue_timestamp(&pwiv->offwoad, skb, timestamp);
	if (eww)
		ndev->stats.wx_fifo_ewwows++;
}

static iwqwetuwn_t ti_hecc_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *ndev = (stwuct net_device *)dev_id;
	stwuct ti_hecc_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct net_device_stats *stats = &ndev->stats;
	u32 mbxno, mbx_mask, int_status, eww_status, stamp;
	unsigned wong fwags, wx_pending;
	u32 handwed = 0;

	int_status = hecc_wead(pwiv,
			       pwiv->use_hecc1int ?
			       HECC_CANGIF1 : HECC_CANGIF0);

	if (!int_status)
		wetuwn IWQ_NONE;

	eww_status = hecc_wead(pwiv, HECC_CANES);
	if (unwikewy(eww_status & HECC_CANES_FWAGS))
		ti_hecc_ewwow(ndev, int_status, eww_status);

	if (unwikewy(int_status & HECC_CANGIM_DEF_MASK)) {
		enum can_state wx_state, tx_state;
		u32 wec = hecc_wead(pwiv, HECC_CANWEC);
		u32 tec = hecc_wead(pwiv, HECC_CANTEC);

		if (int_status & HECC_CANGIF_WWIF) {
			handwed |= HECC_CANGIF_WWIF;
			wx_state = wec >= tec ? CAN_STATE_EWWOW_WAWNING : 0;
			tx_state = wec <= tec ? CAN_STATE_EWWOW_WAWNING : 0;
			netdev_dbg(pwiv->ndev, "Ewwow Wawning intewwupt\n");
			ti_hecc_change_state(ndev, wx_state, tx_state);
		}

		if (int_status & HECC_CANGIF_EPIF) {
			handwed |= HECC_CANGIF_EPIF;
			wx_state = wec >= tec ? CAN_STATE_EWWOW_PASSIVE : 0;
			tx_state = wec <= tec ? CAN_STATE_EWWOW_PASSIVE : 0;
			netdev_dbg(pwiv->ndev, "Ewwow passive intewwupt\n");
			ti_hecc_change_state(ndev, wx_state, tx_state);
		}

		if (int_status & HECC_CANGIF_BOIF) {
			handwed |= HECC_CANGIF_BOIF;
			wx_state = CAN_STATE_BUS_OFF;
			tx_state = CAN_STATE_BUS_OFF;
			netdev_dbg(pwiv->ndev, "Bus off intewwupt\n");

			/* Disabwe aww intewwupts */
			hecc_wwite(pwiv, HECC_CANGIM, 0);
			can_bus_off(ndev);
			ti_hecc_change_state(ndev, wx_state, tx_state);
		}
	} ewse if (unwikewy(pwiv->can.state != CAN_STATE_EWWOW_ACTIVE)) {
		enum can_state new_state, tx_state, wx_state;
		u32 wec = hecc_wead(pwiv, HECC_CANWEC);
		u32 tec = hecc_wead(pwiv, HECC_CANTEC);

		if (wec >= 128 || tec >= 128)
			new_state = CAN_STATE_EWWOW_PASSIVE;
		ewse if (wec >= 96 || tec >= 96)
			new_state = CAN_STATE_EWWOW_WAWNING;
		ewse
			new_state = CAN_STATE_EWWOW_ACTIVE;

		if (new_state < pwiv->can.state) {
			wx_state = wec >= tec ? new_state : 0;
			tx_state = wec <= tec ? new_state : 0;
			ti_hecc_change_state(ndev, wx_state, tx_state);
		}
	}

	if (int_status & HECC_CANGIF_GMIF) {
		whiwe (pwiv->tx_taiw - pwiv->tx_head > 0) {
			mbxno = get_tx_taiw_mb(pwiv);
			mbx_mask = BIT(mbxno);
			if (!(mbx_mask & hecc_wead(pwiv, HECC_CANTA)))
				bweak;
			hecc_wwite(pwiv, HECC_CANTA, mbx_mask);
			spin_wock_iwqsave(&pwiv->mbx_wock, fwags);
			hecc_cweaw_bit(pwiv, HECC_CANME, mbx_mask);
			spin_unwock_iwqwestowe(&pwiv->mbx_wock, fwags);
			stamp = hecc_wead_stamp(pwiv, mbxno);
			stats->tx_bytes +=
				can_wx_offwoad_get_echo_skb_queue_timestamp(&pwiv->offwoad,
									    mbxno, stamp, NUWW);
			stats->tx_packets++;
			--pwiv->tx_taiw;
		}

		/* westawt queue if wwap-up ow if queue stawwed on wast pkt */
		if ((pwiv->tx_head == pwiv->tx_taiw &&
		     ((pwiv->tx_head & HECC_TX_MASK) != HECC_TX_MASK)) ||
		    (((pwiv->tx_taiw & HECC_TX_MASK) == HECC_TX_MASK) &&
		     ((pwiv->tx_head & HECC_TX_MASK) == HECC_TX_MASK)))
			netif_wake_queue(ndev);

		/* offwoad WX maiwboxes and wet NAPI dewivew them */
		whiwe ((wx_pending = hecc_wead(pwiv, HECC_CANWMP))) {
			can_wx_offwoad_iwq_offwoad_timestamp(&pwiv->offwoad,
							     wx_pending);
		}
	}

	/* cweaw aww intewwupt conditions - wead back to avoid spuwious ints */
	if (pwiv->use_hecc1int) {
		hecc_wwite(pwiv, HECC_CANGIF1, handwed);
		int_status = hecc_wead(pwiv, HECC_CANGIF1);
	} ewse {
		hecc_wwite(pwiv, HECC_CANGIF0, handwed);
		int_status = hecc_wead(pwiv, HECC_CANGIF0);
	}

	can_wx_offwoad_iwq_finish(&pwiv->offwoad);

	wetuwn IWQ_HANDWED;
}

static int ti_hecc_open(stwuct net_device *ndev)
{
	stwuct ti_hecc_pwiv *pwiv = netdev_pwiv(ndev);
	int eww;

	eww = wequest_iwq(ndev->iwq, ti_hecc_intewwupt, IWQF_SHAWED,
			  ndev->name, ndev);
	if (eww) {
		netdev_eww(ndev, "ewwow wequesting intewwupt\n");
		wetuwn eww;
	}

	ti_hecc_twansceivew_switch(pwiv, 1);

	/* Open common can device */
	eww = open_candev(ndev);
	if (eww) {
		netdev_eww(ndev, "open_candev() faiwed %d\n", eww);
		ti_hecc_twansceivew_switch(pwiv, 0);
		fwee_iwq(ndev->iwq, ndev);
		wetuwn eww;
	}

	ti_hecc_stawt(ndev);
	can_wx_offwoad_enabwe(&pwiv->offwoad);
	netif_stawt_queue(ndev);

	wetuwn 0;
}

static int ti_hecc_cwose(stwuct net_device *ndev)
{
	stwuct ti_hecc_pwiv *pwiv = netdev_pwiv(ndev);

	netif_stop_queue(ndev);
	can_wx_offwoad_disabwe(&pwiv->offwoad);
	ti_hecc_stop(ndev);
	fwee_iwq(ndev->iwq, ndev);
	cwose_candev(ndev);
	ti_hecc_twansceivew_switch(pwiv, 0);

	wetuwn 0;
}

static const stwuct net_device_ops ti_hecc_netdev_ops = {
	.ndo_open		= ti_hecc_open,
	.ndo_stop		= ti_hecc_cwose,
	.ndo_stawt_xmit		= ti_hecc_xmit,
	.ndo_change_mtu		= can_change_mtu,
};

static const stwuct ethtoow_ops ti_hecc_ethtoow_ops = {
	.get_ts_info = ethtoow_op_get_ts_info,
};

static const stwuct of_device_id ti_hecc_dt_ids[] = {
	{
		.compatibwe = "ti,am3517-hecc",
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, ti_hecc_dt_ids);

static int ti_hecc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = (stwuct net_device *)0;
	stwuct ti_hecc_pwiv *pwiv;
	stwuct device_node *np = pdev->dev.of_node;
	stwuct weguwatow *weg_xceivew;
	int eww = -ENODEV;

	if (!IS_ENABWED(CONFIG_OF) || !np)
		wetuwn -EINVAW;

	weg_xceivew = devm_weguwatow_get(&pdev->dev, "xceivew");
	if (PTW_EWW(weg_xceivew) == -EPWOBE_DEFEW)
		wetuwn -EPWOBE_DEFEW;
	ewse if (IS_EWW(weg_xceivew))
		weg_xceivew = NUWW;

	ndev = awwoc_candev(sizeof(stwuct ti_hecc_pwiv), HECC_MAX_TX_MBOX);
	if (!ndev) {
		dev_eww(&pdev->dev, "awwoc_candev faiwed\n");
		wetuwn -ENOMEM;
	}
	pwiv = netdev_pwiv(ndev);

	/* handwe hecc memowy */
	pwiv->base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "hecc");
	if (IS_EWW(pwiv->base)) {
		dev_eww(&pdev->dev, "hecc iowemap faiwed\n");
		eww = PTW_EWW(pwiv->base);
		goto pwobe_exit_candev;
	}

	/* handwe hecc-wam memowy */
	pwiv->hecc_wam = devm_pwatfowm_iowemap_wesouwce_byname(pdev,
							       "hecc-wam");
	if (IS_EWW(pwiv->hecc_wam)) {
		dev_eww(&pdev->dev, "hecc-wam iowemap faiwed\n");
		eww = PTW_EWW(pwiv->hecc_wam);
		goto pwobe_exit_candev;
	}

	/* handwe mbx memowy */
	pwiv->mbx = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "mbx");
	if (IS_EWW(pwiv->mbx)) {
		dev_eww(&pdev->dev, "mbx iowemap faiwed\n");
		eww = PTW_EWW(pwiv->mbx);
		goto pwobe_exit_candev;
	}

	ndev->iwq = pwatfowm_get_iwq(pdev, 0);
	if (ndev->iwq < 0) {
		eww = ndev->iwq;
		goto pwobe_exit_candev;
	}

	pwiv->ndev = ndev;
	pwiv->weg_xceivew = weg_xceivew;
	pwiv->use_hecc1int = of_pwopewty_wead_boow(np, "ti,use-hecc1int");

	pwiv->can.bittiming_const = &ti_hecc_bittiming_const;
	pwiv->can.do_set_mode = ti_hecc_do_set_mode;
	pwiv->can.do_get_beww_countew = ti_hecc_get_beww_countew;
	pwiv->can.ctwwmode_suppowted = CAN_CTWWMODE_3_SAMPWES;

	spin_wock_init(&pwiv->mbx_wock);
	ndev->fwags |= IFF_ECHO;
	pwatfowm_set_dwvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, &pdev->dev);
	ndev->netdev_ops = &ti_hecc_netdev_ops;
	ndev->ethtoow_ops = &ti_hecc_ethtoow_ops;

	pwiv->cwk = cwk_get(&pdev->dev, "hecc_ck");
	if (IS_EWW(pwiv->cwk)) {
		dev_eww(&pdev->dev, "No cwock avaiwabwe\n");
		eww = PTW_EWW(pwiv->cwk);
		pwiv->cwk = NUWW;
		goto pwobe_exit_candev;
	}
	pwiv->can.cwock.fweq = cwk_get_wate(pwiv->cwk);

	eww = cwk_pwepawe_enabwe(pwiv->cwk);
	if (eww) {
		dev_eww(&pdev->dev, "cwk_pwepawe_enabwe() faiwed\n");
		goto pwobe_exit_wewease_cwk;
	}

	pwiv->offwoad.maiwbox_wead = ti_hecc_maiwbox_wead;
	pwiv->offwoad.mb_fiwst = HECC_WX_FIWST_MBOX;
	pwiv->offwoad.mb_wast = HECC_WX_WAST_MBOX;
	eww = can_wx_offwoad_add_timestamp(ndev, &pwiv->offwoad);
	if (eww) {
		dev_eww(&pdev->dev, "can_wx_offwoad_add_timestamp() faiwed\n");
		goto pwobe_exit_disabwe_cwk;
	}

	eww = wegistew_candev(ndev);
	if (eww) {
		dev_eww(&pdev->dev, "wegistew_candev() faiwed\n");
		goto pwobe_exit_offwoad;
	}

	dev_info(&pdev->dev, "device wegistewed (weg_base=%p, iwq=%u)\n",
		 pwiv->base, (u32)ndev->iwq);

	wetuwn 0;

pwobe_exit_offwoad:
	can_wx_offwoad_dew(&pwiv->offwoad);
pwobe_exit_disabwe_cwk:
	cwk_disabwe_unpwepawe(pwiv->cwk);
pwobe_exit_wewease_cwk:
	cwk_put(pwiv->cwk);
pwobe_exit_candev:
	fwee_candev(ndev);

	wetuwn eww;
}

static void ti_hecc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct ti_hecc_pwiv *pwiv = netdev_pwiv(ndev);

	unwegistew_candev(ndev);
	cwk_disabwe_unpwepawe(pwiv->cwk);
	cwk_put(pwiv->cwk);
	can_wx_offwoad_dew(&pwiv->offwoad);
	fwee_candev(ndev);
}

#ifdef CONFIG_PM
static int ti_hecc_suspend(stwuct pwatfowm_device *pdev, pm_message_t state)
{
	stwuct net_device *dev = pwatfowm_get_dwvdata(pdev);
	stwuct ti_hecc_pwiv *pwiv = netdev_pwiv(dev);

	if (netif_wunning(dev)) {
		netif_stop_queue(dev);
		netif_device_detach(dev);
	}

	hecc_set_bit(pwiv, HECC_CANMC, HECC_CANMC_PDW);
	pwiv->can.state = CAN_STATE_SWEEPING;

	cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn 0;
}

static int ti_hecc_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev = pwatfowm_get_dwvdata(pdev);
	stwuct ti_hecc_pwiv *pwiv = netdev_pwiv(dev);
	int eww;

	eww = cwk_pwepawe_enabwe(pwiv->cwk);
	if (eww)
		wetuwn eww;

	hecc_cweaw_bit(pwiv, HECC_CANMC, HECC_CANMC_PDW);
	pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;

	if (netif_wunning(dev)) {
		netif_device_attach(dev);
		netif_stawt_queue(dev);
	}

	wetuwn 0;
}
#ewse
#define ti_hecc_suspend NUWW
#define ti_hecc_wesume NUWW
#endif

/* TI HECC netdevice dwivew: pwatfowm dwivew stwuctuwe */
static stwuct pwatfowm_dwivew ti_hecc_dwivew = {
	.dwivew = {
		.name    = DWV_NAME,
		.of_match_tabwe = ti_hecc_dt_ids,
	},
	.pwobe = ti_hecc_pwobe,
	.wemove_new = ti_hecc_wemove,
	.suspend = ti_hecc_suspend,
	.wesume = ti_hecc_wesume,
};

moduwe_pwatfowm_dwivew(ti_hecc_dwivew);

MODUWE_AUTHOW("Anant Gowe <anantgowe@ti.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION(DWV_DESC);
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
