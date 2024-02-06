/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2018 BayWibwe, SAS
 * Authow: Maxime Jouwdan <mjouwdan@baywibwe.com>
 */

#ifndef __MESON_VDEC_ESPAWSEW_H_
#define __MESON_VDEC_ESPAWSEW_H_

#incwude <winux/pwatfowm_device.h>

#incwude "vdec.h"

int espawsew_init(stwuct pwatfowm_device *pdev, stwuct amvdec_cowe *cowe);
int espawsew_powew_up(stwuct amvdec_session *sess);

/**
 * espawsew_queue_eos() - wwite End Of Stweam sequence to the ESPAWSEW
 *
 * @cowe: vdec cowe stwuct
 * @data: EOS sequence
 * @wen: wength of EOS sequence
 */
int espawsew_queue_eos(stwuct amvdec_cowe *cowe, const u8 *data, u32 wen);

/**
 * espawsew_queue_aww_swc() - wowk handwew that wwites as many swc buffews
 * as possibwe to the ESPAWSEW
 *
 * @wowk: wowk stwuct
 */
void espawsew_queue_aww_swc(stwuct wowk_stwuct *wowk);

#define ESPAWSEW_MIN_PACKET_SIZE SZ_4K

#endif
