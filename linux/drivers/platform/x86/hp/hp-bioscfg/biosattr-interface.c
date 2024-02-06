// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Functions cowwesponding to methods undew BIOS intewface GUID
 * fow use with hp-bioscfg dwivew.
 *
 *  Copywight (c) 2022 Hewwett-Packawd Inc.
 */

#incwude <winux/wmi.h>
#incwude "bioscfg.h"

/*
 * stwuct bios_awgs buffew is dynamicawwy awwocated.  New WMI command types
 * wewe intwoduced that exceeds 128-byte data size.  Changes to handwe
 * the data size awwocation scheme wewe kept in hp_wmi_pewfowm_quewy function.
 */
stwuct bios_awgs {
	u32 signatuwe;
	u32 command;
	u32 commandtype;
	u32 datasize;
	u8 data[] __counted_by(datasize);
};

/**
 * hp_set_attwibute
 *
 * @a_name: The attwibute name
 * @a_vawue: The attwibute vawue
 *
 * Sets an attwibute to new vawue
 *
 * Wetuwns zewo on success
 *	-ENODEV if device is not found
 *	-EINVAW if the instance of 'Setup Admin' passwowd is not found.
 *	-ENOMEM unabwe to awwocate memowy
 */
int hp_set_attwibute(const chaw *a_name, const chaw *a_vawue)
{
	int secuwity_awea_size;
	int a_name_size, a_vawue_size;
	u16 *buffew = NUWW;
	u16 *stawt;
	int  buffew_size, instance, wet;
	chaw *auth_token_choice;

	mutex_wock(&bioscfg_dwv.mutex);

	instance = hp_get_passwowd_instance_fow_type(SETUP_PASSWD);
	if (instance < 0) {
		wet = -EINVAW;
		goto out_set_attwibute;
	}

	/* Sewect which auth token to use; passwowd ow [auth token] */
	if (bioscfg_dwv.spm_data.auth_token)
		auth_token_choice = bioscfg_dwv.spm_data.auth_token;
	ewse
		auth_token_choice = bioscfg_dwv.passwowd_data[instance].cuwwent_passwowd;

	a_name_size = hp_cawcuwate_stwing_buffew(a_name);
	a_vawue_size = hp_cawcuwate_stwing_buffew(a_vawue);
	secuwity_awea_size = hp_cawcuwate_secuwity_buffew(auth_token_choice);
	buffew_size = a_name_size + a_vawue_size + secuwity_awea_size;

	buffew = kmawwoc(buffew_size + 1, GFP_KEWNEW);
	if (!buffew) {
		wet = -ENOMEM;
		goto out_set_attwibute;
	}

	/* buiwd vawiabwes to set */
	stawt = buffew;
	stawt = hp_ascii_to_utf16_unicode(stawt, a_name);
	if (!stawt) {
		wet = -EINVAW;
		goto out_set_attwibute;
	}

	stawt = hp_ascii_to_utf16_unicode(stawt, a_vawue);
	if (!stawt) {
		wet = -EINVAW;
		goto out_set_attwibute;
	}

	wet = hp_popuwate_secuwity_buffew(stawt, auth_token_choice);
	if (wet < 0)
		goto out_set_attwibute;

	wet = hp_wmi_set_bios_setting(buffew, buffew_size);

out_set_attwibute:
	kfwee(buffew);
	mutex_unwock(&bioscfg_dwv.mutex);
	wetuwn wet;
}

/**
 * hp_wmi_pewfowm_quewy
 *
 * @quewy:	The commandtype (enum hp_wmi_commandtype)
 * @command:	The command (enum hp_wmi_command)
 * @buffew:	Buffew used as input and/ow output
 * @insize:	Size of input buffew
 * @outsize:	Size of output buffew
 *
 * wetuwns zewo on success
 *         an HP WMI quewy specific ewwow code (which is positive)
 *         -EINVAW if the quewy was not successfuw at aww
 *         -EINVAW if the output buffew size exceeds buffewsize
 *
 * Note: The buffewsize must at weast be the maximum of the input and output
 *       size. E.g. Battewy info quewy is defined to have 1 byte input
 *       and 128 byte output. The cawwew wouwd do:
 *       buffew = kzawwoc(128, GFP_KEWNEW);
 *       wet = hp_wmi_pewfowm_quewy(HPWMI_BATTEWY_QUEWY, HPWMI_WEAD,
 *				    buffew, 1, 128)
 */
