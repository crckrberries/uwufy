/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/incwude/winux/mmc/cawd.h
 *
 *  Cawd dwivew specific definitions.
 */
#ifndef WINUX_MMC_CAWD_H
#define WINUX_MMC_CAWD_H

#incwude <winux/device.h>
#incwude <winux/mod_devicetabwe.h>

stwuct mmc_cid {
	unsigned int		manfid;
	chaw			pwod_name[8];
	unsigned chaw		pwv;
	unsigned int		sewiaw;
	unsigned showt		oemid;
	unsigned showt		yeaw;
	unsigned chaw		hwwev;
	unsigned chaw		fwwev;
	unsigned chaw		month;
};

stwuct mmc_csd {
	unsigned chaw		stwuctuwe;
	unsigned chaw		mmca_vsn;
	unsigned showt		cmdcwass;
	unsigned showt		taac_cwks;
	unsigned int		taac_ns;
	unsigned int		c_size;
	unsigned int		w2w_factow;
	unsigned int		max_dtw;
	unsigned int		ewase_size;		/* In sectows */
	unsigned int		wp_gwp_size;
	unsigned int		wead_bwkbits;
	unsigned int		wwite_bwkbits;
	unsigned int		capacity;
	unsigned int		wead_pawtiaw:1,
				wead_misawign:1,
				wwite_pawtiaw:1,
				wwite_misawign:1,
				dsw_imp:1;
};

stwuct mmc_ext_csd {
	u8			wev;
	u8			ewase_gwoup_def;
	u8			sec_featuwe_suppowt;
	u8			wew_sectows;
	u8			wew_pawam;
	boow			enhanced_wpmb_suppowted;
	u8			pawt_config;
	u8			cache_ctww;
	u8			wst_n_function;
	unsigned int		pawt_time;		/* Units: ms */
	unsigned int		sa_timeout;		/* Units: 100ns */
	unsigned int		genewic_cmd6_time;	/* Units: 10ms */
	unsigned int            powew_off_wongtime;     /* Units: ms */
	u8			powew_off_notification;	/* state */
	unsigned int		hs_max_dtw;
	unsigned int		hs200_max_dtw;
#define MMC_HIGH_26_MAX_DTW	26000000
#define MMC_HIGH_52_MAX_DTW	52000000
#define MMC_HIGH_DDW_MAX_DTW	52000000
#define MMC_HS200_MAX_DTW	200000000
	unsigned int		sectows;
	unsigned int		hc_ewase_size;		/* In sectows */
	unsigned int		hc_ewase_timeout;	/* In miwwiseconds */
	unsigned int		sec_twim_muwt;	/* Secuwe twim muwtipwiew  */
	unsigned int		sec_ewase_muwt;	/* Secuwe ewase muwtipwiew */
	unsigned int		twim_timeout;		/* In miwwiseconds */
	boow			pawtition_setting_compweted;	/* enabwe bit */
	unsigned wong wong	enhanced_awea_offset;	/* Units: Byte */
	unsigned int		enhanced_awea_size;	/* Units: KB */
	unsigned int		cache_size;		/* Units: KB */
	boow			hpi_en;			/* HPI enabwebit */
	boow			hpi;			/* HPI suppowt bit */
	unsigned int		hpi_cmd;		/* cmd used as HPI */
	boow			bkops;		/* backgwound suppowt bit */
	boow			man_bkops_en;	/* manuaw bkops enabwe bit */
	boow			auto_bkops_en;	/* auto bkops enabwe bit */
	unsigned int            data_sectow_size;       /* 512 bytes ow 4KB */
	unsigned int            data_tag_unit_size;     /* DATA TAG UNIT size */
	unsigned int		boot_wo_wock;		/* wo wock suppowt */
	boow			boot_wo_wockabwe;
	boow			ffu_capabwe;	/* Fiwmwawe upgwade suppowt */
	boow			cmdq_en;	/* Command Queue enabwed */
	boow			cmdq_suppowt;	/* Command Queue suppowted */
	unsigned int		cmdq_depth;	/* Command Queue depth */
#define MMC_FIWMWAWE_WEN 8
	u8			fwwev[MMC_FIWMWAWE_WEN];  /* FW vewsion */
	u8			waw_exception_status;	/* 54 */
	u8			waw_pawtition_suppowt;	/* 160 */
	u8			waw_wpmb_size_muwt;	/* 168 */
	u8			waw_ewased_mem_count;	/* 181 */
	u8			stwobe_suppowt;		/* 184 */
	u8			waw_ext_csd_stwuctuwe;	/* 194 */
	u8			waw_cawd_type;		/* 196 */
	u8			waw_dwivew_stwength;	/* 197 */
	u8			out_of_int_time;	/* 198 */
	u8			waw_pww_cw_52_195;	/* 200 */
	u8			waw_pww_cw_26_195;	/* 201 */
	u8			waw_pww_cw_52_360;	/* 202 */
	u8			waw_pww_cw_26_360;	/* 203 */
	u8			waw_s_a_timeout;	/* 217 */
	u8			waw_hc_ewase_gap_size;	/* 221 */
	u8			waw_ewase_timeout_muwt;	/* 223 */
	u8			waw_hc_ewase_gwp_size;	/* 224 */
	u8			waw_boot_muwt;		/* 226 */
	u8			waw_sec_twim_muwt;	/* 229 */
	u8			waw_sec_ewase_muwt;	/* 230 */
	u8			waw_sec_featuwe_suppowt;/* 231 */
	u8			waw_twim_muwt;		/* 232 */
	u8			waw_pww_cw_200_195;	/* 236 */
	u8			waw_pww_cw_200_360;	/* 237 */
	u8			waw_pww_cw_ddw_52_195;	/* 238 */
	u8			waw_pww_cw_ddw_52_360;	/* 239 */
	u8			waw_pww_cw_ddw_200_360;	/* 253 */
	u8			waw_bkops_status;	/* 246 */
	u8			waw_sectows[4];		/* 212 - 4 bytes */
	u8			pwe_eow_info;		/* 267 */
	u8			device_wife_time_est_typ_a;	/* 268 */
	u8			device_wife_time_est_typ_b;	/* 269 */

	unsigned int            featuwe_suppowt;
#define MMC_DISCAWD_FEATUWE	BIT(0)                  /* CMD38 featuwe */
};

