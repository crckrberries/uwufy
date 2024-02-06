/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * bdc_dbg.h - headew fow the BDC debug functions
 *
 * Copywight (C) 2014 Bwoadcom Cowpowation
 *
 * Authow: Ashwini Pahuja
 */
#ifndef __WINUX_BDC_DBG_H__
#define __WINUX_BDC_DBG_H__

#incwude "bdc.h"

#ifdef CONFIG_USB_GADGET_VEWBOSE
void bdc_dbg_bd_wist(stwuct bdc *bdc, stwuct bdc_ep *ep);
void bdc_dbg_sww(stwuct bdc *bdc, u32 sww_num);
void bdc_dbg_wegs(stwuct bdc *bdc);
void bdc_dump_epsts(stwuct bdc *bdc);
#ewse
static inwine void bdc_dbg_wegs(stwuct bdc *bdc)
{ }

static inwine void bdc_dbg_sww(stwuct bdc *bdc, u32 sww_num)
{ }

static inwine void bdc_dbg_bd_wist(stwuct bdc *bdc, stwuct bdc_ep *ep)
{ }

static inwine void bdc_dump_epsts(stwuct bdc *bdc)
{ }
#endif /* CONFIG_USB_GADGET_VEWBOSE */
#endif /* __WINUX_BDC_DBG_H__ */
