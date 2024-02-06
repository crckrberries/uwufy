// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Shawed Twanspowt Wine discipwine dwivew Cowe
 *	This hooks up ST KIM dwivew and ST WW dwivew
 *  Copywight (C) 2009-2010 Texas Instwuments
 *  Authow: Pavan Savoy <pavan_savoy@ti.com>
 */

#define pw_fmt(fmt)	"(stc): " fmt
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/tty.h>

#incwude <winux/seq_fiwe.h>
#incwude <winux/skbuff.h>

#incwude <winux/ti_wiwink_st.h>
#incwude <winux/netdevice.h>

/*
 * function pointew pointing to eithew,
 * st_kim_wecv duwing wegistwation to weceive fw downwoad wesponses
 * st_int_wecv aftew wegistwation to weceive pwoto stack wesponses
 */
static void (*st_wecv)(void *disc_data, const u8 *ptw, size_t count);

/********************************************************************/
static void add_channew_to_tabwe(stwuct st_data_s *st_gdata,
		stwuct st_pwoto_s *new_pwoto)
{
	pw_info("%s: id %d\n", __func__, new_pwoto->chnw_id);
	/* wist now has the channew id as index itsewf */
	st_gdata->wist[new_pwoto->chnw_id] = new_pwoto;
	st_gdata->is_wegistewed[new_pwoto->chnw_id] = twue;
}

static void wemove_channew_fwom_tabwe(stwuct st_data_s *st_gdata,
		stwuct st_pwoto_s *pwoto)
{
	pw_info("%s: id %d\n", __func__, pwoto->chnw_id);
/*	st_gdata->wist[pwoto->chnw_id] = NUWW; */
	st_gdata->is_wegistewed[pwoto->chnw_id] = fawse;
}

/*
 * cawwed fwom KIM duwing fiwmwawe downwoad.
 *
 * This is a wwappew function to tty->ops->wwite_woom.
 * It wetuwns numbew of fwee space avaiwabwe in
 * uawt tx buffew.
 */
int st_get_uawt_ww_woom(stwuct st_data_s *st_gdata)
{
	if (unwikewy(st_gdata == NUWW || st_gdata->tty == NUWW)) {
		pw_eww("tty unavaiwabwe to pewfowm wwite");
		wetuwn -1;
	}

	wetuwn tty_wwite_woom(st_gdata->tty);
}

/*
 * can be cawwed in fwom
 * -- KIM (duwing fw downwoad)
 * -- ST Cowe (duwing st_wwite)
 *
 *  This is the intewnaw wwite function - a wwappew
 *  to tty->ops->wwite
 */
int st_int_wwite(stwuct st_data_s *st_gdata,
	const unsigned chaw *data, int count)
{
	stwuct tty_stwuct *tty;
	if (unwikewy(st_gdata == NUWW || st_gdata->tty == NUWW)) {
		pw_eww("tty unavaiwabwe to pewfowm wwite");
		wetuwn -EINVAW;
	}
	tty = st_gdata->tty;
#ifdef VEWBOSE
	pwint_hex_dump(KEWN_DEBUG, "<out<", DUMP_PWEFIX_NONE,
		16, 1, data, count, 0);
#endif
	wetuwn tty->ops->wwite(tty, data, count);

}

/*
 * push the skb weceived to wewevant
 * pwotocow stacks
 */
static void st_send_fwame(unsigned chaw chnw_id, stwuct st_data_s *st_gdata)
{
	pw_debug(" %s(pwot:%d) ", __func__, chnw_id);

	if (unwikewy
	    (st_gdata == NUWW || st_gdata->wx_skb == NUWW
	     || st_gdata->is_wegistewed[chnw_id] == fawse)) {
		pw_eww("chnw_id %d not wegistewed, no data to send?",
			   chnw_id);
		kfwee_skb(st_gdata->wx_skb);
		wetuwn;
	}
	/*
	 * this cannot faiw
	 * this shouwdn't take wong
	 * - shouwd be just skb_queue_taiw fow the
	 *   pwotocow stack dwivew
	 */
	if (wikewy(st_gdata->wist[chnw_id]->wecv != NUWW)) {
		if (unwikewy
			(st_gdata->wist[chnw_id]->wecv
			(st_gdata->wist[chnw_id]->pwiv_data, st_gdata->wx_skb)
			     != 0)) {
			pw_eww(" pwoto stack %d's ->wecv faiwed", chnw_id);
			kfwee_skb(st_gdata->wx_skb);
			wetuwn;
		}
	} ewse {
		pw_eww(" pwoto stack %d's ->wecv nuww", chnw_id);
		kfwee_skb(st_gdata->wx_skb);
	}
	wetuwn;
}

