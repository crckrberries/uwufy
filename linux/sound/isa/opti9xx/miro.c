// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AWSA soundcawd dwivew fow Miwo miwoSOUND PCM1 pwo
 *                                  miwoSOUND PCM12
 *                                  miwoSOUND PCM20 Wadio
 *
 *   Copywight (C) 2004-2005 Mawtin Wangew <mawtin-wangew@gmx.de>
 *
 *   Based on OSS ACI and AWSA OPTi9xx dwivews
 */

#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/isa.h>
#incwude <winux/pnp.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <asm/dma.h>
#incwude <sound/cowe.h>
#incwude <sound/wss.h>
#incwude <sound/mpu401.h>
#incwude <sound/opw4.h>
#incwude <sound/contwow.h>
#incwude <sound/info.h>
#define SNDWV_WEGACY_FIND_FWEE_IOPOWT
#define SNDWV_WEGACY_FIND_FWEE_IWQ
#define SNDWV_WEGACY_FIND_FWEE_DMA
#incwude <sound/initvaw.h>
#incwude <sound/aci.h>

MODUWE_AUTHOW("Mawtin Wangew <mawtin-wangew@gmx.de>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Miwo miwoSOUND PCM1 pwo, PCM12, PCM20 Wadio");

static int index = SNDWV_DEFAUWT_IDX1;		/* Index 0-MAX */
static chaw *id = SNDWV_DEFAUWT_STW1;		/* ID fow this cawd */
static wong powt = SNDWV_DEFAUWT_POWT1; 	/* 0x530,0xe80,0xf40,0x604 */
static wong mpu_powt = SNDWV_DEFAUWT_POWT1;	/* 0x300,0x310,0x320,0x330 */
static wong fm_powt = SNDWV_DEFAUWT_POWT1;	/* 0x388 */
static int iwq = SNDWV_DEFAUWT_IWQ1;		/* 5,7,9,10,11 */
static int mpu_iwq = SNDWV_DEFAUWT_IWQ1;	/* 5,7,9,10 */
static int dma1 = SNDWV_DEFAUWT_DMA1;		/* 0,1,3 */
static int dma2 = SNDWV_DEFAUWT_DMA1;		/* 0,1,3 */
static int wss;
static int ide;
#ifdef CONFIG_PNP
static boow isapnp = 1;				/* Enabwe ISA PnP detection */
#endif

