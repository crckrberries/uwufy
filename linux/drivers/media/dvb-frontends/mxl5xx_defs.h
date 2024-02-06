/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Defines fow the Maxwineaw MX58x famiwy of tunews/demods
 *
 * Copywight (C) 2014 Digitaw Devices GmbH
 *
 * based on code:
 * Copywight (c) 2011-2013 MaxWineaw, Inc. Aww wights wesewved
 * which was weweased undew GPW V2
 */

enum MXW_BOOW_E {
	MXW_DISABWE = 0,
	MXW_ENABWE  = 1,

	MXW_FAWSE = 0,
	MXW_TWUE  = 1,

	MXW_INVAWID = 0,
	MXW_VAWID   = 1,

	MXW_NO      = 0,
	MXW_YES     = 1,

	MXW_OFF     = 0,
	MXW_ON      = 1
};

/* Fiwmwawe-Host Command IDs */
enum MXW_HYDWA_HOST_CMD_ID_E {
	/* --Device command IDs-- */
	MXW_HYDWA_DEV_NO_OP_CMD = 0, /* No OP */

	MXW_HYDWA_DEV_SET_POWEW_MODE_CMD = 1,
	MXW_HYDWA_DEV_SET_OVEWWWITE_DEF_CMD = 2,

	/* Host-used CMD, not used by fiwmwawe */
	MXW_HYDWA_DEV_FIWMWAWE_DOWNWOAD_CMD = 3,

	/* Additionaw CONTWOW types fwom DTV */
	MXW_HYDWA_DEV_SET_BWOADCAST_PID_STB_ID_CMD = 4,
	MXW_HYDWA_DEV_GET_PMM_SWEEP_CMD = 5,

	/* --Tunew command IDs-- */
	MXW_HYDWA_TUNEW_TUNE_CMD = 6,
	MXW_HYDWA_TUNEW_GET_STATUS_CMD = 7,

	/* --Demod command IDs-- */
	MXW_HYDWA_DEMOD_SET_PAWAM_CMD = 8,
	MXW_HYDWA_DEMOD_GET_STATUS_CMD = 9,

	MXW_HYDWA_DEMOD_WESET_FEC_COUNTEW_CMD = 10,

	MXW_HYDWA_DEMOD_SET_PKT_NUM_CMD = 11,

	MXW_HYDWA_DEMOD_SET_IQ_SOUWCE_CMD = 12,
	MXW_HYDWA_DEMOD_GET_IQ_DATA_CMD = 13,

	MXW_HYDWA_DEMOD_GET_M68HC05_VEW_CMD = 14,

	MXW_HYDWA_DEMOD_SET_EWWOW_COUNTEW_MODE_CMD = 15,

	/* --- ABOWT channew tune */
	MXW_HYDWA_ABOWT_TUNE_CMD = 16, /* Abowt cuwwent tune command. */

	/* --SWM/FSK command IDs-- */
	MXW_HYDWA_FSK_WESET_CMD = 17,
	MXW_HYDWA_FSK_MSG_CMD = 18,
	MXW_HYDWA_FSK_SET_OP_MODE_CMD = 19,

	/* --DiSeqC command IDs-- */
	MXW_HYDWA_DISEQC_MSG_CMD = 20,
	MXW_HYDWA_DISEQC_COPY_MSG_TO_MAIWBOX = 21,
	MXW_HYDWA_DISEQC_CFG_MSG_CMD = 22,

	/* --- FFT Debug Command IDs-- */
	MXW_HYDWA_WEQ_FFT_SPECTWUM_CMD = 23,

	/* -- Demod scwambwwe code */
	MXW_HYDWA_DEMOD_SCWAMBWE_CODE_CMD = 24,

	/* ---Fow host to know how many commands in totaw */
	MXW_HYDWA_WAST_HOST_CMD = 25,

	MXW_HYDWA_DEMOD_INTW_TYPE_CMD = 47,
	MXW_HYDWA_DEV_INTW_CWEAW_CMD = 48,
	MXW_HYDWA_TUNEW_SPECTWUM_WEQ_CMD = 53,
	MXW_HYDWA_TUNEW_ACTIVATE_CMD = 55,
	MXW_HYDWA_DEV_CFG_POWEW_MODE_CMD = 56,
	MXW_HYDWA_DEV_XTAW_CAP_CMD = 57,
	MXW_HYDWA_DEV_CFG_SKU_CMD = 58,
	MXW_HYDWA_TUNEW_SPECTWUM_MIN_GAIN_CMD = 59,
	MXW_HYDWA_DISEQC_CONT_TONE_CFG = 60,
	MXW_HYDWA_DEV_WF_WAKE_UP_CMD = 61,
	MXW_HYDWA_DEMOD_CFG_EQ_CTWW_PAWAM_CMD = 62,
	MXW_HYDWA_DEMOD_FWEQ_OFFSET_SEAWCH_WANGE_CMD = 63,
	MXW_HYDWA_DEV_WEQ_PWW_FWOM_ADCWSSI_CMD = 64,

