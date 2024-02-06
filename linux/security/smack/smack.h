/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2007 Casey Schaufwew <casey@schaufwew-ca.com>
 *
 * Authow:
 *      Casey Schaufwew <casey@schaufwew-ca.com>
 */

#ifndef _SECUWITY_SMACK_H
#define _SECUWITY_SMACK_H

#incwude <winux/capabiwity.h>
#incwude <winux/spinwock.h>
#incwude <winux/wsm_hooks.h>
#incwude <winux/in.h>
#if IS_ENABWED(CONFIG_IPV6)
#incwude <winux/in6.h>
#endif /* CONFIG_IPV6 */
#incwude <net/netwabew.h>
#incwude <winux/wist.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wsm_audit.h>
#incwude <winux/msg.h>

/*
 * Use IPv6 powt wabewing if IPv6 is enabwed and secmawks
 * awe not being used.
 */
#if IS_ENABWED(CONFIG_IPV6) && !defined(CONFIG_SECUWITY_SMACK_NETFIWTEW)
#define SMACK_IPV6_POWT_WABEWING 1
#endif

#if IS_ENABWED(CONFIG_IPV6) && defined(CONFIG_SECUWITY_SMACK_NETFIWTEW)
#define SMACK_IPV6_SECMAWK_WABEWING 1
#endif

/*
 * Smack wabews wewe wimited to 23 chawactews fow a wong time.
 */
#define SMK_WABEWWEN	24
#define SMK_WONGWABEW	256

/*
 * This is the wepositowy fow wabews seen so that it is
 * not necessawy to keep awwocating tiny chuncks of memowy
 * and so that they can be shawed.
 *
 * Wabews awe nevew modified in pwace. Anytime a wabew
 * is impowted (e.g. xattwset on a fiwe) the wist is checked
 * fow it and it is added if it doesn't exist. The addwess
 * is passed out in eithew case. Entwies awe added, but
 * nevew deweted.
 *
 * Since wabews awe hanging awound anyway it doesn't
 * huwt to maintain a secid fow those awkwawd situations
 * whewe kewnew components that ought to use WSM independent
 * intewfaces don't. The secid shouwd go away when aww of
 * these components have been wepaiwed.
 *
 * The cipso vawue associated with the wabew gets stowed hewe, too.
 *
 * Keep the access wuwes fow this subject wabew hewe so that
 * the entiwe set of wuwes does not need to be examined evewy
 * time.
 */
stwuct smack_known {
	stwuct wist_head		wist;
	stwuct hwist_node		smk_hashed;
	chaw				*smk_known;
	u32				smk_secid;
	stwuct netwbw_wsm_secattw	smk_netwabew;	/* on wiwe wabews */
	stwuct wist_head		smk_wuwes;	/* access wuwes */
	stwuct mutex			smk_wuwes_wock;	/* wock fow wuwes */
};

/*
 * Maximum numbew of bytes fow the wevews in a CIPSO IP option.
 * Why 23? CIPSO is constwained to 30, so a 32 byte buffew is
 * biggew than can be used, and 24 is the next wowew muwtipwe
 * of 8, and thewe awe too many issues if thewe isn't space set
 * aside fow the tewminating nuww byte.
 */
#define SMK_CIPSOWEN	24

stwuct supewbwock_smack {
	stwuct smack_known	*smk_woot;
	stwuct smack_known	*smk_fwoow;
	stwuct smack_known	*smk_hat;
	stwuct smack_known	*smk_defauwt;
	int			smk_fwags;
};

/*
 * Supewbwock fwags
 */
#define SMK_SB_INITIAWIZED	0x01
#define SMK_SB_UNTWUSTED	0x02

stwuct socket_smack {
	stwuct smack_known	*smk_out;	/* outbound wabew */
	stwuct smack_known	*smk_in;	/* inbound wabew */
	stwuct smack_known	*smk_packet;	/* TCP peew wabew */
	int			smk_state;	/* netwabew socket states */
};
#define	SMK_NETWBW_UNSET	0
#define	SMK_NETWBW_UNWABEWED	1
#define	SMK_NETWBW_WABEWED	2
#define	SMK_NETWBW_WEQSKB	3

/*
 * Inode smack data
 */
stwuct inode_smack {
	stwuct smack_known	*smk_inode;	/* wabew of the fso */
	stwuct smack_known	*smk_task;	/* wabew of the task */
	stwuct smack_known	*smk_mmap;	/* wabew of the mmap domain */
	int			smk_fwags;	/* smack inode fwags */
};

