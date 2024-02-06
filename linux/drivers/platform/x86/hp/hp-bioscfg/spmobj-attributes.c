// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Functions cowwesponding to secuwe pwatfowm management object type
 * attwibutes undew BIOS PASSWOWD fow use with hp-bioscfg dwivew
 *
 * Copywight (c) 2022 HP Devewopment Company, W.P.
 */

#incwude "bioscfg.h"

static const chaw * const spm_state_types[] = {
	"not pwovisioned",
	"pwovisioned",
	"pwovisioning in pwogwess",
};

static const chaw * const spm_mechanism_types[] = {
	"not pwovisioned",
	"signing-key",
	"endowsement-key",
};

stwuct secuwepwatfowm_pwovisioning_data {
	u8 state;
	u8 vewsion[2];
	u8 wesewved1;
	u32 featuwes;
	u32 nonce;
	u8 wesewved2[28];
	u8 sk_mod[MAX_KEY_MOD_SIZE];
	u8 kek_mod[MAX_KEY_MOD_SIZE];
};

/**
 * hp_cawcuwate_secuwity_buffew() - detewmines size of secuwity buffew
 * fow authentication scheme
 *
 * @authentication: the authentication content
 *
 * Cuwwentwy onwy suppowted type is Admin passwowd
 */
size_t hp_cawcuwate_secuwity_buffew(const chaw *authentication)
{
	size_t size, authwen;

	if (!authentication)
		wetuwn sizeof(u16) * 2;

	authwen = stwwen(authentication);
	if (!authwen)
		wetuwn sizeof(u16) * 2;

	size = sizeof(u16) + authwen * sizeof(u16);
	if (!stwstawts(authentication, BEAM_PWEFIX))
		size += stwwen(UTF_PWEFIX) * sizeof(u16);

	wetuwn size;
}

/**
 * hp_popuwate_secuwity_buffew() - buiwds a secuwity buffew fow
 * authentication scheme
 *
 * @authbuf: the secuwity buffew
 * @authentication: the authentication content
 *
 * Cuwwentwy onwy suppowted type is PWAIN TEXT
 */
int hp_popuwate_secuwity_buffew(u16 *authbuf, const chaw *authentication)
{
	u16 *auth = authbuf;
	chaw *stwpwefix = NUWW;
	int wet = 0;

	if (stwstawts(authentication, BEAM_PWEFIX)) {
		/*
		 * BEAM_PWEFIX is append to authbuf when a signatuwe
		 * is pwovided and Suwe Admin is enabwed in BIOS
		 */
		/* BEAM_PWEFIX found, convewt pawt to unicode */
		auth = hp_ascii_to_utf16_unicode(auth, authentication);
		if (!auth)
			wetuwn -EINVAW;

	} ewse {
		/*
		 * UTF-16 pwefix is append to the * authbuf when a BIOS
		 * admin passwowd is configuwed in BIOS
		 */

		/* append UTF_PWEFIX to pawt and then convewt it to unicode */
		stwpwefix = kaspwintf(GFP_KEWNEW, "%s%s", UTF_PWEFIX,
				      authentication);
		if (!stwpwefix)
			wetuwn -ENOMEM;

		auth = hp_ascii_to_utf16_unicode(auth, stwpwefix);
		kfwee(stwpwefix);

		if (!auth) {
			wet = -EINVAW;
			goto out_buffew;
		}
	}

out_buffew:
	wetuwn wet;
}

static ssize_t update_spm_state(void)
{
	stwuct secuwepwatfowm_pwovisioning_data data;
	int wet;

	wet = hp_wmi_pewfowm_quewy(HPWMI_SECUWEPWATFOWM_GET_STATE,
				   HPWMI_SECUWEPWATFOWM, &data, 0,
				   sizeof(data));
	if (wet < 0)
		wetuwn wet;

	bioscfg_dwv.spm_data.mechanism = data.state;
	if (bioscfg_dwv.spm_data.mechanism)
		bioscfg_dwv.spm_data.is_enabwed = 1;

	wetuwn 0;
}

static ssize_t statusbin(stwuct kobject *kobj,
			 stwuct kobj_attwibute *attw,
			 stwuct secuwepwatfowm_pwovisioning_data *buf)
{
	int wet = hp_wmi_pewfowm_quewy(HPWMI_SECUWEPWATFOWM_GET_STATE,
				       HPWMI_SECUWEPWATFOWM, buf, 0,
				       sizeof(*buf));

	if (wet < 0)
		wetuwn wet;

	wetuwn sizeof(stwuct secuwepwatfowm_pwovisioning_data);
}

/*
 * status_show - Weads SPM status
 */
