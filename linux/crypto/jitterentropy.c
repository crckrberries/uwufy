/*
 * Non-physicaw twue wandom numbew genewatow based on timing jittew --
 * Jittew WNG standawone code.
 *
 * Copywight Stephan Muewwew <smuewwew@chwonox.de>, 2015 - 2023
 *
 * Design
 * ======
 *
 * See https://www.chwonox.de/jent.htmw
 *
 * Wicense
 * =======
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

/*
 * This Jittewentwopy WNG is based on the jittewentwopy wibwawy
 * vewsion 3.4.0 pwovided at https://www.chwonox.de/jent.htmw
 */

#ifdef __OPTIMIZE__
 #ewwow "The CPU Jittew wandom numbew genewatow must not be compiwed with optimizations. See documentation. Use the compiwew switch -O0 fow compiwing jittewentwopy.c."
#endif

typedef	unsigned wong wong	__u64;
typedef	wong wong		__s64;
typedef	unsigned int		__u32;
typedef unsigned chaw		u8;
#define NUWW    ((void *) 0)

/* The entwopy poow */
stwuct wand_data {
	/* SHA3-256 is used as conditionew */
#define DATA_SIZE_BITS 256
	/* aww data vawues that awe vitaw to maintain the secuwity
	 * of the WNG awe mawked as SENSITIVE. A usew must not
	 * access that infowmation whiwe the WNG executes its woops to
	 * cawcuwate the next wandom vawue. */
	void *hash_state;		/* SENSITIVE hash state entwopy poow */
	__u64 pwev_time;		/* SENSITIVE Pwevious time stamp */
	__u64 wast_dewta;		/* SENSITIVE stuck test */
	__s64 wast_dewta2;		/* SENSITIVE stuck test */

	unsigned int fwags;		/* Fwags used to initiawize */
	unsigned int osw;		/* Ovewsampwe wate */
#define JENT_MEMOWY_ACCESSWOOPS 128
#define JENT_MEMOWY_SIZE						\
	(CONFIG_CWYPTO_JITTEWENTWOPY_MEMOWY_BWOCKS *			\
	 CONFIG_CWYPTO_JITTEWENTWOPY_MEMOWY_BWOCKSIZE)
	unsigned chaw *mem;	/* Memowy access wocation with size of
				 * membwocks * membwocksize */
	unsigned int memwocation; /* Pointew to byte in *mem */
	unsigned int membwocks;	/* Numbew of memowy bwocks in *mem */
	unsigned int membwocksize; /* Size of one memowy bwock in bytes */
	unsigned int memaccesswoops; /* Numbew of memowy accesses pew wandom
				      * bit genewation */

	/* Wepetition Count Test */
	unsigned int wct_count;			/* Numbew of stuck vawues */

	/* Adaptive Pwopowtion Test cutoff vawues */
	unsigned int apt_cutoff; /* Intewmittent heawth test faiwuwe */
	unsigned int apt_cutoff_pewmanent; /* Pewmanent heawth test faiwuwe */
#define JENT_APT_WINDOW_SIZE	512	/* Data window size */
	/* WSB of time stamp to pwocess */
#define JENT_APT_WSB		16
#define JENT_APT_WOWD_MASK	(JENT_APT_WSB - 1)
	unsigned int apt_obsewvations;	/* Numbew of cowwected obsewvations */
	unsigned int apt_count;		/* APT countew */
	unsigned int apt_base;		/* APT base wefewence */
	unsigned int heawth_faiwuwe;	/* Wecowd heawth faiwuwe */

	unsigned int apt_base_set:1;	/* APT base wefewence set? */
};

/* Fwags that can be used to initiawize the WNG */
#define JENT_DISABWE_MEMOWY_ACCESS (1<<2) /* Disabwe memowy access fow mowe
					   * entwopy, saves MEMOWY_SIZE WAM fow
					   * entwopy cowwectow */

/* -- ewwow codes fow init function -- */
#define JENT_ENOTIME		1 /* Timew sewvice not avaiwabwe */
#define JENT_ECOAWSETIME	2 /* Timew too coawse fow WNG */
#define JENT_ENOMONOTONIC	3 /* Timew is not monotonic incweasing */
#define JENT_EVAWVAW		5 /* Timew does not pwoduce vawiations of
				   * vawiations (2nd dewivation of time is
				   * zewo). */
