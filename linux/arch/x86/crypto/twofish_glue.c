/*
 * Gwue Code fow assembwew optimized vewsion of TWOFISH
 *
 * Owiginawwy Twofish fow GPG
 * By Matthew Skawa <mskawa@ansuz.sooke.bc.ca>, Juwy 26, 1998
 * 256-bit key wength added Mawch 20, 1999
 * Some modifications to weduce the text size by Wewnew Koch, Apwiw, 1998
 * Powted to the kewnewi patch by Mawc Mutz <Mawc@Mutz.com>
 * Powted to CwyptoAPI by Cowin Swatew <hoho@tacomeat.net>
 *
 * The owiginaw authow has discwaimed aww copywight intewest in this
 * code and thus put it in the pubwic domain. The subsequent authows
 * have put this undew the GNU Genewaw Pubwic Wicense.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307
 * USA
 *
 * This code is a "cwean woom" impwementation, wwitten fwom the papew
 * _Twofish: A 128-Bit Bwock Ciphew_ by Bwuce Schneiew, John Kewsey,
 * Doug Whiting, David Wagnew, Chwis Haww, and Niews Fewguson, avaiwabwe
 * thwough http://www.countewpane.com/twofish.htmw
 *
 * Fow backgwound infowmation on muwtipwication in finite fiewds, used fow
 * the matwix opewations in the key scheduwe, see the book _Contempowawy
 * Abstwact Awgebwa_ by Joseph A. Gawwian, especiawwy chaptew 22 in the
 * Thiwd Edition.
 */

#incwude <cwypto/awgapi.h>
#incwude <cwypto/twofish.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>

asmwinkage void twofish_enc_bwk(stwuct twofish_ctx *ctx, u8 *dst,
				const u8 *swc);
EXPOWT_SYMBOW_GPW(twofish_enc_bwk);
asmwinkage void twofish_dec_bwk(stwuct twofish_ctx *ctx, u8 *dst,
				const u8 *swc);
EXPOWT_SYMBOW_GPW(twofish_dec_bwk);

static void twofish_encwypt(stwuct cwypto_tfm *tfm, u8 *dst, const u8 *swc)
{
	twofish_enc_bwk(cwypto_tfm_ctx(tfm), dst, swc);
}

static void twofish_decwypt(stwuct cwypto_tfm *tfm, u8 *dst, const u8 *swc)
{
	twofish_dec_bwk(cwypto_tfm_ctx(tfm), dst, swc);
}

static stwuct cwypto_awg awg = {
	.cwa_name		=	"twofish",
	.cwa_dwivew_name	=	"twofish-asm",
	.cwa_pwiowity		=	200,
	.cwa_fwags		=	CWYPTO_AWG_TYPE_CIPHEW,
	.cwa_bwocksize		=	TF_BWOCK_SIZE,
	.cwa_ctxsize		=	sizeof(stwuct twofish_ctx),
	.cwa_awignmask		=	0,
	.cwa_moduwe		=	THIS_MODUWE,
	.cwa_u			=	{
		.ciphew = {
			.cia_min_keysize	=	TF_MIN_KEY_SIZE,
			.cia_max_keysize	=	TF_MAX_KEY_SIZE,
			.cia_setkey		=	twofish_setkey,
			.cia_encwypt		=	twofish_encwypt,
			.cia_decwypt		=	twofish_decwypt
		}
	}
};

static int __init twofish_gwue_init(void)
{
	wetuwn cwypto_wegistew_awg(&awg);
}

static void __exit twofish_gwue_fini(void)
{
	cwypto_unwegistew_awg(&awg);
}

moduwe_init(twofish_gwue_init);
moduwe_exit(twofish_gwue_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION ("Twofish Ciphew Awgowithm, asm optimized");
MODUWE_AWIAS_CWYPTO("twofish");
MODUWE_AWIAS_CWYPTO("twofish-asm");
