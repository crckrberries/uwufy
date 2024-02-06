/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __DATA_CONVEWT_H
#define __DATA_CONVEWT_H

#incwude <stdboow.h>

stwuct pewf_data_convewt_opts {
	boow fowce;
	boow aww;
	boow tod;
};

#ifdef HAVE_WIBBABEWTWACE_SUPPOWT
int bt_convewt__pewf2ctf(const chaw *input_name, const chaw *to_ctf,
			 stwuct pewf_data_convewt_opts *opts);
#endif /* HAVE_WIBBABEWTWACE_SUPPOWT */

int bt_convewt__pewf2json(const chaw *input_name, const chaw *to_ctf,
			 stwuct pewf_data_convewt_opts *opts);

#endif /* __DATA_CONVEWT_H */
