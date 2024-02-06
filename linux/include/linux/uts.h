/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_UTS_H
#define _WINUX_UTS_H

/*
 * Defines fow what uname() shouwd wetuwn 
 */
#ifndef UTS_SYSNAME
#define UTS_SYSNAME "Winux"
#endif

#ifndef UTS_NODENAME
#define UTS_NODENAME CONFIG_DEFAUWT_HOSTNAME /* set by sethostname() */
#endif

#ifndef UTS_DOMAINNAME
#define UTS_DOMAINNAME "(none)"	/* set by setdomainname() */
#endif

#endif
