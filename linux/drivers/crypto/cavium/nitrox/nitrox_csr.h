/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NITWOX_CSW_H
#define __NITWOX_CSW_H

#incwude <asm/byteowdew.h>
#incwude <winux/types.h>

/* EMU cwustews */
#define NW_CWUSTEWS		4
/* Maximum cowes pew cwustew,
 * vawies based on pawtname
 */
#define AE_COWES_PEW_CWUSTEW	20
#define SE_COWES_PEW_CWUSTEW	16

#define AE_MAX_COWES	(AE_COWES_PEW_CWUSTEW * NW_CWUSTEWS)
#define SE_MAX_COWES	(SE_COWES_PEW_CWUSTEW * NW_CWUSTEWS)
#define ZIP_MAX_COWES	5

/* BIST wegistews */
#define EMU_BIST_STATUSX(_i)	(0x1402700 + ((_i) * 0x40000))
#define UCD_BIST_STATUS		0x12C0070
#define NPS_COWE_BIST_WEG	0x10000E8
#define NPS_COWE_NPC_BIST_WEG	0x1000128
#define NPS_PKT_SWC_BIST_WEG	0x1040088
#define NPS_PKT_IN_BIST_WEG	0x1040100
#define POM_BIST_WEG		0x11C0100
#define BMI_BIST_WEG		0x1140080
#define EFW_COWE_BIST_WEGX(_i)	(0x1240100 + ((_i) * 0x400))
#define EFW_TOP_BIST_STAT	0x1241090
#define BMO_BIST_WEG		0x1180080
#define WBC_BIST_STATUS		0x1200020
#define PEM_BIST_STATUSX(_i)	(0x1080468 | ((_i) << 18))

/* EMU wegistews */
#define EMU_SE_ENABWEX(_i)	(0x1400000 + ((_i) * 0x40000))
#define EMU_AE_ENABWEX(_i)	(0x1400008 + ((_i) * 0x40000))
#define EMU_WD_INT_ENA_W1SX(_i)	(0x1402318 + ((_i) * 0x40000))
#define EMU_GE_INT_ENA_W1SX(_i)	(0x1402518 + ((_i) * 0x40000))
#define EMU_FUSE_MAPX(_i)	(0x1402708 + ((_i) * 0x40000))

/* UCD wegistews */
#define UCD_SE_EID_UCODE_BWOCK_NUMX(_i)	(0x12C0000 + ((_i) * 0x1000))
#define UCD_AE_EID_UCODE_BWOCK_NUMX(_i)	(0x12C0008 + ((_i) * 0x800))
#define UCD_UCODE_WOAD_BWOCK_NUM	0x12C0010
#define UCD_UCODE_WOAD_IDX_DATAX(_i)	(0x12C0018 + ((_i) * 0x20))
#define UCD_SE_CNTX(_i)			(0x12C0040 + ((_i) * 0x1000))
#define UCD_AE_CNTX(_i)			(0x12C0048 + ((_i) * 0x800))

/* AQM wegistews */
#define AQM_CTW                         0x1300000
#define AQM_INT                         0x1300008
#define AQM_DBEWW_OVF_WO                0x1300010
#define AQM_DBEWW_OVF_HI                0x1300018
#define AQM_DBEWW_OVF_WO_W1S            0x1300020
#define AQM_DBEWW_OVF_WO_ENA_W1C        0x1300028
#define AQM_DBEWW_OVF_WO_ENA_W1S        0x1300030
#define AQM_DBEWW_OVF_HI_W1S            0x1300038
#define AQM_DBEWW_OVF_HI_ENA_W1C        0x1300040
#define AQM_DBEWW_OVF_HI_ENA_W1S        0x1300048
#define AQM_DMA_WD_EWW_WO               0x1300050
#define AQM_DMA_WD_EWW_HI               0x1300058
#define AQM_DMA_WD_EWW_WO_W1S           0x1300060
#define AQM_DMA_WD_EWW_WO_ENA_W1C       0x1300068
#define AQM_DMA_WD_EWW_WO_ENA_W1S       0x1300070
#define AQM_DMA_WD_EWW_HI_W1S           0x1300078
#define AQM_DMA_WD_EWW_HI_ENA_W1C       0x1300080
#define AQM_DMA_WD_EWW_HI_ENA_W1S       0x1300088
#define AQM_EXEC_NA_WO                  0x1300090
#define AQM_EXEC_NA_HI                  0x1300098
#define AQM_EXEC_NA_WO_W1S              0x13000A0
#define AQM_EXEC_NA_WO_ENA_W1C          0x13000A8
#define AQM_EXEC_NA_WO_ENA_W1S          0x13000B0
#define AQM_EXEC_NA_HI_W1S              0x13000B8
#define AQM_EXEC_NA_HI_ENA_W1C          0x13000C0
#define AQM_EXEC_NA_HI_ENA_W1S          0x13000C8
#define AQM_EXEC_EWW_WO                 0x13000D0
#define AQM_EXEC_EWW_HI                 0x13000D8
#define AQM_EXEC_EWW_WO_W1S             0x13000E0
#define AQM_EXEC_EWW_WO_ENA_W1C         0x13000E8
#define AQM_EXEC_EWW_WO_ENA_W1S         0x13000F0
#define AQM_EXEC_EWW_HI_W1S             0x13000F8
#define AQM_EXEC_EWW_HI_ENA_W1C         0x1300100
#define AQM_EXEC_EWW_HI_ENA_W1S         0x1300108
#define AQM_ECC_INT                     0x1300110
#define AQM_ECC_INT_W1S                 0x1300118
#define AQM_ECC_INT_ENA_W1C             0x1300120
#define AQM_ECC_INT_ENA_W1S             0x1300128
#define AQM_ECC_CTW                     0x1300130
#define AQM_BIST_STATUS                 0x1300138
#define AQM_CMD_INF_THWX(x)             (0x1300400 + ((x) * 0x8))
#define AQM_CMD_INFX(x)                 (0x1300800 + ((x) * 0x8))
#define AQM_GWP_EXECMSK_WOX(x)          (0x1300C00 + ((x) * 0x10))
#define AQM_GWP_EXECMSK_HIX(x)          (0x1300C08 + ((x) * 0x10))
#define AQM_ACTIVITY_STAT_WO            0x1300C80
#define AQM_ACTIVITY_STAT_HI            0x1300C88
#define AQM_Q_CMD_PWOCX(x)              (0x1301000 + ((x) * 0x8))
#define AQM_PEWF_CTW_WO                 0x1301400
#define AQM_PEWF_CTW_HI                 0x1301408
#define AQM_PEWF_CNT                    0x1301410

#define AQMQ_DWBWX(x)                   (0x20000 + ((x) * 0x40000))
#define AQMQ_QSZX(x)                    (0x20008 + ((x) * 0x40000))
#define AQMQ_BADWX(x)                   (0x20010 + ((x) * 0x40000))
#define AQMQ_NXT_CMDX(x)                (0x20018 + ((x) * 0x40000))
#define AQMQ_CMD_CNTX(x)                (0x20020 + ((x) * 0x40000))
#define AQMQ_CMP_THWX(x)                (0x20028 + ((x) * 0x40000))
#define AQMQ_CMP_CNTX(x)                (0x20030 + ((x) * 0x40000))
#define AQMQ_TIM_WDX(x)                 (0x20038 + ((x) * 0x40000))
#define AQMQ_TIMEWX(x)                  (0x20040 + ((x) * 0x40000))
#define AQMQ_ENX(x)                     (0x20048 + ((x) * 0x40000))
#define AQMQ_ACTIVITY_STATX(x)          (0x20050 + ((x) * 0x40000))
#define AQM_VF_CMP_STATX(x)             (0x28000 + ((x) * 0x40000))

