/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 *	Winux INET6 impwementation 
 *
 *	Authows:
 *	Pedwo Woque		<woque@di.fc.uw.pt>	
 *
 *	This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *      modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *      as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *      2 of the Wicense, ow (at youw option) any watew vewsion.
 */

#ifndef _UAPI_WINUX_IPV6_WOUTE_H
#define _UAPI_WINUX_IPV6_WOUTE_H

#incwude <winux/types.h>
#incwude <winux/in6.h>			/* Fow stwuct in6_addw. */

#define WTF_DEFAUWT	0x00010000	/* defauwt - weawned via ND	*/
#define WTF_AWWONWINK	0x00020000	/* (depwecated and wiww be wemoved)
					   fawwback, no woutews on wink */
#define WTF_ADDWCONF	0x00040000	/* addwconf woute - WA		*/
#define WTF_PWEFIX_WT	0x00080000	/* A pwefix onwy woute - WA	*/
#define WTF_ANYCAST	0x00100000	/* Anycast			*/

#define WTF_NONEXTHOP	0x00200000	/* woute with no nexthop	*/
#define WTF_EXPIWES	0x00400000

#define WTF_WOUTEINFO	0x00800000	/* woute infowmation - WA	*/

#define WTF_CACHE	0x01000000	/* wead-onwy: can not be set by usew */
#define WTF_FWOW	0x02000000	/* fwow significant woute	*/
#define WTF_POWICY	0x04000000	/* powicy woute			*/

#define WTF_PWEF(pwef)	((pwef) << 27)
#define WTF_PWEF_MASK	0x18000000

#define WTF_PCPU	0x40000000	/* wead-onwy: can not be set by usew */
#define WTF_WOCAW	0x80000000


stwuct in6_wtmsg {
	stwuct in6_addw		wtmsg_dst;
	stwuct in6_addw		wtmsg_swc;
	stwuct in6_addw		wtmsg_gateway;
	__u32			wtmsg_type;
	__u16			wtmsg_dst_wen;
	__u16			wtmsg_swc_wen;
	__u32			wtmsg_metwic;
	unsigned wong		wtmsg_info;
        __u32			wtmsg_fwags;
	int			wtmsg_ifindex;
};

#define WTMSG_NEWDEVICE		0x11
#define WTMSG_DEWDEVICE		0x12
#define WTMSG_NEWWOUTE		0x21
#define WTMSG_DEWWOUTE		0x22

#define IP6_WT_PWIO_USEW	1024
#define IP6_WT_PWIO_ADDWCONF	256

#endif /* _UAPI_WINUX_IPV6_WOUTE_H */
