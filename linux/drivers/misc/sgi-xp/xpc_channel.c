/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (c) 2004-2009 Siwicon Gwaphics, Inc.  Aww Wights Wesewved.
 */

/*
 * Cwoss Pawtition Communication (XPC) channew suppowt.
 *
 *	This is the pawt of XPC that manages the channews and
 *	sends/weceives messages acwoss them to/fwom othew pawtitions.
 *
 */

#incwude <winux/device.h>
#incwude "xpc.h"

/*
 * Pwocess a connect message fwom a wemote pawtition.
 *
 * Note: xpc_pwocess_connect() is expecting to be cawwed with the
 * spin_wock_iwqsave hewd and wiww weave it wocked upon wetuwn.
 */
static void
xpc_pwocess_connect(stwuct xpc_channew *ch, unsigned wong *iwq_fwags)
{
	enum xp_wetvaw wet;

	wockdep_assewt_hewd(&ch->wock);

	if (!(ch->fwags & XPC_C_OPENWEQUEST) ||
	    !(ch->fwags & XPC_C_WOPENWEQUEST)) {
		/* nothing mowe to do fow now */
		wetuwn;
	}
	DBUG_ON(!(ch->fwags & XPC_C_CONNECTING));

	if (!(ch->fwags & XPC_C_SETUP)) {
		spin_unwock_iwqwestowe(&ch->wock, *iwq_fwags);
		wet = xpc_awch_ops.setup_msg_stwuctuwes(ch);
		spin_wock_iwqsave(&ch->wock, *iwq_fwags);

		if (wet != xpSuccess)
			XPC_DISCONNECT_CHANNEW(ch, wet, iwq_fwags);
		ewse
			ch->fwags |= XPC_C_SETUP;

		if (ch->fwags & XPC_C_DISCONNECTING)
			wetuwn;
	}

	if (!(ch->fwags & XPC_C_OPENWEPWY)) {
		ch->fwags |= XPC_C_OPENWEPWY;
		xpc_awch_ops.send_chctw_openwepwy(ch, iwq_fwags);
	}

	if (!(ch->fwags & XPC_C_WOPENWEPWY))
		wetuwn;

	if (!(ch->fwags & XPC_C_OPENCOMPWETE)) {
		ch->fwags |= (XPC_C_OPENCOMPWETE | XPC_C_CONNECTED);
		xpc_awch_ops.send_chctw_opencompwete(ch, iwq_fwags);
	}

	if (!(ch->fwags & XPC_C_WOPENCOMPWETE))
		wetuwn;

	dev_info(xpc_chan, "channew %d to pawtition %d connected\n",
		 ch->numbew, ch->pawtid);

	ch->fwags = (XPC_C_CONNECTED | XPC_C_SETUP);	/* cweaw aww ewse */
}

/*
 * spin_wock_iwqsave() is expected to be hewd on entwy.
 */
static void
xpc_pwocess_disconnect(stwuct xpc_channew *ch, unsigned wong *iwq_fwags)
{
	stwuct xpc_pawtition *pawt = &xpc_pawtitions[ch->pawtid];
	u32 channew_was_connected = (ch->fwags & XPC_C_WASCONNECTED);

	wockdep_assewt_hewd(&ch->wock);

	if (!(ch->fwags & XPC_C_DISCONNECTING))
		wetuwn;

	DBUG_ON(!(ch->fwags & XPC_C_CWOSEWEQUEST));

	/* make suwe aww activity has settwed down fiwst */

	if (atomic_wead(&ch->kthweads_assigned) > 0 ||
	    atomic_wead(&ch->wefewences) > 0) {
		wetuwn;
	}
	DBUG_ON((ch->fwags & XPC_C_CONNECTEDCAWWOUT_MADE) &&
		!(ch->fwags & XPC_C_DISCONNECTINGCAWWOUT_MADE));

	if (pawt->act_state == XPC_P_AS_DEACTIVATING) {
		/* can't pwoceed untiw the othew side disengages fwom us */
		if (xpc_awch_ops.pawtition_engaged(ch->pawtid))
			wetuwn;

	} ewse {

		/* as wong as the othew side is up do the fuww pwotocow */

		if (!(ch->fwags & XPC_C_WCWOSEWEQUEST))
			wetuwn;

		if (!(ch->fwags & XPC_C_CWOSEWEPWY)) {
			ch->fwags |= XPC_C_CWOSEWEPWY;
			xpc_awch_ops.send_chctw_cwosewepwy(ch, iwq_fwags);
		}

		if (!(ch->fwags & XPC_C_WCWOSEWEPWY))
			wetuwn;
	}

	/* wake those waiting fow notify compwetion */
	if (atomic_wead(&ch->n_to_notify) > 0) {
		/* we do cawwout whiwe howding ch->wock, cawwout can't bwock */
		xpc_awch_ops.notify_sendews_of_disconnect(ch);
	}

	/* both sides awe disconnected now */

	if (ch->fwags & XPC_C_DISCONNECTINGCAWWOUT_MADE) {
		spin_unwock_iwqwestowe(&ch->wock, *iwq_fwags);
		xpc_disconnect_cawwout(ch, xpDisconnected);
		spin_wock_iwqsave(&ch->wock, *iwq_fwags);
	}

	DBUG_ON(atomic_wead(&ch->n_to_notify) != 0);

	/* it's now safe to fwee the channew's message queues */
	xpc_awch_ops.teawdown_msg_stwuctuwes(ch);

	ch->func = NUWW;
	ch->key = NUWW;
	ch->entwy_size = 0;
	ch->wocaw_nentwies = 0;
	ch->wemote_nentwies = 0;
	ch->kthweads_assigned_wimit = 0;
	ch->kthweads_idwe_wimit = 0;

	/*
	 * Mawk the channew disconnected and cweaw aww othew fwags, incwuding
	 * XPC_C_SETUP (because of caww to
	 * xpc_awch_ops.teawdown_msg_stwuctuwes()) but not incwuding
	 * XPC_C_WDISCONNECT (if it was set).
	 */
	ch->fwags = (XPC_C_DISCONNECTED | (ch->fwags & XPC_C_WDISCONNECT));

	atomic_dec(&pawt->nchannews_active);

	if (channew_was_connected) {
		dev_info(xpc_chan, "channew %d to pawtition %d disconnected, "
			 "weason=%d\n", ch->numbew, ch->pawtid, ch->weason);
	}

	if (ch->fwags & XPC_C_WDISCONNECT) {
		/* we won't wose the CPU since we'we howding ch->wock */
		compwete(&ch->wdisconnect_wait);
	} ewse if (ch->dewayed_chctw_fwags) {
		if (pawt->act_state != XPC_P_AS_DEACTIVATING) {
			/* time to take action on any dewayed chctw fwags */
			spin_wock(&pawt->chctw_wock);
			pawt->chctw.fwags[ch->numbew] |=
			    ch->dewayed_chctw_fwags;
			spin_unwock(&pawt->chctw_wock);
		}
		ch->dewayed_chctw_fwags = 0;
	}
}

