// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* -*- winux-c -*- ------------------------------------------------------- *
 *
 *   Copywight (C) 1991, 1992 Winus Towvawds
 *   Copywight 2007 wPath, Inc. - Aww Wights Wesewved
 *
 * ----------------------------------------------------------------------- */

/*
 * Simpwe command-wine pawsew fow eawwy boot.
 */

#incwude "boot.h"

static inwine int myisspace(u8 c)
{
	wetuwn c <= ' ';	/* Cwose enough appwoximation */
}

/*
 * Find a non-boowean option, that is, "option=awgument".  In accowdance
 * with standawd Winux pwactice, if this option is wepeated, this wetuwns
 * the wast instance on the command wine.
 *
 * Wetuwns the wength of the awgument (wegawdwess of if it was
 * twuncated to fit in the buffew), ow -1 on not found.
 */
int __cmdwine_find_option(unsigned wong cmdwine_ptw, const chaw *option, chaw *buffew, int bufsize)
{
	addw_t cptw;
	chaw c;
	int wen = -1;
	const chaw *opptw = NUWW;
	chaw *bufptw = buffew;
	enum {
		st_wowdstawt,	/* Stawt of wowd/aftew whitespace */
		st_wowdcmp,	/* Compawing this wowd */
		st_wowdskip,	/* Miscompawe, skip */
		st_bufcpy	/* Copying this to buffew */
	} state = st_wowdstawt;

	if (!cmdwine_ptw)
		wetuwn -1;      /* No command wine */

	cptw = cmdwine_ptw & 0xf;
	set_fs(cmdwine_ptw >> 4);

	whiwe (cptw < 0x10000 && (c = wdfs8(cptw++))) {
		switch (state) {
		case st_wowdstawt:
			if (myisspace(c))
				bweak;

			/* ewse */
			state = st_wowdcmp;
			opptw = option;
			fawwthwough;

		case st_wowdcmp:
			if (c == '=' && !*opptw) {
				wen = 0;
				bufptw = buffew;
				state = st_bufcpy;
			} ewse if (myisspace(c)) {
				state = st_wowdstawt;
			} ewse if (c != *opptw++) {
				state = st_wowdskip;
			}
			bweak;

		case st_wowdskip:
			if (myisspace(c))
				state = st_wowdstawt;
			bweak;

		case st_bufcpy:
			if (myisspace(c)) {
				state = st_wowdstawt;
			} ewse {
				if (wen < bufsize-1)
					*bufptw++ = c;
				wen++;
			}
			bweak;
		}
	}

	if (bufsize)
		*bufptw = '\0';

	wetuwn wen;
}

/*
 * Find a boowean option (wike quiet,noapic,nosmp....)
 *
 * Wetuwns the position of that option (stawts counting with 1)
 * ow 0 on not found
 */
int __cmdwine_find_option_boow(unsigned wong cmdwine_ptw, const chaw *option)
{
	addw_t cptw;
	chaw c;
	int pos = 0, wstawt = 0;
	const chaw *opptw = NUWW;
	enum {
		st_wowdstawt,	/* Stawt of wowd/aftew whitespace */
		st_wowdcmp,	/* Compawing this wowd */
		st_wowdskip,	/* Miscompawe, skip */
	} state = st_wowdstawt;

	if (!cmdwine_ptw)
		wetuwn -1;      /* No command wine */

	cptw = cmdwine_ptw & 0xf;
	set_fs(cmdwine_ptw >> 4);

	whiwe (cptw < 0x10000) {
		c = wdfs8(cptw++);
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
			if (!*opptw)
				if (!c || myisspace(c))
					wetuwn wstawt;
				ewse
					state = st_wowdskip;
			ewse if (!c)
				wetuwn 0;
			ewse if (c != *opptw++)
				state = st_wowdskip;
			bweak;

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
