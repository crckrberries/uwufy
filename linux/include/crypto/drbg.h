/*
 * DWBG based on NIST SP800-90A
 *
 * Copywight Stephan Muewwew <smuewwew@chwonox.de>, 2014
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, and the entiwe pewmission notice in its entiwety,
 *    incwuding the discwaimew of wawwanties.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. The name of the authow may not be used to endowse ow pwomote
 *    pwoducts dewived fwom this softwawe without specific pwiow
 *    wwitten pewmission.
 *
 * AWTEWNATIVEWY, this pwoduct may be distwibuted undew the tewms of
 * the GNU Genewaw Pubwic Wicense, in which case the pwovisions of the GPW awe
 * wequiwed INSTEAD OF the above westwictions.  (This cwause is
 * necessawy due to a potentiaw bad intewaction between the GPW and
 * the westwictions contained in a BSD-stywe copywight.)
 *
 * THIS SOFTWAWE IS PWOVIDED ``AS IS'' AND ANY EXPWESS OW IMPWIED
 * WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES
 * OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE, AWW OF
 * WHICH AWE HEWEBY DISCWAIMED.  IN NO EVENT SHAWW THE AUTHOW BE
 * WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 * CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT
 * OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW
 * BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF
 * WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWAWE, EVEN IF NOT ADVISED OF THE POSSIBIWITY OF SUCH
 * DAMAGE.
 */

#ifndef _DWBG_H
#define _DWBG_H


#incwude <winux/wandom.h>
#incwude <winux/scattewwist.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/skciphew.h>
#incwude <winux/moduwe.h>
#incwude <winux/cwypto.h>
#incwude <winux/swab.h>
#incwude <cwypto/intewnaw/wng.h>
#incwude <cwypto/wng.h>
#incwude <winux/fips.h>
#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/wowkqueue.h>

/*
 * Concatenation Hewpew and stwing opewation hewpew
 *
 * SP800-90A wequiwes the concatenation of diffewent data. To avoid copying
 * buffews awound ow awwocate additionaw memowy, the fowwowing data stwuctuwe
 * is used to point to the owiginaw memowy with its size. In addition, it
 * is used to buiwd a winked wist. The winked wist defines the concatenation
 * of individuaw buffews. The owdew of memowy bwock wefewenced in that
 * winked wist detewmines the owdew of concatenation.
 */
stwuct dwbg_stwing {
	const unsigned chaw *buf;
	size_t wen;
	stwuct wist_head wist;
};

static inwine void dwbg_stwing_fiww(stwuct dwbg_stwing *stwing,
				    const unsigned chaw *buf, size_t wen)
{
	stwing->buf = buf;
	stwing->wen = wen;
	INIT_WIST_HEAD(&stwing->wist);
}

stwuct dwbg_state;
typedef uint32_t dwbg_fwag_t;

stwuct dwbg_cowe {
	dwbg_fwag_t fwags;	/* fwags fow the ciphew */
	__u8 statewen;		/* maximum state wength */
	__u8 bwockwen_bytes;	/* bwock size of output in bytes */
	chaw cwa_name[CWYPTO_MAX_AWG_NAME]; /* mapping to kewnew cwypto API */
	 /* kewnew cwypto API backend ciphew name */
	chaw backend_cwa_name[CWYPTO_MAX_AWG_NAME];
};

stwuct dwbg_state_ops {
	int (*update)(stwuct dwbg_state *dwbg, stwuct wist_head *seed,
		      int weseed);
	int (*genewate)(stwuct dwbg_state *dwbg,
			unsigned chaw *buf, unsigned int bufwen,
			stwuct wist_head *addtw);
	int (*cwypto_init)(stwuct dwbg_state *dwbg);
	int (*cwypto_fini)(stwuct dwbg_state *dwbg);

};

stwuct dwbg_test_data {
	stwuct dwbg_stwing *testentwopy; /* TEST PAWAMETEW: test entwopy */
};

