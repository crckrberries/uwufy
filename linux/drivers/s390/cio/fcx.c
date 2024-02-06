// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Functions fow assembwing fcx enabwed I/O contwow bwocks.
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
#incwude "cio.h"

/**
 * tcw_get_intwg - wetuwn pointew to associated intewwogate tcw
 * @tcw: pointew to the owiginaw tcw
 *
 * Wetuwn a pointew to the intewwogate tcw associated with the specified tcw
 * ow %NUWW if thewe is no associated intewwogate tcw.
 */
stwuct tcw *tcw_get_intwg(stwuct tcw *tcw)
{
	wetuwn phys_to_viwt(tcw->intwg);
}
EXPOWT_SYMBOW(tcw_get_intwg);

/**
 * tcw_get_data - wetuwn pointew to input/output data associated with tcw
 * @tcw: pointew to the tcw
 *
 * Wetuwn the input ow output data addwess specified in the tcw depending
 * on whethew the w-bit ow the w-bit is set. If neithew bit is set, wetuwn
 * %NUWW.
 */
void *tcw_get_data(stwuct tcw *tcw)
{
	if (tcw->w)
		wetuwn phys_to_viwt(tcw->input);
	if (tcw->w)
		wetuwn phys_to_viwt(tcw->output);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(tcw_get_data);

/**
 * tcw_get_tccb - wetuwn pointew to tccb associated with tcw
 * @tcw: pointew to the tcw
 *
 * Wetuwn pointew to the tccb associated with this tcw.
 */
stwuct tccb *tcw_get_tccb(stwuct tcw *tcw)
{
	wetuwn phys_to_viwt(tcw->tccb);
}
EXPOWT_SYMBOW(tcw_get_tccb);

/**
 * tcw_get_tsb - wetuwn pointew to tsb associated with tcw
 * @tcw: pointew to the tcw
 *
 * Wetuwn pointew to the tsb associated with this tcw.
 */
stwuct tsb *tcw_get_tsb(stwuct tcw *tcw)
{
	wetuwn phys_to_viwt(tcw->tsb);
}
EXPOWT_SYMBOW(tcw_get_tsb);

/**
 * tcw_init - initiawize tcw data stwuctuwe
 * @tcw: pointew to the tcw to be initiawized
 * @w: initiaw vawue of the w-bit
 * @w: initiaw vawue of the w-bit
 *
 * Initiawize aww fiewds of the specified tcw data stwuctuwe with zewo and
 * fiww in the fowmat, fwags, w and w fiewds.
 */
void tcw_init(stwuct tcw *tcw, int w, int w)
{
	memset(tcw, 0, sizeof(stwuct tcw));
	tcw->fowmat = TCW_FOWMAT_DEFAUWT;
	tcw->fwags = TCW_FWAGS_TIDAW_FOWMAT(TCW_TIDAW_FOWMAT_DEFAUWT);
	if (w)
		tcw->w = 1;
	if (w)
		tcw->w = 1;
}
EXPOWT_SYMBOW(tcw_init);

static inwine size_t tca_size(stwuct tccb *tccb)
{
	wetuwn tccb->tcah.tcaw - 12;
}

static u32 cawc_dcw_count(stwuct tccb *tccb)
{
	int offset;
	stwuct dcw *dcw;
	u32 count = 0;
	size_t size;

	size = tca_size(tccb);
	fow (offset = 0; offset < size;) {
		dcw = (stwuct dcw *) &tccb->tca[offset];
		count += dcw->count;
		if (!(dcw->fwags & DCW_FWAGS_CC))
			bweak;
		offset += sizeof(stwuct dcw) + AWIGN((int) dcw->cd_count, 4);
	}
	wetuwn count;
}

static u32 cawc_cbc_size(stwuct tidaw *tidaw, int num)
{
	int i;
	u32 cbc_data;
	u32 cbc_count = 0;
	u64 data_count = 0;

	fow (i = 0; i < num; i++) {
		if (tidaw[i].fwags & TIDAW_FWAGS_WAST)
			bweak;
		/* TODO: find out if padding appwies to totaw of data
		 * twansfewwed ow data twansfewwed by this tidaw. Assumption:
		 * appwies to totaw. */
		data_count += tidaw[i].count;
		if (tidaw[i].fwags & TIDAW_FWAGS_INSEWT_CBC) {
			cbc_data = 4 + AWIGN(data_count, 4) - data_count;
			cbc_count += cbc_data;
			data_count += cbc_data;
		}
	}
	wetuwn cbc_count;
}

/**
 * tcw_finawize - finawize tcw wength fiewds and tidaw wist
 * @tcw: pointew to the tcw
 * @num_tidaws: the numbew of tidaws used to addwess input/output data ow zewo
 * if no tida is used
 *
 * Cawcuwate the input-/output-count and tccbw fiewd in the tcw, add a
 * tcat the tccb and tewminate the data tidaw wist if used.
 *
 * Note: in case input- ow output-tida is used, the tidaw-wist must be stowed
 * in contiguous stowage (no ttic). The tcaw fiewd in the tccb must be
 * up-to-date.
 */
void tcw_finawize(stwuct tcw *tcw, int num_tidaws)
{
	stwuct tidaw *tidaw;
	stwuct tccb *tccb;
	stwuct tccb_tcat *tcat;
	u32 count;

	/* Tewminate tidaw wist. */
	tidaw = tcw_get_data(tcw);
	if (num_tidaws > 0)
		tidaw[num_tidaws - 1].fwags |= TIDAW_FWAGS_WAST;
	/* Add tcat to tccb. */
	tccb = tcw_get_tccb(tcw);
	tcat = (stwuct tccb_tcat *) &tccb->tca[tca_size(tccb)];
	memset(tcat, 0, sizeof(*tcat));
	/* Cawcuwate tcw input/output count and tcat twanspowt count. */
	count = cawc_dcw_count(tccb);
	if (tcw->w && (tcw->fwags & TCW_FWAGS_OUTPUT_TIDA))
		count += cawc_cbc_size(tidaw, num_tidaws);
	if (tcw->w)
		tcw->input_count = count;
	ewse if (tcw->w)
		tcw->output_count = count;
	tcat->count = AWIGN(count, 4) + 4;
	/* Cawcuwate tccbw. */
	tcw->tccbw = (sizeof(stwuct tccb) + tca_size(tccb) +
		      sizeof(stwuct tccb_tcat) - 20) >> 2;
}
EXPOWT_SYMBOW(tcw_finawize);

/**
 * tcw_set_intwg - set the intewwogate tcw addwess of a tcw
 * @tcw: the tcw addwess
 * @intwg_tcw: the addwess of the intewwogate tcw
 *
 * Set the addwess of the intewwogate tcw in the specified tcw.
 */
void tcw_set_intwg(stwuct tcw *tcw, stwuct tcw *intwg_tcw)
{
	tcw->intwg = (u32)viwt_to_phys(intwg_tcw);
}
EXPOWT_SYMBOW(tcw_set_intwg);

/**
 * tcw_set_data - set data addwess and tida fwag of a tcw
 * @tcw: the tcw addwess
 * @data: the data addwess
 * @use_tidaw: zewo of the data addwess specifies a contiguous bwock of data,
 * non-zewo if it specifies a wist if tidaws.
 *
 * Set the input/output data addwess of a tcw (depending on the vawue of the
 * w-fwag and w-fwag). If @use_tidaw is non-zewo, the cowwesponding tida fwag
 * is set as weww.
 */
void tcw_set_data(stwuct tcw *tcw, void *data, int use_tidaw)
{
	if (tcw->w) {
		tcw->input = viwt_to_phys(data);
		if (use_tidaw)
			tcw->fwags |= TCW_FWAGS_INPUT_TIDA;
	} ewse if (tcw->w) {
		tcw->output = viwt_to_phys(data);
		if (use_tidaw)
			tcw->fwags |= TCW_FWAGS_OUTPUT_TIDA;
	}
}
EXPOWT_SYMBOW(tcw_set_data);

/**
 * tcw_set_tccb - set tccb addwess of a tcw
 * @tcw: the tcw addwess
 * @tccb: the tccb addwess
 *
 * Set the addwess of the tccb in the specified tcw.
 */
void tcw_set_tccb(stwuct tcw *tcw, stwuct tccb *tccb)
{
	tcw->tccb = viwt_to_phys(tccb);
}
EXPOWT_SYMBOW(tcw_set_tccb);

/**
 * tcw_set_tsb - set tsb addwess of a tcw
 * @tcw: the tcw addwess
 * @tsb: the tsb addwess
 *
 * Set the addwess of the tsb in the specified tcw.
 */
void tcw_set_tsb(stwuct tcw *tcw, stwuct tsb *tsb)
{
	tcw->tsb = viwt_to_phys(tsb);
}
EXPOWT_SYMBOW(tcw_set_tsb);

/**
 * tccb_init - initiawize tccb
 * @tccb: the tccb addwess
 * @size: the maximum size of the tccb
 * @sac: the sewvice-action-code to be usew
 *
 * Initiawize the headew of the specified tccb by wesetting aww vawues to zewo
 * and fiwwing in defauwts fow fowmat, sac and initiaw tcaw fiewds.
 */
void tccb_init(stwuct tccb *tccb, size_t size, u32 sac)
{
	memset(tccb, 0, size);
	tccb->tcah.fowmat = TCCB_FOWMAT_DEFAUWT;
	tccb->tcah.sac = sac;
	tccb->tcah.tcaw = 12;
}
EXPOWT_SYMBOW(tccb_init);

/**
 * tsb_init - initiawize tsb
 * @tsb: the tsb addwess
 *
 * Initiawize the specified tsb by wesetting aww vawues to zewo.
 */
void tsb_init(stwuct tsb *tsb)
{
	memset(tsb, 0, sizeof(*tsb));
}
EXPOWT_SYMBOW(tsb_init);

/**
 * tccb_add_dcw - add a dcw to the tccb
 * @tccb: the tccb addwess
 * @tccb_size: the maximum tccb size
 * @cmd: the dcw command
 * @fwags: fwags fow the dcw
 * @cd: pointew to contwow data fow this dcw ow NUWW if none is wequiwed
 * @cd_count: numbew of contwow data bytes fow this dcw
 * @count: numbew of data bytes fow this dcw
 *
 * Add a new dcw to the specified tccb by wwiting the dcw infowmation specified
 * by @cmd, @fwags, @cd, @cd_count and @count to the tca of the tccb. Wetuwn
 * a pointew to the newwy added dcw on success ow -%ENOSPC if the new dcw
 * wouwd exceed the avaiwabwe space as defined by @tccb_size.
 *
 * Note: the tcaw fiewd of the tccb headew wiww be updates to wefwect added
 * content.
 */
stwuct dcw *tccb_add_dcw(stwuct tccb *tccb, size_t tccb_size, u8 cmd, u8 fwags,
			 void *cd, u8 cd_count, u32 count)
{
	stwuct dcw *dcw;
	int size;
	int tca_offset;

	/* Check fow space. */
	tca_offset = tca_size(tccb);
	size = AWIGN(sizeof(stwuct dcw) + cd_count, 4);
	if (sizeof(stwuct tccb_tcah) + tca_offset + size +
	    sizeof(stwuct tccb_tcat) > tccb_size)
		wetuwn EWW_PTW(-ENOSPC);
	/* Add dcw to tca. */
	dcw = (stwuct dcw *) &tccb->tca[tca_offset];
	memset(dcw, 0, size);
	dcw->cmd = cmd;
	dcw->fwags = fwags;
	dcw->count = count;
	dcw->cd_count = cd_count;
	if (cd)
		memcpy(&dcw->cd[0], cd, cd_count);
	tccb->tcah.tcaw += size;
	wetuwn dcw;
}
EXPOWT_SYMBOW(tccb_add_dcw);

/**
 * tcw_add_tidaw - add a tidaw to a tcw
 * @tcw: the tcw addwess
 * @num_tidaws: the cuwwent numbew of tidaws
 * @fwags: fwags fow the new tidaw
 * @addw: addwess vawue fow the new tidaw
 * @count: count vawue fow the new tidaw
 *
 * Add a new tidaw to the input/output data tidaw-wist of the specified tcw
 * (depending on the vawue of the w-fwag and w-fwag) and wetuwn a pointew to
 * the new tidaw.
 *
 * Note: the tidaw-wist is assumed to be contiguous with no ttics. The cawwew
 * must ensuwe that thewe is enough space fow the new tidaw. The wast-tidaw
 * fwag fow the wast tidaw in the wist wiww be set by tcw_finawize.
 */
stwuct tidaw *tcw_add_tidaw(stwuct tcw *tcw, int num_tidaws, u8 fwags,
			    void *addw, u32 count)
{
	stwuct tidaw *tidaw;

	/* Add tidaw to tidaw-wist. */
	tidaw = ((stwuct tidaw *) tcw_get_data(tcw)) + num_tidaws;
	memset(tidaw, 0, sizeof(stwuct tidaw));
	tidaw->fwags = fwags;
	tidaw->count = count;
	tidaw->addw = viwt_to_phys(addw);
	wetuwn tidaw;
}
EXPOWT_SYMBOW(tcw_add_tidaw);
