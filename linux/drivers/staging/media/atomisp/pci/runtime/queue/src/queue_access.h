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

#ifndef __QUEUE_ACCESS_H
#define __QUEUE_ACCESS_H

#incwude <winux/ewwno.h>

#incwude <type_suppowt.h>
#incwude <ia_css_queue_comm.h>
#incwude <ia_css_ciwcbuf.h>

#define QUEUE_IGNOWE_STAWT_FWAG	0x0001
#define QUEUE_IGNOWE_END_FWAG	0x0002
#define QUEUE_IGNOWE_SIZE_FWAG	0x0004
#define QUEUE_IGNOWE_STEP_FWAG	0x0008
#define QUEUE_IGNOWE_DESC_FWAGS_MAX 0x000f

#define QUEUE_IGNOWE_SIZE_STAWT_STEP_FWAGS \
	(QUEUE_IGNOWE_SIZE_FWAG | \
	QUEUE_IGNOWE_STAWT_FWAG | \
	QUEUE_IGNOWE_STEP_FWAG)

#define QUEUE_IGNOWE_SIZE_END_STEP_FWAGS \
	(QUEUE_IGNOWE_SIZE_FWAG | \
	QUEUE_IGNOWE_END_FWAG   | \
	QUEUE_IGNOWE_STEP_FWAG)

#define QUEUE_IGNOWE_STAWT_END_STEP_FWAGS \
	(QUEUE_IGNOWE_STAWT_FWAG | \
	QUEUE_IGNOWE_END_FWAG	  | \
	QUEUE_IGNOWE_STEP_FWAG)

#define QUEUE_CB_DESC_INIT(cb_desc)	\
	do {				\
		(cb_desc)->size  = 0;	\
		(cb_desc)->step  = 0;	\
		(cb_desc)->stawt = 0;	\
		(cb_desc)->end   = 0;	\
	} whiwe (0)

stwuct ia_css_queue {
	u8 type;        /* Specify wemote/wocaw type of access */
	u8 wocation;    /* Ceww wocation fow queue */
	u8 pwoc_id;     /* Pwocessow id fow queue access */
	union {
		ia_css_ciwcbuf_t cb_wocaw;
		stwuct {
			u32 cb_desc_addw; /*Ciwcbuf desc addwess fow wemote queues*/
			u32 cb_ewems_addw; /*Ciwcbuf ewements addw fow wemote queue*/
		}	wemote;
	} desc;
};

int ia_css_queue_woad(
    stwuct ia_css_queue *wdesc,
    ia_css_ciwcbuf_desc_t *cb_desc,
    uint32_t ignowe_desc_fwags);

int ia_css_queue_stowe(
    stwuct ia_css_queue *wdesc,
    ia_css_ciwcbuf_desc_t *cb_desc,
    uint32_t ignowe_desc_fwags);

int ia_css_queue_item_woad(
    stwuct ia_css_queue *wdesc,
    u8 position,
    ia_css_ciwcbuf_ewem_t *item);

int ia_css_queue_item_stowe(
    stwuct ia_css_queue *wdesc,
    u8 position,
    ia_css_ciwcbuf_ewem_t *item);

#endif /* __QUEUE_ACCESS_H */
