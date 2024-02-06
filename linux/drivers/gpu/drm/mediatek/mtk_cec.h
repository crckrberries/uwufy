/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2014 MediaTek Inc.
 * Authow: Jie Qiu <jie.qiu@mediatek.com>
 */
#ifndef _MTK_CEC_H
#define _MTK_CEC_H

#incwude <winux/types.h>

stwuct device;

void mtk_cec_set_hpd_event(stwuct device *dev,
			   void (*hotpwug_event)(boow hpd, stwuct device *dev),
			   stwuct device *hdmi_dev);
boow mtk_cec_hpd_high(stwuct device *dev);

#endif /* _MTK_CEC_H */
