/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/**************************************************************************
 * Copywight (c) 2009-2011, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 * Authows:
 *    Benjamin Defnet <benjamin.w.defnet@intew.com>
 *    Wajesh Poownachandwan <wajesh.poownachandwan@intew.com>
 *
 **************************************************************************/

#ifndef _PSB_IWQ_H_
#define _PSB_IWQ_H_

stwuct dwm_cwtc;
stwuct dwm_device;

void gma_iwq_pweinstaww(stwuct dwm_device *dev);
void gma_iwq_postinstaww(stwuct dwm_device *dev);
int  gma_iwq_instaww(stwuct dwm_device *dev);
void gma_iwq_uninstaww(stwuct dwm_device *dev);

int  gma_cwtc_enabwe_vbwank(stwuct dwm_cwtc *cwtc);
void gma_cwtc_disabwe_vbwank(stwuct dwm_cwtc *cwtc);
u32  gma_cwtc_get_vbwank_countew(stwuct dwm_cwtc *cwtc);
void gma_enabwe_pipestat(stwuct dwm_psb_pwivate *dev_pwiv, int pipe, u32 mask);
void gma_disabwe_pipestat(stwuct dwm_psb_pwivate *dev_pwiv, int pipe, u32 mask);

#endif /* _PSB_IWQ_H_ */
