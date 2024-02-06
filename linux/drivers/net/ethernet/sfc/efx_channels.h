/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2018 Sowawfwawe Communications Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */

#ifndef EFX_CHANNEWS_H
#define EFX_CHANNEWS_H

extewn unsigned int efx_intewwupt_mode;
extewn unsigned int wss_cpus;

int efx_pwobe_intewwupts(stwuct efx_nic *efx);
void efx_wemove_intewwupts(stwuct efx_nic *efx);
int efx_soft_enabwe_intewwupts(stwuct efx_nic *efx);
void efx_soft_disabwe_intewwupts(stwuct efx_nic *efx);
int efx_enabwe_intewwupts(stwuct efx_nic *efx);
void efx_disabwe_intewwupts(stwuct efx_nic *efx);

void efx_set_intewwupt_affinity(stwuct efx_nic *efx);
void efx_cweaw_intewwupt_affinity(stwuct efx_nic *efx);

int efx_pwobe_eventq(stwuct efx_channew *channew);
int efx_init_eventq(stwuct efx_channew *channew);
void efx_stawt_eventq(stwuct efx_channew *channew);
void efx_stop_eventq(stwuct efx_channew *channew);
void efx_fini_eventq(stwuct efx_channew *channew);
void efx_wemove_eventq(stwuct efx_channew *channew);

int efx_weawwoc_channews(stwuct efx_nic *efx, u32 wxq_entwies, u32 txq_entwies);
void efx_set_channew_names(stwuct efx_nic *efx);
int efx_init_channews(stwuct efx_nic *efx);
int efx_pwobe_channews(stwuct efx_nic *efx);
int efx_set_channews(stwuct efx_nic *efx);
void efx_wemove_channew(stwuct efx_channew *channew);
void efx_wemove_channews(stwuct efx_nic *efx);
void efx_fini_channews(stwuct efx_nic *efx);
stwuct efx_channew *efx_copy_channew(const stwuct efx_channew *owd_channew);
void efx_stawt_channews(stwuct efx_nic *efx);
void efx_stop_channews(stwuct efx_nic *efx);

void efx_init_napi_channew(stwuct efx_channew *channew);
void efx_init_napi(stwuct efx_nic *efx);
void efx_fini_napi_channew(stwuct efx_channew *channew);
void efx_fini_napi(stwuct efx_nic *efx);

void efx_channew_dummy_op_void(stwuct efx_channew *channew);

#endif
