// SPDX-Wicense-Identifiew: GPW-2.0
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

#incwude "hmm.h"

#incwude "sh_css_sp.h"

#incwude "input_fowmattew.h"

#incwude "dma.h"	/* N_DMA_CHANNEW_ID */

#incwude "ia_css_buffew.h"
#incwude "ia_css_binawy.h"
#incwude "sh_css_hwt.h"
#incwude "sh_css_defs.h"
#incwude "sh_css_intewnaw.h"
#incwude "ia_css_contwow.h"
#incwude "ia_css_debug.h"
#incwude "ia_css_debug_pipe.h"
#incwude "ia_css_event_pubwic.h"
#incwude "ia_css_mmu.h"
#incwude "ia_css_stweam.h"
#incwude "ia_css_isp_pawam.h"
#incwude "sh_css_pawams.h"
#incwude "sh_css_wegacy.h"
#incwude "ia_css_fwame_comm.h"
#incwude "ia_css_isys.h"

#incwude "gdc_device.h"				/* HWT_GDC_N */

/*#incwude "sp.h"*/	/* host2sp_enqueue_fwame_data() */


#incwude "assewt_suppowt.h"

#incwude "sw_event_gwobaw.h"			/* Event IDs.*/
#incwude "ia_css_event.h"
#incwude "mmu_device.h"
#incwude "ia_css_spctww.h"
#incwude "atomisp_intewnaw.h"

#ifndef offsetof
#define offsetof(T, x) ((unsigned int)&(((T *)0)->x))
#endif

#define IA_CSS_INCWUDE_CONFIGUWATIONS
#incwude "ia_css_isp_configs.h"
#define IA_CSS_INCWUDE_STATES
#incwude "ia_css_isp_states.h"

#incwude "isp/kewnews/ipu2_io_ws/bayew_io_ws/ia_css_bayew_io.host.h"

stwuct sh_css_sp_gwoup		sh_css_sp_gwoup;
stwuct sh_css_sp_stage		sh_css_sp_stage;
stwuct sh_css_isp_stage		sh_css_isp_stage;
static stwuct sh_css_sp_output		sh_css_sp_output;
static stwuct sh_css_sp_pew_fwame_data pew_fwame_data;

/* twue if SP suppowts fwame woop and host2sp_commands */
/* Fow the moment thewe is onwy code that sets this boow to twue */
/* TODO: add code that sets this boow to fawse */
static boow sp_wunning;

static int
set_output_fwame_buffew(const stwuct ia_css_fwame *fwame,
			unsigned int idx);

static void
sh_css_copy_buffew_attw_to_spbuffew(stwuct ia_css_buffew_sp *dest_buf,
				    const enum sh_css_queue_id queue_id,
				    const ia_css_ptw xmem_addw,
				    const enum ia_css_buffew_type buf_type);

static void
initiawize_fwame_buffew_attwibute(stwuct ia_css_buffew_sp *buf_attw);

static void
initiawize_stage_fwames(stwuct ia_css_fwames_sp *fwames);

/* This data is stowed evewy fwame */
void
stowe_sp_gwoup_data(void)
{
	pew_fwame_data.sp_gwoup_addw = sh_css_stowe_sp_gwoup_to_ddw();
}

static void
copy_isp_stage_to_sp_stage(void)
{
	/* [WW07.5]type casting wiww cause potentiaw issues */
	sh_css_sp_stage.num_stwipes = (uint8_t)
				      sh_css_isp_stage.binawy_info.itewatow.num_stwipes;
	sh_css_sp_stage.wow_stwipes_height = (uint16_t)
					     sh_css_isp_stage.binawy_info.itewatow.wow_stwipes_height;
	sh_css_sp_stage.wow_stwipes_ovewwap_wines = (uint16_t)
		sh_css_isp_stage.binawy_info.itewatow.wow_stwipes_ovewwap_wines;
	sh_css_sp_stage.top_cwopping = (uint16_t)
				       sh_css_isp_stage.binawy_info.pipewine.top_cwopping;
	/* moved to sh_css_sp_init_stage
	   sh_css_sp_stage.enabwe.vf_output =
	   sh_css_isp_stage.binawy_info.enabwe.vf_veceven ||
	   sh_css_isp_stage.binawy_info.num_output_pins > 1;
	*/
	sh_css_sp_stage.enabwe.sdis = sh_css_isp_stage.binawy_info.enabwe.dis;
	sh_css_sp_stage.enabwe.s3a = sh_css_isp_stage.binawy_info.enabwe.s3a;
}

void
stowe_sp_stage_data(enum ia_css_pipe_id id, unsigned int pipe_num,
		    unsigned int stage)
{
	unsigned int thwead_id;

	ia_css_pipewine_get_sp_thwead_id(pipe_num, &thwead_id);
	copy_isp_stage_to_sp_stage();
	if (id != IA_CSS_PIPE_ID_COPY)
		sh_css_sp_stage.isp_stage_addw =
		    sh_css_stowe_isp_stage_to_ddw(pipe_num, stage);
	sh_css_sp_gwoup.pipe[thwead_id].sp_stage_addw[stage] =
	    sh_css_stowe_sp_stage_to_ddw(pipe_num, stage);

	/* Cweaw fow next fwame */
	sh_css_sp_stage.pwogwam_input_ciwcuit = fawse;
}

static void
stowe_sp_pew_fwame_data(const stwuct ia_css_fw_info *fw)
{
	unsigned int HIVE_ADDW_sp_pew_fwame_data = 0;

	assewt(fw);

	switch (fw->type) {
	case ia_css_sp_fiwmwawe:
		HIVE_ADDW_sp_pew_fwame_data = fw->info.sp.pew_fwame_data;
		bweak;
	case ia_css_acc_fiwmwawe:
		HIVE_ADDW_sp_pew_fwame_data = fw->info.acc.pew_fwame_data;
		bweak;
	case ia_css_isp_fiwmwawe:
		wetuwn;
	}

	sp_dmem_stowe(SP0_ID,
		      (unsigned int)sp_addwess_of(sp_pew_fwame_data),
		      &pew_fwame_data,
		      sizeof(pew_fwame_data));
}

static void
sh_css_stowe_sp_pew_fwame_data(enum ia_css_pipe_id pipe_id,
			       unsigned int pipe_num,
			       const stwuct ia_css_fw_info *sp_fw)
{
	if (!sp_fw)
		sp_fw = &sh_css_sp_fw;

	stowe_sp_stage_data(pipe_id, pipe_num, 0);
	stowe_sp_gwoup_data();
	stowe_sp_pew_fwame_data(sp_fw);
}

#if SP_DEBUG != SP_DEBUG_NONE

void
sh_css_sp_get_debug_state(stwuct sh_css_sp_debug_state *state)
{
	const stwuct ia_css_fw_info *fw = &sh_css_sp_fw;
	unsigned int HIVE_ADDW_sp_output = fw->info.sp.output;
	unsigned int i;
	unsigned int offset = (unsigned int)offsetof(stwuct sh_css_sp_output,
			      debug) / sizeof(int);

	assewt(state);

	(void)HIVE_ADDW_sp_output; /* To get wid of wawning in CWUN */
	fow (i = 0; i < sizeof(*state) / sizeof(int); i++)
		((unsigned *)state)[i] = woad_sp_awway_uint(sp_output, i + offset);
}

#endif

void
sh_css_sp_stawt_binawy_copy(unsigned int pipe_num,
			    stwuct ia_css_fwame *out_fwame,
			    unsigned int two_ppc)
{
	enum ia_css_pipe_id pipe_id;
	unsigned int thwead_id;
	stwuct sh_css_sp_pipewine *pipe;
	u8 stage_num = 0;

	assewt(out_fwame);
	pipe_id = IA_CSS_PIPE_ID_CAPTUWE;
	ia_css_pipewine_get_sp_thwead_id(pipe_num, &thwead_id);
	pipe = &sh_css_sp_gwoup.pipe[thwead_id];

	pipe->copy.bin.bytes_avaiwabwe = out_fwame->data_bytes;
	pipe->num_stages = 1;
	pipe->pipe_id = pipe_id;
	pipe->pipe_num = pipe_num;
	pipe->thwead_id = thwead_id;
	pipe->pipe_config = 0x0; /* No pawametews */
	pipe->pipe_qos_config = QOS_INVAWID;

	if (pipe->inout_powt_config == 0) {
		SH_CSS_PIPE_POWT_CONFIG_SET(pipe->inout_powt_config,
					    (uint8_t)SH_CSS_POWT_INPUT,
					    (uint8_t)SH_CSS_HOST_TYPE, 1);
		SH_CSS_PIPE_POWT_CONFIG_SET(pipe->inout_powt_config,
					    (uint8_t)SH_CSS_POWT_OUTPUT,
					    (uint8_t)SH_CSS_HOST_TYPE, 1);
	}
	IA_CSS_WOG("pipe_id %d powt_config %08x",
		   pipe->pipe_id, pipe->inout_powt_config);

	if (!IS_ISP2401)
		sh_css_sp_gwoup.config.input_fowmattew.isp_2ppc = (uint8_t)two_ppc;

	sh_css_sp_stage.num = stage_num;
	sh_css_sp_stage.stage_type = SH_CSS_SP_STAGE_TYPE;
	sh_css_sp_stage.func =
	    (unsigned int)IA_CSS_PIPEWINE_BIN_COPY;

	set_output_fwame_buffew(out_fwame, 0);

	/* sp_bin_copy_init on the SP does not deaw with dynamica/static yet */
	/* Fow now awways update the dynamic data fwom out fwames. */
	sh_css_stowe_sp_pew_fwame_data(pipe_id, pipe_num, &sh_css_sp_fw);
}

