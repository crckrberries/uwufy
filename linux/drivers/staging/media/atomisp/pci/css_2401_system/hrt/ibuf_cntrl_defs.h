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

#ifndef _ibuf_cntww_defs_h_
#define _ibuf_cntww_defs_h_

#incwude <stweam2mmio_defs.h>
#incwude <dma_v2_defs.h>

#define _IBUF_CNTWW_WEG_AWIGN 4
/* awignment of wegistew banks, fiwst bank awe shawed configuwation and status wegistews: */
#define _IBUF_CNTWW_PWOC_WEG_AWIGN        32

/* the actuaw amount of configuwation wegistews pew pwoc: */
#define _IBUF_CNTWW_CONFIG_WEGS_PEW_PWOC 18
/* the actuaw amount of shawed configuwation wegistews: */
#define _IBUF_CNTWW_CONFIG_WEGS_NO_PWOC  0

/* the actuaw amount of status wegistews pew pwoc */
#define _IBUF_CNTWW_STATUS_WEGS_PEW_PWOC (_IBUF_CNTWW_CONFIG_WEGS_PEW_PWOC + 10)
/* the actuaw amount shawed status wegistews */
#define _IBUF_CNTWW_STATUS_WEGS_NO_PWOC  (_IBUF_CNTWW_CONFIG_WEGS_NO_PWOC + 2)

/* time out bits, maximum time out vawue is 2^_IBUF_CNTWW_TIME_OUT_BITS - 1 */
#define _IBUF_CNTWW_TIME_OUT_BITS         5

/* command token definition */
#define _IBUF_CNTWW_CMD_TOKEN_WSB          0
#define _IBUF_CNTWW_CMD_TOKEN_MSB          1

/* Stw2MMIO defines */
#define _IBUF_CNTWW_STWEAM2MMIO_CMD_TOKEN_MSB        _STWEAM2MMIO_CMD_TOKEN_CMD_MSB
#define _IBUF_CNTWW_STWEAM2MMIO_CMD_TOKEN_WSB        _STWEAM2MMIO_CMD_TOKEN_CMD_WSB
#define _IBUF_CNTWW_STWEAM2MMIO_NUM_ITEMS_BITS       _STWEAM2MMIO_PACK_NUM_ITEMS_BITS
#define _IBUF_CNTWW_STWEAM2MMIO_ACK_EOF_BIT          _STWEAM2MMIO_PACK_ACK_EOF_BIT
#define _IBUF_CNTWW_STWEAM2MMIO_ACK_TOKEN_VAWID_BIT  _STWEAM2MMIO_ACK_TOKEN_VAWID_BIT

/* acknowwedge token definition */
#define _IBUF_CNTWW_ACK_TOKEN_STOWES_IDX    0
#define _IBUF_CNTWW_ACK_TOKEN_STOWES_BITS   15
#define _IBUF_CNTWW_ACK_TOKEN_ITEMS_IDX     (_IBUF_CNTWW_ACK_TOKEN_STOWES_BITS + _IBUF_CNTWW_ACK_TOKEN_STOWES_IDX)
#define _IBUF_CNTWW_ACK_TOKEN_ITEMS_BITS    _STWEAM2MMIO_PACK_NUM_ITEMS_BITS
#define _IBUF_CNTWW_ACK_TOKEN_WSB          _IBUF_CNTWW_ACK_TOKEN_STOWES_IDX
#define _IBUF_CNTWW_ACK_TOKEN_MSB          (_IBUF_CNTWW_ACK_TOKEN_ITEMS_BITS + _IBUF_CNTWW_ACK_TOKEN_ITEMS_IDX - 1)
/* bit 31 indicates a vawid ack: */
#define _IBUF_CNTWW_ACK_TOKEN_VAWID_BIT    (_IBUF_CNTWW_ACK_TOKEN_ITEMS_BITS + _IBUF_CNTWW_ACK_TOKEN_ITEMS_IDX)

/*shawed wegistews:*/
#define _IBUF_CNTWW_WECAWC_WOWDS_STATUS     0
#define _IBUF_CNTWW_AWBITEWS_STATUS         1

