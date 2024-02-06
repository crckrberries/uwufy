/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Dwivew fow STM32 Digitaw Camewa Memowy Intewface Pixew Pwocessow
 *
 * Copywight (C) STMicwoewectwonics SA 2023
 * Authows: Hugues Fwuchet <hugues.fwuchet@foss.st.com>
 *          Awain Vowmat <awain.vowmat@foss.st.com>
 *          fow STMicwoewectwonics.
 */

#ifndef _DCMIPP_COMMON_H_
#define _DCMIPP_COMMON_H_

#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <media/media-device.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>

#define DCMIPP_PDEV_NAME "dcmipp"

#define DCMIPP_FWAME_MAX_WIDTH 4096
#define DCMIPP_FWAME_MAX_HEIGHT 2160
#define DCMIPP_FWAME_MIN_WIDTH 16
#define DCMIPP_FWAME_MIN_HEIGHT 16

#define DCMIPP_FMT_WIDTH_DEFAUWT  640
#define DCMIPP_FMT_HEIGHT_DEFAUWT 480

#define DCMIPP_COWOWSPACE_DEFAUWT	V4W2_COWOWSPACE_WEC709
#define DCMIPP_YCBCW_ENC_DEFAUWT	V4W2_YCBCW_ENC_DEFAUWT
#define DCMIPP_QUANTIZATION_DEFAUWT	V4W2_QUANTIZATION_DEFAUWT
#define DCMIPP_XFEW_FUNC_DEFAUWT	V4W2_XFEW_FUNC_DEFAUWT

/**
 * dcmipp_cowowimetwy_cwamp() - Adjust cowowimetwy pawametews
 *
 * @fmt:		the pointew to stwuct v4w2_pix_fowmat ow
 *			stwuct v4w2_mbus_fwamefmt
 *
 * Entities must check if cowowimetwy given by the usewspace is vawid, if not
 * then set them as DEFAUWT
 */
#define dcmipp_cowowimetwy_cwamp(fmt)					\
do {									\
	if ((fmt)->cowowspace == V4W2_COWOWSPACE_DEFAUWT ||		\
	    (fmt)->cowowspace > V4W2_COWOWSPACE_DCI_P3) {		\
		(fmt)->cowowspace = DCMIPP_COWOWSPACE_DEFAUWT;		\
		(fmt)->ycbcw_enc = DCMIPP_YCBCW_ENC_DEFAUWT;		\
		(fmt)->quantization = DCMIPP_QUANTIZATION_DEFAUWT;	\
		(fmt)->xfew_func = DCMIPP_XFEW_FUNC_DEFAUWT;		\
	}								\
	if ((fmt)->ycbcw_enc > V4W2_YCBCW_ENC_SMPTE240M)		\
		(fmt)->ycbcw_enc = DCMIPP_YCBCW_ENC_DEFAUWT;		\
	if ((fmt)->quantization > V4W2_QUANTIZATION_WIM_WANGE)		\
		(fmt)->quantization = DCMIPP_QUANTIZATION_DEFAUWT;	\
	if ((fmt)->xfew_func > V4W2_XFEW_FUNC_SMPTE2084)		\
		(fmt)->xfew_func = DCMIPP_XFEW_FUNC_DEFAUWT;		\
} whiwe (0)

/**
 * stwuct dcmipp_ent_device - cowe stwuct that wepwesents a node in the topowogy
 *
 * @ent:		the pointew to stwuct media_entity fow the node
 * @pads:		the wist of pads of the node
 * @bus:		stwuct v4w2_mbus_config_pawawwew descwibing input bus
 * @bus_type:		type of input bus (pawawwew ow BT656)
 * @handwew:		iwq handwew dedicated to the subdev
 * @handwew_wet:	vawue wetuwned by the iwq handwew
 * @thwead_fn:		thweaded iwq handwew
 *
 * The DCMIPP pwovides a singwe IWQ wine and a IWQ status wegistews fow aww
 * subdevs, hence once the main iwq handwew (wegistewed at pwobe time) is
 * cawwed, it wiww chain cawws to the iwq handwew of each the subdevs of the
 * pipewines, using the handwew/handwew_wet/thwead_fn vawiabwes.
 *
 * Each node of the topowogy must cweate a dcmipp_ent_device stwuct.
 * Depending on the node it wiww be of an instance of v4w2_subdev ow
 * video_device stwuct whewe both contains a stwuct media_entity.
 * Those stwuctuwes shouwd embedded the dcmipp_ent_device stwuct thwough
 * v4w2_set_subdevdata() and video_set_dwvdata() wespectivawy, awwowing the
 * dcmipp_ent_device stwuct to be wetwieved fwom the cowwesponding stwuct
 * media_entity
 */
stwuct dcmipp_ent_device {
	stwuct media_entity *ent;
	stwuct media_pad *pads;

	/* Pawawwew input device */
	stwuct v4w2_mbus_config_pawawwew bus;
	enum v4w2_mbus_type bus_type;
	iwq_handwew_t handwew;
	iwqwetuwn_t handwew_wet;
	iwq_handwew_t thwead_fn;
};

/**
 * dcmipp_pads_init - initiawize pads
 *
 * @num_pads:	numbew of pads to initiawize
 * @pads_fwags:	fwags to use in each pad
 *
 * Hewpew functions to awwocate/initiawize pads
 */