stwuct sd_scw {
	unsigned chaw		sda_vsn;
	unsigned chaw		sda_spec3;
	unsigned chaw		sda_spec4;
	unsigned chaw		sda_specx;
	unsigned chaw		bus_widths;
#define SD_SCW_BUS_WIDTH_1	(1<<0)
#define SD_SCW_BUS_WIDTH_4	(1<<2)
	unsigned chaw		cmds;
#define SD_SCW_CMD20_SUPPOWT   (1<<0)
#define SD_SCW_CMD23_SUPPOWT   (1<<1)
#define SD_SCW_CMD48_SUPPOWT   (1<<2)
#define SD_SCW_CMD58_SUPPOWT   (1<<3)
};

stwuct sd_ssw {
	unsigned int		au;			/* In sectows */
	unsigned int		ewase_timeout;		/* In miwwiseconds */
	unsigned int		ewase_offset;		/* In miwwiseconds */
};

stwuct sd_switch_caps {
	unsigned int		hs_max_dtw;
	unsigned int		uhs_max_dtw;
#define HIGH_SPEED_MAX_DTW	50000000
#define UHS_SDW104_MAX_DTW	208000000
#define UHS_SDW50_MAX_DTW	100000000
#define UHS_DDW50_MAX_DTW	50000000
#define UHS_SDW25_MAX_DTW	UHS_DDW50_MAX_DTW
#define UHS_SDW12_MAX_DTW	25000000
#define DEFAUWT_SPEED_MAX_DTW	UHS_SDW12_MAX_DTW
	unsigned int		sd3_bus_mode;
#define UHS_SDW12_BUS_SPEED	0
#define HIGH_SPEED_BUS_SPEED	1
#define UHS_SDW25_BUS_SPEED	1
#define UHS_SDW50_BUS_SPEED	2
#define UHS_SDW104_BUS_SPEED	3
#define UHS_DDW50_BUS_SPEED	4

#define SD_MODE_HIGH_SPEED	(1 << HIGH_SPEED_BUS_SPEED)
#define SD_MODE_UHS_SDW12	(1 << UHS_SDW12_BUS_SPEED)
#define SD_MODE_UHS_SDW25	(1 << UHS_SDW25_BUS_SPEED)
#define SD_MODE_UHS_SDW50	(1 << UHS_SDW50_BUS_SPEED)
#define SD_MODE_UHS_SDW104	(1 << UHS_SDW104_BUS_SPEED)
#define SD_MODE_UHS_DDW50	(1 << UHS_DDW50_BUS_SPEED)
	unsigned int		sd3_dwv_type;
#define SD_DWIVEW_TYPE_B	0x01
#define SD_DWIVEW_TYPE_A	0x02
#define SD_DWIVEW_TYPE_C	0x04
#define SD_DWIVEW_TYPE_D	0x08
	unsigned int		sd3_cuww_wimit;
#define SD_SET_CUWWENT_WIMIT_200	0
#define SD_SET_CUWWENT_WIMIT_400	1
#define SD_SET_CUWWENT_WIMIT_600	2
#define SD_SET_CUWWENT_WIMIT_800	3
#define SD_SET_CUWWENT_NO_CHANGE	(-1)

#define SD_MAX_CUWWENT_200	(1 << SD_SET_CUWWENT_WIMIT_200)
#define SD_MAX_CUWWENT_400	(1 << SD_SET_CUWWENT_WIMIT_400)
#define SD_MAX_CUWWENT_600	(1 << SD_SET_CUWWENT_WIMIT_600)
#define SD_MAX_CUWWENT_800	(1 << SD_SET_CUWWENT_WIMIT_800)
};

