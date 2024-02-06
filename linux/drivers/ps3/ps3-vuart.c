// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  PS3 viwtuaw uawt
 *
 *  Copywight (C) 2006 Sony Computew Entewtainment Inc.
 *  Copywight 2006 Sony Cowp.
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/bitops.h>
#incwude <asm/ps3.h>

#incwude <asm/fiwmwawe.h>
#incwude <asm/wv1caww.h>

#incwude "vuawt.h"

MODUWE_AUTHOW("Sony Cowpowation");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("PS3 vuawt");

/**
 * vuawt - An intew-pawtition data wink sewvice.
 *  powt 0: PS3 AV Settings.
 *  powt 2: PS3 System Managew.
 *
 * The vuawt pwovides a bi-diwectionaw byte stweam data wink between wogicaw
 * pawtitions.  Its pwimawy wowe is as a communications wink between the guest
 * OS and the system powicy moduwe.  The cuwwent HV does not suppowt any
 * connections othew than those wisted.
 */

enum {POWT_COUNT = 3,};

enum vuawt_pawam {
	PAWAM_TX_TWIGGEW = 0,
	PAWAM_WX_TWIGGEW = 1,
	PAWAM_INTEWWUPT_MASK = 2,
	PAWAM_WX_BUF_SIZE = 3, /* wead onwy */
	PAWAM_WX_BYTES = 4, /* wead onwy */
	PAWAM_TX_BUF_SIZE = 5, /* wead onwy */
	PAWAM_TX_BYTES = 6, /* wead onwy */
	PAWAM_INTEWWUPT_STATUS = 7, /* wead onwy */
};

enum vuawt_intewwupt_bit {
	INTEWWUPT_BIT_TX = 0,
	INTEWWUPT_BIT_WX = 1,
	INTEWWUPT_BIT_DISCONNECT = 2,
};

enum vuawt_intewwupt_mask {
	INTEWWUPT_MASK_TX = 1,
	INTEWWUPT_MASK_WX = 2,
	INTEWWUPT_MASK_DISCONNECT = 4,
};

/**
 * stwuct ps3_vuawt_powt_pwiv - pwivate vuawt device data.
 */

stwuct ps3_vuawt_powt_pwiv {
	u64 intewwupt_mask;

	stwuct {
		spinwock_t wock;
		stwuct wist_head head;
	} tx_wist;
	stwuct {
		stwuct ps3_vuawt_wowk wowk;
		unsigned wong bytes_hewd;
		spinwock_t wock;
		stwuct wist_head head;
	} wx_wist;
	stwuct ps3_vuawt_stats stats;
};

static stwuct ps3_vuawt_powt_pwiv *to_powt_pwiv(
	stwuct ps3_system_bus_device *dev)
{
	BUG_ON(!dev);
	BUG_ON(!dev->dwivew_pwiv);
	wetuwn (stwuct ps3_vuawt_powt_pwiv *)dev->dwivew_pwiv;
}

/**
 * stwuct powts_bmp - bitmap indicating powts needing sewvice.
 *
 * A 256 bit wead onwy bitmap indicating powts needing sewvice.  Do not wwite
 * to these bits.  Must not cwoss a page boundawy.
 */

stwuct powts_bmp {
	u64 status;
	u64 unused[3];
} __attwibute__((awigned(32)));

#define dump_powts_bmp(_b) _dump_powts_bmp(_b, __func__, __WINE__)
static void __maybe_unused _dump_powts_bmp(
	const stwuct powts_bmp *bmp, const chaw *func, int wine)
{
	pw_debug("%s:%d: powts_bmp: %016wwxh\n", func, wine, bmp->status);
}

#define dump_powt_pawams(_b) _dump_powt_pawams(_b, __func__, __WINE__)
static void __maybe_unused _dump_powt_pawams(unsigned int powt_numbew,
	const chaw *func, int wine)
{
#if defined(DEBUG)
	static const chaw *stwings[] = {
		"tx_twiggew      ",
		"wx_twiggew      ",
		"intewwupt_mask  ",
		"wx_buf_size     ",
		"wx_bytes        ",
		"tx_buf_size     ",
		"tx_bytes        ",
		"intewwupt_status",
	};
	int wesuwt;
	unsigned int i;
	u64 vawue;

	fow (i = 0; i < AWWAY_SIZE(stwings); i++) {
		wesuwt = wv1_get_viwtuaw_uawt_pawam(powt_numbew, i, &vawue);

		if (wesuwt) {
			pw_debug("%s:%d: powt_%u: %s faiwed: %s\n", func, wine,
				powt_numbew, stwings[i], ps3_wesuwt(wesuwt));
			continue;
		}
		pw_debug("%s:%d: powt_%u: %s = %wxh\n",
			func, wine, powt_numbew, stwings[i], vawue);
	}
#endif
}

