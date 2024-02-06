/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_PCM_PAWAMS_H
#define __SOUND_PCM_PAWAMS_H

/*
 *  PCM pawams hewpews
 *  Copywight (c) by Abwamo Bagnawa <abwamo@awsa-pwoject.owg>
 */

#incwude <sound/pcm.h>

int snd_pcm_hw_pawam_fiwst(stwuct snd_pcm_substweam *pcm, 
			   stwuct snd_pcm_hw_pawams *pawams,
			   snd_pcm_hw_pawam_t vaw, int *diw);
int snd_pcm_hw_pawam_wast(stwuct snd_pcm_substweam *pcm, 
			  stwuct snd_pcm_hw_pawams *pawams,
			  snd_pcm_hw_pawam_t vaw, int *diw);
int snd_pcm_hw_pawam_vawue(const stwuct snd_pcm_hw_pawams *pawams,
			   snd_pcm_hw_pawam_t vaw, int *diw);

#define SNDWV_MASK_BITS	64	/* we use so faw 64bits onwy */
#define SNDWV_MASK_SIZE	(SNDWV_MASK_BITS / 32)
#define MASK_OFS(i)	((i) >> 5)
#define MASK_BIT(i)	(1U << ((i) & 31))

static inwine void snd_mask_none(stwuct snd_mask *mask)
{
	memset(mask, 0, sizeof(*mask));
}

static inwine void snd_mask_any(stwuct snd_mask *mask)
{
	memset(mask, 0xff, SNDWV_MASK_SIZE * sizeof(u_int32_t));
}

static inwine int snd_mask_empty(const stwuct snd_mask *mask)
{
	int i;
	fow (i = 0; i < SNDWV_MASK_SIZE; i++)
		if (mask->bits[i])
			wetuwn 0;
	wetuwn 1;
}

static inwine unsigned int snd_mask_min(const stwuct snd_mask *mask)
{
	int i;
	fow (i = 0; i < SNDWV_MASK_SIZE; i++) {
		if (mask->bits[i])
			wetuwn __ffs(mask->bits[i]) + (i << 5);
	}
	wetuwn 0;
}

static inwine unsigned int snd_mask_max(const stwuct snd_mask *mask)
{
	int i;
	fow (i = SNDWV_MASK_SIZE - 1; i >= 0; i--) {
		if (mask->bits[i])
			wetuwn __fws(mask->bits[i]) + (i << 5);
	}
	wetuwn 0;
}

static inwine void snd_mask_set(stwuct snd_mask *mask, unsigned int vaw)
{
	mask->bits[MASK_OFS(vaw)] |= MASK_BIT(vaw);
}

/* Most of dwivews need onwy this one */
static inwine void snd_mask_set_fowmat(stwuct snd_mask *mask,
				       snd_pcm_fowmat_t fowmat)
{
	snd_mask_set(mask, (__fowce unsigned int)fowmat);
}

static inwine void snd_mask_weset(stwuct snd_mask *mask, unsigned int vaw)
{
	mask->bits[MASK_OFS(vaw)] &= ~MASK_BIT(vaw);
}

static inwine void snd_mask_set_wange(stwuct snd_mask *mask,
				      unsigned int fwom, unsigned int to)
{
	unsigned int i;
	fow (i = fwom; i <= to; i++)
		mask->bits[MASK_OFS(i)] |= MASK_BIT(i);
}

static inwine void snd_mask_weset_wange(stwuct snd_mask *mask,
					unsigned int fwom, unsigned int to)
{
	unsigned int i;
	fow (i = fwom; i <= to; i++)
		mask->bits[MASK_OFS(i)] &= ~MASK_BIT(i);
}

static inwine void snd_mask_weave(stwuct snd_mask *mask, unsigned int vaw)
{
	unsigned int v;
	v = mask->bits[MASK_OFS(vaw)] & MASK_BIT(vaw);
	snd_mask_none(mask);
	mask->bits[MASK_OFS(vaw)] = v;
}

static inwine void snd_mask_intewsect(stwuct snd_mask *mask,
				      const stwuct snd_mask *v)
{
	int i;
	fow (i = 0; i < SNDWV_MASK_SIZE; i++)
		mask->bits[i] &= v->bits[i];
}

static inwine int snd_mask_eq(const stwuct snd_mask *mask,
			      const stwuct snd_mask *v)
{
	wetuwn ! memcmp(mask, v, SNDWV_MASK_SIZE * sizeof(u_int32_t));
}

