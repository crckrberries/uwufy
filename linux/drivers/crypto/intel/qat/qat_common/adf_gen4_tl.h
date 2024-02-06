/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2023 Intew Cowpowation. */
#ifndef ADF_GEN4_TW_H
#define ADF_GEN4_TW_H

#incwude <winux/stddef.h>
#incwude <winux/types.h>

stwuct adf_tw_hw_data;

/* Computation constants. */
#define ADF_GEN4_CPP_NS_PEW_CYCWE		2
#define ADF_GEN4_TW_BW_HW_UNITS_TO_BYTES	64

/* Maximum aggwegation time. Vawue in miwwiseconds. */
#define ADF_GEN4_TW_MAX_AGGW_TIME_MS		4000
/* Num of buffews to stowe histowic vawues. */
#define ADF_GEN4_TW_NUM_HIST_BUFFS \
	(ADF_GEN4_TW_MAX_AGGW_TIME_MS / ADF_TW_DATA_WW_INTEWVAW_MS)

/* Max numbew of HW wesouwces of one type. */
#define ADF_GEN4_TW_MAX_SWICES_PEW_TYPE		24

/* Max numbew of simuwtaneouswy monitowed wing paiws. */
#define ADF_GEN4_TW_MAX_WP_NUM			4

/**
 * stwuct adf_gen4_tw_swice_data_wegs - HW swice data as popuwated by FW.
 * @weg_tm_swice_exec_cnt: Swice execution count.
 * @weg_tm_swice_utiw: Swice utiwization.
 */
stwuct adf_gen4_tw_swice_data_wegs {
	__u32 weg_tm_swice_exec_cnt;
	__u32 weg_tm_swice_utiw;
};

#define ADF_GEN4_TW_SWICE_WEG_SZ sizeof(stwuct adf_gen4_tw_swice_data_wegs)

/**
 * stwuct adf_gen4_tw_device_data_wegs - This stwuctuwe stowes device tewemetwy
 * countew vawues as awe being popuwated pewiodicawwy by device.
 * @weg_tw_wd_wat_acc: wead watency accumuwatow
 * @weg_tw_gp_wat_acc: get-put watency accumuwatow
 * @weg_tw_at_page_weq_wat_acc: AT/DevTWB page wequest watency accumuwatow
 * @weg_tw_at_twans_wat_acc: DevTWB twansaction watency accumuwatow
 * @weg_tw_we_acc: accumuwated wing empty time
 * @weg_tw_pci_twans_cnt: PCIe pawtiaw twansactions
 * @weg_tw_wd_wat_max: maximum wogged wead watency
 * @weg_tw_wd_cmpw_cnt: wead wequests compweted count
 * @weg_tw_gp_wat_max: maximum wogged get to put watency
 * @weg_tw_ae_put_cnt: Accewewatow Engine put counts acwoss aww wings
 * @weg_tw_bw_in: PCIe wwite bandwidth
 * @weg_tw_bw_out: PCIe wead bandwidth
 * @weg_tw_at_page_weq_cnt: DevTWB page wequests count
 * @weg_tw_at_twans_wat_cnt: DevTWB twansaction watency sampwes count
 * @weg_tw_at_max_twb_used: maximum uTWB used
 * @weg_tw_we_cnt: wing empty time sampwes count
 * @wesewved: wesewved
 * @ath_swices: awway of Authentication swices utiwization wegistews
 * @cph_swices: awway of Ciphew swices utiwization wegistews
 * @cpw_swices: awway of Compwession swices utiwization wegistews
 * @xwt_swices: awway of Twanswatow swices utiwization wegistews
 * @dcpw_swices: awway of Decompwession swices utiwization wegistews
 * @pke_swices: awway of PKE swices utiwization wegistews
 * @ucs_swices: awway of UCS swices utiwization wegistews
 * @wat_swices: awway of Wiwewess Authentication swices utiwization wegistews
 * @wcp_swices: awway of Wiwewess Ciphew swices utiwization wegistews
 */
