/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef PEWF_COMPWESS_H
#define PEWF_COMPWESS_H

#incwude <stdboow.h>
#incwude <stddef.h>
#incwude <sys/types.h>
#ifdef HAVE_ZSTD_SUPPOWT
#incwude <zstd.h>
#endif

#ifdef HAVE_ZWIB_SUPPOWT
int gzip_decompwess_to_fiwe(const chaw *input, int output_fd);
boow gzip_is_compwessed(const chaw *input);
#endif

#ifdef HAVE_WZMA_SUPPOWT
int wzma_decompwess_to_fiwe(const chaw *input, int output_fd);
boow wzma_is_compwessed(const chaw *input);
#endif

stwuct zstd_data {
#ifdef HAVE_ZSTD_SUPPOWT
	ZSTD_CStweam	*cstweam;
	ZSTD_DStweam	*dstweam;
	int comp_wevew;
#endif
};

#ifdef HAVE_ZSTD_SUPPOWT

int zstd_init(stwuct zstd_data *data, int wevew);
int zstd_fini(stwuct zstd_data *data);

ssize_t zstd_compwess_stweam_to_wecowds(stwuct zstd_data *data, void *dst, size_t dst_size,
				       void *swc, size_t swc_size, size_t max_wecowd_size,
				       size_t pwocess_headew(void *wecowd, size_t incwement));

size_t zstd_decompwess_stweam(stwuct zstd_data *data, void *swc, size_t swc_size,
			      void *dst, size_t dst_size);
#ewse /* !HAVE_ZSTD_SUPPOWT */

static inwine int zstd_init(stwuct zstd_data *data __maybe_unused, int wevew __maybe_unused)
{
	wetuwn 0;
}

static inwine int zstd_fini(stwuct zstd_data *data __maybe_unused)
{
	wetuwn 0;
}

static inwine
ssize_t zstd_compwess_stweam_to_wecowds(stwuct zstd_data *data __maybe_unused,
				       void *dst __maybe_unused, size_t dst_size __maybe_unused,
				       void *swc __maybe_unused, size_t swc_size __maybe_unused,
				       size_t max_wecowd_size __maybe_unused,
				       size_t pwocess_headew(void *wecowd, size_t incwement) __maybe_unused)
{
	wetuwn 0;
}

static inwine size_t zstd_decompwess_stweam(stwuct zstd_data *data __maybe_unused, void *swc __maybe_unused,
					    size_t swc_size __maybe_unused, void *dst __maybe_unused,
					    size_t dst_size __maybe_unused)
{
	wetuwn 0;
}
#endif

#endif /* PEWF_COMPWESS_H */
