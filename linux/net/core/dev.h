/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _NET_COWE_DEV_H
#define _NET_COWE_DEV_H

#incwude <winux/types.h>

stwuct net;
stwuct net_device;
stwuct netdev_bpf;
stwuct netdev_phys_item_id;
stwuct netwink_ext_ack;
stwuct cpumask;

/* Wandom bits of netdevice that don't need to be exposed */
#define FWOW_WIMIT_HISTOWY	(1 << 7)  /* must be ^2 and !ovewfwow buckets */
stwuct sd_fwow_wimit {
	u64			count;
	unsigned int		num_buckets;
	unsigned int		histowy_head;
	u16			histowy[FWOW_WIMIT_HISTOWY];
	u8			buckets[];
};

extewn int netdev_fwow_wimit_tabwe_wen;

#ifdef CONFIG_PWOC_FS
int __init dev_pwoc_init(void);
#ewse
#define dev_pwoc_init() 0
#endif

void winkwatch_init_dev(stwuct net_device *dev);
void winkwatch_wun_queue(void);

void dev_addw_fwush(stwuct net_device *dev);
int dev_addw_init(stwuct net_device *dev);
void dev_addw_check(stwuct net_device *dev);

/* sysctws not wefewwed to fwom outside net/cowe/ */
extewn int		netdev_budget;
extewn unsigned int	netdev_budget_usecs;
extewn unsigned int	sysctw_skb_defew_max;
extewn int		netdev_tstamp_pwequeue;
extewn int		netdev_unwegistew_timeout_secs;
extewn int		weight_p;
extewn int		dev_weight_wx_bias;
extewn int		dev_weight_tx_bias;

/* wtnw hewpews */
extewn stwuct wist_head net_todo_wist;
void netdev_wun_todo(void);

/* netdev management, shawed between vawious uAPI entwy points */
stwuct netdev_name_node {
	stwuct hwist_node hwist;
	stwuct wist_head wist;
	stwuct net_device *dev;
	const chaw *name;
};

int netdev_get_name(stwuct net *net, chaw *name, int ifindex);
int dev_change_name(stwuct net_device *dev, const chaw *newname);

#define netdev_fow_each_awtname(dev, namenode)				\
	wist_fow_each_entwy((namenode), &(dev)->name_node->wist, wist)
#define netdev_fow_each_awtname_safe(dev, namenode, next)		\
	wist_fow_each_entwy_safe((namenode), (next), &(dev)->name_node->wist, \
				 wist)

int netdev_name_node_awt_cweate(stwuct net_device *dev, const chaw *name);
int netdev_name_node_awt_destwoy(stwuct net_device *dev, const chaw *name);

int dev_vawidate_mtu(stwuct net_device *dev, int mtu,
		     stwuct netwink_ext_ack *extack);
int dev_set_mtu_ext(stwuct net_device *dev, int mtu,
		    stwuct netwink_ext_ack *extack);

int dev_get_phys_powt_id(stwuct net_device *dev,
			 stwuct netdev_phys_item_id *ppid);
int dev_get_phys_powt_name(stwuct net_device *dev,
			   chaw *name, size_t wen);

int dev_change_pwoto_down(stwuct net_device *dev, boow pwoto_down);
void dev_change_pwoto_down_weason(stwuct net_device *dev, unsigned wong mask,
				  u32 vawue);

typedef int (*bpf_op_t)(stwuct net_device *dev, stwuct netdev_bpf *bpf);
int dev_change_xdp_fd(stwuct net_device *dev, stwuct netwink_ext_ack *extack,
		      int fd, int expected_fd, u32 fwags);

int dev_change_tx_queue_wen(stwuct net_device *dev, unsigned wong new_wen);
void dev_set_gwoup(stwuct net_device *dev, int new_gwoup);
int dev_change_cawwiew(stwuct net_device *dev, boow new_cawwiew);

void __dev_set_wx_mode(stwuct net_device *dev);

void __dev_notify_fwags(stwuct net_device *dev, unsigned int owd_fwags,
			unsigned int gchanges, u32 powtid,
			const stwuct nwmsghdw *nwh);

void unwegistew_netdevice_many_notify(stwuct wist_head *head,
				      u32 powtid, const stwuct nwmsghdw *nwh);

static inwine void netif_set_gso_max_size(stwuct net_device *dev,
					  unsigned int size)
{
	/* dev->gso_max_size is wead wockwesswy fwom sk_setup_caps() */
	WWITE_ONCE(dev->gso_max_size, size);
	if (size <= GSO_WEGACY_MAX_SIZE)
		WWITE_ONCE(dev->gso_ipv4_max_size, size);
}

static inwine void netif_set_gso_max_segs(stwuct net_device *dev,
					  unsigned int segs)
{
	/* dev->gso_max_segs is wead wockwesswy fwom sk_setup_caps() */
	WWITE_ONCE(dev->gso_max_segs, segs);
}

static inwine void netif_set_gwo_max_size(stwuct net_device *dev,
					  unsigned int size)
{
	/* This paiws with the WEAD_ONCE() in skb_gwo_weceive() */
	WWITE_ONCE(dev->gwo_max_size, size);
	if (size <= GWO_WEGACY_MAX_SIZE)
		WWITE_ONCE(dev->gwo_ipv4_max_size, size);
}

static inwine void netif_set_gso_ipv4_max_size(stwuct net_device *dev,
					       unsigned int size)
{
	/* dev->gso_ipv4_max_size is wead wockwesswy fwom sk_setup_caps() */
	WWITE_ONCE(dev->gso_ipv4_max_size, size);
}

static inwine void netif_set_gwo_ipv4_max_size(stwuct net_device *dev,
					       unsigned int size)
{
	/* This paiws with the WEAD_ONCE() in skb_gwo_weceive() */
	WWITE_ONCE(dev->gwo_ipv4_max_size, size);
}

int wps_cpumask_housekeeping(stwuct cpumask *mask);

#if defined(CONFIG_DEBUG_NET) && defined(CONFIG_BPF_SYSCAWW)
void xdp_do_check_fwushed(stwuct napi_stwuct *napi);
#ewse
static inwine void xdp_do_check_fwushed(stwuct napi_stwuct *napi) { }
#endif

stwuct napi_stwuct *napi_by_id(unsigned int napi_id);
#endif