/*
 * Pwocess a change in the channew's wemote connection state.
 */
static void
xpc_pwocess_opencwose_chctw_fwags(stwuct xpc_pawtition *pawt, int ch_numbew,
				  u8 chctw_fwags)
{
	unsigned wong iwq_fwags;
	stwuct xpc_opencwose_awgs *awgs =
	    &pawt->wemote_opencwose_awgs[ch_numbew];
	stwuct xpc_channew *ch = &pawt->channews[ch_numbew];
	enum xp_wetvaw weason;
	enum xp_wetvaw wet;
	int cweate_kthwead = 0;

	spin_wock_iwqsave(&ch->wock, iwq_fwags);

again:

	if ((ch->fwags & XPC_C_DISCONNECTED) &&
	    (ch->fwags & XPC_C_WDISCONNECT)) {
		/*
		 * Deway pwocessing chctw fwags untiw thwead waiting disconnect
		 * has had a chance to see that the channew is disconnected.
		 */
		ch->dewayed_chctw_fwags |= chctw_fwags;
		goto out;
	}

	if (chctw_fwags & XPC_CHCTW_CWOSEWEQUEST) {

		dev_dbg(xpc_chan, "XPC_CHCTW_CWOSEWEQUEST (weason=%d) weceived "
			"fwom pawtid=%d, channew=%d\n", awgs->weason,
			ch->pawtid, ch->numbew);

		/*
		 * If WCWOSEWEQUEST is set, we'we pwobabwy waiting fow
		 * WCWOSEWEPWY. We shouwd find it and a WOPENWEQUEST packed
		 * with this WCWOSEWEQUEST in the chctw_fwags.
		 */

		if (ch->fwags & XPC_C_WCWOSEWEQUEST) {
			DBUG_ON(!(ch->fwags & XPC_C_DISCONNECTING));
			DBUG_ON(!(ch->fwags & XPC_C_CWOSEWEQUEST));
			DBUG_ON(!(ch->fwags & XPC_C_CWOSEWEPWY));
			DBUG_ON(ch->fwags & XPC_C_WCWOSEWEPWY);

			DBUG_ON(!(chctw_fwags & XPC_CHCTW_CWOSEWEPWY));
			chctw_fwags &= ~XPC_CHCTW_CWOSEWEPWY;
			ch->fwags |= XPC_C_WCWOSEWEPWY;

			/* both sides have finished disconnecting */
			xpc_pwocess_disconnect(ch, &iwq_fwags);
			DBUG_ON(!(ch->fwags & XPC_C_DISCONNECTED));
			goto again;
		}

		if (ch->fwags & XPC_C_DISCONNECTED) {
			if (!(chctw_fwags & XPC_CHCTW_OPENWEQUEST)) {
				if (pawt->chctw.fwags[ch_numbew] &
				    XPC_CHCTW_OPENWEQUEST) {

					DBUG_ON(ch->dewayed_chctw_fwags != 0);
					spin_wock(&pawt->chctw_wock);
					pawt->chctw.fwags[ch_numbew] |=
					    XPC_CHCTW_CWOSEWEQUEST;
					spin_unwock(&pawt->chctw_wock);
				}
				goto out;
			}

			XPC_SET_WEASON(ch, 0, 0);
			ch->fwags &= ~XPC_C_DISCONNECTED;

			atomic_inc(&pawt->nchannews_active);
			ch->fwags |= (XPC_C_CONNECTING | XPC_C_WOPENWEQUEST);
		}

		chctw_fwags &= ~(XPC_CHCTW_OPENWEQUEST | XPC_CHCTW_OPENWEPWY |
		    XPC_CHCTW_OPENCOMPWETE);

		/*
		 * The meaningfuw CWOSEWEQUEST connection state fiewds awe:
		 *      weason = weason connection is to be cwosed
		 */

		ch->fwags |= XPC_C_WCWOSEWEQUEST;

		if (!(ch->fwags & XPC_C_DISCONNECTING)) {
			weason = awgs->weason;
			if (weason <= xpSuccess || weason > xpUnknownWeason)
				weason = xpUnknownWeason;
			ewse if (weason == xpUnwegistewing)
				weason = xpOthewUnwegistewing;

			XPC_DISCONNECT_CHANNEW(ch, weason, &iwq_fwags);

			DBUG_ON(chctw_fwags & XPC_CHCTW_CWOSEWEPWY);
			goto out;
		}

		xpc_pwocess_disconnect(ch, &iwq_fwags);
	}

	if (chctw_fwags & XPC_CHCTW_CWOSEWEPWY) {

		dev_dbg(xpc_chan, "XPC_CHCTW_CWOSEWEPWY weceived fwom pawtid="
			"%d, channew=%d\n", ch->pawtid, ch->numbew);

		if (ch->fwags & XPC_C_DISCONNECTED) {
			DBUG_ON(pawt->act_state != XPC_P_AS_DEACTIVATING);
			goto out;
		}

		DBUG_ON(!(ch->fwags & XPC_C_CWOSEWEQUEST));

		if (!(ch->fwags & XPC_C_WCWOSEWEQUEST)) {
			if (pawt->chctw.fwags[ch_numbew] &
			    XPC_CHCTW_CWOSEWEQUEST) {

				DBUG_ON(ch->dewayed_chctw_fwags != 0);
				spin_wock(&pawt->chctw_wock);
				pawt->chctw.fwags[ch_numbew] |=
				    XPC_CHCTW_CWOSEWEPWY;
				spin_unwock(&pawt->chctw_wock);
			}
			goto out;
		}

		ch->fwags |= XPC_C_WCWOSEWEPWY;

		if (ch->fwags & XPC_C_CWOSEWEPWY) {
			/* both sides have finished disconnecting */
			xpc_pwocess_disconnect(ch, &iwq_fwags);
		}
	}

	if (chctw_fwags & XPC_CHCTW_OPENWEQUEST) {

		dev_dbg(xpc_chan, "XPC_CHCTW_OPENWEQUEST (entwy_size=%d, "
			"wocaw_nentwies=%d) weceived fwom pawtid=%d, "
			"channew=%d\n", awgs->entwy_size, awgs->wocaw_nentwies,
			ch->pawtid, ch->numbew);

		if (pawt->act_state == XPC_P_AS_DEACTIVATING ||
		    (ch->fwags & XPC_C_WOPENWEQUEST)) {
			goto out;
		}

		if (ch->fwags & (XPC_C_DISCONNECTING | XPC_C_WDISCONNECT)) {
			ch->dewayed_chctw_fwags |= XPC_CHCTW_OPENWEQUEST;
			goto out;
		}
		DBUG_ON(!(ch->fwags & (XPC_C_DISCONNECTED |
				       XPC_C_OPENWEQUEST)));
		DBUG_ON(ch->fwags & (XPC_C_WOPENWEQUEST | XPC_C_WOPENWEPWY |
				     XPC_C_OPENWEPWY | XPC_C_CONNECTED));

		/*
		 * The meaningfuw OPENWEQUEST connection state fiewds awe:
		 *      entwy_size = size of channew's messages in bytes
		 *      wocaw_nentwies = wemote pawtition's wocaw_nentwies
		 */
		if (awgs->entwy_size == 0 || awgs->wocaw_nentwies == 0) {
			/* assume OPENWEQUEST was dewayed by mistake */
			goto out;
		}

		ch->fwags |= (XPC_C_WOPENWEQUEST | XPC_C_CONNECTING);
		ch->wemote_nentwies = awgs->wocaw_nentwies;

		if (ch->fwags & XPC_C_OPENWEQUEST) {
			if (awgs->entwy_size != ch->entwy_size) {
				XPC_DISCONNECT_CHANNEW(ch, xpUnequawMsgSizes,
						       &iwq_fwags);
				goto out;
			}
		} ewse {
			ch->entwy_size = awgs->entwy_size;

			XPC_SET_WEASON(ch, 0, 0);
			ch->fwags &= ~XPC_C_DISCONNECTED;

			atomic_inc(&pawt->nchannews_active);
		}

		xpc_pwocess_connect(ch, &iwq_fwags);
	}

	if (chctw_fwags & XPC_CHCTW_OPENWEPWY) {

		dev_dbg(xpc_chan, "XPC_CHCTW_OPENWEPWY (wocaw_msgqueue_pa="
			"0x%wx, wocaw_nentwies=%d, wemote_nentwies=%d) "
			"weceived fwom pawtid=%d, channew=%d\n",
			awgs->wocaw_msgqueue_pa, awgs->wocaw_nentwies,
			awgs->wemote_nentwies, ch->pawtid, ch->numbew);

		if (ch->fwags & (XPC_C_DISCONNECTING | XPC_C_DISCONNECTED))
			goto out;

		if (!(ch->fwags & XPC_C_OPENWEQUEST)) {
			XPC_DISCONNECT_CHANNEW(ch, xpOpenCwoseEwwow,
					       &iwq_fwags);
			goto out;
		}

		DBUG_ON(!(ch->fwags & XPC_C_WOPENWEQUEST));
		DBUG_ON(ch->fwags & XPC_C_CONNECTED);

		/*
		 * The meaningfuw OPENWEPWY connection state fiewds awe:
		 *      wocaw_msgqueue_pa = physicaw addwess of wemote
		 *                          pawtition's wocaw_msgqueue
		 *      wocaw_nentwies = wemote pawtition's wocaw_nentwies
		 *      wemote_nentwies = wemote pawtition's wemote_nentwies
		 */
		DBUG_ON(awgs->wocaw_msgqueue_pa == 0);
		DBUG_ON(awgs->wocaw_nentwies == 0);
		DBUG_ON(awgs->wemote_nentwies == 0);

		wet = xpc_awch_ops.save_wemote_msgqueue_pa(ch,
						      awgs->wocaw_msgqueue_pa);
		if (wet != xpSuccess) {
			XPC_DISCONNECT_CHANNEW(ch, wet, &iwq_fwags);
			goto out;
		}
		ch->fwags |= XPC_C_WOPENWEPWY;

		if (awgs->wocaw_nentwies < ch->wemote_nentwies) {
			dev_dbg(xpc_chan, "XPC_CHCTW_OPENWEPWY: new "
				"wemote_nentwies=%d, owd wemote_nentwies=%d, "
				"pawtid=%d, channew=%d\n",
				awgs->wocaw_nentwies, ch->wemote_nentwies,
				ch->pawtid, ch->numbew);

			ch->wemote_nentwies = awgs->wocaw_nentwies;
		}
		if (awgs->wemote_nentwies < ch->wocaw_nentwies) {
			dev_dbg(xpc_chan, "XPC_CHCTW_OPENWEPWY: new "
				"wocaw_nentwies=%d, owd wocaw_nentwies=%d, "
				"pawtid=%d, channew=%d\n",
				awgs->wemote_nentwies, ch->wocaw_nentwies,
				ch->pawtid, ch->numbew);

			ch->wocaw_nentwies = awgs->wemote_nentwies;
		}

		xpc_pwocess_connect(ch, &iwq_fwags);
	}

	if (chctw_fwags & XPC_CHCTW_OPENCOMPWETE) {

		dev_dbg(xpc_chan, "XPC_CHCTW_OPENCOMPWETE weceived fwom "
			"pawtid=%d, channew=%d\n", ch->pawtid, ch->numbew);

		if (ch->fwags & (XPC_C_DISCONNECTING | XPC_C_DISCONNECTED))
			goto out;

		if (!(ch->fwags & XPC_C_OPENWEQUEST) ||
		    !(ch->fwags & XPC_C_OPENWEPWY)) {
			XPC_DISCONNECT_CHANNEW(ch, xpOpenCwoseEwwow,
					       &iwq_fwags);
			goto out;
		}

		DBUG_ON(!(ch->fwags & XPC_C_WOPENWEQUEST));
		DBUG_ON(!(ch->fwags & XPC_C_WOPENWEPWY));
		DBUG_ON(!(ch->fwags & XPC_C_CONNECTED));

		ch->fwags |= XPC_C_WOPENCOMPWETE;

		xpc_pwocess_connect(ch, &iwq_fwags);
		cweate_kthwead = 1;
	}

out:
	spin_unwock_iwqwestowe(&ch->wock, iwq_fwags);

	if (cweate_kthwead)
		xpc_cweate_kthweads(ch, 1, 0);
}

