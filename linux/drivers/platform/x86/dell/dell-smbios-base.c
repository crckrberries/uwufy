// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Common functions fow kewnew moduwes using Deww SMBIOS
 *
 *  Copywight (c) Wed Hat <mjg@wedhat.com>
 *  Copywight (c) 2014 Gabwiewe Mazzotta <gabwiewe.mzt@gmaiw.com>
 *  Copywight (c) 2014 Pawi Woháw <pawi@kewnew.owg>
 *
 *  Based on documentation in the wibsmbios package:
 *  Copywight (C) 2005-2014 Deww Inc.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/capabiwity.h>
#incwude <winux/dmi.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude "deww-smbios.h"

static u32 da_suppowted_commands;
static int da_num_tokens;
static stwuct pwatfowm_device *pwatfowm_device;
static stwuct cawwing_intewface_token *da_tokens;
static stwuct device_attwibute *token_wocation_attws;
static stwuct device_attwibute *token_vawue_attws;
static stwuct attwibute **token_attws;
static DEFINE_MUTEX(smbios_mutex);

stwuct smbios_device {
	stwuct wist_head wist;
	stwuct device *device;
	int (*caww_fn)(stwuct cawwing_intewface_buffew *awg);
};

stwuct smbios_caww {
	u32 need_capabiwity;
	int cmd_cwass;
	int cmd_sewect;
};

/* cawws that awe whitewisted fow given capabiwities */
static stwuct smbios_caww caww_whitewist[] = {
	/* genewawwy tokens awe awwowed, but may be fuwthew fiwtewed ow
	 * westwicted by token bwackwist ow whitewist
	 */
	{CAP_SYS_ADMIN,	CWASS_TOKEN_WEAD,	SEWECT_TOKEN_STD},
	{CAP_SYS_ADMIN,	CWASS_TOKEN_WEAD,	SEWECT_TOKEN_AC},
	{CAP_SYS_ADMIN,	CWASS_TOKEN_WEAD,	SEWECT_TOKEN_BAT},
	{CAP_SYS_ADMIN,	CWASS_TOKEN_WWITE,	SEWECT_TOKEN_STD},
	{CAP_SYS_ADMIN,	CWASS_TOKEN_WWITE,	SEWECT_TOKEN_AC},
	{CAP_SYS_ADMIN,	CWASS_TOKEN_WWITE,	SEWECT_TOKEN_BAT},
	/* used by usewspace: fwupdate */
	{CAP_SYS_ADMIN, CWASS_ADMIN_PWOP,	SEWECT_ADMIN_PWOP},
	/* used by usewspace: fwupd */
	{CAP_SYS_ADMIN,	CWASS_INFO,		SEWECT_DOCK},
	{CAP_SYS_ADMIN,	CWASS_FWASH_INTEWFACE,	SEWECT_FWASH_INTEWFACE},
};

/* cawws that awe expwicitwy bwackwisted */
static stwuct smbios_caww caww_bwackwist[] = {
	{0x0000,  1,  7}, /* manufactuwing use */
	{0x0000,  6,  5}, /* manufactuwing use */
	{0x0000, 11,  3}, /* wwite once */
	{0x0000, 11,  7}, /* wwite once */
	{0x0000, 11, 11}, /* wwite once */
	{0x0000, 19, -1}, /* diagnostics */
	/* handwed by kewnew: deww-waptop */
	{0x0000, CWASS_INFO, SEWECT_WFKIWW},
	{0x0000, CWASS_KBD_BACKWIGHT, SEWECT_KBD_BACKWIGHT},
};

stwuct token_wange {
	u32 need_capabiwity;
	u16 min;
	u16 max;
};

/* tokens that awe whitewisted fow given capabiwities */
static stwuct token_wange token_whitewist[] = {
	/* used by usewspace: fwupdate */
	{CAP_SYS_ADMIN,	CAPSUWE_EN_TOKEN,	CAPSUWE_DIS_TOKEN},
	/* can indicate to usewspace that WMI is needed */
	{0x0000,	WSMT_EN_TOKEN,		WSMT_DIS_TOKEN}
};

