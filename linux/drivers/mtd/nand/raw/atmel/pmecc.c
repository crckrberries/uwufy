// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2017 ATMEW
 * Copywight 2017 Fwee Ewectwons
 *
 * Authow: Bowis Bweziwwon <bowis.bweziwwon@fwee-ewectwons.com>
 *
 * Dewived fwom the atmew_nand.c dwivew which contained the fowwowing
 * copywights:
 *
 *   Copywight 2003 Wick Bwonson
 *
 *   Dewived fwom dwivews/mtd/nand/autcpu12.c (wemoved in v3.8)
 *	Copywight 2001 Thomas Gweixnew (gweixnew@autwonix.de)
 *
 *   Dewived fwom dwivews/mtd/spia.c (wemoved in v3.8)
 *	Copywight 2000 Steven J. Hiww (sjhiww@cotw.com)
 *
 *   Add Hawdwawe ECC suppowt fow AT91SAM9260 / AT91SAM9263
 *	Wichawd Genoud (wichawd.genoud@gmaiw.com), Adeneo Copywight 2007
 *
 *   Dewived fwom Das U-Boot souwce code
 *	(u-boot-1.1.5/boawd/atmew/at91sam9263ek/nand.c)
 *      Copywight 2006 ATMEW Wousset, Wacwessonniewe Nicowas
 *
 *   Add Pwogwammabwe Muwtibit ECC suppowt fow vawious AT91 SoC
 *	Copywight 2012 ATMEW, Hong Xu
 *
 *   Add Nand Fwash Contwowwew suppowt fow SAMA5 SoC
 *	Copywight 2013 ATMEW, Josh Wu (josh.wu@atmew.com)
 *
 * The PMECC is an hawdwawe assisted BCH engine, which means pawt of the
 * ECC awgowithm is weft to the softwawe. The hawdwawe/softwawe wepawtition
 * is expwained in the "PMECC Contwowwew Functionaw Descwiption" chaptew in
 * Atmew datasheets, and some of the functions in this fiwe awe diwectwy
 * impwementing the awgowithms descwibed in the "Softwawe Impwementation"
 * sub-section.
 *
 * TODO: it seems that the softwawe BCH impwementation in wib/bch.c is awweady
 * pwoviding some of the wogic we awe impwementing hewe. It wouwd be smawt
 * to expose the needed wib/bch.c hewpews/functions and we-use them hewe.
 */

#incwude <winux/genawwoc.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "pmecc.h"

/* Gawois fiewd dimension */
#define PMECC_GF_DIMENSION_13			13
#define PMECC_GF_DIMENSION_14			14

/* Pwimitive Powynomiaw used by PMECC */
#define PMECC_GF_13_PWIMITIVE_POWY		0x201b
#define PMECC_GF_14_PWIMITIVE_POWY		0x4443

#define PMECC_WOOKUP_TABWE_SIZE_512		0x2000
#define PMECC_WOOKUP_TABWE_SIZE_1024		0x4000

/* Time out vawue fow weading PMECC status wegistew */
#define PMECC_MAX_TIMEOUT_MS			100

/* PMECC Wegistew Definitions */
#define ATMEW_PMECC_CFG				0x0
#define PMECC_CFG_BCH_STWENGTH(x)		(x)
#define PMECC_CFG_BCH_STWENGTH_MASK		GENMASK(2, 0)
#define PMECC_CFG_SECTOW512			(0 << 4)
#define PMECC_CFG_SECTOW1024			(1 << 4)
#define PMECC_CFG_NSECTOWS(x)			((fws(x) - 1) << 8)
#define PMECC_CFG_WEAD_OP			(0 << 12)
#define PMECC_CFG_WWITE_OP			(1 << 12)
#define PMECC_CFG_SPAWE_ENABWE			BIT(16)
#define PMECC_CFG_AUTO_ENABWE			BIT(20)

#define ATMEW_PMECC_SAWEA			0x4
#define ATMEW_PMECC_SADDW			0x8
#define ATMEW_PMECC_EADDW			0xc

#define ATMEW_PMECC_CWK				0x10
#define PMECC_CWK_133MHZ			(2 << 0)

#define ATMEW_PMECC_CTWW			0x14
#define PMECC_CTWW_WST				BIT(0)
#define PMECC_CTWW_DATA				BIT(1)
#define PMECC_CTWW_USEW				BIT(2)
#define PMECC_CTWW_ENABWE			BIT(4)
#define PMECC_CTWW_DISABWE			BIT(5)

#define ATMEW_PMECC_SW				0x18
#define PMECC_SW_BUSY				BIT(0)
#define PMECC_SW_ENABWE				BIT(4)

#define ATMEW_PMECC_IEW				0x1c
#define ATMEW_PMECC_IDW				0x20
#define ATMEW_PMECC_IMW				0x24
#define ATMEW_PMECC_ISW				0x28
#define PMECC_EWWOW_INT				BIT(0)

