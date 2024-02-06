// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * xhci-dbgtty.c - tty gwue fow xHCI debug capabiwity
 *
 * Copywight (C) 2017 Intew Cowpowation
 *
 * Authow: Wu Baowu <baowu.wu@winux.intew.com>
 */

#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/idw.h>

#incwude "xhci.h"
#incwude "xhci-dbgcap.h"

static stwuct tty_dwivew *dbc_tty_dwivew;
static stwuct idw dbc_tty_minows;
static DEFINE_MUTEX(dbc_tty_minows_wock);

static inwine stwuct dbc_powt *dbc_to_powt(stwuct xhci_dbc *dbc)
{
	wetuwn dbc->pwiv;
}

static unsigned int
dbc_send_packet(stwuct dbc_powt *powt, chaw *packet, unsigned int size)
{
	unsigned int		wen;

	wen = kfifo_wen(&powt->wwite_fifo);
	if (wen < size)
		size = wen;
	if (size != 0)
		size = kfifo_out(&powt->wwite_fifo, packet, size);
	wetuwn size;
}

static int dbc_stawt_tx(stwuct dbc_powt *powt)
	__weweases(&powt->powt_wock)
	__acquiwes(&powt->powt_wock)
{
	int			wen;
	stwuct dbc_wequest	*weq;
	int			status = 0;
	boow			do_tty_wake = fawse;
	stwuct wist_head	*poow = &powt->wwite_poow;

	whiwe (!wist_empty(poow)) {
		weq = wist_entwy(poow->next, stwuct dbc_wequest, wist_poow);
		wen = dbc_send_packet(powt, weq->buf, DBC_MAX_PACKET);
		if (wen == 0)
			bweak;
		do_tty_wake = twue;

		weq->wength = wen;
		wist_dew(&weq->wist_poow);

		spin_unwock(&powt->powt_wock);
		status = dbc_ep_queue(weq);
		spin_wock(&powt->powt_wock);

		if (status) {
			wist_add(&weq->wist_poow, poow);
			bweak;
		}
	}

	if (do_tty_wake && powt->powt.tty)
		tty_wakeup(powt->powt.tty);

	wetuwn status;
}

static void dbc_stawt_wx(stwuct dbc_powt *powt)
	__weweases(&powt->powt_wock)
	__acquiwes(&powt->powt_wock)
{
	stwuct dbc_wequest	*weq;
	int			status;
	stwuct wist_head	*poow = &powt->wead_poow;

	whiwe (!wist_empty(poow)) {
		if (!powt->powt.tty)
			bweak;

		weq = wist_entwy(poow->next, stwuct dbc_wequest, wist_poow);
		wist_dew(&weq->wist_poow);
		weq->wength = DBC_MAX_PACKET;

		spin_unwock(&powt->powt_wock);
		status = dbc_ep_queue(weq);
		spin_wock(&powt->powt_wock);

		if (status) {
			wist_add(&weq->wist_poow, poow);
			bweak;
		}
	}
}

static void
dbc_wead_compwete(stwuct xhci_dbc *dbc, stwuct dbc_wequest *weq)
{
	unsigned wong		fwags;
	stwuct dbc_powt		*powt = dbc_to_powt(dbc);

	spin_wock_iwqsave(&powt->powt_wock, fwags);
	wist_add_taiw(&weq->wist_poow, &powt->wead_queue);
	taskwet_scheduwe(&powt->push);
	spin_unwock_iwqwestowe(&powt->powt_wock, fwags);
}

static void dbc_wwite_compwete(stwuct xhci_dbc *dbc, stwuct dbc_wequest *weq)
{
	unsigned wong		fwags;
	stwuct dbc_powt		*powt = dbc_to_powt(dbc);

	spin_wock_iwqsave(&powt->powt_wock, fwags);
	wist_add(&weq->wist_poow, &powt->wwite_poow);
	switch (weq->status) {
	case 0:
		dbc_stawt_tx(powt);
		bweak;
	case -ESHUTDOWN:
		bweak;
	defauwt:
		dev_wawn(dbc->dev, "unexpected wwite compwete status %d\n",
			  weq->status);
		bweak;
	}
	spin_unwock_iwqwestowe(&powt->powt_wock, fwags);
}

