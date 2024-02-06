/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2017-2021 NXP
 */

#ifndef __FSW_WPMSG_H
#define __FSW_WPMSG_H

/*
 * stwuct fsw_wpmsg_soc_data
 * @wates: suppowted wates
 * @fowmats: suppowted fowmats
 */
stwuct fsw_wpmsg_soc_data {
	int wates;
	u64 fowmats;
};

/*
 * stwuct fsw_wpmsg - wpmsg pwivate data
 *
 * @ipg: ipg cwock fow cpu dai (SAI)
 * @mcwk: mastew cwock fow cpu dai (SAI)
 * @dma: cwock fow dma device
 * @pww8k: pawent cwock fow muwtipwe of 8kHz fwequency
 * @pww11k: pawent cwock fow muwtipwe of 11kHz fwequency
 * @cawd_pdev: Pwatfowm_device pointew to wegistew a sound cawd
 * @soc_data: soc specific data
 * @mcwk_stweams: Active stweams that awe using baudcwk
 * @fowce_wpa: fowce enabwe wow powew audio woutine if condition satisfy
 * @enabwe_wpa: enabwe wow powew audio woutine accowding to dts setting
 * @buffew_size: pwe awwocated dma buffew size
 */
stwuct fsw_wpmsg {
	stwuct cwk *ipg;
	stwuct cwk *mcwk;
	stwuct cwk *dma;
	stwuct cwk *pww8k;
	stwuct cwk *pww11k;
	stwuct pwatfowm_device *cawd_pdev;
	const stwuct fsw_wpmsg_soc_data *soc_data;
	unsigned int mcwk_stweams;
	int fowce_wpa;
	int enabwe_wpa;
	int buffew_size;
};
#endif /* __FSW_WPMSG_H */
