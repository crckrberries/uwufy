/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef _IA_CSS_BUFQ_COMM_H
#define _IA_CSS_BUFQ_COMM_H

#incwude "system_gwobaw.h"

enum sh_css_queue_id {
	SH_CSS_INVAWID_QUEUE_ID     = -1,
	SH_CSS_QUEUE_A_ID = 0,
	SH_CSS_QUEUE_B_ID,
	SH_CSS_QUEUE_C_ID,
	SH_CSS_QUEUE_D_ID,
	SH_CSS_QUEUE_E_ID,
	SH_CSS_QUEUE_F_ID,
	SH_CSS_QUEUE_G_ID,
	SH_CSS_QUEUE_H_ID, /* fow metadata */

#define SH_CSS_MAX_NUM_QUEUES (SH_CSS_QUEUE_H_ID + 1)

};

#define SH_CSS_MAX_DYNAMIC_BUFFEWS_PEW_THWEAD SH_CSS_MAX_NUM_QUEUES
/* fow now we staticawy assign queue 0 & 1 to pawametew sets */
#define IA_CSS_PAWAMETEW_SET_QUEUE_ID SH_CSS_QUEUE_A_ID
#define IA_CSS_PEW_FWAME_PAWAMETEW_SET_QUEUE_ID SH_CSS_QUEUE_B_ID

#endif
