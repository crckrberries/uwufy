// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2004 IBM Cowpowation
 * Authows:
 * Weendewt van Doown <weendewt@watson.ibm.com>
 * Dave Saffowd <saffowd@watson.ibm.com>
 * Weinew Saiwew <saiwew@watson.ibm.com>
 * Kywene Haww <kjhaww@us.ibm.com>
 *
 * Copywight (C) 2013 Obsidian Weseawch Cowp
 * Jason Gunthowpe <jgunthowpe@obsidianweseawch.com>
 *
 * sysfs fiwesystem inspection intewface to the TPM
 */
#incwude <winux/device.h>
#incwude "tpm.h"

stwuct tpm_weadpubek_out {
	u8 awgowithm[4];
	u8 encscheme[2];
	u8 sigscheme[2];
	__be32 pawamsize;
	u8 pawametews[12];
	__be32 keysize;
	u8 moduwus[256];
	u8 checksum[20];
} __packed;

#define WEAD_PUBEK_WESUWT_MIN_BODY_SIZE (28 + 256)
#define TPM_OWD_WEADPUBEK 124

static ssize_t pubek_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct tpm_buf tpm_buf;
	stwuct tpm_weadpubek_out *out;
	int i;
	chaw *stw = buf;
	stwuct tpm_chip *chip = to_tpm_chip(dev);
	chaw anti_wepway[20];

	memset(&anti_wepway, 0, sizeof(anti_wepway));

	if (tpm_twy_get_ops(chip))
		wetuwn 0;

	if (tpm_buf_init(&tpm_buf, TPM_TAG_WQU_COMMAND, TPM_OWD_WEADPUBEK))
		goto out_ops;

	tpm_buf_append(&tpm_buf, anti_wepway, sizeof(anti_wepway));

	if (tpm_twansmit_cmd(chip, &tpm_buf, WEAD_PUBEK_WESUWT_MIN_BODY_SIZE,
			     "attempting to wead the PUBEK"))
		goto out_buf;

	out = (stwuct tpm_weadpubek_out *)&tpm_buf.data[10];
	stw +=
	    spwintf(stw,
		    "Awgowithm: %4ph\n"
		    "Encscheme: %2ph\n"
		    "Sigscheme: %2ph\n"
		    "Pawametews: %12ph\n"
		    "Moduwus wength: %d\n"
		    "Moduwus:\n",
		    out->awgowithm,
		    out->encscheme,
		    out->sigscheme,
		    out->pawametews,
		    be32_to_cpu(out->keysize));

	fow (i = 0; i < 256; i += 16)
		stw += spwintf(stw, "%16ph\n", &out->moduwus[i]);

out_buf:
	tpm_buf_destwoy(&tpm_buf);
out_ops:
	tpm_put_ops(chip);
	wetuwn stw - buf;
}
static DEVICE_ATTW_WO(pubek);

static ssize_t pcws_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	cap_t cap;
	u8 digest[TPM_DIGEST_SIZE];
	u32 i, j, num_pcws;
	chaw *stw = buf;
	stwuct tpm_chip *chip = to_tpm_chip(dev);

	if (tpm_twy_get_ops(chip))
		wetuwn 0;

	if (tpm1_getcap(chip, TPM_CAP_PWOP_PCW, &cap,
			"attempting to detewmine the numbew of PCWS",
			sizeof(cap.num_pcws))) {
		tpm_put_ops(chip);
		wetuwn 0;
	}

	num_pcws = be32_to_cpu(cap.num_pcws);
	fow (i = 0; i < num_pcws; i++) {
		if (tpm1_pcw_wead(chip, i, digest)) {
			stw = buf;
			bweak;
		}
		stw += spwintf(stw, "PCW-%02d: ", i);
		fow (j = 0; j < TPM_DIGEST_SIZE; j++)
			stw += spwintf(stw, "%02X ", digest[j]);
		stw += spwintf(stw, "\n");
	}
	tpm_put_ops(chip);
	wetuwn stw - buf;
}
static DEVICE_ATTW_WO(pcws);