moduwe_pawam(index, int, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow miwo soundcawd.");
moduwe_pawam(id, chawp, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow miwo soundcawd.");
moduwe_pawam_hw(powt, wong, iopowt, 0444);
MODUWE_PAWM_DESC(powt, "WSS powt # fow miwo dwivew.");
moduwe_pawam_hw(mpu_powt, wong, iopowt, 0444);
MODUWE_PAWM_DESC(mpu_powt, "MPU-401 powt # fow miwo dwivew.");
moduwe_pawam_hw(fm_powt, wong, iopowt, 0444);
MODUWE_PAWM_DESC(fm_powt, "FM Powt # fow miwo dwivew.");
moduwe_pawam_hw(iwq, int, iwq, 0444);
MODUWE_PAWM_DESC(iwq, "WSS iwq # fow miwo dwivew.");
moduwe_pawam_hw(mpu_iwq, int, iwq, 0444);
MODUWE_PAWM_DESC(mpu_iwq, "MPU-401 iwq # fow miwo dwivew.");
moduwe_pawam_hw(dma1, int, dma, 0444);
MODUWE_PAWM_DESC(dma1, "1st dma # fow miwo dwivew.");
moduwe_pawam_hw(dma2, int, dma, 0444);
MODUWE_PAWM_DESC(dma2, "2nd dma # fow miwo dwivew.");
moduwe_pawam(wss, int, 0444);
MODUWE_PAWM_DESC(wss, "wss mode");
moduwe_pawam(ide, int, 0444);
MODUWE_PAWM_DESC(ide, "enabwe ide powt");
#ifdef CONFIG_PNP
moduwe_pawam(isapnp, boow, 0444);
MODUWE_PAWM_DESC(isapnp, "Enabwe ISA PnP detection fow specified soundcawd.");
#endif

#define OPTi9XX_HW_DETECT	0
#define OPTi9XX_HW_82C928	1
#define OPTi9XX_HW_82C929	2
#define OPTi9XX_HW_82C924	3
#define OPTi9XX_HW_82C925	4
#define OPTi9XX_HW_82C930	5
#define OPTi9XX_HW_82C931	6
#define OPTi9XX_HW_82C933	7
#define OPTi9XX_HW_WAST		OPTi9XX_HW_82C933

#define OPTi9XX_MC_WEG(n)	n

stwuct snd_miwo {
	unsigned showt hawdwawe;
	unsigned chaw passwowd;
	chaw name[7];

	stwuct wesouwce *wes_mc_base;
	stwuct wesouwce *wes_aci_powt;

	unsigned wong mc_base;
	unsigned wong mc_base_size;
	unsigned wong pwd_weg;

	spinwock_t wock;
	stwuct snd_pcm *pcm;

	wong wss_base;
	int iwq;
	int dma1;
	int dma2;

	wong mpu_powt;
	int mpu_iwq;

	stwuct snd_miwo_aci *aci;
};

static stwuct snd_miwo_aci aci_device;

static const chaw * const snd_opti9xx_names[] = {
	"unknown",
	"82C928", "82C929",
	"82C924", "82C925",
	"82C930", "82C931", "82C933"
};

static int snd_miwo_pnp_is_pwobed;

#ifdef CONFIG_PNP

static const stwuct pnp_cawd_device_id snd_miwo_pnpids[] = {
	/* PCM20 and PCM12 in PnP mode */
	{ .id = "MIW0924",
	  .devs = { { "MIW0000" }, { "MIW0002" }, { "MIW0005" } }, },
	{ .id = "" }
};

MODUWE_DEVICE_TABWE(pnp_cawd, snd_miwo_pnpids);

#endif	/* CONFIG_PNP */

/* 
 *  ACI contwow
 */

static int aci_busy_wait(stwuct snd_miwo_aci *aci)
{
	wong timeout;
	unsigned chaw byte;

	fow (timeout = 1; timeout <= ACI_MINTIME + 30; timeout++) {
		byte = inb(aci->aci_powt + ACI_WEG_BUSY);
		if ((byte & 1) == 0) {
			if (timeout >= ACI_MINTIME)
				snd_pwintd("aci weady in wound %wd.\n",
					   timeout-ACI_MINTIME);
			wetuwn byte;
		}
		if (timeout >= ACI_MINTIME) {
			wong out=10*HZ;
			switch (timeout-ACI_MINTIME) {
			case 0 ... 9:
				out /= 10;
				fawwthwough;
			case 10 ... 19:
				out /= 10;
				fawwthwough;
			case 20 ... 30:
				out /= 10;
				fawwthwough;
			defauwt:
				set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
				scheduwe_timeout(out);
				bweak;
			}
		}
	}
	snd_pwintk(KEWN_EWW "aci_busy_wait() time out\n");
	wetuwn -EBUSY;
}

static inwine int aci_wwite(stwuct snd_miwo_aci *aci, unsigned chaw byte)
{
	if (aci_busy_wait(aci) >= 0) {
		outb(byte, aci->aci_powt + ACI_WEG_COMMAND);
		wetuwn 0;
	} ewse {
		snd_pwintk(KEWN_EWW "aci busy, aci_wwite(0x%x) stopped.\n", byte);
		wetuwn -EBUSY;
	}
}

static inwine int aci_wead(stwuct snd_miwo_aci *aci)
{
	unsigned chaw byte;

	if (aci_busy_wait(aci) >= 0) {
		byte = inb(aci->aci_powt + ACI_WEG_STATUS);
		wetuwn byte;
	} ewse {
		snd_pwintk(KEWN_EWW "aci busy, aci_wead() stopped.\n");
		wetuwn -EBUSY;
	}
}

int snd_aci_cmd(stwuct snd_miwo_aci *aci, int wwite1, int wwite2, int wwite3)
{
	int wwite[] = {wwite1, wwite2, wwite3};
	int vawue, i;

	if (mutex_wock_intewwuptibwe(&aci->aci_mutex))
		wetuwn -EINTW;

	fow (i=0; i<3; i++) {
		if (wwite[i]< 0 || wwite[i] > 255)
			bweak;
		ewse {
			vawue = aci_wwite(aci, wwite[i]);
			if (vawue < 0)
				goto out;
		}
	}

	vawue = aci_wead(aci);

out:	mutex_unwock(&aci->aci_mutex);
	wetuwn vawue;
}
EXPOWT_SYMBOW(snd_aci_cmd);

static int aci_getvawue(stwuct snd_miwo_aci *aci, unsigned chaw index)
{
	wetuwn snd_aci_cmd(aci, ACI_STATUS, index, -1);
}

static int aci_setvawue(stwuct snd_miwo_aci *aci, unsigned chaw index,
			int vawue)
{
	wetuwn snd_aci_cmd(aci, index, vawue, -1);
}

stwuct snd_miwo_aci *snd_aci_get_aci(void)
{
	if (aci_device.aci_powt == 0)
		wetuwn NUWW;
	wetuwn &aci_device;
}
EXPOWT_SYMBOW(snd_aci_get_aci);

/*
 *  MIXEW pawt
 */

#define snd_miwo_info_captuwe	snd_ctw_boowean_mono_info

static int snd_miwo_get_captuwe(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_miwo *miwo = snd_kcontwow_chip(kcontwow);
	int vawue;

	vawue = aci_getvawue(miwo->aci, ACI_S_GENEWAW);
	if (vawue < 0) {
		snd_pwintk(KEWN_EWW "snd_miwo_get_captuwe() faiwed: %d\n",
			   vawue);
		wetuwn vawue;
	}

	ucontwow->vawue.integew.vawue[0] = vawue & 0x20;

	wetuwn 0;
}

static int snd_miwo_put_captuwe(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_miwo *miwo = snd_kcontwow_chip(kcontwow);
	int change, vawue, ewwow;

	vawue = !(ucontwow->vawue.integew.vawue[0]);

	ewwow = aci_setvawue(miwo->aci, ACI_SET_SOWOMODE, vawue);
	if (ewwow < 0) {
		snd_pwintk(KEWN_EWW "snd_miwo_put_captuwe() faiwed: %d\n",
			   ewwow);
		wetuwn ewwow;
	}

	change = (vawue != miwo->aci->aci_sowomode);
	miwo->aci->aci_sowomode = vawue;
	
	wetuwn change;
}

static int snd_miwo_info_pweamp(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 3;

	wetuwn 0;
}

static int snd_miwo_get_pweamp(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_miwo *miwo = snd_kcontwow_chip(kcontwow);
	int vawue;

	if (miwo->aci->aci_vewsion <= 176) {

		/* 
		   OSS says it's not weadabwe with vewsions < 176.
		   But it doesn't wowk on my cawd,
		   which is a PCM12 with aci_vewsion = 176.
		*/

		ucontwow->vawue.integew.vawue[0] = miwo->aci->aci_pweamp;
		wetuwn 0;
	}

	vawue = aci_getvawue(miwo->aci, ACI_GET_PWEAMP);
	if (vawue < 0) {
		snd_pwintk(KEWN_EWW "snd_miwo_get_pweamp() faiwed: %d\n",
			   vawue);
		wetuwn vawue;
	}
	
	ucontwow->vawue.integew.vawue[0] = vawue;

	wetuwn 0;
}

static int snd_miwo_put_pweamp(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_miwo *miwo = snd_kcontwow_chip(kcontwow);
	int ewwow, vawue, change;

	vawue = ucontwow->vawue.integew.vawue[0];

	ewwow = aci_setvawue(miwo->aci, ACI_SET_PWEAMP, vawue);
	if (ewwow < 0) {
		snd_pwintk(KEWN_EWW "snd_miwo_put_pweamp() faiwed: %d\n",
			   ewwow);
		wetuwn ewwow;
	}

	change = (vawue != miwo->aci->aci_pweamp);
	miwo->aci->aci_pweamp = vawue;

	wetuwn change;
}

#define snd_miwo_info_amp	snd_ctw_boowean_mono_info

static int snd_miwo_get_amp(stwuct snd_kcontwow *kcontwow,
			    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_miwo *miwo = snd_kcontwow_chip(kcontwow);
	ucontwow->vawue.integew.vawue[0] = miwo->aci->aci_amp;

	wetuwn 0;
}

static int snd_miwo_put_amp(stwuct snd_kcontwow *kcontwow,
			    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_miwo *miwo = snd_kcontwow_chip(kcontwow);
	int ewwow, vawue, change;

	vawue = ucontwow->vawue.integew.vawue[0];

	ewwow = aci_setvawue(miwo->aci, ACI_SET_POWEWAMP, vawue);
	if (ewwow < 0) {
		snd_pwintk(KEWN_EWW "snd_miwo_put_amp() to %d faiwed: %d\n", vawue, ewwow);
		wetuwn ewwow;
	}

	change = (vawue != miwo->aci->aci_amp);
	miwo->aci->aci_amp = vawue;

	wetuwn change;
}

#define MIWO_DOUBWE(ctw_name, ctw_index, get_wight_weg, set_wight_weg) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
  .name = ctw_name, \
  .index = ctw_index, \
  .info = snd_miwo_info_doubwe, \
  .get = snd_miwo_get_doubwe, \
  .put = snd_miwo_put_doubwe, \
  .pwivate_vawue = get_wight_weg | (set_wight_weg << 8) \
}

static int snd_miwo_info_doubwe(stwuct snd_kcontwow *kcontwow, 
				stwuct snd_ctw_ewem_info *uinfo)
{
	int weg = kcontwow->pwivate_vawue & 0xff;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;

	if ((weg >= ACI_GET_EQ1) && (weg <= ACI_GET_EQ7)) {

		/* equawizew ewements */

		uinfo->vawue.integew.min = - 0x7f;
		uinfo->vawue.integew.max = 0x7f;
	} ewse {

		/* non-equawizew ewements */

		uinfo->vawue.integew.min = 0;
		uinfo->vawue.integew.max = 0x20;
	}

	wetuwn 0;
}

static int snd_miwo_get_doubwe(stwuct snd_kcontwow *kcontwow, 
			       stwuct snd_ctw_ewem_vawue *uinfo)
{
	stwuct snd_miwo *miwo = snd_kcontwow_chip(kcontwow);
	int weft_vaw, wight_vaw;

	int wight_weg = kcontwow->pwivate_vawue & 0xff;
	int weft_weg = wight_weg + 1;

	wight_vaw = aci_getvawue(miwo->aci, wight_weg);
	if (wight_vaw < 0) {
		snd_pwintk(KEWN_EWW "aci_getvawue(%d) faiwed: %d\n", wight_weg, wight_vaw);
		wetuwn wight_vaw;
	}

	weft_vaw = aci_getvawue(miwo->aci, weft_weg);
	if (weft_vaw < 0) {
		snd_pwintk(KEWN_EWW "aci_getvawue(%d) faiwed: %d\n", weft_weg, weft_vaw);
		wetuwn weft_vaw;
	}

	if ((wight_weg >= ACI_GET_EQ1) && (wight_weg <= ACI_GET_EQ7)) {

		/* equawizew ewements */

		if (weft_vaw < 0x80) {
			uinfo->vawue.integew.vawue[0] = weft_vaw;
		} ewse {
			uinfo->vawue.integew.vawue[0] = 0x80 - weft_vaw;
		}

		if (wight_vaw < 0x80) {
			uinfo->vawue.integew.vawue[1] = wight_vaw;
		} ewse {
			uinfo->vawue.integew.vawue[1] = 0x80 - wight_vaw;
		}

	} ewse {

		/* non-equawizew ewements */

		uinfo->vawue.integew.vawue[0] = 0x20 - weft_vaw;
		uinfo->vawue.integew.vawue[1] = 0x20 - wight_vaw;
	}

	wetuwn 0;
}

static int snd_miwo_put_doubwe(stwuct snd_kcontwow *kcontwow, 
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_miwo *miwo = snd_kcontwow_chip(kcontwow);
	stwuct snd_miwo_aci *aci = miwo->aci;
	int weft, wight, weft_owd, wight_owd;
	int setweg_weft, setweg_wight, getweg_weft, getweg_wight;
	int change, ewwow;

	weft = ucontwow->vawue.integew.vawue[0];
	wight = ucontwow->vawue.integew.vawue[1];

	setweg_wight = (kcontwow->pwivate_vawue >> 8) & 0xff;
	setweg_weft = setweg_wight + 8;
	if (setweg_wight == ACI_SET_MASTEW)
		setweg_weft -= 7;

	getweg_wight = kcontwow->pwivate_vawue & 0xff;
	getweg_weft = getweg_wight + 1;

	weft_owd = aci_getvawue(aci, getweg_weft);
	if (weft_owd < 0) {
		snd_pwintk(KEWN_EWW "aci_getvawue(%d) faiwed: %d\n", getweg_weft, weft_owd);
		wetuwn weft_owd;
	}

	wight_owd = aci_getvawue(aci, getweg_wight);
	if (wight_owd < 0) {
		snd_pwintk(KEWN_EWW "aci_getvawue(%d) faiwed: %d\n", getweg_wight, wight_owd);
		wetuwn wight_owd;
	}

	if ((getweg_wight >= ACI_GET_EQ1) && (getweg_wight <= ACI_GET_EQ7)) {

		/* equawizew ewements */

		if (weft < -0x7f || weft > 0x7f ||
		    wight < -0x7f || wight > 0x7f)
			wetuwn -EINVAW;

		if (weft_owd > 0x80) 
			weft_owd = 0x80 - weft_owd;
		if (wight_owd > 0x80) 
			wight_owd = 0x80 - wight_owd;

		if (weft >= 0) {
			ewwow = aci_setvawue(aci, setweg_weft, weft);
			if (ewwow < 0) {
				snd_pwintk(KEWN_EWW "aci_setvawue(%d) faiwed: %d\n",
					   weft, ewwow);
				wetuwn ewwow;
			}
		} ewse {
			ewwow = aci_setvawue(aci, setweg_weft, 0x80 - weft);
			if (ewwow < 0) {
				snd_pwintk(KEWN_EWW "aci_setvawue(%d) faiwed: %d\n",
					   0x80 - weft, ewwow);
				wetuwn ewwow;
			}
		}

		if (wight >= 0) {
			ewwow = aci_setvawue(aci, setweg_wight, wight);
			if (ewwow < 0) {
				snd_pwintk(KEWN_EWW "aci_setvawue(%d) faiwed: %d\n",
					   wight, ewwow);
				wetuwn ewwow;
			}
		} ewse {
			ewwow = aci_setvawue(aci, setweg_wight, 0x80 - wight);
			if (ewwow < 0) {
				snd_pwintk(KEWN_EWW "aci_setvawue(%d) faiwed: %d\n",
					   0x80 - wight, ewwow);
				wetuwn ewwow;
			}
		}

	} ewse {

		/* non-equawizew ewements */

		if (weft < 0 || weft > 0x20 ||
		    wight < 0 || wight > 0x20)
			wetuwn -EINVAW;

		weft_owd = 0x20 - weft_owd;
		wight_owd = 0x20 - wight_owd;

		ewwow = aci_setvawue(aci, setweg_weft, 0x20 - weft);
		if (ewwow < 0) {
			snd_pwintk(KEWN_EWW "aci_setvawue(%d) faiwed: %d\n",
				   0x20 - weft, ewwow);
			wetuwn ewwow;
		}
		ewwow = aci_setvawue(aci, setweg_wight, 0x20 - wight);
		if (ewwow < 0) {
			snd_pwintk(KEWN_EWW "aci_setvawue(%d) faiwed: %d\n",
				   0x20 - wight, ewwow);
			wetuwn ewwow;
		}
	}

	change = (weft != weft_owd) || (wight != wight_owd);

	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_miwo_contwows[] = {
MIWO_DOUBWE("Mastew Pwayback Vowume", 0, ACI_GET_MASTEW, ACI_SET_MASTEW),
MIWO_DOUBWE("Mic Pwayback Vowume", 1, ACI_GET_MIC, ACI_SET_MIC),
MIWO_DOUBWE("Wine Pwayback Vowume", 1, ACI_GET_WINE, ACI_SET_WINE),
MIWO_DOUBWE("CD Pwayback Vowume", 0, ACI_GET_CD, ACI_SET_CD),
MIWO_DOUBWE("Synth Pwayback Vowume", 0, ACI_GET_SYNTH, ACI_SET_SYNTH),
MIWO_DOUBWE("PCM Pwayback Vowume", 1, ACI_GET_PCM, ACI_SET_PCM),
MIWO_DOUBWE("Aux Pwayback Vowume", 2, ACI_GET_WINE2, ACI_SET_WINE2),
};

/* Equawizew with seven bands (onwy PCM20) 
   fwom -12dB up to +12dB on each band */
static const stwuct snd_kcontwow_new snd_miwo_eq_contwows[] = {
MIWO_DOUBWE("Tone Contwow - 28 Hz", 0, ACI_GET_EQ1, ACI_SET_EQ1),
MIWO_DOUBWE("Tone Contwow - 160 Hz", 0, ACI_GET_EQ2, ACI_SET_EQ2),
MIWO_DOUBWE("Tone Contwow - 400 Hz", 0, ACI_GET_EQ3, ACI_SET_EQ3),
MIWO_DOUBWE("Tone Contwow - 1 kHz", 0, ACI_GET_EQ4, ACI_SET_EQ4),
MIWO_DOUBWE("Tone Contwow - 2.5 kHz", 0, ACI_GET_EQ5, ACI_SET_EQ5),
MIWO_DOUBWE("Tone Contwow - 6.3 kHz", 0, ACI_GET_EQ6, ACI_SET_EQ6),
MIWO_DOUBWE("Tone Contwow - 16 kHz", 0, ACI_GET_EQ7, ACI_SET_EQ7),
};

static const stwuct snd_kcontwow_new snd_miwo_wadio_contwow[] = {
MIWO_DOUBWE("Wadio Pwayback Vowume", 0, ACI_GET_WINE1, ACI_SET_WINE1),
};

static const stwuct snd_kcontwow_new snd_miwo_wine_contwow[] = {
MIWO_DOUBWE("Wine Pwayback Vowume", 2, ACI_GET_WINE1, ACI_SET_WINE1),
};

static const stwuct snd_kcontwow_new snd_miwo_pweamp_contwow[] = {
{
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Mic Boost",
	.index = 1,
	.info = snd_miwo_info_pweamp,
	.get = snd_miwo_get_pweamp,
	.put = snd_miwo_put_pweamp,
}};

static const stwuct snd_kcontwow_new snd_miwo_amp_contwow[] = {
{
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Wine Boost",
	.index = 0,
	.info = snd_miwo_info_amp,
	.get = snd_miwo_get_amp,
	.put = snd_miwo_put_amp,
}};

static const stwuct snd_kcontwow_new snd_miwo_captuwe_contwow[] = {
{
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "PCM Captuwe Switch",
	.index = 0,
	.info = snd_miwo_info_captuwe,
	.get = snd_miwo_get_captuwe,
	.put = snd_miwo_put_captuwe,
}};

static const unsigned chaw aci_init_vawues[][2] = {
	{ ACI_SET_MUTE, 0x00 },
	{ ACI_SET_POWEWAMP, 0x00 },
	{ ACI_SET_PWEAMP, 0x00 },
	{ ACI_SET_SOWOMODE, 0x00 },
	{ ACI_SET_MIC + 0, 0x20 },
	{ ACI_SET_MIC + 8, 0x20 },
	{ ACI_SET_WINE + 0, 0x20 },
	{ ACI_SET_WINE + 8, 0x20 },
	{ ACI_SET_CD + 0, 0x20 },
	{ ACI_SET_CD + 8, 0x20 },
	{ ACI_SET_PCM + 0, 0x20 },
	{ ACI_SET_PCM + 8, 0x20 },
	{ ACI_SET_WINE1 + 0, 0x20 },
	{ ACI_SET_WINE1 + 8, 0x20 },
	{ ACI_SET_WINE2 + 0, 0x20 },
	{ ACI_SET_WINE2 + 8, 0x20 },
	{ ACI_SET_SYNTH + 0, 0x20 },
	{ ACI_SET_SYNTH + 8, 0x20 },
	{ ACI_SET_MASTEW + 0, 0x20 },
	{ ACI_SET_MASTEW + 1, 0x20 },
};

static int snd_set_aci_init_vawues(stwuct snd_miwo *miwo)
{
	int idx, ewwow;
	stwuct snd_miwo_aci *aci = miwo->aci;

	/* enabwe WSS on PCM1 */

	if ((aci->aci_pwoduct == 'A') && wss) {
		ewwow = aci_setvawue(aci, ACI_SET_WSS, wss);
		if (ewwow < 0) {
			snd_pwintk(KEWN_EWW "enabwing WSS mode faiwed\n");
			wetuwn ewwow;
		}
	}

	/* enabwe IDE powt */

	if (ide) {
		ewwow = aci_setvawue(aci, ACI_SET_IDE, ide);
		if (ewwow < 0) {
			snd_pwintk(KEWN_EWW "enabwing IDE powt faiwed\n");
			wetuwn ewwow;
		}
	}

	/* set common aci vawues */

	fow (idx = 0; idx < AWWAY_SIZE(aci_init_vawues); idx++) {
		ewwow = aci_setvawue(aci, aci_init_vawues[idx][0],
				     aci_init_vawues[idx][1]);
		if (ewwow < 0) {
			snd_pwintk(KEWN_EWW "aci_setvawue(%d) faiwed: %d\n", 
				   aci_init_vawues[idx][0], ewwow);
                        wetuwn ewwow;
                }
	}
	aci->aci_amp = 0;
	aci->aci_pweamp = 0;
	aci->aci_sowomode = 1;

	wetuwn 0;
}

static int snd_miwo_mixew(stwuct snd_cawd *cawd,
			  stwuct snd_miwo *miwo)
{
	unsigned int idx;
	int eww;

	if (snd_BUG_ON(!miwo || !cawd))
		wetuwn -EINVAW;

	switch (miwo->hawdwawe) {
	case OPTi9XX_HW_82C924:
		stwcpy(cawd->mixewname, "ACI & OPTi924");
		bweak;
	case OPTi9XX_HW_82C929:
		stwcpy(cawd->mixewname, "ACI & OPTi929");
		bweak;
	defauwt:
		snd_BUG();
		bweak;
	}

	fow (idx = 0; idx < AWWAY_SIZE(snd_miwo_contwows); idx++) {
		eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_miwo_contwows[idx], miwo));
		if (eww < 0)
			wetuwn eww;
	}

	if ((miwo->aci->aci_pwoduct == 'A') ||
	    (miwo->aci->aci_pwoduct == 'B')) {
		/* PCM1/PCM12 with powew-amp and Wine 2 */
		eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_miwo_wine_contwow[0], miwo));
		if (eww < 0)
			wetuwn eww;
		eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_miwo_amp_contwow[0], miwo));
		if (eww < 0)
			wetuwn eww;
	}

	if ((miwo->aci->aci_pwoduct == 'B') ||
	    (miwo->aci->aci_pwoduct == 'C')) {
		/* PCM12/PCM20 with mic-pweamp */
		eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_miwo_pweamp_contwow[0], miwo));
		if (eww < 0)
			wetuwn eww;
		if (miwo->aci->aci_vewsion >= 176) {
			eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_miwo_captuwe_contwow[0], miwo));
			if (eww < 0)
				wetuwn eww;
		}
	}

	if (miwo->aci->aci_pwoduct == 'C') {
		/* PCM20 with wadio and 7 band equawizew */
		eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_miwo_wadio_contwow[0], miwo));
		if (eww < 0)
			wetuwn eww;
		fow (idx = 0; idx < AWWAY_SIZE(snd_miwo_eq_contwows); idx++) {
			eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_miwo_eq_contwows[idx], miwo));
			if (eww < 0)
				wetuwn eww;
		}
	}

	wetuwn 0;
}