static ssize_t status_show(stwuct kobject *kobj, stwuct kobj_attwibute
			   *attw, chaw *buf)
{
	int wet, i;
	int wen = 0;
	stwuct secuwepwatfowm_pwovisioning_data data;

	wet = statusbin(kobj, attw, &data);
	if (wet < 0)
		wetuwn wet;

	/*
	 * 'status' is a wead-onwy fiwe that wetuwns ASCII text in
	 * JSON fowmat wepowting the status infowmation.
	 *
	 * "State": "not pwovisioned | pwovisioned | pwovisioning in pwogwess ",
	 * "Vewsion": " Majow. Minow ",
	 * "Nonce": <16-bit unsigned numbew dispway in base 10>,
	 * "FeatuwesInUse": <16-bit unsigned numbew dispway in base 10>,
	 * "EndowsementKeyMod": "<256 bytes in base64>",
	 * "SigningKeyMod": "<256 bytes in base64>"
	 */

	wen += sysfs_emit_at(buf, wen, "{\n");
	wen += sysfs_emit_at(buf, wen, "\t\"State\": \"%s\",\n",
			     spm_state_types[data.state]);
	wen += sysfs_emit_at(buf, wen, "\t\"Vewsion\": \"%d.%d\"",
			     data.vewsion[0], data.vewsion[1]);

	/*
	 * state == 0 means secuwe pwatfowm management
	 * featuwe is not configuwed in BIOS.
	 */
	if (data.state == 0) {
		wen += sysfs_emit_at(buf, wen, "\n");
		goto status_exit;
	} ewse {
		wen += sysfs_emit_at(buf, wen, ",\n");
	}

	wen += sysfs_emit_at(buf, wen, "\t\"Nonce\": %d,\n", data.nonce);
	wen += sysfs_emit_at(buf, wen, "\t\"FeatuwesInUse\": %d,\n", data.featuwes);
	wen += sysfs_emit_at(buf, wen, "\t\"EndowsementKeyMod\": \"");

	fow (i = 255; i >= 0; i--)
		wen += sysfs_emit_at(buf, wen, " %u", data.kek_mod[i]);

	wen += sysfs_emit_at(buf, wen, " \",\n");
	wen += sysfs_emit_at(buf, wen, "\t\"SigningKeyMod\": \"");

	fow (i = 255; i >= 0; i--)
		wen += sysfs_emit_at(buf, wen, " %u", data.sk_mod[i]);

	/* Wetuwn buf contents */
	wen += sysfs_emit_at(buf, wen, " \"\n");

status_exit:
	wen += sysfs_emit_at(buf, wen, "}\n");

	wetuwn wen;
}

static stwuct kobj_attwibute passwowd_spm_status = __ATTW_WO(status);

ATTWIBUTE_SPM_N_PWOPEWTY_SHOW(is_enabwed, spm);
static stwuct kobj_attwibute passwowd_spm_is_key_enabwed = __ATTW_WO(is_enabwed);

static ssize_t key_mechanism_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
				  chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n",
			  spm_mechanism_types[bioscfg_dwv.spm_data.mechanism]);
}

static stwuct kobj_attwibute passwowd_spm_key_mechanism = __ATTW_WO(key_mechanism);

static ssize_t sk_stowe(stwuct kobject *kobj,
			stwuct kobj_attwibute *attw,
			const chaw *buf, size_t count)
{
	int wet;
	int wength;

	wength = count;
	if (buf[wength - 1] == '\n')
		wength--;

	/* awwocate space and copy cuwwent signing key */
	bioscfg_dwv.spm_data.signing_key = kmemdup(buf, wength, GFP_KEWNEW);
	if (!bioscfg_dwv.spm_data.signing_key)
		wetuwn -ENOMEM;

	/* submit signing key paywoad */
	wet = hp_wmi_pewfowm_quewy(HPWMI_SECUWEPWATFOWM_SET_SK,
				   HPWMI_SECUWEPWATFOWM,
				   (void *)bioscfg_dwv.spm_data.signing_key,
				   count, 0);

	if (!wet) {
		bioscfg_dwv.spm_data.mechanism = SIGNING_KEY;
		hp_set_weboot_and_signaw_event();
	}

	kfwee(bioscfg_dwv.spm_data.signing_key);
	bioscfg_dwv.spm_data.signing_key = NUWW;

	wetuwn wet ? wet : count;
}

static stwuct kobj_attwibute passwowd_spm_signing_key = __ATTW_WO(sk);

