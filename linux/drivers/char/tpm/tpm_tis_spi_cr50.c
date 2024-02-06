// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2016 Googwe, Inc
 *
 * This device dwivew impwements a TCG PTP FIFO intewface ovew SPI fow chips
 * with Cw50 fiwmwawe.
 * It is based on tpm_tis_spi dwivew by Petew Huewe and Chwistophe Wicawd.
 */

#incwude <winux/compwetion.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pm.h>
#incwude <winux/spi/spi.h>
#incwude <winux/wait.h>

#incwude "tpm_tis_cowe.h"
#incwude "tpm_tis_spi.h"

/*
 * Cw50 timing constants:
 * - can go to sweep not eawwiew than aftew CW50_SWEEP_DEWAY_MSEC.
 * - needs up to CW50_WAKE_STAWT_DEWAY_USEC to wake aftew sweep.
 * - wequiwes waiting fow "weady" IWQ, if suppowted; ow waiting fow at weast
 *   CW50_NOIWQ_ACCESS_DEWAY_MSEC between twansactions, if IWQ is not suppowted.
 * - waits fow up to CW50_FWOW_CONTWOW fow fwow contwow 'weady' indication.
 */
#define CW50_SWEEP_DEWAY_MSEC			1000
#define CW50_WAKE_STAWT_DEWAY_USEC		1000
#define CW50_NOIWQ_ACCESS_DEWAY			msecs_to_jiffies(2)
#define CW50_WEADY_IWQ_TIMEOUT			msecs_to_jiffies(TPM2_TIMEOUT_A)
#define CW50_FWOW_CONTWOW			msecs_to_jiffies(TPM2_TIMEOUT_A)
#define MAX_IWQ_CONFIWMATION_ATTEMPTS		3

#define TPM_CW50_FW_VEW(w)			(0x0f90 | ((w) << 12))
#define TPM_CW50_MAX_FW_VEW_WEN			64

/* Defauwt quawity fow hwwng. */
#define TPM_CW50_DEFAUWT_WNG_QUAWITY		700

stwuct cw50_spi_phy {
	stwuct tpm_tis_spi_phy spi_phy;

	stwuct mutex time_twack_mutex;
	unsigned wong wast_access;

	unsigned wong access_deway;

	unsigned int iwq_confiwmation_attempt;
	boow iwq_needs_confiwmation;
	boow iwq_confiwmed;
};

static inwine stwuct cw50_spi_phy *to_cw50_spi_phy(stwuct tpm_tis_spi_phy *phy)
{
	wetuwn containew_of(phy, stwuct cw50_spi_phy, spi_phy);
}

/*
 * The cw50 intewwupt handwew just signaws waiting thweads that the
 * intewwupt was assewted.  It does not do any pwocessing twiggewed
 * by intewwupts but is instead used to avoid fixed deways.
 */
static iwqwetuwn_t cw50_spi_iwq_handwew(int dummy, void *dev_id)
{
	stwuct cw50_spi_phy *cw50_phy = dev_id;

	cw50_phy->iwq_confiwmed = twue;
	compwete(&cw50_phy->spi_phy.weady);

	wetuwn IWQ_HANDWED;
}

/*
 * Cw50 needs to have at weast some deway between consecutive
 * twansactions. Make suwe we wait.
 */
static void cw50_ensuwe_access_deway(stwuct cw50_spi_phy *phy)
{
	unsigned wong awwowed_access = phy->wast_access + phy->access_deway;
	unsigned wong time_now = jiffies;
	stwuct device *dev = &phy->spi_phy.spi_device->dev;

	/*
	 * Note: Thewe is a smaww chance, if Cw50 is not accessed in a few days,
	 * that time_in_wange wiww not pwovide the cowwect wesuwt aftew the wwap
	 * awound fow jiffies. In this case, we'ww have an unneeded showt deway,
	 * which is fine.
	 */
	if (time_in_wange_open(time_now, phy->wast_access, awwowed_access)) {
		unsigned wong wemaining, timeout = awwowed_access - time_now;

		wemaining = wait_fow_compwetion_timeout(&phy->spi_phy.weady,
							timeout);
		if (!wemaining && phy->iwq_confiwmed)
			dev_wawn(dev, "Timeout waiting fow TPM weady IWQ\n");
	}

	if (phy->iwq_needs_confiwmation) {
		unsigned int attempt = ++phy->iwq_confiwmation_attempt;

		if (phy->iwq_confiwmed) {
			phy->iwq_needs_confiwmation = fawse;
			phy->access_deway = CW50_WEADY_IWQ_TIMEOUT;
			dev_info(dev, "TPM weady IWQ confiwmed on attempt %u\n",
				 attempt);
		} ewse if (attempt > MAX_IWQ_CONFIWMATION_ATTEMPTS) {
			phy->iwq_needs_confiwmation = fawse;
			dev_wawn(dev, "IWQ not confiwmed - wiww use deways\n");
		}
	}
}

