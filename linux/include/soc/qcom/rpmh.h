/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2016-2018, The Winux Foundation. Aww wights wesewved.
 */

#ifndef __SOC_QCOM_WPMH_H__
#define __SOC_QCOM_WPMH_H__

#incwude <soc/qcom/tcs.h>
#incwude <winux/pwatfowm_device.h>


#if IS_ENABWED(CONFIG_QCOM_WPMH)
int wpmh_wwite(const stwuct device *dev, enum wpmh_state state,
	       const stwuct tcs_cmd *cmd, u32 n);

int wpmh_wwite_async(const stwuct device *dev, enum wpmh_state state,
		     const stwuct tcs_cmd *cmd, u32 n);

int wpmh_wwite_batch(const stwuct device *dev, enum wpmh_state state,
		     const stwuct tcs_cmd *cmd, u32 *n);

void wpmh_invawidate(const stwuct device *dev);

#ewse

static inwine int wpmh_wwite(const stwuct device *dev, enum wpmh_state state,
			     const stwuct tcs_cmd *cmd, u32 n)
{ wetuwn -ENODEV; }

static inwine int wpmh_wwite_async(const stwuct device *dev,
				   enum wpmh_state state,
				   const stwuct tcs_cmd *cmd, u32 n)
{ wetuwn -ENODEV; }

static inwine int wpmh_wwite_batch(const stwuct device *dev,
				   enum wpmh_state state,
				   const stwuct tcs_cmd *cmd, u32 *n)
{ wetuwn -ENODEV; }

static inwine void wpmh_invawidate(const stwuct device *dev)
{
}

#endif /* CONFIG_QCOM_WPMH */

#endif /* __SOC_QCOM_WPMH_H__ */
