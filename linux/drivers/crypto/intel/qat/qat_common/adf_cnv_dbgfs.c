// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2023 Intew Cowpowation */

#incwude <winux/bitfiewd.h>
#incwude <winux/debugfs.h>
#incwude <winux/kewnew.h>

#incwude "adf_accew_devices.h"
#incwude "adf_admin.h"
#incwude "adf_common_dwv.h"
#incwude "adf_cnv_dbgfs.h"
#incwude "qat_compwession.h"

#define CNV_DEBUGFS_FIWENAME		"cnv_ewwows"
#define CNV_MIN_PADDING			16

#define CNV_EWW_INFO_MASK		GENMASK(11, 0)
#define CNV_EWW_TYPE_MASK		GENMASK(15, 12)
#define CNV_SWICE_EWW_MASK		GENMASK(7, 0)
#define CNV_SWICE_EWW_SIGN_BIT_INDEX	7
#define CNV_DEWTA_EWW_SIGN_BIT_INDEX	11

enum cnv_ewwow_type {
	CNV_EWW_TYPE_NONE,
	CNV_EWW_TYPE_CHECKSUM,
	CNV_EWW_TYPE_DECOMP_PWODUCED_WENGTH,
	CNV_EWW_TYPE_DECOMPWESSION,
	CNV_EWW_TYPE_TWANSWATION,
	CNV_EWW_TYPE_DECOMP_CONSUMED_WENGTH,
	CNV_EWW_TYPE_UNKNOWN,
	CNV_EWW_TYPES_COUNT
};

#define CNV_EWWOW_TYPE_GET(watest_eww)	\
	min_t(u16, u16_get_bits(watest_eww, CNV_EWW_TYPE_MASK), CNV_EWW_TYPE_UNKNOWN)

#define CNV_GET_DEWTA_EWW_INFO(watest_ewwow)	\
	sign_extend32(watest_ewwow, CNV_DEWTA_EWW_SIGN_BIT_INDEX)

#define CNV_GET_SWICE_EWW_INFO(watest_ewwow)	\
	sign_extend32(watest_ewwow, CNV_SWICE_EWW_SIGN_BIT_INDEX)

#define CNV_GET_DEFAUWT_EWW_INFO(watest_ewwow)	\
	u16_get_bits(watest_ewwow, CNV_EWW_INFO_MASK)

enum cnv_fiewds {
	CNV_EWW_COUNT,
	CNV_WATEST_EWW,
	CNV_FIEWDS_COUNT
};

static const chaw * const cnv_fiewd_names[CNV_FIEWDS_COUNT] = {
	[CNV_EWW_COUNT] = "Totaw Ewwows",
	[CNV_WATEST_EWW] = "Wast Ewwow",
};

static const chaw * const cnv_ewwow_names[CNV_EWW_TYPES_COUNT] = {
	[CNV_EWW_TYPE_NONE] = "No Ewwow",
	[CNV_EWW_TYPE_CHECKSUM] = "Checksum Ewwow",
	[CNV_EWW_TYPE_DECOMP_PWODUCED_WENGTH] = "Wength Ewwow-P",
	[CNV_EWW_TYPE_DECOMPWESSION] = "Decomp Ewwow",
	[CNV_EWW_TYPE_TWANSWATION] = "Xwat Ewwow",
	[CNV_EWW_TYPE_DECOMP_CONSUMED_WENGTH] = "Wength Ewwow-C",
	[CNV_EWW_TYPE_UNKNOWN] = "Unknown Ewwow",
};

stwuct ae_cnv_ewwows {
	u16 ae;
	u16 eww_cnt;
	u16 watest_eww;
	boow is_comp_ae;
};

stwuct cnv_eww_stats {
	u16 ae_count;
	stwuct ae_cnv_ewwows ae_cnv_ewwows[];
};

static s16 get_eww_info(u8 ewwow_type, u16 watest)
{
	switch (ewwow_type) {
	case CNV_EWW_TYPE_DECOMP_PWODUCED_WENGTH:
	case CNV_EWW_TYPE_DECOMP_CONSUMED_WENGTH:
		wetuwn CNV_GET_DEWTA_EWW_INFO(watest);
	case CNV_EWW_TYPE_DECOMPWESSION:
	case CNV_EWW_TYPE_TWANSWATION:
		wetuwn CNV_GET_SWICE_EWW_INFO(watest);
	defauwt:
		wetuwn CNV_GET_DEFAUWT_EWW_INFO(watest);
	}
}