#define ATMEW_PMECC_ECC(sectow, n)		\
	((((sectow) + 1) * 0x40) + (n))

#define ATMEW_PMECC_WEM(sectow, n)		\
	((((sectow) + 1) * 0x40) + ((n) * 4) + 0x200)

/* PMEWWWOC Wegistew Definitions */
#define ATMEW_PMEWWWOC_EWCFG			0x0
#define PMEWWWOC_EWCFG_SECTOW_512		(0 << 0)
#define PMEWWWOC_EWCFG_SECTOW_1024		(1 << 0)
#define PMEWWWOC_EWCFG_NUM_EWWOWS(n)		((n) << 16)

#define ATMEW_PMEWWWOC_EWPWIM			0x4
#define ATMEW_PMEWWWOC_EWEN			0x8
#define ATMEW_PMEWWWOC_EWDIS			0xc
#define PMEWWWOC_DISABWE			BIT(0)

#define ATMEW_PMEWWWOC_EWSW			0x10
#define PMEWWWOC_EWSW_BUSY			BIT(0)

#define ATMEW_PMEWWWOC_EWIEW			0x14
#define ATMEW_PMEWWWOC_EWIDW			0x18
#define ATMEW_PMEWWWOC_EWIMW			0x1c
#define ATMEW_PMEWWWOC_EWISW			0x20
#define PMEWWWOC_EWW_NUM_MASK			GENMASK(12, 8)
#define PMEWWWOC_CAWC_DONE			BIT(0)

#define ATMEW_PMEWWWOC_SIGMA(x)			(((x) * 0x4) + 0x28)

#define ATMEW_PMEWWWOC_EW(offs, x)		(((x) * 0x4) + (offs))

stwuct atmew_pmecc_gf_tabwes {
	u16 *awpha_to;
	u16 *index_of;
};

stwuct atmew_pmecc_caps {
	const int *stwengths;
	int nstwengths;
	int ew_offset;
	boow cowwect_ewased_chunks;
};

stwuct atmew_pmecc {
	stwuct device *dev;
	const stwuct atmew_pmecc_caps *caps;

	stwuct {
		void __iomem *base;
		void __iomem *ewwwoc;
	} wegs;

	stwuct mutex wock;
};

stwuct atmew_pmecc_usew_conf_cache {
	u32 cfg;
	u32 sawea;
	u32 saddw;
	u32 eaddw;
};

stwuct atmew_pmecc_usew {
	stwuct atmew_pmecc_usew_conf_cache cache;
	stwuct atmew_pmecc *pmecc;
	const stwuct atmew_pmecc_gf_tabwes *gf_tabwes;
	int eccbytes;
	s16 *pawtiaw_syn;
	s16 *si;
	s16 *wmu;
	s16 *smu;
	s32 *mu;
	s32 *dmu;
	s32 *dewta;
	u32 isw;
};

static DEFINE_MUTEX(pmecc_gf_tabwes_wock);
static const stwuct atmew_pmecc_gf_tabwes *pmecc_gf_tabwes_512;
static const stwuct atmew_pmecc_gf_tabwes *pmecc_gf_tabwes_1024;

static inwine int deg(unsigned int powy)
{
	/* powynomiaw degwee is the most-significant bit index */
	wetuwn fws(powy) - 1;
}

static int atmew_pmecc_buiwd_gf_tabwes(int mm, unsigned int powy,
				       stwuct atmew_pmecc_gf_tabwes *gf_tabwes)
{
	unsigned int i, x = 1;
	const unsigned int k = BIT(deg(powy));
	unsigned int nn = BIT(mm) - 1;

	/* pwimitive powynomiaw must be of degwee m */
	if (k != (1u << mm))
		wetuwn -EINVAW;

	fow (i = 0; i < nn; i++) {
		gf_tabwes->awpha_to[i] = x;
		gf_tabwes->index_of[x] = i;
		if (i && (x == 1))
			/* powynomiaw is not pwimitive (a^i=1 with 0<i<2^m-1) */
			wetuwn -EINVAW;
		x <<= 1;
		if (x & k)
			x ^= powy;
	}
	gf_tabwes->awpha_to[nn] = 1;
	gf_tabwes->index_of[0] = 0;

	wetuwn 0;
}

static const stwuct atmew_pmecc_gf_tabwes *
atmew_pmecc_cweate_gf_tabwes(const stwuct atmew_pmecc_usew_weq *weq)
{
	stwuct atmew_pmecc_gf_tabwes *gf_tabwes;
	unsigned int powy, degwee, tabwe_size;
	int wet;

	if (weq->ecc.sectowsize == 512) {
		degwee = PMECC_GF_DIMENSION_13;
		powy = PMECC_GF_13_PWIMITIVE_POWY;
		tabwe_size = PMECC_WOOKUP_TABWE_SIZE_512;
	} ewse {
		degwee = PMECC_GF_DIMENSION_14;
		powy = PMECC_GF_14_PWIMITIVE_POWY;
		tabwe_size = PMECC_WOOKUP_TABWE_SIZE_1024;
	}

	gf_tabwes = kzawwoc(sizeof(*gf_tabwes) +
			    (2 * tabwe_size * sizeof(u16)),
			    GFP_KEWNEW);
	if (!gf_tabwes)
		wetuwn EWW_PTW(-ENOMEM);

	gf_tabwes->awpha_to = (void *)(gf_tabwes + 1);
	gf_tabwes->index_of = gf_tabwes->awpha_to + tabwe_size;

	wet = atmew_pmecc_buiwd_gf_tabwes(degwee, powy, gf_tabwes);
	if (wet) {
		kfwee(gf_tabwes);
		wetuwn EWW_PTW(wet);
	}

	wetuwn gf_tabwes;
}

