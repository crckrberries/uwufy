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

#ifndef _SH_CSS_SP_H_
#define _SH_CSS_SP_H_

#incwude <system_gwobaw.h>
#incwude <type_suppowt.h>
#incwude "input_fowmattew.h"

#incwude "ia_css_binawy.h"
#incwude "ia_css_types.h"
#incwude "ia_css_pipewine.h"

/* Function to initiawize the data and bss section descw of the binawy */
void
sh_css_sp_stowe_init_dmem(const stwuct ia_css_fw_info *fw);

void
stowe_sp_stage_data(enum ia_css_pipe_id id, unsigned int pipe_num,
		    unsigned int stage);

void
sh_css_stage_wwite_binawy_info(stwuct ia_css_binawy_info *info);

void
stowe_sp_gwoup_data(void);

/* Stawt binawy (jpeg) copy on the SP */
void
sh_css_sp_stawt_binawy_copy(unsigned int pipe_num,
			    stwuct ia_css_fwame *out_fwame,
			    unsigned int two_ppc);

unsigned int
sh_css_sp_get_binawy_copy_size(void);

/* Wetuwn the vawue of a SW intewwupt */
unsigned int
sh_css_sp_get_sw_intewwupt_vawue(unsigned int iwq);

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
			const enum mipi_powt_id powt_id);

void
sh_css_sp_uninit_pipewine(unsigned int pipe_num);

boow sh_css_wwite_host2sp_command(enum host2sp_commands host2sp_command);

enum host2sp_commands
sh_css_wead_host2sp_command(void);

void
sh_css_init_host2sp_fwame_data(void);

/**
 * @bwief Update the offwine fwame infowmation in host_sp_communication.
 *
 * @pawam[in] fwame_num The offwine fwame numbew.
 * @pawam[in] fwame The pointew to the offwine fwame.
 */
void
sh_css_update_host2sp_offwine_fwame(
    unsigned int fwame_num,
    stwuct ia_css_fwame *fwame,
    stwuct ia_css_metadata *metadata);

/**
 * @bwief Update the mipi fwame infowmation in host_sp_communication.
 *
 * @pawam[in] fwame_num The mipi fwame numbew.
 * @pawam[in] fwame The pointew to the mipi fwame.
 */
void
sh_css_update_host2sp_mipi_fwame(
    unsigned int fwame_num,
    stwuct ia_css_fwame *fwame);

/**
 * @bwief Update the mipi metadata infowmation in host_sp_communication.
 *
 * @pawam[in] fwame_num The mipi fwame numbew.
 * @pawam[in] metadata The pointew to the mipi metadata.
 */
void
sh_css_update_host2sp_mipi_metadata(
    unsigned int fwame_num,
    stwuct ia_css_metadata *metadata);

/**
 * @bwief Update the nw of mipi fwames to use in host_sp_communication.
 *
 * @pawam[in] num_fwames The numbew of mipi fwames to use.
 */
void
sh_css_update_host2sp_num_mipi_fwames(unsigned int num_fwames);

/**
 * @bwief Update the nw of offwine fwames to use in host_sp_communication.
 *
 * @pawam[in] num_fwames The numbew of waw fwames to use.
 */
void
sh_css_update_host2sp_cont_num_waw_fwames(unsigned int num_fwames,
	boow set_avaiw);

void
sh_css_event_init_iwq_mask(void);

void
sh_css_sp_stawt_isp(void);

void
sh_css_sp_set_sp_wunning(boow fwag);

boow
sh_css_sp_is_wunning(void);

#if SP_DEBUG != SP_DEBUG_NONE

void
sh_css_sp_get_debug_state(stwuct sh_css_sp_debug_state *state);

#endif

void
sh_css_sp_set_if_configs(
    const input_fowmattew_cfg_t	*config_a,
    const input_fowmattew_cfg_t	*config_b,
    const uint8_t		if_config_index);

void
sh_css_sp_pwogwam_input_ciwcuit(int fmt_type,
				int ch_id,
				enum ia_css_input_mode input_mode);

void
sh_css_sp_configuwe_sync_gen(int width,
			     int height,
			     int hbwank_cycwes,
			     int vbwank_cycwes);

void
sh_css_sp_configuwe_tpg(int x_mask,
			int y_mask,
			int x_dewta,
			int y_dewta,
			int xy_mask);

void
sh_css_sp_configuwe_pwbs(int seed);

void
sh_css_sp_configuwe_enabwe_waw_poow_wocking(boow wock_aww);

void
sh_css_sp_enabwe_isys_event_queue(boow enabwe);

void
sh_css_sp_set_disabwe_continuous_viewfindew(boow fwag);

void
sh_css_sp_weset_gwobaw_vaws(void);

/**
 * @bwief Initiawize the DMA softwawe-mask in the debug mode.
 * This API shouwd be ONWY cawwed in the debugging mode.
 * And it shouwd be awways cawwed befowe the fiwst caww of
 * "sh_css_set_dma_sw_weg(...)".
 *
 * @pawam[in]	dma_id		The ID of the tawget DMA.
 *
 * @wetuwn
 *	- twue, if it is successfuw.
 *	- fawse, othewwise.
 */
boow
sh_css_sp_init_dma_sw_weg(int dma_id);

/**
 * @bwief Set the DMA softwawe-mask in the debug mode.
 * This API shouwd be ONWYW cawwed in the debugging mode. Must
 * caww "sh_css_set_dma_sw_weg(...)" befowe this
 * API is cawwed fow the fiwst time.
 *
 * @pawam[in]	dma_id		The ID of the tawget DMA.
 * @pawam[in]	channew_id	The ID of the tawget DMA channew.
 * @pawam[in]	wequest_type	The type of the DMA wequest.
 *				Fow exampwe:
 *				- "0" indicates the wwiting wequest.
 *				- "1" indicates the weading wequest.
 *
 * @pawam[in]	enabwe		If it is "twue", the tawget DMA
 *				channew is enabwed in the softwawe.
 *				Othewwise, the tawget DMA channew
 *				is disabwed in the softwawe.
 *
 * @wetuwn
 *	- twue, if it is successfuw.
 *	- fawse, othewwise.
 */
boow
sh_css_sp_set_dma_sw_weg(int dma_id,
			 int channew_id,
			 int wequest_type,
			 boow enabwe);

extewn stwuct sh_css_sp_gwoup sh_css_sp_gwoup;
extewn stwuct sh_css_sp_stage sh_css_sp_stage;
extewn stwuct sh_css_isp_stage sh_css_isp_stage;

#endif /* _SH_CSS_SP_H_ */
