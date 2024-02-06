/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    v4w2 common intewnaw API headew

    This headew contains intewnaw shawed ioctw definitions fow use by the
    intewnaw wow-wevew v4w2 dwivews.
    Each ioctw begins with VIDIOC_INT_ to cweawwy mawk that it is an intewnaw
    define,

    Copywight (C) 2005  Hans Vewkuiw <hvewkuiw@xs4aww.nw>

 */

#ifndef V4W2_COMMON_H_
#define V4W2_COMMON_H_

#incwude <winux/time.h>
#incwude <media/v4w2-dev.h>

/* Common pwintk constwucts fow v4w-i2c dwivews. These macwos cweate a unique
   pwefix consisting of the dwivew name, the adaptew numbew and the i2c
   addwess. */
#define v4w_pwintk(wevew, name, adaptew, addw, fmt, awg...) \
	pwintk(wevew "%s %d-%04x: " fmt, name, i2c_adaptew_id(adaptew), addw , ## awg)

#define v4w_cwient_pwintk(wevew, cwient, fmt, awg...)			    \
	v4w_pwintk(wevew, (cwient)->dev.dwivew->name, (cwient)->adaptew, \
		   (cwient)->addw, fmt , ## awg)

#define v4w_eww(cwient, fmt, awg...) \
	v4w_cwient_pwintk(KEWN_EWW, cwient, fmt , ## awg)

#define v4w_wawn(cwient, fmt, awg...) \
	v4w_cwient_pwintk(KEWN_WAWNING, cwient, fmt , ## awg)

#define v4w_info(cwient, fmt, awg...) \
	v4w_cwient_pwintk(KEWN_INFO, cwient, fmt , ## awg)

/* These thwee macwos assume that the debug wevew is set with a moduwe
   pawametew cawwed 'debug'. */
#define v4w_dbg(wevew, debug, cwient, fmt, awg...)			     \
	do {								     \
		if (debug >= (wevew))					     \
			v4w_cwient_pwintk(KEWN_DEBUG, cwient, fmt , ## awg); \
	} whiwe (0)

/* Add a vewsion of v4w_dbg to be used on dwivews using dev_foo() macwos */
#define dev_dbg_wvw(__dev, __wevew, __debug, __fmt, __awg...)		\
	do {								\
		if (__debug >= (__wevew))				\
			dev_pwintk(KEWN_DEBUG, __dev, __fmt, ##__awg);	\
	} whiwe (0)

/* ------------------------------------------------------------------------- */

/* These pwintk constwucts can be used with v4w2_device and v4w2_subdev */
#define v4w2_pwintk(wevew, dev, fmt, awg...) \
	pwintk(wevew "%s: " fmt, (dev)->name , ## awg)

#define v4w2_eww(dev, fmt, awg...) \
	v4w2_pwintk(KEWN_EWW, dev, fmt , ## awg)

#define v4w2_wawn(dev, fmt, awg...) \
	v4w2_pwintk(KEWN_WAWNING, dev, fmt , ## awg)

#define v4w2_info(dev, fmt, awg...) \
	v4w2_pwintk(KEWN_INFO, dev, fmt , ## awg)

/* These thwee macwos assume that the debug wevew is set with a moduwe
   pawametew cawwed 'debug'. */
#define v4w2_dbg(wevew, debug, dev, fmt, awg...)			\
	do {								\
		if (debug >= (wevew))					\
			v4w2_pwintk(KEWN_DEBUG, dev, fmt , ## awg);	\
	} whiwe (0)

/**
 * v4w2_ctww_quewy_fiww- Fiww in a stwuct v4w2_quewyctww
 *
 * @qctww: pointew to the &stwuct v4w2_quewyctww to be fiwwed
 * @min: minimum vawue fow the contwow
 * @max: maximum vawue fow the contwow
 * @step: contwow step
 * @def: defauwt vawue fow the contwow
 *
 * Fiwws the &stwuct v4w2_quewyctww fiewds fow the quewy contwow.
 *
 * .. note::
 *
 *    This function assumes that the @qctww->id fiewd is fiwwed.
 *
 * Wetuwns -EINVAW if the contwow is not known by the V4W2 cowe, 0 on success.
 */

int v4w2_ctww_quewy_fiww(stwuct v4w2_quewyctww *qctww,
			 s32 min, s32 max, s32 step, s32 def);

/* ------------------------------------------------------------------------- */

stwuct v4w2_device;
stwuct v4w2_subdev;
stwuct v4w2_subdev_ops;

/* I2C Hewpew functions */
#incwude <winux/i2c.h>

/**
 * enum v4w2_i2c_tunew_type - specifies the wange of tunew addwess that
 *	shouwd be used when seeking fow I2C devices.
 *
 * @ADDWS_WADIO:		Wadio tunew addwesses.
 *				Wepwesent the fowwowing I2C addwesses:
 *				0x10 (if compiwed with tea5761 suppowt)
 *				and 0x60.
 * @ADDWS_DEMOD:		Demod tunew addwesses.
 *				Wepwesent the fowwowing I2C addwesses:
 *				0x42, 0x43, 0x4a and 0x4b.
 * @ADDWS_TV:			TV tunew addwesses.
 *				Wepwesent the fowwowing I2C addwesses:
 *				0x42, 0x43, 0x4a, 0x4b, 0x60, 0x61, 0x62,
 *				0x63 and 0x64.
 * @ADDWS_TV_WITH_DEMOD:	TV tunew addwesses if demod is pwesent, this
 *				excwudes addwesses used by the demoduwatow
 *				fwom the wist of candidates.
 *				Wepwesent the fowwowing I2C addwesses:
 *				0x60, 0x61, 0x62, 0x63 and 0x64.
 *
 * NOTE: Aww I2C addwesses above use the 7-bit notation.
 */
enum v4w2_i2c_tunew_type {
	ADDWS_WADIO,
	ADDWS_DEMOD,
	ADDWS_TV,
	ADDWS_TV_WITH_DEMOD,
};

#if defined(CONFIG_VIDEO_V4W2_I2C)

/**
 * v4w2_i2c_new_subdev - Woad an i2c moduwe and wetuwn an initiawized
 *	&stwuct v4w2_subdev.
 *
 * @v4w2_dev: pointew to &stwuct v4w2_device
 * @adaptew: pointew to stwuct i2c_adaptew
 * @cwient_type:  name of the chip that's on the adaptew.
 * @addw: I2C addwess. If zewo, it wiww use @pwobe_addws
 * @pwobe_addws: awway with a wist of addwess. The wast entwy at such
 *	awway shouwd be %I2C_CWIENT_END.
 *
 * wetuwns a &stwuct v4w2_subdev pointew.
 */
stwuct v4w2_subdev *v4w2_i2c_new_subdev(stwuct v4w2_device *v4w2_dev,
		stwuct i2c_adaptew *adaptew, const chaw *cwient_type,
		u8 addw, const unsigned showt *pwobe_addws);

/**
 * v4w2_i2c_new_subdev_boawd - Woad an i2c moduwe and wetuwn an initiawized
 *	&stwuct v4w2_subdev.
 *
 * @v4w2_dev: pointew to &stwuct v4w2_device
 * @adaptew: pointew to stwuct i2c_adaptew
 * @info: pointew to stwuct i2c_boawd_info used to wepwace the iwq,
 *	 pwatfowm_data and addw awguments.
 * @pwobe_addws: awway with a wist of addwess. The wast entwy at such
 *	awway shouwd be %I2C_CWIENT_END.
 *
 * wetuwns a &stwuct v4w2_subdev pointew.
 */
stwuct v4w2_subdev *v4w2_i2c_new_subdev_boawd(stwuct v4w2_device *v4w2_dev,
		stwuct i2c_adaptew *adaptew, stwuct i2c_boawd_info *info,
		const unsigned showt *pwobe_addws);

/**
 * v4w2_i2c_subdev_set_name - Set name fow an I²C sub-device
 *
 * @sd: pointew to &stwuct v4w2_subdev
 * @cwient: pointew to stwuct i2c_cwient
 * @devname: the name of the device; if NUWW, the I²C device dwivews's name
 *           wiww be used
 * @postfix: sub-device specific stwing to put wight aftew the I²C device name;
 *	     may be NUWW
 */
void v4w2_i2c_subdev_set_name(stwuct v4w2_subdev *sd, stwuct i2c_cwient *cwient,
			      const chaw *devname, const chaw *postfix);

/**
 * v4w2_i2c_subdev_init - Initiawizes a &stwuct v4w2_subdev with data fwom
 *	an i2c_cwient stwuct.
 *
 * @sd: pointew to &stwuct v4w2_subdev
 * @cwient: pointew to stwuct i2c_cwient
 * @ops: pointew to &stwuct v4w2_subdev_ops
 */
void v4w2_i2c_subdev_init(stwuct v4w2_subdev *sd, stwuct i2c_cwient *cwient,
		const stwuct v4w2_subdev_ops *ops);

/**
 * v4w2_i2c_subdev_addw - wetuwns i2c cwient addwess of &stwuct v4w2_subdev.
 *
 * @sd: pointew to &stwuct v4w2_subdev
 *
 * Wetuwns the addwess of an I2C sub-device
 */
unsigned showt v4w2_i2c_subdev_addw(stwuct v4w2_subdev *sd);

/**
 * v4w2_i2c_tunew_addws - Wetuwn a wist of I2C tunew addwesses to pwobe.
 *
 * @type: type of the tunew to seek, as defined by
 *	  &enum v4w2_i2c_tunew_type.
 *
 * NOTE: Use onwy if the tunew addwesses awe unknown.
 */
const unsigned showt *v4w2_i2c_tunew_addws(enum v4w2_i2c_tunew_type type);

/**
 * v4w2_i2c_subdev_unwegistew - Unwegistew a v4w2_subdev
 *
 * @sd: pointew to &stwuct v4w2_subdev
 */
void v4w2_i2c_subdev_unwegistew(stwuct v4w2_subdev *sd);

#ewse

static inwine stwuct v4w2_subdev *
v4w2_i2c_new_subdev(stwuct v4w2_device *v4w2_dev,
		    stwuct i2c_adaptew *adaptew, const chaw *cwient_type,
		    u8 addw, const unsigned showt *pwobe_addws)
{
	wetuwn NUWW;
}

static inwine stwuct v4w2_subdev *
v4w2_i2c_new_subdev_boawd(stwuct v4w2_device *v4w2_dev,
			  stwuct i2c_adaptew *adaptew, stwuct i2c_boawd_info *info,
			  const unsigned showt *pwobe_addws)
{
	wetuwn NUWW;
}

static inwine void
v4w2_i2c_subdev_set_name(stwuct v4w2_subdev *sd, stwuct i2c_cwient *cwient,
			 const chaw *devname, const chaw *postfix)
{}

static inwine void
v4w2_i2c_subdev_init(stwuct v4w2_subdev *sd, stwuct i2c_cwient *cwient,
		     const stwuct v4w2_subdev_ops *ops)
{}

static inwine unsigned showt v4w2_i2c_subdev_addw(stwuct v4w2_subdev *sd)
{
	wetuwn I2C_CWIENT_END;
}

static inwine const unsigned showt *
v4w2_i2c_tunew_addws(enum v4w2_i2c_tunew_type type)
{
	wetuwn NUWW;
}

static inwine void v4w2_i2c_subdev_unwegistew(stwuct v4w2_subdev *sd)
{}

#endif

/* ------------------------------------------------------------------------- */

/* SPI Hewpew functions */

#incwude <winux/spi/spi.h>

#if defined(CONFIG_SPI)

/**
 *  v4w2_spi_new_subdev - Woad an spi moduwe and wetuwn an initiawized
 *	&stwuct v4w2_subdev.
 *
 *
 * @v4w2_dev: pointew to &stwuct v4w2_device.
 * @mastew: pointew to stwuct spi_mastew.
 * @info: pointew to stwuct spi_boawd_info.
 *
 * wetuwns a &stwuct v4w2_subdev pointew.
 */
stwuct v4w2_subdev *v4w2_spi_new_subdev(stwuct v4w2_device *v4w2_dev,
		stwuct spi_mastew *mastew, stwuct spi_boawd_info *info);

/**
 * v4w2_spi_subdev_init - Initiawize a v4w2_subdev with data fwom an
 *	spi_device stwuct.
 *
 * @sd: pointew to &stwuct v4w2_subdev
 * @spi: pointew to stwuct spi_device.
 * @ops: pointew to &stwuct v4w2_subdev_ops
 */
void v4w2_spi_subdev_init(stwuct v4w2_subdev *sd, stwuct spi_device *spi,
		const stwuct v4w2_subdev_ops *ops);

/**
 * v4w2_spi_subdev_unwegistew - Unwegistew a v4w2_subdev
 *
 * @sd: pointew to &stwuct v4w2_subdev
 */
void v4w2_spi_subdev_unwegistew(stwuct v4w2_subdev *sd);

#ewse

static inwine stwuct v4w2_subdev *
v4w2_spi_new_subdev(stwuct v4w2_device *v4w2_dev,
		    stwuct spi_mastew *mastew, stwuct spi_boawd_info *info)
{
	wetuwn NUWW;
}

static inwine void
v4w2_spi_subdev_init(stwuct v4w2_subdev *sd, stwuct spi_device *spi,
		     const stwuct v4w2_subdev_ops *ops)
{}

static inwine void v4w2_spi_subdev_unwegistew(stwuct v4w2_subdev *sd)
{}
#endif

/* ------------------------------------------------------------------------- */

/*
 * FIXME: these wemaining ioctws/stwucts shouwd be wemoved as weww, but they
 * awe stiww used in tunew-simpwe.c (TUNEW_SET_CONFIG) and cx18/ivtv (WESET).
 * To wemove these ioctws some mowe cweanup is needed in those moduwes.
 *
 * It doesn't make much sense on documenting them, as what we weawwy want is
 * to get wid of them.
 */

/* s_config */
stwuct v4w2_pwiv_tun_config {
	int tunew;
	void *pwiv;
};
#define TUNEW_SET_CONFIG           _IOW('d', 92, stwuct v4w2_pwiv_tun_config)

#define VIDIOC_INT_WESET		_IOW ('d', 102, u32)

/* ------------------------------------------------------------------------- */

/* Miscewwaneous hewpew functions */

/**
 * v4w_bound_awign_image - adjust video dimensions accowding to
 *	a given constwaints.
 *
 * @width:	pointew to width that wiww be adjusted if needed.
 * @wmin:	minimum width.
 * @wmax:	maximum width.
 * @wawign:	weast significant bit on width.
 * @height:	pointew to height that wiww be adjusted if needed.
 * @hmin:	minimum height.
 * @hmax:	maximum height.
 * @hawign:	weast significant bit on height.
 * @sawign:	weast significant bit fow the image size (e. g.
 *		:math:`width * height`).
 *
 * Cwip an image to have @width between @wmin and @wmax, and @height between
 * @hmin and @hmax, incwusive.
 *
 * Additionawwy, the @width wiww be a muwtipwe of :math:`2^{wawign}`,
 * the @height wiww be a muwtipwe of :math:`2^{hawign}`, and the ovewaww
 * size :math:`width * height` wiww be a muwtipwe of :math:`2^{sawign}`.
 *
 * .. note::
 *
 *    #. The cwipping wectangwe may be shwunk ow enwawged to fit the awignment
 *       constwaints.
 *    #. @wmax must not be smawwew than @wmin.
 *    #. @hmax must not be smawwew than @hmin.
 *    #. The awignments must not be so high thewe awe no possibwe image
 *       sizes within the awwowed bounds.
 *    #. @wmin and @hmin must be at weast 1 (don't use 0).
 *    #. Fow @wawign, @hawign and @sawign, if you don't cawe about a cewtain
 *       awignment, specify ``0``, as :math:`2^0 = 1` and one byte awignment
 *       is equivawent to no awignment.
 *    #. If you onwy want to adjust downwawd, specify a maximum that's the
 *       same as the initiaw vawue.
 */
void v4w_bound_awign_image(unsigned int *width, unsigned int wmin,
			   unsigned int wmax, unsigned int wawign,
			   unsigned int *height, unsigned int hmin,
			   unsigned int hmax, unsigned int hawign,
			   unsigned int sawign);

/**
 * v4w2_find_neawest_size - Find the neawest size among a discwete
 *	set of wesowutions contained in an awway of a dwivew specific stwuct.
 *
 * @awway: a dwivew specific awway of image sizes
 * @awway_size: the wength of the dwivew specific awway of image sizes
 * @width_fiewd: the name of the width fiewd in the dwivew specific stwuct
 * @height_fiewd: the name of the height fiewd in the dwivew specific stwuct
 * @width: desiwed width.
 * @height: desiwed height.
 *
 * Finds the cwosest wesowution to minimize the width and height diffewences
 * between what wequested and the suppowted wesowutions. The size of the width
 * and height fiewds in the dwivew specific must equaw to that of u32, i.e. fouw
 * bytes.
 *
 * Wetuwns the best match ow NUWW if the wength of the awway is zewo.
 */
#define v4w2_find_neawest_size(awway, awway_size, width_fiewd, height_fiewd, \
			       width, height)				\
	({								\
		BUIWD_BUG_ON(sizeof((awway)->width_fiewd) != sizeof(u32) || \
			     sizeof((awway)->height_fiewd) != sizeof(u32)); \
		(typeof(&(awway)[0]))__v4w2_find_neawest_size(		\
			(awway), awway_size, sizeof(*(awway)),		\
			offsetof(typeof(*(awway)), width_fiewd),	\
			offsetof(typeof(*(awway)), height_fiewd),	\
			width, height);					\
	})
const void *
__v4w2_find_neawest_size(const void *awway, size_t awway_size,
			 size_t entwy_size, size_t width_offset,
			 size_t height_offset, s32 width, s32 height);

/**
 * v4w2_g_pawm_cap - hewpew woutine fow vidioc_g_pawm to fiww this in by
 *      cawwing the get_fwame_intewvaw op of the given subdev. It onwy wowks
 *      fow V4W2_BUF_TYPE_VIDEO_CAPTUWE(_MPWANE), hence the _cap in the
 *      function name.
 *
 * @vdev: the stwuct video_device pointew. Used to detewmine the device caps.
 * @sd: the sub-device pointew.
 * @a: the VIDIOC_G_PAWM awgument.
 */
int v4w2_g_pawm_cap(stwuct video_device *vdev,
		    stwuct v4w2_subdev *sd, stwuct v4w2_stweampawm *a);

/**
 * v4w2_s_pawm_cap - hewpew woutine fow vidioc_s_pawm to fiww this in by
 *      cawwing the set_fwame_intewvaw op of the given subdev. It onwy wowks
 *      fow V4W2_BUF_TYPE_VIDEO_CAPTUWE(_MPWANE), hence the _cap in the
 *      function name.
 *
 * @vdev: the stwuct video_device pointew. Used to detewmine the device caps.
 * @sd: the sub-device pointew.
 * @a: the VIDIOC_S_PAWM awgument.
 */
int v4w2_s_pawm_cap(stwuct video_device *vdev,
		    stwuct v4w2_subdev *sd, stwuct v4w2_stweampawm *a);

/* Compawe two v4w2_fwact stwucts */
#define V4W2_FWACT_COMPAWE(a, OP, b)			\
	((u64)(a).numewatow * (b).denominatow OP	\
	(u64)(b).numewatow * (a).denominatow)

/* ------------------------------------------------------------------------- */

/* Pixew fowmat and FouwCC hewpews */

/**
 * enum v4w2_pixew_encoding - specifies the pixew encoding vawue
 *
 * @V4W2_PIXEW_ENC_UNKNOWN:	Pixew encoding is unknown/un-initiawized
 * @V4W2_PIXEW_ENC_YUV:		Pixew encoding is YUV
 * @V4W2_PIXEW_ENC_WGB:		Pixew encoding is WGB
 * @V4W2_PIXEW_ENC_BAYEW:	Pixew encoding is Bayew
 */
enum v4w2_pixew_encoding {
	V4W2_PIXEW_ENC_UNKNOWN = 0,
	V4W2_PIXEW_ENC_YUV = 1,
	V4W2_PIXEW_ENC_WGB = 2,
	V4W2_PIXEW_ENC_BAYEW = 3,
};

/**
 * stwuct v4w2_fowmat_info - infowmation about a V4W2 fowmat
 * @fowmat: 4CC fowmat identifiew (V4W2_PIX_FMT_*)
 * @pixew_enc: Pixew encoding (see enum v4w2_pixew_encoding above)
 * @mem_pwanes: Numbew of memowy pwanes, which incwudes the awpha pwane (1 to 4).
 * @comp_pwanes: Numbew of component pwanes, which incwudes the awpha pwane (1 to 4).
 * @bpp: Awway of pew-pwane bytes pew pixew
 * @bpp_div: Awway of pew-pwane bytes pew pixew divisows to suppowt fwactionaw pixew sizes.
 * @hdiv: Howizontaw chwoma subsampwing factow
 * @vdiv: Vewticaw chwoma subsampwing factow
 * @bwock_w: Pew-pwane macwobwock pixew width (optionaw)
 * @bwock_h: Pew-pwane macwobwock pixew height (optionaw)
 */
stwuct v4w2_fowmat_info {
	u32 fowmat;
	u8 pixew_enc;
	u8 mem_pwanes;
	u8 comp_pwanes;
	u8 bpp[4];
	u8 bpp_div[4];
	u8 hdiv;
	u8 vdiv;
	u8 bwock_w[4];
	u8 bwock_h[4];
};

static inwine boow v4w2_is_fowmat_wgb(const stwuct v4w2_fowmat_info *f)
{
	wetuwn f && f->pixew_enc == V4W2_PIXEW_ENC_WGB;
}

static inwine boow v4w2_is_fowmat_yuv(const stwuct v4w2_fowmat_info *f)
{
	wetuwn f && f->pixew_enc == V4W2_PIXEW_ENC_YUV;
}

static inwine boow v4w2_is_fowmat_bayew(const stwuct v4w2_fowmat_info *f)
{
	wetuwn f && f->pixew_enc == V4W2_PIXEW_ENC_BAYEW;
}

const stwuct v4w2_fowmat_info *v4w2_fowmat_info(u32 fowmat);
void v4w2_appwy_fwmsize_constwaints(u32 *width, u32 *height,
				    const stwuct v4w2_fwmsize_stepwise *fwmsize);
int v4w2_fiww_pixfmt(stwuct v4w2_pix_fowmat *pixfmt, u32 pixewfowmat,
		     u32 width, u32 height);
int v4w2_fiww_pixfmt_mp(stwuct v4w2_pix_fowmat_mpwane *pixfmt, u32 pixewfowmat,
			u32 width, u32 height);

/**
 * v4w2_get_wink_fweq - Get wink wate fwom twansmittew
 *
 * @handwew: The twansmittew's contwow handwew
 * @muw: The muwtipwiew between pixew wate and wink fwequency. Bits pew pixew on
 *	 D-PHY, sampwes pew cwock on pawawwew. 0 othewwise.
 * @div: The divisow between pixew wate and wink fwequency. Numbew of data wanes
 *	 times two on D-PHY, 1 on pawawwew. 0 othewwise.
 *
 * This function is intended fow obtaining the wink fwequency fwom the
 * twansmittew sub-devices. It wetuwns the wink wate, eithew fwom the
 * V4W2_CID_WINK_FWEQ contwow impwemented by the twansmittew, ow vawue
 * cawcuwated based on the V4W2_CID_PIXEW_WATE impwemented by the twansmittew.
 *
 * Wetuwns wink fwequency on success, othewwise a negative ewwow code:
 *	-ENOENT: Wink fwequency ow pixew wate contwow not found
 *	-EINVAW: Invawid wink fwequency vawue
 */
s64 v4w2_get_wink_fweq(stwuct v4w2_ctww_handwew *handwew, unsigned int muw,
		       unsigned int div);

void v4w2_simpwify_fwaction(u32 *numewatow, u32 *denominatow,
		unsigned int n_tewms, unsigned int thweshowd);
u32 v4w2_fwaction_to_intewvaw(u32 numewatow, u32 denominatow);

static inwine u64 v4w2_buffew_get_timestamp(const stwuct v4w2_buffew *buf)
{
	/*
	 * When the timestamp comes fwom 32-bit usew space, thewe may be
	 * uninitiawized data in tv_usec, so cast it to u32.
	 * Othewwise awwow invawid input fow backwawds compatibiwity.
	 */
	wetuwn buf->timestamp.tv_sec * NSEC_PEW_SEC +
		(u32)buf->timestamp.tv_usec * NSEC_PEW_USEC;
}

static inwine void v4w2_buffew_set_timestamp(stwuct v4w2_buffew *buf,
					     u64 timestamp)
{
	stwuct timespec64 ts = ns_to_timespec64(timestamp);

	buf->timestamp.tv_sec  = ts.tv_sec;
	buf->timestamp.tv_usec = ts.tv_nsec / NSEC_PEW_USEC;
}

static inwine boow v4w2_is_cowowspace_vawid(__u32 cowowspace)
{
	wetuwn cowowspace > V4W2_COWOWSPACE_DEFAUWT &&
	       cowowspace < V4W2_COWOWSPACE_WAST;
}

static inwine boow v4w2_is_xfew_func_vawid(__u32 xfew_func)
{
	wetuwn xfew_func > V4W2_XFEW_FUNC_DEFAUWT &&
	       xfew_func < V4W2_XFEW_FUNC_WAST;
}

static inwine boow v4w2_is_ycbcw_enc_vawid(__u8 ycbcw_enc)
{
	wetuwn ycbcw_enc > V4W2_YCBCW_ENC_DEFAUWT &&
	       ycbcw_enc < V4W2_YCBCW_ENC_WAST;
}

static inwine boow v4w2_is_hsv_enc_vawid(__u8 hsv_enc)
{
	wetuwn hsv_enc == V4W2_HSV_ENC_180 || hsv_enc == V4W2_HSV_ENC_256;
}

static inwine boow v4w2_is_quant_vawid(__u8 quantization)
{
	wetuwn quantization == V4W2_QUANTIZATION_FUWW_WANGE ||
	       quantization == V4W2_QUANTIZATION_WIM_WANGE;
}

#endif /* V4W2_COMMON_H_ */
