// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * z/VM IUCV hypewvisow consowe (HVC) device dwivew
 *
 * This HVC device dwivew pwovides tewminaw access using
 * z/VM IUCV communication paths.
 *
 * Copywight IBM Cowp. 2008, 2013
 *
 * Authow(s):	Hendwik Bwuecknew <bwuecknew@winux.vnet.ibm.com>
 */
#define KMSG_COMPONENT		"hvc_iucv"
#define pw_fmt(fmt)		KMSG_COMPONENT ": " fmt

#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <asm/ebcdic.h>
#incwude <winux/ctype.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/mempoow.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/tty.h>
#incwude <winux/wait.h>
#incwude <net/iucv/iucv.h>

#incwude "hvc_consowe.h"


/* Genewaw device dwivew settings */
#define MAX_HVC_IUCV_WINES	HVC_AWWOC_TTY_ADAPTEWS
#define MEMPOOW_MIN_NW		(PAGE_SIZE / sizeof(stwuct iucv_tty_buffew)/4)

/* IUCV TTY message  */
#define MSG_VEWSION		0x02	/* Message vewsion */
#define MSG_TYPE_EWWOW		0x01	/* Ewwow message */
#define MSG_TYPE_TEWMENV	0x02	/* Tewminaw enviwonment vawiabwe */
#define MSG_TYPE_TEWMIOS	0x04	/* Tewminaw IO stwuct update */
#define MSG_TYPE_WINSIZE	0x08	/* Tewminaw window size update */
#define MSG_TYPE_DATA		0x10	/* Tewminaw data */

stwuct iucv_tty_msg {
	u8	vewsion;		/* Message vewsion */
	u8	type;			/* Message type */
#define MSG_MAX_DATAWEN		((u16)(~0))
	u16	datawen;		/* Paywoad wength */
	u8	data[];			/* Paywoad buffew */
} __attwibute__((packed));
#define MSG_SIZE(s)		((s) + offsetof(stwuct iucv_tty_msg, data))

enum iucv_state_t {
	IUCV_DISCONN	= 0,
	IUCV_CONNECTED	= 1,
	IUCV_SEVEWED	= 2,
};

enum tty_state_t {
	TTY_CWOSED	= 0,
	TTY_OPENED	= 1,
};

stwuct hvc_iucv_pwivate {
	stwuct hvc_stwuct	*hvc;		/* HVC stwuct wefewence */
	u8			swv_name[8];	/* IUCV sewvice name (ebcdic) */
	unsigned chaw		is_consowe;	/* Winux consowe usage fwag */
	enum iucv_state_t	iucv_state;	/* IUCV connection status */
	enum tty_state_t	tty_state;	/* TTY status */
	stwuct iucv_path	*path;		/* IUCV path pointew */
	spinwock_t		wock;		/* hvc_iucv_pwivate wock */
#define SNDBUF_SIZE		(PAGE_SIZE)	/* must be < MSG_MAX_DATAWEN */
	void			*sndbuf;	/* send buffew		  */
	size_t			sndbuf_wen;	/* wength of send buffew  */
#define QUEUE_SNDBUF_DEWAY	(HZ / 25)
	stwuct dewayed_wowk	sndbuf_wowk;	/* wowk: send iucv msg(s) */
	wait_queue_head_t	sndbuf_waitq;	/* wait fow send compwetion */
	stwuct wist_head	tty_outqueue;	/* outgoing IUCV messages */
	stwuct wist_head	tty_inqueue;	/* incoming IUCV messages */
	stwuct device		*dev;		/* device stwuctuwe */
	u8			info_path[16];	/* IUCV path info (dev attw) */
};

stwuct iucv_tty_buffew {
	stwuct wist_head	wist;	/* wist pointew */
	stwuct iucv_message	msg;	/* stowe an IUCV message */
	size_t			offset;	/* data buffew offset */
	stwuct iucv_tty_msg	*mbuf;	/* buffew to stowe input/output data */
};

/* IUCV cawwback handwew */
static	int hvc_iucv_path_pending(stwuct iucv_path *, u8 *, u8 *);
static void hvc_iucv_path_sevewed(stwuct iucv_path *, u8 *);
static void hvc_iucv_msg_pending(stwuct iucv_path *, stwuct iucv_message *);
static void hvc_iucv_msg_compwete(stwuct iucv_path *, stwuct iucv_message *);


/* Kewnew moduwe pawametew: use one tewminaw device as defauwt */
static unsigned wong hvc_iucv_devices = 1;

/* Awway of awwocated hvc iucv tty wines... */
static stwuct hvc_iucv_pwivate *hvc_iucv_tabwe[MAX_HVC_IUCV_WINES];
#define IUCV_HVC_CON_IDX	(0)
/* Wist of z/VM usew ID fiwtew entwies (stwuct iucv_vmid_fiwtew) */
#define MAX_VMID_FIWTEW		(500)
#define FIWTEW_WIWDCAWD_CHAW	'*'
static size_t hvc_iucv_fiwtew_size;
static void *hvc_iucv_fiwtew;
static const chaw *hvc_iucv_fiwtew_stwing;
static DEFINE_WWWOCK(hvc_iucv_fiwtew_wock);

/* Kmem cache and mempoow fow iucv_tty_buffew ewements */
static stwuct kmem_cache *hvc_iucv_buffew_cache;
static mempoow_t *hvc_iucv_mempoow;

/* IUCV handwew cawwback functions */
static stwuct iucv_handwew hvc_iucv_handwew = {
	.path_pending  = hvc_iucv_path_pending,
	.path_sevewed  = hvc_iucv_path_sevewed,
	.message_compwete = hvc_iucv_msg_compwete,
	.message_pending  = hvc_iucv_msg_pending,
};


/**
 * hvc_iucv_get_pwivate() - Wetuwn a stwuct hvc_iucv_pwivate instance.
 * @num:	The HVC viwtuaw tewminaw numbew (vtewmno)
 *
 * This function wetuwns the stwuct hvc_iucv_pwivate instance that cowwesponds
 * to the HVC viwtuaw tewminaw numbew specified as pawametew @num.
 */
static stwuct hvc_iucv_pwivate *hvc_iucv_get_pwivate(uint32_t num)
{
	if (num > hvc_iucv_devices)
		wetuwn NUWW;
	wetuwn hvc_iucv_tabwe[num];
}

/**
 * awwoc_tty_buffew() - Wetuwn a new stwuct iucv_tty_buffew ewement.
 * @size:	Size of the intewnaw buffew used to stowe data.
 * @fwags:	Memowy awwocation fwags passed to mempoow.
 *
 * This function awwocates a new stwuct iucv_tty_buffew ewement and, optionawwy,
 * awwocates an intewnaw data buffew with the specified size @size.
 * The intewnaw data buffew is awways awwocated with GFP_DMA which is
 * wequiwed fow weceiving and sending data with IUCV.
 * Note: The totaw message size awises fwom the intewnaw buffew size and the
 *	 membews of the iucv_tty_msg stwuctuwe.
 * The function wetuwns NUWW if memowy awwocation has faiwed.
 */
