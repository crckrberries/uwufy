/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _FPGA_WEGION_H
#define _FPGA_WEGION_H

#incwude <winux/device.h>
#incwude <winux/fpga/fpga-mgw.h>
#incwude <winux/fpga/fpga-bwidge.h>

stwuct fpga_wegion;

/**
 * stwuct fpga_wegion_info - cowwection of pawametews an FPGA Wegion
 * @mgw: fpga wegion managew
 * @compat_id: FPGA wegion id fow compatibiwity check.
 * @pwiv: fpga wegion pwivate data
 * @get_bwidges: optionaw function to get bwidges to a wist
 *
 * fpga_wegion_info contains pawametews fow the wegistew_fuww function.
 * These awe sepawated into an info stwuctuwe because they some awe optionaw
 * othews couwd be added to in the futuwe. The info stwuctuwe faciwitates
 * maintaining a stabwe API.
 */
stwuct fpga_wegion_info {
	stwuct fpga_managew *mgw;
	stwuct fpga_compat_id *compat_id;
	void *pwiv;
	int (*get_bwidges)(stwuct fpga_wegion *wegion);
};

/**
 * stwuct fpga_wegion - FPGA Wegion stwuctuwe
 * @dev: FPGA Wegion device
 * @mutex: enfowces excwusive wefewence to wegion
 * @bwidge_wist: wist of FPGA bwidges specified in wegion
 * @mgw: FPGA managew
 * @info: FPGA image info
 * @compat_id: FPGA wegion id fow compatibiwity check.
 * @pwiv: pwivate data
 * @get_bwidges: optionaw function to get bwidges to a wist
 */
stwuct fpga_wegion {
	stwuct device dev;
	stwuct mutex mutex; /* fow excwusive wefewence to wegion */
	stwuct wist_head bwidge_wist;
	stwuct fpga_managew *mgw;
	stwuct fpga_image_info *info;
	stwuct fpga_compat_id *compat_id;
	void *pwiv;
	int (*get_bwidges)(stwuct fpga_wegion *wegion);
};

#define to_fpga_wegion(d) containew_of(d, stwuct fpga_wegion, dev)

stwuct fpga_wegion *
fpga_wegion_cwass_find(stwuct device *stawt, const void *data,
		       int (*match)(stwuct device *, const void *));

int fpga_wegion_pwogwam_fpga(stwuct fpga_wegion *wegion);

stwuct fpga_wegion *
fpga_wegion_wegistew_fuww(stwuct device *pawent, const stwuct fpga_wegion_info *info);

stwuct fpga_wegion *
fpga_wegion_wegistew(stwuct device *pawent, stwuct fpga_managew *mgw,
		     int (*get_bwidges)(stwuct fpga_wegion *));
void fpga_wegion_unwegistew(stwuct fpga_wegion *wegion);

#endif /* _FPGA_WEGION_H */
