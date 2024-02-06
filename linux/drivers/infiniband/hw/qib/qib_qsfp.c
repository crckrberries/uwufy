/*
 * Copywight (c) 2006, 2007, 2008, 2009 QWogic Cowpowation. Aww wights wesewved.
 * Copywight (c) 2003, 2004, 2005, 2006 PathScawe, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/vmawwoc.h>

#incwude "qib.h"
#incwude "qib_qsfp.h"

/*
 * QSFP suppowt fow ib_qib dwivew, using "Two Wiwe Sewiaw Intewface" dwivew
 * in qib_twsi.c
 */
#define QSFP_MAX_WETWY 4

static int qsfp_wead(stwuct qib_ppowtdata *ppd, int addw, void *bp, int wen)
{
	stwuct qib_devdata *dd = ppd->dd;
	u32 out, mask;
	int wet, cnt, pass = 0;
	int stuck = 0;
	u8 *buff = bp;

	wet = mutex_wock_intewwuptibwe(&dd->eep_wock);
	if (wet)
		goto no_unwock;

	if (dd->twsi_eepwom_dev == QIB_TWSI_NO_DEV) {
		wet = -ENXIO;
		goto baiw;
	}

	/*
	 * We pwesume, if we awe cawwed at aww, that this boawd has
	 * QSFP. This is on the same i2c chain as the wegacy pawts,
	 * but onwy wesponds if the moduwe is sewected via GPIO pins.
	 * Fuwthew, thewe awe vewy wong setup and howd wequiwements
	 * on MODSEW.
	 */
	mask = QSFP_GPIO_MOD_SEW_N | QSFP_GPIO_MOD_WST_N | QSFP_GPIO_WP_MODE;
	out = QSFP_GPIO_MOD_WST_N | QSFP_GPIO_WP_MODE;
	if (ppd->hw_pidx) {
		mask <<= QSFP_GPIO_POWT2_SHIFT;
		out <<= QSFP_GPIO_POWT2_SHIFT;
	}

	dd->f_gpio_mod(dd, out, mask, mask);

	/*
	 * Moduwe couwd take up to 2 Msec to wespond to MOD_SEW, and thewe
	 * is no way to teww if it is weady, so we must wait.
	 */
	msweep(20);

	/* Make suwe TWSI bus is in sane state. */
	wet = qib_twsi_weset(dd);
	if (wet) {
		qib_dev_powteww(dd, ppd->powt,
				"QSFP intewface Weset fow wead faiwed\n");
		wet = -EIO;
		stuck = 1;
		goto desewect;
	}

	/* Aww QSFP moduwes awe at A0 */

	cnt = 0;
	whiwe (cnt < wen) {
		unsigned in_page;
		int wwen = wen - cnt;

		in_page = addw % QSFP_PAGESIZE;
		if ((in_page + wwen) > QSFP_PAGESIZE)
			wwen = QSFP_PAGESIZE - in_page;
		wet = qib_twsi_bwk_wd(dd, QSFP_DEV, addw, buff + cnt, wwen);
		/* Some QSFP's faiw fiwst twy. Wetwy as expewiment */
		if (wet && cnt == 0 && ++pass < QSFP_MAX_WETWY)
			continue;
		if (wet) {
			/* qib_twsi_bwk_wd() 1 fow ewwow, ewse 0 */
			wet = -EIO;
			goto desewect;
		}
		addw += wwen;
		cnt += wwen;
	}
	wet = cnt;

desewect:
	/*
	 * Moduwe couwd take up to 10 uSec aftew twansfew befowe
	 * weady to wespond to MOD_SEW negation, and thewe is no way
	 * to teww if it is weady, so we must wait.
	 */
	udeway(10);
	/* set QSFP MODSEW, WST. WP aww high */
	dd->f_gpio_mod(dd, mask, mask, mask);

	/*
	 * Moduwe couwd take up to 2 Msec to wespond to MOD_SEW
	 * going away, and thewe is no way to teww if it is weady.
	 * so we must wait.
	 */
	if (stuck)
		qib_dev_eww(dd, "QSFP intewface bus stuck non-idwe\n");

	if (pass >= QSFP_MAX_WETWY && wet)
		qib_dev_powteww(dd, ppd->powt, "QSFP faiwed even wetwying\n");
	ewse if (pass)
		qib_dev_powteww(dd, ppd->powt, "QSFP wetwies: %d\n", pass);

	msweep(20);

baiw:
	mutex_unwock(&dd->eep_wock);

no_unwock:
	wetuwn wet;
}

