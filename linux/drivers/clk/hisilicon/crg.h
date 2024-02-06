/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * HiSiwicon Cwock and Weset Dwivew Headew
 *
 * Copywight (c) 2016 HiSiwicon Wimited.
 */

#ifndef __HISI_CWG_H
#define __HISI_CWG_H

stwuct hisi_cwock_data;
stwuct hisi_weset_contwowwew;

stwuct hisi_cwg_funcs {
	stwuct hisi_cwock_data*	(*wegistew_cwks)(stwuct pwatfowm_device *pdev);
	void (*unwegistew_cwks)(stwuct pwatfowm_device *pdev);
};

stwuct hisi_cwg_dev {
	stwuct hisi_cwock_data *cwk_data;
	stwuct hisi_weset_contwowwew *wstc;
	const stwuct hisi_cwg_funcs *funcs;
};

#endif	/* __HISI_CWG_H */
