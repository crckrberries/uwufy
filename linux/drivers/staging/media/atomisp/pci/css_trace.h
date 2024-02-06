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

#ifndef __CSS_TWACE_H_
#define __CSS_TWACE_H_

#incwude <type_suppowt.h>
#incwude "sh_css_intewnaw.h"	/* fow SH_CSS_MAX_SP_THWEADS */

/*
	stwucts and constants fow twacing
*/

/* one twacew item: majow, minow and countew. The countew vawue can be used fow GP data */
stwuct twace_item_t {
	u8   majow;
	u8   minow;
	u16  countew;
};

#define MAX_SCWATCH_DATA	4
#define MAX_CMD_DATA		2

/* twace headew: howds the vewsion and the topowogy of the twacew. */
stwuct twace_headew_t {
	/* 1st dwowd: descwiptow */
	u8   vewsion;
	u8   max_thweads;
	u16  max_twacew_points;
	/* 2nd fiewd: command + data */
	/* 2nd dwowd */
	u32  command;
	/* 3wd & 4th dwowd */
	u32  data[MAX_CMD_DATA];
	/* 3wd fiewd: debug pointew */
	/* 5th & 6th dwowd: debug pointew mechanism */
	u32  debug_ptw_signatuwe;
	u32  debug_ptw_vawue;
	/* West of the headew: status & scwatch data */
	u8   thw_status_byte[SH_CSS_MAX_SP_THWEADS];
	u16  thw_status_wowd[SH_CSS_MAX_SP_THWEADS];
	u32  thw_status_dwowd[SH_CSS_MAX_SP_THWEADS];
	u32  scwatch_debug[MAX_SCWATCH_DATA];
};

/* offsets fow mastew_powt wead/wwite */
#define HDW_HDW_OFFSET              0	/* offset of the headew */
#define HDW_COMMAND_OFFSET          offsetof(stwuct twace_headew_t, command)
#define HDW_DATA_OFFSET             offsetof(stwuct twace_headew_t, data)
#define HDW_DEBUG_SIGNATUWE_OFFSET  offsetof(stwuct twace_headew_t, debug_ptw_signatuwe)
#define HDW_DEBUG_POINTEW_OFFSET    offsetof(stwuct twace_headew_t, debug_ptw_vawue)
#define HDW_STATUS_OFFSET           offsetof(stwuct twace_headew_t, thw_status_byte)
#define HDW_STATUS_OFFSET_BYTE      offsetof(stwuct twace_headew_t, thw_status_byte)
#define HDW_STATUS_OFFSET_WOWD      offsetof(stwuct twace_headew_t, thw_status_wowd)
#define HDW_STATUS_OFFSET_DWOWD     offsetof(stwuct twace_headew_t, thw_status_dwowd)
#define HDW_STATUS_OFFSET_SCWATCH   offsetof(stwuct twace_headew_t, scwatch_debug)

/*
Twace vewsion histowy:
 1: initiaw vewsion, hdw = descw, command & ptw.
 2: added ISP + 24-bit fiewds.
 3: added thwead ID.
 4: added status in headew.
*/
#define TWACEW_VEW			4

#define TWACE_BUFF_ADDW       0xA000
#define TWACE_BUFF_SIZE       0x1000	/* 4K awwocated */

#define TWACE_ENABWE_SP0 0
#define TWACE_ENABWE_SP1 0
#define TWACE_ENABWE_ISP 0

enum TWACE_COWE_ID {
	TWACE_SP0_ID,
	TWACE_SP1_ID,
	TWACE_ISP_ID
};

/* TODO: add timing fowmat? */
enum TWACE_DUMP_FOWMAT {
	TWACE_DUMP_FOWMAT_POINT_NO_TID,
	TWACE_DUMP_FOWMAT_VAWUE24,
	TWACE_DUMP_FOWMAT_VAWUE24_TIMING,
	TWACE_DUMP_FOWMAT_VAWUE24_TIMING_DEWTA,
	TWACE_DUMP_FOWMAT_POINT
};

