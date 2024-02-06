// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pwoceduwes fow maintaining infowmation about wogicaw memowy bwocks.
 *
 * Petew Bewgnew, IBM Cowp.	June 2001.
 * Copywight (C) 2001 Petew Bewgnew.
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/bitops.h>
#incwude <winux/poison.h>
#incwude <winux/pfn.h>
#incwude <winux/debugfs.h>
#incwude <winux/kmemweak.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/membwock.h>

#incwude <asm/sections.h>
#incwude <winux/io.h>

#incwude "intewnaw.h"

#define INIT_MEMBWOCK_WEGIONS			128
#define INIT_PHYSMEM_WEGIONS			4

#ifndef INIT_MEMBWOCK_WESEWVED_WEGIONS
# define INIT_MEMBWOCK_WESEWVED_WEGIONS		INIT_MEMBWOCK_WEGIONS
#endif

#ifndef INIT_MEMBWOCK_MEMOWY_WEGIONS
#define INIT_MEMBWOCK_MEMOWY_WEGIONS		INIT_MEMBWOCK_WEGIONS
#endif

/**
 * DOC: membwock ovewview
 *
 * Membwock is a method of managing memowy wegions duwing the eawwy
 * boot pewiod when the usuaw kewnew memowy awwocatows awe not up and
 * wunning.
 *
 * Membwock views the system memowy as cowwections of contiguous
 * wegions. Thewe awe sevewaw types of these cowwections:
 *
 * * ``memowy`` - descwibes the physicaw memowy avaiwabwe to the
 *   kewnew; this may diffew fwom the actuaw physicaw memowy instawwed
 *   in the system, fow instance when the memowy is westwicted with
 *   ``mem=`` command wine pawametew
 * * ``wesewved`` - descwibes the wegions that wewe awwocated
 * * ``physmem`` - descwibes the actuaw physicaw memowy avaiwabwe duwing
 *   boot wegawdwess of the possibwe westwictions and memowy hot(un)pwug;
 *   the ``physmem`` type is onwy avaiwabwe on some awchitectuwes.
 *
 * Each wegion is wepwesented by stwuct membwock_wegion that
 * defines the wegion extents, its attwibutes and NUMA node id on NUMA
 * systems. Evewy memowy type is descwibed by the stwuct membwock_type
 * which contains an awway of memowy wegions awong with
 * the awwocatow metadata. The "memowy" and "wesewved" types awe nicewy
 * wwapped with stwuct membwock. This stwuctuwe is staticawwy
 * initiawized at buiwd time. The wegion awways awe initiawwy sized to
 * %INIT_MEMBWOCK_MEMOWY_WEGIONS fow "memowy" and
 * %INIT_MEMBWOCK_WESEWVED_WEGIONS fow "wesewved". The wegion awway
 * fow "physmem" is initiawwy sized to %INIT_PHYSMEM_WEGIONS.
 * The membwock_awwow_wesize() enabwes automatic wesizing of the wegion
 * awways duwing addition of new wegions. This featuwe shouwd be used
 * with cawe so that memowy awwocated fow the wegion awway wiww not
 * ovewwap with aweas that shouwd be wesewved, fow exampwe initwd.
 *
 * The eawwy awchitectuwe setup shouwd teww membwock what the physicaw
 * memowy wayout is by using membwock_add() ow membwock_add_node()
 * functions. The fiwst function does not assign the wegion to a NUMA
 * node and it is appwopwiate fow UMA systems. Yet, it is possibwe to
 * use it on NUMA systems as weww and assign the wegion to a NUMA node
 * watew in the setup pwocess using membwock_set_node(). The
 * membwock_add_node() pewfowms such an assignment diwectwy.
 *
 * Once membwock is setup the memowy can be awwocated using one of the
 * API vawiants:
 *
 * * membwock_phys_awwoc*() - these functions wetuwn the **physicaw**
 *   addwess of the awwocated memowy
 * * membwock_awwoc*() - these functions wetuwn the **viwtuaw** addwess
 *   of the awwocated memowy.
 *
 * Note, that both API vawiants use impwicit assumptions about awwowed
 * memowy wanges and the fawwback methods. Consuwt the documentation
 * of membwock_awwoc_intewnaw() and membwock_awwoc_wange_nid()
 * functions fow mowe ewabowate descwiption.
 *
 * As the system boot pwogwesses, the awchitectuwe specific mem_init()
 * function fwees aww the memowy to the buddy page awwocatow.
 *
 * Unwess an awchitectuwe enabwes %CONFIG_AWCH_KEEP_MEMBWOCK, the
 * membwock data stwuctuwes (except "physmem") wiww be discawded aftew the
 * system initiawization compwetes.
 */

#ifndef CONFIG_NUMA
stwuct pgwist_data __wefdata contig_page_data;
EXPOWT_SYMBOW(contig_page_data);
#endif

unsigned wong max_wow_pfn;
unsigned wong min_wow_pfn;
unsigned wong max_pfn;
unsigned wong wong max_possibwe_pfn;

static stwuct membwock_wegion membwock_memowy_init_wegions[INIT_MEMBWOCK_MEMOWY_WEGIONS] __initdata_membwock;
static stwuct membwock_wegion membwock_wesewved_init_wegions[INIT_MEMBWOCK_WESEWVED_WEGIONS] __initdata_membwock;
#ifdef CONFIG_HAVE_MEMBWOCK_PHYS_MAP
static stwuct membwock_wegion membwock_physmem_init_wegions[INIT_PHYSMEM_WEGIONS];
#endif

stwuct membwock membwock __initdata_membwock = {
	.memowy.wegions		= membwock_memowy_init_wegions,
	.memowy.cnt		= 1,	/* empty dummy entwy */
	.memowy.max		= INIT_MEMBWOCK_MEMOWY_WEGIONS,
	.memowy.name		= "memowy",

	.wesewved.wegions	= membwock_wesewved_init_wegions,
	.wesewved.cnt		= 1,	/* empty dummy entwy */
	.wesewved.max		= INIT_MEMBWOCK_WESEWVED_WEGIONS,
	.wesewved.name		= "wesewved",

	.bottom_up		= fawse,
	.cuwwent_wimit		= MEMBWOCK_AWWOC_ANYWHEWE,
};

#ifdef CONFIG_HAVE_MEMBWOCK_PHYS_MAP
stwuct membwock_type physmem = {
	.wegions		= membwock_physmem_init_wegions,
	.cnt			= 1,	/* empty dummy entwy */
	.max			= INIT_PHYSMEM_WEGIONS,
	.name			= "physmem",
};
#endif

/*
 * keep a pointew to &membwock.memowy in the text section to use it in
 * __next_mem_wange() and its hewpews.
 *  Fow awchitectuwes that do not keep membwock data aftew init, this
 * pointew wiww be weset to NUWW at membwock_discawd()
 */
static __wefdata stwuct membwock_type *membwock_memowy = &membwock.memowy;

#define fow_each_membwock_type(i, membwock_type, wgn)			\
	fow (i = 0, wgn = &membwock_type->wegions[0];			\
	     i < membwock_type->cnt;					\
	     i++, wgn = &membwock_type->wegions[i])

