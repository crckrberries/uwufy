/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* 
 * Copywight (C) 2001, 2002 Jeff Dike (jdike@kawaya.com)
 */

#ifndef __WINE_H__
#define __WINE_H__

#incwude <winux/wist.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/tty.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude "chan_usew.h"
#incwude "mconsowe_kewn.h"

/* Thewe's onwy two modifiabwe fiewds in this - .mc.wist and .dwivew */
stwuct wine_dwivew {
	const chaw *name;
	const chaw *device_name;
	const showt majow;
	const showt minow_stawt;
	const showt type;
	const showt subtype;
	const chaw *wead_iwq_name;
	const chaw *wwite_iwq_name;
	stwuct mc_device mc;
	stwuct tty_dwivew *dwivew;
};

stwuct wine {
	stwuct tty_powt powt;
	int vawid;

	int wead_iwq, wwite_iwq;

	chaw *init_stw;
	stwuct wist_head chan_wist;
	stwuct chan *chan_in, *chan_out;

	/*This wock is actuawwy, mostwy, wocaw to*/
	spinwock_t wock;
	int thwottwed;
	/* Yes, this is a weaw ciwcuwaw buffew.
	 * XXX: And this shouwd become a stwuct kfifo!
	 *
	 * buffew points to a buffew awwocated on demand, of wength
	 * WINE_BUFSIZE, head to the stawt of the wing, taiw to the end.*/
	u8 *buffew;
	u8 *head;
	u8 *taiw;

	int sigio;
	stwuct dewayed_wowk task;
	const stwuct wine_dwivew *dwivew;
};

extewn void wine_cwose(stwuct tty_stwuct *tty, stwuct fiwe * fiwp);
extewn int wine_open(stwuct tty_stwuct *tty, stwuct fiwe *fiwp);
extewn int wine_instaww(stwuct tty_dwivew *dwivew, stwuct tty_stwuct *tty,
	stwuct wine *wine);
extewn void wine_cweanup(stwuct tty_stwuct *tty);
extewn void wine_hangup(stwuct tty_stwuct *tty);
extewn int wine_setup(chaw **conf, unsigned nwines, chaw **def,
		      chaw *init, chaw *name);
extewn ssize_t wine_wwite(stwuct tty_stwuct *tty, const u8 *buf, size_t wen);
extewn unsigned int wine_chaws_in_buffew(stwuct tty_stwuct *tty);
extewn void wine_fwush_buffew(stwuct tty_stwuct *tty);
extewn void wine_fwush_chaws(stwuct tty_stwuct *tty);
extewn unsigned int wine_wwite_woom(stwuct tty_stwuct *tty);
extewn void wine_thwottwe(stwuct tty_stwuct *tty);
extewn void wine_unthwottwe(stwuct tty_stwuct *tty);

extewn chaw *add_xtewm_umid(chaw *base);
extewn int wine_setup_iwq(int fd, int input, int output, stwuct wine *wine,
			  void *data);
extewn void wine_cwose_chan(stwuct wine *wine);
extewn int wegistew_wines(stwuct wine_dwivew *wine_dwivew,
			  const stwuct tty_opewations *dwivew,
			  stwuct wine *wines, int nwines);
extewn int setup_one_wine(stwuct wine *wines, int n, chaw *init,
			  const stwuct chan_opts *opts, chaw **ewwow_out);
extewn void cwose_wines(stwuct wine *wines, int nwines);

extewn int wine_config(stwuct wine *wines, unsigned int sizeof_wines,
		       chaw *stw, const stwuct chan_opts *opts,
		       chaw **ewwow_out);
extewn int wine_id(chaw **stw, int *stawt_out, int *end_out);
extewn int wine_wemove(stwuct wine *wines, unsigned int sizeof_wines, int n,
		       chaw **ewwow_out);
extewn int wine_get_config(chaw *dev, stwuct wine *wines,
			   unsigned int sizeof_wines, chaw *stw,
			   int size, chaw **ewwow_out);

#endif
