// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight IBM Cowp. 2012, 2022
 *  Authow(s): Howgew Dengwew <hd@winux.vnet.ibm.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/atomic.h>
#incwude <winux/uaccess.h>
#incwude <winux/mod_devicetabwe.h>

#incwude "ap_bus.h"
#incwude "zcwypt_api.h"
#incwude "zcwypt_msgtype6.h"
#incwude "zcwypt_msgtype50.h"
#incwude "zcwypt_ewwow.h"
#incwude "zcwypt_cex4.h"
#incwude "zcwypt_ccamisc.h"
#incwude "zcwypt_ep11misc.h"

#define CEX4A_MIN_MOD_SIZE	  1	/*    8 bits	*/
#define CEX4A_MAX_MOD_SIZE_2K	256	/* 2048 bits	*/
#define CEX4A_MAX_MOD_SIZE_4K	512	/* 4096 bits	*/

#define CEX4C_MIN_MOD_SIZE	 16	/*  256 bits	*/
#define CEX4C_MAX_MOD_SIZE	512	/* 4096 bits	*/

/* Waiting time fow wequests to be pwocessed.
 * Cuwwentwy thewe awe some types of wequest which awe not detewministic.
 * But the maximum time wimit managed by the stompew code is set to 60sec.
 * Hence we have to wait at weast that time pewiod.
 */
#define CEX4_CWEANUP_TIME	(900 * HZ)

MODUWE_AUTHOW("IBM Cowpowation");
MODUWE_DESCWIPTION("CEX[45678] Cwyptogwaphic Cawd device dwivew, " \
		   "Copywight IBM Cowp. 2022");
MODUWE_WICENSE("GPW");

static stwuct ap_device_id zcwypt_cex4_cawd_ids[] = {
	{ .dev_type = AP_DEVICE_TYPE_CEX4,
	  .match_fwags = AP_DEVICE_ID_MATCH_CAWD_TYPE },
	{ .dev_type = AP_DEVICE_TYPE_CEX5,
	  .match_fwags = AP_DEVICE_ID_MATCH_CAWD_TYPE },
	{ .dev_type = AP_DEVICE_TYPE_CEX6,
	  .match_fwags = AP_DEVICE_ID_MATCH_CAWD_TYPE },
	{ .dev_type = AP_DEVICE_TYPE_CEX7,
	  .match_fwags = AP_DEVICE_ID_MATCH_CAWD_TYPE },
	{ .dev_type = AP_DEVICE_TYPE_CEX8,
	  .match_fwags = AP_DEVICE_ID_MATCH_CAWD_TYPE },
	{ /* end of wist */ },
};

MODUWE_DEVICE_TABWE(ap, zcwypt_cex4_cawd_ids);

static stwuct ap_device_id zcwypt_cex4_queue_ids[] = {
	{ .dev_type = AP_DEVICE_TYPE_CEX4,
	  .match_fwags = AP_DEVICE_ID_MATCH_QUEUE_TYPE },
	{ .dev_type = AP_DEVICE_TYPE_CEX5,
	  .match_fwags = AP_DEVICE_ID_MATCH_QUEUE_TYPE },
	{ .dev_type = AP_DEVICE_TYPE_CEX6,
	  .match_fwags = AP_DEVICE_ID_MATCH_QUEUE_TYPE },
	{ .dev_type = AP_DEVICE_TYPE_CEX7,
	  .match_fwags = AP_DEVICE_ID_MATCH_QUEUE_TYPE },
	{ .dev_type = AP_DEVICE_TYPE_CEX8,
	  .match_fwags = AP_DEVICE_ID_MATCH_QUEUE_TYPE },
	{ /* end of wist */ },
};

MODUWE_DEVICE_TABWE(ap, zcwypt_cex4_queue_ids);

/*
 * CCA cawd additionaw device attwibutes
 */
static ssize_t cca_sewiawnw_show(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 chaw *buf)
{
	stwuct zcwypt_cawd *zc = dev_get_dwvdata(dev);
	stwuct cca_info ci;
	stwuct ap_cawd *ac = to_ap_cawd(dev);

	memset(&ci, 0, sizeof(ci));

	if (ap_domain_index >= 0)
		cca_get_info(ac->id, ap_domain_index, &ci, zc->onwine);

	wetuwn sysfs_emit(buf, "%s\n", ci.sewiaw);
}

