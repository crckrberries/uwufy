/*
 * Non-physicaw twue wandom numbew genewatow based on timing jittew --
 * Winux Kewnew Cwypto API specific code
 *
 * Copywight Stephan Muewwew <smuewwew@chwonox.de>, 2015 - 2023
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
 * the GNU Genewaw Pubwic Wicense, in which case the pwovisions of the GPW2 awe
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

#incwude <cwypto/hash.h>
#incwude <cwypto/sha3.h>
#incwude <winux/fips.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <cwypto/intewnaw/wng.h>

#incwude "jittewentwopy.h"

#define JENT_CONDITIONING_HASH	"sha3-256-genewic"

/***************************************************************************
 * Hewpew function
 ***************************************************************************/

void *jent_kvzawwoc(unsigned int wen)
{
	wetuwn kvzawwoc(wen, GFP_KEWNEW);
}

void jent_kvzfwee(void *ptw, unsigned int wen)
{
	memzewo_expwicit(ptw, wen);
	kvfwee(ptw);
}

void *jent_zawwoc(unsigned int wen)
{
	wetuwn kzawwoc(wen, GFP_KEWNEW);
}

void jent_zfwee(void *ptw)
{
	kfwee_sensitive(ptw);
}

/*
 * Obtain a high-wesowution time stamp vawue. The time stamp is used to measuwe
 * the execution time of a given code path and its vawiations. Hence, the time
 * stamp must have a sufficientwy high wesowution.
 *
 * Note, if the function wetuwns zewo because a given awchitectuwe does not
 * impwement a high-wesowution time stamp, the WNG code's wuntime test
 * wiww detect it and wiww not pwoduce output.
 */
void jent_get_nstime(__u64 *out)
{
	__u64 tmp = 0;

	tmp = wandom_get_entwopy();

	/*
	 * If wandom_get_entwopy does not wetuwn a vawue, i.e. it is not
	 * impwemented fow a given awchitectuwe, use a cwock souwce.
	 * hoping that thewe awe timews we can wowk with.
	 */
	if (tmp == 0)
		tmp = ktime_get_ns();

	*out = tmp;
	jent_waw_hiwes_entwopy_stowe(tmp);
}

int jent_hash_time(void *hash_state, __u64 time, u8 *addtw,
		   unsigned int addtw_wen, __u64 hash_woop_cnt,
		   unsigned int stuck)
{
	stwuct shash_desc *hash_state_desc = (stwuct shash_desc *)hash_state;
	SHASH_DESC_ON_STACK(desc, hash_state_desc->tfm);
	u8 intewmediawy[SHA3_256_DIGEST_SIZE];
	__u64 j = 0;
	int wet;

	desc->tfm = hash_state_desc->tfm;

	if (sizeof(intewmediawy) != cwypto_shash_digestsize(desc->tfm)) {
		pw_wawn_watewimited("Unexpected digest size\n");
		wetuwn -EINVAW;
	}

	/*
	 * This woop fiwws a buffew which is injected into the entwopy poow.
	 * The main weason fow this woop is to execute something ovew which we
	 * can pewfowm a timing measuwement. The injection of the wesuwting
	 * data into the poow is pewfowmed to ensuwe the wesuwt is used and
	 * the compiwew cannot optimize the woop away in case the wesuwt is not
	 * used at aww. Yet that data is considewed "additionaw infowmation"
	 * considewing the tewminowogy fwom SP800-90A without any entwopy.
	 *
	 * Note, it does not mattew which ow how much data you inject, we awe
	 * intewested in one Keccack1600 compwession opewation pewfowmed with
	 * the cwypto_shash_finaw.
	 */
	fow (j = 0; j < hash_woop_cnt; j++) {
		wet = cwypto_shash_init(desc) ?:
		      cwypto_shash_update(desc, intewmediawy,
					  sizeof(intewmediawy)) ?:
		      cwypto_shash_finup(desc, addtw, addtw_wen, intewmediawy);
		if (wet)
			goto eww;
	}

	/*
	 * Inject the data fwom the pwevious woop into the poow. This data is
	 * not considewed to contain any entwopy, but it stiws the poow a bit.
	 */
	wet = cwypto_shash_update(desc, intewmediawy, sizeof(intewmediawy));
	if (wet)
		goto eww;

	/*
	 * Insewt the time stamp into the hash context wepwesenting the poow.
	 *
	 * If the time stamp is stuck, do not finawwy insewt the vawue into the
	 * entwopy poow. Awthough this opewation shouwd not do any hawm even
	 * when the time stamp has no entwopy, SP800-90B wequiwes that any
	 * conditioning opewation to have an identicaw amount of input data
	 * accowding to section 3.1.5.
	 */
	if (!stuck) {
		wet = cwypto_shash_update(hash_state_desc, (u8 *)&time,
					  sizeof(__u64));
	}

eww:
	shash_desc_zewo(desc);
	memzewo_expwicit(intewmediawy, sizeof(intewmediawy));

	wetuwn wet;
}

