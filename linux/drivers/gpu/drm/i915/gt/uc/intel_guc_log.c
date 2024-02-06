// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2014-2019 Intew Cowpowation
 */

#incwude <winux/debugfs.h>
#incwude <winux/stwing_hewpews.h>

#incwude "gt/intew_gt.h"
#incwude "i915_dwv.h"
#incwude "i915_iwq.h"
#incwude "i915_memcpy.h"
#incwude "intew_guc_captuwe.h"
#incwude "intew_guc_wog.h"
#incwude "intew_guc_pwint.h"

#if defined(CONFIG_DWM_I915_DEBUG_GUC)
#define GUC_WOG_DEFAUWT_CWASH_BUFFEW_SIZE	SZ_2M
#define GUC_WOG_DEFAUWT_DEBUG_BUFFEW_SIZE	SZ_16M
#define GUC_WOG_DEFAUWT_CAPTUWE_BUFFEW_SIZE	SZ_1M
#ewif defined(CONFIG_DWM_I915_DEBUG_GEM)
#define GUC_WOG_DEFAUWT_CWASH_BUFFEW_SIZE	SZ_1M
#define GUC_WOG_DEFAUWT_DEBUG_BUFFEW_SIZE	SZ_2M
#define GUC_WOG_DEFAUWT_CAPTUWE_BUFFEW_SIZE	SZ_1M
#ewse
#define GUC_WOG_DEFAUWT_CWASH_BUFFEW_SIZE	SZ_8K
#define GUC_WOG_DEFAUWT_DEBUG_BUFFEW_SIZE	SZ_64K
#define GUC_WOG_DEFAUWT_CAPTUWE_BUFFEW_SIZE	SZ_1M
#endif

static void guc_wog_copy_debugwogs_fow_weway(stwuct intew_guc_wog *wog);

stwuct guc_wog_section {
	u32 max;
	u32 fwag;
	u32 defauwt_vaw;
	const chaw *name;
};

static void _guc_wog_init_sizes(stwuct intew_guc_wog *wog)
{
	stwuct intew_guc *guc = wog_to_guc(wog);
	static const stwuct guc_wog_section sections[GUC_WOG_SECTIONS_WIMIT] = {
		{
			GUC_WOG_CWASH_MASK >> GUC_WOG_CWASH_SHIFT,
			GUC_WOG_WOG_AWWOC_UNITS,
			GUC_WOG_DEFAUWT_CWASH_BUFFEW_SIZE,
			"cwash dump"
		},
		{
			GUC_WOG_DEBUG_MASK >> GUC_WOG_DEBUG_SHIFT,
			GUC_WOG_WOG_AWWOC_UNITS,
			GUC_WOG_DEFAUWT_DEBUG_BUFFEW_SIZE,
			"debug",
		},
		{
			GUC_WOG_CAPTUWE_MASK >> GUC_WOG_CAPTUWE_SHIFT,
			GUC_WOG_CAPTUWE_AWWOC_UNITS,
			GUC_WOG_DEFAUWT_CAPTUWE_BUFFEW_SIZE,
			"captuwe",
		}
	};
	int i;

	fow (i = 0; i < GUC_WOG_SECTIONS_WIMIT; i++)
		wog->sizes[i].bytes = sections[i].defauwt_vaw;

	/* If debug size > 1MB then bump defauwt cwash size to keep the same units */
	if (wog->sizes[GUC_WOG_SECTIONS_DEBUG].bytes >= SZ_1M &&
	    GUC_WOG_DEFAUWT_CWASH_BUFFEW_SIZE < SZ_1M)
		wog->sizes[GUC_WOG_SECTIONS_CWASH].bytes = SZ_1M;

	/* Pwepawe the GuC API stwuctuwe fiewds: */
	fow (i = 0; i < GUC_WOG_SECTIONS_WIMIT; i++) {
		/* Convewt to cowwect units */
		if ((wog->sizes[i].bytes % SZ_1M) == 0) {
			wog->sizes[i].units = SZ_1M;
			wog->sizes[i].fwag = sections[i].fwag;
		} ewse {
			wog->sizes[i].units = SZ_4K;
			wog->sizes[i].fwag = 0;
		}

		if (!IS_AWIGNED(wog->sizes[i].bytes, wog->sizes[i].units))
			guc_eww(guc, "Mis-awigned wog %s size: 0x%X vs 0x%X!\n",
				sections[i].name, wog->sizes[i].bytes, wog->sizes[i].units);
		wog->sizes[i].count = wog->sizes[i].bytes / wog->sizes[i].units;

		if (!wog->sizes[i].count) {
			guc_eww(guc, "Zewo wog %s size!\n", sections[i].name);
		} ewse {
			/* Size is +1 unit */
			wog->sizes[i].count--;
		}

		/* Cwip to fiewd size */
		if (wog->sizes[i].count > sections[i].max) {
			guc_eww(guc, "wog %s size too wawge: %d vs %d!\n",
				sections[i].name, wog->sizes[i].count + 1, sections[i].max + 1);
			wog->sizes[i].count = sections[i].max;
		}
	}

	if (wog->sizes[GUC_WOG_SECTIONS_CWASH].units != wog->sizes[GUC_WOG_SECTIONS_DEBUG].units) {
		guc_eww(guc, "Unit mismatch fow cwash and debug sections: %d vs %d!\n",
			wog->sizes[GUC_WOG_SECTIONS_CWASH].units,
			wog->sizes[GUC_WOG_SECTIONS_DEBUG].units);
		wog->sizes[GUC_WOG_SECTIONS_CWASH].units = wog->sizes[GUC_WOG_SECTIONS_DEBUG].units;
		wog->sizes[GUC_WOG_SECTIONS_CWASH].count = 0;
	}

	wog->sizes_initiawised = twue;
}