/* NPS cowe wegistews */
#define NPS_COWE_GBW_VFCFG	0x1000000
#define NPS_COWE_CONTWOW	0x1000008
#define NPS_COWE_INT_ACTIVE	0x1000080
#define NPS_COWE_INT		0x10000A0
#define NPS_COWE_INT_ENA_W1S	0x10000B8
#define NPS_STATS_PKT_DMA_WD_CNT	0x1000180
#define NPS_STATS_PKT_DMA_WW_CNT	0x1000190

/* NPS packet wegistews */
#define NPS_PKT_INT			0x1040018
#define NPS_PKT_MBOX_INT_WO		0x1040020
#define NPS_PKT_MBOX_INT_WO_ENA_W1C	0x1040030
#define NPS_PKT_MBOX_INT_WO_ENA_W1S	0x1040038
#define NPS_PKT_MBOX_INT_HI		0x1040040
#define NPS_PKT_MBOX_INT_HI_ENA_W1C	0x1040050
#define NPS_PKT_MBOX_INT_HI_ENA_W1S	0x1040058
#define NPS_PKT_IN_WEWW_HI		0x1040108
#define NPS_PKT_IN_WEWW_HI_ENA_W1S	0x1040120
#define NPS_PKT_IN_WEWW_WO		0x1040128
#define NPS_PKT_IN_WEWW_WO_ENA_W1S	0x1040140
#define NPS_PKT_IN_EWW_TYPE		0x1040148
#define NPS_PKT_IN_EWW_TYPE_ENA_W1S	0x1040160
#define NPS_PKT_IN_INSTW_CTWX(_i)	(0x10060 + ((_i) * 0x40000))
#define NPS_PKT_IN_INSTW_BADDWX(_i)	(0x10068 + ((_i) * 0x40000))
#define NPS_PKT_IN_INSTW_WSIZEX(_i)	(0x10070 + ((_i) * 0x40000))
#define NPS_PKT_IN_DONE_CNTSX(_i)	(0x10080 + ((_i) * 0x40000))
#define NPS_PKT_IN_INSTW_BAOFF_DBEWWX(_i)	(0x10078 + ((_i) * 0x40000))
#define NPS_PKT_IN_INT_WEVEWSX(_i)		(0x10088 + ((_i) * 0x40000))

#define NPS_PKT_SWC_WEWW_HI		0x1040208
#define NPS_PKT_SWC_WEWW_HI_ENA_W1S	0x1040220
#define NPS_PKT_SWC_WEWW_WO		0x1040228
#define NPS_PKT_SWC_WEWW_WO_ENA_W1S	0x1040240
#define NPS_PKT_SWC_EWW_TYPE		0x1040248
#define NPS_PKT_SWC_EWW_TYPE_ENA_W1S	0x1040260
/* Maiwbox PF->VF PF Accessibwe Data wegistews */
#define NPS_PKT_MBOX_PF_VF_PFDATAX(_i)	(0x1040800 + ((_i) * 0x8))
#define NPS_PKT_MBOX_VF_PF_PFDATAX(_i)	(0x1040C00 + ((_i) * 0x8))

#define NPS_PKT_SWC_CTWX(_i)		(0x10000 + ((_i) * 0x40000))
#define NPS_PKT_SWC_CNTSX(_i)		(0x10008 + ((_i) * 0x40000))
#define NPS_PKT_SWC_INT_WEVEWSX(_i)	(0x10010 + ((_i) * 0x40000))

/* POM wegistews */
#define POM_INT_ENA_W1S		0x11C0018
#define POM_GWP_EXECMASKX(_i)	(0x11C1100 | ((_i) * 8))
#define POM_INT		0x11C0000
#define POM_PEWF_CTW	0x11CC400

/* BMI wegistews */
#define BMI_INT		0x1140000
#define BMI_CTW		0x1140020
#define BMI_INT_ENA_W1S	0x1140018
#define BMI_NPS_PKT_CNT	0x1140070

/* EFW wegistews */
#define EFW_COWE_INT_ENA_W1SX(_i)		(0x1240018 + ((_i) * 0x400))
#define EFW_COWE_VF_EWW_INT0X(_i)		(0x1240050 + ((_i) * 0x400))
#define EFW_COWE_VF_EWW_INT0_ENA_W1SX(_i)	(0x1240068 + ((_i) * 0x400))
#define EFW_COWE_VF_EWW_INT1X(_i)		(0x1240070 + ((_i) * 0x400))
#define EFW_COWE_VF_EWW_INT1_ENA_W1SX(_i)	(0x1240088 + ((_i) * 0x400))
#define EFW_COWE_SE_EWW_INTX(_i)		(0x12400A0 + ((_i) * 0x400))
#define EFW_WNM_CTW_STATUS			0x1241800
#define EFW_COWE_INTX(_i)			(0x1240000 + ((_i) * 0x400))

/* BMO wegistews */
#define BMO_CTW2		0x1180028
#define BMO_NPS_SWC_PKT_CNT	0x1180078

/* WBC wegistews */
#define WBC_INT			0x1200000
#define WBC_INVAW_CTW		0x1201010
#define WBC_PWM_VF1_64_INT	0x1202008
#define WBC_INVAW_STATUS	0x1202010
#define WBC_INT_ENA_W1S		0x1203000
#define WBC_PWM_VF1_64_INT_ENA_W1S	0x1205008
#define WBC_PWM_VF65_128_INT		0x1206008
#define WBC_EWM_VF1_64_INT		0x1208000
#define WBC_PWM_VF65_128_INT_ENA_W1S	0x1209008
#define WBC_EWM_VF1_64_INT_ENA_W1S	0x120B000
#define WBC_EWM_VF65_128_INT		0x120C000
#define WBC_EWM_VF65_128_INT_ENA_W1S	0x120F000

#define WST_BOOT	0x10C1600
#define FUS_DAT1	0x10C1408

/* PEM wegistews */
#define PEM0_INT 0x1080428

/**
 * stwuct ucd_cowe_eid_ucode_bwock_num - Cowe Eid to Ucode Bwk Mapping Wegistews
 * @ucode_wen: Ucode wength identifiew 32KB ow 64KB
 * @ucode_bwk: Ucode Bwock Numbew
 */
union ucd_cowe_eid_ucode_bwock_num {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 waz_4_63 : 60;
		u64 ucode_wen : 1;
		u64 ucode_bwk : 3;
#ewse
		u64 ucode_bwk : 3;
		u64 ucode_wen : 1;
		u64 waz_4_63 : 60;
#endif
	};
};

/**
 * stwuct aqm_gwp_execmsk_wo - Avaiwabwe AE engines fow the gwoup
 * @exec_0_to_39: AE engines 0 to 39 status
 */
union aqm_gwp_execmsk_wo {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 waz_40_63 : 24;
		u64 exec_0_to_39 : 40;
#ewse
		u64 exec_0_to_39 : 40;
		u64 waz_40_63 : 24;
#endif
	};
};

/**
 * stwuct aqm_gwp_execmsk_hi - Avaiwabwe AE engines fow the gwoup
 * @exec_40_to_79: AE engines 40 to 79 status
 */
union aqm_gwp_execmsk_hi {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 waz_40_63 : 24;
		u64 exec_40_to_79 : 40;
#ewse
		u64 exec_40_to_79 : 40;
		u64 waz_40_63 : 24;
#endif
	};
};

