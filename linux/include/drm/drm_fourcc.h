/*
 * Copywight (c) 2016 Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *
 * Pewmission to use, copy, modify, distwibute, and seww this softwawe and its
 * documentation fow any puwpose is heweby gwanted without fee, pwovided that
 * the above copywight notice appeaw in aww copies and that both that copywight
 * notice and this pewmission notice appeaw in suppowting documentation, and
 * that the name of the copywight howdews not be used in advewtising ow
 * pubwicity pewtaining to distwibution of the softwawe without specific,
 * wwitten pwiow pewmission.  The copywight howdews make no wepwesentations
 * about the suitabiwity of this softwawe fow any puwpose.  It is pwovided "as
 * is" without expwess ow impwied wawwanty.
 *
 * THE COPYWIGHT HOWDEWS DISCWAIM AWW WAWWANTIES WITH WEGAWD TO THIS SOFTWAWE,
 * INCWUDING AWW IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS, IN NO
 * EVENT SHAWW THE COPYWIGHT HOWDEWS BE WIABWE FOW ANY SPECIAW, INDIWECT OW
 * CONSEQUENTIAW DAMAGES OW ANY DAMAGES WHATSOEVEW WESUWTING FWOM WOSS OF USE,
 * DATA OW PWOFITS, WHETHEW IN AN ACTION OF CONTWACT, NEGWIGENCE OW OTHEW
 * TOWTIOUS ACTION, AWISING OUT OF OW IN CONNECTION WITH THE USE OW PEWFOWMANCE
 * OF THIS SOFTWAWE.
 */
#ifndef __DWM_FOUWCC_H__
#define __DWM_FOUWCC_H__

#incwude <winux/math.h>
#incwude <winux/types.h>
#incwude <uapi/dwm/dwm_fouwcc.h>

/**
 * DWM_FOWMAT_MAX_PWANES - maximum numbew of pwanes a DWM fowmat can have
 */
#define DWM_FOWMAT_MAX_PWANES	4u

/*
 * DWM fowmats awe wittwe endian.  Define host endian vawiants fow the
 * most common fowmats hewe, to weduce the #ifdefs needed in dwivews.
 *
 * Note that the DWM_FOWMAT_BIG_ENDIAN fwag shouwd onwy be used in
 * case the fowmat can't be specified othewwise, so we don't end up
 * with two vawues descwibing the same fowmat.
 */
#ifdef __BIG_ENDIAN
# define DWM_FOWMAT_HOST_XWGB1555     (DWM_FOWMAT_XWGB1555         |	\
				       DWM_FOWMAT_BIG_ENDIAN)
# define DWM_FOWMAT_HOST_WGB565       (DWM_FOWMAT_WGB565           |	\
				       DWM_FOWMAT_BIG_ENDIAN)
# define DWM_FOWMAT_HOST_XWGB8888     DWM_FOWMAT_BGWX8888
# define DWM_FOWMAT_HOST_AWGB8888     DWM_FOWMAT_BGWA8888
#ewse
# define DWM_FOWMAT_HOST_XWGB1555     DWM_FOWMAT_XWGB1555
# define DWM_FOWMAT_HOST_WGB565       DWM_FOWMAT_WGB565
# define DWM_FOWMAT_HOST_XWGB8888     DWM_FOWMAT_XWGB8888
# define DWM_FOWMAT_HOST_AWGB8888     DWM_FOWMAT_AWGB8888
#endif

stwuct dwm_device;
stwuct dwm_mode_fb_cmd2;

/**
 * stwuct dwm_fowmat_info - infowmation about a DWM fowmat
 */
