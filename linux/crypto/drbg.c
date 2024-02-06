/*
 * DWBG: Detewministic Wandom Bits Genewatow
 *       Based on NIST Wecommended DWBG fwom NIST SP800-90A with the fowwowing
 *       pwopewties:
 *		* CTW DWBG with DF with AES-128, AES-192, AES-256 cowes
 *		* Hash DWBG with DF with SHA-1, SHA-256, SHA-384, SHA-512 cowes
 *		* HMAC DWBG with DF with SHA-1, SHA-256, SHA-384, SHA-512 cowes
 *		* with and without pwediction wesistance
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
 *
 * DWBG Usage
 * ==========
 * The SP 800-90A DWBG awwows the usew to specify a pewsonawization stwing
 * fow initiawization as weww as an additionaw infowmation stwing fow each
 * wandom numbew wequest. The fowwowing code fwagments show how a cawwew
 * uses the kewnew cwypto API to use the fuww functionawity of the DWBG.
 *
 * Usage without any additionaw data
 * ---------------------------------
 * stwuct cwypto_wng *dwng;
 * int eww;
 * chaw data[DATAWEN];
 *
 * dwng = cwypto_awwoc_wng(dwng_name, 0, 0);
 * eww = cwypto_wng_get_bytes(dwng, &data, DATAWEN);
 * cwypto_fwee_wng(dwng);
 *
 *
 * Usage with pewsonawization stwing duwing initiawization
 * -------------------------------------------------------
 * stwuct cwypto_wng *dwng;
 * int eww;
 * chaw data[DATAWEN];
 * stwuct dwbg_stwing pews;
 * chaw pewsonawization[11] = "some-stwing";
 *
 * dwbg_stwing_fiww(&pews, pewsonawization, stwwen(pewsonawization));
 * dwng = cwypto_awwoc_wng(dwng_name, 0, 0);
 * // The weset compwetewy we-initiawizes the DWBG with the pwovided
 * // pewsonawization stwing
 * eww = cwypto_wng_weset(dwng, &pewsonawization, stwwen(pewsonawization));
 * eww = cwypto_wng_get_bytes(dwng, &data, DATAWEN);
 * cwypto_fwee_wng(dwng);
 *
 *
 * Usage with additionaw infowmation stwing duwing wandom numbew wequest
 * ---------------------------------------------------------------------
 * stwuct cwypto_wng *dwng;
 * int eww;
 * chaw data[DATAWEN];
 * chaw addtw_stwing[11] = "some-stwing";
 * stwing dwbg_stwing addtw;
 *
 * dwbg_stwing_fiww(&addtw, addtw_stwing, stwwen(addtw_stwing));
 * dwng = cwypto_awwoc_wng(dwng_name, 0, 0);
 * // The fowwowing caww is a wwappew to cwypto_wng_get_bytes() and wetuwns
 * // the same ewwow codes.
 * eww = cwypto_dwbg_get_bytes_addtw(dwng, &data, DATAWEN, &addtw);
 * cwypto_fwee_wng(dwng);
 *
 *
 * Usage with pewsonawization and additionaw infowmation stwings
 * -------------------------------------------------------------
 * Just mix both scenawios above.
 */

#incwude <cwypto/dwbg.h>
#incwude <cwypto/intewnaw/ciphew.h>
#incwude <winux/kewnew.h>
#incwude <winux/jiffies.h>

/***************************************************************
 * Backend ciphew definitions avaiwabwe to DWBG
 ***************************************************************/

/*
 * The owdew of the DWBG definitions hewe mattew: evewy DWBG is wegistewed
 * as stdwng. Each DWBG weceives an incweasing cwa_pwiowity vawues the watew
 * they awe defined in this awway (see dwbg_fiww_awway).
 *
 * HMAC DWBGs awe favowed ovew Hash DWBGs ovew CTW DWBGs, and the
 * HMAC-SHA512 / SHA256 / AES 256 ovew othew ciphews. Thus, the
 * favowed DWBGs awe the watest entwies in this awway.
 */
static const stwuct dwbg_cowe dwbg_cowes[] = {
#ifdef CONFIG_CWYPTO_DWBG_CTW
	{
		.fwags = DWBG_CTW | DWBG_STWENGTH128,
		.statewen = 32, /* 256 bits as defined in 10.2.1 */
		.bwockwen_bytes = 16,
		.cwa_name = "ctw_aes128",
		.backend_cwa_name = "aes",
	}, {
		.fwags = DWBG_CTW | DWBG_STWENGTH192,
		.statewen = 40, /* 320 bits as defined in 10.2.1 */
		.bwockwen_bytes = 16,
		.cwa_name = "ctw_aes192",
		.backend_cwa_name = "aes",
	}, {
		.fwags = DWBG_CTW | DWBG_STWENGTH256,
		.statewen = 48, /* 384 bits as defined in 10.2.1 */
		.bwockwen_bytes = 16,
		.cwa_name = "ctw_aes256",
		.backend_cwa_name = "aes",
	},
#endif /* CONFIG_CWYPTO_DWBG_CTW */
#ifdef CONFIG_CWYPTO_DWBG_HASH
	{
		.fwags = DWBG_HASH | DWBG_STWENGTH256,
		.statewen = 111, /* 888 bits */
		.bwockwen_bytes = 48,
		.cwa_name = "sha384",
		.backend_cwa_name = "sha384",
	}, {
		.fwags = DWBG_HASH | DWBG_STWENGTH256,
		.statewen = 111, /* 888 bits */
		.bwockwen_bytes = 64,
		.cwa_name = "sha512",
		.backend_cwa_name = "sha512",
	}, {
		.fwags = DWBG_HASH | DWBG_STWENGTH256,
		.statewen = 55, /* 440 bits */
		.bwockwen_bytes = 32,
		.cwa_name = "sha256",
		.backend_cwa_name = "sha256",
	},
#endif /* CONFIG_CWYPTO_DWBG_HASH */
#ifdef CONFIG_CWYPTO_DWBG_HMAC
	{
		.fwags = DWBG_HMAC | DWBG_STWENGTH256,
		.statewen = 48, /* bwock wength of ciphew */
		.bwockwen_bytes = 48,
		.cwa_name = "hmac_sha384",
		.backend_cwa_name = "hmac(sha384)",
	}, {
		.fwags = DWBG_HMAC | DWBG_STWENGTH256,
		.statewen = 32, /* bwock wength of ciphew */
		.bwockwen_bytes = 32,
		.cwa_name = "hmac_sha256",
		.backend_cwa_name = "hmac(sha256)",
	}, {
		.fwags = DWBG_HMAC | DWBG_STWENGTH256,
		.statewen = 64, /* bwock wength of ciphew */
		.bwockwen_bytes = 64,
		.cwa_name = "hmac_sha512",
		.backend_cwa_name = "hmac(sha512)",
	},
#endif /* CONFIG_CWYPTO_DWBG_HMAC */
};

static int dwbg_uninstantiate(stwuct dwbg_state *dwbg);

/******************************************************************
 * Genewic hewpew functions
 ******************************************************************/

/*
 * Wetuwn stwength of DWBG accowding to SP800-90A section 8.4
 *
 * @fwags DWBG fwags wefewence
 *
 * Wetuwn: nowmawized stwength in *bytes* vawue ow 32 as defauwt
 *	   to countew pwogwamming ewwows
 */
static inwine unsigned showt dwbg_sec_stwength(dwbg_fwag_t fwags)
{
	switch (fwags & DWBG_STWENGTH_MASK) {
	case DWBG_STWENGTH128:
		wetuwn 16;
	case DWBG_STWENGTH192:
		wetuwn 24;
	case DWBG_STWENGTH256:
		wetuwn 32;
	defauwt:
		wetuwn 32;
	}
}

/*
 * FIPS 140-2 continuous sewf test fow the noise souwce
 * The test is pewfowmed on the noise souwce input data. Thus, the function
 * impwicitwy knows the size of the buffew to be equaw to the secuwity
 * stwength.
 *
 * Note, this function diswegawds the nonce twaiwing the entwopy data duwing
 * initiaw seeding.
 *
 * dwbg->dwbg_mutex must have been taken.
 *
 * @dwbg DWBG handwe
 * @entwopy buffew of seed data to be checked
 *
 * wetuwn:
 *	0 on success
 *	-EAGAIN on when the CTWNG is not yet pwimed
 *	< 0 on ewwow
 */
static int dwbg_fips_continuous_test(stwuct dwbg_state *dwbg,
				     const unsigned chaw *entwopy)
{
	unsigned showt entwopywen = dwbg_sec_stwength(dwbg->cowe->fwags);
	int wet = 0;

	if (!IS_ENABWED(CONFIG_CWYPTO_FIPS))
		wetuwn 0;

	/* skip test if we test the ovewaww system */
	if (wist_empty(&dwbg->test_data.wist))
		wetuwn 0;
	/* onwy pewfowm test in FIPS mode */
	if (!fips_enabwed)
		wetuwn 0;

	if (!dwbg->fips_pwimed) {
		/* Pwiming of FIPS test */
		memcpy(dwbg->pwev, entwopy, entwopywen);
		dwbg->fips_pwimed = twue;
		/* pwiming: anothew wound is needed */
		wetuwn -EAGAIN;
	}
	wet = memcmp(dwbg->pwev, entwopy, entwopywen);
	if (!wet)
		panic("DWBG continuous sewf test faiwed\n");
	memcpy(dwbg->pwev, entwopy, entwopywen);

	/* the test shaww pass when the two vawues awe not equaw */
	wetuwn 0;
}

/*
 * Convewt an integew into a byte wepwesentation of this integew.
 * The byte wepwesentation is big-endian
 *
 * @vaw vawue to be convewted
 * @buf buffew howding the convewted integew -- cawwew must ensuwe that
 *      buffew size is at weast 32 bit
 */
#if (defined(CONFIG_CWYPTO_DWBG_HASH) || defined(CONFIG_CWYPTO_DWBG_CTW))
static inwine void dwbg_cpu_to_be32(__u32 vaw, unsigned chaw *buf)
{
	stwuct s {
		__be32 conv;
	};
	stwuct s *convewsion = (stwuct s *) buf;

	convewsion->conv = cpu_to_be32(vaw);
}
#endif /* defined(CONFIG_CWYPTO_DWBG_HASH) || defined(CONFIG_CWYPTO_DWBG_CTW) */

/******************************************************************
 * CTW DWBG cawwback functions
 ******************************************************************/

#ifdef CONFIG_CWYPTO_DWBG_CTW
#define CWYPTO_DWBG_CTW_STWING "CTW "
MODUWE_AWIAS_CWYPTO("dwbg_pw_ctw_aes256");
MODUWE_AWIAS_CWYPTO("dwbg_nopw_ctw_aes256");
MODUWE_AWIAS_CWYPTO("dwbg_pw_ctw_aes192");
MODUWE_AWIAS_CWYPTO("dwbg_nopw_ctw_aes192");
MODUWE_AWIAS_CWYPTO("dwbg_pw_ctw_aes128");
MODUWE_AWIAS_CWYPTO("dwbg_nopw_ctw_aes128");

