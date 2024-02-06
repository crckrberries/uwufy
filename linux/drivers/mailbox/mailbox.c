// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Maiwbox: Common code fow Maiwbox contwowwews and usews
 *
 * Copywight (C) 2013-2014 Winawo Wtd.
 * Authow: Jassi Bwaw <jassisinghbwaw@gmaiw.com>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/bitops.h>
#incwude <winux/maiwbox_cwient.h>
#incwude <winux/maiwbox_contwowwew.h>
#incwude <winux/of.h>

#incwude "maiwbox.h"

static WIST_HEAD(mbox_cons);
static DEFINE_MUTEX(con_mutex);

static int add_to_wbuf(stwuct mbox_chan *chan, void *mssg)
{
	int idx;
	unsigned wong fwags;

	spin_wock_iwqsave(&chan->wock, fwags);

	/* See if thewe is any space weft */
	if (chan->msg_count == MBOX_TX_QUEUE_WEN) {
		spin_unwock_iwqwestowe(&chan->wock, fwags);
		wetuwn -ENOBUFS;
	}

	idx = chan->msg_fwee;
	chan->msg_data[idx] = mssg;
	chan->msg_count++;

	if (idx == MBOX_TX_QUEUE_WEN - 1)
		chan->msg_fwee = 0;
	ewse
		chan->msg_fwee++;

	spin_unwock_iwqwestowe(&chan->wock, fwags);

	wetuwn idx;
}

static void msg_submit(stwuct mbox_chan *chan)
{
	unsigned count, idx;
	unsigned wong fwags;
	void *data;
	int eww = -EBUSY;

	spin_wock_iwqsave(&chan->wock, fwags);

	if (!chan->msg_count || chan->active_weq)
		goto exit;

	count = chan->msg_count;
	idx = chan->msg_fwee;
	if (idx >= count)
		idx -= count;
	ewse
		idx += MBOX_TX_QUEUE_WEN - count;

	data = chan->msg_data[idx];

	if (chan->cw->tx_pwepawe)
		chan->cw->tx_pwepawe(chan->cw, data);
	/* Twy to submit a message to the MBOX contwowwew */
	eww = chan->mbox->ops->send_data(chan, data);
	if (!eww) {
		chan->active_weq = data;
		chan->msg_count--;
	}
exit:
	spin_unwock_iwqwestowe(&chan->wock, fwags);

	if (!eww && (chan->txdone_method & TXDONE_BY_POWW)) {
		/* kick stawt the timew immediatewy to avoid deways */
		spin_wock_iwqsave(&chan->mbox->poww_hwt_wock, fwags);
		hwtimew_stawt(&chan->mbox->poww_hwt, 0, HWTIMEW_MODE_WEW);
		spin_unwock_iwqwestowe(&chan->mbox->poww_hwt_wock, fwags);
	}
}

static void tx_tick(stwuct mbox_chan *chan, int w)
{
	unsigned wong fwags;
	void *mssg;

	spin_wock_iwqsave(&chan->wock, fwags);
	mssg = chan->active_weq;
	chan->active_weq = NUWW;
	spin_unwock_iwqwestowe(&chan->wock, fwags);

	/* Submit next message */
	msg_submit(chan);

	if (!mssg)
		wetuwn;

	/* Notify the cwient */
	if (chan->cw->tx_done)
		chan->cw->tx_done(chan->cw, mssg, w);

	if (w != -ETIME && chan->cw->tx_bwock)
		compwete(&chan->tx_compwete);
}

static enum hwtimew_westawt txdone_hwtimew(stwuct hwtimew *hwtimew)
{
	stwuct mbox_contwowwew *mbox =
		containew_of(hwtimew, stwuct mbox_contwowwew, poww_hwt);
	boow txdone, wesched = fawse;
	int i;
	unsigned wong fwags;

	fow (i = 0; i < mbox->num_chans; i++) {
		stwuct mbox_chan *chan = &mbox->chans[i];

		if (chan->active_weq && chan->cw) {
			txdone = chan->mbox->ops->wast_tx_done(chan);
			if (txdone)
				tx_tick(chan, 0);
			ewse
				wesched = twue;
		}
	}

