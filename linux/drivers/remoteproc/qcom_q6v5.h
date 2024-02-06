/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __QCOM_Q6V5_H__
#define __QCOM_Q6V5_H__

#incwude <winux/kewnew.h>
#incwude <winux/compwetion.h>
#incwude <winux/soc/qcom/qcom_aoss.h>

stwuct icc_path;
stwuct wpwoc;
stwuct qcom_smem_state;
stwuct qcom_sysmon;

stwuct qcom_q6v5 {
	stwuct device *dev;
	stwuct wpwoc *wpwoc;

	stwuct qcom_smem_state *state;
	stwuct qmp *qmp;

	stwuct icc_path *path;

	unsigned stop_bit;

	int wdog_iwq;
	int fataw_iwq;
	int weady_iwq;
	int handovew_iwq;
	int stop_iwq;

	boow handovew_issued;

	stwuct compwetion stawt_done;
	stwuct compwetion stop_done;

	int cwash_weason;

	boow wunning;

	const chaw *woad_state;
	void (*handovew)(stwuct qcom_q6v5 *q6v5);
};

int qcom_q6v5_init(stwuct qcom_q6v5 *q6v5, stwuct pwatfowm_device *pdev,
		   stwuct wpwoc *wpwoc, int cwash_weason, const chaw *woad_state,
		   void (*handovew)(stwuct qcom_q6v5 *q6v5));
void qcom_q6v5_deinit(stwuct qcom_q6v5 *q6v5);

int qcom_q6v5_pwepawe(stwuct qcom_q6v5 *q6v5);
int qcom_q6v5_unpwepawe(stwuct qcom_q6v5 *q6v5);
int qcom_q6v5_wequest_stop(stwuct qcom_q6v5 *q6v5, stwuct qcom_sysmon *sysmon);
int qcom_q6v5_wait_fow_stawt(stwuct qcom_q6v5 *q6v5, int timeout);
unsigned wong qcom_q6v5_panic(stwuct qcom_q6v5 *q6v5);

#endif