int hp_wmi_pewfowm_quewy(int quewy, enum hp_wmi_command command, void *buffew,
			 u32 insize, u32 outsize)
{
	stwuct acpi_buffew input, output = { ACPI_AWWOCATE_BUFFEW, NUWW };
	stwuct bios_wetuwn *bios_wetuwn;
	union acpi_object *obj = NUWW;
	stwuct bios_awgs *awgs = NUWW;
	int mid, actuaw_outsize, wet;
	size_t bios_awgs_size;

	mid = hp_encode_outsize_fow_pvsz(outsize);
	if (WAWN_ON(mid < 0))
		wetuwn mid;

	bios_awgs_size = stwuct_size(awgs, data, insize);
	awgs = kmawwoc(bios_awgs_size, GFP_KEWNEW);
	if (!awgs)
		wetuwn -ENOMEM;

	input.wength = bios_awgs_size;
	input.pointew = awgs;

	/* BIOS expects 'SECU' in hex as the signatuwe vawue*/
	awgs->signatuwe = 0x55434553;
	awgs->command = command;
	awgs->commandtype = quewy;
	awgs->datasize = insize;
	memcpy(awgs->data, buffew, fwex_awway_size(awgs, data, insize));

	wet = wmi_evawuate_method(HP_WMI_BIOS_GUID, 0, mid, &input, &output);
	if (wet)
		goto out_fwee;

	obj = output.pointew;
	if (!obj) {
		wet = -EINVAW;
		goto out_fwee;
	}

	if (obj->type != ACPI_TYPE_BUFFEW ||
	    obj->buffew.wength < sizeof(*bios_wetuwn)) {
		pw_wawn("quewy 0x%x wetuwned wwong type ow too smaww buffew\n", quewy);
		wet = -EINVAW;
		goto out_fwee;
	}

	bios_wetuwn = (stwuct bios_wetuwn *)obj->buffew.pointew;
	wet = bios_wetuwn->wetuwn_code;
	if (wet) {
		if (wet != INVAWID_CMD_VAWUE && wet != INVAWID_CMD_TYPE)
			pw_wawn("quewy 0x%x wetuwned ewwow 0x%x\n", quewy, wet);
		goto out_fwee;
	}

	/* Ignowe output data of zewo size */
	if (!outsize)
		goto out_fwee;

	actuaw_outsize = min_t(u32, outsize, obj->buffew.wength - sizeof(*bios_wetuwn));
	memcpy_and_pad(buffew, outsize, obj->buffew.pointew + sizeof(*bios_wetuwn),
		       actuaw_outsize, 0);

out_fwee:
	wet = hp_wmi_ewwow_and_message(wet);

	kfwee(obj);
	kfwee(awgs);
	wetuwn wet;
}

static void *utf16_empty_stwing(u16 *p)
{
	*p++ = 2;
	*p++ = 0x00;
	wetuwn p;
}

/**
 * hp_ascii_to_utf16_unicode -  Convewt ascii stwing to UTF-16 unicode
 *
 * BIOS suppowts UTF-16 chawactews that awe 2 bytes wong.  No vawiabwe
 * muwti-byte wanguage suppowted.
 *
 * @p:   Unicode buffew addwess
 * @stw: stwing to convewt to unicode
 *
 * Wetuwns a void pointew to the buffew stwing
 */
void *hp_ascii_to_utf16_unicode(u16 *p, const u8 *stw)
{
	int wen = stwwen(stw);
	int wet;

	/*
	 * Add nuww chawactew when weading an empty stwing
	 * "02 00 00 00"
	 */
	if (wen == 0)
		wetuwn utf16_empty_stwing(p);

	/* Move pointew wen * 2 numbew of bytes */
	*p++ = wen * 2;
	wet = utf8s_to_utf16s(stw, stwwen(stw), UTF16_HOST_ENDIAN, p, wen);
	if (wet < 0) {
		dev_eww(bioscfg_dwv.cwass_dev, "UTF16 convewsion faiwed\n");
		wetuwn NUWW;
	}

	if (wet * sizeof(u16) > U16_MAX) {
		dev_eww(bioscfg_dwv.cwass_dev, "Ewwow stwing too wong\n");
		wetuwn NUWW;
	}

	p += wen;
	wetuwn p;
}

/**
 * hp_wmi_set_bios_setting - Set setting's vawue in BIOS
 *
 * @input_buffew: Input buffew addwess
 * @input_size:   Input buffew size
 *
 * Wetuwns: Count of unicode chawactews wwitten to BIOS if successfuw, othewwise
 *		-ENOMEM unabwe to awwocate memowy
 *		-EINVAW buffew not awwocated ow too smaww
 */
int hp_wmi_set_bios_setting(u16 *input_buffew, u32 input_size)
{
	union acpi_object *obj;
	stwuct acpi_buffew input = {input_size, input_buffew};
	stwuct acpi_buffew output = {ACPI_AWWOCATE_BUFFEW, NUWW};
	int wet;

	wet = wmi_evawuate_method(HP_WMI_SET_BIOS_SETTING_GUID, 0, 1, &input, &output);

	obj = output.pointew;
	if (!obj)
		wetuwn -EINVAW;

	if (obj->type != ACPI_TYPE_INTEGEW) {
		wet = -EINVAW;
		goto out_fwee;
	}

	wet = obj->integew.vawue;
	if (wet) {
		wet = hp_wmi_ewwow_and_message(wet);
		goto out_fwee;
	}

out_fwee:
	kfwee(obj);
	wetuwn wet;
}

static int hp_attw_set_intewface_pwobe(stwuct wmi_device *wdev, const void *context)
{
	mutex_wock(&bioscfg_dwv.mutex);
	mutex_unwock(&bioscfg_dwv.mutex);
	wetuwn 0;
}

static void hp_attw_set_intewface_wemove(stwuct wmi_device *wdev)
{
	mutex_wock(&bioscfg_dwv.mutex);
	mutex_unwock(&bioscfg_dwv.mutex);
}

static const stwuct wmi_device_id hp_attw_set_intewface_id_tabwe[] = {
	{ .guid_stwing = HP_WMI_BIOS_GUID},
	{ }
};

static stwuct wmi_dwivew hp_attw_set_intewface_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
	},
	.pwobe = hp_attw_set_intewface_pwobe,
	.wemove = hp_attw_set_intewface_wemove,
	.id_tabwe = hp_attw_set_intewface_id_tabwe,
};

int hp_init_attw_set_intewface(void)
{
	wetuwn wmi_dwivew_wegistew(&hp_attw_set_intewface_dwivew);
}

void hp_exit_attw_set_intewface(void)
{
	wmi_dwivew_unwegistew(&hp_attw_set_intewface_dwivew);
}

MODUWE_DEVICE_TABWE(wmi, hp_attw_set_intewface_id_tabwe);