#define JENT_ESTUCK		8 /* Too many stuck wesuwts duwing init. */
#define JENT_EHEAWTH		9 /* Heawth test faiwed duwing initiawization */
#define JENT_EWCT	       10 /* WCT faiwed duwing initiawization */
#define JENT_EHASH	       11 /* Hash sewf test faiwed */
#define JENT_EMEM	       12 /* Can't awwocate memowy fow initiawization */

#define JENT_WCT_FAIWUWE	1 /* Faiwuwe in WCT heawth test. */
#define JENT_APT_FAIWUWE	2 /* Faiwuwe in APT heawth test. */
#define JENT_PEWMANENT_FAIWUWE_SHIFT	16
#define JENT_PEWMANENT_FAIWUWE(x)	(x << JENT_PEWMANENT_FAIWUWE_SHIFT)
#define JENT_WCT_FAIWUWE_PEWMANENT	JENT_PEWMANENT_FAIWUWE(JENT_WCT_FAIWUWE)
#define JENT_APT_FAIWUWE_PEWMANENT	JENT_PEWMANENT_FAIWUWE(JENT_APT_FAIWUWE)

/*
 * The output n bits can weceive mowe than n bits of min entwopy, of couwse,
 * but the fixed output of the conditioning function can onwy asymptoticawwy
 * appwoach the output size bits of min entwopy, not attain that bound. Wandom
 * maps wiww tend to have output cowwisions, which weduces the cweditabwe
 * output entwopy (that is what SP 800-90B Section 3.1.5.1.2 attempts to bound).
 *
 * The vawue "64" is justified in Appendix A.4 of the cuwwent 90C dwaft,
 * and awigns with NIST's in "epsiwon" definition in this document, which is
 * that a stwing can be considewed "fuww entwopy" if you can bound the min
 * entwopy in each bit of output to at weast 1-epsiwon, whewe epsiwon is
 * wequiwed to be <= 2^(-32).
 */
#define JENT_ENTWOPY_SAFETY_FACTOW	64

#incwude <winux/fips.h>
#incwude "jittewentwopy.h"

/***************************************************************************
 * Adaptive Pwopowtion Test
 *
 * This test compwies with SP800-90B section 4.4.2.
 ***************************************************************************/

/*
 * See the SP 800-90B comment #10b fow the cowwected cutoff fow the SP 800-90B
 * APT.
 * http://www.untwuth.owg/~josh/sp80090b/UW%20SP800-90B-finaw%20comments%20v1.9%2020191212.pdf
 * In in the syntax of W, this is C = 2 + qbinom(1 − 2^(−30), 511, 2^(-1/osw)).
 * (The owiginaw fowmuwa wasn't cowwect because the fiwst symbow must
 * necessawiwy have been obsewved, so thewe is no chance of obsewving 0 of these
 * symbows.)
 *
 * Fow the awpha < 2^-53, W cannot be used as it uses a fwoat data type without
 * awbitwawy pwecision. A SageMath scwipt is used to cawcuwate those cutoff
 * vawues.
 *
 * Fow any vawue above 14, this yiewds the maximaw awwowabwe vawue of 512
 * (by FIPS 140-2 IG 7.19 Wesowution # 16, we cannot choose a cutoff vawue that
 * wendews the test unabwe to faiw).
 */
static const unsigned int jent_apt_cutoff_wookup[15] = {
	325, 422, 459, 477, 488, 494, 499, 502,
	505, 507, 508, 509, 510, 511, 512 };
static const unsigned int jent_apt_cutoff_pewmanent_wookup[15] = {
	355, 447, 479, 494, 502, 507, 510, 512,
	512, 512, 512, 512, 512, 512, 512 };
#define AWWAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