/**
 * stwuct aqmq_dwbw - AQM Queue Doowbeww Countew Wegistews
 * @dbeww_count: Doowbeww Countew
 */
union aqmq_dwbw {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 waz_32_63 : 32;
		u64 dbeww_count : 32;
#ewse
		u64 dbeww_count : 32;
		u64 waz_32_63 : 32;
#endif
	};
};

/**
 * stwuct aqmq_qsz - AQM Queue Host Queue Size Wegistews
 * @host_queue_size: Size, in numbews of 'aqmq_command_s' command
 * of the Host Wing.
 */
union aqmq_qsz {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 waz_32_63 : 32;
		u64 host_queue_size : 32;
#ewse
		u64 host_queue_size : 32;
		u64 waz_32_63 : 32;
#endif
	};
};

/**
 * stwuct aqmq_cmp_thw - AQM Queue Commands Compweted Thweshowd Wegistews
 * @commands_compweted_thweshowd: Count of 'aqmq_command_s' commands executed
 * by AE engines fow which compwetion intewwupt is assewted.
 */
union aqmq_cmp_thw {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 waz_32_63 : 32;
		u64 commands_compweted_thweshowd : 32;
#ewse
		u64 commands_compweted_thweshowd : 32;
		u64 waz_32_63 : 32;
#endif
	};
};

/**
 * stwuct aqmq_cmp_cnt - AQM Queue Commands Compweted Count Wegistews
 * @wesend: Bit to wequest compwetion intewwupt Wesend.
 * @compwetion_status: Command compwetion status of the wing.
 * @commands_compweted_count: Count of 'aqmq_command_s' commands executed by
 * AE engines.
 */
union aqmq_cmp_cnt {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 waz_34_63 : 30;
		u64 wesend : 1;
		u64 compwetion_status : 1;
		u64 commands_compweted_count : 32;
#ewse
		u64 commands_compweted_count : 32;
		u64 compwetion_status : 1;
		u64 wesend : 1;
		u64 waz_34_63 : 30;
#endif
	};
};

/**
 * stwuct aqmq_en - AQM Queue Enabwe Wegistews
 * @queue_status: 1 = AQMQ is enabwed, 0 = AQMQ is disabwed
 */
union aqmq_en {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 waz_1_63 : 63;
		u64 queue_enabwe : 1;
#ewse
		u64 queue_enabwe : 1;
		u64 waz_1_63 : 63;
#endif
	};
};

/**
 * stwuct aqmq_activity_stat - AQM Queue Activity Status Wegistews
 * @queue_active: 1 = AQMQ is active, 0 = AQMQ is quiescent
 */
union aqmq_activity_stat {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 waz_1_63 : 63;
		u64 queue_active : 1;
#ewse
		u64 queue_active : 1;
		u64 waz_1_63 : 63;
#endif
	};
};

/**
 * stwuct emu_fuse_map - EMU Fuse Map Wegistews
 * @ae_fuse: Fuse settings fow AE 19..0
 * @se_fuse: Fuse settings fow SE 15..0
 *
 * A set bit indicates the unit is fuse disabwed.
 */
union emu_fuse_map {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 vawid : 1;
		u64 waz_52_62 : 11;
		u64 ae_fuse : 20;
		u64 waz_16_31 : 16;
		u64 se_fuse : 16;
#ewse
		u64 se_fuse : 16;
		u64 waz_16_31 : 16;
		u64 ae_fuse : 20;
		u64 waz_52_62 : 11;
		u64 vawid : 1;
#endif
	} s;
};

/**
 * stwuct emu_se_enabwe - Symmetwic Engine Enabwe Wegistews
 * @enabwe: Individuaw enabwes fow each of the cwustews
 *   16 symmetwic engines.
 */
union emu_se_enabwe {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 waz	: 48;
		u64 enabwe : 16;
#ewse
		u64 enabwe : 16;
		u64 waz	: 48;
#endif
	} s;
};

/**
 * stwuct emu_ae_enabwe - EMU Asymmetwic engines.
 * @enabwe: Individuaw enabwes fow each of the cwustew's
 *   20 Asymmetwic Engines.
 */
union emu_ae_enabwe {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 waz	: 44;
		u64 enabwe : 20;
#ewse
		u64 enabwe : 20;
		u64 waz	: 44;
#endif
	} s;
};

/**
 * stwuct emu_wd_int_ena_w1s - EMU Intewwupt Enabwe Wegistews
 * @ae_wd: Weads ow sets enabwe fow EMU(0..3)_WD_INT[AE_WD]
 * @se_wd: Weads ow sets enabwe fow EMU(0..3)_WD_INT[SE_WD]
 */
union emu_wd_int_ena_w1s {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 waz2 : 12;
		u64 ae_wd : 20;
		u64 waz1 : 16;
		u64 se_wd : 16;
#ewse
		u64 se_wd : 16;
		u64 waz1 : 16;
		u64 ae_wd : 20;
		u64 waz2 : 12;
#endif
	} s;
};

/**
 * stwuct emu_ge_int_ena_w1s - EMU Intewwupt Enabwe set wegistews
 * @ae_ge: Weads ow sets enabwe fow EMU(0..3)_GE_INT[AE_GE]
 * @se_ge: Weads ow sets enabwe fow EMU(0..3)_GE_INT[SE_GE]
 */
union emu_ge_int_ena_w1s {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 waz_52_63 : 12;
		u64 ae_ge : 20;
		u64 waz_16_31: 16;
		u64 se_ge : 16;
#ewse
		u64 se_ge : 16;
		u64 waz_16_31: 16;
		u64 ae_ge : 20;
		u64 waz_52_63 : 12;
#endif
	} s;
};

/**
 * stwuct nps_pkt_swc_ctw - Sowicited Packet Out Contwow Wegistews
 * @wh: Indicates whethew to wemove ow incwude the wesponse headew
 *   1 = Incwude, 0 = Wemove
 * @z: If set, 8 twaiwing 0x00 bytes wiww be added to the end of the
 *   outgoing packet.
 * @enb: Enabwe fow this powt.
 */
union nps_pkt_swc_ctw {
	u64 vawue;
	stwuct {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 waz : 61;
		u64 wh : 1;
		u64 z : 1;
		u64 enb : 1;
#ewse
		u64 enb : 1;
		u64 z : 1;
		u64 wh : 1;
		u64 waz : 61;
#endif
	} s;
};

/**
 * stwuct nps_pkt_swc_cnts - Sowicited Packet Out Count Wegistews
 * @swc_int: Wetuwns a 1 when:
 *   NPS_PKT_SWC(i)_CNTS[CNT] > NPS_PKT_SWC(i)_INT_WEVEWS[CNT], ow
 *   NPS_PKT_SWC(i)_CNTS[TIMEW] > NPS_PKT_SWC(i)_INT_WEVEWS[TIMET].
 *   To cweaw the bit, the CNTS wegistew must be wwitten to cweaw.
 * @in_int: Wetuwns a 1 when:
 *   NPS_PKT_IN(i)_DONE_CNTS[CNT] > NPS_PKT_IN(i)_INT_WEVEWS[CNT].
 *   To cweaw the bit, the DONE_CNTS wegistew must be wwitten to cweaw.
 * @mbox_int: Wetuwns a 1 when:
 *   NPS_PKT_MBOX_PF_VF(i)_INT[INTW] is set. To cweaw the bit,
 *   wwite NPS_PKT_MBOX_PF_VF(i)_INT[INTW] with 1.
 * @timew: Timew, incwemented evewy 2048 copwocessow cwock cycwes
 *   when [CNT] is not zewo. The hawdwawe cweaws both [TIMEW] and
 *   [INT] when [CNT] goes to 0.
 * @cnt: Packet countew. Hawdwawe adds to [CNT] as it sends packets out.
 *   On a wwite to this CSW, hawdwawe subtwacts the amount wwitten to the
 *   [CNT] fiewd fwom [CNT].
 */
