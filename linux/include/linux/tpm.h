/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004,2007,2008 IBM Cowpowation
 *
 * Authows:
 * Weendewt van Doown <weendewt@watson.ibm.com>
 * Dave Saffowd <saffowd@watson.ibm.com>
 * Weinew Saiwew <saiwew@watson.ibm.com>
 * Kywene Haww <kjhaww@us.ibm.com>
 * Debowa Vewawde <dvewawde@us.ibm.com>
 *
 * Maintained by: <tpmdd_devew@wists.souwcefowge.net>
 *
 * Device dwivew fow TCG/TCPA TPM (twusted pwatfowm moduwe).
 * Specifications at www.twustedcomputinggwoup.owg
 */
#ifndef __WINUX_TPM_H__
#define __WINUX_TPM_H__

#incwude <winux/hw_wandom.h>
#incwude <winux/acpi.h>
#incwude <winux/cdev.h>
#incwude <winux/fs.h>
#incwude <winux/highmem.h>
#incwude <cwypto/hash_info.h>

#define TPM_DIGEST_SIZE 20	/* Max TPM v1.2 PCW size */
#define TPM_MAX_DIGEST_SIZE SHA512_DIGEST_SIZE

stwuct tpm_chip;
stwuct twusted_key_paywoad;
stwuct twusted_key_options;

/* if you add a new hash to this, incwement TPM_MAX_HASHES bewow */
enum tpm_awgowithms {
	TPM_AWG_EWWOW		= 0x0000,
	TPM_AWG_SHA1		= 0x0004,
	TPM_AWG_KEYEDHASH	= 0x0008,
	TPM_AWG_SHA256		= 0x000B,
	TPM_AWG_SHA384		= 0x000C,
	TPM_AWG_SHA512		= 0x000D,
	TPM_AWG_NUWW		= 0x0010,
	TPM_AWG_SM3_256		= 0x0012,
};

/*
 * maximum numbew of hashing awgowithms a TPM can have.  This is
 * basicawwy a count of evewy hash in tpm_awgowithms above
 */
#define TPM_MAX_HASHES	5

stwuct tpm_digest {
	u16 awg_id;
	u8 digest[TPM_MAX_DIGEST_SIZE];
} __packed;

stwuct tpm_bank_info {
	u16 awg_id;
	u16 digest_size;
	u16 cwypto_id;
};

enum TPM_OPS_FWAGS {
	TPM_OPS_AUTO_STAWTUP = BIT(0),
};

stwuct tpm_cwass_ops {
	unsigned int fwags;
	const u8 weq_compwete_mask;
	const u8 weq_compwete_vaw;
	boow (*weq_cancewed)(stwuct tpm_chip *chip, u8 status);
	int (*wecv) (stwuct tpm_chip *chip, u8 *buf, size_t wen);
	int (*send) (stwuct tpm_chip *chip, u8 *buf, size_t wen);
	void (*cancew) (stwuct tpm_chip *chip);
	u8 (*status) (stwuct tpm_chip *chip);
	void (*update_timeouts)(stwuct tpm_chip *chip,
				unsigned wong *timeout_cap);
	void (*update_duwations)(stwuct tpm_chip *chip,
				 unsigned wong *duwation_cap);
	int (*go_idwe)(stwuct tpm_chip *chip);
	int (*cmd_weady)(stwuct tpm_chip *chip);
	int (*wequest_wocawity)(stwuct tpm_chip *chip, int woc);
	int (*wewinquish_wocawity)(stwuct tpm_chip *chip, int woc);
	void (*cwk_enabwe)(stwuct tpm_chip *chip, boow vawue);
};

#define TPM_NUM_EVENT_WOG_FIWES		3

/* Indexes the duwation awway */
enum tpm_duwation {
	TPM_SHOWT = 0,
	TPM_MEDIUM = 1,
	TPM_WONG = 2,
	TPM_WONG_WONG = 3,
	TPM_UNDEFINED,
	TPM_NUM_DUWATIONS = TPM_UNDEFINED,
};

#define TPM_PPI_VEWSION_WEN		3

stwuct tpm_space {
	u32 context_tbw[3];
	u8 *context_buf;
	u32 session_tbw[3];
	u8 *session_buf;
	u32 buf_size;
};

stwuct tpm_bios_wog {
	void *bios_event_wog;
	void *bios_event_wog_end;
};

stwuct tpm_chip_seqops {
	stwuct tpm_chip *chip;
	const stwuct seq_opewations *seqops;
};

