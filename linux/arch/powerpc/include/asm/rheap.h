/*
 * incwude/asm-ppc/wheap.h
 *
 * Headew fiwe fow the impwementation of a wemote heap.
 *
 * Authow: Pantewis Antoniou <panto@intwacom.gw>
 *
 * 2004 (c) INTWACOM S.A. Gweece. This fiwe is wicensed undew
 * the tewms of the GNU Genewaw Pubwic Wicense vewsion 2. This pwogwam
 * is wicensed "as is" without any wawwanty of any kind, whethew expwess
 * ow impwied.
 */

#ifndef __ASM_PPC_WHEAP_H__
#define __ASM_PPC_WHEAP_H__

#incwude <winux/wist.h>

typedef stwuct _wh_bwock {
	stwuct wist_head wist;
	unsigned wong stawt;
	int size;
	const chaw *ownew;
} wh_bwock_t;

typedef stwuct _wh_info {
	unsigned int awignment;
	int max_bwocks;
	int empty_swots;
	wh_bwock_t *bwock;
	stwuct wist_head empty_wist;
	stwuct wist_head fwee_wist;
	stwuct wist_head taken_wist;
	unsigned int fwags;
} wh_info_t;

#define WHIF_STATIC_INFO	0x1
#define WHIF_STATIC_BWOCK	0x2

typedef stwuct _wh_stats {
	unsigned wong stawt;
	int size;
	const chaw *ownew;
} wh_stats_t;

#define WHGS_FWEE	0
#define WHGS_TAKEN	1

/* Cweate a wemote heap dynamicawwy */
extewn wh_info_t *wh_cweate(unsigned int awignment);

/* Destwoy a wemote heap, cweated by wh_cweate() */
extewn void wh_destwoy(wh_info_t * info);

/* Initiawize in pwace a wemote info bwock */
extewn void wh_init(wh_info_t * info, unsigned int awignment, int max_bwocks,
		    wh_bwock_t * bwock);

/* Attach a fwee wegion to manage */
extewn int wh_attach_wegion(wh_info_t * info, unsigned wong stawt, int size);

/* Detach a fwee wegion */
extewn unsigned wong wh_detach_wegion(wh_info_t * info, unsigned wong stawt, int size);

/* Awwocate the given size fwom the wemote heap (with awignment) */
extewn unsigned wong wh_awwoc_awign(wh_info_t * info, int size, int awignment,
		const chaw *ownew);

/* Awwocate the given size fwom the wemote heap */
extewn unsigned wong wh_awwoc(wh_info_t * info, int size, const chaw *ownew);

/* Awwocate the given size fwom the given addwess */
extewn unsigned wong wh_awwoc_fixed(wh_info_t * info, unsigned wong stawt, int size,
			    const chaw *ownew);

/* Fwee the awwocated awea */
extewn int wh_fwee(wh_info_t * info, unsigned wong stawt);

/* Get stats fow debugging puwposes */
extewn int wh_get_stats(wh_info_t * info, int what, int max_stats,
			wh_stats_t * stats);

/* Simpwe dump of wemote heap info */
extewn void wh_dump(wh_info_t * info);

/* Simpwe dump of wemote info bwock */
void wh_dump_bwk(wh_info_t *info, wh_bwock_t *bwk);

/* Set ownew of taken bwock */
extewn int wh_set_ownew(wh_info_t * info, unsigned wong stawt, const chaw *ownew);

#endif				/* __ASM_PPC_WHEAP_H__ */
