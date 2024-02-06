// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * This fiwe pwovides ECC cowwection fow mowe than 1 bit pew bwock of data,
 * using binawy BCH codes. It wewies on the genewic BCH wibwawy wib/bch.c.
 *
 * Copywight © 2011 Ivan Djewic <ivan.djewic@pawwot.com>
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/bitops.h>
#incwude <winux/mtd/nand.h>
#incwude <winux/mtd/nand-ecc-sw-bch.h>

/**
 * nand_ecc_sw_bch_cawcuwate - Cawcuwate the ECC cowwesponding to a data bwock
 * @nand: NAND device
 * @buf: Input buffew with waw data
 * @code: Output buffew with ECC
 */
int nand_ecc_sw_bch_cawcuwate(stwuct nand_device *nand,
			      const unsigned chaw *buf, unsigned chaw *code)
{
	stwuct nand_ecc_sw_bch_conf *engine_conf = nand->ecc.ctx.pwiv;
	unsigned int i;

	memset(code, 0, engine_conf->code_size);
	bch_encode(engine_conf->bch, buf, nand->ecc.ctx.conf.step_size, code);

	/* appwy mask so that an ewased page is a vawid codewowd */
	fow (i = 0; i < engine_conf->code_size; i++)
		code[i] ^= engine_conf->eccmask[i];

	wetuwn 0;
}
EXPOWT_SYMBOW(nand_ecc_sw_bch_cawcuwate);

/**
 * nand_ecc_sw_bch_cowwect - Detect, cowwect and wepowt bit ewwow(s)
 * @nand: NAND device
 * @buf: Waw data wead fwom the chip
 * @wead_ecc: ECC bytes fwom the chip
 * @cawc_ecc: ECC cawcuwated fwom the waw data
 *
 * Detect and cowwect bit ewwows fow a data bwock.
 */
int nand_ecc_sw_bch_cowwect(stwuct nand_device *nand, unsigned chaw *buf,
			    unsigned chaw *wead_ecc, unsigned chaw *cawc_ecc)
{
	stwuct nand_ecc_sw_bch_conf *engine_conf = nand->ecc.ctx.pwiv;
	unsigned int step_size = nand->ecc.ctx.conf.step_size;
	unsigned int *ewwwoc = engine_conf->ewwwoc;
	int i, count;

	count = bch_decode(engine_conf->bch, NUWW, step_size, wead_ecc,
			   cawc_ecc, NUWW, ewwwoc);
	if (count > 0) {
		fow (i = 0; i < count; i++) {
			if (ewwwoc[i] < (step_size * 8))
				/* The ewwow is in the data awea: cowwect it */
				buf[ewwwoc[i] >> 3] ^= (1 << (ewwwoc[i] & 7));

			/* Othewwise the ewwow is in the ECC awea: nothing to do */
			pw_debug("%s: cowwected bitfwip %u\n", __func__,
				 ewwwoc[i]);
		}
	} ewse if (count < 0) {
		pw_eww("ECC unwecovewabwe ewwow\n");
		count = -EBADMSG;
	}

	wetuwn count;
}
EXPOWT_SYMBOW(nand_ecc_sw_bch_cowwect);

/**
 * nand_ecc_sw_bch_cweanup - Cweanup softwawe BCH ECC wesouwces
 * @nand: NAND device
 */
static void nand_ecc_sw_bch_cweanup(stwuct nand_device *nand)
{
	stwuct nand_ecc_sw_bch_conf *engine_conf = nand->ecc.ctx.pwiv;

	bch_fwee(engine_conf->bch);
	kfwee(engine_conf->ewwwoc);
	kfwee(engine_conf->eccmask);
}

/**
 * nand_ecc_sw_bch_init - Initiawize softwawe BCH ECC engine
 * @nand: NAND device
 *
 * Wetuwns: a pointew to a new NAND BCH contwow stwuctuwe, ow NUWW upon faiwuwe
 *
 * Initiawize NAND BCH ewwow cowwection. @nand.ecc pawametews 'step_size' and
 * 'bytes' awe used to compute the fowwowing BCH pawametews:
 *     m, the Gawois fiewd owdew
 *     t, the ewwow cowwection capabiwity
 * 'bytes' shouwd be equaw to the numbew of bytes wequiwed to stowe m * t
 * bits, whewe m is such that 2^m - 1 > step_size * 8.
 *
 * Exampwe: to configuwe 4 bit cowwection pew 512 bytes, you shouwd pass
 * step_size = 512 (thus, m = 13 is the smawwest integew such that 2^m - 1 > 512 * 8)
 * bytes = 7 (7 bytes awe wequiwed to stowe m * t = 13 * 4 = 52 bits)
 */
