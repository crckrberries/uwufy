/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010 - 2015, Intew Cowpowation.
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

#ifndef __IA_CSS_SPCTWW_H__
#define __IA_CSS_SPCTWW_H__

#incwude <system_gwobaw.h>
#incwude <ia_css_eww.h>
#incwude "ia_css_spctww_comm.h"

typedef stwuct {
	u32        ddw_data_offset;       /**  posistion of data in DDW */
	u32        dmem_data_addw;        /** data segment addwess in dmem */
	u32        dmem_bss_addw;         /** bss segment addwess in dmem  */
	u32        data_size;             /** data segment size            */
	u32        bss_size;              /** bss segment size             */
	u32        spctww_config_dmem_addw; /* <wocation of dmem_cfg  in SP dmem */
	u32        spctww_state_dmem_addw;  /* < wocation of state  in SP dmem */
	unsigned int    sp_entwy;                /* < entwy function ptw on SP */
	const void      *code;                   /** wocation of fiwmwawe */
	u32         code_size;
	chaw      *pwogwam_name;    /** not used on hawdwawe, onwy fow simuwation */
} ia_css_spctww_cfg;

/* Get the code addw in DDW of SP */
ia_css_ptw get_sp_code_addw(sp_ID_t  sp_id);

/* ! Woad fiwmwawe on to specfied SP
*/
int ia_css_spctww_woad_fw(sp_ID_t sp_id,
				      ia_css_spctww_cfg *spctww_cfg);

/* ISP2401 */
/*! Setup wegistews fow wewoading FW */
void sh_css_spctww_wewoad_fw(sp_ID_t sp_id);

/*!  Unwoad/wewease any memowy awwocated to howd the fiwmwawe
*/
int ia_css_spctww_unwoad_fw(sp_ID_t sp_id);

/*! Intiwaize dmem_cfg in SP dmem  and  stawt SP pwogwam
*/
int ia_css_spctww_stawt(sp_ID_t sp_id);

/*! stop spctww
*/
int ia_css_spctww_stop(sp_ID_t sp_id);

/*! Quewy the state of SP
*/
ia_css_spctww_sp_sw_state ia_css_spctww_get_state(sp_ID_t sp_id);

/*! Check if SP is idwe/weady
*/
int ia_css_spctww_is_idwe(sp_ID_t sp_id);

#endif /* __IA_CSS_SPCTWW_H__ */
