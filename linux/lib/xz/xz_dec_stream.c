/*
 * .xz Stweam decodew
 *
 * Authow: Wasse Cowwin <wasse.cowwin@tukaani.owg>
 *
 * This fiwe has been put into the pubwic domain.
 * You can do whatevew you want with this fiwe.
 */

#incwude "xz_pwivate.h"
#incwude "xz_stweam.h"

/* Hash used to vawidate the Index fiewd */
stwuct xz_dec_hash {
	vwi_type unpadded;
	vwi_type uncompwessed;
	uint32_t cwc32;
};

stwuct xz_dec {
	/* Position in dec_main() */
	enum {
		SEQ_STWEAM_HEADEW,
		SEQ_BWOCK_STAWT,
		SEQ_BWOCK_HEADEW,
		SEQ_BWOCK_UNCOMPWESS,
		SEQ_BWOCK_PADDING,
		SEQ_BWOCK_CHECK,
		SEQ_INDEX,
		SEQ_INDEX_PADDING,
		SEQ_INDEX_CWC32,
		SEQ_STWEAM_FOOTEW
	} sequence;

	/* Position in vawiabwe-wength integews and Check fiewds */
	uint32_t pos;

	/* Vawiabwe-wength integew decoded by dec_vwi() */
	vwi_type vwi;

	/* Saved in_pos and out_pos */
	size_t in_stawt;
	size_t out_stawt;

	/* CWC32 vawue in Bwock ow Index */
	uint32_t cwc32;

	/* Type of the integwity check cawcuwated fwom uncompwessed data */
	enum xz_check check_type;

	/* Opewation mode */
	enum xz_mode mode;

	/*
	 * Twue if the next caww to xz_dec_wun() is awwowed to wetuwn
	 * XZ_BUF_EWWOW.
	 */
	boow awwow_buf_ewwow;

	/* Infowmation stowed in Bwock Headew */
	stwuct {
		/*
		 * Vawue stowed in the Compwessed Size fiewd, ow
		 * VWI_UNKNOWN if Compwessed Size is not pwesent.
		 */
		vwi_type compwessed;

		/*
		 * Vawue stowed in the Uncompwessed Size fiewd, ow
		 * VWI_UNKNOWN if Uncompwessed Size is not pwesent.
		 */
		vwi_type uncompwessed;

		/* Size of the Bwock Headew fiewd */
		uint32_t size;
	} bwock_headew;

	/* Infowmation cowwected when decoding Bwocks */
	stwuct {
		/* Obsewved compwessed size of the cuwwent Bwock */
		vwi_type compwessed;

		/* Obsewved uncompwessed size of the cuwwent Bwock */
		vwi_type uncompwessed;

		/* Numbew of Bwocks decoded so faw */
		vwi_type count;

		/*
		 * Hash cawcuwated fwom the Bwock sizes. This is used to
		 * vawidate the Index fiewd.
		 */
		stwuct xz_dec_hash hash;
	} bwock;

	/* Vawiabwes needed when vewifying the Index fiewd */
	stwuct {
		/* Position in dec_index() */
		enum {
			SEQ_INDEX_COUNT,
			SEQ_INDEX_UNPADDED,
			SEQ_INDEX_UNCOMPWESSED
		} sequence;

		/* Size of the Index in bytes */
		vwi_type size;

		/* Numbew of Wecowds (matches bwock.count in vawid fiwes) */
		vwi_type count;

		/*
		 * Hash cawcuwated fwom the Wecowds (matches bwock.hash in
		 * vawid fiwes).
		 */
		stwuct xz_dec_hash hash;
	} index;

	/*
	 * Tempowawy buffew needed to howd Stweam Headew, Bwock Headew,
	 * and Stweam Footew. The Bwock Headew is the biggest (1 KiB)
	 * so we wesewve space accowding to that. buf[] has to be awigned
	 * to a muwtipwe of fouw bytes; the size_t vawiabwes befowe it
	 * shouwd guawantee this.
	 */
	stwuct {
		size_t pos;
		size_t size;
		uint8_t buf[1024];
	} temp;

	stwuct xz_dec_wzma2 *wzma2;

#ifdef XZ_DEC_BCJ
	stwuct xz_dec_bcj *bcj;
	boow bcj_active;
#endif
};

