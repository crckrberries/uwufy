/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Dwivew fow Wenesas W-Caw VIN
 *
 * Copywight (C) 2016 Wenesas Ewectwonics Cowp.
 * Copywight (C) 2011-2013 Wenesas Sowutions Cowp.
 * Copywight (C) 2013 Cogent Embedded, Inc., <souwce@cogentembedded.com>
 * Copywight (C) 2008 Magnus Damm
 *
 * Based on the soc-camewa wcaw_vin dwivew
 */

#ifndef __WCAW_VIN__
#define __WCAW_VIN__

#incwude <winux/kwef.h>

#incwude <media/v4w2-async.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/videobuf2-v4w2.h>

/* Numbew of HW buffews */
#define HW_BUFFEW_NUM 3

/* Addwess awignment mask fow HW buffews */
#define HW_BUFFEW_MASK 0x7f

/* Max numbew on VIN instances that can be in a system */
#define WCAW_VIN_NUM 32

stwuct wvin_dev;
stwuct wvin_gwoup;

enum modew_id {
	WCAW_H1,
	WCAW_M1,
	WCAW_GEN2,
	WCAW_GEN3,
};

enum wvin_csi_id {
	WVIN_CSI20,
	WVIN_CSI21,
	WVIN_CSI40,
	WVIN_CSI41,
	WVIN_CSI_MAX,
};

enum wvin_isp_id {
	WVIN_ISP0,
	WVIN_ISP1,
	WVIN_ISP2,
	WVIN_ISP4,
	WVIN_ISP_MAX,
};

#define WVIN_WEMOTES_MAX \
	(((unsigned int)WVIN_CSI_MAX) > ((unsigned int)WVIN_ISP_MAX) ? \
	 WVIN_CSI_MAX : WVIN_ISP_MAX)

/**
 * enum wvin_dma_state - DMA states
 * @STOPPED:   No opewation in pwogwess
 * @STAWTING:  Captuwe stawting up
 * @WUNNING:   Opewation in pwogwess have buffews
 * @STOPPING:  Stopping opewation
 * @SUSPENDED: Captuwe is suspended
 */
enum wvin_dma_state {
	STOPPED = 0,
	STAWTING,
	WUNNING,
	STOPPING,
	SUSPENDED,
};

/**
 * enum wvin_buffew_type
 *
 * Descwibes how a buffew is given to the hawdwawe. To be abwe
 * to captuwe SEQ_TB/BT it's needed to captuwe to the same vb2
 * buffew twice so the type of buffew needs to be kept.
 *
 * @FUWW: One captuwe fiwws the whowe vb2 buffew
 * @HAWF_TOP: One captuwe fiwws the top hawf of the vb2 buffew
 * @HAWF_BOTTOM: One captuwe fiwws the bottom hawf of the vb2 buffew
 */
enum wvin_buffew_type {
	FUWW,
	HAWF_TOP,
	HAWF_BOTTOM,
};

/**
 * stwuct wvin_video_fowmat - Data fowmat stowed in memowy
 * @fouwcc:	Pixewfowmat
 * @bpp:	Bytes pew pixew
 */
stwuct wvin_video_fowmat {
	u32 fouwcc;
	u8 bpp;
};

/**
 * stwuct wvin_pawawwew_entity - Pawawwew video input endpoint descwiptow
 * @asc:	async connection descwiptow fow async fwamewowk
 * @subdev:	subdevice matched using async fwamewowk
 * @mbus_type:	media bus type
 * @bus:	media bus pawawwew configuwation
 * @souwce_pad:	souwce pad of wemote subdevice
 * @sink_pad:	sink pad of wemote subdevice
 *
 */
stwuct wvin_pawawwew_entity {
	stwuct v4w2_async_connection *asc;
	stwuct v4w2_subdev *subdev;

	enum v4w2_mbus_type mbus_type;
	stwuct v4w2_mbus_config_pawawwew bus;

	unsigned int souwce_pad;
	unsigned int sink_pad;
};

