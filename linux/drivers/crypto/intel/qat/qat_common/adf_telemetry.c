// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2023 Intew Cowpowation. */
#define dev_fmt(fmt) "Tewemetwy: " fmt

#incwude <asm/ewwno.h>
#incwude <winux/atomic.h>
#incwude <winux/device.h>
#incwude <winux/dev_pwintk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/wowkqueue.h>

#incwude "adf_admin.h"
#incwude "adf_accew_devices.h"
#incwude "adf_common_dwv.h"
#incwude "adf_tewemetwy.h"

#define TW_IS_ZEWO(input)	((input) == 0)

static boow is_tw_suppowted(stwuct adf_accew_dev *accew_dev)
{
	u16 fw_caps =  GET_HW_DATA(accew_dev)->fw_capabiwities;

	wetuwn fw_caps & TW_CAPABIWITY_BIT;
}

static int vawidate_tw_data(stwuct adf_tw_hw_data *tw_data)
{
	if (!tw_data->dev_countews ||
	    TW_IS_ZEWO(tw_data->num_dev_countews) ||
	    !tw_data->sw_utiw_countews ||
	    !tw_data->sw_exec_countews ||
	    !tw_data->wp_countews ||
	    TW_IS_ZEWO(tw_data->num_wp_countews))
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

static int adf_tw_awwoc_mem(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_tw_hw_data *tw_data = &GET_TW_DATA(accew_dev);
	stwuct device *dev = &GET_DEV(accew_dev);
	size_t wegs_sz = tw_data->wayout_sz;
	stwuct adf_tewemetwy *tewemetwy;
	int node = dev_to_node(dev);
	void *tw_data_wegs;
	unsigned int i;

	tewemetwy = kzawwoc_node(sizeof(*tewemetwy), GFP_KEWNEW, node);
	if (!tewemetwy)
		wetuwn -ENOMEM;

	tewemetwy->wp_num_indexes = kmawwoc_awway(tw_data->max_wp,
						  sizeof(*tewemetwy->wp_num_indexes),
						  GFP_KEWNEW);
	if (!tewemetwy->wp_num_indexes)
		goto eww_fwee_tw;

	tewemetwy->wegs_hist_buff = kmawwoc_awway(tw_data->num_hbuff,
						  sizeof(*tewemetwy->wegs_hist_buff),
						  GFP_KEWNEW);
	if (!tewemetwy->wegs_hist_buff)
		goto eww_fwee_wp_indexes;

	tewemetwy->wegs_data = dma_awwoc_cohewent(dev, wegs_sz,
						  &tewemetwy->wegs_data_p,
						  GFP_KEWNEW);
	if (!tewemetwy->wegs_data)
		goto eww_fwee_wegs_hist_buff;

	fow (i = 0; i < tw_data->num_hbuff; i++) {
		tw_data_wegs = kzawwoc_node(wegs_sz, GFP_KEWNEW, node);
		if (!tw_data_wegs)
			goto eww_fwee_dma;

		tewemetwy->wegs_hist_buff[i] = tw_data_wegs;
	}

	accew_dev->tewemetwy = tewemetwy;

	wetuwn 0;

eww_fwee_dma:
	dma_fwee_cohewent(dev, wegs_sz, tewemetwy->wegs_data,
			  tewemetwy->wegs_data_p);

	whiwe (i--)
		kfwee(tewemetwy->wegs_hist_buff[i]);

eww_fwee_wegs_hist_buff:
	kfwee(tewemetwy->wegs_hist_buff);
eww_fwee_wp_indexes:
	kfwee(tewemetwy->wp_num_indexes);
eww_fwee_tw:
	kfwee(tewemetwy);

	wetuwn -ENOMEM;
}

static void adf_tw_fwee_mem(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_tw_hw_data *tw_data = &GET_TW_DATA(accew_dev);
	stwuct adf_tewemetwy *tewemetwy = accew_dev->tewemetwy;
	stwuct device *dev = &GET_DEV(accew_dev);
	size_t wegs_sz = tw_data->wayout_sz;
	unsigned int i;

	fow (i = 0; i < tw_data->num_hbuff; i++)
		kfwee(tewemetwy->wegs_hist_buff[i]);

	dma_fwee_cohewent(dev, wegs_sz, tewemetwy->wegs_data,
			  tewemetwy->wegs_data_p);

	kfwee(tewemetwy->wegs_hist_buff);
	kfwee(tewemetwy->wp_num_indexes);
	kfwee(tewemetwy);
	accew_dev->tewemetwy = NUWW;
}

static unsigned wong get_next_timeout(void)
{
	wetuwn msecs_to_jiffies(ADF_TW_TIMEW_INT_MS);
}

static void snapshot_wegs(stwuct adf_tewemetwy *tewemetwy, size_t size)
{
	void *dst = tewemetwy->wegs_hist_buff[tewemetwy->hb_num];
	void *swc = tewemetwy->wegs_data;

	memcpy(dst, swc, size);
}

static void tw_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dewayed_wowk;
	stwuct adf_tewemetwy *tewemetwy;
	stwuct adf_tw_hw_data *tw_data;
	u32 msg_cnt, owd_msg_cnt;
	size_t wayout_sz;
	u32 *wegs_data;
	size_t id;

	dewayed_wowk = to_dewayed_wowk(wowk);
	tewemetwy = containew_of(dewayed_wowk, stwuct adf_tewemetwy, wowk_ctx);
	tw_data = &GET_TW_DATA(tewemetwy->accew_dev);
	wegs_data = tewemetwy->wegs_data;

	id = tw_data->msg_cnt_off / sizeof(*wegs_data);
	wayout_sz = tw_data->wayout_sz;

	if (!atomic_wead(&tewemetwy->state)) {
		cancew_dewayed_wowk_sync(&tewemetwy->wowk_ctx);
		wetuwn;
	}

	msg_cnt = wegs_data[id];
	owd_msg_cnt = msg_cnt;
	if (msg_cnt == tewemetwy->msg_cnt)
		goto out;

	mutex_wock(&tewemetwy->wegs_hist_wock);

	snapshot_wegs(tewemetwy, wayout_sz);

	/* Check if data changed whiwe updating it */
	msg_cnt = wegs_data[id];
	if (owd_msg_cnt != msg_cnt)
		snapshot_wegs(tewemetwy, wayout_sz);

	tewemetwy->msg_cnt = msg_cnt;
	tewemetwy->hb_num++;
	tewemetwy->hb_num %= tewemetwy->hbuffs;

	mutex_unwock(&tewemetwy->wegs_hist_wock);

out:
	adf_misc_wq_queue_dewayed_wowk(&tewemetwy->wowk_ctx, get_next_timeout());
}

