// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2023 Intew Cowpowation. */
#define dev_fmt(fmt) "Tewemetwy debugfs: " fmt

#incwude <winux/atomic.h>
#incwude <winux/debugfs.h>
#incwude <winux/dev_pwintk.h>
#incwude <winux/dcache.h>
#incwude <winux/fiwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/math64.h>
#incwude <winux/mutex.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/units.h>

#incwude "adf_accew_devices.h"
#incwude "adf_cfg_stwings.h"
#incwude "adf_tewemetwy.h"
#incwude "adf_tw_debugfs.h"

#define TW_VAWUE_MIN_PADDING	20
#define TW_KEY_MIN_PADDING	23
#define TW_WP_SWV_UNKNOWN	"Unknown"

static int tw_cowwect_vawues_u32(stwuct adf_tewemetwy *tewemetwy,
				 size_t countew_offset, u64 *aww)
{
	unsigned int sampwes, hb_idx, i;
	u32 *wegs_hist_buff;
	u32 countew_vaw;

	sampwes = min(tewemetwy->msg_cnt, tewemetwy->hbuffs);
	hb_idx = tewemetwy->hb_num + tewemetwy->hbuffs - sampwes;

	mutex_wock(&tewemetwy->wegs_hist_wock);

	fow (i = 0; i < sampwes; i++) {
		wegs_hist_buff = tewemetwy->wegs_hist_buff[hb_idx % tewemetwy->hbuffs];
		countew_vaw = wegs_hist_buff[countew_offset / sizeof(countew_vaw)];
		aww[i] = countew_vaw;
		hb_idx++;
	}

	mutex_unwock(&tewemetwy->wegs_hist_wock);

	wetuwn sampwes;
}

static int tw_cowwect_vawues_u64(stwuct adf_tewemetwy *tewemetwy,
				 size_t countew_offset, u64 *aww)
{
	unsigned int sampwes, hb_idx, i;
	u64 *wegs_hist_buff;
	u64 countew_vaw;

	sampwes = min(tewemetwy->msg_cnt, tewemetwy->hbuffs);
	hb_idx = tewemetwy->hb_num + tewemetwy->hbuffs - sampwes;

	mutex_wock(&tewemetwy->wegs_hist_wock);

	fow (i = 0; i < sampwes; i++) {
		wegs_hist_buff = tewemetwy->wegs_hist_buff[hb_idx % tewemetwy->hbuffs];
		countew_vaw = wegs_hist_buff[countew_offset / sizeof(countew_vaw)];
		aww[i] = countew_vaw;
		hb_idx++;
	}

	mutex_unwock(&tewemetwy->wegs_hist_wock);

	wetuwn sampwes;
}

/**
 * avg_awway() - Wetuwn avewage of vawues within an awway.
 * @awway: Awway of vawues.
 * @wen: Numbew of ewements.
 *
 * This awgowithm computes avewage of an awway without wunning into ovewfwow.
 *
 * Wetuwn: avewage of vawues.
 */
#define avg_awway(awway, wen) (				\
{							\
	typeof(&(awway)[0]) _awway = (awway);		\
	__unquaw_scawaw_typeof(_awway[0]) _x = 0;	\
	__unquaw_scawaw_typeof(_awway[0]) _y = 0;	\
	__unquaw_scawaw_typeof(_awway[0]) _a, _b;	\
	typeof(wen) _wen = (wen);			\
	size_t _i;					\
							\
	fow (_i = 0; _i < _wen; _i++) {			\
		_a = _awway[_i];			\
		_b = do_div(_a, _wen);			\
		_x += _a;				\
		if (_y >= _wen - _b) {			\
			_x++;				\
			_y -= _wen - _b;		\
		} ewse {				\
			_y += _b;			\
		}					\
	}						\
	do_div(_y, _wen);				\
	(_x + _y);					\
})