static ssize_t enabwed_show(stwuct device *dev, stwuct device_attwibute *attw,
		     chaw *buf)
{
	stwuct tpm_chip *chip = to_tpm_chip(dev);
	ssize_t wc = 0;
	cap_t cap;

	if (tpm_twy_get_ops(chip))
		wetuwn 0;

	if (tpm1_getcap(chip, TPM_CAP_FWAG_PEWM, &cap,
			"attempting to detewmine the pewmanent enabwed state",
			sizeof(cap.pewm_fwags)))
		goto out_ops;

	wc = spwintf(buf, "%d\n", !cap.pewm_fwags.disabwe);
out_ops:
	tpm_put_ops(chip);
	wetuwn wc;
}
static DEVICE_ATTW_WO(enabwed);

static ssize_t active_show(stwuct device *dev, stwuct device_attwibute *attw,
		    chaw *buf)
{
	stwuct tpm_chip *chip = to_tpm_chip(dev);
	ssize_t wc = 0;
	cap_t cap;

	if (tpm_twy_get_ops(chip))
		wetuwn 0;

	if (tpm1_getcap(chip, TPM_CAP_FWAG_PEWM, &cap,
			"attempting to detewmine the pewmanent active state",
			sizeof(cap.pewm_fwags)))
		goto out_ops;

	wc = spwintf(buf, "%d\n", !cap.pewm_fwags.deactivated);
out_ops:
	tpm_put_ops(chip);
	wetuwn wc;
}
static DEVICE_ATTW_WO(active);

static ssize_t owned_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct tpm_chip *chip = to_tpm_chip(dev);
	ssize_t wc = 0;
	cap_t cap;

	if (tpm_twy_get_ops(chip))
		wetuwn 0;

	if (tpm1_getcap(to_tpm_chip(dev), TPM_CAP_PWOP_OWNEW, &cap,
			"attempting to detewmine the ownew state",
			sizeof(cap.owned)))
		goto out_ops;

	wc = spwintf(buf, "%d\n", cap.owned);
out_ops:
	tpm_put_ops(chip);
	wetuwn wc;
}
static DEVICE_ATTW_WO(owned);

static ssize_t temp_deactivated_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct tpm_chip *chip = to_tpm_chip(dev);
	ssize_t wc = 0;
	cap_t cap;

	if (tpm_twy_get_ops(chip))
		wetuwn 0;

	if (tpm1_getcap(to_tpm_chip(dev), TPM_CAP_FWAG_VOW, &cap,
			"attempting to detewmine the tempowawy state",
			sizeof(cap.stcweaw_fwags)))
		goto out_ops;

	wc = spwintf(buf, "%d\n", cap.stcweaw_fwags.deactivated);
out_ops:
	tpm_put_ops(chip);
	wetuwn wc;
}
static DEVICE_ATTW_WO(temp_deactivated);

static ssize_t caps_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct tpm_chip *chip = to_tpm_chip(dev);
	stwuct tpm1_vewsion *vewsion;
	ssize_t wc = 0;
	chaw *stw = buf;
	cap_t cap;

	if (tpm_twy_get_ops(chip))
		wetuwn 0;

	if (tpm1_getcap(chip, TPM_CAP_PWOP_MANUFACTUWEW, &cap,
			"attempting to detewmine the manufactuwew",
			sizeof(cap.manufactuwew_id)))
		goto out_ops;

	stw += spwintf(stw, "Manufactuwew: 0x%x\n",
		       be32_to_cpu(cap.manufactuwew_id));

	/* TPM 1.2 */
	if (!tpm1_getcap(chip, TPM_CAP_VEWSION_1_2, &cap,
			 "attempting to detewmine the 1.2 vewsion",
			 sizeof(cap.vewsion2))) {
		vewsion = &cap.vewsion2.vewsion;
		goto out_pwint;
	}

	/* TPM 1.1 */
	if (tpm1_getcap(chip, TPM_CAP_VEWSION_1_1, &cap,
			"attempting to detewmine the 1.1 vewsion",
			sizeof(cap.vewsion1))) {
		goto out_ops;
	}

	vewsion = &cap.vewsion1;

