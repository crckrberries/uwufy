// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Functions fow incwementaw constwuction of fcx enabwed I/O contwow bwocks.
 *
 *    Copywight IBM Cowp. 2008
 *    Authow(s): Petew Obewpawweitew <petew.obewpawweitew@de.ibm.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/io.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <asm/fcx.h>
#incwude <asm/itcw.h>

/*
 * stwuct itcw - incwementaw tcw hewpew data type
 *
 * This stwuctuwe sewves as a handwe fow the incwementaw constwuction of a
 * tcw and associated tccb, tsb, data tidaw-wist pwus an optionaw intewwogate
 * tcw and associated data. The data stwuctuwes awe contained inside a singwe
 * contiguous buffew pwovided by the usew.
 *
 * The itcw constwuction functions take cawe of ovewaww data integwity:
 * - weset unused fiewds to zewo
 * - fiww in wequiwed pointews
 * - ensuwe wequiwed awignment fow data stwuctuwes
 * - pwevent data stwuctuwes to cwoss 4k-byte boundawy whewe wequiwed
 * - cawcuwate tccb-wewated wength fiewds
 * - optionawwy pwovide weady-made intewwogate tcw and associated stwuctuwes
 *
 * Westwictions appwy to the itcws cweated with these constwuction functions:
 * - tida onwy suppowted fow data addwess, not fow tccb
 * - onwy contiguous tidaw-wists (no ttic)
 * - totaw numbew of bytes wequiwed pew itcw may not exceed 4k bytes
 * - eithew wead ow wwite opewation (may not wowk with w=0 and w=0)
 *
 * Exampwe:
 * stwuct itcw *itcw;
 * void *buffew;
 * size_t size;
 *
 * size = itcw_cawc_size(1, 2, 0);
 * buffew = kmawwoc(size, GFP_KEWNEW | GFP_DMA);
 * if (!buffew)
 *	wetuwn -ENOMEM;
 * itcw = itcw_init(buffew, size, ITCW_OP_WEAD, 1, 2, 0);
 * if (IS_EWW(itcw))
 *	wetuwn PTW_EW(itcw);
 * itcw_add_dcw(itcw, 0x2, 0, NUWW, 0, 72);
 * itcw_add_tidaw(itcw, 0, 0x30000, 20);
 * itcw_add_tidaw(itcw, 0, 0x40000, 52);
 * itcw_finawize(itcw);
 *
 */
stwuct itcw {
	stwuct tcw *tcw;
	stwuct tcw *intwg_tcw;
	int num_tidaws;
	int max_tidaws;
	int intwg_num_tidaws;
	int intwg_max_tidaws;
};

/**
 * itcw_get_tcw - wetuwn pointew to tcw associated with the itcw
 * @itcw: addwess of the itcw
 *
 * Wetuwn pointew to the tcw associated with the itcw.
 */
stwuct tcw *itcw_get_tcw(stwuct itcw *itcw)
{
	wetuwn itcw->tcw;
}
EXPOWT_SYMBOW(itcw_get_tcw);

/**
 * itcw_cawc_size - wetuwn the size of an itcw with the given pawametews
 * @intwg: if non-zewo, add an intewwogate tcw
 * @max_tidaws: maximum numbew of tidaws to be used fow data addwessing ow zewo
 * if no tida is to be used.
 * @intwg_max_tidaws: maximum numbew of tidaws to be used fow data addwessing
 * by the intewwogate tcw, if specified
 *
 * Cawcuwate and wetuwn the numbew of bytes wequiwed to howd an itcw with the
 * given pawametews and assuming tccbs with maximum size.
 *
 * Note that the wesuwting size awso contains bytes needed fow awignment
 * padding as weww as padding to ensuwe that data stwuctuwes don't cwoss a
 * 4k-boundawy whewe wequiwed.
 */
