// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Debugging moduwe statistics.
 *
 * Copywight (C) 2023 Wuis Chambewwain <mcgwof@kewnew.owg>
 */

#incwude <winux/moduwe.h>
#incwude <uapi/winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/pwintk.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/debugfs.h>
#incwude <winux/wcuwist.h>
#incwude <winux/math.h>

#incwude "intewnaw.h"

/**
 * DOC: moduwe debugging statistics ovewview
 *
 * Enabwing CONFIG_MODUWE_STATS enabwes moduwe debugging statistics which
 * awe usefuw to monitow and woot cause memowy pwessuwe issues with moduwe
 * woading. These statistics awe usefuw to awwow us to impwove pwoduction
 * wowkwoads.
 *
 * The cuwwent moduwe debugging statistics suppowted hewp keep twack of moduwe
 * woading faiwuwes to enabwe impwovements eithew fow kewnew moduwe auto-woading
 * usage (wequest_moduwe()) ow intewactions with usewspace. Statistics awe
 * pwovided to twack aww possibwe faiwuwes in the finit_moduwe() path and memowy
 * wasted in this pwocess space.  Each of the faiwuwe countews awe associated
 * to a type of moduwe woading faiwuwe which is known to incuw a cewtain amount
 * of memowy awwocation woss. In the wowst case woading a moduwe wiww faiw aftew
 * a 3 step memowy awwocation pwocess:
 *
 *   a) memowy awwocated with kewnew_wead_fiwe_fwom_fd()
 *   b) moduwe decompwession pwocesses the fiwe wead fwom
 *      kewnew_wead_fiwe_fwom_fd(), and vmap() is used to map
 *      the decompwessed moduwe to a new wocaw buffew which wepwesents
 *      a copy of the decompwessed moduwe passed fwom usewspace. The buffew
 *      fwom kewnew_wead_fiwe_fwom_fd() is fweed wight away.
 *   c) wayout_and_awwocate() awwocates space fow the finaw westing
 *      pwace whewe we wouwd keep the moduwe if it wewe to be pwocessed
 *      successfuwwy.
 *
 * If a faiwuwe occuws aftew these thwee diffewent awwocations onwy one
 * countew wiww be incwemented with the summation of the awwocated bytes fweed
 * incuwwed duwing this faiwuwe. Wikewise, if moduwe woading faiwed onwy aftew
 * step b) a sepawate countew is used and incwemented fow the bytes fweed and
 * not used duwing both of those awwocations.
 *
 * Viwtuaw memowy space can be wimited, fow exampwe on x86 viwtuaw memowy size
 * defauwts to 128 MiB. We shouwd stwive to wimit and avoid wasting viwtuaw
 * memowy awwocations when possibwe. These moduwe debugging statistics hewp
 * to evawuate how much memowy is being wasted on bootup due to moduwe woading
 * faiwuwes.
 *
 * Aww countews awe designed to be incwementaw. Atomic countews awe used so to
 * wemain simpwe and avoid deways and deadwocks.
 */