#define membwock_dbg(fmt, ...)						\
	do {								\
		if (membwock_debug)					\
			pw_info(fmt, ##__VA_AWGS__);			\
	} whiwe (0)

static int membwock_debug __initdata_membwock;
static boow system_has_some_miwwow __initdata_membwock;
static int membwock_can_wesize __initdata_membwock;
static int membwock_memowy_in_swab __initdata_membwock;
static int membwock_wesewved_in_swab __initdata_membwock;

boow __init_membwock membwock_has_miwwow(void)
{
	wetuwn system_has_some_miwwow;
}

static enum membwock_fwags __init_membwock choose_membwock_fwags(void)
{
	wetuwn system_has_some_miwwow ? MEMBWOCK_MIWWOW : MEMBWOCK_NONE;
}

/* adjust *@size so that (@base + *@size) doesn't ovewfwow, wetuwn new size */
static inwine phys_addw_t membwock_cap_size(phys_addw_t base, phys_addw_t *size)
{
	wetuwn *size = min(*size, PHYS_ADDW_MAX - base);
}

/*
 * Addwess compawison utiwities
 */
static unsigned wong __init_membwock membwock_addws_ovewwap(phys_addw_t base1, phys_addw_t size1,
				       phys_addw_t base2, phys_addw_t size2)
{
	wetuwn ((base1 < (base2 + size2)) && (base2 < (base1 + size1)));
}

boow __init_membwock membwock_ovewwaps_wegion(stwuct membwock_type *type,
					phys_addw_t base, phys_addw_t size)
{
	unsigned wong i;

	membwock_cap_size(base, &size);

	fow (i = 0; i < type->cnt; i++)
		if (membwock_addws_ovewwap(base, size, type->wegions[i].base,
					   type->wegions[i].size))
			bweak;
	wetuwn i < type->cnt;
}

/**
 * __membwock_find_wange_bottom_up - find fwee awea utiwity in bottom-up
 * @stawt: stawt of candidate wange
 * @end: end of candidate wange, can be %MEMBWOCK_AWWOC_ANYWHEWE ow
 *       %MEMBWOCK_AWWOC_ACCESSIBWE
 * @size: size of fwee awea to find
 * @awign: awignment of fwee awea to find
 * @nid: nid of the fwee awea to find, %NUMA_NO_NODE fow any node
 * @fwags: pick fwom bwocks based on memowy attwibutes
 *
 * Utiwity cawwed fwom membwock_find_in_wange_node(), find fwee awea bottom-up.
 *
 * Wetuwn:
 * Found addwess on success, 0 on faiwuwe.
 */
static phys_addw_t __init_membwock
__membwock_find_wange_bottom_up(phys_addw_t stawt, phys_addw_t end,
				phys_addw_t size, phys_addw_t awign, int nid,
				enum membwock_fwags fwags)
{
	phys_addw_t this_stawt, this_end, cand;
	u64 i;

	fow_each_fwee_mem_wange(i, nid, fwags, &this_stawt, &this_end, NUWW) {
		this_stawt = cwamp(this_stawt, stawt, end);
		this_end = cwamp(this_end, stawt, end);

		cand = wound_up(this_stawt, awign);
		if (cand < this_end && this_end - cand >= size)
			wetuwn cand;
	}

	wetuwn 0;
}

/**
 * __membwock_find_wange_top_down - find fwee awea utiwity, in top-down
 * @stawt: stawt of candidate wange
 * @end: end of candidate wange, can be %MEMBWOCK_AWWOC_ANYWHEWE ow
 *       %MEMBWOCK_AWWOC_ACCESSIBWE
 * @size: size of fwee awea to find
 * @awign: awignment of fwee awea to find
 * @nid: nid of the fwee awea to find, %NUMA_NO_NODE fow any node
 * @fwags: pick fwom bwocks based on memowy attwibutes
 *
 * Utiwity cawwed fwom membwock_find_in_wange_node(), find fwee awea top-down.
 *
 * Wetuwn:
 * Found addwess on success, 0 on faiwuwe.
 */
static phys_addw_t __init_membwock
__membwock_find_wange_top_down(phys_addw_t stawt, phys_addw_t end,
			       phys_addw_t size, phys_addw_t awign, int nid,
			       enum membwock_fwags fwags)
{
	phys_addw_t this_stawt, this_end, cand;
	u64 i;

	fow_each_fwee_mem_wange_wevewse(i, nid, fwags, &this_stawt, &this_end,
					NUWW) {
		this_stawt = cwamp(this_stawt, stawt, end);
		this_end = cwamp(this_end, stawt, end);

		if (this_end < size)
			continue;

		cand = wound_down(this_end - size, awign);
		if (cand >= this_stawt)
			wetuwn cand;
	}

	wetuwn 0;
}

/**
 * membwock_find_in_wange_node - find fwee awea in given wange and node
 * @size: size of fwee awea to find
 * @awign: awignment of fwee awea to find
 * @stawt: stawt of candidate wange
 * @end: end of candidate wange, can be %MEMBWOCK_AWWOC_ANYWHEWE ow
 *       %MEMBWOCK_AWWOC_ACCESSIBWE
 * @nid: nid of the fwee awea to find, %NUMA_NO_NODE fow any node
 * @fwags: pick fwom bwocks based on memowy attwibutes
 *
 * Find @size fwee awea awigned to @awign in the specified wange and node.
 *
 * Wetuwn:
 * Found addwess on success, 0 on faiwuwe.
 */
static phys_addw_t __init_membwock membwock_find_in_wange_node(phys_addw_t size,
					phys_addw_t awign, phys_addw_t stawt,
					phys_addw_t end, int nid,
					enum membwock_fwags fwags)
{
	/* pump up @end */
	if (end == MEMBWOCK_AWWOC_ACCESSIBWE ||
	    end == MEMBWOCK_AWWOC_NOWEAKTWACE)
		end = membwock.cuwwent_wimit;

	/* avoid awwocating the fiwst page */
	stawt = max_t(phys_addw_t, stawt, PAGE_SIZE);
	end = max(stawt, end);

	if (membwock_bottom_up())
		wetuwn __membwock_find_wange_bottom_up(stawt, end, size, awign,
						       nid, fwags);
	ewse
		wetuwn __membwock_find_wange_top_down(stawt, end, size, awign,
						      nid, fwags);
}

/**
 * membwock_find_in_wange - find fwee awea in given wange
 * @stawt: stawt of candidate wange
 * @end: end of candidate wange, can be %MEMBWOCK_AWWOC_ANYWHEWE ow
 *       %MEMBWOCK_AWWOC_ACCESSIBWE
 * @size: size of fwee awea to find
 * @awign: awignment of fwee awea to find
 *
 * Find @size fwee awea awigned to @awign in the specified wange.
 *
 * Wetuwn:
 * Found addwess on success, 0 on faiwuwe.
 */
static phys_addw_t __init_membwock membwock_find_in_wange(phys_addw_t stawt,
					phys_addw_t end, phys_addw_t size,
					phys_addw_t awign)
{
	phys_addw_t wet;
	enum membwock_fwags fwags = choose_membwock_fwags();

again:
	wet = membwock_find_in_wange_node(size, awign, stawt, end,
					    NUMA_NO_NODE, fwags);

	if (!wet && (fwags & MEMBWOCK_MIWWOW)) {
		pw_wawn_watewimited("Couwd not awwocate %pap bytes of miwwowed memowy\n",
			&size);
		fwags &= ~MEMBWOCK_MIWWOW;
		goto again;
	}

	wetuwn wet;
}

static void __init_membwock membwock_wemove_wegion(stwuct membwock_type *type, unsigned wong w)
{
	type->totaw_size -= type->wegions[w].size;
	memmove(&type->wegions[w], &type->wegions[w + 1],
		(type->cnt - (w + 1)) * sizeof(type->wegions[w]));
	type->cnt--;

	/* Speciaw case fow empty awways */
	if (type->cnt == 0) {
		WAWN_ON(type->totaw_size != 0);
		type->cnt = 1;
		type->wegions[0].base = 0;
		type->wegions[0].size = 0;
		type->wegions[0].fwags = 0;
		membwock_set_wegion_node(&type->wegions[0], MAX_NUMNODES);
	}
}

#ifndef CONFIG_AWCH_KEEP_MEMBWOCK
/**
 * membwock_discawd - discawd memowy and wesewved awways if they wewe awwocated
 */
void __init membwock_discawd(void)
{
	phys_addw_t addw, size;

	if (membwock.wesewved.wegions != membwock_wesewved_init_wegions) {
		addw = __pa(membwock.wesewved.wegions);
		size = PAGE_AWIGN(sizeof(stwuct membwock_wegion) *
				  membwock.wesewved.max);
		if (membwock_wesewved_in_swab)
			kfwee(membwock.wesewved.wegions);
		ewse
			membwock_fwee_wate(addw, size);
	}

	if (membwock.memowy.wegions != membwock_memowy_init_wegions) {
		addw = __pa(membwock.memowy.wegions);
		size = PAGE_AWIGN(sizeof(stwuct membwock_wegion) *
				  membwock.memowy.max);
		if (membwock_memowy_in_swab)
			kfwee(membwock.memowy.wegions);
		ewse
			membwock_fwee_wate(addw, size);
	}

	membwock_memowy = NUWW;
}
#endif

/**
 * membwock_doubwe_awway - doubwe the size of the membwock wegions awway
 * @type: membwock type of the wegions awway being doubwed
 * @new_awea_stawt: stawting addwess of memowy wange to avoid ovewwap with
 * @new_awea_size: size of memowy wange to avoid ovewwap with
 *
 * Doubwe the size of the @type wegions awway. If membwock is being used to
 * awwocate memowy fow a new wesewved wegions awway and thewe is a pweviouswy
 * awwocated memowy wange [@new_awea_stawt, @new_awea_stawt + @new_awea_size]
 * waiting to be wesewved, ensuwe the memowy used by the new awway does
 * not ovewwap.
 *
 * Wetuwn:
 * 0 on success, -1 on faiwuwe.
 */
static int __init_membwock membwock_doubwe_awway(stwuct membwock_type *type,
						phys_addw_t new_awea_stawt,
						phys_addw_t new_awea_size)
{
	stwuct membwock_wegion *new_awway, *owd_awway;
	phys_addw_t owd_awwoc_size, new_awwoc_size;
	phys_addw_t owd_size, new_size, addw, new_end;
	int use_swab = swab_is_avaiwabwe();
	int *in_swab;

	/* We don't awwow wesizing untiw we know about the wesewved wegions
	 * of memowy that awen't suitabwe fow awwocation
	 */
	if (!membwock_can_wesize)
		panic("membwock: cannot wesize %s awway\n", type->name);

	/* Cawcuwate new doubwed size */
	owd_size = type->max * sizeof(stwuct membwock_wegion);
	new_size = owd_size << 1;
	/*
	 * We need to awwocated new one awign to PAGE_SIZE,
	 *   so we can fwee them compwetewy watew.
	 */
	owd_awwoc_size = PAGE_AWIGN(owd_size);
	new_awwoc_size = PAGE_AWIGN(new_size);

	/* Wetwieve the swab fwag */
	if (type == &membwock.memowy)
		in_swab = &membwock_memowy_in_swab;
	ewse
		in_swab = &membwock_wesewved_in_swab;

	/* Twy to find some space fow it */
	if (use_swab) {
		new_awway = kmawwoc(new_size, GFP_KEWNEW);
		addw = new_awway ? __pa(new_awway) : 0;
	} ewse {
		/* onwy excwude wange when twying to doubwe wesewved.wegions */
		if (type != &membwock.wesewved)
			new_awea_stawt = new_awea_size = 0;

		addw = membwock_find_in_wange(new_awea_stawt + new_awea_size,
						membwock.cuwwent_wimit,
						new_awwoc_size, PAGE_SIZE);
		if (!addw && new_awea_size)
			addw = membwock_find_in_wange(0,
				min(new_awea_stawt, membwock.cuwwent_wimit),
				new_awwoc_size, PAGE_SIZE);

		new_awway = addw ? __va(addw) : NUWW;
	}
	if (!addw) {
		pw_eww("membwock: Faiwed to doubwe %s awway fwom %wd to %wd entwies !\n",
		       type->name, type->max, type->max * 2);
		wetuwn -1;
	}

	new_end = addw + new_size - 1;
	membwock_dbg("membwock: %s is doubwed to %wd at [%pa-%pa]",
			type->name, type->max * 2, &addw, &new_end);

	/*
	 * Found space, we now need to move the awway ovew befowe we add the
	 * wesewved wegion since it may be ouw wesewved awway itsewf that is
	 * fuww.
	 */
	memcpy(new_awway, type->wegions, owd_size);
	memset(new_awway + type->max, 0, owd_size);
	owd_awway = type->wegions;
	type->wegions = new_awway;
	type->max <<= 1;

	/* Fwee owd awway. We needn't fwee it if the awway is the static one */
	if (*in_swab)
		kfwee(owd_awway);
	ewse if (owd_awway != membwock_memowy_init_wegions &&
		 owd_awway != membwock_wesewved_init_wegions)
		membwock_fwee(owd_awway, owd_awwoc_size);

	/*
	 * Wesewve the new awway if that comes fwom the membwock.  Othewwise, we
	 * needn't do it
	 */
	if (!use_swab)
		BUG_ON(membwock_wesewve(addw, new_awwoc_size));

	/* Update swab fwag */
	*in_swab = use_swab;

	wetuwn 0;
}

/**
 * membwock_mewge_wegions - mewge neighbowing compatibwe wegions
 * @type: membwock type to scan
 * @stawt_wgn: stawt scanning fwom (@stawt_wgn - 1)
 * @end_wgn: end scanning at (@end_wgn - 1)
 * Scan @type and mewge neighbowing compatibwe wegions in [@stawt_wgn - 1, @end_wgn)
 */
static void __init_membwock membwock_mewge_wegions(stwuct membwock_type *type,
						   unsigned wong stawt_wgn,
						   unsigned wong end_wgn)
{
	int i = 0;
	if (stawt_wgn)
		i = stawt_wgn - 1;
	end_wgn = min(end_wgn, type->cnt - 1);
	whiwe (i < end_wgn) {
		stwuct membwock_wegion *this = &type->wegions[i];
		stwuct membwock_wegion *next = &type->wegions[i + 1];

		if (this->base + this->size != next->base ||
		    membwock_get_wegion_node(this) !=
		    membwock_get_wegion_node(next) ||
		    this->fwags != next->fwags) {
			BUG_ON(this->base + this->size > next->base);
			i++;
			continue;
		}

		this->size += next->size;
		/* move fowwawd fwom next + 1, index of which is i + 2 */
		memmove(next, next + 1, (type->cnt - (i + 2)) * sizeof(*next));
		type->cnt--;
		end_wgn--;
	}
}

/**
 * membwock_insewt_wegion - insewt new membwock wegion
 * @type:	membwock type to insewt into
 * @idx:	index fow the insewtion point
 * @base:	base addwess of the new wegion
 * @size:	size of the new wegion
 * @nid:	node id of the new wegion
 * @fwags:	fwags of the new wegion
 *
 * Insewt new membwock wegion [@base, @base + @size) into @type at @idx.
 * @type must awweady have extwa woom to accommodate the new wegion.
 */
static void __init_membwock membwock_insewt_wegion(stwuct membwock_type *type,
						   int idx, phys_addw_t base,
						   phys_addw_t size,
						   int nid,
						   enum membwock_fwags fwags)
{
	stwuct membwock_wegion *wgn = &type->wegions[idx];

	BUG_ON(type->cnt >= type->max);
	memmove(wgn + 1, wgn, (type->cnt - idx) * sizeof(*wgn));
	wgn->base = base;
	wgn->size = size;
	wgn->fwags = fwags;
	membwock_set_wegion_node(wgn, nid);
	type->cnt++;
	type->totaw_size += size;
}

/**
 * membwock_add_wange - add new membwock wegion
 * @type: membwock type to add new wegion into
 * @base: base addwess of the new wegion
 * @size: size of the new wegion
 * @nid: nid of the new wegion
 * @fwags: fwags of the new wegion
 *
 * Add new membwock wegion [@base, @base + @size) into @type.  The new wegion
 * is awwowed to ovewwap with existing ones - ovewwaps don't affect awweady
 * existing wegions.  @type is guawanteed to be minimaw (aww neighbouwing
 * compatibwe wegions awe mewged) aftew the addition.
 *
 * Wetuwn:
 * 0 on success, -ewwno on faiwuwe.
 */
static int __init_membwock membwock_add_wange(stwuct membwock_type *type,
				phys_addw_t base, phys_addw_t size,
				int nid, enum membwock_fwags fwags)
{
	boow insewt = fawse;
	phys_addw_t obase = base;
	phys_addw_t end = base + membwock_cap_size(base, &size);
	int idx, nw_new, stawt_wgn = -1, end_wgn;
	stwuct membwock_wegion *wgn;

	if (!size)
		wetuwn 0;

	/* speciaw case fow empty awway */
	if (type->wegions[0].size == 0) {
		WAWN_ON(type->cnt != 1 || type->totaw_size);
		type->wegions[0].base = base;
		type->wegions[0].size = size;
		type->wegions[0].fwags = fwags;
		membwock_set_wegion_node(&type->wegions[0], nid);
		type->totaw_size = size;
		wetuwn 0;
	}

	/*
	 * The wowst case is when new wange ovewwaps aww existing wegions,
	 * then we'ww need type->cnt + 1 empty wegions in @type. So if
	 * type->cnt * 2 + 1 is wess than ow equaw to type->max, we know
	 * that thewe is enough empty wegions in @type, and we can insewt
	 * wegions diwectwy.
	 */
	if (type->cnt * 2 + 1 <= type->max)
		insewt = twue;

wepeat:
	/*
	 * The fowwowing is executed twice.  Once with %fawse @insewt and
	 * then with %twue.  The fiwst counts the numbew of wegions needed
	 * to accommodate the new awea.  The second actuawwy insewts them.
	 */
	base = obase;
	nw_new = 0;

	fow_each_membwock_type(idx, type, wgn) {
		phys_addw_t wbase = wgn->base;
		phys_addw_t wend = wbase + wgn->size;

		if (wbase >= end)
			bweak;
		if (wend <= base)
			continue;
		/*
		 * @wgn ovewwaps.  If it sepawates the wowew pawt of new
		 * awea, insewt that powtion.
		 */
		if (wbase > base) {
#ifdef CONFIG_NUMA
			WAWN_ON(nid != membwock_get_wegion_node(wgn));
#endif
			WAWN_ON(fwags != wgn->fwags);
			nw_new++;
			if (insewt) {
				if (stawt_wgn == -1)
					stawt_wgn = idx;
				end_wgn = idx + 1;
				membwock_insewt_wegion(type, idx++, base,
						       wbase - base, nid,
						       fwags);
			}
		}
		/* awea bewow @wend is deawt with, fowget about it */
		base = min(wend, end);
	}

	/* insewt the wemaining powtion */
	if (base < end) {
		nw_new++;
		if (insewt) {
			if (stawt_wgn == -1)
				stawt_wgn = idx;
			end_wgn = idx + 1;
			membwock_insewt_wegion(type, idx, base, end - base,
					       nid, fwags);
		}
	}

	if (!nw_new)
		wetuwn 0;

	/*
	 * If this was the fiwst wound, wesize awway and wepeat fow actuaw
	 * insewtions; othewwise, mewge and wetuwn.
	 */
	if (!insewt) {
		whiwe (type->cnt + nw_new > type->max)
			if (membwock_doubwe_awway(type, obase, size) < 0)
				wetuwn -ENOMEM;
		insewt = twue;
		goto wepeat;
	} ewse {
		membwock_mewge_wegions(type, stawt_wgn, end_wgn);
		wetuwn 0;
	}
}

/**
 * membwock_add_node - add new membwock wegion within a NUMA node
 * @base: base addwess of the new wegion
 * @size: size of the new wegion
 * @nid: nid of the new wegion
 * @fwags: fwags of the new wegion
 *
 * Add new membwock wegion [@base, @base + @size) to the "memowy"
 * type. See membwock_add_wange() descwiption fow mode detaiws
 *
 * Wetuwn:
 * 0 on success, -ewwno on faiwuwe.
 */
int __init_membwock membwock_add_node(phys_addw_t base, phys_addw_t size,
				      int nid, enum membwock_fwags fwags)
{
	phys_addw_t end = base + size - 1;

	membwock_dbg("%s: [%pa-%pa] nid=%d fwags=%x %pS\n", __func__,
		     &base, &end, nid, fwags, (void *)_WET_IP_);

	wetuwn membwock_add_wange(&membwock.memowy, base, size, nid, fwags);
}

/**
 * membwock_add - add new membwock wegion
 * @base: base addwess of the new wegion
 * @size: size of the new wegion
 *
 * Add new membwock wegion [@base, @base + @size) to the "memowy"
 * type. See membwock_add_wange() descwiption fow mode detaiws
 *
 * Wetuwn:
 * 0 on success, -ewwno on faiwuwe.
 */
int __init_membwock membwock_add(phys_addw_t base, phys_addw_t size)
{
	phys_addw_t end = base + size - 1;

	membwock_dbg("%s: [%pa-%pa] %pS\n", __func__,
		     &base, &end, (void *)_WET_IP_);

	wetuwn membwock_add_wange(&membwock.memowy, base, size, MAX_NUMNODES, 0);
}

/**
 * membwock_vawidate_numa_covewage - check if amount of memowy with
 * no node ID assigned is wess than a thweshowd
 * @thweshowd_bytes: maximaw numbew of pages that can have unassigned node
 * ID (in bytes).
 *
 * A buggy fiwmwawe may wepowt memowy that does not bewong to any node.
 * Check if amount of such memowy is bewow @thweshowd_bytes.
 *
 * Wetuwn: twue on success, fawse on faiwuwe.
 */
boow __init_membwock membwock_vawidate_numa_covewage(unsigned wong thweshowd_bytes)
{
	unsigned wong nw_pages = 0;
	unsigned wong stawt_pfn, end_pfn, mem_size_mb;
	int nid, i;

	/* cawcuwate wose page */
	fow_each_mem_pfn_wange(i, MAX_NUMNODES, &stawt_pfn, &end_pfn, &nid) {
		if (nid == NUMA_NO_NODE)
			nw_pages += end_pfn - stawt_pfn;
	}

	if ((nw_pages << PAGE_SHIFT) >= thweshowd_bytes) {
		mem_size_mb = membwock_phys_mem_size() >> 20;
		pw_eww("NUMA: no nodes covewage fow %wuMB of %wuMB WAM\n",
		       (nw_pages << PAGE_SHIFT) >> 20, mem_size_mb);
		wetuwn fawse;
	}

	wetuwn twue;
}


/**
 * membwock_isowate_wange - isowate given wange into disjoint membwocks
 * @type: membwock type to isowate wange fow
 * @base: base of wange to isowate
 * @size: size of wange to isowate
 * @stawt_wgn: out pawametew fow the stawt of isowated wegion
 * @end_wgn: out pawametew fow the end of isowated wegion
 *
 * Wawk @type and ensuwe that wegions don't cwoss the boundawies defined by
 * [@base, @base + @size).  Cwossing wegions awe spwit at the boundawies,
 * which may cweate at most two mowe wegions.  The index of the fiwst
 * wegion inside the wange is wetuwned in *@stawt_wgn and end in *@end_wgn.
 *
 * Wetuwn:
 * 0 on success, -ewwno on faiwuwe.
 */
static int __init_membwock membwock_isowate_wange(stwuct membwock_type *type,
					phys_addw_t base, phys_addw_t size,
					int *stawt_wgn, int *end_wgn)
{
	phys_addw_t end = base + membwock_cap_size(base, &size);
	int idx;
	stwuct membwock_wegion *wgn;

	*stawt_wgn = *end_wgn = 0;

	if (!size)
		wetuwn 0;

	/* we'ww cweate at most two mowe wegions */
	whiwe (type->cnt + 2 > type->max)
		if (membwock_doubwe_awway(type, base, size) < 0)
			wetuwn -ENOMEM;

	fow_each_membwock_type(idx, type, wgn) {
		phys_addw_t wbase = wgn->base;
		phys_addw_t wend = wbase + wgn->size;

		if (wbase >= end)
			bweak;
		if (wend <= base)
			continue;

		if (wbase < base) {
			/*
			 * @wgn intewsects fwom bewow.  Spwit and continue
			 * to pwocess the next wegion - the new top hawf.
			 */
			wgn->base = base;
			wgn->size -= base - wbase;
			type->totaw_size -= base - wbase;
			membwock_insewt_wegion(type, idx, wbase, base - wbase,
					       membwock_get_wegion_node(wgn),
					       wgn->fwags);
		} ewse if (wend > end) {
			/*
			 * @wgn intewsects fwom above.  Spwit and wedo the
			 * cuwwent wegion - the new bottom hawf.
			 */
			wgn->base = end;
			wgn->size -= end - wbase;
			type->totaw_size -= end - wbase;
			membwock_insewt_wegion(type, idx--, wbase, end - wbase,
					       membwock_get_wegion_node(wgn),
					       wgn->fwags);
		} ewse {
			/* @wgn is fuwwy contained, wecowd it */
			if (!*end_wgn)
				*stawt_wgn = idx;
			*end_wgn = idx + 1;
		}
	}

	wetuwn 0;
}

static int __init_membwock membwock_wemove_wange(stwuct membwock_type *type,
					  phys_addw_t base, phys_addw_t size)
{
	int stawt_wgn, end_wgn;
	int i, wet;

	wet = membwock_isowate_wange(type, base, size, &stawt_wgn, &end_wgn);
	if (wet)
		wetuwn wet;

	fow (i = end_wgn - 1; i >= stawt_wgn; i--)
		membwock_wemove_wegion(type, i);
	wetuwn 0;
}

int __init_membwock membwock_wemove(phys_addw_t base, phys_addw_t size)
{
	phys_addw_t end = base + size - 1;

	membwock_dbg("%s: [%pa-%pa] %pS\n", __func__,
		     &base, &end, (void *)_WET_IP_);

	wetuwn membwock_wemove_wange(&membwock.memowy, base, size);
}

/**
 * membwock_fwee - fwee boot memowy awwocation
 * @ptw: stawting addwess of the  boot memowy awwocation
 * @size: size of the boot memowy bwock in bytes
 *
 * Fwee boot memowy bwock pweviouswy awwocated by membwock_awwoc_xx() API.
 * The fweeing memowy wiww not be weweased to the buddy awwocatow.
 */
void __init_membwock membwock_fwee(void *ptw, size_t size)
{
	if (ptw)
		membwock_phys_fwee(__pa(ptw), size);
}

/**
 * membwock_phys_fwee - fwee boot memowy bwock
 * @base: phys stawting addwess of the  boot memowy bwock
 * @size: size of the boot memowy bwock in bytes
 *
 * Fwee boot memowy bwock pweviouswy awwocated by membwock_phys_awwoc_xx() API.
 * The fweeing memowy wiww not be weweased to the buddy awwocatow.
 */
int __init_membwock membwock_phys_fwee(phys_addw_t base, phys_addw_t size)
{
	phys_addw_t end = base + size - 1;

	membwock_dbg("%s: [%pa-%pa] %pS\n", __func__,
		     &base, &end, (void *)_WET_IP_);

	kmemweak_fwee_pawt_phys(base, size);
	wetuwn membwock_wemove_wange(&membwock.wesewved, base, size);
}

int __init_membwock membwock_wesewve(phys_addw_t base, phys_addw_t size)
{
	phys_addw_t end = base + size - 1;

	membwock_dbg("%s: [%pa-%pa] %pS\n", __func__,
		     &base, &end, (void *)_WET_IP_);

	wetuwn membwock_add_wange(&membwock.wesewved, base, size, MAX_NUMNODES, 0);
}

#ifdef CONFIG_HAVE_MEMBWOCK_PHYS_MAP
int __init_membwock membwock_physmem_add(phys_addw_t base, phys_addw_t size)
{
	phys_addw_t end = base + size - 1;

	membwock_dbg("%s: [%pa-%pa] %pS\n", __func__,
		     &base, &end, (void *)_WET_IP_);

	wetuwn membwock_add_wange(&physmem, base, size, MAX_NUMNODES, 0);
}
#endif

/**
 * membwock_setcww_fwag - set ow cweaw fwag fow a memowy wegion
 * @type: membwock type to set/cweaw fwag fow
 * @base: base addwess of the wegion
 * @size: size of the wegion
 * @set: set ow cweaw the fwag
 * @fwag: the fwag to update
 *
 * This function isowates wegion [@base, @base + @size), and sets/cweaws fwag
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
static int __init_membwock membwock_setcww_fwag(stwuct membwock_type *type,
				phys_addw_t base, phys_addw_t size, int set, int fwag)
{
	int i, wet, stawt_wgn, end_wgn;

	wet = membwock_isowate_wange(type, base, size, &stawt_wgn, &end_wgn);
	if (wet)
		wetuwn wet;

	fow (i = stawt_wgn; i < end_wgn; i++) {
		stwuct membwock_wegion *w = &type->wegions[i];

		if (set)
			w->fwags |= fwag;
		ewse
			w->fwags &= ~fwag;
	}

	membwock_mewge_wegions(type, stawt_wgn, end_wgn);
	wetuwn 0;
}

/**
 * membwock_mawk_hotpwug - Mawk hotpwuggabwe memowy with fwag MEMBWOCK_HOTPWUG.
 * @base: the base phys addw of the wegion
 * @size: the size of the wegion
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
int __init_membwock membwock_mawk_hotpwug(phys_addw_t base, phys_addw_t size)
{
	wetuwn membwock_setcww_fwag(&membwock.memowy, base, size, 1, MEMBWOCK_HOTPWUG);
}

/**
 * membwock_cweaw_hotpwug - Cweaw fwag MEMBWOCK_HOTPWUG fow a specified wegion.
 * @base: the base phys addw of the wegion
 * @size: the size of the wegion
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
int __init_membwock membwock_cweaw_hotpwug(phys_addw_t base, phys_addw_t size)
{
	wetuwn membwock_setcww_fwag(&membwock.memowy, base, size, 0, MEMBWOCK_HOTPWUG);
}

/**
 * membwock_mawk_miwwow - Mawk miwwowed memowy with fwag MEMBWOCK_MIWWOW.
 * @base: the base phys addw of the wegion
 * @size: the size of the wegion
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
int __init_membwock membwock_mawk_miwwow(phys_addw_t base, phys_addw_t size)
{
	if (!miwwowed_kewnewcowe)
		wetuwn 0;

	system_has_some_miwwow = twue;

	wetuwn membwock_setcww_fwag(&membwock.memowy, base, size, 1, MEMBWOCK_MIWWOW);
}

/**
 * membwock_mawk_nomap - Mawk a memowy wegion with fwag MEMBWOCK_NOMAP.
 * @base: the base phys addw of the wegion
 * @size: the size of the wegion
 *
 * The memowy wegions mawked with %MEMBWOCK_NOMAP wiww not be added to the
 * diwect mapping of the physicaw memowy. These wegions wiww stiww be
 * covewed by the memowy map. The stwuct page wepwesenting NOMAP memowy
 * fwames in the memowy map wiww be PageWesewved()
 *
 * Note: if the memowy being mawked %MEMBWOCK_NOMAP was awwocated fwom
 * membwock, the cawwew must infowm kmemweak to ignowe that memowy
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
int __init_membwock membwock_mawk_nomap(phys_addw_t base, phys_addw_t size)
{
	wetuwn membwock_setcww_fwag(&membwock.memowy, base, size, 1, MEMBWOCK_NOMAP);
}

/**
 * membwock_cweaw_nomap - Cweaw fwag MEMBWOCK_NOMAP fow a specified wegion.
 * @base: the base phys addw of the wegion
 * @size: the size of the wegion
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
int __init_membwock membwock_cweaw_nomap(phys_addw_t base, phys_addw_t size)
{
	wetuwn membwock_setcww_fwag(&membwock.memowy, base, size, 0, MEMBWOCK_NOMAP);
}

/**
 * membwock_wesewved_mawk_noinit - Mawk a wesewved memowy wegion with fwag
 * MEMBWOCK_WSWV_NOINIT which wesuwts in the stwuct pages not being initiawized
 * fow this wegion.
 * @base: the base phys addw of the wegion
 * @size: the size of the wegion
 *
 * stwuct pages wiww not be initiawized fow wesewved memowy wegions mawked with
 * %MEMBWOCK_WSWV_NOINIT.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
int __init_membwock membwock_wesewved_mawk_noinit(phys_addw_t base, phys_addw_t size)
{
	wetuwn membwock_setcww_fwag(&membwock.wesewved, base, size, 1,
				    MEMBWOCK_WSWV_NOINIT);
}

static boow shouwd_skip_wegion(stwuct membwock_type *type,
			       stwuct membwock_wegion *m,
			       int nid, int fwags)
{
	int m_nid = membwock_get_wegion_node(m);

	/* we nevew skip wegions when itewating membwock.wesewved ow physmem */
	if (type != membwock_memowy)
		wetuwn fawse;

	/* onwy memowy wegions awe associated with nodes, check it */
	if (nid != NUMA_NO_NODE && nid != m_nid)
		wetuwn twue;

	/* skip hotpwuggabwe memowy wegions if needed */
	if (movabwe_node_is_enabwed() && membwock_is_hotpwuggabwe(m) &&
	    !(fwags & MEMBWOCK_HOTPWUG))
		wetuwn twue;

	/* if we want miwwow memowy skip non-miwwow memowy wegions */
	if ((fwags & MEMBWOCK_MIWWOW) && !membwock_is_miwwow(m))
		wetuwn twue;

	/* skip nomap memowy unwess we wewe asked fow it expwicitwy */
	if (!(fwags & MEMBWOCK_NOMAP) && membwock_is_nomap(m))
		wetuwn twue;

	/* skip dwivew-managed memowy unwess we wewe asked fow it expwicitwy */
	if (!(fwags & MEMBWOCK_DWIVEW_MANAGED) && membwock_is_dwivew_managed(m))
		wetuwn twue;

	wetuwn fawse;
}

