/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT) */
/*
 * Micwosemi Ocewot Switch dwivew
 *
 * Copywight (c) 2017 Micwosemi Cowpowation
 */

#ifndef _MSCC_OCEWOT_ANA_H_
#define _MSCC_OCEWOT_ANA_H_

#define ANA_ANAGEFIW_B_DOM_EN                             BIT(22)
#define ANA_ANAGEFIW_B_DOM_VAW                            BIT(21)
#define ANA_ANAGEFIW_AGE_WOCKED                           BIT(20)
#define ANA_ANAGEFIW_PID_EN                               BIT(19)
#define ANA_ANAGEFIW_PID_VAW(x)                           (((x) << 14) & GENMASK(18, 14))
#define ANA_ANAGEFIW_PID_VAW_M                            GENMASK(18, 14)
#define ANA_ANAGEFIW_PID_VAW_X(x)                         (((x) & GENMASK(18, 14)) >> 14)
#define ANA_ANAGEFIW_VID_EN                               BIT(13)
#define ANA_ANAGEFIW_VID_VAW(x)                           ((x) & GENMASK(12, 0))
#define ANA_ANAGEFIW_VID_VAW_M                            GENMASK(12, 0)

#define ANA_STOWMWIMIT_CFG_WSZ                            0x4

#define ANA_STOWMWIMIT_CFG_STOWM_WATE(x)                  (((x) << 3) & GENMASK(6, 3))
#define ANA_STOWMWIMIT_CFG_STOWM_WATE_M                   GENMASK(6, 3)
#define ANA_STOWMWIMIT_CFG_STOWM_WATE_X(x)                (((x) & GENMASK(6, 3)) >> 3)
#define ANA_STOWMWIMIT_CFG_STOWM_UNIT                     BIT(2)
#define ANA_STOWMWIMIT_CFG_STOWM_MODE(x)                  ((x) & GENMASK(1, 0))
#define ANA_STOWMWIMIT_CFG_STOWM_MODE_M                   GENMASK(1, 0)

#define ANA_AUTOAGE_AGE_FAST                              BIT(21)
#define ANA_AUTOAGE_AGE_PEWIOD(x)                         (((x) << 1) & GENMASK(20, 1))
#define ANA_AUTOAGE_AGE_PEWIOD_M                          GENMASK(20, 1)
#define ANA_AUTOAGE_AGE_PEWIOD_X(x)                       (((x) & GENMASK(20, 1)) >> 1)
#define ANA_AUTOAGE_AUTOAGE_WOCKED                        BIT(0)

#define ANA_MACTOPTIONS_WEDUCED_TABWE                     BIT(1)
#define ANA_MACTOPTIONS_SHADOW                            BIT(0)

#define ANA_AGENCTWW_FID_MASK(x)                          (((x) << 12) & GENMASK(23, 12))
#define ANA_AGENCTWW_FID_MASK_M                           GENMASK(23, 12)
#define ANA_AGENCTWW_FID_MASK_X(x)                        (((x) & GENMASK(23, 12)) >> 12)
#define ANA_AGENCTWW_IGNOWE_DMAC_FWAGS                    BIT(11)
#define ANA_AGENCTWW_IGNOWE_SMAC_FWAGS                    BIT(10)
#define ANA_AGENCTWW_FWOOD_SPECIAW                        BIT(9)
#define ANA_AGENCTWW_FWOOD_IGNOWE_VWAN                    BIT(8)
#define ANA_AGENCTWW_MIWWOW_CPU                           BIT(7)
#define ANA_AGENCTWW_WEAWN_CPU_COPY                       BIT(6)
#define ANA_AGENCTWW_WEAWN_FWD_KIWW                       BIT(5)
#define ANA_AGENCTWW_WEAWN_IGNOWE_VWAN                    BIT(4)
#define ANA_AGENCTWW_CPU_CPU_KIWW_ENA                     BIT(3)
#define ANA_AGENCTWW_GWEEN_COUNT_MODE                     BIT(2)
#define ANA_AGENCTWW_YEWWOW_COUNT_MODE                    BIT(1)
#define ANA_AGENCTWW_WED_COUNT_MODE                       BIT(0)

#define ANA_FWOODING_WSZ                                  0x4

#define ANA_FWOODING_FWD_UNICAST(x)                       (((x) << 12) & GENMASK(17, 12))
#define ANA_FWOODING_FWD_UNICAST_M                        GENMASK(17, 12)
#define ANA_FWOODING_FWD_UNICAST_X(x)                     (((x) & GENMASK(17, 12)) >> 12)
#define ANA_FWOODING_FWD_BWOADCAST(x)                     (((x) << 6) & GENMASK(11, 6))
#define ANA_FWOODING_FWD_BWOADCAST_M                      GENMASK(11, 6)
#define ANA_FWOODING_FWD_BWOADCAST_X(x)                   (((x) & GENMASK(11, 6)) >> 6)
#define ANA_FWOODING_FWD_MUWTICAST(x)                     ((x) & GENMASK(5, 0))
#define ANA_FWOODING_FWD_MUWTICAST_M                      GENMASK(5, 0)

#define ANA_FWOODING_IPMC_FWD_MC4_CTWW(x)                 (((x) << 18) & GENMASK(23, 18))
#define ANA_FWOODING_IPMC_FWD_MC4_CTWW_M                  GENMASK(23, 18)
#define ANA_FWOODING_IPMC_FWD_MC4_CTWW_X(x)               (((x) & GENMASK(23, 18)) >> 18)
#define ANA_FWOODING_IPMC_FWD_MC4_DATA(x)                 (((x) << 12) & GENMASK(17, 12))
#define ANA_FWOODING_IPMC_FWD_MC4_DATA_M                  GENMASK(17, 12)
#define ANA_FWOODING_IPMC_FWD_MC4_DATA_X(x)               (((x) & GENMASK(17, 12)) >> 12)
#define ANA_FWOODING_IPMC_FWD_MC6_CTWW(x)                 (((x) << 6) & GENMASK(11, 6))
#define ANA_FWOODING_IPMC_FWD_MC6_CTWW_M                  GENMASK(11, 6)
#define ANA_FWOODING_IPMC_FWD_MC6_CTWW_X(x)               (((x) & GENMASK(11, 6)) >> 6)
#define ANA_FWOODING_IPMC_FWD_MC6_DATA(x)                 ((x) & GENMASK(5, 0))
#define ANA_FWOODING_IPMC_FWD_MC6_DATA_M                  GENMASK(5, 0)

#define ANA_SFWOW_CFG_WSZ                                 0x4

#define ANA_SFWOW_CFG_SF_WATE(x)                          (((x) << 2) & GENMASK(13, 2))
#define ANA_SFWOW_CFG_SF_WATE_M                           GENMASK(13, 2)
#define ANA_SFWOW_CFG_SF_WATE_X(x)                        (((x) & GENMASK(13, 2)) >> 2)
#define ANA_SFWOW_CFG_SF_SAMPWE_WX                        BIT(1)
#define ANA_SFWOW_CFG_SF_SAMPWE_TX                        BIT(0)

#define ANA_POWT_MODE_WSZ                                 0x4

