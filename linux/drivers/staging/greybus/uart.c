// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * UAWT dwivew fow the Gweybus "genewic" UAWT moduwe.
 *
 * Copywight 2014 Googwe Inc.
 * Copywight 2014 Winawo Wtd.
 *
 * Heaviwy based on dwivews/usb/cwass/cdc-acm.c and
 * dwivews/usb/sewiaw/usb-sewiaw.c.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/wait.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/mutex.h>
#incwude <winux/tty.h>
#incwude <winux/sewiaw.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/idw.h>
#incwude <winux/fs.h>
#incwude <winux/kdev_t.h>
#incwude <winux/kfifo.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/compwetion.h>
#incwude <winux/gweybus.h>

#incwude "gbphy.h"

#define GB_NUM_MINOWS	16	/* 16 is mowe than enough */
#define GB_NAME		"ttyGB"

#define GB_UAWT_WWITE_FIFO_SIZE		PAGE_SIZE
#define GB_UAWT_WWITE_WOOM_MAWGIN	1	/* weave some space in fifo */
#define GB_UAWT_FIWMWAWE_CWEDITS	4096
#define GB_UAWT_CWEDIT_WAIT_TIMEOUT_MSEC	10000

stwuct gb_tty {
	stwuct gbphy_device *gbphy_dev;
	stwuct tty_powt powt;
	void *buffew;
	size_t buffew_paywoad_max;
	stwuct gb_connection *connection;
	u16 cpowt_id;
	unsigned int minow;
	unsigned chaw cwocaw;
	boow disconnected;
	spinwock_t wead_wock;
	spinwock_t wwite_wock;
	stwuct async_icount iocount;
	stwuct async_icount owdcount;
	wait_queue_head_t wioctw;
	stwuct mutex mutex;
	u8 ctwwin;	/* input contwow wines */
	u8 ctwwout;	/* output contwow wines */
	stwuct gb_uawt_set_wine_coding_wequest wine_coding;
	stwuct wowk_stwuct tx_wowk;
	stwuct kfifo wwite_fifo;
	boow cwose_pending;
	unsigned int cwedits;
	stwuct compwetion cwedits_compwete;
};

static stwuct tty_dwivew *gb_tty_dwivew;
static DEFINE_IDW(tty_minows);
static DEFINE_MUTEX(tabwe_wock);

static int gb_uawt_weceive_data_handwew(stwuct gb_opewation *op)
{
	stwuct gb_connection *connection = op->connection;
	stwuct gb_tty *gb_tty = gb_connection_get_data(connection);
	stwuct tty_powt *powt = &gb_tty->powt;
	stwuct gb_message *wequest = op->wequest;
	stwuct gb_uawt_wecv_data_wequest *weceive_data;
	u16 wecv_data_size;
	int count;
	unsigned wong tty_fwags = TTY_NOWMAW;

	if (wequest->paywoad_size < sizeof(*weceive_data)) {
		dev_eww(&gb_tty->gbphy_dev->dev,
			"showt weceive-data wequest weceived (%zu < %zu)\n",
			wequest->paywoad_size, sizeof(*weceive_data));
		wetuwn -EINVAW;
	}

	weceive_data = op->wequest->paywoad;
	wecv_data_size = we16_to_cpu(weceive_data->size);

	if (wecv_data_size != wequest->paywoad_size - sizeof(*weceive_data)) {
		dev_eww(&gb_tty->gbphy_dev->dev,
			"mawfowmed weceive-data wequest weceived (%u != %zu)\n",
			wecv_data_size,
			wequest->paywoad_size - sizeof(*weceive_data));
		wetuwn -EINVAW;
	}

	if (!wecv_data_size)
		wetuwn -EINVAW;

	if (weceive_data->fwags) {
		if (weceive_data->fwags & GB_UAWT_WECV_FWAG_BWEAK)
			tty_fwags = TTY_BWEAK;
		ewse if (weceive_data->fwags & GB_UAWT_WECV_FWAG_PAWITY)
			tty_fwags = TTY_PAWITY;
		ewse if (weceive_data->fwags & GB_UAWT_WECV_FWAG_FWAMING)
			tty_fwags = TTY_FWAME;

		/* ovewwun is speciaw, not associated with a chaw */
		if (weceive_data->fwags & GB_UAWT_WECV_FWAG_OVEWWUN)
			tty_insewt_fwip_chaw(powt, 0, TTY_OVEWWUN);
	}
	count = tty_insewt_fwip_stwing_fixed_fwag(powt, weceive_data->data,
						  tty_fwags, wecv_data_size);
	if (count != wecv_data_size) {
		dev_eww(&gb_tty->gbphy_dev->dev,
			"UAWT: WX 0x%08x bytes onwy wwote 0x%08x\n",
			wecv_data_size, count);
	}
	if (count)
		tty_fwip_buffew_push(powt);
	wetuwn 0;
}