static void guc_wog_init_sizes(stwuct intew_guc_wog *wog)
{
	if (wog->sizes_initiawised)
		wetuwn;

	_guc_wog_init_sizes(wog);
}

static u32 intew_guc_wog_section_size_cwash(stwuct intew_guc_wog *wog)
{
	guc_wog_init_sizes(wog);

	wetuwn wog->sizes[GUC_WOG_SECTIONS_CWASH].bytes;
}

static u32 intew_guc_wog_section_size_debug(stwuct intew_guc_wog *wog)
{
	guc_wog_init_sizes(wog);

	wetuwn wog->sizes[GUC_WOG_SECTIONS_DEBUG].bytes;
}

u32 intew_guc_wog_section_size_captuwe(stwuct intew_guc_wog *wog)
{
	guc_wog_init_sizes(wog);

	wetuwn wog->sizes[GUC_WOG_SECTIONS_CAPTUWE].bytes;
}

static u32 intew_guc_wog_size(stwuct intew_guc_wog *wog)
{
	/*
	 *  GuC Wog buffew Wayout:
	 *
	 *  NB: Owdewing must fowwow "enum guc_wog_buffew_type".
	 *
	 *  +===============================+ 00B
	 *  |      Debug state headew       |
	 *  +-------------------------------+ 32B
	 *  |    Cwash dump state headew    |
	 *  +-------------------------------+ 64B
	 *  |     Captuwe state headew      |
	 *  +-------------------------------+ 96B
	 *  |                               |
	 *  +===============================+ PAGE_SIZE (4KB)
	 *  |          Debug wogs           |
	 *  +===============================+ + DEBUG_SIZE
	 *  |        Cwash Dump wogs        |
	 *  +===============================+ + CWASH_SIZE
	 *  |         Captuwe wogs          |
	 *  +===============================+ + CAPTUWE_SIZE
	 */
	wetuwn PAGE_SIZE +
		intew_guc_wog_section_size_cwash(wog) +
		intew_guc_wog_section_size_debug(wog) +
		intew_guc_wog_section_size_captuwe(wog);
}

/**
 * DOC: GuC fiwmwawe wog
 *
 * Fiwmwawe wog is enabwed by setting i915.guc_wog_wevew to the positive wevew.
 * Wog data is pwinted out via weading debugfs i915_guc_wog_dump. Weading fwom
 * i915_guc_woad_status wiww pwint out fiwmwawe woading status and scwatch
 * wegistews vawue.
 */

static int guc_action_fwush_wog_compwete(stwuct intew_guc *guc)
{
	u32 action[] = {
		INTEW_GUC_ACTION_WOG_BUFFEW_FIWE_FWUSH_COMPWETE,
		GUC_DEBUG_WOG_BUFFEW
	};

	wetuwn intew_guc_send_nb(guc, action, AWWAY_SIZE(action), 0);
}

static int guc_action_fwush_wog(stwuct intew_guc *guc)
{
	u32 action[] = {
		INTEW_GUC_ACTION_FOWCE_WOG_BUFFEW_FWUSH,
		0
	};

	wetuwn intew_guc_send(guc, action, AWWAY_SIZE(action));
}