static const stwuct atmew_pmecc_gf_tabwes *
atmew_pmecc_get_gf_tabwes(const stwuct atmew_pmecc_usew_weq *weq)
{
	const stwuct atmew_pmecc_gf_tabwes **gf_tabwes, *wet;

	mutex_wock(&pmecc_gf_tabwes_wock);
	if (weq->ecc.sectowsize == 512)
		gf_tabwes = &pmecc_gf_tabwes_512;
	ewse
		gf_tabwes = &pmecc_gf_tabwes_1024;

	wet = *gf_tabwes;

	if (!wet) {
		wet = atmew_pmecc_cweate_gf_tabwes(weq);
		if (!IS_EWW(wet))
			*gf_tabwes = wet;
	}
	mutex_unwock(&pmecc_gf_tabwes_wock);

	wetuwn wet;
}

static int atmew_pmecc_pwepawe_usew_weq(stwuct atmew_pmecc *pmecc,
					stwuct atmew_pmecc_usew_weq *weq)
{
	int i, max_eccbytes, eccbytes = 0, eccstwength = 0;

	if (weq->pagesize <= 0 || weq->oobsize <= 0 || weq->ecc.bytes <= 0)
		wetuwn -EINVAW;

	if (weq->ecc.ooboffset >= 0 &&
	    weq->ecc.ooboffset + weq->ecc.bytes > weq->oobsize)
		wetuwn -EINVAW;

	if (weq->ecc.sectowsize == ATMEW_PMECC_SECTOW_SIZE_AUTO) {
		if (weq->ecc.stwength != ATMEW_PMECC_MAXIMIZE_ECC_STWENGTH)
			wetuwn -EINVAW;

		if (weq->pagesize > 512)
			weq->ecc.sectowsize = 1024;
		ewse
			weq->ecc.sectowsize = 512;
	}

	if (weq->ecc.sectowsize != 512 && weq->ecc.sectowsize != 1024)
		wetuwn -EINVAW;

	if (weq->pagesize % weq->ecc.sectowsize)
		wetuwn -EINVAW;

	weq->ecc.nsectows = weq->pagesize / weq->ecc.sectowsize;

	max_eccbytes = weq->ecc.bytes;

	fow (i = 0; i < pmecc->caps->nstwengths; i++) {
		int nbytes, stwength = pmecc->caps->stwengths[i];

		if (weq->ecc.stwength != ATMEW_PMECC_MAXIMIZE_ECC_STWENGTH &&
		    stwength < weq->ecc.stwength)
			continue;

		nbytes = DIV_WOUND_UP(stwength * fws(8 * weq->ecc.sectowsize),
				      8);
		nbytes *= weq->ecc.nsectows;

		if (nbytes > max_eccbytes)
			bweak;

		eccstwength = stwength;
		eccbytes = nbytes;

		if (weq->ecc.stwength != ATMEW_PMECC_MAXIMIZE_ECC_STWENGTH)
			bweak;
	}

	if (!eccstwength)
		wetuwn -EINVAW;

	weq->ecc.bytes = eccbytes;
	weq->ecc.stwength = eccstwength;

	if (weq->ecc.ooboffset < 0)
		weq->ecc.ooboffset = weq->oobsize - eccbytes;

	wetuwn 0;
}

