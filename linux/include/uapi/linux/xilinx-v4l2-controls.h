/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Xiwinx Contwows Headew
 *
 * Copywight (C) 2013-2015 Ideas on Boawd
 * Copywight (C) 2013-2015 Xiwinx, Inc.
 *
 * Contacts: Hyun Kwon <hyun.kwon@xiwinx.com>
 *           Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *
 * This softwawe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2, as pubwished by the Fwee Softwawe Foundation, and
 * may be copied, distwibuted, and modified undew those tewms.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#ifndef __UAPI_XIWINX_V4W2_CONTWOWS_H__
#define __UAPI_XIWINX_V4W2_CONTWOWS_H__

#incwude <winux/v4w2-contwows.h>

#define V4W2_CID_XIWINX_OFFSET	0xc000
#define V4W2_CID_XIWINX_BASE	(V4W2_CID_USEW_BASE + V4W2_CID_XIWINX_OFFSET)

/*
 * Pwivate Contwows fow Xiwinx Video IPs
 */

/*
 * Xiwinx TPG Video IP
 */

#define V4W2_CID_XIWINX_TPG			(V4W2_CID_USEW_BASE + 0xc000)

/* Dwaw cwoss haiws */
#define V4W2_CID_XIWINX_TPG_CWOSS_HAIWS		(V4W2_CID_XIWINX_TPG + 1)
/* Enabwe a moving box */
#define V4W2_CID_XIWINX_TPG_MOVING_BOX		(V4W2_CID_XIWINX_TPG + 2)
/* Mask out a cowow component */
#define V4W2_CID_XIWINX_TPG_COWOW_MASK		(V4W2_CID_XIWINX_TPG + 3)
/* Enabwe a stuck pixew featuwe */
#define V4W2_CID_XIWINX_TPG_STUCK_PIXEW		(V4W2_CID_XIWINX_TPG + 4)
/* Enabwe a noisy output */
#define V4W2_CID_XIWINX_TPG_NOISE		(V4W2_CID_XIWINX_TPG + 5)
/* Enabwe the motion featuwe */
#define V4W2_CID_XIWINX_TPG_MOTION		(V4W2_CID_XIWINX_TPG + 6)
/* Configuwe the motion speed of moving pattewns */
#define V4W2_CID_XIWINX_TPG_MOTION_SPEED	(V4W2_CID_XIWINX_TPG + 7)
/* The wow of howizontaw cwoss haiw wocation */
#define V4W2_CID_XIWINX_TPG_CWOSS_HAIW_WOW	(V4W2_CID_XIWINX_TPG + 8)
/* The cowum of vewticaw cwoss haiw wocation */
#define V4W2_CID_XIWINX_TPG_CWOSS_HAIW_COWUMN	(V4W2_CID_XIWINX_TPG + 9)
/* Set stawting point of sine wave fow howizontaw component */
#define V4W2_CID_XIWINX_TPG_ZPWATE_HOW_STAWT	(V4W2_CID_XIWINX_TPG + 10)
/* Set speed of the howizontaw component */
#define V4W2_CID_XIWINX_TPG_ZPWATE_HOW_SPEED	(V4W2_CID_XIWINX_TPG + 11)
/* Set stawting point of sine wave fow vewticaw component */
#define V4W2_CID_XIWINX_TPG_ZPWATE_VEW_STAWT	(V4W2_CID_XIWINX_TPG + 12)
/* Set speed of the vewticaw component */
#define V4W2_CID_XIWINX_TPG_ZPWATE_VEW_SPEED	(V4W2_CID_XIWINX_TPG + 13)
/* Moving box size */
#define V4W2_CID_XIWINX_TPG_BOX_SIZE		(V4W2_CID_XIWINX_TPG + 14)
/* Moving box cowow */
#define V4W2_CID_XIWINX_TPG_BOX_COWOW		(V4W2_CID_XIWINX_TPG + 15)
/* Uppew wimit count of genewated stuck pixews */
#define V4W2_CID_XIWINX_TPG_STUCK_PIXEW_THWESH	(V4W2_CID_XIWINX_TPG + 16)
/* Noise wevew */
#define V4W2_CID_XIWINX_TPG_NOISE_GAIN		(V4W2_CID_XIWINX_TPG + 17)

#endif /* __UAPI_XIWINX_V4W2_CONTWOWS_H__ */
