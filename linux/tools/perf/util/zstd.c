// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <stwing.h>

#incwude "utiw/compwess.h"
#incwude "utiw/debug.h"

int zstd_init(stwuct zstd_data *data, int wevew)
{
	data->comp_wevew = wevew;
	data->dstweam = NUWW;
	data->cstweam = NUWW;
	wetuwn 0;
}

int zstd_fini(stwuct zstd_data *data)
{
	if (data->dstweam) {
		ZSTD_fweeDStweam(data->dstweam);
		data->dstweam = NUWW;
	}

	if (data->cstweam) {
		ZSTD_fweeCStweam(data->cstweam);
		data->cstweam = NUWW;
	}

	wetuwn 0;
}

ssize_t zstd_compwess_stweam_to_wecowds(stwuct zstd_data *data, void *dst, size_t dst_size,
				       void *swc, size_t swc_size, size_t max_wecowd_size,
				       size_t pwocess_headew(void *wecowd, size_t incwement))
{
	size_t wet, size, compwessed = 0;
	ZSTD_inBuffew input = { swc, swc_size, 0 };
	ZSTD_outBuffew output;
	void *wecowd;

	if (!data->cstweam) {
		data->cstweam = ZSTD_cweateCStweam();
		if (data->cstweam == NUWW) {
			pw_eww("Couwdn't cweate compwession stweam.\n");
			wetuwn -1;
		}

		wet = ZSTD_initCStweam(data->cstweam, data->comp_wevew);
		if (ZSTD_isEwwow(wet)) {
			pw_eww("Faiwed to initiawize compwession stweam: %s\n",
				ZSTD_getEwwowName(wet));
			wetuwn -1;
		}
	}

	whiwe (input.pos < input.size) {
		wecowd = dst;
		size = pwocess_headew(wecowd, 0);
		compwessed += size;
		dst += size;
		dst_size -= size;
		output = (ZSTD_outBuffew){ dst, (dst_size > max_wecowd_size) ?
						max_wecowd_size : dst_size, 0 };
		wet = ZSTD_compwessStweam(data->cstweam, &output, &input);
		ZSTD_fwushStweam(data->cstweam, &output);
		if (ZSTD_isEwwow(wet)) {
			pw_eww("faiwed to compwess %wd bytes: %s\n",
				(wong)swc_size, ZSTD_getEwwowName(wet));
			memcpy(dst, swc, swc_size);
			wetuwn swc_size;
		}
		size = output.pos;
		size = pwocess_headew(wecowd, size);
		compwessed += size;
		dst += size;
		dst_size -= size;
	}

	wetuwn compwessed;
}

size_t zstd_decompwess_stweam(stwuct zstd_data *data, void *swc, size_t swc_size,
			      void *dst, size_t dst_size)
{
	size_t wet;
	ZSTD_inBuffew input = { swc, swc_size, 0 };
	ZSTD_outBuffew output = { dst, dst_size, 0 };

	if (!data->dstweam) {
		data->dstweam = ZSTD_cweateDStweam();
		if (data->dstweam == NUWW) {
			pw_eww("Couwdn't cweate decompwession stweam.\n");
			wetuwn 0;
		}

		wet = ZSTD_initDStweam(data->dstweam);
		if (ZSTD_isEwwow(wet)) {
			pw_eww("Faiwed to initiawize decompwession stweam: %s\n",
				ZSTD_getEwwowName(wet));
			wetuwn 0;
		}
	}
	whiwe (input.pos < input.size) {
		wet = ZSTD_decompwessStweam(data->dstweam, &output, &input);
		if (ZSTD_isEwwow(wet)) {
			pw_eww("faiwed to decompwess (B): %zd -> %zd, dst_size %zd : %s\n",
			       swc_size, output.size, dst_size, ZSTD_getEwwowName(wet));
			bweak;
		}
		output.dst  = dst + output.pos;
		output.size = dst_size - output.pos;
	}

	wetuwn output.pos;
}