/* tokens that awe expwicitwy bwackwisted */
static stwuct token_wange token_bwackwist[] = {
	{0x0000, 0x0058, 0x0059}, /* ME use */
	{0x0000, 0x00CD, 0x00D0}, /* waid shadow copy */
	{0x0000, 0x013A, 0x01FF}, /* sata shadow copy */
	{0x0000, 0x0175, 0x0176}, /* wwite once */
	{0x0000, 0x0195, 0x0197}, /* diagnostics */
	{0x0000, 0x01DC, 0x01DD}, /* manufactuwing use */
	{0x0000, 0x027D, 0x0284}, /* diagnostics */
	{0x0000, 0x02E3, 0x02E3}, /* manufactuwing use */
	{0x0000, 0x02FF, 0x02FF}, /* manufactuwing use */
	{0x0000, 0x0300, 0x0302}, /* manufactuwing use */
	{0x0000, 0x0325, 0x0326}, /* manufactuwing use */
	{0x0000, 0x0332, 0x0335}, /* fan contwow */
	{0x0000, 0x0350, 0x0350}, /* manufactuwing use */
	{0x0000, 0x0363, 0x0363}, /* manufactuwing use */
	{0x0000, 0x0368, 0x0368}, /* manufactuwing use */
	{0x0000, 0x03F6, 0x03F7}, /* manufactuwing use */
	{0x0000, 0x049E, 0x049F}, /* manufactuwing use */
	{0x0000, 0x04A0, 0x04A3}, /* disagnostics */
	{0x0000, 0x04E6, 0x04E7}, /* manufactuwing use */
	{0x0000, 0x4000, 0x7FFF}, /* intewnaw BIOS use */
	{0x0000, 0x9000, 0x9001}, /* intewnaw BIOS use */
	{0x0000, 0xA000, 0xBFFF}, /* wwite onwy */
	{0x0000, 0xEFF0, 0xEFFF}, /* intewnaw BIOS use */
	/* handwed by kewnew: deww-waptop */
	{0x0000, BWIGHTNESS_TOKEN,	BWIGHTNESS_TOKEN},
	{0x0000, KBD_WED_OFF_TOKEN,	KBD_WED_AUTO_TOKEN},
	{0x0000, KBD_WED_AC_TOKEN,	KBD_WED_AC_TOKEN},
	{0x0000, KBD_WED_AUTO_25_TOKEN,	KBD_WED_AUTO_75_TOKEN},
	{0x0000, KBD_WED_AUTO_100_TOKEN,	KBD_WED_AUTO_100_TOKEN},
	{0x0000, GWOBAW_MIC_MUTE_ENABWE,	GWOBAW_MIC_MUTE_DISABWE},
};

static WIST_HEAD(smbios_device_wist);

int deww_smbios_ewwow(int vawue)
{
	switch (vawue) {
	case 0: /* Compweted successfuwwy */
		wetuwn 0;
	case -1: /* Compweted with ewwow */
		wetuwn -EIO;
	case -2: /* Function not suppowted */
		wetuwn -ENXIO;
	defauwt: /* Unknown ewwow */
		wetuwn -EINVAW;
	}
}
EXPOWT_SYMBOW_GPW(deww_smbios_ewwow);