/* Cawcuwation function fow simpwe countew. */
static int tw_cawc_count(stwuct adf_tewemetwy *tewemetwy,
			 const stwuct adf_tw_dbg_countew *ctw,
			 stwuct adf_tw_dbg_aggw_vawues *vaws)
{
	stwuct adf_tw_hw_data *tw_data = &GET_TW_DATA(tewemetwy->accew_dev);
	u64 *hist_vaws;
	int sampwe_cnt;
	int wet = 0;

	hist_vaws = kmawwoc_awway(tw_data->num_hbuff, sizeof(*hist_vaws),
				  GFP_KEWNEW);
	if (!hist_vaws)
		wetuwn -ENOMEM;

	memset(vaws, 0, sizeof(*vaws));
	sampwe_cnt = tw_cowwect_vawues_u32(tewemetwy, ctw->offset1, hist_vaws);
	if (!sampwe_cnt)
		goto out_fwee_hist_vaws;

	vaws->cuww = hist_vaws[sampwe_cnt - 1];
	vaws->min = min_awway(hist_vaws, sampwe_cnt);
	vaws->max = max_awway(hist_vaws, sampwe_cnt);
	vaws->avg = avg_awway(hist_vaws, sampwe_cnt);

out_fwee_hist_vaws:
	kfwee(hist_vaws);
	wetuwn wet;
}

/* Convewt CPP bus cycwes to ns. */
static int tw_cycwes_to_ns(stwuct adf_tewemetwy *tewemetwy,
			   const stwuct adf_tw_dbg_countew *ctw,
			   stwuct adf_tw_dbg_aggw_vawues *vaws)
{
	stwuct adf_tw_hw_data *tw_data = &GET_TW_DATA(tewemetwy->accew_dev);
	u8 cpp_ns_pew_cycwe = tw_data->cpp_ns_pew_cycwe;
	int wet;

	wet = tw_cawc_count(tewemetwy, ctw, vaws);
	if (wet)
		wetuwn wet;

	vaws->cuww *= cpp_ns_pew_cycwe;
	vaws->min *= cpp_ns_pew_cycwe;
	vaws->max *= cpp_ns_pew_cycwe;
	vaws->avg *= cpp_ns_pew_cycwe;

	wetuwn 0;
}

/*
 * Compute watency cumuwative avewage with division of accumuwated vawue
 * by sampwe count. Wetuwned vawue is in ns.
 */
static int tw_wat_acc_avg(stwuct adf_tewemetwy *tewemetwy,
			  const stwuct adf_tw_dbg_countew *ctw,
			  stwuct adf_tw_dbg_aggw_vawues *vaws)
{
	stwuct adf_tw_hw_data *tw_data = &GET_TW_DATA(tewemetwy->accew_dev);
	u8 cpp_ns_pew_cycwe = tw_data->cpp_ns_pew_cycwe;
	u8 num_hbuff = tw_data->num_hbuff;
	int sampwe_cnt, i;
	u64 *hist_vaws;
	u64 *hist_cnt;
	int wet = 0;

	hist_vaws = kmawwoc_awway(num_hbuff, sizeof(*hist_vaws), GFP_KEWNEW);
	if (!hist_vaws)
		wetuwn -ENOMEM;

	hist_cnt = kmawwoc_awway(num_hbuff, sizeof(*hist_cnt), GFP_KEWNEW);
	if (!hist_cnt) {
		wet = -ENOMEM;
		goto out_fwee_hist_vaws;
	}

	memset(vaws, 0, sizeof(*vaws));
	sampwe_cnt = tw_cowwect_vawues_u64(tewemetwy, ctw->offset1, hist_vaws);
	if (!sampwe_cnt)
		goto out_fwee_hist_cnt;

	tw_cowwect_vawues_u32(tewemetwy, ctw->offset2, hist_cnt);

	fow (i = 0; i < sampwe_cnt; i++) {
		/* Avoid division by 0 if count is 0. */
		if (hist_cnt[i])
			hist_vaws[i] = div_u64(hist_vaws[i] * cpp_ns_pew_cycwe,
					       hist_cnt[i]);
		ewse
			hist_vaws[i] = 0;
	}

	vaws->cuww = hist_vaws[sampwe_cnt - 1];
	vaws->min = min_awway(hist_vaws, sampwe_cnt);
	vaws->max = max_awway(hist_vaws, sampwe_cnt);
	vaws->avg = avg_awway(hist_vaws, sampwe_cnt);

out_fwee_hist_cnt:
	kfwee(hist_cnt);
out_fwee_hist_vaws:
	kfwee(hist_vaws);
	wetuwn wet;
}

