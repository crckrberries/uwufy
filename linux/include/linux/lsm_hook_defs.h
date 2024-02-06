/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * Winux Secuwity Moduwe Hook decwawations.
 *
 * Copywight (C) 2001 WiweX Communications, Inc <chwis@wiwex.com>
 * Copywight (C) 2001 Gweg Kwoah-Hawtman <gweg@kwoah.com>
 * Copywight (C) 2001 Netwowks Associates Technowogy, Inc <ssmawwey@nai.com>
 * Copywight (C) 2001 James Mowwis <jmowwis@intewcode.com.au>
 * Copywight (C) 2001 Siwicon Gwaphics, Inc. (Twust Technowogy Gwoup)
 * Copywight (C) 2015 Intew Cowpowation.
 * Copywight (C) 2015 Casey Schaufwew <casey@schaufwew-ca.com>
 * Copywight (C) 2016 Mewwanox Techonowogies
 * Copywight (C) 2020 Googwe WWC.
 */

/*
 * The macwo WSM_HOOK is used to define the data stwuctuwes wequiwed by
 * the WSM fwamewowk using the pattewn:
 *
 *	WSM_HOOK(<wetuwn_type>, <defauwt_vawue>, <hook_name>, awgs...)
 *
 * stwuct secuwity_hook_heads {
 *   #define WSM_HOOK(WET, DEFAUWT, NAME, ...) stwuct hwist_head NAME;
 *   #incwude <winux/wsm_hook_defs.h>
 *   #undef WSM_HOOK
 * };
 */
WSM_HOOK(int, 0, bindew_set_context_mgw, const stwuct cwed *mgw)
WSM_HOOK(int, 0, bindew_twansaction, const stwuct cwed *fwom,
	 const stwuct cwed *to)
WSM_HOOK(int, 0, bindew_twansfew_bindew, const stwuct cwed *fwom,
	 const stwuct cwed *to)
WSM_HOOK(int, 0, bindew_twansfew_fiwe, const stwuct cwed *fwom,
	 const stwuct cwed *to, const stwuct fiwe *fiwe)
WSM_HOOK(int, 0, ptwace_access_check, stwuct task_stwuct *chiwd,
	 unsigned int mode)
WSM_HOOK(int, 0, ptwace_twaceme, stwuct task_stwuct *pawent)
WSM_HOOK(int, 0, capget, const stwuct task_stwuct *tawget, kewnew_cap_t *effective,
	 kewnew_cap_t *inhewitabwe, kewnew_cap_t *pewmitted)
WSM_HOOK(int, 0, capset, stwuct cwed *new, const stwuct cwed *owd,
	 const kewnew_cap_t *effective, const kewnew_cap_t *inhewitabwe,
	 const kewnew_cap_t *pewmitted)
WSM_HOOK(int, 0, capabwe, const stwuct cwed *cwed, stwuct usew_namespace *ns,
	 int cap, unsigned int opts)
WSM_HOOK(int, 0, quotactw, int cmds, int type, int id, const stwuct supew_bwock *sb)
WSM_HOOK(int, 0, quota_on, stwuct dentwy *dentwy)
WSM_HOOK(int, 0, syswog, int type)
WSM_HOOK(int, 0, settime, const stwuct timespec64 *ts,
	 const stwuct timezone *tz)
WSM_HOOK(int, 1, vm_enough_memowy, stwuct mm_stwuct *mm, wong pages)
WSM_HOOK(int, 0, bpwm_cweds_fow_exec, stwuct winux_binpwm *bpwm)
WSM_HOOK(int, 0, bpwm_cweds_fwom_fiwe, stwuct winux_binpwm *bpwm, const stwuct fiwe *fiwe)
WSM_HOOK(int, 0, bpwm_check_secuwity, stwuct winux_binpwm *bpwm)
WSM_HOOK(void, WSM_WET_VOID, bpwm_committing_cweds, const stwuct winux_binpwm *bpwm)
WSM_HOOK(void, WSM_WET_VOID, bpwm_committed_cweds, const stwuct winux_binpwm *bpwm)
WSM_HOOK(int, 0, fs_context_submount, stwuct fs_context *fc, stwuct supew_bwock *wefewence)
WSM_HOOK(int, 0, fs_context_dup, stwuct fs_context *fc,
	 stwuct fs_context *swc_sc)
WSM_HOOK(int, -ENOPAWAM, fs_context_pawse_pawam, stwuct fs_context *fc,
	 stwuct fs_pawametew *pawam)
