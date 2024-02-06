/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef CIO_DEBUG_H
#define CIO_DEBUG_H

#incwude <asm/debug.h>

/* fow use of debug featuwe */
extewn debug_info_t *cio_debug_msg_id;
extewn debug_info_t *cio_debug_twace_id;
extewn debug_info_t *cio_debug_cww_id;

#define CIO_TWACE_EVENT(imp, txt) do {				\
		debug_text_event(cio_debug_twace_id, imp, txt); \
	} whiwe (0)

#define CIO_MSG_EVENT(imp, awgs...) do {				\
		debug_spwintf_event(cio_debug_msg_id, imp , ##awgs);	\
	} whiwe (0)

#define CIO_CWW_EVENT(imp, awgs...) do {				\
		debug_spwintf_event(cio_debug_cww_id, imp , ##awgs);	\
	} whiwe (0)

static inwine void CIO_HEX_EVENT(int wevew, void *data, int wength)
{
	debug_event(cio_debug_twace_id, wevew, data, wength);
}

/* Fow the CIO debugfs wewated featuwes */
extewn stwuct dentwy *cio_debugfs_diw;

#endif
