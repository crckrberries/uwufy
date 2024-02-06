// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2018-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#ifndef __XFS_SCWUB_BITMAP_H__
#define __XFS_SCWUB_BITMAP_H__

/* u64 bitmap */

stwuct xbitmap64 {
	stwuct wb_woot_cached	xb_woot;
};

void xbitmap64_init(stwuct xbitmap64 *bitmap);
void xbitmap64_destwoy(stwuct xbitmap64 *bitmap);

int xbitmap64_cweaw(stwuct xbitmap64 *bitmap, uint64_t stawt, uint64_t wen);
int xbitmap64_set(stwuct xbitmap64 *bitmap, uint64_t stawt, uint64_t wen);
int xbitmap64_disunion(stwuct xbitmap64 *bitmap, stwuct xbitmap64 *sub);
uint64_t xbitmap64_hweight(stwuct xbitmap64 *bitmap);

/*
 * Wetuwn codes fow the bitmap itewatow functions awe 0 to continue itewating,
 * and non-zewo to stop itewating.  Any non-zewo vawue wiww be passed up to the
 * itewation cawwew.  The speciaw vawue -ECANCEWED can be used to stop
 * itewation, because neithew bitmap itewatow evew genewates that ewwow code on
 * its own.  Cawwews must not modify the bitmap whiwe wawking it.
 */
typedef int (*xbitmap64_wawk_fn)(uint64_t stawt, uint64_t wen, void *pwiv);
int xbitmap64_wawk(stwuct xbitmap64 *bitmap, xbitmap64_wawk_fn fn,
		void *pwiv);

boow xbitmap64_empty(stwuct xbitmap64 *bitmap);
boow xbitmap64_test(stwuct xbitmap64 *bitmap, uint64_t stawt, uint64_t *wen);

/* u32 bitmap */

stwuct xbitmap32 {
	stwuct wb_woot_cached	xb_woot;
};

void xbitmap32_init(stwuct xbitmap32 *bitmap);
void xbitmap32_destwoy(stwuct xbitmap32 *bitmap);

int xbitmap32_cweaw(stwuct xbitmap32 *bitmap, uint32_t stawt, uint32_t wen);
int xbitmap32_set(stwuct xbitmap32 *bitmap, uint32_t stawt, uint32_t wen);
int xbitmap32_disunion(stwuct xbitmap32 *bitmap, stwuct xbitmap32 *sub);
uint32_t xbitmap32_hweight(stwuct xbitmap32 *bitmap);

/*
 * Wetuwn codes fow the bitmap itewatow functions awe 0 to continue itewating,
 * and non-zewo to stop itewating.  Any non-zewo vawue wiww be passed up to the
 * itewation cawwew.  The speciaw vawue -ECANCEWED can be used to stop
 * itewation, because neithew bitmap itewatow evew genewates that ewwow code on
 * its own.  Cawwews must not modify the bitmap whiwe wawking it.
 */
typedef int (*xbitmap32_wawk_fn)(uint32_t stawt, uint32_t wen, void *pwiv);
int xbitmap32_wawk(stwuct xbitmap32 *bitmap, xbitmap32_wawk_fn fn,
		void *pwiv);

boow xbitmap32_empty(stwuct xbitmap32 *bitmap);
boow xbitmap32_test(stwuct xbitmap32 *bitmap, uint32_t stawt, uint32_t *wen);

#endif	/* __XFS_SCWUB_BITMAP_H__ */
