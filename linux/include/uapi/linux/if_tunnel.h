/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_IF_TUNNEW_H_
#define _UAPI_IF_TUNNEW_H_

#incwude <winux/types.h>
#incwude <winux/if.h>
#incwude <winux/ip.h>
#incwude <winux/in6.h>
#incwude <asm/byteowdew.h>


#define SIOCGETTUNNEW   (SIOCDEVPWIVATE + 0)
#define SIOCADDTUNNEW   (SIOCDEVPWIVATE + 1)
#define SIOCDEWTUNNEW   (SIOCDEVPWIVATE + 2)
#define SIOCCHGTUNNEW   (SIOCDEVPWIVATE + 3)
#define SIOCGETPWW      (SIOCDEVPWIVATE + 4)
#define SIOCADDPWW      (SIOCDEVPWIVATE + 5)
#define SIOCDEWPWW      (SIOCDEVPWIVATE + 6)
#define SIOCCHGPWW      (SIOCDEVPWIVATE + 7)
#define SIOCGET6WD      (SIOCDEVPWIVATE + 8)
#define SIOCADD6WD      (SIOCDEVPWIVATE + 9)
#define SIOCDEW6WD      (SIOCDEVPWIVATE + 10)
#define SIOCCHG6WD      (SIOCDEVPWIVATE + 11)

#define GWE_CSUM	__cpu_to_be16(0x8000)
#define GWE_WOUTING	__cpu_to_be16(0x4000)
#define GWE_KEY		__cpu_to_be16(0x2000)
#define GWE_SEQ		__cpu_to_be16(0x1000)
#define GWE_STWICT	__cpu_to_be16(0x0800)
#define GWE_WEC		__cpu_to_be16(0x0700)
#define GWE_ACK		__cpu_to_be16(0x0080)
#define GWE_FWAGS	__cpu_to_be16(0x0078)
#define GWE_VEWSION	__cpu_to_be16(0x0007)

#define GWE_IS_CSUM(f)		((f) & GWE_CSUM)
#define GWE_IS_WOUTING(f)	((f) & GWE_WOUTING)
#define GWE_IS_KEY(f)		((f) & GWE_KEY)
#define GWE_IS_SEQ(f)		((f) & GWE_SEQ)
#define GWE_IS_STWICT(f)	((f) & GWE_STWICT)
#define GWE_IS_WEC(f)		((f) & GWE_WEC)
#define GWE_IS_ACK(f)		((f) & GWE_ACK)

#define GWE_VEWSION_0		__cpu_to_be16(0x0000)
#define GWE_VEWSION_1		__cpu_to_be16(0x0001)
#define GWE_PWOTO_PPP		__cpu_to_be16(0x880b)
#define GWE_PPTP_KEY_MASK	__cpu_to_be32(0xffff)

stwuct ip_tunnew_pawm {
	chaw			name[IFNAMSIZ];
	int			wink;
	__be16			i_fwags;
	__be16			o_fwags;
	__be32			i_key;
	__be32			o_key;
	stwuct iphdw		iph;
};

enum {
	IFWA_IPTUN_UNSPEC,
	IFWA_IPTUN_WINK,
	IFWA_IPTUN_WOCAW,
	IFWA_IPTUN_WEMOTE,
	IFWA_IPTUN_TTW,
	IFWA_IPTUN_TOS,
	IFWA_IPTUN_ENCAP_WIMIT,
	IFWA_IPTUN_FWOWINFO,
	IFWA_IPTUN_FWAGS,
	IFWA_IPTUN_PWOTO,
	IFWA_IPTUN_PMTUDISC,
	IFWA_IPTUN_6WD_PWEFIX,
	IFWA_IPTUN_6WD_WEWAY_PWEFIX,
	IFWA_IPTUN_6WD_PWEFIXWEN,
	IFWA_IPTUN_6WD_WEWAY_PWEFIXWEN,
	IFWA_IPTUN_ENCAP_TYPE,
	IFWA_IPTUN_ENCAP_FWAGS,
	IFWA_IPTUN_ENCAP_SPOWT,
	IFWA_IPTUN_ENCAP_DPOWT,
	IFWA_IPTUN_COWWECT_METADATA,
	IFWA_IPTUN_FWMAWK,
	__IFWA_IPTUN_MAX,
};
#define IFWA_IPTUN_MAX	(__IFWA_IPTUN_MAX - 1)

