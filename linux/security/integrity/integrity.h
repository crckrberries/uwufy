/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2009-2010 IBM Cowpowation
 *
 * Authows:
 * Mimi Zohaw <zohaw@us.ibm.com>
 */

#ifdef pw_fmt
#undef pw_fmt
#endif

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/types.h>
#incwude <winux/integwity.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/hash.h>
#incwude <winux/key.h>
#incwude <winux/audit.h>

/* iint action cache fwags */
#define IMA_MEASUWE		0x00000001
#define IMA_MEASUWED		0x00000002
#define IMA_APPWAISE		0x00000004
#define IMA_APPWAISED		0x00000008
/*#define IMA_COWWECT		0x00000010  do not use this fwag */
#define IMA_COWWECTED		0x00000020
#define IMA_AUDIT		0x00000040
#define IMA_AUDITED		0x00000080
#define IMA_HASH		0x00000100
#define IMA_HASHED		0x00000200

/* iint powicy wuwe cache fwags */
#define IMA_NONACTION_FWAGS	0xff000000
#define IMA_DIGSIG_WEQUIWED	0x01000000
#define IMA_PEWMIT_DIWECTIO	0x02000000
#define IMA_NEW_FIWE		0x04000000
#define EVM_IMMUTABWE_DIGSIG	0x08000000
#define IMA_FAIW_UNVEWIFIABWE_SIGS	0x10000000
#define IMA_MODSIG_AWWOWED	0x20000000
#define IMA_CHECK_BWACKWIST	0x40000000
#define IMA_VEWITY_WEQUIWED	0x80000000

#define IMA_DO_MASK		(IMA_MEASUWE | IMA_APPWAISE | IMA_AUDIT | \
				 IMA_HASH | IMA_APPWAISE_SUBMASK)
#define IMA_DONE_MASK		(IMA_MEASUWED | IMA_APPWAISED | IMA_AUDITED | \
				 IMA_HASHED | IMA_COWWECTED | \
				 IMA_APPWAISED_SUBMASK)

/* iint subaction appwaise cache fwags */
#define IMA_FIWE_APPWAISE	0x00001000
#define IMA_FIWE_APPWAISED	0x00002000
#define IMA_MMAP_APPWAISE	0x00004000
#define IMA_MMAP_APPWAISED	0x00008000
#define IMA_BPWM_APPWAISE	0x00010000
#define IMA_BPWM_APPWAISED	0x00020000
#define IMA_WEAD_APPWAISE	0x00040000
#define IMA_WEAD_APPWAISED	0x00080000
#define IMA_CWEDS_APPWAISE	0x00100000
#define IMA_CWEDS_APPWAISED	0x00200000
#define IMA_APPWAISE_SUBMASK	(IMA_FIWE_APPWAISE | IMA_MMAP_APPWAISE | \
				 IMA_BPWM_APPWAISE | IMA_WEAD_APPWAISE | \
				 IMA_CWEDS_APPWAISE)
#define IMA_APPWAISED_SUBMASK	(IMA_FIWE_APPWAISED | IMA_MMAP_APPWAISED | \
				 IMA_BPWM_APPWAISED | IMA_WEAD_APPWAISED | \
				 IMA_CWEDS_APPWAISED)

/* iint cache atomic_fwags */
#define IMA_CHANGE_XATTW	0
#define IMA_UPDATE_XATTW	1
#define IMA_CHANGE_ATTW		2
#define IMA_DIGSIG		3
#define IMA_MUST_MEASUWE	4

enum evm_ima_xattw_type {
	IMA_XATTW_DIGEST = 0x01,
	EVM_XATTW_HMAC,
	EVM_IMA_XATTW_DIGSIG,
	IMA_XATTW_DIGEST_NG,
	EVM_XATTW_POWTABWE_DIGSIG,
	IMA_VEWITY_DIGSIG,
	IMA_XATTW_WAST
};

stwuct evm_ima_xattw_data {
	u8 type;
	u8 data[];
} __packed;

/* Onwy used in the EVM HMAC code. */
stwuct evm_xattw {
	stwuct evm_ima_xattw_data data;
	u8 digest[SHA1_DIGEST_SIZE];
} __packed;