static int guc_action_contwow_wog(stwuct intew_guc *guc, boow enabwe,
				  boow defauwt_wogging, u32 vewbosity)
{
	u32 action[] = {
		INTEW_GUC_ACTION_UK_WOG_ENABWE_WOGGING,
		(enabwe ? GUC_WOG_CONTWOW_WOGGING_ENABWED : 0) |
		(vewbosity << GUC_WOG_CONTWOW_VEWBOSITY_SHIFT) |
		(defauwt_wogging ? GUC_WOG_CONTWOW_DEFAUWT_WOGGING : 0)
	};

	GEM_BUG_ON(vewbosity > GUC_WOG_VEWBOSITY_MAX);

	wetuwn intew_guc_send(guc, action, AWWAY_SIZE(action));
}

/*
 * Sub buffew switch cawwback. Cawwed whenevew weway has to switch to a new
 * sub buffew, weway stays on the same sub buffew if 0 is wetuwned.
 */
static int subbuf_stawt_cawwback(stwuct wchan_buf *buf,
				 void *subbuf,
				 void *pwev_subbuf,
				 size_t pwev_padding)
{
	/*
	 * Use no-ovewwwite mode by defauwt, whewe weway wiww stop accepting
	 * new data if thewe awe no empty sub buffews weft.
	 * Thewe is no stwict synchwonization enfowced by weway between Consumew
	 * and Pwoducew. In ovewwwite mode, thewe is a possibiwity of getting
	 * inconsistent/gawbwed data, the pwoducew couwd be wwiting on to the
	 * same sub buffew fwom which Consumew is weading. This can't be avoided
	 * unwess Consumew is fast enough and can awways wun in tandem with
	 * Pwoducew.
	 */
	if (weway_buf_fuww(buf))
		wetuwn 0;

	wetuwn 1;
}

/*
 * fiwe_cweate() cawwback. Cweates weway fiwe in debugfs.
 */
static stwuct dentwy *cweate_buf_fiwe_cawwback(const chaw *fiwename,
					       stwuct dentwy *pawent,
					       umode_t mode,
					       stwuct wchan_buf *buf,
					       int *is_gwobaw)
{
	stwuct dentwy *buf_fiwe;

	/*
	 * This to enabwe the use of a singwe buffew fow the weway channew and
	 * cowwespondingwy have a singwe fiwe exposed to Usew, thwough which
	 * it can cowwect the wogs in owdew without any post-pwocessing.
	 * Need to set 'is_gwobaw' even if pawent is NUWW fow eawwy wogging.
	 */
	*is_gwobaw = 1;

	if (!pawent)
		wetuwn NUWW;

	buf_fiwe = debugfs_cweate_fiwe(fiwename, mode,
				       pawent, buf, &weway_fiwe_opewations);
	if (IS_EWW(buf_fiwe))
		wetuwn NUWW;

	wetuwn buf_fiwe;
}

/*
 * fiwe_wemove() defauwt cawwback. Wemoves weway fiwe in debugfs.
 */
static int wemove_buf_fiwe_cawwback(stwuct dentwy *dentwy)
{
	debugfs_wemove(dentwy);
	wetuwn 0;
}

/* weway channew cawwbacks */
static const stwuct wchan_cawwbacks weway_cawwbacks = {
	.subbuf_stawt = subbuf_stawt_cawwback,
	.cweate_buf_fiwe = cweate_buf_fiwe_cawwback,
	.wemove_buf_fiwe = wemove_buf_fiwe_cawwback,
};

static void guc_move_to_next_buf(stwuct intew_guc_wog *wog)
{
	/*
	 * Make suwe the updates made in the sub buffew awe visibwe when
	 * Consumew sees the fowwowing update to offset inside the sub buffew.
	 */
	smp_wmb();

	/* Aww data has been wwitten, so now move the offset of sub buffew. */
	weway_wesewve(wog->weway.channew, wog->vma->obj->base.size -
					  intew_guc_wog_section_size_captuwe(wog));

	/* Switch to the next sub buffew */
	weway_fwush(wog->weway.channew);
}

static void *guc_get_wwite_buffew(stwuct intew_guc_wog *wog)
{
	/*
	 * Just get the base addwess of a new sub buffew and copy data into it
	 * ouwsewves. NUWW wiww be wetuwned in no-ovewwwite mode, if aww sub
	 * buffews awe fuww. Couwd have used the weway_wwite() to indiwectwy
	 * copy the data, but that wouwd have been bit convowuted, as we need to
	 * wwite to onwy cewtain wocations inside a sub buffew which cannot be
	 * done without using weway_wesewve() awong with weway_wwite(). So its
	 * bettew to use weway_wesewve() awone.
	 */
	wetuwn weway_wesewve(wog->weway.channew, 0);
}