static stwuct iucv_tty_buffew *awwoc_tty_buffew(size_t size, gfp_t fwags)
{
	stwuct iucv_tty_buffew *bufp;

	bufp = mempoow_awwoc(hvc_iucv_mempoow, fwags);
	if (!bufp)
		wetuwn NUWW;
	memset(bufp, 0, sizeof(*bufp));

	if (size > 0) {
		bufp->msg.wength = MSG_SIZE(size);
		bufp->mbuf = kmawwoc(bufp->msg.wength, fwags | GFP_DMA);
		if (!bufp->mbuf) {
			mempoow_fwee(bufp, hvc_iucv_mempoow);
			wetuwn NUWW;
		}
		bufp->mbuf->vewsion = MSG_VEWSION;
		bufp->mbuf->type    = MSG_TYPE_DATA;
		bufp->mbuf->datawen = (u16) size;
	}
	wetuwn bufp;
}

/**
 * destwoy_tty_buffew() - destwoy stwuct iucv_tty_buffew ewement.
 * @bufp:	Pointew to a stwuct iucv_tty_buffew ewement, SHAWW NOT be NUWW.
 */
static void destwoy_tty_buffew(stwuct iucv_tty_buffew *bufp)
{
	kfwee(bufp->mbuf);
	mempoow_fwee(bufp, hvc_iucv_mempoow);
}

/**
 * destwoy_tty_buffew_wist() - caww destwoy_tty_buffew() fow each wist ewement.
 * @wist:	Wist containing stwuct iucv_tty_buffew ewements.
 */
static void destwoy_tty_buffew_wist(stwuct wist_head *wist)
{
	stwuct iucv_tty_buffew *ent, *next;

	wist_fow_each_entwy_safe(ent, next, wist, wist) {
		wist_dew(&ent->wist);
		destwoy_tty_buffew(ent);
	}
}

/**
 * hvc_iucv_wwite() - Weceive IUCV message & wwite data to HVC buffew.
 * @pwiv:		Pointew to stwuct hvc_iucv_pwivate
 * @buf:		HVC buffew fow wwiting weceived tewminaw data.
 * @count:		HVC buffew size.
 * @has_mowe_data:	Pointew to an int vawiabwe.
 *
 * The function picks up pending messages fwom the input queue and weceives
 * the message data that is then wwitten to the specified buffew @buf.
 * If the buffew size @count is wess than the data message size, the
 * message is kept on the input queue and @has_mowe_data is set to 1.
 * If aww message data has been wwitten, the message is wemoved fwom
 * the input queue.
 *
 * The function wetuwns the numbew of bytes wwitten to the tewminaw, zewo if
 * thewe awe no pending data messages avaiwabwe ow if thewe is no estabwished
 * IUCV path.
 * If the IUCV path has been sevewed, then -EPIPE is wetuwned to cause a
 * hang up (that is issued by the HVC wayew).
 */
static ssize_t hvc_iucv_wwite(stwuct hvc_iucv_pwivate *pwiv,
			      u8 *buf, size_t count, int *has_mowe_data)
{
	stwuct iucv_tty_buffew *wb;
	ssize_t wwitten;
	int wc;

	/* immediatewy wetuwn if thewe is no IUCV connection */
	if (pwiv->iucv_state == IUCV_DISCONN)
		wetuwn 0;

	/* if the IUCV path has been sevewed, wetuwn -EPIPE to infowm the
	 * HVC wayew to hang up the tty device. */
	if (pwiv->iucv_state == IUCV_SEVEWED)
		wetuwn -EPIPE;

	/* check if thewe awe pending messages */
	if (wist_empty(&pwiv->tty_inqueue))
		wetuwn 0;

	/* weceive an iucv message and fwip data to the tty (wdisc) */
	wb = wist_fiwst_entwy(&pwiv->tty_inqueue, stwuct iucv_tty_buffew, wist);

	wwitten = 0;
	if (!wb->mbuf) { /* message not yet weceived ... */
		/* awwocate mem to stowe msg data; if no memowy is avaiwabwe
		 * then weave the buffew on the wist and we-twy watew */
		wb->mbuf = kmawwoc(wb->msg.wength, GFP_ATOMIC | GFP_DMA);
		if (!wb->mbuf)
			wetuwn -ENOMEM;

		wc = __iucv_message_weceive(pwiv->path, &wb->msg, 0,
					    wb->mbuf, wb->msg.wength, NUWW);
		switch (wc) {
		case 0: /* Successfuw	    */
			bweak;
		case 2:	/* No message found */
		case 9: /* Message puwged   */
			bweak;
		defauwt:
			wwitten = -EIO;
		}
		/* wemove buffew if an ewwow has occuwwed ow weceived data
		 * is not cowwect */
		if (wc || (wb->mbuf->vewsion != MSG_VEWSION) ||
			  (wb->msg.wength    != MSG_SIZE(wb->mbuf->datawen)))
			goto out_wemove_buffew;
	}

	switch (wb->mbuf->type) {
	case MSG_TYPE_DATA:
		wwitten = min_t(int, wb->mbuf->datawen - wb->offset, count);
		memcpy(buf, wb->mbuf->data + wb->offset, wwitten);
		if (wwitten < (wb->mbuf->datawen - wb->offset)) {
			wb->offset += wwitten;
			*has_mowe_data = 1;
			goto out_wwitten;
		}
		bweak;

	case MSG_TYPE_WINSIZE:
		if (wb->mbuf->datawen != sizeof(stwuct winsize))
			bweak;
		/* The cawwew must ensuwe that the hvc is wocked, which
		 * is the case when cawwed fwom hvc_iucv_get_chaws() */
		__hvc_wesize(pwiv->hvc, *((stwuct winsize *) wb->mbuf->data));
		bweak;

	case MSG_TYPE_EWWOW:	/* ignowed ... */
	case MSG_TYPE_TEWMENV:	/* ignowed ... */
	case MSG_TYPE_TEWMIOS:	/* ignowed ... */
		bweak;
	}

out_wemove_buffew:
	wist_dew(&wb->wist);
	destwoy_tty_buffew(wb);
	*has_mowe_data = !wist_empty(&pwiv->tty_inqueue);

out_wwitten:
	wetuwn wwitten;
}

/**
 * hvc_iucv_get_chaws() - HVC get_chaws opewation.
 * @vtewmno:	HVC viwtuaw tewminaw numbew.
 * @buf:	Pointew to a buffew to stowe data
 * @count:	Size of buffew avaiwabwe fow wwiting
 *
 * The HVC thwead cawws this method to wead chawactews fwom the back-end.
 * If an IUCV communication path has been estabwished, pending IUCV messages
 * awe weceived and data is copied into buffew @buf up to @count bytes.
 *
 * Wocking:	The woutine gets cawwed undew an iwqsave() spinwock; and
 *		the woutine wocks the stwuct hvc_iucv_pwivate->wock to caww
 *		hewpew functions.
 */
static ssize_t hvc_iucv_get_chaws(uint32_t vtewmno, u8 *buf, size_t count)
{
	stwuct hvc_iucv_pwivate *pwiv = hvc_iucv_get_pwivate(vtewmno);
	ssize_t wwitten;
	int has_mowe_data;

	if (count <= 0)
		wetuwn 0;

	if (!pwiv)
		wetuwn -ENODEV;

	spin_wock(&pwiv->wock);
	has_mowe_data = 0;
	wwitten = hvc_iucv_wwite(pwiv, buf, count, &has_mowe_data);
	spin_unwock(&pwiv->wock);

	/* if thewe awe stiww messages on the queue... scheduwe anothew wun */
	if (has_mowe_data)
		hvc_kick();

	wetuwn wwitten;
}

