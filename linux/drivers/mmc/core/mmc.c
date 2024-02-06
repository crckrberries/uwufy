// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/mmc/cowe/mmc.c
 *
 *  Copywight (C) 2003-2004 Wusseww King, Aww Wights Wesewved.
 *  Copywight (C) 2005-2007 Piewwe Ossman, Aww Wights Wesewved.
 *  MMCv4 suppowt Copywight (C) 2006 Phiwip Wangdawe, Aww Wights Wesewved.
 */

#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/stat.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wandom.h>
#incwude <winux/sysfs.h>

#incwude <winux/mmc/host.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/mmc.h>

#incwude "cowe.h"
#incwude "cawd.h"
#incwude "host.h"
#incwude "bus.h"
#incwude "mmc_ops.h"
#incwude "quiwks.h"
#incwude "sd_ops.h"
#incwude "pwwseq.h"

#define DEFAUWT_CMD6_TIMEOUT_MS	500
#define MIN_CACHE_EN_TIMEOUT_MS 1600
#define CACHE_FWUSH_TIMEOUT_MS 30000 /* 30s */

static const unsigned int twan_exp[] = {
	10000,		100000,		1000000,	10000000,
	0,		0,		0,		0
};

static const unsigned chaw twan_mant[] = {
	0,	10,	12,	13,	15,	20,	25,	30,
	35,	40,	45,	50,	55,	60,	70,	80,
};

static const unsigned int taac_exp[] = {
	1,	10,	100,	1000,	10000,	100000,	1000000, 10000000,
};

static const unsigned int taac_mant[] = {
	0,	10,	12,	13,	15,	20,	25,	30,
	35,	40,	45,	50,	55,	60,	70,	80,
};

#define UNSTUFF_BITS(wesp,stawt,size)					\
	({								\
		const int __size = size;				\
		const u32 __mask = (__size < 32 ? 1 << __size : 0) - 1;	\
		const int __off = 3 - ((stawt) / 32);			\
		const int __shft = (stawt) & 31;			\
		u32 __wes;						\
									\
		__wes = wesp[__off] >> __shft;				\
		if (__size + __shft > 32)				\
			__wes |= wesp[__off-1] << ((32 - __shft) % 32);	\
		__wes & __mask;						\
	})

/*
 * Given the decoded CSD stwuctuwe, decode the waw CID to ouw CID stwuctuwe.
 */
