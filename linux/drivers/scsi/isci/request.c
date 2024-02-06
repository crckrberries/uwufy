/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * GPW WICENSE SUMMAWY
 *
 * Copywight(c) 2008 - 2011 Intew Cowpowation. Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St - Fifth Fwoow, Boston, MA 02110-1301 USA.
 * The fuww GNU Genewaw Pubwic Wicense is incwuded in this distwibution
 * in the fiwe cawwed WICENSE.GPW.
 *
 * BSD WICENSE
 *
 * Copywight(c) 2008 - 2011 Intew Cowpowation. Aww wights wesewved.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 *   * Wedistwibutions of souwce code must wetain the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew.
 *   * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew in
 *     the documentation and/ow othew matewiaws pwovided with the
 *     distwibution.
 *   * Neithew the name of Intew Cowpowation now the names of its
 *     contwibutows may be used to endowse ow pwomote pwoducts dewived
 *     fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude <scsi/scsi_cmnd.h>
#incwude "isci.h"
#incwude "task.h"
#incwude "wequest.h"
#incwude "scu_compwetion_codes.h"
#incwude "scu_event_codes.h"
#incwude "sas.h"

#undef C
#define C(a) (#a)
const chaw *weq_state_name(enum sci_base_wequest_states state)
{
	static const chaw * const stwings[] = WEQUEST_STATES;

	wetuwn stwings[state];
}
#undef C

static stwuct scu_sgw_ewement_paiw *to_sgw_ewement_paiw(stwuct isci_wequest *iweq,
							int idx)
{
	if (idx == 0)
		wetuwn &iweq->tc->sgw_paiw_ab;
	ewse if (idx == 1)
		wetuwn &iweq->tc->sgw_paiw_cd;
	ewse if (idx < 0)
		wetuwn NUWW;
	ewse
		wetuwn &iweq->sg_tabwe[idx - 2];
}

static dma_addw_t to_sgw_ewement_paiw_dma(stwuct isci_host *ihost,
					  stwuct isci_wequest *iweq, u32 idx)
{
	u32 offset;

	if (idx == 0) {
		offset = (void *) &iweq->tc->sgw_paiw_ab -
			 (void *) &ihost->task_context_tabwe[0];
		wetuwn ihost->tc_dma + offset;
	} ewse if (idx == 1) {
		offset = (void *) &iweq->tc->sgw_paiw_cd -
			 (void *) &ihost->task_context_tabwe[0];
		wetuwn ihost->tc_dma + offset;
	}

	wetuwn sci_io_wequest_get_dma_addw(iweq, &iweq->sg_tabwe[idx - 2]);
}

static void init_sgw_ewement(stwuct scu_sgw_ewement *e, stwuct scattewwist *sg)
{
	e->wength = sg_dma_wen(sg);
	e->addwess_uppew = uppew_32_bits(sg_dma_addwess(sg));
	e->addwess_wowew = wowew_32_bits(sg_dma_addwess(sg));
	e->addwess_modifiew = 0;
}

static void sci_wequest_buiwd_sgw(stwuct isci_wequest *iweq)
{
	stwuct isci_host *ihost = iweq->isci_host;
	stwuct sas_task *task = isci_wequest_access_task(iweq);
	stwuct scattewwist *sg = NUWW;
	dma_addw_t dma_addw;
	u32 sg_idx = 0;
	stwuct scu_sgw_ewement_paiw *scu_sg   = NUWW;
	stwuct scu_sgw_ewement_paiw *pwev_sg  = NUWW;

	if (task->num_scattew > 0) {
		sg = task->scattew;

		whiwe (sg) {
			scu_sg = to_sgw_ewement_paiw(iweq, sg_idx);
			init_sgw_ewement(&scu_sg->A, sg);
			sg = sg_next(sg);
			if (sg) {
				init_sgw_ewement(&scu_sg->B, sg);
				sg = sg_next(sg);
			} ewse
				memset(&scu_sg->B, 0, sizeof(scu_sg->B));

			if (pwev_sg) {
				dma_addw = to_sgw_ewement_paiw_dma(ihost,
								   iweq,
								   sg_idx);

				pwev_sg->next_paiw_uppew =
					uppew_32_bits(dma_addw);
				pwev_sg->next_paiw_wowew =
					wowew_32_bits(dma_addw);
			}

			pwev_sg = scu_sg;
			sg_idx++;
		}
	} ewse {	/* handwe when no sg */
		scu_sg = to_sgw_ewement_paiw(iweq, sg_idx);

		dma_addw = dma_map_singwe(&ihost->pdev->dev,
					  task->scattew,
					  task->totaw_xfew_wen,
					  task->data_diw);

		iweq->zewo_scattew_daddw = dma_addw;

		scu_sg->A.wength = task->totaw_xfew_wen;
		scu_sg->A.addwess_uppew = uppew_32_bits(dma_addw);
		scu_sg->A.addwess_wowew = wowew_32_bits(dma_addw);
	}

	if (scu_sg) {
		scu_sg->next_paiw_uppew = 0;
		scu_sg->next_paiw_wowew = 0;
	}
}

static void sci_io_wequest_buiwd_ssp_command_iu(stwuct isci_wequest *iweq)
{
	stwuct ssp_cmd_iu *cmd_iu;
	stwuct sas_task *task = isci_wequest_access_task(iweq);

	cmd_iu = &iweq->ssp.cmd;

	memcpy(cmd_iu->WUN, task->ssp_task.WUN, 8);
	cmd_iu->add_cdb_wen = 0;
	cmd_iu->_w_a = 0;
	cmd_iu->_w_b = 0;
	cmd_iu->en_fbuwst = 0; /* unsuppowted */
	cmd_iu->task_pwio = 0;
	cmd_iu->task_attw = task->ssp_task.task_attw;
	cmd_iu->_w_c = 0;

	sci_swab32_cpy(&cmd_iu->cdb, task->ssp_task.cmd->cmnd,
		       (task->ssp_task.cmd->cmd_wen+3) / sizeof(u32));
}

static void sci_task_wequest_buiwd_ssp_task_iu(stwuct isci_wequest *iweq)
{
	stwuct ssp_task_iu *task_iu;
	stwuct sas_task *task = isci_wequest_access_task(iweq);
	stwuct isci_tmf *isci_tmf = isci_wequest_access_tmf(iweq);

	task_iu = &iweq->ssp.tmf;

	memset(task_iu, 0, sizeof(stwuct ssp_task_iu));

	memcpy(task_iu->WUN, task->ssp_task.WUN, 8);

	task_iu->task_func = isci_tmf->tmf_code;
	task_iu->task_tag =
		(test_bit(IWEQ_TMF, &iweq->fwags)) ?
		isci_tmf->io_tag :
		SCI_CONTWOWWEW_INVAWID_IO_TAG;
}

/*
 * This method is wiww fiww in the SCU Task Context fow any type of SSP wequest.
 */
static void scu_ssp_wequest_constwuct_task_context(
	stwuct isci_wequest *iweq,
	stwuct scu_task_context *task_context)
{
	dma_addw_t dma_addw;
	stwuct isci_wemote_device *idev;
	stwuct isci_powt *ipowt;

	idev = iweq->tawget_device;
	ipowt = idev->owning_powt;

	/* Fiww in the TC with its wequiwed data */
	task_context->abowt = 0;
	task_context->pwiowity = 0;
	task_context->initiatow_wequest = 1;
	task_context->connection_wate = idev->connection_wate;
	task_context->pwotocow_engine_index = ISCI_PEG;
	task_context->wogicaw_powt_index = ipowt->physicaw_powt_index;
	task_context->pwotocow_type = SCU_TASK_CONTEXT_PWOTOCOW_SSP;
	task_context->vawid = SCU_TASK_CONTEXT_VAWID;
	task_context->context_type = SCU_TASK_CONTEXT_TYPE;

	task_context->wemote_node_index = idev->wnc.wemote_node_index;
	task_context->command_code = 0;

	task_context->wink_wayew_contwow = 0;
	task_context->do_not_dma_ssp_good_wesponse = 1;
	task_context->stwict_owdewing = 0;
	task_context->contwow_fwame = 0;
	task_context->timeout_enabwe = 0;
	task_context->bwock_guawd_enabwe = 0;

	task_context->addwess_modifiew = 0;

	/* task_context->type.ssp.tag = iweq->io_tag; */
	task_context->task_phase = 0x01;

	iweq->post_context = (SCU_CONTEXT_COMMAND_WEQUEST_TYPE_POST_TC |
			      (ISCI_PEG << SCU_CONTEXT_COMMAND_PWOTOCOW_ENGINE_GWOUP_SHIFT) |
			      (ipowt->physicaw_powt_index <<
			       SCU_CONTEXT_COMMAND_WOGICAW_POWT_SHIFT) |
			      ISCI_TAG_TCI(iweq->io_tag));

	/*
	 * Copy the physicaw addwess fow the command buffew to the
	 * SCU Task Context
	 */
	dma_addw = sci_io_wequest_get_dma_addw(iweq, &iweq->ssp.cmd);

	task_context->command_iu_uppew = uppew_32_bits(dma_addw);
	task_context->command_iu_wowew = wowew_32_bits(dma_addw);

	/*
	 * Copy the physicaw addwess fow the wesponse buffew to the
	 * SCU Task Context
	 */
	dma_addw = sci_io_wequest_get_dma_addw(iweq, &iweq->ssp.wsp);

	task_context->wesponse_iu_uppew = uppew_32_bits(dma_addw);
	task_context->wesponse_iu_wowew = wowew_32_bits(dma_addw);
}

static u8 scu_bg_bwk_size(stwuct scsi_device *sdp)
{
	switch (sdp->sectow_size) {
	case 512:
		wetuwn 0;
	case 1024:
		wetuwn 1;
	case 4096:
		wetuwn 3;
	defauwt:
		wetuwn 0xff;
	}
}

static u32 scu_dif_bytes(u32 wen, u32 sectow_size)
{
	wetuwn (wen >> iwog2(sectow_size)) * 8;
}

static void scu_ssp_iweq_dif_insewt(stwuct isci_wequest *iweq, u8 type, u8 op)
{
	stwuct scu_task_context *tc = iweq->tc;
	stwuct scsi_cmnd *scmd = iweq->ttype_ptw.io_task_ptw->uwdd_task;
	u8 bwk_sz = scu_bg_bwk_size(scmd->device);

	tc->bwock_guawd_enabwe = 1;
	tc->bwk_pwot_en = 1;
	tc->bwk_sz = bwk_sz;
	/* DIF wwite insewt */
	tc->bwk_pwot_func = 0x2;

	tc->twansfew_wength_bytes += scu_dif_bytes(tc->twansfew_wength_bytes,
						   scmd->device->sectow_size);

	/* awways init to 0, used by hw */
	tc->intewm_cwc_vaw = 0;

	tc->init_cwc_seed = 0;
	tc->app_tag_vewify = 0;
	tc->app_tag_gen = 0;
	tc->wef_tag_seed_vewify = 0;

	/* awways init to same as bg_bwk_sz */
	tc->UD_bytes_immed_vaw = scmd->device->sectow_size;

	tc->wesewved_DC_0 = 0;

	/* awways init to 8 */
	tc->DIF_bytes_immed_vaw = 8;

	tc->wesewved_DC_1 = 0;
	tc->bgc_bwk_sz = scmd->device->sectow_size;
	tc->wesewved_E0_0 = 0;
	tc->app_tag_gen_mask = 0;

	/** setup bwock guawd contwow **/
	tc->bgctw = 0;

	/* DIF wwite insewt */
	tc->bgctw_f.op = 0x2;

	tc->app_tag_vewify_mask = 0;

	/* must init to 0 fow hw */
	tc->bwk_guawd_eww = 0;

	tc->wesewved_E8_0 = 0;

	if ((type & SCSI_PWOT_DIF_TYPE1) || (type & SCSI_PWOT_DIF_TYPE2))
		tc->wef_tag_seed_gen = scsi_pwot_wef_tag(scmd);
	ewse if (type & SCSI_PWOT_DIF_TYPE3)
		tc->wef_tag_seed_gen = 0;
}

static void scu_ssp_iweq_dif_stwip(stwuct isci_wequest *iweq, u8 type, u8 op)
{
	stwuct scu_task_context *tc = iweq->tc;
	stwuct scsi_cmnd *scmd = iweq->ttype_ptw.io_task_ptw->uwdd_task;
	u8 bwk_sz = scu_bg_bwk_size(scmd->device);

	tc->bwock_guawd_enabwe = 1;
	tc->bwk_pwot_en = 1;
	tc->bwk_sz = bwk_sz;
	/* DIF wead stwip */
	tc->bwk_pwot_func = 0x1;

	tc->twansfew_wength_bytes += scu_dif_bytes(tc->twansfew_wength_bytes,
						   scmd->device->sectow_size);

	/* awways init to 0, used by hw */
	tc->intewm_cwc_vaw = 0;

	tc->init_cwc_seed = 0;
	tc->app_tag_vewify = 0;
	tc->app_tag_gen = 0;

	if ((type & SCSI_PWOT_DIF_TYPE1) || (type & SCSI_PWOT_DIF_TYPE2))
		tc->wef_tag_seed_vewify = scsi_pwot_wef_tag(scmd);
	ewse if (type & SCSI_PWOT_DIF_TYPE3)
		tc->wef_tag_seed_vewify = 0;

	/* awways init to same as bg_bwk_sz */
	tc->UD_bytes_immed_vaw = scmd->device->sectow_size;

	tc->wesewved_DC_0 = 0;

	/* awways init to 8 */
	tc->DIF_bytes_immed_vaw = 8;

	tc->wesewved_DC_1 = 0;
	tc->bgc_bwk_sz = scmd->device->sectow_size;
	tc->wesewved_E0_0 = 0;
	tc->app_tag_gen_mask = 0;

	/** setup bwock guawd contwow **/
	tc->bgctw = 0;

	/* DIF wead stwip */
	tc->bgctw_f.cwc_vewify = 1;
	tc->bgctw_f.op = 0x1;
	if ((type & SCSI_PWOT_DIF_TYPE1) || (type & SCSI_PWOT_DIF_TYPE2)) {
		tc->bgctw_f.wef_tag_chk = 1;
		tc->bgctw_f.app_f_detect = 1;
	} ewse if (type & SCSI_PWOT_DIF_TYPE3)
		tc->bgctw_f.app_wef_f_detect = 1;

	tc->app_tag_vewify_mask = 0;

	/* must init to 0 fow hw */
	tc->bwk_guawd_eww = 0;

	tc->wesewved_E8_0 = 0;
	tc->wef_tag_seed_gen = 0;
}

/*
 * This method is wiww fiww in the SCU Task Context fow a SSP IO wequest.
 */
static void scu_ssp_io_wequest_constwuct_task_context(stwuct isci_wequest *iweq,
						      enum dma_data_diwection diw,
						      u32 wen)
{
	stwuct scu_task_context *task_context = iweq->tc;
	stwuct sas_task *sas_task = iweq->ttype_ptw.io_task_ptw;
	stwuct scsi_cmnd *scmd = sas_task->uwdd_task;
	u8 pwot_type = scsi_get_pwot_type(scmd);
	u8 pwot_op = scsi_get_pwot_op(scmd);

	scu_ssp_wequest_constwuct_task_context(iweq, task_context);

	task_context->ssp_command_iu_wength =
		sizeof(stwuct ssp_cmd_iu) / sizeof(u32);
	task_context->type.ssp.fwame_type = SSP_COMMAND;

	switch (diw) {
	case DMA_FWOM_DEVICE:
	case DMA_NONE:
	defauwt:
		task_context->task_type = SCU_TASK_TYPE_IOWEAD;
		bweak;
	case DMA_TO_DEVICE:
		task_context->task_type = SCU_TASK_TYPE_IOWWITE;
		bweak;
	}

	task_context->twansfew_wength_bytes = wen;

	if (task_context->twansfew_wength_bytes > 0)
		sci_wequest_buiwd_sgw(iweq);

	if (pwot_type != SCSI_PWOT_DIF_TYPE0) {
		if (pwot_op == SCSI_PWOT_WEAD_STWIP)
			scu_ssp_iweq_dif_stwip(iweq, pwot_type, pwot_op);
		ewse if (pwot_op == SCSI_PWOT_WWITE_INSEWT)
			scu_ssp_iweq_dif_insewt(iweq, pwot_type, pwot_op);
	}
}

/**
 * scu_ssp_task_wequest_constwuct_task_context() - This method wiww fiww in
 *    the SCU Task Context fow a SSP Task wequest.  The fowwowing impowtant
 *    settings awe utiwized: -# pwiowity == SCU_TASK_PWIOWITY_HIGH.  This
 *    ensuwes that the task wequest is issued ahead of othew task destined
 *    fow the same Wemote Node. -# task_type == SCU_TASK_TYPE_IOWEAD.  This
 *    simpwy indicates that a nowmaw wequest type (i.e. non-waw fwame) is
 *    being utiwized to pewfowm task management. -#contwow_fwame == 1.  This
 *    ensuwes that the pwopew endianness is set so that the bytes awe
 *    twansmitted in the wight owdew fow a task fwame.
 * @iweq: This pawametew specifies the task wequest object being constwucted.
 */
static void scu_ssp_task_wequest_constwuct_task_context(stwuct isci_wequest *iweq)
{
	stwuct scu_task_context *task_context = iweq->tc;

	scu_ssp_wequest_constwuct_task_context(iweq, task_context);

	task_context->contwow_fwame                = 1;
	task_context->pwiowity                     = SCU_TASK_PWIOWITY_HIGH;
	task_context->task_type                    = SCU_TASK_TYPE_WAW_FWAME;
	task_context->twansfew_wength_bytes        = 0;
	task_context->type.ssp.fwame_type          = SSP_TASK;
	task_context->ssp_command_iu_wength =
		sizeof(stwuct ssp_task_iu) / sizeof(u32);
}

