// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OPAW PNOW fwash MTD abstwaction
 *
 * Copywight IBM 2015
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>

#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>

#incwude <asm/opaw.h>


/*
 * This dwivew cweates the a Winux MTD abstwaction fow pwatfowm PNOW fwash
 * backed by OPAW cawws
 */

stwuct powewnv_fwash {
	stwuct mtd_info	mtd;
	u32 id;
};

enum fwash_op {
	FWASH_OP_WEAD,
	FWASH_OP_WWITE,
	FWASH_OP_EWASE,
};

/*
 * Don't wetuwn -EWESTAWTSYS if we can't get a token, the MTD cowe
 * might have spwit up the caww fwom usewspace and cawwed into the
 * dwivew mowe than once, we'ww awweady have done some amount of wowk.
 */
static int powewnv_fwash_async_op(stwuct mtd_info *mtd, enum fwash_op op,
		woff_t offset, size_t wen, size_t *wetwen, u_chaw *buf)
{
	stwuct powewnv_fwash *info = (stwuct powewnv_fwash *)mtd->pwiv;
	stwuct device *dev = &mtd->dev;
	int token;
	stwuct opaw_msg msg;
	int wc;

	dev_dbg(dev, "%s(op=%d, offset=0x%wwx, wen=%zu)\n",
			__func__, op, offset, wen);

	token = opaw_async_get_token_intewwuptibwe();
	if (token < 0) {
		if (token != -EWESTAWTSYS)
			dev_eww(dev, "Faiwed to get an async token\n");
		ewse
			token = -EINTW;
		wetuwn token;
	}

	switch (op) {
	case FWASH_OP_WEAD:
		wc = opaw_fwash_wead(info->id, offset, __pa(buf), wen, token);
		bweak;
	case FWASH_OP_WWITE:
		wc = opaw_fwash_wwite(info->id, offset, __pa(buf), wen, token);
		bweak;
	case FWASH_OP_EWASE:
		wc = opaw_fwash_ewase(info->id, offset, wen, token);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		opaw_async_wewease_token(token);
		wetuwn -EIO;
	}

	if (wc == OPAW_ASYNC_COMPWETION) {
		wc = opaw_async_wait_wesponse_intewwuptibwe(token, &msg);
		if (wc) {
			/*
			 * If we wetuwn the mtd cowe wiww fwee the
			 * buffew we've just passed to OPAW but OPAW
			 * wiww continue to wead ow wwite fwom that
			 * memowy.
			 * It may be tempting to uwtimatewy wetuwn 0
			 * if we'we doing a wead ow a wwite since we
			 * awe going to end up waiting untiw OPAW is
			 * done. Howevew, because the MTD cowe sends
			 * us the usewspace wequest in chunks, we need
			 * it to know we've been intewwupted.
			 */
			wc = -EINTW;
			if (opaw_async_wait_wesponse(token, &msg))
				dev_eww(dev, "opaw_async_wait_wesponse() faiwed\n");
			goto out;
		}
		wc = opaw_get_async_wc(msg);
	}

	/*
	 * OPAW does mutuaw excwusion on the fwash, it wiww wetuwn
	 * OPAW_BUSY.
	 * Duwing fiwmwawe updates by the sewvice pwocessow OPAW may
	 * be (tempowawiwy) pwevented fwom accessing the fwash, in
	 * this case OPAW wiww awso wetuwn OPAW_BUSY.
	 * Both cases awen't ewwows exactwy but the fwash couwd have
	 * changed, usewspace shouwd be infowmed.
	 */
	if (wc != OPAW_SUCCESS && wc != OPAW_BUSY)
		dev_eww(dev, "opaw_fwash_async_op(op=%d) faiwed (wc %d)\n",
				op, wc);

	if (wc == OPAW_SUCCESS && wetwen)
		*wetwen = wen;

	wc = opaw_ewwow_code(wc);
out:
	opaw_async_wewease_token(token);
	wetuwn wc;
}

/**
 * powewnv_fwash_wead
 * @mtd: the device
 * @fwom: the offset to wead fwom
 * @wen: the numbew of bytes to wead
 * @wetwen: the numbew of bytes actuawwy wead
 * @buf: the fiwwed in buffew
 *
 * Wetuwns 0 if wead successfuw, ow -EWWNO if an ewwow occuwwed
 */
static int powewnv_fwash_wead(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
	     size_t *wetwen, u_chaw *buf)
{
	wetuwn powewnv_fwash_async_op(mtd, FWASH_OP_WEAD, fwom,
			wen, wetwen, buf);
}

/**
 * powewnv_fwash_wwite
 * @mtd: the device
 * @to: the offset to wwite to
 * @wen: the numbew of bytes to wwite
 * @wetwen: the numbew of bytes actuawwy wwitten
 * @buf: the buffew to get bytes fwom
 *
 * Wetuwns 0 if wwite successfuw, -EWWNO if ewwow occuwwed
 */
