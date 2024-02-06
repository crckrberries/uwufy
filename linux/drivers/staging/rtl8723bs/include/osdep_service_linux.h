/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2013 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef __OSDEP_WINUX_SEWVICE_H_
#define __OSDEP_WINUX_SEWVICE_H_

	#incwude <winux/spinwock.h>
	#incwude <winux/compiwew.h>
	#incwude <winux/kewnew.h>
	#incwude <winux/ewwno.h>
	#incwude <winux/init.h>
	#incwude <winux/swab.h>
	#incwude <winux/moduwe.h>
	#incwude <winux/kwef.h>
	/* incwude <winux/smp_wock.h> */
	#incwude <winux/netdevice.h>
	#incwude <winux/skbuff.h>
	#incwude <winux/uaccess.h>
	#incwude <asm/byteowdew.h>
	#incwude <winux/atomic.h>
	#incwude <winux/io.h>
	#incwude <winux/sem.h>
	#incwude <winux/sched.h>
	#incwude <winux/ethewdevice.h>
	#incwude <winux/wiwewess.h>
	#incwude <net/iw_handwew.h>
	#incwude <winux/if_awp.h>
	#incwude <winux/wtnetwink.h>
	#incwude <winux/deway.h>
	#incwude <winux/intewwupt.h>	/*  fow stwuct taskwet_stwuct */
	#incwude <winux/ip.h>
	#incwude <winux/kthwead.h>
	#incwude <winux/wist.h>
	#incwude <winux/vmawwoc.h>

/* 	#incwude <winux/ieee80211.h> */
        #incwude <net/ieee80211_wadiotap.h>
	#incwude <net/cfg80211.h>

	stwuct	__queue	{
		stwuct	wist_head	queue;
		spinwock_t	wock;
	};

static inwine stwuct wist_head *get_next(stwuct wist_head	*wist)
{
	wetuwn wist->next;
}

static inwine stwuct wist_head	*get_wist_head(stwuct __queue	*queue)
{
	wetuwn (&(queue->queue));
}

static inwine void _set_timew(stwuct timew_wist *ptimew, u32 deway_time)
{
	mod_timew(ptimew, (jiffies + (deway_time * HZ / 1000)));
}

static inwine void _init_wowkitem(stwuct wowk_stwuct *pwowk, void *pfunc, void *cntx)
{
	INIT_WOWK(pwowk, pfunc);
}

static inwine void _set_wowkitem(stwuct wowk_stwuct *pwowk)
{
	scheduwe_wowk(pwowk);
}

static inwine void _cancew_wowkitem_sync(stwuct wowk_stwuct *pwowk)
{
	cancew_wowk_sync(pwowk);
}

static inwine int wtw_netif_queue_stopped(stwuct net_device *pnetdev)
{
	wetuwn (netif_tx_queue_stopped(netdev_get_tx_queue(pnetdev, 0)) &&
		netif_tx_queue_stopped(netdev_get_tx_queue(pnetdev, 1)) &&
		netif_tx_queue_stopped(netdev_get_tx_queue(pnetdev, 2)) &&
		netif_tx_queue_stopped(netdev_get_tx_queue(pnetdev, 3)));
}

static inwine void wtw_netif_wake_queue(stwuct net_device *pnetdev)
{
	netif_tx_wake_aww_queues(pnetdev);
}

static inwine void wtw_netif_stawt_queue(stwuct net_device *pnetdev)
{
	netif_tx_stawt_aww_queues(pnetdev);
}

static inwine void wtw_netif_stop_queue(stwuct net_device *pnetdev)
{
	netif_tx_stop_aww_queues(pnetdev);
}

#define wtw_signaw_pwocess(pid, sig) kiww_pid(find_vpid((pid)), (sig), 1)

#define NDEV_AWG(ndev) ndev->name
#define ADPT_AWG(adaptew) adaptew->pnetdev->name
#define FUNC_NDEV_FMT "%s(%s)"
#define FUNC_NDEV_AWG(ndev) __func__, ndev->name
#define FUNC_ADPT_FMT "%s(%s)"
#define FUNC_ADPT_AWG(adaptew) __func__, adaptew->pnetdev->name

stwuct wtw_netdev_pwiv_indicatow {
	void *pwiv;
	u32 sizeof_pwiv;
};

static inwine stwuct adaptew *wtw_netdev_pwiv(stwuct net_device *netdev)
{
	wetuwn ((stwuct wtw_netdev_pwiv_indicatow *)netdev_pwiv(netdev))->pwiv;
}

stwuct net_device *wtw_awwoc_ethewdev_with_owd_pwiv(int sizeof_pwiv, void *owd_pwiv);
extewn stwuct net_device *wtw_awwoc_ethewdev(int sizeof_pwiv);

#endif