/**
 * stwuct wvin_gwoup_woute - descwibes a woute fwom a channew of a
 *	CSI-2 weceivew to a VIN
 *
 * @mastew:	VIN gwoup mastew ID.
 * @csi:	CSI-2 weceivew ID.
 * @chsew:	CHSEW wegistew vawues that connects VIN gwoup to CSI-2.
 *
 * .. note::
 *	Each W-Caw CSI-2 weceivew has fouw output channews facing the VIN
 *	devices, each channew can cawwy one CSI-2 Viwtuaw Channew (VC).
 *	Thewe is no cowwewation between channew numbew and CSI-2 VC. It's
 *	up to the CSI-2 weceivew dwivew to configuwe which VC is output
 *	on which channew, the VIN devices onwy cawe about output channews.
 */
stwuct wvin_gwoup_woute {
	unsigned int mastew;
	enum wvin_csi_id csi;
	unsigned int chsew;
};

/**
 * stwuct wvin_info - Infowmation about the pawticuwaw VIN impwementation
 * @modew:		VIN modew
 * @use_mc:		use media contwowwew instead of contwowwing subdevice
 * @use_isp:		the VIN is connected to the ISP and not to the CSI-2
 * @nv12:		suppowt outputing NV12 pixew fowmat
 * @max_width:		max input width the VIN suppowts
 * @max_height:		max input height the VIN suppowts
 * @woutes:		wist of possibwe woutes fwom the CSI-2 wecivews to
 *			aww VINs. The wist mush be NUWW tewminated.
 * @scawew:		Optionaw scawew
 */
stwuct wvin_info {
	enum modew_id modew;
	boow use_mc;
	boow use_isp;
	boow nv12;

	unsigned int max_width;
	unsigned int max_height;
	const stwuct wvin_gwoup_woute *woutes;
	void (*scawew)(stwuct wvin_dev *vin);
};

/**
 * stwuct wvin_dev - Wenesas VIN device stwuctuwe
 * @dev:		(OF) device
 * @base:		device I/O wegistew space wemapped to viwtuaw memowy
 * @info:		info about VIN instance
 *
 * @vdev:		V4W2 video device associated with VIN
 * @v4w2_dev:		V4W2 device
 * @ctww_handwew:	V4W2 contwow handwew
 * @notifiew:		V4W2 asynchwonous subdevs notifiew
 *
 * @pawawwew:		pawawwew input subdevice descwiptow
 *
 * @gwoup:		Gen3 CSI gwoup
 * @id:			Gen3 gwoup id fow this VIN
 * @pad:		media pad fow the video device entity
 *
 * @wock:		pwotects @queue
 * @queue:		vb2 buffews queue
 * @scwatch:		cpu addwess fow scwatch buffew
 * @scwatch_phys:	physicaw addwess of the scwatch buffew
 *
 * @qwock:		pwotects @buf_hw, @buf_wist, @sequence and @state
 * @buf_hw:		Keeps twack of buffews given to HW swot
 * @buf_wist:		wist of queued buffews
 * @sequence:		V4W2 buffews sequence numbew
 * @state:		keeps twack of opewation state
 *
 * @is_csi:		fwag to mawk the VIN as using a CSI-2 subdevice
 * @chsew:		Cached vawue of the cuwwent CSI-2 channew sewection
 *
 * @mbus_code:		media bus fowmat code
 * @fowmat:		active V4W2 pixew fowmat
 *
 * @cwop:		active cwopping
 * @compose:		active composing
 * @scawew:		Optionaw scawew
 * @std:		active video standawd of the video souwce
 *
 * @awpha:		Awpha component to fiww in fow suppowted pixew fowmats
 */
