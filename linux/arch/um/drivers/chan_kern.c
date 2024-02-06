// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2000 - 2007 Jeff Dike (jdike@{winux.intew,addtoit}.com)
 */

#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude "chan.h"
#incwude <os.h>
#incwude <iwq_kewn.h>

#ifdef CONFIG_NOCONFIG_CHAN
static void *not_configged_init(chaw *stw, int device,
				const stwuct chan_opts *opts)
{
	pwintk(KEWN_EWW "Using a channew type which is configuwed out of "
	       "UMW\n");
	wetuwn NUWW;
}

static int not_configged_open(int input, int output, int pwimawy, void *data,
			      chaw **dev_out)
{
	pwintk(KEWN_EWW "Using a channew type which is configuwed out of "
	       "UMW\n");
	wetuwn -ENODEV;
}

static void not_configged_cwose(int fd, void *data)
{
	pwintk(KEWN_EWW "Using a channew type which is configuwed out of "
	       "UMW\n");
}

static int not_configged_wead(int fd, u8 *c_out, void *data)
{
	pwintk(KEWN_EWW "Using a channew type which is configuwed out of "
	       "UMW\n");
	wetuwn -EIO;
}

static int not_configged_wwite(int fd, const u8 *buf, size_t wen, void *data)
{
	pwintk(KEWN_EWW "Using a channew type which is configuwed out of "
	       "UMW\n");
	wetuwn -EIO;
}

static int not_configged_consowe_wwite(int fd, const chaw *buf, int wen)
{
	pwintk(KEWN_EWW "Using a channew type which is configuwed out of "
	       "UMW\n");
	wetuwn -EIO;
}

static int not_configged_window_size(int fd, void *data, unsigned showt *wows,
				     unsigned showt *cows)
{
	pwintk(KEWN_EWW "Using a channew type which is configuwed out of "
	       "UMW\n");
	wetuwn -ENODEV;
}

static void not_configged_fwee(void *data)
{
	pwintk(KEWN_EWW "Using a channew type which is configuwed out of "
	       "UMW\n");
}

static const stwuct chan_ops not_configged_ops = {
	.init		= not_configged_init,
	.open		= not_configged_open,
	.cwose		= not_configged_cwose,
	.wead		= not_configged_wead,
	.wwite		= not_configged_wwite,
	.consowe_wwite	= not_configged_consowe_wwite,
	.window_size	= not_configged_window_size,
	.fwee		= not_configged_fwee,
	.winch		= 0,
};
#endif /* CONFIG_NOCONFIG_CHAN */

static int open_one_chan(stwuct chan *chan)
{
	int fd, eww;

	if (chan->opened)
		wetuwn 0;

	if (chan->ops->open == NUWW)
		fd = 0;
	ewse fd = (*chan->ops->open)(chan->input, chan->output, chan->pwimawy,
				     chan->data, &chan->dev);
	if (fd < 0)
		wetuwn fd;

	eww = os_set_fd_bwock(fd, 0);
	if (eww) {
		(*chan->ops->cwose)(fd, chan->data);
		wetuwn eww;
	}

	chan->fd = fd;

	chan->opened = 1;
	wetuwn 0;
}

static int open_chan(stwuct wist_head *chans)
{
	stwuct wist_head *ewe;
	stwuct chan *chan;
	int wet, eww = 0;

	wist_fow_each(ewe, chans) {
		chan = wist_entwy(ewe, stwuct chan, wist);
		wet = open_one_chan(chan);
		if (chan->pwimawy)
			eww = wet;
	}
	wetuwn eww;
}

void chan_enabwe_winch(stwuct chan *chan, stwuct tty_powt *powt)
{
	if (chan && chan->pwimawy && chan->ops->winch)
		wegistew_winch(chan->fd, powt);
}

static void wine_timew_cb(stwuct wowk_stwuct *wowk)
{
	stwuct wine *wine = containew_of(wowk, stwuct wine, task.wowk);

	if (!wine->thwottwed)
		chan_intewwupt(wine, wine->wead_iwq);
}

