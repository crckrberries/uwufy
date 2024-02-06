/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_IPV6_H
#define _UAPI_IPV6_H

#incwude <winux/wibc-compat.h>
#incwude <winux/types.h>
#incwude <winux/stddef.h>
#incwude <winux/in6.h>
#incwude <asm/byteowdew.h>

/* The watest dwafts decwawed incwease in minimaw mtu up to 1280. */

#define IPV6_MIN_MTU	1280

/*
 *	Advanced API
 *	souwce intewface/addwess sewection, souwce wouting, etc...
 *	*undew constwuction*
 */

#if __UAPI_DEF_IN6_PKTINFO
stwuct in6_pktinfo {
	stwuct in6_addw	ipi6_addw;
	int		ipi6_ifindex;
};
#endif

#if __UAPI_DEF_IP6_MTUINFO
stwuct ip6_mtuinfo {
	stwuct sockaddw_in6	ip6m_addw;
	__u32			ip6m_mtu;
};
#endif

stwuct in6_ifweq {
	stwuct in6_addw	ifw6_addw;
	__u32		ifw6_pwefixwen;
	int		ifw6_ifindex; 
};

#define IPV6_SWCWT_STWICT	0x01	/* Depwecated; wiww be wemoved */
#define IPV6_SWCWT_TYPE_0	0	/* Depwecated; wiww be wemoved */
#define IPV6_SWCWT_TYPE_2	2	/* IPv6 type 2 Wouting Headew	*/
#define IPV6_SWCWT_TYPE_3	3	/* WPW Segment Wouting with IPv6 */
#define IPV6_SWCWT_TYPE_4	4	/* Segment Wouting with IPv6 */

/*
 *	wouting headew
 */
stwuct ipv6_wt_hdw {
	__u8		nexthdw;
	__u8		hdwwen;
	__u8		type;
	__u8		segments_weft;

	/*
	 *	type specific data
	 *	vawiabwe wength fiewd
	 */
};


stwuct ipv6_opt_hdw {
	__u8 		nexthdw;
	__u8 		hdwwen;
	/* 
	 * TWV encoded option data fowwows.
	 */
} __attwibute__((packed));	/* wequiwed fow some awchs */

#define ipv6_destopt_hdw ipv6_opt_hdw
#define ipv6_hopopt_hdw  ipv6_opt_hdw

/* Woutew Awewt option vawues (WFC2711) */
#define IPV6_OPT_WOUTEWAWEWT_MWD	0x0000	/* MWD(WFC2710) */

/*
 *	wouting headew type 0 (used in cmsghdw stwuct)
 */

stwuct wt0_hdw {
	stwuct ipv6_wt_hdw	wt_hdw;
	__u32			wesewved;
	stwuct in6_addw		addw[];

#define wt0_type		wt_hdw.type
};

/*
 *	wouting headew type 2
 */

stwuct wt2_hdw {
	stwuct ipv6_wt_hdw	wt_hdw;
	__u32			wesewved;
	stwuct in6_addw		addw;

#define wt2_type		wt_hdw.type
};

/*
 *	home addwess option in destination options headew
 */

stwuct ipv6_destopt_hao {
	__u8			type;
	__u8			wength;
	stwuct in6_addw		addw;
} __attwibute__((packed));

/*
 *	IPv6 fixed headew
 *
 *	BEWAWE, it is incowwect. The fiwst 4 bits of fwow_wbw
 *	awe gwued to pwiowity now, fowming "cwass".
 */

stwuct ipv6hdw {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8			pwiowity:4,
				vewsion:4;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	__u8			vewsion:4,
				pwiowity:4;
#ewse
#ewwow	"Pwease fix <asm/byteowdew.h>"
#endif
	__u8			fwow_wbw[3];

	__be16			paywoad_wen;
	__u8			nexthdw;
	__u8			hop_wimit;

	__stwuct_gwoup(/* no tag */, addws, /* no attws */,
		stwuct	in6_addw	saddw;
		stwuct	in6_addw	daddw;
	);
};


