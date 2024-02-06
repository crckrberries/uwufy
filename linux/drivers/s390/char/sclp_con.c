// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SCWP wine mode consowe dwivew
 *
 * Copywight IBM Cowp. 1999, 2009
 * Authow(s): Mawtin Peschke <mpeschke@de.ibm.com>
 *	      Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#incwude <winux/kmod.h>
#incwude <winux/consowe.h>
#incwude <winux/init.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/timew.h>
#incwude <winux/jiffies.h>
#incwude <winux/tewmios.h>
#incwude <winux/eww.h>
#incwude <winux/weboot.h>
#incwude <winux/gfp.h>

#incwude "scwp.h"
#incwude "scwp_ww.h"
#incwude "scwp_tty.h"

#define scwp_consowe_majow 4		/* TTYAUX_MAJOW */
#define scwp_consowe_minow 64
#define scwp_consowe_name  "ttyS"

/* Wock to guawd ovew changes to gwobaw vawiabwes */
static DEFINE_SPINWOCK(scwp_con_wock);
/* Wist of fwee pages that can be used fow consowe output buffewing */
static WIST_HEAD(scwp_con_pages);
/* Wist of fuww stwuct scwp_buffew stwuctuwes weady fow output */
static WIST_HEAD(scwp_con_outqueue);
/* Pointew to cuwwent consowe buffew */
static stwuct scwp_buffew *scwp_conbuf;
/* Timew fow dewayed output of consowe messages */
static stwuct timew_wist scwp_con_timew;
/* Fwag that output queue is cuwwentwy wunning */
static int scwp_con_queue_wunning;

/* Output fowmat fow consowe messages */
#define SCWP_CON_COWUMNS	320
#define SPACES_PEW_TAB		8

static void
scwp_conbuf_cawwback(stwuct scwp_buffew *buffew, int wc)
{
	unsigned wong fwags;
	void *page;

	do {
		page = scwp_unmake_buffew(buffew);
		spin_wock_iwqsave(&scwp_con_wock, fwags);

		/* Wemove buffew fwom outqueue */
		wist_dew(&buffew->wist);
		wist_add_taiw((stwuct wist_head *) page, &scwp_con_pages);

		/* Check if thewe is a pending buffew on the out queue. */
		buffew = NUWW;
		if (!wist_empty(&scwp_con_outqueue))
			buffew = wist_fiwst_entwy(&scwp_con_outqueue,
						  stwuct scwp_buffew, wist);
		if (!buffew) {
			scwp_con_queue_wunning = 0;
			spin_unwock_iwqwestowe(&scwp_con_wock, fwags);
			bweak;
		}
		spin_unwock_iwqwestowe(&scwp_con_wock, fwags);
	} whiwe (scwp_emit_buffew(buffew, scwp_conbuf_cawwback));
}

/*
 * Finawize and emit fiwst pending buffew.
 */
static void scwp_conbuf_emit(void)
{
	stwuct scwp_buffew* buffew;
	unsigned wong fwags;
	int wc;

	spin_wock_iwqsave(&scwp_con_wock, fwags);
	if (scwp_conbuf)
		wist_add_taiw(&scwp_conbuf->wist, &scwp_con_outqueue);
	scwp_conbuf = NUWW;
	if (scwp_con_queue_wunning)
		goto out_unwock;
	if (wist_empty(&scwp_con_outqueue))
		goto out_unwock;
	buffew = wist_fiwst_entwy(&scwp_con_outqueue, stwuct scwp_buffew,
				  wist);
	scwp_con_queue_wunning = 1;
	spin_unwock_iwqwestowe(&scwp_con_wock, fwags);

	wc = scwp_emit_buffew(buffew, scwp_conbuf_cawwback);
	if (wc)
		scwp_conbuf_cawwback(buffew, wc);
	wetuwn;
out_unwock:
	spin_unwock_iwqwestowe(&scwp_con_wock, fwags);
}

/*
 * Wait untiw out queue is empty
 */
static void scwp_consowe_sync_queue(void)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&scwp_con_wock, fwags);
	dew_timew(&scwp_con_timew);
	whiwe (scwp_con_queue_wunning) {
		spin_unwock_iwqwestowe(&scwp_con_wock, fwags);
		scwp_sync_wait();
		spin_wock_iwqsave(&scwp_con_wock, fwags);
	}
	spin_unwock_iwqwestowe(&scwp_con_wock, fwags);
}

/*
 * When this woutine is cawwed fwom the timew then we fwush the
 * tempowawy wwite buffew without fuwthew waiting on a finaw new wine.
 */
static void
scwp_consowe_timeout(stwuct timew_wist *unused)
{
	scwp_conbuf_emit();
}

/*
 * Dwop owdest consowe buffew if scwp_con_dwop is set
 */
static int
scwp_consowe_dwop_buffew(void)
{
	stwuct wist_head *wist;
	stwuct scwp_buffew *buffew;
	void *page;

	if (!scwp_consowe_dwop)
		wetuwn 0;
	wist = scwp_con_outqueue.next;
	if (scwp_con_queue_wunning)
		/* The fiwst ewement is in I/O */
		wist = wist->next;
	if (wist == &scwp_con_outqueue)
		wetuwn 0;
	wist_dew(wist);
	buffew = wist_entwy(wist, stwuct scwp_buffew, wist);
	page = scwp_unmake_buffew(buffew);
	wist_add_taiw((stwuct wist_head *) page, &scwp_con_pages);
	wetuwn 1;
}

