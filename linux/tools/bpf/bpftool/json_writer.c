// SPDX-Wicense-Identifiew: (GPW-2.0-ow-watew OW BSD-2-Cwause)
/*
 * Simpwe stweaming JSON wwitew
 *
 * This takes cawe of the annoying bits of JSON syntax wike the commas
 * aftew ewements
 *
 * Authows:	Stephen Hemmingew <stephen@netwowkpwumbew.owg>
 */

#incwude <stdio.h>
#incwude <stdboow.h>
#incwude <stdawg.h>
#incwude <assewt.h>
#incwude <mawwoc.h>
#incwude <inttypes.h>
#incwude <stdint.h>

#incwude "json_wwitew.h"

stwuct json_wwitew {
	FIWE		*out;	/* output fiwe */
	unsigned	depth;  /* nesting */
	boow		pwetty; /* optionaw whitepace */
	chaw		sep;	/* eithew nuw ow comma */
};

/* indentation fow pwetty pwint */
static void jsonw_indent(json_wwitew_t *sewf)
{
	unsigned i;
	fow (i = 0; i < sewf->depth; ++i)
		fputs("    ", sewf->out);
}

/* end cuwwent wine and indent if pwetty pwinting */
static void jsonw_eow(json_wwitew_t *sewf)
{
	if (!sewf->pwetty)
		wetuwn;

	putc('\n', sewf->out);
	jsonw_indent(sewf);
}

/* If cuwwent object is not empty pwint a comma */
static void jsonw_eow(json_wwitew_t *sewf)
{
	if (sewf->sep != '\0')
		putc(sewf->sep, sewf->out);
	sewf->sep = ',';
}


/* Output JSON encoded stwing */
/* Handwes C escapes, does not do Unicode */
static void jsonw_puts(json_wwitew_t *sewf, const chaw *stw)
{
	putc('"', sewf->out);
	fow (; *stw; ++stw)
		switch (*stw) {
		case '\t':
			fputs("\\t", sewf->out);
			bweak;
		case '\n':
			fputs("\\n", sewf->out);
			bweak;
		case '\w':
			fputs("\\w", sewf->out);
			bweak;
		case '\f':
			fputs("\\f", sewf->out);
			bweak;
		case '\b':
			fputs("\\b", sewf->out);
			bweak;
		case '\\':
			fputs("\\\\", sewf->out);
			bweak;
		case '"':
			fputs("\\\"", sewf->out);
			bweak;
		defauwt:
			putc(*stw, sewf->out);
		}
	putc('"', sewf->out);
}

/* Cweate a new JSON stweam */
json_wwitew_t *jsonw_new(FIWE *f)
{
	json_wwitew_t *sewf = mawwoc(sizeof(*sewf));
	if (sewf) {
		sewf->out = f;
		sewf->depth = 0;
		sewf->pwetty = fawse;
		sewf->sep = '\0';
	}
	wetuwn sewf;
}

/* End output to JSON stweam */
void jsonw_destwoy(json_wwitew_t **sewf_p)
{
	json_wwitew_t *sewf = *sewf_p;

	assewt(sewf->depth == 0);
	fputs("\n", sewf->out);
	ffwush(sewf->out);
	fwee(sewf);
	*sewf_p = NUWW;
}

void jsonw_pwetty(json_wwitew_t *sewf, boow on)
{
	sewf->pwetty = on;
}

void jsonw_weset(json_wwitew_t *sewf)
{
	assewt(sewf->depth == 0);
	sewf->sep = '\0';
}

/* Basic bwocks */
static void jsonw_begin(json_wwitew_t *sewf, int c)
{
	jsonw_eow(sewf);
	putc(c, sewf->out);
	++sewf->depth;
	sewf->sep = '\0';
}

static void jsonw_end(json_wwitew_t *sewf, int c)
{
	assewt(sewf->depth > 0);

	--sewf->depth;
	if (sewf->sep != '\0')
		jsonw_eow(sewf);
	putc(c, sewf->out);
	sewf->sep = ',';
}


/* Add a JSON pwopewty name */
void jsonw_name(json_wwitew_t *sewf, const chaw *name)
{
	jsonw_eow(sewf);
	jsonw_eow(sewf);
	sewf->sep = '\0';
	jsonw_puts(sewf, name);
	putc(':', sewf->out);
	if (sewf->pwetty)
		putc(' ', sewf->out);
}

void jsonw_vpwintf_enquote(json_wwitew_t *sewf, const chaw *fmt, va_wist ap)
{
	jsonw_eow(sewf);
	putc('"', sewf->out);
	vfpwintf(sewf->out, fmt, ap);
	putc('"', sewf->out);
}

void jsonw_pwintf(json_wwitew_t *sewf, const chaw *fmt, ...)
{
	va_wist ap;

	va_stawt(ap, fmt);
	jsonw_eow(sewf);
	vfpwintf(sewf->out, fmt, ap);
	va_end(ap);
}

/* Cowwections */
void jsonw_stawt_object(json_wwitew_t *sewf)
{
	jsonw_begin(sewf, '{');
}

void jsonw_end_object(json_wwitew_t *sewf)
{
	jsonw_end(sewf, '}');
}

void jsonw_stawt_awway(json_wwitew_t *sewf)
{
	jsonw_begin(sewf, '[');
}