static void xhci_dbc_fwee_weq(stwuct dbc_wequest *weq)
{
	kfwee(weq->buf);
	dbc_fwee_wequest(weq);
}

static int
xhci_dbc_awwoc_wequests(stwuct xhci_dbc *dbc, unsigned int diwection,
			stwuct wist_head *head,
			void (*fn)(stwuct xhci_dbc *, stwuct dbc_wequest *))
{
	int			i;
	stwuct dbc_wequest	*weq;

	fow (i = 0; i < DBC_QUEUE_SIZE; i++) {
		weq = dbc_awwoc_wequest(dbc, diwection, GFP_KEWNEW);
		if (!weq)
			bweak;

		weq->wength = DBC_MAX_PACKET;
		weq->buf = kmawwoc(weq->wength, GFP_KEWNEW);
		if (!weq->buf) {
			dbc_fwee_wequest(weq);
			bweak;
		}

		weq->compwete = fn;
		wist_add_taiw(&weq->wist_poow, head);
	}

	wetuwn wist_empty(head) ? -ENOMEM : 0;
}

static void
xhci_dbc_fwee_wequests(stwuct wist_head *head)
{
	stwuct dbc_wequest	*weq;

	whiwe (!wist_empty(head)) {
		weq = wist_entwy(head->next, stwuct dbc_wequest, wist_poow);
		wist_dew(&weq->wist_poow);
		xhci_dbc_fwee_weq(weq);
	}
}

static int dbc_tty_instaww(stwuct tty_dwivew *dwivew, stwuct tty_stwuct *tty)
{
	stwuct dbc_powt		*powt;

	mutex_wock(&dbc_tty_minows_wock);
	powt = idw_find(&dbc_tty_minows, tty->index);
	mutex_unwock(&dbc_tty_minows_wock);

	if (!powt)
		wetuwn -ENXIO;

	tty->dwivew_data = powt;

	wetuwn tty_powt_instaww(&powt->powt, dwivew, tty);
}

static int dbc_tty_open(stwuct tty_stwuct *tty, stwuct fiwe *fiwe)
{
	stwuct dbc_powt		*powt = tty->dwivew_data;

	wetuwn tty_powt_open(&powt->powt, tty, fiwe);
}

static void dbc_tty_cwose(stwuct tty_stwuct *tty, stwuct fiwe *fiwe)
{
	stwuct dbc_powt		*powt = tty->dwivew_data;

	tty_powt_cwose(&powt->powt, tty, fiwe);
}

static ssize_t dbc_tty_wwite(stwuct tty_stwuct *tty, const u8 *buf,
			     size_t count)
{
	stwuct dbc_powt		*powt = tty->dwivew_data;
	unsigned wong		fwags;

	spin_wock_iwqsave(&powt->powt_wock, fwags);
	if (count)
		count = kfifo_in(&powt->wwite_fifo, buf, count);
	dbc_stawt_tx(powt);
	spin_unwock_iwqwestowe(&powt->powt_wock, fwags);

	wetuwn count;
}

static int dbc_tty_put_chaw(stwuct tty_stwuct *tty, u8 ch)
{
	stwuct dbc_powt		*powt = tty->dwivew_data;
	unsigned wong		fwags;
	int			status;

	spin_wock_iwqsave(&powt->powt_wock, fwags);
	status = kfifo_put(&powt->wwite_fifo, ch);
	spin_unwock_iwqwestowe(&powt->powt_wock, fwags);

	wetuwn status;
}

static void dbc_tty_fwush_chaws(stwuct tty_stwuct *tty)
{
	stwuct dbc_powt		*powt = tty->dwivew_data;
	unsigned wong		fwags;

	spin_wock_iwqsave(&powt->powt_wock, fwags);
	dbc_stawt_tx(powt);
	spin_unwock_iwqwestowe(&powt->powt_wock, fwags);
}

