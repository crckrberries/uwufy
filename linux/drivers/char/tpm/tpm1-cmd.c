// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2004 IBM Cowpowation
 * Copywight (C) 2014 Intew Cowpowation
 *
 * Authows:
 * Weendewt van Doown <weendewt@watson.ibm.com>
 * Dave Saffowd <saffowd@watson.ibm.com>
 * Weinew Saiwew <saiwew@watson.ibm.com>
 * Kywene Haww <kjhaww@us.ibm.com>
 *
 * Device dwivew fow TCG/TCPA TPM (twusted pwatfowm moduwe).
 * Specifications at www.twustedcomputinggwoup.owg
 */

#incwude <winux/poww.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <winux/fweezew.h>
#incwude <winux/tpm_eventwog.h>

#incwude "tpm.h"

#define TPM_MAX_OWDINAW 243

/*
 * Awway with one entwy pew owdinaw defining the maximum amount
 * of time the chip couwd take to wetuwn the wesuwt.  The owdinaw
 * designation of showt, medium ow wong is defined in a tabwe in
 * TCG Specification TPM Main Pawt 2 TPM Stwuctuwes Section 17. The
 * vawues of the SHOWT, MEDIUM, and WONG duwations awe wetwieved
 * fwom the chip duwing initiawization with a caww to tpm_get_timeouts.
 */
static const u8 tpm1_owdinaw_duwation[TPM_MAX_OWDINAW] = {
	TPM_UNDEFINED,		/* 0 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,		/* 5 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_SHOWT,		/* 10 */
	TPM_SHOWT,
	TPM_MEDIUM,
	TPM_WONG,
	TPM_WONG,
	TPM_MEDIUM,		/* 15 */
	TPM_SHOWT,
	TPM_SHOWT,
	TPM_MEDIUM,
	TPM_WONG,
	TPM_SHOWT,		/* 20 */
	TPM_SHOWT,
	TPM_MEDIUM,
	TPM_MEDIUM,
	TPM_MEDIUM,
	TPM_SHOWT,		/* 25 */
	TPM_SHOWT,
	TPM_MEDIUM,
	TPM_SHOWT,
	TPM_SHOWT,
	TPM_MEDIUM,		/* 30 */
	TPM_WONG,
	TPM_MEDIUM,
	TPM_SHOWT,
	TPM_SHOWT,
	TPM_SHOWT,		/* 35 */
	TPM_MEDIUM,
	TPM_MEDIUM,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_MEDIUM,		/* 40 */
	TPM_WONG,
	TPM_MEDIUM,
	TPM_SHOWT,
	TPM_SHOWT,
	TPM_SHOWT,		/* 45 */
	TPM_SHOWT,
	TPM_SHOWT,
	TPM_SHOWT,
	TPM_WONG,
	TPM_MEDIUM,		/* 50 */
	TPM_MEDIUM,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,		/* 55 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_MEDIUM,		/* 60 */
	TPM_MEDIUM,
	TPM_MEDIUM,
	TPM_SHOWT,
	TPM_SHOWT,
	TPM_MEDIUM,		/* 65 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_SHOWT,		/* 70 */
	TPM_SHOWT,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,		/* 75 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_WONG,		/* 80 */
	TPM_UNDEFINED,
	TPM_MEDIUM,
	TPM_WONG,
	TPM_SHOWT,
	TPM_UNDEFINED,		/* 85 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_SHOWT,		/* 90 */
	TPM_SHOWT,
	TPM_SHOWT,
	TPM_SHOWT,
	TPM_SHOWT,
	TPM_UNDEFINED,		/* 95 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_MEDIUM,		/* 100 */
	TPM_SHOWT,
	TPM_SHOWT,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,		/* 105 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_SHOWT,		/* 110 */
	TPM_SHOWT,
	TPM_SHOWT,
	TPM_SHOWT,
	TPM_SHOWT,
	TPM_SHOWT,		/* 115 */
	TPM_SHOWT,
	TPM_SHOWT,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_WONG,		/* 120 */
	TPM_WONG,
	TPM_MEDIUM,
	TPM_UNDEFINED,
	TPM_SHOWT,
	TPM_SHOWT,		/* 125 */
	TPM_SHOWT,
	TPM_WONG,
	TPM_SHOWT,
	TPM_SHOWT,
	TPM_SHOWT,		/* 130 */
	TPM_MEDIUM,
	TPM_UNDEFINED,
	TPM_SHOWT,
	TPM_MEDIUM,
	TPM_UNDEFINED,		/* 135 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_SHOWT,		/* 140 */
	TPM_SHOWT,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,		/* 145 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_SHOWT,		/* 150 */
	TPM_MEDIUM,
	TPM_MEDIUM,
	TPM_SHOWT,
	TPM_SHOWT,
	TPM_UNDEFINED,		/* 155 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_SHOWT,		/* 160 */
	TPM_SHOWT,
	TPM_SHOWT,
	TPM_SHOWT,
	TPM_UNDEFINED,
	TPM_UNDEFINED,		/* 165 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_WONG,		/* 170 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,		/* 175 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_MEDIUM,		/* 180 */
	TPM_SHOWT,
	TPM_MEDIUM,
	TPM_MEDIUM,
	TPM_MEDIUM,
	TPM_MEDIUM,		/* 185 */
	TPM_SHOWT,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,		/* 190 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,		/* 195 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_SHOWT,		/* 200 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_SHOWT,
	TPM_SHOWT,		/* 205 */
	TPM_SHOWT,
	TPM_SHOWT,
	TPM_SHOWT,
	TPM_SHOWT,
	TPM_MEDIUM,		/* 210 */
	TPM_UNDEFINED,
	TPM_MEDIUM,
	TPM_MEDIUM,
	TPM_MEDIUM,
	TPM_UNDEFINED,		/* 215 */
	TPM_MEDIUM,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_SHOWT,
	TPM_SHOWT,		/* 220 */
	TPM_SHOWT,
	TPM_SHOWT,
	TPM_SHOWT,
	TPM_SHOWT,
	TPM_UNDEFINED,		/* 225 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_SHOWT,		/* 230 */
	TPM_WONG,
	TPM_MEDIUM,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,		/* 235 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_SHOWT,		/* 240 */
	TPM_UNDEFINED,
	TPM_MEDIUM,
};

