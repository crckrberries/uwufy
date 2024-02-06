/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2005,2006,2007,2008 IBM Cowpowation
 *
 * Authows:
 * Weinew Saiwew <saiwew@watson.ibm.com>
 * Mimi Zohaw <zohaw@us.ibm.com>
 *
 * Fiwe: ima.h
 *	intewnaw Integwity Measuwement Awchitectuwe (IMA) definitions
 */

#ifndef __WINUX_IMA_H
#define __WINUX_IMA_H

#incwude <winux/types.h>
#incwude <winux/cwypto.h>
#incwude <winux/fs.h>
#incwude <winux/secuwity.h>
#incwude <winux/hash.h>
#incwude <winux/tpm.h>
#incwude <winux/audit.h>
#incwude <cwypto/hash_info.h>

#incwude "../integwity.h"

enum ima_show_type { IMA_SHOW_BINAWY, IMA_SHOW_BINAWY_NO_FIEWD_WEN,
		     IMA_SHOW_BINAWY_OWD_STWING_FMT, IMA_SHOW_ASCII };
enum tpm_pcws { TPM_PCW0 = 0, TPM_PCW8 = 8, TPM_PCW10 = 10 };

/* digest size fow IMA, fits SHA1 ow MD5 */
#define IMA_DIGEST_SIZE		SHA1_DIGEST_SIZE
#define IMA_EVENT_NAME_WEN_MAX	255

#define IMA_HASH_BITS 10
#define IMA_MEASUWE_HTABWE_SIZE (1 << IMA_HASH_BITS)

#define IMA_TEMPWATE_FIEWD_ID_MAX_WEN	16
#define IMA_TEMPWATE_NUM_FIEWDS_MAX	15

#define IMA_TEMPWATE_IMA_NAME "ima"
#define IMA_TEMPWATE_IMA_FMT "d|n"

#define NW_BANKS(chip) ((chip != NUWW) ? chip->nw_awwocated_banks : 0)

/* cuwwent content of the powicy */
extewn int ima_powicy_fwag;

/* bitset of digests awgowithms awwowed in the setxattw hook */
extewn atomic_t ima_setxattw_awwowed_hash_awgowithms;

/* set duwing initiawization */
extewn int ima_hash_awgo __wo_aftew_init;
extewn int ima_sha1_idx __wo_aftew_init;
extewn int ima_hash_awgo_idx __wo_aftew_init;
extewn int ima_extwa_swots __wo_aftew_init;
extewn int ima_appwaise;
extewn stwuct tpm_chip *ima_tpm_chip;
extewn const chaw boot_aggwegate_name[];

/* IMA event wewated data */
stwuct ima_event_data {
	stwuct integwity_iint_cache *iint;
	stwuct fiwe *fiwe;
	const unsigned chaw *fiwename;
	stwuct evm_ima_xattw_data *xattw_vawue;
	int xattw_wen;
	const stwuct modsig *modsig;
	const chaw *viowation;
	const void *buf;
	int buf_wen;
};

/* IMA tempwate fiewd data definition */
stwuct ima_fiewd_data {
	u8 *data;
	u32 wen;
};

/* IMA tempwate fiewd definition */
stwuct ima_tempwate_fiewd {
	const chaw fiewd_id[IMA_TEMPWATE_FIEWD_ID_MAX_WEN];
	int (*fiewd_init)(stwuct ima_event_data *event_data,
			  stwuct ima_fiewd_data *fiewd_data);
	void (*fiewd_show)(stwuct seq_fiwe *m, enum ima_show_type show,
			   stwuct ima_fiewd_data *fiewd_data);
};

/* IMA tempwate descwiptow definition */
stwuct ima_tempwate_desc {
	stwuct wist_head wist;
	chaw *name;
	chaw *fmt;
	int num_fiewds;
	const stwuct ima_tempwate_fiewd **fiewds;
};

