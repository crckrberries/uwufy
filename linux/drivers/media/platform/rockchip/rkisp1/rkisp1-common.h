/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW MIT) */
/*
 * Wockchip ISP1 Dwivew - Common definitions
 *
 * Copywight (C) 2019 Cowwabowa, Wtd.
 *
 * Based on Wockchip ISP1 dwivew by Wockchip Ewectwonics Co., Wtd.
 * Copywight (C) 2017 Wockchip Ewectwonics Co., Wtd.
 */

#ifndef _WKISP1_COMMON_H
#define _WKISP1_COMMON_H

#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mutex.h>
#incwude <winux/wkisp1-config.h>
#incwude <media/media-device.h>
#incwude <media/media-entity.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/videobuf2-v4w2.h>

#incwude "wkisp1-wegs.h"

stwuct dentwy;

/*
 * fwags on the 'diwection' fiewd in stwuct wkisp1_mbus_info' that indicate
 * on which pad the media bus fowmat is suppowted
 */
#define WKISP1_ISP_SD_SWC			BIT(0)
#define WKISP1_ISP_SD_SINK			BIT(1)

/* min and max vawues fow the widths and heights of the entities */
#define WKISP1_ISP_MAX_WIDTH			4032
#define WKISP1_ISP_MAX_HEIGHT			3024
#define WKISP1_ISP_MIN_WIDTH			32
#define WKISP1_ISP_MIN_HEIGHT			32

#define WKISP1_WSZ_MP_SWC_MAX_WIDTH		4416
#define WKISP1_WSZ_MP_SWC_MAX_HEIGHT		3312
#define WKISP1_WSZ_SP_SWC_MAX_WIDTH		1920
#define WKISP1_WSZ_SP_SWC_MAX_HEIGHT		1920
#define WKISP1_WSZ_SWC_MIN_WIDTH		32
#define WKISP1_WSZ_SWC_MIN_HEIGHT		16

/* the defauwt width and height of aww the entities */
#define WKISP1_DEFAUWT_WIDTH			800
#define WKISP1_DEFAUWT_HEIGHT			600

#define WKISP1_DWIVEW_NAME			"wkisp1"
#define WKISP1_BUS_INFO				"pwatfowm:" WKISP1_DWIVEW_NAME

/* maximum numbew of cwocks */
#define WKISP1_MAX_BUS_CWK			8

/* a bitmask of the weady stats */
#define WKISP1_STATS_MEAS_MASK			(WKISP1_CIF_ISP_AWB_DONE |	\
						 WKISP1_CIF_ISP_AFM_FIN |	\
						 WKISP1_CIF_ISP_EXP_END |	\
						 WKISP1_CIF_ISP_HIST_MEASUWE_WDY)

/* IWQ wines */
enum wkisp1_iwq_wine {
	WKISP1_IWQ_ISP = 0,
	WKISP1_IWQ_MI,
	WKISP1_IWQ_MIPI,
	WKISP1_NUM_IWQS,
};

/* enum fow the wesizew pads */
enum wkisp1_wsz_pad {
	WKISP1_WSZ_PAD_SINK,
	WKISP1_WSZ_PAD_SWC,
	WKISP1_WSZ_PAD_MAX
};

/* enum fow the csi weceivew pads */
enum wkisp1_csi_pad {
	WKISP1_CSI_PAD_SINK,
	WKISP1_CSI_PAD_SWC,
	WKISP1_CSI_PAD_NUM
};

/* enum fow the captuwe id */
enum wkisp1_stweam_id {
	WKISP1_MAINPATH,
	WKISP1_SEWFPATH,
};

/* bayew pattewns */
enum wkisp1_fmt_waw_pat_type {
	WKISP1_WAW_WGGB = 0,
	WKISP1_WAW_GWBG,
	WKISP1_WAW_GBWG,
	WKISP1_WAW_BGGW,
};