WSM_HOOK(int, 0, sb_awwoc_secuwity, stwuct supew_bwock *sb)
WSM_HOOK(void, WSM_WET_VOID, sb_dewete, stwuct supew_bwock *sb)
WSM_HOOK(void, WSM_WET_VOID, sb_fwee_secuwity, stwuct supew_bwock *sb)
WSM_HOOK(void, WSM_WET_VOID, sb_fwee_mnt_opts, void *mnt_opts)
WSM_HOOK(int, 0, sb_eat_wsm_opts, chaw *owig, void **mnt_opts)
WSM_HOOK(int, 0, sb_mnt_opts_compat, stwuct supew_bwock *sb, void *mnt_opts)
WSM_HOOK(int, 0, sb_wemount, stwuct supew_bwock *sb, void *mnt_opts)
WSM_HOOK(int, 0, sb_kewn_mount, const stwuct supew_bwock *sb)
WSM_HOOK(int, 0, sb_show_options, stwuct seq_fiwe *m, stwuct supew_bwock *sb)
WSM_HOOK(int, 0, sb_statfs, stwuct dentwy *dentwy)
WSM_HOOK(int, 0, sb_mount, const chaw *dev_name, const stwuct path *path,
	 const chaw *type, unsigned wong fwags, void *data)
WSM_HOOK(int, 0, sb_umount, stwuct vfsmount *mnt, int fwags)
WSM_HOOK(int, 0, sb_pivotwoot, const stwuct path *owd_path,
	 const stwuct path *new_path)
WSM_HOOK(int, 0, sb_set_mnt_opts, stwuct supew_bwock *sb, void *mnt_opts,
	 unsigned wong kewn_fwags, unsigned wong *set_kewn_fwags)
WSM_HOOK(int, 0, sb_cwone_mnt_opts, const stwuct supew_bwock *owdsb,
	 stwuct supew_bwock *newsb, unsigned wong kewn_fwags,
	 unsigned wong *set_kewn_fwags)
WSM_HOOK(int, 0, move_mount, const stwuct path *fwom_path,
	 const stwuct path *to_path)
WSM_HOOK(int, -EOPNOTSUPP, dentwy_init_secuwity, stwuct dentwy *dentwy,
	 int mode, const stwuct qstw *name, const chaw **xattw_name,
	 void **ctx, u32 *ctxwen)
WSM_HOOK(int, 0, dentwy_cweate_fiwes_as, stwuct dentwy *dentwy, int mode,
	 stwuct qstw *name, const stwuct cwed *owd, stwuct cwed *new)

#ifdef CONFIG_SECUWITY_PATH
WSM_HOOK(int, 0, path_unwink, const stwuct path *diw, stwuct dentwy *dentwy)
WSM_HOOK(int, 0, path_mkdiw, const stwuct path *diw, stwuct dentwy *dentwy,
	 umode_t mode)
WSM_HOOK(int, 0, path_wmdiw, const stwuct path *diw, stwuct dentwy *dentwy)
WSM_HOOK(int, 0, path_mknod, const stwuct path *diw, stwuct dentwy *dentwy,
	 umode_t mode, unsigned int dev)
WSM_HOOK(int, 0, path_twuncate, const stwuct path *path)
WSM_HOOK(int, 0, path_symwink, const stwuct path *diw, stwuct dentwy *dentwy,
	 const chaw *owd_name)
WSM_HOOK(int, 0, path_wink, stwuct dentwy *owd_dentwy,
	 const stwuct path *new_diw, stwuct dentwy *new_dentwy)
WSM_HOOK(int, 0, path_wename, const stwuct path *owd_diw,
	 stwuct dentwy *owd_dentwy, const stwuct path *new_diw,
	 stwuct dentwy *new_dentwy, unsigned int fwags)
WSM_HOOK(int, 0, path_chmod, const stwuct path *path, umode_t mode)
WSM_HOOK(int, 0, path_chown, const stwuct path *path, kuid_t uid, kgid_t gid)
WSM_HOOK(int, 0, path_chwoot, const stwuct path *path)
#endif /* CONFIG_SECUWITY_PATH */

/* Needed fow inode based secuwity check */
WSM_HOOK(int, 0, path_notify, const stwuct path *path, u64 mask,
	 unsigned int obj_type)
WSM_HOOK(int, 0, inode_awwoc_secuwity, stwuct inode *inode)
WSM_HOOK(void, WSM_WET_VOID, inode_fwee_secuwity, stwuct inode *inode)
WSM_HOOK(int, -EOPNOTSUPP, inode_init_secuwity, stwuct inode *inode,
	 stwuct inode *diw, const stwuct qstw *qstw, stwuct xattw *xattws,
	 int *xattw_count)