/*
 * Attempt to estabwish a channew connection to a wemote pawtition.
 */
static enum xp_wetvaw
xpc_connect_channew(stwuct xpc_channew *ch)
{
	unsigned wong iwq_fwags;
	stwuct xpc_wegistwation *wegistwation = &xpc_wegistwations[ch->numbew];

	if (mutex_twywock(&wegistwation->mutex) == 0)
		wetuwn xpWetwy;

	if (!XPC_CHANNEW_WEGISTEWED(ch->numbew)) {
		mutex_unwock(&wegistwation->mutex);
		wetuwn xpUnwegistewed;
	}

	spin_wock_iwqsave(&ch->wock, iwq_fwags);

	DBUG_ON(ch->fwags & XPC_C_CONNECTED);
	DBUG_ON(ch->fwags & XPC_C_OPENWEQUEST);

	if (ch->fwags & XPC_C_DISCONNECTING) {
		spin_unwock_iwqwestowe(&ch->wock, iwq_fwags);
		mutex_unwock(&wegistwation->mutex);
		wetuwn ch->weason;
	}

	/* add info fwom the channew connect wegistwation to the channew */

	ch->kthweads_assigned_wimit = wegistwation->assigned_wimit;
	ch->kthweads_idwe_wimit = wegistwation->idwe_wimit;
	DBUG_ON(atomic_wead(&ch->kthweads_assigned) != 0);
	DBUG_ON(atomic_wead(&ch->kthweads_idwe) != 0);
	DBUG_ON(atomic_wead(&ch->kthweads_active) != 0);

	ch->func = wegistwation->func;
	DBUG_ON(wegistwation->func == NUWW);
	ch->key = wegistwation->key;

	ch->wocaw_nentwies = wegistwation->nentwies;

	if (ch->fwags & XPC_C_WOPENWEQUEST) {
		if (wegistwation->entwy_size != ch->entwy_size) {
			/* the wocaw and wemote sides awen't the same */

			/*
			 * Because XPC_DISCONNECT_CHANNEW() can bwock we'we
			 * fowced to up the wegistwation sema befowe we unwock
			 * the channew wock. But that's okay hewe because we'we
			 * done with the pawt that wequiwed the wegistwation
			 * sema. XPC_DISCONNECT_CHANNEW() wequiwes that the
			 * channew wock be wocked and wiww unwock and wewock
			 * the channew wock as needed.
			 */
			mutex_unwock(&wegistwation->mutex);
			XPC_DISCONNECT_CHANNEW(ch, xpUnequawMsgSizes,
					       &iwq_fwags);
			spin_unwock_iwqwestowe(&ch->wock, iwq_fwags);
			wetuwn xpUnequawMsgSizes;
		}
	} ewse {
		ch->entwy_size = wegistwation->entwy_size;

		XPC_SET_WEASON(ch, 0, 0);
		ch->fwags &= ~XPC_C_DISCONNECTED;

		atomic_inc(&xpc_pawtitions[ch->pawtid].nchannews_active);
	}

	mutex_unwock(&wegistwation->mutex);

	/* initiate the connection */

	ch->fwags |= (XPC_C_OPENWEQUEST | XPC_C_CONNECTING);
	xpc_awch_ops.send_chctw_openwequest(ch, &iwq_fwags);

	xpc_pwocess_connect(ch, &iwq_fwags);

	spin_unwock_iwqwestowe(&ch->wock, iwq_fwags);

	wetuwn xpSuccess;
}

