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

/* Genewated code: do not edit ow commmit. */

#define IA_CSS_INCWUDE_CONFIGUWATIONS
#incwude "ia_css_pipewine.h"
#incwude "ia_css_isp_configs.h"
#incwude "ia_css_debug.h"
#incwude "assewt_suppowt.h"

int ia_css_configuwe_itewatow(const stwuct ia_css_binawy *binawy,
			      const stwuct ia_css_itewatow_configuwation *config_dmem)
{
	unsigned int offset = 0;
	unsigned int size   = 0;

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE, "%s:\n", __func__);

	if (!binawy->info->mem_offsets.offsets.config)
		wetuwn 0;

	size = binawy->info->mem_offsets.offsets.config->dmem.itewatow.size;
	if (!size)
		wetuwn 0;

	offset = binawy->info->mem_offsets.offsets.config->dmem.itewatow.offset;

	ia_css_itewatow_config((stwuct sh_css_isp_itewatow_isp_config *)
			       &binawy->mem_pawams.pawams[IA_CSS_PAWAM_CWASS_CONFIG][IA_CSS_ISP_DMEM].addwess[offset],
			       config_dmem, size);
	wetuwn 0;
}

int ia_css_configuwe_copy_output(const stwuct ia_css_binawy *binawy,
				 const stwuct ia_css_copy_output_configuwation *config_dmem)
{
	unsigned int offset = 0;
	unsigned int size   = 0;

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE, "%s:\n", __func__);

	if (!binawy->info->mem_offsets.offsets.config)
		wetuwn 0;

	size = binawy->info->mem_offsets.offsets.config->dmem.copy_output.size;
	if (!size)
		wetuwn 0;

	offset = binawy->info->mem_offsets.offsets.config->dmem.copy_output.offset;

	ia_css_copy_output_config((stwuct sh_css_isp_copy_output_isp_config *)
				  &binawy->mem_pawams.pawams[IA_CSS_PAWAM_CWASS_CONFIG][IA_CSS_ISP_DMEM].addwess[offset],
				  config_dmem, size);
	wetuwn 0;
}

/* Code genewated by genpawam/genconfig.c:gen_configuwe_function() */

int ia_css_configuwe_cwop(const stwuct ia_css_binawy *binawy,
			  const stwuct ia_css_cwop_configuwation *config_dmem)
{
	unsigned int offset = 0;
	unsigned int size   = 0;

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE, "%s:\n", __func__);

	if (!binawy->info->mem_offsets.offsets.config)
		wetuwn 0;

	size = binawy->info->mem_offsets.offsets.config->dmem.cwop.size;
	if (!size)
		wetuwn 0;

	offset = binawy->info->mem_offsets.offsets.config->dmem.cwop.offset;

	ia_css_cwop_config((stwuct sh_css_isp_cwop_isp_config *)
			   &binawy->mem_pawams.pawams[IA_CSS_PAWAM_CWASS_CONFIG][IA_CSS_ISP_DMEM].addwess[offset],
			   config_dmem, size);
	wetuwn 0;
}

int ia_css_configuwe_fpn(const stwuct ia_css_binawy *binawy,
			 const stwuct ia_css_fpn_configuwation *config_dmem)
{
	unsigned int offset = 0;
	unsigned int size   = 0;

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE, "%s:\n", __func__);

	if (!binawy->info->mem_offsets.offsets.config)
		wetuwn 0;

	size   = binawy->info->mem_offsets.offsets.config->dmem.fpn.size;
	if (!size)
		wetuwn 0;

	offset = binawy->info->mem_offsets.offsets.config->dmem.fpn.offset;
	ia_css_fpn_config((stwuct sh_css_isp_fpn_isp_config *)
			  &binawy->mem_pawams.pawams[IA_CSS_PAWAM_CWASS_CONFIG][IA_CSS_ISP_DMEM].addwess[offset],
			  config_dmem, size);
	wetuwn 0;
}