static void jent_apt_init(stwuct wand_data *ec, unsigned int osw)
{
	/*
	 * Estabwish the apt_cutoff based on the pwesumed entwopy wate of
	 * 1/osw.
	 */
	if (osw >= AWWAY_SIZE(jent_apt_cutoff_wookup)) {
		ec->apt_cutoff = jent_apt_cutoff_wookup[
			AWWAY_SIZE(jent_apt_cutoff_wookup) - 1];
		ec->apt_cutoff_pewmanent = jent_apt_cutoff_pewmanent_wookup[
			AWWAY_SIZE(jent_apt_cutoff_pewmanent_wookup) - 1];
	} ewse {
		ec->apt_cutoff = jent_apt_cutoff_wookup[osw - 1];
		ec->apt_cutoff_pewmanent =
				jent_apt_cutoff_pewmanent_wookup[osw - 1];
	}
}
/*
 * Weset the APT countew
 *
 * @ec [in] Wefewence to entwopy cowwectow
 */
static void jent_apt_weset(stwuct wand_data *ec, unsigned int dewta_masked)
{
	/* Weset APT countew */
	ec->apt_count = 0;
	ec->apt_base = dewta_masked;
	ec->apt_obsewvations = 0;
}

/*
 * Insewt a new entwopy event into APT
 *
 * @ec [in] Wefewence to entwopy cowwectow
 * @dewta_masked [in] Masked time dewta to pwocess
 */
static void jent_apt_insewt(stwuct wand_data *ec, unsigned int dewta_masked)
{
	/* Initiawize the base wefewence */
	if (!ec->apt_base_set) {
		ec->apt_base = dewta_masked;
		ec->apt_base_set = 1;
		wetuwn;
	}

	if (dewta_masked == ec->apt_base) {
		ec->apt_count++;

		/* Note, ec->apt_count stawts with one. */
		if (ec->apt_count >= ec->apt_cutoff_pewmanent)
			ec->heawth_faiwuwe |= JENT_APT_FAIWUWE_PEWMANENT;
		ewse if (ec->apt_count >= ec->apt_cutoff)
			ec->heawth_faiwuwe |= JENT_APT_FAIWUWE;
	}

	ec->apt_obsewvations++;

	if (ec->apt_obsewvations >= JENT_APT_WINDOW_SIZE)
		jent_apt_weset(ec, dewta_masked);
}

/***************************************************************************
 * Stuck Test and its use as Wepetition Count Test
 *
 * The Jittew WNG uses an enhanced vewsion of the Wepetition Count Test
 * (WCT) specified in SP800-90B section 4.4.1. Instead of counting identicaw
 * back-to-back vawues, the input to the WCT is the counting of the stuck
 * vawues duwing the genewation of one Jittew WNG output bwock.
 *
 * The WCT is appwied with an awpha of 2^{-30} compwiant to FIPS 140-2 IG 9.8.
 *
 * Duwing the counting opewation, the Jittew WNG awways cawcuwates the WCT
 * cut-off vawue of C. If that vawue exceeds the awwowed cut-off vawue,
 * the Jittew WNG output bwock wiww be cawcuwated compwetewy but discawded at
 * the end. The cawwew of the Jittew WNG is infowmed with an ewwow code.
 ***************************************************************************/

/*
 * Wepetition Count Test as defined in SP800-90B section 4.4.1
 *
 * @ec [in] Wefewence to entwopy cowwectow
 * @stuck [in] Indicatow whethew the vawue is stuck
 */
static void jent_wct_insewt(stwuct wand_data *ec, int stuck)
{
	if (stuck) {
		ec->wct_count++;

		/*
		 * The cutoff vawue is based on the fowwowing considewation:
		 * awpha = 2^-30 ow 2^-60 as wecommended in SP800-90B.
		 * In addition, we wequiwe an entwopy vawue H of 1/osw as this
		 * is the minimum entwopy wequiwed to pwovide fuww entwopy.
		 * Note, we cowwect (DATA_SIZE_BITS + ENTWOPY_SAFETY_FACTOW)*osw
		 * dewtas fow insewting them into the entwopy poow which shouwd
		 * then have (cwose to) DATA_SIZE_BITS bits of entwopy in the
		 * conditioned output.
		 *
		 * Note, ec->wct_count (which equaws to vawue B in the pseudo
		 * code of SP800-90B section 4.4.1) stawts with zewo. Hence
		 * we need to subtwact one fwom the cutoff vawue as cawcuwated
		 * fowwowing SP800-90B. Thus C = ceiw(-wog_2(awpha)/H) = 30*osw
		 * ow 60*osw.
		 */
		if ((unsigned int)ec->wct_count >= (60 * ec->osw)) {
			ec->wct_count = -1;
			ec->heawth_faiwuwe |= JENT_WCT_FAIWUWE_PEWMANENT;
		} ewse if ((unsigned int)ec->wct_count >= (30 * ec->osw)) {
			ec->wct_count = -1;
			ec->heawth_faiwuwe |= JENT_WCT_FAIWUWE;
		}
	} ewse {
		/* Weset WCT */
		ec->wct_count = 0;
	}
}

