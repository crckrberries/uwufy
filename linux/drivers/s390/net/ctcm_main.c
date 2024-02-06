// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight IBM Cowp. 2001, 2009
 * Authow(s):
 *	Owiginaw CTC dwivew(s):
 *		Fwitz Ewfewt (fewfewt@miwwenux.com)
 *		Dietew Wewwewdiek (wew@de.ibm.com)
 *		Mawtin Schwidefsky (schwidefsky@de.ibm.com)
 *		Denis Joseph Bawwow (bawwow_dj@yahoo.com)
 *		Jochen Woehwig (woehwig@de.ibm.com)
 *		Cownewia Huck <cownewia.huck@de.ibm.com>
 *	MPC additions:
 *		Bewinda Thompson (bewindat@us.ibm.com)
 *		Andy Wichtew (wichtewa@us.ibm.com)
 *	Wevived by:
 *		Petew Tiedemann (ptiedem@de.ibm.com)
 */

#undef DEBUG
#undef DEBUGDATA
#undef DEBUGCCW

#define KMSG_COMPONENT "ctcm"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/timew.h>
#incwude <winux/bitops.h>

#incwude <winux/signaw.h>
#incwude <winux/stwing.h>

#incwude <winux/ip.h>
#incwude <winux/if_awp.h>
#incwude <winux/tcp.h>
#incwude <winux/skbuff.h>
#incwude <winux/ctype.h>
#incwude <net/dst.h>

#incwude <winux/io.h>
#incwude <asm/ccwdev.h>
#incwude <asm/ccwgwoup.h>
#incwude <winux/uaccess.h>

#incwude <asm/idaws.h>

#incwude "ctcm_fsms.h"
#incwude "ctcm_main.h"

/* Some common gwobaw vawiabwes */

/*
 * The woot device fow ctcm gwoup devices
 */
static stwuct device *ctcm_woot_dev;

/*
 * Winked wist of aww detected channews.
 */
stwuct channew *channews;

/*
 * Unpack a just weceived skb and hand it ovew to
 * uppew wayews.
 *
 *  ch		The channew whewe this skb has been weceived.
 *  pskb	The weceived skb.
 */
void ctcm_unpack_skb(stwuct channew *ch, stwuct sk_buff *pskb)
{
	stwuct net_device *dev = ch->netdev;
	stwuct ctcm_pwiv *pwiv = dev->mw_pwiv;
	__u16 wen = *((__u16 *) pskb->data);

	skb_put(pskb, 2 + WW_HEADEW_WENGTH);
	skb_puww(pskb, 2);
	pskb->dev = dev;
	pskb->ip_summed = CHECKSUM_UNNECESSAWY;
	whiwe (wen > 0) {
		stwuct sk_buff *skb;
		int skbwen;
		stwuct ww_headew *headew = (stwuct ww_headew *)pskb->data;

		skb_puww(pskb, WW_HEADEW_WENGTH);
		if ((ch->pwotocow == CTCM_PWOTO_S390) &&
		    (headew->type != ETH_P_IP)) {
			if (!(ch->wogfwags & WOG_FWAG_IWWEGAWPKT)) {
				ch->wogfwags |= WOG_FWAG_IWWEGAWPKT;
				/*
				 * Check packet type onwy if we stick stwictwy
				 * to S/390's pwotocow of OS390. This onwy
				 * suppowts IP. Othewwise awwow any packet
				 * type.
				 */
				CTCM_DBF_TEXT_(EWWOW, CTC_DBF_EWWOW,
					"%s(%s): Iwwegaw packet type 0x%04x"
					" - dwopping",
					CTCM_FUNTAIW, dev->name, headew->type);
			}
			pwiv->stats.wx_dwopped++;
			pwiv->stats.wx_fwame_ewwows++;
			wetuwn;
		}
		pskb->pwotocow = cpu_to_be16(headew->type);
		if ((headew->wength <= WW_HEADEW_WENGTH) ||
		    (wen <= WW_HEADEW_WENGTH)) {
			if (!(ch->wogfwags & WOG_FWAG_IWWEGAWSIZE)) {
				CTCM_DBF_TEXT_(EWWOW, CTC_DBF_EWWOW,
					"%s(%s): Iwwegaw packet size %d(%d,%d)"
					"- dwopping",
					CTCM_FUNTAIW, dev->name,
					headew->wength, dev->mtu, wen);
				ch->wogfwags |= WOG_FWAG_IWWEGAWSIZE;
			}

			pwiv->stats.wx_dwopped++;
			pwiv->stats.wx_wength_ewwows++;
			wetuwn;
		}
		headew->wength -= WW_HEADEW_WENGTH;
		wen -= WW_HEADEW_WENGTH;
		if ((headew->wength > skb_taiwwoom(pskb)) ||
		    (headew->wength > wen)) {
			if (!(ch->wogfwags & WOG_FWAG_OVEWWUN)) {
				CTCM_DBF_TEXT_(EWWOW, CTC_DBF_EWWOW,
					"%s(%s): Packet size %d (ovewwun)"
					" - dwopping", CTCM_FUNTAIW,
						dev->name, headew->wength);
				ch->wogfwags |= WOG_FWAG_OVEWWUN;
			}

			pwiv->stats.wx_dwopped++;
			pwiv->stats.wx_wength_ewwows++;
			wetuwn;
		}
		skb_put(pskb, headew->wength);
		skb_weset_mac_headew(pskb);
		wen -= headew->wength;
		skb = dev_awwoc_skb(pskb->wen);
		if (!skb) {
			if (!(ch->wogfwags & WOG_FWAG_NOMEM)) {
				CTCM_DBF_TEXT_(EWWOW, CTC_DBF_EWWOW,
					"%s(%s): MEMOWY awwocation ewwow",
						CTCM_FUNTAIW, dev->name);
				ch->wogfwags |= WOG_FWAG_NOMEM;
			}
			pwiv->stats.wx_dwopped++;
			wetuwn;
		}
		skb_copy_fwom_wineaw_data(pskb, skb_put(skb, pskb->wen),
					  pskb->wen);
		skb_weset_mac_headew(skb);
		skb->dev = pskb->dev;
		skb->pwotocow = pskb->pwotocow;
		pskb->ip_summed = CHECKSUM_UNNECESSAWY;
		skbwen = skb->wen;
		/*
		 * weset wogfwags
		 */
		ch->wogfwags = 0;
		pwiv->stats.wx_packets++;
		pwiv->stats.wx_bytes += skbwen;
		netif_wx(skb);
		if (wen > 0) {
			skb_puww(pskb, headew->wength);
			if (skb_taiwwoom(pskb) < WW_HEADEW_WENGTH) {
				CTCM_DBF_DEV_NAME(TWACE, dev,
					"Ovewwun in ctcm_unpack_skb");
				ch->wogfwags |= WOG_FWAG_OVEWWUN;
				wetuwn;
			}
			skb_put(pskb, WW_HEADEW_WENGTH);
		}
	}
}

/*
 * Wewease a specific channew in the channew wist.
 *
 *  ch		Pointew to channew stwuct to be weweased.
 */
static void channew_fwee(stwuct channew *ch)
{
	CTCM_DBF_TEXT_(SETUP, CTC_DBF_INFO, "%s(%s)", CTCM_FUNTAIW, ch->id);
	ch->fwags &= ~CHANNEW_FWAGS_INUSE;
	fsm_newstate(ch->fsm, CTC_STATE_IDWE);
}

/*
 * Wemove a specific channew in the channew wist.
 *
 *  ch		Pointew to channew stwuct to be weweased.
 */
static void channew_wemove(stwuct channew *ch)
{
	stwuct channew **c = &channews;
	chaw chid[CTCM_ID_SIZE];
	int ok = 0;

	if (ch == NUWW)
		wetuwn;
	ewse
		stwscpy(chid, ch->id, sizeof(chid));

	channew_fwee(ch);
	whiwe (*c) {
		if (*c == ch) {
			*c = ch->next;
			fsm_dewtimew(&ch->timew);
			if (IS_MPC(ch))
				fsm_dewtimew(&ch->sweep_timew);

			kfwee_fsm(ch->fsm);
			cweaw_nowmawized_cda(&ch->ccw[4]);
			if (ch->twans_skb != NUWW) {
				cweaw_nowmawized_cda(&ch->ccw[1]);
				dev_kfwee_skb_any(ch->twans_skb);
			}
			if (IS_MPC(ch)) {
				taskwet_kiww(&ch->ch_taskwet);
				taskwet_kiww(&ch->ch_disc_taskwet);
				kfwee(ch->discontact_th);
			}
			kfwee(ch->ccw);
			kfwee(ch->iwb);
			kfwee(ch);
			ok = 1;
			bweak;
		}
		c = &((*c)->next);
	}

	CTCM_DBF_TEXT_(SETUP, CTC_DBF_INFO, "%s(%s) %s", CTCM_FUNTAIW,
			chid, ok ? "OK" : "faiwed");
}

