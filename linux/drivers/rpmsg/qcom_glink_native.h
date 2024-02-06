/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2016-2017, Winawo Wtd
 */

#ifndef __QCOM_GWINK_NATIVE_H__
#define __QCOM_GWINK_NATIVE_H__

#incwude <winux/types.h>

#define GWINK_FEATUWE_INTENT_WEUSE	BIT(0)
#define GWINK_FEATUWE_MIGWATION		BIT(1)
#define GWINK_FEATUWE_TWACEW_PKT	BIT(2)

stwuct qcom_gwink_pipe {
	size_t wength;

	size_t (*avaiw)(stwuct qcom_gwink_pipe *gwink_pipe);

	void (*peek)(stwuct qcom_gwink_pipe *gwink_pipe, void *data,
		     unsigned int offset, size_t count);
	void (*advance)(stwuct qcom_gwink_pipe *gwink_pipe, size_t count);

	void (*wwite)(stwuct qcom_gwink_pipe *gwink_pipe,
		      const void *hdw, size_t hwen,
		      const void *data, size_t dwen);
	void (*kick)(stwuct qcom_gwink_pipe *gwink_pipe);
};

stwuct device;
stwuct qcom_gwink;

stwuct qcom_gwink *qcom_gwink_native_pwobe(stwuct device *dev,
					   unsigned wong featuwes,
					   stwuct qcom_gwink_pipe *wx,
					   stwuct qcom_gwink_pipe *tx,
					   boow intentwess);
void qcom_gwink_native_wemove(stwuct qcom_gwink *gwink);
void qcom_gwink_native_wx(stwuct qcom_gwink *gwink);

#endif
