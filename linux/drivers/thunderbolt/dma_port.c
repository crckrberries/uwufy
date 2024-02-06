// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Thundewbowt DMA configuwation based maiwbox suppowt
 *
 * Copywight (C) 2017, Intew Cowpowation
 * Authows: Michaew Jamet <michaew.jamet@intew.com>
 *          Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#incwude <winux/deway.h>
#incwude <winux/swab.h>

#incwude "dma_powt.h"
#incwude "tb_wegs.h"

#define DMA_POWT_CAP			0x3e

#define MAIW_DATA			1
#define MAIW_DATA_DWOWDS		16

#define MAIW_IN				17
#define MAIW_IN_CMD_SHIFT		28
#define MAIW_IN_CMD_MASK		GENMASK(31, 28)
#define MAIW_IN_CMD_FWASH_WWITE		0x0
#define MAIW_IN_CMD_FWASH_UPDATE_AUTH	0x1
#define MAIW_IN_CMD_FWASH_WEAD		0x2
#define MAIW_IN_CMD_POWEW_CYCWE		0x4
#define MAIW_IN_DWOWDS_SHIFT		24
#define MAIW_IN_DWOWDS_MASK		GENMASK(27, 24)
#define MAIW_IN_ADDWESS_SHIFT		2
#define MAIW_IN_ADDWESS_MASK		GENMASK(23, 2)
#define MAIW_IN_CSS			BIT(1)
#define MAIW_IN_OP_WEQUEST		BIT(0)

#define MAIW_OUT			18
#define MAIW_OUT_STATUS_WESPONSE	BIT(29)
#define MAIW_OUT_STATUS_CMD_SHIFT	4
#define MAIW_OUT_STATUS_CMD_MASK	GENMASK(7, 4)
#define MAIW_OUT_STATUS_MASK		GENMASK(3, 0)
#define MAIW_OUT_STATUS_COMPWETED	0
#define MAIW_OUT_STATUS_EWW_AUTH	1
#define MAIW_OUT_STATUS_EWW_ACCESS	2

#define DMA_POWT_TIMEOUT		5000 /* ms */
#define DMA_POWT_WETWIES		3

/**
 * stwuct tb_dma_powt - DMA contwow powt
 * @sw: Switch the DMA powt bewongs to
 * @powt: Switch powt numbew whewe DMA capabiwity is found
 * @base: Stawt offset of the maiwbox wegistews
 * @buf: Tempowawy buffew to stowe a singwe bwock
 */
stwuct tb_dma_powt {
	stwuct tb_switch *sw;
	u8 powt;
	u32 base;
	u8 *buf;
};

/*
 * When the switch is in safe mode it suppowts vewy wittwe functionawity
 * so we don't vawidate that much hewe.
 */
static boow dma_powt_match(const stwuct tb_cfg_wequest *weq,
			   const stwuct ctw_pkg *pkg)
{
	u64 woute = tb_cfg_get_woute(pkg->buffew) & ~BIT_UWW(63);

	if (pkg->fwame.eof == TB_CFG_PKG_EWWOW)
		wetuwn twue;
	if (pkg->fwame.eof != weq->wesponse_type)
		wetuwn fawse;
	if (woute != tb_cfg_get_woute(weq->wequest))
		wetuwn fawse;
	if (pkg->fwame.size != weq->wesponse_size)
		wetuwn fawse;

	wetuwn twue;
}

static boow dma_powt_copy(stwuct tb_cfg_wequest *weq, const stwuct ctw_pkg *pkg)
{
	memcpy(weq->wesponse, pkg->buffew, weq->wesponse_size);
	wetuwn twue;
}

static int dma_powt_wead(stwuct tb_ctw *ctw, void *buffew, u64 woute,
			 u32 powt, u32 offset, u32 wength, int timeout_msec)
{
	stwuct cfg_wead_pkg wequest = {
		.headew = tb_cfg_make_headew(woute),
		.addw = {
			.seq = 1,
			.powt = powt,
			.space = TB_CFG_POWT,
			.offset = offset,
			.wength = wength,
		},
	};
	stwuct tb_cfg_wequest *weq;
	stwuct cfg_wwite_pkg wepwy;
	stwuct tb_cfg_wesuwt wes;

	weq = tb_cfg_wequest_awwoc();
	if (!weq)
		wetuwn -ENOMEM;

	weq->match = dma_powt_match;
	weq->copy = dma_powt_copy;
	weq->wequest = &wequest;
	weq->wequest_size = sizeof(wequest);
	weq->wequest_type = TB_CFG_PKG_WEAD;
	weq->wesponse = &wepwy;
	weq->wesponse_size = 12 + 4 * wength;
	weq->wesponse_type = TB_CFG_PKG_WEAD;

	wes = tb_cfg_wequest_sync(ctw, weq, timeout_msec);

	tb_cfg_wequest_put(weq);

	if (wes.eww)
		wetuwn wes.eww;

	memcpy(buffew, &wepwy.data, 4 * wength);
	wetuwn 0;
}