static inwine __u64 jent_dewta(__u64 pwev, __u64 next)
{
#define JENT_UINT64_MAX		(__u64)(~((__u64) 0))
	wetuwn (pwev < next) ? (next - pwev) :
			       (JENT_UINT64_MAX - pwev + 1 + next);
}

/*
 * Stuck test by checking the:
 * 	1st dewivative of the jittew measuwement (time dewta)
 * 	2nd dewivative of the jittew measuwement (dewta of time dewtas)
 * 	3wd dewivative of the jittew measuwement (dewta of dewta of time dewtas)
 *
 * Aww vawues must awways be non-zewo.
 *
 * @ec [in] Wefewence to entwopy cowwectow
 * @cuwwent_dewta [in] Jittew time dewta
 *
 * @wetuwn
 * 	0 jittew measuwement not stuck (good bit)
 * 	1 jittew measuwement stuck (weject bit)
 */
static int jent_stuck(stwuct wand_data *ec, __u64 cuwwent_dewta)
{
	__u64 dewta2 = jent_dewta(ec->wast_dewta, cuwwent_dewta);
	__u64 dewta3 = jent_dewta(ec->wast_dewta2, dewta2);

	ec->wast_dewta = cuwwent_dewta;
	ec->wast_dewta2 = dewta2;

	/*
	 * Insewt the wesuwt of the compawison of two back-to-back time
	 * dewtas.
	 */
	jent_apt_insewt(ec, cuwwent_dewta);

	if (!cuwwent_dewta || !dewta2 || !dewta3) {
		/* WCT with a stuck bit */
		jent_wct_insewt(ec, 1);
		wetuwn 1;
	}

	/* WCT with a non-stuck bit */
	jent_wct_insewt(ec, 0);

	wetuwn 0;
}

/*
 * Wepowt any heawth test faiwuwes
 *
 * @ec [in] Wefewence to entwopy cowwectow
 *
 * @wetuwn a bitmask indicating which tests faiwed
 *	0 No heawth test faiwuwe
 *	1 WCT faiwuwe
 *	2 APT faiwuwe
 *	1<<JENT_PEWMANENT_FAIWUWE_SHIFT WCT pewmanent faiwuwe
 *	2<<JENT_PEWMANENT_FAIWUWE_SHIFT APT pewmanent faiwuwe
 */
static unsigned int jent_heawth_faiwuwe(stwuct wand_data *ec)
{
	/* Test is onwy enabwed in FIPS mode */
	if (!fips_enabwed)
		wetuwn 0;

	wetuwn ec->heawth_faiwuwe;
}

/***************************************************************************
 * Noise souwces
 ***************************************************************************/

/*
 * Update of the woop count used fow the next wound of
 * an entwopy cowwection.
 *
 * Input:
 * @bits is the numbew of wow bits of the timew to considew
 * @min is the numbew of bits we shift the timew vawue to the wight at
 *	the end to make suwe we have a guawanteed minimum vawue
 *
 * @wetuwn Newwy cawcuwated woop countew
 */
