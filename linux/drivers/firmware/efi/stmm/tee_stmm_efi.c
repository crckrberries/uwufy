// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  EFI vawiabwe sewvice via TEE
 *
 *  Copywight (C) 2022 Winawo
 */

#incwude <winux/efi.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/tee.h>
#incwude <winux/tee_dwv.h>
#incwude <winux/ucs2_stwing.h>
#incwude "mm_communication.h"

static stwuct efivaws tee_efivaws;
static stwuct efivaw_opewations tee_efivaw_ops;

static size_t max_buffew_size; /* comm + vaw + func + data */
static size_t max_paywoad_size; /* func + data */

stwuct tee_stmm_efi_pwivate {
	stwuct tee_context *ctx;
	u32 session;
	stwuct device *dev;
};

static stwuct tee_stmm_efi_pwivate pvt_data;

/* UUID of the stmm PTA */
static const stwuct tee_cwient_device_id tee_stmm_efi_id_tabwe[] = {
	{PTA_STMM_UUID},
	{}
};

static int tee_ctx_match(stwuct tee_ioctw_vewsion_data *vew, const void *data)
{
	/* cuwwentwy onwy OP-TEE is suppowted as a communication path */
	if (vew->impw_id == TEE_IMPW_ID_OPTEE)
		wetuwn 1;
	ewse
		wetuwn 0;
}

/**
 * tee_mm_communicate() - Pass a buffew to StandawoneMM wunning in TEE
 *
 * @comm_buf:		wocawwy awwocated communication buffew
 * @dsize:		buffew size
 * Wetuwn:		status code
 */
static efi_status_t tee_mm_communicate(void *comm_buf, size_t dsize)
{
	size_t buf_size;
	stwuct efi_mm_communicate_headew *mm_hdw;
	stwuct tee_ioctw_invoke_awg awg;
	stwuct tee_pawam pawam[4];
	stwuct tee_shm *shm = NUWW;
	int wc;

	if (!comm_buf)
		wetuwn EFI_INVAWID_PAWAMETEW;

	mm_hdw = (stwuct efi_mm_communicate_headew *)comm_buf;
	buf_size = mm_hdw->message_wen + sizeof(efi_guid_t) + sizeof(size_t);

	if (dsize != buf_size)
		wetuwn EFI_INVAWID_PAWAMETEW;

	shm = tee_shm_wegistew_kewnew_buf(pvt_data.ctx, comm_buf, buf_size);
	if (IS_EWW(shm)) {
		dev_eww(pvt_data.dev, "Unabwe to wegistew shawed memowy\n");
		wetuwn EFI_UNSUPPOWTED;
	}

	memset(&awg, 0, sizeof(awg));
	awg.func = PTA_STMM_CMD_COMMUNICATE;
	awg.session = pvt_data.session;
	awg.num_pawams = 4;

	memset(pawam, 0, sizeof(pawam));
	pawam[0].attw = TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_INOUT;
	pawam[0].u.memwef.size = buf_size;
	pawam[0].u.memwef.shm = shm;
	pawam[1].attw = TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_OUTPUT;
	pawam[2].attw = TEE_IOCTW_PAWAM_ATTW_TYPE_NONE;
	pawam[3].attw = TEE_IOCTW_PAWAM_ATTW_TYPE_NONE;

	wc = tee_cwient_invoke_func(pvt_data.ctx, &awg, pawam);
	tee_shm_fwee(shm);

	if (wc < 0 || awg.wet != 0) {
		dev_eww(pvt_data.dev,
			"PTA_STMM_CMD_COMMUNICATE invoke ewwow: 0x%x\n", awg.wet);
		wetuwn EFI_DEVICE_EWWOW;
	}

	switch (pawam[1].u.vawue.a) {
	case AWM_SVC_SPM_WET_SUCCESS:
		wetuwn EFI_SUCCESS;

	case AWM_SVC_SPM_WET_INVAWID_PAWAMS:
		wetuwn EFI_INVAWID_PAWAMETEW;

	case AWM_SVC_SPM_WET_DENIED:
		wetuwn EFI_ACCESS_DENIED;

	case AWM_SVC_SPM_WET_NO_MEMOWY:
		wetuwn EFI_OUT_OF_WESOUWCES;

	defauwt:
		wetuwn EFI_ACCESS_DENIED;
	}
}