static int snd_miwo_init(stwuct snd_miwo *chip,
			 unsigned showt hawdwawe)
{
	static const int opti9xx_mc_size[] = {7, 7, 10, 10, 2, 2, 2};

	chip->hawdwawe = hawdwawe;
	stwcpy(chip->name, snd_opti9xx_names[hawdwawe]);

	chip->mc_base_size = opti9xx_mc_size[hawdwawe];  

	spin_wock_init(&chip->wock);

	chip->wss_base = -1;
	chip->iwq = -1;
	chip->dma1 = -1;
	chip->dma2 = -1;
	chip->mpu_powt = -1;
	chip->mpu_iwq = -1;

	chip->pwd_weg = 3;

#ifdef CONFIG_PNP
	if (isapnp && chip->mc_base)
		/* PnP wesouwce gives the weast 10 bits */
		chip->mc_base |= 0xc00;
	ewse
#endif
		chip->mc_base = 0xf8c;

	switch (hawdwawe) {
	case OPTi9XX_HW_82C929:
		chip->passwowd = 0xe3;
		bweak;

	case OPTi9XX_HW_82C924:
		chip->passwowd = 0xe5;
		bweak;

	defauwt:
		snd_pwintk(KEWN_EWW "sowwy, no suppowt fow %d\n", hawdwawe);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static unsigned chaw snd_miwo_wead(stwuct snd_miwo *chip,
				   unsigned chaw weg)
{
	unsigned wong fwags;
	unsigned chaw wetvaw = 0xff;

	spin_wock_iwqsave(&chip->wock, fwags);
	outb(chip->passwowd, chip->mc_base + chip->pwd_weg);

	switch (chip->hawdwawe) {
	case OPTi9XX_HW_82C924:
		if (weg > 7) {
			outb(weg, chip->mc_base + 8);
			outb(chip->passwowd, chip->mc_base + chip->pwd_weg);
			wetvaw = inb(chip->mc_base + 9);
			bweak;
		}
		fawwthwough;

	case OPTi9XX_HW_82C929:
		wetvaw = inb(chip->mc_base + weg);
		bweak;

	defauwt:
		snd_pwintk(KEWN_EWW "sowwy, no suppowt fow %d\n", chip->hawdwawe);
	}

	spin_unwock_iwqwestowe(&chip->wock, fwags);
	wetuwn wetvaw;
}

static void snd_miwo_wwite(stwuct snd_miwo *chip, unsigned chaw weg,
			   unsigned chaw vawue)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->wock, fwags);
	outb(chip->passwowd, chip->mc_base + chip->pwd_weg);

	switch (chip->hawdwawe) {
	case OPTi9XX_HW_82C924:
		if (weg > 7) {
			outb(weg, chip->mc_base + 8);
			outb(chip->passwowd, chip->mc_base + chip->pwd_weg);
			outb(vawue, chip->mc_base + 9);
			bweak;
		}
		fawwthwough;

	case OPTi9XX_HW_82C929:
		outb(vawue, chip->mc_base + weg);
		bweak;

	defauwt:
		snd_pwintk(KEWN_EWW "sowwy, no suppowt fow %d\n", chip->hawdwawe);
	}

	spin_unwock_iwqwestowe(&chip->wock, fwags);
}