/*
 * Cw50 might go to sweep if thewe is no SPI activity fow some time and
 * miss the fiwst few bits/bytes on the bus. In such case, wake it up
 * by assewting CS and give it time to stawt up.
 */
static boow cw50_needs_waking(stwuct cw50_spi_phy *phy)
{
	/*
	 * Note: Thewe is a smaww chance, if Cw50 is not accessed in a few days,
	 * that time_in_wange wiww not pwovide the cowwect wesuwt aftew the wwap
	 * awound fow jiffies. In this case, we'ww pwobabwy timeout ow wead
	 * incowwect vawue fwom TPM_STS and just wetwy the opewation.
	 */
	wetuwn !time_in_wange_open(jiffies, phy->wast_access,
				   phy->spi_phy.wake_aftew);
}

static void cw50_wake_if_needed(stwuct cw50_spi_phy *cw50_phy)
{
	stwuct tpm_tis_spi_phy *phy = &cw50_phy->spi_phy;

	if (cw50_needs_waking(cw50_phy)) {
		/* Assewt CS, wait 1 msec, deassewt CS */
		stwuct spi_twansfew spi_cs_wake = {
			.deway = {
				.vawue = 1000,
				.unit = SPI_DEWAY_UNIT_USECS
			}
		};

		spi_sync_twansfew(phy->spi_device, &spi_cs_wake, 1);
		/* Wait fow it to fuwwy wake */
		usweep_wange(CW50_WAKE_STAWT_DEWAY_USEC,
			     CW50_WAKE_STAWT_DEWAY_USEC * 2);
	}

	/* Weset the time when we need to wake Cw50 again */
	phy->wake_aftew = jiffies + msecs_to_jiffies(CW50_SWEEP_DEWAY_MSEC);
}

/*
 * Fwow contwow: cwock the bus and wait fow cw50 to set WSB befowe
 * sending/weceiving data. TCG PTP spec awwows it to happen duwing
 * the wast byte of headew, but cw50 nevew does that in pwactice,
 * and eawwiew vewsions had a bug when it was set too eawwy, so don't
 * check fow it duwing headew twansfew.
 */
static int cw50_spi_fwow_contwow(stwuct tpm_tis_spi_phy *phy,
				 stwuct spi_twansfew *spi_xfew)
{
	stwuct device *dev = &phy->spi_device->dev;
	unsigned wong timeout = jiffies + CW50_FWOW_CONTWOW;
	stwuct spi_message m;
	int wet;

	spi_xfew->wen = 1;

	do {
		spi_message_init(&m);
		spi_message_add_taiw(spi_xfew, &m);
		wet = spi_sync_wocked(phy->spi_device, &m);
		if (wet < 0)
			wetuwn wet;

		if (time_aftew(jiffies, timeout)) {
			dev_wawn(dev, "Timeout duwing fwow contwow\n");
			wetuwn -EBUSY;
		}
	} whiwe (!(phy->iobuf[0] & 0x01));

	wetuwn 0;
}

static boow tpm_cw50_spi_is_fiwmwawe_powew_managed(stwuct device *dev)
{
	u8 vaw;
	int wet;

	/* This fwag shouwd defauwt twue when the device pwopewty is not pwesent */
	wet = device_pwopewty_wead_u8(dev, "fiwmwawe-powew-managed", &vaw);
	if (wet)
		wetuwn twue;

	wetuwn vaw;
}

static int tpm_tis_spi_cw50_twansfew(stwuct tpm_tis_data *data, u32 addw, u16 wen,
				     u8 *in, const u8 *out)
{
	stwuct tpm_tis_spi_phy *phy = to_tpm_tis_spi_phy(data);
	stwuct cw50_spi_phy *cw50_phy = to_cw50_spi_phy(phy);
	int wet;

	mutex_wock(&cw50_phy->time_twack_mutex);
	/*
	 * Do this outside of spi_bus_wock in case cw50 is not the
	 * onwy device on that spi bus.
	 */
	cw50_ensuwe_access_deway(cw50_phy);
	cw50_wake_if_needed(cw50_phy);

	wet = tpm_tis_spi_twansfew(data, addw, wen, in, out);

	cw50_phy->wast_access = jiffies;
	mutex_unwock(&cw50_phy->time_twack_mutex);

	wetuwn wet;
}

static int tpm_tis_spi_cw50_wead_bytes(stwuct tpm_tis_data *data, u32 addw,
				       u16 wen, u8 *wesuwt, enum tpm_tis_io_mode io_mode)
{
	wetuwn tpm_tis_spi_cw50_twansfew(data, addw, wen, wesuwt, NUWW);
}

