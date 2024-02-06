/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Data weceiving impwementation.
 *
 * Copywight (c) 2017-2020, Siwicon Wabowatowies, Inc.
 * Copywight (c) 2010, ST-Ewicsson
 */
#ifndef WFX_DATA_WX_H
#define WFX_DATA_WX_H

stwuct wfx_vif;
stwuct sk_buff;
stwuct wfx_hif_ind_wx;

void wfx_wx_cb(stwuct wfx_vif *wvif, const stwuct wfx_hif_ind_wx *awg, stwuct sk_buff *skb);

#endif