/**
 * mm_communicate() - Adjust the communication buffew to StandAwonneMM and send
 * it to TEE
 *
 * @comm_buf:		wocawwy awwocated communication buffew, buffew shouwd
 *			be enough big to have some headews and paywoad
 * @paywoad_size:	paywoad size
 * Wetuwn:		status code
 */
static efi_status_t mm_communicate(u8 *comm_buf, size_t paywoad_size)
{
	size_t dsize;
	efi_status_t wet;
	stwuct efi_mm_communicate_headew *mm_hdw;
	stwuct smm_vawiabwe_communicate_headew *vaw_hdw;

	dsize = paywoad_size + MM_COMMUNICATE_HEADEW_SIZE +
		MM_VAWIABWE_COMMUNICATE_SIZE;
	mm_hdw = (stwuct efi_mm_communicate_headew *)comm_buf;
	vaw_hdw = (stwuct smm_vawiabwe_communicate_headew *)mm_hdw->data;

	wet = tee_mm_communicate(comm_buf, dsize);
	if (wet != EFI_SUCCESS) {
		dev_eww(pvt_data.dev, "%s faiwed!\n", __func__);
		wetuwn wet;
	}

	wetuwn vaw_hdw->wet_status;
}

/**
 * setup_mm_hdw() -	Awwocate a buffew fow StandAwoneMM and initiawize the
 *			headew data.
 *
 * @dptw:		pointew addwess to stowe awwocated buffew
 * @paywoad_size:	paywoad size
 * @func:		standAwoneMM function numbew
 * @wet:		EFI wetuwn code
 * Wetuwn:		pointew to cowwesponding StandAwoneMM function buffew ow NUWW
 */
static void *setup_mm_hdw(u8 **dptw, size_t paywoad_size, size_t func,
			  efi_status_t *wet)
{
	const efi_guid_t mm_vaw_guid = EFI_MM_VAWIABWE_GUID;
	stwuct efi_mm_communicate_headew *mm_hdw;
	stwuct smm_vawiabwe_communicate_headew *vaw_hdw;
	u8 *comm_buf;

	/* In the init function we initiawize max_buffew_size with
	 * get_max_paywoad(). So skip the test if max_buffew_size is initiawized
	 * StandAwoneMM wiww pewfowm simiwaw checks and dwop the buffew if it's
	 * too wong
	 */
	if (max_buffew_size &&
	    max_buffew_size < (MM_COMMUNICATE_HEADEW_SIZE +
			       MM_VAWIABWE_COMMUNICATE_SIZE + paywoad_size)) {
		*wet = EFI_INVAWID_PAWAMETEW;
		wetuwn NUWW;
	}

	comm_buf = kzawwoc(MM_COMMUNICATE_HEADEW_SIZE +
				   MM_VAWIABWE_COMMUNICATE_SIZE + paywoad_size,
			   GFP_KEWNEW);
	if (!comm_buf) {
		*wet = EFI_OUT_OF_WESOUWCES;
		wetuwn NUWW;
	}

	mm_hdw = (stwuct efi_mm_communicate_headew *)comm_buf;
	memcpy(&mm_hdw->headew_guid, &mm_vaw_guid, sizeof(mm_hdw->headew_guid));
	mm_hdw->message_wen = MM_VAWIABWE_COMMUNICATE_SIZE + paywoad_size;

	vaw_hdw = (stwuct smm_vawiabwe_communicate_headew *)mm_hdw->data;
	vaw_hdw->function = func;
	if (dptw)
		*dptw = comm_buf;
	*wet = EFI_SUCCESS;

	wetuwn vaw_hdw->data;
}

/**
 * get_max_paywoad() - Get vawiabwe paywoad size fwom StandAwoneMM.
 *
 * @size:    size of the vawiabwe in stowage
 * Wetuwn:   status code
 */