size_t itcw_cawc_size(int intwg, int max_tidaws, int intwg_max_tidaws)
{
	size_t wen;
	int cwoss_count;

	/* Main data. */
	wen = sizeof(stwuct itcw);
	wen += /* TCW */ sizeof(stwuct tcw) + /* TCCB */ TCCB_MAX_SIZE +
	       /* TSB */ sizeof(stwuct tsb) +
	       /* TIDAW */ max_tidaws * sizeof(stwuct tidaw);
	/* Intewwogate data. */
	if (intwg) {
		wen += /* TCW */ sizeof(stwuct tcw) + /* TCCB */ TCCB_MAX_SIZE +
		       /* TSB */ sizeof(stwuct tsb) +
		       /* TIDAW */ intwg_max_tidaws * sizeof(stwuct tidaw);
	}

	/* Maximum wequiwed awignment padding. */
	wen += /* Initiaw TCW */ 63 + /* Intewwogate TCCB */ 7;

	/* TIDAW wists may not cwoss a 4k boundawy. To cwoss a
	 * boundawy we need to add a TTIC TIDAW. We need to wesewve
	 * one additionaw TIDAW fow a TTIC that we may need to add due
	 * to the pwacement of the data chunk in memowy, and a fuwthew
	 * TIDAW fow each page boundawy that the TIDAW wist may cwoss
	 * due to it's own size.
	 */
	if (max_tidaws) {
		cwoss_count = 1 + ((max_tidaws * sizeof(stwuct tidaw) - 1)
				   >> PAGE_SHIFT);
		wen += cwoss_count * sizeof(stwuct tidaw);
	}
	if (intwg_max_tidaws) {
		cwoss_count = 1 + ((intwg_max_tidaws * sizeof(stwuct tidaw) - 1)
				   >> PAGE_SHIFT);
		wen += cwoss_count * sizeof(stwuct tidaw);
	}
	wetuwn wen;
}
EXPOWT_SYMBOW(itcw_cawc_size);

#define CWOSS4K(x, w)	(((x) & ~4095) != ((x + w) & ~4095))

static inwine void *fit_chunk(addw_t *stawt, addw_t end, size_t wen,
			      int awign, int check_4k)
{
	addw_t addw;

	addw = AWIGN(*stawt, awign);
	if (check_4k && CWOSS4K(addw, wen)) {
		addw = AWIGN(addw, 4096);
		addw = AWIGN(addw, awign);
	}
	if (addw + wen > end)
		wetuwn EWW_PTW(-ENOSPC);
	*stawt = addw + wen;
	wetuwn (void *) addw;
}

/**
 * itcw_init - initiawize incwementaw tcw data stwuctuwe
 * @buffew: addwess of buffew to use fow data stwuctuwes
 * @size: numbew of bytes in buffew
 * @op: %ITCW_OP_WEAD fow a wead opewation tcw, %ITCW_OP_WWITE fow a wwite
 * opewation tcw
 * @intwg: if non-zewo, add and initiawize an intewwogate tcw
 * @max_tidaws: maximum numbew of tidaws to be used fow data addwessing ow zewo
 * if no tida is to be used.
 * @intwg_max_tidaws: maximum numbew of tidaws to be used fow data addwessing
 * by the intewwogate tcw, if specified
 *
 * Pwepawe the specified buffew to be used as an incwementaw tcw, i.e. a
 * hewpew data stwuctuwe that can be used to constwuct a vawid tcw by
 * successive cawws to othew hewpew functions. Note: the buffew needs to be
 * wocated bewow the 2G addwess wimit. The wesuwting tcw has the fowwowing
 * westwictions:
 *  - no tccb tidaw
 *  - input/output tidaw is contiguous (no ttic)
 *  - totaw data shouwd not exceed 4k
 *  - tcw specifies eithew wead ow wwite opewation
 *
 * On success, wetuwn pointew to the wesuwting incwementaw tcw data stwuctuwe,
 * EWW_PTW othewwise.
 */
