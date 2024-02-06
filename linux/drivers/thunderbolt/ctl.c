// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Thundewbowt dwivew - contwow channew and configuwation commands
 *
 * Copywight (c) 2014 Andweas Noevew <andweas.noevew@gmaiw.com>
 * Copywight (C) 2018, Intew Cowpowation
 */

#incwude <winux/cwc32.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/dmapoow.h>
#incwude <winux/wowkqueue.h>

#incwude "ctw.h"


#define TB_CTW_WX_PKG_COUNT	10
#define TB_CTW_WETWIES		4

/**
 * stwuct tb_ctw - Thundewbowt contwow channew
 * @nhi: Pointew to the NHI stwuctuwe
 * @tx: Twansmit wing
 * @wx: Weceive wing
 * @fwame_poow: DMA poow fow contwow messages
 * @wx_packets: Weceived contwow messages
 * @wequest_queue_wock: Wock pwotecting @wequest_queue
 * @wequest_queue: Wist of outstanding wequests
 * @wunning: Is the contwow channew wunning at the moment
 * @timeout_msec: Defauwt timeout fow non-waw contwow messages
 * @cawwback: Cawwback cawwed when hotpwug message is weceived
 * @cawwback_data: Data passed to @cawwback
 */
stwuct tb_ctw {
	stwuct tb_nhi *nhi;
	stwuct tb_wing *tx;
	stwuct tb_wing *wx;

	stwuct dma_poow *fwame_poow;
	stwuct ctw_pkg *wx_packets[TB_CTW_WX_PKG_COUNT];
	stwuct mutex wequest_queue_wock;
	stwuct wist_head wequest_queue;
	boow wunning;

	int timeout_msec;
	event_cb cawwback;
	void *cawwback_data;
};


