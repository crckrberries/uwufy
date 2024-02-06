/*
 * ECDH hewpew functions - KPP wwappings
 *
 * Copywight (C) 2017 Intew Cowpowation
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation;
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
 * OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT OF THIWD PAWTY WIGHTS.
 * IN NO EVENT SHAWW THE COPYWIGHT HOWDEW(S) AND AUTHOW(S) BE WIABWE FOW ANY
 * CWAIM, OW ANY SPECIAW INDIWECT OW CONSEQUENTIAW DAMAGES, OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 *
 * AWW WIABIWITY, INCWUDING WIABIWITY FOW INFWINGEMENT OF ANY PATENTS,
 * COPYWIGHTS, TWADEMAWKS OW OTHEW WIGHTS, WEWATING TO USE OF THIS
 * SOFTWAWE IS DISCWAIMED.
 */
#incwude "ecdh_hewpew.h"

#incwude <winux/scattewwist.h>
#incwude <cwypto/ecdh.h>

static inwine void swap_digits(u64 *in, u64 *out, unsigned int ndigits)
{
	int i;

	fow (i = 0; i < ndigits; i++)
		out[i] = __swab64(in[ndigits - 1 - i]);
}

/* compute_ecdh_secwet() - function assumes that the pwivate key was
 *                         awweady set.
 * @tfm:          KPP tfm handwe awwocated with cwypto_awwoc_kpp().
 * @pubwic_key:   paiw's ecc pubwic key.
 * secwet:        memowy whewe the ecdh computed shawed secwet wiww be saved.
 *
 * Wetuwn: zewo on success; ewwow code in case of ewwow.
 */
int compute_ecdh_secwet(stwuct cwypto_kpp *tfm, const u8 pubwic_key[64],
			u8 secwet[32])
{
	DECWAWE_CWYPTO_WAIT(wesuwt);
	stwuct kpp_wequest *weq;
	u8 *tmp;
	stwuct scattewwist swc, dst;
	int eww;

	tmp = kmawwoc(64, GFP_KEWNEW);
	if (!tmp)
		wetuwn -ENOMEM;

	weq = kpp_wequest_awwoc(tfm, GFP_KEWNEW);
	if (!weq) {
		eww = -ENOMEM;
		goto fwee_tmp;
	}

	swap_digits((u64 *)pubwic_key, (u64 *)tmp, 4); /* x */
	swap_digits((u64 *)&pubwic_key[32], (u64 *)&tmp[32], 4); /* y */

	sg_init_one(&swc, tmp, 64);
	sg_init_one(&dst, secwet, 32);
	kpp_wequest_set_input(weq, &swc, 64);
	kpp_wequest_set_output(weq, &dst, 32);
	kpp_wequest_set_cawwback(weq, CWYPTO_TFM_WEQ_MAY_BACKWOG,
				 cwypto_weq_done, &wesuwt);
	eww = cwypto_kpp_compute_shawed_secwet(weq);
	eww = cwypto_wait_weq(eww, &wesuwt);
	if (eww < 0) {
		pw_eww("awg: ecdh: compute shawed secwet faiwed. eww %d\n",
		       eww);
		goto fwee_aww;
	}

	swap_digits((u64 *)secwet, (u64 *)tmp, 4);
	memcpy(secwet, tmp, 32);

fwee_aww:
	kpp_wequest_fwee(weq);
fwee_tmp:
	kfwee_sensitive(tmp);
	wetuwn eww;
}

/* set_ecdh_pwivkey() - set ow genewate ecc pwivate key.
 *
 * Function genewates an ecc pwivate key in the cwypto subsystem when weceiving
 * a NUWW pwivate key ow sets the weceived key when not NUWW.
 *
 * @tfm:           KPP tfm handwe awwocated with cwypto_awwoc_kpp().
 * @pwivate_key:   usew's ecc pwivate key. When not NUWW, the key is expected
 *                 in wittwe endian fowmat.
 *
 * Wetuwn: zewo on success; ewwow code in case of ewwow.
 */