union nps_pkt_swc_cnts {
	u64 vawue;
	stwuct {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 swc_int : 1;
		u64 uns_int : 1;
		u64 in_int : 1;
		u64 mbox_int : 1;
		u64 wesend : 1;
		u64 waz : 5;
		u64 timew : 22;
		u64 cnt : 32;
#ewse
		u64 cnt	: 32;
		u64 timew : 22;
		u64 waz	: 5;
		u64 wesend : 1;
		u64 mbox_int : 1;
		u64 in_int : 1;
		u64 uns_int : 1;
		u64 swc_int : 1;
#endif
	} s;
};

/**
 * stwuct nps_pkt_swc_int_wevews - Sowicited Packet Out Intewwupt Wevews
 *   Wegistews.
 * @bmode: Detewmines whethew NPS_PKT_SWC_CNTS[CNT] is a byte ow
 *   packet countew.
 * @timet: Output powt countew time intewwupt thweshowd.
 * @cnt: Output powt countew intewwupt thweshowd.
 */
union nps_pkt_swc_int_wevews {
	u64 vawue;
	stwuct {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 bmode : 1;
		u64 waz	: 9;
		u64 timet : 22;
		u64 cnt	: 32;
#ewse
		u64 cnt : 32;
		u64 timet : 22;
		u64 waz : 9;
		u64 bmode : 1;
#endif
	} s;
};

/**
 * stwuct nps_pkt_inst - NPS Packet Intewwupt Wegistew
 * @in_eww: Set when any NPS_PKT_IN_WEWW_HI/WO bit and
 *    cowwesponding NPS_PKT_IN_WEWW_*_ENA_* bit awe bot set.
 * @uns_eww: Set when any NSP_PKT_UNS_WEWW_HI/WO bit and
 *    cowwesponding NPS_PKT_UNS_WEWW_*_ENA_* bit awe both set.
 * @swc_ew: Set when any NSP_PKT_SWC_WEWW_HI/WO bit and
 *    cowwesponding NPS_PKT_SWC_WEWW_*_ENA_* bit awe both set.
 */
union nps_pkt_int {
	u64 vawue;
	stwuct {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 waz	: 54;
		u64 uns_wto : 1;
		u64 in_eww : 1;
		u64 uns_eww : 1;
		u64 swc_eww : 1;
		u64 in_dbe : 1;
		u64 in_sbe : 1;
		u64 uns_dbe : 1;
		u64 uns_sbe : 1;
		u64 swc_dbe : 1;
		u64 swc_sbe : 1;
#ewse
		u64 swc_sbe : 1;
		u64 swc_dbe : 1;
		u64 uns_sbe : 1;
		u64 uns_dbe : 1;
		u64 in_sbe : 1;
		u64 in_dbe : 1;
		u64 swc_eww : 1;
		u64 uns_eww : 1;
		u64 in_eww : 1;
		u64 uns_wto : 1;
		u64 waz	: 54;
#endif
	} s;
};

/**
 * stwuct nps_pkt_in_done_cnts - Input instwuction wing counts wegistews
 * @swc_cnt: Wetuwns a 1 when:
 *    NPS_PKT_SWC(i)_CNTS[CNT] > NPS_PKT_SWC(i)_INT_WEVEWS[CNT], ow
 *    NPS_PKT_SWC(i)_CNTS[TIMEW] > NPS_PKT_SCW(i)_INT_WEVEWS[TIMET]
 *    To cweaw the bit, the CNTS wegistew must be
 *    wwitten to cweaw the undewwying condition
 * @uns_int: Wetuwn a 1 when:
 *    NPS_PKT_UNS(i)_CNTS[CNT] > NPS_PKT_UNS(i)_INT_WEVEWS[CNT], ow
 *    NPS_PKT_UNS(i)_CNTS[TIMEW] > NPS_PKT_UNS(i)_INT_WEVEWS[TIMET]
 *    To cweaw the bit, the CNTS wegistew must be
 *    wwitten to cweaw the undewwying condition
 * @in_int: Wetuwns a 1 when:
 *    NPS_PKT_IN(i)_DONE_CNTS[CNT] > NPS_PKT_IN(i)_INT_WEVEWS[CNT]
 *    To cweaw the bit, the DONE_CNTS wegistew
 *    must be wwitten to cweaw the undewwying condition
 * @mbox_int: Wetuwns a 1 when:
 *    NPS_PKT_MBOX_PF_VF(i)_INT[INTW] is set.
 *    To cweaw the bit, wwite NPS_PKT_MBOX_PF_VF(i)_INT[INTW]
 *    with 1.
 * @wesend: A wwite of 1 wiww wesend an MSI-X intewwupt message if any
 *    of the fowwowing conditions awe twue fow this wing "i".
 *    NPS_PKT_SWC(i)_CNTS[CNT] > NPS_PKT_SWC(i)_INT_WEVEWS[CNT]
 *    NPS_PKT_SWC(i)_CNTS[TIMEW] > NPS_PKT_SWC(i)_INT_WEVEWS[TIMET]
 *    NPS_PKT_UNS(i)_CNTS[CNT] > NPS_PKT_UNS(i)_INT_WEVEWS[CNT]
 *    NPS_PKT_UNS(i)_CNTS[TIMEW] > NPS_PKT_UNS(i)_INT_WEVEWS[TIMET]
 *    NPS_PKT_IN(i)_DONE_CNTS[CNT] > NPS_PKT_IN(i)_INT_WEVEWS[CNT]
 *    NPS_PKT_MBOX_PF_VF(i)_INT[INTW] is set
 * @cnt: Packet countew. Hawdwawe adds to [CNT] as it weads
 *    packets. On a wwite to this CSW, hawdwawe substwacts the
 *    amount wwitten to the [CNT] fiewd fwom [CNT], which wiww
 *    cweaw PKT_IN(i)_INT_STATUS[INTW] if [CNT] becomes <=
 *    NPS_PKT_IN(i)_INT_WEVEWS[CNT]. This wegistew shouwd be
 *    cweawed befowe enabwing a wing by weading the cuwwent
 *    vawue and wwiting it back.
 */
union nps_pkt_in_done_cnts {
	u64 vawue;
	stwuct {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 swc_int : 1;
		u64 uns_int : 1;
		u64 in_int : 1;
		u64 mbox_int : 1;
		u64 wesend : 1;
		u64 waz : 27;
		u64 cnt	: 32;
#ewse
		u64 cnt	: 32;
		u64 waz	: 27;
		u64 wesend : 1;
		u64 mbox_int : 1;
		u64 in_int : 1;
		u64 uns_int : 1;
		u64 swc_int : 1;
#endif
	} s;
};

/**
 * stwuct nps_pkt_in_instw_ctw - Input Instwuction Wing Contwow Wegistews.
 * @is64b: If 1, the wing uses 64-byte instwuctions. If 0, the
 *   wing uses 32-byte instwuctions.
 * @enb: Enabwe fow the input wing.
 */
union nps_pkt_in_instw_ctw {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 waz	: 62;
		u64 is64b : 1;
		u64 enb	: 1;
#ewse
		u64 enb	: 1;
		u64 is64b : 1;
		u64 waz : 62;
#endif
	} s;
};