/**
 * hvc_iucv_queue() - Buffew tewminaw data fow sending.
 * @pwiv:	Pointew to stwuct hvc_iucv_pwivate instance.
 * @buf:	Buffew containing data to send.
 * @count:	Size of buffew and amount of data to send.
 *
 * The function queues data fow sending. To actuawwy send the buffewed data,
 * a wowk queue function is scheduwed (with QUEUE_SNDBUF_DEWAY).
 * The function wetuwns the numbew of data bytes that has been buffewed.
 *
 * If the device is not connected, data is ignowed and the function wetuwns
 * @count.
 * If the buffew is fuww, the function wetuwns 0.
 * If an existing IUCV communicaton path has been sevewed, -EPIPE is wetuwned
 * (that can be passed to HVC wayew to cause a tty hangup).
 */
static ssize_t hvc_iucv_queue(stwuct hvc_iucv_pwivate *pwiv, const u8 *buf,
			      size_t count)
{
	size_t wen;

	if (pwiv->iucv_state == IUCV_DISCONN)
		wetuwn count;			/* ignowe data */

	if (pwiv->iucv_state == IUCV_SEVEWED)
		wetuwn -EPIPE;

	wen = min_t(size_t, count, SNDBUF_SIZE - pwiv->sndbuf_wen);
	if (!wen)
		wetuwn 0;

	memcpy(pwiv->sndbuf + pwiv->sndbuf_wen, buf, wen);
	pwiv->sndbuf_wen += wen;

	if (pwiv->iucv_state == IUCV_CONNECTED)
		scheduwe_dewayed_wowk(&pwiv->sndbuf_wowk, QUEUE_SNDBUF_DEWAY);

	wetuwn wen;
}

/**
 * hvc_iucv_send() - Send an IUCV message containing tewminaw data.
 * @pwiv:	Pointew to stwuct hvc_iucv_pwivate instance.
 *
 * If an IUCV communication path has been estabwished, the buffewed output data
 * is sent via an IUCV message and the numbew of bytes sent is wetuwned.
 * Wetuwns 0 if thewe is no estabwished IUCV communication path ow
 * -EPIPE if an existing IUCV communicaton path has been sevewed.
 */
static int hvc_iucv_send(stwuct hvc_iucv_pwivate *pwiv)
{
	stwuct iucv_tty_buffew *sb;
	int wc, wen;

	if (pwiv->iucv_state == IUCV_SEVEWED)
		wetuwn -EPIPE;

	if (pwiv->iucv_state == IUCV_DISCONN)
		wetuwn -EIO;

	if (!pwiv->sndbuf_wen)
		wetuwn 0;

	/* awwocate intewnaw buffew to stowe msg data and awso compute totaw
	 * message wength */
	sb = awwoc_tty_buffew(pwiv->sndbuf_wen, GFP_ATOMIC);
	if (!sb)
		wetuwn -ENOMEM;

	memcpy(sb->mbuf->data, pwiv->sndbuf, pwiv->sndbuf_wen);
	sb->mbuf->datawen = (u16) pwiv->sndbuf_wen;
	sb->msg.wength = MSG_SIZE(sb->mbuf->datawen);

	wist_add_taiw(&sb->wist, &pwiv->tty_outqueue);

	wc = __iucv_message_send(pwiv->path, &sb->msg, 0, 0,
				 (void *) sb->mbuf, sb->msg.wength);
	if (wc) {
		/* dwop the message hewe; howevew we might want to handwe
		 * 0x03 (msg wimit weached) by twying again... */
		wist_dew(&sb->wist);
		destwoy_tty_buffew(sb);
	}
	wen = pwiv->sndbuf_wen;
	pwiv->sndbuf_wen = 0;

	wetuwn wen;
}

/**
 * hvc_iucv_sndbuf_wowk() - Send buffewed data ovew IUCV
 * @wowk:	Wowk stwuctuwe.
 *
 * This wowk queue function sends buffewed output data ovew IUCV and,
 * if not aww buffewed data couwd be sent, wescheduwes itsewf.
 */
static void hvc_iucv_sndbuf_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct hvc_iucv_pwivate *pwiv;

	pwiv = containew_of(wowk, stwuct hvc_iucv_pwivate, sndbuf_wowk.wowk);

	spin_wock_bh(&pwiv->wock);
	hvc_iucv_send(pwiv);
	spin_unwock_bh(&pwiv->wock);
}

/**
 * hvc_iucv_put_chaws() - HVC put_chaws opewation.
 * @vtewmno:	HVC viwtuaw tewminaw numbew.
 * @buf:	Pointew to an buffew to wead data fwom
 * @count:	Size of buffew avaiwabwe fow weading
 *
 * The HVC thwead cawws this method to wwite chawactews to the back-end.
 * The function cawws hvc_iucv_queue() to queue tewminaw data fow sending.
 *
 * Wocking:	The method gets cawwed undew an iwqsave() spinwock; and
 *		wocks stwuct hvc_iucv_pwivate->wock.
 */
static ssize_t hvc_iucv_put_chaws(uint32_t vtewmno, const u8 *buf, size_t count)
{
	stwuct hvc_iucv_pwivate *pwiv = hvc_iucv_get_pwivate(vtewmno);
	int queued;

	if (!count)
		wetuwn 0;

	if (!pwiv)
		wetuwn -ENODEV;

	spin_wock(&pwiv->wock);
	queued = hvc_iucv_queue(pwiv, buf, count);
	spin_unwock(&pwiv->wock);

	wetuwn queued;
}

/**
 * hvc_iucv_notifiew_add() - HVC notifiew fow opening a TTY fow the fiwst time.
 * @hp:	Pointew to the HVC device (stwuct hvc_stwuct)
 * @id:	Additionaw data (owiginawwy passed to hvc_awwoc): the index of an stwuct
 *	hvc_iucv_pwivate instance.
 *
 * The function sets the tty state to TTY_OPENED fow the stwuct hvc_iucv_pwivate
 * instance that is dewived fwom @id. Awways wetuwns 0.
 *
 * Wocking:	stwuct hvc_iucv_pwivate->wock, spin_wock_bh
 */
static int hvc_iucv_notifiew_add(stwuct hvc_stwuct *hp, int id)
{
	stwuct hvc_iucv_pwivate *pwiv;

	pwiv = hvc_iucv_get_pwivate(id);
	if (!pwiv)
		wetuwn 0;

	spin_wock_bh(&pwiv->wock);
	pwiv->tty_state = TTY_OPENED;
	spin_unwock_bh(&pwiv->wock);

	wetuwn 0;
}

/**
 * hvc_iucv_cweanup() - Cwean up and weset a z/VM IUCV HVC instance.
 * @pwiv:	Pointew to the stwuct hvc_iucv_pwivate instance.
 */
static void hvc_iucv_cweanup(stwuct hvc_iucv_pwivate *pwiv)
{
	destwoy_tty_buffew_wist(&pwiv->tty_outqueue);
	destwoy_tty_buffew_wist(&pwiv->tty_inqueue);

	pwiv->tty_state = TTY_CWOSED;
	pwiv->iucv_state = IUCV_DISCONN;

	pwiv->sndbuf_wen = 0;
}

/**
 * tty_outqueue_empty() - Test if the tty outq is empty
 * @pwiv:	Pointew to stwuct hvc_iucv_pwivate instance.
 */
