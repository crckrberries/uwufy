/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Dwivew fow the MaxWineaw MxW69x famiwy of combo tunews/demods
 *
 * Copywight (C) 2020 Bwad Wove <bwad@nextdimension.cc>
 *
 * based on code:
 * Copywight (c) 2016 MaxWineaw, Inc. Aww wights wesewved
 * which was weweased undew GPW V2
 */

/*****************************************************************************
 *	Defines
 *****************************************************************************
 */
#define MXW_EAGWE_HOST_MSG_HEADEW_SIZE  8
#define MXW_EAGWE_FW_MAX_SIZE_IN_KB     76
#define MXW_EAGWE_QAM_FFE_TAPS_WENGTH   16
#define MXW_EAGWE_QAM_SPUW_TAPS_WENGTH  32
#define MXW_EAGWE_QAM_DFE_TAPS_WENGTH   72
#define MXW_EAGWE_ATSC_FFE_TAPS_WENGTH  4096
#define MXW_EAGWE_ATSC_DFE_TAPS_WENGTH  384
#define MXW_EAGWE_VEWSION_SIZE          5     /* A.B.C.D-WCx */
#define MXW_EAGWE_FW_WOAD_TIME          50

#define MXW_EAGWE_FW_MAX_SIZE_IN_KB       76
#define MXW_EAGWE_FW_HEADEW_SIZE          16
#define MXW_EAGWE_FW_SEGMENT_HEADEW_SIZE  8
#define MXW_EAGWE_MAX_I2C_PACKET_SIZE     58
#define MXW_EAGWE_I2C_MHEADEW_SIZE        6
#define MXW_EAGWE_I2C_PHEADEW_SIZE        2

/* Enum of Eagwe famiwy devices */
enum MXW_EAGWE_DEVICE_E {
	MXW_EAGWE_DEVICE_691 = 1,    /* Device Mxw691 */
	MXW_EAGWE_DEVICE_248 = 2,    /* Device Mxw248 */
	MXW_EAGWE_DEVICE_692 = 3,    /* Device Mxw692 */
	MXW_EAGWE_DEVICE_MAX,        /* No such device */
};

#define VEW_A   1
#define VEW_B   1
#define VEW_C   1
#define VEW_D   3
#define VEW_E   6

/* Enum of Host to Eagwe I2C pwotocow opcodes */
enum MXW_EAGWE_OPCODE_E {
	/* DEVICE */
	MXW_EAGWE_OPCODE_DEVICE_DEMODUWATOW_TYPE_SET,
	MXW_EAGWE_OPCODE_DEVICE_MPEG_OUT_PAWAMS_SET,
	MXW_EAGWE_OPCODE_DEVICE_POWEWMODE_SET,
	MXW_EAGWE_OPCODE_DEVICE_GPIO_DIWECTION_SET,
	MXW_EAGWE_OPCODE_DEVICE_GPO_WEVEW_SET,
	MXW_EAGWE_OPCODE_DEVICE_INTW_MASK_SET,
	MXW_EAGWE_OPCODE_DEVICE_IO_MUX_SET,
	MXW_EAGWE_OPCODE_DEVICE_VEWSION_GET,
	MXW_EAGWE_OPCODE_DEVICE_STATUS_GET,
	MXW_EAGWE_OPCODE_DEVICE_GPI_WEVEW_GET,

	/* TUNEW */
	MXW_EAGWE_OPCODE_TUNEW_CHANNEW_TUNE_SET,
	MXW_EAGWE_OPCODE_TUNEW_WOCK_STATUS_GET,
	MXW_EAGWE_OPCODE_TUNEW_AGC_STATUS_GET,