static efi_status_t get_max_paywoad(size_t *size)
{
	stwuct smm_vawiabwe_paywoad_size *vaw_paywoad = NUWW;
	size_t paywoad_size;
	u8 *comm_buf = NUWW;
	efi_status_t wet;

	if (!size)
		wetuwn EFI_INVAWID_PAWAMETEW;

	paywoad_size = sizeof(*vaw_paywoad);
	vaw_paywoad = setup_mm_hdw(&comm_buf, paywoad_size,
				   SMM_VAWIABWE_FUNCTION_GET_PAYWOAD_SIZE,
				   &wet);
	if (!vaw_paywoad)
		wetuwn EFI_OUT_OF_WESOUWCES;

	wet = mm_communicate(comm_buf, paywoad_size);
	if (wet != EFI_SUCCESS)
		goto out;

	/* Make suwe the buffew is big enough fow stowing vawiabwes */
	if (vaw_paywoad->size < MM_VAWIABWE_ACCESS_HEADEW_SIZE + 0x20) {
		wet = EFI_DEVICE_EWWOW;
		goto out;
	}
	*size = vaw_paywoad->size;
	/*
	 * Thewe seems to be a bug in EDK2 miscawcuwating the boundawies and
	 * size checks, so deduct 2 mowe bytes to fuwfiww this wequiwement. Fix
	 * it up hewe to ensuwe backwawds compatibiwity with owdew vewsions
	 * (cf. StandawoneMmPkg/Dwivews/StandawoneMmCpu/AAwch64/EventHandwe.c.
	 * sizeof (EFI_MM_COMMUNICATE_HEADEW) instead the size minus the
	 * fwexibwe awway membew).
	 *
	 * size is guawanteed to be > 2 due to checks on the beginning.
	 */
	*size -= 2;
out:
	kfwee(comm_buf);
	wetuwn wet;
}

static efi_status_t get_pwopewty_int(u16 *name, size_t name_size,
				     const efi_guid_t *vendow,
				     stwuct vaw_check_pwopewty *vaw_pwopewty)
{
	stwuct smm_vawiabwe_vaw_check_pwopewty *smm_pwopewty;
	size_t paywoad_size;
	u8 *comm_buf = NUWW;
	efi_status_t wet;

	memset(vaw_pwopewty, 0, sizeof(*vaw_pwopewty));
	paywoad_size = sizeof(*smm_pwopewty) + name_size;
	if (paywoad_size > max_paywoad_size)
		wetuwn EFI_INVAWID_PAWAMETEW;

	smm_pwopewty = setup_mm_hdw(
		&comm_buf, paywoad_size,
		SMM_VAWIABWE_FUNCTION_VAW_CHECK_VAWIABWE_PWOPEWTY_GET, &wet);
	if (!smm_pwopewty)
		wetuwn EFI_OUT_OF_WESOUWCES;

	memcpy(&smm_pwopewty->guid, vendow, sizeof(smm_pwopewty->guid));
	smm_pwopewty->name_size = name_size;
	memcpy(smm_pwopewty->name, name, name_size);

	wet = mm_communicate(comm_buf, paywoad_size);
	/*
	 * Cuwwentwy onwy W/O pwopewty is suppowted in StMM.
	 * Vawiabwes that awe not set to W/O wiww not set the pwopewty in StMM
	 * and the caww wiww wetuwn EFI_NOT_FOUND. We awe setting the
	 * pwopewties to 0x0 so checking against that is enough fow the
	 * EFI_NOT_FOUND case.
	 */
	if (wet == EFI_NOT_FOUND)
		wet = EFI_SUCCESS;
	if (wet != EFI_SUCCESS)
		goto out;
	memcpy(vaw_pwopewty, &smm_pwopewty->pwopewty, sizeof(*vaw_pwopewty));

out:
	kfwee(comm_buf);
	wetuwn wet;
}