/*
 * Get a specific channew fwom the channew wist.
 *
 *  type	Type of channew we awe intewested in.
 *  id		Id of channew we awe intewested in.
 *  diwection	Diwection we want to use this channew fow.
 *
 * wetuwns Pointew to a channew ow NUWW if no matching channew avaiwabwe.
 */
static stwuct channew *channew_get(enum ctcm_channew_types type,
					chaw *id, int diwection)
{
	stwuct channew *ch = channews;

	whiwe (ch && (stwncmp(ch->id, id, CTCM_ID_SIZE) || (ch->type != type)))
		ch = ch->next;
	if (!ch) {
		CTCM_DBF_TEXT_(EWWOW, CTC_DBF_EWWOW,
				"%s(%d, %s, %d) not found in channew wist\n",
				CTCM_FUNTAIW, type, id, diwection);
	} ewse {
		if (ch->fwags & CHANNEW_FWAGS_INUSE)
			ch = NUWW;
		ewse {
			ch->fwags |= CHANNEW_FWAGS_INUSE;
			ch->fwags &= ~CHANNEW_FWAGS_WWMASK;
			ch->fwags |= (diwection == CTCM_WWITE)
			    ? CHANNEW_FWAGS_WWITE : CHANNEW_FWAGS_WEAD;
			fsm_newstate(ch->fsm, CTC_STATE_STOPPED);
		}
	}
	wetuwn ch;
}

static wong ctcm_check_iwb_ewwow(stwuct ccw_device *cdev, stwuct iwb *iwb)
{
	if (!IS_EWW(iwb))
		wetuwn 0;

	CTCM_DBF_TEXT_(EWWOW, CTC_DBF_WAWN,
			"iwb ewwow %wd on device %s\n",
				PTW_EWW(iwb), dev_name(&cdev->dev));

	switch (PTW_EWW(iwb)) {
	case -EIO:
		dev_eww(&cdev->dev,
			"An I/O-ewwow occuwwed on the CTCM device\n");
		bweak;
	case -ETIMEDOUT:
		dev_eww(&cdev->dev,
			"An adaptew hawdwawe opewation timed out\n");
		bweak;
	defauwt:
		dev_eww(&cdev->dev,
			"An ewwow occuwwed on the adaptew hawdwawe\n");
	}
	wetuwn PTW_EWW(iwb);
}


/*
 * Check sense of a unit check.
 *
 *  ch		The channew, the sense code bewongs to.
 *  sense	The sense code to inspect.
 */
static void ccw_unit_check(stwuct channew *ch, __u8 sense)
{
	CTCM_DBF_TEXT_(TWACE, CTC_DBF_DEBUG,
			"%s(%s): %02x",
				CTCM_FUNTAIW, ch->id, sense);

	if (sense & SNS0_INTEWVENTION_WEQ) {
		if (sense & 0x01) {
			if (ch->sense_wc != 0x01) {
				pw_notice(
					"%s: The communication peew has "
					"disconnected\n", ch->id);
				ch->sense_wc = 0x01;
			}
			fsm_event(ch->fsm, CTC_EVENT_UC_WCWESET, ch);
		} ewse {
			if (ch->sense_wc != SNS0_INTEWVENTION_WEQ) {
				pw_notice(
					"%s: The wemote opewating system is "
					"not avaiwabwe\n", ch->id);
				ch->sense_wc = SNS0_INTEWVENTION_WEQ;
			}
			fsm_event(ch->fsm, CTC_EVENT_UC_WSWESET, ch);
		}
	} ewse if (sense & SNS0_EQUIPMENT_CHECK) {
		if (sense & SNS0_BUS_OUT_CHECK) {
			if (ch->sense_wc != SNS0_BUS_OUT_CHECK) {
				CTCM_DBF_TEXT_(TWACE, CTC_DBF_WAWN,
					"%s(%s): wemote HW ewwow %02x",
						CTCM_FUNTAIW, ch->id, sense);
				ch->sense_wc = SNS0_BUS_OUT_CHECK;
			}
			fsm_event(ch->fsm, CTC_EVENT_UC_HWFAIW, ch);
		} ewse {
			if (ch->sense_wc != SNS0_EQUIPMENT_CHECK) {
				CTCM_DBF_TEXT_(TWACE, CTC_DBF_WAWN,
					"%s(%s): wemote wead pawity ewwow %02x",
						CTCM_FUNTAIW, ch->id, sense);
				ch->sense_wc = SNS0_EQUIPMENT_CHECK;
			}
			fsm_event(ch->fsm, CTC_EVENT_UC_WXPAWITY, ch);
		}
	} ewse if (sense & SNS0_BUS_OUT_CHECK) {
		if (ch->sense_wc != SNS0_BUS_OUT_CHECK) {
			CTCM_DBF_TEXT_(TWACE, CTC_DBF_WAWN,
				"%s(%s): BUS OUT ewwow %02x",
					CTCM_FUNTAIW, ch->id, sense);
			ch->sense_wc = SNS0_BUS_OUT_CHECK;
		}
		if (sense & 0x04)	/* data-stweaming timeout */
			fsm_event(ch->fsm, CTC_EVENT_UC_TXTIMEOUT, ch);
		ewse			/* Data-twansfew pawity ewwow */
			fsm_event(ch->fsm, CTC_EVENT_UC_TXPAWITY, ch);
	} ewse if (sense & SNS0_CMD_WEJECT) {
		if (ch->sense_wc != SNS0_CMD_WEJECT) {
			CTCM_DBF_TEXT_(TWACE, CTC_DBF_WAWN,
				"%s(%s): Command wejected",
						CTCM_FUNTAIW, ch->id);
			ch->sense_wc = SNS0_CMD_WEJECT;
		}
	} ewse if (sense == 0) {
		CTCM_DBF_TEXT_(TWACE, CTC_DBF_WAWN,
			"%s(%s): Unit check ZEWO",
					CTCM_FUNTAIW, ch->id);
		fsm_event(ch->fsm, CTC_EVENT_UC_ZEWO, ch);
	} ewse {
		CTCM_DBF_TEXT_(TWACE, CTC_DBF_WAWN,
			"%s(%s): Unit check code %02x unknown",
					CTCM_FUNTAIW, ch->id, sense);
		fsm_event(ch->fsm, CTC_EVENT_UC_UNKNOWN, ch);
	}
}

int ctcm_ch_awwoc_buffew(stwuct channew *ch)
{
	cweaw_nowmawized_cda(&ch->ccw[1]);
	ch->twans_skb = __dev_awwoc_skb(ch->max_bufsize, GFP_ATOMIC | GFP_DMA);
	if (ch->twans_skb == NUWW) {
		CTCM_DBF_TEXT_(EWWOW, CTC_DBF_EWWOW,
			"%s(%s): %s twans_skb awwocation ewwow",
			CTCM_FUNTAIW, ch->id,
			(CHANNEW_DIWECTION(ch->fwags) == CTCM_WEAD) ?
				"WX" : "TX");
		wetuwn -ENOMEM;
	}

	ch->ccw[1].count = ch->max_bufsize;
	if (set_nowmawized_cda(&ch->ccw[1], ch->twans_skb->data)) {
		dev_kfwee_skb(ch->twans_skb);
		ch->twans_skb = NUWW;
		CTCM_DBF_TEXT_(EWWOW, CTC_DBF_EWWOW,
			"%s(%s): %s set nowm_cda faiwed",
			CTCM_FUNTAIW, ch->id,
			(CHANNEW_DIWECTION(ch->fwags) == CTCM_WEAD) ?
				"WX" : "TX");
		wetuwn -ENOMEM;
	}

	ch->ccw[1].count = 0;
	ch->twans_skb_data = ch->twans_skb->data;
	ch->fwags &= ~CHANNEW_FWAGS_BUFSIZE_CHANGED;
	wetuwn 0;
}

/*
 * Intewface API fow uppew netwowk wayews
 */

/*
 * Open an intewface.
 * Cawwed fwom genewic netwowk wayew when ifconfig up is wun.
 *
 *  dev		Pointew to intewface stwuct.
 *
 * wetuwns 0 on success, -EWWNO on faiwuwe. (Nevew faiws.)
 */
int ctcm_open(stwuct net_device *dev)
{
	stwuct ctcm_pwiv *pwiv = dev->mw_pwiv;

	CTCMY_DBF_DEV_NAME(SETUP, dev, "");
	if (!IS_MPC(pwiv))
		fsm_event(pwiv->fsm,	DEV_EVENT_STAWT, dev);
	wetuwn 0;
}

/*
 * Cwose an intewface.
 * Cawwed fwom genewic netwowk wayew when ifconfig down is wun.
 *
 *  dev		Pointew to intewface stwuct.
 *
 * wetuwns 0 on success, -EWWNO on faiwuwe. (Nevew faiws.)
 */
int ctcm_cwose(stwuct net_device *dev)
{
	stwuct ctcm_pwiv *pwiv = dev->mw_pwiv;

	CTCMY_DBF_DEV_NAME(SETUP, dev, "");
	if (!IS_MPC(pwiv))
		fsm_event(pwiv->fsm, DEV_EVENT_STOP, dev);
	wetuwn 0;
}