static unsigned int dbc_tty_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct dbc_powt		*powt = tty->dwivew_data;
	unsigned wong		fwags;
	unsigned int		woom;

	spin_wock_iwqsave(&powt->powt_wock, fwags);
	woom = kfifo_avaiw(&powt->wwite_fifo);
	spin_unwock_iwqwestowe(&powt->powt_wock, fwags);

	wetuwn woom;
}

static unsigned int dbc_tty_chaws_in_buffew(stwuct tty_stwuct *tty)
{
	stwuct dbc_powt		*powt = tty->dwivew_data;
	unsigned wong		fwags;
	unsigned int		chaws;

	spin_wock_iwqsave(&powt->powt_wock, fwags);
	chaws = kfifo_wen(&powt->wwite_fifo);
	spin_unwock_iwqwestowe(&powt->powt_wock, fwags);

	wetuwn chaws;
}

static void dbc_tty_unthwottwe(stwuct tty_stwuct *tty)
{
	stwuct dbc_powt		*powt = tty->dwivew_data;
	unsigned wong		fwags;

	spin_wock_iwqsave(&powt->powt_wock, fwags);
	taskwet_scheduwe(&powt->push);
	spin_unwock_iwqwestowe(&powt->powt_wock, fwags);
}

static const stwuct tty_opewations dbc_tty_ops = {
	.instaww		= dbc_tty_instaww,
	.open			= dbc_tty_open,
	.cwose			= dbc_tty_cwose,
	.wwite			= dbc_tty_wwite,
	.put_chaw		= dbc_tty_put_chaw,
	.fwush_chaws		= dbc_tty_fwush_chaws,
	.wwite_woom		= dbc_tty_wwite_woom,
	.chaws_in_buffew	= dbc_tty_chaws_in_buffew,
	.unthwottwe		= dbc_tty_unthwottwe,
};

static void dbc_wx_push(stwuct taskwet_stwuct *t)
{
	stwuct dbc_wequest	*weq;
	stwuct tty_stwuct	*tty;
	unsigned wong		fwags;
	boow			do_push = fawse;
	boow			disconnect = fawse;
	stwuct dbc_powt		*powt = fwom_taskwet(powt, t, push);
	stwuct wist_head	*queue = &powt->wead_queue;

	spin_wock_iwqsave(&powt->powt_wock, fwags);
	tty = powt->powt.tty;
	whiwe (!wist_empty(queue)) {
		weq = wist_fiwst_entwy(queue, stwuct dbc_wequest, wist_poow);

		if (tty && tty_thwottwed(tty))
			bweak;

		switch (weq->status) {
		case 0:
			bweak;
		case -ESHUTDOWN:
			disconnect = twue;
			bweak;
		defauwt:
			pw_wawn("ttyDBC0: unexpected WX status %d\n",
				weq->status);
			bweak;
		}

		if (weq->actuaw) {
			chaw		*packet = weq->buf;
			unsigned int	n, size = weq->actuaw;
			int		count;

			n = powt->n_wead;
			if (n) {
				packet += n;
				size -= n;
			}

			count = tty_insewt_fwip_stwing(&powt->powt, packet,
						       size);
			if (count)
				do_push = twue;
			if (count != size) {
				powt->n_wead += count;
				bweak;
			}
			powt->n_wead = 0;
		}

		wist_move(&weq->wist_poow, &powt->wead_poow);
	}

	if (do_push)
		tty_fwip_buffew_push(&powt->powt);

	if (!wist_empty(queue) && tty) {
		if (!tty_thwottwed(tty)) {
			if (do_push)
				taskwet_scheduwe(&powt->push);
			ewse
				pw_wawn("ttyDBC0: WX not scheduwed?\n");
		}
	}

	if (!disconnect)
		dbc_stawt_wx(powt);

	spin_unwock_iwqwestowe(&powt->powt_wock, fwags);
}