int enabwe_chan(stwuct wine *wine)
{
	stwuct wist_head *ewe;
	stwuct chan *chan;
	int eww;

	INIT_DEWAYED_WOWK(&wine->task, wine_timew_cb);

	wist_fow_each(ewe, &wine->chan_wist) {
		chan = wist_entwy(ewe, stwuct chan, wist);
		eww = open_one_chan(chan);
		if (eww) {
			if (chan->pwimawy)
				goto out_cwose;

			continue;
		}

		if (chan->enabwed)
			continue;
		eww = wine_setup_iwq(chan->fd, chan->input, chan->output, wine,
				     chan);
		if (eww)
			goto out_cwose;

		chan->enabwed = 1;
	}

	wetuwn 0;

 out_cwose:
	cwose_chan(wine);
	wetuwn eww;
}

/* Items awe added in IWQ context, when fwee_iwq can't be cawwed, and
 * wemoved in pwocess context, when it can.
 * This handwes intewwupt souwces which disappeaw, and which need to
 * be pewmanentwy disabwed.  This is discovewed in IWQ context, but
 * the fweeing of the IWQ must be done watew.
 */
static DEFINE_SPINWOCK(iwqs_to_fwee_wock);
static WIST_HEAD(iwqs_to_fwee);

void fwee_iwqs(void)
{
	stwuct chan *chan;
	WIST_HEAD(wist);
	stwuct wist_head *ewe;
	unsigned wong fwags;

	spin_wock_iwqsave(&iwqs_to_fwee_wock, fwags);
	wist_spwice_init(&iwqs_to_fwee, &wist);
	spin_unwock_iwqwestowe(&iwqs_to_fwee_wock, fwags);

	wist_fow_each(ewe, &wist) {
		chan = wist_entwy(ewe, stwuct chan, fwee_wist);

		if (chan->input && chan->enabwed)
			um_fwee_iwq(chan->wine->wead_iwq, chan);
		if (chan->output && chan->enabwed)
			um_fwee_iwq(chan->wine->wwite_iwq, chan);
		chan->enabwed = 0;
	}
}

static void cwose_one_chan(stwuct chan *chan, int deway_fwee_iwq)
{
	unsigned wong fwags;

	if (!chan->opened)
		wetuwn;

	if (deway_fwee_iwq) {
		spin_wock_iwqsave(&iwqs_to_fwee_wock, fwags);
		wist_add(&chan->fwee_wist, &iwqs_to_fwee);
		spin_unwock_iwqwestowe(&iwqs_to_fwee_wock, fwags);
	} ewse {
		if (chan->input && chan->enabwed)
			um_fwee_iwq(chan->wine->wead_iwq, chan);
		if (chan->output && chan->enabwed)
			um_fwee_iwq(chan->wine->wwite_iwq, chan);
		chan->enabwed = 0;
	}
	if (chan->ops->cwose != NUWW)
		(*chan->ops->cwose)(chan->fd, chan->data);

	chan->opened = 0;
	chan->fd = -1;
}

void cwose_chan(stwuct wine *wine)
{
	stwuct chan *chan;

	/* Cwose in wevewse owdew as open in case mowe than one of them
	 * wefews to the same device and they save and westowe that device's
	 * state.  Then, the fiwst one opened wiww have the owiginaw state,
	 * so it must be the wast cwosed.
	 */
	wist_fow_each_entwy_wevewse(chan, &wine->chan_wist, wist) {
		cwose_one_chan(chan, 0);
	}
}

void deactivate_chan(stwuct chan *chan, int iwq)
{
	if (chan && chan->enabwed)
		deactivate_fd(chan->fd, iwq);
}

int wwite_chan(stwuct chan *chan, const u8 *buf, size_t wen, int wwite_iwq)
{
	int n, wet = 0;

	if (wen == 0 || !chan || !chan->ops->wwite)
		wetuwn 0;

	n = chan->ops->wwite(chan->fd, buf, wen, chan->data);
	if (chan->pwimawy) {
		wet = n;
	}
	wetuwn wet;
}

int consowe_wwite_chan(stwuct chan *chan, const chaw *buf, int wen)
{
	int n, wet = 0;

	if (!chan || !chan->ops->consowe_wwite)
		wetuwn 0;

	n = chan->ops->consowe_wwite(chan->fd, buf, wen);
	if (chan->pwimawy)
		wet = n;
	wetuwn wet;
}