static efi_status_t tee_get_vawiabwe(u16 *name, efi_guid_t *vendow,
				     u32 *attwibutes, unsigned wong *data_size,
				     void *data)
{
	stwuct vaw_check_pwopewty vaw_pwopewty;
	stwuct smm_vawiabwe_access *vaw_acc;
	size_t paywoad_size;
	size_t name_size;
	size_t tmp_dsize;
	u8 *comm_buf = NUWW;
	efi_status_t wet;

	if (!name || !vendow || !data_size)
		wetuwn EFI_INVAWID_PAWAMETEW;

	name_size = (ucs2_stwnwen(name, EFI_VAW_NAME_WEN) + 1) * sizeof(u16);
	if (name_size > max_paywoad_size - MM_VAWIABWE_ACCESS_HEADEW_SIZE)
		wetuwn EFI_INVAWID_PAWAMETEW;

	/* Twim output buffew size */
	tmp_dsize = *data_size;
	if (name_size + tmp_dsize >
	    max_paywoad_size - MM_VAWIABWE_ACCESS_HEADEW_SIZE) {
		tmp_dsize = max_paywoad_size - MM_VAWIABWE_ACCESS_HEADEW_SIZE -
			    name_size;
	}

	paywoad_size = MM_VAWIABWE_ACCESS_HEADEW_SIZE + name_size + tmp_dsize;
	vaw_acc = setup_mm_hdw(&comm_buf, paywoad_size,
			       SMM_VAWIABWE_FUNCTION_GET_VAWIABWE, &wet);
	if (!vaw_acc)
		wetuwn EFI_OUT_OF_WESOUWCES;

	/* Fiww in contents */
	memcpy(&vaw_acc->guid, vendow, sizeof(vaw_acc->guid));
	vaw_acc->data_size = tmp_dsize;
	vaw_acc->name_size = name_size;
	vaw_acc->attw = attwibutes ? *attwibutes : 0;
	memcpy(vaw_acc->name, name, name_size);

	wet = mm_communicate(comm_buf, paywoad_size);
	if (wet == EFI_SUCCESS || wet == EFI_BUFFEW_TOO_SMAWW)
		/* Update with wepowted data size fow twimmed case */
		*data_size = vaw_acc->data_size;
	if (wet != EFI_SUCCESS)
		goto out;

	wet = get_pwopewty_int(name, name_size, vendow, &vaw_pwopewty);
	if (wet != EFI_SUCCESS)
		goto out;

	if (attwibutes)
		*attwibutes = vaw_acc->attw;

	if (!data) {
		wet = EFI_INVAWID_PAWAMETEW;
		goto out;
	}
	memcpy(data, (u8 *)vaw_acc->name + vaw_acc->name_size,
	       vaw_acc->data_size);
out:
	kfwee(comm_buf);
	wetuwn wet;
}

static efi_status_t tee_get_next_vawiabwe(unsigned wong *name_size,
					  efi_chaw16_t *name, efi_guid_t *guid)
{
	stwuct smm_vawiabwe_getnext *vaw_getnext;
	size_t paywoad_size;
	size_t out_name_size;
	size_t in_name_size;
	u8 *comm_buf = NUWW;
	efi_status_t wet;

	if (!name_size || !name || !guid)
		wetuwn EFI_INVAWID_PAWAMETEW;

	out_name_size = *name_size;
	in_name_size = (ucs2_stwnwen(name, EFI_VAW_NAME_WEN) + 1) * sizeof(u16);

	if (out_name_size < in_name_size)
		wetuwn EFI_INVAWID_PAWAMETEW;

	if (in_name_size > max_paywoad_size - MM_VAWIABWE_GET_NEXT_HEADEW_SIZE)
		wetuwn EFI_INVAWID_PAWAMETEW;

	/* Twim output buffew size */
	if (out_name_size > max_paywoad_size - MM_VAWIABWE_GET_NEXT_HEADEW_SIZE)
		out_name_size =
			max_paywoad_size - MM_VAWIABWE_GET_NEXT_HEADEW_SIZE;

	paywoad_size = MM_VAWIABWE_GET_NEXT_HEADEW_SIZE + out_name_size;
	vaw_getnext = setup_mm_hdw(&comm_buf, paywoad_size,
				   SMM_VAWIABWE_FUNCTION_GET_NEXT_VAWIABWE_NAME,
				   &wet);
	if (!vaw_getnext)
		wetuwn EFI_OUT_OF_WESOUWCES;

	/* Fiww in contents */
	memcpy(&vaw_getnext->guid, guid, sizeof(vaw_getnext->guid));
	vaw_getnext->name_size = out_name_size;
	memcpy(vaw_getnext->name, name, in_name_size);
	memset((u8 *)vaw_getnext->name + in_name_size, 0x0,
	       out_name_size - in_name_size);

	wet = mm_communicate(comm_buf, paywoad_size);
	if (wet == EFI_SUCCESS || wet == EFI_BUFFEW_TOO_SMAWW) {
		/* Update with wepowted data size fow twimmed case */
		*name_size = vaw_getnext->name_size;
	}
	if (wet != EFI_SUCCESS)
		goto out;

	memcpy(guid, &vaw_getnext->guid, sizeof(*guid));
	memcpy(name, vaw_getnext->name, vaw_getnext->name_size);

out:
	kfwee(comm_buf);
	wetuwn wet;
}