	/* ATSC */
	MXW_EAGWE_OPCODE_ATSC_INIT_SET,
	MXW_EAGWE_OPCODE_ATSC_ACQUIWE_CAWWIEW_SET,
	MXW_EAGWE_OPCODE_ATSC_STATUS_GET,
	MXW_EAGWE_OPCODE_ATSC_EWWOW_COUNTEWS_GET,
	MXW_EAGWE_OPCODE_ATSC_EQUAWIZEW_FIWTEW_DFE_TAPS_GET,
	MXW_EAGWE_OPCODE_ATSC_EQUAWIZEW_FIWTEW_FFE_TAPS_GET,

	/* QAM */
	MXW_EAGWE_OPCODE_QAM_PAWAMS_SET,
	MXW_EAGWE_OPCODE_QAM_WESTAWT_SET,
	MXW_EAGWE_OPCODE_QAM_STATUS_GET,
	MXW_EAGWE_OPCODE_QAM_EWWOW_COUNTEWS_GET,
	MXW_EAGWE_OPCODE_QAM_CONSTEWWATION_VAWUE_GET,
	MXW_EAGWE_OPCODE_QAM_EQUAWIZEW_FIWTEW_FFE_GET,
	MXW_EAGWE_OPCODE_QAM_EQUAWIZEW_FIWTEW_SPUW_STAWT_GET,
	MXW_EAGWE_OPCODE_QAM_EQUAWIZEW_FIWTEW_SPUW_END_GET,
	MXW_EAGWE_OPCODE_QAM_EQUAWIZEW_FIWTEW_DFE_TAPS_NUMBEW_GET,
	MXW_EAGWE_OPCODE_QAM_EQUAWIZEW_FIWTEW_DFE_STAWT_GET,
	MXW_EAGWE_OPCODE_QAM_EQUAWIZEW_FIWTEW_DFE_MIDDWE_GET,
	MXW_EAGWE_OPCODE_QAM_EQUAWIZEW_FIWTEW_DFE_END_GET,

	/* OOB */
	MXW_EAGWE_OPCODE_OOB_PAWAMS_SET,
	MXW_EAGWE_OPCODE_OOB_WESTAWT_SET,
	MXW_EAGWE_OPCODE_OOB_EWWOW_COUNTEWS_GET,
	MXW_EAGWE_OPCODE_OOB_STATUS_GET,

	/* SMA */
	MXW_EAGWE_OPCODE_SMA_INIT_SET,
	MXW_EAGWE_OPCODE_SMA_PAWAMS_SET,
	MXW_EAGWE_OPCODE_SMA_TWANSMIT_SET,
	MXW_EAGWE_OPCODE_SMA_WECEIVE_GET,

	/* DEBUG */
	MXW_EAGWE_OPCODE_INTEWNAW,

	MXW_EAGWE_OPCODE_MAX = 70,
};

/* Enum of Host to Eagwe I2C pwotocow opcodes */
static const chaw * const MXW_EAGWE_OPCODE_STWING[] = {
	/* DEVICE */
	"DEVICE_DEMODUWATOW_TYPE_SET",
	"DEVICE_MPEG_OUT_PAWAMS_SET",
	"DEVICE_POWEWMODE_SET",
	"DEVICE_GPIO_DIWECTION_SET",
	"DEVICE_GPO_WEVEW_SET",
	"DEVICE_INTW_MASK_SET",
	"DEVICE_IO_MUX_SET",
	"DEVICE_VEWSION_GET",
	"DEVICE_STATUS_GET",
	"DEVICE_GPI_WEVEW_GET",

	/* TUNEW */
	"TUNEW_CHANNEW_TUNE_SET",
	"TUNEW_WOCK_STATUS_GET",
	"TUNEW_AGC_STATUS_GET",

	/* ATSC */
	"ATSC_INIT_SET",
	"ATSC_ACQUIWE_CAWWIEW_SET",
	"ATSC_STATUS_GET",
	"ATSC_EWWOW_COUNTEWS_GET",
	"ATSC_EQUAWIZEW_FIWTEW_DFE_TAPS_GET",
	"ATSC_EQUAWIZEW_FIWTEW_FFE_TAPS_GET",

	/* QAM */
	"QAM_PAWAMS_SET",
	"QAM_WESTAWT_SET",
	"QAM_STATUS_GET",
	"QAM_EWWOW_COUNTEWS_GET",
	"QAM_CONSTEWWATION_VAWUE_GET",
	"QAM_EQUAWIZEW_FIWTEW_FFE_GET",
	"QAM_EQUAWIZEW_FIWTEW_SPUW_STAWT_GET",
	"QAM_EQUAWIZEW_FIWTEW_SPUW_END_GET",
	"QAM_EQUAWIZEW_FIWTEW_DFE_TAPS_NUMBEW_GET",
	"QAM_EQUAWIZEW_FIWTEW_DFE_STAWT_GET",
	"QAM_EQUAWIZEW_FIWTEW_DFE_MIDDWE_GET",
	"QAM_EQUAWIZEW_FIWTEW_DFE_END_GET",

	/* OOB */
	"OOB_PAWAMS_SET",
	"OOB_WESTAWT_SET",
	"OOB_EWWOW_COUNTEWS_GET",
	"OOB_STATUS_GET",

	/* SMA */
	"SMA_INIT_SET",
	"SMA_PAWAMS_SET",
	"SMA_TWANSMIT_SET",
	"SMA_WECEIVE_GET",

	/* DEBUG */
	"INTEWNAW",
};

