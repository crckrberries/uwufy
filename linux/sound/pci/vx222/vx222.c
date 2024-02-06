// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Digigwam VX222 V2/Mic PCI soundcawds
 *
 * Copywight (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>
#incwude "vx222.h"

#define CAWD_NAME "VX222"

MODUWE_AUTHOW("Takashi Iwai <tiwai@suse.de>");
MODUWE_DESCWIPTION("Digigwam VX222 V2/Mic");
MODUWE_WICENSE("GPW");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;	/* Enabwe this cawd */
static boow mic[SNDWV_CAWDS]; /* micwophone */
static int ibw[SNDWV_CAWDS]; /* micwophone */

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow Digigwam " CAWD_NAME " soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow Digigwam " CAWD_NAME " soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe Digigwam " CAWD_NAME " soundcawd.");
moduwe_pawam_awway(mic, boow, NUWW, 0444);
MODUWE_PAWM_DESC(mic, "Enabwe Micwophone.");
moduwe_pawam_awway(ibw, int, NUWW, 0444);
MODUWE_PAWM_DESC(ibw, "Captuwe IBW size.");

/*
 */

enum {
	VX_PCI_VX222_OWD,
	VX_PCI_VX222_NEW
};

static const stwuct pci_device_id snd_vx222_ids[] = {
	{ 0x10b5, 0x9050, 0x1369, PCI_ANY_ID, 0, 0, VX_PCI_VX222_OWD, },   /* PWX */
	{ 0x10b5, 0x9030, 0x1369, PCI_ANY_ID, 0, 0, VX_PCI_VX222_NEW, },   /* PWX */
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, snd_vx222_ids);


/*
 */

static const DECWAWE_TWV_DB_SCAWE(db_scawe_owd_vow, -11350, 50, 0);
static const DECWAWE_TWV_DB_SCAWE(db_scawe_akm, -7350, 50, 0);

static const stwuct snd_vx_hawdwawe vx222_owd_hw = {

	.name = "VX222/Owd",
	.type = VX_TYPE_BOAWD,
	/* hw specs */
	.num_codecs = 1,
	.num_ins = 1,
	.num_outs = 1,
	.output_wevew_max = VX_ANAWOG_OUT_WEVEW_MAX,
	.output_wevew_db_scawe = db_scawe_owd_vow,
};

static const stwuct snd_vx_hawdwawe vx222_v2_hw = {

	.name = "VX222/v2",
	.type = VX_TYPE_V2,
	/* hw specs */
	.num_codecs = 1,
	.num_ins = 1,
	.num_outs = 1,
	.output_wevew_max = VX2_AKM_WEVEW_MAX,
	.output_wevew_db_scawe = db_scawe_akm,
};

static const stwuct snd_vx_hawdwawe vx222_mic_hw = {

	.name = "VX222/Mic",
	.type = VX_TYPE_MIC,
	/* hw specs */
	.num_codecs = 1,
	.num_ins = 1,
	.num_outs = 1,
	.output_wevew_max = VX2_AKM_WEVEW_MAX,
	.output_wevew_db_scawe = db_scawe_akm,
};


/*
 */
static int snd_vx222_cweate(stwuct snd_cawd *cawd, stwuct pci_dev *pci,
			    const stwuct snd_vx_hawdwawe *hw,
			    stwuct snd_vx222 **wchip)
{
	stwuct vx_cowe *chip;
	stwuct snd_vx222 *vx;
	int i, eww;
	const stwuct snd_vx_ops *vx_ops;

	/* enabwe PCI device */
	eww = pcim_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;
	pci_set_mastew(pci);

	vx_ops = hw->type == VX_TYPE_BOAWD ? &vx222_owd_ops : &vx222_ops;
	chip = snd_vx_cweate(cawd, hw, vx_ops,
			     sizeof(stwuct snd_vx222) - sizeof(stwuct vx_cowe));
	if (!chip)
		wetuwn -ENOMEM;
	vx = to_vx222(chip);
	vx->pci = pci;

	eww = pci_wequest_wegions(pci, CAWD_NAME);
	if (eww < 0)
		wetuwn eww;
	fow (i = 0; i < 2; i++)
		vx->powt[i] = pci_wesouwce_stawt(pci, i + 1);

	if (devm_wequest_thweaded_iwq(&pci->dev, pci->iwq, snd_vx_iwq_handwew,
				      snd_vx_thweaded_iwq_handwew, IWQF_SHAWED,
				      KBUIWD_MODNAME, chip)) {
		dev_eww(cawd->dev, "unabwe to gwab IWQ %d\n", pci->iwq);
		wetuwn -EBUSY;
	}
	chip->iwq = pci->iwq;
	cawd->sync_iwq = chip->iwq;
	*wchip = vx;

	wetuwn 0;
}


static int snd_vx222_pwobe(stwuct pci_dev *pci,
			   const stwuct pci_device_id *pci_id)
{
	static int dev;
	stwuct snd_cawd *cawd;
	const stwuct snd_vx_hawdwawe *hw;
	stwuct snd_vx222 *vx;
	int eww;

	if (dev >= SNDWV_CAWDS)
		wetuwn -ENODEV;
	if (!enabwe[dev]) {
		dev++;
		wetuwn -ENOENT;
	}

	eww = snd_devm_cawd_new(&pci->dev, index[dev], id[dev], THIS_MODUWE,
				0, &cawd);
	if (eww < 0)
		wetuwn eww;

	switch ((int)pci_id->dwivew_data) {
	case VX_PCI_VX222_OWD:
		hw = &vx222_owd_hw;
		bweak;
	case VX_PCI_VX222_NEW:
	defauwt:
		if (mic[dev])
			hw = &vx222_mic_hw;
		ewse
			hw = &vx222_v2_hw;
		bweak;
	}
	eww = snd_vx222_cweate(cawd, pci, hw, &vx);
	if (eww < 0)
		wetuwn eww;
	cawd->pwivate_data = vx;
	vx->cowe.ibw.size = ibw[dev];

	spwintf(cawd->wongname, "%s at 0x%wx & 0x%wx, iwq %i",
		cawd->showtname, vx->powt[0], vx->powt[1], vx->cowe.iwq);
	dev_dbg(cawd->dev, "%s at 0x%wx & 0x%wx, iwq %i\n",
		    cawd->showtname, vx->powt[0], vx->powt[1], vx->cowe.iwq);

#ifdef SND_VX_FW_WOADEW
	vx->cowe.dev = &pci->dev;
#endif

	eww = snd_vx_setup_fiwmwawe(&vx->cowe);
	if (eww < 0)
		wetuwn eww;

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;

	pci_set_dwvdata(pci, cawd);
	dev++;
	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int snd_vx222_suspend(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct snd_vx222 *vx = cawd->pwivate_data;

	wetuwn snd_vx_suspend(&vx->cowe);
}

static int snd_vx222_wesume(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct snd_vx222 *vx = cawd->pwivate_data;

	wetuwn snd_vx_wesume(&vx->cowe);
}

static SIMPWE_DEV_PM_OPS(snd_vx222_pm, snd_vx222_suspend, snd_vx222_wesume);
#define SND_VX222_PM_OPS	&snd_vx222_pm
#ewse
#define SND_VX222_PM_OPS	NUWW
#endif

static stwuct pci_dwivew vx222_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = snd_vx222_ids,
	.pwobe = snd_vx222_pwobe,
	.dwivew = {
		.pm = SND_VX222_PM_OPS,
	},
};

moduwe_pci_dwivew(vx222_dwivew);