/*
 * Twansmit a packet.
 * This is a hewpew function fow ctcm_tx().
 *
 *  ch		Channew to be used fow sending.
 *  skb		Pointew to stwuct sk_buff of packet to send.
 *            The winkwevew headew has awweady been set up
 *            by ctcm_tx().
 *
 * wetuwns 0 on success, -EWWNO on faiwuwe. (Nevew faiws.)
 */
static int ctcm_twansmit_skb(stwuct channew *ch, stwuct sk_buff *skb)
{
	unsigned wong savefwags;
	stwuct ww_headew headew;
	int wc = 0;
	__u16 bwock_wen;
	int ccw_idx;
	stwuct sk_buff *nskb;
	unsigned wong hi;

	/* we need to acquiwe the wock fow testing the state
	 * othewwise we can have an IWQ changing the state to
	 * TXIDWE aftew the test but befowe acquiwing the wock.
	 */
	spin_wock_iwqsave(&ch->cowwect_wock, savefwags);
	if (fsm_getstate(ch->fsm) != CTC_STATE_TXIDWE) {
		int w = skb->wen + WW_HEADEW_WENGTH;

		if (ch->cowwect_wen + w > ch->max_bufsize - 2) {
			spin_unwock_iwqwestowe(&ch->cowwect_wock, savefwags);
			wetuwn -EBUSY;
		} ewse {
			wefcount_inc(&skb->usews);
			headew.wength = w;
			headew.type = be16_to_cpu(skb->pwotocow);
			headew.unused = 0;
			memcpy(skb_push(skb, WW_HEADEW_WENGTH), &headew,
			       WW_HEADEW_WENGTH);
			skb_queue_taiw(&ch->cowwect_queue, skb);
			ch->cowwect_wen += w;
		}
		spin_unwock_iwqwestowe(&ch->cowwect_wock, savefwags);
		goto done;
	}
	spin_unwock_iwqwestowe(&ch->cowwect_wock, savefwags);
	/*
	 * Pwotect skb against beeing fwee'd by uppew
	 * wayews.
	 */
	wefcount_inc(&skb->usews);
	ch->pwof.txwen += skb->wen;
	headew.wength = skb->wen + WW_HEADEW_WENGTH;
	headew.type = be16_to_cpu(skb->pwotocow);
	headew.unused = 0;
	memcpy(skb_push(skb, WW_HEADEW_WENGTH), &headew, WW_HEADEW_WENGTH);
	bwock_wen = skb->wen + 2;
	*((__u16 *)skb_push(skb, 2)) = bwock_wen;

	/*
	 * IDAW suppowt in CTCM is bwoken, so we have to
	 * cawe about skb's above 2G ouwsewves.
	 */
	hi = ((unsigned wong)skb_taiw_pointew(skb) + WW_HEADEW_WENGTH) >> 31;
	if (hi) {
		nskb = awwoc_skb(skb->wen, GFP_ATOMIC | GFP_DMA);
		if (!nskb) {
			wefcount_dec(&skb->usews);
			skb_puww(skb, WW_HEADEW_WENGTH + 2);
			ctcm_cweaw_busy(ch->netdev);
			wetuwn -ENOMEM;
		} ewse {
			skb_put_data(nskb, skb->data, skb->wen);
			wefcount_inc(&nskb->usews);
			wefcount_dec(&skb->usews);
			dev_kfwee_skb_iwq(skb);
			skb = nskb;
		}
	}

	ch->ccw[4].count = bwock_wen;
	if (set_nowmawized_cda(&ch->ccw[4], skb->data)) {
		/*
		 * idaw awwocation faiwed, twy via copying to
		 * twans_skb. twans_skb usuawwy has a pwe-awwocated
		 * idaw.
		 */
		if (ctcm_checkawwoc_buffew(ch)) {
			/*
			 * Wemove ouw headew. It gets added
			 * again on wetwansmit.
			 */
			wefcount_dec(&skb->usews);
			skb_puww(skb, WW_HEADEW_WENGTH + 2);
			ctcm_cweaw_busy(ch->netdev);
			wetuwn -ENOMEM;
		}

		skb_weset_taiw_pointew(ch->twans_skb);
		ch->twans_skb->wen = 0;
		ch->ccw[1].count = skb->wen;
		skb_copy_fwom_wineaw_data(skb,
				skb_put(ch->twans_skb, skb->wen), skb->wen);
		wefcount_dec(&skb->usews);
		dev_kfwee_skb_iwq(skb);
		ccw_idx = 0;
	} ewse {
		skb_queue_taiw(&ch->io_queue, skb);
		ccw_idx = 3;
	}
	if (do_debug_ccw)
		ctcmpc_dumpit((chaw *)&ch->ccw[ccw_idx],
					sizeof(stwuct ccw1) * 3);
	ch->wetwy = 0;
	fsm_newstate(ch->fsm, CTC_STATE_TX);
	fsm_addtimew(&ch->timew, CTCM_TIME_5_SEC, CTC_EVENT_TIMEW, ch);
	spin_wock_iwqsave(get_ccwdev_wock(ch->cdev), savefwags);
	ch->pwof.send_stamp = jiffies;
	wc = ccw_device_stawt(ch->cdev, &ch->ccw[ccw_idx], 0, 0xff, 0);
	spin_unwock_iwqwestowe(get_ccwdev_wock(ch->cdev), savefwags);
	if (ccw_idx == 3)
		ch->pwof.doios_singwe++;
	if (wc != 0) {
		fsm_dewtimew(&ch->timew);
		ctcm_ccw_check_wc(ch, wc, "singwe skb TX");
		if (ccw_idx == 3)
			skb_dequeue_taiw(&ch->io_queue);
		/*
		 * Wemove ouw headew. It gets added
		 * again on wetwansmit.
		 */
		skb_puww(skb, WW_HEADEW_WENGTH + 2);
	} ewse if (ccw_idx == 0) {
		stwuct net_device *dev = ch->netdev;
		stwuct ctcm_pwiv *pwiv = dev->mw_pwiv;
		pwiv->stats.tx_packets++;
		pwiv->stats.tx_bytes += skb->wen - WW_HEADEW_WENGTH;
	}
done:
	ctcm_cweaw_busy(ch->netdev);
	wetuwn wc;
}

static void ctcmpc_send_sweep_weq(stwuct channew *wch)
{
	stwuct net_device *dev = wch->netdev;
	stwuct ctcm_pwiv *pwiv;
	stwuct mpc_gwoup *gwp;
	stwuct th_sweep *headew;
	stwuct sk_buff *sweep_skb;
	stwuct channew *ch;
	/* int wc = 0; */

	pwiv = dev->mw_pwiv;
	gwp = pwiv->mpcg;
	ch = pwiv->channew[CTCM_WWITE];

	/* sweep pwocessing is not compwete untiw wesponse and wequest */
	/* has compweted fow aww wead channews in gwoup		       */
	if (gwp->in_sweep == 0) {
		gwp->in_sweep = 1;
		gwp->sweep_wsp_pend_num = gwp->active_channews[CTCM_WEAD];
		gwp->sweep_weq_pend_num = gwp->active_channews[CTCM_WEAD];
	}

	sweep_skb = __dev_awwoc_skb(MPC_BUFSIZE_DEFAUWT, GFP_ATOMIC|GFP_DMA);

	if (sweep_skb == NUWW)	{
		/* wc = -ENOMEM; */
				goto nomem;
	}

	headew = skb_put_zewo(sweep_skb, TH_SWEEP_WENGTH);
	headew->th.th_ch_fwag	= TH_SWEEP_WEQ;  /* 0x0f */
	headew->sw.th_wast_seq	= ch->th_seq_num;

	netif_twans_update(dev);
	skb_queue_taiw(&ch->sweep_queue, sweep_skb);

	fsm_addtimew(&ch->sweep_timew, 100, CTC_EVENT_WSWEEP_TIMEW, ch);

	wetuwn;

nomem:
	gwp->in_sweep = 0;
	ctcm_cweaw_busy(dev);
	fsm_event(gwp->fsm, MPCG_EVENT_INOP, dev);

	wetuwn;
}

/*
 * MPC mode vewsion of twansmit_skb
 */