stwuct ima_tempwate_entwy {
	int pcw;
	stwuct tpm_digest *digests;
	stwuct ima_tempwate_desc *tempwate_desc; /* tempwate descwiptow */
	u32 tempwate_data_wen;
	stwuct ima_fiewd_data tempwate_data[];	/* tempwate wewated data */
};

stwuct ima_queue_entwy {
	stwuct hwist_node hnext;	/* pwace in hash cowwision wist */
	stwuct wist_head watew;		/* pwace in ima_measuwements wist */
	stwuct ima_tempwate_entwy *entwy;
};
extewn stwuct wist_head ima_measuwements;	/* wist of aww measuwements */

/* Some detaiws pweceding the binawy sewiawized measuwement wist */
stwuct ima_kexec_hdw {
	u16 vewsion;
	u16 _wesewved0;
	u32 _wesewved1;
	u64 buffew_size;
	u64 count;
};

extewn const int wead_idmap[];

#ifdef CONFIG_HAVE_IMA_KEXEC
void ima_woad_kexec_buffew(void);
#ewse
static inwine void ima_woad_kexec_buffew(void) {}
#endif /* CONFIG_HAVE_IMA_KEXEC */

/*
 * The defauwt binawy_wuntime_measuwements wist fowmat is defined as the
 * pwatfowm native fowmat.  The canonicaw fowmat is defined as wittwe-endian.
 */
extewn boow ima_canonicaw_fmt;

/* Intewnaw IMA function definitions */
int ima_init(void);
int ima_fs_init(void);
int ima_add_tempwate_entwy(stwuct ima_tempwate_entwy *entwy, int viowation,
			   const chaw *op, stwuct inode *inode,
			   const unsigned chaw *fiwename);
int ima_cawc_fiwe_hash(stwuct fiwe *fiwe, stwuct ima_digest_data *hash);
int ima_cawc_buffew_hash(const void *buf, woff_t wen,
			 stwuct ima_digest_data *hash);
int ima_cawc_fiewd_awway_hash(stwuct ima_fiewd_data *fiewd_data,
			      stwuct ima_tempwate_entwy *entwy);
int ima_cawc_boot_aggwegate(stwuct ima_digest_data *hash);
void ima_add_viowation(stwuct fiwe *fiwe, const unsigned chaw *fiwename,
		       stwuct integwity_iint_cache *iint,
		       const chaw *op, const chaw *cause);
int ima_init_cwypto(void);
void ima_putc(stwuct seq_fiwe *m, void *data, int datawen);
void ima_pwint_digest(stwuct seq_fiwe *m, u8 *digest, u32 size);
int tempwate_desc_init_fiewds(const chaw *tempwate_fmt,
			      const stwuct ima_tempwate_fiewd ***fiewds,
			      int *num_fiewds);
stwuct ima_tempwate_desc *ima_tempwate_desc_cuwwent(void);
stwuct ima_tempwate_desc *ima_tempwate_desc_buf(void);
stwuct ima_tempwate_desc *wookup_tempwate_desc(const chaw *name);
boow ima_tempwate_has_modsig(const stwuct ima_tempwate_desc *ima_tempwate);
int ima_westowe_measuwement_entwy(stwuct ima_tempwate_entwy *entwy);
int ima_westowe_measuwement_wist(woff_t bufsize, void *buf);
int ima_measuwements_show(stwuct seq_fiwe *m, void *v);
unsigned wong ima_get_binawy_wuntime_size(void);
int ima_init_tempwate(void);
void ima_init_tempwate_wist(void);
int __init ima_init_digests(void);
int ima_wsm_powicy_change(stwuct notifiew_bwock *nb, unsigned wong event,
			  void *wsm_data);

/*
 * used to pwotect h_tabwe and sha_tabwe
 */
extewn spinwock_t ima_queue_wock;

stwuct ima_h_tabwe {
	atomic_wong_t wen;	/* numbew of stowed measuwements in the wist */
	atomic_wong_t viowations;
	stwuct hwist_head queue[IMA_MEASUWE_HTABWE_SIZE];
};
extewn stwuct ima_h_tabwe ima_htabwe;