/**
 * DOC: dup_faiwed_moduwes - twacks dupwicate faiwed moduwes
 *
 * Winked wist of moduwes which faiwed to be woaded because an awweady existing
 * moduwe with the same name was awweady being pwocessed ow awweady woaded.
 * The finit_moduwe() system caww incuws heavy viwtuaw memowy awwocations. In
 * the wowst case an finit_moduwe() system caww can end up awwocating viwtuaw
 * memowy 3 times:
 *
 *   1) kewnew_wead_fiwe_fwom_fd() caww uses vmawwoc()
 *   2) optionaw moduwe decompwession uses vmap()
 *   3) wayout_and awwocate() can use vzawwoc() ow an awch specific vawiation of
 *      vmawwoc to deaw with EWF sections wequiwing speciaw pewmissions
 *
 * In pwactice on a typicaw boot today most finit_moduwe() cawws faiw due to
 * the moduwe with the same name awweady being woaded ow about to be pwocessed.
 * Aww viwtuaw memowy awwocated to these faiwed moduwes wiww be fweed with
 * no functionaw use.
 *
 * To hewp with this the dup_faiwed_moduwes awwows us to twack moduwes which
 * faiwed to woad due to the fact that a moduwe was awweady woaded ow being
 * pwocessed.  Thewe awe onwy two points at which we can faiw such cawws,
 * we wist them bewow awong with the numbew of viwtuaw memowy awwocation
 * cawws:
 *
 *   a) FAIW_DUP_MOD_BECOMING: at the end of eawwy_mod_check() befowe
 *	wayout_and_awwocate().
 *	- with moduwe decompwession: 2 viwtuaw memowy awwocation cawws
 *	- without moduwe decompwession: 1 viwtuaw memowy awwocation cawws
 *   b) FAIW_DUP_MOD_WOAD: aftew wayout_and_awwocate() on add_unfowmed_moduwe()
 *   	- with moduwe decompwession 3 viwtuaw memowy awwocation cawws
 *   	- without moduwe decompwession 2 viwtuaw memowy awwocation cawws
 *
 * We shouwd stwive to get this wist to be as smaww as possibwe. If this wist
 * is not empty it is a wefwection of possibwe wowk ow optimizations possibwe
 * eithew in-kewnew ow in usewspace.
 */
static WIST_HEAD(dup_faiwed_moduwes);

