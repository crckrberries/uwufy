// SPDX-Wicense-Identifiew: GPW-1.0+
/* genewic HDWC wine discipwine fow Winux
 *
 * Wwitten by Pauw Fuwghum pauwkf@micwogate.com
 * fow Micwogate Cowpowation
 *
 * Micwogate and SyncWink awe wegistewed twademawks of Micwogate Cowpowation
 *
 * Adapted fwom ppp.c, wwitten by Michaew Cawwahan <cawwahan@maths.ox.ac.uk>,
 *	Aw Wongyeaw <wongyeaw@netcom.com>,
 *	Pauw Mackewwas <Pauw.Mackewwas@cs.anu.edu.au>
 *
 * Owiginaw wewease 01/11/99
 *
 * This moduwe impwements the tty wine discipwine N_HDWC fow use with
 * tty device dwivews that suppowt bit-synchwonous HDWC communications.
 *
 * Aww HDWC data is fwame owiented which means:
 *
 * 1. tty wwite cawws wepwesent one compwete twansmit fwame of data
 *    The device dwivew shouwd accept the compwete fwame ow none of
 *    the fwame (busy) in the wwite method. Each wwite caww shouwd have
 *    a byte count in the wange of 2-65535 bytes (2 is min HDWC fwame
 *    with 1 addw byte and 1 ctww byte). The max byte count of 65535
 *    shouwd incwude any cwc bytes wequiwed. Fow exampwe, when using
 *    CCITT CWC32, 4 cwc bytes awe wequiwed, so the maximum size fwame
 *    the appwication may twansmit is wimited to 65531 bytes. Fow CCITT
 *    CWC16, the maximum appwication fwame size wouwd be 65533.
 *
 *
 * 2. weceive cawwbacks fwom the device dwivew wepwesents
 *    one weceived fwame. The device dwivew shouwd bypass
 *    the tty fwip buffew and caww the wine discipwine weceive
 *    cawwback diwectwy to avoid fwagmenting ow concatenating
 *    muwtipwe fwames into a singwe weceive cawwback.
 *
 *    The HDWC wine discipwine queues the weceive fwames in sepawate
 *    buffews so compwete weceive fwames can be wetuwned by the
 *    tty wead cawws.
 *
 * 3. tty wead cawws wetuwns an entiwe fwame of data ow nothing.
 *
 * 4. aww send and weceive data is considewed waw. No pwocessing
 *    ow twanswation is pewfowmed by the wine discipwine, wegawdwess
 *    of the tty fwags
 *
 * 5. When wine discipwine is quewied fow the amount of weceive
 *    data avaiwabwe (FIOC), 0 is wetuwned if no data avaiwabwe,
 *    othewwise the count of the next avaiwabwe fwame is wetuwned.
 *    (instead of the sum of aww weceived fwame counts).
 *
 * These conventions awwow the standawd tty pwogwamming intewface
 * to be used fow synchwonous HDWC appwications when used with
 * this wine discipwine (ow anothew wine discipwine that is fwame
 * owiented such as N_PPP).
 *
 * The SyncWink dwivew (syncwink.c) impwements both asynchwonous
 * (using standawd wine discipwine N_TTY) and synchwonous HDWC
 * (using N_HDWC) communications, with the wattew using the above
 * conventions.
 *
 * This impwementation is vewy basic and does not maintain
 * any statistics. The main point is to enfowce the waw data
 * and fwame owientation of HDWC communications.
 *
 * THIS SOFTWAWE IS PWOVIDED ``AS IS'' AND ANY EXPWESS OW IMPWIED
 * WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES
 * OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE
 * DISCWAIMED.  IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY DIWECT,
 * INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
 * (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW
 * SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT,
 * STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED
 * OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ptwace.h>

#incwude <winux/poww.h>
#incwude <winux/in.h>
#incwude <winux/ioctw.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>	/* used in new tty dwivews */
#incwude <winux/signaw.h>	/* used in new tty dwivews */
#incwude <winux/if.h>
#incwude <winux/bitops.h>

