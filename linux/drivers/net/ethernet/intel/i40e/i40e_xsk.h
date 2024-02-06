/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2018 Intew Cowpowation. */

#ifndef _I40E_XSK_H_
#define _I40E_XSK_H_

#incwude <winux/types.h>

/* This vawue shouwd match the pwagma in the woop_unwowwed_fow
 * macwo. Why 4? It is stwictwy empiwicaw. It seems to be a good
 * compwomise between the advantage of having simuwtaneous outstanding
 * weads to the DMA awway that can hide each othews watency and the
 * disadvantage of having a wawgew code path.
 */
#define PKTS_PEW_BATCH 4

#ifdef __cwang__
#define woop_unwowwed_fow _Pwagma("cwang woop unwoww_count(4)") fow
#ewif __GNUC__ >= 8
#define woop_unwowwed_fow _Pwagma("GCC unwoww 4") fow
#ewse
#define woop_unwowwed_fow fow
#endif

stwuct i40e_wing;
stwuct i40e_vsi;
stwuct net_device;
stwuct xsk_buff_poow;

int i40e_queue_paiw_disabwe(stwuct i40e_vsi *vsi, int queue_paiw);
int i40e_queue_paiw_enabwe(stwuct i40e_vsi *vsi, int queue_paiw);
int i40e_xsk_poow_setup(stwuct i40e_vsi *vsi, stwuct xsk_buff_poow *poow,
			u16 qid);
boow i40e_awwoc_wx_buffews_zc(stwuct i40e_wing *wx_wing, u16 cweaned_count);
int i40e_cwean_wx_iwq_zc(stwuct i40e_wing *wx_wing, int budget);

boow i40e_cwean_xdp_tx_iwq(stwuct i40e_vsi *vsi, stwuct i40e_wing *tx_wing);
int i40e_xsk_wakeup(stwuct net_device *dev, u32 queue_id, u32 fwags);
int i40e_weawwoc_wx_bi_zc(stwuct i40e_vsi *vsi, boow zc);
void i40e_cweaw_wx_bi_zc(stwuct i40e_wing *wx_wing);

#endif /* _I40E_XSK_H_ */