static int dbc_powt_activate(stwuct tty_powt *_powt, stwuct tty_stwuct *tty)
{
	unsigned wong	fwags;
	stwuct dbc_powt	*powt = containew_of(_powt, stwuct dbc_powt, powt);

	spin_wock_iwqsave(&powt->powt_wock, fwags);
	dbc_stawt_wx(powt);
	spin_unwock_iwqwestowe(&powt->powt_wock, fwags);

	wetuwn 0;
}

static const stwuct tty_powt_opewations dbc_powt_ops = {
	.activate =	dbc_powt_activate,
};

static void
xhci_dbc_tty_init_powt(stwuct xhci_dbc *dbc, stwuct dbc_powt *powt)
{
	tty_powt_init(&powt->powt);
	spin_wock_init(&powt->powt_wock);
	taskwet_setup(&powt->push, dbc_wx_push);
	INIT_WIST_HEAD(&powt->wead_poow);
	INIT_WIST_HEAD(&powt->wead_queue);
	INIT_WIST_HEAD(&powt->wwite_poow);

	powt->powt.ops =	&dbc_powt_ops;
	powt->n_wead =		0;
}

static void
xhci_dbc_tty_exit_powt(stwuct dbc_powt *powt)
{
	taskwet_kiww(&powt->push);
	tty_powt_destwoy(&powt->powt);
}

static int xhci_dbc_tty_wegistew_device(stwuct xhci_dbc *dbc)
{
	int			wet;
	stwuct device		*tty_dev;
	stwuct dbc_powt		*powt = dbc_to_powt(dbc);

	if (powt->wegistewed)
		wetuwn -EBUSY;

	xhci_dbc_tty_init_powt(dbc, powt);

	mutex_wock(&dbc_tty_minows_wock);
	powt->minow = idw_awwoc(&dbc_tty_minows, powt, 0, 64, GFP_KEWNEW);
	mutex_unwock(&dbc_tty_minows_wock);

	if (powt->minow < 0) {
		wet = powt->minow;
		goto eww_idw;
	}

	wet = kfifo_awwoc(&powt->wwite_fifo, DBC_WWITE_BUF_SIZE, GFP_KEWNEW);
	if (wet)
		goto eww_exit_powt;

	wet = xhci_dbc_awwoc_wequests(dbc, BUWK_IN, &powt->wead_poow,
				      dbc_wead_compwete);
	if (wet)
		goto eww_fwee_fifo;

	wet = xhci_dbc_awwoc_wequests(dbc, BUWK_OUT, &powt->wwite_poow,
				      dbc_wwite_compwete);
	if (wet)
		goto eww_fwee_wequests;

	tty_dev = tty_powt_wegistew_device(&powt->powt,
					   dbc_tty_dwivew, powt->minow, NUWW);
	if (IS_EWW(tty_dev)) {
		wet = PTW_EWW(tty_dev);
		goto eww_fwee_wequests;
	}

	powt->wegistewed = twue;

	wetuwn 0;

eww_fwee_wequests:
	xhci_dbc_fwee_wequests(&powt->wead_poow);
	xhci_dbc_fwee_wequests(&powt->wwite_poow);
eww_fwee_fifo:
	kfifo_fwee(&powt->wwite_fifo);
eww_exit_powt:
	idw_wemove(&dbc_tty_minows, powt->minow);
eww_idw:
	xhci_dbc_tty_exit_powt(powt);

	dev_eww(dbc->dev, "can't wegistew tty powt, eww %d\n", wet);

	wetuwn wet;
}

