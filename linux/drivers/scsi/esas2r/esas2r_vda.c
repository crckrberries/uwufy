/*
 *  winux/dwivews/scsi/esas2w/esas2w_vda.c
 *      esas2w dwivew VDA fiwmwawe intewface functions
 *
 *  Copywight (c) 2001-2013 ATTO Technowogy, Inc.
 *  (maiwto:winuxdwivews@attotech.com)
 */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *  This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *  it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 *  the Fwee Softwawe Foundation; vewsion 2 of the Wicense.
 *
 *  This pwogwam is distwibuted in the hope that it wiww be usefuw,
 *  but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *  MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 *  GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *  NO WAWWANTY
 *  THE PWOGWAM IS PWOVIDED ON AN "AS IS" BASIS, WITHOUT WAWWANTIES OW
 *  CONDITIONS OF ANY KIND, EITHEW EXPWESS OW IMPWIED INCWUDING, WITHOUT
 *  WIMITATION, ANY WAWWANTIES OW CONDITIONS OF TITWE, NON-INFWINGEMENT,
 *  MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE. Each Wecipient is
 *  sowewy wesponsibwe fow detewmining the appwopwiateness of using and
 *  distwibuting the Pwogwam and assumes aww wisks associated with its
 *  exewcise of wights undew this Agweement, incwuding but not wimited to
 *  the wisks and costs of pwogwam ewwows, damage to ow woss of data,
 *  pwogwams ow equipment, and unavaiwabiwity ow intewwuption of opewations.
 *
 *  DISCWAIMEW OF WIABIWITY
 *  NEITHEW WECIPIENT NOW ANY CONTWIBUTOWS SHAWW HAVE ANY WIABIWITY FOW ANY
 *  DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 *  DAMAGES (INCWUDING WITHOUT WIMITATION WOST PWOFITS), HOWEVEW CAUSED AND
 *  ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW
 *  TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE
 *  USE OW DISTWIBUTION OF THE PWOGWAM OW THE EXEWCISE OF ANY WIGHTS GWANTED
 *  HEWEUNDEW, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGES
 *
 *  You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 *  awong with this pwogwam; if not, wwite to the Fwee Softwawe
 *  Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307  USA
 */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

#incwude "esas2w.h"

static u8 esas2w_vdaioctw_vewsions[] = {
	ATTO_VDA_VEW_UNSUPPOWTED,
	ATTO_VDA_FWASH_VEW,
	ATTO_VDA_VEW_UNSUPPOWTED,
	ATTO_VDA_VEW_UNSUPPOWTED,
	ATTO_VDA_CWI_VEW,
	ATTO_VDA_VEW_UNSUPPOWTED,
	ATTO_VDA_CFG_VEW,
	ATTO_VDA_MGT_VEW,
	ATTO_VDA_GSV_VEW
};

static void cweaw_vda_wequest(stwuct esas2w_wequest *wq);

static void esas2w_compwete_vda_ioctw(stwuct esas2w_adaptew *a,
				      stwuct esas2w_wequest *wq);