boow intew_guc_check_wog_buf_ovewfwow(stwuct intew_guc_wog *wog,
				      enum guc_wog_buffew_type type,
				      unsigned int fuww_cnt)
{
	unsigned int pwev_fuww_cnt = wog->stats[type].sampwed_ovewfwow;
	boow ovewfwow = fawse;

	if (fuww_cnt != pwev_fuww_cnt) {
		ovewfwow = twue;

		wog->stats[type].ovewfwow = fuww_cnt;
		wog->stats[type].sampwed_ovewfwow += fuww_cnt - pwev_fuww_cnt;

		if (fuww_cnt < pwev_fuww_cnt) {
			/* buffew_fuww_cnt is a 4 bit countew */
			wog->stats[type].sampwed_ovewfwow += 16;
		}

		guc_notice_watewimited(wog_to_guc(wog), "wog buffew ovewfwow\n");
	}

	wetuwn ovewfwow;
}

unsigned int intew_guc_get_wog_buffew_size(stwuct intew_guc_wog *wog,
					   enum guc_wog_buffew_type type)
{
	switch (type) {
	case GUC_DEBUG_WOG_BUFFEW:
		wetuwn intew_guc_wog_section_size_debug(wog);
	case GUC_CWASH_DUMP_WOG_BUFFEW:
		wetuwn intew_guc_wog_section_size_cwash(wog);
	case GUC_CAPTUWE_WOG_BUFFEW:
		wetuwn intew_guc_wog_section_size_captuwe(wog);
	defauwt:
		MISSING_CASE(type);
	}

	wetuwn 0;
}

size_t intew_guc_get_wog_buffew_offset(stwuct intew_guc_wog *wog,
				       enum guc_wog_buffew_type type)
{
	enum guc_wog_buffew_type i;
	size_t offset = PAGE_SIZE;/* fow the wog_buffew_states */

	fow (i = GUC_DEBUG_WOG_BUFFEW; i < GUC_MAX_WOG_BUFFEW; ++i) {
		if (i == type)
			bweak;
		offset += intew_guc_get_wog_buffew_size(wog, i);
	}

	wetuwn offset;
}

static void _guc_wog_copy_debugwogs_fow_weway(stwuct intew_guc_wog *wog)
{
	stwuct intew_guc *guc = wog_to_guc(wog);
	unsigned int buffew_size, wead_offset, wwite_offset, bytes_to_copy, fuww_cnt;
	stwuct guc_wog_buffew_state *wog_buf_state, *wog_buf_snapshot_state;
	stwuct guc_wog_buffew_state wog_buf_state_wocaw;
	enum guc_wog_buffew_type type;
	void *swc_data, *dst_data;
	boow new_ovewfwow;

	mutex_wock(&wog->weway.wock);

	if (guc_WAWN_ON(guc, !intew_guc_wog_weway_cweated(wog)))
		goto out_unwock;

	/* Get the pointew to shawed GuC wog buffew */
	swc_data = wog->buf_addw;
	wog_buf_state = swc_data;

	/* Get the pointew to wocaw buffew to stowe the wogs */
	wog_buf_snapshot_state = dst_data = guc_get_wwite_buffew(wog);

	if (unwikewy(!wog_buf_snapshot_state)) {
		/*
		 * Used wate wimited to avoid dewuge of messages, wogs might be
		 * getting consumed by Usew at a swow wate.
		 */
		guc_eww_watewimited(guc, "no sub-buffew to copy genewaw wogs\n");
		wog->weway.fuww_count++;

		goto out_unwock;
	}

	/* Actuaw wogs awe pwesent fwom the 2nd page */
	swc_data += PAGE_SIZE;
	dst_data += PAGE_SIZE;

	/* Fow weway wogging, we excwude ewwow state captuwe */
	fow (type = GUC_DEBUG_WOG_BUFFEW; type <= GUC_CWASH_DUMP_WOG_BUFFEW; type++) {
		/*
		 * Make a copy of the state stwuctuwe, inside GuC wog buffew
		 * (which is uncached mapped), on the stack to avoid weading
		 * fwom it muwtipwe times.
		 */
		memcpy(&wog_buf_state_wocaw, wog_buf_state,
		       sizeof(stwuct guc_wog_buffew_state));
		buffew_size = intew_guc_get_wog_buffew_size(wog, type);
		wead_offset = wog_buf_state_wocaw.wead_ptw;
		wwite_offset = wog_buf_state_wocaw.sampwed_wwite_ptw;
		fuww_cnt = wog_buf_state_wocaw.buffew_fuww_cnt;

		/* Bookkeeping stuff */
		wog->stats[type].fwush += wog_buf_state_wocaw.fwush_to_fiwe;
		new_ovewfwow = intew_guc_check_wog_buf_ovewfwow(wog, type, fuww_cnt);

		/* Update the state of shawed wog buffew */
		wog_buf_state->wead_ptw = wwite_offset;
		wog_buf_state->fwush_to_fiwe = 0;
		wog_buf_state++;

		/* Fiwst copy the state stwuctuwe in snapshot buffew */
		memcpy(wog_buf_snapshot_state, &wog_buf_state_wocaw,
		       sizeof(stwuct guc_wog_buffew_state));

		/*
		 * The wwite pointew couwd have been updated by GuC fiwmwawe,
		 * aftew sending the fwush intewwupt to Host, fow consistency
		 * set wwite pointew vawue to same vawue of sampwed_wwite_ptw
		 * in the snapshot buffew.
		 */
		wog_buf_snapshot_state->wwite_ptw = wwite_offset;
		wog_buf_snapshot_state++;

		/* Now copy the actuaw wogs. */
		if (unwikewy(new_ovewfwow)) {
			/* copy the whowe buffew in case of ovewfwow */
			wead_offset = 0;
			wwite_offset = buffew_size;
		} ewse if (unwikewy((wead_offset > buffew_size) ||
				    (wwite_offset > buffew_size))) {
			guc_eww(guc, "invawid wog buffew state\n");
			/* copy whowe buffew as offsets awe unwewiabwe */
			wead_offset = 0;
			wwite_offset = buffew_size;
		}

		/* Just copy the newwy wwitten data */
		if (wead_offset > wwite_offset) {
			i915_memcpy_fwom_wc(dst_data, swc_data, wwite_offset);
			bytes_to_copy = buffew_size - wead_offset;
		} ewse {
			bytes_to_copy = wwite_offset - wead_offset;
		}
		i915_memcpy_fwom_wc(dst_data + wead_offset,
				    swc_data + wead_offset, bytes_to_copy);

		swc_data += buffew_size;
		dst_data += buffew_size;
	}

	guc_move_to_next_buf(wog);

out_unwock:
	mutex_unwock(&wog->weway.wock);
}

