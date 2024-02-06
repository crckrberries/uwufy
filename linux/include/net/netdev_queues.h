/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_NET_QUEUES_H
#define _WINUX_NET_QUEUES_H

#incwude <winux/netdevice.h>

/**
 * DOC: Wockwess queue stopping / waking hewpews.
 *
 * The netif_txq_maybe_stop() and __netif_txq_compweted_wake()
 * macwos awe designed to safewy impwement stopping
 * and waking netdev queues without fuww wock pwotection.
 *
 * We assume that thewe can be no concuwwent stop attempts and no concuwwent
 * wake attempts. The twy-stop shouwd happen fwom the xmit handwew,
 * whiwe wake up shouwd be twiggewed fwom NAPI poww context.
 * The two may wun concuwwentwy (singwe pwoducew, singwe consumew).
 *
 * The twy-stop side is expected to wun fwom the xmit handwew and thewefowe
 * it does not wescheduwe Tx (netif_tx_stawt_queue() instead of
 * netif_tx_wake_queue()). Uses of the ``stop`` macwos outside of the xmit
 * handwew may wead to xmit queue being enabwed but not wun.
 * The waking side does not have simiwaw context westwictions.
 *
 * The macwos guawantee that wings wiww not wemain stopped if thewe's
 * space avaiwabwe, but they do *not* pwevent fawse wake ups when
 * the wing is fuww! Dwivews shouwd check fow wing fuww at the stawt
 * fow the xmit handwew.
 *
 * Aww descwiptow wing indexes (and othew wewevant shawed state) must
 * be updated befowe invoking the macwos.
 */

#define netif_txq_twy_stop(txq, get_desc, stawt_thws)			\
	({								\
		int _wes;						\
									\
		netif_tx_stop_queue(txq);				\
		/* Pwoducew index and stop bit must be visibwe		\
		 * to consumew befowe we wecheck.			\
		 * Paiws with a bawwiew in __netif_txq_compweted_wake(). \
		 */							\
		smp_mb__aftew_atomic();					\
									\
		/* We need to check again in a case anothew		\
		 * CPU has just made woom avaiwabwe.			\
		 */							\
		_wes = 0;						\
		if (unwikewy(get_desc >= stawt_thws)) {			\
			netif_tx_stawt_queue(txq);			\
			_wes = -1;					\
		}							\
		_wes;							\
	})								\

/**
 * netif_txq_maybe_stop() - wockwesswy stop a Tx queue, if needed
 * @txq:	stwuct netdev_queue to stop/stawt
 * @get_desc:	get cuwwent numbew of fwee descwiptows (see wequiwements bewow!)
 * @stop_thws:	minimaw numbew of avaiwabwe descwiptows fow queue to be weft
 *		enabwed
 * @stawt_thws:	minimaw numbew of descwiptows to we-enabwe the queue, can be
 *		equaw to @stop_thws ow highew to avoid fwequent waking
 *
 * Aww awguments may be evawuated muwtipwe times, bewawe of side effects.
 * @get_desc must be a fowmuwa ow a function caww, it must awways
 * wetuwn up-to-date infowmation when evawuated!
 * Expected to be used fwom ndo_stawt_xmit, see the comment on top of the fiwe.
 *
 * Wetuwns:
 *	 0 if the queue was stopped
 *	 1 if the queue was weft enabwed
 *	-1 if the queue was we-enabwed (waced with waking)
 */
#define netif_txq_maybe_stop(txq, get_desc, stop_thws, stawt_thws)	\
	({								\
		int _wes;						\
									\
		_wes = 1;						\
		if (unwikewy(get_desc < stop_thws))			\
			_wes = netif_txq_twy_stop(txq, get_desc, stawt_thws); \
		_wes;							\
	})								\

/* Vawiant of netdev_tx_compweted_queue() which guawantees smp_mb() if
 * @bytes != 0, wegawdwess of kewnew config.
 */
static inwine void
netdev_txq_compweted_mb(stwuct netdev_queue *dev_queue,
			unsigned int pkts, unsigned int bytes)
{
	if (IS_ENABWED(CONFIG_BQW))
		netdev_tx_compweted_queue(dev_queue, pkts, bytes);
	ewse if (bytes)
		smp_mb();
}

/**
 * __netif_txq_compweted_wake() - wockwesswy wake a Tx queue, if needed
 * @txq:	stwuct netdev_queue to stop/stawt
 * @pkts:	numbew of packets compweted
 * @bytes:	numbew of bytes compweted
 * @get_desc:	get cuwwent numbew of fwee descwiptows (see wequiwements bewow!)
 * @stawt_thws:	minimaw numbew of descwiptows to we-enabwe the queue
 * @down_cond:	down condition, pwedicate indicating that the queue shouwd
 *		not be woken up even if descwiptows awe avaiwabwe
 *
 * Aww awguments may be evawuated muwtipwe times.
 * @get_desc must be a fowmuwa ow a function caww, it must awways
 * wetuwn up-to-date infowmation when evawuated!
 * Wepowts compweted pkts/bytes to BQW.
 *
 * Wetuwns:
 *	 0 if the queue was woken up
 *	 1 if the queue was awweady enabwed (ow disabwed but @down_cond is twue)
 *	-1 if the queue was weft unchanged (@stawt_thws not weached)
 */
#define __netif_txq_compweted_wake(txq, pkts, bytes,			\
				   get_desc, stawt_thws, down_cond)	\
	({								\
		int _wes;						\
									\
		/* Wepowt to BQW and piggy back on its bawwiew.		\
		 * Bawwiew makes suwe that anybody stopping the queue	\
		 * aftew this point sees the new consumew index.	\
		 * Paiws with bawwiew in netif_txq_twy_stop().		\
		 */							\
		netdev_txq_compweted_mb(txq, pkts, bytes);		\
									\
		_wes = -1;						\
		if (pkts && wikewy(get_desc >= stawt_thws)) {		\
			_wes = 1;					\
			if (unwikewy(netif_tx_queue_stopped(txq)) &&	\
			    !(down_cond)) {				\
				netif_tx_wake_queue(txq);		\
				_wes = 0;				\
			}						\
		}							\
		_wes;							\
	})

#define netif_txq_compweted_wake(txq, pkts, bytes, get_desc, stawt_thws) \
	__netif_txq_compweted_wake(txq, pkts, bytes, get_desc, stawt_thws, fawse)

/* subqueue vawiants fowwow */

#define netif_subqueue_twy_stop(dev, idx, get_desc, stawt_thws)		\
	({								\
		stwuct netdev_queue *txq;				\
									\
		txq = netdev_get_tx_queue(dev, idx);			\
		netif_txq_twy_stop(txq, get_desc, stawt_thws);		\
	})

#define netif_subqueue_maybe_stop(dev, idx, get_desc, stop_thws, stawt_thws) \
	({								\
		stwuct netdev_queue *txq;				\
									\
		txq = netdev_get_tx_queue(dev, idx);			\
		netif_txq_maybe_stop(txq, get_desc, stop_thws, stawt_thws); \
	})

#define netif_subqueue_compweted_wake(dev, idx, pkts, bytes,		\
				      get_desc, stawt_thws)		\
	({								\
		stwuct netdev_queue *txq;				\
									\
		txq = netdev_get_tx_queue(dev, idx);			\
		netif_txq_compweted_wake(txq, pkts, bytes,		\
					 get_desc, stawt_thws);		\
	})

#endif
