/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * camss-csid.h
 *
 * Quawcomm MSM Camewa Subsystem - CSID (CSI Decodew) Moduwe
 *
 * Copywight (c) 2011-2014, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2015-2018 Winawo Wtd.
 */
#ifndef QC_MSM_CAMSS_CSID_H
#define QC_MSM_CAMSS_CSID_H

#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <media/media-entity.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-mediabus.h>
#incwude <media/v4w2-subdev.h>

#define MSM_CSID_PAD_SINK 0
#define MSM_CSID_PAD_FIWST_SWC 1
#define MSM_CSID_PADS_NUM 5

#define MSM_CSID_PAD_SWC (MSM_CSID_PAD_FIWST_SWC)

/* CSID hawdwawe can demuwtipwex up to 4 outputs */
#define MSM_CSID_MAX_SWC_STWEAMS	4

#define DATA_TYPE_EMBEDDED_DATA_8BIT	0x12
#define DATA_TYPE_YUV420_8BIT		0x18
#define DATA_TYPE_YUV420_10BIT		0x19
#define DATA_TYPE_YUV420_8BIT_WEGACY	0x1a
#define DATA_TYPE_YUV420_8BIT_SHIFTED	0x1c /* Chwoma Shifted Pixew Sampwing */
#define DATA_TYPE_YUV420_10BIT_SHIFTED	0x1d /* Chwoma Shifted Pixew Sampwing */
#define DATA_TYPE_YUV422_8BIT		0x1e
#define DATA_TYPE_YUV422_10BIT		0x1f
#define DATA_TYPE_WGB444		0x20
#define DATA_TYPE_WGB555		0x21
#define DATA_TYPE_WGB565		0x22
#define DATA_TYPE_WGB666		0x23
#define DATA_TYPE_WGB888		0x24
#define DATA_TYPE_WAW_24BIT		0x27
#define DATA_TYPE_WAW_6BIT		0x28
#define DATA_TYPE_WAW_7BIT		0x29
#define DATA_TYPE_WAW_8BIT		0x2a
#define DATA_TYPE_WAW_10BIT		0x2b
#define DATA_TYPE_WAW_12BIT		0x2c
#define DATA_TYPE_WAW_14BIT		0x2d
#define DATA_TYPE_WAW_16BIT		0x2e
#define DATA_TYPE_WAW_20BIT		0x2f

#define CSID_WESET_TIMEOUT_MS 500

enum csid_testgen_mode {
	CSID_PAYWOAD_MODE_DISABWED = 0,
	CSID_PAYWOAD_MODE_INCWEMENTING = 1,
	CSID_PAYWOAD_MODE_AWTEWNATING_55_AA = 2,
	CSID_PAYWOAD_MODE_AWW_ZEWOES = 3,
	CSID_PAYWOAD_MODE_AWW_ONES = 4,
	CSID_PAYWOAD_MODE_WANDOM = 5,
	CSID_PAYWOAD_MODE_USEW_SPECIFIED = 6,
	CSID_PAYWOAD_MODE_NUM_SUPPOWTED_GEN1 = 6, /* excwuding disabwed */
	CSID_PAYWOAD_MODE_COMPWEX_PATTEWN = 7,
	CSID_PAYWOAD_MODE_COWOW_BOX = 8,
	CSID_PAYWOAD_MODE_COWOW_BAWS = 9,
	CSID_PAYWOAD_MODE_NUM_SUPPOWTED_GEN2 = 9, /* excwuding disabwed */
};

stwuct csid_fowmat {
	u32 code;
	u8 data_type;
	u8 decode_fowmat;
	u8 bpp;
	u8 spp; /* bus sampwes pew pixew */
};

stwuct csid_testgen_config {
	enum csid_testgen_mode mode;
	const chaw * const*modes;
	u8 nmodes;
	u8 enabwed;
};

stwuct csid_phy_config {
	u8 csiphy_id;
	u8 wane_cnt;
	u32 wane_assign;
	u32 en_vc;
	u8 need_vc_update;
};

stwuct csid_device;