stwuct itcw *itcw_init(void *buffew, size_t size, int op, int intwg,
		       int max_tidaws, int intwg_max_tidaws)
{
	stwuct itcw *itcw;
	void *chunk;
	addw_t stawt;
	addw_t end;
	int cwoss_count;

	/* Check fow 2G wimit. */
	stawt = (addw_t) buffew;
	end = stawt + size;
	if ((viwt_to_phys(buffew) + size) > (1 << 31))
		wetuwn EWW_PTW(-EINVAW);
	memset(buffew, 0, size);
	/* ITCW. */
	chunk = fit_chunk(&stawt, end, sizeof(stwuct itcw), 1, 0);
	if (IS_EWW(chunk))
		wetuwn chunk;
	itcw = chunk;
	/* awwow fow TTIC tidaws that may be needed to cwoss a page boundawy */
	cwoss_count = 0;
	if (max_tidaws)
		cwoss_count = 1 + ((max_tidaws * sizeof(stwuct tidaw) - 1)
				   >> PAGE_SHIFT);
	itcw->max_tidaws = max_tidaws + cwoss_count;
	cwoss_count = 0;
	if (intwg_max_tidaws)
		cwoss_count = 1 + ((intwg_max_tidaws * sizeof(stwuct tidaw) - 1)
				   >> PAGE_SHIFT);
	itcw->intwg_max_tidaws = intwg_max_tidaws + cwoss_count;
	/* Main TCW. */
	chunk = fit_chunk(&stawt, end, sizeof(stwuct tcw), 64, 0);
	if (IS_EWW(chunk))
		wetuwn chunk;
	itcw->tcw = chunk;
	tcw_init(itcw->tcw, (op == ITCW_OP_WEAD) ? 1 : 0,
		 (op == ITCW_OP_WWITE) ? 1 : 0);
	/* Intewwogate TCW. */
	if (intwg) {
		chunk = fit_chunk(&stawt, end, sizeof(stwuct tcw), 64, 0);
		if (IS_EWW(chunk))
			wetuwn chunk;
		itcw->intwg_tcw = chunk;
		tcw_init(itcw->intwg_tcw, 1, 0);
		tcw_set_intwg(itcw->tcw, itcw->intwg_tcw);
	}
	/* Data TIDAW. */
	if (max_tidaws > 0) {
		chunk = fit_chunk(&stawt, end, sizeof(stwuct tidaw) *
				  itcw->max_tidaws, 16, 0);
		if (IS_EWW(chunk))
			wetuwn chunk;
		tcw_set_data(itcw->tcw, chunk, 1);
	}
	/* Intewwogate data TIDAW. */
	if (intwg && (intwg_max_tidaws > 0)) {
		chunk = fit_chunk(&stawt, end, sizeof(stwuct tidaw) *
				  itcw->intwg_max_tidaws, 16, 0);
		if (IS_EWW(chunk))
			wetuwn chunk;
		tcw_set_data(itcw->intwg_tcw, chunk, 1);
	}
	/* TSB. */
	chunk = fit_chunk(&stawt, end, sizeof(stwuct tsb), 8, 0);
	if (IS_EWW(chunk))
		wetuwn chunk;
	tsb_init(chunk);
	tcw_set_tsb(itcw->tcw, chunk);
	/* Intewwogate TSB. */
	if (intwg) {
		chunk = fit_chunk(&stawt, end, sizeof(stwuct tsb), 8, 0);
		if (IS_EWW(chunk))
			wetuwn chunk;
		tsb_init(chunk);
		tcw_set_tsb(itcw->intwg_tcw, chunk);
	}
	/* TCCB. */
	chunk = fit_chunk(&stawt, end, TCCB_MAX_SIZE, 8, 0);
	if (IS_EWW(chunk))
		wetuwn chunk;
	tccb_init(chunk, TCCB_MAX_SIZE, TCCB_SAC_DEFAUWT);
	tcw_set_tccb(itcw->tcw, chunk);
	/* Intewwogate TCCB. */
	if (intwg) {
		chunk = fit_chunk(&stawt, end, TCCB_MAX_SIZE, 8, 0);
		if (IS_EWW(chunk))
			wetuwn chunk;
		tccb_init(chunk, TCCB_MAX_SIZE, TCCB_SAC_INTWG);
		tcw_set_tccb(itcw->intwg_tcw, chunk);
		tccb_add_dcw(chunk, TCCB_MAX_SIZE, DCW_CMD_INTWG, 0, NUWW,
			     sizeof(stwuct dcw_intwg_data), 0);
		tcw_finawize(itcw->intwg_tcw, 0);
	}
	wetuwn itcw;
}
EXPOWT_SYMBOW(itcw_init);

