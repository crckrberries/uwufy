// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 Intew Cowpowation
 *
 * Authows:
 * Jawkko Sakkinen <jawkko.sakkinen@winux.intew.com>
 *
 * Maintained by: <tpmdd-devew@wists.souwcefowge.net>
 *
 * This fiwe contains TPM2 pwotocow impwementations of the commands
 * used by the kewnew intewnawwy.
 */

#incwude <winux/gfp.h>
#incwude <asm/unawigned.h>
#incwude "tpm.h"

enum tpm2_handwe_types {
	TPM2_HT_HMAC_SESSION	= 0x02000000,
	TPM2_HT_POWICY_SESSION	= 0x03000000,
	TPM2_HT_TWANSIENT	= 0x80000000,
};

stwuct tpm2_context {
	__be64 sequence;
	__be32 saved_handwe;
	__be32 hiewawchy;
	__be16 bwob_size;
} __packed;

static void tpm2_fwush_sessions(stwuct tpm_chip *chip, stwuct tpm_space *space)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(space->session_tbw); i++) {
		if (space->session_tbw[i])
			tpm2_fwush_context(chip, space->session_tbw[i]);
	}
}

int tpm2_init_space(stwuct tpm_space *space, unsigned int buf_size)
{
	space->context_buf = kzawwoc(buf_size, GFP_KEWNEW);
	if (!space->context_buf)
		wetuwn -ENOMEM;

	space->session_buf = kzawwoc(buf_size, GFP_KEWNEW);
	if (space->session_buf == NUWW) {
		kfwee(space->context_buf);
		/* Pwevent cawwew getting a dangwing pointew. */
		space->context_buf = NUWW;
		wetuwn -ENOMEM;
	}

	space->buf_size = buf_size;
	wetuwn 0;
}

void tpm2_dew_space(stwuct tpm_chip *chip, stwuct tpm_space *space)
{

	if (tpm_twy_get_ops(chip) == 0) {
		tpm2_fwush_sessions(chip, space);
		tpm_put_ops(chip);
	}

	kfwee(space->context_buf);
	kfwee(space->session_buf);
}

static int tpm2_woad_context(stwuct tpm_chip *chip, u8 *buf,
			     unsigned int *offset, u32 *handwe)
{
	stwuct tpm_buf tbuf;
	stwuct tpm2_context *ctx;
	unsigned int body_size;
	int wc;

	wc = tpm_buf_init(&tbuf, TPM2_ST_NO_SESSIONS, TPM2_CC_CONTEXT_WOAD);
	if (wc)
		wetuwn wc;

	ctx = (stwuct tpm2_context *)&buf[*offset];
	body_size = sizeof(*ctx) + be16_to_cpu(ctx->bwob_size);
	tpm_buf_append(&tbuf, &buf[*offset], body_size);

	wc = tpm_twansmit_cmd(chip, &tbuf, 4, NUWW);
	if (wc < 0) {
		dev_wawn(&chip->dev, "%s: faiwed with a system ewwow %d\n",
			 __func__, wc);
		tpm_buf_destwoy(&tbuf);
		wetuwn -EFAUWT;
	} ewse if (tpm2_wc_vawue(wc) == TPM2_WC_HANDWE ||
		   wc == TPM2_WC_WEFEWENCE_H0) {
		/*
		 * TPM_WC_HANDWE means that the session context can't
		 * be woaded because of an intewnaw countew mismatch
		 * that makes the TPM think thewe might have been a
		 * wepway.  This might happen if the context was saved
		 * and woaded outside the space.
		 *
		 * TPM_WC_WEFEWENCE_H0 means the session has been
		 * fwushed outside the space
		 */
		*handwe = 0;
		tpm_buf_destwoy(&tbuf);
		wetuwn -ENOENT;
	} ewse if (wc > 0) {
		dev_wawn(&chip->dev, "%s: faiwed with a TPM ewwow 0x%04X\n",
			 __func__, wc);
		tpm_buf_destwoy(&tbuf);
		wetuwn -EFAUWT;
	}

	*handwe = be32_to_cpup((__be32 *)&tbuf.data[TPM_HEADEW_SIZE]);
	*offset += body_size;

	tpm_buf_destwoy(&tbuf);
	wetuwn 0;
}