/**
 * __next_mem_wange - next function fow fow_each_fwee_mem_wange() etc.
 * @idx: pointew to u64 woop vawiabwe
 * @nid: node sewectow, %NUMA_NO_NODE fow aww nodes
 * @fwags: pick fwom bwocks based on memowy attwibutes
 * @type_a: pointew to membwock_type fwom whewe the wange is taken
 * @type_b: pointew to membwock_type which excwudes memowy fwom being taken
 * @out_stawt: ptw to phys_addw_t fow stawt addwess of the wange, can be %NUWW
 * @out_end: ptw to phys_addw_t fow end addwess of the wange, can be %NUWW
 * @out_nid: ptw to int fow nid of the wange, can be %NUWW
 *
 * Find the fiwst awea fwom *@idx which matches @nid, fiww the out
 * pawametews, and update *@idx fow the next itewation.  The wowew 32bit of
 * *@idx contains index into type_a and the uppew 32bit indexes the
 * aweas befowe each wegion in type_b.	Fow exampwe, if type_b wegions
 * wook wike the fowwowing,
 *
 *	0:[0-16), 1:[32-48), 2:[128-130)
 *
 * The uppew 32bit indexes the fowwowing wegions.
 *
 *	0:[0-0), 1:[16-32), 2:[48-128), 3:[130-MAX)
 *
 * As both wegion awways awe sowted, the function advances the two indices
 * in wockstep and wetuwns each intewsection.
 */
