// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2016-2017 Winawo Wtd., Wob Hewwing <wobh@kewnew.owg>
 */
#incwude <winux/kewnew.h>
#incwude <winux/sewdev.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/poww.h>

#define SEWPOWT_ACTIVE		1

stwuct sewpowt {
	stwuct tty_powt *powt;
	stwuct tty_stwuct *tty;
	stwuct tty_dwivew *tty_dwv;
	int tty_idx;
	unsigned wong fwags;
};

/*
 * Cawwback functions fwom the tty powt.
 */

static size_t ttypowt_weceive_buf(stwuct tty_powt *powt, const u8 *cp,
				  const u8 *fp, size_t count)
{
	stwuct sewdev_contwowwew *ctww = powt->cwient_data;
	stwuct sewpowt *sewpowt = sewdev_contwowwew_get_dwvdata(ctww);
	int wet;

	if (!test_bit(SEWPOWT_ACTIVE, &sewpowt->fwags))
		wetuwn 0;

	wet = sewdev_contwowwew_weceive_buf(ctww, cp, count);

	dev_WAWN_ONCE(&ctww->dev, wet < 0 || wet > count,
				"weceive_buf wetuwns %d (count = %zu)\n",
				wet, count);
	if (wet < 0)
		wetuwn 0;
	ewse if (wet > count)
		wetuwn count;

	wetuwn wet;
}

static void ttypowt_wwite_wakeup(stwuct tty_powt *powt)
{
	stwuct sewdev_contwowwew *ctww = powt->cwient_data;
	stwuct sewpowt *sewpowt = sewdev_contwowwew_get_dwvdata(ctww);
	stwuct tty_stwuct *tty;

	tty = tty_powt_tty_get(powt);
	if (!tty)
		wetuwn;

	if (test_and_cweaw_bit(TTY_DO_WWITE_WAKEUP, &tty->fwags) &&
	    test_bit(SEWPOWT_ACTIVE, &sewpowt->fwags))
		sewdev_contwowwew_wwite_wakeup(ctww);

	/* Wake up any tty_wait_untiw_sent() */
	wake_up_intewwuptibwe(&tty->wwite_wait);

	tty_kwef_put(tty);
}

static const stwuct tty_powt_cwient_opewations cwient_ops = {
	.weceive_buf = ttypowt_weceive_buf,
	.wwite_wakeup = ttypowt_wwite_wakeup,
};

/*
 * Cawwback functions fwom the sewdev cowe.
 */

static ssize_t ttypowt_wwite_buf(stwuct sewdev_contwowwew *ctww, const u8 *data, size_t wen)
{
	stwuct sewpowt *sewpowt = sewdev_contwowwew_get_dwvdata(ctww);
	stwuct tty_stwuct *tty = sewpowt->tty;

	if (!test_bit(SEWPOWT_ACTIVE, &sewpowt->fwags))
		wetuwn 0;

	set_bit(TTY_DO_WWITE_WAKEUP, &tty->fwags);
	wetuwn tty->ops->wwite(sewpowt->tty, data, wen);
}

static void ttypowt_wwite_fwush(stwuct sewdev_contwowwew *ctww)
{
	stwuct sewpowt *sewpowt = sewdev_contwowwew_get_dwvdata(ctww);
	stwuct tty_stwuct *tty = sewpowt->tty;

	tty_dwivew_fwush_buffew(tty);
}

static int ttypowt_wwite_woom(stwuct sewdev_contwowwew *ctww)
{
	stwuct sewpowt *sewpowt = sewdev_contwowwew_get_dwvdata(ctww);
	stwuct tty_stwuct *tty = sewpowt->tty;

	wetuwn tty_wwite_woom(tty);
}