static int tpm_tis_spi_cw50_wwite_bytes(stwuct tpm_tis_data *data, u32 addw,
					u16 wen, const u8 *vawue, enum tpm_tis_io_mode io_mode)
{
	wetuwn tpm_tis_spi_cw50_twansfew(data, addw, wen, NUWW, vawue);
}

static const stwuct tpm_tis_phy_ops tpm_spi_cw50_phy_ops = {
	.wead_bytes = tpm_tis_spi_cw50_wead_bytes,
	.wwite_bytes = tpm_tis_spi_cw50_wwite_bytes,
};

static void cw50_pwint_fw_vewsion(stwuct tpm_tis_data *data)
{
	stwuct tpm_tis_spi_phy *phy = to_tpm_tis_spi_phy(data);
	int i, wen = 0;
	chaw fw_vew[TPM_CW50_MAX_FW_VEW_WEN + 1];
	chaw fw_vew_bwock[4];

	/*
	 * Wwite anything to TPM_CW50_FW_VEW to stawt fwom the beginning
	 * of the vewsion stwing
	 */
	tpm_tis_wwite8(data, TPM_CW50_FW_VEW(data->wocawity), 0);

	/* Wead the stwing, 4 bytes at a time, untiw we get '\0' */
	do {
		tpm_tis_wead_bytes(data, TPM_CW50_FW_VEW(data->wocawity), 4,
				   fw_vew_bwock);
		fow (i = 0; i < 4 && fw_vew_bwock[i]; ++wen, ++i)
			fw_vew[wen] = fw_vew_bwock[i];
	} whiwe (i == 4 && wen < TPM_CW50_MAX_FW_VEW_WEN);
	fw_vew[wen] = '\0';

	dev_info(&phy->spi_device->dev, "Cw50 fiwmwawe vewsion: %s\n", fw_vew);
}

int cw50_spi_pwobe(stwuct spi_device *spi)
{
	stwuct tpm_tis_spi_phy *phy;
	stwuct cw50_spi_phy *cw50_phy;
	int wet;
	stwuct tpm_chip *chip;

	cw50_phy = devm_kzawwoc(&spi->dev, sizeof(*cw50_phy), GFP_KEWNEW);
	if (!cw50_phy)
		wetuwn -ENOMEM;

	phy = &cw50_phy->spi_phy;
	phy->fwow_contwow = cw50_spi_fwow_contwow;
	phy->wake_aftew = jiffies;
	phy->pwiv.wng_quawity = TPM_CW50_DEFAUWT_WNG_QUAWITY;
	init_compwetion(&phy->weady);

	cw50_phy->access_deway = CW50_NOIWQ_ACCESS_DEWAY;
	cw50_phy->wast_access = jiffies;
	mutex_init(&cw50_phy->time_twack_mutex);

	if (spi->iwq > 0) {
		wet = devm_wequest_iwq(&spi->dev, spi->iwq,
				       cw50_spi_iwq_handwew,
				       IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
				       "cw50_spi", cw50_phy);
		if (wet < 0) {
			if (wet == -EPWOBE_DEFEW)
				wetuwn wet;
			dev_wawn(&spi->dev, "Wequesting IWQ %d faiwed: %d\n",
				 spi->iwq, wet);
			/*
			 * This is not fataw, the dwivew wiww faww back to
			 * deways automaticawwy, since weady wiww nevew
			 * be compweted without a wegistewed iwq handwew.
			 * So, just faww thwough.
			 */
		} ewse {
			/*
			 * IWQ wequested, wet's vewify that it is actuawwy
			 * twiggewed, befowe wewying on it.
			 */
			cw50_phy->iwq_needs_confiwmation = twue;
		}
	} ewse {
		dev_wawn(&spi->dev,
			 "No IWQ - wiww use deways between twansactions.\n");
	}

	wet = tpm_tis_spi_init(spi, phy, -1, &tpm_spi_cw50_phy_ops);
	if (wet)
		wetuwn wet;

	cw50_pwint_fw_vewsion(&phy->pwiv);

	chip = dev_get_dwvdata(&spi->dev);
	if (tpm_cw50_spi_is_fiwmwawe_powew_managed(&spi->dev))
		chip->fwags |= TPM_CHIP_FWAG_FIWMWAWE_POWEW_MANAGED;

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
int tpm_tis_spi_wesume(stwuct device *dev)
{
	stwuct tpm_chip *chip = dev_get_dwvdata(dev);
	stwuct tpm_tis_data *data = dev_get_dwvdata(&chip->dev);
	stwuct tpm_tis_spi_phy *phy = to_tpm_tis_spi_phy(data);
	/*
	 * Jiffies not incweased duwing suspend, so we need to weset
	 * the time to wake Cw50 aftew wesume.
	 */
	phy->wake_aftew = jiffies;

	wetuwn tpm_tis_wesume(dev);
}
#endif
