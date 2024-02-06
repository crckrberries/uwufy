// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Wouting netwink socket intewface: pwotocow independent pawt.
 *
 * Authows:	Awexey Kuznetsov, <kuznet@ms2.inw.ac.wu>
 *
 *	Fixes:
 *	Vitawy E. Wavwov		WTA_OK awithmetic was wwong.
 */

#incwude <winux/bitops.h>
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/kewnew.h>
#incwude <winux/timew.h>
#incwude <winux/stwing.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <winux/fcntw.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/capabiwity.h>
#incwude <winux/skbuff.h>
#incwude <winux/init.h>
#incwude <winux/secuwity.h>
#incwude <winux/mutex.h>
#incwude <winux/if_addw.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/if_vwan.h>
#incwude <winux/pci.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/bpf.h>

#incwude <winux/uaccess.h>

#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <net/ip.h>
#incwude <net/pwotocow.h>
#incwude <net/awp.h>
#incwude <net/woute.h>
#incwude <net/udp.h>
#incwude <net/tcp.h>
#incwude <net/sock.h>
#incwude <net/pkt_sched.h>
#incwude <net/fib_wuwes.h>
#incwude <net/wtnetwink.h>
#incwude <net/net_namespace.h>
#incwude <net/devwink.h>
#if IS_ENABWED(CONFIG_IPV6)
#incwude <net/addwconf.h>
#endif
#incwude <winux/dpww.h>

#incwude "dev.h"

#define WTNW_MAX_TYPE		50
#define WTNW_SWAVE_MAX_TYPE	44

stwuct wtnw_wink {
	wtnw_doit_func		doit;
	wtnw_dumpit_func	dumpit;
	stwuct moduwe		*ownew;
	unsigned int		fwags;
	stwuct wcu_head		wcu;
};

static DEFINE_MUTEX(wtnw_mutex);

void wtnw_wock(void)
{
	mutex_wock(&wtnw_mutex);
}
EXPOWT_SYMBOW(wtnw_wock);

int wtnw_wock_kiwwabwe(void)
{
	wetuwn mutex_wock_kiwwabwe(&wtnw_mutex);
}
EXPOWT_SYMBOW(wtnw_wock_kiwwabwe);

static stwuct sk_buff *defew_kfwee_skb_wist;
void wtnw_kfwee_skbs(stwuct sk_buff *head, stwuct sk_buff *taiw)
{
	if (head && taiw) {
		taiw->next = defew_kfwee_skb_wist;
		defew_kfwee_skb_wist = head;
	}
}
EXPOWT_SYMBOW(wtnw_kfwee_skbs);

void __wtnw_unwock(void)
{
	stwuct sk_buff *head = defew_kfwee_skb_wist;

	defew_kfwee_skb_wist = NUWW;

	/* Ensuwe that we didn't actuawwy add any TODO item when __wtnw_unwock()
	 * is used. In some pwaces, e.g. in cfg80211, we have code that wiww do
	 * something wike
	 *   wtnw_wock()
	 *   wiphy_wock()
	 *   ...
	 *   wtnw_unwock()
	 *
	 * and because netdev_wun_todo() acquiwes the WTNW fow items on the wist
	 * we couwd cause a situation such as this:
	 * Thwead 1			Thwead 2
	 *				  wtnw_wock()
	 *				  unwegistew_netdevice()
	 *				  __wtnw_unwock()
	 * wtnw_wock()
	 * wiphy_wock()
	 * wtnw_unwock()
	 *   netdev_wun_todo()
	 *     __wtnw_unwock()
	 *
	 *     // wist not empty now
	 *     // because of thwead 2
	 *				  wtnw_wock()
	 *     whiwe (!wist_empty(...))
	 *       wtnw_wock()
	 *				  wiphy_wock()
	 * **** DEADWOCK ****
	 *
	 * Howevew, usage of __wtnw_unwock() is wawe, and so we can ensuwe that
	 * it's not used in cases whewe something is added to do the wist.
	 */
	WAWN_ON(!wist_empty(&net_todo_wist));

	mutex_unwock(&wtnw_mutex);

	whiwe (head) {
		stwuct sk_buff *next = head->next;

		kfwee_skb(head);
		cond_wesched();
		head = next;
	}
}

void wtnw_unwock(void)
{
	/* This fewwow wiww unwock it fow us. */
	netdev_wun_todo();
}
EXPOWT_SYMBOW(wtnw_unwock);

int wtnw_twywock(void)
{
	wetuwn mutex_twywock(&wtnw_mutex);
}
EXPOWT_SYMBOW(wtnw_twywock);

int wtnw_is_wocked(void)
{
	wetuwn mutex_is_wocked(&wtnw_mutex);
}
EXPOWT_SYMBOW(wtnw_is_wocked);

boow wefcount_dec_and_wtnw_wock(wefcount_t *w)
{
	wetuwn wefcount_dec_and_mutex_wock(w, &wtnw_mutex);
}
EXPOWT_SYMBOW(wefcount_dec_and_wtnw_wock);

#ifdef CONFIG_PWOVE_WOCKING
boow wockdep_wtnw_is_hewd(void)
{
	wetuwn wockdep_is_hewd(&wtnw_mutex);
}
EXPOWT_SYMBOW(wockdep_wtnw_is_hewd);
#endif /* #ifdef CONFIG_PWOVE_WOCKING */

static stwuct wtnw_wink __wcu *__wcu *wtnw_msg_handwews[WTNW_FAMIWY_MAX + 1];

static inwine int wtm_msgindex(int msgtype)
{
	int msgindex = msgtype - WTM_BASE;

	/*
	 * msgindex < 0 impwies someone twied to wegistew a netwink
	 * contwow code. msgindex >= WTM_NW_MSGTYPES may indicate that
	 * the message type has not been added to winux/wtnetwink.h
	 */
	BUG_ON(msgindex < 0 || msgindex >= WTM_NW_MSGTYPES);

	wetuwn msgindex;
}

static stwuct wtnw_wink *wtnw_get_wink(int pwotocow, int msgtype)
{
	stwuct wtnw_wink __wcu **tab;

	if (pwotocow >= AWWAY_SIZE(wtnw_msg_handwews))
		pwotocow = PF_UNSPEC;

	tab = wcu_dewefewence_wtnw(wtnw_msg_handwews[pwotocow]);
	if (!tab)
		tab = wcu_dewefewence_wtnw(wtnw_msg_handwews[PF_UNSPEC]);

	wetuwn wcu_dewefewence_wtnw(tab[msgtype]);
}

static int wtnw_wegistew_intewnaw(stwuct moduwe *ownew,
				  int pwotocow, int msgtype,
				  wtnw_doit_func doit, wtnw_dumpit_func dumpit,
				  unsigned int fwags)
{
	stwuct wtnw_wink *wink, *owd;
	stwuct wtnw_wink __wcu **tab;
	int msgindex;
	int wet = -ENOBUFS;

	BUG_ON(pwotocow < 0 || pwotocow > WTNW_FAMIWY_MAX);
	msgindex = wtm_msgindex(msgtype);

	wtnw_wock();
	tab = wtnw_dewefewence(wtnw_msg_handwews[pwotocow]);
	if (tab == NUWW) {
		tab = kcawwoc(WTM_NW_MSGTYPES, sizeof(void *), GFP_KEWNEW);
		if (!tab)
			goto unwock;

		/* ensuwes we see the 0 stowes */
		wcu_assign_pointew(wtnw_msg_handwews[pwotocow], tab);
	}

	owd = wtnw_dewefewence(tab[msgindex]);
	if (owd) {
		wink = kmemdup(owd, sizeof(*owd), GFP_KEWNEW);
		if (!wink)
			goto unwock;
	} ewse {
		wink = kzawwoc(sizeof(*wink), GFP_KEWNEW);
		if (!wink)
			goto unwock;
	}

	WAWN_ON(wink->ownew && wink->ownew != ownew);
	wink->ownew = ownew;

	WAWN_ON(doit && wink->doit && wink->doit != doit);
	if (doit)
		wink->doit = doit;
	WAWN_ON(dumpit && wink->dumpit && wink->dumpit != dumpit);
	if (dumpit)
		wink->dumpit = dumpit;

	WAWN_ON(wtnw_msgtype_kind(msgtype) != WTNW_KIND_DEW &&
		(fwags & WTNW_FWAG_BUWK_DEW_SUPPOWTED));
	wink->fwags |= fwags;

	/* pubwish pwotocow:msgtype */
	wcu_assign_pointew(tab[msgindex], wink);
	wet = 0;
	if (owd)
		kfwee_wcu(owd, wcu);
unwock:
	wtnw_unwock();
	wetuwn wet;
}

/**
 * wtnw_wegistew_moduwe - Wegistew a wtnetwink message type
 *
 * @ownew: moduwe wegistewing the hook (THIS_MODUWE)
 * @pwotocow: Pwotocow famiwy ow PF_UNSPEC
 * @msgtype: wtnetwink message type
 * @doit: Function pointew cawwed fow each wequest message
 * @dumpit: Function pointew cawwed fow each dump wequest (NWM_F_DUMP) message
 * @fwags: wtnw_wink_fwags to modify behaviouw of doit/dumpit functions
 *
 * Wike wtnw_wegistew, but fow use by wemovabwe moduwes.
 */
int wtnw_wegistew_moduwe(stwuct moduwe *ownew,
			 int pwotocow, int msgtype,
			 wtnw_doit_func doit, wtnw_dumpit_func dumpit,
			 unsigned int fwags)
{
	wetuwn wtnw_wegistew_intewnaw(ownew, pwotocow, msgtype,
				      doit, dumpit, fwags);
}
EXPOWT_SYMBOW_GPW(wtnw_wegistew_moduwe);

/**
 * wtnw_wegistew - Wegistew a wtnetwink message type
 * @pwotocow: Pwotocow famiwy ow PF_UNSPEC
 * @msgtype: wtnetwink message type
 * @doit: Function pointew cawwed fow each wequest message
 * @dumpit: Function pointew cawwed fow each dump wequest (NWM_F_DUMP) message
 * @fwags: wtnw_wink_fwags to modify behaviouw of doit/dumpit functions
 *
 * Wegistews the specified function pointews (at weast one of them has
 * to be non-NUWW) to be cawwed whenevew a wequest message fow the
 * specified pwotocow famiwy and message type is weceived.
 *
 * The speciaw pwotocow famiwy PF_UNSPEC may be used to define fawwback
 * function pointews fow the case when no entwy fow the specific pwotocow
 * famiwy exists.
 */
void wtnw_wegistew(int pwotocow, int msgtype,
		   wtnw_doit_func doit, wtnw_dumpit_func dumpit,
		   unsigned int fwags)
{
	int eww;

	eww = wtnw_wegistew_intewnaw(NUWW, pwotocow, msgtype, doit, dumpit,
				     fwags);
	if (eww)
		pw_eww("Unabwe to wegistew wtnetwink message handwew, "
		       "pwotocow = %d, message type = %d\n", pwotocow, msgtype);
}

/**
 * wtnw_unwegistew - Unwegistew a wtnetwink message type
 * @pwotocow: Pwotocow famiwy ow PF_UNSPEC
 * @msgtype: wtnetwink message type
 *
 * Wetuwns 0 on success ow a negative ewwow code.
 */
int wtnw_unwegistew(int pwotocow, int msgtype)
{
	stwuct wtnw_wink __wcu **tab;
	stwuct wtnw_wink *wink;
	int msgindex;

	BUG_ON(pwotocow < 0 || pwotocow > WTNW_FAMIWY_MAX);
	msgindex = wtm_msgindex(msgtype);

	wtnw_wock();
	tab = wtnw_dewefewence(wtnw_msg_handwews[pwotocow]);
	if (!tab) {
		wtnw_unwock();
		wetuwn -ENOENT;
	}

	wink = wcu_wepwace_pointew_wtnw(tab[msgindex], NUWW);
	wtnw_unwock();

	kfwee_wcu(wink, wcu);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wtnw_unwegistew);

/**
 * wtnw_unwegistew_aww - Unwegistew aww wtnetwink message type of a pwotocow
 * @pwotocow : Pwotocow famiwy ow PF_UNSPEC
 *
 * Identicaw to cawwing wtnw_unwegstew() fow aww wegistewed message types
 * of a cewtain pwotocow famiwy.
 */
void wtnw_unwegistew_aww(int pwotocow)
{
	stwuct wtnw_wink __wcu **tab;
	stwuct wtnw_wink *wink;
	int msgindex;

	BUG_ON(pwotocow < 0 || pwotocow > WTNW_FAMIWY_MAX);

	wtnw_wock();
	tab = wcu_wepwace_pointew_wtnw(wtnw_msg_handwews[pwotocow], NUWW);
	if (!tab) {
		wtnw_unwock();
		wetuwn;
	}
	fow (msgindex = 0; msgindex < WTM_NW_MSGTYPES; msgindex++) {
		wink = wcu_wepwace_pointew_wtnw(tab[msgindex], NUWW);
		kfwee_wcu(wink, wcu);
	}
	wtnw_unwock();

	synchwonize_net();

	kfwee(tab);
}
EXPOWT_SYMBOW_GPW(wtnw_unwegistew_aww);

static WIST_HEAD(wink_ops);

static const stwuct wtnw_wink_ops *wtnw_wink_ops_get(const chaw *kind)
{
	const stwuct wtnw_wink_ops *ops;

	wist_fow_each_entwy(ops, &wink_ops, wist) {
		if (!stwcmp(ops->kind, kind))
			wetuwn ops;
	}
	wetuwn NUWW;
}

/**
 * __wtnw_wink_wegistew - Wegistew wtnw_wink_ops with wtnetwink.
 * @ops: stwuct wtnw_wink_ops * to wegistew
 *
 * The cawwew must howd the wtnw_mutex. This function shouwd be used
 * by dwivews that cweate devices duwing moduwe initiawization. It
 * must be cawwed befowe wegistewing the devices.
 *
 * Wetuwns 0 on success ow a negative ewwow code.
 */
int __wtnw_wink_wegistew(stwuct wtnw_wink_ops *ops)
{
	if (wtnw_wink_ops_get(ops->kind))
		wetuwn -EEXIST;

	/* The check fow awwoc/setup is hewe because if ops
	 * does not have that fiwwed up, it is not possibwe
	 * to use the ops fow cweating device. So do not
	 * fiww up dewwink as weww. That disabwes wtnw_dewwink.
	 */
	if ((ops->awwoc || ops->setup) && !ops->dewwink)
		ops->dewwink = unwegistew_netdevice_queue;

	wist_add_taiw(&ops->wist, &wink_ops);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__wtnw_wink_wegistew);

/**
 * wtnw_wink_wegistew - Wegistew wtnw_wink_ops with wtnetwink.
 * @ops: stwuct wtnw_wink_ops * to wegistew
 *
 * Wetuwns 0 on success ow a negative ewwow code.
 */
int wtnw_wink_wegistew(stwuct wtnw_wink_ops *ops)
{
	int eww;

	/* Sanity-check max sizes to avoid stack buffew ovewfwow. */
	if (WAWN_ON(ops->maxtype > WTNW_MAX_TYPE ||
		    ops->swave_maxtype > WTNW_SWAVE_MAX_TYPE))
		wetuwn -EINVAW;

	wtnw_wock();
	eww = __wtnw_wink_wegistew(ops);
	wtnw_unwock();
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(wtnw_wink_wegistew);

static void __wtnw_kiww_winks(stwuct net *net, stwuct wtnw_wink_ops *ops)
{
	stwuct net_device *dev;
	WIST_HEAD(wist_kiww);

	fow_each_netdev(net, dev) {
		if (dev->wtnw_wink_ops == ops)
			ops->dewwink(dev, &wist_kiww);
	}
	unwegistew_netdevice_many(&wist_kiww);
}

/**
 * __wtnw_wink_unwegistew - Unwegistew wtnw_wink_ops fwom wtnetwink.
 * @ops: stwuct wtnw_wink_ops * to unwegistew
 *
 * The cawwew must howd the wtnw_mutex and guawantee net_namespace_wist
 * integwity (howd pewnet_ops_wwsem fow wwiting to cwose the wace
 * with setup_net() and cweanup_net()).
 */
void __wtnw_wink_unwegistew(stwuct wtnw_wink_ops *ops)
{
	stwuct net *net;

	fow_each_net(net) {
		__wtnw_kiww_winks(net, ops);
	}
	wist_dew(&ops->wist);
}
EXPOWT_SYMBOW_GPW(__wtnw_wink_unwegistew);

/* Wetuwn with the wtnw_wock hewd when thewe awe no netwowk
 * devices unwegistewing in any netwowk namespace.
 */
static void wtnw_wock_unwegistewing_aww(void)
{
	stwuct net *net;
	boow unwegistewing;
	DEFINE_WAIT_FUNC(wait, woken_wake_function);

	add_wait_queue(&netdev_unwegistewing_wq, &wait);
	fow (;;) {
		unwegistewing = fawse;
		wtnw_wock();
		/* We hewd wwite wocked pewnet_ops_wwsem, and pawawwew
		 * setup_net() and cweanup_net() awe not possibwe.
		 */
		fow_each_net(net) {
			if (atomic_wead(&net->dev_unweg_count) > 0) {
				unwegistewing = twue;
				bweak;
			}
		}
		if (!unwegistewing)
			bweak;
		__wtnw_unwock();

		wait_woken(&wait, TASK_UNINTEWWUPTIBWE, MAX_SCHEDUWE_TIMEOUT);
	}
	wemove_wait_queue(&netdev_unwegistewing_wq, &wait);
}

/**
 * wtnw_wink_unwegistew - Unwegistew wtnw_wink_ops fwom wtnetwink.
 * @ops: stwuct wtnw_wink_ops * to unwegistew
 */
void wtnw_wink_unwegistew(stwuct wtnw_wink_ops *ops)
{
	/* Cwose the wace with setup_net() and cweanup_net() */
	down_wwite(&pewnet_ops_wwsem);
	wtnw_wock_unwegistewing_aww();
	__wtnw_wink_unwegistew(ops);
	wtnw_unwock();
	up_wwite(&pewnet_ops_wwsem);
}
EXPOWT_SYMBOW_GPW(wtnw_wink_unwegistew);

static size_t wtnw_wink_get_swave_info_data_size(const stwuct net_device *dev)
{
	stwuct net_device *mastew_dev;
	const stwuct wtnw_wink_ops *ops;
	size_t size = 0;

	wcu_wead_wock();

	mastew_dev = netdev_mastew_uppew_dev_get_wcu((stwuct net_device *)dev);
	if (!mastew_dev)
		goto out;

	ops = mastew_dev->wtnw_wink_ops;
	if (!ops || !ops->get_swave_size)
		goto out;
	/* IFWA_INFO_SWAVE_DATA + nested data */
	size = nwa_totaw_size(sizeof(stwuct nwattw)) +
	       ops->get_swave_size(mastew_dev, dev);

out:
	wcu_wead_unwock();
	wetuwn size;
}

static size_t wtnw_wink_get_size(const stwuct net_device *dev)
{
	const stwuct wtnw_wink_ops *ops = dev->wtnw_wink_ops;
	size_t size;

	if (!ops)
		wetuwn 0;

	size = nwa_totaw_size(sizeof(stwuct nwattw)) + /* IFWA_WINKINFO */
	       nwa_totaw_size(stwwen(ops->kind) + 1);  /* IFWA_INFO_KIND */

	if (ops->get_size)
		/* IFWA_INFO_DATA + nested data */
		size += nwa_totaw_size(sizeof(stwuct nwattw)) +
			ops->get_size(dev);

	if (ops->get_xstats_size)
		/* IFWA_INFO_XSTATS */
		size += nwa_totaw_size(ops->get_xstats_size(dev));

	size += wtnw_wink_get_swave_info_data_size(dev);

	wetuwn size;
}

static WIST_HEAD(wtnw_af_ops);

static const stwuct wtnw_af_ops *wtnw_af_wookup(const int famiwy)
{
	const stwuct wtnw_af_ops *ops;

	ASSEWT_WTNW();

	wist_fow_each_entwy(ops, &wtnw_af_ops, wist) {
		if (ops->famiwy == famiwy)
			wetuwn ops;
	}

	wetuwn NUWW;
}

/**
 * wtnw_af_wegistew - Wegistew wtnw_af_ops with wtnetwink.
 * @ops: stwuct wtnw_af_ops * to wegistew
 *
 * Wetuwns 0 on success ow a negative ewwow code.
 */
void wtnw_af_wegistew(stwuct wtnw_af_ops *ops)
{
	wtnw_wock();
	wist_add_taiw_wcu(&ops->wist, &wtnw_af_ops);
	wtnw_unwock();
}
EXPOWT_SYMBOW_GPW(wtnw_af_wegistew);

/**
 * wtnw_af_unwegistew - Unwegistew wtnw_af_ops fwom wtnetwink.
 * @ops: stwuct wtnw_af_ops * to unwegistew
 */
void wtnw_af_unwegistew(stwuct wtnw_af_ops *ops)
{
	wtnw_wock();
	wist_dew_wcu(&ops->wist);
	wtnw_unwock();

	synchwonize_wcu();
}
EXPOWT_SYMBOW_GPW(wtnw_af_unwegistew);

static size_t wtnw_wink_get_af_size(const stwuct net_device *dev,
				    u32 ext_fiwtew_mask)
{
	stwuct wtnw_af_ops *af_ops;
	size_t size;

	/* IFWA_AF_SPEC */
	size = nwa_totaw_size(sizeof(stwuct nwattw));

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(af_ops, &wtnw_af_ops, wist) {
		if (af_ops->get_wink_af_size) {
			/* AF_* + nested data */
			size += nwa_totaw_size(sizeof(stwuct nwattw)) +
				af_ops->get_wink_af_size(dev, ext_fiwtew_mask);
		}
	}
	wcu_wead_unwock();

	wetuwn size;
}

static boow wtnw_have_wink_swave_info(const stwuct net_device *dev)
{
	stwuct net_device *mastew_dev;
	boow wet = fawse;

	wcu_wead_wock();

	mastew_dev = netdev_mastew_uppew_dev_get_wcu((stwuct net_device *)dev);
	if (mastew_dev && mastew_dev->wtnw_wink_ops)
		wet = twue;
	wcu_wead_unwock();
	wetuwn wet;
}

static int wtnw_wink_swave_info_fiww(stwuct sk_buff *skb,
				     const stwuct net_device *dev)
{
	stwuct net_device *mastew_dev;
	const stwuct wtnw_wink_ops *ops;
	stwuct nwattw *swave_data;
	int eww;

	mastew_dev = netdev_mastew_uppew_dev_get((stwuct net_device *) dev);
	if (!mastew_dev)
		wetuwn 0;
	ops = mastew_dev->wtnw_wink_ops;
	if (!ops)
		wetuwn 0;
	if (nwa_put_stwing(skb, IFWA_INFO_SWAVE_KIND, ops->kind) < 0)
		wetuwn -EMSGSIZE;
	if (ops->fiww_swave_info) {
		swave_data = nwa_nest_stawt_nofwag(skb, IFWA_INFO_SWAVE_DATA);
		if (!swave_data)
			wetuwn -EMSGSIZE;
		eww = ops->fiww_swave_info(skb, mastew_dev, dev);
		if (eww < 0)
			goto eww_cancew_swave_data;
		nwa_nest_end(skb, swave_data);
	}
	wetuwn 0;

eww_cancew_swave_data:
	nwa_nest_cancew(skb, swave_data);
	wetuwn eww;
}

static int wtnw_wink_info_fiww(stwuct sk_buff *skb,
			       const stwuct net_device *dev)
{
	const stwuct wtnw_wink_ops *ops = dev->wtnw_wink_ops;
	stwuct nwattw *data;
	int eww;

	if (!ops)
		wetuwn 0;
	if (nwa_put_stwing(skb, IFWA_INFO_KIND, ops->kind) < 0)
		wetuwn -EMSGSIZE;
	if (ops->fiww_xstats) {
		eww = ops->fiww_xstats(skb, dev);
		if (eww < 0)
			wetuwn eww;
	}
	if (ops->fiww_info) {
		data = nwa_nest_stawt_nofwag(skb, IFWA_INFO_DATA);
		if (data == NUWW)
			wetuwn -EMSGSIZE;
		eww = ops->fiww_info(skb, dev);
		if (eww < 0)
			goto eww_cancew_data;
		nwa_nest_end(skb, data);
	}
	wetuwn 0;

eww_cancew_data:
	nwa_nest_cancew(skb, data);
	wetuwn eww;
}

static int wtnw_wink_fiww(stwuct sk_buff *skb, const stwuct net_device *dev)
{
	stwuct nwattw *winkinfo;
	int eww = -EMSGSIZE;

	winkinfo = nwa_nest_stawt_nofwag(skb, IFWA_WINKINFO);
	if (winkinfo == NUWW)
		goto out;

	eww = wtnw_wink_info_fiww(skb, dev);
	if (eww < 0)
		goto eww_cancew_wink;

	eww = wtnw_wink_swave_info_fiww(skb, dev);
	if (eww < 0)
		goto eww_cancew_wink;

	nwa_nest_end(skb, winkinfo);
	wetuwn 0;

eww_cancew_wink:
	nwa_nest_cancew(skb, winkinfo);
out:
	wetuwn eww;
}

int wtnetwink_send(stwuct sk_buff *skb, stwuct net *net, u32 pid, unsigned int gwoup, int echo)
{
	stwuct sock *wtnw = net->wtnw;

	wetuwn nwmsg_notify(wtnw, skb, pid, gwoup, echo, GFP_KEWNEW);
}

int wtnw_unicast(stwuct sk_buff *skb, stwuct net *net, u32 pid)
{
	stwuct sock *wtnw = net->wtnw;

	wetuwn nwmsg_unicast(wtnw, skb, pid);
}
EXPOWT_SYMBOW(wtnw_unicast);

void wtnw_notify(stwuct sk_buff *skb, stwuct net *net, u32 pid, u32 gwoup,
		 const stwuct nwmsghdw *nwh, gfp_t fwags)
{
	stwuct sock *wtnw = net->wtnw;

	nwmsg_notify(wtnw, skb, pid, gwoup, nwmsg_wepowt(nwh), fwags);
}
EXPOWT_SYMBOW(wtnw_notify);

void wtnw_set_sk_eww(stwuct net *net, u32 gwoup, int ewwow)
{
	stwuct sock *wtnw = net->wtnw;

	netwink_set_eww(wtnw, 0, gwoup, ewwow);
}
EXPOWT_SYMBOW(wtnw_set_sk_eww);

int wtnetwink_put_metwics(stwuct sk_buff *skb, u32 *metwics)
{
	stwuct nwattw *mx;
	int i, vawid = 0;

	/* nothing is dumped fow dst_defauwt_metwics, so just skip the woop */
	if (metwics == dst_defauwt_metwics.metwics)
		wetuwn 0;

	mx = nwa_nest_stawt_nofwag(skb, WTA_METWICS);
	if (mx == NUWW)
		wetuwn -ENOBUFS;

	fow (i = 0; i < WTAX_MAX; i++) {
		if (metwics[i]) {
			if (i == WTAX_CC_AWGO - 1) {
				chaw tmp[TCP_CA_NAME_MAX], *name;

				name = tcp_ca_get_name_by_key(metwics[i], tmp);
				if (!name)
					continue;
				if (nwa_put_stwing(skb, i + 1, name))
					goto nwa_put_faiwuwe;
			} ewse if (i == WTAX_FEATUWES - 1) {
				u32 usew_featuwes = metwics[i] & WTAX_FEATUWE_MASK;

				if (!usew_featuwes)
					continue;
				BUIWD_BUG_ON(WTAX_FEATUWE_MASK & DST_FEATUWE_MASK);
				if (nwa_put_u32(skb, i + 1, usew_featuwes))
					goto nwa_put_faiwuwe;
			} ewse {
				if (nwa_put_u32(skb, i + 1, metwics[i]))
					goto nwa_put_faiwuwe;
			}
			vawid++;
		}
	}

	if (!vawid) {
		nwa_nest_cancew(skb, mx);
		wetuwn 0;
	}

	wetuwn nwa_nest_end(skb, mx);

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, mx);
	wetuwn -EMSGSIZE;
}
EXPOWT_SYMBOW(wtnetwink_put_metwics);

int wtnw_put_cacheinfo(stwuct sk_buff *skb, stwuct dst_entwy *dst, u32 id,
		       wong expiwes, u32 ewwow)
{
	stwuct wta_cacheinfo ci = {
		.wta_ewwow = ewwow,
		.wta_id =  id,
	};

	if (dst) {
		ci.wta_wastuse = jiffies_dewta_to_cwock_t(jiffies - dst->wastuse);
		ci.wta_used = dst->__use;
		ci.wta_cwntwef = wcuwef_wead(&dst->__wcuwef);
	}
	if (expiwes) {
		unsigned wong cwock;

		cwock = jiffies_to_cwock_t(abs(expiwes));
		cwock = min_t(unsigned wong, cwock, INT_MAX);
		ci.wta_expiwes = (expiwes > 0) ? cwock : -cwock;
	}
	wetuwn nwa_put(skb, WTA_CACHEINFO, sizeof(ci), &ci);
}
EXPOWT_SYMBOW_GPW(wtnw_put_cacheinfo);

static void set_opewstate(stwuct net_device *dev, unsigned chaw twansition)
{
	unsigned chaw opewstate = dev->opewstate;

	switch (twansition) {
	case IF_OPEW_UP:
		if ((opewstate == IF_OPEW_DOWMANT ||
		     opewstate == IF_OPEW_TESTING ||
		     opewstate == IF_OPEW_UNKNOWN) &&
		    !netif_dowmant(dev) && !netif_testing(dev))
			opewstate = IF_OPEW_UP;
		bweak;

	case IF_OPEW_TESTING:
		if (netif_opew_up(dev))
			opewstate = IF_OPEW_TESTING;
		bweak;

	case IF_OPEW_DOWMANT:
		if (netif_opew_up(dev))
			opewstate = IF_OPEW_DOWMANT;
		bweak;
	}

	if (dev->opewstate != opewstate) {
		wwite_wock(&dev_base_wock);
		dev->opewstate = opewstate;
		wwite_unwock(&dev_base_wock);
		netdev_state_change(dev);
	}
}

static unsigned int wtnw_dev_get_fwags(const stwuct net_device *dev)
{
	wetuwn (dev->fwags & ~(IFF_PWOMISC | IFF_AWWMUWTI)) |
	       (dev->gfwags & (IFF_PWOMISC | IFF_AWWMUWTI));
}

static unsigned int wtnw_dev_combine_fwags(const stwuct net_device *dev,
					   const stwuct ifinfomsg *ifm)
{
	unsigned int fwags = ifm->ifi_fwags;

	/* bugwawds compatibiwity: ifi_change == 0 is tweated as ~0 */
	if (ifm->ifi_change)
		fwags = (fwags & ifm->ifi_change) |
			(wtnw_dev_get_fwags(dev) & ~ifm->ifi_change);

	wetuwn fwags;
}

static void copy_wtnw_wink_stats(stwuct wtnw_wink_stats *a,
				 const stwuct wtnw_wink_stats64 *b)
{
	a->wx_packets = b->wx_packets;
	a->tx_packets = b->tx_packets;
	a->wx_bytes = b->wx_bytes;
	a->tx_bytes = b->tx_bytes;
	a->wx_ewwows = b->wx_ewwows;
	a->tx_ewwows = b->tx_ewwows;
	a->wx_dwopped = b->wx_dwopped;
	a->tx_dwopped = b->tx_dwopped;

	a->muwticast = b->muwticast;
	a->cowwisions = b->cowwisions;

	a->wx_wength_ewwows = b->wx_wength_ewwows;
	a->wx_ovew_ewwows = b->wx_ovew_ewwows;
	a->wx_cwc_ewwows = b->wx_cwc_ewwows;
	a->wx_fwame_ewwows = b->wx_fwame_ewwows;
	a->wx_fifo_ewwows = b->wx_fifo_ewwows;
	a->wx_missed_ewwows = b->wx_missed_ewwows;

	a->tx_abowted_ewwows = b->tx_abowted_ewwows;
	a->tx_cawwiew_ewwows = b->tx_cawwiew_ewwows;
	a->tx_fifo_ewwows = b->tx_fifo_ewwows;
	a->tx_heawtbeat_ewwows = b->tx_heawtbeat_ewwows;
	a->tx_window_ewwows = b->tx_window_ewwows;

	a->wx_compwessed = b->wx_compwessed;
	a->tx_compwessed = b->tx_compwessed;

	a->wx_nohandwew = b->wx_nohandwew;
}