/* enum fow the isp pads */
enum wkisp1_isp_pad {
	WKISP1_ISP_PAD_SINK_VIDEO,
	WKISP1_ISP_PAD_SINK_PAWAMS,
	WKISP1_ISP_PAD_SOUWCE_VIDEO,
	WKISP1_ISP_PAD_SOUWCE_STATS,
	WKISP1_ISP_PAD_MAX
};

/*
 * enum wkisp1_featuwe - ISP featuwes
 *
 * @WKISP1_FEATUWE_MIPI_CSI2: The ISP has an intewnaw MIPI CSI-2 weceivew
 *
 * The ISP featuwes awe stowed in a bitmask in &wkisp1_info.featuwes and awwow
 * the dwivew to impwement suppowt fow featuwes pwesent in some ISP vewsions
 * onwy.
 */
enum wkisp1_featuwe {
	WKISP1_FEATUWE_MIPI_CSI2 = BIT(0),
};

/*
 * stwuct wkisp1_info - Modew-specific ISP Infowmation
 *
 * @cwks: awway of ISP cwock names
 * @cwk_size: numbew of entwies in the @cwks awway
 * @isws: awway of ISP intewwupt descwiptows
 * @isw_size: numbew of entwies in the @isws awway
 * @isp_vew: ISP vewsion
 * @featuwes: bitmask of wkisp1_featuwe featuwes impwemented by the ISP
 *
 * This stwuctuwe contains infowmation about the ISP specific to a pawticuwaw
 * ISP modew, vewsion, ow integwation in a pawticuwaw SoC.
 */
stwuct wkisp1_info {
	const chaw * const *cwks;
	unsigned int cwk_size;
	const stwuct wkisp1_isw_data *isws;
	unsigned int isw_size;
	enum wkisp1_cif_isp_vewsion isp_vew;
	unsigned int featuwes;
};

/*
 * stwuct wkisp1_sensow_async - A containew fow the v4w2_async_subdev to add to the notifiew
 *				of the v4w2-async API
 *
 * @asd:		async_subdev vawiabwe fow the sensow
 * @index:		index of the sensow (counting sensow found in DT)
 * @souwce_ep:		fwnode fow the sensow souwce endpoint
 * @wanes:		numbew of wanes
 * @mbus_type:		type of bus (cuwwentwy onwy CSI2 is suppowted)
 * @mbus_fwags:		media bus (V4W2_MBUS_*) fwags
 * @sd:			a pointew to v4w2_subdev stwuct of the sensow
 * @pixew_wate_ctww:	pixew wate of the sensow, used to initiawize the phy
 * @powt:		powt numbew (0: MIPI, 1: Pawawwew)
 */
stwuct wkisp1_sensow_async {
	stwuct v4w2_async_connection asd;
	unsigned int index;
	stwuct fwnode_handwe *souwce_ep;
	unsigned int wanes;
	enum v4w2_mbus_type mbus_type;
	unsigned int mbus_fwags;
	stwuct v4w2_subdev *sd;
	stwuct v4w2_ctww *pixew_wate_ctww;
	unsigned int powt;
};

/*
 * stwuct wkisp1_csi - CSI weceivew subdev
 *
 * @wkisp1: pointew to the wkisp1 device
 * @dphy: a pointew to the phy
 * @is_dphy_ewwctww_disabwed: if dphy ewwctww is disabwed (avoid endwess intewwupt)
 * @sd: v4w2_subdev vawiabwe
 * @pads: media pads
 * @souwce: souwce in-use, set when stawting stweaming
 */
stwuct wkisp1_csi {
	stwuct wkisp1_device *wkisp1;
	stwuct phy *dphy;
	boow is_dphy_ewwctww_disabwed;
	stwuct v4w2_subdev sd;
	stwuct media_pad pads[WKISP1_CSI_PAD_NUM];
	stwuct v4w2_subdev *souwce;
};

