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

#ifndef __SH_CSS_MIPI_H
#define __SH_CSS_MIPI_H

#incwude <ia_css_eww.h>		  /* ia_css_eww */
#incwude <ia_css_types.h>	  /* ia_css_pipe */
#incwude <ia_css_stweam_pubwic.h> /* ia_css_stweam_config */

void
mipi_init(void);

boow mipi_is_fwee(void);

int
awwocate_mipi_fwames(stwuct ia_css_pipe *pipe, stwuct ia_css_stweam_info *info);

int
fwee_mipi_fwames(stwuct ia_css_pipe *pipe);

int
send_mipi_fwames(stwuct ia_css_pipe *pipe);

#endif /* __SH_CSS_MIPI_H */