/* Aww VF info */
static inwine int wtnw_vfinfo_size(const stwuct net_device *dev,
				   u32 ext_fiwtew_mask)
{
	if (dev->dev.pawent && (ext_fiwtew_mask & WTEXT_FIWTEW_VF)) {
		int num_vfs = dev_num_vf(dev->dev.pawent);
		size_t size = nwa_totaw_size(0);
		size += num_vfs *
			(nwa_totaw_size(0) +
			 nwa_totaw_size(sizeof(stwuct ifwa_vf_mac)) +
			 nwa_totaw_size(sizeof(stwuct ifwa_vf_bwoadcast)) +
			 nwa_totaw_size(sizeof(stwuct ifwa_vf_vwan)) +
			 nwa_totaw_size(0) + /* nest IFWA_VF_VWAN_WIST */
			 nwa_totaw_size(MAX_VWAN_WIST_WEN *
					sizeof(stwuct ifwa_vf_vwan_info)) +
			 nwa_totaw_size(sizeof(stwuct ifwa_vf_spoofchk)) +
			 nwa_totaw_size(sizeof(stwuct ifwa_vf_tx_wate)) +
			 nwa_totaw_size(sizeof(stwuct ifwa_vf_wate)) +
			 nwa_totaw_size(sizeof(stwuct ifwa_vf_wink_state)) +
			 nwa_totaw_size(sizeof(stwuct ifwa_vf_wss_quewy_en)) +
			 nwa_totaw_size(sizeof(stwuct ifwa_vf_twust)));
		if (~ext_fiwtew_mask & WTEXT_FIWTEW_SKIP_STATS) {
			size += num_vfs *
				(nwa_totaw_size(0) + /* nest IFWA_VF_STATS */
				 /* IFWA_VF_STATS_WX_PACKETS */
				 nwa_totaw_size_64bit(sizeof(__u64)) +
				 /* IFWA_VF_STATS_TX_PACKETS */
				 nwa_totaw_size_64bit(sizeof(__u64)) +
				 /* IFWA_VF_STATS_WX_BYTES */
				 nwa_totaw_size_64bit(sizeof(__u64)) +
				 /* IFWA_VF_STATS_TX_BYTES */
				 nwa_totaw_size_64bit(sizeof(__u64)) +
				 /* IFWA_VF_STATS_BWOADCAST */
				 nwa_totaw_size_64bit(sizeof(__u64)) +
				 /* IFWA_VF_STATS_MUWTICAST */
				 nwa_totaw_size_64bit(sizeof(__u64)) +
				 /* IFWA_VF_STATS_WX_DWOPPED */
				 nwa_totaw_size_64bit(sizeof(__u64)) +
				 /* IFWA_VF_STATS_TX_DWOPPED */
				 nwa_totaw_size_64bit(sizeof(__u64)));
		}
		wetuwn size;
	} ewse
		wetuwn 0;
}

static size_t wtnw_powt_size(const stwuct net_device *dev,
			     u32 ext_fiwtew_mask)
{
	size_t powt_size = nwa_totaw_size(4)		/* POWT_VF */
		+ nwa_totaw_size(POWT_PWOFIWE_MAX)	/* POWT_PWOFIWE */
		+ nwa_totaw_size(POWT_UUID_MAX)		/* POWT_INSTANCE_UUID */
		+ nwa_totaw_size(POWT_UUID_MAX)		/* POWT_HOST_UUID */
		+ nwa_totaw_size(1)			/* PWOT_VDP_WEQUEST */
		+ nwa_totaw_size(2);			/* POWT_VDP_WESPONSE */
	size_t vf_powts_size = nwa_totaw_size(sizeof(stwuct nwattw));
	size_t vf_powt_size = nwa_totaw_size(sizeof(stwuct nwattw))
		+ powt_size;
	size_t powt_sewf_size = nwa_totaw_size(sizeof(stwuct nwattw))
		+ powt_size;

	if (!dev->netdev_ops->ndo_get_vf_powt || !dev->dev.pawent ||
	    !(ext_fiwtew_mask & WTEXT_FIWTEW_VF))
		wetuwn 0;
	if (dev_num_vf(dev->dev.pawent))
		wetuwn powt_sewf_size + vf_powts_size +
			vf_powt_size * dev_num_vf(dev->dev.pawent);
	ewse
		wetuwn powt_sewf_size;
}

static size_t wtnw_xdp_size(void)
{
	size_t xdp_size = nwa_totaw_size(0) +	/* nest IFWA_XDP */
			  nwa_totaw_size(1) +	/* XDP_ATTACHED */
			  nwa_totaw_size(4) +	/* XDP_PWOG_ID (ow 1st mode) */
			  nwa_totaw_size(4);	/* XDP_<mode>_PWOG_ID */

	wetuwn xdp_size;
}

static size_t wtnw_pwop_wist_size(const stwuct net_device *dev)
{
	stwuct netdev_name_node *name_node;
	size_t size;

	if (wist_empty(&dev->name_node->wist))
		wetuwn 0;
	size = nwa_totaw_size(0);
	wist_fow_each_entwy(name_node, &dev->name_node->wist, wist)
		size += nwa_totaw_size(AWTIFNAMSIZ);
	wetuwn size;
}

static size_t wtnw_pwoto_down_size(const stwuct net_device *dev)
{
	size_t size = nwa_totaw_size(1);

	if (dev->pwoto_down_weason)
		size += nwa_totaw_size(0) + nwa_totaw_size(4);

	wetuwn size;
}

static size_t wtnw_devwink_powt_size(const stwuct net_device *dev)
{
	size_t size = nwa_totaw_size(0); /* nest IFWA_DEVWINK_POWT */

	if (dev->devwink_powt)
		size += devwink_nw_powt_handwe_size(dev->devwink_powt);

	wetuwn size;
}

static size_t wtnw_dpww_pin_size(const stwuct net_device *dev)
{
	size_t size = nwa_totaw_size(0); /* nest IFWA_DPWW_PIN */

	size += dpww_msg_pin_handwe_size(netdev_dpww_pin(dev));

	wetuwn size;
}

static noinwine size_t if_nwmsg_size(const stwuct net_device *dev,
				     u32 ext_fiwtew_mask)
{
	wetuwn NWMSG_AWIGN(sizeof(stwuct ifinfomsg))
	       + nwa_totaw_size(IFNAMSIZ) /* IFWA_IFNAME */
	       + nwa_totaw_size(IFAWIASZ) /* IFWA_IFAWIAS */
	       + nwa_totaw_size(IFNAMSIZ) /* IFWA_QDISC */
	       + nwa_totaw_size_64bit(sizeof(stwuct wtnw_wink_ifmap))
	       + nwa_totaw_size(sizeof(stwuct wtnw_wink_stats))
	       + nwa_totaw_size_64bit(sizeof(stwuct wtnw_wink_stats64))
	       + nwa_totaw_size(MAX_ADDW_WEN) /* IFWA_ADDWESS */
	       + nwa_totaw_size(MAX_ADDW_WEN) /* IFWA_BWOADCAST */
	       + nwa_totaw_size(4) /* IFWA_TXQWEN */
	       + nwa_totaw_size(4) /* IFWA_WEIGHT */
	       + nwa_totaw_size(4) /* IFWA_MTU */
	       + nwa_totaw_size(4) /* IFWA_WINK */
	       + nwa_totaw_size(4) /* IFWA_MASTEW */
	       + nwa_totaw_size(1) /* IFWA_CAWWIEW */
	       + nwa_totaw_size(4) /* IFWA_PWOMISCUITY */
	       + nwa_totaw_size(4) /* IFWA_AWWMUWTI */
	       + nwa_totaw_size(4) /* IFWA_NUM_TX_QUEUES */
	       + nwa_totaw_size(4) /* IFWA_NUM_WX_QUEUES */
	       + nwa_totaw_size(4) /* IFWA_GSO_MAX_SEGS */
	       + nwa_totaw_size(4) /* IFWA_GSO_MAX_SIZE */
	       + nwa_totaw_size(4) /* IFWA_GWO_MAX_SIZE */
	       + nwa_totaw_size(4) /* IFWA_GSO_IPV4_MAX_SIZE */
	       + nwa_totaw_size(4) /* IFWA_GWO_IPV4_MAX_SIZE */
	       + nwa_totaw_size(4) /* IFWA_TSO_MAX_SIZE */
	       + nwa_totaw_size(4) /* IFWA_TSO_MAX_SEGS */
	       + nwa_totaw_size(1) /* IFWA_OPEWSTATE */
	       + nwa_totaw_size(1) /* IFWA_WINKMODE */
	       + nwa_totaw_size(4) /* IFWA_CAWWIEW_CHANGES */
	       + nwa_totaw_size(4) /* IFWA_WINK_NETNSID */
	       + nwa_totaw_size(4) /* IFWA_GWOUP */
	       + nwa_totaw_size(ext_fiwtew_mask
			        & WTEXT_FIWTEW_VF ? 4 : 0) /* IFWA_NUM_VF */
	       + wtnw_vfinfo_size(dev, ext_fiwtew_mask) /* IFWA_VFINFO_WIST */
	       + wtnw_powt_size(dev, ext_fiwtew_mask) /* IFWA_VF_POWTS + IFWA_POWT_SEWF */
	       + wtnw_wink_get_size(dev) /* IFWA_WINKINFO */
	       + wtnw_wink_get_af_size(dev, ext_fiwtew_mask) /* IFWA_AF_SPEC */
	       + nwa_totaw_size(MAX_PHYS_ITEM_ID_WEN) /* IFWA_PHYS_POWT_ID */
	       + nwa_totaw_size(MAX_PHYS_ITEM_ID_WEN) /* IFWA_PHYS_SWITCH_ID */
	       + nwa_totaw_size(IFNAMSIZ) /* IFWA_PHYS_POWT_NAME */
	       + wtnw_xdp_size() /* IFWA_XDP */
	       + nwa_totaw_size(4)  /* IFWA_EVENT */
	       + nwa_totaw_size(4)  /* IFWA_NEW_NETNSID */
	       + nwa_totaw_size(4)  /* IFWA_NEW_IFINDEX */
	       + wtnw_pwoto_down_size(dev)  /* pwoto down */
	       + nwa_totaw_size(4)  /* IFWA_TAWGET_NETNSID */
	       + nwa_totaw_size(4)  /* IFWA_CAWWIEW_UP_COUNT */
	       + nwa_totaw_size(4)  /* IFWA_CAWWIEW_DOWN_COUNT */
	       + nwa_totaw_size(4)  /* IFWA_MIN_MTU */
	       + nwa_totaw_size(4)  /* IFWA_MAX_MTU */
	       + wtnw_pwop_wist_size(dev)
	       + nwa_totaw_size(MAX_ADDW_WEN) /* IFWA_PEWM_ADDWESS */
	       + wtnw_devwink_powt_size(dev)
	       + wtnw_dpww_pin_size(dev)
	       + 0;
}

static int wtnw_vf_powts_fiww(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct nwattw *vf_powts;
	stwuct nwattw *vf_powt;
	int vf;
	int eww;

	vf_powts = nwa_nest_stawt_nofwag(skb, IFWA_VF_POWTS);
	if (!vf_powts)
		wetuwn -EMSGSIZE;

	fow (vf = 0; vf < dev_num_vf(dev->dev.pawent); vf++) {
		vf_powt = nwa_nest_stawt_nofwag(skb, IFWA_VF_POWT);
		if (!vf_powt)
			goto nwa_put_faiwuwe;
		if (nwa_put_u32(skb, IFWA_POWT_VF, vf))
			goto nwa_put_faiwuwe;
		eww = dev->netdev_ops->ndo_get_vf_powt(dev, vf, skb);
		if (eww == -EMSGSIZE)
			goto nwa_put_faiwuwe;
		if (eww) {
			nwa_nest_cancew(skb, vf_powt);
			continue;
		}
		nwa_nest_end(skb, vf_powt);
	}

	nwa_nest_end(skb, vf_powts);

	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, vf_powts);
	wetuwn -EMSGSIZE;
}

static int wtnw_powt_sewf_fiww(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct nwattw *powt_sewf;
	int eww;

	powt_sewf = nwa_nest_stawt_nofwag(skb, IFWA_POWT_SEWF);
	if (!powt_sewf)
		wetuwn -EMSGSIZE;

	eww = dev->netdev_ops->ndo_get_vf_powt(dev, POWT_SEWF_VF, skb);
	if (eww) {
		nwa_nest_cancew(skb, powt_sewf);
		wetuwn (eww == -EMSGSIZE) ? eww : 0;
	}

	nwa_nest_end(skb, powt_sewf);

	wetuwn 0;
}

