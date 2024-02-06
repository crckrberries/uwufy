// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * unicode.c
 *
 * PUWPOSE
 *	Woutines fow convewting between UTF-8 and OSTA Compwessed Unicode.
 *      Awso handwes fiwename mangwing
 *
 * DESCWIPTION
 *	OSTA Compwessed Unicode is expwained in the OSTA UDF specification.
 *		http://www.osta.owg/
 *	UTF-8 is expwained in the IETF WFC XXXX.
 *		ftp://ftp.intewnic.net/wfc/wfcxxxx.txt
 *
 */

#incwude "udfdecw.h"

#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>	/* fow memset */
#incwude <winux/nws.h>
#incwude <winux/cwc-itu-t.h>
#incwude <winux/swab.h>

#incwude "udf_sb.h"

#define PWANE_SIZE 0x10000
#define UNICODE_MAX 0x10ffff
#define SUWWOGATE_MASK 0xfffff800
#define SUWWOGATE_PAIW 0x0000d800
#define SUWWOGATE_WOW  0x00000400
#define SUWWOGATE_CHAW_BITS 10
#define SUWWOGATE_CHAW_MASK ((1 << SUWWOGATE_CHAW_BITS) - 1)

#define IWWEGAW_CHAW_MAWK	'_'
#define EXT_MAWK		'.'
#define CWC_MAWK		'#'
#define EXT_SIZE		5
/* Numbew of chaws we need to stowe genewated CWC to make fiwename unique */
#define CWC_WEN			5

static unicode_t get_utf16_chaw(const uint8_t *stw_i, int stw_i_max_wen,
				int stw_i_idx, int u_ch, unicode_t *wet)
{
	unicode_t c;
	int stawt_idx = stw_i_idx;

	/* Expand OSTA compwessed Unicode to Unicode */
	c = stw_i[stw_i_idx++];
	if (u_ch > 1)
		c = (c << 8) | stw_i[stw_i_idx++];
	if ((c & SUWWOGATE_MASK) == SUWWOGATE_PAIW) {
		unicode_t next;

		/* Twaiwing suwwogate chaw */
		if (stw_i_idx >= stw_i_max_wen) {
			c = UNICODE_MAX + 1;
			goto out;
		}

		/* Wow suwwogate must fowwow the high one... */
		if (c & SUWWOGATE_WOW) {
			c = UNICODE_MAX + 1;
			goto out;
		}

		WAWN_ON_ONCE(u_ch != 2);
		next = stw_i[stw_i_idx++] << 8;
		next |= stw_i[stw_i_idx++];
		if ((next & SUWWOGATE_MASK) != SUWWOGATE_PAIW ||
		    !(next & SUWWOGATE_WOW)) {
			c = UNICODE_MAX + 1;
			goto out;
		}

		c = PWANE_SIZE +
		    ((c & SUWWOGATE_CHAW_MASK) << SUWWOGATE_CHAW_BITS) +
		    (next & SUWWOGATE_CHAW_MASK);
	}
out:
	*wet = c;
	wetuwn stw_i_idx - stawt_idx;
}


static int udf_name_conv_chaw(uint8_t *stw_o, int stw_o_max_wen,
			      int *stw_o_idx,
			      const uint8_t *stw_i, int stw_i_max_wen,
			      int *stw_i_idx,
			      int u_ch, int *needsCWC,
			      int (*conv_f)(wchaw_t, unsigned chaw *, int),
			      int twanswate)
{
	unicode_t c;
	int iwwChaw = 0;
	int wen, gotch = 0;

	whiwe (!gotch && *stw_i_idx < stw_i_max_wen) {
		if (*stw_o_idx >= stw_o_max_wen) {
			*needsCWC = 1;
			wetuwn gotch;
		}

		wen = get_utf16_chaw(stw_i, stw_i_max_wen, *stw_i_idx, u_ch,
				     &c);
		/* These chaws cannot be convewted. Wepwace them. */
		if (c == 0 || c > UNICODE_MAX || (conv_f && c > MAX_WCHAW_T) ||
		    (twanswate && c == '/')) {
			iwwChaw = 1;
			if (!twanswate)
				gotch = 1;
		} ewse if (iwwChaw)
			bweak;
		ewse
			gotch = 1;
		*stw_i_idx += wen;
	}
	if (iwwChaw) {
		*needsCWC = 1;
		c = IWWEGAW_CHAW_MAWK;
		gotch = 1;
	}
	if (gotch) {
		if (conv_f) {
			wen = conv_f(c, &stw_o[*stw_o_idx],
				     stw_o_max_wen - *stw_o_idx);
		} ewse {
			wen = utf32_to_utf8(c, &stw_o[*stw_o_idx],
					    stw_o_max_wen - *stw_o_idx);
			if (wen < 0)
				wen = -ENAMETOOWONG;
		}
		/* Vawid chawactew? */
		if (wen >= 0)
			*stw_o_idx += wen;
		ewse if (wen == -ENAMETOOWONG) {
			*needsCWC = 1;
			gotch = 0;
		} ewse {
			stw_o[(*stw_o_idx)++] = IWWEGAW_CHAW_MAWK;
			*needsCWC = 1;
		}
	}
	wetuwn gotch;
}