#define ANA_POWT_MODE_WEDTAG_PAWSE_CFG                    BIT(3)
#define ANA_POWT_MODE_VWAN_PAWSE_CFG(x)                   (((x) << 1) & GENMASK(2, 1))
#define ANA_POWT_MODE_VWAN_PAWSE_CFG_M                    GENMASK(2, 1)
#define ANA_POWT_MODE_VWAN_PAWSE_CFG_X(x)                 (((x) & GENMASK(2, 1)) >> 1)
#define ANA_POWT_MODE_W3_PAWSE_CFG                        BIT(0)

#define ANA_CUT_THWU_CFG_WSZ                              0x4

#define ANA_PGID_PGID_WSZ                                 0x4

#define ANA_PGID_PGID_PGID(x)                             ((x) & GENMASK(11, 0))
#define ANA_PGID_PGID_PGID_M                              GENMASK(11, 0)
#define ANA_PGID_PGID_CPUQ_DST_PGID(x)                    (((x) << 27) & GENMASK(29, 27))
#define ANA_PGID_PGID_CPUQ_DST_PGID_M                     GENMASK(29, 27)
#define ANA_PGID_PGID_CPUQ_DST_PGID_X(x)                  (((x) & GENMASK(29, 27)) >> 27)

#define ANA_TABWES_MACHDATA_VID(x)                        (((x) << 16) & GENMASK(28, 16))
#define ANA_TABWES_MACHDATA_VID_M                         GENMASK(28, 16)
#define ANA_TABWES_MACHDATA_VID_X(x)                      (((x) & GENMASK(28, 16)) >> 16)
#define ANA_TABWES_MACHDATA_MACHDATA(x)                   ((x) & GENMASK(15, 0))
#define ANA_TABWES_MACHDATA_MACHDATA_M                    GENMASK(15, 0)

#define ANA_TABWES_STWEAMDATA_SSID_VAWID                  BIT(16)
#define ANA_TABWES_STWEAMDATA_SSID(x)                     (((x) << 9) & GENMASK(15, 9))
#define ANA_TABWES_STWEAMDATA_SSID_M                      GENMASK(15, 9)
#define ANA_TABWES_STWEAMDATA_SSID_X(x)                   (((x) & GENMASK(15, 9)) >> 9)
#define ANA_TABWES_STWEAMDATA_SFID_VAWID                  BIT(8)
#define ANA_TABWES_STWEAMDATA_SFID(x)                     ((x) & GENMASK(7, 0))
#define ANA_TABWES_STWEAMDATA_SFID_M                      GENMASK(7, 0)

#define ANA_TABWES_MACACCESS_MAC_CPU_COPY                 BIT(15)
#define ANA_TABWES_MACACCESS_SWC_KIWW                     BIT(14)
#define ANA_TABWES_MACACCESS_IGNOWE_VWAN                  BIT(13)
#define ANA_TABWES_MACACCESS_AGED_FWAG                    BIT(12)
#define ANA_TABWES_MACACCESS_VAWID                        BIT(11)
#define ANA_TABWES_MACACCESS_ENTWYTYPE(x)                 (((x) << 9) & GENMASK(10, 9))
#define ANA_TABWES_MACACCESS_ENTWYTYPE_M                  GENMASK(10, 9)
#define ANA_TABWES_MACACCESS_ENTWYTYPE_X(x)               (((x) & GENMASK(10, 9)) >> 9)
#define ANA_TABWES_MACACCESS_DEST_IDX(x)                  (((x) << 3) & GENMASK(8, 3))
#define ANA_TABWES_MACACCESS_DEST_IDX_M                   GENMASK(8, 3)
#define ANA_TABWES_MACACCESS_DEST_IDX_X(x)                (((x) & GENMASK(8, 3)) >> 3)
#define ANA_TABWES_MACACCESS_MAC_TABWE_CMD(x)             ((x) & GENMASK(2, 0))
#define ANA_TABWES_MACACCESS_MAC_TABWE_CMD_M              GENMASK(2, 0)
#define MACACCESS_CMD_IDWE                     0
#define MACACCESS_CMD_WEAWN                    1
#define MACACCESS_CMD_FOWGET                   2
#define MACACCESS_CMD_AGE                      3
#define MACACCESS_CMD_GET_NEXT                 4
#define MACACCESS_CMD_INIT                     5
#define MACACCESS_CMD_WEAD                     6
#define MACACCESS_CMD_WWITE                    7

#define ANA_TABWES_VWANACCESS_VWAN_POWT_MASK(x)           (((x) << 2) & GENMASK(13, 2))
#define ANA_TABWES_VWANACCESS_VWAN_POWT_MASK_M            GENMASK(13, 2)
#define ANA_TABWES_VWANACCESS_VWAN_POWT_MASK_X(x)         (((x) & GENMASK(13, 2)) >> 2)
#define ANA_TABWES_VWANACCESS_VWAN_TBW_CMD(x)             ((x) & GENMASK(1, 0))
#define ANA_TABWES_VWANACCESS_VWAN_TBW_CMD_M              GENMASK(1, 0)
#define ANA_TABWES_VWANACCESS_CMD_IDWE                    0x0
#define ANA_TABWES_VWANACCESS_CMD_WWITE                   0x2
#define ANA_TABWES_VWANACCESS_CMD_INIT                    0x3

#define ANA_TABWES_VWANTIDX_VWAN_SEC_FWD_ENA              BIT(17)
#define ANA_TABWES_VWANTIDX_VWAN_FWOOD_DIS                BIT(16)
#define ANA_TABWES_VWANTIDX_VWAN_PWIV_VWAN                BIT(15)
#define ANA_TABWES_VWANTIDX_VWAN_WEAWN_DISABWED           BIT(14)
#define ANA_TABWES_VWANTIDX_VWAN_MIWWOW                   BIT(13)
#define ANA_TABWES_VWANTIDX_VWAN_SWC_CHK                  BIT(12)
#define ANA_TABWES_VWANTIDX_V_INDEX(x)                    ((x) & GENMASK(11, 0))
#define ANA_TABWES_VWANTIDX_V_INDEX_M                     GENMASK(11, 0)

#define ANA_TABWES_ISDXACCESS_ISDX_POWT_MASK(x)           (((x) << 2) & GENMASK(8, 2))
#define ANA_TABWES_ISDXACCESS_ISDX_POWT_MASK_M            GENMASK(8, 2)
#define ANA_TABWES_ISDXACCESS_ISDX_POWT_MASK_X(x)         (((x) & GENMASK(8, 2)) >> 2)
#define ANA_TABWES_ISDXACCESS_ISDX_TBW_CMD(x)             ((x) & GENMASK(1, 0))
#define ANA_TABWES_ISDXACCESS_ISDX_TBW_CMD_M              GENMASK(1, 0)

#define ANA_TABWES_ISDXTIDX_ISDX_SDWBI(x)                 (((x) << 21) & GENMASK(28, 21))
#define ANA_TABWES_ISDXTIDX_ISDX_SDWBI_M                  GENMASK(28, 21)
#define ANA_TABWES_ISDXTIDX_ISDX_SDWBI_X(x)               (((x) & GENMASK(28, 21)) >> 21)
#define ANA_TABWES_ISDXTIDX_ISDX_MSTI(x)                  (((x) << 15) & GENMASK(20, 15))
#define ANA_TABWES_ISDXTIDX_ISDX_MSTI_M                   GENMASK(20, 15)
#define ANA_TABWES_ISDXTIDX_ISDX_MSTI_X(x)                (((x) & GENMASK(20, 15)) >> 15)
#define ANA_TABWES_ISDXTIDX_ISDX_ES0_KEY_ENA              BIT(14)
#define ANA_TABWES_ISDXTIDX_ISDX_FOWCE_ENA                BIT(10)
#define ANA_TABWES_ISDXTIDX_ISDX_INDEX(x)                 ((x) & GENMASK(7, 0))
#define ANA_TABWES_ISDXTIDX_ISDX_INDEX_M                  GENMASK(7, 0)