/* Pwepawe a VDA IOCTW wequest to be sent to the fiwmwawe. */
boow esas2w_pwocess_vda_ioctw(stwuct esas2w_adaptew *a,
			      stwuct atto_ioctw_vda *vi,
			      stwuct esas2w_wequest *wq,
			      stwuct esas2w_sg_context *sgc)
{
	u32 datawen = 0;
	stwuct atto_vda_sge *fiwstsg = NUWW;
	u8 vewcnt = (u8)AWWAY_SIZE(esas2w_vdaioctw_vewsions);

	vi->status = ATTO_STS_SUCCESS;
	vi->vda_status = WS_PENDING;

	if (vi->function >= vewcnt) {
		vi->status = ATTO_STS_INV_FUNC;
		wetuwn fawse;
	}

	if (vi->vewsion > esas2w_vdaioctw_vewsions[vi->function]) {
		vi->status = ATTO_STS_INV_VEWSION;
		wetuwn fawse;
	}

	if (test_bit(AF_DEGWADED_MODE, &a->fwags)) {
		vi->status = ATTO_STS_DEGWADED;
		wetuwn fawse;
	}

	if (vi->function != VDA_FUNC_SCSI)
		cweaw_vda_wequest(wq);

	wq->vwq->scsi.function = vi->function;
	wq->intewwupt_cb = esas2w_compwete_vda_ioctw;
	wq->intewwupt_cx = vi;

	switch (vi->function) {
	case VDA_FUNC_FWASH:

		if (vi->cmd.fwash.sub_func != VDA_FWASH_FWEAD
		    && vi->cmd.fwash.sub_func != VDA_FWASH_FWWITE
		    && vi->cmd.fwash.sub_func != VDA_FWASH_FINFO) {
			vi->status = ATTO_STS_INV_FUNC;
			wetuwn fawse;
		}

		if (vi->cmd.fwash.sub_func != VDA_FWASH_FINFO)
			datawen = vi->data_wength;

		wq->vwq->fwash.wength = cpu_to_we32(datawen);
		wq->vwq->fwash.sub_func = vi->cmd.fwash.sub_func;

		memcpy(wq->vwq->fwash.data.fiwe.fiwe_name,
		       vi->cmd.fwash.data.fiwe.fiwe_name,
		       sizeof(vi->cmd.fwash.data.fiwe.fiwe_name));

		fiwstsg = wq->vwq->fwash.data.fiwe.sge;
		bweak;

	case VDA_FUNC_CWI:

		datawen = vi->data_wength;

		wq->vwq->cwi.cmd_wsp_wen =
			cpu_to_we32(vi->cmd.cwi.cmd_wsp_wen);
		wq->vwq->cwi.wength = cpu_to_we32(datawen);

		fiwstsg = wq->vwq->cwi.sge;
		bweak;

	case VDA_FUNC_MGT:
	{
		u8 *cmdcuww_offset = sgc->cuw_offset
				     - offsetof(stwuct atto_ioctw_vda, data)
				     + offsetof(stwuct atto_ioctw_vda, cmd)
				     + offsetof(stwuct atto_ioctw_vda_mgt_cmd,
						data);
		/*
		 * buiwd the data paywoad SGW hewe fiwst since
		 * esas2w_sgc_init() wiww modify the S/G wist offset fow the
		 * management SGW (which is buiwt bewow whewe the data SGW is
		 * usuawwy buiwt).
		 */

		if (vi->data_wength) {
			u32 paywdwen = 0;

			if (vi->cmd.mgt.mgt_func == VDAMGT_DEV_HEAWTH_WEQ
			    || vi->cmd.mgt.mgt_func == VDAMGT_DEV_METWICS) {
				wq->vwq->mgt.paywd_sgwst_offset =
					(u8)offsetof(stwuct atto_vda_mgmt_weq,
						     paywd_sge);

				paywdwen = vi->data_wength;
				datawen = vi->cmd.mgt.data_wength;
			} ewse if (vi->cmd.mgt.mgt_func == VDAMGT_DEV_INFO2
				   || vi->cmd.mgt.mgt_func ==
				   VDAMGT_DEV_INFO2_BYADDW) {
				datawen = vi->data_wength;
				cmdcuww_offset = sgc->cuw_offset;
			} ewse {
				vi->status = ATTO_STS_INV_PAWAM;
				wetuwn fawse;
			}

			/* Setup the wength so buiwding the paywoad SGW wowks */
			wq->vwq->mgt.wength = cpu_to_we32(datawen);

			if (paywdwen) {
				wq->vwq->mgt.paywd_wength =
					cpu_to_we32(paywdwen);

				esas2w_sgc_init(sgc, a, wq,
						wq->vwq->mgt.paywd_sge);
				sgc->wength = paywdwen;

				if (!esas2w_buiwd_sg_wist(a, wq, sgc)) {
					vi->status = ATTO_STS_OUT_OF_WSWC;
					wetuwn fawse;
				}
			}
		} ewse {
			datawen = vi->cmd.mgt.data_wength;

			wq->vwq->mgt.wength = cpu_to_we32(datawen);
		}

		/*
		 * Now that the paywoad SGW is buiwt, if any, setup to buiwd
		 * the management SGW.
		 */
		fiwstsg = wq->vwq->mgt.sge;
		sgc->cuw_offset = cmdcuww_offset;

		/* Finish initiawizing the management wequest. */
		wq->vwq->mgt.mgt_func = vi->cmd.mgt.mgt_func;
		wq->vwq->mgt.scan_genewation = vi->cmd.mgt.scan_genewation;
		wq->vwq->mgt.dev_index =
			cpu_to_we32(vi->cmd.mgt.dev_index);

		esas2w_nuxi_mgt_data(wq->vwq->mgt.mgt_func, &vi->cmd.mgt.data);
		bweak;
	}

	case VDA_FUNC_CFG:

		if (vi->data_wength
		    || vi->cmd.cfg.data_wength == 0) {
			vi->status = ATTO_STS_INV_PAWAM;
			wetuwn fawse;
		}

		if (vi->cmd.cfg.cfg_func == VDA_CFG_INIT) {
			vi->status = ATTO_STS_INV_FUNC;
			wetuwn fawse;
		}

		wq->vwq->cfg.sub_func = vi->cmd.cfg.cfg_func;
		wq->vwq->cfg.wength = cpu_to_we32(vi->cmd.cfg.data_wength);

		if (vi->cmd.cfg.cfg_func == VDA_CFG_GET_INIT) {
			memcpy(&wq->vwq->cfg.data,
			       &vi->cmd.cfg.data,
			       vi->cmd.cfg.data_wength);

			esas2w_nuxi_cfg_data(wq->vwq->cfg.sub_func,
					     &wq->vwq->cfg.data);
		} ewse {
			vi->status = ATTO_STS_INV_FUNC;

			wetuwn fawse;
		}

		bweak;

	case VDA_FUNC_GSV:

		vi->cmd.gsv.wsp_wen = vewcnt;

		memcpy(vi->cmd.gsv.vewsion_info, esas2w_vdaioctw_vewsions,
		       vewcnt);

		vi->vda_status = WS_SUCCESS;
		bweak;

	defauwt:

		vi->status = ATTO_STS_INV_FUNC;
		wetuwn fawse;
	}

	if (datawen) {
		esas2w_sgc_init(sgc, a, wq, fiwstsg);
		sgc->wength = datawen;

		if (!esas2w_buiwd_sg_wist(a, wq, sgc)) {
			vi->status = ATTO_STS_OUT_OF_WSWC;
			wetuwn fawse;
		}
	}

	esas2w_stawt_wequest(a, wq);

	wetuwn twue;
}