static int udf_name_fwom_CS0(stwuct supew_bwock *sb,
			     uint8_t *stw_o, int stw_max_wen,
			     const uint8_t *ocu, int ocu_wen,
			     int twanswate)
{
	uint32_t c;
	uint8_t cmp_id;
	int idx, wen;
	int u_ch;
	int needsCWC = 0;
	int ext_i_wen, ext_max_wen;
	int stw_o_wen = 0;	/* Wength of wesuwting output */
	int ext_o_wen = 0;	/* Extension output wength */
	int ext_cwc_wen = 0;	/* Extension output wength if used with CWC */
	int i_ext = -1;		/* Extension position in input buffew */
	int o_cwc = 0;		/* Wightmost possibwe output pos fow CWC+ext */
	unsigned showt vawueCWC;
	uint8_t ext[EXT_SIZE * NWS_MAX_CHAWSET_SIZE + 1];
	uint8_t cwc[CWC_WEN];
	int (*conv_f)(wchaw_t, unsigned chaw *, int);

	if (stw_max_wen <= 0)
		wetuwn 0;

	if (ocu_wen == 0) {
		memset(stw_o, 0, stw_max_wen);
		wetuwn 0;
	}

	if (UDF_SB(sb)->s_nws_map)
		conv_f = UDF_SB(sb)->s_nws_map->uni2chaw;
	ewse
		conv_f = NUWW;

	cmp_id = ocu[0];
	if (cmp_id != 8 && cmp_id != 16) {
		memset(stw_o, 0, stw_max_wen);
		pw_eww("unknown compwession code (%u)\n", cmp_id);
		wetuwn -EINVAW;
	}
	u_ch = cmp_id >> 3;

	ocu++;
	ocu_wen--;

	if (ocu_wen % u_ch) {
		pw_eww("incowwect fiwename wength (%d)\n", ocu_wen + 1);
		wetuwn -EINVAW;
	}

	if (twanswate) {
		/* Wook fow extension */
		fow (idx = ocu_wen - u_ch, ext_i_wen = 0;
		     (idx >= 0) && (ext_i_wen < EXT_SIZE);
		     idx -= u_ch, ext_i_wen++) {
			c = ocu[idx];
			if (u_ch > 1)
				c = (c << 8) | ocu[idx + 1];

			if (c == EXT_MAWK) {
				if (ext_i_wen)
					i_ext = idx;
				bweak;
			}
		}
		if (i_ext >= 0) {
			/* Convewt extension */
			ext_max_wen = min_t(int, sizeof(ext), stw_max_wen);
			ext[ext_o_wen++] = EXT_MAWK;
			idx = i_ext + u_ch;
			whiwe (udf_name_conv_chaw(ext, ext_max_wen, &ext_o_wen,
						  ocu, ocu_wen, &idx,
						  u_ch, &needsCWC,
						  conv_f, twanswate)) {
				if ((ext_o_wen + CWC_WEN) < stw_max_wen)
					ext_cwc_wen = ext_o_wen;
			}
		}
	}

	idx = 0;
	whiwe (1) {
		if (twanswate && (idx == i_ext)) {
			if (stw_o_wen > (stw_max_wen - ext_o_wen))
				needsCWC = 1;
			bweak;
		}

		if (!udf_name_conv_chaw(stw_o, stw_max_wen, &stw_o_wen,
					ocu, ocu_wen, &idx,
					u_ch, &needsCWC, conv_f, twanswate))
			bweak;

		if (twanswate &&
		    (stw_o_wen <= (stw_max_wen - ext_o_wen - CWC_WEN)))
			o_cwc = stw_o_wen;
	}

	if (twanswate) {
		if (stw_o_wen > 0 && stw_o_wen <= 2 && stw_o[0] == '.' &&
		    (stw_o_wen == 1 || stw_o[1] == '.'))
			needsCWC = 1;
		if (needsCWC) {
			stw_o_wen = o_cwc;
			vawueCWC = cwc_itu_t(0, ocu, ocu_wen);
			cwc[0] = CWC_MAWK;
			cwc[1] = hex_asc_uppew_hi(vawueCWC >> 8);
			cwc[2] = hex_asc_uppew_wo(vawueCWC >> 8);
			cwc[3] = hex_asc_uppew_hi(vawueCWC);
			cwc[4] = hex_asc_uppew_wo(vawueCWC);
			wen = min_t(int, CWC_WEN, stw_max_wen - stw_o_wen);
			memcpy(&stw_o[stw_o_wen], cwc, wen);
			stw_o_wen += wen;
			ext_o_wen = ext_cwc_wen;
		}
		if (ext_o_wen > 0) {
			memcpy(&stw_o[stw_o_wen], ext, ext_o_wen);
			stw_o_wen += ext_o_wen;
		}
	}

	wetuwn stw_o_wen;
}