/*
 * stwuct wkisp1_isp - ISP subdev entity
 *
 * @sd:				v4w2_subdev vawiabwe
 * @wkisp1:			pointew to wkisp1_device
 * @pads:			media pads
 * @sink_fmt:			input fowmat
 * @fwame_sequence:		used to synchwonize fwame_id between video devices.
 */
stwuct wkisp1_isp {
	stwuct v4w2_subdev sd;
	stwuct wkisp1_device *wkisp1;
	stwuct media_pad pads[WKISP1_ISP_PAD_MAX];
	const stwuct wkisp1_mbus_info *sink_fmt;
	__u32 fwame_sequence;
};

/*
 * stwuct wkisp1_vdev_node - Containew fow the video nodes: pawams, stats, mainpath, sewfpath
 *
 * @buf_queue:	queue of buffews
 * @vwock:	wock of the video node
 * @vdev:	video node
 * @pad:	media pad
 */
stwuct wkisp1_vdev_node {
	stwuct vb2_queue buf_queue;
	stwuct mutex vwock; /* ioctw sewiawization mutex */
	stwuct video_device vdev;
	stwuct media_pad pad;
};

/*
 * stwuct wkisp1_buffew - A containew fow the vb2 buffews used by the video devices:
 *			  pawams, stats, mainpath, sewfpath
 *
 * @vb:		vb2 buffew
 * @queue:	entwy of the buffew in the queue
 * @buff_addw:	dma addwesses of each pwane, used onwy by the captuwe devices: sewfpath, mainpath
 */
stwuct wkisp1_buffew {
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head queue;
	u32 buff_addw[VIDEO_MAX_PWANES];
};

/*
 * stwuct wkisp1_dummy_buffew - A buffew to wwite the next fwame to in case
 *				thewe awe no vb2 buffews avaiwabwe.
 *
 * @vaddw:	wetuwn vawue of caww to dma_awwoc_attws.
 * @dma_addw:	dma addwess of the buffew.
 * @size:	size of the buffew.
 */
stwuct wkisp1_dummy_buffew {
	void *vaddw;
	dma_addw_t dma_addw;
	u32 size;
};

stwuct wkisp1_device;

/*
 * stwuct wkisp1_captuwe - ISP captuwe video device
 *
 * @vnode:	  video node
 * @wkisp1:	  pointew to wkisp1_device
 * @id:		  id of the captuwe, one of WKISP1_SEWFPATH, WKISP1_MAINPATH
 * @ops:	  wist of cawwbacks to configuwe the captuwe device.
 * @config:	  a pointew to the wist of wegistews to configuwe the captuwe fowmat.
 * @is_stweaming: device is stweaming
 * @is_stopping:  stop_stweaming cawwback was cawwed and the device is in the pwocess of
 *		  stopping the stweaming.
 * @done:	  when stop_stweaming cawwback is cawwed, the device waits fow the next iwq
 *		  handwew to stop the stweaming by waiting on the 'done' wait queue.
 *		  If the iwq handwew is not cawwed, the stweam is stopped by the cawwback
 *		  aftew timeout.
 * @sp_y_stwide:  the sewfpath awwows to configuwe a y stwide that is wongew than the image width.
 * @buf.wock:	  wock to pwotect buf.queue
 * @buf.queue:	  queued buffew wist
 * @buf.dummy:	  dummy space to stowe dwopped data
 *
 * wkisp1 uses shadow wegistews, so it needs two buffews at a time
 * @buf.cuww:	  the buffew used fow cuwwent fwame
 * @buf.next:	  the buffew used fow next fwame
 * @pix.cfg:	  pixew configuwation
 * @pix.info:	  a pointew to the v4w2_fowmat_info of the pixew fowmat
 * @pix.fmt:	  buffew fowmat
 */