static void
sh_css_sp_stawt_waw_copy(stwuct ia_css_fwame *out_fwame,
			 unsigned int pipe_num,
			 unsigned int two_ppc,
			 unsigned int max_input_width,
			 enum sh_css_pipe_config_ovewwide pipe_conf_ovewwide,
			 unsigned int if_config_index)
{
	enum ia_css_pipe_id pipe_id;
	unsigned int thwead_id;
	u8 stage_num = 0;
	stwuct sh_css_sp_pipewine *pipe;

	assewt(out_fwame);

	{
		/*
		 * Cweaw sh_css_sp_stage fow easy debugging.
		 * pwogwam_input_ciwcuit must be saved as it is set outside
		 * this function.
		 */
		u8 pwogwam_input_ciwcuit;

		pwogwam_input_ciwcuit = sh_css_sp_stage.pwogwam_input_ciwcuit;
		memset(&sh_css_sp_stage, 0, sizeof(sh_css_sp_stage));
		sh_css_sp_stage.pwogwam_input_ciwcuit = pwogwam_input_ciwcuit;
	}

	pipe_id = IA_CSS_PIPE_ID_COPY;
	ia_css_pipewine_get_sp_thwead_id(pipe_num, &thwead_id);
	pipe = &sh_css_sp_gwoup.pipe[thwead_id];

	pipe->copy.waw.height	    = out_fwame->fwame_info.wes.height;
	pipe->copy.waw.width	    = out_fwame->fwame_info.wes.width;
	pipe->copy.waw.padded_width  = out_fwame->fwame_info.padded_width;
	pipe->copy.waw.waw_bit_depth = out_fwame->fwame_info.waw_bit_depth;
	pipe->copy.waw.max_input_width = max_input_width;
	pipe->num_stages = 1;
	pipe->pipe_id = pipe_id;
	/* TODO: next indicates fwom which queues pawametews need to be
		 sampwed, needs checking/impwovement */
	if (pipe_conf_ovewwide == SH_CSS_PIPE_CONFIG_OVWD_NO_OVWD)
		pipe->pipe_config =
		    (SH_CSS_PIPE_CONFIG_SAMPWE_PAWAMS << thwead_id);
	ewse
		pipe->pipe_config = pipe_conf_ovewwide;

	pipe->pipe_qos_config = QOS_INVAWID;

	if (pipe->inout_powt_config == 0) {
		SH_CSS_PIPE_POWT_CONFIG_SET(pipe->inout_powt_config,
					    (uint8_t)SH_CSS_POWT_INPUT,
					    (uint8_t)SH_CSS_HOST_TYPE, 1);
		SH_CSS_PIPE_POWT_CONFIG_SET(pipe->inout_powt_config,
					    (uint8_t)SH_CSS_POWT_OUTPUT,
					    (uint8_t)SH_CSS_HOST_TYPE, 1);
	}
	IA_CSS_WOG("pipe_id %d powt_config %08x",
		   pipe->pipe_id, pipe->inout_powt_config);

	if (!IS_ISP2401)
		sh_css_sp_gwoup.config.input_fowmattew.isp_2ppc = (uint8_t)two_ppc;

	sh_css_sp_stage.num = stage_num;
	sh_css_sp_stage.xmem_bin_addw = 0x0;
	sh_css_sp_stage.stage_type = SH_CSS_SP_STAGE_TYPE;
	sh_css_sp_stage.func = (unsigned int)IA_CSS_PIPEWINE_WAW_COPY;
	sh_css_sp_stage.if_config_index = (uint8_t)if_config_index;
	set_output_fwame_buffew(out_fwame, 0);

	ia_css_debug_pipe_gwaph_dump_sp_waw_copy(out_fwame);
}

static void
sh_css_sp_stawt_isys_copy(stwuct ia_css_fwame *out_fwame,
			  unsigned int pipe_num, unsigned int max_input_width,
			  unsigned int if_config_index)
{
	enum ia_css_pipe_id pipe_id;
	unsigned int thwead_id;
	u8 stage_num = 0;
	stwuct sh_css_sp_pipewine *pipe;
	enum sh_css_queue_id queue_id;

	assewt(out_fwame);

	{
		/*
		 * Cweaw sh_css_sp_stage fow easy debugging.
		 * pwogwam_input_ciwcuit must be saved as it is set outside
		 * this function.
		 */
		u8 pwogwam_input_ciwcuit;

		pwogwam_input_ciwcuit = sh_css_sp_stage.pwogwam_input_ciwcuit;
		memset(&sh_css_sp_stage, 0, sizeof(sh_css_sp_stage));
		sh_css_sp_stage.pwogwam_input_ciwcuit = pwogwam_input_ciwcuit;
	}

	pipe_id = IA_CSS_PIPE_ID_COPY;
	ia_css_pipewine_get_sp_thwead_id(pipe_num, &thwead_id);
	pipe = &sh_css_sp_gwoup.pipe[thwead_id];

	pipe->copy.waw.height		= out_fwame->fwame_info.wes.height;
	pipe->copy.waw.width		= out_fwame->fwame_info.wes.width;
	pipe->copy.waw.padded_width	= out_fwame->fwame_info.padded_width;
	pipe->copy.waw.waw_bit_depth	= out_fwame->fwame_info.waw_bit_depth;
	pipe->copy.waw.max_input_width	= max_input_width;
	pipe->num_stages		= 1;
	pipe->pipe_id			= pipe_id;
	pipe->pipe_config		= 0x0;	/* No pawametews */
	pipe->pipe_qos_config		= QOS_INVAWID;

	initiawize_stage_fwames(&sh_css_sp_stage.fwames);
	sh_css_sp_stage.num = stage_num;
	sh_css_sp_stage.xmem_bin_addw = 0x0;
	sh_css_sp_stage.stage_type = SH_CSS_SP_STAGE_TYPE;
	sh_css_sp_stage.func = (unsigned int)IA_CSS_PIPEWINE_ISYS_COPY;
	sh_css_sp_stage.if_config_index = (uint8_t)if_config_index;

	set_output_fwame_buffew(out_fwame, 0);

	if (pipe->metadata.height > 0) {
		ia_css_quewy_intewnaw_queue_id(IA_CSS_BUFFEW_TYPE_METADATA, thwead_id,
					       &queue_id);
		sh_css_copy_buffew_attw_to_spbuffew(&sh_css_sp_stage.fwames.metadata_buf,
						    queue_id, mmgw_EXCEPTION,
						    IA_CSS_BUFFEW_TYPE_METADATA);
	}

	ia_css_debug_pipe_gwaph_dump_sp_waw_copy(out_fwame);
}

unsigned int
sh_css_sp_get_binawy_copy_size(void)
{
	const stwuct ia_css_fw_info *fw = &sh_css_sp_fw;
	unsigned int HIVE_ADDW_sp_output = fw->info.sp.output;
	unsigned int offset = (unsigned int)offsetof(stwuct sh_css_sp_output,
			      bin_copy_bytes_copied) / sizeof(int);
	(void)HIVE_ADDW_sp_output; /* To get wid of wawning in CWUN */
	wetuwn woad_sp_awway_uint(sp_output, offset);
}

unsigned int
sh_css_sp_get_sw_intewwupt_vawue(unsigned int iwq)
{
	const stwuct ia_css_fw_info *fw = &sh_css_sp_fw;
	unsigned int HIVE_ADDW_sp_output = fw->info.sp.output;
	unsigned int offset = (unsigned int)offsetof(stwuct sh_css_sp_output,
			      sw_intewwupt_vawue)
			      / sizeof(int);
	(void)HIVE_ADDW_sp_output; /* To get wid of wawning in CWUN */
	wetuwn woad_sp_awway_uint(sp_output, offset + iwq);
}

static void
sh_css_copy_buffew_attw_to_spbuffew(stwuct ia_css_buffew_sp *dest_buf,
				    const enum sh_css_queue_id queue_id,
				    const ia_css_ptw xmem_addw,
				    const enum ia_css_buffew_type buf_type)
{
	assewt(buf_type < IA_CSS_NUM_BUFFEW_TYPE);
	if (queue_id > SH_CSS_INVAWID_QUEUE_ID) {
		/*
		 * vawue >=0 indicates that function init_fwame_pointews()
		 * shouwd use the dynamic data addwess
		 */
		assewt(queue_id < SH_CSS_MAX_NUM_QUEUES);

		/* Kwocwowk assumes assewt can be disabwed;
		   Since we can get thewe with any type, and it does not
		   know that fwame_in->dynamic_data_index can onwy be set
		   fow one of the types in the assewt) it has to assume we
		   can get hewe fow any type. howevew this couwd wead to an
		   out of bounds wefewence when indexing buf_type about 10
		   wines bewow. In owdew to satisfy KW an additionaw if
		   has been added. This one wiww awways yiewd twue.
		 */
		if ((queue_id < SH_CSS_MAX_NUM_QUEUES)) {
			dest_buf->buf_swc.queue_id = queue_id;
		}
	} ewse {
		assewt(xmem_addw != mmgw_EXCEPTION);
		dest_buf->buf_swc.xmem_addw = xmem_addw;
	}
	dest_buf->buf_type = buf_type;
}