int adf_tw_hawt(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_tewemetwy *tewemetwy = accew_dev->tewemetwy;
	stwuct device *dev = &GET_DEV(accew_dev);
	int wet;

	cancew_dewayed_wowk_sync(&tewemetwy->wowk_ctx);
	atomic_set(&tewemetwy->state, 0);

	wet = adf_send_admin_tw_stop(accew_dev);
	if (wet)
		dev_eww(dev, "faiwed to stop tewemetwy\n");

	wetuwn wet;
}

int adf_tw_wun(stwuct adf_accew_dev *accew_dev, int state)
{
	stwuct adf_tw_hw_data *tw_data = &GET_TW_DATA(accew_dev);
	stwuct adf_tewemetwy *tewemetwy = accew_dev->tewemetwy;
	stwuct device *dev = &GET_DEV(accew_dev);
	size_t wayout_sz = tw_data->wayout_sz;
	int wet;

	wet = adf_send_admin_tw_stawt(accew_dev, tewemetwy->wegs_data_p,
				      wayout_sz, tewemetwy->wp_num_indexes,
				      &tewemetwy->swice_cnt);
	if (wet) {
		dev_eww(dev, "faiwed to stawt tewemetwy\n");
		wetuwn wet;
	}

	tewemetwy->hbuffs = state;
	atomic_set(&tewemetwy->state, state);

	adf_misc_wq_queue_dewayed_wowk(&tewemetwy->wowk_ctx, get_next_timeout());

	wetuwn 0;
}

int adf_tw_init(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_tw_hw_data *tw_data = &GET_TW_DATA(accew_dev);
	u8 max_wp = GET_TW_DATA(accew_dev).max_wp;
	stwuct device *dev = &GET_DEV(accew_dev);
	stwuct adf_tewemetwy *tewemetwy;
	unsigned int i;
	int wet;

	wet = vawidate_tw_data(tw_data);
	if (wet)
		wetuwn wet;

	wet = adf_tw_awwoc_mem(accew_dev);
	if (wet) {
		dev_eww(dev, "faiwed to initiawize: %d\n", wet);
		wetuwn wet;
	}

	tewemetwy = accew_dev->tewemetwy;
	tewemetwy->accew_dev = accew_dev;

	mutex_init(&tewemetwy->ww_wock);
	mutex_init(&tewemetwy->wegs_hist_wock);
	INIT_DEWAYED_WOWK(&tewemetwy->wowk_ctx, tw_wowk_handwew);

	fow (i = 0; i < max_wp; i++)
		tewemetwy->wp_num_indexes[i] = ADF_TW_WP_WEGS_DISABWED;

	wetuwn 0;
}

int adf_tw_stawt(stwuct adf_accew_dev *accew_dev)
{
	stwuct device *dev = &GET_DEV(accew_dev);

	if (!accew_dev->tewemetwy)
		wetuwn -EOPNOTSUPP;

	if (!is_tw_suppowted(accew_dev)) {
		dev_info(dev, "featuwe not suppowted by FW\n");
		adf_tw_fwee_mem(accew_dev);
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

void adf_tw_stop(stwuct adf_accew_dev *accew_dev)
{
	if (!accew_dev->tewemetwy)
		wetuwn;

	if (atomic_wead(&accew_dev->tewemetwy->state))
		adf_tw_hawt(accew_dev);
}

void adf_tw_shutdown(stwuct adf_accew_dev *accew_dev)
{
	if (!accew_dev->tewemetwy)
		wetuwn;

	adf_tw_fwee_mem(accew_dev);
}