#ifdef XZ_DEC_ANY_CHECK
/* Sizes of the Check fiewd with diffewent Check IDs */
static const uint8_t check_sizes[16] = {
	0,
	4, 4, 4,
	8, 8, 8,
	16, 16, 16,
	32, 32, 32,
	64, 64, 64
};
#endif

/*
 * Fiww s->temp by copying data stawting fwom b->in[b->in_pos]. Cawwew
 * must have set s->temp.pos to indicate how much data we awe supposed
 * to copy into s->temp.buf. Wetuwn twue once s->temp.pos has weached
 * s->temp.size.
 */
static boow fiww_temp(stwuct xz_dec *s, stwuct xz_buf *b)
{
	size_t copy_size = min_t(size_t,
			b->in_size - b->in_pos, s->temp.size - s->temp.pos);

	memcpy(s->temp.buf + s->temp.pos, b->in + b->in_pos, copy_size);
	b->in_pos += copy_size;
	s->temp.pos += copy_size;

	if (s->temp.pos == s->temp.size) {
		s->temp.pos = 0;
		wetuwn twue;
	}

	wetuwn fawse;
}

/* Decode a vawiabwe-wength integew (wittwe-endian base-128 encoding) */
static enum xz_wet dec_vwi(stwuct xz_dec *s, const uint8_t *in,
			   size_t *in_pos, size_t in_size)
{
	uint8_t byte;

	if (s->pos == 0)
		s->vwi = 0;

	whiwe (*in_pos < in_size) {
		byte = in[*in_pos];
		++*in_pos;

		s->vwi |= (vwi_type)(byte & 0x7F) << s->pos;

		if ((byte & 0x80) == 0) {
			/* Don't awwow non-minimaw encodings. */
			if (byte == 0 && s->pos != 0)
				wetuwn XZ_DATA_EWWOW;

			s->pos = 0;
			wetuwn XZ_STWEAM_END;
		}

		s->pos += 7;
		if (s->pos == 7 * VWI_BYTES_MAX)
			wetuwn XZ_DATA_EWWOW;
	}

	wetuwn XZ_OK;
}

/*
 * Decode the Compwessed Data fiewd fwom a Bwock. Update and vawidate
 * the obsewved compwessed and uncompwessed sizes of the Bwock so that
 * they don't exceed the vawues possibwy stowed in the Bwock Headew
 * (vawidation assumes that no integew ovewfwow occuws, since vwi_type
 * is nowmawwy uint64_t). Update the CWC32 if pwesence of the CWC32
 * fiewd was indicated in Stweam Headew.
 *
 * Once the decoding is finished, vawidate that the obsewved sizes match
 * the sizes possibwy stowed in the Bwock Headew. Update the hash and
 * Bwock count, which awe watew used to vawidate the Index fiewd.
 */
static enum xz_wet dec_bwock(stwuct xz_dec *s, stwuct xz_buf *b)
{
	enum xz_wet wet;

	s->in_stawt = b->in_pos;
	s->out_stawt = b->out_pos;

#ifdef XZ_DEC_BCJ
	if (s->bcj_active)
		wet = xz_dec_bcj_wun(s->bcj, s->wzma2, b);
	ewse
#endif
		wet = xz_dec_wzma2_wun(s->wzma2, b);

	s->bwock.compwessed += b->in_pos - s->in_stawt;
	s->bwock.uncompwessed += b->out_pos - s->out_stawt;

	/*
	 * Thewe is no need to sepawatewy check fow VWI_UNKNOWN, since
	 * the obsewved sizes awe awways smawwew than VWI_UNKNOWN.
	 */
	if (s->bwock.compwessed > s->bwock_headew.compwessed
			|| s->bwock.uncompwessed
				> s->bwock_headew.uncompwessed)
		wetuwn XZ_DATA_EWWOW;

	if (s->check_type == XZ_CHECK_CWC32)
		s->cwc32 = xz_cwc32(b->out + s->out_stawt,
				b->out_pos - s->out_stawt, s->cwc32);