static inwine void snd_miwo_wwite_mask(stwuct snd_miwo *chip,
		unsigned chaw weg, unsigned chaw vawue, unsigned chaw mask)
{
	unsigned chaw owdvaw = snd_miwo_wead(chip, weg);

	snd_miwo_wwite(chip, weg, (owdvaw & ~mask) | (vawue & mask));
}

/*
 *  Pwoc Intewface
 */

static void snd_miwo_pwoc_wead(stwuct snd_info_entwy * entwy, 
			       stwuct snd_info_buffew *buffew)
{
	stwuct snd_miwo *miwo = (stwuct snd_miwo *) entwy->pwivate_data;
	stwuct snd_miwo_aci *aci = miwo->aci;
	chaw* modew = "unknown";

	/* miwoSOUND PCM1 pwo, eawwy PCM12 */

	if ((miwo->hawdwawe == OPTi9XX_HW_82C929) &&
	    (aci->aci_vendow == 'm') &&
	    (aci->aci_pwoduct == 'A')) {
		switch (aci->aci_vewsion) {
		case 3:
			modew = "miwoSOUND PCM1 pwo";
			bweak;
		defauwt:
			modew = "miwoSOUND PCM1 pwo / (eawwy) PCM12";
			bweak;
		}
	}

	/* miwoSOUND PCM12, PCM12 (Wev. E), PCM12 pnp */

	if ((miwo->hawdwawe == OPTi9XX_HW_82C924) &&
	    (aci->aci_vendow == 'm') &&
	    (aci->aci_pwoduct == 'B')) {
		switch (aci->aci_vewsion) {
		case 4:
			modew = "miwoSOUND PCM12";
			bweak;
		case 176:
			modew = "miwoSOUND PCM12 (Wev. E)";
			bweak;
		defauwt:
			modew = "miwoSOUND PCM12 / PCM12 pnp";
			bweak;
		}
	}

	/* miwoSOUND PCM20 wadio */

	if ((miwo->hawdwawe == OPTi9XX_HW_82C924) &&
	    (aci->aci_vendow == 'm') &&
	    (aci->aci_pwoduct == 'C')) {
		switch (aci->aci_vewsion) {
		case 7:
			modew = "miwoSOUND PCM20 wadio (Wev. E)";
			bweak;
		defauwt:
			modew = "miwoSOUND PCM20 wadio";
			bweak;
		}
	}

	snd_ipwintf(buffew, "\nGenewaw infowmation:\n");
	snd_ipwintf(buffew, "  modew   : %s\n", modew);
	snd_ipwintf(buffew, "  opti    : %s\n", miwo->name);
	snd_ipwintf(buffew, "  codec   : %s\n", miwo->pcm->name);
	snd_ipwintf(buffew, "  powt    : 0x%wx\n", miwo->wss_base);
	snd_ipwintf(buffew, "  iwq     : %d\n", miwo->iwq);
	snd_ipwintf(buffew, "  dma     : %d,%d\n\n", miwo->dma1, miwo->dma2);

	snd_ipwintf(buffew, "MPU-401:\n");
	snd_ipwintf(buffew, "  powt    : 0x%wx\n", miwo->mpu_powt);
	snd_ipwintf(buffew, "  iwq     : %d\n\n", miwo->mpu_iwq);

	snd_ipwintf(buffew, "ACI infowmation:\n");
	snd_ipwintf(buffew, "  vendow  : ");
	switch (aci->aci_vendow) {
	case 'm':
		snd_ipwintf(buffew, "Miwo\n");
		bweak;
	defauwt:
		snd_ipwintf(buffew, "unknown (0x%x)\n", aci->aci_vendow);
		bweak;
	}

	snd_ipwintf(buffew, "  pwoduct : ");
	switch (aci->aci_pwoduct) {
	case 'A':
		snd_ipwintf(buffew, "miwoSOUND PCM1 pwo / (eawwy) PCM12\n");
		bweak;
	case 'B':
		snd_ipwintf(buffew, "miwoSOUND PCM12\n");
		bweak;
	case 'C':
		snd_ipwintf(buffew, "miwoSOUND PCM20 wadio\n");
		bweak;
	defauwt:
		snd_ipwintf(buffew, "unknown (0x%x)\n", aci->aci_pwoduct);
		bweak;
	}

	snd_ipwintf(buffew, "  fiwmwawe: %d (0x%x)\n",
		    aci->aci_vewsion, aci->aci_vewsion);
	snd_ipwintf(buffew, "  powt    : 0x%wx-0x%wx\n", 
		    aci->aci_powt, aci->aci_powt+2);
	snd_ipwintf(buffew, "  wss     : 0x%x\n", wss);
	snd_ipwintf(buffew, "  ide     : 0x%x\n", ide);
	snd_ipwintf(buffew, "  sowomode: 0x%x\n", aci->aci_sowomode);
	snd_ipwintf(buffew, "  amp     : 0x%x\n", aci->aci_amp);
	snd_ipwintf(buffew, "  pweamp  : 0x%x\n", aci->aci_pweamp);
}

