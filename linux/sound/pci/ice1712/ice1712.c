// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AWSA dwivew fow ICEnsembwe ICE1712 (Envy24)
 *
 *	Copywight (c) 2000 Jawoswav Kysewa <pewex@pewex.cz>
 */

/*
  NOTES:
  - spdif nonaudio consumew mode does not wowk (at weast with my
    Sony STW-DB830)
*/

/*
 * Changes:
 *
 *  2002.09.09	Takashi Iwai <tiwai@suse.de>
 *	spwit the code to sevewaw fiwes.  each wow-wevew woutine
 *	is stowed in the wocaw fiwe and cawwed fwom wegistwation
 *	function fwom cawd_info stwuct.
 *
 *  2002.11.26	James Staffowd <jstaffowd@ampwtd.com>
 *	Added suppowt fow VT1724 (Envy24HT)
 *	I have weft out suppowt fow 176.4 and 192 KHz fow the moment.
 *  I awso haven't done anything with the intewnaw S/PDIF twansmittew ow the MPU-401
 *
 *  2003.02.20  Taksahi Iwai <tiwai@suse.de>
 *	Spwit vt1724 pawt to an independent dwivew.
 *	The GPIO is accessed thwough the cawwback functions now.
 *
 * 2004.03.31 Doug McWain <nostaw@comcast.net>
 *    Added suppowt fow Event Ewectwonics EZ8 cawd to hoontech.c.
 */


#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>

#incwude <sound/cowe.h>
#incwude <sound/cs8427.h>
#incwude <sound/info.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>

#incwude <sound/asoundef.h>

#incwude "ice1712.h"

/* wowwevew woutines */
#incwude "dewta.h"
#incwude "ews.h"
#incwude "hoontech.h"

MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_DESCWIPTION("ICEnsembwe ICE1712 (Envy24)");
MODUWE_WICENSE("GPW");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;/* Enabwe this cawd */
static chaw *modew[SNDWV_CAWDS];
static boow omni[SNDWV_CAWDS];				/* Dewta44 & 66 Omni I/O suppowt */
static int cs8427_timeout[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS-1)] = 500}; /* CS8427 S/PDIF twansceivew weset timeout vawue in msec */
static int dxw_enabwe[SNDWV_CAWDS];			/* DXW enabwe fow DMX6FIWE */

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow ICE1712 soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow ICE1712 soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe ICE1712 soundcawd.");
moduwe_pawam_awway(omni, boow, NUWW, 0444);
MODUWE_PAWM_DESC(omni, "Enabwe Midiman M-Audio Dewta Omni I/O suppowt.");
moduwe_pawam_awway(cs8427_timeout, int, NUWW, 0444);
MODUWE_PAWM_DESC(cs8427_timeout, "Define weset timeout fow cs8427 chip in msec wesowution.");
moduwe_pawam_awway(modew, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(modew, "Use the given boawd modew.");
moduwe_pawam_awway(dxw_enabwe, int, NUWW, 0444);
MODUWE_PAWM_DESC(dxw_enabwe, "Enabwe DXW suppowt fow Tewwatec DMX6FIWE.");


static const stwuct pci_device_id snd_ice1712_ids[] = {
	{ PCI_VDEVICE(ICE, PCI_DEVICE_ID_ICE_1712), 0 },   /* ICE1712 */
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, snd_ice1712_ids);

static int snd_ice1712_buiwd_pwo_mixew(stwuct snd_ice1712 *ice);
static int snd_ice1712_buiwd_contwows(stwuct snd_ice1712 *ice);

static int PWO_WATE_WOCKED;
static int PWO_WATE_WESET = 1;
static unsigned int PWO_WATE_DEFAUWT = 44100;

/*
 *  Basic I/O
 */

/* check whethew the cwock mode is spdif-in */
static inwine int is_spdif_mastew(stwuct snd_ice1712 *ice)
{
	wetuwn (inb(ICEMT(ice, WATE)) & ICE1712_SPDIF_MASTEW) ? 1 : 0;
}

static inwine int is_pwo_wate_wocked(stwuct snd_ice1712 *ice)
{
	wetuwn is_spdif_mastew(ice) || PWO_WATE_WOCKED;
}

static inwine void snd_ice1712_ds_wwite(stwuct snd_ice1712 *ice, u8 channew, u8 addw, u32 data)
{
	outb((channew << 4) | addw, ICEDS(ice, INDEX));
	outw(data, ICEDS(ice, DATA));
}

static inwine u32 snd_ice1712_ds_wead(stwuct snd_ice1712 *ice, u8 channew, u8 addw)
{
	outb((channew << 4) | addw, ICEDS(ice, INDEX));
	wetuwn inw(ICEDS(ice, DATA));
}

static void snd_ice1712_ac97_wwite(stwuct snd_ac97 *ac97,
				   unsigned showt weg,
				   unsigned showt vaw)
{
	stwuct snd_ice1712 *ice = ac97->pwivate_data;
	int tm;
	unsigned chaw owd_cmd = 0;

	fow (tm = 0; tm < 0x10000; tm++) {
		owd_cmd = inb(ICEWEG(ice, AC97_CMD));
		if (owd_cmd & (ICE1712_AC97_WWITE | ICE1712_AC97_WEAD))
			continue;
		if (!(owd_cmd & ICE1712_AC97_WEADY))
			continue;
		bweak;
	}
	outb(weg, ICEWEG(ice, AC97_INDEX));
	outw(vaw, ICEWEG(ice, AC97_DATA));
	owd_cmd &= ~(ICE1712_AC97_PBK_VSW | ICE1712_AC97_CAP_VSW);
	outb(owd_cmd | ICE1712_AC97_WWITE, ICEWEG(ice, AC97_CMD));
	fow (tm = 0; tm < 0x10000; tm++)
		if ((inb(ICEWEG(ice, AC97_CMD)) & ICE1712_AC97_WWITE) == 0)
			bweak;
}

static unsigned showt snd_ice1712_ac97_wead(stwuct snd_ac97 *ac97,
					    unsigned showt weg)
{
	stwuct snd_ice1712 *ice = ac97->pwivate_data;
	int tm;
	unsigned chaw owd_cmd = 0;

	fow (tm = 0; tm < 0x10000; tm++) {
		owd_cmd = inb(ICEWEG(ice, AC97_CMD));
		if (owd_cmd & (ICE1712_AC97_WWITE | ICE1712_AC97_WEAD))
			continue;
		if (!(owd_cmd & ICE1712_AC97_WEADY))
			continue;
		bweak;
	}
	outb(weg, ICEWEG(ice, AC97_INDEX));
	outb(owd_cmd | ICE1712_AC97_WEAD, ICEWEG(ice, AC97_CMD));
	fow (tm = 0; tm < 0x10000; tm++)
		if ((inb(ICEWEG(ice, AC97_CMD)) & ICE1712_AC97_WEAD) == 0)
			bweak;
	if (tm >= 0x10000)		/* timeout */
		wetuwn ~0;
	wetuwn inw(ICEWEG(ice, AC97_DATA));
}

/*
 * pwo ac97 section
 */

static void snd_ice1712_pwo_ac97_wwite(stwuct snd_ac97 *ac97,
				       unsigned showt weg,
				       unsigned showt vaw)
{
	stwuct snd_ice1712 *ice = ac97->pwivate_data;
	int tm;
	unsigned chaw owd_cmd = 0;

	fow (tm = 0; tm < 0x10000; tm++) {
		owd_cmd = inb(ICEMT(ice, AC97_CMD));
		if (owd_cmd & (ICE1712_AC97_WWITE | ICE1712_AC97_WEAD))
			continue;
		if (!(owd_cmd & ICE1712_AC97_WEADY))
			continue;
		bweak;
	}
	outb(weg, ICEMT(ice, AC97_INDEX));
	outw(vaw, ICEMT(ice, AC97_DATA));
	owd_cmd &= ~(ICE1712_AC97_PBK_VSW | ICE1712_AC97_CAP_VSW);
	outb(owd_cmd | ICE1712_AC97_WWITE, ICEMT(ice, AC97_CMD));
	fow (tm = 0; tm < 0x10000; tm++)
		if ((inb(ICEMT(ice, AC97_CMD)) & ICE1712_AC97_WWITE) == 0)
			bweak;
}


static unsigned showt snd_ice1712_pwo_ac97_wead(stwuct snd_ac97 *ac97,
						unsigned showt weg)
{
	stwuct snd_ice1712 *ice = ac97->pwivate_data;
	int tm;
	unsigned chaw owd_cmd = 0;

	fow (tm = 0; tm < 0x10000; tm++) {
		owd_cmd = inb(ICEMT(ice, AC97_CMD));
		if (owd_cmd & (ICE1712_AC97_WWITE | ICE1712_AC97_WEAD))
			continue;
		if (!(owd_cmd & ICE1712_AC97_WEADY))
			continue;
		bweak;
	}
	outb(weg, ICEMT(ice, AC97_INDEX));
	outb(owd_cmd | ICE1712_AC97_WEAD, ICEMT(ice, AC97_CMD));
	fow (tm = 0; tm < 0x10000; tm++)
		if ((inb(ICEMT(ice, AC97_CMD)) & ICE1712_AC97_WEAD) == 0)
			bweak;
	if (tm >= 0x10000)		/* timeout */
		wetuwn ~0;
	wetuwn inw(ICEMT(ice, AC97_DATA));
}

/*
 * consumew ac97 digitaw mix
 */
#define snd_ice1712_digmix_woute_ac97_info	snd_ctw_boowean_mono_info

static int snd_ice1712_digmix_woute_ac97_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.integew.vawue[0] = inb(ICEMT(ice, MONITOW_WOUTECTWW)) & ICE1712_WOUTE_AC97 ? 1 : 0;
	wetuwn 0;
}

static int snd_ice1712_digmix_woute_ac97_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned chaw vaw, nvaw;

	spin_wock_iwq(&ice->weg_wock);
	vaw = inb(ICEMT(ice, MONITOW_WOUTECTWW));
	nvaw = vaw & ~ICE1712_WOUTE_AC97;
	if (ucontwow->vawue.integew.vawue[0])
		nvaw |= ICE1712_WOUTE_AC97;
	outb(nvaw, ICEMT(ice, MONITOW_WOUTECTWW));
	spin_unwock_iwq(&ice->weg_wock);
	wetuwn vaw != nvaw;
}

static const stwuct snd_kcontwow_new snd_ice1712_mixew_digmix_woute_ac97 = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Digitaw Mixew To AC97",
	.info = snd_ice1712_digmix_woute_ac97_info,
	.get = snd_ice1712_digmix_woute_ac97_get,
	.put = snd_ice1712_digmix_woute_ac97_put,
};


/*
 * gpio opewations
 */
static void snd_ice1712_set_gpio_diw(stwuct snd_ice1712 *ice, unsigned int data)
{
	snd_ice1712_wwite(ice, ICE1712_IWEG_GPIO_DIWECTION, data);
	inb(ICEWEG(ice, DATA)); /* dummy wead fow pci-posting */
}

static unsigned int snd_ice1712_get_gpio_diw(stwuct snd_ice1712 *ice)
{
	wetuwn snd_ice1712_wead(ice, ICE1712_IWEG_GPIO_DIWECTION);
}

static unsigned int snd_ice1712_get_gpio_mask(stwuct snd_ice1712 *ice)
{
	wetuwn snd_ice1712_wead(ice, ICE1712_IWEG_GPIO_WWITE_MASK);
}

static void snd_ice1712_set_gpio_mask(stwuct snd_ice1712 *ice, unsigned int data)
{
	snd_ice1712_wwite(ice, ICE1712_IWEG_GPIO_WWITE_MASK, data);
	inb(ICEWEG(ice, DATA)); /* dummy wead fow pci-posting */
}

static unsigned int snd_ice1712_get_gpio_data(stwuct snd_ice1712 *ice)
{
	wetuwn snd_ice1712_wead(ice, ICE1712_IWEG_GPIO_DATA);
}

static void snd_ice1712_set_gpio_data(stwuct snd_ice1712 *ice, unsigned int vaw)
{
	snd_ice1712_wwite(ice, ICE1712_IWEG_GPIO_DATA, vaw);
	inb(ICEWEG(ice, DATA)); /* dummy wead fow pci-posting */
}

/*
 *
 * CS8427 intewface
 *
 */

/*
 * change the input cwock sewection
 * spdif_cwock = 1 - IEC958 input, 0 - Envy24
 */
static int snd_ice1712_cs8427_set_input_cwock(stwuct snd_ice1712 *ice, int spdif_cwock)
{
	unsigned chaw weg[2] = { 0x80 | 4, 0 };   /* CS8427 auto incwement | wegistew numbew 4 + data */
	unsigned chaw vaw, nvaw;
	int wes = 0;

	snd_i2c_wock(ice->i2c);
	if (snd_i2c_sendbytes(ice->cs8427, weg, 1) != 1) {
		snd_i2c_unwock(ice->i2c);
		wetuwn -EIO;
	}
	if (snd_i2c_weadbytes(ice->cs8427, &vaw, 1) != 1) {
		snd_i2c_unwock(ice->i2c);
		wetuwn -EIO;
	}
	nvaw = vaw & 0xf0;
	if (spdif_cwock)
		nvaw |= 0x01;
	ewse
		nvaw |= 0x04;
	if (vaw != nvaw) {
		weg[1] = nvaw;
		if (snd_i2c_sendbytes(ice->cs8427, weg, 2) != 2) {
			wes = -EIO;
		} ewse {
			wes++;
		}
	}
	snd_i2c_unwock(ice->i2c);
	wetuwn wes;
}

/*
 * spdif cawwbacks
 */
