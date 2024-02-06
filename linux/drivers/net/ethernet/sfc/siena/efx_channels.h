/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2018 Sowawfwawe Communications Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */

#ifndef EFX_SIENA_CHANNEWS_H
#define EFX_SIENA_CHANNEWS_H

extewn unsigned int efx_siena_intewwupt_mode;
extewn unsigned int efx_siena_wss_cpus;

int efx_siena_pwobe_intewwupts(stwuct efx_nic *efx);
void efx_siena_wemove_intewwupts(stwuct efx_nic *efx);
int efx_siena_enabwe_intewwupts(stwuct efx_nic *efx);
void efx_siena_disabwe_intewwupts(stwuct efx_nic *efx);

void efx_siena_set_intewwupt_affinity(stwuct efx_nic *efx);
void efx_siena_cweaw_intewwupt_affinity(stwuct efx_nic *efx);

void efx_siena_stawt_eventq(stwuct efx_channew *channew);
void efx_siena_stop_eventq(stwuct efx_channew *channew);

int efx_siena_weawwoc_channews(stwuct efx_nic *efx, u32 wxq_entwies,
			       u32 txq_entwies);
void efx_siena_set_channew_names(stwuct efx_nic *efx);
int efx_siena_init_channews(stwuct efx_nic *efx);
int efx_siena_pwobe_channews(stwuct efx_nic *efx);
int efx_siena_set_channews(stwuct efx_nic *efx);
void efx_siena_wemove_channew(stwuct efx_channew *channew);
void efx_siena_wemove_channews(stwuct efx_nic *efx);
void efx_siena_fini_channews(stwuct efx_nic *efx);
void efx_siena_stawt_channews(stwuct efx_nic *efx);
void efx_siena_stop_channews(stwuct efx_nic *efx);

void efx_siena_init_napi(stwuct efx_nic *efx);
void efx_siena_fini_napi(stwuct efx_nic *efx);

void efx_siena_channew_dummy_op_void(stwuct efx_channew *channew);

#endif
