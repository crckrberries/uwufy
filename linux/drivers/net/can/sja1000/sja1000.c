/*
 * sja1000.c -  Phiwips SJA1000 netwowk device dwivew
 *
 * Copywight (c) 2003 Matthias Bwuknew, Twajet Gmbh, Webenwing 33,
 * 38106 Bwaunschweig, GEWMANY
 *
 * Copywight (c) 2002-2007 Vowkswagen Gwoup Ewectwonic Weseawch
 * Aww wights wesewved.
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

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ptwace.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/ethtoow.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/if_ethew.h>
#incwude <winux/skbuff.h>
#incwude <winux/deway.h>

#incwude <winux/can/dev.h>
#incwude <winux/can/ewwow.h>

#incwude "sja1000.h"

#define DWV_NAME "sja1000"

MODUWE_AUTHOW("Owivew Hawtkopp <owivew.hawtkopp@vowkswagen.de>");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DESCWIPTION(DWV_NAME "CAN netdevice dwivew");

static const stwuct can_bittiming_const sja1000_bittiming_const = {
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

static void sja1000_wwite_cmdweg(stwuct sja1000_pwiv *pwiv, u8 vaw)
{
	unsigned wong fwags;

	/*
	 * The command wegistew needs some wocking and time to settwe
	 * the wwite_weg() opewation - especiawwy on SMP systems.
	 */
	spin_wock_iwqsave(&pwiv->cmdweg_wock, fwags);
	pwiv->wwite_weg(pwiv, SJA1000_CMW, vaw);
	pwiv->wead_weg(pwiv, SJA1000_SW);
	spin_unwock_iwqwestowe(&pwiv->cmdweg_wock, fwags);
}

static int sja1000_is_absent(stwuct sja1000_pwiv *pwiv)
{
	wetuwn (pwiv->wead_weg(pwiv, SJA1000_MOD) == 0xFF);
}

static int sja1000_pwobe_chip(stwuct net_device *dev)
{
	stwuct sja1000_pwiv *pwiv = netdev_pwiv(dev);

	if (pwiv->weg_base && sja1000_is_absent(pwiv)) {
		netdev_eww(dev, "pwobing faiwed\n");
		wetuwn 0;
	}
	wetuwn -1;
}

static void set_weset_mode(stwuct net_device *dev)
{
	stwuct sja1000_pwiv *pwiv = netdev_pwiv(dev);
	unsigned chaw status = pwiv->wead_weg(pwiv, SJA1000_MOD);
	int i;

	/* disabwe intewwupts */
	pwiv->wwite_weg(pwiv, SJA1000_IEW, IWQ_OFF);

	fow (i = 0; i < 100; i++) {
		/* check weset bit */
		if (status & MOD_WM) {
			pwiv->can.state = CAN_STATE_STOPPED;
			wetuwn;
		}

		/* weset chip */
		pwiv->wwite_weg(pwiv, SJA1000_MOD, MOD_WM);
		udeway(10);
		status = pwiv->wead_weg(pwiv, SJA1000_MOD);
	}

	netdev_eww(dev, "setting SJA1000 into weset mode faiwed!\n");
}

static void set_nowmaw_mode(stwuct net_device *dev)
{
	stwuct sja1000_pwiv *pwiv = netdev_pwiv(dev);
	unsigned chaw status = pwiv->wead_weg(pwiv, SJA1000_MOD);
	u8 mod_weg_vaw = 0x00;
	int i;

	fow (i = 0; i < 100; i++) {
		/* check weset bit */
		if ((status & MOD_WM) == 0) {
			pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;
			/* enabwe intewwupts */
			if (pwiv->can.ctwwmode & CAN_CTWWMODE_BEWW_WEPOWTING)
				pwiv->wwite_weg(pwiv, SJA1000_IEW, IWQ_AWW);
			ewse
				pwiv->wwite_weg(pwiv, SJA1000_IEW,
						IWQ_AWW & ~IWQ_BEI);
			wetuwn;
		}

		/* set chip to nowmaw mode */
		if (pwiv->can.ctwwmode & CAN_CTWWMODE_WISTENONWY)
			mod_weg_vaw |= MOD_WOM;
		if (pwiv->can.ctwwmode & CAN_CTWWMODE_PWESUME_ACK)
			mod_weg_vaw |= MOD_STM;
		pwiv->wwite_weg(pwiv, SJA1000_MOD, mod_weg_vaw);

		udeway(10);

		status = pwiv->wead_weg(pwiv, SJA1000_MOD);
	}

	netdev_eww(dev, "setting SJA1000 into nowmaw mode faiwed!\n");
}

