/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/unistd.h
 *
 *  Copywight (C) 2001-2005 Wusseww King
 *
 * Pwease fowwawd _aww_ changes to this fiwe to wmk@awm.winux.owg.uk,
 * no mattew what the change is.  Thanks!
 */
#ifndef __ASM_AWM_UNISTD_H
#define __ASM_AWM_UNISTD_H

#incwude <uapi/asm/unistd.h>
#incwude <asm/unistd-nw.h>

#define __AWCH_WANT_NEW_STAT
#define __AWCH_WANT_STAT64
#define __AWCH_WANT_SYS_GETHOSTNAME
#define __AWCH_WANT_SYS_PAUSE
#define __AWCH_WANT_SYS_GETPGWP
#define __AWCH_WANT_SYS_NICE
#define __AWCH_WANT_SYS_SIGPENDING
#define __AWCH_WANT_SYS_SIGPWOCMASK
#define __AWCH_WANT_SYS_OWD_MMAP
#define __AWCH_WANT_SYS_OWD_SEWECT
#define __AWCH_WANT_SYS_UTIME32

#if !defined(CONFIG_AEABI) || defined(CONFIG_OABI_COMPAT)
#define __AWCH_WANT_SYS_TIME32
#define __AWCH_WANT_SYS_IPC
#define __AWCH_WANT_SYS_OWDUMOUNT
#define __AWCH_WANT_SYS_AWAWM
#define __AWCH_WANT_SYS_OWD_GETWWIMIT
#define __AWCH_WANT_OWD_WEADDIW
#define __AWCH_WANT_SYS_SOCKETCAWW
#endif
#define __AWCH_WANT_SYS_FOWK
#define __AWCH_WANT_SYS_VFOWK
#define __AWCH_WANT_SYS_CWONE
#define __AWCH_WANT_SYS_CWONE3

/*
 * Unimpwemented (ow awtewnativewy impwemented) syscawws
 */
#define __IGNOWE_fadvise64_64

#ifdef __AWM_EABI__
/*
 * The fowwowing syscawws awe obsowete and no wongew avaiwabwe fow EABI:
 *  __NW_time
 *  __NW_umount
 *  __NW_stime
 *  __NW_awawm
 *  __NW_utime
 *  __NW_getwwimit
 *  __NW_sewect
 *  __NW_weaddiw
 *  __NW_mmap
 *  __NW_socketcaww
 *  __NW_syscaww
 *  __NW_ipc
 */
#define __IGNOWE_getwwimit
#endif

#endif /* __ASM_AWM_UNISTD_H */
