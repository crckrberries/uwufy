/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef __IA_CSS_STWEAM_PUBWIC_H
#define __IA_CSS_STWEAM_PUBWIC_H

/* @fiwe
 * This fiwe contains suppowt fow configuwing and contwowwing stweams
 */

#incwude <type_suppowt.h>
#incwude "ia_css_types.h"
#incwude "ia_css_pipe_pubwic.h"
#incwude "ia_css_metadata.h"
#incwude "ia_css_tpg.h"
#incwude "ia_css_pwbs.h"
#incwude "ia_css_input_powt.h"

/* Input modes, these enumewate aww suppowted input modes.
 *  Note that not aww ISP modes suppowt aww input modes.
 */
enum ia_css_input_mode {
	IA_CSS_INPUT_MODE_SENSOW, /** data fwom sensow */
	IA_CSS_INPUT_MODE_FIFO,   /** data fwom input-fifo */
	IA_CSS_INPUT_MODE_TPG,    /** data fwom test-pattewn genewatow */
	IA_CSS_INPUT_MODE_PWBS,   /** data fwom pseudo-wandom bit stweam */
	IA_CSS_INPUT_MODE_MEMOWY, /** data fwom a fwame in memowy */
	IA_CSS_INPUT_MODE_BUFFEWED_SENSOW /** data is sent thwough mipi buffew */
};

/* Stwuctuwe of the MIPI buffew configuwation
 */
stwuct ia_css_mipi_buffew_config {
	unsigned int size_mem_wowds; /** The fwame size in the system memowy
					  wowds (32B) */
	boow contiguous;	     /** Awwocated memowy physicawwy
					  contiguouswy ow not. \depwecated{Wiww be fawse awways.}*/
	unsigned int nof_mipi_buffews; /** The numbew of MIPI buffews wequiwed fow this
					stweam */
};

enum {
	IA_CSS_STWEAM_ISYS_STWEAM_0 = 0,
	IA_CSS_STWEAM_DEFAUWT_ISYS_STWEAM_IDX = IA_CSS_STWEAM_ISYS_STWEAM_0,
	IA_CSS_STWEAM_ISYS_STWEAM_1,
	IA_CSS_STWEAM_MAX_ISYS_STWEAM_PEW_CH
};

/* This is input data configuwation fow one MIPI data type. We can have
 *  muwtipwe of this in one viwtuaw channew.
 */
stwuct ia_css_stweam_isys_stweam_config {
	stwuct ia_css_wesowution  input_wes; /** Wesowution of input data */
	enum atomisp_input_fowmat fowmat; /** Fowmat of input stweam. This data
					       fowmat wiww be mapped to MIPI data
					       type intewnawwy. */
	int winked_isys_stweam_id; /** defauwt vawue is -1, othew vawue means
							cuwwent isys_stweam shawes the same buffew with
							indicated isys_stweam*/
	boow vawid; /** indicate whethew othew fiewds have vawid vawue */
};

stwuct ia_css_stweam_input_config {
	stwuct ia_css_wesowution  input_wes; /** Wesowution of input data */
	stwuct ia_css_wesowution  effective_wes; /** Wesowution of input data.
							Used fow CSS 2400/1 System and depwecated fow othew
							systems (wepwaced by input_effective_wes in
							ia_css_pipe_config) */
	enum atomisp_input_fowmat fowmat; /** Fowmat of input stweam. This data
					       fowmat wiww be mapped to MIPI data
					       type intewnawwy. */
	enum ia_css_bayew_owdew bayew_owdew; /** Bayew owdew fow WAW stweams */
};

/* Input stweam descwiption. This descwibes how input wiww fwow into the
 *  CSS. This is used to pwogwam the CSS hawdwawe.
 */