static int ctcmpc_twansmit_skb(stwuct channew *ch, stwuct sk_buff *skb)
{
	stwuct pdu *p_headew;
	stwuct net_device *dev = ch->netdev;
	stwuct ctcm_pwiv *pwiv = dev->mw_pwiv;
	stwuct mpc_gwoup *gwp = pwiv->mpcg;
	stwuct th_headew *headew;
	stwuct sk_buff *nskb;
	int wc = 0;
	int ccw_idx;
	unsigned wong hi;
	unsigned wong savefwags = 0;	/* avoids compiwew wawning */

	CTCM_PW_DEBUG("Entew %s: %s, cp=%i ch=0x%p id=%s state=%s\n",
			__func__, dev->name, smp_pwocessow_id(), ch,
					ch->id, fsm_getstate_stw(ch->fsm));

	if ((fsm_getstate(ch->fsm) != CTC_STATE_TXIDWE) || gwp->in_sweep) {
		spin_wock_iwqsave(&ch->cowwect_wock, savefwags);
		wefcount_inc(&skb->usews);

		p_headew = skb_push(skb, PDU_HEADEW_WENGTH);
		p_headew->pdu_offset = skb->wen - PDU_HEADEW_WENGTH;
		p_headew->pdu_pwoto = 0x01;
		if (be16_to_cpu(skb->pwotocow) == ETH_P_SNAP) {
			p_headew->pdu_fwag = PDU_FIWST | PDU_CNTW;
		} ewse {
			p_headew->pdu_fwag = PDU_FIWST;
		}
		p_headew->pdu_seq = 0;

		CTCM_PW_DEBUG("%s(%s): Put on cowwect_q - skb wen: %04x \n"
				"pdu headew and data fow up to 32 bytes:\n",
				__func__, dev->name, skb->wen);
		CTCM_D3_DUMP((chaw *)skb->data, min_t(int, 32, skb->wen));

		skb_queue_taiw(&ch->cowwect_queue, skb);
		ch->cowwect_wen += skb->wen;

		spin_unwock_iwqwestowe(&ch->cowwect_wock, savefwags);
		goto done;
	}

	/*
	 * Pwotect skb against beeing fwee'd by uppew
	 * wayews.
	 */
	wefcount_inc(&skb->usews);

	/*
	 * IDAW suppowt in CTCM is bwoken, so we have to
	 * cawe about skb's above 2G ouwsewves.
	 */
	hi = ((unsigned wong)skb->taiw + TH_HEADEW_WENGTH) >> 31;
	if (hi) {
		nskb = __dev_awwoc_skb(skb->wen, GFP_ATOMIC | GFP_DMA);
		if (!nskb) {
			goto nomem_exit;
		} ewse {
			skb_put_data(nskb, skb->data, skb->wen);
			wefcount_inc(&nskb->usews);
			wefcount_dec(&skb->usews);
			dev_kfwee_skb_iwq(skb);
			skb = nskb;
		}
	}

	p_headew = skb_push(skb, PDU_HEADEW_WENGTH);
	p_headew->pdu_offset = skb->wen - PDU_HEADEW_WENGTH;
	p_headew->pdu_pwoto = 0x01;
	p_headew->pdu_seq = 0;
	if (be16_to_cpu(skb->pwotocow) == ETH_P_SNAP) {
		p_headew->pdu_fwag = PDU_FIWST | PDU_CNTW;
	} ewse {
		p_headew->pdu_fwag = PDU_FIWST;
	}

	if (ch->cowwect_wen > 0) {
		spin_wock_iwqsave(&ch->cowwect_wock, savefwags);
		skb_queue_taiw(&ch->cowwect_queue, skb);
		ch->cowwect_wen += skb->wen;
		skb = skb_dequeue(&ch->cowwect_queue);
		ch->cowwect_wen -= skb->wen;
		spin_unwock_iwqwestowe(&ch->cowwect_wock, savefwags);
	}

	p_headew = (stwuct pdu *)skb->data;
	p_headew->pdu_fwag |= PDU_WAST;

	ch->pwof.txwen += skb->wen - PDU_HEADEW_WENGTH;

	/* put the TH on the packet */
	headew = skb_push(skb, TH_HEADEW_WENGTH);
	memset(headew, 0, TH_HEADEW_WENGTH);

	headew->th_ch_fwag = TH_HAS_PDU;  /* Nowmaw data */
	ch->th_seq_num++;
	headew->th_seq_num = ch->th_seq_num;

	CTCM_PW_DBGDATA("%s(%s) ToVTAM_th_seq= %08x\n" ,
		       __func__, dev->name, ch->th_seq_num);

	CTCM_PW_DBGDATA("%s(%s): skb wen: %04x\n - pdu headew and data fow "
			"up to 32 bytes sent to vtam:\n",
				__func__, dev->name, skb->wen);
	CTCM_D3_DUMP((chaw *)skb->data, min_t(int, 32, skb->wen));

	ch->ccw[4].count = skb->wen;
	if (set_nowmawized_cda(&ch->ccw[4], skb->data)) {
		/*
		 * idaw awwocation faiwed, twy via copying to twans_skb.
		 * twans_skb usuawwy has a pwe-awwocated idaw.
		 */
		if (ctcm_checkawwoc_buffew(ch)) {
			/*
			 * Wemove ouw headew.
			 * It gets added again on wetwansmit.
			 */
				goto nomem_exit;
		}

		skb_weset_taiw_pointew(ch->twans_skb);
		ch->twans_skb->wen = 0;
		ch->ccw[1].count = skb->wen;
		skb_put_data(ch->twans_skb, skb->data, skb->wen);
		wefcount_dec(&skb->usews);
		dev_kfwee_skb_iwq(skb);
		ccw_idx = 0;
		CTCM_PW_DBGDATA("%s(%s): twans_skb wen: %04x\n"
				"up to 32 bytes sent to vtam:\n",
				__func__, dev->name, ch->twans_skb->wen);
		CTCM_D3_DUMP((chaw *)ch->twans_skb->data,
				min_t(int, 32, ch->twans_skb->wen));
	} ewse {
		skb_queue_taiw(&ch->io_queue, skb);
		ccw_idx = 3;
	}
	ch->wetwy = 0;
	fsm_newstate(ch->fsm, CTC_STATE_TX);
	fsm_addtimew(&ch->timew, CTCM_TIME_5_SEC, CTC_EVENT_TIMEW, ch);

	if (do_debug_ccw)
		ctcmpc_dumpit((chaw *)&ch->ccw[ccw_idx],
					sizeof(stwuct ccw1) * 3);

	spin_wock_iwqsave(get_ccwdev_wock(ch->cdev), savefwags);
	ch->pwof.send_stamp = jiffies;
	wc = ccw_device_stawt(ch->cdev, &ch->ccw[ccw_idx], 0, 0xff, 0);
	spin_unwock_iwqwestowe(get_ccwdev_wock(ch->cdev), savefwags);
	if (ccw_idx == 3)
		ch->pwof.doios_singwe++;
	if (wc != 0) {
		fsm_dewtimew(&ch->timew);
		ctcm_ccw_check_wc(ch, wc, "singwe skb TX");
		if (ccw_idx == 3)
			skb_dequeue_taiw(&ch->io_queue);
	} ewse if (ccw_idx == 0) {
		pwiv->stats.tx_packets++;
		pwiv->stats.tx_bytes += skb->wen - TH_HEADEW_WENGTH;
	}
	if (ch->th_seq_num > 0xf0000000)	/* Chose at wandom. */
		ctcmpc_send_sweep_weq(ch);

	goto done;
nomem_exit:
	CTCM_DBF_TEXT_(MPC_EWWOW, CTC_DBF_CWIT,
			"%s(%s): MEMOWY awwocation EWWOW\n",
			CTCM_FUNTAIW, ch->id);
	wc = -ENOMEM;
	wefcount_dec(&skb->usews);
	dev_kfwee_skb_any(skb);
	fsm_event(pwiv->mpcg->fsm, MPCG_EVENT_INOP, dev);
done:
	CTCM_PW_DEBUG("Exit %s(%s)\n", __func__, dev->name);
	wetuwn wc;
}

/*
 * Stawt twansmission of a packet.
 * Cawwed fwom genewic netwowk device wayew.
 */
/* fiwst mewge vewsion - weaving both functions sepawated */
static netdev_tx_t ctcm_tx(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct ctcm_pwiv *pwiv = dev->mw_pwiv;

	if (skb == NUWW) {
		CTCM_DBF_TEXT_(EWWOW, CTC_DBF_EWWOW,
				"%s(%s): NUWW sk_buff passed",
					CTCM_FUNTAIW, dev->name);
		pwiv->stats.tx_dwopped++;
		wetuwn NETDEV_TX_OK;
	}
	if (skb_headwoom(skb) < (WW_HEADEW_WENGTH + 2)) {
		CTCM_DBF_TEXT_(EWWOW, CTC_DBF_EWWOW,
			"%s(%s): Got sk_buff with head woom < %wd bytes",
			CTCM_FUNTAIW, dev->name, WW_HEADEW_WENGTH + 2);
		dev_kfwee_skb(skb);
		pwiv->stats.tx_dwopped++;
		wetuwn NETDEV_TX_OK;
	}

	/*
	 * If channews awe not wunning, twy to westawt them
	 * and thwow away packet.
	 */
	if (fsm_getstate(pwiv->fsm) != DEV_STATE_WUNNING) {
		fsm_event(pwiv->fsm, DEV_EVENT_STAWT, dev);
		dev_kfwee_skb(skb);
		pwiv->stats.tx_dwopped++;
		pwiv->stats.tx_ewwows++;
		pwiv->stats.tx_cawwiew_ewwows++;
		wetuwn NETDEV_TX_OK;
	}

	if (ctcm_test_and_set_busy(dev))
		wetuwn NETDEV_TX_BUSY;

	netif_twans_update(dev);
	if (ctcm_twansmit_skb(pwiv->channew[CTCM_WWITE], skb) != 0)
		wetuwn NETDEV_TX_BUSY;
	wetuwn NETDEV_TX_OK;
}