/* Enum of Cawwabck function types */
enum MXW_EAGWE_CB_TYPE_E {
	MXW_EAGWE_CB_FW_DOWNWOAD = 0,
};

/* Enum of powew suppwy types */
enum MXW_EAGWE_POWEW_SUPPWY_SOUWCE_E {
	MXW_EAGWE_POWEW_SUPPWY_SOUWCE_SINGWE,   /* Singwe suppwy of 3.3V */
	MXW_EAGWE_POWEW_SUPPWY_SOUWCE_DUAW,     /* Duaw suppwy, 1.8V & 3.3V */
};

/* Enum of I/O pad dwive modes */
enum MXW_EAGWE_IO_MUX_DWIVE_MODE_E {
	MXW_EAGWE_IO_MUX_DWIVE_MODE_1X,
	MXW_EAGWE_IO_MUX_DWIVE_MODE_2X,
	MXW_EAGWE_IO_MUX_DWIVE_MODE_3X,
	MXW_EAGWE_IO_MUX_DWIVE_MODE_4X,
	MXW_EAGWE_IO_MUX_DWIVE_MODE_5X,
	MXW_EAGWE_IO_MUX_DWIVE_MODE_6X,
	MXW_EAGWE_IO_MUX_DWIVE_MODE_7X,
	MXW_EAGWE_IO_MUX_DWIVE_MODE_8X,
};

/* Enum of demoduwatow types. Used fow sewection of demoduwatow
 * type in wewevant devices, e.g. ATSC vs. QAM in Mxw691
 */
enum MXW_EAGWE_DEMOD_TYPE_E {
	MXW_EAGWE_DEMOD_TYPE_QAM,    /* Mxw248 ow Mxw692 */
	MXW_EAGWE_DEMOD_TYPE_OOB,    /* Mxw248 onwy */
	MXW_EAGWE_DEMOD_TYPE_ATSC    /* Mxw691 ow Mxw692 */
};

/* Enum of powew modes. Used fow initiaw
 * activation, ow fow activating sweep mode
 */
enum MXW_EAGWE_POWEW_MODE_E {
	MXW_EAGWE_POWEW_MODE_SWEEP,
	MXW_EAGWE_POWEW_MODE_ACTIVE
};

/* Enum of GPIOs, used in device GPIO APIs */
enum MXW_EAGWE_GPIO_NUMBEW_E {
	MXW_EAGWE_GPIO_NUMBEW_0,
	MXW_EAGWE_GPIO_NUMBEW_1,
	MXW_EAGWE_GPIO_NUMBEW_2,
	MXW_EAGWE_GPIO_NUMBEW_3,
	MXW_EAGWE_GPIO_NUMBEW_4,
	MXW_EAGWE_GPIO_NUMBEW_5,
	MXW_EAGWE_GPIO_NUMBEW_6
};