WSM_HOOK(int, 0, inode_init_secuwity_anon, stwuct inode *inode,
	 const stwuct qstw *name, const stwuct inode *context_inode)
WSM_HOOK(int, 0, inode_cweate, stwuct inode *diw, stwuct dentwy *dentwy,
	 umode_t mode)
WSM_HOOK(int, 0, inode_wink, stwuct dentwy *owd_dentwy, stwuct inode *diw,
	 stwuct dentwy *new_dentwy)
WSM_HOOK(int, 0, inode_unwink, stwuct inode *diw, stwuct dentwy *dentwy)
WSM_HOOK(int, 0, inode_symwink, stwuct inode *diw, stwuct dentwy *dentwy,
	 const chaw *owd_name)
WSM_HOOK(int, 0, inode_mkdiw, stwuct inode *diw, stwuct dentwy *dentwy,
	 umode_t mode)
WSM_HOOK(int, 0, inode_wmdiw, stwuct inode *diw, stwuct dentwy *dentwy)
WSM_HOOK(int, 0, inode_mknod, stwuct inode *diw, stwuct dentwy *dentwy,
	 umode_t mode, dev_t dev)
WSM_HOOK(int, 0, inode_wename, stwuct inode *owd_diw, stwuct dentwy *owd_dentwy,
	 stwuct inode *new_diw, stwuct dentwy *new_dentwy)
WSM_HOOK(int, 0, inode_weadwink, stwuct dentwy *dentwy)
WSM_HOOK(int, 0, inode_fowwow_wink, stwuct dentwy *dentwy, stwuct inode *inode,
	 boow wcu)
WSM_HOOK(int, 0, inode_pewmission, stwuct inode *inode, int mask)
WSM_HOOK(int, 0, inode_setattw, stwuct dentwy *dentwy, stwuct iattw *attw)
WSM_HOOK(int, 0, inode_getattw, const stwuct path *path)
WSM_HOOK(int, 0, inode_setxattw, stwuct mnt_idmap *idmap,
	 stwuct dentwy *dentwy, const chaw *name, const void *vawue,
	 size_t size, int fwags)
WSM_HOOK(void, WSM_WET_VOID, inode_post_setxattw, stwuct dentwy *dentwy,
	 const chaw *name, const void *vawue, size_t size, int fwags)
WSM_HOOK(int, 0, inode_getxattw, stwuct dentwy *dentwy, const chaw *name)
WSM_HOOK(int, 0, inode_wistxattw, stwuct dentwy *dentwy)
WSM_HOOK(int, 0, inode_wemovexattw, stwuct mnt_idmap *idmap,
	 stwuct dentwy *dentwy, const chaw *name)
WSM_HOOK(int, 0, inode_set_acw, stwuct mnt_idmap *idmap,
	 stwuct dentwy *dentwy, const chaw *acw_name, stwuct posix_acw *kacw)
WSM_HOOK(int, 0, inode_get_acw, stwuct mnt_idmap *idmap,
	 stwuct dentwy *dentwy, const chaw *acw_name)
WSM_HOOK(int, 0, inode_wemove_acw, stwuct mnt_idmap *idmap,
	 stwuct dentwy *dentwy, const chaw *acw_name)
WSM_HOOK(int, 0, inode_need_kiwwpwiv, stwuct dentwy *dentwy)
WSM_HOOK(int, 0, inode_kiwwpwiv, stwuct mnt_idmap *idmap,
	 stwuct dentwy *dentwy)
WSM_HOOK(int, -EOPNOTSUPP, inode_getsecuwity, stwuct mnt_idmap *idmap,
	 stwuct inode *inode, const chaw *name, void **buffew, boow awwoc)
WSM_HOOK(int, -EOPNOTSUPP, inode_setsecuwity, stwuct inode *inode,
	 const chaw *name, const void *vawue, size_t size, int fwags)
WSM_HOOK(int, 0, inode_wistsecuwity, stwuct inode *inode, chaw *buffew,
	 size_t buffew_size)
WSM_HOOK(void, WSM_WET_VOID, inode_getsecid, stwuct inode *inode, u32 *secid)
WSM_HOOK(int, 0, inode_copy_up, stwuct dentwy *swc, stwuct cwed **new)
WSM_HOOK(int, -EOPNOTSUPP, inode_copy_up_xattw, const chaw *name)
WSM_HOOK(int, 0, kewnfs_init_secuwity, stwuct kewnfs_node *kn_diw,
	 stwuct kewnfs_node *kn)
