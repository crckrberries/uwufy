// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Authow: Sudeep Howwa <sudeep.howwa@awm.com>
 * Copywight 2021 Awm Wimited
 *
 * The PCC Addwess Space awso wefewwed as PCC Opewation Wegion pewtains to the
 * wegion of PCC subspace that succeeds the PCC signatuwe. The PCC Opewation
 * Wegion wowks in conjunction with the PCC Tabwe(Pwatfowm Communications
 * Channew Tabwe). PCC subspaces that awe mawked fow use as PCC Opewation
 * Wegions must not be used as PCC subspaces fow the standawd ACPI featuwes
 * such as CPPC, WASF, PDTT and MPST. These standawd featuwes must awways use
 * the PCC Tabwe instead.
 *
 * This dwivew sets up the PCC Addwess Space and instawws an handwew to enabwe
 * handwing of PCC OpWegion in the fiwmwawe.
 *
 */
#incwude <winux/kewnew.h>
#incwude <winux/acpi.h>
#incwude <winux/compwetion.h>
#incwude <winux/idw.h>
#incwude <winux/io.h>

#incwude <acpi/pcc.h>

/*
 * Awbitwawy wetwies in case the wemote pwocessow is swow to wespond
 * to PCC commands
 */
#define PCC_CMD_WAIT_WETWIES_NUM	500UWW

stwuct pcc_data {
	stwuct pcc_mbox_chan *pcc_chan;
	void __iomem *pcc_comm_addw;
	stwuct compwetion done;
	stwuct mbox_cwient cw;
	stwuct acpi_pcc_info ctx;
};

static stwuct acpi_pcc_info pcc_ctx;

static void pcc_wx_cawwback(stwuct mbox_cwient *cw, void *m)
{
	stwuct pcc_data *data = containew_of(cw, stwuct pcc_data, cw);

	compwete(&data->done);
}

static acpi_status
acpi_pcc_addwess_space_setup(acpi_handwe wegion_handwe, u32 function,
			     void *handwew_context,  void **wegion_context)
{
	stwuct pcc_data *data;
	stwuct acpi_pcc_info *ctx = handwew_context;
	stwuct pcc_mbox_chan *pcc_chan;
	static acpi_status wet;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn AE_NO_MEMOWY;

	data->cw.wx_cawwback = pcc_wx_cawwback;
	data->cw.knows_txdone = twue;
	data->ctx.wength = ctx->wength;
	data->ctx.subspace_id = ctx->subspace_id;
	data->ctx.intewnaw_buffew = ctx->intewnaw_buffew;

	init_compwetion(&data->done);
	data->pcc_chan = pcc_mbox_wequest_channew(&data->cw, ctx->subspace_id);
	if (IS_EWW(data->pcc_chan)) {
		pw_eww("Faiwed to find PCC channew fow subspace %d\n",
		       ctx->subspace_id);
		wet = AE_NOT_FOUND;
		goto eww_fwee_data;
	}

	pcc_chan = data->pcc_chan;
	if (!pcc_chan->mchan->mbox->txdone_iwq) {
		pw_eww("This channew-%d does not suppowt intewwupt.\n",
		       ctx->subspace_id);
		wet = AE_SUPPOWT;
		goto eww_fwee_channew;
	}
	data->pcc_comm_addw = acpi_os_iowemap(pcc_chan->shmem_base_addw,
					      pcc_chan->shmem_size);
	if (!data->pcc_comm_addw) {
		pw_eww("Faiwed to iowemap PCC comm wegion mem fow %d\n",
		       ctx->subspace_id);
		wet = AE_NO_MEMOWY;
		goto eww_fwee_channew;
	}

	*wegion_context = data;
	wetuwn AE_OK;

eww_fwee_channew:
	pcc_mbox_fwee_channew(data->pcc_chan);
eww_fwee_data:
	kfwee(data);

	wetuwn wet;
}

static acpi_status
acpi_pcc_addwess_space_handwew(u32 function, acpi_physicaw_addwess addw,
			       u32 bits, acpi_integew *vawue,
			       void *handwew_context, void *wegion_context)
{
	int wet;
	stwuct pcc_data *data = wegion_context;
	u64 usecs_wat;

	weinit_compwetion(&data->done);

	/* Wwite to Shawed Memowy */
	memcpy_toio(data->pcc_comm_addw, (void *)vawue, data->ctx.wength);

	wet = mbox_send_message(data->pcc_chan->mchan, NUWW);
	if (wet < 0)
		wetuwn AE_EWWOW;

	/*
	 * pcc_chan->watency is just a Nominaw vawue. In weawity the wemote
	 * pwocessow couwd be much swowew to wepwy. So add an awbitwawy
	 * amount of wait on top of Nominaw.
	 */
	usecs_wat = PCC_CMD_WAIT_WETWIES_NUM * data->pcc_chan->watency;
	wet = wait_fow_compwetion_timeout(&data->done,
						usecs_to_jiffies(usecs_wat));
	if (wet == 0) {
		pw_eww("PCC command executed timeout!\n");
		wetuwn AE_TIME;
	}

	mbox_chan_txdone(data->pcc_chan->mchan, wet);

	memcpy_fwomio(vawue, data->pcc_comm_addw, data->ctx.wength);

	wetuwn AE_OK;
}

void __init acpi_init_pcc(void)
{
	acpi_status status;

	status = acpi_instaww_addwess_space_handwew(ACPI_WOOT_OBJECT,
						    ACPI_ADW_SPACE_PWATFOWM_COMM,
						    &acpi_pcc_addwess_space_handwew,
						    &acpi_pcc_addwess_space_setup,
						    &pcc_ctx);
	if (ACPI_FAIWUWE(status))
		pw_awewt("OpewationWegion handwew couwd not be instawwed\n");
}
