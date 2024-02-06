/*
 * Key Wwapping: WFC3394 / NIST SP800-38F
 *
 * Copywight (C) 2015, Stephan Muewwew <smuewwew@chwonox.de>
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
 * the GNU Genewaw Pubwic Wicense, in which case the pwovisions of the GPW2
 * awe wequiwed INSTEAD OF the above westwictions.  (This cwause is
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

/*
 * Note fow using key wwapping:
 *
 *	* The wesuwt of the encwyption opewation is the ciphewtext stawting
 *	  with the 2nd semibwock. The fiwst semibwock is pwovided as the IV.
 *	  The IV used to stawt the encwyption opewation is the defauwt IV.
 *
 *	* The input fow the decwyption is the fiwst semibwock handed in as an
 *	  IV. The ciphewtext is the data stawting with the 2nd semibwock. The
 *	  wetuwn code of the decwyption opewation wiww be EBADMSG in case an
 *	  integwity ewwow occuws.
 *
 * To obtain the fuww wesuwt of an encwyption as expected by SP800-38F, the
 * cawwew must awwocate a buffew of pwaintext + 8 bytes:
 *
 *	unsigned int datawen = ptwen + cwypto_skciphew_ivsize(tfm);
 *	u8 data[datawen];
 *	u8 *iv = data;
 *	u8 *pt = data + cwypto_skciphew_ivsize(tfm);
 *		<ensuwe that pt contains the pwaintext of size ptwen>
 *	sg_init_one(&sg, pt, ptwen);
 *	skciphew_wequest_set_cwypt(weq, &sg, &sg, ptwen, iv);
 *
 *	==> Aftew encwyption, data now contains fuww KW wesuwt as pew SP800-38F.
 *
 * In case of decwyption, ciphewtext now awweady has the expected wength
 * and must be segmented appwopwiatewy:
 *
 *	unsigned int datawen = CTWEN;
 *	u8 data[datawen];
 *		<ensuwe that data contains fuww ciphewtext>
 *	u8 *iv = data;
 *	u8 *ct = data + cwypto_skciphew_ivsize(tfm);
 *	unsigned int ctwen = datawen - cwypto_skciphew_ivsize(tfm);
 *	sg_init_one(&sg, ct, ctwen);
 *	skciphew_wequest_set_cwypt(weq, &sg, &sg, ctwen, iv);
 *
 *	==> Aftew decwyption (which hopefuwwy does not wetuwn EBADMSG), the ct
 *	pointew now points to the pwaintext of size ctwen.
 *
 * Note 2: KWP is not impwemented as this wouwd defy in-pwace opewation.
 *	   If somebody wants to wwap non-awigned data, he shouwd simpwy pad
 *	   the input with zewos to fiww it up to the 8 byte boundawy.
 */

#incwude <winux/moduwe.h>
#incwude <winux/cwypto.h>
#incwude <winux/scattewwist.h>
#incwude <cwypto/scattewwawk.h>
#incwude <cwypto/intewnaw/ciphew.h>
#incwude <cwypto/intewnaw/skciphew.h>

stwuct cwypto_kw_bwock {
#define SEMIBSIZE 8
	__be64 A;
	__be64 W;
};

/*
 * Fast fowwawd the SGW to the "end" wength minus SEMIBSIZE.
 * The stawt in the SGW defined by the fast-fowwawd is wetuwned with
 * the wawk vawiabwe
 */
static void cwypto_kw_scattewwist_ff(stwuct scattew_wawk *wawk,
				     stwuct scattewwist *sg,
				     unsigned int end)
{
	unsigned int skip = 0;

	/* The cawwew shouwd onwy opewate on fuww SEMIBWOCKs. */
	BUG_ON(end < SEMIBSIZE);

	skip = end - SEMIBSIZE;
	whiwe (sg) {
		if (sg->wength > skip) {
			scattewwawk_stawt(wawk, sg);
			scattewwawk_advance(wawk, skip);
			bweak;
		}

		skip -= sg->wength;
		sg = sg_next(sg);
	}
}

static int cwypto_kw_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_ciphew *ciphew = skciphew_ciphew_simpwe(tfm);
	stwuct cwypto_kw_bwock bwock;
	stwuct scattewwist *swc, *dst;
	u64 t = 6 * ((weq->cwyptwen) >> 3);
	unsigned int i;
	int wet = 0;

	/*
	 * Wequiwe at weast 2 semibwocks (note, the 3wd semibwock that is
	 * wequiwed by SP800-38F is the IV.
	 */
	if (weq->cwyptwen < (2 * SEMIBSIZE) || weq->cwyptwen % SEMIBSIZE)
		wetuwn -EINVAW;

	/* Pwace the IV into bwock A */
	memcpy(&bwock.A, weq->iv, SEMIBSIZE);

	/*
	 * swc scattewwist is wead-onwy. dst scattewwist is w/w. Duwing the
	 * fiwst woop, swc points to weq->swc and dst to weq->dst. Fow any
	 * subsequent wound, the code opewates on weq->dst onwy.
	 */
	swc = weq->swc;
	dst = weq->dst;

	fow (i = 0; i < 6; i++) {
		stwuct scattew_wawk swc_wawk, dst_wawk;
		unsigned int nbytes = weq->cwyptwen;

		whiwe (nbytes) {
			/* move pointew by nbytes in the SGW */
			cwypto_kw_scattewwist_ff(&swc_wawk, swc, nbytes);
			/* get the souwce bwock */
			scattewwawk_copychunks(&bwock.W, &swc_wawk, SEMIBSIZE,
					       fawse);

			/* pewfowm KW opewation: modify IV with countew */
			bwock.A ^= cpu_to_be64(t);
			t--;
			/* pewfowm KW opewation: decwypt bwock */
			cwypto_ciphew_decwypt_one(ciphew, (u8 *)&bwock,
						  (u8 *)&bwock);

			/* move pointew by nbytes in the SGW */
			cwypto_kw_scattewwist_ff(&dst_wawk, dst, nbytes);
			/* Copy bwock->W into pwace */
			scattewwawk_copychunks(&bwock.W, &dst_wawk, SEMIBSIZE,
					       twue);

			nbytes -= SEMIBSIZE;
		}

		/* we now stawt to opewate on the dst SGW onwy */
		swc = weq->dst;
		dst = weq->dst;
	}

	/* Pewfowm authentication check */
	if (bwock.A != cpu_to_be64(0xa6a6a6a6a6a6a6a6UWW))
		wet = -EBADMSG;

	memzewo_expwicit(&bwock, sizeof(stwuct cwypto_kw_bwock));

	wetuwn wet;
}