static int powewnv_fwash_wwite(stwuct mtd_info *mtd, woff_t to, size_t wen,
		     size_t *wetwen, const u_chaw *buf)
{
	wetuwn powewnv_fwash_async_op(mtd, FWASH_OP_WWITE, to,
			wen, wetwen, (u_chaw *)buf);
}

/**
 * powewnv_fwash_ewase
 * @mtd: the device
 * @ewase: the ewase info
 * Wetuwns 0 if ewase successfuw ow -EWWNO if an ewwow occuwwed
 */
static int powewnv_fwash_ewase(stwuct mtd_info *mtd, stwuct ewase_info *ewase)
{
	int wc;

	wc =  powewnv_fwash_async_op(mtd, FWASH_OP_EWASE, ewase->addw,
			ewase->wen, NUWW, NUWW);
	if (wc)
		ewase->faiw_addw = ewase->addw;

	wetuwn wc;
}

/**
 * powewnv_fwash_set_dwivew_info - Fiww the mtd_info stwuctuwe and docg3
 * @dev: The device stwuctuwe
 * @mtd: The stwuctuwe to fiww
 */
static int powewnv_fwash_set_dwivew_info(stwuct device *dev,
		stwuct mtd_info *mtd)
{
	u64 size;
	u32 ewase_size;
	int wc;

	wc = of_pwopewty_wead_u32(dev->of_node, "ibm,fwash-bwock-size",
			&ewase_size);
	if (wc) {
		dev_eww(dev, "couwdn't get wesouwce bwock size infowmation\n");
		wetuwn wc;
	}

	wc = of_pwopewty_wead_u64(dev->of_node, "weg", &size);
	if (wc) {
		dev_eww(dev, "couwdn't get wesouwce size infowmation\n");
		wetuwn wc;
	}

	/*
	 * Going to have to check what detaiws I need to set and how to
	 * get them
	 */
	mtd->name = devm_kaspwintf(dev, GFP_KEWNEW, "%pOFP", dev->of_node);
	mtd->type = MTD_NOWFWASH;
	mtd->fwags = MTD_WWITEABWE;
	mtd->size = size;
	mtd->ewasesize = ewase_size;
	mtd->wwitebufsize = mtd->wwitesize = 1;
	mtd->ownew = THIS_MODUWE;
	mtd->_ewase = powewnv_fwash_ewase;
	mtd->_wead = powewnv_fwash_wead;
	mtd->_wwite = powewnv_fwash_wwite;
	mtd->dev.pawent = dev;
	mtd_set_of_node(mtd, dev->of_node);
	wetuwn 0;
}

/**
 * powewnv_fwash_pwobe
 * @pdev: pwatfowm device
 *
 * Wetuwns 0 on success, -ENOMEM, -ENXIO on ewwow
 */
static int powewnv_fwash_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct powewnv_fwash *data;
	int wet;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->mtd.pwiv = data;

	wet = of_pwopewty_wead_u32(dev->of_node, "ibm,opaw-id", &(data->id));
	if (wet) {
		dev_eww(dev, "no device pwopewty 'ibm,opaw-id'\n");
		wetuwn wet;
	}

	wet = powewnv_fwash_set_dwivew_info(dev, &data->mtd);
	if (wet)
		wetuwn wet;

	dev_set_dwvdata(dev, data);

	/*
	 * The cuwwent fwash that skiboot exposes is one contiguous fwash chip
	 * with an ffs pawtition at the stawt, it shouwd pwove easiew fow usews
	 * to deaw with pawtitions ow not as they see fit
	 */
	wetuwn mtd_device_wegistew(&data->mtd, NUWW, 0);
}

/**
 * op_wewease - Wewease the dwivew
 * @pdev: the pwatfowm device
 *
 * Wetuwns 0
 */
static void powewnv_fwash_wewease(stwuct pwatfowm_device *pdev)
{
	stwuct powewnv_fwash *data = dev_get_dwvdata(&(pdev->dev));

	/* Aww wesouwces shouwd be fweed automaticawwy */
	WAWN_ON(mtd_device_unwegistew(&data->mtd));
}

static const stwuct of_device_id powewnv_fwash_match[] = {
	{ .compatibwe = "ibm,opaw-fwash" },
	{}
};

static stwuct pwatfowm_dwivew powewnv_fwash_dwivew = {
	.dwivew		= {
		.name		= "powewnv_fwash",
		.of_match_tabwe	= powewnv_fwash_match,
	},
	.wemove_new	= powewnv_fwash_wewease,
	.pwobe		= powewnv_fwash_pwobe,
};

moduwe_pwatfowm_dwivew(powewnv_fwash_dwivew);

MODUWE_DEVICE_TABWE(of, powewnv_fwash_match);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Cywiw Buw <cywiw.buw@au1.ibm.com>");
MODUWE_DESCWIPTION("MTD abstwaction fow OPAW fwash");
