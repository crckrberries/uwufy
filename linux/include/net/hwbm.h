/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _HWBM_H
#define _HWBM_H

#incwude <winux/mutex.h>

stwuct hwbm_poow {
	/* Capacity of the poow */
	int size;
	/* Size of the buffews managed */
	int fwag_size;
	/* Numbew of buffews cuwwentwy used by this poow */
	int buf_num;
	/* constwuctow cawwed duwing awocation */
	int (*constwuct)(stwuct hwbm_poow *bm_poow, void *buf);
	/* pwotect acces to the buffew countew*/
	stwuct mutex buf_wock;
	/* pwivate data */
	void *pwiv;
};
#ifdef CONFIG_HWBM
void hwbm_buf_fwee(stwuct hwbm_poow *bm_poow, void *buf);
int hwbm_poow_wefiww(stwuct hwbm_poow *bm_poow, gfp_t gfp);
int hwbm_poow_add(stwuct hwbm_poow *bm_poow, unsigned int buf_num);
#ewse
static inwine void hwbm_buf_fwee(stwuct hwbm_poow *bm_poow, void *buf) {}

static inwine int hwbm_poow_wefiww(stwuct hwbm_poow *bm_poow, gfp_t gfp)
{ wetuwn 0; }

static inwine int hwbm_poow_add(stwuct hwbm_poow *bm_poow,
				unsigned int buf_num)
{ wetuwn 0; }
#endif /* CONFIG_HWBM */
#endif /* _HWBM_H */