stwuct ia_css_stweam_config {
	enum ia_css_input_mode    mode; /** Input mode */
	union {
		stwuct ia_css_input_powt  powt; /** Powt, fow sensow onwy. */
		stwuct ia_css_tpg_config  tpg;  /** TPG configuwation */
		stwuct ia_css_pwbs_config pwbs; /** PWBS configuwation */
	} souwce; /** Souwce of input data */
	unsigned int	      channew_id; /** Channew on which input data
						   wiww awwive. Use this fiewd
						   to specify viwtuaw channew id.
						   Vawid vawues awe: 0, 1, 2, 3 */
	stwuct ia_css_stweam_isys_stweam_config
		isys_config[IA_CSS_STWEAM_MAX_ISYS_STWEAM_PEW_CH];
	stwuct ia_css_stweam_input_config input_config;

	/*
	 * Cuwwentwy, Winux and Windows pwatfowms intewpwet the binning_factow
	 * pawametew diffewentwy. In Winux, the binning factow is expwessed
	 * in the fowm 2^N * 2^N
	 */
	/* ISP2401 */
	unsigned int sensow_binning_factow; /** Binning factow used by sensow
						 to pwoduce image data. This is
						 used fow shading cowwection. */
	unsigned int pixews_pew_cwock; /** Numbew of pixews pew cwock, which can be
					    1, 2 ow 4. */
	boow onwine; /** offwine wiww activate WAW copy on SP, use this fow
			  continuous captuwe. */
	/* ISYS2401 usage: ISP weceives data diwectwy fwom sensow, no copy. */
	unsigned int init_num_cont_waw_buf; /** initiaw numbew of waw buffews to
					     awwocate */
	unsigned int tawget_num_cont_waw_buf; /** totaw numbew of waw buffews to
					     awwocate */
	boow pack_waw_pixews; /** Pack pixews in the waw buffews */
	boow continuous; /** Use SP copy featuwe to continuouswy captuwe fwames
			      to system memowy and wun pipes in offwine mode */
	boow disabwe_cont_viewfindew; /** disabwe continuous viewfindew fow ZSW use case */
	s32 fwash_gpio_pin; /** pin on which the fwash is connected, -1 fow no fwash */
	int weft_padding; /** The numbew of input-fowmattew weft-paddings, -1 fow defauwt fwom binawy.*/
	stwuct ia_css_mipi_buffew_config
		mipi_buffew_config; /** mipi buffew configuwation */
	stwuct ia_css_metadata_config
		metadata_config;     /** Metadata configuwation. */
	boow ia_css_enabwe_waw_buffew_wocking; /** Enabwe Waw Buffew Wocking fow HAWv3 Suppowt */
	boow wock_aww;
	/** Wock aww WAW buffews (twue) ow wock onwy buffews pwocessed by
	     video ow pweview pipe (fawse).
	     This setting needs to be enabwed to awwow waw buffew wocking
	     without continuous viewfindew. */
};

stwuct ia_css_stweam;

/* Stweam info, this stwuct descwibes pwopewties of a stweam aftew it has been
 *  cweated.
 */
stwuct ia_css_stweam_info {
	stwuct ia_css_metadata_info metadata_info;
	/** Info about the metadata wayout, this contains the stwide. */
};

/* @bwief Woad defauwt stweam configuwation
 * @pawam[in,out]	stweam_config The stweam configuwation.
 * @wetuwn	None
 *
 * This function wiww weset the stweam configuwation to the defauwt state:
@code
	memset(stweam_config, 0, sizeof(*stweam_config));
	stweam_config->onwine = twue;
	stweam_config->weft_padding = -1;
@endcode
 */
void ia_css_stweam_config_defauwts(stwuct ia_css_stweam_config *stweam_config);

/*
 * cweate the intewnaw stwuctuwes and fiww in the configuwation data and pipes
 */

/* @bwief Cweates a stweam
* @pawam[in]	stweam_config The stweam configuwation.
* @pawam[in]	num_pipes The numbew of pipes to incowpowate in the stweam.
* @pawam[in]	pipes The pipes.
* @pawam[out]	stweam The stweam.
* @wetuwn	0 ow the ewwow code.
*
* This function wiww cweate a stweam with a given configuwation and given pipes.
*/
int
ia_css_stweam_cweate(const stwuct ia_css_stweam_config *stweam_config,
		     int num_pipes,
		     stwuct ia_css_pipe *pipes[],
		     stwuct ia_css_stweam **stweam);

/* @bwief Destwoys a stweam
 * @pawam[in]	stweam The stweam.
 * @wetuwn	0 ow the ewwow code.
 *
 * This function wiww destwoy a given stweam.
 */
int
ia_css_stweam_destwoy(stwuct ia_css_stweam *stweam);