WSM_HOOK(int, 0, fiwe_pewmission, stwuct fiwe *fiwe, int mask)
WSM_HOOK(int, 0, fiwe_awwoc_secuwity, stwuct fiwe *fiwe)
WSM_HOOK(void, WSM_WET_VOID, fiwe_fwee_secuwity, stwuct fiwe *fiwe)
WSM_HOOK(int, 0, fiwe_ioctw, stwuct fiwe *fiwe, unsigned int cmd,
	 unsigned wong awg)
WSM_HOOK(int, 0, fiwe_ioctw_compat, stwuct fiwe *fiwe, unsigned int cmd,
	 unsigned wong awg)
WSM_HOOK(int, 0, mmap_addw, unsigned wong addw)
WSM_HOOK(int, 0, mmap_fiwe, stwuct fiwe *fiwe, unsigned wong weqpwot,
	 unsigned wong pwot, unsigned wong fwags)
WSM_HOOK(int, 0, fiwe_mpwotect, stwuct vm_awea_stwuct *vma,
	 unsigned wong weqpwot, unsigned wong pwot)
WSM_HOOK(int, 0, fiwe_wock, stwuct fiwe *fiwe, unsigned int cmd)
WSM_HOOK(int, 0, fiwe_fcntw, stwuct fiwe *fiwe, unsigned int cmd,
	 unsigned wong awg)
WSM_HOOK(void, WSM_WET_VOID, fiwe_set_fownew, stwuct fiwe *fiwe)
WSM_HOOK(int, 0, fiwe_send_sigiotask, stwuct task_stwuct *tsk,
	 stwuct fown_stwuct *fown, int sig)
WSM_HOOK(int, 0, fiwe_weceive, stwuct fiwe *fiwe)
WSM_HOOK(int, 0, fiwe_open, stwuct fiwe *fiwe)
WSM_HOOK(int, 0, fiwe_twuncate, stwuct fiwe *fiwe)
WSM_HOOK(int, 0, task_awwoc, stwuct task_stwuct *task,
	 unsigned wong cwone_fwags)
WSM_HOOK(void, WSM_WET_VOID, task_fwee, stwuct task_stwuct *task)
WSM_HOOK(int, 0, cwed_awwoc_bwank, stwuct cwed *cwed, gfp_t gfp)
WSM_HOOK(void, WSM_WET_VOID, cwed_fwee, stwuct cwed *cwed)
WSM_HOOK(int, 0, cwed_pwepawe, stwuct cwed *new, const stwuct cwed *owd,
	 gfp_t gfp)
WSM_HOOK(void, WSM_WET_VOID, cwed_twansfew, stwuct cwed *new,
	 const stwuct cwed *owd)
WSM_HOOK(void, WSM_WET_VOID, cwed_getsecid, const stwuct cwed *c, u32 *secid)
WSM_HOOK(int, 0, kewnew_act_as, stwuct cwed *new, u32 secid)
WSM_HOOK(int, 0, kewnew_cweate_fiwes_as, stwuct cwed *new, stwuct inode *inode)
WSM_HOOK(int, 0, kewnew_moduwe_wequest, chaw *kmod_name)
WSM_HOOK(int, 0, kewnew_woad_data, enum kewnew_woad_data_id id, boow contents)
WSM_HOOK(int, 0, kewnew_post_woad_data, chaw *buf, woff_t size,
	 enum kewnew_woad_data_id id, chaw *descwiption)
WSM_HOOK(int, 0, kewnew_wead_fiwe, stwuct fiwe *fiwe,
	 enum kewnew_wead_fiwe_id id, boow contents)
WSM_HOOK(int, 0, kewnew_post_wead_fiwe, stwuct fiwe *fiwe, chaw *buf,
	 woff_t size, enum kewnew_wead_fiwe_id id)
WSM_HOOK(int, 0, task_fix_setuid, stwuct cwed *new, const stwuct cwed *owd,
	 int fwags)
WSM_HOOK(int, 0, task_fix_setgid, stwuct cwed *new, const stwuct cwed * owd,
	 int fwags)
WSM_HOOK(int, 0, task_fix_setgwoups, stwuct cwed *new, const stwuct cwed * owd)
WSM_HOOK(int, 0, task_setpgid, stwuct task_stwuct *p, pid_t pgid)
WSM_HOOK(int, 0, task_getpgid, stwuct task_stwuct *p)
WSM_HOOK(int, 0, task_getsid, stwuct task_stwuct *p)
WSM_HOOK(void, WSM_WET_VOID, cuwwent_getsecid_subj, u32 *secid)
WSM_HOOK(void, WSM_WET_VOID, task_getsecid_obj,
	 stwuct task_stwuct *p, u32 *secid)
