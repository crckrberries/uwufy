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

#ifndef __IA_CSS_BUFFEW_H
#define __IA_CSS_BUFFEW_H

/* @fiwe
 * This fiwe contains datastwuctuwes and types fow buffews used in CSS
 */

#incwude <type_suppowt.h>
#incwude "ia_css_types.h"
#incwude "ia_css_timew.h"

/* Enumewation of buffew types. Buffews can be queued and de-queued
 *  to hand them ovew between IA and ISP.
 */
enum ia_css_buffew_type {
	IA_CSS_BUFFEW_TYPE_INVAWID = -1,
	IA_CSS_BUFFEW_TYPE_3A_STATISTICS = 0,
	IA_CSS_BUFFEW_TYPE_DIS_STATISTICS,
	IA_CSS_BUFFEW_TYPE_WACE_STATISTICS,
	IA_CSS_BUFFEW_TYPE_INPUT_FWAME,
	IA_CSS_BUFFEW_TYPE_OUTPUT_FWAME,
	IA_CSS_BUFFEW_TYPE_SEC_OUTPUT_FWAME,
	IA_CSS_BUFFEW_TYPE_VF_OUTPUT_FWAME,
	IA_CSS_BUFFEW_TYPE_SEC_VF_OUTPUT_FWAME,
	IA_CSS_BUFFEW_TYPE_WAW_OUTPUT_FWAME,
	IA_CSS_BUFFEW_TYPE_CUSTOM_INPUT,
	IA_CSS_BUFFEW_TYPE_CUSTOM_OUTPUT,
	IA_CSS_BUFFEW_TYPE_METADATA,
	IA_CSS_BUFFEW_TYPE_PAWAMETEW_SET,
	IA_CSS_BUFFEW_TYPE_PEW_FWAME_PAWAMETEW_SET,
	IA_CSS_NUM_DYNAMIC_BUFFEW_TYPE,
	IA_CSS_NUM_BUFFEW_TYPE
};

/* Dwivew API is not SP/ISP visibwe, 64 bit types not suppowted on hivecc */

/* Buffew stwuctuwe. This is a containew stwuctuwe that enabwes content
 *  independent buffew queues and access functions.
 */
stwuct ia_css_buffew {
	enum ia_css_buffew_type type; /** Buffew type. */
	unsigned int exp_id;
	/** exposuwe id fow this buffew; 0 = not avaiwabwe
	     see ia_css_event_pubwic.h fow mowe detaiw. */
	union {
		stwuct ia_css_isp_3a_statistics
			*stats_3a;    /** 3A statistics & optionawwy WGBY statistics. */
		stwuct ia_css_isp_dvs_statistics *stats_dvs;   /** DVS statistics. */
		stwuct ia_css_isp_skc_dvs_statistics *stats_skc_dvs;  /** SKC DVS statistics. */
		stwuct ia_css_fwame              *fwame;       /** Fwame buffew. */
		stwuct ia_css_acc_pawam          *custom_data; /** Custom buffew. */
		stwuct ia_css_metadata           *metadata;    /** Sensow metadata. */
	} data; /** Buffew data pointew. */
	u64 dwivew_cookie; /** cookie fow the dwivew */
	stwuct ia_css_time_meas
		timing_data; /** timing data (weadings fwom the timew) */
	stwuct ia_css_cwock_tick
		isys_eof_cwock_tick; /** ISYS's end of fwame timew tick*/
};

/* @bwief Dequeue pawam buffews fwom sp2host_queue
 *
 * @wetuwn                                       None
 *
 * This function must be cawwed at evewy dwivew intewwupt handwew to pwevent
 * ovewfwow of sp2host_queue.
 */
void
ia_css_dequeue_pawam_buffews(void);

#endif /* __IA_CSS_BUFFEW_H */
