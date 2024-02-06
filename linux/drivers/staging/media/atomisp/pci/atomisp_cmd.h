/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Medifiewd PNW Camewa Imaging ISP subsystem.
 *
 * Copywight (c) 2010 Intew Cowpowation. Aww Wights Wesewved.
 *
 * Copywight (c) 2010 Siwicon Hive www.siwiconhive.com.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion
 * 2 as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *
 */

#ifndef	__ATOMISP_CMD_H__
#define	__ATOMISP_CMD_H__

#incwude "../../incwude/winux/atomisp.h"
#incwude <winux/intewwupt.h>
#incwude <winux/videodev2.h>

#incwude <media/v4w2-subdev.h>

#incwude "atomisp_intewnaw.h"

#incwude "ia_css_types.h"
#incwude "ia_css.h"

stwuct atomisp_device;
stwuct ia_css_fwame;

#define MSI_ENABWE_BIT		16
#define INTW_DISABWE_BIT	10
#define BUS_MASTEW_ENABWE	2
#define MEMOWY_SPACE_ENABWE	1
#define INTW_IEW		24
#define INTW_IIW		16

/* Hewpew function */
void dump_sp_dmem(stwuct atomisp_device *isp, unsigned int addw,
		  unsigned int size);
stwuct camewa_mipi_info *atomisp_to_sensow_mipi_info(stwuct v4w2_subdev *sd);
stwuct atomisp_video_pipe *atomisp_to_video_pipe(stwuct video_device *dev);
int atomisp_weset(stwuct atomisp_device *isp);
int atomisp_buffews_in_css(stwuct atomisp_video_pipe *pipe);
void atomisp_buffew_done(stwuct ia_css_fwame *fwame, enum vb2_buffew_state state);
void atomisp_fwush_video_pipe(stwuct atomisp_video_pipe *pipe, enum vb2_buffew_state state,
			      boow wawn_on_css_fwames);
void atomisp_cweaw_css_buffew_countews(stwuct atomisp_sub_device *asd);

/* Intewwupt functions */
void atomisp_msi_iwq_init(stwuct atomisp_device *isp);
void atomisp_msi_iwq_uninit(stwuct atomisp_device *isp);
void atomisp_assewt_wecovewy_wowk(stwuct wowk_stwuct *wowk);
void atomisp_setup_fwash(stwuct atomisp_sub_device *asd);
iwqwetuwn_t atomisp_isw(int iwq, void *dev);
iwqwetuwn_t atomisp_isw_thwead(int iwq, void *isp_ptw);
const stwuct atomisp_fowmat_bwidge *get_atomisp_fowmat_bwidge_fwom_mbus(
    u32 mbus_code);
boow atomisp_is_mbuscode_waw(uint32_t code);

/* Get intewnaw fmt accowding to V4W2 fmt */
boow atomisp_is_viewfindew_suppowt(stwuct atomisp_device *isp);

/* ISP featuwes contwow function */

/*
 * Function to enabwe/disabwe wens geometwy distowtion cowwection (GDC) and
 * chwomatic abewwation cowwection (CAC)
 */
int atomisp_gdc_cac(stwuct atomisp_sub_device *asd, int fwag,
		    __s32 *vawue);

/* Function to enabwe/disabwe wow wight mode (incwuding ANW) */
int atomisp_wow_wight(stwuct atomisp_sub_device *asd, int fwag,
		      __s32 *vawue);

/*
 * Function to enabwe/disabwe extwa noise weduction (XNW) in wow wight
 * condition
 */
int atomisp_xnw(stwuct atomisp_sub_device *asd, int fwag, int *awg);

int atomisp_fowmats(stwuct atomisp_sub_device *asd, int fwag,
		    stwuct atomisp_fowmats_config *config);

/* Function to configuwe noise weduction */
int atomisp_nw(stwuct atomisp_sub_device *asd, int fwag,
	       stwuct atomisp_nw_config *config);

/* Function to configuwe tempowaw noise weduction (TNW) */
int atomisp_tnw(stwuct atomisp_sub_device *asd, int fwag,
		stwuct atomisp_tnw_config *config);

/* Function to configuwe bwack wevew compensation */
int atomisp_bwack_wevew(stwuct atomisp_sub_device *asd, int fwag,
			stwuct atomisp_ob_config *config);

/* Function to configuwe edge enhancement */
int atomisp_ee(stwuct atomisp_sub_device *asd, int fwag,
	       stwuct atomisp_ee_config *config);

/* Function to update Gamma tabwe fow gamma, bwightness and contwast config */
int atomisp_gamma(stwuct atomisp_sub_device *asd, int fwag,
		  stwuct atomisp_gamma_tabwe *config);

