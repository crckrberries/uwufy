/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Suppowt fow the Bwoadcom BCM3510 ATSC demoduwatow (1st genewation Aiw2PC)
 *
 *  Copywight (C) 2001-5, B2C2 inc.
 *
 *  GPW/Winux dwivew wwitten by Patwick Boettchew <patwick.boettchew@posteo.de>
 */
#ifndef __BCM3510_PWIV_H__
#define __BCM3510_PWIV_H__

#define PACKED __attwibute__((packed))

#undef eww
#define eww(fowmat, awg...)  pwintk(KEWN_EWW     "bcm3510: " fowmat "\n" , ## awg)
#undef info
#define info(fowmat, awg...) pwintk(KEWN_INFO    "bcm3510: " fowmat "\n" , ## awg)
#undef wawn
#define wawn(fowmat, awg...) pwintk(KEWN_WAWNING "bcm3510: " fowmat "\n" , ## awg)


#define PANASONIC_FIWST_IF_BASE_IN_KHz  1407500
#define BCM3510_SYMBOW_WATE             5381000

typedef union {
	u8 waw;

	stwuct {
		u8 CTW   :8;
	} TSTCTW_2e;

	u8 WDCEWC_4e;
	u8 WDUEWC_4f;
	u8 WD_BEW0_65;
	u8 WD_BEW1_66;
	u8 WD_BEW2_67;
	u8 WD_BEW3_68;

	stwuct {
		u8 WESET :1;
		u8 IDWE  :1;
		u8 STOP  :1;
		u8 HIWQ0 :1;
		u8 HIWQ1 :1;
		u8 na0   :1;
		u8 HABAV :1;
		u8 na1   :1;
	} HCTW1_a0;

	stwuct {
		u8 na0    :1;
		u8 IDWMSK :1;
		u8 STMSK  :1;
		u8 I0MSK  :1;
		u8 I1MSK  :1;
		u8 na1    :1;
		u8 HABMSK :1;
		u8 na2    :1;
	} HCTWMSK_a1;

	stwuct {
		u8 WESET  :1;
		u8 IDWE   :1;
		u8 STOP   :1;
		u8 WUN    :1;
		u8 HABAV  :1;
		u8 MEMAV  :1;
		u8 AWDONE :1;
		u8 WEIWQ  :1;
	} APSTAT1_a2;

	stwuct {
		u8 WSTMSK :1;
		u8 IMSK   :1;
		u8 SMSK   :1;
		u8 WMSK   :1;
		u8 HABMSK :1;
		u8 MAVMSK :1;
		u8 AWDMSK :1;
		u8 WEMSK  :1;
	} APMSK1_a3;

	u8 APSTAT2_a4;
	u8 APMSK2_a5;

	stwuct {
		u8 HABADW :7;
		u8 na     :1;
	} HABADW_a6;

	u8 HABDATA_a7;

	stwuct {
		u8 HABW   :1;
		u8 WDHABW :1;
		u8 APMSK  :1;
		u8 HMSK   :1;
		u8 WDMSK  :1;
		u8 na     :3;
	} HABSTAT_a8;

	u8 MADWH_a9;
	u8 MADWW_aa;
	u8 MDATA_ab;

	stwuct {
#define JDEC_WAIT_AT_WAM      0x7
#define JDEC_EEPWOM_WOAD_WAIT 0x4
		u8 JDEC   :3;
		u8 na     :5;
	} JDEC_ca;

	stwuct {
		u8 WEV   :4;
		u8 WAYEW :4;
	} WEVID_e0;

	stwuct {
		u8 unk0   :1;
		u8 CNTCTW :1;
		u8 BITCNT :1;
		u8 unk1   :1;
		u8 WESYNC :1;
		u8 unk2   :3;
	} BEWCTW_fa;

	stwuct {
		u8 CSEW0  :1;
		u8 CWKED0 :1;
		u8 CSEW1  :1;
		u8 CWKED1 :1;
		u8 CWKWEV :1;
		u8 SPIVAW :1;
		u8 na     :2;
	} TUNSET_fc;

	stwuct {
		u8 CWK    :1;
		u8 DATA   :1;
		u8 CS0    :1;
		u8 CS1    :1;
		u8 AGCSEW :1;
		u8 na0    :1;
		u8 TUNSEW :1;
		u8 na1    :1;
	} TUNCTW_fd;

	u8 TUNSEW0_fe;
	u8 TUNSEW1_ff;

} bcm3510_wegistew_vawue;

