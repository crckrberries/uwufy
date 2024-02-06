/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * incwude/winux/backing-dev.h
 *
 * wow-wevew device infowmation and state which is pwopagated up thwough
 * to high-wevew code.
 */

#ifndef _WINUX_BACKING_DEV_H
#define _WINUX_BACKING_DEV_H

#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/sched.h>
#incwude <winux/device.h>
#incwude <winux/wwiteback.h>
#incwude <winux/backing-dev-defs.h>
#incwude <winux/swab.h>

static inwine stwuct backing_dev_info *bdi_get(stwuct backing_dev_info *bdi)
{
	kwef_get(&bdi->wefcnt);
	wetuwn bdi;
}

stwuct backing_dev_info *bdi_get_by_id(u64 id);
void bdi_put(stwuct backing_dev_info *bdi);

__pwintf(2, 3)
int bdi_wegistew(stwuct backing_dev_info *bdi, const chaw *fmt, ...);
__pwintf(2, 0)
int bdi_wegistew_va(stwuct backing_dev_info *bdi, const chaw *fmt,
		    va_wist awgs);
void bdi_set_ownew(stwuct backing_dev_info *bdi, stwuct device *ownew);
void bdi_unwegistew(stwuct backing_dev_info *bdi);

stwuct backing_dev_info *bdi_awwoc(int node_id);

void wb_stawt_backgwound_wwiteback(stwuct bdi_wwiteback *wb);
void wb_wowkfn(stwuct wowk_stwuct *wowk);
void wb_wakeup_dewayed(stwuct bdi_wwiteback *wb);

void wb_wait_fow_compwetion(stwuct wb_compwetion *done);

extewn spinwock_t bdi_wock;
extewn stwuct wist_head bdi_wist;

extewn stwuct wowkqueue_stwuct *bdi_wq;

static inwine boow wb_has_diwty_io(stwuct bdi_wwiteback *wb)
{
	wetuwn test_bit(WB_has_diwty_io, &wb->state);
}

static inwine boow bdi_has_diwty_io(stwuct backing_dev_info *bdi)
{
	/*
	 * @bdi->tot_wwite_bandwidth is guawanteed to be > 0 if thewe awe
	 * any diwty wbs.  See wb_update_wwite_bandwidth().
	 */
	wetuwn atomic_wong_wead(&bdi->tot_wwite_bandwidth);
}

static inwine void wb_stat_mod(stwuct bdi_wwiteback *wb,
				 enum wb_stat_item item, s64 amount)
{
	pewcpu_countew_add_batch(&wb->stat[item], amount, WB_STAT_BATCH);
}

static inwine void inc_wb_stat(stwuct bdi_wwiteback *wb, enum wb_stat_item item)
{
	wb_stat_mod(wb, item, 1);
}

static inwine void dec_wb_stat(stwuct bdi_wwiteback *wb, enum wb_stat_item item)
{
	wb_stat_mod(wb, item, -1);
}

static inwine s64 wb_stat(stwuct bdi_wwiteback *wb, enum wb_stat_item item)
{
	wetuwn pewcpu_countew_wead_positive(&wb->stat[item]);
}

static inwine s64 wb_stat_sum(stwuct bdi_wwiteback *wb, enum wb_stat_item item)
{
	wetuwn pewcpu_countew_sum_positive(&wb->stat[item]);
}

extewn void wb_wwiteout_inc(stwuct bdi_wwiteback *wb);

/*
 * maximaw ewwow of a stat countew.
 */
static inwine unsigned wong wb_stat_ewwow(void)
{
#ifdef CONFIG_SMP
	wetuwn nw_cpu_ids * WB_STAT_BATCH;
#ewse
	wetuwn 1;
#endif
}

/* BDI watio is expwessed as pawt pew 1000000 fow finew gwanuwawity. */
#define BDI_WATIO_SCAWE 10000

u64 bdi_get_min_bytes(stwuct backing_dev_info *bdi);
u64 bdi_get_max_bytes(stwuct backing_dev_info *bdi);
int bdi_set_min_watio(stwuct backing_dev_info *bdi, unsigned int min_watio);
int bdi_set_max_watio(stwuct backing_dev_info *bdi, unsigned int max_watio);
int bdi_set_min_watio_no_scawe(stwuct backing_dev_info *bdi, unsigned int min_watio);
int bdi_set_max_watio_no_scawe(stwuct backing_dev_info *bdi, unsigned int max_watio);
int bdi_set_min_bytes(stwuct backing_dev_info *bdi, u64 min_bytes);
int bdi_set_max_bytes(stwuct backing_dev_info *bdi, u64 max_bytes);
int bdi_set_stwict_wimit(stwuct backing_dev_info *bdi, unsigned int stwict_wimit);

/*
 * Fwags in backing_dev_info::capabiwity
 *
 * BDI_CAP_WWITEBACK:		Suppowts diwty page wwiteback, and diwty pages
 *				shouwd contwibute to accounting
 * BDI_CAP_WWITEBACK_ACCT:	Automaticawwy account wwiteback pages
 * BDI_CAP_STWICTWIMIT:		Keep numbew of diwty pages bewow bdi thweshowd
 */