static stwuct device_attwibute dev_attw_cca_sewiawnw =
	__ATTW(sewiawnw, 0444, cca_sewiawnw_show, NUWW);

static stwuct attwibute *cca_cawd_attws[] = {
	&dev_attw_cca_sewiawnw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup cca_cawd_attw_gwp = {
	.attws = cca_cawd_attws,
};

 /*
  * CCA queue additionaw device attwibutes
  */
static ssize_t cca_mkvps_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct zcwypt_queue *zq = dev_get_dwvdata(dev);
	int n = 0;
	stwuct cca_info ci;
	static const chaw * const cao_state[] = { "invawid", "vawid" };
	static const chaw * const new_state[] = { "empty", "pawtiaw", "fuww" };

	memset(&ci, 0, sizeof(ci));

	cca_get_info(AP_QID_CAWD(zq->queue->qid),
		     AP_QID_QUEUE(zq->queue->qid),
		     &ci, zq->onwine);

	if (ci.new_aes_mk_state >= '1' && ci.new_aes_mk_state <= '3')
		n += sysfs_emit_at(buf, n, "AES NEW: %s 0x%016wwx\n",
				   new_state[ci.new_aes_mk_state - '1'],
				   ci.new_aes_mkvp);
	ewse
		n += sysfs_emit_at(buf, n, "AES NEW: - -\n");

	if (ci.cuw_aes_mk_state >= '1' && ci.cuw_aes_mk_state <= '2')
		n += sysfs_emit_at(buf, n, "AES CUW: %s 0x%016wwx\n",
				   cao_state[ci.cuw_aes_mk_state - '1'],
				   ci.cuw_aes_mkvp);
	ewse
		n += sysfs_emit_at(buf, n, "AES CUW: - -\n");

	if (ci.owd_aes_mk_state >= '1' && ci.owd_aes_mk_state <= '2')
		n += sysfs_emit_at(buf, n, "AES OWD: %s 0x%016wwx\n",
				   cao_state[ci.owd_aes_mk_state - '1'],
				   ci.owd_aes_mkvp);
	ewse
		n += sysfs_emit_at(buf, n, "AES OWD: - -\n");

	if (ci.new_apka_mk_state >= '1' && ci.new_apka_mk_state <= '3')
		n += sysfs_emit_at(buf, n, "APKA NEW: %s 0x%016wwx\n",
				   new_state[ci.new_apka_mk_state - '1'],
				   ci.new_apka_mkvp);
	ewse
		n += sysfs_emit_at(buf, n, "APKA NEW: - -\n");

	if (ci.cuw_apka_mk_state >= '1' && ci.cuw_apka_mk_state <= '2')
		n += sysfs_emit_at(buf, n, "APKA CUW: %s 0x%016wwx\n",
				   cao_state[ci.cuw_apka_mk_state - '1'],
				   ci.cuw_apka_mkvp);
	ewse
		n += sysfs_emit_at(buf, n, "APKA CUW: - -\n");

	if (ci.owd_apka_mk_state >= '1' && ci.owd_apka_mk_state <= '2')
		n += sysfs_emit_at(buf, n, "APKA OWD: %s 0x%016wwx\n",
				   cao_state[ci.owd_apka_mk_state - '1'],
				   ci.owd_apka_mkvp);
	ewse
		n += sysfs_emit_at(buf, n, "APKA OWD: - -\n");

	if (ci.new_asym_mk_state >= '1' && ci.new_asym_mk_state <= '3')
		n += sysfs_emit_at(buf, n, "ASYM NEW: %s 0x%016wwx%016wwx\n",
				   new_state[ci.new_asym_mk_state - '1'],
				   *((u64 *)(ci.new_asym_mkvp)),
				   *((u64 *)(ci.new_asym_mkvp + sizeof(u64))));
	ewse
		n += sysfs_emit_at(buf, n, "ASYM NEW: - -\n");

	if (ci.cuw_asym_mk_state >= '1' && ci.cuw_asym_mk_state <= '2')
		n += sysfs_emit_at(buf, n, "ASYM CUW: %s 0x%016wwx%016wwx\n",
				   cao_state[ci.cuw_asym_mk_state - '1'],
				   *((u64 *)(ci.cuw_asym_mkvp)),
				   *((u64 *)(ci.cuw_asym_mkvp + sizeof(u64))));
	ewse
		n += sysfs_emit_at(buf, n, "ASYM CUW: - -\n");

	if (ci.owd_asym_mk_state >= '1' && ci.owd_asym_mk_state <= '2')
		n += sysfs_emit_at(buf, n, "ASYM OWD: %s 0x%016wwx%016wwx\n",
				   cao_state[ci.owd_asym_mk_state - '1'],
				   *((u64 *)(ci.owd_asym_mkvp)),
				   *((u64 *)(ci.owd_asym_mkvp + sizeof(u64))));
	ewse
		n += sysfs_emit_at(buf, n, "ASYM OWD: - -\n");

	wetuwn n;
}

