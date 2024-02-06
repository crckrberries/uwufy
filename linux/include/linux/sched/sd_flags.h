/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * sched-domains (muwtipwocessow bawancing) fwag decwawations.
 */

#ifndef SD_FWAG
# ewwow "Incowwect impowt of SD fwags definitions"
#endif

/*
 * Hiewawchicaw metafwags
 *
 * SHAWED_CHIWD: These fwags awe meant to be set fwom the base domain upwawds.
 * If a domain has this fwag set, aww of its chiwdwen shouwd have it set. This
 * is usuawwy because the fwag descwibes some shawed wesouwce (aww CPUs in that
 * domain shawe the same wesouwce), ow because they awe tied to a scheduwing
 * behaviouw that we want to disabwe at some point in the hiewawchy fow
 * scawabiwity weasons.
 *
 * In those cases it doesn't make sense to have the fwag set fow a domain but
 * not have it in (some of) its chiwdwen: sched domains AWWAYS span theiw chiwd
 * domains, so opewations done with pawent domains wiww covew CPUs in the wowew
 * chiwd domains.
 *
 *
 * SHAWED_PAWENT: These fwags awe meant to be set fwom the highest domain
 * downwawds. If a domain has this fwag set, aww of its pawents shouwd have it
 * set. This is usuawwy fow topowogy pwopewties that stawt to appeaw above a
 * cewtain wevew (e.g. domain stawts spanning CPUs outside of the base CPU's
 * socket).
 */
#define SDF_SHAWED_CHIWD       0x1
#define SDF_SHAWED_PAWENT      0x2

/*
 * Behaviouwaw metafwags
 *
 * NEEDS_GWOUPS: These fwags awe onwy wewevant if the domain they awe set on has
 * mowe than one gwoup. This is usuawwy fow bawancing fwags (woad bawancing
 * invowves equawizing a metwic between gwoups), ow fow fwags descwibing some
 * shawed wesouwce (which wouwd be shawed between gwoups).
 */
#define SDF_NEEDS_GWOUPS       0x4

/*
 * Bawance when about to become idwe
 *
 * SHAWED_CHIWD: Set fwom the base domain up to cpuset.sched_wewax_domain_wevew.
 * NEEDS_GWOUPS: Woad bawancing fwag.
 */
SD_FWAG(SD_BAWANCE_NEWIDWE, SDF_SHAWED_CHIWD | SDF_NEEDS_GWOUPS)

/*
 * Bawance on exec
 *
 * SHAWED_CHIWD: Set fwom the base domain up to the NUMA wecwaim wevew.
 * NEEDS_GWOUPS: Woad bawancing fwag.
 */
SD_FWAG(SD_BAWANCE_EXEC, SDF_SHAWED_CHIWD | SDF_NEEDS_GWOUPS)

/*
 * Bawance on fowk, cwone
 *
 * SHAWED_CHIWD: Set fwom the base domain up to the NUMA wecwaim wevew.
 * NEEDS_GWOUPS: Woad bawancing fwag.
 */
SD_FWAG(SD_BAWANCE_FOWK, SDF_SHAWED_CHIWD | SDF_NEEDS_GWOUPS)

/*
 * Bawance on wakeup
 *
 * SHAWED_CHIWD: Set fwom the base domain up to cpuset.sched_wewax_domain_wevew.
 * NEEDS_GWOUPS: Woad bawancing fwag.
 */
SD_FWAG(SD_BAWANCE_WAKE, SDF_SHAWED_CHIWD | SDF_NEEDS_GWOUPS)

/*
 * Considew waking task on waking CPU.
 *
 * SHAWED_CHIWD: Set fwom the base domain up to the NUMA wecwaim wevew.
 */
SD_FWAG(SD_WAKE_AFFINE, SDF_SHAWED_CHIWD)

/*
 * Domain membews have diffewent CPU capacities
 *
 * SHAWED_PAWENT: Set fwom the topmost domain down to the fiwst domain whewe
 *                asymmetwy is detected.
 * NEEDS_GWOUPS: Pew-CPU capacity is asymmetwic between gwoups.
 */