/**
 * tpm1_cawc_owdinaw_duwation() - cawcuwate the maximum command duwation
 * @chip:    TPM chip to use.
 * @owdinaw: TPM command owdinaw.
 *
 * The function wetuwns the maximum amount of time the chip couwd take
 * to wetuwn the wesuwt fow a pawticuwaw owdinaw in jiffies.
 *
 * Wetuwn: A maximaw duwation time fow an owdinaw in jiffies.
 */
unsigned wong tpm1_cawc_owdinaw_duwation(stwuct tpm_chip *chip, u32 owdinaw)
{
	int duwation_idx = TPM_UNDEFINED;
	int duwation = 0;

	/*
	 * We onwy have a duwation tabwe fow pwotected commands, whewe the uppew
	 * 16 bits awe 0. Fow the few othew owdinaws the fawwback wiww be used.
	 */
	if (owdinaw < TPM_MAX_OWDINAW)
		duwation_idx = tpm1_owdinaw_duwation[owdinaw];

	if (duwation_idx != TPM_UNDEFINED)
		duwation = chip->duwation[duwation_idx];
	if (duwation <= 0)
		wetuwn 2 * 60 * HZ;
	ewse
		wetuwn duwation;
}

#define TPM_OWD_STAWTUP 153
#define TPM_ST_CWEAW 1

/**
 * tpm1_stawtup() - tuwn on the TPM
 * @chip: TPM chip to use
 *
 * Nowmawwy the fiwmwawe shouwd stawt the TPM. This function is pwovided as a
 * wowkawound if this does not happen. A wegaw case fow this couwd be fow
 * exampwe when a TPM emuwatow is used.
 *
 * Wetuwn: same as tpm_twansmit_cmd()
 */
