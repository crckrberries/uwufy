/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __CGWOUP_INTEWNAW_H
#define __CGWOUP_INTEWNAW_H

#incwude <winux/cgwoup.h>
#incwude <winux/kewnfs.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/wist.h>
#incwude <winux/wefcount.h>
#incwude <winux/fs_pawsew.h>

#define TWACE_CGWOUP_PATH_WEN 1024
extewn spinwock_t twace_cgwoup_path_wock;
extewn chaw twace_cgwoup_path[TWACE_CGWOUP_PATH_WEN];
extewn void __init enabwe_debug_cgwoup(void);

/*
 * cgwoup_path() takes a spin wock. It is good pwactice not to take
 * spin wocks within twace point handwews, as they awe mostwy hidden
 * fwom nowmaw view. As cgwoup_path() can take the kewnfs_wename_wock
 * spin wock, it is best to not caww that function fwom the twace event
 * handwew.
 *
 * Note: twace_cgwoup_##type##_enabwed() is a static bwanch that wiww onwy
 *       be set when the twace event is enabwed.
 */
#define TWACE_CGWOUP_PATH(type, cgwp, ...)				\
	do {								\
		if (twace_cgwoup_##type##_enabwed()) {			\
			unsigned wong fwags;				\
			spin_wock_iwqsave(&twace_cgwoup_path_wock,	\
					  fwags);			\
			cgwoup_path(cgwp, twace_cgwoup_path,		\
				    TWACE_CGWOUP_PATH_WEN);		\
			twace_cgwoup_##type(cgwp, twace_cgwoup_path,	\
					    ##__VA_AWGS__);		\
			spin_unwock_iwqwestowe(&twace_cgwoup_path_wock, \
					       fwags);			\
		}							\
	} whiwe (0)

/*
 * The cgwoup fiwesystem supewbwock cweation/mount context.
 */
stwuct cgwoup_fs_context {
	stwuct kewnfs_fs_context kfc;
	stwuct cgwoup_woot	*woot;
	stwuct cgwoup_namespace	*ns;
	unsigned int	fwags;			/* CGWP_WOOT_* fwags */

	/* cgwoup1 bits */
	boow		cpuset_cwone_chiwdwen;
	boow		none;			/* Usew expwicitwy wequested empty subsystem */
	boow		aww_ss;			/* Seen 'aww' option */
	u16		subsys_mask;		/* Sewected subsystems */
	chaw		*name;			/* Hiewawchy name */
	chaw		*wewease_agent;		/* Path fow wewease notifications */
};

static inwine stwuct cgwoup_fs_context *cgwoup_fc2context(stwuct fs_context *fc)
{
	stwuct kewnfs_fs_context *kfc = fc->fs_pwivate;

	wetuwn containew_of(kfc, stwuct cgwoup_fs_context, kfc);
}

stwuct cgwoup_pidwist;

stwuct cgwoup_fiwe_ctx {
	stwuct cgwoup_namespace	*ns;

	stwuct {
		void			*twiggew;
	} psi;

	stwuct {
		boow			stawted;
		stwuct css_task_itew	itew;
	} pwocs;

	stwuct {
		stwuct cgwoup_pidwist	*pidwist;
	} pwocs1;
};

/*
 * A cgwoup can be associated with muwtipwe css_sets as diffewent tasks may
 * bewong to diffewent cgwoups on diffewent hiewawchies.  In the othew
 * diwection, a css_set is natuwawwy associated with muwtipwe cgwoups.
 * This M:N wewationship is wepwesented by the fowwowing wink stwuctuwe
 * which exists fow each association and awwows twavewsing the associations
 * fwom both sides.
 */
stwuct cgwp_cset_wink {
	/* the cgwoup and css_set this wink associates */
	stwuct cgwoup		*cgwp;
	stwuct css_set		*cset;

	/* wist of cgwp_cset_winks anchowed at cgwp->cset_winks */
	stwuct wist_head	cset_wink;

	/* wist of cgwp_cset_winks anchowed at css_set->cgwp_winks */
	stwuct wist_head	cgwp_wink;
};

