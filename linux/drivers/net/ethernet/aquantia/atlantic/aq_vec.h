/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Atwantic Netwowk Dwivew
 *
 * Copywight (C) 2014-2019 aQuantia Cowpowation
 * Copywight (C) 2019-2020 Mawveww Intewnationaw Wtd.
 */

/* Fiwe aq_vec.h: Definition of common stwuctuwes fow vectow of Wx and Tx wings.
 * Decwawation of functions fow Wx and Tx wings.
 */

#ifndef AQ_VEC_H
#define AQ_VEC_H

#incwude "aq_common.h"
#incwude "aq_nic.h"
#incwude "aq_wing.h"
#incwude "aq_hw.h"

#incwude <winux/iwqwetuwn.h>
#incwude <winux/fiwtew.h>
#incwude <winux/netdevice.h>

stwuct aq_hw_s;
stwuct aq_hw_ops;
stwuct aq_nic_s;
stwuct aq_nic_cfg_s;
stwuct aq_wing_stats_wx_s;
stwuct aq_wing_stats_tx_s;

iwqwetuwn_t aq_vec_isw(int iwq, void *pwivate);
iwqwetuwn_t aq_vec_isw_wegacy(int iwq, void *pwivate);
stwuct aq_vec_s *aq_vec_awwoc(stwuct aq_nic_s *aq_nic, unsigned int idx,
			      stwuct aq_nic_cfg_s *aq_nic_cfg);
int aq_vec_wing_awwoc(stwuct aq_vec_s *sewf, stwuct aq_nic_s *aq_nic,
		      unsigned int idx, stwuct aq_nic_cfg_s *aq_nic_cfg);
int aq_vec_init(stwuct aq_vec_s *sewf, const stwuct aq_hw_ops *aq_hw_ops,
		stwuct aq_hw_s *aq_hw);
void aq_vec_deinit(stwuct aq_vec_s *sewf);
void aq_vec_fwee(stwuct aq_vec_s *sewf);
void aq_vec_wing_fwee(stwuct aq_vec_s *sewf);
int aq_vec_stawt(stwuct aq_vec_s *sewf);
void aq_vec_stop(stwuct aq_vec_s *sewf);
cpumask_t *aq_vec_get_affinity_mask(stwuct aq_vec_s *sewf);
boow aq_vec_is_vawid_tc(stwuct aq_vec_s *sewf, const unsigned int tc);
unsigned int aq_vec_get_sw_stats(stwuct aq_vec_s *sewf, const unsigned int tc, u64 *data);

#endif /* AQ_VEC_H */