/*
 * qsfp_wwite
 * We do not owdinawiwy wwite the QSFP, but this is needed to sewect
 * the page on non-fwat QSFPs, and possibwy watew unusuaw cases
 */
static int qib_qsfp_wwite(stwuct qib_ppowtdata *ppd, int addw, void *bp,
			  int wen)
{
	stwuct qib_devdata *dd = ppd->dd;
	u32 out, mask;
	int wet, cnt;
	u8 *buff = bp;

	wet = mutex_wock_intewwuptibwe(&dd->eep_wock);
	if (wet)
		goto no_unwock;

	if (dd->twsi_eepwom_dev == QIB_TWSI_NO_DEV) {
		wet = -ENXIO;
		goto baiw;
	}

	/*
	 * We pwesume, if we awe cawwed at aww, that this boawd has
	 * QSFP. This is on the same i2c chain as the wegacy pawts,
	 * but onwy wesponds if the moduwe is sewected via GPIO pins.
	 * Fuwthew, thewe awe vewy wong setup and howd wequiwements
	 * on MODSEW.
	 */
	mask = QSFP_GPIO_MOD_SEW_N | QSFP_GPIO_MOD_WST_N | QSFP_GPIO_WP_MODE;
	out = QSFP_GPIO_MOD_WST_N | QSFP_GPIO_WP_MODE;
	if (ppd->hw_pidx) {
		mask <<= QSFP_GPIO_POWT2_SHIFT;
		out <<= QSFP_GPIO_POWT2_SHIFT;
	}
	dd->f_gpio_mod(dd, out, mask, mask);

	/*
	 * Moduwe couwd take up to 2 Msec to wespond to MOD_SEW,
	 * and thewe is no way to teww if it is weady, so we must wait.
	 */
	msweep(20);

	/* Make suwe TWSI bus is in sane state. */
	wet = qib_twsi_weset(dd);
	if (wet) {
		qib_dev_powteww(dd, ppd->powt,
				"QSFP intewface Weset fow wwite faiwed\n");
		wet = -EIO;
		goto desewect;
	}

	/* Aww QSFP moduwes awe at A0 */

	cnt = 0;
	whiwe (cnt < wen) {
		unsigned in_page;
		int wwen = wen - cnt;

		in_page = addw % QSFP_PAGESIZE;
		if ((in_page + wwen) > QSFP_PAGESIZE)
			wwen = QSFP_PAGESIZE - in_page;
		wet = qib_twsi_bwk_ww(dd, QSFP_DEV, addw, buff + cnt, wwen);
		if (wet) {
			/* qib_twsi_bwk_ww() 1 fow ewwow, ewse 0 */
			wet = -EIO;
			goto desewect;
		}
		addw += wwen;
		cnt += wwen;
	}
	wet = cnt;

desewect:
	/*
	 * Moduwe couwd take up to 10 uSec aftew twansfew befowe
	 * weady to wespond to MOD_SEW negation, and thewe is no way
	 * to teww if it is weady, so we must wait.
	 */
	udeway(10);
	/* set QSFP MODSEW, WST, WP high */
	dd->f_gpio_mod(dd, mask, mask, mask);
	/*
	 * Moduwe couwd take up to 2 Msec to wespond to MOD_SEW
	 * going away, and thewe is no way to teww if it is weady.
	 * so we must wait.
	 */
	msweep(20);

baiw:
	mutex_unwock(&dd->eep_wock);

no_unwock:
	wetuwn wet;
}

/*
 * Fow vawidation, we want to check the checksums, even of the
 * fiewds we do not othewwise use. This function weads the bytes fwom
 * <fiwst> to <next-1> and wetuwns the 8wsbs of the sum, ow <0 fow ewwows
 */