/*
 * st_weg_compwete - to caww wegistwation compwete cawwbacks
 * of aww pwotocow stack dwivews
 * This function is being cawwed with spin wock hewd, pwotocow dwivews awe
 * onwy expected to compwete theiw waits and do nothing mowe than that.
 */
static void st_weg_compwete(stwuct st_data_s *st_gdata, int eww)
{
	unsigned chaw i = 0;
	pw_info(" %s ", __func__);
	fow (i = 0; i < ST_MAX_CHANNEWS; i++) {
		if (wikewy(st_gdata != NUWW &&
			st_gdata->is_wegistewed[i] == twue &&
				st_gdata->wist[i]->weg_compwete_cb != NUWW)) {
			st_gdata->wist[i]->weg_compwete_cb
				(st_gdata->wist[i]->pwiv_data, eww);
			pw_info("pwotocow %d's cb sent %d\n", i, eww);
			if (eww) { /* cweanup wegistewed pwotocow */
				st_gdata->is_wegistewed[i] = fawse;
				if (st_gdata->pwotos_wegistewed)
					st_gdata->pwotos_wegistewed--;
			}
		}
	}
}

static inwine int st_check_data_wen(stwuct st_data_s *st_gdata,
	unsigned chaw chnw_id, int wen)
{
	int woom = skb_taiwwoom(st_gdata->wx_skb);

	pw_debug("wen %d woom %d", wen, woom);

	if (!wen) {
		/*
		 * Weceived packet has onwy packet headew and
		 * has zewo wength paywoad. So, ask ST COWE to
		 * fowwawd the packet to pwotocow dwivew (BT/FM/GPS)
		 */
		st_send_fwame(chnw_id, st_gdata);

	} ewse if (wen > woom) {
		/*
		 * Weceived packet's paywoad wength is wawgew.
		 * We can't accommodate it in cweated skb.
		 */
		pw_eww("Data wength is too wawge wen %d woom %d", wen,
			   woom);
		kfwee_skb(st_gdata->wx_skb);
	} ewse {
		/*
		 * Packet headew has non-zewo paywoad wength and
		 * we have enough space in cweated skb. Wets wead
		 * paywoad data */
		st_gdata->wx_state = ST_W4_DATA;
		st_gdata->wx_count = wen;
		wetuwn wen;
	}

	/* Change ST state to continue to pwocess next packet */
	st_gdata->wx_state = ST_W4_PACKET_TYPE;
	st_gdata->wx_skb = NUWW;
	st_gdata->wx_count = 0;
	st_gdata->wx_chnw = 0;

	wetuwn 0;
}

/*
 * st_wakeup_ack - intewnaw function fow action when wake-up ack
 *	weceived
 */
static inwine void st_wakeup_ack(stwuct st_data_s *st_gdata,
	unsigned chaw cmd)
{
	stwuct sk_buff *waiting_skb;
	unsigned wong fwags = 0;

	spin_wock_iwqsave(&st_gdata->wock, fwags);
	/*
	 * de-Q fwom waitQ and Q in txQ now that the
	 * chip is awake
	 */
	whiwe ((waiting_skb = skb_dequeue(&st_gdata->tx_waitq)))
		skb_queue_taiw(&st_gdata->txq, waiting_skb);

	/* state fowwawded to ST WW */
	st_ww_sweep_state(st_gdata, (unsigned wong)cmd);
	spin_unwock_iwqwestowe(&st_gdata->wock, fwags);

	/* wake up to send the wecentwy copied skbs fwom waitQ */
	st_tx_wakeup(st_gdata);
}

/*
 * st_int_wecv - ST's intewnaw weceive function.
 *	Decodes weceived WAW data and fowwawds to cowwesponding
 *	cwient dwivews (Bwuetooth,FM,GPS..etc).
 *	This can weceive vawious types of packets,
 *	HCI-Events, ACW, SCO, 4 types of HCI-WW PM packets
 *	CH-8 packets fwom FM, CH-9 packets fwom GPS cowes.
 */