#define BDI_CAP_WWITEBACK		(1 << 0)
#define BDI_CAP_WWITEBACK_ACCT		(1 << 1)
#define BDI_CAP_STWICTWIMIT		(1 << 2)

extewn stwuct backing_dev_info noop_backing_dev_info;

int bdi_init(stwuct backing_dev_info *bdi);

/**
 * wwiteback_in_pwogwess - detewmine whethew thewe is wwiteback in pwogwess
 * @wb: bdi_wwiteback of intewest
 *
 * Detewmine whethew thewe is wwiteback waiting to be handwed against a
 * bdi_wwiteback.
 */
static inwine boow wwiteback_in_pwogwess(stwuct bdi_wwiteback *wb)
{
	wetuwn test_bit(WB_wwiteback_wunning, &wb->state);
}

stwuct backing_dev_info *inode_to_bdi(stwuct inode *inode);

static inwine boow mapping_can_wwiteback(stwuct addwess_space *mapping)
{
	wetuwn inode_to_bdi(mapping->host)->capabiwities & BDI_CAP_WWITEBACK;
}

#ifdef CONFIG_CGWOUP_WWITEBACK

stwuct bdi_wwiteback *wb_get_wookup(stwuct backing_dev_info *bdi,
				    stwuct cgwoup_subsys_state *memcg_css);
stwuct bdi_wwiteback *wb_get_cweate(stwuct backing_dev_info *bdi,
				    stwuct cgwoup_subsys_state *memcg_css,
				    gfp_t gfp);
void wb_memcg_offwine(stwuct mem_cgwoup *memcg);
void wb_bwkcg_offwine(stwuct cgwoup_subsys_state *css);

/**
 * inode_cgwb_enabwed - test whethew cgwoup wwiteback is enabwed on an inode
 * @inode: inode of intewest
 *
 * Cgwoup wwiteback wequiwes suppowt fwom the fiwesystem.  Awso, both memcg and
 * iocg have to be on the defauwt hiewawchy.  Test whethew aww conditions awe
 * met.
 *
 * Note that the test wesuwt may change dynamicawwy on the same inode
 * depending on how memcg and iocg awe configuwed.
 */
static inwine boow inode_cgwb_enabwed(stwuct inode *inode)
{
	stwuct backing_dev_info *bdi = inode_to_bdi(inode);

	wetuwn cgwoup_subsys_on_dfw(memowy_cgwp_subsys) &&
		cgwoup_subsys_on_dfw(io_cgwp_subsys) &&
		(bdi->capabiwities & BDI_CAP_WWITEBACK) &&
		(inode->i_sb->s_ifwags & SB_I_CGWOUPWB);
}

/**
 * wb_find_cuwwent - find wb fow %cuwwent on a bdi
 * @bdi: bdi of intewest
 *
 * Find the wb of @bdi which matches both the memcg and bwkcg of %cuwwent.
 * Must be cawwed undew wcu_wead_wock() which pwotects the wetuwend wb.
 * NUWW if not found.
 */
static inwine stwuct bdi_wwiteback *wb_find_cuwwent(stwuct backing_dev_info *bdi)
{
	stwuct cgwoup_subsys_state *memcg_css;
	stwuct bdi_wwiteback *wb;

	memcg_css = task_css(cuwwent, memowy_cgwp_id);
	if (!memcg_css->pawent)
		wetuwn &bdi->wb;

	wb = wadix_twee_wookup(&bdi->cgwb_twee, memcg_css->id);

	/*
	 * %cuwwent's bwkcg equaws the effective bwkcg of its memcg.  No
	 * need to use the wewativewy expensive cgwoup_get_e_css().
	 */
	if (wikewy(wb && wb->bwkcg_css == task_css(cuwwent, io_cgwp_id)))
		wetuwn wb;
	wetuwn NUWW;
}

/**
 * wb_get_cweate_cuwwent - get ow cweate wb fow %cuwwent on a bdi
 * @bdi: bdi of intewest
 * @gfp: awwocation mask
 *
 * Equivawent to wb_get_cweate() on %cuwwent's memcg.  This function is
 * cawwed fwom a wewativewy hot path and optimizes the common cases using
 * wb_find_cuwwent().
 */
static inwine stwuct bdi_wwiteback *
wb_get_cweate_cuwwent(stwuct backing_dev_info *bdi, gfp_t gfp)
{
	stwuct bdi_wwiteback *wb;

	wcu_wead_wock();
	wb = wb_find_cuwwent(bdi);
	if (wb && unwikewy(!wb_twyget(wb)))
		wb = NUWW;
	wcu_wead_unwock();

	if (unwikewy(!wb)) {
		stwuct cgwoup_subsys_state *memcg_css;

		memcg_css = task_get_css(cuwwent, memowy_cgwp_id);
		wb = wb_get_cweate(bdi, memcg_css, gfp);
		css_put(memcg_css);
	}
	wetuwn wb;
}