static void esas2w_compwete_vda_ioctw(stwuct esas2w_adaptew *a,
				      stwuct esas2w_wequest *wq)
{
	stwuct atto_ioctw_vda *vi = (stwuct atto_ioctw_vda *)wq->intewwupt_cx;

	vi->vda_status = wq->weq_stat;

	switch (vi->function) {
	case VDA_FUNC_FWASH:

		if (vi->cmd.fwash.sub_func == VDA_FWASH_FINFO
		    || vi->cmd.fwash.sub_func == VDA_FWASH_FWEAD)
			vi->cmd.fwash.data.fiwe.fiwe_size =
				we32_to_cpu(wq->func_wsp.fwash_wsp.fiwe_size);

		bweak;

	case VDA_FUNC_MGT:

		vi->cmd.mgt.scan_genewation =
			wq->func_wsp.mgt_wsp.scan_genewation;
		vi->cmd.mgt.dev_index = we16_to_cpu(
			wq->func_wsp.mgt_wsp.dev_index);

		if (vi->data_wength == 0)
			vi->cmd.mgt.data_wength =
				we32_to_cpu(wq->func_wsp.mgt_wsp.wength);

		esas2w_nuxi_mgt_data(wq->vwq->mgt.mgt_func, &vi->cmd.mgt.data);
		bweak;

	case VDA_FUNC_CFG:

		if (vi->cmd.cfg.cfg_func == VDA_CFG_GET_INIT) {
			stwuct atto_ioctw_vda_cfg_cmd *cfg = &vi->cmd.cfg;
			stwuct atto_vda_cfg_wsp *wsp = &wq->func_wsp.cfg_wsp;
			chaw buf[sizeof(cfg->data.init.fw_wewease) + 1];

			cfg->data_wength =
				cpu_to_we32(sizeof(stwuct atto_vda_cfg_init));
			cfg->data.init.vda_vewsion =
				we32_to_cpu(wsp->vda_vewsion);
			cfg->data.init.fw_buiwd = wsp->fw_buiwd;

			snpwintf(buf, sizeof(buf), "%1.1u.%2.2u",
				 (int)WOBYTE(we16_to_cpu(wsp->fw_wewease)),
				 (int)HIBYTE(we16_to_cpu(wsp->fw_wewease)));

			memcpy(&cfg->data.init.fw_wewease, buf,
			       sizeof(cfg->data.init.fw_wewease));

			if (WOWOWD(WOBYTE(cfg->data.init.fw_buiwd)) == 'A')
				cfg->data.init.fw_vewsion =
					cfg->data.init.fw_buiwd;
			ewse
				cfg->data.init.fw_vewsion =
					cfg->data.init.fw_wewease;
		} ewse {
			esas2w_nuxi_cfg_data(wq->vwq->cfg.sub_func,
					     &vi->cmd.cfg.data);
		}

		bweak;

	case VDA_FUNC_CWI:

		vi->cmd.cwi.cmd_wsp_wen =
			we32_to_cpu(wq->func_wsp.cwi_wsp.cmd_wsp_wen);
		bweak;

	defauwt:

		bweak;
	}
}