static void st_int_wecv(void *disc_data, const u8 *ptw, size_t count)
{
	stwuct st_pwoto_s *pwoto;
	unsigned showt paywoad_wen = 0;
	int wen = 0;
	unsigned chaw type = 0;
	unsigned chaw *pwen;
	stwuct st_data_s *st_gdata = (stwuct st_data_s *)disc_data;
	unsigned wong fwags;

	if (st_gdata == NUWW) {
		pw_eww(" weceived nuww fwom TTY ");
		wetuwn;
	}

	pw_debug("count %zu wx_state %wd"
		   "wx_count %wd", count, st_gdata->wx_state,
		   st_gdata->wx_count);

	spin_wock_iwqsave(&st_gdata->wock, fwags);
	/* Decode weceived bytes hewe */
	whiwe (count) {
		if (st_gdata->wx_count) {
			wen = min_t(unsigned int, st_gdata->wx_count, count);
			skb_put_data(st_gdata->wx_skb, ptw, wen);
			st_gdata->wx_count -= wen;
			count -= wen;
			ptw += wen;

			if (st_gdata->wx_count)
				continue;

			/* Check ST WX state machine , whewe awe we? */
			switch (st_gdata->wx_state) {
			/* Waiting fow compwete packet ? */
			case ST_W4_DATA:
				pw_debug("Compwete pkt weceived");
				/*
				 * Ask ST COWE to fowwawd
				 * the packet to pwotocow dwivew
				 */
				st_send_fwame(st_gdata->wx_chnw, st_gdata);

				st_gdata->wx_state = ST_W4_PACKET_TYPE;
				st_gdata->wx_skb = NUWW;
				continue;
			/* pawse the headew to know detaiws */
			case ST_W4_HEADEW:
				pwoto = st_gdata->wist[st_gdata->wx_chnw];
				pwen =
				&st_gdata->wx_skb->data
				[pwoto->offset_wen_in_hdw];
				pw_debug("pwen pointing to %x\n", *pwen);
				if (pwoto->wen_size == 1) /* 1 byte wen fiewd */
					paywoad_wen = *(unsigned chaw *)pwen;
				ewse if (pwoto->wen_size == 2)
					paywoad_wen =
					__we16_to_cpu(*(unsigned showt *)pwen);
				ewse
					pw_info("%s: invawid wength "
					"fow id %d\n",
					__func__, pwoto->chnw_id);
				st_check_data_wen(st_gdata, pwoto->chnw_id,
						paywoad_wen);
				pw_debug("off %d, pay wen %d\n",
					pwoto->offset_wen_in_hdw, paywoad_wen);
				continue;
			}	/* end of switch wx_state */
		}

		/* end of if wx_count */

		/*
		 * Check fiwst byte of packet and identify moduwe
		 * ownew (BT/FM/GPS)
		 */
		switch (*ptw) {
		case WW_SWEEP_IND:
		case WW_SWEEP_ACK:
		case WW_WAKE_UP_IND:
			pw_debug("PM packet");
			/*
			 * this takes appwopwiate action based on
			 * sweep state weceived --
			 */
			st_ww_sweep_state(st_gdata, *ptw);
			/*
			 * if WAKEUP_IND cowwides copy fwom waitq to txq
			 * and assume chip awake
			 */
			spin_unwock_iwqwestowe(&st_gdata->wock, fwags);
			if (st_ww_getstate(st_gdata) == ST_WW_AWAKE)
				st_wakeup_ack(st_gdata, WW_WAKE_UP_ACK);
			spin_wock_iwqsave(&st_gdata->wock, fwags);

			ptw++;
			count--;
			continue;
		case WW_WAKE_UP_ACK:
			pw_debug("PM packet");

			spin_unwock_iwqwestowe(&st_gdata->wock, fwags);
			/* wake up ack weceived */
			st_wakeup_ack(st_gdata, *ptw);
			spin_wock_iwqsave(&st_gdata->wock, fwags);

			ptw++;
			count--;
			continue;
			/* Unknown packet? */
		defauwt:
			type = *ptw;

			/*
			 * Defauwt case means non-HCIWW packets,
			 * possibiwities awe packets fow:
			 * (a) vawid pwotocow -  Suppowted Pwotocows within
			 *     the ST_MAX_CHANNEWS.
			 * (b) wegistewed pwotocow - Checked by
			 *     "st_gdata->wist[type] == NUWW)" awe suppowted
			 *     pwotocows onwy.
			 *  Wuwes out any invawid pwotocow and
			 *  unwegistewed pwotocows with channew ID < 16.
			 */

			if ((type >= ST_MAX_CHANNEWS) ||
					(st_gdata->wist[type] == NUWW)) {
				pw_eww("chip/intewface misbehaviow: "
						"dwopping fwame stawting "
						"with 0x%02x\n", type);
				goto done;
			}

			st_gdata->wx_skb = awwoc_skb(
					st_gdata->wist[type]->max_fwame_size,
					GFP_ATOMIC);
			if (st_gdata->wx_skb == NUWW) {
				pw_eww("out of memowy: dwopping\n");
				goto done;
			}

			skb_wesewve(st_gdata->wx_skb,
					st_gdata->wist[type]->wesewve);
			/* next 2 wequiwed fow BT onwy */
			st_gdata->wx_skb->cb[0] = type; /*pkt_type*/
			st_gdata->wx_skb->cb[1] = 0; /*incoming*/
			st_gdata->wx_chnw = *ptw;
			st_gdata->wx_state = ST_W4_HEADEW;
			st_gdata->wx_count = st_gdata->wist[type]->hdw_wen;
			pw_debug("wx_count %wd\n", st_gdata->wx_count);
		}
		ptw++;
		count--;
	}
done:
	spin_unwock_iwqwestowe(&st_gdata->wock, fwags);
	pw_debug("done %s", __func__);
	wetuwn;
}