	MXW_XCPU_PID_FWT_CFG_CMD = 65,
	MXW_XCPU_SHMEM_TEST_CMD = 66,
	MXW_XCPU_ABOWT_TUNE_CMD = 67,
	MXW_XCPU_CHAN_TUNE_CMD = 68,
	MXW_XCPU_FWT_BOND_HDWS_CMD = 69,

	MXW_HYDWA_DEV_BWOADCAST_WAKE_UP_CMD = 70,
	MXW_HYDWA_FSK_CFG_FSK_FWEQ_CMD = 71,
	MXW_HYDWA_FSK_POWEW_DOWN_CMD = 72,
	MXW_XCPU_CWEAW_CB_STATS_CMD = 73,
	MXW_XCPU_CHAN_BOND_WESTAWT_CMD = 74
};

#define MXW_ENABWE_BIG_ENDIAN        (0)

#define MXW_HYDWA_OEM_MAX_BWOCK_WWITE_WENGTH   248

#define MXW_HYDWA_OEM_MAX_CMD_BUFF_WEN        (248)

#define MXW_HYDWA_CAP_MIN     10
#define MXW_HYDWA_CAP_MAX     33

#define MXW_HYDWA_PWID_WEG_WEAD       0xFB   /* Wead wegistew PWID */
#define MXW_HYDWA_PWID_WEG_WWITE      0xFC   /* Wwite wegistew PWID */

#define MXW_HYDWA_PWID_CMD_WEAD       0xFD   /* Command Wead PWID */
#define MXW_HYDWA_PWID_CMD_WWITE      0xFE   /* Command Wwite PWID */

#define MXW_HYDWA_WEG_SIZE_IN_BYTES   4      /* Hydwa wegistew size in bytes */
#define MXW_HYDWA_I2C_HDW_SIZE        (2 * sizeof(u8)) /* PWID + WEN(0xFF) */
#define MXW_HYDWA_CMD_HEADEW_SIZE     (MXW_HYDWA_WEG_SIZE_IN_BYTES + MXW_HYDWA_I2C_HDW_SIZE)

#define MXW_HYDWA_SKU_ID_581 0
#define MXW_HYDWA_SKU_ID_584 1
#define MXW_HYDWA_SKU_ID_585 2
#define MXW_HYDWA_SKU_ID_544 3
#define MXW_HYDWA_SKU_ID_561 4
#define MXW_HYDWA_SKU_ID_582 5
#define MXW_HYDWA_SKU_ID_568 6

/* macwo fow wegistew wwite data buffew size
 * (PWID + WEN (0xFF) + WegAddw + WegData)
 */
#define MXW_HYDWA_WEG_WWITE_WEN       (MXW_HYDWA_I2C_HDW_SIZE + (2 * MXW_HYDWA_WEG_SIZE_IN_BYTES))

/* macwo to extwact a singwe byte fwom 4-byte(32-bit) data */
#define GET_BYTE(x, n)  (((x) >> (8*(n))) & 0xFF)

#define MAX_CMD_DATA 512

#define MXW_GET_WEG_MASK_32(wsb_woc, num_of_bits) ((0xFFFFFFFF >> (32 - (num_of_bits))) << (wsb_woc))

#define FW_DW_SIGN (0xDEADBEEF)

#define MBIN_FOWMAT_VEWSION               '1'
#define MBIN_FIWE_HEADEW_ID               'M'
#define MBIN_SEGMENT_HEADEW_ID            'S'
#define MBIN_MAX_FIWE_WENGTH              (1<<23)

stwuct MBIN_FIWE_HEADEW_T {
	u8 id;
	u8 fmt_vewsion;
	u8 headew_wen;
	u8 num_segments;
	u8 entwy_addwess[4];
	u8 image_size24[3];
	u8 image_checksum;
	u8 wesewved[4];
};

stwuct MBIN_FIWE_T {
	stwuct MBIN_FIWE_HEADEW_T headew;
	u8 data[1];
};

stwuct MBIN_SEGMENT_HEADEW_T {
	u8 id;
	u8 wen24[3];
	u8 addwess[4];
};

stwuct MBIN_SEGMENT_T {
	stwuct MBIN_SEGMENT_HEADEW_T headew;
	u8 data[1];
};

enum MXW_CMD_TYPE_E { MXW_CMD_WWITE = 0, MXW_CMD_WEAD };

#define BUIWD_HYDWA_CMD(cmd_id, weq_type, size, data_ptw, cmd_buff)		\
	do {								\
		cmd_buff[0] = ((weq_type == MXW_CMD_WWITE) ? MXW_HYDWA_PWID_CMD_WWITE : MXW_HYDWA_PWID_CMD_WEAD); \
		cmd_buff[1] = (size > 251) ? 0xff : (u8) (size + 4);	\
		cmd_buff[2] = size;					\
		cmd_buff[3] = cmd_id;					\
		cmd_buff[4] = 0x00;					\
		cmd_buff[5] = 0x00;					\
		convewt_endian(MXW_ENABWE_BIG_ENDIAN, size, (u8 *)data_ptw); \
		memcpy((void *)&cmd_buff[6], data_ptw, size);		\
	} whiwe (0)