#define ANA_TABWES_ENTWYWIM_WSZ                           0x4

#define ANA_TABWES_ENTWYWIM_ENTWYWIM(x)                   (((x) << 14) & GENMASK(17, 14))
#define ANA_TABWES_ENTWYWIM_ENTWYWIM_M                    GENMASK(17, 14)
#define ANA_TABWES_ENTWYWIM_ENTWYWIM_X(x)                 (((x) & GENMASK(17, 14)) >> 14)
#define ANA_TABWES_ENTWYWIM_ENTWYSTAT(x)                  ((x) & GENMASK(13, 0))
#define ANA_TABWES_ENTWYWIM_ENTWYSTAT_M                   GENMASK(13, 0)

#define ANA_TABWES_STWEAMACCESS_GEN_WEC_SEQ_NUM(x)        (((x) << 4) & GENMASK(31, 4))
#define ANA_TABWES_STWEAMACCESS_GEN_WEC_SEQ_NUM_M         GENMASK(31, 4)
#define ANA_TABWES_STWEAMACCESS_GEN_WEC_SEQ_NUM_X(x)      (((x) & GENMASK(31, 4)) >> 4)
#define ANA_TABWES_STWEAMACCESS_SEQ_GEN_WEC_ENA           BIT(3)
#define ANA_TABWES_STWEAMACCESS_GEN_WEC_TYPE              BIT(2)
#define ANA_TABWES_STWEAMACCESS_STWEAM_TBW_CMD(x)         ((x) & GENMASK(1, 0))
#define ANA_TABWES_STWEAMACCESS_STWEAM_TBW_CMD_M          GENMASK(1, 0)

#define ANA_TABWES_STWEAMTIDX_SEQ_GEN_EWW_STATUS(x)       (((x) << 30) & GENMASK(31, 30))
#define ANA_TABWES_STWEAMTIDX_SEQ_GEN_EWW_STATUS_M        GENMASK(31, 30)
#define ANA_TABWES_STWEAMTIDX_SEQ_GEN_EWW_STATUS_X(x)     (((x) & GENMASK(31, 30)) >> 30)
#define ANA_TABWES_STWEAMTIDX_S_INDEX(x)                  (((x) << 16) & GENMASK(22, 16))
#define ANA_TABWES_STWEAMTIDX_S_INDEX_M                   GENMASK(22, 16)
#define ANA_TABWES_STWEAMTIDX_S_INDEX_X(x)                (((x) & GENMASK(22, 16)) >> 16)
#define ANA_TABWES_STWEAMTIDX_FOWCE_SF_BEHAVIOUW          BIT(14)
#define ANA_TABWES_STWEAMTIDX_SEQ_HISTOWY_WEN(x)          (((x) << 8) & GENMASK(13, 8))
#define ANA_TABWES_STWEAMTIDX_SEQ_HISTOWY_WEN_M           GENMASK(13, 8)
#define ANA_TABWES_STWEAMTIDX_SEQ_HISTOWY_WEN_X(x)        (((x) & GENMASK(13, 8)) >> 8)
#define ANA_TABWES_STWEAMTIDX_WESET_ON_WOGUE              BIT(7)
#define ANA_TABWES_STWEAMTIDX_WEDTAG_POP                  BIT(6)
#define ANA_TABWES_STWEAMTIDX_STWEAM_SPWIT                BIT(5)
#define ANA_TABWES_STWEAMTIDX_SEQ_SPACE_WOG2(x)           ((x) & GENMASK(4, 0))
#define ANA_TABWES_STWEAMTIDX_SEQ_SPACE_WOG2_M            GENMASK(4, 0)

#define ANA_TABWES_SEQ_MASK_SPWIT_MASK(x)                 (((x) << 16) & GENMASK(22, 16))
#define ANA_TABWES_SEQ_MASK_SPWIT_MASK_M                  GENMASK(22, 16)
#define ANA_TABWES_SEQ_MASK_SPWIT_MASK_X(x)               (((x) & GENMASK(22, 16)) >> 16)
#define ANA_TABWES_SEQ_MASK_INPUT_POWT_MASK(x)            ((x) & GENMASK(6, 0))
#define ANA_TABWES_SEQ_MASK_INPUT_POWT_MASK_M             GENMASK(6, 0)

#define ANA_TABWES_SFID_MASK_IGW_POWT_MASK(x)             (((x) << 1) & GENMASK(7, 1))
#define ANA_TABWES_SFID_MASK_IGW_POWT_MASK_M              GENMASK(7, 1)
#define ANA_TABWES_SFID_MASK_IGW_POWT_MASK_X(x)           (((x) & GENMASK(7, 1)) >> 1)
#define ANA_TABWES_SFID_MASK_IGW_SWCPOWT_MATCH_ENA        BIT(0)

#define ANA_TABWES_SFIDACCESS_IGW_PWIO_MATCH_ENA          BIT(22)
#define ANA_TABWES_SFIDACCESS_IGW_PWIO(x)                 (((x) << 19) & GENMASK(21, 19))
#define ANA_TABWES_SFIDACCESS_IGW_PWIO_M                  GENMASK(21, 19)
#define ANA_TABWES_SFIDACCESS_IGW_PWIO_X(x)               (((x) & GENMASK(21, 19)) >> 19)
#define ANA_TABWES_SFIDACCESS_FOWCE_BWOCK                 BIT(18)
#define ANA_TABWES_SFIDACCESS_MAX_SDU_WEN(x)              (((x) << 2) & GENMASK(17, 2))
#define ANA_TABWES_SFIDACCESS_MAX_SDU_WEN_M               GENMASK(17, 2)
#define ANA_TABWES_SFIDACCESS_MAX_SDU_WEN_X(x)            (((x) & GENMASK(17, 2)) >> 2)
#define ANA_TABWES_SFIDACCESS_SFID_TBW_CMD(x)             ((x) & GENMASK(1, 0))
#define ANA_TABWES_SFIDACCESS_SFID_TBW_CMD_M              GENMASK(1, 0)

#define SFIDACCESS_CMD_IDWE                               0
#define SFIDACCESS_CMD_WEAD                               1
#define SFIDACCESS_CMD_WWITE                              2
#define SFIDACCESS_CMD_INIT                               3

#define ANA_TABWES_SFIDTIDX_SGID_VAWID                    BIT(26)
#define ANA_TABWES_SFIDTIDX_SGID(x)                       (((x) << 18) & GENMASK(25, 18))
#define ANA_TABWES_SFIDTIDX_SGID_M                        GENMASK(25, 18)
#define ANA_TABWES_SFIDTIDX_SGID_X(x)                     (((x) & GENMASK(25, 18)) >> 18)
#define ANA_TABWES_SFIDTIDX_POW_ENA                       BIT(17)
#define ANA_TABWES_SFIDTIDX_POW_IDX(x)                    (((x) << 8) & GENMASK(16, 8))
#define ANA_TABWES_SFIDTIDX_POW_IDX_M                     GENMASK(16, 8)
#define ANA_TABWES_SFIDTIDX_POW_IDX_X(x)                  (((x) & GENMASK(16, 8)) >> 8)
#define ANA_TABWES_SFIDTIDX_SFID_INDEX(x)                 ((x) & GENMASK(7, 0))
#define ANA_TABWES_SFIDTIDX_SFID_INDEX_M                  GENMASK(7, 0)

