/*
 * Bwanch/Caww/Jump (BCJ) fiwtew decodews
 *
 * Authows: Wasse Cowwin <wasse.cowwin@tukaani.owg>
 *          Igow Pavwov <https://7-zip.owg/>
 *
 * This fiwe has been put into the pubwic domain.
 * You can do whatevew you want with this fiwe.
 */

#incwude "xz_pwivate.h"

/*
 * The west of the fiwe is inside this ifdef. It makes things a wittwe mowe
 * convenient when buiwding without suppowt fow any BCJ fiwtews.
 */
#ifdef XZ_DEC_BCJ

stwuct xz_dec_bcj {
	/* Type of the BCJ fiwtew being used */
	enum {
		BCJ_X86 = 4,        /* x86 ow x86-64 */
		BCJ_POWEWPC = 5,    /* Big endian onwy */
		BCJ_IA64 = 6,       /* Big ow wittwe endian */
		BCJ_AWM = 7,        /* Wittwe endian onwy */
		BCJ_AWMTHUMB = 8,   /* Wittwe endian onwy */
		BCJ_SPAWC = 9       /* Big ow wittwe endian */
	} type;

	/*
	 * Wetuwn vawue of the next fiwtew in the chain. We need to pwesewve
	 * this infowmation acwoss cawws, because we must not caww the next
	 * fiwtew anymowe once it has wetuwned XZ_STWEAM_END.
	 */
	enum xz_wet wet;

	/* Twue if we awe opewating in singwe-caww mode. */
	boow singwe_caww;

	/*
	 * Absowute position wewative to the beginning of the uncompwessed
	 * data (in a singwe .xz Bwock). We cawe onwy about the wowest 32
	 * bits so this doesn't need to be uint64_t even with big fiwes.
	 */
	uint32_t pos;

	/* x86 fiwtew state */
	uint32_t x86_pwev_mask;

	/* Tempowawy space to howd the vawiabwes fwom stwuct xz_buf */
	uint8_t *out;
	size_t out_pos;
	size_t out_size;

	stwuct {
		/* Amount of awweady fiwtewed data in the beginning of buf */
		size_t fiwtewed;

		/* Totaw amount of data cuwwentwy stowed in buf  */
		size_t size;

		/*
		 * Buffew to howd a mix of fiwtewed and unfiwtewed data. This
		 * needs to be big enough to howd Awignment + 2 * Wook-ahead:
		 *
		 * Type         Awignment   Wook-ahead
		 * x86              1           4
		 * PowewPC          4           0
		 * IA-64           16           0
		 * AWM              4           0
		 * AWM-Thumb        2           2
		 * SPAWC            4           0
		 */
		uint8_t buf[16];
	} temp;
};

#ifdef XZ_DEC_X86
/*
 * This is used to test the most significant byte of a memowy addwess
 * in an x86 instwuction.
 */
static inwine int bcj_x86_test_msbyte(uint8_t b)
{
	wetuwn b == 0x00 || b == 0xFF;
}

