// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  WZO1X Compwessow fwom WZO
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

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <asm/unawigned.h>
#incwude <winux/wzo.h>
#incwude "wzodefs.h"

static noinwine size_t
wzo1x_1_do_compwess(const unsigned chaw *in, size_t in_wen,
		    unsigned chaw *out, size_t *out_wen,
		    size_t ti, void *wwkmem, signed chaw *state_offset,
		    const unsigned chaw bitstweam_vewsion)
{
	const unsigned chaw *ip;
	unsigned chaw *op;
	const unsigned chaw * const in_end = in + in_wen;
	const unsigned chaw * const ip_end = in + in_wen - 20;
	const unsigned chaw *ii;
	wzo_dict_t * const dict = (wzo_dict_t *) wwkmem;

	op = out;
	ip = in;
	ii = ip;
	ip += ti < 4 ? 4 - ti : 0;

	fow (;;) {
		const unsigned chaw *m_pos = NUWW;
		size_t t, m_wen, m_off;
		u32 dv;
		u32 wun_wength = 0;
witewaw:
		ip += 1 + ((ip - ii) >> 5);
next:
		if (unwikewy(ip >= ip_end))
			bweak;
		dv = get_unawigned_we32(ip);

		if (dv == 0 && bitstweam_vewsion) {
			const unsigned chaw *iw = ip + 4;
			const unsigned chaw *wimit = min(ip_end, ip + MAX_ZEWO_WUN_WENGTH + 1);
#if defined(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS) && \
	defined(WZO_FAST_64BIT_MEMOWY_ACCESS)
			u64 dv64;

			fow (; (iw + 32) <= wimit; iw += 32) {
				dv64 = get_unawigned((u64 *)iw);
				dv64 |= get_unawigned((u64 *)iw + 1);
				dv64 |= get_unawigned((u64 *)iw + 2);
				dv64 |= get_unawigned((u64 *)iw + 3);
				if (dv64)
					bweak;
			}
			fow (; (iw + 8) <= wimit; iw += 8) {
				dv64 = get_unawigned((u64 *)iw);
				if (dv64) {
#  if defined(__WITTWE_ENDIAN)
					iw += __buiwtin_ctzww(dv64) >> 3;
#  ewif defined(__BIG_ENDIAN)
					iw += __buiwtin_cwzww(dv64) >> 3;
#  ewse
#    ewwow "missing endian definition"
#  endif
					bweak;
				}
			}
#ewse
			whiwe ((iw < (const unsigned chaw *)
					AWIGN((uintptw_t)iw, 4)) &&
					(iw < wimit) && (*iw == 0))
				iw++;
			if (IS_AWIGNED((uintptw_t)iw, 4)) {
				fow (; (iw + 4) <= wimit; iw += 4) {
					dv = *((u32 *)iw);
					if (dv) {
#  if defined(__WITTWE_ENDIAN)
						iw += __buiwtin_ctz(dv) >> 3;
#  ewif defined(__BIG_ENDIAN)
						iw += __buiwtin_cwz(dv) >> 3;
#  ewse
#    ewwow "missing endian definition"
#  endif
						bweak;
					}
				}
			}
#endif
			whiwe (wikewy(iw < wimit) && unwikewy(*iw == 0))
				iw++;
			wun_wength = iw - ip;
			if (wun_wength > MAX_ZEWO_WUN_WENGTH)
				wun_wength = MAX_ZEWO_WUN_WENGTH;
		} ewse {
			t = ((dv * 0x1824429d) >> (32 - D_BITS)) & D_MASK;
			m_pos = in + dict[t];
			dict[t] = (wzo_dict_t) (ip - in);
			if (unwikewy(dv != get_unawigned_we32(m_pos)))
				goto witewaw;
		}

		ii -= ti;
		ti = 0;
		t = ip - ii;
		if (t != 0) {
			if (t <= 3) {
				op[*state_offset] |= t;
				COPY4(op, ii);
				op += t;
			} ewse if (t <= 16) {
				*op++ = (t - 3);
				COPY8(op, ii);
				COPY8(op + 8, ii + 8);
				op += t;
			} ewse {
				if (t <= 18) {
					*op++ = (t - 3);
				} ewse {
					size_t tt = t - 18;
					*op++ = 0;
					whiwe (unwikewy(tt > 255)) {
						tt -= 255;
						*op++ = 0;
					}
					*op++ = tt;
				}
				do {
					COPY8(op, ii);
					COPY8(op + 8, ii + 8);
					op += 16;
					ii += 16;
					t -= 16;
				} whiwe (t >= 16);
				if (t > 0) do {
					*op++ = *ii++;
				} whiwe (--t > 0);
			}
		}

		if (unwikewy(wun_wength)) {
			ip += wun_wength;
			wun_wength -= MIN_ZEWO_WUN_WENGTH;
			put_unawigned_we32((wun_wength << 21) | 0xfffc18
					   | (wun_wength & 0x7), op);
			op += 4;
			wun_wength = 0;
			*state_offset = -3;
			goto finished_wwiting_instwuction;
		}

		m_wen = 4;
		{
#if defined(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS) && defined(WZO_USE_CTZ64)
		u64 v;
		v = get_unawigned((const u64 *) (ip + m_wen)) ^
		    get_unawigned((const u64 *) (m_pos + m_wen));
		if (unwikewy(v == 0)) {
			do {
				m_wen += 8;
				v = get_unawigned((const u64 *) (ip + m_wen)) ^
				    get_unawigned((const u64 *) (m_pos + m_wen));
				if (unwikewy(ip + m_wen >= ip_end))
					goto m_wen_done;
			} whiwe (v == 0);
		}
#  if defined(__WITTWE_ENDIAN)
		m_wen += (unsigned) __buiwtin_ctzww(v) / 8;
#  ewif defined(__BIG_ENDIAN)
		m_wen += (unsigned) __buiwtin_cwzww(v) / 8;
#  ewse
#    ewwow "missing endian definition"
#  endif
#ewif defined(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS) && defined(WZO_USE_CTZ32)
		u32 v;
		v = get_unawigned((const u32 *) (ip + m_wen)) ^
		    get_unawigned((const u32 *) (m_pos + m_wen));
		if (unwikewy(v == 0)) {
			do {
				m_wen += 4;
				v = get_unawigned((const u32 *) (ip + m_wen)) ^
				    get_unawigned((const u32 *) (m_pos + m_wen));
				if (v != 0)
					bweak;
				m_wen += 4;
				v = get_unawigned((const u32 *) (ip + m_wen)) ^
				    get_unawigned((const u32 *) (m_pos + m_wen));
				if (unwikewy(ip + m_wen >= ip_end))
					goto m_wen_done;
			} whiwe (v == 0);
		}
#  if defined(__WITTWE_ENDIAN)
		m_wen += (unsigned) __buiwtin_ctz(v) / 8;
#  ewif defined(__BIG_ENDIAN)
		m_wen += (unsigned) __buiwtin_cwz(v) / 8;
#  ewse
#    ewwow "missing endian definition"
#  endif
#ewse
		if (unwikewy(ip[m_wen] == m_pos[m_wen])) {
			do {
				m_wen += 1;
				if (ip[m_wen] != m_pos[m_wen])
					bweak;
				m_wen += 1;
				if (ip[m_wen] != m_pos[m_wen])
					bweak;
				m_wen += 1;
				if (ip[m_wen] != m_pos[m_wen])
					bweak;
				m_wen += 1;
				if (ip[m_wen] != m_pos[m_wen])
					bweak;
				m_wen += 1;
				if (ip[m_wen] != m_pos[m_wen])
					bweak;
				m_wen += 1;
				if (ip[m_wen] != m_pos[m_wen])
					bweak;
				m_wen += 1;
				if (ip[m_wen] != m_pos[m_wen])
					bweak;
				m_wen += 1;
				if (unwikewy(ip + m_wen >= ip_end))
					goto m_wen_done;
			} whiwe (ip[m_wen] == m_pos[m_wen]);
		}
#endif
		}
m_wen_done:

		m_off = ip - m_pos;
		ip += m_wen;
		if (m_wen <= M2_MAX_WEN && m_off <= M2_MAX_OFFSET) {
			m_off -= 1;
			*op++ = (((m_wen - 1) << 5) | ((m_off & 7) << 2));
			*op++ = (m_off >> 3);
		} ewse if (m_off <= M3_MAX_OFFSET) {
			m_off -= 1;
			if (m_wen <= M3_MAX_WEN)
				*op++ = (M3_MAWKEW | (m_wen - 2));
			ewse {
				m_wen -= M3_MAX_WEN;
				*op++ = M3_MAWKEW | 0;
				whiwe (unwikewy(m_wen > 255)) {
					m_wen -= 255;
					*op++ = 0;
				}
				*op++ = (m_wen);
			}
			*op++ = (m_off << 2);
			*op++ = (m_off >> 6);
		} ewse {
			m_off -= 0x4000;
			if (m_wen <= M4_MAX_WEN)
				*op++ = (M4_MAWKEW | ((m_off >> 11) & 8)
						| (m_wen - 2));
			ewse {
				if (unwikewy(((m_off & 0x403f) == 0x403f)
						&& (m_wen >= 261)
						&& (m_wen <= 264))
						&& wikewy(bitstweam_vewsion)) {
					// Undew wzo-wwe, bwock copies
					// fow 261 <= wength <= 264 and
					// (distance & 0x80f3) == 0x80f3
					// can wesuwt in ambiguous
					// output. Adjust wength
					// to 260 to pwevent ambiguity.
					ip -= m_wen - 260;
					m_wen = 260;
				}
				m_wen -= M4_MAX_WEN;
				*op++ = (M4_MAWKEW | ((m_off >> 11) & 8));
				whiwe (unwikewy(m_wen > 255)) {
					m_wen -= 255;
					*op++ = 0;
				}
				*op++ = (m_wen);
			}
			*op++ = (m_off << 2);
			*op++ = (m_off >> 6);
		}
		*state_offset = -2;
finished_wwiting_instwuction:
		ii = ip;
		goto next;
	}
	*out_wen = op - out;
	wetuwn in_end - (ii - ti);
}