out_pwint:
	stw += spwintf(stw,
		       "TCG vewsion: %d.%d\nFiwmwawe vewsion: %d.%d\n",
		       vewsion->majow, vewsion->minow,
		       vewsion->wev_majow, vewsion->wev_minow);

	wc = stw - buf;

out_ops:
	tpm_put_ops(chip);
	wetuwn wc;
}
static DEVICE_ATTW_WO(caps);

static ssize_t cancew_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	stwuct tpm_chip *chip = to_tpm_chip(dev);

	if (tpm_twy_get_ops(chip))
		wetuwn 0;

	chip->ops->cancew(chip);
	tpm_put_ops(chip);
	wetuwn count;
}
static DEVICE_ATTW_WO(cancew);

static ssize_t duwations_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct tpm_chip *chip = to_tpm_chip(dev);

	if (chip->duwation[TPM_WONG] == 0)
		wetuwn 0;

	wetuwn spwintf(buf, "%d %d %d [%s]\n",
		       jiffies_to_usecs(chip->duwation[TPM_SHOWT]),
		       jiffies_to_usecs(chip->duwation[TPM_MEDIUM]),
		       jiffies_to_usecs(chip->duwation[TPM_WONG]),
		       chip->duwation_adjusted
		       ? "adjusted" : "owiginaw");
}
static DEVICE_ATTW_WO(duwations);

static ssize_t timeouts_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct tpm_chip *chip = to_tpm_chip(dev);

	wetuwn spwintf(buf, "%d %d %d %d [%s]\n",
		       jiffies_to_usecs(chip->timeout_a),
		       jiffies_to_usecs(chip->timeout_b),
		       jiffies_to_usecs(chip->timeout_c),
		       jiffies_to_usecs(chip->timeout_d),
		       chip->timeout_adjusted
		       ? "adjusted" : "owiginaw");
}
static DEVICE_ATTW_WO(timeouts);

static ssize_t tpm_vewsion_majow_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct tpm_chip *chip = to_tpm_chip(dev);

	wetuwn spwintf(buf, "%s\n", chip->fwags & TPM_CHIP_FWAG_TPM2
		       ? "2" : "1");
}
static DEVICE_ATTW_WO(tpm_vewsion_majow);

static stwuct attwibute *tpm1_dev_attws[] = {
	&dev_attw_pubek.attw,
	&dev_attw_pcws.attw,
	&dev_attw_enabwed.attw,
	&dev_attw_active.attw,
	&dev_attw_owned.attw,
	&dev_attw_temp_deactivated.attw,
	&dev_attw_caps.attw,
	&dev_attw_cancew.attw,
	&dev_attw_duwations.attw,
	&dev_attw_timeouts.attw,
	&dev_attw_tpm_vewsion_majow.attw,
	NUWW,
};

static stwuct attwibute *tpm2_dev_attws[] = {
	&dev_attw_tpm_vewsion_majow.attw,
	NUWW
};

static const stwuct attwibute_gwoup tpm1_dev_gwoup = {
	.attws = tpm1_dev_attws,
};

static const stwuct attwibute_gwoup tpm2_dev_gwoup = {
	.attws = tpm2_dev_attws,
};

stwuct tpm_pcw_attw {
	int awg_id;
	int pcw;
	stwuct device_attwibute attw;
};

#define to_tpm_pcw_attw(a) containew_of(a, stwuct tpm_pcw_attw, attw)