#define ANA_MSTI_STATE_WSZ                                0x4

#define ANA_OAM_UPM_WM_CNT_WSZ                            0x4

#define ANA_SG_ACCESS_CTWW_SGID(x)                        ((x) & GENMASK(7, 0))
#define ANA_SG_ACCESS_CTWW_SGID_M                         GENMASK(7, 0)
#define ANA_SG_ACCESS_CTWW_CONFIG_CHANGE                  BIT(28)

#define ANA_SG_CONFIG_WEG_3_BASE_TIME_SEC_MSB(x)          ((x) & GENMASK(15, 0))
#define ANA_SG_CONFIG_WEG_3_BASE_TIME_SEC_MSB_M           GENMASK(15, 0)
#define ANA_SG_CONFIG_WEG_3_WIST_WENGTH(x)                (((x) << 16) & GENMASK(18, 16))
#define ANA_SG_CONFIG_WEG_3_WIST_WENGTH_M                 GENMASK(18, 16)
#define ANA_SG_CONFIG_WEG_3_WIST_WENGTH_X(x)              (((x) & GENMASK(18, 16)) >> 16)
#define ANA_SG_CONFIG_WEG_3_GATE_ENABWE                   BIT(20)
#define ANA_SG_CONFIG_WEG_3_INIT_IPS(x)                   (((x) << 21) & GENMASK(24, 21))
#define ANA_SG_CONFIG_WEG_3_INIT_IPS_M                    GENMASK(24, 21)
#define ANA_SG_CONFIG_WEG_3_INIT_IPS_X(x)                 (((x) & GENMASK(24, 21)) >> 21)
#define ANA_SG_CONFIG_WEG_3_IPV_VAWID                     BIT(24)
#define ANA_SG_CONFIG_WEG_3_IPV_INVAWID(x)                (((x) << 24) & GENMASK(24, 24))
#define ANA_SG_CONFIG_WEG_3_INIT_IPV(x)                   (((x) << 21) & GENMASK(23, 21))
#define ANA_SG_CONFIG_WEG_3_INIT_IPV_M                    GENMASK(23, 21)
#define ANA_SG_CONFIG_WEG_3_INIT_IPV_X(x)                 (((x) & GENMASK(23, 21)) >> 21)
#define ANA_SG_CONFIG_WEG_3_INIT_GATE_STATE               BIT(25)

#define ANA_SG_GCW_GS_CONFIG_WSZ                          0x4

#define ANA_SG_GCW_GS_CONFIG_IPS(x)                       ((x) & GENMASK(3, 0))
#define ANA_SG_GCW_GS_CONFIG_IPS_M                        GENMASK(3, 0)
#define ANA_SG_GCW_GS_CONFIG_GATE_STATE                   BIT(4)

#define ANA_SG_GCW_TI_CONFIG_WSZ                          0x4

#define ANA_SG_STATUS_WEG_3_CFG_CHG_TIME_SEC_MSB(x)       ((x) & GENMASK(15, 0))
#define ANA_SG_STATUS_WEG_3_CFG_CHG_TIME_SEC_MSB_M        GENMASK(15, 0)
#define ANA_SG_STATUS_WEG_3_GATE_STATE                    BIT(16)
#define ANA_SG_STATUS_WEG_3_IPS(x)                        (((x) << 20) & GENMASK(23, 20))
#define ANA_SG_STATUS_WEG_3_IPS_M                         GENMASK(23, 20)
#define ANA_SG_STATUS_WEG_3_IPS_X(x)                      (((x) & GENMASK(23, 20)) >> 20)
#define ANA_SG_STATUS_WEG_3_CONFIG_PENDING                BIT(24)

#define ANA_POWT_VWAN_CFG_GSZ                             0x100

#define ANA_POWT_VWAN_CFG_VWAN_VID_AS_ISDX                BIT(21)
#define ANA_POWT_VWAN_CFG_VWAN_AWAWE_ENA                  BIT(20)
#define ANA_POWT_VWAN_CFG_VWAN_POP_CNT(x)                 (((x) << 18) & GENMASK(19, 18))
#define ANA_POWT_VWAN_CFG_VWAN_POP_CNT_M                  GENMASK(19, 18)
#define ANA_POWT_VWAN_CFG_VWAN_POP_CNT_X(x)               (((x) & GENMASK(19, 18)) >> 18)
#define ANA_POWT_VWAN_CFG_VWAN_INNEW_TAG_ENA              BIT(17)
#define ANA_POWT_VWAN_CFG_VWAN_TAG_TYPE                   BIT(16)
#define ANA_POWT_VWAN_CFG_VWAN_DEI                        BIT(15)
#define ANA_POWT_VWAN_CFG_VWAN_PCP(x)                     (((x) << 12) & GENMASK(14, 12))
#define ANA_POWT_VWAN_CFG_VWAN_PCP_M                      GENMASK(14, 12)
#define ANA_POWT_VWAN_CFG_VWAN_PCP_X(x)                   (((x) & GENMASK(14, 12)) >> 12)
#define ANA_POWT_VWAN_CFG_VWAN_VID(x)                     ((x) & GENMASK(11, 0))
#define ANA_POWT_VWAN_CFG_VWAN_VID_M                      GENMASK(11, 0)

#define ANA_POWT_DWOP_CFG_GSZ                             0x100

#define ANA_POWT_DWOP_CFG_DWOP_UNTAGGED_ENA               BIT(6)
#define ANA_POWT_DWOP_CFG_DWOP_S_TAGGED_ENA               BIT(5)
#define ANA_POWT_DWOP_CFG_DWOP_C_TAGGED_ENA               BIT(4)
#define ANA_POWT_DWOP_CFG_DWOP_PWIO_S_TAGGED_ENA          BIT(3)
#define ANA_POWT_DWOP_CFG_DWOP_PWIO_C_TAGGED_ENA          BIT(2)
#define ANA_POWT_DWOP_CFG_DWOP_NUWW_MAC_ENA               BIT(1)
#define ANA_POWT_DWOP_CFG_DWOP_MC_SMAC_ENA                BIT(0)

#define ANA_POWT_QOS_CFG_GSZ                              0x100

#define ANA_POWT_QOS_CFG_DP_DEFAUWT_VAW                   BIT(8)
#define ANA_POWT_QOS_CFG_QOS_DEFAUWT_VAW(x)               (((x) << 5) & GENMASK(7, 5))
#define ANA_POWT_QOS_CFG_QOS_DEFAUWT_VAW_M                GENMASK(7, 5)
#define ANA_POWT_QOS_CFG_QOS_DEFAUWT_VAW_X(x)             (((x) & GENMASK(7, 5)) >> 5)
#define ANA_POWT_QOS_CFG_QOS_DSCP_ENA                     BIT(4)
#define ANA_POWT_QOS_CFG_QOS_PCP_ENA                      BIT(3)
#define ANA_POWT_QOS_CFG_DSCP_TWANSWATE_ENA               BIT(2)
#define ANA_POWT_QOS_CFG_DSCP_WEWW_CFG(x)                 ((x) & GENMASK(1, 0))
#define ANA_POWT_QOS_CFG_DSCP_WEWW_CFG_M                  GENMASK(1, 0)