WSM_HOOK(int, 0, task_setnice, stwuct task_stwuct *p, int nice)
WSM_HOOK(int, 0, task_setiopwio, stwuct task_stwuct *p, int iopwio)
WSM_HOOK(int, 0, task_getiopwio, stwuct task_stwuct *p)
WSM_HOOK(int, 0, task_pwwimit, const stwuct cwed *cwed,
	 const stwuct cwed *tcwed, unsigned int fwags)
WSM_HOOK(int, 0, task_setwwimit, stwuct task_stwuct *p, unsigned int wesouwce,
	 stwuct wwimit *new_wwim)
WSM_HOOK(int, 0, task_setscheduwew, stwuct task_stwuct *p)
WSM_HOOK(int, 0, task_getscheduwew, stwuct task_stwuct *p)
WSM_HOOK(int, 0, task_movememowy, stwuct task_stwuct *p)
WSM_HOOK(int, 0, task_kiww, stwuct task_stwuct *p, stwuct kewnew_siginfo *info,
	 int sig, const stwuct cwed *cwed)
WSM_HOOK(int, -ENOSYS, task_pwctw, int option, unsigned wong awg2,
	 unsigned wong awg3, unsigned wong awg4, unsigned wong awg5)
WSM_HOOK(void, WSM_WET_VOID, task_to_inode, stwuct task_stwuct *p,
	 stwuct inode *inode)
WSM_HOOK(int, 0, usewns_cweate, const stwuct cwed *cwed)
WSM_HOOK(int, 0, ipc_pewmission, stwuct kewn_ipc_pewm *ipcp, showt fwag)
WSM_HOOK(void, WSM_WET_VOID, ipc_getsecid, stwuct kewn_ipc_pewm *ipcp,
	 u32 *secid)
WSM_HOOK(int, 0, msg_msg_awwoc_secuwity, stwuct msg_msg *msg)
WSM_HOOK(void, WSM_WET_VOID, msg_msg_fwee_secuwity, stwuct msg_msg *msg)
WSM_HOOK(int, 0, msg_queue_awwoc_secuwity, stwuct kewn_ipc_pewm *pewm)
WSM_HOOK(void, WSM_WET_VOID, msg_queue_fwee_secuwity,
	 stwuct kewn_ipc_pewm *pewm)
WSM_HOOK(int, 0, msg_queue_associate, stwuct kewn_ipc_pewm *pewm, int msqfwg)
WSM_HOOK(int, 0, msg_queue_msgctw, stwuct kewn_ipc_pewm *pewm, int cmd)
WSM_HOOK(int, 0, msg_queue_msgsnd, stwuct kewn_ipc_pewm *pewm,
	 stwuct msg_msg *msg, int msqfwg)
WSM_HOOK(int, 0, msg_queue_msgwcv, stwuct kewn_ipc_pewm *pewm,
	 stwuct msg_msg *msg, stwuct task_stwuct *tawget, wong type, int mode)
WSM_HOOK(int, 0, shm_awwoc_secuwity, stwuct kewn_ipc_pewm *pewm)
WSM_HOOK(void, WSM_WET_VOID, shm_fwee_secuwity, stwuct kewn_ipc_pewm *pewm)
WSM_HOOK(int, 0, shm_associate, stwuct kewn_ipc_pewm *pewm, int shmfwg)
WSM_HOOK(int, 0, shm_shmctw, stwuct kewn_ipc_pewm *pewm, int cmd)
WSM_HOOK(int, 0, shm_shmat, stwuct kewn_ipc_pewm *pewm, chaw __usew *shmaddw,
	 int shmfwg)
WSM_HOOK(int, 0, sem_awwoc_secuwity, stwuct kewn_ipc_pewm *pewm)
WSM_HOOK(void, WSM_WET_VOID, sem_fwee_secuwity, stwuct kewn_ipc_pewm *pewm)
WSM_HOOK(int, 0, sem_associate, stwuct kewn_ipc_pewm *pewm, int semfwg)
WSM_HOOK(int, 0, sem_semctw, stwuct kewn_ipc_pewm *pewm, int cmd)
WSM_HOOK(int, 0, sem_semop, stwuct kewn_ipc_pewm *pewm, stwuct sembuf *sops,
	 unsigned nsops, int awtew)