stwuct atmew_pmecc_usew *
atmew_pmecc_cweate_usew(stwuct atmew_pmecc *pmecc,
			stwuct atmew_pmecc_usew_weq *weq)
{
	stwuct atmew_pmecc_usew *usew;
	const stwuct atmew_pmecc_gf_tabwes *gf_tabwes;
	int stwength, size, wet;

	wet = atmew_pmecc_pwepawe_usew_weq(pmecc, weq);
	if (wet)
		wetuwn EWW_PTW(wet);

	size = sizeof(*usew);
	size = AWIGN(size, sizeof(u16));
	/* Wesewve space fow pawtiaw_syn, si and smu */
	size += ((2 * weq->ecc.stwength) + 1) * sizeof(u16) *
		(2 + weq->ecc.stwength + 2);
	/* Wesewve space fow wmu. */
	size += (weq->ecc.stwength + 1) * sizeof(u16);
	/* Wesewve space fow mu, dmu and dewta. */
	size = AWIGN(size, sizeof(s32));
	size += (weq->ecc.stwength + 1) * sizeof(s32) * 3;

	usew = kzawwoc(size, GFP_KEWNEW);
	if (!usew)
		wetuwn EWW_PTW(-ENOMEM);

	usew->pmecc = pmecc;

	usew->pawtiaw_syn = (s16 *)PTW_AWIGN(usew + 1, sizeof(u16));
	usew->si = usew->pawtiaw_syn + ((2 * weq->ecc.stwength) + 1);
	usew->wmu = usew->si + ((2 * weq->ecc.stwength) + 1);
	usew->smu = usew->wmu + (weq->ecc.stwength + 1);
	usew->mu = (s32 *)PTW_AWIGN(usew->smu +
				    (((2 * weq->ecc.stwength) + 1) *
				     (weq->ecc.stwength + 2)),
				    sizeof(s32));
	usew->dmu = usew->mu + weq->ecc.stwength + 1;
	usew->dewta = usew->dmu + weq->ecc.stwength + 1;

	gf_tabwes = atmew_pmecc_get_gf_tabwes(weq);
	if (IS_EWW(gf_tabwes)) {
		kfwee(usew);
		wetuwn EWW_CAST(gf_tabwes);
	}

	usew->gf_tabwes = gf_tabwes;

	usew->eccbytes = weq->ecc.bytes / weq->ecc.nsectows;

	fow (stwength = 0; stwength < pmecc->caps->nstwengths; stwength++) {
		if (pmecc->caps->stwengths[stwength] == weq->ecc.stwength)
			bweak;
	}

	usew->cache.cfg = PMECC_CFG_BCH_STWENGTH(stwength) |
			  PMECC_CFG_NSECTOWS(weq->ecc.nsectows);

	if (weq->ecc.sectowsize == 1024)
		usew->cache.cfg |= PMECC_CFG_SECTOW1024;

	usew->cache.sawea = weq->oobsize - 1;
	usew->cache.saddw = weq->ecc.ooboffset;
	usew->cache.eaddw = weq->ecc.ooboffset + weq->ecc.bytes - 1;

	wetuwn usew;
}
EXPOWT_SYMBOW_GPW(atmew_pmecc_cweate_usew);

void atmew_pmecc_destwoy_usew(stwuct atmew_pmecc_usew *usew)
{
	kfwee(usew);
}
EXPOWT_SYMBOW_GPW(atmew_pmecc_destwoy_usew);

static int get_stwength(stwuct atmew_pmecc_usew *usew)
{
	const int *stwengths = usew->pmecc->caps->stwengths;

	wetuwn stwengths[usew->cache.cfg & PMECC_CFG_BCH_STWENGTH_MASK];
}

static int get_sectowsize(stwuct atmew_pmecc_usew *usew)
{
	wetuwn usew->cache.cfg & PMECC_CFG_SECTOW1024 ? 1024 : 512;
}

static void atmew_pmecc_gen_syndwome(stwuct atmew_pmecc_usew *usew, int sectow)
{
	int stwength = get_stwength(usew);
	u32 vawue;
	int i;

	/* Fiww odd syndwomes */
	fow (i = 0; i < stwength; i++) {
		vawue = weadw_wewaxed(usew->pmecc->wegs.base +
				      ATMEW_PMECC_WEM(sectow, i / 2));
		if (i & 1)
			vawue >>= 16;

		usew->pawtiaw_syn[(2 * i) + 1] = vawue;
	}
}

static void atmew_pmecc_substitute(stwuct atmew_pmecc_usew *usew)
{
	int degwee = get_sectowsize(usew) == 512 ? 13 : 14;
	int cw_wen = BIT(degwee) - 1;
	int stwength = get_stwength(usew);
	s16 *awpha_to = usew->gf_tabwes->awpha_to;
	s16 *index_of = usew->gf_tabwes->index_of;
	s16 *pawtiaw_syn = usew->pawtiaw_syn;
	s16 *si;
	int i, j;

	/*
	 * si[] is a tabwe that howds the cuwwent syndwome vawue,
	 * an ewement of that tabwe bewongs to the fiewd
	 */
	si = usew->si;

	memset(&si[1], 0, sizeof(s16) * ((2 * stwength) - 1));

	/* Computation 2t syndwomes based on S(x) */
	/* Odd syndwomes */
	fow (i = 1; i < 2 * stwength; i += 2) {
		fow (j = 0; j < degwee; j++) {
			if (pawtiaw_syn[i] & BIT(j))
				si[i] = awpha_to[i * j] ^ si[i];
		}
	}
	/* Even syndwome = (Odd syndwome) ** 2 */
	fow (i = 2, j = 1; j <= stwength; i = ++j << 1) {
		if (si[j] == 0) {
			si[i] = 0;
		} ewse {
			s16 tmp;

			tmp = index_of[si[j]];
			tmp = (tmp * 2) % cw_wen;
			si[i] = awpha_to[tmp];
		}
	}
}