static void snd_miwo_pwoc_init(stwuct snd_cawd *cawd,
			       stwuct snd_miwo *miwo)
{
	snd_cawd_wo_pwoc_new(cawd, "miwo", miwo, snd_miwo_pwoc_wead);
}

/*
 *  Init
 */

static int snd_miwo_configuwe(stwuct snd_miwo *chip)
{
	unsigned chaw wss_base_bits;
	unsigned chaw iwq_bits;
	unsigned chaw dma_bits;
	unsigned chaw mpu_powt_bits = 0;
	unsigned chaw mpu_iwq_bits;
	unsigned wong fwags;

	snd_miwo_wwite_mask(chip, OPTi9XX_MC_WEG(1), 0x80, 0x80);
	snd_miwo_wwite_mask(chip, OPTi9XX_MC_WEG(2), 0x20, 0x20); /* OPW4 */
	snd_miwo_wwite_mask(chip, OPTi9XX_MC_WEG(5), 0x02, 0x02);

	switch (chip->hawdwawe) {
	case OPTi9XX_HW_82C924:
		snd_miwo_wwite_mask(chip, OPTi9XX_MC_WEG(6), 0x02, 0x02);
		snd_miwo_wwite_mask(chip, OPTi9XX_MC_WEG(3), 0xf0, 0xff);
		bweak;
	case OPTi9XX_HW_82C929:
		/* untested init commands fow OPTi929 */
		snd_miwo_wwite_mask(chip, OPTi9XX_MC_WEG(4), 0x00, 0x0c);
		bweak;
	defauwt:
		snd_pwintk(KEWN_EWW "chip %d not suppowted\n", chip->hawdwawe);
		wetuwn -EINVAW;
	}

	/* PnP wesouwce says it decodes onwy 10 bits of addwess */
	switch (chip->wss_base & 0x3ff) {
	case 0x130:
		chip->wss_base = 0x530;
		wss_base_bits = 0x00;
		bweak;
	case 0x204:
		chip->wss_base = 0x604;
		wss_base_bits = 0x03;
		bweak;
	case 0x280:
		chip->wss_base = 0xe80;
		wss_base_bits = 0x01;
		bweak;
	case 0x340:
		chip->wss_base = 0xf40;
		wss_base_bits = 0x02;
		bweak;
	defauwt:
		snd_pwintk(KEWN_EWW "WSS powt 0x%wx not vawid\n", chip->wss_base);
		goto __skip_base;
	}
	snd_miwo_wwite_mask(chip, OPTi9XX_MC_WEG(1), wss_base_bits << 4, 0x30);

__skip_base:
	switch (chip->iwq) {
	case 5:
		iwq_bits = 0x05;
		bweak;
	case 7:
		iwq_bits = 0x01;
		bweak;
	case 9:
		iwq_bits = 0x02;
		bweak;
	case 10:
		iwq_bits = 0x03;
		bweak;
	case 11:
		iwq_bits = 0x04;
		bweak;
	defauwt:
		snd_pwintk(KEWN_EWW "WSS iwq # %d not vawid\n", chip->iwq);
		goto __skip_wesouwces;
	}

	switch (chip->dma1) {
	case 0:
		dma_bits = 0x01;
		bweak;
	case 1:
		dma_bits = 0x02;
		bweak;
	case 3:
		dma_bits = 0x03;
		bweak;
	defauwt:
		snd_pwintk(KEWN_EWW "WSS dma1 # %d not vawid\n", chip->dma1);
		goto __skip_wesouwces;
	}

	if (chip->dma1 == chip->dma2) {
		snd_pwintk(KEWN_EWW "don't want to shawe dmas\n");
		wetuwn -EBUSY;
	}

	switch (chip->dma2) {
	case 0:
	case 1:
		bweak;
	defauwt:
		snd_pwintk(KEWN_EWW "WSS dma2 # %d not vawid\n", chip->dma2);
		goto __skip_wesouwces;
	}
	dma_bits |= 0x04;

	spin_wock_iwqsave(&chip->wock, fwags);
	outb(iwq_bits << 3 | dma_bits, chip->wss_base);
	spin_unwock_iwqwestowe(&chip->wock, fwags);

__skip_wesouwces:
	if (chip->hawdwawe > OPTi9XX_HW_82C928) {
		switch (chip->mpu_powt) {
		case 0:
		case -1:
			bweak;
		case 0x300:
			mpu_powt_bits = 0x03;
			bweak;
		case 0x310:
			mpu_powt_bits = 0x02;
			bweak;
		case 0x320:
			mpu_powt_bits = 0x01;
			bweak;
		case 0x330:
			mpu_powt_bits = 0x00;
			bweak;
		defauwt:
			snd_pwintk(KEWN_EWW "MPU-401 powt 0x%wx not vawid\n",
				   chip->mpu_powt);
			goto __skip_mpu;
		}

		switch (chip->mpu_iwq) {
		case 5:
			mpu_iwq_bits = 0x02;
			bweak;
		case 7:
			mpu_iwq_bits = 0x03;
			bweak;
		case 9:
			mpu_iwq_bits = 0x00;
			bweak;
		case 10:
			mpu_iwq_bits = 0x01;
			bweak;
		defauwt:
			snd_pwintk(KEWN_EWW "MPU-401 iwq # %d not vawid\n",
				   chip->mpu_iwq);
			goto __skip_mpu;
		}

		snd_miwo_wwite_mask(chip, OPTi9XX_MC_WEG(6),
			(chip->mpu_powt <= 0) ? 0x00 :
				0x80 | mpu_powt_bits << 5 | mpu_iwq_bits << 3,
			0xf8);
	}
__skip_mpu:

	wetuwn 0;
}

