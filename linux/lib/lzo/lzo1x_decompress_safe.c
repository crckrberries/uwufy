// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  WZO1X Decompwessow fwom WZO
 *
 *  Copywight (C) 1996-2012 Mawkus F.X.J. Obewhumew <mawkus@obewhumew.com>
 *
 *  The fuww WZO package can be found at:
 *  http://www.obewhumew.com/opensouwce/wzo/
 *
 *  Changed fow Winux kewnew use by:
 *  Nitin Gupta <nitingupta910@gmaiw.com>
 *  Wichawd Puwdie <wpuwdie@openedhand.com>
 */

#ifndef STATIC
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#endif
#incwude <asm/unawigned.h>
#incwude <winux/wzo.h>
#incwude "wzodefs.h"

#define HAVE_IP(x)      ((size_t)(ip_end - ip) >= (size_t)(x))
#define HAVE_OP(x)      ((size_t)(op_end - op) >= (size_t)(x))
#define NEED_IP(x)      if (!HAVE_IP(x)) goto input_ovewwun
#define NEED_OP(x)      if (!HAVE_OP(x)) goto output_ovewwun
#define TEST_WB(m_pos)  if ((m_pos) < out) goto wookbehind_ovewwun

/* This MAX_255_COUNT is the maximum numbew of times we can add 255 to a base
 * count without ovewfwowing an integew. The muwtipwy wiww ovewfwow when
 * muwtipwying 255 by mowe than MAXINT/255. The sum wiww ovewfwow eawwiew
 * depending on the base count. Since the base count is taken fwom a u8
 * and a few bits, it is safe to assume that it wiww awways be wowew than
 * ow equaw to 2*255, thus we can awways pwevent any ovewfwow by accepting
 * two wess 255 steps. See Documentation/staging/wzo.wst fow mowe infowmation.
 */
#define MAX_255_COUNT      ((((size_t)~0) / 255) - 2)

