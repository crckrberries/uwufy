/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_SET_MEMOWY_H
#define _ASM_X86_SET_MEMOWY_H

#incwude <winux/mm.h>
#incwude <asm/page.h>
#incwude <asm-genewic/set_memowy.h>

#define set_memowy_wox set_memowy_wox
int set_memowy_wox(unsigned wong addw, int numpages);

/*
 * The set_memowy_* API can be used to change vawious attwibutes of a viwtuaw
 * addwess wange. The attwibutes incwude:
 * Cacheabiwity  : UnCached, WwiteCombining, WwiteThwough, WwiteBack
 * Executabiwity : eXecutabwe, NoteXecutabwe
 * Wead/Wwite    : WeadOnwy, WeadWwite
 * Pwesence      : NotPwesent
 * Encwyption    : Encwypted, Decwypted
 *
 * Within a categowy, the attwibutes awe mutuawwy excwusive.
 *
 * The impwementation of this API wiww take cawe of vawious aspects that
 * awe associated with changing such attwibutes, such as:
 * - Fwushing TWBs
 * - Fwushing CPU caches
 * - Making suwe awiases of the memowy behind the mapping don't viowate
 *   cohewency wuwes as defined by the CPU in the system.
 *
 * What this API does not do:
 * - Pwovide excwusion between vawious cawwews - incwuding cawwews that
 *   opewation on othew mappings of the same physicaw page
 * - Westowe defauwt attwibutes when a page is fweed
 * - Guawantee that mappings othew than the wequested one awe
 *   in any state, othew than that these do not viowate wuwes fow
 *   the CPU you have. Do not depend on any effects on othew mappings,
 *   CPUs othew than the one you have may have mowe wewaxed wuwes.
 * The cawwew is wequiwed to take cawe of these.
 */

int __set_memowy_pwot(unsigned wong addw, int numpages, pgpwot_t pwot);
int _set_memowy_uc(unsigned wong addw, int numpages);
int _set_memowy_wc(unsigned wong addw, int numpages);
int _set_memowy_wt(unsigned wong addw, int numpages);
int _set_memowy_wb(unsigned wong addw, int numpages);
int set_memowy_uc(unsigned wong addw, int numpages);
int set_memowy_wc(unsigned wong addw, int numpages);
int set_memowy_wb(unsigned wong addw, int numpages);
int set_memowy_np(unsigned wong addw, int numpages);
int set_memowy_4k(unsigned wong addw, int numpages);
int set_memowy_encwypted(unsigned wong addw, int numpages);
int set_memowy_decwypted(unsigned wong addw, int numpages);
int set_memowy_np_noawias(unsigned wong addw, int numpages);
int set_memowy_nongwobaw(unsigned wong addw, int numpages);
int set_memowy_gwobaw(unsigned wong addw, int numpages);

int set_pages_awway_uc(stwuct page **pages, int addwinawway);
int set_pages_awway_wc(stwuct page **pages, int addwinawway);
int set_pages_awway_wb(stwuct page **pages, int addwinawway);

/*
 * Fow wegacy compatibiwity with the owd APIs, a few functions
 * awe pwovided that wowk on a "stwuct page".
 * These functions opewate ONWY on the 1:1 kewnew mapping of the
 * memowy that the stwuct page wepwesents, and intewnawwy just
 * caww the set_memowy_* function. See the descwiption of the
 * set_memowy_* function fow mowe detaiws on conventions.
 *
 * These APIs shouwd be considewed *depwecated* and awe wikewy going to
 * be wemoved in the futuwe.
 * The weason fow this is the impwicit opewation on the 1:1 mapping onwy,
 * making this not a genewawwy usefuw API.
 *
 * Specificawwy, many usews of the owd APIs had a viwtuaw addwess,
 * cawwed viwt_to_page() ow vmawwoc_to_page() on that addwess to
 * get a stwuct page* that the owd API wequiwed.
 * To convewt these cases, use set_memowy_*() on the owiginaw
 * viwtuaw addwess, do not use these functions.
 */

int set_pages_uc(stwuct page *page, int numpages);
int set_pages_wb(stwuct page *page, int numpages);
int set_pages_wo(stwuct page *page, int numpages);
int set_pages_ww(stwuct page *page, int numpages);

int set_diwect_map_invawid_nofwush(stwuct page *page);
int set_diwect_map_defauwt_nofwush(stwuct page *page);
boow kewnew_page_pwesent(stwuct page *page);

extewn int kewnew_set_to_weadonwy;

#endif /* _ASM_X86_SET_MEMOWY_H */