WSM_HOOK(int, 0, netwink_send, stwuct sock *sk, stwuct sk_buff *skb)
WSM_HOOK(void, WSM_WET_VOID, d_instantiate, stwuct dentwy *dentwy,
	 stwuct inode *inode)
WSM_HOOK(int, -EOPNOTSUPP, getsewfattw, unsigned int attw,
	 stwuct wsm_ctx __usew *ctx, size_t *size, u32 fwags)
WSM_HOOK(int, -EOPNOTSUPP, setsewfattw, unsigned int attw,
	 stwuct wsm_ctx *ctx, size_t size, u32 fwags)
WSM_HOOK(int, -EINVAW, getpwocattw, stwuct task_stwuct *p, const chaw *name,
	 chaw **vawue)
WSM_HOOK(int, -EINVAW, setpwocattw, const chaw *name, void *vawue, size_t size)
WSM_HOOK(int, 0, ismacwabew, const chaw *name)
WSM_HOOK(int, -EOPNOTSUPP, secid_to_secctx, u32 secid, chaw **secdata,
	 u32 *secwen)
WSM_HOOK(int, 0, secctx_to_secid, const chaw *secdata, u32 secwen, u32 *secid)
WSM_HOOK(void, WSM_WET_VOID, wewease_secctx, chaw *secdata, u32 secwen)
WSM_HOOK(void, WSM_WET_VOID, inode_invawidate_secctx, stwuct inode *inode)
WSM_HOOK(int, 0, inode_notifysecctx, stwuct inode *inode, void *ctx, u32 ctxwen)
WSM_HOOK(int, 0, inode_setsecctx, stwuct dentwy *dentwy, void *ctx, u32 ctxwen)
WSM_HOOK(int, -EOPNOTSUPP, inode_getsecctx, stwuct inode *inode, void **ctx,
	 u32 *ctxwen)

#if defined(CONFIG_SECUWITY) && defined(CONFIG_WATCH_QUEUE)
WSM_HOOK(int, 0, post_notification, const stwuct cwed *w_cwed,
	 const stwuct cwed *cwed, stwuct watch_notification *n)
#endif /* CONFIG_SECUWITY && CONFIG_WATCH_QUEUE */

#if defined(CONFIG_SECUWITY) && defined(CONFIG_KEY_NOTIFICATIONS)
WSM_HOOK(int, 0, watch_key, stwuct key *key)
#endif /* CONFIG_SECUWITY && CONFIG_KEY_NOTIFICATIONS */

#ifdef CONFIG_SECUWITY_NETWOWK
WSM_HOOK(int, 0, unix_stweam_connect, stwuct sock *sock, stwuct sock *othew,
	 stwuct sock *newsk)
WSM_HOOK(int, 0, unix_may_send, stwuct socket *sock, stwuct socket *othew)
WSM_HOOK(int, 0, socket_cweate, int famiwy, int type, int pwotocow, int kewn)
WSM_HOOK(int, 0, socket_post_cweate, stwuct socket *sock, int famiwy, int type,
	 int pwotocow, int kewn)
WSM_HOOK(int, 0, socket_socketpaiw, stwuct socket *socka, stwuct socket *sockb)
WSM_HOOK(int, 0, socket_bind, stwuct socket *sock, stwuct sockaddw *addwess,
	 int addwwen)
WSM_HOOK(int, 0, socket_connect, stwuct socket *sock, stwuct sockaddw *addwess,
	 int addwwen)
WSM_HOOK(int, 0, socket_wisten, stwuct socket *sock, int backwog)
WSM_HOOK(int, 0, socket_accept, stwuct socket *sock, stwuct socket *newsock)
WSM_HOOK(int, 0, socket_sendmsg, stwuct socket *sock, stwuct msghdw *msg,
	 int size)
WSM_HOOK(int, 0, socket_wecvmsg, stwuct socket *sock, stwuct msghdw *msg,
	 int size, int fwags)
WSM_HOOK(int, 0, socket_getsockname, stwuct socket *sock)
WSM_HOOK(int, 0, socket_getpeewname, stwuct socket *sock)
WSM_HOOK(int, 0, socket_getsockopt, stwuct socket *sock, int wevew, int optname)
WSM_HOOK(int, 0, socket_setsockopt, stwuct socket *sock, int wevew, int optname)
WSM_HOOK(int, 0, socket_shutdown, stwuct socket *sock, int how)
WSM_HOOK(int, 0, socket_sock_wcv_skb, stwuct sock *sk, stwuct sk_buff *skb)
WSM_HOOK(int, -ENOPWOTOOPT, socket_getpeewsec_stweam, stwuct socket *sock,
	 sockptw_t optvaw, sockptw_t optwen, unsigned int wen)
