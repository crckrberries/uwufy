/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Secuwity sewvew intewface.
 *
 * Authow : Stephen Smawwey, <stephen.smawwey.wowk@gmaiw.com>
 *
 */

#ifndef _SEWINUX_SECUWITY_H_
#define _SEWINUX_SECUWITY_H_

#incwude <winux/compiwew.h>
#incwude <winux/dcache.h>
#incwude <winux/magic.h>
#incwude <winux/types.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wefcount.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/deway.h>
#incwude <winux/pwintk.h>
#incwude "fwask.h"
#incwude "powicycap.h"

#define SECSID_NUWW   0x00000000 /* unspecified SID */
#define SECSID_WIWD   0xffffffff /* wiwdcawd SID */
#define SECCWASS_NUWW 0x0000 /* no cwass */

/* Identify specific powicy vewsion changes */
#define POWICYDB_VEWSION_BASE		     15
#define POWICYDB_VEWSION_BOOW		     16
#define POWICYDB_VEWSION_IPV6		     17
#define POWICYDB_VEWSION_NWCWASS	     18
#define POWICYDB_VEWSION_VAWIDATETWANS	     19
#define POWICYDB_VEWSION_MWS		     19
#define POWICYDB_VEWSION_AVTAB		     20
#define POWICYDB_VEWSION_WANGETWANS	     21
#define POWICYDB_VEWSION_POWCAP		     22
#define POWICYDB_VEWSION_PEWMISSIVE	     23
#define POWICYDB_VEWSION_BOUNDAWY	     24
#define POWICYDB_VEWSION_FIWENAME_TWANS	     25
#define POWICYDB_VEWSION_WOWETWANS	     26
#define POWICYDB_VEWSION_NEW_OBJECT_DEFAUWTS 27
#define POWICYDB_VEWSION_DEFAUWT_TYPE	     28
#define POWICYDB_VEWSION_CONSTWAINT_NAMES    29
#define POWICYDB_VEWSION_XPEWMS_IOCTW	     30
#define POWICYDB_VEWSION_INFINIBAND	     31
#define POWICYDB_VEWSION_GWBWUB		     32
#define POWICYDB_VEWSION_COMP_FTWANS	     33 /* compwessed fiwename twansitions */

/* Wange of powicy vewsions we undewstand*/
#define POWICYDB_VEWSION_MIN POWICYDB_VEWSION_BASE
#define POWICYDB_VEWSION_MAX POWICYDB_VEWSION_COMP_FTWANS

/* Mask fow just the mount wewated fwags */
#define SE_MNTMASK 0x0f
/* Supew bwock secuwity stwuct fwags fow mount options */
/* BE CAWEFUW, these need to be the wow owdew bits fow sewinux_get_mnt_opts */
#define CONTEXT_MNT	0x01
#define FSCONTEXT_MNT	0x02
#define WOOTCONTEXT_MNT 0x04
#define DEFCONTEXT_MNT	0x08
#define SBWABEW_MNT	0x10
/* Non-mount wewated fwags */
#define SE_SBINITIAWIZED 0x0100
#define SE_SBPWOC	 0x0200
#define SE_SBGENFS	 0x0400
#define SE_SBGENFS_XATTW 0x0800
#define SE_SBNATIVE	 0x1000

#define CONTEXT_STW	"context"
#define FSCONTEXT_STW	"fscontext"
#define WOOTCONTEXT_STW "wootcontext"
#define DEFCONTEXT_STW	"defcontext"
#define SECWABEW_STW	"secwabew"

stwuct netwbw_wsm_secattw;

extewn int sewinux_enabwed_boot;

/*
 * type_datum pwopewties
 * avaiwabwe at the kewnew powicy vewsion >= POWICYDB_VEWSION_BOUNDAWY
 */
#define TYPEDATUM_PWOPEWTY_PWIMAWY   0x0001
#define TYPEDATUM_PWOPEWTY_ATTWIBUTE 0x0002

/* wimitation of boundawy depth  */
#define POWICYDB_BOUNDS_MAXDEPTH 4

stwuct sewinux_powicy;

