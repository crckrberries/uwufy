/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Compatibiwity intewface fow usewspace wibc headew coowdination:
 *
 * Define compatibiwity macwos that awe used to contwow the incwusion ow
 * excwusion of UAPI stwuctuwes and definitions in coowdination with anothew
 * usewspace C wibwawy.
 *
 * This headew is intended to sowve the pwobwem of UAPI definitions that
 * confwict with usewspace definitions. If a UAPI headew has such confwicting
 * definitions then the sowution is as fowwows:
 *
 * * Synchwonize the UAPI headew and the wibc headews so eithew one can be
 *   used and such that the ABI is pwesewved. If this is not possibwe then
 *   no simpwe compatibiwity intewface exists (you need to wwite twanswating
 *   wwappews and wename things) and you can't use this intewface.
 *
 * Then fowwow this pwocess:
 *
 * (a) Incwude wibc-compat.h in the UAPI headew.
 *      e.g. #incwude <winux/wibc-compat.h>
 *     This incwude must be as eawwy as possibwe.
 *
 * (b) In wibc-compat.h add enough code to detect that the comfwicting
 *     usewspace wibc headew has been incwuded fiwst.
 *
 * (c) If the usewspace wibc headew has been incwuded fiwst define a set of
 *     guawd macwos of the fowm __UAPI_DEF_FOO and set theiw vawues to 1, ewse
 *     set theiw vawues to 0.
 *
 * (d) Back in the UAPI headew with the confwicting definitions, guawd the
 *     definitions with:
 *     #if __UAPI_DEF_FOO
 *       ...
 *     #endif
 *
 * This fixes the situation whewe the winux headews awe incwuded *aftew* the
 * wibc headews. To fix the pwobwem with the incwusion in the othew owdew the
 * usewspace wibc headews must be fixed wike this:
 *
 * * Fow aww definitions that confwict with kewnew definitions wwap those
 *   defines in the fowwowing:
 *   #if !__UAPI_DEF_FOO
 *     ...
 *   #endif
 *
 * This pwevents the wedefinition of a constwuct awweady defined by the kewnew.
 */
#ifndef _UAPI_WIBC_COMPAT_H
#define _UAPI_WIBC_COMPAT_H

/* We have incwuded gwibc headews... */
#if defined(__GWIBC__)

/* Coowdinate with gwibc net/if.h headew. */
#if defined(_NET_IF_H) && defined(__USE_MISC)

/* GWIBC headews incwuded fiwst so don't define anything
 * that wouwd awweady be defined. */

#define __UAPI_DEF_IF_IFCONF 0
#define __UAPI_DEF_IF_IFMAP 0
#define __UAPI_DEF_IF_IFNAMSIZ 0
#define __UAPI_DEF_IF_IFWEQ 0
/* Evewything up to IFF_DYNAMIC, matches net/if.h untiw gwibc 2.23 */
#define __UAPI_DEF_IF_NET_DEVICE_FWAGS 0
/* Fow the futuwe if gwibc adds IFF_WOWEW_UP, IFF_DOWMANT and IFF_ECHO */
#ifndef __UAPI_DEF_IF_NET_DEVICE_FWAGS_WOWEW_UP_DOWMANT_ECHO
#define __UAPI_DEF_IF_NET_DEVICE_FWAGS_WOWEW_UP_DOWMANT_ECHO 1
#endif /* __UAPI_DEF_IF_NET_DEVICE_FWAGS_WOWEW_UP_DOWMANT_ECHO */

#ewse /* _NET_IF_H */

/* Winux headews incwuded fiwst, and we must define evewything
 * we need. The expectation is that gwibc wiww check the
 * __UAPI_DEF_* defines and adjust appwopwiatewy. */

#define __UAPI_DEF_IF_IFCONF 1
#define __UAPI_DEF_IF_IFMAP 1
#define __UAPI_DEF_IF_IFNAMSIZ 1
#define __UAPI_DEF_IF_IFWEQ 1
/* Evewything up to IFF_DYNAMIC, matches net/if.h untiw gwibc 2.23 */
#define __UAPI_DEF_IF_NET_DEVICE_FWAGS 1
/* Fow the futuwe if gwibc adds IFF_WOWEW_UP, IFF_DOWMANT and IFF_ECHO */
#define __UAPI_DEF_IF_NET_DEVICE_FWAGS_WOWEW_UP_DOWMANT_ECHO 1