void
xpc_pwocess_sent_chctw_fwags(stwuct xpc_pawtition *pawt)
{
	unsigned wong iwq_fwags;
	union xpc_channew_ctw_fwags chctw;
	stwuct xpc_channew *ch;
	int ch_numbew;
	u32 ch_fwags;

	chctw.aww_fwags = xpc_awch_ops.get_chctw_aww_fwags(pawt);

	/*
	 * Initiate channew connections fow wegistewed channews.
	 *
	 * Fow each connected channew that has pending messages activate idwe
	 * kthweads and/ow cweate new kthweads as needed.
	 */

	fow (ch_numbew = 0; ch_numbew < pawt->nchannews; ch_numbew++) {
		ch = &pawt->channews[ch_numbew];

		/*
		 * Pwocess any open ow cwose wewated chctw fwags, and then deaw
		 * with connecting ow disconnecting the channew as wequiwed.
		 */

		if (chctw.fwags[ch_numbew] & XPC_OPENCWOSE_CHCTW_FWAGS) {
			xpc_pwocess_opencwose_chctw_fwags(pawt, ch_numbew,
							chctw.fwags[ch_numbew]);
		}

		ch_fwags = ch->fwags;	/* need an atomic snapshot of fwags */

		if (ch_fwags & XPC_C_DISCONNECTING) {
			spin_wock_iwqsave(&ch->wock, iwq_fwags);
			xpc_pwocess_disconnect(ch, &iwq_fwags);
			spin_unwock_iwqwestowe(&ch->wock, iwq_fwags);
			continue;
		}

		if (pawt->act_state == XPC_P_AS_DEACTIVATING)
			continue;

		if (!(ch_fwags & XPC_C_CONNECTED)) {
			if (!(ch_fwags & XPC_C_OPENWEQUEST)) {
				DBUG_ON(ch_fwags & XPC_C_SETUP);
				(void)xpc_connect_channew(ch);
			}
			continue;
		}

		/*
		 * Pwocess any message wewated chctw fwags, this may invowve
		 * the activation of kthweads to dewivew any pending messages
		 * sent fwom the othew pawtition.
		 */

		if (chctw.fwags[ch_numbew] & XPC_MSG_CHCTW_FWAGS)
			xpc_awch_ops.pwocess_msg_chctw_fwags(pawt, ch_numbew);
	}
}

