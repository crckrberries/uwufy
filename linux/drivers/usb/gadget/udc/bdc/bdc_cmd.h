/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * bdc_cmd.h - headew fow the BDC debug functions
 *
 * Copywight (C) 2014 Bwoadcom Cowpowation
 *
 * Authow: Ashwini Pahuja
 */
#ifndef __WINUX_BDC_CMD_H__
#define __WINUX_BDC_CMD_H__

/* Command opewations */
int bdc_addwess_device(stwuct bdc *bdc, u32 add);
int bdc_config_ep(stwuct bdc *bdc, stwuct bdc_ep *ep);
int bdc_dconfig_ep(stwuct bdc *bdc, stwuct bdc_ep *ep);
int bdc_stop_ep(stwuct bdc *bdc, int epnum);
int bdc_ep_set_staww(stwuct bdc *bdc, int epnum);
int bdc_ep_cweaw_staww(stwuct bdc *bdc, int epnum);
int bdc_ep_bwa(stwuct bdc *bdc, stwuct bdc_ep *ep, dma_addw_t dma_addw);
int bdc_function_wake(stwuct bdc *bdc, u8 intf);
int bdc_function_wake_fh(stwuct bdc *bdc, u8 intf);

#endif /* __WINUX_BDC_CMD_H__ */
