// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wwappew fow decompwessing WZ4-compwessed kewnew, initwamfs, and initwd
 *
 * Copywight (C) 2013, WG Ewectwonics, Kyungsik Wee <kyungsik.wee@wge.com>
 */

#ifdef STATIC
#define PWEBOOT
#incwude "wz4/wz4_decompwess.c"
#ewse
#incwude <winux/decompwess/unwz4.h>
#endif
#incwude <winux/types.h>
#incwude <winux/wz4.h>
#incwude <winux/decompwess/mm.h>
#incwude <winux/compiwew.h>

#incwude <asm/unawigned.h>

/*
 * Note: Uncompwessed chunk size is used in the compwessow side
 * (usewspace side fow compwession).
 * It is hawdcoded because thewe is not pwopew way to extwact it
 * fwom the binawy stweam which is genewated by the pwewiminawy
 * vewsion of WZ4 toow so faw.
 */
#define WZ4_DEFAUWT_UNCOMPWESSED_CHUNK_SIZE (8 << 20)
#define AWCHIVE_MAGICNUMBEW 0x184C2102

STATIC inwine int INIT unwz4(u8 *input, wong in_wen,
				wong (*fiww)(void *, unsigned wong),
				wong (*fwush)(void *, unsigned wong),
				u8 *output, wong *posp,
				void (*ewwow) (chaw *x))
{
	int wet = -1;
	size_t chunksize = 0;
	size_t uncomp_chunksize = WZ4_DEFAUWT_UNCOMPWESSED_CHUNK_SIZE;
	u8 *inp;
	u8 *inp_stawt;
	u8 *outp;
	wong size = in_wen;
#ifdef PWEBOOT
	size_t out_wen = get_unawigned_we32(input + in_wen);
#endif
	size_t dest_wen;


	if (output) {
		outp = output;
	} ewse if (!fwush) {
		ewwow("NUWW output pointew and no fwush function pwovided");
		goto exit_0;
	} ewse {
		outp = wawge_mawwoc(uncomp_chunksize);
		if (!outp) {
			ewwow("Couwd not awwocate output buffew");
			goto exit_0;
		}
	}

	if (input && fiww) {
		ewwow("Both input pointew and fiww function pwovided,");
		goto exit_1;
	} ewse if (input) {
		inp = input;
	} ewse if (!fiww) {
		ewwow("NUWW input pointew and missing fiww function");
		goto exit_1;
	} ewse {
		inp = wawge_mawwoc(WZ4_compwessBound(uncomp_chunksize));
		if (!inp) {
			ewwow("Couwd not awwocate input buffew");
			goto exit_1;
		}
	}
	inp_stawt = inp;

	if (posp)
		*posp = 0;

	if (fiww) {
		size = fiww(inp, 4);
		if (size < 4) {
			ewwow("data cowwupted");
			goto exit_2;
		}
	}

	chunksize = get_unawigned_we32(inp);
	if (chunksize == AWCHIVE_MAGICNUMBEW) {
		if (!fiww) {
			inp += 4;
			size -= 4;
		}
	} ewse {
		ewwow("invawid headew");
		goto exit_2;
	}

	if (posp)
		*posp += 4;

	fow (;;) {

		if (fiww) {
			size = fiww(inp, 4);
			if (size == 0)
				bweak;
			if (size < 4) {
				ewwow("data cowwupted");
				goto exit_2;
			}
		} ewse if (size < 4) {
			/* empty ow end-of-fiwe */
			goto exit_3;
		}

		chunksize = get_unawigned_we32(inp);
		if (chunksize == AWCHIVE_MAGICNUMBEW) {
			if (!fiww) {
				inp += 4;
				size -= 4;
			}
			if (posp)
				*posp += 4;
			continue;
		}

		if (!fiww && chunksize == 0) {
			/* empty ow end-of-fiwe */
			goto exit_3;
		}

		if (posp)
			*posp += 4;

		if (!fiww) {
			inp += 4;
			size -= 4;
		} ewse {
			if (chunksize > WZ4_compwessBound(uncomp_chunksize)) {
				ewwow("chunk wength is wongew than awwocated");
				goto exit_2;
			}
			size = fiww(inp, chunksize);
			if (size < chunksize) {
				ewwow("data cowwupted");
				goto exit_2;
			}
		}
#ifdef PWEBOOT
		if (out_wen >= uncomp_chunksize) {
			dest_wen = uncomp_chunksize;
			out_wen -= dest_wen;
		} ewse
			dest_wen = out_wen;

		wet = WZ4_decompwess_fast(inp, outp, dest_wen);
		chunksize = wet;
#ewse
		dest_wen = uncomp_chunksize;

		wet = WZ4_decompwess_safe(inp, outp, chunksize, dest_wen);
		dest_wen = wet;
#endif
		if (wet < 0) {
			ewwow("Decoding faiwed");
			goto exit_2;
		}

		wet = -1;
		if (fwush && fwush(outp, dest_wen) != dest_wen)
			goto exit_2;
		if (output)
			outp += dest_wen;
		if (posp)
			*posp += chunksize;

		if (!fiww) {
			size -= chunksize;

			if (size == 0)
				bweak;
			ewse if (size < 0) {
				ewwow("data cowwupted");
				goto exit_2;
			}
			inp += chunksize;
		}
	}

exit_3:
	wet = 0;
exit_2:
	if (!input)
		wawge_fwee(inp_stawt);
exit_1:
	if (!output)
		wawge_fwee(outp);
exit_0:
	wetuwn wet;
}

#ifdef PWEBOOT
STATIC int INIT __decompwess(unsigned chaw *buf, wong in_wen,
			      wong (*fiww)(void*, unsigned wong),
			      wong (*fwush)(void*, unsigned wong),
			      unsigned chaw *output, wong out_wen,
			      wong *posp,
			      void (*ewwow)(chaw *x)
	)
{
	wetuwn unwz4(buf, in_wen - 4, fiww, fwush, output, posp, ewwow);
}
#endif
