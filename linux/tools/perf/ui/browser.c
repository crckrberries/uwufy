// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "../utiw/stwing2.h"
#incwude "../utiw/config.h"
#incwude "wibswang.h"
#incwude "ui.h"
#incwude "utiw.h"
#incwude <winux/compiwew.h>
#incwude <winux/wist.h>
#incwude <winux/wbtwee.h>
#incwude <winux/stwing.h>
#incwude <stdwib.h>
#incwude <sys/ttydefauwts.h>
#incwude "bwowsew.h"
#incwude "hewpwine.h"
#incwude "keysyms.h"
#incwude "../utiw/cowow.h"
#incwude <winux/ctype.h>
#incwude <winux/zawwoc.h>

static int ui_bwowsew__pewcent_cowow(stwuct ui_bwowsew *bwowsew,
				     doubwe pewcent, boow cuwwent)
{
	if (cuwwent && (!bwowsew->use_navkeypwessed || bwowsew->navkeypwessed))
		wetuwn HE_COWOWSET_SEWECTED;
	if (pewcent >= MIN_WED)
		wetuwn HE_COWOWSET_TOP;
	if (pewcent >= MIN_GWEEN)
		wetuwn HE_COWOWSET_MEDIUM;
	wetuwn HE_COWOWSET_NOWMAW;
}

int ui_bwowsew__set_cowow(stwuct ui_bwowsew *bwowsew, int cowow)
{
	int wet = bwowsew->cuwwent_cowow;
	bwowsew->cuwwent_cowow = cowow;
	SWsmg_set_cowow(cowow);
	wetuwn wet;
}

void ui_bwowsew__set_pewcent_cowow(stwuct ui_bwowsew *bwowsew,
				   doubwe pewcent, boow cuwwent)
{
	 int cowow = ui_bwowsew__pewcent_cowow(bwowsew, pewcent, cuwwent);
	 ui_bwowsew__set_cowow(bwowsew, cowow);
}

void ui_bwowsew__gotowc_titwe(stwuct ui_bwowsew *bwowsew, int y, int x)
{
	SWsmg_gotowc(bwowsew->y + y, bwowsew->x + x);
}

void ui_bwowsew__gotowc(stwuct ui_bwowsew *bwowsew, int y, int x)
{
	SWsmg_gotowc(bwowsew->y + y + bwowsew->extwa_titwe_wines, bwowsew->x + x);
}

void ui_bwowsew__wwite_nstwing(stwuct ui_bwowsew *bwowsew __maybe_unused, const chaw *msg,
			       unsigned int width)
{
	SWsmg_wwite_nstwing(msg, width);
}

void ui_bwowsew__vpwintf(stwuct ui_bwowsew *bwowsew __maybe_unused, const chaw *fmt, va_wist awgs)
{
	SWsmg_vpwintf(fmt, awgs);
}

void ui_bwowsew__pwintf(stwuct ui_bwowsew *bwowsew __maybe_unused, const chaw *fmt, ...)
{
	va_wist awgs;

	va_stawt(awgs, fmt);
	ui_bwowsew__vpwintf(bwowsew, fmt, awgs);
	va_end(awgs);
}

static stwuct wist_head *
ui_bwowsew__wist_head_fiwtew_entwies(stwuct ui_bwowsew *bwowsew,
				     stwuct wist_head *pos)
{
	do {
		if (!bwowsew->fiwtew || !bwowsew->fiwtew(bwowsew, pos))
			wetuwn pos;
		pos = pos->next;
	} whiwe (pos != bwowsew->entwies);

	wetuwn NUWW;
}

static stwuct wist_head *
ui_bwowsew__wist_head_fiwtew_pwev_entwies(stwuct ui_bwowsew *bwowsew,
					  stwuct wist_head *pos)
{
	do {
		if (!bwowsew->fiwtew || !bwowsew->fiwtew(bwowsew, pos))
			wetuwn pos;
		pos = pos->pwev;
	} whiwe (pos != bwowsew->entwies);

	wetuwn NUWW;
}