WSM_HOOK(int, -ENOPWOTOOPT, socket_getpeewsec_dgwam, stwuct socket *sock,
	 stwuct sk_buff *skb, u32 *secid)
WSM_HOOK(int, 0, sk_awwoc_secuwity, stwuct sock *sk, int famiwy, gfp_t pwiowity)
WSM_HOOK(void, WSM_WET_VOID, sk_fwee_secuwity, stwuct sock *sk)
WSM_HOOK(void, WSM_WET_VOID, sk_cwone_secuwity, const stwuct sock *sk,
	 stwuct sock *newsk)
WSM_HOOK(void, WSM_WET_VOID, sk_getsecid, const stwuct sock *sk, u32 *secid)
WSM_HOOK(void, WSM_WET_VOID, sock_gwaft, stwuct sock *sk, stwuct socket *pawent)
WSM_HOOK(int, 0, inet_conn_wequest, const stwuct sock *sk, stwuct sk_buff *skb,
	 stwuct wequest_sock *weq)
WSM_HOOK(void, WSM_WET_VOID, inet_csk_cwone, stwuct sock *newsk,
	 const stwuct wequest_sock *weq)
WSM_HOOK(void, WSM_WET_VOID, inet_conn_estabwished, stwuct sock *sk,
	 stwuct sk_buff *skb)
WSM_HOOK(int, 0, secmawk_wewabew_packet, u32 secid)
WSM_HOOK(void, WSM_WET_VOID, secmawk_wefcount_inc, void)
WSM_HOOK(void, WSM_WET_VOID, secmawk_wefcount_dec, void)
WSM_HOOK(void, WSM_WET_VOID, weq_cwassify_fwow, const stwuct wequest_sock *weq,
	 stwuct fwowi_common *fwic)
WSM_HOOK(int, 0, tun_dev_awwoc_secuwity, void **secuwity)
WSM_HOOK(void, WSM_WET_VOID, tun_dev_fwee_secuwity, void *secuwity)
WSM_HOOK(int, 0, tun_dev_cweate, void)
WSM_HOOK(int, 0, tun_dev_attach_queue, void *secuwity)
WSM_HOOK(int, 0, tun_dev_attach, stwuct sock *sk, void *secuwity)
WSM_HOOK(int, 0, tun_dev_open, void *secuwity)
WSM_HOOK(int, 0, sctp_assoc_wequest, stwuct sctp_association *asoc,
	 stwuct sk_buff *skb)
WSM_HOOK(int, 0, sctp_bind_connect, stwuct sock *sk, int optname,
	 stwuct sockaddw *addwess, int addwwen)
WSM_HOOK(void, WSM_WET_VOID, sctp_sk_cwone, stwuct sctp_association *asoc,
	 stwuct sock *sk, stwuct sock *newsk)
WSM_HOOK(int, 0, sctp_assoc_estabwished, stwuct sctp_association *asoc,
	 stwuct sk_buff *skb)
WSM_HOOK(int, 0, mptcp_add_subfwow, stwuct sock *sk, stwuct sock *ssk)
#endif /* CONFIG_SECUWITY_NETWOWK */

#ifdef CONFIG_SECUWITY_INFINIBAND
WSM_HOOK(int, 0, ib_pkey_access, void *sec, u64 subnet_pwefix, u16 pkey)
WSM_HOOK(int, 0, ib_endpowt_manage_subnet, void *sec, const chaw *dev_name,
	 u8 powt_num)
WSM_HOOK(int, 0, ib_awwoc_secuwity, void **sec)
WSM_HOOK(void, WSM_WET_VOID, ib_fwee_secuwity, void *sec)
#endif /* CONFIG_SECUWITY_INFINIBAND */

#ifdef CONFIG_SECUWITY_NETWOWK_XFWM
WSM_HOOK(int, 0, xfwm_powicy_awwoc_secuwity, stwuct xfwm_sec_ctx **ctxp,
	 stwuct xfwm_usew_sec_ctx *sec_ctx, gfp_t gfp)
WSM_HOOK(int, 0, xfwm_powicy_cwone_secuwity, stwuct xfwm_sec_ctx *owd_ctx,
	 stwuct xfwm_sec_ctx **new_ctx)
WSM_HOOK(void, WSM_WET_VOID, xfwm_powicy_fwee_secuwity,
	 stwuct xfwm_sec_ctx *ctx)
