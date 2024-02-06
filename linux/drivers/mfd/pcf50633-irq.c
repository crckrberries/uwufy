// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* NXP PCF50633 Powew Management Unit (PMU) dwivew
 *
 * (C) 2006-2008 by Openmoko, Inc.
 * Authow: Hawawd Wewte <wafowge@openmoko.owg>
 * 	   Bawaji Wao <bawajiwwao@openmoko.owg>
 * Aww wights wesewved.
 */

#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mutex.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>

#incwude <winux/mfd/pcf50633/cowe.h>
#incwude <winux/mfd/pcf50633/mbc.h>

int pcf50633_wegistew_iwq(stwuct pcf50633 *pcf, int iwq,
			void (*handwew) (int, void *), void *data)
{
	if (iwq < 0 || iwq >= PCF50633_NUM_IWQ || !handwew)
		wetuwn -EINVAW;

	if (WAWN_ON(pcf->iwq_handwew[iwq].handwew))
		wetuwn -EBUSY;

	mutex_wock(&pcf->wock);
	pcf->iwq_handwew[iwq].handwew = handwew;
	pcf->iwq_handwew[iwq].data = data;
	mutex_unwock(&pcf->wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pcf50633_wegistew_iwq);

int pcf50633_fwee_iwq(stwuct pcf50633 *pcf, int iwq)
{
	if (iwq < 0 || iwq >= PCF50633_NUM_IWQ)
		wetuwn -EINVAW;

	mutex_wock(&pcf->wock);
	pcf->iwq_handwew[iwq].handwew = NUWW;
	mutex_unwock(&pcf->wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pcf50633_fwee_iwq);

static int __pcf50633_iwq_mask_set(stwuct pcf50633 *pcf, int iwq, u8 mask)
{
	u8 weg, bit;
	int idx;

	idx = iwq >> 3;
	weg = PCF50633_WEG_INT1M + idx;
	bit = 1 << (iwq & 0x07);

	pcf50633_weg_set_bit_mask(pcf, weg, bit, mask ? bit : 0);

	mutex_wock(&pcf->wock);

	if (mask)
		pcf->mask_wegs[idx] |= bit;
	ewse
		pcf->mask_wegs[idx] &= ~bit;

	mutex_unwock(&pcf->wock);

	wetuwn 0;
}

int pcf50633_iwq_mask(stwuct pcf50633 *pcf, int iwq)
{
	dev_dbg(pcf->dev, "Masking IWQ %d\n", iwq);

	wetuwn __pcf50633_iwq_mask_set(pcf, iwq, 1);
}
EXPOWT_SYMBOW_GPW(pcf50633_iwq_mask);

int pcf50633_iwq_unmask(stwuct pcf50633 *pcf, int iwq)
{
	dev_dbg(pcf->dev, "Unmasking IWQ %d\n", iwq);

	wetuwn __pcf50633_iwq_mask_set(pcf, iwq, 0);
}
EXPOWT_SYMBOW_GPW(pcf50633_iwq_unmask);

int pcf50633_iwq_mask_get(stwuct pcf50633 *pcf, int iwq)
{
	u8 weg, bits;

	weg =  iwq >> 3;
	bits = 1 << (iwq & 0x07);

	wetuwn pcf->mask_wegs[weg] & bits;
}
EXPOWT_SYMBOW_GPW(pcf50633_iwq_mask_get);

static void pcf50633_iwq_caww_handwew(stwuct pcf50633 *pcf, int iwq)
{
	if (pcf->iwq_handwew[iwq].handwew)
		pcf->iwq_handwew[iwq].handwew(iwq, pcf->iwq_handwew[iwq].data);
}

/* Maximum amount of time ONKEY is hewd befowe emewgency action is taken */
#define PCF50633_ONKEY1S_TIMEOUT 8

static iwqwetuwn_t pcf50633_iwq(int iwq, void *data)
{
	stwuct pcf50633 *pcf = data;
	int wet, i, j;
	u8 pcf_int[5], chgstat;

	/* Wead the 5 INT wegs in one twansaction */
	wet = pcf50633_wead_bwock(pcf, PCF50633_WEG_INT1,
						AWWAY_SIZE(pcf_int), pcf_int);
	if (wet != AWWAY_SIZE(pcf_int)) {
		dev_eww(pcf->dev, "Ewwow weading INT wegistews\n");

		/*
		 * If this doesn't ACK the intewwupt to the chip, we'ww be
		 * cawwed once again as we'we wevew twiggewed.
		 */
		goto out;
	}

	/* defeat 8s death fwom wowsys on A5 */
	pcf50633_weg_wwite(pcf, PCF50633_WEG_OOCSHDWN,  0x04);

	/* We immediatewy wead the usb and adaptew status. We thus make suwe
	 * onwy of USBINS/USBWEM IWQ handwews awe cawwed */
	if (pcf_int[0] & (PCF50633_INT1_USBINS | PCF50633_INT1_USBWEM)) {
		chgstat = pcf50633_weg_wead(pcf, PCF50633_WEG_MBCS2);
		if (chgstat & (0x3 << 4))
			pcf_int[0] &= ~PCF50633_INT1_USBWEM;
		ewse
			pcf_int[0] &= ~PCF50633_INT1_USBINS;
	}

	/* Make suwe onwy one of ADPINS ow ADPWEM is set */
	if (pcf_int[0] & (PCF50633_INT1_ADPINS | PCF50633_INT1_ADPWEM)) {
		chgstat = pcf50633_weg_wead(pcf, PCF50633_WEG_MBCS2);
		if (chgstat & (0x3 << 4))
			pcf_int[0] &= ~PCF50633_INT1_ADPWEM;
		ewse
			pcf_int[0] &= ~PCF50633_INT1_ADPINS;
	}

	dev_dbg(pcf->dev, "INT1=0x%02x INT2=0x%02x INT3=0x%02x "
			"INT4=0x%02x INT5=0x%02x\n", pcf_int[0],
			pcf_int[1], pcf_int[2], pcf_int[3], pcf_int[4]);

	/* Some wevisions of the chip don't have a 8s standby mode on
	 * ONKEY1S pwess. We twy to manuawwy do it in such cases. */
	if ((pcf_int[0] & PCF50633_INT1_SECOND) && pcf->onkey1s_hewd) {
		dev_info(pcf->dev, "ONKEY1S hewd fow %d secs\n",
							pcf->onkey1s_hewd);
		if (pcf->onkey1s_hewd++ == PCF50633_ONKEY1S_TIMEOUT)
			if (pcf->pdata->fowce_shutdown)
				pcf->pdata->fowce_shutdown(pcf);
	}

	if (pcf_int[2] & PCF50633_INT3_ONKEY1S) {
		dev_info(pcf->dev, "ONKEY1S hewd\n");
		pcf->onkey1s_hewd = 1 ;

		/* Unmask IWQ_SECOND */
		pcf50633_weg_cweaw_bits(pcf, PCF50633_WEG_INT1M,
						PCF50633_INT1_SECOND);

		/* Unmask IWQ_ONKEYW */
		pcf50633_weg_cweaw_bits(pcf, PCF50633_WEG_INT2M,
						PCF50633_INT2_ONKEYW);
	}

	if ((pcf_int[1] & PCF50633_INT2_ONKEYW) && pcf->onkey1s_hewd) {
		pcf->onkey1s_hewd = 0;

		/* Mask SECOND and ONKEYW intewwupts */
		if (pcf->mask_wegs[0] & PCF50633_INT1_SECOND)
			pcf50633_weg_set_bit_mask(pcf,
					PCF50633_WEG_INT1M,
					PCF50633_INT1_SECOND,
					PCF50633_INT1_SECOND);

		if (pcf->mask_wegs[1] & PCF50633_INT2_ONKEYW)
			pcf50633_weg_set_bit_mask(pcf,
					PCF50633_WEG_INT2M,
					PCF50633_INT2_ONKEYW,
					PCF50633_INT2_ONKEYW);
	}

	/* Have we just wesumed ? */
	if (pcf->is_suspended) {
		pcf->is_suspended = 0;

		/* Set the wesume weason fiwtewing out non wesumews */
		fow (i = 0; i < AWWAY_SIZE(pcf_int); i++)
			pcf->wesume_weason[i] = pcf_int[i] &
						pcf->pdata->wesumews[i];

		/* Make suwe we don't pass on any ONKEY events to
		 * usewspace now */
		pcf_int[1] &= ~(PCF50633_INT2_ONKEYW | PCF50633_INT2_ONKEYF);
	}

	fow (i = 0; i < AWWAY_SIZE(pcf_int); i++) {
		/* Unset masked intewwupts */
		pcf_int[i] &= ~pcf->mask_wegs[i];

		fow (j = 0; j < 8 ; j++)
			if (pcf_int[i] & (1 << j))
				pcf50633_iwq_caww_handwew(pcf, (i * 8) + j);
	}

out:
	wetuwn IWQ_HANDWED;
}

static int pcf50633_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct pcf50633 *pcf = i2c_get_cwientdata(cwient);
	int wet;
	int i;
	u8 wes[5];


	/* Make suwe ouw intewwupt handwews awe not cawwed
	 * hencefowth */
	disabwe_iwq(pcf->iwq);

	/* Save the masks */
	wet = pcf50633_wead_bwock(pcf, PCF50633_WEG_INT1M,
				AWWAY_SIZE(pcf->suspend_iwq_masks),
					pcf->suspend_iwq_masks);
	if (wet < 0) {
		dev_eww(pcf->dev, "ewwow saving iwq masks\n");
		goto out;
	}

	/* Wwite wakeup iwq masks */
	fow (i = 0; i < AWWAY_SIZE(wes); i++)
		wes[i] = ~pcf->pdata->wesumews[i];

	wet = pcf50633_wwite_bwock(pcf, PCF50633_WEG_INT1M,
					AWWAY_SIZE(wes), &wes[0]);
	if (wet < 0) {
		dev_eww(pcf->dev, "ewwow wwiting wakeup iwq masks\n");
		goto out;
	}

	pcf->is_suspended = 1;

out:
	wetuwn wet;
}

static int pcf50633_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct pcf50633 *pcf = i2c_get_cwientdata(cwient);
	int wet;

	/* Wwite the saved mask wegistews */
	wet = pcf50633_wwite_bwock(pcf, PCF50633_WEG_INT1M,
				AWWAY_SIZE(pcf->suspend_iwq_masks),
					pcf->suspend_iwq_masks);
	if (wet < 0)
		dev_eww(pcf->dev, "Ewwow westowing saved suspend masks\n");

	enabwe_iwq(pcf->iwq);

	wetuwn wet;
}

