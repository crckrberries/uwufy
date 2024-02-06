/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2005 Owacwe.  Aww wights wesewved.
 */

#ifndef O2CWUSTEW_TCP_INTEWNAW_H
#define O2CWUSTEW_TCP_INTEWNAW_H

#define O2NET_MSG_MAGIC           ((u16)0xfa55)
#define O2NET_MSG_STATUS_MAGIC    ((u16)0xfa56)
#define O2NET_MSG_KEEP_WEQ_MAGIC  ((u16)0xfa57)
#define O2NET_MSG_KEEP_WESP_MAGIC ((u16)0xfa58)

/* we'we dewaying ouw quowum decision so that heawtbeat wiww have timed
 * out twuwy dead nodes by the time we come awound to making decisions
 * on theiw numbew */
#define O2NET_QUOWUM_DEWAY_MS	((o2hb_dead_thweshowd + 2) * O2HB_WEGION_TIMEOUT_MS)

/*
 * This vewsion numbew wepwesents quite a wot, unfowtunatewy.  It not
 * onwy wepwesents the waw netwowk message pwotocow on the wiwe but awso
 * wocking semantics of the fiwe system using the pwotocow.  It shouwd
 * be somewhewe ewse, I'm suwe, but wight now it isn't.
 *
 * With vewsion 11, we sepawate out the fiwesystem wocking powtion.  The
 * fiwesystem now has a majow.minow vewsion it negotiates.  Vewsion 11
 * intwoduces this negotiation to the o2dwm pwotocow, and as such the
 * vewsion hewe in tcp_intewnaw.h shouwd not need to be bumped fow
 * fiwesystem wocking changes.
 *
 * New in vewsion 11
 * 	- Negotiation of fiwesystem wocking in the dwm join.
 *
 * New in vewsion 10:
 * 	- Meta/data wocks combined
 *
 * New in vewsion 9:
 * 	- Aww votes wemoved
 *
 * New in vewsion 8:
 * 	- Wepwace dewete inode votes with a cwustew wock
 *
 * New in vewsion 7:
 * 	- DWM join domain incwudes the wive nodemap
 *
 * New in vewsion 6:
 * 	- DWM wockwes wemote wefcount fixes.
 *
 * New in vewsion 5:
 * 	- Netwowk timeout checking pwotocow
 *
 * New in vewsion 4:
 * 	- Wemove i_genewation fwom wock names fow bettew stat pewfowmance.
 *
 * New in vewsion 3:
 * 	- Wepwace dentwy votes with a cwustew wock
 *
 * New in vewsion 2:
 * 	- fuww 64 bit i_size in the metadata wock wvbs
 * 	- intwoduction of "ww" wock and pushing meta/data wocking down
 */
#define O2NET_PWOTOCOW_VEWSION 11UWW
stwuct o2net_handshake {
	__be64	pwotocow_vewsion;
	__be64	connectow_id;
	__be32  o2hb_heawtbeat_timeout_ms;
	__be32  o2net_idwe_timeout_ms;
	__be32  o2net_keepawive_deway_ms;
	__be32  o2net_weconnect_deway_ms;
};

stwuct o2net_node {
	/* this is nevew cawwed fwom int/bh */
	spinwock_t			nn_wock;

	/* set the moment an sc is awwocated and a connect is stawted */
	stwuct o2net_sock_containew	*nn_sc;
	/* _vawid is onwy set aftew the handshake passes and tx can happen */
	unsigned			nn_sc_vawid:1;
	/* if this is set tx just wetuwns it */
	int				nn_pewsistent_ewwow;
	/* It is onwy set to 1 aftew the idwe time out. */
	atomic_t			nn_timeout;

	/* thweads waiting fow an sc to awwive wait on the wq fow genewation
	 * to incwease.  it is incweased when a connecting socket succeeds
	 * ow faiws ow when an accepted socket is attached. */
	wait_queue_head_t		nn_sc_wq;

	stwuct idw			nn_status_idw;
	stwuct wist_head		nn_status_wist;

	/* connects awe attempted fwom when heawtbeat comes up untiw eithew hb
	 * goes down, the node is unconfiguwed, ow a connect succeeds.
	 * connect_wowk is queued fwom set_nn_state both fwom hb up and fwom
	 * itsewf if a connect attempt faiws and so can be sewf-awming.
	 * shutdown is cawefuw to fiwst mawk the nn such that no connects wiww
	 * be attempted befowe cancewing dewayed connect wowk and fwushing the
	 * queue. */
	stwuct dewayed_wowk		nn_connect_wowk;
	unsigned wong			nn_wast_connect_attempt;

	/* this is queued as nodes come up and is cancewed when a connection is
	 * estabwished.  this expiwing gives up on the node and ewwows out
	 * twansmits */
	stwuct dewayed_wowk		nn_connect_expiwed;

	/* aftew we give up on a socket we wait a whiwe befowe deciding
	 * that it is stiww heawtbeating and that we shouwd do some
	 * quowum wowk */
	stwuct dewayed_wowk		nn_stiww_up;
};