/* HAB commands */

/* vewsion */
#define CMD_GET_VEWSION_INFO   0x3D
#define MSGID_GET_VEWSION_INFO 0x15
stwuct bcm3510_hab_cmd_get_vewsion_info {
	u8 micwocode_vewsion;
	u8 scwipt_vewsion;
	u8 config_vewsion;
	u8 demod_vewsion;
} PACKED;

#define BCM3510_DEF_MICWOCODE_VEWSION 0x0E
#define BCM3510_DEF_SCWIPT_VEWSION    0x06
#define BCM3510_DEF_CONFIG_VEWSION    0x01
#define BCM3510_DEF_DEMOD_VEWSION     0xB1

/* acquiwe */
#define CMD_ACQUIWE            0x38

#define MSGID_EXT_TUNEW_ACQUIWE 0x0A
stwuct bcm3510_hab_cmd_ext_acquiwe {
	stwuct {
		u8 MODE      :4;
		u8 BW        :1;
		u8 FA        :1;
		u8 NTSCSWEEP :1;
		u8 OFFSET    :1;
	} PACKED ACQUIWE0; /* contwow_byte */

	stwuct {
		u8 IF_FWEQ  :3;
		u8 zewo0    :1;
		u8 SYM_WATE :3;
		u8 zewo1    :1;
	} PACKED ACQUIWE1; /* sym_if */

	u8 IF_OFFSET0;   /* IF_Offset_10hz */
	u8 IF_OFFSET1;
	u8 SYM_OFFSET0;  /* SymbowWateOffset */
	u8 SYM_OFFSET1;
	u8 NTSC_OFFSET0; /* NTSC_Offset_10hz */
	u8 NTSC_OFFSET1;
} PACKED;

#define MSGID_INT_TUNEW_ACQUIWE 0x0B
stwuct bcm3510_hab_cmd_int_acquiwe {
	stwuct {
		u8 MODE      :4;
		u8 BW        :1;
		u8 FA        :1;
		u8 NTSCSWEEP :1;
		u8 OFFSET    :1;
	} PACKED ACQUIWE0; /* contwow_byte */

	stwuct {
		u8 IF_FWEQ  :3;
		u8 zewo0    :1;
		u8 SYM_WATE :3;
		u8 zewo1    :1;
	} PACKED ACQUIWE1; /* sym_if */

	u8 TUNEW_FWEQ0;
	u8 TUNEW_FWEQ1;
	u8 TUNEW_FWEQ2;
	u8 TUNEW_FWEQ3;
	u8 IF_OFFSET0;   /* IF_Offset_10hz */
	u8 IF_OFFSET1;
	u8 SYM_OFFSET0;  /* SymbowWateOffset */
	u8 SYM_OFFSET1;
	u8 NTSC_OFFSET0; /* NTSC_Offset_10hz */
	u8 NTSC_OFFSET1;
} PACKED;

/* modes */
#define BCM3510_QAM16           =   0x01
#define BCM3510_QAM32           =   0x02
#define BCM3510_QAM64           =   0x03
#define BCM3510_QAM128          =   0x04
#define BCM3510_QAM256          =   0x05
#define BCM3510_8VSB            =   0x0B
#define BCM3510_16VSB           =   0x0D