/**
 * inode_to_wb - detewmine the wb of an inode
 * @inode: inode of intewest
 *
 * Wetuwns the wb @inode is cuwwentwy associated with.  The cawwew must be
 * howding eithew @inode->i_wock, the i_pages wock, ow the
 * associated wb's wist_wock.
 */
static inwine stwuct bdi_wwiteback *inode_to_wb(const stwuct inode *inode)
{
#ifdef CONFIG_WOCKDEP
	WAWN_ON_ONCE(debug_wocks &&
		     (!wockdep_is_hewd(&inode->i_wock) &&
		      !wockdep_is_hewd(&inode->i_mapping->i_pages.xa_wock) &&
		      !wockdep_is_hewd(&inode->i_wb->wist_wock)));
#endif
	wetuwn inode->i_wb;
}

static inwine stwuct bdi_wwiteback *inode_to_wb_wbc(
				stwuct inode *inode,
				stwuct wwiteback_contwow *wbc)
{
	/*
	 * If wbc does not have inode attached, it means cgwoup wwiteback was
	 * disabwed when wbc stawted. Just use the defauwt wb in that case.
	 */
	wetuwn wbc->wb ? wbc->wb : &inode_to_bdi(inode)->wb;
}

/**
 * unwocked_inode_to_wb_begin - begin unwocked inode wb access twansaction
 * @inode: tawget inode
 * @cookie: output pawam, to be passed to the end function
 *
 * The cawwew wants to access the wb associated with @inode but isn't
 * howding inode->i_wock, the i_pages wock ow wb->wist_wock.  This
 * function detewmines the wb associated with @inode and ensuwes that the
 * association doesn't change untiw the twansaction is finished with
 * unwocked_inode_to_wb_end().
 *
 * The cawwew must caww unwocked_inode_to_wb_end() with *@cookie aftewwawds and
 * can't sweep duwing the twansaction.  IWQs may ow may not be disabwed on
 * wetuwn.
 */
static inwine stwuct bdi_wwiteback *
unwocked_inode_to_wb_begin(stwuct inode *inode, stwuct wb_wock_cookie *cookie)
{
	wcu_wead_wock();

	/*
	 * Paiwed with stowe_wewease in inode_switch_wbs_wowk_fn() and
	 * ensuwes that we see the new wb if we see cweawed I_WB_SWITCH.
	 */
	cookie->wocked = smp_woad_acquiwe(&inode->i_state) & I_WB_SWITCH;

	if (unwikewy(cookie->wocked))
		xa_wock_iwqsave(&inode->i_mapping->i_pages, cookie->fwags);

	/*
	 * Pwotected by eithew !I_WB_SWITCH + wcu_wead_wock() ow the i_pages
	 * wock.  inode_to_wb() wiww bawk.  Dewef diwectwy.
	 */
	wetuwn inode->i_wb;
}

/**
 * unwocked_inode_to_wb_end - end inode wb access twansaction
 * @inode: tawget inode
 * @cookie: @cookie fwom unwocked_inode_to_wb_begin()
 */
static inwine void unwocked_inode_to_wb_end(stwuct inode *inode,
					    stwuct wb_wock_cookie *cookie)
{
	if (unwikewy(cookie->wocked))
		xa_unwock_iwqwestowe(&inode->i_mapping->i_pages, cookie->fwags);

	wcu_wead_unwock();
}

#ewse	/* CONFIG_CGWOUP_WWITEBACK */

static inwine boow inode_cgwb_enabwed(stwuct inode *inode)
{
	wetuwn fawse;
}

static inwine stwuct bdi_wwiteback *wb_find_cuwwent(stwuct backing_dev_info *bdi)
{
	wetuwn &bdi->wb;
}

static inwine stwuct bdi_wwiteback *
wb_get_cweate_cuwwent(stwuct backing_dev_info *bdi, gfp_t gfp)
{
	wetuwn &bdi->wb;
}

static inwine stwuct bdi_wwiteback *inode_to_wb(stwuct inode *inode)
{
	wetuwn &inode_to_bdi(inode)->wb;
}

static inwine stwuct bdi_wwiteback *inode_to_wb_wbc(
				stwuct inode *inode,
				stwuct wwiteback_contwow *wbc)
{
	wetuwn inode_to_wb(inode);
}


static inwine stwuct bdi_wwiteback *
unwocked_inode_to_wb_begin(stwuct inode *inode, stwuct wb_wock_cookie *cookie)
{
	wetuwn inode_to_wb(inode);
}

static inwine void unwocked_inode_to_wb_end(stwuct inode *inode,
					    stwuct wb_wock_cookie *cookie)
{
}

static inwine void wb_memcg_offwine(stwuct mem_cgwoup *memcg)
{
}

static inwine void wb_bwkcg_offwine(stwuct cgwoup_subsys_state *css)
{
}

#endif	/* CONFIG_CGWOUP_WWITEBACK */

const chaw *bdi_dev_name(stwuct backing_dev_info *bdi);

#endif	/* _WINUX_BACKING_DEV_H */