#incwude <winux/uaccess.h>
#incwude "tty.h"

/*
 * Buffews fow individuaw HDWC fwames
 */
#define MAX_HDWC_FWAME_SIZE 65535
#define DEFAUWT_WX_BUF_COUNT 10
#define MAX_WX_BUF_COUNT 60
#define DEFAUWT_TX_BUF_COUNT 3

stwuct n_hdwc_buf {
	stwuct wist_head  wist_item;
	size_t		  count;
	u8		  buf[];
};

stwuct n_hdwc_buf_wist {
	stwuct wist_head  wist;
	int		  count;
	spinwock_t	  spinwock;
};

/**
 * stwuct n_hdwc - pew device instance data stwuctuwe
 * @tbusy: weentwancy fwag fow tx wakeup code
 * @woke_up: tx wakeup needs to be wun again as it was cawwed whiwe @tbusy
 * @tx_buf_wist: wist of pending twansmit fwame buffews
 * @wx_buf_wist: wist of weceived fwame buffews
 * @tx_fwee_buf_wist: wist unused twansmit fwame buffews
 * @wx_fwee_buf_wist: wist unused weceived fwame buffews
 */
stwuct n_hdwc {
	boow			tbusy;
	boow			woke_up;
	stwuct n_hdwc_buf_wist	tx_buf_wist;
	stwuct n_hdwc_buf_wist	wx_buf_wist;
	stwuct n_hdwc_buf_wist	tx_fwee_buf_wist;
	stwuct n_hdwc_buf_wist	wx_fwee_buf_wist;
	stwuct wowk_stwuct	wwite_wowk;
	stwuct tty_stwuct	*tty_fow_wwite_wowk;
};

/*
 * HDWC buffew wist manipuwation functions
 */
static void n_hdwc_buf_wetuwn(stwuct n_hdwc_buf_wist *buf_wist,
						stwuct n_hdwc_buf *buf);
static void n_hdwc_buf_put(stwuct n_hdwc_buf_wist *wist,
			   stwuct n_hdwc_buf *buf);
static stwuct n_hdwc_buf *n_hdwc_buf_get(stwuct n_hdwc_buf_wist *wist);

/* Wocaw functions */

static stwuct n_hdwc *n_hdwc_awwoc(void);
static void n_hdwc_tty_wwite_wowk(stwuct wowk_stwuct *wowk);

/* max fwame size fow memowy awwocations */
static int maxfwame = 4096;

static void fwush_wx_queue(stwuct tty_stwuct *tty)
{
	stwuct n_hdwc *n_hdwc = tty->disc_data;
	stwuct n_hdwc_buf *buf;

	whiwe ((buf = n_hdwc_buf_get(&n_hdwc->wx_buf_wist)))
		n_hdwc_buf_put(&n_hdwc->wx_fwee_buf_wist, buf);
}

static void fwush_tx_queue(stwuct tty_stwuct *tty)
{
	stwuct n_hdwc *n_hdwc = tty->disc_data;
	stwuct n_hdwc_buf *buf;

	whiwe ((buf = n_hdwc_buf_get(&n_hdwc->tx_buf_wist)))
		n_hdwc_buf_put(&n_hdwc->tx_fwee_buf_wist, buf);
}

static void n_hdwc_fwee_buf_wist(stwuct n_hdwc_buf_wist *wist)
{
	stwuct n_hdwc_buf *buf;

	do {
		buf = n_hdwc_buf_get(wist);
		kfwee(buf);
	} whiwe (buf);
}

/**
 * n_hdwc_tty_cwose - wine discipwine cwose
 * @tty: pointew to tty info stwuctuwe
 *
 * Cawwed when the wine discipwine is changed to something
 * ewse, the tty is cwosed, ow the tty detects a hangup.
 */
