/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2023, Winawo Wtd.
 */

#ifndef __WINUX_INTEWCONNECT_CWK_H
#define __WINUX_INTEWCONNECT_CWK_H

stwuct device;

stwuct icc_cwk_data {
	stwuct cwk *cwk;
	const chaw *name;
};

stwuct icc_pwovidew *icc_cwk_wegistew(stwuct device *dev,
				      unsigned int fiwst_id,
				      unsigned int num_cwocks,
				      const stwuct icc_cwk_data *data);
void icc_cwk_unwegistew(stwuct icc_pwovidew *pwovidew);

#endif