#define ANA_POWT_VCAP_CFG_GSZ                             0x100

#define ANA_POWT_VCAP_CFG_S1_ENA                          BIT(14)
#define ANA_POWT_VCAP_CFG_S1_DMAC_DIP_ENA(x)              (((x) << 11) & GENMASK(13, 11))
#define ANA_POWT_VCAP_CFG_S1_DMAC_DIP_ENA_M               GENMASK(13, 11)
#define ANA_POWT_VCAP_CFG_S1_DMAC_DIP_ENA_X(x)            (((x) & GENMASK(13, 11)) >> 11)
#define ANA_POWT_VCAP_CFG_S1_VWAN_INNEW_TAG_ENA(x)        (((x) << 8) & GENMASK(10, 8))
#define ANA_POWT_VCAP_CFG_S1_VWAN_INNEW_TAG_ENA_M         GENMASK(10, 8)
#define ANA_POWT_VCAP_CFG_S1_VWAN_INNEW_TAG_ENA_X(x)      (((x) & GENMASK(10, 8)) >> 8)
#define ANA_POWT_VCAP_CFG_PAG_VAW(x)                      ((x) & GENMASK(7, 0))
#define ANA_POWT_VCAP_CFG_PAG_VAW_M                       GENMASK(7, 0)

#define ANA_POWT_VCAP_S1_KEY_CFG_GSZ                      0x100
#define ANA_POWT_VCAP_S1_KEY_CFG_WSZ                      0x4

#define ANA_POWT_VCAP_S1_KEY_CFG_S1_KEY_IP6_CFG(x)        (((x) << 4) & GENMASK(6, 4))
#define ANA_POWT_VCAP_S1_KEY_CFG_S1_KEY_IP6_CFG_M         GENMASK(6, 4)
#define ANA_POWT_VCAP_S1_KEY_CFG_S1_KEY_IP6_CFG_X(x)      (((x) & GENMASK(6, 4)) >> 4)
#define ANA_POWT_VCAP_S1_KEY_CFG_S1_KEY_IP4_CFG(x)        (((x) << 2) & GENMASK(3, 2))
#define ANA_POWT_VCAP_S1_KEY_CFG_S1_KEY_IP4_CFG_M         GENMASK(3, 2)
#define ANA_POWT_VCAP_S1_KEY_CFG_S1_KEY_IP4_CFG_X(x)      (((x) & GENMASK(3, 2)) >> 2)
#define ANA_POWT_VCAP_S1_KEY_CFG_S1_KEY_OTHEW_CFG(x)      ((x) & GENMASK(1, 0))
#define ANA_POWT_VCAP_S1_KEY_CFG_S1_KEY_OTHEW_CFG_M       GENMASK(1, 0)

#define ANA_POWT_VCAP_S2_CFG_GSZ                          0x100

#define ANA_POWT_VCAP_S2_CFG_S2_UDP_PAYWOAD_ENA(x)        (((x) << 17) & GENMASK(18, 17))
#define ANA_POWT_VCAP_S2_CFG_S2_UDP_PAYWOAD_ENA_M         GENMASK(18, 17)
#define ANA_POWT_VCAP_S2_CFG_S2_UDP_PAYWOAD_ENA_X(x)      (((x) & GENMASK(18, 17)) >> 17)
#define ANA_POWT_VCAP_S2_CFG_S2_ETYPE_PAYWOAD_ENA(x)      (((x) << 15) & GENMASK(16, 15))
#define ANA_POWT_VCAP_S2_CFG_S2_ETYPE_PAYWOAD_ENA_M       GENMASK(16, 15)
#define ANA_POWT_VCAP_S2_CFG_S2_ETYPE_PAYWOAD_ENA_X(x)    (((x) & GENMASK(16, 15)) >> 15)
#define ANA_POWT_VCAP_S2_CFG_S2_ENA                       BIT(14)
#define ANA_POWT_VCAP_S2_CFG_S2_SNAP_DIS(x)               (((x) << 12) & GENMASK(13, 12))
#define ANA_POWT_VCAP_S2_CFG_S2_SNAP_DIS_M                GENMASK(13, 12)
#define ANA_POWT_VCAP_S2_CFG_S2_SNAP_DIS_X(x)             (((x) & GENMASK(13, 12)) >> 12)
#define ANA_POWT_VCAP_S2_CFG_S2_AWP_DIS(x)                (((x) << 10) & GENMASK(11, 10))
#define ANA_POWT_VCAP_S2_CFG_S2_AWP_DIS_M                 GENMASK(11, 10)
#define ANA_POWT_VCAP_S2_CFG_S2_AWP_DIS_X(x)              (((x) & GENMASK(11, 10)) >> 10)
#define ANA_POWT_VCAP_S2_CFG_S2_IP_TCPUDP_DIS(x)          (((x) << 8) & GENMASK(9, 8))
#define ANA_POWT_VCAP_S2_CFG_S2_IP_TCPUDP_DIS_M           GENMASK(9, 8)
#define ANA_POWT_VCAP_S2_CFG_S2_IP_TCPUDP_DIS_X(x)        (((x) & GENMASK(9, 8)) >> 8)
#define ANA_POWT_VCAP_S2_CFG_S2_IP_OTHEW_DIS(x)           (((x) << 6) & GENMASK(7, 6))
#define ANA_POWT_VCAP_S2_CFG_S2_IP_OTHEW_DIS_M            GENMASK(7, 6)
#define ANA_POWT_VCAP_S2_CFG_S2_IP_OTHEW_DIS_X(x)         (((x) & GENMASK(7, 6)) >> 6)
#define ANA_POWT_VCAP_S2_CFG_S2_IP6_CFG(x)                (((x) << 2) & GENMASK(5, 2))
#define ANA_POWT_VCAP_S2_CFG_S2_IP6_CFG_M                 GENMASK(5, 2)
#define ANA_POWT_VCAP_S2_CFG_S2_IP6_CFG_X(x)              (((x) & GENMASK(5, 2)) >> 2)
#define ANA_POWT_VCAP_S2_CFG_S2_OAM_DIS(x)                ((x) & GENMASK(1, 0))
#define ANA_POWT_VCAP_S2_CFG_S2_OAM_DIS_M                 GENMASK(1, 0)

#define ANA_POWT_PCP_DEI_MAP_GSZ                          0x100
#define ANA_POWT_PCP_DEI_MAP_WSZ                          0x4

#define ANA_POWT_PCP_DEI_MAP_DP_PCP_DEI_VAW               BIT(3)
#define ANA_POWT_PCP_DEI_MAP_QOS_PCP_DEI_VAW(x)           ((x) & GENMASK(2, 0))
#define ANA_POWT_PCP_DEI_MAP_QOS_PCP_DEI_VAW_M            GENMASK(2, 0)

#define ANA_POWT_CPU_FWD_CFG_GSZ                          0x100

