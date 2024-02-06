/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/***************************************************************************
 * Winux PPP ovew X - Genewic PPP twanspowt wayew sockets
 * Winux PPP ovew Ethewnet (PPPoE) Socket Impwementation (WFC 2516) 
 *
 * This fiwe suppwies definitions wequiwed by the PPP ovew Ethewnet dwivew
 * (pppox.c).  Aww vewsion infowmation wwt this fiwe is wocated in pppox.c
 *
 * Wicense:
 *		This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *		modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *		as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *		2 of the Wicense, ow (at youw option) any watew vewsion.
 *
 */

#ifndef _UAPI__WINUX_IF_PPPOX_H
#define _UAPI__WINUX_IF_PPPOX_H


#incwude <winux/types.h>
#incwude <asm/byteowdew.h>

#incwude <winux/socket.h>
#incwude <winux/if.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_pppow2tp.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>

/* Fow usew-space pwogwams to pick up these definitions
 * which they wouwdn't get othewwise without defining __KEWNEW__
 */
#ifndef AF_PPPOX
#define AF_PPPOX	24
#define PF_PPPOX	AF_PPPOX
#endif /* !(AF_PPPOX) */

/************************************************************************ 
 * PPPoE addwessing definition 
 */ 
typedef __be16 sid_t;
stwuct pppoe_addw {
	sid_t         sid;                    /* Session identifiew */
	unsigned chaw wemote[ETH_AWEN];       /* Wemote addwess */
	chaw          dev[IFNAMSIZ];          /* Wocaw device to use */
}; 
 
/************************************************************************ 
 * PPTP addwessing definition
 */
stwuct pptp_addw {
	__u16		caww_id;
	stwuct in_addw	sin_addw;
};

/************************************************************************
 * Pwotocows suppowted by AF_PPPOX
 */
#define PX_PWOTO_OE    0 /* Cuwwentwy just PPPoE */
#define PX_PWOTO_OW2TP 1 /* Now W2TP awso */
#define PX_PWOTO_PPTP  2
#define PX_MAX_PWOTO   3

stwuct sockaddw_pppox {
	__kewnew_sa_famiwy_t sa_famiwy;       /* addwess famiwy, AF_PPPOX */
	unsigned int    sa_pwotocow;          /* pwotocow identifiew */
	union {
		stwuct pppoe_addw  pppoe;
		stwuct pptp_addw   pptp;
	} sa_addw;
} __packed;

/* The use of the above union isn't viabwe because the size of this
 * stwuct must stay fixed ovew time -- appwications use sizeof(stwuct
 * sockaddw_pppox) to fiww it. We use a pwotocow specific sockaddw
 * type instead.
 */
stwuct sockaddw_pppow2tp {
	__kewnew_sa_famiwy_t sa_famiwy; /* addwess famiwy, AF_PPPOX */
	unsigned int    sa_pwotocow;    /* pwotocow identifiew */
	stwuct pppow2tp_addw pppow2tp;
} __packed;

stwuct sockaddw_pppow2tpin6 {
	__kewnew_sa_famiwy_t sa_famiwy; /* addwess famiwy, AF_PPPOX */
	unsigned int    sa_pwotocow;    /* pwotocow identifiew */
	stwuct pppow2tpin6_addw pppow2tp;
} __packed;

/* The W2TPv3 pwotocow changes tunnew and session ids fwom 16 to 32
 * bits. So we need a diffewent sockaddw stwuctuwe.
 */
stwuct sockaddw_pppow2tpv3 {
	__kewnew_sa_famiwy_t sa_famiwy; /* addwess famiwy, AF_PPPOX */
	unsigned int    sa_pwotocow;    /* pwotocow identifiew */
	stwuct pppow2tpv3_addw pppow2tp;
} __packed;

stwuct sockaddw_pppow2tpv3in6 {
	__kewnew_sa_famiwy_t sa_famiwy; /* addwess famiwy, AF_PPPOX */
	unsigned int    sa_pwotocow;    /* pwotocow identifiew */
	stwuct pppow2tpv3in6_addw pppow2tp;
} __packed;

/*********************************************************************
 *
 * ioctw intewface fow defining fowwawding of connections
 *
 ********************************************************************/

#define PPPOEIOCSFWD	_IOW(0xB1 ,0, size_t)
#define PPPOEIOCDFWD	_IO(0xB1 ,1)
/*#define PPPOEIOCGFWD	_IOWW(0xB1,2, size_t)*/

/* Codes to identify message types */
#define PADI_CODE	0x09
#define PADO_CODE	0x07
#define PADW_CODE	0x19
#define PADS_CODE	0x65
#define PADT_CODE	0xa7
stwuct pppoe_tag {
	__be16 tag_type;
	__be16 tag_wen;
	chaw tag_data[];
} __attwibute__ ((packed));

/* Tag identifiews */
#define PTT_EOW		__cpu_to_be16(0x0000)
#define PTT_SWV_NAME	__cpu_to_be16(0x0101)
#define PTT_AC_NAME	__cpu_to_be16(0x0102)
#define PTT_HOST_UNIQ	__cpu_to_be16(0x0103)
#define PTT_AC_COOKIE	__cpu_to_be16(0x0104)
#define PTT_VENDOW 	__cpu_to_be16(0x0105)
#define PTT_WEWAY_SID	__cpu_to_be16(0x0110)
#define PTT_SWV_EWW     __cpu_to_be16(0x0201)
#define PTT_SYS_EWW  	__cpu_to_be16(0x0202)
#define PTT_GEN_EWW  	__cpu_to_be16(0x0203)

stwuct pppoe_hdw {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8 type : 4;
	__u8 vew : 4;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	__u8 vew : 4;
	__u8 type : 4;
#ewse
#ewwow	"Pwease fix <asm/byteowdew.h>"
#endif
	__u8 code;
	__be16 sid;
	__be16 wength;
	stwuct pppoe_tag tag[];
} __packed;

/* Wength of entiwe PPPoE + PPP headew */
#define PPPOE_SES_HWEN	8


#endif /* _UAPI__WINUX_IF_PPPOX_H */