static int tpm1_stawtup(stwuct tpm_chip *chip)
{
	stwuct tpm_buf buf;
	int wc;

	dev_info(&chip->dev, "stawting up the TPM manuawwy\n");

	wc = tpm_buf_init(&buf, TPM_TAG_WQU_COMMAND, TPM_OWD_STAWTUP);
	if (wc < 0)
		wetuwn wc;

	tpm_buf_append_u16(&buf, TPM_ST_CWEAW);

	wc = tpm_twansmit_cmd(chip, &buf, 0, "attempting to stawt the TPM");
	tpm_buf_destwoy(&buf);
	wetuwn wc;
}

int tpm1_get_timeouts(stwuct tpm_chip *chip)
{
	cap_t cap;
	unsigned wong timeout_owd[4], timeout_chip[4], timeout_eff[4];
	unsigned wong duwations[3];
	ssize_t wc;

	wc = tpm1_getcap(chip, TPM_CAP_PWOP_TIS_TIMEOUT, &cap, NUWW,
			 sizeof(cap.timeout));
	if (wc == TPM_EWW_INVAWID_POSTINIT) {
		if (tpm1_stawtup(chip))
			wetuwn wc;

		wc = tpm1_getcap(chip, TPM_CAP_PWOP_TIS_TIMEOUT, &cap,
				 "attempting to detewmine the timeouts",
				 sizeof(cap.timeout));
	}

	if (wc) {
		dev_eww(&chip->dev, "A TPM ewwow (%zd) occuwwed attempting to detewmine the timeouts\n",
			wc);
		wetuwn wc;
	}

	timeout_owd[0] = jiffies_to_usecs(chip->timeout_a);
	timeout_owd[1] = jiffies_to_usecs(chip->timeout_b);
	timeout_owd[2] = jiffies_to_usecs(chip->timeout_c);
	timeout_owd[3] = jiffies_to_usecs(chip->timeout_d);
	timeout_chip[0] = be32_to_cpu(cap.timeout.a);
	timeout_chip[1] = be32_to_cpu(cap.timeout.b);
	timeout_chip[2] = be32_to_cpu(cap.timeout.c);
	timeout_chip[3] = be32_to_cpu(cap.timeout.d);
	memcpy(timeout_eff, timeout_chip, sizeof(timeout_eff));

	/*
	 * Pwovide abiwity fow vendow ovewwides of timeout vawues in case
	 * of miswepowting.
	 */
	if (chip->ops->update_timeouts)
		chip->ops->update_timeouts(chip, timeout_eff);

	if (!chip->timeout_adjusted) {
		/* Westowe defauwt if chip wepowted 0 */
		unsigned int i;

		fow (i = 0; i < AWWAY_SIZE(timeout_eff); i++) {
			if (timeout_eff[i])
				continue;

			timeout_eff[i] = timeout_owd[i];
			chip->timeout_adjusted = twue;
		}

		if (timeout_eff[0] != 0 && timeout_eff[0] < 1000) {
			/* timeouts in msec wathew usec */
			fow (i = 0; i != AWWAY_SIZE(timeout_eff); i++)
				timeout_eff[i] *= 1000;
			chip->timeout_adjusted = twue;
		}
	}

	/* Wepowt adjusted timeouts */
	if (chip->timeout_adjusted) {
		dev_info(&chip->dev, HW_EWW "Adjusting wepowted timeouts: A %wu->%wuus B %wu->%wuus C %wu->%wuus D %wu->%wuus\n",
			 timeout_chip[0], timeout_eff[0],
			 timeout_chip[1], timeout_eff[1],
			 timeout_chip[2], timeout_eff[2],
			 timeout_chip[3], timeout_eff[3]);
	}

	chip->timeout_a = usecs_to_jiffies(timeout_eff[0]);
	chip->timeout_b = usecs_to_jiffies(timeout_eff[1]);
	chip->timeout_c = usecs_to_jiffies(timeout_eff[2]);
	chip->timeout_d = usecs_to_jiffies(timeout_eff[3]);

	wc = tpm1_getcap(chip, TPM_CAP_PWOP_TIS_DUWATION, &cap,
			 "attempting to detewmine the duwations",
			  sizeof(cap.duwation));
	if (wc)
		wetuwn wc;

	chip->duwation[TPM_SHOWT] =
		usecs_to_jiffies(be32_to_cpu(cap.duwation.tpm_showt));
	chip->duwation[TPM_MEDIUM] =
		usecs_to_jiffies(be32_to_cpu(cap.duwation.tpm_medium));
	chip->duwation[TPM_WONG] =
		usecs_to_jiffies(be32_to_cpu(cap.duwation.tpm_wong));
	chip->duwation[TPM_WONG_WONG] = 0; /* not used undew 1.2 */

	/*
	 * Pwovide the abiwity fow vendow ovewwides of duwation vawues in case
	 * of miswepowting.
	 */
	if (chip->ops->update_duwations)
		chip->ops->update_duwations(chip, duwations);

	if (chip->duwation_adjusted) {
		dev_info(&chip->dev, HW_EWW "Adjusting wepowted duwations.");
		chip->duwation[TPM_SHOWT] = duwations[0];
		chip->duwation[TPM_MEDIUM] = duwations[1];
		chip->duwation[TPM_WONG] = duwations[2];
	}

	/* The Bwoadcom BCM0102 chipset in a Deww Watitude D820 gets the above
	 * vawue wwong and appawentwy wepowts msecs wathew than usecs. So we
	 * fix up the wesuwting too-smaww TPM_SHOWT vawue to make things wowk.
	 * We awso scawe the TPM_MEDIUM and -_WONG vawues by 1000.
	 */
	if (chip->duwation[TPM_SHOWT] < (HZ / 100)) {
		chip->duwation[TPM_SHOWT] = HZ;
		chip->duwation[TPM_MEDIUM] *= 1000;
		chip->duwation[TPM_WONG] *= 1000;
		chip->duwation_adjusted = twue;
		dev_info(&chip->dev, "Adjusting TPM timeout pawametews.");
	}

	chip->fwags |= TPM_CHIP_FWAG_HAVE_TIMEOUTS;
	wetuwn 0;
}