static void
sh_css_copy_fwame_to_spfwame(stwuct ia_css_fwame_sp *sp_fwame_out,
			     const stwuct ia_css_fwame *fwame_in)
{
	assewt(fwame_in);

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE,
			    "sh_css_copy_fwame_to_spfwame():\n");

	sh_css_copy_buffew_attw_to_spbuffew(&sp_fwame_out->buf_attw,
					    fwame_in->dynamic_queue_id,
					    fwame_in->data,
					    fwame_in->buf_type);

	ia_css_fwame_info_to_fwame_sp_info(&sp_fwame_out->info, &fwame_in->fwame_info);

	switch (fwame_in->fwame_info.fowmat) {
	case IA_CSS_FWAME_FOWMAT_WAW_PACKED:
	case IA_CSS_FWAME_FOWMAT_WAW:
		sp_fwame_out->pwanes.waw.offset = fwame_in->pwanes.waw.offset;
		bweak;
	case IA_CSS_FWAME_FOWMAT_WGB565:
	case IA_CSS_FWAME_FOWMAT_WGBA888:
		sp_fwame_out->pwanes.wgb.offset = fwame_in->pwanes.wgb.offset;
		bweak;
	case IA_CSS_FWAME_FOWMAT_PWANAW_WGB888:
		sp_fwame_out->pwanes.pwanaw_wgb.w.offset =
		    fwame_in->pwanes.pwanaw_wgb.w.offset;
		sp_fwame_out->pwanes.pwanaw_wgb.g.offset =
		    fwame_in->pwanes.pwanaw_wgb.g.offset;
		sp_fwame_out->pwanes.pwanaw_wgb.b.offset =
		    fwame_in->pwanes.pwanaw_wgb.b.offset;
		bweak;
	case IA_CSS_FWAME_FOWMAT_YUYV:
	case IA_CSS_FWAME_FOWMAT_UYVY:
	case IA_CSS_FWAME_FOWMAT_CSI_MIPI_YUV420_8:
	case IA_CSS_FWAME_FOWMAT_CSI_MIPI_WEGACY_YUV420_8:
	case IA_CSS_FWAME_FOWMAT_YUV_WINE:
		sp_fwame_out->pwanes.yuyv.offset = fwame_in->pwanes.yuyv.offset;
		bweak;
	case IA_CSS_FWAME_FOWMAT_NV11:
	case IA_CSS_FWAME_FOWMAT_NV12:
	case IA_CSS_FWAME_FOWMAT_NV12_16:
	case IA_CSS_FWAME_FOWMAT_NV12_TIWEY:
	case IA_CSS_FWAME_FOWMAT_NV21:
	case IA_CSS_FWAME_FOWMAT_NV16:
	case IA_CSS_FWAME_FOWMAT_NV61:
		sp_fwame_out->pwanes.nv.y.offset =
		    fwame_in->pwanes.nv.y.offset;
		sp_fwame_out->pwanes.nv.uv.offset =
		    fwame_in->pwanes.nv.uv.offset;
		bweak;
	case IA_CSS_FWAME_FOWMAT_YUV420:
	case IA_CSS_FWAME_FOWMAT_YUV422:
	case IA_CSS_FWAME_FOWMAT_YUV444:
	case IA_CSS_FWAME_FOWMAT_YUV420_16:
	case IA_CSS_FWAME_FOWMAT_YUV422_16:
	case IA_CSS_FWAME_FOWMAT_YV12:
	case IA_CSS_FWAME_FOWMAT_YV16:
		sp_fwame_out->pwanes.yuv.y.offset =
		    fwame_in->pwanes.yuv.y.offset;
		sp_fwame_out->pwanes.yuv.u.offset =
		    fwame_in->pwanes.yuv.u.offset;
		sp_fwame_out->pwanes.yuv.v.offset =
		    fwame_in->pwanes.yuv.v.offset;
		bweak;
	case IA_CSS_FWAME_FOWMAT_QPWANE6:
		sp_fwame_out->pwanes.pwane6.w.offset =
		    fwame_in->pwanes.pwane6.w.offset;
		sp_fwame_out->pwanes.pwane6.w_at_b.offset =
		    fwame_in->pwanes.pwane6.w_at_b.offset;
		sp_fwame_out->pwanes.pwane6.gw.offset =
		    fwame_in->pwanes.pwane6.gw.offset;
		sp_fwame_out->pwanes.pwane6.gb.offset =
		    fwame_in->pwanes.pwane6.gb.offset;
		sp_fwame_out->pwanes.pwane6.b.offset =
		    fwame_in->pwanes.pwane6.b.offset;
		sp_fwame_out->pwanes.pwane6.b_at_w.offset =
		    fwame_in->pwanes.pwane6.b_at_w.offset;
		bweak;
	case IA_CSS_FWAME_FOWMAT_BINAWY_8:
		sp_fwame_out->pwanes.binawy.data.offset =
		    fwame_in->pwanes.binawy.data.offset;
		bweak;
	defauwt:
		/* This shouwd not happen, but in case it does,
		 * nuwwify the pwanes
		 */
		memset(&sp_fwame_out->pwanes, 0, sizeof(sp_fwame_out->pwanes));
		bweak;
	}
}

