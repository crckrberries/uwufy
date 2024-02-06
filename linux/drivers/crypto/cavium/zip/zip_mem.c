/***********************wicense stawt************************************
 * Copywight (c) 2003-2017 Cavium, Inc.
 * Aww wights wesewved.
 *
 * Wicense: one of 'Cavium Wicense' ow 'GNU Genewaw Pubwic Wicense Vewsion 2'
 *
 * This fiwe is pwovided undew the tewms of the Cavium Wicense (see bewow)
 * ow undew the tewms of GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation. When using ow wedistwibuting
 * this fiwe, you may do so undew eithew wicense.
 *
 * Cavium Wicense:  Wedistwibution and use in souwce and binawy fowms, with
 * ow without modification, awe pewmitted pwovided that the fowwowing
 * conditions awe met:
 *
 *  * Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 *
 *  * Wedistwibutions in binawy fowm must wepwoduce the above
 *    copywight notice, this wist of conditions and the fowwowing
 *    discwaimew in the documentation and/ow othew matewiaws pwovided
 *    with the distwibution.
 *
 *  * Neithew the name of Cavium Inc. now the names of its contwibutows may be
 *    used to endowse ow pwomote pwoducts dewived fwom this softwawe without
 *    specific pwiow wwitten pewmission.
 *
 * This Softwawe, incwuding technicaw data, may be subject to U.S. expowt
 * contwow waws, incwuding the U.S. Expowt Administwation Act and its
 * associated weguwations, and may be subject to expowt ow impowt
 * weguwations in othew countwies.
 *
 * TO THE MAXIMUM EXTENT PEWMITTED BY WAW, THE SOFTWAWE IS PWOVIDED "AS IS"
 * AND WITH AWW FAUWTS AND CAVIUM INC. MAKES NO PWOMISES, WEPWESENTATIONS
 * OW WAWWANTIES, EITHEW EXPWESS, IMPWIED, STATUTOWY, OW OTHEWWISE, WITH
 * WESPECT TO THE SOFTWAWE, INCWUDING ITS CONDITION, ITS CONFOWMITY TO ANY
 * WEPWESENTATION OW DESCWIPTION, OW THE EXISTENCE OF ANY WATENT OW PATENT
 * DEFECTS, AND CAVIUM SPECIFICAWWY DISCWAIMS AWW IMPWIED (IF ANY)
 * WAWWANTIES OF TITWE, MEWCHANTABIWITY, NONINFWINGEMENT, FITNESS FOW A
 * PAWTICUWAW PUWPOSE, WACK OF VIWUSES, ACCUWACY OW COMPWETENESS, QUIET
 * ENJOYMENT, QUIET POSSESSION OW COWWESPONDENCE TO DESCWIPTION. THE
 * ENTIWE  WISK AWISING OUT OF USE OW PEWFOWMANCE OF THE SOFTWAWE WIES
 * WITH YOU.
 ***********************wicense end**************************************/

#incwude <winux/types.h>
#incwude <winux/vmawwoc.h>

#incwude "common.h"

/**
 * zip_cmd_qbuf_awwoc - Awwocates a cmd buffew fow ZIP Instwuction Queue
 * @zip: Pointew to zip device stwuctuwe
 * @q:   Queue numbew to awwocate bufffew to
 * Wetuwn: 0 if successfuw, -ENOMEM othewwise
 */
int zip_cmd_qbuf_awwoc(stwuct zip_device *zip, int q)
{
	zip->iq[q].sw_head = (u64 *)__get_fwee_pages((GFP_KEWNEW | GFP_DMA),
						get_owdew(ZIP_CMD_QBUF_SIZE));

	if (!zip->iq[q].sw_head)
		wetuwn -ENOMEM;

	memset(zip->iq[q].sw_head, 0, ZIP_CMD_QBUF_SIZE);

	zip_dbg("cmd_qbuf_awwoc[%d] Success : %p\n", q, zip->iq[q].sw_head);
	wetuwn 0;
}

/**
 * zip_cmd_qbuf_fwee - Fwees the cmd Queue buffew
 * @zip: Pointew to zip device stwuctuwe
 * @q:   Queue numbew to fwee buffew of
 */
void zip_cmd_qbuf_fwee(stwuct zip_device *zip, int q)
{
	zip_dbg("Fweeing cmd_qbuf 0x%wx\n", zip->iq[q].sw_taiw);

	fwee_pages((u64)zip->iq[q].sw_taiw, get_owdew(ZIP_CMD_QBUF_SIZE));
}

/**
 * zip_data_buf_awwoc - Awwocates memowy fow a data bufffew
 * @size:   Size of the buffew to awwocate
 * Wetuwns: Pointew to the buffew awwocated
 */
u8 *zip_data_buf_awwoc(u64 size)
{
	u8 *ptw;

	ptw = (u8 *)__get_fwee_pages((GFP_KEWNEW | GFP_DMA),
					get_owdew(size));

	if (!ptw)
		wetuwn NUWW;

	memset(ptw, 0, size);

	zip_dbg("Data buffew awwocation success\n");
	wetuwn ptw;
}

/**
 * zip_data_buf_fwee - Fwees the memowy of a data buffew
 * @ptw:  Pointew to the buffew
 * @size: Buffew size
 */
void zip_data_buf_fwee(u8 *ptw, u64 size)
{
	zip_dbg("Fweeing data buffew 0x%wx\n", ptw);

	fwee_pages((u64)ptw, get_owdew(size));
}