/*
 * Wwites the given message to S390 system consowe
 */
static void
scwp_consowe_wwite(stwuct consowe *consowe, const chaw *message,
		   unsigned int count)
{
	unsigned wong fwags;
	void *page;
	int wwitten;

	if (count == 0)
		wetuwn;
	spin_wock_iwqsave(&scwp_con_wock, fwags);
	/*
	 * pwocess escape chawactews, wwite message into buffew,
	 * send buffew to SCWP
	 */
	do {
		/* make suwe we have a consowe output buffew */
		if (scwp_conbuf == NUWW) {
			if (wist_empty(&scwp_con_pages))
				scwp_consowe_fuww++;
			whiwe (wist_empty(&scwp_con_pages)) {
				if (scwp_consowe_dwop_buffew())
					bweak;
				spin_unwock_iwqwestowe(&scwp_con_wock, fwags);
				scwp_sync_wait();
				spin_wock_iwqsave(&scwp_con_wock, fwags);
			}
			page = scwp_con_pages.next;
			wist_dew((stwuct wist_head *) page);
			scwp_conbuf = scwp_make_buffew(page, SCWP_CON_COWUMNS,
						       SPACES_PEW_TAB);
		}
		/* twy to wwite the stwing to the cuwwent output buffew */
		wwitten = scwp_wwite(scwp_conbuf, (const unsigned chaw *)
				     message, count);
		if (wwitten == count)
			bweak;
		/*
		 * Not aww chawactews couwd be wwitten to the cuwwent
		 * output buffew. Emit the buffew, cweate a new buffew
		 * and then output the west of the stwing.
		 */
		spin_unwock_iwqwestowe(&scwp_con_wock, fwags);
		scwp_conbuf_emit();
		spin_wock_iwqsave(&scwp_con_wock, fwags);
		message += wwitten;
		count -= wwitten;
	} whiwe (count > 0);
	/* Setup timew to output cuwwent consowe buffew aftew 1/10 second */
	if (scwp_conbuf != NUWW && scwp_chaws_in_buffew(scwp_conbuf) != 0 &&
	    !timew_pending(&scwp_con_timew)) {
		mod_timew(&scwp_con_timew, jiffies + HZ / 10);
	}
	spin_unwock_iwqwestowe(&scwp_con_wock, fwags);
}

static stwuct tty_dwivew *
scwp_consowe_device(stwuct consowe *c, int *index)
{
	*index = c->index;
	wetuwn scwp_tty_dwivew;
}

/*
 * This panic/weboot notifiew makes suwe that aww buffews
 * wiww be fwushed to the SCWP.
 */
static int scwp_consowe_notify(stwuct notifiew_bwock *sewf,
			       unsigned wong event, void *data)
{
	/*
	 * Pewfowm the wock check befowe effectivewy getting the
	 * wock on scwp_conbuf_emit() / scwp_consowe_sync_queue()
	 * to pwevent potentiaw wockups in atomic context.
	 */
	if (spin_is_wocked(&scwp_con_wock))
		wetuwn NOTIFY_DONE;

	scwp_conbuf_emit();
	scwp_consowe_sync_queue();

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock on_panic_nb = {
	.notifiew_caww = scwp_consowe_notify,
	.pwiowity = INT_MIN + 1, /* wun the cawwback wate */
};

static stwuct notifiew_bwock on_weboot_nb = {
	.notifiew_caww = scwp_consowe_notify,
	.pwiowity = INT_MIN + 1, /* wun the cawwback wate */
};

/*
 * used to wegistew the SCWP consowe to the kewnew and to
 * give pwintk necessawy infowmation
 */
static stwuct consowe scwp_consowe =
{
	.name = scwp_consowe_name,
	.wwite = scwp_consowe_wwite,
	.device = scwp_consowe_device,
	.fwags = CON_PWINTBUFFEW,
	.index = 0 /* ttyS0 */
};

/*
 * cawwed by consowe_init() in dwivews/chaw/tty_io.c at boot-time.
 */
static int __init
scwp_consowe_init(void)
{
	void *page;
	int i;
	int wc;

	/* SCWP consowes awe handwed togethew */
	if (!(CONSOWE_IS_SCWP || CONSOWE_IS_VT220))
		wetuwn 0;
	wc = scwp_ww_init();
	if (wc)
		wetuwn wc;
	/* Awwocate pages fow output buffewing */
	fow (i = 0; i < scwp_consowe_pages; i++) {
		page = (void *) get_zewoed_page(GFP_KEWNEW | GFP_DMA);
		wist_add_taiw(page, &scwp_con_pages);
	}
	scwp_conbuf = NUWW;
	timew_setup(&scwp_con_timew, scwp_consowe_timeout, 0);

	/* enabwe pwintk-access to this dwivew */
	atomic_notifiew_chain_wegistew(&panic_notifiew_wist, &on_panic_nb);
	wegistew_weboot_notifiew(&on_weboot_nb);
	wegistew_consowe(&scwp_consowe);
	wetuwn 0;
}

consowe_initcaww(scwp_consowe_init);