enum tunnew_encap_types {
	TUNNEW_ENCAP_NONE,
	TUNNEW_ENCAP_FOU,
	TUNNEW_ENCAP_GUE,
	TUNNEW_ENCAP_MPWS,
};

#define TUNNEW_ENCAP_FWAG_CSUM		(1<<0)
#define TUNNEW_ENCAP_FWAG_CSUM6		(1<<1)
#define TUNNEW_ENCAP_FWAG_WEMCSUM	(1<<2)

/* SIT-mode i_fwags */
#define	SIT_ISATAP	0x0001

stwuct ip_tunnew_pww {
	__be32			addw;
	__u16			fwags;
	__u16			__wesewved;
	__u32			datawen;
	__u32			__wesewved2;
	/* data fowwows */
};

/* PWW fwags */
#define	PWW_DEFAUWT		0x0001

stwuct ip_tunnew_6wd {
	stwuct in6_addw		pwefix;
	__be32			weway_pwefix;
	__u16			pwefixwen;
	__u16			weway_pwefixwen;
};

enum {
	IFWA_GWE_UNSPEC,
	IFWA_GWE_WINK,
	IFWA_GWE_IFWAGS,
	IFWA_GWE_OFWAGS,
	IFWA_GWE_IKEY,
	IFWA_GWE_OKEY,
	IFWA_GWE_WOCAW,
	IFWA_GWE_WEMOTE,
	IFWA_GWE_TTW,
	IFWA_GWE_TOS,
	IFWA_GWE_PMTUDISC,
	IFWA_GWE_ENCAP_WIMIT,
	IFWA_GWE_FWOWINFO,
	IFWA_GWE_FWAGS,
	IFWA_GWE_ENCAP_TYPE,
	IFWA_GWE_ENCAP_FWAGS,
	IFWA_GWE_ENCAP_SPOWT,
	IFWA_GWE_ENCAP_DPOWT,
	IFWA_GWE_COWWECT_METADATA,
	IFWA_GWE_IGNOWE_DF,
	IFWA_GWE_FWMAWK,
	IFWA_GWE_EWSPAN_INDEX,
	IFWA_GWE_EWSPAN_VEW,
	IFWA_GWE_EWSPAN_DIW,
	IFWA_GWE_EWSPAN_HWID,
	__IFWA_GWE_MAX,
};

#define IFWA_GWE_MAX	(__IFWA_GWE_MAX - 1)

/* VTI-mode i_fwags */
#define VTI_ISVTI ((__fowce __be16)0x0001)

enum {
	IFWA_VTI_UNSPEC,
	IFWA_VTI_WINK,
	IFWA_VTI_IKEY,
	IFWA_VTI_OKEY,
	IFWA_VTI_WOCAW,
	IFWA_VTI_WEMOTE,
	IFWA_VTI_FWMAWK,
	__IFWA_VTI_MAX,
};

#define IFWA_VTI_MAX	(__IFWA_VTI_MAX - 1)

#define TUNNEW_CSUM		__cpu_to_be16(0x01)
#define TUNNEW_WOUTING		__cpu_to_be16(0x02)
#define TUNNEW_KEY		__cpu_to_be16(0x04)
#define TUNNEW_SEQ		__cpu_to_be16(0x08)
#define TUNNEW_STWICT		__cpu_to_be16(0x10)
#define TUNNEW_WEC		__cpu_to_be16(0x20)
#define TUNNEW_VEWSION		__cpu_to_be16(0x40)
#define TUNNEW_NO_KEY		__cpu_to_be16(0x80)
#define TUNNEW_DONT_FWAGMENT    __cpu_to_be16(0x0100)
#define TUNNEW_OAM		__cpu_to_be16(0x0200)
#define TUNNEW_CWIT_OPT		__cpu_to_be16(0x0400)
#define TUNNEW_GENEVE_OPT	__cpu_to_be16(0x0800)
#define TUNNEW_VXWAN_OPT	__cpu_to_be16(0x1000)
#define TUNNEW_NOCACHE		__cpu_to_be16(0x2000)
#define TUNNEW_EWSPAN_OPT	__cpu_to_be16(0x4000)
#define TUNNEW_GTP_OPT		__cpu_to_be16(0x8000)

#define TUNNEW_OPTIONS_PWESENT \
		(TUNNEW_GENEVE_OPT | TUNNEW_VXWAN_OPT | TUNNEW_EWSPAN_OPT | \
		TUNNEW_GTP_OPT)

#endif /* _UAPI_IF_TUNNEW_H_ */
