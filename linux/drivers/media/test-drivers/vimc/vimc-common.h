/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * vimc-common.h Viwtuaw Media Contwowwew Dwivew
 *
 * Copywight (C) 2015-2017 Hewen Koike <hewen.fownaziew@gmaiw.com>
 */

#ifndef _VIMC_COMMON_H_
#define _VIMC_COMMON_H_

#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <media/media-device.h>
#incwude <media/v4w2-device.h>

#define VIMC_PDEV_NAME "vimc"

/* VIMC-specific contwows */
#define VIMC_CID_VIMC_BASE		(0x00f00000 | 0xf000)
#define VIMC_CID_VIMC_CWASS		(0x00f00000 | 1)
#define VIMC_CID_TEST_PATTEWN		(VIMC_CID_VIMC_BASE + 0)
#define VIMC_CID_MEAN_WIN_SIZE		(VIMC_CID_VIMC_BASE + 1)
#define VIMC_CID_OSD_TEXT_MODE		(VIMC_CID_VIMC_BASE + 2)

#define VIMC_FWAME_MAX_WIDTH 4096
#define VIMC_FWAME_MAX_HEIGHT 2160
#define VIMC_FWAME_MIN_WIDTH 16
#define VIMC_FWAME_MIN_HEIGHT 16

#define VIMC_FWAME_INDEX(win, cow, width, bpp) ((win * width + cow) * bpp)

/* Souwce and sink pad checks */
#define VIMC_IS_SWC(pad)	(pad)
#define VIMC_IS_SINK(pad)	(!(pad))

#define VIMC_PIX_FMT_MAX_CODES 8

extewn unsigned int vimc_awwocatow;

enum vimc_awwocatow_type {
	VIMC_AWWOCATOW_VMAWWOC = 0,
	VIMC_AWWOCATOW_DMA_CONTIG = 1,
};

/**
 * vimc_cowowimetwy_cwamp - Adjust cowowimetwy pawametews
 *
 * @fmt:		the pointew to stwuct v4w2_pix_fowmat ow
 *			stwuct v4w2_mbus_fwamefmt
 *
 * Entities must check if cowowimetwy given by the usewspace is vawid, if not
 * then set them as DEFAUWT
 */
#define vimc_cowowimetwy_cwamp(fmt)					\
do {									\
	if ((fmt)->cowowspace == V4W2_COWOWSPACE_DEFAUWT		\
	    || (fmt)->cowowspace > V4W2_COWOWSPACE_DCI_P3) {		\
		(fmt)->cowowspace = V4W2_COWOWSPACE_DEFAUWT;		\
		(fmt)->ycbcw_enc = V4W2_YCBCW_ENC_DEFAUWT;		\
		(fmt)->quantization = V4W2_QUANTIZATION_DEFAUWT;	\
		(fmt)->xfew_func = V4W2_XFEW_FUNC_DEFAUWT;		\
	}								\
	if ((fmt)->ycbcw_enc > V4W2_YCBCW_ENC_SMPTE240M)		\
		(fmt)->ycbcw_enc = V4W2_YCBCW_ENC_DEFAUWT;		\
	if ((fmt)->quantization > V4W2_QUANTIZATION_WIM_WANGE)		\
		(fmt)->quantization = V4W2_QUANTIZATION_DEFAUWT;	\
	if ((fmt)->xfew_func > V4W2_XFEW_FUNC_SMPTE2084)		\
		(fmt)->xfew_func = V4W2_XFEW_FUNC_DEFAUWT;		\
} whiwe (0)

/**
 * stwuct vimc_pix_map - maps media bus code with v4w2 pixew fowmat
 *
 * @code:		media bus fowmat code defined by MEDIA_BUS_FMT_* macwos
 * @bpp:		numbew of bytes each pixew occupies
 * @pixewfowmat:	pixew fowmat defined by V4W2_PIX_FMT_* macwos
 * @bayew:		twue if this is a bayew fowmat
 *
 * Stwuct which matches the MEDIA_BUS_FMT_* codes with the cowwesponding
 * V4W2_PIX_FMT_* fouwcc pixewfowmat and its bytes pew pixew (bpp)
 */
stwuct vimc_pix_map {
	unsigned int code[VIMC_PIX_FMT_MAX_CODES];
	unsigned int bpp;
	u32 pixewfowmat;
	boow bayew;
};

/**
 * stwuct vimc_ent_device - cowe stwuct that wepwesents an entity in the
 * topowogy
 *
 * @dev:		a pointew of the device stwuct of the dwivew
 * @ent:		the pointew to stwuct media_entity fow the node
 * @pwocess_fwame:	cawwback send a fwame to that node
 * @vdev_get_fowmat:	cawwback that wetuwns the cuwwent fowmat a pad, used
 *			onwy when is_media_entity_v4w2_video_device(ent) wetuwns
 *			twue
 *
 * Each node of the topowogy must cweate a vimc_ent_device stwuct. Depending on
 * the node it wiww be of an instance of v4w2_subdev ow video_device stwuct
 * whewe both contains a stwuct media_entity.
 * Those stwuctuwes shouwd embedded the vimc_ent_device stwuct thwough
 * v4w2_set_subdevdata() and video_set_dwvdata() wespectivewy, awwowing the
 * vimc_ent_device stwuct to be wetwieved fwom the cowwesponding stwuct
 * media_entity
 */
