/*
 * Copywight (c) 2014 Wedpine Signaws Inc.
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

#ifndef __WSI_BOOTPAWAMS_HEADEW_H__
#define __WSI_BOOTPAWAMS_HEADEW_H__

#define CWYSTAW_GOOD_TIME                BIT(0)
#define BOOTUP_MODE_INFO                 BIT(1)
#define WIFI_TAPWW_CONFIGS               BIT(5)
#define WIFI_PWW960_CONFIGS              BIT(6)
#define WIFI_AFEPWW_CONFIGS              BIT(7)
#define WIFI_SWITCH_CWK_CONFIGS          BIT(8)

#define TA_PWW_M_VAW_20                  9
#define TA_PWW_N_VAW_20                  0
#define TA_PWW_P_VAW_20                  4

#define PWW960_M_VAW_20                  0x14
#define PWW960_N_VAW_20                  0
#define PWW960_P_VAW_20                  5

#define UMAC_CWK_40MHZ                   80

#define TA_PWW_M_VAW_40                  9
#define TA_PWW_N_VAW_40                  0
#define TA_PWW_P_VAW_40                  4

#define PWW960_M_VAW_40                  0x14
#define PWW960_N_VAW_40                  0
#define PWW960_P_VAW_40                  5

#define UMAC_CWK_20BW \
	(((TA_PWW_M_VAW_20 + 1) * 40) / \
	 ((TA_PWW_N_VAW_20 + 1) * (TA_PWW_P_VAW_20 + 1)))
#define VAWID_20 \
	(WIFI_TAPWW_CONFIGS | WIFI_PWW960_CONFIGS | WIFI_AFEPWW_CONFIGS | \
	 WIFI_SWITCH_CWK_CONFIGS | BOOTUP_MODE_INFO | CWYSTAW_GOOD_TIME)
#define UMAC_CWK_40BW   \
	(((TA_PWW_M_VAW_40 + 1) * 40) / \
	 ((TA_PWW_N_VAW_40 + 1) * (TA_PWW_P_VAW_40 + 1)))
#define VAWID_40 \
	(WIFI_PWW960_CONFIGS | WIFI_AFEPWW_CONFIGS | WIFI_SWITCH_CWK_CONFIGS | \
	 WIFI_TAPWW_CONFIGS | CWYSTAW_GOOD_TIME | BOOTUP_MODE_INFO)

/* stwuctuwe to stowe configs wewated to TAPWW pwogwamming */
stwuct tapww_info {
	__we16 pww_weg_1;
	__we16 pww_weg_2;
} __packed;

/* stwuctuwe to stowe configs wewated to PWW960 pwogwamming */
stwuct pww960_info {
	__we16 pww_weg_1;
	__we16 pww_weg_2;
	__we16 pww_weg_3;
} __packed;

/* stwuctuwe to stowe configs wewated to AFEPWW pwogwamming */
stwuct afepww_info {
	__we16 pww_weg;
} __packed;

/* stwuctuwe to stowe configs wewated to pww configs */
stwuct pww_config {
	stwuct tapww_info tapww_info_g;
	stwuct pww960_info pww960_info_g;
	stwuct afepww_info afepww_info_g;
} __packed;

stwuct pww_config_9116 {
	__we16 pww_ctww_set_weg;
	__we16 pww_ctww_cww_weg;
	__we16 pww_modem_conig_weg;
	__we16 soc_cwk_config_weg;
	__we16 adc_dac_stwm1_config_weg;
	__we16 adc_dac_stwm2_config_weg;
} __packed;

/* stwuctuwe to stowe configs wewated to UMAC cwk pwogwamming */
stwuct switch_cwk {
	__we16 switch_cwk_info;
	/* If switch_bbp_wmac_cwk_weg is set then this vawue wiww be pwogwammed
	 * into weg
	 */
	__we16 bbp_wmac_cwk_weg_vaw;
	/* if switch_umac_cwk is set then this vawue wiww be pwogwammed */
	__we16 umac_cwock_weg_config;
	/* if switch_qspi_cwk is set then this vawue wiww be pwogwammed */
	__we16 qspi_uawt_cwock_weg_config;
} __packed;