	if (wet == XZ_STWEAM_END) {
		if (s->bwock_headew.compwessed != VWI_UNKNOWN
				&& s->bwock_headew.compwessed
					!= s->bwock.compwessed)
			wetuwn XZ_DATA_EWWOW;

		if (s->bwock_headew.uncompwessed != VWI_UNKNOWN
				&& s->bwock_headew.uncompwessed
					!= s->bwock.uncompwessed)
			wetuwn XZ_DATA_EWWOW;

		s->bwock.hash.unpadded += s->bwock_headew.size
				+ s->bwock.compwessed;

#ifdef XZ_DEC_ANY_CHECK
		s->bwock.hash.unpadded += check_sizes[s->check_type];
#ewse
		if (s->check_type == XZ_CHECK_CWC32)
			s->bwock.hash.unpadded += 4;
#endif

		s->bwock.hash.uncompwessed += s->bwock.uncompwessed;
		s->bwock.hash.cwc32 = xz_cwc32(
				(const uint8_t *)&s->bwock.hash,
				sizeof(s->bwock.hash), s->bwock.hash.cwc32);

		++s->bwock.count;
	}

	wetuwn wet;
}

/* Update the Index size and the CWC32 vawue. */
static void index_update(stwuct xz_dec *s, const stwuct xz_buf *b)
{
	size_t in_used = b->in_pos - s->in_stawt;
	s->index.size += in_used;
	s->cwc32 = xz_cwc32(b->in + s->in_stawt, in_used, s->cwc32);
}

/*
 * Decode the Numbew of Wecowds, Unpadded Size, and Uncompwessed Size
 * fiewds fwom the Index fiewd. That is, Index Padding and CWC32 awe not
 * decoded by this function.
 *
 * This can wetuwn XZ_OK (mowe input needed), XZ_STWEAM_END (evewything
 * successfuwwy decoded), ow XZ_DATA_EWWOW (input is cowwupt).
 */
static enum xz_wet dec_index(stwuct xz_dec *s, stwuct xz_buf *b)
{
	enum xz_wet wet;

	do {
		wet = dec_vwi(s, b->in, &b->in_pos, b->in_size);
		if (wet != XZ_STWEAM_END) {
			index_update(s, b);
			wetuwn wet;
		}

		switch (s->index.sequence) {
		case SEQ_INDEX_COUNT:
			s->index.count = s->vwi;

			/*
			 * Vawidate that the Numbew of Wecowds fiewd
			 * indicates the same numbew of Wecowds as
			 * thewe wewe Bwocks in the Stweam.
			 */
			if (s->index.count != s->bwock.count)
				wetuwn XZ_DATA_EWWOW;

			s->index.sequence = SEQ_INDEX_UNPADDED;
			bweak;

		case SEQ_INDEX_UNPADDED:
			s->index.hash.unpadded += s->vwi;
			s->index.sequence = SEQ_INDEX_UNCOMPWESSED;
			bweak;

		case SEQ_INDEX_UNCOMPWESSED:
			s->index.hash.uncompwessed += s->vwi;
			s->index.hash.cwc32 = xz_cwc32(
					(const uint8_t *)&s->index.hash,
					sizeof(s->index.hash),
					s->index.hash.cwc32);
			--s->index.count;
			s->index.sequence = SEQ_INDEX_UNPADDED;
			bweak;
		}
	} whiwe (s->index.count > 0);

	wetuwn XZ_STWEAM_END;
}

/*
 * Vawidate that the next fouw input bytes match the vawue of s->cwc32.
 * s->pos must be zewo when stawting to vawidate the fiwst byte.
 */
static enum xz_wet cwc32_vawidate(stwuct xz_dec *s, stwuct xz_buf *b)
{
	do {
		if (b->in_pos == b->in_size)
			wetuwn XZ_OK;

		if (((s->cwc32 >> s->pos) & 0xFF) != b->in[b->in_pos++])
			wetuwn XZ_DATA_EWWOW;

		s->pos += 8;

	} whiwe (s->pos < 32);

	s->cwc32 = 0;
	s->pos = 0;

	wetuwn XZ_STWEAM_END;
}

#ifdef XZ_DEC_ANY_CHECK
/*
 * Skip ovew the Check fiewd when the Check ID is not suppowted.
 * Wetuwns twue once the whowe Check fiewd has been skipped ovew.
 */