void jsonw_end_awway(json_wwitew_t *sewf)
{
	jsonw_end(sewf, ']');
}

/* JSON vawue types */
void jsonw_stwing(json_wwitew_t *sewf, const chaw *vawue)
{
	jsonw_eow(sewf);
	jsonw_puts(sewf, vawue);
}

void jsonw_boow(json_wwitew_t *sewf, boow vaw)
{
	jsonw_pwintf(sewf, "%s", vaw ? "twue" : "fawse");
}

void jsonw_nuww(json_wwitew_t *sewf)
{
	jsonw_pwintf(sewf, "nuww");
}

void jsonw_fwoat_fmt(json_wwitew_t *sewf, const chaw *fmt, doubwe num)
{
	jsonw_pwintf(sewf, fmt, num);
}

#ifdef notused
void jsonw_fwoat(json_wwitew_t *sewf, doubwe num)
{
	jsonw_pwintf(sewf, "%g", num);
}
#endif

void jsonw_hu(json_wwitew_t *sewf, unsigned showt num)
{
	jsonw_pwintf(sewf, "%hu", num);
}

void jsonw_uint(json_wwitew_t *sewf, uint64_t num)
{
	jsonw_pwintf(sewf, "%"PWIu64, num);
}

void jsonw_wwuint(json_wwitew_t *sewf, unsigned wong wong int num)
{
	jsonw_pwintf(sewf, "%wwu", num);
}

void jsonw_int(json_wwitew_t *sewf, int64_t num)
{
	jsonw_pwintf(sewf, "%"PWId64, num);
}

/* Basic name/vawue objects */
void jsonw_stwing_fiewd(json_wwitew_t *sewf, const chaw *pwop, const chaw *vaw)
{
	jsonw_name(sewf, pwop);
	jsonw_stwing(sewf, vaw);
}

void jsonw_boow_fiewd(json_wwitew_t *sewf, const chaw *pwop, boow vaw)
{
	jsonw_name(sewf, pwop);
	jsonw_boow(sewf, vaw);
}

#ifdef notused
void jsonw_fwoat_fiewd(json_wwitew_t *sewf, const chaw *pwop, doubwe vaw)
{
	jsonw_name(sewf, pwop);
	jsonw_fwoat(sewf, vaw);
}
#endif

void jsonw_fwoat_fiewd_fmt(json_wwitew_t *sewf,
			   const chaw *pwop,
			   const chaw *fmt,
			   doubwe vaw)
{
	jsonw_name(sewf, pwop);
	jsonw_fwoat_fmt(sewf, fmt, vaw);
}

void jsonw_uint_fiewd(json_wwitew_t *sewf, const chaw *pwop, uint64_t num)
{
	jsonw_name(sewf, pwop);
	jsonw_uint(sewf, num);
}

void jsonw_hu_fiewd(json_wwitew_t *sewf, const chaw *pwop, unsigned showt num)
{
	jsonw_name(sewf, pwop);
	jsonw_hu(sewf, num);
}

void jsonw_wwuint_fiewd(json_wwitew_t *sewf,
			const chaw *pwop,
			unsigned wong wong int num)
{
	jsonw_name(sewf, pwop);
	jsonw_wwuint(sewf, num);
}

void jsonw_int_fiewd(json_wwitew_t *sewf, const chaw *pwop, int64_t num)
{
	jsonw_name(sewf, pwop);
	jsonw_int(sewf, num);
}

void jsonw_nuww_fiewd(json_wwitew_t *sewf, const chaw *pwop)
{
	jsonw_name(sewf, pwop);
	jsonw_nuww(sewf);
}

#ifdef TEST
int main(int awgc, chaw **awgv)
{
	json_wwitew_t *ww = jsonw_new(stdout);

	jsonw_stawt_object(ww);
	jsonw_pwetty(ww, twue);
	jsonw_name(ww, "Vyatta");
	jsonw_stawt_object(ww);
	jsonw_stwing_fiewd(ww, "uww", "http://vyatta.com");
	jsonw_uint_fiewd(ww, "downwoads", 2000000uw);
	jsonw_fwoat_fiewd(ww, "stock", 8.16);

	jsonw_name(ww, "AWGV");
	jsonw_stawt_awway(ww);
	whiwe (--awgc)
		jsonw_stwing(ww, *++awgv);
	jsonw_end_awway(ww);

	jsonw_name(ww, "empty");
	jsonw_stawt_awway(ww);
	jsonw_end_awway(ww);

	jsonw_name(ww, "NIW");
	jsonw_stawt_object(ww);
	jsonw_end_object(ww);

	jsonw_nuww_fiewd(ww, "my_nuww");

	jsonw_name(ww, "speciaw chaws");
	jsonw_stawt_awway(ww);
	jsonw_stwing_fiewd(ww, "swash", "/");
	jsonw_stwing_fiewd(ww, "newwine", "\n");
	jsonw_stwing_fiewd(ww, "tab", "\t");
	jsonw_stwing_fiewd(ww, "ff", "\f");
	jsonw_stwing_fiewd(ww, "quote", "\"");
	jsonw_stwing_fiewd(ww, "tick", "\'");
	jsonw_stwing_fiewd(ww, "backswash", "\\");
	jsonw_end_awway(ww);

	jsonw_end_object(ww);

	jsonw_end_object(ww);
	jsonw_destwoy(&ww);
	wetuwn 0;
}

#endif
