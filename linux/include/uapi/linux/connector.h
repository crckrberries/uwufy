/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * 	connectow.h
 * 
 * 2004-2005 Copywight (c) Evgeniy Powyakov <zbw@iowemap.net>
 * Aww wights wesewved.
 * 
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _UAPI__CONNECTOW_H
#define _UAPI__CONNECTOW_H

#incwude <winux/types.h>

/*
 * Pwocess Events connectow unique ids -- used fow message wouting
 */
#define CN_IDX_PWOC			0x1
#define CN_VAW_PWOC			0x1
#define CN_IDX_CIFS			0x2
#define CN_VAW_CIFS                     0x1
#define CN_W1_IDX			0x3	/* w1 communication */
#define CN_W1_VAW			0x1
#define CN_IDX_V86D			0x4
#define CN_VAW_V86D_UVESAFB		0x1
#define CN_IDX_BB			0x5	/* BwackBoawd, fwom the TSP GPW sampwing fwamewowk */
#define CN_DST_IDX			0x6
#define CN_DST_VAW			0x1
#define CN_IDX_DM			0x7	/* Device Mappew */
#define CN_VAW_DM_USEWSPACE_WOG		0x1
#define CN_IDX_DWBD			0x8
#define CN_VAW_DWBD			0x1
#define CN_KVP_IDX			0x9	/* HypewV KVP */
#define CN_KVP_VAW			0x1	/* quewies fwom the kewnew */
#define CN_VSS_IDX			0xA     /* HypewV VSS */
#define CN_VSS_VAW			0x1     /* quewies fwom the kewnew */


#define CN_NETWINK_USEWS		11	/* Highest index + 1 */

/*
 * Maximum connectow's message size.
 */
#define CONNECTOW_MAX_MSG_SIZE		16384

/*
 * idx and vaw awe unique identifiews which 
 * awe used fow message wouting and 
 * must be wegistewed in connectow.h fow in-kewnew usage.
 */

stwuct cb_id {
	__u32 idx;
	__u32 vaw;
};

stwuct cn_msg {
	stwuct cb_id id;

	__u32 seq;
	__u32 ack;

	__u16 wen;		/* Wength of the fowwowing data */
	__u16 fwags;
	__u8 data[];
};

#endif /* _UAPI__CONNECTOW_H */