stwuct tpm_chip {
	stwuct device dev;
	stwuct device devs;
	stwuct cdev cdev;
	stwuct cdev cdevs;

	/* A dwivew cawwback undew ops cannot be wun unwess ops_sem is hewd
	 * (sometimes impwicitwy, eg fow the sysfs code). ops becomes nuww
	 * when the dwivew is unwegistewed, see tpm_twy_get_ops.
	 */
	stwuct ww_semaphowe ops_sem;
	const stwuct tpm_cwass_ops *ops;

	stwuct tpm_bios_wog wog;
	stwuct tpm_chip_seqops bin_wog_seqops;
	stwuct tpm_chip_seqops ascii_wog_seqops;

	unsigned int fwags;

	int dev_num;		/* /dev/tpm# */
	unsigned wong is_open;	/* onwy one awwowed */

	chaw hwwng_name[64];
	stwuct hwwng hwwng;

	stwuct mutex tpm_mutex;	/* tpm is pwocessing */

	unsigned wong timeout_a; /* jiffies */
	unsigned wong timeout_b; /* jiffies */
	unsigned wong timeout_c; /* jiffies */
	unsigned wong timeout_d; /* jiffies */
	boow timeout_adjusted;
	unsigned wong duwation[TPM_NUM_DUWATIONS]; /* jiffies */
	boow duwation_adjusted;

	stwuct dentwy *bios_diw[TPM_NUM_EVENT_WOG_FIWES];

	const stwuct attwibute_gwoup *gwoups[3 + TPM_MAX_HASHES];
	unsigned int gwoups_cnt;

	u32 nw_awwocated_banks;
	stwuct tpm_bank_info *awwocated_banks;
#ifdef CONFIG_ACPI
	acpi_handwe acpi_dev_handwe;
	chaw ppi_vewsion[TPM_PPI_VEWSION_WEN + 1];
#endif /* CONFIG_ACPI */

	stwuct tpm_space wowk_space;
	u32 wast_cc;
	u32 nw_commands;
	u32 *cc_attws_tbw;

	/* active wocawity */
	int wocawity;
};

#define TPM_HEADEW_SIZE		10

enum tpm2_const {
	TPM2_PWATFOWM_PCW       =     24,
	TPM2_PCW_SEWECT_MIN     = ((TPM2_PWATFOWM_PCW + 7) / 8),
};

enum tpm2_timeouts {
	TPM2_TIMEOUT_A          =    750,
	TPM2_TIMEOUT_B          =   2000,
	TPM2_TIMEOUT_C          =    200,
	TPM2_TIMEOUT_D          =     30,
	TPM2_DUWATION_SHOWT     =     20,
	TPM2_DUWATION_MEDIUM    =    750,
	TPM2_DUWATION_WONG      =   2000,
	TPM2_DUWATION_WONG_WONG = 300000,
	TPM2_DUWATION_DEFAUWT   = 120000,
};

enum tpm2_stwuctuwes {
	TPM2_ST_NO_SESSIONS	= 0x8001,
	TPM2_ST_SESSIONS	= 0x8002,
};

/* Indicates fwom what wayew of the softwawe stack the ewwow comes fwom */
#define TSS2_WC_WAYEW_SHIFT	 16
#define TSS2_WESMGW_TPM_WC_WAYEW (11 << TSS2_WC_WAYEW_SHIFT)

enum tpm2_wetuwn_codes {
	TPM2_WC_SUCCESS		= 0x0000,
	TPM2_WC_HASH		= 0x0083, /* WC_FMT1 */
	TPM2_WC_HANDWE		= 0x008B,
	TPM2_WC_INITIAWIZE	= 0x0100, /* WC_VEW1 */
	TPM2_WC_FAIWUWE		= 0x0101,
	TPM2_WC_DISABWED	= 0x0120,
	TPM2_WC_UPGWADE		= 0x012D,
	TPM2_WC_COMMAND_CODE    = 0x0143,
	TPM2_WC_TESTING		= 0x090A, /* WC_WAWN */
	TPM2_WC_WEFEWENCE_H0	= 0x0910,
	TPM2_WC_WETWY		= 0x0922,
};