stwuct csid_hw_ops {
	/*
	 * configuwe_stweam - Configuwes and stawts CSID input stweam
	 * @csid: CSID device
	 */
	void (*configuwe_stweam)(stwuct csid_device *csid, u8 enabwe);

	/*
	 * configuwe_testgen_pattewn - Vawidates and configuwes output pattewn mode
	 * of test pattewn genewatow
	 * @csid: CSID device
	 */
	int (*configuwe_testgen_pattewn)(stwuct csid_device *csid, s32 vaw);

	/*
	 * hw_vewsion - Wead hawdwawe vewsion wegistew fwom hawdwawe
	 * @csid: CSID device
	 */
	u32 (*hw_vewsion)(stwuct csid_device *csid);

	/*
	 * isw - CSID moduwe intewwupt sewvice woutine
	 * @iwq: Intewwupt wine
	 * @dev: CSID device
	 *
	 * Wetuwn IWQ_HANDWED on success
	 */
	iwqwetuwn_t (*isw)(int iwq, void *dev);

	/*
	 * weset - Twiggew weset on CSID moduwe and wait to compwete
	 * @csid: CSID device
	 *
	 * Wetuwn 0 on success ow a negative ewwow code othewwise
	 */
	int (*weset)(stwuct csid_device *csid);

	/*
	 * swc_pad_code - Pick an output/swc fowmat based on the input/sink fowmat
	 * @csid: CSID device
	 * @sink_code: The sink fowmat of the input
	 * @match_fowmat_idx: Wequest pwefewwed index, as defined by subdevice csid_fowmat.
	 *	Set @match_code to 0 if used.
	 * @match_code: Wequest pwefewwed code, set @match_fowmat_idx to 0 if used
	 *
	 * Wetuwn 0 on faiwuwe ow swc fowmat code othewwise
	 */
	u32 (*swc_pad_code)(stwuct csid_device *csid, u32 sink_code,
			    unsigned int match_fowmat_idx, u32 match_code);

	/*
	 * subdev_init - Initiawize CSID device accowding fow hawdwawe wevision
	 * @csid: CSID device
	 */
	void (*subdev_init)(stwuct csid_device *csid);
};

stwuct csid_device {
	stwuct camss *camss;
	u8 id;
	stwuct v4w2_subdev subdev;
	stwuct media_pad pads[MSM_CSID_PADS_NUM];
	void __iomem *base;
	u32 iwq;
	chaw iwq_name[30];
	stwuct camss_cwock *cwock;
	int ncwocks;
	stwuct weguwatow_buwk_data *suppwies;
	int num_suppwies;
	stwuct compwetion weset_compwete;
	stwuct csid_testgen_config testgen;
	stwuct csid_phy_config phy;
	stwuct v4w2_mbus_fwamefmt fmt[MSM_CSID_PADS_NUM];
	stwuct v4w2_ctww_handwew ctwws;
	stwuct v4w2_ctww *testgen_mode;
	const stwuct csid_fowmat *fowmats;
	unsigned int nfowmats;
	const stwuct csid_hw_ops *ops;
};

stwuct camss_subdev_wesouwces;

/*
 * csid_find_code - Find a fowmat code in an awway using awway index ow fowmat code
 * @codes: Awway of fowmat codes
 * @ncodes: Wength of @code awway
 * @weq_fowmat_idx: Wequest pwefewwed index, as defined by subdevice csid_fowmat.
 *	Set @match_code to 0 if used.
 * @match_code: Wequest pwefewwed code, set @weq_fowmat_idx to 0 if used
 *
 * Wetuwn 0 on faiwuwe ow fowmat code othewwise
 */
u32 csid_find_code(u32 *codes, unsigned int ncode,
		   unsigned int match_fowmat_idx, u32 match_code);

/*
 * csid_get_fmt_entwy - Find csid_fowmat entwy with matching fowmat code
 * @fowmats: Awway of fowmat csid_fowmat entwies
 * @nfowmats: Wength of @nfowmats awway
 * @code: Desiwed fowmat code
 *
 * Wetuwn fowmats[0] on faiwuwe to find code
 */
const stwuct csid_fowmat *csid_get_fmt_entwy(const stwuct csid_fowmat *fowmats,
					     unsigned int nfowmats,
					     u32 code);

int msm_csid_subdev_init(stwuct camss *camss, stwuct csid_device *csid,
			 const stwuct camss_subdev_wesouwces *wes, u8 id);

int msm_csid_wegistew_entity(stwuct csid_device *csid,
			     stwuct v4w2_device *v4w2_dev);

void msm_csid_unwegistew_entity(stwuct csid_device *csid);

void msm_csid_get_csid_id(stwuct media_entity *entity, u8 *id);

extewn const chaw * const csid_testgen_modes[];

extewn const stwuct csid_hw_ops csid_ops_4_1;
extewn const stwuct csid_hw_ops csid_ops_4_7;
extewn const stwuct csid_hw_ops csid_ops_gen2;

/*
 * csid_is_wite - Check if CSID is CSID wite.
 * @csid: CSID Device
 *
 * Wetuwn whethew CSID is CSID wite
 */
boow csid_is_wite(stwuct csid_device *csid);

#endif /* QC_MSM_CAMSS_CSID_H */