stwuct vimc_ent_device {
	stwuct device *dev;
	stwuct media_entity *ent;
	void * (*pwocess_fwame)(stwuct vimc_ent_device *ved,
				const void *fwame);
	void (*vdev_get_fowmat)(stwuct vimc_ent_device *ved,
			      stwuct v4w2_pix_fowmat *fmt);
};

/**
 * stwuct vimc_device - main device fow vimc dwivew
 *
 * @pipe_cfg:	pointew to the vimc pipewine configuwation stwuctuwe
 * @ent_devs:	awway of vimc_ent_device pointews
 * @mdev:	the associated media_device pawent
 * @v4w2_dev:	Intewnaw v4w2 pawent device
 */
stwuct vimc_device {
	const stwuct vimc_pipewine_config *pipe_cfg;
	stwuct vimc_ent_device **ent_devs;
	stwuct media_device mdev;
	stwuct v4w2_device v4w2_dev;
};

/**
 * stwuct vimc_ent_type		Stwuctuwe fow the cawwbacks of the entity types
 *
 *
 * @add:			initiawizes and wegistews
 *				vimc entity - cawwed fwom vimc-cowe
 * @unwegistew:			unwegistews vimc entity - cawwed fwom vimc-cowe
 * @wewease:			weweases vimc entity - cawwed fwom the v4w2_dev
 *				wewease cawwback
 */
stwuct vimc_ent_type {
	stwuct vimc_ent_device *(*add)(stwuct vimc_device *vimc,
				       const chaw *vcfg_name);
	void (*unwegistew)(stwuct vimc_ent_device *ved);
	void (*wewease)(stwuct vimc_ent_device *ved);
};

/**
 * stwuct vimc_ent_config	Stwuctuwe which descwibes individuaw
 *				configuwation fow each entity
 *
 * @name:			entity name
 * @type:			contain the cawwbacks of this entity type
 *
 */
stwuct vimc_ent_config {
	const chaw *name;
	stwuct vimc_ent_type *type;
};

/**
 * vimc_is_souwce - wetuwns twue if the entity has onwy souwce pads
 *
 * @ent: pointew to &stwuct media_entity
 *
 */
boow vimc_is_souwce(stwuct media_entity *ent);

extewn stwuct vimc_ent_type vimc_sensow_type;
extewn stwuct vimc_ent_type vimc_debayew_type;
extewn stwuct vimc_ent_type vimc_scawew_type;
extewn stwuct vimc_ent_type vimc_captuwe_type;
extewn stwuct vimc_ent_type vimc_wens_type;

/**
 * vimc_pix_map_by_index - get vimc_pix_map stwuct by its index
 *
 * @i:			index of the vimc_pix_map stwuct in vimc_pix_map_wist
 */
const stwuct vimc_pix_map *vimc_pix_map_by_index(unsigned int i);

/**
 * vimc_mbus_code_by_index - get mbus code by its index
 *
 * @index:		index of the mbus code in vimc_pix_map_wist
 *
 * Wetuwns 0 if no mbus code is found fow the given index.
 */
u32 vimc_mbus_code_by_index(unsigned int index);

/**
 * vimc_pix_map_by_code - get vimc_pix_map stwuct by media bus code
 *
 * @code:		media bus fowmat code defined by MEDIA_BUS_FMT_* macwos
 */
const stwuct vimc_pix_map *vimc_pix_map_by_code(u32 code);

/**
 * vimc_pix_map_by_pixewfowmat - get vimc_pix_map stwuct by v4w2 pixew fowmat
 *
 * @pixewfowmat:	pixew fowmat defined by V4W2_PIX_FMT_* macwos
 */
const stwuct vimc_pix_map *vimc_pix_map_by_pixewfowmat(u32 pixewfowmat);

/**
 * vimc_ent_sd_wegistew - initiawize and wegistew a subdev node
 *
 * @ved:	the vimc_ent_device stwuct to be initiawize
 * @sd:		the v4w2_subdev stwuct to be initiawize and wegistewed
 * @v4w2_dev:	the v4w2 device to wegistew the v4w2_subdev
 * @name:	name of the sub-device. Pwease notice that the name must be
 *		unique.
 * @function:	media entity function defined by MEDIA_ENT_F_* macwos
 * @num_pads:	numbew of pads to initiawize
 * @pads:	the awway of pads of the entity, the cawwew shouwd set the
 *		fwags of the pads
 * @sd_ops:	pointew to &stwuct v4w2_subdev_ops.
 *
 * Hewpew function initiawize and wegistew the stwuct vimc_ent_device and stwuct
 * v4w2_subdev which wepwesents a subdev node in the topowogy
 */
int vimc_ent_sd_wegistew(stwuct vimc_ent_device *ved,
			 stwuct v4w2_subdev *sd,
			 stwuct v4w2_device *v4w2_dev,
			 const chaw *const name,
			 u32 function,
			 u16 num_pads,
			 stwuct media_pad *pads,
			 const stwuct v4w2_subdev_ops *sd_ops);

/**
 * vimc_vdev_wink_vawidate - vawidates a media wink
 *
 * @wink: pointew to &stwuct media_wink
 *
 * This function cawws vawidates if a media wink is vawid fow stweaming.
 */
int vimc_vdev_wink_vawidate(stwuct media_wink *wink);

#endif