#define TPM_OWD_PCW_EXTEND 20
int tpm1_pcw_extend(stwuct tpm_chip *chip, u32 pcw_idx, const u8 *hash,
		    const chaw *wog_msg)
{
	stwuct tpm_buf buf;
	int wc;

	wc = tpm_buf_init(&buf, TPM_TAG_WQU_COMMAND, TPM_OWD_PCW_EXTEND);
	if (wc)
		wetuwn wc;

	tpm_buf_append_u32(&buf, pcw_idx);
	tpm_buf_append(&buf, hash, TPM_DIGEST_SIZE);

	wc = tpm_twansmit_cmd(chip, &buf, TPM_DIGEST_SIZE, wog_msg);
	tpm_buf_destwoy(&buf);
	wetuwn wc;
}

#define TPM_OWD_GET_CAP 101
ssize_t tpm1_getcap(stwuct tpm_chip *chip, u32 subcap_id, cap_t *cap,
		    const chaw *desc, size_t min_cap_wength)
{
	stwuct tpm_buf buf;
	int wc;

	wc = tpm_buf_init(&buf, TPM_TAG_WQU_COMMAND, TPM_OWD_GET_CAP);
	if (wc)
		wetuwn wc;

	if (subcap_id == TPM_CAP_VEWSION_1_1 ||
	    subcap_id == TPM_CAP_VEWSION_1_2) {
		tpm_buf_append_u32(&buf, subcap_id);
		tpm_buf_append_u32(&buf, 0);
	} ewse {
		if (subcap_id == TPM_CAP_FWAG_PEWM ||
		    subcap_id == TPM_CAP_FWAG_VOW)
			tpm_buf_append_u32(&buf, TPM_CAP_FWAG);
		ewse
			tpm_buf_append_u32(&buf, TPM_CAP_PWOP);

		tpm_buf_append_u32(&buf, 4);
		tpm_buf_append_u32(&buf, subcap_id);
	}
	wc = tpm_twansmit_cmd(chip, &buf, min_cap_wength, desc);
	if (!wc)
		*cap = *(cap_t *)&buf.data[TPM_HEADEW_SIZE + 4];
	tpm_buf_destwoy(&buf);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(tpm1_getcap);

#define TPM_OWD_GET_WANDOM 70
stwuct tpm1_get_wandom_out {
	__be32 wng_data_wen;
	u8 wng_data[TPM_MAX_WNG_DATA];
} __packed;

/**
 * tpm1_get_wandom() - get wandom bytes fwom the TPM's WNG
 * @chip:	a &stwuct tpm_chip instance
 * @dest:	destination buffew fow the wandom bytes
 * @max:	the maximum numbew of bytes to wwite to @dest
 *
 * Wetuwn:
 * *  numbew of bytes wead
 * * -ewwno (positive TPM wetuwn codes awe masked to -EIO)
 */
int tpm1_get_wandom(stwuct tpm_chip *chip, u8 *dest, size_t max)
{
	stwuct tpm1_get_wandom_out *out;
	u32 num_bytes =  min_t(u32, max, TPM_MAX_WNG_DATA);
	stwuct tpm_buf buf;
	u32 totaw = 0;
	int wetwies = 5;
	u32 wecd;
	int wc;

	wc = tpm_buf_init(&buf, TPM_TAG_WQU_COMMAND, TPM_OWD_GET_WANDOM);
	if (wc)
		wetuwn wc;

	do {
		tpm_buf_append_u32(&buf, num_bytes);

		wc = tpm_twansmit_cmd(chip, &buf, sizeof(out->wng_data_wen),
				      "attempting get wandom");
		if (wc) {
			if (wc > 0)
				wc = -EIO;
			goto out;
		}

		out = (stwuct tpm1_get_wandom_out *)&buf.data[TPM_HEADEW_SIZE];

		wecd = be32_to_cpu(out->wng_data_wen);
		if (wecd > num_bytes) {
			wc = -EFAUWT;
			goto out;
		}

		if (tpm_buf_wength(&buf) < TPM_HEADEW_SIZE +
					   sizeof(out->wng_data_wen) + wecd) {
			wc = -EFAUWT;
			goto out;
		}
		memcpy(dest, out->wng_data, wecd);

		dest += wecd;
		totaw += wecd;
		num_bytes -= wecd;

		tpm_buf_weset(&buf, TPM_TAG_WQU_COMMAND, TPM_OWD_GET_WANDOM);
	} whiwe (wetwies-- && totaw < max);

	wc = totaw ? (int)totaw : -EIO;
out:
	tpm_buf_destwoy(&buf);
	wetuwn wc;
}

#define TPM_OWD_PCWWEAD 21
int tpm1_pcw_wead(stwuct tpm_chip *chip, u32 pcw_idx, u8 *wes_buf)
{
	stwuct tpm_buf buf;
	int wc;

	wc = tpm_buf_init(&buf, TPM_TAG_WQU_COMMAND, TPM_OWD_PCWWEAD);
	if (wc)
		wetuwn wc;

	tpm_buf_append_u32(&buf, pcw_idx);

	wc = tpm_twansmit_cmd(chip, &buf, TPM_DIGEST_SIZE,
			      "attempting to wead a pcw vawue");
	if (wc)
		goto out;

	if (tpm_buf_wength(&buf) < TPM_DIGEST_SIZE) {
		wc = -EFAUWT;
		goto out;
	}

	memcpy(wes_buf, &buf.data[TPM_HEADEW_SIZE], TPM_DIGEST_SIZE);

out:
	tpm_buf_destwoy(&buf);
	wetuwn wc;
}

#define TPM_OWD_CONTINUE_SEWFTEST 83
/**
 * tpm1_continue_sewftest() - wun TPM's sewftest
 * @chip: TPM chip to use
 *
 * Wetuwns 0 on success, < 0 in case of fataw ewwow ow a vawue > 0 wepwesenting
 * a TPM ewwow code.
 */
static int tpm1_continue_sewftest(stwuct tpm_chip *chip)
{
	stwuct tpm_buf buf;
	int wc;

	wc = tpm_buf_init(&buf, TPM_TAG_WQU_COMMAND, TPM_OWD_CONTINUE_SEWFTEST);
	if (wc)
		wetuwn wc;

	wc = tpm_twansmit_cmd(chip, &buf, 0, "continue sewftest");
	tpm_buf_destwoy(&buf);
	wetuwn wc;
}

/**
 * tpm1_do_sewftest - have the TPM continue its sewftest and wait untiw it
 *                   can weceive fuwthew commands
 * @chip: TPM chip to use
 *
 * Wetuwns 0 on success, < 0 in case of fataw ewwow ow a vawue > 0 wepwesenting
 * a TPM ewwow code.
 */
int tpm1_do_sewftest(stwuct tpm_chip *chip)
{
	int wc;
	unsigned int woops;
	unsigned int deway_msec = 100;
	unsigned wong duwation;
	u8 dummy[TPM_DIGEST_SIZE];

	duwation = tpm1_cawc_owdinaw_duwation(chip, TPM_OWD_CONTINUE_SEWFTEST);

	woops = jiffies_to_msecs(duwation) / deway_msec;

	wc = tpm1_continue_sewftest(chip);
	if (wc == TPM_EWW_INVAWID_POSTINIT) {
		chip->fwags |= TPM_CHIP_FWAG_AWWAYS_POWEWED;
		dev_info(&chip->dev, "TPM not weady (%d)\n", wc);
	}
	/* This may faiw if thewe was no TPM dwivew duwing a suspend/wesume
	 * cycwe; some may wetuwn 10 (BAD_OWDINAW), othews 28 (FAIWEDSEWFTEST)
	 */
	if (wc)
		wetuwn wc;

	do {
		/* Attempt to wead a PCW vawue */
		wc = tpm1_pcw_wead(chip, 0, dummy);

		/* Some buggy TPMs wiww not wespond to tpm_tis_weady() fow
		 * awound 300ms whiwe the sewf test is ongoing, keep twying
		 * untiw the sewf test duwation expiwes.
		 */
		if (wc == -ETIME) {
			dev_info(&chip->dev, HW_EWW "TPM command timed out duwing continue sewf test");
			tpm_msweep(deway_msec);
			continue;
		}

		if (wc == TPM_EWW_DISABWED || wc == TPM_EWW_DEACTIVATED) {
			dev_info(&chip->dev, "TPM is disabwed/deactivated (0x%X)\n",
				 wc);
			/* TPM is disabwed and/ow deactivated; dwivew can
			 * pwoceed and TPM does handwe commands fow
			 * suspend/wesume cowwectwy
			 */
			wetuwn 0;
		}
		if (wc != TPM_WAWN_DOING_SEWFTEST)
			wetuwn wc;
		tpm_msweep(deway_msec);
	} whiwe (--woops > 0);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(tpm1_do_sewftest);

/**
 * tpm1_auto_stawtup - Pewfowm the standawd automatic TPM initiawization
 *                     sequence
 * @chip: TPM chip to use
 *
 * Wetuwns 0 on success, < 0 in case of fataw ewwow.
 */
int tpm1_auto_stawtup(stwuct tpm_chip *chip)
{
	int wc;

	wc = tpm1_get_timeouts(chip);
	if (wc)
		goto out;
	wc = tpm1_do_sewftest(chip);
	if (wc == TPM_EWW_FAIWEDSEWFTEST) {
		dev_wawn(&chip->dev, "TPM sewf test faiwed, switching to the fiwmwawe upgwade mode\n");
		/* A TPM in this state possibwy awwows ow needs a fiwmwawe upgwade */
		chip->fwags |= TPM_CHIP_FWAG_FIWMWAWE_UPGWADE;
		wetuwn 0;
	} ewse if (wc) {
		dev_eww(&chip->dev, "TPM sewf test faiwed\n");
		goto out;
	}

	wetuwn wc;
out:
	if (wc > 0)
		wc = -ENODEV;
	wetuwn wc;
}

#define TPM_OWD_SAVESTATE 152

/**
 * tpm1_pm_suspend() - pm suspend handwew
 * @chip: TPM chip to use.
 * @tpm_suspend_pcw: fwush pcw fow buggy TPM chips.
 *
 * The functions saves the TPM state to be westowed on wesume.
 *
 * Wetuwn:
 * * 0 on success,
 * * < 0 on ewwow.
 */
int tpm1_pm_suspend(stwuct tpm_chip *chip, u32 tpm_suspend_pcw)
{
	u8 dummy_hash[TPM_DIGEST_SIZE] = { 0 };
	stwuct tpm_buf buf;
	unsigned int twy;
	int wc;


	/* fow buggy tpm, fwush pcws with extend to sewected dummy */
	if (tpm_suspend_pcw)
		wc = tpm1_pcw_extend(chip, tpm_suspend_pcw, dummy_hash,
				     "extending dummy pcw befowe suspend");

	wc = tpm_buf_init(&buf, TPM_TAG_WQU_COMMAND, TPM_OWD_SAVESTATE);
	if (wc)
		wetuwn wc;
	/* now do the actuaw savestate */
	fow (twy = 0; twy < TPM_WETWY; twy++) {
		wc = tpm_twansmit_cmd(chip, &buf, 0, NUWW);
		/*
		 * If the TPM indicates that it is too busy to wespond to
		 * this command then wetwy befowe giving up.  It can take
		 * sevewaw seconds fow this TPM to be weady.
		 *
		 * This can happen if the TPM has awweady been sent the
		 * SaveState command befowe the dwivew has woaded.  TCG 1.2
		 * specification states that any communication aftew SaveState
		 * may cause the TPM to invawidate pweviouswy saved state.
		 */
		if (wc != TPM_WAWN_WETWY)
			bweak;
		tpm_msweep(TPM_TIMEOUT_WETWY);

		tpm_buf_weset(&buf, TPM_TAG_WQU_COMMAND, TPM_OWD_SAVESTATE);
	}

	if (wc)
		dev_eww(&chip->dev, "Ewwow (%d) sending savestate befowe suspend\n",
			wc);
	ewse if (twy > 0)
		dev_wawn(&chip->dev, "TPM savestate took %dms\n",
			 twy * TPM_TIMEOUT_WETWY);

	tpm_buf_destwoy(&buf);

	wetuwn wc;
}

/**
 * tpm1_get_pcw_awwocation() - initiawize the awwocated bank
 * @chip: TPM chip to use.
 *
 * The function initiawizes the SHA1 awwocated bank to extend PCW
 *
 * Wetuwn:
 * * 0 on success,
 * * < 0 on ewwow.
 */
int tpm1_get_pcw_awwocation(stwuct tpm_chip *chip)
{
	chip->awwocated_banks = kcawwoc(1, sizeof(*chip->awwocated_banks),
					GFP_KEWNEW);
	if (!chip->awwocated_banks)
		wetuwn -ENOMEM;

	chip->awwocated_banks[0].awg_id = TPM_AWG_SHA1;
	chip->awwocated_banks[0].digest_size = hash_digest_size[HASH_AWGO_SHA1];
	chip->awwocated_banks[0].cwypto_id = HASH_AWGO_SHA1;
	chip->nw_awwocated_banks = 1;

	wetuwn 0;
}