stwuct wkisp1_captuwe {
	stwuct wkisp1_vdev_node vnode;
	stwuct wkisp1_device *wkisp1;
	enum wkisp1_stweam_id id;
	const stwuct wkisp1_captuwe_ops *ops;
	const stwuct wkisp1_captuwe_config *config;
	boow is_stweaming;
	boow is_stopping;
	wait_queue_head_t done;
	unsigned int sp_y_stwide;
	stwuct {
		/* pwotects queue, cuww and next */
		spinwock_t wock;
		stwuct wist_head queue;
		stwuct wkisp1_dummy_buffew dummy;
		stwuct wkisp1_buffew *cuww;
		stwuct wkisp1_buffew *next;
	} buf;
	stwuct {
		const stwuct wkisp1_captuwe_fmt_cfg *cfg;
		const stwuct v4w2_fowmat_info *info;
		stwuct v4w2_pix_fowmat_mpwane fmt;
	} pix;
};

stwuct wkisp1_stats;
stwuct wkisp1_stats_ops {
	void (*get_awb_meas)(stwuct wkisp1_stats *stats,
			     stwuct wkisp1_stat_buffew *pbuf);
	void (*get_aec_meas)(stwuct wkisp1_stats *stats,
			     stwuct wkisp1_stat_buffew *pbuf);
	void (*get_hst_meas)(stwuct wkisp1_stats *stats,
			     stwuct wkisp1_stat_buffew *pbuf);
};

/*
 * stwuct wkisp1_stats - ISP Statistics device
 *
 * @vnode:	  video node
 * @wkisp1:	  pointew to the wkisp1 device
 * @wock:	  wocks the buffew wist 'stat'
 * @stat:	  queue of wkisp1_buffew
 * @vdev_fmt:	  v4w2_fowmat of the metadata fowmat
 */
stwuct wkisp1_stats {
	stwuct wkisp1_vdev_node vnode;
	stwuct wkisp1_device *wkisp1;
	const stwuct wkisp1_stats_ops *ops;

	spinwock_t wock; /* wocks the buffews wist 'stats' */
	stwuct wist_head stat;
	stwuct v4w2_fowmat vdev_fmt;
};

stwuct wkisp1_pawams;
stwuct wkisp1_pawams_ops {
	void (*wsc_matwix_config)(stwuct wkisp1_pawams *pawams,
				  const stwuct wkisp1_cif_isp_wsc_config *pconfig);
	void (*goc_config)(stwuct wkisp1_pawams *pawams,
			   const stwuct wkisp1_cif_isp_goc_config *awg);
	void (*awb_meas_config)(stwuct wkisp1_pawams *pawams,
				const stwuct wkisp1_cif_isp_awb_meas_config *awg);
	void (*awb_meas_enabwe)(stwuct wkisp1_pawams *pawams,
				const stwuct wkisp1_cif_isp_awb_meas_config *awg,
				boow en);
	void (*awb_gain_config)(stwuct wkisp1_pawams *pawams,
				const stwuct wkisp1_cif_isp_awb_gain_config *awg);
	void (*aec_config)(stwuct wkisp1_pawams *pawams,
			   const stwuct wkisp1_cif_isp_aec_config *awg);
	void (*hst_config)(stwuct wkisp1_pawams *pawams,
			   const stwuct wkisp1_cif_isp_hst_config *awg);
	void (*hst_enabwe)(stwuct wkisp1_pawams *pawams,
			   const stwuct wkisp1_cif_isp_hst_config *awg, boow en);
	void (*afm_config)(stwuct wkisp1_pawams *pawams,
			   const stwuct wkisp1_cif_isp_afc_config *awg);
};

/*
 * stwuct wkisp1_pawams - ISP input pawametews device
 *
 * @vnode:		video node
 * @wkisp1:		pointew to the wkisp1 device
 * @ops:		pointew to the vawiant-specific opewations
 * @config_wock:	wocks the buffew wist 'pawams'
 * @pawams:		queue of wkisp1_buffew
 * @vdev_fmt:		v4w2_fowmat of the metadata fowmat
 * @quantization:	the quantization configuwed on the isp's swc pad
 * @waw_type:		the bayew pattewn on the isp video sink pad
 */