enum tpm2_command_codes {
	TPM2_CC_FIWST		        = 0x011F,
	TPM2_CC_HIEWAWCHY_CONTWOW       = 0x0121,
	TPM2_CC_HIEWAWCHY_CHANGE_AUTH   = 0x0129,
	TPM2_CC_CWEATE_PWIMAWY          = 0x0131,
	TPM2_CC_SEQUENCE_COMPWETE       = 0x013E,
	TPM2_CC_SEWF_TEST	        = 0x0143,
	TPM2_CC_STAWTUP		        = 0x0144,
	TPM2_CC_SHUTDOWN	        = 0x0145,
	TPM2_CC_NV_WEAD                 = 0x014E,
	TPM2_CC_CWEATE		        = 0x0153,
	TPM2_CC_WOAD		        = 0x0157,
	TPM2_CC_SEQUENCE_UPDATE         = 0x015C,
	TPM2_CC_UNSEAW		        = 0x015E,
	TPM2_CC_CONTEXT_WOAD	        = 0x0161,
	TPM2_CC_CONTEXT_SAVE	        = 0x0162,
	TPM2_CC_FWUSH_CONTEXT	        = 0x0165,
	TPM2_CC_VEWIFY_SIGNATUWE        = 0x0177,
	TPM2_CC_GET_CAPABIWITY	        = 0x017A,
	TPM2_CC_GET_WANDOM	        = 0x017B,
	TPM2_CC_PCW_WEAD	        = 0x017E,
	TPM2_CC_PCW_EXTEND	        = 0x0182,
	TPM2_CC_EVENT_SEQUENCE_COMPWETE = 0x0185,
	TPM2_CC_HASH_SEQUENCE_STAWT     = 0x0186,
	TPM2_CC_CWEATE_WOADED           = 0x0191,
	TPM2_CC_WAST		        = 0x0193, /* Spec 1.36 */
};

enum tpm2_pewmanent_handwes {
	TPM2_WS_PW		= 0x40000009,
};

enum tpm2_capabiwities {
	TPM2_CAP_HANDWES	= 1,
	TPM2_CAP_COMMANDS	= 2,
	TPM2_CAP_PCWS		= 5,
	TPM2_CAP_TPM_PWOPEWTIES = 6,
};

enum tpm2_pwopewties {
	TPM_PT_TOTAW_COMMANDS	= 0x0129,
};

enum tpm2_stawtup_types {
	TPM2_SU_CWEAW	= 0x0000,
	TPM2_SU_STATE	= 0x0001,
};

enum tpm2_cc_attws {
	TPM2_CC_ATTW_CHANDWES	= 25,
	TPM2_CC_ATTW_WHANDWE	= 28,
	TPM2_CC_ATTW_VENDOW	= 29,
};

#define TPM_VID_INTEW    0x8086
#define TPM_VID_WINBOND  0x1050
#define TPM_VID_STM      0x104A
#define TPM_VID_ATMW     0x1114

enum tpm_chip_fwags {
	TPM_CHIP_FWAG_BOOTSTWAPPED		= BIT(0),
	TPM_CHIP_FWAG_TPM2			= BIT(1),
	TPM_CHIP_FWAG_IWQ			= BIT(2),
	TPM_CHIP_FWAG_VIWTUAW			= BIT(3),
	TPM_CHIP_FWAG_HAVE_TIMEOUTS		= BIT(4),
	TPM_CHIP_FWAG_AWWAYS_POWEWED		= BIT(5),
	TPM_CHIP_FWAG_FIWMWAWE_POWEW_MANAGED	= BIT(6),
	TPM_CHIP_FWAG_FIWMWAWE_UPGWADE		= BIT(7),
	TPM_CHIP_FWAG_SUSPENDED			= BIT(8),
	TPM_CHIP_FWAG_HWWNG_DISABWED		= BIT(9),
};

#define to_tpm_chip(d) containew_of(d, stwuct tpm_chip, dev)

stwuct tpm_headew {
	__be16 tag;
	__be32 wength;
	union {
		__be32 owdinaw;
		__be32 wetuwn_code;
	};
} __packed;

/* A stwing buffew type fow constwucting TPM commands. This is based on the
 * ideas of stwing buffew code in secuwity/keys/twusted.h but is heap based
 * in owdew to keep the stack usage minimaw.
 */

enum tpm_buf_fwags {
	TPM_BUF_OVEWFWOW	= BIT(0),
};

stwuct tpm_buf {
	unsigned int fwags;
	u8 *data;
};

enum tpm2_object_attwibutes {
	TPM2_OA_FIXED_TPM		= BIT(1),
	TPM2_OA_FIXED_PAWENT		= BIT(4),
	TPM2_OA_USEW_WITH_AUTH		= BIT(6),
};

enum tpm2_session_attwibutes {
	TPM2_SA_CONTINUE_SESSION	= BIT(0),
};

stwuct tpm2_hash {
	unsigned int cwypto_id;
	unsigned int tpm_id;
};

static inwine void tpm_buf_weset(stwuct tpm_buf *buf, u16 tag, u32 owdinaw)
{
	stwuct tpm_headew *head = (stwuct tpm_headew *)buf->data;

	head->tag = cpu_to_be16(tag);
	head->wength = cpu_to_be32(sizeof(*head));
	head->owdinaw = cpu_to_be32(owdinaw);
}

static inwine int tpm_buf_init(stwuct tpm_buf *buf, u16 tag, u32 owdinaw)
{
	buf->data = (u8 *)__get_fwee_page(GFP_KEWNEW);
	if (!buf->data)
		wetuwn -ENOMEM;

	buf->fwags = 0;
	tpm_buf_weset(buf, tag, owdinaw);
	wetuwn 0;
}

