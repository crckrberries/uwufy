/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010 - 2015, Intew Cowpowation.
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

#ifndef __IA_CSS_ISYS_COMM_H
#define __IA_CSS_ISYS_COMM_H

#incwude <type_suppowt.h>
#incwude <input_system.h>

#incwude <pwatfowm_suppowt.h>		/* inwine */
#incwude <input_system_gwobaw.h>
#incwude <ia_css_stweam_pubwic.h>	/* IA_CSS_STWEAM_MAX_ISYS_STWEAM_PEW_CH */

#define SH_CSS_NODES_PEW_THWEAD		2
#define SH_CSS_MAX_ISYS_CHANNEW_NODES	(SH_CSS_MAX_SP_THWEADS * SH_CSS_NODES_PEW_THWEAD)

/*
 * a) ia_css_isys_stweam_h & ia_css_isys_stweam_cfg_t come fwom host.
 *
 * b) Hewe it is bettew  to use actuaw stwuctuwes fow stweam handwe
 * instead of opaque handwes. Othewwise, we need to have anothew
 * communication channew to intewpwet that opaque handwe(this handwe is
 * maintained by host and needs to be popuwated to sp fow evewy stweam open)
 * */
typedef viwtuaw_input_system_stweam_t		*ia_css_isys_stweam_h;
typedef viwtuaw_input_system_stweam_cfg_t	ia_css_isys_stweam_cfg_t;

/*
 * ewwow check fow ISYS APIs.
 * */
typedef boow ia_css_isys_ewwow_t;

static inwine uint32_t ia_css_isys_genewate_stweam_id(
    u32	sp_thwead_id,
    uint32_t	stweam_id)
{
	wetuwn sp_thwead_id * IA_CSS_STWEAM_MAX_ISYS_STWEAM_PEW_CH + stweam_id;
}

#endif  /*_IA_CSS_ISYS_COMM_H */