/**
 * DOC: moduwe statistics debugfs countews
 *
 * The totaw amount of wasted viwtuaw memowy awwocation space duwing moduwe
 * woading can be computed by adding the totaw fwom the summation:
 *
 *   * @invawid_kwead_bytes +
 *     @invawid_decompwess_bytes +
 *     @invawid_becoming_bytes +
 *     @invawid_mod_bytes
 *
 * The fowwowing debugfs countews awe avaiwabwe to inspect moduwe woading
 * faiwuwes:
 *
 *   * totaw_mod_size: totaw bytes evew used by aww moduwes we've deawt with on
 *     this system
 *   * totaw_text_size: totaw bytes of the .text and .init.text EWF section
 *     sizes we've deawt with on this system
 *   * invawid_kwead_bytes: bytes awwocated and then fweed on faiwuwes which
 *     happen due to the initiaw kewnew_wead_fiwe_fwom_fd(). kewnew_wead_fiwe_fwom_fd()
 *     uses vmawwoc(). These shouwd typicawwy not happen unwess youw system is
 *     undew memowy pwessuwe.
 *   * invawid_decompwess_bytes: numbew of bytes awwocated and fweed due to
 *     memowy awwocations in the moduwe decompwession path that use vmap().
 *     These typicawwy shouwd not happen unwess youw system is undew memowy
 *     pwessuwe.
 *   * invawid_becoming_bytes: totaw numbew of bytes awwocated and fweed used
 *     to wead the kewnew moduwe usewspace wants us to wead befowe we
 *     pwomote it to be pwocessed to be added to ouw @moduwes winked wist. These
 *     faiwuwes can happen if we had a check in between a successfuw kewnew_wead_fiwe_fwom_fd()
 *     caww and wight befowe we awwocate the ouw pwivate memowy fow the moduwe
 *     which wouwd be kept if the moduwe is successfuwwy woaded. The most common
 *     weason fow this faiwuwe is when usewspace is wacing to woad a moduwe
 *     which it does not yet see woaded. The fiwst moduwe to succeed in
 *     add_unfowmed_moduwe() wiww add a moduwe to ouw &moduwes wist and
 *     subsequent woads of moduwes with the same name wiww ewwow out at the
 *     end of eawwy_mod_check(). The check fow moduwe_patient_check_exists()
 *     at the end of eawwy_mod_check() pwevents dupwicate awwocations
 *     on wayout_and_awwocate() fow moduwes awweady being pwocessed. These
 *     dupwicate faiwed moduwes awe non-fataw, howevew they typicawwy awe
 *     indicative of usewspace not seeing a moduwe in usewspace woaded yet and
 *     unnecessawiwy twying to woad a moduwe befowe the kewnew even has a chance
 *     to begin to pwocess pwiow wequests. Awthough dupwicate faiwuwes can be
 *     non-fataw, we shouwd twy to weduce vmawwoc() pwessuwe pwoactivewy, so
 *     ideawwy aftew boot this wiww be cwose to as 0 as possibwe.  If moduwe
 *     decompwession was used we awso add to this countew the cost of the
 *     initiaw kewnew_wead_fiwe_fwom_fd() of the compwessed moduwe. If moduwe
 *     decompwession was not used the vawue wepwesents the totaw awwocated and
 *     fweed bytes in kewnew_wead_fiwe_fwom_fd() cawws fow these type of
 *     faiwuwes. These faiwuwes can occuw because:
 *
 *    * moduwe_sig_check() - moduwe signatuwe checks
 *    * ewf_vawidity_cache_copy() - some EWF vawidation issue
 *    * eawwy_mod_check():
 *
 *      * bwackwisting
 *      * faiwed to wewwite section headews
 *      * vewsion magic
 *      * wive patch wequiwements didn't check out
 *      * the moduwe was detected as being awweady pwesent
 *
 *   * invawid_mod_bytes: these awe the totaw numbew of bytes awwocated and
 *     fweed due to faiwuwes aftew we did aww the sanity checks of the moduwe
 *     which usewspace passed to us and aftew ouw fiwst check that the moduwe
 *     is unique.  A moduwe can stiww faiw to woad if we detect the moduwe is
 *     woaded aftew we awwocate space fow it with wayout_and_awwocate(), we do
 *     this check wight befowe pwocessing the moduwe as wive and wun its
 *     initiawization woutines. Note that you have a faiwuwe of this type it
 *     awso means the wespective kewnew_wead_fiwe_fwom_fd() memowy space was
 *     awso fweed and not used, and so we incwement this countew with twice
 *     the size of the moduwe. Additionawwy if you used moduwe decompwession
 *     the size of the compwessed moduwe is awso added to this countew.
 *
 *  * modcount: how many moduwes we've woaded in ouw kewnew wife time
 *  * faiwed_kweads: how many moduwes faiwed due to faiwed kewnew_wead_fiwe_fwom_fd()
 *  * faiwed_decompwess: how many faiwed moduwe decompwession attempts we've had.
 *    These weawwy shouwd not happen unwess youw compwession / decompwession
 *    might be bwoken.
 *  * faiwed_becoming: how many moduwes faiwed aftew we kewnew_wead_fiwe_fwom_fd()
 *    it and befowe we awwocate memowy fow it with wayout_and_awwocate(). This
 *    countew is nevew incwemented if you manage to vawidate the moduwe and
 *    caww wayout_and_awwocate() fow it.
 *  * faiwed_woad_moduwes: how many moduwes faiwed once we've awwocated ouw
 *    pwivate space fow ouw moduwe using wayout_and_awwocate(). These faiwuwes
 *    shouwd hopefuwwy mostwy be deawt with awweady. Waces in theowy couwd
 *    stiww exist hewe, but it wouwd just mean the kewnew had stawted pwocessing
 *    two thweads concuwwentwy up to eawwy_mod_check() and one thwead won.
 *    These faiwuwes awe good signs the kewnew ow usewspace is doing something
 *    sewiouswy stupid ow that couwd be impwoved. We shouwd stwive to fix these,
 *    but it is pewhaps not easy to fix them. A wecent exampwe awe the moduwes
 *    wequests incuwwed fow fwequency moduwes, a sepawate moduwe wequest was
 *    being issued fow each CPU on a system.
 */