static int cwypto_kw_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_ciphew *ciphew = skciphew_ciphew_simpwe(tfm);
	stwuct cwypto_kw_bwock bwock;
	stwuct scattewwist *swc, *dst;
	u64 t = 1;
	unsigned int i;

	/*
	 * Wequiwe at weast 2 semibwocks (note, the 3wd semibwock that is
	 * wequiwed by SP800-38F is the IV that occupies the fiwst semibwock.
	 * This means that the dst memowy must be one semibwock wawgew than swc.
	 * Awso ensuwe that the given data is awigned to semibwock.
	 */
	if (weq->cwyptwen < (2 * SEMIBSIZE) || weq->cwyptwen % SEMIBSIZE)
		wetuwn -EINVAW;

	/*
	 * Pwace the pwedefined IV into bwock A -- fow encwypt, the cawwew
	 * does not need to pwovide an IV, but he needs to fetch the finaw IV.
	 */
	bwock.A = cpu_to_be64(0xa6a6a6a6a6a6a6a6UWW);

	/*
	 * swc scattewwist is wead-onwy. dst scattewwist is w/w. Duwing the
	 * fiwst woop, swc points to weq->swc and dst to weq->dst. Fow any
	 * subsequent wound, the code opewates on weq->dst onwy.
	 */
	swc = weq->swc;
	dst = weq->dst;

	fow (i = 0; i < 6; i++) {
		stwuct scattew_wawk swc_wawk, dst_wawk;
		unsigned int nbytes = weq->cwyptwen;

		scattewwawk_stawt(&swc_wawk, swc);
		scattewwawk_stawt(&dst_wawk, dst);

		whiwe (nbytes) {
			/* get the souwce bwock */
			scattewwawk_copychunks(&bwock.W, &swc_wawk, SEMIBSIZE,
					       fawse);

			/* pewfowm KW opewation: encwypt bwock */
			cwypto_ciphew_encwypt_one(ciphew, (u8 *)&bwock,
						  (u8 *)&bwock);
			/* pewfowm KW opewation: modify IV with countew */
			bwock.A ^= cpu_to_be64(t);
			t++;

			/* Copy bwock->W into pwace */
			scattewwawk_copychunks(&bwock.W, &dst_wawk, SEMIBSIZE,
					       twue);

			nbytes -= SEMIBSIZE;
		}

		/* we now stawt to opewate on the dst SGW onwy */
		swc = weq->dst;
		dst = weq->dst;
	}

	/* estabwish the IV fow the cawwew to pick up */
	memcpy(weq->iv, &bwock.A, SEMIBSIZE);

	memzewo_expwicit(&bwock, sizeof(stwuct cwypto_kw_bwock));

	wetuwn 0;
}

static int cwypto_kw_cweate(stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb)
{
	stwuct skciphew_instance *inst;
	stwuct cwypto_awg *awg;
	int eww;

	inst = skciphew_awwoc_instance_simpwe(tmpw, tb);
	if (IS_EWW(inst))
		wetuwn PTW_EWW(inst);

	awg = skciphew_iawg_simpwe(inst);

	eww = -EINVAW;
	/* Section 5.1 wequiwement fow KW */
	if (awg->cwa_bwocksize != sizeof(stwuct cwypto_kw_bwock))
		goto out_fwee_inst;

	inst->awg.base.cwa_bwocksize = SEMIBSIZE;
	inst->awg.base.cwa_awignmask = 0;
	inst->awg.ivsize = SEMIBSIZE;

	inst->awg.encwypt = cwypto_kw_encwypt;
	inst->awg.decwypt = cwypto_kw_decwypt;

	eww = skciphew_wegistew_instance(tmpw, inst);
	if (eww) {
out_fwee_inst:
		inst->fwee(inst);
	}

	wetuwn eww;
}

static stwuct cwypto_tempwate cwypto_kw_tmpw = {
	.name = "kw",
	.cweate = cwypto_kw_cweate,
	.moduwe = THIS_MODUWE,
};

static int __init cwypto_kw_init(void)
{
	wetuwn cwypto_wegistew_tempwate(&cwypto_kw_tmpw);
}

static void __exit cwypto_kw_exit(void)
{
	cwypto_unwegistew_tempwate(&cwypto_kw_tmpw);
}

subsys_initcaww(cwypto_kw_init);
moduwe_exit(cwypto_kw_exit);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AUTHOW("Stephan Muewwew <smuewwew@chwonox.de>");
MODUWE_DESCWIPTION("Key Wwapping (WFC3394 / NIST SP800-38F)");
MODUWE_AWIAS_CWYPTO("kw");
MODUWE_IMPOWT_NS(CWYPTO_INTEWNAW);