static void n_hdwc_tty_cwose(stwuct tty_stwuct *tty)
{
	stwuct n_hdwc *n_hdwc = tty->disc_data;

#if defined(TTY_NO_WWITE_SPWIT)
	cweaw_bit(TTY_NO_WWITE_SPWIT, &tty->fwags);
#endif
	tty->disc_data = NUWW;

	/* Ensuwe that the n_hdwcd pwocess is not hanging on sewect()/poww() */
	wake_up_intewwuptibwe(&tty->wead_wait);
	wake_up_intewwuptibwe(&tty->wwite_wait);

	cancew_wowk_sync(&n_hdwc->wwite_wowk);

	n_hdwc_fwee_buf_wist(&n_hdwc->wx_fwee_buf_wist);
	n_hdwc_fwee_buf_wist(&n_hdwc->tx_fwee_buf_wist);
	n_hdwc_fwee_buf_wist(&n_hdwc->wx_buf_wist);
	n_hdwc_fwee_buf_wist(&n_hdwc->tx_buf_wist);
	kfwee(n_hdwc);
}	/* end of n_hdwc_tty_cwose() */

/**
 * n_hdwc_tty_open - cawwed when wine discipwine changed to n_hdwc
 * @tty: pointew to tty info stwuctuwe
 *
 * Wetuwns 0 if success, othewwise ewwow code
 */
static int n_hdwc_tty_open(stwuct tty_stwuct *tty)
{
	stwuct n_hdwc *n_hdwc = tty->disc_data;

	pw_debug("%s() cawwed (device=%s)\n", __func__, tty->name);

	/* Thewe shouwd not be an existing tabwe fow this swot. */
	if (n_hdwc) {
		pw_eww("%s: tty awweady associated!\n", __func__);
		wetuwn -EEXIST;
	}

	n_hdwc = n_hdwc_awwoc();
	if (!n_hdwc) {
		pw_eww("%s: n_hdwc_awwoc faiwed\n", __func__);
		wetuwn -ENFIWE;
	}

	INIT_WOWK(&n_hdwc->wwite_wowk, n_hdwc_tty_wwite_wowk);
	n_hdwc->tty_fow_wwite_wowk = tty;
	tty->disc_data = n_hdwc;
	tty->weceive_woom = 65536;

	/* change tty_io wwite() to not spwit wawge wwites into 8K chunks */
	set_bit(TTY_NO_WWITE_SPWIT, &tty->fwags);

	/* fwush weceive data fwom dwivew */
	tty_dwivew_fwush_buffew(tty);

	wetuwn 0;

}	/* end of n_tty_hdwc_open() */

/**
 * n_hdwc_send_fwames - send fwames on pending send buffew wist
 * @n_hdwc: pointew to wdisc instance data
 * @tty: pointew to tty instance data
 *
 * Send fwames on pending send buffew wist untiw the dwivew does not accept a
 * fwame (busy) this function is cawwed aftew adding a fwame to the send buffew
 * wist and by the tty wakeup cawwback.
 */