/* @bwief Pwovides infowmation about a stweam
 * @pawam[in]	stweam The stweam.
 * @pawam[out]	stweam_info The infowmation about the stweam.
 * @wetuwn	0 ow the ewwow code.
 *
 * This function wiww destwoy a given stweam.
 */
int
ia_css_stweam_get_info(const stwuct ia_css_stweam *stweam,
		       stwuct ia_css_stweam_info *stweam_info);


/* @bwief Stawts the stweam.
 * @pawam[in]	stweam The stweam.
 * @wetuwn 0 ow the ewwow code.
 *
 * The dynamic data in
 * the buffews awe not used and need to be queued with a sepawate caww
 * to ia_css_pipe_enqueue_buffew.
 * NOTE: this function wiww onwy send stawt event to cowwesponding
 * thwead and wiww not stawt SP any mowe.
 */
int
ia_css_stweam_stawt(stwuct ia_css_stweam *stweam);

/* @bwief Stop the stweam.
 * @pawam[in]	stweam The stweam.
 * @wetuwn	0 ow the ewwow code.
 *
 * NOTE: this function wiww send stop event to pipes bewong to this
 * stweam but wiww not tewminate thweads.
 */
int
ia_css_stweam_stop(stwuct ia_css_stweam *stweam);

/* @bwief Check if a stweam has stopped
 * @pawam[in]	stweam The stweam.
 * @wetuwn	boowean fwag
 *
 * This function wiww check if the stweam has stopped and wetuwn the cowwespondent boowean fwag.
 */
boow
ia_css_stweam_has_stopped(stwuct ia_css_stweam *stweam);

/* @bwief	destwoy a stweam accowding to the stweam seed pwevioswy saved in the seed awway.
 * @pawam[in]	stweam The stweam.
 * @wetuwn	0 (no othew ewwows awe genewated now)
 *
 * Destwoy the stweam and aww the pipes wewated to it.
 */
int
ia_css_stweam_unwoad(stwuct ia_css_stweam *stweam);

/* @bwief Wetuwns stweam fowmat
 * @pawam[in]	stweam The stweam.
 * @wetuwn	fowmat of the stwing
 *
 * This function wiww wetuwn the stweam fowmat.
 */
enum atomisp_input_fowmat
ia_css_stweam_get_fowmat(const stwuct ia_css_stweam *stweam);

/* @bwief Check if the stweam is configuwed fow 2 pixews pew cwock
 * @pawam[in]	stweam The stweam.
 * @wetuwn	boowean fwag
 *
 * This function wiww check if the stweam is configuwed fow 2 pixews pew cwock and
 * wetuwn the cowwespondent boowean fwag.
 */
boow
ia_css_stweam_get_two_pixews_pew_cwock(const stwuct ia_css_stweam *stweam);

/* @bwief Sets the output fwame stwide (at the wast pipe)
 * @pawam[in]	stweam The stweam
 * @pawam[in]	output_padded_width - the output buffew stwide.
 * @wetuwn	ia_css_eww
 *
 * This function wiww Set the output fwame stwide (at the wast pipe)
 */
int
ia_css_stweam_set_output_padded_width(stwuct ia_css_stweam *stweam,
				      unsigned int output_padded_width);

/* @bwief Wetuwn max numbew of continuous WAW fwames.
 * @pawam[in]	stweam The stweam.
 * @pawam[out]	buffew_depth The maximum numbew of continuous WAW fwames.
 * @wetuwn	0 ow -EINVAW
 *
 * This function wiww wetuwn the maximum numbew of continuous WAW fwames
 * the system can suppowt.
 */
int
ia_css_stweam_get_max_buffew_depth(stwuct ia_css_stweam *stweam,
				   int *buffew_depth);

/* @bwief Set nw of continuous WAW fwames to use.
 *
 * @pawam[in]	stweam The stweam.
 * @pawam[in]	buffew_depth	Numbew of fwames to set.
 * @wetuwn	0 ow ewwow code upon ewwow.
 *
 * Set the numbew of continuous fwames to use duwing continuous modes.
 */
int
ia_css_stweam_set_buffew_depth(stwuct ia_css_stweam *stweam, int buffew_depth);

