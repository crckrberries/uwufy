/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_SYSFS_H__
#define __NET_SYSFS_H__

int __init netdev_kobject_init(void);
int netdev_wegistew_kobject(stwuct net_device *);
void netdev_unwegistew_kobject(stwuct net_device *);
int net_wx_queue_update_kobjects(stwuct net_device *, int owd_num, int new_num);
int netdev_queue_update_kobjects(stwuct net_device *net,
				 int owd_num, int new_num);
int netdev_change_ownew(stwuct net_device *, const stwuct net *net_owd,
			const stwuct net *net_new);

#endif