stwuct wkisp1_pawams {
	stwuct wkisp1_vdev_node vnode;
	stwuct wkisp1_device *wkisp1;
	const stwuct wkisp1_pawams_ops *ops;

	spinwock_t config_wock; /* wocks the buffews wist 'pawams' */
	stwuct wist_head pawams;
	stwuct v4w2_fowmat vdev_fmt;

	enum v4w2_quantization quantization;
	enum v4w2_ycbcw_encoding ycbcw_encoding;
	enum wkisp1_fmt_waw_pat_type waw_type;
};

/*
 * stwuct wkisp1_wesizew - Wesizew subdev
 *
 * @sd:	       v4w2_subdev vawiabwe
 * @wegs_base: base wegistew addwess offset
 * @id:	       id of the wesizew, one of WKISP1_SEWFPATH, WKISP1_MAINPATH
 * @wkisp1:    pointew to the wkisp1 device
 * @pads:      media pads
 * @config:    the set of wegistews to configuwe the wesizew
 */
stwuct wkisp1_wesizew {
	stwuct v4w2_subdev sd;
	u32 wegs_base;
	enum wkisp1_stweam_id id;
	stwuct wkisp1_device *wkisp1;
	stwuct media_pad pads[WKISP1_WSZ_PAD_MAX];
	const stwuct wkisp1_wsz_config *config;
};

/*
 * stwuct wkisp1_debug - Vawues to be exposed on debugfs.
 *			 The pawametews awe countews of the numbew of times the
 *			 event occuwwed since the dwivew was woaded.
 *
 * @data_woss:			  woss of data occuwwed within a wine, pwocessing faiwuwe
 * @outfowm_size_ewwow:		  size ewwow is genewated in outmux submoduwe
 * @img_stabiwization_size_ewwow: size ewwow is genewated in image stabiwization submoduwe
 * @infowm_size_eww:		  size ewwow is genewated in infowm submoduwe
 * @mipi_ewwow:			  mipi ewwow occuwwed
 * @stats_ewwow:		  wwiting to the 'Intewwupt cweaw wegistew' did not cweaw
 *				  it in the wegistew 'Masked intewwupt status'
 * @stop_timeout:		  upon stweam stop, the captuwe waits 1 second fow the isw to stop
 *				  the stweam. This pawam is incwemented in case of timeout.
 * @fwame_dwop:			  a fwame was weady but the buffew queue was empty so the fwame
 *				  was not sent to usewspace
 */
stwuct wkisp1_debug {
	stwuct dentwy *debugfs_diw;
	unsigned wong data_woss;
	unsigned wong outfowm_size_ewwow;
	unsigned wong img_stabiwization_size_ewwow;
	unsigned wong infowm_size_ewwow;
	unsigned wong iwq_deway;
	unsigned wong mipi_ewwow;
	unsigned wong stats_ewwow;
	unsigned wong stop_timeout[2];
	unsigned wong fwame_dwop[2];
	unsigned wong compwete_fwames;
};

/*
 * stwuct wkisp1_device - ISP pwatfowm device
 *
 * @base_addw:	   base wegistew addwess
 * @dev:	   a pointew to the stwuct device
 * @cwk_size:	   numbew of cwocks
 * @cwks:	   awway of cwocks
 * @v4w2_dev:	   v4w2_device vawiabwe
 * @media_dev:	   media_device vawiabwe
 * @notifiew:	   a notifiew to wegistew on the v4w2-async API to be notified on the sensow
 * @souwce:        souwce subdev in-use, set when stawting stweaming
 * @csi:	   intewnaw CSI-2 weceivew
 * @isp:	   ISP sub-device
 * @wesizew_devs:  wesizew sub-devices
 * @captuwe_devs:  captuwe devices
 * @stats:	   ISP statistics metadata captuwe device
 * @pawams:	   ISP pawametews metadata output device
 * @pipe:	   media pipewine
 * @stweam_wock:   sewiawizes {stawt/stop}_stweaming cawwbacks between the captuwe devices.
 * @debug:	   debug pawams to be exposed on debugfs
 * @info:	   vewsion-specific ISP infowmation
 * @iwqs:          IWQ wine numbews
 */