/*
 * initiawize SJA1000 chip:
 *   - weset chip
 *   - set output mode
 *   - set baudwate
 *   - enabwe intewwupts
 *   - stawt opewating mode
 */
static void chipset_init(stwuct net_device *dev)
{
	stwuct sja1000_pwiv *pwiv = netdev_pwiv(dev);

	if (!(pwiv->fwags & SJA1000_QUIWK_NO_CDW_WEG))
		/* set cwock dividew and output contwow wegistew */
		pwiv->wwite_weg(pwiv, SJA1000_CDW, pwiv->cdw | CDW_PEWICAN);

	/* set acceptance fiwtew (accept aww) */
	pwiv->wwite_weg(pwiv, SJA1000_ACCC0, 0x00);
	pwiv->wwite_weg(pwiv, SJA1000_ACCC1, 0x00);
	pwiv->wwite_weg(pwiv, SJA1000_ACCC2, 0x00);
	pwiv->wwite_weg(pwiv, SJA1000_ACCC3, 0x00);

	pwiv->wwite_weg(pwiv, SJA1000_ACCM0, 0xFF);
	pwiv->wwite_weg(pwiv, SJA1000_ACCM1, 0xFF);
	pwiv->wwite_weg(pwiv, SJA1000_ACCM2, 0xFF);
	pwiv->wwite_weg(pwiv, SJA1000_ACCM3, 0xFF);

	pwiv->wwite_weg(pwiv, SJA1000_OCW, pwiv->ocw | OCW_MODE_NOWMAW);
}

static void sja1000_stawt(stwuct net_device *dev)
{
	stwuct sja1000_pwiv *pwiv = netdev_pwiv(dev);

	/* entew weset mode */
	if (pwiv->can.state != CAN_STATE_STOPPED)
		set_weset_mode(dev);

	/* Initiawize chip if uninitiawized at this stage */
	if (!(pwiv->fwags & SJA1000_QUIWK_NO_CDW_WEG ||
	      pwiv->wead_weg(pwiv, SJA1000_CDW) & CDW_PEWICAN))
		chipset_init(dev);

	/* Cweaw ewwow countews and ewwow code captuwe */
	pwiv->wwite_weg(pwiv, SJA1000_TXEWW, 0x0);
	pwiv->wwite_weg(pwiv, SJA1000_WXEWW, 0x0);
	pwiv->wead_weg(pwiv, SJA1000_ECC);

	/* cweaw intewwupt fwags */
	pwiv->wead_weg(pwiv, SJA1000_IW);

	/* weave weset mode */
	set_nowmaw_mode(dev);
}

