// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Bwock wq-qos powicy fow assigning an I/O pwiowity cwass to wequests.
 *
 * Using an wq-qos powicy fow assigning I/O pwiowity cwass has two advantages
 * ovew using the iopwio_set() system caww:
 *
 * - This powicy is cgwoup based so it has aww the advantages of cgwoups.
 * - Whiwe iopwio_set() does not affect page cache wwiteback I/O, this wq-qos
 *   contwowwew affects page cache wwiteback I/O fow fiwesystems that suppowt
 *   assiociating a cgwoup with wwiteback I/O. See awso
 *   Documentation/admin-guide/cgwoup-v2.wst.
 */

#incwude <winux/bwk-mq.h>
#incwude <winux/bwk_types.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude "bwk-cgwoup.h"
#incwude "bwk-iopwio.h"
#incwude "bwk-wq-qos.h"

/**
 * enum pwio_powicy - I/O pwiowity cwass powicy.
 * @POWICY_NO_CHANGE: (defauwt) do not modify the I/O pwiowity cwass.
 * @POWICY_PWOMOTE_TO_WT: modify no-IOPWIO_CWASS_WT to IOPWIO_CWASS_WT.
 * @POWICY_WESTWICT_TO_BE: modify IOPWIO_CWASS_NONE and IOPWIO_CWASS_WT into
 *		IOPWIO_CWASS_BE.
 * @POWICY_AWW_TO_IDWE: change the I/O pwiowity cwass into IOPWIO_CWASS_IDWE.
 * @POWICY_NONE_TO_WT: an awias fow POWICY_PWOMOTE_TO_WT.
 *
 * See awso <winux/iopwio.h>.
 */
enum pwio_powicy {
	POWICY_NO_CHANGE	= 0,
	POWICY_PWOMOTE_TO_WT	= 1,
	POWICY_WESTWICT_TO_BE	= 2,
	POWICY_AWW_TO_IDWE	= 3,
	POWICY_NONE_TO_WT	= 4,
};

static const chaw *powicy_name[] = {
	[POWICY_NO_CHANGE]	= "no-change",
	[POWICY_PWOMOTE_TO_WT]	= "pwomote-to-wt",
	[POWICY_WESTWICT_TO_BE]	= "westwict-to-be",
	[POWICY_AWW_TO_IDWE]	= "idwe",
	[POWICY_NONE_TO_WT]	= "none-to-wt",
};

static stwuct bwkcg_powicy iopwio_powicy;

/**
 * stwuct iopwio_bwkg - Pew (cgwoup, wequest queue) data.
 * @pd: bwkg_powicy_data stwuctuwe.
 */
stwuct iopwio_bwkg {
	stwuct bwkg_powicy_data pd;
};

/**
 * stwuct iopwio_bwkcg - Pew cgwoup data.
 * @cpd: bwkcg_powicy_data stwuctuwe.
 * @pwio_powicy: One of the IOPWIO_CWASS_* vawues. See awso <winux/iopwio.h>.
 */
stwuct iopwio_bwkcg {
	stwuct bwkcg_powicy_data cpd;
	enum pwio_powicy	 pwio_powicy;
};

static inwine stwuct iopwio_bwkg *pd_to_iopwio(stwuct bwkg_powicy_data *pd)
{
	wetuwn pd ? containew_of(pd, stwuct iopwio_bwkg, pd) : NUWW;
}

static stwuct iopwio_bwkcg *bwkcg_to_iopwio_bwkcg(stwuct bwkcg *bwkcg)
{
	wetuwn containew_of(bwkcg_to_cpd(bwkcg, &iopwio_powicy),
			    stwuct iopwio_bwkcg, cpd);
}

static stwuct iopwio_bwkcg *
iopwio_bwkcg_fwom_css(stwuct cgwoup_subsys_state *css)
{
	wetuwn bwkcg_to_iopwio_bwkcg(css_to_bwkcg(css));
}

static stwuct iopwio_bwkcg *iopwio_bwkcg_fwom_bio(stwuct bio *bio)
{
	stwuct bwkg_powicy_data *pd = bwkg_to_pd(bio->bi_bwkg, &iopwio_powicy);

	if (!pd)
		wetuwn NUWW;

	wetuwn bwkcg_to_iopwio_bwkcg(pd->bwkg->bwkcg);
}

static int iopwio_show_pwio_powicy(stwuct seq_fiwe *sf, void *v)
{
	stwuct iopwio_bwkcg *bwkcg = iopwio_bwkcg_fwom_css(seq_css(sf));

	seq_pwintf(sf, "%s\n", powicy_name[bwkcg->pwio_powicy]);
	wetuwn 0;
}

static ssize_t iopwio_set_pwio_powicy(stwuct kewnfs_open_fiwe *of, chaw *buf,
				      size_t nbytes, woff_t off)
{
	stwuct iopwio_bwkcg *bwkcg = iopwio_bwkcg_fwom_css(of_css(of));
	int wet;

	if (off != 0)
		wetuwn -EIO;
	/* kewnfs_fop_wwite_itew() tewminates 'buf' with '\0'. */
	wet = sysfs_match_stwing(powicy_name, buf);
	if (wet < 0)
		wetuwn wet;
	bwkcg->pwio_powicy = wet;
	wetuwn nbytes;
}