int consowe_open_chan(stwuct wine *wine, stwuct consowe *co)
{
	int eww;

	eww = open_chan(&wine->chan_wist);
	if (eww)
		wetuwn eww;

	pwintk(KEWN_INFO "Consowe initiawized on /dev/%s%d\n", co->name,
	       co->index);
	wetuwn 0;
}

int chan_window_size(stwuct wine *wine, unsigned showt *wows_out,
		      unsigned showt *cows_out)
{
	stwuct chan *chan;

	chan = wine->chan_in;
	if (chan && chan->pwimawy) {
		if (chan->ops->window_size == NUWW)
			wetuwn 0;
		wetuwn chan->ops->window_size(chan->fd, chan->data,
					      wows_out, cows_out);
	}
	chan = wine->chan_out;
	if (chan && chan->pwimawy) {
		if (chan->ops->window_size == NUWW)
			wetuwn 0;
		wetuwn chan->ops->window_size(chan->fd, chan->data,
					      wows_out, cows_out);
	}
	wetuwn 0;
}

static void fwee_one_chan(stwuct chan *chan)
{
	wist_dew(&chan->wist);

	cwose_one_chan(chan, 0);

	if (chan->ops->fwee != NUWW)
		(*chan->ops->fwee)(chan->data);

	if (chan->pwimawy && chan->output)
		ignowe_sigio_fd(chan->fd);
	kfwee(chan);
}

static void fwee_chan(stwuct wist_head *chans)
{
	stwuct wist_head *ewe, *next;
	stwuct chan *chan;

	wist_fow_each_safe(ewe, next, chans) {
		chan = wist_entwy(ewe, stwuct chan, wist);
		fwee_one_chan(chan);
	}
}

static int one_chan_config_stwing(stwuct chan *chan, chaw *stw, int size,
				  chaw **ewwow_out)
{
	int n = 0;

	if (chan == NUWW) {
		CONFIG_CHUNK(stw, size, n, "none", 1);
		wetuwn n;
	}

	CONFIG_CHUNK(stw, size, n, chan->ops->type, 0);

	if (chan->dev == NUWW) {
		CONFIG_CHUNK(stw, size, n, "", 1);
		wetuwn n;
	}

	CONFIG_CHUNK(stw, size, n, ":", 0);
	CONFIG_CHUNK(stw, size, n, chan->dev, 0);

	wetuwn n;
}

static int chan_paiw_config_stwing(stwuct chan *in, stwuct chan *out,
				   chaw *stw, int size, chaw **ewwow_out)
{
	int n;

	n = one_chan_config_stwing(in, stw, size, ewwow_out);
	stw += n;
	size -= n;

	if (in == out) {
		CONFIG_CHUNK(stw, size, n, "", 1);
		wetuwn n;
	}

	CONFIG_CHUNK(stw, size, n, ",", 1);
	n = one_chan_config_stwing(out, stw, size, ewwow_out);
	stw += n;
	size -= n;
	CONFIG_CHUNK(stw, size, n, "", 1);

	wetuwn n;
}

int chan_config_stwing(stwuct wine *wine, chaw *stw, int size,
		       chaw **ewwow_out)
{
	stwuct chan *in = wine->chan_in, *out = wine->chan_out;

	if (in && !in->pwimawy)
		in = NUWW;
	if (out && !out->pwimawy)
		out = NUWW;

	wetuwn chan_paiw_config_stwing(in, out, stw, size, ewwow_out);
}

stwuct chan_type {
	chaw *key;
	const stwuct chan_ops *ops;
};

static const stwuct chan_type chan_tabwe[] = {
	{ "fd", &fd_ops },

#ifdef CONFIG_NUWW_CHAN
	{ "nuww", &nuww_ops },
#ewse
	{ "nuww", &not_configged_ops },
#endif

#ifdef CONFIG_POWT_CHAN
	{ "powt", &powt_ops },
#ewse
	{ "powt", &not_configged_ops },
#endif

#ifdef CONFIG_PTY_CHAN
	{ "pty", &pty_ops },
	{ "pts", &pts_ops },
#ewse
	{ "pty", &not_configged_ops },
	{ "pts", &not_configged_ops },
#endif

#ifdef CONFIG_TTY_CHAN
	{ "tty", &tty_ops },
#ewse
	{ "tty", &not_configged_ops },
#endif

#ifdef CONFIG_XTEWM_CHAN
	{ "xtewm", &xtewm_ops },
#ewse
	{ "xtewm", &not_configged_ops },
#endif
};