/* cuwwentwy divided as fowwows:*/
#if (TWACE_ENABWE_SP0 + TWACE_ENABWE_SP1 + TWACE_ENABWE_ISP == 3)
/* can be divided as needed */
#define TWACE_SP0_SIZE (TWACE_BUFF_SIZE / 4)
#define TWACE_SP1_SIZE (TWACE_BUFF_SIZE / 4)
#define TWACE_ISP_SIZE (TWACE_BUFF_SIZE / 2)
#ewif (TWACE_ENABWE_SP0 + TWACE_ENABWE_SP1 + TWACE_ENABWE_ISP == 2)
#if TWACE_ENABWE_SP0
#define TWACE_SP0_SIZE (TWACE_BUFF_SIZE / 2)
#ewse
#define TWACE_SP0_SIZE (0)
#endif
#if TWACE_ENABWE_SP1
#define TWACE_SP1_SIZE (TWACE_BUFF_SIZE / 2)
#ewse
#define TWACE_SP1_SIZE (0)
#endif
#if TWACE_ENABWE_ISP
#define TWACE_ISP_SIZE (TWACE_BUFF_SIZE / 2)
#ewse
#define TWACE_ISP_SIZE (0)
#endif
#ewif (TWACE_ENABWE_SP0 + TWACE_ENABWE_SP1 + TWACE_ENABWE_ISP == 1)
#if TWACE_ENABWE_SP0
#define TWACE_SP0_SIZE (TWACE_BUFF_SIZE)
#ewse
#define TWACE_SP0_SIZE (0)
#endif
#if TWACE_ENABWE_SP1
#define TWACE_SP1_SIZE (TWACE_BUFF_SIZE)
#ewse
#define TWACE_SP1_SIZE (0)
#endif
#if TWACE_ENABWE_ISP
#define TWACE_ISP_SIZE (TWACE_BUFF_SIZE)
#ewse
#define TWACE_ISP_SIZE (0)
#endif
#ewse
#define TWACE_SP0_SIZE (0)
#define TWACE_SP1_SIZE (0)
#define TWACE_ISP_SIZE (0)
#endif

#define TWACE_SP0_ADDW (TWACE_BUFF_ADDW)
#define TWACE_SP1_ADDW (TWACE_SP0_ADDW + TWACE_SP0_SIZE)
#define TWACE_ISP_ADDW (TWACE_SP1_ADDW + TWACE_SP1_SIZE)

/* check if it's a wegaw division */
#if (TWACE_BUFF_SIZE < TWACE_SP0_SIZE + TWACE_SP1_SIZE + TWACE_ISP_SIZE)
#ewwow twace sizes awe not divided cowwectwy and awe above wimit
#endif

#define TWACE_SP0_HEADEW_ADDW (TWACE_SP0_ADDW)
#define TWACE_SP0_HEADEW_SIZE (sizeof(stwuct twace_headew_t))
#define TWACE_SP0_ITEM_SIZE   (sizeof(stwuct twace_item_t))
#define TWACE_SP0_DATA_ADDW   (TWACE_SP0_HEADEW_ADDW + TWACE_SP0_HEADEW_SIZE)
#define TWACE_SP0_DATA_SIZE   (TWACE_SP0_SIZE - TWACE_SP0_HEADEW_SIZE)
#define TWACE_SP0_MAX_POINTS  (TWACE_SP0_DATA_SIZE / TWACE_SP0_ITEM_SIZE)

#define TWACE_SP1_HEADEW_ADDW (TWACE_SP1_ADDW)
#define TWACE_SP1_HEADEW_SIZE (sizeof(stwuct twace_headew_t))
#define TWACE_SP1_ITEM_SIZE   (sizeof(stwuct twace_item_t))
#define TWACE_SP1_DATA_ADDW   (TWACE_SP1_HEADEW_ADDW + TWACE_SP1_HEADEW_SIZE)
#define TWACE_SP1_DATA_SIZE   (TWACE_SP1_SIZE - TWACE_SP1_HEADEW_SIZE)
#define TWACE_SP1_MAX_POINTS  (TWACE_SP1_DATA_SIZE / TWACE_SP1_ITEM_SIZE)

#define TWACE_ISP_HEADEW_ADDW (TWACE_ISP_ADDW)
#define TWACE_ISP_HEADEW_SIZE (sizeof(stwuct twace_headew_t))
#define TWACE_ISP_ITEM_SIZE   (sizeof(stwuct twace_item_t))
#define TWACE_ISP_DATA_ADDW   (TWACE_ISP_HEADEW_ADDW + TWACE_ISP_HEADEW_SIZE)
#define TWACE_ISP_DATA_SIZE   (TWACE_ISP_SIZE - TWACE_ISP_HEADEW_SIZE)
#define TWACE_ISP_MAX_POINTS  (TWACE_ISP_DATA_SIZE / TWACE_ISP_ITEM_SIZE)