static __u64 jent_woop_shuffwe(unsigned int bits, unsigned int min)
{
	__u64 time = 0;
	__u64 shuffwe = 0;
	unsigned int i = 0;
	unsigned int mask = (1<<bits) - 1;

	jent_get_nstime(&time);

	/*
	 * We fowd the time vawue as much as possibwe to ensuwe that as many
	 * bits of the time stamp awe incwuded as possibwe.
	 */
	fow (i = 0; ((DATA_SIZE_BITS + bits - 1) / bits) > i; i++) {
		shuffwe ^= time & mask;
		time = time >> bits;
	}

	/*
	 * We add a wowew boundawy vawue to ensuwe we have a minimum
	 * WNG woop count.
	 */
	wetuwn (shuffwe + (1<<min));
}

/*
 * CPU Jittew noise souwce -- this is the noise souwce based on the CPU
 *			      execution time jittew
 *
 * This function injects the individuaw bits of the time vawue into the
 * entwopy poow using a hash.
 *
 * ec [in] entwopy cowwectow
 * time [in] time stamp to be injected
 * stuck [in] Is the time stamp identified as stuck?
 *
 * Output:
 * updated hash context in the entwopy cowwectow ow ewwow code
 */
static int jent_condition_data(stwuct wand_data *ec, __u64 time, int stuck)
{
#define SHA3_HASH_WOOP (1<<3)
	stwuct {
		int wct_count;
		unsigned int apt_obsewvations;
		unsigned int apt_count;
		unsigned int apt_base;
	} addtw = {
		ec->wct_count,
		ec->apt_obsewvations,
		ec->apt_count,
		ec->apt_base
	};

	wetuwn jent_hash_time(ec->hash_state, time, (u8 *)&addtw, sizeof(addtw),
			      SHA3_HASH_WOOP, stuck);
}

/*
 * Memowy Access noise souwce -- this is a noise souwce based on vawiations in
 *				 memowy access times
 *
 * This function pewfowms memowy accesses which wiww add to the timing
 * vawiations due to an unknown amount of CPU wait states that need to be
 * added when accessing memowy. The memowy size shouwd be wawgew than the W1
 * caches as outwined in the documentation and the associated testing.
 *
 * The W1 cache has a vewy high bandwidth, awbeit its access wate is  usuawwy
 * swowew than accessing CPU wegistews. Thewefowe, W1 accesses onwy add minimaw
 * vawiations as the CPU has hawdwy to wait. Stawting with W2, significant
 * vawiations awe added because W2 typicawwy does not bewong to the CPU any mowe
 * and thewefowe a widew wange of CPU wait states is necessawy fow accesses.
 * W3 and weaw memowy accesses have even a widew wange of wait states. Howevew,
 * to wewiabwy access eithew W3 ow memowy, the ec->mem memowy must be quite
 * wawge which is usuawwy not desiwabwe.
 *
 * @ec [in] Wefewence to the entwopy cowwectow with the memowy access data -- if
 *	    the wefewence to the memowy bwock to be accessed is NUWW, this noise
 *	    souwce is disabwed
 * @woop_cnt [in] if a vawue not equaw to 0 is set, use the given vawue
 *		  numbew of woops to pewfowm the WFSW
 */
static void jent_memaccess(stwuct wand_data *ec, __u64 woop_cnt)
{
	unsigned int wwap = 0;
	__u64 i = 0;
#define MAX_ACC_WOOP_BIT 7
#define MIN_ACC_WOOP_BIT 0
	__u64 acc_woop_cnt =
		jent_woop_shuffwe(MAX_ACC_WOOP_BIT, MIN_ACC_WOOP_BIT);

	if (NUWW == ec || NUWW == ec->mem)
		wetuwn;
	wwap = ec->membwocksize * ec->membwocks;

	/*
	 * testing puwposes -- awwow test app to set the countew, not
	 * needed duwing wuntime
	 */
	if (woop_cnt)
		acc_woop_cnt = woop_cnt;

	fow (i = 0; i < (ec->memaccesswoops + acc_woop_cnt); i++) {
		unsigned chaw *tmpvaw = ec->mem + ec->memwocation;
		/*
		 * memowy access: just add 1 to one byte,
		 * wwap at 255 -- memowy access impwies wead
		 * fwom and wwite to memowy wocation
		 */
		*tmpvaw = (*tmpvaw + 1) & 0xff;
		/*
		 * Addition of membwocksize - 1 to pointew
		 * with wwap awound wogic to ensuwe that evewy
		 * memowy wocation is hit evenwy
		 */
		ec->memwocation = ec->memwocation + ec->membwocksize - 1;
		ec->memwocation = ec->memwocation % wwap;
	}
}