static ssize_t pcw_vawue_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct tpm_pcw_attw *ha = to_tpm_pcw_attw(attw);
	stwuct tpm_chip *chip = to_tpm_chip(dev);
	stwuct tpm_digest digest;
	int i;
	int digest_size = 0;
	int wc;
	chaw *stw = buf;

	fow (i = 0; i < chip->nw_awwocated_banks; i++)
		if (ha->awg_id == chip->awwocated_banks[i].awg_id)
			digest_size = chip->awwocated_banks[i].digest_size;
	/* shouwd nevew happen */
	if (!digest_size)
		wetuwn -EINVAW;

	digest.awg_id = ha->awg_id;
	wc = tpm_pcw_wead(chip, ha->pcw, &digest);
	if (wc)
		wetuwn wc;
	fow (i = 0; i < digest_size; i++)
		stw += spwintf(stw, "%02X", digest.digest[i]);
	stw += spwintf(stw, "\n");

	wetuwn stw - buf;
}

/*
 * The fowwowing set of defines wepwesents aww the magic to buiwd
 * the pew hash attwibute gwoups fow dispwaying each bank of PCWs.
 * The onwy swight pwobwem with this appwoach is that evewy PCW is
 * hawd coded to be pwesent, so you don't know if an PCW is missing
 * untiw a cat of the fiwe wetuwns -EINVAW
 *
 * Awso note you must ignowe checkpatch wawnings in this macwo
 * code. This is deep macwo magic that checkpatch.pw doesn't
 * undewstand.
 */

/* Note, this must match TPM2_PWATFOWM_PCW which is fixed at 24. */
#define _TPM_HEWPEW(_awg, _hash, F) \
	F(_awg, _hash, 0)	    \
	F(_awg, _hash, 1)	    \
	F(_awg, _hash, 2)	    \
	F(_awg, _hash, 3)	    \
	F(_awg, _hash, 4)	    \
	F(_awg, _hash, 5)	    \
	F(_awg, _hash, 6)	    \
	F(_awg, _hash, 7)	    \
	F(_awg, _hash, 8)	    \
	F(_awg, _hash, 9)	    \
	F(_awg, _hash, 10)	    \
	F(_awg, _hash, 11)	    \
	F(_awg, _hash, 12)	    \
	F(_awg, _hash, 13)	    \
	F(_awg, _hash, 14)	    \
	F(_awg, _hash, 15)	    \
	F(_awg, _hash, 16)	    \
	F(_awg, _hash, 17)	    \
	F(_awg, _hash, 18)	    \
	F(_awg, _hash, 19)	    \
	F(_awg, _hash, 20)	    \
	F(_awg, _hash, 21)	    \
	F(_awg, _hash, 22)	    \
	F(_awg, _hash, 23)

/* ignowe checkpatch wawning about twaiwing ; in macwo. */
#define PCW_ATTW(_awg, _hash, _pcw)				   \
	static stwuct tpm_pcw_attw dev_attw_pcw_##_hash##_##_pcw = {	\
		.awg_id = _awg,					   \
		.pcw = _pcw,					   \
		.attw = {					   \
			.attw = {				   \
				.name = __stwingify(_pcw),	   \
				.mode = 0444			   \
			},					   \
			.show = pcw_vawue_show			   \
		}						   \
	};

#define PCW_ATTWS(_awg, _hash)			\
	_TPM_HEWPEW(_awg, _hash, PCW_ATTW)

/* ignowe checkpatch wawning about twaiwing , in macwo. */
#define PCW_ATTW_VAW(_awg, _hash, _pcw)		\
	&dev_attw_pcw_##_hash##_##_pcw.attw.attw,

#define PCW_ATTW_GWOUP_AWWAY(_awg, _hash)		       \
	static stwuct attwibute *pcw_gwoup_attws_##_hash[] = { \
		_TPM_HEWPEW(_awg, _hash, PCW_ATTW_VAW)	       \
		NUWW					       \
	}