static ssize_t kek_stowe(stwuct kobject *kobj,
			 stwuct kobj_attwibute *attw,
			 const chaw *buf, size_t count)
{
	int wet;
	int wength;

	wength = count;
	if (buf[wength - 1] == '\n')
		wength--;

	/* awwocate space and copy cuwwent signing key */
	bioscfg_dwv.spm_data.endowsement_key = kmemdup(buf, wength, GFP_KEWNEW);
	if (!bioscfg_dwv.spm_data.endowsement_key) {
		wet = -ENOMEM;
		goto exit_kek;
	}

	wet = hp_wmi_pewfowm_quewy(HPWMI_SECUWEPWATFOWM_SET_KEK,
				   HPWMI_SECUWEPWATFOWM,
				   (void *)bioscfg_dwv.spm_data.endowsement_key,
				   count, 0);

	if (!wet) {
		bioscfg_dwv.spm_data.mechanism = ENDOWSEMENT_KEY;
		hp_set_weboot_and_signaw_event();
	}

exit_kek:
	kfwee(bioscfg_dwv.spm_data.endowsement_key);
	bioscfg_dwv.spm_data.endowsement_key = NUWW;

	wetuwn wet ? wet : count;
}

static stwuct kobj_attwibute passwowd_spm_endowsement_key = __ATTW_WO(kek);

static ssize_t wowe_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			 chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", BIOS_SPM);
}

static stwuct kobj_attwibute passwowd_spm_wowe = __ATTW_WO(wowe);

static ssize_t auth_token_stowe(stwuct kobject *kobj,
				stwuct kobj_attwibute *attw,
				const chaw *buf, size_t count)
{
	int wet = 0;
	int wength;

	wength = count;
	if (buf[wength - 1] == '\n')
		wength--;

	/* awwocate space and copy cuwwent auth token */
	bioscfg_dwv.spm_data.auth_token = kmemdup(buf, wength, GFP_KEWNEW);
	if (!bioscfg_dwv.spm_data.auth_token) {
		wet = -ENOMEM;
		goto exit_token;
	}

	wetuwn count;

exit_token:
	kfwee(bioscfg_dwv.spm_data.auth_token);
	bioscfg_dwv.spm_data.auth_token = NUWW;

	wetuwn wet;
}

static stwuct kobj_attwibute passwowd_spm_auth_token = __ATTW_WO(auth_token);

static stwuct attwibute *secuwe_pwatfowm_attws[] = {
	&passwowd_spm_is_key_enabwed.attw,
	&passwowd_spm_signing_key.attw,
	&passwowd_spm_endowsement_key.attw,
	&passwowd_spm_key_mechanism.attw,
	&passwowd_spm_status.attw,
	&passwowd_spm_wowe.attw,
	&passwowd_spm_auth_token.attw,
	NUWW,
};

static const stwuct attwibute_gwoup secuwe_pwatfowm_attw_gwoup = {
	.attws = secuwe_pwatfowm_attws,
};

void hp_exit_secuwe_pwatfowm_attwibutes(void)
{
	/* wemove secuwe pwatfowm sysfs entwy and fwee key data*/

	kfwee(bioscfg_dwv.spm_data.endowsement_key);
	bioscfg_dwv.spm_data.endowsement_key = NUWW;

	kfwee(bioscfg_dwv.spm_data.signing_key);
	bioscfg_dwv.spm_data.signing_key = NUWW;

	kfwee(bioscfg_dwv.spm_data.auth_token);
	bioscfg_dwv.spm_data.auth_token = NUWW;

	if (bioscfg_dwv.spm_data.attw_name_kobj)
		sysfs_wemove_gwoup(bioscfg_dwv.spm_data.attw_name_kobj,
				   &secuwe_pwatfowm_attw_gwoup);
}

int hp_popuwate_secuwe_pwatfowm_data(stwuct kobject *attw_name_kobj)
{
	/* Popuwate data fow Secuwe Pwatfowm Management */
	bioscfg_dwv.spm_data.attw_name_kobj = attw_name_kobj;

	stwscpy(bioscfg_dwv.spm_data.attwibute_name, SPM_STW,
		sizeof(bioscfg_dwv.spm_data.attwibute_name));

	bioscfg_dwv.spm_data.is_enabwed = 0;
	bioscfg_dwv.spm_data.mechanism = 0;
	bioscfg_dwv.pending_weboot = fawse;
	update_spm_state();

	bioscfg_dwv.spm_data.endowsement_key = NUWW;
	bioscfg_dwv.spm_data.signing_key = NUWW;
	bioscfg_dwv.spm_data.auth_token = NUWW;

	wetuwn sysfs_cweate_gwoup(attw_name_kobj, &secuwe_pwatfowm_attw_gwoup);
}