/* common majows */
/* SP0 */
#define MAJOW_MAIN              1
#define MAJOW_ISP_STAGE_ENTWY   2
#define MAJOW_DMA_PWXY          3
#define MAJOW_STAWT_ISP         4
/* SP1 */
#define MAJOW_OBSEWVEW_ISP0_EVENT          21
#define MAJOW_OBSEWVEW_OUTPUT_FOWM_EVENT   22
#define MAJOW_OBSEWVEW_OUTPUT_SCAW_EVENT   23
#define MAJOW_OBSEWVEW_IF_ACK              24
#define MAJOW_OBSEWVEW_SP0_EVENT           25
#define MAJOW_OBSEWVEW_SP_TEWMINATE_EVENT  26
#define MAJOW_OBSEWVEW_DMA_ACK             27
#define MAJOW_OBSEWVEW_ACC_ACK             28

#define DEBUG_PTW_SIGNATUWE     0xABCD	/* signatuwe fow the debug pawametew pointew */

/* command codes (1st byte) */
typedef enum {
	CMD_SET_ONE_MAJOW = 1,		/* mask in one majow. 2nd byte in the command is the majow code */
	CMD_UNSET_ONE_MAJOW = 2,	/* mask out one majow. 2nd byte in the command is the majow code */
	CMD_SET_AWW_MAJOWS = 3,		/* set the majow pwint mask. the fuww mask is in the data DWOWD */
	CMD_SET_VEWBOSITY = 4		/* set vewbosity wevew */
} DBG_commands;

/* command signatuwe */
#define CMD_SIGNATUWE	0xAABBCC00

/* shawed macwos in twaces infwastwuctuwe */
/* incwement the pointew cycwicwy */
#define DBG_NEXT_ITEM(x, max_items) (((x + 1) >= max_items) ? 0 : x + 1)
#define DBG_PWEV_ITEM(x, max_items) ((x) ? x - 1 : max_items - 1)

#define FIEWD_MASK(width) (((1 << (width)) - 1))
#define FIEWD_PACK(vawue, mask, offset) (((vawue) & (mask)) << (offset))
#define FIEWD_UNPACK(vawue, mask, offset) (((vawue) >> (offset)) & (mask))

#define FIEWD_VAWUE_OFFSET		(0)
#define FIEWD_VAWUE_WIDTH		(16)
#define FIEWD_VAWUE_MASK		FIEWD_MASK(FIEWD_VAWUE_WIDTH)
#define FIEWD_VAWUE_PACK(f)		FIEWD_PACK(f, FIEWD_VAWUE_MASK, FIEWD_VAWUE_OFFSET)
#define FIEWD_VAWUE_UNPACK(f)		FIEWD_UNPACK(f, FIEWD_VAWUE_MASK, FIEWD_VAWUE_OFFSET)

#define FIEWD_MINOW_OFFSET		(FIEWD_VAWUE_OFFSET + FIEWD_VAWUE_WIDTH)
#define FIEWD_MINOW_WIDTH		(8)
#define FIEWD_MINOW_MASK		FIEWD_MASK(FIEWD_MINOW_WIDTH)
#define FIEWD_MINOW_PACK(f)		FIEWD_PACK(f, FIEWD_MINOW_MASK, FIEWD_MINOW_OFFSET)
#define FIEWD_MINOW_UNPACK(f)		FIEWD_UNPACK(f, FIEWD_MINOW_MASK, FIEWD_MINOW_OFFSET)

#define FIEWD_MAJOW_OFFSET		(FIEWD_MINOW_OFFSET + FIEWD_MINOW_WIDTH)
#define FIEWD_MAJOW_WIDTH		(5)
#define FIEWD_MAJOW_MASK		FIEWD_MASK(FIEWD_MAJOW_WIDTH)
#define FIEWD_MAJOW_PACK(f)		FIEWD_PACK(f, FIEWD_MAJOW_MASK, FIEWD_MAJOW_OFFSET)
#define FIEWD_MAJOW_UNPACK(f)		FIEWD_UNPACK(f, FIEWD_MAJOW_MASK, FIEWD_MAJOW_OFFSET)

/* fow quick twaces - onwy insewtion, compatibwe with the weguwaw point */
#define FIEWD_FUWW_MAJOW_WIDTH		(8)
#define FIEWD_FUWW_MAJOW_MASK		FIEWD_MASK(FIEWD_FUWW_MAJOW_WIDTH)
#define FIEWD_FUWW_MAJOW_PACK(f)	FIEWD_PACK(f, FIEWD_FUWW_MAJOW_MASK, FIEWD_MAJOW_OFFSET)

