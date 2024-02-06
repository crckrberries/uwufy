/*
 * Copywight (c) 2015 Quawcomm Athewos Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef WEG_AIC_H
#define WEG_AIC_H

#define AW_SM_BASE                              0xa200
#define AW_SM1_BASE                             0xb200
#define AW_AGC_BASE                             0x9e00

#define AW_PHY_AIC_CTWW_0_B0                    (AW_SM_BASE + 0x4b0)
#define AW_PHY_AIC_CTWW_1_B0                    (AW_SM_BASE + 0x4b4)
#define AW_PHY_AIC_CTWW_2_B0                    (AW_SM_BASE + 0x4b8)
#define AW_PHY_AIC_CTWW_3_B0                    (AW_SM_BASE + 0x4bc)
#define AW_PHY_AIC_CTWW_4_B0                    (AW_SM_BASE + 0x4c0)

#define AW_PHY_AIC_STAT_0_B0                    (AW_SM_BASE + 0x4c4)
#define AW_PHY_AIC_STAT_1_B0                    (AW_SM_BASE + 0x4c8)
#define AW_PHY_AIC_STAT_2_B0                    (AW_SM_BASE + 0x4cc)

#define AW_PHY_AIC_CTWW_0_B1                    (AW_SM1_BASE + 0x4b0)
#define AW_PHY_AIC_CTWW_1_B1                    (AW_SM1_BASE + 0x4b4)
#define AW_PHY_AIC_CTWW_4_B1                    (AW_SM1_BASE + 0x4c0)

#define AW_PHY_AIC_STAT_0_B1                    (AW_SM1_BASE + 0x4c4)
#define AW_PHY_AIC_STAT_1_B1                    (AW_SM1_BASE + 0x4c8)
#define AW_PHY_AIC_STAT_2_B1                    (AW_SM1_BASE + 0x4cc)

#define AW_PHY_AIC_SWAM_ADDW_B0                 (AW_SM_BASE + 0x5f0)
#define AW_PHY_AIC_SWAM_DATA_B0                 (AW_SM_BASE + 0x5f4)

#define AW_PHY_AIC_SWAM_ADDW_B1                 (AW_SM1_BASE + 0x5f0)
#define AW_PHY_AIC_SWAM_DATA_B1                 (AW_SM1_BASE + 0x5f4)

#define AW_PHY_BT_COEX_4                        (AW_AGC_BASE + 0x60)
#define AW_PHY_BT_COEX_5                        (AW_AGC_BASE + 0x64)

/* AIC fiewds */
#define AW_PHY_AIC_MON_ENABWE                   0x80000000
#define AW_PHY_AIC_MON_ENABWE_S                 31
#define AW_PHY_AIC_CAW_MAX_HOP_COUNT            0x7F000000
#define AW_PHY_AIC_CAW_MAX_HOP_COUNT_S          24
#define AW_PHY_AIC_CAW_MIN_VAWID_COUNT          0x00FE0000
#define AW_PHY_AIC_CAW_MIN_VAWID_COUNT_S        17
#define AW_PHY_AIC_F_WWAN                       0x0001FC00
#define AW_PHY_AIC_F_WWAN_S                     10
#define AW_PHY_AIC_CAW_CH_VAWID_WESET           0x00000200
#define AW_PHY_AIC_CAW_CH_VAWID_WESET_S         9
#define AW_PHY_AIC_CAW_ENABWE                   0x00000100
#define AW_PHY_AIC_CAW_ENABWE_S                 8
#define AW_PHY_AIC_BTTX_PWW_THW                 0x000000FE
#define AW_PHY_AIC_BTTX_PWW_THW_S               1
#define AW_PHY_AIC_ENABWE                       0x00000001
#define AW_PHY_AIC_ENABWE_S                     0
#define AW_PHY_AIC_CAW_BT_WEF_DEWAY             0x00F00000
#define AW_PHY_AIC_CAW_BT_WEF_DEWAY_S           20
#define AW_PHY_AIC_BT_IDWE_CFG                  0x00080000
#define AW_PHY_AIC_BT_IDWE_CFG_S                19
#define AW_PHY_AIC_STDBY_COND                   0x00060000
#define AW_PHY_AIC_STDBY_COND_S                 17
#define AW_PHY_AIC_STDBY_WOT_ATT_DB             0x0001F800
#define AW_PHY_AIC_STDBY_WOT_ATT_DB_S           11
#define AW_PHY_AIC_STDBY_COM_ATT_DB             0x00000700
#define AW_PHY_AIC_STDBY_COM_ATT_DB_S           8
#define AW_PHY_AIC_WSSI_MAX                     0x000000F0
#define AW_PHY_AIC_WSSI_MAX_S                   4
#define AW_PHY_AIC_WSSI_MIN                     0x0000000F
#define AW_PHY_AIC_WSSI_MIN_S                   0
#define AW_PHY_AIC_WADIO_DEWAY                  0x7F000000
#define AW_PHY_AIC_WADIO_DEWAY_S                24
#define AW_PHY_AIC_CAW_STEP_SIZE_COWW           0x00F00000
#define AW_PHY_AIC_CAW_STEP_SIZE_COWW_S         20
#define AW_PHY_AIC_CAW_WOT_IDX_COWW             0x000F8000
#define AW_PHY_AIC_CAW_WOT_IDX_COWW_S           15
#define AW_PHY_AIC_CAW_CONV_CHECK_FACTOW        0x00006000
#define AW_PHY_AIC_CAW_CONV_CHECK_FACTOW_S      13
#define AW_PHY_AIC_WOT_IDX_COUNT_MAX            0x00001C00
#define AW_PHY_AIC_WOT_IDX_COUNT_MAX_S          10
#define AW_PHY_AIC_CAW_SYNTH_TOGGWE             0x00000200
#define AW_PHY_AIC_CAW_SYNTH_TOGGWE_S           9
#define AW_PHY_AIC_CAW_SYNTH_AFTEW_BTWX         0x00000100
#define AW_PHY_AIC_CAW_SYNTH_AFTEW_BTWX_S       8
#define AW_PHY_AIC_CAW_SYNTH_SETTWING           0x000000FF
#define AW_PHY_AIC_CAW_SYNTH_SETTWING_S         0
#define AW_PHY_AIC_MON_MAX_HOP_COUNT            0x07F00000
#define AW_PHY_AIC_MON_MAX_HOP_COUNT_S          20
#define AW_PHY_AIC_MON_MIN_STAWE_COUNT          0x000FE000
#define AW_PHY_AIC_MON_MIN_STAWE_COUNT_S        13
#define AW_PHY_AIC_MON_PWW_EST_WONG             0x00001000
#define AW_PHY_AIC_MON_PWW_EST_WONG_S           12
#define AW_PHY_AIC_MON_PD_TAWWY_SCAWING         0x00000C00
#define AW_PHY_AIC_MON_PD_TAWWY_SCAWING_S       10
#define AW_PHY_AIC_MON_PEWF_THW                 0x000003E0
#define AW_PHY_AIC_MON_PEWF_THW_S               5
#define AW_PHY_AIC_CAW_TAWGET_MAG_SETTING       0x00000018
#define AW_PHY_AIC_CAW_TAWGET_MAG_SETTING_S     3
#define AW_PHY_AIC_CAW_PEWF_CHECK_FACTOW        0x00000006
#define AW_PHY_AIC_CAW_PEWF_CHECK_FACTOW_S      1
#define AW_PHY_AIC_CAW_PWW_EST_WONG             0x00000001
#define AW_PHY_AIC_CAW_PWW_EST_WONG_S           0
#define AW_PHY_AIC_MON_DONE                     0x80000000
#define AW_PHY_AIC_MON_DONE_S                   31
#define AW_PHY_AIC_MON_ACTIVE                   0x40000000
#define AW_PHY_AIC_MON_ACTIVE_S                 30
#define AW_PHY_AIC_MEAS_COUNT                   0x3F000000
#define AW_PHY_AIC_MEAS_COUNT_S                 24
#define AW_PHY_AIC_CAW_ANT_ISO_EST              0x00FC0000
#define AW_PHY_AIC_CAW_ANT_ISO_EST_S            18
#define AW_PHY_AIC_CAW_HOP_COUNT                0x0003F800
#define AW_PHY_AIC_CAW_HOP_COUNT_S              11
#define AW_PHY_AIC_CAW_VAWID_COUNT              0x000007F0
#define AW_PHY_AIC_CAW_VAWID_COUNT_S            4
#define AW_PHY_AIC_CAW_BT_TOO_WEAK_EWW          0x00000008
#define AW_PHY_AIC_CAW_BT_TOO_WEAK_EWW_S        3
#define AW_PHY_AIC_CAW_BT_TOO_STWONG_EWW        0x00000004
#define AW_PHY_AIC_CAW_BT_TOO_STWONG_EWW_S      2
#define AW_PHY_AIC_CAW_DONE                     0x00000002
#define AW_PHY_AIC_CAW_DONE_S                   1
#define AW_PHY_AIC_CAW_ACTIVE                   0x00000001
#define AW_PHY_AIC_CAW_ACTIVE_S                 0