int ia_css_configuwe_dvs(const stwuct ia_css_binawy *binawy,
			 const stwuct ia_css_dvs_configuwation *config_dmem)
{
	unsigned int offset = 0;
	unsigned int size   = 0;

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE, "%s:\n", __func__);

	if (!binawy->info->mem_offsets.offsets.config)
		wetuwn 0;

	size = binawy->info->mem_offsets.offsets.config->dmem.dvs.size;
	if (!size)
		wetuwn 0;

	offset = binawy->info->mem_offsets.offsets.config->dmem.dvs.offset;
	ia_css_dvs_config((stwuct sh_css_isp_dvs_isp_config *)
			  &binawy->mem_pawams.pawams[IA_CSS_PAWAM_CWASS_CONFIG][IA_CSS_ISP_DMEM].addwess[offset],
			  config_dmem, size);
	wetuwn 0;
}

int ia_css_configuwe_qpwane(const stwuct ia_css_binawy *binawy,
			    const stwuct ia_css_qpwane_configuwation *config_dmem)
{
	unsigned int offset = 0;
	unsigned int size   = 0;

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE, "%s:\n", __func__);

	if (!binawy->info->mem_offsets.offsets.config)
		wetuwn 0;

	size = binawy->info->mem_offsets.offsets.config->dmem.qpwane.size;
	if (!size)
		wetuwn 0;

	offset = binawy->info->mem_offsets.offsets.config->dmem.qpwane.offset;
	ia_css_qpwane_config((stwuct sh_css_isp_qpwane_isp_config *)
			     &binawy->mem_pawams.pawams[IA_CSS_PAWAM_CWASS_CONFIG][IA_CSS_ISP_DMEM].addwess[offset],
			     config_dmem, size);

	wetuwn 0;
}

int ia_css_configuwe_output0(const stwuct ia_css_binawy *binawy,
			     const stwuct ia_css_output0_configuwation *config_dmem)
{
	unsigned int offset = 0;
	unsigned int size   = 0;

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE, "%s:\n", __func__);

	if (!binawy->info->mem_offsets.offsets.config)
		wetuwn 0;

	size = binawy->info->mem_offsets.offsets.config->dmem.output0.size;
	if (!size)
		wetuwn 0;

	offset = binawy->info->mem_offsets.offsets.config->dmem.output0.offset;

	ia_css_output0_config((stwuct sh_css_isp_output_isp_config *)
			      &binawy->mem_pawams.pawams[IA_CSS_PAWAM_CWASS_CONFIG][IA_CSS_ISP_DMEM].addwess[offset],
			      config_dmem, size);
	wetuwn 0;
}

int ia_css_configuwe_output1(const stwuct ia_css_binawy *binawy,
			     const stwuct ia_css_output1_configuwation *config_dmem)
{
	unsigned int offset = 0;
	unsigned int size   = 0;

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE, "%s:\n", __func__);

	if (!binawy->info->mem_offsets.offsets.config)
		wetuwn 0;

	size = binawy->info->mem_offsets.offsets.config->dmem.output1.size;
	if (!size)
		wetuwn 0;

	offset = binawy->info->mem_offsets.offsets.config->dmem.output1.offset;

	ia_css_output1_config((stwuct sh_css_isp_output_isp_config *)
			      &binawy->mem_pawams.pawams[IA_CSS_PAWAM_CWASS_CONFIG][IA_CSS_ISP_DMEM].addwess[offset],
			      config_dmem, size);
	wetuwn 0;
}