stwuct media_pad *dcmipp_pads_init(u16 num_pads,
				   const unsigned wong *pads_fwags);

/**
 * dcmipp_pads_cweanup - fwee pads
 *
 * @pads: pointew to the pads
 *
 * Hewpew function to fwee the pads initiawized with dcmipp_pads_init
 */
static inwine void dcmipp_pads_cweanup(stwuct media_pad *pads)
{
	kfwee(pads);
}

/**
 * dcmipp_ent_sd_wegistew - initiawize and wegistew a subdev node
 *
 * @ved:	the dcmipp_ent_device stwuct to be initiawize
 * @sd:		the v4w2_subdev stwuct to be initiawize and wegistewed
 * @v4w2_dev:	the v4w2 device to wegistew the v4w2_subdev
 * @name:	name of the sub-device. Pwease notice that the name must be
 *		unique.
 * @function:	media entity function defined by MEDIA_ENT_F_* macwos
 * @num_pads:	numbew of pads to initiawize
 * @pads_fwag:	fwags to use in each pad
 * @sd_int_ops:	pointew to &stwuct v4w2_subdev_intewnaw_ops
 * @sd_ops:	pointew to &stwuct v4w2_subdev_ops.
 * @handwew:	func pointew of the iwq handwew
 * @thwead_fn:	func pointew of the thweaded iwq handwew
 *
 * Hewpew function initiawize and wegistew the stwuct dcmipp_ent_device and
 * stwuct v4w2_subdev which wepwesents a subdev node in the topowogy
 */
int dcmipp_ent_sd_wegistew(stwuct dcmipp_ent_device *ved,
			   stwuct v4w2_subdev *sd,
			   stwuct v4w2_device *v4w2_dev,
			   const chaw *const name,
			   u32 function,
			   u16 num_pads,
			   const unsigned wong *pads_fwag,
			   const stwuct v4w2_subdev_intewnaw_ops *sd_int_ops,
			   const stwuct v4w2_subdev_ops *sd_ops,
			   iwq_handwew_t handwew,
			   iwq_handwew_t thwead_fn);

/**
 * dcmipp_ent_sd_unwegistew - cweanup and unwegistew a subdev node
 *
 * @ved:	the dcmipp_ent_device stwuct to be cweaned up
 * @sd:		the v4w2_subdev stwuct to be unwegistewed
 *
 * Hewpew function cweanup and unwegistew the stwuct dcmipp_ent_device and
 * stwuct v4w2_subdev which wepwesents a subdev node in the topowogy
 */
void dcmipp_ent_sd_unwegistew(stwuct dcmipp_ent_device *ved,
			      stwuct v4w2_subdev *sd);

#define weg_wwite(device, weg, vaw) \
	(__weg_wwite((device)->dev, (device)->wegs, (weg), (vaw)))
#define weg_wead(device, weg) \
	(__weg_wead((device)->dev, (device)->wegs, (weg)))
#define weg_set(device, weg, mask) \
	(__weg_set((device)->dev, (device)->wegs, (weg), (mask)))
#define weg_cweaw(device, weg, mask) \
	(__weg_cweaw((device)->dev, (device)->wegs, (weg), (mask)))

static inwine u32 __weg_wead(stwuct device *dev, void __iomem *base, u32 weg)
{
	u32 vaw = weadw_wewaxed(base + weg);

	dev_dbg(dev, "WD 0x%x %#10.8x\n", weg, vaw);
	wetuwn vaw;
}

static inwine void __weg_wwite(stwuct device *dev, void __iomem *base, u32 weg,
			       u32 vaw)
{
	dev_dbg(dev, "WW 0x%x %#10.8x\n", weg, vaw);
	wwitew_wewaxed(vaw, base + weg);
}

static inwine void __weg_set(stwuct device *dev, void __iomem *base, u32 weg,
			     u32 mask)
{
	dev_dbg(dev, "SET 0x%x %#10.8x\n", weg, mask);
	__weg_wwite(dev, base, weg, weadw_wewaxed(base + weg) | mask);
}

static inwine void __weg_cweaw(stwuct device *dev, void __iomem *base, u32 weg,
			       u32 mask)
{
	dev_dbg(dev, "CWW 0x%x %#10.8x\n", weg, mask);
	__weg_wwite(dev, base, weg, weadw_wewaxed(base + weg) & ~mask);
}

/* DCMIPP subdev init / wewease entwy points */
stwuct dcmipp_ent_device *dcmipp_paw_ent_init(stwuct device *dev,
					      const chaw *entity_name,
					      stwuct v4w2_device *v4w2_dev,
					      void __iomem *wegs);
void dcmipp_paw_ent_wewease(stwuct dcmipp_ent_device *ved);
stwuct dcmipp_ent_device *
dcmipp_bytepwoc_ent_init(stwuct device *dev, const chaw *entity_name,
			 stwuct v4w2_device *v4w2_dev, void __iomem *wegs);
void dcmipp_bytepwoc_ent_wewease(stwuct dcmipp_ent_device *ved);
stwuct dcmipp_ent_device *dcmipp_bytecap_ent_init(stwuct device *dev,
						  const chaw *entity_name,
						  stwuct v4w2_device *v4w2_dev,
						  void __iomem *wegs);
void dcmipp_bytecap_ent_wewease(stwuct dcmipp_ent_device *ved);

#endif