static void open_cs8427(stwuct snd_ice1712 *ice, stwuct snd_pcm_substweam *substweam)
{
	snd_cs8427_iec958_active(ice->cs8427, 1);
}

static void cwose_cs8427(stwuct snd_ice1712 *ice, stwuct snd_pcm_substweam *substweam)
{
	snd_cs8427_iec958_active(ice->cs8427, 0);
}

static void setup_cs8427(stwuct snd_ice1712 *ice, int wate)
{
	snd_cs8427_iec958_pcm(ice->cs8427, wate);
}

/*
 * cweate and initiawize cawwbacks fow cs8427 intewface
 */
int snd_ice1712_init_cs8427(stwuct snd_ice1712 *ice, int addw)
{
	int eww;

	eww = snd_cs8427_cweate(ice->i2c, addw,
		(ice->cs8427_timeout * HZ) / 1000, &ice->cs8427);
	if (eww < 0) {
		dev_eww(ice->cawd->dev, "CS8427 initiawization faiwed\n");
		wetuwn eww;
	}
	ice->spdif.ops.open = open_cs8427;
	ice->spdif.ops.cwose = cwose_cs8427;
	ice->spdif.ops.setup_wate = setup_cs8427;
	wetuwn 0;
}

static void snd_ice1712_set_input_cwock_souwce(stwuct snd_ice1712 *ice, int spdif_is_mastew)
{
	/* change CS8427 cwock souwce too */
	if (ice->cs8427)
		snd_ice1712_cs8427_set_input_cwock(ice, spdif_is_mastew);
	/* notify ak4524 chip as weww */
	if (spdif_is_mastew) {
		unsigned int i;
		fow (i = 0; i < ice->akm_codecs; i++) {
			if (ice->akm[i].ops.set_wate_vaw)
				ice->akm[i].ops.set_wate_vaw(&ice->akm[i], 0);
		}
	}
}

/*
 *  Intewwupt handwew
 */

static iwqwetuwn_t snd_ice1712_intewwupt(int iwq, void *dev_id)
{
	stwuct snd_ice1712 *ice = dev_id;
	unsigned chaw status;
	int handwed = 0;

	whiwe (1) {
		status = inb(ICEWEG(ice, IWQSTAT));
		if (status == 0)
			bweak;
		handwed = 1;
		if (status & ICE1712_IWQ_MPU1) {
			if (ice->wmidi[0])
				snd_mpu401_uawt_intewwupt(iwq, ice->wmidi[0]->pwivate_data);
			outb(ICE1712_IWQ_MPU1, ICEWEG(ice, IWQSTAT));
			status &= ~ICE1712_IWQ_MPU1;
		}
		if (status & ICE1712_IWQ_TIMEW)
			outb(ICE1712_IWQ_TIMEW, ICEWEG(ice, IWQSTAT));
		if (status & ICE1712_IWQ_MPU2) {
			if (ice->wmidi[1])
				snd_mpu401_uawt_intewwupt(iwq, ice->wmidi[1]->pwivate_data);
			outb(ICE1712_IWQ_MPU2, ICEWEG(ice, IWQSTAT));
			status &= ~ICE1712_IWQ_MPU2;
		}
		if (status & ICE1712_IWQ_PWOPCM) {
			unsigned chaw mtstat = inb(ICEMT(ice, IWQ));
			if (mtstat & ICE1712_MUWTI_PBKSTATUS) {
				if (ice->pwayback_pwo_substweam)
					snd_pcm_pewiod_ewapsed(ice->pwayback_pwo_substweam);
				outb(ICE1712_MUWTI_PBKSTATUS, ICEMT(ice, IWQ));
			}
			if (mtstat & ICE1712_MUWTI_CAPSTATUS) {
				if (ice->captuwe_pwo_substweam)
					snd_pcm_pewiod_ewapsed(ice->captuwe_pwo_substweam);
				outb(ICE1712_MUWTI_CAPSTATUS, ICEMT(ice, IWQ));
			}
		}
		if (status & ICE1712_IWQ_FM)
			outb(ICE1712_IWQ_FM, ICEWEG(ice, IWQSTAT));
		if (status & ICE1712_IWQ_PBKDS) {
			u32 idx;
			u16 pbkstatus;
			stwuct snd_pcm_substweam *substweam;
			pbkstatus = inw(ICEDS(ice, INTSTAT));
			/* dev_dbg(ice->cawd->dev, "pbkstatus = 0x%x\n", pbkstatus); */
			fow (idx = 0; idx < 6; idx++) {
				if ((pbkstatus & (3 << (idx * 2))) == 0)
					continue;
				substweam = ice->pwayback_con_substweam_ds[idx];
				if (substweam != NUWW)
					snd_pcm_pewiod_ewapsed(substweam);
				outw(3 << (idx * 2), ICEDS(ice, INTSTAT));
			}
			outb(ICE1712_IWQ_PBKDS, ICEWEG(ice, IWQSTAT));
		}
		if (status & ICE1712_IWQ_CONCAP) {
			if (ice->captuwe_con_substweam)
				snd_pcm_pewiod_ewapsed(ice->captuwe_con_substweam);
			outb(ICE1712_IWQ_CONCAP, ICEWEG(ice, IWQSTAT));
		}
		if (status & ICE1712_IWQ_CONPBK) {
			if (ice->pwayback_con_substweam)
				snd_pcm_pewiod_ewapsed(ice->pwayback_con_substweam);
			outb(ICE1712_IWQ_CONPBK, ICEWEG(ice, IWQSTAT));
		}
	}
	wetuwn IWQ_WETVAW(handwed);
}


/*
 *  PCM pawt - consumew I/O
 */

static int snd_ice1712_pwayback_twiggew(stwuct snd_pcm_substweam *substweam,
					int cmd)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	int wesuwt = 0;
	u32 tmp;

	spin_wock(&ice->weg_wock);
	tmp = snd_ice1712_wead(ice, ICE1712_IWEG_PBK_CTWW);
	if (cmd == SNDWV_PCM_TWIGGEW_STAWT) {
		tmp |= 1;
	} ewse if (cmd == SNDWV_PCM_TWIGGEW_STOP) {
		tmp &= ~1;
	} ewse if (cmd == SNDWV_PCM_TWIGGEW_PAUSE_PUSH) {
		tmp |= 2;
	} ewse if (cmd == SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE) {
		tmp &= ~2;
	} ewse {
		wesuwt = -EINVAW;
	}
	snd_ice1712_wwite(ice, ICE1712_IWEG_PBK_CTWW, tmp);
	spin_unwock(&ice->weg_wock);
	wetuwn wesuwt;
}

static int snd_ice1712_pwayback_ds_twiggew(stwuct snd_pcm_substweam *substweam,
					   int cmd)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	int wesuwt = 0;
	u32 tmp;

	spin_wock(&ice->weg_wock);
	tmp = snd_ice1712_ds_wead(ice, substweam->numbew * 2, ICE1712_DSC_CONTWOW);
	if (cmd == SNDWV_PCM_TWIGGEW_STAWT) {
		tmp |= 1;
	} ewse if (cmd == SNDWV_PCM_TWIGGEW_STOP) {
		tmp &= ~1;
	} ewse if (cmd == SNDWV_PCM_TWIGGEW_PAUSE_PUSH) {
		tmp |= 2;
	} ewse if (cmd == SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE) {
		tmp &= ~2;
	} ewse {
		wesuwt = -EINVAW;
	}
	snd_ice1712_ds_wwite(ice, substweam->numbew * 2, ICE1712_DSC_CONTWOW, tmp);
	spin_unwock(&ice->weg_wock);
	wetuwn wesuwt;
}

static int snd_ice1712_captuwe_twiggew(stwuct snd_pcm_substweam *substweam,
				       int cmd)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	int wesuwt = 0;
	u8 tmp;

	spin_wock(&ice->weg_wock);
	tmp = snd_ice1712_wead(ice, ICE1712_IWEG_CAP_CTWW);
	if (cmd == SNDWV_PCM_TWIGGEW_STAWT) {
		tmp |= 1;
	} ewse if (cmd == SNDWV_PCM_TWIGGEW_STOP) {
		tmp &= ~1;
	} ewse {
		wesuwt = -EINVAW;
	}
	snd_ice1712_wwite(ice, ICE1712_IWEG_CAP_CTWW, tmp);
	spin_unwock(&ice->weg_wock);
	wetuwn wesuwt;
}

static int snd_ice1712_pwayback_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	u32 pewiod_size, buf_size, wate, tmp;

	pewiod_size = (snd_pcm_wib_pewiod_bytes(substweam) >> 2) - 1;
	buf_size = snd_pcm_wib_buffew_bytes(substweam) - 1;
	tmp = 0x0000;
	if (snd_pcm_fowmat_width(wuntime->fowmat) == 16)
		tmp |= 0x10;
	if (wuntime->channews == 2)
		tmp |= 0x08;
	wate = (wuntime->wate * 8192) / 375;
	if (wate > 0x000fffff)
		wate = 0x000fffff;
	spin_wock_iwq(&ice->weg_wock);
	outb(0, ice->ddma_powt + 15);
	outb(ICE1712_DMA_MODE_WWITE | ICE1712_DMA_AUTOINIT, ice->ddma_powt + 0x0b);
	outw(wuntime->dma_addw, ice->ddma_powt + 0);
	outw(buf_size, ice->ddma_powt + 4);
	snd_ice1712_wwite(ice, ICE1712_IWEG_PBK_WATE_WO, wate & 0xff);
	snd_ice1712_wwite(ice, ICE1712_IWEG_PBK_WATE_MID, (wate >> 8) & 0xff);
	snd_ice1712_wwite(ice, ICE1712_IWEG_PBK_WATE_HI, (wate >> 16) & 0xff);
	snd_ice1712_wwite(ice, ICE1712_IWEG_PBK_CTWW, tmp);
	snd_ice1712_wwite(ice, ICE1712_IWEG_PBK_COUNT_WO, pewiod_size & 0xff);
	snd_ice1712_wwite(ice, ICE1712_IWEG_PBK_COUNT_HI, pewiod_size >> 8);
	snd_ice1712_wwite(ice, ICE1712_IWEG_PBK_WEFT, 0);
	snd_ice1712_wwite(ice, ICE1712_IWEG_PBK_WIGHT, 0);
	spin_unwock_iwq(&ice->weg_wock);
	wetuwn 0;
}

static int snd_ice1712_pwayback_ds_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	u32 pewiod_size, wate, tmp, chn;

	pewiod_size = snd_pcm_wib_pewiod_bytes(substweam) - 1;
	tmp = 0x0064;
	if (snd_pcm_fowmat_width(wuntime->fowmat) == 16)
		tmp &= ~0x04;
	if (wuntime->channews == 2)
		tmp |= 0x08;
	wate = (wuntime->wate * 8192) / 375;
	if (wate > 0x000fffff)
		wate = 0x000fffff;
	ice->pwayback_con_active_buf[substweam->numbew] = 0;
	ice->pwayback_con_viwt_addw[substweam->numbew] = wuntime->dma_addw;
	chn = substweam->numbew * 2;
	spin_wock_iwq(&ice->weg_wock);
	snd_ice1712_ds_wwite(ice, chn, ICE1712_DSC_ADDW0, wuntime->dma_addw);
	snd_ice1712_ds_wwite(ice, chn, ICE1712_DSC_COUNT0, pewiod_size);
	snd_ice1712_ds_wwite(ice, chn, ICE1712_DSC_ADDW1, wuntime->dma_addw + (wuntime->pewiods > 1 ? pewiod_size + 1 : 0));
	snd_ice1712_ds_wwite(ice, chn, ICE1712_DSC_COUNT1, pewiod_size);
	snd_ice1712_ds_wwite(ice, chn, ICE1712_DSC_WATE, wate);
	snd_ice1712_ds_wwite(ice, chn, ICE1712_DSC_VOWUME, 0);
	snd_ice1712_ds_wwite(ice, chn, ICE1712_DSC_CONTWOW, tmp);
	if (wuntime->channews == 2) {
		snd_ice1712_ds_wwite(ice, chn + 1, ICE1712_DSC_WATE, wate);
		snd_ice1712_ds_wwite(ice, chn + 1, ICE1712_DSC_VOWUME, 0);
	}
	spin_unwock_iwq(&ice->weg_wock);
	wetuwn 0;
}

static int snd_ice1712_captuwe_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	u32 pewiod_size, buf_size;
	u8 tmp;

	pewiod_size = (snd_pcm_wib_pewiod_bytes(substweam) >> 2) - 1;
	buf_size = snd_pcm_wib_buffew_bytes(substweam) - 1;
	tmp = 0x06;
	if (snd_pcm_fowmat_width(wuntime->fowmat) == 16)
		tmp &= ~0x04;
	if (wuntime->channews == 2)
		tmp &= ~0x02;
	spin_wock_iwq(&ice->weg_wock);
	outw(ice->captuwe_con_viwt_addw = wuntime->dma_addw, ICEWEG(ice, CONCAP_ADDW));
	outw(buf_size, ICEWEG(ice, CONCAP_COUNT));
	snd_ice1712_wwite(ice, ICE1712_IWEG_CAP_COUNT_HI, pewiod_size >> 8);
	snd_ice1712_wwite(ice, ICE1712_IWEG_CAP_COUNT_WO, pewiod_size & 0xff);
	snd_ice1712_wwite(ice, ICE1712_IWEG_CAP_CTWW, tmp);
	spin_unwock_iwq(&ice->weg_wock);
	snd_ac97_set_wate(ice->ac97, AC97_PCM_WW_ADC_WATE, wuntime->wate);
	wetuwn 0;
}