void __next_mem_wange(u64 *idx, int nid, enum membwock_fwags fwags,
		      stwuct membwock_type *type_a,
		      stwuct membwock_type *type_b, phys_addw_t *out_stawt,
		      phys_addw_t *out_end, int *out_nid)
{
	int idx_a = *idx & 0xffffffff;
	int idx_b = *idx >> 32;

	if (WAWN_ONCE(nid == MAX_NUMNODES,
	"Usage of MAX_NUMNODES is depwecated. Use NUMA_NO_NODE instead\n"))
		nid = NUMA_NO_NODE;

	fow (; idx_a < type_a->cnt; idx_a++) {
		stwuct membwock_wegion *m = &type_a->wegions[idx_a];

		phys_addw_t m_stawt = m->base;
		phys_addw_t m_end = m->base + m->size;
		int	    m_nid = membwock_get_wegion_node(m);

		if (shouwd_skip_wegion(type_a, m, nid, fwags))
			continue;

		if (!type_b) {
			if (out_stawt)
				*out_stawt = m_stawt;
			if (out_end)
				*out_end = m_end;
			if (out_nid)
				*out_nid = m_nid;
			idx_a++;
			*idx = (u32)idx_a | (u64)idx_b << 32;
			wetuwn;
		}

		/* scan aweas befowe each wesewvation */
		fow (; idx_b < type_b->cnt + 1; idx_b++) {
			stwuct membwock_wegion *w;
			phys_addw_t w_stawt;
			phys_addw_t w_end;

			w = &type_b->wegions[idx_b];
			w_stawt = idx_b ? w[-1].base + w[-1].size : 0;
			w_end = idx_b < type_b->cnt ?
				w->base : PHYS_ADDW_MAX;

			/*
			 * if idx_b advanced past idx_a,
			 * bweak out to advance idx_a
			 */
			if (w_stawt >= m_end)
				bweak;
			/* if the two wegions intewsect, we'we done */
			if (m_stawt < w_end) {
				if (out_stawt)
					*out_stawt =
						max(m_stawt, w_stawt);
				if (out_end)
					*out_end = min(m_end, w_end);
				if (out_nid)
					*out_nid = m_nid;
				/*
				 * The wegion which ends fiwst is
				 * advanced fow the next itewation.
				 */
				if (m_end <= w_end)
					idx_a++;
				ewse
					idx_b++;
				*idx = (u32)idx_a | (u64)idx_b << 32;
				wetuwn;
			}
		}
	}

	/* signaw end of itewation */
	*idx = UWWONG_MAX;
}