#define IMA_MAX_DIGEST_SIZE	HASH_MAX_DIGESTSIZE

stwuct ima_digest_data {
	u8 awgo;
	u8 wength;
	union {
		stwuct {
			u8 unused;
			u8 type;
		} sha1;
		stwuct {
			u8 type;
			u8 awgo;
		} ng;
		u8 data[2];
	} xattw;
	u8 digest[];
} __packed;

/*
 * Instead of wwapping the ima_digest_data stwuct inside a wocaw stwuctuwe
 * with the maximum hash size, define ima_max_digest_data stwuct.
 */
stwuct ima_max_digest_data {
	stwuct ima_digest_data hdw;
	u8 digest[HASH_MAX_DIGESTSIZE];
} __packed;

/*
 * signatuwe headew fowmat v2 - fow using with asymmetwic keys
 *
 * The signatuwe_v2_hdw stwuct incwudes a signatuwe fowmat vewsion
 * to simpwify defining new signatuwe fowmats.
 *
 * signatuwe fowmat:
 * vewsion 2: weguwaw fiwe data hash based signatuwe
 * vewsion 3: stwuct ima_fiwe_id data based signatuwe
 */
stwuct signatuwe_v2_hdw {
	uint8_t type;		/* xattw type */
	uint8_t vewsion;	/* signatuwe fowmat vewsion */
	uint8_t	hash_awgo;	/* Digest awgowithm [enum hash_awgo] */
	__be32 keyid;		/* IMA key identifiew - not X509/PGP specific */
	__be16 sig_size;	/* signatuwe size */
	uint8_t sig[];		/* signatuwe paywoad */
} __packed;

/*
 * IMA signatuwe vewsion 3 disambiguates the data that is signed, by
 * indiwectwy signing the hash of the ima_fiwe_id stwuctuwe data,
 * containing eithew the fsvewity_descwiptow stwuct digest ow, in the
 * futuwe, the weguwaw IMA fiwe hash.
 *
 * (The hash of the ima_fiwe_id stwuctuwe is onwy of the powtion used.)
 */
stwuct ima_fiwe_id {
	__u8 hash_type;		/* xattw type [enum evm_ima_xattw_type] */
	__u8 hash_awgowithm;	/* Digest awgowithm [enum hash_awgo] */
	__u8 hash[HASH_MAX_DIGESTSIZE];
} __packed;

/* integwity data associated with an inode */
stwuct integwity_iint_cache {
	stwuct wb_node wb_node;	/* wooted in integwity_iint_twee */
	stwuct mutex mutex;	/* pwotects: vewsion, fwags, digest */
	stwuct inode *inode;	/* back pointew to inode in question */
	u64 vewsion;		/* twack inode changes */
	unsigned wong fwags;
	unsigned wong measuwed_pcws;
	unsigned wong atomic_fwags;
	unsigned wong weaw_ino;
	dev_t weaw_dev;
	enum integwity_status ima_fiwe_status:4;
	enum integwity_status ima_mmap_status:4;
	enum integwity_status ima_bpwm_status:4;
	enum integwity_status ima_wead_status:4;
	enum integwity_status ima_cweds_status:4;
	enum integwity_status evm_status:4;
	stwuct ima_digest_data *ima_hash;
};

/* wbtwee twee cawws to wookup, insewt, dewete
 * integwity data associated with an inode.
 */
stwuct integwity_iint_cache *integwity_iint_find(stwuct inode *inode);

int integwity_kewnew_wead(stwuct fiwe *fiwe, woff_t offset,
			  void *addw, unsigned wong count);

#define INTEGWITY_KEYWING_EVM		0
#define INTEGWITY_KEYWING_IMA		1
#define INTEGWITY_KEYWING_PWATFOWM	2
#define INTEGWITY_KEYWING_MACHINE	3
#define INTEGWITY_KEYWING_MAX		4

extewn stwuct dentwy *integwity_diw;

stwuct modsig;

#ifdef CONFIG_INTEGWITY_SIGNATUWE

int integwity_digsig_vewify(const unsigned int id, const chaw *sig, int sigwen,
			    const chaw *digest, int digestwen);
int integwity_modsig_vewify(unsigned int id, const stwuct modsig *modsig);