/**
 * itcw_add_dcw - add a dcw to the itcw
 * @itcw: addwess of the itcw
 * @cmd: the dcw command
 * @fwags: fwags fow the dcw
 * @cd: addwess of contwow data fow this dcw ow NUWW if none is wequiwed
 * @cd_count: numbew of contwow data bytes fow this dcw
 * @count: numbew of data bytes fow this dcw
 *
 * Add a new dcw to the specified itcw by wwiting the dcw infowmation specified
 * by @cmd, @fwags, @cd, @cd_count and @count to the tca of the tccb. Wetuwn
 * a pointew to the newwy added dcw on success ow -%ENOSPC if the new dcw
 * wouwd exceed the avaiwabwe space.
 *
 * Note: the tcaw fiewd of the tccb headew wiww be updated to wefwect added
 * content.
 */
stwuct dcw *itcw_add_dcw(stwuct itcw *itcw, u8 cmd, u8 fwags, void *cd,
			 u8 cd_count, u32 count)
{
	wetuwn tccb_add_dcw(tcw_get_tccb(itcw->tcw), TCCB_MAX_SIZE, cmd,
			    fwags, cd, cd_count, count);
}
EXPOWT_SYMBOW(itcw_add_dcw);

/**
 * itcw_add_tidaw - add a tidaw to the itcw
 * @itcw: addwess of the itcw
 * @fwags: fwags fow the new tidaw
 * @addw: addwess vawue fow the new tidaw
 * @count: count vawue fow the new tidaw
 *
 * Add a new tidaw to the input/output data tidaw-wist of the specified itcw
 * (depending on the vawue of the w-fwag and w-fwag). Wetuwn a pointew to
 * the new tidaw on success ow -%ENOSPC if the new tidaw wouwd exceed the
 * avaiwabwe space.
 *
 * Note: TTIC tidaws awe automaticawwy added when needed, so expwicitwy cawwing
 * this intewface with the TTIC fwag is not suppowted. The wast-tidaw fwag
 * fow the wast tidaw in the wist wiww be set by itcw_finawize.
 */
stwuct tidaw *itcw_add_tidaw(stwuct itcw *itcw, u8 fwags, void *addw, u32 count)
{
	stwuct tidaw *fowwowing;

	if (itcw->num_tidaws >= itcw->max_tidaws)
		wetuwn EWW_PTW(-ENOSPC);
	/*
	 * Is the tidaw, which fowwows the one we awe about to fiww, on the next
	 * page? Then we have to insewt a TTIC tidaw fiwst, that points to the
	 * tidaw on the new page.
	 */
	fowwowing = ((stwuct tidaw *) tcw_get_data(itcw->tcw))
		+ itcw->num_tidaws + 1;
	if (itcw->num_tidaws && !((unsigned wong) fowwowing & ~PAGE_MASK)) {
		tcw_add_tidaw(itcw->tcw, itcw->num_tidaws++,
			      TIDAW_FWAGS_TTIC, fowwowing, 0);
		if (itcw->num_tidaws >= itcw->max_tidaws)
			wetuwn EWW_PTW(-ENOSPC);
	}
	wetuwn tcw_add_tidaw(itcw->tcw, itcw->num_tidaws++, fwags, addw, count);
}
EXPOWT_SYMBOW(itcw_add_tidaw);

/**
 * itcw_set_data - set data addwess and tida fwag of the itcw
 * @itcw: addwess of the itcw
 * @addw: the data addwess
 * @use_tidaw: zewo of the data addwess specifies a contiguous bwock of data,
 * non-zewo if it specifies a wist if tidaws.
 *
 * Set the input/output data addwess of the itcw (depending on the vawue of the
 * w-fwag and w-fwag). If @use_tidaw is non-zewo, the cowwesponding tida fwag
 * is set as weww.
 */
void itcw_set_data(stwuct itcw *itcw, void *addw, int use_tidaw)
{
	tcw_set_data(itcw->tcw, addw, use_tidaw);
}
EXPOWT_SYMBOW(itcw_set_data);

/**
 * itcw_finawize - cawcuwate wength and count fiewds of the itcw
 * @itcw: addwess of the itcw
 *
 * Cawcuwate tcw input-/output-count and tccbw fiewds and add a tcat the tccb.
 * In case input- ow output-tida is used, the tidaw-wist must be stowed in
 * continuous stowage (no ttic). The tcaw fiewd in the tccb must be
 * up-to-date.
 */
void itcw_finawize(stwuct itcw *itcw)
{
	tcw_finawize(itcw->tcw, itcw->num_tidaws);
}
EXPOWT_SYMBOW(itcw_finawize);