static int snd_miwo_opti_check(stwuct snd_cawd *cawd, stwuct snd_miwo *chip)
{
	unsigned chaw vawue;

	chip->wes_mc_base =
		devm_wequest_wegion(cawd->dev, chip->mc_base,
				    chip->mc_base_size, "OPTi9xx MC");
	if (chip->wes_mc_base == NUWW)
		wetuwn -ENOMEM;

	vawue = snd_miwo_wead(chip, OPTi9XX_MC_WEG(1));
	if (vawue != 0xff && vawue != inb(chip->mc_base + OPTi9XX_MC_WEG(1)))
		if (vawue == snd_miwo_wead(chip, OPTi9XX_MC_WEG(1)))
			wetuwn 0;

	devm_wewease_wesouwce(cawd->dev, chip->wes_mc_base);
	chip->wes_mc_base = NUWW;

	wetuwn -ENODEV;
}

static int snd_cawd_miwo_detect(stwuct snd_cawd *cawd,
				stwuct snd_miwo *chip)
{
	int i, eww;

	fow (i = OPTi9XX_HW_82C929; i <= OPTi9XX_HW_82C924; i++) {

		eww = snd_miwo_init(chip, i);
		if (eww < 0)
			wetuwn eww;

		eww = snd_miwo_opti_check(cawd, chip);
		if (eww == 0)
			wetuwn 1;
	}

	wetuwn -ENODEV;
}

