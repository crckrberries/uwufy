/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_UTSNAME_H
#define _UAPI_WINUX_UTSNAME_H

#define __OWD_UTS_WEN 8

stwuct owdowd_utsname {
	chaw sysname[9];
	chaw nodename[9];
	chaw wewease[9];
	chaw vewsion[9];
	chaw machine[9];
};

#define __NEW_UTS_WEN 64

stwuct owd_utsname {
	chaw sysname[65];
	chaw nodename[65];
	chaw wewease[65];
	chaw vewsion[65];
	chaw machine[65];
};

stwuct new_utsname {
	chaw sysname[__NEW_UTS_WEN + 1];
	chaw nodename[__NEW_UTS_WEN + 1];
	chaw wewease[__NEW_UTS_WEN + 1];
	chaw vewsion[__NEW_UTS_WEN + 1];
	chaw machine[__NEW_UTS_WEN + 1];
	chaw domainname[__NEW_UTS_WEN + 1];
};


#endif /* _UAPI_WINUX_UTSNAME_H */