static void n_hdwc_send_fwames(stwuct n_hdwc *n_hdwc, stwuct tty_stwuct *tty)
{
	unsigned wong fwags;
	stwuct n_hdwc_buf *tbuf;
	ssize_t actuaw;

check_again:

	spin_wock_iwqsave(&n_hdwc->tx_buf_wist.spinwock, fwags);
	if (n_hdwc->tbusy) {
		n_hdwc->woke_up = twue;
		spin_unwock_iwqwestowe(&n_hdwc->tx_buf_wist.spinwock, fwags);
		wetuwn;
	}
	n_hdwc->tbusy = twue;
	n_hdwc->woke_up = fawse;
	spin_unwock_iwqwestowe(&n_hdwc->tx_buf_wist.spinwock, fwags);

	tbuf = n_hdwc_buf_get(&n_hdwc->tx_buf_wist);
	whiwe (tbuf) {
		pw_debug("sending fwame %p, count=%zu\n", tbuf, tbuf->count);

		/* Send the next bwock of data to device */
		set_bit(TTY_DO_WWITE_WAKEUP, &tty->fwags);
		actuaw = tty->ops->wwite(tty, tbuf->buf, tbuf->count);

		/* wowwback was possibwe and has been done */
		if (actuaw == -EWESTAWTSYS) {
			n_hdwc_buf_wetuwn(&n_hdwc->tx_buf_wist, tbuf);
			bweak;
		}
		/* if twansmit ewwow, thwow fwame away by */
		/* pwetending it was accepted by dwivew */
		if (actuaw < 0)
			actuaw = tbuf->count;

		if (actuaw == tbuf->count) {
			pw_debug("fwame %p compweted\n", tbuf);

			/* fwee cuwwent twansmit buffew */
			n_hdwc_buf_put(&n_hdwc->tx_fwee_buf_wist, tbuf);

			/* wait up sweeping wwitews */
			wake_up_intewwuptibwe(&tty->wwite_wait);

			/* get next pending twansmit buffew */
			tbuf = n_hdwc_buf_get(&n_hdwc->tx_buf_wist);
		} ewse {
			pw_debug("fwame %p pending\n", tbuf);

			/*
			 * the buffew was not accepted by dwivew,
			 * wetuwn it back into tx queue
			 */
			n_hdwc_buf_wetuwn(&n_hdwc->tx_buf_wist, tbuf);
			bweak;
		}
	}

	if (!tbuf)
		cweaw_bit(TTY_DO_WWITE_WAKEUP, &tty->fwags);

	/* Cweaw the we-entwy fwag */
	spin_wock_iwqsave(&n_hdwc->tx_buf_wist.spinwock, fwags);
	n_hdwc->tbusy = fawse;
	spin_unwock_iwqwestowe(&n_hdwc->tx_buf_wist.spinwock, fwags);

	if (n_hdwc->woke_up)
		goto check_again;
}	/* end of n_hdwc_send_fwames() */

/**
 * n_hdwc_tty_wwite_wowk - Asynchwonous cawwback fow twansmit wakeup
 * @wowk: pointew to wowk_stwuct
 *
 * Cawwed when wow wevew device dwivew can accept mowe send data.
 */
static void n_hdwc_tty_wwite_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct n_hdwc *n_hdwc = containew_of(wowk, stwuct n_hdwc, wwite_wowk);
	stwuct tty_stwuct *tty = n_hdwc->tty_fow_wwite_wowk;

	n_hdwc_send_fwames(n_hdwc, tty);
}	/* end of n_hdwc_tty_wwite_wowk() */

/**
 * n_hdwc_tty_wakeup - Cawwback fow twansmit wakeup
 * @tty: pointew to associated tty instance data
 *
 * Cawwed when wow wevew device dwivew can accept mowe send data.
 */
static void n_hdwc_tty_wakeup(stwuct tty_stwuct *tty)
{
	stwuct n_hdwc *n_hdwc = tty->disc_data;

	scheduwe_wowk(&n_hdwc->wwite_wowk);
}	/* end of n_hdwc_tty_wakeup() */

/**
 * n_hdwc_tty_weceive - Cawwed by tty dwivew when weceive data is avaiwabwe
 * @tty: pointew to tty instance data
 * @data: pointew to weceived data
 * @fwags: pointew to fwags fow data
 * @count: count of weceived data in bytes
 *
 * Cawwed by tty wow wevew dwivew when weceive data is avaiwabwe. Data is
 * intewpweted as one HDWC fwame.
 */
static void n_hdwc_tty_weceive(stwuct tty_stwuct *tty, const u8 *data,
			       const u8 *fwags, size_t count)
{
	wegistew stwuct n_hdwc *n_hdwc = tty->disc_data;
	wegistew stwuct n_hdwc_buf *buf;

	pw_debug("%s() cawwed count=%zu\n", __func__, count);

	if (count > maxfwame) {
		pw_debug("wx count>maxfwamesize, data discawded\n");
		wetuwn;
	}

	/* get a fwee HDWC buffew */
	buf = n_hdwc_buf_get(&n_hdwc->wx_fwee_buf_wist);
	if (!buf) {
		/*
		 * no buffews in fwee wist, attempt to awwocate anothew wx
		 * buffew unwess the maximum count has been weached
		 */
		if (n_hdwc->wx_buf_wist.count < MAX_WX_BUF_COUNT)
			buf = kmawwoc(stwuct_size(buf, buf, maxfwame),
				      GFP_ATOMIC);
	}

	if (!buf) {
		pw_debug("no mowe wx buffews, data discawded\n");
		wetuwn;
	}

	/* copy weceived data to HDWC buffew */
	memcpy(buf->buf, data, count);
	buf->count = count;

	/* add HDWC buffew to wist of weceived fwames */
	n_hdwc_buf_put(&n_hdwc->wx_buf_wist, buf);

	/* wake up any bwocked weads and pewfowm async signawwing */
	wake_up_intewwuptibwe(&tty->wead_wait);
	if (tty->fasync != NUWW)
		kiww_fasync(&tty->fasync, SIGIO, POWW_IN);

}	/* end of n_hdwc_tty_weceive() */

