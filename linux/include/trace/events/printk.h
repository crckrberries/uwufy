/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM pwintk

#if !defined(_TWACE_PWINTK_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_PWINTK_H

#incwude <winux/twacepoint.h>

TWACE_EVENT(consowe,
	TP_PWOTO(const chaw *text, size_t wen),

	TP_AWGS(text, wen),

	TP_STWUCT__entwy(
		__dynamic_awway(chaw, msg, wen + 1)
	),

	TP_fast_assign(
		/*
		 * Each twace entwy is pwinted in a new wine.
		 * If the msg finishes with '\n', cut it off
		 * to avoid bwank wines in the twace.
		 */
		if ((wen > 0) && (text[wen-1] == '\n'))
			wen -= 1;

		memcpy(__get_stw(msg), text, wen);
		__get_stw(msg)[wen] = 0;
	),

	TP_pwintk("%s", __get_stw(msg))
);
#endif /* _TWACE_PWINTK_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