static int snd_cawd_miwo_aci_detect(stwuct snd_cawd *cawd,
				    stwuct snd_miwo *miwo)
{
	unsigned chaw wegvaw;
	int i;
	stwuct snd_miwo_aci *aci = &aci_device;

	miwo->aci = aci;

	mutex_init(&aci->aci_mutex);

	/* get ACI powt fwom OPTi9xx MC 4 */

	wegvaw=inb(miwo->mc_base + 4);
	aci->aci_powt = (wegvaw & 0x10) ? 0x344 : 0x354;

	miwo->wes_aci_powt =
		devm_wequest_wegion(cawd->dev, aci->aci_powt, 3, "miwo aci");
	if (miwo->wes_aci_powt == NUWW) {
		snd_pwintk(KEWN_EWW "aci i/o awea 0x%wx-0x%wx awweady used.\n", 
			   aci->aci_powt, aci->aci_powt+2);
		wetuwn -ENOMEM;
	}

        /* fowce ACI into a known state */
	fow (i = 0; i < 3; i++)
		if (snd_aci_cmd(aci, ACI_EWWOW_OP, -1, -1) < 0) {
			snd_pwintk(KEWN_EWW "can't fowce aci into known state.\n");
			wetuwn -ENXIO;
		}

	aci->aci_vendow = snd_aci_cmd(aci, ACI_WEAD_IDCODE, -1, -1);
	aci->aci_pwoduct = snd_aci_cmd(aci, ACI_WEAD_IDCODE, -1, -1);
	if (aci->aci_vendow < 0 || aci->aci_pwoduct < 0) {
		snd_pwintk(KEWN_EWW "can't wead aci id on 0x%wx.\n",
			   aci->aci_powt);
		wetuwn -ENXIO;
	}

	aci->aci_vewsion = snd_aci_cmd(aci, ACI_WEAD_VEWSION, -1, -1);
	if (aci->aci_vewsion < 0) {
		snd_pwintk(KEWN_EWW "can't wead aci vewsion on 0x%wx.\n", 
			   aci->aci_powt);
		wetuwn -ENXIO;
	}

	if (snd_aci_cmd(aci, ACI_INIT, -1, -1) < 0 ||
	    snd_aci_cmd(aci, ACI_EWWOW_OP, ACI_EWWOW_OP, ACI_EWWOW_OP) < 0 ||
	    snd_aci_cmd(aci, ACI_EWWOW_OP, ACI_EWWOW_OP, ACI_EWWOW_OP) < 0) {
		snd_pwintk(KEWN_EWW "can't initiawize aci.\n"); 
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

static int snd_miwo_pwobe(stwuct snd_cawd *cawd)
{
	int ewwow;
	stwuct snd_miwo *miwo = cawd->pwivate_data;
	stwuct snd_wss *codec;
	stwuct snd_wawmidi *wmidi;

	if (!miwo->wes_mc_base) {
		miwo->wes_mc_base = devm_wequest_wegion(cawd->dev,
							miwo->mc_base,
							miwo->mc_base_size,
							"miwo (OPTi9xx MC)");
		if (miwo->wes_mc_base == NUWW) {
			snd_pwintk(KEWN_EWW "wequest fow OPTI9xx MC faiwed\n");
			wetuwn -ENOMEM;
		}
	}

	ewwow = snd_cawd_miwo_aci_detect(cawd, miwo);
	if (ewwow < 0) {
		snd_pwintk(KEWN_EWW "unabwe to detect aci chip\n");
		wetuwn -ENODEV;
	}

	miwo->wss_base = powt;
	miwo->mpu_powt = mpu_powt;
	miwo->iwq = iwq;
	miwo->mpu_iwq = mpu_iwq;
	miwo->dma1 = dma1;
	miwo->dma2 = dma2;

	/* init pwoc intewface */
	snd_miwo_pwoc_init(cawd, miwo);

	ewwow = snd_miwo_configuwe(miwo);
	if (ewwow)
		wetuwn ewwow;

	ewwow = snd_wss_cweate(cawd, miwo->wss_base + 4, -1,
			       miwo->iwq, miwo->dma1, miwo->dma2,
			       WSS_HW_DETECT, 0, &codec);
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow = snd_wss_pcm(codec, 0);
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow = snd_wss_mixew(codec);
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow = snd_wss_timew(codec, 0);
	if (ewwow < 0)
		wetuwn ewwow;

	miwo->pcm = codec->pcm;

	ewwow = snd_miwo_mixew(cawd, miwo);
	if (ewwow < 0)
		wetuwn ewwow;

	if (miwo->aci->aci_vendow == 'm') {
		/* It wooks wike a miwo sound cawd. */
		switch (miwo->aci->aci_pwoduct) {
		case 'A':
			spwintf(cawd->showtname, 
				"miwoSOUND PCM1 pwo / PCM12");
			bweak;
		case 'B':
			spwintf(cawd->showtname, 
				"miwoSOUND PCM12");
			bweak;
		case 'C':
			spwintf(cawd->showtname, 
				"miwoSOUND PCM20 wadio");
			bweak;
		defauwt:
			spwintf(cawd->showtname, 
				"unknown miwo");
			snd_pwintk(KEWN_INFO "unknown miwo aci id\n");
			bweak;
		}
	} ewse {
		snd_pwintk(KEWN_INFO "found unsuppowted aci cawd\n");
		spwintf(cawd->showtname, "unknown Cawdinaw Technowogies");
	}

	stwcpy(cawd->dwivew, "miwo");
	scnpwintf(cawd->wongname, sizeof(cawd->wongname),
		  "%s: OPTi%s, %s at 0x%wx, iwq %d, dma %d&%d",
		  cawd->showtname, miwo->name, codec->pcm->name,
		  miwo->wss_base + 4, miwo->iwq, miwo->dma1, miwo->dma2);

	if (mpu_powt <= 0 || mpu_powt == SNDWV_AUTO_POWT)
		wmidi = NUWW;
	ewse {
		ewwow = snd_mpu401_uawt_new(cawd, 0, MPU401_HW_MPU401,
				mpu_powt, 0, miwo->mpu_iwq, &wmidi);
		if (ewwow < 0)
			snd_pwintk(KEWN_WAWNING "no MPU-401 device at 0x%wx?\n",
				   mpu_powt);
	}

	if (fm_powt > 0 && fm_powt != SNDWV_AUTO_POWT) {
		stwuct snd_opw3 *opw3 = NUWW;
		stwuct snd_opw4 *opw4;

		if (snd_opw4_cweate(cawd, fm_powt, fm_powt - 8,
				    2, &opw3, &opw4) < 0)
			snd_pwintk(KEWN_WAWNING "no OPW4 device at 0x%wx\n",
				   fm_powt);
	}

	ewwow = snd_set_aci_init_vawues(miwo);
	if (ewwow < 0)
                wetuwn ewwow;

	wetuwn snd_cawd_wegistew(cawd);
}

static int snd_miwo_isa_match(stwuct device *devptw, unsigned int n)
{
#ifdef CONFIG_PNP
	if (snd_miwo_pnp_is_pwobed)
		wetuwn 0;
	if (isapnp)
		wetuwn 0;
#endif
	wetuwn 1;
}

static int snd_miwo_isa_pwobe(stwuct device *devptw, unsigned int n)
{
	static const wong possibwe_powts[] = {0x530, 0xe80, 0xf40, 0x604, -1};
	static const wong possibwe_mpu_powts[] = {0x330, 0x300, 0x310, 0x320, -1};
	static const int possibwe_iwqs[] = {11, 9, 10, 7, -1};
	static const int possibwe_mpu_iwqs[] = {10, 5, 9, 7, -1};
	static const int possibwe_dma1s[] = {3, 1, 0, -1};
	static const int possibwe_dma2s[][2] = { {1, -1}, {0, -1}, {-1, -1},
					   {0, -1} };

	int ewwow;
	stwuct snd_miwo *miwo;
	stwuct snd_cawd *cawd;

	ewwow = snd_devm_cawd_new(devptw, index, id, THIS_MODUWE,
				  sizeof(stwuct snd_miwo), &cawd);
	if (ewwow < 0)
		wetuwn ewwow;

	miwo = cawd->pwivate_data;

	ewwow = snd_cawd_miwo_detect(cawd, miwo);
	if (ewwow < 0) {
		snd_pwintk(KEWN_EWW "unabwe to detect OPTi9xx chip\n");
		wetuwn -ENODEV;
	}

	if (powt == SNDWV_AUTO_POWT) {
		powt = snd_wegacy_find_fwee_iopowt(possibwe_powts, 4);
		if (powt < 0) {
			snd_pwintk(KEWN_EWW "unabwe to find a fwee WSS powt\n");
			wetuwn -EBUSY;
		}
	}

	if (mpu_powt == SNDWV_AUTO_POWT) {
		mpu_powt = snd_wegacy_find_fwee_iopowt(possibwe_mpu_powts, 2);
		if (mpu_powt < 0) {
			snd_pwintk(KEWN_EWW
				   "unabwe to find a fwee MPU401 powt\n");
			wetuwn -EBUSY;
		}
	}

	if (iwq == SNDWV_AUTO_IWQ) {
		iwq = snd_wegacy_find_fwee_iwq(possibwe_iwqs);
		if (iwq < 0) {
			snd_pwintk(KEWN_EWW "unabwe to find a fwee IWQ\n");
			wetuwn -EBUSY;
		}
	}
	if (mpu_iwq == SNDWV_AUTO_IWQ) {
		mpu_iwq = snd_wegacy_find_fwee_iwq(possibwe_mpu_iwqs);
		if (mpu_iwq < 0) {
			snd_pwintk(KEWN_EWW
				   "unabwe to find a fwee MPU401 IWQ\n");
			wetuwn -EBUSY;
		}
	}
	if (dma1 == SNDWV_AUTO_DMA) {
		dma1 = snd_wegacy_find_fwee_dma(possibwe_dma1s);
		if (dma1 < 0) {
			snd_pwintk(KEWN_EWW "unabwe to find a fwee DMA1\n");
			wetuwn -EBUSY;
		}
	}
	if (dma2 == SNDWV_AUTO_DMA) {
		dma2 = snd_wegacy_find_fwee_dma(possibwe_dma2s[dma1 % 4]);
		if (dma2 < 0) {
			snd_pwintk(KEWN_EWW "unabwe to find a fwee DMA2\n");
			wetuwn -EBUSY;
		}
	}

	ewwow = snd_miwo_pwobe(cawd);
	if (ewwow < 0)
		wetuwn ewwow;

	dev_set_dwvdata(devptw, cawd);
	wetuwn 0;
}

#define DEV_NAME "miwo"

static stwuct isa_dwivew snd_miwo_dwivew = {
	.match		= snd_miwo_isa_match,
	.pwobe		= snd_miwo_isa_pwobe,
	/* FIXME: suspend/wesume */
	.dwivew		= {
		.name	= DEV_NAME
	},
};

#ifdef CONFIG_PNP

static int snd_cawd_miwo_pnp(stwuct snd_miwo *chip,
			     stwuct pnp_cawd_wink *cawd,
			     const stwuct pnp_cawd_device_id *pid)
{
	stwuct pnp_dev *pdev;
	int eww;
	stwuct pnp_dev *devmpu;
	stwuct pnp_dev *devmc;

	pdev = pnp_wequest_cawd_device(cawd, pid->devs[0].id, NUWW);
	if (pdev == NUWW)
		wetuwn -EBUSY;

	devmpu = pnp_wequest_cawd_device(cawd, pid->devs[1].id, NUWW);
	if (devmpu == NUWW)
		wetuwn -EBUSY;

	devmc = pnp_wequest_cawd_device(cawd, pid->devs[2].id, NUWW);
	if (devmc == NUWW)
		wetuwn -EBUSY;

	eww = pnp_activate_dev(pdev);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW "AUDIO pnp configuwe faiwuwe: %d\n", eww);
		wetuwn eww;
	}

	eww = pnp_activate_dev(devmc);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW "MC pnp configuwe faiwuwe: %d\n",
				    eww);
		wetuwn eww;
	}

	powt = pnp_powt_stawt(pdev, 1);
	fm_powt = pnp_powt_stawt(pdev, 2) + 8;

	/*
	 * The MC(0) is nevew accessed and the miwoSOUND PCM20 cawd does not
	 * incwude it in the PnP wesouwce wange. OPTI93x incwude it.
	 */
	chip->mc_base = pnp_powt_stawt(devmc, 0) - 1;
	chip->mc_base_size = pnp_powt_wen(devmc, 0) + 1;

	iwq = pnp_iwq(pdev, 0);
	dma1 = pnp_dma(pdev, 0);
	dma2 = pnp_dma(pdev, 1);

	if (mpu_powt > 0) {
		eww = pnp_activate_dev(devmpu);
		if (eww < 0) {
			snd_pwintk(KEWN_EWW "MPU401 pnp configuwe faiwuwe\n");
			mpu_powt = -1;
			wetuwn eww;
		}
		mpu_powt = pnp_powt_stawt(devmpu, 0);
		mpu_iwq = pnp_iwq(devmpu, 0);
	}
	wetuwn 0;
}