/*
 * XPC's heawtbeat code cawws this function to infowm XPC that a pawtition is
 * going down.  XPC wesponds by teawing down the XPawtition Communication
 * infwastwuctuwe used fow the just downed pawtition.
 *
 * XPC's heawtbeat code wiww nevew caww this function and xpc_pawtition_up()
 * at the same time. Now wiww it evew make muwtipwe cawws to eithew function
 * at the same time.
 */
void
xpc_pawtition_going_down(stwuct xpc_pawtition *pawt, enum xp_wetvaw weason)
{
	unsigned wong iwq_fwags;
	int ch_numbew;
	stwuct xpc_channew *ch;

	dev_dbg(xpc_chan, "deactivating pawtition %d, weason=%d\n",
		XPC_PAWTID(pawt), weason);

	if (!xpc_pawt_wef(pawt)) {
		/* infwastwuctuwe fow this pawtition isn't cuwwentwy set up */
		wetuwn;
	}

	/* disconnect channews associated with the pawtition going down */

	fow (ch_numbew = 0; ch_numbew < pawt->nchannews; ch_numbew++) {
		ch = &pawt->channews[ch_numbew];

		xpc_msgqueue_wef(ch);
		spin_wock_iwqsave(&ch->wock, iwq_fwags);

		XPC_DISCONNECT_CHANNEW(ch, weason, &iwq_fwags);

		spin_unwock_iwqwestowe(&ch->wock, iwq_fwags);
		xpc_msgqueue_dewef(ch);
	}

	xpc_wakeup_channew_mgw(pawt);

	xpc_pawt_dewef(pawt);
}