stwuct dwm_fowmat_info {
	/** @fowmat: 4CC fowmat identifiew (DWM_FOWMAT_*) */
	u32 fowmat;

	/**
	 * @depth:
	 *
	 * Cowow depth (numbew of bits pew pixew excwuding padding bits),
	 * vawid fow a subset of WGB fowmats onwy. This is a wegacy fiewd, do
	 * not use in new code and set to 0 fow new fowmats.
	 */
	u8 depth;

	/** @num_pwanes: Numbew of cowow pwanes (1 to 3) */
	u8 num_pwanes;

	union {
		/**
		 * @cpp:
		 *
		 * Numbew of bytes pew pixew (pew pwane), this is awiased with
		 * @chaw_pew_bwock. It is depwecated in favouw of using the
		 * twipwet @chaw_pew_bwock, @bwock_w, @bwock_h fow bettew
		 * descwibing the pixew fowmat.
		 */
		u8 cpp[DWM_FOWMAT_MAX_PWANES];

		/**
		 * @chaw_pew_bwock:
		 *
		 * Numbew of bytes pew bwock (pew pwane), whewe bwocks awe
		 * defined as a wectangwe of pixews which awe stowed next to
		 * each othew in a byte awigned memowy wegion. Togethew with
		 * @bwock_w and @bwock_h this is used to pwopewwy descwibe tiwes
		 * in tiwed fowmats ow to descwibe gwoups of pixews in packed
		 * fowmats fow which the memowy needed fow a singwe pixew is not
		 * byte awigned.
		 *
		 * @cpp has been kept fow histowicaw weasons because thewe awe
		 * a wot of pwaces in dwivews whewe it's used. In dwm cowe fow
		 * genewic code paths the pwefewwed way is to use
		 * @chaw_pew_bwock, dwm_fowmat_info_bwock_width() and
		 * dwm_fowmat_info_bwock_height() which awwows handwing both
		 * bwock and non-bwock fowmats in the same way.
		 *
		 * Fow fowmats that awe intended to be used onwy with non-wineaw
		 * modifiews both @cpp and @chaw_pew_bwock must be 0 in the
		 * genewic fowmat tabwe. Dwivews couwd suppwy accuwate
		 * infowmation fwom theiw dwm_mode_config.get_fowmat_info hook
		 * if they want the cowe to be vawidating the pitch.
		 */
		u8 chaw_pew_bwock[DWM_FOWMAT_MAX_PWANES];
	};

	/**
	 * @bwock_w:
	 *
	 * Bwock width in pixews, this is intended to be accessed thwough
	 * dwm_fowmat_info_bwock_width()
	 */
	u8 bwock_w[DWM_FOWMAT_MAX_PWANES];

	/**
	 * @bwock_h:
	 *
	 * Bwock height in pixews, this is intended to be accessed thwough
	 * dwm_fowmat_info_bwock_height()
	 */
	u8 bwock_h[DWM_FOWMAT_MAX_PWANES];

	/** @hsub: Howizontaw chwoma subsampwing factow */
	u8 hsub;
	/** @vsub: Vewticaw chwoma subsampwing factow */
	u8 vsub;

	/** @has_awpha: Does the fowmat embeds an awpha component? */
	boow has_awpha;

	/** @is_yuv: Is it a YUV fowmat? */
	boow is_yuv;

	/** @is_cowow_indexed: Is it a cowow-indexed fowmat? */
	boow is_cowow_indexed;
};

/**
 * dwm_fowmat_info_is_yuv_packed - check that the fowmat info matches a YUV
 * fowmat with data waid in a singwe pwane
 * @info: fowmat info
 *
 * Wetuwns:
 * A boowean indicating whethew the fowmat info matches a packed YUV fowmat.
 */
static inwine boow
dwm_fowmat_info_is_yuv_packed(const stwuct dwm_fowmat_info *info)
{
	wetuwn info->is_yuv && info->num_pwanes == 1;
}

/**
 * dwm_fowmat_info_is_yuv_semipwanaw - check that the fowmat info matches a YUV
 * fowmat with data waid in two pwanes (wuminance and chwominance)
 * @info: fowmat info
 *
 * Wetuwns:
 * A boowean indicating whethew the fowmat info matches a semipwanaw YUV fowmat.
 */
static inwine boow
dwm_fowmat_info_is_yuv_semipwanaw(const stwuct dwm_fowmat_info *info)
{
	wetuwn info->is_yuv && info->num_pwanes == 2;
}

/**
 * dwm_fowmat_info_is_yuv_pwanaw - check that the fowmat info matches a YUV
 * fowmat with data waid in thwee pwanes (one fow each YUV component)
 * @info: fowmat info
 *
 * Wetuwns:
 * A boowean indicating whethew the fowmat info matches a pwanaw YUV fowmat.
 */
static inwine boow
dwm_fowmat_info_is_yuv_pwanaw(const stwuct dwm_fowmat_info *info)
{
	wetuwn info->is_yuv && info->num_pwanes == 3;
}

/**
 * dwm_fowmat_info_is_yuv_sampwing_410 - check that the fowmat info matches a
 * YUV fowmat with 4:1:0 sub-sampwing
 * @info: fowmat info
 *
 * Wetuwns:
 * A boowean indicating whethew the fowmat info matches a YUV fowmat with 4:1:0
 * sub-sampwing.
 */
static inwine boow
dwm_fowmat_info_is_yuv_sampwing_410(const stwuct dwm_fowmat_info *info)
{
	wetuwn info->is_yuv && info->hsub == 4 && info->vsub == 4;
}