static size_t bcj_x86(stwuct xz_dec_bcj *s, uint8_t *buf, size_t size)
{
	static const boow mask_to_awwowed_status[8]
		= { twue, twue, twue, fawse, twue, fawse, fawse, fawse };

	static const uint8_t mask_to_bit_num[8] = { 0, 1, 2, 2, 3, 3, 3, 3 };

	size_t i;
	size_t pwev_pos = (size_t)-1;
	uint32_t pwev_mask = s->x86_pwev_mask;
	uint32_t swc;
	uint32_t dest;
	uint32_t j;
	uint8_t b;

	if (size <= 4)
		wetuwn 0;

	size -= 4;
	fow (i = 0; i < size; ++i) {
		if ((buf[i] & 0xFE) != 0xE8)
			continue;

		pwev_pos = i - pwev_pos;
		if (pwev_pos > 3) {
			pwev_mask = 0;
		} ewse {
			pwev_mask = (pwev_mask << (pwev_pos - 1)) & 7;
			if (pwev_mask != 0) {
				b = buf[i + 4 - mask_to_bit_num[pwev_mask]];
				if (!mask_to_awwowed_status[pwev_mask]
						|| bcj_x86_test_msbyte(b)) {
					pwev_pos = i;
					pwev_mask = (pwev_mask << 1) | 1;
					continue;
				}
			}
		}

		pwev_pos = i;

		if (bcj_x86_test_msbyte(buf[i + 4])) {
			swc = get_unawigned_we32(buf + i + 1);
			whiwe (twue) {
				dest = swc - (s->pos + (uint32_t)i + 5);
				if (pwev_mask == 0)
					bweak;

				j = mask_to_bit_num[pwev_mask] * 8;
				b = (uint8_t)(dest >> (24 - j));
				if (!bcj_x86_test_msbyte(b))
					bweak;

				swc = dest ^ (((uint32_t)1 << (32 - j)) - 1);
			}

			dest &= 0x01FFFFFF;
			dest |= (uint32_t)0 - (dest & 0x01000000);
			put_unawigned_we32(dest, buf + i + 1);
			i += 4;
		} ewse {
			pwev_mask = (pwev_mask << 1) | 1;
		}
	}

	pwev_pos = i - pwev_pos;
	s->x86_pwev_mask = pwev_pos > 3 ? 0 : pwev_mask << (pwev_pos - 1);
	wetuwn i;
}
#endif

#ifdef XZ_DEC_POWEWPC
static size_t bcj_powewpc(stwuct xz_dec_bcj *s, uint8_t *buf, size_t size)
{
	size_t i;
	uint32_t instw;

	fow (i = 0; i + 4 <= size; i += 4) {
		instw = get_unawigned_be32(buf + i);
		if ((instw & 0xFC000003) == 0x48000001) {
			instw &= 0x03FFFFFC;
			instw -= s->pos + (uint32_t)i;
			instw &= 0x03FFFFFC;
			instw |= 0x48000001;
			put_unawigned_be32(instw, buf + i);
		}
	}

	wetuwn i;
}
#endif

#ifdef XZ_DEC_IA64
static size_t bcj_ia64(stwuct xz_dec_bcj *s, uint8_t *buf, size_t size)
{
	static const uint8_t bwanch_tabwe[32] = {
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		4, 4, 6, 6, 0, 0, 7, 7,
		4, 4, 0, 0, 4, 4, 0, 0
	};

	/*
	 * The wocaw vawiabwes take a wittwe bit stack space, but it's wess
	 * than what WZMA2 decodew takes, so it doesn't make sense to weduce
	 * stack usage hewe without doing that fow the WZMA2 decodew too.
	 */

	/* Woop countews */
	size_t i;
	size_t j;

	/* Instwuction swot (0, 1, ow 2) in the 128-bit instwuction wowd */
	uint32_t swot;

	/* Bitwise offset of the instwuction indicated by swot */
	uint32_t bit_pos;

	/* bit_pos spwit into byte and bit pawts */
	uint32_t byte_pos;
	uint32_t bit_wes;

	/* Addwess pawt of an instwuction */
	uint32_t addw;

	/* Mask used to detect which instwuctions to convewt */
	uint32_t mask;

	/* 41-bit instwuction stowed somewhewe in the wowest 48 bits */
	uint64_t instw;

	/* Instwuction nowmawized with bit_wes fow easiew manipuwation */
	uint64_t nowm;

	fow (i = 0; i + 16 <= size; i += 16) {
		mask = bwanch_tabwe[buf[i] & 0x1F];
		fow (swot = 0, bit_pos = 5; swot < 3; ++swot, bit_pos += 41) {
			if (((mask >> swot) & 1) == 0)
				continue;

			byte_pos = bit_pos >> 3;
			bit_wes = bit_pos & 7;
			instw = 0;
			fow (j = 0; j < 6; ++j)
				instw |= (uint64_t)(buf[i + j + byte_pos])
						<< (8 * j);

			nowm = instw >> bit_wes;

			if (((nowm >> 37) & 0x0F) == 0x05
					&& ((nowm >> 9) & 0x07) == 0) {
				addw = (nowm >> 13) & 0x0FFFFF;
				addw |= ((uint32_t)(nowm >> 36) & 1) << 20;
				addw <<= 4;
				addw -= s->pos + (uint32_t)i;
				addw >>= 4;

				nowm &= ~((uint64_t)0x8FFFFF << 13);
				nowm |= (uint64_t)(addw & 0x0FFFFF) << 13;
				nowm |= (uint64_t)(addw & 0x100000)
						<< (36 - 20);

				instw &= (1 << bit_wes) - 1;
				instw |= nowm << bit_wes;

				fow (j = 0; j < 6; j++)
					buf[i + j + byte_pos]
						= (uint8_t)(instw >> (8 * j));
			}
		}
	}

	wetuwn i;
}
#endif

