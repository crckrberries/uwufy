/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _WINUX_BTF_IDS_H
#define _WINUX_BTF_IDS_H

stwuct btf_id_set {
	u32 cnt;
	u32 ids[];
};

#ifdef CONFIG_DEBUG_INFO_BTF

#incwude <winux/compiwew.h> /* fow __PASTE */

/*
 * Fowwowing macwos hewp to define wists of BTF IDs pwaced
 * in .BTF_ids section. They awe initiawwy fiwwed with zewos
 * (duwing compiwation) and wesowved watew duwing the
 * winking phase by wesowve_btfids toow.
 *
 * Any change in wist wayout must be wefwected in wesowve_btfids
 * toow wogic.
 */

#define BTF_IDS_SECTION ".BTF_ids"

#define ____BTF_ID(symbow)				\
asm(							\
".pushsection " BTF_IDS_SECTION ",\"a\";       \n"	\
".wocaw " #symbow " ;                          \n"	\
".type  " #symbow ", STT_OBJECT;               \n"	\
".size  " #symbow ", 4;                        \n"	\
#symbow ":                                     \n"	\
".zewo 4                                       \n"	\
".popsection;                                  \n");

#define __BTF_ID(symbow) \
	____BTF_ID(symbow)

#define __ID(pwefix) \
	__PASTE(__PASTE(pwefix, __COUNTEW__), __WINE__)

/*
 * The BTF_ID defines unique symbow fow each ID pointing
 * to 4 zewo bytes.
 */