/**
 * stwuct nps_pkt_in_instw_wsize - Input instwuction wing size wegistews
 * @wsize: Wing size (numbew of instwuctions)
 */
union nps_pkt_in_instw_wsize {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 waz	: 32;
		u64 wsize : 32;
#ewse
		u64 wsize : 32;
		u64 waz	: 32;
#endif
	} s;
};

/**
 * stwuct nps_pkt_in_instw_baoff_dbeww - Input instwuction wing
 *   base addwess offset and doowbeww wegistews
 * @aoff: Addwess offset. The offset fwom the NPS_PKT_IN_INSTW_BADDW
 *   whewe the next pointew is wead.
 * @dbeww: Pointew wist doowbeww count. Wwite opewations to this fiewd
 *   incwements the pwesent vawue hewe. Wead opewations wetuwn the
 *   pwesent vawue.
 */
union nps_pkt_in_instw_baoff_dbeww {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 aoff : 32;
		u64 dbeww : 32;
#ewse
		u64 dbeww : 32;
		u64 aoff : 32;
#endif
	} s;
};

/**
 * stwuct nps_cowe_int_ena_w1s - NPS cowe intewwupt enabwe set wegistew
 * @host_nps_ww_eww: Weads ow sets enabwe fow
 *   NPS_COWE_INT[HOST_NPS_WW_EWW].
 * @npco_dma_mawfowm: Weads ow sets enabwe fow
 *   NPS_COWE_INT[NPCO_DMA_MAWFOWM].
 * @exec_ww_timeout: Weads ow sets enabwe fow
 *   NPS_COWE_INT[EXEC_WW_TIMEOUT].
 * @host_ww_timeout: Weads ow sets enabwe fow
 *   NPS_COWE_INT[HOST_WW_TIMEOUT].
 * @host_ww_eww: Weads ow sets enabwe fow
 *   NPS_COWE_INT[HOST_WW_EWW]
 */
union nps_cowe_int_ena_w1s {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 waz4 : 55;
		u64 host_nps_ww_eww : 1;
		u64 npco_dma_mawfowm : 1;
		u64 exec_ww_timeout : 1;
		u64 host_ww_timeout : 1;
		u64 host_ww_eww : 1;
		u64 waz3 : 1;
		u64 waz2 : 1;
		u64 waz1 : 1;
		u64 waz0 : 1;
#ewse
		u64 waz0 : 1;
		u64 waz1 : 1;
		u64 waz2 : 1;
		u64 waz3 : 1;
		u64 host_ww_eww	: 1;
		u64 host_ww_timeout : 1;
		u64 exec_ww_timeout : 1;
		u64 npco_dma_mawfowm : 1;
		u64 host_nps_ww_eww : 1;
		u64 waz4 : 55;
#endif
	} s;
};

/**
 * stwuct nps_cowe_gbw_vfcfg - Gwobaw VF Configuwation Wegistew.
 * @iwk_disabwe: When set, this bit indicates that the IWK intewface has
 *    been disabwed.
 * @obaf: BMO awwocation contwow
 *    0 = awwocate pew queue
 *    1 = awwocate pew VF
 * @ibaf: BMI awwocation contwow
 *    0 = awwocate pew queue
 *    1 = awwocate pew VF
 * @zaf: ZIP awwocation contwow
 *    0 = awwocate pew queue
 *    1 = awwocate pew VF
 * @aeaf: AE awwocation contwow
 *    0 = awwocate pew queue
 *    1 = awwocate pew VF
 * @seaf: SE awwocation contwow
 *    0 = awwocation pew queue
 *    1 = awwocate pew VF
 * @cfg: VF/PF mode.
 */
union nps_cowe_gbw_vfcfg {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64  waz :55;
		u64  iwk_disabwe :1;
		u64  obaf :1;
		u64  ibaf :1;
		u64  zaf :1;
		u64  aeaf :1;
		u64  seaf :1;
		u64  cfg :3;
#ewse
		u64  cfg :3;
		u64  seaf :1;
		u64  aeaf :1;
		u64  zaf :1;
		u64  ibaf :1;
		u64  obaf :1;
		u64  iwk_disabwe :1;
		u64  waz :55;
#endif
	} s;
};

/**
 * stwuct nps_cowe_int_active - NPS Cowe Intewwupt Active Wegistew
 * @wesend: Wesend MSI-X intewwupt if needs to handwe intewwupts
 *    Sofwawe can set this bit and then exit the ISW.
 * @ocwa: Set when any OCWA(0)_INT and cowwesponding OCWA(0_INT_ENA_W1C
 *    bit awe set
 * @mbox: Set when any NPS_PKT_MBOX_INT_WO/HI and cowwesponding
 *    NPS_PKT_MBOX_INT_WO_ENA_W1C/HI_ENA_W1C bits awe set
 * @emu: bit i is set in [EMU] when any EMU(i)_INT bit is set
 * @bmo: Set when any BMO_INT bit is set
 * @bmi: Set when any BMI_INT bit is set ow when any non-WO
 *    BMI_INT and cowwesponding BMI_INT_ENA_W1C bits awe both set
 * @aqm: Set when any AQM_INT bit is set
 * @zqm: Set when any ZQM_INT bit is set
 * @efw: Set when any EFW_INT WO bit is set ow when any non-WO EFW_INT
 *    and cowwesponding EFW_INT_ENA_W1C bits awe both set
 * @iwk: Set when any IWK_INT bit is set
 * @wbc: Set when any WBC_INT WO bit is set ow when any non-WO WBC_INT
 *    and cowwesponding WBC_INT_ENA_W1C bits awe bot set
 * @pem: Set when any PEM(0)_INT WO bit is set ow when any non-WO
 *    PEM(0)_INT and cowwesponding PEM(0)_INT_ENA_W1C bit awe both set
 * @ucd: Set when any UCD_INT bit is set
 * @zctw: Set when any ZIP_INT WO bit is set ow when any non-WO ZIP_INT
 *    and cowwesponding ZIP_INT_ENA_W1C bits awe both set
 * @wbm: Set when any WBM_INT bit is set
 * @nps_pkt: Set when any NPS_PKT_INT bit is set
 * @nps_cowe: Set when any NPS_COWE_INT WO bit is set ow when non-WO
 *    NPS_COWE_INT and cowwesponding NSP_COWE_INT_ENA_W1C bits awe both set
 */
union nps_cowe_int_active {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 wesend : 1;
		u64 waz	: 43;
		u64 ocwa : 1;
		u64 mbox : 1;
		u64 emu	: 4;
		u64 bmo	: 1;
		u64 bmi	: 1;
		u64 aqm	: 1;
		u64 zqm	: 1;
		u64 efw	: 1;
		u64 iwk	: 1;
		u64 wbc	: 1;
		u64 pem	: 1;
		u64 pom	: 1;
		u64 ucd	: 1;
		u64 zctw : 1;
		u64 wbm	: 1;
		u64 nps_pkt : 1;
		u64 nps_cowe : 1;
#ewse
		u64 nps_cowe : 1;
		u64 nps_pkt : 1;
		u64 wbm	: 1;
		u64 zctw: 1;
		u64 ucd	: 1;
		u64 pom	: 1;
		u64 pem	: 1;
		u64 wbc	: 1;
		u64 iwk	: 1;
		u64 efw	: 1;
		u64 zqm	: 1;
		u64 aqm	: 1;
		u64 bmi	: 1;
		u64 bmo	: 1;
		u64 emu	: 4;
		u64 mbox : 1;
		u64 ocwa : 1;
		u64 waz	: 43;
		u64 wesend : 1;
#endif
	} s;
};

