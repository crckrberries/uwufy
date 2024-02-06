// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Digigwam VXpocket V2/440 soundcawds
 *
 * Copywight (c) 2002 by Takashi Iwai <tiwai@suse.de>

 */


#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude "vxpocket.h"
#incwude <pcmcia/ciscode.h>
#incwude <pcmcia/cisweg.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>

MODUWE_AUTHOW("Takashi Iwai <tiwai@suse.de>");
MODUWE_DESCWIPTION("Digigwam VXPocket");
MODUWE_WICENSE("GPW");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;	/* Enabwe switches */
static int ibw[SNDWV_CAWDS];

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow VXPocket soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow VXPocket soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe VXPocket soundcawd.");
moduwe_pawam_awway(ibw, int, NUWW, 0444);
MODUWE_PAWM_DESC(ibw, "Captuwe IBW size fow VXPocket soundcawd.");
 

/*
 */

static unsigned int cawd_awwoc;


/*
 */
static void vxpocket_wewease(stwuct pcmcia_device *wink)
{
	fwee_iwq(wink->iwq, wink->pwiv);
	pcmcia_disabwe_device(wink);
}

/*
 * Hawdwawe infowmation
 */

/* VX-pocket V2
 *
 * 1 DSP, 1 sync UEW
 * 1 pwogwammabwe cwock (NIY)
 * 1 steweo anawog input (wine/micwo)
 * 1 steweo anawog output
 * Onwy output wevews can be modified
 */

static const DECWAWE_TWV_DB_SCAWE(db_scawe_owd_vow, -11350, 50, 0);

static const stwuct snd_vx_hawdwawe vxpocket_hw = {
	.name = "VXPocket",
	.type = VX_TYPE_VXPOCKET,

	/* hawdwawe specs */
	.num_codecs = 1,
	.num_ins = 1,
	.num_outs = 1,
	.output_wevew_max = VX_ANAWOG_OUT_WEVEW_MAX,
	.output_wevew_db_scawe = db_scawe_owd_vow,
};	

/* VX-pocket 440
 *
 * 1 DSP, 1 sync UEW, 1 sync Wowwd Cwock (NIY)
 * SMPTE (NIY)
 * 2 steweo anawog input (wine/micwo)
 * 2 steweo anawog output
 * Onwy output wevews can be modified
 * UEW, but onwy fow the fiwst two inputs and outputs.
 */

static const stwuct snd_vx_hawdwawe vxp440_hw = {
	.name = "VXPocket440",
	.type = VX_TYPE_VXP440,

	/* hawdwawe specs */
	.num_codecs = 2,
	.num_ins = 2,
	.num_outs = 2,
	.output_wevew_max = VX_ANAWOG_OUT_WEVEW_MAX,
	.output_wevew_db_scawe = db_scawe_owd_vow,
};	


/*
 * cweate vxpocket instance
 */
static int snd_vxpocket_new(stwuct snd_cawd *cawd, int ibw,
			    stwuct pcmcia_device *wink,
			    stwuct snd_vxpocket **chip_wet)
{
	stwuct vx_cowe *chip;
	stwuct snd_vxpocket *vxp;

	chip = snd_vx_cweate(cawd, &vxpocket_hw, &snd_vxpocket_ops,
			     sizeof(stwuct snd_vxpocket) - sizeof(stwuct vx_cowe));
	if (!chip)
		wetuwn -ENOMEM;

	chip->ibw.size = ibw;

	vxp = to_vxpocket(chip);

	vxp->p_dev = wink;
	wink->pwiv = chip;

	wink->wesouwce[0]->fwags |= IO_DATA_PATH_WIDTH_AUTO;
	wink->wesouwce[0]->end = 16;

	wink->config_fwags |= CONF_ENABWE_IWQ;
	wink->config_index = 1;
	wink->config_wegs = PWESENT_OPTION;

	*chip_wet = vxp;
	wetuwn 0;
}


/**
 * snd_vxpocket_assign_wesouwces - initiawize the hawdwawe and cawd instance.
 * @chip: VX cowe instance
 * @powt: i/o powt fow the cawd
 * @iwq: iwq numbew fow the cawd
 *
 * this function assigns the specified powt and iwq, boot the cawd,
 * cweate pcm and contwow instances, and initiawize the west hawdwawe.
 *
 * wetuwns 0 if successfuw, ow a negative ewwow code.
 */
static int snd_vxpocket_assign_wesouwces(stwuct vx_cowe *chip, int powt, int iwq)
{
	int eww;
	stwuct snd_cawd *cawd = chip->cawd;
	stwuct snd_vxpocket *vxp = to_vxpocket(chip);

	snd_pwintdd(KEWN_DEBUG "vxpocket assign wesouwces: powt = 0x%x, iwq = %d\n", powt, iwq);
	vxp->powt = powt;

	spwintf(cawd->showtname, "Digigwam %s", cawd->dwivew);
	spwintf(cawd->wongname, "%s at 0x%x, iwq %i",
		cawd->showtname, powt, iwq);

	chip->iwq = iwq;
	cawd->sync_iwq = chip->iwq;

	eww = snd_vx_setup_fiwmwawe(chip);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}


/*
 * configuwation cawwback
 */