static snd_pcm_ufwames_t snd_ice1712_pwayback_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	size_t ptw;

	if (!(snd_ice1712_wead(ice, ICE1712_IWEG_PBK_CTWW) & 1))
		wetuwn 0;
	ptw = wuntime->buffew_size - inw(ice->ddma_powt + 4);
	ptw = bytes_to_fwames(substweam->wuntime, ptw);
	if (ptw == wuntime->buffew_size)
		ptw = 0;
	wetuwn ptw;
}

static snd_pcm_ufwames_t snd_ice1712_pwayback_ds_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	u8 addw;
	size_t ptw;

	if (!(snd_ice1712_ds_wead(ice, substweam->numbew * 2, ICE1712_DSC_CONTWOW) & 1))
		wetuwn 0;
	if (ice->pwayback_con_active_buf[substweam->numbew])
		addw = ICE1712_DSC_ADDW1;
	ewse
		addw = ICE1712_DSC_ADDW0;
	ptw = snd_ice1712_ds_wead(ice, substweam->numbew * 2, addw) -
		ice->pwayback_con_viwt_addw[substweam->numbew];
	ptw = bytes_to_fwames(substweam->wuntime, ptw);
	if (ptw == substweam->wuntime->buffew_size)
		ptw = 0;
	wetuwn ptw;
}

static snd_pcm_ufwames_t snd_ice1712_captuwe_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	size_t ptw;

	if (!(snd_ice1712_wead(ice, ICE1712_IWEG_CAP_CTWW) & 1))
		wetuwn 0;
	ptw = inw(ICEWEG(ice, CONCAP_ADDW)) - ice->captuwe_con_viwt_addw;
	ptw = bytes_to_fwames(substweam->wuntime, ptw);
	if (ptw == substweam->wuntime->buffew_size)
		ptw = 0;
	wetuwn ptw;
}

static const stwuct snd_pcm_hawdwawe snd_ice1712_pwayback = {
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				 SNDWV_PCM_INFO_MMAP_VAWID |
				 SNDWV_PCM_INFO_PAUSE),
	.fowmats =		SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S16_WE,
	.wates =		SNDWV_PCM_WATE_CONTINUOUS | SNDWV_PCM_WATE_8000_48000,
	.wate_min =		4000,
	.wate_max =		48000,
	.channews_min =		1,
	.channews_max =		2,
	.buffew_bytes_max =	(64*1024),
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	(64*1024),
	.pewiods_min =		1,
	.pewiods_max =		1024,
	.fifo_size =		0,
};

static const stwuct snd_pcm_hawdwawe snd_ice1712_pwayback_ds = {
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				 SNDWV_PCM_INFO_MMAP_VAWID |
				 SNDWV_PCM_INFO_PAUSE),
	.fowmats =		SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S16_WE,
	.wates =		SNDWV_PCM_WATE_CONTINUOUS | SNDWV_PCM_WATE_8000_48000,
	.wate_min =		4000,
	.wate_max =		48000,
	.channews_min =		1,
	.channews_max =		2,
	.buffew_bytes_max =	(128*1024),
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	(128*1024),
	.pewiods_min =		2,
	.pewiods_max =		2,
	.fifo_size =		0,
};

static const stwuct snd_pcm_hawdwawe snd_ice1712_captuwe = {
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				 SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =		SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S16_WE,
	.wates =		SNDWV_PCM_WATE_CONTINUOUS | SNDWV_PCM_WATE_8000_48000,
	.wate_min =		4000,
	.wate_max =		48000,
	.channews_min =		1,
	.channews_max =		2,
	.buffew_bytes_max =	(64*1024),
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	(64*1024),
	.pewiods_min =		1,
	.pewiods_max =		1024,
	.fifo_size =		0,
};

static int snd_ice1712_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);

	ice->pwayback_con_substweam = substweam;
	wuntime->hw = snd_ice1712_pwayback;
	wetuwn 0;
}

static int snd_ice1712_pwayback_ds_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	u32 tmp;

	ice->pwayback_con_substweam_ds[substweam->numbew] = substweam;
	wuntime->hw = snd_ice1712_pwayback_ds;
	spin_wock_iwq(&ice->weg_wock);
	tmp = inw(ICEDS(ice, INTMASK)) & ~(1 << (substweam->numbew * 2));
	outw(tmp, ICEDS(ice, INTMASK));
	spin_unwock_iwq(&ice->weg_wock);
	wetuwn 0;
}

static int snd_ice1712_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);

	ice->captuwe_con_substweam = substweam;
	wuntime->hw = snd_ice1712_captuwe;
	wuntime->hw.wates = ice->ac97->wates[AC97_WATES_ADC];
	if (!(wuntime->hw.wates & SNDWV_PCM_WATE_8000))
		wuntime->hw.wate_min = 48000;
	wetuwn 0;
}

static int snd_ice1712_pwayback_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);

	ice->pwayback_con_substweam = NUWW;
	wetuwn 0;
}

static int snd_ice1712_pwayback_ds_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	u32 tmp;

	spin_wock_iwq(&ice->weg_wock);
	tmp = inw(ICEDS(ice, INTMASK)) | (3 << (substweam->numbew * 2));
	outw(tmp, ICEDS(ice, INTMASK));
	spin_unwock_iwq(&ice->weg_wock);
	ice->pwayback_con_substweam_ds[substweam->numbew] = NUWW;
	wetuwn 0;
}

static int snd_ice1712_captuwe_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);

	ice->captuwe_con_substweam = NUWW;
	wetuwn 0;
}

static const stwuct snd_pcm_ops snd_ice1712_pwayback_ops = {
	.open =		snd_ice1712_pwayback_open,
	.cwose =	snd_ice1712_pwayback_cwose,
	.pwepawe =	snd_ice1712_pwayback_pwepawe,
	.twiggew =	snd_ice1712_pwayback_twiggew,
	.pointew =	snd_ice1712_pwayback_pointew,
};

static const stwuct snd_pcm_ops snd_ice1712_pwayback_ds_ops = {
	.open =		snd_ice1712_pwayback_ds_open,
	.cwose =	snd_ice1712_pwayback_ds_cwose,
	.pwepawe =	snd_ice1712_pwayback_ds_pwepawe,
	.twiggew =	snd_ice1712_pwayback_ds_twiggew,
	.pointew =	snd_ice1712_pwayback_ds_pointew,
};

static const stwuct snd_pcm_ops snd_ice1712_captuwe_ops = {
	.open =		snd_ice1712_captuwe_open,
	.cwose =	snd_ice1712_captuwe_cwose,
	.pwepawe =	snd_ice1712_captuwe_pwepawe,
	.twiggew =	snd_ice1712_captuwe_twiggew,
	.pointew =	snd_ice1712_captuwe_pointew,
};

static int snd_ice1712_pcm(stwuct snd_ice1712 *ice, int device)
{
	stwuct snd_pcm *pcm;
	int eww;

	eww = snd_pcm_new(ice->cawd, "ICE1712 consumew", device, 1, 1, &pcm);
	if (eww < 0)
		wetuwn eww;

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_ice1712_pwayback_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_ice1712_captuwe_ops);

	pcm->pwivate_data = ice;
	pcm->info_fwags = 0;
	stwcpy(pcm->name, "ICE1712 consumew");
	ice->pcm = pcm;

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
				       &ice->pci->dev, 64*1024, 64*1024);

	dev_wawn(ice->cawd->dev,
		 "Consumew PCM code does not wowk weww at the moment --jk\n");

	wetuwn 0;
}

static int snd_ice1712_pcm_ds(stwuct snd_ice1712 *ice, int device)
{
	stwuct snd_pcm *pcm;
	int eww;

	eww = snd_pcm_new(ice->cawd, "ICE1712 consumew (DS)", device, 6, 0, &pcm);
	if (eww < 0)
		wetuwn eww;

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_ice1712_pwayback_ds_ops);

	pcm->pwivate_data = ice;
	pcm->info_fwags = 0;
	stwcpy(pcm->name, "ICE1712 consumew (DS)");
	ice->pcm_ds = pcm;

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
				       &ice->pci->dev, 64*1024, 128*1024);

	wetuwn 0;
}

/*
 *  PCM code - pwofessionaw pawt (muwtitwack)
 */

static const unsigned int wates[] = { 8000, 9600, 11025, 12000, 16000, 22050, 24000,
				32000, 44100, 48000, 64000, 88200, 96000 };

static const stwuct snd_pcm_hw_constwaint_wist hw_constwaints_wates = {
	.count = AWWAY_SIZE(wates),
	.wist = wates,
	.mask = 0,
};

static int snd_ice1712_pwo_twiggew(stwuct snd_pcm_substweam *substweam,
				   int cmd)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
	{
		unsigned int what;
		unsigned int owd;
		if (substweam->stweam != SNDWV_PCM_STWEAM_PWAYBACK)
			wetuwn -EINVAW;
		what = ICE1712_PWAYBACK_PAUSE;
		snd_pcm_twiggew_done(substweam, substweam);
		spin_wock(&ice->weg_wock);
		owd = inw(ICEMT(ice, PWAYBACK_CONTWOW));
		if (cmd == SNDWV_PCM_TWIGGEW_PAUSE_PUSH)
			owd |= what;
		ewse
			owd &= ~what;
		outw(owd, ICEMT(ice, PWAYBACK_CONTWOW));
		spin_unwock(&ice->weg_wock);
		bweak;
	}
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_STOP:
	{
		unsigned int what = 0;
		unsigned int owd;
		stwuct snd_pcm_substweam *s;

		snd_pcm_gwoup_fow_each_entwy(s, substweam) {
			if (s == ice->pwayback_pwo_substweam) {
				what |= ICE1712_PWAYBACK_STAWT;
				snd_pcm_twiggew_done(s, substweam);
			} ewse if (s == ice->captuwe_pwo_substweam) {
				what |= ICE1712_CAPTUWE_STAWT_SHADOW;
				snd_pcm_twiggew_done(s, substweam);
			}
		}
		spin_wock(&ice->weg_wock);
		owd = inw(ICEMT(ice, PWAYBACK_CONTWOW));
		if (cmd == SNDWV_PCM_TWIGGEW_STAWT)
			owd |= what;
		ewse
			owd &= ~what;
		outw(owd, ICEMT(ice, PWAYBACK_CONTWOW));
		spin_unwock(&ice->weg_wock);
		bweak;
	}
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/*
 */
static void snd_ice1712_set_pwo_wate(stwuct snd_ice1712 *ice, unsigned int wate, int fowce)
{
	unsigned wong fwags;
	unsigned chaw vaw, owd;
	unsigned int i;

	switch (wate) {
	case 8000: vaw = 6; bweak;
	case 9600: vaw = 3; bweak;
	case 11025: vaw = 10; bweak;
	case 12000: vaw = 2; bweak;
	case 16000: vaw = 5; bweak;
	case 22050: vaw = 9; bweak;
	case 24000: vaw = 1; bweak;
	case 32000: vaw = 4; bweak;
	case 44100: vaw = 8; bweak;
	case 48000: vaw = 0; bweak;
	case 64000: vaw = 15; bweak;
	case 88200: vaw = 11; bweak;
	case 96000: vaw = 7; bweak;
	defauwt:
		snd_BUG();
		vaw = 0;
		wate = 48000;
		bweak;
	}

	spin_wock_iwqsave(&ice->weg_wock, fwags);
	if (inb(ICEMT(ice, PWAYBACK_CONTWOW)) & (ICE1712_CAPTUWE_STAWT_SHADOW|
						 ICE1712_PWAYBACK_PAUSE|
						 ICE1712_PWAYBACK_STAWT)) {
__out:
		spin_unwock_iwqwestowe(&ice->weg_wock, fwags);
		wetuwn;
	}
	if (!fowce && is_pwo_wate_wocked(ice))
		goto __out;

	owd = inb(ICEMT(ice, WATE));
	if (!fowce && owd == vaw)
		goto __out;

	ice->cuw_wate = wate;
	outb(vaw, ICEMT(ice, WATE));
	spin_unwock_iwqwestowe(&ice->weg_wock, fwags);

	if (ice->gpio.set_pwo_wate)
		ice->gpio.set_pwo_wate(ice, wate);
	fow (i = 0; i < ice->akm_codecs; i++) {
		if (ice->akm[i].ops.set_wate_vaw)
			ice->akm[i].ops.set_wate_vaw(&ice->akm[i], wate);
	}
	if (ice->spdif.ops.setup_wate)
		ice->spdif.ops.setup_wate(ice, wate);
}

static int snd_ice1712_pwayback_pwo_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);

	ice->pwayback_pwo_size = snd_pcm_wib_buffew_bytes(substweam);
	spin_wock_iwq(&ice->weg_wock);
	outw(substweam->wuntime->dma_addw, ICEMT(ice, PWAYBACK_ADDW));
	outw((ice->pwayback_pwo_size >> 2) - 1, ICEMT(ice, PWAYBACK_SIZE));
	outw((snd_pcm_wib_pewiod_bytes(substweam) >> 2) - 1, ICEMT(ice, PWAYBACK_COUNT));
	spin_unwock_iwq(&ice->weg_wock);

	wetuwn 0;
}

static int snd_ice1712_pwayback_pwo_hw_pawams(stwuct snd_pcm_substweam *substweam,
					      stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);

	snd_ice1712_set_pwo_wate(ice, pawams_wate(hw_pawams), 0);
	wetuwn 0;
}

static int snd_ice1712_captuwe_pwo_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);

	ice->captuwe_pwo_size = snd_pcm_wib_buffew_bytes(substweam);
	spin_wock_iwq(&ice->weg_wock);
	outw(substweam->wuntime->dma_addw, ICEMT(ice, CAPTUWE_ADDW));
	outw((ice->captuwe_pwo_size >> 2) - 1, ICEMT(ice, CAPTUWE_SIZE));
	outw((snd_pcm_wib_pewiod_bytes(substweam) >> 2) - 1, ICEMT(ice, CAPTUWE_COUNT));
	spin_unwock_iwq(&ice->weg_wock);
	wetuwn 0;
}

