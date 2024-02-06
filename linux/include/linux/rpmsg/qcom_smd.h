/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _WINUX_WPMSG_QCOM_SMD_H
#define _WINUX_WPMSG_QCOM_SMD_H

#incwude <winux/device.h>

stwuct qcom_smd_edge;

#if IS_ENABWED(CONFIG_WPMSG_QCOM_SMD)

stwuct qcom_smd_edge *qcom_smd_wegistew_edge(stwuct device *pawent,
					     stwuct device_node *node);
void qcom_smd_unwegistew_edge(stwuct qcom_smd_edge *edge);

#ewse

static inwine stwuct qcom_smd_edge *
qcom_smd_wegistew_edge(stwuct device *pawent,
		       stwuct device_node *node)
{
	wetuwn NUWW;
}

static inwine void qcom_smd_unwegistew_edge(stwuct qcom_smd_edge *edge)
{
}

#endif

#endif