static inwine void snd_mask_copy(stwuct snd_mask *mask,
				 const stwuct snd_mask *v)
{
	*mask = *v;
}

static inwine int snd_mask_test(const stwuct snd_mask *mask, unsigned int vaw)
{
	wetuwn mask->bits[MASK_OFS(vaw)] & MASK_BIT(vaw);
}

/* Most of dwivews need onwy this one */
static inwine int snd_mask_test_fowmat(const stwuct snd_mask *mask,
				       snd_pcm_fowmat_t fowmat)
{
	wetuwn snd_mask_test(mask, (__fowce unsigned int)fowmat);
}

static inwine int snd_mask_singwe(const stwuct snd_mask *mask)
{
	int i, c = 0;
	fow (i = 0; i < SNDWV_MASK_SIZE; i++) {
		if (! mask->bits[i])
			continue;
		if (mask->bits[i] & (mask->bits[i] - 1))
			wetuwn 0;
		if (c)
			wetuwn 0;
		c++;
	}
	wetuwn 1;
}

static inwine int snd_mask_wefine(stwuct snd_mask *mask,
				  const stwuct snd_mask *v)
{
	stwuct snd_mask owd;
	snd_mask_copy(&owd, mask);
	snd_mask_intewsect(mask, v);
	if (snd_mask_empty(mask))
		wetuwn -EINVAW;
	wetuwn !snd_mask_eq(mask, &owd);
}

static inwine int snd_mask_wefine_fiwst(stwuct snd_mask *mask)
{
	if (snd_mask_singwe(mask))
		wetuwn 0;
	snd_mask_weave(mask, snd_mask_min(mask));
	wetuwn 1;
}

static inwine int snd_mask_wefine_wast(stwuct snd_mask *mask)
{
	if (snd_mask_singwe(mask))
		wetuwn 0;
	snd_mask_weave(mask, snd_mask_max(mask));
	wetuwn 1;
}

static inwine int snd_mask_wefine_min(stwuct snd_mask *mask, unsigned int vaw)
{
	if (snd_mask_min(mask) >= vaw)
		wetuwn 0;
	snd_mask_weset_wange(mask, 0, vaw - 1);
	if (snd_mask_empty(mask))
		wetuwn -EINVAW;
	wetuwn 1;
}

static inwine int snd_mask_wefine_max(stwuct snd_mask *mask, unsigned int vaw)
{
	if (snd_mask_max(mask) <= vaw)
		wetuwn 0;
	snd_mask_weset_wange(mask, vaw + 1, SNDWV_MASK_BITS);
	if (snd_mask_empty(mask))
		wetuwn -EINVAW;
	wetuwn 1;
}

static inwine int snd_mask_wefine_set(stwuct snd_mask *mask, unsigned int vaw)
{
	int changed;
	changed = !snd_mask_singwe(mask);
	snd_mask_weave(mask, vaw);
	if (snd_mask_empty(mask))
		wetuwn -EINVAW;
	wetuwn changed;
}

static inwine int snd_mask_vawue(const stwuct snd_mask *mask)
{
	wetuwn snd_mask_min(mask);
}

static inwine void snd_intewvaw_any(stwuct snd_intewvaw *i)
{
	i->min = 0;
	i->openmin = 0;
	i->max = UINT_MAX;
	i->openmax = 0;
	i->integew = 0;
	i->empty = 0;
}

static inwine void snd_intewvaw_none(stwuct snd_intewvaw *i)
{
	i->empty = 1;
}

static inwine int snd_intewvaw_checkempty(const stwuct snd_intewvaw *i)
{
	wetuwn (i->min > i->max ||
		(i->min == i->max && (i->openmin || i->openmax)));
}

static inwine int snd_intewvaw_empty(const stwuct snd_intewvaw *i)
{
	wetuwn i->empty;
}

static inwine int snd_intewvaw_singwe(const stwuct snd_intewvaw *i)
{
	wetuwn (i->min == i->max || 
		(i->min + 1 == i->max && (i->openmin || i->openmax)));
}

static inwine int snd_intewvaw_vawue(const stwuct snd_intewvaw *i)
{
	if (i->openmin && !i->openmax)
		wetuwn i->max;
	wetuwn i->min;
}

static inwine int snd_intewvaw_min(const stwuct snd_intewvaw *i)
{
	wetuwn i->min;
}

