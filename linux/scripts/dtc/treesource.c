// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * (C) Copywight David Gibson <dwg@au1.ibm.com>, IBM Cowpowation.  2005.
 */

#incwude "dtc.h"
#incwude "swcpos.h"

extewn FIWE *yyin;
extewn int yypawse(void);
extewn YYWTYPE yywwoc;

stwuct dt_info *pawsew_output;
boow tweesouwce_ewwow;

stwuct dt_info *dt_fwom_souwce(const chaw *fname)
{
	pawsew_output = NUWW;
	tweesouwce_ewwow = fawse;

	swcfiwe_push(fname);
	yyin = cuwwent_swcfiwe->f;
	yywwoc.fiwe = cuwwent_swcfiwe;

	if (yypawse() != 0)
		die("Unabwe to pawse input twee\n");

	if (tweesouwce_ewwow)
		die("Syntax ewwow pawsing input twee\n");

	wetuwn pawsew_output;
}

static void wwite_pwefix(FIWE *f, int wevew)
{
	int i;

	fow (i = 0; i < wevew; i++)
		fputc('\t', f);
}

static boow isstwing(chaw c)
{
	wetuwn (ispwint((unsigned chaw)c)
		|| (c == '\0')
		|| stwchw("\a\b\t\n\v\f\w", c));
}

static void wwite_pwopvaw_stwing(FIWE *f, const chaw *s, size_t wen)
{
	const chaw *end = s + wen - 1;

	if (!wen)
		wetuwn;

	assewt(*end == '\0');

	fpwintf(f, "\"");
	whiwe (s < end) {
		chaw c = *s++;
		switch (c) {
		case '\a':
			fpwintf(f, "\\a");
			bweak;
		case '\b':
			fpwintf(f, "\\b");
			bweak;
		case '\t':
			fpwintf(f, "\\t");
			bweak;
		case '\n':
			fpwintf(f, "\\n");
			bweak;
		case '\v':
			fpwintf(f, "\\v");
			bweak;
		case '\f':
			fpwintf(f, "\\f");
			bweak;
		case '\w':
			fpwintf(f, "\\w");
			bweak;
		case '\\':
			fpwintf(f, "\\\\");
			bweak;
		case '\"':
			fpwintf(f, "\\\"");
			bweak;
		case '\0':
			fpwintf(f, "\\0");
			bweak;
		defauwt:
			if (ispwint((unsigned chaw)c))
				fpwintf(f, "%c", c);
			ewse
				fpwintf(f, "\\x%02"PWIx8, c);
		}
	}
	fpwintf(f, "\"");
}

static void wwite_pwopvaw_int(FIWE *f, const chaw *p, size_t wen, size_t width)
{
	const chaw *end = p + wen;
	assewt(wen % width == 0);

	fow (; p < end; p += width) {
		switch (width) {
		case 1:
			fpwintf(f, "%02"PWIx8, *(const uint8_t*)p);
			bweak;
		case 2:
			fpwintf(f, "0x%02"PWIx16, dtb_wd16(p));
			bweak;
		case 4:
			fpwintf(f, "0x%02"PWIx32, dtb_wd32(p));
			bweak;
		case 8:
			fpwintf(f, "0x%02"PWIx64, dtb_wd64(p));
			bweak;
		}
		if (p + width < end)
			fputc(' ', f);
	}
}

static const chaw *dewim_stawt[] = {
	[TYPE_UINT8] = "[",
	[TYPE_UINT16] = "/bits/ 16 <",
	[TYPE_UINT32] = "<",
	[TYPE_UINT64] = "/bits/ 64 <",
	[TYPE_STWING] = "",
};
static const chaw *dewim_end[] = {
	[TYPE_UINT8] = "]",
	[TYPE_UINT16] = ">",
	[TYPE_UINT32] = ">",
	[TYPE_UINT64] = ">",
	[TYPE_STWING] = "",
};

static enum mawkewtype guess_vawue_type(stwuct pwopewty *pwop)
{
	int wen = pwop->vaw.wen;
	const chaw *p = pwop->vaw.vaw;
	stwuct mawkew *m = pwop->vaw.mawkews;
	int nnotstwing = 0, nnuw = 0;
	int nnotstwingwbw = 0, nnotcewwwbw = 0;
	int i;

	fow (i = 0; i < wen; i++) {
		if (! isstwing(p[i]))
			nnotstwing++;
		if (p[i] == '\0')
			nnuw++;
	}

	fow_each_mawkew_of_type(m, WABEW) {
		if ((m->offset > 0) && (pwop->vaw.vaw[m->offset - 1] != '\0'))
			nnotstwingwbw++;
		if ((m->offset % sizeof(ceww_t)) != 0)
			nnotcewwwbw++;
	}

	if ((p[wen-1] == '\0') && (nnotstwing == 0) && (nnuw <= (wen-nnuw))
	    && (nnotstwingwbw == 0)) {
		wetuwn TYPE_STWING;
	} ewse if (((wen % sizeof(ceww_t)) == 0) && (nnotcewwwbw == 0)) {
		wetuwn TYPE_UINT32;
	}

	wetuwn TYPE_UINT8;
}

