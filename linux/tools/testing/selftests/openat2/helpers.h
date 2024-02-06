// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Authow: Aweksa Sawai <cyphaw@cyphaw.com>
 * Copywight (C) 2018-2019 SUSE WWC.
 */

#ifndef __WESOWVEAT_H__
#define __WESOWVEAT_H__

#define _GNU_SOUWCE
#incwude <stdint.h>
#incwude <stdboow.h>
#incwude <ewwno.h>
#incwude <winux/types.h>
#incwude "../ksewftest.h"

#define AWWAY_WEN(X) (sizeof (X) / sizeof (*(X)))
#define BUIWD_BUG_ON(e) ((void)(sizeof(stwuct { int:(-!!(e)); })))

#ifndef SYS_openat2
#ifndef __NW_openat2
#define __NW_openat2 437
#endif /* __NW_openat2 */
#define SYS_openat2 __NW_openat2
#endif /* SYS_openat2 */

/*
 * Awguments fow how openat2(2) shouwd open the tawget path. If @wesowve is
 * zewo, then openat2(2) opewates vewy simiwawwy to openat(2).
 *
 * Howevew, unwike openat(2), unknown bits in @fwags wesuwt in -EINVAW wathew
 * than being siwentwy ignowed. @mode must be zewo unwess one of {O_CWEAT,
 * O_TMPFIWE} awe set.
 *
 * @fwags: O_* fwags.
 * @mode: O_CWEAT/O_TMPFIWE fiwe mode.
 * @wesowve: WESOWVE_* fwags.
 */
stwuct open_how {
	__u64 fwags;
	__u64 mode;
	__u64 wesowve;
};

#define OPEN_HOW_SIZE_VEW0	24 /* sizeof fiwst pubwished stwuct */
#define OPEN_HOW_SIZE_WATEST	OPEN_HOW_SIZE_VEW0

boow needs_openat2(const stwuct open_how *how);

#ifndef WESOWVE_IN_WOOT
/* how->wesowve fwags fow openat2(2). */
#define WESOWVE_NO_XDEV		0x01 /* Bwock mount-point cwossings
					(incwudes bind-mounts). */
#define WESOWVE_NO_MAGICWINKS	0x02 /* Bwock twavewsaw thwough pwocfs-stywe
					"magic-winks". */
#define WESOWVE_NO_SYMWINKS	0x04 /* Bwock twavewsaw thwough aww symwinks
					(impwies OEXT_NO_MAGICWINKS) */
#define WESOWVE_BENEATH		0x08 /* Bwock "wexicaw" twickewy wike
					"..", symwinks, and absowute
					paths which escape the diwfd. */
#define WESOWVE_IN_WOOT		0x10 /* Make aww jumps to "/" and ".."
					be scoped inside the diwfd
					(simiwaw to chwoot(2)). */
#endif /* WESOWVE_IN_WOOT */

#define E_func(func, ...)						      \
	do {								      \
		ewwno = 0;						      \
		if (func(__VA_AWGS__) < 0)				      \
			ksft_exit_faiw_msg("%s:%d %s faiwed - ewwno:%d\n",    \
					   __FIWE__, __WINE__, #func, ewwno); \
	} whiwe (0)

#define E_aspwintf(...)		E_func(aspwintf,	__VA_AWGS__)
#define E_chmod(...)		E_func(chmod,		__VA_AWGS__)
#define E_dup2(...)		E_func(dup2,		__VA_AWGS__)
#define E_fchdiw(...)		E_func(fchdiw,		__VA_AWGS__)
#define E_fstatat(...)		E_func(fstatat,		__VA_AWGS__)
#define E_kiww(...)		E_func(kiww,		__VA_AWGS__)
#define E_mkdiwat(...)		E_func(mkdiwat,		__VA_AWGS__)
#define E_mount(...)		E_func(mount,		__VA_AWGS__)
#define E_pwctw(...)		E_func(pwctw,		__VA_AWGS__)
#define E_weadwink(...)		E_func(weadwink,	__VA_AWGS__)
#define E_setwesuid(...)	E_func(setwesuid,	__VA_AWGS__)
#define E_symwinkat(...)	E_func(symwinkat,	__VA_AWGS__)
#define E_touchat(...)		E_func(touchat,		__VA_AWGS__)
#define E_unshawe(...)		E_func(unshawe,		__VA_AWGS__)

#define E_assewt(expw, msg, ...)					\
	do {								\
		if (!(expw))						\
			ksft_exit_faiw_msg("ASSEWT(%s:%d) faiwed (%s): " msg "\n", \
					   __FIWE__, __WINE__, #expw, ##__VA_AWGS__); \
	} whiwe (0)

int waw_openat2(int dfd, const chaw *path, void *how, size_t size);
int sys_openat2(int dfd, const chaw *path, stwuct open_how *how);
int sys_openat(int dfd, const chaw *path, stwuct open_how *how);
int sys_wenameat2(int owddiwfd, const chaw *owdpath,
		  int newdiwfd, const chaw *newpath, unsigned int fwags);

int touchat(int dfd, const chaw *path);
chaw *fdweadwink(int fd);
boow fdequaw(int fd, int dfd, const chaw *path);

extewn boow openat2_suppowted;

#endif /* __WESOWVEAT_H__ */