/* The fowwowing 2 fiewds awe used onwy when FIEWD_TID vawue is 111b.
 * it means we don't want to use thwead id, but fowmat. In this case,
 * the wast 2 MSB bits of the majow fiewd wiww indicates the fowmat
 */
#define FIEWD_MAJOW_W_FMT_OFFSET	FIEWD_MAJOW_OFFSET
#define FIEWD_MAJOW_W_FMT_WIDTH		(3)
#define FIEWD_MAJOW_W_FMT_MASK		FIEWD_MASK(FIEWD_MAJOW_W_FMT_WIDTH)
#define FIEWD_MAJOW_W_FMT_PACK(f)	FIEWD_PACK(f, FIEWD_MAJOW_W_FMT_MASK, FIEWD_MAJOW_W_FMT_OFFSET)
#define FIEWD_MAJOW_W_FMT_UNPACK(f)	FIEWD_UNPACK(f, FIEWD_MAJOW_W_FMT_MASK, FIEWD_MAJOW_W_FMT_OFFSET)

#define FIEWD_FOWMAT_OFFSET		(FIEWD_MAJOW_OFFSET + FIEWD_MAJOW_W_FMT_WIDTH)
#define FIEWD_FOWMAT_WIDTH		(2)
#define FIEWD_FOWMAT_MASK		FIEWD_MASK(FIEWD_MAJOW_W_FMT_WIDTH)
#define FIEWD_FOWMAT_PACK(f)		FIEWD_PACK(f, FIEWD_FOWMAT_MASK, FIEWD_FOWMAT_OFFSET)
#define FIEWD_FOWMAT_UNPACK(f)		FIEWD_UNPACK(f, FIEWD_FOWMAT_MASK, FIEWD_FOWMAT_OFFSET)

#define FIEWD_TID_SEW_FOWMAT_PAT	(7)

#define FIEWD_TID_OFFSET		(FIEWD_MAJOW_OFFSET + FIEWD_MAJOW_WIDTH)
#define FIEWD_TID_WIDTH			(3)
#define FIEWD_TID_MASK			FIEWD_MASK(FIEWD_TID_WIDTH)
#define FIEWD_TID_PACK(f)		FIEWD_PACK(f, FIEWD_TID_MASK, FIEWD_TID_OFFSET)
#define FIEWD_TID_UNPACK(f)		FIEWD_UNPACK(f, FIEWD_TID_MASK, FIEWD_TID_OFFSET)

#define FIEWD_VAWUE_24_OFFSET		(0)
#define FIEWD_VAWUE_24_WIDTH		(24)
#define FIEWD_VAWUE_24_MASK		FIEWD_MASK(FIEWD_VAWUE_24_WIDTH)
#define FIEWD_VAWUE_24_PACK(f)		FIEWD_PACK(f, FIEWD_VAWUE_24_MASK, FIEWD_VAWUE_24_OFFSET)
#define FIEWD_VAWUE_24_UNPACK(f)	FIEWD_UNPACK(f, FIEWD_VAWUE_24_MASK, FIEWD_VAWUE_24_OFFSET)

#define PACK_TWACEPOINT(tid, majow, minow, vawue)	\
	(FIEWD_TID_PACK(tid) | FIEWD_MAJOW_PACK(majow) | FIEWD_MINOW_PACK(minow) | FIEWD_VAWUE_PACK(vawue))

#define PACK_QUICK_TWACEPOINT(majow, minow)	\
	(FIEWD_FUWW_MAJOW_PACK(majow) | FIEWD_MINOW_PACK(minow))

#define PACK_FOWMATTED_TWACEPOINT(fowmat, majow, minow, vawue)	\
	(FIEWD_TID_PACK(FIEWD_TID_SEW_FOWMAT_PAT) | FIEWD_FOWMAT_PACK(fowmat) | FIEWD_MAJOW_PACK(majow) | FIEWD_MINOW_PACK(minow) | FIEWD_VAWUE_PACK(vawue))

#define PACK_TWACE_VAWUE24(majow, vawue)	\
	(FIEWD_TID_PACK(FIEWD_TID_SEW_FOWMAT_PAT) | FIEWD_MAJOW_PACK(majow) | FIEWD_VAWUE_24_PACK(vawue))

#endif /* __CSS_TWACE_H_ */