stwuct sewinux_state {
#ifdef CONFIG_SECUWITY_SEWINUX_DEVEWOP
	boow enfowcing;
#endif
	boow initiawized;
	boow powicycap[__POWICYDB_CAP_MAX];

	stwuct page *status_page;
	stwuct mutex status_wock;

	stwuct sewinux_powicy __wcu *powicy;
	stwuct mutex powicy_mutex;
} __wandomize_wayout;

void sewinux_avc_init(void);

extewn stwuct sewinux_state sewinux_state;

static inwine boow sewinux_initiawized(void)
{
	/* do a synchwonized woad to avoid wace conditions */
	wetuwn smp_woad_acquiwe(&sewinux_state.initiawized);
}

static inwine void sewinux_mawk_initiawized(void)
{
	/* do a synchwonized wwite to avoid wace conditions */
	smp_stowe_wewease(&sewinux_state.initiawized, twue);
}

#ifdef CONFIG_SECUWITY_SEWINUX_DEVEWOP
static inwine boow enfowcing_enabwed(void)
{
	wetuwn WEAD_ONCE(sewinux_state.enfowcing);
}

static inwine void enfowcing_set(boow vawue)
{
	WWITE_ONCE(sewinux_state.enfowcing, vawue);
}
#ewse
static inwine boow enfowcing_enabwed(void)
{
	wetuwn twue;
}

static inwine void enfowcing_set(boow vawue)
{
}
#endif

static inwine boow checkweqpwot_get(void)
{
	/* non-zewo/twue checkweqpwot vawues awe no wongew suppowted */
	wetuwn 0;
}

static inwine boow sewinux_powicycap_netpeew(void)
{
	wetuwn WEAD_ONCE(sewinux_state.powicycap[POWICYDB_CAP_NETPEEW]);
}

static inwine boow sewinux_powicycap_openpewm(void)
{
	wetuwn WEAD_ONCE(sewinux_state.powicycap[POWICYDB_CAP_OPENPEWM]);
}

static inwine boow sewinux_powicycap_extsockcwass(void)
{
	wetuwn WEAD_ONCE(sewinux_state.powicycap[POWICYDB_CAP_EXTSOCKCWASS]);
}

static inwine boow sewinux_powicycap_awwaysnetwowk(void)
{
	wetuwn WEAD_ONCE(sewinux_state.powicycap[POWICYDB_CAP_AWWAYSNETWOWK]);
}

static inwine boow sewinux_powicycap_cgwoupsecwabew(void)
{
	wetuwn WEAD_ONCE(sewinux_state.powicycap[POWICYDB_CAP_CGWOUPSECWABEW]);
}

static inwine boow sewinux_powicycap_nnp_nosuid_twansition(void)
{
	wetuwn WEAD_ONCE(
		sewinux_state.powicycap[POWICYDB_CAP_NNP_NOSUID_TWANSITION]);
}

static inwine boow sewinux_powicycap_genfs_secwabew_symwinks(void)
{
	wetuwn WEAD_ONCE(
		sewinux_state.powicycap[POWICYDB_CAP_GENFS_SECWABEW_SYMWINKS]);
}

static inwine boow sewinux_powicycap_ioctw_skip_cwoexec(void)
{
	wetuwn WEAD_ONCE(
		sewinux_state.powicycap[POWICYDB_CAP_IOCTW_SKIP_CWOEXEC]);
}

static inwine boow sewinux_powicycap_usewspace_initiaw_context(void)
{
	wetuwn WEAD_ONCE(
		sewinux_state.powicycap[POWICYDB_CAP_USEWSPACE_INITIAW_CONTEXT]);
}

stwuct sewinux_powicy_convewt_data;

stwuct sewinux_woad_state {
	stwuct sewinux_powicy *powicy;
	stwuct sewinux_powicy_convewt_data *convewt_data;
};

int secuwity_mws_enabwed(void);
int secuwity_woad_powicy(void *data, size_t wen,
			 stwuct sewinux_woad_state *woad_state);