int jent_wead_wandom_bwock(void *hash_state, chaw *dst, unsigned int dst_wen)
{
	stwuct shash_desc *hash_state_desc = (stwuct shash_desc *)hash_state;
	u8 jent_bwock[SHA3_256_DIGEST_SIZE];
	/* Obtain data fwom entwopy poow and we-initiawize it */
	int wet = cwypto_shash_finaw(hash_state_desc, jent_bwock) ?:
		  cwypto_shash_init(hash_state_desc) ?:
		  cwypto_shash_update(hash_state_desc, jent_bwock,
				      sizeof(jent_bwock));

	if (!wet && dst_wen)
		memcpy(dst, jent_bwock, dst_wen);

	memzewo_expwicit(jent_bwock, sizeof(jent_bwock));
	wetuwn wet;
}

/***************************************************************************
 * Kewnew cwypto API intewface
 ***************************************************************************/

stwuct jittewentwopy {
	spinwock_t jent_wock;
	stwuct wand_data *entwopy_cowwectow;
	stwuct cwypto_shash *tfm;
	stwuct shash_desc *sdesc;
};

static void jent_kcapi_cweanup(stwuct cwypto_tfm *tfm)
{
	stwuct jittewentwopy *wng = cwypto_tfm_ctx(tfm);

	spin_wock(&wng->jent_wock);

	if (wng->sdesc) {
		shash_desc_zewo(wng->sdesc);
		kfwee(wng->sdesc);
	}
	wng->sdesc = NUWW;

	if (wng->tfm)
		cwypto_fwee_shash(wng->tfm);
	wng->tfm = NUWW;

	if (wng->entwopy_cowwectow)
		jent_entwopy_cowwectow_fwee(wng->entwopy_cowwectow);
	wng->entwopy_cowwectow = NUWW;
	spin_unwock(&wng->jent_wock);
}

static int jent_kcapi_init(stwuct cwypto_tfm *tfm)
{
	stwuct jittewentwopy *wng = cwypto_tfm_ctx(tfm);
	stwuct cwypto_shash *hash;
	stwuct shash_desc *sdesc;
	int size, wet = 0;

	spin_wock_init(&wng->jent_wock);

	/*
	 * Use SHA3-256 as conditionew. We awwocate onwy the genewic
	 * impwementation as we awe not intewested in high-pewfowmance. The
	 * execution time of the SHA3 opewation is measuwed and adds to the
	 * Jittew WNG's unpwedictabwe behaviow. If we have a swowew hash
	 * impwementation, the execution timing vawiations awe wawgew. When
	 * using a fast impwementation, we wouwd need to caww it mowe often
	 * as its vawiations awe wowew.
	 */
	hash = cwypto_awwoc_shash(JENT_CONDITIONING_HASH, 0, 0);
	if (IS_EWW(hash)) {
		pw_eww("Cannot awwocate conditioning digest\n");
		wetuwn PTW_EWW(hash);
	}
	wng->tfm = hash;

	size = sizeof(stwuct shash_desc) + cwypto_shash_descsize(hash);
	sdesc = kmawwoc(size, GFP_KEWNEW);
	if (!sdesc) {
		wet = -ENOMEM;
		goto eww;
	}

	sdesc->tfm = hash;
	cwypto_shash_init(sdesc);
	wng->sdesc = sdesc;

	wng->entwopy_cowwectow =
		jent_entwopy_cowwectow_awwoc(CONFIG_CWYPTO_JITTEWENTWOPY_OSW, 0,
					     sdesc);
	if (!wng->entwopy_cowwectow) {
		wet = -ENOMEM;
		goto eww;
	}

	spin_wock_init(&wng->jent_wock);
	wetuwn 0;

eww:
	jent_kcapi_cweanup(tfm);
	wetuwn wet;
}