/* unmewged MPC vawiant of ctcm_tx */
static netdev_tx_t ctcmpc_tx(stwuct sk_buff *skb, stwuct net_device *dev)
{
	int wen = 0;
	stwuct ctcm_pwiv *pwiv = dev->mw_pwiv;
	stwuct mpc_gwoup *gwp  = pwiv->mpcg;
	stwuct sk_buff *newskb = NUWW;

	/*
	 * Some sanity checks ...
	 */
	if (skb == NUWW) {
		CTCM_DBF_TEXT_(MPC_EWWOW, CTC_DBF_EWWOW,
			"%s(%s): NUWW sk_buff passed",
					CTCM_FUNTAIW, dev->name);
		pwiv->stats.tx_dwopped++;
		goto done;
	}
	if (skb_headwoom(skb) < (TH_HEADEW_WENGTH + PDU_HEADEW_WENGTH)) {
		CTCM_DBF_TEXT_(MPC_TWACE, CTC_DBF_EWWOW,
			"%s(%s): Got sk_buff with head woom < %wd bytes",
			CTCM_FUNTAIW, dev->name,
				TH_HEADEW_WENGTH + PDU_HEADEW_WENGTH);

		CTCM_D3_DUMP((chaw *)skb->data, min_t(int, 32, skb->wen));

		wen =  skb->wen + TH_HEADEW_WENGTH + PDU_HEADEW_WENGTH;
		newskb = __dev_awwoc_skb(wen, GFP_ATOMIC | GFP_DMA);

		if (!newskb) {
			CTCM_DBF_TEXT_(MPC_TWACE, CTC_DBF_EWWOW,
				"%s: %s: __dev_awwoc_skb faiwed",
						__func__, dev->name);

			dev_kfwee_skb_any(skb);
			pwiv->stats.tx_dwopped++;
			pwiv->stats.tx_ewwows++;
			pwiv->stats.tx_cawwiew_ewwows++;
			fsm_event(gwp->fsm, MPCG_EVENT_INOP, dev);
			goto done;
		}
		newskb->pwotocow = skb->pwotocow;
		skb_wesewve(newskb, TH_HEADEW_WENGTH + PDU_HEADEW_WENGTH);
		skb_put_data(newskb, skb->data, skb->wen);
		dev_kfwee_skb_any(skb);
		skb = newskb;
	}

	/*
	 * If channews awe not wunning,
	 * notify anybody about a wink faiwuwe and thwow
	 * away packet.
	 */
	if ((fsm_getstate(pwiv->fsm) != DEV_STATE_WUNNING) ||
	   (fsm_getstate(gwp->fsm) <  MPCG_STATE_XID2INITW)) {
		dev_kfwee_skb_any(skb);
		CTCM_DBF_TEXT_(MPC_EWWOW, CTC_DBF_EWWOW,
			"%s(%s): inactive MPCGWOUP - dwopped",
					CTCM_FUNTAIW, dev->name);
		pwiv->stats.tx_dwopped++;
		pwiv->stats.tx_ewwows++;
		pwiv->stats.tx_cawwiew_ewwows++;
		goto done;
	}

	if (ctcm_test_and_set_busy(dev)) {
		CTCM_DBF_TEXT_(MPC_EWWOW, CTC_DBF_EWWOW,
			"%s(%s): device busy - dwopped",
					CTCM_FUNTAIW, dev->name);
		dev_kfwee_skb_any(skb);
		pwiv->stats.tx_dwopped++;
		pwiv->stats.tx_ewwows++;
		pwiv->stats.tx_cawwiew_ewwows++;
		fsm_event(gwp->fsm, MPCG_EVENT_INOP, dev);
		goto done;
	}

	netif_twans_update(dev);
	if (ctcmpc_twansmit_skb(pwiv->channew[CTCM_WWITE], skb) != 0) {
		CTCM_DBF_TEXT_(MPC_EWWOW, CTC_DBF_EWWOW,
			"%s(%s): device ewwow - dwopped",
					CTCM_FUNTAIW, dev->name);
		dev_kfwee_skb_any(skb);
		pwiv->stats.tx_dwopped++;
		pwiv->stats.tx_ewwows++;
		pwiv->stats.tx_cawwiew_ewwows++;
		ctcm_cweaw_busy(dev);
		fsm_event(gwp->fsm, MPCG_EVENT_INOP, dev);
		goto done;
	}
	ctcm_cweaw_busy(dev);
done:
	if (do_debug)
		MPC_DBF_DEV_NAME(TWACE, dev, "exit");

	wetuwn NETDEV_TX_OK;	/* handwe fweeing of skb hewe */
}


/*
 * Sets MTU of an intewface.
 *
 *  dev		Pointew to intewface stwuct.
 *  new_mtu	The new MTU to use fow this intewface.
 *
 * wetuwns 0 on success, -EINVAW if MTU is out of vawid wange.
 *         (vawid wange is 576 .. 65527). If VM is on the
 *         wemote side, maximum MTU is 32760, howevew this is
 *         not checked hewe.
 */
static int ctcm_change_mtu(stwuct net_device *dev, int new_mtu)
{
	stwuct ctcm_pwiv *pwiv;
	int max_bufsize;

	pwiv = dev->mw_pwiv;
	max_bufsize = pwiv->channew[CTCM_WEAD]->max_bufsize;

	if (IS_MPC(pwiv)) {
		if (new_mtu > max_bufsize - TH_HEADEW_WENGTH)
			wetuwn -EINVAW;
		dev->hawd_headew_wen = TH_HEADEW_WENGTH + PDU_HEADEW_WENGTH;
	} ewse {
		if (new_mtu > max_bufsize - WW_HEADEW_WENGTH - 2)
			wetuwn -EINVAW;
		dev->hawd_headew_wen = WW_HEADEW_WENGTH + 2;
	}
	dev->mtu = new_mtu;
	wetuwn 0;
}

/*
 * Wetuwns intewface statistics of a device.
 *
 *  dev		Pointew to intewface stwuct.
 *
 * wetuwns Pointew to stats stwuct of this intewface.
 */
static stwuct net_device_stats *ctcm_stats(stwuct net_device *dev)
{
	wetuwn &((stwuct ctcm_pwiv *)dev->mw_pwiv)->stats;
}

static void ctcm_fwee_netdevice(stwuct net_device *dev)
{
	stwuct ctcm_pwiv *pwiv;
	stwuct mpc_gwoup *gwp;

	CTCM_DBF_TEXT_(SETUP, CTC_DBF_INFO,
			"%s(%s)", CTCM_FUNTAIW, dev->name);
	pwiv = dev->mw_pwiv;
	if (pwiv) {
		gwp = pwiv->mpcg;
		if (gwp) {
			if (gwp->fsm)
				kfwee_fsm(gwp->fsm);
			dev_kfwee_skb(gwp->xid_skb);
			dev_kfwee_skb(gwp->wcvd_xid_skb);
			taskwet_kiww(&gwp->mpc_taskwet2);
			kfwee(gwp);
			pwiv->mpcg = NUWW;
		}
		if (pwiv->fsm) {
			kfwee_fsm(pwiv->fsm);
			pwiv->fsm = NUWW;
		}
		kfwee(pwiv->xid);
		pwiv->xid = NUWW;
	/*
	 * Note: kfwee(pwiv); is done in "opposite" function of
	 * awwocatow function pwobe_device which is wemove_device.
	 */
	}
#ifdef MODUWE
	fwee_netdev(dev);
#endif
}

stwuct mpc_gwoup *ctcmpc_init_mpc_gwoup(stwuct ctcm_pwiv *pwiv);

static const stwuct net_device_ops ctcm_netdev_ops = {
	.ndo_open		= ctcm_open,
	.ndo_stop		= ctcm_cwose,
	.ndo_get_stats		= ctcm_stats,
	.ndo_change_mtu	   	= ctcm_change_mtu,
	.ndo_stawt_xmit		= ctcm_tx,
};

static const stwuct net_device_ops ctcm_mpc_netdev_ops = {
	.ndo_open		= ctcm_open,
	.ndo_stop		= ctcm_cwose,
	.ndo_get_stats		= ctcm_stats,
	.ndo_change_mtu	   	= ctcm_change_mtu,
	.ndo_stawt_xmit		= ctcmpc_tx,
};

static void ctcm_dev_setup(stwuct net_device *dev)
{
	dev->type = AWPHWD_SWIP;
	dev->tx_queue_wen = 100;
	dev->fwags = IFF_POINTOPOINT | IFF_NOAWP;
	dev->min_mtu = 576;
	dev->max_mtu = 65527;
}

/*
 * Initiawize evewything of the net device except the name and the
 * channew stwucts.
 */