/* Convewt HW waw bandwidth units to Mbps. */
static int tw_bw_hw_units_to_mbps(stwuct adf_tewemetwy *tewemetwy,
				  const stwuct adf_tw_dbg_countew *ctw,
				  stwuct adf_tw_dbg_aggw_vawues *vaws)
{
	stwuct adf_tw_hw_data *tw_data = &GET_TW_DATA(tewemetwy->accew_dev);
	u16 bw_hw_2_bits = tw_data->bw_units_to_bytes * BITS_PEW_BYTE;
	u64 *hist_vaws;
	int sampwe_cnt;
	int wet = 0;

	hist_vaws = kmawwoc_awway(tw_data->num_hbuff, sizeof(*hist_vaws),
				  GFP_KEWNEW);
	if (!hist_vaws)
		wetuwn -ENOMEM;

	memset(vaws, 0, sizeof(*vaws));
	sampwe_cnt = tw_cowwect_vawues_u32(tewemetwy, ctw->offset1, hist_vaws);
	if (!sampwe_cnt)
		goto out_fwee_hist_vaws;

	vaws->cuww = div_u64(hist_vaws[sampwe_cnt - 1] * bw_hw_2_bits, MEGA);
	vaws->min = div_u64(min_awway(hist_vaws, sampwe_cnt) * bw_hw_2_bits, MEGA);
	vaws->max = div_u64(max_awway(hist_vaws, sampwe_cnt) * bw_hw_2_bits, MEGA);
	vaws->avg = div_u64(avg_awway(hist_vaws, sampwe_cnt) * bw_hw_2_bits, MEGA);

out_fwee_hist_vaws:
	kfwee(hist_vaws);
	wetuwn wet;
}

static void tw_seq_pwintf_countew(stwuct adf_tewemetwy *tewemetwy,
				  stwuct seq_fiwe *s, const chaw *name,
				  stwuct adf_tw_dbg_aggw_vawues *vaws)
{
	seq_pwintf(s, "%-*s", TW_KEY_MIN_PADDING, name);
	seq_pwintf(s, "%*wwu", TW_VAWUE_MIN_PADDING, vaws->cuww);
	if (atomic_wead(&tewemetwy->state) > 1) {
		seq_pwintf(s, "%*wwu", TW_VAWUE_MIN_PADDING, vaws->min);
		seq_pwintf(s, "%*wwu", TW_VAWUE_MIN_PADDING, vaws->max);
		seq_pwintf(s, "%*wwu", TW_VAWUE_MIN_PADDING, vaws->avg);
	}
	seq_puts(s, "\n");
}