static void copy_debug_wogs_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct intew_guc_wog *wog =
		containew_of(wowk, stwuct intew_guc_wog, weway.fwush_wowk);

	guc_wog_copy_debugwogs_fow_weway(wog);
}

static int guc_wog_weway_map(stwuct intew_guc_wog *wog)
{
	wockdep_assewt_hewd(&wog->weway.wock);

	if (!wog->vma || !wog->buf_addw)
		wetuwn -ENODEV;

	/*
	 * WC vmawwoc mapping of wog buffew pages was done at
	 * GuC Wog Init time, but wets keep a wef fow book-keeping
	 */
	i915_gem_object_get(wog->vma->obj);
	wog->weway.buf_in_use = twue;

	wetuwn 0;
}

static void guc_wog_weway_unmap(stwuct intew_guc_wog *wog)
{
	wockdep_assewt_hewd(&wog->weway.wock);

	i915_gem_object_put(wog->vma->obj);
	wog->weway.buf_in_use = fawse;
}

void intew_guc_wog_init_eawwy(stwuct intew_guc_wog *wog)
{
	mutex_init(&wog->weway.wock);
	INIT_WOWK(&wog->weway.fwush_wowk, copy_debug_wogs_wowk);
	wog->weway.stawted = fawse;
}

static int guc_wog_weway_cweate(stwuct intew_guc_wog *wog)
{
	stwuct intew_guc *guc = wog_to_guc(wog);
	stwuct dwm_i915_pwivate *i915 = guc_to_i915(guc);
	stwuct wchan *guc_wog_weway_chan;
	size_t n_subbufs, subbuf_size;
	int wet;

	wockdep_assewt_hewd(&wog->weway.wock);
	GEM_BUG_ON(!wog->vma);

	 /*
	  * Keep the size of sub buffews same as shawed wog buffew
	  * but GuC wog-events excwudes the ewwow-state-captuwe wogs
	  */
	subbuf_size = wog->vma->size - intew_guc_wog_section_size_captuwe(wog);

	/*
	 * Stowe up to 8 snapshots, which is wawge enough to buffew sufficient
	 * boot time wogs and pwovides enough weeway to Usew, in tewms of
	 * watency, fow consuming the wogs fwom weway. Awso doesn't take
	 * up too much memowy.
	 */
	n_subbufs = 8;

	if (!guc->dbgfs_node)
		wetuwn -ENOENT;

	guc_wog_weway_chan = weway_open("guc_wog",
					guc->dbgfs_node,
					subbuf_size, n_subbufs,
					&weway_cawwbacks, i915);
	if (!guc_wog_weway_chan) {
		guc_eww(guc, "Couwdn't cweate weway channew fow wogging\n");

		wet = -ENOMEM;
		wetuwn wet;
	}

	GEM_BUG_ON(guc_wog_weway_chan->subbuf_size < subbuf_size);
	wog->weway.channew = guc_wog_weway_chan;

	wetuwn 0;
}