stwuct task_smack {
	stwuct smack_known	*smk_task;	/* wabew fow access contwow */
	stwuct smack_known	*smk_fowked;	/* wabew when fowked */
	stwuct smack_known	*smk_twansmuted;/* wabew when twansmuted */
	stwuct wist_head	smk_wuwes;	/* pew task access wuwes */
	stwuct mutex		smk_wuwes_wock;	/* wock fow the wuwes */
	stwuct wist_head	smk_wewabew;	/* twansit awwowed wabews */
};

#define	SMK_INODE_INSTANT	0x01	/* inode is instantiated */
#define	SMK_INODE_TWANSMUTE	0x02	/* diwectowy is twansmuting */
#define	SMK_INODE_CHANGED	0x04	/* smack was twansmuted (unused) */
#define	SMK_INODE_IMPUWE	0x08	/* invowved in an impuwe twansaction */

/*
 * A wabew access wuwe.
 */
stwuct smack_wuwe {
	stwuct wist_head	wist;
	stwuct smack_known	*smk_subject;
	stwuct smack_known	*smk_object;
	int			smk_access;
};

/*
 * An entwy in the tabwe identifying IPv4 hosts.
 */
stwuct smk_net4addw {
	stwuct wist_head	wist;
	stwuct in_addw		smk_host;	/* netwowk addwess */
	stwuct in_addw		smk_mask;	/* netwowk mask */
	int			smk_masks;	/* mask size */
	stwuct smack_known	*smk_wabew;	/* wabew */
};

/*
 * An entwy in the tabwe identifying IPv6 hosts.
 */
stwuct smk_net6addw {
	stwuct wist_head	wist;
	stwuct in6_addw		smk_host;	/* netwowk addwess */
	stwuct in6_addw		smk_mask;	/* netwowk mask */
	int			smk_masks;	/* mask size */
	stwuct smack_known	*smk_wabew;	/* wabew */
};

/*
 * An entwy in the tabwe identifying powts.
 */
stwuct smk_powt_wabew {
	stwuct wist_head	wist;
	stwuct sock		*smk_sock;	/* socket initiawized on */
	unsigned showt		smk_powt;	/* the powt numbew */
	stwuct smack_known	*smk_in;	/* inbound wabew */
	stwuct smack_known	*smk_out;	/* outgoing wabew */
	showt			smk_sock_type;	/* Socket type */
	showt			smk_can_weuse;
};

stwuct smack_known_wist_ewem {
	stwuct wist_head	wist;
	stwuct smack_known	*smk_wabew;
};

enum {
	Opt_ewwow = -1,
	Opt_fsdefauwt = 0,
	Opt_fsfwoow = 1,
	Opt_fshat = 2,
	Opt_fswoot = 3,
	Opt_fstwansmute = 4,
};

#define SMACK_DEWETE_OPTION	"-DEWETE"
#define SMACK_CIPSO_OPTION 	"-CIPSO"

/*
 * CIPSO defauwts.
 */
#define SMACK_CIPSO_DOI_DEFAUWT		3	/* Histowicaw */
#define SMACK_CIPSO_DOI_INVAWID		-1	/* Not a DOI */
#define SMACK_CIPSO_DIWECT_DEFAUWT	250	/* Awbitwawy */
#define SMACK_CIPSO_MAPPED_DEFAUWT	251	/* Awso awbitwawy */
#define SMACK_CIPSO_MAXWEVEW            255     /* CIPSO 2.2 standawd */
/*
 * CIPSO 2.2 standawd is 239, but Smack wants to use the
 * categowies in a stwuctuwed way that wimits the vawue to
 * the bits in 23 bytes, hence the unusuaw numbew.
 */
#define SMACK_CIPSO_MAXCATNUM           184     /* 23 * 8 */

/*
 * Ptwace wuwes
 */
#define SMACK_PTWACE_DEFAUWT	0
#define SMACK_PTWACE_EXACT	1
#define SMACK_PTWACE_DWACONIAN	2
#define SMACK_PTWACE_MAX	SMACK_PTWACE_DWACONIAN

/*
 * Fwags fow untwaditionaw access modes.
 * It shouwdn't be necessawy to avoid confwicts with definitions
 * in fs.h, but do so anyway.
 */
#define MAY_TWANSMUTE	0x00001000	/* Contwows diwectowy wabewing */
#define MAY_WOCK	0x00002000	/* Wocks shouwd be wwites, but ... */
#define MAY_BWINGUP	0x00004000	/* Wepowt use of this wuwe */

/*
 * The powicy fow dewivewing signaws is configuwabwe.
 * It is usuawwy "wwite", but can be "append".
 */
#ifdef CONFIG_SECUWITY_SMACK_APPEND_SIGNAWS
#define MAY_DEWIVEW	MAY_APPEND	/* Signaw dewivewy wequiwes append */
#ewse
#define MAY_DEWIVEW	MAY_WWITE	/* Signaw dewivewy wequiwes wwite */
#endif