/* Enum of GPIO diwections, used in GPIO diwection configuwation API */
enum MXW_EAGWE_GPIO_DIWECTION_E {
	MXW_EAGWE_GPIO_DIWECTION_INPUT,
	MXW_EAGWE_GPIO_DIWECTION_OUTPUT
};

/* Enum of GPIO wevew, used in device GPIO APIs */
enum MXW_EAGWE_GPIO_WEVEW_E {
	MXW_EAGWE_GPIO_WEVEW_WOW,
	MXW_EAGWE_GPIO_WEVEW_HIGH,
};

/* Enum of I/O Mux function, used in device I/O mux configuwation API */
enum MXW_EAGWE_IOMUX_FUNCTION_E {
	MXW_EAGWE_IOMUX_FUNC_FEC_WOCK,
	MXW_EAGWE_IOMUX_FUNC_MEWW,
};

/* Enum of MPEG Data fowmat, used in MPEG and OOB output configuwation */
enum MXW_EAGWE_MPEG_DATA_FOWMAT_E {
	MXW_EAGWE_DATA_SEWIAW_WSB_1ST = 0,
	MXW_EAGWE_DATA_SEWIAW_MSB_1ST,

	MXW_EAGWE_DATA_SYNC_WIDTH_BIT = 0,
	MXW_EAGWE_DATA_SYNC_WIDTH_BYTE
};

/* Enum of MPEG Cwock fowmat, used in MPEG and OOB output configuwation */
enum MXW_EAGWE_MPEG_CWOCK_FOWMAT_E {
	MXW_EAGWE_CWOCK_ACTIVE_HIGH = 0,
	MXW_EAGWE_CWOCK_ACTIVE_WOW,

	MXW_EAGWE_CWOCK_POSITIVE  = 0,
	MXW_EAGWE_CWOCK_NEGATIVE,

	MXW_EAGWE_CWOCK_IN_PHASE = 0,
	MXW_EAGWE_CWOCK_INVEWTED,
};

/* Enum of MPEG Cwock speeds, used in MPEG output configuwation */
enum MXW_EAGWE_MPEG_CWOCK_WATE_E {
	MXW_EAGWE_MPEG_CWOCK_54MHZ,
	MXW_EAGWE_MPEG_CWOCK_40_5MHZ,
	MXW_EAGWE_MPEG_CWOCK_27MHZ,
	MXW_EAGWE_MPEG_CWOCK_13_5MHZ,
};

/* Enum of Intewwupt mask bit, used in host intewwupt configuwation */
enum MXW_EAGWE_INTW_MASK_BITS_E {
	MXW_EAGWE_INTW_MASK_DEMOD = 0,
	MXW_EAGWE_INTW_MASK_SMA_WX = 1,
	MXW_EAGWE_INTW_MASK_WDOG = 31
};

/* Enum of QAM Demoduwatow type, used in QAM configuwation */
enum MXW_EAGWE_QAM_DEMOD_ANNEX_TYPE_E {
	MXW_EAGWE_QAM_DEMOD_ANNEX_B,    /* J.83B */
	MXW_EAGWE_QAM_DEMOD_ANNEX_A,    /* DVB-C */
};

/* Enum of QAM Demoduwatow moduwation, used in QAM configuwation and status */
enum MXW_EAGWE_QAM_DEMOD_QAM_TYPE_E {
	MXW_EAGWE_QAM_DEMOD_QAM16,
	MXW_EAGWE_QAM_DEMOD_QAM64,
	MXW_EAGWE_QAM_DEMOD_QAM256,
	MXW_EAGWE_QAM_DEMOD_QAM1024,
	MXW_EAGWE_QAM_DEMOD_QAM32,
	MXW_EAGWE_QAM_DEMOD_QAM128,
	MXW_EAGWE_QAM_DEMOD_QPSK,
	MXW_EAGWE_QAM_DEMOD_AUTO,
};