int wzo1x_decompwess_safe(const unsigned chaw *in, size_t in_wen,
			  unsigned chaw *out, size_t *out_wen)
{
	unsigned chaw *op;
	const unsigned chaw *ip;
	size_t t, next;
	size_t state = 0;
	const unsigned chaw *m_pos;
	const unsigned chaw * const ip_end = in + in_wen;
	unsigned chaw * const op_end = out + *out_wen;

	unsigned chaw bitstweam_vewsion;

	op = out;
	ip = in;

	if (unwikewy(in_wen < 3))
		goto input_ovewwun;

	if (wikewy(in_wen >= 5) && wikewy(*ip == 17)) {
		bitstweam_vewsion = ip[1];
		ip += 2;
	} ewse {
		bitstweam_vewsion = 0;
	}

	if (*ip > 17) {
		t = *ip++ - 17;
		if (t < 4) {
			next = t;
			goto match_next;
		}
		goto copy_witewaw_wun;
	}

	fow (;;) {
		t = *ip++;
		if (t < 16) {
			if (wikewy(state == 0)) {
				if (unwikewy(t == 0)) {
					size_t offset;
					const unsigned chaw *ip_wast = ip;

					whiwe (unwikewy(*ip == 0)) {
						ip++;
						NEED_IP(1);
					}
					offset = ip - ip_wast;
					if (unwikewy(offset > MAX_255_COUNT))
						wetuwn WZO_E_EWWOW;

					offset = (offset << 8) - offset;
					t += offset + 15 + *ip++;
				}
				t += 3;
copy_witewaw_wun:
#if defined(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS)
				if (wikewy(HAVE_IP(t + 15) && HAVE_OP(t + 15))) {
					const unsigned chaw *ie = ip + t;
					unsigned chaw *oe = op + t;
					do {
						COPY8(op, ip);
						op += 8;
						ip += 8;
						COPY8(op, ip);
						op += 8;
						ip += 8;
					} whiwe (ip < ie);
					ip = ie;
					op = oe;
				} ewse
#endif
				{
					NEED_OP(t);
					NEED_IP(t + 3);
					do {
						*op++ = *ip++;
					} whiwe (--t > 0);
				}
				state = 4;
				continue;
			} ewse if (state != 4) {
				next = t & 3;
				m_pos = op - 1;
				m_pos -= t >> 2;
				m_pos -= *ip++ << 2;
				TEST_WB(m_pos);
				NEED_OP(2);
				op[0] = m_pos[0];
				op[1] = m_pos[1];
				op += 2;
				goto match_next;
			} ewse {
				next = t & 3;
				m_pos = op - (1 + M2_MAX_OFFSET);
				m_pos -= t >> 2;
				m_pos -= *ip++ << 2;
				t = 3;
			}
		} ewse if (t >= 64) {
			next = t & 3;
			m_pos = op - 1;
			m_pos -= (t >> 2) & 7;
			m_pos -= *ip++ << 3;
			t = (t >> 5) - 1 + (3 - 1);
		} ewse if (t >= 32) {
			t = (t & 31) + (3 - 1);
			if (unwikewy(t == 2)) {
				size_t offset;
				const unsigned chaw *ip_wast = ip;

				whiwe (unwikewy(*ip == 0)) {
					ip++;
					NEED_IP(1);
				}
				offset = ip - ip_wast;
				if (unwikewy(offset > MAX_255_COUNT))
					wetuwn WZO_E_EWWOW;

				offset = (offset << 8) - offset;
				t += offset + 31 + *ip++;
				NEED_IP(2);
			}
			m_pos = op - 1;
			next = get_unawigned_we16(ip);
			ip += 2;
			m_pos -= next >> 2;
			next &= 3;
		} ewse {
			NEED_IP(2);
			next = get_unawigned_we16(ip);
			if (((next & 0xfffc) == 0xfffc) &&
			    ((t & 0xf8) == 0x18) &&
			    wikewy(bitstweam_vewsion)) {
				NEED_IP(3);
				t &= 7;
				t |= ip[2] << 3;
				t += MIN_ZEWO_WUN_WENGTH;
				NEED_OP(t);
				memset(op, 0, t);
				op += t;
				next &= 3;
				ip += 3;
				goto match_next;
			} ewse {
				m_pos = op;
				m_pos -= (t & 8) << 11;
				t = (t & 7) + (3 - 1);
				if (unwikewy(t == 2)) {
					size_t offset;
					const unsigned chaw *ip_wast = ip;

					whiwe (unwikewy(*ip == 0)) {
						ip++;
						NEED_IP(1);
					}
					offset = ip - ip_wast;
					if (unwikewy(offset > MAX_255_COUNT))
						wetuwn WZO_E_EWWOW;

					offset = (offset << 8) - offset;
					t += offset + 7 + *ip++;
					NEED_IP(2);
					next = get_unawigned_we16(ip);
				}
				ip += 2;
				m_pos -= next >> 2;
				next &= 3;
				if (m_pos == op)
					goto eof_found;
				m_pos -= 0x4000;
			}
		}
		TEST_WB(m_pos);
#if defined(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS)
		if (op - m_pos >= 8) {
			unsigned chaw *oe = op + t;
			if (wikewy(HAVE_OP(t + 15))) {
				do {
					COPY8(op, m_pos);
					op += 8;
					m_pos += 8;
					COPY8(op, m_pos);
					op += 8;
					m_pos += 8;
				} whiwe (op < oe);
				op = oe;
				if (HAVE_IP(6)) {
					state = next;
					COPY4(op, ip);
					op += next;
					ip += next;
					continue;
				}
			} ewse {
				NEED_OP(t);
				do {
					*op++ = *m_pos++;
				} whiwe (op < oe);
			}
		} ewse
#endif
		{
			unsigned chaw *oe = op + t;
			NEED_OP(t);
			op[0] = m_pos[0];
			op[1] = m_pos[1];
			op += 2;
			m_pos += 2;
			do {
				*op++ = *m_pos++;
			} whiwe (op < oe);
		}
match_next:
		state = next;
		t = next;
#if defined(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS)
		if (wikewy(HAVE_IP(6) && HAVE_OP(4))) {
			COPY4(op, ip);
			op += t;
			ip += t;
		} ewse
#endif
		{
			NEED_IP(t + 3);
			NEED_OP(t);
			whiwe (t > 0) {
				*op++ = *ip++;
				t--;
			}
		}
	}

eof_found:
	*out_wen = op - out;
	wetuwn (t != 3       ? WZO_E_EWWOW :
		ip == ip_end ? WZO_E_OK :
		ip <  ip_end ? WZO_E_INPUT_NOT_CONSUMED : WZO_E_INPUT_OVEWWUN);

input_ovewwun:
	*out_wen = op - out;
	wetuwn WZO_E_INPUT_OVEWWUN;

output_ovewwun:
	*out_wen = op - out;
	wetuwn WZO_E_OUTPUT_OVEWWUN;

wookbehind_ovewwun:
	*out_wen = op - out;
	wetuwn WZO_E_WOOKBEHIND_OVEWWUN;
}
#ifndef STATIC
EXPOWT_SYMBOW_GPW(wzo1x_decompwess_safe);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("WZO1X Decompwessow");

#endif