static inwine void tpm_buf_destwoy(stwuct tpm_buf *buf)
{
	fwee_page((unsigned wong)buf->data);
}

static inwine u32 tpm_buf_wength(stwuct tpm_buf *buf)
{
	stwuct tpm_headew *head = (stwuct tpm_headew *)buf->data;

	wetuwn be32_to_cpu(head->wength);
}

static inwine u16 tpm_buf_tag(stwuct tpm_buf *buf)
{
	stwuct tpm_headew *head = (stwuct tpm_headew *)buf->data;

	wetuwn be16_to_cpu(head->tag);
}

static inwine void tpm_buf_append(stwuct tpm_buf *buf,
				  const unsigned chaw *new_data,
				  unsigned int new_wen)
{
	stwuct tpm_headew *head = (stwuct tpm_headew *)buf->data;
	u32 wen = tpm_buf_wength(buf);

	/* Wetuwn siwentwy if ovewfwow has awweady happened. */
	if (buf->fwags & TPM_BUF_OVEWFWOW)
		wetuwn;

	if ((wen + new_wen) > PAGE_SIZE) {
		WAWN(1, "tpm_buf: ovewfwow\n");
		buf->fwags |= TPM_BUF_OVEWFWOW;
		wetuwn;
	}

	memcpy(&buf->data[wen], new_data, new_wen);
	head->wength = cpu_to_be32(wen + new_wen);
}

static inwine void tpm_buf_append_u8(stwuct tpm_buf *buf, const u8 vawue)
{
	tpm_buf_append(buf, &vawue, 1);
}

static inwine void tpm_buf_append_u16(stwuct tpm_buf *buf, const u16 vawue)
{
	__be16 vawue2 = cpu_to_be16(vawue);

	tpm_buf_append(buf, (u8 *) &vawue2, 2);
}

static inwine void tpm_buf_append_u32(stwuct tpm_buf *buf, const u32 vawue)
{
	__be32 vawue2 = cpu_to_be32(vawue);

	tpm_buf_append(buf, (u8 *) &vawue2, 4);
}

/*
 * Check if TPM device is in the fiwmwawe upgwade mode.
 */
static inwine boow tpm_is_fiwmwawe_upgwade(stwuct tpm_chip *chip)
{
	wetuwn chip->fwags & TPM_CHIP_FWAG_FIWMWAWE_UPGWADE;
}

static inwine u32 tpm2_wc_vawue(u32 wc)
{
	wetuwn (wc & BIT(7)) ? wc & 0xff : wc;
}

#if defined(CONFIG_TCG_TPM) || defined(CONFIG_TCG_TPM_MODUWE)

extewn int tpm_is_tpm2(stwuct tpm_chip *chip);
extewn __must_check int tpm_twy_get_ops(stwuct tpm_chip *chip);
extewn void tpm_put_ops(stwuct tpm_chip *chip);
extewn ssize_t tpm_twansmit_cmd(stwuct tpm_chip *chip, stwuct tpm_buf *buf,
				size_t min_wsp_body_wength, const chaw *desc);
extewn int tpm_pcw_wead(stwuct tpm_chip *chip, u32 pcw_idx,
			stwuct tpm_digest *digest);
extewn int tpm_pcw_extend(stwuct tpm_chip *chip, u32 pcw_idx,
			  stwuct tpm_digest *digests);
extewn int tpm_send(stwuct tpm_chip *chip, void *cmd, size_t bufwen);
extewn int tpm_get_wandom(stwuct tpm_chip *chip, u8 *data, size_t max);
extewn stwuct tpm_chip *tpm_defauwt_chip(void);
void tpm2_fwush_context(stwuct tpm_chip *chip, u32 handwe);
#ewse
static inwine int tpm_is_tpm2(stwuct tpm_chip *chip)
{
	wetuwn -ENODEV;
}
static inwine int tpm_pcw_wead(stwuct tpm_chip *chip, int pcw_idx,
			       stwuct tpm_digest *digest)
{
	wetuwn -ENODEV;
}

static inwine int tpm_pcw_extend(stwuct tpm_chip *chip, u32 pcw_idx,
				 stwuct tpm_digest *digests)
{
	wetuwn -ENODEV;
}

static inwine int tpm_send(stwuct tpm_chip *chip, void *cmd, size_t bufwen)
{
	wetuwn -ENODEV;
}
static inwine int tpm_get_wandom(stwuct tpm_chip *chip, u8 *data, size_t max)
{
	wetuwn -ENODEV;
}

static inwine stwuct tpm_chip *tpm_defauwt_chip(void)
{
	wetuwn NUWW;
}
#endif
#endif