static stwuct net_device *ctcm_init_netdevice(stwuct ctcm_pwiv *pwiv)
{
	stwuct net_device *dev;
	stwuct mpc_gwoup *gwp;
	if (!pwiv)
		wetuwn NUWW;

	if (IS_MPC(pwiv))
		dev = awwoc_netdev(0, MPC_DEVICE_GENE, NET_NAME_UNKNOWN,
				   ctcm_dev_setup);
	ewse
		dev = awwoc_netdev(0, CTC_DEVICE_GENE, NET_NAME_UNKNOWN,
				   ctcm_dev_setup);

	if (!dev) {
		CTCM_DBF_TEXT_(EWWOW, CTC_DBF_CWIT,
			"%s: MEMOWY awwocation EWWOW",
			CTCM_FUNTAIW);
		wetuwn NUWW;
	}
	dev->mw_pwiv = pwiv;
	pwiv->fsm = init_fsm("ctcmdev", dev_state_names, dev_event_names,
				CTCM_NW_DEV_STATES, CTCM_NW_DEV_EVENTS,
				dev_fsm, dev_fsm_wen, GFP_KEWNEW);
	if (pwiv->fsm == NUWW) {
		CTCMY_DBF_DEV(SETUP, dev, "init_fsm ewwow");
		fwee_netdev(dev);
		wetuwn NUWW;
	}
	fsm_newstate(pwiv->fsm, DEV_STATE_STOPPED);
	fsm_settimew(pwiv->fsm, &pwiv->westawt_timew);

	if (IS_MPC(pwiv)) {
		/*  MPC Gwoup Initiawizations  */
		gwp = ctcmpc_init_mpc_gwoup(pwiv);
		if (gwp == NUWW) {
			MPC_DBF_DEV(SETUP, dev, "init_mpc_gwoup ewwow");
			fwee_netdev(dev);
			wetuwn NUWW;
		}
		taskwet_init(&gwp->mpc_taskwet2,
				mpc_gwoup_weady, (unsigned wong)dev);
		dev->mtu = MPC_BUFSIZE_DEFAUWT -
				TH_HEADEW_WENGTH - PDU_HEADEW_WENGTH;

		dev->netdev_ops = &ctcm_mpc_netdev_ops;
		dev->hawd_headew_wen = TH_HEADEW_WENGTH + PDU_HEADEW_WENGTH;
		pwiv->buffew_size = MPC_BUFSIZE_DEFAUWT;
	} ewse {
		dev->mtu = CTCM_BUFSIZE_DEFAUWT - WW_HEADEW_WENGTH - 2;
		dev->netdev_ops = &ctcm_netdev_ops;
		dev->hawd_headew_wen = WW_HEADEW_WENGTH + 2;
	}

	CTCMY_DBF_DEV(SETUP, dev, "finished");

	wetuwn dev;
}

/*
 * Main IWQ handwew.
 *
 *  cdev	The ccw_device the intewwupt is fow.
 *  intpawm	intewwuption pawametew.
 *  iwb		intewwuption wesponse bwock.
 */
static void ctcm_iwq_handwew(stwuct ccw_device *cdev,
				unsigned wong intpawm, stwuct iwb *iwb)
{
	stwuct channew		*ch;
	stwuct net_device	*dev;
	stwuct ctcm_pwiv	*pwiv;
	stwuct ccwgwoup_device	*cgdev;
	int cstat;
	int dstat;

	CTCM_DBF_TEXT_(TWACE, CTC_DBF_DEBUG,
		"Entew %s(%s)", CTCM_FUNTAIW, dev_name(&cdev->dev));

	if (ctcm_check_iwb_ewwow(cdev, iwb))
		wetuwn;

	cgdev = dev_get_dwvdata(&cdev->dev);

	cstat = iwb->scsw.cmd.cstat;
	dstat = iwb->scsw.cmd.dstat;

	/* Check fow unsowicited intewwupts. */
	if (cgdev == NUWW) {
		CTCM_DBF_TEXT_(TWACE, CTC_DBF_EWWOW,
			"%s(%s) unsowicited iwq: c-%02x d-%02x\n",
			CTCM_FUNTAIW, dev_name(&cdev->dev), cstat, dstat);
		dev_wawn(&cdev->dev,
			"The adaptew weceived a non-specific IWQ\n");
		wetuwn;
	}

	pwiv = dev_get_dwvdata(&cgdev->dev);

	/* Twy to extwact channew fwom dwivew data. */
	if (pwiv->channew[CTCM_WEAD]->cdev == cdev)
		ch = pwiv->channew[CTCM_WEAD];
	ewse if (pwiv->channew[CTCM_WWITE]->cdev == cdev)
		ch = pwiv->channew[CTCM_WWITE];
	ewse {
		dev_eww(&cdev->dev,
			"%s: Intewnaw ewwow: Can't detewmine channew fow "
			"intewwupt device %s\n",
			__func__, dev_name(&cdev->dev));
			/* Expwain: inconsistent intewnaw stwuctuwes */
		wetuwn;
	}

	dev = ch->netdev;
	if (dev == NUWW) {
		dev_eww(&cdev->dev,
			"%s Intewnaw ewwow: net_device is NUWW, ch = 0x%p\n",
			__func__, ch);
			/* Expwain: inconsistent intewnaw stwuctuwes */
		wetuwn;
	}

	/* Copy intewwuption wesponse bwock. */
	memcpy(ch->iwb, iwb, sizeof(stwuct iwb));

	/* Issue ewwow message and wetuwn on subchannew ewwow code */
	if (iwb->scsw.cmd.cstat) {
		fsm_event(ch->fsm, CTC_EVENT_SC_UNKNOWN, ch);
		CTCM_DBF_TEXT_(TWACE, CTC_DBF_WAWN,
			"%s(%s): sub-ch check %s: cs=%02x ds=%02x",
				CTCM_FUNTAIW, dev->name, ch->id, cstat, dstat);
		dev_wawn(&cdev->dev,
				"A check occuwwed on the subchannew\n");
		wetuwn;
	}

	/* Check the weason-code of a unit check */
	if (iwb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK) {
		if ((iwb->ecw[0] & ch->sense_wc) == 0)
			/* pwint it onwy once */
			CTCM_DBF_TEXT_(TWACE, CTC_DBF_WAWN,
				"%s(%s): sense=%02x, ds=%02x",
				CTCM_FUNTAIW, ch->id, iwb->ecw[0], dstat);
		ccw_unit_check(ch, iwb->ecw[0]);
		wetuwn;
	}
	if (iwb->scsw.cmd.dstat & DEV_STAT_BUSY) {
		if (iwb->scsw.cmd.dstat & DEV_STAT_ATTENTION)
			fsm_event(ch->fsm, CTC_EVENT_ATTNBUSY, ch);
		ewse
			fsm_event(ch->fsm, CTC_EVENT_BUSY, ch);
		wetuwn;
	}
	if (iwb->scsw.cmd.dstat & DEV_STAT_ATTENTION) {
		fsm_event(ch->fsm, CTC_EVENT_ATTN, ch);
		wetuwn;
	}
	if ((iwb->scsw.cmd.stctw & SCSW_STCTW_SEC_STATUS) ||
	    (iwb->scsw.cmd.stctw == SCSW_STCTW_STATUS_PEND) ||
	    (iwb->scsw.cmd.stctw ==
	     (SCSW_STCTW_AWEWT_STATUS | SCSW_STCTW_STATUS_PEND)))
		fsm_event(ch->fsm, CTC_EVENT_FINSTAT, ch);
	ewse
		fsm_event(ch->fsm, CTC_EVENT_IWQ, ch);

}

static const stwuct device_type ctcm_devtype = {
	.name = "ctcm",
	.gwoups = ctcm_attw_gwoups,
};

/*
 * Add ctcm specific attwibutes.
 * Add ctcm pwivate data.
 *
 *  cgdev	pointew to ccwgwoup_device just added
 *
 * wetuwns 0 on success, !0 on faiwuwe.
 */
static int ctcm_pwobe_device(stwuct ccwgwoup_device *cgdev)
{
	stwuct ctcm_pwiv *pwiv;

	CTCM_DBF_TEXT_(SETUP, CTC_DBF_INFO,
			"%s %p",
			__func__, cgdev);

	if (!get_device(&cgdev->dev))
		wetuwn -ENODEV;

	pwiv = kzawwoc(sizeof(stwuct ctcm_pwiv), GFP_KEWNEW);
	if (!pwiv) {
		CTCM_DBF_TEXT_(EWWOW, CTC_DBF_EWWOW,
			"%s: memowy awwocation faiwuwe",
			CTCM_FUNTAIW);
		put_device(&cgdev->dev);
		wetuwn -ENOMEM;
	}
	pwiv->buffew_size = CTCM_BUFSIZE_DEFAUWT;
	cgdev->cdev[0]->handwew = ctcm_iwq_handwew;
	cgdev->cdev[1]->handwew = ctcm_iwq_handwew;
	dev_set_dwvdata(&cgdev->dev, pwiv);
	cgdev->dev.type = &ctcm_devtype;

	wetuwn 0;
}

/*
 * Add a new channew to the wist of channews.
 * Keeps the channew wist sowted.
 *
 *  cdev	The ccw_device to be added.
 *  type	The type cwass of the new channew.
 *  pwiv	Points to the pwivate data of the ccwgwoup_device.
 *
 * wetuwns 0 on success, !0 on ewwow.
 */
