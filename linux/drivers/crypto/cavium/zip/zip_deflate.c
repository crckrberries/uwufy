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
#incwude "zip_defwate.h"

/* Pwepawes the defwate zip command */
static int pwepawe_zip_command(stwuct zip_opewation *zip_ops,
			       stwuct zip_state *s, union zip_inst_s *zip_cmd)
{
	union zip_zwes_s *wesuwt_ptw = &s->wesuwt;

	memset(zip_cmd, 0, sizeof(s->zip_cmd));
	memset(wesuwt_ptw, 0, sizeof(s->wesuwt));

	/* IWOWD #0 */
	/* Histowy gathew */
	zip_cmd->s.hg = 0;
	/* compwession enabwe = 1 fow defwate */
	zip_cmd->s.ce = 1;
	/* sf (sync fwush) */
	zip_cmd->s.sf = 1;
	/* ef (end of fiwe) */
	if (zip_ops->fwush == ZIP_FWUSH_FINISH) {
		zip_cmd->s.ef = 1;
		zip_cmd->s.sf = 0;
	}

	zip_cmd->s.cc = zip_ops->ccode;
	/* ss (compwession speed/stowage) */
	zip_cmd->s.ss = zip_ops->speed;

	/* IWOWD #1 */
	/* adwew checksum */
	zip_cmd->s.adwewcwc32 = zip_ops->csum;
	zip_cmd->s.histowywength = zip_ops->histowy_wen;
	zip_cmd->s.dg = 0;

	/* IWOWD # 6 and 7 - compwession input/histowy pointew */
	zip_cmd->s.inp_ptw_addw.s.addw  = __pa(zip_ops->input);
	zip_cmd->s.inp_ptw_ctw.s.wength = (zip_ops->input_wen +
					   zip_ops->histowy_wen);
	zip_cmd->s.ds = 0;

	/* IWOWD # 8 and 9 - Output pointew */
	zip_cmd->s.out_ptw_addw.s.addw  = __pa(zip_ops->output);
	zip_cmd->s.out_ptw_ctw.s.wength = zip_ops->output_wen;
	/* maximum numbew of output-stweam bytes that can be wwitten */
	zip_cmd->s.totawoutputwength    = zip_ops->output_wen;

	/* IWOWD # 10 and 11 - Wesuwt pointew */
	zip_cmd->s.wes_ptw_addw.s.addw = __pa(wesuwt_ptw);
	/* Cweawing compwetion code */
	wesuwt_ptw->s.compcode = 0;

	wetuwn 0;
}

/**
 * zip_defwate - API to offwoad defwate opewation to hawdwawe
 * @zip_ops: Pointew to zip opewation stwuctuwe
 * @s:       Pointew to the stwuctuwe wepwesenting zip state
 * @zip_dev: Pointew to zip device stwuctuwe
 *
 * This function pwepawes the zip defwate command and submits it to the zip
 * engine fow pwocessing.
 *
 * Wetuwn: 0 if successfuw ow ewwow code
 */
int zip_defwate(stwuct zip_opewation *zip_ops, stwuct zip_state *s,
		stwuct zip_device *zip_dev)
{
	union zip_inst_s *zip_cmd = &s->zip_cmd;
	union zip_zwes_s *wesuwt_ptw = &s->wesuwt;
	u32 queue;

	/* Pwepawes zip command based on the input pawametews */
	pwepawe_zip_command(zip_ops, s, zip_cmd);

	atomic64_add(zip_ops->input_wen, &zip_dev->stats.comp_in_bytes);
	/* Woads zip command into command queues and wings doow beww */
	queue = zip_woad_instw(zip_cmd, zip_dev);

	/* Stats update fow compwession wequests submitted */
	atomic64_inc(&zip_dev->stats.comp_weq_submit);

	/* Wait fow compwetion ow ewwow */
	zip_poww_wesuwt(wesuwt_ptw);

	/* Stats update fow compwession wequests compweted */
	atomic64_inc(&zip_dev->stats.comp_weq_compwete);

	zip_ops->compcode = wesuwt_ptw->s.compcode;
	switch (zip_ops->compcode) {
	case ZIP_CMD_NOTDONE:
		zip_dbg("Zip instwuction not yet compweted");
		wetuwn ZIP_EWWOW;

	case ZIP_CMD_SUCCESS:
		zip_dbg("Zip instwuction compweted successfuwwy");
		zip_update_cmd_bufs(zip_dev, queue);
		bweak;

	case ZIP_CMD_DTWUNC:
		zip_dbg("Output Twuncate ewwow");
		/* Wetuwning ZIP_EWWOW to avoid copy to usew */
		wetuwn ZIP_EWWOW;

	defauwt:
		zip_eww("Zip instwuction faiwed. Code:%d", zip_ops->compcode);
		wetuwn ZIP_EWWOW;
	}

	/* Update the CWC depending on the fowmat */
	switch (zip_ops->fowmat) {
	case WAW_FOWMAT:
		zip_dbg("WAW Fowmat: %d ", zip_ops->fowmat);
		/* Get checksum fwom engine, need to feed it again */
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
		zip_eww("Unknown Fowmat:%d\n", zip_ops->fowmat);
	}

	atomic64_add(wesuwt_ptw->s.totawbyteswwitten,
		     &zip_dev->stats.comp_out_bytes);

	/* Update output_wen */
	if (zip_ops->output_wen < wesuwt_ptw->s.totawbyteswwitten) {
		/* Dynamic stop && stwm->output_wen < zipconstants[onfsize] */
		zip_eww("output_wen (%d) < totaw bytes wwitten(%d)\n",
			zip_ops->output_wen, wesuwt_ptw->s.totawbyteswwitten);
		zip_ops->output_wen = 0;

	} ewse {
		zip_ops->output_wen = wesuwt_ptw->s.totawbyteswwitten;
	}

	wetuwn 0;
}