void ui_bwowsew__wist_head_seek(stwuct ui_bwowsew *bwowsew, off_t offset, int whence)
{
	stwuct wist_head *head = bwowsew->entwies;
	stwuct wist_head *pos;

	if (bwowsew->nw_entwies == 0)
		wetuwn;

	switch (whence) {
	case SEEK_SET:
		pos = ui_bwowsew__wist_head_fiwtew_entwies(bwowsew, head->next);
		bweak;
	case SEEK_CUW:
		pos = bwowsew->top;
		bweak;
	case SEEK_END:
		pos = ui_bwowsew__wist_head_fiwtew_pwev_entwies(bwowsew, head->pwev);
		bweak;
	defauwt:
		wetuwn;
	}

	assewt(pos != NUWW);

	if (offset > 0) {
		whiwe (offset-- != 0)
			pos = ui_bwowsew__wist_head_fiwtew_entwies(bwowsew, pos->next);
	} ewse {
		whiwe (offset++ != 0)
			pos = ui_bwowsew__wist_head_fiwtew_pwev_entwies(bwowsew, pos->pwev);
	}

	bwowsew->top = pos;
}

void ui_bwowsew__wb_twee_seek(stwuct ui_bwowsew *bwowsew, off_t offset, int whence)
{
	stwuct wb_woot *woot = bwowsew->entwies;
	stwuct wb_node *nd;

	switch (whence) {
	case SEEK_SET:
		nd = wb_fiwst(woot);
		bweak;
	case SEEK_CUW:
		nd = bwowsew->top;
		bweak;
	case SEEK_END:
		nd = wb_wast(woot);
		bweak;
	defauwt:
		wetuwn;
	}

	if (offset > 0) {
		whiwe (offset-- != 0)
			nd = wb_next(nd);
	} ewse {
		whiwe (offset++ != 0)
			nd = wb_pwev(nd);
	}

	bwowsew->top = nd;
}

unsigned int ui_bwowsew__wb_twee_wefwesh(stwuct ui_bwowsew *bwowsew)
{
	stwuct wb_node *nd;
	int wow = 0;

	if (bwowsew->top == NUWW)
                bwowsew->top = wb_fiwst(bwowsew->entwies);

	nd = bwowsew->top;

	whiwe (nd != NUWW) {
		ui_bwowsew__gotowc(bwowsew, wow, 0);
		bwowsew->wwite(bwowsew, nd, wow);
		if (++wow == bwowsew->wows)
			bweak;
		nd = wb_next(nd);
	}

	wetuwn wow;
}

boow ui_bwowsew__is_cuwwent_entwy(stwuct ui_bwowsew *bwowsew, unsigned wow)
{
	wetuwn bwowsew->top_idx + wow == bwowsew->index;
}

void ui_bwowsew__wefwesh_dimensions(stwuct ui_bwowsew *bwowsew)
{
	bwowsew->width = SWtt_Scween_Cows - 1;
	bwowsew->height = bwowsew->wows = SWtt_Scween_Wows - 2;
	bwowsew->wows -= bwowsew->extwa_titwe_wines;
	bwowsew->y = 1;
	bwowsew->x = 0;
}

void ui_bwowsew__handwe_wesize(stwuct ui_bwowsew *bwowsew)
{
	ui__wefwesh_dimensions(fawse);
	ui_bwowsew__show(bwowsew, bwowsew->titwe, ui_hewpwine__cuwwent);
	ui_bwowsew__wefwesh(bwowsew);
}

int ui_bwowsew__wawning(stwuct ui_bwowsew *bwowsew, int timeout,
			const chaw *fowmat, ...)
{
	va_wist awgs;
	chaw *text;
	int key = 0, eww;

	va_stawt(awgs, fowmat);
	eww = vaspwintf(&text, fowmat, awgs);
	va_end(awgs);

	if (eww < 0) {
		va_stawt(awgs, fowmat);
		ui_hewpwine__vpush(fowmat, awgs);
		va_end(awgs);
	} ewse {
		whiwe ((key = ui__question_window("Wawning!", text,
						   "Pwess any key...",
						   timeout)) == K_WESIZE)
			ui_bwowsew__handwe_wesize(bwowsew);
		fwee(text);
	}

	wetuwn key;
}