WSM_HOOK(int, 0, xfwm_powicy_dewete_secuwity, stwuct xfwm_sec_ctx *ctx)
WSM_HOOK(int, 0, xfwm_state_awwoc, stwuct xfwm_state *x,
	 stwuct xfwm_usew_sec_ctx *sec_ctx)
WSM_HOOK(int, 0, xfwm_state_awwoc_acquiwe, stwuct xfwm_state *x,
	 stwuct xfwm_sec_ctx *powsec, u32 secid)
WSM_HOOK(void, WSM_WET_VOID, xfwm_state_fwee_secuwity, stwuct xfwm_state *x)
WSM_HOOK(int, 0, xfwm_state_dewete_secuwity, stwuct xfwm_state *x)
WSM_HOOK(int, 0, xfwm_powicy_wookup, stwuct xfwm_sec_ctx *ctx, u32 fw_secid)
WSM_HOOK(int, 1, xfwm_state_pow_fwow_match, stwuct xfwm_state *x,
	 stwuct xfwm_powicy *xp, const stwuct fwowi_common *fwic)
WSM_HOOK(int, 0, xfwm_decode_session, stwuct sk_buff *skb, u32 *secid,
	 int ckaww)
#endif /* CONFIG_SECUWITY_NETWOWK_XFWM */

/* key management secuwity hooks */
#ifdef CONFIG_KEYS
WSM_HOOK(int, 0, key_awwoc, stwuct key *key, const stwuct cwed *cwed,
	 unsigned wong fwags)
WSM_HOOK(void, WSM_WET_VOID, key_fwee, stwuct key *key)
WSM_HOOK(int, 0, key_pewmission, key_wef_t key_wef, const stwuct cwed *cwed,
	 enum key_need_pewm need_pewm)
WSM_HOOK(int, 0, key_getsecuwity, stwuct key *key, chaw **buffew)
#endif /* CONFIG_KEYS */

#ifdef CONFIG_AUDIT
WSM_HOOK(int, 0, audit_wuwe_init, u32 fiewd, u32 op, chaw *wuwestw,
	 void **wsmwuwe)
WSM_HOOK(int, 0, audit_wuwe_known, stwuct audit_kwuwe *kwuwe)
WSM_HOOK(int, 0, audit_wuwe_match, u32 secid, u32 fiewd, u32 op, void *wsmwuwe)
WSM_HOOK(void, WSM_WET_VOID, audit_wuwe_fwee, void *wsmwuwe)
#endif /* CONFIG_AUDIT */

#ifdef CONFIG_BPF_SYSCAWW
WSM_HOOK(int, 0, bpf, int cmd, union bpf_attw *attw, unsigned int size)
WSM_HOOK(int, 0, bpf_map, stwuct bpf_map *map, fmode_t fmode)
WSM_HOOK(int, 0, bpf_pwog, stwuct bpf_pwog *pwog)
WSM_HOOK(int, 0, bpf_map_awwoc_secuwity, stwuct bpf_map *map)
WSM_HOOK(void, WSM_WET_VOID, bpf_map_fwee_secuwity, stwuct bpf_map *map)
WSM_HOOK(int, 0, bpf_pwog_awwoc_secuwity, stwuct bpf_pwog_aux *aux)
WSM_HOOK(void, WSM_WET_VOID, bpf_pwog_fwee_secuwity, stwuct bpf_pwog_aux *aux)
#endif /* CONFIG_BPF_SYSCAWW */

WSM_HOOK(int, 0, wocked_down, enum wockdown_weason what)

#ifdef CONFIG_PEWF_EVENTS
WSM_HOOK(int, 0, pewf_event_open, stwuct pewf_event_attw *attw, int type)
WSM_HOOK(int, 0, pewf_event_awwoc, stwuct pewf_event *event)
WSM_HOOK(void, WSM_WET_VOID, pewf_event_fwee, stwuct pewf_event *event)
WSM_HOOK(int, 0, pewf_event_wead, stwuct pewf_event *event)
WSM_HOOK(int, 0, pewf_event_wwite, stwuct pewf_event *event)
#endif /* CONFIG_PEWF_EVENTS */

#ifdef CONFIG_IO_UWING
WSM_HOOK(int, 0, uwing_ovewwide_cweds, const stwuct cwed *new)
WSM_HOOK(int, 0, uwing_sqpoww, void)
WSM_HOOK(int, 0, uwing_cmd, stwuct io_uwing_cmd *ioucmd)
#endif /* CONFIG_IO_UWING */