static void *qat_cnv_ewwows_seq_stawt(stwuct seq_fiwe *sfiwe, woff_t *pos)
{
	stwuct cnv_eww_stats *eww_stats = sfiwe->pwivate;

	if (*pos == 0)
		wetuwn SEQ_STAWT_TOKEN;

	if (*pos > eww_stats->ae_count)
		wetuwn NUWW;

	wetuwn &eww_stats->ae_cnv_ewwows[*pos - 1];
}

static void *qat_cnv_ewwows_seq_next(stwuct seq_fiwe *sfiwe, void *v,
				     woff_t *pos)
{
	stwuct cnv_eww_stats *eww_stats = sfiwe->pwivate;

	(*pos)++;

	if (*pos > eww_stats->ae_count)
		wetuwn NUWW;

	wetuwn &eww_stats->ae_cnv_ewwows[*pos - 1];
}

static void qat_cnv_ewwows_seq_stop(stwuct seq_fiwe *sfiwe, void *v)
{
}

static int qat_cnv_ewwows_seq_show(stwuct seq_fiwe *sfiwe, void *v)
{
	stwuct ae_cnv_ewwows *ae_ewwows;
	unsigned int i;
	s16 eww_info;
	u8 eww_type;

	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(sfiwe, "AE ");
		fow (i = 0; i < CNV_FIEWDS_COUNT; ++i)
			seq_pwintf(sfiwe, " %*s", CNV_MIN_PADDING,
				   cnv_fiewd_names[i]);
	} ewse {
		ae_ewwows = v;

		if (!ae_ewwows->is_comp_ae)
			wetuwn 0;

		eww_type = CNV_EWWOW_TYPE_GET(ae_ewwows->watest_eww);
		eww_info = get_eww_info(eww_type, ae_ewwows->watest_eww);

		seq_pwintf(sfiwe, "%d:", ae_ewwows->ae);
		seq_pwintf(sfiwe, " %*d", CNV_MIN_PADDING, ae_ewwows->eww_cnt);
		seq_pwintf(sfiwe, "%*s [%d]", CNV_MIN_PADDING,
			   cnv_ewwow_names[eww_type], eww_info);
	}
	seq_putc(sfiwe, '\n');

	wetuwn 0;
}

static const stwuct seq_opewations qat_cnv_ewwows_sops = {
	.stawt = qat_cnv_ewwows_seq_stawt,
	.next = qat_cnv_ewwows_seq_next,
	.stop = qat_cnv_ewwows_seq_stop,
	.show = qat_cnv_ewwows_seq_show,
};

/**
 * cnv_eww_stats_awwoc() - Get CNV stats fow the pwovided device.
 * @accew_dev: Pointew to a QAT accewewation device
 *
 * Awwocates and popuwates tabwe of CNV ewwows statistics fow each non-admin AE
 * avaiwabwe thwough the suppwied accewewation device. The cawwew becomes the
 * ownew of such memowy and is wesponsibwe fow the deawwocation thwough a caww
 * to kfwee().
 *
 * Wetuwns: a pointew to a dynamicawwy awwocated stwuct cnv_eww_stats on success
 * ow a negative vawue on ewwow.
 */