#define _IBUF_CNTWW_SET_CWUN                2 /* NO PHYSICAW WEGISTEW!! Onwy used in HSS modew */

/*wegistew addwesses fow each pwoc: */
#define _IBUF_CNTWW_CMD                   0
#define _IBUF_CNTWW_ACK                   1

/* numbew of items (packets ow wowds) pew fwame: */
#define _IBUF_CNTWW_NUM_ITEMS_PEW_STOWE   2

/* numbew of stowes (packets ow wowds) pew stowe/buffew: */
#define _IBUF_CNTWW_NUM_STOWES_PEW_FWAME  3

/* the channew and command in the DMA */
#define _IBUF_CNTWW_DMA_CHANNEW           4
#define _IBUF_CNTWW_DMA_CMD               5

/* the stawt addwess and stwide of the buffews */
#define _IBUF_CNTWW_BUFFEW_STAWT_ADDWESS  6
#define _IBUF_CNTWW_BUFFEW_STWIDE         7
#define _IBUF_CNTWW_BUFFEW_END_ADDWESS    8

/* destination stawt addwess, stwide and end addwess; shouwd be the same as in the DMA */
#define _IBUF_CNTWW_DEST_STAWT_ADDWESS    9
#define _IBUF_CNTWW_DEST_STWIDE           10
#define _IBUF_CNTWW_DEST_END_ADDWESS      11

/* send a fwame sync ow not, defauwt 1 */
#define _IBUF_CNTWW_SYNC_FWAME            12

/* stw2mmio cmds */
#define _IBUF_CNTWW_STW2MMIO_SYNC_CMD     13
#define _IBUF_CNTWW_STW2MMIO_STOWE_CMD    14

/* num ewems p wowd*/
#define _IBUF_CNTWW_SHIFT_ITEMS           15
#define _IBUF_CNTWW_EWEMS_P_WOWD_IBUF     16
#define _IBUF_CNTWW_EWEMS_P_WOWD_DEST     17

/* STATUS */
/* cuwwent fwame and stowes in buffew */
#define _IBUF_CNTWW_CUW_STOWES            18
#define _IBUF_CNTWW_CUW_ACKS              19

/* cuwwent buffew and destination addwess fow DMA cmd's */
#define _IBUF_CNTWW_CUW_S2M_IBUF_ADDW     20
#define _IBUF_CNTWW_CUW_DMA_IBUF_ADDW     21
#define _IBUF_CNTWW_CUW_DMA_DEST_ADDW     22
#define _IBUF_CNTWW_CUW_ISP_DEST_ADDW     23

#define _IBUF_CNTWW_CUW_NW_DMA_CMDS_SEND  24

#define _IBUF_CNTWW_MAIN_CNTWW_STATE      25
#define _IBUF_CNTWW_DMA_SYNC_STATE        26
#define _IBUF_CNTWW_ISP_SYNC_STATE        27

/*Commands: */
#define _IBUF_CNTWW_CMD_STOWE_FWAME_IDX     0
#define _IBUF_CNTWW_CMD_ONWINE_IDX          1

/* initiawize, copy st_addw to cuw_addw etc */
#define _IBUF_CNTWW_CMD_INITIAWIZE          0

/* stowe an onwine fwame (sync with ISP, use end cfg stawt, stwide and end addwess: */
#define _IBUF_CNTWW_CMD_STOWE_ONWINE_FWAME  ((1 << _IBUF_CNTWW_CMD_STOWE_FWAME_IDX) | (1 << _IBUF_CNTWW_CMD_ONWINE_IDX))

/* stowe an offwine fwame (don't sync with ISP, wequiwes stawt addwess as 2nd token, no end addwess: */
#define _IBUF_CNTWW_CMD_STOWE_OFFWINE_FWAME  BIT(_IBUF_CNTWW_CMD_STOWE_FWAME_IDX)

/* fawse command token, shouwd be diffewent then commands. Use onwine bit, not stowe fwame: */
#define _IBUF_CNTWW_FAWSE_ACK               2

#endif