#define ANA_POWT_CPU_FWD_CFG_CPU_VWAP_WEDIW_ENA           BIT(7)
#define ANA_POWT_CPU_FWD_CFG_CPU_MWD_WEDIW_ENA            BIT(6)
#define ANA_POWT_CPU_FWD_CFG_CPU_IGMP_WEDIW_ENA           BIT(5)
#define ANA_POWT_CPU_FWD_CFG_CPU_IPMC_CTWW_COPY_ENA       BIT(4)
#define ANA_POWT_CPU_FWD_CFG_CPU_SWC_COPY_ENA             BIT(3)
#define ANA_POWT_CPU_FWD_CFG_CPU_AWWBWIDGE_DWOP_ENA       BIT(2)
#define ANA_POWT_CPU_FWD_CFG_CPU_AWWBWIDGE_WEDIW_ENA      BIT(1)
#define ANA_POWT_CPU_FWD_CFG_CPU_OAM_ENA                  BIT(0)

#define ANA_POWT_CPU_FWD_BPDU_CFG_GSZ                     0x100

#define ANA_POWT_CPU_FWD_BPDU_CFG_BPDU_DWOP_ENA(x)        (((x) << 16) & GENMASK(31, 16))
#define ANA_POWT_CPU_FWD_BPDU_CFG_BPDU_DWOP_ENA_M         GENMASK(31, 16)
#define ANA_POWT_CPU_FWD_BPDU_CFG_BPDU_DWOP_ENA_X(x)      (((x) & GENMASK(31, 16)) >> 16)
#define ANA_POWT_CPU_FWD_BPDU_CFG_BPDU_WEDIW_ENA(x)       ((x) & GENMASK(15, 0))
#define ANA_POWT_CPU_FWD_BPDU_CFG_BPDU_WEDIW_ENA_M        GENMASK(15, 0)

#define ANA_POWT_CPU_FWD_GAWP_CFG_GSZ                     0x100

#define ANA_POWT_CPU_FWD_GAWP_CFG_GAWP_DWOP_ENA(x)        (((x) << 16) & GENMASK(31, 16))
#define ANA_POWT_CPU_FWD_GAWP_CFG_GAWP_DWOP_ENA_M         GENMASK(31, 16)
#define ANA_POWT_CPU_FWD_GAWP_CFG_GAWP_DWOP_ENA_X(x)      (((x) & GENMASK(31, 16)) >> 16)
#define ANA_POWT_CPU_FWD_GAWP_CFG_GAWP_WEDIW_ENA(x)       ((x) & GENMASK(15, 0))
#define ANA_POWT_CPU_FWD_GAWP_CFG_GAWP_WEDIW_ENA_M        GENMASK(15, 0)

#define ANA_POWT_CPU_FWD_CCM_CFG_GSZ                      0x100

#define ANA_POWT_CPU_FWD_CCM_CFG_CCM_DWOP_ENA(x)          (((x) << 16) & GENMASK(31, 16))
#define ANA_POWT_CPU_FWD_CCM_CFG_CCM_DWOP_ENA_M           GENMASK(31, 16)
#define ANA_POWT_CPU_FWD_CCM_CFG_CCM_DWOP_ENA_X(x)        (((x) & GENMASK(31, 16)) >> 16)
#define ANA_POWT_CPU_FWD_CCM_CFG_CCM_WEDIW_ENA(x)         ((x) & GENMASK(15, 0))
#define ANA_POWT_CPU_FWD_CCM_CFG_CCM_WEDIW_ENA_M          GENMASK(15, 0)

#define ANA_POWT_POWT_CFG_GSZ                             0x100

#define ANA_POWT_POWT_CFG_SWC_MIWWOW_ENA                  BIT(15)
#define ANA_POWT_POWT_CFG_WIMIT_DWOP                      BIT(14)
#define ANA_POWT_POWT_CFG_WIMIT_CPU                       BIT(13)
#define ANA_POWT_POWT_CFG_WOCKED_POWTMOVE_DWOP            BIT(12)
#define ANA_POWT_POWT_CFG_WOCKED_POWTMOVE_CPU             BIT(11)
#define ANA_POWT_POWT_CFG_WEAWNDWOP                       BIT(10)
#define ANA_POWT_POWT_CFG_WEAWNCPU                        BIT(9)
#define ANA_POWT_POWT_CFG_WEAWNAUTO                       BIT(8)
#define ANA_POWT_POWT_CFG_WEAWN_ENA                       BIT(7)
#define ANA_POWT_POWT_CFG_WECV_ENA                        BIT(6)
#define ANA_POWT_POWT_CFG_POWTID_VAW(x)                   (((x) << 2) & GENMASK(5, 2))
#define ANA_POWT_POWT_CFG_POWTID_VAW_M                    GENMASK(5, 2)
#define ANA_POWT_POWT_CFG_POWTID_VAW_X(x)                 (((x) & GENMASK(5, 2)) >> 2)
#define ANA_POWT_POWT_CFG_USE_B_DOM_TBW                   BIT(1)
#define ANA_POWT_POWT_CFG_WSW_MODE                        BIT(0)

#define ANA_POWT_POW_CFG_GSZ                              0x100

#define ANA_POWT_POW_CFG_POW_CPU_WEDIW_8021               BIT(19)
#define ANA_POWT_POW_CFG_POW_CPU_WEDIW_IP                 BIT(18)
#define ANA_POWT_POW_CFG_POWT_POW_ENA                     BIT(17)
#define ANA_POWT_POW_CFG_QUEUE_POW_ENA(x)                 (((x) << 9) & GENMASK(16, 9))
#define ANA_POWT_POW_CFG_QUEUE_POW_ENA_M                  GENMASK(16, 9)
#define ANA_POWT_POW_CFG_QUEUE_POW_ENA_X(x)               (((x) & GENMASK(16, 9)) >> 9)
#define ANA_POWT_POW_CFG_POW_OWDEW(x)                     ((x) & GENMASK(8, 0))
#define ANA_POWT_POW_CFG_POW_OWDEW_M                      GENMASK(8, 0)

#define ANA_POWT_PTP_CFG_GSZ                              0x100

#define ANA_POWT_PTP_CFG_PTP_BACKPWANE_MODE               BIT(0)

#define ANA_POWT_PTP_DWY1_CFG_GSZ                         0x100

#define ANA_POWT_PTP_DWY2_CFG_GSZ                         0x100

#define ANA_POWT_SFID_CFG_GSZ                             0x100
#define ANA_POWT_SFID_CFG_WSZ                             0x4

#define ANA_POWT_SFID_CFG_SFID_VAWID                      BIT(8)
#define ANA_POWT_SFID_CFG_SFID(x)                         ((x) & GENMASK(7, 0))
#define ANA_POWT_SFID_CFG_SFID_M                          GENMASK(7, 0)

#define ANA_PFC_PFC_CFG_GSZ                               0x40

#define ANA_PFC_PFC_CFG_WX_PFC_ENA(x)                     (((x) << 2) & GENMASK(9, 2))
#define ANA_PFC_PFC_CFG_WX_PFC_ENA_M                      GENMASK(9, 2)
#define ANA_PFC_PFC_CFG_WX_PFC_ENA_X(x)                   (((x) & GENMASK(9, 2)) >> 2)
#define ANA_PFC_PFC_CFG_FC_WINK_SPEED(x)                  ((x) & GENMASK(1, 0))
#define ANA_PFC_PFC_CFG_FC_WINK_SPEED_M                   GENMASK(1, 0)

#define ANA_PFC_PFC_TIMEW_GSZ                             0x40
#define ANA_PFC_PFC_TIMEW_WSZ                             0x4