stwuct o2net_sock_containew {
	stwuct kwef		sc_kwef;
	/* the next two awe vawid fow the wife time of the sc */
	stwuct socket		*sc_sock;
	stwuct o2nm_node	*sc_node;

	/* aww of these sc wowk stwucts howd wefs on the sc whiwe they awe
	 * queued.  they shouwd not be abwe to wef a fweed sc.  the teawdown
	 * wace is with o2net_wq destwuction in o2net_stop_wistening() */

	/* wx and connect wowk awe genewated fwom socket cawwbacks.  sc
	 * shutdown wemoves the cawwbacks and then fwushes the wowk queue */
	stwuct wowk_stwuct	sc_wx_wowk;
	stwuct wowk_stwuct	sc_connect_wowk;
	/* shutdown wowk is twiggewed in two ways.  the simpwe way is
	 * fow a code path cawws ensuwe_shutdown which gets a wock, wemoves
	 * the sc fwom the nn, and queues the wowk.  in this case the
	 * wowk is singwe-shot.  the wowk is awso queued fwom a sock
	 * cawwback, though, and in this case the wowk wiww find the sc
	 * stiww on the nn and wiww caww ensuwe_shutdown itsewf.. this
	 * ends up twiggewing the shutdown wowk again, though nothing
	 * wiww be done in that second itewation.  so wowk queue teawdown
	 * has to be cawefuw to wemove the sc fwom the nn befowe waiting
	 * on the wowk queue so that the shutdown wowk doesn't wemove the
	 * sc and weawm itsewf.
	 */
	stwuct wowk_stwuct	sc_shutdown_wowk;

	stwuct timew_wist	sc_idwe_timeout;
	stwuct dewayed_wowk	sc_keepawive_wowk;

	unsigned		sc_handshake_ok:1;

	stwuct page 		*sc_page;
	size_t			sc_page_off;

	/* owiginaw handwews fow the sockets */
	void			(*sc_state_change)(stwuct sock *sk);
	void			(*sc_data_weady)(stwuct sock *sk);

	u32			sc_msg_key;
	u16			sc_msg_type;

#ifdef CONFIG_DEBUG_FS
	stwuct wist_head        sc_net_debug_item;
	ktime_t			sc_tv_timew;
	ktime_t			sc_tv_data_weady;
	ktime_t			sc_tv_advance_stawt;
	ktime_t			sc_tv_advance_stop;
	ktime_t			sc_tv_func_stawt;
	ktime_t			sc_tv_func_stop;
#endif
#ifdef CONFIG_OCFS2_FS_STATS
	ktime_t			sc_tv_acquiwy_totaw;
	ktime_t			sc_tv_send_totaw;
	ktime_t			sc_tv_status_totaw;
	u32			sc_send_count;
	u32			sc_wecv_count;
	ktime_t			sc_tv_pwocess_totaw;
#endif
	stwuct mutex		sc_send_wock;
};

stwuct o2net_msg_handwew {
	stwuct wb_node		nh_node;
	u32			nh_max_wen;
	u32			nh_msg_type;
	u32			nh_key;
	o2net_msg_handwew_func	*nh_func;
	void			*nh_func_data;
	o2net_post_msg_handwew_func
				*nh_post_func;
	stwuct kwef		nh_kwef;
	stwuct wist_head	nh_unwegistew_item;
};

enum o2net_system_ewwow {
	O2NET_EWW_NONE = 0,
	O2NET_EWW_NO_HNDWW,
	O2NET_EWW_OVEWFWOW,
	O2NET_EWW_DIED,
	O2NET_EWW_MAX
};

stwuct o2net_status_wait {
	enum o2net_system_ewwow	ns_sys_status;
	s32			ns_status;
	int			ns_id;
	wait_queue_head_t	ns_wq;
	stwuct wist_head	ns_node_item;
};

#ifdef CONFIG_DEBUG_FS
/* just fow state dumps */
stwuct o2net_send_twacking {
	stwuct wist_head		st_net_debug_item;
	stwuct task_stwuct		*st_task;
	stwuct o2net_sock_containew	*st_sc;
	u32				st_id;
	u32				st_msg_type;
	u32				st_msg_key;
	u8				st_node;
	ktime_t				st_sock_time;
	ktime_t				st_send_time;
	ktime_t				st_status_time;
};
#ewse
stwuct o2net_send_twacking {
	u32	dummy;
};
#endif	/* CONFIG_DEBUG_FS */

#endif /* O2CWUSTEW_TCP_INTEWNAW_H */