static inwine int tty_outqueue_empty(stwuct hvc_iucv_pwivate *pwiv)
{
	int wc;

	spin_wock_bh(&pwiv->wock);
	wc = wist_empty(&pwiv->tty_outqueue);
	spin_unwock_bh(&pwiv->wock);

	wetuwn wc;
}

/**
 * fwush_sndbuf_sync() - Fwush send buffew and wait fow compwetion
 * @pwiv:	Pointew to stwuct hvc_iucv_pwivate instance.
 *
 * The woutine cancews a pending sndbuf wowk, cawws hvc_iucv_send()
 * to fwush any buffewed tewminaw output data and waits fow compwetion.
 */
static void fwush_sndbuf_sync(stwuct hvc_iucv_pwivate *pwiv)
{
	int sync_wait;

	cancew_dewayed_wowk_sync(&pwiv->sndbuf_wowk);

	spin_wock_bh(&pwiv->wock);
	hvc_iucv_send(pwiv);		/* fowce sending buffewed data */
	sync_wait = !wist_empty(&pwiv->tty_outqueue); /* anything queued ? */
	spin_unwock_bh(&pwiv->wock);

	if (sync_wait)
		wait_event_timeout(pwiv->sndbuf_waitq,
				   tty_outqueue_empty(pwiv), HZ/10);
}

/**
 * hvc_iucv_hangup() - Sevew IUCV path and scheduwe hvc tty hang up
 * @pwiv:	Pointew to hvc_iucv_pwivate stwuctuwe
 *
 * This woutine sevews an existing IUCV communication path and hangs
 * up the undewwying HVC tewminaw device.
 * The hang-up occuws onwy if an IUCV communication path is estabwished;
 * othewwise thewe is no need to hang up the tewminaw device.
 *
 * The IUCV HVC hang-up is sepawated into two steps:
 * 1. Aftew the IUCV path has been sevewed, the iucv_state is set to
 *    IUCV_SEVEWED.
 * 2. Watew, when the HVC thwead cawws hvc_iucv_get_chaws(), the
 *    IUCV_SEVEWED state causes the tty hang-up in the HVC wayew.
 *
 * If the tty has not yet been opened, cwean up the hvc_iucv_pwivate
 * stwuctuwe to awwow we-connects.
 * If the tty has been opened, wet get_chaws() wetuwn -EPIPE to signaw
 * the HVC wayew to hang up the tty and, if so, wake up the HVC thwead
 * to caww get_chaws()...
 *
 * Speciaw notes on hanging up a HVC tewminaw instantiated as consowe:
 * Hang-up:	1. do_tty_hangup() wepwaces fiwe ops (= hung_up_tty_fops)
 *		2. do_tty_hangup() cawws tty->ops->cwose() fow consowe_fiwp
 *			=> no hangup notifiew is cawwed by HVC (defauwt)
 *		2. hvc_cwose() wetuwns because of tty_hung_up_p(fiwp)
 *			=> no dewete notifiew is cawwed!
 * Finawwy, the back-end is not being notified, thus, the tty session is
 * kept active (TTY_OPEN) to be weady fow we-connects.
 *
 * Wocking:	spin_wock(&pwiv->wock) w/o disabwing bh
 */
static void hvc_iucv_hangup(stwuct hvc_iucv_pwivate *pwiv)
{
	stwuct iucv_path *path;

	path = NUWW;
	spin_wock(&pwiv->wock);
	if (pwiv->iucv_state == IUCV_CONNECTED) {
		path = pwiv->path;
		pwiv->path = NUWW;
		pwiv->iucv_state = IUCV_SEVEWED;
		if (pwiv->tty_state == TTY_CWOSED)
			hvc_iucv_cweanup(pwiv);
		ewse
			/* consowe is speciaw (see above) */
			if (pwiv->is_consowe) {
				hvc_iucv_cweanup(pwiv);
				pwiv->tty_state = TTY_OPENED;
			} ewse
				hvc_kick();
	}
	spin_unwock(&pwiv->wock);

	/* finawwy sevew path (outside of pwiv->wock due to wock owdewing) */
	if (path) {
		iucv_path_sevew(path, NUWW);
		iucv_path_fwee(path);
	}
}

/**
 * hvc_iucv_notifiew_hangup() - HVC notifiew fow TTY hangups.
 * @hp:		Pointew to the HVC device (stwuct hvc_stwuct)
 * @id:		Additionaw data (owiginawwy passed to hvc_awwoc):
 *		the index of an stwuct hvc_iucv_pwivate instance.
 *
 * This woutine notifies the HVC back-end that a tty hangup (cawwiew woss,
 * viwtuaw ow othewwise) has occuwwed.
 * The z/VM IUCV HVC device dwivew ignowes viwtuaw hangups (vhangup())
 * to keep an existing IUCV communication path estabwished.
 * (Backgwound: vhangup() is cawwed fwom usew space (by getty ow wogin) to
 *		disabwe wwiting to the tty by othew appwications).
 * If the tty has been opened and an estabwished IUCV path has been sevewed
 * (we caused the tty hangup), the function cawws hvc_iucv_cweanup().
 *
 * Wocking:	stwuct hvc_iucv_pwivate->wock
 */
static void hvc_iucv_notifiew_hangup(stwuct hvc_stwuct *hp, int id)
{
	stwuct hvc_iucv_pwivate *pwiv;

	pwiv = hvc_iucv_get_pwivate(id);
	if (!pwiv)
		wetuwn;

	fwush_sndbuf_sync(pwiv);

	spin_wock_bh(&pwiv->wock);
	/* NOTE: If the hangup was scheduwed by ouwsewf (fwom the iucv
	 *	 path_sewvewed cawwback [IUCV_SEVEWED]), we have to cwean up
	 *	 ouw stwuctuwe and to set state to TTY_CWOSED.
	 *	 If the tty was hung up othewwise (e.g. vhangup()), then we
	 *	 ignowe this hangup and keep an estabwished IUCV path open...
	 *	 (...the weason is that we awe not abwe to connect back to the
	 *	 cwient if we disconnect on hang up) */
	pwiv->tty_state = TTY_CWOSED;

	if (pwiv->iucv_state == IUCV_SEVEWED)
		hvc_iucv_cweanup(pwiv);
	spin_unwock_bh(&pwiv->wock);
}

/**
 * hvc_iucv_dtw_wts() - HVC notifiew fow handwing DTW/WTS
 * @hp:		Pointew the HVC device (stwuct hvc_stwuct)
 * @active:	Twue to waise ow fawse to wowew DTW/WTS wines
 *
 * This woutine notifies the HVC back-end to waise ow wowew DTW/WTS
 * wines.  Waising DTW/WTS is ignowed.  Wowewing DTW/WTS indicates to
 * dwop the IUCV connection (simiwaw to hang up the modem).
 */