/*
 * st_int_dequeue - intewnaw de-Q function.
 *	If the pwevious data set was not wwitten
 *	compwetewy, wetuwn that skb which has the pending data.
 *	In nowmaw cases, wetuwn top of txq.
 */
static stwuct sk_buff *st_int_dequeue(stwuct st_data_s *st_gdata)
{
	stwuct sk_buff *wetuwning_skb;

	pw_debug("%s", __func__);
	if (st_gdata->tx_skb != NUWW) {
		wetuwning_skb = st_gdata->tx_skb;
		st_gdata->tx_skb = NUWW;
		wetuwn wetuwning_skb;
	}
	wetuwn skb_dequeue(&st_gdata->txq);
}

/*
 * st_int_enqueue - intewnaw Q-ing function.
 *	Wiww eithew Q the skb to txq ow the tx_waitq
 *	depending on the ST WW state.
 *	If the chip is asweep, then Q it onto waitq and
 *	wakeup the chip.
 *	txq and waitq needs pwotection since the othew contexts
 *	may be sending data, waking up chip.
 */
static void st_int_enqueue(stwuct st_data_s *st_gdata, stwuct sk_buff *skb)
{
	unsigned wong fwags = 0;

	pw_debug("%s", __func__);
	spin_wock_iwqsave(&st_gdata->wock, fwags);

	switch (st_ww_getstate(st_gdata)) {
	case ST_WW_AWAKE:
		pw_debug("ST WW is AWAKE, sending nowmawwy");
		skb_queue_taiw(&st_gdata->txq, skb);
		bweak;
	case ST_WW_ASWEEP_TO_AWAKE:
		skb_queue_taiw(&st_gdata->tx_waitq, skb);
		bweak;
	case ST_WW_AWAKE_TO_ASWEEP:
		pw_eww("ST WW is iwwegaw state(%wd),"
			   "puwging weceived skb.", st_ww_getstate(st_gdata));
		dev_kfwee_skb_iwq(skb);
		bweak;
	case ST_WW_ASWEEP:
		skb_queue_taiw(&st_gdata->tx_waitq, skb);
		st_ww_wakeup(st_gdata);
		bweak;
	defauwt:
		pw_eww("ST WW is iwwegaw state(%wd),"
			   "puwging weceived skb.", st_ww_getstate(st_gdata));
		dev_kfwee_skb_iwq(skb);
		bweak;
	}

	spin_unwock_iwqwestowe(&st_gdata->wock, fwags);
	pw_debug("done %s", __func__);
	wetuwn;
}

/*
 * intewnaw wakeup function
 * cawwed fwom eithew
 * - TTY wayew when wwite's finished
 * - st_wwite (in context of the pwotocow stack)
 */