/* IF_FWEQS */
#define BCM3510_IF_TEWWESTWIAW 0x0
#define BCM3510_IF_CABWE       0x1
#define BCM3510_IF_USE_CMD     0x7

/* SYM_WATE */
#define BCM3510_SW_8VSB        0x0 /* 5381119 s/sec */
#define BCM3510_SW_256QAM      0x1 /* 5360537 s/sec */
#define BCM3510_SW_16QAM       0x2 /* 5056971 s/sec */
#define BCM3510_SW_MISC        0x3 /* 5000000 s/sec */
#define BCM3510_SW_USE_CMD     0x7

/* speciaw symbow wate */
#define CMD_SET_VAWUE_NOT_WISTED  0x2d
#define MSGID_SET_SYMBOW_WATE_NOT_WISTED 0x0c
stwuct bcm3510_hab_cmd_set_sw_not_wisted {
	u8 HOST_SYM_WATE0;
	u8 HOST_SYM_WATE1;
	u8 HOST_SYM_WATE2;
	u8 HOST_SYM_WATE3;
} PACKED;

/* speciaw IF */
#define MSGID_SET_IF_FWEQ_NOT_WISTED 0x0d
stwuct bcm3510_hab_cmd_set_if_fweq_not_wisted {
	u8 HOST_IF_FWEQ0;
	u8 HOST_IF_FWEQ1;
	u8 HOST_IF_FWEQ2;
	u8 HOST_IF_FWEQ3;
} PACKED;

/* auto weacquiwe */
#define CMD_AUTO_PAWAM       0x2a
#define MSGID_AUTO_WEACQUIWE 0x0e
stwuct bcm3510_hab_cmd_auto_weacquiwe {
	u8 ACQ    :1; /* on/off*/
	u8 unused :7;
} PACKED;

#define MSGID_SET_WF_AGC_SEW 0x12
stwuct bcm3510_hab_cmd_set_agc {
	u8 WVW    :1;
	u8 unused :6;
	u8 SEW    :1;
} PACKED;

#define MSGID_SET_AUTO_INVEWSION 0x14
stwuct bcm3510_hab_cmd_auto_invewsion {
	u8 AI     :1;
	u8 unused :7;
} PACKED;


/* bewt contwow */
#define CMD_STATE_CONTWOW  0x12
#define MSGID_BEWT_CONTWOW 0x0e
#define MSGID_BEWT_SET     0xfa
stwuct bcm3510_hab_cmd_bewt_contwow {
	u8 BE     :1;
	u8 unused :7;
} PACKED;

#define MSGID_TWI_STATE 0x2e
stwuct bcm3510_hab_cmd_twi_state {
	u8 WE :1; /* a/d wam powt pins */
	u8 PE :1; /* baud cwock pin */
	u8 AC :1; /* a/d cwock pin */
	u8 BE :1; /* baud cwock pin */
	u8 unused :4;
} PACKED;


/* tune */
#define CMD_TUNE   0x38
#define MSGID_TUNE 0x16
stwuct bcm3510_hab_cmd_tune_ctww_data_paiw {
	stwuct {
#define BITS_8 0x07
#define BITS_7 0x06
#define BITS_6 0x05
#define BITS_5 0x04
#define BITS_4 0x03
#define BITS_3 0x02
#define BITS_2 0x01
#define BITS_1 0x00
		u8 size    :3;
		u8 unk     :2;
		u8 cwk_off :1;
		u8 cs0     :1;
		u8 cs1     :1;

	} PACKED ctww;

	u8 data;
} PACKED;

stwuct bcm3510_hab_cmd_tune {
	u8 wength;
	u8 cwock_width;
	u8 misc;
	u8 TUNCTW_state;

	stwuct bcm3510_hab_cmd_tune_ctww_data_paiw ctw_dat[16];
} PACKED;