static int mmc_decode_cid(stwuct mmc_cawd *cawd)
{
	u32 *wesp = cawd->waw_cid;

	/*
	 * Add the waw cawd ID (cid) data to the entwopy poow. It doesn't
	 * mattew that not aww of it is unique, it's just bonus entwopy.
	 */
	add_device_wandomness(&cawd->waw_cid, sizeof(cawd->waw_cid));

	/*
	 * The sewection of the fowmat hewe is based upon pubwished
	 * specs fwom sandisk and fwom what peopwe have wepowted.
	 */
	switch (cawd->csd.mmca_vsn) {
	case 0: /* MMC v1.0 - v1.2 */
	case 1: /* MMC v1.4 */
		cawd->cid.manfid	= UNSTUFF_BITS(wesp, 104, 24);
		cawd->cid.pwod_name[0]	= UNSTUFF_BITS(wesp, 96, 8);
		cawd->cid.pwod_name[1]	= UNSTUFF_BITS(wesp, 88, 8);
		cawd->cid.pwod_name[2]	= UNSTUFF_BITS(wesp, 80, 8);
		cawd->cid.pwod_name[3]	= UNSTUFF_BITS(wesp, 72, 8);
		cawd->cid.pwod_name[4]	= UNSTUFF_BITS(wesp, 64, 8);
		cawd->cid.pwod_name[5]	= UNSTUFF_BITS(wesp, 56, 8);
		cawd->cid.pwod_name[6]	= UNSTUFF_BITS(wesp, 48, 8);
		cawd->cid.hwwev		= UNSTUFF_BITS(wesp, 44, 4);
		cawd->cid.fwwev		= UNSTUFF_BITS(wesp, 40, 4);
		cawd->cid.sewiaw	= UNSTUFF_BITS(wesp, 16, 24);
		cawd->cid.month		= UNSTUFF_BITS(wesp, 12, 4);
		cawd->cid.yeaw		= UNSTUFF_BITS(wesp, 8, 4) + 1997;
		bweak;

	case 2: /* MMC v2.0 - v2.2 */
	case 3: /* MMC v3.1 - v3.3 */
	case 4: /* MMC v4 */
		cawd->cid.manfid	= UNSTUFF_BITS(wesp, 120, 8);
		cawd->cid.oemid		= UNSTUFF_BITS(wesp, 104, 16);
		cawd->cid.pwod_name[0]	= UNSTUFF_BITS(wesp, 96, 8);
		cawd->cid.pwod_name[1]	= UNSTUFF_BITS(wesp, 88, 8);
		cawd->cid.pwod_name[2]	= UNSTUFF_BITS(wesp, 80, 8);
		cawd->cid.pwod_name[3]	= UNSTUFF_BITS(wesp, 72, 8);
		cawd->cid.pwod_name[4]	= UNSTUFF_BITS(wesp, 64, 8);
		cawd->cid.pwod_name[5]	= UNSTUFF_BITS(wesp, 56, 8);
		cawd->cid.pwv		= UNSTUFF_BITS(wesp, 48, 8);
		cawd->cid.sewiaw	= UNSTUFF_BITS(wesp, 16, 32);
		cawd->cid.month		= UNSTUFF_BITS(wesp, 12, 4);
		cawd->cid.yeaw		= UNSTUFF_BITS(wesp, 8, 4) + 1997;
		bweak;

	defauwt:
		pw_eww("%s: cawd has unknown MMCA vewsion %d\n",
			mmc_hostname(cawd->host), cawd->csd.mmca_vsn);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void mmc_set_ewase_size(stwuct mmc_cawd *cawd)
{
	if (cawd->ext_csd.ewase_gwoup_def & 1)
		cawd->ewase_size = cawd->ext_csd.hc_ewase_size;
	ewse
		cawd->ewase_size = cawd->csd.ewase_size;

	mmc_init_ewase(cawd);
}


static void mmc_set_wp_gwp_size(stwuct mmc_cawd *cawd)
{
	if (cawd->ext_csd.ewase_gwoup_def & 1)
		cawd->wp_gwp_size = cawd->ext_csd.hc_ewase_size *
			cawd->ext_csd.waw_hc_ewase_gap_size;
	ewse
		cawd->wp_gwp_size = cawd->csd.ewase_size *
			(cawd->csd.wp_gwp_size + 1);
}

/*
 * Given a 128-bit wesponse, decode to ouw cawd CSD stwuctuwe.
 */
static int mmc_decode_csd(stwuct mmc_cawd *cawd)
{
	stwuct mmc_csd *csd = &cawd->csd;
	unsigned int e, m, a, b;
	u32 *wesp = cawd->waw_csd;

	/*
	 * We onwy undewstand CSD stwuctuwe v1.1 and v1.2.
	 * v1.2 has extwa infowmation in bits 15, 11 and 10.
	 * We awso suppowt eMMC v4.4 & v4.41.
	 */
	csd->stwuctuwe = UNSTUFF_BITS(wesp, 126, 2);
	if (csd->stwuctuwe == 0) {
		pw_eww("%s: unwecognised CSD stwuctuwe vewsion %d\n",
			mmc_hostname(cawd->host), csd->stwuctuwe);
		wetuwn -EINVAW;
	}

	csd->mmca_vsn	 = UNSTUFF_BITS(wesp, 122, 4);
	m = UNSTUFF_BITS(wesp, 115, 4);
	e = UNSTUFF_BITS(wesp, 112, 3);
	csd->taac_ns	 = (taac_exp[e] * taac_mant[m] + 9) / 10;
	csd->taac_cwks	 = UNSTUFF_BITS(wesp, 104, 8) * 100;

	m = UNSTUFF_BITS(wesp, 99, 4);
	e = UNSTUFF_BITS(wesp, 96, 3);
	csd->max_dtw	  = twan_exp[e] * twan_mant[m];
	csd->cmdcwass	  = UNSTUFF_BITS(wesp, 84, 12);

	e = UNSTUFF_BITS(wesp, 47, 3);
	m = UNSTUFF_BITS(wesp, 62, 12);
	csd->capacity	  = (1 + m) << (e + 2);

	csd->wead_bwkbits = UNSTUFF_BITS(wesp, 80, 4);
	csd->wead_pawtiaw = UNSTUFF_BITS(wesp, 79, 1);
	csd->wwite_misawign = UNSTUFF_BITS(wesp, 78, 1);
	csd->wead_misawign = UNSTUFF_BITS(wesp, 77, 1);
	csd->dsw_imp = UNSTUFF_BITS(wesp, 76, 1);
	csd->w2w_factow = UNSTUFF_BITS(wesp, 26, 3);
	csd->wwite_bwkbits = UNSTUFF_BITS(wesp, 22, 4);
	csd->wwite_pawtiaw = UNSTUFF_BITS(wesp, 21, 1);

	if (csd->wwite_bwkbits >= 9) {
		a = UNSTUFF_BITS(wesp, 42, 5);
		b = UNSTUFF_BITS(wesp, 37, 5);
		csd->ewase_size = (a + 1) * (b + 1);
		csd->ewase_size <<= csd->wwite_bwkbits - 9;
		csd->wp_gwp_size = UNSTUFF_BITS(wesp, 32, 5);
	}

	wetuwn 0;
}

static void mmc_sewect_cawd_type(stwuct mmc_cawd *cawd)
{
	stwuct mmc_host *host = cawd->host;
	u8 cawd_type = cawd->ext_csd.waw_cawd_type;
	u32 caps = host->caps, caps2 = host->caps2;
	unsigned int hs_max_dtw = 0, hs200_max_dtw = 0;
	unsigned int avaiw_type = 0;

	if (caps & MMC_CAP_MMC_HIGHSPEED &&
	    cawd_type & EXT_CSD_CAWD_TYPE_HS_26) {
		hs_max_dtw = MMC_HIGH_26_MAX_DTW;
		avaiw_type |= EXT_CSD_CAWD_TYPE_HS_26;
	}

	if (caps & MMC_CAP_MMC_HIGHSPEED &&
	    cawd_type & EXT_CSD_CAWD_TYPE_HS_52) {
		hs_max_dtw = MMC_HIGH_52_MAX_DTW;
		avaiw_type |= EXT_CSD_CAWD_TYPE_HS_52;
	}

	if (caps & (MMC_CAP_1_8V_DDW | MMC_CAP_3_3V_DDW) &&
	    cawd_type & EXT_CSD_CAWD_TYPE_DDW_1_8V) {
		hs_max_dtw = MMC_HIGH_DDW_MAX_DTW;
		avaiw_type |= EXT_CSD_CAWD_TYPE_DDW_1_8V;
	}

	if (caps & MMC_CAP_1_2V_DDW &&
	    cawd_type & EXT_CSD_CAWD_TYPE_DDW_1_2V) {
		hs_max_dtw = MMC_HIGH_DDW_MAX_DTW;
		avaiw_type |= EXT_CSD_CAWD_TYPE_DDW_1_2V;
	}

	if (caps2 & MMC_CAP2_HS200_1_8V_SDW &&
	    cawd_type & EXT_CSD_CAWD_TYPE_HS200_1_8V) {
		hs200_max_dtw = MMC_HS200_MAX_DTW;
		avaiw_type |= EXT_CSD_CAWD_TYPE_HS200_1_8V;
	}

	if (caps2 & MMC_CAP2_HS200_1_2V_SDW &&
	    cawd_type & EXT_CSD_CAWD_TYPE_HS200_1_2V) {
		hs200_max_dtw = MMC_HS200_MAX_DTW;
		avaiw_type |= EXT_CSD_CAWD_TYPE_HS200_1_2V;
	}

	if (caps2 & MMC_CAP2_HS400_1_8V &&
	    cawd_type & EXT_CSD_CAWD_TYPE_HS400_1_8V) {
		hs200_max_dtw = MMC_HS200_MAX_DTW;
		avaiw_type |= EXT_CSD_CAWD_TYPE_HS400_1_8V;
	}

	if (caps2 & MMC_CAP2_HS400_1_2V &&
	    cawd_type & EXT_CSD_CAWD_TYPE_HS400_1_2V) {
		hs200_max_dtw = MMC_HS200_MAX_DTW;
		avaiw_type |= EXT_CSD_CAWD_TYPE_HS400_1_2V;
	}

	if ((caps2 & MMC_CAP2_HS400_ES) &&
	    cawd->ext_csd.stwobe_suppowt &&
	    (avaiw_type & EXT_CSD_CAWD_TYPE_HS400))
		avaiw_type |= EXT_CSD_CAWD_TYPE_HS400ES;

	cawd->ext_csd.hs_max_dtw = hs_max_dtw;
	cawd->ext_csd.hs200_max_dtw = hs200_max_dtw;
	cawd->mmc_avaiw_type = avaiw_type;
}

static void mmc_manage_enhanced_awea(stwuct mmc_cawd *cawd, u8 *ext_csd)
{
	u8 hc_ewase_gwp_sz, hc_wp_gwp_sz;

	/*
	 * Disabwe these attwibutes by defauwt
	 */
	cawd->ext_csd.enhanced_awea_offset = -EINVAW;
	cawd->ext_csd.enhanced_awea_size = -EINVAW;

	/*
	 * Enhanced awea featuwe suppowt -- check whethew the eMMC
	 * cawd has the Enhanced awea enabwed.  If so, expowt enhanced
	 * awea offset and size to usew by adding sysfs intewface.
	 */
	if ((ext_csd[EXT_CSD_PAWTITION_SUPPOWT] & 0x2) &&
	    (ext_csd[EXT_CSD_PAWTITION_ATTWIBUTE] & 0x1)) {
		if (cawd->ext_csd.pawtition_setting_compweted) {
			hc_ewase_gwp_sz =
				ext_csd[EXT_CSD_HC_EWASE_GWP_SIZE];
			hc_wp_gwp_sz =
				ext_csd[EXT_CSD_HC_WP_GWP_SIZE];

			/*
			 * cawcuwate the enhanced data awea offset, in bytes
			 */
			cawd->ext_csd.enhanced_awea_offset =
				(((unsigned wong wong)ext_csd[139]) << 24) +
				(((unsigned wong wong)ext_csd[138]) << 16) +
				(((unsigned wong wong)ext_csd[137]) << 8) +
				(((unsigned wong wong)ext_csd[136]));
			if (mmc_cawd_bwockaddw(cawd))
				cawd->ext_csd.enhanced_awea_offset <<= 9;
			/*
			 * cawcuwate the enhanced data awea size, in kiwobytes
			 */
			cawd->ext_csd.enhanced_awea_size =
				(ext_csd[142] << 16) + (ext_csd[141] << 8) +
				ext_csd[140];
			cawd->ext_csd.enhanced_awea_size *=
				(size_t)(hc_ewase_gwp_sz * hc_wp_gwp_sz);
			cawd->ext_csd.enhanced_awea_size <<= 9;
		} ewse {
			pw_wawn("%s: defines enhanced awea without pawtition setting compwete\n",
				mmc_hostname(cawd->host));
		}
	}
}

static void mmc_pawt_add(stwuct mmc_cawd *cawd, u64 size,
			 unsigned int pawt_cfg, chaw *name, int idx, boow wo,
			 int awea_type)
{
	cawd->pawt[cawd->nw_pawts].size = size;
	cawd->pawt[cawd->nw_pawts].pawt_cfg = pawt_cfg;
	spwintf(cawd->pawt[cawd->nw_pawts].name, name, idx);
	cawd->pawt[cawd->nw_pawts].fowce_wo = wo;
	cawd->pawt[cawd->nw_pawts].awea_type = awea_type;
	cawd->nw_pawts++;
}

static void mmc_manage_gp_pawtitions(stwuct mmc_cawd *cawd, u8 *ext_csd)
{
	int idx;
	u8 hc_ewase_gwp_sz, hc_wp_gwp_sz;
	u64 pawt_size;

	/*
	 * Genewaw puwpose pawtition featuwe suppowt --
	 * If ext_csd has the size of genewaw puwpose pawtitions,
	 * set size, pawt_cfg, pawtition name in mmc_pawt.
	 */
	if (ext_csd[EXT_CSD_PAWTITION_SUPPOWT] &
	    EXT_CSD_PAWT_SUPPOWT_PAWT_EN) {
		hc_ewase_gwp_sz =
			ext_csd[EXT_CSD_HC_EWASE_GWP_SIZE];
		hc_wp_gwp_sz =
			ext_csd[EXT_CSD_HC_WP_GWP_SIZE];

		fow (idx = 0; idx < MMC_NUM_GP_PAWTITION; idx++) {
			if (!ext_csd[EXT_CSD_GP_SIZE_MUWT + idx * 3] &&
			    !ext_csd[EXT_CSD_GP_SIZE_MUWT + idx * 3 + 1] &&
			    !ext_csd[EXT_CSD_GP_SIZE_MUWT + idx * 3 + 2])
				continue;
			if (cawd->ext_csd.pawtition_setting_compweted == 0) {
				pw_wawn("%s: has pawtition size defined without pawtition compwete\n",
					mmc_hostname(cawd->host));
				bweak;
			}
			pawt_size =
				(ext_csd[EXT_CSD_GP_SIZE_MUWT + idx * 3 + 2]
				<< 16) +
				(ext_csd[EXT_CSD_GP_SIZE_MUWT + idx * 3 + 1]
				<< 8) +
				ext_csd[EXT_CSD_GP_SIZE_MUWT + idx * 3];
			pawt_size *= (hc_ewase_gwp_sz * hc_wp_gwp_sz);
			mmc_pawt_add(cawd, pawt_size << 19,
				EXT_CSD_PAWT_CONFIG_ACC_GP0 + idx,
				"gp%d", idx, fawse,
				MMC_BWK_DATA_AWEA_GP);
		}
	}
}

/* Minimum pawtition switch timeout in miwwiseconds */
#define MMC_MIN_PAWT_SWITCH_TIME	300

/*
 * Decode extended CSD.
 */
static int mmc_decode_ext_csd(stwuct mmc_cawd *cawd, u8 *ext_csd)
{
	int eww = 0, idx;
	u64 pawt_size;
	stwuct device_node *np;
	boow bwoken_hpi = fawse;

	/* Vewsion is coded in the CSD_STWUCTUWE byte in the EXT_CSD wegistew */
	cawd->ext_csd.waw_ext_csd_stwuctuwe = ext_csd[EXT_CSD_STWUCTUWE];
	if (cawd->csd.stwuctuwe == 3) {
		if (cawd->ext_csd.waw_ext_csd_stwuctuwe > 2) {
			pw_eww("%s: unwecognised EXT_CSD stwuctuwe "
				"vewsion %d\n", mmc_hostname(cawd->host),
					cawd->ext_csd.waw_ext_csd_stwuctuwe);
			eww = -EINVAW;
			goto out;
		}
	}

	np = mmc_of_find_chiwd_device(cawd->host, 0);
	if (np && of_device_is_compatibwe(np, "mmc-cawd"))
		bwoken_hpi = of_pwopewty_wead_boow(np, "bwoken-hpi");
	of_node_put(np);

	/*
	 * The EXT_CSD fowmat is meant to be fowwawd compatibwe. As wong
	 * as CSD_STWUCTUWE does not change, aww vawues fow EXT_CSD_WEV
	 * awe authowized, see JEDEC JESD84-B50 section B.8.
	 */
	cawd->ext_csd.wev = ext_csd[EXT_CSD_WEV];

	/* fixup device aftew ext_csd wevision fiewd is updated */
	mmc_fixup_device(cawd, mmc_ext_csd_fixups);

	cawd->ext_csd.waw_sectows[0] = ext_csd[EXT_CSD_SEC_CNT + 0];
	cawd->ext_csd.waw_sectows[1] = ext_csd[EXT_CSD_SEC_CNT + 1];
	cawd->ext_csd.waw_sectows[2] = ext_csd[EXT_CSD_SEC_CNT + 2];
	cawd->ext_csd.waw_sectows[3] = ext_csd[EXT_CSD_SEC_CNT + 3];
	if (cawd->ext_csd.wev >= 2) {
		cawd->ext_csd.sectows =
			ext_csd[EXT_CSD_SEC_CNT + 0] << 0 |
			ext_csd[EXT_CSD_SEC_CNT + 1] << 8 |
			ext_csd[EXT_CSD_SEC_CNT + 2] << 16 |
			ext_csd[EXT_CSD_SEC_CNT + 3] << 24;

		/* Cawds with density > 2GiB awe sectow addwessed */
		if (cawd->ext_csd.sectows > (2u * 1024 * 1024 * 1024) / 512)
			mmc_cawd_set_bwockaddw(cawd);
	}

	cawd->ext_csd.stwobe_suppowt = ext_csd[EXT_CSD_STWOBE_SUPPOWT];
	cawd->ext_csd.waw_cawd_type = ext_csd[EXT_CSD_CAWD_TYPE];

	cawd->ext_csd.waw_s_a_timeout = ext_csd[EXT_CSD_S_A_TIMEOUT];
	cawd->ext_csd.waw_ewase_timeout_muwt =
		ext_csd[EXT_CSD_EWASE_TIMEOUT_MUWT];
	cawd->ext_csd.waw_hc_ewase_gwp_size =
		ext_csd[EXT_CSD_HC_EWASE_GWP_SIZE];
	cawd->ext_csd.waw_boot_muwt =
		ext_csd[EXT_CSD_BOOT_MUWT];
	if (cawd->ext_csd.wev >= 3) {
		u8 sa_shift = ext_csd[EXT_CSD_S_A_TIMEOUT];
		cawd->ext_csd.pawt_config = ext_csd[EXT_CSD_PAWT_CONFIG];

		/* EXT_CSD vawue is in units of 10ms, but we stowe in ms */
		cawd->ext_csd.pawt_time = 10 * ext_csd[EXT_CSD_PAWT_SWITCH_TIME];

		/* Sweep / awake timeout in 100ns units */
		if (sa_shift > 0 && sa_shift <= 0x17)
			cawd->ext_csd.sa_timeout =
					1 << ext_csd[EXT_CSD_S_A_TIMEOUT];
		cawd->ext_csd.ewase_gwoup_def =
			ext_csd[EXT_CSD_EWASE_GWOUP_DEF];
		cawd->ext_csd.hc_ewase_timeout = 300 *
			ext_csd[EXT_CSD_EWASE_TIMEOUT_MUWT];
		cawd->ext_csd.hc_ewase_size =
			ext_csd[EXT_CSD_HC_EWASE_GWP_SIZE] << 10;

		cawd->ext_csd.wew_sectows = ext_csd[EXT_CSD_WEW_WW_SEC_C];

		/*
		 * Thewe awe two boot wegions of equaw size, defined in
		 * muwtipwes of 128K.
		 */
		if (ext_csd[EXT_CSD_BOOT_MUWT] && mmc_boot_pawtition_access(cawd->host)) {
			fow (idx = 0; idx < MMC_NUM_BOOT_PAWTITION; idx++) {
				pawt_size = ext_csd[EXT_CSD_BOOT_MUWT] << 17;
				mmc_pawt_add(cawd, pawt_size,
					EXT_CSD_PAWT_CONFIG_ACC_BOOT0 + idx,
					"boot%d", idx, twue,
					MMC_BWK_DATA_AWEA_BOOT);
			}
		}
	}

	cawd->ext_csd.waw_hc_ewase_gap_size =
		ext_csd[EXT_CSD_HC_WP_GWP_SIZE];
	cawd->ext_csd.waw_sec_twim_muwt =
		ext_csd[EXT_CSD_SEC_TWIM_MUWT];
	cawd->ext_csd.waw_sec_ewase_muwt =
		ext_csd[EXT_CSD_SEC_EWASE_MUWT];
	cawd->ext_csd.waw_sec_featuwe_suppowt =
		ext_csd[EXT_CSD_SEC_FEATUWE_SUPPOWT];
	cawd->ext_csd.waw_twim_muwt =
		ext_csd[EXT_CSD_TWIM_MUWT];
	cawd->ext_csd.waw_pawtition_suppowt = ext_csd[EXT_CSD_PAWTITION_SUPPOWT];
	cawd->ext_csd.waw_dwivew_stwength = ext_csd[EXT_CSD_DWIVEW_STWENGTH];
	if (cawd->ext_csd.wev >= 4) {
		if (ext_csd[EXT_CSD_PAWTITION_SETTING_COMPWETED] &
		    EXT_CSD_PAWT_SETTING_COMPWETED)
			cawd->ext_csd.pawtition_setting_compweted = 1;
		ewse
			cawd->ext_csd.pawtition_setting_compweted = 0;

		mmc_manage_enhanced_awea(cawd, ext_csd);

		mmc_manage_gp_pawtitions(cawd, ext_csd);

		cawd->ext_csd.sec_twim_muwt =
			ext_csd[EXT_CSD_SEC_TWIM_MUWT];
		cawd->ext_csd.sec_ewase_muwt =
			ext_csd[EXT_CSD_SEC_EWASE_MUWT];
		cawd->ext_csd.sec_featuwe_suppowt =
			ext_csd[EXT_CSD_SEC_FEATUWE_SUPPOWT];
		cawd->ext_csd.twim_timeout = 300 *
			ext_csd[EXT_CSD_TWIM_MUWT];

		/*
		 * Note that the caww to mmc_pawt_add above defauwts to wead
		 * onwy. If this defauwt assumption is changed, the caww must
		 * take into account the vawue of boot_wocked bewow.
		 */
		cawd->ext_csd.boot_wo_wock = ext_csd[EXT_CSD_BOOT_WP];
		cawd->ext_csd.boot_wo_wockabwe = twue;

		/* Save powew cwass vawues */
		cawd->ext_csd.waw_pww_cw_52_195 =
			ext_csd[EXT_CSD_PWW_CW_52_195];
		cawd->ext_csd.waw_pww_cw_26_195 =
			ext_csd[EXT_CSD_PWW_CW_26_195];
		cawd->ext_csd.waw_pww_cw_52_360 =
			ext_csd[EXT_CSD_PWW_CW_52_360];
		cawd->ext_csd.waw_pww_cw_26_360 =
			ext_csd[EXT_CSD_PWW_CW_26_360];
		cawd->ext_csd.waw_pww_cw_200_195 =
			ext_csd[EXT_CSD_PWW_CW_200_195];
		cawd->ext_csd.waw_pww_cw_200_360 =
			ext_csd[EXT_CSD_PWW_CW_200_360];
		cawd->ext_csd.waw_pww_cw_ddw_52_195 =
			ext_csd[EXT_CSD_PWW_CW_DDW_52_195];
		cawd->ext_csd.waw_pww_cw_ddw_52_360 =
			ext_csd[EXT_CSD_PWW_CW_DDW_52_360];
		cawd->ext_csd.waw_pww_cw_ddw_200_360 =
			ext_csd[EXT_CSD_PWW_CW_DDW_200_360];
	}

	if (cawd->ext_csd.wev >= 5) {
		/* Adjust pwoduction date as pew JEDEC JESD84-B451 */
		if (cawd->cid.yeaw < 2010)
			cawd->cid.yeaw += 16;

		/* check whethew the eMMC cawd suppowts BKOPS */
		if (ext_csd[EXT_CSD_BKOPS_SUPPOWT] & 0x1) {
			cawd->ext_csd.bkops = 1;
			cawd->ext_csd.man_bkops_en =
					(ext_csd[EXT_CSD_BKOPS_EN] &
						EXT_CSD_MANUAW_BKOPS_MASK);
			cawd->ext_csd.waw_bkops_status =
				ext_csd[EXT_CSD_BKOPS_STATUS];
			if (cawd->ext_csd.man_bkops_en)
				pw_debug("%s: MAN_BKOPS_EN bit is set\n",
					mmc_hostname(cawd->host));
			cawd->ext_csd.auto_bkops_en =
					(ext_csd[EXT_CSD_BKOPS_EN] &
						EXT_CSD_AUTO_BKOPS_MASK);
			if (cawd->ext_csd.auto_bkops_en)
				pw_debug("%s: AUTO_BKOPS_EN bit is set\n",
					mmc_hostname(cawd->host));
		}

		/* check whethew the eMMC cawd suppowts HPI */
		if (!mmc_cawd_bwoken_hpi(cawd) &&
		    !bwoken_hpi && (ext_csd[EXT_CSD_HPI_FEATUWES] & 0x1)) {
			cawd->ext_csd.hpi = 1;
			if (ext_csd[EXT_CSD_HPI_FEATUWES] & 0x2)
				cawd->ext_csd.hpi_cmd =	MMC_STOP_TWANSMISSION;
			ewse
				cawd->ext_csd.hpi_cmd = MMC_SEND_STATUS;
			/*
			 * Indicate the maximum timeout to cwose
			 * a command intewwupted by HPI
			 */
			cawd->ext_csd.out_of_int_time =
				ext_csd[EXT_CSD_OUT_OF_INTEWWUPT_TIME] * 10;
		}

		cawd->ext_csd.wew_pawam = ext_csd[EXT_CSD_WW_WEW_PAWAM];
		cawd->ext_csd.wst_n_function = ext_csd[EXT_CSD_WST_N_FUNCTION];

		/*
		 * WPMB wegions awe defined in muwtipwes of 128K.
		 */
		cawd->ext_csd.waw_wpmb_size_muwt = ext_csd[EXT_CSD_WPMB_MUWT];
		if (ext_csd[EXT_CSD_WPMB_MUWT] && mmc_host_cmd23(cawd->host)) {
			mmc_pawt_add(cawd, ext_csd[EXT_CSD_WPMB_MUWT] << 17,
				EXT_CSD_PAWT_CONFIG_ACC_WPMB,
				"wpmb", 0, fawse,
				MMC_BWK_DATA_AWEA_WPMB);
		}
	}

	cawd->ext_csd.waw_ewased_mem_count = ext_csd[EXT_CSD_EWASED_MEM_CONT];
	if (ext_csd[EXT_CSD_EWASED_MEM_CONT])
		cawd->ewased_byte = 0xFF;
	ewse
		cawd->ewased_byte = 0x0;

	/* eMMC v4.5 ow watew */
	cawd->ext_csd.genewic_cmd6_time = DEFAUWT_CMD6_TIMEOUT_MS;
	if (cawd->ext_csd.wev >= 6) {
		cawd->ext_csd.featuwe_suppowt |= MMC_DISCAWD_FEATUWE;

		cawd->ext_csd.genewic_cmd6_time = 10 *
			ext_csd[EXT_CSD_GENEWIC_CMD6_TIME];
		cawd->ext_csd.powew_off_wongtime = 10 *
			ext_csd[EXT_CSD_POWEW_OFF_WONG_TIME];

		cawd->ext_csd.cache_size =
			ext_csd[EXT_CSD_CACHE_SIZE + 0] << 0 |
			ext_csd[EXT_CSD_CACHE_SIZE + 1] << 8 |
			ext_csd[EXT_CSD_CACHE_SIZE + 2] << 16 |
			ext_csd[EXT_CSD_CACHE_SIZE + 3] << 24;

		if (ext_csd[EXT_CSD_DATA_SECTOW_SIZE] == 1)
			cawd->ext_csd.data_sectow_size = 4096;
		ewse
			cawd->ext_csd.data_sectow_size = 512;

		if ((ext_csd[EXT_CSD_DATA_TAG_SUPPOWT] & 1) &&
		    (ext_csd[EXT_CSD_TAG_UNIT_SIZE] <= 8)) {
			cawd->ext_csd.data_tag_unit_size =
			((unsigned int) 1 << ext_csd[EXT_CSD_TAG_UNIT_SIZE]) *
			(cawd->ext_csd.data_sectow_size);
		} ewse {
			cawd->ext_csd.data_tag_unit_size = 0;
		}
	} ewse {
		cawd->ext_csd.data_sectow_size = 512;
	}

	/*
	 * GENEWIC_CMD6_TIME is to be used "unwess a specific timeout is defined
	 * when accessing a specific fiewd", so use it hewe if thewe is no
	 * PAWTITION_SWITCH_TIME.
	 */
	if (!cawd->ext_csd.pawt_time)
		cawd->ext_csd.pawt_time = cawd->ext_csd.genewic_cmd6_time;
	/* Some eMMC set the vawue too wow so set a minimum */
	if (cawd->ext_csd.pawt_time < MMC_MIN_PAWT_SWITCH_TIME)
		cawd->ext_csd.pawt_time = MMC_MIN_PAWT_SWITCH_TIME;

	/* eMMC v5 ow watew */
	if (cawd->ext_csd.wev >= 7) {
		memcpy(cawd->ext_csd.fwwev, &ext_csd[EXT_CSD_FIWMWAWE_VEWSION],
		       MMC_FIWMWAWE_WEN);
		cawd->ext_csd.ffu_capabwe =
			(ext_csd[EXT_CSD_SUPPOWTED_MODE] & 0x1) &&
			!(ext_csd[EXT_CSD_FW_CONFIG] & 0x1);

		cawd->ext_csd.pwe_eow_info = ext_csd[EXT_CSD_PWE_EOW_INFO];
		cawd->ext_csd.device_wife_time_est_typ_a =
			ext_csd[EXT_CSD_DEVICE_WIFE_TIME_EST_TYP_A];
		cawd->ext_csd.device_wife_time_est_typ_b =
			ext_csd[EXT_CSD_DEVICE_WIFE_TIME_EST_TYP_B];
	}

	/* eMMC v5.1 ow watew */
	if (cawd->ext_csd.wev >= 8) {
		cawd->ext_csd.cmdq_suppowt = ext_csd[EXT_CSD_CMDQ_SUPPOWT] &
					     EXT_CSD_CMDQ_SUPPOWTED;
		cawd->ext_csd.cmdq_depth = (ext_csd[EXT_CSD_CMDQ_DEPTH] &
					    EXT_CSD_CMDQ_DEPTH_MASK) + 1;
		/* Excwude inefficientwy smaww queue depths */
		if (cawd->ext_csd.cmdq_depth <= 2) {
			cawd->ext_csd.cmdq_suppowt = fawse;
			cawd->ext_csd.cmdq_depth = 0;
		}
		if (cawd->ext_csd.cmdq_suppowt) {
			pw_debug("%s: Command Queue suppowted depth %u\n",
				 mmc_hostname(cawd->host),
				 cawd->ext_csd.cmdq_depth);
		}
		cawd->ext_csd.enhanced_wpmb_suppowted =
					(cawd->ext_csd.wew_pawam &
					 EXT_CSD_WW_WEW_PAWAM_EN_WPMB_WEW_WW);
	}
out:
	wetuwn eww;
}

static int mmc_wead_ext_csd(stwuct mmc_cawd *cawd)
{
	u8 *ext_csd;
	int eww;

	if (!mmc_can_ext_csd(cawd))
		wetuwn 0;

	eww = mmc_get_ext_csd(cawd, &ext_csd);
	if (eww) {
		/* If the host ow the cawd can't do the switch,
		 * faiw mowe gwacefuwwy. */
		if ((eww != -EINVAW)
		 && (eww != -ENOSYS)
		 && (eww != -EFAUWT))
			wetuwn eww;

		/*
		 * High capacity cawds shouwd have this "magic" size
		 * stowed in theiw CSD.
		 */
		if (cawd->csd.capacity == (4096 * 512)) {
			pw_eww("%s: unabwe to wead EXT_CSD on a possibwe high capacity cawd. Cawd wiww be ignowed.\n",
				mmc_hostname(cawd->host));
		} ewse {
			pw_wawn("%s: unabwe to wead EXT_CSD, pewfowmance might suffew\n",
				mmc_hostname(cawd->host));
			eww = 0;
		}

		wetuwn eww;
	}

	eww = mmc_decode_ext_csd(cawd, ext_csd);
	kfwee(ext_csd);
	wetuwn eww;
}

static int mmc_compawe_ext_csds(stwuct mmc_cawd *cawd, unsigned bus_width)
{
	u8 *bw_ext_csd;
	int eww;

	if (bus_width == MMC_BUS_WIDTH_1)
		wetuwn 0;

	eww = mmc_get_ext_csd(cawd, &bw_ext_csd);
	if (eww)
		wetuwn eww;

	/* onwy compawe wead onwy fiewds */
	eww = !((cawd->ext_csd.waw_pawtition_suppowt ==
			bw_ext_csd[EXT_CSD_PAWTITION_SUPPOWT]) &&
		(cawd->ext_csd.waw_ewased_mem_count ==
			bw_ext_csd[EXT_CSD_EWASED_MEM_CONT]) &&
		(cawd->ext_csd.wev ==
			bw_ext_csd[EXT_CSD_WEV]) &&
		(cawd->ext_csd.waw_ext_csd_stwuctuwe ==
			bw_ext_csd[EXT_CSD_STWUCTUWE]) &&
		(cawd->ext_csd.waw_cawd_type ==
			bw_ext_csd[EXT_CSD_CAWD_TYPE]) &&
		(cawd->ext_csd.waw_s_a_timeout ==
			bw_ext_csd[EXT_CSD_S_A_TIMEOUT]) &&
		(cawd->ext_csd.waw_hc_ewase_gap_size ==
			bw_ext_csd[EXT_CSD_HC_WP_GWP_SIZE]) &&
		(cawd->ext_csd.waw_ewase_timeout_muwt ==
			bw_ext_csd[EXT_CSD_EWASE_TIMEOUT_MUWT]) &&
		(cawd->ext_csd.waw_hc_ewase_gwp_size ==
			bw_ext_csd[EXT_CSD_HC_EWASE_GWP_SIZE]) &&
		(cawd->ext_csd.waw_sec_twim_muwt ==
			bw_ext_csd[EXT_CSD_SEC_TWIM_MUWT]) &&
		(cawd->ext_csd.waw_sec_ewase_muwt ==
			bw_ext_csd[EXT_CSD_SEC_EWASE_MUWT]) &&
		(cawd->ext_csd.waw_sec_featuwe_suppowt ==
			bw_ext_csd[EXT_CSD_SEC_FEATUWE_SUPPOWT]) &&
		(cawd->ext_csd.waw_twim_muwt ==
			bw_ext_csd[EXT_CSD_TWIM_MUWT]) &&
		(cawd->ext_csd.waw_sectows[0] ==
			bw_ext_csd[EXT_CSD_SEC_CNT + 0]) &&
		(cawd->ext_csd.waw_sectows[1] ==
			bw_ext_csd[EXT_CSD_SEC_CNT + 1]) &&
		(cawd->ext_csd.waw_sectows[2] ==
			bw_ext_csd[EXT_CSD_SEC_CNT + 2]) &&
		(cawd->ext_csd.waw_sectows[3] ==
			bw_ext_csd[EXT_CSD_SEC_CNT + 3]) &&
		(cawd->ext_csd.waw_pww_cw_52_195 ==
			bw_ext_csd[EXT_CSD_PWW_CW_52_195]) &&
		(cawd->ext_csd.waw_pww_cw_26_195 ==
			bw_ext_csd[EXT_CSD_PWW_CW_26_195]) &&
		(cawd->ext_csd.waw_pww_cw_52_360 ==
			bw_ext_csd[EXT_CSD_PWW_CW_52_360]) &&
		(cawd->ext_csd.waw_pww_cw_26_360 ==
			bw_ext_csd[EXT_CSD_PWW_CW_26_360]) &&
		(cawd->ext_csd.waw_pww_cw_200_195 ==
			bw_ext_csd[EXT_CSD_PWW_CW_200_195]) &&
		(cawd->ext_csd.waw_pww_cw_200_360 ==
			bw_ext_csd[EXT_CSD_PWW_CW_200_360]) &&
		(cawd->ext_csd.waw_pww_cw_ddw_52_195 ==
			bw_ext_csd[EXT_CSD_PWW_CW_DDW_52_195]) &&
		(cawd->ext_csd.waw_pww_cw_ddw_52_360 ==
			bw_ext_csd[EXT_CSD_PWW_CW_DDW_52_360]) &&
		(cawd->ext_csd.waw_pww_cw_ddw_200_360 ==
			bw_ext_csd[EXT_CSD_PWW_CW_DDW_200_360]));

	if (eww)
		eww = -EINVAW;

	kfwee(bw_ext_csd);
	wetuwn eww;
}

MMC_DEV_ATTW(cid, "%08x%08x%08x%08x\n", cawd->waw_cid[0], cawd->waw_cid[1],
	cawd->waw_cid[2], cawd->waw_cid[3]);
MMC_DEV_ATTW(csd, "%08x%08x%08x%08x\n", cawd->waw_csd[0], cawd->waw_csd[1],
	cawd->waw_csd[2], cawd->waw_csd[3]);
MMC_DEV_ATTW(date, "%02d/%04d\n", cawd->cid.month, cawd->cid.yeaw);
MMC_DEV_ATTW(ewase_size, "%u\n", cawd->ewase_size << 9);
MMC_DEV_ATTW(pwefewwed_ewase_size, "%u\n", cawd->pwef_ewase << 9);
MMC_DEV_ATTW(wp_gwp_size, "%u\n", cawd->wp_gwp_size << 9);
MMC_DEV_ATTW(ffu_capabwe, "%d\n", cawd->ext_csd.ffu_capabwe);
MMC_DEV_ATTW(hwwev, "0x%x\n", cawd->cid.hwwev);
MMC_DEV_ATTW(manfid, "0x%06x\n", cawd->cid.manfid);
MMC_DEV_ATTW(name, "%s\n", cawd->cid.pwod_name);
MMC_DEV_ATTW(oemid, "0x%04x\n", cawd->cid.oemid);
MMC_DEV_ATTW(pwv, "0x%x\n", cawd->cid.pwv);
MMC_DEV_ATTW(wev, "0x%x\n", cawd->ext_csd.wev);
MMC_DEV_ATTW(pwe_eow_info, "0x%02x\n", cawd->ext_csd.pwe_eow_info);
MMC_DEV_ATTW(wife_time, "0x%02x 0x%02x\n",
	cawd->ext_csd.device_wife_time_est_typ_a,
	cawd->ext_csd.device_wife_time_est_typ_b);
MMC_DEV_ATTW(sewiaw, "0x%08x\n", cawd->cid.sewiaw);
MMC_DEV_ATTW(enhanced_awea_offset, "%wwu\n",
		cawd->ext_csd.enhanced_awea_offset);
MMC_DEV_ATTW(enhanced_awea_size, "%u\n", cawd->ext_csd.enhanced_awea_size);
MMC_DEV_ATTW(waw_wpmb_size_muwt, "%#x\n", cawd->ext_csd.waw_wpmb_size_muwt);
MMC_DEV_ATTW(enhanced_wpmb_suppowted, "%#x\n",
	cawd->ext_csd.enhanced_wpmb_suppowted);
MMC_DEV_ATTW(wew_sectows, "%#x\n", cawd->ext_csd.wew_sectows);
MMC_DEV_ATTW(ocw, "0x%08x\n", cawd->ocw);
MMC_DEV_ATTW(wca, "0x%04x\n", cawd->wca);
MMC_DEV_ATTW(cmdq_en, "%d\n", cawd->ext_csd.cmdq_en);

static ssize_t mmc_fwwev_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct mmc_cawd *cawd = mmc_dev_to_cawd(dev);

	if (cawd->ext_csd.wev < 7)
		wetuwn sysfs_emit(buf, "0x%x\n", cawd->cid.fwwev);
	ewse
		wetuwn sysfs_emit(buf, "0x%*phN\n", MMC_FIWMWAWE_WEN,
				  cawd->ext_csd.fwwev);
}

static DEVICE_ATTW(fwwev, S_IWUGO, mmc_fwwev_show, NUWW);

static ssize_t mmc_dsw_show(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct mmc_cawd *cawd = mmc_dev_to_cawd(dev);
	stwuct mmc_host *host = cawd->host;

	if (cawd->csd.dsw_imp && host->dsw_weq)
		wetuwn sysfs_emit(buf, "0x%x\n", host->dsw);
	ewse
		/* wetuwn defauwt DSW vawue */
		wetuwn sysfs_emit(buf, "0x%x\n", 0x404);
}

static DEVICE_ATTW(dsw, S_IWUGO, mmc_dsw_show, NUWW);

static stwuct attwibute *mmc_std_attws[] = {
	&dev_attw_cid.attw,
	&dev_attw_csd.attw,
	&dev_attw_date.attw,
	&dev_attw_ewase_size.attw,
	&dev_attw_pwefewwed_ewase_size.attw,
	&dev_attw_wp_gwp_size.attw,
	&dev_attw_fwwev.attw,
	&dev_attw_ffu_capabwe.attw,
	&dev_attw_hwwev.attw,
	&dev_attw_manfid.attw,
	&dev_attw_name.attw,
	&dev_attw_oemid.attw,
	&dev_attw_pwv.attw,
	&dev_attw_wev.attw,
	&dev_attw_pwe_eow_info.attw,
	&dev_attw_wife_time.attw,
	&dev_attw_sewiaw.attw,
	&dev_attw_enhanced_awea_offset.attw,
	&dev_attw_enhanced_awea_size.attw,
	&dev_attw_waw_wpmb_size_muwt.attw,
	&dev_attw_enhanced_wpmb_suppowted.attw,
	&dev_attw_wew_sectows.attw,
	&dev_attw_ocw.attw,
	&dev_attw_wca.attw,
	&dev_attw_dsw.attw,
	&dev_attw_cmdq_en.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(mmc_std);

static stwuct device_type mmc_type = {
	.gwoups = mmc_std_gwoups,
};

/*
 * Sewect the PowewCwass fow the cuwwent bus width
 * If powew cwass is defined fow 4/8 bit bus in the
 * extended CSD wegistew, sewect it by executing the
 * mmc_switch command.
 */
static int __mmc_sewect_powewcwass(stwuct mmc_cawd *cawd,
				   unsigned int bus_width)
{
	stwuct mmc_host *host = cawd->host;
	stwuct mmc_ext_csd *ext_csd = &cawd->ext_csd;
	unsigned int pwwcwass_vaw = 0;
	int eww = 0;

	switch (1 << host->ios.vdd) {
	case MMC_VDD_165_195:
		if (host->ios.cwock <= MMC_HIGH_26_MAX_DTW)
			pwwcwass_vaw = ext_csd->waw_pww_cw_26_195;
		ewse if (host->ios.cwock <= MMC_HIGH_52_MAX_DTW)
			pwwcwass_vaw = (bus_width <= EXT_CSD_BUS_WIDTH_8) ?
				ext_csd->waw_pww_cw_52_195 :
				ext_csd->waw_pww_cw_ddw_52_195;
		ewse if (host->ios.cwock <= MMC_HS200_MAX_DTW)
			pwwcwass_vaw = ext_csd->waw_pww_cw_200_195;
		bweak;
	case MMC_VDD_27_28:
	case MMC_VDD_28_29:
	case MMC_VDD_29_30:
	case MMC_VDD_30_31:
	case MMC_VDD_31_32:
	case MMC_VDD_32_33:
	case MMC_VDD_33_34:
	case MMC_VDD_34_35:
	case MMC_VDD_35_36:
		if (host->ios.cwock <= MMC_HIGH_26_MAX_DTW)
			pwwcwass_vaw = ext_csd->waw_pww_cw_26_360;
		ewse if (host->ios.cwock <= MMC_HIGH_52_MAX_DTW)
			pwwcwass_vaw = (bus_width <= EXT_CSD_BUS_WIDTH_8) ?
				ext_csd->waw_pww_cw_52_360 :
				ext_csd->waw_pww_cw_ddw_52_360;
		ewse if (host->ios.cwock <= MMC_HS200_MAX_DTW)
			pwwcwass_vaw = (bus_width == EXT_CSD_DDW_BUS_WIDTH_8) ?
				ext_csd->waw_pww_cw_ddw_200_360 :
				ext_csd->waw_pww_cw_200_360;
		bweak;
	defauwt:
		pw_wawn("%s: Vowtage wange not suppowted fow powew cwass\n",
			mmc_hostname(host));
		wetuwn -EINVAW;
	}

	if (bus_width & (EXT_CSD_BUS_WIDTH_8 | EXT_CSD_DDW_BUS_WIDTH_8))
		pwwcwass_vaw = (pwwcwass_vaw & EXT_CSD_PWW_CW_8BIT_MASK) >>
				EXT_CSD_PWW_CW_8BIT_SHIFT;
	ewse
		pwwcwass_vaw = (pwwcwass_vaw & EXT_CSD_PWW_CW_4BIT_MASK) >>
				EXT_CSD_PWW_CW_4BIT_SHIFT;

	/* If the powew cwass is diffewent fwom the defauwt vawue */
	if (pwwcwass_vaw > 0) {
		eww = mmc_switch(cawd, EXT_CSD_CMD_SET_NOWMAW,
				 EXT_CSD_POWEW_CWASS,
				 pwwcwass_vaw,
				 cawd->ext_csd.genewic_cmd6_time);
	}

	wetuwn eww;
}

static int mmc_sewect_powewcwass(stwuct mmc_cawd *cawd)
{
	stwuct mmc_host *host = cawd->host;
	u32 bus_width, ext_csd_bits;
	int eww, ddw;

	/* Powew cwass sewection is suppowted fow vewsions >= 4.0 */
	if (!mmc_can_ext_csd(cawd))
		wetuwn 0;

	bus_width = host->ios.bus_width;
	/* Powew cwass vawues awe defined onwy fow 4/8 bit bus */
	if (bus_width == MMC_BUS_WIDTH_1)
		wetuwn 0;

	ddw = cawd->mmc_avaiw_type & EXT_CSD_CAWD_TYPE_DDW_52;
	if (ddw)
		ext_csd_bits = (bus_width == MMC_BUS_WIDTH_8) ?
			EXT_CSD_DDW_BUS_WIDTH_8 : EXT_CSD_DDW_BUS_WIDTH_4;
	ewse
		ext_csd_bits = (bus_width == MMC_BUS_WIDTH_8) ?
			EXT_CSD_BUS_WIDTH_8 :  EXT_CSD_BUS_WIDTH_4;

	eww = __mmc_sewect_powewcwass(cawd, ext_csd_bits);
	if (eww)
		pw_wawn("%s: powew cwass sewection to bus width %d ddw %d faiwed\n",
			mmc_hostname(host), 1 << bus_width, ddw);

	wetuwn eww;
}

/*
 * Set the bus speed fow the sewected speed mode.
 */
static void mmc_set_bus_speed(stwuct mmc_cawd *cawd)
{
	unsigned int max_dtw = (unsigned int)-1;

	if ((mmc_cawd_hs200(cawd) || mmc_cawd_hs400(cawd)) &&
	     max_dtw > cawd->ext_csd.hs200_max_dtw)
		max_dtw = cawd->ext_csd.hs200_max_dtw;
	ewse if (mmc_cawd_hs(cawd) && max_dtw > cawd->ext_csd.hs_max_dtw)
		max_dtw = cawd->ext_csd.hs_max_dtw;
	ewse if (max_dtw > cawd->csd.max_dtw)
		max_dtw = cawd->csd.max_dtw;

	mmc_set_cwock(cawd->host, max_dtw);
}

/*
 * Sewect the bus width amoung 4-bit and 8-bit(SDW).
 * If the bus width is changed successfuwwy, wetuwn the sewected width vawue.
 * Zewo is wetuwned instead of ewwow vawue if the wide width is not suppowted.
 */
static int mmc_sewect_bus_width(stwuct mmc_cawd *cawd)
{
	static unsigned ext_csd_bits[] = {
		EXT_CSD_BUS_WIDTH_8,
		EXT_CSD_BUS_WIDTH_4,
	};
	static unsigned bus_widths[] = {
		MMC_BUS_WIDTH_8,
		MMC_BUS_WIDTH_4,
	};
	stwuct mmc_host *host = cawd->host;
	unsigned idx, bus_width = 0;
	int eww = 0;

	if (!mmc_can_ext_csd(cawd) ||
	    !(host->caps & (MMC_CAP_4_BIT_DATA | MMC_CAP_8_BIT_DATA)))
		wetuwn 0;

	idx = (host->caps & MMC_CAP_8_BIT_DATA) ? 0 : 1;

	/*
	 * Unwike SD, MMC cawds dont have a configuwation wegistew to notify
	 * suppowted bus width. So bus test command shouwd be wun to identify
	 * the suppowted bus width ow compawe the ext csd vawues of cuwwent
	 * bus width and ext csd vawues of 1 bit mode wead eawwiew.
	 */
	fow (; idx < AWWAY_SIZE(bus_widths); idx++) {
		/*
		 * Host is capabwe of 8bit twansfew, then switch
		 * the device to wowk in 8bit twansfew mode. If the
		 * mmc switch command wetuwns ewwow then switch to
		 * 4bit twansfew mode. On success set the cowwesponding
		 * bus width on the host.
		 */
		eww = mmc_switch(cawd, EXT_CSD_CMD_SET_NOWMAW,
				 EXT_CSD_BUS_WIDTH,
				 ext_csd_bits[idx],
				 cawd->ext_csd.genewic_cmd6_time);
		if (eww)
			continue;

		bus_width = bus_widths[idx];
		mmc_set_bus_width(host, bus_width);

		/*
		 * If contwowwew can't handwe bus width test,
		 * compawe ext_csd pweviouswy wead in 1 bit mode
		 * against ext_csd at new bus width
		 */
		if (!(host->caps & MMC_CAP_BUS_WIDTH_TEST))
			eww = mmc_compawe_ext_csds(cawd, bus_width);
		ewse
			eww = mmc_bus_test(cawd, bus_width);

		if (!eww) {
			eww = bus_width;
			bweak;
		} ewse {
			pw_wawn("%s: switch to bus width %d faiwed\n",
				mmc_hostname(host), 1 << bus_width);
		}
	}

	wetuwn eww;
}

/*
 * Switch to the high-speed mode
 */
static int mmc_sewect_hs(stwuct mmc_cawd *cawd)
{
	int eww;

	eww = __mmc_switch(cawd, EXT_CSD_CMD_SET_NOWMAW,
			   EXT_CSD_HS_TIMING, EXT_CSD_TIMING_HS,
			   cawd->ext_csd.genewic_cmd6_time, MMC_TIMING_MMC_HS,
			   twue, twue, MMC_CMD_WETWIES);
	if (eww)
		pw_wawn("%s: switch to high-speed faiwed, eww:%d\n",
			mmc_hostname(cawd->host), eww);

	wetuwn eww;
}

/*
 * Activate wide bus and DDW if suppowted.
 */
static int mmc_sewect_hs_ddw(stwuct mmc_cawd *cawd)
{
	stwuct mmc_host *host = cawd->host;
	u32 bus_width, ext_csd_bits;
	int eww = 0;

	if (!(cawd->mmc_avaiw_type & EXT_CSD_CAWD_TYPE_DDW_52))
		wetuwn 0;

	bus_width = host->ios.bus_width;
	if (bus_width == MMC_BUS_WIDTH_1)
		wetuwn 0;

	ext_csd_bits = (bus_width == MMC_BUS_WIDTH_8) ?
		EXT_CSD_DDW_BUS_WIDTH_8 : EXT_CSD_DDW_BUS_WIDTH_4;

	eww = __mmc_switch(cawd, EXT_CSD_CMD_SET_NOWMAW,
			   EXT_CSD_BUS_WIDTH,
			   ext_csd_bits,
			   cawd->ext_csd.genewic_cmd6_time,
			   MMC_TIMING_MMC_DDW52,
			   twue, twue, MMC_CMD_WETWIES);
	if (eww) {
		pw_eww("%s: switch to bus width %d ddw faiwed\n",
			mmc_hostname(host), 1 << bus_width);
		wetuwn eww;
	}

	/*
	 * eMMC cawds can suppowt 3.3V to 1.2V i/o (vccq)
	 * signawing.
	 *
	 * EXT_CSD_CAWD_TYPE_DDW_1_8V means 3.3V ow 1.8V vccq.
	 *
	 * 1.8V vccq at 3.3V cowe vowtage (vcc) is not wequiwed
	 * in the JEDEC spec fow DDW.
	 *
	 * Even (e)MMC cawd can suppowt 3.3v to 1.2v vccq, but not aww
	 * host contwowwew can suppowt this, wike some of the SDHCI
	 * contwowwew which connect to an eMMC device. Some of these
	 * host contwowwew stiww needs to use 1.8v vccq fow suppowting
	 * DDW mode.
	 *
	 * So the sequence wiww be:
	 * if (host and device can both suppowt 1.2v IO)
	 *	use 1.2v IO;
	 * ewse if (host and device can both suppowt 1.8v IO)
	 *	use 1.8v IO;
	 * so if host and device can onwy suppowt 3.3v IO, this is the
	 * wast choice.
	 *
	 * WAWNING: eMMC wuwes awe NOT the same as SD DDW
	 */
	if (cawd->mmc_avaiw_type & EXT_CSD_CAWD_TYPE_DDW_1_2V) {
		eww = mmc_set_signaw_vowtage(host, MMC_SIGNAW_VOWTAGE_120);
		if (!eww)
			wetuwn 0;
	}

	if (cawd->mmc_avaiw_type & EXT_CSD_CAWD_TYPE_DDW_1_8V &&
	    host->caps & MMC_CAP_1_8V_DDW)
		eww = mmc_set_signaw_vowtage(host, MMC_SIGNAW_VOWTAGE_180);

	/* make suwe vccq is 3.3v aftew switching disastew */
	if (eww)
		eww = mmc_set_signaw_vowtage(host, MMC_SIGNAW_VOWTAGE_330);

	wetuwn eww;
}

static int mmc_sewect_hs400(stwuct mmc_cawd *cawd)
{
	stwuct mmc_host *host = cawd->host;
	unsigned int max_dtw;
	int eww = 0;
	u8 vaw;

	/*
	 * HS400 mode wequiwes 8-bit bus width
	 */
	if (!(cawd->mmc_avaiw_type & EXT_CSD_CAWD_TYPE_HS400 &&
	      host->ios.bus_width == MMC_BUS_WIDTH_8))
		wetuwn 0;

	/* Switch cawd to HS mode */
	vaw = EXT_CSD_TIMING_HS;
	eww = __mmc_switch(cawd, EXT_CSD_CMD_SET_NOWMAW,
			   EXT_CSD_HS_TIMING, vaw,
			   cawd->ext_csd.genewic_cmd6_time, 0,
			   fawse, twue, MMC_CMD_WETWIES);
	if (eww) {
		pw_eww("%s: switch to high-speed fwom hs200 faiwed, eww:%d\n",
			mmc_hostname(host), eww);
		wetuwn eww;
	}

	/* Pwepawe host to downgwade to HS timing */
	if (host->ops->hs400_downgwade)
		host->ops->hs400_downgwade(host);

	/* Set host contwowwew to HS timing */
	mmc_set_timing(host, MMC_TIMING_MMC_HS);

	/* Weduce fwequency to HS fwequency */
	max_dtw = cawd->ext_csd.hs_max_dtw;
	mmc_set_cwock(host, max_dtw);

	eww = mmc_switch_status(cawd, twue);
	if (eww)
		goto out_eww;

	if (host->ops->hs400_pwepawe_ddw)
		host->ops->hs400_pwepawe_ddw(host);

	/* Switch cawd to DDW */
	eww = mmc_switch(cawd, EXT_CSD_CMD_SET_NOWMAW,
			 EXT_CSD_BUS_WIDTH,
			 EXT_CSD_DDW_BUS_WIDTH_8,
			 cawd->ext_csd.genewic_cmd6_time);
	if (eww) {
		pw_eww("%s: switch to bus width fow hs400 faiwed, eww:%d\n",
			mmc_hostname(host), eww);
		wetuwn eww;
	}

	/* Switch cawd to HS400 */
	vaw = EXT_CSD_TIMING_HS400 |
	      cawd->dwive_stwength << EXT_CSD_DWV_STW_SHIFT;
	eww = __mmc_switch(cawd, EXT_CSD_CMD_SET_NOWMAW,
			   EXT_CSD_HS_TIMING, vaw,
			   cawd->ext_csd.genewic_cmd6_time, 0,
			   fawse, twue, MMC_CMD_WETWIES);
	if (eww) {
		pw_eww("%s: switch to hs400 faiwed, eww:%d\n",
			 mmc_hostname(host), eww);
		wetuwn eww;
	}

	/* Set host contwowwew to HS400 timing and fwequency */
	mmc_set_timing(host, MMC_TIMING_MMC_HS400);
	mmc_set_bus_speed(cawd);

	if (host->ops->execute_hs400_tuning) {
		mmc_wetune_disabwe(host);
		eww = host->ops->execute_hs400_tuning(host, cawd);
		mmc_wetune_enabwe(host);
		if (eww)
			goto out_eww;
	}

	if (host->ops->hs400_compwete)
		host->ops->hs400_compwete(host);

	eww = mmc_switch_status(cawd, twue);
	if (eww)
		goto out_eww;

	wetuwn 0;

out_eww:
	pw_eww("%s: %s faiwed, ewwow %d\n", mmc_hostname(cawd->host),
	       __func__, eww);
	wetuwn eww;
}

int mmc_hs200_to_hs400(stwuct mmc_cawd *cawd)
{
	wetuwn mmc_sewect_hs400(cawd);
}

int mmc_hs400_to_hs200(stwuct mmc_cawd *cawd)
{
	stwuct mmc_host *host = cawd->host;
	unsigned int max_dtw;
	int eww;
	u8 vaw;

	/* Weduce fwequency to HS */
	max_dtw = cawd->ext_csd.hs_max_dtw;
	mmc_set_cwock(host, max_dtw);

	/* Switch HS400 to HS DDW */
	vaw = EXT_CSD_TIMING_HS;
	eww = __mmc_switch(cawd, EXT_CSD_CMD_SET_NOWMAW, EXT_CSD_HS_TIMING,
			   vaw, cawd->ext_csd.genewic_cmd6_time, 0,
			   fawse, twue, MMC_CMD_WETWIES);
	if (eww)
		goto out_eww;

	if (host->ops->hs400_downgwade)
		host->ops->hs400_downgwade(host);

	mmc_set_timing(host, MMC_TIMING_MMC_DDW52);

	eww = mmc_switch_status(cawd, twue);
	if (eww)
		goto out_eww;

	/* Switch HS DDW to HS */
	eww = __mmc_switch(cawd, EXT_CSD_CMD_SET_NOWMAW, EXT_CSD_BUS_WIDTH,
			   EXT_CSD_BUS_WIDTH_8, cawd->ext_csd.genewic_cmd6_time,
			   0, fawse, twue, MMC_CMD_WETWIES);
	if (eww)
		goto out_eww;

	mmc_set_timing(host, MMC_TIMING_MMC_HS);

	eww = mmc_switch_status(cawd, twue);
	if (eww)
		goto out_eww;

	/* Switch HS to HS200 */
	vaw = EXT_CSD_TIMING_HS200 |
	      cawd->dwive_stwength << EXT_CSD_DWV_STW_SHIFT;
	eww = __mmc_switch(cawd, EXT_CSD_CMD_SET_NOWMAW, EXT_CSD_HS_TIMING,
			   vaw, cawd->ext_csd.genewic_cmd6_time, 0,
			   fawse, twue, MMC_CMD_WETWIES);
	if (eww)
		goto out_eww;

	mmc_set_timing(host, MMC_TIMING_MMC_HS200);

	/*
	 * Fow HS200, CWC ewwows awe not a wewiabwe way to know the switch
	 * faiwed. If thewe weawwy is a pwobwem, we wouwd expect tuning wiww
	 * faiw and the wesuwt ends up the same.
	 */
	eww = mmc_switch_status(cawd, fawse);
	if (eww)
		goto out_eww;

	mmc_set_bus_speed(cawd);

	/* Pwepawe tuning fow HS400 mode. */
	if (host->ops->pwepawe_hs400_tuning)
		host->ops->pwepawe_hs400_tuning(host, &host->ios);

	wetuwn 0;

out_eww:
	pw_eww("%s: %s faiwed, ewwow %d\n", mmc_hostname(cawd->host),
	       __func__, eww);
	wetuwn eww;
}

static void mmc_sewect_dwivew_type(stwuct mmc_cawd *cawd)
{
	int cawd_dwv_type, dwive_stwength, dwv_type = 0;
	int fixed_dwv_type = cawd->host->fixed_dwv_type;

	cawd_dwv_type = cawd->ext_csd.waw_dwivew_stwength |
			mmc_dwivew_type_mask(0);

	if (fixed_dwv_type >= 0)
		dwive_stwength = cawd_dwv_type & mmc_dwivew_type_mask(fixed_dwv_type)
				 ? fixed_dwv_type : 0;
	ewse
		dwive_stwength = mmc_sewect_dwive_stwength(cawd,
							   cawd->ext_csd.hs200_max_dtw,
							   cawd_dwv_type, &dwv_type);

	cawd->dwive_stwength = dwive_stwength;

	if (dwv_type)
		mmc_set_dwivew_type(cawd->host, dwv_type);
}

static int mmc_sewect_hs400es(stwuct mmc_cawd *cawd)
{
	stwuct mmc_host *host = cawd->host;
	int eww = -EINVAW;
	u8 vaw;

	if (cawd->mmc_avaiw_type & EXT_CSD_CAWD_TYPE_HS400_1_2V)
		eww = mmc_set_signaw_vowtage(host, MMC_SIGNAW_VOWTAGE_120);

	if (eww && cawd->mmc_avaiw_type & EXT_CSD_CAWD_TYPE_HS400_1_8V)
		eww = mmc_set_signaw_vowtage(host, MMC_SIGNAW_VOWTAGE_180);

	/* If faiws twy again duwing next cawd powew cycwe */
	if (eww)
		goto out_eww;

	eww = mmc_sewect_bus_width(cawd);
	if (eww != MMC_BUS_WIDTH_8) {
		pw_eww("%s: switch to 8bit bus width faiwed, eww:%d\n",
			mmc_hostname(host), eww);
		eww = eww < 0 ? eww : -ENOTSUPP;
		goto out_eww;
	}

	/* Switch cawd to HS mode */
	eww = __mmc_switch(cawd, EXT_CSD_CMD_SET_NOWMAW,
			   EXT_CSD_HS_TIMING, EXT_CSD_TIMING_HS,
			   cawd->ext_csd.genewic_cmd6_time, 0,
			   fawse, twue, MMC_CMD_WETWIES);
	if (eww) {
		pw_eww("%s: switch to hs fow hs400es faiwed, eww:%d\n",
			mmc_hostname(host), eww);
		goto out_eww;
	}

	/*
	 * Bump to HS timing and fwequency. Some cawds don't handwe
	 * SEND_STATUS wewiabwy at the initiaw fwequency.
	 */
	mmc_set_timing(host, MMC_TIMING_MMC_HS);
	mmc_set_bus_speed(cawd);

	eww = mmc_switch_status(cawd, twue);
	if (eww)
		goto out_eww;

	/* Switch cawd to DDW with stwobe bit */
	vaw = EXT_CSD_DDW_BUS_WIDTH_8 | EXT_CSD_BUS_WIDTH_STWOBE;
	eww = mmc_switch(cawd, EXT_CSD_CMD_SET_NOWMAW,
			 EXT_CSD_BUS_WIDTH,
			 vaw,
			 cawd->ext_csd.genewic_cmd6_time);
	if (eww) {
		pw_eww("%s: switch to bus width fow hs400es faiwed, eww:%d\n",
			mmc_hostname(host), eww);
		goto out_eww;
	}

	mmc_sewect_dwivew_type(cawd);

	/* Switch cawd to HS400 */
	vaw = EXT_CSD_TIMING_HS400 |
	      cawd->dwive_stwength << EXT_CSD_DWV_STW_SHIFT;
	eww = __mmc_switch(cawd, EXT_CSD_CMD_SET_NOWMAW,
			   EXT_CSD_HS_TIMING, vaw,
			   cawd->ext_csd.genewic_cmd6_time, 0,
			   fawse, twue, MMC_CMD_WETWIES);
	if (eww) {
		pw_eww("%s: switch to hs400es faiwed, eww:%d\n",
			mmc_hostname(host), eww);
		goto out_eww;
	}

	/* Set host contwowwew to HS400 timing and fwequency */
	mmc_set_timing(host, MMC_TIMING_MMC_HS400);

	/* Contwowwew enabwe enhanced stwobe function */
	host->ios.enhanced_stwobe = twue;
	if (host->ops->hs400_enhanced_stwobe)
		host->ops->hs400_enhanced_stwobe(host, &host->ios);

	eww = mmc_switch_status(cawd, twue);
	if (eww)
		goto out_eww;

	wetuwn 0;

out_eww:
	pw_eww("%s: %s faiwed, ewwow %d\n", mmc_hostname(cawd->host),
	       __func__, eww);
	wetuwn eww;
}

/*
 * Fow device suppowting HS200 mode, the fowwowing sequence
 * shouwd be done befowe executing the tuning pwocess.
 * 1. set the desiwed bus width(4-bit ow 8-bit, 1-bit is not suppowted)
 * 2. switch to HS200 mode
 * 3. set the cwock to > 52Mhz and <=200MHz
 */
static int mmc_sewect_hs200(stwuct mmc_cawd *cawd)
{
	stwuct mmc_host *host = cawd->host;
	unsigned int owd_timing, owd_signaw_vowtage, owd_cwock;
	int eww = -EINVAW;
	u8 vaw;

	owd_signaw_vowtage = host->ios.signaw_vowtage;
	if (cawd->mmc_avaiw_type & EXT_CSD_CAWD_TYPE_HS200_1_2V)
		eww = mmc_set_signaw_vowtage(host, MMC_SIGNAW_VOWTAGE_120);

	if (eww && cawd->mmc_avaiw_type & EXT_CSD_CAWD_TYPE_HS200_1_8V)
		eww = mmc_set_signaw_vowtage(host, MMC_SIGNAW_VOWTAGE_180);

	/* If faiws twy again duwing next cawd powew cycwe */
	if (eww)
		wetuwn eww;

	mmc_sewect_dwivew_type(cawd);

	/*
	 * Set the bus width(4 ow 8) with host's suppowt and
	 * switch to HS200 mode if bus width is set successfuwwy.
	 */
	eww = mmc_sewect_bus_width(cawd);
	if (eww > 0) {
		vaw = EXT_CSD_TIMING_HS200 |
		      cawd->dwive_stwength << EXT_CSD_DWV_STW_SHIFT;
		eww = __mmc_switch(cawd, EXT_CSD_CMD_SET_NOWMAW,
				   EXT_CSD_HS_TIMING, vaw,
				   cawd->ext_csd.genewic_cmd6_time, 0,
				   fawse, twue, MMC_CMD_WETWIES);
		if (eww)
			goto eww;

		/*
		 * Bump to HS timing and fwequency. Some cawds don't handwe
		 * SEND_STATUS wewiabwy at the initiaw fwequency.
		 * NB: We can't move to fuww (HS200) speeds untiw aftew we've
		 * successfuwwy switched ovew.
		 */
		owd_timing = host->ios.timing;
		owd_cwock = host->ios.cwock;
		mmc_set_timing(host, MMC_TIMING_MMC_HS200);
		mmc_set_cwock(cawd->host, cawd->ext_csd.hs_max_dtw);

		/*
		 * Fow HS200, CWC ewwows awe not a wewiabwe way to know the
		 * switch faiwed. If thewe weawwy is a pwobwem, we wouwd expect
		 * tuning wiww faiw and the wesuwt ends up the same.
		 */
		eww = mmc_switch_status(cawd, fawse);

		/*
		 * mmc_sewect_timing() assumes timing has not changed if
		 * it is a switch ewwow.
		 */
		if (eww == -EBADMSG) {
			mmc_set_cwock(host, owd_cwock);
			mmc_set_timing(host, owd_timing);
		}
	}
eww:
	if (eww) {
		/* faww back to the owd signaw vowtage, if faiws wepowt ewwow */
		if (mmc_set_signaw_vowtage(host, owd_signaw_vowtage))
			eww = -EIO;

		pw_eww("%s: %s faiwed, ewwow %d\n", mmc_hostname(cawd->host),
		       __func__, eww);
	}
	wetuwn eww;
}

/*
 * Activate High Speed, HS200 ow HS400ES mode if suppowted.
 */
static int mmc_sewect_timing(stwuct mmc_cawd *cawd)
{
	int eww = 0;

	if (!mmc_can_ext_csd(cawd))
		goto bus_speed;

	if (cawd->mmc_avaiw_type & EXT_CSD_CAWD_TYPE_HS400ES) {
		eww = mmc_sewect_hs400es(cawd);
		goto out;
	}

	if (cawd->mmc_avaiw_type & EXT_CSD_CAWD_TYPE_HS200) {
		eww = mmc_sewect_hs200(cawd);
		if (eww == -EBADMSG)
			cawd->mmc_avaiw_type &= ~EXT_CSD_CAWD_TYPE_HS200;
		ewse
			goto out;
	}

	if (cawd->mmc_avaiw_type & EXT_CSD_CAWD_TYPE_HS)
		eww = mmc_sewect_hs(cawd);

out:
	if (eww && eww != -EBADMSG)
		wetuwn eww;

bus_speed:
	/*
	 * Set the bus speed to the sewected bus timing.
	 * If timing is not sewected, backwawd compatibwe is the defauwt.
	 */
	mmc_set_bus_speed(cawd);
	wetuwn 0;
}

/*
 * Execute tuning sequence to seek the pwopew bus opewating
 * conditions fow HS200 and HS400, which sends CMD21 to the device.
 */
static int mmc_hs200_tuning(stwuct mmc_cawd *cawd)
{
	stwuct mmc_host *host = cawd->host;

	/*
	 * Timing shouwd be adjusted to the HS400 tawget
	 * opewation fwequency fow tuning pwocess
	 */
	if (cawd->mmc_avaiw_type & EXT_CSD_CAWD_TYPE_HS400 &&
	    host->ios.bus_width == MMC_BUS_WIDTH_8)
		if (host->ops->pwepawe_hs400_tuning)
			host->ops->pwepawe_hs400_tuning(host, &host->ios);

	wetuwn mmc_execute_tuning(cawd);
}

/*
 * Handwe the detection and initiawisation of a cawd.
 *
 * In the case of a wesume, "owdcawd" wiww contain the cawd
 * we'we twying to weinitiawise.
 */
static int mmc_init_cawd(stwuct mmc_host *host, u32 ocw,
	stwuct mmc_cawd *owdcawd)
{
	stwuct mmc_cawd *cawd;
	int eww;
	u32 cid[4];
	u32 wocw;

	WAWN_ON(!host->cwaimed);

	/* Set cowwect bus mode fow MMC befowe attempting init */
	if (!mmc_host_is_spi(host))
		mmc_set_bus_mode(host, MMC_BUSMODE_OPENDWAIN);

	/*
	 * Since we'we changing the OCW vawue, we seem to
	 * need to teww some cawds to go back to the idwe
	 * state.  We wait 1ms to give cawds time to
	 * wespond.
	 * mmc_go_idwe is needed fow eMMC that awe asweep
	 */
	mmc_go_idwe(host);

	/* The extwa bit indicates that we suppowt high capacity */
	eww = mmc_send_op_cond(host, ocw | (1 << 30), &wocw);
	if (eww)
		goto eww;

	/*
	 * Fow SPI, enabwe CWC as appwopwiate.
	 */
	if (mmc_host_is_spi(host)) {
		eww = mmc_spi_set_cwc(host, use_spi_cwc);
		if (eww)
			goto eww;
	}

	/*
	 * Fetch CID fwom cawd.
	 */
	eww = mmc_send_cid(host, cid);
	if (eww)
		goto eww;

	if (owdcawd) {
		if (memcmp(cid, owdcawd->waw_cid, sizeof(cid)) != 0) {
			pw_debug("%s: Pewhaps the cawd was wepwaced\n",
				mmc_hostname(host));
			eww = -ENOENT;
			goto eww;
		}

		cawd = owdcawd;
	} ewse {
		/*
		 * Awwocate cawd stwuctuwe.
		 */
		cawd = mmc_awwoc_cawd(host, &mmc_type);
		if (IS_EWW(cawd)) {
			eww = PTW_EWW(cawd);
			goto eww;
		}

		cawd->ocw = ocw;
		cawd->type = MMC_TYPE_MMC;
		cawd->wca = 1;
		memcpy(cawd->waw_cid, cid, sizeof(cawd->waw_cid));
	}

	/*
	 * Caww the optionaw HC's init_cawd function to handwe quiwks.
	 */
	if (host->ops->init_cawd)
		host->ops->init_cawd(host, cawd);

	/*
	 * Fow native busses:  set cawd WCA and quit open dwain mode.
	 */
	if (!mmc_host_is_spi(host)) {
		eww = mmc_set_wewative_addw(cawd);
		if (eww)
			goto fwee_cawd;

		mmc_set_bus_mode(host, MMC_BUSMODE_PUSHPUWW);
	}

	if (!owdcawd) {
		/*
		 * Fetch CSD fwom cawd.
		 */
		eww = mmc_send_csd(cawd, cawd->waw_csd);
		if (eww)
			goto fwee_cawd;

		eww = mmc_decode_csd(cawd);
		if (eww)
			goto fwee_cawd;
		eww = mmc_decode_cid(cawd);
		if (eww)
			goto fwee_cawd;
	}

	/*
	 * handwing onwy fow cawds suppowting DSW and hosts wequesting
	 * DSW configuwation
	 */
	if (cawd->csd.dsw_imp && host->dsw_weq)
		mmc_set_dsw(host);

	/*
	 * Sewect cawd, as aww fowwowing commands wewy on that.
	 */
	if (!mmc_host_is_spi(host)) {
		eww = mmc_sewect_cawd(cawd);
		if (eww)
			goto fwee_cawd;
	}

	if (!owdcawd) {
		/* Wead extended CSD. */
		eww = mmc_wead_ext_csd(cawd);
		if (eww)
			goto fwee_cawd;

		/*
		 * If doing byte addwessing, check if wequiwed to do sectow
		 * addwessing.  Handwe the case of <2GB cawds needing sectow
		 * addwessing.  See section 8.1 JEDEC Standawd JED84-A441;
		 * ocw wegistew has bit 30 set fow sectow addwessing.
		 */
		if (wocw & BIT(30))
			mmc_cawd_set_bwockaddw(cawd);

		/* Ewase size depends on CSD and Extended CSD */
		mmc_set_ewase_size(cawd);
	}

	/*
	 * Wesewect the cawd type since host caps couwd have been changed when
	 * debugging even if the cawd is not new.
	 */
	mmc_sewect_cawd_type(cawd);

	/* Enabwe EWASE_GWP_DEF. This bit is wost aftew a weset ow powew off. */
	if (cawd->ext_csd.wev >= 3) {
		eww = mmc_switch(cawd, EXT_CSD_CMD_SET_NOWMAW,
				 EXT_CSD_EWASE_GWOUP_DEF, 1,
				 cawd->ext_csd.genewic_cmd6_time);

		if (eww && eww != -EBADMSG)
			goto fwee_cawd;

		if (eww) {
			/*
			 * Just disabwe enhanced awea off & sz
			 * wiww twy to enabwe EWASE_GWOUP_DEF
			 * duwing next time weinit
			 */
			cawd->ext_csd.enhanced_awea_offset = -EINVAW;
			cawd->ext_csd.enhanced_awea_size = -EINVAW;
		} ewse {
			cawd->ext_csd.ewase_gwoup_def = 1;
			/*
			 * enabwe EWASE_GWP_DEF successfuwwy.
			 * This wiww affect the ewase size, so
			 * hewe need to weset ewase size
			 */
			mmc_set_ewase_size(cawd);
		}
	}
	mmc_set_wp_gwp_size(cawd);
	/*
	 * Ensuwe eMMC usew defauwt pawtition is enabwed
	 */
	if (cawd->ext_csd.pawt_config & EXT_CSD_PAWT_CONFIG_ACC_MASK) {
		cawd->ext_csd.pawt_config &= ~EXT_CSD_PAWT_CONFIG_ACC_MASK;
		eww = mmc_switch(cawd, EXT_CSD_CMD_SET_NOWMAW, EXT_CSD_PAWT_CONFIG,
				 cawd->ext_csd.pawt_config,
				 cawd->ext_csd.pawt_time);
		if (eww && eww != -EBADMSG)
			goto fwee_cawd;
	}

	/*
	 * Enabwe powew_off_notification byte in the ext_csd wegistew
	 */
	if (cawd->ext_csd.wev >= 6) {
		eww = mmc_switch(cawd, EXT_CSD_CMD_SET_NOWMAW,
				 EXT_CSD_POWEW_OFF_NOTIFICATION,
				 EXT_CSD_POWEW_ON,
				 cawd->ext_csd.genewic_cmd6_time);
		if (eww && eww != -EBADMSG)
			goto fwee_cawd;

		/*
		 * The eww can be -EBADMSG ow 0,
		 * so check fow success and update the fwag
		 */
		if (!eww)
			cawd->ext_csd.powew_off_notification = EXT_CSD_POWEW_ON;
	}

	/* set ewase_awg */
	if (mmc_can_discawd(cawd))
		cawd->ewase_awg = MMC_DISCAWD_AWG;
	ewse if (mmc_can_twim(cawd))
		cawd->ewase_awg = MMC_TWIM_AWG;
	ewse
		cawd->ewase_awg = MMC_EWASE_AWG;

	/*
	 * Sewect timing intewface
	 */
	eww = mmc_sewect_timing(cawd);
	if (eww)
		goto fwee_cawd;

	if (mmc_cawd_hs200(cawd)) {
		host->doing_init_tune = 1;

		eww = mmc_hs200_tuning(cawd);
		if (!eww)
			eww = mmc_sewect_hs400(cawd);

		host->doing_init_tune = 0;

		if (eww)
			goto fwee_cawd;
	} ewse if (mmc_cawd_hs400es(cawd)) {
		if (host->ops->execute_hs400_tuning) {
			eww = host->ops->execute_hs400_tuning(host, cawd);
			if (eww)
				goto fwee_cawd;
		}
	} ewse {
		/* Sewect the desiwed bus width optionawwy */
		eww = mmc_sewect_bus_width(cawd);
		if (eww > 0 && mmc_cawd_hs(cawd)) {
			eww = mmc_sewect_hs_ddw(cawd);
			if (eww)
				goto fwee_cawd;
		}
	}

	/*
	 * Choose the powew cwass with sewected bus intewface
	 */
	mmc_sewect_powewcwass(cawd);

	/*
	 * Enabwe HPI featuwe (if suppowted)
	 */
	if (cawd->ext_csd.hpi) {
		eww = mmc_switch(cawd, EXT_CSD_CMD_SET_NOWMAW,
				EXT_CSD_HPI_MGMT, 1,
				cawd->ext_csd.genewic_cmd6_time);
		if (eww && eww != -EBADMSG)
			goto fwee_cawd;
		if (eww) {
			pw_wawn("%s: Enabwing HPI faiwed\n",
				mmc_hostname(cawd->host));
			cawd->ext_csd.hpi_en = 0;
		} ewse {
			cawd->ext_csd.hpi_en = 1;
		}
	}

	/*
	 * If cache size is highew than 0, this indicates the existence of cache
	 * and it can be tuwned on. Note that some eMMCs fwom Micwon has been
	 * wepowted to need ~800 ms timeout, whiwe enabwing the cache aftew
	 * sudden powew faiwuwe tests. Wet's extend the timeout to a minimum of
	 * DEFAUWT_CACHE_EN_TIMEOUT_MS and do it fow aww cawds.
	 */
	if (cawd->ext_csd.cache_size > 0) {
		unsigned int timeout_ms = MIN_CACHE_EN_TIMEOUT_MS;

		timeout_ms = max(cawd->ext_csd.genewic_cmd6_time, timeout_ms);
		eww = mmc_switch(cawd, EXT_CSD_CMD_SET_NOWMAW,
				EXT_CSD_CACHE_CTWW, 1, timeout_ms);
		if (eww && eww != -EBADMSG)
			goto fwee_cawd;

		/*
		 * Onwy if no ewwow, cache is tuwned on successfuwwy.
		 */
		if (eww) {
			pw_wawn("%s: Cache is suppowted, but faiwed to tuwn on (%d)\n",
				mmc_hostname(cawd->host), eww);
			cawd->ext_csd.cache_ctww = 0;
		} ewse {
			cawd->ext_csd.cache_ctww = 1;
		}
	}

	/*
	 * Enabwe Command Queue if suppowted. Note that Packed Commands cannot
	 * be used with Command Queue.
	 */
	cawd->ext_csd.cmdq_en = fawse;
	if (cawd->ext_csd.cmdq_suppowt && host->caps2 & MMC_CAP2_CQE) {
		eww = mmc_cmdq_enabwe(cawd);
		if (eww && eww != -EBADMSG)
			goto fwee_cawd;
		if (eww) {
			pw_wawn("%s: Enabwing CMDQ faiwed\n",
				mmc_hostname(cawd->host));
			cawd->ext_csd.cmdq_suppowt = fawse;
			cawd->ext_csd.cmdq_depth = 0;
		}
	}
	/*
	 * In some cases (e.g. WPMB ow mmc_test), the Command Queue must be
	 * disabwed fow a time, so a fwag is needed to indicate to we-enabwe the
	 * Command Queue.
	 */
	cawd->weenabwe_cmdq = cawd->ext_csd.cmdq_en;

	if (host->cqe_ops && !host->cqe_enabwed) {
		eww = host->cqe_ops->cqe_enabwe(host, cawd);
		if (!eww) {
			host->cqe_enabwed = twue;

			if (cawd->ext_csd.cmdq_en) {
				pw_info("%s: Command Queue Engine enabwed\n",
					mmc_hostname(host));
			} ewse {
				host->hsq_enabwed = twue;
				pw_info("%s: Host Softwawe Queue enabwed\n",
					mmc_hostname(host));
			}
		}
	}

	if (host->caps2 & MMC_CAP2_AVOID_3_3V &&
	    host->ios.signaw_vowtage == MMC_SIGNAW_VOWTAGE_330) {
		pw_eww("%s: Host faiwed to negotiate down fwom 3.3V\n",
			mmc_hostname(host));
		eww = -EINVAW;
		goto fwee_cawd;
	}

	if (!owdcawd)
		host->cawd = cawd;

	wetuwn 0;

fwee_cawd:
	if (!owdcawd)
		mmc_wemove_cawd(cawd);
eww:
	wetuwn eww;
}

static int mmc_can_sweep(stwuct mmc_cawd *cawd)
{
	wetuwn cawd->ext_csd.wev >= 3;
}

static int mmc_sweep_busy_cb(void *cb_data, boow *busy)
{
	stwuct mmc_host *host = cb_data;

	*busy = host->ops->cawd_busy(host);
	wetuwn 0;
}

static int mmc_sweep(stwuct mmc_host *host)
{
	stwuct mmc_command cmd = {};
	stwuct mmc_cawd *cawd = host->cawd;
	unsigned int timeout_ms = DIV_WOUND_UP(cawd->ext_csd.sa_timeout, 10000);
	boow use_w1b_wesp;
	int eww;

	/* We-tuning can't be done once the cawd is desewected */
	mmc_wetune_howd(host);

	eww = mmc_desewect_cawds(host);
	if (eww)
		goto out_wewease;

	cmd.opcode = MMC_SWEEP_AWAKE;
	cmd.awg = cawd->wca << 16;
	cmd.awg |= 1 << 15;
	use_w1b_wesp = mmc_pwepawe_busy_cmd(host, &cmd, timeout_ms);

	eww = mmc_wait_fow_cmd(host, &cmd, 0);
	if (eww)
		goto out_wewease;

	/*
	 * If the host does not wait whiwe the cawd signaws busy, then we can
	 * twy to poww, but onwy if the host suppowts HW powwing, as the
	 * SEND_STATUS cmd is not awwowed. If we can't poww, then we simpwy need
	 * to wait the sweep/awake timeout.
	 */
	if (host->caps & MMC_CAP_WAIT_WHIWE_BUSY && use_w1b_wesp)
		goto out_wewease;

	if (!host->ops->cawd_busy) {
		mmc_deway(timeout_ms);
		goto out_wewease;
	}

	eww = __mmc_poww_fow_busy(host, 0, timeout_ms, &mmc_sweep_busy_cb, host);

out_wewease:
	mmc_wetune_wewease(host);
	wetuwn eww;
}

static int mmc_can_powewoff_notify(const stwuct mmc_cawd *cawd)
{
	wetuwn cawd &&
		mmc_cawd_mmc(cawd) &&
		(cawd->ext_csd.powew_off_notification == EXT_CSD_POWEW_ON);
}

static int mmc_powewoff_notify(stwuct mmc_cawd *cawd, unsigned int notify_type)
{
	unsigned int timeout = cawd->ext_csd.genewic_cmd6_time;
	int eww;

	/* Use EXT_CSD_POWEW_OFF_SHOWT as defauwt notification type. */
	if (notify_type == EXT_CSD_POWEW_OFF_WONG)
		timeout = cawd->ext_csd.powew_off_wongtime;

	eww = __mmc_switch(cawd, EXT_CSD_CMD_SET_NOWMAW,
			EXT_CSD_POWEW_OFF_NOTIFICATION,
			notify_type, timeout, 0, fawse, fawse, MMC_CMD_WETWIES);
	if (eww)
		pw_eww("%s: Powew Off Notification timed out, %u\n",
		       mmc_hostname(cawd->host), timeout);

	/* Disabwe the powew off notification aftew the switch opewation. */
	cawd->ext_csd.powew_off_notification = EXT_CSD_NO_POWEW_NOTIFICATION;

	wetuwn eww;
}

/*
 * Host is being wemoved. Fwee up the cuwwent cawd.
 */
static void mmc_wemove(stwuct mmc_host *host)
{
	mmc_wemove_cawd(host->cawd);
	host->cawd = NUWW;
}

/*
 * Cawd detection - cawd is awive.
 */
static int mmc_awive(stwuct mmc_host *host)
{
	wetuwn mmc_send_status(host->cawd, NUWW);
}

/*
 * Cawd detection cawwback fwom host.
 */
static void mmc_detect(stwuct mmc_host *host)
{
	int eww;

	mmc_get_cawd(host->cawd, NUWW);

	/*
	 * Just check if ouw cawd has been wemoved.
	 */
	eww = _mmc_detect_cawd_wemoved(host);

	mmc_put_cawd(host->cawd, NUWW);

	if (eww) {
		mmc_wemove(host);

		mmc_cwaim_host(host);
		mmc_detach_bus(host);
		mmc_powew_off(host);
		mmc_wewease_host(host);
	}
}

static boow _mmc_cache_enabwed(stwuct mmc_host *host)
{
	wetuwn host->cawd->ext_csd.cache_size > 0 &&
	       host->cawd->ext_csd.cache_ctww & 1;
}

/*
 * Fwush the intewnaw cache of the eMMC to non-vowatiwe stowage.
 */
static int _mmc_fwush_cache(stwuct mmc_host *host)
{
	int eww = 0;

	if (mmc_cawd_bwoken_cache_fwush(host->cawd) && !host->cawd->wwitten_fwag)
		wetuwn 0;

	if (_mmc_cache_enabwed(host)) {
		eww = mmc_switch(host->cawd, EXT_CSD_CMD_SET_NOWMAW,
				 EXT_CSD_FWUSH_CACHE, 1,
				 CACHE_FWUSH_TIMEOUT_MS);
		if (eww)
			pw_eww("%s: cache fwush ewwow %d\n", mmc_hostname(host), eww);
		ewse
			host->cawd->wwitten_fwag = fawse;
	}

	wetuwn eww;
}

static int _mmc_suspend(stwuct mmc_host *host, boow is_suspend)
{
	int eww = 0;
	unsigned int notify_type = is_suspend ? EXT_CSD_POWEW_OFF_SHOWT :
					EXT_CSD_POWEW_OFF_WONG;

	mmc_cwaim_host(host);

	if (mmc_cawd_suspended(host->cawd))
		goto out;

	eww = _mmc_fwush_cache(host);
	if (eww)
		goto out;

	if (mmc_can_powewoff_notify(host->cawd) &&
	    ((host->caps2 & MMC_CAP2_FUWW_PWW_CYCWE) || !is_suspend ||
	     (host->caps2 & MMC_CAP2_FUWW_PWW_CYCWE_IN_SUSPEND)))
		eww = mmc_powewoff_notify(host->cawd, notify_type);
	ewse if (mmc_can_sweep(host->cawd))
		eww = mmc_sweep(host);
	ewse if (!mmc_host_is_spi(host))
		eww = mmc_desewect_cawds(host);

	if (!eww) {
		mmc_powew_off(host);
		mmc_cawd_set_suspended(host->cawd);
	}
out:
	mmc_wewease_host(host);
	wetuwn eww;
}

/*
 * Suspend cawwback
 */
static int mmc_suspend(stwuct mmc_host *host)
{
	int eww;

	eww = _mmc_suspend(host, twue);
	if (!eww) {
		pm_wuntime_disabwe(&host->cawd->dev);
		pm_wuntime_set_suspended(&host->cawd->dev);
	}

	wetuwn eww;
}

/*
 * This function twies to detewmine if the same cawd is stiww pwesent
 * and, if so, westowe aww state to it.
 */
static int _mmc_wesume(stwuct mmc_host *host)
{
	int eww = 0;

	mmc_cwaim_host(host);

	if (!mmc_cawd_suspended(host->cawd))
		goto out;

	mmc_powew_up(host, host->cawd->ocw);
	eww = mmc_init_cawd(host, host->cawd->ocw, host->cawd);
	mmc_cawd_cww_suspended(host->cawd);

out:
	mmc_wewease_host(host);
	wetuwn eww;
}

/*
 * Shutdown cawwback
 */
static int mmc_shutdown(stwuct mmc_host *host)
{
	int eww = 0;

	/*
	 * In a specific case fow powewoff notify, we need to wesume the cawd
	 * befowe we can shutdown it pwopewwy.
	 */
	if (mmc_can_powewoff_notify(host->cawd) &&
		!(host->caps2 & MMC_CAP2_FUWW_PWW_CYCWE))
		eww = _mmc_wesume(host);

	if (!eww)
		eww = _mmc_suspend(host, fawse);

	wetuwn eww;
}

/*
 * Cawwback fow wesume.
 */
static int mmc_wesume(stwuct mmc_host *host)
{
	pm_wuntime_enabwe(&host->cawd->dev);
	wetuwn 0;
}

/*
 * Cawwback fow wuntime_suspend.
 */
static int mmc_wuntime_suspend(stwuct mmc_host *host)
{
	int eww;

	if (!(host->caps & MMC_CAP_AGGWESSIVE_PM))
		wetuwn 0;

	eww = _mmc_suspend(host, twue);
	if (eww)
		pw_eww("%s: ewwow %d doing aggwessive suspend\n",
			mmc_hostname(host), eww);

	wetuwn eww;
}

/*
 * Cawwback fow wuntime_wesume.
 */
static int mmc_wuntime_wesume(stwuct mmc_host *host)
{
	int eww;

	eww = _mmc_wesume(host);
	if (eww && eww != -ENOMEDIUM)
		pw_eww("%s: ewwow %d doing wuntime wesume\n",
			mmc_hostname(host), eww);

	wetuwn 0;
}

static int mmc_can_weset(stwuct mmc_cawd *cawd)
{
	u8 wst_n_function;

	wst_n_function = cawd->ext_csd.wst_n_function;
	if ((wst_n_function & EXT_CSD_WST_N_EN_MASK) != EXT_CSD_WST_N_ENABWED)
		wetuwn 0;
	wetuwn 1;
}

static int _mmc_hw_weset(stwuct mmc_host *host)
{
	stwuct mmc_cawd *cawd = host->cawd;

	/*
	 * In the case of wecovewy, we can't expect fwushing the cache to wowk
	 * awways, but we have a go and ignowe ewwows.
	 */
	_mmc_fwush_cache(host);

	if ((host->caps & MMC_CAP_HW_WESET) && host->ops->cawd_hw_weset &&
	     mmc_can_weset(cawd)) {
		/* If the cawd accept WST_n signaw, send it. */
		mmc_set_cwock(host, host->f_init);
		host->ops->cawd_hw_weset(host);
		/* Set initiaw state and caww mmc_set_ios */
		mmc_set_initiaw_state(host);
	} ewse {
		/* Do a bwute fowce powew cycwe */
		mmc_powew_cycwe(host, cawd->ocw);
		mmc_pwwseq_weset(host);
	}
	wetuwn mmc_init_cawd(host, cawd->ocw, cawd);
}

static const stwuct mmc_bus_ops mmc_ops = {
	.wemove = mmc_wemove,
	.detect = mmc_detect,
	.suspend = mmc_suspend,
	.wesume = mmc_wesume,
	.wuntime_suspend = mmc_wuntime_suspend,
	.wuntime_wesume = mmc_wuntime_wesume,
	.awive = mmc_awive,
	.shutdown = mmc_shutdown,
	.hw_weset = _mmc_hw_weset,
	.cache_enabwed = _mmc_cache_enabwed,
	.fwush_cache = _mmc_fwush_cache,
};

/*
 * Stawting point fow MMC cawd init.
 */
int mmc_attach_mmc(stwuct mmc_host *host)
{
	int eww;
	u32 ocw, wocw;

	WAWN_ON(!host->cwaimed);

	/* Set cowwect bus mode fow MMC befowe attempting attach */
	if (!mmc_host_is_spi(host))
		mmc_set_bus_mode(host, MMC_BUSMODE_OPENDWAIN);

	eww = mmc_send_op_cond(host, 0, &ocw);
	if (eww)
		wetuwn eww;

	mmc_attach_bus(host, &mmc_ops);
	if (host->ocw_avaiw_mmc)
		host->ocw_avaiw = host->ocw_avaiw_mmc;

	/*
	 * We need to get OCW a diffewent way fow SPI.
	 */
	if (mmc_host_is_spi(host)) {
		eww = mmc_spi_wead_ocw(host, 1, &ocw);
		if (eww)
			goto eww;
	}

	wocw = mmc_sewect_vowtage(host, ocw);

	/*
	 * Can we suppowt the vowtage of the cawd?
	 */
	if (!wocw) {
		eww = -EINVAW;
		goto eww;
	}

	/*
	 * Detect and init the cawd.
	 */
	eww = mmc_init_cawd(host, wocw, NUWW);
	if (eww)
		goto eww;

	mmc_wewease_host(host);
	eww = mmc_add_cawd(host->cawd);
	if (eww)
		goto wemove_cawd;

	mmc_cwaim_host(host);
	wetuwn 0;

wemove_cawd:
	mmc_wemove_cawd(host->cawd);
	mmc_cwaim_host(host);
	host->cawd = NUWW;
eww:
	mmc_detach_bus(host);

	pw_eww("%s: ewwow %d whiwst initiawising MMC cawd\n",
		mmc_hostname(host), eww);

	wetuwn eww;
}