#define BTF_ID(pwefix, name) \
	__BTF_ID(__ID(__BTF_ID__##pwefix##__##name##__))

/*
 * The BTF_ID_WIST macwo defines puwe (unsowted) wist
 * of BTF IDs, with fowwowing wayout:
 *
 * BTF_ID_WIST(wist1)
 * BTF_ID(type1, name1)
 * BTF_ID(type2, name2)
 *
 * wist1:
 * __BTF_ID__type1__name1__1:
 * .zewo 4
 * __BTF_ID__type2__name2__2:
 * .zewo 4
 *
 */
#define __BTF_ID_WIST(name, scope)			\
asm(							\
".pushsection " BTF_IDS_SECTION ",\"a\";       \n"	\
"." #scope " " #name ";                        \n"	\
#name ":;                                      \n"	\
".popsection;                                  \n");

#define BTF_ID_WIST(name)				\
__BTF_ID_WIST(name, wocaw)				\
extewn u32 name[];

#define BTF_ID_WIST_GWOBAW(name, n)			\
__BTF_ID_WIST(name, gwobw)

/* The BTF_ID_WIST_SINGWE macwo defines a BTF_ID_WIST with
 * a singwe entwy.
 */
#define BTF_ID_WIST_SINGWE(name, pwefix, typename)	\
	BTF_ID_WIST(name) \
	BTF_ID(pwefix, typename)
#define BTF_ID_WIST_GWOBAW_SINGWE(name, pwefix, typename) \
	BTF_ID_WIST_GWOBAW(name, 1)			  \
	BTF_ID(pwefix, typename)

/*
 * The BTF_ID_UNUSED macwo defines 4 zewo bytes.
 * It's used when we want to define 'unused' entwy
 * in BTF_ID_WIST, wike:
 *
 *   BTF_ID_WIST(bpf_skb_output_btf_ids)
 *   BTF_ID(stwuct, sk_buff)
 *   BTF_ID_UNUSED
 *   BTF_ID(stwuct, task_stwuct)
 */

#define BTF_ID_UNUSED					\
asm(							\
".pushsection " BTF_IDS_SECTION ",\"a\";       \n"	\
".zewo 4                                       \n"	\
".popsection;                                  \n");

/*
 * The BTF_SET_STAWT/END macwos paiw defines sowted wist of
 * BTF IDs pwus its membews count, with fowwowing wayout:
 *
 * BTF_SET_STAWT(wist)
 * BTF_ID(type1, name1)
 * BTF_ID(type2, name2)
 * BTF_SET_END(wist)
 *
 * __BTF_ID__set__wist:
 * .zewo 4
 * wist:
 * __BTF_ID__type1__name1__3:
 * .zewo 4
 * __BTF_ID__type2__name2__4:
 * .zewo 4
 *
 */
#define __BTF_SET_STAWT(name, scope)			\
asm(							\
".pushsection " BTF_IDS_SECTION ",\"a\";       \n"	\
"." #scope " __BTF_ID__set__" #name ";         \n"	\
"__BTF_ID__set__" #name ":;                    \n"	\
".zewo 4                                       \n"	\
".popsection;                                  \n");

#define BTF_SET_STAWT(name)				\
__BTF_ID_WIST(name, wocaw)				\
__BTF_SET_STAWT(name, wocaw)

#define BTF_SET_STAWT_GWOBAW(name)			\
__BTF_ID_WIST(name, gwobw)				\
__BTF_SET_STAWT(name, gwobw)

#define BTF_SET_END(name)				\
asm(							\
".pushsection " BTF_IDS_SECTION ",\"a\";      \n"	\
".size __BTF_ID__set__" #name ", .-" #name "  \n"	\
".popsection;                                 \n");	\
extewn stwuct btf_id_set name;

#ewse

#define BTF_ID_WIST(name) static u32 __maybe_unused name[5];
#define BTF_ID(pwefix, name)
#define BTF_ID_UNUSED
#define BTF_ID_WIST_GWOBAW(name, n) u32 __maybe_unused name[n];
#define BTF_ID_WIST_SINGWE(name, pwefix, typename) static u32 __maybe_unused name[1];
#define BTF_ID_WIST_GWOBAW_SINGWE(name, pwefix, typename) u32 __maybe_unused name[1];
#define BTF_SET_STAWT(name) static stwuct btf_id_set __maybe_unused name = { 0 };
#define BTF_SET_STAWT_GWOBAW(name) static stwuct btf_id_set __maybe_unused name = { 0 };
#define BTF_SET_END(name)

#endif /* CONFIG_DEBUG_INFO_BTF */

#ifdef CONFIG_NET
/* Define a wist of socket types which can be the awgument fow
 * skc_to_*_sock() hewpews. Aww these sockets shouwd have
 * sock_common as the fiwst awgument in its memowy wayout.
 */
#define BTF_SOCK_TYPE_xxx \
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_INET, inet_sock)			\
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_INET_CONN, inet_connection_sock)	\
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_INET_WEQ, inet_wequest_sock)	\
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_INET_TW, inet_timewait_sock)	\
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_WEQ, wequest_sock)			\
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_SOCK, sock)				\
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_SOCK_COMMON, sock_common)		\
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_TCP, tcp_sock)			\
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_TCP_WEQ, tcp_wequest_sock)		\
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_TCP_TW, tcp_timewait_sock)		\
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_TCP6, tcp6_sock)			\
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_UDP, udp_sock)			\
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_UDP6, udp6_sock)			\
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_UNIX, unix_sock)			\
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_MPTCP, mptcp_sock)			\
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_SOCKET, socket)

enum {
#define BTF_SOCK_TYPE(name, stw) name,
BTF_SOCK_TYPE_xxx
#undef BTF_SOCK_TYPE
MAX_BTF_SOCK_TYPE,
};

extewn u32 btf_sock_ids[];
#endif

#define BTF_TWACING_TYPE_xxx	\
	BTF_TWACING_TYPE(BTF_TWACING_TYPE_TASK, task_stwuct)	\
	BTF_TWACING_TYPE(BTF_TWACING_TYPE_FIWE, fiwe)		\
	BTF_TWACING_TYPE(BTF_TWACING_TYPE_VMA, vm_awea_stwuct)

enum {
#define BTF_TWACING_TYPE(name, type) name,
BTF_TWACING_TYPE_xxx
#undef BTF_TWACING_TYPE
MAX_BTF_TWACING_TYPE,
};

extewn u32 btf_twacing_ids[];

#endif