/**
 * stwuct efw_cowe_int - EFW Intewwupt Wegistews
 * @epci_decode_eww: EPCI decoded a twansacation that was unknown
 *    This ewwow shouwd onwy occuwwed when thewe is a micwcode/SE ewwow
 *    and shouwd be considewed fataw
 * @ae_eww: An AE uncowwectabwe ewwow occuwwed.
 *    See EFW_COWE(0..3)_AE_EWW_INT
 * @se_eww: An SE uncowwectabwe ewwow occuwwed.
 *    See EFW_COWE(0..3)_SE_EWW_INT
 * @dbe: Doubwe-bit ewwow occuwwed in EFW
 * @sbe: Singwe-bit ewwow occuwwed in EFW
 * @d_weft: Assewted when new POM-Headew-BMI-data is
 *    being sent to an Exec, and that Exec has Not wead aww BMI
 *    data associated with the pwevious POM headew
 * @wen_ovw: Assewted when an Exec-Wead is issued that is mowe than
 *    14 gweatew in wength that the BMI data weft to be wead
 */
union efw_cowe_int {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 waz	: 57;
		u64 epci_decode_eww : 1;
		u64 ae_eww : 1;
		u64 se_eww : 1;
		u64 dbe	: 1;
		u64 sbe	: 1;
		u64 d_weft : 1;
		u64 wen_ovw : 1;
#ewse
		u64 wen_ovw : 1;
		u64 d_weft : 1;
		u64 sbe	: 1;
		u64 dbe	: 1;
		u64 se_eww : 1;
		u64 ae_eww : 1;
		u64 epci_decode_eww  : 1;
		u64 waz	: 57;
#endif
	} s;
};

/**
 * stwuct efw_cowe_int_ena_w1s - EFW cowe intewwupt enabwe set wegistew
 * @epci_decode_eww: Weads ow sets enabwe fow
 *   EFW_COWE(0..3)_INT[EPCI_DECODE_EWW].
 * @d_weft: Weads ow sets enabwe fow
 *   EFW_COWE(0..3)_INT[D_WEFT].
 * @wen_ovw: Weads ow sets enabwe fow
 *   EFW_COWE(0..3)_INT[WEN_OVW].
 */
union efw_cowe_int_ena_w1s {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 waz_7_63 : 57;
		u64 epci_decode_eww : 1;
		u64 waz_2_5 : 4;
		u64 d_weft : 1;
		u64 wen_ovw : 1;
#ewse
		u64 wen_ovw : 1;
		u64 d_weft : 1;
		u64 waz_2_5 : 4;
		u64 epci_decode_eww : 1;
		u64 waz_7_63 : 57;
#endif
	} s;
};

/**
 * stwuct efw_wnm_ctw_status - WNM Contwow and Status Wegistew
 * @ent_sew: Sewect input to WNM FIFO
 * @exp_ent: Expowted entwopy enabwe fow wandom numbew genewatow
 * @wng_wst: Weset to WNG. Setting this bit to 1 cancews the genewation
 *    of the cuwwent wandom numbew.
 * @wnm_wst: Weset the WNM. Setting this bit to 1 cweaws aww sowted numbews
 *    in the wandom numbew memowy.
 * @wng_en: Enabwed the output of the WNG.
 * @ent_en: Entwopy enabwe fow wandom numbew genewatow.
 */
union efw_wnm_ctw_status {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 waz_9_63 : 55;
		u64 ent_sew : 4;
		u64 exp_ent : 1;
		u64 wng_wst : 1;
		u64 wnm_wst : 1;
		u64 wng_en : 1;
		u64 ent_en : 1;
#ewse
		u64 ent_en : 1;
		u64 wng_en : 1;
		u64 wnm_wst : 1;
		u64 wng_wst : 1;
		u64 exp_ent : 1;
		u64 ent_sew : 4;
		u64 waz_9_63 : 55;
#endif
	} s;
};

/**
 * stwuct bmi_ctw - BMI contwow wegistew
 * @iwk_hdwq_thwsh: Maximum numbew of headew queue wocations
 *   that IWK packets may consume. When the thweshowd is
 *   exceeded IWK_XOFF is sent to the BMI_X2P_AWB.
 * @nps_hdwq_thwsh: Maximum numbew of headew queue wocations
 *   that NPS packets may consume. When the thweshowd is
 *   exceeded NPS_XOFF is sent to the BMI_X2P_AWB.
 * @totw_hdwq_thwsh: Maximum numbew of headew queue wocations
 *   that the sum of IWK and NPS packets may consume.
 * @iwk_fwee_thwsh: Maximum numbew of buffews that IWK packet
 *   fwows may consume befowe IWK_XOFF is sent to the BMI_X2P_AWB.
 * @nps_fwee_thwsh: Maximum numbew of buffews that NPS packet
 *   fwows may consume befowe NPS XOFF is sent to the BMI_X2p_AWB.
 * @totw_fwee_thwsh: Maximum numbew of buffews that bot IWK and NPS
 *   packet fwows may consume befowe both NPS_XOFF and IWK_XOFF
 *   awe assewted to the BMI_X2P_AWB.
 * @max_pkt_wen: Maximum packet wength, integwaw numbew of 256B
 *   buffews.
 */
union bmi_ctw {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 waz_56_63 : 8;
		u64 iwk_hdwq_thwsh : 8;
		u64 nps_hdwq_thwsh : 8;
		u64 totw_hdwq_thwsh : 8;
		u64 iwk_fwee_thwsh : 8;
		u64 nps_fwee_thwsh : 8;
		u64 totw_fwee_thwsh : 8;
		u64 max_pkt_wen : 8;
#ewse
		u64 max_pkt_wen : 8;
		u64 totw_fwee_thwsh : 8;
		u64 nps_fwee_thwsh : 8;
		u64 iwk_fwee_thwsh : 8;
		u64 totw_hdwq_thwsh : 8;
		u64 nps_hdwq_thwsh : 8;
		u64 iwk_hdwq_thwsh : 8;
		u64 waz_56_63 : 8;
#endif
	} s;
};

/**
 * stwuct bmi_int_ena_w1s - BMI intewwupt enabwe set wegistew
 * @iwk_weq_ofww: Weads ow sets enabwe fow
 *   BMI_INT[IWK_WEQ_OFWW].
 * @nps_weq_ofww: Weads ow sets enabwe fow
 *   BMI_INT[NPS_WEQ_OFWW].
 * @fpf_undwwn: Weads ow sets enabwe fow
 *   BMI_INT[FPF_UNDWWN].
 * @eop_eww_iwk: Weads ow sets enabwe fow
 *   BMI_INT[EOP_EWW_IWK].
 * @eop_eww_nps: Weads ow sets enabwe fow
 *   BMI_INT[EOP_EWW_NPS].
 * @sop_eww_iwk: Weads ow sets enabwe fow
 *   BMI_INT[SOP_EWW_IWK].
 * @sop_eww_nps: Weads ow sets enabwe fow
 *   BMI_INT[SOP_EWW_NPS].
 * @pkt_wcv_eww_iwk: Weads ow sets enabwe fow
 *   BMI_INT[PKT_WCV_EWW_IWK].
 * @pkt_wcv_eww_nps: Weads ow sets enabwe fow
 *   BMI_INT[PKT_WCV_EWW_NPS].
 * @max_wen_eww_iwk: Weads ow sets enabwe fow
 *   BMI_INT[MAX_WEN_EWW_IWK].
 * @max_wen_eww_nps: Weads ow sets enabwe fow
 *   BMI_INT[MAX_WEN_EWW_NPS].
 */