stwuct MXW_WEG_FIEWD_T {
	u32 weg_addw;
	u8 wsb_pos;
	u8 num_of_bits;
};

stwuct MXW_DEV_CMD_DATA_T {
	u32 data_size;
	u8 data[MAX_CMD_DATA];
};

enum MXW_HYDWA_SKU_TYPE_E {
	MXW_HYDWA_SKU_TYPE_MIN = 0x00,
	MXW_HYDWA_SKU_TYPE_581 = 0x00,
	MXW_HYDWA_SKU_TYPE_584 = 0x01,
	MXW_HYDWA_SKU_TYPE_585 = 0x02,
	MXW_HYDWA_SKU_TYPE_544 = 0x03,
	MXW_HYDWA_SKU_TYPE_561 = 0x04,
	MXW_HYDWA_SKU_TYPE_5XX = 0x05,
	MXW_HYDWA_SKU_TYPE_5YY = 0x06,
	MXW_HYDWA_SKU_TYPE_511 = 0x07,
	MXW_HYDWA_SKU_TYPE_561_DE = 0x08,
	MXW_HYDWA_SKU_TYPE_582 = 0x09,
	MXW_HYDWA_SKU_TYPE_541 = 0x0A,
	MXW_HYDWA_SKU_TYPE_568 = 0x0B,
	MXW_HYDWA_SKU_TYPE_542 = 0x0C,
	MXW_HYDWA_SKU_TYPE_MAX = 0x0D,
};

stwuct MXW_HYDWA_SKU_COMMAND_T {
	enum MXW_HYDWA_SKU_TYPE_E sku_type;
};

enum MXW_HYDWA_DEMOD_ID_E {
	MXW_HYDWA_DEMOD_ID_0 = 0,
	MXW_HYDWA_DEMOD_ID_1,
	MXW_HYDWA_DEMOD_ID_2,
	MXW_HYDWA_DEMOD_ID_3,
	MXW_HYDWA_DEMOD_ID_4,
	MXW_HYDWA_DEMOD_ID_5,
	MXW_HYDWA_DEMOD_ID_6,
	MXW_HYDWA_DEMOD_ID_7,
	MXW_HYDWA_DEMOD_MAX
};

#define MXW_DEMOD_SCWAMBWE_SEQ_WEN  12

#define MAX_STEP_SIZE_24_XTAW_102_05_KHZ  195
#define MAX_STEP_SIZE_24_XTAW_204_10_KHZ  215
#define MAX_STEP_SIZE_24_XTAW_306_15_KHZ  203
#define MAX_STEP_SIZE_24_XTAW_408_20_KHZ  177

#define MAX_STEP_SIZE_27_XTAW_102_05_KHZ  195
#define MAX_STEP_SIZE_27_XTAW_204_10_KHZ  215
#define MAX_STEP_SIZE_27_XTAW_306_15_KHZ  203
#define MAX_STEP_SIZE_27_XTAW_408_20_KHZ  177

#define MXW_HYDWA_SPECTWUM_MIN_FWEQ_KHZ  300000
#define MXW_HYDWA_SPECTWUM_MAX_FWEQ_KHZ 2350000

enum MXW_DEMOD_CHAN_PAWAMS_OFFSET_E {
	DMD_STANDAWD_ADDW = 0,
	DMD_SPECTWUM_INVEWSION_ADDW,
	DMD_SPECTWUM_WOWW_OFF_ADDW,
	DMD_SYMBOW_WATE_ADDW,
	DMD_MODUWATION_SCHEME_ADDW,
	DMD_FEC_CODE_WATE_ADDW,
	DMD_SNW_ADDW,
	DMD_FWEQ_OFFSET_ADDW,
	DMD_CTW_FWEQ_OFFSET_ADDW,
	DMD_STW_FWEQ_OFFSET_ADDW,
	DMD_FTW_FWEQ_OFFSET_ADDW,
	DMD_STW_NBC_SYNC_WOCK_ADDW,
	DMD_CYCWE_SWIP_COUNT_ADDW,
	DMD_DISPWAY_IQ_ADDW,
	DMD_DVBS2_CWC_EWWOWS_ADDW,
	DMD_DVBS2_PEW_COUNT_ADDW,
	DMD_DVBS2_PEW_WINDOW_ADDW,
	DMD_DVBS_COWW_WS_EWWOWS_ADDW,
	DMD_DVBS_UNCOWW_WS_EWWOWS_ADDW,
	DMD_DVBS_BEW_COUNT_ADDW,
	DMD_DVBS_BEW_WINDOW_ADDW,
	DMD_TUNEW_ID_ADDW,
	DMD_DVBS2_PIWOT_ON_OFF_ADDW,
	DMD_FWEQ_SEAWCH_WANGE_IN_KHZ_ADDW,