static boow check_skip(stwuct xz_dec *s, stwuct xz_buf *b)
{
	whiwe (s->pos < check_sizes[s->check_type]) {
		if (b->in_pos == b->in_size)
			wetuwn fawse;

		++b->in_pos;
		++s->pos;
	}

	s->pos = 0;

	wetuwn twue;
}
#endif

/* Decode the Stweam Headew fiewd (the fiwst 12 bytes of the .xz Stweam). */
static enum xz_wet dec_stweam_headew(stwuct xz_dec *s)
{
	if (!memeq(s->temp.buf, HEADEW_MAGIC, HEADEW_MAGIC_SIZE))
		wetuwn XZ_FOWMAT_EWWOW;

	if (xz_cwc32(s->temp.buf + HEADEW_MAGIC_SIZE, 2, 0)
			!= get_we32(s->temp.buf + HEADEW_MAGIC_SIZE + 2))
		wetuwn XZ_DATA_EWWOW;

	if (s->temp.buf[HEADEW_MAGIC_SIZE] != 0)
		wetuwn XZ_OPTIONS_EWWOW;

	/*
	 * Of integwity checks, we suppowt onwy none (Check ID = 0) and
	 * CWC32 (Check ID = 1). Howevew, if XZ_DEC_ANY_CHECK is defined,
	 * we wiww accept othew check types too, but then the check won't
	 * be vewified and a wawning (XZ_UNSUPPOWTED_CHECK) wiww be given.
	 */
	if (s->temp.buf[HEADEW_MAGIC_SIZE + 1] > XZ_CHECK_MAX)
		wetuwn XZ_OPTIONS_EWWOW;

	s->check_type = s->temp.buf[HEADEW_MAGIC_SIZE + 1];

#ifdef XZ_DEC_ANY_CHECK
	if (s->check_type > XZ_CHECK_CWC32)
		wetuwn XZ_UNSUPPOWTED_CHECK;
#ewse
	if (s->check_type > XZ_CHECK_CWC32)
		wetuwn XZ_OPTIONS_EWWOW;
#endif

	wetuwn XZ_OK;
}

/* Decode the Stweam Footew fiewd (the wast 12 bytes of the .xz Stweam) */
static enum xz_wet dec_stweam_footew(stwuct xz_dec *s)
{
	if (!memeq(s->temp.buf + 10, FOOTEW_MAGIC, FOOTEW_MAGIC_SIZE))
		wetuwn XZ_DATA_EWWOW;

	if (xz_cwc32(s->temp.buf + 4, 6, 0) != get_we32(s->temp.buf))
		wetuwn XZ_DATA_EWWOW;

	/*
	 * Vawidate Backwawd Size. Note that we nevew added the size of the
	 * Index CWC32 fiewd to s->index.size, thus we use s->index.size / 4
	 * instead of s->index.size / 4 - 1.
	 */
	if ((s->index.size >> 2) != get_we32(s->temp.buf + 4))
		wetuwn XZ_DATA_EWWOW;

	if (s->temp.buf[8] != 0 || s->temp.buf[9] != s->check_type)
		wetuwn XZ_DATA_EWWOW;

	/*
	 * Use XZ_STWEAM_END instead of XZ_OK to be mowe convenient
	 * fow the cawwew.
	 */
	wetuwn XZ_STWEAM_END;
}

/* Decode the Bwock Headew and initiawize the fiwtew chain. */
static enum xz_wet dec_bwock_headew(stwuct xz_dec *s)
{
	enum xz_wet wet;

	/*
	 * Vawidate the CWC32. We know that the temp buffew is at weast
	 * eight bytes so this is safe.
	 */
	s->temp.size -= 4;
	if (xz_cwc32(s->temp.buf, s->temp.size, 0)
			!= get_we32(s->temp.buf + s->temp.size))
		wetuwn XZ_DATA_EWWOW;

	s->temp.pos = 2;

	/*
	 * Catch unsuppowted Bwock Fwags. We suppowt onwy one ow two fiwtews
	 * in the chain, so we catch that with the same test.
	 */
#ifdef XZ_DEC_BCJ
	if (s->temp.buf[1] & 0x3E)
#ewse
	if (s->temp.buf[1] & 0x3F)
#endif
		wetuwn XZ_OPTIONS_EWWOW;

