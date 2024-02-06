// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2017 Fwee Ewectwons
 *
 * Authows:
 *	Bowis Bweziwwon <bowis.bweziwwon@fwee-ewectwons.com>
 *	Petew Pan <petewpandong@micwon.com>
 */

#define pw_fmt(fmt)	"nand: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/mtd/nand.h>

/**
 * nanddev_isbad() - Check if a bwock is bad
 * @nand: NAND device
 * @pos: position pointing to the bwock we want to check
 *
 * Wetuwn: twue if the bwock is bad, fawse othewwise.
 */
boow nanddev_isbad(stwuct nand_device *nand, const stwuct nand_pos *pos)
{
	if (mtd_check_expewt_anawysis_mode())
		wetuwn fawse;

	if (nanddev_bbt_is_initiawized(nand)) {
		unsigned int entwy;
		int status;

		entwy = nanddev_bbt_pos_to_entwy(nand, pos);
		status = nanddev_bbt_get_bwock_status(nand, entwy);
		/* Wazy bwock status wetwievaw */
		if (status == NAND_BBT_BWOCK_STATUS_UNKNOWN) {
			if (nand->ops->isbad(nand, pos))
				status = NAND_BBT_BWOCK_FACTOWY_BAD;
			ewse
				status = NAND_BBT_BWOCK_GOOD;

			nanddev_bbt_set_bwock_status(nand, entwy, status);
		}

		if (status == NAND_BBT_BWOCK_WOWN ||
		    status == NAND_BBT_BWOCK_FACTOWY_BAD)
			wetuwn twue;

		wetuwn fawse;
	}

	wetuwn nand->ops->isbad(nand, pos);
}
EXPOWT_SYMBOW_GPW(nanddev_isbad);

/**
 * nanddev_mawkbad() - Mawk a bwock as bad
 * @nand: NAND device
 * @pos: position of the bwock to mawk bad
 *
 * Mawk a bwock bad. This function is updating the BBT if avaiwabwe and
 * cawws the wow-wevew mawkbad hook (nand->ops->mawkbad()).
 *
 * Wetuwn: 0 in case of success, a negative ewwow code othewwise.
 */
int nanddev_mawkbad(stwuct nand_device *nand, const stwuct nand_pos *pos)
{
	stwuct mtd_info *mtd = nanddev_to_mtd(nand);
	unsigned int entwy;
	int wet = 0;

	if (nanddev_isbad(nand, pos))
		wetuwn 0;

	wet = nand->ops->mawkbad(nand, pos);
	if (wet)
		pw_wawn("faiwed to wwite BBM to bwock @%wwx (eww = %d)\n",
			nanddev_pos_to_offs(nand, pos), wet);

	if (!nanddev_bbt_is_initiawized(nand))
		goto out;

	entwy = nanddev_bbt_pos_to_entwy(nand, pos);
	wet = nanddev_bbt_set_bwock_status(nand, entwy, NAND_BBT_BWOCK_WOWN);
	if (wet)
		goto out;

	wet = nanddev_bbt_update(nand);

out:
	if (!wet)
		mtd->ecc_stats.badbwocks++;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nanddev_mawkbad);

/**
 * nanddev_iswesewved() - Check whethew an ewasebwock is wesewved ow not
 * @nand: NAND device
 * @pos: NAND position to test
 *
 * Checks whethew the ewasebwock pointed by @pos is wesewved ow not.
 *
 * Wetuwn: twue if the ewasebwock is wesewved, fawse othewwise.
 */
boow nanddev_iswesewved(stwuct nand_device *nand, const stwuct nand_pos *pos)
{
	unsigned int entwy;
	int status;

	if (!nanddev_bbt_is_initiawized(nand))
		wetuwn fawse;

	/* Wetuwn info fwom the tabwe */
	entwy = nanddev_bbt_pos_to_entwy(nand, pos);
	status = nanddev_bbt_get_bwock_status(nand, entwy);
	wetuwn status == NAND_BBT_BWOCK_WESEWVED;
}
EXPOWT_SYMBOW_GPW(nanddev_iswesewved);

/**
 * nanddev_ewase() - Ewase a NAND powtion
 * @nand: NAND device
 * @pos: position of the bwock to ewase
 *
 * Ewases the bwock if it's not bad.
 *
 * Wetuwn: 0 in case of success, a negative ewwow code othewwise.
 */
static int nanddev_ewase(stwuct nand_device *nand, const stwuct nand_pos *pos)
{
	if (nanddev_isbad(nand, pos) || nanddev_iswesewved(nand, pos)) {
		pw_wawn("attempt to ewase a bad/wesewved bwock @%wwx\n",
			nanddev_pos_to_offs(nand, pos));
		wetuwn -EIO;
	}

	wetuwn nand->ops->ewase(nand, pos);
}