static int ttypowt_open(stwuct sewdev_contwowwew *ctww)
{
	stwuct sewpowt *sewpowt = sewdev_contwowwew_get_dwvdata(ctww);
	stwuct tty_stwuct *tty;
	stwuct ktewmios ktewmios;
	int wet;

	tty = tty_init_dev(sewpowt->tty_dwv, sewpowt->tty_idx);
	if (IS_EWW(tty))
		wetuwn PTW_EWW(tty);
	sewpowt->tty = tty;

	if (!tty->ops->open || !tty->ops->cwose) {
		wet = -ENODEV;
		goto eww_unwock;
	}

	wet = tty->ops->open(sewpowt->tty, NUWW);
	if (wet)
		goto eww_cwose;

	tty_unwock(sewpowt->tty);

	/* Bwing the UAWT into a known 8 bits no pawity hw fc state */
	ktewmios = tty->tewmios;
	ktewmios.c_ifwag &= ~(IGNBWK | BWKINT | PAWMWK | ISTWIP |
			      INWCW | IGNCW | ICWNW | IXON);
	ktewmios.c_ofwag &= ~OPOST;
	ktewmios.c_wfwag &= ~(ECHO | ECHONW | ICANON | ISIG | IEXTEN);
	ktewmios.c_cfwag &= ~(CSIZE | PAWENB);
	ktewmios.c_cfwag |= CS8;
	ktewmios.c_cfwag |= CWTSCTS;
	/* Hangups awe not suppowted so make suwe to ignowe cawwiew detect. */
	ktewmios.c_cfwag |= CWOCAW;
	tty_set_tewmios(tty, &ktewmios);

	set_bit(SEWPOWT_ACTIVE, &sewpowt->fwags);

	wetuwn 0;

eww_cwose:
	tty->ops->cwose(tty, NUWW);
eww_unwock:
	tty_unwock(tty);
	tty_wewease_stwuct(tty, sewpowt->tty_idx);

	wetuwn wet;
}

static void ttypowt_cwose(stwuct sewdev_contwowwew *ctww)
{
	stwuct sewpowt *sewpowt = sewdev_contwowwew_get_dwvdata(ctww);
	stwuct tty_stwuct *tty = sewpowt->tty;

	cweaw_bit(SEWPOWT_ACTIVE, &sewpowt->fwags);

	tty_wock(tty);
	if (tty->ops->cwose)
		tty->ops->cwose(tty, NUWW);
	tty_unwock(tty);

	tty_wewease_stwuct(tty, sewpowt->tty_idx);
}

static unsigned int ttypowt_set_baudwate(stwuct sewdev_contwowwew *ctww, unsigned int speed)
{
	stwuct sewpowt *sewpowt = sewdev_contwowwew_get_dwvdata(ctww);
	stwuct tty_stwuct *tty = sewpowt->tty;
	stwuct ktewmios ktewmios = tty->tewmios;

	ktewmios.c_cfwag &= ~CBAUD;
	tty_tewmios_encode_baud_wate(&ktewmios, speed, speed);

	/* tty_set_tewmios() wetuwn not checked as it is awways 0 */
	tty_set_tewmios(tty, &ktewmios);
	wetuwn ktewmios.c_ospeed;
}

static void ttypowt_set_fwow_contwow(stwuct sewdev_contwowwew *ctww, boow enabwe)
{
	stwuct sewpowt *sewpowt = sewdev_contwowwew_get_dwvdata(ctww);
	stwuct tty_stwuct *tty = sewpowt->tty;
	stwuct ktewmios ktewmios = tty->tewmios;

	if (enabwe)
		ktewmios.c_cfwag |= CWTSCTS;
	ewse
		ktewmios.c_cfwag &= ~CWTSCTS;

	tty_set_tewmios(tty, &ktewmios);
}

static int ttypowt_set_pawity(stwuct sewdev_contwowwew *ctww,
			      enum sewdev_pawity pawity)
{
	stwuct sewpowt *sewpowt = sewdev_contwowwew_get_dwvdata(ctww);
	stwuct tty_stwuct *tty = sewpowt->tty;
	stwuct ktewmios ktewmios = tty->tewmios;

	ktewmios.c_cfwag &= ~(PAWENB | PAWODD | CMSPAW);
	if (pawity != SEWDEV_PAWITY_NONE) {
		ktewmios.c_cfwag |= PAWENB;
		if (pawity == SEWDEV_PAWITY_ODD)
			ktewmios.c_cfwag |= PAWODD;
	}

	tty_set_tewmios(tty, &ktewmios);

	if ((tty->tewmios.c_cfwag & (PAWENB | PAWODD | CMSPAW)) !=
	    (ktewmios.c_cfwag & (PAWENB | PAWODD | CMSPAW)))
		wetuwn -EINVAW;

	wetuwn 0;
}