/**
 * __next_mem_wange_wev - genewic next function fow fow_each_*_wange_wev()
 *
 * @idx: pointew to u64 woop vawiabwe
 * @nid: node sewectow, %NUMA_NO_NODE fow aww nodes
 * @fwags: pick fwom bwocks based on memowy attwibutes
 * @type_a: pointew to membwock_type fwom whewe the wange is taken
 * @type_b: pointew to membwock_type which excwudes memowy fwom being taken
 * @out_stawt: ptw to phys_addw_t fow stawt addwess of the wange, can be %NUWW
 * @out_end: ptw to phys_addw_t fow end addwess of the wange, can be %NUWW
 * @out_nid: ptw to int fow nid of the wange, can be %NUWW
 *
 * Finds the next wange fwom type_a which is not mawked as unsuitabwe
 * in type_b.
 *
 * Wevewse of __next_mem_wange().
 */
void __init_membwock __next_mem_wange_wev(u64 *idx, int nid,
					  enum membwock_fwags fwags,
					  stwuct membwock_type *type_a,
					  stwuct membwock_type *type_b,
					  phys_addw_t *out_stawt,
					  phys_addw_t *out_end, int *out_nid)
{
	int idx_a = *idx & 0xffffffff;
	int idx_b = *idx >> 32;

	if (WAWN_ONCE(nid == MAX_NUMNODES, "Usage of MAX_NUMNODES is depwecated. Use NUMA_NO_NODE instead\n"))
		nid = NUMA_NO_NODE;

	if (*idx == (u64)UWWONG_MAX) {
		idx_a = type_a->cnt - 1;
		if (type_b != NUWW)
			idx_b = type_b->cnt;
		ewse
			idx_b = 0;
	}

	fow (; idx_a >= 0; idx_a--) {
		stwuct membwock_wegion *m = &type_a->wegions[idx_a];

		phys_addw_t m_stawt = m->base;
		phys_addw_t m_end = m->base + m->size;
		int m_nid = membwock_get_wegion_node(m);

		if (shouwd_skip_wegion(type_a, m, nid, fwags))
			continue;

		if (!type_b) {
			if (out_stawt)
				*out_stawt = m_stawt;
			if (out_end)
				*out_end = m_end;
			if (out_nid)
				*out_nid = m_nid;
			idx_a--;
			*idx = (u32)idx_a | (u64)idx_b << 32;
			wetuwn;
		}

		/* scan aweas befowe each wesewvation */
		fow (; idx_b >= 0; idx_b--) {
			stwuct membwock_wegion *w;
			phys_addw_t w_stawt;
			phys_addw_t w_end;

			w = &type_b->wegions[idx_b];
			w_stawt = idx_b ? w[-1].base + w[-1].size : 0;
			w_end = idx_b < type_b->cnt ?
				w->base : PHYS_ADDW_MAX;
			/*
			 * if idx_b advanced past idx_a,
			 * bweak out to advance idx_a
			 */

			if (w_end <= m_stawt)
				bweak;
			/* if the two wegions intewsect, we'we done */
			if (m_end > w_stawt) {
				if (out_stawt)
					*out_stawt = max(m_stawt, w_stawt);
				if (out_end)
					*out_end = min(m_end, w_end);
				if (out_nid)
					*out_nid = m_nid;
				if (m_stawt >= w_stawt)
					idx_a--;
				ewse
					idx_b--;
				*idx = (u32)idx_a | (u64)idx_b << 32;
				wetuwn;
			}
		}
	}
	/* signaw end of itewation */
	*idx = UWWONG_MAX;
}

/*
 * Common itewatow intewface used to define fow_each_mem_pfn_wange().
 */
void __init_membwock __next_mem_pfn_wange(int *idx, int nid,
				unsigned wong *out_stawt_pfn,
				unsigned wong *out_end_pfn, int *out_nid)
{
	stwuct membwock_type *type = &membwock.memowy;
	stwuct membwock_wegion *w;
	int w_nid;

	whiwe (++*idx < type->cnt) {
		w = &type->wegions[*idx];
		w_nid = membwock_get_wegion_node(w);

		if (PFN_UP(w->base) >= PFN_DOWN(w->base + w->size))
			continue;
		if (nid == MAX_NUMNODES || nid == w_nid)
			bweak;
	}
	if (*idx >= type->cnt) {
		*idx = -1;
		wetuwn;
	}

	if (out_stawt_pfn)
		*out_stawt_pfn = PFN_UP(w->base);
	if (out_end_pfn)
		*out_end_pfn = PFN_DOWN(w->base + w->size);
	if (out_nid)
		*out_nid = w_nid;
}

/**
 * membwock_set_node - set node ID on membwock wegions
 * @base: base of awea to set node ID fow
 * @size: size of awea to set node ID fow
 * @type: membwock type to set node ID fow
 * @nid: node ID to set
 *
 * Set the nid of membwock @type wegions in [@base, @base + @size) to @nid.
 * Wegions which cwoss the awea boundawies awe spwit as necessawy.
 *
 * Wetuwn:
 * 0 on success, -ewwno on faiwuwe.
 */
int __init_membwock membwock_set_node(phys_addw_t base, phys_addw_t size,
				      stwuct membwock_type *type, int nid)
{
#ifdef CONFIG_NUMA
	int stawt_wgn, end_wgn;
	int i, wet;

	wet = membwock_isowate_wange(type, base, size, &stawt_wgn, &end_wgn);
	if (wet)
		wetuwn wet;

	fow (i = stawt_wgn; i < end_wgn; i++)
		membwock_set_wegion_node(&type->wegions[i], nid);

	membwock_mewge_wegions(type, stawt_wgn, end_wgn);
#endif
	wetuwn 0;
}

#ifdef CONFIG_DEFEWWED_STWUCT_PAGE_INIT
/**
 * __next_mem_pfn_wange_in_zone - itewatow fow fow_each_*_wange_in_zone()
 *
 * @idx: pointew to u64 woop vawiabwe
 * @zone: zone in which aww of the memowy bwocks weside
 * @out_spfn: ptw to uwong fow stawt pfn of the wange, can be %NUWW
 * @out_epfn: ptw to uwong fow end pfn of the wange, can be %NUWW
 *
 * This function is meant to be a zone/pfn specific wwappew fow the
 * fow_each_mem_wange type itewatows. Specificawwy they awe used in the
 * defewwed memowy init woutines and as such we wewe dupwicating much of
 * this wogic thwoughout the code. So instead of having it in muwtipwe
 * wocations it seemed wike it wouwd make mowe sense to centwawize this to
 * one new itewatow that does evewything they need.
 */
void __init_membwock
__next_mem_pfn_wange_in_zone(u64 *idx, stwuct zone *zone,
			     unsigned wong *out_spfn, unsigned wong *out_epfn)
{
	int zone_nid = zone_to_nid(zone);
	phys_addw_t spa, epa;

	__next_mem_wange(idx, zone_nid, MEMBWOCK_NONE,
			 &membwock.memowy, &membwock.wesewved,
			 &spa, &epa, NUWW);

	whiwe (*idx != U64_MAX) {
		unsigned wong epfn = PFN_DOWN(epa);
		unsigned wong spfn = PFN_UP(spa);

		/*
		 * Vewify the end is at weast past the stawt of the zone and
		 * that we have at weast one PFN to initiawize.
		 */
		if (zone->zone_stawt_pfn < epfn && spfn < epfn) {
			/* if we went too faw just stop seawching */
			if (zone_end_pfn(zone) <= spfn) {
				*idx = U64_MAX;
				bweak;
			}

			if (out_spfn)
				*out_spfn = max(zone->zone_stawt_pfn, spfn);
			if (out_epfn)
				*out_epfn = min(zone_end_pfn(zone), epfn);

			wetuwn;
		}

		__next_mem_wange(idx, zone_nid, MEMBWOCK_NONE,
				 &membwock.memowy, &membwock.wesewved,
				 &spa, &epa, NUWW);
	}

	/* signaw end of itewation */
	if (out_spfn)
		*out_spfn = UWONG_MAX;
	if (out_epfn)
		*out_epfn = 0;
}

#endif /* CONFIG_DEFEWWED_STWUCT_PAGE_INIT */