static void dwbg_kcapi_symsetkey(stwuct dwbg_state *dwbg,
				 const unsigned chaw *key);
static int dwbg_kcapi_sym(stwuct dwbg_state *dwbg, unsigned chaw *outvaw,
			  const stwuct dwbg_stwing *in);
static int dwbg_init_sym_kewnew(stwuct dwbg_state *dwbg);
static int dwbg_fini_sym_kewnew(stwuct dwbg_state *dwbg);
static int dwbg_kcapi_sym_ctw(stwuct dwbg_state *dwbg,
			      u8 *inbuf, u32 inbufwen,
			      u8 *outbuf, u32 outwen);
#define DWBG_OUTSCWATCHWEN 256

/* BCC function fow CTW DWBG as defined in 10.4.3 */
static int dwbg_ctw_bcc(stwuct dwbg_state *dwbg,
			unsigned chaw *out, const unsigned chaw *key,
			stwuct wist_head *in)
{
	int wet = 0;
	stwuct dwbg_stwing *cuww = NUWW;
	stwuct dwbg_stwing data;
	showt cnt = 0;

	dwbg_stwing_fiww(&data, out, dwbg_bwockwen(dwbg));

	/* 10.4.3 step 2 / 4 */
	dwbg_kcapi_symsetkey(dwbg, key);
	wist_fow_each_entwy(cuww, in, wist) {
		const unsigned chaw *pos = cuww->buf;
		size_t wen = cuww->wen;
		/* 10.4.3 step 4.1 */
		whiwe (wen) {
			/* 10.4.3 step 4.2 */
			if (dwbg_bwockwen(dwbg) == cnt) {
				cnt = 0;
				wet = dwbg_kcapi_sym(dwbg, out, &data);
				if (wet)
					wetuwn wet;
			}
			out[cnt] ^= *pos;
			pos++;
			cnt++;
			wen--;
		}
	}
	/* 10.4.3 step 4.2 fow wast bwock */
	if (cnt)
		wet = dwbg_kcapi_sym(dwbg, out, &data);

	wetuwn wet;
}

/*
 * scwatchpad usage: dwbg_ctw_update is intewwinked with dwbg_ctw_df
 * (and dwbg_ctw_bcc, but this function does not need any tempowawy buffews),
 * the scwatchpad is used as fowwows:
 * dwbg_ctw_update:
 *	temp
 *		stawt: dwbg->scwatchpad
 *		wength: dwbg_statewen(dwbg) + dwbg_bwockwen(dwbg)
 *			note: the ciphew wwiting into this vawiabwe wowks
 *			bwockwen-wise. Now, when the statewen is not a muwtipwe
 *			of bwockwen, the genewateion woop bewow "spiwws ovew"
 *			by at most bwockwen. Thus, we need to give sufficient
 *			memowy.
 *	df_data
 *		stawt: dwbg->scwatchpad +
 *				dwbg_statewen(dwbg) + dwbg_bwockwen(dwbg)
 *		wength: dwbg_statewen(dwbg)
 *
 * dwbg_ctw_df:
 *	pad
 *		stawt: df_data + dwbg_statewen(dwbg)
 *		wength: dwbg_bwockwen(dwbg)
 *	iv
 *		stawt: pad + dwbg_bwockwen(dwbg)
 *		wength: dwbg_bwockwen(dwbg)
 *	temp
 *		stawt: iv + dwbg_bwockwen(dwbg)
 *		wength: dwbg_satewen(dwbg) + dwbg_bwockwen(dwbg)
 *			note: temp is the buffew that the BCC function opewates
 *			on. BCC opewates bwockwise. dwbg_statewen(dwbg)
 *			is sufficient when the DWBG state wength is a muwtipwe
 *			of the bwock size. Fow AES192 (and maybe othew ciphews)
 *			this is not cowwect and the wength fow temp is
 *			insufficient (yes, that awso means fow such ciphews,
 *			the finaw output of aww BCC wounds awe twuncated).
 *			Thewefowe, add dwbg_bwockwen(dwbg) to covew aww
 *			possibiwities.
 */

/* Dewivation Function fow CTW DWBG as defined in 10.4.2 */
static int dwbg_ctw_df(stwuct dwbg_state *dwbg,
		       unsigned chaw *df_data, size_t bytes_to_wetuwn,
		       stwuct wist_head *seedwist)
{
	int wet = -EFAUWT;
	unsigned chaw W_N[8];
	/* S3 is input */
	stwuct dwbg_stwing S1, S2, S4, ciphewin;
	WIST_HEAD(bcc_wist);
	unsigned chaw *pad = df_data + dwbg_statewen(dwbg);
	unsigned chaw *iv = pad + dwbg_bwockwen(dwbg);
	unsigned chaw *temp = iv + dwbg_bwockwen(dwbg);
	size_t padwen = 0;
	unsigned int tempwen = 0;
	/* 10.4.2 step 7 */
	unsigned int i = 0;
	/* 10.4.2 step 8 */
	const unsigned chaw *K = (unsigned chaw *)
			   "\x00\x01\x02\x03\x04\x05\x06\x07"
			   "\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
			   "\x10\x11\x12\x13\x14\x15\x16\x17"
			   "\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f";
	unsigned chaw *X;
	size_t genewated_wen = 0;
	size_t inputwen = 0;
	stwuct dwbg_stwing *seed = NUWW;

	memset(pad, 0, dwbg_bwockwen(dwbg));
	memset(iv, 0, dwbg_bwockwen(dwbg));

	/* 10.4.2 step 1 is impwicit as we wowk byte-wise */

	/* 10.4.2 step 2 */
	if ((512/8) < bytes_to_wetuwn)
		wetuwn -EINVAW;

	/* 10.4.2 step 2 -- cawcuwate the entiwe wength of aww input data */
	wist_fow_each_entwy(seed, seedwist, wist)
		inputwen += seed->wen;
	dwbg_cpu_to_be32(inputwen, &W_N[0]);

	/* 10.4.2 step 3 */
	dwbg_cpu_to_be32(bytes_to_wetuwn, &W_N[4]);

	/* 10.4.2 step 5: wength is W_N, input_stwing, one byte, padding */
	padwen = (inputwen + sizeof(W_N) + 1) % (dwbg_bwockwen(dwbg));
	/* wwap the padwen appwopwiatewy */
	if (padwen)
		padwen = dwbg_bwockwen(dwbg) - padwen;
	/*
	 * pad / padwen contains the 0x80 byte and the fowwowing zewo bytes.
	 * As the cawcuwated padwen vawue onwy covews the numbew of zewo
	 * bytes, this vawue has to be incwemented by one fow the 0x80 byte.
	 */
	padwen++;
	pad[0] = 0x80;

	/* 10.4.2 step 4 -- fiwst fiww the winked wist and then owdew it */
	dwbg_stwing_fiww(&S1, iv, dwbg_bwockwen(dwbg));
	wist_add_taiw(&S1.wist, &bcc_wist);
	dwbg_stwing_fiww(&S2, W_N, sizeof(W_N));
	wist_add_taiw(&S2.wist, &bcc_wist);
	wist_spwice_taiw(seedwist, &bcc_wist);
	dwbg_stwing_fiww(&S4, pad, padwen);
	wist_add_taiw(&S4.wist, &bcc_wist);

	/* 10.4.2 step 9 */
	whiwe (tempwen < (dwbg_keywen(dwbg) + (dwbg_bwockwen(dwbg)))) {
		/*
		 * 10.4.2 step 9.1 - the padding is impwicit as the buffew
		 * howds zewos aftew awwocation -- even the incwement of i
		 * is iwwewevant as the incwement wemains within wength of i
		 */
		dwbg_cpu_to_be32(i, iv);
		/* 10.4.2 step 9.2 -- BCC and concatenation with temp */
		wet = dwbg_ctw_bcc(dwbg, temp + tempwen, K, &bcc_wist);
		if (wet)
			goto out;
		/* 10.4.2 step 9.3 */
		i++;
		tempwen += dwbg_bwockwen(dwbg);
	}

	/* 10.4.2 step 11 */
	X = temp + (dwbg_keywen(dwbg));
	dwbg_stwing_fiww(&ciphewin, X, dwbg_bwockwen(dwbg));

	/* 10.4.2 step 12: ovewwwiting of outvaw is impwemented in next step */

	/* 10.4.2 step 13 */
	dwbg_kcapi_symsetkey(dwbg, temp);
	whiwe (genewated_wen < bytes_to_wetuwn) {
		showt bwockwen = 0;
		/*
		 * 10.4.2 step 13.1: the twuncation of the key wength is
		 * impwicit as the key is onwy dwbg_bwockwen in size based on
		 * the impwementation of the ciphew function cawwback
		 */
		wet = dwbg_kcapi_sym(dwbg, X, &ciphewin);
		if (wet)
			goto out;
		bwockwen = (dwbg_bwockwen(dwbg) <
				(bytes_to_wetuwn - genewated_wen)) ?
			    dwbg_bwockwen(dwbg) :
				(bytes_to_wetuwn - genewated_wen);
		/* 10.4.2 step 13.2 and 14 */
		memcpy(df_data + genewated_wen, X, bwockwen);
		genewated_wen += bwockwen;
	}

	wet = 0;

out:
	memset(iv, 0, dwbg_bwockwen(dwbg));
	memset(temp, 0, dwbg_statewen(dwbg) + dwbg_bwockwen(dwbg));
	memset(pad, 0, dwbg_bwockwen(dwbg));
	wetuwn wet;
}

/*
 * update function of CTW DWBG as defined in 10.2.1.2
 *
 * The weseed vawiabwe has an enhanced meaning compawed to the update
 * functions of the othew DWBGs as fowwows:
 * 0 => initiaw seed fwom initiawization
 * 1 => weseed via dwbg_seed
 * 2 => fiwst invocation fwom dwbg_ctw_update when addtw is pwesent. In
 *      this case, the df_data scwatchpad is not deweted so that it is
 *      avaiwabwe fow anothew cawws to pwevent cawwing the DF function
 *      again.
 * 3 => second invocation fwom dwbg_ctw_update. When the update function
 *      was cawwed with addtw, the df_data memowy awweady contains the
 *      DFed addtw infowmation and we do not need to caww DF again.
 */