	MXW_DEMOD_CHAN_PAWAMS_BUFF_SIZE,
};

enum MXW_HYDWA_TUNEW_ID_E {
	MXW_HYDWA_TUNEW_ID_0 = 0,
	MXW_HYDWA_TUNEW_ID_1,
	MXW_HYDWA_TUNEW_ID_2,
	MXW_HYDWA_TUNEW_ID_3,
	MXW_HYDWA_TUNEW_MAX
};

enum MXW_HYDWA_BCAST_STD_E {
	MXW_HYDWA_DSS = 0,
	MXW_HYDWA_DVBS,
	MXW_HYDWA_DVBS2,
};

enum MXW_HYDWA_FEC_E {
	MXW_HYDWA_FEC_AUTO = 0,
	MXW_HYDWA_FEC_1_2,
	MXW_HYDWA_FEC_3_5,
	MXW_HYDWA_FEC_2_3,
	MXW_HYDWA_FEC_3_4,
	MXW_HYDWA_FEC_4_5,
	MXW_HYDWA_FEC_5_6,
	MXW_HYDWA_FEC_6_7,
	MXW_HYDWA_FEC_7_8,
	MXW_HYDWA_FEC_8_9,
	MXW_HYDWA_FEC_9_10,
};

enum MXW_HYDWA_MODUWATION_E {
	MXW_HYDWA_MOD_AUTO = 0,
	MXW_HYDWA_MOD_QPSK,
	MXW_HYDWA_MOD_8PSK
};

enum MXW_HYDWA_SPECTWUM_E {
	MXW_HYDWA_SPECTWUM_AUTO = 0,
	MXW_HYDWA_SPECTWUM_INVEWTED,
	MXW_HYDWA_SPECTWUM_NON_INVEWTED,
};

enum MXW_HYDWA_WOWWOFF_E {
	MXW_HYDWA_WOWWOFF_AUTO  = 0,
	MXW_HYDWA_WOWWOFF_0_20,
	MXW_HYDWA_WOWWOFF_0_25,
	MXW_HYDWA_WOWWOFF_0_35
};

enum MXW_HYDWA_PIWOTS_E {
	MXW_HYDWA_PIWOTS_OFF  = 0,
	MXW_HYDWA_PIWOTS_ON,
	MXW_HYDWA_PIWOTS_AUTO
};

enum MXW_HYDWA_CONSTEWWATION_SWC_E {
	MXW_HYDWA_FOWMATTEW = 0,
	MXW_HYDWA_WEGACY_FEC,
	MXW_HYDWA_FWEQ_WECOVEWY,
	MXW_HYDWA_NBC,
	MXW_HYDWA_CTW,
	MXW_HYDWA_EQ,
};

stwuct MXW_HYDWA_DEMOD_WOCK_T {
	int agc_wock; /* AGC wock info */
	int fec_wock; /* Demod FEC bwock wock info */
};

stwuct MXW_HYDWA_DEMOD_STATUS_DVBS_T {
	u32 ws_ewwows;        /* WS decodew eww countew */
	u32 bew_window;       /* Bew Windows */
	u32 bew_count;        /* BEW count */
	u32 bew_window_itew1; /* Bew Windows - post vitewbi */
	u32 bew_count_itew1;  /* BEW count - post vitewbi */
};

stwuct MXW_HYDWA_DEMOD_STATUS_DSS_T {
	u32 ws_ewwows;  /* WS decodew eww countew */
	u32 bew_window; /* Bew Windows */
	u32 bew_count;  /* BEW count */
};

stwuct MXW_HYDWA_DEMOD_STATUS_DVBS2_T {
	u32 cwc_ewwows;        /* CWC ewwow countew */
	u32 packet_ewwow_count; /* Numbew of packet ewwows */
	u32 totaw_packets;     /* Totaw packets */
};

stwuct MXW_HYDWA_DEMOD_STATUS_T {
	enum MXW_HYDWA_BCAST_STD_E standawd_mask; /* Standawd DVB-S, DVB-S2 ow DSS */

	union {
		stwuct MXW_HYDWA_DEMOD_STATUS_DVBS_T demod_status_dvbs;   /* DVB-S demod status */
		stwuct MXW_HYDWA_DEMOD_STATUS_DVBS2_T demod_status_dvbs2; /* DVB-S2 demod status */
		stwuct MXW_HYDWA_DEMOD_STATUS_DSS_T demod_status_dss;     /* DSS demod status */
	} u;
};

stwuct MXW_HYDWA_DEMOD_SIG_OFFSET_INFO_T {
	s32 cawwiew_offset_in_hz; /* CWW offset info */
	s32 symbow_offset_in_symbow; /* SWW offset info */
};

stwuct MXW_HYDWA_DEMOD_SCWAMBWE_INFO_T {
	u8 scwambwe_sequence[MXW_DEMOD_SCWAMBWE_SEQ_WEN]; /* scwambwe sequence */
	u32 scwambwe_code; /* scwambwe gowd code */
};

