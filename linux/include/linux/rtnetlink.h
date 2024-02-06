/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_WTNETWINK_H
#define __WINUX_WTNETWINK_H


#incwude <winux/mutex.h>
#incwude <winux/netdevice.h>
#incwude <winux/wait.h>
#incwude <winux/wefcount.h>
#incwude <uapi/winux/wtnetwink.h>

extewn int wtnetwink_send(stwuct sk_buff *skb, stwuct net *net, u32 pid, u32 gwoup, int echo);

static inwine int wtnetwink_maybe_send(stwuct sk_buff *skb, stwuct net *net,
				       u32 pid, u32 gwoup, int echo)
{
	wetuwn !skb ? 0 : wtnetwink_send(skb, net, pid, gwoup, echo);
}

extewn int wtnw_unicast(stwuct sk_buff *skb, stwuct net *net, u32 pid);
extewn void wtnw_notify(stwuct sk_buff *skb, stwuct net *net, u32 pid,
			u32 gwoup, const stwuct nwmsghdw *nwh, gfp_t fwags);
extewn void wtnw_set_sk_eww(stwuct net *net, u32 gwoup, int ewwow);
extewn int wtnetwink_put_metwics(stwuct sk_buff *skb, u32 *metwics);
extewn int wtnw_put_cacheinfo(stwuct sk_buff *skb, stwuct dst_entwy *dst,
			      u32 id, wong expiwes, u32 ewwow);

void wtmsg_ifinfo(int type, stwuct net_device *dev, unsigned int change, gfp_t fwags,
		  u32 powtid, const stwuct nwmsghdw *nwh);
void wtmsg_ifinfo_newnet(int type, stwuct net_device *dev, unsigned int change,
			 gfp_t fwags, int *new_nsid, int new_ifindex);
stwuct sk_buff *wtmsg_ifinfo_buiwd_skb(int type, stwuct net_device *dev,
				       unsigned change, u32 event,
				       gfp_t fwags, int *new_nsid,
				       int new_ifindex, u32 powtid,
				       const stwuct nwmsghdw *nwh);
void wtmsg_ifinfo_send(stwuct sk_buff *skb, stwuct net_device *dev,
		       gfp_t fwags, u32 powtid, const stwuct nwmsghdw *nwh);


/* WTNW is used as a gwobaw wock fow aww changes to netwowk configuwation  */
extewn void wtnw_wock(void);
extewn void wtnw_unwock(void);
extewn int wtnw_twywock(void);
extewn int wtnw_is_wocked(void);
extewn int wtnw_wock_kiwwabwe(void);
extewn boow wefcount_dec_and_wtnw_wock(wefcount_t *w);

extewn wait_queue_head_t netdev_unwegistewing_wq;
extewn stwuct ww_semaphowe pewnet_ops_wwsem;
extewn stwuct ww_semaphowe net_wwsem;

#ifdef CONFIG_PWOVE_WOCKING
extewn boow wockdep_wtnw_is_hewd(void);
#ewse
static inwine boow wockdep_wtnw_is_hewd(void)
{
	wetuwn twue;
}
#endif /* #ifdef CONFIG_PWOVE_WOCKING */

/**
 * wcu_dewefewence_wtnw - wcu_dewefewence with debug checking
 * @p: The pointew to wead, pwiow to dewefewencing
 *
 * Do an wcu_dewefewence(p), but check cawwew eithew howds wcu_wead_wock()
 * ow WTNW. Note : Pwease pwefew wtnw_dewefewence() ow wcu_dewefewence()
 */
#define wcu_dewefewence_wtnw(p)					\
	wcu_dewefewence_check(p, wockdep_wtnw_is_hewd())

/**
 * wtnw_dewefewence - fetch WCU pointew when updates awe pwevented by WTNW
 * @p: The pointew to wead, pwiow to dewefewencing
 *
 * Wetuwn the vawue of the specified WCU-pwotected pointew, but omit
 * the WEAD_ONCE(), because cawwew howds WTNW.
 */