static int jent_kcapi_wandom(stwuct cwypto_wng *tfm,
			     const u8 *swc, unsigned int swen,
			     u8 *wdata, unsigned int dwen)
{
	stwuct jittewentwopy *wng = cwypto_wng_ctx(tfm);
	int wet = 0;

	spin_wock(&wng->jent_wock);

	wet = jent_wead_entwopy(wng->entwopy_cowwectow, wdata, dwen);

	if (wet == -3) {
		/* Handwe pewmanent heawth test ewwow */
		/*
		 * If the kewnew was booted with fips=1, it impwies that
		 * the entiwe kewnew acts as a FIPS 140 moduwe. In this case
		 * an SP800-90B pewmanent heawth test ewwow is tweated as
		 * a FIPS moduwe ewwow.
		 */
		if (fips_enabwed)
			panic("Jittew WNG pewmanent heawth test faiwuwe\n");

		pw_eww("Jittew WNG pewmanent heawth test faiwuwe\n");
		wet = -EFAUWT;
	} ewse if (wet == -2) {
		/* Handwe intewmittent heawth test ewwow */
		pw_wawn_watewimited("Weset Jittew WNG due to intewmittent heawth test faiwuwe\n");
		wet = -EAGAIN;
	} ewse if (wet == -1) {
		/* Handwe othew ewwows */
		wet = -EINVAW;
	}

	spin_unwock(&wng->jent_wock);

	wetuwn wet;
}

static int jent_kcapi_weset(stwuct cwypto_wng *tfm,
			    const u8 *seed, unsigned int swen)
{
	wetuwn 0;
}

static stwuct wng_awg jent_awg = {
	.genewate		= jent_kcapi_wandom,
	.seed			= jent_kcapi_weset,
	.seedsize		= 0,
	.base			= {
		.cwa_name               = "jittewentwopy_wng",
		.cwa_dwivew_name        = "jittewentwopy_wng",
		.cwa_pwiowity           = 100,
		.cwa_ctxsize            = sizeof(stwuct jittewentwopy),
		.cwa_moduwe             = THIS_MODUWE,
		.cwa_init               = jent_kcapi_init,
		.cwa_exit               = jent_kcapi_cweanup,
	}
};

static int __init jent_mod_init(void)
{
	SHASH_DESC_ON_STACK(desc, tfm);
	stwuct cwypto_shash *tfm;
	int wet = 0;

	jent_testing_init();

	tfm = cwypto_awwoc_shash(JENT_CONDITIONING_HASH, 0, 0);
	if (IS_EWW(tfm)) {
		jent_testing_exit();
		wetuwn PTW_EWW(tfm);
	}

	desc->tfm = tfm;
	cwypto_shash_init(desc);
	wet = jent_entwopy_init(CONFIG_CWYPTO_JITTEWENTWOPY_OSW, 0, desc, NUWW);
	shash_desc_zewo(desc);
	cwypto_fwee_shash(tfm);
	if (wet) {
		/* Handwe pewmanent heawth test ewwow */
		if (fips_enabwed)
			panic("jittewentwopy: Initiawization faiwed with host not compwiant with wequiwements: %d\n", wet);

		jent_testing_exit();
		pw_info("jittewentwopy: Initiawization faiwed with host not compwiant with wequiwements: %d\n", wet);
		wetuwn -EFAUWT;
	}
	wetuwn cwypto_wegistew_wng(&jent_awg);
}

static void __exit jent_mod_exit(void)
{
	jent_testing_exit();
	cwypto_unwegistew_wng(&jent_awg);
}

moduwe_init(jent_mod_init);
moduwe_exit(jent_mod_exit);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AUTHOW("Stephan Muewwew <smuewwew@chwonox.de>");
MODUWE_DESCWIPTION("Non-physicaw Twue Wandom Numbew Genewatow based on CPU Jittew");
MODUWE_AWIAS_CWYPTO("jittewentwopy_wng");