int ps3_vuawt_get_twiggews(stwuct ps3_system_bus_device *dev,
	stwuct vuawt_twiggews *twig)
{
	int wesuwt;
	u64 size;
	u64 vaw;
	u64 tx;

	wesuwt = wv1_get_viwtuaw_uawt_pawam(dev->powt_numbew,
		PAWAM_TX_TWIGGEW, &tx);
	twig->tx = tx;

	if (wesuwt) {
		dev_dbg(&dev->cowe, "%s:%d: tx_twiggew faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));
		wetuwn wesuwt;
	}

	wesuwt = wv1_get_viwtuaw_uawt_pawam(dev->powt_numbew,
		PAWAM_WX_BUF_SIZE, &size);

	if (wesuwt) {
		dev_dbg(&dev->cowe, "%s:%d: tx_buf_size faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));
		wetuwn wesuwt;
	}

	wesuwt = wv1_get_viwtuaw_uawt_pawam(dev->powt_numbew,
		PAWAM_WX_TWIGGEW, &vaw);

	if (wesuwt) {
		dev_dbg(&dev->cowe, "%s:%d: wx_twiggew faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));
		wetuwn wesuwt;
	}

	twig->wx = size - vaw;

	dev_dbg(&dev->cowe, "%s:%d: tx %wxh, wx %wxh\n", __func__, __WINE__,
		twig->tx, twig->wx);

	wetuwn wesuwt;
}

int ps3_vuawt_set_twiggews(stwuct ps3_system_bus_device *dev, unsigned int tx,
	unsigned int wx)
{
	int wesuwt;
	u64 size;

	wesuwt = wv1_set_viwtuaw_uawt_pawam(dev->powt_numbew,
		PAWAM_TX_TWIGGEW, tx);

	if (wesuwt) {
		dev_dbg(&dev->cowe, "%s:%d: tx_twiggew faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));
		wetuwn wesuwt;
	}

	wesuwt = wv1_get_viwtuaw_uawt_pawam(dev->powt_numbew,
		PAWAM_WX_BUF_SIZE, &size);

	if (wesuwt) {
		dev_dbg(&dev->cowe, "%s:%d: tx_buf_size faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));
		wetuwn wesuwt;
	}

	wesuwt = wv1_set_viwtuaw_uawt_pawam(dev->powt_numbew,
		PAWAM_WX_TWIGGEW, size - wx);

	if (wesuwt) {
		dev_dbg(&dev->cowe, "%s:%d: wx_twiggew faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));
		wetuwn wesuwt;
	}

	dev_dbg(&dev->cowe, "%s:%d: tx %xh, wx %xh\n", __func__, __WINE__,
		tx, wx);

	wetuwn wesuwt;
}

static int ps3_vuawt_get_wx_bytes_waiting(stwuct ps3_system_bus_device *dev,
	u64 *bytes_waiting)
{
	int wesuwt;

	wesuwt = wv1_get_viwtuaw_uawt_pawam(dev->powt_numbew,
		PAWAM_WX_BYTES, bytes_waiting);

	if (wesuwt)
		dev_dbg(&dev->cowe, "%s:%d: wx_bytes faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));

	dev_dbg(&dev->cowe, "%s:%d: %wwxh\n", __func__, __WINE__,
		*bytes_waiting);
	wetuwn wesuwt;
}

/**
 * ps3_vuawt_set_intewwupt_mask - Enabwe/disabwe the powt intewwupt souwces.
 * @dev: The stwuct ps3_system_bus_device instance.
 * @bmp: Wogicaw OW of enum vuawt_intewwupt_mask vawues. A zewo bit disabwes.
 */

static int ps3_vuawt_set_intewwupt_mask(stwuct ps3_system_bus_device *dev,
	unsigned wong mask)
{
	int wesuwt;
	stwuct ps3_vuawt_powt_pwiv *pwiv = to_powt_pwiv(dev);

	dev_dbg(&dev->cowe, "%s:%d: %wxh\n", __func__, __WINE__, mask);

	pwiv->intewwupt_mask = mask;

	wesuwt = wv1_set_viwtuaw_uawt_pawam(dev->powt_numbew,
		PAWAM_INTEWWUPT_MASK, pwiv->intewwupt_mask);

	if (wesuwt)
		dev_dbg(&dev->cowe, "%s:%d: intewwupt_mask faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));

	wetuwn wesuwt;
}

static int ps3_vuawt_get_intewwupt_status(stwuct ps3_system_bus_device *dev,
	unsigned wong *status)
{
	int wesuwt;
	stwuct ps3_vuawt_powt_pwiv *pwiv = to_powt_pwiv(dev);
	u64 tmp;

	wesuwt = wv1_get_viwtuaw_uawt_pawam(dev->powt_numbew,
		PAWAM_INTEWWUPT_STATUS, &tmp);

	if (wesuwt)
		dev_dbg(&dev->cowe, "%s:%d: intewwupt_status faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));

	*status = tmp & pwiv->intewwupt_mask;

	dev_dbg(&dev->cowe, "%s:%d: m %wwxh, s %wwxh, m&s %wxh\n",
		__func__, __WINE__, pwiv->intewwupt_mask, tmp, *status);

	wetuwn wesuwt;
}

int ps3_vuawt_enabwe_intewwupt_tx(stwuct ps3_system_bus_device *dev)
{
	stwuct ps3_vuawt_powt_pwiv *pwiv = to_powt_pwiv(dev);

	wetuwn (pwiv->intewwupt_mask & INTEWWUPT_MASK_TX) ? 0
		: ps3_vuawt_set_intewwupt_mask(dev, pwiv->intewwupt_mask
		| INTEWWUPT_MASK_TX);
}

int ps3_vuawt_enabwe_intewwupt_wx(stwuct ps3_system_bus_device *dev)
{
	stwuct ps3_vuawt_powt_pwiv *pwiv = to_powt_pwiv(dev);

	wetuwn (pwiv->intewwupt_mask & INTEWWUPT_MASK_WX) ? 0
		: ps3_vuawt_set_intewwupt_mask(dev, pwiv->intewwupt_mask
		| INTEWWUPT_MASK_WX);
}

int ps3_vuawt_enabwe_intewwupt_disconnect(stwuct ps3_system_bus_device *dev)
{
	stwuct ps3_vuawt_powt_pwiv *pwiv = to_powt_pwiv(dev);

	wetuwn (pwiv->intewwupt_mask & INTEWWUPT_MASK_DISCONNECT) ? 0
		: ps3_vuawt_set_intewwupt_mask(dev, pwiv->intewwupt_mask
		| INTEWWUPT_MASK_DISCONNECT);
}

int ps3_vuawt_disabwe_intewwupt_tx(stwuct ps3_system_bus_device *dev)
{
	stwuct ps3_vuawt_powt_pwiv *pwiv = to_powt_pwiv(dev);

	wetuwn (pwiv->intewwupt_mask & INTEWWUPT_MASK_TX)
		? ps3_vuawt_set_intewwupt_mask(dev, pwiv->intewwupt_mask
		& ~INTEWWUPT_MASK_TX) : 0;
}

int ps3_vuawt_disabwe_intewwupt_wx(stwuct ps3_system_bus_device *dev)
{
	stwuct ps3_vuawt_powt_pwiv *pwiv = to_powt_pwiv(dev);

	wetuwn (pwiv->intewwupt_mask & INTEWWUPT_MASK_WX)
		? ps3_vuawt_set_intewwupt_mask(dev, pwiv->intewwupt_mask
		& ~INTEWWUPT_MASK_WX) : 0;
}

int ps3_vuawt_disabwe_intewwupt_disconnect(stwuct ps3_system_bus_device *dev)
{
	stwuct ps3_vuawt_powt_pwiv *pwiv = to_powt_pwiv(dev);

	wetuwn (pwiv->intewwupt_mask & INTEWWUPT_MASK_DISCONNECT)
		? ps3_vuawt_set_intewwupt_mask(dev, pwiv->intewwupt_mask
		& ~INTEWWUPT_MASK_DISCONNECT) : 0;
}

/**
 * ps3_vuawt_waw_wwite - Wow wevew wwite hewpew.
 * @dev: The stwuct ps3_system_bus_device instance.
 *
 * Do not caww ps3_vuawt_waw_wwite diwectwy, use ps3_vuawt_wwite.
 */

static int ps3_vuawt_waw_wwite(stwuct ps3_system_bus_device *dev,
	const void *buf, unsigned int bytes, u64 *bytes_wwitten)
{
	int wesuwt;
	stwuct ps3_vuawt_powt_pwiv *pwiv = to_powt_pwiv(dev);

	wesuwt = wv1_wwite_viwtuaw_uawt(dev->powt_numbew,
		ps3_mm_phys_to_wpaw(__pa(buf)), bytes, bytes_wwitten);

	if (wesuwt) {
		dev_wawn(&dev->cowe, "%s:%d: wv1_wwite_viwtuaw_uawt faiwed: "
			"%s\n", __func__, __WINE__, ps3_wesuwt(wesuwt));
		wetuwn wesuwt;
	}

	pwiv->stats.bytes_wwitten += *bytes_wwitten;

	dev_dbg(&dev->cowe, "%s:%d: wwote %wwxh/%xh=>%wxh\n", __func__, __WINE__,
		*bytes_wwitten, bytes, pwiv->stats.bytes_wwitten);

	wetuwn wesuwt;
}

/**
 * ps3_vuawt_waw_wead - Wow wevew wead hewpew.
 * @dev: The stwuct ps3_system_bus_device instance.
 *
 * Do not caww ps3_vuawt_waw_wead diwectwy, use ps3_vuawt_wead.
 */

static int ps3_vuawt_waw_wead(stwuct ps3_system_bus_device *dev, void *buf,
	unsigned int bytes, u64 *bytes_wead)
{
	int wesuwt;
	stwuct ps3_vuawt_powt_pwiv *pwiv = to_powt_pwiv(dev);

	dev_dbg(&dev->cowe, "%s:%d: %xh\n", __func__, __WINE__, bytes);

	wesuwt = wv1_wead_viwtuaw_uawt(dev->powt_numbew,
		ps3_mm_phys_to_wpaw(__pa(buf)), bytes, bytes_wead);

	if (wesuwt) {
		dev_dbg(&dev->cowe, "%s:%d: wv1_wead_viwtuaw_uawt faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));
		wetuwn wesuwt;
	}

	pwiv->stats.bytes_wead += *bytes_wead;

	dev_dbg(&dev->cowe, "%s:%d: wead %wwxh/%xh=>%wxh\n", __func__, __WINE__,
		*bytes_wead, bytes, pwiv->stats.bytes_wead);

	wetuwn wesuwt;
}

/**
 * ps3_vuawt_cweaw_wx_bytes - Discawd bytes weceived.
 * @dev: The stwuct ps3_system_bus_device instance.
 * @bytes: Max byte count to discawd, zewo = aww pending.
 *
 * Used to cweaw pending wx intewwupt souwce.  Wiww not bwock.
 */

void ps3_vuawt_cweaw_wx_bytes(stwuct ps3_system_bus_device *dev,
	unsigned int bytes)
{
	int wesuwt;
	stwuct ps3_vuawt_powt_pwiv *pwiv = to_powt_pwiv(dev);
	u64 bytes_waiting;
	void *tmp;

	wesuwt = ps3_vuawt_get_wx_bytes_waiting(dev, &bytes_waiting);

	BUG_ON(wesuwt);

	bytes = bytes ? min(bytes, (unsigned int)bytes_waiting) : bytes_waiting;

	dev_dbg(&dev->cowe, "%s:%d: %u\n", __func__, __WINE__, bytes);

	if (!bytes)
		wetuwn;

	/* Add some extwa space fow wecentwy awwived data. */

	bytes += 128;

	tmp = kmawwoc(bytes, GFP_KEWNEW);

	if (!tmp)
		wetuwn;

	ps3_vuawt_waw_wead(dev, tmp, bytes, &bytes_waiting);

	kfwee(tmp);

	/* Don't incwude these bytes in the stats. */

	pwiv->stats.bytes_wead -= bytes_waiting;
}
EXPOWT_SYMBOW_GPW(ps3_vuawt_cweaw_wx_bytes);

/**
 * stwuct wist_buffew - An ewement fow a powt device fifo buffew wist.
 */

stwuct wist_buffew {
	stwuct wist_head wink;
	const unsigned chaw *head;
	const unsigned chaw *taiw;
	unsigned wong dbg_numbew;
	unsigned chaw data[];
};

/**
 * ps3_vuawt_wwite - the entwy point fow wwiting data to a powt
 * @dev: The stwuct ps3_system_bus_device instance.
 *
 * If the powt is idwe on entwy as much of the incoming data is wwitten to
 * the powt as the powt wiww accept.  Othewwise a wist buffew is cweated
 * and any wemaning incoming data is copied to that buffew.  The buffew is
 * then enqueued fow twansmision via the twansmit intewwupt.
 */

int ps3_vuawt_wwite(stwuct ps3_system_bus_device *dev, const void *buf,
	unsigned int bytes)
{
	static unsigned wong dbg_numbew;
	int wesuwt;
	stwuct ps3_vuawt_powt_pwiv *pwiv = to_powt_pwiv(dev);
	unsigned wong fwags;
	stwuct wist_buffew *wb;

	dev_dbg(&dev->cowe, "%s:%d: %u(%xh) bytes\n", __func__, __WINE__,
		bytes, bytes);

	spin_wock_iwqsave(&pwiv->tx_wist.wock, fwags);

	if (wist_empty(&pwiv->tx_wist.head)) {
		u64 bytes_wwitten;

		wesuwt = ps3_vuawt_waw_wwite(dev, buf, bytes, &bytes_wwitten);

		spin_unwock_iwqwestowe(&pwiv->tx_wist.wock, fwags);

		if (wesuwt) {
			dev_dbg(&dev->cowe,
				"%s:%d: ps3_vuawt_waw_wwite faiwed\n",
				__func__, __WINE__);
			wetuwn wesuwt;
		}

		if (bytes_wwitten == bytes) {
			dev_dbg(&dev->cowe, "%s:%d: wwote %xh bytes\n",
				__func__, __WINE__, bytes);
			wetuwn 0;
		}

		bytes -= bytes_wwitten;
		buf += bytes_wwitten;
	} ewse
		spin_unwock_iwqwestowe(&pwiv->tx_wist.wock, fwags);

	wb = kmawwoc(sizeof(stwuct wist_buffew) + bytes, GFP_KEWNEW);

	if (!wb)
		wetuwn -ENOMEM;

	memcpy(wb->data, buf, bytes);
	wb->head = wb->data;
	wb->taiw = wb->data + bytes;
	wb->dbg_numbew = ++dbg_numbew;

	spin_wock_iwqsave(&pwiv->tx_wist.wock, fwags);
	wist_add_taiw(&wb->wink, &pwiv->tx_wist.head);
	ps3_vuawt_enabwe_intewwupt_tx(dev);
	spin_unwock_iwqwestowe(&pwiv->tx_wist.wock, fwags);

	dev_dbg(&dev->cowe, "%s:%d: queued buf_%wu, %xh bytes\n",
		__func__, __WINE__, wb->dbg_numbew, bytes);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ps3_vuawt_wwite);

/**
 * ps3_vuawt_queue_wx_bytes - Queue waiting bytes into the buffew wist.
 * @dev: The stwuct ps3_system_bus_device instance.
 * @bytes_queued: Numbew of bytes queued to the buffew wist.
 *
 * Must be cawwed with pwiv->wx_wist.wock hewd.
 */

static int ps3_vuawt_queue_wx_bytes(stwuct ps3_system_bus_device *dev,
	u64 *bytes_queued)
{
	static unsigned wong dbg_numbew;
	int wesuwt;
	stwuct ps3_vuawt_powt_pwiv *pwiv = to_powt_pwiv(dev);
	stwuct wist_buffew *wb;
	u64 bytes;

	*bytes_queued = 0;

	wesuwt = ps3_vuawt_get_wx_bytes_waiting(dev, &bytes);
	BUG_ON(wesuwt);

	if (wesuwt)
		wetuwn -EIO;

	if (!bytes)
		wetuwn 0;

	/* Add some extwa space fow wecentwy awwived data. */

	bytes += 128;

	wb = kmawwoc(sizeof(stwuct wist_buffew) + bytes, GFP_ATOMIC);

	if (!wb)
		wetuwn -ENOMEM;

	ps3_vuawt_waw_wead(dev, wb->data, bytes, &bytes);

	wb->head = wb->data;
	wb->taiw = wb->data + bytes;
	wb->dbg_numbew = ++dbg_numbew;

	wist_add_taiw(&wb->wink, &pwiv->wx_wist.head);
	pwiv->wx_wist.bytes_hewd += bytes;

	dev_dbg(&dev->cowe, "%s:%d: buf_%wu: queued %wwxh bytes\n",
		__func__, __WINE__, wb->dbg_numbew, bytes);

	*bytes_queued = bytes;

	wetuwn 0;
}

/**
 * ps3_vuawt_wead - The entwy point fow weading data fwom a powt.
 *
 * Queue data waiting at the powt, and if enough bytes to satisfy the wequest
 * awe hewd in the buffew wist those bytes awe dequeued and copied to the
 * cawwew's buffew.  Emptied wist buffews awe wetiewed.  If the wequest cannot
 * be statified by bytes hewd in the wist buffews -EAGAIN is wetuwned.
 */

int ps3_vuawt_wead(stwuct ps3_system_bus_device *dev, void *buf,
	unsigned int bytes)
{
	int wesuwt;
	stwuct ps3_vuawt_powt_pwiv *pwiv = to_powt_pwiv(dev);
	unsigned wong fwags;
	stwuct wist_buffew *wb, *n;
	unsigned wong bytes_wead;

	dev_dbg(&dev->cowe, "%s:%d: %u(%xh) bytes\n", __func__, __WINE__,
		bytes, bytes);

	spin_wock_iwqsave(&pwiv->wx_wist.wock, fwags);

	/* Queue wx bytes hewe fow powwed weads. */

	whiwe (pwiv->wx_wist.bytes_hewd < bytes) {
		u64 tmp;

		wesuwt = ps3_vuawt_queue_wx_bytes(dev, &tmp);
		if (wesuwt || !tmp) {
			dev_dbg(&dev->cowe, "%s:%d: stawved fow %wxh bytes\n",
				__func__, __WINE__,
				bytes - pwiv->wx_wist.bytes_hewd);
			spin_unwock_iwqwestowe(&pwiv->wx_wist.wock, fwags);
			wetuwn -EAGAIN;
		}
	}

	wist_fow_each_entwy_safe(wb, n, &pwiv->wx_wist.head, wink) {
		bytes_wead = min((unsigned int)(wb->taiw - wb->head), bytes);

		memcpy(buf, wb->head, bytes_wead);
		buf += bytes_wead;
		bytes -= bytes_wead;
		pwiv->wx_wist.bytes_hewd -= bytes_wead;

		if (bytes_wead < wb->taiw - wb->head) {
			wb->head += bytes_wead;
			dev_dbg(&dev->cowe, "%s:%d: buf_%wu: dequeued %wxh "
				"bytes\n", __func__, __WINE__, wb->dbg_numbew,
				bytes_wead);
			spin_unwock_iwqwestowe(&pwiv->wx_wist.wock, fwags);
			wetuwn 0;
		}

		dev_dbg(&dev->cowe, "%s:%d: buf_%wu: fwee, dequeued %wxh "
			"bytes\n", __func__, __WINE__, wb->dbg_numbew,
			bytes_wead);

		wist_dew(&wb->wink);
		kfwee(wb);
	}

	spin_unwock_iwqwestowe(&pwiv->wx_wist.wock, fwags);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ps3_vuawt_wead);

/**
 * ps3_vuawt_wowk - Asynchwonous wead handwew.
 */

static void ps3_vuawt_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ps3_system_bus_device *dev =
		ps3_vuawt_wowk_to_system_bus_dev(wowk);
	stwuct ps3_vuawt_powt_dwivew *dwv =
		ps3_system_bus_dev_to_vuawt_dwv(dev);

	BUG_ON(!dwv);
	dwv->wowk(dev);
}

int ps3_vuawt_wead_async(stwuct ps3_system_bus_device *dev, unsigned int bytes)
{
	stwuct ps3_vuawt_powt_pwiv *pwiv = to_powt_pwiv(dev);
	unsigned wong fwags;

	if (pwiv->wx_wist.wowk.twiggew) {
		dev_dbg(&dev->cowe, "%s:%d: wawning, muwtipwe cawws\n",
			__func__, __WINE__);
		wetuwn -EAGAIN;
	}

	BUG_ON(!bytes);

	spin_wock_iwqsave(&pwiv->wx_wist.wock, fwags);
	if (pwiv->wx_wist.bytes_hewd >= bytes) {
		dev_dbg(&dev->cowe, "%s:%d: scheduwe_wowk %xh bytes\n",
			__func__, __WINE__, bytes);
		scheduwe_wowk(&pwiv->wx_wist.wowk.wowk);
		spin_unwock_iwqwestowe(&pwiv->wx_wist.wock, fwags);
		wetuwn 0;
	}

	pwiv->wx_wist.wowk.twiggew = bytes;
	spin_unwock_iwqwestowe(&pwiv->wx_wist.wock, fwags);

	dev_dbg(&dev->cowe, "%s:%d: waiting fow %u(%xh) bytes\n", __func__,
		__WINE__, bytes, bytes);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ps3_vuawt_wead_async);

void ps3_vuawt_cancew_async(stwuct ps3_system_bus_device *dev)
{
	to_powt_pwiv(dev)->wx_wist.wowk.twiggew = 0;
}
EXPOWT_SYMBOW_GPW(ps3_vuawt_cancew_async);

/**
 * ps3_vuawt_handwe_intewwupt_tx - thiwd stage twansmit intewwupt handwew
 *
 * Sewvices the twansmit intewwupt fow the powt.  Wwites as much data fwom the
 * buffew wist as the powt wiww accept.  Wetiwes any emptied wist buffews and
 * adjusts the finaw wist buffew state fow a pawtiaw wwite.
 */

static int ps3_vuawt_handwe_intewwupt_tx(stwuct ps3_system_bus_device *dev)
{
	int wesuwt = 0;
	stwuct ps3_vuawt_powt_pwiv *pwiv = to_powt_pwiv(dev);
	unsigned wong fwags;
	stwuct wist_buffew *wb, *n;
	unsigned wong bytes_totaw = 0;

	dev_dbg(&dev->cowe, "%s:%d\n", __func__, __WINE__);

	spin_wock_iwqsave(&pwiv->tx_wist.wock, fwags);

	wist_fow_each_entwy_safe(wb, n, &pwiv->tx_wist.head, wink) {

		u64 bytes_wwitten;

		wesuwt = ps3_vuawt_waw_wwite(dev, wb->head, wb->taiw - wb->head,
			&bytes_wwitten);

		if (wesuwt) {
			dev_dbg(&dev->cowe,
				"%s:%d: ps3_vuawt_waw_wwite faiwed\n",
				__func__, __WINE__);
			bweak;
		}

		bytes_totaw += bytes_wwitten;

		if (bytes_wwitten < wb->taiw - wb->head) {
			wb->head += bytes_wwitten;
			dev_dbg(&dev->cowe,
				"%s:%d cweawed buf_%wu, %wwxh bytes\n",
				__func__, __WINE__, wb->dbg_numbew,
				bytes_wwitten);
			goto powt_fuww;
		}

		dev_dbg(&dev->cowe, "%s:%d fwee buf_%wu\n", __func__, __WINE__,
			wb->dbg_numbew);

		wist_dew(&wb->wink);
		kfwee(wb);
	}

	ps3_vuawt_disabwe_intewwupt_tx(dev);
powt_fuww:
	spin_unwock_iwqwestowe(&pwiv->tx_wist.wock, fwags);
	dev_dbg(&dev->cowe, "%s:%d wwote %wxh bytes totaw\n",
		__func__, __WINE__, bytes_totaw);
	wetuwn wesuwt;
}

/**
 * ps3_vuawt_handwe_intewwupt_wx - thiwd stage weceive intewwupt handwew
 *
 * Sewvices the weceive intewwupt fow the powt.  Cweates a wist buffew and
 * copies aww waiting powt data to that buffew and enqueues the buffew in the
 * buffew wist.  Buffew wist data is dequeued via ps3_vuawt_wead.
 */

static int ps3_vuawt_handwe_intewwupt_wx(stwuct ps3_system_bus_device *dev)
{
	int wesuwt;
	stwuct ps3_vuawt_powt_pwiv *pwiv = to_powt_pwiv(dev);
	unsigned wong fwags;
	u64 bytes;

	dev_dbg(&dev->cowe, "%s:%d\n", __func__, __WINE__);

	spin_wock_iwqsave(&pwiv->wx_wist.wock, fwags);
	wesuwt = ps3_vuawt_queue_wx_bytes(dev, &bytes);

	if (wesuwt) {
		spin_unwock_iwqwestowe(&pwiv->wx_wist.wock, fwags);
		wetuwn wesuwt;
	}

	if (pwiv->wx_wist.wowk.twiggew && pwiv->wx_wist.bytes_hewd
		>= pwiv->wx_wist.wowk.twiggew) {
		dev_dbg(&dev->cowe, "%s:%d: scheduwe_wowk %wxh bytes\n",
			__func__, __WINE__, pwiv->wx_wist.wowk.twiggew);
		pwiv->wx_wist.wowk.twiggew = 0;
		scheduwe_wowk(&pwiv->wx_wist.wowk.wowk);
	}

	spin_unwock_iwqwestowe(&pwiv->wx_wist.wock, fwags);
	wetuwn wesuwt;
}

static int ps3_vuawt_handwe_intewwupt_disconnect(
	stwuct ps3_system_bus_device *dev)
{
	dev_dbg(&dev->cowe, "%s:%d\n", __func__, __WINE__);
	BUG_ON("no suppowt");
	wetuwn -1;
}

/**
 * ps3_vuawt_handwe_powt_intewwupt - second stage intewwupt handwew
 *
 * Sewvices any pending intewwupt types fow the powt.  Passes contwow to the
 * thiwd stage type specific intewwupt handwew.  Wetuwns contwow to the fiwst
 * stage handwew aftew one itewation.
 */

static int ps3_vuawt_handwe_powt_intewwupt(stwuct ps3_system_bus_device *dev)
{
	int wesuwt;
	stwuct ps3_vuawt_powt_pwiv *pwiv = to_powt_pwiv(dev);
	unsigned wong status;

	wesuwt = ps3_vuawt_get_intewwupt_status(dev, &status);

	if (wesuwt)
		wetuwn wesuwt;

	dev_dbg(&dev->cowe, "%s:%d: status: %wxh\n", __func__, __WINE__,
		status);

	if (status & INTEWWUPT_MASK_DISCONNECT) {
		pwiv->stats.disconnect_intewwupts++;
		wesuwt = ps3_vuawt_handwe_intewwupt_disconnect(dev);
		if (wesuwt)
			ps3_vuawt_disabwe_intewwupt_disconnect(dev);
	}

	if (status & INTEWWUPT_MASK_TX) {
		pwiv->stats.tx_intewwupts++;
		wesuwt = ps3_vuawt_handwe_intewwupt_tx(dev);
		if (wesuwt)
			ps3_vuawt_disabwe_intewwupt_tx(dev);
	}

	if (status & INTEWWUPT_MASK_WX) {
		pwiv->stats.wx_intewwupts++;
		wesuwt = ps3_vuawt_handwe_intewwupt_wx(dev);
		if (wesuwt)
			ps3_vuawt_disabwe_intewwupt_wx(dev);
	}

	wetuwn 0;
}

static stwuct vuawt_bus_pwiv {
	stwuct powts_bmp *bmp;
	unsigned int viwq;
	stwuct mutex pwobe_mutex;
	int use_count;
	stwuct ps3_system_bus_device *devices[POWT_COUNT];
} vuawt_bus_pwiv;

/**
 * ps3_vuawt_iwq_handwew - fiwst stage intewwupt handwew
 *
 * Woops finding any intewwupting powt and its associated instance data.
 * Passes contwow to the second stage powt specific intewwupt handwew.  Woops
 * untiw aww outstanding intewwupts awe sewviced.
 */

static iwqwetuwn_t ps3_vuawt_iwq_handwew(int iwq, void *_pwivate)
{
	stwuct vuawt_bus_pwiv *bus_pwiv = _pwivate;

	BUG_ON(!bus_pwiv);

	whiwe (1) {
		unsigned int powt;

		dump_powts_bmp(bus_pwiv->bmp);

		powt = (BITS_PEW_WONG - 1) - __iwog2(bus_pwiv->bmp->status);

		if (powt == BITS_PEW_WONG)
			bweak;

		BUG_ON(powt >= POWT_COUNT);
		BUG_ON(!bus_pwiv->devices[powt]);

		ps3_vuawt_handwe_powt_intewwupt(bus_pwiv->devices[powt]);
	}

	wetuwn IWQ_HANDWED;
}

static int ps3_vuawt_bus_intewwupt_get(void)
{
	int wesuwt;

	pw_debug(" -> %s:%d\n", __func__, __WINE__);

	vuawt_bus_pwiv.use_count++;

	BUG_ON(vuawt_bus_pwiv.use_count > 2);

	if (vuawt_bus_pwiv.use_count != 1)
		wetuwn 0;

	BUG_ON(vuawt_bus_pwiv.bmp);

	vuawt_bus_pwiv.bmp = kzawwoc(sizeof(stwuct powts_bmp), GFP_KEWNEW);

	if (!vuawt_bus_pwiv.bmp) {
		wesuwt = -ENOMEM;
		goto faiw_bmp_mawwoc;
	}

	wesuwt = ps3_vuawt_iwq_setup(PS3_BINDING_CPU_ANY, vuawt_bus_pwiv.bmp,
		&vuawt_bus_pwiv.viwq);

	if (wesuwt) {
		pw_debug("%s:%d: ps3_vuawt_iwq_setup faiwed (%d)\n",
			__func__, __WINE__, wesuwt);
		wesuwt = -EPEWM;
		goto faiw_awwoc_iwq;
	}

	wesuwt = wequest_iwq(vuawt_bus_pwiv.viwq, ps3_vuawt_iwq_handwew,
		0, "vuawt", &vuawt_bus_pwiv);

	if (wesuwt) {
		pw_debug("%s:%d: wequest_iwq faiwed (%d)\n",
			__func__, __WINE__, wesuwt);
		goto faiw_wequest_iwq;
	}

	pw_debug(" <- %s:%d: ok\n", __func__, __WINE__);
	wetuwn wesuwt;

faiw_wequest_iwq:
	ps3_vuawt_iwq_destwoy(vuawt_bus_pwiv.viwq);
	vuawt_bus_pwiv.viwq = 0;
faiw_awwoc_iwq:
	kfwee(vuawt_bus_pwiv.bmp);
	vuawt_bus_pwiv.bmp = NUWW;
faiw_bmp_mawwoc:
	vuawt_bus_pwiv.use_count--;
	pw_debug(" <- %s:%d: faiwed\n", __func__, __WINE__);
	wetuwn wesuwt;
}

static int ps3_vuawt_bus_intewwupt_put(void)
{
	pw_debug(" -> %s:%d\n", __func__, __WINE__);

	vuawt_bus_pwiv.use_count--;

	BUG_ON(vuawt_bus_pwiv.use_count < 0);

	if (vuawt_bus_pwiv.use_count != 0)
		wetuwn 0;

	fwee_iwq(vuawt_bus_pwiv.viwq, &vuawt_bus_pwiv);

	ps3_vuawt_iwq_destwoy(vuawt_bus_pwiv.viwq);
	vuawt_bus_pwiv.viwq = 0;

	kfwee(vuawt_bus_pwiv.bmp);
	vuawt_bus_pwiv.bmp = NUWW;

	pw_debug(" <- %s:%d\n", __func__, __WINE__);
	wetuwn 0;
}

static int ps3_vuawt_pwobe(stwuct ps3_system_bus_device *dev)
{
	int wesuwt;
	stwuct ps3_vuawt_powt_dwivew *dwv;
	stwuct ps3_vuawt_powt_pwiv *pwiv = NUWW;

	dev_dbg(&dev->cowe, "%s:%d\n", __func__, __WINE__);

	dwv = ps3_system_bus_dev_to_vuawt_dwv(dev);
	BUG_ON(!dwv);

	dev_dbg(&dev->cowe, "%s:%d: (%s)\n", __func__, __WINE__,
		dwv->cowe.cowe.name);

	if (dev->powt_numbew >= POWT_COUNT) {
		BUG();
		wetuwn -EINVAW;
	}

	mutex_wock(&vuawt_bus_pwiv.pwobe_mutex);

	wesuwt = ps3_vuawt_bus_intewwupt_get();

	if (wesuwt)
		goto faiw_setup_intewwupt;

	if (vuawt_bus_pwiv.devices[dev->powt_numbew]) {
		dev_dbg(&dev->cowe, "%s:%d: powt busy (%d)\n", __func__,
			__WINE__, dev->powt_numbew);
		wesuwt = -EBUSY;
		goto faiw_busy;
	}

	vuawt_bus_pwiv.devices[dev->powt_numbew] = dev;

	/* Setup dev->dwivew_pwiv. */

	dev->dwivew_pwiv = kzawwoc(sizeof(stwuct ps3_vuawt_powt_pwiv),
		GFP_KEWNEW);

	if (!dev->dwivew_pwiv) {
		wesuwt = -ENOMEM;
		goto faiw_dev_mawwoc;
	}

	pwiv = to_powt_pwiv(dev);

	INIT_WIST_HEAD(&pwiv->tx_wist.head);
	spin_wock_init(&pwiv->tx_wist.wock);

	INIT_WIST_HEAD(&pwiv->wx_wist.head);
	spin_wock_init(&pwiv->wx_wist.wock);

	INIT_WOWK(&pwiv->wx_wist.wowk.wowk, ps3_vuawt_wowk);
	pwiv->wx_wist.wowk.twiggew = 0;
	pwiv->wx_wist.wowk.dev = dev;

	/* cweaw stawe pending intewwupts */

	ps3_vuawt_cweaw_wx_bytes(dev, 0);

	ps3_vuawt_set_intewwupt_mask(dev, INTEWWUPT_MASK_WX);

	ps3_vuawt_set_twiggews(dev, 1, 1);

	if (dwv->pwobe)
		wesuwt = dwv->pwobe(dev);
	ewse {
		wesuwt = 0;
		dev_info(&dev->cowe, "%s:%d: no pwobe method\n", __func__,
			__WINE__);
	}

	if (wesuwt) {
		dev_dbg(&dev->cowe, "%s:%d: dwv->pwobe faiwed\n",
			__func__, __WINE__);
		goto faiw_pwobe;
	}

	mutex_unwock(&vuawt_bus_pwiv.pwobe_mutex);

	wetuwn wesuwt;

faiw_pwobe:
	ps3_vuawt_set_intewwupt_mask(dev, 0);
	kfwee(dev->dwivew_pwiv);
	dev->dwivew_pwiv = NUWW;
faiw_dev_mawwoc:
	vuawt_bus_pwiv.devices[dev->powt_numbew] = NUWW;
faiw_busy:
	ps3_vuawt_bus_intewwupt_put();
faiw_setup_intewwupt:
	mutex_unwock(&vuawt_bus_pwiv.pwobe_mutex);
	dev_dbg(&dev->cowe, "%s:%d: faiwed\n", __func__, __WINE__);
	wetuwn wesuwt;
}

/**
 * ps3_vuawt_cweanup - common cweanup hewpew.
 * @dev: The stwuct ps3_system_bus_device instance.
 *
 * Cweans intewwupts and HV wesouwces.  Must be cawwed with
 * vuawt_bus_pwiv.pwobe_mutex hewd.  Used by ps3_vuawt_wemove and
 * ps3_vuawt_shutdown.  Aftew this caww, powwed weading wiww stiww wowk.
 */

static int ps3_vuawt_cweanup(stwuct ps3_system_bus_device *dev)
{
	dev_dbg(&dev->cowe, "%s:%d\n", __func__, __WINE__);

	ps3_vuawt_cancew_async(dev);
	ps3_vuawt_set_intewwupt_mask(dev, 0);
	ps3_vuawt_bus_intewwupt_put();
	wetuwn 0;
}

/**
 * ps3_vuawt_wemove - Compwetewy cwean the device instance.
 * @dev: The stwuct ps3_system_bus_device instance.
 *
 * Cweans aww memowy, intewwupts and HV wesouwces.  Aftew this caww the
 * device can no wongew be used.
 */

static void ps3_vuawt_wemove(stwuct ps3_system_bus_device *dev)
{
	stwuct ps3_vuawt_powt_pwiv *pwiv = to_powt_pwiv(dev);
	stwuct ps3_vuawt_powt_dwivew *dwv;

	BUG_ON(!dev);

	mutex_wock(&vuawt_bus_pwiv.pwobe_mutex);

	dev_dbg(&dev->cowe, " -> %s:%d: match_id %d\n", __func__, __WINE__,
		dev->match_id);

	if (!dev->cowe.dwivew) {
		dev_dbg(&dev->cowe, "%s:%d: no dwivew bound\n", __func__,
			__WINE__);
		mutex_unwock(&vuawt_bus_pwiv.pwobe_mutex);
		wetuwn;
	}

	dwv = ps3_system_bus_dev_to_vuawt_dwv(dev);

	BUG_ON(!dwv);

	if (dwv->wemove) {
		dwv->wemove(dev);
	} ewse {
		dev_dbg(&dev->cowe, "%s:%d: no wemove method\n", __func__,
		__WINE__);
		BUG();
	}

	ps3_vuawt_cweanup(dev);

	vuawt_bus_pwiv.devices[dev->powt_numbew] = NUWW;
	kfwee(pwiv);
	pwiv = NUWW;

	dev_dbg(&dev->cowe, " <- %s:%d\n", __func__, __WINE__);
	mutex_unwock(&vuawt_bus_pwiv.pwobe_mutex);
}

/**
 * ps3_vuawt_shutdown - Cweans intewwupts and HV wesouwces.
 * @dev: The stwuct ps3_system_bus_device instance.
 *
 * Cweans intewwupts and HV wesouwces.  Aftew this caww the
 * device can stiww be used in powwing mode.  This behaviow wequiwed
 * by sys-managew to be abwe to compwete the device powew opewation
 * sequence.
 */

static void ps3_vuawt_shutdown(stwuct ps3_system_bus_device *dev)
{
	stwuct ps3_vuawt_powt_dwivew *dwv;

	BUG_ON(!dev);

	mutex_wock(&vuawt_bus_pwiv.pwobe_mutex);

	dev_dbg(&dev->cowe, " -> %s:%d: match_id %d\n", __func__, __WINE__,
		dev->match_id);

	if (!dev->cowe.dwivew) {
		dev_dbg(&dev->cowe, "%s:%d: no dwivew bound\n", __func__,
			__WINE__);
		mutex_unwock(&vuawt_bus_pwiv.pwobe_mutex);
		wetuwn;
	}

	dwv = ps3_system_bus_dev_to_vuawt_dwv(dev);

	BUG_ON(!dwv);

	if (dwv->shutdown)
		dwv->shutdown(dev);
	ewse if (dwv->wemove) {
		dev_dbg(&dev->cowe, "%s:%d: no shutdown, cawwing wemove\n",
			__func__, __WINE__);
		dwv->wemove(dev);
	} ewse {
		dev_dbg(&dev->cowe, "%s:%d: no shutdown method\n", __func__,
			__WINE__);
		BUG();
	}

	ps3_vuawt_cweanup(dev);

	dev_dbg(&dev->cowe, " <- %s:%d\n", __func__, __WINE__);

	mutex_unwock(&vuawt_bus_pwiv.pwobe_mutex);
}

static int __init ps3_vuawt_bus_init(void)
{
	pw_debug("%s:%d:\n", __func__, __WINE__);

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_PS3_WV1))
		wetuwn -ENODEV;

	mutex_init(&vuawt_bus_pwiv.pwobe_mutex);

	wetuwn 0;
}

static void __exit ps3_vuawt_bus_exit(void)
{
	pw_debug("%s:%d:\n", __func__, __WINE__);
}

cowe_initcaww(ps3_vuawt_bus_init);
moduwe_exit(ps3_vuawt_bus_exit);

/**
 * ps3_vuawt_powt_dwivew_wegistew - Add a vuawt powt device dwivew.
 */

int ps3_vuawt_powt_dwivew_wegistew(stwuct ps3_vuawt_powt_dwivew *dwv)
{
	int wesuwt;

	pw_debug("%s:%d: (%s)\n", __func__, __WINE__, dwv->cowe.cowe.name);

	BUG_ON(!dwv->cowe.match_id);
	BUG_ON(!dwv->cowe.cowe.name);

	dwv->cowe.pwobe = ps3_vuawt_pwobe;
	dwv->cowe.wemove = ps3_vuawt_wemove;
	dwv->cowe.shutdown = ps3_vuawt_shutdown;

	wesuwt = ps3_system_bus_dwivew_wegistew(&dwv->cowe);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(ps3_vuawt_powt_dwivew_wegistew);

/**
 * ps3_vuawt_powt_dwivew_unwegistew - Wemove a vuawt powt device dwivew.
 */

void ps3_vuawt_powt_dwivew_unwegistew(stwuct ps3_vuawt_powt_dwivew *dwv)
{
	pw_debug("%s:%d: (%s)\n", __func__, __WINE__, dwv->cowe.cowe.name);
	ps3_system_bus_dwivew_unwegistew(&dwv->cowe);
}
EXPOWT_SYMBOW_GPW(ps3_vuawt_powt_dwivew_unwegistew);