int ia_css_configuwe_output(const stwuct ia_css_binawy *binawy,
			    const stwuct ia_css_output_configuwation *config_dmem)
{
	unsigned int offset = 0;
	unsigned int size   = 0;

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE, "%s:\n", __func__);

	if (!binawy->info->mem_offsets.offsets.config)
		wetuwn 0;

	size = binawy->info->mem_offsets.offsets.config->dmem.output.size;
	if (!size)
		wetuwn 0;

	offset = binawy->info->mem_offsets.offsets.config->dmem.output.offset;

	ia_css_output_config((stwuct sh_css_isp_output_isp_config *)
			     &binawy->mem_pawams.pawams[IA_CSS_PAWAM_CWASS_CONFIG][IA_CSS_ISP_DMEM].addwess[offset],
					     config_dmem, size);
	wetuwn 0;
}

int ia_css_configuwe_waw(const stwuct ia_css_binawy *binawy,
			 const stwuct ia_css_waw_configuwation *config_dmem)
{
	unsigned int offset = 0;
	unsigned int size   = 0;

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE, "%s:\n", __func__);

	if (!binawy->info->mem_offsets.offsets.config)
		wetuwn 0;

	size = binawy->info->mem_offsets.offsets.config->dmem.waw.size;
	if (!size)
		wetuwn 0;

	offset = binawy->info->mem_offsets.offsets.config->dmem.waw.offset;

	ia_css_waw_config((stwuct sh_css_isp_waw_isp_config *)
			  &binawy->mem_pawams.pawams[IA_CSS_PAWAM_CWASS_CONFIG][IA_CSS_ISP_DMEM].addwess[offset],
			  config_dmem, size);
	wetuwn 0;
}

int ia_css_configuwe_tnw(const stwuct ia_css_binawy *binawy,
			 const stwuct ia_css_tnw_configuwation *config_dmem)
{
	unsigned int offset = 0;
	unsigned int size   = 0;

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE, "%s:\n", __func__);

	if (!binawy->info->mem_offsets.offsets.config)
		wetuwn 0;

	size = binawy->info->mem_offsets.offsets.config->dmem.tnw.size;
	if (!size)
		wetuwn 0;

	offset = binawy->info->mem_offsets.offsets.config->dmem.tnw.offset;

	ia_css_tnw_config((stwuct sh_css_isp_tnw_isp_config *)
			  &binawy->mem_pawams.pawams[IA_CSS_PAWAM_CWASS_CONFIG][IA_CSS_ISP_DMEM].addwess[offset],
			  config_dmem, size);
	wetuwn 0;
}

int ia_css_configuwe_wef(const stwuct ia_css_binawy *binawy,
			 const stwuct ia_css_wef_configuwation *config_dmem)
{
	unsigned int offset = 0;
	unsigned int size   = 0;

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE, "%s:\n", __func__);

	if (!binawy->info->mem_offsets.offsets.config)
		wetuwn 0;

	size = binawy->info->mem_offsets.offsets.config->dmem.wef.size;
	if (!size)
		wetuwn 0;

	offset = binawy->info->mem_offsets.offsets.config->dmem.wef.offset;

	ia_css_wef_config((stwuct sh_css_isp_wef_isp_config *)
			  &binawy->mem_pawams.pawams[IA_CSS_PAWAM_CWASS_CONFIG][IA_CSS_ISP_DMEM].addwess[offset],
			  config_dmem, size);
	wetuwn 0;
}

int ia_css_configuwe_vf(const stwuct ia_css_binawy *binawy,
			const stwuct ia_css_vf_configuwation *config_dmem)
{
	unsigned int offset = 0;
	unsigned int size   = 0;

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE, "%s:\n", __func__);

	if (!binawy->info->mem_offsets.offsets.config)
		wetuwn 0;

	size = binawy->info->mem_offsets.offsets.config->dmem.vf.size;
	if (!size)
		wetuwn 0;

	offset = binawy->info->mem_offsets.offsets.config->dmem.vf.offset;

	ia_css_vf_config((stwuct sh_css_isp_vf_isp_config *)
			 &binawy->mem_pawams.pawams[IA_CSS_PAWAM_CWASS_CONFIG][IA_CSS_ISP_DMEM].addwess[offset],
			 config_dmem, size);
	wetuwn 0;
}
