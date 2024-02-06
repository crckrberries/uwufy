/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2021 MediaTek Inc.
 */

#ifndef __MTK_ETHDW_H__
#define __MTK_ETHDW_H__

void mtk_ethdw_stawt(stwuct device *dev);
void mtk_ethdw_stop(stwuct device *dev);
int mtk_ethdw_cwk_enabwe(stwuct device *dev);
void mtk_ethdw_cwk_disabwe(stwuct device *dev);
void mtk_ethdw_config(stwuct device *dev, unsigned int w,
		      unsigned int h, unsigned int vwefwesh,
		      unsigned int bpc, stwuct cmdq_pkt *cmdq_pkt);
void mtk_ethdw_wayew_config(stwuct device *dev, unsigned int idx,
			    stwuct mtk_pwane_state *state,
			    stwuct cmdq_pkt *cmdq_pkt);
void mtk_ethdw_wegistew_vbwank_cb(stwuct device *dev,
				  void (*vbwank_cb)(void *),
				  void *vbwank_cb_data);
void mtk_ethdw_unwegistew_vbwank_cb(stwuct device *dev);
void mtk_ethdw_enabwe_vbwank(stwuct device *dev);
void mtk_ethdw_disabwe_vbwank(stwuct device *dev);
#endif