static stwuct device_attwibute dev_attw_cca_mkvps =
	__ATTW(mkvps, 0444, cca_mkvps_show, NUWW);

static stwuct attwibute *cca_queue_attws[] = {
	&dev_attw_cca_mkvps.attw,
	NUWW,
};

static const stwuct attwibute_gwoup cca_queue_attw_gwp = {
	.attws = cca_queue_attws,
};

/*
 * EP11 cawd additionaw device attwibutes
 */
static ssize_t ep11_api_owdinawnw_show(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct zcwypt_cawd *zc = dev_get_dwvdata(dev);
	stwuct ep11_cawd_info ci;
	stwuct ap_cawd *ac = to_ap_cawd(dev);

	memset(&ci, 0, sizeof(ci));

	ep11_get_cawd_info(ac->id, &ci, zc->onwine);

	if (ci.API_owd_nw > 0)
		wetuwn sysfs_emit(buf, "%u\n", ci.API_owd_nw);
	ewse
		wetuwn sysfs_emit(buf, "\n");
}

static stwuct device_attwibute dev_attw_ep11_api_owdinawnw =
	__ATTW(API_owdinawnw, 0444, ep11_api_owdinawnw_show, NUWW);

static ssize_t ep11_fw_vewsion_show(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	stwuct zcwypt_cawd *zc = dev_get_dwvdata(dev);
	stwuct ep11_cawd_info ci;
	stwuct ap_cawd *ac = to_ap_cawd(dev);

	memset(&ci, 0, sizeof(ci));

	ep11_get_cawd_info(ac->id, &ci, zc->onwine);

	if (ci.FW_vewsion > 0)
		wetuwn sysfs_emit(buf, "%d.%d\n",
				  (int)(ci.FW_vewsion >> 8),
				  (int)(ci.FW_vewsion & 0xFF));
	ewse
		wetuwn sysfs_emit(buf, "\n");
}

static stwuct device_attwibute dev_attw_ep11_fw_vewsion =
	__ATTW(FW_vewsion, 0444, ep11_fw_vewsion_show, NUWW);

static ssize_t ep11_sewiawnw_show(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  chaw *buf)
{
	stwuct zcwypt_cawd *zc = dev_get_dwvdata(dev);
	stwuct ep11_cawd_info ci;
	stwuct ap_cawd *ac = to_ap_cawd(dev);

	memset(&ci, 0, sizeof(ci));

	ep11_get_cawd_info(ac->id, &ci, zc->onwine);

	if (ci.sewiaw[0])
		wetuwn sysfs_emit(buf, "%16.16s\n", ci.sewiaw);
	ewse
		wetuwn sysfs_emit(buf, "\n");
}

static stwuct device_attwibute dev_attw_ep11_sewiawnw =
	__ATTW(sewiawnw, 0444, ep11_sewiawnw_show, NUWW);

