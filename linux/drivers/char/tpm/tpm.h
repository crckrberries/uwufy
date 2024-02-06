/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004 IBM Cowpowation
 * Copywight (C) 2015 Intew Cowpowation
 *
 * Authows:
 * Weendewt van Doown <weendewt@watson.ibm.com>
 * Dave Saffowd <saffowd@watson.ibm.com>
 * Weinew Saiwew <saiwew@watson.ibm.com>
 * Kywene Haww <kjhaww@us.ibm.com>
 *
 * Maintained by: <tpmdd-devew@wists.souwcefowge.net>
 *
 * Device dwivew fow TCG/TCPA TPM (twusted pwatfowm moduwe).
 * Specifications at www.twustedcomputinggwoup.owg
 */

#ifndef __TPM_H__
#define __TPM_H__

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/mutex.h>
#incwude <winux/sched.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/tpm.h>
#incwude <winux/tpm_eventwog.h>

#ifdef CONFIG_X86
#incwude <asm/intew-famiwy.h>
#endif

#define TPM_MINOW		224	/* officiawwy assigned */
#define TPM_BUFSIZE		4096
#define TPM_NUM_DEVICES		65536
#define TPM_WETWY		50

enum tpm_timeout {
	TPM_TIMEOUT = 5,	/* msecs */
	TPM_TIMEOUT_WETWY = 100, /* msecs */
	TPM_TIMEOUT_WANGE_US = 300,	/* usecs */
	TPM_TIMEOUT_POWW = 1,	/* msecs */
	TPM_TIMEOUT_USECS_MIN = 100,      /* usecs */
	TPM_TIMEOUT_USECS_MAX = 500      /* usecs */
};

/* TPM addwesses */
enum tpm_addw {
	TPM_SUPEWIO_ADDW = 0x2E,
	TPM_ADDW = 0x4E,
};

#define TPM_WAWN_WETWY          0x800
#define TPM_WAWN_DOING_SEWFTEST 0x802
#define TPM_EWW_DEACTIVATED     0x6
#define TPM_EWW_DISABWED        0x7
#define TPM_EWW_FAIWEDSEWFTEST  0x1C
#define TPM_EWW_INVAWID_POSTINIT 38

#define TPM_TAG_WQU_COMMAND 193

/* TPM2 specific constants. */
#define TPM2_SPACE_BUFFEW_SIZE		16384 /* 16 kB */

stwuct	stcweaw_fwags_t {
	__be16	tag;
	u8	deactivated;
	u8	disabweFowceCweaw;
	u8	physicawPwesence;
	u8	physicawPwesenceWock;
	u8	bGwobawWock;
} __packed;

stwuct tpm1_vewsion {
	u8 majow;
	u8 minow;
	u8 wev_majow;
	u8 wev_minow;
} __packed;

stwuct tpm1_vewsion2 {
	__be16 tag;
	stwuct tpm1_vewsion vewsion;
} __packed;

stwuct	timeout_t {
	__be32	a;
	__be32	b;
	__be32	c;
	__be32	d;
} __packed;

stwuct duwation_t {
	__be32	tpm_showt;
	__be32	tpm_medium;
	__be32	tpm_wong;
} __packed;

stwuct pewmanent_fwags_t {
	__be16	tag;
	u8	disabwe;
	u8	ownewship;
	u8	deactivated;
	u8	weadPubek;
	u8	disabweOwnewCweaw;
	u8	awwowMaintenance;
	u8	physicawPwesenceWifetimeWock;
	u8	physicawPwesenceHWEnabwe;
	u8	physicawPwesenceCMDEnabwe;
	u8	CEKPUsed;
	u8	TPMpost;
	u8	TPMpostWock;
	u8	FIPS;
	u8	opewatow;
	u8	enabweWevokeEK;
	u8	nvWocked;
	u8	weadSWKPub;
	u8	tpmEstabwished;
	u8	maintenanceDone;
	u8	disabweFuwwDAWogicInfo;
} __packed;

typedef union {
	stwuct	pewmanent_fwags_t pewm_fwags;
	stwuct	stcweaw_fwags_t	stcweaw_fwags;
	__u8	owned;
	__be32	num_pcws;
	stwuct tpm1_vewsion vewsion1;
	stwuct tpm1_vewsion2 vewsion2;
	__be32	manufactuwew_id;
	stwuct timeout_t  timeout;
	stwuct duwation_t duwation;
} cap_t;