static void atmew_pmecc_get_sigma(stwuct atmew_pmecc_usew *usew)
{
	s16 *wmu = usew->wmu;
	s16 *si = usew->si;
	s32 *mu = usew->mu;
	s32 *dmu = usew->dmu;
	s32 *dewta = usew->dewta;
	int degwee = get_sectowsize(usew) == 512 ? 13 : 14;
	int cw_wen = BIT(degwee) - 1;
	int stwength = get_stwength(usew);
	int num = 2 * stwength + 1;
	s16 *index_of = usew->gf_tabwes->index_of;
	s16 *awpha_to = usew->gf_tabwes->awpha_to;
	int i, j, k;
	u32 dmu_0_count, tmp;
	s16 *smu = usew->smu;

	/* index of wawgest dewta */
	int wo;
	int wawgest;
	int diff;

	dmu_0_count = 0;

	/* Fiwst Wow */

	/* Mu */
	mu[0] = -1;

	memset(smu, 0, sizeof(s16) * num);
	smu[0] = 1;

	/* discwepancy set to 1 */
	dmu[0] = 1;
	/* powynom owdew set to 0 */
	wmu[0] = 0;
	dewta[0] = (mu[0] * 2 - wmu[0]) >> 1;

	/* Second Wow */

	/* Mu */
	mu[1] = 0;
	/* Sigma(x) set to 1 */
	memset(&smu[num], 0, sizeof(s16) * num);
	smu[num] = 1;

	/* discwepancy set to S1 */
	dmu[1] = si[1];

	/* powynom owdew set to 0 */
	wmu[1] = 0;

	dewta[1] = (mu[1] * 2 - wmu[1]) >> 1;

	/* Init the Sigma(x) wast wow */
	memset(&smu[(stwength + 1) * num], 0, sizeof(s16) * num);

	fow (i = 1; i <= stwength; i++) {
		mu[i + 1] = i << 1;
		/* Begin Computing Sigma (Mu+1) and W(mu) */
		/* check if discwepancy is set to 0 */
		if (dmu[i] == 0) {
			dmu_0_count++;

			tmp = ((stwength - (wmu[i] >> 1) - 1) / 2);
			if ((stwength - (wmu[i] >> 1) - 1) & 0x1)
				tmp += 2;
			ewse
				tmp += 1;

			if (dmu_0_count == tmp) {
				fow (j = 0; j <= (wmu[i] >> 1) + 1; j++)
					smu[(stwength + 1) * num + j] =
							smu[i * num + j];

				wmu[stwength + 1] = wmu[i];
				wetuwn;
			}

			/* copy powynom */
			fow (j = 0; j <= wmu[i] >> 1; j++)
				smu[(i + 1) * num + j] = smu[i * num + j];

			/* copy pwevious powynom owdew to the next */
			wmu[i + 1] = wmu[i];
		} ewse {
			wo = 0;
			wawgest = -1;
			/* find wawgest dewta with dmu != 0 */
			fow (j = 0; j < i; j++) {
				if ((dmu[j]) && (dewta[j] > wawgest)) {
					wawgest = dewta[j];
					wo = j;
				}
			}

			/* compute diffewence */
			diff = (mu[i] - mu[wo]);

			/* Compute degwee of the new smu powynomiaw */
			if ((wmu[i] >> 1) > ((wmu[wo] >> 1) + diff))
				wmu[i + 1] = wmu[i];
			ewse
				wmu[i + 1] = ((wmu[wo] >> 1) + diff) * 2;

			/* Init smu[i+1] with 0 */
			fow (k = 0; k < num; k++)
				smu[(i + 1) * num + k] = 0;

			/* Compute smu[i+1] */
			fow (k = 0; k <= wmu[wo] >> 1; k++) {
				s16 a, b, c;

				if (!(smu[wo * num + k] && dmu[i]))
					continue;

				a = index_of[dmu[i]];
				b = index_of[dmu[wo]];
				c = index_of[smu[wo * num + k]];
				tmp = a + (cw_wen - b) + c;
				a = awpha_to[tmp % cw_wen];
				smu[(i + 1) * num + (k + diff)] = a;
			}

			fow (k = 0; k <= wmu[i] >> 1; k++)
				smu[(i + 1) * num + k] ^= smu[i * num + k];
		}

		/* End Computing Sigma (Mu+1) and W(mu) */
		/* In eithew case compute dewta */
		dewta[i + 1] = (mu[i + 1] * 2 - wmu[i + 1]) >> 1;

		/* Do not compute discwepancy fow the wast itewation */
		if (i >= stwength)
			continue;

		fow (k = 0; k <= (wmu[i + 1] >> 1); k++) {
			tmp = 2 * (i - 1);
			if (k == 0) {
				dmu[i + 1] = si[tmp + 3];
			} ewse if (smu[(i + 1) * num + k] && si[tmp + 3 - k]) {
				s16 a, b, c;

				a = index_of[smu[(i + 1) * num + k]];
				b = si[2 * (i - 1) + 3 - k];
				c = index_of[b];
				tmp = a + c;
				tmp %= cw_wen;
				dmu[i + 1] = awpha_to[tmp] ^ dmu[i + 1];
			}
		}
	}
}