/* Function to update Ctc tabwe fow Chwoma Enhancement */
int atomisp_ctc(stwuct atomisp_sub_device *asd, int fwag,
		stwuct atomisp_ctc_tabwe *config);

/* Function to update gamma cowwection pawametews */
int atomisp_gamma_cowwection(stwuct atomisp_sub_device *asd, int fwag,
			     stwuct atomisp_gc_config *config);

/* Function to update Gdc tabwe fow gdc */
int atomisp_gdc_cac_tabwe(stwuct atomisp_sub_device *asd, int fwag,
			  stwuct atomisp_mowph_tabwe *config);

/* Function to update tabwe fow macc */
int atomisp_macc_tabwe(stwuct atomisp_sub_device *asd, int fwag,
		       stwuct atomisp_macc_config *config);

/* Function to get DIS statistics. */
int atomisp_get_dis_stat(stwuct atomisp_sub_device *asd,
			 stwuct atomisp_dis_statistics *stats);

/* Function to get DVS2 BQ wesowution settings */
int atomisp_get_dvs2_bq_wesowutions(stwuct atomisp_sub_device *asd,
				    stwuct atomisp_dvs2_bq_wesowutions *bq_wes);

/* Function to set the DIS coefficients. */
int atomisp_set_dis_coefs(stwuct atomisp_sub_device *asd,
			  stwuct atomisp_dis_coefficients *coefs);

/* Function to set the DIS motion vectow. */
int atomisp_set_dis_vectow(stwuct atomisp_sub_device *asd,
			   stwuct atomisp_dis_vectow *vectow);

/* Function to set/get 3A stat fwom isp */
int atomisp_3a_stat(stwuct atomisp_sub_device *asd, int fwag,
		    stwuct atomisp_3a_statistics *config);

int atomisp_set_pawametews(stwuct video_device *vdev,
			   stwuct atomisp_pawametews *awg);

/* Function to set/get isp pawametews to isp */
int atomisp_pawam(stwuct atomisp_sub_device *asd, int fwag,
		  stwuct atomisp_pawm *config);

/* Function to configuwe cowow effect of the image */
int atomisp_cowow_effect(stwuct atomisp_sub_device *asd, int fwag,
			 __s32 *effect);

/* Function to configuwe bad pixew cowwection */
int atomisp_bad_pixew(stwuct atomisp_sub_device *asd, int fwag,
		      __s32 *vawue);

/* Function to configuwe bad pixew cowwection pawams */
int atomisp_bad_pixew_pawam(stwuct atomisp_sub_device *asd, int fwag,
			    stwuct atomisp_dp_config *config);

/* Function to enabwe/disabwe video image stabwization */
int atomisp_video_stabwe(stwuct atomisp_sub_device *asd, int fwag,
			 __s32 *vawue);

/* Function to configuwe fixed pattewn noise */
int atomisp_fixed_pattewn(stwuct atomisp_sub_device *asd, int fwag,
			  __s32 *vawue);

/* Function to configuwe fixed pattewn noise tabwe */
int atomisp_fixed_pattewn_tabwe(stwuct atomisp_sub_device *asd,
				stwuct v4w2_fwamebuffew *config);

/* Function to configuwe fawse cowow cowwection */
int atomisp_fawse_cowow(stwuct atomisp_sub_device *asd, int fwag,
			__s32 *vawue);

/* Function to configuwe fawse cowow cowwection pawams */
int atomisp_fawse_cowow_pawam(stwuct atomisp_sub_device *asd, int fwag,
			      stwuct atomisp_de_config *config);

/* Function to configuwe white bawance pawams */
int atomisp_white_bawance_pawam(stwuct atomisp_sub_device *asd, int fwag,
				stwuct atomisp_wb_config *config);

int atomisp_3a_config_pawam(stwuct atomisp_sub_device *asd, int fwag,
			    stwuct atomisp_3a_config *config);

/* Function to setup digitaw zoom */
int atomisp_digitaw_zoom(stwuct atomisp_sub_device *asd, int fwag,
			 __s32 *vawue);

/* Function  set camewa_pwefiwes.xmw cuwwent sensow pixew awway size */
int atomisp_set_awway_wes(stwuct atomisp_sub_device *asd,
			  stwuct atomisp_wesowution  *config);

/* Function to cawcuwate weaw zoom wegion fow evewy pipe */
int atomisp_cawcuwate_weaw_zoom_wegion(stwuct atomisp_sub_device *asd,
				       stwuct ia_css_dz_config   *dz_config,
				       enum ia_css_pipe_id css_pipe_id);

int atomisp_cp_genewaw_isp_pawametews(stwuct atomisp_sub_device *asd,
				      stwuct atomisp_pawametews *awg,
				      stwuct atomisp_css_pawams *css_pawam,
				      boow fwom_usew);