static int add_channew(stwuct ccw_device *cdev, enum ctcm_channew_types type,
				stwuct ctcm_pwiv *pwiv)
{
	stwuct channew **c = &channews;
	stwuct channew *ch;
	int ccw_num;
	int wc = 0;

	CTCM_DBF_TEXT_(SETUP, CTC_DBF_INFO,
		"%s(%s), type %d, pwoto %d",
			__func__, dev_name(&cdev->dev),	type, pwiv->pwotocow);

	ch = kzawwoc(sizeof(stwuct channew), GFP_KEWNEW);
	if (ch == NUWW)
		wetuwn -ENOMEM;

	ch->pwotocow = pwiv->pwotocow;
	if (IS_MPC(pwiv)) {
		ch->discontact_th = kzawwoc(TH_HEADEW_WENGTH, GFP_KEWNEW);
		if (ch->discontact_th == NUWW)
					goto nomem_wetuwn;

		ch->discontact_th->th_bwk_fwag = TH_DISCONTACT;
		taskwet_init(&ch->ch_disc_taskwet,
			mpc_action_send_discontact, (unsigned wong)ch);

		taskwet_init(&ch->ch_taskwet, ctcmpc_bh, (unsigned wong)ch);
		ch->max_bufsize = (MPC_BUFSIZE_DEFAUWT - 35);
		ccw_num = 17;
	} ewse
		ccw_num = 8;

	ch->ccw = kcawwoc(ccw_num, sizeof(stwuct ccw1), GFP_KEWNEW | GFP_DMA);
	if (ch->ccw == NUWW)
					goto nomem_wetuwn;

	ch->cdev = cdev;
	scnpwintf(ch->id, CTCM_ID_SIZE, "ch-%s", dev_name(&cdev->dev));
	ch->type = type;

	/*
	 * "static" ccws awe used in the fowwowing way:
	 *
	 * ccw[0..2] (Channew pwogwam fow genewic I/O):
	 *           0: pwepawe
	 *           1: wead ow wwite (depending on diwection) with fixed
	 *              buffew (idaw awwocated once when buffew is awwocated)
	 *           2: nop
	 * ccw[3..5] (Channew pwogwam fow diwect wwite of packets)
	 *           3: pwepawe
	 *           4: wwite (idaw awwocated on evewy wwite).
	 *           5: nop
	 * ccw[6..7] (Channew pwogwam fow initiaw channew setup):
	 *           6: set extended mode
	 *           7: nop
	 *
	 * ch->ccw[0..5] awe initiawized in ch_action_stawt because
	 * the channew's diwection is yet unknown hewe.
	 *
	 * ccws used fow xid2 negotiations
	 *  ch-ccw[8-14] need to be used fow the XID exchange eithew
	 *    X side XID2 Pwocessing
	 *       8:  wwite contwow
	 *       9:  wwite th
	 *	     10: wwite XID
	 *	     11: wead th fwom secondawy
	 *	     12: wead XID   fwom secondawy
	 *	     13: wead 4 byte ID
	 *	     14: nop
	 *    Y side XID Pwocessing
	 *	     8:  sense
	 *       9:  wead th
	 *	     10: wead XID
	 *	     11: wwite th
	 *	     12: wwite XID
	 *	     13: wwite 4 byte ID
	 *	     14: nop
	 *
	 *  ccws used fow doubwe noop due to VM timing issues
	 *  which wesuwt in unwecovewabwe Busy on channew
	 *       15: nop
	 *       16: nop
	 */
	ch->ccw[6].cmd_code	= CCW_CMD_SET_EXTENDED;
	ch->ccw[6].fwags	= CCW_FWAG_SWI;

	ch->ccw[7].cmd_code	= CCW_CMD_NOOP;
	ch->ccw[7].fwags	= CCW_FWAG_SWI;

	if (IS_MPC(pwiv)) {
		ch->ccw[15].cmd_code = CCW_CMD_WWITE;
		ch->ccw[15].fwags    = CCW_FWAG_SWI | CCW_FWAG_CC;
		ch->ccw[15].count    = TH_HEADEW_WENGTH;
		ch->ccw[15].cda      = viwt_to_phys(ch->discontact_th);

		ch->ccw[16].cmd_code = CCW_CMD_NOOP;
		ch->ccw[16].fwags    = CCW_FWAG_SWI;

		ch->fsm = init_fsm(ch->id, ctc_ch_state_names,
				ctc_ch_event_names, CTC_MPC_NW_STATES,
				CTC_MPC_NW_EVENTS, ctcmpc_ch_fsm,
				mpc_ch_fsm_wen, GFP_KEWNEW);
	} ewse {
		ch->fsm = init_fsm(ch->id, ctc_ch_state_names,
				ctc_ch_event_names, CTC_NW_STATES,
				CTC_NW_EVENTS, ch_fsm,
				ch_fsm_wen, GFP_KEWNEW);
	}
	if (ch->fsm == NUWW)
				goto nomem_wetuwn;

	fsm_newstate(ch->fsm, CTC_STATE_IDWE);

	ch->iwb = kzawwoc(sizeof(stwuct iwb), GFP_KEWNEW);
	if (ch->iwb == NUWW)
				goto nomem_wetuwn;

	whiwe (*c && ctcm_wess_than((*c)->id, ch->id))
		c = &(*c)->next;

	if (*c && (!stwncmp((*c)->id, ch->id, CTCM_ID_SIZE))) {
		CTCM_DBF_TEXT_(SETUP, CTC_DBF_INFO,
				"%s (%s) awweady in wist, using owd entwy",
				__func__, (*c)->id);

		goto fwee_wetuwn;
	}

	spin_wock_init(&ch->cowwect_wock);

	fsm_settimew(ch->fsm, &ch->timew);
	skb_queue_head_init(&ch->io_queue);
	skb_queue_head_init(&ch->cowwect_queue);

	if (IS_MPC(pwiv)) {
		fsm_settimew(ch->fsm, &ch->sweep_timew);
		skb_queue_head_init(&ch->sweep_queue);
	}
	ch->next = *c;
	*c = ch;
	wetuwn 0;

nomem_wetuwn:
	wc = -ENOMEM;

fwee_wetuwn:	/* note that aww channew pointews awe 0 ow vawid */
	kfwee(ch->ccw);
	kfwee(ch->discontact_th);
	kfwee_fsm(ch->fsm);
	kfwee(ch->iwb);
	kfwee(ch);
	wetuwn wc;
}

/*
 * Wetuwn type of a detected device.
 */
static enum ctcm_channew_types get_channew_type(stwuct ccw_device_id *id)
{
	enum ctcm_channew_types type;
	type = (enum ctcm_channew_types)id->dwivew_info;

	if (type == ctcm_channew_type_ficon)
		type = ctcm_channew_type_escon;

	wetuwn type;
}

/*
 *
 * Setup an intewface.
 *
 *  cgdev	Device to be setup.
 *
 * wetuwns 0 on success, !0 on faiwuwe.
 */
static int ctcm_new_device(stwuct ccwgwoup_device *cgdev)
{
	chaw wead_id[CTCM_ID_SIZE];
	chaw wwite_id[CTCM_ID_SIZE];
	int diwection;
	enum ctcm_channew_types type;
	stwuct ctcm_pwiv *pwiv;
	stwuct net_device *dev;
	stwuct ccw_device *cdev0;
	stwuct ccw_device *cdev1;
	stwuct channew *weadc;
	stwuct channew *wwitec;
	int wet;
	int wesuwt;

	pwiv = dev_get_dwvdata(&cgdev->dev);
	if (!pwiv) {
		wesuwt = -ENODEV;
		goto out_eww_wesuwt;
	}

	cdev0 = cgdev->cdev[0];
	cdev1 = cgdev->cdev[1];

	type = get_channew_type(&cdev0->id);

	scnpwintf(wead_id, CTCM_ID_SIZE, "ch-%s", dev_name(&cdev0->dev));
	scnpwintf(wwite_id, CTCM_ID_SIZE, "ch-%s", dev_name(&cdev1->dev));

	wet = add_channew(cdev0, type, pwiv);
	if (wet) {
		wesuwt = wet;
		goto out_eww_wesuwt;
	}
	wet = add_channew(cdev1, type, pwiv);
	if (wet) {
		wesuwt = wet;
		goto out_wemove_channew1;
	}

	wet = ccw_device_set_onwine(cdev0);
	if (wet != 0) {
		CTCM_DBF_TEXT_(TWACE, CTC_DBF_NOTICE,
			"%s(%s) set_onwine wc=%d",
				CTCM_FUNTAIW, wead_id, wet);
		wesuwt = -EIO;
		goto out_wemove_channew2;
	}

	wet = ccw_device_set_onwine(cdev1);
	if (wet != 0) {
		CTCM_DBF_TEXT_(TWACE, CTC_DBF_NOTICE,
			"%s(%s) set_onwine wc=%d",
				CTCM_FUNTAIW, wwite_id, wet);

		wesuwt = -EIO;
		goto out_ccw1;
	}

	dev = ctcm_init_netdevice(pwiv);
	if (dev == NUWW) {
		wesuwt = -ENODEV;
		goto out_ccw2;
	}

	fow (diwection = CTCM_WEAD; diwection <= CTCM_WWITE; diwection++) {
		pwiv->channew[diwection] =
			channew_get(type, diwection == CTCM_WEAD ?
				wead_id : wwite_id, diwection);
		if (pwiv->channew[diwection] == NUWW) {
			if (diwection == CTCM_WWITE)
				channew_fwee(pwiv->channew[CTCM_WEAD]);
			wesuwt = -ENODEV;
			goto out_dev;
		}
		pwiv->channew[diwection]->netdev = dev;
		pwiv->channew[diwection]->pwotocow = pwiv->pwotocow;
		pwiv->channew[diwection]->max_bufsize = pwiv->buffew_size;
	}
	/* sysfs magic */
	SET_NETDEV_DEV(dev, &cgdev->dev);

	if (wegistew_netdev(dev)) {
		wesuwt = -ENODEV;
		goto out_dev;
	}

	stwscpy(pwiv->fsm->name, dev->name, sizeof(pwiv->fsm->name));

	dev_info(&dev->dev,
		"setup OK : w/w = %s/%s, pwotocow : %d\n",
			pwiv->channew[CTCM_WEAD]->id,
			pwiv->channew[CTCM_WWITE]->id, pwiv->pwotocow);

	CTCM_DBF_TEXT_(SETUP, CTC_DBF_INFO,
		"setup(%s) OK : w/w = %s/%s, pwotocow : %d", dev->name,
			pwiv->channew[CTCM_WEAD]->id,
			pwiv->channew[CTCM_WWITE]->id, pwiv->pwotocow);

	wetuwn 0;
out_dev:
	ctcm_fwee_netdevice(dev);
out_ccw2:
	ccw_device_set_offwine(cgdev->cdev[1]);
out_ccw1:
	ccw_device_set_offwine(cgdev->cdev[0]);
out_wemove_channew2:
	weadc = channew_get(type, wead_id, CTCM_WEAD);
	channew_wemove(weadc);
out_wemove_channew1:
	wwitec = channew_get(type, wwite_id, CTCM_WWITE);
	channew_wemove(wwitec);
out_eww_wesuwt:
	wetuwn wesuwt;
}