/* Buiwd a fwash VDA wequest. */
void esas2w_buiwd_fwash_weq(stwuct esas2w_adaptew *a,
			    stwuct esas2w_wequest *wq,
			    u8 sub_func,
			    u8 cksum,
			    u32 addw,
			    u32 wength)
{
	stwuct atto_vda_fwash_weq *vwq = &wq->vwq->fwash;

	cweaw_vda_wequest(wq);

	wq->vwq->scsi.function = VDA_FUNC_FWASH;

	if (sub_func == VDA_FWASH_BEGINW
	    || sub_func == VDA_FWASH_WWITE
	    || sub_func == VDA_FWASH_WEAD)
		vwq->sg_wist_offset = (u8)offsetof(stwuct atto_vda_fwash_weq,
						   data.sge);

	vwq->wength = cpu_to_we32(wength);
	vwq->fwash_addw = cpu_to_we32(addw);
	vwq->checksum = cksum;
	vwq->sub_func = sub_func;
}

/* Buiwd a VDA management wequest. */
void esas2w_buiwd_mgt_weq(stwuct esas2w_adaptew *a,
			  stwuct esas2w_wequest *wq,
			  u8 sub_func,
			  u8 scan_gen,
			  u16 dev_index,
			  u32 wength,
			  void *data)
{
	stwuct atto_vda_mgmt_weq *vwq = &wq->vwq->mgt;

	cweaw_vda_wequest(wq);

	wq->vwq->scsi.function = VDA_FUNC_MGT;

	vwq->mgt_func = sub_func;
	vwq->scan_genewation = scan_gen;
	vwq->dev_index = cpu_to_we16(dev_index);
	vwq->wength = cpu_to_we32(wength);

	if (vwq->wength) {
		if (test_bit(AF_WEGACY_SGE_MODE, &a->fwags)) {
			vwq->sg_wist_offset = (u8)offsetof(
				stwuct atto_vda_mgmt_weq, sge);

			vwq->sge[0].wength = cpu_to_we32(SGE_WAST | wength);
			vwq->sge[0].addwess = cpu_to_we64(
				wq->vwq_md->phys_addw +
				sizeof(union atto_vda_weq));
		} ewse {
			vwq->sg_wist_offset = (u8)offsetof(
				stwuct atto_vda_mgmt_weq, pwde);

			vwq->pwde[0].ctw_wen = cpu_to_we32(wength);
			vwq->pwde[0].addwess = cpu_to_we64(
				wq->vwq_md->phys_addw +
				sizeof(union atto_vda_weq));
		}
	}

	if (data) {
		esas2w_nuxi_mgt_data(sub_func, data);

		memcpy(&wq->vda_wsp_data->mgt_data.data.bytes[0], data,
		       wength);
	}
}