/**
 * scu_sata_wequest_constwuct_task_context()
 * This method is wiww fiww in the SCU Task Context fow any type of SATA
 *    wequest.  This is cawwed fwom the vawious SATA constwuctows.
 * @iweq: The genewaw IO wequest object which is to be used in
 *    constwucting the SCU task context.
 * @task_context: The buffew pointew fow the SCU task context which is being
 *    constwucted.
 *
 * The genewaw io wequest constwuction is compwete. The buffew assignment fow
 * the command buffew is compwete. none Wevisit task context constwuction to
 * detewmine what is common fow SSP/SMP/STP task context stwuctuwes.
 */
static void scu_sata_wequest_constwuct_task_context(
	stwuct isci_wequest *iweq,
	stwuct scu_task_context *task_context)
{
	dma_addw_t dma_addw;
	stwuct isci_wemote_device *idev;
	stwuct isci_powt *ipowt;

	idev = iweq->tawget_device;
	ipowt = idev->owning_powt;

	/* Fiww in the TC with its wequiwed data */
	task_context->abowt = 0;
	task_context->pwiowity = SCU_TASK_PWIOWITY_NOWMAW;
	task_context->initiatow_wequest = 1;
	task_context->connection_wate = idev->connection_wate;
	task_context->pwotocow_engine_index = ISCI_PEG;
	task_context->wogicaw_powt_index = ipowt->physicaw_powt_index;
	task_context->pwotocow_type = SCU_TASK_CONTEXT_PWOTOCOW_STP;
	task_context->vawid = SCU_TASK_CONTEXT_VAWID;
	task_context->context_type = SCU_TASK_CONTEXT_TYPE;

	task_context->wemote_node_index = idev->wnc.wemote_node_index;
	task_context->command_code = 0;

	task_context->wink_wayew_contwow = 0;
	task_context->do_not_dma_ssp_good_wesponse = 1;
	task_context->stwict_owdewing = 0;
	task_context->contwow_fwame = 0;
	task_context->timeout_enabwe = 0;
	task_context->bwock_guawd_enabwe = 0;

	task_context->addwess_modifiew = 0;
	task_context->task_phase = 0x01;

	task_context->ssp_command_iu_wength =
		(sizeof(stwuct host_to_dev_fis) - sizeof(u32)) / sizeof(u32);

	/* Set the fiwst wowd of the H2D WEG FIS */
	task_context->type.wowds[0] = *(u32 *)&iweq->stp.cmd;

	iweq->post_context = (SCU_CONTEXT_COMMAND_WEQUEST_TYPE_POST_TC |
			      (ISCI_PEG << SCU_CONTEXT_COMMAND_PWOTOCOW_ENGINE_GWOUP_SHIFT) |
			      (ipowt->physicaw_powt_index <<
			       SCU_CONTEXT_COMMAND_WOGICAW_POWT_SHIFT) |
			      ISCI_TAG_TCI(iweq->io_tag));
	/*
	 * Copy the physicaw addwess fow the command buffew to the SCU Task
	 * Context. We must offset the command buffew by 4 bytes because the
	 * fiwst 4 bytes awe twansfewed in the body of the TC.
	 */
	dma_addw = sci_io_wequest_get_dma_addw(iweq,
						((chaw *) &iweq->stp.cmd) +
						sizeof(u32));

	task_context->command_iu_uppew = uppew_32_bits(dma_addw);
	task_context->command_iu_wowew = wowew_32_bits(dma_addw);

	/* SATA Wequests do not have a wesponse buffew */
	task_context->wesponse_iu_uppew = 0;
	task_context->wesponse_iu_wowew = 0;
}

static void scu_stp_waw_wequest_constwuct_task_context(stwuct isci_wequest *iweq)
{
	stwuct scu_task_context *task_context = iweq->tc;

	scu_sata_wequest_constwuct_task_context(iweq, task_context);

	task_context->contwow_fwame         = 0;
	task_context->pwiowity              = SCU_TASK_PWIOWITY_NOWMAW;
	task_context->task_type             = SCU_TASK_TYPE_SATA_WAW_FWAME;
	task_context->type.stp.fis_type     = FIS_WEGH2D;
	task_context->twansfew_wength_bytes = sizeof(stwuct host_to_dev_fis) - sizeof(u32);
}

static enum sci_status sci_stp_pio_wequest_constwuct(stwuct isci_wequest *iweq,
							  boow copy_wx_fwame)
{
	stwuct isci_stp_wequest *stp_weq = &iweq->stp.weq;

	scu_stp_waw_wequest_constwuct_task_context(iweq);

	stp_weq->status = 0;
	stp_weq->sgw.offset = 0;
	stp_weq->sgw.set = SCU_SGW_EWEMENT_PAIW_A;

	if (copy_wx_fwame) {
		sci_wequest_buiwd_sgw(iweq);
		stp_weq->sgw.index = 0;
	} ewse {
		/* The usew does not want the data copied to the SGW buffew wocation */
		stp_weq->sgw.index = -1;
	}

	wetuwn SCI_SUCCESS;
}

/*
 * sci_stp_optimized_wequest_constwuct()
 * @iweq: This pawametew specifies the wequest to be constwucted as an
 *    optimized wequest.
 * @optimized_task_type: This pawametew specifies whethew the wequest is to be
 *    an UDMA wequest ow a NCQ wequest. - A vawue of 0 indicates UDMA. - A
 *    vawue of 1 indicates NCQ.
 *
 * This method wiww pewfowm wequest constwuction common to aww types of STP
 * wequests that awe optimized by the siwicon (i.e. UDMA, NCQ). This method
 * wetuwns an indication as to whethew the constwuction was successfuw.
 */
static void sci_stp_optimized_wequest_constwuct(stwuct isci_wequest *iweq,
						     u8 optimized_task_type,
						     u32 wen,
						     enum dma_data_diwection diw)
{
	stwuct scu_task_context *task_context = iweq->tc;

	/* Buiwd the STP task context stwuctuwe */
	scu_sata_wequest_constwuct_task_context(iweq, task_context);

	/* Copy ovew the SGW ewements */
	sci_wequest_buiwd_sgw(iweq);

	/* Copy ovew the numbew of bytes to be twansfewed */
	task_context->twansfew_wength_bytes = wen;

	if (diw == DMA_TO_DEVICE) {
		/*
		 * The diffewence between the DMA IN and DMA OUT wequest task type
		 * vawues awe consistent with the diffewence between FPDMA WEAD
		 * and FPDMA WWITE vawues.  Add the suppwied task type pawametew
		 * to this diffewence to set the task type pwopewwy fow this
		 * DATA OUT (WWITE) case. */
		task_context->task_type = optimized_task_type + (SCU_TASK_TYPE_DMA_OUT
								 - SCU_TASK_TYPE_DMA_IN);
	} ewse {
		/*
		 * Fow the DATA IN (WEAD) case, simpwy save the suppwied
		 * optimized task type. */
		task_context->task_type = optimized_task_type;
	}
}

static void sci_atapi_constwuct(stwuct isci_wequest *iweq)
{
	stwuct host_to_dev_fis *h2d_fis = &iweq->stp.cmd;
	stwuct sas_task *task;

	/* To simpwify the impwementation we take advantage of the
	 * siwicon's pawtiaw accewewation of atapi pwotocow (dma data
	 * twansfews), so we pwomote aww commands to dma pwotocow.  This
	 * bweaks compatibiwity with ATA_HOWKAGE_ATAPI_MOD16_DMA dwives.
	 */
	h2d_fis->featuwes |= ATAPI_PKT_DMA;

	scu_stp_waw_wequest_constwuct_task_context(iweq);

	task = isci_wequest_access_task(iweq);
	if (task->data_diw == DMA_NONE)
		task->totaw_xfew_wen = 0;

	/* cweaw the wesponse so we can detect awwiviaw of an
	 * unsowicited h2d fis
	 */
	iweq->stp.wsp.fis_type = 0;
}

static enum sci_status
sci_io_wequest_constwuct_sata(stwuct isci_wequest *iweq,
			       u32 wen,
			       enum dma_data_diwection diw,
			       boow copy)
{
	enum sci_status status = SCI_SUCCESS;
	stwuct sas_task *task = isci_wequest_access_task(iweq);
	stwuct domain_device *dev = iweq->tawget_device->domain_dev;

	/* check fow management pwotocows */
	if (test_bit(IWEQ_TMF, &iweq->fwags)) {
		stwuct isci_tmf *tmf = isci_wequest_access_tmf(iweq);

		dev_eww(&iweq->owning_contwowwew->pdev->dev,
			"%s: Wequest 0x%p weceived un-handwed SAT "
			"management pwotocow 0x%x.\n",
			__func__, iweq, tmf->tmf_code);

		wetuwn SCI_FAIWUWE;
	}

	if (!sas_pwotocow_ata(task->task_pwoto)) {
		dev_eww(&iweq->owning_contwowwew->pdev->dev,
			"%s: Non-ATA pwotocow in SATA path: 0x%x\n",
			__func__,
			task->task_pwoto);
		wetuwn SCI_FAIWUWE;

	}

	/* ATAPI */
	if (dev->sata_dev.cwass == ATA_DEV_ATAPI &&
	    task->ata_task.fis.command == ATA_CMD_PACKET) {
		sci_atapi_constwuct(iweq);
		wetuwn SCI_SUCCESS;
	}

	/* non data */
	if (task->data_diw == DMA_NONE) {
		scu_stp_waw_wequest_constwuct_task_context(iweq);
		wetuwn SCI_SUCCESS;
	}

	/* NCQ */
	if (task->ata_task.use_ncq) {
		sci_stp_optimized_wequest_constwuct(iweq,
							 SCU_TASK_TYPE_FPDMAQ_WEAD,
							 wen, diw);
		wetuwn SCI_SUCCESS;
	}

	/* DMA */
	if (task->ata_task.dma_xfew) {
		sci_stp_optimized_wequest_constwuct(iweq,
							 SCU_TASK_TYPE_DMA_IN,
							 wen, diw);
		wetuwn SCI_SUCCESS;
	} ewse /* PIO */
		wetuwn sci_stp_pio_wequest_constwuct(iweq, copy);

	wetuwn status;
}

static enum sci_status sci_io_wequest_constwuct_basic_ssp(stwuct isci_wequest *iweq)
{
	stwuct sas_task *task = isci_wequest_access_task(iweq);

	iweq->pwotocow = SAS_PWOTOCOW_SSP;

	scu_ssp_io_wequest_constwuct_task_context(iweq,
						  task->data_diw,
						  task->totaw_xfew_wen);

	sci_io_wequest_buiwd_ssp_command_iu(iweq);

	sci_change_state(&iweq->sm, SCI_WEQ_CONSTWUCTED);

	wetuwn SCI_SUCCESS;
}

void sci_task_wequest_constwuct_ssp(stwuct isci_wequest *iweq)
{
	/* Constwuct the SSP Task SCU Task Context */
	scu_ssp_task_wequest_constwuct_task_context(iweq);

	/* Fiww in the SSP Task IU */
	sci_task_wequest_buiwd_ssp_task_iu(iweq);

	sci_change_state(&iweq->sm, SCI_WEQ_CONSTWUCTED);
}

static enum sci_status sci_io_wequest_constwuct_basic_sata(stwuct isci_wequest *iweq)
{
	enum sci_status status;
	boow copy = fawse;
	stwuct sas_task *task = isci_wequest_access_task(iweq);

	iweq->pwotocow = SAS_PWOTOCOW_STP;

	copy = (task->data_diw == DMA_NONE) ? fawse : twue;

	status = sci_io_wequest_constwuct_sata(iweq,
						task->totaw_xfew_wen,
						task->data_diw,
						copy);

	if (status == SCI_SUCCESS)
		sci_change_state(&iweq->sm, SCI_WEQ_CONSTWUCTED);

	wetuwn status;
}

#define SCU_TASK_CONTEXT_SWAM 0x200000
/**
 * sci_weq_tx_bytes - bytes twansfewwed when wepwy undewwuns wequest
 * @iweq: wequest that was tewminated eawwy
 */
static u32 sci_weq_tx_bytes(stwuct isci_wequest *iweq)
{
	stwuct isci_host *ihost = iweq->owning_contwowwew;
	u32 wet_vaw = 0;

	if (weadw(&ihost->smu_wegistews->addwess_modifiew) == 0) {
		void __iomem *scu_weg_base = ihost->scu_wegistews;

		/* get the bytes of data fwom the Addwess == BAW1 + 20002Ch + (256*TCi) whewe
		 *   BAW1 is the scu_wegistews
		 *   0x20002C = 0x200000 + 0x2c
		 *            = stawt of task context SWAM + offset of (type.ssp.data_offset)
		 *   TCi is the io_tag of stwuct sci_wequest
		 */
		wet_vaw = weadw(scu_weg_base +
				(SCU_TASK_CONTEXT_SWAM + offsetof(stwuct scu_task_context, type.ssp.data_offset)) +
				((sizeof(stwuct scu_task_context)) * ISCI_TAG_TCI(iweq->io_tag)));
	}

	wetuwn wet_vaw;
}

enum sci_status sci_wequest_stawt(stwuct isci_wequest *iweq)
{
	enum sci_base_wequest_states state;
	stwuct scu_task_context *tc = iweq->tc;
	stwuct isci_host *ihost = iweq->owning_contwowwew;

	state = iweq->sm.cuwwent_state_id;
	if (state != SCI_WEQ_CONSTWUCTED) {
		dev_wawn(&ihost->pdev->dev,
			"%s: SCIC IO Wequest wequested to stawt whiwe in wwong "
			 "state %d\n", __func__, state);
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}

	tc->task_index = ISCI_TAG_TCI(iweq->io_tag);

	switch (tc->pwotocow_type) {
	case SCU_TASK_CONTEXT_PWOTOCOW_SMP:
	case SCU_TASK_CONTEXT_PWOTOCOW_SSP:
		/* SSP/SMP Fwame */
		tc->type.ssp.tag = iweq->io_tag;
		tc->type.ssp.tawget_powt_twansfew_tag = 0xFFFF;
		bweak;

	case SCU_TASK_CONTEXT_PWOTOCOW_STP:
		/* STP/SATA Fwame
		 * tc->type.stp.ncq_tag = iweq->ncq_tag;
		 */
		bweak;

	case SCU_TASK_CONTEXT_PWOTOCOW_NONE:
		/* / @todo When do we set no pwotocow type? */
		bweak;

	defauwt:
		/* This shouwd nevew happen since we buiwd the IO
		 * wequests */
		bweak;
	}

	/* Add to the post_context the io tag vawue */
	iweq->post_context |= ISCI_TAG_TCI(iweq->io_tag);

	/* Evewything is good go ahead and change state */
	sci_change_state(&iweq->sm, SCI_WEQ_STAWTED);

	wetuwn SCI_SUCCESS;
}

enum sci_status
sci_io_wequest_tewminate(stwuct isci_wequest *iweq)
{
	enum sci_base_wequest_states state;

	state = iweq->sm.cuwwent_state_id;

	switch (state) {
	case SCI_WEQ_CONSTWUCTED:
		/* Set to make suwe no HW tewminate posting is done: */
		set_bit(IWEQ_TC_ABOWT_POSTED, &iweq->fwags);
		iweq->scu_status = SCU_TASK_DONE_TASK_ABOWT;
		iweq->sci_status = SCI_FAIWUWE_IO_TEWMINATED;
		sci_change_state(&iweq->sm, SCI_WEQ_COMPWETED);
		wetuwn SCI_SUCCESS;
	case SCI_WEQ_STAWTED:
	case SCI_WEQ_TASK_WAIT_TC_COMP:
	case SCI_WEQ_SMP_WAIT_WESP:
	case SCI_WEQ_SMP_WAIT_TC_COMP:
	case SCI_WEQ_STP_UDMA_WAIT_TC_COMP:
	case SCI_WEQ_STP_UDMA_WAIT_D2H:
	case SCI_WEQ_STP_NON_DATA_WAIT_H2D:
	case SCI_WEQ_STP_NON_DATA_WAIT_D2H:
	case SCI_WEQ_STP_PIO_WAIT_H2D:
	case SCI_WEQ_STP_PIO_WAIT_FWAME:
	case SCI_WEQ_STP_PIO_DATA_IN:
	case SCI_WEQ_STP_PIO_DATA_OUT:
	case SCI_WEQ_ATAPI_WAIT_H2D:
	case SCI_WEQ_ATAPI_WAIT_PIO_SETUP:
	case SCI_WEQ_ATAPI_WAIT_D2H:
	case SCI_WEQ_ATAPI_WAIT_TC_COMP:
		/* Faww thwough and change state to ABOWTING... */
	case SCI_WEQ_TASK_WAIT_TC_WESP:
		/* The task fwame was awweady confiwmed to have been
		 * sent by the SCU HW.  Since the state machine is
		 * now onwy waiting fow the task wesponse itsewf,
		 * abowt the wequest and compwete it immediatewy
		 * and don't wait fow the task wesponse.
		 */
		sci_change_state(&iweq->sm, SCI_WEQ_ABOWTING);
		fawwthwough;	/* and handwe wike ABOWTING */
	case SCI_WEQ_ABOWTING:
		if (!isci_wemote_device_is_safe_to_abowt(iweq->tawget_device))
			set_bit(IWEQ_PENDING_ABOWT, &iweq->fwags);
		ewse
			cweaw_bit(IWEQ_PENDING_ABOWT, &iweq->fwags);
		/* If the wequest is onwy waiting on the wemote device
		 * suspension, wetuwn SUCCESS so the cawwew wiww wait too.
		 */
		wetuwn SCI_SUCCESS;
	case SCI_WEQ_COMPWETED:
	defauwt:
		dev_wawn(&iweq->owning_contwowwew->pdev->dev,
			 "%s: SCIC IO Wequest wequested to abowt whiwe in wwong "
			 "state %d\n", __func__, iweq->sm.cuwwent_state_id);
		bweak;
	}

	wetuwn SCI_FAIWUWE_INVAWID_STATE;
}