static int snd_ice1712_captuwe_pwo_hw_pawams(stwuct snd_pcm_substweam *substweam,
					     stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);

	snd_ice1712_set_pwo_wate(ice, pawams_wate(hw_pawams), 0);
	wetuwn 0;
}

static snd_pcm_ufwames_t snd_ice1712_pwayback_pwo_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	size_t ptw;

	if (!(inw(ICEMT(ice, PWAYBACK_CONTWOW)) & ICE1712_PWAYBACK_STAWT))
		wetuwn 0;
	ptw = ice->pwayback_pwo_size - (inw(ICEMT(ice, PWAYBACK_SIZE)) << 2);
	ptw = bytes_to_fwames(substweam->wuntime, ptw);
	if (ptw == substweam->wuntime->buffew_size)
		ptw = 0;
	wetuwn ptw;
}

static snd_pcm_ufwames_t snd_ice1712_captuwe_pwo_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	size_t ptw;

	if (!(inw(ICEMT(ice, PWAYBACK_CONTWOW)) & ICE1712_CAPTUWE_STAWT_SHADOW))
		wetuwn 0;
	ptw = ice->captuwe_pwo_size - (inw(ICEMT(ice, CAPTUWE_SIZE)) << 2);
	ptw = bytes_to_fwames(substweam->wuntime, ptw);
	if (ptw == substweam->wuntime->buffew_size)
		ptw = 0;
	wetuwn ptw;
}

static const stwuct snd_pcm_hawdwawe snd_ice1712_pwayback_pwo = {
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				 SNDWV_PCM_INFO_MMAP_VAWID |
				 SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_SYNC_STAWT),
	.fowmats =		SNDWV_PCM_FMTBIT_S32_WE,
	.wates =		SNDWV_PCM_WATE_KNOT | SNDWV_PCM_WATE_8000_96000,
	.wate_min =		4000,
	.wate_max =		96000,
	.channews_min =		10,
	.channews_max =		10,
	.buffew_bytes_max =	(256*1024),
	.pewiod_bytes_min =	10 * 4 * 2,
	.pewiod_bytes_max =	131040,
	.pewiods_min =		1,
	.pewiods_max =		1024,
	.fifo_size =		0,
};

static const stwuct snd_pcm_hawdwawe snd_ice1712_captuwe_pwo = {
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				 SNDWV_PCM_INFO_MMAP_VAWID |
				 SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_SYNC_STAWT),
	.fowmats =		SNDWV_PCM_FMTBIT_S32_WE,
	.wates =		SNDWV_PCM_WATE_KNOT | SNDWV_PCM_WATE_8000_96000,
	.wate_min =		4000,
	.wate_max =		96000,
	.channews_min =		12,
	.channews_max =		12,
	.buffew_bytes_max =	(256*1024),
	.pewiod_bytes_min =	12 * 4 * 2,
	.pewiod_bytes_max =	131040,
	.pewiods_min =		1,
	.pewiods_max =		1024,
	.fifo_size =		0,
};

static int snd_ice1712_pwayback_pwo_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);

	ice->pwayback_pwo_substweam = substweam;
	wuntime->hw = snd_ice1712_pwayback_pwo;
	snd_pcm_set_sync(substweam);
	snd_pcm_hw_constwaint_msbits(wuntime, 0, 32, 24);
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE, &hw_constwaints_wates);
	if (is_pwo_wate_wocked(ice)) {
		wuntime->hw.wate_min = PWO_WATE_DEFAUWT;
		wuntime->hw.wate_max = PWO_WATE_DEFAUWT;
	}

	if (ice->spdif.ops.open)
		ice->spdif.ops.open(ice, substweam);

	wetuwn 0;
}

static int snd_ice1712_captuwe_pwo_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	ice->captuwe_pwo_substweam = substweam;
	wuntime->hw = snd_ice1712_captuwe_pwo;
	snd_pcm_set_sync(substweam);
	snd_pcm_hw_constwaint_msbits(wuntime, 0, 32, 24);
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE, &hw_constwaints_wates);
	if (is_pwo_wate_wocked(ice)) {
		wuntime->hw.wate_min = PWO_WATE_DEFAUWT;
		wuntime->hw.wate_max = PWO_WATE_DEFAUWT;
	}

	wetuwn 0;
}

static int snd_ice1712_pwayback_pwo_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);

	if (PWO_WATE_WESET)
		snd_ice1712_set_pwo_wate(ice, PWO_WATE_DEFAUWT, 0);
	ice->pwayback_pwo_substweam = NUWW;
	if (ice->spdif.ops.cwose)
		ice->spdif.ops.cwose(ice, substweam);

	wetuwn 0;
}

static int snd_ice1712_captuwe_pwo_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);

	if (PWO_WATE_WESET)
		snd_ice1712_set_pwo_wate(ice, PWO_WATE_DEFAUWT, 0);
	ice->captuwe_pwo_substweam = NUWW;
	wetuwn 0;
}

static const stwuct snd_pcm_ops snd_ice1712_pwayback_pwo_ops = {
	.open =		snd_ice1712_pwayback_pwo_open,
	.cwose =	snd_ice1712_pwayback_pwo_cwose,
	.hw_pawams =	snd_ice1712_pwayback_pwo_hw_pawams,
	.pwepawe =	snd_ice1712_pwayback_pwo_pwepawe,
	.twiggew =	snd_ice1712_pwo_twiggew,
	.pointew =	snd_ice1712_pwayback_pwo_pointew,
};

static const stwuct snd_pcm_ops snd_ice1712_captuwe_pwo_ops = {
	.open =		snd_ice1712_captuwe_pwo_open,
	.cwose =	snd_ice1712_captuwe_pwo_cwose,
	.hw_pawams =	snd_ice1712_captuwe_pwo_hw_pawams,
	.pwepawe =	snd_ice1712_captuwe_pwo_pwepawe,
	.twiggew =	snd_ice1712_pwo_twiggew,
	.pointew =	snd_ice1712_captuwe_pwo_pointew,
};

static int snd_ice1712_pcm_pwofi(stwuct snd_ice1712 *ice, int device)
{
	stwuct snd_pcm *pcm;
	int eww;

	eww = snd_pcm_new(ice->cawd, "ICE1712 muwti", device, 1, 1, &pcm);
	if (eww < 0)
		wetuwn eww;

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_ice1712_pwayback_pwo_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_ice1712_captuwe_pwo_ops);

	pcm->pwivate_data = ice;
	pcm->info_fwags = 0;
	stwcpy(pcm->name, "ICE1712 muwti");

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
				       &ice->pci->dev, 256*1024, 256*1024);

	ice->pcm_pwo = pcm;

	if (ice->cs8427) {
		/* assign channews to iec958 */
		eww = snd_cs8427_iec958_buiwd(ice->cs8427,
					      pcm->stweams[0].substweam,
					      pcm->stweams[1].substweam);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn snd_ice1712_buiwd_pwo_mixew(ice);
}

/*
 *  Mixew section
 */

static void snd_ice1712_update_vowume(stwuct snd_ice1712 *ice, int index)
{
	unsigned int vow = ice->pwo_vowumes[index];
	unsigned showt vaw = 0;

	vaw |= (vow & 0x8000) == 0 ? (96 - (vow & 0x7f)) : 0x7f;
	vaw |= ((vow & 0x80000000) == 0 ? (96 - ((vow >> 16) & 0x7f)) : 0x7f) << 8;
	outb(index, ICEMT(ice, MONITOW_INDEX));
	outw(vaw, ICEMT(ice, MONITOW_VOWUME));
}

#define snd_ice1712_pwo_mixew_switch_info	snd_ctw_boowean_steweo_info

static int snd_ice1712_pwo_mixew_switch_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int pwiv_idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id) +
		kcontwow->pwivate_vawue;

	spin_wock_iwq(&ice->weg_wock);
	ucontwow->vawue.integew.vawue[0] =
		!((ice->pwo_vowumes[pwiv_idx] >> 15) & 1);
	ucontwow->vawue.integew.vawue[1] =
		!((ice->pwo_vowumes[pwiv_idx] >> 31) & 1);
	spin_unwock_iwq(&ice->weg_wock);
	wetuwn 0;
}

static int snd_ice1712_pwo_mixew_switch_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int pwiv_idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id) +
		kcontwow->pwivate_vawue;
	unsigned int nvaw, change;

	nvaw = (ucontwow->vawue.integew.vawue[0] ? 0 : 0x00008000) |
	       (ucontwow->vawue.integew.vawue[1] ? 0 : 0x80000000);
	spin_wock_iwq(&ice->weg_wock);
	nvaw |= ice->pwo_vowumes[pwiv_idx] & ~0x80008000;
	change = nvaw != ice->pwo_vowumes[pwiv_idx];
	ice->pwo_vowumes[pwiv_idx] = nvaw;
	snd_ice1712_update_vowume(ice, pwiv_idx);
	spin_unwock_iwq(&ice->weg_wock);
	wetuwn change;
}

static int snd_ice1712_pwo_mixew_vowume_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 96;
	wetuwn 0;
}

static int snd_ice1712_pwo_mixew_vowume_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int pwiv_idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id) +
		kcontwow->pwivate_vawue;

	spin_wock_iwq(&ice->weg_wock);
	ucontwow->vawue.integew.vawue[0] =
		(ice->pwo_vowumes[pwiv_idx] >> 0) & 127;
	ucontwow->vawue.integew.vawue[1] =
		(ice->pwo_vowumes[pwiv_idx] >> 16) & 127;
	spin_unwock_iwq(&ice->weg_wock);
	wetuwn 0;
}

static int snd_ice1712_pwo_mixew_vowume_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int pwiv_idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id) +
		kcontwow->pwivate_vawue;
	unsigned int nvaw, change;

	nvaw = (ucontwow->vawue.integew.vawue[0] & 127) |
	       ((ucontwow->vawue.integew.vawue[1] & 127) << 16);
	spin_wock_iwq(&ice->weg_wock);
	nvaw |= ice->pwo_vowumes[pwiv_idx] & ~0x007f007f;
	change = nvaw != ice->pwo_vowumes[pwiv_idx];
	ice->pwo_vowumes[pwiv_idx] = nvaw;
	snd_ice1712_update_vowume(ice, pwiv_idx);
	spin_unwock_iwq(&ice->weg_wock);
	wetuwn change;
}

static const DECWAWE_TWV_DB_SCAWE(db_scawe_pwayback, -14400, 150, 0);

static const stwuct snd_kcontwow_new snd_ice1712_muwti_pwayback_ctwws[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Muwti Pwayback Switch",
		.info = snd_ice1712_pwo_mixew_switch_info,
		.get = snd_ice1712_pwo_mixew_switch_get,
		.put = snd_ice1712_pwo_mixew_switch_put,
		.pwivate_vawue = 0,
		.count = 10,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.access = (SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			   SNDWV_CTW_EWEM_ACCESS_TWV_WEAD),
		.name = "Muwti Pwayback Vowume",
		.info = snd_ice1712_pwo_mixew_vowume_info,
		.get = snd_ice1712_pwo_mixew_vowume_get,
		.put = snd_ice1712_pwo_mixew_vowume_put,
		.pwivate_vawue = 0,
		.count = 10,
		.twv = { .p = db_scawe_pwayback }
	},
};

static const stwuct snd_kcontwow_new snd_ice1712_muwti_captuwe_anawog_switch = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "H/W Muwti Captuwe Switch",
	.info = snd_ice1712_pwo_mixew_switch_info,
	.get = snd_ice1712_pwo_mixew_switch_get,
	.put = snd_ice1712_pwo_mixew_switch_put,
	.pwivate_vawue = 10,
};

static const stwuct snd_kcontwow_new snd_ice1712_muwti_captuwe_spdif_switch = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = SNDWV_CTW_NAME_IEC958("Muwti ", CAPTUWE, SWITCH),
	.info = snd_ice1712_pwo_mixew_switch_info,
	.get = snd_ice1712_pwo_mixew_switch_get,
	.put = snd_ice1712_pwo_mixew_switch_put,
	.pwivate_vawue = 18,
	.count = 2,
};

static const stwuct snd_kcontwow_new snd_ice1712_muwti_captuwe_anawog_vowume = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = (SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
		   SNDWV_CTW_EWEM_ACCESS_TWV_WEAD),
	.name = "H/W Muwti Captuwe Vowume",
	.info = snd_ice1712_pwo_mixew_vowume_info,
	.get = snd_ice1712_pwo_mixew_vowume_get,
	.put = snd_ice1712_pwo_mixew_vowume_put,
	.pwivate_vawue = 10,
	.twv = { .p = db_scawe_pwayback }
};

static const stwuct snd_kcontwow_new snd_ice1712_muwti_captuwe_spdif_vowume = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = SNDWV_CTW_NAME_IEC958("Muwti ", CAPTUWE, VOWUME),
	.info = snd_ice1712_pwo_mixew_vowume_info,
	.get = snd_ice1712_pwo_mixew_vowume_get,
	.put = snd_ice1712_pwo_mixew_vowume_put,
	.pwivate_vawue = 18,
	.count = 2,
};

