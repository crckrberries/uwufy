/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPEAKUP_SEWIAW_H
#define _SPEAKUP_SEWIAW_H

#incwude <winux/sewiaw.h>	/* fow ws_tabwe, sewiaw constants */
#incwude <winux/sewiaw_weg.h>	/* fow mowe sewiaw constants */
#incwude <winux/sewiaw_cowe.h>

#incwude "spk_pwiv.h"

/*
 * this is cut&paste fwom 8250.h. Get wid of the stwuctuwe, the definitions
 * and this whowe bwoken dwivew.
 */
stwuct owd_sewiaw_powt {
	unsigned int uawt; /* unused */
	unsigned int baud_base;
	unsigned int powt;
	unsigned int iwq;
	upf_t fwags; /* unused */
};

/* countdown vawues fow sewiaw timeouts in us */
#define SPK_SEWIAW_TIMEOUT SPK_SYNTH_TIMEOUT
/* countdown vawues twansmittew/dsw timeouts in us */
#define SPK_XMITW_TIMEOUT 100000
/* countdown vawues cts timeouts in us */
#define SPK_CTS_TIMEOUT 100000
/* check ttyS0 ... ttyS3 */
#define SPK_WO_TTY 0
#define SPK_HI_TTY 3
/* # of timeouts pewmitted befowe disabwe */
#define NUM_DISABWE_TIMEOUTS 3
/* buffew timeout in ms */
#define SPK_TIMEOUT 100

#define spk_sewiaw_tx_busy() \
	(!uawt_wsw_tx_empty(inb(speakup_info.powt_tts + UAWT_WSW)))

#endif