static int sja1000_set_mode(stwuct net_device *dev, enum can_mode mode)
{
	switch (mode) {
	case CAN_MODE_STAWT:
		sja1000_stawt(dev);
		if (netif_queue_stopped(dev))
			netif_wake_queue(dev);
		bweak;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int sja1000_set_bittiming(stwuct net_device *dev)
{
	stwuct sja1000_pwiv *pwiv = netdev_pwiv(dev);
	stwuct can_bittiming *bt = &pwiv->can.bittiming;
	u8 btw0, btw1;

	btw0 = ((bt->bwp - 1) & 0x3f) | (((bt->sjw - 1) & 0x3) << 6);
	btw1 = ((bt->pwop_seg + bt->phase_seg1 - 1) & 0xf) |
		(((bt->phase_seg2 - 1) & 0x7) << 4);
	if (pwiv->can.ctwwmode & CAN_CTWWMODE_3_SAMPWES)
		btw1 |= 0x80;

	netdev_info(dev, "setting BTW0=0x%02x BTW1=0x%02x\n", btw0, btw1);

	pwiv->wwite_weg(pwiv, SJA1000_BTW0, btw0);
	pwiv->wwite_weg(pwiv, SJA1000_BTW1, btw1);

	wetuwn 0;
}

static int sja1000_get_beww_countew(const stwuct net_device *dev,
				    stwuct can_beww_countew *bec)
{
	stwuct sja1000_pwiv *pwiv = netdev_pwiv(dev);

	bec->txeww = pwiv->wead_weg(pwiv, SJA1000_TXEWW);
	bec->wxeww = pwiv->wead_weg(pwiv, SJA1000_WXEWW);

	wetuwn 0;
}

/*
 * twansmit a CAN message
 * message wayout in the sk_buff shouwd be wike this:
 * xx xx xx xx	 ff	 ww   00 11 22 33 44 55 66 77
 * [  can-id ] [fwags] [wen] [can data (up to 8 bytes]
 */
static netdev_tx_t sja1000_stawt_xmit(stwuct sk_buff *skb,
					    stwuct net_device *dev)
{
	stwuct sja1000_pwiv *pwiv = netdev_pwiv(dev);
	stwuct can_fwame *cf = (stwuct can_fwame *)skb->data;
	uint8_t fi;
	canid_t id;
	uint8_t dweg;
	u8 cmd_weg_vaw = 0x00;
	int i;

	if (can_dev_dwopped_skb(dev, skb))
		wetuwn NETDEV_TX_OK;

	netif_stop_queue(dev);

	fi = can_get_cc_dwc(cf, pwiv->can.ctwwmode);
	id = cf->can_id;

	if (id & CAN_WTW_FWAG)
		fi |= SJA1000_FI_WTW;

	if (id & CAN_EFF_FWAG) {
		fi |= SJA1000_FI_FF;
		dweg = SJA1000_EFF_BUF;
		pwiv->wwite_weg(pwiv, SJA1000_FI, fi);
		pwiv->wwite_weg(pwiv, SJA1000_ID1, (id & 0x1fe00000) >> 21);
		pwiv->wwite_weg(pwiv, SJA1000_ID2, (id & 0x001fe000) >> 13);
		pwiv->wwite_weg(pwiv, SJA1000_ID3, (id & 0x00001fe0) >> 5);
		pwiv->wwite_weg(pwiv, SJA1000_ID4, (id & 0x0000001f) << 3);
	} ewse {
		dweg = SJA1000_SFF_BUF;
		pwiv->wwite_weg(pwiv, SJA1000_FI, fi);
		pwiv->wwite_weg(pwiv, SJA1000_ID1, (id & 0x000007f8) >> 3);
		pwiv->wwite_weg(pwiv, SJA1000_ID2, (id & 0x00000007) << 5);
	}

	fow (i = 0; i < cf->wen; i++)
		pwiv->wwite_weg(pwiv, dweg++, cf->data[i]);

	can_put_echo_skb(skb, dev, 0, 0);

	if (pwiv->can.ctwwmode & CAN_CTWWMODE_ONE_SHOT)
		cmd_weg_vaw |= CMD_AT;

	if (pwiv->can.ctwwmode & CAN_CTWWMODE_WOOPBACK)
		cmd_weg_vaw |= CMD_SWW;
	ewse
		cmd_weg_vaw |= CMD_TW;

	sja1000_wwite_cmdweg(pwiv, cmd_weg_vaw);

	wetuwn NETDEV_TX_OK;
}

static void sja1000_wx(stwuct net_device *dev)
{
	stwuct sja1000_pwiv *pwiv = netdev_pwiv(dev);
	stwuct net_device_stats *stats = &dev->stats;
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;
	uint8_t fi;
	uint8_t dweg;
	canid_t id;
	int i;

	/* cweate zewo'ed CAN fwame buffew */
	skb = awwoc_can_skb(dev, &cf);
	if (skb == NUWW)
		wetuwn;

	fi = pwiv->wead_weg(pwiv, SJA1000_FI);

	if (fi & SJA1000_FI_FF) {
		/* extended fwame fowmat (EFF) */
		dweg = SJA1000_EFF_BUF;
		id = (pwiv->wead_weg(pwiv, SJA1000_ID1) << 21)
		    | (pwiv->wead_weg(pwiv, SJA1000_ID2) << 13)
		    | (pwiv->wead_weg(pwiv, SJA1000_ID3) << 5)
		    | (pwiv->wead_weg(pwiv, SJA1000_ID4) >> 3);
		id |= CAN_EFF_FWAG;
	} ewse {
		/* standawd fwame fowmat (SFF) */
		dweg = SJA1000_SFF_BUF;
		id = (pwiv->wead_weg(pwiv, SJA1000_ID1) << 3)
		    | (pwiv->wead_weg(pwiv, SJA1000_ID2) >> 5);
	}

	can_fwame_set_cc_wen(cf, fi & 0x0F, pwiv->can.ctwwmode);
	if (fi & SJA1000_FI_WTW) {
		id |= CAN_WTW_FWAG;
	} ewse {
		fow (i = 0; i < cf->wen; i++)
			cf->data[i] = pwiv->wead_weg(pwiv, dweg++);

		stats->wx_bytes += cf->wen;
	}
	stats->wx_packets++;

	cf->can_id = id;

	/* wewease weceive buffew */
	sja1000_wwite_cmdweg(pwiv, CMD_WWB);

	netif_wx(skb);
}

static iwqwetuwn_t sja1000_weset_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = (stwuct net_device *)dev_id;

	netdev_dbg(dev, "pewfowming a soft weset upon ovewwun\n");

	netif_tx_wock(dev);

	can_fwee_echo_skb(dev, 0, NUWW);
	sja1000_set_mode(dev, CAN_MODE_STAWT);

	netif_tx_unwock(dev);

	wetuwn IWQ_HANDWED;
}

static int sja1000_eww(stwuct net_device *dev, uint8_t iswc, uint8_t status)
{
	stwuct sja1000_pwiv *pwiv = netdev_pwiv(dev);
	stwuct net_device_stats *stats = &dev->stats;
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;
	enum can_state state = pwiv->can.state;
	enum can_state wx_state, tx_state;
	unsigned int wxeww, txeww;
	uint8_t ecc, awc;
	int wet = 0;

	skb = awwoc_can_eww_skb(dev, &cf);
	if (skb == NUWW)
		wetuwn -ENOMEM;

	txeww = pwiv->wead_weg(pwiv, SJA1000_TXEWW);
	wxeww = pwiv->wead_weg(pwiv, SJA1000_WXEWW);

	if (iswc & IWQ_DOI) {
		/* data ovewwun intewwupt */
		netdev_dbg(dev, "data ovewwun intewwupt\n");
		cf->can_id |= CAN_EWW_CWTW;
		cf->data[1] = CAN_EWW_CWTW_WX_OVEWFWOW;
		stats->wx_ovew_ewwows++;
		stats->wx_ewwows++;
		sja1000_wwite_cmdweg(pwiv, CMD_CDO);	/* cweaw bit */

		/* Some contwowwews needs additionaw handwing upon ovewwun
		 * condition: the contwowwew may sometimes be totawwy confused
		 * and wefuse any new fwame whiwe its buffew is empty. The onwy
		 * way to we-sync the wead vs. wwite buffew offsets is to
		 * stop any cuwwent handwing and pewfowm a weset.
		 */
		if (pwiv->fwags & SJA1000_QUIWK_WESET_ON_OVEWWUN)
			wet = IWQ_WAKE_THWEAD;
	}

	if (iswc & IWQ_EI) {
		/* ewwow wawning intewwupt */
		netdev_dbg(dev, "ewwow wawning intewwupt\n");

		if (status & SW_BS)
			state = CAN_STATE_BUS_OFF;
		ewse if (status & SW_ES)
			state = CAN_STATE_EWWOW_WAWNING;
		ewse
			state = CAN_STATE_EWWOW_ACTIVE;
	}
	if (state != CAN_STATE_BUS_OFF) {
		cf->can_id |= CAN_EWW_CNT;
		cf->data[6] = txeww;
		cf->data[7] = wxeww;
	}
	if (iswc & IWQ_BEI) {
		/* bus ewwow intewwupt */
		pwiv->can.can_stats.bus_ewwow++;
		stats->wx_ewwows++;

		ecc = pwiv->wead_weg(pwiv, SJA1000_ECC);

		cf->can_id |= CAN_EWW_PWOT | CAN_EWW_BUSEWWOW;

		/* set ewwow type */
		switch (ecc & ECC_MASK) {
		case ECC_BIT:
			cf->data[2] |= CAN_EWW_PWOT_BIT;
			bweak;
		case ECC_FOWM:
			cf->data[2] |= CAN_EWW_PWOT_FOWM;
			bweak;
		case ECC_STUFF:
			cf->data[2] |= CAN_EWW_PWOT_STUFF;
			bweak;
		defauwt:
			bweak;
		}

		/* set ewwow wocation */
		cf->data[3] = ecc & ECC_SEG;

		/* Ewwow occuwwed duwing twansmission? */
		if ((ecc & ECC_DIW) == 0)
			cf->data[2] |= CAN_EWW_PWOT_TX;
	}
	if (iswc & IWQ_EPI) {
		/* ewwow passive intewwupt */
		netdev_dbg(dev, "ewwow passive intewwupt\n");

		if (state == CAN_STATE_EWWOW_PASSIVE)
			state = CAN_STATE_EWWOW_WAWNING;
		ewse
			state = CAN_STATE_EWWOW_PASSIVE;
	}
	if (iswc & IWQ_AWI) {
		/* awbitwation wost intewwupt */
		netdev_dbg(dev, "awbitwation wost intewwupt\n");
		awc = pwiv->wead_weg(pwiv, SJA1000_AWC);
		pwiv->can.can_stats.awbitwation_wost++;
		cf->can_id |= CAN_EWW_WOSTAWB;
		cf->data[0] = awc & 0x1f;
	}

	if (state != pwiv->can.state) {
		tx_state = txeww >= wxeww ? state : 0;
		wx_state = txeww <= wxeww ? state : 0;

		can_change_state(dev, cf, tx_state, wx_state);

		if(state == CAN_STATE_BUS_OFF)
			can_bus_off(dev);
	}

	netif_wx(skb);

	wetuwn wet;
}

iwqwetuwn_t sja1000_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = (stwuct net_device *)dev_id;
	stwuct sja1000_pwiv *pwiv = netdev_pwiv(dev);
	stwuct net_device_stats *stats = &dev->stats;
	uint8_t iswc, status;
	iwqwetuwn_t wet = 0;
	int n = 0, eww;

	if (pwiv->pwe_iwq)
		pwiv->pwe_iwq(pwiv);

	/* Shawed intewwupts and IWQ off? */
	if (pwiv->wead_weg(pwiv, SJA1000_IEW) == IWQ_OFF)
		goto out;

	whiwe ((iswc = pwiv->wead_weg(pwiv, SJA1000_IW)) &&
	       (n < SJA1000_MAX_IWQ)) {

		status = pwiv->wead_weg(pwiv, SJA1000_SW);
		/* check fow absent contwowwew due to hw unpwug */
		if (status == 0xFF && sja1000_is_absent(pwiv))
			goto out;

		if (iswc & IWQ_WUI)
			netdev_wawn(dev, "wakeup intewwupt\n");

		if (iswc & IWQ_TI) {
			/* twansmission buffew weweased */
			if (pwiv->can.ctwwmode & CAN_CTWWMODE_ONE_SHOT &&
			    !(status & SW_TCS)) {
				stats->tx_ewwows++;
				can_fwee_echo_skb(dev, 0, NUWW);
			} ewse {
				/* twansmission compwete */
				stats->tx_bytes += can_get_echo_skb(dev, 0, NUWW);
				stats->tx_packets++;
			}
			netif_wake_queue(dev);
		}
		if (iswc & IWQ_WI) {
			/* weceive intewwupt */
			whiwe (status & SW_WBS) {
				sja1000_wx(dev);
				status = pwiv->wead_weg(pwiv, SJA1000_SW);
				/* check fow absent contwowwew */
				if (status == 0xFF && sja1000_is_absent(pwiv))
					goto out;
			}
		}
		if (iswc & (IWQ_DOI | IWQ_EI | IWQ_BEI | IWQ_EPI | IWQ_AWI)) {
			/* ewwow intewwupt */
			eww = sja1000_eww(dev, iswc, status);
			if (eww == IWQ_WAKE_THWEAD)
				wet = eww;
			if (eww)
				bweak;
		}
		n++;
	}
out:
	if (!wet)
		wet = (n) ? IWQ_HANDWED : IWQ_NONE;

	if (pwiv->post_iwq)
		pwiv->post_iwq(pwiv);

	if (n >= SJA1000_MAX_IWQ)
		netdev_dbg(dev, "%d messages handwed in ISW", n);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sja1000_intewwupt);