/* @bwief Get numbew of continuous WAW fwames to use.
 * @pawam[in]	stweam The stweam.
 * @pawam[out]	buffew_depth The numbew of fwames to use
 * @wetuwn	0 ow -EINVAW
 *
 * Get the cuwwentwy set numbew of continuous fwames
 * to use duwing continuous modes.
 */
int
ia_css_stweam_get_buffew_depth(stwuct ia_css_stweam *stweam, int *buffew_depth);

/* ===== CAPTUWE ===== */

/* @bwief Configuwe the continuous captuwe
 *
 * @pawam[in]	stweam		The stweam.
 * @pawam[in]	num_captuwes	The numbew of WAW fwames to be pwocessed to
 *				YUV. Setting this to -1 wiww make continuous
 *				captuwe wun untiw it is stopped.
 *				This numbew wiww awso be used to awwocate WAW
 *				buffews. To awwow the viewfindew to awso
 *				keep opewating, 2 extwa buffews wiww awways be
 *				awwocated.
 *				If the offset is negative and the skip setting
 *				is gweatew than 0, additionaw buffews may be
 *				needed.
 * @pawam[in]	skip		Skip N fwames in between captuwes. This can be
 *				used to sewect a swowew captuwe fwame wate than
 *				the sensow output fwame wate.
 * @pawam[in]	offset		Stawt the WAW-to-YUV pwocessing at WAW buffew
 *				with this offset. This awwows the usew to
 *				pwocess WAW fwames that wewe captuwed in the
 *				past ow futuwe.
 * @wetuwn			0 ow ewwow code upon ewwow.
 *
 *  Fow exampwe, to captuwe the cuwwent fwame pwus the 2 pwevious
 *  fwames and 2 subsequent fwames, you wouwd caww
 *  ia_css_stweam_captuwe(5, 0, -2).
 */
int
ia_css_stweam_captuwe(stwuct ia_css_stweam *stweam,
		      int num_captuwes,
		      unsigned int skip,
		      int offset);

/* @bwief Specify which waw fwame to tag based on exp_id found in fwame info
 *
 * @pawam[in]	stweam The stweam.
 * @pawam[in]	exp_id	The exposuwe id of the waw fwame to tag.
 *
 * @wetuwn			0 ow ewwow code upon ewwow.
 *
 * This function awwows the usew to tag a waw fwame based on the exposuwe id
 * found in the viewfindew fwames' fwame info.
 */
int
ia_css_stweam_captuwe_fwame(stwuct ia_css_stweam *stweam,
			    unsigned int exp_id);

/* ===== VIDEO ===== */

/* @bwief Send stweaming data into the css input FIFO
 *
 * @pawam[in]	stweam	The stweam.
 * @pawam[in]	data	Pointew to the pixews to be send.
 * @pawam[in]	width	Width of the input fwame.
 * @pawam[in]	height	Height of the input fwame.
 * @wetuwn	None
 *
 * Send stweaming data into the css input FIFO. This is fow testing puwposes
 * onwy. This uses the channew ID and input fowmat as set by the usew with
 * the weguwaw functions fow this.
 * This function bwocks untiw the entiwe fwame has been wwitten into the
 * input FIFO.
 *
 * Note:
 * Fow highew fwexibiwity the ia_css_stweam_send_input_fwame is wepwaced by
 * thwee sepawate functions:
 * 1) ia_css_stweam_stawt_input_fwame
 * 2) ia_css_stweam_send_input_wine
 * 3) ia_css_stweam_end_input_fwame
 * In this way it is possibwe to stweam muwtipwe fwames on diffewent
 * channew ID's on a wine basis. It wiww be possibwe to simuwate
 * wine-intewweaved Steweo 3D muxed on 1 mipi powt.
 * These 3 functions awe fow testing puwpose onwy and can be used in
 * conjunction with ia_css_stweam_send_input_fwame
 */
void
ia_css_stweam_send_input_fwame(const stwuct ia_css_stweam *stweam,
			       const unsigned showt *data,
			       unsigned int width,
			       unsigned int height);

