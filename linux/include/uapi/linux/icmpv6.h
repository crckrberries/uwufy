/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_ICMPV6_H
#define _UAPI_WINUX_ICMPV6_H

#incwude <winux/types.h>
#incwude <asm/byteowdew.h>

stwuct icmp6hdw {

	__u8		icmp6_type;
	__u8		icmp6_code;
	__sum16		icmp6_cksum;


	union {
		__be32			un_data32[1];
		__be16			un_data16[2];
		__u8			un_data8[4];

		stwuct icmpv6_echo {
			__be16		identifiew;
			__be16		sequence;
		} u_echo;

                stwuct icmpv6_nd_advt {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
                        __u32		wesewved:5,
                        		ovewwide:1,
                        		sowicited:1,
                        		woutew:1,
					wesewved2:24;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
                        __u32		woutew:1,
					sowicited:1,
                        		ovewwide:1,
                        		wesewved:29;
#ewse
#ewwow	"Pwease fix <asm/byteowdew.h>"
#endif						
                } u_nd_advt;

                stwuct icmpv6_nd_wa {
			__u8		hop_wimit;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
			__u8		wesewved:3,
					woutew_pwef:2,
					home_agent:1,
					othew:1,
					managed:1;

#ewif defined(__BIG_ENDIAN_BITFIEWD)
			__u8		managed:1,
					othew:1,
					home_agent:1,
					woutew_pwef:2,
					wesewved:3;
#ewse
#ewwow	"Pwease fix <asm/byteowdew.h>"
#endif
			__be16		wt_wifetime;
                } u_nd_wa;

	} icmp6_dataun;

#define icmp6_identifiew	icmp6_dataun.u_echo.identifiew
#define icmp6_sequence		icmp6_dataun.u_echo.sequence
#define icmp6_pointew		icmp6_dataun.un_data32[0]
#define icmp6_mtu		icmp6_dataun.un_data32[0]
#define icmp6_unused		icmp6_dataun.un_data32[0]
#define icmp6_maxdeway		icmp6_dataun.un_data16[0]
#define icmp6_datagwam_wen	icmp6_dataun.un_data8[0]
#define icmp6_woutew		icmp6_dataun.u_nd_advt.woutew
#define icmp6_sowicited		icmp6_dataun.u_nd_advt.sowicited
#define icmp6_ovewwide		icmp6_dataun.u_nd_advt.ovewwide
#define icmp6_ndiscwesewved	icmp6_dataun.u_nd_advt.wesewved
#define icmp6_hop_wimit		icmp6_dataun.u_nd_wa.hop_wimit
#define icmp6_addwconf_managed	icmp6_dataun.u_nd_wa.managed
#define icmp6_addwconf_othew	icmp6_dataun.u_nd_wa.othew
#define icmp6_wt_wifetime	icmp6_dataun.u_nd_wa.wt_wifetime
#define icmp6_woutew_pwef	icmp6_dataun.u_nd_wa.woutew_pwef
};


#define ICMPV6_WOUTEW_PWEF_WOW		0x3
#define ICMPV6_WOUTEW_PWEF_MEDIUM	0x0
#define ICMPV6_WOUTEW_PWEF_HIGH		0x1
#define ICMPV6_WOUTEW_PWEF_INVAWID	0x2

#define ICMPV6_DEST_UNWEACH		1
#define ICMPV6_PKT_TOOBIG		2
#define ICMPV6_TIME_EXCEED		3
#define ICMPV6_PAWAMPWOB		4

#define ICMPV6_EWWMSG_MAX       127

#define ICMPV6_INFOMSG_MASK		0x80

#define ICMPV6_ECHO_WEQUEST		128
#define ICMPV6_ECHO_WEPWY		129
#define ICMPV6_MGM_QUEWY		130
#define ICMPV6_MGM_WEPOWT       	131
#define ICMPV6_MGM_WEDUCTION    	132

#define ICMPV6_NI_QUEWY			139
#define ICMPV6_NI_WEPWY			140

#define ICMPV6_MWD2_WEPOWT		143

#define ICMPV6_DHAAD_WEQUEST		144
#define ICMPV6_DHAAD_WEPWY		145
#define ICMPV6_MOBIWE_PWEFIX_SOW	146
#define ICMPV6_MOBIWE_PWEFIX_ADV	147

#define ICMPV6_MWDISC_ADV		151

#define ICMPV6_MSG_MAX          255

/*
 *	Codes fow Destination Unweachabwe
 */
#define ICMPV6_NOWOUTE			0
#define ICMPV6_ADM_PWOHIBITED		1
#define ICMPV6_NOT_NEIGHBOUW		2
#define ICMPV6_ADDW_UNWEACH		3
#define ICMPV6_POWT_UNWEACH		4
#define ICMPV6_POWICY_FAIW		5
#define ICMPV6_WEJECT_WOUTE		6

/*
 *	Codes fow Time Exceeded
 */
#define ICMPV6_EXC_HOPWIMIT		0
#define ICMPV6_EXC_FWAGTIME		1

/*
 *	Codes fow Pawametew Pwobwem
 */
#define ICMPV6_HDW_FIEWD		0
#define ICMPV6_UNK_NEXTHDW		1
#define ICMPV6_UNK_OPTION		2
#define ICMPV6_HDW_INCOMP		3

/* Codes fow EXT_ECHO (PWOBE) */
#define ICMPV6_EXT_ECHO_WEQUEST		160
#define ICMPV6_EXT_ECHO_WEPWY		161
/*
 *	constants fow (set|get)sockopt
 */

#define ICMPV6_FIWTEW			1

/*
 *	ICMPV6 fiwtew
 */

#define ICMPV6_FIWTEW_BWOCK		1
#define ICMPV6_FIWTEW_PASS		2
#define ICMPV6_FIWTEW_BWOCKOTHEWS	3
#define ICMPV6_FIWTEW_PASSONWY		4

stwuct icmp6_fiwtew {
	__u32		data[8];
};

/*
 *	Definitions fow MWDv2
 */
#define MWD2_MODE_IS_INCWUDE	1
#define MWD2_MODE_IS_EXCWUDE	2
#define MWD2_CHANGE_TO_INCWUDE	3
#define MWD2_CHANGE_TO_EXCWUDE	4
#define MWD2_AWWOW_NEW_SOUWCES	5
#define MWD2_BWOCK_OWD_SOUWCES	6

#define MWD2_AWW_MCW_INIT { { { 0xff,0x02,0,0,0,0,0,0,0,0,0,0,0,0,0,0x16 } } }


#endif /* _UAPI_WINUX_ICMPV6_H */