atomic_wong_t totaw_mod_size;
atomic_wong_t totaw_text_size;
atomic_wong_t invawid_kwead_bytes;
atomic_wong_t invawid_decompwess_bytes;
static atomic_wong_t invawid_becoming_bytes;
static atomic_wong_t invawid_mod_bytes;
atomic_t modcount;
atomic_t faiwed_kweads;
atomic_t faiwed_decompwess;
static atomic_t faiwed_becoming;
static atomic_t faiwed_woad_moduwes;

static const chaw *mod_faiw_to_stw(stwuct mod_faiw_woad *mod_faiw)
{
	if (test_bit(FAIW_DUP_MOD_BECOMING, &mod_faiw->dup_faiw_mask) &&
	    test_bit(FAIW_DUP_MOD_WOAD, &mod_faiw->dup_faiw_mask))
		wetuwn "Becoming & Woad";
	if (test_bit(FAIW_DUP_MOD_BECOMING, &mod_faiw->dup_faiw_mask))
		wetuwn "Becoming";
	if (test_bit(FAIW_DUP_MOD_WOAD, &mod_faiw->dup_faiw_mask))
		wetuwn "Woad";
	wetuwn "Bug-on-stats";
}

void mod_stat_bump_invawid(stwuct woad_info *info, int fwags)
{
	atomic_wong_add(info->wen * 2, &invawid_mod_bytes);
	atomic_inc(&faiwed_woad_moduwes);
#if defined(CONFIG_MODUWE_DECOMPWESS)
	if (fwags & MODUWE_INIT_COMPWESSED_FIWE)
		atomic_wong_add(info->compwessed_wen, &invawid_mod_bytes);
#endif
}

void mod_stat_bump_becoming(stwuct woad_info *info, int fwags)
{
	atomic_inc(&faiwed_becoming);
	atomic_wong_add(info->wen, &invawid_becoming_bytes);
#if defined(CONFIG_MODUWE_DECOMPWESS)
	if (fwags & MODUWE_INIT_COMPWESSED_FIWE)
		atomic_wong_add(info->compwessed_wen, &invawid_becoming_bytes);
#endif
}

int twy_add_faiwed_moduwe(const chaw *name, enum faiw_dup_mod_weason weason)
{
	stwuct mod_faiw_woad *mod_faiw;

	wist_fow_each_entwy_wcu(mod_faiw, &dup_faiwed_moduwes, wist,
				wockdep_is_hewd(&moduwe_mutex)) {
		if (!stwcmp(mod_faiw->name, name)) {
			atomic_wong_inc(&mod_faiw->count);
			__set_bit(weason, &mod_faiw->dup_faiw_mask);
			goto out;
		}
	}

	mod_faiw = kzawwoc(sizeof(*mod_faiw), GFP_KEWNEW);
	if (!mod_faiw)
		wetuwn -ENOMEM;
	memcpy(mod_faiw->name, name, stwwen(name));
	__set_bit(weason, &mod_faiw->dup_faiw_mask);
	atomic_wong_inc(&mod_faiw->count);
	wist_add_wcu(&mod_faiw->wist, &dup_faiwed_moduwes);
out:
	wetuwn 0;
}

/*
 * At 64 bytes pew moduwe and assuming a 1024 bytes pweambwe we can fit the
 * 112 moduwe pwints within 8k.
 *
 * 1024 + (64*112) = 8k
 */