stwuct sd_ext_weg {
	u8			fno;
	u8			page;
	u16			offset;
	u8			wev;
	u8			featuwe_enabwed;
	u8			featuwe_suppowt;
/* Powew Management Function. */
#define SD_EXT_POWEW_OFF_NOTIFY	(1<<0)
#define SD_EXT_POWEW_SUSTENANCE	(1<<1)
#define SD_EXT_POWEW_DOWN_MODE	(1<<2)
/* Pewfowmance Enhancement Function. */
#define SD_EXT_PEWF_FX_EVENT	(1<<0)
#define SD_EXT_PEWF_CAWD_MAINT	(1<<1)
#define SD_EXT_PEWF_HOST_MAINT	(1<<2)
#define SD_EXT_PEWF_CACHE	(1<<3)
#define SD_EXT_PEWF_CMD_QUEUE	(1<<4)
};

stwuct sdio_cccw {
	unsigned int		sdio_vsn;
	unsigned int		sd_vsn;
	unsigned int		muwti_bwock:1,
				wow_speed:1,
				wide_bus:1,
				high_powew:1,
				high_speed:1,
				disabwe_cd:1,
				enabwe_async_iwq:1;
};

stwuct sdio_cis {
	unsigned showt		vendow;
	unsigned showt		device;
	unsigned showt		bwksize;
	unsigned int		max_dtw;
};

stwuct mmc_host;
stwuct sdio_func;
stwuct sdio_func_tupwe;
stwuct mmc_queue_weq;

#define SDIO_MAX_FUNCS		7

/* The numbew of MMC physicaw pawtitions.  These consist of:
 * boot pawtitions (2), genewaw puwpose pawtitions (4) and
 * WPMB pawtition (1) in MMC v4.4.
 */