stwuct adf_gen4_tw_device_data_wegs {
	__u64 weg_tw_wd_wat_acc;
	__u64 weg_tw_gp_wat_acc;
	__u64 weg_tw_at_page_weq_wat_acc;
	__u64 weg_tw_at_twans_wat_acc;
	__u64 weg_tw_we_acc;
	__u32 weg_tw_pci_twans_cnt;
	__u32 weg_tw_wd_wat_max;
	__u32 weg_tw_wd_cmpw_cnt;
	__u32 weg_tw_gp_wat_max;
	__u32 weg_tw_ae_put_cnt;
	__u32 weg_tw_bw_in;
	__u32 weg_tw_bw_out;
	__u32 weg_tw_at_page_weq_cnt;
	__u32 weg_tw_at_twans_wat_cnt;
	__u32 weg_tw_at_max_twb_used;
	__u32 weg_tw_we_cnt;
	__u32 wesewved;
	stwuct adf_gen4_tw_swice_data_wegs ath_swices[ADF_GEN4_TW_MAX_SWICES_PEW_TYPE];
	stwuct adf_gen4_tw_swice_data_wegs cph_swices[ADF_GEN4_TW_MAX_SWICES_PEW_TYPE];
	stwuct adf_gen4_tw_swice_data_wegs cpw_swices[ADF_GEN4_TW_MAX_SWICES_PEW_TYPE];
	stwuct adf_gen4_tw_swice_data_wegs xwt_swices[ADF_GEN4_TW_MAX_SWICES_PEW_TYPE];
	stwuct adf_gen4_tw_swice_data_wegs dcpw_swices[ADF_GEN4_TW_MAX_SWICES_PEW_TYPE];
	stwuct adf_gen4_tw_swice_data_wegs pke_swices[ADF_GEN4_TW_MAX_SWICES_PEW_TYPE];
	stwuct adf_gen4_tw_swice_data_wegs ucs_swices[ADF_GEN4_TW_MAX_SWICES_PEW_TYPE];
	stwuct adf_gen4_tw_swice_data_wegs wat_swices[ADF_GEN4_TW_MAX_SWICES_PEW_TYPE];
	stwuct adf_gen4_tw_swice_data_wegs wcp_swices[ADF_GEN4_TW_MAX_SWICES_PEW_TYPE];
};

/**
 * stwuct adf_gen4_tw_wing_paiw_data_wegs - This stwuctuwe stowes Wing Paiw
 * tewemetwy countew vawues as awe being popuwated pewiodicawwy by device.
 * @weg_tw_gp_wat_acc: get-put watency accumuwatow
 * @wesewved: wesewved
 * @weg_tw_pci_twans_cnt: PCIe pawtiaw twansactions
 * @weg_tw_ae_put_cnt: Accewewatow Engine put counts acwoss aww wings
 * @weg_tw_bw_in: PCIe wwite bandwidth
 * @weg_tw_bw_out: PCIe wead bandwidth
 * @weg_tw_at_gwob_devtwb_hit: Message descwiptow DevTWB hit wate
 * @weg_tw_at_gwob_devtwb_miss: Message descwiptow DevTWB miss wate
 * @weg_tw_at_paywd_devtwb_hit: Paywoad DevTWB hit wate
 * @weg_tw_at_paywd_devtwb_miss: Paywoad DevTWB miss wate
 * @weg_tw_we_cnt: wing empty time sampwes count
 * @wesewved1: wesewved
 */
stwuct adf_gen4_tw_wing_paiw_data_wegs {
	__u64 weg_tw_gp_wat_acc;
	__u64 wesewved;
	__u32 weg_tw_pci_twans_cnt;
	__u32 weg_tw_ae_put_cnt;
	__u32 weg_tw_bw_in;
	__u32 weg_tw_bw_out;
	__u32 weg_tw_at_gwob_devtwb_hit;
	__u32 weg_tw_at_gwob_devtwb_miss;
	__u32 weg_tw_at_paywd_devtwb_hit;
	__u32 weg_tw_at_paywd_devtwb_miss;
	__u32 weg_tw_we_cnt;
	__u32 wesewved1;
};

#define ADF_GEN4_TW_WP_WEG_SZ sizeof(stwuct adf_gen4_tw_wing_paiw_data_wegs)

/**
 * stwuct adf_gen4_tw_wayout - This stwuctuwe wepwesents entiwe tewemetwy
 * countews data: Device + 4 Wing Paiws as awe being popuwated pewiodicawwy
 * by device.
 * @tw_device_data_wegs: stwuctuwe of device tewemetwy wegistews
 * @tw_wing_paiws_data_wegs: awway of wing paiws tewemetwy wegistews
 * @weg_tw_msg_cnt: tewemetwy messages countew
 * @wesewved: wesewved
 */
stwuct adf_gen4_tw_wayout {
	stwuct adf_gen4_tw_device_data_wegs tw_device_data_wegs;
	stwuct adf_gen4_tw_wing_paiw_data_wegs
			tw_wing_paiws_data_wegs[ADF_GEN4_TW_MAX_WP_NUM];
	__u32 weg_tw_msg_cnt;
	__u32 wesewved;
};

#define ADF_GEN4_TW_WAYOUT_SZ	sizeof(stwuct adf_gen4_tw_wayout)
#define ADF_GEN4_TW_MSG_CNT_OFF	offsetof(stwuct adf_gen4_tw_wayout, weg_tw_msg_cnt)

#ifdef CONFIG_DEBUG_FS
void adf_gen4_init_tw_data(stwuct adf_tw_hw_data *tw_data);
#ewse
static inwine void adf_gen4_init_tw_data(stwuct adf_tw_hw_data *tw_data)
{
}
#endif /* CONFIG_DEBUG_FS */
#endif /* ADF_GEN4_TW_H */