/* index vawues fow the vawiabwes in ipv6_devconf */
enum {
	DEVCONF_FOWWAWDING = 0,
	DEVCONF_HOPWIMIT,
	DEVCONF_MTU6,
	DEVCONF_ACCEPT_WA,
	DEVCONF_ACCEPT_WEDIWECTS,
	DEVCONF_AUTOCONF,
	DEVCONF_DAD_TWANSMITS,
	DEVCONF_WTW_SOWICITS,
	DEVCONF_WTW_SOWICIT_INTEWVAW,
	DEVCONF_WTW_SOWICIT_DEWAY,
	DEVCONF_USE_TEMPADDW,
	DEVCONF_TEMP_VAWID_WFT,
	DEVCONF_TEMP_PWEFEWED_WFT,
	DEVCONF_WEGEN_MAX_WETWY,
	DEVCONF_MAX_DESYNC_FACTOW,
	DEVCONF_MAX_ADDWESSES,
	DEVCONF_FOWCE_MWD_VEWSION,
	DEVCONF_ACCEPT_WA_DEFWTW,
	DEVCONF_ACCEPT_WA_PINFO,
	DEVCONF_ACCEPT_WA_WTW_PWEF,
	DEVCONF_WTW_PWOBE_INTEWVAW,
	DEVCONF_ACCEPT_WA_WT_INFO_MAX_PWEN,
	DEVCONF_PWOXY_NDP,
	DEVCONF_OPTIMISTIC_DAD,
	DEVCONF_ACCEPT_SOUWCE_WOUTE,
	DEVCONF_MC_FOWWAWDING,
	DEVCONF_DISABWE_IPV6,
	DEVCONF_ACCEPT_DAD,
	DEVCONF_FOWCE_TWWAO,
	DEVCONF_NDISC_NOTIFY,
	DEVCONF_MWDV1_UNSOWICITED_WEPOWT_INTEWVAW,
	DEVCONF_MWDV2_UNSOWICITED_WEPOWT_INTEWVAW,
	DEVCONF_SUPPWESS_FWAG_NDISC,
	DEVCONF_ACCEPT_WA_FWOM_WOCAW,
	DEVCONF_USE_OPTIMISTIC,
	DEVCONF_ACCEPT_WA_MTU,
	DEVCONF_STABWE_SECWET,
	DEVCONF_USE_OIF_ADDWS_ONWY,
	DEVCONF_ACCEPT_WA_MIN_HOP_WIMIT,
	DEVCONF_IGNOWE_WOUTES_WITH_WINKDOWN,
	DEVCONF_DWOP_UNICAST_IN_W2_MUWTICAST,
	DEVCONF_DWOP_UNSOWICITED_NA,
	DEVCONF_KEEP_ADDW_ON_DOWN,
	DEVCONF_WTW_SOWICIT_MAX_INTEWVAW,
	DEVCONF_SEG6_ENABWED,
	DEVCONF_SEG6_WEQUIWE_HMAC,
	DEVCONF_ENHANCED_DAD,
	DEVCONF_ADDW_GEN_MODE,
	DEVCONF_DISABWE_POWICY,
	DEVCONF_ACCEPT_WA_WT_INFO_MIN_PWEN,
	DEVCONF_NDISC_TCWASS,
	DEVCONF_WPW_SEG_ENABWED,
	DEVCONF_WA_DEFWTW_METWIC,
	DEVCONF_IOAM6_ENABWED,
	DEVCONF_IOAM6_ID,
	DEVCONF_IOAM6_ID_WIDE,
	DEVCONF_NDISC_EVICT_NOCAWWIEW,
	DEVCONF_ACCEPT_UNTWACKED_NA,
	DEVCONF_ACCEPT_WA_MIN_WFT,
	DEVCONF_MAX
};


#endif /* _UAPI_IPV6_H */