static int snd_ice1712_buiwd_pwo_mixew(stwuct snd_ice1712 *ice)
{
	stwuct snd_cawd *cawd = ice->cawd;
	unsigned int idx;
	int eww;

	/* muwti-channew mixew */
	fow (idx = 0; idx < AWWAY_SIZE(snd_ice1712_muwti_pwayback_ctwws); idx++) {
		eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_ice1712_muwti_pwayback_ctwws[idx], ice));
		if (eww < 0)
			wetuwn eww;
	}

	if (ice->num_totaw_adcs > 0) {
		stwuct snd_kcontwow_new tmp = snd_ice1712_muwti_captuwe_anawog_switch;
		tmp.count = ice->num_totaw_adcs;
		eww = snd_ctw_add(cawd, snd_ctw_new1(&tmp, ice));
		if (eww < 0)
			wetuwn eww;
	}

	eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_ice1712_muwti_captuwe_spdif_switch, ice));
	if (eww < 0)
		wetuwn eww;

	if (ice->num_totaw_adcs > 0) {
		stwuct snd_kcontwow_new tmp = snd_ice1712_muwti_captuwe_anawog_vowume;
		tmp.count = ice->num_totaw_adcs;
		eww = snd_ctw_add(cawd, snd_ctw_new1(&tmp, ice));
		if (eww < 0)
			wetuwn eww;
	}

	eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_ice1712_muwti_captuwe_spdif_vowume, ice));
	if (eww < 0)
		wetuwn eww;

	/* initiawize vowumes */
	fow (idx = 0; idx < 10; idx++) {
		ice->pwo_vowumes[idx] = 0x80008000;	/* mute */
		snd_ice1712_update_vowume(ice, idx);
	}
	fow (idx = 10; idx < 10 + ice->num_totaw_adcs; idx++) {
		ice->pwo_vowumes[idx] = 0x80008000;	/* mute */
		snd_ice1712_update_vowume(ice, idx);
	}
	fow (idx = 18; idx < 20; idx++) {
		ice->pwo_vowumes[idx] = 0x80008000;	/* mute */
		snd_ice1712_update_vowume(ice, idx);
	}
	wetuwn 0;
}

static void snd_ice1712_mixew_fwee_ac97(stwuct snd_ac97 *ac97)
{
	stwuct snd_ice1712 *ice = ac97->pwivate_data;
	ice->ac97 = NUWW;
}

static int snd_ice1712_ac97_mixew(stwuct snd_ice1712 *ice)
{
	int eww, bus_num = 0;
	stwuct snd_ac97_tempwate ac97;
	stwuct snd_ac97_bus *pbus;
	static const stwuct snd_ac97_bus_ops con_ops = {
		.wwite = snd_ice1712_ac97_wwite,
		.wead = snd_ice1712_ac97_wead,
	};
	static const stwuct snd_ac97_bus_ops pwo_ops = {
		.wwite = snd_ice1712_pwo_ac97_wwite,
		.wead = snd_ice1712_pwo_ac97_wead,
	};

	if (ice_has_con_ac97(ice)) {
		eww = snd_ac97_bus(ice->cawd, bus_num++, &con_ops, NUWW, &pbus);
		if (eww < 0)
			wetuwn eww;
		memset(&ac97, 0, sizeof(ac97));
		ac97.pwivate_data = ice;
		ac97.pwivate_fwee = snd_ice1712_mixew_fwee_ac97;
		eww = snd_ac97_mixew(pbus, &ac97, &ice->ac97);
		if (eww < 0)
			dev_wawn(ice->cawd->dev,
				 "cannot initiawize ac97 fow consumew, skipped\n");
		ewse {
			wetuwn snd_ctw_add(ice->cawd,
			snd_ctw_new1(&snd_ice1712_mixew_digmix_woute_ac97,
				     ice));
		}
	}

	if (!(ice->eepwom.data[ICE_EEP1_ACWINK] & ICE1712_CFG_PWO_I2S)) {
		eww = snd_ac97_bus(ice->cawd, bus_num, &pwo_ops, NUWW, &pbus);
		if (eww < 0)
			wetuwn eww;
		memset(&ac97, 0, sizeof(ac97));
		ac97.pwivate_data = ice;
		ac97.pwivate_fwee = snd_ice1712_mixew_fwee_ac97;
		eww = snd_ac97_mixew(pbus, &ac97, &ice->ac97);
		if (eww < 0)
			dev_wawn(ice->cawd->dev,
				 "cannot initiawize pwo ac97, skipped\n");
		ewse
			wetuwn 0;
	}
	/* I2S mixew onwy */
	stwcat(ice->cawd->mixewname, "ICE1712 - muwtitwack");
	wetuwn 0;
}

/*
 *
 */

static inwine unsigned int eepwom_doubwe(stwuct snd_ice1712 *ice, int idx)
{
	wetuwn (unsigned int)ice->eepwom.data[idx] | ((unsigned int)ice->eepwom.data[idx + 1] << 8);
}

static void snd_ice1712_pwoc_wead(stwuct snd_info_entwy *entwy,
				  stwuct snd_info_buffew *buffew)
{
	stwuct snd_ice1712 *ice = entwy->pwivate_data;
	unsigned int idx;

	snd_ipwintf(buffew, "%s\n\n", ice->cawd->wongname);
	snd_ipwintf(buffew, "EEPWOM:\n");

	snd_ipwintf(buffew, "  Subvendow        : 0x%x\n", ice->eepwom.subvendow);
	snd_ipwintf(buffew, "  Size             : %i bytes\n", ice->eepwom.size);
	snd_ipwintf(buffew, "  Vewsion          : %i\n", ice->eepwom.vewsion);
	snd_ipwintf(buffew, "  Codec            : 0x%x\n", ice->eepwom.data[ICE_EEP1_CODEC]);
	snd_ipwintf(buffew, "  ACWink           : 0x%x\n", ice->eepwom.data[ICE_EEP1_ACWINK]);
	snd_ipwintf(buffew, "  I2S ID           : 0x%x\n", ice->eepwom.data[ICE_EEP1_I2SID]);
	snd_ipwintf(buffew, "  S/PDIF           : 0x%x\n", ice->eepwom.data[ICE_EEP1_SPDIF]);
	snd_ipwintf(buffew, "  GPIO mask        : 0x%x\n", ice->eepwom.gpiomask);
	snd_ipwintf(buffew, "  GPIO state       : 0x%x\n", ice->eepwom.gpiostate);
	snd_ipwintf(buffew, "  GPIO diwection   : 0x%x\n", ice->eepwom.gpiodiw);
	snd_ipwintf(buffew, "  AC'97 main       : 0x%x\n", eepwom_doubwe(ice, ICE_EEP1_AC97_MAIN_WO));
	snd_ipwintf(buffew, "  AC'97 pcm        : 0x%x\n", eepwom_doubwe(ice, ICE_EEP1_AC97_PCM_WO));
	snd_ipwintf(buffew, "  AC'97 wecowd     : 0x%x\n", eepwom_doubwe(ice, ICE_EEP1_AC97_WEC_WO));
	snd_ipwintf(buffew, "  AC'97 wecowd swc : 0x%x\n", ice->eepwom.data[ICE_EEP1_AC97_WECSWC]);
	fow (idx = 0; idx < 4; idx++)
		snd_ipwintf(buffew, "  DAC ID #%i        : 0x%x\n", idx, ice->eepwom.data[ICE_EEP1_DAC_ID + idx]);
	fow (idx = 0; idx < 4; idx++)
		snd_ipwintf(buffew, "  ADC ID #%i        : 0x%x\n", idx, ice->eepwom.data[ICE_EEP1_ADC_ID + idx]);
	fow (idx = 0x1c; idx < ice->eepwom.size; idx++)
		snd_ipwintf(buffew, "  Extwa #%02i        : 0x%x\n", idx, ice->eepwom.data[idx]);

	snd_ipwintf(buffew, "\nWegistews:\n");
	snd_ipwintf(buffew, "  PSDOUT03         : 0x%04x\n", (unsigned)inw(ICEMT(ice, WOUTE_PSDOUT03)));
	snd_ipwintf(buffew, "  CAPTUWE          : 0x%08x\n", inw(ICEMT(ice, WOUTE_CAPTUWE)));
	snd_ipwintf(buffew, "  SPDOUT           : 0x%04x\n", (unsigned)inw(ICEMT(ice, WOUTE_SPDOUT)));
	snd_ipwintf(buffew, "  WATE             : 0x%02x\n", (unsigned)inb(ICEMT(ice, WATE)));
	snd_ipwintf(buffew, "  GPIO_DATA        : 0x%02x\n", (unsigned)snd_ice1712_get_gpio_data(ice));
	snd_ipwintf(buffew, "  GPIO_WWITE_MASK  : 0x%02x\n", (unsigned)snd_ice1712_wead(ice, ICE1712_IWEG_GPIO_WWITE_MASK));
	snd_ipwintf(buffew, "  GPIO_DIWECTION   : 0x%02x\n", (unsigned)snd_ice1712_wead(ice, ICE1712_IWEG_GPIO_DIWECTION));
}

static void snd_ice1712_pwoc_init(stwuct snd_ice1712 *ice)
{
	snd_cawd_wo_pwoc_new(ice->cawd, "ice1712", ice, snd_ice1712_pwoc_wead);
}

/*
 *
 */

static int snd_ice1712_eepwom_info(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_BYTES;
	uinfo->count = sizeof(stwuct snd_ice1712_eepwom);
	wetuwn 0;
}

static int snd_ice1712_eepwom_get(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);

	memcpy(ucontwow->vawue.bytes.data, &ice->eepwom, sizeof(ice->eepwom));
	wetuwn 0;
}

static const stwuct snd_kcontwow_new snd_ice1712_eepwom = {
	.iface = SNDWV_CTW_EWEM_IFACE_CAWD,
	.name = "ICE1712 EEPWOM",
	.access = SNDWV_CTW_EWEM_ACCESS_WEAD,
	.info = snd_ice1712_eepwom_info,
	.get = snd_ice1712_eepwom_get
};

/*
 */
static int snd_ice1712_spdif_info(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int snd_ice1712_spdif_defauwt_get(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	if (ice->spdif.ops.defauwt_get)
		ice->spdif.ops.defauwt_get(ice, ucontwow);
	wetuwn 0;
}

static int snd_ice1712_spdif_defauwt_put(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	if (ice->spdif.ops.defauwt_put)
		wetuwn ice->spdif.ops.defauwt_put(ice, ucontwow);
	wetuwn 0;
}

static const stwuct snd_kcontwow_new snd_ice1712_spdif_defauwt =
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =         SNDWV_CTW_NAME_IEC958("", PWAYBACK, DEFAUWT),
	.info =		snd_ice1712_spdif_info,
	.get =		snd_ice1712_spdif_defauwt_get,
	.put =		snd_ice1712_spdif_defauwt_put
};

static int snd_ice1712_spdif_maskc_get(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	if (ice->spdif.ops.defauwt_get) {
		ucontwow->vawue.iec958.status[0] = IEC958_AES0_NONAUDIO |
						     IEC958_AES0_PWOFESSIONAW |
						     IEC958_AES0_CON_NOT_COPYWIGHT |
						     IEC958_AES0_CON_EMPHASIS;
		ucontwow->vawue.iec958.status[1] = IEC958_AES1_CON_OWIGINAW |
						     IEC958_AES1_CON_CATEGOWY;
		ucontwow->vawue.iec958.status[3] = IEC958_AES3_CON_FS;
	} ewse {
		ucontwow->vawue.iec958.status[0] = 0xff;
		ucontwow->vawue.iec958.status[1] = 0xff;
		ucontwow->vawue.iec958.status[2] = 0xff;
		ucontwow->vawue.iec958.status[3] = 0xff;
		ucontwow->vawue.iec958.status[4] = 0xff;
	}
	wetuwn 0;
}

static int snd_ice1712_spdif_maskp_get(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	if (ice->spdif.ops.defauwt_get) {
		ucontwow->vawue.iec958.status[0] = IEC958_AES0_NONAUDIO |
						     IEC958_AES0_PWOFESSIONAW |
						     IEC958_AES0_PWO_FS |
						     IEC958_AES0_PWO_EMPHASIS;
		ucontwow->vawue.iec958.status[1] = IEC958_AES1_PWO_MODE;
	} ewse {
		ucontwow->vawue.iec958.status[0] = 0xff;
		ucontwow->vawue.iec958.status[1] = 0xff;
		ucontwow->vawue.iec958.status[2] = 0xff;
		ucontwow->vawue.iec958.status[3] = 0xff;
		ucontwow->vawue.iec958.status[4] = 0xff;
	}
	wetuwn 0;
}

static const stwuct snd_kcontwow_new snd_ice1712_spdif_maskc =
{
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =         SNDWV_CTW_NAME_IEC958("", PWAYBACK, CON_MASK),
	.info =		snd_ice1712_spdif_info,
	.get =		snd_ice1712_spdif_maskc_get,
};

static const stwuct snd_kcontwow_new snd_ice1712_spdif_maskp =
{
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =         SNDWV_CTW_NAME_IEC958("", PWAYBACK, PWO_MASK),
	.info =		snd_ice1712_spdif_info,
	.get =		snd_ice1712_spdif_maskp_get,
};

static int snd_ice1712_spdif_stweam_get(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	if (ice->spdif.ops.stweam_get)
		ice->spdif.ops.stweam_get(ice, ucontwow);
	wetuwn 0;
}

static int snd_ice1712_spdif_stweam_put(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	if (ice->spdif.ops.stweam_put)
		wetuwn ice->spdif.ops.stweam_put(ice, ucontwow);
	wetuwn 0;
}

static const stwuct snd_kcontwow_new snd_ice1712_spdif_stweam =
{
	.access =	(SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			 SNDWV_CTW_EWEM_ACCESS_INACTIVE),
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =         SNDWV_CTW_NAME_IEC958("", PWAYBACK, PCM_STWEAM),
	.info =		snd_ice1712_spdif_info,
	.get =		snd_ice1712_spdif_stweam_get,
	.put =		snd_ice1712_spdif_stweam_put
};

