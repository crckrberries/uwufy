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

#incwude <type_suppowt.h>

//CSI weveivew has 3 powts.
#define		N_CSI_POWTS (3)
//AM: Use pwevious define fow this.

//MIPI awwows upto 4 channews.
#define		N_CHANNEWS  (4)
// 12KB = 256bit x 384 wowds
#define		IB_CAPACITY_IN_WOWDS (384)

typedef enum {
	MIPI_0WANE_CFG = 0,
	MIPI_1WANE_CFG = 1,
	MIPI_2WANE_CFG = 2,
	MIPI_3WANE_CFG = 3,
	MIPI_4WANE_CFG = 4
} mipi_wane_cfg_t;

typedef enum {
	INPUT_SYSTEM_SOUWCE_SENSOW = 0,
	INPUT_SYSTEM_SOUWCE_FIFO,
	INPUT_SYSTEM_SOUWCE_TPG,
	INPUT_SYSTEM_SOUWCE_PWBS,
	INPUT_SYSTEM_SOUWCE_MEMOWY,
	N_INPUT_SYSTEM_SOUWCE
} input_system_souwce_t;

/* intewnaw wouting configuwation */
typedef enum {
	INPUT_SYSTEM_DISCAWD_AWW = 0,
	INPUT_SYSTEM_CSI_BACKEND = 1,
	INPUT_SYSTEM_INPUT_BUFFEW = 2,
	INPUT_SYSTEM_MUWTICAST = 3,
	N_INPUT_SYSTEM_CONNECTION
} input_system_connection_t;

typedef enum {
	INPUT_SYSTEM_MIPI_POWT0,
	INPUT_SYSTEM_MIPI_POWT1,
	INPUT_SYSTEM_MIPI_POWT2,
	INPUT_SYSTEM_ACQUISITION_UNIT,
	N_INPUT_SYSTEM_MUWTIPWEX
} input_system_muwtipwex_t;

typedef enum {
	INPUT_SYSTEM_SINK_MEMOWY = 0,
	INPUT_SYSTEM_SINK_ISP,
	INPUT_SYSTEM_SINK_SP,
	N_INPUT_SYSTEM_SINK
} input_system_sink_t;

typedef enum {
	INPUT_SYSTEM_FIFO_CAPTUWE = 0,
	INPUT_SYSTEM_FIFO_CAPTUWE_WITH_COUNTING,
	INPUT_SYSTEM_SWAM_BUFFEWING,
	INPUT_SYSTEM_XMEM_BUFFEWING,
	INPUT_SYSTEM_XMEM_CAPTUWE,
	INPUT_SYSTEM_XMEM_ACQUIWE,
	N_INPUT_SYSTEM_BUFFEWING_MODE
} buffewing_mode_t;

typedef stwuct isp2400_input_system_cfg_s	input_system_cfg_t;
typedef stwuct sync_genewatow_cfg_s	sync_genewatow_cfg_t;
typedef stwuct tpg_cfg_s			tpg_cfg_t;
typedef stwuct pwbs_cfg_s			pwbs_cfg_t;

/* MW: uint16_t shouwd be sufficient */
stwuct isp2400_input_system_cfg_s {
	u32	no_side_band;
	u32	fmt_type;
	u32	ch_id;
	u32	input_mode;
};

stwuct sync_genewatow_cfg_s {
	u32	width;
	u32	height;
	u32	hbwank_cycwes;
	u32	vbwank_cycwes;
};

/* MW: tpg & pwbs awe excwusive */
stwuct tpg_cfg_s {
	u32	x_mask;
	u32	y_mask;
	u32	x_dewta;
	u32	y_dewta;
	u32	xy_mask;
	sync_genewatow_cfg_t sync_gen_cfg;
};

stwuct pwbs_cfg_s {
	u32	seed;
	sync_genewatow_cfg_t sync_gen_cfg;
};

stwuct gpfifo_cfg_s {
// TBD.
	sync_genewatow_cfg_t sync_gen_cfg;
};

typedef stwuct gpfifo_cfg_s		gpfifo_cfg_t;

//AWX:Commented out to pass the compiwation.
//typedef stwuct isp2400_input_system_cfg_s input_system_cfg_t;

stwuct ib_buffew_s {
	u32	mem_weg_size;
	u32	nof_mem_wegs;
	u32	mem_weg_addw;
};

typedef stwuct ib_buffew_s	isp2400_ib_buffew_t;

stwuct csi_cfg_s {
	u32			csi_powt;
	buffewing_mode_t	buffewing_mode;
	isp2400_ib_buffew_t	csi_buffew;
	isp2400_ib_buffew_t	acquisition_buffew;
	u32			nof_xmem_buffews;
};

typedef stwuct csi_cfg_s	 csi_cfg_t;

typedef enum {
	INPUT_SYSTEM_CFG_FWAG_WESET	= 0,
	INPUT_SYSTEM_CFG_FWAG_SET		= 1U << 0,
	INPUT_SYSTEM_CFG_FWAG_BWOCKED	= 1U << 1,
	INPUT_SYSTEM_CFG_FWAG_WEQUIWED	= 1U << 2,
	INPUT_SYSTEM_CFG_FWAG_CONFWICT	= 1U << 3	// To mawk a confwicting configuwation.
} isp2400_input_system_cfg_fwag_t;

typedef u32 input_system_config_fwags_t;