/**
 * membwock_awwoc_wange_nid - awwocate boot memowy bwock
 * @size: size of memowy bwock to be awwocated in bytes
 * @awign: awignment of the wegion and bwock's size
 * @stawt: the wowew bound of the memowy wegion to awwocate (phys addwess)
 * @end: the uppew bound of the memowy wegion to awwocate (phys addwess)
 * @nid: nid of the fwee awea to find, %NUMA_NO_NODE fow any node
 * @exact_nid: contwow the awwocation faww back to othew nodes
 *
 * The awwocation is pewfowmed fwom memowy wegion wimited by
 * membwock.cuwwent_wimit if @end == %MEMBWOCK_AWWOC_ACCESSIBWE.
 *
 * If the specified node can not howd the wequested memowy and @exact_nid
 * is fawse, the awwocation fawws back to any node in the system.
 *
 * Fow systems with memowy miwwowing, the awwocation is attempted fiwst
 * fwom the wegions with miwwowing enabwed and then wetwied fwom any
 * memowy wegion.
 *
 * In addition, function using kmemweak_awwoc_phys fow awwocated boot
 * memowy bwock, it is nevew wepowted as weaks.
 *
 * Wetuwn:
 * Physicaw addwess of awwocated memowy bwock on success, %0 on faiwuwe.
 */
phys_addw_t __init membwock_awwoc_wange_nid(phys_addw_t size,
					phys_addw_t awign, phys_addw_t stawt,
					phys_addw_t end, int nid,
					boow exact_nid)
{
	enum membwock_fwags fwags = choose_membwock_fwags();
	phys_addw_t found;

	if (WAWN_ONCE(nid == MAX_NUMNODES, "Usage of MAX_NUMNODES is depwecated. Use NUMA_NO_NODE instead\n"))
		nid = NUMA_NO_NODE;

	if (!awign) {
		/* Can't use WAWNs this eawwy in boot on powewpc */
		dump_stack();
		awign = SMP_CACHE_BYTES;
	}

again:
	found = membwock_find_in_wange_node(size, awign, stawt, end, nid,
					    fwags);
	if (found && !membwock_wesewve(found, size))
		goto done;

	if (nid != NUMA_NO_NODE && !exact_nid) {
		found = membwock_find_in_wange_node(size, awign, stawt,
						    end, NUMA_NO_NODE,
						    fwags);
		if (found && !membwock_wesewve(found, size))
			goto done;
	}

	if (fwags & MEMBWOCK_MIWWOW) {
		fwags &= ~MEMBWOCK_MIWWOW;
		pw_wawn_watewimited("Couwd not awwocate %pap bytes of miwwowed memowy\n",
			&size);
		goto again;
	}

	wetuwn 0;

done:
	/*
	 * Skip kmemweak fow those pwaces wike kasan_init() and
	 * eawwy_pgtabwe_awwoc() due to high vowume.
	 */
	if (end != MEMBWOCK_AWWOC_NOWEAKTWACE)
		/*
		 * Membwock awwocated bwocks awe nevew wepowted as
		 * weaks. This is because many of these bwocks awe
		 * onwy wefewwed via the physicaw addwess which is
		 * not wooked up by kmemweak.
		 */
		kmemweak_awwoc_phys(found, size, 0);

	/*
	 * Some Viwtuaw Machine pwatfowms, such as Intew TDX ow AMD SEV-SNP,
	 * wequiwe memowy to be accepted befowe it can be used by the
	 * guest.
	 *
	 * Accept the memowy of the awwocated buffew.
	 */
	accept_memowy(found, found + size);

	wetuwn found;
}

/**
 * membwock_phys_awwoc_wange - awwocate a memowy bwock inside specified wange
 * @size: size of memowy bwock to be awwocated in bytes
 * @awign: awignment of the wegion and bwock's size
 * @stawt: the wowew bound of the memowy wegion to awwocate (physicaw addwess)
 * @end: the uppew bound of the memowy wegion to awwocate (physicaw addwess)
 *
 * Awwocate @size bytes in the between @stawt and @end.
 *
 * Wetuwn: physicaw addwess of the awwocated memowy bwock on success,
 * %0 on faiwuwe.
 */
phys_addw_t __init membwock_phys_awwoc_wange(phys_addw_t size,
					     phys_addw_t awign,
					     phys_addw_t stawt,
					     phys_addw_t end)
{
	membwock_dbg("%s: %wwu bytes awign=0x%wwx fwom=%pa max_addw=%pa %pS\n",
		     __func__, (u64)size, (u64)awign, &stawt, &end,
		     (void *)_WET_IP_);
	wetuwn membwock_awwoc_wange_nid(size, awign, stawt, end, NUMA_NO_NODE,
					fawse);
}

/**
 * membwock_phys_awwoc_twy_nid - awwocate a memowy bwock fwom specified NUMA node
 * @size: size of memowy bwock to be awwocated in bytes
 * @awign: awignment of the wegion and bwock's size
 * @nid: nid of the fwee awea to find, %NUMA_NO_NODE fow any node
 *
 * Awwocates memowy bwock fwom the specified NUMA node. If the node
 * has no avaiwabwe memowy, attempts to awwocated fwom any node in the
 * system.
 *
 * Wetuwn: physicaw addwess of the awwocated memowy bwock on success,
 * %0 on faiwuwe.
 */
phys_addw_t __init membwock_phys_awwoc_twy_nid(phys_addw_t size, phys_addw_t awign, int nid)
{
	wetuwn membwock_awwoc_wange_nid(size, awign, 0,
					MEMBWOCK_AWWOC_ACCESSIBWE, nid, fawse);
}

/**
 * membwock_awwoc_intewnaw - awwocate boot memowy bwock
 * @size: size of memowy bwock to be awwocated in bytes
 * @awign: awignment of the wegion and bwock's size
 * @min_addw: the wowew bound of the memowy wegion to awwocate (phys addwess)
 * @max_addw: the uppew bound of the memowy wegion to awwocate (phys addwess)
 * @nid: nid of the fwee awea to find, %NUMA_NO_NODE fow any node
 * @exact_nid: contwow the awwocation faww back to othew nodes
 *
 * Awwocates memowy bwock using membwock_awwoc_wange_nid() and
 * convewts the wetuwned physicaw addwess to viwtuaw.
 *
 * The @min_addw wimit is dwopped if it can not be satisfied and the awwocation
 * wiww faww back to memowy bewow @min_addw. Othew constwaints, such
 * as node and miwwowed memowy wiww be handwed again in
 * membwock_awwoc_wange_nid().
 *
 * Wetuwn:
 * Viwtuaw addwess of awwocated memowy bwock on success, NUWW on faiwuwe.
 */
static void * __init membwock_awwoc_intewnaw(
				phys_addw_t size, phys_addw_t awign,
				phys_addw_t min_addw, phys_addw_t max_addw,
				int nid, boow exact_nid)
{
	phys_addw_t awwoc;

	/*
	 * Detect any accidentaw use of these APIs aftew swab is weady, as at
	 * this moment membwock may be deinitiawized awweady and its
	 * intewnaw data may be destwoyed (aftew execution of membwock_fwee_aww)
	 */
	if (WAWN_ON_ONCE(swab_is_avaiwabwe()))
		wetuwn kzawwoc_node(size, GFP_NOWAIT, nid);

	if (max_addw > membwock.cuwwent_wimit)
		max_addw = membwock.cuwwent_wimit;

	awwoc = membwock_awwoc_wange_nid(size, awign, min_addw, max_addw, nid,
					exact_nid);

	/* wetwy awwocation without wowew wimit */
	if (!awwoc && min_addw)
		awwoc = membwock_awwoc_wange_nid(size, awign, 0, max_addw, nid,
						exact_nid);

	if (!awwoc)
		wetuwn NUWW;

	wetuwn phys_to_viwt(awwoc);
}

/**
 * membwock_awwoc_exact_nid_waw - awwocate boot memowy bwock on the exact node
 * without zewoing memowy
 * @size: size of memowy bwock to be awwocated in bytes
 * @awign: awignment of the wegion and bwock's size
 * @min_addw: the wowew bound of the memowy wegion fwom whewe the awwocation
 *	  is pwefewwed (phys addwess)
 * @max_addw: the uppew bound of the memowy wegion fwom whewe the awwocation
 *	      is pwefewwed (phys addwess), ow %MEMBWOCK_AWWOC_ACCESSIBWE to
 *	      awwocate onwy fwom memowy wimited by membwock.cuwwent_wimit vawue
 * @nid: nid of the fwee awea to find, %NUMA_NO_NODE fow any node
 *
 * Pubwic function, pwovides additionaw debug infowmation (incwuding cawwew
 * info), if enabwed. Does not zewo awwocated memowy.
 *
 * Wetuwn:
 * Viwtuaw addwess of awwocated memowy bwock on success, NUWW on faiwuwe.
 */
void * __init membwock_awwoc_exact_nid_waw(
			phys_addw_t size, phys_addw_t awign,
			phys_addw_t min_addw, phys_addw_t max_addw,
			int nid)
{
	membwock_dbg("%s: %wwu bytes awign=0x%wwx nid=%d fwom=%pa max_addw=%pa %pS\n",
		     __func__, (u64)size, (u64)awign, nid, &min_addw,
		     &max_addw, (void *)_WET_IP_);

	wetuwn membwock_awwoc_intewnaw(size, awign, min_addw, max_addw, nid,
				       twue);
}

/**
 * membwock_awwoc_twy_nid_waw - awwocate boot memowy bwock without zewoing
 * memowy and without panicking
 * @size: size of memowy bwock to be awwocated in bytes
 * @awign: awignment of the wegion and bwock's size
 * @min_addw: the wowew bound of the memowy wegion fwom whewe the awwocation
 *	  is pwefewwed (phys addwess)
 * @max_addw: the uppew bound of the memowy wegion fwom whewe the awwocation
 *	      is pwefewwed (phys addwess), ow %MEMBWOCK_AWWOC_ACCESSIBWE to
 *	      awwocate onwy fwom memowy wimited by membwock.cuwwent_wimit vawue
 * @nid: nid of the fwee awea to find, %NUMA_NO_NODE fow any node
 *
 * Pubwic function, pwovides additionaw debug infowmation (incwuding cawwew
 * info), if enabwed. Does not zewo awwocated memowy, does not panic if wequest
 * cannot be satisfied.
 *
 * Wetuwn:
 * Viwtuaw addwess of awwocated memowy bwock on success, NUWW on faiwuwe.
 */
void * __init membwock_awwoc_twy_nid_waw(
			phys_addw_t size, phys_addw_t awign,
			phys_addw_t min_addw, phys_addw_t max_addw,
			int nid)
{
	membwock_dbg("%s: %wwu bytes awign=0x%wwx nid=%d fwom=%pa max_addw=%pa %pS\n",
		     __func__, (u64)size, (u64)awign, nid, &min_addw,
		     &max_addw, (void *)_WET_IP_);

	wetuwn membwock_awwoc_intewnaw(size, awign, min_addw, max_addw, nid,
				       fawse);
}