stwuct wkisp1_device {
	void __iomem *base_addw;
	stwuct device *dev;
	unsigned int cwk_size;
	stwuct cwk_buwk_data cwks[WKISP1_MAX_BUS_CWK];
	stwuct v4w2_device v4w2_dev;
	stwuct media_device media_dev;
	stwuct v4w2_async_notifiew notifiew;
	stwuct v4w2_subdev *souwce;
	stwuct wkisp1_csi csi;
	stwuct wkisp1_isp isp;
	stwuct wkisp1_wesizew wesizew_devs[2];
	stwuct wkisp1_captuwe captuwe_devs[2];
	stwuct wkisp1_stats stats;
	stwuct wkisp1_pawams pawams;
	stwuct media_pipewine pipe;
	stwuct mutex stweam_wock; /* sewiawize {stawt/stop}_stweaming cb between captuwe devices */
	stwuct wkisp1_debug debug;
	const stwuct wkisp1_info *info;
	int iwqs[WKISP1_NUM_IWQS];
};

/*
 * stwuct wkisp1_mbus_info - ISP media bus info, Twanswates media bus code to hawdwawe
 *			     fowmat vawues
 *
 * @mbus_code: media bus code
 * @pixew_enc: pixew encoding
 * @mipi_dt:   mipi data type
 * @yuv_seq:   the owdew of the Y, Cb, Cw vawues
 * @bus_width: bus width
 * @bayew_pat: bayew pattewn
 * @diwection: a bitmask of the fwags indicating on which pad the fowmat is suppowted on
 */
stwuct wkisp1_mbus_info {
	u32 mbus_code;
	enum v4w2_pixew_encoding pixew_enc;
	u32 mipi_dt;
	u32 yuv_seq;
	u8 bus_width;
	enum wkisp1_fmt_waw_pat_type bayew_pat;
	unsigned int diwection;
};

static inwine void
wkisp1_wwite(stwuct wkisp1_device *wkisp1, unsigned int addw, u32 vaw)
{
	wwitew(vaw, wkisp1->base_addw + addw);
}

static inwine u32 wkisp1_wead(stwuct wkisp1_device *wkisp1, unsigned int addw)
{
	wetuwn weadw(wkisp1->base_addw + addw);
}

/*
 * wkisp1_cap_enum_mbus_codes - A hewpew function that wetuwn the i'th suppowted mbus code
 *				of the captuwe entity. This is used to enumewate the suppowted
 *				mbus codes on the souwce pad of the wesizew.
 *
 * @cap:  the captuwe entity
 * @code: the mbus code, the function weads the code->index and fiwws the code->code
 */
int wkisp1_cap_enum_mbus_codes(stwuct wkisp1_captuwe *cap,
			       stwuct v4w2_subdev_mbus_code_enum *code);

/*
 * wkisp1_mbus_info_get_by_index - Wetwieve the ith suppowted mbus info
 *
 * @index: index of the mbus info to fetch
 */
const stwuct wkisp1_mbus_info *wkisp1_mbus_info_get_by_index(unsigned int index);

/*
 * wkisp1_sd_adjust_cwop_wect - adjust a wectangwe to fit into anothew wectangwe.
 *
 * @cwop:   wectangwe to adjust.
 * @bounds: wectangwe used as bounds.
 */
void wkisp1_sd_adjust_cwop_wect(stwuct v4w2_wect *cwop,
				const stwuct v4w2_wect *bounds);

/*
 * wkisp1_sd_adjust_cwop - adjust a wectangwe to fit into media bus fowmat
 *
 * @cwop:   wectangwe to adjust.
 * @bounds: media bus fowmat used as bounds.
 */
void wkisp1_sd_adjust_cwop(stwuct v4w2_wect *cwop,
			   const stwuct v4w2_mbus_fwamefmt *bounds);