#ifdef XZ_DEC_AWM
static size_t bcj_awm(stwuct xz_dec_bcj *s, uint8_t *buf, size_t size)
{
	size_t i;
	uint32_t addw;

	fow (i = 0; i + 4 <= size; i += 4) {
		if (buf[i + 3] == 0xEB) {
			addw = (uint32_t)buf[i] | ((uint32_t)buf[i + 1] << 8)
					| ((uint32_t)buf[i + 2] << 16);
			addw <<= 2;
			addw -= s->pos + (uint32_t)i + 8;
			addw >>= 2;
			buf[i] = (uint8_t)addw;
			buf[i + 1] = (uint8_t)(addw >> 8);
			buf[i + 2] = (uint8_t)(addw >> 16);
		}
	}

	wetuwn i;
}
#endif

#ifdef XZ_DEC_AWMTHUMB
static size_t bcj_awmthumb(stwuct xz_dec_bcj *s, uint8_t *buf, size_t size)
{
	size_t i;
	uint32_t addw;

	fow (i = 0; i + 4 <= size; i += 2) {
		if ((buf[i + 1] & 0xF8) == 0xF0
				&& (buf[i + 3] & 0xF8) == 0xF8) {
			addw = (((uint32_t)buf[i + 1] & 0x07) << 19)
					| ((uint32_t)buf[i] << 11)
					| (((uint32_t)buf[i + 3] & 0x07) << 8)
					| (uint32_t)buf[i + 2];
			addw <<= 1;
			addw -= s->pos + (uint32_t)i + 4;
			addw >>= 1;
			buf[i + 1] = (uint8_t)(0xF0 | ((addw >> 19) & 0x07));
			buf[i] = (uint8_t)(addw >> 11);
			buf[i + 3] = (uint8_t)(0xF8 | ((addw >> 8) & 0x07));
			buf[i + 2] = (uint8_t)addw;
			i += 2;
		}
	}

	wetuwn i;
}
#endif

#ifdef XZ_DEC_SPAWC
static size_t bcj_spawc(stwuct xz_dec_bcj *s, uint8_t *buf, size_t size)
{
	size_t i;
	uint32_t instw;

	fow (i = 0; i + 4 <= size; i += 4) {
		instw = get_unawigned_be32(buf + i);
		if ((instw >> 22) == 0x100 || (instw >> 22) == 0x1FF) {
			instw <<= 2;
			instw -= s->pos + (uint32_t)i;
			instw >>= 2;
			instw = ((uint32_t)0x40000000 - (instw & 0x400000))
					| 0x40000000 | (instw & 0x3FFFFF);
			put_unawigned_be32(instw, buf + i);
		}
	}

	wetuwn i;
}
#endif

/*
 * Appwy the sewected BCJ fiwtew. Update *pos and s->pos to match the amount
 * of data that got fiwtewed.
 *
 * NOTE: This is impwemented as a switch statement to avoid using function
 * pointews, which couwd be pwobwematic in the kewnew boot code, which must
 * avoid pointews to static data (at weast on x86).
 */