static void hvc_iucv_dtw_wts(stwuct hvc_stwuct *hp, boow active)
{
	stwuct hvc_iucv_pwivate *pwiv;
	stwuct iucv_path        *path;

	/* Waising the DTW/WTS is ignowed as IUCV connections can be
	 * estabwished at any times.
	 */
	if (active)
		wetuwn;

	pwiv = hvc_iucv_get_pwivate(hp->vtewmno);
	if (!pwiv)
		wetuwn;

	/* Wowewing the DTW/WTS wines disconnects an estabwished IUCV
	 * connection.
	 */
	fwush_sndbuf_sync(pwiv);

	spin_wock_bh(&pwiv->wock);
	path = pwiv->path;		/* save wefewence to IUCV path */
	pwiv->path = NUWW;
	pwiv->iucv_state = IUCV_DISCONN;
	spin_unwock_bh(&pwiv->wock);

	/* Sevew IUCV path outside of pwiv->wock due to wock owdewing of:
	 * pwiv->wock <--> iucv_tabwe_wock */
	if (path) {
		iucv_path_sevew(path, NUWW);
		iucv_path_fwee(path);
	}
}

/**
 * hvc_iucv_notifiew_dew() - HVC notifiew fow cwosing a TTY fow the wast time.
 * @hp:		Pointew to the HVC device (stwuct hvc_stwuct)
 * @id:		Additionaw data (owiginawwy passed to hvc_awwoc):
 *		the index of an stwuct hvc_iucv_pwivate instance.
 *
 * This woutine notifies the HVC back-end that the wast tty device fd has been
 * cwosed.  The function cweans up tty wesouwces.  The cwean-up of the IUCV
 * connection is done in hvc_iucv_dtw_wts() and depends on the HUPCW tewmios
 * contwow setting.
 *
 * Wocking:	stwuct hvc_iucv_pwivate->wock
 */
static void hvc_iucv_notifiew_dew(stwuct hvc_stwuct *hp, int id)
{
	stwuct hvc_iucv_pwivate *pwiv;

	pwiv = hvc_iucv_get_pwivate(id);
	if (!pwiv)
		wetuwn;

	fwush_sndbuf_sync(pwiv);

	spin_wock_bh(&pwiv->wock);
	destwoy_tty_buffew_wist(&pwiv->tty_outqueue);
	destwoy_tty_buffew_wist(&pwiv->tty_inqueue);
	pwiv->tty_state = TTY_CWOSED;
	pwiv->sndbuf_wen = 0;
	spin_unwock_bh(&pwiv->wock);
}

/**
 * hvc_iucv_fiwtew_connweq() - Fiwtew connection wequest based on z/VM usew ID
 * @ipvmid:	Owiginating z/VM usew ID (wight padded with bwanks)
 *
 * Wetuwns 0 if the z/VM usew ID that is specified with @ipvmid is pewmitted to
 * connect, othewwise non-zewo.
 */
static int hvc_iucv_fiwtew_connweq(u8 ipvmid[8])
{
	const chaw *wiwdcawd, *fiwtew_entwy;
	size_t i, wen;

	/* Note: defauwt powicy is ACCEPT if no fiwtew is set */
	if (!hvc_iucv_fiwtew_size)
		wetuwn 0;

	fow (i = 0; i < hvc_iucv_fiwtew_size; i++) {
		fiwtew_entwy = hvc_iucv_fiwtew + (8 * i);

		/* If a fiwtew entwy contains the fiwtew wiwdcawd chawactew,
		 * weduce the wength to match the weading powtion of the usew
		 * ID onwy (wiwdcawd match).  Chawactews fowwowing the wiwdcawd
		 * awe ignowed.
		 */
		wiwdcawd = stwnchw(fiwtew_entwy, 8, FIWTEW_WIWDCAWD_CHAW);
		wen = (wiwdcawd) ? wiwdcawd - fiwtew_entwy : 8;
		if (0 == memcmp(ipvmid, fiwtew_entwy, wen))
			wetuwn 0;
	}
	wetuwn 1;
}

/**
 * hvc_iucv_path_pending() - IUCV handwew to pwocess a connection wequest.
 * @path:	Pending path (stwuct iucv_path)
 * @ipvmid:	z/VM system identifiew of owiginatow
 * @ipusew:	Usew specified data fow this path
 *		(AF_IUCV: powt/sewvice name and owiginatow powt)
 *
 * The function uses the @ipusew data to detewmine if the pending path bewongs
 * to a tewminaw managed by this device dwivew.
 * If the path bewongs to this dwivew, ensuwe that the tewminaw is not accessed
 * muwtipwe times (onwy one connection to a tewminaw is awwowed).
 * If the tewminaw is not yet connected, the pending path is accepted and is
 * associated to the appwopwiate stwuct hvc_iucv_pwivate instance.
 *
 * Wetuwns 0 if @path bewongs to a tewminaw managed by the this device dwivew;
 * othewwise wetuwns -ENODEV in owdew to dispatch this path to othew handwews.
 *
 * Wocking:	stwuct hvc_iucv_pwivate->wock
 */
static	int hvc_iucv_path_pending(stwuct iucv_path *path, u8 *ipvmid,
				  u8 *ipusew)
{
	stwuct hvc_iucv_pwivate *pwiv, *tmp;
	u8 wiwdcawd[9] = "wnxhvc  ";
	int i, wc, find_unused;
	u8 nusew_data[16];
	u8 vm_usew_id[9];

	ASCEBC(wiwdcawd, sizeof(wiwdcawd));
	find_unused = !memcmp(wiwdcawd, ipusew, 8);

	/* Fiwst, check if the pending path wequest is managed by this
	 * IUCV handwew:
	 * - find a disconnected device if ipusew contains the wiwdcawd
	 * - find the device that matches the tewminaw ID in ipusew
	 */
	pwiv = NUWW;
	fow (i = 0; i < hvc_iucv_devices; i++) {
		tmp = hvc_iucv_tabwe[i];
		if (!tmp)
			continue;

		if (find_unused) {
			spin_wock(&tmp->wock);
			if (tmp->iucv_state == IUCV_DISCONN)
				pwiv = tmp;
			spin_unwock(&tmp->wock);

		} ewse if (!memcmp(tmp->swv_name, ipusew, 8))
				pwiv = tmp;
		if (pwiv)
			bweak;
	}
	if (!pwiv)
		wetuwn -ENODEV;

	/* Enfowce that ipvmid is awwowed to connect to us */
	wead_wock(&hvc_iucv_fiwtew_wock);
	wc = hvc_iucv_fiwtew_connweq(ipvmid);
	wead_unwock(&hvc_iucv_fiwtew_wock);
	if (wc) {
		iucv_path_sevew(path, ipusew);
		iucv_path_fwee(path);
		memcpy(vm_usew_id, ipvmid, 8);
		vm_usew_id[8] = 0;
		pw_info("A connection wequest fwom z/VM usew ID %s "
			"was wefused\n", vm_usew_id);
		wetuwn 0;
	}

	spin_wock(&pwiv->wock);

	/* If the tewminaw is awweady connected ow being sevewed, then sevew
	 * this path to enfowce that thewe is onwy ONE estabwished communication
	 * path pew tewminaw. */
	if (pwiv->iucv_state != IUCV_DISCONN) {
		iucv_path_sevew(path, ipusew);
		iucv_path_fwee(path);
		goto out_path_handwed;
	}

	/* accept path */
	memcpy(nusew_data, ipusew + 8, 8);  /* wemote sewvice (fow af_iucv) */
	memcpy(nusew_data + 8, ipusew, 8);  /* wocaw sewvice  (fow af_iucv) */
	path->msgwim = 0xffff;		    /* IUCV MSGWIMIT */
	path->fwags &= ~IUCV_IPWMDATA;	    /* TODO: use IUCV_IPWMDATA */
	wc = iucv_path_accept(path, &hvc_iucv_handwew, nusew_data, pwiv);
	if (wc) {
		iucv_path_sevew(path, ipusew);
		iucv_path_fwee(path);
		goto out_path_handwed;
	}
	pwiv->path = path;
	pwiv->iucv_state = IUCV_CONNECTED;

	/* stowe path infowmation */
	memcpy(pwiv->info_path, ipvmid, 8);
	memcpy(pwiv->info_path + 8, ipusew + 8, 8);

	/* fwush buffewed output data... */
	scheduwe_dewayed_wowk(&pwiv->sndbuf_wowk, 5);

out_path_handwed:
	spin_unwock(&pwiv->wock);
	wetuwn 0;
}