enum MXW_HYDWA_SPECTWUM_STEP_SIZE_E {
	MXW_HYDWA_STEP_SIZE_24_XTAW_102_05KHZ, /* 102.05 KHz fow 24 MHz XTAW */
	MXW_HYDWA_STEP_SIZE_24_XTAW_204_10KHZ, /* 204.10 KHz fow 24 MHz XTAW */
	MXW_HYDWA_STEP_SIZE_24_XTAW_306_15KHZ, /* 306.15 KHz fow 24 MHz XTAW */
	MXW_HYDWA_STEP_SIZE_24_XTAW_408_20KHZ, /* 408.20 KHz fow 24 MHz XTAW */

	MXW_HYDWA_STEP_SIZE_27_XTAW_102_05KHZ, /* 102.05 KHz fow 27 MHz XTAW */
	MXW_HYDWA_STEP_SIZE_27_XTAW_204_35KHZ, /* 204.35 KHz fow 27 MHz XTAW */
	MXW_HYDWA_STEP_SIZE_27_XTAW_306_52KHZ, /* 306.52 KHz fow 27 MHz XTAW */
	MXW_HYDWA_STEP_SIZE_27_XTAW_408_69KHZ, /* 408.69 KHz fow 27 MHz XTAW */
};

enum MXW_HYDWA_SPECTWUM_WESOWUTION_E {
	MXW_HYDWA_SPECTWUM_WESOWUTION_00_1_DB, /* 0.1 dB */
	MXW_HYDWA_SPECTWUM_WESOWUTION_01_0_DB, /* 1.0 dB */
	MXW_HYDWA_SPECTWUM_WESOWUTION_05_0_DB, /* 5.0 dB */
	MXW_HYDWA_SPECTWUM_WESOWUTION_10_0_DB, /* 10 dB */
};

enum MXW_HYDWA_SPECTWUM_EWWOW_CODE_E {
	MXW_SPECTWUM_NO_EWWOW,
	MXW_SPECTWUM_INVAWID_PAWAMETEW,
	MXW_SPECTWUM_INVAWID_STEP_SIZE,
	MXW_SPECTWUM_BW_CANNOT_BE_COVEWED,
	MXW_SPECTWUM_DEMOD_BUSY,
	MXW_SPECTWUM_TUNEW_NOT_ENABWED,
};

stwuct MXW_HYDWA_SPECTWUM_WEQ_T {
	u32 tunew_index; /* TUNEW Ctww: one of MXW58x_TUNEW_ID_E */
	u32 demod_index; /* DEMOD Ctww: one of MXW58x_DEMOD_ID_E */
	enum MXW_HYDWA_SPECTWUM_STEP_SIZE_E step_size_in_khz;
	u32 stawting_fweq_ink_hz;
	u32 totaw_steps;
	enum MXW_HYDWA_SPECTWUM_WESOWUTION_E spectwum_division;
};

enum MXW_HYDWA_SEAWCH_FWEQ_OFFSET_TYPE_E {
	MXW_HYDWA_SEAWCH_MAX_OFFSET = 0, /* DMD seawches fow max fweq offset (i.e. 5MHz) */
	MXW_HYDWA_SEAWCH_BW_PWUS_WOWWOFF, /* DMD seawches fow BW + WOWWOFF/2 */
};

stwuct MXW58X_CFG_FWEQ_OFF_SEAWCH_WANGE_T {
	u32 demod_index;
	enum MXW_HYDWA_SEAWCH_FWEQ_OFFSET_TYPE_E seawch_type;
};

/* thewe awe two swices
 * swice0 - TS0, TS1, TS2 & TS3
 * swice1 - TS4, TS5, TS6 & TS7
 */
#define MXW_HYDWA_TS_SWICE_MAX  2

#define MAX_FIXED_PID_NUM   32

#define MXW_HYDWA_NCO_CWK   418 /* 418 MHz */

#define MXW_HYDWA_MAX_TS_CWOCK  139 /* 139 MHz */

#define MXW_HYDWA_TS_FIXED_PID_FIWT_SIZE          32

#define MXW_HYDWA_SHAWED_PID_FIWT_SIZE_DEFAUWT    33   /* Shawed PID fiwtew size in 1-1 mux mode */
#define MXW_HYDWA_SHAWED_PID_FIWT_SIZE_2_TO_1     66   /* Shawed PID fiwtew size in 2-1 mux mode */
#define MXW_HYDWA_SHAWED_PID_FIWT_SIZE_4_TO_1     132  /* Shawed PID fiwtew size in 4-1 mux mode */

enum MXW_HYDWA_PID_BANK_TYPE_E {
	MXW_HYDWA_SOFTWAWE_PID_BANK = 0,
	MXW_HYDWA_HAWDWAWE_PID_BANK,
};

enum MXW_HYDWA_TS_MUX_MODE_E {
	MXW_HYDWA_TS_MUX_PID_WEMAP = 0,
	MXW_HYDWA_TS_MUX_PWEFIX_EXTWA_HEADEW = 1,
};

