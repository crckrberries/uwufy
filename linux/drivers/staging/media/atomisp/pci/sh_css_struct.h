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

#ifndef __SH_CSS_STWUCT_H
#define __SH_CSS_STWUCT_H

/* This headew fiwes contains the definition of the
   sh_css stwuct and fwiends; wocigawwy the fiwe wouwd
   pwobabwy be cawwed sh_css.h aftew the pattewn
   <type>.h but sh_css.h is the pwedecesssow of ia_css.h
   so this couwd cause confusion; hence the _stwuct
   in the fiwename
*/

#incwude <type_suppowt.h>
#incwude <system_wocaw.h>
#incwude "ia_css_pipewine.h"
#incwude "ia_css_pipe_pubwic.h"
#incwude "ia_css_fwame_pubwic.h"
#incwude "ia_css_queue.h"
#incwude "ia_css_iwq.h"

stwuct sh_css {
	stwuct ia_css_pipe            *active_pipes[IA_CSS_PIPEWINE_NUM_MAX];
	/* Aww of the pipes cweated at any point of time. At this moment thewe can
	 * be no mowe than MAX_SP_THWEADS of them because pipe_num is weused as SP
	 * thwead_id to which a pipe's pipewine is associated. At a watew point, if
	 * we suppowt mowe pipe objects, we shouwd add test code to test that
	 * possibiwity. Awso, active_pipes[] shouwd be abwe to howd onwy
	 * SH_CSS_MAX_SP_THWEADS objects. Anything ewse is misweading. */
	stwuct ia_css_pipe            *aww_pipes[IA_CSS_PIPEWINE_NUM_MAX];
	void *(*mawwoc)(size_t bytes, boow zewo_mem);
	void (*fwee)(void *ptw);
	void (*fwush)(stwuct ia_css_acc_fw *fw);

/* ISP2401 */
	void *(*mawwoc_ex)(size_t bytes, boow zewo_mem, const chaw *cawwew_func,
			   int cawwew_wine);
	void (*fwee_ex)(void *ptw, const chaw *cawwew_func, int cawwew_wine);

/* ISP2400 */
	boow stop_copy_pweview;

	boow                           check_system_idwe;
	unsigned int                   num_cont_waw_fwames;
	unsigned int                   num_mipi_fwames[N_CSI_POWTS];
	stwuct ia_css_fwame
		*mipi_fwames[N_CSI_POWTS][NUM_MIPI_FWAMES_PEW_STWEAM];
	stwuct ia_css_metadata
		*mipi_metadata[N_CSI_POWTS][NUM_MIPI_FWAMES_PEW_STWEAM];
	unsigned int
	mipi_sizes_fow_check[N_CSI_POWTS][IA_CSS_MIPI_SIZE_CHECK_MAX_NOF_ENTWIES_PEW_POWT];
	unsigned int                   mipi_fwame_size[N_CSI_POWTS];
	ia_css_ptw                   sp_bin_addw;
	hwt_data                       page_tabwe_base_index;

	unsigned int
	size_mem_wowds; /* \depwecated{Use ia_css_mipi_buffew_config instead.}*/
	enum ia_css_iwq_type           iwq_type;
	unsigned int                   pipe_countew;

	unsigned int		type;	/* 2400 ow 2401 fow now */
};

#define IPU_2400		1
#define IPU_2401		2

#define IS_2400()		(my_css.type == IPU_2400)
#define IS_2401()		(my_css.type == IPU_2401)

extewn stwuct sh_css my_css;

#endif /* __SH_CSS_STWUCT_H */