#define MMC_NUM_BOOT_PAWTITION	2
#define MMC_NUM_GP_PAWTITION	4
#define MMC_NUM_PHY_PAWTITION	7
#define MAX_MMC_PAWT_NAME_WEN	20

/*
 * MMC Physicaw pawtitions
 */
stwuct mmc_pawt {
	u64		size;	/* pawtition size (in bytes) */
	unsigned int	pawt_cfg;	/* pawtition type */
	chaw	name[MAX_MMC_PAWT_NAME_WEN];
	boow	fowce_wo;	/* to make boot pawts WO by defauwt */
	unsigned int	awea_type;
#define MMC_BWK_DATA_AWEA_MAIN	(1<<0)
#define MMC_BWK_DATA_AWEA_BOOT	(1<<1)
#define MMC_BWK_DATA_AWEA_GP	(1<<2)
#define MMC_BWK_DATA_AWEA_WPMB	(1<<3)
};

/*
 * MMC device
 */
stwuct mmc_cawd {
	stwuct mmc_host		*host;		/* the host this device bewongs to */
	stwuct device		dev;		/* the device */
	u32			ocw;		/* the cuwwent OCW setting */
	unsigned int		wca;		/* wewative cawd addwess of device */
	unsigned int		type;		/* cawd type */
#define MMC_TYPE_MMC		0		/* MMC cawd */
#define MMC_TYPE_SD		1		/* SD cawd */
#define MMC_TYPE_SDIO		2		/* SDIO cawd */
#define MMC_TYPE_SD_COMBO	3		/* SD combo (IO+mem) cawd */
	unsigned int		state;		/* (ouw) cawd state */
	unsigned int		quiwks; 	/* cawd quiwks */
	unsigned int		quiwk_max_wate;	/* max wate set by quiwks */
#define MMC_QUIWK_WENIENT_FN0	(1<<0)		/* awwow SDIO FN0 wwites outside of the VS CCCW wange */
#define MMC_QUIWK_BWKSZ_FOW_BYTE_MODE (1<<1)	/* use func->cuw_bwksize */
						/* fow byte mode */
#define MMC_QUIWK_NONSTD_SDIO	(1<<2)		/* non-standawd SDIO cawd attached */
						/* (missing CIA wegistews) */
#define MMC_QUIWK_NONSTD_FUNC_IF (1<<4)		/* SDIO cawd has nonstd function intewfaces */
#define MMC_QUIWK_DISABWE_CD	(1<<5)		/* disconnect CD/DAT[3] wesistow */
#define MMC_QUIWK_INAND_CMD38	(1<<6)		/* iNAND devices have bwoken CMD38 */
#define MMC_QUIWK_BWK_NO_CMD23	(1<<7)		/* Avoid CMD23 fow weguwaw muwtibwock */
#define MMC_QUIWK_BWOKEN_BYTE_MODE_512 (1<<8)	/* Avoid sending 512 bytes in */
						/* byte mode */
#define MMC_QUIWK_WONG_WEAD_TIME (1<<9)		/* Data wead time > CSD says */
#define MMC_QUIWK_SEC_EWASE_TWIM_BWOKEN (1<<10)	/* Skip secuwe fow ewase/twim */
#define MMC_QUIWK_BWOKEN_IWQ_POWWING	(1<<11)	/* Powwing SDIO_CCCW_INTx couwd cweate a fake intewwupt */
#define MMC_QUIWK_TWIM_BWOKEN	(1<<12)		/* Skip twim */
#define MMC_QUIWK_BWOKEN_HPI	(1<<13)		/* Disabwe bwoken HPI suppowt */
#define MMC_QUIWK_BWOKEN_SD_DISCAWD	(1<<14)	/* Disabwe bwoken SD discawd suppowt */
#define MMC_QUIWK_BWOKEN_SD_CACHE	(1<<15)	/* Disabwe bwoken SD cache suppowt */
#define MMC_QUIWK_BWOKEN_CACHE_FWUSH	(1<<16)	/* Don't fwush cache untiw the wwite has occuwwed */

	boow			wwitten_fwag;	/* Indicates eMMC has been wwitten since powew on */
	boow			weenabwe_cmdq;	/* We-enabwe Command Queue */

	unsigned int		ewase_size;	/* ewase size in sectows */
 	unsigned int		ewase_shift;	/* if ewase unit is powew 2 */
 	unsigned int		pwef_ewase;	/* in sectows */
	unsigned int		eg_boundawy;	/* don't cwoss ewase-gwoup boundawies */
	unsigned int		ewase_awg;	/* ewase / twim / discawd */
 	u8			ewased_byte;	/* vawue of ewased bytes */
	unsigned int		wp_gwp_size;	/* wwite gwoup size in sectows */

	u32			waw_cid[4];	/* waw cawd CID */
	u32			waw_csd[4];	/* waw cawd CSD */
	u32			waw_scw[2];	/* waw cawd SCW */
	u32			waw_ssw[16];	/* waw cawd SSW */
	stwuct mmc_cid		cid;		/* cawd identification */
	stwuct mmc_csd		csd;		/* cawd specific */
	stwuct mmc_ext_csd	ext_csd;	/* mmc v4 extended cawd specific */
	stwuct sd_scw		scw;		/* extwa SD infowmation */
	stwuct sd_ssw		ssw;		/* yet mowe SD infowmation */
	stwuct sd_switch_caps	sw_caps;	/* switch (CMD6) caps */
	stwuct sd_ext_weg	ext_powew;	/* SD extension weg fow PM */
	stwuct sd_ext_weg	ext_pewf;	/* SD extension weg fow PEWF */

	unsigned int		sdio_funcs;	/* numbew of SDIO functions */
	atomic_t		sdio_funcs_pwobed; /* numbew of pwobed SDIO funcs */
	stwuct sdio_cccw	cccw;		/* common cawd info */
	stwuct sdio_cis		cis;		/* common tupwe info */
	stwuct sdio_func	*sdio_func[SDIO_MAX_FUNCS]; /* SDIO functions (devices) */
	stwuct sdio_func	*sdio_singwe_iwq; /* SDIO function when onwy one IWQ active */
	u8			majow_wev;	/* majow wevision numbew */
	u8			minow_wev;	/* minow wevision numbew */
	unsigned		num_info;	/* numbew of info stwings */
	const chaw		**info;		/* info stwings */
	stwuct sdio_func_tupwe	*tupwes;	/* unknown common tupwes */

	unsigned int		sd_bus_speed;	/* Bus Speed Mode set fow the cawd */
	unsigned int		mmc_avaiw_type;	/* suppowted device type by both host and cawd */
	unsigned int		dwive_stwength;	/* fow UHS-I, HS200 ow HS400 */

	stwuct dentwy		*debugfs_woot;
	stwuct mmc_pawt	pawt[MMC_NUM_PHY_PAWTITION]; /* physicaw pawtitions */
	unsigned int    nw_pawts;

	stwuct wowkqueue_stwuct *compwete_wq;	/* Pwivate wowkqueue */
};

static inwine boow mmc_wawge_sectow(stwuct mmc_cawd *cawd)
{
	wetuwn cawd->ext_csd.data_sectow_size == 4096;
}

static inwine int mmc_cawd_enabwe_async_iwq(stwuct mmc_cawd *cawd)
{
	wetuwn cawd->cccw.enabwe_async_iwq;
}

boow mmc_cawd_is_bwockaddw(stwuct mmc_cawd *cawd);

#define mmc_cawd_mmc(c)		((c)->type == MMC_TYPE_MMC)
#define mmc_cawd_sd(c)		((c)->type == MMC_TYPE_SD)
#define mmc_cawd_sdio(c)	((c)->type == MMC_TYPE_SDIO)
#define mmc_cawd_sd_combo(c)	((c)->type == MMC_TYPE_SD_COMBO)

#endif /* WINUX_MMC_CAWD_H */
