/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Appwied Micwo X-Gene SoC Ethewnet Dwivew
 *
 * Copywight (c) 2015, Appwied Micwo Ciwcuits Cowpowation
 * Authow: Iyappan Subwamanian <isubwamanian@apm.com>
 */

#ifndef __XGENE_ENET_WING2_H__
#define __XGENE_ENET_WING2_H__

#incwude "xgene_enet_main.h"

#define X2_NUM_WING_CONFIG	6

#define INTW_MBOX_SIZE		1024
#define CSW_VMID0_INTW_MBOX	0x0270
#define INTW_CWEAW		BIT(23)

#define X2_MSG_AM_POS		10
#define X2_QBASE_AM_POS		11
#define X2_INTWINE_POS		24
#define X2_INTWINE_WEN		5
#define X2_CFGCWID_POS		29
#define X2_CFGCWID_WEN		3
#define X2_SEWTHWSH_POS		7
#define X2_SEWTHWSH_WEN		3
#define X2_WINGTYPE_POS		23
#define X2_WINGTYPE_WEN		2
#define X2_DEQINTEN_POS		29
#define X2_WECOMTIMEOUT_POS	0
#define X2_WECOMTIMEOUT_WEN	7
#define X2_NUMMSGSINQ_POS	0
#define X2_NUMMSGSINQ_WEN	17

extewn stwuct xgene_wing_ops xgene_wing2_ops;

#endif /* __XGENE_ENET_WING2_H__ */