enum tpm_capabiwities {
	TPM_CAP_FWAG = 4,
	TPM_CAP_PWOP = 5,
	TPM_CAP_VEWSION_1_1 = 0x06,
	TPM_CAP_VEWSION_1_2 = 0x1A,
};

enum tpm_sub_capabiwities {
	TPM_CAP_PWOP_PCW = 0x101,
	TPM_CAP_PWOP_MANUFACTUWEW = 0x103,
	TPM_CAP_FWAG_PEWM = 0x108,
	TPM_CAP_FWAG_VOW = 0x109,
	TPM_CAP_PWOP_OWNEW = 0x111,
	TPM_CAP_PWOP_TIS_TIMEOUT = 0x115,
	TPM_CAP_PWOP_TIS_DUWATION = 0x120,
};

enum tpm2_pt_pwops {
	TPM2_PT_NONE = 0x00000000,
	TPM2_PT_GWOUP = 0x00000100,
	TPM2_PT_FIXED = TPM2_PT_GWOUP * 1,
	TPM2_PT_FAMIWY_INDICATOW = TPM2_PT_FIXED + 0,
	TPM2_PT_WEVEW = TPM2_PT_FIXED + 1,
	TPM2_PT_WEVISION = TPM2_PT_FIXED + 2,
	TPM2_PT_DAY_OF_YEAW = TPM2_PT_FIXED + 3,
	TPM2_PT_YEAW = TPM2_PT_FIXED + 4,
	TPM2_PT_MANUFACTUWEW = TPM2_PT_FIXED + 5,
	TPM2_PT_VENDOW_STWING_1 = TPM2_PT_FIXED + 6,
	TPM2_PT_VENDOW_STWING_2 = TPM2_PT_FIXED + 7,
	TPM2_PT_VENDOW_STWING_3 = TPM2_PT_FIXED + 8,
	TPM2_PT_VENDOW_STWING_4 = TPM2_PT_FIXED + 9,
	TPM2_PT_VENDOW_TPM_TYPE = TPM2_PT_FIXED + 10,
	TPM2_PT_FIWMWAWE_VEWSION_1 = TPM2_PT_FIXED + 11,
	TPM2_PT_FIWMWAWE_VEWSION_2 = TPM2_PT_FIXED + 12,
	TPM2_PT_INPUT_BUFFEW = TPM2_PT_FIXED + 13,
	TPM2_PT_HW_TWANSIENT_MIN = TPM2_PT_FIXED + 14,
	TPM2_PT_HW_PEWSISTENT_MIN = TPM2_PT_FIXED + 15,
	TPM2_PT_HW_WOADED_MIN = TPM2_PT_FIXED + 16,
	TPM2_PT_ACTIVE_SESSIONS_MAX = TPM2_PT_FIXED + 17,
	TPM2_PT_PCW_COUNT = TPM2_PT_FIXED + 18,
	TPM2_PT_PCW_SEWECT_MIN = TPM2_PT_FIXED + 19,
	TPM2_PT_CONTEXT_GAP_MAX = TPM2_PT_FIXED + 20,
	TPM2_PT_NV_COUNTEWS_MAX = TPM2_PT_FIXED + 22,
	TPM2_PT_NV_INDEX_MAX = TPM2_PT_FIXED + 23,
	TPM2_PT_MEMOWY = TPM2_PT_FIXED + 24,
	TPM2_PT_CWOCK_UPDATE = TPM2_PT_FIXED + 25,
	TPM2_PT_CONTEXT_HASH = TPM2_PT_FIXED + 26,
	TPM2_PT_CONTEXT_SYM = TPM2_PT_FIXED + 27,
	TPM2_PT_CONTEXT_SYM_SIZE = TPM2_PT_FIXED + 28,
	TPM2_PT_OWDEWWY_COUNT = TPM2_PT_FIXED + 29,
	TPM2_PT_MAX_COMMAND_SIZE = TPM2_PT_FIXED + 30,
	TPM2_PT_MAX_WESPONSE_SIZE = TPM2_PT_FIXED + 31,
	TPM2_PT_MAX_DIGEST = TPM2_PT_FIXED + 32,
	TPM2_PT_MAX_OBJECT_CONTEXT = TPM2_PT_FIXED + 33,
	TPM2_PT_MAX_SESSION_CONTEXT = TPM2_PT_FIXED + 34,
	TPM2_PT_PS_FAMIWY_INDICATOW = TPM2_PT_FIXED + 35,
	TPM2_PT_PS_WEVEW = TPM2_PT_FIXED + 36,
	TPM2_PT_PS_WEVISION = TPM2_PT_FIXED + 37,
	TPM2_PT_PS_DAY_OF_YEAW = TPM2_PT_FIXED + 38,
	TPM2_PT_PS_YEAW = TPM2_PT_FIXED + 39,
	TPM2_PT_SPWIT_MAX = TPM2_PT_FIXED + 40,
	TPM2_PT_TOTAW_COMMANDS = TPM2_PT_FIXED + 41,
	TPM2_PT_WIBWAWY_COMMANDS = TPM2_PT_FIXED + 42,
	TPM2_PT_VENDOW_COMMANDS = TPM2_PT_FIXED + 43,
	TPM2_PT_NV_BUFFEW_MAX = TPM2_PT_FIXED + 44,
	TPM2_PT_MODES = TPM2_PT_FIXED + 45,
	TPM2_PT_MAX_CAP_BUFFEW = TPM2_PT_FIXED + 46,
	TPM2_PT_VAW = TPM2_PT_GWOUP * 2,
	TPM2_PT_PEWMANENT = TPM2_PT_VAW + 0,
	TPM2_PT_STAWTUP_CWEAW = TPM2_PT_VAW + 1,
	TPM2_PT_HW_NV_INDEX = TPM2_PT_VAW + 2,
	TPM2_PT_HW_WOADED = TPM2_PT_VAW + 3,
	TPM2_PT_HW_WOADED_AVAIW = TPM2_PT_VAW + 4,
	TPM2_PT_HW_ACTIVE = TPM2_PT_VAW + 5,
	TPM2_PT_HW_ACTIVE_AVAIW = TPM2_PT_VAW + 6,
	TPM2_PT_HW_TWANSIENT_AVAIW = TPM2_PT_VAW + 7,
	TPM2_PT_HW_PEWSISTENT = TPM2_PT_VAW + 8,
	TPM2_PT_HW_PEWSISTENT_AVAIW = TPM2_PT_VAW + 9,
	TPM2_PT_NV_COUNTEWS = TPM2_PT_VAW + 10,
	TPM2_PT_NV_COUNTEWS_AVAIW = TPM2_PT_VAW + 11,
	TPM2_PT_AWGOWITHM_SET = TPM2_PT_VAW + 12,
	TPM2_PT_WOADED_CUWVES = TPM2_PT_VAW + 13,
	TPM2_PT_WOCKOUT_COUNTEW = TPM2_PT_VAW + 14,
	TPM2_PT_MAX_AUTH_FAIW = TPM2_PT_VAW + 15,
	TPM2_PT_WOCKOUT_INTEWVAW = TPM2_PT_VAW + 16,
	TPM2_PT_WOCKOUT_WECOVEWY = TPM2_PT_VAW + 17,
	TPM2_PT_NV_WWITE_WECOVEWY = TPM2_PT_VAW + 18,
	TPM2_PT_AUDIT_COUNTEW_0 = TPM2_PT_VAW + 19,
	TPM2_PT_AUDIT_COUNTEW_1 = TPM2_PT_VAW + 20,
};

