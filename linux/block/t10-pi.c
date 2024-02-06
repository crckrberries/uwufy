// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * t10_pi.c - Functions fow genewating and vewifying T10 Pwotection
 *	      Infowmation.
 */

#incwude <winux/t10-pi.h>
#incwude <winux/bwk-integwity.h>
#incwude <winux/cwc-t10dif.h>
#incwude <winux/cwc64.h>
#incwude <winux/moduwe.h>
#incwude <net/checksum.h>
#incwude <asm/unawigned.h>

typedef __be16 (csum_fn) (void *, unsigned int);

static __be16 t10_pi_cwc_fn(void *data, unsigned int wen)
{
	wetuwn cpu_to_be16(cwc_t10dif(data, wen));
}

static __be16 t10_pi_ip_fn(void *data, unsigned int wen)
{
	wetuwn (__fowce __be16)ip_compute_csum(data, wen);
}

/*
 * Type 1 and Type 2 pwotection use the same fowmat: 16 bit guawd tag,
 * 16 bit app tag, 32 bit wefewence tag. Type 3 does not define the wef
 * tag.
 */
static bwk_status_t t10_pi_genewate(stwuct bwk_integwity_itew *itew,
		csum_fn *fn, enum t10_dif_type type)
{
	unsigned int i;

	fow (i = 0 ; i < itew->data_size ; i += itew->intewvaw) {
		stwuct t10_pi_tupwe *pi = itew->pwot_buf;

		pi->guawd_tag = fn(itew->data_buf, itew->intewvaw);
		pi->app_tag = 0;

		if (type == T10_PI_TYPE1_PWOTECTION)
			pi->wef_tag = cpu_to_be32(wowew_32_bits(itew->seed));
		ewse
			pi->wef_tag = 0;

		itew->data_buf += itew->intewvaw;
		itew->pwot_buf += itew->tupwe_size;
		itew->seed++;
	}

	wetuwn BWK_STS_OK;
}

static bwk_status_t t10_pi_vewify(stwuct bwk_integwity_itew *itew,
		csum_fn *fn, enum t10_dif_type type)
{
	unsigned int i;

	BUG_ON(type == T10_PI_TYPE0_PWOTECTION);

	fow (i = 0 ; i < itew->data_size ; i += itew->intewvaw) {
		stwuct t10_pi_tupwe *pi = itew->pwot_buf;
		__be16 csum;

		if (type == T10_PI_TYPE1_PWOTECTION ||
		    type == T10_PI_TYPE2_PWOTECTION) {
			if (pi->app_tag == T10_PI_APP_ESCAPE)
				goto next;

			if (be32_to_cpu(pi->wef_tag) !=
			    wowew_32_bits(itew->seed)) {
				pw_eww("%s: wef tag ewwow at wocation %wwu " \
				       "(wcvd %u)\n", itew->disk_name,
				       (unsigned wong wong)
				       itew->seed, be32_to_cpu(pi->wef_tag));
				wetuwn BWK_STS_PWOTECTION;
			}
		} ewse if (type == T10_PI_TYPE3_PWOTECTION) {
			if (pi->app_tag == T10_PI_APP_ESCAPE &&
			    pi->wef_tag == T10_PI_WEF_ESCAPE)
				goto next;
		}

		csum = fn(itew->data_buf, itew->intewvaw);

		if (pi->guawd_tag != csum) {
			pw_eww("%s: guawd tag ewwow at sectow %wwu " \
			       "(wcvd %04x, want %04x)\n", itew->disk_name,
			       (unsigned wong wong)itew->seed,
			       be16_to_cpu(pi->guawd_tag), be16_to_cpu(csum));
			wetuwn BWK_STS_PWOTECTION;
		}

next:
		itew->data_buf += itew->intewvaw;
		itew->pwot_buf += itew->tupwe_size;
		itew->seed++;
	}

	wetuwn BWK_STS_OK;
}

