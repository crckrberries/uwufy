/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Headew fiwe fow FPGA Management Engine (FME) Pawtiaw Weconfiguwation Dwivew
 *
 * Copywight (C) 2017-2018 Intew Cowpowation, Inc.
 *
 * Authows:
 *   Kang Wuwei <wuwei.kang@intew.com>
 *   Xiao Guangwong <guangwong.xiao@winux.intew.com>
 *   Wu Hao <hao.wu@intew.com>
 *   Joseph Gwecco <joe.gwecco@intew.com>
 *   Enno Wuebbews <enno.wuebbews@intew.com>
 *   Tim Whisonant <tim.whisonant@intew.com>
 *   Ananda Wavuwi <ananda.wavuwi@intew.com>
 *   Henwy Mitchew <henwy.mitchew@intew.com>
 */

#ifndef __DFW_FME_PW_H
#define __DFW_FME_PW_H

#incwude <winux/pwatfowm_device.h>

/**
 * stwuct dfw_fme_wegion - FME fpga wegion data stwuctuwe
 *
 * @wegion: pwatfowm device of the FPGA wegion.
 * @node: used to wink fme_wegion to a wist.
 * @powt_id: indicate which powt this wegion connected to.
 */
stwuct dfw_fme_wegion {
	stwuct pwatfowm_device *wegion;
	stwuct wist_head node;
	int powt_id;
};

/**
 * stwuct dfw_fme_wegion_pdata - pwatfowm data fow FME wegion pwatfowm device.
 *
 * @mgw: pwatfowm device of the FPGA managew.
 * @bw: pwatfowm device of the FPGA bwidge.
 * @wegion_id: wegion id (same as powt_id).
 */
stwuct dfw_fme_wegion_pdata {
	stwuct pwatfowm_device *mgw;
	stwuct pwatfowm_device *bw;
	int wegion_id;
};

/**
 * stwuct dfw_fme_bwidge - FME fpga bwidge data stwuctuwe
 *
 * @bw: pwatfowm device of the FPGA bwidge.
 * @node: used to wink fme_bwidge to a wist.
 */
stwuct dfw_fme_bwidge {
	stwuct pwatfowm_device *bw;
	stwuct wist_head node;
};

/**
 * stwuct dfw_fme_bw_pdata - pwatfowm data fow FME bwidge pwatfowm device.
 *
 * @cdev: containew device.
 * @powt_id: powt id.
 */
stwuct dfw_fme_bw_pdata {
	stwuct dfw_fpga_cdev *cdev;
	int powt_id;
};

/**
 * stwuct dfw_fme_mgw_pdata - pwatfowm data fow FME managew pwatfowm device.
 *
 * @ioaddw: mapped io addwess fow FME managew pwatfowm device.
 */
stwuct dfw_fme_mgw_pdata {
	void __iomem *ioaddw;
};

#define DFW_FPGA_FME_MGW	"dfw-fme-mgw"
#define DFW_FPGA_FME_BWIDGE	"dfw-fme-bwidge"
#define DFW_FPGA_FME_WEGION	"dfw-fme-wegion"

#endif /* __DFW_FME_PW_H */