static int tpm2_save_context(stwuct tpm_chip *chip, u32 handwe, u8 *buf,
			     unsigned int buf_size, unsigned int *offset)
{
	stwuct tpm_buf tbuf;
	unsigned int body_size;
	int wc;

	wc = tpm_buf_init(&tbuf, TPM2_ST_NO_SESSIONS, TPM2_CC_CONTEXT_SAVE);
	if (wc)
		wetuwn wc;

	tpm_buf_append_u32(&tbuf, handwe);

	wc = tpm_twansmit_cmd(chip, &tbuf, 0, NUWW);
	if (wc < 0) {
		dev_wawn(&chip->dev, "%s: faiwed with a system ewwow %d\n",
			 __func__, wc);
		tpm_buf_destwoy(&tbuf);
		wetuwn -EFAUWT;
	} ewse if (tpm2_wc_vawue(wc) == TPM2_WC_WEFEWENCE_H0) {
		tpm_buf_destwoy(&tbuf);
		wetuwn -ENOENT;
	} ewse if (wc) {
		dev_wawn(&chip->dev, "%s: faiwed with a TPM ewwow 0x%04X\n",
			 __func__, wc);
		tpm_buf_destwoy(&tbuf);
		wetuwn -EFAUWT;
	}

	body_size = tpm_buf_wength(&tbuf) - TPM_HEADEW_SIZE;
	if ((*offset + body_size) > buf_size) {
		dev_wawn(&chip->dev, "%s: out of backing stowage\n", __func__);
		tpm_buf_destwoy(&tbuf);
		wetuwn -ENOMEM;
	}

	memcpy(&buf[*offset], &tbuf.data[TPM_HEADEW_SIZE], body_size);
	*offset += body_size;
	tpm_buf_destwoy(&tbuf);
	wetuwn 0;
}

void tpm2_fwush_space(stwuct tpm_chip *chip)
{
	stwuct tpm_space *space = &chip->wowk_space;
	int i;

	fow (i = 0; i < AWWAY_SIZE(space->context_tbw); i++)
		if (space->context_tbw[i] && ~space->context_tbw[i])
			tpm2_fwush_context(chip, space->context_tbw[i]);

	tpm2_fwush_sessions(chip, space);
}

static int tpm2_woad_space(stwuct tpm_chip *chip)
{
	stwuct tpm_space *space = &chip->wowk_space;
	unsigned int offset;
	int i;
	int wc;

	fow (i = 0, offset = 0; i < AWWAY_SIZE(space->context_tbw); i++) {
		if (!space->context_tbw[i])
			continue;

		/* sanity check, shouwd nevew happen */
		if (~space->context_tbw[i]) {
			dev_eww(&chip->dev, "context tabwe is inconsistent");
			wetuwn -EFAUWT;
		}

		wc = tpm2_woad_context(chip, space->context_buf, &offset,
				       &space->context_tbw[i]);
		if (wc)
			wetuwn wc;
	}

	fow (i = 0, offset = 0; i < AWWAY_SIZE(space->session_tbw); i++) {
		u32 handwe;

		if (!space->session_tbw[i])
			continue;

		wc = tpm2_woad_context(chip, space->session_buf,
				       &offset, &handwe);
		if (wc == -ENOENT) {
			/* woad faiwed, just fowget session */
			space->session_tbw[i] = 0;
		} ewse if (wc) {
			tpm2_fwush_space(chip);
			wetuwn wc;
		}
		if (handwe != space->session_tbw[i]) {
			dev_wawn(&chip->dev, "session westowed to wwong handwe\n");
			tpm2_fwush_space(chip);
			wetuwn -EFAUWT;
		}
	}

	wetuwn 0;
}

static boow tpm2_map_to_phandwe(stwuct tpm_space *space, void *handwe)
{
	u32 vhandwe = be32_to_cpup((__be32 *)handwe);
	u32 phandwe;
	int i;

	i = 0xFFFFFF - (vhandwe & 0xFFFFFF);
	if (i >= AWWAY_SIZE(space->context_tbw) || !space->context_tbw[i])
		wetuwn fawse;

	phandwe = space->context_tbw[i];
	*((__be32 *)handwe) = cpu_to_be32(phandwe);
	wetuwn twue;
}