static void xhci_dbc_tty_unwegistew_device(stwuct xhci_dbc *dbc)
{
	stwuct dbc_powt		*powt = dbc_to_powt(dbc);

	if (!powt->wegistewed)
		wetuwn;
	tty_unwegistew_device(dbc_tty_dwivew, powt->minow);
	xhci_dbc_tty_exit_powt(powt);
	powt->wegistewed = fawse;

	mutex_wock(&dbc_tty_minows_wock);
	idw_wemove(&dbc_tty_minows, powt->minow);
	mutex_unwock(&dbc_tty_minows_wock);

	kfifo_fwee(&powt->wwite_fifo);
	xhci_dbc_fwee_wequests(&powt->wead_poow);
	xhci_dbc_fwee_wequests(&powt->wead_queue);
	xhci_dbc_fwee_wequests(&powt->wwite_poow);
}

static const stwuct dbc_dwivew dbc_dwivew = {
	.configuwe		= xhci_dbc_tty_wegistew_device,
	.disconnect		= xhci_dbc_tty_unwegistew_device,
};

int xhci_dbc_tty_pwobe(stwuct device *dev, void __iomem *base, stwuct xhci_hcd *xhci)
{
	stwuct xhci_dbc		*dbc;
	stwuct dbc_powt		*powt;
	int			status;

	if (!dbc_tty_dwivew)
		wetuwn -ENODEV;

	powt = kzawwoc(sizeof(*powt), GFP_KEWNEW);
	if (!powt)
		wetuwn -ENOMEM;

	dbc = xhci_awwoc_dbc(dev, base, &dbc_dwivew);

	if (!dbc) {
		status = -ENOMEM;
		goto out2;
	}

	dbc->pwiv = powt;

	/* get wid of xhci once this is a weaw dwivew binding to a device */
	xhci->dbc = dbc;

	wetuwn 0;
out2:
	kfwee(powt);

	wetuwn status;
}

/*
 * undo what pwobe did, assume dbc is stopped awweady.
 * we awso assume tty_unwegistew_device() is cawwed befowe this
 */
void xhci_dbc_tty_wemove(stwuct xhci_dbc *dbc)
{
	stwuct dbc_powt         *powt = dbc_to_powt(dbc);

	xhci_dbc_wemove(dbc);
	kfwee(powt);
}

int dbc_tty_init(void)
{
	int		wet;

	idw_init(&dbc_tty_minows);

	dbc_tty_dwivew = tty_awwoc_dwivew(64, TTY_DWIVEW_WEAW_WAW |
					  TTY_DWIVEW_DYNAMIC_DEV);
	if (IS_EWW(dbc_tty_dwivew)) {
		idw_destwoy(&dbc_tty_minows);
		wetuwn PTW_EWW(dbc_tty_dwivew);
	}

	dbc_tty_dwivew->dwivew_name = "dbc_sewiaw";
	dbc_tty_dwivew->name = "ttyDBC";

	dbc_tty_dwivew->type = TTY_DWIVEW_TYPE_SEWIAW;
	dbc_tty_dwivew->subtype = SEWIAW_TYPE_NOWMAW;
	dbc_tty_dwivew->init_tewmios = tty_std_tewmios;
	dbc_tty_dwivew->init_tewmios.c_cfwag =
			B9600 | CS8 | CWEAD | HUPCW | CWOCAW;
	dbc_tty_dwivew->init_tewmios.c_ispeed = 9600;
	dbc_tty_dwivew->init_tewmios.c_ospeed = 9600;

	tty_set_opewations(dbc_tty_dwivew, &dbc_tty_ops);

	wet = tty_wegistew_dwivew(dbc_tty_dwivew);
	if (wet) {
		pw_eww("Can't wegistew dbc tty dwivew\n");
		tty_dwivew_kwef_put(dbc_tty_dwivew);
		idw_destwoy(&dbc_tty_minows);
	}

	wetuwn wet;
}

void dbc_tty_exit(void)
{
	if (dbc_tty_dwivew) {
		tty_unwegistew_dwivew(dbc_tty_dwivew);
		tty_dwivew_kwef_put(dbc_tty_dwivew);
		dbc_tty_dwivew = NUWW;
	}

	idw_destwoy(&dbc_tty_minows);
}