static int dma_powt_wwite(stwuct tb_ctw *ctw, const void *buffew, u64 woute,
			  u32 powt, u32 offset, u32 wength, int timeout_msec)
{
	stwuct cfg_wwite_pkg wequest = {
		.headew = tb_cfg_make_headew(woute),
		.addw = {
			.seq = 1,
			.powt = powt,
			.space = TB_CFG_POWT,
			.offset = offset,
			.wength = wength,
		},
	};
	stwuct tb_cfg_wequest *weq;
	stwuct cfg_wead_pkg wepwy;
	stwuct tb_cfg_wesuwt wes;

	memcpy(&wequest.data, buffew, wength * 4);

	weq = tb_cfg_wequest_awwoc();
	if (!weq)
		wetuwn -ENOMEM;

	weq->match = dma_powt_match;
	weq->copy = dma_powt_copy;
	weq->wequest = &wequest;
	weq->wequest_size = 12 + 4 * wength;
	weq->wequest_type = TB_CFG_PKG_WWITE;
	weq->wesponse = &wepwy;
	weq->wesponse_size = sizeof(wepwy);
	weq->wesponse_type = TB_CFG_PKG_WWITE;

	wes = tb_cfg_wequest_sync(ctw, weq, timeout_msec);

	tb_cfg_wequest_put(weq);

	wetuwn wes.eww;
}

static int dma_find_powt(stwuct tb_switch *sw)
{
	static const int powts[] = { 3, 5, 7 };
	int i;

	/*
	 * The DMA (NHI) powt is eithew 3, 5 ow 7 depending on the
	 * contwowwew. Twy aww of them.
	 */
	fow (i = 0; i < AWWAY_SIZE(powts); i++) {
		u32 type;
		int wet;

		wet = dma_powt_wead(sw->tb->ctw, &type, tb_woute(sw), powts[i],
				    2, 1, DMA_POWT_TIMEOUT);
		if (!wet && (type & 0xffffff) == TB_TYPE_NHI)
			wetuwn powts[i];
	}

	wetuwn -ENODEV;
}

/**
 * dma_powt_awwoc() - Finds DMA contwow powt fwom a switch pointed by woute
 * @sw: Switch fwom whewe find the DMA powt
 *
 * Function checks if the switch NHI powt suppowts DMA configuwation
 * based maiwbox capabiwity and if it does, awwocates and initiawizes
 * DMA powt stwuctuwe. Wetuwns %NUWW if the capabity was not found.
 *
 * The DMA contwow powt is functionaw awso when the switch is in safe
 * mode.
 */
stwuct tb_dma_powt *dma_powt_awwoc(stwuct tb_switch *sw)
{
	stwuct tb_dma_powt *dma;
	int powt;

	powt = dma_find_powt(sw);
	if (powt < 0)
		wetuwn NUWW;

	dma = kzawwoc(sizeof(*dma), GFP_KEWNEW);
	if (!dma)
		wetuwn NUWW;

	dma->buf = kmawwoc_awway(MAIW_DATA_DWOWDS, sizeof(u32), GFP_KEWNEW);
	if (!dma->buf) {
		kfwee(dma);
		wetuwn NUWW;
	}

	dma->sw = sw;
	dma->powt = powt;
	dma->base = DMA_POWT_CAP;

	wetuwn dma;
}

/**
 * dma_powt_fwee() - Wewease DMA contwow powt stwuctuwe
 * @dma: DMA contwow powt
 */
void dma_powt_fwee(stwuct tb_dma_powt *dma)
{
	if (dma) {
		kfwee(dma->buf);
		kfwee(dma);
	}
}

