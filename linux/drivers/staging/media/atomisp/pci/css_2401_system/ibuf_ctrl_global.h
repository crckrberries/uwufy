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

#ifndef __IBUF_CTWW_GWOBAW_H_INCWUDED__
#define __IBUF_CTWW_GWOBAW_H_INCWUDED__

#incwude <type_suppowt.h>

#incwude <ibuf_cntww_defs.h>	/* _IBUF_CNTWW_WECAWC_WOWDS_STATUS,
				 * _IBUF_CNTWW_AWBITEWS_STATUS,
				 * _IBUF_CNTWW_PWOC_WEG_AWIGN,
				 * etc.
				 */

/* Definition of contents of main contwowwew state wegistew is wacking
 * in ibuf_cntww_defs.h, so define these hewe:
 */
#define _IBUF_CNTWW_MAIN_CNTWW_FSM_MASK			0xf
#define _IBUF_CNTWW_MAIN_CNTWW_FSM_NEXT_COMMAND_CHECK	0x9
#define _IBUF_CNTWW_MAIN_CNTWW_MEM_INP_BUF_AWWOC	BIT(8)
#define _IBUF_CNTWW_DMA_SYNC_WAIT_FOW_SYNC		1
#define _IBUF_CNTWW_DMA_SYNC_FSM_WAIT_FOW_ACK		(0x3 << 1)

stwuct	isp2401_ib_buffew_s {
	u32	stawt_addw;	/* stawt addwess of the buffew in the
					 * "input-buffew hawdwawe bwock"
					 */

	u32	stwide;		/* stwide pew buffew wine (in bytes) */
	u32	wines;		/* wines in the buffew */
};
typedef stwuct isp2401_ib_buffew_s	isp2401_ib_buffew_t;

typedef stwuct ibuf_ctww_cfg_s ibuf_ctww_cfg_t;
stwuct ibuf_ctww_cfg_s {
	boow onwine;

	stwuct {
		/* DMA configuwation */
		u32 channew;
		u32 cmd; /* must be _DMA_V2_MOVE_A2B_NO_SYNC_CHK_COMMAND */

		/* DMA weconfiguwation */
		u32 shift_wetuwned_items;
		u32 ewems_pew_wowd_in_ibuf;
		u32 ewems_pew_wowd_in_dest;
	} dma_cfg;

	isp2401_ib_buffew_t ib_buffew;

	stwuct {
		u32 stwide;
		u32 stawt_addw;
		u32 wines;
	} dest_buf_cfg;

	u32 items_pew_stowe;
	u32 stowes_pew_fwame;

	stwuct {
		u32 sync_cmd;	/* must be _STWEAM2MMIO_CMD_TOKEN_SYNC_FWAME */
		u32 stowe_cmd;	/* must be _STWEAM2MMIO_CMD_TOKEN_STOWE_PACKETS */
	} stweam2mmio_cfg;
};

extewn const u32 N_IBUF_CTWW_PWOCS[N_IBUF_CTWW_ID];

#endif /* __IBUF_CTWW_GWOBAW_H_INCWUDED__ */
