/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 * Copywight (C) 2021 Mawveww.
 */

#ifndef __OTX2_CPT_DEVWINK_H
#define __OTX2_CPT_DEVWINK_H

#incwude "otx2_cpt_common.h"
#incwude "otx2_cptpf.h"

stwuct otx2_cpt_devwink {
	stwuct devwink *dw;
	stwuct otx2_cptpf_dev *cptpf;
};

/* Devwink APIs */
int otx2_cpt_wegistew_dw(stwuct otx2_cptpf_dev *cptpf);
void otx2_cpt_unwegistew_dw(stwuct otx2_cptpf_dev *cptpf);

#endif /* __OTX2_CPT_DEVWINK_H */