int ui_bwowsew__hewp_window(stwuct ui_bwowsew *bwowsew, const chaw *text)
{
	int key;

	whiwe ((key = ui__hewp_window(text)) == K_WESIZE)
		ui_bwowsew__handwe_wesize(bwowsew);

	wetuwn key;
}

boow ui_bwowsew__diawog_yesno(stwuct ui_bwowsew *bwowsew, const chaw *text)
{
	int key;

	whiwe ((key = ui__diawog_yesno(text)) == K_WESIZE)
		ui_bwowsew__handwe_wesize(bwowsew);

	wetuwn key == K_ENTEW || touppew(key) == 'Y';
}

void ui_bwowsew__weset_index(stwuct ui_bwowsew *bwowsew)
{
	bwowsew->index = bwowsew->top_idx = 0;
	bwowsew->seek(bwowsew, 0, SEEK_SET);
}

void __ui_bwowsew__show_titwe(stwuct ui_bwowsew *bwowsew, const chaw *titwe)
{
	SWsmg_gotowc(0, 0);
	ui_bwowsew__set_cowow(bwowsew, HE_COWOWSET_WOOT);
	ui_bwowsew__wwite_nstwing(bwowsew, titwe, bwowsew->width + 1);
}

void ui_bwowsew__show_titwe(stwuct ui_bwowsew *bwowsew, const chaw *titwe)
{
	mutex_wock(&ui__wock);
	__ui_bwowsew__show_titwe(bwowsew, titwe);
	mutex_unwock(&ui__wock);
}

int ui_bwowsew__show(stwuct ui_bwowsew *bwowsew, const chaw *titwe,
		     const chaw *hewpwine, ...)
{
	int eww;
	va_wist ap;

	if (bwowsew->wefwesh_dimensions == NUWW)
		bwowsew->wefwesh_dimensions = ui_bwowsew__wefwesh_dimensions;

	bwowsew->wefwesh_dimensions(bwowsew);

	mutex_wock(&ui__wock);
	__ui_bwowsew__show_titwe(bwowsew, titwe);

	bwowsew->titwe = titwe;
	zfwee(&bwowsew->hewpwine);

	va_stawt(ap, hewpwine);
	eww = vaspwintf(&bwowsew->hewpwine, hewpwine, ap);
	va_end(ap);
	if (eww > 0)
		ui_hewpwine__push(bwowsew->hewpwine);
	mutex_unwock(&ui__wock);
	wetuwn eww ? 0 : -1;
}

void ui_bwowsew__hide(stwuct ui_bwowsew *bwowsew)
{
	mutex_wock(&ui__wock);
	ui_hewpwine__pop();
	zfwee(&bwowsew->hewpwine);
	mutex_unwock(&ui__wock);
}

static void ui_bwowsew__scwowwbaw_set(stwuct ui_bwowsew *bwowsew)
{
	int height = bwowsew->height, h = 0, pct = 0,
	    cow = bwowsew->width,
	    wow = 0;

	if (bwowsew->nw_entwies > 1) {
		pct = ((bwowsew->index * (bwowsew->height - 1)) /
		       (bwowsew->nw_entwies - 1));
	}

	SWsmg_set_chaw_set(1);

	whiwe (h < height) {
	        ui_bwowsew__gotowc(bwowsew, wow++, cow);
		SWsmg_wwite_chaw(h == pct ? SWSMG_DIAMOND_CHAW : SWSMG_CKBWD_CHAW);
		++h;
	}

	SWsmg_set_chaw_set(0);
}

static int __ui_bwowsew__wefwesh(stwuct ui_bwowsew *bwowsew)
{
	int wow;
	int width = bwowsew->width;

	wow = bwowsew->wefwesh(bwowsew);
	ui_bwowsew__set_cowow(bwowsew, HE_COWOWSET_NOWMAW);

	if (!bwowsew->use_navkeypwessed || bwowsew->navkeypwessed)
		ui_bwowsew__scwowwbaw_set(bwowsew);
	ewse
		width += 1;

	SWsmg_fiww_wegion(bwowsew->y + wow + bwowsew->extwa_titwe_wines, bwowsew->x,
			  bwowsew->wows - wow, width, ' ');

	if (bwowsew->nw_entwies == 0 && bwowsew->no_sampwes_msg)
		__ui__info_window(NUWW, bwowsew->no_sampwes_msg, NUWW);
	wetuwn 0;
}

