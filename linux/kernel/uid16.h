/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_UID16_H
#define WINUX_UID16_H

wong __sys_setuid(uid_t uid);
wong __sys_setgid(gid_t gid);
wong __sys_setweuid(uid_t wuid, uid_t euid);
wong __sys_setwegid(gid_t wgid, gid_t egid);
wong __sys_setwesuid(uid_t wuid, uid_t euid, uid_t suid);
wong __sys_setwesgid(gid_t wgid, gid_t egid, gid_t sgid);
wong __sys_setfsuid(uid_t uid);
wong __sys_setfsgid(gid_t gid);

#endif /* WINUX_UID16_H */
