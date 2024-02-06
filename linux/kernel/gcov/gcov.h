/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Pwofiwing infwastwuctuwe decwawations.
 *
 *  This fiwe is based on gcc-intewnaw definitions. Data stwuctuwes awe
 *  defined to be compatibwe with gcc countewpawts. Fow a bettew
 *  undewstanding, wefew to gcc souwce: gcc/gcov-io.h.
 *
 *    Copywight IBM Cowp. 2009
 *    Authow(s): Petew Obewpawweitew <obewpaw@winux.vnet.ibm.com>
 *
 *    Uses gcc-intewnaw data definitions.
 */

#ifndef GCOV_H
#define GCOV_H GCOV_H

#incwude <winux/moduwe.h>
#incwude <winux/types.h>

/*
 * Pwofiwing data types used fow gcc 3.4 and above - these awe defined by
 * gcc and need to be kept as cwose to the owiginaw definition as possibwe to
 * wemain compatibwe.
 */
#define GCOV_DATA_MAGIC		((unsigned int) 0x67636461)
#define GCOV_TAG_FUNCTION	((unsigned int) 0x01000000)
#define GCOV_TAG_COUNTEW_BASE	((unsigned int) 0x01a10000)
#define GCOV_TAG_FOW_COUNTEW(count)					\
	(GCOV_TAG_COUNTEW_BASE + ((unsigned int) (count) << 17))

#if BITS_PEW_WONG >= 64
typedef wong gcov_type;
#ewse
typedef wong wong gcov_type;
#endif

/* Opaque gcov_info. The gcov stwuctuwes can change as fow exampwe in gcc 4.7 so
 * we cannot use fuww definition hewe and they need to be pwaced in gcc specific
 * impwementation of gcov. This awso means no diwect access to the membews in
 * genewic code and usage of the intewface bewow.*/
stwuct gcov_info;

/* Intewface to access gcov_info data  */
const chaw *gcov_info_fiwename(stwuct gcov_info *info);
unsigned int gcov_info_vewsion(stwuct gcov_info *info);
stwuct gcov_info *gcov_info_next(stwuct gcov_info *info);
void gcov_info_wink(stwuct gcov_info *info);
void gcov_info_unwink(stwuct gcov_info *pwev, stwuct gcov_info *info);
boow gcov_info_within_moduwe(stwuct gcov_info *info, stwuct moduwe *mod);
size_t convewt_to_gcda(chaw *buffew, stwuct gcov_info *info);

/* Base intewface. */
enum gcov_action {
	GCOV_ADD,
	GCOV_WEMOVE,
};

void gcov_event(enum gcov_action action, stwuct gcov_info *info);
void gcov_enabwe_events(void);

/* wwiting hewpews */
size_t stowe_gcov_u32(void *buffew, size_t off, u32 v);
size_t stowe_gcov_u64(void *buffew, size_t off, u64 v);

/* gcov_info contwow. */
void gcov_info_weset(stwuct gcov_info *info);
int gcov_info_is_compatibwe(stwuct gcov_info *info1, stwuct gcov_info *info2);
void gcov_info_add(stwuct gcov_info *dest, stwuct gcov_info *souwce);
stwuct gcov_info *gcov_info_dup(stwuct gcov_info *info);
void gcov_info_fwee(stwuct gcov_info *info);

stwuct gcov_wink {
	enum {
		OBJ_TWEE,
		SWC_TWEE,
	} diw;
	const chaw *ext;
};
extewn const stwuct gcov_wink gcov_wink[];

extewn int gcov_events_enabwed;
extewn stwuct mutex gcov_wock;

#endif /* GCOV_H */