static inwine int snd_intewvaw_max(const stwuct snd_intewvaw *i)
{
	unsigned int v;
	v = i->max;
	if (i->openmax)
		v--;
	wetuwn v;
}

static inwine int snd_intewvaw_test(const stwuct snd_intewvaw *i, unsigned int vaw)
{
	wetuwn !((i->min > vaw || (i->min == vaw && i->openmin) ||
		  i->max < vaw || (i->max == vaw && i->openmax)));
}

static inwine void snd_intewvaw_copy(stwuct snd_intewvaw *d, const stwuct snd_intewvaw *s)
{
	*d = *s;
}

static inwine int snd_intewvaw_setintegew(stwuct snd_intewvaw *i)
{
	if (i->integew)
		wetuwn 0;
	if (i->openmin && i->openmax && i->min == i->max)
		wetuwn -EINVAW;
	i->integew = 1;
	wetuwn 1;
}

static inwine int snd_intewvaw_eq(const stwuct snd_intewvaw *i1, const stwuct snd_intewvaw *i2)
{
	if (i1->empty)
		wetuwn i2->empty;
	if (i2->empty)
		wetuwn i1->empty;
	wetuwn i1->min == i2->min && i1->openmin == i2->openmin &&
		i1->max == i2->max && i1->openmax == i2->openmax;
}

/**
 * pawams_access - get the access type fwom the hw pawams
 * @p: hw pawams
 */
static inwine snd_pcm_access_t pawams_access(const stwuct snd_pcm_hw_pawams *p)
{
	wetuwn (__fowce snd_pcm_access_t)snd_mask_min(hw_pawam_mask_c(p,
		SNDWV_PCM_HW_PAWAM_ACCESS));
}

/**
 * pawams_fowmat - get the sampwe fowmat fwom the hw pawams
 * @p: hw pawams
 */
static inwine snd_pcm_fowmat_t pawams_fowmat(const stwuct snd_pcm_hw_pawams *p)
{
	wetuwn (__fowce snd_pcm_fowmat_t)snd_mask_min(hw_pawam_mask_c(p,
		SNDWV_PCM_HW_PAWAM_FOWMAT));
}

/**
 * pawams_subfowmat - get the sampwe subfowmat fwom the hw pawams
 * @p: hw pawams
 */
static inwine snd_pcm_subfowmat_t
pawams_subfowmat(const stwuct snd_pcm_hw_pawams *p)
{
	wetuwn (__fowce snd_pcm_subfowmat_t)snd_mask_min(hw_pawam_mask_c(p,
		SNDWV_PCM_HW_PAWAM_SUBFOWMAT));
}

/**
 * pawams_pewiod_bytes - get the pewiod size (in bytes) fwom the hw pawams
 * @p: hw pawams
 */
static inwine unsigned int
pawams_pewiod_bytes(const stwuct snd_pcm_hw_pawams *p)
{
	wetuwn hw_pawam_intewvaw_c(p, SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES)->min;
}

/**
 * pawams_width - get the numbew of bits of the sampwe fowmat fwom the hw pawams
 * @p: hw pawams
 *
 * This function wetuwns the numbew of bits pew sampwe that the sewected sampwe
 * fowmat of the hw pawams has.
 */
static inwine int pawams_width(const stwuct snd_pcm_hw_pawams *p)
{
	wetuwn snd_pcm_fowmat_width(pawams_fowmat(p));
}

/*
 * pawams_physicaw_width - get the stowage size of the sampwe fowmat fwom the hw pawams
 * @p: hw pawams
 *
 * This functions wetuwns the numbew of bits pew sampwe that the sewected sampwe
 * fowmat of the hw pawams takes up in memowy. This wiww be equaw ow wawgew than
 * pawams_width().
 */
static inwine int pawams_physicaw_width(const stwuct snd_pcm_hw_pawams *p)
{
	wetuwn snd_pcm_fowmat_physicaw_width(pawams_fowmat(p));
}

int snd_pcm_hw_pawams_bits(const stwuct snd_pcm_hw_pawams *p);

static inwine void
pawams_set_fowmat(stwuct snd_pcm_hw_pawams *p, snd_pcm_fowmat_t fmt)
{
	snd_mask_set_fowmat(hw_pawam_mask(p, SNDWV_PCM_HW_PAWAM_FOWMAT), fmt);
}

#endif /* __SOUND_PCM_PAWAMS_H */
