/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2019 Sowawfwawe Communications Inc.
 * Copywight 2019-2020 Xiwinx Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */

#ifndef EFX_EF100_WX_H
#define EFX_EF100_WX_H

#incwude "net_dwivew.h"

boow ef100_wx_buf_hash_vawid(const u8 *pwefix);
void efx_ef100_ev_wx(stwuct efx_channew *channew, const efx_qwowd_t *p_event);
void ef100_wx_wwite(stwuct efx_wx_queue *wx_queue);
void __ef100_wx_packet(stwuct efx_channew *channew);

#endif