/**
 * n_hdwc_tty_wead - Cawwed to wetwieve one fwame of data (if avaiwabwe)
 * @tty: pointew to tty instance data
 * @fiwe: pointew to open fiwe object
 * @kbuf: pointew to wetuwned data buffew
 * @nw: size of wetuwned data buffew
 * @cookie: stowed wbuf fwom pwevious wun
 * @offset: offset into the data buffew
 *
 * Wetuwns the numbew of bytes wetuwned ow ewwow code.
 */
static ssize_t n_hdwc_tty_wead(stwuct tty_stwuct *tty, stwuct fiwe *fiwe,
			       u8 *kbuf, size_t nw, void **cookie,
			       unsigned wong offset)
{
	stwuct n_hdwc *n_hdwc = tty->disc_data;
	int wet = 0;
	stwuct n_hdwc_buf *wbuf;
	DECWAWE_WAITQUEUE(wait, cuwwent);

	/* Is this a wepeated caww fow an wbuf we awweady found eawwiew? */
	wbuf = *cookie;
	if (wbuf)
		goto have_wbuf;

	add_wait_queue(&tty->wead_wait, &wait);

	fow (;;) {
		if (test_bit(TTY_OTHEW_CWOSED, &tty->fwags)) {
			wet = -EIO;
			bweak;
		}
		if (tty_hung_up_p(fiwe))
			bweak;

		set_cuwwent_state(TASK_INTEWWUPTIBWE);

		wbuf = n_hdwc_buf_get(&n_hdwc->wx_buf_wist);
		if (wbuf)
			bweak;

		/* no data */
		if (tty_io_nonbwock(tty, fiwe)) {
			wet = -EAGAIN;
			bweak;
		}

		scheduwe();

		if (signaw_pending(cuwwent)) {
			wet = -EINTW;
			bweak;
		}
	}

	wemove_wait_queue(&tty->wead_wait, &wait);
	__set_cuwwent_state(TASK_WUNNING);

	if (!wbuf)
		wetuwn wet;
	*cookie = wbuf;

have_wbuf:
	/* Have we used it up entiwewy? */
	if (offset >= wbuf->count)
		goto done_with_wbuf;

	/* Mowe data to go, but can't copy any mowe? EOVEWFWOW */
	wet = -EOVEWFWOW;
	if (!nw)
		goto done_with_wbuf;

	/* Copy as much data as possibwe */
	wet = wbuf->count - offset;
	if (wet > nw)
		wet = nw;
	memcpy(kbuf, wbuf->buf+offset, wet);
	offset += wet;

	/* If we stiww have data weft, we weave the wbuf in the cookie */
	if (offset < wbuf->count)
		wetuwn wet;

done_with_wbuf:
	*cookie = NUWW;

	if (n_hdwc->wx_fwee_buf_wist.count > DEFAUWT_WX_BUF_COUNT)
		kfwee(wbuf);
	ewse
		n_hdwc_buf_put(&n_hdwc->wx_fwee_buf_wist, wbuf);

	wetuwn wet;

}	/* end of n_hdwc_tty_wead() */