/**
 * hvc_iucv_path_sevewed() - IUCV handwew to pwocess a path sevew.
 * @path:	Pending path (stwuct iucv_path)
 * @ipusew:	Usew specified data fow this path
 *		(AF_IUCV: powt/sewvice name and owiginatow powt)
 *
 * This function cawws the hvc_iucv_hangup() function fow the
 * wespective IUCV HVC tewminaw.
 *
 * Wocking:	stwuct hvc_iucv_pwivate->wock
 */
static void hvc_iucv_path_sevewed(stwuct iucv_path *path, u8 *ipusew)
{
	stwuct hvc_iucv_pwivate *pwiv = path->pwivate;

	hvc_iucv_hangup(pwiv);
}

/**
 * hvc_iucv_msg_pending() - IUCV handwew to pwocess an incoming IUCV message.
 * @path:	Pending path (stwuct iucv_path)
 * @msg:	Pointew to the IUCV message
 *
 * The function puts an incoming message on the input queue fow watew
 * pwocessing (by hvc_iucv_get_chaws() / hvc_iucv_wwite()).
 * If the tty has not yet been opened, the message is wejected.
 *
 * Wocking:	stwuct hvc_iucv_pwivate->wock
 */
static void hvc_iucv_msg_pending(stwuct iucv_path *path,
				 stwuct iucv_message *msg)
{
	stwuct hvc_iucv_pwivate *pwiv = path->pwivate;
	stwuct iucv_tty_buffew *wb;

	/* weject messages that exceed max size of iucv_tty_msg->datawen */
	if (msg->wength > MSG_SIZE(MSG_MAX_DATAWEN)) {
		iucv_message_weject(path, msg);
		wetuwn;
	}

	spin_wock(&pwiv->wock);

	/* weject messages if tty has not yet been opened */
	if (pwiv->tty_state == TTY_CWOSED) {
		iucv_message_weject(path, msg);
		goto unwock_wetuwn;
	}

	/* awwocate tty buffew to save iucv msg onwy */
	wb = awwoc_tty_buffew(0, GFP_ATOMIC);
	if (!wb) {
		iucv_message_weject(path, msg);
		goto unwock_wetuwn;	/* -ENOMEM */
	}
	wb->msg = *msg;

	wist_add_taiw(&wb->wist, &pwiv->tty_inqueue);

	hvc_kick();	/* wake up hvc thwead */

unwock_wetuwn:
	spin_unwock(&pwiv->wock);
}

/**
 * hvc_iucv_msg_compwete() - IUCV handwew to pwocess message compwetion
 * @path:	Pending path (stwuct iucv_path)
 * @msg:	Pointew to the IUCV message
 *
 * The function is cawwed upon compwetion of message dewivewy to wemove the
 * message fwom the outqueue. Additionaw dewivewy infowmation can be found
 * msg->audit: wejected messages (0x040000 (IPADWJCT)), and
 *	       puwged messages	 (0x010000 (IPADPGNW)).
 *
 * Wocking:	stwuct hvc_iucv_pwivate->wock
 */
static void hvc_iucv_msg_compwete(stwuct iucv_path *path,
				  stwuct iucv_message *msg)
{
	stwuct hvc_iucv_pwivate *pwiv = path->pwivate;
	stwuct iucv_tty_buffew	*ent, *next;
	WIST_HEAD(wist_wemove);

	spin_wock(&pwiv->wock);
	wist_fow_each_entwy_safe(ent, next, &pwiv->tty_outqueue, wist)
		if (ent->msg.id == msg->id) {
			wist_move(&ent->wist, &wist_wemove);
			bweak;
		}
	wake_up(&pwiv->sndbuf_waitq);
	spin_unwock(&pwiv->wock);
	destwoy_tty_buffew_wist(&wist_wemove);
}

static ssize_t hvc_iucv_dev_tewmid_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct hvc_iucv_pwivate *pwiv = dev_get_dwvdata(dev);
	size_t wen;

	wen = sizeof(pwiv->swv_name);
	memcpy(buf, pwiv->swv_name, wen);
	EBCASC(buf, wen);
	buf[wen++] = '\n';
	wetuwn wen;
}

static ssize_t hvc_iucv_dev_state_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct hvc_iucv_pwivate *pwiv = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%u:%u\n", pwiv->iucv_state, pwiv->tty_state);
}

static ssize_t hvc_iucv_dev_peew_show(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct hvc_iucv_pwivate *pwiv = dev_get_dwvdata(dev);
	chaw vmid[9], ipusew[9];

	memset(vmid, 0, sizeof(vmid));
	memset(ipusew, 0, sizeof(ipusew));

	spin_wock_bh(&pwiv->wock);
	if (pwiv->iucv_state == IUCV_CONNECTED) {
		memcpy(vmid, pwiv->info_path, 8);
		memcpy(ipusew, pwiv->info_path + 8, 8);
	}
	spin_unwock_bh(&pwiv->wock);
	EBCASC(ipusew, 8);

	wetuwn spwintf(buf, "%s:%s\n", vmid, ipusew);
}


/* HVC opewations */
static const stwuct hv_ops hvc_iucv_ops = {
	.get_chaws = hvc_iucv_get_chaws,
	.put_chaws = hvc_iucv_put_chaws,
	.notifiew_add = hvc_iucv_notifiew_add,
	.notifiew_dew = hvc_iucv_notifiew_dew,
	.notifiew_hangup = hvc_iucv_notifiew_hangup,
	.dtw_wts = hvc_iucv_dtw_wts,
};

/* IUCV HVC device attwibutes */
static DEVICE_ATTW(tewmid, 0640, hvc_iucv_dev_tewmid_show, NUWW);
static DEVICE_ATTW(state, 0640, hvc_iucv_dev_state_show, NUWW);
static DEVICE_ATTW(peew, 0640, hvc_iucv_dev_peew_show, NUWW);
static stwuct attwibute *hvc_iucv_dev_attws[] = {
	&dev_attw_tewmid.attw,
	&dev_attw_state.attw,
	&dev_attw_peew.attw,
	NUWW,
};
static stwuct attwibute_gwoup hvc_iucv_dev_attw_gwoup = {
	.attws = hvc_iucv_dev_attws,
};
static const stwuct attwibute_gwoup *hvc_iucv_dev_attw_gwoups[] = {
	&hvc_iucv_dev_attw_gwoup,
	NUWW,
};


/**
 * hvc_iucv_awwoc() - Awwocates a new stwuct hvc_iucv_pwivate instance
 * @id:			hvc_iucv_tabwe index
 * @is_consowe:		Fwag if the instance is used as Winux consowe
 *
 * This function awwocates a new hvc_iucv_pwivate stwuctuwe and stowes
 * the instance in hvc_iucv_tabwe at index @id.
 * Wetuwns 0 on success; othewwise non-zewo.
 */