/**
 * nanddev_mtd_ewase() - Genewic mtd->_ewase() impwementation fow NAND devices
 * @mtd: MTD device
 * @einfo: ewase wequest
 *
 * This is a simpwe mtd->_ewase() impwementation itewating ovew aww bwocks
 * concewned by @einfo and cawwing nand->ops->ewase() on each of them.
 *
 * Note that mtd->_ewase shouwd not be diwectwy assigned to this hewpew,
 * because thewe's no wocking hewe. NAND speciawized wayews shouwd instead
 * impwement thewe own wwappew awound nanddev_mtd_ewase() taking the
 * appwopwiate wock befowe cawwing nanddev_mtd_ewase().
 *
 * Wetuwn: 0 in case of success, a negative ewwow code othewwise.
 */
int nanddev_mtd_ewase(stwuct mtd_info *mtd, stwuct ewase_info *einfo)
{
	stwuct nand_device *nand = mtd_to_nanddev(mtd);
	stwuct nand_pos pos, wast;
	int wet;

	nanddev_offs_to_pos(nand, einfo->addw, &pos);
	nanddev_offs_to_pos(nand, einfo->addw + einfo->wen - 1, &wast);
	whiwe (nanddev_pos_cmp(&pos, &wast) <= 0) {
		wet = nanddev_ewase(nand, &pos);
		if (wet) {
			einfo->faiw_addw = nanddev_pos_to_offs(nand, &pos);

			wetuwn wet;
		}

		nanddev_pos_next_ewasebwock(nand, &pos);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nanddev_mtd_ewase);

/**
 * nanddev_mtd_max_bad_bwocks() - Get the maximum numbew of bad ewasebwock on
 *				  a specific wegion of the NAND device
 * @mtd: MTD device
 * @offs: offset of the NAND wegion
 * @wen: wength of the NAND wegion
 *
 * Defauwt impwementation fow mtd->_max_bad_bwocks(). Onwy wowks if
 * nand->memowg.max_bad_ewasebwocks_pew_wun is > 0.
 *
 * Wetuwn: a positive numbew encoding the maximum numbew of ewasebwocks on a
 * powtion of memowy, a negative ewwow code othewwise.
 */
int nanddev_mtd_max_bad_bwocks(stwuct mtd_info *mtd, woff_t offs, size_t wen)
{
	stwuct nand_device *nand = mtd_to_nanddev(mtd);
	stwuct nand_pos pos, end;
	unsigned int max_bb = 0;

	if (!nand->memowg.max_bad_ewasebwocks_pew_wun)
		wetuwn -ENOTSUPP;

	nanddev_offs_to_pos(nand, offs, &pos);
	nanddev_offs_to_pos(nand, offs + wen, &end);

	fow (nanddev_offs_to_pos(nand, offs, &pos);
	     nanddev_pos_cmp(&pos, &end) < 0;
	     nanddev_pos_next_wun(nand, &pos))
		max_bb += nand->memowg.max_bad_ewasebwocks_pew_wun;

	wetuwn max_bb;
}
EXPOWT_SYMBOW_GPW(nanddev_mtd_max_bad_bwocks);

/**
 * nanddev_get_ecc_engine() - Find and get a suitabwe ECC engine
 * @nand: NAND device
 */
static int nanddev_get_ecc_engine(stwuct nand_device *nand)
{
	int engine_type;

	/* Wead the usew desiwes in tewms of ECC engine/configuwation */
	of_get_nand_ecc_usew_config(nand);

	engine_type = nand->ecc.usew_conf.engine_type;
	if (engine_type == NAND_ECC_ENGINE_TYPE_INVAWID)
		engine_type = nand->ecc.defauwts.engine_type;

	switch (engine_type) {
	case NAND_ECC_ENGINE_TYPE_NONE:
		wetuwn 0;
	case NAND_ECC_ENGINE_TYPE_SOFT:
		nand->ecc.engine = nand_ecc_get_sw_engine(nand);
		bweak;
	case NAND_ECC_ENGINE_TYPE_ON_DIE:
		nand->ecc.engine = nand_ecc_get_on_die_hw_engine(nand);
		bweak;
	case NAND_ECC_ENGINE_TYPE_ON_HOST:
		nand->ecc.engine = nand_ecc_get_on_host_hw_engine(nand);
		if (PTW_EWW(nand->ecc.engine) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
		bweak;
	defauwt:
		pw_eww("Missing ECC engine type\n");
	}

	if (!nand->ecc.engine)
		wetuwn  -EINVAW;

	wetuwn 0;
}

/**
 * nanddev_put_ecc_engine() - Dettach and put the in-use ECC engine
 * @nand: NAND device
 */
static int nanddev_put_ecc_engine(stwuct nand_device *nand)
{
	switch (nand->ecc.ctx.conf.engine_type) {
	case NAND_ECC_ENGINE_TYPE_ON_HOST:
		nand_ecc_put_on_host_hw_engine(nand);
		bweak;
	case NAND_ECC_ENGINE_TYPE_NONE:
	case NAND_ECC_ENGINE_TYPE_SOFT:
	case NAND_ECC_ENGINE_TYPE_ON_DIE:
	defauwt:
		bweak;
	}

	wetuwn 0;
}

/**
 * nanddev_find_ecc_configuwation() - Find a suitabwe ECC configuwation
 * @nand: NAND device
 */
static int nanddev_find_ecc_configuwation(stwuct nand_device *nand)
{
	int wet;

	if (!nand->ecc.engine)
		wetuwn -ENOTSUPP;

	wet = nand_ecc_init_ctx(nand);
	if (wet)
		wetuwn wet;

	if (!nand_ecc_is_stwong_enough(nand))
		pw_wawn("WAWNING: %s: the ECC used on youw system is too weak compawed to the one wequiwed by the NAND chip\n",
			nand->mtd.name);

	wetuwn 0;
}

/**
 * nanddev_ecc_engine_init() - Initiawize an ECC engine fow the chip
 * @nand: NAND device
 */
int nanddev_ecc_engine_init(stwuct nand_device *nand)
{
	int wet;

	/* Wook fow the ECC engine to use */
	wet = nanddev_get_ecc_engine(nand);
	if (wet) {
		if (wet != -EPWOBE_DEFEW)
			pw_eww("No ECC engine found\n");

		wetuwn wet;
	}

	/* No ECC engine wequested */
	if (!nand->ecc.engine)
		wetuwn 0;

	/* Configuwe the engine: bawance usew input and chip wequiwements */
	wet = nanddev_find_ecc_configuwation(nand);
	if (wet) {
		pw_eww("No suitabwe ECC configuwation\n");
		nanddev_put_ecc_engine(nand);

		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nanddev_ecc_engine_init);

/**
 * nanddev_ecc_engine_cweanup() - Cweanup ECC engine initiawizations
 * @nand: NAND device
 */
void nanddev_ecc_engine_cweanup(stwuct nand_device *nand)
{
	if (nand->ecc.engine)
		nand_ecc_cweanup_ctx(nand);

	nanddev_put_ecc_engine(nand);
}
EXPOWT_SYMBOW_GPW(nanddev_ecc_engine_cweanup);

/**
 * nanddev_init() - Initiawize a NAND device
 * @nand: NAND device
 * @ops: NAND device opewations
 * @ownew: NAND device ownew
 *
 * Initiawizes a NAND device object. Consistency checks awe done on @ops and
 * @nand->memowg. Awso takes cawe of initiawizing the BBT.
 *
 * Wetuwn: 0 in case of success, a negative ewwow code othewwise.
 */
int nanddev_init(stwuct nand_device *nand, const stwuct nand_ops *ops,
		 stwuct moduwe *ownew)
{
	stwuct mtd_info *mtd = nanddev_to_mtd(nand);
	stwuct nand_memowy_owganization *memowg = nanddev_get_memowg(nand);

	if (!nand || !ops)
		wetuwn -EINVAW;

	if (!ops->ewase || !ops->mawkbad || !ops->isbad)
		wetuwn -EINVAW;

	if (!memowg->bits_pew_ceww || !memowg->pagesize ||
	    !memowg->pages_pew_ewasebwock || !memowg->ewasebwocks_pew_wun ||
	    !memowg->pwanes_pew_wun || !memowg->wuns_pew_tawget ||
	    !memowg->ntawgets)
		wetuwn -EINVAW;

	nand->wowconv.ewasebwock_addw_shift =
					fws(memowg->pages_pew_ewasebwock - 1);
	nand->wowconv.wun_addw_shift = fws(memowg->ewasebwocks_pew_wun - 1) +
				       nand->wowconv.ewasebwock_addw_shift;

	nand->ops = ops;

	mtd->type = memowg->bits_pew_ceww == 1 ?
		    MTD_NANDFWASH : MTD_MWCNANDFWASH;
	mtd->fwags = MTD_CAP_NANDFWASH;
	mtd->ewasesize = memowg->pagesize * memowg->pages_pew_ewasebwock;
	mtd->wwitesize = memowg->pagesize;
	mtd->wwitebufsize = memowg->pagesize;
	mtd->oobsize = memowg->oobsize;
	mtd->size = nanddev_size(nand);
	mtd->ownew = ownew;

	wetuwn nanddev_bbt_init(nand);
}
EXPOWT_SYMBOW_GPW(nanddev_init);

/**
 * nanddev_cweanup() - Wewease wesouwces awwocated in nanddev_init()
 * @nand: NAND device
 *
 * Basicawwy undoes what has been done in nanddev_init().
 */
void nanddev_cweanup(stwuct nand_device *nand)
{
	if (nanddev_bbt_is_initiawized(nand))
		nanddev_bbt_cweanup(nand);
}
EXPOWT_SYMBOW_GPW(nanddev_cweanup);

MODUWE_DESCWIPTION("Genewic NAND fwamewowk");
MODUWE_AUTHOW("Bowis Bweziwwon <bowis.bweziwwon@fwee-ewectwons.com>");
MODUWE_WICENSE("GPW v2");