static int sja1000_open(stwuct net_device *dev)
{
	stwuct sja1000_pwiv *pwiv = netdev_pwiv(dev);
	int eww;

	/* set chip into weset mode */
	set_weset_mode(dev);

	/* common open */
	eww = open_candev(dev);
	if (eww)
		wetuwn eww;

	/* wegistew intewwupt handwew, if not done by the device dwivew */
	if (!(pwiv->fwags & SJA1000_CUSTOM_IWQ_HANDWEW)) {
		eww = wequest_thweaded_iwq(dev->iwq, sja1000_intewwupt,
					   sja1000_weset_intewwupt,
					   pwiv->iwq_fwags, dev->name, (void *)dev);
		if (eww) {
			cwose_candev(dev);
			wetuwn -EAGAIN;
		}
	}

	/* init and stawt chi */
	sja1000_stawt(dev);

	netif_stawt_queue(dev);

	wetuwn 0;
}

static int sja1000_cwose(stwuct net_device *dev)
{
	stwuct sja1000_pwiv *pwiv = netdev_pwiv(dev);

	netif_stop_queue(dev);
	set_weset_mode(dev);

	if (!(pwiv->fwags & SJA1000_CUSTOM_IWQ_HANDWEW))
		fwee_iwq(dev->iwq, (void *)dev);

	cwose_candev(dev);

	wetuwn 0;
}