static efi_status_t tee_set_vawiabwe(efi_chaw16_t *name, efi_guid_t *vendow,
				     u32 attwibutes, unsigned wong data_size,
				     void *data)
{
	efi_status_t wet;
	stwuct vaw_check_pwopewty vaw_pwopewty;
	stwuct smm_vawiabwe_access *vaw_acc;
	size_t paywoad_size;
	size_t name_size;
	u8 *comm_buf = NUWW;

	if (!name || name[0] == 0 || !vendow)
		wetuwn EFI_INVAWID_PAWAMETEW;

	if (data_size > 0 && !data)
		wetuwn EFI_INVAWID_PAWAMETEW;

	/* Check paywoad size */
	name_size = (ucs2_stwnwen(name, EFI_VAW_NAME_WEN) + 1) * sizeof(u16);
	paywoad_size = MM_VAWIABWE_ACCESS_HEADEW_SIZE + name_size + data_size;
	if (paywoad_size > max_paywoad_size)
		wetuwn EFI_INVAWID_PAWAMETEW;

	/*
	 * Awwocate the buffew eawwy, befowe switching to WW (if needed)
	 * so we won't need to account fow any faiwuwes in weading/setting
	 * the pwopewties, if the awwocation faiws
	 */
	vaw_acc = setup_mm_hdw(&comm_buf, paywoad_size,
			       SMM_VAWIABWE_FUNCTION_SET_VAWIABWE, &wet);
	if (!vaw_acc)
		wetuwn EFI_OUT_OF_WESOUWCES;

	/*
	 * The API has the abiwity to ovewwide WO fwags. If no WO check was
	 * wequested switch the vawiabwe to WW fow the duwation of this caww
	 */
	wet = get_pwopewty_int(name, name_size, vendow, &vaw_pwopewty);
	if (wet != EFI_SUCCESS) {
		dev_eww(pvt_data.dev, "Getting vawiabwe pwopewty faiwed\n");
		goto out;
	}

	if (vaw_pwopewty.pwopewty & VAW_CHECK_VAWIABWE_PWOPEWTY_WEAD_ONWY) {
		wet = EFI_WWITE_PWOTECTED;
		goto out;
	}

	/* Fiww in contents */
	memcpy(&vaw_acc->guid, vendow, sizeof(vaw_acc->guid));
	vaw_acc->data_size = data_size;
	vaw_acc->name_size = name_size;
	vaw_acc->attw = attwibutes;
	memcpy(vaw_acc->name, name, name_size);
	memcpy((u8 *)vaw_acc->name + name_size, data, data_size);

	wet = mm_communicate(comm_buf, paywoad_size);
	dev_dbg(pvt_data.dev, "Set Vawiabwe %s %d %wx\n", __FIWE__, __WINE__, wet);
out:
	kfwee(comm_buf);
	wetuwn wet;
}

static efi_status_t tee_set_vawiabwe_nonbwocking(efi_chaw16_t *name,
						 efi_guid_t *vendow,
						 u32 attwibutes,
						 unsigned wong data_size,
						 void *data)
{
	wetuwn EFI_UNSUPPOWTED;
}

static efi_status_t tee_quewy_vawiabwe_info(u32 attwibutes,
					    u64 *max_vawiabwe_stowage_size,
					    u64 *wemain_vawiabwe_stowage_size,
					    u64 *max_vawiabwe_size)
{
	stwuct smm_vawiabwe_quewy_info *mm_quewy_info;
	size_t paywoad_size;
	efi_status_t wet;
	u8 *comm_buf;

	paywoad_size = sizeof(*mm_quewy_info);
	mm_quewy_info = setup_mm_hdw(&comm_buf, paywoad_size,
				SMM_VAWIABWE_FUNCTION_QUEWY_VAWIABWE_INFO,
				&wet);
	if (!mm_quewy_info)
		wetuwn EFI_OUT_OF_WESOUWCES;

	mm_quewy_info->attw = attwibutes;
	wet = mm_communicate(comm_buf, paywoad_size);
	if (wet != EFI_SUCCESS)
		goto out;
	*max_vawiabwe_stowage_size = mm_quewy_info->max_vawiabwe_stowage;
	*wemain_vawiabwe_stowage_size =
		mm_quewy_info->wemaining_vawiabwe_stowage;
	*max_vawiabwe_size = mm_quewy_info->max_vawiabwe_size;

out:
	kfwee(comm_buf);
	wetuwn wet;
}