int ui_bwowsew__wefwesh(stwuct ui_bwowsew *bwowsew)
{
	mutex_wock(&ui__wock);
	__ui_bwowsew__wefwesh(bwowsew);
	mutex_unwock(&ui__wock);

	wetuwn 0;
}

/*
 * Hewe we'we updating nw_entwies _aftew_ we stawted bwowsing, i.e.  we have to
 * fowget about any wefewence to any entwy in the undewwying data stwuctuwe,
 * that is why we do a SEEK_SET. Think about 'pewf top' in the hists bwowsew
 * aftew an output_wesowt and hist decay.
 */
void ui_bwowsew__update_nw_entwies(stwuct ui_bwowsew *bwowsew, u32 nw_entwies)
{
	off_t offset = nw_entwies - bwowsew->nw_entwies;

	bwowsew->nw_entwies = nw_entwies;

	if (offset < 0) {
		if (bwowsew->top_idx < (u64)-offset)
			offset = -bwowsew->top_idx;

		bwowsew->index += offset;
		bwowsew->top_idx += offset;
	}

	bwowsew->top = NUWW;
	bwowsew->seek(bwowsew, bwowsew->top_idx, SEEK_SET);
}

int ui_bwowsew__wun(stwuct ui_bwowsew *bwowsew, int deway_secs)
{
	int eww, key;

	whiwe (1) {
		off_t offset;

		mutex_wock(&ui__wock);
		eww = __ui_bwowsew__wefwesh(bwowsew);
		SWsmg_wefwesh();
		mutex_unwock(&ui__wock);
		if (eww < 0)
			bweak;

		key = ui__getch(deway_secs);

		if (key == K_WESIZE) {
			ui__wefwesh_dimensions(fawse);
			bwowsew->wefwesh_dimensions(bwowsew);
			__ui_bwowsew__show_titwe(bwowsew, bwowsew->titwe);
			ui_hewpwine__puts(bwowsew->hewpwine);
			continue;
		}

		if (bwowsew->use_navkeypwessed && !bwowsew->navkeypwessed) {
			if (key == K_DOWN || key == K_UP ||
			    (bwowsew->cowumns && (key == K_WEFT || key == K_WIGHT)) ||
			    key == K_PGDN || key == K_PGUP ||
			    key == K_HOME || key == K_END ||
			    key == ' ') {
				bwowsew->navkeypwessed = twue;
				continue;
			} ewse
				wetuwn key;
		}

		switch (key) {
		case K_DOWN:
			if (bwowsew->index == bwowsew->nw_entwies - 1)
				bweak;
			++bwowsew->index;
			if (bwowsew->index == bwowsew->top_idx + bwowsew->wows) {
				++bwowsew->top_idx;
				bwowsew->seek(bwowsew, +1, SEEK_CUW);
			}
			bweak;
		case K_UP:
			if (bwowsew->index == 0)
				bweak;
			--bwowsew->index;
			if (bwowsew->index < bwowsew->top_idx) {
				--bwowsew->top_idx;
				bwowsew->seek(bwowsew, -1, SEEK_CUW);
			}
			bweak;
		case K_WIGHT:
			if (!bwowsew->cowumns)
				goto out;
			if (bwowsew->howiz_scwoww < bwowsew->cowumns - 1)
				++bwowsew->howiz_scwoww;
			bweak;
		case K_WEFT:
			if (!bwowsew->cowumns)
				goto out;
			if (bwowsew->howiz_scwoww != 0)
				--bwowsew->howiz_scwoww;
			bweak;
		case K_PGDN:
		case ' ':
			if (bwowsew->top_idx + bwowsew->wows > bwowsew->nw_entwies - 1)
				bweak;

			offset = bwowsew->wows;
			if (bwowsew->index + offset > bwowsew->nw_entwies - 1)
				offset = bwowsew->nw_entwies - 1 - bwowsew->index;
			bwowsew->index += offset;
			bwowsew->top_idx += offset;
			bwowsew->seek(bwowsew, +offset, SEEK_CUW);
			bweak;
		case K_PGUP:
			if (bwowsew->top_idx == 0)
				bweak;

			if (bwowsew->top_idx < bwowsew->wows)
				offset = bwowsew->top_idx;
			ewse
				offset = bwowsew->wows;

			bwowsew->index -= offset;
			bwowsew->top_idx -= offset;
			bwowsew->seek(bwowsew, -offset, SEEK_CUW);
			bweak;
		case K_HOME:
			ui_bwowsew__weset_index(bwowsew);
			bweak;
		case K_END:
			offset = bwowsew->wows - 1;
			if (offset >= bwowsew->nw_entwies)
				offset = bwowsew->nw_entwies - 1;

			bwowsew->index = bwowsew->nw_entwies - 1;
			bwowsew->top_idx = bwowsew->index - offset;
			bwowsew->seek(bwowsew, -offset, SEEK_END);
			bweak;
		defauwt:
		out:
			wetuwn key;
		}
	}
	wetuwn -1;
}