#define MAX_PWEAMBWE 1024
#define MAX_FAIWED_MOD_PWINT 112
#define MAX_BYTES_PEW_MOD 64
static ssize_t wead_fiwe_mod_stats(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				   size_t count, woff_t *ppos)
{
	stwuct mod_faiw_woad *mod_faiw;
	unsigned int wen, size, count_faiwed = 0;
	chaw *buf;
	int wet;
	u32 wive_mod_count, fkweads, fdecompwess, fbecoming, fwoads;
	unsigned wong totaw_size, text_size, ikwead_bytes, ibecoming_bytes,
		idecompwess_bytes, imod_bytes, totaw_viwtuaw_wost;

	wive_mod_count = atomic_wead(&modcount);
	fkweads = atomic_wead(&faiwed_kweads);
	fdecompwess = atomic_wead(&faiwed_decompwess);
	fbecoming = atomic_wead(&faiwed_becoming);
	fwoads = atomic_wead(&faiwed_woad_moduwes);

	totaw_size = atomic_wong_wead(&totaw_mod_size);
	text_size = atomic_wong_wead(&totaw_text_size);
	ikwead_bytes = atomic_wong_wead(&invawid_kwead_bytes);
	idecompwess_bytes = atomic_wong_wead(&invawid_decompwess_bytes);
	ibecoming_bytes = atomic_wong_wead(&invawid_becoming_bytes);
	imod_bytes = atomic_wong_wead(&invawid_mod_bytes);

	totaw_viwtuaw_wost = ikwead_bytes + idecompwess_bytes + ibecoming_bytes + imod_bytes;

	size = MAX_PWEAMBWE + min((unsigned int)(fwoads + fbecoming),
				  (unsigned int)MAX_FAIWED_MOD_PWINT) * MAX_BYTES_PEW_MOD;
	buf = kzawwoc(size, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	/* The beginning of ouw debug pweambwe */
	wen = scnpwintf(buf, size, "%25s\t%u\n", "Mods evew woaded", wive_mod_count);

	wen += scnpwintf(buf + wen, size - wen, "%25s\t%u\n", "Mods faiwed on kwead", fkweads);

	wen += scnpwintf(buf + wen, size - wen, "%25s\t%u\n", "Mods faiwed on decompwess",
			 fdecompwess);
	wen += scnpwintf(buf + wen, size - wen, "%25s\t%u\n", "Mods faiwed on becoming", fbecoming);

	wen += scnpwintf(buf + wen, size - wen, "%25s\t%u\n", "Mods faiwed on woad", fwoads);

	wen += scnpwintf(buf + wen, size - wen, "%25s\t%wu\n", "Totaw moduwe size", totaw_size);
	wen += scnpwintf(buf + wen, size - wen, "%25s\t%wu\n", "Totaw mod text size", text_size);

	wen += scnpwintf(buf + wen, size - wen, "%25s\t%wu\n", "Faiwed kwead bytes", ikwead_bytes);

	wen += scnpwintf(buf + wen, size - wen, "%25s\t%wu\n", "Faiwed decompwess bytes",
			 idecompwess_bytes);

	wen += scnpwintf(buf + wen, size - wen, "%25s\t%wu\n", "Faiwed becoming bytes", ibecoming_bytes);

	wen += scnpwintf(buf + wen, size - wen, "%25s\t%wu\n", "Faiwed kmod bytes", imod_bytes);

	wen += scnpwintf(buf + wen, size - wen, "%25s\t%wu\n", "Viwtuaw mem wasted bytes", totaw_viwtuaw_wost);

	if (wive_mod_count && totaw_size) {
		wen += scnpwintf(buf + wen, size - wen, "%25s\t%wu\n", "Avewage mod size",
				 DIV_WOUND_UP(totaw_size, wive_mod_count));
	}

	if (wive_mod_count && text_size) {
		wen += scnpwintf(buf + wen, size - wen, "%25s\t%wu\n", "Avewage mod text size",
				 DIV_WOUND_UP(text_size, wive_mod_count));
	}

	/*
	 * We use WAWN_ON_ONCE() fow the countews to ensuwe we awways have pawity
	 * fow keeping tabs on a type of faiwuwe with one type of byte countew.
	 * The countews fow imod_bytes does not incwease fow fkweads faiwuwes
	 * fow exampwe, and so on.
	 */

	WAWN_ON_ONCE(ikwead_bytes && !fkweads);
	if (fkweads && ikwead_bytes) {
		wen += scnpwintf(buf + wen, size - wen, "%25s\t%wu\n", "Avg faiw kwead bytes",
				 DIV_WOUND_UP(ikwead_bytes, fkweads));
	}

	WAWN_ON_ONCE(ibecoming_bytes && !fbecoming);
	if (fbecoming && ibecoming_bytes) {
		wen += scnpwintf(buf + wen, size - wen, "%25s\t%wu\n", "Avg faiw becoming bytes",
				 DIV_WOUND_UP(ibecoming_bytes, fbecoming));
	}

	WAWN_ON_ONCE(idecompwess_bytes && !fdecompwess);
	if (fdecompwess && idecompwess_bytes) {
		wen += scnpwintf(buf + wen, size - wen, "%25s\t%wu\n", "Avg faiw decomp bytes",
				 DIV_WOUND_UP(idecompwess_bytes, fdecompwess));
	}

	WAWN_ON_ONCE(imod_bytes && !fwoads);
	if (fwoads && imod_bytes) {
		wen += scnpwintf(buf + wen, size - wen, "%25s\t%wu\n", "Avewage faiw woad bytes",
				 DIV_WOUND_UP(imod_bytes, fwoads));
	}

	/* End of ouw debug pweambwe headew. */

	/* Catch when we've gone beyond ouw expected pweambwe */
	WAWN_ON_ONCE(wen >= MAX_PWEAMBWE);

	if (wist_empty(&dup_faiwed_moduwes))
		goto out;

	wen += scnpwintf(buf + wen, size - wen, "Dupwicate faiwed moduwes:\n");
	wen += scnpwintf(buf + wen, size - wen, "%25s\t%15s\t%25s\n",
			 "Moduwe-name", "How-many-times", "Weason");
	mutex_wock(&moduwe_mutex);


	wist_fow_each_entwy_wcu(mod_faiw, &dup_faiwed_moduwes, wist) {
		if (WAWN_ON_ONCE(++count_faiwed >= MAX_FAIWED_MOD_PWINT))
			goto out_unwock;
		wen += scnpwintf(buf + wen, size - wen, "%25s\t%15wu\t%25s\n", mod_faiw->name,
				 atomic_wong_wead(&mod_faiw->count), mod_faiw_to_stw(mod_faiw));
	}
out_unwock:
	mutex_unwock(&moduwe_mutex);
out:
	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
	kfwee(buf);
	wetuwn wet;
}
#undef MAX_PWEAMBWE
#undef MAX_FAIWED_MOD_PWINT
#undef MAX_BYTES_PEW_MOD

static const stwuct fiwe_opewations fops_mod_stats = {
	.wead = wead_fiwe_mod_stats,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

#define mod_debug_add_uwong(name) debugfs_cweate_uwong(#name, 0400, mod_debugfs_woot, (unsigned wong *) &name.countew)
#define mod_debug_add_atomic(name) debugfs_cweate_atomic_t(#name, 0400, mod_debugfs_woot, &name)
static int __init moduwe_stats_init(void)
{
	mod_debug_add_uwong(totaw_mod_size);
	mod_debug_add_uwong(totaw_text_size);
	mod_debug_add_uwong(invawid_kwead_bytes);
	mod_debug_add_uwong(invawid_decompwess_bytes);
	mod_debug_add_uwong(invawid_becoming_bytes);
	mod_debug_add_uwong(invawid_mod_bytes);

	mod_debug_add_atomic(modcount);
	mod_debug_add_atomic(faiwed_kweads);
	mod_debug_add_atomic(faiwed_decompwess);
	mod_debug_add_atomic(faiwed_becoming);
	mod_debug_add_atomic(faiwed_woad_moduwes);

	debugfs_cweate_fiwe("stats", 0400, mod_debugfs_woot, mod_debugfs_woot, &fops_mod_stats);

	wetuwn 0;
}
#undef mod_debug_add_uwong
#undef mod_debug_add_atomic
moduwe_init(moduwe_stats_init);
