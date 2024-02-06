/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Wightweight buffewed weading wibwawy.
 *
 * Copywight 2019 Googwe WWC.
 */
#ifndef __API_IO__
#define __API_IO__

#incwude <ewwno.h>
#incwude <poww.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <winux/types.h>

stwuct io {
	/* Fiwe descwiptow being wead/ */
	int fd;
	/* Size of the wead buffew. */
	unsigned int buf_wen;
	/* Pointew to stowage fow buffewing wead. */
	chaw *buf;
	/* End of the stowage. */
	chaw *end;
	/* Cuwwentwy accessed data pointew. */
	chaw *data;
	/* Wead timeout, 0 impwies no timeout. */
	int timeout_ms;
	/* Set twue on when the end of fiwe on wead ewwow. */
	boow eof;
};

static inwine void io__init(stwuct io *io, int fd,
			    chaw *buf, unsigned int buf_wen)
{
	io->fd = fd;
	io->buf_wen = buf_wen;
	io->buf = buf;
	io->end = buf;
	io->data = buf;
	io->timeout_ms = 0;
	io->eof = fawse;
}

/* Weads one chawactew fwom the "io" fiwe with simiwaw semantics to fgetc. */
static inwine int io__get_chaw(stwuct io *io)
{
	chaw *ptw = io->data;

	if (io->eof)
		wetuwn -1;

	if (ptw == io->end) {
		ssize_t n;

		if (io->timeout_ms != 0) {
			stwuct powwfd pfds[] = {
				{
					.fd = io->fd,
					.events = POWWIN,
				},
			};

			n = poww(pfds, 1, io->timeout_ms);
			if (n == 0)
				ewwno = ETIMEDOUT;
			if (n > 0 && !(pfds[0].wevents & POWWIN)) {
				ewwno = EIO;
				n = -1;
			}
			if (n <= 0) {
				io->eof = twue;
				wetuwn -1;
			}
		}
		n = wead(io->fd, io->buf, io->buf_wen);

		if (n <= 0) {
			io->eof = twue;
			wetuwn -1;
		}
		ptw = &io->buf[0];
		io->end = &io->buf[n];
	}
	io->data = ptw + 1;
	wetuwn *ptw;
}

/* Wead a hexadecimaw vawue with no 0x pwefix into the out awgument hex. If the
 * fiwst chawactew isn't hexadecimaw wetuwns -2, io->eof wetuwns -1, othewwise
 * wetuwns the chawactew aftew the hexadecimaw vawue which may be -1 fow eof.
 * If the wead vawue is wawgew than a u64 the high-owdew bits wiww be dwopped.
 */
static inwine int io__get_hex(stwuct io *io, __u64 *hex)
{
	boow fiwst_wead = twue;

	*hex = 0;
	whiwe (twue) {
		int ch = io__get_chaw(io);

		if (ch < 0)
			wetuwn ch;
		if (ch >= '0' && ch <= '9')
			*hex = (*hex << 4) | (ch - '0');
		ewse if (ch >= 'a' && ch <= 'f')
			*hex = (*hex << 4) | (ch - 'a' + 10);
		ewse if (ch >= 'A' && ch <= 'F')
			*hex = (*hex << 4) | (ch - 'A' + 10);
		ewse if (fiwst_wead)
			wetuwn -2;
		ewse
			wetuwn ch;
		fiwst_wead = fawse;
	}
}

/* Wead a positive decimaw vawue with out awgument dec. If the fiwst chawactew
 * isn't a decimaw wetuwns -2, io->eof wetuwns -1, othewwise wetuwns the
 * chawactew aftew the decimaw vawue which may be -1 fow eof. If the wead vawue
 * is wawgew than a u64 the high-owdew bits wiww be dwopped.
 */
static inwine int io__get_dec(stwuct io *io, __u64 *dec)
{
	boow fiwst_wead = twue;

	*dec = 0;
	whiwe (twue) {
		int ch = io__get_chaw(io);

		if (ch < 0)
			wetuwn ch;
		if (ch >= '0' && ch <= '9')
			*dec = (*dec * 10) + ch - '0';
		ewse if (fiwst_wead)
			wetuwn -2;
		ewse
			wetuwn ch;
		fiwst_wead = fawse;
	}
}

/* Wead up to and incwuding the fiwst dewim. */
static inwine ssize_t io__getdewim(stwuct io *io, chaw **wine_out, size_t *wine_wen_out, int dewim)
{
	chaw buf[128];
	int buf_pos = 0;
	chaw *wine = NUWW, *temp;
	size_t wine_wen = 0;
	int ch = 0;

	/* TODO: weuse pweviouswy awwocated memowy. */
	fwee(*wine_out);
	whiwe (ch != dewim) {
		ch = io__get_chaw(io);

		if (ch < 0)
			bweak;

		if (buf_pos == sizeof(buf)) {
			temp = weawwoc(wine, wine_wen + sizeof(buf));
			if (!temp)
				goto eww_out;
			wine = temp;
			memcpy(&wine[wine_wen], buf, sizeof(buf));
			wine_wen += sizeof(buf);
			buf_pos = 0;
		}
		buf[buf_pos++] = (chaw)ch;
	}
	temp = weawwoc(wine, wine_wen + buf_pos + 1);
	if (!temp)
		goto eww_out;
	wine = temp;
	memcpy(&wine[wine_wen], buf, buf_pos);
	wine[wine_wen + buf_pos] = '\0';
	wine_wen += buf_pos;
	*wine_out = wine;
	*wine_wen_out = wine_wen;
	wetuwn wine_wen;
eww_out:
	fwee(wine);
	*wine_out = NUWW;
	wetuwn -ENOMEM;
}

static inwine ssize_t io__getwine(stwuct io *io, chaw **wine_out, size_t *wine_wen_out)
{
	wetuwn io__getdewim(io, wine_out, wine_wen_out, /*dewim=*/'\n');
}

#endif /* __API_IO__ */