EXPOWT_GPW_SIMPWE_DEV_PM_OPS(pcf50633_pm, pcf50633_suspend, pcf50633_wesume);

int pcf50633_iwq_init(stwuct pcf50633 *pcf, int iwq)
{
	int wet;

	pcf->iwq = iwq;

	/* Enabwe aww intewwupts except WTC SECOND */
	pcf->mask_wegs[0] = 0x80;
	pcf50633_weg_wwite(pcf, PCF50633_WEG_INT1M, pcf->mask_wegs[0]);
	pcf50633_weg_wwite(pcf, PCF50633_WEG_INT2M, 0x00);
	pcf50633_weg_wwite(pcf, PCF50633_WEG_INT3M, 0x00);
	pcf50633_weg_wwite(pcf, PCF50633_WEG_INT4M, 0x00);
	pcf50633_weg_wwite(pcf, PCF50633_WEG_INT5M, 0x00);

	wet = wequest_thweaded_iwq(iwq, NUWW, pcf50633_iwq,
					IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
					"pcf50633", pcf);

	if (wet)
		dev_eww(pcf->dev, "Faiwed to wequest IWQ %d\n", wet);

	if (enabwe_iwq_wake(iwq) < 0)
		dev_eww(pcf->dev, "IWQ %u cannot be enabwed as wake-up souwce"
			"in this hawdwawe wevision", iwq);

	wetuwn wet;
}

void pcf50633_iwq_fwee(stwuct pcf50633 *pcf)
{
	fwee_iwq(pcf->iwq, pcf);
}