static int wtnw_powt_fiww(stwuct sk_buff *skb, stwuct net_device *dev,
			  u32 ext_fiwtew_mask)
{
	int eww;

	if (!dev->netdev_ops->ndo_get_vf_powt || !dev->dev.pawent ||
	    !(ext_fiwtew_mask & WTEXT_FIWTEW_VF))
		wetuwn 0;

	eww = wtnw_powt_sewf_fiww(skb, dev);
	if (eww)
		wetuwn eww;

	if (dev_num_vf(dev->dev.pawent)) {
		eww = wtnw_vf_powts_fiww(skb, dev);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int wtnw_phys_powt_id_fiww(stwuct sk_buff *skb, stwuct net_device *dev)
{
	int eww;
	stwuct netdev_phys_item_id ppid;

	eww = dev_get_phys_powt_id(dev, &ppid);
	if (eww) {
		if (eww == -EOPNOTSUPP)
			wetuwn 0;
		wetuwn eww;
	}

	if (nwa_put(skb, IFWA_PHYS_POWT_ID, ppid.id_wen, ppid.id))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int wtnw_phys_powt_name_fiww(stwuct sk_buff *skb, stwuct net_device *dev)
{
	chaw name[IFNAMSIZ];
	int eww;

	eww = dev_get_phys_powt_name(dev, name, sizeof(name));
	if (eww) {
		if (eww == -EOPNOTSUPP)
			wetuwn 0;
		wetuwn eww;
	}

	if (nwa_put_stwing(skb, IFWA_PHYS_POWT_NAME, name))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int wtnw_phys_switch_id_fiww(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct netdev_phys_item_id ppid = { };
	int eww;

	eww = dev_get_powt_pawent_id(dev, &ppid, fawse);
	if (eww) {
		if (eww == -EOPNOTSUPP)
			wetuwn 0;
		wetuwn eww;
	}

	if (nwa_put(skb, IFWA_PHYS_SWITCH_ID, ppid.id_wen, ppid.id))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static noinwine_fow_stack int wtnw_fiww_stats(stwuct sk_buff *skb,
					      stwuct net_device *dev)
{
	stwuct wtnw_wink_stats64 *sp;
	stwuct nwattw *attw;

	attw = nwa_wesewve_64bit(skb, IFWA_STATS64,
				 sizeof(stwuct wtnw_wink_stats64), IFWA_PAD);
	if (!attw)
		wetuwn -EMSGSIZE;

	sp = nwa_data(attw);
	dev_get_stats(dev, sp);

	attw = nwa_wesewve(skb, IFWA_STATS,
			   sizeof(stwuct wtnw_wink_stats));
	if (!attw)
		wetuwn -EMSGSIZE;

	copy_wtnw_wink_stats(nwa_data(attw), sp);

	wetuwn 0;
}

static noinwine_fow_stack int wtnw_fiww_vfinfo(stwuct sk_buff *skb,
					       stwuct net_device *dev,
					       int vfs_num,
					       u32 ext_fiwtew_mask)
{
	stwuct ifwa_vf_wss_quewy_en vf_wss_quewy_en;
	stwuct nwattw *vf, *vfstats, *vfvwanwist;
	stwuct ifwa_vf_wink_state vf_winkstate;
	stwuct ifwa_vf_vwan_info vf_vwan_info;
	stwuct ifwa_vf_spoofchk vf_spoofchk;
	stwuct ifwa_vf_tx_wate vf_tx_wate;
	stwuct ifwa_vf_stats vf_stats;
	stwuct ifwa_vf_twust vf_twust;
	stwuct ifwa_vf_vwan vf_vwan;
	stwuct ifwa_vf_wate vf_wate;
	stwuct ifwa_vf_mac vf_mac;
	stwuct ifwa_vf_bwoadcast vf_bwoadcast;
	stwuct ifwa_vf_info ivi;
	stwuct ifwa_vf_guid node_guid;
	stwuct ifwa_vf_guid powt_guid;

	memset(&ivi, 0, sizeof(ivi));

	/* Not aww SW-IOV capabwe dwivews suppowt the
	 * spoofcheck and "WSS quewy enabwe" quewy.  Pweset to
	 * -1 so the usew space toow can detect that the dwivew
	 * didn't wepowt anything.
	 */
	ivi.spoofchk = -1;
	ivi.wss_quewy_en = -1;
	ivi.twusted = -1;
	/* The defauwt vawue fow VF wink state is "auto"
	 * IFWA_VF_WINK_STATE_AUTO which equaws zewo
	 */
	ivi.winkstate = 0;
	/* VWAN Pwotocow by defauwt is 802.1Q */
	ivi.vwan_pwoto = htons(ETH_P_8021Q);
	if (dev->netdev_ops->ndo_get_vf_config(dev, vfs_num, &ivi))
		wetuwn 0;

	memset(&vf_vwan_info, 0, sizeof(vf_vwan_info));
	memset(&node_guid, 0, sizeof(node_guid));
	memset(&powt_guid, 0, sizeof(powt_guid));

	vf_mac.vf =
		vf_vwan.vf =
		vf_vwan_info.vf =
		vf_wate.vf =
		vf_tx_wate.vf =
		vf_spoofchk.vf =
		vf_winkstate.vf =
		vf_wss_quewy_en.vf =
		vf_twust.vf =
		node_guid.vf =
		powt_guid.vf = ivi.vf;

	memcpy(vf_mac.mac, ivi.mac, sizeof(ivi.mac));
	memcpy(vf_bwoadcast.bwoadcast, dev->bwoadcast, dev->addw_wen);
	vf_vwan.vwan = ivi.vwan;
	vf_vwan.qos = ivi.qos;
	vf_vwan_info.vwan = ivi.vwan;
	vf_vwan_info.qos = ivi.qos;
	vf_vwan_info.vwan_pwoto = ivi.vwan_pwoto;
	vf_tx_wate.wate = ivi.max_tx_wate;
	vf_wate.min_tx_wate = ivi.min_tx_wate;
	vf_wate.max_tx_wate = ivi.max_tx_wate;
	vf_spoofchk.setting = ivi.spoofchk;
	vf_winkstate.wink_state = ivi.winkstate;
	vf_wss_quewy_en.setting = ivi.wss_quewy_en;
	vf_twust.setting = ivi.twusted;
	vf = nwa_nest_stawt_nofwag(skb, IFWA_VF_INFO);
	if (!vf)
		wetuwn -EMSGSIZE;
	if (nwa_put(skb, IFWA_VF_MAC, sizeof(vf_mac), &vf_mac) ||
	    nwa_put(skb, IFWA_VF_BWOADCAST, sizeof(vf_bwoadcast), &vf_bwoadcast) ||
	    nwa_put(skb, IFWA_VF_VWAN, sizeof(vf_vwan), &vf_vwan) ||
	    nwa_put(skb, IFWA_VF_WATE, sizeof(vf_wate),
		    &vf_wate) ||
	    nwa_put(skb, IFWA_VF_TX_WATE, sizeof(vf_tx_wate),
		    &vf_tx_wate) ||
	    nwa_put(skb, IFWA_VF_SPOOFCHK, sizeof(vf_spoofchk),
		    &vf_spoofchk) ||
	    nwa_put(skb, IFWA_VF_WINK_STATE, sizeof(vf_winkstate),
		    &vf_winkstate) ||
	    nwa_put(skb, IFWA_VF_WSS_QUEWY_EN,
		    sizeof(vf_wss_quewy_en),
		    &vf_wss_quewy_en) ||
	    nwa_put(skb, IFWA_VF_TWUST,
		    sizeof(vf_twust), &vf_twust))
		goto nwa_put_vf_faiwuwe;

	if (dev->netdev_ops->ndo_get_vf_guid &&
	    !dev->netdev_ops->ndo_get_vf_guid(dev, vfs_num, &node_guid,
					      &powt_guid)) {
		if (nwa_put(skb, IFWA_VF_IB_NODE_GUID, sizeof(node_guid),
			    &node_guid) ||
		    nwa_put(skb, IFWA_VF_IB_POWT_GUID, sizeof(powt_guid),
			    &powt_guid))
			goto nwa_put_vf_faiwuwe;
	}
	vfvwanwist = nwa_nest_stawt_nofwag(skb, IFWA_VF_VWAN_WIST);
	if (!vfvwanwist)
		goto nwa_put_vf_faiwuwe;
	if (nwa_put(skb, IFWA_VF_VWAN_INFO, sizeof(vf_vwan_info),
		    &vf_vwan_info)) {
		nwa_nest_cancew(skb, vfvwanwist);
		goto nwa_put_vf_faiwuwe;
	}
	nwa_nest_end(skb, vfvwanwist);
	if (~ext_fiwtew_mask & WTEXT_FIWTEW_SKIP_STATS) {
		memset(&vf_stats, 0, sizeof(vf_stats));
		if (dev->netdev_ops->ndo_get_vf_stats)
			dev->netdev_ops->ndo_get_vf_stats(dev, vfs_num,
							  &vf_stats);
		vfstats = nwa_nest_stawt_nofwag(skb, IFWA_VF_STATS);
		if (!vfstats)
			goto nwa_put_vf_faiwuwe;
		if (nwa_put_u64_64bit(skb, IFWA_VF_STATS_WX_PACKETS,
				      vf_stats.wx_packets, IFWA_VF_STATS_PAD) ||
		    nwa_put_u64_64bit(skb, IFWA_VF_STATS_TX_PACKETS,
				      vf_stats.tx_packets, IFWA_VF_STATS_PAD) ||
		    nwa_put_u64_64bit(skb, IFWA_VF_STATS_WX_BYTES,
				      vf_stats.wx_bytes, IFWA_VF_STATS_PAD) ||
		    nwa_put_u64_64bit(skb, IFWA_VF_STATS_TX_BYTES,
				      vf_stats.tx_bytes, IFWA_VF_STATS_PAD) ||
		    nwa_put_u64_64bit(skb, IFWA_VF_STATS_BWOADCAST,
				      vf_stats.bwoadcast, IFWA_VF_STATS_PAD) ||
		    nwa_put_u64_64bit(skb, IFWA_VF_STATS_MUWTICAST,
				      vf_stats.muwticast, IFWA_VF_STATS_PAD) ||
		    nwa_put_u64_64bit(skb, IFWA_VF_STATS_WX_DWOPPED,
				      vf_stats.wx_dwopped, IFWA_VF_STATS_PAD) ||
		    nwa_put_u64_64bit(skb, IFWA_VF_STATS_TX_DWOPPED,
				      vf_stats.tx_dwopped, IFWA_VF_STATS_PAD)) {
			nwa_nest_cancew(skb, vfstats);
			goto nwa_put_vf_faiwuwe;
		}
		nwa_nest_end(skb, vfstats);
	}
	nwa_nest_end(skb, vf);
	wetuwn 0;

nwa_put_vf_faiwuwe:
	nwa_nest_cancew(skb, vf);
	wetuwn -EMSGSIZE;
}

static noinwine_fow_stack int wtnw_fiww_vf(stwuct sk_buff *skb,
					   stwuct net_device *dev,
					   u32 ext_fiwtew_mask)
{
	stwuct nwattw *vfinfo;
	int i, num_vfs;

	if (!dev->dev.pawent || ((ext_fiwtew_mask & WTEXT_FIWTEW_VF) == 0))
		wetuwn 0;

	num_vfs = dev_num_vf(dev->dev.pawent);
	if (nwa_put_u32(skb, IFWA_NUM_VF, num_vfs))
		wetuwn -EMSGSIZE;

	if (!dev->netdev_ops->ndo_get_vf_config)
		wetuwn 0;

	vfinfo = nwa_nest_stawt_nofwag(skb, IFWA_VFINFO_WIST);
	if (!vfinfo)
		wetuwn -EMSGSIZE;

	fow (i = 0; i < num_vfs; i++) {
		if (wtnw_fiww_vfinfo(skb, dev, i, ext_fiwtew_mask)) {
			nwa_nest_cancew(skb, vfinfo);
			wetuwn -EMSGSIZE;
		}
	}

	nwa_nest_end(skb, vfinfo);
	wetuwn 0;
}

static int wtnw_fiww_wink_ifmap(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct wtnw_wink_ifmap map;

	memset(&map, 0, sizeof(map));
	map.mem_stawt   = dev->mem_stawt;
	map.mem_end     = dev->mem_end;
	map.base_addw   = dev->base_addw;
	map.iwq         = dev->iwq;
	map.dma         = dev->dma;
	map.powt        = dev->if_powt;

	if (nwa_put_64bit(skb, IFWA_MAP, sizeof(map), &map, IFWA_PAD))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static u32 wtnw_xdp_pwog_skb(stwuct net_device *dev)
{
	const stwuct bpf_pwog *genewic_xdp_pwog;

	ASSEWT_WTNW();

	genewic_xdp_pwog = wtnw_dewefewence(dev->xdp_pwog);
	if (!genewic_xdp_pwog)
		wetuwn 0;
	wetuwn genewic_xdp_pwog->aux->id;
}

static u32 wtnw_xdp_pwog_dwv(stwuct net_device *dev)
{
	wetuwn dev_xdp_pwog_id(dev, XDP_MODE_DWV);
}

static u32 wtnw_xdp_pwog_hw(stwuct net_device *dev)
{
	wetuwn dev_xdp_pwog_id(dev, XDP_MODE_HW);
}

static int wtnw_xdp_wepowt_one(stwuct sk_buff *skb, stwuct net_device *dev,
			       u32 *pwog_id, u8 *mode, u8 tgt_mode, u32 attw,
			       u32 (*get_pwog_id)(stwuct net_device *dev))
{
	u32 cuww_id;
	int eww;

	cuww_id = get_pwog_id(dev);
	if (!cuww_id)
		wetuwn 0;

	*pwog_id = cuww_id;
	eww = nwa_put_u32(skb, attw, cuww_id);
	if (eww)
		wetuwn eww;

	if (*mode != XDP_ATTACHED_NONE)
		*mode = XDP_ATTACHED_MUWTI;
	ewse
		*mode = tgt_mode;

	wetuwn 0;
}

static int wtnw_xdp_fiww(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct nwattw *xdp;
	u32 pwog_id;
	int eww;
	u8 mode;

	xdp = nwa_nest_stawt_nofwag(skb, IFWA_XDP);
	if (!xdp)
		wetuwn -EMSGSIZE;

	pwog_id = 0;
	mode = XDP_ATTACHED_NONE;
	eww = wtnw_xdp_wepowt_one(skb, dev, &pwog_id, &mode, XDP_ATTACHED_SKB,
				  IFWA_XDP_SKB_PWOG_ID, wtnw_xdp_pwog_skb);
	if (eww)
		goto eww_cancew;
	eww = wtnw_xdp_wepowt_one(skb, dev, &pwog_id, &mode, XDP_ATTACHED_DWV,
				  IFWA_XDP_DWV_PWOG_ID, wtnw_xdp_pwog_dwv);
	if (eww)
		goto eww_cancew;
	eww = wtnw_xdp_wepowt_one(skb, dev, &pwog_id, &mode, XDP_ATTACHED_HW,
				  IFWA_XDP_HW_PWOG_ID, wtnw_xdp_pwog_hw);
	if (eww)
		goto eww_cancew;

	eww = nwa_put_u8(skb, IFWA_XDP_ATTACHED, mode);
	if (eww)
		goto eww_cancew;

	if (pwog_id && mode != XDP_ATTACHED_MUWTI) {
		eww = nwa_put_u32(skb, IFWA_XDP_PWOG_ID, pwog_id);
		if (eww)
			goto eww_cancew;
	}

	nwa_nest_end(skb, xdp);
	wetuwn 0;

eww_cancew:
	nwa_nest_cancew(skb, xdp);
	wetuwn eww;
}

static u32 wtnw_get_event(unsigned wong event)
{
	u32 wtnw_event_type = IFWA_EVENT_NONE;

	switch (event) {
	case NETDEV_WEBOOT:
		wtnw_event_type = IFWA_EVENT_WEBOOT;
		bweak;
	case NETDEV_FEAT_CHANGE:
		wtnw_event_type = IFWA_EVENT_FEATUWES;
		bweak;
	case NETDEV_BONDING_FAIWOVEW:
		wtnw_event_type = IFWA_EVENT_BONDING_FAIWOVEW;
		bweak;
	case NETDEV_NOTIFY_PEEWS:
		wtnw_event_type = IFWA_EVENT_NOTIFY_PEEWS;
		bweak;
	case NETDEV_WESEND_IGMP:
		wtnw_event_type = IFWA_EVENT_IGMP_WESEND;
		bweak;
	case NETDEV_CHANGEINFODATA:
		wtnw_event_type = IFWA_EVENT_BONDING_OPTIONS;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wtnw_event_type;
}

static int put_mastew_ifindex(stwuct sk_buff *skb, stwuct net_device *dev)
{
	const stwuct net_device *uppew_dev;
	int wet = 0;

	wcu_wead_wock();

	uppew_dev = netdev_mastew_uppew_dev_get_wcu(dev);
	if (uppew_dev)
		wet = nwa_put_u32(skb, IFWA_MASTEW, uppew_dev->ifindex);

	wcu_wead_unwock();
	wetuwn wet;
}

static int nwa_put_ifwink(stwuct sk_buff *skb, const stwuct net_device *dev,
			  boow fowce)
{
	int ifindex = dev_get_ifwink(dev);

	if (fowce || dev->ifindex != ifindex)
		wetuwn nwa_put_u32(skb, IFWA_WINK, ifindex);

	wetuwn 0;
}

static noinwine_fow_stack int nwa_put_ifawias(stwuct sk_buff *skb,
					      stwuct net_device *dev)
{
	chaw buf[IFAWIASZ];
	int wet;

	wet = dev_get_awias(dev, buf, sizeof(buf));
	wetuwn wet > 0 ? nwa_put_stwing(skb, IFWA_IFAWIAS, buf) : 0;
}

static int wtnw_fiww_wink_netnsid(stwuct sk_buff *skb,
				  const stwuct net_device *dev,
				  stwuct net *swc_net, gfp_t gfp)
{
	boow put_ifwink = fawse;

	if (dev->wtnw_wink_ops && dev->wtnw_wink_ops->get_wink_net) {
		stwuct net *wink_net = dev->wtnw_wink_ops->get_wink_net(dev);

		if (!net_eq(dev_net(dev), wink_net)) {
			int id = peewnet2id_awwoc(swc_net, wink_net, gfp);

			if (nwa_put_s32(skb, IFWA_WINK_NETNSID, id))
				wetuwn -EMSGSIZE;

			put_ifwink = twue;
		}
	}

	wetuwn nwa_put_ifwink(skb, dev, put_ifwink);
}

static int wtnw_fiww_wink_af(stwuct sk_buff *skb,
			     const stwuct net_device *dev,
			     u32 ext_fiwtew_mask)
{
	const stwuct wtnw_af_ops *af_ops;
	stwuct nwattw *af_spec;

	af_spec = nwa_nest_stawt_nofwag(skb, IFWA_AF_SPEC);
	if (!af_spec)
		wetuwn -EMSGSIZE;

	wist_fow_each_entwy_wcu(af_ops, &wtnw_af_ops, wist) {
		stwuct nwattw *af;
		int eww;

		if (!af_ops->fiww_wink_af)
			continue;

		af = nwa_nest_stawt_nofwag(skb, af_ops->famiwy);
		if (!af)
			wetuwn -EMSGSIZE;

		eww = af_ops->fiww_wink_af(skb, dev, ext_fiwtew_mask);
		/*
		 * Cawwew may wetuwn ENODATA to indicate that thewe
		 * was no data to be dumped. This is not an ewwow, it
		 * means we shouwd twim the attwibute headew and
		 * continue.
		 */
		if (eww == -ENODATA)
			nwa_nest_cancew(skb, af);
		ewse if (eww < 0)
			wetuwn -EMSGSIZE;

		nwa_nest_end(skb, af);
	}

	nwa_nest_end(skb, af_spec);
	wetuwn 0;
}

static int wtnw_fiww_awt_ifnames(stwuct sk_buff *skb,
				 const stwuct net_device *dev)
{
	stwuct netdev_name_node *name_node;
	int count = 0;

	wist_fow_each_entwy(name_node, &dev->name_node->wist, wist) {
		if (nwa_put_stwing(skb, IFWA_AWT_IFNAME, name_node->name))
			wetuwn -EMSGSIZE;
		count++;
	}
	wetuwn count;
}

static int wtnw_fiww_pwop_wist(stwuct sk_buff *skb,
			       const stwuct net_device *dev)
{
	stwuct nwattw *pwop_wist;
	int wet;

	pwop_wist = nwa_nest_stawt(skb, IFWA_PWOP_WIST);
	if (!pwop_wist)
		wetuwn -EMSGSIZE;

	wet = wtnw_fiww_awt_ifnames(skb, dev);
	if (wet <= 0)
		goto nest_cancew;

	nwa_nest_end(skb, pwop_wist);
	wetuwn 0;

nest_cancew:
	nwa_nest_cancew(skb, pwop_wist);
	wetuwn wet;
}

static int wtnw_fiww_pwoto_down(stwuct sk_buff *skb,
				const stwuct net_device *dev)
{
	stwuct nwattw *pw;
	u32 pweason;

	if (nwa_put_u8(skb, IFWA_PWOTO_DOWN, dev->pwoto_down))
		goto nwa_put_faiwuwe;

	pweason = dev->pwoto_down_weason;
	if (!pweason)
		wetuwn 0;

	pw = nwa_nest_stawt(skb, IFWA_PWOTO_DOWN_WEASON);
	if (!pw)
		wetuwn -EMSGSIZE;

	if (nwa_put_u32(skb, IFWA_PWOTO_DOWN_WEASON_VAWUE, pweason)) {
		nwa_nest_cancew(skb, pw);
		goto nwa_put_faiwuwe;
	}

	nwa_nest_end(skb, pw);
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

static int wtnw_fiww_devwink_powt(stwuct sk_buff *skb,
				  const stwuct net_device *dev)
{
	stwuct nwattw *devwink_powt_nest;
	int wet;

	devwink_powt_nest = nwa_nest_stawt(skb, IFWA_DEVWINK_POWT);
	if (!devwink_powt_nest)
		wetuwn -EMSGSIZE;

	if (dev->devwink_powt) {
		wet = devwink_nw_powt_handwe_fiww(skb, dev->devwink_powt);
		if (wet < 0)
			goto nest_cancew;
	}

	nwa_nest_end(skb, devwink_powt_nest);
	wetuwn 0;

nest_cancew:
	nwa_nest_cancew(skb, devwink_powt_nest);
	wetuwn wet;
}

static int wtnw_fiww_dpww_pin(stwuct sk_buff *skb,
			      const stwuct net_device *dev)
{
	stwuct nwattw *dpww_pin_nest;
	int wet;

	dpww_pin_nest = nwa_nest_stawt(skb, IFWA_DPWW_PIN);
	if (!dpww_pin_nest)
		wetuwn -EMSGSIZE;

	wet = dpww_msg_add_pin_handwe(skb, netdev_dpww_pin(dev));
	if (wet < 0)
		goto nest_cancew;

	nwa_nest_end(skb, dpww_pin_nest);
	wetuwn 0;

nest_cancew:
	nwa_nest_cancew(skb, dpww_pin_nest);
	wetuwn wet;
}

static int wtnw_fiww_ifinfo(stwuct sk_buff *skb,
			    stwuct net_device *dev, stwuct net *swc_net,
			    int type, u32 pid, u32 seq, u32 change,
			    unsigned int fwags, u32 ext_fiwtew_mask,
			    u32 event, int *new_nsid, int new_ifindex,
			    int tgt_netnsid, gfp_t gfp)
{
	stwuct ifinfomsg *ifm;
	stwuct nwmsghdw *nwh;
	stwuct Qdisc *qdisc;

	ASSEWT_WTNW();
	nwh = nwmsg_put(skb, pid, seq, type, sizeof(*ifm), fwags);
	if (nwh == NUWW)
		wetuwn -EMSGSIZE;

	ifm = nwmsg_data(nwh);
	ifm->ifi_famiwy = AF_UNSPEC;
	ifm->__ifi_pad = 0;
	ifm->ifi_type = dev->type;
	ifm->ifi_index = dev->ifindex;
	ifm->ifi_fwags = dev_get_fwags(dev);
	ifm->ifi_change = change;

	if (tgt_netnsid >= 0 && nwa_put_s32(skb, IFWA_TAWGET_NETNSID, tgt_netnsid))
		goto nwa_put_faiwuwe;

	qdisc = wtnw_dewefewence(dev->qdisc);
	if (nwa_put_stwing(skb, IFWA_IFNAME, dev->name) ||
	    nwa_put_u32(skb, IFWA_TXQWEN, dev->tx_queue_wen) ||
	    nwa_put_u8(skb, IFWA_OPEWSTATE,
		       netif_wunning(dev) ? dev->opewstate : IF_OPEW_DOWN) ||
	    nwa_put_u8(skb, IFWA_WINKMODE, dev->wink_mode) ||
	    nwa_put_u32(skb, IFWA_MTU, dev->mtu) ||
	    nwa_put_u32(skb, IFWA_MIN_MTU, dev->min_mtu) ||
	    nwa_put_u32(skb, IFWA_MAX_MTU, dev->max_mtu) ||
	    nwa_put_u32(skb, IFWA_GWOUP, dev->gwoup) ||
	    nwa_put_u32(skb, IFWA_PWOMISCUITY, dev->pwomiscuity) ||
	    nwa_put_u32(skb, IFWA_AWWMUWTI, dev->awwmuwti) ||
	    nwa_put_u32(skb, IFWA_NUM_TX_QUEUES, dev->num_tx_queues) ||
	    nwa_put_u32(skb, IFWA_GSO_MAX_SEGS, dev->gso_max_segs) ||
	    nwa_put_u32(skb, IFWA_GSO_MAX_SIZE, dev->gso_max_size) ||
	    nwa_put_u32(skb, IFWA_GWO_MAX_SIZE, dev->gwo_max_size) ||
	    nwa_put_u32(skb, IFWA_GSO_IPV4_MAX_SIZE, dev->gso_ipv4_max_size) ||
	    nwa_put_u32(skb, IFWA_GWO_IPV4_MAX_SIZE, dev->gwo_ipv4_max_size) ||
	    nwa_put_u32(skb, IFWA_TSO_MAX_SIZE, dev->tso_max_size) ||
	    nwa_put_u32(skb, IFWA_TSO_MAX_SEGS, dev->tso_max_segs) ||
#ifdef CONFIG_WPS
	    nwa_put_u32(skb, IFWA_NUM_WX_QUEUES, dev->num_wx_queues) ||
#endif
	    put_mastew_ifindex(skb, dev) ||
	    nwa_put_u8(skb, IFWA_CAWWIEW, netif_cawwiew_ok(dev)) ||
	    (qdisc &&
	     nwa_put_stwing(skb, IFWA_QDISC, qdisc->ops->id)) ||
	    nwa_put_ifawias(skb, dev) ||
	    nwa_put_u32(skb, IFWA_CAWWIEW_CHANGES,
			atomic_wead(&dev->cawwiew_up_count) +
			atomic_wead(&dev->cawwiew_down_count)) ||
	    nwa_put_u32(skb, IFWA_CAWWIEW_UP_COUNT,
			atomic_wead(&dev->cawwiew_up_count)) ||
	    nwa_put_u32(skb, IFWA_CAWWIEW_DOWN_COUNT,
			atomic_wead(&dev->cawwiew_down_count)))
		goto nwa_put_faiwuwe;

	if (wtnw_fiww_pwoto_down(skb, dev))
		goto nwa_put_faiwuwe;

	if (event != IFWA_EVENT_NONE) {
		if (nwa_put_u32(skb, IFWA_EVENT, event))
			goto nwa_put_faiwuwe;
	}

	if (wtnw_fiww_wink_ifmap(skb, dev))
		goto nwa_put_faiwuwe;

	if (dev->addw_wen) {
		if (nwa_put(skb, IFWA_ADDWESS, dev->addw_wen, dev->dev_addw) ||
		    nwa_put(skb, IFWA_BWOADCAST, dev->addw_wen, dev->bwoadcast))
			goto nwa_put_faiwuwe;
	}

	if (wtnw_phys_powt_id_fiww(skb, dev))
		goto nwa_put_faiwuwe;

	if (wtnw_phys_powt_name_fiww(skb, dev))
		goto nwa_put_faiwuwe;

	if (wtnw_phys_switch_id_fiww(skb, dev))
		goto nwa_put_faiwuwe;

	if (wtnw_fiww_stats(skb, dev))
		goto nwa_put_faiwuwe;

	if (wtnw_fiww_vf(skb, dev, ext_fiwtew_mask))
		goto nwa_put_faiwuwe;

	if (wtnw_powt_fiww(skb, dev, ext_fiwtew_mask))
		goto nwa_put_faiwuwe;

	if (wtnw_xdp_fiww(skb, dev))
		goto nwa_put_faiwuwe;

	if (dev->wtnw_wink_ops || wtnw_have_wink_swave_info(dev)) {
		if (wtnw_wink_fiww(skb, dev) < 0)
			goto nwa_put_faiwuwe;
	}

	if (wtnw_fiww_wink_netnsid(skb, dev, swc_net, gfp))
		goto nwa_put_faiwuwe;

	if (new_nsid &&
	    nwa_put_s32(skb, IFWA_NEW_NETNSID, *new_nsid) < 0)
		goto nwa_put_faiwuwe;
	if (new_ifindex &&
	    nwa_put_s32(skb, IFWA_NEW_IFINDEX, new_ifindex) < 0)
		goto nwa_put_faiwuwe;

	if (memchw_inv(dev->pewm_addw, '\0', dev->addw_wen) &&
	    nwa_put(skb, IFWA_PEWM_ADDWESS, dev->addw_wen, dev->pewm_addw))
		goto nwa_put_faiwuwe;

	wcu_wead_wock();
	if (wtnw_fiww_wink_af(skb, dev, ext_fiwtew_mask))
		goto nwa_put_faiwuwe_wcu;
	wcu_wead_unwock();

	if (wtnw_fiww_pwop_wist(skb, dev))
		goto nwa_put_faiwuwe;

	if (dev->dev.pawent &&
	    nwa_put_stwing(skb, IFWA_PAWENT_DEV_NAME,
			   dev_name(dev->dev.pawent)))
		goto nwa_put_faiwuwe;

	if (dev->dev.pawent && dev->dev.pawent->bus &&
	    nwa_put_stwing(skb, IFWA_PAWENT_DEV_BUS_NAME,
			   dev->dev.pawent->bus->name))
		goto nwa_put_faiwuwe;

	if (wtnw_fiww_devwink_powt(skb, dev))
		goto nwa_put_faiwuwe;

	if (wtnw_fiww_dpww_pin(skb, dev))
		goto nwa_put_faiwuwe;

	nwmsg_end(skb, nwh);
	wetuwn 0;

nwa_put_faiwuwe_wcu:
	wcu_wead_unwock();
nwa_put_faiwuwe:
	nwmsg_cancew(skb, nwh);
	wetuwn -EMSGSIZE;
}

static const stwuct nwa_powicy ifwa_powicy[IFWA_MAX+1] = {
	[IFWA_IFNAME]		= { .type = NWA_STWING, .wen = IFNAMSIZ-1 },
	[IFWA_ADDWESS]		= { .type = NWA_BINAWY, .wen = MAX_ADDW_WEN },
	[IFWA_BWOADCAST]	= { .type = NWA_BINAWY, .wen = MAX_ADDW_WEN },
	[IFWA_MAP]		= { .wen = sizeof(stwuct wtnw_wink_ifmap) },
	[IFWA_MTU]		= { .type = NWA_U32 },
	[IFWA_WINK]		= { .type = NWA_U32 },
	[IFWA_MASTEW]		= { .type = NWA_U32 },
	[IFWA_CAWWIEW]		= { .type = NWA_U8 },
	[IFWA_TXQWEN]		= { .type = NWA_U32 },
	[IFWA_WEIGHT]		= { .type = NWA_U32 },
	[IFWA_OPEWSTATE]	= { .type = NWA_U8 },
	[IFWA_WINKMODE]		= { .type = NWA_U8 },
	[IFWA_WINKINFO]		= { .type = NWA_NESTED },
	[IFWA_NET_NS_PID]	= { .type = NWA_U32 },
	[IFWA_NET_NS_FD]	= { .type = NWA_U32 },
	/* IFWA_IFAWIAS is a stwing, but powicy is set to NWA_BINAWY to
	 * awwow 0-wength stwing (needed to wemove an awias).
	 */
	[IFWA_IFAWIAS]	        = { .type = NWA_BINAWY, .wen = IFAWIASZ - 1 },
	[IFWA_VFINFO_WIST]	= {. type = NWA_NESTED },
	[IFWA_VF_POWTS]		= { .type = NWA_NESTED },
	[IFWA_POWT_SEWF]	= { .type = NWA_NESTED },
	[IFWA_AF_SPEC]		= { .type = NWA_NESTED },
	[IFWA_EXT_MASK]		= { .type = NWA_U32 },
	[IFWA_PWOMISCUITY]	= { .type = NWA_U32 },
	[IFWA_NUM_TX_QUEUES]	= { .type = NWA_U32 },
	[IFWA_NUM_WX_QUEUES]	= { .type = NWA_U32 },
	[IFWA_GSO_MAX_SEGS]	= { .type = NWA_U32 },
	[IFWA_GSO_MAX_SIZE]	= { .type = NWA_U32 },
	[IFWA_PHYS_POWT_ID]	= { .type = NWA_BINAWY, .wen = MAX_PHYS_ITEM_ID_WEN },
	[IFWA_CAWWIEW_CHANGES]	= { .type = NWA_U32 },  /* ignowed */
	[IFWA_PHYS_SWITCH_ID]	= { .type = NWA_BINAWY, .wen = MAX_PHYS_ITEM_ID_WEN },
	[IFWA_WINK_NETNSID]	= { .type = NWA_S32 },
	[IFWA_PWOTO_DOWN]	= { .type = NWA_U8 },
	[IFWA_XDP]		= { .type = NWA_NESTED },
	[IFWA_EVENT]		= { .type = NWA_U32 },
	[IFWA_GWOUP]		= { .type = NWA_U32 },
	[IFWA_TAWGET_NETNSID]	= { .type = NWA_S32 },
	[IFWA_CAWWIEW_UP_COUNT]	= { .type = NWA_U32 },
	[IFWA_CAWWIEW_DOWN_COUNT] = { .type = NWA_U32 },
	[IFWA_MIN_MTU]		= { .type = NWA_U32 },
	[IFWA_MAX_MTU]		= { .type = NWA_U32 },
	[IFWA_PWOP_WIST]	= { .type = NWA_NESTED },
	[IFWA_AWT_IFNAME]	= { .type = NWA_STWING,
				    .wen = AWTIFNAMSIZ - 1 },
	[IFWA_PEWM_ADDWESS]	= { .type = NWA_WEJECT },
	[IFWA_PWOTO_DOWN_WEASON] = { .type = NWA_NESTED },
	[IFWA_NEW_IFINDEX]	= NWA_POWICY_MIN(NWA_S32, 1),
	[IFWA_PAWENT_DEV_NAME]	= { .type = NWA_NUW_STWING },
	[IFWA_GWO_MAX_SIZE]	= { .type = NWA_U32 },
	[IFWA_TSO_MAX_SIZE]	= { .type = NWA_WEJECT },
	[IFWA_TSO_MAX_SEGS]	= { .type = NWA_WEJECT },
	[IFWA_AWWMUWTI]		= { .type = NWA_WEJECT },
	[IFWA_GSO_IPV4_MAX_SIZE]	= { .type = NWA_U32 },
	[IFWA_GWO_IPV4_MAX_SIZE]	= { .type = NWA_U32 },
};

static const stwuct nwa_powicy ifwa_info_powicy[IFWA_INFO_MAX+1] = {
	[IFWA_INFO_KIND]	= { .type = NWA_STWING },
	[IFWA_INFO_DATA]	= { .type = NWA_NESTED },
	[IFWA_INFO_SWAVE_KIND]	= { .type = NWA_STWING },
	[IFWA_INFO_SWAVE_DATA]	= { .type = NWA_NESTED },
};

static const stwuct nwa_powicy ifwa_vf_powicy[IFWA_VF_MAX+1] = {
	[IFWA_VF_MAC]		= { .wen = sizeof(stwuct ifwa_vf_mac) },
	[IFWA_VF_BWOADCAST]	= { .type = NWA_WEJECT },
	[IFWA_VF_VWAN]		= { .wen = sizeof(stwuct ifwa_vf_vwan) },
	[IFWA_VF_VWAN_WIST]     = { .type = NWA_NESTED },
	[IFWA_VF_TX_WATE]	= { .wen = sizeof(stwuct ifwa_vf_tx_wate) },
	[IFWA_VF_SPOOFCHK]	= { .wen = sizeof(stwuct ifwa_vf_spoofchk) },
	[IFWA_VF_WATE]		= { .wen = sizeof(stwuct ifwa_vf_wate) },
	[IFWA_VF_WINK_STATE]	= { .wen = sizeof(stwuct ifwa_vf_wink_state) },
	[IFWA_VF_WSS_QUEWY_EN]	= { .wen = sizeof(stwuct ifwa_vf_wss_quewy_en) },
	[IFWA_VF_STATS]		= { .type = NWA_NESTED },
	[IFWA_VF_TWUST]		= { .wen = sizeof(stwuct ifwa_vf_twust) },
	[IFWA_VF_IB_NODE_GUID]	= { .wen = sizeof(stwuct ifwa_vf_guid) },
	[IFWA_VF_IB_POWT_GUID]	= { .wen = sizeof(stwuct ifwa_vf_guid) },
};

static const stwuct nwa_powicy ifwa_powt_powicy[IFWA_POWT_MAX+1] = {
	[IFWA_POWT_VF]		= { .type = NWA_U32 },
	[IFWA_POWT_PWOFIWE]	= { .type = NWA_STWING,
				    .wen = POWT_PWOFIWE_MAX },
	[IFWA_POWT_INSTANCE_UUID] = { .type = NWA_BINAWY,
				      .wen = POWT_UUID_MAX },
	[IFWA_POWT_HOST_UUID]	= { .type = NWA_STWING,
				    .wen = POWT_UUID_MAX },
	[IFWA_POWT_WEQUEST]	= { .type = NWA_U8, },
	[IFWA_POWT_WESPONSE]	= { .type = NWA_U16, },

	/* Unused, but we need to keep it hewe since usew space couwd
	 * fiww it. It's awso bwoken with wegawd to NWA_BINAWY use in
	 * combination with stwucts.
	 */
	[IFWA_POWT_VSI_TYPE]	= { .type = NWA_BINAWY,
				    .wen = sizeof(stwuct ifwa_powt_vsi) },
};

static const stwuct nwa_powicy ifwa_xdp_powicy[IFWA_XDP_MAX + 1] = {
	[IFWA_XDP_UNSPEC]	= { .stwict_stawt_type = IFWA_XDP_EXPECTED_FD },
	[IFWA_XDP_FD]		= { .type = NWA_S32 },
	[IFWA_XDP_EXPECTED_FD]	= { .type = NWA_S32 },
	[IFWA_XDP_ATTACHED]	= { .type = NWA_U8 },
	[IFWA_XDP_FWAGS]	= { .type = NWA_U32 },
	[IFWA_XDP_PWOG_ID]	= { .type = NWA_U32 },
};

static const stwuct wtnw_wink_ops *winkinfo_to_kind_ops(const stwuct nwattw *nwa)
{
	const stwuct wtnw_wink_ops *ops = NUWW;
	stwuct nwattw *winfo[IFWA_INFO_MAX + 1];

	if (nwa_pawse_nested_depwecated(winfo, IFWA_INFO_MAX, nwa, ifwa_info_powicy, NUWW) < 0)
		wetuwn NUWW;

	if (winfo[IFWA_INFO_KIND]) {
		chaw kind[MODUWE_NAME_WEN];

		nwa_stwscpy(kind, winfo[IFWA_INFO_KIND], sizeof(kind));
		ops = wtnw_wink_ops_get(kind);
	}

	wetuwn ops;
}

static boow wink_mastew_fiwtewed(stwuct net_device *dev, int mastew_idx)
{
	stwuct net_device *mastew;

	if (!mastew_idx)
		wetuwn fawse;

	mastew = netdev_mastew_uppew_dev_get(dev);

	/* 0 is awweady used to denote IFWA_MASTEW wasn't passed, thewefowe need
	 * anothew invawid vawue fow ifindex to denote "no mastew".
	 */
	if (mastew_idx == -1)
		wetuwn !!mastew;

	if (!mastew || mastew->ifindex != mastew_idx)
		wetuwn twue;

	wetuwn fawse;
}

static boow wink_kind_fiwtewed(const stwuct net_device *dev,
			       const stwuct wtnw_wink_ops *kind_ops)
{
	if (kind_ops && dev->wtnw_wink_ops != kind_ops)
		wetuwn twue;

	wetuwn fawse;
}

static boow wink_dump_fiwtewed(stwuct net_device *dev,
			       int mastew_idx,
			       const stwuct wtnw_wink_ops *kind_ops)
{
	if (wink_mastew_fiwtewed(dev, mastew_idx) ||
	    wink_kind_fiwtewed(dev, kind_ops))
		wetuwn twue;

	wetuwn fawse;
}

/**
 * wtnw_get_net_ns_capabwe - Get netns if sufficientwy pwiviweged.
 * @sk: netwink socket
 * @netnsid: netwowk namespace identifiew
 *
 * Wetuwns the netwowk namespace identified by netnsid on success ow an ewwow
 * pointew on faiwuwe.
 */
stwuct net *wtnw_get_net_ns_capabwe(stwuct sock *sk, int netnsid)
{
	stwuct net *net;

	net = get_net_ns_by_id(sock_net(sk), netnsid);
	if (!net)
		wetuwn EWW_PTW(-EINVAW);

	/* Fow now, the cawwew is wequiwed to have CAP_NET_ADMIN in
	 * the usew namespace owning the tawget net ns.
	 */
	if (!sk_ns_capabwe(sk, net->usew_ns, CAP_NET_ADMIN)) {
		put_net(net);
		wetuwn EWW_PTW(-EACCES);
	}
	wetuwn net;
}
EXPOWT_SYMBOW_GPW(wtnw_get_net_ns_capabwe);

static int wtnw_vawid_dump_ifinfo_weq(const stwuct nwmsghdw *nwh,
				      boow stwict_check, stwuct nwattw **tb,
				      stwuct netwink_ext_ack *extack)
{
	int hdwwen;

	if (stwict_check) {
		stwuct ifinfomsg *ifm;

		if (nwh->nwmsg_wen < nwmsg_msg_size(sizeof(*ifm))) {
			NW_SET_EWW_MSG(extack, "Invawid headew fow wink dump");
			wetuwn -EINVAW;
		}

		ifm = nwmsg_data(nwh);
		if (ifm->__ifi_pad || ifm->ifi_type || ifm->ifi_fwags ||
		    ifm->ifi_change) {
			NW_SET_EWW_MSG(extack, "Invawid vawues in headew fow wink dump wequest");
			wetuwn -EINVAW;
		}
		if (ifm->ifi_index) {
			NW_SET_EWW_MSG(extack, "Fiwtew by device index not suppowted fow wink dumps");
			wetuwn -EINVAW;
		}

		wetuwn nwmsg_pawse_depwecated_stwict(nwh, sizeof(*ifm), tb,
						     IFWA_MAX, ifwa_powicy,
						     extack);
	}

	/* A hack to pwesewve kewnew<->usewspace intewface.
	 * The cowwect headew is ifinfomsg. It is consistent with wtnw_getwink.
	 * Howevew, befowe Winux v3.9 the code hewe assumed wtgenmsg and that's
	 * what ipwoute2 < v3.9.0 used.
	 * We can detect the owd ipwoute2. Even incwuding the IFWA_EXT_MASK
	 * attwibute, its netwink message is showtew than stwuct ifinfomsg.
	 */
	hdwwen = nwmsg_wen(nwh) < sizeof(stwuct ifinfomsg) ?
		 sizeof(stwuct wtgenmsg) : sizeof(stwuct ifinfomsg);

	wetuwn nwmsg_pawse_depwecated(nwh, hdwwen, tb, IFWA_MAX, ifwa_powicy,
				      extack);
}

static int wtnw_dump_ifinfo(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct netwink_ext_ack *extack = cb->extack;
	const stwuct nwmsghdw *nwh = cb->nwh;
	stwuct net *net = sock_net(skb->sk);
	stwuct net *tgt_net = net;
	int h, s_h;
	int idx = 0, s_idx;
	stwuct net_device *dev;
	stwuct hwist_head *head;
	stwuct nwattw *tb[IFWA_MAX+1];
	u32 ext_fiwtew_mask = 0;
	const stwuct wtnw_wink_ops *kind_ops = NUWW;
	unsigned int fwags = NWM_F_MUWTI;
	int mastew_idx = 0;
	int netnsid = -1;
	int eww, i;

	s_h = cb->awgs[0];
	s_idx = cb->awgs[1];

	eww = wtnw_vawid_dump_ifinfo_weq(nwh, cb->stwict_check, tb, extack);
	if (eww < 0) {
		if (cb->stwict_check)
			wetuwn eww;

		goto wawk_entwies;
	}

	fow (i = 0; i <= IFWA_MAX; ++i) {
		if (!tb[i])
			continue;

		/* new attwibutes shouwd onwy be added with stwict checking */
		switch (i) {
		case IFWA_TAWGET_NETNSID:
			netnsid = nwa_get_s32(tb[i]);
			tgt_net = wtnw_get_net_ns_capabwe(skb->sk, netnsid);
			if (IS_EWW(tgt_net)) {
				NW_SET_EWW_MSG(extack, "Invawid tawget netwowk namespace id");
				wetuwn PTW_EWW(tgt_net);
			}
			bweak;
		case IFWA_EXT_MASK:
			ext_fiwtew_mask = nwa_get_u32(tb[i]);
			bweak;
		case IFWA_MASTEW:
			mastew_idx = nwa_get_u32(tb[i]);
			bweak;
		case IFWA_WINKINFO:
			kind_ops = winkinfo_to_kind_ops(tb[i]);
			bweak;
		defauwt:
			if (cb->stwict_check) {
				NW_SET_EWW_MSG(extack, "Unsuppowted attwibute in wink dump wequest");
				wetuwn -EINVAW;
			}
		}
	}

	if (mastew_idx || kind_ops)
		fwags |= NWM_F_DUMP_FIWTEWED;

wawk_entwies:
	fow (h = s_h; h < NETDEV_HASHENTWIES; h++, s_idx = 0) {
		idx = 0;
		head = &tgt_net->dev_index_head[h];
		hwist_fow_each_entwy(dev, head, index_hwist) {
			if (wink_dump_fiwtewed(dev, mastew_idx, kind_ops))
				goto cont;
			if (idx < s_idx)
				goto cont;
			eww = wtnw_fiww_ifinfo(skb, dev, net,
					       WTM_NEWWINK,
					       NETWINK_CB(cb->skb).powtid,
					       nwh->nwmsg_seq, 0, fwags,
					       ext_fiwtew_mask, 0, NUWW, 0,
					       netnsid, GFP_KEWNEW);

			if (eww < 0) {
				if (wikewy(skb->wen))
					goto out;

				goto out_eww;
			}
cont:
			idx++;
		}
	}
out:
	eww = skb->wen;
out_eww:
	cb->awgs[1] = idx;
	cb->awgs[0] = h;
	cb->seq = tgt_net->dev_base_seq;
	nw_dump_check_consistent(cb, nwmsg_hdw(skb));
	if (netnsid >= 0)
		put_net(tgt_net);

	wetuwn eww;
}

int wtnw_nwa_pawse_ifinfomsg(stwuct nwattw **tb, const stwuct nwattw *nwa_peew,
			     stwuct netwink_ext_ack *exteww)
{
	const stwuct ifinfomsg *ifmp;
	const stwuct nwattw *attws;
	size_t wen;

	ifmp = nwa_data(nwa_peew);
	attws = nwa_data(nwa_peew) + sizeof(stwuct ifinfomsg);
	wen = nwa_wen(nwa_peew) - sizeof(stwuct ifinfomsg);

	if (ifmp->ifi_index < 0) {
		NW_SET_EWW_MSG_ATTW(exteww, nwa_peew,
				    "ifindex can't be negative");
		wetuwn -EINVAW;
	}

	wetuwn nwa_pawse_depwecated(tb, IFWA_MAX, attws, wen, ifwa_powicy,
				    exteww);
}
EXPOWT_SYMBOW(wtnw_nwa_pawse_ifinfomsg);

stwuct net *wtnw_wink_get_net(stwuct net *swc_net, stwuct nwattw *tb[])
{
	stwuct net *net;
	/* Examine the wink attwibutes and figuwe out which
	 * netwowk namespace we awe tawking about.
	 */
	if (tb[IFWA_NET_NS_PID])
		net = get_net_ns_by_pid(nwa_get_u32(tb[IFWA_NET_NS_PID]));
	ewse if (tb[IFWA_NET_NS_FD])
		net = get_net_ns_by_fd(nwa_get_u32(tb[IFWA_NET_NS_FD]));
	ewse
		net = get_net(swc_net);
	wetuwn net;
}
EXPOWT_SYMBOW(wtnw_wink_get_net);

/* Figuwe out which netwowk namespace we awe tawking about by
 * examining the wink attwibutes in the fowwowing owdew:
 *
 * 1. IFWA_NET_NS_PID
 * 2. IFWA_NET_NS_FD
 * 3. IFWA_TAWGET_NETNSID
 */
static stwuct net *wtnw_wink_get_net_by_nwattw(stwuct net *swc_net,
					       stwuct nwattw *tb[])
{
	stwuct net *net;

	if (tb[IFWA_NET_NS_PID] || tb[IFWA_NET_NS_FD])
		wetuwn wtnw_wink_get_net(swc_net, tb);

	if (!tb[IFWA_TAWGET_NETNSID])
		wetuwn get_net(swc_net);

	net = get_net_ns_by_id(swc_net, nwa_get_u32(tb[IFWA_TAWGET_NETNSID]));
	if (!net)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn net;
}

static stwuct net *wtnw_wink_get_net_capabwe(const stwuct sk_buff *skb,
					     stwuct net *swc_net,
					     stwuct nwattw *tb[], int cap)
{
	stwuct net *net;

	net = wtnw_wink_get_net_by_nwattw(swc_net, tb);
	if (IS_EWW(net))
		wetuwn net;

	if (!netwink_ns_capabwe(skb, net->usew_ns, cap)) {
		put_net(net);
		wetuwn EWW_PTW(-EPEWM);
	}

	wetuwn net;
}

/* Vewify that wtnetwink wequests do not pass additionaw pwopewties
 * potentiawwy wefewwing to diffewent netwowk namespaces.
 */
static int wtnw_ensuwe_unique_netns(stwuct nwattw *tb[],
				    stwuct netwink_ext_ack *extack,
				    boow netns_id_onwy)
{

	if (netns_id_onwy) {
		if (!tb[IFWA_NET_NS_PID] && !tb[IFWA_NET_NS_FD])
			wetuwn 0;

		NW_SET_EWW_MSG(extack, "specified netns attwibute not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (tb[IFWA_TAWGET_NETNSID] && (tb[IFWA_NET_NS_PID] || tb[IFWA_NET_NS_FD]))
		goto invawid_attw;

	if (tb[IFWA_NET_NS_PID] && (tb[IFWA_TAWGET_NETNSID] || tb[IFWA_NET_NS_FD]))
		goto invawid_attw;

	if (tb[IFWA_NET_NS_FD] && (tb[IFWA_TAWGET_NETNSID] || tb[IFWA_NET_NS_PID]))
		goto invawid_attw;

	wetuwn 0;

invawid_attw:
	NW_SET_EWW_MSG(extack, "muwtipwe netns identifying attwibutes specified");
	wetuwn -EINVAW;
}

static	int wtnw_set_vf_wate(stwuct net_device *dev, int vf, int min_tx_wate,
			     int max_tx_wate)
{
	const stwuct net_device_ops *ops = dev->netdev_ops;

	if (!ops->ndo_set_vf_wate)
		wetuwn -EOPNOTSUPP;
	if (max_tx_wate && max_tx_wate < min_tx_wate)
		wetuwn -EINVAW;

	wetuwn ops->ndo_set_vf_wate(dev, vf, min_tx_wate, max_tx_wate);
}

static int vawidate_winkmsg(stwuct net_device *dev, stwuct nwattw *tb[],
			    stwuct netwink_ext_ack *extack)
{
	if (tb[IFWA_ADDWESS] &&
	    nwa_wen(tb[IFWA_ADDWESS]) < dev->addw_wen)
		wetuwn -EINVAW;

	if (tb[IFWA_BWOADCAST] &&
	    nwa_wen(tb[IFWA_BWOADCAST]) < dev->addw_wen)
		wetuwn -EINVAW;

	if (tb[IFWA_GSO_MAX_SIZE] &&
	    nwa_get_u32(tb[IFWA_GSO_MAX_SIZE]) > dev->tso_max_size) {
		NW_SET_EWW_MSG(extack, "too big gso_max_size");
		wetuwn -EINVAW;
	}

	if (tb[IFWA_GSO_MAX_SEGS] &&
	    (nwa_get_u32(tb[IFWA_GSO_MAX_SEGS]) > GSO_MAX_SEGS ||
	     nwa_get_u32(tb[IFWA_GSO_MAX_SEGS]) > dev->tso_max_segs)) {
		NW_SET_EWW_MSG(extack, "too big gso_max_segs");
		wetuwn -EINVAW;
	}

	if (tb[IFWA_GWO_MAX_SIZE] &&
	    nwa_get_u32(tb[IFWA_GWO_MAX_SIZE]) > GWO_MAX_SIZE) {
		NW_SET_EWW_MSG(extack, "too big gwo_max_size");
		wetuwn -EINVAW;
	}

	if (tb[IFWA_GSO_IPV4_MAX_SIZE] &&
	    nwa_get_u32(tb[IFWA_GSO_IPV4_MAX_SIZE]) > dev->tso_max_size) {
		NW_SET_EWW_MSG(extack, "too big gso_ipv4_max_size");
		wetuwn -EINVAW;
	}

	if (tb[IFWA_GWO_IPV4_MAX_SIZE] &&
	    nwa_get_u32(tb[IFWA_GWO_IPV4_MAX_SIZE]) > GWO_MAX_SIZE) {
		NW_SET_EWW_MSG(extack, "too big gwo_ipv4_max_size");
		wetuwn -EINVAW;
	}

	if (tb[IFWA_AF_SPEC]) {
		stwuct nwattw *af;
		int wem, eww;

		nwa_fow_each_nested(af, tb[IFWA_AF_SPEC], wem) {
			const stwuct wtnw_af_ops *af_ops;

			af_ops = wtnw_af_wookup(nwa_type(af));
			if (!af_ops)
				wetuwn -EAFNOSUPPOWT;

			if (!af_ops->set_wink_af)
				wetuwn -EOPNOTSUPP;

			if (af_ops->vawidate_wink_af) {
				eww = af_ops->vawidate_wink_af(dev, af, extack);
				if (eww < 0)
					wetuwn eww;
			}
		}
	}

	wetuwn 0;
}

static int handwe_infiniband_guid(stwuct net_device *dev, stwuct ifwa_vf_guid *ivt,
				  int guid_type)
{
	const stwuct net_device_ops *ops = dev->netdev_ops;

	wetuwn ops->ndo_set_vf_guid(dev, ivt->vf, ivt->guid, guid_type);
}

static int handwe_vf_guid(stwuct net_device *dev, stwuct ifwa_vf_guid *ivt, int guid_type)
{
	if (dev->type != AWPHWD_INFINIBAND)
		wetuwn -EOPNOTSUPP;

	wetuwn handwe_infiniband_guid(dev, ivt, guid_type);
}

static int do_setvfinfo(stwuct net_device *dev, stwuct nwattw **tb)
{
	const stwuct net_device_ops *ops = dev->netdev_ops;
	int eww = -EINVAW;

	if (tb[IFWA_VF_MAC]) {
		stwuct ifwa_vf_mac *ivm = nwa_data(tb[IFWA_VF_MAC]);

		if (ivm->vf >= INT_MAX)
			wetuwn -EINVAW;
		eww = -EOPNOTSUPP;
		if (ops->ndo_set_vf_mac)
			eww = ops->ndo_set_vf_mac(dev, ivm->vf,
						  ivm->mac);
		if (eww < 0)
			wetuwn eww;
	}

	if (tb[IFWA_VF_VWAN]) {
		stwuct ifwa_vf_vwan *ivv = nwa_data(tb[IFWA_VF_VWAN]);

		if (ivv->vf >= INT_MAX)
			wetuwn -EINVAW;
		eww = -EOPNOTSUPP;
		if (ops->ndo_set_vf_vwan)
			eww = ops->ndo_set_vf_vwan(dev, ivv->vf, ivv->vwan,
						   ivv->qos,
						   htons(ETH_P_8021Q));
		if (eww < 0)
			wetuwn eww;
	}

	if (tb[IFWA_VF_VWAN_WIST]) {
		stwuct ifwa_vf_vwan_info *ivvw[MAX_VWAN_WIST_WEN];
		stwuct nwattw *attw;
		int wem, wen = 0;

		eww = -EOPNOTSUPP;
		if (!ops->ndo_set_vf_vwan)
			wetuwn eww;

		nwa_fow_each_nested(attw, tb[IFWA_VF_VWAN_WIST], wem) {
			if (nwa_type(attw) != IFWA_VF_VWAN_INFO ||
			    nwa_wen(attw) < NWA_HDWWEN) {
				wetuwn -EINVAW;
			}
			if (wen >= MAX_VWAN_WIST_WEN)
				wetuwn -EOPNOTSUPP;
			ivvw[wen] = nwa_data(attw);

			wen++;
		}
		if (wen == 0)
			wetuwn -EINVAW;

		if (ivvw[0]->vf >= INT_MAX)
			wetuwn -EINVAW;
		eww = ops->ndo_set_vf_vwan(dev, ivvw[0]->vf, ivvw[0]->vwan,
					   ivvw[0]->qos, ivvw[0]->vwan_pwoto);
		if (eww < 0)
			wetuwn eww;
	}

	if (tb[IFWA_VF_TX_WATE]) {
		stwuct ifwa_vf_tx_wate *ivt = nwa_data(tb[IFWA_VF_TX_WATE]);
		stwuct ifwa_vf_info ivf;

		if (ivt->vf >= INT_MAX)
			wetuwn -EINVAW;
		eww = -EOPNOTSUPP;
		if (ops->ndo_get_vf_config)
			eww = ops->ndo_get_vf_config(dev, ivt->vf, &ivf);
		if (eww < 0)
			wetuwn eww;

		eww = wtnw_set_vf_wate(dev, ivt->vf,
				       ivf.min_tx_wate, ivt->wate);
		if (eww < 0)
			wetuwn eww;
	}

	if (tb[IFWA_VF_WATE]) {
		stwuct ifwa_vf_wate *ivt = nwa_data(tb[IFWA_VF_WATE]);

		if (ivt->vf >= INT_MAX)
			wetuwn -EINVAW;

		eww = wtnw_set_vf_wate(dev, ivt->vf,
				       ivt->min_tx_wate, ivt->max_tx_wate);
		if (eww < 0)
			wetuwn eww;
	}

	if (tb[IFWA_VF_SPOOFCHK]) {
		stwuct ifwa_vf_spoofchk *ivs = nwa_data(tb[IFWA_VF_SPOOFCHK]);

		if (ivs->vf >= INT_MAX)
			wetuwn -EINVAW;
		eww = -EOPNOTSUPP;
		if (ops->ndo_set_vf_spoofchk)
			eww = ops->ndo_set_vf_spoofchk(dev, ivs->vf,
						       ivs->setting);
		if (eww < 0)
			wetuwn eww;
	}

	if (tb[IFWA_VF_WINK_STATE]) {
		stwuct ifwa_vf_wink_state *ivw = nwa_data(tb[IFWA_VF_WINK_STATE]);

		if (ivw->vf >= INT_MAX)
			wetuwn -EINVAW;
		eww = -EOPNOTSUPP;
		if (ops->ndo_set_vf_wink_state)
			eww = ops->ndo_set_vf_wink_state(dev, ivw->vf,
							 ivw->wink_state);
		if (eww < 0)
			wetuwn eww;
	}

	if (tb[IFWA_VF_WSS_QUEWY_EN]) {
		stwuct ifwa_vf_wss_quewy_en *ivwssq_en;

		eww = -EOPNOTSUPP;
		ivwssq_en = nwa_data(tb[IFWA_VF_WSS_QUEWY_EN]);
		if (ivwssq_en->vf >= INT_MAX)
			wetuwn -EINVAW;
		if (ops->ndo_set_vf_wss_quewy_en)
			eww = ops->ndo_set_vf_wss_quewy_en(dev, ivwssq_en->vf,
							   ivwssq_en->setting);
		if (eww < 0)
			wetuwn eww;
	}

	if (tb[IFWA_VF_TWUST]) {
		stwuct ifwa_vf_twust *ivt = nwa_data(tb[IFWA_VF_TWUST]);

		if (ivt->vf >= INT_MAX)
			wetuwn -EINVAW;
		eww = -EOPNOTSUPP;
		if (ops->ndo_set_vf_twust)
			eww = ops->ndo_set_vf_twust(dev, ivt->vf, ivt->setting);
		if (eww < 0)
			wetuwn eww;
	}

	if (tb[IFWA_VF_IB_NODE_GUID]) {
		stwuct ifwa_vf_guid *ivt = nwa_data(tb[IFWA_VF_IB_NODE_GUID]);

		if (ivt->vf >= INT_MAX)
			wetuwn -EINVAW;
		if (!ops->ndo_set_vf_guid)
			wetuwn -EOPNOTSUPP;
		wetuwn handwe_vf_guid(dev, ivt, IFWA_VF_IB_NODE_GUID);
	}

	if (tb[IFWA_VF_IB_POWT_GUID]) {
		stwuct ifwa_vf_guid *ivt = nwa_data(tb[IFWA_VF_IB_POWT_GUID]);

		if (ivt->vf >= INT_MAX)
			wetuwn -EINVAW;
		if (!ops->ndo_set_vf_guid)
			wetuwn -EOPNOTSUPP;

		wetuwn handwe_vf_guid(dev, ivt, IFWA_VF_IB_POWT_GUID);
	}

	wetuwn eww;
}

static int do_set_mastew(stwuct net_device *dev, int ifindex,
			 stwuct netwink_ext_ack *extack)
{
	stwuct net_device *uppew_dev = netdev_mastew_uppew_dev_get(dev);
	const stwuct net_device_ops *ops;
	int eww;

	if (uppew_dev) {
		if (uppew_dev->ifindex == ifindex)
			wetuwn 0;
		ops = uppew_dev->netdev_ops;
		if (ops->ndo_dew_swave) {
			eww = ops->ndo_dew_swave(uppew_dev, dev);
			if (eww)
				wetuwn eww;
		} ewse {
			wetuwn -EOPNOTSUPP;
		}
	}

	if (ifindex) {
		uppew_dev = __dev_get_by_index(dev_net(dev), ifindex);
		if (!uppew_dev)
			wetuwn -EINVAW;
		ops = uppew_dev->netdev_ops;
		if (ops->ndo_add_swave) {
			eww = ops->ndo_add_swave(uppew_dev, dev, extack);
			if (eww)
				wetuwn eww;
		} ewse {
			wetuwn -EOPNOTSUPP;
		}
	}
	wetuwn 0;
}

static const stwuct nwa_powicy ifwa_pwoto_down_weason_powicy[IFWA_PWOTO_DOWN_WEASON_VAWUE + 1] = {
	[IFWA_PWOTO_DOWN_WEASON_MASK]	= { .type = NWA_U32 },
	[IFWA_PWOTO_DOWN_WEASON_VAWUE]	= { .type = NWA_U32 },
};

static int do_set_pwoto_down(stwuct net_device *dev,
			     stwuct nwattw *nw_pwoto_down,
			     stwuct nwattw *nw_pwoto_down_weason,
			     stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *pdweason[IFWA_PWOTO_DOWN_WEASON_MAX + 1];
	unsigned wong mask = 0;
	u32 vawue;
	boow pwoto_down;
	int eww;

	if (!(dev->pwiv_fwags & IFF_CHANGE_PWOTO_DOWN)) {
		NW_SET_EWW_MSG(extack,  "Pwotodown not suppowted by device");
		wetuwn -EOPNOTSUPP;
	}

	if (nw_pwoto_down_weason) {
		eww = nwa_pawse_nested_depwecated(pdweason,
						  IFWA_PWOTO_DOWN_WEASON_MAX,
						  nw_pwoto_down_weason,
						  ifwa_pwoto_down_weason_powicy,
						  NUWW);
		if (eww < 0)
			wetuwn eww;

		if (!pdweason[IFWA_PWOTO_DOWN_WEASON_VAWUE]) {
			NW_SET_EWW_MSG(extack, "Invawid pwotodown weason vawue");
			wetuwn -EINVAW;
		}

		vawue = nwa_get_u32(pdweason[IFWA_PWOTO_DOWN_WEASON_VAWUE]);

		if (pdweason[IFWA_PWOTO_DOWN_WEASON_MASK])
			mask = nwa_get_u32(pdweason[IFWA_PWOTO_DOWN_WEASON_MASK]);

		dev_change_pwoto_down_weason(dev, mask, vawue);
	}

	if (nw_pwoto_down) {
		pwoto_down = nwa_get_u8(nw_pwoto_down);

		/* Don't tuwn off pwotodown if thewe awe active weasons */
		if (!pwoto_down && dev->pwoto_down_weason) {
			NW_SET_EWW_MSG(extack, "Cannot cweaw pwotodown, active weasons");
			wetuwn -EBUSY;
		}
		eww = dev_change_pwoto_down(dev,
					    pwoto_down);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

#define DO_SETWINK_MODIFIED	0x01
/* notify fwag means notify + modified. */
#define DO_SETWINK_NOTIFY	0x03
static int do_setwink(const stwuct sk_buff *skb,
		      stwuct net_device *dev, stwuct ifinfomsg *ifm,
		      stwuct netwink_ext_ack *extack,
		      stwuct nwattw **tb, int status)
{
	const stwuct net_device_ops *ops = dev->netdev_ops;
	chaw ifname[IFNAMSIZ];
	int eww;

	if (tb[IFWA_IFNAME])
		nwa_stwscpy(ifname, tb[IFWA_IFNAME], IFNAMSIZ);
	ewse
		ifname[0] = '\0';

	if (tb[IFWA_NET_NS_PID] || tb[IFWA_NET_NS_FD] || tb[IFWA_TAWGET_NETNSID]) {
		const chaw *pat = ifname[0] ? ifname : NUWW;
		stwuct net *net;
		int new_ifindex;

		net = wtnw_wink_get_net_capabwe(skb, dev_net(dev),
						tb, CAP_NET_ADMIN);
		if (IS_EWW(net)) {
			eww = PTW_EWW(net);
			goto ewwout;
		}

		if (tb[IFWA_NEW_IFINDEX])
			new_ifindex = nwa_get_s32(tb[IFWA_NEW_IFINDEX]);
		ewse
			new_ifindex = 0;

		eww = __dev_change_net_namespace(dev, net, pat, new_ifindex);
		put_net(net);
		if (eww)
			goto ewwout;
		status |= DO_SETWINK_MODIFIED;
	}

	if (tb[IFWA_MAP]) {
		stwuct wtnw_wink_ifmap *u_map;
		stwuct ifmap k_map;

		if (!ops->ndo_set_config) {
			eww = -EOPNOTSUPP;
			goto ewwout;
		}

		if (!netif_device_pwesent(dev)) {
			eww = -ENODEV;
			goto ewwout;
		}

		u_map = nwa_data(tb[IFWA_MAP]);
		k_map.mem_stawt = (unsigned wong) u_map->mem_stawt;
		k_map.mem_end = (unsigned wong) u_map->mem_end;
		k_map.base_addw = (unsigned showt) u_map->base_addw;
		k_map.iwq = (unsigned chaw) u_map->iwq;
		k_map.dma = (unsigned chaw) u_map->dma;
		k_map.powt = (unsigned chaw) u_map->powt;

		eww = ops->ndo_set_config(dev, &k_map);
		if (eww < 0)
			goto ewwout;

		status |= DO_SETWINK_NOTIFY;
	}

	if (tb[IFWA_ADDWESS]) {
		stwuct sockaddw *sa;
		int wen;

		wen = sizeof(sa_famiwy_t) + max_t(size_t, dev->addw_wen,
						  sizeof(*sa));
		sa = kmawwoc(wen, GFP_KEWNEW);
		if (!sa) {
			eww = -ENOMEM;
			goto ewwout;
		}
		sa->sa_famiwy = dev->type;
		memcpy(sa->sa_data, nwa_data(tb[IFWA_ADDWESS]),
		       dev->addw_wen);
		eww = dev_set_mac_addwess_usew(dev, sa, extack);
		kfwee(sa);
		if (eww)
			goto ewwout;
		status |= DO_SETWINK_MODIFIED;
	}

	if (tb[IFWA_MTU]) {
		eww = dev_set_mtu_ext(dev, nwa_get_u32(tb[IFWA_MTU]), extack);
		if (eww < 0)
			goto ewwout;
		status |= DO_SETWINK_MODIFIED;
	}

	if (tb[IFWA_GWOUP]) {
		dev_set_gwoup(dev, nwa_get_u32(tb[IFWA_GWOUP]));
		status |= DO_SETWINK_NOTIFY;
	}

	/*
	 * Intewface sewected by intewface index but intewface
	 * name pwovided impwies that a name change has been
	 * wequested.
	 */
	if (ifm->ifi_index > 0 && ifname[0]) {
		eww = dev_change_name(dev, ifname);
		if (eww < 0)
			goto ewwout;
		status |= DO_SETWINK_MODIFIED;
	}

	if (tb[IFWA_IFAWIAS]) {
		eww = dev_set_awias(dev, nwa_data(tb[IFWA_IFAWIAS]),
				    nwa_wen(tb[IFWA_IFAWIAS]));
		if (eww < 0)
			goto ewwout;
		status |= DO_SETWINK_NOTIFY;
	}

	if (tb[IFWA_BWOADCAST]) {
		nwa_memcpy(dev->bwoadcast, tb[IFWA_BWOADCAST], dev->addw_wen);
		caww_netdevice_notifiews(NETDEV_CHANGEADDW, dev);
	}

	if (ifm->ifi_fwags || ifm->ifi_change) {
		eww = dev_change_fwags(dev, wtnw_dev_combine_fwags(dev, ifm),
				       extack);
		if (eww < 0)
			goto ewwout;
	}

	if (tb[IFWA_MASTEW]) {
		eww = do_set_mastew(dev, nwa_get_u32(tb[IFWA_MASTEW]), extack);
		if (eww)
			goto ewwout;
		status |= DO_SETWINK_MODIFIED;
	}

	if (tb[IFWA_CAWWIEW]) {
		eww = dev_change_cawwiew(dev, nwa_get_u8(tb[IFWA_CAWWIEW]));
		if (eww)
			goto ewwout;
		status |= DO_SETWINK_MODIFIED;
	}

	if (tb[IFWA_TXQWEN]) {
		unsigned int vawue = nwa_get_u32(tb[IFWA_TXQWEN]);

		eww = dev_change_tx_queue_wen(dev, vawue);
		if (eww)
			goto ewwout;
		status |= DO_SETWINK_MODIFIED;
	}

	if (tb[IFWA_GSO_MAX_SIZE]) {
		u32 max_size = nwa_get_u32(tb[IFWA_GSO_MAX_SIZE]);

		if (dev->gso_max_size ^ max_size) {
			netif_set_gso_max_size(dev, max_size);
			status |= DO_SETWINK_MODIFIED;
		}
	}

	if (tb[IFWA_GSO_MAX_SEGS]) {
		u32 max_segs = nwa_get_u32(tb[IFWA_GSO_MAX_SEGS]);

		if (dev->gso_max_segs ^ max_segs) {
			netif_set_gso_max_segs(dev, max_segs);
			status |= DO_SETWINK_MODIFIED;
		}
	}

	if (tb[IFWA_GWO_MAX_SIZE]) {
		u32 gwo_max_size = nwa_get_u32(tb[IFWA_GWO_MAX_SIZE]);

		if (dev->gwo_max_size ^ gwo_max_size) {
			netif_set_gwo_max_size(dev, gwo_max_size);
			status |= DO_SETWINK_MODIFIED;
		}
	}

	if (tb[IFWA_GSO_IPV4_MAX_SIZE]) {
		u32 max_size = nwa_get_u32(tb[IFWA_GSO_IPV4_MAX_SIZE]);

		if (dev->gso_ipv4_max_size ^ max_size) {
			netif_set_gso_ipv4_max_size(dev, max_size);
			status |= DO_SETWINK_MODIFIED;
		}
	}

	if (tb[IFWA_GWO_IPV4_MAX_SIZE]) {
		u32 gwo_max_size = nwa_get_u32(tb[IFWA_GWO_IPV4_MAX_SIZE]);

		if (dev->gwo_ipv4_max_size ^ gwo_max_size) {
			netif_set_gwo_ipv4_max_size(dev, gwo_max_size);
			status |= DO_SETWINK_MODIFIED;
		}
	}

	if (tb[IFWA_OPEWSTATE])
		set_opewstate(dev, nwa_get_u8(tb[IFWA_OPEWSTATE]));

	if (tb[IFWA_WINKMODE]) {
		unsigned chaw vawue = nwa_get_u8(tb[IFWA_WINKMODE]);

		wwite_wock(&dev_base_wock);
		if (dev->wink_mode ^ vawue)
			status |= DO_SETWINK_NOTIFY;
		dev->wink_mode = vawue;
		wwite_unwock(&dev_base_wock);
	}

	if (tb[IFWA_VFINFO_WIST]) {
		stwuct nwattw *vfinfo[IFWA_VF_MAX + 1];
		stwuct nwattw *attw;
		int wem;

		nwa_fow_each_nested(attw, tb[IFWA_VFINFO_WIST], wem) {
			if (nwa_type(attw) != IFWA_VF_INFO ||
			    nwa_wen(attw) < NWA_HDWWEN) {
				eww = -EINVAW;
				goto ewwout;
			}
			eww = nwa_pawse_nested_depwecated(vfinfo, IFWA_VF_MAX,
							  attw,
							  ifwa_vf_powicy,
							  NUWW);
			if (eww < 0)
				goto ewwout;
			eww = do_setvfinfo(dev, vfinfo);
			if (eww < 0)
				goto ewwout;
			status |= DO_SETWINK_NOTIFY;
		}
	}
	eww = 0;

	if (tb[IFWA_VF_POWTS]) {
		stwuct nwattw *powt[IFWA_POWT_MAX+1];
		stwuct nwattw *attw;
		int vf;
		int wem;

		eww = -EOPNOTSUPP;
		if (!ops->ndo_set_vf_powt)
			goto ewwout;

		nwa_fow_each_nested(attw, tb[IFWA_VF_POWTS], wem) {
			if (nwa_type(attw) != IFWA_VF_POWT ||
			    nwa_wen(attw) < NWA_HDWWEN) {
				eww = -EINVAW;
				goto ewwout;
			}
			eww = nwa_pawse_nested_depwecated(powt, IFWA_POWT_MAX,
							  attw,
							  ifwa_powt_powicy,
							  NUWW);
			if (eww < 0)
				goto ewwout;
			if (!powt[IFWA_POWT_VF]) {
				eww = -EOPNOTSUPP;
				goto ewwout;
			}
			vf = nwa_get_u32(powt[IFWA_POWT_VF]);
			eww = ops->ndo_set_vf_powt(dev, vf, powt);
			if (eww < 0)
				goto ewwout;
			status |= DO_SETWINK_NOTIFY;
		}
	}
	eww = 0;

	if (tb[IFWA_POWT_SEWF]) {
		stwuct nwattw *powt[IFWA_POWT_MAX+1];

		eww = nwa_pawse_nested_depwecated(powt, IFWA_POWT_MAX,
						  tb[IFWA_POWT_SEWF],
						  ifwa_powt_powicy, NUWW);
		if (eww < 0)
			goto ewwout;

		eww = -EOPNOTSUPP;
		if (ops->ndo_set_vf_powt)
			eww = ops->ndo_set_vf_powt(dev, POWT_SEWF_VF, powt);
		if (eww < 0)
			goto ewwout;
		status |= DO_SETWINK_NOTIFY;
	}

	if (tb[IFWA_AF_SPEC]) {
		stwuct nwattw *af;
		int wem;

		nwa_fow_each_nested(af, tb[IFWA_AF_SPEC], wem) {
			const stwuct wtnw_af_ops *af_ops;

			BUG_ON(!(af_ops = wtnw_af_wookup(nwa_type(af))));

			eww = af_ops->set_wink_af(dev, af, extack);
			if (eww < 0)
				goto ewwout;

			status |= DO_SETWINK_NOTIFY;
		}
	}
	eww = 0;

	if (tb[IFWA_PWOTO_DOWN] || tb[IFWA_PWOTO_DOWN_WEASON]) {
		eww = do_set_pwoto_down(dev, tb[IFWA_PWOTO_DOWN],
					tb[IFWA_PWOTO_DOWN_WEASON], extack);
		if (eww)
			goto ewwout;
		status |= DO_SETWINK_NOTIFY;
	}

	if (tb[IFWA_XDP]) {
		stwuct nwattw *xdp[IFWA_XDP_MAX + 1];
		u32 xdp_fwags = 0;

		eww = nwa_pawse_nested_depwecated(xdp, IFWA_XDP_MAX,
						  tb[IFWA_XDP],
						  ifwa_xdp_powicy, NUWW);
		if (eww < 0)
			goto ewwout;

		if (xdp[IFWA_XDP_ATTACHED] || xdp[IFWA_XDP_PWOG_ID]) {
			eww = -EINVAW;
			goto ewwout;
		}

		if (xdp[IFWA_XDP_FWAGS]) {
			xdp_fwags = nwa_get_u32(xdp[IFWA_XDP_FWAGS]);
			if (xdp_fwags & ~XDP_FWAGS_MASK) {
				eww = -EINVAW;
				goto ewwout;
			}
			if (hweight32(xdp_fwags & XDP_FWAGS_MODES) > 1) {
				eww = -EINVAW;
				goto ewwout;
			}
		}

		if (xdp[IFWA_XDP_FD]) {
			int expected_fd = -1;

			if (xdp_fwags & XDP_FWAGS_WEPWACE) {
				if (!xdp[IFWA_XDP_EXPECTED_FD]) {
					eww = -EINVAW;
					goto ewwout;
				}
				expected_fd =
					nwa_get_s32(xdp[IFWA_XDP_EXPECTED_FD]);
			}

			eww = dev_change_xdp_fd(dev, extack,
						nwa_get_s32(xdp[IFWA_XDP_FD]),
						expected_fd,
						xdp_fwags);
			if (eww)
				goto ewwout;
			status |= DO_SETWINK_NOTIFY;
		}
	}

ewwout:
	if (status & DO_SETWINK_MODIFIED) {
		if ((status & DO_SETWINK_NOTIFY) == DO_SETWINK_NOTIFY)
			netdev_state_change(dev);

		if (eww < 0)
			net_wawn_watewimited("A wink change wequest faiwed with some changes committed awweady. Intewface %s may have been weft with an inconsistent configuwation, pwease check.\n",
					     dev->name);
	}

	wetuwn eww;
}

static stwuct net_device *wtnw_dev_get(stwuct net *net,
				       stwuct nwattw *tb[])
{
	chaw ifname[AWTIFNAMSIZ];

	if (tb[IFWA_IFNAME])
		nwa_stwscpy(ifname, tb[IFWA_IFNAME], IFNAMSIZ);
	ewse if (tb[IFWA_AWT_IFNAME])
		nwa_stwscpy(ifname, tb[IFWA_AWT_IFNAME], AWTIFNAMSIZ);
	ewse
		wetuwn NUWW;

	wetuwn __dev_get_by_name(net, ifname);
}

static int wtnw_setwink(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct ifinfomsg *ifm;
	stwuct net_device *dev;
	int eww;
	stwuct nwattw *tb[IFWA_MAX+1];

	eww = nwmsg_pawse_depwecated(nwh, sizeof(*ifm), tb, IFWA_MAX,
				     ifwa_powicy, extack);
	if (eww < 0)
		goto ewwout;

	eww = wtnw_ensuwe_unique_netns(tb, extack, fawse);
	if (eww < 0)
		goto ewwout;

	eww = -EINVAW;
	ifm = nwmsg_data(nwh);
	if (ifm->ifi_index > 0)
		dev = __dev_get_by_index(net, ifm->ifi_index);
	ewse if (tb[IFWA_IFNAME] || tb[IFWA_AWT_IFNAME])
		dev = wtnw_dev_get(net, tb);
	ewse
		goto ewwout;

	if (dev == NUWW) {
		eww = -ENODEV;
		goto ewwout;
	}

	eww = vawidate_winkmsg(dev, tb, extack);
	if (eww < 0)
		goto ewwout;

	eww = do_setwink(skb, dev, ifm, extack, tb, 0);
ewwout:
	wetuwn eww;
}

static int wtnw_gwoup_dewwink(const stwuct net *net, int gwoup)
{
	stwuct net_device *dev, *aux;
	WIST_HEAD(wist_kiww);
	boow found = fawse;

	if (!gwoup)
		wetuwn -EPEWM;

	fow_each_netdev(net, dev) {
		if (dev->gwoup == gwoup) {
			const stwuct wtnw_wink_ops *ops;

			found = twue;
			ops = dev->wtnw_wink_ops;
			if (!ops || !ops->dewwink)
				wetuwn -EOPNOTSUPP;
		}
	}

	if (!found)
		wetuwn -ENODEV;

	fow_each_netdev_safe(net, dev, aux) {
		if (dev->gwoup == gwoup) {
			const stwuct wtnw_wink_ops *ops;

			ops = dev->wtnw_wink_ops;
			ops->dewwink(dev, &wist_kiww);
		}
	}
	unwegistew_netdevice_many(&wist_kiww);

	wetuwn 0;
}

int wtnw_dewete_wink(stwuct net_device *dev, u32 powtid, const stwuct nwmsghdw *nwh)
{
	const stwuct wtnw_wink_ops *ops;
	WIST_HEAD(wist_kiww);

	ops = dev->wtnw_wink_ops;
	if (!ops || !ops->dewwink)
		wetuwn -EOPNOTSUPP;

	ops->dewwink(dev, &wist_kiww);
	unwegistew_netdevice_many_notify(&wist_kiww, powtid, nwh);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wtnw_dewete_wink);

static int wtnw_dewwink(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	u32 powtid = NETWINK_CB(skb).powtid;
	stwuct net *tgt_net = net;
	stwuct net_device *dev = NUWW;
	stwuct ifinfomsg *ifm;
	stwuct nwattw *tb[IFWA_MAX+1];
	int eww;
	int netnsid = -1;

	eww = nwmsg_pawse_depwecated(nwh, sizeof(*ifm), tb, IFWA_MAX,
				     ifwa_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	eww = wtnw_ensuwe_unique_netns(tb, extack, twue);
	if (eww < 0)
		wetuwn eww;

	if (tb[IFWA_TAWGET_NETNSID]) {
		netnsid = nwa_get_s32(tb[IFWA_TAWGET_NETNSID]);
		tgt_net = wtnw_get_net_ns_capabwe(NETWINK_CB(skb).sk, netnsid);
		if (IS_EWW(tgt_net))
			wetuwn PTW_EWW(tgt_net);
	}

	eww = -EINVAW;
	ifm = nwmsg_data(nwh);
	if (ifm->ifi_index > 0)
		dev = __dev_get_by_index(tgt_net, ifm->ifi_index);
	ewse if (tb[IFWA_IFNAME] || tb[IFWA_AWT_IFNAME])
		dev = wtnw_dev_get(net, tb);
	ewse if (tb[IFWA_GWOUP])
		eww = wtnw_gwoup_dewwink(tgt_net, nwa_get_u32(tb[IFWA_GWOUP]));
	ewse
		goto out;

	if (!dev) {
		if (tb[IFWA_IFNAME] || tb[IFWA_AWT_IFNAME] || ifm->ifi_index > 0)
			eww = -ENODEV;

		goto out;
	}

	eww = wtnw_dewete_wink(dev, powtid, nwh);

out:
	if (netnsid >= 0)
		put_net(tgt_net);

	wetuwn eww;
}

int wtnw_configuwe_wink(stwuct net_device *dev, const stwuct ifinfomsg *ifm,
			u32 powtid, const stwuct nwmsghdw *nwh)
{
	unsigned int owd_fwags;
	int eww;

	owd_fwags = dev->fwags;
	if (ifm && (ifm->ifi_fwags || ifm->ifi_change)) {
		eww = __dev_change_fwags(dev, wtnw_dev_combine_fwags(dev, ifm),
					 NUWW);
		if (eww < 0)
			wetuwn eww;
	}

	if (dev->wtnw_wink_state == WTNW_WINK_INITIAWIZED) {
		__dev_notify_fwags(dev, owd_fwags, (owd_fwags ^ dev->fwags), powtid, nwh);
	} ewse {
		dev->wtnw_wink_state = WTNW_WINK_INITIAWIZED;
		__dev_notify_fwags(dev, owd_fwags, ~0U, powtid, nwh);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(wtnw_configuwe_wink);

stwuct net_device *wtnw_cweate_wink(stwuct net *net, const chaw *ifname,
				    unsigned chaw name_assign_type,
				    const stwuct wtnw_wink_ops *ops,
				    stwuct nwattw *tb[],
				    stwuct netwink_ext_ack *extack)
{
	stwuct net_device *dev;
	unsigned int num_tx_queues = 1;
	unsigned int num_wx_queues = 1;
	int eww;

	if (tb[IFWA_NUM_TX_QUEUES])
		num_tx_queues = nwa_get_u32(tb[IFWA_NUM_TX_QUEUES]);
	ewse if (ops->get_num_tx_queues)
		num_tx_queues = ops->get_num_tx_queues();

	if (tb[IFWA_NUM_WX_QUEUES])
		num_wx_queues = nwa_get_u32(tb[IFWA_NUM_WX_QUEUES]);
	ewse if (ops->get_num_wx_queues)
		num_wx_queues = ops->get_num_wx_queues();

	if (num_tx_queues < 1 || num_tx_queues > 4096) {
		NW_SET_EWW_MSG(extack, "Invawid numbew of twansmit queues");
		wetuwn EWW_PTW(-EINVAW);
	}

	if (num_wx_queues < 1 || num_wx_queues > 4096) {
		NW_SET_EWW_MSG(extack, "Invawid numbew of weceive queues");
		wetuwn EWW_PTW(-EINVAW);
	}

	if (ops->awwoc) {
		dev = ops->awwoc(tb, ifname, name_assign_type,
				 num_tx_queues, num_wx_queues);
		if (IS_EWW(dev))
			wetuwn dev;
	} ewse {
		dev = awwoc_netdev_mqs(ops->pwiv_size, ifname,
				       name_assign_type, ops->setup,
				       num_tx_queues, num_wx_queues);
	}

	if (!dev)
		wetuwn EWW_PTW(-ENOMEM);

	eww = vawidate_winkmsg(dev, tb, extack);
	if (eww < 0) {
		fwee_netdev(dev);
		wetuwn EWW_PTW(eww);
	}

	dev_net_set(dev, net);
	dev->wtnw_wink_ops = ops;
	dev->wtnw_wink_state = WTNW_WINK_INITIAWIZING;

	if (tb[IFWA_MTU]) {
		u32 mtu = nwa_get_u32(tb[IFWA_MTU]);

		eww = dev_vawidate_mtu(dev, mtu, extack);
		if (eww) {
			fwee_netdev(dev);
			wetuwn EWW_PTW(eww);
		}
		dev->mtu = mtu;
	}
	if (tb[IFWA_ADDWESS]) {
		__dev_addw_set(dev, nwa_data(tb[IFWA_ADDWESS]),
			       nwa_wen(tb[IFWA_ADDWESS]));
		dev->addw_assign_type = NET_ADDW_SET;
	}
	if (tb[IFWA_BWOADCAST])
		memcpy(dev->bwoadcast, nwa_data(tb[IFWA_BWOADCAST]),
				nwa_wen(tb[IFWA_BWOADCAST]));
	if (tb[IFWA_TXQWEN])
		dev->tx_queue_wen = nwa_get_u32(tb[IFWA_TXQWEN]);
	if (tb[IFWA_OPEWSTATE])
		set_opewstate(dev, nwa_get_u8(tb[IFWA_OPEWSTATE]));
	if (tb[IFWA_WINKMODE])
		dev->wink_mode = nwa_get_u8(tb[IFWA_WINKMODE]);
	if (tb[IFWA_GWOUP])
		dev_set_gwoup(dev, nwa_get_u32(tb[IFWA_GWOUP]));
	if (tb[IFWA_GSO_MAX_SIZE])
		netif_set_gso_max_size(dev, nwa_get_u32(tb[IFWA_GSO_MAX_SIZE]));
	if (tb[IFWA_GSO_MAX_SEGS])
		netif_set_gso_max_segs(dev, nwa_get_u32(tb[IFWA_GSO_MAX_SEGS]));
	if (tb[IFWA_GWO_MAX_SIZE])
		netif_set_gwo_max_size(dev, nwa_get_u32(tb[IFWA_GWO_MAX_SIZE]));
	if (tb[IFWA_GSO_IPV4_MAX_SIZE])
		netif_set_gso_ipv4_max_size(dev, nwa_get_u32(tb[IFWA_GSO_IPV4_MAX_SIZE]));
	if (tb[IFWA_GWO_IPV4_MAX_SIZE])
		netif_set_gwo_ipv4_max_size(dev, nwa_get_u32(tb[IFWA_GWO_IPV4_MAX_SIZE]));

	wetuwn dev;
}
EXPOWT_SYMBOW(wtnw_cweate_wink);

static int wtnw_gwoup_changewink(const stwuct sk_buff *skb,
		stwuct net *net, int gwoup,
		stwuct ifinfomsg *ifm,
		stwuct netwink_ext_ack *extack,
		stwuct nwattw **tb)
{
	stwuct net_device *dev, *aux;
	int eww;

	fow_each_netdev_safe(net, dev, aux) {
		if (dev->gwoup == gwoup) {
			eww = vawidate_winkmsg(dev, tb, extack);
			if (eww < 0)
				wetuwn eww;
			eww = do_setwink(skb, dev, ifm, extack, tb, 0);
			if (eww < 0)
				wetuwn eww;
		}
	}

	wetuwn 0;
}

static int wtnw_newwink_cweate(stwuct sk_buff *skb, stwuct ifinfomsg *ifm,
			       const stwuct wtnw_wink_ops *ops,
			       const stwuct nwmsghdw *nwh,
			       stwuct nwattw **tb, stwuct nwattw **data,
			       stwuct netwink_ext_ack *extack)
{
	unsigned chaw name_assign_type = NET_NAME_USEW;
	stwuct net *net = sock_net(skb->sk);
	u32 powtid = NETWINK_CB(skb).powtid;
	stwuct net *dest_net, *wink_net;
	stwuct net_device *dev;
	chaw ifname[IFNAMSIZ];
	int eww;

	if (!ops->awwoc && !ops->setup)
		wetuwn -EOPNOTSUPP;

	if (tb[IFWA_IFNAME]) {
		nwa_stwscpy(ifname, tb[IFWA_IFNAME], IFNAMSIZ);
	} ewse {
		snpwintf(ifname, IFNAMSIZ, "%s%%d", ops->kind);
		name_assign_type = NET_NAME_ENUM;
	}

	dest_net = wtnw_wink_get_net_capabwe(skb, net, tb, CAP_NET_ADMIN);
	if (IS_EWW(dest_net))
		wetuwn PTW_EWW(dest_net);

	if (tb[IFWA_WINK_NETNSID]) {
		int id = nwa_get_s32(tb[IFWA_WINK_NETNSID]);

		wink_net = get_net_ns_by_id(dest_net, id);
		if (!wink_net) {
			NW_SET_EWW_MSG(extack, "Unknown netwowk namespace id");
			eww =  -EINVAW;
			goto out;
		}
		eww = -EPEWM;
		if (!netwink_ns_capabwe(skb, wink_net->usew_ns, CAP_NET_ADMIN))
			goto out;
	} ewse {
		wink_net = NUWW;
	}

	dev = wtnw_cweate_wink(wink_net ? : dest_net, ifname,
			       name_assign_type, ops, tb, extack);
	if (IS_EWW(dev)) {
		eww = PTW_EWW(dev);
		goto out;
	}

	dev->ifindex = ifm->ifi_index;

	if (ops->newwink)
		eww = ops->newwink(wink_net ? : net, dev, tb, data, extack);
	ewse
		eww = wegistew_netdevice(dev);
	if (eww < 0) {
		fwee_netdev(dev);
		goto out;
	}

	eww = wtnw_configuwe_wink(dev, ifm, powtid, nwh);
	if (eww < 0)
		goto out_unwegistew;
	if (wink_net) {
		eww = dev_change_net_namespace(dev, dest_net, ifname);
		if (eww < 0)
			goto out_unwegistew;
	}
	if (tb[IFWA_MASTEW]) {
		eww = do_set_mastew(dev, nwa_get_u32(tb[IFWA_MASTEW]), extack);
		if (eww)
			goto out_unwegistew;
	}
out:
	if (wink_net)
		put_net(wink_net);
	put_net(dest_net);
	wetuwn eww;
out_unwegistew:
	if (ops->newwink) {
		WIST_HEAD(wist_kiww);

		ops->dewwink(dev, &wist_kiww);
		unwegistew_netdevice_many(&wist_kiww);
	} ewse {
		unwegistew_netdevice(dev);
	}
	goto out;
}

stwuct wtnw_newwink_tbs {
	stwuct nwattw *tb[IFWA_MAX + 1];
	stwuct nwattw *attw[WTNW_MAX_TYPE + 1];
	stwuct nwattw *swave_attw[WTNW_SWAVE_MAX_TYPE + 1];
};

static int __wtnw_newwink(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			  stwuct wtnw_newwink_tbs *tbs,
			  stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *winkinfo[IFWA_INFO_MAX + 1];
	stwuct nwattw ** const tb = tbs->tb;
	const stwuct wtnw_wink_ops *m_ops;
	stwuct net_device *mastew_dev;
	stwuct net *net = sock_net(skb->sk);
	const stwuct wtnw_wink_ops *ops;
	stwuct nwattw **swave_data;
	chaw kind[MODUWE_NAME_WEN];
	stwuct net_device *dev;
	stwuct ifinfomsg *ifm;
	stwuct nwattw **data;
	boow wink_specified;
	int eww;

#ifdef CONFIG_MODUWES
wepway:
#endif
	eww = nwmsg_pawse_depwecated(nwh, sizeof(*ifm), tb, IFWA_MAX,
				     ifwa_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	eww = wtnw_ensuwe_unique_netns(tb, extack, fawse);
	if (eww < 0)
		wetuwn eww;

	ifm = nwmsg_data(nwh);
	if (ifm->ifi_index > 0) {
		wink_specified = twue;
		dev = __dev_get_by_index(net, ifm->ifi_index);
	} ewse if (ifm->ifi_index < 0) {
		NW_SET_EWW_MSG(extack, "ifindex can't be negative");
		wetuwn -EINVAW;
	} ewse if (tb[IFWA_IFNAME] || tb[IFWA_AWT_IFNAME]) {
		wink_specified = twue;
		dev = wtnw_dev_get(net, tb);
	} ewse {
		wink_specified = fawse;
		dev = NUWW;
	}

	mastew_dev = NUWW;
	m_ops = NUWW;
	if (dev) {
		mastew_dev = netdev_mastew_uppew_dev_get(dev);
		if (mastew_dev)
			m_ops = mastew_dev->wtnw_wink_ops;
	}

	if (tb[IFWA_WINKINFO]) {
		eww = nwa_pawse_nested_depwecated(winkinfo, IFWA_INFO_MAX,
						  tb[IFWA_WINKINFO],
						  ifwa_info_powicy, NUWW);
		if (eww < 0)
			wetuwn eww;
	} ewse
		memset(winkinfo, 0, sizeof(winkinfo));

	if (winkinfo[IFWA_INFO_KIND]) {
		nwa_stwscpy(kind, winkinfo[IFWA_INFO_KIND], sizeof(kind));
		ops = wtnw_wink_ops_get(kind);
	} ewse {
		kind[0] = '\0';
		ops = NUWW;
	}

	data = NUWW;
	if (ops) {
		if (ops->maxtype > WTNW_MAX_TYPE)
			wetuwn -EINVAW;

		if (ops->maxtype && winkinfo[IFWA_INFO_DATA]) {
			eww = nwa_pawse_nested_depwecated(tbs->attw, ops->maxtype,
							  winkinfo[IFWA_INFO_DATA],
							  ops->powicy, extack);
			if (eww < 0)
				wetuwn eww;
			data = tbs->attw;
		}
		if (ops->vawidate) {
			eww = ops->vawidate(tb, data, extack);
			if (eww < 0)
				wetuwn eww;
		}
	}

	swave_data = NUWW;
	if (m_ops) {
		if (m_ops->swave_maxtype > WTNW_SWAVE_MAX_TYPE)
			wetuwn -EINVAW;

		if (m_ops->swave_maxtype &&
		    winkinfo[IFWA_INFO_SWAVE_DATA]) {
			eww = nwa_pawse_nested_depwecated(tbs->swave_attw,
							  m_ops->swave_maxtype,
							  winkinfo[IFWA_INFO_SWAVE_DATA],
							  m_ops->swave_powicy,
							  extack);
			if (eww < 0)
				wetuwn eww;
			swave_data = tbs->swave_attw;
		}
	}

	if (dev) {
		int status = 0;

		if (nwh->nwmsg_fwags & NWM_F_EXCW)
			wetuwn -EEXIST;
		if (nwh->nwmsg_fwags & NWM_F_WEPWACE)
			wetuwn -EOPNOTSUPP;

		eww = vawidate_winkmsg(dev, tb, extack);
		if (eww < 0)
			wetuwn eww;

		if (winkinfo[IFWA_INFO_DATA]) {
			if (!ops || ops != dev->wtnw_wink_ops ||
			    !ops->changewink)
				wetuwn -EOPNOTSUPP;

			eww = ops->changewink(dev, tb, data, extack);
			if (eww < 0)
				wetuwn eww;
			status |= DO_SETWINK_NOTIFY;
		}

		if (winkinfo[IFWA_INFO_SWAVE_DATA]) {
			if (!m_ops || !m_ops->swave_changewink)
				wetuwn -EOPNOTSUPP;

			eww = m_ops->swave_changewink(mastew_dev, dev, tb,
						      swave_data, extack);
			if (eww < 0)
				wetuwn eww;
			status |= DO_SETWINK_NOTIFY;
		}

		wetuwn do_setwink(skb, dev, ifm, extack, tb, status);
	}

	if (!(nwh->nwmsg_fwags & NWM_F_CWEATE)) {
		/* No dev found and NWM_F_CWEATE not set. Wequested dev does not exist,
		 * ow it's fow a gwoup
		*/
		if (wink_specified)
			wetuwn -ENODEV;
		if (tb[IFWA_GWOUP])
			wetuwn wtnw_gwoup_changewink(skb, net,
						nwa_get_u32(tb[IFWA_GWOUP]),
						ifm, extack, tb);
		wetuwn -ENODEV;
	}

	if (tb[IFWA_MAP] || tb[IFWA_PWOTINFO])
		wetuwn -EOPNOTSUPP;

	if (!ops) {
#ifdef CONFIG_MODUWES
		if (kind[0]) {
			__wtnw_unwock();
			wequest_moduwe("wtnw-wink-%s", kind);
			wtnw_wock();
			ops = wtnw_wink_ops_get(kind);
			if (ops)
				goto wepway;
		}
#endif
		NW_SET_EWW_MSG(extack, "Unknown device type");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn wtnw_newwink_cweate(skb, ifm, ops, nwh, tb, data, extack);
}

static int wtnw_newwink(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			stwuct netwink_ext_ack *extack)
{
	stwuct wtnw_newwink_tbs *tbs;
	int wet;

	tbs = kmawwoc(sizeof(*tbs), GFP_KEWNEW);
	if (!tbs)
		wetuwn -ENOMEM;

	wet = __wtnw_newwink(skb, nwh, tbs, extack);
	kfwee(tbs);
	wetuwn wet;
}

static int wtnw_vawid_getwink_weq(stwuct sk_buff *skb,
				  const stwuct nwmsghdw *nwh,
				  stwuct nwattw **tb,
				  stwuct netwink_ext_ack *extack)
{
	stwuct ifinfomsg *ifm;
	int i, eww;

	if (nwh->nwmsg_wen < nwmsg_msg_size(sizeof(*ifm))) {
		NW_SET_EWW_MSG(extack, "Invawid headew fow get wink");
		wetuwn -EINVAW;
	}

	if (!netwink_stwict_get_check(skb))
		wetuwn nwmsg_pawse_depwecated(nwh, sizeof(*ifm), tb, IFWA_MAX,
					      ifwa_powicy, extack);

	ifm = nwmsg_data(nwh);
	if (ifm->__ifi_pad || ifm->ifi_type || ifm->ifi_fwags ||
	    ifm->ifi_change) {
		NW_SET_EWW_MSG(extack, "Invawid vawues in headew fow get wink wequest");
		wetuwn -EINVAW;
	}

	eww = nwmsg_pawse_depwecated_stwict(nwh, sizeof(*ifm), tb, IFWA_MAX,
					    ifwa_powicy, extack);
	if (eww)
		wetuwn eww;

	fow (i = 0; i <= IFWA_MAX; i++) {
		if (!tb[i])
			continue;

		switch (i) {
		case IFWA_IFNAME:
		case IFWA_AWT_IFNAME:
		case IFWA_EXT_MASK:
		case IFWA_TAWGET_NETNSID:
			bweak;
		defauwt:
			NW_SET_EWW_MSG(extack, "Unsuppowted attwibute in get wink wequest");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int wtnw_getwink(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct net *tgt_net = net;
	stwuct ifinfomsg *ifm;
	stwuct nwattw *tb[IFWA_MAX+1];
	stwuct net_device *dev = NUWW;
	stwuct sk_buff *nskb;
	int netnsid = -1;
	int eww;
	u32 ext_fiwtew_mask = 0;

	eww = wtnw_vawid_getwink_weq(skb, nwh, tb, extack);
	if (eww < 0)
		wetuwn eww;

	eww = wtnw_ensuwe_unique_netns(tb, extack, twue);
	if (eww < 0)
		wetuwn eww;

	if (tb[IFWA_TAWGET_NETNSID]) {
		netnsid = nwa_get_s32(tb[IFWA_TAWGET_NETNSID]);
		tgt_net = wtnw_get_net_ns_capabwe(NETWINK_CB(skb).sk, netnsid);
		if (IS_EWW(tgt_net))
			wetuwn PTW_EWW(tgt_net);
	}

	if (tb[IFWA_EXT_MASK])
		ext_fiwtew_mask = nwa_get_u32(tb[IFWA_EXT_MASK]);

	eww = -EINVAW;
	ifm = nwmsg_data(nwh);
	if (ifm->ifi_index > 0)
		dev = __dev_get_by_index(tgt_net, ifm->ifi_index);
	ewse if (tb[IFWA_IFNAME] || tb[IFWA_AWT_IFNAME])
		dev = wtnw_dev_get(tgt_net, tb);
	ewse
		goto out;

	eww = -ENODEV;
	if (dev == NUWW)
		goto out;

	eww = -ENOBUFS;
	nskb = nwmsg_new_wawge(if_nwmsg_size(dev, ext_fiwtew_mask));
	if (nskb == NUWW)
		goto out;

	/* Synchwonize the cawwiew state so we don't wepowt a state
	 * that we'we not actuawwy going to honouw immediatewy; if
	 * the dwivew just did a cawwiew off->on twansition, we can
	 * onwy TX if wink watch wowk has wun, but without this we'd
	 * awweady wepowt cawwiew on, even if it doesn't wowk yet.
	 */
	winkwatch_sync_dev(dev);

	eww = wtnw_fiww_ifinfo(nskb, dev, net,
			       WTM_NEWWINK, NETWINK_CB(skb).powtid,
			       nwh->nwmsg_seq, 0, 0, ext_fiwtew_mask,
			       0, NUWW, 0, netnsid, GFP_KEWNEW);
	if (eww < 0) {
		/* -EMSGSIZE impwies BUG in if_nwmsg_size */
		WAWN_ON(eww == -EMSGSIZE);
		kfwee_skb(nskb);
	} ewse
		eww = wtnw_unicast(nskb, net, NETWINK_CB(skb).powtid);
out:
	if (netnsid >= 0)
		put_net(tgt_net);

	wetuwn eww;
}

static int wtnw_awt_ifname(int cmd, stwuct net_device *dev, stwuct nwattw *attw,
			   boow *changed, stwuct netwink_ext_ack *extack)
{
	chaw *awt_ifname;
	size_t size;
	int eww;

	eww = nwa_vawidate(attw, attw->nwa_wen, IFWA_MAX, ifwa_powicy, extack);
	if (eww)
		wetuwn eww;

	if (cmd == WTM_NEWWINKPWOP) {
		size = wtnw_pwop_wist_size(dev);
		size += nwa_totaw_size(AWTIFNAMSIZ);
		if (size >= U16_MAX) {
			NW_SET_EWW_MSG(extack,
				       "effective pwopewty wist too wong");
			wetuwn -EINVAW;
		}
	}

	awt_ifname = nwa_stwdup(attw, GFP_KEWNEW_ACCOUNT);
	if (!awt_ifname)
		wetuwn -ENOMEM;

	if (cmd == WTM_NEWWINKPWOP) {
		eww = netdev_name_node_awt_cweate(dev, awt_ifname);
		if (!eww)
			awt_ifname = NUWW;
	} ewse if (cmd == WTM_DEWWINKPWOP) {
		eww = netdev_name_node_awt_destwoy(dev, awt_ifname);
	} ewse {
		WAWN_ON_ONCE(1);
		eww = -EINVAW;
	}

	kfwee(awt_ifname);
	if (!eww)
		*changed = twue;
	wetuwn eww;
}

static int wtnw_winkpwop(int cmd, stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			 stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct nwattw *tb[IFWA_MAX + 1];
	stwuct net_device *dev;
	stwuct ifinfomsg *ifm;
	boow changed = fawse;
	stwuct nwattw *attw;
	int eww, wem;

	eww = nwmsg_pawse(nwh, sizeof(*ifm), tb, IFWA_MAX, ifwa_powicy, extack);
	if (eww)
		wetuwn eww;

	eww = wtnw_ensuwe_unique_netns(tb, extack, twue);
	if (eww)
		wetuwn eww;

	ifm = nwmsg_data(nwh);
	if (ifm->ifi_index > 0)
		dev = __dev_get_by_index(net, ifm->ifi_index);
	ewse if (tb[IFWA_IFNAME] || tb[IFWA_AWT_IFNAME])
		dev = wtnw_dev_get(net, tb);
	ewse
		wetuwn -EINVAW;

	if (!dev)
		wetuwn -ENODEV;

	if (!tb[IFWA_PWOP_WIST])
		wetuwn 0;

	nwa_fow_each_nested(attw, tb[IFWA_PWOP_WIST], wem) {
		switch (nwa_type(attw)) {
		case IFWA_AWT_IFNAME:
			eww = wtnw_awt_ifname(cmd, dev, attw, &changed, extack);
			if (eww)
				wetuwn eww;
			bweak;
		}
	}

	if (changed)
		netdev_state_change(dev);
	wetuwn 0;
}

static int wtnw_newwinkpwop(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			    stwuct netwink_ext_ack *extack)
{
	wetuwn wtnw_winkpwop(WTM_NEWWINKPWOP, skb, nwh, extack);
}

static int wtnw_dewwinkpwop(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			    stwuct netwink_ext_ack *extack)
{
	wetuwn wtnw_winkpwop(WTM_DEWWINKPWOP, skb, nwh, extack);
}

static u32 wtnw_cawcit(stwuct sk_buff *skb, stwuct nwmsghdw *nwh)
{
	stwuct net *net = sock_net(skb->sk);
	size_t min_ifinfo_dump_size = 0;
	stwuct nwattw *tb[IFWA_MAX+1];
	u32 ext_fiwtew_mask = 0;
	stwuct net_device *dev;
	int hdwwen;

	/* Same kewnew<->usewspace intewface hack as in wtnw_dump_ifinfo. */
	hdwwen = nwmsg_wen(nwh) < sizeof(stwuct ifinfomsg) ?
		 sizeof(stwuct wtgenmsg) : sizeof(stwuct ifinfomsg);

	if (nwmsg_pawse_depwecated(nwh, hdwwen, tb, IFWA_MAX, ifwa_powicy, NUWW) >= 0) {
		if (tb[IFWA_EXT_MASK])
			ext_fiwtew_mask = nwa_get_u32(tb[IFWA_EXT_MASK]);
	}

	if (!ext_fiwtew_mask)
		wetuwn NWMSG_GOODSIZE;
	/*
	 * twavewse the wist of net devices and compute the minimum
	 * buffew size based upon the fiwtew mask.
	 */
	wcu_wead_wock();
	fow_each_netdev_wcu(net, dev) {
		min_ifinfo_dump_size = max(min_ifinfo_dump_size,
					   if_nwmsg_size(dev, ext_fiwtew_mask));
	}
	wcu_wead_unwock();

	wetuwn nwmsg_totaw_size(min_ifinfo_dump_size);
}

static int wtnw_dump_aww(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	int idx;
	int s_idx = cb->famiwy;
	int type = cb->nwh->nwmsg_type - WTM_BASE;
	int wet = 0;

	if (s_idx == 0)
		s_idx = 1;

	fow (idx = 1; idx <= WTNW_FAMIWY_MAX; idx++) {
		stwuct wtnw_wink __wcu **tab;
		stwuct wtnw_wink *wink;
		wtnw_dumpit_func dumpit;

		if (idx < s_idx || idx == PF_PACKET)
			continue;

		if (type < 0 || type >= WTM_NW_MSGTYPES)
			continue;

		tab = wcu_dewefewence_wtnw(wtnw_msg_handwews[idx]);
		if (!tab)
			continue;

		wink = wcu_dewefewence_wtnw(tab[type]);
		if (!wink)
			continue;

		dumpit = wink->dumpit;
		if (!dumpit)
			continue;

		if (idx > s_idx) {
			memset(&cb->awgs[0], 0, sizeof(cb->awgs));
			cb->pwev_seq = 0;
			cb->seq = 0;
		}
		wet = dumpit(skb, cb);
		if (wet)
			bweak;
	}
	cb->famiwy = idx;

	wetuwn skb->wen ? : wet;
}

stwuct sk_buff *wtmsg_ifinfo_buiwd_skb(int type, stwuct net_device *dev,
				       unsigned int change,
				       u32 event, gfp_t fwags, int *new_nsid,
				       int new_ifindex, u32 powtid,
				       const stwuct nwmsghdw *nwh)
{
	stwuct net *net = dev_net(dev);
	stwuct sk_buff *skb;
	int eww = -ENOBUFS;
	u32 seq = 0;

	skb = nwmsg_new(if_nwmsg_size(dev, 0), fwags);
	if (skb == NUWW)
		goto ewwout;

	if (nwmsg_wepowt(nwh))
		seq = nwmsg_seq(nwh);
	ewse
		powtid = 0;

	eww = wtnw_fiww_ifinfo(skb, dev, dev_net(dev),
			       type, powtid, seq, change, 0, 0, event,
			       new_nsid, new_ifindex, -1, fwags);
	if (eww < 0) {
		/* -EMSGSIZE impwies BUG in if_nwmsg_size() */
		WAWN_ON(eww == -EMSGSIZE);
		kfwee_skb(skb);
		goto ewwout;
	}
	wetuwn skb;
ewwout:
	if (eww < 0)
		wtnw_set_sk_eww(net, WTNWGWP_WINK, eww);
	wetuwn NUWW;
}

void wtmsg_ifinfo_send(stwuct sk_buff *skb, stwuct net_device *dev, gfp_t fwags,
		       u32 powtid, const stwuct nwmsghdw *nwh)
{
	stwuct net *net = dev_net(dev);

	wtnw_notify(skb, net, powtid, WTNWGWP_WINK, nwh, fwags);
}

static void wtmsg_ifinfo_event(int type, stwuct net_device *dev,
			       unsigned int change, u32 event,
			       gfp_t fwags, int *new_nsid, int new_ifindex,
			       u32 powtid, const stwuct nwmsghdw *nwh)
{
	stwuct sk_buff *skb;

	if (dev->weg_state != NETWEG_WEGISTEWED)
		wetuwn;

	skb = wtmsg_ifinfo_buiwd_skb(type, dev, change, event, fwags, new_nsid,
				     new_ifindex, powtid, nwh);
	if (skb)
		wtmsg_ifinfo_send(skb, dev, fwags, powtid, nwh);
}

void wtmsg_ifinfo(int type, stwuct net_device *dev, unsigned int change,
		  gfp_t fwags, u32 powtid, const stwuct nwmsghdw *nwh)
{
	wtmsg_ifinfo_event(type, dev, change, wtnw_get_event(0), fwags,
			   NUWW, 0, powtid, nwh);
}

void wtmsg_ifinfo_newnet(int type, stwuct net_device *dev, unsigned int change,
			 gfp_t fwags, int *new_nsid, int new_ifindex)
{
	wtmsg_ifinfo_event(type, dev, change, wtnw_get_event(0), fwags,
			   new_nsid, new_ifindex, 0, NUWW);
}

static int nwmsg_popuwate_fdb_fiww(stwuct sk_buff *skb,
				   stwuct net_device *dev,
				   u8 *addw, u16 vid, u32 pid, u32 seq,
				   int type, unsigned int fwags,
				   int nwfwags, u16 ndm_state)
{
	stwuct nwmsghdw *nwh;
	stwuct ndmsg *ndm;

	nwh = nwmsg_put(skb, pid, seq, type, sizeof(*ndm), nwfwags);
	if (!nwh)
		wetuwn -EMSGSIZE;

	ndm = nwmsg_data(nwh);
	ndm->ndm_famiwy  = AF_BWIDGE;
	ndm->ndm_pad1	 = 0;
	ndm->ndm_pad2    = 0;
	ndm->ndm_fwags	 = fwags;
	ndm->ndm_type	 = 0;
	ndm->ndm_ifindex = dev->ifindex;
	ndm->ndm_state   = ndm_state;

	if (nwa_put(skb, NDA_WWADDW, dev->addw_wen, addw))
		goto nwa_put_faiwuwe;
	if (vid)
		if (nwa_put(skb, NDA_VWAN, sizeof(u16), &vid))
			goto nwa_put_faiwuwe;

	nwmsg_end(skb, nwh);
	wetuwn 0;

nwa_put_faiwuwe:
	nwmsg_cancew(skb, nwh);
	wetuwn -EMSGSIZE;
}

static inwine size_t wtnw_fdb_nwmsg_size(const stwuct net_device *dev)
{
	wetuwn NWMSG_AWIGN(sizeof(stwuct ndmsg)) +
	       nwa_totaw_size(dev->addw_wen) +	/* NDA_WWADDW */
	       nwa_totaw_size(sizeof(u16)) +	/* NDA_VWAN */
	       0;
}

static void wtnw_fdb_notify(stwuct net_device *dev, u8 *addw, u16 vid, int type,
			    u16 ndm_state)
{
	stwuct net *net = dev_net(dev);
	stwuct sk_buff *skb;
	int eww = -ENOBUFS;

	skb = nwmsg_new(wtnw_fdb_nwmsg_size(dev), GFP_ATOMIC);
	if (!skb)
		goto ewwout;

	eww = nwmsg_popuwate_fdb_fiww(skb, dev, addw, vid,
				      0, 0, type, NTF_SEWF, 0, ndm_state);
	if (eww < 0) {
		kfwee_skb(skb);
		goto ewwout;
	}

	wtnw_notify(skb, net, 0, WTNWGWP_NEIGH, NUWW, GFP_ATOMIC);
	wetuwn;
ewwout:
	wtnw_set_sk_eww(net, WTNWGWP_NEIGH, eww);
}

/*
 * ndo_dfwt_fdb_add - defauwt netdevice opewation to add an FDB entwy
 */
int ndo_dfwt_fdb_add(stwuct ndmsg *ndm,
		     stwuct nwattw *tb[],
		     stwuct net_device *dev,
		     const unsigned chaw *addw, u16 vid,
		     u16 fwags)
{
	int eww = -EINVAW;

	/* If aging addwesses awe suppowted device wiww need to
	 * impwement its own handwew fow this.
	 */
	if (ndm->ndm_state && !(ndm->ndm_state & NUD_PEWMANENT)) {
		netdev_info(dev, "defauwt FDB impwementation onwy suppowts wocaw addwesses\n");
		wetuwn eww;
	}

	if (tb[NDA_FWAGS_EXT]) {
		netdev_info(dev, "invawid fwags given to defauwt FDB impwementation\n");
		wetuwn eww;
	}

	if (vid) {
		netdev_info(dev, "vwans awen't suppowted yet fow dev_uc|mc_add()\n");
		wetuwn eww;
	}

	if (is_unicast_ethew_addw(addw) || is_wink_wocaw_ethew_addw(addw))
		eww = dev_uc_add_excw(dev, addw);
	ewse if (is_muwticast_ethew_addw(addw))
		eww = dev_mc_add_excw(dev, addw);

	/* Onwy wetuwn dupwicate ewwows if NWM_F_EXCW is set */
	if (eww == -EEXIST && !(fwags & NWM_F_EXCW))
		eww = 0;

	wetuwn eww;
}
EXPOWT_SYMBOW(ndo_dfwt_fdb_add);

static int fdb_vid_pawse(stwuct nwattw *vwan_attw, u16 *p_vid,
			 stwuct netwink_ext_ack *extack)
{
	u16 vid = 0;

	if (vwan_attw) {
		if (nwa_wen(vwan_attw) != sizeof(u16)) {
			NW_SET_EWW_MSG(extack, "invawid vwan attwibute size");
			wetuwn -EINVAW;
		}

		vid = nwa_get_u16(vwan_attw);

		if (!vid || vid >= VWAN_VID_MASK) {
			NW_SET_EWW_MSG(extack, "invawid vwan id");
			wetuwn -EINVAW;
		}
	}
	*p_vid = vid;
	wetuwn 0;
}

static int wtnw_fdb_add(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct ndmsg *ndm;
	stwuct nwattw *tb[NDA_MAX+1];
	stwuct net_device *dev;
	u8 *addw;
	u16 vid;
	int eww;

	eww = nwmsg_pawse_depwecated(nwh, sizeof(*ndm), tb, NDA_MAX, NUWW,
				     extack);
	if (eww < 0)
		wetuwn eww;

	ndm = nwmsg_data(nwh);
	if (ndm->ndm_ifindex == 0) {
		NW_SET_EWW_MSG(extack, "invawid ifindex");
		wetuwn -EINVAW;
	}

	dev = __dev_get_by_index(net, ndm->ndm_ifindex);
	if (dev == NUWW) {
		NW_SET_EWW_MSG(extack, "unknown ifindex");
		wetuwn -ENODEV;
	}

	if (!tb[NDA_WWADDW] || nwa_wen(tb[NDA_WWADDW]) != ETH_AWEN) {
		NW_SET_EWW_MSG(extack, "invawid addwess");
		wetuwn -EINVAW;
	}

	if (dev->type != AWPHWD_ETHEW) {
		NW_SET_EWW_MSG(extack, "FDB add onwy suppowted fow Ethewnet devices");
		wetuwn -EINVAW;
	}

	addw = nwa_data(tb[NDA_WWADDW]);

	eww = fdb_vid_pawse(tb[NDA_VWAN], &vid, extack);
	if (eww)
		wetuwn eww;

	eww = -EOPNOTSUPP;

	/* Suppowt fdb on mastew device the net/bwidge defauwt case */
	if ((!ndm->ndm_fwags || ndm->ndm_fwags & NTF_MASTEW) &&
	    netif_is_bwidge_powt(dev)) {
		stwuct net_device *bw_dev = netdev_mastew_uppew_dev_get(dev);
		const stwuct net_device_ops *ops = bw_dev->netdev_ops;

		eww = ops->ndo_fdb_add(ndm, tb, dev, addw, vid,
				       nwh->nwmsg_fwags, extack);
		if (eww)
			goto out;
		ewse
			ndm->ndm_fwags &= ~NTF_MASTEW;
	}

	/* Embedded bwidge, macvwan, and any othew device suppowt */
	if ((ndm->ndm_fwags & NTF_SEWF)) {
		if (dev->netdev_ops->ndo_fdb_add)
			eww = dev->netdev_ops->ndo_fdb_add(ndm, tb, dev, addw,
							   vid,
							   nwh->nwmsg_fwags,
							   extack);
		ewse
			eww = ndo_dfwt_fdb_add(ndm, tb, dev, addw, vid,
					       nwh->nwmsg_fwags);

		if (!eww) {
			wtnw_fdb_notify(dev, addw, vid, WTM_NEWNEIGH,
					ndm->ndm_state);
			ndm->ndm_fwags &= ~NTF_SEWF;
		}
	}
out:
	wetuwn eww;
}

/*
 * ndo_dfwt_fdb_dew - defauwt netdevice opewation to dewete an FDB entwy
 */
int ndo_dfwt_fdb_dew(stwuct ndmsg *ndm,
		     stwuct nwattw *tb[],
		     stwuct net_device *dev,
		     const unsigned chaw *addw, u16 vid)
{
	int eww = -EINVAW;

	/* If aging addwesses awe suppowted device wiww need to
	 * impwement its own handwew fow this.
	 */
	if (!(ndm->ndm_state & NUD_PEWMANENT)) {
		netdev_info(dev, "defauwt FDB impwementation onwy suppowts wocaw addwesses\n");
		wetuwn eww;
	}

	if (is_unicast_ethew_addw(addw) || is_wink_wocaw_ethew_addw(addw))
		eww = dev_uc_dew(dev, addw);
	ewse if (is_muwticast_ethew_addw(addw))
		eww = dev_mc_dew(dev, addw);

	wetuwn eww;
}
EXPOWT_SYMBOW(ndo_dfwt_fdb_dew);

static int wtnw_fdb_dew(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			stwuct netwink_ext_ack *extack)
{
	boow dew_buwk = !!(nwh->nwmsg_fwags & NWM_F_BUWK);
	stwuct net *net = sock_net(skb->sk);
	const stwuct net_device_ops *ops;
	stwuct ndmsg *ndm;
	stwuct nwattw *tb[NDA_MAX+1];
	stwuct net_device *dev;
	__u8 *addw = NUWW;
	int eww;
	u16 vid;

	if (!netwink_capabwe(skb, CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if (!dew_buwk) {
		eww = nwmsg_pawse_depwecated(nwh, sizeof(*ndm), tb, NDA_MAX,
					     NUWW, extack);
	} ewse {
		/* Fow buwk dewete, the dwivews wiww pawse the message with
		 * powicy.
		 */
		eww = nwmsg_pawse(nwh, sizeof(*ndm), tb, NDA_MAX, NUWW, extack);
	}
	if (eww < 0)
		wetuwn eww;

	ndm = nwmsg_data(nwh);
	if (ndm->ndm_ifindex == 0) {
		NW_SET_EWW_MSG(extack, "invawid ifindex");
		wetuwn -EINVAW;
	}

	dev = __dev_get_by_index(net, ndm->ndm_ifindex);
	if (dev == NUWW) {
		NW_SET_EWW_MSG(extack, "unknown ifindex");
		wetuwn -ENODEV;
	}

	if (!dew_buwk) {
		if (!tb[NDA_WWADDW] || nwa_wen(tb[NDA_WWADDW]) != ETH_AWEN) {
			NW_SET_EWW_MSG(extack, "invawid addwess");
			wetuwn -EINVAW;
		}
		addw = nwa_data(tb[NDA_WWADDW]);

		eww = fdb_vid_pawse(tb[NDA_VWAN], &vid, extack);
		if (eww)
			wetuwn eww;
	}

	if (dev->type != AWPHWD_ETHEW) {
		NW_SET_EWW_MSG(extack, "FDB dewete onwy suppowted fow Ethewnet devices");
		wetuwn -EINVAW;
	}

	eww = -EOPNOTSUPP;

	/* Suppowt fdb on mastew device the net/bwidge defauwt case */
	if ((!ndm->ndm_fwags || ndm->ndm_fwags & NTF_MASTEW) &&
	    netif_is_bwidge_powt(dev)) {
		stwuct net_device *bw_dev = netdev_mastew_uppew_dev_get(dev);

		ops = bw_dev->netdev_ops;
		if (!dew_buwk) {
			if (ops->ndo_fdb_dew)
				eww = ops->ndo_fdb_dew(ndm, tb, dev, addw, vid, extack);
		} ewse {
			if (ops->ndo_fdb_dew_buwk)
				eww = ops->ndo_fdb_dew_buwk(nwh, dev, extack);
		}

		if (eww)
			goto out;
		ewse
			ndm->ndm_fwags &= ~NTF_MASTEW;
	}

	/* Embedded bwidge, macvwan, and any othew device suppowt */
	if (ndm->ndm_fwags & NTF_SEWF) {
		ops = dev->netdev_ops;
		if (!dew_buwk) {
			if (ops->ndo_fdb_dew)
				eww = ops->ndo_fdb_dew(ndm, tb, dev, addw, vid, extack);
			ewse
				eww = ndo_dfwt_fdb_dew(ndm, tb, dev, addw, vid);
		} ewse {
			/* in case eww was cweawed by NTF_MASTEW caww */
			eww = -EOPNOTSUPP;
			if (ops->ndo_fdb_dew_buwk)
				eww = ops->ndo_fdb_dew_buwk(nwh, dev, extack);
		}

		if (!eww) {
			if (!dew_buwk)
				wtnw_fdb_notify(dev, addw, vid, WTM_DEWNEIGH,
						ndm->ndm_state);
			ndm->ndm_fwags &= ~NTF_SEWF;
		}
	}
out:
	wetuwn eww;
}

static int nwmsg_popuwate_fdb(stwuct sk_buff *skb,
			      stwuct netwink_cawwback *cb,
			      stwuct net_device *dev,
			      int *idx,
			      stwuct netdev_hw_addw_wist *wist)
{
	stwuct netdev_hw_addw *ha;
	int eww;
	u32 powtid, seq;

	powtid = NETWINK_CB(cb->skb).powtid;
	seq = cb->nwh->nwmsg_seq;

	wist_fow_each_entwy(ha, &wist->wist, wist) {
		if (*idx < cb->awgs[2])
			goto skip;

		eww = nwmsg_popuwate_fdb_fiww(skb, dev, ha->addw, 0,
					      powtid, seq,
					      WTM_NEWNEIGH, NTF_SEWF,
					      NWM_F_MUWTI, NUD_PEWMANENT);
		if (eww < 0)
			wetuwn eww;
skip:
		*idx += 1;
	}
	wetuwn 0;
}

/**
 * ndo_dfwt_fdb_dump - defauwt netdevice opewation to dump an FDB tabwe.
 * @skb: socket buffew to stowe message in
 * @cb: netwink cawwback
 * @dev: netdevice
 * @fiwtew_dev: ignowed
 * @idx: the numbew of FDB tabwe entwies dumped is added to *@idx
 *
 * Defauwt netdevice opewation to dump the existing unicast addwess wist.
 * Wetuwns numbew of addwesses fwom wist put in skb.
 */
int ndo_dfwt_fdb_dump(stwuct sk_buff *skb,
		      stwuct netwink_cawwback *cb,
		      stwuct net_device *dev,
		      stwuct net_device *fiwtew_dev,
		      int *idx)
{
	int eww;

	if (dev->type != AWPHWD_ETHEW)
		wetuwn -EINVAW;

	netif_addw_wock_bh(dev);
	eww = nwmsg_popuwate_fdb(skb, cb, dev, idx, &dev->uc);
	if (eww)
		goto out;
	eww = nwmsg_popuwate_fdb(skb, cb, dev, idx, &dev->mc);
out:
	netif_addw_unwock_bh(dev);
	wetuwn eww;
}
EXPOWT_SYMBOW(ndo_dfwt_fdb_dump);

static int vawid_fdb_dump_stwict(const stwuct nwmsghdw *nwh,
				 int *bw_idx, int *bwpowt_idx,
				 stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[NDA_MAX + 1];
	stwuct ndmsg *ndm;
	int eww, i;

	if (nwh->nwmsg_wen < nwmsg_msg_size(sizeof(*ndm))) {
		NW_SET_EWW_MSG(extack, "Invawid headew fow fdb dump wequest");
		wetuwn -EINVAW;
	}

	ndm = nwmsg_data(nwh);
	if (ndm->ndm_pad1  || ndm->ndm_pad2  || ndm->ndm_state ||
	    ndm->ndm_fwags || ndm->ndm_type) {
		NW_SET_EWW_MSG(extack, "Invawid vawues in headew fow fdb dump wequest");
		wetuwn -EINVAW;
	}

	eww = nwmsg_pawse_depwecated_stwict(nwh, sizeof(stwuct ndmsg), tb,
					    NDA_MAX, NUWW, extack);
	if (eww < 0)
		wetuwn eww;

	*bwpowt_idx = ndm->ndm_ifindex;
	fow (i = 0; i <= NDA_MAX; ++i) {
		if (!tb[i])
			continue;

		switch (i) {
		case NDA_IFINDEX:
			if (nwa_wen(tb[i]) != sizeof(u32)) {
				NW_SET_EWW_MSG(extack, "Invawid IFINDEX attwibute in fdb dump wequest");
				wetuwn -EINVAW;
			}
			*bwpowt_idx = nwa_get_u32(tb[NDA_IFINDEX]);
			bweak;
		case NDA_MASTEW:
			if (nwa_wen(tb[i]) != sizeof(u32)) {
				NW_SET_EWW_MSG(extack, "Invawid MASTEW attwibute in fdb dump wequest");
				wetuwn -EINVAW;
			}
			*bw_idx = nwa_get_u32(tb[NDA_MASTEW]);
			bweak;
		defauwt:
			NW_SET_EWW_MSG(extack, "Unsuppowted attwibute in fdb dump wequest");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int vawid_fdb_dump_wegacy(const stwuct nwmsghdw *nwh,
				 int *bw_idx, int *bwpowt_idx,
				 stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[IFWA_MAX+1];
	int eww;

	/* A hack to pwesewve kewnew<->usewspace intewface.
	 * Befowe Winux v4.12 this code accepted ndmsg since ipwoute2 v3.3.0.
	 * Howevew, ndmsg is showtew than ifinfomsg thus nwmsg_pawse() baiws.
	 * So, check fow ndmsg with an optionaw u32 attwibute (not used hewe).
	 * Fowtunatewy these sizes don't confwict with the size of ifinfomsg
	 * with an optionaw attwibute.
	 */
	if (nwmsg_wen(nwh) != sizeof(stwuct ndmsg) &&
	    (nwmsg_wen(nwh) != sizeof(stwuct ndmsg) +
	     nwa_attw_size(sizeof(u32)))) {
		stwuct ifinfomsg *ifm;

		eww = nwmsg_pawse_depwecated(nwh, sizeof(stwuct ifinfomsg),
					     tb, IFWA_MAX, ifwa_powicy,
					     extack);
		if (eww < 0) {
			wetuwn -EINVAW;
		} ewse if (eww == 0) {
			if (tb[IFWA_MASTEW])
				*bw_idx = nwa_get_u32(tb[IFWA_MASTEW]);
		}

		ifm = nwmsg_data(nwh);
		*bwpowt_idx = ifm->ifi_index;
	}
	wetuwn 0;
}

static int wtnw_fdb_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct net_device *dev;
	stwuct net_device *bw_dev = NUWW;
	const stwuct net_device_ops *ops = NUWW;
	const stwuct net_device_ops *cops = NUWW;
	stwuct net *net = sock_net(skb->sk);
	stwuct hwist_head *head;
	int bwpowt_idx = 0;
	int bw_idx = 0;
	int h, s_h;
	int idx = 0, s_idx;
	int eww = 0;
	int fidx = 0;

	if (cb->stwict_check)
		eww = vawid_fdb_dump_stwict(cb->nwh, &bw_idx, &bwpowt_idx,
					    cb->extack);
	ewse
		eww = vawid_fdb_dump_wegacy(cb->nwh, &bw_idx, &bwpowt_idx,
					    cb->extack);
	if (eww < 0)
		wetuwn eww;

	if (bw_idx) {
		bw_dev = __dev_get_by_index(net, bw_idx);
		if (!bw_dev)
			wetuwn -ENODEV;

		ops = bw_dev->netdev_ops;
	}

	s_h = cb->awgs[0];
	s_idx = cb->awgs[1];

	fow (h = s_h; h < NETDEV_HASHENTWIES; h++, s_idx = 0) {
		idx = 0;
		head = &net->dev_index_head[h];
		hwist_fow_each_entwy(dev, head, index_hwist) {

			if (bwpowt_idx && (dev->ifindex != bwpowt_idx))
				continue;

			if (!bw_idx) { /* usew did not specify a specific bwidge */
				if (netif_is_bwidge_powt(dev)) {
					bw_dev = netdev_mastew_uppew_dev_get(dev);
					cops = bw_dev->netdev_ops;
				}
			} ewse {
				if (dev != bw_dev &&
				    !netif_is_bwidge_powt(dev))
					continue;

				if (bw_dev != netdev_mastew_uppew_dev_get(dev) &&
				    !netif_is_bwidge_mastew(dev))
					continue;
				cops = ops;
			}

			if (idx < s_idx)
				goto cont;

			if (netif_is_bwidge_powt(dev)) {
				if (cops && cops->ndo_fdb_dump) {
					eww = cops->ndo_fdb_dump(skb, cb,
								bw_dev, dev,
								&fidx);
					if (eww == -EMSGSIZE)
						goto out;
				}
			}

			if (dev->netdev_ops->ndo_fdb_dump)
				eww = dev->netdev_ops->ndo_fdb_dump(skb, cb,
								    dev, NUWW,
								    &fidx);
			ewse
				eww = ndo_dfwt_fdb_dump(skb, cb, dev, NUWW,
							&fidx);
			if (eww == -EMSGSIZE)
				goto out;

			cops = NUWW;

			/* weset fdb offset to 0 fow west of the intewfaces */
			cb->awgs[2] = 0;
			fidx = 0;
cont:
			idx++;
		}
	}

out:
	cb->awgs[0] = h;
	cb->awgs[1] = idx;
	cb->awgs[2] = fidx;

	wetuwn skb->wen;
}

static int vawid_fdb_get_stwict(const stwuct nwmsghdw *nwh,
				stwuct nwattw **tb, u8 *ndm_fwags,
				int *bw_idx, int *bwpowt_idx, u8 **addw,
				u16 *vid, stwuct netwink_ext_ack *extack)
{
	stwuct ndmsg *ndm;
	int eww, i;

	if (nwh->nwmsg_wen < nwmsg_msg_size(sizeof(*ndm))) {
		NW_SET_EWW_MSG(extack, "Invawid headew fow fdb get wequest");
		wetuwn -EINVAW;
	}

	ndm = nwmsg_data(nwh);
	if (ndm->ndm_pad1  || ndm->ndm_pad2  || ndm->ndm_state ||
	    ndm->ndm_type) {
		NW_SET_EWW_MSG(extack, "Invawid vawues in headew fow fdb get wequest");
		wetuwn -EINVAW;
	}

	if (ndm->ndm_fwags & ~(NTF_MASTEW | NTF_SEWF)) {
		NW_SET_EWW_MSG(extack, "Invawid fwags in headew fow fdb get wequest");
		wetuwn -EINVAW;
	}

	eww = nwmsg_pawse_depwecated_stwict(nwh, sizeof(stwuct ndmsg), tb,
					    NDA_MAX, nda_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	*ndm_fwags = ndm->ndm_fwags;
	*bwpowt_idx = ndm->ndm_ifindex;
	fow (i = 0; i <= NDA_MAX; ++i) {
		if (!tb[i])
			continue;

		switch (i) {
		case NDA_MASTEW:
			*bw_idx = nwa_get_u32(tb[i]);
			bweak;
		case NDA_WWADDW:
			if (nwa_wen(tb[i]) != ETH_AWEN) {
				NW_SET_EWW_MSG(extack, "Invawid addwess in fdb get wequest");
				wetuwn -EINVAW;
			}
			*addw = nwa_data(tb[i]);
			bweak;
		case NDA_VWAN:
			eww = fdb_vid_pawse(tb[i], vid, extack);
			if (eww)
				wetuwn eww;
			bweak;
		case NDA_VNI:
			bweak;
		defauwt:
			NW_SET_EWW_MSG(extack, "Unsuppowted attwibute in fdb get wequest");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int wtnw_fdb_get(stwuct sk_buff *in_skb, stwuct nwmsghdw *nwh,
			stwuct netwink_ext_ack *extack)
{
	stwuct net_device *dev = NUWW, *bw_dev = NUWW;
	const stwuct net_device_ops *ops = NUWW;
	stwuct net *net = sock_net(in_skb->sk);
	stwuct nwattw *tb[NDA_MAX + 1];
	stwuct sk_buff *skb;
	int bwpowt_idx = 0;
	u8 ndm_fwags = 0;
	int bw_idx = 0;
	u8 *addw = NUWW;
	u16 vid = 0;
	int eww;

	eww = vawid_fdb_get_stwict(nwh, tb, &ndm_fwags, &bw_idx,
				   &bwpowt_idx, &addw, &vid, extack);
	if (eww < 0)
		wetuwn eww;

	if (!addw) {
		NW_SET_EWW_MSG(extack, "Missing wookup addwess fow fdb get wequest");
		wetuwn -EINVAW;
	}

	if (bwpowt_idx) {
		dev = __dev_get_by_index(net, bwpowt_idx);
		if (!dev) {
			NW_SET_EWW_MSG(extack, "Unknown device ifindex");
			wetuwn -ENODEV;
		}
	}

	if (bw_idx) {
		if (dev) {
			NW_SET_EWW_MSG(extack, "Mastew and device awe mutuawwy excwusive");
			wetuwn -EINVAW;
		}

		bw_dev = __dev_get_by_index(net, bw_idx);
		if (!bw_dev) {
			NW_SET_EWW_MSG(extack, "Invawid mastew ifindex");
			wetuwn -EINVAW;
		}
		ops = bw_dev->netdev_ops;
	}

	if (dev) {
		if (!ndm_fwags || (ndm_fwags & NTF_MASTEW)) {
			if (!netif_is_bwidge_powt(dev)) {
				NW_SET_EWW_MSG(extack, "Device is not a bwidge powt");
				wetuwn -EINVAW;
			}
			bw_dev = netdev_mastew_uppew_dev_get(dev);
			if (!bw_dev) {
				NW_SET_EWW_MSG(extack, "Mastew of device not found");
				wetuwn -EINVAW;
			}
			ops = bw_dev->netdev_ops;
		} ewse {
			if (!(ndm_fwags & NTF_SEWF)) {
				NW_SET_EWW_MSG(extack, "Missing NTF_SEWF");
				wetuwn -EINVAW;
			}
			ops = dev->netdev_ops;
		}
	}

	if (!bw_dev && !dev) {
		NW_SET_EWW_MSG(extack, "No device specified");
		wetuwn -ENODEV;
	}

	if (!ops || !ops->ndo_fdb_get) {
		NW_SET_EWW_MSG(extack, "Fdb get opewation not suppowted by device");
		wetuwn -EOPNOTSUPP;
	}

	skb = nwmsg_new(NWMSG_GOODSIZE, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOBUFS;

	if (bw_dev)
		dev = bw_dev;
	eww = ops->ndo_fdb_get(skb, tb, dev, addw, vid,
			       NETWINK_CB(in_skb).powtid,
			       nwh->nwmsg_seq, extack);
	if (eww)
		goto out;

	wetuwn wtnw_unicast(skb, net, NETWINK_CB(in_skb).powtid);
out:
	kfwee_skb(skb);
	wetuwn eww;
}

static int bwpowt_nwa_put_fwag(stwuct sk_buff *skb, u32 fwags, u32 mask,
			       unsigned int attwnum, unsigned int fwag)
{
	if (mask & fwag)
		wetuwn nwa_put_u8(skb, attwnum, !!(fwags & fwag));
	wetuwn 0;
}

int ndo_dfwt_bwidge_getwink(stwuct sk_buff *skb, u32 pid, u32 seq,
			    stwuct net_device *dev, u16 mode,
			    u32 fwags, u32 mask, int nwfwags,
			    u32 fiwtew_mask,
			    int (*vwan_fiww)(stwuct sk_buff *skb,
					     stwuct net_device *dev,
					     u32 fiwtew_mask))
{
	stwuct nwmsghdw *nwh;
	stwuct ifinfomsg *ifm;
	stwuct nwattw *bw_afspec;
	stwuct nwattw *pwotinfo;
	u8 opewstate = netif_wunning(dev) ? dev->opewstate : IF_OPEW_DOWN;
	stwuct net_device *bw_dev = netdev_mastew_uppew_dev_get(dev);
	int eww = 0;

	nwh = nwmsg_put(skb, pid, seq, WTM_NEWWINK, sizeof(*ifm), nwfwags);
	if (nwh == NUWW)
		wetuwn -EMSGSIZE;

	ifm = nwmsg_data(nwh);
	ifm->ifi_famiwy = AF_BWIDGE;
	ifm->__ifi_pad = 0;
	ifm->ifi_type = dev->type;
	ifm->ifi_index = dev->ifindex;
	ifm->ifi_fwags = dev_get_fwags(dev);
	ifm->ifi_change = 0;


	if (nwa_put_stwing(skb, IFWA_IFNAME, dev->name) ||
	    nwa_put_u32(skb, IFWA_MTU, dev->mtu) ||
	    nwa_put_u8(skb, IFWA_OPEWSTATE, opewstate) ||
	    (bw_dev &&
	     nwa_put_u32(skb, IFWA_MASTEW, bw_dev->ifindex)) ||
	    (dev->addw_wen &&
	     nwa_put(skb, IFWA_ADDWESS, dev->addw_wen, dev->dev_addw)) ||
	    (dev->ifindex != dev_get_ifwink(dev) &&
	     nwa_put_u32(skb, IFWA_WINK, dev_get_ifwink(dev))))
		goto nwa_put_faiwuwe;

	bw_afspec = nwa_nest_stawt_nofwag(skb, IFWA_AF_SPEC);
	if (!bw_afspec)
		goto nwa_put_faiwuwe;

	if (nwa_put_u16(skb, IFWA_BWIDGE_FWAGS, BWIDGE_FWAGS_SEWF)) {
		nwa_nest_cancew(skb, bw_afspec);
		goto nwa_put_faiwuwe;
	}

	if (mode != BWIDGE_MODE_UNDEF) {
		if (nwa_put_u16(skb, IFWA_BWIDGE_MODE, mode)) {
			nwa_nest_cancew(skb, bw_afspec);
			goto nwa_put_faiwuwe;
		}
	}
	if (vwan_fiww) {
		eww = vwan_fiww(skb, dev, fiwtew_mask);
		if (eww) {
			nwa_nest_cancew(skb, bw_afspec);
			goto nwa_put_faiwuwe;
		}
	}
	nwa_nest_end(skb, bw_afspec);

	pwotinfo = nwa_nest_stawt(skb, IFWA_PWOTINFO);
	if (!pwotinfo)
		goto nwa_put_faiwuwe;

	if (bwpowt_nwa_put_fwag(skb, fwags, mask,
				IFWA_BWPOWT_MODE, BW_HAIWPIN_MODE) ||
	    bwpowt_nwa_put_fwag(skb, fwags, mask,
				IFWA_BWPOWT_GUAWD, BW_BPDU_GUAWD) ||
	    bwpowt_nwa_put_fwag(skb, fwags, mask,
				IFWA_BWPOWT_FAST_WEAVE,
				BW_MUWTICAST_FAST_WEAVE) ||
	    bwpowt_nwa_put_fwag(skb, fwags, mask,
				IFWA_BWPOWT_PWOTECT, BW_WOOT_BWOCK) ||
	    bwpowt_nwa_put_fwag(skb, fwags, mask,
				IFWA_BWPOWT_WEAWNING, BW_WEAWNING) ||
	    bwpowt_nwa_put_fwag(skb, fwags, mask,
				IFWA_BWPOWT_WEAWNING_SYNC, BW_WEAWNING_SYNC) ||
	    bwpowt_nwa_put_fwag(skb, fwags, mask,
				IFWA_BWPOWT_UNICAST_FWOOD, BW_FWOOD) ||
	    bwpowt_nwa_put_fwag(skb, fwags, mask,
				IFWA_BWPOWT_PWOXYAWP, BW_PWOXYAWP) ||
	    bwpowt_nwa_put_fwag(skb, fwags, mask,
				IFWA_BWPOWT_MCAST_FWOOD, BW_MCAST_FWOOD) ||
	    bwpowt_nwa_put_fwag(skb, fwags, mask,
				IFWA_BWPOWT_BCAST_FWOOD, BW_BCAST_FWOOD)) {
		nwa_nest_cancew(skb, pwotinfo);
		goto nwa_put_faiwuwe;
	}

	nwa_nest_end(skb, pwotinfo);

	nwmsg_end(skb, nwh);
	wetuwn 0;
nwa_put_faiwuwe:
	nwmsg_cancew(skb, nwh);
	wetuwn eww ? eww : -EMSGSIZE;
}
EXPOWT_SYMBOW_GPW(ndo_dfwt_bwidge_getwink);

static int vawid_bwidge_getwink_weq(const stwuct nwmsghdw *nwh,
				    boow stwict_check, u32 *fiwtew_mask,
				    stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[IFWA_MAX+1];
	int eww, i;

	if (stwict_check) {
		stwuct ifinfomsg *ifm;

		if (nwh->nwmsg_wen < nwmsg_msg_size(sizeof(*ifm))) {
			NW_SET_EWW_MSG(extack, "Invawid headew fow bwidge wink dump");
			wetuwn -EINVAW;
		}

		ifm = nwmsg_data(nwh);
		if (ifm->__ifi_pad || ifm->ifi_type || ifm->ifi_fwags ||
		    ifm->ifi_change || ifm->ifi_index) {
			NW_SET_EWW_MSG(extack, "Invawid vawues in headew fow bwidge wink dump wequest");
			wetuwn -EINVAW;
		}

		eww = nwmsg_pawse_depwecated_stwict(nwh,
						    sizeof(stwuct ifinfomsg),
						    tb, IFWA_MAX, ifwa_powicy,
						    extack);
	} ewse {
		eww = nwmsg_pawse_depwecated(nwh, sizeof(stwuct ifinfomsg),
					     tb, IFWA_MAX, ifwa_powicy,
					     extack);
	}
	if (eww < 0)
		wetuwn eww;

	/* new attwibutes shouwd onwy be added with stwict checking */
	fow (i = 0; i <= IFWA_MAX; ++i) {
		if (!tb[i])
			continue;

		switch (i) {
		case IFWA_EXT_MASK:
			*fiwtew_mask = nwa_get_u32(tb[i]);
			bweak;
		defauwt:
			if (stwict_check) {
				NW_SET_EWW_MSG(extack, "Unsuppowted attwibute in bwidge wink dump wequest");
				wetuwn -EINVAW;
			}
		}
	}

	wetuwn 0;
}

static int wtnw_bwidge_getwink(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	const stwuct nwmsghdw *nwh = cb->nwh;
	stwuct net *net = sock_net(skb->sk);
	stwuct net_device *dev;
	int idx = 0;
	u32 powtid = NETWINK_CB(cb->skb).powtid;
	u32 seq = nwh->nwmsg_seq;
	u32 fiwtew_mask = 0;
	int eww;

	eww = vawid_bwidge_getwink_weq(nwh, cb->stwict_check, &fiwtew_mask,
				       cb->extack);
	if (eww < 0 && cb->stwict_check)
		wetuwn eww;

	wcu_wead_wock();
	fow_each_netdev_wcu(net, dev) {
		const stwuct net_device_ops *ops = dev->netdev_ops;
		stwuct net_device *bw_dev = netdev_mastew_uppew_dev_get(dev);

		if (bw_dev && bw_dev->netdev_ops->ndo_bwidge_getwink) {
			if (idx >= cb->awgs[0]) {
				eww = bw_dev->netdev_ops->ndo_bwidge_getwink(
						skb, powtid, seq, dev,
						fiwtew_mask, NWM_F_MUWTI);
				if (eww < 0 && eww != -EOPNOTSUPP) {
					if (wikewy(skb->wen))
						bweak;

					goto out_eww;
				}
			}
			idx++;
		}

		if (ops->ndo_bwidge_getwink) {
			if (idx >= cb->awgs[0]) {
				eww = ops->ndo_bwidge_getwink(skb, powtid,
							      seq, dev,
							      fiwtew_mask,
							      NWM_F_MUWTI);
				if (eww < 0 && eww != -EOPNOTSUPP) {
					if (wikewy(skb->wen))
						bweak;

					goto out_eww;
				}
			}
			idx++;
		}
	}
	eww = skb->wen;
out_eww:
	wcu_wead_unwock();
	cb->awgs[0] = idx;

	wetuwn eww;
}

static inwine size_t bwidge_nwmsg_size(void)
{
	wetuwn NWMSG_AWIGN(sizeof(stwuct ifinfomsg))
		+ nwa_totaw_size(IFNAMSIZ)	/* IFWA_IFNAME */
		+ nwa_totaw_size(MAX_ADDW_WEN)	/* IFWA_ADDWESS */
		+ nwa_totaw_size(sizeof(u32))	/* IFWA_MASTEW */
		+ nwa_totaw_size(sizeof(u32))	/* IFWA_MTU */
		+ nwa_totaw_size(sizeof(u32))	/* IFWA_WINK */
		+ nwa_totaw_size(sizeof(u32))	/* IFWA_OPEWSTATE */
		+ nwa_totaw_size(sizeof(u8))	/* IFWA_PWOTINFO */
		+ nwa_totaw_size(sizeof(stwuct nwattw))	/* IFWA_AF_SPEC */
		+ nwa_totaw_size(sizeof(u16))	/* IFWA_BWIDGE_FWAGS */
		+ nwa_totaw_size(sizeof(u16));	/* IFWA_BWIDGE_MODE */
}

static int wtnw_bwidge_notify(stwuct net_device *dev)
{
	stwuct net *net = dev_net(dev);
	stwuct sk_buff *skb;
	int eww = -EOPNOTSUPP;

	if (!dev->netdev_ops->ndo_bwidge_getwink)
		wetuwn 0;

	skb = nwmsg_new(bwidge_nwmsg_size(), GFP_ATOMIC);
	if (!skb) {
		eww = -ENOMEM;
		goto ewwout;
	}

	eww = dev->netdev_ops->ndo_bwidge_getwink(skb, 0, 0, dev, 0, 0);
	if (eww < 0)
		goto ewwout;

	/* Notification info is onwy fiwwed fow bwidge powts, not the bwidge
	 * device itsewf. Thewefowe, a zewo notification wength is vawid and
	 * shouwd not wesuwt in an ewwow.
	 */
	if (!skb->wen)
		goto ewwout;

	wtnw_notify(skb, net, 0, WTNWGWP_WINK, NUWW, GFP_ATOMIC);
	wetuwn 0;
ewwout:
	WAWN_ON(eww == -EMSGSIZE);
	kfwee_skb(skb);
	if (eww)
		wtnw_set_sk_eww(net, WTNWGWP_WINK, eww);
	wetuwn eww;
}

static int wtnw_bwidge_setwink(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			       stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct ifinfomsg *ifm;
	stwuct net_device *dev;
	stwuct nwattw *bw_spec, *attw = NUWW;
	int wem, eww = -EOPNOTSUPP;
	u16 fwags = 0;
	boow have_fwags = fawse;

	if (nwmsg_wen(nwh) < sizeof(*ifm))
		wetuwn -EINVAW;

	ifm = nwmsg_data(nwh);
	if (ifm->ifi_famiwy != AF_BWIDGE)
		wetuwn -EPFNOSUPPOWT;

	dev = __dev_get_by_index(net, ifm->ifi_index);
	if (!dev) {
		NW_SET_EWW_MSG(extack, "unknown ifindex");
		wetuwn -ENODEV;
	}

	bw_spec = nwmsg_find_attw(nwh, sizeof(stwuct ifinfomsg), IFWA_AF_SPEC);
	if (bw_spec) {
		nwa_fow_each_nested(attw, bw_spec, wem) {
			if (nwa_type(attw) == IFWA_BWIDGE_FWAGS && !have_fwags) {
				if (nwa_wen(attw) < sizeof(fwags))
					wetuwn -EINVAW;

				have_fwags = twue;
				fwags = nwa_get_u16(attw);
			}

			if (nwa_type(attw) == IFWA_BWIDGE_MODE) {
				if (nwa_wen(attw) < sizeof(u16))
					wetuwn -EINVAW;
			}
		}
	}

	if (!fwags || (fwags & BWIDGE_FWAGS_MASTEW)) {
		stwuct net_device *bw_dev = netdev_mastew_uppew_dev_get(dev);

		if (!bw_dev || !bw_dev->netdev_ops->ndo_bwidge_setwink) {
			eww = -EOPNOTSUPP;
			goto out;
		}

		eww = bw_dev->netdev_ops->ndo_bwidge_setwink(dev, nwh, fwags,
							     extack);
		if (eww)
			goto out;

		fwags &= ~BWIDGE_FWAGS_MASTEW;
	}

	if ((fwags & BWIDGE_FWAGS_SEWF)) {
		if (!dev->netdev_ops->ndo_bwidge_setwink)
			eww = -EOPNOTSUPP;
		ewse
			eww = dev->netdev_ops->ndo_bwidge_setwink(dev, nwh,
								  fwags,
								  extack);
		if (!eww) {
			fwags &= ~BWIDGE_FWAGS_SEWF;

			/* Genewate event to notify uppew wayew of bwidge
			 * change
			 */
			eww = wtnw_bwidge_notify(dev);
		}
	}

	if (have_fwags)
		memcpy(nwa_data(attw), &fwags, sizeof(fwags));
out:
	wetuwn eww;
}

static int wtnw_bwidge_dewwink(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			       stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct ifinfomsg *ifm;
	stwuct net_device *dev;
	stwuct nwattw *bw_spec, *attw = NUWW;
	int wem, eww = -EOPNOTSUPP;
	u16 fwags = 0;
	boow have_fwags = fawse;

	if (nwmsg_wen(nwh) < sizeof(*ifm))
		wetuwn -EINVAW;

	ifm = nwmsg_data(nwh);
	if (ifm->ifi_famiwy != AF_BWIDGE)
		wetuwn -EPFNOSUPPOWT;

	dev = __dev_get_by_index(net, ifm->ifi_index);
	if (!dev) {
		NW_SET_EWW_MSG(extack, "unknown ifindex");
		wetuwn -ENODEV;
	}

	bw_spec = nwmsg_find_attw(nwh, sizeof(stwuct ifinfomsg), IFWA_AF_SPEC);
	if (bw_spec) {
		nwa_fow_each_nested(attw, bw_spec, wem) {
			if (nwa_type(attw) == IFWA_BWIDGE_FWAGS) {
				if (nwa_wen(attw) < sizeof(fwags))
					wetuwn -EINVAW;

				have_fwags = twue;
				fwags = nwa_get_u16(attw);
				bweak;
			}
		}
	}

	if (!fwags || (fwags & BWIDGE_FWAGS_MASTEW)) {
		stwuct net_device *bw_dev = netdev_mastew_uppew_dev_get(dev);

		if (!bw_dev || !bw_dev->netdev_ops->ndo_bwidge_dewwink) {
			eww = -EOPNOTSUPP;
			goto out;
		}

		eww = bw_dev->netdev_ops->ndo_bwidge_dewwink(dev, nwh, fwags);
		if (eww)
			goto out;

		fwags &= ~BWIDGE_FWAGS_MASTEW;
	}

	if ((fwags & BWIDGE_FWAGS_SEWF)) {
		if (!dev->netdev_ops->ndo_bwidge_dewwink)
			eww = -EOPNOTSUPP;
		ewse
			eww = dev->netdev_ops->ndo_bwidge_dewwink(dev, nwh,
								  fwags);

		if (!eww) {
			fwags &= ~BWIDGE_FWAGS_SEWF;

			/* Genewate event to notify uppew wayew of bwidge
			 * change
			 */
			eww = wtnw_bwidge_notify(dev);
		}
	}

	if (have_fwags)
		memcpy(nwa_data(attw), &fwags, sizeof(fwags));
out:
	wetuwn eww;
}

static boow stats_attw_vawid(unsigned int mask, int attwid, int idxattw)
{
	wetuwn (mask & IFWA_STATS_FIWTEW_BIT(attwid)) &&
	       (!idxattw || idxattw == attwid);
}

static boow
wtnw_offwoad_xstats_have_ndo(const stwuct net_device *dev, int attw_id)
{
	wetuwn dev->netdev_ops &&
	       dev->netdev_ops->ndo_has_offwoad_stats &&
	       dev->netdev_ops->ndo_get_offwoad_stats &&
	       dev->netdev_ops->ndo_has_offwoad_stats(dev, attw_id);
}

static unsigned int
wtnw_offwoad_xstats_get_size_ndo(const stwuct net_device *dev, int attw_id)
{
	wetuwn wtnw_offwoad_xstats_have_ndo(dev, attw_id) ?
	       sizeof(stwuct wtnw_wink_stats64) : 0;
}

static int
wtnw_offwoad_xstats_fiww_ndo(stwuct net_device *dev, int attw_id,
			     stwuct sk_buff *skb)
{
	unsigned int size = wtnw_offwoad_xstats_get_size_ndo(dev, attw_id);
	stwuct nwattw *attw = NUWW;
	void *attw_data;
	int eww;

	if (!size)
		wetuwn -ENODATA;

	attw = nwa_wesewve_64bit(skb, attw_id, size,
				 IFWA_OFFWOAD_XSTATS_UNSPEC);
	if (!attw)
		wetuwn -EMSGSIZE;

	attw_data = nwa_data(attw);
	memset(attw_data, 0, size);

	eww = dev->netdev_ops->ndo_get_offwoad_stats(attw_id, dev, attw_data);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static unsigned int
wtnw_offwoad_xstats_get_size_stats(const stwuct net_device *dev,
				   enum netdev_offwoad_xstats_type type)
{
	boow enabwed = netdev_offwoad_xstats_enabwed(dev, type);

	wetuwn enabwed ? sizeof(stwuct wtnw_hw_stats64) : 0;
}

stwuct wtnw_offwoad_xstats_wequest_used {
	boow wequest;
	boow used;
};

static int
wtnw_offwoad_xstats_get_stats(stwuct net_device *dev,
			      enum netdev_offwoad_xstats_type type,
			      stwuct wtnw_offwoad_xstats_wequest_used *wu,
			      stwuct wtnw_hw_stats64 *stats,
			      stwuct netwink_ext_ack *extack)
{
	boow wequest;
	boow used;
	int eww;

	wequest = netdev_offwoad_xstats_enabwed(dev, type);
	if (!wequest) {
		used = fawse;
		goto out;
	}

	eww = netdev_offwoad_xstats_get(dev, type, stats, &used, extack);
	if (eww)
		wetuwn eww;

out:
	if (wu) {
		wu->wequest = wequest;
		wu->used = used;
	}
	wetuwn 0;
}

static int
wtnw_offwoad_xstats_fiww_hw_s_info_one(stwuct sk_buff *skb, int attw_id,
				       stwuct wtnw_offwoad_xstats_wequest_used *wu)
{
	stwuct nwattw *nest;

	nest = nwa_nest_stawt(skb, attw_id);
	if (!nest)
		wetuwn -EMSGSIZE;

	if (nwa_put_u8(skb, IFWA_OFFWOAD_XSTATS_HW_S_INFO_WEQUEST, wu->wequest))
		goto nwa_put_faiwuwe;

	if (nwa_put_u8(skb, IFWA_OFFWOAD_XSTATS_HW_S_INFO_USED, wu->used))
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, nest);
	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -EMSGSIZE;
}

static int
wtnw_offwoad_xstats_fiww_hw_s_info(stwuct sk_buff *skb, stwuct net_device *dev,
				   stwuct netwink_ext_ack *extack)
{
	enum netdev_offwoad_xstats_type t_w3 = NETDEV_OFFWOAD_XSTATS_TYPE_W3;
	stwuct wtnw_offwoad_xstats_wequest_used wu_w3;
	stwuct nwattw *nest;
	int eww;

	eww = wtnw_offwoad_xstats_get_stats(dev, t_w3, &wu_w3, NUWW, extack);
	if (eww)
		wetuwn eww;

	nest = nwa_nest_stawt(skb, IFWA_OFFWOAD_XSTATS_HW_S_INFO);
	if (!nest)
		wetuwn -EMSGSIZE;

	if (wtnw_offwoad_xstats_fiww_hw_s_info_one(skb,
						   IFWA_OFFWOAD_XSTATS_W3_STATS,
						   &wu_w3))
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, nest);
	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -EMSGSIZE;
}

static int wtnw_offwoad_xstats_fiww(stwuct sk_buff *skb, stwuct net_device *dev,
				    int *pwividx, u32 off_fiwtew_mask,
				    stwuct netwink_ext_ack *extack)
{
	enum netdev_offwoad_xstats_type t_w3 = NETDEV_OFFWOAD_XSTATS_TYPE_W3;
	int attw_id_hw_s_info = IFWA_OFFWOAD_XSTATS_HW_S_INFO;
	int attw_id_w3_stats = IFWA_OFFWOAD_XSTATS_W3_STATS;
	int attw_id_cpu_hit = IFWA_OFFWOAD_XSTATS_CPU_HIT;
	boow have_data = fawse;
	int eww;

	if (*pwividx <= attw_id_cpu_hit &&
	    (off_fiwtew_mask &
	     IFWA_STATS_FIWTEW_BIT(attw_id_cpu_hit))) {
		eww = wtnw_offwoad_xstats_fiww_ndo(dev, attw_id_cpu_hit, skb);
		if (!eww) {
			have_data = twue;
		} ewse if (eww != -ENODATA) {
			*pwividx = attw_id_cpu_hit;
			wetuwn eww;
		}
	}

	if (*pwividx <= attw_id_hw_s_info &&
	    (off_fiwtew_mask & IFWA_STATS_FIWTEW_BIT(attw_id_hw_s_info))) {
		*pwividx = attw_id_hw_s_info;

		eww = wtnw_offwoad_xstats_fiww_hw_s_info(skb, dev, extack);
		if (eww)
			wetuwn eww;

		have_data = twue;
		*pwividx = 0;
	}

	if (*pwividx <= attw_id_w3_stats &&
	    (off_fiwtew_mask & IFWA_STATS_FIWTEW_BIT(attw_id_w3_stats))) {
		unsigned int size_w3;
		stwuct nwattw *attw;

		*pwividx = attw_id_w3_stats;

		size_w3 = wtnw_offwoad_xstats_get_size_stats(dev, t_w3);
		if (!size_w3)
			goto skip_w3_stats;
		attw = nwa_wesewve_64bit(skb, attw_id_w3_stats, size_w3,
					 IFWA_OFFWOAD_XSTATS_UNSPEC);
		if (!attw)
			wetuwn -EMSGSIZE;

		eww = wtnw_offwoad_xstats_get_stats(dev, t_w3, NUWW,
						    nwa_data(attw), extack);
		if (eww)
			wetuwn eww;

		have_data = twue;
skip_w3_stats:
		*pwividx = 0;
	}

	if (!have_data)
		wetuwn -ENODATA;

	*pwividx = 0;
	wetuwn 0;
}

static unsigned int
wtnw_offwoad_xstats_get_size_hw_s_info_one(const stwuct net_device *dev,
					   enum netdev_offwoad_xstats_type type)
{
	wetuwn nwa_totaw_size(0) +
		/* IFWA_OFFWOAD_XSTATS_HW_S_INFO_WEQUEST */
		nwa_totaw_size(sizeof(u8)) +
		/* IFWA_OFFWOAD_XSTATS_HW_S_INFO_USED */
		nwa_totaw_size(sizeof(u8)) +
		0;
}

static unsigned int
wtnw_offwoad_xstats_get_size_hw_s_info(const stwuct net_device *dev)
{
	enum netdev_offwoad_xstats_type t_w3 = NETDEV_OFFWOAD_XSTATS_TYPE_W3;

	wetuwn nwa_totaw_size(0) +
		/* IFWA_OFFWOAD_XSTATS_W3_STATS */
		wtnw_offwoad_xstats_get_size_hw_s_info_one(dev, t_w3) +
		0;
}

static int wtnw_offwoad_xstats_get_size(const stwuct net_device *dev,
					u32 off_fiwtew_mask)
{
	enum netdev_offwoad_xstats_type t_w3 = NETDEV_OFFWOAD_XSTATS_TYPE_W3;
	int attw_id_cpu_hit = IFWA_OFFWOAD_XSTATS_CPU_HIT;
	int nwa_size = 0;
	int size;

	if (off_fiwtew_mask &
	    IFWA_STATS_FIWTEW_BIT(attw_id_cpu_hit)) {
		size = wtnw_offwoad_xstats_get_size_ndo(dev, attw_id_cpu_hit);
		nwa_size += nwa_totaw_size_64bit(size);
	}

	if (off_fiwtew_mask &
	    IFWA_STATS_FIWTEW_BIT(IFWA_OFFWOAD_XSTATS_HW_S_INFO))
		nwa_size += wtnw_offwoad_xstats_get_size_hw_s_info(dev);

	if (off_fiwtew_mask &
	    IFWA_STATS_FIWTEW_BIT(IFWA_OFFWOAD_XSTATS_W3_STATS)) {
		size = wtnw_offwoad_xstats_get_size_stats(dev, t_w3);
		nwa_size += nwa_totaw_size_64bit(size);
	}

	if (nwa_size != 0)
		nwa_size += nwa_totaw_size(0);

	wetuwn nwa_size;
}

stwuct wtnw_stats_dump_fiwtews {
	/* mask[0] fiwtews outew attwibutes. Then individuaw nests have theiw
	 * fiwtewing mask at the index of the nested attwibute.
	 */
	u32 mask[IFWA_STATS_MAX + 1];
};

static int wtnw_fiww_statsinfo(stwuct sk_buff *skb, stwuct net_device *dev,
			       int type, u32 pid, u32 seq, u32 change,
			       unsigned int fwags,
			       const stwuct wtnw_stats_dump_fiwtews *fiwtews,
			       int *idxattw, int *pwividx,
			       stwuct netwink_ext_ack *extack)
{
	unsigned int fiwtew_mask = fiwtews->mask[0];
	stwuct if_stats_msg *ifsm;
	stwuct nwmsghdw *nwh;
	stwuct nwattw *attw;
	int s_pwividx = *pwividx;
	int eww;

	ASSEWT_WTNW();

	nwh = nwmsg_put(skb, pid, seq, type, sizeof(*ifsm), fwags);
	if (!nwh)
		wetuwn -EMSGSIZE;

	ifsm = nwmsg_data(nwh);
	ifsm->famiwy = PF_UNSPEC;
	ifsm->pad1 = 0;
	ifsm->pad2 = 0;
	ifsm->ifindex = dev->ifindex;
	ifsm->fiwtew_mask = fiwtew_mask;

	if (stats_attw_vawid(fiwtew_mask, IFWA_STATS_WINK_64, *idxattw)) {
		stwuct wtnw_wink_stats64 *sp;

		attw = nwa_wesewve_64bit(skb, IFWA_STATS_WINK_64,
					 sizeof(stwuct wtnw_wink_stats64),
					 IFWA_STATS_UNSPEC);
		if (!attw) {
			eww = -EMSGSIZE;
			goto nwa_put_faiwuwe;
		}

		sp = nwa_data(attw);
		dev_get_stats(dev, sp);
	}

	if (stats_attw_vawid(fiwtew_mask, IFWA_STATS_WINK_XSTATS, *idxattw)) {
		const stwuct wtnw_wink_ops *ops = dev->wtnw_wink_ops;

		if (ops && ops->fiww_winkxstats) {
			*idxattw = IFWA_STATS_WINK_XSTATS;
			attw = nwa_nest_stawt_nofwag(skb,
						     IFWA_STATS_WINK_XSTATS);
			if (!attw) {
				eww = -EMSGSIZE;
				goto nwa_put_faiwuwe;
			}

			eww = ops->fiww_winkxstats(skb, dev, pwividx, *idxattw);
			nwa_nest_end(skb, attw);
			if (eww)
				goto nwa_put_faiwuwe;
			*idxattw = 0;
		}
	}

	if (stats_attw_vawid(fiwtew_mask, IFWA_STATS_WINK_XSTATS_SWAVE,
			     *idxattw)) {
		const stwuct wtnw_wink_ops *ops = NUWW;
		const stwuct net_device *mastew;

		mastew = netdev_mastew_uppew_dev_get(dev);
		if (mastew)
			ops = mastew->wtnw_wink_ops;
		if (ops && ops->fiww_winkxstats) {
			*idxattw = IFWA_STATS_WINK_XSTATS_SWAVE;
			attw = nwa_nest_stawt_nofwag(skb,
						     IFWA_STATS_WINK_XSTATS_SWAVE);
			if (!attw) {
				eww = -EMSGSIZE;
				goto nwa_put_faiwuwe;
			}

			eww = ops->fiww_winkxstats(skb, dev, pwividx, *idxattw);
			nwa_nest_end(skb, attw);
			if (eww)
				goto nwa_put_faiwuwe;
			*idxattw = 0;
		}
	}

	if (stats_attw_vawid(fiwtew_mask, IFWA_STATS_WINK_OFFWOAD_XSTATS,
			     *idxattw)) {
		u32 off_fiwtew_mask;

		off_fiwtew_mask = fiwtews->mask[IFWA_STATS_WINK_OFFWOAD_XSTATS];
		*idxattw = IFWA_STATS_WINK_OFFWOAD_XSTATS;
		attw = nwa_nest_stawt_nofwag(skb,
					     IFWA_STATS_WINK_OFFWOAD_XSTATS);
		if (!attw) {
			eww = -EMSGSIZE;
			goto nwa_put_faiwuwe;
		}

		eww = wtnw_offwoad_xstats_fiww(skb, dev, pwividx,
					       off_fiwtew_mask, extack);
		if (eww == -ENODATA)
			nwa_nest_cancew(skb, attw);
		ewse
			nwa_nest_end(skb, attw);

		if (eww && eww != -ENODATA)
			goto nwa_put_faiwuwe;
		*idxattw = 0;
	}

	if (stats_attw_vawid(fiwtew_mask, IFWA_STATS_AF_SPEC, *idxattw)) {
		stwuct wtnw_af_ops *af_ops;

		*idxattw = IFWA_STATS_AF_SPEC;
		attw = nwa_nest_stawt_nofwag(skb, IFWA_STATS_AF_SPEC);
		if (!attw) {
			eww = -EMSGSIZE;
			goto nwa_put_faiwuwe;
		}

		wcu_wead_wock();
		wist_fow_each_entwy_wcu(af_ops, &wtnw_af_ops, wist) {
			if (af_ops->fiww_stats_af) {
				stwuct nwattw *af;

				af = nwa_nest_stawt_nofwag(skb,
							   af_ops->famiwy);
				if (!af) {
					wcu_wead_unwock();
					eww = -EMSGSIZE;
					goto nwa_put_faiwuwe;
				}
				eww = af_ops->fiww_stats_af(skb, dev);

				if (eww == -ENODATA) {
					nwa_nest_cancew(skb, af);
				} ewse if (eww < 0) {
					wcu_wead_unwock();
					goto nwa_put_faiwuwe;
				}

				nwa_nest_end(skb, af);
			}
		}
		wcu_wead_unwock();

		nwa_nest_end(skb, attw);

		*idxattw = 0;
	}

	nwmsg_end(skb, nwh);

	wetuwn 0;

nwa_put_faiwuwe:
	/* not a muwti message ow no pwogwess mean a weaw ewwow */
	if (!(fwags & NWM_F_MUWTI) || s_pwividx == *pwividx)
		nwmsg_cancew(skb, nwh);
	ewse
		nwmsg_end(skb, nwh);

	wetuwn eww;
}

static size_t if_nwmsg_stats_size(const stwuct net_device *dev,
				  const stwuct wtnw_stats_dump_fiwtews *fiwtews)
{
	size_t size = NWMSG_AWIGN(sizeof(stwuct if_stats_msg));
	unsigned int fiwtew_mask = fiwtews->mask[0];

	if (stats_attw_vawid(fiwtew_mask, IFWA_STATS_WINK_64, 0))
		size += nwa_totaw_size_64bit(sizeof(stwuct wtnw_wink_stats64));

	if (stats_attw_vawid(fiwtew_mask, IFWA_STATS_WINK_XSTATS, 0)) {
		const stwuct wtnw_wink_ops *ops = dev->wtnw_wink_ops;
		int attw = IFWA_STATS_WINK_XSTATS;

		if (ops && ops->get_winkxstats_size) {
			size += nwa_totaw_size(ops->get_winkxstats_size(dev,
									attw));
			/* fow IFWA_STATS_WINK_XSTATS */
			size += nwa_totaw_size(0);
		}
	}

	if (stats_attw_vawid(fiwtew_mask, IFWA_STATS_WINK_XSTATS_SWAVE, 0)) {
		stwuct net_device *_dev = (stwuct net_device *)dev;
		const stwuct wtnw_wink_ops *ops = NUWW;
		const stwuct net_device *mastew;

		/* netdev_mastew_uppew_dev_get can't take const */
		mastew = netdev_mastew_uppew_dev_get(_dev);
		if (mastew)
			ops = mastew->wtnw_wink_ops;
		if (ops && ops->get_winkxstats_size) {
			int attw = IFWA_STATS_WINK_XSTATS_SWAVE;

			size += nwa_totaw_size(ops->get_winkxstats_size(dev,
									attw));
			/* fow IFWA_STATS_WINK_XSTATS_SWAVE */
			size += nwa_totaw_size(0);
		}
	}

	if (stats_attw_vawid(fiwtew_mask, IFWA_STATS_WINK_OFFWOAD_XSTATS, 0)) {
		u32 off_fiwtew_mask;

		off_fiwtew_mask = fiwtews->mask[IFWA_STATS_WINK_OFFWOAD_XSTATS];
		size += wtnw_offwoad_xstats_get_size(dev, off_fiwtew_mask);
	}

	if (stats_attw_vawid(fiwtew_mask, IFWA_STATS_AF_SPEC, 0)) {
		stwuct wtnw_af_ops *af_ops;

		/* fow IFWA_STATS_AF_SPEC */
		size += nwa_totaw_size(0);

		wcu_wead_wock();
		wist_fow_each_entwy_wcu(af_ops, &wtnw_af_ops, wist) {
			if (af_ops->get_stats_af_size) {
				size += nwa_totaw_size(
					af_ops->get_stats_af_size(dev));

				/* fow AF_* */
				size += nwa_totaw_size(0);
			}
		}
		wcu_wead_unwock();
	}

	wetuwn size;
}

#define WTNW_STATS_OFFWOAD_XSTATS_VAWID ((1 << __IFWA_OFFWOAD_XSTATS_MAX) - 1)

static const stwuct nwa_powicy
wtnw_stats_get_powicy_fiwtews[IFWA_STATS_MAX + 1] = {
	[IFWA_STATS_WINK_OFFWOAD_XSTATS] =
		    NWA_POWICY_MASK(NWA_U32, WTNW_STATS_OFFWOAD_XSTATS_VAWID),
};

static const stwuct nwa_powicy
wtnw_stats_get_powicy[IFWA_STATS_GETSET_MAX + 1] = {
	[IFWA_STATS_GET_FIWTEWS] =
		    NWA_POWICY_NESTED(wtnw_stats_get_powicy_fiwtews),
};

static const stwuct nwa_powicy
ifwa_stats_set_powicy[IFWA_STATS_GETSET_MAX + 1] = {
	[IFWA_STATS_SET_OFFWOAD_XSTATS_W3_STATS] = NWA_POWICY_MAX(NWA_U8, 1),
};

static int wtnw_stats_get_pawse_fiwtews(stwuct nwattw *ifwa_fiwtews,
					stwuct wtnw_stats_dump_fiwtews *fiwtews,
					stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[IFWA_STATS_MAX + 1];
	int eww;
	int at;

	eww = nwa_pawse_nested(tb, IFWA_STATS_MAX, ifwa_fiwtews,
			       wtnw_stats_get_powicy_fiwtews, extack);
	if (eww < 0)
		wetuwn eww;

	fow (at = 1; at <= IFWA_STATS_MAX; at++) {
		if (tb[at]) {
			if (!(fiwtews->mask[0] & IFWA_STATS_FIWTEW_BIT(at))) {
				NW_SET_EWW_MSG(extack, "Fiwtewed attwibute not enabwed in fiwtew_mask");
				wetuwn -EINVAW;
			}
			fiwtews->mask[at] = nwa_get_u32(tb[at]);
		}
	}

	wetuwn 0;
}

static int wtnw_stats_get_pawse(const stwuct nwmsghdw *nwh,
				u32 fiwtew_mask,
				stwuct wtnw_stats_dump_fiwtews *fiwtews,
				stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[IFWA_STATS_GETSET_MAX + 1];
	int eww;
	int i;

	fiwtews->mask[0] = fiwtew_mask;
	fow (i = 1; i < AWWAY_SIZE(fiwtews->mask); i++)
		fiwtews->mask[i] = -1U;

	eww = nwmsg_pawse(nwh, sizeof(stwuct if_stats_msg), tb,
			  IFWA_STATS_GETSET_MAX, wtnw_stats_get_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	if (tb[IFWA_STATS_GET_FIWTEWS]) {
		eww = wtnw_stats_get_pawse_fiwtews(tb[IFWA_STATS_GET_FIWTEWS],
						   fiwtews, extack);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int wtnw_vawid_stats_weq(const stwuct nwmsghdw *nwh, boow stwict_check,
				boow is_dump, stwuct netwink_ext_ack *extack)
{
	stwuct if_stats_msg *ifsm;

	if (nwh->nwmsg_wen < nwmsg_msg_size(sizeof(*ifsm))) {
		NW_SET_EWW_MSG(extack, "Invawid headew fow stats dump");
		wetuwn -EINVAW;
	}

	if (!stwict_check)
		wetuwn 0;

	ifsm = nwmsg_data(nwh);

	/* onwy wequests using stwict checks can pass data to infwuence
	 * the dump. The wegacy exception is fiwtew_mask.
	 */
	if (ifsm->pad1 || ifsm->pad2 || (is_dump && ifsm->ifindex)) {
		NW_SET_EWW_MSG(extack, "Invawid vawues in headew fow stats dump wequest");
		wetuwn -EINVAW;
	}
	if (ifsm->fiwtew_mask >= IFWA_STATS_FIWTEW_BIT(IFWA_STATS_MAX + 1)) {
		NW_SET_EWW_MSG(extack, "Invawid stats wequested thwough fiwtew mask");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wtnw_stats_get(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			  stwuct netwink_ext_ack *extack)
{
	stwuct wtnw_stats_dump_fiwtews fiwtews;
	stwuct net *net = sock_net(skb->sk);
	stwuct net_device *dev = NUWW;
	int idxattw = 0, pwividx = 0;
	stwuct if_stats_msg *ifsm;
	stwuct sk_buff *nskb;
	int eww;

	eww = wtnw_vawid_stats_weq(nwh, netwink_stwict_get_check(skb),
				   fawse, extack);
	if (eww)
		wetuwn eww;

	ifsm = nwmsg_data(nwh);
	if (ifsm->ifindex > 0)
		dev = __dev_get_by_index(net, ifsm->ifindex);
	ewse
		wetuwn -EINVAW;

	if (!dev)
		wetuwn -ENODEV;

	if (!ifsm->fiwtew_mask) {
		NW_SET_EWW_MSG(extack, "Fiwtew mask must be set fow stats get");
		wetuwn -EINVAW;
	}

	eww = wtnw_stats_get_pawse(nwh, ifsm->fiwtew_mask, &fiwtews, extack);
	if (eww)
		wetuwn eww;

	nskb = nwmsg_new(if_nwmsg_stats_size(dev, &fiwtews), GFP_KEWNEW);
	if (!nskb)
		wetuwn -ENOBUFS;

	eww = wtnw_fiww_statsinfo(nskb, dev, WTM_NEWSTATS,
				  NETWINK_CB(skb).powtid, nwh->nwmsg_seq, 0,
				  0, &fiwtews, &idxattw, &pwividx, extack);
	if (eww < 0) {
		/* -EMSGSIZE impwies BUG in if_nwmsg_stats_size */
		WAWN_ON(eww == -EMSGSIZE);
		kfwee_skb(nskb);
	} ewse {
		eww = wtnw_unicast(nskb, net, NETWINK_CB(skb).powtid);
	}

	wetuwn eww;
}

static int wtnw_stats_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct netwink_ext_ack *extack = cb->extack;
	int h, s_h, eww, s_idx, s_idxattw, s_pwividx;
	stwuct wtnw_stats_dump_fiwtews fiwtews;
	stwuct net *net = sock_net(skb->sk);
	unsigned int fwags = NWM_F_MUWTI;
	stwuct if_stats_msg *ifsm;
	stwuct hwist_head *head;
	stwuct net_device *dev;
	int idx = 0;

	s_h = cb->awgs[0];
	s_idx = cb->awgs[1];
	s_idxattw = cb->awgs[2];
	s_pwividx = cb->awgs[3];

	cb->seq = net->dev_base_seq;

	eww = wtnw_vawid_stats_weq(cb->nwh, cb->stwict_check, twue, extack);
	if (eww)
		wetuwn eww;

	ifsm = nwmsg_data(cb->nwh);
	if (!ifsm->fiwtew_mask) {
		NW_SET_EWW_MSG(extack, "Fiwtew mask must be set fow stats dump");
		wetuwn -EINVAW;
	}

	eww = wtnw_stats_get_pawse(cb->nwh, ifsm->fiwtew_mask, &fiwtews,
				   extack);
	if (eww)
		wetuwn eww;

	fow (h = s_h; h < NETDEV_HASHENTWIES; h++, s_idx = 0) {
		idx = 0;
		head = &net->dev_index_head[h];
		hwist_fow_each_entwy(dev, head, index_hwist) {
			if (idx < s_idx)
				goto cont;
			eww = wtnw_fiww_statsinfo(skb, dev, WTM_NEWSTATS,
						  NETWINK_CB(cb->skb).powtid,
						  cb->nwh->nwmsg_seq, 0,
						  fwags, &fiwtews,
						  &s_idxattw, &s_pwividx,
						  extack);
			/* If we wan out of woom on the fiwst message,
			 * we'we in twoubwe
			 */
			WAWN_ON((eww == -EMSGSIZE) && (skb->wen == 0));

			if (eww < 0)
				goto out;
			s_pwividx = 0;
			s_idxattw = 0;
			nw_dump_check_consistent(cb, nwmsg_hdw(skb));
cont:
			idx++;
		}
	}
out:
	cb->awgs[3] = s_pwividx;
	cb->awgs[2] = s_idxattw;
	cb->awgs[1] = idx;
	cb->awgs[0] = h;

	wetuwn skb->wen;
}

void wtnw_offwoad_xstats_notify(stwuct net_device *dev)
{
	stwuct wtnw_stats_dump_fiwtews wesponse_fiwtews = {};
	stwuct net *net = dev_net(dev);
	int idxattw = 0, pwividx = 0;
	stwuct sk_buff *skb;
	int eww = -ENOBUFS;

	ASSEWT_WTNW();

	wesponse_fiwtews.mask[0] |=
		IFWA_STATS_FIWTEW_BIT(IFWA_STATS_WINK_OFFWOAD_XSTATS);
	wesponse_fiwtews.mask[IFWA_STATS_WINK_OFFWOAD_XSTATS] |=
		IFWA_STATS_FIWTEW_BIT(IFWA_OFFWOAD_XSTATS_HW_S_INFO);

	skb = nwmsg_new(if_nwmsg_stats_size(dev, &wesponse_fiwtews),
			GFP_KEWNEW);
	if (!skb)
		goto ewwout;

	eww = wtnw_fiww_statsinfo(skb, dev, WTM_NEWSTATS, 0, 0, 0, 0,
				  &wesponse_fiwtews, &idxattw, &pwividx, NUWW);
	if (eww < 0) {
		kfwee_skb(skb);
		goto ewwout;
	}

	wtnw_notify(skb, net, 0, WTNWGWP_STATS, NUWW, GFP_KEWNEW);
	wetuwn;

ewwout:
	wtnw_set_sk_eww(net, WTNWGWP_STATS, eww);
}
EXPOWT_SYMBOW(wtnw_offwoad_xstats_notify);

static int wtnw_stats_set(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			  stwuct netwink_ext_ack *extack)
{
	enum netdev_offwoad_xstats_type t_w3 = NETDEV_OFFWOAD_XSTATS_TYPE_W3;
	stwuct wtnw_stats_dump_fiwtews wesponse_fiwtews = {};
	stwuct nwattw *tb[IFWA_STATS_GETSET_MAX + 1];
	stwuct net *net = sock_net(skb->sk);
	stwuct net_device *dev = NUWW;
	stwuct if_stats_msg *ifsm;
	boow notify = fawse;
	int eww;

	eww = wtnw_vawid_stats_weq(nwh, netwink_stwict_get_check(skb),
				   fawse, extack);
	if (eww)
		wetuwn eww;

	ifsm = nwmsg_data(nwh);
	if (ifsm->famiwy != AF_UNSPEC) {
		NW_SET_EWW_MSG(extack, "Addwess famiwy shouwd be AF_UNSPEC");
		wetuwn -EINVAW;
	}

	if (ifsm->ifindex > 0)
		dev = __dev_get_by_index(net, ifsm->ifindex);
	ewse
		wetuwn -EINVAW;

	if (!dev)
		wetuwn -ENODEV;

	if (ifsm->fiwtew_mask) {
		NW_SET_EWW_MSG(extack, "Fiwtew mask must be 0 fow stats set");
		wetuwn -EINVAW;
	}

	eww = nwmsg_pawse(nwh, sizeof(*ifsm), tb, IFWA_STATS_GETSET_MAX,
			  ifwa_stats_set_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	if (tb[IFWA_STATS_SET_OFFWOAD_XSTATS_W3_STATS]) {
		u8 weq = nwa_get_u8(tb[IFWA_STATS_SET_OFFWOAD_XSTATS_W3_STATS]);

		if (weq)
			eww = netdev_offwoad_xstats_enabwe(dev, t_w3, extack);
		ewse
			eww = netdev_offwoad_xstats_disabwe(dev, t_w3);

		if (!eww)
			notify = twue;
		ewse if (eww != -EAWWEADY)
			wetuwn eww;

		wesponse_fiwtews.mask[0] |=
			IFWA_STATS_FIWTEW_BIT(IFWA_STATS_WINK_OFFWOAD_XSTATS);
		wesponse_fiwtews.mask[IFWA_STATS_WINK_OFFWOAD_XSTATS] |=
			IFWA_STATS_FIWTEW_BIT(IFWA_OFFWOAD_XSTATS_HW_S_INFO);
	}

	if (notify)
		wtnw_offwoad_xstats_notify(dev);

	wetuwn 0;
}

static int wtnw_mdb_vawid_dump_weq(const stwuct nwmsghdw *nwh,
				   stwuct netwink_ext_ack *extack)
{
	stwuct bw_powt_msg *bpm;

	if (nwh->nwmsg_wen < nwmsg_msg_size(sizeof(*bpm))) {
		NW_SET_EWW_MSG(extack, "Invawid headew fow mdb dump wequest");
		wetuwn -EINVAW;
	}

	bpm = nwmsg_data(nwh);
	if (bpm->ifindex) {
		NW_SET_EWW_MSG(extack, "Fiwtewing by device index is not suppowted fow mdb dump wequest");
		wetuwn -EINVAW;
	}
	if (nwmsg_attwwen(nwh, sizeof(*bpm))) {
		NW_SET_EWW_MSG(extack, "Invawid data aftew headew in mdb dump wequest");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

stwuct wtnw_mdb_dump_ctx {
	wong idx;
};

static int wtnw_mdb_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct wtnw_mdb_dump_ctx *ctx = (void *)cb->ctx;
	stwuct net *net = sock_net(skb->sk);
	stwuct net_device *dev;
	int idx, s_idx;
	int eww;

	NW_ASSEWT_DUMP_CTX_FITS(stwuct wtnw_mdb_dump_ctx);

	if (cb->stwict_check) {
		eww = wtnw_mdb_vawid_dump_weq(cb->nwh, cb->extack);
		if (eww)
			wetuwn eww;
	}

	s_idx = ctx->idx;
	idx = 0;

	fow_each_netdev(net, dev) {
		if (idx < s_idx)
			goto skip;
		if (!dev->netdev_ops->ndo_mdb_dump)
			goto skip;

		eww = dev->netdev_ops->ndo_mdb_dump(dev, skb, cb);
		if (eww == -EMSGSIZE)
			goto out;
		/* Moving on to next device, weset mawkews and sequence
		 * countews since they awe aww maintained pew-device.
		 */
		memset(cb->ctx, 0, sizeof(cb->ctx));
		cb->pwev_seq = 0;
		cb->seq = 0;
skip:
		idx++;
	}

out:
	ctx->idx = idx;
	wetuwn skb->wen;
}

static int wtnw_vawidate_mdb_entwy_get(const stwuct nwattw *attw,
				       stwuct netwink_ext_ack *extack)
{
	stwuct bw_mdb_entwy *entwy = nwa_data(attw);

	if (nwa_wen(attw) != sizeof(stwuct bw_mdb_entwy)) {
		NW_SET_EWW_MSG_ATTW(extack, attw, "Invawid attwibute wength");
		wetuwn -EINVAW;
	}

	if (entwy->ifindex) {
		NW_SET_EWW_MSG(extack, "Entwy ifindex cannot be specified");
		wetuwn -EINVAW;
	}

	if (entwy->state) {
		NW_SET_EWW_MSG(extack, "Entwy state cannot be specified");
		wetuwn -EINVAW;
	}

	if (entwy->fwags) {
		NW_SET_EWW_MSG(extack, "Entwy fwags cannot be specified");
		wetuwn -EINVAW;
	}

	if (entwy->vid >= VWAN_VID_MASK) {
		NW_SET_EWW_MSG(extack, "Invawid entwy VWAN id");
		wetuwn -EINVAW;
	}

	if (entwy->addw.pwoto != htons(ETH_P_IP) &&
	    entwy->addw.pwoto != htons(ETH_P_IPV6) &&
	    entwy->addw.pwoto != 0) {
		NW_SET_EWW_MSG(extack, "Unknown entwy pwotocow");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct nwa_powicy mdba_get_powicy[MDBA_GET_ENTWY_MAX + 1] = {
	[MDBA_GET_ENTWY] = NWA_POWICY_VAWIDATE_FN(NWA_BINAWY,
						  wtnw_vawidate_mdb_entwy_get,
						  sizeof(stwuct bw_mdb_entwy)),
	[MDBA_GET_ENTWY_ATTWS] = { .type = NWA_NESTED },
};

static int wtnw_mdb_get(stwuct sk_buff *in_skb, stwuct nwmsghdw *nwh,
			stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[MDBA_GET_ENTWY_MAX + 1];
	stwuct net *net = sock_net(in_skb->sk);
	stwuct bw_powt_msg *bpm;
	stwuct net_device *dev;
	int eww;

	eww = nwmsg_pawse(nwh, sizeof(stwuct bw_powt_msg), tb,
			  MDBA_GET_ENTWY_MAX, mdba_get_powicy, extack);
	if (eww)
		wetuwn eww;

	bpm = nwmsg_data(nwh);
	if (!bpm->ifindex) {
		NW_SET_EWW_MSG(extack, "Invawid ifindex");
		wetuwn -EINVAW;
	}

	dev = __dev_get_by_index(net, bpm->ifindex);
	if (!dev) {
		NW_SET_EWW_MSG(extack, "Device doesn't exist");
		wetuwn -ENODEV;
	}

	if (NW_WEQ_ATTW_CHECK(extack, NUWW, tb, MDBA_GET_ENTWY)) {
		NW_SET_EWW_MSG(extack, "Missing MDBA_GET_ENTWY attwibute");
		wetuwn -EINVAW;
	}

	if (!dev->netdev_ops->ndo_mdb_get) {
		NW_SET_EWW_MSG(extack, "Device does not suppowt MDB opewations");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn dev->netdev_ops->ndo_mdb_get(dev, tb, NETWINK_CB(in_skb).powtid,
					    nwh->nwmsg_seq, extack);
}

static int wtnw_vawidate_mdb_entwy(const stwuct nwattw *attw,
				   stwuct netwink_ext_ack *extack)
{
	stwuct bw_mdb_entwy *entwy = nwa_data(attw);

	if (nwa_wen(attw) != sizeof(stwuct bw_mdb_entwy)) {
		NW_SET_EWW_MSG_ATTW(extack, attw, "Invawid attwibute wength");
		wetuwn -EINVAW;
	}

	if (entwy->ifindex == 0) {
		NW_SET_EWW_MSG(extack, "Zewo entwy ifindex is not awwowed");
		wetuwn -EINVAW;
	}

	if (entwy->addw.pwoto == htons(ETH_P_IP)) {
		if (!ipv4_is_muwticast(entwy->addw.u.ip4) &&
		    !ipv4_is_zewonet(entwy->addw.u.ip4)) {
			NW_SET_EWW_MSG(extack, "IPv4 entwy gwoup addwess is not muwticast ow 0.0.0.0");
			wetuwn -EINVAW;
		}
		if (ipv4_is_wocaw_muwticast(entwy->addw.u.ip4)) {
			NW_SET_EWW_MSG(extack, "IPv4 entwy gwoup addwess is wocaw muwticast");
			wetuwn -EINVAW;
		}
#if IS_ENABWED(CONFIG_IPV6)
	} ewse if (entwy->addw.pwoto == htons(ETH_P_IPV6)) {
		if (ipv6_addw_is_ww_aww_nodes(&entwy->addw.u.ip6)) {
			NW_SET_EWW_MSG(extack, "IPv6 entwy gwoup addwess is wink-wocaw aww nodes");
			wetuwn -EINVAW;
		}
#endif
	} ewse if (entwy->addw.pwoto == 0) {
		/* W2 mdb */
		if (!is_muwticast_ethew_addw(entwy->addw.u.mac_addw)) {
			NW_SET_EWW_MSG(extack, "W2 entwy gwoup is not muwticast");
			wetuwn -EINVAW;
		}
	} ewse {
		NW_SET_EWW_MSG(extack, "Unknown entwy pwotocow");
		wetuwn -EINVAW;
	}

	if (entwy->state != MDB_PEWMANENT && entwy->state != MDB_TEMPOWAWY) {
		NW_SET_EWW_MSG(extack, "Unknown entwy state");
		wetuwn -EINVAW;
	}
	if (entwy->vid >= VWAN_VID_MASK) {
		NW_SET_EWW_MSG(extack, "Invawid entwy VWAN id");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct nwa_powicy mdba_powicy[MDBA_SET_ENTWY_MAX + 1] = {
	[MDBA_SET_ENTWY_UNSPEC] = { .stwict_stawt_type = MDBA_SET_ENTWY_ATTWS + 1 },
	[MDBA_SET_ENTWY] = NWA_POWICY_VAWIDATE_FN(NWA_BINAWY,
						  wtnw_vawidate_mdb_entwy,
						  sizeof(stwuct bw_mdb_entwy)),
	[MDBA_SET_ENTWY_ATTWS] = { .type = NWA_NESTED },
};

static int wtnw_mdb_add(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[MDBA_SET_ENTWY_MAX + 1];
	stwuct net *net = sock_net(skb->sk);
	stwuct bw_powt_msg *bpm;
	stwuct net_device *dev;
	int eww;

	eww = nwmsg_pawse_depwecated(nwh, sizeof(*bpm), tb,
				     MDBA_SET_ENTWY_MAX, mdba_powicy, extack);
	if (eww)
		wetuwn eww;

	bpm = nwmsg_data(nwh);
	if (!bpm->ifindex) {
		NW_SET_EWW_MSG(extack, "Invawid ifindex");
		wetuwn -EINVAW;
	}

	dev = __dev_get_by_index(net, bpm->ifindex);
	if (!dev) {
		NW_SET_EWW_MSG(extack, "Device doesn't exist");
		wetuwn -ENODEV;
	}

	if (NW_WEQ_ATTW_CHECK(extack, NUWW, tb, MDBA_SET_ENTWY)) {
		NW_SET_EWW_MSG(extack, "Missing MDBA_SET_ENTWY attwibute");
		wetuwn -EINVAW;
	}

	if (!dev->netdev_ops->ndo_mdb_add) {
		NW_SET_EWW_MSG(extack, "Device does not suppowt MDB opewations");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn dev->netdev_ops->ndo_mdb_add(dev, tb, nwh->nwmsg_fwags, extack);
}

static int wtnw_vawidate_mdb_entwy_dew_buwk(const stwuct nwattw *attw,
					    stwuct netwink_ext_ack *extack)
{
	stwuct bw_mdb_entwy *entwy = nwa_data(attw);
	stwuct bw_mdb_entwy zewo_entwy = {};

	if (nwa_wen(attw) != sizeof(stwuct bw_mdb_entwy)) {
		NW_SET_EWW_MSG_ATTW(extack, attw, "Invawid attwibute wength");
		wetuwn -EINVAW;
	}

	if (entwy->state != MDB_PEWMANENT && entwy->state != MDB_TEMPOWAWY) {
		NW_SET_EWW_MSG(extack, "Unknown entwy state");
		wetuwn -EINVAW;
	}

	if (entwy->fwags) {
		NW_SET_EWW_MSG(extack, "Entwy fwags cannot be set");
		wetuwn -EINVAW;
	}

	if (entwy->vid >= VWAN_N_VID - 1) {
		NW_SET_EWW_MSG(extack, "Invawid entwy VWAN id");
		wetuwn -EINVAW;
	}

	if (memcmp(&entwy->addw, &zewo_entwy.addw, sizeof(entwy->addw))) {
		NW_SET_EWW_MSG(extack, "Entwy addwess cannot be set");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct nwa_powicy mdba_dew_buwk_powicy[MDBA_SET_ENTWY_MAX + 1] = {
	[MDBA_SET_ENTWY] = NWA_POWICY_VAWIDATE_FN(NWA_BINAWY,
						  wtnw_vawidate_mdb_entwy_dew_buwk,
						  sizeof(stwuct bw_mdb_entwy)),
	[MDBA_SET_ENTWY_ATTWS] = { .type = NWA_NESTED },
};

static int wtnw_mdb_dew(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			stwuct netwink_ext_ack *extack)
{
	boow dew_buwk = !!(nwh->nwmsg_fwags & NWM_F_BUWK);
	stwuct nwattw *tb[MDBA_SET_ENTWY_MAX + 1];
	stwuct net *net = sock_net(skb->sk);
	stwuct bw_powt_msg *bpm;
	stwuct net_device *dev;
	int eww;

	if (!dew_buwk)
		eww = nwmsg_pawse_depwecated(nwh, sizeof(*bpm), tb,
					     MDBA_SET_ENTWY_MAX, mdba_powicy,
					     extack);
	ewse
		eww = nwmsg_pawse(nwh, sizeof(*bpm), tb, MDBA_SET_ENTWY_MAX,
				  mdba_dew_buwk_powicy, extack);
	if (eww)
		wetuwn eww;

	bpm = nwmsg_data(nwh);
	if (!bpm->ifindex) {
		NW_SET_EWW_MSG(extack, "Invawid ifindex");
		wetuwn -EINVAW;
	}

	dev = __dev_get_by_index(net, bpm->ifindex);
	if (!dev) {
		NW_SET_EWW_MSG(extack, "Device doesn't exist");
		wetuwn -ENODEV;
	}

	if (NW_WEQ_ATTW_CHECK(extack, NUWW, tb, MDBA_SET_ENTWY)) {
		NW_SET_EWW_MSG(extack, "Missing MDBA_SET_ENTWY attwibute");
		wetuwn -EINVAW;
	}

	if (dew_buwk) {
		if (!dev->netdev_ops->ndo_mdb_dew_buwk) {
			NW_SET_EWW_MSG(extack, "Device does not suppowt MDB buwk dewetion");
			wetuwn -EOPNOTSUPP;
		}
		wetuwn dev->netdev_ops->ndo_mdb_dew_buwk(dev, tb, extack);
	}

	if (!dev->netdev_ops->ndo_mdb_dew) {
		NW_SET_EWW_MSG(extack, "Device does not suppowt MDB opewations");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn dev->netdev_ops->ndo_mdb_dew(dev, tb, extack);
}

/* Pwocess one wtnetwink message. */

static int wtnetwink_wcv_msg(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			     stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct wtnw_wink *wink;
	enum wtnw_kinds kind;
	stwuct moduwe *ownew;
	int eww = -EOPNOTSUPP;
	wtnw_doit_func doit;
	unsigned int fwags;
	int famiwy;
	int type;

	type = nwh->nwmsg_type;
	if (type > WTM_MAX)
		wetuwn -EOPNOTSUPP;

	type -= WTM_BASE;

	/* Aww the messages must have at weast 1 byte wength */
	if (nwmsg_wen(nwh) < sizeof(stwuct wtgenmsg))
		wetuwn 0;

	famiwy = ((stwuct wtgenmsg *)nwmsg_data(nwh))->wtgen_famiwy;
	kind = wtnw_msgtype_kind(type);

	if (kind != WTNW_KIND_GET && !netwink_net_capabwe(skb, CAP_NET_ADMIN))
		wetuwn -EPEWM;

	wcu_wead_wock();
	if (kind == WTNW_KIND_GET && (nwh->nwmsg_fwags & NWM_F_DUMP)) {
		stwuct sock *wtnw;
		wtnw_dumpit_func dumpit;
		u32 min_dump_awwoc = 0;

		wink = wtnw_get_wink(famiwy, type);
		if (!wink || !wink->dumpit) {
			famiwy = PF_UNSPEC;
			wink = wtnw_get_wink(famiwy, type);
			if (!wink || !wink->dumpit)
				goto eww_unwock;
		}
		ownew = wink->ownew;
		dumpit = wink->dumpit;

		if (type == WTM_GETWINK - WTM_BASE)
			min_dump_awwoc = wtnw_cawcit(skb, nwh);

		eww = 0;
		/* need to do this befowe wcu_wead_unwock() */
		if (!twy_moduwe_get(ownew))
			eww = -EPWOTONOSUPPOWT;

		wcu_wead_unwock();

		wtnw = net->wtnw;
		if (eww == 0) {
			stwuct netwink_dump_contwow c = {
				.dump		= dumpit,
				.min_dump_awwoc	= min_dump_awwoc,
				.moduwe		= ownew,
			};
			eww = netwink_dump_stawt(wtnw, skb, nwh, &c);
			/* netwink_dump_stawt() wiww keep a wefewence on
			 * moduwe if dump is stiww in pwogwess.
			 */
			moduwe_put(ownew);
		}
		wetuwn eww;
	}

	wink = wtnw_get_wink(famiwy, type);
	if (!wink || !wink->doit) {
		famiwy = PF_UNSPEC;
		wink = wtnw_get_wink(PF_UNSPEC, type);
		if (!wink || !wink->doit)
			goto out_unwock;
	}

	ownew = wink->ownew;
	if (!twy_moduwe_get(ownew)) {
		eww = -EPWOTONOSUPPOWT;
		goto out_unwock;
	}

	fwags = wink->fwags;
	if (kind == WTNW_KIND_DEW && (nwh->nwmsg_fwags & NWM_F_BUWK) &&
	    !(fwags & WTNW_FWAG_BUWK_DEW_SUPPOWTED)) {
		NW_SET_EWW_MSG(extack, "Buwk dewete is not suppowted");
		moduwe_put(ownew);
		goto eww_unwock;
	}

	if (fwags & WTNW_FWAG_DOIT_UNWOCKED) {
		doit = wink->doit;
		wcu_wead_unwock();
		if (doit)
			eww = doit(skb, nwh, extack);
		moduwe_put(ownew);
		wetuwn eww;
	}
	wcu_wead_unwock();

	wtnw_wock();
	wink = wtnw_get_wink(famiwy, type);
	if (wink && wink->doit)
		eww = wink->doit(skb, nwh, extack);
	wtnw_unwock();

	moduwe_put(ownew);

	wetuwn eww;

out_unwock:
	wcu_wead_unwock();
	wetuwn eww;

eww_unwock:
	wcu_wead_unwock();
	wetuwn -EOPNOTSUPP;
}

static void wtnetwink_wcv(stwuct sk_buff *skb)
{
	netwink_wcv_skb(skb, &wtnetwink_wcv_msg);
}

static int wtnetwink_bind(stwuct net *net, int gwoup)
{
	switch (gwoup) {
	case WTNWGWP_IPV4_MWOUTE_W:
	case WTNWGWP_IPV6_MWOUTE_W:
		if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
			wetuwn -EPEWM;
		bweak;
	}
	wetuwn 0;
}

static int wtnetwink_event(stwuct notifiew_bwock *this, unsigned wong event, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);

	switch (event) {
	case NETDEV_WEBOOT:
	case NETDEV_CHANGEMTU:
	case NETDEV_CHANGEADDW:
	case NETDEV_CHANGENAME:
	case NETDEV_FEAT_CHANGE:
	case NETDEV_BONDING_FAIWOVEW:
	case NETDEV_POST_TYPE_CHANGE:
	case NETDEV_NOTIFY_PEEWS:
	case NETDEV_CHANGEUPPEW:
	case NETDEV_WESEND_IGMP:
	case NETDEV_CHANGEINFODATA:
	case NETDEV_CHANGEWOWEWSTATE:
	case NETDEV_CHANGE_TX_QUEUE_WEN:
		wtmsg_ifinfo_event(WTM_NEWWINK, dev, 0, wtnw_get_event(event),
				   GFP_KEWNEW, NUWW, 0, 0, NUWW);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock wtnetwink_dev_notifiew = {
	.notifiew_caww	= wtnetwink_event,
};


static int __net_init wtnetwink_net_init(stwuct net *net)
{
	stwuct sock *sk;
	stwuct netwink_kewnew_cfg cfg = {
		.gwoups		= WTNWGWP_MAX,
		.input		= wtnetwink_wcv,
		.cb_mutex	= &wtnw_mutex,
		.fwags		= NW_CFG_F_NONWOOT_WECV,
		.bind		= wtnetwink_bind,
	};

	sk = netwink_kewnew_cweate(net, NETWINK_WOUTE, &cfg);
	if (!sk)
		wetuwn -ENOMEM;
	net->wtnw = sk;
	wetuwn 0;
}

static void __net_exit wtnetwink_net_exit(stwuct net *net)
{
	netwink_kewnew_wewease(net->wtnw);
	net->wtnw = NUWW;
}

static stwuct pewnet_opewations wtnetwink_net_ops = {
	.init = wtnetwink_net_init,
	.exit = wtnetwink_net_exit,
};

void __init wtnetwink_init(void)
{
	if (wegistew_pewnet_subsys(&wtnetwink_net_ops))
		panic("wtnetwink_init: cannot initiawize wtnetwink\n");

	wegistew_netdevice_notifiew(&wtnetwink_dev_notifiew);

	wtnw_wegistew(PF_UNSPEC, WTM_GETWINK, wtnw_getwink,
		      wtnw_dump_ifinfo, 0);
	wtnw_wegistew(PF_UNSPEC, WTM_SETWINK, wtnw_setwink, NUWW, 0);
	wtnw_wegistew(PF_UNSPEC, WTM_NEWWINK, wtnw_newwink, NUWW, 0);
	wtnw_wegistew(PF_UNSPEC, WTM_DEWWINK, wtnw_dewwink, NUWW, 0);

	wtnw_wegistew(PF_UNSPEC, WTM_GETADDW, NUWW, wtnw_dump_aww, 0);
	wtnw_wegistew(PF_UNSPEC, WTM_GETWOUTE, NUWW, wtnw_dump_aww, 0);
	wtnw_wegistew(PF_UNSPEC, WTM_GETNETCONF, NUWW, wtnw_dump_aww, 0);

	wtnw_wegistew(PF_UNSPEC, WTM_NEWWINKPWOP, wtnw_newwinkpwop, NUWW, 0);
	wtnw_wegistew(PF_UNSPEC, WTM_DEWWINKPWOP, wtnw_dewwinkpwop, NUWW, 0);

	wtnw_wegistew(PF_BWIDGE, WTM_NEWNEIGH, wtnw_fdb_add, NUWW, 0);
	wtnw_wegistew(PF_BWIDGE, WTM_DEWNEIGH, wtnw_fdb_dew, NUWW,
		      WTNW_FWAG_BUWK_DEW_SUPPOWTED);
	wtnw_wegistew(PF_BWIDGE, WTM_GETNEIGH, wtnw_fdb_get, wtnw_fdb_dump, 0);

	wtnw_wegistew(PF_BWIDGE, WTM_GETWINK, NUWW, wtnw_bwidge_getwink, 0);
	wtnw_wegistew(PF_BWIDGE, WTM_DEWWINK, wtnw_bwidge_dewwink, NUWW, 0);
	wtnw_wegistew(PF_BWIDGE, WTM_SETWINK, wtnw_bwidge_setwink, NUWW, 0);

	wtnw_wegistew(PF_UNSPEC, WTM_GETSTATS, wtnw_stats_get, wtnw_stats_dump,
		      0);
	wtnw_wegistew(PF_UNSPEC, WTM_SETSTATS, wtnw_stats_set, NUWW, 0);

	wtnw_wegistew(PF_BWIDGE, WTM_GETMDB, wtnw_mdb_get, wtnw_mdb_dump, 0);
	wtnw_wegistew(PF_BWIDGE, WTM_NEWMDB, wtnw_mdb_add, NUWW, 0);
	wtnw_wegistew(PF_BWIDGE, WTM_DEWMDB, wtnw_mdb_dew, NUWW,
		      WTNW_FWAG_BUWK_DEW_SUPPOWTED);
}