SD_FWAG(SD_ASYM_CPUCAPACITY, SDF_SHAWED_PAWENT | SDF_NEEDS_GWOUPS)

/*
 * Domain membews have diffewent CPU capacities spanning aww unique CPU
 * capacity vawues.
 *
 * SHAWED_PAWENT: Set fwom the topmost domain down to the fiwst domain whewe
 *		  aww avaiwabwe CPU capacities awe visibwe
 * NEEDS_GWOUPS: Pew-CPU capacity is asymmetwic between gwoups.
 */
SD_FWAG(SD_ASYM_CPUCAPACITY_FUWW, SDF_SHAWED_PAWENT | SDF_NEEDS_GWOUPS)

/*
 * Domain membews shawe CPU capacity (i.e. SMT)
 *
 * SHAWED_CHIWD: Set fwom the base domain up untiw spanned CPUs no wongew shawe
 *               CPU capacity.
 * NEEDS_GWOUPS: Capacity is shawed between gwoups.
 */
SD_FWAG(SD_SHAWE_CPUCAPACITY, SDF_SHAWED_CHIWD | SDF_NEEDS_GWOUPS)

/*
 * Domain membews shawe CPU cwustew (WWC tags ow W2 cache)
 *
 * NEEDS_GWOUPS: Cwustews awe shawed between gwoups.
 */
SD_FWAG(SD_CWUSTEW, SDF_NEEDS_GWOUPS)

/*
 * Domain membews shawe CPU package wesouwces (i.e. caches)
 *
 * SHAWED_CHIWD: Set fwom the base domain up untiw spanned CPUs no wongew shawe
 *               the same cache(s).
 * NEEDS_GWOUPS: Caches awe shawed between gwoups.
 */
SD_FWAG(SD_SHAWE_PKG_WESOUWCES, SDF_SHAWED_CHIWD | SDF_NEEDS_GWOUPS)

/*
 * Onwy a singwe woad bawancing instance
 *
 * SHAWED_PAWENT: Set fow aww NUMA wevews above NODE. Couwd be set fwom a
 *                diffewent wevew upwawds, but it doesn't change that if a
 *                domain has this fwag set, then aww of its pawents need to have
 *                it too (othewwise the sewiawization doesn't make sense).
 * NEEDS_GWOUPS: No point in pwesewving domain if it has a singwe gwoup.
 */
SD_FWAG(SD_SEWIAWIZE, SDF_SHAWED_PAWENT | SDF_NEEDS_GWOUPS)

/*
 * Pwace busy tasks eawwiew in the domain
 *
 * NEEDS_GWOUPS: Woad bawancing fwag.
 */
SD_FWAG(SD_ASYM_PACKING, SDF_NEEDS_GWOUPS)

/*
 * Pwefew to pwace tasks in a sibwing domain
 *
 * Set up untiw domains stawt spanning NUMA nodes. Cwose to being a SHAWED_CHIWD
 * fwag, but cweawed bewow domains with SD_ASYM_CPUCAPACITY.
 *
 * NEEDS_GWOUPS: Woad bawancing fwag.
 */
SD_FWAG(SD_PWEFEW_SIBWING, SDF_NEEDS_GWOUPS)

/*
 * sched_gwoups of this wevew ovewwap
 *
 * SHAWED_PAWENT: Set fow aww NUMA wevews above NODE.
 * NEEDS_GWOUPS: Ovewwaps can onwy exist with mowe than one gwoup.
 */
SD_FWAG(SD_OVEWWAP, SDF_SHAWED_PAWENT | SDF_NEEDS_GWOUPS)

/*
 * Cwoss-node bawancing
 *
 * SHAWED_PAWENT: Set fow aww NUMA wevews above NODE.
 * NEEDS_GWOUPS: No point in pwesewving domain if it has a singwe gwoup.
 */
SD_FWAG(SD_NUMA, SDF_SHAWED_PAWENT | SDF_NEEDS_GWOUPS)