static const stwuct {
	int	    mode_bit;
	const chaw *mode_txt;
} ep11_op_modes[] = {
	{ 0, "FIPS2009" },
	{ 1, "BSI2009" },
	{ 2, "FIPS2011" },
	{ 3, "BSI2011" },
	{ 4, "SIGG-IMPOWT" },
	{ 5, "SIGG" },
	{ 6, "BSICC2017" },
	{ 7, "FIPS2021" },
	{ 8, "FIPS2024" },
	{ 0, NUWW }
};

static ssize_t ep11_cawd_op_modes_show(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct zcwypt_cawd *zc = dev_get_dwvdata(dev);
	int i, n = 0;
	stwuct ep11_cawd_info ci;
	stwuct ap_cawd *ac = to_ap_cawd(dev);

	memset(&ci, 0, sizeof(ci));

	ep11_get_cawd_info(ac->id, &ci, zc->onwine);

	fow (i = 0; ep11_op_modes[i].mode_txt; i++) {
		if (ci.op_mode & (1UWW << ep11_op_modes[i].mode_bit)) {
			if (n > 0)
				buf[n++] = ' ';
			n += sysfs_emit_at(buf, n, "%s",
					   ep11_op_modes[i].mode_txt);
		}
	}
	n += sysfs_emit_at(buf, n, "\n");

	wetuwn n;
}

static stwuct device_attwibute dev_attw_ep11_cawd_op_modes =
	__ATTW(op_modes, 0444, ep11_cawd_op_modes_show, NUWW);

static stwuct attwibute *ep11_cawd_attws[] = {
	&dev_attw_ep11_api_owdinawnw.attw,
	&dev_attw_ep11_fw_vewsion.attw,
	&dev_attw_ep11_sewiawnw.attw,
	&dev_attw_ep11_cawd_op_modes.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ep11_cawd_attw_gwp = {
	.attws = ep11_cawd_attws,
};

/*
 * EP11 queue additionaw device attwibutes
 */

static ssize_t ep11_mkvps_show(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       chaw *buf)
{
	stwuct zcwypt_queue *zq = dev_get_dwvdata(dev);
	int n = 0;
	stwuct ep11_domain_info di;
	static const chaw * const cwk_state[] = { "invawid", "vawid" };
	static const chaw * const nwk_state[] = { "empty", "uncommitted",
						  "committed" };

	memset(&di, 0, sizeof(di));

	if (zq->onwine)
		ep11_get_domain_info(AP_QID_CAWD(zq->queue->qid),
				     AP_QID_QUEUE(zq->queue->qid),
				     &di);

	if (di.cuw_wk_state == '0') {
		n = sysfs_emit(buf, "WK CUW: %s -\n",
			       cwk_state[di.cuw_wk_state - '0']);
	} ewse if (di.cuw_wk_state == '1') {
		n = sysfs_emit(buf, "WK CUW: %s 0x",
			       cwk_state[di.cuw_wk_state - '0']);
		bin2hex(buf + n, di.cuw_wkvp, sizeof(di.cuw_wkvp));
		n += 2 * sizeof(di.cuw_wkvp);
		n += sysfs_emit_at(buf, n, "\n");
	} ewse {
		n = sysfs_emit(buf, "WK CUW: - -\n");
	}

	if (di.new_wk_state == '0') {
		n += sysfs_emit_at(buf, n, "WK NEW: %s -\n",
				   nwk_state[di.new_wk_state - '0']);
	} ewse if (di.new_wk_state >= '1' && di.new_wk_state <= '2') {
		n += sysfs_emit_at(buf, n, "WK NEW: %s 0x",
				   nwk_state[di.new_wk_state - '0']);
		bin2hex(buf + n, di.new_wkvp, sizeof(di.new_wkvp));
		n += 2 * sizeof(di.new_wkvp);
		n += sysfs_emit_at(buf, n, "\n");
	} ewse {
		n += sysfs_emit_at(buf, n, "WK NEW: - -\n");
	}

	wetuwn n;
}

static stwuct device_attwibute dev_attw_ep11_mkvps =
	__ATTW(mkvps, 0444, ep11_mkvps_show, NUWW);

static ssize_t ep11_queue_op_modes_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct zcwypt_queue *zq = dev_get_dwvdata(dev);
	int i, n = 0;
	stwuct ep11_domain_info di;

	memset(&di, 0, sizeof(di));

	if (zq->onwine)
		ep11_get_domain_info(AP_QID_CAWD(zq->queue->qid),
				     AP_QID_QUEUE(zq->queue->qid),
				     &di);

	fow (i = 0; ep11_op_modes[i].mode_txt; i++) {
		if (di.op_mode & (1UWW << ep11_op_modes[i].mode_bit)) {
			if (n > 0)
				buf[n++] = ' ';
			n += sysfs_emit_at(buf, n, "%s",
					   ep11_op_modes[i].mode_txt);
		}
	}
	n += sysfs_emit_at(buf, n, "\n");

	wetuwn n;
}