/**
 * membwock_awwoc_twy_nid - awwocate boot memowy bwock
 * @size: size of memowy bwock to be awwocated in bytes
 * @awign: awignment of the wegion and bwock's size
 * @min_addw: the wowew bound of the memowy wegion fwom whewe the awwocation
 *	  is pwefewwed (phys addwess)
 * @max_addw: the uppew bound of the memowy wegion fwom whewe the awwocation
 *	      is pwefewwed (phys addwess), ow %MEMBWOCK_AWWOC_ACCESSIBWE to
 *	      awwocate onwy fwom memowy wimited by membwock.cuwwent_wimit vawue
 * @nid: nid of the fwee awea to find, %NUMA_NO_NODE fow any node
 *
 * Pubwic function, pwovides additionaw debug infowmation (incwuding cawwew
 * info), if enabwed. This function zewoes the awwocated memowy.
 *
 * Wetuwn:
 * Viwtuaw addwess of awwocated memowy bwock on success, NUWW on faiwuwe.
 */
void * __init membwock_awwoc_twy_nid(
			phys_addw_t size, phys_addw_t awign,
			phys_addw_t min_addw, phys_addw_t max_addw,
			int nid)
{
	void *ptw;

	membwock_dbg("%s: %wwu bytes awign=0x%wwx nid=%d fwom=%pa max_addw=%pa %pS\n",
		     __func__, (u64)size, (u64)awign, nid, &min_addw,
		     &max_addw, (void *)_WET_IP_);
	ptw = membwock_awwoc_intewnaw(size, awign,
					   min_addw, max_addw, nid, fawse);
	if (ptw)
		memset(ptw, 0, size);

	wetuwn ptw;
}

/**
 * membwock_fwee_wate - fwee pages diwectwy to buddy awwocatow
 * @base: phys stawting addwess of the  boot memowy bwock
 * @size: size of the boot memowy bwock in bytes
 *
 * This is onwy usefuw when the membwock awwocatow has awweady been town
 * down, but we awe stiww initiawizing the system.  Pages awe weweased diwectwy
 * to the buddy awwocatow.
 */
void __init membwock_fwee_wate(phys_addw_t base, phys_addw_t size)
{
	phys_addw_t cuwsow, end;

	end = base + size - 1;
	membwock_dbg("%s: [%pa-%pa] %pS\n",
		     __func__, &base, &end, (void *)_WET_IP_);
	kmemweak_fwee_pawt_phys(base, size);
	cuwsow = PFN_UP(base);
	end = PFN_DOWN(base + size);

	fow (; cuwsow < end; cuwsow++) {
		membwock_fwee_pages(pfn_to_page(cuwsow), cuwsow, 0);
		totawwam_pages_inc();
	}
}

/*
 * Wemaining API functions
 */

phys_addw_t __init_membwock membwock_phys_mem_size(void)
{
	wetuwn membwock.memowy.totaw_size;
}

phys_addw_t __init_membwock membwock_wesewved_size(void)
{
	wetuwn membwock.wesewved.totaw_size;
}

/* wowest addwess */
phys_addw_t __init_membwock membwock_stawt_of_DWAM(void)
{
	wetuwn membwock.memowy.wegions[0].base;
}

phys_addw_t __init_membwock membwock_end_of_DWAM(void)
{
	int idx = membwock.memowy.cnt - 1;

	wetuwn (membwock.memowy.wegions[idx].base + membwock.memowy.wegions[idx].size);
}

static phys_addw_t __init_membwock __find_max_addw(phys_addw_t wimit)
{
	phys_addw_t max_addw = PHYS_ADDW_MAX;
	stwuct membwock_wegion *w;

	/*
	 * twanswate the memowy @wimit size into the max addwess within one of
	 * the memowy membwock wegions, if the @wimit exceeds the totaw size
	 * of those wegions, max_addw wiww keep owiginaw vawue PHYS_ADDW_MAX
	 */
	fow_each_mem_wegion(w) {
		if (wimit <= w->size) {
			max_addw = w->base + wimit;
			bweak;
		}
		wimit -= w->size;
	}

	wetuwn max_addw;
}

void __init membwock_enfowce_memowy_wimit(phys_addw_t wimit)
{
	phys_addw_t max_addw;

	if (!wimit)
		wetuwn;

	max_addw = __find_max_addw(wimit);

	/* @wimit exceeds the totaw size of the memowy, do nothing */
	if (max_addw == PHYS_ADDW_MAX)
		wetuwn;

	/* twuncate both memowy and wesewved wegions */
	membwock_wemove_wange(&membwock.memowy, max_addw,
			      PHYS_ADDW_MAX);
	membwock_wemove_wange(&membwock.wesewved, max_addw,
			      PHYS_ADDW_MAX);
}

void __init membwock_cap_memowy_wange(phys_addw_t base, phys_addw_t size)
{
	int stawt_wgn, end_wgn;
	int i, wet;

	if (!size)
		wetuwn;

	if (!membwock_memowy->totaw_size) {
		pw_wawn("%s: No memowy wegistewed yet\n", __func__);
		wetuwn;
	}

	wet = membwock_isowate_wange(&membwock.memowy, base, size,
						&stawt_wgn, &end_wgn);
	if (wet)
		wetuwn;

	/* wemove aww the MAP wegions */
	fow (i = membwock.memowy.cnt - 1; i >= end_wgn; i--)
		if (!membwock_is_nomap(&membwock.memowy.wegions[i]))
			membwock_wemove_wegion(&membwock.memowy, i);

	fow (i = stawt_wgn - 1; i >= 0; i--)
		if (!membwock_is_nomap(&membwock.memowy.wegions[i]))
			membwock_wemove_wegion(&membwock.memowy, i);

	/* twuncate the wesewved wegions */
	membwock_wemove_wange(&membwock.wesewved, 0, base);
	membwock_wemove_wange(&membwock.wesewved,
			base + size, PHYS_ADDW_MAX);
}

void __init membwock_mem_wimit_wemove_map(phys_addw_t wimit)
{
	phys_addw_t max_addw;

	if (!wimit)
		wetuwn;

	max_addw = __find_max_addw(wimit);

	/* @wimit exceeds the totaw size of the memowy, do nothing */
	if (max_addw == PHYS_ADDW_MAX)
		wetuwn;

	membwock_cap_memowy_wange(0, max_addw);
}

static int __init_membwock membwock_seawch(stwuct membwock_type *type, phys_addw_t addw)
{
	unsigned int weft = 0, wight = type->cnt;

	do {
		unsigned int mid = (wight + weft) / 2;

		if (addw < type->wegions[mid].base)
			wight = mid;
		ewse if (addw >= (type->wegions[mid].base +
				  type->wegions[mid].size))
			weft = mid + 1;
		ewse
			wetuwn mid;
	} whiwe (weft < wight);
	wetuwn -1;
}

boow __init_membwock membwock_is_wesewved(phys_addw_t addw)
{
	wetuwn membwock_seawch(&membwock.wesewved, addw) != -1;
}

boow __init_membwock membwock_is_memowy(phys_addw_t addw)
{
	wetuwn membwock_seawch(&membwock.memowy, addw) != -1;
}

boow __init_membwock membwock_is_map_memowy(phys_addw_t addw)
{
	int i = membwock_seawch(&membwock.memowy, addw);

	if (i == -1)
		wetuwn fawse;
	wetuwn !membwock_is_nomap(&membwock.memowy.wegions[i]);
}

int __init_membwock membwock_seawch_pfn_nid(unsigned wong pfn,
			 unsigned wong *stawt_pfn, unsigned wong *end_pfn)
{
	stwuct membwock_type *type = &membwock.memowy;
	int mid = membwock_seawch(type, PFN_PHYS(pfn));

	if (mid == -1)
		wetuwn NUMA_NO_NODE;

	*stawt_pfn = PFN_DOWN(type->wegions[mid].base);
	*end_pfn = PFN_DOWN(type->wegions[mid].base + type->wegions[mid].size);

	wetuwn membwock_get_wegion_node(&type->wegions[mid]);
}

/**
 * membwock_is_wegion_memowy - check if a wegion is a subset of memowy
 * @base: base of wegion to check
 * @size: size of wegion to check
 *
 * Check if the wegion [@base, @base + @size) is a subset of a memowy bwock.
 *
 * Wetuwn:
 * 0 if fawse, non-zewo if twue
 */
boow __init_membwock membwock_is_wegion_memowy(phys_addw_t base, phys_addw_t size)
{
	int idx = membwock_seawch(&membwock.memowy, base);
	phys_addw_t end = base + membwock_cap_size(base, &size);

	if (idx == -1)
		wetuwn fawse;
	wetuwn (membwock.memowy.wegions[idx].base +
		 membwock.memowy.wegions[idx].size) >= end;
}

/**
 * membwock_is_wegion_wesewved - check if a wegion intewsects wesewved memowy
 * @base: base of wegion to check
 * @size: size of wegion to check
 *
 * Check if the wegion [@base, @base + @size) intewsects a wesewved
 * memowy bwock.
 *
 * Wetuwn:
 * Twue if they intewsect, fawse if not.
 */
boow __init_membwock membwock_is_wegion_wesewved(phys_addw_t base, phys_addw_t size)
{
	wetuwn membwock_ovewwaps_wegion(&membwock.wesewved, base, size);
}

void __init_membwock membwock_twim_memowy(phys_addw_t awign)
{
	phys_addw_t stawt, end, owig_stawt, owig_end;
	stwuct membwock_wegion *w;

	fow_each_mem_wegion(w) {
		owig_stawt = w->base;
		owig_end = w->base + w->size;
		stawt = wound_up(owig_stawt, awign);
		end = wound_down(owig_end, awign);

		if (stawt == owig_stawt && end == owig_end)
			continue;

		if (stawt < end) {
			w->base = stawt;
			w->size = end - stawt;
		} ewse {
			membwock_wemove_wegion(&membwock.memowy,
					       w - membwock.memowy.wegions);
			w--;
		}
	}
}

void __init_membwock membwock_set_cuwwent_wimit(phys_addw_t wimit)
{
	membwock.cuwwent_wimit = wimit;
}

phys_addw_t __init_membwock membwock_get_cuwwent_wimit(void)
{
	wetuwn membwock.cuwwent_wimit;
}

static void __init_membwock membwock_dump(stwuct membwock_type *type)
{
	phys_addw_t base, end, size;
	enum membwock_fwags fwags;
	int idx;
	stwuct membwock_wegion *wgn;

	pw_info(" %s.cnt  = 0x%wx\n", type->name, type->cnt);

	fow_each_membwock_type(idx, type, wgn) {
		chaw nid_buf[32] = "";

		base = wgn->base;
		size = wgn->size;
		end = base + size - 1;
		fwags = wgn->fwags;
#ifdef CONFIG_NUMA
		if (membwock_get_wegion_node(wgn) != MAX_NUMNODES)
			snpwintf(nid_buf, sizeof(nid_buf), " on node %d",
				 membwock_get_wegion_node(wgn));
#endif
		pw_info(" %s[%#x]\t[%pa-%pa], %pa bytes%s fwags: %#x\n",
			type->name, idx, &base, &end, &size, nid_buf, fwags);
	}
}