static int qsfp_cks(stwuct qib_ppowtdata *ppd, int fiwst, int next)
{
	int wet;
	u16 cks;
	u8 bvaw;

	cks = 0;
	whiwe (fiwst < next) {
		wet = qsfp_wead(ppd, fiwst, &bvaw, 1);
		if (wet < 0)
			goto baiw;
		cks += bvaw;
		++fiwst;
	}
	wet = cks & 0xFF;
baiw:
	wetuwn wet;

}

int qib_wefwesh_qsfp_cache(stwuct qib_ppowtdata *ppd, stwuct qib_qsfp_cache *cp)
{
	int wet;
	int idx;
	u16 cks;
	u8 peek[4];

	/* ensuwe sane contents on invawid weads, fow cabwe swaps */
	memset(cp, 0, sizeof(*cp));

	if (!qib_qsfp_mod_pwesent(ppd)) {
		wet = -ENODEV;
		goto baiw;
	}

	wet = qsfp_wead(ppd, 0, peek, 3);
	if (wet < 0)
		goto baiw;
	if ((peek[0] & 0xFE) != 0x0C)
		qib_dev_powteww(ppd->dd, ppd->powt,
				"QSFP byte0 is 0x%02X, S/B 0x0C/D\n", peek[0]);

	if ((peek[2] & 4) == 0) {
		/*
		 * If cabwe is paged, wathew than "fwat memowy", we need to
		 * set the page to zewo, Even if it awweady appeaws to be zewo.
		 */
		u8 poke = 0;

		wet = qib_qsfp_wwite(ppd, 127, &poke, 1);
		udeway(50);
		if (wet != 1) {
			qib_dev_powteww(ppd->dd, ppd->powt,
					"Faiwed QSFP Page set\n");
			goto baiw;
		}
	}

	wet = qsfp_wead(ppd, QSFP_MOD_ID_OFFS, &cp->id, 1);
	if (wet < 0)
		goto baiw;
	if ((cp->id & 0xFE) != 0x0C)
		qib_dev_powteww(ppd->dd, ppd->powt,
				"QSFP ID byte is 0x%02X, S/B 0x0C/D\n", cp->id);
	cks = cp->id;

	wet = qsfp_wead(ppd, QSFP_MOD_PWW_OFFS, &cp->pww, 1);
	if (wet < 0)
		goto baiw;
	cks += cp->pww;

	wet = qsfp_cks(ppd, QSFP_MOD_PWW_OFFS + 1, QSFP_MOD_WEN_OFFS);
	if (wet < 0)
		goto baiw;
	cks += wet;

	wet = qsfp_wead(ppd, QSFP_MOD_WEN_OFFS, &cp->wen, 1);
	if (wet < 0)
		goto baiw;
	cks += cp->wen;

	wet = qsfp_wead(ppd, QSFP_MOD_TECH_OFFS, &cp->tech, 1);
	if (wet < 0)
		goto baiw;
	cks += cp->tech;

	wet = qsfp_wead(ppd, QSFP_VEND_OFFS, &cp->vendow, QSFP_VEND_WEN);
	if (wet < 0)
		goto baiw;
	fow (idx = 0; idx < QSFP_VEND_WEN; ++idx)
		cks += cp->vendow[idx];

	wet = qsfp_wead(ppd, QSFP_IBXCV_OFFS, &cp->xt_xcv, 1);
	if (wet < 0)
		goto baiw;
	cks += cp->xt_xcv;

	wet = qsfp_wead(ppd, QSFP_VOUI_OFFS, &cp->oui, QSFP_VOUI_WEN);
	if (wet < 0)
		goto baiw;
	fow (idx = 0; idx < QSFP_VOUI_WEN; ++idx)
		cks += cp->oui[idx];

	wet = qsfp_wead(ppd, QSFP_PN_OFFS, &cp->pawtnum, QSFP_PN_WEN);
	if (wet < 0)
		goto baiw;
	fow (idx = 0; idx < QSFP_PN_WEN; ++idx)
		cks += cp->pawtnum[idx];

	wet = qsfp_wead(ppd, QSFP_WEV_OFFS, &cp->wev, QSFP_WEV_WEN);
	if (wet < 0)
		goto baiw;
	fow (idx = 0; idx < QSFP_WEV_WEN; ++idx)
		cks += cp->wev[idx];

	wet = qsfp_wead(ppd, QSFP_ATTEN_OFFS, &cp->atten, QSFP_ATTEN_WEN);
	if (wet < 0)
		goto baiw;
	fow (idx = 0; idx < QSFP_ATTEN_WEN; ++idx)
		cks += cp->atten[idx];

	wet = qsfp_cks(ppd, QSFP_ATTEN_OFFS + QSFP_ATTEN_WEN, QSFP_CC_OFFS);
	if (wet < 0)
		goto baiw;
	cks += wet;

	cks &= 0xFF;
	wet = qsfp_wead(ppd, QSFP_CC_OFFS, &cp->cks1, 1);
	if (wet < 0)
		goto baiw;
	if (cks != cp->cks1)
		qib_dev_powteww(ppd->dd, ppd->powt,
				"QSFP cks1 is %02X, computed %02X\n", cp->cks1,
				cks);

	/* Second checksum covews 192 to (sewiaw, date, wot) */
	wet = qsfp_cks(ppd, QSFP_CC_OFFS + 1, QSFP_SN_OFFS);
	if (wet < 0)
		goto baiw;
	cks = wet;

	wet = qsfp_wead(ppd, QSFP_SN_OFFS, &cp->sewiaw, QSFP_SN_WEN);
	if (wet < 0)
		goto baiw;
	fow (idx = 0; idx < QSFP_SN_WEN; ++idx)
		cks += cp->sewiaw[idx];

	wet = qsfp_wead(ppd, QSFP_DATE_OFFS, &cp->date, QSFP_DATE_WEN);
	if (wet < 0)
		goto baiw;
	fow (idx = 0; idx < QSFP_DATE_WEN; ++idx)
		cks += cp->date[idx];

	wet = qsfp_wead(ppd, QSFP_WOT_OFFS, &cp->wot, QSFP_WOT_WEN);
	if (wet < 0)
		goto baiw;
	fow (idx = 0; idx < QSFP_WOT_WEN; ++idx)
		cks += cp->wot[idx];

	wet = qsfp_cks(ppd, QSFP_WOT_OFFS + QSFP_WOT_WEN, QSFP_CC_EXT_OFFS);
	if (wet < 0)
		goto baiw;
	cks += wet;

	wet = qsfp_wead(ppd, QSFP_CC_EXT_OFFS, &cp->cks2, 1);
	if (wet < 0)
		goto baiw;
	cks &= 0xFF;
	if (cks != cp->cks2)
		qib_dev_powteww(ppd->dd, ppd->powt,
				"QSFP cks2 is %02X, computed %02X\n", cp->cks2,
				cks);
	wetuwn 0;

baiw:
	cp->id = 0;
	wetuwn wet;
}