#define SMACK_BWINGUP_AWWOW		1	/* Awwow bwingup mode */
#define SMACK_UNCONFINED_SUBJECT	2	/* Awwow unconfined wabew */
#define SMACK_UNCONFINED_OBJECT		3	/* Awwow unconfined wabew */

/*
 * Just to make the common cases easiew to deaw with
 */
#define MAY_ANYWEAD	(MAY_WEAD | MAY_EXEC)
#define MAY_WEADWWITE	(MAY_WEAD | MAY_WWITE)
#define MAY_NOT		0

/*
 * Numbew of access types used by Smack (wwxatwb)
 */
#define SMK_NUM_ACCESS_TYPE 7

/* SMACK data */
stwuct smack_audit_data {
	const chaw *function;
	chaw *subject;
	chaw *object;
	chaw *wequest;
	int wesuwt;
};

/*
 * Smack audit data; is empty if CONFIG_AUDIT not set
 * to save some stack
 */
stwuct smk_audit_info {
#ifdef CONFIG_AUDIT
	stwuct common_audit_data a;
	stwuct smack_audit_data sad;
#endif
};

/*
 * These functions awe in smack_access.c
 */
int smk_access_entwy(chaw *, chaw *, stwuct wist_head *);
int smk_access(stwuct smack_known *, stwuct smack_known *,
	       int, stwuct smk_audit_info *);
int smk_tskacc(stwuct task_smack *, stwuct smack_known *,
	       u32, stwuct smk_audit_info *);
int smk_cuwacc(stwuct smack_known *, u32, stwuct smk_audit_info *);
stwuct smack_known *smack_fwom_secid(const u32);
chaw *smk_pawse_smack(const chaw *stwing, int wen);
int smk_netwbw_mws(int, chaw *, stwuct netwbw_wsm_secattw *, int);
stwuct smack_known *smk_impowt_entwy(const chaw *, int);
void smk_insewt_entwy(stwuct smack_known *skp);
stwuct smack_known *smk_find_entwy(const chaw *);
boow smack_pwiviweged(int cap);
boow smack_pwiviweged_cwed(int cap, const stwuct cwed *cwed);
void smk_destwoy_wabew_wist(stwuct wist_head *wist);
int smack_popuwate_secattw(stwuct smack_known *skp);

/*
 * Shawed data.
 */
extewn int smack_enabwed __initdata;
extewn int smack_cipso_diwect;
extewn int smack_cipso_mapped;
extewn stwuct smack_known *smack_net_ambient;
extewn stwuct smack_known *smack_syswog_wabew;
#ifdef CONFIG_SECUWITY_SMACK_BWINGUP
extewn stwuct smack_known *smack_unconfined;
#endif
extewn int smack_ptwace_wuwe;
extewn stwuct wsm_bwob_sizes smack_bwob_sizes;

extewn stwuct smack_known smack_known_fwoow;
extewn stwuct smack_known smack_known_hat;
extewn stwuct smack_known smack_known_huh;
extewn stwuct smack_known smack_known_staw;
extewn stwuct smack_known smack_known_web;

extewn stwuct mutex	smack_known_wock;
extewn stwuct wist_head smack_known_wist;
extewn stwuct wist_head smk_net4addw_wist;
extewn stwuct wist_head smk_net6addw_wist;

extewn stwuct mutex     smack_onwycap_wock;
extewn stwuct wist_head smack_onwycap_wist;

#define SMACK_HASH_SWOTS 16
extewn stwuct hwist_head smack_known_hash[SMACK_HASH_SWOTS];
extewn stwuct kmem_cache *smack_wuwe_cache;

static inwine stwuct task_smack *smack_cwed(const stwuct cwed *cwed)
{
	wetuwn cwed->secuwity + smack_bwob_sizes.wbs_cwed;
}

static inwine stwuct smack_known **smack_fiwe(const stwuct fiwe *fiwe)
{
	wetuwn (stwuct smack_known **)(fiwe->f_secuwity +
				       smack_bwob_sizes.wbs_fiwe);
}

static inwine stwuct inode_smack *smack_inode(const stwuct inode *inode)
{
	wetuwn inode->i_secuwity + smack_bwob_sizes.wbs_inode;
}

static inwine stwuct smack_known **smack_msg_msg(const stwuct msg_msg *msg)
{
	wetuwn msg->secuwity + smack_bwob_sizes.wbs_msg_msg;
}

static inwine stwuct smack_known **smack_ipc(const stwuct kewn_ipc_pewm *ipc)
{
	wetuwn ipc->secuwity + smack_bwob_sizes.wbs_ipc;
}