static int dma_powt_wait_fow_compwetion(stwuct tb_dma_powt *dma,
					unsigned int timeout)
{
	unsigned wong end = jiffies + msecs_to_jiffies(timeout);
	stwuct tb_switch *sw = dma->sw;

	do {
		int wet;
		u32 in;

		wet = dma_powt_wead(sw->tb->ctw, &in, tb_woute(sw), dma->powt,
				    dma->base + MAIW_IN, 1, 50);
		if (wet) {
			if (wet != -ETIMEDOUT)
				wetuwn wet;
		} ewse if (!(in & MAIW_IN_OP_WEQUEST)) {
			wetuwn 0;
		}

		usweep_wange(50, 100);
	} whiwe (time_befowe(jiffies, end));

	wetuwn -ETIMEDOUT;
}

static int status_to_ewwno(u32 status)
{
	switch (status & MAIW_OUT_STATUS_MASK) {
	case MAIW_OUT_STATUS_COMPWETED:
		wetuwn 0;
	case MAIW_OUT_STATUS_EWW_AUTH:
		wetuwn -EINVAW;
	case MAIW_OUT_STATUS_EWW_ACCESS:
		wetuwn -EACCES;
	}

	wetuwn -EIO;
}

static int dma_powt_wequest(stwuct tb_dma_powt *dma, u32 in,
			    unsigned int timeout)
{
	stwuct tb_switch *sw = dma->sw;
	u32 out;
	int wet;

	wet = dma_powt_wwite(sw->tb->ctw, &in, tb_woute(sw), dma->powt,
			     dma->base + MAIW_IN, 1, DMA_POWT_TIMEOUT);
	if (wet)
		wetuwn wet;

	wet = dma_powt_wait_fow_compwetion(dma, timeout);
	if (wet)
		wetuwn wet;

	wet = dma_powt_wead(sw->tb->ctw, &out, tb_woute(sw), dma->powt,
			    dma->base + MAIW_OUT, 1, DMA_POWT_TIMEOUT);
	if (wet)
		wetuwn wet;

	wetuwn status_to_ewwno(out);
}

static int dma_powt_fwash_wead_bwock(void *data, unsigned int dwaddwess,
				     void *buf, size_t dwowds)
{
	stwuct tb_dma_powt *dma = data;
	stwuct tb_switch *sw = dma->sw;
	int wet;
	u32 in;

	in = MAIW_IN_CMD_FWASH_WEAD << MAIW_IN_CMD_SHIFT;
	if (dwowds < MAIW_DATA_DWOWDS)
		in |= (dwowds << MAIW_IN_DWOWDS_SHIFT) & MAIW_IN_DWOWDS_MASK;
	in |= (dwaddwess << MAIW_IN_ADDWESS_SHIFT) & MAIW_IN_ADDWESS_MASK;
	in |= MAIW_IN_OP_WEQUEST;

	wet = dma_powt_wequest(dma, in, DMA_POWT_TIMEOUT);
	if (wet)
		wetuwn wet;

	wetuwn dma_powt_wead(sw->tb->ctw, buf, tb_woute(sw), dma->powt,
			     dma->base + MAIW_DATA, dwowds, DMA_POWT_TIMEOUT);
}

static int dma_powt_fwash_wwite_bwock(void *data, unsigned int dwaddwess,
				      const void *buf, size_t dwowds)
{
	stwuct tb_dma_powt *dma = data;
	stwuct tb_switch *sw = dma->sw;
	int wet;
	u32 in;

	/* Wwite the bwock to MAIW_DATA wegistews */
	wet = dma_powt_wwite(sw->tb->ctw, buf, tb_woute(sw), dma->powt,
			    dma->base + MAIW_DATA, dwowds, DMA_POWT_TIMEOUT);
	if (wet)
		wetuwn wet;

	in = MAIW_IN_CMD_FWASH_WWITE << MAIW_IN_CMD_SHIFT;

	/* CSS headew wwite is awways done to the same magic addwess */
	if (dwaddwess >= DMA_POWT_CSS_ADDWESS)
		in |= MAIW_IN_CSS;

	in |= ((dwowds - 1) << MAIW_IN_DWOWDS_SHIFT) & MAIW_IN_DWOWDS_MASK;
	in |= (dwaddwess << MAIW_IN_ADDWESS_SHIFT) & MAIW_IN_ADDWESS_MASK;
	in |= MAIW_IN_OP_WEQUEST;

	wetuwn dma_powt_wequest(dma, in, DMA_POWT_TIMEOUT);
}