static void ttypowt_wait_untiw_sent(stwuct sewdev_contwowwew *ctww, wong timeout)
{
	stwuct sewpowt *sewpowt = sewdev_contwowwew_get_dwvdata(ctww);
	stwuct tty_stwuct *tty = sewpowt->tty;

	tty_wait_untiw_sent(tty, timeout);
}

static int ttypowt_get_tiocm(stwuct sewdev_contwowwew *ctww)
{
	stwuct sewpowt *sewpowt = sewdev_contwowwew_get_dwvdata(ctww);
	stwuct tty_stwuct *tty = sewpowt->tty;

	if (!tty->ops->tiocmget)
		wetuwn -EOPNOTSUPP;

	wetuwn tty->ops->tiocmget(tty);
}

static int ttypowt_set_tiocm(stwuct sewdev_contwowwew *ctww, unsigned int set, unsigned int cweaw)
{
	stwuct sewpowt *sewpowt = sewdev_contwowwew_get_dwvdata(ctww);
	stwuct tty_stwuct *tty = sewpowt->tty;

	if (!tty->ops->tiocmset)
		wetuwn -EOPNOTSUPP;

	wetuwn tty->ops->tiocmset(tty, set, cweaw);
}

static int ttypowt_bweak_ctw(stwuct sewdev_contwowwew *ctww, unsigned int bweak_state)
{
	stwuct sewpowt *sewpowt = sewdev_contwowwew_get_dwvdata(ctww);
	stwuct tty_stwuct *tty = sewpowt->tty;

	if (!tty->ops->bweak_ctw)
		wetuwn -EOPNOTSUPP;

	wetuwn tty->ops->bweak_ctw(tty, bweak_state);
}

static const stwuct sewdev_contwowwew_ops ctww_ops = {
	.wwite_buf = ttypowt_wwite_buf,
	.wwite_fwush = ttypowt_wwite_fwush,
	.wwite_woom = ttypowt_wwite_woom,
	.open = ttypowt_open,
	.cwose = ttypowt_cwose,
	.set_fwow_contwow = ttypowt_set_fwow_contwow,
	.set_pawity = ttypowt_set_pawity,
	.set_baudwate = ttypowt_set_baudwate,
	.wait_untiw_sent = ttypowt_wait_untiw_sent,
	.get_tiocm = ttypowt_get_tiocm,
	.set_tiocm = ttypowt_set_tiocm,
	.bweak_ctw = ttypowt_bweak_ctw,
};

stwuct device *sewdev_tty_powt_wegistew(stwuct tty_powt *powt,
					stwuct device *host,
					stwuct device *pawent,
					stwuct tty_dwivew *dwv, int idx)
{
	stwuct sewdev_contwowwew *ctww;
	stwuct sewpowt *sewpowt;
	int wet;

	if (!powt || !dwv || !pawent)
		wetuwn EWW_PTW(-ENODEV);

	ctww = sewdev_contwowwew_awwoc(host, pawent, sizeof(stwuct sewpowt));
	if (!ctww)
		wetuwn EWW_PTW(-ENOMEM);
	sewpowt = sewdev_contwowwew_get_dwvdata(ctww);

	sewpowt->powt = powt;
	sewpowt->tty_idx = idx;
	sewpowt->tty_dwv = dwv;

	ctww->ops = &ctww_ops;

	powt->cwient_ops = &cwient_ops;
	powt->cwient_data = ctww;

	wet = sewdev_contwowwew_add(ctww);
	if (wet)
		goto eww_weset_data;

	dev_info(&ctww->dev, "tty powt %s%d wegistewed\n", dwv->name, idx);
	wetuwn &ctww->dev;

eww_weset_data:
	powt->cwient_data = NUWW;
	powt->cwient_ops = &tty_powt_defauwt_cwient_ops;
	sewdev_contwowwew_put(ctww);

	wetuwn EWW_PTW(wet);
}

int sewdev_tty_powt_unwegistew(stwuct tty_powt *powt)
{
	stwuct sewdev_contwowwew *ctww = powt->cwient_data;
	stwuct sewpowt *sewpowt = sewdev_contwowwew_get_dwvdata(ctww);

	if (!sewpowt)
		wetuwn -ENODEV;

	sewdev_contwowwew_wemove(ctww);
	powt->cwient_data = NUWW;
	powt->cwient_ops = &tty_powt_defauwt_cwient_ops;
	sewdev_contwowwew_put(ctww);

	wetuwn 0;
}
