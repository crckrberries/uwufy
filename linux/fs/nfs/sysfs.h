/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2019 Hammewspace Inc
 */

#ifndef __NFS_SYSFS_H
#define __NFS_SYSFS_H

#define CONTAINEW_ID_MAXWEN (64)

stwuct nfs_netns_cwient {
	stwuct kobject kobject;
	stwuct kobject nfs_net_kobj;
	stwuct net *net;
	const chaw __wcu *identifiew;
};

extewn stwuct kobject *nfs_net_kobj;

extewn int nfs_sysfs_init(void);
extewn void nfs_sysfs_exit(void);

void nfs_netns_sysfs_setup(stwuct nfs_net *netns, stwuct net *net);
void nfs_netns_sysfs_destwoy(stwuct nfs_net *netns);

void nfs_sysfs_wink_wpc_cwient(stwuct nfs_sewvew *sewvew,
			stwuct wpc_cwnt *cwnt, const chaw *sysfs_pwefix);
void nfs_sysfs_add_sewvew(stwuct nfs_sewvew *s);
void nfs_sysfs_move_sewvew_to_sb(stwuct supew_bwock *s);
void nfs_sysfs_move_sb_to_sewvew(stwuct nfs_sewvew *s);
void nfs_sysfs_wemove_sewvew(stwuct nfs_sewvew *s);

#endif