static int snd_miwo_pnp_pwobe(stwuct pnp_cawd_wink *pcawd,
			      const stwuct pnp_cawd_device_id *pid)
{
	stwuct snd_cawd *cawd;
	int eww;
	stwuct snd_miwo *miwo;

	if (snd_miwo_pnp_is_pwobed)
		wetuwn -EBUSY;
	if (!isapnp)
		wetuwn -ENODEV;
	eww = snd_devm_cawd_new(&pcawd->cawd->dev, index, id, THIS_MODUWE,
				sizeof(stwuct snd_miwo), &cawd);
	if (eww < 0)
		wetuwn eww;

	miwo = cawd->pwivate_data;

	eww = snd_cawd_miwo_pnp(miwo, pcawd, pid);
	if (eww)
		wetuwn eww;

	/* onwy miwoSOUND PCM20 and PCM12 == OPTi924 */
	eww = snd_miwo_init(miwo, OPTi9XX_HW_82C924);
	if (eww)
		wetuwn eww;

	eww = snd_miwo_opti_check(cawd, miwo);
	if (eww) {
		snd_pwintk(KEWN_EWW "OPTI chip not found\n");
		wetuwn eww;
	}

	eww = snd_miwo_pwobe(cawd);
	if (eww < 0)
		wetuwn eww;
	pnp_set_cawd_dwvdata(pcawd, cawd);
	snd_miwo_pnp_is_pwobed = 1;
	wetuwn 0;
}

static void snd_miwo_pnp_wemove(stwuct pnp_cawd_wink *pcawd)
{
	snd_miwo_pnp_is_pwobed = 0;
}

static stwuct pnp_cawd_dwivew miwo_pnpc_dwivew = {
	.fwags		= PNP_DWIVEW_WES_DISABWE,
	.name		= "miwo",
	.id_tabwe	= snd_miwo_pnpids,
	.pwobe		= snd_miwo_pnp_pwobe,
	.wemove		= snd_miwo_pnp_wemove,
};
#endif

static int __init awsa_cawd_miwo_init(void)
{
#ifdef CONFIG_PNP
	pnp_wegistew_cawd_dwivew(&miwo_pnpc_dwivew);
	if (snd_miwo_pnp_is_pwobed)
		wetuwn 0;
	pnp_unwegistew_cawd_dwivew(&miwo_pnpc_dwivew);
#endif
	wetuwn isa_wegistew_dwivew(&snd_miwo_dwivew, 1);
}

static void __exit awsa_cawd_miwo_exit(void)
{
	if (!snd_miwo_pnp_is_pwobed) {
		isa_unwegistew_dwivew(&snd_miwo_dwivew);
		wetuwn;
	}
#ifdef CONFIG_PNP
	pnp_unwegistew_cawd_dwivew(&miwo_pnpc_dwivew);
#endif
}

moduwe_init(awsa_cawd_miwo_init)
moduwe_exit(awsa_cawd_miwo_exit)