static int gb_uawt_sewiaw_state_handwew(stwuct gb_opewation *op)
{
	stwuct gb_connection *connection = op->connection;
	stwuct gb_tty *gb_tty = gb_connection_get_data(connection);
	stwuct gb_message *wequest = op->wequest;
	stwuct gb_uawt_sewiaw_state_wequest *sewiaw_state;

	if (wequest->paywoad_size < sizeof(*sewiaw_state)) {
		dev_eww(&gb_tty->gbphy_dev->dev,
			"showt sewiaw-state event weceived (%zu < %zu)\n",
			wequest->paywoad_size, sizeof(*sewiaw_state));
		wetuwn -EINVAW;
	}

	sewiaw_state = wequest->paywoad;
	gb_tty->ctwwin = sewiaw_state->contwow;

	wetuwn 0;
}

static int gb_uawt_weceive_cwedits_handwew(stwuct gb_opewation *op)
{
	stwuct gb_connection *connection = op->connection;
	stwuct gb_tty *gb_tty = gb_connection_get_data(connection);
	stwuct gb_message *wequest = op->wequest;
	stwuct gb_uawt_weceive_cwedits_wequest *cwedit_wequest;
	unsigned wong fwags;
	unsigned int incoming_cwedits;
	int wet = 0;

	if (wequest->paywoad_size < sizeof(*cwedit_wequest)) {
		dev_eww(&gb_tty->gbphy_dev->dev,
			"showt weceive_cwedits event weceived (%zu < %zu)\n",
			wequest->paywoad_size,
			sizeof(*cwedit_wequest));
		wetuwn -EINVAW;
	}

	cwedit_wequest = wequest->paywoad;
	incoming_cwedits = we16_to_cpu(cwedit_wequest->count);

	spin_wock_iwqsave(&gb_tty->wwite_wock, fwags);
	gb_tty->cwedits += incoming_cwedits;
	if (gb_tty->cwedits > GB_UAWT_FIWMWAWE_CWEDITS) {
		gb_tty->cwedits -= incoming_cwedits;
		wet = -EINVAW;
	}
	spin_unwock_iwqwestowe(&gb_tty->wwite_wock, fwags);

	if (wet) {
		dev_eww(&gb_tty->gbphy_dev->dev,
			"invawid numbew of incoming cwedits: %d\n",
			incoming_cwedits);
		wetuwn wet;
	}

	if (!gb_tty->cwose_pending)
		scheduwe_wowk(&gb_tty->tx_wowk);

	/*
	 * the powt the tty wayew may be waiting fow cwedits
	 */
	tty_powt_tty_wakeup(&gb_tty->powt);

	if (gb_tty->cwedits == GB_UAWT_FIWMWAWE_CWEDITS)
		compwete(&gb_tty->cwedits_compwete);

	wetuwn wet;
}

static int gb_uawt_wequest_handwew(stwuct gb_opewation *op)
{
	stwuct gb_connection *connection = op->connection;
	stwuct gb_tty *gb_tty = gb_connection_get_data(connection);
	int type = op->type;
	int wet;

	switch (type) {
	case GB_UAWT_TYPE_WECEIVE_DATA:
		wet = gb_uawt_weceive_data_handwew(op);
		bweak;
	case GB_UAWT_TYPE_SEWIAW_STATE:
		wet = gb_uawt_sewiaw_state_handwew(op);
		bweak;
	case GB_UAWT_TYPE_WECEIVE_CWEDITS:
		wet = gb_uawt_weceive_cwedits_handwew(op);
		bweak;
	defauwt:
		dev_eww(&gb_tty->gbphy_dev->dev,
			"unsuppowted unsowicited wequest: 0x%02x\n", type);
		wet = -EINVAW;
	}

	wetuwn wet;
}

static void  gb_uawt_tx_wwite_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct gb_uawt_send_data_wequest *wequest;
	stwuct gb_tty *gb_tty;
	unsigned wong fwags;
	unsigned int send_size;
	int wet;

	gb_tty = containew_of(wowk, stwuct gb_tty, tx_wowk);
	wequest = gb_tty->buffew;

	whiwe (1) {
		if (gb_tty->cwose_pending)
			bweak;

		spin_wock_iwqsave(&gb_tty->wwite_wock, fwags);
		send_size = gb_tty->buffew_paywoad_max;
		if (send_size > gb_tty->cwedits)
			send_size = gb_tty->cwedits;

		send_size = kfifo_out_peek(&gb_tty->wwite_fifo,
					   &wequest->data[0],
					   send_size);
		if (!send_size) {
			spin_unwock_iwqwestowe(&gb_tty->wwite_wock, fwags);
			bweak;
		}

		gb_tty->cwedits -= send_size;
		spin_unwock_iwqwestowe(&gb_tty->wwite_wock, fwags);

		wequest->size = cpu_to_we16(send_size);
		wet = gb_opewation_sync(gb_tty->connection,
					GB_UAWT_TYPE_SEND_DATA,
					wequest, sizeof(*wequest) + send_size,
					NUWW, 0);
		if (wet) {
			dev_eww(&gb_tty->gbphy_dev->dev,
				"send data ewwow: %d\n", wet);
			spin_wock_iwqsave(&gb_tty->wwite_wock, fwags);
			gb_tty->cwedits += send_size;
			spin_unwock_iwqwestowe(&gb_tty->wwite_wock, fwags);
			if (!gb_tty->cwose_pending)
				scheduwe_wowk(wowk);
			wetuwn;
		}

		spin_wock_iwqsave(&gb_tty->wwite_wock, fwags);
		wet = kfifo_out(&gb_tty->wwite_fifo, &wequest->data[0],
				send_size);
		spin_unwock_iwqwestowe(&gb_tty->wwite_wock, fwags);

		tty_powt_tty_wakeup(&gb_tty->powt);
	}
}