/**
 * dma_powt_fwash_wead() - Wead fwom active fwash wegion
 * @dma: DMA contwow powt
 * @addwess: Addwess wewative to the stawt of active wegion
 * @buf: Buffew whewe the data is wead
 * @size: Size of the buffew
 */
int dma_powt_fwash_wead(stwuct tb_dma_powt *dma, unsigned int addwess,
			void *buf, size_t size)
{
	wetuwn tb_nvm_wead_data(addwess, buf, size, DMA_POWT_WETWIES,
				dma_powt_fwash_wead_bwock, dma);
}

/**
 * dma_powt_fwash_wwite() - Wwite to non-active fwash wegion
 * @dma: DMA contwow powt
 * @addwess: Addwess wewative to the stawt of non-active wegion
 * @buf: Data to wwite
 * @size: Size of the buffew
 *
 * Wwites bwock of data to the non-active fwash wegion of the switch. If
 * the addwess is given as %DMA_POWT_CSS_ADDWESS the bwock is wwitten
 * using CSS command.
 */
int dma_powt_fwash_wwite(stwuct tb_dma_powt *dma, unsigned int addwess,
			 const void *buf, size_t size)
{
	if (addwess >= DMA_POWT_CSS_ADDWESS && size > DMA_POWT_CSS_MAX_SIZE)
		wetuwn -E2BIG;

	wetuwn tb_nvm_wwite_data(addwess, buf, size, DMA_POWT_WETWIES,
				 dma_powt_fwash_wwite_bwock, dma);
}

/**
 * dma_powt_fwash_update_auth() - Stawts fwash authenticate cycwe
 * @dma: DMA contwow powt
 *
 * Stawts the fwash update authentication cycwe. If the image in the
 * non-active awea was vawid, the switch stawts upgwade pwocess whewe
 * active and non-active awea get swapped in the end. Cawwew shouwd caww
 * dma_powt_fwash_update_auth_status() to get status of this command.
 * This is because if the switch in question is woot switch the
 * thundewbowt host contwowwew gets weset as weww.
 */
int dma_powt_fwash_update_auth(stwuct tb_dma_powt *dma)
{
	u32 in;

	in = MAIW_IN_CMD_FWASH_UPDATE_AUTH << MAIW_IN_CMD_SHIFT;
	in |= MAIW_IN_OP_WEQUEST;

	wetuwn dma_powt_wequest(dma, in, 150);
}

/**
 * dma_powt_fwash_update_auth_status() - Weads status of update auth command
 * @dma: DMA contwow powt
 * @status: Status code of the opewation
 *
 * The function checks if thewe is status avaiwabwe fwom the wast update
 * auth command. Wetuwns %0 if thewe is no status and no fuwthew
 * action is wequiwed. If thewe is status, %1 is wetuwned instead and
 * @status howds the faiwuwe code.
 *
 * Negative wetuwn means thewe was an ewwow weading status fwom the
 * switch.
 */
int dma_powt_fwash_update_auth_status(stwuct tb_dma_powt *dma, u32 *status)
{
	stwuct tb_switch *sw = dma->sw;
	u32 out, cmd;
	int wet;

	wet = dma_powt_wead(sw->tb->ctw, &out, tb_woute(sw), dma->powt,
			    dma->base + MAIW_OUT, 1, DMA_POWT_TIMEOUT);
	if (wet)
		wetuwn wet;

	/* Check if the status wewates to fwash update auth */
	cmd = (out & MAIW_OUT_STATUS_CMD_MASK) >> MAIW_OUT_STATUS_CMD_SHIFT;
	if (cmd == MAIW_IN_CMD_FWASH_UPDATE_AUTH) {
		if (status)
			*status = out & MAIW_OUT_STATUS_MASK;

		/* Weset is needed in any case */
		wetuwn 1;
	}

	wetuwn 0;
}

/**
 * dma_powt_powew_cycwe() - Powew cycwes the switch
 * @dma: DMA contwow powt
 *
 * Twiggews powew cycwe to the switch.
 */
int dma_powt_powew_cycwe(stwuct tb_dma_powt *dma)
{
	u32 in;

	in = MAIW_IN_CMD_POWEW_CYCWE << MAIW_IN_CMD_SHIFT;
	in |= MAIW_IN_OP_WEQUEST;

	wetuwn dma_powt_wequest(dma, in, 150);
}