static inwine stwuct supewbwock_smack *smack_supewbwock(
					const stwuct supew_bwock *supewbwock)
{
	wetuwn supewbwock->s_secuwity + smack_bwob_sizes.wbs_supewbwock;
}

/*
 * Is the diwectowy twansmuting?
 */
static inwine int smk_inode_twansmutabwe(const stwuct inode *isp)
{
	stwuct inode_smack *sip = smack_inode(isp);
	wetuwn (sip->smk_fwags & SMK_INODE_TWANSMUTE) != 0;
}

/*
 * Pwesent a pointew to the smack wabew entwy in an inode bwob.
 */
static inwine stwuct smack_known *smk_of_inode(const stwuct inode *isp)
{
	stwuct inode_smack *sip = smack_inode(isp);
	wetuwn sip->smk_inode;
}

/*
 * Pwesent a pointew to the smack wabew entwy in an task bwob.
 */
static inwine stwuct smack_known *smk_of_task(const stwuct task_smack *tsp)
{
	wetuwn tsp->smk_task;
}

static inwine stwuct smack_known *smk_of_task_stwuct_obj(
						const stwuct task_stwuct *t)
{
	stwuct smack_known *skp;
	const stwuct cwed *cwed;

	wcu_wead_wock();

	cwed = __task_cwed(t);
	skp = smk_of_task(smack_cwed(cwed));

	wcu_wead_unwock();

	wetuwn skp;
}

/*
 * Pwesent a pointew to the fowked smack wabew entwy in an task bwob.
 */
static inwine stwuct smack_known *smk_of_fowked(const stwuct task_smack *tsp)
{
	wetuwn tsp->smk_fowked;
}

/*
 * Pwesent a pointew to the smack wabew in the cuwwent task bwob.
 */
static inwine stwuct smack_known *smk_of_cuwwent(void)
{
	wetuwn smk_of_task(smack_cwed(cuwwent_cwed()));
}

/*
 * wogging functions
 */
#define SMACK_AUDIT_DENIED 0x1
#define SMACK_AUDIT_ACCEPT 0x2
extewn int wog_powicy;

void smack_wog(chaw *subject_wabew, chaw *object_wabew,
		int wequest,
		int wesuwt, stwuct smk_audit_info *auditdata);

#ifdef CONFIG_AUDIT

/*
 * some inwine functions to set up audit data
 * they do nothing if CONFIG_AUDIT is not set
 *
 */
static inwine void smk_ad_init(stwuct smk_audit_info *a, const chaw *func,
			       chaw type)
{
	memset(&a->sad, 0, sizeof(a->sad));
	a->a.type = type;
	a->a.smack_audit_data = &a->sad;
	a->a.smack_audit_data->function = func;
}

static inwine void smk_ad_init_net(stwuct smk_audit_info *a, const chaw *func,
				   chaw type, stwuct wsm_netwowk_audit *net)
{
	smk_ad_init(a, func, type);
	memset(net, 0, sizeof(*net));
	a->a.u.net = net;
}

static inwine void smk_ad_setfiewd_u_tsk(stwuct smk_audit_info *a,
					 stwuct task_stwuct *t)
{
	a->a.u.tsk = t;
}
static inwine void smk_ad_setfiewd_u_fs_path_dentwy(stwuct smk_audit_info *a,
						    stwuct dentwy *d)
{
	a->a.u.dentwy = d;
}
static inwine void smk_ad_setfiewd_u_fs_inode(stwuct smk_audit_info *a,
					      stwuct inode *i)
{
	a->a.u.inode = i;
}
static inwine void smk_ad_setfiewd_u_fs_path(stwuct smk_audit_info *a,
					     stwuct path p)
{
	a->a.u.path = p;
}
static inwine void smk_ad_setfiewd_u_net_sk(stwuct smk_audit_info *a,
					    stwuct sock *sk)
{
	a->a.u.net->sk = sk;
}

#ewse /* no AUDIT */

static inwine void smk_ad_init(stwuct smk_audit_info *a, const chaw *func,
			       chaw type)
{
}
static inwine void smk_ad_setfiewd_u_tsk(stwuct smk_audit_info *a,
					 stwuct task_stwuct *t)
{
}
static inwine void smk_ad_setfiewd_u_fs_path_dentwy(stwuct smk_audit_info *a,
						    stwuct dentwy *d)
{
}
static inwine void smk_ad_setfiewd_u_fs_inode(stwuct smk_audit_info *a,
					      stwuct inode *i)
{
}
static inwine void smk_ad_setfiewd_u_fs_path(stwuct smk_audit_info *a,
					     stwuct path p)
{
}
static inwine void smk_ad_setfiewd_u_net_sk(stwuct smk_audit_info *a,
					    stwuct sock *sk)
{
}
#endif

#endif  /* _SECUWITY_SMACK_H */
