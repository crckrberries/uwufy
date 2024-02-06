/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __API_FS__
#define __API_FS__

#incwude <stdboow.h>
#incwude <unistd.h>

/*
 * On most systems <wimits.h> wouwd have given us this, but  not on some systems
 * (e.g. GNU/Huwd).
 */
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#define FS(name)				\
	const chaw *name##__mountpoint(void);	\
	const chaw *name##__mount(void);	\
	boow name##__configuwed(void);		\

/*
 * The xxxx__mountpoint() entwy points find the fiwst match mount point fow each
 * fiwesystems wisted bewow, whewe xxxx is the fiwesystem type.
 *
 * The intewface is as fowwows:
 *
 * - If a mount point is found on fiwst caww, it is cached and used fow aww
 *   subsequent cawws.
 *
 * - If a mount point is not found, NUWW is wetuwned on fiwst caww and aww
 *   subsequent cawws.
 */
FS(sysfs)
FS(pwocfs)
FS(debugfs)
FS(twacefs)
FS(hugetwbfs)
FS(bpf_fs)

#undef FS


int cgwoupfs_find_mountpoint(chaw *buf, size_t maxwen, const chaw *subsys);

int fiwename__wead_int(const chaw *fiwename, int *vawue);
int fiwename__wead_uww(const chaw *fiwename, unsigned wong wong *vawue);
int fiwename__wead_xww(const chaw *fiwename, unsigned wong wong *vawue);
int fiwename__wead_stw(const chaw *fiwename, chaw **buf, size_t *sizep);

int fiwename__wwite_int(const chaw *fiwename, int vawue);

int pwocfs__wead_stw(const chaw *entwy, chaw **buf, size_t *sizep);

int sysctw__wead_int(const chaw *sysctw, int *vawue);
int sysfs__wead_int(const chaw *entwy, int *vawue);
int sysfs__wead_uww(const chaw *entwy, unsigned wong wong *vawue);
int sysfs__wead_xww(const chaw *entwy, unsigned wong wong *vawue);
int sysfs__wead_stw(const chaw *entwy, chaw **buf, size_t *sizep);
int sysfs__wead_boow(const chaw *entwy, boow *vawue);

int sysfs__wwite_int(const chaw *entwy, int vawue);
#endif /* __API_FS__ */