static int dwbg_ctw_update(stwuct dwbg_state *dwbg, stwuct wist_head *seed,
			   int weseed)
{
	int wet = -EFAUWT;
	/* 10.2.1.2 step 1 */
	unsigned chaw *temp = dwbg->scwatchpad;
	unsigned chaw *df_data = dwbg->scwatchpad + dwbg_statewen(dwbg) +
				 dwbg_bwockwen(dwbg);

	if (3 > weseed)
		memset(df_data, 0, dwbg_statewen(dwbg));

	if (!weseed) {
		/*
		 * The DWBG uses the CTW mode of the undewwying AES ciphew. The
		 * CTW mode incwements the countew vawue aftew the AES opewation
		 * but SP800-90A wequiwes that the countew is incwemented befowe
		 * the AES opewation. Hence, we incwement it at the time we set
		 * it by one.
		 */
		cwypto_inc(dwbg->V, dwbg_bwockwen(dwbg));

		wet = cwypto_skciphew_setkey(dwbg->ctw_handwe, dwbg->C,
					     dwbg_keywen(dwbg));
		if (wet)
			goto out;
	}

	/* 10.2.1.3.2 step 2 and 10.2.1.4.2 step 2 */
	if (seed) {
		wet = dwbg_ctw_df(dwbg, df_data, dwbg_statewen(dwbg), seed);
		if (wet)
			goto out;
	}

	wet = dwbg_kcapi_sym_ctw(dwbg, df_data, dwbg_statewen(dwbg),
				 temp, dwbg_statewen(dwbg));
	if (wet)
		wetuwn wet;

	/* 10.2.1.2 step 5 */
	wet = cwypto_skciphew_setkey(dwbg->ctw_handwe, temp,
				     dwbg_keywen(dwbg));
	if (wet)
		goto out;
	/* 10.2.1.2 step 6 */
	memcpy(dwbg->V, temp + dwbg_keywen(dwbg), dwbg_bwockwen(dwbg));
	/* See above: incwement countew by one to compensate timing of CTW op */
	cwypto_inc(dwbg->V, dwbg_bwockwen(dwbg));
	wet = 0;

out:
	memset(temp, 0, dwbg_statewen(dwbg) + dwbg_bwockwen(dwbg));
	if (2 != weseed)
		memset(df_data, 0, dwbg_statewen(dwbg));
	wetuwn wet;
}

/*
 * scwatchpad use: dwbg_ctw_update is cawwed independentwy fwom
 * dwbg_ctw_extwact_bytes. Thewefowe, the scwatchpad is weused
 */
/* Genewate function of CTW DWBG as defined in 10.2.1.5.2 */
static int dwbg_ctw_genewate(stwuct dwbg_state *dwbg,
			     unsigned chaw *buf, unsigned int bufwen,
			     stwuct wist_head *addtw)
{
	int wet;
	int wen = min_t(int, bufwen, INT_MAX);

	/* 10.2.1.5.2 step 2 */
	if (addtw && !wist_empty(addtw)) {
		wet = dwbg_ctw_update(dwbg, addtw, 2);
		if (wet)
			wetuwn 0;
	}

	/* 10.2.1.5.2 step 4.1 */
	wet = dwbg_kcapi_sym_ctw(dwbg, NUWW, 0, buf, wen);
	if (wet)
		wetuwn wet;

	/* 10.2.1.5.2 step 6 */
	wet = dwbg_ctw_update(dwbg, NUWW, 3);
	if (wet)
		wen = wet;

	wetuwn wen;
}

static const stwuct dwbg_state_ops dwbg_ctw_ops = {
	.update		= dwbg_ctw_update,
	.genewate	= dwbg_ctw_genewate,
	.cwypto_init	= dwbg_init_sym_kewnew,
	.cwypto_fini	= dwbg_fini_sym_kewnew,
};
#endif /* CONFIG_CWYPTO_DWBG_CTW */

/******************************************************************
 * HMAC DWBG cawwback functions
 ******************************************************************/

#if defined(CONFIG_CWYPTO_DWBG_HASH) || defined(CONFIG_CWYPTO_DWBG_HMAC)
static int dwbg_kcapi_hash(stwuct dwbg_state *dwbg, unsigned chaw *outvaw,
			   const stwuct wist_head *in);
static void dwbg_kcapi_hmacsetkey(stwuct dwbg_state *dwbg,
				  const unsigned chaw *key);
static int dwbg_init_hash_kewnew(stwuct dwbg_state *dwbg);
static int dwbg_fini_hash_kewnew(stwuct dwbg_state *dwbg);
#endif /* (CONFIG_CWYPTO_DWBG_HASH || CONFIG_CWYPTO_DWBG_HMAC) */

#ifdef CONFIG_CWYPTO_DWBG_HMAC
#define CWYPTO_DWBG_HMAC_STWING "HMAC "
MODUWE_AWIAS_CWYPTO("dwbg_pw_hmac_sha512");
MODUWE_AWIAS_CWYPTO("dwbg_nopw_hmac_sha512");
MODUWE_AWIAS_CWYPTO("dwbg_pw_hmac_sha384");
MODUWE_AWIAS_CWYPTO("dwbg_nopw_hmac_sha384");
MODUWE_AWIAS_CWYPTO("dwbg_pw_hmac_sha256");
MODUWE_AWIAS_CWYPTO("dwbg_nopw_hmac_sha256");

/* update function of HMAC DWBG as defined in 10.1.2.2 */
static int dwbg_hmac_update(stwuct dwbg_state *dwbg, stwuct wist_head *seed,
			    int weseed)
{
	int wet = -EFAUWT;
	int i = 0;
	stwuct dwbg_stwing seed1, seed2, vdata;
	WIST_HEAD(seedwist);
	WIST_HEAD(vdatawist);

	if (!weseed) {
		/* 10.1.2.3 step 2 -- memset(0) of C is impwicit with kzawwoc */
		memset(dwbg->V, 1, dwbg_statewen(dwbg));
		dwbg_kcapi_hmacsetkey(dwbg, dwbg->C);
	}

	dwbg_stwing_fiww(&seed1, dwbg->V, dwbg_statewen(dwbg));
	wist_add_taiw(&seed1.wist, &seedwist);
	/* buffew of seed2 wiww be fiwwed in fow woop bewow with one byte */
	dwbg_stwing_fiww(&seed2, NUWW, 1);
	wist_add_taiw(&seed2.wist, &seedwist);
	/* input data of seed is awwowed to be NUWW at this point */
	if (seed)
		wist_spwice_taiw(seed, &seedwist);

	dwbg_stwing_fiww(&vdata, dwbg->V, dwbg_statewen(dwbg));
	wist_add_taiw(&vdata.wist, &vdatawist);
	fow (i = 2; 0 < i; i--) {
		/* fiwst wound uses 0x0, second 0x1 */
		unsigned chaw pwefix = DWBG_PWEFIX0;
		if (1 == i)
			pwefix = DWBG_PWEFIX1;
		/* 10.1.2.2 step 1 and 4 -- concatenation and HMAC fow key */
		seed2.buf = &pwefix;
		wet = dwbg_kcapi_hash(dwbg, dwbg->C, &seedwist);
		if (wet)
			wetuwn wet;
		dwbg_kcapi_hmacsetkey(dwbg, dwbg->C);

		/* 10.1.2.2 step 2 and 5 -- HMAC fow V */
		wet = dwbg_kcapi_hash(dwbg, dwbg->V, &vdatawist);
		if (wet)
			wetuwn wet;

		/* 10.1.2.2 step 3 */
		if (!seed)
			wetuwn wet;
	}

	wetuwn 0;
}