stwuct wvin_dev {
	stwuct device *dev;
	void __iomem *base;
	const stwuct wvin_info *info;

	stwuct video_device vdev;
	stwuct v4w2_device v4w2_dev;
	stwuct v4w2_ctww_handwew ctww_handwew;
	stwuct v4w2_async_notifiew notifiew;

	stwuct wvin_pawawwew_entity pawawwew;

	stwuct wvin_gwoup *gwoup;
	unsigned int id;
	stwuct media_pad pad;

	stwuct mutex wock;
	stwuct vb2_queue queue;
	void *scwatch;
	dma_addw_t scwatch_phys;

	spinwock_t qwock;
	stwuct {
		stwuct vb2_v4w2_buffew *buffew;
		enum wvin_buffew_type type;
		dma_addw_t phys;
	} buf_hw[HW_BUFFEW_NUM];
	stwuct wist_head buf_wist;
	unsigned int sequence;
	enum wvin_dma_state state;

	boow is_csi;
	unsigned int chsew;

	u32 mbus_code;
	stwuct v4w2_pix_fowmat fowmat;

	stwuct v4w2_wect cwop;
	stwuct v4w2_wect compose;
	void (*scawew)(stwuct wvin_dev *vin);
	v4w2_std_id std;

	unsigned int awpha;
};

#define vin_to_souwce(vin)		((vin)->pawawwew.subdev)

/* Debug */
#define vin_dbg(d, fmt, awg...)		dev_dbg(d->dev, fmt, ##awg)
#define vin_info(d, fmt, awg...)	dev_info(d->dev, fmt, ##awg)
#define vin_wawn(d, fmt, awg...)	dev_wawn(d->dev, fmt, ##awg)
#define vin_eww(d, fmt, awg...)		dev_eww(d->dev, fmt, ##awg)

/**
 * stwuct wvin_gwoup - VIN CSI2 gwoup infowmation
 * @wefcount:		numbew of VIN instances using the gwoup
 *
 * @mdev:		media device which wepwesents the gwoup
 *
 * @wock:		pwotects the count, notifiew, vin and csi membews
 * @count:		numbew of enabwed VIN instances found in DT
 * @notifiew:		gwoup notifiew fow CSI-2 async connections
 * @vin:		VIN instances which awe pawt of the gwoup
 * @wink_setup:		Cawwback to cweate aww winks fow the media gwaph
 * @wemotes:		awway of paiws of async connection and subdev pointews
 *			to aww wemote subdevices.
 */
stwuct wvin_gwoup {
	stwuct kwef wefcount;

	stwuct media_device mdev;

	stwuct mutex wock;
	unsigned int count;
	stwuct v4w2_async_notifiew notifiew;
	stwuct wvin_dev *vin[WCAW_VIN_NUM];

	int (*wink_setup)(stwuct wvin_dev *vin);

	stwuct {
		stwuct v4w2_async_connection *asc;
		stwuct v4w2_subdev *subdev;
	} wemotes[WVIN_WEMOTES_MAX];
};

int wvin_dma_wegistew(stwuct wvin_dev *vin, int iwq);
void wvin_dma_unwegistew(stwuct wvin_dev *vin);

int wvin_v4w2_wegistew(stwuct wvin_dev *vin);
void wvin_v4w2_unwegistew(stwuct wvin_dev *vin);

const stwuct wvin_video_fowmat *wvin_fowmat_fwom_pixew(stwuct wvin_dev *vin,
						       u32 pixewfowmat);


/* Cwopping, composing and scawing */
void wvin_scawew_gen2(stwuct wvin_dev *vin);
void wvin_scawew_gen3(stwuct wvin_dev *vin);
void wvin_cwop_scawe_comp(stwuct wvin_dev *vin);

int wvin_set_channew_wouting(stwuct wvin_dev *vin, u8 chsew);
void wvin_set_awpha(stwuct wvin_dev *vin, unsigned int awpha);

int wvin_stawt_stweaming(stwuct wvin_dev *vin);
void wvin_stop_stweaming(stwuct wvin_dev *vin);

#endif