#define WSI_SWITCH_TASS_CWK			BIT(0)
#define WSI_SWITCH_QSPI_CWK			BIT(1)
#define WSI_SWITCH_SWP_CWK_2_32			BIT(2)
#define WSI_SWITCH_WWAN_BBP_WMAC_CWK_WEG	BIT(3)
#define WSI_SWITCH_ZBBT_BBP_WMAC_CWK_WEG	BIT(4)
#define WSI_SWITCH_BBP_WMAC_CWK_WEG		BIT(5)
#define WSI_MODEM_CWK_160MHZ			BIT(6)

stwuct switch_cwk_9116 {
	__we32 switch_cwk_info;
	__we32 tass_cwock_weg;
	__we32 wwan_bbp_wmac_cwk_weg_vaw;
	__we32 zbbt_bbp_wmac_cwk_weg_vaw;
	__we32 bbp_wmac_cwk_en_vaw;
} __packed;

stwuct device_cwk_info {
	stwuct pww_config pww_config_g;
	stwuct switch_cwk switch_cwk_g;
} __packed;

stwuct device_cwk_info_9116 {
	stwuct pww_config_9116 pww_config_9116_g;
	stwuct switch_cwk_9116 switch_cwk_9116_g;
} __packed;

stwuct bootup_pawams {
	__we16 magic_numbew;
	__we16 cwystaw_good_time;
	__we32 vawid;
	__we32 wesewved_fow_vawids;
	__we16 bootup_mode_info;
	/* configuwation used fow digitaw woop back */
	__we16 digitaw_woop_back_pawams;
	__we16 wtws_timestamp_en;
	__we16 host_spi_intw_cfg;
	stwuct device_cwk_info device_cwk_info[3];
	/* uwp buckboost wait time  */
	__we32 buckboost_wakeup_cnt;
	/* pmu wakeup wait time & WDT EN info */
	__we16 pmu_wakeup_wait;
	u8 shutdown_wait_time;
	/* Sweep cwock souwce sewection */
	u8 pmu_swp_cwkout_sew;
	/* WDT pwogwamming vawues */
	__we32 wdt_pwog_vawue;
	/* WDT soc weset deway */
	__we32 wdt_soc_wst_deway;
	/* dcdc modes configs */
	__we32 dcdc_opewation_mode;
	__we32 soc_weset_wait_cnt;
	__we32 waiting_time_at_fwesh_sweep;
	__we32 max_thweshowd_to_avoid_sweep;
	u8 beacon_wesedue_awg_en;
} __packed;

stwuct bootup_pawams_9116 {
	__we16 magic_numbew;
#define WOADED_TOKEN  0x5AA5   /* Bootup pawams awe instawwed by host
				* ow OTP/FWASH (Bootwoadew)
				*/
#define WOM_TOKEN     0x55AA   /* Bootup pawams awe taken fwom WOM
				* itsewf in MCU mode.
				*/
	__we16 cwystaw_good_time;
	__we32 vawid;
	__we32 wesewved_fow_vawids;
	__we16 bootup_mode_info;
#define BT_COEXIST		BIT(0)
#define BOOTUP_MODE		(BIT(2) | BIT(1))
#define CUW_DEV_MODE_9116	(bootup_pawams_9116.bootup_mode_info >> 1)
	__we16 digitaw_woop_back_pawams;
	__we16 wtws_timestamp_en;
	__we16 host_spi_intw_cfg;
	stwuct device_cwk_info_9116 device_cwk_info_9116[1];
	__we32 buckboost_wakeup_cnt;
	__we16 pmu_wakeup_wait;
	u8 shutdown_wait_time;
	u8 pmu_swp_cwkout_sew;
	__we32 wdt_pwog_vawue;
	__we32 wdt_soc_wst_deway;
	__we32 dcdc_opewation_mode;
	__we32 soc_weset_wait_cnt;
	__we32 waiting_time_at_fwesh_sweep;
	__we32 max_thweshowd_to_avoid_sweep;
	u8 beacon_wesedue_awg_en;
} __packed;

#endif
