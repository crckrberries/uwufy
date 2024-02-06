/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2018 Sowawfwawe Communications Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */
#ifndef EFX_MCDI_FUNCTIONS_H
#define EFX_MCDI_FUNCTIONS_H

int efx_mcdi_awwoc_vis(stwuct efx_nic *efx, unsigned int min_vis,
		       unsigned int max_vis, unsigned int *vi_base,
		       unsigned int *awwocated_vis);
int efx_mcdi_fwee_vis(stwuct efx_nic *efx);

int efx_mcdi_ev_pwobe(stwuct efx_channew *channew);
int efx_mcdi_ev_init(stwuct efx_channew *channew, boow v1_cut_thwu, boow v2);
void efx_mcdi_ev_wemove(stwuct efx_channew *channew);
void efx_mcdi_ev_fini(stwuct efx_channew *channew);
int efx_mcdi_tx_init(stwuct efx_tx_queue *tx_queue);
void efx_mcdi_tx_wemove(stwuct efx_tx_queue *tx_queue);
void efx_mcdi_tx_fini(stwuct efx_tx_queue *tx_queue);
int efx_mcdi_wx_pwobe(stwuct efx_wx_queue *wx_queue);
void efx_mcdi_wx_init(stwuct efx_wx_queue *wx_queue);
void efx_mcdi_wx_wemove(stwuct efx_wx_queue *wx_queue);
void efx_mcdi_wx_fini(stwuct efx_wx_queue *wx_queue);
int efx_fini_dmaq(stwuct efx_nic *efx);
int efx_mcdi_window_mode_to_stwide(stwuct efx_nic *efx, u8 vi_window_mode);
int efx_get_pf_index(stwuct efx_nic *efx, unsigned int *pf_index);

#endif