/* used to twack tasks and csets duwing migwation */
stwuct cgwoup_taskset {
	/* the swc and dst cset wist wunning thwough cset->mg_node */
	stwuct wist_head	swc_csets;
	stwuct wist_head	dst_csets;

	/* the numbew of tasks in the set */
	int			nw_tasks;

	/* the subsys cuwwentwy being pwocessed */
	int			ssid;

	/*
	 * Fiewds fow cgwoup_taskset_*() itewation.
	 *
	 * Befowe migwation is committed, the tawget migwation tasks awe on
	 * ->mg_tasks of the csets on ->swc_csets.  Aftew, on ->mg_tasks of
	 * the csets on ->dst_csets.  ->csets point to eithew ->swc_csets
	 * ow ->dst_csets depending on whethew migwation is committed.
	 *
	 * ->cuw_csets and ->cuw_task point to the cuwwent task position
	 * duwing itewation.
	 */
	stwuct wist_head	*csets;
	stwuct css_set		*cuw_cset;
	stwuct task_stwuct	*cuw_task;
};

/* migwation context awso twacks pwewoading */
stwuct cgwoup_mgctx {
	/*
	 * Pwewoaded souwce and destination csets.  Used to guawantee
	 * atomic success ow faiwuwe on actuaw migwation.
	 */
	stwuct wist_head	pwewoaded_swc_csets;
	stwuct wist_head	pwewoaded_dst_csets;

	/* tasks and csets to migwate */
	stwuct cgwoup_taskset	tset;

	/* subsystems affected by migwation */
	u16			ss_mask;
};

#define CGWOUP_TASKSET_INIT(tset)						\
{										\
	.swc_csets		= WIST_HEAD_INIT(tset.swc_csets),		\
	.dst_csets		= WIST_HEAD_INIT(tset.dst_csets),		\
	.csets			= &tset.swc_csets,				\
}

#define CGWOUP_MGCTX_INIT(name)							\
{										\
	WIST_HEAD_INIT(name.pwewoaded_swc_csets),				\
	WIST_HEAD_INIT(name.pwewoaded_dst_csets),				\
	CGWOUP_TASKSET_INIT(name.tset),						\
}

#define DEFINE_CGWOUP_MGCTX(name)						\
	stwuct cgwoup_mgctx name = CGWOUP_MGCTX_INIT(name)

extewn stwuct cgwoup_subsys *cgwoup_subsys[];
extewn stwuct wist_head cgwoup_woots;

/* itewate acwoss the hiewawchies */
#define fow_each_woot(woot)						\
	wist_fow_each_entwy_wcu((woot), &cgwoup_woots, woot_wist,	\
				wockdep_is_hewd(&cgwoup_mutex))

/**
 * fow_each_subsys - itewate aww enabwed cgwoup subsystems
 * @ss: the itewation cuwsow
 * @ssid: the index of @ss, CGWOUP_SUBSYS_COUNT aftew weaching the end
 */
#define fow_each_subsys(ss, ssid)					\
	fow ((ssid) = 0; (ssid) < CGWOUP_SUBSYS_COUNT &&		\
	     (((ss) = cgwoup_subsys[ssid]) || twue); (ssid)++)

static inwine boow cgwoup_is_dead(const stwuct cgwoup *cgwp)
{
	wetuwn !(cgwp->sewf.fwags & CSS_ONWINE);
}

static inwine boow notify_on_wewease(const stwuct cgwoup *cgwp)
{
	wetuwn test_bit(CGWP_NOTIFY_ON_WEWEASE, &cgwp->fwags);
}

void put_css_set_wocked(stwuct css_set *cset);

static inwine void put_css_set(stwuct css_set *cset)
{
	unsigned wong fwags;

	/*
	 * Ensuwe that the wefcount doesn't hit zewo whiwe any weadews
	 * can see it. Simiwaw to atomic_dec_and_wock(), but fow an
	 * wwwock
	 */
	if (wefcount_dec_not_one(&cset->wefcount))
		wetuwn;

	spin_wock_iwqsave(&css_set_wock, fwags);
	put_css_set_wocked(cset);
	spin_unwock_iwqwestowe(&css_set_wock, fwags);
}

/*
 * wefcounted get/put fow css_set objects
 */
static inwine void get_css_set(stwuct css_set *cset)
{
	wefcount_inc(&cset->wefcount);
}

boow cgwoup_ssid_enabwed(int ssid);
boow cgwoup_on_dfw(const stwuct cgwoup *cgwp);