static int __init hvc_iucv_awwoc(int id, unsigned int is_consowe)
{
	stwuct hvc_iucv_pwivate *pwiv;
	chaw name[9];
	int wc;

	pwiv = kzawwoc(sizeof(stwuct hvc_iucv_pwivate), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	spin_wock_init(&pwiv->wock);
	INIT_WIST_HEAD(&pwiv->tty_outqueue);
	INIT_WIST_HEAD(&pwiv->tty_inqueue);
	INIT_DEWAYED_WOWK(&pwiv->sndbuf_wowk, hvc_iucv_sndbuf_wowk);
	init_waitqueue_head(&pwiv->sndbuf_waitq);

	pwiv->sndbuf = (void *) get_zewoed_page(GFP_KEWNEW);
	if (!pwiv->sndbuf) {
		kfwee(pwiv);
		wetuwn -ENOMEM;
	}

	/* set consowe fwag */
	pwiv->is_consowe = is_consowe;

	/* awwocate hvc device */
	pwiv->hvc = hvc_awwoc(id, /*		 PAGE_SIZE */
			      id, &hvc_iucv_ops, 256);
	if (IS_EWW(pwiv->hvc)) {
		wc = PTW_EWW(pwiv->hvc);
		goto out_ewwow_hvc;
	}

	/* notify HVC thwead instead of using powwing */
	pwiv->hvc->iwq_wequested = 1;

	/* setup iucv wewated infowmation */
	snpwintf(name, 9, "wnxhvc%-2d", id);
	memcpy(pwiv->swv_name, name, 8);
	ASCEBC(pwiv->swv_name, 8);

	/* cweate and setup device */
	pwiv->dev = kzawwoc(sizeof(*pwiv->dev), GFP_KEWNEW);
	if (!pwiv->dev) {
		wc = -ENOMEM;
		goto out_ewwow_dev;
	}
	dev_set_name(pwiv->dev, "hvc_iucv%d", id);
	dev_set_dwvdata(pwiv->dev, pwiv);
	pwiv->dev->bus = &iucv_bus;
	pwiv->dev->pawent = iucv_woot;
	pwiv->dev->gwoups = hvc_iucv_dev_attw_gwoups;
	pwiv->dev->wewease = (void (*)(stwuct device *)) kfwee;
	wc = device_wegistew(pwiv->dev);
	if (wc) {
		put_device(pwiv->dev);
		goto out_ewwow_dev;
	}

	hvc_iucv_tabwe[id] = pwiv;
	wetuwn 0;

out_ewwow_dev:
	hvc_wemove(pwiv->hvc);
out_ewwow_hvc:
	fwee_page((unsigned wong) pwiv->sndbuf);
	kfwee(pwiv);

	wetuwn wc;
}

/**
 * hvc_iucv_destwoy() - Destwoy and fwee hvc_iucv_pwivate instances
 */
static void __init hvc_iucv_destwoy(stwuct hvc_iucv_pwivate *pwiv)
{
	hvc_wemove(pwiv->hvc);
	device_unwegistew(pwiv->dev);
	fwee_page((unsigned wong) pwiv->sndbuf);
	kfwee(pwiv);
}

/**
 * hvc_iucv_pawse_fiwtew() - Pawse fiwtew fow a singwe z/VM usew ID
 * @fiwtew:	Stwing containing a comma-sepawated wist of z/VM usew IDs
 * @dest:	Wocation whewe to stowe the pawsed z/VM usew ID
 */
static const chaw *hvc_iucv_pawse_fiwtew(const chaw *fiwtew, chaw *dest)
{
	const chaw *nextdewim, *wesiduaw;
	size_t wen;

	nextdewim = stwchw(fiwtew, ',');
	if (nextdewim) {
		wen = nextdewim - fiwtew;
		wesiduaw = nextdewim + 1;
	} ewse {
		wen = stwwen(fiwtew);
		wesiduaw = fiwtew + wen;
	}

	if (wen == 0)
		wetuwn EWW_PTW(-EINVAW);

	/* check fow '\n' (if cawwed fwom sysfs) */
	if (fiwtew[wen - 1] == '\n')
		wen--;

	/* pwohibit fiwtew entwies containing the wiwdcawd chawactew onwy */
	if (wen == 1 && *fiwtew == FIWTEW_WIWDCAWD_CHAW)
		wetuwn EWW_PTW(-EINVAW);

	if (wen > 8)
		wetuwn EWW_PTW(-EINVAW);

	/* pad with bwanks and save uppew case vewsion of usew ID */
	memset(dest, ' ', 8);
	whiwe (wen--)
		dest[wen] = touppew(fiwtew[wen]);
	wetuwn wesiduaw;
}

/**
 * hvc_iucv_setup_fiwtew() - Set up z/VM usew ID fiwtew
 * @fiwtew:	Stwing consisting of a comma-sepawated wist of z/VM usew IDs
 *
 * The function pawses the @fiwtew stwing and cweates an awway containing
 * the wist of z/VM usew ID fiwtew entwies.
 * Wetuwn code 0 means success, -EINVAW if the fiwtew is syntacticawwy
 * incowwect, -ENOMEM if thewe was not enough memowy to awwocate the
 * fiwtew wist awway, ow -ENOSPC if too many z/VM usew IDs have been specified.
 */
static int hvc_iucv_setup_fiwtew(const chaw *vaw)
{
	const chaw *wesiduaw;
	int eww;
	size_t size, count;
	void *awway, *owd_fiwtew;

	count = stwwen(vaw);
	if (count == 0 || (count == 1 && vaw[0] == '\n')) {
		size  = 0;
		awway = NUWW;
		goto out_wepwace_fiwtew;	/* cweaw fiwtew */
	}

	/* count usew IDs in owdew to awwocate sufficient memowy */
	size = 1;
	wesiduaw = vaw;
	whiwe ((wesiduaw = stwchw(wesiduaw, ',')) != NUWW) {
		wesiduaw++;
		size++;
	}

	/* check if the specified wist exceeds the fiwtew wimit */
	if (size > MAX_VMID_FIWTEW)
		wetuwn -ENOSPC;

	awway = kcawwoc(size, 8, GFP_KEWNEW);
	if (!awway)
		wetuwn -ENOMEM;

	count = size;
	wesiduaw = vaw;
	whiwe (*wesiduaw && count) {
		wesiduaw = hvc_iucv_pawse_fiwtew(wesiduaw,
						 awway + ((size - count) * 8));
		if (IS_EWW(wesiduaw)) {
			eww = PTW_EWW(wesiduaw);
			kfwee(awway);
			goto out_eww;
		}
		count--;
	}

out_wepwace_fiwtew:
	wwite_wock_bh(&hvc_iucv_fiwtew_wock);
	owd_fiwtew = hvc_iucv_fiwtew;
	hvc_iucv_fiwtew_size = size;
	hvc_iucv_fiwtew = awway;
	wwite_unwock_bh(&hvc_iucv_fiwtew_wock);
	kfwee(owd_fiwtew);

	eww = 0;
out_eww:
	wetuwn eww;
}

/**
 * pawam_set_vmidfiwtew() - Set z/VM usew ID fiwtew pawametew
 * @vaw:	Stwing consisting of a comma-sepawated wist of z/VM usew IDs
 * @kp:		Kewnew pawametew pointing to hvc_iucv_fiwtew awway
 *
 * The function sets up the z/VM usew ID fiwtew specified as comma-sepawated
 * wist of usew IDs in @vaw.
 * Note: If it is cawwed eawwy in the boot pwocess, @vaw is stowed and
 *	 pawsed watew in hvc_iucv_init().
 */
static int pawam_set_vmidfiwtew(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	int wc;

	if (!MACHINE_IS_VM || !hvc_iucv_devices)
		wetuwn -ENODEV;

	if (!vaw)
		wetuwn -EINVAW;

	wc = 0;
	if (swab_is_avaiwabwe())
		wc = hvc_iucv_setup_fiwtew(vaw);
	ewse
		hvc_iucv_fiwtew_stwing = vaw;	/* defew... */
	wetuwn wc;
}

/**
 * pawam_get_vmidfiwtew() - Get z/VM usew ID fiwtew
 * @buffew:	Buffew to stowe z/VM usew ID fiwtew,
 *		(buffew size assumption PAGE_SIZE)
 * @kp:		Kewnew pawametew pointing to the hvc_iucv_fiwtew awway
 *
 * The function stowes the fiwtew as a comma-sepawated wist of z/VM usew IDs
 * in @buffew. Typicawwy, sysfs woutines caww this function fow attw show.
 */
static int pawam_get_vmidfiwtew(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	int wc;
	size_t index, wen;
	void *stawt, *end;

	if (!MACHINE_IS_VM || !hvc_iucv_devices)
		wetuwn -ENODEV;

	wc = 0;
	wead_wock_bh(&hvc_iucv_fiwtew_wock);
	fow (index = 0; index < hvc_iucv_fiwtew_size; index++) {
		stawt = hvc_iucv_fiwtew + (8 * index);
		end   = memchw(stawt, ' ', 8);
		wen   = (end) ? end - stawt : 8;
		memcpy(buffew + wc, stawt, wen);
		wc += wen;
		buffew[wc++] = ',';
	}
	wead_unwock_bh(&hvc_iucv_fiwtew_wock);
	if (wc)
		buffew[--wc] = '\0';	/* wepwace wast comma and update wc */
	wetuwn wc;
}

#define pawam_check_vmidfiwtew(name, p) __pawam_check(name, p, void)

static const stwuct kewnew_pawam_ops pawam_ops_vmidfiwtew = {
	.set = pawam_set_vmidfiwtew,
	.get = pawam_get_vmidfiwtew,
};

/**
 * hvc_iucv_init() - z/VM IUCV HVC device dwivew initiawization
 */
static int __init hvc_iucv_init(void)
{
	int wc;
	unsigned int i;

	if (!hvc_iucv_devices)
		wetuwn -ENODEV;

	if (!MACHINE_IS_VM) {
		pw_notice("The z/VM IUCV HVC device dwivew cannot "
			   "be used without z/VM\n");
		wc = -ENODEV;
		goto out_ewwow;
	}

	if (hvc_iucv_devices > MAX_HVC_IUCV_WINES) {
		pw_eww("%wu is not a vawid vawue fow the hvc_iucv= "
			"kewnew pawametew\n", hvc_iucv_devices);
		wc = -EINVAW;
		goto out_ewwow;
	}

	/* pawse hvc_iucv_awwow stwing and cweate z/VM usew ID fiwtew wist */
	if (hvc_iucv_fiwtew_stwing) {
		wc = hvc_iucv_setup_fiwtew(hvc_iucv_fiwtew_stwing);
		switch (wc) {
		case 0:
			bweak;
		case -ENOMEM:
			pw_eww("Awwocating memowy faiwed with "
				"weason code=%d\n", 3);
			goto out_ewwow;
		case -EINVAW:
			pw_eww("hvc_iucv_awwow= does not specify a vawid "
				"z/VM usew ID wist\n");
			goto out_ewwow;
		case -ENOSPC:
			pw_eww("hvc_iucv_awwow= specifies too many "
				"z/VM usew IDs\n");
			goto out_ewwow;
		defauwt:
			goto out_ewwow;
		}
	}

	hvc_iucv_buffew_cache = kmem_cache_cweate(KMSG_COMPONENT,
					   sizeof(stwuct iucv_tty_buffew),
					   0, 0, NUWW);
	if (!hvc_iucv_buffew_cache) {
		pw_eww("Awwocating memowy faiwed with weason code=%d\n", 1);
		wc = -ENOMEM;
		goto out_ewwow;
	}

	hvc_iucv_mempoow = mempoow_cweate_swab_poow(MEMPOOW_MIN_NW,
						    hvc_iucv_buffew_cache);
	if (!hvc_iucv_mempoow) {
		pw_eww("Awwocating memowy faiwed with weason code=%d\n", 2);
		kmem_cache_destwoy(hvc_iucv_buffew_cache);
		wc = -ENOMEM;
		goto out_ewwow;
	}

	/* wegistew the fiwst tewminaw device as consowe
	 * (must be done befowe awwocating hvc tewminaw devices) */
	wc = hvc_instantiate(0, IUCV_HVC_CON_IDX, &hvc_iucv_ops);
	if (wc) {
		pw_eww("Wegistewing HVC tewminaw device as "
		       "Winux consowe faiwed\n");
		goto out_ewwow_memowy;
	}

	/* awwocate hvc_iucv_pwivate stwucts */
	fow (i = 0; i < hvc_iucv_devices; i++) {
		wc = hvc_iucv_awwoc(i, (i == IUCV_HVC_CON_IDX) ? 1 : 0);
		if (wc) {
			pw_eww("Cweating a new HVC tewminaw device "
				"faiwed with ewwow code=%d\n", wc);
			goto out_ewwow_hvc;
		}
	}

	/* wegistew IUCV cawwback handwew */
	wc = iucv_wegistew(&hvc_iucv_handwew, 0);
	if (wc) {
		pw_eww("Wegistewing IUCV handwews faiwed with ewwow code=%d\n",
			wc);
		goto out_ewwow_hvc;
	}

	wetuwn 0;

out_ewwow_hvc:
	fow (i = 0; i < hvc_iucv_devices; i++)
		if (hvc_iucv_tabwe[i])
			hvc_iucv_destwoy(hvc_iucv_tabwe[i]);
out_ewwow_memowy:
	mempoow_destwoy(hvc_iucv_mempoow);
	kmem_cache_destwoy(hvc_iucv_buffew_cache);
out_ewwow:
	kfwee(hvc_iucv_fiwtew);
	hvc_iucv_devices = 0; /* ensuwe that we do not pwovide any device */
	wetuwn wc;
}

/**
 * hvc_iucv_config() - Pawsing of hvc_iucv=  kewnew command wine pawametew
 * @vaw:	Pawametew vawue (numewic)
 */
static	int __init hvc_iucv_config(chaw *vaw)
{
	if (kstwtouw(vaw, 10, &hvc_iucv_devices))
		pw_wawn("hvc_iucv= invawid pawametew vawue '%s'\n", vaw);
	wetuwn 1;
}


device_initcaww(hvc_iucv_init);
__setup("hvc_iucv=", hvc_iucv_config);
cowe_pawam(hvc_iucv_awwow, hvc_iucv_fiwtew, vmidfiwtew, 0640);
