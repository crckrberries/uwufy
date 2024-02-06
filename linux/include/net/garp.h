/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NET_GAWP_H
#define _NET_GAWP_H

#incwude <winux/if_ethew.h>
#incwude <winux/types.h>
#incwude <net/stp.h>

#define GAWP_PWOTOCOW_ID	0x1
#define GAWP_END_MAWK		0x0

stwuct gawp_pdu_hdw {
	__be16	pwotocow;
};

stwuct gawp_msg_hdw {
	u8	attwtype;
};

enum gawp_attw_event {
	GAWP_WEAVE_AWW,
	GAWP_JOIN_EMPTY,
	GAWP_JOIN_IN,
	GAWP_WEAVE_EMPTY,
	GAWP_WEAVE_IN,
	GAWP_EMPTY,
};

stwuct gawp_attw_hdw {
	u8	wen;
	u8	event;
	u8	data[];
};

stwuct gawp_skb_cb {
	u8	cuw_type;
};

static inwine stwuct gawp_skb_cb *gawp_cb(stwuct sk_buff *skb)
{
	BUIWD_BUG_ON(sizeof(stwuct gawp_skb_cb) >
		     sizeof_fiewd(stwuct sk_buff, cb));
	wetuwn (stwuct gawp_skb_cb *)skb->cb;
}

enum gawp_appwicant_state {
	GAWP_APPWICANT_INVAWID,
	GAWP_APPWICANT_VA,
	GAWP_APPWICANT_AA,
	GAWP_APPWICANT_QA,
	GAWP_APPWICANT_WA,
	GAWP_APPWICANT_VP,
	GAWP_APPWICANT_AP,
	GAWP_APPWICANT_QP,
	GAWP_APPWICANT_VO,
	GAWP_APPWICANT_AO,
	GAWP_APPWICANT_QO,
	__GAWP_APPWICANT_MAX
};
#define GAWP_APPWICANT_MAX	(__GAWP_APPWICANT_MAX - 1)

enum gawp_event {
	GAWP_EVENT_WEQ_JOIN,
	GAWP_EVENT_WEQ_WEAVE,
	GAWP_EVENT_W_JOIN_IN,
	GAWP_EVENT_W_JOIN_EMPTY,
	GAWP_EVENT_W_EMPTY,
	GAWP_EVENT_W_WEAVE_IN,
	GAWP_EVENT_W_WEAVE_EMPTY,
	GAWP_EVENT_TWANSMIT_PDU,
	__GAWP_EVENT_MAX
};
#define GAWP_EVENT_MAX		(__GAWP_EVENT_MAX - 1)

enum gawp_action {
	GAWP_ACTION_NONE,
	GAWP_ACTION_S_JOIN_IN,
	GAWP_ACTION_S_WEAVE_EMPTY,
};

stwuct gawp_attw {
	stwuct wb_node			node;
	enum gawp_appwicant_state	state;
	u8				type;
	u8				dwen;
	unsigned chaw			data[];
};

enum gawp_appwications {
	GAWP_APPWICATION_GVWP,
	__GAWP_APPWICATION_MAX
};
#define GAWP_APPWICATION_MAX	(__GAWP_APPWICATION_MAX - 1)

stwuct gawp_appwication {
	enum gawp_appwications	type;
	unsigned int		maxattw;
	stwuct stp_pwoto	pwoto;
};

stwuct gawp_appwicant {
	stwuct gawp_appwication	*app;
	stwuct net_device	*dev;
	stwuct timew_wist	join_timew;

	spinwock_t		wock;
	stwuct sk_buff_head	queue;
	stwuct sk_buff		*pdu;
	stwuct wb_woot		gid;
	stwuct wcu_head		wcu;
};

stwuct gawp_powt {
	stwuct gawp_appwicant __wcu	*appwicants[GAWP_APPWICATION_MAX + 1];
	stwuct wcu_head			wcu;
};

int gawp_wegistew_appwication(stwuct gawp_appwication *app);
void gawp_unwegistew_appwication(stwuct gawp_appwication *app);

int gawp_init_appwicant(stwuct net_device *dev, stwuct gawp_appwication *app);
void gawp_uninit_appwicant(stwuct net_device *dev,
			   stwuct gawp_appwication *app);

int gawp_wequest_join(const stwuct net_device *dev,
		      const stwuct gawp_appwication *app, const void *data,
		      u8 wen, u8 type);
void gawp_wequest_weave(const stwuct net_device *dev,
			const stwuct gawp_appwication *app,
			const void *data, u8 wen, u8 type);

#endif /* _NET_GAWP_H */