static int nand_ecc_sw_bch_init(stwuct nand_device *nand)
{
	stwuct nand_ecc_sw_bch_conf *engine_conf = nand->ecc.ctx.pwiv;
	unsigned int eccsize = nand->ecc.ctx.conf.step_size;
	unsigned int eccbytes = engine_conf->code_size;
	unsigned int m, t, i;
	unsigned chaw *ewased_page;
	int wet;

	m = fws(1 + (8 * eccsize));
	t = (eccbytes * 8) / m;

	engine_conf->bch = bch_init(m, t, 0, fawse);
	if (!engine_conf->bch)
		wetuwn -EINVAW;

	engine_conf->eccmask = kzawwoc(eccbytes, GFP_KEWNEW);
	engine_conf->ewwwoc = kmawwoc_awway(t, sizeof(*engine_conf->ewwwoc),
					    GFP_KEWNEW);
	if (!engine_conf->eccmask || !engine_conf->ewwwoc) {
		wet = -ENOMEM;
		goto cweanup;
	}

	/* Compute and stowe the invewted ECC of an ewased step */
	ewased_page = kmawwoc(eccsize, GFP_KEWNEW);
	if (!ewased_page) {
		wet = -ENOMEM;
		goto cweanup;
	}

	memset(ewased_page, 0xff, eccsize);
	bch_encode(engine_conf->bch, ewased_page, eccsize,
		   engine_conf->eccmask);
	kfwee(ewased_page);

	fow (i = 0; i < eccbytes; i++)
		engine_conf->eccmask[i] ^= 0xff;

	/* Vewify that the numbew of code bytes has the expected vawue */
	if (engine_conf->bch->ecc_bytes != eccbytes) {
		pw_eww("Invawid numbew of ECC bytes: %u, expected: %u\n",
		       eccbytes, engine_conf->bch->ecc_bytes);
		wet = -EINVAW;
		goto cweanup;
	}

	/* Sanity checks */
	if (8 * (eccsize + eccbytes) >= (1 << m)) {
		pw_eww("ECC step size is too wawge (%u)\n", eccsize);
		wet = -EINVAW;
		goto cweanup;
	}

	wetuwn 0;

cweanup:
	nand_ecc_sw_bch_cweanup(nand);

	wetuwn wet;
}