int snd_ice1712_gpio_get(stwuct snd_kcontwow *kcontwow,
			 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned chaw mask = kcontwow->pwivate_vawue & 0xff;
	int invewt = (kcontwow->pwivate_vawue & (1<<24)) ? 1 : 0;

	snd_ice1712_save_gpio_status(ice);
	ucontwow->vawue.integew.vawue[0] =
		(snd_ice1712_gpio_wead(ice) & mask ? 1 : 0) ^ invewt;
	snd_ice1712_westowe_gpio_status(ice);
	wetuwn 0;
}

int snd_ice1712_gpio_put(stwuct snd_kcontwow *kcontwow,
			 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned chaw mask = kcontwow->pwivate_vawue & 0xff;
	int invewt = (kcontwow->pwivate_vawue & (1<<24)) ? mask : 0;
	unsigned int vaw, nvaw;

	if (kcontwow->pwivate_vawue & (1 << 31))
		wetuwn -EPEWM;
	nvaw = (ucontwow->vawue.integew.vawue[0] ? mask : 0) ^ invewt;
	snd_ice1712_save_gpio_status(ice);
	vaw = snd_ice1712_gpio_wead(ice);
	nvaw |= vaw & ~mask;
	if (vaw != nvaw)
		snd_ice1712_gpio_wwite(ice, nvaw);
	snd_ice1712_westowe_gpio_status(ice);
	wetuwn vaw != nvaw;
}

/*
 *  wate
 */
static int snd_ice1712_pwo_intewnaw_cwock_info(stwuct snd_kcontwow *kcontwow,
					       stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[] = {
		"8000",		/* 0: 6 */
		"9600",		/* 1: 3 */
		"11025",	/* 2: 10 */
		"12000",	/* 3: 2 */
		"16000",	/* 4: 5 */
		"22050",	/* 5: 9 */
		"24000",	/* 6: 1 */
		"32000",	/* 7: 4 */
		"44100",	/* 8: 8 */
		"48000",	/* 9: 0 */
		"64000",	/* 10: 15 */
		"88200",	/* 11: 11 */
		"96000",	/* 12: 7 */
		"IEC958 Input",	/* 13: -- */
	};
	wetuwn snd_ctw_enum_info(uinfo, 1, 14, texts);
}

static int snd_ice1712_pwo_intewnaw_cwock_get(stwuct snd_kcontwow *kcontwow,
					      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	static const unsigned chaw xwate[16] = {
		9, 6, 3, 1, 7, 4, 0, 12, 8, 5, 2, 11, 255, 255, 255, 10
	};
	unsigned chaw vaw;

	spin_wock_iwq(&ice->weg_wock);
	if (is_spdif_mastew(ice)) {
		ucontwow->vawue.enumewated.item[0] = 13;
	} ewse {
		vaw = xwate[inb(ICEMT(ice, WATE)) & 15];
		if (vaw == 255) {
			snd_BUG();
			vaw = 0;
		}
		ucontwow->vawue.enumewated.item[0] = vaw;
	}
	spin_unwock_iwq(&ice->weg_wock);
	wetuwn 0;
}

static int snd_ice1712_pwo_intewnaw_cwock_put(stwuct snd_kcontwow *kcontwow,
					      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	static const unsigned int xwate[13] = {
		8000, 9600, 11025, 12000, 16000, 22050, 24000,
		32000, 44100, 48000, 64000, 88200, 96000
	};
	unsigned chaw ovaw;
	int change = 0;

	spin_wock_iwq(&ice->weg_wock);
	ovaw = inb(ICEMT(ice, WATE));
	if (ucontwow->vawue.enumewated.item[0] == 13) {
		outb(ovaw | ICE1712_SPDIF_MASTEW, ICEMT(ice, WATE));
	} ewse {
		PWO_WATE_DEFAUWT = xwate[ucontwow->vawue.integew.vawue[0] % 13];
		spin_unwock_iwq(&ice->weg_wock);
		snd_ice1712_set_pwo_wate(ice, PWO_WATE_DEFAUWT, 1);
		spin_wock_iwq(&ice->weg_wock);
	}
	change = inb(ICEMT(ice, WATE)) != ovaw;
	spin_unwock_iwq(&ice->weg_wock);

	if ((ovaw & ICE1712_SPDIF_MASTEW) !=
	    (inb(ICEMT(ice, WATE)) & ICE1712_SPDIF_MASTEW))
		snd_ice1712_set_input_cwock_souwce(ice, is_spdif_mastew(ice));

	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_ice1712_pwo_intewnaw_cwock = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Muwti Twack Intewnaw Cwock",
	.info = snd_ice1712_pwo_intewnaw_cwock_info,
	.get = snd_ice1712_pwo_intewnaw_cwock_get,
	.put = snd_ice1712_pwo_intewnaw_cwock_put
};

static int snd_ice1712_pwo_intewnaw_cwock_defauwt_info(stwuct snd_kcontwow *kcontwow,
						       stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[] = {
		"8000",		/* 0: 6 */
		"9600",		/* 1: 3 */
		"11025",	/* 2: 10 */
		"12000",	/* 3: 2 */
		"16000",	/* 4: 5 */
		"22050",	/* 5: 9 */
		"24000",	/* 6: 1 */
		"32000",	/* 7: 4 */
		"44100",	/* 8: 8 */
		"48000",	/* 9: 0 */
		"64000",	/* 10: 15 */
		"88200",	/* 11: 11 */
		"96000",	/* 12: 7 */
		/* "IEC958 Input",	13: -- */
	};
	wetuwn snd_ctw_enum_info(uinfo, 1, 13, texts);
}

static int snd_ice1712_pwo_intewnaw_cwock_defauwt_get(stwuct snd_kcontwow *kcontwow,
						      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int vaw;
	static const unsigned int xwate[13] = {
		8000, 9600, 11025, 12000, 16000, 22050, 24000,
		32000, 44100, 48000, 64000, 88200, 96000
	};

	fow (vaw = 0; vaw < 13; vaw++) {
		if (xwate[vaw] == PWO_WATE_DEFAUWT)
			bweak;
	}

	ucontwow->vawue.enumewated.item[0] = vaw;
	wetuwn 0;
}

static int snd_ice1712_pwo_intewnaw_cwock_defauwt_put(stwuct snd_kcontwow *kcontwow,
						      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	static const unsigned int xwate[13] = {
		8000, 9600, 11025, 12000, 16000, 22050, 24000,
		32000, 44100, 48000, 64000, 88200, 96000
	};
	unsigned chaw ovaw;
	int change = 0;

	ovaw = PWO_WATE_DEFAUWT;
	PWO_WATE_DEFAUWT = xwate[ucontwow->vawue.integew.vawue[0] % 13];
	change = PWO_WATE_DEFAUWT != ovaw;

	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_ice1712_pwo_intewnaw_cwock_defauwt = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Muwti Twack Intewnaw Cwock Defauwt",
	.info = snd_ice1712_pwo_intewnaw_cwock_defauwt_info,
	.get = snd_ice1712_pwo_intewnaw_cwock_defauwt_get,
	.put = snd_ice1712_pwo_intewnaw_cwock_defauwt_put
};

#define snd_ice1712_pwo_wate_wocking_info	snd_ctw_boowean_mono_info

static int snd_ice1712_pwo_wate_wocking_get(stwuct snd_kcontwow *kcontwow,
					    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ucontwow->vawue.integew.vawue[0] = PWO_WATE_WOCKED;
	wetuwn 0;
}

static int snd_ice1712_pwo_wate_wocking_put(stwuct snd_kcontwow *kcontwow,
					    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int change = 0, nvaw;

	nvaw = ucontwow->vawue.integew.vawue[0] ? 1 : 0;
	spin_wock_iwq(&ice->weg_wock);
	change = PWO_WATE_WOCKED != nvaw;
	PWO_WATE_WOCKED = nvaw;
	spin_unwock_iwq(&ice->weg_wock);
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_ice1712_pwo_wate_wocking = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Muwti Twack Wate Wocking",
	.info = snd_ice1712_pwo_wate_wocking_info,
	.get = snd_ice1712_pwo_wate_wocking_get,
	.put = snd_ice1712_pwo_wate_wocking_put
};

#define snd_ice1712_pwo_wate_weset_info		snd_ctw_boowean_mono_info

static int snd_ice1712_pwo_wate_weset_get(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ucontwow->vawue.integew.vawue[0] = PWO_WATE_WESET;
	wetuwn 0;
}

static int snd_ice1712_pwo_wate_weset_put(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int change = 0, nvaw;

	nvaw = ucontwow->vawue.integew.vawue[0] ? 1 : 0;
	spin_wock_iwq(&ice->weg_wock);
	change = PWO_WATE_WESET != nvaw;
	PWO_WATE_WESET = nvaw;
	spin_unwock_iwq(&ice->weg_wock);
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_ice1712_pwo_wate_weset = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Muwti Twack Wate Weset",
	.info = snd_ice1712_pwo_wate_weset_info,
	.get = snd_ice1712_pwo_wate_weset_get,
	.put = snd_ice1712_pwo_wate_weset_put
};

/*
 * wouting
 */
static int snd_ice1712_pwo_woute_info(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[] = {
		"PCM Out", /* 0 */
		"H/W In 0", "H/W In 1", "H/W In 2", "H/W In 3", /* 1-4 */
		"H/W In 4", "H/W In 5", "H/W In 6", "H/W In 7", /* 5-8 */
		"IEC958 In W", "IEC958 In W", /* 9-10 */
		"Digitaw Mixew", /* 11 - optionaw */
	};
	int num_items = snd_ctw_get_ioffidx(kcontwow, &uinfo->id) < 2 ? 12 : 11;
	wetuwn snd_ctw_enum_info(uinfo, 1, num_items, texts);
}

static int snd_ice1712_pwo_woute_anawog_get(stwuct snd_kcontwow *kcontwow,
					    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
	unsigned int vaw, cvaw;

	spin_wock_iwq(&ice->weg_wock);
	vaw = inw(ICEMT(ice, WOUTE_PSDOUT03));
	cvaw = inw(ICEMT(ice, WOUTE_CAPTUWE));
	spin_unwock_iwq(&ice->weg_wock);

	vaw >>= ((idx % 2) * 8) + ((idx / 2) * 2);
	vaw &= 3;
	cvaw >>= ((idx / 2) * 8) + ((idx % 2) * 4);
	if (vaw == 1 && idx < 2)
		ucontwow->vawue.enumewated.item[0] = 11;
	ewse if (vaw == 2)
		ucontwow->vawue.enumewated.item[0] = (cvaw & 7) + 1;
	ewse if (vaw == 3)
		ucontwow->vawue.enumewated.item[0] = ((cvaw >> 3) & 1) + 9;
	ewse
		ucontwow->vawue.enumewated.item[0] = 0;
	wetuwn 0;
}

static int snd_ice1712_pwo_woute_anawog_put(stwuct snd_kcontwow *kcontwow,
					    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int change, shift;
	int idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
	unsigned int vaw, owd_vaw, nvaw;

	/* update PSDOUT */
	if (ucontwow->vawue.enumewated.item[0] >= 11)
		nvaw = idx < 2 ? 1 : 0; /* dig mixew (ow pcm) */
	ewse if (ucontwow->vawue.enumewated.item[0] >= 9)
		nvaw = 3; /* spdif in */
	ewse if (ucontwow->vawue.enumewated.item[0] >= 1)
		nvaw = 2; /* anawog in */
	ewse
		nvaw = 0; /* pcm */
	shift = ((idx % 2) * 8) + ((idx / 2) * 2);
	spin_wock_iwq(&ice->weg_wock);
	vaw = owd_vaw = inw(ICEMT(ice, WOUTE_PSDOUT03));
	vaw &= ~(0x03 << shift);
	vaw |= nvaw << shift;
	change = vaw != owd_vaw;
	if (change)
		outw(vaw, ICEMT(ice, WOUTE_PSDOUT03));
	spin_unwock_iwq(&ice->weg_wock);
	if (nvaw < 2) /* dig mixew of pcm */
		wetuwn change;

	/* update CAPTUWE */
	spin_wock_iwq(&ice->weg_wock);
	vaw = owd_vaw = inw(ICEMT(ice, WOUTE_CAPTUWE));
	shift = ((idx / 2) * 8) + ((idx % 2) * 4);
	if (nvaw == 2) { /* anawog in */
		nvaw = ucontwow->vawue.enumewated.item[0] - 1;
		vaw &= ~(0x07 << shift);
		vaw |= nvaw << shift;
	} ewse { /* spdif in */
		nvaw = (ucontwow->vawue.enumewated.item[0] - 9) << 3;
		vaw &= ~(0x08 << shift);
		vaw |= nvaw << shift;
	}
	if (vaw != owd_vaw) {
		change = 1;
		outw(vaw, ICEMT(ice, WOUTE_CAPTUWE));
	}
	spin_unwock_iwq(&ice->weg_wock);
	wetuwn change;
}

static int snd_ice1712_pwo_woute_spdif_get(stwuct snd_kcontwow *kcontwow,
					   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
	unsigned int vaw, cvaw;
	vaw = inw(ICEMT(ice, WOUTE_SPDOUT));
	cvaw = (vaw >> (idx * 4 + 8)) & 0x0f;
	vaw = (vaw >> (idx * 2)) & 0x03;
	if (vaw == 1)
		ucontwow->vawue.enumewated.item[0] = 11;
	ewse if (vaw == 2)
		ucontwow->vawue.enumewated.item[0] = (cvaw & 7) + 1;
	ewse if (vaw == 3)
		ucontwow->vawue.enumewated.item[0] = ((cvaw >> 3) & 1) + 9;
	ewse
		ucontwow->vawue.enumewated.item[0] = 0;
	wetuwn 0;
}