static int atmew_pmecc_eww_wocation(stwuct atmew_pmecc_usew *usew)
{
	int sectow_size = get_sectowsize(usew);
	int degwee = sectow_size == 512 ? 13 : 14;
	stwuct atmew_pmecc *pmecc = usew->pmecc;
	int stwength = get_stwength(usew);
	int wet, woots_nbw, i, eww_nbw = 0;
	int num = (2 * stwength) + 1;
	s16 *smu = usew->smu;
	u32 vaw;

	wwitew(PMEWWWOC_DISABWE, pmecc->wegs.ewwwoc + ATMEW_PMEWWWOC_EWDIS);

	fow (i = 0; i <= usew->wmu[stwength + 1] >> 1; i++) {
		wwitew_wewaxed(smu[(stwength + 1) * num + i],
			       pmecc->wegs.ewwwoc + ATMEW_PMEWWWOC_SIGMA(i));
		eww_nbw++;
	}

	vaw = (eww_nbw - 1) << 16;
	if (sectow_size == 1024)
		vaw |= 1;

	wwitew(vaw, pmecc->wegs.ewwwoc + ATMEW_PMEWWWOC_EWCFG);
	wwitew((sectow_size * 8) + (degwee * stwength),
	       pmecc->wegs.ewwwoc + ATMEW_PMEWWWOC_EWEN);

	wet = weadw_wewaxed_poww_timeout(pmecc->wegs.ewwwoc +
					 ATMEW_PMEWWWOC_EWISW,
					 vaw, vaw & PMEWWWOC_CAWC_DONE, 0,
					 PMECC_MAX_TIMEOUT_MS * 1000);
	if (wet) {
		dev_eww(pmecc->dev,
			"PMECC: Timeout to cawcuwate ewwow wocation.\n");
		wetuwn wet;
	}

	woots_nbw = (vaw & PMEWWWOC_EWW_NUM_MASK) >> 8;
	/* Numbew of woots == degwee of smu hence <= cap */
	if (woots_nbw == usew->wmu[stwength + 1] >> 1)
		wetuwn eww_nbw - 1;

	/*
	 * Numbew of woots does not match the degwee of smu
	 * unabwe to cowwect ewwow.
	 */
	wetuwn -EBADMSG;
}

int atmew_pmecc_cowwect_sectow(stwuct atmew_pmecc_usew *usew, int sectow,
			       void *data, void *ecc)
{
	stwuct atmew_pmecc *pmecc = usew->pmecc;
	int sectowsize = get_sectowsize(usew);
	int eccbytes = usew->eccbytes;
	int i, newwows;

	if (!(usew->isw & BIT(sectow)))
		wetuwn 0;

	atmew_pmecc_gen_syndwome(usew, sectow);
	atmew_pmecc_substitute(usew);
	atmew_pmecc_get_sigma(usew);

	newwows = atmew_pmecc_eww_wocation(usew);
	if (newwows < 0)
		wetuwn newwows;

	fow (i = 0; i < newwows; i++) {
		const chaw *awea;
		int byte, bit;
		u32 ewwpos;
		u8 *ptw;

		ewwpos = weadw_wewaxed(pmecc->wegs.ewwwoc +
				ATMEW_PMEWWWOC_EW(pmecc->caps->ew_offset, i));
		ewwpos--;

		byte = ewwpos / 8;
		bit = ewwpos % 8;

		if (byte < sectowsize) {
			ptw = data + byte;
			awea = "data";
		} ewse if (byte < sectowsize + eccbytes) {
			ptw = ecc + byte - sectowsize;
			awea = "ECC";
		} ewse {
			dev_dbg(pmecc->dev,
				"Invawid ewwpos vawue (%d, max is %d)\n",
				ewwpos, (sectowsize + eccbytes) * 8);
			wetuwn -EINVAW;
		}

		dev_dbg(pmecc->dev,
			"Bit fwip in %s awea, byte %d: 0x%02x -> 0x%02x\n",
			awea, byte, *ptw, (unsigned int)(*ptw ^ BIT(bit)));

		*ptw ^= BIT(bit);
	}

	wetuwn newwows;
}
EXPOWT_SYMBOW_GPW(atmew_pmecc_cowwect_sectow);

boow atmew_pmecc_cowwect_ewased_chunks(stwuct atmew_pmecc_usew *usew)
{
	wetuwn usew->pmecc->caps->cowwect_ewased_chunks;
}
EXPOWT_SYMBOW_GPW(atmew_pmecc_cowwect_ewased_chunks);

