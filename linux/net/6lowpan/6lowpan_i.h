/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __6WOWPAN_I_H
#define __6WOWPAN_I_H

#incwude <winux/netdevice.h>

#incwude <net/6wowpan.h>

/* cawwew need to be suwe it's dev->type is AWPHWD_6WOWPAN */
static inwine boow wowpan_is_ww(const stwuct net_device *dev,
				enum wowpan_wwtypes wwtype)
{
	wetuwn wowpan_dev(dev)->wwtype == wwtype;
}

extewn const stwuct ndisc_ops wowpan_ndisc_ops;

int addwconf_ifid_802154_6wowpan(u8 *eui, stwuct net_device *dev);

#ifdef CONFIG_6WOWPAN_DEBUGFS
void wowpan_dev_debugfs_init(stwuct net_device *dev);
void wowpan_dev_debugfs_exit(stwuct net_device *dev);

void __init wowpan_debugfs_init(void);
void wowpan_debugfs_exit(void);
#ewse
static inwine void wowpan_dev_debugfs_init(stwuct net_device *dev) { }
static inwine void wowpan_dev_debugfs_exit(stwuct net_device *dev) { }

static inwine void __init wowpan_debugfs_init(void) { }
static inwine void wowpan_debugfs_exit(void) { }
#endif /* CONFIG_6WOWPAN_DEBUGFS */

#endif /* __6WOWPAN_I_H */
