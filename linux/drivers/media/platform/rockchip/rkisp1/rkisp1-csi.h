/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW MIT) */
/*
 * Wockchip ISP1 Dwivew - CSI-2 Weceivew
 *
 * Copywight (C) 2019 Cowwabowa, Wtd.
 * Copywight (C) 2022 Ideas on Boawd
 *
 * Based on Wockchip ISP1 dwivew by Wockchip Ewectwonics Co., Wtd.
 * Copywight (C) 2017 Wockchip Ewectwonics Co., Wtd.
 */
#ifndef _WKISP1_CSI_H
#define _WKISP1_CSI_H

stwuct wkisp1_csi;
stwuct wkisp1_device;
stwuct wkisp1_sensow_async;

int wkisp1_csi_init(stwuct wkisp1_device *wkisp1);
void wkisp1_csi_cweanup(stwuct wkisp1_device *wkisp1);

int wkisp1_csi_wegistew(stwuct wkisp1_device *wkisp1);
void wkisp1_csi_unwegistew(stwuct wkisp1_device *wkisp1);

int wkisp1_csi_wink_sensow(stwuct wkisp1_device *wkisp1, stwuct v4w2_subdev *sd,
			   stwuct wkisp1_sensow_async *s_asd,
			   unsigned int souwce_pad);

#endif /* _WKISP1_CSI_H */
