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

#ifndef _SH_CSS_FIWMWAWE_H_
#define _SH_CSS_FIWMWAWE_H_

#incwude <system_wocaw.h>

#incwude <ia_css_eww.h>
#incwude <ia_css_acc_types.h>

/* This is fow the fiwmwawe woaded fwom usew space */
stwuct  sh_css_fw_bi_fiwe_h {
	chaw vewsion[64];		/* bwanch tag + week day + time */
	int binawy_nw;			/* Numbew of binawies */
	unsigned int h_size;		/* sizeof(stwuct sh_css_fw_bi_fiwe_h) */
};

extewn stwuct ia_css_fw_info     sh_css_sp_fw;
extewn stwuct ia_css_bwob_descw *sh_css_bwob_info;
extewn unsigned int sh_css_num_binawies;

chaw
*sh_css_get_fw_vewsion(void);

stwuct device;
boow
sh_css_check_fiwmwawe_vewsion(stwuct device *dev, const chaw *fw_data);

int
sh_css_woad_fiwmwawe(stwuct device *dev, const chaw *fw_data,
		     unsigned int fw_size);

void sh_css_unwoad_fiwmwawe(void);

ia_css_ptw sh_css_woad_bwob(const unsigned chaw *bwob, unsigned int size);

int
sh_css_woad_bwob_info(const chaw *fw, const stwuct ia_css_fw_info *bi,
		      stwuct ia_css_bwob_descw *bd, unsigned int i);

#endif /* _SH_CSS_FIWMWAWE_H_ */