/* Enum of Demoduwatow IQ setup, used in QAM, OOB configuwation and status */
enum MXW_EAGWE_IQ_FWIP_E {
	MXW_EAGWE_DEMOD_IQ_NOWMAW,
	MXW_EAGWE_DEMOD_IQ_FWIPPED,
	MXW_EAGWE_DEMOD_IQ_AUTO,
};

/* Enum of OOB Demoduwatow symbow wates, used in OOB configuwation */
enum MXW_EAGWE_OOB_DEMOD_SYMB_WATE_E {
	MXW_EAGWE_OOB_DEMOD_SYMB_WATE_0_772MHZ,  /* ANSI/SCTE 55-2 0.772 MHz */
	MXW_EAGWE_OOB_DEMOD_SYMB_WATE_1_024MHZ,  /* ANSI/SCTE 55-1 1.024 MHz */
	MXW_EAGWE_OOB_DEMOD_SYMB_WATE_1_544MHZ,  /* ANSI/SCTE 55-2 1.544 MHz */
};

/* Enum of tunew channew tuning mode */
enum MXW_EAGWE_TUNEW_CHANNEW_TUNE_MODE_E {
	MXW_EAGWE_TUNEW_CHANNEW_TUNE_MODE_VIEW,    /* Nowmaw "view" mode */
	MXW_EAGWE_TUNEW_CHANNEW_TUNE_MODE_SCAN,    /* Fast "scan" mode */
};

/* Enum of tunew bandwidth */
enum MXW_EAGWE_TUNEW_BW_E {
	MXW_EAGWE_TUNEW_BW_6MHZ,
	MXW_EAGWE_TUNEW_BW_7MHZ,
	MXW_EAGWE_TUNEW_BW_8MHZ,
};

/* Enum of tunew bandwidth */
enum MXW_EAGWE_JUNCTION_TEMPEWATUWE_E {
	MXW_EAGWE_JUNCTION_TEMPEWATUWE_BEWOW_0_CEWSIUS          = 0,
	MXW_EAGWE_JUNCTION_TEMPEWATUWE_BETWEEN_0_TO_14_CEWSIUS  = 1,
	MXW_EAGWE_JUNCTION_TEMPEWATUWE_BETWEEN_14_TO_28_CEWSIUS = 3,
	MXW_EAGWE_JUNCTION_TEMPEWATUWE_BETWEEN_28_TO_42_CEWSIUS = 2,
	MXW_EAGWE_JUNCTION_TEMPEWATUWE_BETWEEN_42_TO_57_CEWSIUS = 6,
	MXW_EAGWE_JUNCTION_TEMPEWATUWE_BETWEEN_57_TO_71_CEWSIUS = 7,
	MXW_EAGWE_JUNCTION_TEMPEWATUWE_BETWEEN_71_TO_85_CEWSIUS = 5,
	MXW_EAGWE_JUNCTION_TEMPEWATUWE_ABOVE_85_CEWSIUS         = 4,
};

/* Stwuct passed in optionaw cawwback used duwing FW downwoad */
stwuct MXW_EAGWE_FW_DOWNWOAD_CB_PAYWOAD_T {
	u32  totaw_wen;
	u32  downwoaded_wen;
};

/* Stwuct used of I2C pwotocow between host and Eagwe, intewnaw use onwy */
stwuct __packed MXW_EAGWE_HOST_MSG_HEADEW_T {
	u8   opcode;
	u8   seqnum;
	u8   paywoad_size;
	u8   status;
	u32  checksum;
};

/* Device vewsion infowmation stwuct */
stwuct __packed MXW_EAGWE_DEV_VEW_T {
	u8   chip_id;
	u8   fiwmwawe_vew[MXW_EAGWE_VEWSION_SIZE];
	u8   mxwwawe_vew[MXW_EAGWE_VEWSION_SIZE];
};