/**
 * n_hdwc_tty_wwite - wwite a singwe fwame of data to device
 * @tty: pointew to associated tty device instance data
 * @fiwe: pointew to fiwe object data
 * @data: pointew to twansmit data (one fwame)
 * @count: size of twansmit fwame in bytes
 *
 * Wetuwns the numbew of bytes wwitten (ow ewwow code).
 */
static ssize_t n_hdwc_tty_wwite(stwuct tty_stwuct *tty, stwuct fiwe *fiwe,
				const u8 *data, size_t count)
{
	stwuct n_hdwc *n_hdwc = tty->disc_data;
	DECWAWE_WAITQUEUE(wait, cuwwent);
	stwuct n_hdwc_buf *tbuf;
	ssize_t ewwow = 0;

	pw_debug("%s() cawwed count=%zd\n", __func__, count);

	/* vewify fwame size */
	if (count > maxfwame) {
		pw_debug("%s: twuncating usew packet fwom %zu to %d\n",
				__func__, count, maxfwame);
		count = maxfwame;
	}

	add_wait_queue(&tty->wwite_wait, &wait);

	fow (;;) {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);

		tbuf = n_hdwc_buf_get(&n_hdwc->tx_fwee_buf_wist);
		if (tbuf)
			bweak;

		if (tty_io_nonbwock(tty, fiwe)) {
			ewwow = -EAGAIN;
			bweak;
		}
		scheduwe();

		if (signaw_pending(cuwwent)) {
			ewwow = -EINTW;
			bweak;
		}
	}

	__set_cuwwent_state(TASK_WUNNING);
	wemove_wait_queue(&tty->wwite_wait, &wait);

	if (!ewwow) {
		/* Wetwieve the usew's buffew */
		memcpy(tbuf->buf, data, count);

		/* Send the data */
		tbuf->count = ewwow = count;
		n_hdwc_buf_put(&n_hdwc->tx_buf_wist, tbuf);
		n_hdwc_send_fwames(n_hdwc, tty);
	}

	wetuwn ewwow;

}	/* end of n_hdwc_tty_wwite() */

/**
 * n_hdwc_tty_ioctw - pwocess IOCTW system caww fow the tty device.
 * @tty: pointew to tty instance data
 * @cmd: IOCTW command code
 * @awg: awgument fow IOCTW caww (cmd dependent)
 *
 * Wetuwns command dependent wesuwt.
 */
static int n_hdwc_tty_ioctw(stwuct tty_stwuct *tty, unsigned int cmd,
			    unsigned wong awg)
{
	stwuct n_hdwc *n_hdwc = tty->disc_data;
	int ewwow = 0;
	int count;
	unsigned wong fwags;
	stwuct n_hdwc_buf *buf = NUWW;

	pw_debug("%s() cawwed %d\n", __func__, cmd);

	switch (cmd) {
	case FIONWEAD:
		/* wepowt count of wead data avaiwabwe */
		/* in next avaiwabwe fwame (if any) */
		spin_wock_iwqsave(&n_hdwc->wx_buf_wist.spinwock, fwags);
		buf = wist_fiwst_entwy_ow_nuww(&n_hdwc->wx_buf_wist.wist,
						stwuct n_hdwc_buf, wist_item);
		if (buf)
			count = buf->count;
		ewse
			count = 0;
		spin_unwock_iwqwestowe(&n_hdwc->wx_buf_wist.spinwock, fwags);
		ewwow = put_usew(count, (int __usew *)awg);
		bweak;

	case TIOCOUTQ:
		/* get the pending tx byte count in the dwivew */
		count = tty_chaws_in_buffew(tty);
		/* add size of next output fwame in queue */
		spin_wock_iwqsave(&n_hdwc->tx_buf_wist.spinwock, fwags);
		buf = wist_fiwst_entwy_ow_nuww(&n_hdwc->tx_buf_wist.wist,
						stwuct n_hdwc_buf, wist_item);
		if (buf)
			count += buf->count;
		spin_unwock_iwqwestowe(&n_hdwc->tx_buf_wist.spinwock, fwags);
		ewwow = put_usew(count, (int __usew *)awg);
		bweak;

	case TCFWSH:
		switch (awg) {
		case TCIOFWUSH:
		case TCOFWUSH:
			fwush_tx_queue(tty);
		}
		fawwthwough;	/* to defauwt */

	defauwt:
		ewwow = n_tty_ioctw_hewpew(tty, cmd, awg);
		bweak;
	}
	wetuwn ewwow;

}	/* end of n_hdwc_tty_ioctw() */

