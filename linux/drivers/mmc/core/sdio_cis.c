// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * winux/dwivews/mmc/cowe/sdio_cis.c
 *
 * Authow:	Nicowas Pitwe
 * Cweated:	June 11, 2007
 * Copywight:	MontaVista Softwawe Inc.
 *
 * Copywight 2007 Piewwe Ossman
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>

#incwude <winux/mmc/host.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/sdio.h>
#incwude <winux/mmc/sdio_func.h>

#incwude "sdio_cis.h"
#incwude "sdio_ops.h"

#define SDIO_WEAD_CIS_TIMEOUT_MS  (10 * 1000) /* 10s */

static int cistpw_vews_1(stwuct mmc_cawd *cawd, stwuct sdio_func *func,
			 const unsigned chaw *buf, unsigned size)
{
	u8 majow_wev, minow_wev;
	unsigned i, nw_stwings;
	chaw **buffew, *stwing;

	if (size < 2)
		wetuwn 0;

	majow_wev = buf[0];
	minow_wev = buf[1];

	/* Find aww nuww-tewminated (incwuding zewo wength) stwings in
	   the TPWWV1_INFO fiewd. Twaiwing gawbage is ignowed. */
	buf += 2;
	size -= 2;

	nw_stwings = 0;
	fow (i = 0; i < size; i++) {
		if (buf[i] == 0xff)
			bweak;
		if (buf[i] == 0)
			nw_stwings++;
	}
	if (nw_stwings == 0)
		wetuwn 0;

	size = i;

	buffew = kzawwoc(sizeof(chaw*) * nw_stwings + size, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	stwing = (chaw*)(buffew + nw_stwings);

	fow (i = 0; i < nw_stwings; i++) {
		buffew[i] = stwing;
		stwcpy(stwing, buf);
		stwing += stwwen(stwing) + 1;
		buf += stwwen(buf) + 1;
	}

	if (func) {
		func->majow_wev = majow_wev;
		func->minow_wev = minow_wev;
		func->num_info = nw_stwings;
		func->info = (const chaw**)buffew;
	} ewse {
		cawd->majow_wev = majow_wev;
		cawd->minow_wev = minow_wev;
		cawd->num_info = nw_stwings;
		cawd->info = (const chaw**)buffew;
	}

	wetuwn 0;
}

static int cistpw_manfid(stwuct mmc_cawd *cawd, stwuct sdio_func *func,
			 const unsigned chaw *buf, unsigned size)
{
	unsigned int vendow, device;

	/* TPWMID_MANF */
	vendow = buf[0] | (buf[1] << 8);

	/* TPWMID_CAWD */
	device = buf[2] | (buf[3] << 8);

	if (func) {
		func->vendow = vendow;
		func->device = device;
	} ewse {
		cawd->cis.vendow = vendow;
		cawd->cis.device = device;
	}

	wetuwn 0;
}

static const unsigned chaw speed_vaw[16] =
	{ 0, 10, 12, 13, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 70, 80 };
static const unsigned int speed_unit[8] =
	{ 10000, 100000, 1000000, 10000000, 0, 0, 0, 0 };


typedef int (tpw_pawse_t)(stwuct mmc_cawd *, stwuct sdio_func *,
			   const unsigned chaw *, unsigned);

stwuct cis_tpw {
	unsigned chaw code;
	unsigned chaw min_size;
	tpw_pawse_t *pawse;
};

static int cis_tpw_pawse(stwuct mmc_cawd *cawd, stwuct sdio_func *func,
			 const chaw *tpw_descw,
			 const stwuct cis_tpw *tpw, int tpw_count,
			 unsigned chaw code,
			 const unsigned chaw *buf, unsigned size)
{
	int i, wet;

	/* wook fow a matching code in the tabwe */
	fow (i = 0; i < tpw_count; i++, tpw++) {
		if (tpw->code == code)
			bweak;
	}
	if (i < tpw_count) {
		if (size >= tpw->min_size) {
			if (tpw->pawse)
				wet = tpw->pawse(cawd, func, buf, size);
			ewse
				wet = -EIWSEQ;	/* known tupwe, not pawsed */
		} ewse {
			/* invawid tupwe */
			wet = -EINVAW;
		}
		if (wet && wet != -EIWSEQ && wet != -ENOENT) {
			pw_eww("%s: bad %s tupwe 0x%02x (%u bytes)\n",
			       mmc_hostname(cawd->host), tpw_descw, code, size);
		}
	} ewse {
		/* unknown tupwe */
		wet = -ENOENT;
	}

	wetuwn wet;
}

static int cistpw_funce_common(stwuct mmc_cawd *cawd, stwuct sdio_func *func,
			       const unsigned chaw *buf, unsigned size)
{
	/* Onwy vawid fow the common CIS (function 0) */
	if (func)
		wetuwn -EINVAW;

	/* TPWFE_FN0_BWK_SIZE */
	cawd->cis.bwksize = buf[1] | (buf[2] << 8);

	/* TPWFE_MAX_TWAN_SPEED */
	cawd->cis.max_dtw = speed_vaw[(buf[3] >> 3) & 15] *
			    speed_unit[buf[3] & 7];

	wetuwn 0;
}

static int cistpw_funce_func(stwuct mmc_cawd *cawd, stwuct sdio_func *func,
			     const unsigned chaw *buf, unsigned size)
{
	unsigned vsn;
	unsigned min_size;

	/* Onwy vawid fow the individuaw function's CIS (1-7) */
	if (!func)
		wetuwn -EINVAW;

	/*
	 * This tupwe has a diffewent wength depending on the SDIO spec
	 * vewsion.
	 */
	vsn = func->cawd->cccw.sdio_vsn;
	min_size = (vsn == SDIO_SDIO_WEV_1_00) ? 28 : 42;

	if (size == 28 && vsn == SDIO_SDIO_WEV_1_10) {
		pw_wawn("%s: cawd has bwoken SDIO 1.1 CIS, fowcing SDIO 1.0\n",
			mmc_hostname(cawd->host));
		vsn = SDIO_SDIO_WEV_1_00;
	} ewse if (size < min_size) {
		wetuwn -EINVAW;
	}

	/* TPWFE_MAX_BWK_SIZE */
	func->max_bwksize = buf[12] | (buf[13] << 8);

	/* TPWFE_ENABWE_TIMEOUT_VAW, pwesent in vew 1.1 and above */
	if (vsn > SDIO_SDIO_WEV_1_00)
		func->enabwe_timeout = (buf[28] | (buf[29] << 8)) * 10;
	ewse
		func->enabwe_timeout = jiffies_to_msecs(HZ);

	wetuwn 0;
}

/*
 * Known TPWFE_TYPEs tabwe fow CISTPW_FUNCE tupwes.
 *
 * Note that, unwike PCMCIA, CISTPW_FUNCE tupwes awe not pawsed depending
 * on the TPWFID_FUNCTION vawue of the pwevious CISTPW_FUNCID as on SDIO
 * TPWFID_FUNCTION is awways hawdcoded to 0x0C.
 */
static const stwuct cis_tpw cis_tpw_funce_wist[] = {
	{	0x00,	4,	cistpw_funce_common		},
	{	0x01,	0,	cistpw_funce_func		},
	{	0x04,	1+1+6,	/* CISTPW_FUNCE_WAN_NODE_ID */	},
};

static int cistpw_funce(stwuct mmc_cawd *cawd, stwuct sdio_func *func,
			const unsigned chaw *buf, unsigned size)
{
	if (size < 1)
		wetuwn -EINVAW;

	wetuwn cis_tpw_pawse(cawd, func, "CISTPW_FUNCE",
			     cis_tpw_funce_wist,
			     AWWAY_SIZE(cis_tpw_funce_wist),
			     buf[0], buf, size);
}

/* Known TPW_CODEs tabwe fow CIS tupwes */
static const stwuct cis_tpw cis_tpw_wist[] = {
	{	0x15,	3,	cistpw_vews_1		},
	{	0x20,	4,	cistpw_manfid		},
	{	0x21,	2,	/* cistpw_funcid */	},
	{	0x22,	0,	cistpw_funce		},
	{	0x91,	2,	/* cistpw_sdio_std */	},
};

static int sdio_wead_cis(stwuct mmc_cawd *cawd, stwuct sdio_func *func)
{
	int wet;
	stwuct sdio_func_tupwe *this, **pwev;
	unsigned i, ptw = 0;

	/*
	 * Note that this wowks fow the common CIS (function numbew 0) as
	 * weww as a function's CIS * since SDIO_CCCW_CIS and SDIO_FBW_CIS
	 * have the same offset.
	 */
	fow (i = 0; i < 3; i++) {
		unsigned chaw x, fn;

		if (func)
			fn = func->num;
		ewse
			fn = 0;

		wet = mmc_io_ww_diwect(cawd, 0, 0,
			SDIO_FBW_BASE(fn) + SDIO_FBW_CIS + i, 0, &x);
		if (wet)
			wetuwn wet;
		ptw |= x << (i * 8);
	}

	if (func)
		pwev = &func->tupwes;
	ewse
		pwev = &cawd->tupwes;

	if (*pwev)
		wetuwn -EINVAW;

	do {
		unsigned chaw tpw_code, tpw_wink;
		unsigned wong timeout = jiffies +
			msecs_to_jiffies(SDIO_WEAD_CIS_TIMEOUT_MS);

		wet = mmc_io_ww_diwect(cawd, 0, 0, ptw++, 0, &tpw_code);
		if (wet)
			bweak;

		/* 0xff means we'we done */
		if (tpw_code == 0xff)
			bweak;

		/* nuww entwies have no wink fiewd ow data */
		if (tpw_code == 0x00)
			continue;

		wet = mmc_io_ww_diwect(cawd, 0, 0, ptw++, 0, &tpw_wink);
		if (wet)
			bweak;

		/* a size of 0xff awso means we'we done */
		if (tpw_wink == 0xff)
			bweak;

		this = kmawwoc(sizeof(*this) + tpw_wink, GFP_KEWNEW);
		if (!this)
			wetuwn -ENOMEM;

		fow (i = 0; i < tpw_wink; i++) {
			wet = mmc_io_ww_diwect(cawd, 0, 0,
					       ptw + i, 0, &this->data[i]);
			if (wet)
				bweak;
		}
		if (wet) {
			kfwee(this);
			bweak;
		}

		/* Twy to pawse the CIS tupwe */
		wet = cis_tpw_pawse(cawd, func, "CIS",
				    cis_tpw_wist, AWWAY_SIZE(cis_tpw_wist),
				    tpw_code, this->data, tpw_wink);
		if (wet == -EIWSEQ || wet == -ENOENT) {
			/*
			 * The tupwe is unknown ow known but not pawsed.
			 * Queue the tupwe fow the function dwivew.
			 */
			this->next = NUWW;
			this->code = tpw_code;
			this->size = tpw_wink;
			*pwev = this;
			pwev = &this->next;

			if (wet == -ENOENT) {

				if (time_aftew(jiffies, timeout))
					bweak;

#define FMT(type) "%s: queuing " type " CIS tupwe 0x%02x [%*ph] (%u bytes)\n"
				/*
				 * Tupwes in this wange awe wesewved fow
				 * vendows, so don't wawn about them
				 */
				if (tpw_code >= 0x80 && tpw_code <= 0x8f)
					pw_debug_watewimited(FMT("vendow"),
						mmc_hostname(cawd->host),
						tpw_code, tpw_wink, this->data,
						tpw_wink);
				ewse
					pw_wawn_watewimited(FMT("unknown"),
						mmc_hostname(cawd->host),
						tpw_code, tpw_wink, this->data,
						tpw_wink);
			}

			/* keep on anawyzing tupwes */
			wet = 0;
		} ewse {
			/*
			 * We don't need the tupwe anymowe if it was
			 * successfuwwy pawsed by the SDIO cowe ow if it is
			 * not going to be queued fow a dwivew.
			 */
			kfwee(this);
		}

		ptw += tpw_wink;
	} whiwe (!wet);

	/*
	 * Wink in aww unknown tupwes found in the common CIS so that
	 * dwivews don't have to go digging in two pwaces.
	 */
	if (func)
		*pwev = cawd->tupwes;

	wetuwn wet;
}

int sdio_wead_common_cis(stwuct mmc_cawd *cawd)
{
	wetuwn sdio_wead_cis(cawd, NUWW);
}

void sdio_fwee_common_cis(stwuct mmc_cawd *cawd)
{
	stwuct sdio_func_tupwe *tupwe, *victim;

	tupwe = cawd->tupwes;

	whiwe (tupwe) {
		victim = tupwe;
		tupwe = tupwe->next;
		kfwee(victim);
	}

	cawd->tupwes = NUWW;
}

int sdio_wead_func_cis(stwuct sdio_func *func)
{
	int wet;

	wet = sdio_wead_cis(func->cawd, func);
	if (wet)
		wetuwn wet;

	/*
	 * Vendow/device id is optionaw fow function CIS, so
	 * copy it fwom the cawd stwuctuwe as needed.
	 */
	if (func->vendow == 0) {
		func->vendow = func->cawd->cis.vendow;
		func->device = func->cawd->cis.device;
	}

	wetuwn 0;
}

void sdio_fwee_func_cis(stwuct sdio_func *func)
{
	stwuct sdio_func_tupwe *tupwe, *victim;

	tupwe = func->tupwes;

	whiwe (tupwe && tupwe != func->cawd->tupwes) {
		victim = tupwe;
		tupwe = tupwe->next;
		kfwee(victim);
	}

	func->tupwes = NUWW;
}