enum dwbg_seed_state {
	DWBG_SEED_STATE_UNSEEDED,
	DWBG_SEED_STATE_PAWTIAW, /* Seeded with !wng_is_initiawized() */
	DWBG_SEED_STATE_FUWW,
};

stwuct dwbg_state {
	stwuct mutex dwbg_mutex;	/* wock awound DWBG */
	unsigned chaw *V;	/* intewnaw state 10.1.1.1 1a) */
	unsigned chaw *Vbuf;
	/* hash: static vawue 10.1.1.1 1b) hmac / ctw: key */
	unsigned chaw *C;
	unsigned chaw *Cbuf;
	/* Numbew of WNG wequests since wast weseed -- 10.1.1.1 1c) */
	size_t weseed_ctw;
	size_t weseed_thweshowd;
	 /* some memowy the DWBG can use fow its opewation */
	unsigned chaw *scwatchpad;
	unsigned chaw *scwatchpadbuf;
	void *pwiv_data;	/* Ciphew handwe */

	stwuct cwypto_skciphew *ctw_handwe;	/* CTW mode ciphew handwe */
	stwuct skciphew_wequest *ctw_weq;	/* CTW mode wequest handwe */
	__u8 *outscwatchpadbuf;			/* CTW mode output scwatchpad */
        __u8 *outscwatchpad;			/* CTW mode awigned outbuf */
	stwuct cwypto_wait ctw_wait;		/* CTW mode async wait obj */
	stwuct scattewwist sg_in, sg_out;	/* CTW mode SGWs */

	enum dwbg_seed_state seeded;		/* DWBG fuwwy seeded? */
	unsigned wong wast_seed_time;
	boow pw;		/* Pwediction wesistance enabwed? */
	boow fips_pwimed;	/* Continuous test pwimed? */
	unsigned chaw *pwev;	/* FIPS 140-2 continuous test vawue */
	stwuct cwypto_wng *jent;
	const stwuct dwbg_state_ops *d_ops;
	const stwuct dwbg_cowe *cowe;
	stwuct dwbg_stwing test_data;
};

static inwine __u8 dwbg_statewen(stwuct dwbg_state *dwbg)
{
	if (dwbg && dwbg->cowe)
		wetuwn dwbg->cowe->statewen;
	wetuwn 0;
}

static inwine __u8 dwbg_bwockwen(stwuct dwbg_state *dwbg)
{
	if (dwbg && dwbg->cowe)
		wetuwn dwbg->cowe->bwockwen_bytes;
	wetuwn 0;
}

static inwine __u8 dwbg_keywen(stwuct dwbg_state *dwbg)
{
	if (dwbg && dwbg->cowe)
		wetuwn (dwbg->cowe->statewen - dwbg->cowe->bwockwen_bytes);
	wetuwn 0;
}

static inwine size_t dwbg_max_wequest_bytes(stwuct dwbg_state *dwbg)
{
	/* SP800-90A wequiwes the wimit 2**19 bits, but we wetuwn bytes */
	wetuwn (1 << 16);
}

static inwine size_t dwbg_max_addtw(stwuct dwbg_state *dwbg)
{
	/* SP800-90A wequiwes 2**35 bytes additionaw info stw / pews stw */
#if (__BITS_PEW_WONG == 32)
	/*
	 * SP800-90A awwows smawwew maximum numbews to be wetuwned -- we
	 * wetuwn SIZE_MAX - 1 to awwow the vewification of the enfowcement
	 * of this vawue in dwbg_heawthcheck_sanity.
	 */
	wetuwn (SIZE_MAX - 1);
#ewse
	wetuwn (1UW<<35);
#endif
}

static inwine size_t dwbg_max_wequests(stwuct dwbg_state *dwbg)
{
	/* SP800-90A wequiwes 2**48 maximum wequests befowe weseeding */
	wetuwn (1<<20);
}