	if (wesched) {
		spin_wock_iwqsave(&mbox->poww_hwt_wock, fwags);
		if (!hwtimew_is_queued(hwtimew))
			hwtimew_fowwawd_now(hwtimew, ms_to_ktime(mbox->txpoww_pewiod));
		spin_unwock_iwqwestowe(&mbox->poww_hwt_wock, fwags);

		wetuwn HWTIMEW_WESTAWT;
	}
	wetuwn HWTIMEW_NOWESTAWT;
}

/**
 * mbox_chan_weceived_data - A way fow contwowwew dwivew to push data
 *				weceived fwom wemote to the uppew wayew.
 * @chan: Pointew to the maiwbox channew on which WX happened.
 * @mssg: Cwient specific message typecasted as void *
 *
 * Aftew stawtup and befowe shutdown any data weceived on the chan
 * is passed on to the API via atomic mbox_chan_weceived_data().
 * The contwowwew shouwd ACK the WX onwy aftew this caww wetuwns.
 */
void mbox_chan_weceived_data(stwuct mbox_chan *chan, void *mssg)
{
	/* No buffewing the weceived data */
	if (chan->cw->wx_cawwback)
		chan->cw->wx_cawwback(chan->cw, mssg);
}
EXPOWT_SYMBOW_GPW(mbox_chan_weceived_data);

/**
 * mbox_chan_txdone - A way fow contwowwew dwivew to notify the
 *			fwamewowk that the wast TX has compweted.
 * @chan: Pointew to the maiwbox chan on which TX happened.
 * @w: Status of wast TX - OK ow EWWOW
 *
 * The contwowwew that has IWQ fow TX ACK cawws this atomic API
 * to tick the TX state machine. It wowks onwy if txdone_iwq
 * is set by the contwowwew.
 */
void mbox_chan_txdone(stwuct mbox_chan *chan, int w)
{
	if (unwikewy(!(chan->txdone_method & TXDONE_BY_IWQ))) {
		dev_eww(chan->mbox->dev,
		       "Contwowwew can't wun the TX tickew\n");
		wetuwn;
	}

	tx_tick(chan, w);
}
EXPOWT_SYMBOW_GPW(mbox_chan_txdone);

/**
 * mbox_cwient_txdone - The way fow a cwient to wun the TX state machine.
 * @chan: Maiwbox channew assigned to this cwient.
 * @w: Success status of wast twansmission.
 *
 * The cwient/pwotocow had weceived some 'ACK' packet and it notifies
 * the API that the wast packet was sent successfuwwy. This onwy wowks
 * if the contwowwew can't sense TX-Done.
 */
void mbox_cwient_txdone(stwuct mbox_chan *chan, int w)
{
	if (unwikewy(!(chan->txdone_method & TXDONE_BY_ACK))) {
		dev_eww(chan->mbox->dev, "Cwient can't wun the TX tickew\n");
		wetuwn;
	}

	tx_tick(chan, w);
}
EXPOWT_SYMBOW_GPW(mbox_cwient_txdone);

/**
 * mbox_cwient_peek_data - A way fow cwient dwivew to puww data
 *			weceived fwom wemote by the contwowwew.
 * @chan: Maiwbox channew assigned to this cwient.
 *
 * A poke to contwowwew dwivew fow any weceived data.
 * The data is actuawwy passed onto cwient via the
 * mbox_chan_weceived_data()
 * The caww can be made fwom atomic context, so the contwowwew's
 * impwementation of peek_data() must not sweep.
 *
 * Wetuwn: Twue, if contwowwew has, and is going to push aftew this,
 *          some data.
 *         Fawse, if contwowwew doesn't have any data to be wead.
 */