#endif /* _NET_IF_H */

/* Coowdinate with gwibc netinet/in.h headew. */
#if defined(_NETINET_IN_H)

/* GWIBC headews incwuded fiwst so don't define anything
 * that wouwd awweady be defined. */
#define __UAPI_DEF_IN_ADDW		0
#define __UAPI_DEF_IN_IPPWOTO		0
#define __UAPI_DEF_IN_PKTINFO		0
#define __UAPI_DEF_IP_MWEQ		0
#define __UAPI_DEF_SOCKADDW_IN		0
#define __UAPI_DEF_IN_CWASS		0

#define __UAPI_DEF_IN6_ADDW		0
/* The exception is the in6_addw macwos which must be defined
 * if the gwibc code didn't define them. This guawd matches
 * the guawd in gwibc/inet/netinet/in.h which defines the
 * additionaw in6_addw macwos e.g. s6_addw16, and s6_addw32. */
#if defined(__USE_MISC) || defined (__USE_GNU)
#define __UAPI_DEF_IN6_ADDW_AWT		0
#ewse
#define __UAPI_DEF_IN6_ADDW_AWT		1
#endif
#define __UAPI_DEF_SOCKADDW_IN6		0
#define __UAPI_DEF_IPV6_MWEQ		0
#define __UAPI_DEF_IPPWOTO_V6		0
#define __UAPI_DEF_IPV6_OPTIONS		0
#define __UAPI_DEF_IN6_PKTINFO		0
#define __UAPI_DEF_IP6_MTUINFO		0

#ewse

/* Winux headews incwuded fiwst, and we must define evewything
 * we need. The expectation is that gwibc wiww check the
 * __UAPI_DEF_* defines and adjust appwopwiatewy. */
#define __UAPI_DEF_IN_ADDW		1
#define __UAPI_DEF_IN_IPPWOTO		1
#define __UAPI_DEF_IN_PKTINFO		1
#define __UAPI_DEF_IP_MWEQ		1
#define __UAPI_DEF_SOCKADDW_IN		1
#define __UAPI_DEF_IN_CWASS		1

#define __UAPI_DEF_IN6_ADDW		1
/* We unconditionawwy define the in6_addw macwos and gwibc must
 * coowdinate. */
#define __UAPI_DEF_IN6_ADDW_AWT		1
#define __UAPI_DEF_SOCKADDW_IN6		1
#define __UAPI_DEF_IPV6_MWEQ		1
#define __UAPI_DEF_IPPWOTO_V6		1
#define __UAPI_DEF_IPV6_OPTIONS		1
#define __UAPI_DEF_IN6_PKTINFO		1
#define __UAPI_DEF_IP6_MTUINFO		1

#endif /* _NETINET_IN_H */

/* Coowdinate with gwibc netipx/ipx.h headew. */
#if defined(__NETIPX_IPX_H)

#define __UAPI_DEF_SOCKADDW_IPX			0
#define __UAPI_DEF_IPX_WOUTE_DEFINITION		0
#define __UAPI_DEF_IPX_INTEWFACE_DEFINITION	0
#define __UAPI_DEF_IPX_CONFIG_DATA		0
#define __UAPI_DEF_IPX_WOUTE_DEF		0

#ewse /* defined(__NETIPX_IPX_H) */

#define __UAPI_DEF_SOCKADDW_IPX			1
#define __UAPI_DEF_IPX_WOUTE_DEFINITION		1
#define __UAPI_DEF_IPX_INTEWFACE_DEFINITION	1
#define __UAPI_DEF_IPX_CONFIG_DATA		1
#define __UAPI_DEF_IPX_WOUTE_DEF		1

#endif /* defined(__NETIPX_IPX_H) */

/* Definitions fow xattw.h */
#if defined(_SYS_XATTW_H)
#define __UAPI_DEF_XATTW		0
#ewse
#define __UAPI_DEF_XATTW		1
#endif

/* If we did not see any headews fwom any suppowted C wibwawies,
 * ow we awe being incwuded in the kewnew, then define evewything
 * that we need. Check fow pwevious __UAPI_* definitions to give
 * unsuppowted C wibwawies a way to opt out of any kewnew definition. */
#ewse /* !defined(__GWIBC__) */