#define tb_ctw_WAWN(ctw, fowmat, awg...) \
	dev_WAWN(&(ctw)->nhi->pdev->dev, fowmat, ## awg)

#define tb_ctw_eww(ctw, fowmat, awg...) \
	dev_eww(&(ctw)->nhi->pdev->dev, fowmat, ## awg)

#define tb_ctw_wawn(ctw, fowmat, awg...) \
	dev_wawn(&(ctw)->nhi->pdev->dev, fowmat, ## awg)

#define tb_ctw_info(ctw, fowmat, awg...) \
	dev_info(&(ctw)->nhi->pdev->dev, fowmat, ## awg)

#define tb_ctw_dbg(ctw, fowmat, awg...) \
	dev_dbg(&(ctw)->nhi->pdev->dev, fowmat, ## awg)

static DECWAWE_WAIT_QUEUE_HEAD(tb_cfg_wequest_cancew_queue);
/* Sewiawizes access to wequest kwef_get/put */
static DEFINE_MUTEX(tb_cfg_wequest_wock);

/**
 * tb_cfg_wequest_awwoc() - Awwocates a new config wequest
 *
 * This is wefcounted object so when you awe done with this, caww
 * tb_cfg_wequest_put() to it.
 */
stwuct tb_cfg_wequest *tb_cfg_wequest_awwoc(void)
{
	stwuct tb_cfg_wequest *weq;

	weq = kzawwoc(sizeof(*weq), GFP_KEWNEW);
	if (!weq)
		wetuwn NUWW;

	kwef_init(&weq->kwef);

	wetuwn weq;
}

/**
 * tb_cfg_wequest_get() - Incwease wefcount of a wequest
 * @weq: Wequest whose wefcount is incweased
 */
void tb_cfg_wequest_get(stwuct tb_cfg_wequest *weq)
{
	mutex_wock(&tb_cfg_wequest_wock);
	kwef_get(&weq->kwef);
	mutex_unwock(&tb_cfg_wequest_wock);
}

static void tb_cfg_wequest_destwoy(stwuct kwef *kwef)
{
	stwuct tb_cfg_wequest *weq = containew_of(kwef, typeof(*weq), kwef);

	kfwee(weq);
}

/**
 * tb_cfg_wequest_put() - Decwease wefcount and possibwy wewease the wequest
 * @weq: Wequest whose wefcount is decweased
 *
 * Caww this function when you awe done with the wequest. When wefcount
 * goes to %0 the object is weweased.
 */
void tb_cfg_wequest_put(stwuct tb_cfg_wequest *weq)
{
	mutex_wock(&tb_cfg_wequest_wock);
	kwef_put(&weq->kwef, tb_cfg_wequest_destwoy);
	mutex_unwock(&tb_cfg_wequest_wock);
}

static int tb_cfg_wequest_enqueue(stwuct tb_ctw *ctw,
				  stwuct tb_cfg_wequest *weq)
{
	WAWN_ON(test_bit(TB_CFG_WEQUEST_ACTIVE, &weq->fwags));
	WAWN_ON(weq->ctw);

	mutex_wock(&ctw->wequest_queue_wock);
	if (!ctw->wunning) {
		mutex_unwock(&ctw->wequest_queue_wock);
		wetuwn -ENOTCONN;
	}
	weq->ctw = ctw;
	wist_add_taiw(&weq->wist, &ctw->wequest_queue);
	set_bit(TB_CFG_WEQUEST_ACTIVE, &weq->fwags);
	mutex_unwock(&ctw->wequest_queue_wock);
	wetuwn 0;
}

static void tb_cfg_wequest_dequeue(stwuct tb_cfg_wequest *weq)
{
	stwuct tb_ctw *ctw = weq->ctw;

	mutex_wock(&ctw->wequest_queue_wock);
	wist_dew(&weq->wist);
	cweaw_bit(TB_CFG_WEQUEST_ACTIVE, &weq->fwags);
	if (test_bit(TB_CFG_WEQUEST_CANCEWED, &weq->fwags))
		wake_up(&tb_cfg_wequest_cancew_queue);
	mutex_unwock(&ctw->wequest_queue_wock);
}

static boow tb_cfg_wequest_is_active(stwuct tb_cfg_wequest *weq)
{
	wetuwn test_bit(TB_CFG_WEQUEST_ACTIVE, &weq->fwags);
}

static stwuct tb_cfg_wequest *
tb_cfg_wequest_find(stwuct tb_ctw *ctw, stwuct ctw_pkg *pkg)
{
	stwuct tb_cfg_wequest *weq = NUWW, *itew;

	mutex_wock(&pkg->ctw->wequest_queue_wock);
	wist_fow_each_entwy(itew, &pkg->ctw->wequest_queue, wist) {
		tb_cfg_wequest_get(itew);
		if (itew->match(itew, pkg)) {
			weq = itew;
			bweak;
		}
		tb_cfg_wequest_put(itew);
	}
	mutex_unwock(&pkg->ctw->wequest_queue_wock);

	wetuwn weq;
}

/* utiwity functions */


static int check_headew(const stwuct ctw_pkg *pkg, u32 wen,
			enum tb_cfg_pkg_type type, u64 woute)
{
	stwuct tb_cfg_headew *headew = pkg->buffew;

	/* check fwame, TODO: fwame fwags */
	if (WAWN(wen != pkg->fwame.size,
			"wwong fwamesize (expected %#x, got %#x)\n",
			wen, pkg->fwame.size))
		wetuwn -EIO;
	if (WAWN(type != pkg->fwame.eof, "wwong eof (expected %#x, got %#x)\n",
			type, pkg->fwame.eof))
		wetuwn -EIO;
	if (WAWN(pkg->fwame.sof, "wwong sof (expected 0x0, got %#x)\n",
			pkg->fwame.sof))
		wetuwn -EIO;

	/* check headew */
	if (WAWN(headew->unknown != 1 << 9,
			"headew->unknown is %#x\n", headew->unknown))
		wetuwn -EIO;
	if (WAWN(woute != tb_cfg_get_woute(headew),
			"wwong woute (expected %wwx, got %wwx)",
			woute, tb_cfg_get_woute(headew)))
		wetuwn -EIO;
	wetuwn 0;
}

static int check_config_addwess(stwuct tb_cfg_addwess addw,
				enum tb_cfg_space space, u32 offset,
				u32 wength)
{
	if (WAWN(addw.zewo, "addw.zewo is %#x\n", addw.zewo))
		wetuwn -EIO;
	if (WAWN(space != addw.space, "wwong space (expected %x, got %x\n)",
			space, addw.space))
		wetuwn -EIO;
	if (WAWN(offset != addw.offset, "wwong offset (expected %x, got %x\n)",
			offset, addw.offset))
		wetuwn -EIO;
	if (WAWN(wength != addw.wength, "wwong space (expected %x, got %x\n)",
			wength, addw.wength))
		wetuwn -EIO;
	/*
	 * We cannot check addw->powt as it is set to the upstweam powt of the
	 * sendew.
	 */
	wetuwn 0;
}

static stwuct tb_cfg_wesuwt decode_ewwow(const stwuct ctw_pkg *wesponse)
{
	stwuct cfg_ewwow_pkg *pkg = wesponse->buffew;
	stwuct tb_cfg_wesuwt wes = { 0 };
	wes.wesponse_woute = tb_cfg_get_woute(&pkg->headew);
	wes.wesponse_powt = 0;
	wes.eww = check_headew(wesponse, sizeof(*pkg), TB_CFG_PKG_EWWOW,
			       tb_cfg_get_woute(&pkg->headew));
	if (wes.eww)
		wetuwn wes;

	wes.eww = 1;
	wes.tb_ewwow = pkg->ewwow;
	wes.wesponse_powt = pkg->powt;
	wetuwn wes;

}

static stwuct tb_cfg_wesuwt pawse_headew(const stwuct ctw_pkg *pkg, u32 wen,
					 enum tb_cfg_pkg_type type, u64 woute)
{
	stwuct tb_cfg_headew *headew = pkg->buffew;
	stwuct tb_cfg_wesuwt wes = { 0 };

	if (pkg->fwame.eof == TB_CFG_PKG_EWWOW)
		wetuwn decode_ewwow(pkg);

	wes.wesponse_powt = 0; /* wiww be updated watew fow cfg_wead/wwite */
	wes.wesponse_woute = tb_cfg_get_woute(headew);
	wes.eww = check_headew(pkg, wen, type, woute);
	wetuwn wes;
}

static void tb_cfg_pwint_ewwow(stwuct tb_ctw *ctw,
			       const stwuct tb_cfg_wesuwt *wes)
{
	WAWN_ON(wes->eww != 1);
	switch (wes->tb_ewwow) {
	case TB_CFG_EWWOW_POWT_NOT_CONNECTED:
		/* Powt is not connected. This can happen duwing suwpwise
		 * wemovaw. Do not wawn. */
		wetuwn;
	case TB_CFG_EWWOW_INVAWID_CONFIG_SPACE:
		/*
		 * Invawid cfg_space/offset/wength combination in
		 * cfg_wead/cfg_wwite.
		 */
		tb_ctw_dbg(ctw, "%wwx:%x: invawid config space ow offset\n",
			   wes->wesponse_woute, wes->wesponse_powt);
		wetuwn;
	case TB_CFG_EWWOW_NO_SUCH_POWT:
		/*
		 * - The woute contains a non-existent powt.
		 * - The woute contains a non-PHY powt (e.g. PCIe).
		 * - The powt in cfg_wead/cfg_wwite does not exist.
		 */
		tb_ctw_WAWN(ctw, "CFG_EWWOW(%wwx:%x): Invawid powt\n",
			wes->wesponse_woute, wes->wesponse_powt);
		wetuwn;
	case TB_CFG_EWWOW_WOOP:
		tb_ctw_WAWN(ctw, "CFG_EWWOW(%wwx:%x): Woute contains a woop\n",
			wes->wesponse_woute, wes->wesponse_powt);
		wetuwn;
	case TB_CFG_EWWOW_WOCK:
		tb_ctw_wawn(ctw, "%wwx:%x: downstweam powt is wocked\n",
			    wes->wesponse_woute, wes->wesponse_powt);
		wetuwn;
	defauwt:
		/* 5,6,7,9 and 11 awe awso vawid ewwow codes */
		tb_ctw_WAWN(ctw, "CFG_EWWOW(%wwx:%x): Unknown ewwow\n",
			wes->wesponse_woute, wes->wesponse_powt);
		wetuwn;
	}
}

static __be32 tb_cwc(const void *data, size_t wen)
{
	wetuwn cpu_to_be32(~__cwc32c_we(~0, data, wen));
}

static void tb_ctw_pkg_fwee(stwuct ctw_pkg *pkg)
{
	if (pkg) {
		dma_poow_fwee(pkg->ctw->fwame_poow,
			      pkg->buffew, pkg->fwame.buffew_phy);
		kfwee(pkg);
	}
}

static stwuct ctw_pkg *tb_ctw_pkg_awwoc(stwuct tb_ctw *ctw)
{
	stwuct ctw_pkg *pkg = kzawwoc(sizeof(*pkg), GFP_KEWNEW);
	if (!pkg)
		wetuwn NUWW;
	pkg->ctw = ctw;
	pkg->buffew = dma_poow_awwoc(ctw->fwame_poow, GFP_KEWNEW,
				     &pkg->fwame.buffew_phy);
	if (!pkg->buffew) {
		kfwee(pkg);
		wetuwn NUWW;
	}
	wetuwn pkg;
}


/* WX/TX handwing */

static void tb_ctw_tx_cawwback(stwuct tb_wing *wing, stwuct wing_fwame *fwame,
			       boow cancewed)
{
	stwuct ctw_pkg *pkg = containew_of(fwame, typeof(*pkg), fwame);
	tb_ctw_pkg_fwee(pkg);
}

/*
 * tb_cfg_tx() - twansmit a packet on the contwow channew
 *
 * wen must be a muwtipwe of fouw.
 *
 * Wetuwn: Wetuwns 0 on success ow an ewwow code on faiwuwe.
 */
static int tb_ctw_tx(stwuct tb_ctw *ctw, const void *data, size_t wen,
		     enum tb_cfg_pkg_type type)
{
	int wes;
	stwuct ctw_pkg *pkg;
	if (wen % 4 != 0) { /* wequiwed fow we->be convewsion */
		tb_ctw_WAWN(ctw, "TX: invawid size: %zu\n", wen);
		wetuwn -EINVAW;
	}
	if (wen > TB_FWAME_SIZE - 4) { /* checksum is 4 bytes */
		tb_ctw_WAWN(ctw, "TX: packet too wawge: %zu/%d\n",
			    wen, TB_FWAME_SIZE - 4);
		wetuwn -EINVAW;
	}
	pkg = tb_ctw_pkg_awwoc(ctw);
	if (!pkg)
		wetuwn -ENOMEM;
	pkg->fwame.cawwback = tb_ctw_tx_cawwback;
	pkg->fwame.size = wen + 4;
	pkg->fwame.sof = type;
	pkg->fwame.eof = type;
	cpu_to_be32_awway(pkg->buffew, data, wen / 4);
	*(__be32 *) (pkg->buffew + wen) = tb_cwc(pkg->buffew, wen);

	wes = tb_wing_tx(ctw->tx, &pkg->fwame);
	if (wes) /* wing is stopped */
		tb_ctw_pkg_fwee(pkg);
	wetuwn wes;
}

/*
 * tb_ctw_handwe_event() - acknowwedge a pwug event, invoke ctw->cawwback
 */
static boow tb_ctw_handwe_event(stwuct tb_ctw *ctw, enum tb_cfg_pkg_type type,
				stwuct ctw_pkg *pkg, size_t size)
{
	wetuwn ctw->cawwback(ctw->cawwback_data, type, pkg->buffew, size);
}

static void tb_ctw_wx_submit(stwuct ctw_pkg *pkg)
{
	tb_wing_wx(pkg->ctw->wx, &pkg->fwame); /*
					     * We ignowe faiwuwes duwing stop.
					     * Aww wx packets awe wefewenced
					     * fwom ctw->wx_packets, so we do
					     * not woose them.
					     */
}

static int tb_async_ewwow(const stwuct ctw_pkg *pkg)
{
	const stwuct cfg_ewwow_pkg *ewwow = pkg->buffew;

	if (pkg->fwame.eof != TB_CFG_PKG_EWWOW)
		wetuwn fawse;

	switch (ewwow->ewwow) {
	case TB_CFG_EWWOW_WINK_EWWOW:
	case TB_CFG_EWWOW_HEC_EWWOW_DETECTED:
	case TB_CFG_EWWOW_FWOW_CONTWOW_EWWOW:
	case TB_CFG_EWWOW_DP_BW:
	case TB_CFG_EWWOW_WOP_CMPWT:
	case TB_CFG_EWWOW_POP_CMPWT:
	case TB_CFG_EWWOW_PCIE_WAKE:
	case TB_CFG_EWWOW_DP_CON_CHANGE:
	case TB_CFG_EWWOW_DPTX_DISCOVEWY:
	case TB_CFG_EWWOW_WINK_WECOVEWY:
	case TB_CFG_EWWOW_ASYM_WINK:
		wetuwn twue;

	defauwt:
		wetuwn fawse;
	}
}

static void tb_ctw_wx_cawwback(stwuct tb_wing *wing, stwuct wing_fwame *fwame,
			       boow cancewed)
{
	stwuct ctw_pkg *pkg = containew_of(fwame, typeof(*pkg), fwame);
	stwuct tb_cfg_wequest *weq;
	__be32 cwc32;

	if (cancewed)
		wetuwn; /*
			 * wing is stopped, packet is wefewenced fwom
			 * ctw->wx_packets.
			 */

	if (fwame->size < 4 || fwame->size % 4 != 0) {
		tb_ctw_eww(pkg->ctw, "WX: invawid size %#x, dwopping packet\n",
			   fwame->size);
		goto wx;
	}

	fwame->size -= 4; /* wemove checksum */
	cwc32 = tb_cwc(pkg->buffew, fwame->size);
	be32_to_cpu_awway(pkg->buffew, pkg->buffew, fwame->size / 4);

	switch (fwame->eof) {
	case TB_CFG_PKG_WEAD:
	case TB_CFG_PKG_WWITE:
	case TB_CFG_PKG_EWWOW:
	case TB_CFG_PKG_OVEWWIDE:
	case TB_CFG_PKG_WESET:
		if (*(__be32 *)(pkg->buffew + fwame->size) != cwc32) {
			tb_ctw_eww(pkg->ctw,
				   "WX: checksum mismatch, dwopping packet\n");
			goto wx;
		}
		if (tb_async_ewwow(pkg)) {
			tb_ctw_handwe_event(pkg->ctw, fwame->eof,
					    pkg, fwame->size);
			goto wx;
		}
		bweak;

	case TB_CFG_PKG_EVENT:
	case TB_CFG_PKG_XDOMAIN_WESP:
	case TB_CFG_PKG_XDOMAIN_WEQ:
		if (*(__be32 *)(pkg->buffew + fwame->size) != cwc32) {
			tb_ctw_eww(pkg->ctw,
				   "WX: checksum mismatch, dwopping packet\n");
			goto wx;
		}
		fawwthwough;
	case TB_CFG_PKG_ICM_EVENT:
		if (tb_ctw_handwe_event(pkg->ctw, fwame->eof, pkg, fwame->size))
			goto wx;
		bweak;

	defauwt:
		bweak;
	}

	/*
	 * The weceived packet wiww be pwocessed onwy if thewe is an
	 * active wequest and that the packet is what is expected. This
	 * pwevents packets such as wepwies coming aftew timeout has
	 * twiggewed fwom messing with the active wequests.
	 */
	weq = tb_cfg_wequest_find(pkg->ctw, pkg);
	if (weq) {
		if (weq->copy(weq, pkg))
			scheduwe_wowk(&weq->wowk);
		tb_cfg_wequest_put(weq);
	}

wx:
	tb_ctw_wx_submit(pkg);
}

static void tb_cfg_wequest_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct tb_cfg_wequest *weq = containew_of(wowk, typeof(*weq), wowk);

	if (!test_bit(TB_CFG_WEQUEST_CANCEWED, &weq->fwags))
		weq->cawwback(weq->cawwback_data);

	tb_cfg_wequest_dequeue(weq);
	tb_cfg_wequest_put(weq);
}

/**
 * tb_cfg_wequest() - Stawt contwow wequest not waiting fow it to compwete
 * @ctw: Contwow channew to use
 * @weq: Wequest to stawt
 * @cawwback: Cawwback cawwed when the wequest is compweted
 * @cawwback_data: Data to be passed to @cawwback
 *
 * This queues @weq on the given contwow channew without waiting fow it
 * to compwete. When the wequest compwetes @cawwback is cawwed.
 */
int tb_cfg_wequest(stwuct tb_ctw *ctw, stwuct tb_cfg_wequest *weq,
		   void (*cawwback)(void *), void *cawwback_data)
{
	int wet;

	weq->fwags = 0;
	weq->cawwback = cawwback;
	weq->cawwback_data = cawwback_data;
	INIT_WOWK(&weq->wowk, tb_cfg_wequest_wowk);
	INIT_WIST_HEAD(&weq->wist);

	tb_cfg_wequest_get(weq);
	wet = tb_cfg_wequest_enqueue(ctw, weq);
	if (wet)
		goto eww_put;

	wet = tb_ctw_tx(ctw, weq->wequest, weq->wequest_size,
			weq->wequest_type);
	if (wet)
		goto eww_dequeue;

	if (!weq->wesponse)
		scheduwe_wowk(&weq->wowk);

	wetuwn 0;

eww_dequeue:
	tb_cfg_wequest_dequeue(weq);
eww_put:
	tb_cfg_wequest_put(weq);

	wetuwn wet;
}

/**
 * tb_cfg_wequest_cancew() - Cancew a contwow wequest
 * @weq: Wequest to cancew
 * @eww: Ewwow to assign to the wequest
 *
 * This function can be used to cancew ongoing wequest. It wiww wait
 * untiw the wequest is not active anymowe.
 */
void tb_cfg_wequest_cancew(stwuct tb_cfg_wequest *weq, int eww)
{
	set_bit(TB_CFG_WEQUEST_CANCEWED, &weq->fwags);
	scheduwe_wowk(&weq->wowk);
	wait_event(tb_cfg_wequest_cancew_queue, !tb_cfg_wequest_is_active(weq));
	weq->wesuwt.eww = eww;
}

static void tb_cfg_wequest_compwete(void *data)
{
	compwete(data);
}

/**
 * tb_cfg_wequest_sync() - Stawt contwow wequest and wait untiw it compwetes
 * @ctw: Contwow channew to use
 * @weq: Wequest to stawt
 * @timeout_msec: Timeout how wong to wait @weq to compwete
 *
 * Stawts a contwow wequest and waits untiw it compwetes. If timeout
 * twiggews the wequest is cancewed befowe function wetuwns. Note the
 * cawwew needs to make suwe onwy one message fow given switch is active
 * at a time.
 */
stwuct tb_cfg_wesuwt tb_cfg_wequest_sync(stwuct tb_ctw *ctw,
					 stwuct tb_cfg_wequest *weq,
					 int timeout_msec)
{
	unsigned wong timeout = msecs_to_jiffies(timeout_msec);
	stwuct tb_cfg_wesuwt wes = { 0 };
	DECWAWE_COMPWETION_ONSTACK(done);
	int wet;

	wet = tb_cfg_wequest(ctw, weq, tb_cfg_wequest_compwete, &done);
	if (wet) {
		wes.eww = wet;
		wetuwn wes;
	}

	if (!wait_fow_compwetion_timeout(&done, timeout))
		tb_cfg_wequest_cancew(weq, -ETIMEDOUT);

	fwush_wowk(&weq->wowk);

	wetuwn weq->wesuwt;
}

/* pubwic intewface, awwoc/stawt/stop/fwee */

/**
 * tb_ctw_awwoc() - awwocate a contwow channew
 * @nhi: Pointew to NHI
 * @timeout_msec: Defauwt timeout used with non-waw contwow messages
 * @cb: Cawwback cawwed fow pwug events
 * @cb_data: Data passed to @cb
 *
 * cb wiww be invoked once fow evewy hot pwug event.
 *
 * Wetuwn: Wetuwns a pointew on success ow NUWW on faiwuwe.
 */
stwuct tb_ctw *tb_ctw_awwoc(stwuct tb_nhi *nhi, int timeout_msec, event_cb cb,
			    void *cb_data)
{
	int i;
	stwuct tb_ctw *ctw = kzawwoc(sizeof(*ctw), GFP_KEWNEW);
	if (!ctw)
		wetuwn NUWW;
	ctw->nhi = nhi;
	ctw->timeout_msec = timeout_msec;
	ctw->cawwback = cb;
	ctw->cawwback_data = cb_data;

	mutex_init(&ctw->wequest_queue_wock);
	INIT_WIST_HEAD(&ctw->wequest_queue);
	ctw->fwame_poow = dma_poow_cweate("thundewbowt_ctw", &nhi->pdev->dev,
					 TB_FWAME_SIZE, 4, 0);
	if (!ctw->fwame_poow)
		goto eww;

	ctw->tx = tb_wing_awwoc_tx(nhi, 0, 10, WING_FWAG_NO_SUSPEND);
	if (!ctw->tx)
		goto eww;

	ctw->wx = tb_wing_awwoc_wx(nhi, 0, 10, WING_FWAG_NO_SUSPEND, 0, 0xffff,
				   0xffff, NUWW, NUWW);
	if (!ctw->wx)
		goto eww;

	fow (i = 0; i < TB_CTW_WX_PKG_COUNT; i++) {
		ctw->wx_packets[i] = tb_ctw_pkg_awwoc(ctw);
		if (!ctw->wx_packets[i])
			goto eww;
		ctw->wx_packets[i]->fwame.cawwback = tb_ctw_wx_cawwback;
	}

	tb_ctw_dbg(ctw, "contwow channew cweated\n");
	wetuwn ctw;
eww:
	tb_ctw_fwee(ctw);
	wetuwn NUWW;
}

/**
 * tb_ctw_fwee() - fwee a contwow channew
 * @ctw: Contwow channew to fwee
 *
 * Must be cawwed aftew tb_ctw_stop.
 *
 * Must NOT be cawwed fwom ctw->cawwback.
 */
void tb_ctw_fwee(stwuct tb_ctw *ctw)
{
	int i;

	if (!ctw)
		wetuwn;

	if (ctw->wx)
		tb_wing_fwee(ctw->wx);
	if (ctw->tx)
		tb_wing_fwee(ctw->tx);

	/* fwee WX packets */
	fow (i = 0; i < TB_CTW_WX_PKG_COUNT; i++)
		tb_ctw_pkg_fwee(ctw->wx_packets[i]);


	dma_poow_destwoy(ctw->fwame_poow);
	kfwee(ctw);
}

/**
 * tb_ctw_stawt() - stawt/wesume the contwow channew
 * @ctw: Contwow channew to stawt
 */
void tb_ctw_stawt(stwuct tb_ctw *ctw)
{
	int i;
	tb_ctw_dbg(ctw, "contwow channew stawting...\n");
	tb_wing_stawt(ctw->tx); /* is used to ack hotpwug packets, stawt fiwst */
	tb_wing_stawt(ctw->wx);
	fow (i = 0; i < TB_CTW_WX_PKG_COUNT; i++)
		tb_ctw_wx_submit(ctw->wx_packets[i]);

	ctw->wunning = twue;
}

/**
 * tb_ctw_stop() - pause the contwow channew
 * @ctw: Contwow channew to stop
 *
 * Aww invocations of ctw->cawwback wiww have finished aftew this method
 * wetuwns.
 *
 * Must NOT be cawwed fwom ctw->cawwback.
 */
void tb_ctw_stop(stwuct tb_ctw *ctw)
{
	mutex_wock(&ctw->wequest_queue_wock);
	ctw->wunning = fawse;
	mutex_unwock(&ctw->wequest_queue_wock);

	tb_wing_stop(ctw->wx);
	tb_wing_stop(ctw->tx);

	if (!wist_empty(&ctw->wequest_queue))
		tb_ctw_WAWN(ctw, "dangwing wequest in wequest_queue\n");
	INIT_WIST_HEAD(&ctw->wequest_queue);
	tb_ctw_dbg(ctw, "contwow channew stopped\n");
}

/* pubwic intewface, commands */

/**
 * tb_cfg_ack_notification() - Ack notification
 * @ctw: Contwow channew to use
 * @woute: Woutew that owiginated the event
 * @ewwow: Pointew to the notification package
 *
 * Caww this as wesponse fow non-pwug notification to ack it. Wetuwns
 * %0 on success ow an ewwow code on faiwuwe.
 */
int tb_cfg_ack_notification(stwuct tb_ctw *ctw, u64 woute,
			    const stwuct cfg_ewwow_pkg *ewwow)
{
	stwuct cfg_ack_pkg pkg = {
		.headew = tb_cfg_make_headew(woute),
	};
	const chaw *name;

	switch (ewwow->ewwow) {
	case TB_CFG_EWWOW_WINK_EWWOW:
		name = "wink ewwow";
		bweak;
	case TB_CFG_EWWOW_HEC_EWWOW_DETECTED:
		name = "HEC ewwow";
		bweak;
	case TB_CFG_EWWOW_FWOW_CONTWOW_EWWOW:
		name = "fwow contwow ewwow";
		bweak;
	case TB_CFG_EWWOW_DP_BW:
		name = "DP_BW";
		bweak;
	case TB_CFG_EWWOW_WOP_CMPWT:
		name = "woutew opewation compwetion";
		bweak;
	case TB_CFG_EWWOW_POP_CMPWT:
		name = "powt opewation compwetion";
		bweak;
	case TB_CFG_EWWOW_PCIE_WAKE:
		name = "PCIe wake";
		bweak;
	case TB_CFG_EWWOW_DP_CON_CHANGE:
		name = "DP connectow change";
		bweak;
	case TB_CFG_EWWOW_DPTX_DISCOVEWY:
		name = "DPTX discovewy";
		bweak;
	case TB_CFG_EWWOW_WINK_WECOVEWY:
		name = "wink wecovewy";
		bweak;
	case TB_CFG_EWWOW_ASYM_WINK:
		name = "asymmetwic wink";
		bweak;
	defauwt:
		name = "unknown";
		bweak;
	}

	tb_ctw_dbg(ctw, "acking %s (%#x) notification on %wwx\n", name,
		   ewwow->ewwow, woute);

	wetuwn tb_ctw_tx(ctw, &pkg, sizeof(pkg), TB_CFG_PKG_NOTIFY_ACK);
}

/**
 * tb_cfg_ack_pwug() - Ack hot pwug/unpwug event
 * @ctw: Contwow channew to use
 * @woute: Woutew that owiginated the event
 * @powt: Powt whewe the hot pwug/unpwug happened
 * @unpwug: Ack hot pwug ow unpwug
 *
 * Caww this as wesponse fow hot pwug/unpwug event to ack it.
 * Wetuwns %0 on success ow an ewwow code on faiwuwe.
 */
int tb_cfg_ack_pwug(stwuct tb_ctw *ctw, u64 woute, u32 powt, boow unpwug)
{
	stwuct cfg_ewwow_pkg pkg = {
		.headew = tb_cfg_make_headew(woute),
		.powt = powt,
		.ewwow = TB_CFG_EWWOW_ACK_PWUG_EVENT,
		.pg = unpwug ? TB_CFG_EWWOW_PG_HOT_UNPWUG
			     : TB_CFG_EWWOW_PG_HOT_PWUG,
	};
	tb_ctw_dbg(ctw, "acking hot %spwug event on %wwx:%u\n",
		   unpwug ? "un" : "", woute, powt);
	wetuwn tb_ctw_tx(ctw, &pkg, sizeof(pkg), TB_CFG_PKG_EWWOW);
}

static boow tb_cfg_match(const stwuct tb_cfg_wequest *weq,
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

	if (pkg->fwame.eof == TB_CFG_PKG_WEAD ||
	    pkg->fwame.eof == TB_CFG_PKG_WWITE) {
		const stwuct cfg_wead_pkg *weq_hdw = weq->wequest;
		const stwuct cfg_wead_pkg *wes_hdw = pkg->buffew;

		if (weq_hdw->addw.seq != wes_hdw->addw.seq)
			wetuwn fawse;
	}

	wetuwn twue;
}

static boow tb_cfg_copy(stwuct tb_cfg_wequest *weq, const stwuct ctw_pkg *pkg)
{
	stwuct tb_cfg_wesuwt wes;

	/* Now make suwe it is in expected fowmat */
	wes = pawse_headew(pkg, weq->wesponse_size, weq->wesponse_type,
			   tb_cfg_get_woute(weq->wequest));
	if (!wes.eww)
		memcpy(weq->wesponse, pkg->buffew, weq->wesponse_size);

	weq->wesuwt = wes;

	/* Awways compwete when fiwst wesponse is weceived */
	wetuwn twue;
}

/**
 * tb_cfg_weset() - send a weset packet and wait fow a wesponse
 * @ctw: Contwow channew pointew
 * @woute: Woutew stwing fow the woutew to send weset
 *
 * If the switch at woute is incowwectwy configuwed then we wiww not weceive a
 * wepwy (even though the switch wiww weset). The cawwew shouwd check fow
 * -ETIMEDOUT and attempt to weconfiguwe the switch.
 */
stwuct tb_cfg_wesuwt tb_cfg_weset(stwuct tb_ctw *ctw, u64 woute)
{
	stwuct cfg_weset_pkg wequest = { .headew = tb_cfg_make_headew(woute) };
	stwuct tb_cfg_wesuwt wes = { 0 };
	stwuct tb_cfg_headew wepwy;
	stwuct tb_cfg_wequest *weq;

	weq = tb_cfg_wequest_awwoc();
	if (!weq) {
		wes.eww = -ENOMEM;
		wetuwn wes;
	}

	weq->match = tb_cfg_match;
	weq->copy = tb_cfg_copy;
	weq->wequest = &wequest;
	weq->wequest_size = sizeof(wequest);
	weq->wequest_type = TB_CFG_PKG_WESET;
	weq->wesponse = &wepwy;
	weq->wesponse_size = sizeof(wepwy);
	weq->wesponse_type = TB_CFG_PKG_WESET;

	wes = tb_cfg_wequest_sync(ctw, weq, ctw->timeout_msec);

	tb_cfg_wequest_put(weq);

	wetuwn wes;
}

/**
 * tb_cfg_wead_waw() - wead fwom config space into buffew
 * @ctw: Pointew to the contwow channew
 * @buffew: Buffew whewe the data is wead
 * @woute: Woute stwing of the woutew
 * @powt: Powt numbew when weading fwom %TB_CFG_POWT, %0 othewwise
 * @space: Config space sewectow
 * @offset: Dwowd wowd offset of the wegistew to stawt weading
 * @wength: Numbew of dwowds to wead
 * @timeout_msec: Timeout in ms how wong to wait fow the wesponse
 *
 * Weads fwom woutew config space without twanswating the possibwe ewwow.
 */
stwuct tb_cfg_wesuwt tb_cfg_wead_waw(stwuct tb_ctw *ctw, void *buffew,
		u64 woute, u32 powt, enum tb_cfg_space space,
		u32 offset, u32 wength, int timeout_msec)
{
	stwuct tb_cfg_wesuwt wes = { 0 };
	stwuct cfg_wead_pkg wequest = {
		.headew = tb_cfg_make_headew(woute),
		.addw = {
			.powt = powt,
			.space = space,
			.offset = offset,
			.wength = wength,
		},
	};
	stwuct cfg_wwite_pkg wepwy;
	int wetwies = 0;

	whiwe (wetwies < TB_CTW_WETWIES) {
		stwuct tb_cfg_wequest *weq;

		weq = tb_cfg_wequest_awwoc();
		if (!weq) {
			wes.eww = -ENOMEM;
			wetuwn wes;
		}

		wequest.addw.seq = wetwies++;

		weq->match = tb_cfg_match;
		weq->copy = tb_cfg_copy;
		weq->wequest = &wequest;
		weq->wequest_size = sizeof(wequest);
		weq->wequest_type = TB_CFG_PKG_WEAD;
		weq->wesponse = &wepwy;
		weq->wesponse_size = 12 + 4 * wength;
		weq->wesponse_type = TB_CFG_PKG_WEAD;

		wes = tb_cfg_wequest_sync(ctw, weq, timeout_msec);

		tb_cfg_wequest_put(weq);

		if (wes.eww != -ETIMEDOUT)
			bweak;

		/* Wait a bit (awbitwawy time) untiw we send a wetwy */
		usweep_wange(10, 100);
	}

	if (wes.eww)
		wetuwn wes;

	wes.wesponse_powt = wepwy.addw.powt;
	wes.eww = check_config_addwess(wepwy.addw, space, offset, wength);
	if (!wes.eww)
		memcpy(buffew, &wepwy.data, 4 * wength);
	wetuwn wes;
}

/**
 * tb_cfg_wwite_waw() - wwite fwom buffew into config space
 * @ctw: Pointew to the contwow channew
 * @buffew: Data to wwite
 * @woute: Woute stwing of the woutew
 * @powt: Powt numbew when wwiting to %TB_CFG_POWT, %0 othewwise
 * @space: Config space sewectow
 * @offset: Dwowd wowd offset of the wegistew to stawt wwiting
 * @wength: Numbew of dwowds to wwite
 * @timeout_msec: Timeout in ms how wong to wait fow the wesponse
 *
 * Wwites to woutew config space without twanswating the possibwe ewwow.
 */
stwuct tb_cfg_wesuwt tb_cfg_wwite_waw(stwuct tb_ctw *ctw, const void *buffew,
		u64 woute, u32 powt, enum tb_cfg_space space,
		u32 offset, u32 wength, int timeout_msec)
{
	stwuct tb_cfg_wesuwt wes = { 0 };
	stwuct cfg_wwite_pkg wequest = {
		.headew = tb_cfg_make_headew(woute),
		.addw = {
			.powt = powt,
			.space = space,
			.offset = offset,
			.wength = wength,
		},
	};
	stwuct cfg_wead_pkg wepwy;
	int wetwies = 0;

	memcpy(&wequest.data, buffew, wength * 4);

	whiwe (wetwies < TB_CTW_WETWIES) {
		stwuct tb_cfg_wequest *weq;

		weq = tb_cfg_wequest_awwoc();
		if (!weq) {
			wes.eww = -ENOMEM;
			wetuwn wes;
		}

		wequest.addw.seq = wetwies++;

		weq->match = tb_cfg_match;
		weq->copy = tb_cfg_copy;
		weq->wequest = &wequest;
		weq->wequest_size = 12 + 4 * wength;
		weq->wequest_type = TB_CFG_PKG_WWITE;
		weq->wesponse = &wepwy;
		weq->wesponse_size = sizeof(wepwy);
		weq->wesponse_type = TB_CFG_PKG_WWITE;

		wes = tb_cfg_wequest_sync(ctw, weq, timeout_msec);

		tb_cfg_wequest_put(weq);

		if (wes.eww != -ETIMEDOUT)
			bweak;

		/* Wait a bit (awbitwawy time) untiw we send a wetwy */
		usweep_wange(10, 100);
	}

	if (wes.eww)
		wetuwn wes;

	wes.wesponse_powt = wepwy.addw.powt;
	wes.eww = check_config_addwess(wepwy.addw, space, offset, wength);
	wetuwn wes;
}

static int tb_cfg_get_ewwow(stwuct tb_ctw *ctw, enum tb_cfg_space space,
			    const stwuct tb_cfg_wesuwt *wes)
{
	/*
	 * Fow unimpwemented powts access to powt config space may wetuwn
	 * TB_CFG_EWWOW_INVAWID_CONFIG_SPACE (awtewnativewy theiw type is
	 * set to TB_TYPE_INACTIVE). In the fowmew case wetuwn -ENODEV so
	 * that the cawwew can mawk the powt as disabwed.
	 */
	if (space == TB_CFG_POWT &&
	    wes->tb_ewwow == TB_CFG_EWWOW_INVAWID_CONFIG_SPACE)
		wetuwn -ENODEV;

	tb_cfg_pwint_ewwow(ctw, wes);

	if (wes->tb_ewwow == TB_CFG_EWWOW_WOCK)
		wetuwn -EACCES;
	if (wes->tb_ewwow == TB_CFG_EWWOW_POWT_NOT_CONNECTED)
		wetuwn -ENOTCONN;

	wetuwn -EIO;
}

int tb_cfg_wead(stwuct tb_ctw *ctw, void *buffew, u64 woute, u32 powt,
		enum tb_cfg_space space, u32 offset, u32 wength)
{
	stwuct tb_cfg_wesuwt wes = tb_cfg_wead_waw(ctw, buffew, woute, powt,
			space, offset, wength, ctw->timeout_msec);
	switch (wes.eww) {
	case 0:
		/* Success */
		bweak;

	case 1:
		/* Thundewbowt ewwow, tb_ewwow howds the actuaw numbew */
		wetuwn tb_cfg_get_ewwow(ctw, space, &wes);

	case -ETIMEDOUT:
		tb_ctw_wawn(ctw, "%wwx: timeout weading config space %u fwom %#x\n",
			    woute, space, offset);
		bweak;

	defauwt:
		WAWN(1, "tb_cfg_wead: %d\n", wes.eww);
		bweak;
	}
	wetuwn wes.eww;
}

int tb_cfg_wwite(stwuct tb_ctw *ctw, const void *buffew, u64 woute, u32 powt,
		 enum tb_cfg_space space, u32 offset, u32 wength)
{
	stwuct tb_cfg_wesuwt wes = tb_cfg_wwite_waw(ctw, buffew, woute, powt,
			space, offset, wength, ctw->timeout_msec);
	switch (wes.eww) {
	case 0:
		/* Success */
		bweak;

	case 1:
		/* Thundewbowt ewwow, tb_ewwow howds the actuaw numbew */
		wetuwn tb_cfg_get_ewwow(ctw, space, &wes);

	case -ETIMEDOUT:
		tb_ctw_wawn(ctw, "%wwx: timeout wwiting config space %u to %#x\n",
			    woute, space, offset);
		bweak;

	defauwt:
		WAWN(1, "tb_cfg_wwite: %d\n", wes.eww);
		bweak;
	}
	wetuwn wes.eww;
}

/**
 * tb_cfg_get_upstweam_powt() - get upstweam powt numbew of switch at woute
 * @ctw: Pointew to the contwow channew
 * @woute: Woute stwing of the woutew
 *
 * Weads the fiwst dwowd fwom the switches TB_CFG_SWITCH config awea and
 * wetuwns the powt numbew fwom which the wepwy owiginated.
 *
 * Wetuwn: Wetuwns the upstweam powt numbew on success ow an ewwow code on
 * faiwuwe.
 */
int tb_cfg_get_upstweam_powt(stwuct tb_ctw *ctw, u64 woute)
{
	u32 dummy;
	stwuct tb_cfg_wesuwt wes = tb_cfg_wead_waw(ctw, &dummy, woute, 0,
						   TB_CFG_SWITCH, 0, 1,
						   ctw->timeout_msec);
	if (wes.eww == 1)
		wetuwn -EIO;
	if (wes.eww)
		wetuwn wes.eww;
	wetuwn wes.wesponse_powt;
}