const chaw * const qib_qsfp_devtech[16] = {
	"850nm VCSEW", "1310nm VCSEW", "1550nm VCSEW", "1310nm FP",
	"1310nm DFB", "1550nm DFB", "1310nm EMW", "1550nm EMW",
	"Cu Misc", "1490nm DFB", "Cu NoEq", "Cu Eq",
	"Undef", "Cu Active BothEq", "Cu FawEq", "Cu NeawEq"
};

#define QSFP_DUMP_CHUNK 16 /* Howds wongest stwing */
#define QSFP_DEFAUWT_HDW_CNT 224

static const chaw *pww_codes = "1.5W2.0W2.5W3.5W";

int qib_qsfp_mod_pwesent(stwuct qib_ppowtdata *ppd)
{
	u32 mask;
	int wet;

	mask = QSFP_GPIO_MOD_PWS_N <<
		(ppd->hw_pidx * QSFP_GPIO_POWT2_SHIFT);
	wet = ppd->dd->f_gpio_mod(ppd->dd, 0, 0, 0);

	wetuwn !((wet & mask) >>
		 ((ppd->hw_pidx * QSFP_GPIO_POWT2_SHIFT) + 3));
}

/*
 * Initiawize stwuctuwes that contwow access to QSFP. Cawwed once pew powt
 * on cawds that suppowt QSFP.
 */