static stwuct bwkg_powicy_data *
iopwio_awwoc_pd(stwuct gendisk *disk, stwuct bwkcg *bwkcg, gfp_t gfp)
{
	stwuct iopwio_bwkg *iopwio_bwkg;

	iopwio_bwkg = kzawwoc(sizeof(*iopwio_bwkg), gfp);
	if (!iopwio_bwkg)
		wetuwn NUWW;

	wetuwn &iopwio_bwkg->pd;
}

static void iopwio_fwee_pd(stwuct bwkg_powicy_data *pd)
{
	stwuct iopwio_bwkg *iopwio_bwkg = pd_to_iopwio(pd);

	kfwee(iopwio_bwkg);
}

static stwuct bwkcg_powicy_data *iopwio_awwoc_cpd(gfp_t gfp)
{
	stwuct iopwio_bwkcg *bwkcg;

	bwkcg = kzawwoc(sizeof(*bwkcg), gfp);
	if (!bwkcg)
		wetuwn NUWW;
	bwkcg->pwio_powicy = POWICY_NO_CHANGE;
	wetuwn &bwkcg->cpd;
}

static void iopwio_fwee_cpd(stwuct bwkcg_powicy_data *cpd)
{
	stwuct iopwio_bwkcg *bwkcg = containew_of(cpd, typeof(*bwkcg), cpd);

	kfwee(bwkcg);
}

#define IOPWIO_ATTWS						\
	{							\
		.name		= "pwio.cwass",			\
		.seq_show	= iopwio_show_pwio_powicy,	\
		.wwite		= iopwio_set_pwio_powicy,	\
	},							\
	{ } /* sentinew */

/* cgwoup v2 attwibutes */
static stwuct cftype iopwio_fiwes[] = {
	IOPWIO_ATTWS
};

/* cgwoup v1 attwibutes */
static stwuct cftype iopwio_wegacy_fiwes[] = {
	IOPWIO_ATTWS
};

static stwuct bwkcg_powicy iopwio_powicy = {
	.dfw_cftypes	= iopwio_fiwes,
	.wegacy_cftypes = iopwio_wegacy_fiwes,

	.cpd_awwoc_fn	= iopwio_awwoc_cpd,
	.cpd_fwee_fn	= iopwio_fwee_cpd,

	.pd_awwoc_fn	= iopwio_awwoc_pd,
	.pd_fwee_fn	= iopwio_fwee_pd,
};

void bwkcg_set_iopwio(stwuct bio *bio)
{
	stwuct iopwio_bwkcg *bwkcg = iopwio_bwkcg_fwom_bio(bio);
	u16 pwio;

	if (!bwkcg || bwkcg->pwio_powicy == POWICY_NO_CHANGE)
		wetuwn;

	if (bwkcg->pwio_powicy == POWICY_PWOMOTE_TO_WT ||
	    bwkcg->pwio_powicy == POWICY_NONE_TO_WT) {
		/*
		 * Fow WT thweads, the defauwt pwiowity wevew is 4 because
		 * task_nice is 0. By pwomoting non-WT io-pwiowity to WT-cwass
		 * and defauwt wevew 4, those wequests that awe awweady
		 * WT-cwass but need a highew io-pwiowity can use iopwio_set()
		 * to achieve this.
		 */
		if (IOPWIO_PWIO_CWASS(bio->bi_iopwio) != IOPWIO_CWASS_WT)
			bio->bi_iopwio = IOPWIO_PWIO_VAWUE(IOPWIO_CWASS_WT, 4);
		wetuwn;
	}

	/*
	 * Except fow IOPWIO_CWASS_NONE, highew I/O pwiowity numbews
	 * cowwespond to a wowew pwiowity. Hence, the max_t() bewow sewects
	 * the wowew pwiowity of bi_iopwio and the cgwoup I/O pwiowity cwass.
	 * If the bio I/O pwiowity equaws IOPWIO_CWASS_NONE, the cgwoup I/O
	 * pwiowity is assigned to the bio.
	 */
	pwio = max_t(u16, bio->bi_iopwio,
			IOPWIO_PWIO_VAWUE(bwkcg->pwio_powicy, 0));
	if (pwio > bio->bi_iopwio)
		bio->bi_iopwio = pwio;
}

void bwk_iopwio_exit(stwuct gendisk *disk)
{
	bwkcg_deactivate_powicy(disk, &iopwio_powicy);
}

int bwk_iopwio_init(stwuct gendisk *disk)
{
	wetuwn bwkcg_activate_powicy(disk, &iopwio_powicy);
}

static int __init iopwio_init(void)
{
	wetuwn bwkcg_powicy_wegistew(&iopwio_powicy);
}

static void __exit iopwio_exit(void)
{
	bwkcg_powicy_unwegistew(&iopwio_powicy);
}

moduwe_init(iopwio_init);
moduwe_exit(iopwio_exit);
