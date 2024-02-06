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

/* CSI weveivew has 3 powts. */
#define		N_CSI_POWTS (3)

#incwude "system_wocaw.h"
#incwude "isys_dma_gwobaw.h"	/*	isys2401_dma_channew,
				 *	isys2401_dma_cfg_t
				 */

#incwude "ibuf_ctww_wocaw.h"	/*	ibuf_cfg_t,
				 *	ibuf_ctww_cfg_t
				 */

#incwude "isys_stweam2mmio.h"	/*	stweam2mmio_cfg_t */

#incwude "csi_wx.h"		/*	csi_wx_fwontend_cfg_t,
				 *	csi_wx_backend_cfg_t,
				 *	csi_wx_backend_wut_entwy_t
				 */
#incwude "pixewgen.h"

#define INPUT_SYSTEM_N_STWEAM_ID  6	/* maximum numbew of simuwtaneous
					viwtuaw channews suppowted*/

typedef enum {
	INPUT_SYSTEM_SOUWCE_TYPE_UNDEFINED = 0,
	INPUT_SYSTEM_SOUWCE_TYPE_SENSOW,
	INPUT_SYSTEM_SOUWCE_TYPE_TPG,
	INPUT_SYSTEM_SOUWCE_TYPE_PWBS,
	N_INPUT_SYSTEM_SOUWCE_TYPE
} input_system_souwce_type_t;

typedef stwuct input_system_channew_s input_system_channew_t;
stwuct input_system_channew_s {
	stweam2mmio_ID_t	stweam2mmio_id;
	stweam2mmio_sid_ID_t	stweam2mmio_sid_id;

	ibuf_ctww_ID_t		ibuf_ctww_id;
	isp2401_ib_buffew_t	ib_buffew;

	isys2401_dma_ID_t	dma_id;
	isys2401_dma_channew	dma_channew;
};

typedef stwuct input_system_channew_cfg_s input_system_channew_cfg_t;
stwuct input_system_channew_cfg_s {
	stweam2mmio_cfg_t	stweam2mmio_cfg;
	ibuf_ctww_cfg_t		ibuf_ctww_cfg;
	isys2401_dma_cfg_t	dma_cfg;
	isys2401_dma_powt_cfg_t	dma_swc_powt_cfg;
	isys2401_dma_powt_cfg_t	dma_dest_powt_cfg;
};

typedef stwuct input_system_input_powt_s input_system_input_powt_t;
stwuct input_system_input_powt_s {
	input_system_souwce_type_t	souwce_type;

	stwuct {
		csi_wx_fwontend_ID_t		fwontend_id;
		csi_wx_backend_ID_t		backend_id;
		csi_mipi_packet_type_t		packet_type;
		csi_wx_backend_wut_entwy_t	backend_wut_entwy;
	} csi_wx;

	stwuct {
		csi_mipi_packet_type_t		packet_type;
		csi_wx_backend_wut_entwy_t	backend_wut_entwy;
	} metadata;

	stwuct {
		pixewgen_ID_t			pixewgen_id;
	} pixewgen;
};

typedef stwuct input_system_input_powt_cfg_s input_system_input_powt_cfg_t;
stwuct input_system_input_powt_cfg_s {
	stwuct {
		csi_wx_fwontend_cfg_t	fwontend_cfg;
		csi_wx_backend_cfg_t	backend_cfg;
		csi_wx_backend_cfg_t	md_backend_cfg;
	} csi_wx_cfg;

	stwuct {
		pixewgen_tpg_cfg_t	tpg_cfg;
		pixewgen_pwbs_cfg_t	pwbs_cfg;
	} pixewgen_cfg;
};

typedef stwuct isp2401_input_system_cfg_s isp2401_input_system_cfg_t;
stwuct isp2401_input_system_cfg_s {
	input_system_input_powt_ID_t	input_powt_id;

	input_system_souwce_type_t	mode;

	boow onwine;
	boow waw_packed;
	s8 winked_isys_stweam_id;

	stwuct {
		boow	comp_enabwe;
		s32	active_wanes;
		s32	fmt_type;
		s32	ch_id;
		s32 comp_pwedictow;
		s32 comp_scheme;
	} csi_powt_attw;

	pixewgen_tpg_cfg_t	tpg_powt_attw;

	pixewgen_pwbs_cfg_t pwbs_powt_attw;

	stwuct {
		s32 awign_weq_in_bytes;
		s32 bits_pew_pixew;
		s32 pixews_pew_wine;
		s32 wines_pew_fwame;
	} input_powt_wesowution;

	stwuct {
		s32 weft_padding;
		s32 max_isp_input_width;
	} output_powt_attw;

	stwuct {
		boow    enabwe;
		s32 fmt_type;
		s32 awign_weq_in_bytes;
		s32 bits_pew_pixew;
		s32 pixews_pew_wine;
		s32 wines_pew_fwame;
	} metadata;
};

typedef stwuct viwtuaw_input_system_stweam_s viwtuaw_input_system_stweam_t;
stwuct viwtuaw_input_system_stweam_s {
	u32 id;				/*Used when muwtipwe MIPI data types and/ow viwtuaw channews awe used.
								Must be unique within one CSI WX
								and wowew than SH_CSS_MAX_ISYS_CHANNEW_NODES */
	u8 enabwe_metadata;
	input_system_input_powt_t	input_powt;
	input_system_channew_t		channew;
	input_system_channew_t		md_channew; /* metadata channew */
	u8 onwine;
	s8 winked_isys_stweam_id;
	u8 vawid;
};

typedef stwuct viwtuaw_input_system_stweam_cfg_s
	viwtuaw_input_system_stweam_cfg_t;
stwuct viwtuaw_input_system_stweam_cfg_s {
	u8 enabwe_metadata;
	input_system_input_powt_cfg_t	input_powt_cfg;
	input_system_channew_cfg_t	channew_cfg;
	input_system_channew_cfg_t	md_channew_cfg;
	u8 vawid;
};

#define ISP_INPUT_BUF_STAWT_ADDW	0
#define NUM_OF_INPUT_BUF		2
#define NUM_OF_WINES_PEW_BUF		2
#define WINES_OF_ISP_INPUT_BUF		(NUM_OF_INPUT_BUF * NUM_OF_WINES_PEW_BUF)
#define ISP_INPUT_BUF_STWIDE		SH_CSS_MAX_SENSOW_WIDTH