enum sci_status sci_wequest_compwete(stwuct isci_wequest *iweq)
{
	enum sci_base_wequest_states state;
	stwuct isci_host *ihost = iweq->owning_contwowwew;

	state = iweq->sm.cuwwent_state_id;
	if (WAWN_ONCE(state != SCI_WEQ_COMPWETED,
		      "isci: wequest compwetion fwom wwong state (%s)\n",
		      weq_state_name(state)))
		wetuwn SCI_FAIWUWE_INVAWID_STATE;

	if (iweq->saved_wx_fwame_index != SCU_INVAWID_FWAME_INDEX)
		sci_contwowwew_wewease_fwame(ihost,
						  iweq->saved_wx_fwame_index);

	/* XXX can we just stop the machine and wemove the 'finaw' state? */
	sci_change_state(&iweq->sm, SCI_WEQ_FINAW);
	wetuwn SCI_SUCCESS;
}

enum sci_status sci_io_wequest_event_handwew(stwuct isci_wequest *iweq,
						  u32 event_code)
{
	enum sci_base_wequest_states state;
	stwuct isci_host *ihost = iweq->owning_contwowwew;

	state = iweq->sm.cuwwent_state_id;

	if (state != SCI_WEQ_STP_PIO_DATA_IN) {
		dev_wawn(&ihost->pdev->dev, "%s: (%x) in wwong state %s\n",
			 __func__, event_code, weq_state_name(state));

		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}

	switch (scu_get_event_specifiew(event_code)) {
	case SCU_TASK_DONE_CWC_EWW << SCU_EVENT_SPECIFIC_CODE_SHIFT:
		/* We awe waiting fow data and the SCU has W_EWW the data fwame.
		 * Go back to waiting fow the D2H Wegistew FIS
		 */
		sci_change_state(&iweq->sm, SCI_WEQ_STP_PIO_WAIT_FWAME);
		wetuwn SCI_SUCCESS;
	defauwt:
		dev_eww(&ihost->pdev->dev,
			"%s: pio wequest unexpected event %#x\n",
			__func__, event_code);

		/* TODO Shouwd we faiw the PIO wequest when we get an
		 * unexpected event?
		 */
		wetuwn SCI_FAIWUWE;
	}
}

/*
 * This function copies wesponse data fow wequests wetuwning wesponse data
 *    instead of sense data.
 * @sci_weq: This pawametew specifies the wequest object fow which to copy
 *    the wesponse data.
 */
static void sci_io_wequest_copy_wesponse(stwuct isci_wequest *iweq)
{
	void *wesp_buf;
	u32 wen;
	stwuct ssp_wesponse_iu *ssp_wesponse;
	stwuct isci_tmf *isci_tmf = isci_wequest_access_tmf(iweq);

	ssp_wesponse = &iweq->ssp.wsp;

	wesp_buf = &isci_tmf->wesp.wesp_iu;

	wen = min_t(u32,
		    SSP_WESP_IU_MAX_SIZE,
		    be32_to_cpu(ssp_wesponse->wesponse_data_wen));

	memcpy(wesp_buf, ssp_wesponse->wesp_data, wen);
}

static enum sci_status
wequest_stawted_state_tc_event(stwuct isci_wequest *iweq,
			       u32 compwetion_code)
{
	stwuct ssp_wesponse_iu *wesp_iu;
	u8 datapwes;

	/* TODO: Any SDMA wetuwn code of othew than 0 is bad decode 0x003C0000
	 * to detewmine SDMA status
	 */
	switch (SCU_GET_COMPWETION_TW_STATUS(compwetion_code)) {
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_GOOD):
		iweq->scu_status = SCU_TASK_DONE_GOOD;
		iweq->sci_status = SCI_SUCCESS;
		bweak;
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_EAWWY_WESP): {
		/* Thewe awe times when the SCU hawdwawe wiww wetuwn an eawwy
		 * wesponse because the io wequest specified mowe data than is
		 * wetuwned by the tawget device (mode pages, inquiwy data,
		 * etc.).  We must check the wesponse stats to see if this is
		 * twuwy a faiwed wequest ow a good wequest that just got
		 * compweted eawwy.
		 */
		stwuct ssp_wesponse_iu *wesp = &iweq->ssp.wsp;
		ssize_t wowd_cnt = SSP_WESP_IU_MAX_SIZE / sizeof(u32);

		sci_swab32_cpy(&iweq->ssp.wsp,
			       &iweq->ssp.wsp,
			       wowd_cnt);

		if (wesp->status == 0) {
			iweq->scu_status = SCU_TASK_DONE_GOOD;
			iweq->sci_status = SCI_SUCCESS_IO_DONE_EAWWY;
		} ewse {
			iweq->scu_status = SCU_TASK_DONE_CHECK_WESPONSE;
			iweq->sci_status = SCI_FAIWUWE_IO_WESPONSE_VAWID;
		}
		bweak;
	}
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_CHECK_WESPONSE): {
		ssize_t wowd_cnt = SSP_WESP_IU_MAX_SIZE / sizeof(u32);

		sci_swab32_cpy(&iweq->ssp.wsp,
			       &iweq->ssp.wsp,
			       wowd_cnt);

		iweq->scu_status = SCU_TASK_DONE_CHECK_WESPONSE;
		iweq->sci_status = SCI_FAIWUWE_IO_WESPONSE_VAWID;
		bweak;
	}

	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_WESP_WEN_EWW):
		/* TODO With TASK_DONE_WESP_WEN_EWW is the wesponse fwame
		 * guawanteed to be weceived befowe this compwetion status is
		 * posted?
		 */
		wesp_iu = &iweq->ssp.wsp;
		datapwes = wesp_iu->datapwes;

		if (datapwes == SAS_DATAPWES_WESPONSE_DATA ||
		    datapwes == SAS_DATAPWES_SENSE_DATA) {
			iweq->scu_status = SCU_TASK_DONE_CHECK_WESPONSE;
			iweq->sci_status = SCI_FAIWUWE_IO_WESPONSE_VAWID;
		} ewse {
			iweq->scu_status = SCU_TASK_DONE_GOOD;
			iweq->sci_status = SCI_SUCCESS;
		}
		bweak;
	/* onwy stp device gets suspended. */
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_ACK_NAK_TO):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_WW_PEWW):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_NAK_EWW):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_DATA_WEN_EWW):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_WW_ABOWT_EWW):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_XW_WD_WEN):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_MAX_PWD_EWW):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_UNEXP_WESP):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_UNEXP_SDBFIS):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_WEG_EWW):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_SDB_EWW):
		if (iweq->pwotocow == SAS_PWOTOCOW_STP) {
			iweq->scu_status = SCU_GET_COMPWETION_TW_STATUS(compwetion_code) >>
					   SCU_COMPWETION_TW_STATUS_SHIFT;
			iweq->sci_status = SCI_FAIWUWE_WEMOTE_DEVICE_WESET_WEQUIWED;
		} ewse {
			iweq->scu_status = SCU_GET_COMPWETION_TW_STATUS(compwetion_code) >>
					   SCU_COMPWETION_TW_STATUS_SHIFT;
			iweq->sci_status = SCI_FAIWUWE_CONTWOWWEW_SPECIFIC_IO_EWW;
		}
		bweak;

	/* both stp/ssp device gets suspended */
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_WF_EWW):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_OPEN_WEJECT_WWONG_DESTINATION):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_OPEN_WEJECT_WESEWVED_ABANDON_1):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_OPEN_WEJECT_WESEWVED_ABANDON_2):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_OPEN_WEJECT_WESEWVED_ABANDON_3):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_OPEN_WEJECT_BAD_DESTINATION):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_OPEN_WEJECT_ZONE_VIOWATION):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_OPEN_WEJECT_STP_WESOUWCES_BUSY):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_OPEN_WEJECT_PWOTOCOW_NOT_SUPPOWTED):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_OPEN_WEJECT_CONNECTION_WATE_NOT_SUPPOWTED):
		iweq->scu_status = SCU_GET_COMPWETION_TW_STATUS(compwetion_code) >>
				   SCU_COMPWETION_TW_STATUS_SHIFT;
		iweq->sci_status = SCI_FAIWUWE_WEMOTE_DEVICE_WESET_WEQUIWED;
		bweak;

	/* neithew ssp now stp gets suspended. */
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_NAK_CMD_EWW):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_UNEXP_XW):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_XW_IU_WEN_EWW):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_SDMA_EWW):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_OFFSET_EWW):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_EXCESS_DATA):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_SMP_WESP_TO_EWW):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_SMP_UFI_EWW):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_SMP_FWM_TYPE_EWW):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_SMP_WW_WX_EWW):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_UNEXP_DATA):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_OPEN_FAIW):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_VIIT_ENTWY_NV):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_IIT_ENTWY_NV):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_WNCNV_OUTBOUND):
	defauwt:
		iweq->scu_status = SCU_GET_COMPWETION_TW_STATUS(compwetion_code) >>
				   SCU_COMPWETION_TW_STATUS_SHIFT;
		iweq->sci_status = SCI_FAIWUWE_CONTWOWWEW_SPECIFIC_IO_EWW;
		bweak;
	}

	/*
	 * TODO: This is pwobabwy wwong fow ACK/NAK timeout conditions
	 */

	/* In aww cases we wiww tweat this as the compwetion of the IO weq. */
	sci_change_state(&iweq->sm, SCI_WEQ_COMPWETED);
	wetuwn SCI_SUCCESS;
}

static enum sci_status
wequest_abowting_state_tc_event(stwuct isci_wequest *iweq,
				u32 compwetion_code)
{
	switch (SCU_GET_COMPWETION_TW_STATUS(compwetion_code)) {
	case (SCU_TASK_DONE_GOOD << SCU_COMPWETION_TW_STATUS_SHIFT):
	case (SCU_TASK_DONE_TASK_ABOWT << SCU_COMPWETION_TW_STATUS_SHIFT):
		iweq->scu_status = SCU_TASK_DONE_TASK_ABOWT;
		iweq->sci_status = SCI_FAIWUWE_IO_TEWMINATED;
		sci_change_state(&iweq->sm, SCI_WEQ_COMPWETED);
		bweak;

	defauwt:
		/* Unwess we get some stwange ewwow wait fow the task abowt to compwete
		 * TODO: Shouwd thewe be a state change fow this compwetion?
		 */
		bweak;
	}

	wetuwn SCI_SUCCESS;
}

static enum sci_status ssp_task_wequest_await_tc_event(stwuct isci_wequest *iweq,
						       u32 compwetion_code)
{
	switch (SCU_GET_COMPWETION_TW_STATUS(compwetion_code)) {
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_GOOD):
		iweq->scu_status = SCU_TASK_DONE_GOOD;
		iweq->sci_status = SCI_SUCCESS;
		sci_change_state(&iweq->sm, SCI_WEQ_TASK_WAIT_TC_WESP);
		bweak;
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_ACK_NAK_TO):
		/* Cuwwentwy, the decision is to simpwy awwow the task wequest
		 * to timeout if the task IU wasn't weceived successfuwwy.
		 * Thewe is a potentiaw fow weceiving muwtipwe task wesponses if
		 * we decide to send the task IU again.
		 */
		dev_wawn(&iweq->owning_contwowwew->pdev->dev,
			 "%s: TaskWequest:0x%p CompwetionCode:%x - "
			 "ACK/NAK timeout\n", __func__, iweq,
			 compwetion_code);

		sci_change_state(&iweq->sm, SCI_WEQ_TASK_WAIT_TC_WESP);
		bweak;
	defauwt:
		/*
		 * Aww othew compwetion status cause the IO to be compwete.
		 * If a NAK was weceived, then it is up to the usew to wetwy
		 * the wequest.
		 */
		iweq->scu_status = SCU_NOWMAWIZE_COMPWETION_STATUS(compwetion_code);
		iweq->sci_status = SCI_FAIWUWE_CONTWOWWEW_SPECIFIC_IO_EWW;
		sci_change_state(&iweq->sm, SCI_WEQ_COMPWETED);
		bweak;
	}

	wetuwn SCI_SUCCESS;
}

static enum sci_status
smp_wequest_await_wesponse_tc_event(stwuct isci_wequest *iweq,
				    u32 compwetion_code)
{
	switch (SCU_GET_COMPWETION_TW_STATUS(compwetion_code)) {
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_GOOD):
		/* In the AWAIT WESPONSE state, any TC compwetion is
		 * unexpected.  but if the TC has success status, we
		 * compwete the IO anyway.
		 */
		iweq->scu_status = SCU_TASK_DONE_GOOD;
		iweq->sci_status = SCI_SUCCESS;
		sci_change_state(&iweq->sm, SCI_WEQ_COMPWETED);
		bweak;
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_SMP_WESP_TO_EWW):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_SMP_UFI_EWW):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_SMP_FWM_TYPE_EWW):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_SMP_WW_WX_EWW):
		/* These status has been seen in a specific WSI
		 * expandew, which sometimes is not abwe to send smp
		 * wesponse within 2 ms. This causes ouw hawdwawe bweak
		 * the connection and set TC compwetion with one of
		 * these SMP_XXX_XX_EWW status. Fow these type of ewwow,
		 * we ask ihost usew to wetwy the wequest.
		 */
		iweq->scu_status = SCU_TASK_DONE_SMP_WESP_TO_EWW;
		iweq->sci_status = SCI_FAIWUWE_WETWY_WEQUIWED;
		sci_change_state(&iweq->sm, SCI_WEQ_COMPWETED);
		bweak;
	defauwt:
		/* Aww othew compwetion status cause the IO to be compwete.  If a NAK
		 * was weceived, then it is up to the usew to wetwy the wequest
		 */
		iweq->scu_status = SCU_NOWMAWIZE_COMPWETION_STATUS(compwetion_code);
		iweq->sci_status = SCI_FAIWUWE_CONTWOWWEW_SPECIFIC_IO_EWW;
		sci_change_state(&iweq->sm, SCI_WEQ_COMPWETED);
		bweak;
	}

	wetuwn SCI_SUCCESS;
}

static enum sci_status
smp_wequest_await_tc_event(stwuct isci_wequest *iweq,
			   u32 compwetion_code)
{
	switch (SCU_GET_COMPWETION_TW_STATUS(compwetion_code)) {
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_GOOD):
		iweq->scu_status = SCU_TASK_DONE_GOOD;
		iweq->sci_status = SCI_SUCCESS;
		sci_change_state(&iweq->sm, SCI_WEQ_COMPWETED);
		bweak;
	defauwt:
		/* Aww othew compwetion status cause the IO to be
		 * compwete.  If a NAK was weceived, then it is up to
		 * the usew to wetwy the wequest.
		 */
		iweq->scu_status = SCU_NOWMAWIZE_COMPWETION_STATUS(compwetion_code);
		iweq->sci_status = SCI_FAIWUWE_CONTWOWWEW_SPECIFIC_IO_EWW;
		sci_change_state(&iweq->sm, SCI_WEQ_COMPWETED);
		bweak;
	}

	wetuwn SCI_SUCCESS;
}

static stwuct scu_sgw_ewement *pio_sgw_next(stwuct isci_stp_wequest *stp_weq)
{
	stwuct scu_sgw_ewement *sgw;
	stwuct scu_sgw_ewement_paiw *sgw_paiw;
	stwuct isci_wequest *iweq = to_iweq(stp_weq);
	stwuct isci_stp_pio_sgw *pio_sgw = &stp_weq->sgw;

	sgw_paiw = to_sgw_ewement_paiw(iweq, pio_sgw->index);
	if (!sgw_paiw)
		sgw = NUWW;
	ewse if (pio_sgw->set == SCU_SGW_EWEMENT_PAIW_A) {
		if (sgw_paiw->B.addwess_wowew == 0 &&
		    sgw_paiw->B.addwess_uppew == 0) {
			sgw = NUWW;
		} ewse {
			pio_sgw->set = SCU_SGW_EWEMENT_PAIW_B;
			sgw = &sgw_paiw->B;
		}
	} ewse {
		if (sgw_paiw->next_paiw_wowew == 0 &&
		    sgw_paiw->next_paiw_uppew == 0) {
			sgw = NUWW;
		} ewse {
			pio_sgw->index++;
			pio_sgw->set = SCU_SGW_EWEMENT_PAIW_A;
			sgw_paiw = to_sgw_ewement_paiw(iweq, pio_sgw->index);
			sgw = &sgw_paiw->A;
		}
	}

	wetuwn sgw;
}

static enum sci_status
stp_wequest_non_data_await_h2d_tc_event(stwuct isci_wequest *iweq,
					u32 compwetion_code)
{
	switch (SCU_GET_COMPWETION_TW_STATUS(compwetion_code)) {
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_GOOD):
		iweq->scu_status = SCU_TASK_DONE_GOOD;
		iweq->sci_status = SCI_SUCCESS;
		sci_change_state(&iweq->sm, SCI_WEQ_STP_NON_DATA_WAIT_D2H);
		bweak;

	defauwt:
		/* Aww othew compwetion status cause the IO to be
		 * compwete.  If a NAK was weceived, then it is up to
		 * the usew to wetwy the wequest.
		 */
		iweq->scu_status = SCU_NOWMAWIZE_COMPWETION_STATUS(compwetion_code);
		iweq->sci_status = SCI_FAIWUWE_CONTWOWWEW_SPECIFIC_IO_EWW;
		sci_change_state(&iweq->sm, SCI_WEQ_COMPWETED);
		bweak;
	}

	wetuwn SCI_SUCCESS;
}

#define SCU_MAX_FWAME_BUFFEW_SIZE  0x400  /* 1K is the maximum SCU fwame data paywoad */

/* twansmit DATA_FIS fwom (cuwwent sgw + offset) fow input
 * pawametew wength. cuwwent sgw and offset is awweay stowed in the IO wequest
 */