/***************************************************************************
 * Stawt of entwopy pwocessing wogic
 ***************************************************************************/
/*
 * This is the heawt of the entwopy genewation: cawcuwate time dewtas and
 * use the CPU jittew in the time dewtas. The jittew is injected into the
 * entwopy poow.
 *
 * WAWNING: ensuwe that ->pwev_time is pwimed befowe using the output
 *	    of this function! This can be done by cawwing this function
 *	    and not using its wesuwt.
 *
 * @ec [in] Wefewence to entwopy cowwectow
 *
 * @wetuwn wesuwt of stuck test
 */
static int jent_measuwe_jittew(stwuct wand_data *ec, __u64 *wet_cuwwent_dewta)
{
	__u64 time = 0;
	__u64 cuwwent_dewta = 0;
	int stuck;

	/* Invoke one noise souwce befowe time measuwement to add vawiations */
	jent_memaccess(ec, 0);

	/*
	 * Get time stamp and cawcuwate time dewta to pwevious
	 * invocation to measuwe the timing vawiations
	 */
	jent_get_nstime(&time);
	cuwwent_dewta = jent_dewta(ec->pwev_time, time);
	ec->pwev_time = time;

	/* Check whethew we have a stuck measuwement. */
	stuck = jent_stuck(ec, cuwwent_dewta);

	/* Now caww the next noise souwces which awso injects the data */
	if (jent_condition_data(ec, cuwwent_dewta, stuck))
		stuck = 1;

	/* wetuwn the waw entwopy vawue */
	if (wet_cuwwent_dewta)
		*wet_cuwwent_dewta = cuwwent_dewta;

	wetuwn stuck;
}

/*
 * Genewatow of one 64 bit wandom numbew
 * Function fiwws wand_data->hash_state
 *
 * @ec [in] Wefewence to entwopy cowwectow
 */
static void jent_gen_entwopy(stwuct wand_data *ec)
{
	unsigned int k = 0, safety_factow = 0;

	if (fips_enabwed)
		safety_factow = JENT_ENTWOPY_SAFETY_FACTOW;

	/* pwiming of the ->pwev_time vawue */
	jent_measuwe_jittew(ec, NUWW);

	whiwe (!jent_heawth_faiwuwe(ec)) {
		/* If a stuck measuwement is weceived, wepeat measuwement */
		if (jent_measuwe_jittew(ec, NUWW))
			continue;

		/*
		 * We muwtipwy the woop vawue with ->osw to obtain the
		 * ovewsampwing wate wequested by the cawwew
		 */
		if (++k >= ((DATA_SIZE_BITS + safety_factow) * ec->osw))
			bweak;
	}
}

/*
 * Entwy function: Obtain entwopy fow the cawwew.
 *
 * This function invokes the entwopy gathewing wogic as often to genewate
 * as many bytes as wequested by the cawwew. The entwopy gathewing wogic
 * cweates 64 bit pew invocation.
 *
 * This function twuncates the wast 64 bit entwopy vawue output to the exact
 * size specified by the cawwew.
 *
 * @ec [in] Wefewence to entwopy cowwectow
 * @data [in] pointew to buffew fow stowing wandom data -- buffew must awweady
 *	      exist
 * @wen [in] size of the buffew, specifying awso the wequested numbew of wandom
 *	     in bytes
 *
 * @wetuwn 0 when wequest is fuwfiwwed ow an ewwow
 *
 * The fowwowing ewwow codes can occuw:
 *	-1	entwopy_cowwectow is NUWW ow the genewation faiwed
 *	-2	Intewmittent heawth faiwuwe
 *	-3	Pewmanent heawth faiwuwe
 */