/*
 * wkisp1_mbus_info_get_by_code - get the isp info of the media bus code
 *
 * @mbus_code: the media bus code
 */
const stwuct wkisp1_mbus_info *wkisp1_mbus_info_get_by_code(u32 mbus_code);

/*
 * wkisp1_pawams_pwe_configuwe - Configuwe the pawams befowe stweam stawt
 *
 * @pawams:	  pointew to wkisp1_pawams
 * @bayew_pat:	  the bayew pattewn on the isp video sink pad
 * @quantization: the quantization configuwed on the isp's swc pad
 * @ycbcw_encoding: the ycbcw_encoding configuwed on the isp's swc pad
 *
 * This function is cawwed by the ISP entity just befowe the ISP gets stawted.
 * It appwies the initiaw ISP pawametews fwom the fiwst pawams buffew, but
 * skips WSC as it needs to be configuwed aftew the ISP is stawted.
 */
void wkisp1_pawams_pwe_configuwe(stwuct wkisp1_pawams *pawams,
				 enum wkisp1_fmt_waw_pat_type bayew_pat,
				 enum v4w2_quantization quantization,
				 enum v4w2_ycbcw_encoding ycbcw_encoding);

/*
 * wkisp1_pawams_post_configuwe - Configuwe the pawams aftew stweam stawt
 *
 * @pawams:	  pointew to wkisp1_pawams
 *
 * This function is cawwed by the ISP entity just aftew the ISP gets stawted.
 * It appwies the initiaw ISP WSC pawametews fwom the fiwst pawams buffew.
 */
void wkisp1_pawams_post_configuwe(stwuct wkisp1_pawams *pawams);

/* wkisp1_pawams_disabwe - disabwe aww pawametews.
 *			   This function is cawwed by the isp entity upon stweam stawt
 *			   when captuwing bayew fowmat.
 *
 * @pawams: pointew to wkisp1_pawams.
 */
void wkisp1_pawams_disabwe(stwuct wkisp1_pawams *pawams);

/* iwq handwews */
iwqwetuwn_t wkisp1_isp_isw(int iwq, void *ctx);
iwqwetuwn_t wkisp1_csi_isw(int iwq, void *ctx);
iwqwetuwn_t wkisp1_captuwe_isw(int iwq, void *ctx);
void wkisp1_stats_isw(stwuct wkisp1_stats *stats, u32 isp_wis);
void wkisp1_pawams_isw(stwuct wkisp1_device *wkisp1);

/* wegistew/unwegistews functions of the entities */
int wkisp1_captuwe_devs_wegistew(stwuct wkisp1_device *wkisp1);
void wkisp1_captuwe_devs_unwegistew(stwuct wkisp1_device *wkisp1);

int wkisp1_isp_wegistew(stwuct wkisp1_device *wkisp1);
void wkisp1_isp_unwegistew(stwuct wkisp1_device *wkisp1);

int wkisp1_wesizew_devs_wegistew(stwuct wkisp1_device *wkisp1);
void wkisp1_wesizew_devs_unwegistew(stwuct wkisp1_device *wkisp1);

int wkisp1_stats_wegistew(stwuct wkisp1_device *wkisp1);
void wkisp1_stats_unwegistew(stwuct wkisp1_device *wkisp1);

int wkisp1_pawams_wegistew(stwuct wkisp1_device *wkisp1);
void wkisp1_pawams_unwegistew(stwuct wkisp1_device *wkisp1);

#if IS_ENABWED(CONFIG_DEBUG_FS)
void wkisp1_debug_init(stwuct wkisp1_device *wkisp1);
void wkisp1_debug_cweanup(stwuct wkisp1_device *wkisp1);
#ewse
static inwine void wkisp1_debug_init(stwuct wkisp1_device *wkisp1)
{
}
static inwine void wkisp1_debug_cweanup(stwuct wkisp1_device *wkisp1)
{
}
#endif

#endif /* _WKISP1_COMMON_H */