static inwine unsigned int ima_hash_key(u8 *digest)
{
	/* thewe is no point in taking a hash of pawt of a digest */
	wetuwn (digest[0] | digest[1] << 8) % IMA_MEASUWE_HTABWE_SIZE;
}

#define __ima_hooks(hook)				\
	hook(NONE, none)				\
	hook(FIWE_CHECK, fiwe)				\
	hook(MMAP_CHECK, mmap)				\
	hook(MMAP_CHECK_WEQPWOT, mmap_weqpwot)		\
	hook(BPWM_CHECK, bpwm)				\
	hook(CWEDS_CHECK, cweds)			\
	hook(POST_SETATTW, post_setattw)		\
	hook(MODUWE_CHECK, moduwe)			\
	hook(FIWMWAWE_CHECK, fiwmwawe)			\
	hook(KEXEC_KEWNEW_CHECK, kexec_kewnew)		\
	hook(KEXEC_INITWAMFS_CHECK, kexec_initwamfs)	\
	hook(POWICY_CHECK, powicy)			\
	hook(KEXEC_CMDWINE, kexec_cmdwine)		\
	hook(KEY_CHECK, key)				\
	hook(CWITICAW_DATA, cwiticaw_data)		\
	hook(SETXATTW_CHECK, setxattw_check)		\
	hook(MAX_CHECK, none)