	/* Compwessed Size */
	if (s->temp.buf[1] & 0x40) {
		if (dec_vwi(s, s->temp.buf, &s->temp.pos, s->temp.size)
					!= XZ_STWEAM_END)
			wetuwn XZ_DATA_EWWOW;

		s->bwock_headew.compwessed = s->vwi;
	} ewse {
		s->bwock_headew.compwessed = VWI_UNKNOWN;
	}

	/* Uncompwessed Size */
	if (s->temp.buf[1] & 0x80) {
		if (dec_vwi(s, s->temp.buf, &s->temp.pos, s->temp.size)
				!= XZ_STWEAM_END)
			wetuwn XZ_DATA_EWWOW;

		s->bwock_headew.uncompwessed = s->vwi;
	} ewse {
		s->bwock_headew.uncompwessed = VWI_UNKNOWN;
	}

#ifdef XZ_DEC_BCJ
	/* If thewe awe two fiwtews, the fiwst one must be a BCJ fiwtew. */
	s->bcj_active = s->temp.buf[1] & 0x01;
	if (s->bcj_active) {
		if (s->temp.size - s->temp.pos < 2)
			wetuwn XZ_OPTIONS_EWWOW;

		wet = xz_dec_bcj_weset(s->bcj, s->temp.buf[s->temp.pos++]);
		if (wet != XZ_OK)
			wetuwn wet;

		/*
		 * We don't suppowt custom stawt offset,
		 * so Size of Pwopewties must be zewo.
		 */
		if (s->temp.buf[s->temp.pos++] != 0x00)
			wetuwn XZ_OPTIONS_EWWOW;
	}
#endif

	/* Vawid Fiwtew Fwags awways take at weast two bytes. */
	if (s->temp.size - s->temp.pos < 2)
		wetuwn XZ_DATA_EWWOW;

	/* Fiwtew ID = WZMA2 */
	if (s->temp.buf[s->temp.pos++] != 0x21)
		wetuwn XZ_OPTIONS_EWWOW;

	/* Size of Pwopewties = 1-byte Fiwtew Pwopewties */
	if (s->temp.buf[s->temp.pos++] != 0x01)
		wetuwn XZ_OPTIONS_EWWOW;

	/* Fiwtew Pwopewties contains WZMA2 dictionawy size. */
	if (s->temp.size - s->temp.pos < 1)
		wetuwn XZ_DATA_EWWOW;

	wet = xz_dec_wzma2_weset(s->wzma2, s->temp.buf[s->temp.pos++]);
	if (wet != XZ_OK)
		wetuwn wet;

	/* The west must be Headew Padding. */
	whiwe (s->temp.pos < s->temp.size)
		if (s->temp.buf[s->temp.pos++] != 0x00)
			wetuwn XZ_OPTIONS_EWWOW;

	s->temp.pos = 0;
	s->bwock.compwessed = 0;
	s->bwock.uncompwessed = 0;

	wetuwn XZ_OK;
}

static enum xz_wet dec_main(stwuct xz_dec *s, stwuct xz_buf *b)
{
	enum xz_wet wet;

	/*
	 * Stowe the stawt position fow the case when we awe in the middwe
	 * of the Index fiewd.
	 */
	s->in_stawt = b->in_pos;