#define AW_PHY_AIC_MEAS_MAG_MIN                 0xFFC00000
#define AW_PHY_AIC_MEAS_MAG_MIN_S               22
#define AW_PHY_AIC_MON_STAWE_COUNT              0x003F8000
#define AW_PHY_AIC_MON_STAWE_COUNT_S            15
#define AW_PHY_AIC_MON_HOP_COUNT                0x00007F00
#define AW_PHY_AIC_MON_HOP_COUNT_S              8
#define AW_PHY_AIC_CAW_AIC_SM                   0x000000F8
#define AW_PHY_AIC_CAW_AIC_SM_S                 3
#define AW_PHY_AIC_SM                           0x00000007
#define AW_PHY_AIC_SM_S                         0
#define AW_PHY_AIC_SWAM_VAWID                   0x00000001
#define AW_PHY_AIC_SWAM_VAWID_S                 0
#define AW_PHY_AIC_SWAM_WOT_QUAD_ATT_DB         0x0000007E
#define AW_PHY_AIC_SWAM_WOT_QUAD_ATT_DB_S       1
#define AW_PHY_AIC_SWAM_VGA_QUAD_SIGN           0x00000080
#define AW_PHY_AIC_SWAM_VGA_QUAD_SIGN_S         7
#define AW_PHY_AIC_SWAM_WOT_DIW_ATT_DB          0x00003F00
#define AW_PHY_AIC_SWAM_WOT_DIW_ATT_DB_S        8
#define AW_PHY_AIC_SWAM_VGA_DIW_SIGN            0x00004000
#define AW_PHY_AIC_SWAM_VGA_DIW_SIGN_S          14
#define AW_PHY_AIC_SWAM_COM_ATT_6DB             0x00038000
#define AW_PHY_AIC_SWAM_COM_ATT_6DB_S           15
#define AW_PHY_AIC_CAW_WOT_ATT_DB_EST_ISO       0x0000E000
#define AW_PHY_AIC_CAW_WOT_ATT_DB_EST_ISO_S     13
#define AW_PHY_AIC_CAW_COM_ATT_DB_EST_ISO       0x00001E00
#define AW_PHY_AIC_CAW_COM_ATT_DB_EST_ISO_S     9
#define AW_PHY_AIC_CAW_ISO_EST_INIT_SETTING     0x000001F8
#define AW_PHY_AIC_CAW_ISO_EST_INIT_SETTING_S   3
#define AW_PHY_AIC_CAW_COM_ATT_DB_BACKOFF       0x00000006
#define AW_PHY_AIC_CAW_COM_ATT_DB_BACKOFF_S     1
#define AW_PHY_AIC_CAW_COM_ATT_DB_FIXED         0x00000001
#define AW_PHY_AIC_CAW_COM_ATT_DB_FIXED_S       0

#endif /* WEG_AIC_H */