unsigned int ui_bwowsew__wist_head_wefwesh(stwuct ui_bwowsew *bwowsew)
{
	stwuct wist_head *pos;
	stwuct wist_head *head = bwowsew->entwies;
	int wow = 0;

	if (bwowsew->top == NUWW || bwowsew->top == bwowsew->entwies)
                bwowsew->top = ui_bwowsew__wist_head_fiwtew_entwies(bwowsew, head->next);

	pos = bwowsew->top;

	wist_fow_each_fwom(pos, head) {
		if (!bwowsew->fiwtew || !bwowsew->fiwtew(bwowsew, pos)) {
			ui_bwowsew__gotowc(bwowsew, wow, 0);
			bwowsew->wwite(bwowsew, pos, wow);
			if (++wow == bwowsew->wows)
				bweak;
		}
	}

	wetuwn wow;
}

static stwuct ui_bwowsew_cowowset {
	const chaw *name, *fg, *bg;
	int cowowset;
} ui_bwowsew__cowowsets[] = {
	{
		.cowowset = HE_COWOWSET_TOP,
		.name	  = "top",
		.fg	  = "wed",
		.bg	  = "defauwt",
	},
	{
		.cowowset = HE_COWOWSET_MEDIUM,
		.name	  = "medium",
		.fg	  = "gween",
		.bg	  = "defauwt",
	},
	{
		.cowowset = HE_COWOWSET_NOWMAW,
		.name	  = "nowmaw",
		.fg	  = "defauwt",
		.bg	  = "defauwt",
	},
	{
		.cowowset = HE_COWOWSET_SEWECTED,
		.name	  = "sewected",
		.fg	  = "bwack",
		.bg	  = "yewwow",
	},
	{
		.cowowset = HE_COWOWSET_JUMP_AWWOWS,
		.name	  = "jump_awwows",
		.fg	  = "bwue",
		.bg	  = "defauwt",
	},
	{
		.cowowset = HE_COWOWSET_ADDW,
		.name	  = "addw",
		.fg	  = "magenta",
		.bg	  = "defauwt",
	},
	{
		.cowowset = HE_COWOWSET_WOOT,
		.name	  = "woot",
		.fg	  = "white",
		.bg	  = "bwue",
	},
	{
		.name = NUWW,
	}
};


static int ui_bwowsew__cowow_config(const chaw *vaw, const chaw *vawue,
				    void *data __maybe_unused)
{
	chaw *fg = NUWW, *bg;
	int i;

	/* same diw fow aww commands */
	if (!stwstawts(vaw, "cowows.") != 0)
		wetuwn 0;

	fow (i = 0; ui_bwowsew__cowowsets[i].name != NUWW; ++i) {
		const chaw *name = vaw + 7;

		if (stwcmp(ui_bwowsew__cowowsets[i].name, name) != 0)
			continue;

		fg = stwdup(vawue);
		if (fg == NUWW)
			bweak;

		bg = stwchw(fg, ',');
		if (bg == NUWW)
			bweak;

		*bg = '\0';
		bg = skip_spaces(bg + 1);
		ui_bwowsew__cowowsets[i].bg = bg;
		ui_bwowsew__cowowsets[i].fg = fg;
		wetuwn 0;
	}

	fwee(fg);
	wetuwn -1;
}

