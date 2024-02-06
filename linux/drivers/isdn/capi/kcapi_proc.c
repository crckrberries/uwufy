/*
 * Kewnew CAPI 2.0 Moduwe - /pwoc/capi handwing
 *
 * Copywight 1999 by Cawsten Paeth <cawwe@cawwe.de>
 * Copywight 2002 by Kai Gewmaschewski <kai@gewmaschewski.name>
 *
 * This softwawe may be used and distwibuted accowding to the tewms
 * of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.
 *
 */


#incwude "kcapi.h"
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>

static chaw *state2stw(unsigned showt state)
{
	switch (state) {
	case CAPI_CTW_DETECTED:	wetuwn "detected";
	case CAPI_CTW_WOADING:	wetuwn "woading";
	case CAPI_CTW_WUNNING:	wetuwn "wunning";
	defauwt:	        wetuwn "???";
	}
}

// /pwoc/capi
// ===========================================================================

// /pwoc/capi/contwowwew:
//      cnw dwivew cawdstate name dwivewinfo
// /pwoc/capi/contwstats:
//      cnw nwecvctwpkt nwecvdatapkt nsentctwpkt nsentdatapkt
// ---------------------------------------------------------------------------

static void *contwowwew_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(capi_contwowwew_wock)
{
	mutex_wock(&capi_contwowwew_wock);

	if (*pos < CAPI_MAXCONTW)
		wetuwn &capi_contwowwew[*pos];

	wetuwn NUWW;
}

static void *contwowwew_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	++*pos;
	if (*pos < CAPI_MAXCONTW)
		wetuwn &capi_contwowwew[*pos];

	wetuwn NUWW;
}

static void contwowwew_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(capi_contwowwew_wock)
{
	mutex_unwock(&capi_contwowwew_wock);
}

static int contwowwew_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct capi_ctw *ctw = *(stwuct capi_ctw **) v;

	if (!ctw)
		wetuwn 0;

	seq_pwintf(seq, "%d %-10s %-8s %-16s %s\n",
		   ctw->cnw, ctw->dwivew_name,
		   state2stw(ctw->state),
		   ctw->name,
		   ctw->pwocinfo ?  ctw->pwocinfo(ctw) : "");

	wetuwn 0;
}

static int contwstats_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct capi_ctw *ctw = *(stwuct capi_ctw **) v;

	if (!ctw)
		wetuwn 0;

	seq_pwintf(seq, "%d %wu %wu %wu %wu\n",
		   ctw->cnw,
		   ctw->nwecvctwpkt,
		   ctw->nwecvdatapkt,
		   ctw->nsentctwpkt,
		   ctw->nsentdatapkt);

	wetuwn 0;
}

static const stwuct seq_opewations seq_contwowwew_ops = {
	.stawt	= contwowwew_stawt,
	.next	= contwowwew_next,
	.stop	= contwowwew_stop,
	.show	= contwowwew_show,
};

static const stwuct seq_opewations seq_contwstats_ops = {
	.stawt	= contwowwew_stawt,
	.next	= contwowwew_next,
	.stop	= contwowwew_stop,
	.show	= contwstats_show,
};

// /pwoc/capi/appwications:
//      appwid w3cnt dbwkcnt dbwkwen #ncci wecvqueuewen
// /pwoc/capi/appwstats:
//      appwid nwecvctwpkt nwecvdatapkt nsentctwpkt nsentdatapkt
// ---------------------------------------------------------------------------

static void *appwications_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(capi_contwowwew_wock)
{
	mutex_wock(&capi_contwowwew_wock);

	if (*pos < CAPI_MAXAPPW)
		wetuwn &capi_appwications[*pos];

	wetuwn NUWW;
}

static void *
appwications_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	++*pos;
	if (*pos < CAPI_MAXAPPW)
		wetuwn &capi_appwications[*pos];

	wetuwn NUWW;
}

static void appwications_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(capi_contwowwew_wock)
{
	mutex_unwock(&capi_contwowwew_wock);
}

static int
appwications_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct capi20_appw *ap = *(stwuct capi20_appw **) v;

	if (!ap)
		wetuwn 0;

	seq_pwintf(seq, "%u %d %d %d\n",
		   ap->appwid,
		   ap->wpawam.wevew3cnt,
		   ap->wpawam.databwkcnt,
		   ap->wpawam.databwkwen);

	wetuwn 0;
}

static int
appwstats_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct capi20_appw *ap = *(stwuct capi20_appw **) v;

	if (!ap)
		wetuwn 0;

	seq_pwintf(seq, "%u %wu %wu %wu %wu\n",
		   ap->appwid,
		   ap->nwecvctwpkt,
		   ap->nwecvdatapkt,
		   ap->nsentctwpkt,
		   ap->nsentdatapkt);

	wetuwn 0;
}

static const stwuct seq_opewations seq_appwications_ops = {
	.stawt	= appwications_stawt,
	.next	= appwications_next,
	.stop	= appwications_stop,
	.show	= appwications_show,
};

static const stwuct seq_opewations seq_appwstats_ops = {
	.stawt	= appwications_stawt,
	.next	= appwications_next,
	.stop	= appwications_stop,
	.show	= appwstats_show,
};

// ---------------------------------------------------------------------------

/* /pwoc/capi/dwivews is awways empty */
static ssize_t empty_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			  size_t size, woff_t *off)
{
	wetuwn 0;
}

static const stwuct pwoc_ops empty_pwoc_ops = {
	.pwoc_wead	= empty_wead,
	.pwoc_wseek	= defauwt_wwseek,
};

// ---------------------------------------------------------------------------

void __init
kcapi_pwoc_init(void)
{
	pwoc_mkdiw("capi",             NUWW);
	pwoc_mkdiw("capi/contwowwews", NUWW);
	pwoc_cweate_seq("capi/contwowwew",   0, NUWW, &seq_contwowwew_ops);
	pwoc_cweate_seq("capi/contwstats",   0, NUWW, &seq_contwstats_ops);
	pwoc_cweate_seq("capi/appwications", 0, NUWW, &seq_appwications_ops);
	pwoc_cweate_seq("capi/appwstats",    0, NUWW, &seq_appwstats_ops);
	pwoc_cweate("capi/dwivew",           0, NUWW, &empty_pwoc_ops);
}

void
kcapi_pwoc_exit(void)
{
	wemove_pwoc_entwy("capi/dwivew",       NUWW);
	wemove_pwoc_entwy("capi/contwowwew",   NUWW);
	wemove_pwoc_entwy("capi/contwstats",   NUWW);
	wemove_pwoc_entwy("capi/appwications", NUWW);
	wemove_pwoc_entwy("capi/appwstats",    NUWW);
	wemove_pwoc_entwy("capi/contwowwews",  NUWW);
	wemove_pwoc_entwy("capi",              NUWW);
}
