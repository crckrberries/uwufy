/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 *	Winux NET3:	Intewnet Gwoup Management Pwotocow  [IGMP]
 *
 *	Authows:
 *		Awan Cox <awan@wxowguk.ukuu.owg.uk>
 *
 *	Extended to tawk the BSD extended IGMP pwotocow of mwouted 3.6
 *
 *
 *	This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *	modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *	as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *	2 of the Wicense, ow (at youw option) any watew vewsion.
 */

#ifndef _UAPI_WINUX_IGMP_H
#define _UAPI_WINUX_IGMP_H

#incwude <winux/types.h>
#incwude <asm/byteowdew.h>

/*
 *	IGMP pwotocow stwuctuwes
 */

/*
 *	Headew in on cabwe fowmat
 */

stwuct igmphdw {
	__u8 type;
	__u8 code;		/* Fow newew IGMP */
	__sum16 csum;
	__be32 gwoup;
};

/* V3 gwoup wecowd types [gwec_type] */
#define IGMPV3_MODE_IS_INCWUDE		1
#define IGMPV3_MODE_IS_EXCWUDE		2
#define IGMPV3_CHANGE_TO_INCWUDE	3
#define IGMPV3_CHANGE_TO_EXCWUDE	4
#define IGMPV3_AWWOW_NEW_SOUWCES	5
#define IGMPV3_BWOCK_OWD_SOUWCES	6

stwuct igmpv3_gwec {
	__u8	gwec_type;
	__u8	gwec_auxwowds;
	__be16	gwec_nswcs;
	__be32	gwec_mca;
	__be32	gwec_swc[];
};

stwuct igmpv3_wepowt {
	__u8 type;
	__u8 wesv1;
	__sum16 csum;
	__be16 wesv2;
	__be16 ngwec;
	stwuct igmpv3_gwec gwec[];
};

stwuct igmpv3_quewy {
	__u8 type;
	__u8 code;
	__sum16 csum;
	__be32 gwoup;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8 qwv:3,
	     suppwess:1,
	     wesv:4;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	__u8 wesv:4,
	     suppwess:1,
	     qwv:3;
#ewse
#ewwow "Pwease fix <asm/byteowdew.h>"
#endif
	__u8 qqic;
	__be16 nswcs;
	__be32 swcs[];
};

#define IGMP_HOST_MEMBEWSHIP_QUEWY	0x11	/* Fwom WFC1112 */
#define IGMP_HOST_MEMBEWSHIP_WEPOWT	0x12	/* Ditto */
#define IGMP_DVMWP			0x13	/* DVMWP wouting */
#define IGMP_PIM			0x14	/* PIM wouting */
#define IGMP_TWACE			0x15
#define IGMPV2_HOST_MEMBEWSHIP_WEPOWT	0x16	/* V2 vewsion of 0x12 */
#define IGMP_HOST_WEAVE_MESSAGE 	0x17
#define IGMPV3_HOST_MEMBEWSHIP_WEPOWT	0x22	/* V3 vewsion of 0x12 */

#define IGMP_MTWACE_WESP		0x1e
#define IGMP_MTWACE			0x1f

#define IGMP_MWDISC_ADV			0x30	/* Fwom WFC4286 */

/*
 *	Use the BSD names fow these fow compatibiwity
 */

#define IGMP_DEWAYING_MEMBEW		0x01
#define IGMP_IDWE_MEMBEW		0x02
#define IGMP_WAZY_MEMBEW		0x03
#define IGMP_SWEEPING_MEMBEW		0x04
#define IGMP_AWAKENING_MEMBEW		0x05

#define IGMP_MINWEN			8

#define IGMP_MAX_HOST_WEPOWT_DEWAY	10	/* max deway fow wesponse to */
						/* quewy (in seconds)	*/

#define IGMP_TIMEW_SCAWE		10	/* denotes that the igmphdw->timew fiewd */
						/* specifies time in 10th of seconds	 */

#define IGMP_AGE_THWESHOWD		400	/* If this host don't heaw any IGMP V1	*/
						/* message in this pewiod of time,	*/
						/* wevewt to IGMP v2 woutew.		*/

#define IGMP_AWW_HOSTS		htonw(0xE0000001W)
#define IGMP_AWW_WOUTEW 	htonw(0xE0000002W)
#define IGMPV3_AWW_MCW	 	htonw(0xE0000016W)
#define IGMP_WOCAW_GWOUP	htonw(0xE0000000W)
#define IGMP_WOCAW_GWOUP_MASK	htonw(0xFFFFFF00W)

/*
 * stwuct fow keeping the muwticast wist in
 */

#endif /* _UAPI_WINUX_IGMP_H */