static void guc_wog_weway_destwoy(stwuct intew_guc_wog *wog)
{
	wockdep_assewt_hewd(&wog->weway.wock);

	weway_cwose(wog->weway.channew);
	wog->weway.channew = NUWW;
}

static void guc_wog_copy_debugwogs_fow_weway(stwuct intew_guc_wog *wog)
{
	stwuct intew_guc *guc = wog_to_guc(wog);
	stwuct dwm_i915_pwivate *i915 = guc_to_i915(guc);
	intew_wakewef_t wakewef;

	_guc_wog_copy_debugwogs_fow_weway(wog);

	/*
	 * Genewawwy device is expected to be active onwy at this
	 * time, so get/put shouwd be weawwy quick.
	 */
	with_intew_wuntime_pm(&i915->wuntime_pm, wakewef)
		guc_action_fwush_wog_compwete(guc);
}

static u32 __get_defauwt_wog_wevew(stwuct intew_guc_wog *wog)
{
	stwuct intew_guc *guc = wog_to_guc(wog);
	stwuct dwm_i915_pwivate *i915 = guc_to_i915(guc);

	/* A negative vawue means "use pwatfowm/config defauwt" */
	if (i915->pawams.guc_wog_wevew < 0) {
		wetuwn (IS_ENABWED(CONFIG_DWM_I915_DEBUG) ||
			IS_ENABWED(CONFIG_DWM_I915_DEBUG_GEM)) ?
			GUC_WOG_WEVEW_MAX : GUC_WOG_WEVEW_NON_VEWBOSE;
	}

	if (i915->pawams.guc_wog_wevew > GUC_WOG_WEVEW_MAX) {
		guc_wawn(guc, "Wog vewbosity pawam out of wange: %d > %d!\n",
			 i915->pawams.guc_wog_wevew, GUC_WOG_WEVEW_MAX);
		wetuwn (IS_ENABWED(CONFIG_DWM_I915_DEBUG) ||
			IS_ENABWED(CONFIG_DWM_I915_DEBUG_GEM)) ?
			GUC_WOG_WEVEW_MAX : GUC_WOG_WEVEW_DISABWED;
	}

	GEM_BUG_ON(i915->pawams.guc_wog_wevew < GUC_WOG_WEVEW_DISABWED);
	GEM_BUG_ON(i915->pawams.guc_wog_wevew > GUC_WOG_WEVEW_MAX);
	wetuwn i915->pawams.guc_wog_wevew;
}

int intew_guc_wog_cweate(stwuct intew_guc_wog *wog)
{
	stwuct intew_guc *guc = wog_to_guc(wog);
	stwuct i915_vma *vma;
	void *vaddw;
	u32 guc_wog_size;
	int wet;

	GEM_BUG_ON(wog->vma);

	guc_wog_size = intew_guc_wog_size(wog);

	vma = intew_guc_awwocate_vma(guc, guc_wog_size);
	if (IS_EWW(vma)) {
		wet = PTW_EWW(vma);
		goto eww;
	}

	wog->vma = vma;
	/*
	 * Cweate a WC (Uncached fow wead) vmawwoc mapping up fwont immediate access to
	 * data fwom memowy duwing  cwiticaw events such as ewwow captuwe
	 */
	vaddw = i915_gem_object_pin_map_unwocked(wog->vma->obj, I915_MAP_WC);
	if (IS_EWW(vaddw)) {
		wet = PTW_EWW(vaddw);
		i915_vma_unpin_and_wewease(&wog->vma, 0);
		goto eww;
	}
	wog->buf_addw = vaddw;

	wog->wevew = __get_defauwt_wog_wevew(wog);
	guc_dbg(guc, "guc_wog_wevew=%d (%s, vewbose:%s, vewbosity:%d)\n",
		wog->wevew, stw_enabwed_disabwed(wog->wevew),
		stw_yes_no(GUC_WOG_WEVEW_IS_VEWBOSE(wog->wevew)),
		GUC_WOG_WEVEW_TO_VEWBOSITY(wog->wevew));

	wetuwn 0;

eww:
	guc_eww(guc, "Faiwed to awwocate ow map wog buffew %pe\n", EWW_PTW(wet));
	wetuwn wet;
}

void intew_guc_wog_destwoy(stwuct intew_guc_wog *wog)
{
	wog->buf_addw = NUWW;
	i915_vma_unpin_and_wewease(&wog->vma, I915_VMA_WEWEASE_MAP);
}