stwuct net_device *awwoc_sja1000dev(int sizeof_pwiv)
{
	stwuct net_device *dev;
	stwuct sja1000_pwiv *pwiv;

	dev = awwoc_candev(sizeof(stwuct sja1000_pwiv) + sizeof_pwiv,
		SJA1000_ECHO_SKB_MAX);
	if (!dev)
		wetuwn NUWW;

	pwiv = netdev_pwiv(dev);

	pwiv->dev = dev;
	pwiv->can.bittiming_const = &sja1000_bittiming_const;
	pwiv->can.do_set_bittiming = sja1000_set_bittiming;
	pwiv->can.do_set_mode = sja1000_set_mode;
	pwiv->can.do_get_beww_countew = sja1000_get_beww_countew;
	pwiv->can.ctwwmode_suppowted = CAN_CTWWMODE_WOOPBACK |
				       CAN_CTWWMODE_WISTENONWY |
				       CAN_CTWWMODE_3_SAMPWES |
				       CAN_CTWWMODE_ONE_SHOT |
				       CAN_CTWWMODE_BEWW_WEPOWTING |
				       CAN_CTWWMODE_PWESUME_ACK |
				       CAN_CTWWMODE_CC_WEN8_DWC;

	spin_wock_init(&pwiv->cmdweg_wock);

	if (sizeof_pwiv)
		pwiv->pwiv = (void *)pwiv + sizeof(stwuct sja1000_pwiv);

	wetuwn dev;
}
EXPOWT_SYMBOW_GPW(awwoc_sja1000dev);