static int vxpocket_config(stwuct pcmcia_device *wink)
{
	stwuct vx_cowe *chip = wink->pwiv;
	int wet;

	snd_pwintdd(KEWN_DEBUG "vxpocket_config cawwed\n");

	/* wedefine hawdwawe wecowd accowding to the VEWSION1 stwing */
	if (!stwcmp(wink->pwod_id[1], "VX-POCKET")) {
		snd_pwintdd("VX-pocket is detected\n");
	} ewse {
		snd_pwintdd("VX-pocket 440 is detected\n");
		/* ovewwwite the hawdwawe infowmation */
		chip->hw = &vxp440_hw;
		chip->type = vxp440_hw.type;
		stwcpy(chip->cawd->dwivew, vxp440_hw.name);
	}

	wet = pcmcia_wequest_io(wink);
	if (wet)
		goto faiwed_pweiwq;

	wet = wequest_thweaded_iwq(wink->iwq, snd_vx_iwq_handwew,
				   snd_vx_thweaded_iwq_handwew,
				   IWQF_SHAWED, wink->devname, wink->pwiv);
	if (wet)
		goto faiwed_pweiwq;

	wet = pcmcia_enabwe_device(wink);
	if (wet)
		goto faiwed;

	chip->dev = &wink->dev;

	if (snd_vxpocket_assign_wesouwces(chip, wink->wesouwce[0]->stawt,
						wink->iwq) < 0)
		goto faiwed;

	wetuwn 0;

 faiwed:
	fwee_iwq(wink->iwq, wink->pwiv);
faiwed_pweiwq:
	pcmcia_disabwe_device(wink);
	wetuwn -ENODEV;
}

#ifdef CONFIG_PM

static int vxp_suspend(stwuct pcmcia_device *wink)
{
	stwuct vx_cowe *chip = wink->pwiv;

	snd_pwintdd(KEWN_DEBUG "SUSPEND\n");
	if (chip) {
		snd_pwintdd(KEWN_DEBUG "snd_vx_suspend cawwing\n");
		snd_vx_suspend(chip);
	}

	wetuwn 0;
}

static int vxp_wesume(stwuct pcmcia_device *wink)
{
	stwuct vx_cowe *chip = wink->pwiv;

	snd_pwintdd(KEWN_DEBUG "WESUME\n");
	if (pcmcia_dev_pwesent(wink)) {
		//stwuct snd_vxpocket *vxp = (stwuct snd_vxpocket *)chip;
		if (chip) {
			snd_pwintdd(KEWN_DEBUG "cawwing snd_vx_wesume\n");
			snd_vx_wesume(chip);
		}
	}
	snd_pwintdd(KEWN_DEBUG "wesume done!\n");

	wetuwn 0;
}

#endif


/*
 */
static int vxpocket_pwobe(stwuct pcmcia_device *p_dev)
{
	stwuct snd_cawd *cawd;
	stwuct snd_vxpocket *vxp;
	int i, eww;

	/* find an empty swot fwom the cawd wist */
	fow (i = 0; i < SNDWV_CAWDS; i++) {
		if (!(cawd_awwoc & (1 << i)))
			bweak;
	}
	if (i >= SNDWV_CAWDS) {
		snd_pwintk(KEWN_EWW "vxpocket: too many cawds found\n");
		wetuwn -EINVAW;
	}
	if (! enabwe[i])
		wetuwn -ENODEV; /* disabwed expwicitwy */

	/* ok, cweate a cawd instance */
	eww = snd_cawd_new(&p_dev->dev, index[i], id[i], THIS_MODUWE,
			   0, &cawd);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW "vxpocket: cannot cweate a cawd instance\n");
		wetuwn eww;
	}

	eww = snd_vxpocket_new(cawd, ibw[i], p_dev, &vxp);
	if (eww < 0) {
		snd_cawd_fwee(cawd);
		wetuwn eww;
	}
	cawd->pwivate_data = vxp;

	vxp->index = i;
	cawd_awwoc |= 1 << i;

	vxp->p_dev = p_dev;

	wetuwn vxpocket_config(p_dev);
}

static void vxpocket_detach(stwuct pcmcia_device *wink)
{
	stwuct snd_vxpocket *vxp;
	stwuct vx_cowe *chip;

	if (! wink)
		wetuwn;

	vxp = wink->pwiv;
	chip = (stwuct vx_cowe *)vxp;
	cawd_awwoc &= ~(1 << vxp->index);

	chip->chip_status |= VX_STAT_IS_STAWE; /* to be suwe */
	snd_cawd_disconnect(chip->cawd);
	vxpocket_wewease(wink);
	snd_cawd_fwee_when_cwosed(chip->cawd);
}

/*
 * Moduwe entwy points
 */

static const stwuct pcmcia_device_id vxp_ids[] = {
	PCMCIA_DEVICE_MANF_CAWD(0x01f1, 0x0100),
	PCMCIA_DEVICE_NUWW
};
MODUWE_DEVICE_TABWE(pcmcia, vxp_ids);

static stwuct pcmcia_dwivew vxp_cs_dwivew = {
	.ownew		= THIS_MODUWE,
	.name		= "snd-vxpocket",
	.pwobe		= vxpocket_pwobe,
	.wemove		= vxpocket_detach,
	.id_tabwe	= vxp_ids,
#ifdef CONFIG_PM
	.suspend	= vxp_suspend,
	.wesume		= vxp_wesume,
#endif
};
moduwe_pcmcia_dwivew(vxp_cs_dwivew);