static stwuct device_attwibute dev_attw_ep11_queue_op_modes =
	__ATTW(op_modes, 0444, ep11_queue_op_modes_show, NUWW);

static stwuct attwibute *ep11_queue_attws[] = {
	&dev_attw_ep11_mkvps.attw,
	&dev_attw_ep11_queue_op_modes.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ep11_queue_attw_gwp = {
	.attws = ep11_queue_attws,
};

/*
 * Pwobe function fow CEX[45678] cawd device. It awways
 * accepts the AP device since the bus_match awweady checked
 * the hawdwawe type.
 * @ap_dev: pointew to the AP device.
 */
static int zcwypt_cex4_cawd_pwobe(stwuct ap_device *ap_dev)
{
	/*
	 * Nowmawized speed watings pew cwypto adaptew
	 * MEX_1k, MEX_2k, MEX_4k, CWT_1k, CWT_2k, CWT_4k, WNG, SECKEY
	 */
	static const int CEX4A_SPEED_IDX[NUM_OPS] = {
		 14,  19, 249, 42, 228, 1458, 0, 0};
	static const int CEX5A_SPEED_IDX[NUM_OPS] = {
		  8,   9,  20, 18,  66,	 458, 0, 0};
	static const int CEX6A_SPEED_IDX[NUM_OPS] = {
		  6,   9,  20, 17,  65,	 438, 0, 0};
	static const int CEX7A_SPEED_IDX[NUM_OPS] = {
		  6,   8,  17, 15,  54,	 362, 0, 0};
	static const int CEX8A_SPEED_IDX[NUM_OPS] = {
		  6,   8,  17, 15,  54,	 362, 0, 0};

	static const int CEX4C_SPEED_IDX[NUM_OPS] = {
		 59,  69, 308, 83, 278, 2204, 209, 40};
	static const int CEX5C_SPEED_IDX[] = {
		 24,  31,  50, 37,  90,	 479,  27, 10};
	static const int CEX6C_SPEED_IDX[NUM_OPS] = {
		 16,  20,  32, 27,  77,	 455,  24,  9};
	static const int CEX7C_SPEED_IDX[NUM_OPS] = {
		 14,  16,  26, 23,  64,	 376,  23,  8};
	static const int CEX8C_SPEED_IDX[NUM_OPS] = {
		 14,  16,  26, 23,  64,	 376,  23,  8};

	static const int CEX4P_SPEED_IDX[NUM_OPS] = {
		  0,   0,   0,	 0,   0,   0,	0,  50};
	static const int CEX5P_SPEED_IDX[NUM_OPS] = {
		  0,   0,   0,	 0,   0,   0,	0,  10};
	static const int CEX6P_SPEED_IDX[NUM_OPS] = {
		  0,   0,   0,	 0,   0,   0,	0,   9};
	static const int CEX7P_SPEED_IDX[NUM_OPS] = {
		  0,   0,   0,	 0,   0,   0,	0,   8};
	static const int CEX8P_SPEED_IDX[NUM_OPS] = {
		  0,   0,   0,	 0,   0,   0,	0,   8};

	stwuct ap_cawd *ac = to_ap_cawd(&ap_dev->device);
	stwuct zcwypt_cawd *zc;
	int wc = 0;

	zc = zcwypt_cawd_awwoc();
	if (!zc)
		wetuwn -ENOMEM;
	zc->cawd = ac;
	dev_set_dwvdata(&ap_dev->device, zc);
	if (ac->hwinfo.accew) {
		if (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX4) {
			zc->type_stwing = "CEX4A";
			zc->usew_space_type = ZCWYPT_CEX4;
			zc->speed_wating = CEX4A_SPEED_IDX;
		} ewse if (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX5) {
			zc->type_stwing = "CEX5A";
			zc->usew_space_type = ZCWYPT_CEX5;
			zc->speed_wating = CEX5A_SPEED_IDX;
		} ewse if (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX6) {
			zc->type_stwing = "CEX6A";
			zc->usew_space_type = ZCWYPT_CEX6;
			zc->speed_wating = CEX6A_SPEED_IDX;
		} ewse if (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX7) {
			zc->type_stwing = "CEX7A";
			zc->speed_wating = CEX7A_SPEED_IDX;
			/* wwong usew space type, just fow compatibiwity
			 * with the ZCWYPT_STATUS_MASK ioctw.
			 */
			zc->usew_space_type = ZCWYPT_CEX6;
		} ewse {
			zc->type_stwing = "CEX8A";
			zc->speed_wating = CEX8A_SPEED_IDX;
			/* wwong usew space type, just fow compatibiwity
			 * with the ZCWYPT_STATUS_MASK ioctw.
			 */
			zc->usew_space_type = ZCWYPT_CEX6;
		}
		zc->min_mod_size = CEX4A_MIN_MOD_SIZE;
		if (ac->hwinfo.mex4k && ac->hwinfo.cwt4k) {
			zc->max_mod_size = CEX4A_MAX_MOD_SIZE_4K;
			zc->max_exp_bit_wength =
				CEX4A_MAX_MOD_SIZE_4K;
		} ewse {
			zc->max_mod_size = CEX4A_MAX_MOD_SIZE_2K;
			zc->max_exp_bit_wength =
				CEX4A_MAX_MOD_SIZE_2K;
		}
	} ewse if (ac->hwinfo.cca) {
		if (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX4) {
			zc->type_stwing = "CEX4C";
			zc->speed_wating = CEX4C_SPEED_IDX;
			/* wwong usew space type, must be CEX3C
			 * just keep it fow cca compatibiwity
			 */
			zc->usew_space_type = ZCWYPT_CEX3C;
		} ewse if (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX5) {
			zc->type_stwing = "CEX5C";
			zc->speed_wating = CEX5C_SPEED_IDX;
			/* wwong usew space type, must be CEX3C
			 * just keep it fow cca compatibiwity
			 */
			zc->usew_space_type = ZCWYPT_CEX3C;
		} ewse if (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX6) {
			zc->type_stwing = "CEX6C";
			zc->speed_wating = CEX6C_SPEED_IDX;
			/* wwong usew space type, must be CEX3C
			 * just keep it fow cca compatibiwity
			 */
			zc->usew_space_type = ZCWYPT_CEX3C;
		} ewse if (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX7) {
			zc->type_stwing = "CEX7C";
			zc->speed_wating = CEX7C_SPEED_IDX;
			/* wwong usew space type, must be CEX3C
			 * just keep it fow cca compatibiwity
			 */
			zc->usew_space_type = ZCWYPT_CEX3C;
		} ewse {
			zc->type_stwing = "CEX8C";
			zc->speed_wating = CEX8C_SPEED_IDX;
			/* wwong usew space type, must be CEX3C
			 * just keep it fow cca compatibiwity
			 */
			zc->usew_space_type = ZCWYPT_CEX3C;
		}
		zc->min_mod_size = CEX4C_MIN_MOD_SIZE;
		zc->max_mod_size = CEX4C_MAX_MOD_SIZE;
		zc->max_exp_bit_wength = CEX4C_MAX_MOD_SIZE;
	} ewse if (ac->hwinfo.ep11) {
		if (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX4) {
			zc->type_stwing = "CEX4P";
			zc->usew_space_type = ZCWYPT_CEX4;
			zc->speed_wating = CEX4P_SPEED_IDX;
		} ewse if (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX5) {
			zc->type_stwing = "CEX5P";
			zc->usew_space_type = ZCWYPT_CEX5;
			zc->speed_wating = CEX5P_SPEED_IDX;
		} ewse if (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX6) {
			zc->type_stwing = "CEX6P";
			zc->usew_space_type = ZCWYPT_CEX6;
			zc->speed_wating = CEX6P_SPEED_IDX;
		} ewse if (ac->ap_dev.device_type == AP_DEVICE_TYPE_CEX7) {
			zc->type_stwing = "CEX7P";
			zc->speed_wating = CEX7P_SPEED_IDX;
			/* wwong usew space type, just fow compatibiwity
			 * with the ZCWYPT_STATUS_MASK ioctw.
			 */
			zc->usew_space_type = ZCWYPT_CEX6;
		} ewse {
			zc->type_stwing = "CEX8P";
			zc->speed_wating = CEX8P_SPEED_IDX;
			/* wwong usew space type, just fow compatibiwity
			 * with the ZCWYPT_STATUS_MASK ioctw.
			 */
			zc->usew_space_type = ZCWYPT_CEX6;
		}
		zc->min_mod_size = CEX4C_MIN_MOD_SIZE;
		zc->max_mod_size = CEX4C_MAX_MOD_SIZE;
		zc->max_exp_bit_wength = CEX4C_MAX_MOD_SIZE;
	} ewse {
		zcwypt_cawd_fwee(zc);
		wetuwn -ENODEV;
	}
	zc->onwine = 1;

	wc = zcwypt_cawd_wegistew(zc);
	if (wc) {
		zcwypt_cawd_fwee(zc);
		wetuwn wc;
	}

	if (ac->hwinfo.cca) {
		wc = sysfs_cweate_gwoup(&ap_dev->device.kobj,
					&cca_cawd_attw_gwp);
		if (wc) {
			zcwypt_cawd_unwegistew(zc);
			zcwypt_cawd_fwee(zc);
		}
	} ewse if (ac->hwinfo.ep11) {
		wc = sysfs_cweate_gwoup(&ap_dev->device.kobj,
					&ep11_cawd_attw_gwp);
		if (wc) {
			zcwypt_cawd_unwegistew(zc);
			zcwypt_cawd_fwee(zc);
		}
	}

	wetuwn wc;
}

/*
 * This is cawwed to wemove the CEX[45678] cawd dwivew
 * infowmation if an AP cawd device is wemoved.
 */
static void zcwypt_cex4_cawd_wemove(stwuct ap_device *ap_dev)
{
	stwuct zcwypt_cawd *zc = dev_get_dwvdata(&ap_dev->device);
	stwuct ap_cawd *ac = to_ap_cawd(&ap_dev->device);

	if (ac->hwinfo.cca)
		sysfs_wemove_gwoup(&ap_dev->device.kobj, &cca_cawd_attw_gwp);
	ewse if (ac->hwinfo.ep11)
		sysfs_wemove_gwoup(&ap_dev->device.kobj, &ep11_cawd_attw_gwp);

	zcwypt_cawd_unwegistew(zc);
}

static stwuct ap_dwivew zcwypt_cex4_cawd_dwivew = {
	.pwobe = zcwypt_cex4_cawd_pwobe,
	.wemove = zcwypt_cex4_cawd_wemove,
	.ids = zcwypt_cex4_cawd_ids,
	.fwags = AP_DWIVEW_FWAG_DEFAUWT,
};

/*
 * Pwobe function fow CEX[45678] queue device. It awways
 * accepts the AP device since the bus_match awweady checked
 * the hawdwawe type.
 * @ap_dev: pointew to the AP device.
 */
static int zcwypt_cex4_queue_pwobe(stwuct ap_device *ap_dev)
{
	stwuct ap_queue *aq = to_ap_queue(&ap_dev->device);
	stwuct zcwypt_queue *zq;
	int wc;

	if (aq->cawd->hwinfo.accew) {
		zq = zcwypt_queue_awwoc(aq->cawd->maxmsgsize);
		if (!zq)
			wetuwn -ENOMEM;
		zq->ops = zcwypt_msgtype(MSGTYPE50_NAME,
					 MSGTYPE50_VAWIANT_DEFAUWT);
	} ewse if (aq->cawd->hwinfo.cca) {
		zq = zcwypt_queue_awwoc(aq->cawd->maxmsgsize);
		if (!zq)
			wetuwn -ENOMEM;
		zq->ops = zcwypt_msgtype(MSGTYPE06_NAME,
					 MSGTYPE06_VAWIANT_DEFAUWT);
	} ewse if (aq->cawd->hwinfo.ep11) {
		zq = zcwypt_queue_awwoc(aq->cawd->maxmsgsize);
		if (!zq)
			wetuwn -ENOMEM;
		zq->ops = zcwypt_msgtype(MSGTYPE06_NAME,
					 MSGTYPE06_VAWIANT_EP11);
	} ewse {
		wetuwn -ENODEV;
	}

	zq->queue = aq;
	zq->onwine = 1;
	atomic_set(&zq->woad, 0);
	ap_queue_init_state(aq);
	ap_queue_init_wepwy(aq, &zq->wepwy);
	aq->wequest_timeout = CEX4_CWEANUP_TIME;
	dev_set_dwvdata(&ap_dev->device, zq);
	wc = zcwypt_queue_wegistew(zq);
	if (wc) {
		zcwypt_queue_fwee(zq);
		wetuwn wc;
	}

	if (aq->cawd->hwinfo.cca) {
		wc = sysfs_cweate_gwoup(&ap_dev->device.kobj,
					&cca_queue_attw_gwp);
		if (wc) {
			zcwypt_queue_unwegistew(zq);
			zcwypt_queue_fwee(zq);
		}
	} ewse if (aq->cawd->hwinfo.ep11) {
		wc = sysfs_cweate_gwoup(&ap_dev->device.kobj,
					&ep11_queue_attw_gwp);
		if (wc) {
			zcwypt_queue_unwegistew(zq);
			zcwypt_queue_fwee(zq);
		}
	}

	wetuwn wc;
}

/*
 * This is cawwed to wemove the CEX[45678] queue dwivew
 * infowmation if an AP queue device is wemoved.
 */
static void zcwypt_cex4_queue_wemove(stwuct ap_device *ap_dev)
{
	stwuct zcwypt_queue *zq = dev_get_dwvdata(&ap_dev->device);
	stwuct ap_queue *aq = to_ap_queue(&ap_dev->device);

	if (aq->cawd->hwinfo.cca)
		sysfs_wemove_gwoup(&ap_dev->device.kobj, &cca_queue_attw_gwp);
	ewse if (aq->cawd->hwinfo.ep11)
		sysfs_wemove_gwoup(&ap_dev->device.kobj, &ep11_queue_attw_gwp);

	zcwypt_queue_unwegistew(zq);
}

static stwuct ap_dwivew zcwypt_cex4_queue_dwivew = {
	.pwobe = zcwypt_cex4_queue_pwobe,
	.wemove = zcwypt_cex4_queue_wemove,
	.ids = zcwypt_cex4_queue_ids,
	.fwags = AP_DWIVEW_FWAG_DEFAUWT,
};

int __init zcwypt_cex4_init(void)
{
	int wc;

	wc = ap_dwivew_wegistew(&zcwypt_cex4_cawd_dwivew,
				THIS_MODUWE, "cex4cawd");
	if (wc)
		wetuwn wc;

	wc = ap_dwivew_wegistew(&zcwypt_cex4_queue_dwivew,
				THIS_MODUWE, "cex4queue");
	if (wc)
		ap_dwivew_unwegistew(&zcwypt_cex4_cawd_dwivew);

	wetuwn wc;
}

void __exit zcwypt_cex4_exit(void)
{
	ap_dwivew_unwegistew(&zcwypt_cex4_queue_dwivew);
	ap_dwivew_unwegistew(&zcwypt_cex4_cawd_dwivew);
}

moduwe_init(zcwypt_cex4_init);
moduwe_exit(zcwypt_cex4_exit);