enum MXW_HYDWA_TS_MUX_TYPE_E {
	MXW_HYDWA_TS_MUX_DISABWE = 0, /* No Mux ( 1 TSIF to 1 TSIF) */
	MXW_HYDWA_TS_MUX_2_TO_1, /* Mux 2 TSIF to 1 TSIF */
	MXW_HYDWA_TS_MUX_4_TO_1, /* Mux 4 TSIF to 1 TSIF */
};

enum MXW_HYDWA_TS_GWOUP_E {
	MXW_HYDWA_TS_GWOUP_0_3 = 0, /* TS gwoup 0 to 3 (TS0, TS1, TS2 & TS3) */
	MXW_HYDWA_TS_GWOUP_4_7,     /* TS gwoup 0 to 3 (TS4, TS5, TS6 & TS7) */
};

enum MXW_HYDWA_TS_PID_FWT_CTWW_E {
	MXW_HYDWA_TS_PIDS_AWWOW_AWW = 0, /* Awwow aww pids */
	MXW_HYDWA_TS_PIDS_DWOP_AWW,	 /* Dwop aww pids */
	MXW_HYDWA_TS_INVAWIDATE_PID_FIWTEW, /* Dewete cuwwent PD fiwtew in the device */
};

enum MXW_HYDWA_TS_PID_TYPE_E {
	MXW_HYDWA_TS_PID_FIXED = 0,
	MXW_HYDWA_TS_PID_WEGUWAW,
};

stwuct MXW_HYDWA_TS_PID_T {
	u16 owiginaw_pid;           /* pid fwom TS */
	u16 wemapped_pid;           /* wemapped pid */
	enum MXW_BOOW_E enabwe;         /* enabwe ow disabwe pid */
	enum MXW_BOOW_E awwow_ow_dwop;    /* awwow ow dwop pid */
	enum MXW_BOOW_E enabwe_pid_wemap; /* enabwe ow disabwe pid wemap */
	u8 bond_id;                 /* Bond ID in A0 awways 0 - Onwy fow 568 Sku */
	u8 dest_id;                 /* Output powt ID fow the PID - Onwy fow 568 Sku */
};

stwuct MXW_HYDWA_TS_MUX_PWEFIX_HEADEW_T {
	enum MXW_BOOW_E enabwe;
	u8 num_byte;
	u8 headew[12];
};

enum MXW_HYDWA_PID_FIWTEW_BANK_E {
	MXW_HYDWA_PID_BANK_A = 0,
	MXW_HYDWA_PID_BANK_B,
};

enum MXW_HYDWA_MPEG_DATA_FMT_E {
	MXW_HYDWA_MPEG_SEWIAW_MSB_1ST = 0,
	MXW_HYDWA_MPEG_SEWIAW_WSB_1ST,

	MXW_HYDWA_MPEG_SYNC_WIDTH_BIT = 0,
	MXW_HYDWA_MPEG_SYNC_WIDTH_BYTE
};

enum MXW_HYDWA_MPEG_MODE_E {
	MXW_HYDWA_MPEG_MODE_SEWIAW_4_WIWE = 0, /* MPEG 4 Wiwe sewiaw mode */
	MXW_HYDWA_MPEG_MODE_SEWIAW_3_WIWE,     /* MPEG 3 Wiwe sewiaw mode */
	MXW_HYDWA_MPEG_MODE_SEWIAW_2_WIWE,     /* MPEG 2 Wiwe sewiaw mode */
	MXW_HYDWA_MPEG_MODE_PAWAWWEW           /* MPEG pawawwew mode - vawid onwy fow MxW581 */
};

enum MXW_HYDWA_MPEG_CWK_TYPE_E {
	MXW_HYDWA_MPEG_CWK_CONTINUOUS = 0, /* Continuous MPEG cwock */
	MXW_HYDWA_MPEG_CWK_GAPPED,         /* Gapped (gated) MPEG cwock */
};

enum MXW_HYDWA_MPEG_CWK_FMT_E {
	MXW_HYDWA_MPEG_ACTIVE_WOW = 0,
	MXW_HYDWA_MPEG_ACTIVE_HIGH,

	MXW_HYDWA_MPEG_CWK_NEGATIVE = 0,
	MXW_HYDWA_MPEG_CWK_POSITIVE,

	MXW_HYDWA_MPEG_CWK_IN_PHASE = 0,
	MXW_HYDWA_MPEG_CWK_INVEWTED,
};

enum MXW_HYDWA_MPEG_CWK_PHASE_E {
	MXW_HYDWA_MPEG_CWK_PHASE_SHIFT_0_DEG = 0,
	MXW_HYDWA_MPEG_CWK_PHASE_SHIFT_90_DEG,
	MXW_HYDWA_MPEG_CWK_PHASE_SHIFT_180_DEG,
	MXW_HYDWA_MPEG_CWK_PHASE_SHIFT_270_DEG
};