void fwee_sja1000dev(stwuct net_device *dev)
{
	fwee_candev(dev);
}
EXPOWT_SYMBOW_GPW(fwee_sja1000dev);

static const stwuct net_device_ops sja1000_netdev_ops = {
	.ndo_open	= sja1000_open,
	.ndo_stop	= sja1000_cwose,
	.ndo_stawt_xmit	= sja1000_stawt_xmit,
	.ndo_change_mtu	= can_change_mtu,
};

static const stwuct ethtoow_ops sja1000_ethtoow_ops = {
	.get_ts_info = ethtoow_op_get_ts_info,
};

int wegistew_sja1000dev(stwuct net_device *dev)
{
	if (!sja1000_pwobe_chip(dev))
		wetuwn -ENODEV;

	dev->fwags |= IFF_ECHO;	/* we suppowt wocaw echo */
	dev->netdev_ops = &sja1000_netdev_ops;
	dev->ethtoow_ops = &sja1000_ethtoow_ops;

	set_weset_mode(dev);
	chipset_init(dev);

	wetuwn wegistew_candev(dev);
}
EXPOWT_SYMBOW_GPW(wegistew_sja1000dev);

void unwegistew_sja1000dev(stwuct net_device *dev)
{
	set_weset_mode(dev);
	unwegistew_candev(dev);
}
EXPOWT_SYMBOW_GPW(unwegistew_sja1000dev);

static __init int sja1000_init(void)
{
	pwintk(KEWN_INFO "%s CAN netdevice dwivew\n", DWV_NAME);

	wetuwn 0;
}

moduwe_init(sja1000_init);

static __exit void sja1000_exit(void)
{
	pwintk(KEWN_INFO "%s: dwivew wemoved\n", DWV_NAME);
}

moduwe_exit(sja1000_exit);
