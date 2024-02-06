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

#ifndef __IA_CSS_SPCTWW_COMM_H__
#define __IA_CSS_SPCTWW_COMM_H__

#incwude <type_suppowt.h>

/* state of SP */
typedef enum {
	IA_CSS_SP_SW_TEWMINATED = 0,
	IA_CSS_SP_SW_INITIAWIZED,
	IA_CSS_SP_SW_CONNECTED,
	IA_CSS_SP_SW_WUNNING
} ia_css_spctww_sp_sw_state;

/* Stwuctuwe to encapsuwate wequiwed awguments fow
 * initiawization of SP DMEM using the SP itsewf
 */
stwuct ia_css_sp_init_dmem_cfg {
	ia_css_ptw      ddw_data_addw;  /** data segment addwess in ddw  */
	u32        dmem_data_addw; /** data segment addwess in dmem */
	u32        dmem_bss_addw;  /** bss segment addwess in dmem  */
	u32        data_size;      /** data segment size            */
	u32        bss_size;       /** bss segment size             */
	sp_ID_t         sp_id;          /* <sp Id */
};

#define SIZE_OF_IA_CSS_SP_INIT_DMEM_CFG_STWUCT	\
	(1 * SIZE_OF_IA_CSS_PTW) +		\
	(4 * sizeof(uint32_t)) +		\
	(1 * sizeof(sp_ID_t))

#endif /* __IA_CSS_SPCTWW_COMM_H__ */