enum MXW_HYDWA_MPEG_EWW_INDICATION_E {
	MXW_HYDWA_MPEG_EWW_WEPWACE_SYNC = 0,
	MXW_HYDWA_MPEG_EWW_WEPWACE_VAWID,
	MXW_HYDWA_MPEG_EWW_INDICATION_DISABWED
};

stwuct MXW_HYDWA_MPEGOUT_PAWAM_T {
	int                                  enabwe;               /* Enabwe ow Disabwe MPEG OUT */
	enum MXW_HYDWA_MPEG_CWK_TYPE_E       mpeg_cwk_type;          /* Continuous ow gapped */
	enum MXW_HYDWA_MPEG_CWK_FMT_E        mpeg_cwk_pow;           /* MPEG Cwk powawity */
	u8                                   max_mpeg_cwk_wate;       /* Max MPEG Cwk wate (0 - 104 MHz, 139 MHz) */
	enum MXW_HYDWA_MPEG_CWK_PHASE_E      mpeg_cwk_phase;         /* MPEG Cwk phase */
	enum MXW_HYDWA_MPEG_DATA_FMT_E       wsb_ow_msb_fiwst;        /* WSB fiwst ow MSB fiwst in TS twansmission */
	enum MXW_HYDWA_MPEG_DATA_FMT_E       mpeg_sync_puwse_width;   /* MPEG SYNC puwse width (1-bit ow 1-byte) */
	enum MXW_HYDWA_MPEG_CWK_FMT_E        mpeg_vawid_pow;         /* MPEG VAWID powawity */
	enum MXW_HYDWA_MPEG_CWK_FMT_E        mpeg_sync_pow;          /* MPEG SYNC powawity */
	enum MXW_HYDWA_MPEG_MODE_E           mpeg_mode;             /* config 4/3/2-wiwe sewiaw ow pawawwew TS out */
	enum MXW_HYDWA_MPEG_EWW_INDICATION_E mpeg_ewwow_indication;  /* Enabwe ow Disabwe MPEG ewwow indication */
};

enum MXW_HYDWA_EXT_TS_IN_ID_E {
	MXW_HYDWA_EXT_TS_IN_0 = 0,
	MXW_HYDWA_EXT_TS_IN_1,
	MXW_HYDWA_EXT_TS_IN_2,
	MXW_HYDWA_EXT_TS_IN_3,
	MXW_HYDWA_EXT_TS_IN_MAX
};

enum MXW_HYDWA_TS_OUT_ID_E {
	MXW_HYDWA_TS_OUT_0 = 0,
	MXW_HYDWA_TS_OUT_1,
	MXW_HYDWA_TS_OUT_2,
	MXW_HYDWA_TS_OUT_3,
	MXW_HYDWA_TS_OUT_4,
	MXW_HYDWA_TS_OUT_5,
	MXW_HYDWA_TS_OUT_6,
	MXW_HYDWA_TS_OUT_7,
	MXW_HYDWA_TS_OUT_MAX
};

enum MXW_HYDWA_TS_DWIVE_STWENGTH_E {
	MXW_HYDWA_TS_DWIVE_STWENGTH_1X = 0,
	MXW_HYDWA_TS_DWIVE_STWENGTH_2X,
	MXW_HYDWA_TS_DWIVE_STWENGTH_3X,
	MXW_HYDWA_TS_DWIVE_STWENGTH_4X,
	MXW_HYDWA_TS_DWIVE_STWENGTH_5X,
	MXW_HYDWA_TS_DWIVE_STWENGTH_6X,
	MXW_HYDWA_TS_DWIVE_STWENGTH_7X,
	MXW_HYDWA_TS_DWIVE_STWENGTH_8X
};

enum MXW_HYDWA_DEVICE_E {
	MXW_HYDWA_DEVICE_581 = 0,
	MXW_HYDWA_DEVICE_584,
	MXW_HYDWA_DEVICE_585,
	MXW_HYDWA_DEVICE_544,
	MXW_HYDWA_DEVICE_561,
	MXW_HYDWA_DEVICE_TEST,
	MXW_HYDWA_DEVICE_582,
	MXW_HYDWA_DEVICE_541,
	MXW_HYDWA_DEVICE_568,
	MXW_HYDWA_DEVICE_542,
	MXW_HYDWA_DEVICE_541S,
	MXW_HYDWA_DEVICE_561S,
	MXW_HYDWA_DEVICE_581S,
	MXW_HYDWA_DEVICE_MAX
};

/* Demod IQ data */
stwuct MXW_HYDWA_DEMOD_IQ_SWC_T {
	u32 demod_id;
	u32 souwce_of_iq; /* == 0, it means I/Q comes fwom Fowmattew
			 * == 1, Wegacy FEC
			 * == 2, Fwequency Wecovewy
			 * == 3, NBC
			 * == 4, CTW
			 * == 5, EQ
			 * == 6, FPGA
			 */
};

stwuct MXW_HYDWA_DEMOD_ABOWT_TUNE_T {
	u32 demod_id;
};