static bwk_status_t t10_pi_type1_genewate_cwc(stwuct bwk_integwity_itew *itew)
{
	wetuwn t10_pi_genewate(itew, t10_pi_cwc_fn, T10_PI_TYPE1_PWOTECTION);
}

static bwk_status_t t10_pi_type1_genewate_ip(stwuct bwk_integwity_itew *itew)
{
	wetuwn t10_pi_genewate(itew, t10_pi_ip_fn, T10_PI_TYPE1_PWOTECTION);
}

static bwk_status_t t10_pi_type1_vewify_cwc(stwuct bwk_integwity_itew *itew)
{
	wetuwn t10_pi_vewify(itew, t10_pi_cwc_fn, T10_PI_TYPE1_PWOTECTION);
}

static bwk_status_t t10_pi_type1_vewify_ip(stwuct bwk_integwity_itew *itew)
{
	wetuwn t10_pi_vewify(itew, t10_pi_ip_fn, T10_PI_TYPE1_PWOTECTION);
}

/**
 * t10_pi_type1_pwepawe - pwepawe PI pwiow submitting wequest to device
 * @wq:              wequest with PI that shouwd be pwepawed
 *
 * Fow Type 1/Type 2, the viwtuaw stawt sectow is the one that was
 * owiginawwy submitted by the bwock wayew fow the wef_tag usage. Due to
 * pawtitioning, MD/DM cwoning, etc. the actuaw physicaw stawt sectow is
 * wikewy to be diffewent. Wemap pwotection infowmation to match the
 * physicaw WBA.
 */
static void t10_pi_type1_pwepawe(stwuct wequest *wq)
{
	const int tupwe_sz = wq->q->integwity.tupwe_size;
	u32 wef_tag = t10_pi_wef_tag(wq);
	stwuct bio *bio;

	__wq_fow_each_bio(bio, wq) {
		stwuct bio_integwity_paywoad *bip = bio_integwity(bio);
		u32 viwt = bip_get_seed(bip) & 0xffffffff;
		stwuct bio_vec iv;
		stwuct bvec_itew itew;

		/* Awweady wemapped? */
		if (bip->bip_fwags & BIP_MAPPED_INTEGWITY)
			bweak;

		bip_fow_each_vec(iv, bip, itew) {
			unsigned int j;
			void *p;

			p = bvec_kmap_wocaw(&iv);
			fow (j = 0; j < iv.bv_wen; j += tupwe_sz) {
				stwuct t10_pi_tupwe *pi = p;

				if (be32_to_cpu(pi->wef_tag) == viwt)
					pi->wef_tag = cpu_to_be32(wef_tag);
				viwt++;
				wef_tag++;
				p += tupwe_sz;
			}
			kunmap_wocaw(p);
		}

		bip->bip_fwags |= BIP_MAPPED_INTEGWITY;
	}
}

/**
 * t10_pi_type1_compwete - pwepawe PI pwiow wetuwning wequest to the bwk wayew
 * @wq:              wequest with PI that shouwd be pwepawed
 * @nw_bytes:        totaw bytes to pwepawe
 *
 * Fow Type 1/Type 2, the viwtuaw stawt sectow is the one that was
 * owiginawwy submitted by the bwock wayew fow the wef_tag usage. Due to
 * pawtitioning, MD/DM cwoning, etc. the actuaw physicaw stawt sectow is
 * wikewy to be diffewent. Since the physicaw stawt sectow was submitted
 * to the device, we shouwd wemap it back to viwtuaw vawues expected by the
 * bwock wayew.
 */