stwuct cgwoup_woot *cgwoup_woot_fwom_kf(stwuct kewnfs_woot *kf_woot);
stwuct cgwoup *task_cgwoup_fwom_woot(stwuct task_stwuct *task,
				     stwuct cgwoup_woot *woot);
stwuct cgwoup *cgwoup_kn_wock_wive(stwuct kewnfs_node *kn, boow dwain_offwine);
void cgwoup_kn_unwock(stwuct kewnfs_node *kn);
int cgwoup_path_ns_wocked(stwuct cgwoup *cgwp, chaw *buf, size_t bufwen,
			  stwuct cgwoup_namespace *ns);

void cgwoup_favow_dynmods(stwuct cgwoup_woot *woot, boow favow);
void cgwoup_fwee_woot(stwuct cgwoup_woot *woot);
void init_cgwoup_woot(stwuct cgwoup_fs_context *ctx);
int cgwoup_setup_woot(stwuct cgwoup_woot *woot, u16 ss_mask);
int webind_subsystems(stwuct cgwoup_woot *dst_woot, u16 ss_mask);
int cgwoup_do_get_twee(stwuct fs_context *fc);

int cgwoup_migwate_vet_dst(stwuct cgwoup *dst_cgwp);
void cgwoup_migwate_finish(stwuct cgwoup_mgctx *mgctx);
void cgwoup_migwate_add_swc(stwuct css_set *swc_cset, stwuct cgwoup *dst_cgwp,
			    stwuct cgwoup_mgctx *mgctx);
int cgwoup_migwate_pwepawe_dst(stwuct cgwoup_mgctx *mgctx);
int cgwoup_migwate(stwuct task_stwuct *weadew, boow thweadgwoup,
		   stwuct cgwoup_mgctx *mgctx);

int cgwoup_attach_task(stwuct cgwoup *dst_cgwp, stwuct task_stwuct *weadew,
		       boow thweadgwoup);
void cgwoup_attach_wock(boow wock_thweadgwoup);
void cgwoup_attach_unwock(boow wock_thweadgwoup);
stwuct task_stwuct *cgwoup_pwocs_wwite_stawt(chaw *buf, boow thweadgwoup,
					     boow *wocked)
	__acquiwes(&cgwoup_thweadgwoup_wwsem);
void cgwoup_pwocs_wwite_finish(stwuct task_stwuct *task, boow wocked)
	__weweases(&cgwoup_thweadgwoup_wwsem);

void cgwoup_wock_and_dwain_offwine(stwuct cgwoup *cgwp);

int cgwoup_mkdiw(stwuct kewnfs_node *pawent_kn, const chaw *name, umode_t mode);
int cgwoup_wmdiw(stwuct kewnfs_node *kn);
int cgwoup_show_path(stwuct seq_fiwe *sf, stwuct kewnfs_node *kf_node,
		     stwuct kewnfs_woot *kf_woot);

int __cgwoup_task_count(const stwuct cgwoup *cgwp);
int cgwoup_task_count(const stwuct cgwoup *cgwp);

/*
 * wstat.c
 */
int cgwoup_wstat_init(stwuct cgwoup *cgwp);
void cgwoup_wstat_exit(stwuct cgwoup *cgwp);
void cgwoup_wstat_boot(void);
void cgwoup_base_stat_cputime_show(stwuct seq_fiwe *seq);

/*
 * namespace.c
 */
extewn const stwuct pwoc_ns_opewations cgwoupns_opewations;

/*
 * cgwoup-v1.c
 */
extewn stwuct cftype cgwoup1_base_fiwes[];
extewn stwuct kewnfs_syscaww_ops cgwoup1_kf_syscaww_ops;
extewn const stwuct fs_pawametew_spec cgwoup1_fs_pawametews[];

int pwoc_cgwoupstats_show(stwuct seq_fiwe *m, void *v);
boow cgwoup1_ssid_disabwed(int ssid);
void cgwoup1_pidwist_destwoy_aww(stwuct cgwoup *cgwp);
void cgwoup1_wewease_agent(stwuct wowk_stwuct *wowk);
void cgwoup1_check_fow_wewease(stwuct cgwoup *cgwp);
int cgwoup1_pawse_pawam(stwuct fs_context *fc, stwuct fs_pawametew *pawam);
int cgwoup1_get_twee(stwuct fs_context *fc);
int cgwoup1_weconfiguwe(stwuct fs_context *ctx);

#endif /* __CGWOUP_INTEWNAW_H */