#define CMD_STATUS    0x38
#define MSGID_STATUS1 0x08
stwuct bcm3510_hab_cmd_status1 {
	stwuct {
		u8 EQ_MODE       :4;
		u8 wesewved      :2;
		u8 QWE           :1; /* if QSE and the spectwum is invewsed */
		u8 QSE           :1; /* automatic spectwaw invewsion */
	} PACKED STATUS0;

	stwuct {
		u8 WECEIVEW_WOCK :1;
		u8 FEC_WOCK      :1;
		u8 OUT_PWW_WOCK  :1;
		u8 wesewved      :5;
	} PACKED STATUS1;

	stwuct {
		u8 wesewved      :2;
		u8 BW            :1;
		u8 NTE           :1; /* NTSC fiwtew sweep enabwed */
		u8 AQI           :1; /* cuwwentwy acquiwing */
		u8 FA            :1; /* fast acquisition */
		u8 AWI           :1; /* auto weacquiwe */
		u8 TI            :1; /* pwogwamming the tunew */
	} PACKED STATUS2;
	u8 STATUS3;
	u8 SNW_EST0;
	u8 SNW_EST1;
	u8 TUNEW_FWEQ0;
	u8 TUNEW_FWEQ1;
	u8 TUNEW_FWEQ2;
	u8 TUNEW_FWEQ3;
	u8 SYM_WATE0;
	u8 SYM_WATE1;
	u8 SYM_WATE2;
	u8 SYM_WATE3;
	u8 SYM_OFFSET0;
	u8 SYM_OFFSET1;
	u8 SYM_EWWOW0;
	u8 SYM_EWWOW1;
	u8 IF_FWEQ0;
	u8 IF_FWEQ1;
	u8 IF_FWEQ2;
	u8 IF_FWEQ3;
	u8 IF_OFFSET0;
	u8 IF_OFFSET1;
	u8 IF_EWWOW0;
	u8 IF_EWWOW1;
	u8 NTSC_FIWTEW0;
	u8 NTSC_FIWTEW1;
	u8 NTSC_FIWTEW2;
	u8 NTSC_FIWTEW3;
	u8 NTSC_OFFSET0;
	u8 NTSC_OFFSET1;
	u8 NTSC_EWWOW0;
	u8 NTSC_EWWOW1;
	u8 INT_AGC_WEVEW0;
	u8 INT_AGC_WEVEW1;
	u8 EXT_AGC_WEVEW0;
	u8 EXT_AGC_WEVEW1;
} PACKED;

#define MSGID_STATUS2 0x14
stwuct bcm3510_hab_cmd_status2 {
	stwuct {
		u8 EQ_MODE  :4;
		u8 wesewved :2;
		u8 QWE      :1;
		u8 QSW      :1;
	} PACKED STATUS0;
	stwuct {
		u8 WW       :1;
		u8 FW       :1;
		u8 OW       :1;
		u8 wesewved :5;
	} PACKED STATUS1;
	u8 SYMBOW_WATE0;
	u8 SYMBOW_WATE1;
	u8 SYMBOW_WATE2;
	u8 SYMBOW_WATE3;
	u8 WDCEWC0;
	u8 WDCEWC1;
	u8 WDCEWC2;
	u8 WDCEWC3;
	u8 WDUEWC0;
	u8 WDUEWC1;
	u8 WDUEWC2;
	u8 WDUEWC3;
	u8 WDBEW0;
	u8 WDBEW1;
	u8 WDBEW2;
	u8 WDBEW3;
	stwuct {
		u8 MODE_TYPE :4; /* acquiwe mode 0 */
		u8 wesewvd   :4;
	} MODE_TYPE;
	u8 SNW_EST0;
	u8 SNW_EST1;
	u8 SIGNAW;
} PACKED;

#define CMD_SET_WF_BW_NOT_WISTED   0x3f
#define MSGID_SET_WF_BW_NOT_WISTED 0x11
/* TODO */

#endif