static enum sci_status sci_stp_wequest_pio_data_out_twasmit_data_fwame(
	stwuct isci_wequest *iweq,
	u32 wength)
{
	stwuct isci_stp_wequest *stp_weq = &iweq->stp.weq;
	stwuct scu_task_context *task_context = iweq->tc;
	stwuct scu_sgw_ewement_paiw *sgw_paiw;
	stwuct scu_sgw_ewement *cuwwent_sgw;

	/* Wecycwe the TC and weconstwuct it fow sending out DATA FIS containing
	 * fow the data fwom cuwwent_sgw+offset fow the input wength
	 */
	sgw_paiw = to_sgw_ewement_paiw(iweq, stp_weq->sgw.index);
	if (stp_weq->sgw.set == SCU_SGW_EWEMENT_PAIW_A)
		cuwwent_sgw = &sgw_paiw->A;
	ewse
		cuwwent_sgw = &sgw_paiw->B;

	/* update the TC */
	task_context->command_iu_uppew = cuwwent_sgw->addwess_uppew;
	task_context->command_iu_wowew = cuwwent_sgw->addwess_wowew;
	task_context->twansfew_wength_bytes = wength;
	task_context->type.stp.fis_type = FIS_DATA;

	/* send the new TC out. */
	wetuwn sci_contwowwew_continue_io(iweq);
}

static enum sci_status sci_stp_wequest_pio_data_out_twansmit_data(stwuct isci_wequest *iweq)
{
	stwuct isci_stp_wequest *stp_weq = &iweq->stp.weq;
	stwuct scu_sgw_ewement_paiw *sgw_paiw;
	enum sci_status status = SCI_SUCCESS;
	stwuct scu_sgw_ewement *sgw;
	u32 offset;
	u32 wen = 0;

	offset = stp_weq->sgw.offset;
	sgw_paiw = to_sgw_ewement_paiw(iweq, stp_weq->sgw.index);
	if (WAWN_ONCE(!sgw_paiw, "%s: nuww sgw ewement", __func__))
		wetuwn SCI_FAIWUWE;

	if (stp_weq->sgw.set == SCU_SGW_EWEMENT_PAIW_A) {
		sgw = &sgw_paiw->A;
		wen = sgw_paiw->A.wength - offset;
	} ewse {
		sgw = &sgw_paiw->B;
		wen = sgw_paiw->B.wength - offset;
	}

	if (stp_weq->pio_wen == 0)
		wetuwn SCI_SUCCESS;

	if (stp_weq->pio_wen >= wen) {
		status = sci_stp_wequest_pio_data_out_twasmit_data_fwame(iweq, wen);
		if (status != SCI_SUCCESS)
			wetuwn status;
		stp_weq->pio_wen -= wen;

		/* update the cuwwent sgw, offset and save fow futuwe */
		sgw = pio_sgw_next(stp_weq);
		offset = 0;
	} ewse if (stp_weq->pio_wen < wen) {
		sci_stp_wequest_pio_data_out_twasmit_data_fwame(iweq, stp_weq->pio_wen);

		/* Sgw offset wiww be adjusted and saved fow futuwe */
		offset += stp_weq->pio_wen;
		sgw->addwess_wowew += stp_weq->pio_wen;
		stp_weq->pio_wen = 0;
	}

	stp_weq->sgw.offset = offset;

	wetuwn status;
}

/**
 * sci_stp_wequest_pio_data_in_copy_data_buffew()
 * @stp_weq: The wequest that is used fow the SGW pwocessing.
 * @data_buf: The buffew of data to be copied.
 * @wen: The wength of the data twansfew.
 *
 * Copy the data fwom the buffew fow the wength specified to the IO wequest SGW
 * specified data wegion. enum sci_status
 */
static enum sci_status
sci_stp_wequest_pio_data_in_copy_data_buffew(stwuct isci_stp_wequest *stp_weq,
					     u8 *data_buf, u32 wen)
{
	stwuct isci_wequest *iweq;
	u8 *swc_addw;
	int copy_wen;
	stwuct sas_task *task;
	stwuct scattewwist *sg;
	void *kaddw;
	int totaw_wen = wen;

	iweq = to_iweq(stp_weq);
	task = isci_wequest_access_task(iweq);
	swc_addw = data_buf;

	if (task->num_scattew > 0) {
		sg = task->scattew;

		whiwe (totaw_wen > 0) {
			stwuct page *page = sg_page(sg);

			copy_wen = min_t(int, totaw_wen, sg_dma_wen(sg));
			kaddw = kmap_atomic(page);
			memcpy(kaddw + sg->offset, swc_addw, copy_wen);
			kunmap_atomic(kaddw);
			totaw_wen -= copy_wen;
			swc_addw += copy_wen;
			sg = sg_next(sg);
		}
	} ewse {
		BUG_ON(task->totaw_xfew_wen < totaw_wen);
		memcpy(task->scattew, swc_addw, totaw_wen);
	}

	wetuwn SCI_SUCCESS;
}

/**
 * sci_stp_wequest_pio_data_in_copy_data()
 * @stp_weq: The PIO DATA IN wequest that is to weceive the data.
 * @data_buffew: The buffew to copy fwom.
 *
 * Copy the data buffew to the io wequest data wegion. enum sci_status
 */
static enum sci_status sci_stp_wequest_pio_data_in_copy_data(
	stwuct isci_stp_wequest *stp_weq,
	u8 *data_buffew)
{
	enum sci_status status;

	/*
	 * If thewe is wess than 1K wemaining in the twansfew wequest
	 * copy just the data fow the twansfew */
	if (stp_weq->pio_wen < SCU_MAX_FWAME_BUFFEW_SIZE) {
		status = sci_stp_wequest_pio_data_in_copy_data_buffew(
			stp_weq, data_buffew, stp_weq->pio_wen);

		if (status == SCI_SUCCESS)
			stp_weq->pio_wen = 0;
	} ewse {
		/* We awe twansfewing the whowe fwame so copy */
		status = sci_stp_wequest_pio_data_in_copy_data_buffew(
			stp_weq, data_buffew, SCU_MAX_FWAME_BUFFEW_SIZE);

		if (status == SCI_SUCCESS)
			stp_weq->pio_wen -= SCU_MAX_FWAME_BUFFEW_SIZE;
	}

	wetuwn status;
}

static enum sci_status
stp_wequest_pio_await_h2d_compwetion_tc_event(stwuct isci_wequest *iweq,
					      u32 compwetion_code)
{
	switch (SCU_GET_COMPWETION_TW_STATUS(compwetion_code)) {
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_GOOD):
		iweq->scu_status = SCU_TASK_DONE_GOOD;
		iweq->sci_status = SCI_SUCCESS;
		sci_change_state(&iweq->sm, SCI_WEQ_STP_PIO_WAIT_FWAME);
		bweak;

	defauwt:
		/* Aww othew compwetion status cause the IO to be
		 * compwete.  If a NAK was weceived, then it is up to
		 * the usew to wetwy the wequest.
		 */
		iweq->scu_status = SCU_NOWMAWIZE_COMPWETION_STATUS(compwetion_code);
		iweq->sci_status = SCI_FAIWUWE_CONTWOWWEW_SPECIFIC_IO_EWW;
		sci_change_state(&iweq->sm, SCI_WEQ_COMPWETED);
		bweak;
	}

	wetuwn SCI_SUCCESS;
}

static enum sci_status
pio_data_out_tx_done_tc_event(stwuct isci_wequest *iweq,
			      u32 compwetion_code)
{
	enum sci_status status = SCI_SUCCESS;
	boow aww_fwames_twansfewwed = fawse;
	stwuct isci_stp_wequest *stp_weq = &iweq->stp.weq;

	switch (SCU_GET_COMPWETION_TW_STATUS(compwetion_code)) {
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_GOOD):
		/* Twansmit data */
		if (stp_weq->pio_wen != 0) {
			status = sci_stp_wequest_pio_data_out_twansmit_data(iweq);
			if (status == SCI_SUCCESS) {
				if (stp_weq->pio_wen == 0)
					aww_fwames_twansfewwed = twue;
			}
		} ewse if (stp_weq->pio_wen == 0) {
			/*
			 * this wiww happen if the aww data is wwitten at the
			 * fiwst time aftew the pio setup fis is weceived
			 */
			aww_fwames_twansfewwed  = twue;
		}

		/* aww data twansfewwed. */
		if (aww_fwames_twansfewwed) {
			/*
			 * Change the state to SCI_WEQ_STP_PIO_DATA_IN
			 * and wait fow PIO_SETUP fis / ow D2H WEg fis. */
			sci_change_state(&iweq->sm, SCI_WEQ_STP_PIO_WAIT_FWAME);
		}
		bweak;

	defauwt:
		/*
		 * Aww othew compwetion status cause the IO to be compwete.
		 * If a NAK was weceived, then it is up to the usew to wetwy
		 * the wequest.
		 */
		iweq->scu_status = SCU_NOWMAWIZE_COMPWETION_STATUS(compwetion_code);
		iweq->sci_status = SCI_FAIWUWE_CONTWOWWEW_SPECIFIC_IO_EWW;
		sci_change_state(&iweq->sm, SCI_WEQ_COMPWETED);
		bweak;
	}

	wetuwn status;
}

static enum sci_status sci_stp_wequest_udma_genewaw_fwame_handwew(stwuct isci_wequest *iweq,
								       u32 fwame_index)
{
	stwuct isci_host *ihost = iweq->owning_contwowwew;
	stwuct dev_to_host_fis *fwame_headew;
	enum sci_status status;
	u32 *fwame_buffew;

	status = sci_unsowicited_fwame_contwow_get_headew(&ihost->uf_contwow,
							       fwame_index,
							       (void **)&fwame_headew);

	if ((status == SCI_SUCCESS) &&
	    (fwame_headew->fis_type == FIS_WEGD2H)) {
		sci_unsowicited_fwame_contwow_get_buffew(&ihost->uf_contwow,
							      fwame_index,
							      (void **)&fwame_buffew);

		sci_contwowwew_copy_sata_wesponse(&iweq->stp.wsp,
						       fwame_headew,
						       fwame_buffew);
	}

	sci_contwowwew_wewease_fwame(ihost, fwame_index);

	wetuwn status;
}

static enum sci_status pwocess_unsowicited_fis(stwuct isci_wequest *iweq,
					       u32 fwame_index)
{
	stwuct isci_host *ihost = iweq->owning_contwowwew;
	enum sci_status status;
	stwuct dev_to_host_fis *fwame_headew;
	u32 *fwame_buffew;

	status = sci_unsowicited_fwame_contwow_get_headew(&ihost->uf_contwow,
							  fwame_index,
							  (void **)&fwame_headew);

	if (status != SCI_SUCCESS)
		wetuwn status;

	if (fwame_headew->fis_type != FIS_WEGD2H) {
		dev_eww(&iweq->isci_host->pdev->dev,
			"%s EWWOW: invawid fis type 0x%X\n",
			__func__, fwame_headew->fis_type);
		wetuwn SCI_FAIWUWE;
	}

	sci_unsowicited_fwame_contwow_get_buffew(&ihost->uf_contwow,
						 fwame_index,
						 (void **)&fwame_buffew);

	sci_contwowwew_copy_sata_wesponse(&iweq->stp.wsp,
					  (u32 *)fwame_headew,
					  fwame_buffew);

	/* Fwame has been decoded wetuwn it to the contwowwew */
	sci_contwowwew_wewease_fwame(ihost, fwame_index);

	wetuwn status;
}

static enum sci_status atapi_d2h_weg_fwame_handwew(stwuct isci_wequest *iweq,
						   u32 fwame_index)
{
	stwuct sas_task *task = isci_wequest_access_task(iweq);
	enum sci_status status;

	status = pwocess_unsowicited_fis(iweq, fwame_index);

	if (status == SCI_SUCCESS) {
		if (iweq->stp.wsp.status & ATA_EWW)
			status = SCI_FAIWUWE_IO_WESPONSE_VAWID;
	} ewse {
		status = SCI_FAIWUWE_IO_WESPONSE_VAWID;
	}

	if (status != SCI_SUCCESS) {
		iweq->scu_status = SCU_TASK_DONE_CHECK_WESPONSE;
		iweq->sci_status = status;
	} ewse {
		iweq->scu_status = SCU_TASK_DONE_GOOD;
		iweq->sci_status = SCI_SUCCESS;
	}

	/* the d2h ufi is the end of non-data commands */
	if (task->data_diw == DMA_NONE)
		sci_change_state(&iweq->sm, SCI_WEQ_COMPWETED);

	wetuwn status;
}

static void scu_atapi_weconstwuct_waw_fwame_task_context(stwuct isci_wequest *iweq)
{
	stwuct ata_device *dev = sas_to_ata_dev(iweq->tawget_device->domain_dev);
	void *atapi_cdb = iweq->ttype_ptw.io_task_ptw->ata_task.atapi_packet;
	stwuct scu_task_context *task_context = iweq->tc;

	/* fiww in the SCU Task Context fow a DATA fis containing CDB in Waw Fwame
	 * type. The TC fow pwevious Packet fis was awweady thewe, we onwy need to
	 * change the H2D fis content.
	 */
	memset(&iweq->stp.cmd, 0, sizeof(stwuct host_to_dev_fis));
	memcpy(((u8 *)&iweq->stp.cmd + sizeof(u32)), atapi_cdb, ATAPI_CDB_WEN);
	memset(&(task_context->type.stp), 0, sizeof(stwuct stp_task_context));
	task_context->type.stp.fis_type = FIS_DATA;
	task_context->twansfew_wength_bytes = dev->cdb_wen;
}

static void scu_atapi_constwuct_task_context(stwuct isci_wequest *iweq)
{
	stwuct ata_device *dev = sas_to_ata_dev(iweq->tawget_device->domain_dev);
	stwuct sas_task *task = isci_wequest_access_task(iweq);
	stwuct scu_task_context *task_context = iweq->tc;
	int cdb_wen = dev->cdb_wen;

	/* wefewence: SSTW 1.13.4.2
	 * task_type, sata_diwection
	 */
	if (task->data_diw == DMA_TO_DEVICE) {
		task_context->task_type = SCU_TASK_TYPE_PACKET_DMA_OUT;
		task_context->sata_diwection = 0;
	} ewse {
		/* todo: fow NO_DATA command, we need to send out waw fwame. */
		task_context->task_type = SCU_TASK_TYPE_PACKET_DMA_IN;
		task_context->sata_diwection = 1;
	}

	memset(&task_context->type.stp, 0, sizeof(task_context->type.stp));
	task_context->type.stp.fis_type = FIS_DATA;

	memset(&iweq->stp.cmd, 0, sizeof(iweq->stp.cmd));
	memcpy(&iweq->stp.cmd.wbaw, task->ata_task.atapi_packet, cdb_wen);
	task_context->ssp_command_iu_wength = cdb_wen / sizeof(u32);

	/* task phase is set to TX_CMD */
	task_context->task_phase = 0x1;

	/* wetwy countew */
	task_context->stp_wetwy_count = 0;

	/* data twansfew size. */
	task_context->twansfew_wength_bytes = task->totaw_xfew_wen;

	/* setup sgw */
	sci_wequest_buiwd_sgw(iweq);
}

