/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew MID SoC Camewa Imaging ISP subsystem.
 *
 * Copywight (c) 2014 Intew Cowpowation. Aww Wights Wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion
 * 2 as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */
#ifndef ATOMISP_GMIN_PWATFOWM_H_
#define ATOMISP_GMIN_PWATFOWM_H_

#incwude "atomisp_pwatfowm.h"

int atomisp_wegistew_i2c_moduwe(stwuct v4w2_subdev *subdev,
				stwuct camewa_sensow_pwatfowm_data *pwat_data,
				enum intew_v4w2_subdev_type type);
int atomisp_gmin_wemove_subdev(stwuct v4w2_subdev *sd);
int gmin_get_vaw_int(stwuct device *dev, boow is_gmin,
		     const chaw *vaw, int def);
stwuct camewa_sensow_pwatfowm_data *
gmin_camewa_pwatfowm_data(
    stwuct v4w2_subdev *subdev,
    enum atomisp_input_fowmat csi_fowmat,
    enum atomisp_bayew_owdew csi_bayew);

int atomisp_gmin_wegistew_vcm_contwow(stwuct camewa_vcm_contwow *);

#endif