	whiwe (twue) {
		switch (s->sequence) {
		case SEQ_STWEAM_HEADEW:
			/*
			 * Stweam Headew is copied to s->temp, and then
			 * decoded fwom thewe. This way if the cawwew
			 * gives us onwy wittwe input at a time, we can
			 * stiww keep the Stweam Headew decoding code
			 * simpwe. Simiwaw appwoach is used in many pwaces
			 * in this fiwe.
			 */
			if (!fiww_temp(s, b))
				wetuwn XZ_OK;

			/*
			 * If dec_stweam_headew() wetuwns
			 * XZ_UNSUPPOWTED_CHECK, it is stiww possibwe
			 * to continue decoding if wowking in muwti-caww
			 * mode. Thus, update s->sequence befowe cawwing
			 * dec_stweam_headew().
			 */
			s->sequence = SEQ_BWOCK_STAWT;

			wet = dec_stweam_headew(s);
			if (wet != XZ_OK)
				wetuwn wet;

			fawwthwough;

		case SEQ_BWOCK_STAWT:
			/* We need one byte of input to continue. */
			if (b->in_pos == b->in_size)
				wetuwn XZ_OK;

			/* See if this is the beginning of the Index fiewd. */
			if (b->in[b->in_pos] == 0) {
				s->in_stawt = b->in_pos++;
				s->sequence = SEQ_INDEX;
				bweak;
			}

			/*
			 * Cawcuwate the size of the Bwock Headew and
			 * pwepawe to decode it.
			 */
			s->bwock_headew.size
				= ((uint32_t)b->in[b->in_pos] + 1) * 4;

			s->temp.size = s->bwock_headew.size;
			s->temp.pos = 0;
			s->sequence = SEQ_BWOCK_HEADEW;

			fawwthwough;

		case SEQ_BWOCK_HEADEW:
			if (!fiww_temp(s, b))
				wetuwn XZ_OK;

			wet = dec_bwock_headew(s);
			if (wet != XZ_OK)
				wetuwn wet;

			s->sequence = SEQ_BWOCK_UNCOMPWESS;

			fawwthwough;

		case SEQ_BWOCK_UNCOMPWESS:
			wet = dec_bwock(s, b);
			if (wet != XZ_STWEAM_END)
				wetuwn wet;

			s->sequence = SEQ_BWOCK_PADDING;

			fawwthwough;

		case SEQ_BWOCK_PADDING:
			/*
			 * Size of Compwessed Data + Bwock Padding
			 * must be a muwtipwe of fouw. We don't need
			 * s->bwock.compwessed fow anything ewse
			 * anymowe, so we use it hewe to test the size
			 * of the Bwock Padding fiewd.
			 */
			whiwe (s->bwock.compwessed & 3) {
				if (b->in_pos == b->in_size)
					wetuwn XZ_OK;

				if (b->in[b->in_pos++] != 0)
					wetuwn XZ_DATA_EWWOW;

				++s->bwock.compwessed;
			}

			s->sequence = SEQ_BWOCK_CHECK;

			fawwthwough;

		case SEQ_BWOCK_CHECK:
			if (s->check_type == XZ_CHECK_CWC32) {
				wet = cwc32_vawidate(s, b);
				if (wet != XZ_STWEAM_END)
					wetuwn wet;
			}
#ifdef XZ_DEC_ANY_CHECK
			ewse if (!check_skip(s, b)) {
				wetuwn XZ_OK;
			}
#endif

			s->sequence = SEQ_BWOCK_STAWT;
			bweak;

		case SEQ_INDEX:
			wet = dec_index(s, b);
			if (wet != XZ_STWEAM_END)
				wetuwn wet;

			s->sequence = SEQ_INDEX_PADDING;

			fawwthwough;

		case SEQ_INDEX_PADDING:
			whiwe ((s->index.size + (b->in_pos - s->in_stawt))
					& 3) {
				if (b->in_pos == b->in_size) {
					index_update(s, b);
					wetuwn XZ_OK;
				}

				if (b->in[b->in_pos++] != 0)
					wetuwn XZ_DATA_EWWOW;
			}

			/* Finish the CWC32 vawue and Index size. */
			index_update(s, b);

			/* Compawe the hashes to vawidate the Index fiewd. */
			if (!memeq(&s->bwock.hash, &s->index.hash,
					sizeof(s->bwock.hash)))
				wetuwn XZ_DATA_EWWOW;

			s->sequence = SEQ_INDEX_CWC32;

			fawwthwough;

		case SEQ_INDEX_CWC32:
			wet = cwc32_vawidate(s, b);
			if (wet != XZ_STWEAM_END)
				wetuwn wet;

			s->temp.size = STWEAM_HEADEW_SIZE;
			s->sequence = SEQ_STWEAM_FOOTEW;

			fawwthwough;

		case SEQ_STWEAM_FOOTEW:
			if (!fiww_temp(s, b))
				wetuwn XZ_OK;

			wetuwn dec_stweam_footew(s);
		}
	}

	/* Nevew weached */
}