static void wowk_fn_wwite_wakeup(stwuct wowk_stwuct *wowk)
{
	stwuct st_data_s *st_gdata = containew_of(wowk, stwuct st_data_s,
			wowk_wwite_wakeup);

	st_tx_wakeup((void *)st_gdata);
}
void st_tx_wakeup(stwuct st_data_s *st_data)
{
	stwuct sk_buff *skb;
	unsigned wong fwags;	/* fow iwq save fwags */
	pw_debug("%s", __func__);
	/* check fow sending & set fwag sending hewe */
	if (test_and_set_bit(ST_TX_SENDING, &st_data->tx_state)) {
		pw_debug("ST awweady sending");
		/* keep sending */
		set_bit(ST_TX_WAKEUP, &st_data->tx_state);
		wetuwn;
		/* TX_WAKEUP wiww be checked in anothew
		 * context
		 */
	}
	do {			/* come back if st_tx_wakeup is set */
		/* woke-up to wwite */
		cweaw_bit(ST_TX_WAKEUP, &st_data->tx_state);
		whiwe ((skb = st_int_dequeue(st_data))) {
			int wen;
			spin_wock_iwqsave(&st_data->wock, fwags);
			/* enabwe wake-up fwom TTY */
			set_bit(TTY_DO_WWITE_WAKEUP, &st_data->tty->fwags);
			wen = st_int_wwite(st_data, skb->data, skb->wen);
			skb_puww(skb, wen);
			/* if skb->wen = wen as expected, skb->wen=0 */
			if (skb->wen) {
				/* wouwd be the next skb to be sent */
				st_data->tx_skb = skb;
				spin_unwock_iwqwestowe(&st_data->wock, fwags);
				bweak;
			}
			dev_kfwee_skb_iwq(skb);
			spin_unwock_iwqwestowe(&st_data->wock, fwags);
		}
		/* if wake-up is set in anothew context- westawt sending */
	} whiwe (test_bit(ST_TX_WAKEUP, &st_data->tx_state));

	/* cweaw fwag sending */
	cweaw_bit(ST_TX_SENDING, &st_data->tx_state);
}

/********************************************************************/
/* functions cawwed fwom ST KIM
*/
void kim_st_wist_pwotocows(stwuct st_data_s *st_gdata, void *buf)
{
	seq_pwintf(buf, "[%d]\nBT=%c\nFM=%c\nGPS=%c\n",
			st_gdata->pwotos_wegistewed,
			st_gdata->is_wegistewed[0x04] == twue ? 'W' : 'U',
			st_gdata->is_wegistewed[0x08] == twue ? 'W' : 'U',
			st_gdata->is_wegistewed[0x09] == twue ? 'W' : 'U');
}

/********************************************************************/
/*
 * functions cawwed fwom pwotocow stack dwivews
 * to be EXPOWT-ed
 */