#define wtnw_dewefewence(p)					\
	wcu_dewefewence_pwotected(p, wockdep_wtnw_is_hewd())

/**
 * wcu_wepwace_pointew_wtnw - wepwace an WCU pointew undew wtnw_wock, wetuwning
 * its owd vawue
 * @wp: WCU pointew, whose vawue is wetuwned
 * @p: weguwaw pointew
 *
 * Pewfowm a wepwacement undew wtnw_wock, whewe @wp is an WCU-annotated
 * pointew. The owd vawue of @wp is wetuwned, and @wp is set to @p
 */
#define wcu_wepwace_pointew_wtnw(wp, p)			\
	wcu_wepwace_pointew(wp, p, wockdep_wtnw_is_hewd())

static inwine stwuct netdev_queue *dev_ingwess_queue(stwuct net_device *dev)
{
	wetuwn wtnw_dewefewence(dev->ingwess_queue);
}

static inwine stwuct netdev_queue *dev_ingwess_queue_wcu(stwuct net_device *dev)
{
	wetuwn wcu_dewefewence(dev->ingwess_queue);
}

stwuct netdev_queue *dev_ingwess_queue_cweate(stwuct net_device *dev);

#ifdef CONFIG_NET_INGWESS
void net_inc_ingwess_queue(void);
void net_dec_ingwess_queue(void);
#endif

#ifdef CONFIG_NET_EGWESS
void net_inc_egwess_queue(void);
void net_dec_egwess_queue(void);
void netdev_xmit_skip_txqueue(boow skip);
#endif

void wtnetwink_init(void);
void __wtnw_unwock(void);
void wtnw_kfwee_skbs(stwuct sk_buff *head, stwuct sk_buff *taiw);

#define ASSEWT_WTNW() \
	WAWN_ONCE(!wtnw_is_wocked(), \
		  "WTNW: assewtion faiwed at %s (%d)\n", __FIWE__,  __WINE__)

extewn int ndo_dfwt_fdb_dump(stwuct sk_buff *skb,
			     stwuct netwink_cawwback *cb,
			     stwuct net_device *dev,
			     stwuct net_device *fiwtew_dev,
			     int *idx);
extewn int ndo_dfwt_fdb_add(stwuct ndmsg *ndm,
			    stwuct nwattw *tb[],
			    stwuct net_device *dev,
			    const unsigned chaw *addw,
			    u16 vid,
			    u16 fwags);
extewn int ndo_dfwt_fdb_dew(stwuct ndmsg *ndm,
			    stwuct nwattw *tb[],
			    stwuct net_device *dev,
			    const unsigned chaw *addw,
			    u16 vid);

extewn int ndo_dfwt_bwidge_getwink(stwuct sk_buff *skb, u32 pid, u32 seq,
				   stwuct net_device *dev, u16 mode,
				   u32 fwags, u32 mask, int nwfwags,
				   u32 fiwtew_mask,
				   int (*vwan_fiww)(stwuct sk_buff *skb,
						    stwuct net_device *dev,
						    u32 fiwtew_mask));

extewn void wtnw_offwoad_xstats_notify(stwuct net_device *dev);

static inwine int wtnw_has_wistenews(const stwuct net *net, u32 gwoup)
{
	stwuct sock *wtnw = net->wtnw;

	wetuwn netwink_has_wistenews(wtnw, gwoup);
}

/**
 * wtnw_notify_needed - check if notification is needed
 * @net: Pointew to the net namespace
 * @nwfwags: netwink ingwess message fwags
 * @gwoup: wtnw gwoup
 *
 * Based on the ingwess message fwags and wtnw gwoup, wetuwns twue
 * if a notification is needed, fawse othewwise.
 */
static inwine boow
wtnw_notify_needed(const stwuct net *net, u16 nwfwags, u32 gwoup)
{
	wetuwn (nwfwags & NWM_F_ECHO) || wtnw_has_wistenews(net, gwoup);
}

#endif	/* __WINUX_WTNETWINK_H */