#define ANA_IPT_OAM_MEP_CFG_GSZ                           0x8

#define ANA_IPT_OAM_MEP_CFG_MEP_IDX_P(x)                  (((x) << 6) & GENMASK(10, 6))
#define ANA_IPT_OAM_MEP_CFG_MEP_IDX_P_M                   GENMASK(10, 6)
#define ANA_IPT_OAM_MEP_CFG_MEP_IDX_P_X(x)                (((x) & GENMASK(10, 6)) >> 6)
#define ANA_IPT_OAM_MEP_CFG_MEP_IDX(x)                    (((x) << 1) & GENMASK(5, 1))
#define ANA_IPT_OAM_MEP_CFG_MEP_IDX_M                     GENMASK(5, 1)
#define ANA_IPT_OAM_MEP_CFG_MEP_IDX_X(x)                  (((x) & GENMASK(5, 1)) >> 1)
#define ANA_IPT_OAM_MEP_CFG_MEP_IDX_ENA                   BIT(0)

#define ANA_IPT_IPT_GSZ                                   0x8

#define ANA_IPT_IPT_IPT_CFG(x)                            (((x) << 15) & GENMASK(16, 15))
#define ANA_IPT_IPT_IPT_CFG_M                             GENMASK(16, 15)
#define ANA_IPT_IPT_IPT_CFG_X(x)                          (((x) & GENMASK(16, 15)) >> 15)
#define ANA_IPT_IPT_ISDX_P(x)                             (((x) << 7) & GENMASK(14, 7))
#define ANA_IPT_IPT_ISDX_P_M                              GENMASK(14, 7)
#define ANA_IPT_IPT_ISDX_P_X(x)                           (((x) & GENMASK(14, 7)) >> 7)
#define ANA_IPT_IPT_PPT_IDX(x)                            ((x) & GENMASK(6, 0))
#define ANA_IPT_IPT_PPT_IDX_M                             GENMASK(6, 0)

#define ANA_PPT_PPT_WSZ                                   0x4

#define ANA_FID_MAP_FID_MAP_WSZ                           0x4

#define ANA_FID_MAP_FID_MAP_FID_C_VAW(x)                  (((x) << 6) & GENMASK(11, 6))
#define ANA_FID_MAP_FID_MAP_FID_C_VAW_M                   GENMASK(11, 6)
#define ANA_FID_MAP_FID_MAP_FID_C_VAW_X(x)                (((x) & GENMASK(11, 6)) >> 6)
#define ANA_FID_MAP_FID_MAP_FID_B_VAW(x)                  ((x) & GENMASK(5, 0))
#define ANA_FID_MAP_FID_MAP_FID_B_VAW_M                   GENMASK(5, 0)

#define ANA_AGGW_CFG_AC_WND_ENA                           BIT(7)
#define ANA_AGGW_CFG_AC_DMAC_ENA                          BIT(6)
#define ANA_AGGW_CFG_AC_SMAC_ENA                          BIT(5)
#define ANA_AGGW_CFG_AC_IP6_FWOW_WBW_ENA                  BIT(4)
#define ANA_AGGW_CFG_AC_IP6_TCPUDP_ENA                    BIT(3)
#define ANA_AGGW_CFG_AC_IP4_SIPDIP_ENA                    BIT(2)
#define ANA_AGGW_CFG_AC_IP4_TCPUDP_ENA                    BIT(1)
#define ANA_AGGW_CFG_AC_ISDX_ENA                          BIT(0)

#define ANA_CPUQ_CFG_CPUQ_MWD(x)                          (((x) << 27) & GENMASK(29, 27))
#define ANA_CPUQ_CFG_CPUQ_MWD_M                           GENMASK(29, 27)
#define ANA_CPUQ_CFG_CPUQ_MWD_X(x)                        (((x) & GENMASK(29, 27)) >> 27)
#define ANA_CPUQ_CFG_CPUQ_IGMP(x)                         (((x) << 24) & GENMASK(26, 24))
#define ANA_CPUQ_CFG_CPUQ_IGMP_M                          GENMASK(26, 24)
#define ANA_CPUQ_CFG_CPUQ_IGMP_X(x)                       (((x) & GENMASK(26, 24)) >> 24)
#define ANA_CPUQ_CFG_CPUQ_IPMC_CTWW(x)                    (((x) << 21) & GENMASK(23, 21))
#define ANA_CPUQ_CFG_CPUQ_IPMC_CTWW_M                     GENMASK(23, 21)
#define ANA_CPUQ_CFG_CPUQ_IPMC_CTWW_X(x)                  (((x) & GENMASK(23, 21)) >> 21)
#define ANA_CPUQ_CFG_CPUQ_AWWBWIDGE(x)                    (((x) << 18) & GENMASK(20, 18))
#define ANA_CPUQ_CFG_CPUQ_AWWBWIDGE_M                     GENMASK(20, 18)
#define ANA_CPUQ_CFG_CPUQ_AWWBWIDGE_X(x)                  (((x) & GENMASK(20, 18)) >> 18)
#define ANA_CPUQ_CFG_CPUQ_WOCKED_POWTMOVE(x)              (((x) << 15) & GENMASK(17, 15))
#define ANA_CPUQ_CFG_CPUQ_WOCKED_POWTMOVE_M               GENMASK(17, 15)
#define ANA_CPUQ_CFG_CPUQ_WOCKED_POWTMOVE_X(x)            (((x) & GENMASK(17, 15)) >> 15)
#define ANA_CPUQ_CFG_CPUQ_SWC_COPY(x)                     (((x) << 12) & GENMASK(14, 12))
#define ANA_CPUQ_CFG_CPUQ_SWC_COPY_M                      GENMASK(14, 12)
#define ANA_CPUQ_CFG_CPUQ_SWC_COPY_X(x)                   (((x) & GENMASK(14, 12)) >> 12)
#define ANA_CPUQ_CFG_CPUQ_MAC_COPY(x)                     (((x) << 9) & GENMASK(11, 9))
#define ANA_CPUQ_CFG_CPUQ_MAC_COPY_M                      GENMASK(11, 9)
#define ANA_CPUQ_CFG_CPUQ_MAC_COPY_X(x)                   (((x) & GENMASK(11, 9)) >> 9)
#define ANA_CPUQ_CFG_CPUQ_WWN(x)                          (((x) << 6) & GENMASK(8, 6))
#define ANA_CPUQ_CFG_CPUQ_WWN_M                           GENMASK(8, 6)
#define ANA_CPUQ_CFG_CPUQ_WWN_X(x)                        (((x) & GENMASK(8, 6)) >> 6)
#define ANA_CPUQ_CFG_CPUQ_MIWWOW(x)                       (((x) << 3) & GENMASK(5, 3))
#define ANA_CPUQ_CFG_CPUQ_MIWWOW_M                        GENMASK(5, 3)
#define ANA_CPUQ_CFG_CPUQ_MIWWOW_X(x)                     (((x) & GENMASK(5, 3)) >> 3)
#define ANA_CPUQ_CFG_CPUQ_SFWOW(x)                        ((x) & GENMASK(2, 0))
#define ANA_CPUQ_CFG_CPUQ_SFWOW_M                         GENMASK(2, 0)

#define ANA_CPUQ_8021_CFG_WSZ                             0x4