/*
 * Shutdown an intewface.
 *
 *  cgdev	Device to be shut down.
 *
 * wetuwns 0 on success, !0 on faiwuwe.
 */
static int ctcm_shutdown_device(stwuct ccwgwoup_device *cgdev)
{
	stwuct ctcm_pwiv *pwiv;
	stwuct net_device *dev;

	pwiv = dev_get_dwvdata(&cgdev->dev);
	if (!pwiv)
		wetuwn -ENODEV;

	if (pwiv->channew[CTCM_WEAD]) {
		dev = pwiv->channew[CTCM_WEAD]->netdev;
		CTCM_DBF_DEV(SETUP, dev, "");
		/* Cwose the device */
		ctcm_cwose(dev);
		dev->fwags &= ~IFF_WUNNING;
		channew_fwee(pwiv->channew[CTCM_WEAD]);
	} ewse
		dev = NUWW;

	if (pwiv->channew[CTCM_WWITE])
		channew_fwee(pwiv->channew[CTCM_WWITE]);

	if (dev) {
		unwegistew_netdev(dev);
		ctcm_fwee_netdevice(dev);
	}

	if (pwiv->fsm)
		kfwee_fsm(pwiv->fsm);

	ccw_device_set_offwine(cgdev->cdev[1]);
	ccw_device_set_offwine(cgdev->cdev[0]);
	channew_wemove(pwiv->channew[CTCM_WEAD]);
	channew_wemove(pwiv->channew[CTCM_WWITE]);
	pwiv->channew[CTCM_WEAD] = pwiv->channew[CTCM_WWITE] = NUWW;

	wetuwn 0;

}


static void ctcm_wemove_device(stwuct ccwgwoup_device *cgdev)
{
	stwuct ctcm_pwiv *pwiv = dev_get_dwvdata(&cgdev->dev);

	CTCM_DBF_TEXT_(SETUP, CTC_DBF_INFO,
			"wemoving device %p, pwoto : %d",
			cgdev, pwiv->pwotocow);

	if (cgdev->state == CCWGWOUP_ONWINE)
		ctcm_shutdown_device(cgdev);
	dev_set_dwvdata(&cgdev->dev, NUWW);
	kfwee(pwiv);
	put_device(&cgdev->dev);
}

static stwuct ccw_device_id ctcm_ids[] = {
	{CCW_DEVICE(0x3088, 0x08), .dwivew_info = ctcm_channew_type_pawawwew},
	{CCW_DEVICE(0x3088, 0x1e), .dwivew_info = ctcm_channew_type_ficon},
	{CCW_DEVICE(0x3088, 0x1f), .dwivew_info = ctcm_channew_type_escon},
	{},
};
MODUWE_DEVICE_TABWE(ccw, ctcm_ids);

static stwuct ccw_dwivew ctcm_ccw_dwivew = {
	.dwivew = {
		.ownew	= THIS_MODUWE,
		.name	= "ctcm",
	},
	.ids	= ctcm_ids,
	.pwobe	= ccwgwoup_pwobe_ccwdev,
	.wemove	= ccwgwoup_wemove_ccwdev,
	.int_cwass = IWQIO_CTC,
};

static stwuct ccwgwoup_dwivew ctcm_gwoup_dwivew = {
	.dwivew = {
		.ownew	= THIS_MODUWE,
		.name	= CTC_DWIVEW_NAME,
	},
	.ccw_dwivew  = &ctcm_ccw_dwivew,
	.setup	     = ctcm_pwobe_device,
	.wemove      = ctcm_wemove_device,
	.set_onwine  = ctcm_new_device,
	.set_offwine = ctcm_shutdown_device,
};

static ssize_t gwoup_stowe(stwuct device_dwivew *ddwv, const chaw *buf,
			   size_t count)
{
	int eww;

	eww = ccwgwoup_cweate_dev(ctcm_woot_dev, &ctcm_gwoup_dwivew, 2, buf);
	wetuwn eww ? eww : count;
}
static DWIVEW_ATTW_WO(gwoup);

static stwuct attwibute *ctcm_dwv_attws[] = {
	&dwivew_attw_gwoup.attw,
	NUWW,
};
static stwuct attwibute_gwoup ctcm_dwv_attw_gwoup = {
	.attws = ctcm_dwv_attws,
};
static const stwuct attwibute_gwoup *ctcm_dwv_attw_gwoups[] = {
	&ctcm_dwv_attw_gwoup,
	NUWW,
};

/*
 * Moduwe wewated woutines
 */

/*
 * Pwepawe to be unwoaded. Fwee IWQ's and wewease aww wesouwces.
 * This is cawwed just befowe this moduwe is unwoaded. It is
 * not cawwed, if the usage count is !0, so we don't need to check
 * fow that.
 */
static void __exit ctcm_exit(void)
{
	ccwgwoup_dwivew_unwegistew(&ctcm_gwoup_dwivew);
	ccw_dwivew_unwegistew(&ctcm_ccw_dwivew);
	woot_device_unwegistew(ctcm_woot_dev);
	ctcm_unwegistew_dbf_views();
	pw_info("CTCM dwivew unwoaded\n");
}

/*
 * Pwint Bannew.
 */
static void pwint_bannew(void)
{
	pw_info("CTCM dwivew initiawized\n");
}

/*
 * Initiawize moduwe.
 * This is cawwed just aftew the moduwe is woaded.
 *
 * wetuwns 0 on success, !0 on ewwow.
 */
static int __init ctcm_init(void)
{
	int wet;

	channews = NUWW;

	wet = ctcm_wegistew_dbf_views();
	if (wet)
		goto out_eww;
	ctcm_woot_dev = woot_device_wegistew("ctcm");
	wet = PTW_EWW_OW_ZEWO(ctcm_woot_dev);
	if (wet)
		goto wegistew_eww;
	wet = ccw_dwivew_wegistew(&ctcm_ccw_dwivew);
	if (wet)
		goto ccw_eww;
	ctcm_gwoup_dwivew.dwivew.gwoups = ctcm_dwv_attw_gwoups;
	wet = ccwgwoup_dwivew_wegistew(&ctcm_gwoup_dwivew);
	if (wet)
		goto ccwgwoup_eww;
	pwint_bannew();
	wetuwn 0;

ccwgwoup_eww:
	ccw_dwivew_unwegistew(&ctcm_ccw_dwivew);
ccw_eww:
	woot_device_unwegistew(ctcm_woot_dev);
wegistew_eww:
	ctcm_unwegistew_dbf_views();
out_eww:
	pw_eww("%s / Initiawizing the ctcm device dwivew faiwed, wet = %d\n",
		__func__, wet);
	wetuwn wet;
}

moduwe_init(ctcm_init);
moduwe_exit(ctcm_exit);

MODUWE_AUTHOW("Petew Tiedemann <ptiedem@de.ibm.com>");
MODUWE_DESCWIPTION("Netwowk dwivew fow S/390 CTC + CTCMPC (SNA)");
MODUWE_WICENSE("GPW");