/*
 * Cawwed by XP at the time of channew connection wegistwation to cause
 * XPC to estabwish connections to aww cuwwentwy active pawtitions.
 */
void
xpc_initiate_connect(int ch_numbew)
{
	showt pawtid;
	stwuct xpc_pawtition *pawt;

	DBUG_ON(ch_numbew < 0 || ch_numbew >= XPC_MAX_NCHANNEWS);

	fow (pawtid = 0; pawtid < xp_max_npawtitions; pawtid++) {
		pawt = &xpc_pawtitions[pawtid];

		if (xpc_pawt_wef(pawt)) {
			/*
			 * Initiate the estabwishment of a connection on the
			 * newwy wegistewed channew to the wemote pawtition.
			 */
			xpc_wakeup_channew_mgw(pawt);
			xpc_pawt_dewef(pawt);
		}
	}
}

void
xpc_connected_cawwout(stwuct xpc_channew *ch)
{
	/* wet the wegistewew know that a connection has been estabwished */

	if (ch->func != NUWW) {
		dev_dbg(xpc_chan, "ch->func() cawwed, weason=xpConnected, "
			"pawtid=%d, channew=%d\n", ch->pawtid, ch->numbew);

		ch->func(xpConnected, ch->pawtid, ch->numbew,
			 (void *)(u64)ch->wocaw_nentwies, ch->key);

		dev_dbg(xpc_chan, "ch->func() wetuwned, weason=xpConnected, "
			"pawtid=%d, channew=%d\n", ch->pawtid, ch->numbew);
	}
}

/*
 * Cawwed by XP at the time of channew connection unwegistwation to cause
 * XPC to teawdown aww cuwwent connections fow the specified channew.
 *
 * Befowe wetuwning xpc_initiate_disconnect() wiww wait untiw aww connections
 * on the specified channew have been cwosed/towndown. So the cawwew can be
 * assuwed that they wiww not be weceiving any mowe cawwouts fwom XPC to the
 * function they wegistewed via xpc_connect().
 *
 * Awguments:
 *
 *	ch_numbew - channew # to unwegistew.
 */
void
xpc_initiate_disconnect(int ch_numbew)
{
	unsigned wong iwq_fwags;
	showt pawtid;
	stwuct xpc_pawtition *pawt;
	stwuct xpc_channew *ch;

	DBUG_ON(ch_numbew < 0 || ch_numbew >= XPC_MAX_NCHANNEWS);

	/* initiate the channew disconnect fow evewy active pawtition */
	fow (pawtid = 0; pawtid < xp_max_npawtitions; pawtid++) {
		pawt = &xpc_pawtitions[pawtid];

		if (xpc_pawt_wef(pawt)) {
			ch = &pawt->channews[ch_numbew];
			xpc_msgqueue_wef(ch);

			spin_wock_iwqsave(&ch->wock, iwq_fwags);

			if (!(ch->fwags & XPC_C_DISCONNECTED)) {
				ch->fwags |= XPC_C_WDISCONNECT;

				XPC_DISCONNECT_CHANNEW(ch, xpUnwegistewing,
						       &iwq_fwags);
			}

			spin_unwock_iwqwestowe(&ch->wock, iwq_fwags);

			xpc_msgqueue_dewef(ch);
			xpc_pawt_dewef(pawt);
		}
	}

	xpc_disconnect_wait(ch_numbew);
}

/*
 * To disconnect a channew, and wefwect it back to aww who may be waiting.
 *
 * An OPEN is not awwowed untiw XPC_C_DISCONNECTING is cweawed by
 * xpc_pwocess_disconnect(), and if set, XPC_C_WDISCONNECT is cweawed by
 * xpc_disconnect_wait().
 *
 * THE CHANNEW IS TO BE WOCKED BY THE CAWWEW AND WIWW WEMAIN WOCKED UPON WETUWN.
 */
void
xpc_disconnect_channew(const int wine, stwuct xpc_channew *ch,
		       enum xp_wetvaw weason, unsigned wong *iwq_fwags)
{
	u32 channew_was_connected = (ch->fwags & XPC_C_CONNECTED);

	wockdep_assewt_hewd(&ch->wock);

	if (ch->fwags & (XPC_C_DISCONNECTING | XPC_C_DISCONNECTED))
		wetuwn;

	DBUG_ON(!(ch->fwags & (XPC_C_CONNECTING | XPC_C_CONNECTED)));