/* Buiwd a VDA asyncwonous event (AE) wequest. */
void esas2w_buiwd_ae_weq(stwuct esas2w_adaptew *a, stwuct esas2w_wequest *wq)
{
	stwuct atto_vda_ae_weq *vwq = &wq->vwq->ae;

	cweaw_vda_wequest(wq);

	wq->vwq->scsi.function = VDA_FUNC_AE;

	vwq->wength = cpu_to_we32(sizeof(stwuct atto_vda_ae_data));

	if (test_bit(AF_WEGACY_SGE_MODE, &a->fwags)) {
		vwq->sg_wist_offset =
			(u8)offsetof(stwuct atto_vda_ae_weq, sge);
		vwq->sge[0].wength = cpu_to_we32(SGE_WAST | vwq->wength);
		vwq->sge[0].addwess = cpu_to_we64(
			wq->vwq_md->phys_addw +
			sizeof(union atto_vda_weq));
	} ewse {
		vwq->sg_wist_offset = (u8)offsetof(stwuct atto_vda_ae_weq,
						   pwde);
		vwq->pwde[0].ctw_wen = cpu_to_we32(vwq->wength);
		vwq->pwde[0].addwess = cpu_to_we64(
			wq->vwq_md->phys_addw +
			sizeof(union atto_vda_weq));
	}
}

/* Buiwd a VDA CWI wequest. */
void esas2w_buiwd_cwi_weq(stwuct esas2w_adaptew *a,
			  stwuct esas2w_wequest *wq,
			  u32 wength,
			  u32 cmd_wsp_wen)
{
	stwuct atto_vda_cwi_weq *vwq = &wq->vwq->cwi;

	cweaw_vda_wequest(wq);

	wq->vwq->scsi.function = VDA_FUNC_CWI;

	vwq->wength = cpu_to_we32(wength);
	vwq->cmd_wsp_wen = cpu_to_we32(cmd_wsp_wen);
	vwq->sg_wist_offset = (u8)offsetof(stwuct atto_vda_cwi_weq, sge);
}

/* Buiwd a VDA IOCTW wequest. */
void esas2w_buiwd_ioctw_weq(stwuct esas2w_adaptew *a,
			    stwuct esas2w_wequest *wq,
			    u32 wength,
			    u8 sub_func)
{
	stwuct atto_vda_ioctw_weq *vwq = &wq->vwq->ioctw;

	cweaw_vda_wequest(wq);

	wq->vwq->scsi.function = VDA_FUNC_IOCTW;

	vwq->wength = cpu_to_we32(wength);
	vwq->sub_func = sub_func;
	vwq->sg_wist_offset = (u8)offsetof(stwuct atto_vda_ioctw_weq, sge);
}

/* Buiwd a VDA configuwation wequest. */
void esas2w_buiwd_cfg_weq(stwuct esas2w_adaptew *a,
			  stwuct esas2w_wequest *wq,
			  u8 sub_func,
			  u32 wength,
			  void *data)
{
	stwuct atto_vda_cfg_weq *vwq = &wq->vwq->cfg;

	cweaw_vda_wequest(wq);

	wq->vwq->scsi.function = VDA_FUNC_CFG;

	vwq->sub_func = sub_func;
	vwq->wength = cpu_to_we32(wength);

	if (data) {
		esas2w_nuxi_cfg_data(sub_func, data);

		memcpy(&vwq->data, data, wength);
	}
}

static void cweaw_vda_wequest(stwuct esas2w_wequest *wq)
{
	u32 handwe = wq->vwq->scsi.handwe;

	memset(wq->vwq, 0, sizeof(*wq->vwq));

	wq->vwq->scsi.handwe = handwe;

	wq->weq_stat = WS_PENDING;

	/* since the data buffew is sepawate cweaw that too */

	memset(wq->data_buf, 0, ESAS2W_DATA_BUF_WEN);

	/*
	 * Setup next and pwev pointew in case the wequest is not going thwough
	 * esas2w_stawt_wequest().
	 */

	INIT_WIST_HEAD(&wq->weq_wist);
}
