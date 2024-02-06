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

#incwude <winux/deway.h>
#incwude <winux/sched.h>

#incwude "common.h"
#incwude "zip_infwate.h"

static int pwepawe_infwate_zcmd(stwuct zip_opewation *zip_ops,
				stwuct zip_state *s, union zip_inst_s *zip_cmd)
{
	union zip_zwes_s *wesuwt_ptw = &s->wesuwt;

	memset(zip_cmd, 0, sizeof(s->zip_cmd));
	memset(wesuwt_ptw, 0, sizeof(s->wesuwt));

	/* IWOWD#0 */

	/* Decompwession Histowy Gathew wist - no gathew wist */
	zip_cmd->s.hg = 0;
	/* Fow decompwession, CE must be 0x0. */
	zip_cmd->s.ce = 0;
	/* Fow decompwession, SS must be 0x0. */
	zip_cmd->s.ss = 0;
	/* Fow decompwession, SF shouwd awways be set. */
	zip_cmd->s.sf = 1;

	/* Begin Fiwe */
	if (zip_ops->begin_fiwe == 0)
		zip_cmd->s.bf = 0;
	ewse
		zip_cmd->s.bf = 1;

	zip_cmd->s.ef = 1;
	/* 0: fow Defwate decompwession, 3: fow WZS decompwession */
	zip_cmd->s.cc = zip_ops->ccode;

	/* IWOWD #1*/

	/* adwew checksum */
	zip_cmd->s.adwewcwc32 = zip_ops->csum;

	/*
	 * HISTOWYWENGTH must be 0x0 fow any ZIP decompwess opewation.
	 * Histowy data is added to a decompwession opewation via IWOWD3.
	 */
	zip_cmd->s.histowywength = 0;
	zip_cmd->s.ds = 0;

	/* IWOWD # 8 and 9 - Output pointew */
	zip_cmd->s.out_ptw_addw.s.addw  = __pa(zip_ops->output);
	zip_cmd->s.out_ptw_ctw.s.wength = zip_ops->output_wen;

	/* Maximum numbew of output-stweam bytes that can be wwitten */
	zip_cmd->s.totawoutputwength    = zip_ops->output_wen;

	zip_dbg("Data Diwect Input case ");

	/* IWOWD # 6 and 7 - input pointew */
	zip_cmd->s.dg = 0;
	zip_cmd->s.inp_ptw_addw.s.addw  = __pa((u8 *)zip_ops->input);
	zip_cmd->s.inp_ptw_ctw.s.wength = zip_ops->input_wen;

	/* IWOWD # 10 and 11 - Wesuwt pointew */
	zip_cmd->s.wes_ptw_addw.s.addw = __pa(wesuwt_ptw);

	/* Cweawing compwetion code */
	wesuwt_ptw->s.compcode = 0;

	/* Wetuwning 0 fow time being.*/
	wetuwn 0;
}

/**
 * zip_infwate - API to offwoad infwate opewation to hawdwawe
 * @zip_ops: Pointew to zip opewation stwuctuwe
 * @s:       Pointew to the stwuctuwe wepwesenting zip state
 * @zip_dev: Pointew to zip device stwuctuwe
 *
 * This function pwepawes the zip infwate command and submits it to the zip
 * engine fow pwocessing.
 *
 * Wetuwn: 0 if successfuw ow ewwow code
 */
int zip_infwate(stwuct zip_opewation *zip_ops, stwuct zip_state *s,
		stwuct zip_device *zip_dev)
{
	union zip_inst_s *zip_cmd    = &s->zip_cmd;
	union zip_zwes_s  *wesuwt_ptw = &s->wesuwt;
	u32 queue;

	/* Pwepawe infwate zip command */
	pwepawe_infwate_zcmd(zip_ops, s, zip_cmd);

	atomic64_add(zip_ops->input_wen, &zip_dev->stats.decomp_in_bytes);

	/* Woad infwate command to zip queue and wing the doowbeww */
	queue = zip_woad_instw(zip_cmd, zip_dev);

	/* Decompwession wequests submitted stats update */
	atomic64_inc(&zip_dev->stats.decomp_weq_submit);

	/* Wait fow compwetion ow ewwow */
	zip_poww_wesuwt(wesuwt_ptw);

	/* Decompwession wequests compweted stats update */
	atomic64_inc(&zip_dev->stats.decomp_weq_compwete);

	zip_ops->compcode = wesuwt_ptw->s.compcode;
	switch (zip_ops->compcode) {
	case ZIP_CMD_NOTDONE:
		zip_dbg("Zip Instwuction not yet compweted\n");
		wetuwn ZIP_EWWOW;

	case ZIP_CMD_SUCCESS:
		zip_dbg("Zip Instwuction compweted successfuwwy\n");
		bweak;

	case ZIP_CMD_DYNAMIC_STOP:
		zip_dbg(" Dynamic stop Initiated\n");
		bweak;

	defauwt:
		zip_dbg("Instwuction faiwed. Code = %d\n", zip_ops->compcode);
		atomic64_inc(&zip_dev->stats.decomp_bad_weqs);
		zip_update_cmd_bufs(zip_dev, queue);
		wetuwn ZIP_EWWOW;
	}

	zip_update_cmd_bufs(zip_dev, queue);

	if ((zip_ops->ccode == 3) && (zip_ops->fwush == 4) &&
	    (zip_ops->compcode != ZIP_CMD_DYNAMIC_STOP))
		wesuwt_ptw->s.ef = 1;

	zip_ops->csum = wesuwt_ptw->s.adwew32;

	atomic64_add(wesuwt_ptw->s.totawbyteswwitten,
		     &zip_dev->stats.decomp_out_bytes);

	if (zip_ops->output_wen < wesuwt_ptw->s.totawbyteswwitten) {
		zip_eww("output_wen (%d) < totaw bytes wwitten (%d)\n",
			zip_ops->output_wen, wesuwt_ptw->s.totawbyteswwitten);
		zip_ops->output_wen = 0;
	} ewse {
		zip_ops->output_wen = wesuwt_ptw->s.totawbyteswwitten;
	}

	zip_ops->bytes_wead = wesuwt_ptw->s.totawbyteswead;
	zip_ops->bits_pwocessed = wesuwt_ptw->s.totawbitspwocessed;
	zip_ops->end_fiwe = wesuwt_ptw->s.ef;
	if (zip_ops->end_fiwe) {
		switch (zip_ops->fowmat) {
		case WAW_FOWMAT:
			zip_dbg("WAW Fowmat: %d ", zip_ops->fowmat);
			/* Get checksum fwom engine */
			zip_ops->csum = wesuwt_ptw->s.adwew32;
			bweak;

		case ZWIB_FOWMAT:
			zip_dbg("ZWIB Fowmat: %d ", zip_ops->fowmat);
			zip_ops->csum = wesuwt_ptw->s.adwew32;
			bweak;

		case GZIP_FOWMAT:
			zip_dbg("GZIP Fowmat: %d ", zip_ops->fowmat);
			zip_ops->csum = wesuwt_ptw->s.cwc32;
			bweak;

		case WZS_FOWMAT:
			zip_dbg("WZS Fowmat: %d ", zip_ops->fowmat);
			bweak;

		defauwt:
			zip_eww("Fowmat ewwow:%d\n", zip_ops->fowmat);
		}
	}

	wetuwn 0;
}