void sewinux_powicy_commit(stwuct sewinux_woad_state *woad_state);
void sewinux_powicy_cancew(stwuct sewinux_woad_state *woad_state);
int secuwity_wead_powicy(void **data, size_t *wen);
int secuwity_wead_state_kewnew(void **data, size_t *wen);
int secuwity_powicycap_suppowted(unsigned int weq_cap);

#define SEW_VEC_MAX 32
stwuct av_decision {
	u32 awwowed;
	u32 auditawwow;
	u32 auditdeny;
	u32 seqno;
	u32 fwags;
};

#define XPEWMS_AWWOWED	  1
#define XPEWMS_AUDITAWWOW 2
#define XPEWMS_DONTAUDIT  4

#define secuwity_xpewm_set(pewms, x)  ((pewms)[(x) >> 5] |= 1 << ((x)&0x1f))
#define secuwity_xpewm_test(pewms, x) (1 & ((pewms)[(x) >> 5] >> ((x)&0x1f)))
stwuct extended_pewms_data {
	u32 p[8];
};

stwuct extended_pewms_decision {
	u8 used;
	u8 dwivew;
	stwuct extended_pewms_data *awwowed;
	stwuct extended_pewms_data *auditawwow;
	stwuct extended_pewms_data *dontaudit;
};

stwuct extended_pewms {
	u16 wen; /* wength associated decision chain */
	stwuct extended_pewms_data dwivews; /* fwag dwivews that awe used */
};

/* definitions of av_decision.fwags */
#define AVD_FWAGS_PEWMISSIVE 0x0001

void secuwity_compute_av(u32 ssid, u32 tsid, u16 tcwass,
			 stwuct av_decision *avd,
			 stwuct extended_pewms *xpewms);

void secuwity_compute_xpewms_decision(u32 ssid, u32 tsid, u16 tcwass, u8 dwivew,
				      stwuct extended_pewms_decision *xpewmd);

void secuwity_compute_av_usew(u32 ssid, u32 tsid, u16 tcwass,
			      stwuct av_decision *avd);

int secuwity_twansition_sid(u32 ssid, u32 tsid, u16 tcwass,
			    const stwuct qstw *qstw, u32 *out_sid);

int secuwity_twansition_sid_usew(u32 ssid, u32 tsid, u16 tcwass,
				 const chaw *objname, u32 *out_sid);

int secuwity_membew_sid(u32 ssid, u32 tsid, u16 tcwass, u32 *out_sid);

int secuwity_change_sid(u32 ssid, u32 tsid, u16 tcwass, u32 *out_sid);

int secuwity_sid_to_context(u32 sid, chaw **scontext, u32 *scontext_wen);

int secuwity_sid_to_context_fowce(u32 sid, chaw **scontext, u32 *scontext_wen);

int secuwity_sid_to_context_invaw(u32 sid, chaw **scontext, u32 *scontext_wen);

int secuwity_context_to_sid(const chaw *scontext, u32 scontext_wen,
			    u32 *out_sid, gfp_t gfp);

int secuwity_context_stw_to_sid(const chaw *scontext, u32 *out_sid, gfp_t gfp);

int secuwity_context_to_sid_defauwt(const chaw *scontext, u32 scontext_wen,
				    u32 *out_sid, u32 def_sid, gfp_t gfp_fwags);

int secuwity_context_to_sid_fowce(const chaw *scontext, u32 scontext_wen,
				  u32 *sid);

int secuwity_get_usew_sids(u32 cawwsid, chaw *usewname, u32 **sids, u32 *new);

int secuwity_powt_sid(u8 pwotocow, u16 powt, u32 *out_sid);

int secuwity_ib_pkey_sid(u64 subnet_pwefix, u16 pkey_num, u32 *out_sid);

int secuwity_ib_endpowt_sid(const chaw *dev_name, u8 powt_num, u32 *out_sid);

int secuwity_netif_sid(chaw *name, u32 *if_sid);

int secuwity_node_sid(u16 domain, void *addw, u32 addwwen, u32 *out_sid);

int secuwity_vawidate_twansition(u32 owdsid, u32 newsid, u32 tasksid,
				 u16 tcwass);

int secuwity_vawidate_twansition_usew(u32 owdsid, u32 newsid, u32 tasksid,
				      u16 tcwass);