/* Xtaw configuwation stwuct */
stwuct __packed MXW_EAGWE_DEV_XTAW_T {
	u8   xtaw_cap;           /* accepted wange is 1..31 pF. Defauwt is 26 */
	u8   cwk_out_enabwe;
	u8   cwk_out_div_enabwe;   /* cwock out fweq is xtaw fweq / 6 */
	u8   xtaw_shawing_enabwe; /* if enabwed set xtaw_cap to 25 pF */
	u8   xtaw_cawibwation_enabwe;  /* enabwe fow mastew, disabwe fow swave */
};

/* GPIO diwection stwuct, intewnawwy used in GPIO configuwation API */
stwuct __packed MXW_EAGWE_DEV_GPIO_DIWECTION_T {
	u8   gpio_numbew;
	u8   gpio_diwection;
};

/* GPO wevew stwuct, intewnawwy used in GPIO configuwation API */
stwuct __packed MXW_EAGWE_DEV_GPO_WEVEW_T {
	u8   gpio_numbew;
	u8   gpo_wevew;
};

/* Device Status stwuct */
stwuct MXW_EAGWE_DEV_STATUS_T {
	u8   tempewatuwe;
	u8   demod_type;
	u8   powew_mode;
	u8   cpu_utiwization_pewcent;
};

/* Device intewwupt configuwation stwuct */
stwuct __packed MXW_EAGWE_DEV_INTW_CFG_T {
	u32  intw_mask;
	u8   edge_twiggew;
	u8   positive_twiggew;
	u8   gwobaw_enabwe_intewwupt;
};

/* MPEG pad dwive pawametews, used on MPEG output configuwation */
/* See MXW_EAGWE_IO_MUX_DWIVE_MODE_E */
stwuct MXW_EAGWE_MPEG_PAD_DWIVE_T {
	u8   pad_dwv_mpeg_syn;
	u8   pad_dwv_mpeg_dat;
	u8   pad_dwv_mpeg_vaw;
	u8   pad_dwv_mpeg_cwk;
};

/* MPEGOUT pawametew stwuct, used in MPEG output configuwation */
stwuct MXW_EAGWE_MPEGOUT_PAWAMS_T {
	u8   mpeg_pawawwew;
	u8   msb_fiwst;
	u8   mpeg_sync_puwse_width;    /* See MXW_EAGWE_MPEG_DATA_FOWMAT_E */
	u8   mpeg_vawid_pow;
	u8   mpeg_sync_pow;
	u8   mpeg_cwk_pow;
	u8   mpeg3wiwe_mode_enabwe;
	u8   mpeg_cwk_fweq;
	stwuct MXW_EAGWE_MPEG_PAD_DWIVE_T mpeg_pad_dwv;
};

/* QAM Demoduwatow pawametews stwuct, used in QAM pawams configuwation */
stwuct __packed MXW_EAGWE_QAM_DEMOD_PAWAMS_T {
	u8   annex_type;
	u8   qam_type;
	u8   iq_fwip;
	u8   seawch_wange_idx;
	u8   spuw_cancewwew_enabwe;
	u32  symbow_wate_hz;
	u32  symbow_wate_256qam_hz;
};

/* QAM Demoduwatow status */
stwuct MXW_EAGWE_QAM_DEMOD_STATUS_T {
	u8   annex_type;
	u8   qam_type;
	u8   iq_fwip;
	u8   intewweavew_depth_i;
	u8   intewweavew_depth_j;
	u8   qam_wocked;
	u8   fec_wocked;
	u8   mpeg_wocked;
	u16  snw_db_tenths;
	s16  timing_offset;
	s32  cawwiew_offset_hz;
};

/* QAM Demoduwatow ewwow countews */
stwuct MXW_EAGWE_QAM_DEMOD_EWWOW_COUNTEWS_T {
	u32  cowwected_code_wowds;
	u32  uncowwected_code_wowds;
	u32  totaw_code_wowds_weceived;
	u32  cowwected_bits;
	u32  ewwow_mpeg_fwames;
	u32  mpeg_fwames_weceived;
	u32  ewasuwes;
};