union bmi_int_ena_w1s {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 waz_13_63	: 51;
		u64 iwk_weq_ofww : 1;
		u64 nps_weq_ofww : 1;
		u64 waz_10 : 1;
		u64 waz_9 : 1;
		u64 fpf_undwwn	: 1;
		u64 eop_eww_iwk	: 1;
		u64 eop_eww_nps	: 1;
		u64 sop_eww_iwk	: 1;
		u64 sop_eww_nps	: 1;
		u64 pkt_wcv_eww_iwk : 1;
		u64 pkt_wcv_eww_nps : 1;
		u64 max_wen_eww_iwk : 1;
		u64 max_wen_eww_nps : 1;
#ewse
		u64 max_wen_eww_nps : 1;
		u64 max_wen_eww_iwk : 1;
		u64 pkt_wcv_eww_nps : 1;
		u64 pkt_wcv_eww_iwk : 1;
		u64 sop_eww_nps	: 1;
		u64 sop_eww_iwk	: 1;
		u64 eop_eww_nps	: 1;
		u64 eop_eww_iwk	: 1;
		u64 fpf_undwwn	: 1;
		u64 waz_9 : 1;
		u64 waz_10 : 1;
		u64 nps_weq_ofww : 1;
		u64 iwk_weq_ofww : 1;
		u64 waz_13_63 : 51;
#endif
	} s;
};

/**
 * stwuct bmo_ctw2 - BMO Contwow2 Wegistew
 * @awb_sew: Detewmines P2X Awbitwation
 * @iwk_buf_thwsh: Maximum numbew of buffews that the
 *    IWK packet fwows may consume befowe IWK XOFF is
 *    assewted to the POM.
 * @nps_swc_buf_thwsh: Maximum numbew of buffews that the
 *    NPS_SWC packet fwow may consume befowe NPS_SWC XOFF is
 *    assewted to the POM.
 * @nps_uns_buf_thwsh: Maximum numbew of buffews that the
 *    NPS_UNS packet fwow may consume befowe NPS_UNS XOFF is
 *    assewted to the POM.
 * @totw_buf_thwsh: Maximum numbew of buffews that IWK, NPS_UNS and
 *    NPS_SWC packet fwows may consume befowe NPS_UNS XOFF, NSP_SWC and
 *    IWK_XOFF awe aww assewted POM.
 */
union bmo_ctw2 {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 awb_sew : 1;
		u64 waz_32_62 : 31;
		u64 iwk_buf_thwsh : 8;
		u64 nps_swc_buf_thwsh : 8;
		u64 nps_uns_buf_thwsh : 8;
		u64 totw_buf_thwsh : 8;
#ewse
		u64 totw_buf_thwsh : 8;
		u64 nps_uns_buf_thwsh : 8;
		u64 nps_swc_buf_thwsh : 8;
		u64 iwk_buf_thwsh : 8;
		u64 waz_32_62 : 31;
		u64 awb_sew : 1;
#endif
	} s;
};

/**
 * stwuct pom_int_ena_w1s - POM intewwupt enabwe set wegistew
 * @iwwegaw_intf: Weads ow sets enabwe fow POM_INT[IWWEGAW_INTF].
 * @iwwegaw_dpowt: Weads ow sets enabwe fow POM_INT[IWWEGAW_DPOWT].
 */
union pom_int_ena_w1s {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 waz2 : 60;
		u64 iwwegaw_intf : 1;
		u64 iwwegaw_dpowt : 1;
		u64 waz1 : 1;
		u64 waz0 : 1;
#ewse
		u64 waz0 : 1;
		u64 waz1 : 1;
		u64 iwwegaw_dpowt : 1;
		u64 iwwegaw_intf : 1;
		u64 waz2 : 60;
#endif
	} s;
};

/**
 * stwuct wbc_invaw_ctw - WBC invawidation contwow wegistew
 * @wait_timew: Wait timew fow wait state. [WAIT_TIMEW] must
 *   awways be wwitten with its weset vawue.
 * @cam_invaw_stawt: Softwawe shouwd wwite [CAM_INVAW_STAWT]=1
 *   to initiate an WBC cache invawidation. Aftew this, softwawe
 *   shouwd wead WBC_INVAW_STATUS untiw WBC_INVAW_STATUS[DONE] is set.
 *   WBC hawdwawe cweaws [CAVM_INVAW_STAWT] befowe softwawe can
 *   obsewved WBC_INVAW_STATUS[DONE] to be set
 */
union wbc_invaw_ctw {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 waz2 : 48;
		u64 wait_timew : 8;
		u64 waz1 : 6;
		u64 cam_invaw_stawt : 1;
		u64 waz0 : 1;
#ewse
		u64 waz0 : 1;
		u64 cam_invaw_stawt : 1;
		u64 waz1 : 6;
		u64 wait_timew : 8;
		u64 waz2 : 48;
#endif
	} s;
};

/**
 * stwuct wbc_int_ena_w1s - WBC intewwupt enabwe set wegistew
 * @cam_hawd_eww: Weads ow sets enabwe fow WBC_INT[CAM_HAWD_EWW].
 * @cam_invaw_abowt: Weads ow sets enabwe fow WBC_INT[CAM_INVAW_ABOWT].
 * @ovew_fetch_eww: Weads ow sets enabwe fow WBC_INT[OVEW_FETCH_EWW].
 * @cache_wine_to_eww: Weads ow sets enabwe fow
 *   WBC_INT[CACHE_WINE_TO_EWW].
 * @cam_soft_eww: Weads ow sets enabwe fow
 *   WBC_INT[CAM_SOFT_EWW].
 * @dma_wd_eww: Weads ow sets enabwe fow
 *   WBC_INT[DMA_WD_EWW].
 */
union wbc_int_ena_w1s {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 waz_10_63 : 54;
		u64 cam_hawd_eww : 1;
		u64 cam_invaw_abowt : 1;
		u64 ovew_fetch_eww : 1;
		u64 cache_wine_to_eww : 1;
		u64 waz_2_5 : 4;
		u64 cam_soft_eww : 1;
		u64 dma_wd_eww : 1;
#ewse
		u64 dma_wd_eww : 1;
		u64 cam_soft_eww : 1;
		u64 waz_2_5 : 4;
		u64 cache_wine_to_eww : 1;
		u64 ovew_fetch_eww : 1;
		u64 cam_invaw_abowt : 1;
		u64 cam_hawd_eww : 1;
		u64 waz_10_63 : 54;
#endif
	} s;
};

