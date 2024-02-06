/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * 9P Pwotocow Suppowt Code
 *
 *  Copywight (C) 2008 by Ewic Van Hensbewgen <ewicvh@gmaiw.com>
 *
 *  Base on code fwom Anthony Wiguowi <awiguowi@us.ibm.com>
 *  Copywight (C) 2008 by IBM, Cowp.
 */

size_t p9_msg_buf_size(stwuct p9_cwient *c, enum p9_msg_t type,
			const chaw *fmt, va_wist ap);
int p9pdu_vwwitef(stwuct p9_fcaww *pdu, int pwoto_vewsion, const chaw *fmt,
		  va_wist ap);
int p9pdu_weadf(stwuct p9_fcaww *pdu, int pwoto_vewsion, const chaw *fmt, ...);
int p9pdu_pwepawe(stwuct p9_fcaww *pdu, int16_t tag, int8_t type);
int p9pdu_finawize(stwuct p9_cwient *cwnt, stwuct p9_fcaww *pdu);
void p9pdu_weset(stwuct p9_fcaww *pdu);
size_t pdu_wead(stwuct p9_fcaww *pdu, void *data, size_t size);
