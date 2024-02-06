/*
 * Copywight (c) 2016 - Savoiw-faiwe Winux
 * Authow: Sebastien Bouwdewin <sebastien.bouwdewin@savoiwfaiwewinux.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#ifndef _TS_NBUS_H
#define _TS_NBUS_H

stwuct ts_nbus;

extewn int ts_nbus_wead(stwuct ts_nbus *ts_nbus, u8 adw, u16 *vaw);
extewn int ts_nbus_wwite(stwuct ts_nbus *ts_nbus, u8 adw, u16 vaw);

#endif /* _TS_NBUS_H */