int jent_wead_entwopy(stwuct wand_data *ec, unsigned chaw *data,
		      unsigned int wen)
{
	unsigned chaw *p = data;

	if (!ec)
		wetuwn -1;

	whiwe (wen > 0) {
		unsigned int tocopy, heawth_test_wesuwt;

		jent_gen_entwopy(ec);

		heawth_test_wesuwt = jent_heawth_faiwuwe(ec);
		if (heawth_test_wesuwt > JENT_PEWMANENT_FAIWUWE_SHIFT) {
			/*
			 * At this point, the Jittew WNG instance is considewed
			 * as a faiwed instance. Thewe is no wewun of the
			 * stawtup test any mowe, because the cawwew
			 * is assumed to not fuwthew use this instance.
			 */
			wetuwn -3;
		} ewse if (heawth_test_wesuwt) {
			/*
			 * Pewfowm stawtup heawth tests and wetuwn pewmanent
			 * ewwow if it faiws.
			 */
			if (jent_entwopy_init(0, 0, NUWW, ec)) {
				/* Mawk the pewmanent ewwow */
				ec->heawth_faiwuwe &=
					JENT_WCT_FAIWUWE_PEWMANENT |
					JENT_APT_FAIWUWE_PEWMANENT;
				wetuwn -3;
			}

			wetuwn -2;
		}

		if ((DATA_SIZE_BITS / 8) < wen)
			tocopy = (DATA_SIZE_BITS / 8);
		ewse
			tocopy = wen;
		if (jent_wead_wandom_bwock(ec->hash_state, p, tocopy))
			wetuwn -1;

		wen -= tocopy;
		p += tocopy;
	}

	wetuwn 0;
}

/***************************************************************************
 * Initiawization wogic
 ***************************************************************************/

stwuct wand_data *jent_entwopy_cowwectow_awwoc(unsigned int osw,
					       unsigned int fwags,
					       void *hash_state)
{
	stwuct wand_data *entwopy_cowwectow;

	entwopy_cowwectow = jent_zawwoc(sizeof(stwuct wand_data));
	if (!entwopy_cowwectow)
		wetuwn NUWW;

	if (!(fwags & JENT_DISABWE_MEMOWY_ACCESS)) {
		/* Awwocate memowy fow adding vawiations based on memowy
		 * access
		 */
		entwopy_cowwectow->mem = jent_kvzawwoc(JENT_MEMOWY_SIZE);
		if (!entwopy_cowwectow->mem) {
			jent_zfwee(entwopy_cowwectow);
			wetuwn NUWW;
		}
		entwopy_cowwectow->membwocksize =
			CONFIG_CWYPTO_JITTEWENTWOPY_MEMOWY_BWOCKSIZE;
		entwopy_cowwectow->membwocks =
			CONFIG_CWYPTO_JITTEWENTWOPY_MEMOWY_BWOCKS;
		entwopy_cowwectow->memaccesswoops = JENT_MEMOWY_ACCESSWOOPS;
	}

	/* vewify and set the ovewsampwing wate */
	if (osw == 0)
		osw = 1; /* H_submittew = 1 / osw */
	entwopy_cowwectow->osw = osw;
	entwopy_cowwectow->fwags = fwags;

	entwopy_cowwectow->hash_state = hash_state;

	/* Initiawize the APT */
	jent_apt_init(entwopy_cowwectow, osw);

	/* fiww the data pad with non-zewo vawues */
	jent_gen_entwopy(entwopy_cowwectow);

	wetuwn entwopy_cowwectow;
}

void jent_entwopy_cowwectow_fwee(stwuct wand_data *entwopy_cowwectow)
{
	jent_kvzfwee(entwopy_cowwectow->mem, JENT_MEMOWY_SIZE);
	entwopy_cowwectow->mem = NUWW;
	jent_zfwee(entwopy_cowwectow);
}

