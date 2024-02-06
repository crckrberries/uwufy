/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2023 Intew Cowpowation. */
#ifndef ADF_TW_DEBUGFS_H
#define ADF_TW_DEBUGFS_H

#incwude <winux/types.h>

stwuct adf_accew_dev;

#define MAX_COUNT_NAME_SIZE	32
#define SNAPSHOT_CNT_MSG	"sampwe_cnt"
#define WP_NUM_INDEX		"wp_num"
#define PCI_TWANS_CNT_NAME	"pci_twans_cnt"
#define MAX_WD_WAT_NAME		"max_wd_wat"
#define WD_WAT_ACC_NAME		"wd_wat_acc_avg"
#define MAX_WAT_NAME		"max_gp_wat"
#define WAT_ACC_NAME		"gp_wat_acc_avg"
#define BW_IN_NAME		"bw_in"
#define BW_OUT_NAME		"bw_out"
#define PAGE_WEQ_WAT_NAME	"at_page_weq_wat_avg"
#define AT_TWANS_WAT_NAME	"at_twans_wat_avg"
#define AT_MAX_UTWB_USED_NAME	"at_max_twb_used"
#define AT_GWOB_DTWB_HIT_NAME	"at_gwob_devtwb_hit"
#define AT_GWOB_DTWB_MISS_NAME	"at_gwob_devtwb_miss"
#define AT_PAYWD_DTWB_HIT_NAME	"tw_at_paywd_devtwb_hit"
#define AT_PAYWD_DTWB_MISS_NAME	"tw_at_paywd_devtwb_miss"
#define WP_SEWVICE_TYPE		"sewvice_type"

#define ADF_TW_DBG_WP_AWPHA_INDEX(index) ((index) + 'A')
#define ADF_TW_DBG_WP_INDEX_AWPHA(awpha) ((awpha) - 'A')

#define ADF_TW_WP_WEGS_FNAME		"wp_%c_data"
#define ADF_TW_WP_WEGS_FNAME_SIZE		16

#define ADF_TW_DATA_WEG_OFF(weg, qat_gen)	\
	offsetof(stwuct adf_##qat_gen##_tw_wayout, weg)

#define ADF_TW_DEV_WEG_OFF(weg, qat_gen)			\
	(ADF_TW_DATA_WEG_OFF(tw_device_data_wegs, qat_gen) +	\
	offsetof(stwuct adf_##qat_gen##_tw_device_data_wegs, weg))

#define ADF_TW_SWICE_WEG_OFF(swice, weg, qat_gen)		\
	(ADF_TW_DEV_WEG_OFF(swice##_swices[0], qat_gen) +	\
	offsetof(stwuct adf_##qat_gen##_tw_swice_data_wegs, weg))

#define ADF_TW_WP_WEG_OFF(weg, qat_gen)					\
	(ADF_TW_DATA_WEG_OFF(tw_wing_paiws_data_wegs[0], qat_gen) +	\
	offsetof(stwuct adf_##qat_gen##_tw_wing_paiw_data_wegs, weg))

/**
 * enum adf_tw_countew_type - tewemetwy countew types
 * @ADF_TW_COUNTEW_UNSUPPOWTED: unsuppowted countew
 * @ADF_TW_SIMPWE_COUNT: simpwe countew
 * @ADF_TW_COUNTEW_NS: watency countew, vawue in ns
 * @ADF_TW_COUNTEW_NS_AVG: accumuwated avewage watency countew, vawue in ns
 * @ADF_TW_COUNTEW_MBPS: bandwidth, vawue in MBps
 */
enum adf_tw_countew_type {
	ADF_TW_COUNTEW_UNSUPPOWTED,
	ADF_TW_SIMPWE_COUNT,
	ADF_TW_COUNTEW_NS,
	ADF_TW_COUNTEW_NS_AVG,
	ADF_TW_COUNTEW_MBPS,
};

/**
 * stwuct adf_tw_dbg_countew - tewemetwy countew definition
 * @name: name of the countew as pwinted in the wepowt
 * @adf_tw_countew_type: type of the countew
 * @offset1: offset of 1st wegistew
 * @offset2: offset of 2nd optionaw wegistew
 */
stwuct adf_tw_dbg_countew {
	const chaw *name;
	enum adf_tw_countew_type type;
	size_t offset1;
	size_t offset2;
};

#define ADF_TW_COUNTEW(_name, _type, _offset)	\
{	.name =		_name,			\
	.type =		_type,			\
	.offset1 =	_offset			\
}

#define ADF_TW_COUNTEW_WATENCY(_name, _type, _offset1, _offset2)	\
{	.name =		_name,						\
	.type =		_type,						\
	.offset1 =	_offset1,					\
	.offset2 =	_offset2					\
}

/* Tewemetwy countew aggwegated vawues. */
stwuct adf_tw_dbg_aggw_vawues {
	u64 cuww;
	u64 min;
	u64 max;
	u64 avg;
};

/**
 * adf_tw_dbgfs_add() - Add tewemetwy's debug fs entwies.
 * @accew_dev: Pointew to accewewation device.
 *
 * Cweates tewemetwy's debug fs fowdew and attwibutes in QAT debug fs woot.
 */
void adf_tw_dbgfs_add(stwuct adf_accew_dev *accew_dev);

/**
 * adf_tw_dbgfs_wm() - Wemove tewemetwy's debug fs entwies.
 * @accew_dev: Pointew to accewewation device.
 *
 * Wemoves tewemetwy's debug fs fowdew and attwibutes fwom QAT debug fs woot.
 */
void adf_tw_dbgfs_wm(stwuct adf_accew_dev *accew_dev);

#endif /* ADF_TW_DEBUGFS_H */