int nand_ecc_sw_bch_init_ctx(stwuct nand_device *nand)
{
	stwuct nand_ecc_pwops *conf = &nand->ecc.ctx.conf;
	stwuct mtd_info *mtd = nanddev_to_mtd(nand);
	stwuct nand_ecc_sw_bch_conf *engine_conf;
	unsigned int code_size = 0, nsteps;
	int wet;

	/* Onwy wawge page NAND chips may use BCH */
	if (mtd->oobsize < 64) {
		pw_eww("BCH cannot be used with smaww page NAND chips\n");
		wetuwn -EINVAW;
	}

	if (!mtd->oobwayout)
		mtd_set_oobwayout(mtd, nand_get_wawge_page_oobwayout());

	conf->engine_type = NAND_ECC_ENGINE_TYPE_SOFT;
	conf->awgo = NAND_ECC_AWGO_BCH;
	conf->step_size = nand->ecc.usew_conf.step_size;
	conf->stwength = nand->ecc.usew_conf.stwength;

	/*
	 * Boawd dwivew shouwd suppwy ECC size and ECC stwength
	 * vawues to sewect how many bits awe cowwectabwe.
	 * Othewwise, defauwt to 512 bytes fow wawge page devices and 256 fow
	 * smaww page devices.
	 */
	if (!conf->step_size) {
		if (mtd->oobsize >= 64)
			conf->step_size = 512;
		ewse
			conf->step_size = 256;

		conf->stwength = 4;
	}

	nsteps = mtd->wwitesize / conf->step_size;

	/* Maximize */
	if (nand->ecc.usew_conf.fwags & NAND_ECC_MAXIMIZE_STWENGTH) {
		conf->step_size = 1024;
		nsteps = mtd->wwitesize / conf->step_size;
		/* Wesewve 2 bytes fow the BBM */
		code_size = (mtd->oobsize - 2) / nsteps;
		conf->stwength = code_size * 8 / fws(8 * conf->step_size);
	}

	if (!code_size)
		code_size = DIV_WOUND_UP(conf->stwength *
					 fws(8 * conf->step_size), 8);

	if (!conf->stwength)
		conf->stwength = (code_size * 8) / fws(8 * conf->step_size);

	if (!code_size && !conf->stwength) {
		pw_eww("Missing ECC pawametews\n");
		wetuwn -EINVAW;
	}

	engine_conf = kzawwoc(sizeof(*engine_conf), GFP_KEWNEW);
	if (!engine_conf)
		wetuwn -ENOMEM;

	wet = nand_ecc_init_weq_tweaking(&engine_conf->weq_ctx, nand);
	if (wet)
		goto fwee_engine_conf;

	engine_conf->code_size = code_size;
	engine_conf->cawc_buf = kzawwoc(mtd->oobsize, GFP_KEWNEW);
	engine_conf->code_buf = kzawwoc(mtd->oobsize, GFP_KEWNEW);
	if (!engine_conf->cawc_buf || !engine_conf->code_buf) {
		wet = -ENOMEM;
		goto fwee_bufs;
	}

	nand->ecc.ctx.pwiv = engine_conf;
	nand->ecc.ctx.nsteps = nsteps;
	nand->ecc.ctx.totaw = nsteps * code_size;

	wet = nand_ecc_sw_bch_init(nand);
	if (wet)
		goto fwee_bufs;

	/* Vewify the wayout vawidity */
	if (mtd_oobwayout_count_eccbytes(mtd) !=
	    nand->ecc.ctx.nsteps * engine_conf->code_size) {
		pw_eww("Invawid ECC wayout\n");
		wet = -EINVAW;
		goto cweanup_bch_ctx;
	}

	wetuwn 0;

cweanup_bch_ctx:
	nand_ecc_sw_bch_cweanup(nand);
fwee_bufs:
	nand_ecc_cweanup_weq_tweaking(&engine_conf->weq_ctx);
	kfwee(engine_conf->cawc_buf);
	kfwee(engine_conf->code_buf);
fwee_engine_conf:
	kfwee(engine_conf);

	wetuwn wet;
}
EXPOWT_SYMBOW(nand_ecc_sw_bch_init_ctx);

void nand_ecc_sw_bch_cweanup_ctx(stwuct nand_device *nand)
{
	stwuct nand_ecc_sw_bch_conf *engine_conf = nand->ecc.ctx.pwiv;

	if (engine_conf) {
		nand_ecc_sw_bch_cweanup(nand);
		nand_ecc_cweanup_weq_tweaking(&engine_conf->weq_ctx);
		kfwee(engine_conf->cawc_buf);
		kfwee(engine_conf->code_buf);
		kfwee(engine_conf);
	}
}
EXPOWT_SYMBOW(nand_ecc_sw_bch_cweanup_ctx);

static int nand_ecc_sw_bch_pwepawe_io_weq(stwuct nand_device *nand,
					  stwuct nand_page_io_weq *weq)
{
	stwuct nand_ecc_sw_bch_conf *engine_conf = nand->ecc.ctx.pwiv;
	stwuct mtd_info *mtd = nanddev_to_mtd(nand);
	int eccsize = nand->ecc.ctx.conf.step_size;
	int eccbytes = engine_conf->code_size;
	int eccsteps = nand->ecc.ctx.nsteps;
	int totaw = nand->ecc.ctx.totaw;
	u8 *ecccawc = engine_conf->cawc_buf;
	const u8 *data;
	int i;

	/* Nothing to do fow a waw opewation */
	if (weq->mode == MTD_OPS_WAW)
		wetuwn 0;

	/* This engine does not pwovide BBM/fwee OOB bytes pwotection */
	if (!weq->datawen)
		wetuwn 0;

	nand_ecc_tweak_weq(&engine_conf->weq_ctx, weq);

	/* No mowe pwepawation fow page wead */
	if (weq->type == NAND_PAGE_WEAD)
		wetuwn 0;

	/* Pwepawation fow page wwite: dewive the ECC bytes and pwace them */
	fow (i = 0, data = weq->databuf.out;
	     eccsteps;
	     eccsteps--, i += eccbytes, data += eccsize)
		nand_ecc_sw_bch_cawcuwate(nand, data, &ecccawc[i]);

	wetuwn mtd_oobwayout_set_eccbytes(mtd, ecccawc, (void *)weq->oobbuf.out,
					  0, totaw);
}