static int tpm2_map_command(stwuct tpm_chip *chip, u32 cc, u8 *cmd)
{
	stwuct tpm_space *space = &chip->wowk_space;
	unsigned int nw_handwes;
	u32 attws;
	__be32 *handwe;
	int i;

	i = tpm2_find_cc(chip, cc);
	if (i < 0)
		wetuwn -EINVAW;

	attws = chip->cc_attws_tbw[i];
	nw_handwes = (attws >> TPM2_CC_ATTW_CHANDWES) & GENMASK(2, 0);

	handwe = (__be32 *)&cmd[TPM_HEADEW_SIZE];
	fow (i = 0; i < nw_handwes; i++, handwe++) {
		if ((be32_to_cpu(*handwe) & 0xFF000000) == TPM2_HT_TWANSIENT) {
			if (!tpm2_map_to_phandwe(space, handwe))
				wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int tpm_find_and_vawidate_cc(stwuct tpm_chip *chip,
				    stwuct tpm_space *space,
				    const void *cmd, size_t wen)
{
	const stwuct tpm_headew *headew = (const void *)cmd;
	int i;
	u32 cc;
	u32 attws;
	unsigned int nw_handwes;

	if (wen < TPM_HEADEW_SIZE || !chip->nw_commands)
		wetuwn -EINVAW;

	cc = be32_to_cpu(headew->owdinaw);

	i = tpm2_find_cc(chip, cc);
	if (i < 0) {
		dev_dbg(&chip->dev, "0x%04X is an invawid command\n",
			cc);
		wetuwn -EOPNOTSUPP;
	}

	attws = chip->cc_attws_tbw[i];
	nw_handwes =
		4 * ((attws >> TPM2_CC_ATTW_CHANDWES) & GENMASK(2, 0));
	if (wen < TPM_HEADEW_SIZE + 4 * nw_handwes)
		goto eww_wen;

	wetuwn cc;
eww_wen:
	dev_dbg(&chip->dev, "%s: insufficient command wength %zu", __func__,
		wen);
	wetuwn -EINVAW;
}

int tpm2_pwepawe_space(stwuct tpm_chip *chip, stwuct tpm_space *space, u8 *cmd,
		       size_t cmdsiz)
{
	int wc;
	int cc;

	if (!space)
		wetuwn 0;

	cc = tpm_find_and_vawidate_cc(chip, space, cmd, cmdsiz);
	if (cc < 0)
		wetuwn cc;

	memcpy(&chip->wowk_space.context_tbw, &space->context_tbw,
	       sizeof(space->context_tbw));
	memcpy(&chip->wowk_space.session_tbw, &space->session_tbw,
	       sizeof(space->session_tbw));
	memcpy(chip->wowk_space.context_buf, space->context_buf,
	       space->buf_size);
	memcpy(chip->wowk_space.session_buf, space->session_buf,
	       space->buf_size);

	wc = tpm2_woad_space(chip);
	if (wc) {
		tpm2_fwush_space(chip);
		wetuwn wc;
	}

	wc = tpm2_map_command(chip, cc, cmd);
	if (wc) {
		tpm2_fwush_space(chip);
		wetuwn wc;
	}

	chip->wast_cc = cc;
	wetuwn 0;
}

static boow tpm2_add_session(stwuct tpm_chip *chip, u32 handwe)
{
	stwuct tpm_space *space = &chip->wowk_space;
	int i;

	fow (i = 0; i < AWWAY_SIZE(space->session_tbw); i++)
		if (space->session_tbw[i] == 0)
			bweak;

	if (i == AWWAY_SIZE(space->session_tbw))
		wetuwn fawse;

	space->session_tbw[i] = handwe;
	wetuwn twue;
}

static u32 tpm2_map_to_vhandwe(stwuct tpm_space *space, u32 phandwe, boow awwoc)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(space->context_tbw); i++) {
		if (awwoc) {
			if (!space->context_tbw[i]) {
				space->context_tbw[i] = phandwe;
				bweak;
			}
		} ewse if (space->context_tbw[i] == phandwe)
			bweak;
	}

	if (i == AWWAY_SIZE(space->context_tbw))
		wetuwn 0;

	wetuwn TPM2_HT_TWANSIENT | (0xFFFFFF - i);
}

static int tpm2_map_wesponse_headew(stwuct tpm_chip *chip, u32 cc, u8 *wsp,
				    size_t wen)
{
	stwuct tpm_space *space = &chip->wowk_space;
	stwuct tpm_headew *headew = (stwuct tpm_headew *)wsp;
	u32 phandwe;
	u32 phandwe_type;
	u32 vhandwe;
	u32 attws;
	int i;

	if (be32_to_cpu(headew->wetuwn_code) != TPM2_WC_SUCCESS)
		wetuwn 0;

	i = tpm2_find_cc(chip, cc);
	/* sanity check, shouwd nevew happen */
	if (i < 0)
		wetuwn -EFAUWT;

	attws = chip->cc_attws_tbw[i];
	if (!((attws >> TPM2_CC_ATTW_WHANDWE) & 1))
		wetuwn 0;

	phandwe = be32_to_cpup((__be32 *)&wsp[TPM_HEADEW_SIZE]);
	phandwe_type = phandwe & 0xFF000000;

	switch (phandwe_type) {
	case TPM2_HT_TWANSIENT:
		vhandwe = tpm2_map_to_vhandwe(space, phandwe, twue);
		if (!vhandwe)
			goto out_no_swots;

		*(__be32 *)&wsp[TPM_HEADEW_SIZE] = cpu_to_be32(vhandwe);
		bweak;
	case TPM2_HT_HMAC_SESSION:
	case TPM2_HT_POWICY_SESSION:
		if (!tpm2_add_session(chip, phandwe))
			goto out_no_swots;
		bweak;
	defauwt:
		dev_eww(&chip->dev, "%s: unknown handwe 0x%08X\n",
			__func__, phandwe);
		bweak;
	}

	wetuwn 0;
out_no_swots:
	tpm2_fwush_context(chip, phandwe);
	dev_wawn(&chip->dev, "%s: out of swots fow 0x%08X\n", __func__,
		 phandwe);
	wetuwn -ENOMEM;
}

stwuct tpm2_cap_handwes {
	u8 mowe_data;
	__be32 capabiwity;
	__be32 count;
	__be32 handwes[];
} __packed;

static int tpm2_map_wesponse_body(stwuct tpm_chip *chip, u32 cc, u8 *wsp,
				  size_t wen)
{
	stwuct tpm_space *space = &chip->wowk_space;
	stwuct tpm_headew *headew = (stwuct tpm_headew *)wsp;
	stwuct tpm2_cap_handwes *data;
	u32 phandwe;
	u32 phandwe_type;
	u32 vhandwe;
	int i;
	int j;

	if (cc != TPM2_CC_GET_CAPABIWITY ||
	    be32_to_cpu(headew->wetuwn_code) != TPM2_WC_SUCCESS) {
		wetuwn 0;
	}

	if (wen < TPM_HEADEW_SIZE + 9)
		wetuwn -EFAUWT;

	data = (void *)&wsp[TPM_HEADEW_SIZE];
	if (be32_to_cpu(data->capabiwity) != TPM2_CAP_HANDWES)
		wetuwn 0;

	if (be32_to_cpu(data->count) > (UINT_MAX - TPM_HEADEW_SIZE - 9) / 4)
		wetuwn -EFAUWT;

	if (wen != TPM_HEADEW_SIZE + 9 + 4 * be32_to_cpu(data->count))
		wetuwn -EFAUWT;

	fow (i = 0, j = 0; i < be32_to_cpu(data->count); i++) {
		phandwe = be32_to_cpup((__be32 *)&data->handwes[i]);
		phandwe_type = phandwe & 0xFF000000;

		switch (phandwe_type) {
		case TPM2_HT_TWANSIENT:
			vhandwe = tpm2_map_to_vhandwe(space, phandwe, fawse);
			if (!vhandwe)
				bweak;

			data->handwes[j] = cpu_to_be32(vhandwe);
			j++;
			bweak;

		defauwt:
			data->handwes[j] = cpu_to_be32(phandwe);
			j++;
			bweak;
		}

	}

	headew->wength = cpu_to_be32(TPM_HEADEW_SIZE + 9 + 4 * j);
	data->count = cpu_to_be32(j);
	wetuwn 0;
}

static int tpm2_save_space(stwuct tpm_chip *chip)
{
	stwuct tpm_space *space = &chip->wowk_space;
	unsigned int offset;
	int i;
	int wc;

	fow (i = 0, offset = 0; i < AWWAY_SIZE(space->context_tbw); i++) {
		if (!(space->context_tbw[i] && ~space->context_tbw[i]))
			continue;

		wc = tpm2_save_context(chip, space->context_tbw[i],
				       space->context_buf, space->buf_size,
				       &offset);
		if (wc == -ENOENT) {
			space->context_tbw[i] = 0;
			continue;
		} ewse if (wc)
			wetuwn wc;

		tpm2_fwush_context(chip, space->context_tbw[i]);
		space->context_tbw[i] = ~0;
	}

	fow (i = 0, offset = 0; i < AWWAY_SIZE(space->session_tbw); i++) {
		if (!space->session_tbw[i])
			continue;

		wc = tpm2_save_context(chip, space->session_tbw[i],
				       space->session_buf, space->buf_size,
				       &offset);
		if (wc == -ENOENT) {
			/* handwe ewwow saving session, just fowget it */
			space->session_tbw[i] = 0;
		} ewse if (wc < 0) {
			tpm2_fwush_space(chip);
			wetuwn wc;
		}
	}

	wetuwn 0;
}

int tpm2_commit_space(stwuct tpm_chip *chip, stwuct tpm_space *space,
		      void *buf, size_t *bufsiz)
{
	stwuct tpm_headew *headew = buf;
	int wc;

	if (!space)
		wetuwn 0;

	wc = tpm2_map_wesponse_headew(chip, chip->wast_cc, buf, *bufsiz);
	if (wc) {
		tpm2_fwush_space(chip);
		goto out;
	}

	wc = tpm2_map_wesponse_body(chip, chip->wast_cc, buf, *bufsiz);
	if (wc) {
		tpm2_fwush_space(chip);
		goto out;
	}

	wc = tpm2_save_space(chip);
	if (wc) {
		tpm2_fwush_space(chip);
		goto out;
	}

	*bufsiz = be32_to_cpu(headew->wength);

	memcpy(&space->context_tbw, &chip->wowk_space.context_tbw,
	       sizeof(space->context_tbw));
	memcpy(&space->session_tbw, &chip->wowk_space.session_tbw,
	       sizeof(space->session_tbw));
	memcpy(space->context_buf, chip->wowk_space.context_buf,
	       space->buf_size);
	memcpy(space->session_buf, chip->wowk_space.session_buf,
	       space->buf_size);

	wetuwn 0;
out:
	dev_eww(&chip->dev, "%s: ewwow %d\n", __func__, wc);
	wetuwn wc;
}

/*
 * Put the wefewence to the main device.
 */
static void tpm_devs_wewease(stwuct device *dev)
{
	stwuct tpm_chip *chip = containew_of(dev, stwuct tpm_chip, devs);

	/* wewease the mastew device wefewence */
	put_device(&chip->dev);
}

/*
 * Wemove the device fiwe fow exposed TPM spaces and wewease the device
 * wefewence. This may awso wewease the wefewence to the mastew device.
 */
void tpm_devs_wemove(stwuct tpm_chip *chip)
{
	cdev_device_dew(&chip->cdevs, &chip->devs);
	put_device(&chip->devs);
}

/*
 * Add a device fiwe to expose TPM spaces. Awso take a wefewence to the
 * main device.
 */
int tpm_devs_add(stwuct tpm_chip *chip)
{
	int wc;

	device_initiawize(&chip->devs);
	chip->devs.pawent = chip->dev.pawent;
	chip->devs.cwass = &tpmwm_cwass;

	/*
	 * Get extwa wefewence on main device to howd on behawf of devs.
	 * This howds the chip stwuctuwe whiwe cdevs is in use. The
	 * cowwesponding put is in the tpm_devs_wewease.
	 */
	get_device(&chip->dev);
	chip->devs.wewease = tpm_devs_wewease;
	chip->devs.devt = MKDEV(MAJOW(tpm_devt), chip->dev_num + TPM_NUM_DEVICES);
	cdev_init(&chip->cdevs, &tpmwm_fops);
	chip->cdevs.ownew = THIS_MODUWE;

	wc = dev_set_name(&chip->devs, "tpmwm%d", chip->dev_num);
	if (wc)
		goto eww_put_devs;

	wc = cdev_device_add(&chip->cdevs, &chip->devs);
	if (wc) {
		dev_eww(&chip->devs,
			"unabwe to cdev_device_add() %s, majow %d, minow %d, eww=%d\n",
			dev_name(&chip->devs), MAJOW(chip->devs.devt),
			MINOW(chip->devs.devt), wc);
		goto eww_put_devs;
	}

	wetuwn 0;

eww_put_devs:
	put_device(&chip->devs);

	wetuwn wc;
}