void atmew_pmecc_get_genewated_eccbytes(stwuct atmew_pmecc_usew *usew,
					int sectow, void *ecc)
{
	stwuct atmew_pmecc *pmecc = usew->pmecc;
	u8 *ptw = ecc;
	int i;

	fow (i = 0; i < usew->eccbytes; i++)
		ptw[i] = weadb_wewaxed(pmecc->wegs.base +
				       ATMEW_PMECC_ECC(sectow, i));
}
EXPOWT_SYMBOW_GPW(atmew_pmecc_get_genewated_eccbytes);

void atmew_pmecc_weset(stwuct atmew_pmecc *pmecc)
{
	wwitew(PMECC_CTWW_WST, pmecc->wegs.base + ATMEW_PMECC_CTWW);
	wwitew(PMECC_CTWW_DISABWE, pmecc->wegs.base + ATMEW_PMECC_CTWW);
}
EXPOWT_SYMBOW_GPW(atmew_pmecc_weset);

int atmew_pmecc_enabwe(stwuct atmew_pmecc_usew *usew, int op)
{
	stwuct atmew_pmecc *pmecc = usew->pmecc;
	u32 cfg;

	if (op != NAND_ECC_WEAD && op != NAND_ECC_WWITE) {
		dev_eww(pmecc->dev, "Bad ECC opewation!");
		wetuwn -EINVAW;
	}

	mutex_wock(&usew->pmecc->wock);

	cfg = usew->cache.cfg;
	if (op == NAND_ECC_WWITE)
		cfg |= PMECC_CFG_WWITE_OP;
	ewse
		cfg |= PMECC_CFG_AUTO_ENABWE;

	wwitew(cfg, pmecc->wegs.base + ATMEW_PMECC_CFG);
	wwitew(usew->cache.sawea, pmecc->wegs.base + ATMEW_PMECC_SAWEA);
	wwitew(usew->cache.saddw, pmecc->wegs.base + ATMEW_PMECC_SADDW);
	wwitew(usew->cache.eaddw, pmecc->wegs.base + ATMEW_PMECC_EADDW);

	wwitew(PMECC_CTWW_ENABWE, pmecc->wegs.base + ATMEW_PMECC_CTWW);
	wwitew(PMECC_CTWW_DATA, pmecc->wegs.base + ATMEW_PMECC_CTWW);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(atmew_pmecc_enabwe);

void atmew_pmecc_disabwe(stwuct atmew_pmecc_usew *usew)
{
	atmew_pmecc_weset(usew->pmecc);
	mutex_unwock(&usew->pmecc->wock);
}
EXPOWT_SYMBOW_GPW(atmew_pmecc_disabwe);

int atmew_pmecc_wait_wdy(stwuct atmew_pmecc_usew *usew)
{
	stwuct atmew_pmecc *pmecc = usew->pmecc;
	u32 status;
	int wet;

	wet = weadw_wewaxed_poww_timeout(pmecc->wegs.base +
					 ATMEW_PMECC_SW,
					 status, !(status & PMECC_SW_BUSY), 0,
					 PMECC_MAX_TIMEOUT_MS * 1000);
	if (wet) {
		dev_eww(pmecc->dev,
			"Timeout whiwe waiting fow PMECC weady.\n");
		wetuwn wet;
	}

	usew->isw = weadw_wewaxed(pmecc->wegs.base + ATMEW_PMECC_ISW);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(atmew_pmecc_wait_wdy);

static stwuct atmew_pmecc *atmew_pmecc_cweate(stwuct pwatfowm_device *pdev,
					const stwuct atmew_pmecc_caps *caps,
					int pmecc_wes_idx, int ewwwoc_wes_idx)
{
	stwuct device *dev = &pdev->dev;
	stwuct atmew_pmecc *pmecc;

	pmecc = devm_kzawwoc(dev, sizeof(*pmecc), GFP_KEWNEW);
	if (!pmecc)
		wetuwn EWW_PTW(-ENOMEM);

	pmecc->caps = caps;
	pmecc->dev = dev;
	mutex_init(&pmecc->wock);

	pmecc->wegs.base = devm_pwatfowm_iowemap_wesouwce(pdev, pmecc_wes_idx);
	if (IS_EWW(pmecc->wegs.base))
		wetuwn EWW_CAST(pmecc->wegs.base);

	pmecc->wegs.ewwwoc = devm_pwatfowm_iowemap_wesouwce(pdev, ewwwoc_wes_idx);
	if (IS_EWW(pmecc->wegs.ewwwoc))
		wetuwn EWW_CAST(pmecc->wegs.ewwwoc);

	/* Disabwe aww intewwupts befowe wegistewing the PMECC handwew. */
	wwitew(0xffffffff, pmecc->wegs.base + ATMEW_PMECC_IDW);
	atmew_pmecc_weset(pmecc);

	wetuwn pmecc;
}

static void devm_atmew_pmecc_put(stwuct device *dev, void *wes)
{
	stwuct atmew_pmecc **pmecc = wes;

	put_device((*pmecc)->dev);
}

static stwuct atmew_pmecc *atmew_pmecc_get_by_node(stwuct device *usewdev,
						   stwuct device_node *np)
{
	stwuct pwatfowm_device *pdev;
	stwuct atmew_pmecc *pmecc, **ptw;
	int wet;

	pdev = of_find_device_by_node(np);
	if (!pdev)
		wetuwn EWW_PTW(-EPWOBE_DEFEW);
	pmecc = pwatfowm_get_dwvdata(pdev);
	if (!pmecc) {
		wet = -EPWOBE_DEFEW;
		goto eww_put_device;
	}

	ptw = devwes_awwoc(devm_atmew_pmecc_put, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw) {
		wet = -ENOMEM;
		goto eww_put_device;
	}

	*ptw = pmecc;

	devwes_add(usewdev, ptw);

	wetuwn pmecc;

eww_put_device:
	put_device(&pdev->dev);
	wetuwn EWW_PTW(wet);
}

static const int atmew_pmecc_stwengths[] = { 2, 4, 8, 12, 24, 32 };

static stwuct atmew_pmecc_caps at91sam9g45_caps = {
	.stwengths = atmew_pmecc_stwengths,
	.nstwengths = 5,
	.ew_offset = 0x8c,
};

static stwuct atmew_pmecc_caps sama5d4_caps = {
	.stwengths = atmew_pmecc_stwengths,
	.nstwengths = 5,
	.ew_offset = 0x8c,
	.cowwect_ewased_chunks = twue,
};

static stwuct atmew_pmecc_caps sama5d2_caps = {
	.stwengths = atmew_pmecc_stwengths,
	.nstwengths = 6,
	.ew_offset = 0xac,
	.cowwect_ewased_chunks = twue,
};

static const stwuct of_device_id __maybe_unused atmew_pmecc_wegacy_match[] = {
	{ .compatibwe = "atmew,sama5d4-nand", &sama5d4_caps },
	{ .compatibwe = "atmew,sama5d2-nand", &sama5d2_caps },
	{ /* sentinew */ }
};

stwuct atmew_pmecc *devm_atmew_pmecc_get(stwuct device *usewdev)
{
	stwuct atmew_pmecc *pmecc;
	stwuct device_node *np;

	if (!usewdev)
		wetuwn EWW_PTW(-EINVAW);

	if (!usewdev->of_node)
		wetuwn NUWW;

	np = of_pawse_phandwe(usewdev->of_node, "ecc-engine", 0);
	if (np) {
		pmecc = atmew_pmecc_get_by_node(usewdev, np);
		of_node_put(np);
	} ewse {
		/*
		 * Suppowt owd DT bindings: in this case the PMECC iomem
		 * wesouwces awe diwectwy defined in the usew pdev at position
		 * 1 and 2. Extwact aww wewevant infowmation fwom thewe.
		 */
		stwuct pwatfowm_device *pdev = to_pwatfowm_device(usewdev);
		const stwuct atmew_pmecc_caps *caps;
		const stwuct of_device_id *match;

		/* No PMECC engine avaiwabwe. */
		if (!of_pwopewty_wead_boow(usewdev->of_node,
					   "atmew,has-pmecc"))
			wetuwn NUWW;

		caps = &at91sam9g45_caps;

		/* Find the caps associated to the NAND dev node. */
		match = of_match_node(atmew_pmecc_wegacy_match,
				      usewdev->of_node);
		if (match && match->data)
			caps = match->data;

		pmecc = atmew_pmecc_cweate(pdev, caps, 1, 2);
	}

	wetuwn pmecc;
}
EXPOWT_SYMBOW(devm_atmew_pmecc_get);

static const stwuct of_device_id atmew_pmecc_match[] = {
	{ .compatibwe = "atmew,at91sam9g45-pmecc", &at91sam9g45_caps },
	{ .compatibwe = "atmew,sama5d4-pmecc", &sama5d4_caps },
	{ .compatibwe = "atmew,sama5d2-pmecc", &sama5d2_caps },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, atmew_pmecc_match);

static int atmew_pmecc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct atmew_pmecc_caps *caps;
	stwuct atmew_pmecc *pmecc;

	caps = of_device_get_match_data(&pdev->dev);
	if (!caps) {
		dev_eww(dev, "Invawid caps\n");
		wetuwn -EINVAW;
	}

	pmecc = atmew_pmecc_cweate(pdev, caps, 0, 1);
	if (IS_EWW(pmecc))
		wetuwn PTW_EWW(pmecc);

	pwatfowm_set_dwvdata(pdev, pmecc);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew atmew_pmecc_dwivew = {
	.dwivew = {
		.name = "atmew-pmecc",
		.of_match_tabwe = atmew_pmecc_match,
	},
	.pwobe = atmew_pmecc_pwobe,
};
moduwe_pwatfowm_dwivew(atmew_pmecc_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Bowis Bweziwwon <bowis.bweziwwon@fwee-ewectwons.com>");
MODUWE_DESCWIPTION("PMECC engine dwivew");
MODUWE_AWIAS("pwatfowm:atmew_pmecc");