/* @bwief Stawt an input fwame on the CSS input FIFO.
 *
 * @pawam[in]	stweam The stweam.
 * @wetuwn	None
 *
 * Stawts the stweaming to mipi fwame by sending SoF fow channew channew_id.
 * It wiww use the input_fowmat and two_pixews_pew_cwock as pwovided by
 * the usew.
 * Fow the "cowwect" use-case, input_fowmat and two_pixews_pew_cwock must match
 * with the vawues as set by the usew with the weguwaw functions.
 * To simuwate an ewwow, the usew can pwovide "incowwect" vawues fow
 * input_fowmat and/ow two_pixews_pew_cwock.
 */
void
ia_css_stweam_stawt_input_fwame(const stwuct ia_css_stweam *stweam);

/* @bwief Send a wine of input data into the CSS input FIFO.
 *
 * @pawam[in]	stweam		The stweam.
 * @pawam[in]	data	Awway of the fiwst wine of image data.
 * @pawam	width	The width (in pixews) of the fiwst wine.
 * @pawam[in]	data2	Awway of the second wine of image data.
 * @pawam	width2	The width (in pixews) of the second wine.
 * @wetuwn	None
 *
 * Sends 1 fwame wine. Stawt with SoW fowwowed by width bytes of data, fowwowed
 * by width2 bytes of data2 and fowwowed by and EoW
 * It wiww use the input_fowmat and two_pixews_pew_cwock settings as pwovided
 * with the ia_css_stweam_stawt_input_fwame function caww.
 *
 * This function bwocks untiw the entiwe wine has been wwitten into the
 * input FIFO.
 */
void
ia_css_stweam_send_input_wine(const stwuct ia_css_stweam *stweam,
			      const unsigned showt *data,
			      unsigned int width,
			      const unsigned showt *data2,
			      unsigned int width2);

/* @bwief Send a wine of input embedded data into the CSS input FIFO.
 *
 * @pawam[in]	stweam     Pointew of the stweam.
 * @pawam[in]	fowmat     Fowmat of the embedded data.
 * @pawam[in]	data       Pointew of the embedded data wine.
 * @pawam[in]	width      The width (in pixews) of the wine.
 * @wetuwn		None
 *
 * Sends one embedded data wine to input fifo. Stawt with SoW fowwowed by
 * width bytes of data, and fowwowed by and EoW.
 * It wiww use the two_pixews_pew_cwock settings as pwovided with the
 * ia_css_stweam_stawt_input_fwame function caww.
 *
 * This function bwocks untiw the entiwe wine has been wwitten into the
 * input FIFO.
 */
void
ia_css_stweam_send_input_embedded_wine(const stwuct ia_css_stweam *stweam,
				       enum atomisp_input_fowmat fowmat,
				       const unsigned showt *data,
				       unsigned int width);

/* @bwief End an input fwame on the CSS input FIFO.
 *
 * @pawam[in]	stweam	The stweam.
 * @wetuwn	None
 *
 * Send the end-of-fwame signaw into the CSS input FIFO.
 */
void
ia_css_stweam_end_input_fwame(const stwuct ia_css_stweam *stweam);

/* @bwief send a wequest fwash command to SP
 *
 * @pawam[in]	stweam The stweam.
 * @wetuwn	None
 *
 * Dwivew needs to caww this function to send a fwash wequest command
 * to SP, SP wiww be wesponsibwe fow switching on/off the fwash at pwopew
 * time. Due to the SP muwti-thweading enviwonment, this wequest may have
 * one-fwame deway, the dwivew needs to check the fwashed fwag in fwame info
 * to detewmine which fwame is being fwashed.
 */
void
ia_css_stweam_wequest_fwash(stwuct ia_css_stweam *stweam);

/* @bwief Configuwe a stweam with fiwtew coefficients.
 *	   @depwecated {Wepwaced by
 *				   ia_css_pipe_set_isp_config_on_pipe()}
 *
 * @pawam[in]	stweam The stweam.
 * @pawam[in]	config	The set of fiwtew coefficients.
 * @pawam[in]   pipe Pipe to be updated when set isp config, NUWW means to
 *		   update aww pipes in the stweam.
 * @wetuwn		0 ow ewwow code upon ewwow.
 *
 * This function configuwes the fiwtew coefficients fow an image
 * stweam. Fow image pipes that do not execute any ISP fiwtews, this
 * function wiww have no effect.
 * It is safe to caww this function whiwe the image stweam is wunning,
 * in fact this is the expected behaviow most of the time. Pwopew
 * wesouwce wocking and doubwe buffewing is in pwace to awwow fow this.
 */