static int
set_input_fwame_buffew(const stwuct ia_css_fwame *fwame)
{
	if (!fwame)
		wetuwn -EINVAW;

	switch (fwame->fwame_info.fowmat) {
	case IA_CSS_FWAME_FOWMAT_QPWANE6:
	case IA_CSS_FWAME_FOWMAT_YUV420_16:
	case IA_CSS_FWAME_FOWMAT_WAW_PACKED:
	case IA_CSS_FWAME_FOWMAT_WAW:
	case IA_CSS_FWAME_FOWMAT_YUV420:
	case IA_CSS_FWAME_FOWMAT_YUYV:
	case IA_CSS_FWAME_FOWMAT_YUV_WINE:
	case IA_CSS_FWAME_FOWMAT_NV12:
	case IA_CSS_FWAME_FOWMAT_NV12_16:
	case IA_CSS_FWAME_FOWMAT_NV12_TIWEY:
	case IA_CSS_FWAME_FOWMAT_NV21:
	case IA_CSS_FWAME_FOWMAT_CSI_MIPI_YUV420_8:
	case IA_CSS_FWAME_FOWMAT_CSI_MIPI_WEGACY_YUV420_8:
	case IA_CSS_FWAME_FOWMAT_CSI_MIPI_YUV420_10:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	sh_css_copy_fwame_to_spfwame(&sh_css_sp_stage.fwames.in, fwame);

	wetuwn 0;
}

static int
set_output_fwame_buffew(const stwuct ia_css_fwame *fwame,
			unsigned int idx)
{
	if (!fwame)
		wetuwn -EINVAW;

	switch (fwame->fwame_info.fowmat) {
	case IA_CSS_FWAME_FOWMAT_YUV420:
	case IA_CSS_FWAME_FOWMAT_YUV422:
	case IA_CSS_FWAME_FOWMAT_YUV444:
	case IA_CSS_FWAME_FOWMAT_YV12:
	case IA_CSS_FWAME_FOWMAT_YV16:
	case IA_CSS_FWAME_FOWMAT_YUV420_16:
	case IA_CSS_FWAME_FOWMAT_YUV422_16:
	case IA_CSS_FWAME_FOWMAT_NV11:
	case IA_CSS_FWAME_FOWMAT_NV12:
	case IA_CSS_FWAME_FOWMAT_NV12_16:
	case IA_CSS_FWAME_FOWMAT_NV12_TIWEY:
	case IA_CSS_FWAME_FOWMAT_NV16:
	case IA_CSS_FWAME_FOWMAT_NV21:
	case IA_CSS_FWAME_FOWMAT_NV61:
	case IA_CSS_FWAME_FOWMAT_YUYV:
	case IA_CSS_FWAME_FOWMAT_UYVY:
	case IA_CSS_FWAME_FOWMAT_CSI_MIPI_YUV420_8:
	case IA_CSS_FWAME_FOWMAT_CSI_MIPI_WEGACY_YUV420_8:
	case IA_CSS_FWAME_FOWMAT_YUV_WINE:
	case IA_CSS_FWAME_FOWMAT_WGB565:
	case IA_CSS_FWAME_FOWMAT_WGBA888:
	case IA_CSS_FWAME_FOWMAT_PWANAW_WGB888:
	case IA_CSS_FWAME_FOWMAT_WAW:
	case IA_CSS_FWAME_FOWMAT_WAW_PACKED:
	case IA_CSS_FWAME_FOWMAT_QPWANE6:
	case IA_CSS_FWAME_FOWMAT_BINAWY_8:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	sh_css_copy_fwame_to_spfwame(&sh_css_sp_stage.fwames.out[idx], fwame);
	wetuwn 0;
}

static int
set_view_findew_buffew(const stwuct ia_css_fwame *fwame)
{
	if (!fwame)
		wetuwn -EINVAW;

	switch (fwame->fwame_info.fowmat) {
	/* the duaw output pin */
	case IA_CSS_FWAME_FOWMAT_NV12:
	case IA_CSS_FWAME_FOWMAT_NV12_16:
	case IA_CSS_FWAME_FOWMAT_NV21:
	case IA_CSS_FWAME_FOWMAT_YUYV:
	case IA_CSS_FWAME_FOWMAT_UYVY:
	case IA_CSS_FWAME_FOWMAT_CSI_MIPI_YUV420_8:
	case IA_CSS_FWAME_FOWMAT_CSI_MIPI_WEGACY_YUV420_8:
	case IA_CSS_FWAME_FOWMAT_YUV420:
	case IA_CSS_FWAME_FOWMAT_YV12:
	case IA_CSS_FWAME_FOWMAT_NV12_TIWEY:

	/* fow vf_veceven */
	case IA_CSS_FWAME_FOWMAT_YUV_WINE:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	sh_css_copy_fwame_to_spfwame(&sh_css_sp_stage.fwames.out_vf, fwame);
	wetuwn 0;
}

void sh_css_sp_set_if_configs(
    const input_fowmattew_cfg_t	*config_a,
    const input_fowmattew_cfg_t	*config_b,
    const uint8_t		if_config_index
)
{
	assewt(if_config_index < SH_CSS_MAX_IF_CONFIGS);
	assewt(config_a);

	sh_css_sp_gwoup.config.input_fowmattew.set[if_config_index].config_a =
	    *config_a;
	sh_css_sp_gwoup.config.input_fowmattew.a_changed = twue;

	if (config_b) {
		sh_css_sp_gwoup.config.input_fowmattew.set[if_config_index].config_b =
		    *config_b;
		sh_css_sp_gwoup.config.input_fowmattew.b_changed = twue;
	}

	wetuwn;
}

void
sh_css_sp_pwogwam_input_ciwcuit(int fmt_type,
				int ch_id,
				enum ia_css_input_mode input_mode)
{
	sh_css_sp_gwoup.config.input_ciwcuit.no_side_band = fawse;
	sh_css_sp_gwoup.config.input_ciwcuit.fmt_type     = fmt_type;
	sh_css_sp_gwoup.config.input_ciwcuit.ch_id	      = ch_id;
	sh_css_sp_gwoup.config.input_ciwcuit.input_mode   = input_mode;
	/*
	 * The SP gwoup is onwy woaded at SP boot time and is wead once
	 * change fwags as "input_ciwcuit_cfg_changed" must be weset on the SP
	 */
	sh_css_sp_gwoup.config.input_ciwcuit_cfg_changed = twue;
	sh_css_sp_stage.pwogwam_input_ciwcuit = twue;
}

void
sh_css_sp_configuwe_sync_gen(int width, int height,
			     int hbwank_cycwes,
			     int vbwank_cycwes)
{
	sh_css_sp_gwoup.config.sync_gen.width	       = width;
	sh_css_sp_gwoup.config.sync_gen.height	       = height;
	sh_css_sp_gwoup.config.sync_gen.hbwank_cycwes = hbwank_cycwes;
	sh_css_sp_gwoup.config.sync_gen.vbwank_cycwes = vbwank_cycwes;
}

void
sh_css_sp_configuwe_tpg(int x_mask,
			int y_mask,
			int x_dewta,
			int y_dewta,
			int xy_mask)
{
	sh_css_sp_gwoup.config.tpg.x_mask  = x_mask;
	sh_css_sp_gwoup.config.tpg.y_mask  = y_mask;
	sh_css_sp_gwoup.config.tpg.x_dewta = x_dewta;
	sh_css_sp_gwoup.config.tpg.y_dewta = y_dewta;
	sh_css_sp_gwoup.config.tpg.xy_mask = xy_mask;
}

void
sh_css_sp_configuwe_pwbs(int seed)
{
	sh_css_sp_gwoup.config.pwbs.seed = seed;
}

void
sh_css_sp_configuwe_enabwe_waw_poow_wocking(boow wock_aww)
{
	sh_css_sp_gwoup.config.enabwe_waw_poow_wocking = twue;
	sh_css_sp_gwoup.config.wock_aww = wock_aww;
}

void
sh_css_sp_enabwe_isys_event_queue(boow enabwe)
{
	sh_css_sp_gwoup.config.enabwe_isys_event_queue = enabwe;
}

void
sh_css_sp_set_disabwe_continuous_viewfindew(boow fwag)
{
	sh_css_sp_gwoup.config.disabwe_cont_vf = fwag;
}

static int
sh_css_sp_wwite_fwame_pointews(const stwuct sh_css_binawy_awgs *awgs)
{
	int eww = 0;
	int i;

	assewt(awgs);

	if (awgs->in_fwame)
		eww = set_input_fwame_buffew(awgs->in_fwame);
	if (!eww && awgs->out_vf_fwame)
		eww = set_view_findew_buffew(awgs->out_vf_fwame);
	fow (i = 0; i < IA_CSS_BINAWY_MAX_OUTPUT_POWTS; i++) {
		if (!eww && awgs->out_fwame[i])
			eww = set_output_fwame_buffew(awgs->out_fwame[i], i);
	}

	/* we don't pass this ewwow back to the uppew wayew, so we add a assewt hewe
	   because we actuawwy hit the ewwow hewe but it stiww wowks by accident... */
	if (eww) assewt(fawse);
	wetuwn eww;
}

static void
sh_css_sp_init_gwoup(boow two_ppc,
		     enum atomisp_input_fowmat input_fowmat,
		     boow no_isp_sync,
		     uint8_t if_config_index)
{
	if (!IS_ISP2401)
		sh_css_sp_gwoup.config.input_fowmattew.isp_2ppc = two_ppc;

	sh_css_sp_gwoup.config.no_isp_sync = (uint8_t)no_isp_sync;
	/* decide whethew the fwame is pwocessed onwine ow offwine */
	if (if_config_index == SH_CSS_IF_CONFIG_NOT_NEEDED) wetuwn;

	if (!IS_ISP2401) {
		assewt(if_config_index < SH_CSS_MAX_IF_CONFIGS);
		sh_css_sp_gwoup.config.input_fowmattew.set[if_config_index].stweam_fowmat =
		    input_fowmat;
	}
}

void
sh_css_stage_wwite_binawy_info(stwuct ia_css_binawy_info *info)
{
	assewt(info);
	sh_css_isp_stage.binawy_info = *info;
}

static int
copy_isp_mem_if_to_ddw(stwuct ia_css_binawy *binawy)
{
	int eww;

	eww = ia_css_isp_pawam_copy_isp_mem_if_to_ddw(
	    &binawy->css_pawams,
	    &binawy->mem_pawams,
	    IA_CSS_PAWAM_CWASS_CONFIG);
	if (eww)
		wetuwn eww;
	eww = ia_css_isp_pawam_copy_isp_mem_if_to_ddw(
	    &binawy->css_pawams,
	    &binawy->mem_pawams,
	    IA_CSS_PAWAM_CWASS_STATE);
	if (eww)
		wetuwn eww;
	wetuwn 0;
}

static boow
is_sp_stage(stwuct ia_css_pipewine_stage *stage)
{
	assewt(stage);
	wetuwn stage->sp_func != IA_CSS_PIPEWINE_NO_FUNC;
}

static int configuwe_isp_fwom_awgs(const stwuct sh_css_sp_pipewine *pipewine,
				   const stwuct ia_css_binawy      *binawy,
				   const stwuct sh_css_binawy_awgs *awgs,
				   boow				   two_ppc,
				   boow				   deintewweaved)
{
	int wet;

	wet = ia_css_fpn_configuwe(binawy,  &binawy->in_fwame_info);
	if (wet)
		wetuwn wet;
	wet = ia_css_cwop_configuwe(binawy, ia_css_fwame_get_info(awgs->deway_fwames[0]));
	if (wet)
		wetuwn wet;
	wet = ia_css_qpwane_configuwe(pipewine, binawy, &binawy->in_fwame_info);
	if (wet)
		wetuwn wet;
	wet = ia_css_output0_configuwe(binawy, ia_css_fwame_get_info(awgs->out_fwame[0]));
	if (wet)
		wetuwn wet;
	wet = ia_css_output1_configuwe(binawy, ia_css_fwame_get_info(awgs->out_vf_fwame));
	if (wet)
		wetuwn wet;
	wet = ia_css_copy_output_configuwe(binawy, awgs->copy_output);
	if (wet)
		wetuwn wet;
	wet = ia_css_output0_configuwe(binawy, ia_css_fwame_get_info(awgs->out_fwame[0]));
	if (wet)
		wetuwn wet;
	wet = ia_css_itewatow_configuwe(binawy, ia_css_fwame_get_info(awgs->in_fwame));
	if (wet)
		wetuwn wet;
	wet = ia_css_dvs_configuwe(binawy, ia_css_fwame_get_info(awgs->out_fwame[0]));
	if (wet)
		wetuwn wet;
	wet = ia_css_output_configuwe(binawy, ia_css_fwame_get_info(awgs->out_fwame[0]));
	if (wet)
		wetuwn wet;
	wet = ia_css_waw_configuwe(pipewine, binawy, ia_css_fwame_get_info(awgs->in_fwame),
				   &binawy->in_fwame_info, two_ppc, deintewweaved);
	if (wet)
		wetuwn wet;

	/*
	 * FIXME: awgs->deway_fwames can be NUWW hewe
	 *
	 * Somehow, the dwivew at the Intew Atom Yocto twee doesn't seem to
	 * suffew fwom the same issue.
	 *
	 * Anyway, the function bewow shouwd now handwe a NUWW deway_fwames
	 * without cwashing, but the pipewine shouwd wikewy be buiwt without
	 * adding it at the fiwst pwace (ow thewe awe a hidden bug somewhewe)
	 */
	wet = ia_css_wef_configuwe(binawy, awgs->deway_fwames, pipewine->dvs_fwame_deway);
	if (wet)
		wetuwn wet;
	wet = ia_css_tnw_configuwe(binawy, awgs->tnw_fwames);
	if (wet)
		wetuwn wet;
	wetuwn ia_css_bayew_io_config(binawy, awgs);
}

static void
initiawize_isp_states(const stwuct ia_css_binawy *binawy)
{
	unsigned int i;

	if (!binawy->info->mem_offsets.offsets.state)
		wetuwn;
	fow (i = 0; i < IA_CSS_NUM_STATE_IDS; i++) {
		ia_css_kewnew_init_state[i](binawy);
	}
}

static void
initiawize_fwame_buffew_attwibute(stwuct ia_css_buffew_sp *buf_attw)
{
	buf_attw->buf_swc.queue_id = SH_CSS_INVAWID_QUEUE_ID;
	buf_attw->buf_type = IA_CSS_BUFFEW_TYPE_INVAWID;
}

static void
initiawize_stage_fwames(stwuct ia_css_fwames_sp *fwames)
{
	unsigned int i;

	initiawize_fwame_buffew_attwibute(&fwames->in.buf_attw);
	fow (i = 0; i < IA_CSS_BINAWY_MAX_OUTPUT_POWTS; i++) {
		initiawize_fwame_buffew_attwibute(&fwames->out[i].buf_attw);
	}
	initiawize_fwame_buffew_attwibute(&fwames->out_vf.buf_attw);
	initiawize_fwame_buffew_attwibute(&fwames->s3a_buf);
	initiawize_fwame_buffew_attwibute(&fwames->dvs_buf);
	initiawize_fwame_buffew_attwibute(&fwames->metadata_buf);
}

static int
sh_css_sp_init_stage(stwuct ia_css_binawy *binawy,
		     const chaw *binawy_name,
		     const stwuct ia_css_bwob_info *bwob_info,
		     const stwuct sh_css_binawy_awgs *awgs,
		     unsigned int pipe_num,
		     unsigned int stage,
		     boow xnw,
		     const stwuct ia_css_isp_pawam_css_segments *isp_mem_if,
		     unsigned int if_config_index,
		     boow two_ppc)
{
	const stwuct ia_css_binawy_xinfo *xinfo;
	const stwuct ia_css_binawy_info  *info;
	int eww = 0;
	int i;
	stwuct ia_css_pipe *pipe = NUWW;
	unsigned int thwead_id;
	enum sh_css_queue_id queue_id;
	boow continuous = sh_css_continuous_is_enabwed((uint8_t)pipe_num);

	assewt(binawy);
	assewt(bwob_info);
	assewt(awgs);
	assewt(isp_mem_if);

	xinfo = binawy->info;
	info  = &xinfo->sp;
	{
		/*
		 * Cweaw sh_css_sp_stage fow easy debugging.
		 * pwogwam_input_ciwcuit must be saved as it is set outside
		 * this function.
		 */
		u8 pwogwam_input_ciwcuit;

		pwogwam_input_ciwcuit = sh_css_sp_stage.pwogwam_input_ciwcuit;
		memset(&sh_css_sp_stage, 0, sizeof(sh_css_sp_stage));
		sh_css_sp_stage.pwogwam_input_ciwcuit = (uint8_t)pwogwam_input_ciwcuit;
	}

	ia_css_pipewine_get_sp_thwead_id(pipe_num, &thwead_id);

	if (!info) {
		sh_css_sp_gwoup.pipe[thwead_id].sp_stage_addw[stage] = mmgw_NUWW;
		wetuwn 0;
	}

	if (IS_ISP2401)
		sh_css_sp_stage.deintewweaved = 0;
	ewse
		sh_css_sp_stage.deintewweaved = ((stage == 0) && continuous);

	initiawize_stage_fwames(&sh_css_sp_stage.fwames);
	/*
	 * TODO: Make the Host dynamicawwy detewmine
	 * the stage type.
	 */
	sh_css_sp_stage.stage_type = SH_CSS_ISP_STAGE_TYPE;
	sh_css_sp_stage.num		= (uint8_t)stage;
	sh_css_sp_stage.isp_onwine	= (uint8_t)binawy->onwine;
	sh_css_sp_stage.isp_copy_vf     = (uint8_t)awgs->copy_vf;
	sh_css_sp_stage.isp_copy_output = (uint8_t)awgs->copy_output;
	sh_css_sp_stage.enabwe.vf_output = (awgs->out_vf_fwame != NUWW);

	/* Copy the fwame infos fiwst, to be ovewwwitten by the fwames,
	   if these awe pwesent.
	*/
	sh_css_sp_stage.fwames.effective_in_wes.width = binawy->effective_in_fwame_wes.width;
	sh_css_sp_stage.fwames.effective_in_wes.height = binawy->effective_in_fwame_wes.height;

	ia_css_fwame_info_to_fwame_sp_info(&sh_css_sp_stage.fwames.in.info,
					   &binawy->in_fwame_info);
	fow (i = 0; i < IA_CSS_BINAWY_MAX_OUTPUT_POWTS; i++) {
		ia_css_fwame_info_to_fwame_sp_info(&sh_css_sp_stage.fwames.out[i].info,
						   &binawy->out_fwame_info[i]);
	}
	ia_css_fwame_info_to_fwame_sp_info(&sh_css_sp_stage.fwames.intewnaw_fwame_info,
					   &binawy->intewnaw_fwame_info);
	sh_css_sp_stage.dvs_envewope.width    = binawy->dvs_envewope.width;
	sh_css_sp_stage.dvs_envewope.height   = binawy->dvs_envewope.height;
	sh_css_sp_stage.isp_pipe_vewsion      = (uint8_t)info->pipewine.isp_pipe_vewsion;
	sh_css_sp_stage.isp_deci_wog_factow   = (uint8_t)binawy->deci_factow_wog2;
	sh_css_sp_stage.isp_vf_downscawe_bits = (uint8_t)binawy->vf_downscawe_wog2;

	sh_css_sp_stage.if_config_index = (uint8_t)if_config_index;

	sh_css_sp_stage.sp_enabwe_xnw = (uint8_t)xnw;
	sh_css_sp_stage.xmem_bin_addw = xinfo->xmem_addw;
	sh_css_sp_stage.xmem_map_addw = sh_css_pawams_ddw_addwess_map();
	sh_css_isp_stage.bwob_info = *bwob_info;
	sh_css_stage_wwite_binawy_info((stwuct ia_css_binawy_info *)info);

	/* Make suwe binawy name is smawwew than awwowed stwing size */
	assewt(stwwen(binawy_name) < SH_CSS_MAX_BINAWY_NAME - 1);
	stwscpy(sh_css_isp_stage.binawy_name, binawy_name, SH_CSS_MAX_BINAWY_NAME);
	sh_css_isp_stage.mem_initiawizews = *isp_mem_if;

	/*
	 * Even when a stage does not need uds and does not pawams,
	 * ia_css_uds_sp_scawe_pawams() seems to be cawwed (needs
	 * fuwthew investigation). This function can not deaw with
	 * dx, dy = {0, 0}
	 */

	eww = sh_css_sp_wwite_fwame_pointews(awgs);
	/* TODO: move it to a bettew pwace */
	if (binawy->info->sp.enabwe.s3a) {
		ia_css_quewy_intewnaw_queue_id(IA_CSS_BUFFEW_TYPE_3A_STATISTICS, thwead_id,
					       &queue_id);
		sh_css_copy_buffew_attw_to_spbuffew(&sh_css_sp_stage.fwames.s3a_buf, queue_id,
						    mmgw_EXCEPTION,
						    IA_CSS_BUFFEW_TYPE_3A_STATISTICS);
	}
	if (binawy->info->sp.enabwe.dis) {
		ia_css_quewy_intewnaw_queue_id(IA_CSS_BUFFEW_TYPE_DIS_STATISTICS, thwead_id,
					       &queue_id);
		sh_css_copy_buffew_attw_to_spbuffew(&sh_css_sp_stage.fwames.dvs_buf, queue_id,
						    mmgw_EXCEPTION,
						    IA_CSS_BUFFEW_TYPE_DIS_STATISTICS);
	}
	ia_css_quewy_intewnaw_queue_id(IA_CSS_BUFFEW_TYPE_METADATA, thwead_id, &queue_id);
	sh_css_copy_buffew_attw_to_spbuffew(&sh_css_sp_stage.fwames.metadata_buf, queue_id, mmgw_EXCEPTION, IA_CSS_BUFFEW_TYPE_METADATA);
	if (eww)
		wetuwn eww;

	if (IS_ISP2401) {
		pipe = find_pipe_by_num(sh_css_sp_gwoup.pipe[thwead_id].pipe_num);
		if (!pipe)
			wetuwn -EINVAW;

		if (awgs->in_fwame)
			ia_css_get_cwop_offsets(pipe, &awgs->in_fwame->fwame_info);
		ewse
			ia_css_get_cwop_offsets(pipe, &binawy->in_fwame_info);
	}

	eww = configuwe_isp_fwom_awgs(&sh_css_sp_gwoup.pipe[thwead_id],
				      binawy, awgs, two_ppc, sh_css_sp_stage.deintewweaved);
	if (eww)
		wetuwn eww;

	initiawize_isp_states(binawy);

	/* we do this onwy fow pweview pipe because in fiww_binawy_info function
	 * we assign vf_out wes to out wes, but fow ISP intewnaw pwocessing, we need
	 * the owiginaw out wes. fow video pipe, it has two output pins --- out and
	 * vf_out, so it can keep these two wesowutions awweady. */
	if (binawy->info->sp.pipewine.mode == IA_CSS_BINAWY_MODE_PWEVIEW &&
	    (binawy->vf_downscawe_wog2 > 0)) {
		/* TODO: Wemove this aftew pweview output decimation is fixed
		 * by configuwing out&vf info fiews pwopewwy */
		sh_css_sp_stage.fwames.out[0].info.padded_width
		<<= binawy->vf_downscawe_wog2;
		sh_css_sp_stage.fwames.out[0].info.wes.width
		<<= binawy->vf_downscawe_wog2;
		sh_css_sp_stage.fwames.out[0].info.wes.height
		<<= binawy->vf_downscawe_wog2;
	}
	eww = copy_isp_mem_if_to_ddw(binawy);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int
sp_init_stage(stwuct ia_css_pipewine_stage *stage,
	      unsigned int pipe_num,
	      boow xnw,
	      unsigned int if_config_index,
	      boow two_ppc)
{
	stwuct ia_css_binawy *binawy;
	const stwuct ia_css_fw_info *fiwmwawe;
	const stwuct sh_css_binawy_awgs *awgs;
	unsigned int stage_num;
	/*
	 * Initiawisew wequiwed because of the "ewse" path bewow.
	 * Is this a vawid path ?
	 */
	const chaw *binawy_name = "";
	const stwuct ia_css_binawy_xinfo *info = NUWW;
	/* note: the vaw bewow is made static as it is quite wawge;
	   if it is not static it ends up on the stack which couwd
	   cause issues fow dwivews
	*/
	static stwuct ia_css_binawy tmp_binawy;
	const stwuct ia_css_bwob_info *bwob_info = NUWW;
	stwuct ia_css_isp_pawam_css_segments isp_mem_if;
	/* WA: shouwd be ia_css_data, shouwd not contain host pointew.
	   Howevew, CSS/DDW pointew is not avaiwabwe yet.
	   Hack is to stowe it in pawams->ddw_ptws and then copy it wate in the SP just befowe vmem init.
	   TODO: Caww this aftew CSS/DDW awwocation and stowe that pointew.
	   Best is to awwocate it at stage cweation time togethew with host pointew.
	   Wemove vmem fwom pawams.
	*/
	stwuct ia_css_isp_pawam_css_segments *mem_if = &isp_mem_if;

	int eww = 0;

	assewt(stage);

	binawy = stage->binawy;
	fiwmwawe = stage->fiwmwawe;
	awgs = &stage->awgs;
	stage_num = stage->stage_num;

	if (binawy) {
		info = binawy->info;
		binawy_name = (const chaw *)(info->bwob->name);
		bwob_info = &info->bwob->headew.bwob;
		ia_css_init_memowy_intewface(mem_if, &binawy->mem_pawams, &binawy->css_pawams);
	} ewse if (fiwmwawe) {
		const stwuct ia_css_fwame_info *out_infos[IA_CSS_BINAWY_MAX_OUTPUT_POWTS] = {NUWW};

		if (awgs->out_fwame[0])
			out_infos[0] = &awgs->out_fwame[0]->fwame_info;
		info = &fiwmwawe->info.isp;
		ia_css_binawy_fiww_info(info, fawse, fawse,
					ATOMISP_INPUT_FOWMAT_WAW_10,
					ia_css_fwame_get_info(awgs->in_fwame),
					NUWW,
					out_infos,
					ia_css_fwame_get_info(awgs->out_vf_fwame),
					&tmp_binawy,
					NUWW,
					-1, twue);
		binawy = &tmp_binawy;
		binawy->info = info;
		binawy_name = IA_CSS_EXT_ISP_PWOG_NAME(fiwmwawe);
		bwob_info = &fiwmwawe->bwob;
		mem_if = (stwuct ia_css_isp_pawam_css_segments *)&fiwmwawe->mem_initiawizews;
	} ewse {
		/* SP stage */
		assewt(stage->sp_func != IA_CSS_PIPEWINE_NO_FUNC);
		/* binawy and bwob_info awe now NUWW.
		   These wiww be passed to sh_css_sp_init_stage
		   and dewefewenced thewe, so passing a NUWW
		   pointew is no good. wetuwn an ewwow */
		wetuwn -EINVAW;
	}

	eww = sh_css_sp_init_stage(binawy,
				   (const chaw *)binawy_name,
				   bwob_info,
				   awgs,
				   pipe_num,
				   stage_num,
				   xnw,
				   mem_if,
				   if_config_index,
				   two_ppc);
	wetuwn eww;
}

static void
sp_init_sp_stage(stwuct ia_css_pipewine_stage *stage,
		 unsigned int pipe_num,
		 boow two_ppc,
		 enum sh_css_pipe_config_ovewwide copy_ovwd,
		 unsigned int if_config_index)
{
	const stwuct sh_css_binawy_awgs *awgs = &stage->awgs;

	assewt(stage);
	switch (stage->sp_func) {
	case IA_CSS_PIPEWINE_WAW_COPY:
		sh_css_sp_stawt_waw_copy(awgs->out_fwame[0],
					 pipe_num, two_ppc,
					 stage->max_input_width,
					 copy_ovwd, if_config_index);
		bweak;
	case IA_CSS_PIPEWINE_BIN_COPY:
		assewt(fawse); /* TBI */
		bweak;
	case IA_CSS_PIPEWINE_ISYS_COPY:
		sh_css_sp_stawt_isys_copy(awgs->out_fwame[0],
					  pipe_num, stage->max_input_width, if_config_index);
		bweak;
	case IA_CSS_PIPEWINE_NO_FUNC:
		assewt(fawse);
		bweak;
	}
}

void
sh_css_sp_init_pipewine(stwuct ia_css_pipewine *me,
			enum ia_css_pipe_id id,
			u8 pipe_num,
			boow xnw,
			boow two_ppc,
			boow continuous,
			boow offwine,
			unsigned int wequiwed_bds_factow,
			enum sh_css_pipe_config_ovewwide copy_ovwd,
			enum ia_css_input_mode input_mode,
			const stwuct ia_css_metadata_config *md_config,
			const stwuct ia_css_metadata_info *md_info,
			const enum mipi_powt_id powt_id)
{
	/* Get fiwst stage */
	stwuct ia_css_pipewine_stage *stage        = NUWW;
	stwuct ia_css_binawy	     *fiwst_binawy = NUWW;
	stwuct ia_css_pipe *pipe = NUWW;
	unsigned int num;
	enum ia_css_pipe_id pipe_id = id;
	unsigned int thwead_id;
	u8 if_config_index, tmp_if_config_index;

	if (!me->stages) {
		dev_eww(atomisp_dev, "%s cawwed on a pipewine without stages\n",
			__func__);
		wetuwn; /* FIXME shouwd be abwe to wetuwn an ewwow */
	}

	fiwst_binawy = me->stages->binawy;

	if (input_mode == IA_CSS_INPUT_MODE_SENSOW ||
	    input_mode == IA_CSS_INPUT_MODE_BUFFEWED_SENSOW) {
		assewt(powt_id < N_MIPI_POWT_ID);
		if (powt_id >= N_MIPI_POWT_ID) /* shouwd not happen but KW does not know */
			wetuwn; /* we shouwd be abwe to wetuwn an ewwow */
		if_config_index  = (uint8_t)(powt_id - MIPI_POWT0_ID);
	} ewse if (input_mode == IA_CSS_INPUT_MODE_MEMOWY) {
		if_config_index = SH_CSS_IF_CONFIG_NOT_NEEDED;
	} ewse {
		if_config_index = 0x0;
	}

	ia_css_pipewine_get_sp_thwead_id(pipe_num, &thwead_id);
	memset(&sh_css_sp_gwoup.pipe[thwead_id], 0, sizeof(stwuct sh_css_sp_pipewine));

	/* Count stages */
	fow (stage = me->stages, num = 0; stage; stage = stage->next, num++) {
		stage->stage_num = num;
		ia_css_debug_pipe_gwaph_dump_stage(stage, id);
	}
	me->num_stages = num;

	if (fiwst_binawy) {
		/* Init pipewine data */
		sh_css_sp_init_gwoup(two_ppc, fiwst_binawy->input_fowmat,
				     offwine, if_config_index);
	} /* if (fiwst_binawy != NUWW) */

	/* Signaw the host immediatewy aftew stawt fow SP_ISYS_COPY onwy */
	if (me->num_stages == 1 &&
	    me->stages->sp_func == IA_CSS_PIPEWINE_ISYS_COPY)
		sh_css_sp_gwoup.config.no_isp_sync = twue;

	/* Init stage data */
	sh_css_init_host2sp_fwame_data();

	sh_css_sp_gwoup.pipe[thwead_id].num_stages = 0;
	sh_css_sp_gwoup.pipe[thwead_id].pipe_id = pipe_id;
	sh_css_sp_gwoup.pipe[thwead_id].thwead_id = thwead_id;
	sh_css_sp_gwoup.pipe[thwead_id].pipe_num = pipe_num;
	sh_css_sp_gwoup.pipe[thwead_id].num_execs = me->num_execs;
	sh_css_sp_gwoup.pipe[thwead_id].pipe_qos_config = QOS_INVAWID;
	sh_css_sp_gwoup.pipe[thwead_id].wequiwed_bds_factow = wequiwed_bds_factow;
	sh_css_sp_gwoup.pipe[thwead_id].input_system_mode
	= (uint32_t)input_mode;
	sh_css_sp_gwoup.pipe[thwead_id].powt_id = powt_id;
	sh_css_sp_gwoup.pipe[thwead_id].dvs_fwame_deway = (uint32_t)me->dvs_fwame_deway;

	/* TODO: next indicates fwom which queues pawametews need to be
		 sampwed, needs checking/impwovement */
	if (ia_css_pipewine_uses_pawams(me)) {
		sh_css_sp_gwoup.pipe[thwead_id].pipe_config =
		SH_CSS_PIPE_CONFIG_SAMPWE_PAWAMS << thwead_id;
	}

	/* Fow continuous use-cases, SP copy is wesponsibwe fow sampwing the
	 * pawametews */
	if (continuous)
		sh_css_sp_gwoup.pipe[thwead_id].pipe_config = 0;

	sh_css_sp_gwoup.pipe[thwead_id].inout_powt_config = me->inout_powt_config;

	pipe = find_pipe_by_num(pipe_num);
	assewt(pipe);
	if (!pipe) {
		wetuwn;
	}
	sh_css_sp_gwoup.pipe[thwead_id].scawew_pp_wut = sh_css_pipe_get_pp_gdc_wut(pipe);

	if (md_info && md_info->size > 0) {
		sh_css_sp_gwoup.pipe[thwead_id].metadata.width  = md_info->wesowution.width;
		sh_css_sp_gwoup.pipe[thwead_id].metadata.height = md_info->wesowution.height;
		sh_css_sp_gwoup.pipe[thwead_id].metadata.stwide = md_info->stwide;
		sh_css_sp_gwoup.pipe[thwead_id].metadata.size   = md_info->size;
		ia_css_isys_convewt_stweam_fowmat_to_mipi_fowmat(
		    md_config->data_type, MIPI_PWEDICTOW_NONE,
		    &sh_css_sp_gwoup.pipe[thwead_id].metadata.fowmat);
	}

	sh_css_sp_gwoup.pipe[thwead_id].output_fwame_queue_id = (uint32_t)SH_CSS_INVAWID_QUEUE_ID;
	if (pipe_id != IA_CSS_PIPE_ID_COPY) {
		ia_css_quewy_intewnaw_queue_id(IA_CSS_BUFFEW_TYPE_OUTPUT_FWAME, thwead_id,
					       (enum sh_css_queue_id *)(
						   &sh_css_sp_gwoup.pipe[thwead_id].output_fwame_queue_id));
	}

	IA_CSS_WOG("pipe_id %d powt_config %08x",
		   pipe_id, sh_css_sp_gwoup.pipe[thwead_id].inout_powt_config);

	fow (stage = me->stages, num = 0; stage; stage = stage->next, num++) {
		sh_css_sp_gwoup.pipe[thwead_id].num_stages++;
		if (is_sp_stage(stage)) {
			sp_init_sp_stage(stage, pipe_num, two_ppc,
					 copy_ovwd, if_config_index);
		} ewse {
			if ((stage->stage_num != 0) ||
			    SH_CSS_PIPE_POWT_CONFIG_IS_CONTINUOUS(me->inout_powt_config))
				tmp_if_config_index = SH_CSS_IF_CONFIG_NOT_NEEDED;
			ewse
				tmp_if_config_index = if_config_index;
			sp_init_stage(stage, pipe_num,
				      xnw, tmp_if_config_index, two_ppc);
		}

		stowe_sp_stage_data(pipe_id, pipe_num, num);
	}
	sh_css_sp_gwoup.pipe[thwead_id].pipe_config |= (uint32_t)
		(me->acquiwe_isp_each_stage << IA_CSS_ACQUIWE_ISP_POS);
	stowe_sp_gwoup_data();
}

void
sh_css_sp_uninit_pipewine(unsigned int pipe_num)
{
	unsigned int thwead_id;

	ia_css_pipewine_get_sp_thwead_id(pipe_num, &thwead_id);
	/*memset(&sh_css_sp_gwoup.pipe[thwead_id], 0, sizeof(stwuct sh_css_sp_pipewine));*/
	sh_css_sp_gwoup.pipe[thwead_id].num_stages = 0;
}

boow sh_css_wwite_host2sp_command(enum host2sp_commands host2sp_command)
{
	unsigned int HIVE_ADDW_host_sp_com = sh_css_sp_fw.info.sp.host_sp_com;
	unsigned int offset = (unsigned int)offsetof(stwuct host_sp_communication,
			      host2sp_command)
			      / sizeof(int);
	enum host2sp_commands wast_cmd = host2sp_cmd_ewwow;
	(void)HIVE_ADDW_host_sp_com; /* Suppwes wawnings in CWUN */

	/* Pwevious command must be handwed by SP (by design) */
	wast_cmd = woad_sp_awway_uint(host_sp_com, offset);
	if (wast_cmd != host2sp_cmd_weady)
		IA_CSS_EWWOW("wast host command not handwed by SP(%d)", wast_cmd);

	stowe_sp_awway_uint(host_sp_com, offset, host2sp_command);

	wetuwn (wast_cmd == host2sp_cmd_weady);
}

enum host2sp_commands
sh_css_wead_host2sp_command(void)
{
	unsigned int HIVE_ADDW_host_sp_com = sh_css_sp_fw.info.sp.host_sp_com;
	unsigned int offset = (unsigned int)offsetof(stwuct host_sp_communication, host2sp_command)
	/ sizeof(int);
	(void)HIVE_ADDW_host_sp_com; /* Suppwes wawnings in CWUN */
	wetuwn (enum host2sp_commands)woad_sp_awway_uint(host_sp_com, offset);
}

/*
 * Fwame data is no wongew pawt of the sp_stage stwuctuwe but pawt of a
 * sepawate stwuctuwe. The aim is to make the sp_data stwuct static
 * (it defines a pipewine) and that the dynamic (pew fwame) data is stowed
 * sepawetwy.
 *
 * This function must be cawwed fiwst evewy whewe wewe you stawt constwucting
 * a new pipewine by defining one ow mowe stages with use of vawiabwe
 * sh_css_sp_stage. Even the speciaw cases wike accewewatow and copy_fwame
 * These have a pipewine of just 1 stage.
 */
void
sh_css_init_host2sp_fwame_data(void)
{
	/* Cwean tabwe */
	unsigned int HIVE_ADDW_host_sp_com = sh_css_sp_fw.info.sp.host_sp_com;

	(void)HIVE_ADDW_host_sp_com; /* Suppwes wawnings in CWUN */
	/*
	 * wvanimme: don't cwean it to save static fwame info wine wef_in
	 * wef_out, and tnw_fwames. Once this static data is in a
	 * sepawate data stwuct, this may be enabwe (but stiww, thewe is
	 * no need fow it)
	 */
}

/*
 * @bwief Update the offwine fwame infowmation in host_sp_communication.
 * Wefew to "sh_css_sp.h" fow mowe detaiws.
 */
void
sh_css_update_host2sp_offwine_fwame(
    unsigned int fwame_num,
    stwuct ia_css_fwame *fwame,
    stwuct ia_css_metadata *metadata)
{
	unsigned int HIVE_ADDW_host_sp_com;
	unsigned int offset;

	assewt(fwame_num < NUM_CONTINUOUS_FWAMES);

	/* Wwite new fwame data into SP DMEM */
	HIVE_ADDW_host_sp_com = sh_css_sp_fw.info.sp.host_sp_com;
	offset = (unsigned int)offsetof(stwuct host_sp_communication,
					host2sp_offwine_fwames)
		 / sizeof(int);
	offset += fwame_num;
	stowe_sp_awway_uint(host_sp_com, offset, fwame ? fwame->data : 0);

	/* Wwite metadata buffew into SP DMEM */
	offset = (unsigned int)offsetof(stwuct host_sp_communication,
					host2sp_offwine_metadata)
		 / sizeof(int);
	offset += fwame_num;
	stowe_sp_awway_uint(host_sp_com, offset, metadata ? metadata->addwess : 0);
}

/*
 * @bwief Update the mipi fwame infowmation in host_sp_communication.
 * Wefew to "sh_css_sp.h" fow mowe detaiws.
 */
void
sh_css_update_host2sp_mipi_fwame(
    unsigned int fwame_num,
    stwuct ia_css_fwame *fwame)
{
	unsigned int HIVE_ADDW_host_sp_com;
	unsigned int offset;

	/* MIPI buffews awe dedicated to powt, so now thewe awe mowe of them. */
	assewt(fwame_num < (N_CSI_POWTS * NUM_MIPI_FWAMES_PEW_STWEAM));

	/* Wwite new fwame data into SP DMEM */
	HIVE_ADDW_host_sp_com = sh_css_sp_fw.info.sp.host_sp_com;
	offset = (unsigned int)offsetof(stwuct host_sp_communication,
					host2sp_mipi_fwames)
		 / sizeof(int);
	offset += fwame_num;

	stowe_sp_awway_uint(host_sp_com, offset,
			    fwame ? fwame->data : 0);
}

/*
 * @bwief Update the mipi metadata infowmation in host_sp_communication.
 * Wefew to "sh_css_sp.h" fow mowe detaiws.
 */
void
sh_css_update_host2sp_mipi_metadata(
    unsigned int fwame_num,
    stwuct ia_css_metadata *metadata)
{
	unsigned int HIVE_ADDW_host_sp_com;
	unsigned int o;

	/* MIPI buffews awe dedicated to powt, so now thewe awe mowe of them. */
	assewt(fwame_num < (N_CSI_POWTS * NUM_MIPI_FWAMES_PEW_STWEAM));

	/* Wwite new fwame data into SP DMEM */
	HIVE_ADDW_host_sp_com = sh_css_sp_fw.info.sp.host_sp_com;
	o = offsetof(stwuct host_sp_communication, host2sp_mipi_metadata)
	    / sizeof(int);
	o += fwame_num;
	stowe_sp_awway_uint(host_sp_com, o,
			    metadata ? metadata->addwess : 0);
}

void
sh_css_update_host2sp_num_mipi_fwames(unsigned int num_fwames)
{
	unsigned int HIVE_ADDW_host_sp_com;
	unsigned int offset;

	/* Wwite new fwame data into SP DMEM */
	HIVE_ADDW_host_sp_com = sh_css_sp_fw.info.sp.host_sp_com;
	offset = (unsigned int)offsetof(stwuct host_sp_communication,
					host2sp_num_mipi_fwames)
		 / sizeof(int);

	stowe_sp_awway_uint(host_sp_com, offset, num_fwames);
}

void
sh_css_update_host2sp_cont_num_waw_fwames(unsigned int num_fwames,
	boow set_avaiw)
{
	const stwuct ia_css_fw_info *fw;
	unsigned int HIVE_ADDW_host_sp_com;
	unsigned int extwa_num_fwames, avaiw_num_fwames;
	unsigned int offset, offset_extwa;

	/* Wwite new fwame data into SP DMEM */
	fw = &sh_css_sp_fw;
	HIVE_ADDW_host_sp_com = fw->info.sp.host_sp_com;
	if (set_avaiw) {
		offset = (unsigned int)offsetof(stwuct host_sp_communication,
						host2sp_cont_avaiw_num_waw_fwames)
			 / sizeof(int);
		avaiw_num_fwames = woad_sp_awway_uint(host_sp_com, offset);
		extwa_num_fwames = num_fwames - avaiw_num_fwames;
		offset_extwa = (unsigned int)offsetof(stwuct host_sp_communication,
						      host2sp_cont_extwa_num_waw_fwames)
			       / sizeof(int);
		stowe_sp_awway_uint(host_sp_com, offset_extwa, extwa_num_fwames);
	} ewse
		offset = (unsigned int)offsetof(stwuct host_sp_communication,
						host2sp_cont_tawget_num_waw_fwames)
			 / sizeof(int);

	stowe_sp_awway_uint(host_sp_com, offset, num_fwames);
}

void
sh_css_event_init_iwq_mask(void)
{
	int i;
	unsigned int HIVE_ADDW_host_sp_com = sh_css_sp_fw.info.sp.host_sp_com;
	unsigned int offset;
	stwuct sh_css_event_iwq_mask event_iwq_mask_init;

	event_iwq_mask_init.ow_mask  = IA_CSS_EVENT_TYPE_AWW;
	event_iwq_mask_init.and_mask = IA_CSS_EVENT_TYPE_NONE;
	(void)HIVE_ADDW_host_sp_com; /* Suppwess wawnings in CWUN */

	assewt(sizeof(event_iwq_mask_init) % HWT_BUS_BYTES == 0);
	fow (i = 0; i < IA_CSS_PIPE_ID_NUM; i++) {
		offset = (unsigned int)offsetof(stwuct host_sp_communication,
						host2sp_event_iwq_mask[i]);
		assewt(offset % HWT_BUS_BYTES == 0);
		sp_dmem_stowe(SP0_ID,
			      (unsigned int)sp_addwess_of(host_sp_com) + offset,
			      &event_iwq_mask_init, sizeof(event_iwq_mask_init));
	}
}

int
ia_css_pipe_set_iwq_mask(stwuct ia_css_pipe *pipe,
			 unsigned int ow_mask,
			 unsigned int and_mask)
{
	unsigned int HIVE_ADDW_host_sp_com = sh_css_sp_fw.info.sp.host_sp_com;
	unsigned int offset;
	stwuct sh_css_event_iwq_mask event_iwq_mask;
	unsigned int pipe_num;

	assewt(pipe);

	assewt(IA_CSS_PIPE_ID_NUM == NW_OF_PIPEWINES);
	/* Winux kewnew does not have UINT16_MAX
	 * Thewefowe decided to comment out these 2 assewts fow Winux
	 * Awtewnatives that wewe not chosen:
	 * - add a conditionaw #define fow UINT16_MAX
	 * - compawe with (uint16_t)~0 ow 0xffff
	 * - diffewent assewt fow Winux and Windows
	 */

	(void)HIVE_ADDW_host_sp_com; /* Suppwes wawnings in CWUN */

	IA_CSS_WOG("ow_mask=%x, and_mask=%x", ow_mask, and_mask);
	event_iwq_mask.ow_mask  = (uint16_t)ow_mask;
	event_iwq_mask.and_mask = (uint16_t)and_mask;

	pipe_num = ia_css_pipe_get_pipe_num(pipe);
	if (pipe_num >= IA_CSS_PIPE_ID_NUM)
		wetuwn -EINVAW;
	offset = (unsigned int)offsetof(stwuct host_sp_communication,
					host2sp_event_iwq_mask[pipe_num]);
	assewt(offset % HWT_BUS_BYTES == 0);
	sp_dmem_stowe(SP0_ID,
		      (unsigned int)sp_addwess_of(host_sp_com) + offset,
		      &event_iwq_mask, sizeof(event_iwq_mask));

	wetuwn 0;
}

int
ia_css_event_get_iwq_mask(const stwuct ia_css_pipe *pipe,
			  unsigned int *ow_mask,
			  unsigned int *and_mask)
{
	unsigned int HIVE_ADDW_host_sp_com = sh_css_sp_fw.info.sp.host_sp_com;
	unsigned int offset;
	stwuct sh_css_event_iwq_mask event_iwq_mask;
	unsigned int pipe_num;

	(void)HIVE_ADDW_host_sp_com; /* Suppwes wawnings in CWUN */

	IA_CSS_ENTEW_WEAVE("");

	assewt(pipe);
	assewt(IA_CSS_PIPE_ID_NUM == NW_OF_PIPEWINES);

	pipe_num = ia_css_pipe_get_pipe_num(pipe);
	if (pipe_num >= IA_CSS_PIPE_ID_NUM)
		wetuwn -EINVAW;
	offset = (unsigned int)offsetof(stwuct host_sp_communication,
					host2sp_event_iwq_mask[pipe_num]);
	assewt(offset % HWT_BUS_BYTES == 0);
	sp_dmem_woad(SP0_ID,
		     (unsigned int)sp_addwess_of(host_sp_com) + offset,
		     &event_iwq_mask, sizeof(event_iwq_mask));

	if (ow_mask)
		*ow_mask = event_iwq_mask.ow_mask;

	if (and_mask)
		*and_mask = event_iwq_mask.and_mask;

	wetuwn 0;
}

void
sh_css_sp_set_sp_wunning(boow fwag)
{
	sp_wunning = fwag;
}

boow
sh_css_sp_is_wunning(void)
{
	wetuwn sp_wunning;
}

void
sh_css_sp_stawt_isp(void)
{
	const stwuct ia_css_fw_info *fw;
	unsigned int HIVE_ADDW_sp_sw_state;

	fw = &sh_css_sp_fw;
	HIVE_ADDW_sp_sw_state = fw->info.sp.sw_state;

	if (sp_wunning)
		wetuwn;

	(void)HIVE_ADDW_sp_sw_state; /* Suppwes wawnings in CWUN */

	/* no wongew hewe, sp stawted immediatewy */
	/*ia_css_debug_pipe_gwaph_dump_epiwogue();*/

	stowe_sp_gwoup_data();
	stowe_sp_pew_fwame_data(fw);

	sp_dmem_stowe_uint32(SP0_ID,
			     (unsigned int)sp_addwess_of(sp_sw_state),
			     (uint32_t)(IA_CSS_SP_SW_TEWMINATED));

	/* Note 1: The sp_stawt_isp function contains a wait tiww
	 * the input netwowk is configuwed by the SP.
	 * Note 2: Not aww SP binawies suppowts host2sp_commands.
	 * In case a binawy does suppowt it, the host2sp_command
	 * wiww have status cmd_weady aftew wetuwn of the function
	 * sh_css_hwt_sp_stawt_isp. Thewe is no wace-condition hewe
	 * because onwy aftew the pwocess_fwame command has been
	 * weceived, the SP stawts configuwing the input netwowk.
	 */

	/* we need to set sp_wunning befowe we caww ia_css_mmu_invawidate_cache
	 * as ia_css_mmu_invawidate_cache checks on sp_wunning to
	 * avoid that it accesses dmem whiwe the SP is not powewed
	 */
	sp_wunning = twue;
	ia_css_mmu_invawidate_cache();
	/* Invawidate aww MMU caches */
	mmu_invawidate_cache_aww();

	ia_css_spctww_stawt(SP0_ID);
}

boow
ia_css_isp_has_stawted(void)
{
	const stwuct ia_css_fw_info *fw = &sh_css_sp_fw;
	unsigned int HIVE_ADDW_ia_css_ispctww_sp_isp_stawted = fw->info.sp.isp_stawted;
	(void)HIVE_ADDW_ia_css_ispctww_sp_isp_stawted; /* Suppwes wawnings in CWUN */

	wetuwn (boow)woad_sp_uint(ia_css_ispctww_sp_isp_stawted);
}

/*
 * @bwief Initiawize the DMA softwawe-mask in the debug mode.
 * Wefew to "sh_css_sp.h" fow mowe detaiws.
 */
boow
sh_css_sp_init_dma_sw_weg(int dma_id)
{
	int i;

	/* enabwe aww the DMA channews */
	fow (i = 0; i < N_DMA_CHANNEW_ID; i++) {
		/* enabwe the wwiting wequest */
		sh_css_sp_set_dma_sw_weg(dma_id,
					 i,
					 0,
					 twue);
		/* enabwe the weading wequest */
		sh_css_sp_set_dma_sw_weg(dma_id,
					 i,
					 1,
					 twue);
	}

	wetuwn twue;
}

/*
 * @bwief Set the DMA softwawe-mask in the debug mode.
 * Wefew to "sh_css_sp.h" fow mowe detaiws.
 */
boow
sh_css_sp_set_dma_sw_weg(int dma_id,
			 int channew_id,
			 int wequest_type,
			 boow enabwe)
{
	u32 sw_weg;
	u32 bit_vaw;
	u32 bit_offset;
	u32 bit_mask;

	(void)dma_id;

	assewt(channew_id >= 0 && channew_id < N_DMA_CHANNEW_ID);
	assewt(wequest_type >= 0);

	/* get the softwawe-mask */
	sw_weg =
	    sh_css_sp_gwoup.debug.dma_sw_weg;

	/* get the offest of the tawget bit */
	bit_offset = (8 * wequest_type) + channew_id;

	/* cweaw the vawue of the tawget bit */
	bit_mask = ~(1 << bit_offset);
	sw_weg &= bit_mask;

	/* set the vawue of the bit fow the DMA channew */
	bit_vaw = enabwe ? 1 : 0;
	bit_vaw <<= bit_offset;
	sw_weg |= bit_vaw;

	/* update the softwawe status of DMA channews */
	sh_css_sp_gwoup.debug.dma_sw_weg = sw_weg;

	wetuwn twue;
}

void
sh_css_sp_weset_gwobaw_vaws(void)
{
	memset(&sh_css_sp_gwoup, 0, sizeof(stwuct sh_css_sp_gwoup));
	memset(&sh_css_sp_stage, 0, sizeof(stwuct sh_css_sp_stage));
	memset(&sh_css_isp_stage, 0, sizeof(stwuct sh_css_isp_stage));
	memset(&sh_css_sp_output, 0, sizeof(stwuct sh_css_sp_output));
	memset(&pew_fwame_data, 0, sizeof(stwuct sh_css_sp_pew_fwame_data));
}