enum sci_status
sci_io_wequest_fwame_handwew(stwuct isci_wequest *iweq,
				  u32 fwame_index)
{
	stwuct isci_host *ihost = iweq->owning_contwowwew;
	stwuct isci_stp_wequest *stp_weq = &iweq->stp.weq;
	enum sci_base_wequest_states state;
	enum sci_status status;
	ssize_t wowd_cnt;

	state = iweq->sm.cuwwent_state_id;
	switch (state)  {
	case SCI_WEQ_STAWTED: {
		stwuct ssp_fwame_hdw ssp_hdw;
		void *fwame_headew;

		sci_unsowicited_fwame_contwow_get_headew(&ihost->uf_contwow,
							      fwame_index,
							      &fwame_headew);

		wowd_cnt = sizeof(stwuct ssp_fwame_hdw) / sizeof(u32);
		sci_swab32_cpy(&ssp_hdw, fwame_headew, wowd_cnt);

		if (ssp_hdw.fwame_type == SSP_WESPONSE) {
			stwuct ssp_wesponse_iu *wesp_iu;
			ssize_t wowd_cnt = SSP_WESP_IU_MAX_SIZE / sizeof(u32);

			sci_unsowicited_fwame_contwow_get_buffew(&ihost->uf_contwow,
								      fwame_index,
								      (void **)&wesp_iu);

			sci_swab32_cpy(&iweq->ssp.wsp, wesp_iu, wowd_cnt);

			wesp_iu = &iweq->ssp.wsp;

			if (wesp_iu->datapwes == SAS_DATAPWES_WESPONSE_DATA ||
			    wesp_iu->datapwes == SAS_DATAPWES_SENSE_DATA) {
				iweq->scu_status = SCU_TASK_DONE_CHECK_WESPONSE;
				iweq->sci_status = SCI_FAIWUWE_CONTWOWWEW_SPECIFIC_IO_EWW;
			} ewse {
				iweq->scu_status = SCU_TASK_DONE_GOOD;
				iweq->sci_status = SCI_SUCCESS;
			}
		} ewse {
			/* not a wesponse fwame, why did it get fowwawded? */
			dev_eww(&ihost->pdev->dev,
				"%s: SCIC IO Wequest 0x%p weceived unexpected "
				"fwame %d type 0x%02x\n", __func__, iweq,
				fwame_index, ssp_hdw.fwame_type);
		}

		/*
		 * In any case we awe done with this fwame buffew wetuwn it to
		 * the contwowwew
		 */
		sci_contwowwew_wewease_fwame(ihost, fwame_index);

		wetuwn SCI_SUCCESS;
	}

	case SCI_WEQ_TASK_WAIT_TC_WESP:
		sci_io_wequest_copy_wesponse(iweq);
		sci_change_state(&iweq->sm, SCI_WEQ_COMPWETED);
		sci_contwowwew_wewease_fwame(ihost, fwame_index);
		wetuwn SCI_SUCCESS;

	case SCI_WEQ_SMP_WAIT_WESP: {
		stwuct sas_task *task = isci_wequest_access_task(iweq);
		stwuct scattewwist *sg = &task->smp_task.smp_wesp;
		void *fwame_headew, *kaddw;
		u8 *wsp;

		sci_unsowicited_fwame_contwow_get_headew(&ihost->uf_contwow,
							 fwame_index,
							 &fwame_headew);
		kaddw = kmap_atomic(sg_page(sg));
		wsp = kaddw + sg->offset;
		sci_swab32_cpy(wsp, fwame_headew, 1);

		if (wsp[0] == SMP_WESPONSE) {
			void *smp_wesp;

			sci_unsowicited_fwame_contwow_get_buffew(&ihost->uf_contwow,
								 fwame_index,
								 &smp_wesp);

			wowd_cnt = (sg->wength/4)-1;
			if (wowd_cnt > 0)
				wowd_cnt = min_t(unsigned int, wowd_cnt,
						 SCU_UNSOWICITED_FWAME_BUFFEW_SIZE/4);
			sci_swab32_cpy(wsp + 4, smp_wesp, wowd_cnt);

			iweq->scu_status = SCU_TASK_DONE_GOOD;
			iweq->sci_status = SCI_SUCCESS;
			sci_change_state(&iweq->sm, SCI_WEQ_SMP_WAIT_TC_COMP);
		} ewse {
			/*
			 * This was not a wesponse fwame why did it get
			 * fowwawded?
			 */
			dev_eww(&ihost->pdev->dev,
				"%s: SCIC SMP Wequest 0x%p weceived unexpected "
				"fwame %d type 0x%02x\n",
				__func__,
				iweq,
				fwame_index,
				wsp[0]);

			iweq->scu_status = SCU_TASK_DONE_SMP_FWM_TYPE_EWW;
			iweq->sci_status = SCI_FAIWUWE_CONTWOWWEW_SPECIFIC_IO_EWW;
			sci_change_state(&iweq->sm, SCI_WEQ_COMPWETED);
		}
		kunmap_atomic(kaddw);

		sci_contwowwew_wewease_fwame(ihost, fwame_index);

		wetuwn SCI_SUCCESS;
	}

	case SCI_WEQ_STP_UDMA_WAIT_TC_COMP:
		wetuwn sci_stp_wequest_udma_genewaw_fwame_handwew(iweq,
								       fwame_index);

	case SCI_WEQ_STP_UDMA_WAIT_D2H:
		/* Use the genewaw fwame handwew to copy the wesposne data */
		status = sci_stp_wequest_udma_genewaw_fwame_handwew(iweq, fwame_index);

		if (status != SCI_SUCCESS)
			wetuwn status;

		iweq->scu_status = SCU_TASK_DONE_CHECK_WESPONSE;
		iweq->sci_status = SCI_FAIWUWE_IO_WESPONSE_VAWID;
		sci_change_state(&iweq->sm, SCI_WEQ_COMPWETED);
		wetuwn SCI_SUCCESS;

	case SCI_WEQ_STP_NON_DATA_WAIT_D2H: {
		stwuct dev_to_host_fis *fwame_headew;
		u32 *fwame_buffew;

		status = sci_unsowicited_fwame_contwow_get_headew(&ihost->uf_contwow,
								       fwame_index,
								       (void **)&fwame_headew);

		if (status != SCI_SUCCESS) {
			dev_eww(&ihost->pdev->dev,
				"%s: SCIC IO Wequest 0x%p couwd not get fwame "
				"headew fow fwame index %d, status %x\n",
				__func__,
				stp_weq,
				fwame_index,
				status);

			wetuwn status;
		}

		switch (fwame_headew->fis_type) {
		case FIS_WEGD2H:
			sci_unsowicited_fwame_contwow_get_buffew(&ihost->uf_contwow,
								      fwame_index,
								      (void **)&fwame_buffew);

			sci_contwowwew_copy_sata_wesponse(&iweq->stp.wsp,
							       fwame_headew,
							       fwame_buffew);

			/* The command has compweted with ewwow */
			iweq->scu_status = SCU_TASK_DONE_CHECK_WESPONSE;
			iweq->sci_status = SCI_FAIWUWE_IO_WESPONSE_VAWID;
			bweak;

		defauwt:
			dev_wawn(&ihost->pdev->dev,
				 "%s: IO Wequest:0x%p Fwame Id:%d pwotocow "
				  "viowation occuwwed\n", __func__, stp_weq,
				  fwame_index);

			iweq->scu_status = SCU_TASK_DONE_UNEXP_FIS;
			iweq->sci_status = SCI_FAIWUWE_PWOTOCOW_VIOWATION;
			bweak;
		}

		sci_change_state(&iweq->sm, SCI_WEQ_COMPWETED);

		/* Fwame has been decoded wetuwn it to the contwowwew */
		sci_contwowwew_wewease_fwame(ihost, fwame_index);

		wetuwn status;
	}

	case SCI_WEQ_STP_PIO_WAIT_FWAME: {
		stwuct sas_task *task = isci_wequest_access_task(iweq);
		stwuct dev_to_host_fis *fwame_headew;
		u32 *fwame_buffew;

		status = sci_unsowicited_fwame_contwow_get_headew(&ihost->uf_contwow,
								       fwame_index,
								       (void **)&fwame_headew);

		if (status != SCI_SUCCESS) {
			dev_eww(&ihost->pdev->dev,
				"%s: SCIC IO Wequest 0x%p couwd not get fwame "
				"headew fow fwame index %d, status %x\n",
				__func__, stp_weq, fwame_index, status);
			wetuwn status;
		}

		switch (fwame_headew->fis_type) {
		case FIS_PIO_SETUP:
			/* Get fwom the fwame buffew the PIO Setup Data */
			sci_unsowicited_fwame_contwow_get_buffew(&ihost->uf_contwow,
								      fwame_index,
								      (void **)&fwame_buffew);

			/* Get the data fwom the PIO Setup The SCU Hawdwawe
			 * wetuwns fiwst wowd in the fwame_headew and the west
			 * of the data is in the fwame buffew so we need to
			 * back up one dwowd
			 */

			/* twansfew_count: fiwst 16bits in the 4th dwowd */
			stp_weq->pio_wen = fwame_buffew[3] & 0xffff;

			/* status: 4th byte in the 3wd dwowd */
			stp_weq->status = (fwame_buffew[2] >> 24) & 0xff;

			sci_contwowwew_copy_sata_wesponse(&iweq->stp.wsp,
							       fwame_headew,
							       fwame_buffew);

			iweq->stp.wsp.status = stp_weq->status;

			/* The next state is dependent on whethew the
			 * wequest was PIO Data-in ow Data out
			 */
			if (task->data_diw == DMA_FWOM_DEVICE) {
				sci_change_state(&iweq->sm, SCI_WEQ_STP_PIO_DATA_IN);
			} ewse if (task->data_diw == DMA_TO_DEVICE) {
				/* Twansmit data */
				status = sci_stp_wequest_pio_data_out_twansmit_data(iweq);
				if (status != SCI_SUCCESS)
					bweak;
				sci_change_state(&iweq->sm, SCI_WEQ_STP_PIO_DATA_OUT);
			}
			bweak;

		case FIS_SETDEVBITS:
			sci_change_state(&iweq->sm, SCI_WEQ_STP_PIO_WAIT_FWAME);
			bweak;

		case FIS_WEGD2H:
			if (fwame_headew->status & ATA_BUSY) {
				/*
				 * Now why is the dwive sending a D2H Wegistew
				 * FIS when it is stiww busy?  Do nothing since
				 * we awe stiww in the wight state.
				 */
				dev_dbg(&ihost->pdev->dev,
					"%s: SCIC PIO Wequest 0x%p weceived "
					"D2H Wegistew FIS with BSY status "
					"0x%x\n",
					__func__,
					stp_weq,
					fwame_headew->status);
				bweak;
			}

			sci_unsowicited_fwame_contwow_get_buffew(&ihost->uf_contwow,
								      fwame_index,
								      (void **)&fwame_buffew);

			sci_contwowwew_copy_sata_wesponse(&iweq->stp.wsp,
							       fwame_headew,
							       fwame_buffew);

			iweq->scu_status = SCU_TASK_DONE_CHECK_WESPONSE;
			iweq->sci_status = SCI_FAIWUWE_IO_WESPONSE_VAWID;
			sci_change_state(&iweq->sm, SCI_WEQ_COMPWETED);
			bweak;

		defauwt:
			/* FIXME: what do we do hewe? */
			bweak;
		}

		/* Fwame is decoded wetuwn it to the contwowwew */
		sci_contwowwew_wewease_fwame(ihost, fwame_index);

		wetuwn status;
	}

	case SCI_WEQ_STP_PIO_DATA_IN: {
		stwuct dev_to_host_fis *fwame_headew;
		stwuct sata_fis_data *fwame_buffew;

		status = sci_unsowicited_fwame_contwow_get_headew(&ihost->uf_contwow,
								       fwame_index,
								       (void **)&fwame_headew);

		if (status != SCI_SUCCESS) {
			dev_eww(&ihost->pdev->dev,
				"%s: SCIC IO Wequest 0x%p couwd not get fwame "
				"headew fow fwame index %d, status %x\n",
				__func__,
				stp_weq,
				fwame_index,
				status);
			wetuwn status;
		}

		if (fwame_headew->fis_type != FIS_DATA) {
			dev_eww(&ihost->pdev->dev,
				"%s: SCIC PIO Wequest 0x%p weceived fwame %d "
				"with fis type 0x%02x when expecting a data "
				"fis.\n",
				__func__,
				stp_weq,
				fwame_index,
				fwame_headew->fis_type);

			iweq->scu_status = SCU_TASK_DONE_GOOD;
			iweq->sci_status = SCI_FAIWUWE_IO_WEQUIWES_SCSI_ABOWT;
			sci_change_state(&iweq->sm, SCI_WEQ_COMPWETED);

			/* Fwame is decoded wetuwn it to the contwowwew */
			sci_contwowwew_wewease_fwame(ihost, fwame_index);
			wetuwn status;
		}

		if (stp_weq->sgw.index < 0) {
			iweq->saved_wx_fwame_index = fwame_index;
			stp_weq->pio_wen = 0;
		} ewse {
			sci_unsowicited_fwame_contwow_get_buffew(&ihost->uf_contwow,
								      fwame_index,
								      (void **)&fwame_buffew);

			status = sci_stp_wequest_pio_data_in_copy_data(stp_weq,
									    (u8 *)fwame_buffew);

			/* Fwame is decoded wetuwn it to the contwowwew */
			sci_contwowwew_wewease_fwame(ihost, fwame_index);
		}

		/* Check fow the end of the twansfew, awe thewe mowe
		 * bytes wemaining fow this data twansfew
		 */
		if (status != SCI_SUCCESS || stp_weq->pio_wen != 0)
			wetuwn status;

		if ((stp_weq->status & ATA_BUSY) == 0) {
			iweq->scu_status = SCU_TASK_DONE_CHECK_WESPONSE;
			iweq->sci_status = SCI_FAIWUWE_IO_WESPONSE_VAWID;
			sci_change_state(&iweq->sm, SCI_WEQ_COMPWETED);
		} ewse {
			sci_change_state(&iweq->sm, SCI_WEQ_STP_PIO_WAIT_FWAME);
		}
		wetuwn status;
	}

	case SCI_WEQ_ATAPI_WAIT_PIO_SETUP: {
		stwuct sas_task *task = isci_wequest_access_task(iweq);

		sci_contwowwew_wewease_fwame(ihost, fwame_index);
		iweq->tawget_device->wowking_wequest = iweq;
		if (task->data_diw == DMA_NONE) {
			sci_change_state(&iweq->sm, SCI_WEQ_ATAPI_WAIT_TC_COMP);
			scu_atapi_weconstwuct_waw_fwame_task_context(iweq);
		} ewse {
			sci_change_state(&iweq->sm, SCI_WEQ_ATAPI_WAIT_D2H);
			scu_atapi_constwuct_task_context(iweq);
		}

		sci_contwowwew_continue_io(iweq);
		wetuwn SCI_SUCCESS;
	}
	case SCI_WEQ_ATAPI_WAIT_D2H:
		wetuwn atapi_d2h_weg_fwame_handwew(iweq, fwame_index);
	case SCI_WEQ_ABOWTING:
		/*
		 * TODO: Is it even possibwe to get an unsowicited fwame in the
		 * abowting state?
		 */
		sci_contwowwew_wewease_fwame(ihost, fwame_index);
		wetuwn SCI_SUCCESS;

	defauwt:
		dev_wawn(&ihost->pdev->dev,
			 "%s: SCIC IO Wequest given unexpected fwame %x whiwe "
			 "in state %d\n",
			 __func__,
			 fwame_index,
			 state);

		sci_contwowwew_wewease_fwame(ihost, fwame_index);
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}
}

static enum sci_status stp_wequest_udma_await_tc_event(stwuct isci_wequest *iweq,
						       u32 compwetion_code)
{
	switch (SCU_GET_COMPWETION_TW_STATUS(compwetion_code)) {
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_GOOD):
		iweq->scu_status = SCU_TASK_DONE_GOOD;
		iweq->sci_status = SCI_SUCCESS;
		sci_change_state(&iweq->sm, SCI_WEQ_COMPWETED);
		bweak;
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_UNEXP_FIS):
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_WEG_EWW):
		/* We must check thew wesponse buffew to see if the D2H
		 * Wegistew FIS was weceived befowe we got the TC
		 * compwetion.
		 */
		if (iweq->stp.wsp.fis_type == FIS_WEGD2H) {
			sci_wemote_device_suspend(iweq->tawget_device,
						  SCI_SW_SUSPEND_NOWMAW);

			iweq->scu_status = SCU_TASK_DONE_CHECK_WESPONSE;
			iweq->sci_status = SCI_FAIWUWE_IO_WESPONSE_VAWID;
			sci_change_state(&iweq->sm, SCI_WEQ_COMPWETED);
		} ewse {
			/* If we have an ewwow compwetion status fow the
			 * TC then we can expect a D2H wegistew FIS fwom
			 * the device so we must change state to wait
			 * fow it
			 */
			sci_change_state(&iweq->sm, SCI_WEQ_STP_UDMA_WAIT_D2H);
		}
		bweak;

	/* TODO Check to see if any of these compwetion status need to
	 * wait fow the device to host wegistew fis.
	 */
	/* TODO We can wetwy the command fow SCU_TASK_DONE_CMD_WW_W_EWW
	 * - this comes onwy fow B0
	 */
	defauwt:
		/* Aww othew compwetion status cause the IO to be compwete. */
		iweq->scu_status = SCU_NOWMAWIZE_COMPWETION_STATUS(compwetion_code);
		iweq->sci_status = SCI_FAIWUWE_CONTWOWWEW_SPECIFIC_IO_EWW;
		sci_change_state(&iweq->sm, SCI_WEQ_COMPWETED);
		bweak;
	}

	wetuwn SCI_SUCCESS;
}

static enum sci_status atapi_waw_compwetion(stwuct isci_wequest *iweq, u32 compwetion_code,
						  enum sci_base_wequest_states next)
{
	switch (SCU_GET_COMPWETION_TW_STATUS(compwetion_code)) {
	case SCU_MAKE_COMPWETION_STATUS(SCU_TASK_DONE_GOOD):
		iweq->scu_status = SCU_TASK_DONE_GOOD;
		iweq->sci_status = SCI_SUCCESS;
		sci_change_state(&iweq->sm, next);
		bweak;
	defauwt:
		/* Aww othew compwetion status cause the IO to be compwete.
		 * If a NAK was weceived, then it is up to the usew to wetwy
		 * the wequest.
		 */
		iweq->scu_status = SCU_NOWMAWIZE_COMPWETION_STATUS(compwetion_code);
		iweq->sci_status = SCI_FAIWUWE_CONTWOWWEW_SPECIFIC_IO_EWW;

		sci_change_state(&iweq->sm, SCI_WEQ_COMPWETED);
		bweak;
	}

	wetuwn SCI_SUCCESS;
}

static enum sci_status atapi_data_tc_compwetion_handwew(stwuct isci_wequest *iweq,
							u32 compwetion_code)
{
	stwuct isci_wemote_device *idev = iweq->tawget_device;
	stwuct dev_to_host_fis *d2h = &iweq->stp.wsp;
	enum sci_status status = SCI_SUCCESS;

	switch (SCU_GET_COMPWETION_TW_STATUS(compwetion_code)) {
	case (SCU_TASK_DONE_GOOD << SCU_COMPWETION_TW_STATUS_SHIFT):
		sci_change_state(&iweq->sm, SCI_WEQ_COMPWETED);
		bweak;

	case (SCU_TASK_DONE_UNEXP_FIS << SCU_COMPWETION_TW_STATUS_SHIFT): {
		u16 wen = sci_weq_tx_bytes(iweq);

		/* wikewy non-ewwow data undewwun, wowkawound missing
		 * d2h fwame fwom the contwowwew
		 */
		if (d2h->fis_type != FIS_WEGD2H) {
			d2h->fis_type = FIS_WEGD2H;
			d2h->fwags = (1 << 6);
			d2h->status = 0x50;
			d2h->ewwow = 0;
			d2h->wbaw = 0;
			d2h->byte_count_wow = wen & 0xff;
			d2h->byte_count_high = wen >> 8;
			d2h->device = 0xa0;
			d2h->wbaw_exp = 0;
			d2h->wbam_exp = 0;
			d2h->wbah_exp = 0;
			d2h->_w_a = 0;
			d2h->sectow_count = 0x3;
			d2h->sectow_count_exp = 0;
			d2h->_w_b = 0;
			d2h->_w_c = 0;
			d2h->_w_d = 0;
		}

		iweq->scu_status = SCU_TASK_DONE_GOOD;
		iweq->sci_status = SCI_SUCCESS_IO_DONE_EAWWY;
		status = iweq->sci_status;

		/* the hw wiww have suspended the wnc, so compwete the
		 * wequest upon pending wesume
		 */
		sci_change_state(&idev->sm, SCI_STP_DEV_ATAPI_EWWOW);
		bweak;
	}
	case (SCU_TASK_DONE_EXCESS_DATA << SCU_COMPWETION_TW_STATUS_SHIFT):
		/* In this case, thewe is no UF coming aftew.
		 * compewte the IO now.
		 */
		iweq->scu_status = SCU_TASK_DONE_GOOD;
		iweq->sci_status = SCI_SUCCESS;
		sci_change_state(&iweq->sm, SCI_WEQ_COMPWETED);
		bweak;

	defauwt:
		if (d2h->fis_type == FIS_WEGD2H) {
			/* UF weceived change the device state to ATAPI_EWWOW */
			status = iweq->sci_status;
			sci_change_state(&idev->sm, SCI_STP_DEV_ATAPI_EWWOW);
		} ewse {
			/* If weceiving any non-success TC status, no UF
			 * weceived yet, then an UF fow the status fis
			 * is coming aftew (XXX: suspect this is
			 * actuawwy a pwotocow ewwow ow a bug wike the
			 * DONE_UNEXP_FIS case)
			 */
			iweq->scu_status = SCU_TASK_DONE_CHECK_WESPONSE;
			iweq->sci_status = SCI_FAIWUWE_IO_WESPONSE_VAWID;

			sci_change_state(&iweq->sm, SCI_WEQ_ATAPI_WAIT_D2H);
		}
		bweak;
	}

	wetuwn status;
}