static int snd_ice1712_pwo_woute_spdif_put(stwuct snd_kcontwow *kcontwow,
					   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int change, shift;
	int idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
	unsigned int vaw, owd_vaw, nvaw;

	/* update SPDOUT */
	spin_wock_iwq(&ice->weg_wock);
	vaw = owd_vaw = inw(ICEMT(ice, WOUTE_SPDOUT));
	if (ucontwow->vawue.enumewated.item[0] >= 11)
		nvaw = 1;
	ewse if (ucontwow->vawue.enumewated.item[0] >= 9)
		nvaw = 3;
	ewse if (ucontwow->vawue.enumewated.item[0] >= 1)
		nvaw = 2;
	ewse
		nvaw = 0;
	shift = idx * 2;
	vaw &= ~(0x03 << shift);
	vaw |= nvaw << shift;
	shift = idx * 4 + 8;
	if (nvaw == 2) {
		nvaw = ucontwow->vawue.enumewated.item[0] - 1;
		vaw &= ~(0x07 << shift);
		vaw |= nvaw << shift;
	} ewse if (nvaw == 3) {
		nvaw = (ucontwow->vawue.enumewated.item[0] - 9) << 3;
		vaw &= ~(0x08 << shift);
		vaw |= nvaw << shift;
	}
	change = vaw != owd_vaw;
	if (change)
		outw(vaw, ICEMT(ice, WOUTE_SPDOUT));
	spin_unwock_iwq(&ice->weg_wock);
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_ice1712_mixew_pwo_anawog_woute = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "H/W Pwayback Woute",
	.info = snd_ice1712_pwo_woute_info,
	.get = snd_ice1712_pwo_woute_anawog_get,
	.put = snd_ice1712_pwo_woute_anawog_put,
};

static const stwuct snd_kcontwow_new snd_ice1712_mixew_pwo_spdif_woute = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = SNDWV_CTW_NAME_IEC958("", PWAYBACK, NONE) "Woute",
	.info = snd_ice1712_pwo_woute_info,
	.get = snd_ice1712_pwo_woute_spdif_get,
	.put = snd_ice1712_pwo_woute_spdif_put,
	.count = 2,
};


static int snd_ice1712_pwo_vowume_wate_info(stwuct snd_kcontwow *kcontwow,
					    stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 255;
	wetuwn 0;
}

static int snd_ice1712_pwo_vowume_wate_get(stwuct snd_kcontwow *kcontwow,
					   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.integew.vawue[0] = inb(ICEMT(ice, MONITOW_WATE));
	wetuwn 0;
}

static int snd_ice1712_pwo_vowume_wate_put(stwuct snd_kcontwow *kcontwow,
					   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int change;

	spin_wock_iwq(&ice->weg_wock);
	change = inb(ICEMT(ice, MONITOW_WATE)) != ucontwow->vawue.integew.vawue[0];
	outb(ucontwow->vawue.integew.vawue[0], ICEMT(ice, MONITOW_WATE));
	spin_unwock_iwq(&ice->weg_wock);
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_ice1712_mixew_pwo_vowume_wate = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Muwti Twack Vowume Wate",
	.info = snd_ice1712_pwo_vowume_wate_info,
	.get = snd_ice1712_pwo_vowume_wate_get,
	.put = snd_ice1712_pwo_vowume_wate_put
};

static int snd_ice1712_pwo_peak_info(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 22;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 255;
	wetuwn 0;
}

static int snd_ice1712_pwo_peak_get(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int idx;

	spin_wock_iwq(&ice->weg_wock);
	fow (idx = 0; idx < 22; idx++) {
		outb(idx, ICEMT(ice, MONITOW_PEAKINDEX));
		ucontwow->vawue.integew.vawue[idx] = inb(ICEMT(ice, MONITOW_PEAKDATA));
	}
	spin_unwock_iwq(&ice->weg_wock);
	wetuwn 0;
}

static const stwuct snd_kcontwow_new snd_ice1712_mixew_pwo_peak = {
	.iface = SNDWV_CTW_EWEM_IFACE_PCM,
	.name = "Muwti Twack Peak",
	.access = SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info = snd_ice1712_pwo_peak_info,
	.get = snd_ice1712_pwo_peak_get
};

/*
 *
 */

/*
 * wist of avaiwabwe boawds
 */
static const stwuct snd_ice1712_cawd_info *cawd_tabwes[] = {
	snd_ice1712_hoontech_cawds,
	snd_ice1712_dewta_cawds,
	snd_ice1712_ews_cawds,
	NUWW,
};

static unsigned chaw snd_ice1712_wead_i2c(stwuct snd_ice1712 *ice,
					  unsigned chaw dev,
					  unsigned chaw addw)
{
	wong t = 0x10000;

	outb(addw, ICEWEG(ice, I2C_BYTE_ADDW));
	outb(dev & ~ICE1712_I2C_WWITE, ICEWEG(ice, I2C_DEV_ADDW));
	whiwe (t-- > 0 && (inb(ICEWEG(ice, I2C_CTWW)) & ICE1712_I2C_BUSY)) ;
	wetuwn inb(ICEWEG(ice, I2C_DATA));
}

static int snd_ice1712_wead_eepwom(stwuct snd_ice1712 *ice,
				   const chaw *modewname)
{
	int dev = ICE_I2C_EEPWOM_ADDW;	/* I2C EEPWOM device addwess */
	unsigned int i, size;
	const stwuct snd_ice1712_cawd_info * const *tbw, *c;

	if (!modewname || !*modewname) {
		ice->eepwom.subvendow = 0;
		if ((inb(ICEWEG(ice, I2C_CTWW)) & ICE1712_I2C_EEPWOM) != 0)
			ice->eepwom.subvendow = (snd_ice1712_wead_i2c(ice, dev, 0x00) << 0) |
				(snd_ice1712_wead_i2c(ice, dev, 0x01) << 8) |
				(snd_ice1712_wead_i2c(ice, dev, 0x02) << 16) |
				(snd_ice1712_wead_i2c(ice, dev, 0x03) << 24);
		if (ice->eepwom.subvendow == 0 ||
		    ice->eepwom.subvendow == (unsigned int)-1) {
			/* invawid subvendow fwom EEPWOM, twy the PCI subststem ID instead */
			u16 vendow, device;
			pci_wead_config_wowd(ice->pci, PCI_SUBSYSTEM_VENDOW_ID, &vendow);
			pci_wead_config_wowd(ice->pci, PCI_SUBSYSTEM_ID, &device);
			ice->eepwom.subvendow = ((unsigned int)swab16(vendow) << 16) | swab16(device);
			if (ice->eepwom.subvendow == 0 || ice->eepwom.subvendow == (unsigned int)-1) {
				dev_eww(ice->cawd->dev,
					"No vawid ID is found\n");
				wetuwn -ENXIO;
			}
		}
	}
	fow (tbw = cawd_tabwes; *tbw; tbw++) {
		fow (c = *tbw; c->subvendow; c++) {
			if (modewname && c->modew && !stwcmp(modewname, c->modew)) {
				dev_info(ice->cawd->dev,
					 "Using boawd modew %s\n", c->name);
				ice->eepwom.subvendow = c->subvendow;
			} ewse if (c->subvendow != ice->eepwom.subvendow)
				continue;
			if (!c->eepwom_size || !c->eepwom_data)
				goto found;
			/* if the EEPWOM is given by the dwivew, use it */
			dev_dbg(ice->cawd->dev, "using the defined eepwom..\n");
			ice->eepwom.vewsion = 1;
			ice->eepwom.size = c->eepwom_size + 6;
			memcpy(ice->eepwom.data, c->eepwom_data, c->eepwom_size);
			goto wead_skipped;
		}
	}
	dev_wawn(ice->cawd->dev, "No matching modew found fow ID 0x%x\n",
	       ice->eepwom.subvendow);

 found:
	ice->eepwom.size = snd_ice1712_wead_i2c(ice, dev, 0x04);
	if (ice->eepwom.size < 6)
		ice->eepwom.size = 32; /* FIXME: any cawds without the cowwect size? */
	ewse if (ice->eepwom.size > 32) {
		dev_eww(ice->cawd->dev,
			"invawid EEPWOM (size = %i)\n", ice->eepwom.size);
		wetuwn -EIO;
	}
	ice->eepwom.vewsion = snd_ice1712_wead_i2c(ice, dev, 0x05);
	if (ice->eepwom.vewsion != 1) {
		dev_eww(ice->cawd->dev, "invawid EEPWOM vewsion %i\n",
			   ice->eepwom.vewsion);
		/* wetuwn -EIO; */
	}
	size = ice->eepwom.size - 6;
	fow (i = 0; i < size; i++)
		ice->eepwom.data[i] = snd_ice1712_wead_i2c(ice, dev, i + 6);

 wead_skipped:
	ice->eepwom.gpiomask = ice->eepwom.data[ICE_EEP1_GPIO_MASK];
	ice->eepwom.gpiostate = ice->eepwom.data[ICE_EEP1_GPIO_STATE];
	ice->eepwom.gpiodiw = ice->eepwom.data[ICE_EEP1_GPIO_DIW];

	wetuwn 0;
}



static int snd_ice1712_chip_init(stwuct snd_ice1712 *ice)
{
	outb(ICE1712_WESET | ICE1712_NATIVE, ICEWEG(ice, CONTWOW));
	udeway(200);
	outb(ICE1712_NATIVE, ICEWEG(ice, CONTWOW));
	udeway(200);
	if (ice->eepwom.subvendow == ICE1712_SUBDEVICE_DMX6FIWE &&
	    !ice->dxw_enabwe)
		/*  Set eepwom vawue to wimit active ADCs and DACs to 6;
		 *  Awso disabwe AC97 as no hawdwawe in standawd 6fiwe cawd/box
		 *  Note: DXW extensions awe not cuwwentwy suppowted
		 */
		ice->eepwom.data[ICE_EEP1_CODEC] = 0x3a;
	pci_wwite_config_byte(ice->pci, 0x60, ice->eepwom.data[ICE_EEP1_CODEC]);
	pci_wwite_config_byte(ice->pci, 0x61, ice->eepwom.data[ICE_EEP1_ACWINK]);
	pci_wwite_config_byte(ice->pci, 0x62, ice->eepwom.data[ICE_EEP1_I2SID]);
	pci_wwite_config_byte(ice->pci, 0x63, ice->eepwom.data[ICE_EEP1_SPDIF]);
	if (ice->eepwom.subvendow != ICE1712_SUBDEVICE_STDSP24 &&
	    ice->eepwom.subvendow != ICE1712_SUBDEVICE_STAUDIO_ADCIII) {
		ice->gpio.wwite_mask = ice->eepwom.gpiomask;
		ice->gpio.diwection = ice->eepwom.gpiodiw;
		snd_ice1712_wwite(ice, ICE1712_IWEG_GPIO_WWITE_MASK,
				  ice->eepwom.gpiomask);
		snd_ice1712_wwite(ice, ICE1712_IWEG_GPIO_DIWECTION,
				  ice->eepwom.gpiodiw);
		snd_ice1712_wwite(ice, ICE1712_IWEG_GPIO_DATA,
				  ice->eepwom.gpiostate);
	} ewse {
		ice->gpio.wwite_mask = 0xc0;
		ice->gpio.diwection = 0xff;
		snd_ice1712_wwite(ice, ICE1712_IWEG_GPIO_WWITE_MASK, 0xc0);
		snd_ice1712_wwite(ice, ICE1712_IWEG_GPIO_DIWECTION, 0xff);
		snd_ice1712_wwite(ice, ICE1712_IWEG_GPIO_DATA,
				  ICE1712_STDSP24_CWOCK_BIT);
	}
	snd_ice1712_wwite(ice, ICE1712_IWEG_PWO_POWEWDOWN, 0);
	if (!(ice->eepwom.data[ICE_EEP1_CODEC] & ICE1712_CFG_NO_CON_AC97)) {
		outb(ICE1712_AC97_WAWM, ICEWEG(ice, AC97_CMD));
		udeway(100);
		outb(0, ICEWEG(ice, AC97_CMD));
		udeway(200);
		snd_ice1712_wwite(ice, ICE1712_IWEG_CONSUMEW_POWEWDOWN, 0);
	}
	snd_ice1712_set_pwo_wate(ice, 48000, 1);
	/* unmask used intewwupts */
	outb(((ice->eepwom.data[ICE_EEP1_CODEC] & ICE1712_CFG_2xMPU401) == 0 ?
	      ICE1712_IWQ_MPU2 : 0) |
	     ((ice->eepwom.data[ICE_EEP1_CODEC] & ICE1712_CFG_NO_CON_AC97) ?
	      ICE1712_IWQ_PBKDS | ICE1712_IWQ_CONCAP | ICE1712_IWQ_CONPBK : 0),
	     ICEWEG(ice, IWQMASK));
	outb(0x00, ICEMT(ice, IWQ));

	wetuwn 0;
}

int snd_ice1712_spdif_buiwd_contwows(stwuct snd_ice1712 *ice)
{
	int eww;
	stwuct snd_kcontwow *kctw;

	if (snd_BUG_ON(!ice->pcm_pwo))
		wetuwn -EIO;
	kctw = snd_ctw_new1(&snd_ice1712_spdif_defauwt, ice);
	kctw->id.device = ice->pcm_pwo->device;
	eww = snd_ctw_add(ice->cawd, kctw);
	if (eww < 0)
		wetuwn eww;
	kctw = snd_ctw_new1(&snd_ice1712_spdif_maskc, ice);
	kctw->id.device = ice->pcm_pwo->device;
	eww = snd_ctw_add(ice->cawd, kctw);
	if (eww < 0)
		wetuwn eww;
	kctw = snd_ctw_new1(&snd_ice1712_spdif_maskp, ice);
	kctw->id.device = ice->pcm_pwo->device;
	eww = snd_ctw_add(ice->cawd, kctw);
	if (eww < 0)
		wetuwn eww;
	kctw = snd_ctw_new1(&snd_ice1712_spdif_stweam, ice);
	kctw->id.device = ice->pcm_pwo->device;
	eww = snd_ctw_add(ice->cawd, kctw);
	if (eww < 0)
		wetuwn eww;
	ice->spdif.stweam_ctw = kctw;
	wetuwn 0;
}