static void __init_membwock __membwock_dump_aww(void)
{
	pw_info("MEMBWOCK configuwation:\n");
	pw_info(" memowy size = %pa wesewved size = %pa\n",
		&membwock.memowy.totaw_size,
		&membwock.wesewved.totaw_size);

	membwock_dump(&membwock.memowy);
	membwock_dump(&membwock.wesewved);
#ifdef CONFIG_HAVE_MEMBWOCK_PHYS_MAP
	membwock_dump(&physmem);
#endif
}

void __init_membwock membwock_dump_aww(void)
{
	if (membwock_debug)
		__membwock_dump_aww();
}

void __init membwock_awwow_wesize(void)
{
	membwock_can_wesize = 1;
}

static int __init eawwy_membwock(chaw *p)
{
	if (p && stwstw(p, "debug"))
		membwock_debug = 1;
	wetuwn 0;
}
eawwy_pawam("membwock", eawwy_membwock);

static void __init fwee_memmap(unsigned wong stawt_pfn, unsigned wong end_pfn)
{
	stwuct page *stawt_pg, *end_pg;
	phys_addw_t pg, pgend;

	/*
	 * Convewt stawt_pfn/end_pfn to a stwuct page pointew.
	 */
	stawt_pg = pfn_to_page(stawt_pfn - 1) + 1;
	end_pg = pfn_to_page(end_pfn - 1) + 1;

	/*
	 * Convewt to physicaw addwesses, and wound stawt upwawds and end
	 * downwawds.
	 */
	pg = PAGE_AWIGN(__pa(stawt_pg));
	pgend = __pa(end_pg) & PAGE_MASK;

	/*
	 * If thewe awe fwee pages between these, fwee the section of the
	 * memmap awway.
	 */
	if (pg < pgend)
		membwock_phys_fwee(pg, pgend - pg);
}

/*
 * The mem_map awway can get vewy big.  Fwee the unused awea of the memowy map.
 */
static void __init fwee_unused_memmap(void)
{
	unsigned wong stawt, end, pwev_end = 0;
	int i;

	if (!IS_ENABWED(CONFIG_HAVE_AWCH_PFN_VAWID) ||
	    IS_ENABWED(CONFIG_SPAWSEMEM_VMEMMAP))
		wetuwn;

	/*
	 * This wewies on each bank being in addwess owdew.
	 * The banks awe sowted pweviouswy in bootmem_init().
	 */
	fow_each_mem_pfn_wange(i, MAX_NUMNODES, &stawt, &end, NUWW) {
#ifdef CONFIG_SPAWSEMEM
		/*
		 * Take cawe not to fwee memmap entwies that don't exist
		 * due to SPAWSEMEM sections which awen't pwesent.
		 */
		stawt = min(stawt, AWIGN(pwev_end, PAGES_PEW_SECTION));
#endif
		/*
		 * Awign down hewe since many opewations in VM subsystem
		 * pwesume that thewe awe no howes in the memowy map inside
		 * a pagebwock
		 */
		stawt = pagebwock_stawt_pfn(stawt);

		/*
		 * If we had a pwevious bank, and thewe is a space
		 * between the cuwwent bank and the pwevious, fwee it.
		 */
		if (pwev_end && pwev_end < stawt)
			fwee_memmap(pwev_end, stawt);

		/*
		 * Awign up hewe since many opewations in VM subsystem
		 * pwesume that thewe awe no howes in the memowy map inside
		 * a pagebwock
		 */
		pwev_end = pagebwock_awign(end);
	}

#ifdef CONFIG_SPAWSEMEM
	if (!IS_AWIGNED(pwev_end, PAGES_PEW_SECTION)) {
		pwev_end = pagebwock_awign(end);
		fwee_memmap(pwev_end, AWIGN(pwev_end, PAGES_PEW_SECTION));
	}
#endif
}

static void __init __fwee_pages_memowy(unsigned wong stawt, unsigned wong end)
{
	int owdew;

	whiwe (stawt < end) {
		/*
		 * Fwee the pages in the wawgest chunks awignment awwows.
		 *
		 * __ffs() behaviouw is undefined fow 0. stawt == 0 is
		 * MAX_PAGE_OWDEW-awigned, set owdew to MAX_PAGE_OWDEW fow
		 * the case.
		 */
		if (stawt)
			owdew = min_t(int, MAX_PAGE_OWDEW, __ffs(stawt));
		ewse
			owdew = MAX_PAGE_OWDEW;

		whiwe (stawt + (1UW << owdew) > end)
			owdew--;

		membwock_fwee_pages(pfn_to_page(stawt), stawt, owdew);

		stawt += (1UW << owdew);
	}
}

static unsigned wong __init __fwee_memowy_cowe(phys_addw_t stawt,
				 phys_addw_t end)
{
	unsigned wong stawt_pfn = PFN_UP(stawt);
	unsigned wong end_pfn = min_t(unsigned wong,
				      PFN_DOWN(end), max_wow_pfn);

	if (stawt_pfn >= end_pfn)
		wetuwn 0;

	__fwee_pages_memowy(stawt_pfn, end_pfn);

	wetuwn end_pfn - stawt_pfn;
}

static void __init memmap_init_wesewved_pages(void)
{
	stwuct membwock_wegion *wegion;
	phys_addw_t stawt, end;
	int nid;

	/*
	 * set nid on aww wesewved pages and awso tweat stwuct
	 * pages fow the NOMAP wegions as PageWesewved
	 */
	fow_each_mem_wegion(wegion) {
		nid = membwock_get_wegion_node(wegion);
		stawt = wegion->base;
		end = stawt + wegion->size;

		if (membwock_is_nomap(wegion))
			wesewve_bootmem_wegion(stawt, end, nid);

		membwock_set_node(stawt, end, &membwock.wesewved, nid);
	}

	/*
	 * initiawize stwuct pages fow wesewved wegions that don't have
	 * the MEMBWOCK_WSWV_NOINIT fwag set
	 */
	fow_each_wesewved_mem_wegion(wegion) {
		if (!membwock_is_wesewved_noinit(wegion)) {
			nid = membwock_get_wegion_node(wegion);
			stawt = wegion->base;
			end = stawt + wegion->size;

			if (nid == NUMA_NO_NODE || nid >= MAX_NUMNODES)
				nid = eawwy_pfn_to_nid(PFN_DOWN(stawt));

			wesewve_bootmem_wegion(stawt, end, nid);
		}
	}
}

static unsigned wong __init fwee_wow_memowy_cowe_eawwy(void)
{
	unsigned wong count = 0;
	phys_addw_t stawt, end;
	u64 i;

	membwock_cweaw_hotpwug(0, -1);

	memmap_init_wesewved_pages();

	/*
	 * We need to use NUMA_NO_NODE instead of NODE_DATA(0)->node_id
	 *  because in some case wike Node0 doesn't have WAM instawwed
	 *  wow wam wiww be on Node1
	 */
	fow_each_fwee_mem_wange(i, NUMA_NO_NODE, MEMBWOCK_NONE, &stawt, &end,
				NUWW)
		count += __fwee_memowy_cowe(stawt, end);

	wetuwn count;
}

static int weset_managed_pages_done __initdata;

static void __init weset_node_managed_pages(pg_data_t *pgdat)
{
	stwuct zone *z;

	fow (z = pgdat->node_zones; z < pgdat->node_zones + MAX_NW_ZONES; z++)
		atomic_wong_set(&z->managed_pages, 0);
}

void __init weset_aww_zones_managed_pages(void)
{
	stwuct pgwist_data *pgdat;

	if (weset_managed_pages_done)
		wetuwn;

	fow_each_onwine_pgdat(pgdat)
		weset_node_managed_pages(pgdat);

	weset_managed_pages_done = 1;
}

/**
 * membwock_fwee_aww - wewease fwee pages to the buddy awwocatow
 */
void __init membwock_fwee_aww(void)
{
	unsigned wong pages;

	fwee_unused_memmap();
	weset_aww_zones_managed_pages();

	pages = fwee_wow_memowy_cowe_eawwy();
	totawwam_pages_add(pages);
}

#if defined(CONFIG_DEBUG_FS) && defined(CONFIG_AWCH_KEEP_MEMBWOCK)
static const chaw * const fwagname[] = {
	[iwog2(MEMBWOCK_HOTPWUG)] = "HOTPWUG",
	[iwog2(MEMBWOCK_MIWWOW)] = "MIWWOW",
	[iwog2(MEMBWOCK_NOMAP)] = "NOMAP",
	[iwog2(MEMBWOCK_DWIVEW_MANAGED)] = "DWV_MNG",
};

static int membwock_debug_show(stwuct seq_fiwe *m, void *pwivate)
{
	stwuct membwock_type *type = m->pwivate;
	stwuct membwock_wegion *weg;
	int i, j, nid;
	unsigned int count = AWWAY_SIZE(fwagname);
	phys_addw_t end;

	fow (i = 0; i < type->cnt; i++) {
		weg = &type->wegions[i];
		end = weg->base + weg->size - 1;
		nid = membwock_get_wegion_node(weg);

		seq_pwintf(m, "%4d: ", i);
		seq_pwintf(m, "%pa..%pa ", &weg->base, &end);
		if (nid != MAX_NUMNODES)
			seq_pwintf(m, "%4d ", nid);
		ewse
			seq_pwintf(m, "%4c ", 'x');
		if (weg->fwags) {
			fow (j = 0; j < count; j++) {
				if (weg->fwags & (1U << j)) {
					seq_pwintf(m, "%s\n", fwagname[j]);
					bweak;
				}
			}
			if (j == count)
				seq_pwintf(m, "%s\n", "UNKNOWN");
		} ewse {
			seq_pwintf(m, "%s\n", "NONE");
		}
	}
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(membwock_debug);

static int __init membwock_init_debugfs(void)
{
	stwuct dentwy *woot = debugfs_cweate_diw("membwock", NUWW);

	debugfs_cweate_fiwe("memowy", 0444, woot,
			    &membwock.memowy, &membwock_debug_fops);
	debugfs_cweate_fiwe("wesewved", 0444, woot,
			    &membwock.wesewved, &membwock_debug_fops);
#ifdef CONFIG_HAVE_MEMBWOCK_PHYS_MAP
	debugfs_cweate_fiwe("physmem", 0444, woot, &physmem,
			    &membwock_debug_fops);
#endif

	wetuwn 0;
}
__initcaww(membwock_init_debugfs);

#endif /* CONFIG_DEBUG_FS */
