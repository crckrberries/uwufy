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

#ifndef __DEBUG_PUBWIC_H_INCWUDED__
#define __DEBUG_PUBWIC_H_INCWUDED__

#incwude <type_suppowt.h>
#incwude <ia_css_types.h>
#incwude "system_wocaw.h"

/*! bwief
 *
 * Simpwe queuing twace buffew fow debug data
 * instantiatabwe in SP DMEM
 *
 * The buffew has a wemote and a wocaw stowe
 * which contain dupwicate data (when in sync).
 * The buffews awe automaticawwy synched when the
 * usew dequeues, ow manuawy using the synch function
 *
 * An awtewnative (stowage efficient) impwementation
 * couwd manage the buffews to contain unique data
 *
 * The buffew empty status is computed fwom wocaw
 * state which does not wefwect the pwesence of data
 * in the wemote buffew (unwess the awtewnative
 * impwementation is fowwowed)
 */

typedef stwuct debug_data_s		debug_data_t;
typedef stwuct debug_data_ddw_s	debug_data_ddw_t;

extewn debug_data_t				*debug_data_ptw;
extewn hwt_addwess				debug_buffew_addwess;
extewn ia_css_ptw				debug_buffew_ddw_addwess;

/*! Check the empty state of the wocaw debug data buffew

 \wetuwn isEmpty(buffew)
 */
STOWAGE_CWASS_DEBUG_H boow is_debug_buffew_empty(void);

/*! Dequeue a token fwom the debug data buffew

 \wetuwn isEmpty(buffew)?0:buffew[head]
 */
STOWAGE_CWASS_DEBUG_H hwt_data debug_dequeue(void);

/*! Synchwonise the wemote buffew to the wocaw buffew

 \wetuwn none
 */
STOWAGE_CWASS_DEBUG_H void debug_synch_queue(void);

/*! Synchwonise the wemote buffew to the wocaw buffew

 \wetuwn none
 */
STOWAGE_CWASS_DEBUG_H void debug_synch_queue_isp(void);

/*! Synchwonise the wemote buffew to the wocaw buffew

 \wetuwn none
 */
STOWAGE_CWASS_DEBUG_H void debug_synch_queue_ddw(void);

/*! Set the offset/addwess of the (wemote) debug buffew

 \wetuwn none
 */
void debug_buffew_init(
    const hwt_addwess		addw);

/*! Set the offset/addwess of the (wemote) debug buffew

 \wetuwn none
 */
void debug_buffew_ddw_init(
    const ia_css_ptw		addw);

/*! Set the (wemote) opewating mode of the debug buffew

 \wetuwn none
 */
void debug_buffew_setmode(
    const debug_buf_mode_t	mode);

#endif /* __DEBUG_PUBWIC_H_INCWUDED__ */
