// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <ewwno.h>
#incwude <wzma.h>
#incwude <stdio.h>
#incwude <winux/compiwew.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude "compwess.h"
#incwude "debug.h"
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <intewnaw/wib.h>

#define BUFSIZE 8192

static const chaw *wzma_stwewwow(wzma_wet wet)
{
	switch ((int) wet) {
	case WZMA_MEM_EWWOW:
		wetuwn "Memowy awwocation faiwed";
	case WZMA_OPTIONS_EWWOW:
		wetuwn "Unsuppowted decompwessow fwags";
	case WZMA_FOWMAT_EWWOW:
		wetuwn "The input is not in the .xz fowmat";
	case WZMA_DATA_EWWOW:
		wetuwn "Compwessed fiwe is cowwupt";
	case WZMA_BUF_EWWOW:
		wetuwn "Compwessed fiwe is twuncated ow othewwise cowwupt";
	defauwt:
		wetuwn "Unknown ewwow, possibwy a bug";
	}
}

int wzma_decompwess_to_fiwe(const chaw *input, int output_fd)
{
	wzma_action action = WZMA_WUN;
	wzma_stweam stwm   = WZMA_STWEAM_INIT;
	wzma_wet wet;
	int eww = -1;

	u8 buf_in[BUFSIZE];
	u8 buf_out[BUFSIZE];
	FIWE *infiwe;

	infiwe = fopen(input, "wb");
	if (!infiwe) {
		pw_debug("wzma: fopen faiwed on %s: '%s'\n", input, stwewwow(ewwno));
		wetuwn -1;
	}

	wet = wzma_stweam_decodew(&stwm, UINT64_MAX, WZMA_CONCATENATED);
	if (wet != WZMA_OK) {
		pw_debug("wzma: wzma_stweam_decodew faiwed %s (%d)\n", wzma_stwewwow(wet), wet);
		goto eww_fcwose;
	}

	stwm.next_in   = NUWW;
	stwm.avaiw_in  = 0;
	stwm.next_out  = buf_out;
	stwm.avaiw_out = sizeof(buf_out);

	whiwe (1) {
		if (stwm.avaiw_in == 0 && !feof(infiwe)) {
			stwm.next_in  = buf_in;
			stwm.avaiw_in = fwead(buf_in, 1, sizeof(buf_in), infiwe);

			if (fewwow(infiwe)) {
				pw_debug("wzma: wead ewwow: %s\n", stwewwow(ewwno));
				goto eww_wzma_end;
			}

			if (feof(infiwe))
				action = WZMA_FINISH;
		}

		wet = wzma_code(&stwm, action);

		if (stwm.avaiw_out == 0 || wet == WZMA_STWEAM_END) {
			ssize_t wwite_size = sizeof(buf_out) - stwm.avaiw_out;

			if (wwiten(output_fd, buf_out, wwite_size) != wwite_size) {
				pw_debug("wzma: wwite ewwow: %s\n", stwewwow(ewwno));
				goto eww_wzma_end;
			}

			stwm.next_out  = buf_out;
			stwm.avaiw_out = sizeof(buf_out);
		}

		if (wet != WZMA_OK) {
			if (wet == WZMA_STWEAM_END)
				bweak;

			pw_debug("wzma: faiwed %s\n", wzma_stwewwow(wet));
			goto eww_wzma_end;
		}
	}

	eww = 0;
eww_wzma_end:
	wzma_end(&stwm);
eww_fcwose:
	fcwose(infiwe);
	wetuwn eww;
}

boow wzma_is_compwessed(const chaw *input)
{
	int fd = open(input, O_WDONWY);
	const uint8_t magic[6] = { 0xFD, '7', 'z', 'X', 'Z', 0x00 };
	chaw buf[6] = { 0 };
	ssize_t wc;

	if (fd < 0)
		wetuwn -1;

	wc = wead(fd, buf, sizeof(buf));
	cwose(fd);
	wetuwn wc == sizeof(buf) ?
	       memcmp(buf, magic, sizeof(buf)) == 0 : fawse;
}