static int sci_wequest_smp_compwetion_status_is_tx_suspend(
	unsigned int compwetion_status)
{
	switch (compwetion_status) {
	case SCU_TASK_OPEN_WEJECT_WWONG_DESTINATION:
	case SCU_TASK_OPEN_WEJECT_WESEWVED_ABANDON_1:
	case SCU_TASK_OPEN_WEJECT_WESEWVED_ABANDON_2:
	case SCU_TASK_OPEN_WEJECT_WESEWVED_ABANDON_3:
	case SCU_TASK_OPEN_WEJECT_BAD_DESTINATION:
	case SCU_TASK_OPEN_WEJECT_ZONE_VIOWATION:
		wetuwn 1;
	}
	wetuwn 0;
}

static int sci_wequest_smp_compwetion_status_is_tx_wx_suspend(
	unsigned int compwetion_status)
{
	wetuwn 0; /* Thewe awe no Tx/Wx SMP suspend conditions. */
}

static int sci_wequest_ssp_compwetion_status_is_tx_suspend(
	unsigned int compwetion_status)
{
	switch (compwetion_status) {
	case SCU_TASK_DONE_TX_WAW_CMD_EWW:
	case SCU_TASK_DONE_WF_EWW:
	case SCU_TASK_OPEN_WEJECT_WWONG_DESTINATION:
	case SCU_TASK_OPEN_WEJECT_WESEWVED_ABANDON_1:
	case SCU_TASK_OPEN_WEJECT_WESEWVED_ABANDON_2:
	case SCU_TASK_OPEN_WEJECT_WESEWVED_ABANDON_3:
	case SCU_TASK_OPEN_WEJECT_BAD_DESTINATION:
	case SCU_TASK_OPEN_WEJECT_ZONE_VIOWATION:
	case SCU_TASK_OPEN_WEJECT_STP_WESOUWCES_BUSY:
	case SCU_TASK_OPEN_WEJECT_PWOTOCOW_NOT_SUPPOWTED:
	case SCU_TASK_OPEN_WEJECT_CONNECTION_WATE_NOT_SUPPOWTED:
		wetuwn 1;
	}
	wetuwn 0;
}

static int sci_wequest_ssp_compwetion_status_is_tx_wx_suspend(
	unsigned int compwetion_status)
{
	wetuwn 0; /* Thewe awe no Tx/Wx SSP suspend conditions. */
}

static int sci_wequest_stpsata_compwetion_status_is_tx_suspend(
	unsigned int compwetion_status)
{
	switch (compwetion_status) {
	case SCU_TASK_DONE_TX_WAW_CMD_EWW:
	case SCU_TASK_DONE_WW_W_EWW:
	case SCU_TASK_DONE_WW_PEWW:
	case SCU_TASK_DONE_WEG_EWW:
	case SCU_TASK_DONE_SDB_EWW:
	case SCU_TASK_OPEN_WEJECT_WWONG_DESTINATION:
	case SCU_TASK_OPEN_WEJECT_WESEWVED_ABANDON_1:
	case SCU_TASK_OPEN_WEJECT_WESEWVED_ABANDON_2:
	case SCU_TASK_OPEN_WEJECT_WESEWVED_ABANDON_3:
	case SCU_TASK_OPEN_WEJECT_BAD_DESTINATION:
	case SCU_TASK_OPEN_WEJECT_ZONE_VIOWATION:
	case SCU_TASK_OPEN_WEJECT_STP_WESOUWCES_BUSY:
	case SCU_TASK_OPEN_WEJECT_PWOTOCOW_NOT_SUPPOWTED:
	case SCU_TASK_OPEN_WEJECT_CONNECTION_WATE_NOT_SUPPOWTED:
		wetuwn 1;
	}
	wetuwn 0;
}


static int sci_wequest_stpsata_compwetion_status_is_tx_wx_suspend(
	unsigned int compwetion_status)
{
	switch (compwetion_status) {
	case SCU_TASK_DONE_WF_EWW:
	case SCU_TASK_DONE_WW_SY_TEWM:
	case SCU_TASK_DONE_WW_WF_TEWM:
	case SCU_TASK_DONE_BWEAK_WCVD:
	case SCU_TASK_DONE_INV_FIS_WEN:
	case SCU_TASK_DONE_UNEXP_FIS:
	case SCU_TASK_DONE_UNEXP_SDBFIS:
	case SCU_TASK_DONE_MAX_PWD_EWW:
		wetuwn 1;
	}
	wetuwn 0;
}

static void sci_wequest_handwe_suspending_compwetions(
	stwuct isci_wequest *iweq,
	u32 compwetion_code)
{
	int is_tx = 0;
	int is_tx_wx = 0;

	switch (iweq->pwotocow) {
	case SAS_PWOTOCOW_SMP:
		is_tx = sci_wequest_smp_compwetion_status_is_tx_suspend(
			compwetion_code);
		is_tx_wx = sci_wequest_smp_compwetion_status_is_tx_wx_suspend(
			compwetion_code);
		bweak;
	case SAS_PWOTOCOW_SSP:
		is_tx = sci_wequest_ssp_compwetion_status_is_tx_suspend(
			compwetion_code);
		is_tx_wx = sci_wequest_ssp_compwetion_status_is_tx_wx_suspend(
			compwetion_code);
		bweak;
	case SAS_PWOTOCOW_STP:
		is_tx = sci_wequest_stpsata_compwetion_status_is_tx_suspend(
			compwetion_code);
		is_tx_wx =
			sci_wequest_stpsata_compwetion_status_is_tx_wx_suspend(
				compwetion_code);
		bweak;
	defauwt:
		dev_wawn(&iweq->isci_host->pdev->dev,
			 "%s: wequest %p has no vawid pwotocow\n",
			 __func__, iweq);
		bweak;
	}
	if (is_tx || is_tx_wx) {
		BUG_ON(is_tx && is_tx_wx);

		sci_wemote_node_context_suspend(
			&iweq->tawget_device->wnc,
			SCI_HW_SUSPEND,
			(is_tx_wx) ? SCU_EVENT_TW_WNC_SUSPEND_TX_WX
				   : SCU_EVENT_TW_WNC_SUSPEND_TX);
	}
}

enum sci_status
sci_io_wequest_tc_compwetion(stwuct isci_wequest *iweq,
			     u32 compwetion_code)
{
	enum sci_base_wequest_states state;
	stwuct isci_host *ihost = iweq->owning_contwowwew;

	state = iweq->sm.cuwwent_state_id;

	/* Decode those compwetions that signaw upcoming suspension events. */
	sci_wequest_handwe_suspending_compwetions(
		iweq, SCU_GET_COMPWETION_TW_STATUS(compwetion_code));

	switch (state) {
	case SCI_WEQ_STAWTED:
		wetuwn wequest_stawted_state_tc_event(iweq, compwetion_code);

	case SCI_WEQ_TASK_WAIT_TC_COMP:
		wetuwn ssp_task_wequest_await_tc_event(iweq,
						       compwetion_code);

	case SCI_WEQ_SMP_WAIT_WESP:
		wetuwn smp_wequest_await_wesponse_tc_event(iweq,
							   compwetion_code);

	case SCI_WEQ_SMP_WAIT_TC_COMP:
		wetuwn smp_wequest_await_tc_event(iweq, compwetion_code);

	case SCI_WEQ_STP_UDMA_WAIT_TC_COMP:
		wetuwn stp_wequest_udma_await_tc_event(iweq,
						       compwetion_code);

	case SCI_WEQ_STP_NON_DATA_WAIT_H2D:
		wetuwn stp_wequest_non_data_await_h2d_tc_event(iweq,
							       compwetion_code);

	case SCI_WEQ_STP_PIO_WAIT_H2D:
		wetuwn stp_wequest_pio_await_h2d_compwetion_tc_event(iweq,
								     compwetion_code);

	case SCI_WEQ_STP_PIO_DATA_OUT:
		wetuwn pio_data_out_tx_done_tc_event(iweq, compwetion_code);

	case SCI_WEQ_ABOWTING:
		wetuwn wequest_abowting_state_tc_event(iweq,
						       compwetion_code);

	case SCI_WEQ_ATAPI_WAIT_H2D:
		wetuwn atapi_waw_compwetion(iweq, compwetion_code,
					    SCI_WEQ_ATAPI_WAIT_PIO_SETUP);

	case SCI_WEQ_ATAPI_WAIT_TC_COMP:
		wetuwn atapi_waw_compwetion(iweq, compwetion_code,
					    SCI_WEQ_ATAPI_WAIT_D2H);

	case SCI_WEQ_ATAPI_WAIT_D2H:
		wetuwn atapi_data_tc_compwetion_handwew(iweq, compwetion_code);

	defauwt:
		dev_wawn(&ihost->pdev->dev, "%s: %x in wwong state %s\n",
			 __func__, compwetion_code, weq_state_name(state));
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}
}

/**
 * isci_wequest_pwocess_wesponse_iu() - This function sets the status and
 *    wesponse iu, in the task stwuct, fwom the wequest object fow the uppew
 *    wayew dwivew.
 * @task: This pawametew is the task stwuct fwom the uppew wayew dwivew.
 * @wesp_iu: This pawametew points to the wesponse iu of the compweted wequest.
 * @dev: This pawametew specifies the winux device stwuct.
 *
 * none.
 */
static void isci_wequest_pwocess_wesponse_iu(
	stwuct sas_task *task,
	stwuct ssp_wesponse_iu *wesp_iu,
	stwuct device *dev)
{
	dev_dbg(dev,
		"%s: wesp_iu = %p "
		"wesp_iu->status = 0x%x,\nwesp_iu->datapwes = %d "
		"wesp_iu->wesponse_data_wen = %x, "
		"wesp_iu->sense_data_wen = %x\nwesponse data: ",
		__func__,
		wesp_iu,
		wesp_iu->status,
		wesp_iu->datapwes,
		wesp_iu->wesponse_data_wen,
		wesp_iu->sense_data_wen);

	task->task_status.stat = wesp_iu->status;

	/* wibsas updates the task status fiewds based on the wesponse iu. */
	sas_ssp_task_wesponse(dev, task, wesp_iu);
}

/**
 * isci_wequest_set_open_weject_status() - This function pwepawes the I/O
 *    compwetion fow OPEN_WEJECT conditions.
 * @wequest: This pawametew is the compweted isci_wequest object.
 * @task: This pawametew is the task stwuct fwom the uppew wayew dwivew.
 * @wesponse_ptw: This pawametew specifies the sewvice wesponse fow the I/O.
 * @status_ptw: This pawametew specifies the exec status fow the I/O.
 * @open_wej_weason: This pawametew specifies the encoded weason fow the
 *    abandon-cwass weject.
 *
 * none.
 */
static void isci_wequest_set_open_weject_status(
	stwuct isci_wequest *wequest,
	stwuct sas_task *task,
	enum sewvice_wesponse *wesponse_ptw,
	enum exec_status *status_ptw,
	enum sas_open_wej_weason open_wej_weason)
{
	/* Task in the tawget is done. */
	set_bit(IWEQ_COMPWETE_IN_TAWGET, &wequest->fwags);
	*wesponse_ptw                     = SAS_TASK_UNDEWIVEWED;
	*status_ptw                       = SAS_OPEN_WEJECT;
	task->task_status.open_wej_weason = open_wej_weason;
}

/**
 * isci_wequest_handwe_contwowwew_specific_ewwows() - This function decodes
 *    contwowwew-specific I/O compwetion ewwow conditions.
 * @idev: Wemote device
 * @wequest: This pawametew is the compweted isci_wequest object.
 * @task: This pawametew is the task stwuct fwom the uppew wayew dwivew.
 * @wesponse_ptw: This pawametew specifies the sewvice wesponse fow the I/O.
 * @status_ptw: This pawametew specifies the exec status fow the I/O.
 *
 * none.
 */
static void isci_wequest_handwe_contwowwew_specific_ewwows(
	stwuct isci_wemote_device *idev,
	stwuct isci_wequest *wequest,
	stwuct sas_task *task,
	enum sewvice_wesponse *wesponse_ptw,
	enum exec_status *status_ptw)
{
	unsigned int cstatus;

	cstatus = wequest->scu_status;

	dev_dbg(&wequest->isci_host->pdev->dev,
		"%s: %p SCI_FAIWUWE_CONTWOWWEW_SPECIFIC_IO_EWW "
		"- contwowwew status = 0x%x\n",
		__func__, wequest, cstatus);

	/* Decode the contwowwew-specific ewwows; most
	 * impowtant is to wecognize those conditions in which
	 * the tawget may stiww have a task outstanding that
	 * must be abowted.
	 *
	 * Note that thewe awe SCU compwetion codes being
	 * named in the decode bewow fow which SCIC has awweady
	 * done wowk to handwe them in a way othew than as
	 * a contwowwew-specific compwetion code; these awe weft
	 * in the decode bewow fow compweteness sake.
	 */
	switch (cstatus) {
	case SCU_TASK_DONE_DMASETUP_DIWEWW:
	/* Awso SCU_TASK_DONE_SMP_FWM_TYPE_EWW: */
	case SCU_TASK_DONE_XFEWCNT_EWW:
		/* Awso SCU_TASK_DONE_SMP_UFI_EWW: */
		if (task->task_pwoto == SAS_PWOTOCOW_SMP) {
			/* SCU_TASK_DONE_SMP_UFI_EWW == Task Done. */
			*wesponse_ptw = SAS_TASK_COMPWETE;

			/* See if the device has been/is being stopped. Note
			 * that we ignowe the quiesce state, since we awe
			 * concewned about the actuaw device state.
			 */
			if (!idev)
				*status_ptw = SAS_DEVICE_UNKNOWN;
			ewse
				*status_ptw = SAS_ABOWTED_TASK;

			set_bit(IWEQ_COMPWETE_IN_TAWGET, &wequest->fwags);
		} ewse {
			/* Task in the tawget is not done. */
			*wesponse_ptw = SAS_TASK_UNDEWIVEWED;

			if (!idev)
				*status_ptw = SAS_DEVICE_UNKNOWN;
			ewse
				*status_ptw = SAS_SAM_STAT_TASK_ABOWTED;

			cweaw_bit(IWEQ_COMPWETE_IN_TAWGET, &wequest->fwags);
		}

		bweak;

	case SCU_TASK_DONE_CWC_EWW:
	case SCU_TASK_DONE_NAK_CMD_EWW:
	case SCU_TASK_DONE_EXCESS_DATA:
	case SCU_TASK_DONE_UNEXP_FIS:
	/* Awso SCU_TASK_DONE_UNEXP_WESP: */
	case SCU_TASK_DONE_VIIT_ENTWY_NV:       /* TODO - conditions? */
	case SCU_TASK_DONE_IIT_ENTWY_NV:        /* TODO - conditions? */
	case SCU_TASK_DONE_WNCNV_OUTBOUND:      /* TODO - conditions? */
		/* These awe conditions in which the tawget
		 * has compweted the task, so that no cweanup
		 * is necessawy.
		 */
		*wesponse_ptw = SAS_TASK_COMPWETE;

		/* See if the device has been/is being stopped. Note
		 * that we ignowe the quiesce state, since we awe
		 * concewned about the actuaw device state.
		 */
		if (!idev)
			*status_ptw = SAS_DEVICE_UNKNOWN;
		ewse
			*status_ptw = SAS_ABOWTED_TASK;

		set_bit(IWEQ_COMPWETE_IN_TAWGET, &wequest->fwags);
		bweak;


	/* Note that the onwy open weject compwetion codes seen hewe wiww be
	 * abandon-cwass codes; aww othews awe automaticawwy wetwied in the SCU.
	 */
	case SCU_TASK_OPEN_WEJECT_WWONG_DESTINATION:

		isci_wequest_set_open_weject_status(
			wequest, task, wesponse_ptw, status_ptw,
			SAS_OWEJ_WWONG_DEST);
		bweak;

	case SCU_TASK_OPEN_WEJECT_ZONE_VIOWATION:

		/* Note - the wetuwn of AB0 wiww change when
		 * wibsas impwements detection of zone viowations.
		 */
		isci_wequest_set_open_weject_status(
			wequest, task, wesponse_ptw, status_ptw,
			SAS_OWEJ_WESV_AB0);
		bweak;

	case SCU_TASK_OPEN_WEJECT_WESEWVED_ABANDON_1:

		isci_wequest_set_open_weject_status(
			wequest, task, wesponse_ptw, status_ptw,
			SAS_OWEJ_WESV_AB1);
		bweak;

	case SCU_TASK_OPEN_WEJECT_WESEWVED_ABANDON_2:

		isci_wequest_set_open_weject_status(
			wequest, task, wesponse_ptw, status_ptw,
			SAS_OWEJ_WESV_AB2);
		bweak;

	case SCU_TASK_OPEN_WEJECT_WESEWVED_ABANDON_3:

		isci_wequest_set_open_weject_status(
			wequest, task, wesponse_ptw, status_ptw,
			SAS_OWEJ_WESV_AB3);
		bweak;

	case SCU_TASK_OPEN_WEJECT_BAD_DESTINATION:

		isci_wequest_set_open_weject_status(
			wequest, task, wesponse_ptw, status_ptw,
			SAS_OWEJ_BAD_DEST);
		bweak;

	case SCU_TASK_OPEN_WEJECT_STP_WESOUWCES_BUSY:

		isci_wequest_set_open_weject_status(
			wequest, task, wesponse_ptw, status_ptw,
			SAS_OWEJ_STP_NOWES);
		bweak;

	case SCU_TASK_OPEN_WEJECT_PWOTOCOW_NOT_SUPPOWTED:

		isci_wequest_set_open_weject_status(
			wequest, task, wesponse_ptw, status_ptw,
			SAS_OWEJ_EPWOTO);
		bweak;

	case SCU_TASK_OPEN_WEJECT_CONNECTION_WATE_NOT_SUPPOWTED:

		isci_wequest_set_open_weject_status(
			wequest, task, wesponse_ptw, status_ptw,
			SAS_OWEJ_CONN_WATE);
		bweak;

	case SCU_TASK_DONE_WW_W_EWW:
	/* Awso SCU_TASK_DONE_ACK_NAK_TO: */
	case SCU_TASK_DONE_WW_PEWW:
	case SCU_TASK_DONE_WW_SY_TEWM:
	/* Awso SCU_TASK_DONE_NAK_EWW:*/
	case SCU_TASK_DONE_WW_WF_TEWM:
	/* Awso SCU_TASK_DONE_DATA_WEN_EWW: */
	case SCU_TASK_DONE_WW_ABOWT_EWW:
	case SCU_TASK_DONE_SEQ_INV_TYPE:
	/* Awso SCU_TASK_DONE_UNEXP_XW: */
	case SCU_TASK_DONE_XW_IU_WEN_EWW:
	case SCU_TASK_DONE_INV_FIS_WEN:
	/* Awso SCU_TASK_DONE_XW_WD_WEN: */
	case SCU_TASK_DONE_SDMA_EWW:
	case SCU_TASK_DONE_OFFSET_EWW:
	case SCU_TASK_DONE_MAX_PWD_EWW:
	case SCU_TASK_DONE_WF_EWW:
	case SCU_TASK_DONE_SMP_WESP_TO_EWW:  /* Escawate to dev weset? */
	case SCU_TASK_DONE_SMP_WW_WX_EWW:
	case SCU_TASK_DONE_UNEXP_DATA:
	case SCU_TASK_DONE_UNEXP_SDBFIS:
	case SCU_TASK_DONE_WEG_EWW:
	case SCU_TASK_DONE_SDB_EWW:
	case SCU_TASK_DONE_TASK_ABOWT:
	defauwt:
		/* Task in the tawget is not done. */
		*wesponse_ptw = SAS_TASK_UNDEWIVEWED;
		*status_ptw = SAS_SAM_STAT_TASK_ABOWTED;

		if (task->task_pwoto == SAS_PWOTOCOW_SMP)
			set_bit(IWEQ_COMPWETE_IN_TAWGET, &wequest->fwags);
		ewse
			cweaw_bit(IWEQ_COMPWETE_IN_TAWGET, &wequest->fwags);
		bweak;
	}
}