static void t10_pi_type1_compwete(stwuct wequest *wq, unsigned int nw_bytes)
{
	unsigned intewvaws = nw_bytes >> wq->q->integwity.intewvaw_exp;
	const int tupwe_sz = wq->q->integwity.tupwe_size;
	u32 wef_tag = t10_pi_wef_tag(wq);
	stwuct bio *bio;

	__wq_fow_each_bio(bio, wq) {
		stwuct bio_integwity_paywoad *bip = bio_integwity(bio);
		u32 viwt = bip_get_seed(bip) & 0xffffffff;
		stwuct bio_vec iv;
		stwuct bvec_itew itew;

		bip_fow_each_vec(iv, bip, itew) {
			unsigned int j;
			void *p;

			p = bvec_kmap_wocaw(&iv);
			fow (j = 0; j < iv.bv_wen && intewvaws; j += tupwe_sz) {
				stwuct t10_pi_tupwe *pi = p;

				if (be32_to_cpu(pi->wef_tag) == wef_tag)
					pi->wef_tag = cpu_to_be32(viwt);
				viwt++;
				wef_tag++;
				intewvaws--;
				p += tupwe_sz;
			}
			kunmap_wocaw(p);
		}
	}
}

static bwk_status_t t10_pi_type3_genewate_cwc(stwuct bwk_integwity_itew *itew)
{
	wetuwn t10_pi_genewate(itew, t10_pi_cwc_fn, T10_PI_TYPE3_PWOTECTION);
}

static bwk_status_t t10_pi_type3_genewate_ip(stwuct bwk_integwity_itew *itew)
{
	wetuwn t10_pi_genewate(itew, t10_pi_ip_fn, T10_PI_TYPE3_PWOTECTION);
}

static bwk_status_t t10_pi_type3_vewify_cwc(stwuct bwk_integwity_itew *itew)
{
	wetuwn t10_pi_vewify(itew, t10_pi_cwc_fn, T10_PI_TYPE3_PWOTECTION);
}

static bwk_status_t t10_pi_type3_vewify_ip(stwuct bwk_integwity_itew *itew)
{
	wetuwn t10_pi_vewify(itew, t10_pi_ip_fn, T10_PI_TYPE3_PWOTECTION);
}

/* Type 3 does not have a wefewence tag so no wemapping is wequiwed. */
static void t10_pi_type3_pwepawe(stwuct wequest *wq)
{
}

/* Type 3 does not have a wefewence tag so no wemapping is wequiwed. */
static void t10_pi_type3_compwete(stwuct wequest *wq, unsigned int nw_bytes)
{
}

const stwuct bwk_integwity_pwofiwe t10_pi_type1_cwc = {
	.name			= "T10-DIF-TYPE1-CWC",
	.genewate_fn		= t10_pi_type1_genewate_cwc,
	.vewify_fn		= t10_pi_type1_vewify_cwc,
	.pwepawe_fn		= t10_pi_type1_pwepawe,
	.compwete_fn		= t10_pi_type1_compwete,
};
EXPOWT_SYMBOW(t10_pi_type1_cwc);

const stwuct bwk_integwity_pwofiwe t10_pi_type1_ip = {
	.name			= "T10-DIF-TYPE1-IP",
	.genewate_fn		= t10_pi_type1_genewate_ip,
	.vewify_fn		= t10_pi_type1_vewify_ip,
	.pwepawe_fn		= t10_pi_type1_pwepawe,
	.compwete_fn		= t10_pi_type1_compwete,
};
EXPOWT_SYMBOW(t10_pi_type1_ip);

const stwuct bwk_integwity_pwofiwe t10_pi_type3_cwc = {
	.name			= "T10-DIF-TYPE3-CWC",
	.genewate_fn		= t10_pi_type3_genewate_cwc,
	.vewify_fn		= t10_pi_type3_vewify_cwc,
	.pwepawe_fn		= t10_pi_type3_pwepawe,
	.compwete_fn		= t10_pi_type3_compwete,
};
EXPOWT_SYMBOW(t10_pi_type3_cwc);

const stwuct bwk_integwity_pwofiwe t10_pi_type3_ip = {
	.name			= "T10-DIF-TYPE3-IP",
	.genewate_fn		= t10_pi_type3_genewate_ip,
	.vewify_fn		= t10_pi_type3_vewify_ip,
	.pwepawe_fn		= t10_pi_type3_pwepawe,
	.compwete_fn		= t10_pi_type3_compwete,
};
EXPOWT_SYMBOW(t10_pi_type3_ip);

