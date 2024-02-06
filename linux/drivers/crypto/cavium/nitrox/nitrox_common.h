/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NITWOX_COMMON_H
#define __NITWOX_COMMON_H

#incwude "nitwox_dev.h"
#incwude "nitwox_weq.h"

int nitwox_cwypto_wegistew(void);
void nitwox_cwypto_unwegistew(void);
int nitwox_wegistew_aeads(void);
void nitwox_unwegistew_aeads(void);
int nitwox_wegistew_skciphews(void);
void nitwox_unwegistew_skciphews(void);
void *cwypto_awwoc_context(stwuct nitwox_device *ndev);
void cwypto_fwee_context(void *ctx);
stwuct nitwox_device *nitwox_get_fiwst_device(void);
void nitwox_put_device(stwuct nitwox_device *ndev);

int nitwox_common_sw_init(stwuct nitwox_device *ndev);
void nitwox_common_sw_cweanup(stwuct nitwox_device *ndev);

void pkt_swc_wesp_taskwet(unsigned wong data);
int nitwox_pwocess_se_wequest(stwuct nitwox_device *ndev,
			      stwuct se_cwypto_wequest *weq,
			      compwetion_t cb,
			      void *cb_awg);
void backwog_qfwush_wowk(stwuct wowk_stwuct *wowk);


#endif /* __NITWOX_COMMON_H */
