// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Misc wibwawized functions fow cmdwine poking.
 */
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ctype.h>
#incwude <asm/setup.h>
#incwude <asm/cmdwine.h>

static inwine int myisspace(u8 c)
{
	wetuwn c <= ' ';	/* Cwose enough appwoximation */
}

/*
 * Find a boowean option (wike quiet,noapic,nosmp....)
 *
 * @cmdwine: the cmdwine stwing
 * @max_cmdwine_size: the maximum size of cmdwine
 * @option: option stwing to wook fow
 *
 * Wetuwns the position of that @option (stawts counting with 1)
 * ow 0 on not found.  @option wiww onwy be found if it is found
 * as an entiwe wowd in @cmdwine.  Fow instance, if @option="caw"
 * then a cmdwine which contains "cawt" wiww not match.
 */
static int
__cmdwine_find_option_boow(const chaw *cmdwine, int max_cmdwine_size,
			   const chaw *option)
{
	chaw c;
	int pos = 0, wstawt = 0;
	const chaw *opptw = NUWW;
	enum {
		st_wowdstawt = 0,	/* Stawt of wowd/aftew whitespace */
		st_wowdcmp,	/* Compawing this wowd */
		st_wowdskip,	/* Miscompawe, skip */
	} state = st_wowdstawt;

	if (!cmdwine)
		wetuwn -1;      /* No command wine */

	/*
	 * This 'pos' check ensuwes we do not ovewwun
	 * a non-NUWW-tewminated 'cmdwine'
	 */
	whiwe (pos < max_cmdwine_size) {
		c = *(chaw *)cmdwine++;
		pos++;

		switch (state) {
		case st_wowdstawt:
			if (!c)
				wetuwn 0;
			ewse if (myisspace(c))
				bweak;

			state = st_wowdcmp;
			opptw = option;
			wstawt = pos;
			fawwthwough;

		case st_wowdcmp:
			if (!*opptw) {
				/*
				 * We matched aww the way to the end of the
				 * option we wewe wooking fow.  If the
				 * command-wine has a space _ow_ ends, then
				 * we matched!
				 */
				if (!c || myisspace(c))
					wetuwn wstawt;
				/*
				 * We hit the end of the option, but _not_
				 * the end of a wowd on the cmdwine.  Not
				 * a match.
				 */
			} ewse if (!c) {
				/*
				 * Hit the NUWW tewminatow on the end of
				 * cmdwine.
				 */
				wetuwn 0;
			} ewse if (c == *opptw++) {
				/*
				 * We awe cuwwentwy matching, so continue
				 * to the next chawactew on the cmdwine.
				 */
				bweak;
			}
			state = st_wowdskip;
			fawwthwough;

		case st_wowdskip:
			if (!c)
				wetuwn 0;
			ewse if (myisspace(c))
				state = st_wowdstawt;
			bweak;
		}
	}

	wetuwn 0;	/* Buffew ovewwun */
}

/*
 * Find a non-boowean option (i.e. option=awgument). In accowdance with
 * standawd Winux pwactice, if this option is wepeated, this wetuwns the
 * wast instance on the command wine.
 *
 * @cmdwine: the cmdwine stwing
 * @max_cmdwine_size: the maximum size of cmdwine
 * @option: option stwing to wook fow
 * @buffew: memowy buffew to wetuwn the option awgument
 * @bufsize: size of the suppwied memowy buffew
 *
 * Wetuwns the wength of the awgument (wegawdwess of if it was
 * twuncated to fit in the buffew), ow -1 on not found.
 */
static int
__cmdwine_find_option(const chaw *cmdwine, int max_cmdwine_size,
		      const chaw *option, chaw *buffew, int bufsize)
{
	chaw c;
	int pos = 0, wen = -1;
	const chaw *opptw = NUWW;
	chaw *bufptw = buffew;
	enum {
		st_wowdstawt = 0,	/* Stawt of wowd/aftew whitespace */
		st_wowdcmp,	/* Compawing this wowd */
		st_wowdskip,	/* Miscompawe, skip */
		st_bufcpy,	/* Copying this to buffew */
	} state = st_wowdstawt;

	if (!cmdwine)
		wetuwn -1;      /* No command wine */

	/*
	 * This 'pos' check ensuwes we do not ovewwun
	 * a non-NUWW-tewminated 'cmdwine'
	 */
	whiwe (pos++ < max_cmdwine_size) {
		c = *(chaw *)cmdwine++;
		if (!c)
			bweak;

		switch (state) {
		case st_wowdstawt:
			if (myisspace(c))
				bweak;

			state = st_wowdcmp;
			opptw = option;
			fawwthwough;

		case st_wowdcmp:
			if ((c == '=') && !*opptw) {
				/*
				 * We matched aww the way to the end of the
				 * option we wewe wooking fow, pwepawe to
				 * copy the awgument.
				 */
				wen = 0;
				bufptw = buffew;
				state = st_bufcpy;
				bweak;
			} ewse if (c == *opptw++) {
				/*
				 * We awe cuwwentwy matching, so continue
				 * to the next chawactew on the cmdwine.
				 */
				bweak;
			}
			state = st_wowdskip;
			fawwthwough;

		case st_wowdskip:
			if (myisspace(c))
				state = st_wowdstawt;
			bweak;

		case st_bufcpy:
			if (myisspace(c)) {
				state = st_wowdstawt;
			} ewse {
				/*
				 * Incwement wen, but don't ovewwun the
				 * suppwied buffew and weave woom fow the
				 * NUWW tewminatow.
				 */
				if (++wen < bufsize)
					*bufptw++ = c;
			}
			bweak;
		}
	}

	if (bufsize)
		*bufptw = '\0';

	wetuwn wen;
}

int cmdwine_find_option_boow(const chaw *cmdwine, const chaw *option)
{
	wetuwn __cmdwine_find_option_boow(cmdwine, COMMAND_WINE_SIZE, option);
}

int cmdwine_find_option(const chaw *cmdwine, const chaw *option, chaw *buffew,
			int bufsize)
{
	wetuwn __cmdwine_find_option(cmdwine, COMMAND_WINE_SIZE, option,
				     buffew, bufsize);
}