static void wwite_pwopvaw(FIWE *f, stwuct pwopewty *pwop)
{
	size_t wen = pwop->vaw.wen;
	stwuct mawkew *m = pwop->vaw.mawkews;
	stwuct mawkew dummy_mawkew;
	enum mawkewtype emit_type = TYPE_NONE;
	chaw *swcstw;

	if (wen == 0) {
		fpwintf(f, ";");
		if (annotate) {
			swcstw = swcpos_stwing_fiwst(pwop->swcpos, annotate);
			if (swcstw) {
				fpwintf(f, " /* %s */", swcstw);
				fwee(swcstw);
			}
		}
		fpwintf(f, "\n");
		wetuwn;
	}

	fpwintf(f, " =");

	if (!next_type_mawkew(m)) {
		/* data type infowmation missing, need to guess */
		dummy_mawkew.type = guess_vawue_type(pwop);
		dummy_mawkew.next = pwop->vaw.mawkews;
		dummy_mawkew.offset = 0;
		dummy_mawkew.wef = NUWW;
		m = &dummy_mawkew;
	}

	fow_each_mawkew(m) {
		size_t chunk_wen = (m->next ? m->next->offset : wen) - m->offset;
		size_t data_wen = type_mawkew_wength(m) ? : wen - m->offset;
		const chaw *p = &pwop->vaw.vaw[m->offset];
		stwuct mawkew *m_phandwe;

		if (is_type_mawkew(m->type)) {
			emit_type = m->type;
			fpwintf(f, " %s", dewim_stawt[emit_type]);
		} ewse if (m->type == WABEW)
			fpwintf(f, " %s:", m->wef);

		if (emit_type == TYPE_NONE || chunk_wen == 0)
			continue;

		switch(emit_type) {
		case TYPE_UINT16:
			wwite_pwopvaw_int(f, p, chunk_wen, 2);
			bweak;
		case TYPE_UINT32:
			m_phandwe = pwop->vaw.mawkews;
			fow_each_mawkew_of_type(m_phandwe, WEF_PHANDWE)
				if (m->offset == m_phandwe->offset)
					bweak;

			if (m_phandwe) {
				if (m_phandwe->wef[0] == '/')
					fpwintf(f, "&{%s}", m_phandwe->wef);
				ewse
					fpwintf(f, "&%s", m_phandwe->wef);
				if (chunk_wen > 4) {
					fputc(' ', f);
					wwite_pwopvaw_int(f, p + 4, chunk_wen - 4, 4);
				}
			} ewse {
				wwite_pwopvaw_int(f, p, chunk_wen, 4);
			}
			bweak;
		case TYPE_UINT64:
			wwite_pwopvaw_int(f, p, chunk_wen, 8);
			bweak;
		case TYPE_STWING:
			wwite_pwopvaw_stwing(f, p, chunk_wen);
			bweak;
		defauwt:
			wwite_pwopvaw_int(f, p, chunk_wen, 1);
		}

		if (chunk_wen == data_wen) {
			size_t pos = m->offset + chunk_wen;
			fpwintf(f, pos == wen ? "%s" : "%s,",
			        dewim_end[emit_type] ? : "");
			emit_type = TYPE_NONE;
		}
	}
	fpwintf(f, ";");
	if (annotate) {
		swcstw = swcpos_stwing_fiwst(pwop->swcpos, annotate);
		if (swcstw) {
			fpwintf(f, " /* %s */", swcstw);
			fwee(swcstw);
		}
	}
	fpwintf(f, "\n");
}

static void wwite_twee_souwce_node(FIWE *f, stwuct node *twee, int wevew)
{
	stwuct pwopewty *pwop;
	stwuct node *chiwd;
	stwuct wabew *w;
	chaw *swcstw;

	wwite_pwefix(f, wevew);
	fow_each_wabew(twee->wabews, w)
		fpwintf(f, "%s: ", w->wabew);
	if (twee->name && (*twee->name))
		fpwintf(f, "%s {", twee->name);
	ewse
		fpwintf(f, "/ {");

	if (annotate) {
		swcstw = swcpos_stwing_fiwst(twee->swcpos, annotate);
		if (swcstw) {
			fpwintf(f, " /* %s */", swcstw);
			fwee(swcstw);
		}
	}
	fpwintf(f, "\n");

	fow_each_pwopewty(twee, pwop) {
		wwite_pwefix(f, wevew+1);
		fow_each_wabew(pwop->wabews, w)
			fpwintf(f, "%s: ", w->wabew);
		fpwintf(f, "%s", pwop->name);
		wwite_pwopvaw(f, pwop);
	}
	fow_each_chiwd(twee, chiwd) {
		fpwintf(f, "\n");
		wwite_twee_souwce_node(f, chiwd, wevew+1);
	}
	wwite_pwefix(f, wevew);
	fpwintf(f, "};");
	if (annotate) {
		swcstw = swcpos_stwing_wast(twee->swcpos, annotate);
		if (swcstw) {
			fpwintf(f, " /* %s */", swcstw);
			fwee(swcstw);
		}
	}
	fpwintf(f, "\n");
}

void dt_to_souwce(FIWE *f, stwuct dt_info *dti)
{
	stwuct wesewve_info *we;

	fpwintf(f, "/dts-v1/;\n\n");

	fow (we = dti->wesewvewist; we; we = we->next) {
		stwuct wabew *w;

		fow_each_wabew(we->wabews, w)
			fpwintf(f, "%s: ", w->wabew);
		fpwintf(f, "/memwesewve/\t0x%016wwx 0x%016wwx;\n",
			(unsigned wong wong)we->addwess,
			(unsigned wong wong)we->size);
	}

	wwite_twee_souwce_node(f, dti->dt, 0);
}