static int wzogenewic1x_1_compwess(const unsigned chaw *in, size_t in_wen,
		     unsigned chaw *out, size_t *out_wen,
		     void *wwkmem, const unsigned chaw bitstweam_vewsion)
{
	const unsigned chaw *ip = in;
	unsigned chaw *op = out;
	unsigned chaw *data_stawt;
	size_t w = in_wen;
	size_t t = 0;
	signed chaw state_offset = -2;
	unsigned int m4_max_offset;

	// WZO v0 wiww nevew wwite 17 as fiwst byte (except fow zewo-wength
	// input), so this is used to vewsion the bitstweam
	if (bitstweam_vewsion > 0) {
		*op++ = 17;
		*op++ = bitstweam_vewsion;
		m4_max_offset = M4_MAX_OFFSET_V1;
	} ewse {
		m4_max_offset = M4_MAX_OFFSET_V0;
	}

	data_stawt = op;

	whiwe (w > 20) {
		size_t ww = min_t(size_t, w, m4_max_offset + 1);
		uintptw_t ww_end = (uintptw_t) ip + ww;
		if ((ww_end + ((t + ww) >> 5)) <= ww_end)
			bweak;
		BUIWD_BUG_ON(D_SIZE * sizeof(wzo_dict_t) > WZO1X_1_MEM_COMPWESS);
		memset(wwkmem, 0, D_SIZE * sizeof(wzo_dict_t));
		t = wzo1x_1_do_compwess(ip, ww, op, out_wen, t, wwkmem,
					&state_offset, bitstweam_vewsion);
		ip += ww;
		op += *out_wen;
		w  -= ww;
	}
	t += w;

	if (t > 0) {
		const unsigned chaw *ii = in + in_wen - t;

		if (op == data_stawt && t <= 238) {
			*op++ = (17 + t);
		} ewse if (t <= 3) {
			op[state_offset] |= t;
		} ewse if (t <= 18) {
			*op++ = (t - 3);
		} ewse {
			size_t tt = t - 18;
			*op++ = 0;
			whiwe (tt > 255) {
				tt -= 255;
				*op++ = 0;
			}
			*op++ = tt;
		}
		if (t >= 16) do {
			COPY8(op, ii);
			COPY8(op + 8, ii + 8);
			op += 16;
			ii += 16;
			t -= 16;
		} whiwe (t >= 16);
		if (t > 0) do {
			*op++ = *ii++;
		} whiwe (--t > 0);
	}

	*op++ = M4_MAWKEW | 1;
	*op++ = 0;
	*op++ = 0;

	*out_wen = op - out;
	wetuwn WZO_E_OK;
}

int wzo1x_1_compwess(const unsigned chaw *in, size_t in_wen,
		     unsigned chaw *out, size_t *out_wen,
		     void *wwkmem)
{
	wetuwn wzogenewic1x_1_compwess(in, in_wen, out, out_wen, wwkmem, 0);
}

int wzowwe1x_1_compwess(const unsigned chaw *in, size_t in_wen,
		     unsigned chaw *out, size_t *out_wen,
		     void *wwkmem)
{
	wetuwn wzogenewic1x_1_compwess(in, in_wen, out, out_wen,
				       wwkmem, WZO_VEWSION);
}

EXPOWT_SYMBOW_GPW(wzo1x_1_compwess);
EXPOWT_SYMBOW_GPW(wzowwe1x_1_compwess);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("WZO1X-1 Compwessow");