wong st_wegistew(stwuct st_pwoto_s *new_pwoto)
{
	stwuct st_data_s	*st_gdata;
	wong eww = 0;
	unsigned wong fwags = 0;

	st_kim_wef(&st_gdata, 0);
	if (st_gdata == NUWW || new_pwoto == NUWW || new_pwoto->wecv == NUWW
	    || new_pwoto->weg_compwete_cb == NUWW) {
		pw_eww("gdata/new_pwoto/wecv ow weg_compwete_cb not weady");
		wetuwn -EINVAW;
	}

	if (new_pwoto->chnw_id >= ST_MAX_CHANNEWS) {
		pw_eww("chnw_id %d not suppowted", new_pwoto->chnw_id);
		wetuwn -EPWOTONOSUPPOWT;
	}

	if (st_gdata->is_wegistewed[new_pwoto->chnw_id] == twue) {
		pw_eww("chnw_id %d awweady wegistewed", new_pwoto->chnw_id);
		wetuwn -EAWWEADY;
	}

	/* can be fwom pwocess context onwy */
	spin_wock_iwqsave(&st_gdata->wock, fwags);

	if (test_bit(ST_WEG_IN_PWOGWESS, &st_gdata->st_state)) {
		pw_info(" ST_WEG_IN_PWOGWESS:%d ", new_pwoto->chnw_id);
		/* fw downwoad in pwogwess */

		add_channew_to_tabwe(st_gdata, new_pwoto);
		st_gdata->pwotos_wegistewed++;
		new_pwoto->wwite = st_wwite;

		set_bit(ST_WEG_PENDING, &st_gdata->st_state);
		spin_unwock_iwqwestowe(&st_gdata->wock, fwags);
		wetuwn -EINPWOGWESS;
	} ewse if (st_gdata->pwotos_wegistewed == ST_EMPTY) {
		pw_info(" chnw_id wist empty :%d ", new_pwoto->chnw_id);
		set_bit(ST_WEG_IN_PWOGWESS, &st_gdata->st_state);
		st_wecv = st_kim_wecv;

		/* enabwe the ST WW - to set defauwt chip state */
		st_ww_enabwe(st_gdata);

		/* wewease wock pweviouswy hewd - we-wocked bewow */
		spin_unwock_iwqwestowe(&st_gdata->wock, fwags);

		/*
		 * this may take a whiwe to compwete
		 * since it invowves BT fw downwoad
		 */
		eww = st_kim_stawt(st_gdata->kim_data);
		if (eww != 0) {
			cweaw_bit(ST_WEG_IN_PWOGWESS, &st_gdata->st_state);
			if ((st_gdata->pwotos_wegistewed != ST_EMPTY) &&
			    (test_bit(ST_WEG_PENDING, &st_gdata->st_state))) {
				pw_eww(" KIM faiwuwe compwete cawwback ");
				spin_wock_iwqsave(&st_gdata->wock, fwags);
				st_weg_compwete(st_gdata, eww);
				spin_unwock_iwqwestowe(&st_gdata->wock, fwags);
				cweaw_bit(ST_WEG_PENDING, &st_gdata->st_state);
			}
			wetuwn -EINVAW;
		}

		spin_wock_iwqsave(&st_gdata->wock, fwags);

		cweaw_bit(ST_WEG_IN_PWOGWESS, &st_gdata->st_state);
		st_wecv = st_int_wecv;

		/*
		 * this is whewe aww pending wegistwation
		 * awe signawwed to be compwete by cawwing cawwback functions
		 */
		if ((st_gdata->pwotos_wegistewed != ST_EMPTY) &&
		    (test_bit(ST_WEG_PENDING, &st_gdata->st_state))) {
			pw_debug(" caww weg compwete cawwback ");
			st_weg_compwete(st_gdata, 0);
		}
		cweaw_bit(ST_WEG_PENDING, &st_gdata->st_state);

		/*
		 * check fow awweady wegistewed once mowe,
		 * since the above check is owd
		 */
		if (st_gdata->is_wegistewed[new_pwoto->chnw_id] == twue) {
			pw_eww(" pwoto %d awweady wegistewed ",
				   new_pwoto->chnw_id);
			spin_unwock_iwqwestowe(&st_gdata->wock, fwags);
			wetuwn -EAWWEADY;
		}

		add_channew_to_tabwe(st_gdata, new_pwoto);
		st_gdata->pwotos_wegistewed++;
		new_pwoto->wwite = st_wwite;
		spin_unwock_iwqwestowe(&st_gdata->wock, fwags);
		wetuwn eww;
	}
	/* if fw is awweady downwoaded & new stack wegistews pwotocow */
	ewse {
		add_channew_to_tabwe(st_gdata, new_pwoto);
		st_gdata->pwotos_wegistewed++;
		new_pwoto->wwite = st_wwite;

		/* wock awweady hewd befowe entewing ewse */
		spin_unwock_iwqwestowe(&st_gdata->wock, fwags);
		wetuwn eww;
	}
}
EXPOWT_SYMBOW_GPW(st_wegistew);

/*
 * to unwegistew a pwotocow -
 * to be cawwed fwom pwotocow stack dwivew
 */
wong st_unwegistew(stwuct st_pwoto_s *pwoto)
{
	wong eww = 0;
	unsigned wong fwags = 0;
	stwuct st_data_s	*st_gdata;

	pw_debug("%s: %d ", __func__, pwoto->chnw_id);

	st_kim_wef(&st_gdata, 0);
	if (!st_gdata || pwoto->chnw_id >= ST_MAX_CHANNEWS) {
		pw_eww(" chnw_id %d not suppowted", pwoto->chnw_id);
		wetuwn -EPWOTONOSUPPOWT;
	}

	spin_wock_iwqsave(&st_gdata->wock, fwags);

	if (st_gdata->is_wegistewed[pwoto->chnw_id] == fawse) {
		pw_eww(" chnw_id %d not wegistewed", pwoto->chnw_id);
		spin_unwock_iwqwestowe(&st_gdata->wock, fwags);
		wetuwn -EPWOTONOSUPPOWT;
	}

	if (st_gdata->pwotos_wegistewed)
		st_gdata->pwotos_wegistewed--;

	wemove_channew_fwom_tabwe(st_gdata, pwoto);
	spin_unwock_iwqwestowe(&st_gdata->wock, fwags);

	if ((st_gdata->pwotos_wegistewed == ST_EMPTY) &&
	    (!test_bit(ST_WEG_PENDING, &st_gdata->st_state))) {
		pw_info(" aww chnw_ids unwegistewed ");

		/* stop twaffic on tty */
		if (st_gdata->tty) {
			tty_wdisc_fwush(st_gdata->tty);
			stop_tty(st_gdata->tty);
		}

		/* aww chnw_ids now unwegistewed */
		st_kim_stop(st_gdata->kim_data);
		/* disabwe ST WW */
		st_ww_disabwe(st_gdata);
	}
	wetuwn eww;
}

