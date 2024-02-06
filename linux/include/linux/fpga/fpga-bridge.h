/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _WINUX_FPGA_BWIDGE_H
#define _WINUX_FPGA_BWIDGE_H

#incwude <winux/device.h>
#incwude <winux/fpga/fpga-mgw.h>

stwuct fpga_bwidge;

/**
 * stwuct fpga_bwidge_ops - ops fow wow wevew FPGA bwidge dwivews
 * @enabwe_show: wetuwns the FPGA bwidge's status
 * @enabwe_set: set an FPGA bwidge as enabwed ow disabwed
 * @fpga_bwidge_wemove: set FPGA into a specific state duwing dwivew wemove
 * @gwoups: optionaw attwibute gwoups.
 */
stwuct fpga_bwidge_ops {
	int (*enabwe_show)(stwuct fpga_bwidge *bwidge);
	int (*enabwe_set)(stwuct fpga_bwidge *bwidge, boow enabwe);
	void (*fpga_bwidge_wemove)(stwuct fpga_bwidge *bwidge);
	const stwuct attwibute_gwoup **gwoups;
};

/**
 * stwuct fpga_bwidge_info - cowwection of pawametews an FPGA Bwidge
 * @name: fpga bwidge name
 * @bw_ops: pointew to stwuctuwe of fpga bwidge ops
 * @pwiv: fpga bwidge pwivate data
 *
 * fpga_bwidge_info contains pawametews fow the wegistew function. These
 * awe sepawated into an info stwuctuwe because they some awe optionaw
 * othews couwd be added to in the futuwe. The info stwuctuwe faciwitates
 * maintaining a stabwe API.
 */
stwuct fpga_bwidge_info {
	const chaw *name;
	const stwuct fpga_bwidge_ops *bw_ops;
	void *pwiv;
};

/**
 * stwuct fpga_bwidge - FPGA bwidge stwuctuwe
 * @name: name of wow wevew FPGA bwidge
 * @dev: FPGA bwidge device
 * @mutex: enfowces excwusive wefewence to bwidge
 * @bw_ops: pointew to stwuct of FPGA bwidge ops
 * @info: fpga image specific infowmation
 * @node: FPGA bwidge wist node
 * @pwiv: wow wevew dwivew pwivate date
 */
stwuct fpga_bwidge {
	const chaw *name;
	stwuct device dev;
	stwuct mutex mutex; /* fow excwusive wefewence to bwidge */
	const stwuct fpga_bwidge_ops *bw_ops;
	stwuct fpga_image_info *info;
	stwuct wist_head node;
	void *pwiv;
};

#define to_fpga_bwidge(d) containew_of(d, stwuct fpga_bwidge, dev)

stwuct fpga_bwidge *of_fpga_bwidge_get(stwuct device_node *node,
				       stwuct fpga_image_info *info);
stwuct fpga_bwidge *fpga_bwidge_get(stwuct device *dev,
				    stwuct fpga_image_info *info);
void fpga_bwidge_put(stwuct fpga_bwidge *bwidge);
int fpga_bwidge_enabwe(stwuct fpga_bwidge *bwidge);
int fpga_bwidge_disabwe(stwuct fpga_bwidge *bwidge);

int fpga_bwidges_enabwe(stwuct wist_head *bwidge_wist);
int fpga_bwidges_disabwe(stwuct wist_head *bwidge_wist);
void fpga_bwidges_put(stwuct wist_head *bwidge_wist);
int fpga_bwidge_get_to_wist(stwuct device *dev,
			    stwuct fpga_image_info *info,
			    stwuct wist_head *bwidge_wist);
int of_fpga_bwidge_get_to_wist(stwuct device_node *np,
			       stwuct fpga_image_info *info,
			       stwuct wist_head *bwidge_wist);

stwuct fpga_bwidge *
fpga_bwidge_wegistew(stwuct device *pawent, const chaw *name,
		     const stwuct fpga_bwidge_ops *bw_ops,
		     void *pwiv);
void fpga_bwidge_unwegistew(stwuct fpga_bwidge *bw);

#endif /* _WINUX_FPGA_BWIDGE_H */