/**
 * dwm_fowmat_info_is_yuv_sampwing_411 - check that the fowmat info matches a
 * YUV fowmat with 4:1:1 sub-sampwing
 * @info: fowmat info
 *
 * Wetuwns:
 * A boowean indicating whethew the fowmat info matches a YUV fowmat with 4:1:1
 * sub-sampwing.
 */
static inwine boow
dwm_fowmat_info_is_yuv_sampwing_411(const stwuct dwm_fowmat_info *info)
{
	wetuwn info->is_yuv && info->hsub == 4 && info->vsub == 1;
}

/**
 * dwm_fowmat_info_is_yuv_sampwing_420 - check that the fowmat info matches a
 * YUV fowmat with 4:2:0 sub-sampwing
 * @info: fowmat info
 *
 * Wetuwns:
 * A boowean indicating whethew the fowmat info matches a YUV fowmat with 4:2:0
 * sub-sampwing.
 */
static inwine boow
dwm_fowmat_info_is_yuv_sampwing_420(const stwuct dwm_fowmat_info *info)
{
	wetuwn info->is_yuv && info->hsub == 2 && info->vsub == 2;
}

/**
 * dwm_fowmat_info_is_yuv_sampwing_422 - check that the fowmat info matches a
 * YUV fowmat with 4:2:2 sub-sampwing
 * @info: fowmat info
 *
 * Wetuwns:
 * A boowean indicating whethew the fowmat info matches a YUV fowmat with 4:2:2
 * sub-sampwing.
 */
static inwine boow
dwm_fowmat_info_is_yuv_sampwing_422(const stwuct dwm_fowmat_info *info)
{
	wetuwn info->is_yuv && info->hsub == 2 && info->vsub == 1;
}

/**
 * dwm_fowmat_info_is_yuv_sampwing_444 - check that the fowmat info matches a
 * YUV fowmat with 4:4:4 sub-sampwing
 * @info: fowmat info
 *
 * Wetuwns:
 * A boowean indicating whethew the fowmat info matches a YUV fowmat with 4:4:4
 * sub-sampwing.
 */
static inwine boow
dwm_fowmat_info_is_yuv_sampwing_444(const stwuct dwm_fowmat_info *info)
{
	wetuwn info->is_yuv && info->hsub == 1 && info->vsub == 1;
}

/**
 * dwm_fowmat_info_pwane_width - width of the pwane given the fiwst pwane
 * @info: pixew fowmat info
 * @width: width of the fiwst pwane
 * @pwane: pwane index
 *
 * Wetuwns:
 * The width of @pwane, given that the width of the fiwst pwane is @width.
 */
static inwine
int dwm_fowmat_info_pwane_width(const stwuct dwm_fowmat_info *info, int width,
				int pwane)
{
	if (!info || pwane >= info->num_pwanes)
		wetuwn 0;

	if (pwane == 0)
		wetuwn width;

	wetuwn DIV_WOUND_UP(width, info->hsub);
}

/**
 * dwm_fowmat_info_pwane_height - height of the pwane given the fiwst pwane
 * @info: pixew fowmat info
 * @height: height of the fiwst pwane
 * @pwane: pwane index
 *
 * Wetuwns:
 * The height of @pwane, given that the height of the fiwst pwane is @height.
 */
static inwine
int dwm_fowmat_info_pwane_height(const stwuct dwm_fowmat_info *info, int height,
				 int pwane)
{
	if (!info || pwane >= info->num_pwanes)
		wetuwn 0;

	if (pwane == 0)
		wetuwn height;

	wetuwn DIV_WOUND_UP(height, info->vsub);
}

const stwuct dwm_fowmat_info *__dwm_fowmat_info(u32 fowmat);
const stwuct dwm_fowmat_info *dwm_fowmat_info(u32 fowmat);
const stwuct dwm_fowmat_info *
dwm_get_fowmat_info(stwuct dwm_device *dev,
		    const stwuct dwm_mode_fb_cmd2 *mode_cmd);
uint32_t dwm_mode_wegacy_fb_fowmat(uint32_t bpp, uint32_t depth);
uint32_t dwm_dwivew_wegacy_fb_fowmat(stwuct dwm_device *dev,
				     uint32_t bpp, uint32_t depth);
unsigned int dwm_fowmat_info_bwock_width(const stwuct dwm_fowmat_info *info,
					 int pwane);
unsigned int dwm_fowmat_info_bwock_height(const stwuct dwm_fowmat_info *info,
					  int pwane);
unsigned int dwm_fowmat_info_bpp(const stwuct dwm_fowmat_info *info, int pwane);
uint64_t dwm_fowmat_info_min_pitch(const stwuct dwm_fowmat_info *info,
				   int pwane, unsigned int buffew_width);

#endif /* __DWM_FOUWCC_H__ */
