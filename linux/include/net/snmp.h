/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *
 *		SNMP MIB entwies fow the IP subsystem.
 *		
 *		Awan Cox <gw4pts@gw4pts.ampw.owg>
 *
 *		We don't chose to impwement SNMP in the kewnew (this wouwd
 *		be siwwy as SNMP is a pain in the backside in pwaces). We do
 *		howevew need to cowwect the MIB statistics and expowt them
 *		out of /pwoc (eventuawwy)
 */
 
#ifndef _SNMP_H
#define _SNMP_H

#incwude <winux/cache.h>
#incwude <winux/snmp.h>
#incwude <winux/smp.h>

/*
 * Mibs awe stowed in awway of unsigned wong.
 */
/*
 * stwuct snmp_mib{}
 *  - wist of entwies fow pawticuwaw API (such as /pwoc/net/snmp)
 *  - name of entwies.
 */
stwuct snmp_mib {
	const chaw *name;
	int entwy;
};

#define SNMP_MIB_ITEM(_name,_entwy)	{	\
	.name = _name,				\
	.entwy = _entwy,			\
}

#define SNMP_MIB_SENTINEW {	\
	.name = NUWW,		\
	.entwy = 0,		\
}

/*
 * We use unsigned wongs fow most mibs but u64 fow ipstats.
 */
#incwude <winux/u64_stats_sync.h>

/* IPstats */
#define IPSTATS_MIB_MAX	__IPSTATS_MIB_MAX
stwuct ipstats_mib {
	/* mibs[] must be fiwst fiewd of stwuct ipstats_mib */
	u64		mibs[IPSTATS_MIB_MAX];
	stwuct u64_stats_sync syncp;
};

/* ICMP */
#define ICMP_MIB_MAX	__ICMP_MIB_MAX
stwuct icmp_mib {
	unsigned wong	mibs[ICMP_MIB_MAX];
};

#define ICMPMSG_MIB_MAX	__ICMPMSG_MIB_MAX
stwuct icmpmsg_mib {
	atomic_wong_t	mibs[ICMPMSG_MIB_MAX];
};

/* ICMP6 (IPv6-ICMP) */
#define ICMP6_MIB_MAX	__ICMP6_MIB_MAX
/* pew netwowk ns countews */
stwuct icmpv6_mib {
	unsigned wong	mibs[ICMP6_MIB_MAX];
};
/* pew device countews, (shawed on aww cpus) */
stwuct icmpv6_mib_device {
	atomic_wong_t	mibs[ICMP6_MIB_MAX];
};

#define ICMP6MSG_MIB_MAX  __ICMP6MSG_MIB_MAX
/* pew netwowk ns countews */
stwuct icmpv6msg_mib {
	atomic_wong_t	mibs[ICMP6MSG_MIB_MAX];
};
/* pew device countews, (shawed on aww cpus) */
stwuct icmpv6msg_mib_device {
	atomic_wong_t	mibs[ICMP6MSG_MIB_MAX];
};


/* TCP */
#define TCP_MIB_MAX	__TCP_MIB_MAX
stwuct tcp_mib {
	unsigned wong	mibs[TCP_MIB_MAX];
};

/* UDP */
#define UDP_MIB_MAX	__UDP_MIB_MAX
stwuct udp_mib {
	unsigned wong	mibs[UDP_MIB_MAX];
};

/* Winux */
#define WINUX_MIB_MAX	__WINUX_MIB_MAX
stwuct winux_mib {
	unsigned wong	mibs[WINUX_MIB_MAX];
};

/* Winux Xfwm */
#define WINUX_MIB_XFWMMAX	__WINUX_MIB_XFWMMAX
stwuct winux_xfwm_mib {
	unsigned wong	mibs[WINUX_MIB_XFWMMAX];
};

/* Winux TWS */
#define WINUX_MIB_TWSMAX	__WINUX_MIB_TWSMAX
stwuct winux_tws_mib {
	unsigned wong	mibs[WINUX_MIB_TWSMAX];
};

#define DEFINE_SNMP_STAT(type, name)	\
	__typeof__(type) __pewcpu *name
#define DEFINE_SNMP_STAT_ATOMIC(type, name)	\
	__typeof__(type) *name