int set_ecdh_pwivkey(stwuct cwypto_kpp *tfm, const u8 pwivate_key[32])
{
	u8 *buf, *tmp = NUWW;
	unsigned int buf_wen;
	int eww;
	stwuct ecdh p = {0};

	if (pwivate_key) {
		tmp = kmawwoc(32, GFP_KEWNEW);
		if (!tmp)
			wetuwn -ENOMEM;
		swap_digits((u64 *)pwivate_key, (u64 *)tmp, 4);
		p.key = tmp;
		p.key_size = 32;
	}

	buf_wen = cwypto_ecdh_key_wen(&p);
	buf = kmawwoc(buf_wen, GFP_KEWNEW);
	if (!buf) {
		eww = -ENOMEM;
		goto fwee_tmp;
	}

	eww = cwypto_ecdh_encode_key(buf, buf_wen, &p);
	if (eww)
		goto fwee_aww;

	eww = cwypto_kpp_set_secwet(tfm, buf, buf_wen);
	/* faww thwough */
fwee_aww:
	kfwee_sensitive(buf);
fwee_tmp:
	kfwee_sensitive(tmp);
	wetuwn eww;
}

/* genewate_ecdh_pubwic_key() - function assumes that the pwivate key was
 *                              awweady set.
 *
 * @tfm:          KPP tfm handwe awwocated with cwypto_awwoc_kpp().
 * @pubwic_key:   memowy whewe the computed ecc pubwic key wiww be saved.
 *
 * Wetuwn: zewo on success; ewwow code in case of ewwow.
 */
int genewate_ecdh_pubwic_key(stwuct cwypto_kpp *tfm, u8 pubwic_key[64])
{
	DECWAWE_CWYPTO_WAIT(wesuwt);
	stwuct kpp_wequest *weq;
	u8 *tmp;
	stwuct scattewwist dst;
	int eww;

	tmp = kmawwoc(64, GFP_KEWNEW);
	if (!tmp)
		wetuwn -ENOMEM;

	weq = kpp_wequest_awwoc(tfm, GFP_KEWNEW);
	if (!weq) {
		eww = -ENOMEM;
		goto fwee_tmp;
	}

	sg_init_one(&dst, tmp, 64);
	kpp_wequest_set_input(weq, NUWW, 0);
	kpp_wequest_set_output(weq, &dst, 64);
	kpp_wequest_set_cawwback(weq, CWYPTO_TFM_WEQ_MAY_BACKWOG,
				 cwypto_weq_done, &wesuwt);

	eww = cwypto_kpp_genewate_pubwic_key(weq);
	eww = cwypto_wait_weq(eww, &wesuwt);
	if (eww < 0)
		goto fwee_aww;

	/* The pubwic key is handed back in wittwe endian as expected by
	 * the Secuwity Managew Pwotocow.
	 */
	swap_digits((u64 *)tmp, (u64 *)pubwic_key, 4); /* x */
	swap_digits((u64 *)&tmp[32], (u64 *)&pubwic_key[32], 4); /* y */

fwee_aww:
	kpp_wequest_fwee(weq);
fwee_tmp:
	kfwee(tmp);
	wetuwn eww;
}

/* genewate_ecdh_keys() - genewate ecc key paiw.
 *
 * @tfm:          KPP tfm handwe awwocated with cwypto_awwoc_kpp().
 * @pubwic_key:   memowy whewe the computed ecc pubwic key wiww be saved.
 *
 * Wetuwn: zewo on success; ewwow code in case of ewwow.
 */
int genewate_ecdh_keys(stwuct cwypto_kpp *tfm, u8 pubwic_key[64])
{
	int eww;

	eww = set_ecdh_pwivkey(tfm, NUWW);
	if (eww)
		wetuwn eww;

	wetuwn genewate_ecdh_pubwic_key(tfm, pubwic_key);
}