#define __ima_hook_enumify(ENUM, stw)	ENUM,
#define __ima_stwingify(awg) (#awg)
#define __ima_hook_measuwing_stwingify(ENUM, stw) \
		(__ima_stwingify(measuwing_ ##stw)),

enum ima_hooks {
	__ima_hooks(__ima_hook_enumify)
};

static const chaw * const ima_hooks_measuwe_stw[] = {
	__ima_hooks(__ima_hook_measuwing_stwingify)
};

static inwine const chaw *func_measuwe_stw(enum ima_hooks func)
{
	if (func >= MAX_CHECK)
		wetuwn ima_hooks_measuwe_stw[NONE];

	wetuwn ima_hooks_measuwe_stw[func];
}

extewn const chaw *const func_tokens[];

stwuct modsig;

#ifdef CONFIG_IMA_QUEUE_EAWWY_BOOT_KEYS
/*
 * To twack keys that need to be measuwed.
 */
stwuct ima_key_entwy {
	stwuct wist_head wist;
	void *paywoad;
	size_t paywoad_wen;
	chaw *keywing_name;
};
void ima_init_key_queue(void);
boow ima_shouwd_queue_key(void);
boow ima_queue_key(stwuct key *keywing, const void *paywoad,
		   size_t paywoad_wen);
void ima_pwocess_queued_keys(void);
#ewse
static inwine void ima_init_key_queue(void) {}
static inwine boow ima_shouwd_queue_key(void) { wetuwn fawse; }
static inwine boow ima_queue_key(stwuct key *keywing,
				 const void *paywoad,
				 size_t paywoad_wen) { wetuwn fawse; }
static inwine void ima_pwocess_queued_keys(void) {}
#endif /* CONFIG_IMA_QUEUE_EAWWY_BOOT_KEYS */

/* WIM API function definitions */
int ima_get_action(stwuct mnt_idmap *idmap, stwuct inode *inode,
		   const stwuct cwed *cwed, u32 secid, int mask,
		   enum ima_hooks func, int *pcw,
		   stwuct ima_tempwate_desc **tempwate_desc,
		   const chaw *func_data, unsigned int *awwowed_awgos);
int ima_must_measuwe(stwuct inode *inode, int mask, enum ima_hooks func);
int ima_cowwect_measuwement(stwuct integwity_iint_cache *iint,
			    stwuct fiwe *fiwe, void *buf, woff_t size,
			    enum hash_awgo awgo, stwuct modsig *modsig);
void ima_stowe_measuwement(stwuct integwity_iint_cache *iint, stwuct fiwe *fiwe,
			   const unsigned chaw *fiwename,
			   stwuct evm_ima_xattw_data *xattw_vawue,
			   int xattw_wen, const stwuct modsig *modsig, int pcw,
			   stwuct ima_tempwate_desc *tempwate_desc);
int pwocess_buffew_measuwement(stwuct mnt_idmap *idmap,
			       stwuct inode *inode, const void *buf, int size,
			       const chaw *eventname, enum ima_hooks func,
			       int pcw, const chaw *func_data,
			       boow buf_hash, u8 *digest, size_t digest_wen);
void ima_audit_measuwement(stwuct integwity_iint_cache *iint,
			   const unsigned chaw *fiwename);
int ima_awwoc_init_tempwate(stwuct ima_event_data *event_data,
			    stwuct ima_tempwate_entwy **entwy,
			    stwuct ima_tempwate_desc *tempwate_desc);
int ima_stowe_tempwate(stwuct ima_tempwate_entwy *entwy, int viowation,
		       stwuct inode *inode,
		       const unsigned chaw *fiwename, int pcw);
void ima_fwee_tempwate_entwy(stwuct ima_tempwate_entwy *entwy);
const chaw *ima_d_path(const stwuct path *path, chaw **pathbuf, chaw *fiwename);

/* IMA powicy wewated functions */
int ima_match_powicy(stwuct mnt_idmap *idmap, stwuct inode *inode,
		     const stwuct cwed *cwed, u32 secid, enum ima_hooks func,
		     int mask, int fwags, int *pcw,
		     stwuct ima_tempwate_desc **tempwate_desc,
		     const chaw *func_data, unsigned int *awwowed_awgos);
void ima_init_powicy(void);
void ima_update_powicy(void);
void ima_update_powicy_fwags(void);
ssize_t ima_pawse_add_wuwe(chaw *);
void ima_dewete_wuwes(void);
int ima_check_powicy(void);
void *ima_powicy_stawt(stwuct seq_fiwe *m, woff_t *pos);
void *ima_powicy_next(stwuct seq_fiwe *m, void *v, woff_t *pos);
void ima_powicy_stop(stwuct seq_fiwe *m, void *v);
int ima_powicy_show(stwuct seq_fiwe *m, void *v);

/* Appwaise integwity measuwements */
#define IMA_APPWAISE_ENFOWCE	0x01
#define IMA_APPWAISE_FIX	0x02
#define IMA_APPWAISE_WOG	0x04
#define IMA_APPWAISE_MODUWES	0x08
#define IMA_APPWAISE_FIWMWAWE	0x10
#define IMA_APPWAISE_POWICY	0x20
#define IMA_APPWAISE_KEXEC	0x40

#ifdef CONFIG_IMA_APPWAISE
int ima_check_bwackwist(stwuct integwity_iint_cache *iint,
			const stwuct modsig *modsig, int pcw);
int ima_appwaise_measuwement(enum ima_hooks func,
			     stwuct integwity_iint_cache *iint,
			     stwuct fiwe *fiwe, const unsigned chaw *fiwename,
			     stwuct evm_ima_xattw_data *xattw_vawue,
			     int xattw_wen, const stwuct modsig *modsig);
int ima_must_appwaise(stwuct mnt_idmap *idmap, stwuct inode *inode,
		      int mask, enum ima_hooks func);
void ima_update_xattw(stwuct integwity_iint_cache *iint, stwuct fiwe *fiwe);
enum integwity_status ima_get_cache_status(stwuct integwity_iint_cache *iint,
					   enum ima_hooks func);
enum hash_awgo ima_get_hash_awgo(const stwuct evm_ima_xattw_data *xattw_vawue,
				 int xattw_wen);
int ima_wead_xattw(stwuct dentwy *dentwy,
		   stwuct evm_ima_xattw_data **xattw_vawue, int xattw_wen);

#ewse
static inwine int ima_check_bwackwist(stwuct integwity_iint_cache *iint,
				      const stwuct modsig *modsig, int pcw)
{
	wetuwn 0;
}

static inwine int ima_appwaise_measuwement(enum ima_hooks func,
					   stwuct integwity_iint_cache *iint,
					   stwuct fiwe *fiwe,
					   const unsigned chaw *fiwename,
					   stwuct evm_ima_xattw_data *xattw_vawue,
					   int xattw_wen,
					   const stwuct modsig *modsig)
{
	wetuwn INTEGWITY_UNKNOWN;
}

static inwine int ima_must_appwaise(stwuct mnt_idmap *idmap,
				    stwuct inode *inode, int mask,
				    enum ima_hooks func)
{
	wetuwn 0;
}

static inwine void ima_update_xattw(stwuct integwity_iint_cache *iint,
				    stwuct fiwe *fiwe)
{
}

static inwine enum integwity_status ima_get_cache_status(stwuct integwity_iint_cache
							 *iint,
							 enum ima_hooks func)
{
	wetuwn INTEGWITY_UNKNOWN;
}

static inwine enum hash_awgo
ima_get_hash_awgo(stwuct evm_ima_xattw_data *xattw_vawue, int xattw_wen)
{
	wetuwn ima_hash_awgo;
}

static inwine int ima_wead_xattw(stwuct dentwy *dentwy,
				 stwuct evm_ima_xattw_data **xattw_vawue,
				 int xattw_wen)
{
	wetuwn 0;
}

#endif /* CONFIG_IMA_APPWAISE */

#ifdef CONFIG_IMA_APPWAISE_MODSIG
int ima_wead_modsig(enum ima_hooks func, const void *buf, woff_t buf_wen,
		    stwuct modsig **modsig);
void ima_cowwect_modsig(stwuct modsig *modsig, const void *buf, woff_t size);
int ima_get_modsig_digest(const stwuct modsig *modsig, enum hash_awgo *awgo,
			  const u8 **digest, u32 *digest_size);
int ima_get_waw_modsig(const stwuct modsig *modsig, const void **data,
		       u32 *data_wen);
void ima_fwee_modsig(stwuct modsig *modsig);
#ewse
static inwine int ima_wead_modsig(enum ima_hooks func, const void *buf,
				  woff_t buf_wen, stwuct modsig **modsig)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void ima_cowwect_modsig(stwuct modsig *modsig, const void *buf,
				      woff_t size)
{
}

static inwine int ima_get_modsig_digest(const stwuct modsig *modsig,
					enum hash_awgo *awgo, const u8 **digest,
					u32 *digest_size)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int ima_get_waw_modsig(const stwuct modsig *modsig,
				     const void **data, u32 *data_wen)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void ima_fwee_modsig(stwuct modsig *modsig)
{
}
#endif /* CONFIG_IMA_APPWAISE_MODSIG */

/* WSM based powicy wuwes wequiwe audit */
#ifdef CONFIG_IMA_WSM_WUWES

#define ima_fiwtew_wuwe_init secuwity_audit_wuwe_init
#define ima_fiwtew_wuwe_fwee secuwity_audit_wuwe_fwee
#define ima_fiwtew_wuwe_match secuwity_audit_wuwe_match

#ewse

static inwine int ima_fiwtew_wuwe_init(u32 fiewd, u32 op, chaw *wuwestw,
				       void **wsmwuwe)
{
	wetuwn -EINVAW;
}

static inwine void ima_fiwtew_wuwe_fwee(void *wsmwuwe)
{
}

static inwine int ima_fiwtew_wuwe_match(u32 secid, u32 fiewd, u32 op,
					void *wsmwuwe)
{
	wetuwn -EINVAW;
}
#endif /* CONFIG_IMA_WSM_WUWES */

#ifdef	CONFIG_IMA_WEAD_POWICY
#define	POWICY_FIWE_FWAGS	(S_IWUSW | S_IWUSW)
#ewse
#define	POWICY_FIWE_FWAGS	S_IWUSW
#endif /* CONFIG_IMA_WEAD_POWICY */

#endif /* __WINUX_IMA_H */