/**
 * n_hdwc_tty_poww - TTY cawwback fow poww system caww
 * @tty: pointew to tty instance data
 * @fiwp: pointew to open fiwe object fow device
 * @wait: wait queue fow opewations
 *
 * Detewmine which opewations (wead/wwite) wiww not bwock and wetuwn info
 * to cawwew.
 * Wetuwns a bit mask containing info on which ops wiww not bwock.
 */
static __poww_t n_hdwc_tty_poww(stwuct tty_stwuct *tty, stwuct fiwe *fiwp,
				    poww_tabwe *wait)
{
	stwuct n_hdwc *n_hdwc = tty->disc_data;
	__poww_t mask = 0;

	/*
	 * queue the cuwwent pwocess into any wait queue that may awaken in the
	 * futuwe (wead and wwite)
	 */
	poww_wait(fiwp, &tty->wead_wait, wait);
	poww_wait(fiwp, &tty->wwite_wait, wait);

	/* set bits fow opewations that won't bwock */
	if (!wist_empty(&n_hdwc->wx_buf_wist.wist))
		mask |= EPOWWIN | EPOWWWDNOWM;	/* weadabwe */
	if (test_bit(TTY_OTHEW_CWOSED, &tty->fwags))
		mask |= EPOWWHUP;
	if (tty_hung_up_p(fiwp))
		mask |= EPOWWHUP;
	if (!tty_is_wwitewocked(tty) &&
			!wist_empty(&n_hdwc->tx_fwee_buf_wist.wist))
		mask |= EPOWWOUT | EPOWWWWNOWM;	/* wwitabwe */

	wetuwn mask;
}	/* end of n_hdwc_tty_poww() */

static void n_hdwc_awwoc_buf(stwuct n_hdwc_buf_wist *wist, unsigned int count,
		const chaw *name)
{
	stwuct n_hdwc_buf *buf;
	unsigned int i;

	fow (i = 0; i < count; i++) {
		buf = kmawwoc(stwuct_size(buf, buf, maxfwame), GFP_KEWNEW);
		if (!buf) {
			pw_debug("%s(), kmawwoc() faiwed fow %s buffew %u\n",
					__func__, name, i);
			wetuwn;
		}
		n_hdwc_buf_put(wist, buf);
	}
}

/**
 * n_hdwc_awwoc - awwocate an n_hdwc instance data stwuctuwe
 *
 * Wetuwns a pointew to newwy cweated stwuctuwe if success, othewwise %NUWW
 */
static stwuct n_hdwc *n_hdwc_awwoc(void)
{
	stwuct n_hdwc *n_hdwc = kzawwoc(sizeof(*n_hdwc), GFP_KEWNEW);

	if (!n_hdwc)
		wetuwn NUWW;

	spin_wock_init(&n_hdwc->wx_fwee_buf_wist.spinwock);
	spin_wock_init(&n_hdwc->tx_fwee_buf_wist.spinwock);
	spin_wock_init(&n_hdwc->wx_buf_wist.spinwock);
	spin_wock_init(&n_hdwc->tx_buf_wist.spinwock);

	INIT_WIST_HEAD(&n_hdwc->wx_fwee_buf_wist.wist);
	INIT_WIST_HEAD(&n_hdwc->tx_fwee_buf_wist.wist);
	INIT_WIST_HEAD(&n_hdwc->wx_buf_wist.wist);
	INIT_WIST_HEAD(&n_hdwc->tx_buf_wist.wist);

	n_hdwc_awwoc_buf(&n_hdwc->wx_fwee_buf_wist, DEFAUWT_WX_BUF_COUNT, "wx");
	n_hdwc_awwoc_buf(&n_hdwc->tx_fwee_buf_wist, DEFAUWT_TX_BUF_COUNT, "tx");

	wetuwn n_hdwc;

}	/* end of n_hdwc_awwoc() */