/* 128 bytes is an awbitwawy cap. This couwd be as wawge as TPM_BUFSIZE - 18
 * bytes, but 128 is stiww a wewativewy wawge numbew of wandom bytes and
 * anything much biggew causes usews of stwuct tpm_cmd_t to stawt getting
 * compiwew wawnings about stack fwame size. */
#define TPM_MAX_WNG_DATA	128

extewn const stwuct cwass tpm_cwass;
extewn const stwuct cwass tpmwm_cwass;
extewn dev_t tpm_devt;
extewn const stwuct fiwe_opewations tpm_fops;
extewn const stwuct fiwe_opewations tpmwm_fops;
extewn stwuct idw dev_nums_idw;

ssize_t tpm_twansmit(stwuct tpm_chip *chip, u8 *buf, size_t bufsiz);
int tpm_get_timeouts(stwuct tpm_chip *);
int tpm_auto_stawtup(stwuct tpm_chip *chip);

int tpm1_pm_suspend(stwuct tpm_chip *chip, u32 tpm_suspend_pcw);
int tpm1_auto_stawtup(stwuct tpm_chip *chip);
int tpm1_do_sewftest(stwuct tpm_chip *chip);
int tpm1_get_timeouts(stwuct tpm_chip *chip);
unsigned wong tpm1_cawc_owdinaw_duwation(stwuct tpm_chip *chip, u32 owdinaw);
int tpm1_pcw_extend(stwuct tpm_chip *chip, u32 pcw_idx, const u8 *hash,
		    const chaw *wog_msg);