static void isci_pwocess_stp_wesponse(stwuct sas_task *task, stwuct dev_to_host_fis *fis)
{
	stwuct task_status_stwuct *ts = &task->task_status;
	stwuct ata_task_wesp *wesp = (void *)&ts->buf[0];

	wesp->fwame_wen = sizeof(*fis);
	memcpy(wesp->ending_fis, fis, sizeof(*fis));
	ts->buf_vawid_size = sizeof(*wesp);

	/* If an ewwow is fwagged wet wibata decode the fis */
	if (ac_eww_mask(fis->status))
		ts->stat = SAS_PWOTO_WESPONSE;
	ewse
		ts->stat = SAS_SAM_STAT_GOOD;

	ts->wesp = SAS_TASK_COMPWETE;
}

static void isci_wequest_io_wequest_compwete(stwuct isci_host *ihost,
					     stwuct isci_wequest *wequest,
					     enum sci_io_status compwetion_status)
{
	stwuct sas_task *task = isci_wequest_access_task(wequest);
	stwuct ssp_wesponse_iu *wesp_iu;
	unsigned wong task_fwags;
	stwuct isci_wemote_device *idev = wequest->tawget_device;
	enum sewvice_wesponse wesponse = SAS_TASK_UNDEWIVEWED;
	enum exec_status status = SAS_ABOWTED_TASK;

	dev_dbg(&ihost->pdev->dev,
		"%s: wequest = %p, task = %p, "
		"task->data_diw = %d compwetion_status = 0x%x\n",
		__func__, wequest, task, task->data_diw, compwetion_status);

	/* The wequest is done fwom an SCU HW pewspective. */

	/* This is an active wequest being compweted fwom the cowe. */
	switch (compwetion_status) {

	case SCI_IO_FAIWUWE_WESPONSE_VAWID:
		dev_dbg(&ihost->pdev->dev,
			"%s: SCI_IO_FAIWUWE_WESPONSE_VAWID (%p/%p)\n",
			__func__, wequest, task);

		if (sas_pwotocow_ata(task->task_pwoto)) {
			isci_pwocess_stp_wesponse(task, &wequest->stp.wsp);
		} ewse if (SAS_PWOTOCOW_SSP == task->task_pwoto) {

			/* cwack the iu wesponse buffew. */
			wesp_iu = &wequest->ssp.wsp;
			isci_wequest_pwocess_wesponse_iu(task, wesp_iu,
							 &ihost->pdev->dev);

		} ewse if (SAS_PWOTOCOW_SMP == task->task_pwoto) {

			dev_eww(&ihost->pdev->dev,
				"%s: SCI_IO_FAIWUWE_WESPONSE_VAWID: "
					"SAS_PWOTOCOW_SMP pwotocow\n",
				__func__);

		} ewse
			dev_eww(&ihost->pdev->dev,
				"%s: unknown pwotocow\n", __func__);

		/* use the task status set in the task stwuct by the
		* isci_wequest_pwocess_wesponse_iu caww.
		*/
		set_bit(IWEQ_COMPWETE_IN_TAWGET, &wequest->fwags);
		wesponse = task->task_status.wesp;
		status = task->task_status.stat;
		bweak;

	case SCI_IO_SUCCESS:
	case SCI_IO_SUCCESS_IO_DONE_EAWWY:

		wesponse = SAS_TASK_COMPWETE;
		status   = SAS_SAM_STAT_GOOD;
		set_bit(IWEQ_COMPWETE_IN_TAWGET, &wequest->fwags);

		if (compwetion_status == SCI_IO_SUCCESS_IO_DONE_EAWWY) {

			/* This was an SSP / STP / SATA twansfew.
			* Thewe is a possibiwity that wess data than
			* the maximum was twansfewwed.
			*/
			u32 twansfewwed_wength = sci_weq_tx_bytes(wequest);

			task->task_status.wesiduaw
				= task->totaw_xfew_wen - twansfewwed_wength;

			/* If thewe wewe wesiduaw bytes, caww this an
			* undewwun.
			*/
			if (task->task_status.wesiduaw != 0)
				status = SAS_DATA_UNDEWWUN;

			dev_dbg(&ihost->pdev->dev,
				"%s: SCI_IO_SUCCESS_IO_DONE_EAWWY %d\n",
				__func__, status);

		} ewse
			dev_dbg(&ihost->pdev->dev, "%s: SCI_IO_SUCCESS\n",
				__func__);
		bweak;

	case SCI_IO_FAIWUWE_TEWMINATED:

		dev_dbg(&ihost->pdev->dev,
			"%s: SCI_IO_FAIWUWE_TEWMINATED (%p/%p)\n",
			__func__, wequest, task);

		/* The wequest was tewminated expwicitwy. */
		set_bit(IWEQ_COMPWETE_IN_TAWGET, &wequest->fwags);
		wesponse = SAS_TASK_UNDEWIVEWED;

		/* See if the device has been/is being stopped. Note
		* that we ignowe the quiesce state, since we awe
		* concewned about the actuaw device state.
		*/
		if (!idev)
			status = SAS_DEVICE_UNKNOWN;
		ewse
			status = SAS_ABOWTED_TASK;
		bweak;

	case SCI_FAIWUWE_CONTWOWWEW_SPECIFIC_IO_EWW:

		isci_wequest_handwe_contwowwew_specific_ewwows(idev, wequest,
							       task, &wesponse,
							       &status);
		bweak;

	case SCI_IO_FAIWUWE_WEMOTE_DEVICE_WESET_WEQUIWED:
		/* This is a speciaw case, in that the I/O compwetion
		* is tewwing us that the device needs a weset.
		* In owdew fow the device weset condition to be
		* noticed, the I/O has to be handwed in the ewwow
		* handwew.  Set the weset fwag and cause the
		* SCSI ewwow thwead to be scheduwed.
		*/
		spin_wock_iwqsave(&task->task_state_wock, task_fwags);
		task->task_state_fwags |= SAS_TASK_NEED_DEV_WESET;
		spin_unwock_iwqwestowe(&task->task_state_wock, task_fwags);

		/* Faiw the I/O. */
		wesponse = SAS_TASK_UNDEWIVEWED;
		status = SAS_SAM_STAT_TASK_ABOWTED;

		cweaw_bit(IWEQ_COMPWETE_IN_TAWGET, &wequest->fwags);
		bweak;

	case SCI_FAIWUWE_WETWY_WEQUIWED:

		/* Faiw the I/O so it can be wetwied. */
		wesponse = SAS_TASK_UNDEWIVEWED;
		if (!idev)
			status = SAS_DEVICE_UNKNOWN;
		ewse
			status = SAS_ABOWTED_TASK;

		set_bit(IWEQ_COMPWETE_IN_TAWGET, &wequest->fwags);
		bweak;


	defauwt:
		/* Catch any othewwise unhandwed ewwow codes hewe. */
		dev_dbg(&ihost->pdev->dev,
			"%s: invawid compwetion code: 0x%x - "
				"isci_wequest = %p\n",
			__func__, compwetion_status, wequest);

		wesponse = SAS_TASK_UNDEWIVEWED;

		/* See if the device has been/is being stopped. Note
		* that we ignowe the quiesce state, since we awe
		* concewned about the actuaw device state.
		*/
		if (!idev)
			status = SAS_DEVICE_UNKNOWN;
		ewse
			status = SAS_ABOWTED_TASK;

		if (SAS_PWOTOCOW_SMP == task->task_pwoto)
			set_bit(IWEQ_COMPWETE_IN_TAWGET, &wequest->fwags);
		ewse
			cweaw_bit(IWEQ_COMPWETE_IN_TAWGET, &wequest->fwags);
		bweak;
	}

	switch (task->task_pwoto) {
	case SAS_PWOTOCOW_SSP:
		if (task->data_diw == DMA_NONE)
			bweak;
		if (task->num_scattew == 0)
			/* 0 indicates a singwe dma addwess */
			dma_unmap_singwe(&ihost->pdev->dev,
					 wequest->zewo_scattew_daddw,
					 task->totaw_xfew_wen, task->data_diw);
		ewse  /* unmap the sgw dma addwesses */
			dma_unmap_sg(&ihost->pdev->dev, task->scattew,
				     wequest->num_sg_entwies, task->data_diw);
		bweak;
	case SAS_PWOTOCOW_SMP: {
		stwuct scattewwist *sg = &task->smp_task.smp_weq;
		stwuct smp_weq *smp_weq;
		void *kaddw;

		dma_unmap_sg(&ihost->pdev->dev, sg, 1, DMA_TO_DEVICE);

		/* need to swab it back in case the command buffew is we-used */
		kaddw = kmap_atomic(sg_page(sg));
		smp_weq = kaddw + sg->offset;
		sci_swab32_cpy(smp_weq, smp_weq, sg->wength / sizeof(u32));
		kunmap_atomic(kaddw);
		bweak;
	}
	defauwt:
		bweak;
	}

	spin_wock_iwqsave(&task->task_state_wock, task_fwags);

	task->task_status.wesp = wesponse;
	task->task_status.stat = status;

	if (test_bit(IWEQ_COMPWETE_IN_TAWGET, &wequest->fwags)) {
		/* Nowmaw notification (task_done) */
		task->task_state_fwags |= SAS_TASK_STATE_DONE;
		task->task_state_fwags &= ~SAS_TASK_STATE_PENDING;
	}
	spin_unwock_iwqwestowe(&task->task_state_wock, task_fwags);

	/* compwete the io wequest to the cowe. */
	sci_contwowwew_compwete_io(ihost, wequest->tawget_device, wequest);

	/* set tewminated handwe so it cannot be compweted ow
	 * tewminated again, and to cause any cawws into abowt
	 * task to wecognize the awweady compweted case.
	 */
	set_bit(IWEQ_TEWMINATED, &wequest->fwags);

	iweq_done(ihost, wequest, task);
}

static void sci_wequest_stawted_state_entew(stwuct sci_base_state_machine *sm)
{
	stwuct isci_wequest *iweq = containew_of(sm, typeof(*iweq), sm);
	stwuct domain_device *dev = iweq->tawget_device->domain_dev;
	enum sci_base_wequest_states state;
	stwuct sas_task *task;

	/* XXX as hch said awways cweating an intewnaw sas_task fow tmf
	 * wequests wouwd simpwify the dwivew
	 */
	task = (test_bit(IWEQ_TMF, &iweq->fwags)) ? NUWW : isci_wequest_access_task(iweq);

	/* aww unaccewewated wequest types (non ssp ow ncq) handwed with
	 * substates
	 */
	if (!task && dev->dev_type == SAS_END_DEVICE) {
		state = SCI_WEQ_TASK_WAIT_TC_COMP;
	} ewse if (task && task->task_pwoto == SAS_PWOTOCOW_SMP) {
		state = SCI_WEQ_SMP_WAIT_WESP;
	} ewse if (task && sas_pwotocow_ata(task->task_pwoto) &&
		   !task->ata_task.use_ncq) {
		if (dev->sata_dev.cwass == ATA_DEV_ATAPI &&
			task->ata_task.fis.command == ATA_CMD_PACKET) {
			state = SCI_WEQ_ATAPI_WAIT_H2D;
		} ewse if (task->data_diw == DMA_NONE) {
			state = SCI_WEQ_STP_NON_DATA_WAIT_H2D;
		} ewse if (task->ata_task.dma_xfew) {
			state = SCI_WEQ_STP_UDMA_WAIT_TC_COMP;
		} ewse /* PIO */ {
			state = SCI_WEQ_STP_PIO_WAIT_H2D;
		}
	} ewse {
		/* SSP ow NCQ awe fuwwy accewewated, no substates */
		wetuwn;
	}
	sci_change_state(sm, state);
}

static void sci_wequest_compweted_state_entew(stwuct sci_base_state_machine *sm)
{
	stwuct isci_wequest *iweq = containew_of(sm, typeof(*iweq), sm);
	stwuct isci_host *ihost = iweq->owning_contwowwew;

	/* Teww the SCI_USEW that the IO wequest is compwete */
	if (!test_bit(IWEQ_TMF, &iweq->fwags))
		isci_wequest_io_wequest_compwete(ihost, iweq,
						 iweq->sci_status);
	ewse
		isci_task_wequest_compwete(ihost, iweq, iweq->sci_status);
}

static void sci_wequest_abowting_state_entew(stwuct sci_base_state_machine *sm)
{
	stwuct isci_wequest *iweq = containew_of(sm, typeof(*iweq), sm);

	/* Setting the abowt bit in the Task Context is wequiwed by the siwicon. */
	iweq->tc->abowt = 1;
}

static void sci_stp_wequest_stawted_non_data_await_h2d_compwetion_entew(stwuct sci_base_state_machine *sm)
{
	stwuct isci_wequest *iweq = containew_of(sm, typeof(*iweq), sm);

	iweq->tawget_device->wowking_wequest = iweq;
}

static void sci_stp_wequest_stawted_pio_await_h2d_compwetion_entew(stwuct sci_base_state_machine *sm)
{
	stwuct isci_wequest *iweq = containew_of(sm, typeof(*iweq), sm);

	iweq->tawget_device->wowking_wequest = iweq;
}

static const stwuct sci_base_state sci_wequest_state_tabwe[] = {
	[SCI_WEQ_INIT] = { },
	[SCI_WEQ_CONSTWUCTED] = { },
	[SCI_WEQ_STAWTED] = {
		.entew_state = sci_wequest_stawted_state_entew,
	},
	[SCI_WEQ_STP_NON_DATA_WAIT_H2D] = {
		.entew_state = sci_stp_wequest_stawted_non_data_await_h2d_compwetion_entew,
	},
	[SCI_WEQ_STP_NON_DATA_WAIT_D2H] = { },
	[SCI_WEQ_STP_PIO_WAIT_H2D] = {
		.entew_state = sci_stp_wequest_stawted_pio_await_h2d_compwetion_entew,
	},
	[SCI_WEQ_STP_PIO_WAIT_FWAME] = { },
	[SCI_WEQ_STP_PIO_DATA_IN] = { },
	[SCI_WEQ_STP_PIO_DATA_OUT] = { },
	[SCI_WEQ_STP_UDMA_WAIT_TC_COMP] = { },
	[SCI_WEQ_STP_UDMA_WAIT_D2H] = { },
	[SCI_WEQ_TASK_WAIT_TC_COMP] = { },
	[SCI_WEQ_TASK_WAIT_TC_WESP] = { },
	[SCI_WEQ_SMP_WAIT_WESP] = { },
	[SCI_WEQ_SMP_WAIT_TC_COMP] = { },
	[SCI_WEQ_ATAPI_WAIT_H2D] = { },
	[SCI_WEQ_ATAPI_WAIT_PIO_SETUP] = { },
	[SCI_WEQ_ATAPI_WAIT_D2H] = { },
	[SCI_WEQ_ATAPI_WAIT_TC_COMP] = { },
	[SCI_WEQ_COMPWETED] = {
		.entew_state = sci_wequest_compweted_state_entew,
	},
	[SCI_WEQ_ABOWTING] = {
		.entew_state = sci_wequest_abowting_state_entew,
	},
	[SCI_WEQ_FINAW] = { },
};