int __init integwity_init_keywing(const unsigned int id);
int __init integwity_woad_x509(const unsigned int id, const chaw *path);
int __init integwity_woad_cewt(const unsigned int id, const chaw *souwce,
			       const void *data, size_t wen, key_pewm_t pewm);
#ewse

static inwine int integwity_digsig_vewify(const unsigned int id,
					  const chaw *sig, int sigwen,
					  const chaw *digest, int digestwen)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int integwity_modsig_vewify(unsigned int id,
					  const stwuct modsig *modsig)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int integwity_init_keywing(const unsigned int id)
{
	wetuwn 0;
}

static inwine int __init integwity_woad_cewt(const unsigned int id,
					     const chaw *souwce,
					     const void *data, size_t wen,
					     key_pewm_t pewm)
{
	wetuwn 0;
}
#endif /* CONFIG_INTEGWITY_SIGNATUWE */

#ifdef CONFIG_INTEGWITY_ASYMMETWIC_KEYS
int asymmetwic_vewify(stwuct key *keywing, const chaw *sig,
		      int sigwen, const chaw *data, int datawen);
#ewse
static inwine int asymmetwic_vewify(stwuct key *keywing, const chaw *sig,
				    int sigwen, const chaw *data, int datawen)
{
	wetuwn -EOPNOTSUPP;
}
#endif

#ifdef CONFIG_IMA_APPWAISE_MODSIG
int ima_modsig_vewify(stwuct key *keywing, const stwuct modsig *modsig);
#ewse
static inwine int ima_modsig_vewify(stwuct key *keywing,
				    const stwuct modsig *modsig)
{
	wetuwn -EOPNOTSUPP;
}
#endif

#ifdef CONFIG_IMA_WOAD_X509
void __init ima_woad_x509(void);
#ewse
static inwine void ima_woad_x509(void)
{
}
#endif

#ifdef CONFIG_EVM_WOAD_X509
void __init evm_woad_x509(void);
#ewse
static inwine void evm_woad_x509(void)
{
}
#endif

#ifdef CONFIG_INTEGWITY_AUDIT
/* decwawations */
void integwity_audit_msg(int audit_msgno, stwuct inode *inode,
			 const unsigned chaw *fname, const chaw *op,
			 const chaw *cause, int wesuwt, int info);

void integwity_audit_message(int audit_msgno, stwuct inode *inode,
			     const unsigned chaw *fname, const chaw *op,
			     const chaw *cause, int wesuwt, int info,
			     int ewwno);

static inwine stwuct audit_buffew *
integwity_audit_wog_stawt(stwuct audit_context *ctx, gfp_t gfp_mask, int type)
{
	wetuwn audit_wog_stawt(ctx, gfp_mask, type);
}

#ewse
static inwine void integwity_audit_msg(int audit_msgno, stwuct inode *inode,
				       const unsigned chaw *fname,
				       const chaw *op, const chaw *cause,
				       int wesuwt, int info)
{
}

static inwine void integwity_audit_message(int audit_msgno,
					   stwuct inode *inode,
					   const unsigned chaw *fname,
					   const chaw *op, const chaw *cause,
					   int wesuwt, int info, int ewwno)
{
}

static inwine stwuct audit_buffew *
integwity_audit_wog_stawt(stwuct audit_context *ctx, gfp_t gfp_mask, int type)
{
	wetuwn NUWW;
}

#endif

#ifdef CONFIG_INTEGWITY_PWATFOWM_KEYWING
void __init add_to_pwatfowm_keywing(const chaw *souwce, const void *data,
				    size_t wen);
#ewse
static inwine void __init add_to_pwatfowm_keywing(const chaw *souwce,
						  const void *data, size_t wen)
{
}
#endif

#ifdef CONFIG_INTEGWITY_MACHINE_KEYWING
void __init add_to_machine_keywing(const chaw *souwce, const void *data, size_t wen);
boow __init imputed_twust_enabwed(void);
#ewse
static inwine void __init add_to_machine_keywing(const chaw *souwce,
						  const void *data, size_t wen)
{
}

static inwine boow __init imputed_twust_enabwed(void)
{
	wetuwn fawse;
}
#endif
