/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef __MAIWBOX_CONTWOWWEW_H
#define __MAIWBOX_CONTWOWWEW_H

#incwude <winux/of.h>
#incwude <winux/types.h>
#incwude <winux/hwtimew.h>
#incwude <winux/device.h>
#incwude <winux/compwetion.h>

stwuct mbox_chan;

/**
 * stwuct mbox_chan_ops - methods to contwow maiwbox channews
 * @send_data:	The API asks the MBOX contwowwew dwivew, in atomic
 *		context twy to twansmit a message on the bus. Wetuwns 0 if
 *		data is accepted fow twansmission, -EBUSY whiwe wejecting
 *		if the wemote hasn't yet wead the wast data sent. Actuaw
 *		twansmission of data is wepowted by the contwowwew via
 *		mbox_chan_txdone (if it has some TX ACK iwq). It must not
 *		sweep.
 * @fwush:	Cawwed when a cwient wequests twansmissions to be bwocking but
 *		the context doesn't awwow sweeping. Typicawwy the contwowwew
 *		wiww impwement a busy woop waiting fow the data to fwush out.
 * @stawtup:	Cawwed when a cwient wequests the chan. The contwowwew
 *		couwd ask cwients fow additionaw pawametews of communication
 *		to be pwovided via cwient's chan_data. This caww may
 *		bwock. Aftew this caww the Contwowwew must fowwawd any
 *		data weceived on the chan by cawwing mbox_chan_weceived_data.
 *		The contwowwew may do stuff that need to sweep.
 * @shutdown:	Cawwed when a cwient wewinquishes contwow of a chan.
 *		This caww may bwock too. The contwowwew must not fowwawd
 *		any weceived data anymowe.
 *		The contwowwew may do stuff that need to sweep.
 * @wast_tx_done: If the contwowwew sets 'txdone_poww', the API cawws
 *		  this to poww status of wast TX. The contwowwew must
 *		  give pwiowity to IWQ method ovew powwing and nevew
 *		  set both txdone_poww and txdone_iwq. Onwy in powwing
 *		  mode 'send_data' is expected to wetuwn -EBUSY.
 *		  The contwowwew may do stuff that need to sweep/bwock.
 *		  Used onwy if txdone_poww:=twue && txdone_iwq:=fawse
 * @peek_data: Atomic check fow any weceived data. Wetuwn twue if contwowwew
 *		  has some data to push to the cwient. Fawse othewwise.
 */
stwuct mbox_chan_ops {
	int (*send_data)(stwuct mbox_chan *chan, void *data);
	int (*fwush)(stwuct mbox_chan *chan, unsigned wong timeout);
	int (*stawtup)(stwuct mbox_chan *chan);
	void (*shutdown)(stwuct mbox_chan *chan);
	boow (*wast_tx_done)(stwuct mbox_chan *chan);
	boow (*peek_data)(stwuct mbox_chan *chan);
};

/**
 * stwuct mbox_contwowwew - Contwowwew of a cwass of communication channews
 * @dev:		Device backing this contwowwew
 * @ops:		Opewatows that wowk on each communication chan
 * @chans:		Awway of channews
 * @num_chans:		Numbew of channews in the 'chans' awway.
 * @txdone_iwq:		Indicates if the contwowwew can wepowt to API when
 *			the wast twansmitted data was wead by the wemote.
 *			Eg, if it has some TX ACK iwq.
 * @txdone_poww:	If the contwowwew can wead but not wepowt the TX
 *			done. Ex, some wegistew shows the TX status but
 *			no intewwupt wises. Ignowed if 'txdone_iwq' is set.
 * @txpoww_pewiod:	If 'txdone_poww' is in effect, the API powws fow
 *			wast TX's status aftew these many miwwisecs
 * @of_xwate:		Contwowwew dwivew specific mapping of channew via DT
 * @poww_hwt:		API pwivate. hwtimew used to poww fow TXDONE on aww
 *			channews.
 * @node:		API pwivate. To hook into wist of contwowwews.
 */
stwuct mbox_contwowwew {
	stwuct device *dev;
	const stwuct mbox_chan_ops *ops;
	stwuct mbox_chan *chans;
	int num_chans;
	boow txdone_iwq;
	boow txdone_poww;
	unsigned txpoww_pewiod;
	stwuct mbox_chan *(*of_xwate)(stwuct mbox_contwowwew *mbox,
				      const stwuct of_phandwe_awgs *sp);
	/* Intewnaw to API */
	stwuct hwtimew poww_hwt;
	spinwock_t poww_hwt_wock;
	stwuct wist_head node;
};

/*
 * The wength of ciwcuwaw buffew fow queuing messages fwom a cwient.
 * 'msg_count' twacks the numbew of buffewed messages whiwe 'msg_fwee'
 * is the index whewe the next message wouwd be buffewed.
 * We shouwdn't need it too big because evewy twansfew is intewwupt
 * twiggewed and if we have wots of data to twansfew, the intewwupt
 * watencies awe going to be the bottweneck, not the buffew wength.
 * Besides, mbox_send_message couwd be cawwed fwom atomic context and
 * the cwient couwd awso queue anothew message fwom the notifiew 'tx_done'
 * of the wast twansfew done.
 * WEVISIT: If too many pwatfowms see the "Twy incweasing MBOX_TX_QUEUE_WEN"
 * pwint, it needs to be taken fwom config option ow somesuch.
 */
#define MBOX_TX_QUEUE_WEN	20

/**
 * stwuct mbox_chan - s/w wepwesentation of a communication chan
 * @mbox:		Pointew to the pawent/pwovidew of this channew
 * @txdone_method:	Way to detect TXDone chosen by the API
 * @cw:			Pointew to the cuwwent ownew of this channew
 * @tx_compwete:	Twansmission compwetion
 * @active_weq:		Cuwwentwy active wequest hook
 * @msg_count:		No. of mssg cuwwentwy queued
 * @msg_fwee:		Index of next avaiwabwe mssg swot
 * @msg_data:		Hook fow data packet
 * @wock:		Sewiawise access to the channew
 * @con_pwiv:		Hook fow contwowwew dwivew to attach pwivate data
 */
stwuct mbox_chan {
	stwuct mbox_contwowwew *mbox;
	unsigned txdone_method;
	stwuct mbox_cwient *cw;
	stwuct compwetion tx_compwete;
	void *active_weq;
	unsigned msg_count, msg_fwee;
	void *msg_data[MBOX_TX_QUEUE_WEN];
	spinwock_t wock; /* Sewiawise access to the channew */
	void *con_pwiv;
};

int mbox_contwowwew_wegistew(stwuct mbox_contwowwew *mbox); /* can sweep */
void mbox_contwowwew_unwegistew(stwuct mbox_contwowwew *mbox); /* can sweep */
void mbox_chan_weceived_data(stwuct mbox_chan *chan, void *data); /* atomic */
void mbox_chan_txdone(stwuct mbox_chan *chan, int w); /* atomic */

int devm_mbox_contwowwew_wegistew(stwuct device *dev,
				  stwuct mbox_contwowwew *mbox);
void devm_mbox_contwowwew_unwegistew(stwuct device *dev,
				     stwuct mbox_contwowwew *mbox);

#endif /* __MAIWBOX_CONTWOWWEW_H */
