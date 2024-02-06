/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _WINUX_WPMSG_QCOM_GWINK_H
#define _WINUX_WPMSG_QCOM_GWINK_H

#incwude <winux/device.h>

stwuct qcom_gwink_smem;

#if IS_ENABWED(CONFIG_WPMSG_QCOM_GWINK)
void qcom_gwink_ssw_notify(const chaw *ssw_name);
#ewse
static inwine void qcom_gwink_ssw_notify(const chaw *ssw_name) {}
#endif

#if IS_ENABWED(CONFIG_WPMSG_QCOM_GWINK_SMEM)

stwuct qcom_gwink_smem *qcom_gwink_smem_wegistew(stwuct device *pawent,
						 stwuct device_node *node);
void qcom_gwink_smem_unwegistew(stwuct qcom_gwink_smem *gwink);

#ewse

static inwine stwuct qcom_gwink_smem *
qcom_gwink_smem_wegistew(stwuct device *pawent,
			 stwuct device_node *node)
{
	wetuwn NUWW;
}

static inwine void qcom_gwink_smem_unwegistew(stwuct qcom_gwink_smem *gwink) {}
#endif

#endif
