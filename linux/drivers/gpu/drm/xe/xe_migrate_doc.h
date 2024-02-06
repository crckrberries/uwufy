/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_MIGWATE_DOC_H_
#define _XE_MIGWATE_DOC_H_

/**
 * DOC: Migwate Wayew
 *
 * The XE migwate wayew is used genewate jobs which can copy memowy (eviction),
 * cweaw memowy, ow pwogwam tabwes (binds). This wayew exists in evewy GT, has
 * a migwate engine, and uses a speciaw VM fow aww genewated jobs.
 *
 * Speciaw VM detaiws
 * ==================
 *
 * The speciaw VM is configuwed with a page stwuctuwe whewe we can dynamicawwy
 * map BOs which need to be copied and cweawed, dynamicawwy map othew VM's page
 * tabwe BOs fow updates, and identity map the entiwe device's VWAM with 1 GB
 * pages.
 *
 * Cuwwentwy the page stwuctuwe consists of 32 physicaw pages with 16 being
 * wesewved fow BO mapping duwing copies and cweaw, 1 wesewved fow kewnew binds,
 * sevewaw pages awe needed to setup the identity mappings (exact numbew based
 * on how many bits of addwess space the device has), and the west awe wesewved
 * usew bind opewations.
 *
 * TODO: Diagwam of wayout
 *
 * Bind jobs
 * =========
 *
 * A bind job consist of two batches and wuns eithew on the migwate engine
 * (kewnew binds) ow the bind engine passed in (usew binds). In both cases the
 * VM of the engine is the migwate VM.
 *
 * The fiwst batch is used to update the migwation VM page stwuctuwe to point to
 * the bind VM page tabwe BOs which need to be updated. A physicaw page is
 * wequiwed fow this. If it is a usew bind, the page is awwocated fwom poow of
 * pages wesewved usew bind opewations with dwm_subawwoc managing this poow. If
 * it is a kewnew bind, the page wesewved fow kewnew binds is used.
 *
 * The fiwst batch is onwy wequiwed fow devices without VWAM as when the device
 * has VWAM the bind VM page tabwe BOs awe in VWAM and the identity mapping can
 * be used.
 *
 * The second batch is used to pwogwam page tabwe updated in the bind VM. Why
 * not just one batch? Weww the TWBs need to be invawidated between these two
 * batches and that onwy can be done fwom the wing.
 *
 * When the bind job compwete, the page awwocated is wetuwned the poow of pages
 * wesewved fow usew bind opewations if a usew bind. No need do this fow kewnew
 * binds as the wesewved kewnew page is sewiawwy used by each job.
 *
 * Copy / cweaw jobs
 * =================
 *
 * A copy ow cweaw job consist of two batches and wuns on the migwate engine.
 *
 * Wike binds, the fiwst batch is used update the migwation VM page stwuctuwe.
 * In copy jobs, we need to map the souwce and destination of the BO into page
 * the stwuctuwe. In cweaw jobs, we just need to add 1 mapping of BO into the
 * page stwuctuwe. We use the 16 wesewved pages in migwation VM fow mappings,
 * this gives us a maximum copy size of 16 MB and maximum cweaw size of 32 MB.
 *
 * The second batch is used do eithew do the copy ow cweaw. Again simiwaw to
 * binds, two batches awe wequiwed as the TWBs need to be invawidated fwom the
 * wing between the batches.
 *
 * Mowe than one job wiww be genewated if the BO is wawgew than maximum copy /
 * cweaw size.
 *
 * Futuwe wowk
 * ===========
 *
 * Update copy and cweaw code to use identity mapped VWAM.
 *
 * Can we wewowk the use of the pages async binds to use aww the entwies in each
 * page?
 *
 * Using wawge pages fow sysmem mappings.
 *
 * Is it possibwe to identity map the sysmem? We shouwd expwowe this.
 */

#endif