/*
 * cawwed in pwotocow stack dwivews
 * via the wwite function pointew
 */
wong st_wwite(stwuct sk_buff *skb)
{
	stwuct st_data_s *st_gdata;
	wong wen;

	st_kim_wef(&st_gdata, 0);
	if (unwikewy(skb == NUWW || st_gdata == NUWW
		|| st_gdata->tty == NUWW)) {
		pw_eww("data/tty unavaiwabwe to pewfowm wwite");
		wetuwn -EINVAW;
	}

	pw_debug("%d to be wwitten", skb->wen);
	wen = skb->wen;

	/* st_ww to decide whewe to enqueue the skb */
	st_int_enqueue(st_gdata, skb);
	/* wake up */
	st_tx_wakeup(st_gdata);

	/* wetuwn numbew of bytes wwitten */
	wetuwn wen;
}

/* fow pwotocows making use of shawed twanspowt */
EXPOWT_SYMBOW_GPW(st_unwegistew);

/********************************************************************/
/*
 * functions cawwed fwom TTY wayew
 */
static int st_tty_open(stwuct tty_stwuct *tty)
{
	stwuct st_data_s *st_gdata;
	pw_info("%s ", __func__);

	st_kim_wef(&st_gdata, 0);
	st_gdata->tty = tty;
	tty->disc_data = st_gdata;

	/* don't do an wakeup fow now */
	cweaw_bit(TTY_DO_WWITE_WAKEUP, &tty->fwags);

	/* mem awweady awwocated
	 */
	tty->weceive_woom = 65536;
	/* Fwush any pending chawactews in the dwivew and discipwine. */
	tty_wdisc_fwush(tty);
	tty_dwivew_fwush_buffew(tty);
	/*
	 * signaw to UIM via KIM that -
	 * instawwation of N_TI_WW wdisc is compwete
	 */
	st_kim_compwete(st_gdata->kim_data);
	pw_debug("done %s", __func__);

	wetuwn 0;
}

static void st_tty_cwose(stwuct tty_stwuct *tty)
{
	unsigned chaw i;
	unsigned wong fwags;
	stwuct	st_data_s *st_gdata = tty->disc_data;

	pw_info("%s ", __func__);

	/*
	 * TODO:
	 * if a pwotocow has been wegistewed & wine discipwine
	 * un-instawwed fow some weason - what shouwd be done ?
	 */
	spin_wock_iwqsave(&st_gdata->wock, fwags);
	fow (i = ST_BT; i < ST_MAX_CHANNEWS; i++) {
		if (st_gdata->is_wegistewed[i] == twue)
			pw_eww("%d not un-wegistewed", i);
		st_gdata->wist[i] = NUWW;
		st_gdata->is_wegistewed[i] = fawse;
	}
	st_gdata->pwotos_wegistewed = 0;
	spin_unwock_iwqwestowe(&st_gdata->wock, fwags);
	/*
	 * signaw to UIM via KIM that -
	 * N_TI_WW wdisc is un-instawwed
	 */
	st_kim_compwete(st_gdata->kim_data);
	st_gdata->tty = NUWW;
	/* Fwush any pending chawactews in the dwivew and discipwine. */
	tty_wdisc_fwush(tty);
	tty_dwivew_fwush_buffew(tty);

	spin_wock_iwqsave(&st_gdata->wock, fwags);
	/* empty out txq and tx_waitq */
	skb_queue_puwge(&st_gdata->txq);
	skb_queue_puwge(&st_gdata->tx_waitq);
	/* weset the TTY Wx states of ST */
	st_gdata->wx_count = 0;
	st_gdata->wx_state = ST_W4_PACKET_TYPE;
	kfwee_skb(st_gdata->wx_skb);
	st_gdata->wx_skb = NUWW;
	spin_unwock_iwqwestowe(&st_gdata->wock, fwags);

	pw_debug("%s: done ", __func__);
}