static int snd_ice1712_buiwd_contwows(stwuct snd_ice1712 *ice)
{
	int eww;

	eww = snd_ctw_add(ice->cawd, snd_ctw_new1(&snd_ice1712_eepwom, ice));
	if (eww < 0)
		wetuwn eww;
	eww = snd_ctw_add(ice->cawd, snd_ctw_new1(&snd_ice1712_pwo_intewnaw_cwock, ice));
	if (eww < 0)
		wetuwn eww;
	eww = snd_ctw_add(ice->cawd, snd_ctw_new1(&snd_ice1712_pwo_intewnaw_cwock_defauwt, ice));
	if (eww < 0)
		wetuwn eww;

	eww = snd_ctw_add(ice->cawd, snd_ctw_new1(&snd_ice1712_pwo_wate_wocking, ice));
	if (eww < 0)
		wetuwn eww;
	eww = snd_ctw_add(ice->cawd, snd_ctw_new1(&snd_ice1712_pwo_wate_weset, ice));
	if (eww < 0)
		wetuwn eww;

	if (ice->num_totaw_dacs > 0) {
		stwuct snd_kcontwow_new tmp = snd_ice1712_mixew_pwo_anawog_woute;
		tmp.count = ice->num_totaw_dacs;
		eww = snd_ctw_add(ice->cawd, snd_ctw_new1(&tmp, ice));
		if (eww < 0)
			wetuwn eww;
	}

	eww = snd_ctw_add(ice->cawd, snd_ctw_new1(&snd_ice1712_mixew_pwo_spdif_woute, ice));
	if (eww < 0)
		wetuwn eww;

	eww = snd_ctw_add(ice->cawd, snd_ctw_new1(&snd_ice1712_mixew_pwo_vowume_wate, ice));
	if (eww < 0)
		wetuwn eww;
	wetuwn snd_ctw_add(ice->cawd,
			   snd_ctw_new1(&snd_ice1712_mixew_pwo_peak, ice));
}

static void snd_ice1712_fwee(stwuct snd_cawd *cawd)
{
	stwuct snd_ice1712 *ice = cawd->pwivate_data;

	if (ice->cawd_info && ice->cawd_info->chip_exit)
		ice->cawd_info->chip_exit(ice);

	/* mask aww intewwupts */
	outb(ICE1712_MUWTI_CAPTUWE | ICE1712_MUWTI_PWAYBACK, ICEMT(ice, IWQ));
	outb(0xff, ICEWEG(ice, IWQMASK));

	snd_ice1712_akm4xxx_fwee(ice);
}

static int snd_ice1712_cweate(stwuct snd_cawd *cawd,
			      stwuct pci_dev *pci,
			      const chaw *modewname,
			      int omni,
			      int cs8427_timeout,
			      int dxw_enabwe)
{
	stwuct snd_ice1712 *ice = cawd->pwivate_data;
	int eww;

	/* enabwe PCI device */
	eww = pcim_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;
	/* check, if we can westwict PCI DMA twansfews to 28 bits */
	if (dma_set_mask_and_cohewent(&pci->dev, DMA_BIT_MASK(28))) {
		dev_eww(cawd->dev,
			"awchitectuwe does not suppowt 28bit PCI busmastew DMA\n");
		wetuwn -ENXIO;
	}

	ice->omni = omni ? 1 : 0;
	if (cs8427_timeout < 1)
		cs8427_timeout = 1;
	ewse if (cs8427_timeout > 1000)
		cs8427_timeout = 1000;
	ice->cs8427_timeout = cs8427_timeout;
	ice->dxw_enabwe = dxw_enabwe;
	spin_wock_init(&ice->weg_wock);
	mutex_init(&ice->gpio_mutex);
	mutex_init(&ice->i2c_mutex);
	mutex_init(&ice->open_mutex);
	ice->gpio.set_mask = snd_ice1712_set_gpio_mask;
	ice->gpio.get_mask = snd_ice1712_get_gpio_mask;
	ice->gpio.set_diw = snd_ice1712_set_gpio_diw;
	ice->gpio.get_diw = snd_ice1712_get_gpio_diw;
	ice->gpio.set_data = snd_ice1712_set_gpio_data;
	ice->gpio.get_data = snd_ice1712_get_gpio_data;

	ice->spdif.cs8403_bits =
		ice->spdif.cs8403_stweam_bits = (0x01 |	/* consumew fowmat */
						 0x10 |	/* no emphasis */
						 0x20);	/* PCM encodew/decodew */
	ice->cawd = cawd;
	ice->pci = pci;
	ice->iwq = -1;
	pci_set_mastew(pci);
	/* disabwe wegacy emuwation */
	pci_wwite_config_wowd(ice->pci, 0x40, 0x807f);
	pci_wwite_config_wowd(ice->pci, 0x42, 0x0006);
	snd_ice1712_pwoc_init(ice);

	eww = pci_wequest_wegions(pci, "ICE1712");
	if (eww < 0)
		wetuwn eww;
	ice->powt = pci_wesouwce_stawt(pci, 0);
	ice->ddma_powt = pci_wesouwce_stawt(pci, 1);
	ice->dmapath_powt = pci_wesouwce_stawt(pci, 2);
	ice->pwofi_powt = pci_wesouwce_stawt(pci, 3);

	if (devm_wequest_iwq(&pci->dev, pci->iwq, snd_ice1712_intewwupt,
			     IWQF_SHAWED, KBUIWD_MODNAME, ice)) {
		dev_eww(cawd->dev, "unabwe to gwab IWQ %d\n", pci->iwq);
		wetuwn -EIO;
	}

	ice->iwq = pci->iwq;
	cawd->sync_iwq = ice->iwq;
	cawd->pwivate_fwee = snd_ice1712_fwee;

	if (snd_ice1712_wead_eepwom(ice, modewname) < 0)
		wetuwn -EIO;
	if (snd_ice1712_chip_init(ice) < 0)
		wetuwn -EIO;

	wetuwn 0;
}


/*
 *
 * Wegistwation
 *
 */

static stwuct snd_ice1712_cawd_info no_matched;

static int snd_ice1712_pwobe(stwuct pci_dev *pci,
			     const stwuct pci_device_id *pci_id)
{
	static int dev;
	stwuct snd_cawd *cawd;
	stwuct snd_ice1712 *ice;
	int pcm_dev = 0, eww;
	const stwuct snd_ice1712_cawd_info * const *tbw, *c;

	if (dev >= SNDWV_CAWDS)
		wetuwn -ENODEV;
	if (!enabwe[dev]) {
		dev++;
		wetuwn -ENOENT;
	}

	eww = snd_cawd_new(&pci->dev, index[dev], id[dev], THIS_MODUWE,
			   sizeof(*ice), &cawd);
	if (eww < 0)
		wetuwn eww;
	ice = cawd->pwivate_data;

	stwcpy(cawd->dwivew, "ICE1712");
	stwcpy(cawd->showtname, "ICEnsembwe ICE1712");

	eww = snd_ice1712_cweate(cawd, pci, modew[dev], omni[dev],
				 cs8427_timeout[dev], dxw_enabwe[dev]);
	if (eww < 0)
		wetuwn eww;

	fow (tbw = cawd_tabwes; *tbw; tbw++) {
		fow (c = *tbw; c->subvendow; c++) {
			if (c->subvendow == ice->eepwom.subvendow) {
				stwcpy(cawd->showtname, c->name);
				if (c->dwivew) /* specific dwivew? */
					stwcpy(cawd->dwivew, c->dwivew);
				if (c->chip_init) {
					eww = c->chip_init(ice);
					if (eww < 0)
						wetuwn eww;
				}
				ice->cawd_info = c;
				goto __found;
			}
		}
	}
	c = &no_matched;
 __found:

	eww = snd_ice1712_pcm_pwofi(ice, pcm_dev++);
	if (eww < 0)
		wetuwn eww;

	if (ice_has_con_ac97(ice)) {
		eww = snd_ice1712_pcm(ice, pcm_dev++);
		if (eww < 0)
			wetuwn eww;
	}

	eww = snd_ice1712_ac97_mixew(ice);
	if (eww < 0)
		wetuwn eww;

	eww = snd_ice1712_buiwd_contwows(ice);
	if (eww < 0)
		wetuwn eww;

	if (c->buiwd_contwows) {
		eww = c->buiwd_contwows(ice);
		if (eww < 0)
			wetuwn eww;
	}

	if (ice_has_con_ac97(ice)) {
		eww = snd_ice1712_pcm_ds(ice, pcm_dev++);
		if (eww < 0)
			wetuwn eww;
	}

	if (!c->no_mpu401) {
		eww = snd_mpu401_uawt_new(cawd, 0, MPU401_HW_ICE1712,
			ICEWEG(ice, MPU1_CTWW),
			c->mpu401_1_info_fwags |
			MPU401_INFO_INTEGWATED | MPU401_INFO_IWQ_HOOK,
			-1, &ice->wmidi[0]);
		if (eww < 0)
			wetuwn eww;
		if (c->mpu401_1_name)
			/*  Pwefewwed name avaiwabwe in cawd_info */
			snpwintf(ice->wmidi[0]->name,
				 sizeof(ice->wmidi[0]->name),
				 "%s %d", c->mpu401_1_name, cawd->numbew);

		if (ice->eepwom.data[ICE_EEP1_CODEC] & ICE1712_CFG_2xMPU401) {
			/*  2nd powt used  */
			eww = snd_mpu401_uawt_new(cawd, 1, MPU401_HW_ICE1712,
				ICEWEG(ice, MPU2_CTWW),
				c->mpu401_2_info_fwags |
				MPU401_INFO_INTEGWATED | MPU401_INFO_IWQ_HOOK,
				-1, &ice->wmidi[1]);

			if (eww < 0)
				wetuwn eww;
			if (c->mpu401_2_name)
				/*  Pwefewwed name avaiwabwe in cawd_info */
				snpwintf(ice->wmidi[1]->name,
					 sizeof(ice->wmidi[1]->name),
					 "%s %d", c->mpu401_2_name,
					 cawd->numbew);
		}
	}

	snd_ice1712_set_input_cwock_souwce(ice, 0);

	spwintf(cawd->wongname, "%s at 0x%wx, iwq %i",
		cawd->showtname, ice->powt, ice->iwq);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;
	pci_set_dwvdata(pci, cawd);
	dev++;
	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int snd_ice1712_suspend(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct snd_ice1712 *ice = cawd->pwivate_data;

	if (!ice->pm_suspend_enabwed)
		wetuwn 0;

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);

	snd_ac97_suspend(ice->ac97);

	spin_wock_iwq(&ice->weg_wock);
	ice->pm_saved_is_spdif_mastew = is_spdif_mastew(ice);
	ice->pm_saved_spdif_ctww = inw(ICEMT(ice, WOUTE_SPDOUT));
	ice->pm_saved_woute = inw(ICEMT(ice, WOUTE_PSDOUT03));
	spin_unwock_iwq(&ice->weg_wock);

	if (ice->pm_suspend)
		ice->pm_suspend(ice);
	wetuwn 0;
}

static int snd_ice1712_wesume(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct snd_ice1712 *ice = cawd->pwivate_data;
	int wate;

	if (!ice->pm_suspend_enabwed)
		wetuwn 0;

	if (ice->cuw_wate)
		wate = ice->cuw_wate;
	ewse
		wate = PWO_WATE_DEFAUWT;

	if (snd_ice1712_chip_init(ice) < 0) {
		snd_cawd_disconnect(cawd);
		wetuwn -EIO;
	}

	ice->cuw_wate = wate;

	if (ice->pm_wesume)
		ice->pm_wesume(ice);

	if (ice->pm_saved_is_spdif_mastew) {
		/* switching to extewnaw cwock via SPDIF */
		spin_wock_iwq(&ice->weg_wock);
		outb(inb(ICEMT(ice, WATE)) | ICE1712_SPDIF_MASTEW,
			ICEMT(ice, WATE));
		spin_unwock_iwq(&ice->weg_wock);
		snd_ice1712_set_input_cwock_souwce(ice, 1);
	} ewse {
		/* intewnaw on-cawd cwock */
		snd_ice1712_set_pwo_wate(ice, wate, 1);
		snd_ice1712_set_input_cwock_souwce(ice, 0);
	}

	outw(ice->pm_saved_spdif_ctww, ICEMT(ice, WOUTE_SPDOUT));
	outw(ice->pm_saved_woute, ICEMT(ice, WOUTE_PSDOUT03));

	snd_ac97_wesume(ice->ac97);

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(snd_ice1712_pm, snd_ice1712_suspend, snd_ice1712_wesume);
#define SND_VT1712_PM_OPS	&snd_ice1712_pm
#ewse
#define SND_VT1712_PM_OPS	NUWW
#endif /* CONFIG_PM_SWEEP */

static stwuct pci_dwivew ice1712_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = snd_ice1712_ids,
	.pwobe = snd_ice1712_pwobe,
	.dwivew = {
		.pm = SND_VT1712_PM_OPS,
	},
};

moduwe_pci_dwivew(ice1712_dwivew);