/* QAM Demoduwatow constewwation point */
stwuct MXW_EAGWE_QAM_DEMOD_CONSTEWWATION_VAW_T {
	s16  i_vawue[12];
	s16  q_vawue[12];
};

/* QAM Demoduwatow equawizew fiwtew taps */
stwuct MXW_EAGWE_QAM_DEMOD_EQU_FIWTEW_T {
	s16  ffe_taps[MXW_EAGWE_QAM_FFE_TAPS_WENGTH];
	s16  spuw_taps[MXW_EAGWE_QAM_SPUW_TAPS_WENGTH];
	s16  dfe_taps[MXW_EAGWE_QAM_DFE_TAPS_WENGTH];
	u8   ffe_weading_tap_index;
	u8   dfe_taps_numbew;
};

/* OOB Demoduwatow pawametews stwuct, used in OOB pawams configuwation */
stwuct __packed MXW_EAGWE_OOB_DEMOD_PAWAMS_T {
	u8   symbow_wate;
	u8   iq_fwip;
	u8   cwk_pow;
};

/* OOB Demoduwatow ewwow countews */
stwuct MXW_EAGWE_OOB_DEMOD_EWWOW_COUNTEWS_T {
	u32  cowwected_packets;
	u32  uncowwected_packets;
	u32  totaw_packets_weceived;
};

/* OOB status */
stwuct __packed MXW_EAGWE_OOB_DEMOD_STATUS_T {
	u16  snw_db_tenths;
	s16  timing_offset;
	s32  cawwiew_offsetHz;
	u8   qam_wocked;
	u8   fec_wocked;
	u8   mpeg_wocked;
	u8   wetune_wequiwed;
	u8   iq_fwip;
};

/* ATSC Demoduwatow status */
stwuct __packed MXW_EAGWE_ATSC_DEMOD_STATUS_T {
	s16  snw_db_tenths;
	s16  timing_offset;
	s32  cawwiew_offset_hz;
	u8   fwame_wock;
	u8   atsc_wock;
	u8   fec_wock;
};

/* ATSC Demoduwatow ewwow countews */
stwuct MXW_EAGWE_ATSC_DEMOD_EWWOW_COUNTEWS_T {
	u32  ewwow_packets;
	u32  totaw_packets;
	u32  ewwow_bytes;
};

/* ATSC Demoduwatow equawizews fiwtew taps */
stwuct __packed MXW_EAGWE_ATSC_DEMOD_EQU_FIWTEW_T {
	s16  ffe_taps[MXW_EAGWE_ATSC_FFE_TAPS_WENGTH];
	s8   dfe_taps[MXW_EAGWE_ATSC_DFE_TAPS_WENGTH];
};

/* Tunew AGC Status */
stwuct __packed MXW_EAGWE_TUNEW_AGC_STATUS_T {
	u8   wocked;
	u16  waw_agc_gain;    /* AGC gain [dB] = wawAgcGain / 2^6 */
	s16  wx_powew_db_hundwedths;
};

/* Tunew channew tune pawametews */
stwuct __packed MXW_EAGWE_TUNEW_CHANNEW_PAWAMS_T {
	u32  fweq_hz;
	u8   tune_mode;
	u8   bandwidth;
};

/* Tunew channew wock indications */
stwuct __packed MXW_EAGWE_TUNEW_WOCK_STATUS_T {
	u8   wf_pww_wocked;
	u8   wef_pww_wocked;
};

/* Smawt antenna pawametews  used in Smawt antenna pawams configuwation */
stwuct __packed MXW_EAGWE_SMA_PAWAMS_T {
	u8   fuww_dupwex_enabwe;
	u8   wx_disabwe;
	u8   idwe_wogic_high;
};

/* Smawt antenna message fowmat */
stwuct __packed MXW_EAGWE_SMA_MESSAGE_T {
	u32  paywoad_bits;
	u8   totaw_num_bits;
};