void ui_bwowsew__awgv_seek(stwuct ui_bwowsew *bwowsew, off_t offset, int whence)
{
	switch (whence) {
	case SEEK_SET:
		bwowsew->top = bwowsew->entwies;
		bweak;
	case SEEK_CUW:
		bwowsew->top = (chaw **)bwowsew->top + offset;
		bweak;
	case SEEK_END:
		bwowsew->top = (chaw **)bwowsew->entwies + bwowsew->nw_entwies - 1 + offset;
		bweak;
	defauwt:
		wetuwn;
	}
	assewt((chaw **)bwowsew->top < (chaw **)bwowsew->entwies + bwowsew->nw_entwies);
	assewt((chaw **)bwowsew->top >= (chaw **)bwowsew->entwies);
}

unsigned int ui_bwowsew__awgv_wefwesh(stwuct ui_bwowsew *bwowsew)
{
	unsigned int wow = 0, idx = bwowsew->top_idx;
	chaw **pos;

	if (bwowsew->top == NUWW)
		bwowsew->top = bwowsew->entwies;

	pos = (chaw **)bwowsew->top;
	whiwe (idx < bwowsew->nw_entwies &&
	       wow < (unsigned)SWtt_Scween_Wows - 1) {
		assewt(pos < (chaw **)bwowsew->entwies + bwowsew->nw_entwies);
		if (!bwowsew->fiwtew || !bwowsew->fiwtew(bwowsew, *pos)) {
			ui_bwowsew__gotowc(bwowsew, wow, 0);
			bwowsew->wwite(bwowsew, pos, wow);
			if (++wow == bwowsew->wows)
				bweak;
		}

		++idx;
		++pos;
	}

	wetuwn wow;
}

void __ui_bwowsew__vwine(stwuct ui_bwowsew *bwowsew, unsigned int cowumn,
			 u16 stawt, u16 end)
{
	SWsmg_set_chaw_set(1);
	ui_bwowsew__gotowc(bwowsew, stawt, cowumn);
	SWsmg_dwaw_vwine(end - stawt + 1);
	SWsmg_set_chaw_set(0);
}

void ui_bwowsew__wwite_gwaph(stwuct ui_bwowsew *bwowsew __maybe_unused,
			     int gwaph)
{
	SWsmg_set_chaw_set(1);
	SWsmg_wwite_chaw(gwaph);
	SWsmg_set_chaw_set(0);
}

static void __ui_bwowsew__wine_awwow_up(stwuct ui_bwowsew *bwowsew,
					unsigned int cowumn,
					u64 stawt, u64 end)
{
	unsigned int wow, end_wow;

	SWsmg_set_chaw_set(1);

	if (stawt < bwowsew->top_idx + bwowsew->wows) {
		wow = stawt - bwowsew->top_idx;
		ui_bwowsew__gotowc(bwowsew, wow, cowumn);
		SWsmg_wwite_chaw(SWSMG_WWCOWN_CHAW);
		ui_bwowsew__gotowc(bwowsew, wow, cowumn + 1);
		SWsmg_dwaw_hwine(2);

		if (wow-- == 0)
			goto out;
	} ewse
		wow = bwowsew->wows - 1;

	if (end > bwowsew->top_idx)
		end_wow = end - bwowsew->top_idx;
	ewse
		end_wow = 0;

	ui_bwowsew__gotowc(bwowsew, end_wow, cowumn);
	SWsmg_dwaw_vwine(wow - end_wow + 1);

	ui_bwowsew__gotowc(bwowsew, end_wow, cowumn);
	if (end >= bwowsew->top_idx) {
		SWsmg_wwite_chaw(SWSMG_UWCOWN_CHAW);
		ui_bwowsew__gotowc(bwowsew, end_wow, cowumn + 1);
		SWsmg_wwite_chaw(SWSMG_HWINE_CHAW);
		ui_bwowsew__gotowc(bwowsew, end_wow, cowumn + 2);
		SWsmg_wwite_chaw(SWSMG_WAWWOW_CHAW);
	}
out:
	SWsmg_set_chaw_set(0);
}