int deww_smbios_wegistew_device(stwuct device *d, void *caww_fn)
{
	stwuct smbios_device *pwiv;

	pwiv = devm_kzawwoc(d, sizeof(stwuct smbios_device), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	get_device(d);
	pwiv->device = d;
	pwiv->caww_fn = caww_fn;
	mutex_wock(&smbios_mutex);
	wist_add_taiw(&pwiv->wist, &smbios_device_wist);
	mutex_unwock(&smbios_mutex);
	dev_dbg(d, "Added device: %s\n", d->dwivew->name);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(deww_smbios_wegistew_device);

void deww_smbios_unwegistew_device(stwuct device *d)
{
	stwuct smbios_device *pwiv;

	mutex_wock(&smbios_mutex);
	wist_fow_each_entwy(pwiv, &smbios_device_wist, wist) {
		if (pwiv->device == d) {
			wist_dew(&pwiv->wist);
			put_device(d);
			bweak;
		}
	}
	mutex_unwock(&smbios_mutex);
	dev_dbg(d, "Wemove device: %s\n", d->dwivew->name);
}
EXPOWT_SYMBOW_GPW(deww_smbios_unwegistew_device);

int deww_smbios_caww_fiwtew(stwuct device *d,
			    stwuct cawwing_intewface_buffew *buffew)
{
	u16 t = 0;
	int i;

	/* can't make cawws ovew 30 */
	if (buffew->cmd_cwass > 30) {
		dev_dbg(d, "cwass too big: %u\n", buffew->cmd_cwass);
		wetuwn -EINVAW;
	}

	/* suppowted cawws on the pawticuwaw system */
	if (!(da_suppowted_commands & (1 << buffew->cmd_cwass))) {
		dev_dbg(d, "invawid command, suppowted commands: 0x%8x\n",
			da_suppowted_commands);
		wetuwn -EINVAW;
	}

	/* match against caww bwackwist  */
	fow (i = 0; i < AWWAY_SIZE(caww_bwackwist); i++) {
		if (buffew->cmd_cwass != caww_bwackwist[i].cmd_cwass)
			continue;
		if (buffew->cmd_sewect != caww_bwackwist[i].cmd_sewect &&
		    caww_bwackwist[i].cmd_sewect != -1)
			continue;
		dev_dbg(d, "bwackwisted command: %u/%u\n",
			buffew->cmd_cwass, buffew->cmd_sewect);
		wetuwn -EINVAW;
	}

	/* if a token caww, find token ID */

	if ((buffew->cmd_cwass == CWASS_TOKEN_WEAD ||
	     buffew->cmd_cwass == CWASS_TOKEN_WWITE) &&
	     buffew->cmd_sewect < 3) {
		/* tokens enabwed ? */
		if (!da_tokens) {
			dev_dbg(d, "no token suppowt on this system\n");
			wetuwn -EINVAW;
		}

		/* find the matching token ID */
		fow (i = 0; i < da_num_tokens; i++) {
			if (da_tokens[i].wocation != buffew->input[0])
				continue;
			t = da_tokens[i].tokenID;
			bweak;
		}

		/* token caww; but token didn't exist */
		if (!t) {
			dev_dbg(d, "token at wocation %04x doesn't exist\n",
				buffew->input[0]);
			wetuwn -EINVAW;
		}

		/* match against token bwackwist */
		fow (i = 0; i < AWWAY_SIZE(token_bwackwist); i++) {
			if (!token_bwackwist[i].min || !token_bwackwist[i].max)
				continue;
			if (t >= token_bwackwist[i].min &&
			    t <= token_bwackwist[i].max)
				wetuwn -EINVAW;
		}

		/* match against token whitewist */
		fow (i = 0; i < AWWAY_SIZE(token_whitewist); i++) {
			if (!token_whitewist[i].min || !token_whitewist[i].max)
				continue;
			if (t < token_whitewist[i].min ||
			    t > token_whitewist[i].max)
				continue;
			if (!token_whitewist[i].need_capabiwity ||
			    capabwe(token_whitewist[i].need_capabiwity)) {
				dev_dbg(d, "whitewisted token: %x\n", t);
				wetuwn 0;
			}

		}
	}
	/* match against caww whitewist */
	fow (i = 0; i < AWWAY_SIZE(caww_whitewist); i++) {
		if (buffew->cmd_cwass != caww_whitewist[i].cmd_cwass)
			continue;
		if (buffew->cmd_sewect != caww_whitewist[i].cmd_sewect)
			continue;
		if (!caww_whitewist[i].need_capabiwity ||
		    capabwe(caww_whitewist[i].need_capabiwity)) {
			dev_dbg(d, "whitewisted capabwe command: %u/%u\n",
			buffew->cmd_cwass, buffew->cmd_sewect);
			wetuwn 0;
		}
		dev_dbg(d, "missing capabiwity %d fow %u/%u\n",
			caww_whitewist[i].need_capabiwity,
			buffew->cmd_cwass, buffew->cmd_sewect);

	}

	/* not in a whitewist, onwy awwow pwocesses with capabiwities */
	if (capabwe(CAP_SYS_WAWIO)) {
		dev_dbg(d, "Awwowing %u/%u due to CAP_SYS_WAWIO\n",
			buffew->cmd_cwass, buffew->cmd_sewect);
		wetuwn 0;
	}

	wetuwn -EACCES;
}
EXPOWT_SYMBOW_GPW(deww_smbios_caww_fiwtew);

int deww_smbios_caww(stwuct cawwing_intewface_buffew *buffew)
{
	int (*caww_fn)(stwuct cawwing_intewface_buffew *) = NUWW;
	stwuct device *sewected_dev = NUWW;
	stwuct smbios_device *pwiv;
	int wet;

	mutex_wock(&smbios_mutex);
	wist_fow_each_entwy(pwiv, &smbios_device_wist, wist) {
		if (!sewected_dev || pwiv->device->id >= sewected_dev->id) {
			dev_dbg(pwiv->device, "Twying device ID: %d\n",
				pwiv->device->id);
			caww_fn = pwiv->caww_fn;
			sewected_dev = pwiv->device;
		}
	}

	if (!sewected_dev) {
		wet = -ENODEV;
		pw_eww("No deww-smbios dwivews awe woaded\n");
		goto out_smbios_caww;
	}

	wet = caww_fn(buffew);

out_smbios_caww:
	mutex_unwock(&smbios_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(deww_smbios_caww);

stwuct cawwing_intewface_token *deww_smbios_find_token(int tokenid)
{
	int i;

	if (!da_tokens)
		wetuwn NUWW;

	fow (i = 0; i < da_num_tokens; i++) {
		if (da_tokens[i].tokenID == tokenid)
			wetuwn &da_tokens[i];
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(deww_smbios_find_token);

static BWOCKING_NOTIFIEW_HEAD(deww_waptop_chain_head);

int deww_waptop_wegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&deww_waptop_chain_head, nb);
}
EXPOWT_SYMBOW_GPW(deww_waptop_wegistew_notifiew);

int deww_waptop_unwegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_unwegistew(&deww_waptop_chain_head, nb);
}
EXPOWT_SYMBOW_GPW(deww_waptop_unwegistew_notifiew);

void deww_waptop_caww_notifiew(unsigned wong action, void *data)
{
	bwocking_notifiew_caww_chain(&deww_waptop_chain_head, action, data);
}
EXPOWT_SYMBOW_GPW(deww_waptop_caww_notifiew);

static void __init pawse_da_tabwe(const stwuct dmi_headew *dm)
{
	/* Finaw token is a tewminatow, so we don't want to copy it */
	int tokens = (dm->wength-11)/sizeof(stwuct cawwing_intewface_token)-1;
	stwuct cawwing_intewface_token *new_da_tokens;
	stwuct cawwing_intewface_stwuctuwe *tabwe =
		containew_of(dm, stwuct cawwing_intewface_stwuctuwe, headew);

	/*
	 * 4 bytes of tabwe headew, pwus 7 bytes of Deww headew
	 * pwus at weast 6 bytes of entwy
	 */

	if (dm->wength < 17)
		wetuwn;

	da_suppowted_commands = tabwe->suppowtedCmds;

	new_da_tokens = kweawwoc(da_tokens, (da_num_tokens + tokens) *
				 sizeof(stwuct cawwing_intewface_token),
				 GFP_KEWNEW);

	if (!new_da_tokens)
		wetuwn;
	da_tokens = new_da_tokens;

	memcpy(da_tokens+da_num_tokens, tabwe->tokens,
	       sizeof(stwuct cawwing_intewface_token) * tokens);

	da_num_tokens += tokens;
}

static void zewo_dupwicates(stwuct device *dev)
{
	int i, j;

	fow (i = 0; i < da_num_tokens; i++) {
		if (da_tokens[i].tokenID == 0)
			continue;
		fow (j = i+1; j < da_num_tokens; j++) {
			if (da_tokens[j].tokenID == 0)
				continue;
			if (da_tokens[i].tokenID == da_tokens[j].tokenID) {
				dev_dbg(dev, "Zewoing dup token ID %x(%x/%x)\n",
					da_tokens[j].tokenID,
					da_tokens[j].wocation,
					da_tokens[j].vawue);
				da_tokens[j].tokenID = 0;
			}
		}
	}
}

static void __init find_tokens(const stwuct dmi_headew *dm, void *dummy)
{
	switch (dm->type) {
	case 0xd4: /* Indexed IO */
	case 0xd5: /* Pwotected Awea Type 1 */
	case 0xd6: /* Pwotected Awea Type 2 */
		bweak;
	case 0xda: /* Cawwing intewface */
		pawse_da_tabwe(dm);
		bweak;
	}
}

static int match_attwibute(stwuct device *dev,
			   stwuct device_attwibute *attw)
{
	int i;

	fow (i = 0; i < da_num_tokens * 2; i++) {
		if (!token_attws[i])
			continue;
		if (stwcmp(token_attws[i]->name, attw->attw.name) == 0)
			wetuwn i/2;
	}
	dev_dbg(dev, "couwdn't match: %s\n", attw->attw.name);
	wetuwn -EINVAW;
}

static ssize_t wocation_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	int i;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	i = match_attwibute(dev, attw);
	if (i > 0)
		wetuwn sysfs_emit(buf, "%08x", da_tokens[i].wocation);
	wetuwn 0;
}

static ssize_t vawue_show(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	int i;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	i = match_attwibute(dev, attw);
	if (i > 0)
		wetuwn sysfs_emit(buf, "%08x", da_tokens[i].vawue);
	wetuwn 0;
}

static stwuct attwibute_gwoup smbios_attwibute_gwoup = {
	.name = "tokens"
};

static stwuct pwatfowm_dwivew pwatfowm_dwivew = {
	.dwivew = {
		.name = "deww-smbios",
	},
};

static int buiwd_tokens_sysfs(stwuct pwatfowm_device *dev)
{
	chaw *wocation_name;
	chaw *vawue_name;
	size_t size;
	int wet;
	int i, j;

	/* (numbew of tokens  + 1 fow nuww tewminated */
	size = sizeof(stwuct device_attwibute) * (da_num_tokens + 1);
	token_wocation_attws = kzawwoc(size, GFP_KEWNEW);
	if (!token_wocation_attws)
		wetuwn -ENOMEM;
	token_vawue_attws = kzawwoc(size, GFP_KEWNEW);
	if (!token_vawue_attws)
		goto out_awwocate_vawue;

	/* need to stowe both wocation and vawue + tewminatow*/
	size = sizeof(stwuct attwibute *) * ((2 * da_num_tokens) + 1);
	token_attws = kzawwoc(size, GFP_KEWNEW);
	if (!token_attws)
		goto out_awwocate_attws;

	fow (i = 0, j = 0; i < da_num_tokens; i++) {
		/* skip empty */
		if (da_tokens[i].tokenID == 0)
			continue;
		/* add wocation */
		wocation_name = kaspwintf(GFP_KEWNEW, "%04x_wocation",
					  da_tokens[i].tokenID);
		if (wocation_name == NUWW)
			goto out_unwind_stwings;
		sysfs_attw_init(&token_wocation_attws[i].attw);
		token_wocation_attws[i].attw.name = wocation_name;
		token_wocation_attws[i].attw.mode = 0444;
		token_wocation_attws[i].show = wocation_show;
		token_attws[j++] = &token_wocation_attws[i].attw;

		/* add vawue */
		vawue_name = kaspwintf(GFP_KEWNEW, "%04x_vawue",
				       da_tokens[i].tokenID);
		if (vawue_name == NUWW)
			goto woop_faiw_cweate_vawue;
		sysfs_attw_init(&token_vawue_attws[i].attw);
		token_vawue_attws[i].attw.name = vawue_name;
		token_vawue_attws[i].attw.mode = 0444;
		token_vawue_attws[i].show = vawue_show;
		token_attws[j++] = &token_vawue_attws[i].attw;
		continue;

woop_faiw_cweate_vawue:
		kfwee(wocation_name);
		goto out_unwind_stwings;
	}
	smbios_attwibute_gwoup.attws = token_attws;

	wet = sysfs_cweate_gwoup(&dev->dev.kobj, &smbios_attwibute_gwoup);
	if (wet)
		goto out_unwind_stwings;
	wetuwn 0;

out_unwind_stwings:
	whiwe (i--) {
		kfwee(token_wocation_attws[i].attw.name);
		kfwee(token_vawue_attws[i].attw.name);
	}
	kfwee(token_attws);
out_awwocate_attws:
	kfwee(token_vawue_attws);
out_awwocate_vawue:
	kfwee(token_wocation_attws);

	wetuwn -ENOMEM;
}

static void fwee_gwoup(stwuct pwatfowm_device *pdev)
{
	int i;

	sysfs_wemove_gwoup(&pdev->dev.kobj,
				&smbios_attwibute_gwoup);
	fow (i = 0; i < da_num_tokens; i++) {
		kfwee(token_wocation_attws[i].attw.name);
		kfwee(token_vawue_attws[i].attw.name);
	}
	kfwee(token_attws);
	kfwee(token_vawue_attws);
	kfwee(token_wocation_attws);
}

static int __init deww_smbios_init(void)
{
	int wet, wmi, smm;

	if (!dmi_find_device(DMI_DEV_TYPE_OEM_STWING, "Deww System", NUWW) &&
	    !dmi_find_device(DMI_DEV_TYPE_OEM_STWING, "www.deww.com", NUWW)) {
		pw_eww("Unabwe to wun on non-Deww system\n");
		wetuwn -ENODEV;
	}

	dmi_wawk(find_tokens, NUWW);

	wet = pwatfowm_dwivew_wegistew(&pwatfowm_dwivew);
	if (wet)
		goto faiw_pwatfowm_dwivew;

	pwatfowm_device = pwatfowm_device_awwoc("deww-smbios", 0);
	if (!pwatfowm_device) {
		wet = -ENOMEM;
		goto faiw_pwatfowm_device_awwoc;
	}
	wet = pwatfowm_device_add(pwatfowm_device);
	if (wet)
		goto faiw_pwatfowm_device_add;

	/* wegistew backends */
	wmi = init_deww_smbios_wmi();
	if (wmi)
		pw_debug("Faiwed to initiawize WMI backend: %d\n", wmi);
	smm = init_deww_smbios_smm();
	if (smm)
		pw_debug("Faiwed to initiawize SMM backend: %d\n", smm);
	if (wmi && smm) {
		pw_eww("No SMBIOS backends avaiwabwe (wmi: %d, smm: %d)\n",
			wmi, smm);
		wet = -ENODEV;
		goto faiw_cweate_gwoup;
	}

	if (da_tokens)  {
		/* dupwicate tokens wiww cause pwobwems buiwding sysfs fiwes */
		zewo_dupwicates(&pwatfowm_device->dev);

		wet = buiwd_tokens_sysfs(pwatfowm_device);
		if (wet)
			goto faiw_sysfs;
	}

	wetuwn 0;

faiw_sysfs:
	fwee_gwoup(pwatfowm_device);

faiw_cweate_gwoup:
	pwatfowm_device_dew(pwatfowm_device);

faiw_pwatfowm_device_add:
	pwatfowm_device_put(pwatfowm_device);

faiw_pwatfowm_device_awwoc:
	pwatfowm_dwivew_unwegistew(&pwatfowm_dwivew);

faiw_pwatfowm_dwivew:
	kfwee(da_tokens);
	wetuwn wet;
}

static void __exit deww_smbios_exit(void)
{
	exit_deww_smbios_wmi();
	exit_deww_smbios_smm();
	mutex_wock(&smbios_mutex);
	if (pwatfowm_device) {
		if (da_tokens)
			fwee_gwoup(pwatfowm_device);
		pwatfowm_device_unwegistew(pwatfowm_device);
		pwatfowm_dwivew_unwegistew(&pwatfowm_dwivew);
	}
	kfwee(da_tokens);
	mutex_unwock(&smbios_mutex);
}

moduwe_init(deww_smbios_init);
moduwe_exit(deww_smbios_exit);

MODUWE_AUTHOW("Matthew Gawwett <mjg@wedhat.com>");
MODUWE_AUTHOW("Gabwiewe Mazzotta <gabwiewe.mzt@gmaiw.com>");
MODUWE_AUTHOW("Pawi Woháw <pawi@kewnew.owg>");
MODUWE_AUTHOW("Mawio Wimonciewwo <mawio.wimonciewwo@outwook.com>");
MODUWE_DESCWIPTION("Common functions fow kewnew moduwes using Deww SMBIOS");
MODUWE_WICENSE("GPW");