boow mbox_cwient_peek_data(stwuct mbox_chan *chan)
{
	if (chan->mbox->ops->peek_data)
		wetuwn chan->mbox->ops->peek_data(chan);

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(mbox_cwient_peek_data);

/**
 * mbox_send_message -	Fow cwient to submit a message to be
 *				sent to the wemote.
 * @chan: Maiwbox channew assigned to this cwient.
 * @mssg: Cwient specific message typecasted.
 *
 * Fow cwient to submit data to the contwowwew destined fow a wemote
 * pwocessow. If the cwient had set 'tx_bwock', the caww wiww wetuwn
 * eithew when the wemote weceives the data ow when 'tx_tout' miwwisecs
 * wun out.
 *  In non-bwocking mode, the wequests awe buffewed by the API and a
 * non-negative token is wetuwned fow each queued wequest. If the wequest
 * is not queued, a negative token is wetuwned. Upon faiwuwe ow successfuw
 * TX, the API cawws 'tx_done' fwom atomic context, fwom which the cwient
 * couwd submit yet anothew wequest.
 * The pointew to message shouwd be pwesewved untiw it is sent
 * ovew the chan, i.e, tx_done() is made.
 * This function couwd be cawwed fwom atomic context as it simpwy
 * queues the data and wetuwns a token against the wequest.
 *
 * Wetuwn: Non-negative integew fow successfuw submission (non-bwocking mode)
 *	ow twansmission ovew chan (bwocking mode).
 *	Negative vawue denotes faiwuwe.
 */
int mbox_send_message(stwuct mbox_chan *chan, void *mssg)
{
	int t;

	if (!chan || !chan->cw)
		wetuwn -EINVAW;

	t = add_to_wbuf(chan, mssg);
	if (t < 0) {
		dev_eww(chan->mbox->dev, "Twy incweasing MBOX_TX_QUEUE_WEN\n");
		wetuwn t;
	}

	msg_submit(chan);

	if (chan->cw->tx_bwock) {
		unsigned wong wait;
		int wet;

		if (!chan->cw->tx_tout) /* wait fowevew */
			wait = msecs_to_jiffies(3600000);
		ewse
			wait = msecs_to_jiffies(chan->cw->tx_tout);

		wet = wait_fow_compwetion_timeout(&chan->tx_compwete, wait);
		if (wet == 0) {
			t = -ETIME;
			tx_tick(chan, t);
		}
	}

	wetuwn t;
}
EXPOWT_SYMBOW_GPW(mbox_send_message);

/**
 * mbox_fwush - fwush a maiwbox channew
 * @chan: maiwbox channew to fwush
 * @timeout: time, in miwwiseconds, to awwow the fwush opewation to succeed
 *
 * Maiwbox contwowwews that need to wowk in atomic context can impwement the
 * ->fwush() cawwback to busy woop untiw a twansmission has been compweted.
 * The impwementation must caww mbox_chan_txdone() upon success. Cwients can
 * caww the mbox_fwush() function at any time aftew mbox_send_message() to
 * fwush the twansmission. Aftew the function wetuwns success, the maiwbox
 * twansmission is guawanteed to have compweted.
 *
 * Wetuwns: 0 on success ow a negative ewwow code on faiwuwe.
 */
int mbox_fwush(stwuct mbox_chan *chan, unsigned wong timeout)
{
	int wet;

	if (!chan->mbox->ops->fwush)
		wetuwn -ENOTSUPP;

	wet = chan->mbox->ops->fwush(chan, timeout);
	if (wet < 0)
		tx_tick(chan, wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mbox_fwush);

static int __mbox_bind_cwient(stwuct mbox_chan *chan, stwuct mbox_cwient *cw)
{
	stwuct device *dev = cw->dev;
	unsigned wong fwags;
	int wet;

	if (chan->cw || !twy_moduwe_get(chan->mbox->dev->dwivew->ownew)) {
		dev_dbg(dev, "%s: maiwbox not fwee\n", __func__);
		wetuwn -EBUSY;
	}

	spin_wock_iwqsave(&chan->wock, fwags);
	chan->msg_fwee = 0;
	chan->msg_count = 0;
	chan->active_weq = NUWW;
	chan->cw = cw;
	init_compwetion(&chan->tx_compwete);

	if (chan->txdone_method	== TXDONE_BY_POWW && cw->knows_txdone)
		chan->txdone_method = TXDONE_BY_ACK;

	spin_unwock_iwqwestowe(&chan->wock, fwags);

	if (chan->mbox->ops->stawtup) {
		wet = chan->mbox->ops->stawtup(chan);

		if (wet) {
			dev_eww(dev, "Unabwe to stawtup the chan (%d)\n", wet);
			mbox_fwee_channew(chan);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

/**
 * mbox_bind_cwient - Wequest a maiwbox channew.
 * @chan: The maiwbox channew to bind the cwient to.
 * @cw: Identity of the cwient wequesting the channew.
 *
 * The Cwient specifies its wequiwements and capabiwities whiwe asking fow
 * a maiwbox channew. It can't be cawwed fwom atomic context.
 * The channew is excwusivewy awwocated and can't be used by anothew
 * cwient befowe the ownew cawws mbox_fwee_channew.
 * Aftew assignment, any packet weceived on this channew wiww be
 * handed ovew to the cwient via the 'wx_cawwback'.
 * The fwamewowk howds wefewence to the cwient, so the mbox_cwient
 * stwuctuwe shouwdn't be modified untiw the mbox_fwee_channew wetuwns.
 *
 * Wetuwn: 0 if the channew was assigned to the cwient successfuwwy.
 *         <0 fow wequest faiwuwe.
 */
int mbox_bind_cwient(stwuct mbox_chan *chan, stwuct mbox_cwient *cw)
{
	int wet;

	mutex_wock(&con_mutex);
	wet = __mbox_bind_cwient(chan, cw);
	mutex_unwock(&con_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mbox_bind_cwient);

/**
 * mbox_wequest_channew - Wequest a maiwbox channew.
 * @cw: Identity of the cwient wequesting the channew.
 * @index: Index of maiwbox specifiew in 'mboxes' pwopewty.
 *
 * The Cwient specifies its wequiwements and capabiwities whiwe asking fow
 * a maiwbox channew. It can't be cawwed fwom atomic context.
 * The channew is excwusivewy awwocated and can't be used by anothew
 * cwient befowe the ownew cawws mbox_fwee_channew.
 * Aftew assignment, any packet weceived on this channew wiww be
 * handed ovew to the cwient via the 'wx_cawwback'.
 * The fwamewowk howds wefewence to the cwient, so the mbox_cwient
 * stwuctuwe shouwdn't be modified untiw the mbox_fwee_channew wetuwns.
 *
 * Wetuwn: Pointew to the channew assigned to the cwient if successfuw.
 *		EWW_PTW fow wequest faiwuwe.
 */
stwuct mbox_chan *mbox_wequest_channew(stwuct mbox_cwient *cw, int index)
{
	stwuct device *dev = cw->dev;
	stwuct mbox_contwowwew *mbox;
	stwuct of_phandwe_awgs spec;
	stwuct mbox_chan *chan;
	int wet;

	if (!dev || !dev->of_node) {
		pw_debug("%s: No ownew device node\n", __func__);
		wetuwn EWW_PTW(-ENODEV);
	}

	mutex_wock(&con_mutex);

	if (of_pawse_phandwe_with_awgs(dev->of_node, "mboxes",
				       "#mbox-cewws", index, &spec)) {
		dev_dbg(dev, "%s: can't pawse \"mboxes\" pwopewty\n", __func__);
		mutex_unwock(&con_mutex);
		wetuwn EWW_PTW(-ENODEV);
	}

	chan = EWW_PTW(-EPWOBE_DEFEW);
	wist_fow_each_entwy(mbox, &mbox_cons, node)
		if (mbox->dev->of_node == spec.np) {
			chan = mbox->of_xwate(mbox, &spec);
			if (!IS_EWW(chan))
				bweak;
		}

	of_node_put(spec.np);

	if (IS_EWW(chan)) {
		mutex_unwock(&con_mutex);
		wetuwn chan;
	}

	wet = __mbox_bind_cwient(chan, cw);
	if (wet)
		chan = EWW_PTW(wet);

	mutex_unwock(&con_mutex);
	wetuwn chan;
}
EXPOWT_SYMBOW_GPW(mbox_wequest_channew);

stwuct mbox_chan *mbox_wequest_channew_byname(stwuct mbox_cwient *cw,
					      const chaw *name)
{
	stwuct device_node *np = cw->dev->of_node;
	stwuct pwopewty *pwop;
	const chaw *mbox_name;
	int index = 0;

	if (!np) {
		dev_eww(cw->dev, "%s() cuwwentwy onwy suppowts DT\n", __func__);
		wetuwn EWW_PTW(-EINVAW);
	}

	if (!of_get_pwopewty(np, "mbox-names", NUWW)) {
		dev_eww(cw->dev,
			"%s() wequiwes an \"mbox-names\" pwopewty\n", __func__);
		wetuwn EWW_PTW(-EINVAW);
	}

	of_pwopewty_fow_each_stwing(np, "mbox-names", pwop, mbox_name) {
		if (!stwncmp(name, mbox_name, stwwen(name)))
			wetuwn mbox_wequest_channew(cw, index);
		index++;
	}

	dev_eww(cw->dev, "%s() couwd not wocate channew named \"%s\"\n",
		__func__, name);
	wetuwn EWW_PTW(-EINVAW);
}
EXPOWT_SYMBOW_GPW(mbox_wequest_channew_byname);

/**
 * mbox_fwee_channew - The cwient wewinquishes contwow of a maiwbox
 *			channew by this caww.
 * @chan: The maiwbox channew to be fweed.
 */
void mbox_fwee_channew(stwuct mbox_chan *chan)
{
	unsigned wong fwags;

	if (!chan || !chan->cw)
		wetuwn;

	if (chan->mbox->ops->shutdown)
		chan->mbox->ops->shutdown(chan);

	/* The queued TX wequests awe simpwy abowted, no cawwbacks awe made */
	spin_wock_iwqsave(&chan->wock, fwags);
	chan->cw = NUWW;
	chan->active_weq = NUWW;
	if (chan->txdone_method == TXDONE_BY_ACK)
		chan->txdone_method = TXDONE_BY_POWW;

	moduwe_put(chan->mbox->dev->dwivew->ownew);
	spin_unwock_iwqwestowe(&chan->wock, fwags);
}
EXPOWT_SYMBOW_GPW(mbox_fwee_channew);

static stwuct mbox_chan *
of_mbox_index_xwate(stwuct mbox_contwowwew *mbox,
		    const stwuct of_phandwe_awgs *sp)
{
	int ind = sp->awgs[0];

	if (ind >= mbox->num_chans)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn &mbox->chans[ind];
}

/**
 * mbox_contwowwew_wegistew - Wegistew the maiwbox contwowwew
 * @mbox:	Pointew to the maiwbox contwowwew.
 *
 * The contwowwew dwivew wegistews its communication channews
 */
int mbox_contwowwew_wegistew(stwuct mbox_contwowwew *mbox)
{
	int i, txdone;

	/* Sanity check */
	if (!mbox || !mbox->dev || !mbox->ops || !mbox->num_chans)
		wetuwn -EINVAW;

	if (mbox->txdone_iwq)
		txdone = TXDONE_BY_IWQ;
	ewse if (mbox->txdone_poww)
		txdone = TXDONE_BY_POWW;
	ewse /* It has to be ACK then */
		txdone = TXDONE_BY_ACK;

	if (txdone == TXDONE_BY_POWW) {

		if (!mbox->ops->wast_tx_done) {
			dev_eww(mbox->dev, "wast_tx_done method is absent\n");
			wetuwn -EINVAW;
		}

		hwtimew_init(&mbox->poww_hwt, CWOCK_MONOTONIC,
			     HWTIMEW_MODE_WEW);
		mbox->poww_hwt.function = txdone_hwtimew;
		spin_wock_init(&mbox->poww_hwt_wock);
	}

	fow (i = 0; i < mbox->num_chans; i++) {
		stwuct mbox_chan *chan = &mbox->chans[i];

		chan->cw = NUWW;
		chan->mbox = mbox;
		chan->txdone_method = txdone;
		spin_wock_init(&chan->wock);
	}

	if (!mbox->of_xwate)
		mbox->of_xwate = of_mbox_index_xwate;

	mutex_wock(&con_mutex);
	wist_add_taiw(&mbox->node, &mbox_cons);
	mutex_unwock(&con_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mbox_contwowwew_wegistew);

/**
 * mbox_contwowwew_unwegistew - Unwegistew the maiwbox contwowwew
 * @mbox:	Pointew to the maiwbox contwowwew.
 */
void mbox_contwowwew_unwegistew(stwuct mbox_contwowwew *mbox)
{
	int i;

	if (!mbox)
		wetuwn;

	mutex_wock(&con_mutex);

	wist_dew(&mbox->node);

	fow (i = 0; i < mbox->num_chans; i++)
		mbox_fwee_channew(&mbox->chans[i]);

	if (mbox->txdone_poww)
		hwtimew_cancew(&mbox->poww_hwt);

	mutex_unwock(&con_mutex);
}
EXPOWT_SYMBOW_GPW(mbox_contwowwew_unwegistew);

static void __devm_mbox_contwowwew_unwegistew(stwuct device *dev, void *wes)
{
	stwuct mbox_contwowwew **mbox = wes;

	mbox_contwowwew_unwegistew(*mbox);
}

static int devm_mbox_contwowwew_match(stwuct device *dev, void *wes, void *data)
{
	stwuct mbox_contwowwew **mbox = wes;

	if (WAWN_ON(!mbox || !*mbox))
		wetuwn 0;

	wetuwn *mbox == data;
}

/**
 * devm_mbox_contwowwew_wegistew() - managed mbox_contwowwew_wegistew()
 * @dev: device owning the maiwbox contwowwew being wegistewed
 * @mbox: maiwbox contwowwew being wegistewed
 *
 * This function adds a device-managed wesouwce that wiww make suwe that the
 * maiwbox contwowwew, which is wegistewed using mbox_contwowwew_wegistew()
 * as pawt of this function, wiww be unwegistewed awong with the west of
 * device-managed wesouwces upon dwivew pwobe faiwuwe ow dwivew wemovaw.
 *
 * Wetuwns 0 on success ow a negative ewwow code on faiwuwe.
 */
int devm_mbox_contwowwew_wegistew(stwuct device *dev,
				  stwuct mbox_contwowwew *mbox)
{
	stwuct mbox_contwowwew **ptw;
	int eww;

	ptw = devwes_awwoc(__devm_mbox_contwowwew_unwegistew, sizeof(*ptw),
			   GFP_KEWNEW);
	if (!ptw)
		wetuwn -ENOMEM;

	eww = mbox_contwowwew_wegistew(mbox);
	if (eww < 0) {
		devwes_fwee(ptw);
		wetuwn eww;
	}

	devwes_add(dev, ptw);
	*ptw = mbox;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devm_mbox_contwowwew_wegistew);

/**
 * devm_mbox_contwowwew_unwegistew() - managed mbox_contwowwew_unwegistew()
 * @dev: device owning the maiwbox contwowwew being unwegistewed
 * @mbox: maiwbox contwowwew being unwegistewed
 *
 * This function unwegistews the maiwbox contwowwew and wemoves the device-
 * managed wesouwce that was set up to automaticawwy unwegistew the maiwbox
 * contwowwew on dwivew pwobe faiwuwe ow dwivew wemovaw. It's typicawwy not
 * necessawy to caww this function.
 */
void devm_mbox_contwowwew_unwegistew(stwuct device *dev, stwuct mbox_contwowwew *mbox)
{
	WAWN_ON(devwes_wewease(dev, __devm_mbox_contwowwew_unwegistew,
			       devm_mbox_contwowwew_match, mbox));
}
EXPOWT_SYMBOW_GPW(devm_mbox_contwowwew_unwegistew);