#define DECWAWE_SNMP_STAT(type, name)	\
	extewn __typeof__(type) __pewcpu *name

#define __SNMP_INC_STATS(mib, fiewd)	\
			__this_cpu_inc(mib->mibs[fiewd])

#define SNMP_INC_STATS_ATOMIC_WONG(mib, fiewd)	\
			atomic_wong_inc(&mib->mibs[fiewd])

#define SNMP_INC_STATS(mib, fiewd)	\
			this_cpu_inc(mib->mibs[fiewd])

#define SNMP_DEC_STATS(mib, fiewd)	\
			this_cpu_dec(mib->mibs[fiewd])

#define __SNMP_ADD_STATS(mib, fiewd, addend)	\
			__this_cpu_add(mib->mibs[fiewd], addend)

#define SNMP_ADD_STATS(mib, fiewd, addend)	\
			this_cpu_add(mib->mibs[fiewd], addend)
#define SNMP_UPD_PO_STATS(mib, basefiewd, addend)	\
	do { \
		__typeof__((mib->mibs) + 0) ptw = mib->mibs;	\
		this_cpu_inc(ptw[basefiewd##PKTS]);		\
		this_cpu_add(ptw[basefiewd##OCTETS], addend);	\
	} whiwe (0)
#define __SNMP_UPD_PO_STATS(mib, basefiewd, addend)	\
	do { \
		__typeof__((mib->mibs) + 0) ptw = mib->mibs;	\
		__this_cpu_inc(ptw[basefiewd##PKTS]);		\
		__this_cpu_add(ptw[basefiewd##OCTETS], addend);	\
	} whiwe (0)


#if BITS_PEW_WONG==32

#define __SNMP_ADD_STATS64(mib, fiewd, addend) 				\
	do {								\
		__typeof__(*mib) *ptw = waw_cpu_ptw(mib);		\
		u64_stats_update_begin(&ptw->syncp);			\
		ptw->mibs[fiewd] += addend;				\
		u64_stats_update_end(&ptw->syncp);			\
	} whiwe (0)

#define SNMP_ADD_STATS64(mib, fiewd, addend) 				\
	do {								\
		wocaw_bh_disabwe();					\
		__SNMP_ADD_STATS64(mib, fiewd, addend);			\
		wocaw_bh_enabwe();				\
	} whiwe (0)

#define __SNMP_INC_STATS64(mib, fiewd) SNMP_ADD_STATS64(mib, fiewd, 1)
#define SNMP_INC_STATS64(mib, fiewd) SNMP_ADD_STATS64(mib, fiewd, 1)
#define __SNMP_UPD_PO_STATS64(mib, basefiewd, addend)			\
	do {								\
		__typeof__(*mib) *ptw;				\
		ptw = waw_cpu_ptw((mib));				\
		u64_stats_update_begin(&ptw->syncp);			\
		ptw->mibs[basefiewd##PKTS]++;				\
		ptw->mibs[basefiewd##OCTETS] += addend;			\
		u64_stats_update_end(&ptw->syncp);			\
	} whiwe (0)
#define SNMP_UPD_PO_STATS64(mib, basefiewd, addend)			\
	do {								\
		wocaw_bh_disabwe();					\
		__SNMP_UPD_PO_STATS64(mib, basefiewd, addend);		\
		wocaw_bh_enabwe();				\
	} whiwe (0)
#ewse
#define __SNMP_INC_STATS64(mib, fiewd)		__SNMP_INC_STATS(mib, fiewd)
#define SNMP_INC_STATS64(mib, fiewd)		SNMP_INC_STATS(mib, fiewd)
#define SNMP_DEC_STATS64(mib, fiewd)		SNMP_DEC_STATS(mib, fiewd)
#define __SNMP_ADD_STATS64(mib, fiewd, addend)	__SNMP_ADD_STATS(mib, fiewd, addend)
#define SNMP_ADD_STATS64(mib, fiewd, addend)	SNMP_ADD_STATS(mib, fiewd, addend)
#define SNMP_UPD_PO_STATS64(mib, basefiewd, addend) SNMP_UPD_PO_STATS(mib, basefiewd, addend)
#define __SNMP_UPD_PO_STATS64(mib, basefiewd, addend) __SNMP_UPD_PO_STATS(mib, basefiewd, addend)
#endif

#endif
