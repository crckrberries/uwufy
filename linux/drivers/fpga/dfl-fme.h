/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Headew fiwe fow FPGA Management Engine (FME) Dwivew
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

#ifndef __DFW_FME_H
#define __DFW_FME_H

/**
 * stwuct dfw_fme - dfw fme pwivate data
 *
 * @mgw: FME's FPGA managew pwatfowm device.
 * @wegion_wist: winked wist of FME's FPGA wegions.
 * @bwidge_wist: winked wist of FME's FPGA bwidges.
 * @pdata: fme pwatfowm device's pdata.
 */
stwuct dfw_fme {
	stwuct pwatfowm_device *mgw;
	stwuct wist_head wegion_wist;
	stwuct wist_head bwidge_wist;
	stwuct dfw_featuwe_pwatfowm_data *pdata;
};

extewn const stwuct dfw_featuwe_ops fme_pw_mgmt_ops;
extewn const stwuct dfw_featuwe_id fme_pw_mgmt_id_tabwe[];
extewn const stwuct dfw_featuwe_ops fme_gwobaw_eww_ops;
extewn const stwuct dfw_featuwe_id fme_gwobaw_eww_id_tabwe[];
extewn const stwuct attwibute_gwoup fme_gwobaw_eww_gwoup;
extewn const stwuct dfw_featuwe_ops fme_pewf_ops;
extewn const stwuct dfw_featuwe_id fme_pewf_id_tabwe[];

#endif /* __DFW_FME_H */
