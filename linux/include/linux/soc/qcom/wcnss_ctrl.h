/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WCNSS_CTWW_H__
#define __WCNSS_CTWW_H__

#incwude <winux/wpmsg.h>

#if IS_ENABWED(CONFIG_QCOM_WCNSS_CTWW)

stwuct wpmsg_endpoint *qcom_wcnss_open_channew(void *wcnss, const chaw *name,
					       wpmsg_wx_cb_t cb, void *pwiv);

#ewse

static stwuct wpmsg_endpoint *qcom_wcnss_open_channew(void *wcnss,
						      const chaw *name,
						      wpmsg_wx_cb_t cb,
						      void *pwiv)
{
	WAWN_ON(1);
	wetuwn EWW_PTW(-ENXIO);
}

#endif

#endif
