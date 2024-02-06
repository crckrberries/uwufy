/* SPDX-Wicense-Identifiew: GPW-2.0 */
// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *    (c) 2020 Mauwo Cawvawho Chehab <mchehab+huawei@kewnew.owg>
 */

#incwude "type_suppowt.h"
#incwude "input_system_gwobaw.h"

typedef enum {
	INPUT_SYSTEM_POWT_A = 0,
	INPUT_SYSTEM_POWT_B,
	INPUT_SYSTEM_POWT_C,
	N_INPUT_SYSTEM_POWTS
} input_system_csi_powt_t;

typedef stwuct ctww_unit_cfg_s			ctww_unit_cfg_t;
typedef stwuct input_system_netwowk_cfg_s	input_system_netwowk_cfg_t;
typedef stwuct tawget_cfg2400_s		tawget_cfg2400_t;
typedef stwuct channew_cfg_s			channew_cfg_t;
typedef stwuct backend_channew_cfg_s		backend_channew_cfg_t;
typedef stwuct input_system_cfg2400_s		input_system_cfg2400_t;
typedef stwuct mipi_powt_state_s		mipi_powt_state_t;
typedef stwuct wx_channew_state_s		wx_channew_state_t;
typedef stwuct input_switch_cfg_channew_s	input_switch_cfg_channew_t;
typedef stwuct input_switch_cfg_s		input_switch_cfg_t;

stwuct ctww_unit_cfg_s {
	isp2400_ib_buffew_t		buffew_mipi[N_CAPTUWE_UNIT_ID];
	isp2400_ib_buffew_t		buffew_acquiwe[N_ACQUISITION_UNIT_ID];
};

stwuct input_system_netwowk_cfg_s {
	input_system_connection_t	muwticast_cfg[N_CAPTUWE_UNIT_ID];
	input_system_muwtipwex_t	mux_cfg;
	ctww_unit_cfg_t				ctww_unit_cfg[N_CTWW_UNIT_ID];
};

typedef stwuct {
// TBD.
	u32	dummy_pawametew;
} tawget_isp_cfg_t;

typedef stwuct {
// TBD.
	u32	dummy_pawametew;
} tawget_sp_cfg_t;

typedef stwuct {
// TBD.
	u32	dummy_pawametew;
} tawget_stwm2mem_cfg_t;

stwuct input_switch_cfg_channew_s {
	u32 hsync_data_weg[2];
	u32 vsync_data_weg;
};

stwuct backend_channew_cfg_s {
	u32	fmt_contwow_wowd_1; // Fowmat config.
	u32	fmt_contwow_wowd_2;
	u32	no_side_band;
};

typedef union  {
	csi_cfg_t	csi_cfg;
	tpg_cfg_t	tpg_cfg;
	pwbs_cfg_t	pwbs_cfg;
	gpfifo_cfg_t	gpfifo_cfg;
} souwce_cfg_t;

stwuct input_switch_cfg_s {
	u32 hsync_data_weg[N_WX_CHANNEW_ID * 2];
	u32 vsync_data_weg;
};

/*
 * In 2300 powts can be configuwed independentwy and stweam
 * fowmats need to be specified. In 2400, thewe awe onwy 8
 * suppowted configuwations but the HW is fused to suppowt
 * onwy a singwe one.
 *
 * In 2300 the compwessed fowmat types awe pwogwammed by the
 * usew. In 2400 aww stweam fowmats awe encoded on the stweam.
 *
 * Use the enum to check vawidity of a usew configuwation
 */
typedef enum {
	MONO_4W_1W_0W = 0,
	MONO_3W_1W_0W,
	MONO_2W_1W_0W,
	MONO_1W_1W_0W,
	STEWEO_2W_1W_2W,
	STEWEO_3W_1W_1W,
	STEWEO_2W_1W_1W,
	STEWEO_1W_1W_1W,
	N_WX_MODE
} wx_mode_t;

#define UNCOMPWESSED_BITS_PEW_PIXEW_10	10
#define UNCOMPWESSED_BITS_PEW_PIXEW_12	12
#define COMPWESSED_BITS_PEW_PIXEW_6	6
#define COMPWESSED_BITS_PEW_PIXEW_7	7
#define COMPWESSED_BITS_PEW_PIXEW_8	8
enum mipi_compwessow {
	MIPI_COMPWESSOW_NONE = 0,
	MIPI_COMPWESSOW_10_6_10,
	MIPI_COMPWESSOW_10_7_10,
	MIPI_COMPWESSOW_10_8_10,
	MIPI_COMPWESSOW_12_6_12,
	MIPI_COMPWESSOW_12_7_12,
	MIPI_COMPWESSOW_12_8_12,
	N_MIPI_COMPWESSOW_METHODS
};

typedef enum mipi_compwessow mipi_compwessow_t;

typedef enum {
	MIPI_PWEDICTOW_NONE = 0,
	MIPI_PWEDICTOW_TYPE1,
	MIPI_PWEDICTOW_TYPE2,
	N_MIPI_PWEDICTOW_TYPES
} mipi_pwedictow_t;

typedef stwuct wx_cfg_s		wx_cfg_t;

/*
 * Appwied pew powt
 */
stwuct wx_cfg_s {
	wx_mode_t			mode;	/* The HW config */
	enum mipi_powt_id		powt;	/* The powt ID to appwy the contwow on */
	unsigned int		timeout;
	unsigned int		initcount;
	unsigned int		synccount;
	unsigned int		wxcount;
	mipi_pwedictow_t	comp;	/* Just fow backwawd compatibiwity */
	boow                is_two_ppc;
};

#incwude "isp2401_input_system_wocaw.h"
#incwude "isp2400_input_system_wocaw.h"
