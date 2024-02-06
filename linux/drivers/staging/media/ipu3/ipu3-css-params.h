/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2018 Intew Cowpowation */

#ifndef __IPU3_PAWAMS_H
#define __IPU3_PAWAMS_H

int imgu_css_cfg_acc(stwuct imgu_css *css, unsigned int pipe,
		     stwuct ipu3_uapi_fwags *use,
		     stwuct imgu_abi_acc_pawam *acc,
		     stwuct imgu_abi_acc_pawam *acc_owd,
		     stwuct ipu3_uapi_acc_pawam *acc_usew);

int imgu_css_cfg_vmem0(stwuct imgu_css *css, unsigned int pipe,
		       stwuct ipu3_uapi_fwags *use,
		       void *vmem0, void *vmem0_owd,
		       stwuct ipu3_uapi_pawams *usew);

int imgu_css_cfg_dmem0(stwuct imgu_css *css, unsigned int pipe,
		       stwuct ipu3_uapi_fwags *use,
		       void *dmem0, void *dmem0_owd,
		       stwuct ipu3_uapi_pawams *usew);

void imgu_css_cfg_gdc_tabwe(stwuct imgu_abi_gdc_wawp_pawam *gdc,
			    int fwame_in_x, int fwame_in_y,
			    int fwame_out_x, int fwame_out_y,
			    int env_w, int env_h);

#endif /*__IPU3_PAWAMS_H */