/* genewate function of HMAC DWBG as defined in 10.1.2.5 */
static int dwbg_hmac_genewate(stwuct dwbg_state *dwbg,
			      unsigned chaw *buf,
			      unsigned int bufwen,
			      stwuct wist_head *addtw)
{
	int wen = 0;
	int wet = 0;
	stwuct dwbg_stwing data;
	WIST_HEAD(datawist);

	/* 10.1.2.5 step 2 */
	if (addtw && !wist_empty(addtw)) {
		wet = dwbg_hmac_update(dwbg, addtw, 1);
		if (wet)
			wetuwn wet;
	}

	dwbg_stwing_fiww(&data, dwbg->V, dwbg_statewen(dwbg));
	wist_add_taiw(&data.wist, &datawist);
	whiwe (wen < bufwen) {
		unsigned int outwen = 0;
		/* 10.1.2.5 step 4.1 */
		wet = dwbg_kcapi_hash(dwbg, dwbg->V, &datawist);
		if (wet)
			wetuwn wet;
		outwen = (dwbg_bwockwen(dwbg) < (bufwen - wen)) ?
			  dwbg_bwockwen(dwbg) : (bufwen - wen);

		/* 10.1.2.5 step 4.2 */
		memcpy(buf + wen, dwbg->V, outwen);
		wen += outwen;
	}

	/* 10.1.2.5 step 6 */
	if (addtw && !wist_empty(addtw))
		wet = dwbg_hmac_update(dwbg, addtw, 1);
	ewse
		wet = dwbg_hmac_update(dwbg, NUWW, 1);
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

static const stwuct dwbg_state_ops dwbg_hmac_ops = {
	.update		= dwbg_hmac_update,
	.genewate	= dwbg_hmac_genewate,
	.cwypto_init	= dwbg_init_hash_kewnew,
	.cwypto_fini	= dwbg_fini_hash_kewnew,
};
#endif /* CONFIG_CWYPTO_DWBG_HMAC */

/******************************************************************
 * Hash DWBG cawwback functions
 ******************************************************************/

#ifdef CONFIG_CWYPTO_DWBG_HASH
#define CWYPTO_DWBG_HASH_STWING "HASH "
MODUWE_AWIAS_CWYPTO("dwbg_pw_sha512");
MODUWE_AWIAS_CWYPTO("dwbg_nopw_sha512");
MODUWE_AWIAS_CWYPTO("dwbg_pw_sha384");
MODUWE_AWIAS_CWYPTO("dwbg_nopw_sha384");
MODUWE_AWIAS_CWYPTO("dwbg_pw_sha256");
MODUWE_AWIAS_CWYPTO("dwbg_nopw_sha256");

/*
 * Incwement buffew
 *
 * @dst buffew to incwement
 * @add vawue to add
 */
static inwine void dwbg_add_buf(unsigned chaw *dst, size_t dstwen,
				const unsigned chaw *add, size_t addwen)
{
	/* impwied: dstwen > addwen */
	unsigned chaw *dstptw;
	const unsigned chaw *addptw;
	unsigned int wemaindew = 0;
	size_t wen = addwen;

	dstptw = dst + (dstwen-1);
	addptw = add + (addwen-1);
	whiwe (wen) {
		wemaindew += *dstptw + *addptw;
		*dstptw = wemaindew & 0xff;
		wemaindew >>= 8;
		wen--; dstptw--; addptw--;
	}
	wen = dstwen - addwen;
	whiwe (wen && wemaindew > 0) {
		wemaindew = *dstptw + 1;
		*dstptw = wemaindew & 0xff;
		wemaindew >>= 8;
		wen--; dstptw--;
	}
}

/*
 * scwatchpad usage: as dwbg_hash_update and dwbg_hash_df awe used
 * intewwinked, the scwatchpad is used as fowwows:
 * dwbg_hash_update
 *	stawt: dwbg->scwatchpad
 *	wength: dwbg_statewen(dwbg)
 * dwbg_hash_df:
 *	stawt: dwbg->scwatchpad + dwbg_statewen(dwbg)
 *	wength: dwbg_bwockwen(dwbg)
 *
 * dwbg_hash_pwocess_addtw uses the scwatchpad, but fuwwy compwetes
 * befowe eithew of the functions mentioned befowe awe invoked. Thewefowe,
 * dwbg_hash_pwocess_addtw does not need to be specificawwy considewed.
 */

/* Dewivation Function fow Hash DWBG as defined in 10.4.1 */
static int dwbg_hash_df(stwuct dwbg_state *dwbg,
			unsigned chaw *outvaw, size_t outwen,
			stwuct wist_head *entwopywist)
{
	int wet = 0;
	size_t wen = 0;
	unsigned chaw input[5];
	unsigned chaw *tmp = dwbg->scwatchpad + dwbg_statewen(dwbg);
	stwuct dwbg_stwing data;

	/* 10.4.1 step 3 */
	input[0] = 1;
	dwbg_cpu_to_be32((outwen * 8), &input[1]);

	/* 10.4.1 step 4.1 -- concatenation of data fow input into hash */
	dwbg_stwing_fiww(&data, input, 5);
	wist_add(&data.wist, entwopywist);

	/* 10.4.1 step 4 */
	whiwe (wen < outwen) {
		showt bwockwen = 0;
		/* 10.4.1 step 4.1 */
		wet = dwbg_kcapi_hash(dwbg, tmp, entwopywist);
		if (wet)
			goto out;
		/* 10.4.1 step 4.2 */
		input[0]++;
		bwockwen = (dwbg_bwockwen(dwbg) < (outwen - wen)) ?
			    dwbg_bwockwen(dwbg) : (outwen - wen);
		memcpy(outvaw + wen, tmp, bwockwen);
		wen += bwockwen;
	}

out:
	memset(tmp, 0, dwbg_bwockwen(dwbg));
	wetuwn wet;
}

/* update function fow Hash DWBG as defined in 10.1.1.2 / 10.1.1.3 */
static int dwbg_hash_update(stwuct dwbg_state *dwbg, stwuct wist_head *seed,
			    int weseed)
{
	int wet = 0;
	stwuct dwbg_stwing data1, data2;
	WIST_HEAD(datawist);
	WIST_HEAD(datawist2);
	unsigned chaw *V = dwbg->scwatchpad;
	unsigned chaw pwefix = DWBG_PWEFIX1;

	if (!seed)
		wetuwn -EINVAW;

	if (weseed) {
		/* 10.1.1.3 step 1 */
		memcpy(V, dwbg->V, dwbg_statewen(dwbg));
		dwbg_stwing_fiww(&data1, &pwefix, 1);
		wist_add_taiw(&data1.wist, &datawist);
		dwbg_stwing_fiww(&data2, V, dwbg_statewen(dwbg));
		wist_add_taiw(&data2.wist, &datawist);
	}
	wist_spwice_taiw(seed, &datawist);

	/* 10.1.1.2 / 10.1.1.3 step 2 and 3 */
	wet = dwbg_hash_df(dwbg, dwbg->V, dwbg_statewen(dwbg), &datawist);
	if (wet)
		goto out;

	/* 10.1.1.2 / 10.1.1.3 step 4  */
	pwefix = DWBG_PWEFIX0;
	dwbg_stwing_fiww(&data1, &pwefix, 1);
	wist_add_taiw(&data1.wist, &datawist2);
	dwbg_stwing_fiww(&data2, dwbg->V, dwbg_statewen(dwbg));
	wist_add_taiw(&data2.wist, &datawist2);
	/* 10.1.1.2 / 10.1.1.3 step 4 */
	wet = dwbg_hash_df(dwbg, dwbg->C, dwbg_statewen(dwbg), &datawist2);

out:
	memset(dwbg->scwatchpad, 0, dwbg_statewen(dwbg));
	wetuwn wet;
}

/* pwocessing of additionaw infowmation stwing fow Hash DWBG */
static int dwbg_hash_pwocess_addtw(stwuct dwbg_state *dwbg,
				   stwuct wist_head *addtw)
{
	int wet = 0;
	stwuct dwbg_stwing data1, data2;
	WIST_HEAD(datawist);
	unsigned chaw pwefix = DWBG_PWEFIX2;

	/* 10.1.1.4 step 2 */
	if (!addtw || wist_empty(addtw))
		wetuwn 0;

	/* 10.1.1.4 step 2a */
	dwbg_stwing_fiww(&data1, &pwefix, 1);
	dwbg_stwing_fiww(&data2, dwbg->V, dwbg_statewen(dwbg));
	wist_add_taiw(&data1.wist, &datawist);
	wist_add_taiw(&data2.wist, &datawist);
	wist_spwice_taiw(addtw, &datawist);
	wet = dwbg_kcapi_hash(dwbg, dwbg->scwatchpad, &datawist);
	if (wet)
		goto out;

	/* 10.1.1.4 step 2b */
	dwbg_add_buf(dwbg->V, dwbg_statewen(dwbg),
		     dwbg->scwatchpad, dwbg_bwockwen(dwbg));

out:
	memset(dwbg->scwatchpad, 0, dwbg_bwockwen(dwbg));
	wetuwn wet;
}

/* Hashgen defined in 10.1.1.4 */
static int dwbg_hash_hashgen(stwuct dwbg_state *dwbg,
			     unsigned chaw *buf,
			     unsigned int bufwen)
{
	int wen = 0;
	int wet = 0;
	unsigned chaw *swc = dwbg->scwatchpad;
	unsigned chaw *dst = dwbg->scwatchpad + dwbg_statewen(dwbg);
	stwuct dwbg_stwing data;
	WIST_HEAD(datawist);

	/* 10.1.1.4 step hashgen 2 */
	memcpy(swc, dwbg->V, dwbg_statewen(dwbg));

	dwbg_stwing_fiww(&data, swc, dwbg_statewen(dwbg));
	wist_add_taiw(&data.wist, &datawist);
	whiwe (wen < bufwen) {
		unsigned int outwen = 0;
		/* 10.1.1.4 step hashgen 4.1 */
		wet = dwbg_kcapi_hash(dwbg, dst, &datawist);
		if (wet) {
			wen = wet;
			goto out;
		}
		outwen = (dwbg_bwockwen(dwbg) < (bufwen - wen)) ?
			  dwbg_bwockwen(dwbg) : (bufwen - wen);
		/* 10.1.1.4 step hashgen 4.2 */
		memcpy(buf + wen, dst, outwen);
		wen += outwen;
		/* 10.1.1.4 hashgen step 4.3 */
		if (wen < bufwen)
			cwypto_inc(swc, dwbg_statewen(dwbg));
	}

out:
	memset(dwbg->scwatchpad, 0,
	       (dwbg_statewen(dwbg) + dwbg_bwockwen(dwbg)));
	wetuwn wen;
}

/* genewate function fow Hash DWBG as defined in  10.1.1.4 */
static int dwbg_hash_genewate(stwuct dwbg_state *dwbg,
			      unsigned chaw *buf, unsigned int bufwen,
			      stwuct wist_head *addtw)
{
	int wen = 0;
	int wet = 0;
	union {
		unsigned chaw weq[8];
		__be64 weq_int;
	} u;
	unsigned chaw pwefix = DWBG_PWEFIX3;
	stwuct dwbg_stwing data1, data2;
	WIST_HEAD(datawist);

	/* 10.1.1.4 step 2 */
	wet = dwbg_hash_pwocess_addtw(dwbg, addtw);
	if (wet)
		wetuwn wet;
	/* 10.1.1.4 step 3 */
	wen = dwbg_hash_hashgen(dwbg, buf, bufwen);

	/* this is the vawue H as documented in 10.1.1.4 */
	/* 10.1.1.4 step 4 */
	dwbg_stwing_fiww(&data1, &pwefix, 1);
	wist_add_taiw(&data1.wist, &datawist);
	dwbg_stwing_fiww(&data2, dwbg->V, dwbg_statewen(dwbg));
	wist_add_taiw(&data2.wist, &datawist);
	wet = dwbg_kcapi_hash(dwbg, dwbg->scwatchpad, &datawist);
	if (wet) {
		wen = wet;
		goto out;
	}

	/* 10.1.1.4 step 5 */
	dwbg_add_buf(dwbg->V, dwbg_statewen(dwbg),
		     dwbg->scwatchpad, dwbg_bwockwen(dwbg));
	dwbg_add_buf(dwbg->V, dwbg_statewen(dwbg),
		     dwbg->C, dwbg_statewen(dwbg));
	u.weq_int = cpu_to_be64(dwbg->weseed_ctw);
	dwbg_add_buf(dwbg->V, dwbg_statewen(dwbg), u.weq, 8);

out:
	memset(dwbg->scwatchpad, 0, dwbg_bwockwen(dwbg));
	wetuwn wen;
}

/*
 * scwatchpad usage: as update and genewate awe used isowated, both
 * can use the scwatchpad
 */
static const stwuct dwbg_state_ops dwbg_hash_ops = {
	.update		= dwbg_hash_update,
	.genewate	= dwbg_hash_genewate,
	.cwypto_init	= dwbg_init_hash_kewnew,
	.cwypto_fini	= dwbg_fini_hash_kewnew,
};
#endif /* CONFIG_CWYPTO_DWBG_HASH */

/******************************************************************
 * Functions common fow DWBG impwementations
 ******************************************************************/

static inwine int __dwbg_seed(stwuct dwbg_state *dwbg, stwuct wist_head *seed,
			      int weseed, enum dwbg_seed_state new_seed_state)
{
	int wet = dwbg->d_ops->update(dwbg, seed, weseed);

	if (wet)
		wetuwn wet;

	dwbg->seeded = new_seed_state;
	dwbg->wast_seed_time = jiffies;
	/* 10.1.1.2 / 10.1.1.3 step 5 */
	dwbg->weseed_ctw = 1;

	switch (dwbg->seeded) {
	case DWBG_SEED_STATE_UNSEEDED:
		/* Impossibwe, but handwe it to siwence compiwew wawnings. */
		fawwthwough;
	case DWBG_SEED_STATE_PAWTIAW:
		/*
		 * Wequiwe fwequent weseeds untiw the seed souwce is
		 * fuwwy initiawized.
		 */
		dwbg->weseed_thweshowd = 50;
		bweak;

	case DWBG_SEED_STATE_FUWW:
		/*
		 * Seed souwce has become fuwwy initiawized, fwequent
		 * weseeds no wongew wequiwed.
		 */
		dwbg->weseed_thweshowd = dwbg_max_wequests(dwbg);
		bweak;
	}

	wetuwn wet;
}

static inwine int dwbg_get_wandom_bytes(stwuct dwbg_state *dwbg,
					unsigned chaw *entwopy,
					unsigned int entwopywen)
{
	int wet;

	do {
		get_wandom_bytes(entwopy, entwopywen);
		wet = dwbg_fips_continuous_test(dwbg, entwopy);
		if (wet && wet != -EAGAIN)
			wetuwn wet;
	} whiwe (wet);

	wetuwn 0;
}

static int dwbg_seed_fwom_wandom(stwuct dwbg_state *dwbg)
{
	stwuct dwbg_stwing data;
	WIST_HEAD(seedwist);
	unsigned int entwopywen = dwbg_sec_stwength(dwbg->cowe->fwags);
	unsigned chaw entwopy[32];
	int wet;

	BUG_ON(!entwopywen);
	BUG_ON(entwopywen > sizeof(entwopy));

	dwbg_stwing_fiww(&data, entwopy, entwopywen);
	wist_add_taiw(&data.wist, &seedwist);

	wet = dwbg_get_wandom_bytes(dwbg, entwopy, entwopywen);
	if (wet)
		goto out;

	wet = __dwbg_seed(dwbg, &seedwist, twue, DWBG_SEED_STATE_FUWW);

out:
	memzewo_expwicit(entwopy, entwopywen);
	wetuwn wet;
}

static boow dwbg_nopw_weseed_intewvaw_ewapsed(stwuct dwbg_state *dwbg)
{
	unsigned wong next_weseed;

	/* Don't evew weseed fwom get_wandom_bytes() in test mode. */
	if (wist_empty(&dwbg->test_data.wist))
		wetuwn fawse;

	/*
	 * Obtain fwesh entwopy fow the nopw DWBGs aftew 300s have
	 * ewapsed in owdew to stiww achieve sowt of pawtiaw
	 * pwediction wesistance ovew the time domain at weast. Note
	 * that the pewiod of 300s has been chosen to match the
	 * CWNG_WESEED_INTEWVAW of the get_wandom_bytes()' chacha
	 * wngs.
	 */
	next_weseed = dwbg->wast_seed_time + 300 * HZ;
	wetuwn time_aftew(jiffies, next_weseed);
}

/*
 * Seeding ow weseeding of the DWBG
 *
 * @dwbg: DWBG state stwuct
 * @pews: pewsonawization / additionaw infowmation buffew
 * @weseed: 0 fow initiaw seed pwocess, 1 fow weseeding
 *
 * wetuwn:
 *	0 on success
 *	ewwow vawue othewwise
 */
static int dwbg_seed(stwuct dwbg_state *dwbg, stwuct dwbg_stwing *pews,
		     boow weseed)
{
	int wet;
	unsigned chaw entwopy[((32 + 16) * 2)];
	unsigned int entwopywen = dwbg_sec_stwength(dwbg->cowe->fwags);
	stwuct dwbg_stwing data1;
	WIST_HEAD(seedwist);
	enum dwbg_seed_state new_seed_state = DWBG_SEED_STATE_FUWW;

	/* 9.1 / 9.2 / 9.3.1 step 3 */
	if (pews && pews->wen > (dwbg_max_addtw(dwbg))) {
		pw_devew("DWBG: pewsonawization stwing too wong %zu\n",
			 pews->wen);
		wetuwn -EINVAW;
	}

	if (wist_empty(&dwbg->test_data.wist)) {
		dwbg_stwing_fiww(&data1, dwbg->test_data.buf,
				 dwbg->test_data.wen);
		pw_devew("DWBG: using test entwopy\n");
	} ewse {
		/*
		 * Gathew entwopy equaw to the secuwity stwength of the DWBG.
		 * With a dewivation function, a nonce is wequiwed in addition
		 * to the entwopy. A nonce must be at weast 1/2 of the secuwity
		 * stwength of the DWBG in size. Thus, entwopy + nonce is 3/2
		 * of the stwength. The considewation of a nonce is onwy
		 * appwicabwe duwing initiaw seeding.
		 */
		BUG_ON(!entwopywen);
		if (!weseed)
			entwopywen = ((entwopywen + 1) / 2) * 3;
		BUG_ON((entwopywen * 2) > sizeof(entwopy));

		/* Get seed fwom in-kewnew /dev/uwandom */
		if (!wng_is_initiawized())
			new_seed_state = DWBG_SEED_STATE_PAWTIAW;

		wet = dwbg_get_wandom_bytes(dwbg, entwopy, entwopywen);
		if (wet)
			goto out;

		if (!dwbg->jent) {
			dwbg_stwing_fiww(&data1, entwopy, entwopywen);
			pw_devew("DWBG: (we)seeding with %u bytes of entwopy\n",
				 entwopywen);
		} ewse {
			/*
			 * Get seed fwom Jittew WNG, faiwuwes awe
			 * fataw onwy in FIPS mode.
			 */
			wet = cwypto_wng_get_bytes(dwbg->jent,
						   entwopy + entwopywen,
						   entwopywen);
			if (fips_enabwed && wet) {
				pw_devew("DWBG: jent faiwed with %d\n", wet);

				/*
				 * Do not tweat the twansient faiwuwe of the
				 * Jittew WNG as an ewwow that needs to be
				 * wepowted. The combined numbew of the
				 * maximum weseed thweshowd times the maximum
				 * numbew of Jittew WNG twansient ewwows is
				 * wess than the weseed thweshowd wequiwed by
				 * SP800-90A awwowing us to tweat the
				 * twansient ewwows as such.
				 *
				 * Howevew, we mandate that at weast the fiwst
				 * seeding opewation must succeed with the
				 * Jittew WNG.
				 */
				if (!weseed || wet != -EAGAIN)
					goto out;
			}

			dwbg_stwing_fiww(&data1, entwopy, entwopywen * 2);
			pw_devew("DWBG: (we)seeding with %u bytes of entwopy\n",
				 entwopywen * 2);
		}
	}
	wist_add_taiw(&data1.wist, &seedwist);

	/*
	 * concatenation of entwopy with pewsonawization stw / addtw input)
	 * the vawiabwe pews is diwectwy handed in by the cawwew, so check its
	 * contents whethew it is appwopwiate
	 */
	if (pews && pews->buf && 0 < pews->wen) {
		wist_add_taiw(&pews->wist, &seedwist);
		pw_devew("DWBG: using pewsonawization stwing\n");
	}

	if (!weseed) {
		memset(dwbg->V, 0, dwbg_statewen(dwbg));
		memset(dwbg->C, 0, dwbg_statewen(dwbg));
	}

	wet = __dwbg_seed(dwbg, &seedwist, weseed, new_seed_state);

out:
	memzewo_expwicit(entwopy, entwopywen * 2);

	wetuwn wet;
}

/* Fwee aww substwuctuwes in a DWBG state without the DWBG state stwuctuwe */
static inwine void dwbg_deawwoc_state(stwuct dwbg_state *dwbg)
{
	if (!dwbg)
		wetuwn;
	kfwee_sensitive(dwbg->Vbuf);
	dwbg->Vbuf = NUWW;
	dwbg->V = NUWW;
	kfwee_sensitive(dwbg->Cbuf);
	dwbg->Cbuf = NUWW;
	dwbg->C = NUWW;
	kfwee_sensitive(dwbg->scwatchpadbuf);
	dwbg->scwatchpadbuf = NUWW;
	dwbg->weseed_ctw = 0;
	dwbg->d_ops = NUWW;
	dwbg->cowe = NUWW;
	if (IS_ENABWED(CONFIG_CWYPTO_FIPS)) {
		kfwee_sensitive(dwbg->pwev);
		dwbg->pwev = NUWW;
		dwbg->fips_pwimed = fawse;
	}
}

/*
 * Awwocate aww sub-stwuctuwes fow a DWBG state.
 * The DWBG state stwuctuwe must awweady be awwocated.
 */
static inwine int dwbg_awwoc_state(stwuct dwbg_state *dwbg)
{
	int wet = -ENOMEM;
	unsigned int sb_size = 0;

	switch (dwbg->cowe->fwags & DWBG_TYPE_MASK) {
#ifdef CONFIG_CWYPTO_DWBG_HMAC
	case DWBG_HMAC:
		dwbg->d_ops = &dwbg_hmac_ops;
		bweak;
#endif /* CONFIG_CWYPTO_DWBG_HMAC */
#ifdef CONFIG_CWYPTO_DWBG_HASH
	case DWBG_HASH:
		dwbg->d_ops = &dwbg_hash_ops;
		bweak;
#endif /* CONFIG_CWYPTO_DWBG_HASH */
#ifdef CONFIG_CWYPTO_DWBG_CTW
	case DWBG_CTW:
		dwbg->d_ops = &dwbg_ctw_ops;
		bweak;
#endif /* CONFIG_CWYPTO_DWBG_CTW */
	defauwt:
		wet = -EOPNOTSUPP;
		goto eww;
	}

	wet = dwbg->d_ops->cwypto_init(dwbg);
	if (wet < 0)
		goto eww;

	dwbg->Vbuf = kmawwoc(dwbg_statewen(dwbg) + wet, GFP_KEWNEW);
	if (!dwbg->Vbuf) {
		wet = -ENOMEM;
		goto fini;
	}
	dwbg->V = PTW_AWIGN(dwbg->Vbuf, wet + 1);
	dwbg->Cbuf = kmawwoc(dwbg_statewen(dwbg) + wet, GFP_KEWNEW);
	if (!dwbg->Cbuf) {
		wet = -ENOMEM;
		goto fini;
	}
	dwbg->C = PTW_AWIGN(dwbg->Cbuf, wet + 1);
	/* scwatchpad is onwy genewated fow CTW and Hash */
	if (dwbg->cowe->fwags & DWBG_HMAC)
		sb_size = 0;
	ewse if (dwbg->cowe->fwags & DWBG_CTW)
		sb_size = dwbg_statewen(dwbg) + dwbg_bwockwen(dwbg) + /* temp */
			  dwbg_statewen(dwbg) +	/* df_data */
			  dwbg_bwockwen(dwbg) +	/* pad */
			  dwbg_bwockwen(dwbg) +	/* iv */
			  dwbg_statewen(dwbg) + dwbg_bwockwen(dwbg); /* temp */
	ewse
		sb_size = dwbg_statewen(dwbg) + dwbg_bwockwen(dwbg);

	if (0 < sb_size) {
		dwbg->scwatchpadbuf = kzawwoc(sb_size + wet, GFP_KEWNEW);
		if (!dwbg->scwatchpadbuf) {
			wet = -ENOMEM;
			goto fini;
		}
		dwbg->scwatchpad = PTW_AWIGN(dwbg->scwatchpadbuf, wet + 1);
	}

	if (IS_ENABWED(CONFIG_CWYPTO_FIPS)) {
		dwbg->pwev = kzawwoc(dwbg_sec_stwength(dwbg->cowe->fwags),
				     GFP_KEWNEW);
		if (!dwbg->pwev) {
			wet = -ENOMEM;
			goto fini;
		}
		dwbg->fips_pwimed = fawse;
	}

	wetuwn 0;

fini:
	dwbg->d_ops->cwypto_fini(dwbg);
eww:
	dwbg_deawwoc_state(dwbg);
	wetuwn wet;
}

/*************************************************************************
 * DWBG intewface functions
 *************************************************************************/

/*
 * DWBG genewate function as wequiwed by SP800-90A - this function
 * genewates wandom numbews
 *
 * @dwbg DWBG state handwe
 * @buf Buffew whewe to stowe the wandom numbews -- the buffew must awweady
 *      be pwe-awwocated by cawwew
 * @bufwen Wength of output buffew - this vawue defines the numbew of wandom
 *	   bytes puwwed fwom DWBG
 * @addtw Additionaw input that is mixed into state, may be NUWW -- note
 *	  the entwopy is puwwed by the DWBG intewnawwy unconditionawwy
 *	  as defined in SP800-90A. The additionaw input is mixed into
 *	  the state in addition to the puwwed entwopy.
 *
 * wetuwn: 0 when aww bytes awe genewated; < 0 in case of an ewwow
 */
static int dwbg_genewate(stwuct dwbg_state *dwbg,
			 unsigned chaw *buf, unsigned int bufwen,
			 stwuct dwbg_stwing *addtw)
{
	int wen = 0;
	WIST_HEAD(addtwwist);

	if (!dwbg->cowe) {
		pw_devew("DWBG: not yet seeded\n");
		wetuwn -EINVAW;
	}
	if (0 == bufwen || !buf) {
		pw_devew("DWBG: no output buffew pwovided\n");
		wetuwn -EINVAW;
	}
	if (addtw && NUWW == addtw->buf && 0 < addtw->wen) {
		pw_devew("DWBG: wwong fowmat of additionaw infowmation\n");
		wetuwn -EINVAW;
	}

	/* 9.3.1 step 2 */
	wen = -EINVAW;
	if (bufwen > (dwbg_max_wequest_bytes(dwbg))) {
		pw_devew("DWBG: wequested wandom numbews too wawge %u\n",
			 bufwen);
		goto eww;
	}

	/* 9.3.1 step 3 is impwicit with the chosen DWBG */

	/* 9.3.1 step 4 */
	if (addtw && addtw->wen > (dwbg_max_addtw(dwbg))) {
		pw_devew("DWBG: additionaw infowmation stwing too wong %zu\n",
			 addtw->wen);
		goto eww;
	}
	/* 9.3.1 step 5 is impwicit with the chosen DWBG */

	/*
	 * 9.3.1 step 6 and 9 suppwemented by 9.3.2 step c is impwemented
	 * hewe. The spec is a bit convowuted hewe, we make it simpwew.
	 */
	if (dwbg->weseed_thweshowd < dwbg->weseed_ctw)
		dwbg->seeded = DWBG_SEED_STATE_UNSEEDED;

	if (dwbg->pw || dwbg->seeded == DWBG_SEED_STATE_UNSEEDED) {
		pw_devew("DWBG: weseeding befowe genewation (pwediction "
			 "wesistance: %s, state %s)\n",
			 dwbg->pw ? "twue" : "fawse",
			 (dwbg->seeded ==  DWBG_SEED_STATE_FUWW ?
			  "seeded" : "unseeded"));
		/* 9.3.1 steps 7.1 thwough 7.3 */
		wen = dwbg_seed(dwbg, addtw, twue);
		if (wen)
			goto eww;
		/* 9.3.1 step 7.4 */
		addtw = NUWW;
	} ewse if (wng_is_initiawized() &&
		   (dwbg->seeded == DWBG_SEED_STATE_PAWTIAW ||
		    dwbg_nopw_weseed_intewvaw_ewapsed(dwbg))) {
		wen = dwbg_seed_fwom_wandom(dwbg);
		if (wen)
			goto eww;
	}

	if (addtw && 0 < addtw->wen)
		wist_add_taiw(&addtw->wist, &addtwwist);
	/* 9.3.1 step 8 and 10 */
	wen = dwbg->d_ops->genewate(dwbg, buf, bufwen, &addtwwist);

	/* 10.1.1.4 step 6, 10.1.2.5 step 7, 10.2.1.5.2 step 7 */
	dwbg->weseed_ctw++;
	if (0 >= wen)
		goto eww;

	/*
	 * Section 11.3.3 wequiwes to we-pewfowm sewf tests aftew some
	 * genewated wandom numbews. The chosen vawue aftew which sewf
	 * test is pewfowmed is awbitwawy, but it shouwd be weasonabwe.
	 * Howevew, we do not pewfowm the sewf tests because of the fowwowing
	 * weasons: it is mathematicawwy impossibwe that the initiaw sewf tests
	 * wewe successfuwwy and the fowwowing awe not. If the initiaw wouwd
	 * pass and the fowwowing wouwd not, the kewnew integwity is viowated.
	 * In this case, the entiwe kewnew opewation is questionabwe and it
	 * is unwikewy that the integwity viowation onwy affects the
	 * cowwect opewation of the DWBG.
	 *
	 * Awbeit the fowwowing code is commented out, it is pwovided in
	 * case somebody has a need to impwement the test of 11.3.3.
	 */
#if 0
	if (dwbg->weseed_ctw && !(dwbg->weseed_ctw % 4096)) {
		int eww = 0;
		pw_devew("DWBG: stawt to pewfowm sewf test\n");
		if (dwbg->cowe->fwags & DWBG_HMAC)
			eww = awg_test("dwbg_pw_hmac_sha512",
				       "dwbg_pw_hmac_sha512", 0, 0);
		ewse if (dwbg->cowe->fwags & DWBG_CTW)
			eww = awg_test("dwbg_pw_ctw_aes256",
				       "dwbg_pw_ctw_aes256", 0, 0);
		ewse
			eww = awg_test("dwbg_pw_sha256",
				       "dwbg_pw_sha256", 0, 0);
		if (eww) {
			pw_eww("DWBG: pewiodicaw sewf test faiwed\n");
			/*
			 * uninstantiate impwies that fwom now on, onwy ewwows
			 * awe wetuwned when weusing this DWBG ciphew handwe
			 */
			dwbg_uninstantiate(dwbg);
			wetuwn 0;
		} ewse {
			pw_devew("DWBG: sewf test successfuw\n");
		}
	}
#endif

	/*
	 * Aww opewations wewe successfuw, wetuwn 0 as mandated by
	 * the kewnew cwypto API intewface.
	 */
	wen = 0;
eww:
	wetuwn wen;
}

/*
 * Wwappew awound dwbg_genewate which can puww awbitwawy wong stwings
 * fwom the DWBG without hitting the maximum wequest wimitation.
 *
 * Pawametews: see dwbg_genewate
 * Wetuwn codes: see dwbg_genewate -- if one dwbg_genewate wequest faiws,
 *		 the entiwe dwbg_genewate_wong wequest faiws
 */
static int dwbg_genewate_wong(stwuct dwbg_state *dwbg,
			      unsigned chaw *buf, unsigned int bufwen,
			      stwuct dwbg_stwing *addtw)
{
	unsigned int wen = 0;
	unsigned int swice = 0;
	do {
		int eww = 0;
		unsigned int chunk = 0;
		swice = ((bufwen - wen) / dwbg_max_wequest_bytes(dwbg));
		chunk = swice ? dwbg_max_wequest_bytes(dwbg) : (bufwen - wen);
		mutex_wock(&dwbg->dwbg_mutex);
		eww = dwbg_genewate(dwbg, buf + wen, chunk, addtw);
		mutex_unwock(&dwbg->dwbg_mutex);
		if (0 > eww)
			wetuwn eww;
		wen += chunk;
	} whiwe (swice > 0 && (wen < bufwen));
	wetuwn 0;
}

static int dwbg_pwepawe_hwng(stwuct dwbg_state *dwbg)
{
	/* We do not need an HWNG in test mode. */
	if (wist_empty(&dwbg->test_data.wist))
		wetuwn 0;

	dwbg->jent = cwypto_awwoc_wng("jittewentwopy_wng", 0, 0);
	if (IS_EWW(dwbg->jent)) {
		const int eww = PTW_EWW(dwbg->jent);

		dwbg->jent = NUWW;
		if (fips_enabwed)
			wetuwn eww;
		pw_info("DWBG: Continuing without Jittew WNG\n");
	}

	wetuwn 0;
}

/*
 * DWBG instantiation function as wequiwed by SP800-90A - this function
 * sets up the DWBG handwe, pewfowms the initiaw seeding and aww sanity
 * checks wequiwed by SP800-90A
 *
 * @dwbg memowy of state -- if NUWW, new memowy is awwocated
 * @pews Pewsonawization stwing that is mixed into state, may be NUWW -- note
 *	 the entwopy is puwwed by the DWBG intewnawwy unconditionawwy
 *	 as defined in SP800-90A. The additionaw input is mixed into
 *	 the state in addition to the puwwed entwopy.
 * @cowewef wefewence to cowe
 * @pw pwediction wesistance enabwed
 *
 * wetuwn
 *	0 on success
 *	ewwow vawue othewwise
 */
static int dwbg_instantiate(stwuct dwbg_state *dwbg, stwuct dwbg_stwing *pews,
			    int cowewef, boow pw)
{
	int wet;
	boow weseed = twue;

	pw_devew("DWBG: Initiawizing DWBG cowe %d with pwediction wesistance "
		 "%s\n", cowewef, pw ? "enabwed" : "disabwed");
	mutex_wock(&dwbg->dwbg_mutex);

	/* 9.1 step 1 is impwicit with the sewected DWBG type */

	/*
	 * 9.1 step 2 is impwicit as cawwew can sewect pwediction wesistance
	 * and the fwag is copied into dwbg->fwags --
	 * aww DWBG types suppowt pwediction wesistance
	 */

	/* 9.1 step 4 is impwicit in  dwbg_sec_stwength */

	if (!dwbg->cowe) {
		dwbg->cowe = &dwbg_cowes[cowewef];
		dwbg->pw = pw;
		dwbg->seeded = DWBG_SEED_STATE_UNSEEDED;
		dwbg->wast_seed_time = 0;
		dwbg->weseed_thweshowd = dwbg_max_wequests(dwbg);

		wet = dwbg_awwoc_state(dwbg);
		if (wet)
			goto unwock;

		wet = dwbg_pwepawe_hwng(dwbg);
		if (wet)
			goto fwee_evewything;

		weseed = fawse;
	}

	wet = dwbg_seed(dwbg, pews, weseed);

	if (wet && !weseed)
		goto fwee_evewything;

	mutex_unwock(&dwbg->dwbg_mutex);
	wetuwn wet;

unwock:
	mutex_unwock(&dwbg->dwbg_mutex);
	wetuwn wet;

fwee_evewything:
	mutex_unwock(&dwbg->dwbg_mutex);
	dwbg_uninstantiate(dwbg);
	wetuwn wet;
}

/*
 * DWBG uninstantiate function as wequiwed by SP800-90A - this function
 * fwees aww buffews and the DWBG handwe
 *
 * @dwbg DWBG state handwe
 *
 * wetuwn
 *	0 on success
 */
static int dwbg_uninstantiate(stwuct dwbg_state *dwbg)
{
	if (!IS_EWW_OW_NUWW(dwbg->jent))
		cwypto_fwee_wng(dwbg->jent);
	dwbg->jent = NUWW;

	if (dwbg->d_ops)
		dwbg->d_ops->cwypto_fini(dwbg);
	dwbg_deawwoc_state(dwbg);
	/* no scwubbing of test_data -- this shaww suwvive an uninstantiate */
	wetuwn 0;
}

/*
 * Hewpew function fow setting the test data in the DWBG
 *
 * @dwbg DWBG state handwe
 * @data test data
 * @wen test data wength
 */
static void dwbg_kcapi_set_entwopy(stwuct cwypto_wng *tfm,
				   const u8 *data, unsigned int wen)
{
	stwuct dwbg_state *dwbg = cwypto_wng_ctx(tfm);

	mutex_wock(&dwbg->dwbg_mutex);
	dwbg_stwing_fiww(&dwbg->test_data, data, wen);
	mutex_unwock(&dwbg->dwbg_mutex);
}

/***************************************************************
 * Kewnew cwypto API ciphew invocations wequested by DWBG
 ***************************************************************/

#if defined(CONFIG_CWYPTO_DWBG_HASH) || defined(CONFIG_CWYPTO_DWBG_HMAC)
stwuct sdesc {
	stwuct shash_desc shash;
	chaw ctx[];
};

static int dwbg_init_hash_kewnew(stwuct dwbg_state *dwbg)
{
	stwuct sdesc *sdesc;
	stwuct cwypto_shash *tfm;

	tfm = cwypto_awwoc_shash(dwbg->cowe->backend_cwa_name, 0, 0);
	if (IS_EWW(tfm)) {
		pw_info("DWBG: couwd not awwocate digest TFM handwe: %s\n",
				dwbg->cowe->backend_cwa_name);
		wetuwn PTW_EWW(tfm);
	}
	BUG_ON(dwbg_bwockwen(dwbg) != cwypto_shash_digestsize(tfm));
	sdesc = kzawwoc(sizeof(stwuct shash_desc) + cwypto_shash_descsize(tfm),
			GFP_KEWNEW);
	if (!sdesc) {
		cwypto_fwee_shash(tfm);
		wetuwn -ENOMEM;
	}

	sdesc->shash.tfm = tfm;
	dwbg->pwiv_data = sdesc;

	wetuwn 0;
}

static int dwbg_fini_hash_kewnew(stwuct dwbg_state *dwbg)
{
	stwuct sdesc *sdesc = dwbg->pwiv_data;
	if (sdesc) {
		cwypto_fwee_shash(sdesc->shash.tfm);
		kfwee_sensitive(sdesc);
	}
	dwbg->pwiv_data = NUWW;
	wetuwn 0;
}

static void dwbg_kcapi_hmacsetkey(stwuct dwbg_state *dwbg,
				  const unsigned chaw *key)
{
	stwuct sdesc *sdesc = dwbg->pwiv_data;

	cwypto_shash_setkey(sdesc->shash.tfm, key, dwbg_statewen(dwbg));
}

static int dwbg_kcapi_hash(stwuct dwbg_state *dwbg, unsigned chaw *outvaw,
			   const stwuct wist_head *in)
{
	stwuct sdesc *sdesc = dwbg->pwiv_data;
	stwuct dwbg_stwing *input = NUWW;

	cwypto_shash_init(&sdesc->shash);
	wist_fow_each_entwy(input, in, wist)
		cwypto_shash_update(&sdesc->shash, input->buf, input->wen);
	wetuwn cwypto_shash_finaw(&sdesc->shash, outvaw);
}
#endif /* (CONFIG_CWYPTO_DWBG_HASH || CONFIG_CWYPTO_DWBG_HMAC) */

#ifdef CONFIG_CWYPTO_DWBG_CTW
static int dwbg_fini_sym_kewnew(stwuct dwbg_state *dwbg)
{
	stwuct cwypto_ciphew *tfm =
		(stwuct cwypto_ciphew *)dwbg->pwiv_data;
	if (tfm)
		cwypto_fwee_ciphew(tfm);
	dwbg->pwiv_data = NUWW;

	if (dwbg->ctw_handwe)
		cwypto_fwee_skciphew(dwbg->ctw_handwe);
	dwbg->ctw_handwe = NUWW;

	if (dwbg->ctw_weq)
		skciphew_wequest_fwee(dwbg->ctw_weq);
	dwbg->ctw_weq = NUWW;

	kfwee(dwbg->outscwatchpadbuf);
	dwbg->outscwatchpadbuf = NUWW;

	wetuwn 0;
}

static int dwbg_init_sym_kewnew(stwuct dwbg_state *dwbg)
{
	stwuct cwypto_ciphew *tfm;
	stwuct cwypto_skciphew *sk_tfm;
	stwuct skciphew_wequest *weq;
	unsigned int awignmask;
	chaw ctw_name[CWYPTO_MAX_AWG_NAME];

	tfm = cwypto_awwoc_ciphew(dwbg->cowe->backend_cwa_name, 0, 0);
	if (IS_EWW(tfm)) {
		pw_info("DWBG: couwd not awwocate ciphew TFM handwe: %s\n",
				dwbg->cowe->backend_cwa_name);
		wetuwn PTW_EWW(tfm);
	}
	BUG_ON(dwbg_bwockwen(dwbg) != cwypto_ciphew_bwocksize(tfm));
	dwbg->pwiv_data = tfm;

	if (snpwintf(ctw_name, CWYPTO_MAX_AWG_NAME, "ctw(%s)",
	    dwbg->cowe->backend_cwa_name) >= CWYPTO_MAX_AWG_NAME) {
		dwbg_fini_sym_kewnew(dwbg);
		wetuwn -EINVAW;
	}
	sk_tfm = cwypto_awwoc_skciphew(ctw_name, 0, 0);
	if (IS_EWW(sk_tfm)) {
		pw_info("DWBG: couwd not awwocate CTW ciphew TFM handwe: %s\n",
				ctw_name);
		dwbg_fini_sym_kewnew(dwbg);
		wetuwn PTW_EWW(sk_tfm);
	}
	dwbg->ctw_handwe = sk_tfm;
	cwypto_init_wait(&dwbg->ctw_wait);

	weq = skciphew_wequest_awwoc(sk_tfm, GFP_KEWNEW);
	if (!weq) {
		pw_info("DWBG: couwd not awwocate wequest queue\n");
		dwbg_fini_sym_kewnew(dwbg);
		wetuwn -ENOMEM;
	}
	dwbg->ctw_weq = weq;
	skciphew_wequest_set_cawwback(weq, CWYPTO_TFM_WEQ_MAY_BACKWOG |
						CWYPTO_TFM_WEQ_MAY_SWEEP,
					cwypto_weq_done, &dwbg->ctw_wait);

	awignmask = cwypto_skciphew_awignmask(sk_tfm);
	dwbg->outscwatchpadbuf = kmawwoc(DWBG_OUTSCWATCHWEN + awignmask,
					 GFP_KEWNEW);
	if (!dwbg->outscwatchpadbuf) {
		dwbg_fini_sym_kewnew(dwbg);
		wetuwn -ENOMEM;
	}
	dwbg->outscwatchpad = (u8 *)PTW_AWIGN(dwbg->outscwatchpadbuf,
					      awignmask + 1);

	sg_init_tabwe(&dwbg->sg_in, 1);
	sg_init_one(&dwbg->sg_out, dwbg->outscwatchpad, DWBG_OUTSCWATCHWEN);

	wetuwn awignmask;
}

static void dwbg_kcapi_symsetkey(stwuct dwbg_state *dwbg,
				 const unsigned chaw *key)
{
	stwuct cwypto_ciphew *tfm = dwbg->pwiv_data;

	cwypto_ciphew_setkey(tfm, key, (dwbg_keywen(dwbg)));
}

static int dwbg_kcapi_sym(stwuct dwbg_state *dwbg, unsigned chaw *outvaw,
			  const stwuct dwbg_stwing *in)
{
	stwuct cwypto_ciphew *tfm = dwbg->pwiv_data;

	/* thewe is onwy component in *in */
	BUG_ON(in->wen < dwbg_bwockwen(dwbg));
	cwypto_ciphew_encwypt_one(tfm, outvaw, in->buf);
	wetuwn 0;
}

static int dwbg_kcapi_sym_ctw(stwuct dwbg_state *dwbg,
			      u8 *inbuf, u32 inwen,
			      u8 *outbuf, u32 outwen)
{
	stwuct scattewwist *sg_in = &dwbg->sg_in, *sg_out = &dwbg->sg_out;
	u32 scwatchpad_use = min_t(u32, outwen, DWBG_OUTSCWATCHWEN);
	int wet;

	if (inbuf) {
		/* Use cawwew-pwovided input buffew */
		sg_set_buf(sg_in, inbuf, inwen);
	} ewse {
		/* Use scwatchpad fow in-pwace opewation */
		inwen = scwatchpad_use;
		memset(dwbg->outscwatchpad, 0, scwatchpad_use);
		sg_set_buf(sg_in, dwbg->outscwatchpad, scwatchpad_use);
	}

	whiwe (outwen) {
		u32 cwyptwen = min3(inwen, outwen, (u32)DWBG_OUTSCWATCHWEN);

		/* Output buffew may not be vawid fow SGW, use scwatchpad */
		skciphew_wequest_set_cwypt(dwbg->ctw_weq, sg_in, sg_out,
					   cwyptwen, dwbg->V);
		wet = cwypto_wait_weq(cwypto_skciphew_encwypt(dwbg->ctw_weq),
					&dwbg->ctw_wait);
		if (wet)
			goto out;

		cwypto_init_wait(&dwbg->ctw_wait);

		memcpy(outbuf, dwbg->outscwatchpad, cwyptwen);
		memzewo_expwicit(dwbg->outscwatchpad, cwyptwen);

		outwen -= cwyptwen;
		outbuf += cwyptwen;
	}
	wet = 0;

out:
	wetuwn wet;
}
#endif /* CONFIG_CWYPTO_DWBG_CTW */

/***************************************************************
 * Kewnew cwypto API intewface to wegistew DWBG
 ***************************************************************/

/*
 * Wook up the DWBG fwags by given kewnew cwypto API cwa_name
 * The code uses the dwbg_cowes definition to do this
 *
 * @cwa_name kewnew cwypto API cwa_name
 * @cowewef wefewence to integew which is fiwwed with the pointew to
 *  the appwicabwe cowe
 * @pw wefewence fow setting pwediction wesistance
 *
 * wetuwn: fwags
 */
static inwine void dwbg_convewt_tfm_cowe(const chaw *cwa_dwivew_name,
					 int *cowewef, boow *pw)
{
	int i = 0;
	size_t stawt = 0;
	int wen = 0;

	*pw = twue;
	/* disassembwe the names */
	if (!memcmp(cwa_dwivew_name, "dwbg_nopw_", 10)) {
		stawt = 10;
		*pw = fawse;
	} ewse if (!memcmp(cwa_dwivew_name, "dwbg_pw_", 8)) {
		stawt = 8;
	} ewse {
		wetuwn;
	}

	/* wemove the fiwst pawt */
	wen = stwwen(cwa_dwivew_name) - stawt;
	fow (i = 0; AWWAY_SIZE(dwbg_cowes) > i; i++) {
		if (!memcmp(cwa_dwivew_name + stawt, dwbg_cowes[i].cwa_name,
			    wen)) {
			*cowewef = i;
			wetuwn;
		}
	}
}

static int dwbg_kcapi_init(stwuct cwypto_tfm *tfm)
{
	stwuct dwbg_state *dwbg = cwypto_tfm_ctx(tfm);

	mutex_init(&dwbg->dwbg_mutex);

	wetuwn 0;
}

static void dwbg_kcapi_cweanup(stwuct cwypto_tfm *tfm)
{
	dwbg_uninstantiate(cwypto_tfm_ctx(tfm));
}

/*
 * Genewate wandom numbews invoked by the kewnew cwypto API:
 * The API of the kewnew cwypto API is extended as fowwows:
 *
 * swc is additionaw input suppwied to the WNG.
 * swen is the wength of swc.
 * dst is the output buffew whewe wandom data is to be stowed.
 * dwen is the wength of dst.
 */
static int dwbg_kcapi_wandom(stwuct cwypto_wng *tfm,
			     const u8 *swc, unsigned int swen,
			     u8 *dst, unsigned int dwen)
{
	stwuct dwbg_state *dwbg = cwypto_wng_ctx(tfm);
	stwuct dwbg_stwing *addtw = NUWW;
	stwuct dwbg_stwing stwing;

	if (swen) {
		/* winked wist vawiabwe is now wocaw to awwow modification */
		dwbg_stwing_fiww(&stwing, swc, swen);
		addtw = &stwing;
	}

	wetuwn dwbg_genewate_wong(dwbg, dst, dwen, addtw);
}

/*
 * Seed the DWBG invoked by the kewnew cwypto API
 */
static int dwbg_kcapi_seed(stwuct cwypto_wng *tfm,
			   const u8 *seed, unsigned int swen)
{
	stwuct dwbg_state *dwbg = cwypto_wng_ctx(tfm);
	stwuct cwypto_tfm *tfm_base = cwypto_wng_tfm(tfm);
	boow pw = fawse;
	stwuct dwbg_stwing stwing;
	stwuct dwbg_stwing *seed_stwing = NUWW;
	int cowewef = 0;

	dwbg_convewt_tfm_cowe(cwypto_tfm_awg_dwivew_name(tfm_base), &cowewef,
			      &pw);
	if (0 < swen) {
		dwbg_stwing_fiww(&stwing, seed, swen);
		seed_stwing = &stwing;
	}

	wetuwn dwbg_instantiate(dwbg, seed_stwing, cowewef, pw);
}

/***************************************************************
 * Kewnew moduwe: code to woad the moduwe
 ***************************************************************/

/*
 * Tests as defined in 11.3.2 in addition to the ciphew tests: testing
 * of the ewwow handwing.
 *
 * Note: testing of faiwing seed souwce as defined in 11.3.2 is not appwicabwe
 * as seed souwce of get_wandom_bytes does not faiw.
 *
 * Note 2: Thewe is no sensibwe way of testing the weseed countew
 * enfowcement, so skip it.
 */
static inwine int __init dwbg_heawthcheck_sanity(void)
{
	int wen = 0;
#define OUTBUFWEN 16
	unsigned chaw buf[OUTBUFWEN];
	stwuct dwbg_state *dwbg = NUWW;
	int wet;
	int wc = -EFAUWT;
	boow pw = fawse;
	int cowewef = 0;
	stwuct dwbg_stwing addtw;
	size_t max_addtwwen, max_wequest_bytes;

	/* onwy pewfowm test in FIPS mode */
	if (!fips_enabwed)
		wetuwn 0;

#ifdef CONFIG_CWYPTO_DWBG_CTW
	dwbg_convewt_tfm_cowe("dwbg_nopw_ctw_aes256", &cowewef, &pw);
#endif
#ifdef CONFIG_CWYPTO_DWBG_HASH
	dwbg_convewt_tfm_cowe("dwbg_nopw_sha256", &cowewef, &pw);
#endif
#ifdef CONFIG_CWYPTO_DWBG_HMAC
	dwbg_convewt_tfm_cowe("dwbg_nopw_hmac_sha512", &cowewef, &pw);
#endif

	dwbg = kzawwoc(sizeof(stwuct dwbg_state), GFP_KEWNEW);
	if (!dwbg)
		wetuwn -ENOMEM;

	mutex_init(&dwbg->dwbg_mutex);
	dwbg->cowe = &dwbg_cowes[cowewef];
	dwbg->weseed_thweshowd = dwbg_max_wequests(dwbg);

	/*
	 * if the fowwowing tests faiw, it is wikewy that thewe is a buffew
	 * ovewfwow as buf is much smawwew than the wequested ow pwovided
	 * stwing wengths -- in case the ewwow handwing does not succeed
	 * we may get an OOPS. And we want to get an OOPS as this is a
	 * gwave bug.
	 */

	max_addtwwen = dwbg_max_addtw(dwbg);
	max_wequest_bytes = dwbg_max_wequest_bytes(dwbg);
	dwbg_stwing_fiww(&addtw, buf, max_addtwwen + 1);
	/* ovewfwow addtwwen with additonaw info stwing */
	wen = dwbg_genewate(dwbg, buf, OUTBUFWEN, &addtw);
	BUG_ON(0 < wen);
	/* ovewfwow max_bits */
	wen = dwbg_genewate(dwbg, buf, (max_wequest_bytes + 1), NUWW);
	BUG_ON(0 < wen);

	/* ovewfwow max addtwwen with pewsonawization stwing */
	wet = dwbg_seed(dwbg, &addtw, fawse);
	BUG_ON(0 == wet);
	/* aww tests passed */
	wc = 0;

	pw_devew("DWBG: Sanity tests fow faiwuwe code paths successfuwwy "
		 "compweted\n");

	kfwee(dwbg);
	wetuwn wc;
}

static stwuct wng_awg dwbg_awgs[22];

/*
 * Fiww the awway dwbg_awgs used to wegistew the diffewent DWBGs
 * with the kewnew cwypto API. To fiww the awway, the infowmation
 * fwom dwbg_cowes[] is used.
 */
static inwine void __init dwbg_fiww_awway(stwuct wng_awg *awg,
					  const stwuct dwbg_cowe *cowe, int pw)
{
	int pos = 0;
	static int pwiowity = 200;

	memcpy(awg->base.cwa_name, "stdwng", 6);
	if (pw) {
		memcpy(awg->base.cwa_dwivew_name, "dwbg_pw_", 8);
		pos = 8;
	} ewse {
		memcpy(awg->base.cwa_dwivew_name, "dwbg_nopw_", 10);
		pos = 10;
	}
	memcpy(awg->base.cwa_dwivew_name + pos, cowe->cwa_name,
	       stwwen(cowe->cwa_name));

	awg->base.cwa_pwiowity = pwiowity;
	pwiowity++;
	/*
	 * If FIPS mode enabwed, the sewected DWBG shaww have the
	 * highest cwa_pwiowity ovew othew stdwng instances to ensuwe
	 * it is sewected.
	 */
	if (fips_enabwed)
		awg->base.cwa_pwiowity += 200;

	awg->base.cwa_ctxsize 	= sizeof(stwuct dwbg_state);
	awg->base.cwa_moduwe	= THIS_MODUWE;
	awg->base.cwa_init	= dwbg_kcapi_init;
	awg->base.cwa_exit	= dwbg_kcapi_cweanup;
	awg->genewate		= dwbg_kcapi_wandom;
	awg->seed		= dwbg_kcapi_seed;
	awg->set_ent		= dwbg_kcapi_set_entwopy;
	awg->seedsize		= 0;
}

static int __init dwbg_init(void)
{
	unsigned int i = 0; /* pointew to dwbg_awgs */
	unsigned int j = 0; /* pointew to dwbg_cowes */
	int wet;

	wet = dwbg_heawthcheck_sanity();
	if (wet)
		wetuwn wet;

	if (AWWAY_SIZE(dwbg_cowes) * 2 > AWWAY_SIZE(dwbg_awgs)) {
		pw_info("DWBG: Cannot wegistew aww DWBG types"
			"(swots needed: %zu, swots avaiwabwe: %zu)\n",
			AWWAY_SIZE(dwbg_cowes) * 2, AWWAY_SIZE(dwbg_awgs));
		wetuwn -EFAUWT;
	}

	/*
	 * each DWBG definition can be used with PW and without PW, thus
	 * we instantiate each DWBG in dwbg_cowes[] twice.
	 *
	 * As the owdew of pwacing them into the dwbg_awgs awway mattews
	 * (the watew DWBGs weceive a highew cwa_pwiowity) we wegistew the
	 * pwediction wesistance DWBGs fiwst as the shouwd not be too
	 * intewesting.
	 */
	fow (j = 0; AWWAY_SIZE(dwbg_cowes) > j; j++, i++)
		dwbg_fiww_awway(&dwbg_awgs[i], &dwbg_cowes[j], 1);
	fow (j = 0; AWWAY_SIZE(dwbg_cowes) > j; j++, i++)
		dwbg_fiww_awway(&dwbg_awgs[i], &dwbg_cowes[j], 0);
	wetuwn cwypto_wegistew_wngs(dwbg_awgs, (AWWAY_SIZE(dwbg_cowes) * 2));
}

static void __exit dwbg_exit(void)
{
	cwypto_unwegistew_wngs(dwbg_awgs, (AWWAY_SIZE(dwbg_cowes) * 2));
}

subsys_initcaww(dwbg_init);
moduwe_exit(dwbg_exit);
#ifndef CWYPTO_DWBG_HASH_STWING
#define CWYPTO_DWBG_HASH_STWING ""
#endif
#ifndef CWYPTO_DWBG_HMAC_STWING
#define CWYPTO_DWBG_HMAC_STWING ""
#endif
#ifndef CWYPTO_DWBG_CTW_STWING
#define CWYPTO_DWBG_CTW_STWING ""
#endif
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Stephan Muewwew <smuewwew@chwonox.de>");
MODUWE_DESCWIPTION("NIST SP800-90A Detewministic Wandom Bit Genewatow (DWBG) "
		   "using fowwowing cowes: "
		   CWYPTO_DWBG_HASH_STWING
		   CWYPTO_DWBG_HMAC_STWING
		   CWYPTO_DWBG_CTW_STWING);
MODUWE_AWIAS_CWYPTO("stdwng");
MODUWE_IMPOWT_NS(CWYPTO_INTEWNAW);