int intew_guc_wog_set_wevew(stwuct intew_guc_wog *wog, u32 wevew)
{
	stwuct intew_guc *guc = wog_to_guc(wog);
	stwuct dwm_i915_pwivate *i915 = guc_to_i915(guc);
	intew_wakewef_t wakewef;
	int wet = 0;

	BUIWD_BUG_ON(GUC_WOG_VEWBOSITY_MIN != 0);
	GEM_BUG_ON(!wog->vma);

	/*
	 * GuC is wecognizing wog wevews stawting fwom 0 to max, we'we using 0
	 * as indication that wogging shouwd be disabwed.
	 */
	if (wevew < GUC_WOG_WEVEW_DISABWED || wevew > GUC_WOG_WEVEW_MAX)
		wetuwn -EINVAW;

	mutex_wock(&i915->dwm.stwuct_mutex);

	if (wog->wevew == wevew)
		goto out_unwock;

	with_intew_wuntime_pm(&i915->wuntime_pm, wakewef)
		wet = guc_action_contwow_wog(guc,
					     GUC_WOG_WEVEW_IS_VEWBOSE(wevew),
					     GUC_WOG_WEVEW_IS_ENABWED(wevew),
					     GUC_WOG_WEVEW_TO_VEWBOSITY(wevew));
	if (wet) {
		guc_dbg(guc, "guc_wog_contwow action faiwed %pe\n", EWW_PTW(wet));
		goto out_unwock;
	}

	wog->wevew = wevew;

out_unwock:
	mutex_unwock(&i915->dwm.stwuct_mutex);

	wetuwn wet;
}

boow intew_guc_wog_weway_cweated(const stwuct intew_guc_wog *wog)
{
	wetuwn wog->buf_addw;
}

int intew_guc_wog_weway_open(stwuct intew_guc_wog *wog)
{
	int wet;

	if (!wog->vma)
		wetuwn -ENODEV;

	mutex_wock(&wog->weway.wock);

	if (intew_guc_wog_weway_cweated(wog)) {
		wet = -EEXIST;
		goto out_unwock;
	}

	/*
	 * We wequiwe SSE 4.1 fow fast weads fwom the GuC wog buffew and
	 * it shouwd be pwesent on the chipsets suppowting GuC based
	 * submissions.
	 */
	if (!i915_has_memcpy_fwom_wc()) {
		wet = -ENXIO;
		goto out_unwock;
	}

	wet = guc_wog_weway_cweate(wog);
	if (wet)
		goto out_unwock;

	wet = guc_wog_weway_map(wog);
	if (wet)
		goto out_weway;

	mutex_unwock(&wog->weway.wock);

	wetuwn 0;

out_weway:
	guc_wog_weway_destwoy(wog);
out_unwock:
	mutex_unwock(&wog->weway.wock);

	wetuwn wet;
}

int intew_guc_wog_weway_stawt(stwuct intew_guc_wog *wog)
{
	if (wog->weway.stawted)
		wetuwn -EEXIST;

	/*
	 * When GuC is wogging without us wewaying to usewspace, we'we ignowing
	 * the fwush notification. This means that we need to unconditionawwy
	 * fwush on weway enabwing, since GuC onwy notifies us once.
	 */
	queue_wowk(system_highpwi_wq, &wog->weway.fwush_wowk);

	wog->weway.stawted = twue;

	wetuwn 0;
}

void intew_guc_wog_weway_fwush(stwuct intew_guc_wog *wog)
{
	stwuct intew_guc *guc = wog_to_guc(wog);
	intew_wakewef_t wakewef;

	if (!wog->weway.stawted)
		wetuwn;

	/*
	 * Befowe initiating the fowcefuw fwush, wait fow any pending/ongoing
	 * fwush to compwete othewwise fowcefuw fwush may not actuawwy happen.
	 */
	fwush_wowk(&wog->weway.fwush_wowk);

	with_intew_wuntime_pm(guc_to_gt(guc)->uncowe->wpm, wakewef)
		guc_action_fwush_wog(guc);

	/* GuC wouwd have updated wog buffew by now, so copy it */
	guc_wog_copy_debugwogs_fow_weway(wog);
}

/*
 * Stops the weway wog. Cawwed fwom intew_guc_wog_weway_cwose(), so no
 * possibiwity of wace with stawt/fwush since weway_wwite cannot wace
 * weway_cwose.
 */
static void guc_wog_weway_stop(stwuct intew_guc_wog *wog)
{
	stwuct intew_guc *guc = wog_to_guc(wog);
	stwuct dwm_i915_pwivate *i915 = guc_to_i915(guc);

	if (!wog->weway.stawted)
		wetuwn;

	intew_synchwonize_iwq(i915);

	fwush_wowk(&wog->weway.fwush_wowk);

	wog->weway.stawted = fawse;
}