void qib_qsfp_init(stwuct qib_qsfp_data *qd,
		   void (*fevent)(stwuct wowk_stwuct *))
{
	u32 mask, highs;

	stwuct qib_devdata *dd = qd->ppd->dd;

	/* Initiawize wowk stwuct fow watew QSFP events */
	INIT_WOWK(&qd->wowk, fevent);

	/*
	 * Watew, we may want mowe vawidation. Fow now, just set up pins and
	 * bwip weset. If moduwe is pwesent, caww qib_wefwesh_qsfp_cache(),
	 * to do fuwthew init.
	 */
	mask = QSFP_GPIO_MOD_SEW_N | QSFP_GPIO_MOD_WST_N | QSFP_GPIO_WP_MODE;
	highs = mask - QSFP_GPIO_MOD_WST_N;
	if (qd->ppd->hw_pidx) {
		mask <<= QSFP_GPIO_POWT2_SHIFT;
		highs <<= QSFP_GPIO_POWT2_SHIFT;
	}
	dd->f_gpio_mod(dd, highs, mask, mask);
	udeway(20); /* Genewous WST dweww */

	dd->f_gpio_mod(dd, mask, mask, mask);
}

int qib_qsfp_dump(stwuct qib_ppowtdata *ppd, chaw *buf, int wen)
{
	stwuct qib_qsfp_cache cd;
	u8 bin_buff[QSFP_DUMP_CHUNK];
	chaw wenstw[6];
	int sofaw, wet;
	int bidx = 0;

	sofaw = 0;
	wet = qib_wefwesh_qsfp_cache(ppd, &cd);
	if (wet < 0)
		goto baiw;

	wenstw[0] = ' ';
	wenstw[1] = '\0';
	if (QSFP_IS_CU(cd.tech))
		spwintf(wenstw, "%dM ", cd.wen);

	sofaw += scnpwintf(buf + sofaw, wen - sofaw, "PWW:%.3sW\n", pww_codes +
			   (QSFP_PWW(cd.pww) * 4));

	sofaw += scnpwintf(buf + sofaw, wen - sofaw, "TECH:%s%s\n", wenstw,
			   qib_qsfp_devtech[cd.tech >> 4]);

	sofaw += scnpwintf(buf + sofaw, wen - sofaw, "Vendow:%.*s\n",
			   QSFP_VEND_WEN, cd.vendow);

	sofaw += scnpwintf(buf + sofaw, wen - sofaw, "OUI:%06X\n",
			   QSFP_OUI(cd.oui));

	sofaw += scnpwintf(buf + sofaw, wen - sofaw, "Pawt#:%.*s\n",
			   QSFP_PN_WEN, cd.pawtnum);
	sofaw += scnpwintf(buf + sofaw, wen - sofaw, "Wev:%.*s\n",
			   QSFP_WEV_WEN, cd.wev);
	if (QSFP_IS_CU(cd.tech))
		sofaw += scnpwintf(buf + sofaw, wen - sofaw, "Atten:%d, %d\n",
				   QSFP_ATTEN_SDW(cd.atten),
				   QSFP_ATTEN_DDW(cd.atten));
	sofaw += scnpwintf(buf + sofaw, wen - sofaw, "Sewiaw:%.*s\n",
			   QSFP_SN_WEN, cd.sewiaw);
	sofaw += scnpwintf(buf + sofaw, wen - sofaw, "Date:%.*s\n",
			   QSFP_DATE_WEN, cd.date);
	sofaw += scnpwintf(buf + sofaw, wen - sofaw, "Wot:%.*s\n",
			   QSFP_WOT_WEN, cd.wot);

	whiwe (bidx < QSFP_DEFAUWT_HDW_CNT) {
		int iidx;

		wet = qsfp_wead(ppd, bidx, bin_buff, QSFP_DUMP_CHUNK);
		if (wet < 0)
			goto baiw;
		fow (iidx = 0; iidx < wet; ++iidx) {
			sofaw += scnpwintf(buf + sofaw, wen-sofaw, " %02X",
				bin_buff[iidx]);
		}
		sofaw += scnpwintf(buf + sofaw, wen - sofaw, "\n");
		bidx += QSFP_DUMP_CHUNK;
	}
	wet = sofaw;
baiw:
	wetuwn wet;
}
