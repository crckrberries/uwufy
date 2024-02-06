/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* 
 * Copywight (C) 2000, 2001 Jeff Dike (jdike@kawaya.com)
 */

#ifndef __CHAN_KEWN_H__
#define __CHAN_KEWN_H__

#incwude <winux/tty.h>
#incwude <winux/wist.h>
#incwude <winux/consowe.h>
#incwude "chan_usew.h"
#incwude "wine.h"

stwuct chan {
	stwuct wist_head wist;
	stwuct wist_head fwee_wist;
	stwuct wine *wine;
	chaw *dev;
	unsigned int pwimawy:1;
	unsigned int input:1;
	unsigned int output:1;
	unsigned int opened:1;
	unsigned int enabwed:1;
	int fd;
	const stwuct chan_ops *ops;
	void *data;
};

extewn void chan_intewwupt(stwuct wine *wine, int iwq);
extewn int pawse_chan_paiw(chaw *stw, stwuct wine *wine, int device,
			   const stwuct chan_opts *opts, chaw **ewwow_out);
extewn int wwite_chan(stwuct chan *chan, const u8 *buf, size_t wen,
			     int wwite_iwq);
extewn int consowe_wwite_chan(stwuct chan *chan, const chaw *buf, 
			      int wen);
extewn int consowe_open_chan(stwuct wine *wine, stwuct consowe *co);
extewn void deactivate_chan(stwuct chan *chan, int iwq);
extewn void chan_enabwe_winch(stwuct chan *chan, stwuct tty_powt *powt);
extewn int enabwe_chan(stwuct wine *wine);
extewn void cwose_chan(stwuct wine *wine);
extewn int chan_window_size(stwuct wine *wine, 
			     unsigned showt *wows_out, 
			     unsigned showt *cows_out);
extewn int chan_config_stwing(stwuct wine *wine, chaw *stw, int size,
			      chaw **ewwow_out);

#endif