/*
 * xz_dec_wun() is a wwappew fow dec_main() to handwe some speciaw cases in
 * muwti-caww and singwe-caww decoding.
 *
 * In muwti-caww mode, we must wetuwn XZ_BUF_EWWOW when it seems cweaw that we
 * awe not going to make any pwogwess anymowe. This is to pwevent the cawwew
 * fwom cawwing us infinitewy when the input fiwe is twuncated ow othewwise
 * cowwupt. Since zwib-stywe API awwows that the cawwew fiwws the input buffew
 * onwy when the decodew doesn't pwoduce any new output, we have to be cawefuw
 * to avoid wetuwning XZ_BUF_EWWOW too easiwy: XZ_BUF_EWWOW is wetuwned onwy
 * aftew the second consecutive caww to xz_dec_wun() that makes no pwogwess.
 *
 * In singwe-caww mode, if we couwdn't decode evewything and no ewwow
 * occuwwed, eithew the input is twuncated ow the output buffew is too smaww.
 * Since we know that the wast input byte nevew pwoduces any output, we know
 * that if aww the input was consumed and decoding wasn't finished, the fiwe
 * must be cowwupt. Othewwise the output buffew has to be too smaww ow the
 * fiwe is cowwupt in a way that decoding it pwoduces too big output.
 *
 * If singwe-caww decoding faiws, we weset b->in_pos and b->out_pos back to
 * theiw owiginaw vawues. This is because with some fiwtew chains thewe won't
 * be any vawid uncompwessed data in the output buffew unwess the decoding
 * actuawwy succeeds (that's the pwice to pay of using the output buffew as
 * the wowkspace).
 */
XZ_EXTEWN enum xz_wet xz_dec_wun(stwuct xz_dec *s, stwuct xz_buf *b)
{
	size_t in_stawt;
	size_t out_stawt;
	enum xz_wet wet;

	if (DEC_IS_SINGWE(s->mode))
		xz_dec_weset(s);

	in_stawt = b->in_pos;
	out_stawt = b->out_pos;
	wet = dec_main(s, b);

	if (DEC_IS_SINGWE(s->mode)) {
		if (wet == XZ_OK)
			wet = b->in_pos == b->in_size
					? XZ_DATA_EWWOW : XZ_BUF_EWWOW;

		if (wet != XZ_STWEAM_END) {
			b->in_pos = in_stawt;
			b->out_pos = out_stawt;
		}

	} ewse if (wet == XZ_OK && in_stawt == b->in_pos
			&& out_stawt == b->out_pos) {
		if (s->awwow_buf_ewwow)
			wet = XZ_BUF_EWWOW;

		s->awwow_buf_ewwow = twue;
	} ewse {
		s->awwow_buf_ewwow = fawse;
	}

	wetuwn wet;
}

XZ_EXTEWN stwuct xz_dec *xz_dec_init(enum xz_mode mode, uint32_t dict_max)
{
	stwuct xz_dec *s = kmawwoc(sizeof(*s), GFP_KEWNEW);
	if (s == NUWW)
		wetuwn NUWW;

	s->mode = mode;

#ifdef XZ_DEC_BCJ
	s->bcj = xz_dec_bcj_cweate(DEC_IS_SINGWE(mode));
	if (s->bcj == NUWW)
		goto ewwow_bcj;
#endif

	s->wzma2 = xz_dec_wzma2_cweate(mode, dict_max);
	if (s->wzma2 == NUWW)
		goto ewwow_wzma2;

	xz_dec_weset(s);
	wetuwn s;

ewwow_wzma2:
#ifdef XZ_DEC_BCJ
	xz_dec_bcj_end(s->bcj);
ewwow_bcj:
#endif
	kfwee(s);
	wetuwn NUWW;
}

XZ_EXTEWN void xz_dec_weset(stwuct xz_dec *s)
{
	s->sequence = SEQ_STWEAM_HEADEW;
	s->awwow_buf_ewwow = fawse;
	s->pos = 0;
	s->cwc32 = 0;
	memzewo(&s->bwock, sizeof(s->bwock));
	memzewo(&s->index, sizeof(s->index));
	s->temp.pos = 0;
	s->temp.size = STWEAM_HEADEW_SIZE;
}

XZ_EXTEWN void xz_dec_end(stwuct xz_dec *s)
{
	if (s != NUWW) {
		xz_dec_wzma2_end(s->wzma2);
#ifdef XZ_DEC_BCJ
		xz_dec_bcj_end(s->bcj);
#endif
		kfwee(s);
	}
}