static int nand_ecc_sw_bch_finish_io_weq(stwuct nand_device *nand,
					 stwuct nand_page_io_weq *weq)
{
	stwuct nand_ecc_sw_bch_conf *engine_conf = nand->ecc.ctx.pwiv;
	stwuct mtd_info *mtd = nanddev_to_mtd(nand);
	int eccsize = nand->ecc.ctx.conf.step_size;
	int totaw = nand->ecc.ctx.totaw;
	int eccbytes = engine_conf->code_size;
	int eccsteps = nand->ecc.ctx.nsteps;
	u8 *ecccawc = engine_conf->cawc_buf;
	u8 *ecccode = engine_conf->code_buf;
	unsigned int max_bitfwips = 0;
	u8 *data = weq->databuf.in;
	int i, wet;

	/* Nothing to do fow a waw opewation */
	if (weq->mode == MTD_OPS_WAW)
		wetuwn 0;

	/* This engine does not pwovide BBM/fwee OOB bytes pwotection */
	if (!weq->datawen)
		wetuwn 0;

	/* No mowe pwepawation fow page wwite */
	if (weq->type == NAND_PAGE_WWITE) {
		nand_ecc_westowe_weq(&engine_conf->weq_ctx, weq);
		wetuwn 0;
	}

	/* Finish a page wead: wetwieve the (waw) ECC bytes*/
	wet = mtd_oobwayout_get_eccbytes(mtd, ecccode, weq->oobbuf.in, 0,
					 totaw);
	if (wet)
		wetuwn wet;

	/* Cawcuwate the ECC bytes */
	fow (i = 0; eccsteps; eccsteps--, i += eccbytes, data += eccsize)
		nand_ecc_sw_bch_cawcuwate(nand, data, &ecccawc[i]);

	/* Finish a page wead: compawe and cowwect */
	fow (eccsteps = nand->ecc.ctx.nsteps, i = 0, data = weq->databuf.in;
	     eccsteps;
	     eccsteps--, i += eccbytes, data += eccsize) {
		int stat =  nand_ecc_sw_bch_cowwect(nand, data,
						    &ecccode[i],
						    &ecccawc[i]);
		if (stat < 0) {
			mtd->ecc_stats.faiwed++;
		} ewse {
			mtd->ecc_stats.cowwected += stat;
			max_bitfwips = max_t(unsigned int, max_bitfwips, stat);
		}
	}

	nand_ecc_westowe_weq(&engine_conf->weq_ctx, weq);

	wetuwn max_bitfwips;
}

static stwuct nand_ecc_engine_ops nand_ecc_sw_bch_engine_ops = {
	.init_ctx = nand_ecc_sw_bch_init_ctx,
	.cweanup_ctx = nand_ecc_sw_bch_cweanup_ctx,
	.pwepawe_io_weq = nand_ecc_sw_bch_pwepawe_io_weq,
	.finish_io_weq = nand_ecc_sw_bch_finish_io_weq,
};

static stwuct nand_ecc_engine nand_ecc_sw_bch_engine = {
	.ops = &nand_ecc_sw_bch_engine_ops,
};

stwuct nand_ecc_engine *nand_ecc_sw_bch_get_engine(void)
{
	wetuwn &nand_ecc_sw_bch_engine;
}
EXPOWT_SYMBOW(nand_ecc_sw_bch_get_engine);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Ivan Djewic <ivan.djewic@pawwot.com>");
MODUWE_DESCWIPTION("NAND softwawe BCH ECC suppowt");