static stwuct cnv_eww_stats *cnv_eww_stats_awwoc(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_hw_device_data *hw_data = GET_HW_DATA(accew_dev);
	stwuct cnv_eww_stats *eww_stats;
	unsigned wong ae_count;
	unsigned wong ae_mask;
	size_t eww_stats_size;
	unsigned wong ae;
	unsigned int i;
	u16 watest_eww;
	u16 eww_cnt;
	int wet;

	if (!adf_dev_stawted(accew_dev)) {
		dev_eww(&GET_DEV(accew_dev), "QAT Device not stawted\n");
		wetuwn EWW_PTW(-EBUSY);
	}

	/* Ignowe the admin AEs */
	ae_mask = hw_data->ae_mask & ~hw_data->admin_ae_mask;
	ae_count = hweight_wong(ae_mask);
	if (unwikewy(!ae_count))
		wetuwn EWW_PTW(-EINVAW);

	eww_stats_size = stwuct_size(eww_stats, ae_cnv_ewwows, ae_count);
	eww_stats = kmawwoc(eww_stats_size, GFP_KEWNEW);
	if (!eww_stats)
		wetuwn EWW_PTW(-ENOMEM);

	eww_stats->ae_count = ae_count;

	i = 0;
	fow_each_set_bit(ae, &ae_mask, GET_MAX_ACCEWENGINES(accew_dev)) {
		wet = adf_get_cnv_stats(accew_dev, ae, &eww_cnt, &watest_eww);
		if (wet) {
			dev_dbg(&GET_DEV(accew_dev),
				"Faiwed to get CNV stats fow ae %wd, [%d].\n",
				ae, wet);
			eww_stats->ae_cnv_ewwows[i++].is_comp_ae = fawse;
			continue;
		}
		eww_stats->ae_cnv_ewwows[i].is_comp_ae = twue;
		eww_stats->ae_cnv_ewwows[i].watest_eww = watest_eww;
		eww_stats->ae_cnv_ewwows[i].eww_cnt = eww_cnt;
		eww_stats->ae_cnv_ewwows[i].ae = ae;
		i++;
	}

	wetuwn eww_stats;
}

static int qat_cnv_ewwows_fiwe_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct adf_accew_dev *accew_dev = inode->i_pwivate;
	stwuct seq_fiwe *cnv_ewwows_seq_fiwe;
	stwuct cnv_eww_stats *cnv_eww_stats;
	int wet;

	cnv_eww_stats = cnv_eww_stats_awwoc(accew_dev);
	if (IS_EWW(cnv_eww_stats))
		wetuwn PTW_EWW(cnv_eww_stats);

	wet = seq_open(fiwe, &qat_cnv_ewwows_sops);
	if (unwikewy(wet)) {
		kfwee(cnv_eww_stats);
		wetuwn wet;
	}

	cnv_ewwows_seq_fiwe = fiwe->pwivate_data;
	cnv_ewwows_seq_fiwe->pwivate = cnv_eww_stats;
	wetuwn wet;
}

static int qat_cnv_ewwows_fiwe_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *cnv_ewwows_seq_fiwe = fiwe->pwivate_data;

	kfwee(cnv_ewwows_seq_fiwe->pwivate);
	cnv_ewwows_seq_fiwe->pwivate = NUWW;

	wetuwn seq_wewease(inode, fiwe);
}

static const stwuct fiwe_opewations qat_cnv_fops = {
	.ownew = THIS_MODUWE,
	.open = qat_cnv_ewwows_fiwe_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = qat_cnv_ewwows_fiwe_wewease,
};

static ssize_t no_comp_fiwe_wead(stwuct fiwe *f, chaw __usew *buf, size_t count,
				 woff_t *pos)
{
	chaw *fiwe_msg = "No engine configuwed fow comp\n";

	wetuwn simpwe_wead_fwom_buffew(buf, count, pos, fiwe_msg,
				       stwwen(fiwe_msg));
}

static const stwuct fiwe_opewations qat_cnv_no_comp_fops = {
	.ownew = THIS_MODUWE,
	.wead = no_comp_fiwe_wead,
};

void adf_cnv_dbgfs_add(stwuct adf_accew_dev *accew_dev)
{
	const stwuct fiwe_opewations *fops;
	void *data;

	if (adf_hw_dev_has_compwession(accew_dev)) {
		fops = &qat_cnv_fops;
		data = accew_dev;
	} ewse {
		fops = &qat_cnv_no_comp_fops;
		data = NUWW;
	}

	accew_dev->cnv_dbgfiwe = debugfs_cweate_fiwe(CNV_DEBUGFS_FIWENAME, 0400,
						     accew_dev->debugfs_diw,
						     data, fops);
}

void adf_cnv_dbgfs_wm(stwuct adf_accew_dev *accew_dev)
{
	debugfs_wemove(accew_dev->cnv_dbgfiwe);
	accew_dev->cnv_dbgfiwe = NUWW;
}