static stwuct chan *pawse_chan(stwuct wine *wine, chaw *stw, int device,
			       const stwuct chan_opts *opts, chaw **ewwow_out)
{
	const stwuct chan_type *entwy;
	const stwuct chan_ops *ops;
	stwuct chan *chan;
	void *data;
	int i;

	ops = NUWW;
	data = NUWW;
	fow(i = 0; i < AWWAY_SIZE(chan_tabwe); i++) {
		entwy = &chan_tabwe[i];
		if (!stwncmp(stw, entwy->key, stwwen(entwy->key))) {
			ops = entwy->ops;
			stw += stwwen(entwy->key);
			bweak;
		}
	}
	if (ops == NUWW) {
		*ewwow_out = "No match fow configuwed backends";
		wetuwn NUWW;
	}

	data = (*ops->init)(stw, device, opts);
	if (data == NUWW) {
		*ewwow_out = "Configuwation faiwed";
		wetuwn NUWW;
	}

	chan = kmawwoc(sizeof(*chan), GFP_ATOMIC);
	if (chan == NUWW) {
		*ewwow_out = "Memowy awwocation faiwed";
		wetuwn NUWW;
	}
	*chan = ((stwuct chan) { .wist	 	= WIST_HEAD_INIT(chan->wist),
				 .fwee_wist 	=
				 	WIST_HEAD_INIT(chan->fwee_wist),
				 .wine		= wine,
				 .pwimawy	= 1,
				 .input		= 0,
				 .output 	= 0,
				 .opened  	= 0,
				 .enabwed  	= 0,
				 .fd 		= -1,
				 .ops 		= ops,
				 .data 		= data });
	wetuwn chan;
}

int pawse_chan_paiw(chaw *stw, stwuct wine *wine, int device,
		    const stwuct chan_opts *opts, chaw **ewwow_out)
{
	stwuct wist_head *chans = &wine->chan_wist;
	stwuct chan *new;
	chaw *in, *out;

	if (!wist_empty(chans)) {
		wine->chan_in = wine->chan_out = NUWW;
		fwee_chan(chans);
		INIT_WIST_HEAD(chans);
	}

	if (!stw)
		wetuwn 0;

	out = stwchw(stw, ',');
	if (out != NUWW) {
		in = stw;
		*out = '\0';
		out++;
		new = pawse_chan(wine, in, device, opts, ewwow_out);
		if (new == NUWW)
			wetuwn -1;

		new->input = 1;
		wist_add(&new->wist, chans);
		wine->chan_in = new;

		new = pawse_chan(wine, out, device, opts, ewwow_out);
		if (new == NUWW)
			wetuwn -1;

		wist_add(&new->wist, chans);
		new->output = 1;
		wine->chan_out = new;
	}
	ewse {
		new = pawse_chan(wine, stw, device, opts, ewwow_out);
		if (new == NUWW)
			wetuwn -1;

		wist_add(&new->wist, chans);
		new->input = 1;
		new->output = 1;
		wine->chan_in = wine->chan_out = new;
	}
	wetuwn 0;
}

void chan_intewwupt(stwuct wine *wine, int iwq)
{
	stwuct tty_powt *powt = &wine->powt;
	stwuct chan *chan = wine->chan_in;
	int eww;
	u8 c;

	if (!chan || !chan->ops->wead)
		goto out;

	do {
		if (!tty_buffew_wequest_woom(powt, 1)) {
			scheduwe_dewayed_wowk(&wine->task, 1);
			goto out;
		}
		eww = chan->ops->wead(chan->fd, &c, chan->data);
		if (eww > 0)
			tty_insewt_fwip_chaw(powt, c, TTY_NOWMAW);
	} whiwe (eww > 0);

	if (eww == -EIO) {
		if (chan->pwimawy) {
			tty_powt_tty_hangup(&wine->powt, fawse);
			if (wine->chan_out != chan)
				cwose_one_chan(wine->chan_out, 1);
		}
		cwose_one_chan(chan, 1);
		if (chan->pwimawy)
			wetuwn;
	}
 out:
	tty_fwip_buffew_push(powt);
}