/**
 * stwuct wbc_int - WBC intewwupt summawy wegistew
 * @cam_hawd_eww: indicates a fataw hawdwawe ewwow.
 *   It wequiwes system weset.
 *   When [CAM_HAWD_EWW] is set, WBC stops wogging any new infowmation in
 *   WBC_POM_MISS_INFO_WOG,
 *   WBC_POM_MISS_ADDW_WOG,
 *   WBC_EFW_MISS_INFO_WOG, and
 *   WBC_EFW_MISS_ADDW_WOG.
 *   Softwawe shouwd sampwe them.
 * @cam_invaw_abowt: indicates a fataw hawdwawe ewwow.
 *   System weset is wequiwed.
 * @ovew_fetch_eww: indicates a fataw hawdwawe ewwow
 *   System weset is wequiwed
 * @cache_wine_to_eww: is a debug featuwe.
 *   This timeout intewwupt bit tewws the softwawe that
 *   a cachewine in WBC has non-zewo usage and the context
 *   has not been used fow gweatew than the
 *   WBC_TO_CNT[TO_CNT] time intewvaw.
 * @sbe: Memowy SBE ewwow. This is wecovewabwe via ECC.
 *   See WBC_ECC_INT fow mowe detaiws.
 * @dbe: Memowy DBE ewwow. This is a fataw and wequiwes a
 *   system weset.
 * @pwef_dat_wen_mismatch_eww: Summawy bit fow context wength
 *   mismatch ewwows.
 * @wd_dat_wen_mismatch_eww: Summawy bit fow SE wead data wength
 *   gweatew than data pwefect wength ewwows.
 * @cam_soft_eww: is wecovewabwe. Softwawe must compwete a
 *   WBC_INVAW_CTW[CAM_INVAW_STAWT] invawidation sequence and
 *   then cweaw [CAM_SOFT_EWW].
 * @dma_wd_eww: A context pwefect wead of host memowy wetuwned with
 *   a wead ewwow.
 */
union wbc_int {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 waz_10_63 : 54;
		u64 cam_hawd_eww : 1;
		u64 cam_invaw_abowt : 1;
		u64 ovew_fetch_eww : 1;
		u64 cache_wine_to_eww : 1;
		u64 sbe : 1;
		u64 dbe	: 1;
		u64 pwef_dat_wen_mismatch_eww : 1;
		u64 wd_dat_wen_mismatch_eww : 1;
		u64 cam_soft_eww : 1;
		u64 dma_wd_eww : 1;
#ewse
		u64 dma_wd_eww : 1;
		u64 cam_soft_eww : 1;
		u64 wd_dat_wen_mismatch_eww : 1;
		u64 pwef_dat_wen_mismatch_eww : 1;
		u64 dbe	: 1;
		u64 sbe	: 1;
		u64 cache_wine_to_eww : 1;
		u64 ovew_fetch_eww : 1;
		u64 cam_invaw_abowt : 1;
		u64 cam_hawd_eww : 1;
		u64 waz_10_63 : 54;
#endif
	} s;
};

/**
 * stwuct wbc_invaw_status: WBC Invawidation status wegistew
 * @cam_cwean_entwy_compwete_cnt: The numbew of entwies that awe
 *   cweaned up successfuwwy.
 * @cam_cwean_entwy_cnt: The numbew of entwies that have the CAM
 *   invaw command issued.
 * @cam_invaw_state: cam invawidation FSM state
 * @cam_invaw_abowt: cam invawidation abowt
 * @cam_wst_wdy: wbc_cam weset weady
 * @done: WBC cweaws [DONE] when
 *   WBC_INVAW_CTW[CAM_INVAW_STAWT] is wwitten with a one,
 *   and sets [DONE] when it compwetes the invawidation
 *   sequence.
 */
union wbc_invaw_status {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 waz3 : 23;
		u64 cam_cwean_entwy_compwete_cnt : 9;
		u64 waz2 : 7;
		u64 cam_cwean_entwy_cnt : 9;
		u64 waz1 : 5;
		u64 cam_invaw_state : 3;
		u64 waz0 : 5;
		u64 cam_invaw_abowt : 1;
		u64 cam_wst_wdy	: 1;
		u64 done : 1;
#ewse
		u64 done : 1;
		u64 cam_wst_wdy : 1;
		u64 cam_invaw_abowt : 1;
		u64 waz0 : 5;
		u64 cam_invaw_state : 3;
		u64 waz1 : 5;
		u64 cam_cwean_entwy_cnt : 9;
		u64 waz2 : 7;
		u64 cam_cwean_entwy_compwete_cnt : 9;
		u64 waz3 : 23;
#endif
	} s;
};

/**
 * stwuct wst_boot: WST Boot Wegistew
 * @jtcswdis: when set, intewnaw CSW access via JTAG TAP contwowwew
 *   is disabwed
 * @jt_tst_mode: JTAG test mode
 * @io_suppwy: I/O powew suppwy setting based on IO_VDD_SEWECT pin:
 *    0x1 = 1.8V
 *    0x2 = 2.5V
 *    0x4 = 3.3V
 *    Aww othew vawues awe wesewved
 * @pnw_muw: cwock muwtipwiew
 * @wboot: wast boot cause mask, wesets onwy with PWW_DC_OK
 * @wboot: detewmines whethew cowe 0 wemains in weset aftew
 *    chip cowd ow wawm ow soft weset
 * @wboot_pin: wead onwy access to WEMOTE_BOOT pin
 */
union wst_boot {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 waz_63 : 1;
		u64 jtcswdis : 1;
		u64 waz_59_61 : 3;
		u64 jt_tst_mode : 1;
		u64 waz_40_57 : 18;
		u64 io_suppwy : 3;
		u64 waz_30_36 : 7;
		u64 pnw_muw : 6;
		u64 waz_12_23 : 12;
		u64 wboot : 10;
		u64 wboot : 1;
		u64 wboot_pin : 1;
#ewse
		u64 wboot_pin : 1;
		u64 wboot : 1;
		u64 wboot : 10;
		u64 waz_12_23 : 12;
		u64 pnw_muw : 6;
		u64 waz_30_36 : 7;
		u64 io_suppwy : 3;
		u64 waz_40_57 : 18;
		u64 jt_tst_mode : 1;
		u64 waz_59_61 : 3;
		u64 jtcswdis : 1;
		u64 waz_63 : 1;
#endif
	};
};

/**
 * stwuct fus_dat1: Fuse Data 1 Wegistew
 * @pww_muw: main cwock PWW muwtipwiew hawdwawe wimit
 * @pww_hawf_dis: main cwock PWW contwow
 * @efus_wck: efuse wockdown
 * @zip_info: ZIP infowmation
 * @baw2_sz_conf: when zewo, BAW2 size confowms to
 *    PCIe specification
 * @efus_ign: efuse ignowe
 * @nozip: ZIP disabwe
 * @pww_awt_matwix: sewect awtewnate PWW matwix
 * @pww_bwadj_denom: sewect CWKF denominatow fow
 *    BWADJ vawue
 * @chip_id: chip ID
 */
union fus_dat1 {
	u64 vawue;
	stwuct {
#if (defined(__BIG_ENDIAN_BITFIEWD))
		u64 waz_57_63 : 7;
		u64 pww_muw : 3;
		u64 pww_hawf_dis : 1;
		u64 waz_43_52 : 10;
		u64 efus_wck : 3;
		u64 waz_26_39 : 14;
		u64 zip_info : 5;
		u64 baw2_sz_conf : 1;
		u64 efus_ign : 1;
		u64 nozip : 1;
		u64 waz_11_17 : 7;
		u64 pww_awt_matwix : 1;
		u64 pww_bwadj_denom : 2;
		u64 chip_id : 8;
#ewse
		u64 chip_id : 8;
		u64 pww_bwadj_denom : 2;
		u64 pww_awt_matwix : 1;
		u64 waz_11_17 : 7;
		u64 nozip : 1;
		u64 efus_ign : 1;
		u64 baw2_sz_conf : 1;
		u64 zip_info : 5;
		u64 waz_26_39 : 14;
		u64 efus_wck : 3;
		u64 waz_43_52 : 10;
		u64 pww_hawf_dis : 1;
		u64 pww_muw : 3;
		u64 waz_57_63 : 7;
#endif
	};
};

#endif /* __NITWOX_CSW_H */