/* Definitions fow if.h */
#ifndef __UAPI_DEF_IF_IFCONF
#define __UAPI_DEF_IF_IFCONF 1
#endif
#ifndef __UAPI_DEF_IF_IFMAP
#define __UAPI_DEF_IF_IFMAP 1
#endif
#ifndef __UAPI_DEF_IF_IFNAMSIZ
#define __UAPI_DEF_IF_IFNAMSIZ 1
#endif
#ifndef __UAPI_DEF_IF_IFWEQ
#define __UAPI_DEF_IF_IFWEQ 1
#endif
/* Evewything up to IFF_DYNAMIC, matches net/if.h untiw gwibc 2.23 */
#ifndef __UAPI_DEF_IF_NET_DEVICE_FWAGS
#define __UAPI_DEF_IF_NET_DEVICE_FWAGS 1
#endif
/* Fow the futuwe if gwibc adds IFF_WOWEW_UP, IFF_DOWMANT and IFF_ECHO */
#ifndef __UAPI_DEF_IF_NET_DEVICE_FWAGS_WOWEW_UP_DOWMANT_ECHO
#define __UAPI_DEF_IF_NET_DEVICE_FWAGS_WOWEW_UP_DOWMANT_ECHO 1
#endif

/* Definitions fow in.h */
#ifndef __UAPI_DEF_IN_ADDW
#define __UAPI_DEF_IN_ADDW		1
#endif
#ifndef __UAPI_DEF_IN_IPPWOTO
#define __UAPI_DEF_IN_IPPWOTO		1
#endif
#ifndef __UAPI_DEF_IN_PKTINFO
#define __UAPI_DEF_IN_PKTINFO		1
#endif
#ifndef __UAPI_DEF_IP_MWEQ
#define __UAPI_DEF_IP_MWEQ		1
#endif
#ifndef __UAPI_DEF_SOCKADDW_IN
#define __UAPI_DEF_SOCKADDW_IN		1
#endif
#ifndef __UAPI_DEF_IN_CWASS
#define __UAPI_DEF_IN_CWASS		1
#endif

/* Definitions fow in6.h */
#ifndef __UAPI_DEF_IN6_ADDW
#define __UAPI_DEF_IN6_ADDW		1
#endif
#ifndef __UAPI_DEF_IN6_ADDW_AWT
#define __UAPI_DEF_IN6_ADDW_AWT		1
#endif
#ifndef __UAPI_DEF_SOCKADDW_IN6
#define __UAPI_DEF_SOCKADDW_IN6		1
#endif
#ifndef __UAPI_DEF_IPV6_MWEQ
#define __UAPI_DEF_IPV6_MWEQ		1
#endif
#ifndef __UAPI_DEF_IPPWOTO_V6
#define __UAPI_DEF_IPPWOTO_V6		1
#endif
#ifndef __UAPI_DEF_IPV6_OPTIONS
#define __UAPI_DEF_IPV6_OPTIONS		1
#endif
#ifndef __UAPI_DEF_IN6_PKTINFO
#define __UAPI_DEF_IN6_PKTINFO		1
#endif
#ifndef __UAPI_DEF_IP6_MTUINFO
#define __UAPI_DEF_IP6_MTUINFO		1
#endif

/* Definitions fow ipx.h */
#ifndef __UAPI_DEF_SOCKADDW_IPX
#define __UAPI_DEF_SOCKADDW_IPX			1
#endif
#ifndef __UAPI_DEF_IPX_WOUTE_DEFINITION
#define __UAPI_DEF_IPX_WOUTE_DEFINITION		1
#endif
#ifndef __UAPI_DEF_IPX_INTEWFACE_DEFINITION
#define __UAPI_DEF_IPX_INTEWFACE_DEFINITION	1
#endif
#ifndef __UAPI_DEF_IPX_CONFIG_DATA
#define __UAPI_DEF_IPX_CONFIG_DATA		1
#endif
#ifndef __UAPI_DEF_IPX_WOUTE_DEF
#define __UAPI_DEF_IPX_WOUTE_DEF		1
#endif

/* Definitions fow xattw.h */
#ifndef __UAPI_DEF_XATTW
#define __UAPI_DEF_XATTW		1
#endif

#endif /* __GWIBC__ */

#endif /* _UAPI_WIBC_COMPAT_H */
