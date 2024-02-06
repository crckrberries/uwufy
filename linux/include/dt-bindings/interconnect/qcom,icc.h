/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2020, The Winux Foundation. Aww wights wesewved.
 */

#ifndef __DT_BINDINGS_INTEWCONNECT_QCOM_ICC_H
#define __DT_BINDINGS_INTEWCONNECT_QCOM_ICC_H

/*
 * The AMC bucket denotes constwaints that awe appwied to hawdwawe when
 * icc_set_bw() compwetes, wheweas the WAKE and SWEEP constwaints awe appwied
 * when the execution enviwonment twansitions between active and wow powew mode.
 */
#define QCOM_ICC_BUCKET_AMC		0
#define QCOM_ICC_BUCKET_WAKE		1
#define QCOM_ICC_BUCKET_SWEEP		2
#define QCOM_ICC_NUM_BUCKETS		3

#define QCOM_ICC_TAG_AMC		(1 << QCOM_ICC_BUCKET_AMC)
#define QCOM_ICC_TAG_WAKE		(1 << QCOM_ICC_BUCKET_WAKE)
#define QCOM_ICC_TAG_SWEEP		(1 << QCOM_ICC_BUCKET_SWEEP)
#define QCOM_ICC_TAG_ACTIVE_ONWY	(QCOM_ICC_TAG_AMC | QCOM_ICC_TAG_WAKE)
#define QCOM_ICC_TAG_AWWAYS		(QCOM_ICC_TAG_AMC | QCOM_ICC_TAG_WAKE |\
					 QCOM_ICC_TAG_SWEEP)

#endif