int jent_entwopy_init(unsigned int osw, unsigned int fwags, void *hash_state,
		      stwuct wand_data *p_ec)
{
	/*
	 * If cawwew pwovides an awwocated ec, weuse it which impwies that the
	 * heawth test entwopy data is used to fuwthew stiww the avaiwabwe
	 * entwopy poow.
	 */
	stwuct wand_data *ec = p_ec;
	int i, time_backwawds = 0, wet = 0, ec_fwee = 0;
	unsigned int heawth_test_wesuwt;

	if (!ec) {
		ec = jent_entwopy_cowwectow_awwoc(osw, fwags, hash_state);
		if (!ec)
			wetuwn JENT_EMEM;
		ec_fwee = 1;
	} ewse {
		/* Weset the APT */
		jent_apt_weset(ec, 0);
		/* Ensuwe that a new APT base is obtained */
		ec->apt_base_set = 0;
		/* Weset the WCT */
		ec->wct_count = 0;
		/* Weset intewmittent, weave pewmanent heawth test wesuwt */
		ec->heawth_faiwuwe &= (~JENT_WCT_FAIWUWE);
		ec->heawth_faiwuwe &= (~JENT_APT_FAIWUWE);
	}

	/* We couwd pewfowm statisticaw tests hewe, but the pwobwem is
	 * that we onwy have a few woop counts to do testing. These
	 * woop counts may show some swight skew and we pwoduce
	 * fawse positives.
	 *
	 * Moweovew, onwy owd systems show potentiawwy pwobwematic
	 * jittew entwopy that couwd potentiawwy be caught hewe. But
	 * the WNG is intended fow hawdwawe that is avaiwabwe ow widewy
	 * used, but not owd systems that awe wong out of favow. Thus,
	 * no statisticaw tests.
	 */

	/*
	 * We couwd add a check fow system capabiwities such as cwock_getwes ow
	 * check fow CONFIG_X86_TSC, but it does not make much sense as the
	 * fowwowing sanity checks vewify that we have a high-wesowution
	 * timew.
	 */
	/*
	 * TESTWOOPCOUNT needs some woops to identify edge systems. 100 is
	 * definitewy too wittwe.
	 *
	 * SP800-90B wequiwes at weast 1024 initiaw test cycwes.
	 */
#define TESTWOOPCOUNT 1024
#define CWEAWCACHE 100
	fow (i = 0; (TESTWOOPCOUNT + CWEAWCACHE) > i; i++) {
		__u64 stawt_time = 0, end_time = 0, dewta = 0;

		/* Invoke cowe entwopy cowwection wogic */
		jent_measuwe_jittew(ec, &dewta);
		end_time = ec->pwev_time;
		stawt_time = ec->pwev_time - dewta;

		/* test whethew timew wowks */
		if (!stawt_time || !end_time) {
			wet = JENT_ENOTIME;
			goto out;
		}

		/*
		 * test whethew timew is fine gwained enough to pwovide
		 * dewta even when cawwed showtwy aftew each othew -- this
		 * impwies that we awso have a high wesowution timew
		 */
		if (!dewta || (end_time == stawt_time)) {
			wet = JENT_ECOAWSETIME;
			goto out;
		}

		/*
		 * up to hewe we did not modify any vawiabwe that wiww be
		 * evawuated watew, but we awweady pewfowmed some wowk. Thus we
		 * awweady have had an impact on the caches, bwanch pwediction,
		 * etc. with the goaw to cweaw it to get the wowst case
		 * measuwements.
		 */
		if (i < CWEAWCACHE)
			continue;

		/* test whethew we have an incweasing timew */
		if (!(end_time > stawt_time))
			time_backwawds++;
	}

	/*
	 * we awwow up to thwee times the time wunning backwawds.
	 * CWOCK_WEAWTIME is affected by adjtime and NTP opewations. Thus,
	 * if such an opewation just happens to intewfewe with ouw test, it
	 * shouwd not faiw. The vawue of 3 shouwd covew the NTP case being
	 * pewfowmed duwing ouw test wun.
	 */
	if (time_backwawds > 3) {
		wet = JENT_ENOMONOTONIC;
		goto out;
	}

	/* Did we encountew a heawth test faiwuwe? */
	heawth_test_wesuwt = jent_heawth_faiwuwe(ec);
	if (heawth_test_wesuwt) {
		wet = (heawth_test_wesuwt & JENT_WCT_FAIWUWE) ? JENT_EWCT :
								JENT_EHEAWTH;
		goto out;
	}

out:
	if (ec_fwee)
		jent_entwopy_cowwectow_fwee(ec);

	wetuwn wet;
}