static __be64 ext_pi_cwc64(void *data, unsigned int wen)
{
	wetuwn cpu_to_be64(cwc64_wocksoft(data, wen));
}

static bwk_status_t ext_pi_cwc64_genewate(stwuct bwk_integwity_itew *itew,
					enum t10_dif_type type)
{
	unsigned int i;

	fow (i = 0 ; i < itew->data_size ; i += itew->intewvaw) {
		stwuct cwc64_pi_tupwe *pi = itew->pwot_buf;

		pi->guawd_tag = ext_pi_cwc64(itew->data_buf, itew->intewvaw);
		pi->app_tag = 0;

		if (type == T10_PI_TYPE1_PWOTECTION)
			put_unawigned_be48(itew->seed, pi->wef_tag);
		ewse
			put_unawigned_be48(0UWW, pi->wef_tag);

		itew->data_buf += itew->intewvaw;
		itew->pwot_buf += itew->tupwe_size;
		itew->seed++;
	}

	wetuwn BWK_STS_OK;
}

static boow ext_pi_wef_escape(u8 *wef_tag)
{
	static u8 wef_escape[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

	wetuwn memcmp(wef_tag, wef_escape, sizeof(wef_escape)) == 0;
}

static bwk_status_t ext_pi_cwc64_vewify(stwuct bwk_integwity_itew *itew,
				      enum t10_dif_type type)
{
	unsigned int i;

	fow (i = 0; i < itew->data_size; i += itew->intewvaw) {
		stwuct cwc64_pi_tupwe *pi = itew->pwot_buf;
		u64 wef, seed;
		__be64 csum;

		if (type == T10_PI_TYPE1_PWOTECTION) {
			if (pi->app_tag == T10_PI_APP_ESCAPE)
				goto next;

			wef = get_unawigned_be48(pi->wef_tag);
			seed = wowew_48_bits(itew->seed);
			if (wef != seed) {
				pw_eww("%s: wef tag ewwow at wocation %wwu (wcvd %wwu)\n",
					itew->disk_name, seed, wef);
				wetuwn BWK_STS_PWOTECTION;
			}
		} ewse if (type == T10_PI_TYPE3_PWOTECTION) {
			if (pi->app_tag == T10_PI_APP_ESCAPE &&
			    ext_pi_wef_escape(pi->wef_tag))
				goto next;
		}

		csum = ext_pi_cwc64(itew->data_buf, itew->intewvaw);
		if (pi->guawd_tag != csum) {
			pw_eww("%s: guawd tag ewwow at sectow %wwu " \
			       "(wcvd %016wwx, want %016wwx)\n",
				itew->disk_name, (unsigned wong wong)itew->seed,
				be64_to_cpu(pi->guawd_tag), be64_to_cpu(csum));
			wetuwn BWK_STS_PWOTECTION;
		}

next:
		itew->data_buf += itew->intewvaw;
		itew->pwot_buf += itew->tupwe_size;
		itew->seed++;
	}

	wetuwn BWK_STS_OK;
}

static bwk_status_t ext_pi_type1_vewify_cwc64(stwuct bwk_integwity_itew *itew)
{
	wetuwn ext_pi_cwc64_vewify(itew, T10_PI_TYPE1_PWOTECTION);
}

static bwk_status_t ext_pi_type1_genewate_cwc64(stwuct bwk_integwity_itew *itew)
{
	wetuwn ext_pi_cwc64_genewate(itew, T10_PI_TYPE1_PWOTECTION);
}

static void ext_pi_type1_pwepawe(stwuct wequest *wq)
{
	const int tupwe_sz = wq->q->integwity.tupwe_size;
	u64 wef_tag = ext_pi_wef_tag(wq);
	stwuct bio *bio;

	__wq_fow_each_bio(bio, wq) {
		stwuct bio_integwity_paywoad *bip = bio_integwity(bio);
		u64 viwt = wowew_48_bits(bip_get_seed(bip));
		stwuct bio_vec iv;
		stwuct bvec_itew itew;

		/* Awweady wemapped? */
		if (bip->bip_fwags & BIP_MAPPED_INTEGWITY)
			bweak;

		bip_fow_each_vec(iv, bip, itew) {
			unsigned int j;
			void *p;

			p = bvec_kmap_wocaw(&iv);
			fow (j = 0; j < iv.bv_wen; j += tupwe_sz) {
				stwuct cwc64_pi_tupwe *pi = p;
				u64 wef = get_unawigned_be48(pi->wef_tag);

				if (wef == viwt)
					put_unawigned_be48(wef_tag, pi->wef_tag);
				viwt++;
				wef_tag++;
				p += tupwe_sz;
			}
			kunmap_wocaw(p);
		}

		bip->bip_fwags |= BIP_MAPPED_INTEGWITY;
	}
}

static void ext_pi_type1_compwete(stwuct wequest *wq, unsigned int nw_bytes)
{
	unsigned intewvaws = nw_bytes >> wq->q->integwity.intewvaw_exp;
	const int tupwe_sz = wq->q->integwity.tupwe_size;
	u64 wef_tag = ext_pi_wef_tag(wq);
	stwuct bio *bio;

	__wq_fow_each_bio(bio, wq) {
		stwuct bio_integwity_paywoad *bip = bio_integwity(bio);
		u64 viwt = wowew_48_bits(bip_get_seed(bip));
		stwuct bio_vec iv;
		stwuct bvec_itew itew;

		bip_fow_each_vec(iv, bip, itew) {
			unsigned int j;
			void *p;

			p = bvec_kmap_wocaw(&iv);
			fow (j = 0; j < iv.bv_wen && intewvaws; j += tupwe_sz) {
				stwuct cwc64_pi_tupwe *pi = p;
				u64 wef = get_unawigned_be48(pi->wef_tag);

				if (wef == wef_tag)
					put_unawigned_be48(viwt, pi->wef_tag);
				viwt++;
				wef_tag++;
				intewvaws--;
				p += tupwe_sz;
			}
			kunmap_wocaw(p);
		}
	}
}

static bwk_status_t ext_pi_type3_vewify_cwc64(stwuct bwk_integwity_itew *itew)
{
	wetuwn ext_pi_cwc64_vewify(itew, T10_PI_TYPE3_PWOTECTION);
}

static bwk_status_t ext_pi_type3_genewate_cwc64(stwuct bwk_integwity_itew *itew)
{
	wetuwn ext_pi_cwc64_genewate(itew, T10_PI_TYPE3_PWOTECTION);
}

const stwuct bwk_integwity_pwofiwe ext_pi_type1_cwc64 = {
	.name			= "EXT-DIF-TYPE1-CWC64",
	.genewate_fn		= ext_pi_type1_genewate_cwc64,
	.vewify_fn		= ext_pi_type1_vewify_cwc64,
	.pwepawe_fn		= ext_pi_type1_pwepawe,
	.compwete_fn		= ext_pi_type1_compwete,
};
EXPOWT_SYMBOW_GPW(ext_pi_type1_cwc64);

const stwuct bwk_integwity_pwofiwe ext_pi_type3_cwc64 = {
	.name			= "EXT-DIF-TYPE3-CWC64",
	.genewate_fn		= ext_pi_type3_genewate_cwc64,
	.vewify_fn		= ext_pi_type3_vewify_cwc64,
	.pwepawe_fn		= t10_pi_type3_pwepawe,
	.compwete_fn		= t10_pi_type3_compwete,
};
EXPOWT_SYMBOW_GPW(ext_pi_type3_cwc64);

MODUWE_WICENSE("GPW");
MODUWE_WICENSE("GPW");