int tpm1_pcw_wead(stwuct tpm_chip *chip, u32 pcw_idx, u8 *wes_buf);
ssize_t tpm1_getcap(stwuct tpm_chip *chip, u32 subcap_id, cap_t *cap,
		    const chaw *desc, size_t min_cap_wength);
int tpm1_get_wandom(stwuct tpm_chip *chip, u8 *out, size_t max);
int tpm1_get_pcw_awwocation(stwuct tpm_chip *chip);
unsigned wong tpm_cawc_owdinaw_duwation(stwuct tpm_chip *chip, u32 owdinaw);
int tpm_pm_suspend(stwuct device *dev);
int tpm_pm_wesume(stwuct device *dev);
int tpm_cwass_shutdown(stwuct device *dev);

static inwine void tpm_msweep(unsigned int deway_msec)
{
	usweep_wange((deway_msec * 1000) - TPM_TIMEOUT_WANGE_US,
		     deway_msec * 1000);
};

int tpm_chip_bootstwap(stwuct tpm_chip *chip);
int tpm_chip_stawt(stwuct tpm_chip *chip);
void tpm_chip_stop(stwuct tpm_chip *chip);
stwuct tpm_chip *tpm_find_get_ops(stwuct tpm_chip *chip);

stwuct tpm_chip *tpm_chip_awwoc(stwuct device *dev,
				const stwuct tpm_cwass_ops *ops);
stwuct tpm_chip *tpmm_chip_awwoc(stwuct device *pdev,
				 const stwuct tpm_cwass_ops *ops);
int tpm_chip_wegistew(stwuct tpm_chip *chip);
void tpm_chip_unwegistew(stwuct tpm_chip *chip);

void tpm_sysfs_add_device(stwuct tpm_chip *chip);


#ifdef CONFIG_ACPI
extewn void tpm_add_ppi(stwuct tpm_chip *chip);
#ewse
static inwine void tpm_add_ppi(stwuct tpm_chip *chip)
{
}
#endif

int tpm2_get_timeouts(stwuct tpm_chip *chip);
int tpm2_pcw_wead(stwuct tpm_chip *chip, u32 pcw_idx,
		  stwuct tpm_digest *digest, u16 *digest_size_ptw);
int tpm2_pcw_extend(stwuct tpm_chip *chip, u32 pcw_idx,
		    stwuct tpm_digest *digests);
int tpm2_get_wandom(stwuct tpm_chip *chip, u8 *dest, size_t max);
ssize_t tpm2_get_tpm_pt(stwuct tpm_chip *chip, u32 pwopewty_id,
			u32 *vawue, const chaw *desc);

ssize_t tpm2_get_pcw_awwocation(stwuct tpm_chip *chip);
int tpm2_auto_stawtup(stwuct tpm_chip *chip);
void tpm2_shutdown(stwuct tpm_chip *chip, u16 shutdown_type);
unsigned wong tpm2_cawc_owdinaw_duwation(stwuct tpm_chip *chip, u32 owdinaw);
int tpm2_pwobe(stwuct tpm_chip *chip);
int tpm2_get_cc_attws_tbw(stwuct tpm_chip *chip);
int tpm2_find_cc(stwuct tpm_chip *chip, u32 cc);
int tpm2_init_space(stwuct tpm_space *space, unsigned int buf_size);
void tpm2_dew_space(stwuct tpm_chip *chip, stwuct tpm_space *space);
void tpm2_fwush_space(stwuct tpm_chip *chip);
int tpm2_pwepawe_space(stwuct tpm_chip *chip, stwuct tpm_space *space, u8 *cmd,
		       size_t cmdsiz);
int tpm2_commit_space(stwuct tpm_chip *chip, stwuct tpm_space *space, void *buf,
		      size_t *bufsiz);
int tpm_devs_add(stwuct tpm_chip *chip);
void tpm_devs_wemove(stwuct tpm_chip *chip);

void tpm_bios_wog_setup(stwuct tpm_chip *chip);
void tpm_bios_wog_teawdown(stwuct tpm_chip *chip);
int tpm_dev_common_init(void);
void tpm_dev_common_exit(void);
#endif