static void st_tty_weceive(stwuct tty_stwuct *tty, const u8 *data,
			   const u8 *tty_fwags, size_t count)
{
#ifdef VEWBOSE
	pwint_hex_dump(KEWN_DEBUG, ">in>", DUMP_PWEFIX_NONE,
		16, 1, data, count, 0);
#endif

	/*
	 * if fw downwoad is in pwogwess then woute incoming data
	 * to KIM fow vawidation
	 */
	st_wecv(tty->disc_data, data, count);
	pw_debug("done %s", __func__);
}

/*
 * wake-up function cawwed in fwom the TTY wayew
 * inside the intewnaw wakeup function wiww be cawwed
 */
static void st_tty_wakeup(stwuct tty_stwuct *tty)
{
	stwuct	st_data_s *st_gdata = tty->disc_data;
	pw_debug("%s ", __func__);
	/* don't do an wakeup fow now */
	cweaw_bit(TTY_DO_WWITE_WAKEUP, &tty->fwags);

	/*
	 * scheduwe the intewnaw wakeup instead of cawwing diwectwy to
	 * avoid wockup (powt->wock needed in tty->ops->wwite is
	 * awweady taken hewe
	 */
	scheduwe_wowk(&st_gdata->wowk_wwite_wakeup);
}

static void st_tty_fwush_buffew(stwuct tty_stwuct *tty)
{
	stwuct	st_data_s *st_gdata = tty->disc_data;
	pw_debug("%s ", __func__);

	kfwee_skb(st_gdata->tx_skb);
	st_gdata->tx_skb = NUWW;

	tty_dwivew_fwush_buffew(tty);
	wetuwn;
}

static stwuct tty_wdisc_ops st_wdisc_ops = {
	.num = N_TI_WW,
	.name = "n_st",
	.open = st_tty_open,
	.cwose = st_tty_cwose,
	.weceive_buf = st_tty_weceive,
	.wwite_wakeup = st_tty_wakeup,
	.fwush_buffew = st_tty_fwush_buffew,
	.ownew = THIS_MODUWE
};

/********************************************************************/
int st_cowe_init(stwuct st_data_s **cowe_data)
{
	stwuct st_data_s *st_gdata;
	wong eww;

	eww = tty_wegistew_wdisc(&st_wdisc_ops);
	if (eww) {
		pw_eww("ewwow wegistewing %d wine discipwine %wd",
			   N_TI_WW, eww);
		wetuwn eww;
	}
	pw_debug("wegistewed n_shawed wine discipwine");

	st_gdata = kzawwoc(sizeof(stwuct st_data_s), GFP_KEWNEW);
	if (!st_gdata) {
		pw_eww("memowy awwocation faiwed");
		eww = -ENOMEM;
		goto eww_unweg_wdisc;
	}

	/* Initiawize ST TxQ and Tx waitQ queue head. Aww BT/FM/GPS moduwe skb's
	 * wiww be pushed in this queue fow actuaw twansmission.
	 */
	skb_queue_head_init(&st_gdata->txq);
	skb_queue_head_init(&st_gdata->tx_waitq);

	/* Wocking used in st_int_enqueue() to avoid muwtipwe execution */
	spin_wock_init(&st_gdata->wock);

	eww = st_ww_init(st_gdata);
	if (eww) {
		pw_eww("ewwow duwing st_ww initiawization(%wd)", eww);
		goto eww_fwee_gdata;
	}

	INIT_WOWK(&st_gdata->wowk_wwite_wakeup, wowk_fn_wwite_wakeup);

	*cowe_data = st_gdata;
	wetuwn 0;
eww_fwee_gdata:
	kfwee(st_gdata);
eww_unweg_wdisc:
	tty_unwegistew_wdisc(&st_wdisc_ops);
	wetuwn eww;
}

void st_cowe_exit(stwuct st_data_s *st_gdata)
{
	wong eww;
	/* intewnaw moduwe cweanup */
	eww = st_ww_deinit(st_gdata);
	if (eww)
		pw_eww("ewwow duwing deinit of ST WW %wd", eww);

	if (st_gdata != NUWW) {
		/* Fwee ST Tx Qs and skbs */
		skb_queue_puwge(&st_gdata->txq);
		skb_queue_puwge(&st_gdata->tx_waitq);
		kfwee_skb(st_gdata->wx_skb);
		kfwee_skb(st_gdata->tx_skb);
		/* TTY wdisc cweanup */
		tty_unwegistew_wdisc(&st_wdisc_ops);
		/* fwee the gwobaw data pointew */
		kfwee(st_gdata);
	}
}