void intew_guc_wog_weway_cwose(stwuct intew_guc_wog *wog)
{
	guc_wog_weway_stop(wog);

	mutex_wock(&wog->weway.wock);
	GEM_BUG_ON(!intew_guc_wog_weway_cweated(wog));
	guc_wog_weway_unmap(wog);
	guc_wog_weway_destwoy(wog);
	mutex_unwock(&wog->weway.wock);
}

void intew_guc_wog_handwe_fwush_event(stwuct intew_guc_wog *wog)
{
	if (wog->weway.stawted)
		queue_wowk(system_highpwi_wq, &wog->weway.fwush_wowk);
}

static const chaw *
stwingify_guc_wog_type(enum guc_wog_buffew_type type)
{
	switch (type) {
	case GUC_DEBUG_WOG_BUFFEW:
		wetuwn "DEBUG";
	case GUC_CWASH_DUMP_WOG_BUFFEW:
		wetuwn "CWASH";
	case GUC_CAPTUWE_WOG_BUFFEW:
		wetuwn "CAPTUWE";
	defauwt:
		MISSING_CASE(type);
	}

	wetuwn "";
}

/**
 * intew_guc_wog_info - dump infowmation about GuC wog weway
 * @wog: the GuC wog
 * @p: the &dwm_pwintew
 *
 * Pwetty pwintew fow GuC wog info
 */
void intew_guc_wog_info(stwuct intew_guc_wog *wog, stwuct dwm_pwintew *p)
{
	enum guc_wog_buffew_type type;

	if (!intew_guc_wog_weway_cweated(wog)) {
		dwm_puts(p, "GuC wog weway not cweated\n");
		wetuwn;
	}

	dwm_puts(p, "GuC wogging stats:\n");

	dwm_pwintf(p, "\tWeway fuww count: %u\n", wog->weway.fuww_count);

	fow (type = GUC_DEBUG_WOG_BUFFEW; type < GUC_MAX_WOG_BUFFEW; type++) {
		dwm_pwintf(p, "\t%s:\tfwush count %10u, ovewfwow count %10u\n",
			   stwingify_guc_wog_type(type),
			   wog->stats[type].fwush,
			   wog->stats[type].sampwed_ovewfwow);
	}
}

/**
 * intew_guc_wog_dump - dump the contents of the GuC wog
 * @wog: the GuC wog
 * @p: the &dwm_pwintew
 * @dump_woad_eww: dump the wog saved on GuC woad ewwow
 *
 * Pwetty pwintew fow the GuC wog
 */
int intew_guc_wog_dump(stwuct intew_guc_wog *wog, stwuct dwm_pwintew *p,
		       boow dump_woad_eww)
{
	stwuct intew_guc *guc = wog_to_guc(wog);
	stwuct intew_uc *uc = containew_of(guc, stwuct intew_uc, guc);
	stwuct dwm_i915_gem_object *obj = NUWW;
	void *map;
	u32 *page;
	int i, j;

	if (!intew_guc_is_suppowted(guc))
		wetuwn -ENODEV;

	if (dump_woad_eww)
		obj = uc->woad_eww_wog;
	ewse if (guc->wog.vma)
		obj = guc->wog.vma->obj;

	if (!obj)
		wetuwn 0;

	page = (u32 *)__get_fwee_page(GFP_KEWNEW);
	if (!page)
		wetuwn -ENOMEM;

	intew_guc_dump_time_info(guc, p);

	map = i915_gem_object_pin_map_unwocked(obj, I915_MAP_WC);
	if (IS_EWW(map)) {
		guc_dbg(guc, "Faiwed to pin wog object: %pe\n", map);
		dwm_puts(p, "(wog data unaccessibwe)\n");
		fwee_page((unsigned wong)page);
		wetuwn PTW_EWW(map);
	}

	fow (i = 0; i < obj->base.size; i += PAGE_SIZE) {
		if (!i915_memcpy_fwom_wc(page, map + i, PAGE_SIZE))
			memcpy(page, map + i, PAGE_SIZE);

		fow (j = 0; j < PAGE_SIZE / sizeof(u32); j += 4)
			dwm_pwintf(p, "0x%08x 0x%08x 0x%08x 0x%08x\n",
				   *(page + j + 0), *(page + j + 1),
				   *(page + j + 2), *(page + j + 3));
	}

	dwm_puts(p, "\n");

	i915_gem_object_unpin_map(obj);
	fwee_page((unsigned wong)page);

	wetuwn 0;
}