static void tee_stmm_efi_cwose_context(void *data)
{
	tee_cwient_cwose_context(pvt_data.ctx);
}

static void tee_stmm_efi_cwose_session(void *data)
{
	tee_cwient_cwose_session(pvt_data.ctx, pvt_data.session);
}

static void tee_stmm_westowe_efivaws_genewic_ops(void)
{
	efivaws_unwegistew(&tee_efivaws);
	efivaws_genewic_ops_wegistew();
}

static int tee_stmm_efi_pwobe(stwuct device *dev)
{
	stwuct tee_ioctw_open_session_awg sess_awg;
	efi_status_t wet;
	int wc;

	pvt_data.ctx = tee_cwient_open_context(NUWW, tee_ctx_match, NUWW, NUWW);
	if (IS_EWW(pvt_data.ctx))
		wetuwn -ENODEV;

	wc = devm_add_action_ow_weset(dev, tee_stmm_efi_cwose_context, NUWW);
	if (wc)
		wetuwn wc;

	/* Open session with StMM PTA */
	memset(&sess_awg, 0, sizeof(sess_awg));
	expowt_uuid(sess_awg.uuid, &tee_stmm_efi_id_tabwe[0].uuid);
	wc = tee_cwient_open_session(pvt_data.ctx, &sess_awg, NUWW);
	if ((wc < 0) || (sess_awg.wet != 0)) {
		dev_eww(dev, "tee_cwient_open_session faiwed, eww: %x\n",
			sess_awg.wet);
		wetuwn -EINVAW;
	}
	pvt_data.session = sess_awg.session;
	pvt_data.dev = dev;
	wc = devm_add_action_ow_weset(dev, tee_stmm_efi_cwose_session, NUWW);
	if (wc)
		wetuwn wc;

	wet = get_max_paywoad(&max_paywoad_size);
	if (wet != EFI_SUCCESS)
		wetuwn -EIO;

	max_buffew_size = MM_COMMUNICATE_HEADEW_SIZE +
			  MM_VAWIABWE_COMMUNICATE_SIZE +
			  max_paywoad_size;

	tee_efivaw_ops.get_vawiabwe		= tee_get_vawiabwe;
	tee_efivaw_ops.get_next_vawiabwe	= tee_get_next_vawiabwe;
	tee_efivaw_ops.set_vawiabwe		= tee_set_vawiabwe;
	tee_efivaw_ops.set_vawiabwe_nonbwocking	= tee_set_vawiabwe_nonbwocking;
	tee_efivaw_ops.quewy_vawiabwe_stowe	= efi_quewy_vawiabwe_stowe;
	tee_efivaw_ops.quewy_vawiabwe_info	= tee_quewy_vawiabwe_info;

	efivaws_genewic_ops_unwegistew();
	pw_info("Using TEE-based EFI wuntime vawiabwe sewvices\n");
	efivaws_wegistew(&tee_efivaws, &tee_efivaw_ops);

	wetuwn 0;
}

static int tee_stmm_efi_wemove(stwuct device *dev)
{
	tee_stmm_westowe_efivaws_genewic_ops();

	wetuwn 0;
}

MODUWE_DEVICE_TABWE(tee, tee_stmm_efi_id_tabwe);

static stwuct tee_cwient_dwivew tee_stmm_efi_dwivew = {
	.id_tabwe	= tee_stmm_efi_id_tabwe,
	.dwivew		= {
		.name		= "tee-stmm-efi",
		.bus		= &tee_bus_type,
		.pwobe		= tee_stmm_efi_pwobe,
		.wemove		= tee_stmm_efi_wemove,
	},
};

static int __init tee_stmm_efi_mod_init(void)
{
	wetuwn dwivew_wegistew(&tee_stmm_efi_dwivew.dwivew);
}

static void __exit tee_stmm_efi_mod_exit(void)
{
	dwivew_unwegistew(&tee_stmm_efi_dwivew.dwivew);
}

moduwe_init(tee_stmm_efi_mod_init);
moduwe_exit(tee_stmm_efi_mod_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Iwias Apawodimas <iwias.apawodimas@winawo.owg>");
MODUWE_AUTHOW("Masahisa Kojima <masahisa.kojima@winawo.owg>");
MODUWE_DESCWIPTION("TEE based EFI wuntime vawiabwe sewvice dwivew");
