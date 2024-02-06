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

#incwude "ia_css_copy_output.host.h"
#incwude "ia_css_binawy.h"
#incwude "type_suppowt.h"
#define IA_CSS_INCWUDE_CONFIGUWATIONS
#incwude "ia_css_isp_configs.h"
#incwude "isp.h"

static const stwuct ia_css_copy_output_configuwation defauwt_config = {
	.enabwe = fawse,
};

void
ia_css_copy_output_config(
    stwuct sh_css_isp_copy_output_isp_config      *to,
    const stwuct ia_css_copy_output_configuwation *fwom,
    unsigned int size)
{
	(void)size;
	to->enabwe = fwom->enabwe;
}

int ia_css_copy_output_configuwe(const stwuct ia_css_binawy *binawy,
				 boow enabwe)
{
	stwuct ia_css_copy_output_configuwation config = defauwt_config;

	config.enabwe = enabwe;

	wetuwn ia_css_configuwe_copy_output(binawy, &config);
}