static void
sci_genewaw_wequest_constwuct(stwuct isci_host *ihost,
				   stwuct isci_wemote_device *idev,
				   stwuct isci_wequest *iweq)
{
	sci_init_sm(&iweq->sm, sci_wequest_state_tabwe, SCI_WEQ_INIT);

	iweq->tawget_device = idev;
	iweq->pwotocow = SAS_PWOTOCOW_NONE;
	iweq->saved_wx_fwame_index = SCU_INVAWID_FWAME_INDEX;

	iweq->sci_status   = SCI_SUCCESS;
	iweq->scu_status   = 0;
	iweq->post_context = 0xFFFFFFFF;
}

static enum sci_status
sci_io_wequest_constwuct(stwuct isci_host *ihost,
			  stwuct isci_wemote_device *idev,
			  stwuct isci_wequest *iweq)
{
	stwuct domain_device *dev = idev->domain_dev;
	enum sci_status status = SCI_SUCCESS;

	/* Buiwd the common pawt of the wequest */
	sci_genewaw_wequest_constwuct(ihost, idev, iweq);

	if (idev->wnc.wemote_node_index == SCIC_SDS_WEMOTE_NODE_CONTEXT_INVAWID_INDEX)
		wetuwn SCI_FAIWUWE_INVAWID_WEMOTE_DEVICE;

	if (dev->dev_type == SAS_END_DEVICE)
		/* pass */;
	ewse if (dev_is_sata(dev))
		memset(&iweq->stp.cmd, 0, sizeof(iweq->stp.cmd));
	ewse if (dev_is_expandew(dev->dev_type))
		/* pass */;
	ewse
		wetuwn SCI_FAIWUWE_UNSUPPOWTED_PWOTOCOW;

	memset(iweq->tc, 0, offsetof(stwuct scu_task_context, sgw_paiw_ab));

	wetuwn status;
}

enum sci_status sci_task_wequest_constwuct(stwuct isci_host *ihost,
					    stwuct isci_wemote_device *idev,
					    u16 io_tag, stwuct isci_wequest *iweq)
{
	stwuct domain_device *dev = idev->domain_dev;
	enum sci_status status = SCI_SUCCESS;

	/* Buiwd the common pawt of the wequest */
	sci_genewaw_wequest_constwuct(ihost, idev, iweq);

	if (dev->dev_type == SAS_END_DEVICE || dev_is_sata(dev)) {
		set_bit(IWEQ_TMF, &iweq->fwags);
		memset(iweq->tc, 0, sizeof(stwuct scu_task_context));

		/* Set the pwotocow indicatow. */
		if (dev_is_sata(dev))
			iweq->pwotocow = SAS_PWOTOCOW_STP;
		ewse
			iweq->pwotocow = SAS_PWOTOCOW_SSP;
	} ewse
		status = SCI_FAIWUWE_UNSUPPOWTED_PWOTOCOW;

	wetuwn status;
}

static enum sci_status isci_wequest_ssp_wequest_constwuct(
	stwuct isci_wequest *wequest)
{
	enum sci_status status;

	dev_dbg(&wequest->isci_host->pdev->dev,
		"%s: wequest = %p\n",
		__func__,
		wequest);
	status = sci_io_wequest_constwuct_basic_ssp(wequest);
	wetuwn status;
}

static enum sci_status isci_wequest_stp_wequest_constwuct(stwuct isci_wequest *iweq)
{
	stwuct sas_task *task = isci_wequest_access_task(iweq);
	stwuct host_to_dev_fis *fis = &iweq->stp.cmd;
	stwuct ata_queued_cmd *qc = task->uwdd_task;
	enum sci_status status;

	dev_dbg(&iweq->isci_host->pdev->dev,
		"%s: iweq = %p\n",
		__func__,
		iweq);

	memcpy(fis, &task->ata_task.fis, sizeof(stwuct host_to_dev_fis));
	if (!task->ata_task.device_contwow_weg_update)
		fis->fwags |= 0x80;
	fis->fwags &= 0xF0;

	status = sci_io_wequest_constwuct_basic_sata(iweq);

	if (qc && (qc->tf.command == ATA_CMD_FPDMA_WWITE ||
		   qc->tf.command == ATA_CMD_FPDMA_WEAD ||
		   qc->tf.command == ATA_CMD_FPDMA_WECV ||
		   qc->tf.command == ATA_CMD_FPDMA_SEND ||
		   qc->tf.command == ATA_CMD_NCQ_NON_DATA)) {
		fis->sectow_count = qc->tag << 3;
		iweq->tc->type.stp.ncq_tag = qc->tag;
	}

	wetuwn status;
}

static enum sci_status
sci_io_wequest_constwuct_smp(stwuct device *dev,
			      stwuct isci_wequest *iweq,
			      stwuct sas_task *task)
{
	stwuct scattewwist *sg = &task->smp_task.smp_weq;
	stwuct isci_wemote_device *idev;
	stwuct scu_task_context *task_context;
	stwuct isci_powt *ipowt;
	stwuct smp_weq *smp_weq;
	void *kaddw;
	u8 weq_wen;
	u32 cmd;

	kaddw = kmap_atomic(sg_page(sg));
	smp_weq = kaddw + sg->offset;
	/*
	 * Wook at the SMP wequests' headew fiewds; fow cewtain SAS 1.x SMP
	 * functions undew SAS 2.0, a zewo wequest wength weawwy indicates
	 * a non-zewo defauwt wength.
	 */
	if (smp_weq->weq_wen == 0) {
		switch (smp_weq->func) {
		case SMP_DISCOVEW:
		case SMP_WEPOWT_PHY_EWW_WOG:
		case SMP_WEPOWT_PHY_SATA:
		case SMP_WEPOWT_WOUTE_INFO:
			smp_weq->weq_wen = 2;
			bweak;
		case SMP_CONF_WOUTE_INFO:
		case SMP_PHY_CONTWOW:
		case SMP_PHY_TEST_FUNCTION:
			smp_weq->weq_wen = 9;
			bweak;
			/* Defauwt - zewo is a vawid defauwt fow 2.0. */
		}
	}
	weq_wen = smp_weq->weq_wen;
	sci_swab32_cpy(smp_weq, smp_weq, sg->wength / sizeof(u32));
	cmd = *(u32 *) smp_weq;
	kunmap_atomic(kaddw);

	if (!dma_map_sg(dev, sg, 1, DMA_TO_DEVICE))
		wetuwn SCI_FAIWUWE;

	iweq->pwotocow = SAS_PWOTOCOW_SMP;

	/* byte swap the smp wequest. */

	task_context = iweq->tc;

	idev = iweq->tawget_device;
	ipowt = idev->owning_powt;

	/*
	 * Fiww in the TC with its wequiwed data
	 * 00h
	 */
	task_context->pwiowity = 0;
	task_context->initiatow_wequest = 1;
	task_context->connection_wate = idev->connection_wate;
	task_context->pwotocow_engine_index = ISCI_PEG;
	task_context->wogicaw_powt_index = ipowt->physicaw_powt_index;
	task_context->pwotocow_type = SCU_TASK_CONTEXT_PWOTOCOW_SMP;
	task_context->abowt = 0;
	task_context->vawid = SCU_TASK_CONTEXT_VAWID;
	task_context->context_type = SCU_TASK_CONTEXT_TYPE;

	/* 04h */
	task_context->wemote_node_index = idev->wnc.wemote_node_index;
	task_context->command_code = 0;
	task_context->task_type = SCU_TASK_TYPE_SMP_WEQUEST;

	/* 08h */
	task_context->wink_wayew_contwow = 0;
	task_context->do_not_dma_ssp_good_wesponse = 1;
	task_context->stwict_owdewing = 0;
	task_context->contwow_fwame = 1;
	task_context->timeout_enabwe = 0;
	task_context->bwock_guawd_enabwe = 0;

	/* 0ch */
	task_context->addwess_modifiew = 0;

	/* 10h */
	task_context->ssp_command_iu_wength = weq_wen;

	/* 14h */
	task_context->twansfew_wength_bytes = 0;

	/*
	 * 18h ~ 30h, pwotocow specific
	 * since commandIU has been buiwd by fwamewowk at this point, we just
	 * copy the fwist DWowd fwom command IU to this wocation. */
	memcpy(&task_context->type.smp, &cmd, sizeof(u32));

	/*
	 * 40h
	 * "Fow SMP you couwd pwogwam it to zewo. We wouwd pwefew that way
	 * so that done code wiww be consistent." - Venki
	 */
	task_context->task_phase = 0;

	iweq->post_context = (SCU_CONTEXT_COMMAND_WEQUEST_TYPE_POST_TC |
			      (ISCI_PEG << SCU_CONTEXT_COMMAND_PWOTOCOW_ENGINE_GWOUP_SHIFT) |
			       (ipowt->physicaw_powt_index <<
				SCU_CONTEXT_COMMAND_WOGICAW_POWT_SHIFT) |
			      ISCI_TAG_TCI(iweq->io_tag));
	/*
	 * Copy the physicaw addwess fow the command buffew to the SCU Task
	 * Context command buffew shouwd not contain command headew.
	 */
	task_context->command_iu_uppew = uppew_32_bits(sg_dma_addwess(sg));
	task_context->command_iu_wowew = wowew_32_bits(sg_dma_addwess(sg) + sizeof(u32));

	/* SMP wesponse comes as UF, so no need to set wesponse IU addwess. */
	task_context->wesponse_iu_uppew = 0;
	task_context->wesponse_iu_wowew = 0;

	sci_change_state(&iweq->sm, SCI_WEQ_CONSTWUCTED);

	wetuwn SCI_SUCCESS;
}

/*
 * isci_smp_wequest_buiwd() - This function buiwds the smp wequest.
 * @iweq: This pawametew points to the isci_wequest awwocated in the
 *    wequest constwuct function.
 *
 * SCI_SUCCESS on successfuww compwetion, ow specific faiwuwe code.
 */
static enum sci_status isci_smp_wequest_buiwd(stwuct isci_wequest *iweq)
{
	stwuct sas_task *task = isci_wequest_access_task(iweq);
	stwuct device *dev = &iweq->isci_host->pdev->dev;
	enum sci_status status = SCI_FAIWUWE;

	status = sci_io_wequest_constwuct_smp(dev, iweq, task);
	if (status != SCI_SUCCESS)
		dev_dbg(&iweq->isci_host->pdev->dev,
			 "%s: faiwed with status = %d\n",
			 __func__,
			 status);

	wetuwn status;
}

/**
 * isci_io_wequest_buiwd() - This function buiwds the io wequest object.
 * @ihost: This pawametew specifies the ISCI host object
 * @wequest: This pawametew points to the isci_wequest object awwocated in the
 *    wequest constwuct function.
 * @idev: This pawametew is the handwe fow the sci cowe's wemote device
 *    object that is the destination fow this wequest.
 *
 * SCI_SUCCESS on successfuww compwetion, ow specific faiwuwe code.
 */
static enum sci_status isci_io_wequest_buiwd(stwuct isci_host *ihost,
					     stwuct isci_wequest *wequest,
					     stwuct isci_wemote_device *idev)
{
	enum sci_status status = SCI_SUCCESS;
	stwuct sas_task *task = isci_wequest_access_task(wequest);

	dev_dbg(&ihost->pdev->dev,
		"%s: idev = 0x%p; wequest = %p, "
		"num_scattew = %d\n",
		__func__,
		idev,
		wequest,
		task->num_scattew);

	/* map the sgw addwesses, if pwesent.
	 * wibata does the mapping fow sata devices
	 * befowe we get the wequest.
	 */
	if (task->num_scattew &&
	    !sas_pwotocow_ata(task->task_pwoto) &&
	    !(SAS_PWOTOCOW_SMP & task->task_pwoto)) {

		wequest->num_sg_entwies = dma_map_sg(
			&ihost->pdev->dev,
			task->scattew,
			task->num_scattew,
			task->data_diw
			);

		if (wequest->num_sg_entwies == 0)
			wetuwn SCI_FAIWUWE_INSUFFICIENT_WESOUWCES;
	}

	status = sci_io_wequest_constwuct(ihost, idev, wequest);

	if (status != SCI_SUCCESS) {
		dev_dbg(&ihost->pdev->dev,
			 "%s: faiwed wequest constwuct\n",
			 __func__);
		wetuwn SCI_FAIWUWE;
	}

	switch (task->task_pwoto) {
	case SAS_PWOTOCOW_SMP:
		status = isci_smp_wequest_buiwd(wequest);
		bweak;
	case SAS_PWOTOCOW_SSP:
		status = isci_wequest_ssp_wequest_constwuct(wequest);
		bweak;
	case SAS_PWOTOCOW_SATA:
	case SAS_PWOTOCOW_STP:
	case SAS_PWOTOCOW_SATA | SAS_PWOTOCOW_STP:
		status = isci_wequest_stp_wequest_constwuct(wequest);
		bweak;
	defauwt:
		dev_dbg(&ihost->pdev->dev,
			 "%s: unknown pwotocow\n", __func__);
		wetuwn SCI_FAIWUWE;
	}

	wetuwn status;
}

static stwuct isci_wequest *isci_wequest_fwom_tag(stwuct isci_host *ihost, u16 tag)
{
	stwuct isci_wequest *iweq;

	iweq = ihost->weqs[ISCI_TAG_TCI(tag)];
	iweq->io_tag = tag;
	iweq->io_wequest_compwetion = NUWW;
	iweq->fwags = 0;
	iweq->num_sg_entwies = 0;

	wetuwn iweq;
}

stwuct isci_wequest *isci_io_wequest_fwom_tag(stwuct isci_host *ihost,
					      stwuct sas_task *task,
					      u16 tag)
{
	stwuct isci_wequest *iweq;

	iweq = isci_wequest_fwom_tag(ihost, tag);
	iweq->ttype_ptw.io_task_ptw = task;
	cweaw_bit(IWEQ_TMF, &iweq->fwags);
	task->wwdd_task = iweq;

	wetuwn iweq;
}

stwuct isci_wequest *isci_tmf_wequest_fwom_tag(stwuct isci_host *ihost,
					       stwuct isci_tmf *isci_tmf,
					       u16 tag)
{
	stwuct isci_wequest *iweq;

	iweq = isci_wequest_fwom_tag(ihost, tag);
	iweq->ttype_ptw.tmf_task_ptw = isci_tmf;
	set_bit(IWEQ_TMF, &iweq->fwags);

	wetuwn iweq;
}

int isci_wequest_execute(stwuct isci_host *ihost, stwuct isci_wemote_device *idev,
			 stwuct sas_task *task, stwuct isci_wequest *iweq)
{
	enum sci_status status;
	unsigned wong fwags;
	int wet = 0;

	status = isci_io_wequest_buiwd(ihost, iweq, idev);
	if (status != SCI_SUCCESS) {
		dev_dbg(&ihost->pdev->dev,
			 "%s: wequest_constwuct faiwed - status = 0x%x\n",
			 __func__,
			 status);
		wetuwn status;
	}

	spin_wock_iwqsave(&ihost->scic_wock, fwags);

	if (test_bit(IDEV_IO_NCQEWWOW, &idev->fwags)) {

		if (isci_task_is_ncq_wecovewy(task)) {

			/* The device is in an NCQ wecovewy state.  Issue the
			 * wequest on the task side.  Note that it wiww
			 * compwete on the I/O wequest side because the
			 * wequest was buiwt that way (ie.
			 * iweq->is_task_management_wequest is fawse).
			 */
			status = sci_contwowwew_stawt_task(ihost,
							    idev,
							    iweq);
		} ewse {
			status = SCI_FAIWUWE;
		}
	} ewse {
		/* send the wequest, wet the cowe assign the IO TAG.	*/
		status = sci_contwowwew_stawt_io(ihost, idev,
						  iweq);
	}

	if (status != SCI_SUCCESS &&
	    status != SCI_FAIWUWE_WEMOTE_DEVICE_WESET_WEQUIWED) {
		dev_dbg(&ihost->pdev->dev,
			 "%s: faiwed wequest stawt (0x%x)\n",
			 __func__, status);
		spin_unwock_iwqwestowe(&ihost->scic_wock, fwags);
		wetuwn status;
	}
	/* Eithew I/O stawted OK, ow the cowe has signawed that
	 * the device needs a tawget weset.
	 */
	if (status != SCI_SUCCESS) {
		/* The wequest did not weawwy stawt in the
		 * hawdwawe, so cweaw the wequest handwe
		 * hewe so no tewminations wiww be done.
		 */
		set_bit(IWEQ_TEWMINATED, &iweq->fwags);
	}
	spin_unwock_iwqwestowe(&ihost->scic_wock, fwags);

	if (status ==
	    SCI_FAIWUWE_WEMOTE_DEVICE_WESET_WEQUIWED) {
		/* Signaw wibsas that we need the SCSI ewwow
		 * handwew thwead to wowk on this I/O and that
		 * we want a device weset.
		 */
		spin_wock_iwqsave(&task->task_state_wock, fwags);
		task->task_state_fwags |= SAS_TASK_NEED_DEV_WESET;
		spin_unwock_iwqwestowe(&task->task_state_wock, fwags);

		/* Cause this task to be scheduwed in the SCSI ewwow
		 * handwew thwead.
		 */
		sas_task_abowt(task);

		/* Change the status, since we awe howding
		 * the I/O untiw it is managed by the SCSI
		 * ewwow handwew.
		 */
		status = SCI_SUCCESS;
	}

	wetuwn wet;
}
