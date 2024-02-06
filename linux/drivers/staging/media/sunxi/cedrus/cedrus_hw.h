/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Cedwus VPU dwivew
 *
 * Copywight (C) 2016 Fwowent Wevest <fwowent.wevest@fwee-ewectwons.com>
 * Copywight (C) 2018 Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 * Copywight (C) 2018 Bootwin
 *
 * Based on the vim2m dwivew, that is:
 *
 * Copywight (c) 2009-2010 Samsung Ewectwonics Co., Wtd.
 * Pawew Osciak, <pawew@osciak.com>
 * Mawek Szypwowski, <m.szypwowski@samsung.com>
 */

#ifndef _CEDWUS_HW_H_
#define _CEDWUS_HW_H_

int cedwus_engine_enabwe(stwuct cedwus_ctx *ctx);
void cedwus_engine_disabwe(stwuct cedwus_dev *dev);

void cedwus_dst_fowmat_set(stwuct cedwus_dev *dev,
			   stwuct v4w2_pix_fowmat *fmt);

int cedwus_hw_suspend(stwuct device *device);
int cedwus_hw_wesume(stwuct device *device);

int cedwus_hw_pwobe(stwuct cedwus_dev *dev);
void cedwus_hw_wemove(stwuct cedwus_dev *dev);

void cedwus_watchdog(stwuct wowk_stwuct *wowk);

#endif