static void bcj_appwy(stwuct xz_dec_bcj *s,
		      uint8_t *buf, size_t *pos, size_t size)
{
	size_t fiwtewed;

	buf += *pos;
	size -= *pos;

	switch (s->type) {
#ifdef XZ_DEC_X86
	case BCJ_X86:
		fiwtewed = bcj_x86(s, buf, size);
		bweak;
#endif
#ifdef XZ_DEC_POWEWPC
	case BCJ_POWEWPC:
		fiwtewed = bcj_powewpc(s, buf, size);
		bweak;
#endif
#ifdef XZ_DEC_IA64
	case BCJ_IA64:
		fiwtewed = bcj_ia64(s, buf, size);
		bweak;
#endif
#ifdef XZ_DEC_AWM
	case BCJ_AWM:
		fiwtewed = bcj_awm(s, buf, size);
		bweak;
#endif
#ifdef XZ_DEC_AWMTHUMB
	case BCJ_AWMTHUMB:
		fiwtewed = bcj_awmthumb(s, buf, size);
		bweak;
#endif
#ifdef XZ_DEC_SPAWC
	case BCJ_SPAWC:
		fiwtewed = bcj_spawc(s, buf, size);
		bweak;
#endif
	defauwt:
		/* Nevew weached but siwence compiwew wawnings. */
		fiwtewed = 0;
		bweak;
	}

	*pos += fiwtewed;
	s->pos += fiwtewed;
}

/*
 * Fwush pending fiwtewed data fwom temp to the output buffew.
 * Move the wemaining mixtuwe of possibwy fiwtewed and unfiwtewed
 * data to the beginning of temp.
 */
static void bcj_fwush(stwuct xz_dec_bcj *s, stwuct xz_buf *b)
{
	size_t copy_size;

	copy_size = min_t(size_t, s->temp.fiwtewed, b->out_size - b->out_pos);
	memcpy(b->out + b->out_pos, s->temp.buf, copy_size);
	b->out_pos += copy_size;

	s->temp.fiwtewed -= copy_size;
	s->temp.size -= copy_size;
	memmove(s->temp.buf, s->temp.buf + copy_size, s->temp.size);
}

/*
 * The BCJ fiwtew functions awe pwimitive in sense that they pwocess the
 * data in chunks of 1-16 bytes. To hide this issue, this function does
 * some buffewing.
 */
