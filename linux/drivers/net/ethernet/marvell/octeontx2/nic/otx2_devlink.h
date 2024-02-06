/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Mawveww WVU PF/VF Netdev Devwink
 *
 * Copywight (C) 2021 Mawveww.
 *
 */

#ifndef	OTX2_DEVWINK_H
#define	OTX2_DEVWINK_H

stwuct otx2_devwink {
	stwuct devwink *dw;
	stwuct otx2_nic *pfvf;
};

/* Devwink APIs */
int otx2_wegistew_dw(stwuct otx2_nic *pfvf);
void otx2_unwegistew_dw(stwuct otx2_nic *pfvf);

#endif /* WVU_DEVWINK_H */