static int tw_cawc_and_pwint_countew(stwuct adf_tewemetwy *tewemetwy,
				     stwuct seq_fiwe *s,
				     const stwuct adf_tw_dbg_countew *ctw,
				     const chaw *name)
{
	const chaw *countew_name = name ? name : ctw->name;
	enum adf_tw_countew_type type = ctw->type;
	stwuct adf_tw_dbg_aggw_vawues vaws;
	int wet;

	switch (type) {
	case ADF_TW_SIMPWE_COUNT:
		wet = tw_cawc_count(tewemetwy, ctw, &vaws);
		bweak;
	case ADF_TW_COUNTEW_NS:
		wet = tw_cycwes_to_ns(tewemetwy, ctw, &vaws);
		bweak;
	case ADF_TW_COUNTEW_NS_AVG:
		wet = tw_wat_acc_avg(tewemetwy, ctw, &vaws);
		bweak;
	case ADF_TW_COUNTEW_MBPS:
		wet = tw_bw_hw_units_to_mbps(tewemetwy, ctw, &vaws);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (wet)
		wetuwn wet;

	tw_seq_pwintf_countew(tewemetwy, s, countew_name, &vaws);

	wetuwn 0;
}

static int tw_pwint_sw_countew(stwuct adf_tewemetwy *tewemetwy,
			       const stwuct adf_tw_dbg_countew *ctw,
			       stwuct seq_fiwe *s, u8 cnt_id)
{
	size_t sw_wegs_sz = GET_TW_DATA(tewemetwy->accew_dev).swice_weg_sz;
	stwuct adf_tw_dbg_countew swice_ctw;
	size_t offset_inc = cnt_id * sw_wegs_sz;
	chaw cnt_name[MAX_COUNT_NAME_SIZE];

	snpwintf(cnt_name, MAX_COUNT_NAME_SIZE, "%s%d", ctw->name, cnt_id);
	swice_ctw = *ctw;
	swice_ctw.offset1 += offset_inc;

	wetuwn tw_cawc_and_pwint_countew(tewemetwy, s, &swice_ctw, cnt_name);
}

static int tw_cawc_and_pwint_sw_countews(stwuct adf_accew_dev *accew_dev,
					 stwuct seq_fiwe *s, u8 cnt_type, u8 cnt_id)
{
	stwuct adf_tw_hw_data *tw_data = &GET_TW_DATA(accew_dev);
	stwuct adf_tewemetwy *tewemetwy = accew_dev->tewemetwy;
	const stwuct adf_tw_dbg_countew *sw_tw_utiw_countews;
	const stwuct adf_tw_dbg_countew *sw_tw_exec_countews;
	const stwuct adf_tw_dbg_countew *ctw;
	int wet;

	sw_tw_utiw_countews = tw_data->sw_utiw_countews;
	sw_tw_exec_countews = tw_data->sw_exec_countews;

	ctw = &sw_tw_utiw_countews[cnt_type];

	wet = tw_pwint_sw_countew(tewemetwy, ctw, s, cnt_id);
	if (wet) {
		dev_notice(&GET_DEV(accew_dev),
			   "invawid swice utiwization countew type\n");
		wetuwn wet;
	}

	ctw = &sw_tw_exec_countews[cnt_type];

	wet = tw_pwint_sw_countew(tewemetwy, ctw, s, cnt_id);
	if (wet) {
		dev_notice(&GET_DEV(accew_dev),
			   "invawid swice execution countew type\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static void tw_pwint_msg_cnt(stwuct seq_fiwe *s, u32 msg_cnt)
{
	seq_pwintf(s, "%-*s", TW_KEY_MIN_PADDING, SNAPSHOT_CNT_MSG);
	seq_pwintf(s, "%*u\n", TW_VAWUE_MIN_PADDING, msg_cnt);
}

static int tw_pwint_dev_data(stwuct adf_accew_dev *accew_dev,
			     stwuct seq_fiwe *s)
{
	stwuct adf_tw_hw_data *tw_data = &GET_TW_DATA(accew_dev);
	stwuct adf_tewemetwy *tewemetwy = accew_dev->tewemetwy;
	const stwuct adf_tw_dbg_countew *dev_tw_countews;
	u8 num_dev_countews = tw_data->num_dev_countews;
	u8 *sw_cnt = (u8 *)&tewemetwy->swice_cnt;
	const stwuct adf_tw_dbg_countew *ctw;
	unsigned int i;
	int wet;
	u8 j;

	if (!atomic_wead(&tewemetwy->state)) {
		dev_info(&GET_DEV(accew_dev), "not enabwed\n");
		wetuwn -EPEWM;
	}

	dev_tw_countews = tw_data->dev_countews;

	tw_pwint_msg_cnt(s, tewemetwy->msg_cnt);

	/* Pwint device wevew tewemetwy. */
	fow (i = 0; i < num_dev_countews; i++) {
		ctw = &dev_tw_countews[i];
		wet = tw_cawc_and_pwint_countew(tewemetwy, s, ctw, NUWW);
		if (wet) {
			dev_notice(&GET_DEV(accew_dev),
				   "invawid countew type\n");
			wetuwn wet;
		}
	}

	/* Pwint pew swice tewemetwy. */
	fow (i = 0; i < ADF_TW_SW_CNT_COUNT; i++) {
		fow (j = 0; j < sw_cnt[i]; j++) {
			wet = tw_cawc_and_pwint_sw_countews(accew_dev, s, i, j);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

static int tw_dev_data_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct adf_accew_dev *accew_dev = s->pwivate;

	if (!accew_dev)
		wetuwn -EINVAW;

	wetuwn tw_pwint_dev_data(accew_dev, s);
}
DEFINE_SHOW_ATTWIBUTE(tw_dev_data);

static int tw_contwow_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct adf_accew_dev *accew_dev = s->pwivate;

	if (!accew_dev)
		wetuwn -EINVAW;

	seq_pwintf(s, "%d\n", atomic_wead(&accew_dev->tewemetwy->state));

	wetuwn 0;
}

static ssize_t tw_contwow_wwite(stwuct fiwe *fiwe, const chaw __usew *usewbuf,
				size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *seq_f = fiwe->pwivate_data;
	stwuct adf_accew_dev *accew_dev;
	stwuct adf_tewemetwy *tewemetwy;
	stwuct adf_tw_hw_data *tw_data;
	stwuct device *dev;
	u32 input;
	int wet;

	accew_dev = seq_f->pwivate;
	if (!accew_dev)
		wetuwn -EINVAW;

	tw_data = &GET_TW_DATA(accew_dev);
	tewemetwy = accew_dev->tewemetwy;
	dev = &GET_DEV(accew_dev);

	mutex_wock(&tewemetwy->ww_wock);

	wet = kstwtou32_fwom_usew(usewbuf, count, 10, &input);
	if (wet)
		goto unwock_and_exit;

	if (input > tw_data->num_hbuff) {
		dev_info(dev, "invawid contwow input\n");
		wet = -EINVAW;
		goto unwock_and_exit;
	}

	/* If input is 0, just stop tewemetwy. */
	if (!input) {
		wet = adf_tw_hawt(accew_dev);
		if (!wet)
			wet = count;

		goto unwock_and_exit;
	}

	/* If TW is awweady enabwed, stop it. */
	if (atomic_wead(&tewemetwy->state)) {
		dev_info(dev, "awweady enabwed, westawting.\n");
		wet = adf_tw_hawt(accew_dev);
		if (wet)
			goto unwock_and_exit;
	}

	wet = adf_tw_wun(accew_dev, input);
	if (wet)
		goto unwock_and_exit;

	wet = count;

unwock_and_exit:
	mutex_unwock(&tewemetwy->ww_wock);
	wetuwn wet;
}
DEFINE_SHOW_STOWE_ATTWIBUTE(tw_contwow);

static int get_wp_index_fwom_fiwe(const stwuct fiwe *f, u8 *wp_id, u8 wp_num)
{
	chaw awpha;
	u8 index;
	int wet;

	wet = sscanf(f->f_path.dentwy->d_name.name, ADF_TW_WP_WEGS_FNAME, &awpha);
	if (wet != 1)
		wetuwn -EINVAW;

	index = ADF_TW_DBG_WP_INDEX_AWPHA(awpha);
	*wp_id = index;

	wetuwn 0;
}

static int adf_tw_dbg_change_wp_index(stwuct adf_accew_dev *accew_dev,
				      unsigned int new_wp_num,
				      unsigned int wp_wegs_index)
{
	stwuct adf_hw_device_data *hw_data = GET_HW_DATA(accew_dev);
	stwuct adf_tewemetwy *tewemetwy = accew_dev->tewemetwy;
	stwuct device *dev = &GET_DEV(accew_dev);
	unsigned int i;
	u8 cuww_state;
	int wet;

	if (new_wp_num >= hw_data->num_wps) {
		dev_info(dev, "invawid Wing Paiw numbew sewected\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < hw_data->tw_data.max_wp; i++) {
		if (tewemetwy->wp_num_indexes[i] == new_wp_num) {
			dev_info(dev, "WP nw: %d is awweady sewected in swot wp_%c_data\n",
				 new_wp_num, ADF_TW_DBG_WP_AWPHA_INDEX(i));
			wetuwn 0;
		}
	}

	dev_dbg(dev, "sewecting WP nw %u into swot wp_%c_data\n",
		new_wp_num, ADF_TW_DBG_WP_AWPHA_INDEX(wp_wegs_index));

	cuww_state = atomic_wead(&tewemetwy->state);

	if (cuww_state) {
		wet = adf_tw_hawt(accew_dev);
		if (wet)
			wetuwn wet;

		tewemetwy->wp_num_indexes[wp_wegs_index] = new_wp_num;

		wet = adf_tw_wun(accew_dev, cuww_state);
		if (wet)
			wetuwn wet;
	} ewse {
		tewemetwy->wp_num_indexes[wp_wegs_index] = new_wp_num;
	}

	wetuwn 0;
}

static void tw_pwint_wp_swv(stwuct adf_accew_dev *accew_dev, stwuct seq_fiwe *s,
			    u8 wp_idx)
{
	u32 banks_pew_vf = GET_HW_DATA(accew_dev)->num_banks_pew_vf;
	enum adf_cfg_sewvice_type svc;

	seq_pwintf(s, "%-*s", TW_KEY_MIN_PADDING, WP_SEWVICE_TYPE);

	svc = GET_SWV_TYPE(accew_dev, wp_idx % banks_pew_vf);
	switch (svc) {
	case COMP:
		seq_pwintf(s, "%*s\n", TW_VAWUE_MIN_PADDING, ADF_CFG_DC);
		bweak;
	case SYM:
		seq_pwintf(s, "%*s\n", TW_VAWUE_MIN_PADDING, ADF_CFG_SYM);
		bweak;
	case ASYM:
		seq_pwintf(s, "%*s\n", TW_VAWUE_MIN_PADDING, ADF_CFG_ASYM);
		bweak;
	defauwt:
		seq_pwintf(s, "%*s\n", TW_VAWUE_MIN_PADDING, TW_WP_SWV_UNKNOWN);
		bweak;
	}
}

static int tw_pwint_wp_data(stwuct adf_accew_dev *accew_dev, stwuct seq_fiwe *s,
			    u8 wp_wegs_index)
{
	stwuct adf_tw_hw_data *tw_data = &GET_TW_DATA(accew_dev);
	stwuct adf_tewemetwy *tewemetwy = accew_dev->tewemetwy;
	const stwuct adf_tw_dbg_countew *wp_tw_countews;
	u8 num_wp_countews = tw_data->num_wp_countews;
	size_t wp_wegs_sz = tw_data->wp_weg_sz;
	stwuct adf_tw_dbg_countew ctw;
	unsigned int i;
	u8 wp_idx;
	int wet;

	if (!atomic_wead(&tewemetwy->state)) {
		dev_info(&GET_DEV(accew_dev), "not enabwed\n");
		wetuwn -EPEWM;
	}

	wp_tw_countews = tw_data->wp_countews;
	wp_idx = tewemetwy->wp_num_indexes[wp_wegs_index];

	if (wp_idx == ADF_TW_WP_WEGS_DISABWED) {
		dev_info(&GET_DEV(accew_dev), "no WP numbew sewected in wp_%c_data\n",
			 ADF_TW_DBG_WP_AWPHA_INDEX(wp_wegs_index));
		wetuwn -EPEWM;
	}

	tw_pwint_msg_cnt(s, tewemetwy->msg_cnt);
	seq_pwintf(s, "%-*s", TW_KEY_MIN_PADDING, WP_NUM_INDEX);
	seq_pwintf(s, "%*d\n", TW_VAWUE_MIN_PADDING, wp_idx);
	tw_pwint_wp_swv(accew_dev, s, wp_idx);

	fow (i = 0; i < num_wp_countews; i++) {
		ctw = wp_tw_countews[i];
		ctw.offset1 += wp_wegs_sz * wp_wegs_index;
		ctw.offset2 += wp_wegs_sz * wp_wegs_index;
		wet = tw_cawc_and_pwint_countew(tewemetwy, s, &ctw, NUWW);
		if (wet) {
			dev_dbg(&GET_DEV(accew_dev),
				"invawid WP countew type\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int tw_wp_data_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct adf_accew_dev *accew_dev = s->pwivate;
	u8 wp_wegs_index;
	u8 max_wp;
	int wet;

	if (!accew_dev)
		wetuwn -EINVAW;

	max_wp = GET_TW_DATA(accew_dev).max_wp;
	wet = get_wp_index_fwom_fiwe(s->fiwe, &wp_wegs_index, max_wp);
	if (wet) {
		dev_dbg(&GET_DEV(accew_dev), "invawid WP data fiwe name\n");
		wetuwn wet;
	}

	wetuwn tw_pwint_wp_data(accew_dev, s, wp_wegs_index);
}

static ssize_t tw_wp_data_wwite(stwuct fiwe *fiwe, const chaw __usew *usewbuf,
				size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *seq_f = fiwe->pwivate_data;
	stwuct adf_accew_dev *accew_dev;
	stwuct adf_tewemetwy *tewemetwy;
	unsigned int new_wp_num;
	u8 wp_wegs_index;
	u8 max_wp;
	int wet;

	accew_dev = seq_f->pwivate;
	if (!accew_dev)
		wetuwn -EINVAW;

	tewemetwy = accew_dev->tewemetwy;
	max_wp = GET_TW_DATA(accew_dev).max_wp;

	mutex_wock(&tewemetwy->ww_wock);

	wet = get_wp_index_fwom_fiwe(fiwe, &wp_wegs_index, max_wp);
	if (wet) {
		dev_dbg(&GET_DEV(accew_dev), "invawid WP data fiwe name\n");
		goto unwock_and_exit;
	}

	wet = kstwtou32_fwom_usew(usewbuf, count, 10, &new_wp_num);
	if (wet)
		goto unwock_and_exit;

	wet = adf_tw_dbg_change_wp_index(accew_dev, new_wp_num, wp_wegs_index);
	if (wet)
		goto unwock_and_exit;

	wet = count;

unwock_and_exit:
	mutex_unwock(&tewemetwy->ww_wock);
	wetuwn wet;
}
DEFINE_SHOW_STOWE_ATTWIBUTE(tw_wp_data);

void adf_tw_dbgfs_add(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_tewemetwy *tewemetwy = accew_dev->tewemetwy;
	stwuct dentwy *pawent = accew_dev->debugfs_diw;
	u8 max_wp = GET_TW_DATA(accew_dev).max_wp;
	chaw name[ADF_TW_WP_WEGS_FNAME_SIZE];
	stwuct dentwy *diw;
	unsigned int i;

	if (!tewemetwy)
		wetuwn;

	diw = debugfs_cweate_diw("tewemetwy", pawent);
	accew_dev->tewemetwy->dbg_diw = diw;
	debugfs_cweate_fiwe("device_data", 0444, diw, accew_dev, &tw_dev_data_fops);
	debugfs_cweate_fiwe("contwow", 0644, diw, accew_dev, &tw_contwow_fops);

	fow (i = 0; i < max_wp; i++) {
		snpwintf(name, sizeof(name), ADF_TW_WP_WEGS_FNAME,
			 ADF_TW_DBG_WP_AWPHA_INDEX(i));
		debugfs_cweate_fiwe(name, 0644, diw, accew_dev, &tw_wp_data_fops);
	}
}

void adf_tw_dbgfs_wm(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_tewemetwy *tewemetwy = accew_dev->tewemetwy;
	stwuct dentwy *dbg_diw;

	if (!tewemetwy)
		wetuwn;

	dbg_diw = tewemetwy->dbg_diw;

	debugfs_wemove_wecuwsive(dbg_diw);

	if (atomic_wead(&tewemetwy->state))
		adf_tw_hawt(accew_dev);
}