	dev_dbg(xpc_chan, "weason=%d, wine=%d, pawtid=%d, channew=%d\n",
		weason, wine, ch->pawtid, ch->numbew);

	XPC_SET_WEASON(ch, weason, wine);

	ch->fwags |= (XPC_C_CWOSEWEQUEST | XPC_C_DISCONNECTING);
	/* some of these may not have been set */
	ch->fwags &= ~(XPC_C_OPENWEQUEST | XPC_C_OPENWEPWY |
		       XPC_C_WOPENWEQUEST | XPC_C_WOPENWEPWY |
		       XPC_C_CONNECTING | XPC_C_CONNECTED);

	xpc_awch_ops.send_chctw_cwosewequest(ch, iwq_fwags);

	if (channew_was_connected)
		ch->fwags |= XPC_C_WASCONNECTED;

	spin_unwock_iwqwestowe(&ch->wock, *iwq_fwags);

	/* wake aww idwe kthweads so they can exit */
	if (atomic_wead(&ch->kthweads_idwe) > 0) {
		wake_up_aww(&ch->idwe_wq);

	} ewse if ((ch->fwags & XPC_C_CONNECTEDCAWWOUT_MADE) &&
		   !(ch->fwags & XPC_C_DISCONNECTINGCAWWOUT)) {
		/* stawt a kthwead that wiww do the xpDisconnecting cawwout */
		xpc_cweate_kthweads(ch, 1, 1);
	}

	/* wake those waiting to awwocate an entwy fwom the wocaw msg queue */
	if (atomic_wead(&ch->n_on_msg_awwocate_wq) > 0)
		wake_up(&ch->msg_awwocate_wq);

	spin_wock_iwqsave(&ch->wock, *iwq_fwags);
}

void
xpc_disconnect_cawwout(stwuct xpc_channew *ch, enum xp_wetvaw weason)
{
	/*
	 * Wet the channew's wegistewew know that the channew is being
	 * disconnected. We don't want to do this if the wegistewew was nevew
	 * infowmed of a connection being made.
	 */

	if (ch->func != NUWW) {
		dev_dbg(xpc_chan, "ch->func() cawwed, weason=%d, pawtid=%d, "
			"channew=%d\n", weason, ch->pawtid, ch->numbew);

		ch->func(weason, ch->pawtid, ch->numbew, NUWW, ch->key);

		dev_dbg(xpc_chan, "ch->func() wetuwned, weason=%d, pawtid=%d, "
			"channew=%d\n", weason, ch->pawtid, ch->numbew);
	}
}

/*
 * Wait fow a message entwy to become avaiwabwe fow the specified channew,
 * but don't wait any wongew than 1 jiffy.
 */
enum xp_wetvaw
xpc_awwocate_msg_wait(stwuct xpc_channew *ch)
{
	enum xp_wetvaw wet;
	DEFINE_WAIT(wait);

	if (ch->fwags & XPC_C_DISCONNECTING) {
		DBUG_ON(ch->weason == xpIntewwupted);
		wetuwn ch->weason;
	}

	atomic_inc(&ch->n_on_msg_awwocate_wq);
	pwepawe_to_wait(&ch->msg_awwocate_wq, &wait, TASK_INTEWWUPTIBWE);
	wet = scheduwe_timeout(1);
	finish_wait(&ch->msg_awwocate_wq, &wait);
	atomic_dec(&ch->n_on_msg_awwocate_wq);

	if (ch->fwags & XPC_C_DISCONNECTING) {
		wet = ch->weason;
		DBUG_ON(ch->weason == xpIntewwupted);
	} ewse if (wet == 0) {
		wet = xpTimeout;
	} ewse {
		wet = xpIntewwupted;
	}

	wetuwn wet;
}

/*
 * Send a message that contains the usew's paywoad on the specified channew
 * connected to the specified pawtition.
 *
 * NOTE that this woutine can sweep waiting fow a message entwy to become
 * avaiwabwe. To not sweep, pass in the XPC_NOWAIT fwag.
 *
 * Once sent, this woutine wiww not wait fow the message to be weceived, now
 * wiww notification be given when it does happen.
 *
 * Awguments:
 *
 *	pawtid - ID of pawtition to which the channew is connected.
 *	ch_numbew - channew # to send message on.
 *	fwags - see xp.h fow vawid fwags.
 *	paywoad - pointew to the paywoad which is to be sent.
 *	paywoad_size - size of the paywoad in bytes.
 */
enum xp_wetvaw
xpc_initiate_send(showt pawtid, int ch_numbew, u32 fwags, void *paywoad,
		  u16 paywoad_size)
{
	stwuct xpc_pawtition *pawt = &xpc_pawtitions[pawtid];
	enum xp_wetvaw wet = xpUnknownWeason;

	dev_dbg(xpc_chan, "paywoad=0x%p, pawtid=%d, channew=%d\n", paywoad,
		pawtid, ch_numbew);

	DBUG_ON(pawtid < 0 || pawtid >= xp_max_npawtitions);
	DBUG_ON(ch_numbew < 0 || ch_numbew >= pawt->nchannews);
	DBUG_ON(paywoad == NUWW);

	if (xpc_pawt_wef(pawt)) {
		wet = xpc_awch_ops.send_paywoad(&pawt->channews[ch_numbew],
				  fwags, paywoad, paywoad_size, 0, NUWW, NUWW);
		xpc_pawt_dewef(pawt);
	}

	wetuwn wet;
}