stwuct MXW_HYDWA_TUNEW_CMD {
	u8 tunew_id;
	u8 enabwe;
};

/* Demod Pawa fow Channew Tune */
stwuct MXW_HYDWA_DEMOD_PAWAM_T {
	u32 tunew_index;
	u32 demod_index;
	u32 fwequency_in_hz;     /* Fwequency */
	u32 standawd;          /* one of MXW_HYDWA_BCAST_STD_E */
	u32 spectwum_invewsion; /* Input : Spectwum invewsion. */
	u32 woww_off;           /* wowwOff (awpha) factow */
	u32 symbow_wate_in_hz;    /* Symbow wate */
	u32 piwots;            /* TWUE = piwots enabwed */
	u32 moduwation_scheme;  /* Input : Moduwation Scheme is one of MXW_HYDWA_MODUWATION_E */
	u32 fec_code_wate;       /* Input : Fowwawd ewwow cowwection wate. Is one of MXW_HYDWA_FEC_E */
	u32 max_cawwiew_offset_in_mhz; /* Maximum cawwiew fweq offset in MHz. Same as fweqSeawchWangeKHz, but in unit of MHz. */
};

stwuct MXW_HYDWA_DEMOD_SCWAMBWE_CODE_T {
	u32 demod_index;
	u8 scwambwe_sequence[12]; /* scwambwe sequence */
	u32 scwambwe_code; /* scwambwe gowd code */
};

stwuct MXW_INTW_CFG_T {
	u32 intw_type;
	u32 intw_duwation_in_nano_secs;
	u32 intw_mask;
};

stwuct MXW_HYDWA_POWEW_MODE_CMD {
	u8 powew_mode; /* enumewation vawues awe defined in MXW_HYDWA_PWW_MODE_E (device API.h) */
};

stwuct MXW_HYDWA_WF_WAKEUP_PAWAM_T {
	u32 time_intewvaw_in_seconds; /* in seconds */
	u32 tunew_index;
	s32 wssi_thweshowd;
};

stwuct MXW_HYDWA_WF_WAKEUP_CFG_T {
	u32 tunew_count;
	stwuct MXW_HYDWA_WF_WAKEUP_PAWAM_T pawams;
};

enum MXW_HYDWA_AUX_CTWW_MODE_E {
	MXW_HYDWA_AUX_CTWW_MODE_FSK = 0, /* Sewect FSK contwowwew */
	MXW_HYDWA_AUX_CTWW_MODE_DISEQC,  /* Sewect DiSEqC contwowwew */
};

enum MXW_HYDWA_DISEQC_OPMODE_E {
	MXW_HYDWA_DISEQC_ENVEWOPE_MODE = 0,
	MXW_HYDWA_DISEQC_TONE_MODE,
};

enum MXW_HYDWA_DISEQC_VEW_E {
	MXW_HYDWA_DISEQC_1_X = 0, /* Config DiSEqC 1.x mode */
	MXW_HYDWA_DISEQC_2_X, /* Config DiSEqC 2.x mode */
	MXW_HYDWA_DISEQC_DISABWE /* Disabwe DiSEqC */
};

enum MXW_HYDWA_DISEQC_CAWWIEW_FWEQ_E {
	MXW_HYDWA_DISEQC_CAWWIEW_FWEQ_22KHZ = 0, /* DiSEqC signaw fwequency of 22 KHz */
	MXW_HYDWA_DISEQC_CAWWIEW_FWEQ_33KHZ,     /* DiSEqC signaw fwequency of 33 KHz */
	MXW_HYDWA_DISEQC_CAWWIEW_FWEQ_44KHZ      /* DiSEqC signaw fwequency of 44 KHz */
};

enum MXW_HYDWA_DISEQC_ID_E {
	MXW_HYDWA_DISEQC_ID_0 = 0,
	MXW_HYDWA_DISEQC_ID_1,
	MXW_HYDWA_DISEQC_ID_2,
	MXW_HYDWA_DISEQC_ID_3
};

enum MXW_HYDWA_FSK_OP_MODE_E {
	MXW_HYDWA_FSK_CFG_TYPE_39KPBS = 0, /* 39.0kbps */
	MXW_HYDWA_FSK_CFG_TYPE_39_017KPBS, /* 39.017kbps */
	MXW_HYDWA_FSK_CFG_TYPE_115_2KPBS   /* 115.2kbps */
};

stwuct MXW58X_DSQ_OP_MODE_T {
	u32 diseqc_id; /* DSQ 0, 1, 2 ow 3 */
	u32 op_mode; /* Envewope mode (0) ow intewnaw tone mode (1) */
	u32 vewsion; /* 0: 1.0, 1: 1.1, 2: Disabwe */
	u32 centew_fweq; /* 0: 22KHz, 1: 33KHz and 2: 44 KHz */
};

stwuct MXW_HYDWA_DISEQC_CFG_CONT_TONE_T {
	u32 diseqc_id;
	u32 cont_tone_fwag; /* 1: Enabwe , 0: Disabwe */
};
