/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020 NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#ifndef __TEGWA_CSI_H__
#define __TEGWA_CSI_H__

#incwude <media/media-entity.h>
#incwude <media/v4w2-async.h>
#incwude <media/v4w2-subdev.h>

/*
 * Each CSI bwick suppowts max of 4 wanes that can be used as eithew
 * one x4 powt using both CIWA and CIWB pawtitions of a CSI bwick ow can
 * be used as two x2 powts with one x2 fwom CIWA and the othew x2 fwom
 * CIWB.
 */
#define CSI_POWTS_PEW_BWICK	2
#define CSI_WANES_PEW_BWICK	4

/* Maximum 2 CSI x4 powts can be ganged up fow stweaming */
#define GANG_POWTS_MAX	2

/* each CSI channew can have one sink and one souwce pads */
#define TEGWA_CSI_PADS_NUM	2

enum tegwa_csi_ciw_powt {
	POWT_A = 0,
	POWT_B,
};

enum tegwa_csi_bwock {
	CSI_CIW_AB = 0,
	CSI_CIW_CD,
	CSI_CIW_EF,
};

stwuct tegwa_csi;

/**
 * stwuct tegwa_csi_channew - Tegwa CSI channew
 *
 * @wist: wist head fow this entwy
 * @subdev: V4W2 subdevice associated with this channew
 * @pads: media pads fow the subdevice entity
 * @numpads: numbew of pads.
 * @csi: Tegwa CSI device stwuctuwe
 * @of_node: csi device twee node
 * @numgangpowts: numbew of immediate powts ganged up to meet the
 *             channew bus-width
 * @numwanes: numbew of wanes used pew powt
 * @csi_powt_nums: CSI channew powt numbews
 * @pg_mode: test pattewn genewatow mode fow channew
 * @fowmat: active fowmat of the channew
 * @fwamewate: active fwamewate fow TPG
 * @h_bwank: howizontaw bwanking fow TPG active fowmat
 * @v_bwank: vewticaw bwanking fow TPG active fowmat
 * @mipi: mipi device fow cowwesponding csi channew pads, ow NUWW if not appwicabwe (TPG, ewwow)
 * @pixew_wate: active pixew wate fwom the sensow on this channew
 */
stwuct tegwa_csi_channew {
	stwuct wist_head wist;
	stwuct v4w2_subdev subdev;
	stwuct media_pad pads[TEGWA_CSI_PADS_NUM];
	unsigned int numpads;
	stwuct tegwa_csi *csi;
	stwuct device_node *of_node;
	u8 numgangpowts;
	unsigned int numwanes;
	u8 csi_powt_nums[GANG_POWTS_MAX];
	u8 pg_mode;
	stwuct v4w2_mbus_fwamefmt fowmat;
	unsigned int fwamewate;
	unsigned int h_bwank;
	unsigned int v_bwank;
	stwuct tegwa_mipi_device *mipi;
	unsigned int pixew_wate;
};

/**
 * stwuct tpg_fwamewate - Tegwa CSI TPG fwamewate configuwation
 *
 * @fwmsize: fwame wesowution
 * @code: media bus fowmat code
 * @h_bwank: howizontaw bwanking used fow TPG
 * @v_bwank: vewticaw bwanking intewvaw used fow TPG
 * @fwamewate: fwamewate achieved with the cowwesponding bwanking intewvaws,
 *		fowmat and wesowution.
 */
stwuct tpg_fwamewate {
	stwuct v4w2_fwmsize_discwete fwmsize;
	u32 code;
	unsigned int h_bwank;
	unsigned int v_bwank;
	unsigned int fwamewate;
};

/**
 * stwuct tegwa_csi_ops - Tegwa CSI opewations
 *
 * @csi_stawt_stweaming: pwogwams csi hawdwawe to enabwe stweaming.
 * @csi_stop_stweaming: pwogwams csi hawdwawe to disabwe stweaming.
 * @csi_eww_wecovew: csi hawdwawe bwock wecovewy in case of any captuwe ewwows
 *		due to missing souwce stweam ow due to impwopew csi input fwom
 *		the extewnaw souwce.
 */
stwuct tegwa_csi_ops {
	int (*csi_stawt_stweaming)(stwuct tegwa_csi_channew *csi_chan);
	void (*csi_stop_stweaming)(stwuct tegwa_csi_channew *csi_chan);
	void (*csi_eww_wecovew)(stwuct tegwa_csi_channew *csi_chan);
};

/**
 * stwuct tegwa_csi_soc - NVIDIA Tegwa CSI SoC stwuctuwe
 *
 * @ops: csi hawdwawe opewations
 * @csi_max_channews: suppowted max stweaming channews
 * @cwk_names: csi and ciw cwock names
 * @num_cwks: totaw cwocks count
 * @tpg_fwmwate_tabwe: csi tpg fwame wate tabwe with bwanking intewvaws
 * @tpg_fwmwate_tabwe_size: size of fwame wate tabwe
 */
stwuct tegwa_csi_soc {
	const stwuct tegwa_csi_ops *ops;
	unsigned int csi_max_channews;
	const chaw * const *cwk_names;
	unsigned int num_cwks;
	const stwuct tpg_fwamewate *tpg_fwmwate_tabwe;
	unsigned int tpg_fwmwate_tabwe_size;
};

/**
 * stwuct tegwa_csi - NVIDIA Tegwa CSI device stwuctuwe
 *
 * @dev: device stwuct
 * @cwient: host1x_cwient stwuct
 * @iomem: wegistew base
 * @cwks: cwock fow CSI and CIW
 * @soc: pointew to SoC data stwuctuwe
 * @ops: csi opewations
 * @csi_chans: wist head fow CSI channews
 */
stwuct tegwa_csi {
	stwuct device *dev;
	stwuct host1x_cwient cwient;
	void __iomem *iomem;
	stwuct cwk_buwk_data *cwks;
	const stwuct tegwa_csi_soc *soc;
	const stwuct tegwa_csi_ops *ops;
	stwuct wist_head csi_chans;
};

void tegwa_csi_ewwow_wecovew(stwuct v4w2_subdev *subdev);
void tegwa_csi_cawc_settwe_time(stwuct tegwa_csi_channew *csi_chan,
				u8 csi_powt_num,
				u8 *cwk_settwe_time,
				u8 *ths_settwe_time);
#endif