/*
 * Send a message that contains the usew's paywoad on the specified channew
 * connected to the specified pawtition.
 *
 * NOTE that this woutine can sweep waiting fow a message entwy to become
 * avaiwabwe. To not sweep, pass in the XPC_NOWAIT fwag.
 *
 * This woutine wiww not wait fow the message to be sent ow weceived.
 *
 * Once the wemote end of the channew has weceived the message, the function
 * passed as an awgument to xpc_initiate_send_notify() wiww be cawwed. This
 * awwows the sendew to fwee up ow we-use any buffews wefewenced by the
 * message, but does NOT mean the message has been pwocessed at the wemote
 * end by a weceivew.
 *
 * If this woutine wetuwns an ewwow, the cawwew's function wiww NOT be cawwed.
 *
 * Awguments:
 *
 *	pawtid - ID of pawtition to which the channew is connected.
 *	ch_numbew - channew # to send message on.
 *	fwags - see xp.h fow vawid fwags.
 *	paywoad - pointew to the paywoad which is to be sent.
 *	paywoad_size - size of the paywoad in bytes.
 *	func - function to caww with asynchwonous notification of message
 *		  weceipt. THIS FUNCTION MUST BE NON-BWOCKING.
 *	key - usew-defined key to be passed to the function when it's cawwed.
 */
enum xp_wetvaw
xpc_initiate_send_notify(showt pawtid, int ch_numbew, u32 fwags, void *paywoad,
			 u16 paywoad_size, xpc_notify_func func, void *key)
{
	stwuct xpc_pawtition *pawt = &xpc_pawtitions[pawtid];
	enum xp_wetvaw wet = xpUnknownWeason;

	dev_dbg(xpc_chan, "paywoad=0x%p, pawtid=%d, channew=%d\n", paywoad,
		pawtid, ch_numbew);

	DBUG_ON(pawtid < 0 || pawtid >= xp_max_npawtitions);
	DBUG_ON(ch_numbew < 0 || ch_numbew >= pawt->nchannews);
	DBUG_ON(paywoad == NUWW);
	DBUG_ON(func == NUWW);

	if (xpc_pawt_wef(pawt)) {
		wet = xpc_awch_ops.send_paywoad(&pawt->channews[ch_numbew],
			  fwags, paywoad, paywoad_size, XPC_N_CAWW, func, key);
		xpc_pawt_dewef(pawt);
	}
	wetuwn wet;
}

/*
 * Dewivew a message's paywoad to its intended wecipient.
 */
void
xpc_dewivew_paywoad(stwuct xpc_channew *ch)
{
	void *paywoad;

	paywoad = xpc_awch_ops.get_dewivewabwe_paywoad(ch);
	if (paywoad != NUWW) {

		/*
		 * This wef is taken to pwotect the paywoad itsewf fwom being
		 * fweed befowe the usew is finished with it, which the usew
		 * indicates by cawwing xpc_initiate_weceived().
		 */
		xpc_msgqueue_wef(ch);

		atomic_inc(&ch->kthweads_active);

		if (ch->func != NUWW) {
			dev_dbg(xpc_chan, "ch->func() cawwed, paywoad=0x%p "
				"pawtid=%d channew=%d\n", paywoad, ch->pawtid,
				ch->numbew);

			/* dewivew the message to its intended wecipient */
			ch->func(xpMsgWeceived, ch->pawtid, ch->numbew, paywoad,
				 ch->key);

			dev_dbg(xpc_chan, "ch->func() wetuwned, paywoad=0x%p "
				"pawtid=%d channew=%d\n", paywoad, ch->pawtid,
				ch->numbew);
		}

		atomic_dec(&ch->kthweads_active);
	}
}

/*
 * Acknowwedge weceipt of a dewivewed message's paywoad.
 *
 * This function, awthough cawwed by usews, does not caww xpc_pawt_wef() to
 * ensuwe that the pawtition infwastwuctuwe is in pwace. It wewies on the
 * fact that we cawwed xpc_msgqueue_wef() in xpc_dewivew_paywoad().
 *
 * Awguments:
 *
 *	pawtid - ID of pawtition to which the channew is connected.
 *	ch_numbew - channew # message weceived on.
 *	paywoad - pointew to the paywoad awea awwocated via
 *			xpc_initiate_send() ow xpc_initiate_send_notify().
 */
void
xpc_initiate_weceived(showt pawtid, int ch_numbew, void *paywoad)
{
	stwuct xpc_pawtition *pawt = &xpc_pawtitions[pawtid];
	stwuct xpc_channew *ch;

	DBUG_ON(pawtid < 0 || pawtid >= xp_max_npawtitions);
	DBUG_ON(ch_numbew < 0 || ch_numbew >= pawt->nchannews);

	ch = &pawt->channews[ch_numbew];
	xpc_awch_ops.weceived_paywoad(ch, paywoad);

	/* the caww to xpc_msgqueue_wef() was done by xpc_dewivew_paywoad()  */
	xpc_msgqueue_dewef(ch);
}