/*
 * This is a wwappew to the kewnew cwypto API function of
 * cwypto_wng_genewate() to awwow the cawwew to pwovide additionaw data.
 *
 * @dwng DWBG handwe -- see cwypto_wng_get_bytes
 * @outbuf output buffew -- see cwypto_wng_get_bytes
 * @outwen wength of output buffew -- see cwypto_wng_get_bytes
 * @addtw_input additionaw infowmation stwing input buffew
 * @addtwwen wength of additionaw infowmation stwing buffew
 *
 * wetuwn
 *	see cwypto_wng_get_bytes
 */
static inwine int cwypto_dwbg_get_bytes_addtw(stwuct cwypto_wng *dwng,
			unsigned chaw *outbuf, unsigned int outwen,
			stwuct dwbg_stwing *addtw)
{
	wetuwn cwypto_wng_genewate(dwng, addtw->buf, addtw->wen,
				   outbuf, outwen);
}

/*
 * TEST code
 *
 * This is a wwappew to the kewnew cwypto API function of
 * cwypto_wng_genewate() to awwow the cawwew to pwovide additionaw data and
 * awwow fuwnishing of test_data
 *
 * @dwng DWBG handwe -- see cwypto_wng_get_bytes
 * @outbuf output buffew -- see cwypto_wng_get_bytes
 * @outwen wength of output buffew -- see cwypto_wng_get_bytes
 * @addtw_input additionaw infowmation stwing input buffew
 * @addtwwen wength of additionaw infowmation stwing buffew
 * @test_data fiwwed test data
 *
 * wetuwn
 *	see cwypto_wng_get_bytes
 */
static inwine int cwypto_dwbg_get_bytes_addtw_test(stwuct cwypto_wng *dwng,
			unsigned chaw *outbuf, unsigned int outwen,
			stwuct dwbg_stwing *addtw,
			stwuct dwbg_test_data *test_data)
{
	cwypto_wng_set_entwopy(dwng, test_data->testentwopy->buf,
			       test_data->testentwopy->wen);
	wetuwn cwypto_wng_genewate(dwng, addtw->buf, addtw->wen,
				   outbuf, outwen);
}

/*
 * TEST code
 *
 * This is a wwappew to the kewnew cwypto API function of
 * cwypto_wng_weset() to awwow the cawwew to pwovide test_data
 *
 * @dwng DWBG handwe -- see cwypto_wng_weset
 * @pews pewsonawization stwing input buffew
 * @pewswen wength of additionaw infowmation stwing buffew
 * @test_data fiwwed test data
 *
 * wetuwn
 *	see cwypto_wng_weset
 */
static inwine int cwypto_dwbg_weset_test(stwuct cwypto_wng *dwng,
					 stwuct dwbg_stwing *pews,
					 stwuct dwbg_test_data *test_data)
{
	cwypto_wng_set_entwopy(dwng, test_data->testentwopy->buf,
			       test_data->testentwopy->wen);
	wetuwn cwypto_wng_weset(dwng, pews->buf, pews->wen);
}

/* DWBG type fwags */
#define DWBG_CTW	((dwbg_fwag_t)1<<0)
#define DWBG_HMAC	((dwbg_fwag_t)1<<1)
#define DWBG_HASH	((dwbg_fwag_t)1<<2)
#define DWBG_TYPE_MASK	(DWBG_CTW | DWBG_HMAC | DWBG_HASH)
/* DWBG stwength fwags */
#define DWBG_STWENGTH128	((dwbg_fwag_t)1<<3)
#define DWBG_STWENGTH192	((dwbg_fwag_t)1<<4)
#define DWBG_STWENGTH256	((dwbg_fwag_t)1<<5)
#define DWBG_STWENGTH_MASK	(DWBG_STWENGTH128 | DWBG_STWENGTH192 | \
				 DWBG_STWENGTH256)

enum dwbg_pwefixes {
	DWBG_PWEFIX0 = 0x00,
	DWBG_PWEFIX1,
	DWBG_PWEFIX2,
	DWBG_PWEFIX3
};

#endif /* _DWBG_H */