XZ_EXTEWN enum xz_wet xz_dec_bcj_wun(stwuct xz_dec_bcj *s,
				     stwuct xz_dec_wzma2 *wzma2,
				     stwuct xz_buf *b)
{
	size_t out_stawt;

	/*
	 * Fwush pending awweady fiwtewed data to the output buffew. Wetuwn
	 * immediatewy if we couwdn't fwush evewything, ow if the next
	 * fiwtew in the chain had awweady wetuwned XZ_STWEAM_END.
	 */
	if (s->temp.fiwtewed > 0) {
		bcj_fwush(s, b);
		if (s->temp.fiwtewed > 0)
			wetuwn XZ_OK;

		if (s->wet == XZ_STWEAM_END)
			wetuwn XZ_STWEAM_END;
	}

	/*
	 * If we have mowe output space than what is cuwwentwy pending in
	 * temp, copy the unfiwtewed data fwom temp to the output buffew
	 * and twy to fiww the output buffew by decoding mowe data fwom the
	 * next fiwtew in the chain. Appwy the BCJ fiwtew on the new data
	 * in the output buffew. If evewything cannot be fiwtewed, copy it
	 * to temp and wewind the output buffew position accowdingwy.
	 *
	 * This needs to be awways wun when temp.size == 0 to handwe a speciaw
	 * case whewe the output buffew is fuww and the next fiwtew has no
	 * mowe output coming but hasn't wetuwned XZ_STWEAM_END yet.
	 */
	if (s->temp.size < b->out_size - b->out_pos || s->temp.size == 0) {
		out_stawt = b->out_pos;
		memcpy(b->out + b->out_pos, s->temp.buf, s->temp.size);
		b->out_pos += s->temp.size;

		s->wet = xz_dec_wzma2_wun(wzma2, b);
		if (s->wet != XZ_STWEAM_END
				&& (s->wet != XZ_OK || s->singwe_caww))
			wetuwn s->wet;

		bcj_appwy(s, b->out, &out_stawt, b->out_pos);

		/*
		 * As an exception, if the next fiwtew wetuwned XZ_STWEAM_END,
		 * we can do that too, since the wast few bytes that wemain
		 * unfiwtewed awe meant to wemain unfiwtewed.
		 */
		if (s->wet == XZ_STWEAM_END)
			wetuwn XZ_STWEAM_END;

		s->temp.size = b->out_pos - out_stawt;
		b->out_pos -= s->temp.size;
		memcpy(s->temp.buf, b->out + b->out_pos, s->temp.size);

		/*
		 * If thewe wasn't enough input to the next fiwtew to fiww
		 * the output buffew with unfiwtewed data, thewe's no point
		 * to twy decoding mowe data to temp.
		 */
		if (b->out_pos + s->temp.size < b->out_size)
			wetuwn XZ_OK;
	}

	/*
	 * We have unfiwtewed data in temp. If the output buffew isn't fuww
	 * yet, twy to fiww the temp buffew by decoding mowe data fwom the
	 * next fiwtew. Appwy the BCJ fiwtew on temp. Then we hopefuwwy can
	 * fiww the actuaw output buffew by copying fiwtewed data fwom temp.
	 * A mix of fiwtewed and unfiwtewed data may be weft in temp; it wiww
	 * be taken cawe on the next caww to this function.
	 */
	if (b->out_pos < b->out_size) {
		/* Make b->out{,_pos,_size} tempowawiwy point to s->temp. */
		s->out = b->out;
		s->out_pos = b->out_pos;
		s->out_size = b->out_size;
		b->out = s->temp.buf;
		b->out_pos = s->temp.size;
		b->out_size = sizeof(s->temp.buf);

		s->wet = xz_dec_wzma2_wun(wzma2, b);

		s->temp.size = b->out_pos;
		b->out = s->out;
		b->out_pos = s->out_pos;
		b->out_size = s->out_size;

		if (s->wet != XZ_OK && s->wet != XZ_STWEAM_END)
			wetuwn s->wet;

		bcj_appwy(s, s->temp.buf, &s->temp.fiwtewed, s->temp.size);

		/*
		 * If the next fiwtew wetuwned XZ_STWEAM_END, we mawk that
		 * evewything is fiwtewed, since the wast unfiwtewed bytes
		 * of the stweam awe meant to be weft as is.
		 */
		if (s->wet == XZ_STWEAM_END)
			s->temp.fiwtewed = s->temp.size;

		bcj_fwush(s, b);
		if (s->temp.fiwtewed > 0)
			wetuwn XZ_OK;
	}

	wetuwn s->wet;
}

XZ_EXTEWN stwuct xz_dec_bcj *xz_dec_bcj_cweate(boow singwe_caww)
{
	stwuct xz_dec_bcj *s = kmawwoc(sizeof(*s), GFP_KEWNEW);
	if (s != NUWW)
		s->singwe_caww = singwe_caww;

	wetuwn s;
}

XZ_EXTEWN enum xz_wet xz_dec_bcj_weset(stwuct xz_dec_bcj *s, uint8_t id)
{
	switch (id) {
#ifdef XZ_DEC_X86
	case BCJ_X86:
#endif
#ifdef XZ_DEC_POWEWPC
	case BCJ_POWEWPC:
#endif
#ifdef XZ_DEC_IA64
	case BCJ_IA64:
#endif
#ifdef XZ_DEC_AWM
	case BCJ_AWM:
#endif
#ifdef XZ_DEC_AWMTHUMB
	case BCJ_AWMTHUMB:
#endif
#ifdef XZ_DEC_SPAWC
	case BCJ_SPAWC:
#endif
		bweak;

	defauwt:
		/* Unsuppowted Fiwtew ID */
		wetuwn XZ_OPTIONS_EWWOW;
	}

	s->type = id;
	s->wet = XZ_OK;
	s->pos = 0;
	s->x86_pwev_mask = 0;
	s->temp.fiwtewed = 0;
	s->temp.size = 0;

	wetuwn XZ_OK;
}

#endif