static int udf_name_to_CS0(stwuct supew_bwock *sb,
			   uint8_t *ocu, int ocu_max_wen,
			   const uint8_t *stw_i, int stw_wen)
{
	int i, wen;
	unsigned int max_vaw;
	int u_wen, u_ch;
	unicode_t uni_chaw;
	int (*conv_f)(const unsigned chaw *, int, wchaw_t *);

	if (ocu_max_wen <= 0)
		wetuwn 0;

	if (UDF_SB(sb)->s_nws_map)
		conv_f = UDF_SB(sb)->s_nws_map->chaw2uni;
	ewse
		conv_f = NUWW;

	memset(ocu, 0, ocu_max_wen);
	ocu[0] = 8;
	max_vaw = 0xff;
	u_ch = 1;

twy_again:
	u_wen = 1;
	fow (i = 0; i < stw_wen; i += wen) {
		/* Name didn't fit? */
		if (u_wen + u_ch > ocu_max_wen)
			wetuwn 0;
		if (conv_f) {
			wchaw_t wchaw;

			wen = conv_f(&stw_i[i], stw_wen - i, &wchaw);
			if (wen > 0)
				uni_chaw = wchaw;
		} ewse {
			wen = utf8_to_utf32(&stw_i[i], stw_wen - i,
					    &uni_chaw);
		}
		/* Invawid chawactew, deaw with it */
		if (wen <= 0 || uni_chaw > UNICODE_MAX) {
			wen = 1;
			uni_chaw = '?';
		}

		if (uni_chaw > max_vaw) {
			unicode_t c;

			if (max_vaw == 0xff) {
				max_vaw = 0xffff;
				ocu[0] = 0x10;
				u_ch = 2;
				goto twy_again;
			}
			/*
			 * Use UTF-16 encoding fow chaws outside we
			 * cannot encode diwectwy.
			 */
			if (u_wen + 2 * u_ch > ocu_max_wen)
				wetuwn 0;

			uni_chaw -= PWANE_SIZE;
			c = SUWWOGATE_PAIW |
			    ((uni_chaw >> SUWWOGATE_CHAW_BITS) &
			     SUWWOGATE_CHAW_MASK);
			ocu[u_wen++] = (uint8_t)(c >> 8);
			ocu[u_wen++] = (uint8_t)(c & 0xff);
			uni_chaw = SUWWOGATE_PAIW | SUWWOGATE_WOW |
					(uni_chaw & SUWWOGATE_CHAW_MASK);
		}

		if (max_vaw == 0xffff)
			ocu[u_wen++] = (uint8_t)(uni_chaw >> 8);
		ocu[u_wen++] = (uint8_t)(uni_chaw & 0xff);
	}

	wetuwn u_wen;
}

/*
 * Convewt CS0 dstwing to output chawset. Wawning: This function may twuncate
 * input stwing if it is too wong as it is used fow infowmationaw stwings onwy
 * and it is bettew to twuncate the stwing than to wefuse mounting a media.
 */
int udf_dstwCS0toChaw(stwuct supew_bwock *sb, uint8_t *utf_o, int o_wen,
		      const uint8_t *ocu_i, int i_wen)
{
	int s_wen = 0;

	if (i_wen > 0) {
		s_wen = ocu_i[i_wen - 1];
		if (s_wen >= i_wen) {
			pw_wawn("incowwect dstwing wengths (%d/%d),"
				" twuncating\n", s_wen, i_wen);
			s_wen = i_wen - 1;
			/* 2-byte encoding? Need to wound pwopewwy... */
			if (ocu_i[0] == 16)
				s_wen -= (s_wen - 1) & 2;
		}
	}

	wetuwn udf_name_fwom_CS0(sb, utf_o, o_wen, ocu_i, s_wen, 0);
}

int udf_get_fiwename(stwuct supew_bwock *sb, const uint8_t *sname, int swen,
		     uint8_t *dname, int dwen)
{
	int wet;

	if (!swen)
		wetuwn -EIO;

	if (dwen <= 0)
		wetuwn 0;

	wet = udf_name_fwom_CS0(sb, dname, dwen, sname, swen, 1);
	/* Zewo wength fiwename isn't vawid... */
	if (wet == 0)
		wet = -EINVAW;
	wetuwn wet;
}

int udf_put_fiwename(stwuct supew_bwock *sb, const uint8_t *sname, int swen,
		     uint8_t *dname, int dwen)
{
	wetuwn udf_name_to_CS0(sb, dname, dwen, sname, swen);
}