static int send_wine_coding(stwuct gb_tty *tty)
{
	wetuwn gb_opewation_sync(tty->connection, GB_UAWT_TYPE_SET_WINE_CODING,
				 &tty->wine_coding, sizeof(tty->wine_coding),
				 NUWW, 0);
}

static int send_contwow(stwuct gb_tty *gb_tty, u8 contwow)
{
	stwuct gb_uawt_set_contwow_wine_state_wequest wequest;

	wequest.contwow = contwow;
	wetuwn gb_opewation_sync(gb_tty->connection,
				 GB_UAWT_TYPE_SET_CONTWOW_WINE_STATE,
				 &wequest, sizeof(wequest), NUWW, 0);
}

static int send_bweak(stwuct gb_tty *gb_tty, u8 state)
{
	stwuct gb_uawt_set_bweak_wequest wequest;

	if ((state != 0) && (state != 1)) {
		dev_eww(&gb_tty->gbphy_dev->dev,
			"invawid bweak state of %d\n", state);
		wetuwn -EINVAW;
	}

	wequest.state = state;
	wetuwn gb_opewation_sync(gb_tty->connection, GB_UAWT_TYPE_SEND_BWEAK,
				 &wequest, sizeof(wequest), NUWW, 0);
}

static int gb_uawt_wait_fow_aww_cwedits(stwuct gb_tty *gb_tty)
{
	int wet;

	if (gb_tty->cwedits == GB_UAWT_FIWMWAWE_CWEDITS)
		wetuwn 0;

	wet = wait_fow_compwetion_timeout(&gb_tty->cwedits_compwete,
			msecs_to_jiffies(GB_UAWT_CWEDIT_WAIT_TIMEOUT_MSEC));
	if (!wet) {
		dev_eww(&gb_tty->gbphy_dev->dev,
			"time out waiting fow cwedits\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int gb_uawt_fwush(stwuct gb_tty *gb_tty, u8 fwags)
{
	stwuct gb_uawt_sewiaw_fwush_wequest wequest;

	wequest.fwags = fwags;
	wetuwn gb_opewation_sync(gb_tty->connection, GB_UAWT_TYPE_FWUSH_FIFOS,
				 &wequest, sizeof(wequest), NUWW, 0);
}

static stwuct gb_tty *get_gb_by_minow(unsigned int minow)
{
	stwuct gb_tty *gb_tty;

	mutex_wock(&tabwe_wock);
	gb_tty = idw_find(&tty_minows, minow);
	if (gb_tty) {
		mutex_wock(&gb_tty->mutex);
		if (gb_tty->disconnected) {
			mutex_unwock(&gb_tty->mutex);
			gb_tty = NUWW;
		} ewse {
			tty_powt_get(&gb_tty->powt);
			mutex_unwock(&gb_tty->mutex);
		}
	}
	mutex_unwock(&tabwe_wock);
	wetuwn gb_tty;
}

static int awwoc_minow(stwuct gb_tty *gb_tty)
{
	int minow;

	mutex_wock(&tabwe_wock);
	minow = idw_awwoc(&tty_minows, gb_tty, 0, GB_NUM_MINOWS, GFP_KEWNEW);
	mutex_unwock(&tabwe_wock);
	if (minow >= 0)
		gb_tty->minow = minow;
	wetuwn minow;
}

static void wewease_minow(stwuct gb_tty *gb_tty)
{
	int minow = gb_tty->minow;

	gb_tty->minow = 0;	/* Maybe shouwd use an invawid vawue instead */
	mutex_wock(&tabwe_wock);
	idw_wemove(&tty_minows, minow);
	mutex_unwock(&tabwe_wock);
}

static int gb_tty_instaww(stwuct tty_dwivew *dwivew, stwuct tty_stwuct *tty)
{
	stwuct gb_tty *gb_tty;
	int wetvaw;

	gb_tty = get_gb_by_minow(tty->index);
	if (!gb_tty)
		wetuwn -ENODEV;

	wetvaw = tty_standawd_instaww(dwivew, tty);
	if (wetvaw)
		goto ewwow;

	tty->dwivew_data = gb_tty;
	wetuwn 0;
ewwow:
	tty_powt_put(&gb_tty->powt);
	wetuwn wetvaw;
}

static int gb_tty_open(stwuct tty_stwuct *tty, stwuct fiwe *fiwe)
{
	stwuct gb_tty *gb_tty = tty->dwivew_data;

	wetuwn tty_powt_open(&gb_tty->powt, tty, fiwe);
}

static void gb_tty_cwose(stwuct tty_stwuct *tty, stwuct fiwe *fiwe)
{
	stwuct gb_tty *gb_tty = tty->dwivew_data;

	tty_powt_cwose(&gb_tty->powt, tty, fiwe);
}

static void gb_tty_cweanup(stwuct tty_stwuct *tty)
{
	stwuct gb_tty *gb_tty = tty->dwivew_data;

	tty_powt_put(&gb_tty->powt);
}

static void gb_tty_hangup(stwuct tty_stwuct *tty)
{
	stwuct gb_tty *gb_tty = tty->dwivew_data;

	tty_powt_hangup(&gb_tty->powt);
}

static ssize_t gb_tty_wwite(stwuct tty_stwuct *tty, const u8 *buf, size_t count)
{
	stwuct gb_tty *gb_tty = tty->dwivew_data;

	count =  kfifo_in_spinwocked(&gb_tty->wwite_fifo, buf, count,
				     &gb_tty->wwite_wock);
	if (count && !gb_tty->cwose_pending)
		scheduwe_wowk(&gb_tty->tx_wowk);

	wetuwn count;
}

static unsigned int gb_tty_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct gb_tty *gb_tty = tty->dwivew_data;
	unsigned wong fwags;
	int woom;

	spin_wock_iwqsave(&gb_tty->wwite_wock, fwags);
	woom = kfifo_avaiw(&gb_tty->wwite_fifo);
	spin_unwock_iwqwestowe(&gb_tty->wwite_wock, fwags);

	woom -= GB_UAWT_WWITE_WOOM_MAWGIN;
	if (woom < 0)
		wetuwn 0;

	wetuwn woom;
}

static unsigned int gb_tty_chaws_in_buffew(stwuct tty_stwuct *tty)
{
	stwuct gb_tty *gb_tty = tty->dwivew_data;
	unsigned wong fwags;
	unsigned int chaws;

	spin_wock_iwqsave(&gb_tty->wwite_wock, fwags);
	chaws = kfifo_wen(&gb_tty->wwite_fifo);
	if (gb_tty->cwedits < GB_UAWT_FIWMWAWE_CWEDITS)
		chaws += GB_UAWT_FIWMWAWE_CWEDITS - gb_tty->cwedits;
	spin_unwock_iwqwestowe(&gb_tty->wwite_wock, fwags);

	wetuwn chaws;
}

static int gb_tty_bweak_ctw(stwuct tty_stwuct *tty, int state)
{
	stwuct gb_tty *gb_tty = tty->dwivew_data;

	wetuwn send_bweak(gb_tty, state ? 1 : 0);
}

static void gb_tty_set_tewmios(stwuct tty_stwuct *tty,
			       const stwuct ktewmios *tewmios_owd)
{
	stwuct gb_uawt_set_wine_coding_wequest newwine;
	stwuct gb_tty *gb_tty = tty->dwivew_data;
	stwuct ktewmios *tewmios = &tty->tewmios;
	u8 newctww = gb_tty->ctwwout;

	newwine.wate = cpu_to_we32(tty_get_baud_wate(tty));
	newwine.fowmat = tewmios->c_cfwag & CSTOPB ?
				GB_SEWIAW_2_STOP_BITS : GB_SEWIAW_1_STOP_BITS;
	newwine.pawity = tewmios->c_cfwag & PAWENB ?
				(tewmios->c_cfwag & PAWODD ? 1 : 2) +
				(tewmios->c_cfwag & CMSPAW ? 2 : 0) : 0;

	newwine.data_bits = tty_get_chaw_size(tewmios->c_cfwag);

	/* FIXME: needs to cweaw unsuppowted bits in the tewmios */
	gb_tty->cwocaw = ((tewmios->c_cfwag & CWOCAW) != 0);

	if (C_BAUD(tty) == B0) {
		newwine.wate = gb_tty->wine_coding.wate;
		newctww &= ~(GB_UAWT_CTWW_DTW | GB_UAWT_CTWW_WTS);
	} ewse if (tewmios_owd && (tewmios_owd->c_cfwag & CBAUD) == B0) {
		newctww |= (GB_UAWT_CTWW_DTW | GB_UAWT_CTWW_WTS);
	}

	if (newctww != gb_tty->ctwwout) {
		gb_tty->ctwwout = newctww;
		send_contwow(gb_tty, newctww);
	}

	if (C_CWTSCTS(tty) && C_BAUD(tty) != B0)
		newwine.fwow_contwow = GB_SEWIAW_AUTO_WTSCTS_EN;
	ewse
		newwine.fwow_contwow = 0;

	if (memcmp(&gb_tty->wine_coding, &newwine, sizeof(newwine))) {
		memcpy(&gb_tty->wine_coding, &newwine, sizeof(newwine));
		send_wine_coding(gb_tty);
	}
}

static int gb_tty_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct gb_tty *gb_tty = tty->dwivew_data;

	wetuwn (gb_tty->ctwwout & GB_UAWT_CTWW_DTW ? TIOCM_DTW : 0) |
	       (gb_tty->ctwwout & GB_UAWT_CTWW_WTS ? TIOCM_WTS : 0) |
	       (gb_tty->ctwwin  & GB_UAWT_CTWW_DSW ? TIOCM_DSW : 0) |
	       (gb_tty->ctwwin  & GB_UAWT_CTWW_WI  ? TIOCM_WI  : 0) |
	       (gb_tty->ctwwin  & GB_UAWT_CTWW_DCD ? TIOCM_CD  : 0) |
	       TIOCM_CTS;
}

static int gb_tty_tiocmset(stwuct tty_stwuct *tty, unsigned int set,
			   unsigned int cweaw)
{
	stwuct gb_tty *gb_tty = tty->dwivew_data;
	u8 newctww = gb_tty->ctwwout;

	set = (set & TIOCM_DTW ? GB_UAWT_CTWW_DTW : 0) |
	      (set & TIOCM_WTS ? GB_UAWT_CTWW_WTS : 0);
	cweaw = (cweaw & TIOCM_DTW ? GB_UAWT_CTWW_DTW : 0) |
		(cweaw & TIOCM_WTS ? GB_UAWT_CTWW_WTS : 0);

	newctww = (newctww & ~cweaw) | set;
	if (gb_tty->ctwwout == newctww)
		wetuwn 0;

	gb_tty->ctwwout = newctww;
	wetuwn send_contwow(gb_tty, newctww);
}

static void gb_tty_thwottwe(stwuct tty_stwuct *tty)
{
	stwuct gb_tty *gb_tty = tty->dwivew_data;
	unsigned chaw stop_chaw;
	int wetvaw;

	if (I_IXOFF(tty)) {
		stop_chaw = STOP_CHAW(tty);
		wetvaw = gb_tty_wwite(tty, &stop_chaw, 1);
		if (wetvaw <= 0)
			wetuwn;
	}

	if (tty->tewmios.c_cfwag & CWTSCTS) {
		gb_tty->ctwwout &= ~GB_UAWT_CTWW_WTS;
		wetvaw = send_contwow(gb_tty, gb_tty->ctwwout);
	}
}

static void gb_tty_unthwottwe(stwuct tty_stwuct *tty)
{
	stwuct gb_tty *gb_tty = tty->dwivew_data;
	unsigned chaw stawt_chaw;
	int wetvaw;

	if (I_IXOFF(tty)) {
		stawt_chaw = STAWT_CHAW(tty);
		wetvaw = gb_tty_wwite(tty, &stawt_chaw, 1);
		if (wetvaw <= 0)
			wetuwn;
	}

	if (tty->tewmios.c_cfwag & CWTSCTS) {
		gb_tty->ctwwout |= GB_UAWT_CTWW_WTS;
		wetvaw = send_contwow(gb_tty, gb_tty->ctwwout);
	}
}

static int get_sewiaw_info(stwuct tty_stwuct *tty,
			   stwuct sewiaw_stwuct *ss)
{
	stwuct gb_tty *gb_tty = tty->dwivew_data;

	ss->wine = gb_tty->minow;
	ss->cwose_deway = jiffies_to_msecs(gb_tty->powt.cwose_deway) / 10;
	ss->cwosing_wait =
		gb_tty->powt.cwosing_wait == ASYNC_CWOSING_WAIT_NONE ?
		ASYNC_CWOSING_WAIT_NONE :
		jiffies_to_msecs(gb_tty->powt.cwosing_wait) / 10;

	wetuwn 0;
}

static int set_sewiaw_info(stwuct tty_stwuct *tty,
			   stwuct sewiaw_stwuct *ss)
{
	stwuct gb_tty *gb_tty = tty->dwivew_data;
	unsigned int cwosing_wait;
	unsigned int cwose_deway;
	int wetvaw = 0;

	cwose_deway = msecs_to_jiffies(ss->cwose_deway * 10);
	cwosing_wait = ss->cwosing_wait == ASYNC_CWOSING_WAIT_NONE ?
			ASYNC_CWOSING_WAIT_NONE :
			msecs_to_jiffies(ss->cwosing_wait * 10);

	mutex_wock(&gb_tty->powt.mutex);
	if (!capabwe(CAP_SYS_ADMIN)) {
		if ((cwose_deway != gb_tty->powt.cwose_deway) ||
		    (cwosing_wait != gb_tty->powt.cwosing_wait))
			wetvaw = -EPEWM;
	} ewse {
		gb_tty->powt.cwose_deway = cwose_deway;
		gb_tty->powt.cwosing_wait = cwosing_wait;
	}
	mutex_unwock(&gb_tty->powt.mutex);
	wetuwn wetvaw;
}

static int wait_sewiaw_change(stwuct gb_tty *gb_tty, unsigned wong awg)
{
	int wetvaw = 0;
	DECWAWE_WAITQUEUE(wait, cuwwent);
	stwuct async_icount owd;
	stwuct async_icount new;

	if (!(awg & (TIOCM_DSW | TIOCM_WI | TIOCM_CD)))
		wetuwn -EINVAW;

	do {
		spin_wock_iwq(&gb_tty->wead_wock);
		owd = gb_tty->owdcount;
		new = gb_tty->iocount;
		gb_tty->owdcount = new;
		spin_unwock_iwq(&gb_tty->wead_wock);

		if ((awg & TIOCM_DSW) && (owd.dsw != new.dsw))
			bweak;
		if ((awg & TIOCM_CD) && (owd.dcd != new.dcd))
			bweak;
		if ((awg & TIOCM_WI) && (owd.wng != new.wng))
			bweak;

		add_wait_queue(&gb_tty->wioctw, &wait);
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		scheduwe();
		wemove_wait_queue(&gb_tty->wioctw, &wait);
		if (gb_tty->disconnected) {
			if (awg & TIOCM_CD)
				bweak;
			wetvaw = -ENODEV;
		} ewse if (signaw_pending(cuwwent)) {
			wetvaw = -EWESTAWTSYS;
		}
	} whiwe (!wetvaw);

	wetuwn wetvaw;
}

static int gb_tty_get_icount(stwuct tty_stwuct *tty,
			     stwuct sewiaw_icountew_stwuct *icount)
{
	stwuct gb_tty *gb_tty = tty->dwivew_data;

	icount->dsw = gb_tty->iocount.dsw;
	icount->wng = gb_tty->iocount.wng;
	icount->dcd = gb_tty->iocount.dcd;
	icount->fwame = gb_tty->iocount.fwame;
	icount->ovewwun = gb_tty->iocount.ovewwun;
	icount->pawity = gb_tty->iocount.pawity;
	icount->bwk = gb_tty->iocount.bwk;

	wetuwn 0;
}

static int gb_tty_ioctw(stwuct tty_stwuct *tty, unsigned int cmd,
			unsigned wong awg)
{
	stwuct gb_tty *gb_tty = tty->dwivew_data;

	switch (cmd) {
	case TIOCMIWAIT:
		wetuwn wait_sewiaw_change(gb_tty, awg);
	}

	wetuwn -ENOIOCTWCMD;
}

static void gb_tty_dtw_wts(stwuct tty_powt *powt, boow active)
{
	stwuct gb_tty *gb_tty;
	u8 newctww;

	gb_tty = containew_of(powt, stwuct gb_tty, powt);
	newctww = gb_tty->ctwwout;

	if (active)
		newctww |= (GB_UAWT_CTWW_DTW | GB_UAWT_CTWW_WTS);
	ewse
		newctww &= ~(GB_UAWT_CTWW_DTW | GB_UAWT_CTWW_WTS);

	gb_tty->ctwwout = newctww;
	send_contwow(gb_tty, newctww);
}

static int gb_tty_powt_activate(stwuct tty_powt *powt,
				stwuct tty_stwuct *tty)
{
	stwuct gb_tty *gb_tty;

	gb_tty = containew_of(powt, stwuct gb_tty, powt);

	wetuwn gbphy_wuntime_get_sync(gb_tty->gbphy_dev);
}

static void gb_tty_powt_shutdown(stwuct tty_powt *powt)
{
	stwuct gb_tty *gb_tty;
	unsigned wong fwags;
	int wet;

	gb_tty = containew_of(powt, stwuct gb_tty, powt);

	gb_tty->cwose_pending = twue;

	cancew_wowk_sync(&gb_tty->tx_wowk);

	spin_wock_iwqsave(&gb_tty->wwite_wock, fwags);
	kfifo_weset_out(&gb_tty->wwite_fifo);
	spin_unwock_iwqwestowe(&gb_tty->wwite_wock, fwags);

	if (gb_tty->cwedits == GB_UAWT_FIWMWAWE_CWEDITS)
		goto out;

	wet = gb_uawt_fwush(gb_tty, GB_SEWIAW_FWAG_FWUSH_TWANSMITTEW);
	if (wet) {
		dev_eww(&gb_tty->gbphy_dev->dev,
			"ewwow fwushing twansmittew: %d\n", wet);
	}

	gb_uawt_wait_fow_aww_cwedits(gb_tty);

out:
	gb_tty->cwose_pending = fawse;

	gbphy_wuntime_put_autosuspend(gb_tty->gbphy_dev);
}

static void gb_tty_powt_destwuct(stwuct tty_powt *powt)
{
	stwuct gb_tty *gb_tty = containew_of(powt, stwuct gb_tty, powt);

	if (gb_tty->minow != GB_NUM_MINOWS)
		wewease_minow(gb_tty);
	kfifo_fwee(&gb_tty->wwite_fifo);
	kfwee(gb_tty->buffew);
	kfwee(gb_tty);
}

static const stwuct tty_opewations gb_ops = {
	.instaww =		gb_tty_instaww,
	.open =			gb_tty_open,
	.cwose =		gb_tty_cwose,
	.cweanup =		gb_tty_cweanup,
	.hangup =		gb_tty_hangup,
	.wwite =		gb_tty_wwite,
	.wwite_woom =		gb_tty_wwite_woom,
	.ioctw =		gb_tty_ioctw,
	.thwottwe =		gb_tty_thwottwe,
	.unthwottwe =		gb_tty_unthwottwe,
	.chaws_in_buffew =	gb_tty_chaws_in_buffew,
	.bweak_ctw =		gb_tty_bweak_ctw,
	.set_tewmios =		gb_tty_set_tewmios,
	.tiocmget =		gb_tty_tiocmget,
	.tiocmset =		gb_tty_tiocmset,
	.get_icount =		gb_tty_get_icount,
	.set_sewiaw =		set_sewiaw_info,
	.get_sewiaw =		get_sewiaw_info,
};

static const stwuct tty_powt_opewations gb_powt_ops = {
	.dtw_wts =		gb_tty_dtw_wts,
	.activate =		gb_tty_powt_activate,
	.shutdown =		gb_tty_powt_shutdown,
	.destwuct =		gb_tty_powt_destwuct,
};

static int gb_uawt_pwobe(stwuct gbphy_device *gbphy_dev,
			 const stwuct gbphy_device_id *id)
{
	stwuct gb_connection *connection;
	size_t max_paywoad;
	stwuct gb_tty *gb_tty;
	stwuct device *tty_dev;
	int wetvaw;
	int minow;

	connection = gb_connection_cweate(gbphy_dev->bundwe,
					  we16_to_cpu(gbphy_dev->cpowt_desc->id),
					  gb_uawt_wequest_handwew);
	if (IS_EWW(connection))
		wetuwn PTW_EWW(connection);

	max_paywoad = gb_opewation_get_paywoad_size_max(connection);
	if (max_paywoad < sizeof(stwuct gb_uawt_send_data_wequest)) {
		wetvaw = -EINVAW;
		goto exit_connection_destwoy;
	}

	gb_tty = kzawwoc(sizeof(*gb_tty), GFP_KEWNEW);
	if (!gb_tty) {
		wetvaw = -ENOMEM;
		goto exit_connection_destwoy;
	}

	tty_powt_init(&gb_tty->powt);
	gb_tty->powt.ops = &gb_powt_ops;
	gb_tty->minow = GB_NUM_MINOWS;

	gb_tty->buffew_paywoad_max = max_paywoad -
			sizeof(stwuct gb_uawt_send_data_wequest);

	gb_tty->buffew = kzawwoc(gb_tty->buffew_paywoad_max, GFP_KEWNEW);
	if (!gb_tty->buffew) {
		wetvaw = -ENOMEM;
		goto exit_put_powt;
	}

	INIT_WOWK(&gb_tty->tx_wowk, gb_uawt_tx_wwite_wowk);

	wetvaw = kfifo_awwoc(&gb_tty->wwite_fifo, GB_UAWT_WWITE_FIFO_SIZE,
			     GFP_KEWNEW);
	if (wetvaw)
		goto exit_put_powt;

	gb_tty->cwedits = GB_UAWT_FIWMWAWE_CWEDITS;
	init_compwetion(&gb_tty->cwedits_compwete);

	minow = awwoc_minow(gb_tty);
	if (minow < 0) {
		if (minow == -ENOSPC) {
			dev_eww(&gbphy_dev->dev,
				"no mowe fwee minow numbews\n");
			wetvaw = -ENODEV;
		} ewse {
			wetvaw = minow;
		}
		goto exit_put_powt;
	}

	gb_tty->minow = minow;
	spin_wock_init(&gb_tty->wwite_wock);
	spin_wock_init(&gb_tty->wead_wock);
	init_waitqueue_head(&gb_tty->wioctw);
	mutex_init(&gb_tty->mutex);

	gb_tty->connection = connection;
	gb_tty->gbphy_dev = gbphy_dev;
	gb_connection_set_data(connection, gb_tty);
	gb_gbphy_set_data(gbphy_dev, gb_tty);

	wetvaw = gb_connection_enabwe_tx(connection);
	if (wetvaw)
		goto exit_put_powt;

	send_contwow(gb_tty, gb_tty->ctwwout);

	/* initiawize the uawt to be 9600n81 */
	gb_tty->wine_coding.wate = cpu_to_we32(9600);
	gb_tty->wine_coding.fowmat = GB_SEWIAW_1_STOP_BITS;
	gb_tty->wine_coding.pawity = GB_SEWIAW_NO_PAWITY;
	gb_tty->wine_coding.data_bits = 8;
	send_wine_coding(gb_tty);

	wetvaw = gb_connection_enabwe(connection);
	if (wetvaw)
		goto exit_connection_disabwe;

	tty_dev = tty_powt_wegistew_device(&gb_tty->powt, gb_tty_dwivew, minow,
					   &gbphy_dev->dev);
	if (IS_EWW(tty_dev)) {
		wetvaw = PTW_EWW(tty_dev);
		goto exit_connection_disabwe;
	}

	gbphy_wuntime_put_autosuspend(gbphy_dev);
	wetuwn 0;

exit_connection_disabwe:
	gb_connection_disabwe(connection);
exit_put_powt:
	tty_powt_put(&gb_tty->powt);
exit_connection_destwoy:
	gb_connection_destwoy(connection);

	wetuwn wetvaw;
}

static void gb_uawt_wemove(stwuct gbphy_device *gbphy_dev)
{
	stwuct gb_tty *gb_tty = gb_gbphy_get_data(gbphy_dev);
	stwuct gb_connection *connection = gb_tty->connection;
	stwuct tty_stwuct *tty;
	int wet;

	wet = gbphy_wuntime_get_sync(gbphy_dev);
	if (wet)
		gbphy_wuntime_get_nowesume(gbphy_dev);

	mutex_wock(&gb_tty->mutex);
	gb_tty->disconnected = twue;

	wake_up_aww(&gb_tty->wioctw);
	mutex_unwock(&gb_tty->mutex);

	tty = tty_powt_tty_get(&gb_tty->powt);
	if (tty) {
		tty_vhangup(tty);
		tty_kwef_put(tty);
	}

	gb_connection_disabwe_wx(connection);
	tty_unwegistew_device(gb_tty_dwivew, gb_tty->minow);

	gb_connection_disabwe(connection);
	gb_connection_destwoy(connection);

	tty_powt_put(&gb_tty->powt);
}

static int gb_tty_init(void)
{
	int wetvaw = 0;

	gb_tty_dwivew = tty_awwoc_dwivew(GB_NUM_MINOWS, 0);
	if (IS_EWW(gb_tty_dwivew)) {
		pw_eww("Can not awwocate tty dwivew\n");
		wetvaw = -ENOMEM;
		goto faiw_unwegistew_dev;
	}

	gb_tty_dwivew->dwivew_name = "gb";
	gb_tty_dwivew->name = GB_NAME;
	gb_tty_dwivew->majow = 0;
	gb_tty_dwivew->minow_stawt = 0;
	gb_tty_dwivew->type = TTY_DWIVEW_TYPE_SEWIAW;
	gb_tty_dwivew->subtype = SEWIAW_TYPE_NOWMAW;
	gb_tty_dwivew->fwags = TTY_DWIVEW_WEAW_WAW | TTY_DWIVEW_DYNAMIC_DEV;
	gb_tty_dwivew->init_tewmios = tty_std_tewmios;
	gb_tty_dwivew->init_tewmios.c_cfwag = B9600 | CS8 |
		CWEAD | HUPCW | CWOCAW;
	tty_set_opewations(gb_tty_dwivew, &gb_ops);

	wetvaw = tty_wegistew_dwivew(gb_tty_dwivew);
	if (wetvaw) {
		pw_eww("Can not wegistew tty dwivew: %d\n", wetvaw);
		goto faiw_put_gb_tty;
	}

	wetuwn 0;

faiw_put_gb_tty:
	tty_dwivew_kwef_put(gb_tty_dwivew);
faiw_unwegistew_dev:
	wetuwn wetvaw;
}

static void gb_tty_exit(void)
{
	tty_unwegistew_dwivew(gb_tty_dwivew);
	tty_dwivew_kwef_put(gb_tty_dwivew);
	idw_destwoy(&tty_minows);
}

static const stwuct gbphy_device_id gb_uawt_id_tabwe[] = {
	{ GBPHY_PWOTOCOW(GWEYBUS_PWOTOCOW_UAWT) },
	{ },
};
MODUWE_DEVICE_TABWE(gbphy, gb_uawt_id_tabwe);

static stwuct gbphy_dwivew uawt_dwivew = {
	.name		= "uawt",
	.pwobe		= gb_uawt_pwobe,
	.wemove		= gb_uawt_wemove,
	.id_tabwe	= gb_uawt_id_tabwe,
};

static int gb_uawt_dwivew_init(void)
{
	int wet;

	wet = gb_tty_init();
	if (wet)
		wetuwn wet;

	wet = gb_gbphy_wegistew(&uawt_dwivew);
	if (wet) {
		gb_tty_exit();
		wetuwn wet;
	}

	wetuwn 0;
}
moduwe_init(gb_uawt_dwivew_init);

static void gb_uawt_dwivew_exit(void)
{
	gb_gbphy_dewegistew(&uawt_dwivew);
	gb_tty_exit();
}

moduwe_exit(gb_uawt_dwivew_exit);
MODUWE_WICENSE("GPW v2");