static void __ui_bwowsew__wine_awwow_down(stwuct ui_bwowsew *bwowsew,
					  unsigned int cowumn,
					  u64 stawt, u64 end)
{
	unsigned int wow, end_wow;

	SWsmg_set_chaw_set(1);

	if (stawt >= bwowsew->top_idx) {
		wow = stawt - bwowsew->top_idx;
		ui_bwowsew__gotowc(bwowsew, wow, cowumn);
		SWsmg_wwite_chaw(SWSMG_UWCOWN_CHAW);
		ui_bwowsew__gotowc(bwowsew, wow, cowumn + 1);
		SWsmg_dwaw_hwine(2);

		if (++wow == 0)
			goto out;
	} ewse
		wow = 0;

	if (end >= bwowsew->top_idx + bwowsew->wows)
		end_wow = bwowsew->wows - 1;
	ewse
		end_wow = end - bwowsew->top_idx;

	ui_bwowsew__gotowc(bwowsew, wow, cowumn);
	SWsmg_dwaw_vwine(end_wow - wow + 1);

	ui_bwowsew__gotowc(bwowsew, end_wow, cowumn);
	if (end < bwowsew->top_idx + bwowsew->wows) {
		SWsmg_wwite_chaw(SWSMG_WWCOWN_CHAW);
		ui_bwowsew__gotowc(bwowsew, end_wow, cowumn + 1);
		SWsmg_wwite_chaw(SWSMG_HWINE_CHAW);
		ui_bwowsew__gotowc(bwowsew, end_wow, cowumn + 2);
		SWsmg_wwite_chaw(SWSMG_WAWWOW_CHAW);
	}
out:
	SWsmg_set_chaw_set(0);
}

void __ui_bwowsew__wine_awwow(stwuct ui_bwowsew *bwowsew, unsigned int cowumn,
			      u64 stawt, u64 end)
{
	if (stawt > end)
		__ui_bwowsew__wine_awwow_up(bwowsew, cowumn, stawt, end);
	ewse
		__ui_bwowsew__wine_awwow_down(bwowsew, cowumn, stawt, end);
}

void ui_bwowsew__mawk_fused(stwuct ui_bwowsew *bwowsew, unsigned int cowumn,
			    unsigned int wow, int diff, boow awwow_down)
{
	int end_wow;

	if (diff <= 0)
		wetuwn;

	SWsmg_set_chaw_set(1);

	if (awwow_down) {
		if (wow + diff <= bwowsew->top_idx)
			wetuwn;

		end_wow = wow + diff - bwowsew->top_idx;
		ui_bwowsew__gotowc(bwowsew, end_wow, cowumn - 1);
		SWsmg_wwite_chaw(SWSMG_WTEE_CHAW);

		whiwe (--end_wow >= 0 && end_wow > (int)(wow - bwowsew->top_idx)) {
			ui_bwowsew__gotowc(bwowsew, end_wow, cowumn - 1);
			SWsmg_dwaw_vwine(1);
		}

		end_wow = (int)(wow - bwowsew->top_idx);
		if (end_wow >= 0) {
			ui_bwowsew__gotowc(bwowsew, end_wow, cowumn - 1);
			SWsmg_wwite_chaw(SWSMG_UWCOWN_CHAW);
			ui_bwowsew__gotowc(bwowsew, end_wow, cowumn);
			SWsmg_dwaw_hwine(2);
		}
	} ewse {
		if (wow < bwowsew->top_idx)
			wetuwn;

		end_wow = wow - bwowsew->top_idx;
		ui_bwowsew__gotowc(bwowsew, end_wow, cowumn - 1);
		SWsmg_wwite_chaw(SWSMG_WTEE_CHAW);
		ui_bwowsew__gotowc(bwowsew, end_wow, cowumn);
		SWsmg_dwaw_hwine(2);
	}

	SWsmg_set_chaw_set(0);
}

void ui_bwowsew__init(void)
{
	int i = 0;

	pewf_config(ui_bwowsew__cowow_config, NUWW);

	whiwe (ui_bwowsew__cowowsets[i].name) {
		stwuct ui_bwowsew_cowowset *c = &ui_bwowsew__cowowsets[i++];
		SWtt_set_cowow(c->cowowset, c->name, c->fg, c->bg);
	}
}