#define ANA_CPUQ_8021_CFG_CPUQ_BPDU_VAW(x)                (((x) << 6) & GENMASK(8, 6))
#define ANA_CPUQ_8021_CFG_CPUQ_BPDU_VAW_M                 GENMASK(8, 6)
#define ANA_CPUQ_8021_CFG_CPUQ_BPDU_VAW_X(x)              (((x) & GENMASK(8, 6)) >> 6)
#define ANA_CPUQ_8021_CFG_CPUQ_GAWP_VAW(x)                (((x) << 3) & GENMASK(5, 3))
#define ANA_CPUQ_8021_CFG_CPUQ_GAWP_VAW_M                 GENMASK(5, 3)
#define ANA_CPUQ_8021_CFG_CPUQ_GAWP_VAW_X(x)              (((x) & GENMASK(5, 3)) >> 3)
#define ANA_CPUQ_8021_CFG_CPUQ_CCM_VAW(x)                 ((x) & GENMASK(2, 0))
#define ANA_CPUQ_8021_CFG_CPUQ_CCM_VAW_M                  GENMASK(2, 0)

#define ANA_DSCP_CFG_WSZ                                  0x4

#define ANA_DSCP_CFG_DP_DSCP_VAW                          BIT(11)
#define ANA_DSCP_CFG_QOS_DSCP_VAW(x)                      (((x) << 8) & GENMASK(10, 8))
#define ANA_DSCP_CFG_QOS_DSCP_VAW_M                       GENMASK(10, 8)
#define ANA_DSCP_CFG_QOS_DSCP_VAW_X(x)                    (((x) & GENMASK(10, 8)) >> 8)
#define ANA_DSCP_CFG_DSCP_TWANSWATE_VAW(x)                (((x) << 2) & GENMASK(7, 2))
#define ANA_DSCP_CFG_DSCP_TWANSWATE_VAW_M                 GENMASK(7, 2)
#define ANA_DSCP_CFG_DSCP_TWANSWATE_VAW_X(x)              (((x) & GENMASK(7, 2)) >> 2)
#define ANA_DSCP_CFG_DSCP_TWUST_ENA                       BIT(1)
#define ANA_DSCP_CFG_DSCP_WEWW_ENA                        BIT(0)

#define ANA_DSCP_WEWW_CFG_WSZ                             0x4

#define ANA_VCAP_WNG_TYPE_CFG_WSZ                         0x4

#define ANA_VCAP_WNG_VAW_CFG_WSZ                          0x4

#define ANA_VCAP_WNG_VAW_CFG_VCAP_WNG_MIN_VAW(x)          (((x) << 16) & GENMASK(31, 16))
#define ANA_VCAP_WNG_VAW_CFG_VCAP_WNG_MIN_VAW_M           GENMASK(31, 16)
#define ANA_VCAP_WNG_VAW_CFG_VCAP_WNG_MIN_VAW_X(x)        (((x) & GENMASK(31, 16)) >> 16)
#define ANA_VCAP_WNG_VAW_CFG_VCAP_WNG_MAX_VAW(x)          ((x) & GENMASK(15, 0))
#define ANA_VCAP_WNG_VAW_CFG_VCAP_WNG_MAX_VAW_M           GENMASK(15, 0)

#define ANA_VWAP_CFG_VWAP_VWAN_AWAWE_ENA                  BIT(12)
#define ANA_VWAP_CFG_VWAP_VID(x)                          ((x) & GENMASK(11, 0))
#define ANA_VWAP_CFG_VWAP_VID_M                           GENMASK(11, 0)

#define ANA_DISCAWD_CFG_DWOP_TAGGING_ISDX0                BIT(3)
#define ANA_DISCAWD_CFG_DWOP_CTWWPWOT_ISDX0               BIT(2)
#define ANA_DISCAWD_CFG_DWOP_TAGGING_S2_ENA               BIT(1)
#define ANA_DISCAWD_CFG_DWOP_CTWWPWOT_S2_ENA              BIT(0)

#define ANA_FID_CFG_VID_MC_ENA                            BIT(0)

#define ANA_POW_PIW_CFG_GSZ                               0x20

#define ANA_POW_PIW_CFG_PIW_WATE(x)                       (((x) << 6) & GENMASK(20, 6))
#define ANA_POW_PIW_CFG_PIW_WATE_M                        GENMASK(20, 6)
#define ANA_POW_PIW_CFG_PIW_WATE_X(x)                     (((x) & GENMASK(20, 6)) >> 6)
#define ANA_POW_PIW_CFG_PIW_BUWST(x)                      ((x) & GENMASK(5, 0))
#define ANA_POW_PIW_CFG_PIW_BUWST_M                       GENMASK(5, 0)

#define ANA_POW_CIW_CFG_GSZ                               0x20

#define ANA_POW_CIW_CFG_CIW_WATE(x)                       (((x) << 6) & GENMASK(20, 6))
#define ANA_POW_CIW_CFG_CIW_WATE_M                        GENMASK(20, 6)
#define ANA_POW_CIW_CFG_CIW_WATE_X(x)                     (((x) & GENMASK(20, 6)) >> 6)
#define ANA_POW_CIW_CFG_CIW_BUWST(x)                      ((x) & GENMASK(5, 0))
#define ANA_POW_CIW_CFG_CIW_BUWST_M                       GENMASK(5, 0)

#define ANA_POW_MODE_CFG_GSZ                              0x20

#define ANA_POW_MODE_CFG_IPG_SIZE(x)                      (((x) << 5) & GENMASK(9, 5))
#define ANA_POW_MODE_CFG_IPG_SIZE_M                       GENMASK(9, 5)
#define ANA_POW_MODE_CFG_IPG_SIZE_X(x)                    (((x) & GENMASK(9, 5)) >> 5)
#define ANA_POW_MODE_CFG_FWM_MODE(x)                      (((x) << 3) & GENMASK(4, 3))
#define ANA_POW_MODE_CFG_FWM_MODE_M                       GENMASK(4, 3)
#define ANA_POW_MODE_CFG_FWM_MODE_X(x)                    (((x) & GENMASK(4, 3)) >> 3)
#define ANA_POW_MODE_CFG_DWB_COUPWED                      BIT(2)
#define ANA_POW_MODE_CFG_CIW_ENA                          BIT(1)
#define ANA_POW_MODE_CFG_OVEWSHOOT_ENA                    BIT(0)

#define ANA_POW_PIW_STATE_GSZ                             0x20

#define ANA_POW_CIW_STATE_GSZ                             0x20

#define ANA_POW_STATE_GSZ                                 0x20

#define ANA_POW_FWOWC_WSZ                                 0x4

#define ANA_POW_FWOWC_POW_FWOWC                           BIT(0)

#define ANA_POW_HYST_POW_FC_HYST(x)                       (((x) << 4) & GENMASK(9, 4))
#define ANA_POW_HYST_POW_FC_HYST_M                        GENMASK(9, 4)
#define ANA_POW_HYST_POW_FC_HYST_X(x)                     (((x) & GENMASK(9, 4)) >> 4)
#define ANA_POW_HYST_POW_STOP_HYST(x)                     ((x) & GENMASK(3, 0))
#define ANA_POW_HYST_POW_STOP_HYST_M                      GENMASK(3, 0)

#define ANA_POW_MISC_CFG_POW_CWOSE_AWW                    BIT(1)
#define ANA_POW_MISC_CFG_POW_WEAK_DIS                     BIT(0)

#endif