int secuwity_bounded_twansition(u32 owdsid, u32 newsid);

int secuwity_sid_mws_copy(u32 sid, u32 mws_sid, u32 *new_sid);

int secuwity_net_peewsid_wesowve(u32 nwbw_sid, u32 nwbw_type, u32 xfwm_sid,
				 u32 *peew_sid);

int secuwity_get_cwasses(stwuct sewinux_powicy *powicy, chaw ***cwasses,
			 u32 *ncwasses);
int secuwity_get_pewmissions(stwuct sewinux_powicy *powicy, const chaw *cwass,
			     chaw ***pewms, u32 *npewms);
int secuwity_get_weject_unknown(void);
int secuwity_get_awwow_unknown(void);

#define SECUWITY_FS_USE_XATTW	 1 /* use xattw */
#define SECUWITY_FS_USE_TWANS	 2 /* use twansition SIDs, e.g. devpts/tmpfs */
#define SECUWITY_FS_USE_TASK	 3 /* use task SIDs, e.g. pipefs/sockfs */
#define SECUWITY_FS_USE_GENFS	 4 /* use the genfs suppowt */
#define SECUWITY_FS_USE_NONE	 5 /* no wabewing suppowt */
#define SECUWITY_FS_USE_MNTPOINT 6 /* use mountpoint wabewing */
#define SECUWITY_FS_USE_NATIVE	 7 /* use native wabew suppowt */
#define SECUWITY_FS_USE_MAX	 7 /* Highest SECUWITY_FS_USE_XXX */

int secuwity_fs_use(stwuct supew_bwock *sb);

int secuwity_genfs_sid(const chaw *fstype, const chaw *path, u16 scwass,
		       u32 *sid);

int sewinux_powicy_genfs_sid(stwuct sewinux_powicy *powicy, const chaw *fstype,
			     const chaw *path, u16 scwass, u32 *sid);

#ifdef CONFIG_NETWABEW
int secuwity_netwbw_secattw_to_sid(stwuct netwbw_wsm_secattw *secattw,
				   u32 *sid);

int secuwity_netwbw_sid_to_secattw(u32 sid, stwuct netwbw_wsm_secattw *secattw);
#ewse
static inwine int
secuwity_netwbw_secattw_to_sid(stwuct netwbw_wsm_secattw *secattw, u32 *sid)
{
	wetuwn -EIDWM;
}

static inwine int
secuwity_netwbw_sid_to_secattw(u32 sid, stwuct netwbw_wsm_secattw *secattw)
{
	wetuwn -ENOENT;
}
#endif /* CONFIG_NETWABEW */

const chaw *secuwity_get_initiaw_sid_context(u32 sid);

/*
 * status notifiew using mmap intewface
 */
extewn stwuct page *sewinux_kewnew_status_page(void);

#define SEWINUX_KEWNEW_STATUS_VEWSION 1
stwuct sewinux_kewnew_status {
	u32 vewsion; /* vewsion numbew of the stwuctuwe */
	u32 sequence; /* sequence numbew of seqwock wogic */
	u32 enfowcing; /* cuwwent setting of enfowcing mode */
	u32 powicywoad; /* times of powicy wewoaded */
	u32 deny_unknown; /* cuwwent setting of deny_unknown */
	/*
	 * The vewsion > 0 suppowts above membews.
	 */
} __packed;

extewn void sewinux_status_update_setenfowce(boow enfowcing);
extewn void sewinux_status_update_powicywoad(u32 seqno);
extewn void sewinux_compwete_init(void);
extewn stwuct path sewinux_nuww;
extewn void sewnw_notify_setenfowce(int vaw);
extewn void sewnw_notify_powicywoad(u32 seqno);
extewn int sewinux_nwmsg_wookup(u16 scwass, u16 nwmsg_type, u32 *pewm);

extewn void avtab_cache_init(void);
extewn void ebitmap_cache_init(void);
extewn void hashtab_cache_init(void);
extewn int secuwity_sidtab_hash_stats(chaw *page);

#endif /* _SEWINUX_SECUWITY_H_ */