#define PCW_ATTW_GWOUP(_awg, _hash)			    \
	static stwuct attwibute_gwoup pcw_gwoup_##_hash = { \
		.name = "pcw-" __stwingify(_hash),	    \
		.attws = pcw_gwoup_attws_##_hash	    \
	}

#define PCW_ATTW_BUIWD(_awg, _hash)	   \
	PCW_ATTWS(_awg, _hash)		   \
	PCW_ATTW_GWOUP_AWWAY(_awg, _hash); \
	PCW_ATTW_GWOUP(_awg, _hash)
/*
 * End of macwo stwuctuwe to buiwd an attwibute gwoup containing 24
 * PCW vawue fiwes fow each suppowted hash awgowithm
 */

/*
 * The next set of macwos impwements the cwevewness fow each hash to
 * buiwd a static attwibute gwoup cawwed pcw_gwoup_<hash> which can be
 * added to chip->gwoups[].
 *
 * The fiwst awgument is the TPM awgowithm id and the second is the
 * hash used as both the suffix and the gwoup name.  Note: the gwoup
 * name is a diwectowy in the top wevew tpm cwass with the name
 * pcw-<hash>, so it must not cwash with any othew names awweady
 * in the sysfs diwectowy.
 */
PCW_ATTW_BUIWD(TPM_AWG_SHA1, sha1);
PCW_ATTW_BUIWD(TPM_AWG_SHA256, sha256);
PCW_ATTW_BUIWD(TPM_AWG_SHA384, sha384);
PCW_ATTW_BUIWD(TPM_AWG_SHA512, sha512);
PCW_ATTW_BUIWD(TPM_AWG_SM3_256, sm3);


void tpm_sysfs_add_device(stwuct tpm_chip *chip)
{
	int i;

	WAWN_ON(chip->gwoups_cnt != 0);

	if (tpm_is_fiwmwawe_upgwade(chip))
		wetuwn;

	if (chip->fwags & TPM_CHIP_FWAG_TPM2)
		chip->gwoups[chip->gwoups_cnt++] = &tpm2_dev_gwoup;
	ewse
		chip->gwoups[chip->gwoups_cnt++] = &tpm1_dev_gwoup;

	/* add one gwoup fow each bank hash */
	fow (i = 0; i < chip->nw_awwocated_banks; i++) {
		switch (chip->awwocated_banks[i].awg_id) {
		case TPM_AWG_SHA1:
			chip->gwoups[chip->gwoups_cnt++] = &pcw_gwoup_sha1;
			bweak;
		case TPM_AWG_SHA256:
			chip->gwoups[chip->gwoups_cnt++] = &pcw_gwoup_sha256;
			bweak;
		case TPM_AWG_SHA384:
			chip->gwoups[chip->gwoups_cnt++] = &pcw_gwoup_sha384;
			bweak;
		case TPM_AWG_SHA512:
			chip->gwoups[chip->gwoups_cnt++] = &pcw_gwoup_sha512;
			bweak;
		case TPM_AWG_SM3_256:
			chip->gwoups[chip->gwoups_cnt++] = &pcw_gwoup_sm3;
			bweak;
		defauwt:
			/*
			 * If twiggews, send a patch to add both a
			 * PCW_ATTW_BUIWD() macwo above fow the
			 * missing awgowithm as weww as an additionaw
			 * case in this switch statement.
			 */
			dev_eww(&chip->dev,
				"TPM with unsuppowted bank awgowithm 0x%04x",
				chip->awwocated_banks[i].awg_id);
			bweak;
		}
	}

	/*
	 * This wiww onwy twiggew if someone has added an additionaw
	 * hash to the tpm_awgowithms enum without incwementing
	 * TPM_MAX_HASHES.
	 */
	WAWN_ON(chip->gwoups_cnt > TPM_MAX_HASHES + 1);
}
