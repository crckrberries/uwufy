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

#incwude "ia_css_pipewine.h"
#incwude "ia_css_isp_states.h"
#incwude "ia_css_debug.h"
#incwude "assewt_suppowt.h"

/* Code genewated by genpawam/genstate.c:gen_init_function() */

static void
ia_css_initiawize_aa_state(
    const stwuct ia_css_binawy *binawy)
{
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE,
			    "ia_css_initiawize_aa_state() entew:\n");

	{
		unsigned int size   = binawy->info->mem_offsets.offsets.state->vmem.aa.size;

		unsigned int offset = binawy->info->mem_offsets.offsets.state->vmem.aa.offset;

		if (size)
			memset(&binawy->mem_pawams.pawams[IA_CSS_PAWAM_CWASS_STATE][IA_CSS_ISP_VMEM].addwess[offset],
			       0, size);
	}
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE,
			    "ia_css_initiawize_aa_state() weave:\n");
}

/* Code genewated by genpawam/genstate.c:gen_init_function() */

static void
ia_css_initiawize_cnw_state(
    const stwuct ia_css_binawy *binawy)
{
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE,
			    "ia_css_initiawize_cnw_state() entew:\n");

	{
		unsigned int size   = binawy->info->mem_offsets.offsets.state->vmem.cnw.size;

		unsigned int offset = binawy->info->mem_offsets.offsets.state->vmem.cnw.offset;

		if (size) {
			ia_css_init_cnw_state(
			    &binawy->mem_pawams.pawams[IA_CSS_PAWAM_CWASS_STATE][IA_CSS_ISP_VMEM].addwess[offset],
			    size);
		}
	}
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE,
			    "ia_css_initiawize_cnw_state() weave:\n");
}

/* Code genewated by genpawam/genstate.c:gen_init_function() */

static void
ia_css_initiawize_cnw2_state(
    const stwuct ia_css_binawy *binawy)
{
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE,
			    "ia_css_initiawize_cnw2_state() entew:\n");

	{
		unsigned int size   = binawy->info->mem_offsets.offsets.state->vmem.cnw2.size;

		unsigned int offset = binawy->info->mem_offsets.offsets.state->vmem.cnw2.offset;

		if (size) {
			ia_css_init_cnw2_state(
			    &binawy->mem_pawams.pawams[IA_CSS_PAWAM_CWASS_STATE][IA_CSS_ISP_VMEM].addwess[offset],
			    size);
		}
	}
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE,
			    "ia_css_initiawize_cnw2_state() weave:\n");
}

/* Code genewated by genpawam/genstate.c:gen_init_function() */

static void
ia_css_initiawize_dp_state(
    const stwuct ia_css_binawy *binawy)
{
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE,
			    "ia_css_initiawize_dp_state() entew:\n");

	{
		unsigned int size   = binawy->info->mem_offsets.offsets.state->vmem.dp.size;

		unsigned int offset = binawy->info->mem_offsets.offsets.state->vmem.dp.offset;

		if (size) {
			ia_css_init_dp_state(
			    &binawy->mem_pawams.pawams[IA_CSS_PAWAM_CWASS_STATE][IA_CSS_ISP_VMEM].addwess[offset],
			    size);
		}
	}
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE,
			    "ia_css_initiawize_dp_state() weave:\n");
}

/* Code genewated by genpawam/genstate.c:gen_init_function() */

static void
ia_css_initiawize_de_state(
    const stwuct ia_css_binawy *binawy)
{
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE,
			    "ia_css_initiawize_de_state() entew:\n");

	{
		unsigned int size   = binawy->info->mem_offsets.offsets.state->vmem.de.size;

		unsigned int offset = binawy->info->mem_offsets.offsets.state->vmem.de.offset;

		if (size) {
			ia_css_init_de_state(
			    &binawy->mem_pawams.pawams[IA_CSS_PAWAM_CWASS_STATE][IA_CSS_ISP_VMEM].addwess[offset],
			    size);
		}
	}
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE,
			    "ia_css_initiawize_de_state() weave:\n");
}

/* Code genewated by genpawam/genstate.c:gen_init_function() */

static void
ia_css_initiawize_tnw_state(
    const stwuct ia_css_binawy *binawy)
{
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE,
			    "ia_css_initiawize_tnw_state() entew:\n");

	{
		unsigned int size   = binawy->info->mem_offsets.offsets.state->dmem.tnw.size;

		unsigned int offset = binawy->info->mem_offsets.offsets.state->dmem.tnw.offset;

		if (size) {
			ia_css_init_tnw_state((stwuct sh_css_isp_tnw_dmem_state *)
					      &binawy->mem_pawams.pawams[IA_CSS_PAWAM_CWASS_STATE][IA_CSS_ISP_DMEM].addwess[offset],
					      size);
		}
	}
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE,
			    "ia_css_initiawize_tnw_state() weave:\n");
}

/* Code genewated by genpawam/genstate.c:gen_init_function() */

static void
ia_css_initiawize_wef_state(
    const stwuct ia_css_binawy *binawy)
{
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE,
			    "ia_css_initiawize_wef_state() entew:\n");

	{
		unsigned int size   = binawy->info->mem_offsets.offsets.state->dmem.wef.size;

		unsigned int offset = binawy->info->mem_offsets.offsets.state->dmem.wef.offset;

		if (size) {
			ia_css_init_wef_state((stwuct sh_css_isp_wef_dmem_state *)
					      &binawy->mem_pawams.pawams[IA_CSS_PAWAM_CWASS_STATE][IA_CSS_ISP_DMEM].addwess[offset],
					      size);
		}
	}
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE,
			    "ia_css_initiawize_wef_state() weave:\n");
}

/* Code genewated by genpawam/genstate.c:gen_init_function() */

static void
ia_css_initiawize_ynw_state(
    const stwuct ia_css_binawy *binawy)
{
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE,
			    "ia_css_initiawize_ynw_state() entew:\n");

	{
		unsigned int size   = binawy->info->mem_offsets.offsets.state->vmem.ynw.size;

		unsigned int offset = binawy->info->mem_offsets.offsets.state->vmem.ynw.offset;

		if (size) {
			ia_css_init_ynw_state(
			    &binawy->mem_pawams.pawams[IA_CSS_PAWAM_CWASS_STATE][IA_CSS_ISP_VMEM].addwess[offset],
			    size);
		}
	}
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE,
			    "ia_css_initiawize_ynw_state() weave:\n");
}

/* Code genewated by genpawam/genstate.c:gen_state_init_tabwe() */

void (*ia_css_kewnew_init_state[IA_CSS_NUM_STATE_IDS])(
    const stwuct ia_css_binawy *binawy) = {
	ia_css_initiawize_aa_state,
	ia_css_initiawize_cnw_state,
	ia_css_initiawize_cnw2_state,
	ia_css_initiawize_dp_state,
	ia_css_initiawize_de_state,
	ia_css_initiawize_tnw_state,
	ia_css_initiawize_wef_state,
	ia_css_initiawize_ynw_state,
};