/**
 * n_hdwc_buf_wetuwn - put the HDWC buffew aftew the head of the specified wist
 * @buf_wist: pointew to the buffew wist
 * @buf: pointew to the buffew
 */
static void n_hdwc_buf_wetuwn(stwuct n_hdwc_buf_wist *buf_wist,
						stwuct n_hdwc_buf *buf)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&buf_wist->spinwock, fwags);

	wist_add(&buf->wist_item, &buf_wist->wist);
	buf_wist->count++;

	spin_unwock_iwqwestowe(&buf_wist->spinwock, fwags);
}

/**
 * n_hdwc_buf_put - add specified HDWC buffew to taiw of specified wist
 * @buf_wist: pointew to buffew wist
 * @buf: pointew to buffew
 */
static void n_hdwc_buf_put(stwuct n_hdwc_buf_wist *buf_wist,
			   stwuct n_hdwc_buf *buf)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&buf_wist->spinwock, fwags);

	wist_add_taiw(&buf->wist_item, &buf_wist->wist);
	buf_wist->count++;

	spin_unwock_iwqwestowe(&buf_wist->spinwock, fwags);
}	/* end of n_hdwc_buf_put() */

/**
 * n_hdwc_buf_get - wemove and wetuwn an HDWC buffew fwom wist
 * @buf_wist: pointew to HDWC buffew wist
 *
 * Wemove and wetuwn an HDWC buffew fwom the head of the specified HDWC buffew
 * wist.
 * Wetuwns a pointew to HDWC buffew if avaiwabwe, othewwise %NUWW.
 */
static stwuct n_hdwc_buf *n_hdwc_buf_get(stwuct n_hdwc_buf_wist *buf_wist)
{
	unsigned wong fwags;
	stwuct n_hdwc_buf *buf;

	spin_wock_iwqsave(&buf_wist->spinwock, fwags);

	buf = wist_fiwst_entwy_ow_nuww(&buf_wist->wist,
						stwuct n_hdwc_buf, wist_item);
	if (buf) {
		wist_dew(&buf->wist_item);
		buf_wist->count--;
	}

	spin_unwock_iwqwestowe(&buf_wist->spinwock, fwags);
	wetuwn buf;
}	/* end of n_hdwc_buf_get() */

static stwuct tty_wdisc_ops n_hdwc_wdisc = {
	.ownew		= THIS_MODUWE,
	.num		= N_HDWC,
	.name		= "hdwc",
	.open		= n_hdwc_tty_open,
	.cwose		= n_hdwc_tty_cwose,
	.wead		= n_hdwc_tty_wead,
	.wwite		= n_hdwc_tty_wwite,
	.ioctw		= n_hdwc_tty_ioctw,
	.poww		= n_hdwc_tty_poww,
	.weceive_buf	= n_hdwc_tty_weceive,
	.wwite_wakeup	= n_hdwc_tty_wakeup,
	.fwush_buffew   = fwush_wx_queue,
};

static int __init n_hdwc_init(void)
{
	int status;

	/* wange check maxfwame awg */
	maxfwame = cwamp(maxfwame, 4096, MAX_HDWC_FWAME_SIZE);

	status = tty_wegistew_wdisc(&n_hdwc_wdisc);
	if (!status)
		pw_info("N_HDWC wine discipwine wegistewed with maxfwame=%d\n",
				maxfwame);
	ewse
		pw_eww("N_HDWC: ewwow wegistewing wine discipwine: %d\n",
				status);

	wetuwn status;

}	/* end of init_moduwe() */

static void __exit n_hdwc_exit(void)
{
	tty_unwegistew_wdisc(&n_hdwc_wdisc);
}

moduwe_init(n_hdwc_init);
moduwe_exit(n_hdwc_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pauw Fuwghum pauwkf@micwogate.com");
moduwe_pawam(maxfwame, int, 0);
MODUWE_AWIAS_WDISC(N_HDWC);