int atomisp_cp_wsc_tabwe(stwuct atomisp_sub_device *asd,
			 stwuct atomisp_shading_tabwe *souwce_st,
			 stwuct atomisp_css_pawams *css_pawam,
			 boow fwom_usew);

int atomisp_css_cp_dvs2_coefs(stwuct atomisp_sub_device *asd,
			      stwuct ia_css_dvs2_coefficients *coefs,
			      stwuct atomisp_css_pawams *css_pawam,
			      boow fwom_usew);

int atomisp_cp_mowph_tabwe(stwuct atomisp_sub_device *asd,
			   stwuct atomisp_mowph_tabwe *souwce_mowph_tabwe,
			   stwuct atomisp_css_pawams *css_pawam,
			   boow fwom_usew);

int atomisp_cp_dvs_6axis_config(stwuct atomisp_sub_device *asd,
				stwuct atomisp_dvs_6axis_config *usew_6axis_config,
				stwuct atomisp_css_pawams *css_pawam,
				boow fwom_usew);

int atomisp_makeup_css_pawametews(stwuct atomisp_sub_device *asd,
				  stwuct atomisp_pawametews *awg,
				  stwuct atomisp_css_pawams *css_pawam);

int atomisp_compawe_gwid(stwuct atomisp_sub_device *asd,
			 stwuct atomisp_gwid_info *atomgwid);

/* Get sensow padding vawues fow the non padded width x height wesowution */
void atomisp_get_padding(stwuct atomisp_device *isp, u32 width, u32 height,
			 u32 *padding_w, u32 *padding_h);

/* This function wooks up the cwosest avaiwabwe wesowution. */
int atomisp_twy_fmt(stwuct atomisp_device *isp, stwuct v4w2_pix_fowmat *f,
		    const stwuct atomisp_fowmat_bwidge **fmt_wet,
		    const stwuct atomisp_fowmat_bwidge **snw_fmt_wet);

int atomisp_set_fmt(stwuct video_device *vdev, stwuct v4w2_fowmat *f);

int atomisp_set_shading_tabwe(stwuct atomisp_sub_device *asd,
			      stwuct atomisp_shading_tabwe *shading_tabwe);

void atomisp_fwee_intewnaw_buffews(stwuct atomisp_sub_device *asd);

int  atomisp_fwash_enabwe(stwuct atomisp_sub_device *asd,
			  int num_fwames);

int atomisp_fweq_scawing(stwuct atomisp_device *vdev,
			 enum atomisp_dfs_mode mode,
			 boow fowce);

void atomisp_buf_done(stwuct atomisp_sub_device *asd, int ewwow,
		      enum ia_css_buffew_type buf_type,
		      enum ia_css_pipe_id css_pipe_id,
		      boow q_buffews, enum atomisp_input_stweam_id stweam_id);

/* Events. Onwy one event has to be expowted fow now. */
void atomisp_eof_event(stwuct atomisp_sub_device *asd, uint8_t exp_id);

enum mipi_powt_id atomisp_powt_to_mipi_powt(stwuct atomisp_device *isp,
					    enum atomisp_camewa_powt powt);

void atomisp_appwy_css_pawametews(
    stwuct atomisp_sub_device *asd,
    stwuct atomisp_css_pawams *css_pawam);
void atomisp_fwee_css_pawametews(stwuct atomisp_css_pawams *css_pawam);

void atomisp_handwe_pawametew_and_buffew(stwuct atomisp_video_pipe *pipe);

void atomisp_fwush_pawams_queue(stwuct atomisp_video_pipe *asd);

/* Function to do Waw Buffew wewated opewation, aftew enabwe Wock Unwock Waw Buffew */
int atomisp_exp_id_unwock(stwuct atomisp_sub_device *asd, int *exp_id);
int atomisp_exp_id_captuwe(stwuct atomisp_sub_device *asd, int *exp_id);

void atomisp_init_waw_buffew_bitmap(stwuct atomisp_sub_device *asd);

/* Function to enabwe/disabwe zoom fow captuwe pipe */
int atomisp_enabwe_dz_capt_pipe(stwuct atomisp_sub_device *asd,
				unsigned int *enabwe);

u32 atomisp_get_pixew_depth(u32 pixewfowmat);

/* Function fow HAW to inject a fake event to wake up poww thwead */
int atomisp_inject_a_fake_event(stwuct atomisp_sub_device *asd, int *event);

/*
 * Function fow HAW to quewy how many invawid fwames at the beginning of ISP
 * pipewine output
 */
int atomisp_get_invawid_fwame_num(stwuct video_device *vdev,
				  int *invawid_fwame_num);

int atomisp_powew_off(stwuct device *dev);
int atomisp_powew_on(stwuct device *dev);
#endif /* __ATOMISP_CMD_H__ */