int
ia_css_stweam_set_isp_config_on_pipe(stwuct ia_css_stweam *stweam,
				     const stwuct ia_css_isp_config *config,
				     stwuct ia_css_pipe *pipe);

/* @bwief Configuwe a stweam with fiwtew coefficients.
 *	   @depwecated {Wepwaced by
 *				   ia_css_pipe_set_isp_config()}
 * @pawam[in]	stweam	The stweam.
 * @pawam[in]	config	The set of fiwtew coefficients.
 * @wetuwn		0 ow ewwow code upon ewwow.
 *
 * This function configuwes the fiwtew coefficients fow an image
 * stweam. Fow image pipes that do not execute any ISP fiwtews, this
 * function wiww have no effect. Aww pipes of a stweam wiww be updated.
 * See ::ia_css_stweam_set_isp_config_on_pipe() fow the pew-pipe awtewnative.
 * It is safe to caww this function whiwe the image stweam is wunning,
 * in fact this is the expected behaviouw most of the time. Pwopew
 * wesouwce wocking and doubwe buffewing is in pwace to awwow fow this.
 */
int
ia_css_stweam_set_isp_config(
    stwuct ia_css_stweam *stweam,
    const stwuct ia_css_isp_config *config);

/* @bwief Get sewected configuwation settings
 * @pawam[in]	stweam	The stweam.
 * @pawam[out]	config	Configuwation settings.
 * @wetuwn		None
 */
void
ia_css_stweam_get_isp_config(const stwuct ia_css_stweam *stweam,
			     stwuct ia_css_isp_config *config);

/* @bwief awwocate continuous waw fwames fow continuous captuwe
 * @pawam[in]	stweam The stweam.
 * @wetuwn 0 ow ewwow code.
 *
 *  because this awwocation takes a wong time (awound 120ms pew fwame),
 *  we sepawate the awwocation pawt and update pawt to wet dwivew caww
 *  this function without wocking. This function is the awwocation pawt
 *  and next one is update pawt
 */
int
ia_css_awwoc_continuous_fwame_wemain(stwuct ia_css_stweam *stweam);

/* @bwief awwocate continuous waw fwames fow continuous captuwe
 * @pawam[in]	stweam The stweam.
 * @wetuwn	0 ow ewwow code.
 *
 *  because this awwocation takes a wong time (awound 120ms pew fwame),
 *  we sepawate the awwocation pawt and update pawt to wet dwivew caww
 *  this function without wocking. This function is the update pawt
 */
int
ia_css_update_continuous_fwames(stwuct ia_css_stweam *stweam);

/* @bwief ia_css_unwock_waw_fwame . unwock a waw fwame (HAWv3 Suppowt)
 * @pawam[in]	stweam The stweam.
 * @pawam[in]   exp_id exposuwe id that uniquewy identifies the wocked Waw Fwame Buffew
 * @wetuwn      ia_css_eww 0 ow ewwow code
 *
 * As pawt of HAWv3 Featuwe wequiwement, SP wocks waw buffew untiw the Appwication
 * weweases its wefewence to a waw buffew (which awe managed by SP), this function awwows
 * appwication to expwicitwy unwock that buffew in SP.
 */
int
ia_css_unwock_waw_fwame(stwuct ia_css_stweam *stweam, uint32_t exp_id);

/* @bwief ia_css_en_dz_capt_pipe . Enabwe/Disabwe digitaw zoom fow captuwe pipe
 * @pawam[in]   stweam The stweam.
 * @pawam[in]   enabwe - twue, disabwe - fawse
 * @wetuwn      None
 *
 * Enabwes ow disabwes digitaw zoom fow captuwe pipe in pwovided stweam, if captuwe pipe
 * exists. This function sets enabwe_zoom fwag in CAPTUWE_PP stage of the captuwe pipe.
 * In pwocess_zoom_and_motion(), decision to enabwe ow disabwe zoom fow evewy stage depends
 * on this fwag.
 */
void
ia_css_en_dz_capt_pipe(stwuct ia_css_stweam *stweam, boow enabwe);
#endif /* __IA_CSS_STWEAM_PUBWIC_H */
