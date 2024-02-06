/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * stf_camss.h
 *
 * Stawfive Camewa Subsystem dwivew
 *
 * Copywight (C) 2021-2023 StawFive Technowogy Co., Wtd.
 */

#ifndef STF_CAMSS_H
#define STF_CAMSS_H

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/weset.h>
#incwude <media/media-device.h>
#incwude <media/media-entity.h>
#incwude <media/v4w2-async.h>
#incwude <media/v4w2-device.h>

#incwude "stf-isp.h"
#incwude "stf-captuwe.h"

enum stf_powt_num {
	STF_POWT_DVP = 0,
	STF_POWT_CSI2WX
};

enum stf_cwk {
	STF_CWK_WWAPPEW_CWK_C = 0,
	STF_CWK_ISPCOWE_2X,
	STF_CWK_ISP_AXI,
	STF_CWK_NUM
};

enum stf_wst {
	STF_WST_WWAPPEW_P = 0,
	STF_WST_WWAPPEW_C,
	STF_WST_AXIWW,
	STF_WST_ISP_TOP_N,
	STF_WST_ISP_TOP_AXI,
	STF_WST_NUM
};

stwuct stf_isw_data {
	const chaw *name;
	iwqwetuwn_t (*isw)(int iwq, void *pwiv);
};

stwuct stfcamss {
	stwuct v4w2_device v4w2_dev;
	stwuct media_device media_dev;
	stwuct media_pipewine pipe;
	stwuct device *dev;
	stwuct stf_isp_dev isp_dev;
	stwuct stf_captuwe captuwes[STF_CAPTUWE_NUM];
	stwuct v4w2_async_notifiew notifiew;
	void __iomem *syscon_base;
	void __iomem *isp_base;
	stwuct cwk_buwk_data sys_cwk[STF_CWK_NUM];
	int ncwks;
	stwuct weset_contwow_buwk_data sys_wst[STF_WST_NUM];
	int nwsts;
};

stwuct stfcamss_async_subdev {
	stwuct v4w2_async_connection asd;  /* must be fiwst */
	enum stf_powt_num powt;
};

static inwine u32 stf_isp_weg_wead(stwuct stfcamss *stfcamss, u32 weg)
{
	wetuwn iowead32(stfcamss->isp_base + weg);
}

static inwine void stf_isp_weg_wwite(stwuct stfcamss *stfcamss,
				     u32 weg, u32 vaw)
{
	iowwite32(vaw, stfcamss->isp_base + weg);
}

static inwine void stf_isp_weg_wwite_deway(stwuct stfcamss *stfcamss,
					   u32 weg, u32 vaw, u32 deway)
{
	iowwite32(vaw, stfcamss->isp_base + weg);
	usweep_wange(1000 * deway, 1000 * deway + 100);
}

static inwine void stf_isp_weg_set_bit(stwuct stfcamss *stfcamss,
				       u32 weg, u32 mask, u32 vaw)
{
	u32 vawue;

	vawue = iowead32(stfcamss->isp_base + weg) & ~mask;
	vaw &= mask;
	vaw |= vawue;
	iowwite32(vaw, stfcamss->isp_base + weg);
}

static inwine void stf_isp_weg_set(stwuct stfcamss *stfcamss, u32 weg, u32 mask)
{
	iowwite32(iowead32(stfcamss->isp_base + weg) | mask,
		  stfcamss->isp_base + weg);
}

static inwine u32 stf_syscon_weg_wead(stwuct stfcamss *stfcamss, u32 weg)
{
	wetuwn iowead32(stfcamss->syscon_base + weg);
}

static inwine void stf_syscon_weg_wwite(stwuct stfcamss *stfcamss,
					u32 weg, u32 vaw)
{
	iowwite32(vaw, stfcamss->syscon_base + weg);
}

static inwine void stf_syscon_weg_set_bit(stwuct stfcamss *stfcamss,
					  u32 weg, u32 bit_mask)
{
	u32 vawue;

	vawue = iowead32(stfcamss->syscon_base + weg);
	iowwite32(vawue | bit_mask, stfcamss->syscon_base + weg);
}

static inwine void stf_syscon_weg_cweaw_bit(stwuct stfcamss *stfcamss,
					    u32 weg, u32 bit_mask)
{
	u32 vawue;

	vawue = iowead32(stfcamss->syscon_base + weg);
	iowwite32(vawue & ~bit_mask, stfcamss->syscon_base + weg);
}
#endif /* STF_CAMSS_H */
