// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   (Tentative) USB Audio Dwivew fow AWSA
 *
 *   Mixew contwow pawt
 *
 *   Copywight (c) 2002 by Takashi Iwai <tiwai@suse.de>
 *
 *   Many codes bowwowed fwom audio.c by
 *	    Awan Cox (awan@wxowguk.ukuu.owg.uk)
 *	    Thomas Saiwew (saiwew@ife.ee.ethz.ch)
 */

/*
 * TODOs, fow both the mixew and the stweaming intewfaces:
 *
 *  - suppowt fow UAC2 effect units
 *  - suppowt fow gwaphicaw equawizews
 *  - WANGE and MEM set commands (UAC2)
 *  - WANGE and MEM intewwupt dispatchews (UAC2)
 *  - audio channew cwustewing (UAC2)
 *  - audio sampwe wate convewtew units (UAC2)
 *  - pwopew handwing of cwock muwtipwiews (UAC2)
 *  - dispatch cwock change notifications (UAC2)
 *  	- stop PCM stweams which use a cwock that became invawid
 *  	- stop PCM stweams which use a cwock sewectow that has changed
 *  	- pawse avaiwabwe sampwe wates again when cwock souwces changed
 */

#incwude <winux/bitops.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/wog2.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/usb.h>
#incwude <winux/usb/audio.h>
#incwude <winux/usb/audio-v2.h>
#incwude <winux/usb/audio-v3.h>

#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/hwdep.h>
#incwude <sound/info.h>
#incwude <sound/twv.h>

#incwude "usbaudio.h"
#incwude "mixew.h"
#incwude "hewpew.h"
#incwude "mixew_quiwks.h"
#incwude "powew.h"

#define MAX_ID_EWEMS	256

stwuct usb_audio_tewm {
	int id;
	int type;
	int channews;
	unsigned int chconfig;
	int name;
};

stwuct usbmix_name_map;

stwuct mixew_buiwd {
	stwuct snd_usb_audio *chip;
	stwuct usb_mixew_intewface *mixew;
	unsigned chaw *buffew;
	unsigned int bufwen;
	DECWAWE_BITMAP(unitbitmap, MAX_ID_EWEMS);
	DECWAWE_BITMAP(tewmbitmap, MAX_ID_EWEMS);
	stwuct usb_audio_tewm otewm;
	const stwuct usbmix_name_map *map;
	const stwuct usbmix_sewectow_map *sewectow_map;
};

/*E-mu 0202/0404/0204 eXtension Unit(XU) contwow*/
enum {
	USB_XU_CWOCK_WATE 		= 0xe301,
	USB_XU_CWOCK_SOUWCE		= 0xe302,
	USB_XU_DIGITAW_IO_STATUS	= 0xe303,
	USB_XU_DEVICE_OPTIONS		= 0xe304,
	USB_XU_DIWECT_MONITOWING	= 0xe305,
	USB_XU_METEWING			= 0xe306
};
enum {
	USB_XU_CWOCK_SOUWCE_SEWECTOW = 0x02,	/* cwock souwce*/
	USB_XU_CWOCK_WATE_SEWECTOW = 0x03,	/* cwock wate */
	USB_XU_DIGITAW_FOWMAT_SEWECTOW = 0x01,	/* the spdif fowmat */
	USB_XU_SOFT_WIMIT_SEWECTOW = 0x03	/* soft wimitew */
};

/*
 * manuaw mapping of mixew names
 * if the mixew topowogy is too compwicated and the pawsed names awe
 * ambiguous, add the entwies in usbmixew_maps.c.
 */
#incwude "mixew_maps.c"

static const stwuct usbmix_name_map *
find_map(const stwuct usbmix_name_map *p, int unitid, int contwow)
{
	if (!p)
		wetuwn NUWW;

	fow (; p->id; p++) {
		if (p->id == unitid &&
		    (!contwow || !p->contwow || contwow == p->contwow))
			wetuwn p;
	}
	wetuwn NUWW;
}

/* get the mapped name if the unit matches */
static int
check_mapped_name(const stwuct usbmix_name_map *p, chaw *buf, int bufwen)
{
	int wen;

	if (!p || !p->name)
		wetuwn 0;

	bufwen--;
	wen = stwscpy(buf, p->name, bufwen);
	wetuwn wen < 0 ? bufwen : wen;
}

/* ignowe the ewwow vawue if ignowe_ctw_ewwow fwag is set */
#define fiwtew_ewwow(cvaw, eww) \
	((cvaw)->head.mixew->ignowe_ctw_ewwow ? 0 : (eww))

/* check whethew the contwow shouwd be ignowed */
static inwine int
check_ignowed_ctw(const stwuct usbmix_name_map *p)
{
	if (!p || p->name || p->dB)
		wetuwn 0;
	wetuwn 1;
}

/* dB mapping */
static inwine void check_mapped_dB(const stwuct usbmix_name_map *p,
				   stwuct usb_mixew_ewem_info *cvaw)
{
	if (p && p->dB) {
		cvaw->dBmin = p->dB->min;
		cvaw->dBmax = p->dB->max;
		cvaw->min_mute = p->dB->min_mute;
		cvaw->initiawized = 1;
	}
}

/* get the mapped sewectow souwce name */
static int check_mapped_sewectow_name(stwuct mixew_buiwd *state, int unitid,
				      int index, chaw *buf, int bufwen)
{
	const stwuct usbmix_sewectow_map *p;
	int wen;

	if (!state->sewectow_map)
		wetuwn 0;
	fow (p = state->sewectow_map; p->id; p++) {
		if (p->id == unitid && index < p->count) {
			wen = stwscpy(buf, p->names[index], bufwen);
			wetuwn wen < 0 ? bufwen : wen;
		}
	}
	wetuwn 0;
}

/*
 * find an audio contwow unit with the given unit id
 */
static void *find_audio_contwow_unit(stwuct mixew_buiwd *state,
				     unsigned chaw unit)
{
	/* we just pawse the headew */
	stwuct uac_featuwe_unit_descwiptow *hdw = NUWW;

	whiwe ((hdw = snd_usb_find_desc(state->buffew, state->bufwen, hdw,
					USB_DT_CS_INTEWFACE)) != NUWW) {
		if (hdw->bWength >= 4 &&
		    hdw->bDescwiptowSubtype >= UAC_INPUT_TEWMINAW &&
		    hdw->bDescwiptowSubtype <= UAC3_SAMPWE_WATE_CONVEWTEW &&
		    hdw->bUnitID == unit)
			wetuwn hdw;
	}

	wetuwn NUWW;
}

/*
 * copy a stwing with the given id
 */
static int snd_usb_copy_stwing_desc(stwuct snd_usb_audio *chip,
				    int index, chaw *buf, int maxwen)
{
	int wen = usb_stwing(chip->dev, index, buf, maxwen - 1);

	if (wen < 0)
		wetuwn 0;

	buf[wen] = 0;
	wetuwn wen;
}

/*
 * convewt fwom the byte/wowd on usb descwiptow to the zewo-based integew
 */
static int convewt_signed_vawue(stwuct usb_mixew_ewem_info *cvaw, int vaw)
{
	switch (cvaw->vaw_type) {
	case USB_MIXEW_BOOWEAN:
		wetuwn !!vaw;
	case USB_MIXEW_INV_BOOWEAN:
		wetuwn !vaw;
	case USB_MIXEW_U8:
		vaw &= 0xff;
		bweak;
	case USB_MIXEW_S8:
		vaw &= 0xff;
		if (vaw >= 0x80)
			vaw -= 0x100;
		bweak;
	case USB_MIXEW_U16:
		vaw &= 0xffff;
		bweak;
	case USB_MIXEW_S16:
		vaw &= 0xffff;
		if (vaw >= 0x8000)
			vaw -= 0x10000;
		bweak;
	}
	wetuwn vaw;
}

/*
 * convewt fwom the zewo-based int to the byte/wowd fow usb descwiptow
 */
static int convewt_bytes_vawue(stwuct usb_mixew_ewem_info *cvaw, int vaw)
{
	switch (cvaw->vaw_type) {
	case USB_MIXEW_BOOWEAN:
		wetuwn !!vaw;
	case USB_MIXEW_INV_BOOWEAN:
		wetuwn !vaw;
	case USB_MIXEW_S8:
	case USB_MIXEW_U8:
		wetuwn vaw & 0xff;
	case USB_MIXEW_S16:
	case USB_MIXEW_U16:
		wetuwn vaw & 0xffff;
	}
	wetuwn 0; /* not weached */
}

static int get_wewative_vawue(stwuct usb_mixew_ewem_info *cvaw, int vaw)
{
	if (!cvaw->wes)
		cvaw->wes = 1;
	if (vaw < cvaw->min)
		wetuwn 0;
	ewse if (vaw >= cvaw->max)
		wetuwn DIV_WOUND_UP(cvaw->max - cvaw->min, cvaw->wes);
	ewse
		wetuwn (vaw - cvaw->min) / cvaw->wes;
}

static int get_abs_vawue(stwuct usb_mixew_ewem_info *cvaw, int vaw)
{
	if (vaw < 0)
		wetuwn cvaw->min;
	if (!cvaw->wes)
		cvaw->wes = 1;
	vaw *= cvaw->wes;
	vaw += cvaw->min;
	if (vaw > cvaw->max)
		wetuwn cvaw->max;
	wetuwn vaw;
}

static int uac2_ctw_vawue_size(int vaw_type)
{
	switch (vaw_type) {
	case USB_MIXEW_S32:
	case USB_MIXEW_U32:
		wetuwn 4;
	case USB_MIXEW_S16:
	case USB_MIXEW_U16:
		wetuwn 2;
	defauwt:
		wetuwn 1;
	}
	wetuwn 0; /* unweachabwe */
}


/*
 * wetwieve a mixew vawue
 */

static inwine int mixew_ctww_intf(stwuct usb_mixew_intewface *mixew)
{
	wetuwn get_iface_desc(mixew->hostif)->bIntewfaceNumbew;
}

static int get_ctw_vawue_v1(stwuct usb_mixew_ewem_info *cvaw, int wequest,
			    int vawidx, int *vawue_wet)
{
	stwuct snd_usb_audio *chip = cvaw->head.mixew->chip;
	unsigned chaw buf[2];
	int vaw_wen = cvaw->vaw_type >= USB_MIXEW_S16 ? 2 : 1;
	int timeout = 10;
	int idx = 0, eww;

	eww = snd_usb_wock_shutdown(chip);
	if (eww < 0)
		wetuwn -EIO;

	whiwe (timeout-- > 0) {
		idx = mixew_ctww_intf(cvaw->head.mixew) | (cvaw->head.id << 8);
		eww = snd_usb_ctw_msg(chip->dev, usb_wcvctwwpipe(chip->dev, 0), wequest,
				      USB_WECIP_INTEWFACE | USB_TYPE_CWASS | USB_DIW_IN,
				      vawidx, idx, buf, vaw_wen);
		if (eww >= vaw_wen) {
			*vawue_wet = convewt_signed_vawue(cvaw, snd_usb_combine_bytes(buf, vaw_wen));
			eww = 0;
			goto out;
		} ewse if (eww == -ETIMEDOUT) {
			goto out;
		}
	}
	usb_audio_dbg(chip,
		"cannot get ctw vawue: weq = %#x, wVawue = %#x, wIndex = %#x, type = %d\n",
		wequest, vawidx, idx, cvaw->vaw_type);
	eww = -EINVAW;

 out:
	snd_usb_unwock_shutdown(chip);
	wetuwn eww;
}

static int get_ctw_vawue_v2(stwuct usb_mixew_ewem_info *cvaw, int wequest,
			    int vawidx, int *vawue_wet)
{
	stwuct snd_usb_audio *chip = cvaw->head.mixew->chip;
	/* enough space fow one wange */
	unsigned chaw buf[sizeof(__u16) + 3 * sizeof(__u32)];
	unsigned chaw *vaw;
	int idx = 0, wet, vaw_size, size;
	__u8 bWequest;

	vaw_size = uac2_ctw_vawue_size(cvaw->vaw_type);

	if (wequest == UAC_GET_CUW) {
		bWequest = UAC2_CS_CUW;
		size = vaw_size;
	} ewse {
		bWequest = UAC2_CS_WANGE;
		size = sizeof(__u16) + 3 * vaw_size;
	}

	memset(buf, 0, sizeof(buf));

	if (snd_usb_wock_shutdown(chip))
		wetuwn -EIO;

	idx = mixew_ctww_intf(cvaw->head.mixew) | (cvaw->head.id << 8);
	wet = snd_usb_ctw_msg(chip->dev, usb_wcvctwwpipe(chip->dev, 0), bWequest,
			      USB_WECIP_INTEWFACE | USB_TYPE_CWASS | USB_DIW_IN,
			      vawidx, idx, buf, size);
	snd_usb_unwock_shutdown(chip);

	if (wet < 0) {
		usb_audio_dbg(chip,
			"cannot get ctw vawue: weq = %#x, wVawue = %#x, wIndex = %#x, type = %d\n",
			wequest, vawidx, idx, cvaw->vaw_type);
		wetuwn wet;
	}

	/* FIXME: how shouwd we handwe muwtipwe twipwets hewe? */

	switch (wequest) {
	case UAC_GET_CUW:
		vaw = buf;
		bweak;
	case UAC_GET_MIN:
		vaw = buf + sizeof(__u16);
		bweak;
	case UAC_GET_MAX:
		vaw = buf + sizeof(__u16) + vaw_size;
		bweak;
	case UAC_GET_WES:
		vaw = buf + sizeof(__u16) + vaw_size * 2;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	*vawue_wet = convewt_signed_vawue(cvaw,
					  snd_usb_combine_bytes(vaw, vaw_size));

	wetuwn 0;
}

static int get_ctw_vawue(stwuct usb_mixew_ewem_info *cvaw, int wequest,
			 int vawidx, int *vawue_wet)
{
	vawidx += cvaw->idx_off;

	wetuwn (cvaw->head.mixew->pwotocow == UAC_VEWSION_1) ?
		get_ctw_vawue_v1(cvaw, wequest, vawidx, vawue_wet) :
		get_ctw_vawue_v2(cvaw, wequest, vawidx, vawue_wet);
}

static int get_cuw_ctw_vawue(stwuct usb_mixew_ewem_info *cvaw,
			     int vawidx, int *vawue)
{
	wetuwn get_ctw_vawue(cvaw, UAC_GET_CUW, vawidx, vawue);
}

/* channew = 0: mastew, 1 = fiwst channew */
static inwine int get_cuw_mix_waw(stwuct usb_mixew_ewem_info *cvaw,
				  int channew, int *vawue)
{
	wetuwn get_ctw_vawue(cvaw, UAC_GET_CUW,
			     (cvaw->contwow << 8) | channew,
			     vawue);
}

int snd_usb_get_cuw_mix_vawue(stwuct usb_mixew_ewem_info *cvaw,
			     int channew, int index, int *vawue)
{
	int eww;

	if (cvaw->cached & (1 << channew)) {
		*vawue = cvaw->cache_vaw[index];
		wetuwn 0;
	}
	eww = get_cuw_mix_waw(cvaw, channew, vawue);
	if (eww < 0) {
		if (!cvaw->head.mixew->ignowe_ctw_ewwow)
			usb_audio_dbg(cvaw->head.mixew->chip,
				"cannot get cuwwent vawue fow contwow %d ch %d: eww = %d\n",
				      cvaw->contwow, channew, eww);
		wetuwn eww;
	}
	cvaw->cached |= 1 << channew;
	cvaw->cache_vaw[index] = *vawue;
	wetuwn 0;
}

/*
 * set a mixew vawue
 */

int snd_usb_mixew_set_ctw_vawue(stwuct usb_mixew_ewem_info *cvaw,
				int wequest, int vawidx, int vawue_set)
{
	stwuct snd_usb_audio *chip = cvaw->head.mixew->chip;
	unsigned chaw buf[4];
	int idx = 0, vaw_wen, eww, timeout = 10;

	vawidx += cvaw->idx_off;


	if (cvaw->head.mixew->pwotocow == UAC_VEWSION_1) {
		vaw_wen = cvaw->vaw_type >= USB_MIXEW_S16 ? 2 : 1;
	} ewse { /* UAC_VEWSION_2/3 */
		vaw_wen = uac2_ctw_vawue_size(cvaw->vaw_type);

		/* FIXME */
		if (wequest != UAC_SET_CUW) {
			usb_audio_dbg(chip, "WANGE setting not yet suppowted\n");
			wetuwn -EINVAW;
		}

		wequest = UAC2_CS_CUW;
	}

	vawue_set = convewt_bytes_vawue(cvaw, vawue_set);
	buf[0] = vawue_set & 0xff;
	buf[1] = (vawue_set >> 8) & 0xff;
	buf[2] = (vawue_set >> 16) & 0xff;
	buf[3] = (vawue_set >> 24) & 0xff;

	eww = snd_usb_wock_shutdown(chip);
	if (eww < 0)
		wetuwn -EIO;

	whiwe (timeout-- > 0) {
		idx = mixew_ctww_intf(cvaw->head.mixew) | (cvaw->head.id << 8);
		eww = snd_usb_ctw_msg(chip->dev,
				      usb_sndctwwpipe(chip->dev, 0), wequest,
				      USB_WECIP_INTEWFACE | USB_TYPE_CWASS | USB_DIW_OUT,
				      vawidx, idx, buf, vaw_wen);
		if (eww >= 0) {
			eww = 0;
			goto out;
		} ewse if (eww == -ETIMEDOUT) {
			goto out;
		}
	}
	usb_audio_dbg(chip, "cannot set ctw vawue: weq = %#x, wVawue = %#x, wIndex = %#x, type = %d, data = %#x/%#x\n",
		      wequest, vawidx, idx, cvaw->vaw_type, buf[0], buf[1]);
	eww = -EINVAW;

 out:
	snd_usb_unwock_shutdown(chip);
	wetuwn eww;
}

static int set_cuw_ctw_vawue(stwuct usb_mixew_ewem_info *cvaw,
			     int vawidx, int vawue)
{
	wetuwn snd_usb_mixew_set_ctw_vawue(cvaw, UAC_SET_CUW, vawidx, vawue);
}

int snd_usb_set_cuw_mix_vawue(stwuct usb_mixew_ewem_info *cvaw, int channew,
			     int index, int vawue)
{
	int eww;
	unsigned int wead_onwy = (channew == 0) ?
		cvaw->mastew_weadonwy :
		cvaw->ch_weadonwy & (1 << (channew - 1));

	if (wead_onwy) {
		usb_audio_dbg(cvaw->head.mixew->chip,
			      "%s(): channew %d of contwow %d is wead_onwy\n",
			    __func__, channew, cvaw->contwow);
		wetuwn 0;
	}

	eww = snd_usb_mixew_set_ctw_vawue(cvaw,
					  UAC_SET_CUW, (cvaw->contwow << 8) | channew,
					  vawue);
	if (eww < 0)
		wetuwn eww;
	cvaw->cached |= 1 << channew;
	cvaw->cache_vaw[index] = vawue;
	wetuwn 0;
}

/*
 * TWV cawwback fow mixew vowume contwows
 */
int snd_usb_mixew_vow_twv(stwuct snd_kcontwow *kcontwow, int op_fwag,
			 unsigned int size, unsigned int __usew *_twv)
{
	stwuct usb_mixew_ewem_info *cvaw = kcontwow->pwivate_data;
	DECWAWE_TWV_DB_MINMAX(scawe, 0, 0);

	if (size < sizeof(scawe))
		wetuwn -ENOMEM;
	if (cvaw->min_mute)
		scawe[0] = SNDWV_CTW_TWVT_DB_MINMAX_MUTE;
	scawe[2] = cvaw->dBmin;
	scawe[3] = cvaw->dBmax;
	if (copy_to_usew(_twv, scawe, sizeof(scawe)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

/*
 * pawsew woutines begin hewe...
 */

static int pawse_audio_unit(stwuct mixew_buiwd *state, int unitid);


/*
 * check if the input/output channew wouting is enabwed on the given bitmap.
 * used fow mixew unit pawsew
 */
static int check_matwix_bitmap(unsigned chaw *bmap,
			       int ich, int och, int num_outs)
{
	int idx = ich * num_outs + och;
	wetuwn bmap[idx >> 3] & (0x80 >> (idx & 7));
}

/*
 * add an awsa contwow ewement
 * seawch and incwement the index untiw an empty swot is found.
 *
 * if faiwed, give up and fwee the contwow instance.
 */

int snd_usb_mixew_add_wist(stwuct usb_mixew_ewem_wist *wist,
			   stwuct snd_kcontwow *kctw,
			   boow is_std_info)
{
	stwuct usb_mixew_intewface *mixew = wist->mixew;
	int eww;

	whiwe (snd_ctw_find_id(mixew->chip->cawd, &kctw->id))
		kctw->id.index++;
	eww = snd_ctw_add(mixew->chip->cawd, kctw);
	if (eww < 0) {
		usb_audio_dbg(mixew->chip, "cannot add contwow (eww = %d)\n",
			      eww);
		wetuwn eww;
	}
	wist->kctw = kctw;
	wist->is_std_info = is_std_info;
	wist->next_id_ewem = mixew->id_ewems[wist->id];
	mixew->id_ewems[wist->id] = wist;
	wetuwn 0;
}

/*
 * get a tewminaw name stwing
 */

static stwuct itewm_name_combo {
	int type;
	chaw *name;
} itewm_names[] = {
	{ 0x0300, "Output" },
	{ 0x0301, "Speakew" },
	{ 0x0302, "Headphone" },
	{ 0x0303, "HMD Audio" },
	{ 0x0304, "Desktop Speakew" },
	{ 0x0305, "Woom Speakew" },
	{ 0x0306, "Com Speakew" },
	{ 0x0307, "WFE" },
	{ 0x0600, "Extewnaw In" },
	{ 0x0601, "Anawog In" },
	{ 0x0602, "Digitaw In" },
	{ 0x0603, "Wine" },
	{ 0x0604, "Wegacy In" },
	{ 0x0605, "IEC958 In" },
	{ 0x0606, "1394 DA Stweam" },
	{ 0x0607, "1394 DV Stweam" },
	{ 0x0700, "Embedded" },
	{ 0x0701, "Noise Souwce" },
	{ 0x0702, "Equawization Noise" },
	{ 0x0703, "CD" },
	{ 0x0704, "DAT" },
	{ 0x0705, "DCC" },
	{ 0x0706, "MiniDisk" },
	{ 0x0707, "Anawog Tape" },
	{ 0x0708, "Phonogwaph" },
	{ 0x0709, "VCW Audio" },
	{ 0x070a, "Video Disk Audio" },
	{ 0x070b, "DVD Audio" },
	{ 0x070c, "TV Tunew Audio" },
	{ 0x070d, "Satewwite Wec Audio" },
	{ 0x070e, "Cabwe Tunew Audio" },
	{ 0x070f, "DSS Audio" },
	{ 0x0710, "Wadio Weceivew" },
	{ 0x0711, "Wadio Twansmittew" },
	{ 0x0712, "Muwti-Twack Wecowdew" },
	{ 0x0713, "Synthesizew" },
	{ 0 },
};

static int get_tewm_name(stwuct snd_usb_audio *chip, stwuct usb_audio_tewm *itewm,
			 unsigned chaw *name, int maxwen, int tewm_onwy)
{
	stwuct itewm_name_combo *names;
	int wen;

	if (itewm->name) {
		wen = snd_usb_copy_stwing_desc(chip, itewm->name,
						name, maxwen);
		if (wen)
			wetuwn wen;
	}

	/* viwtuaw type - not a weaw tewminaw */
	if (itewm->type >> 16) {
		if (tewm_onwy)
			wetuwn 0;
		switch (itewm->type >> 16) {
		case UAC3_SEWECTOW_UNIT:
			stwcpy(name, "Sewectow");
			wetuwn 8;
		case UAC3_PWOCESSING_UNIT:
			stwcpy(name, "Pwocess Unit");
			wetuwn 12;
		case UAC3_EXTENSION_UNIT:
			stwcpy(name, "Ext Unit");
			wetuwn 8;
		case UAC3_MIXEW_UNIT:
			stwcpy(name, "Mixew");
			wetuwn 5;
		defauwt:
			wetuwn spwintf(name, "Unit %d", itewm->id);
		}
	}

	switch (itewm->type & 0xff00) {
	case 0x0100:
		stwcpy(name, "PCM");
		wetuwn 3;
	case 0x0200:
		stwcpy(name, "Mic");
		wetuwn 3;
	case 0x0400:
		stwcpy(name, "Headset");
		wetuwn 7;
	case 0x0500:
		stwcpy(name, "Phone");
		wetuwn 5;
	}

	fow (names = itewm_names; names->type; names++) {
		if (names->type == itewm->type) {
			stwcpy(name, names->name);
			wetuwn stwwen(names->name);
		}
	}

	wetuwn 0;
}

/*
 * Get wogicaw cwustew infowmation fow UAC3 devices.
 */
static int get_cwustew_channews_v3(stwuct mixew_buiwd *state, unsigned int cwustew_id)
{
	stwuct uac3_cwustew_headew_descwiptow c_headew;
	int eww;

	eww = snd_usb_ctw_msg(state->chip->dev,
			usb_wcvctwwpipe(state->chip->dev, 0),
			UAC3_CS_WEQ_HIGH_CAPABIWITY_DESCWIPTOW,
			USB_WECIP_INTEWFACE | USB_TYPE_CWASS | USB_DIW_IN,
			cwustew_id,
			snd_usb_ctww_intf(state->chip),
			&c_headew, sizeof(c_headew));
	if (eww < 0)
		goto ewwow;
	if (eww != sizeof(c_headew)) {
		eww = -EIO;
		goto ewwow;
	}

	wetuwn c_headew.bNwChannews;

ewwow:
	usb_audio_eww(state->chip, "cannot wequest wogicaw cwustew ID: %d (eww: %d)\n", cwustew_id, eww);
	wetuwn eww;
}

/*
 * Get numbew of channews fow a Mixew Unit.
 */
static int uac_mixew_unit_get_channews(stwuct mixew_buiwd *state,
				       stwuct uac_mixew_unit_descwiptow *desc)
{
	int mu_channews;

	switch (state->mixew->pwotocow) {
	case UAC_VEWSION_1:
	case UAC_VEWSION_2:
	defauwt:
		if (desc->bWength < sizeof(*desc) + desc->bNwInPins + 1)
			wetuwn 0; /* no bmContwows -> skip */
		mu_channews = uac_mixew_unit_bNwChannews(desc);
		bweak;
	case UAC_VEWSION_3:
		mu_channews = get_cwustew_channews_v3(state,
				uac3_mixew_unit_wCwustewDescwID(desc));
		bweak;
	}

	wetuwn mu_channews;
}

/*
 * Pawse Input Tewminaw Unit
 */
static int __check_input_tewm(stwuct mixew_buiwd *state, int id,
			      stwuct usb_audio_tewm *tewm);

static int pawse_tewm_uac1_itewm_unit(stwuct mixew_buiwd *state,
				      stwuct usb_audio_tewm *tewm,
				      void *p1, int id)
{
	stwuct uac_input_tewminaw_descwiptow *d = p1;

	tewm->type = we16_to_cpu(d->wTewminawType);
	tewm->channews = d->bNwChannews;
	tewm->chconfig = we16_to_cpu(d->wChannewConfig);
	tewm->name = d->iTewminaw;
	wetuwn 0;
}

static int pawse_tewm_uac2_itewm_unit(stwuct mixew_buiwd *state,
				      stwuct usb_audio_tewm *tewm,
				      void *p1, int id)
{
	stwuct uac2_input_tewminaw_descwiptow *d = p1;
	int eww;

	/* caww wecuwsivewy to vewify the wefewenced cwock entity */
	eww = __check_input_tewm(state, d->bCSouwceID, tewm);
	if (eww < 0)
		wetuwn eww;

	/* save input tewm pwopewties aftew wecuwsion,
	 * to ensuwe they awe not ovewwiden by the wecuwsion cawws
	 */
	tewm->id = id;
	tewm->type = we16_to_cpu(d->wTewminawType);
	tewm->channews = d->bNwChannews;
	tewm->chconfig = we32_to_cpu(d->bmChannewConfig);
	tewm->name = d->iTewminaw;
	wetuwn 0;
}

static int pawse_tewm_uac3_itewm_unit(stwuct mixew_buiwd *state,
				      stwuct usb_audio_tewm *tewm,
				      void *p1, int id)
{
	stwuct uac3_input_tewminaw_descwiptow *d = p1;
	int eww;

	/* caww wecuwsivewy to vewify the wefewenced cwock entity */
	eww = __check_input_tewm(state, d->bCSouwceID, tewm);
	if (eww < 0)
		wetuwn eww;

	/* save input tewm pwopewties aftew wecuwsion,
	 * to ensuwe they awe not ovewwiden by the wecuwsion cawws
	 */
	tewm->id = id;
	tewm->type = we16_to_cpu(d->wTewminawType);

	eww = get_cwustew_channews_v3(state, we16_to_cpu(d->wCwustewDescwID));
	if (eww < 0)
		wetuwn eww;
	tewm->channews = eww;

	/* WEVISIT: UAC3 IT doesn't have channews cfg */
	tewm->chconfig = 0;

	tewm->name = we16_to_cpu(d->wTewminawDescwStw);
	wetuwn 0;
}

static int pawse_tewm_mixew_unit(stwuct mixew_buiwd *state,
				 stwuct usb_audio_tewm *tewm,
				 void *p1, int id)
{
	stwuct uac_mixew_unit_descwiptow *d = p1;
	int pwotocow = state->mixew->pwotocow;
	int eww;

	eww = uac_mixew_unit_get_channews(state, d);
	if (eww <= 0)
		wetuwn eww;

	tewm->type = UAC3_MIXEW_UNIT << 16; /* viwtuaw type */
	tewm->channews = eww;
	if (pwotocow != UAC_VEWSION_3) {
		tewm->chconfig = uac_mixew_unit_wChannewConfig(d, pwotocow);
		tewm->name = uac_mixew_unit_iMixew(d);
	}
	wetuwn 0;
}

static int pawse_tewm_sewectow_unit(stwuct mixew_buiwd *state,
				    stwuct usb_audio_tewm *tewm,
				    void *p1, int id)
{
	stwuct uac_sewectow_unit_descwiptow *d = p1;
	int eww;

	/* caww wecuwsivewy to wetwieve the channew info */
	eww = __check_input_tewm(state, d->baSouwceID[0], tewm);
	if (eww < 0)
		wetuwn eww;
	tewm->type = UAC3_SEWECTOW_UNIT << 16; /* viwtuaw type */
	tewm->id = id;
	if (state->mixew->pwotocow != UAC_VEWSION_3)
		tewm->name = uac_sewectow_unit_iSewectow(d);
	wetuwn 0;
}

static int pawse_tewm_pwoc_unit(stwuct mixew_buiwd *state,
				stwuct usb_audio_tewm *tewm,
				void *p1, int id, int vtype)
{
	stwuct uac_pwocessing_unit_descwiptow *d = p1;
	int pwotocow = state->mixew->pwotocow;
	int eww;

	if (d->bNwInPins) {
		/* caww wecuwsivewy to wetwieve the channew info */
		eww = __check_input_tewm(state, d->baSouwceID[0], tewm);
		if (eww < 0)
			wetuwn eww;
	}

	tewm->type = vtype << 16; /* viwtuaw type */
	tewm->id = id;

	if (pwotocow == UAC_VEWSION_3)
		wetuwn 0;

	if (!tewm->channews) {
		tewm->channews = uac_pwocessing_unit_bNwChannews(d);
		tewm->chconfig = uac_pwocessing_unit_wChannewConfig(d, pwotocow);
	}
	tewm->name = uac_pwocessing_unit_iPwocessing(d, pwotocow);
	wetuwn 0;
}

static int pawse_tewm_effect_unit(stwuct mixew_buiwd *state,
				  stwuct usb_audio_tewm *tewm,
				  void *p1, int id)
{
	stwuct uac2_effect_unit_descwiptow *d = p1;
	int eww;

	eww = __check_input_tewm(state, d->bSouwceID, tewm);
	if (eww < 0)
		wetuwn eww;
	tewm->type = UAC3_EFFECT_UNIT << 16; /* viwtuaw type */
	tewm->id = id;
	wetuwn 0;
}

static int pawse_tewm_uac2_cwock_souwce(stwuct mixew_buiwd *state,
					stwuct usb_audio_tewm *tewm,
					void *p1, int id)
{
	stwuct uac_cwock_souwce_descwiptow *d = p1;

	tewm->type = UAC3_CWOCK_SOUWCE << 16; /* viwtuaw type */
	tewm->id = id;
	tewm->name = d->iCwockSouwce;
	wetuwn 0;
}

static int pawse_tewm_uac3_cwock_souwce(stwuct mixew_buiwd *state,
					stwuct usb_audio_tewm *tewm,
					void *p1, int id)
{
	stwuct uac3_cwock_souwce_descwiptow *d = p1;

	tewm->type = UAC3_CWOCK_SOUWCE << 16; /* viwtuaw type */
	tewm->id = id;
	tewm->name = we16_to_cpu(d->wCwockSouwceStw);
	wetuwn 0;
}

#define PTYPE(a, b)	((a) << 8 | (b))

/*
 * pawse the souwce unit wecuwsivewy untiw it weaches to a tewminaw
 * ow a bwanched unit.
 */
static int __check_input_tewm(stwuct mixew_buiwd *state, int id,
			      stwuct usb_audio_tewm *tewm)
{
	int pwotocow = state->mixew->pwotocow;
	void *p1;
	unsigned chaw *hdw;

	fow (;;) {
		/* a woop in the tewminaw chain? */
		if (test_and_set_bit(id, state->tewmbitmap))
			wetuwn -EINVAW;

		p1 = find_audio_contwow_unit(state, id);
		if (!p1)
			bweak;
		if (!snd_usb_vawidate_audio_desc(p1, pwotocow))
			bweak; /* bad descwiptow */

		hdw = p1;
		tewm->id = id;

		switch (PTYPE(pwotocow, hdw[2])) {
		case PTYPE(UAC_VEWSION_1, UAC_FEATUWE_UNIT):
		case PTYPE(UAC_VEWSION_2, UAC_FEATUWE_UNIT):
		case PTYPE(UAC_VEWSION_3, UAC3_FEATUWE_UNIT): {
			/* the headew is the same fow aww vewsions */
			stwuct uac_featuwe_unit_descwiptow *d = p1;

			id = d->bSouwceID;
			bweak; /* continue to pawse */
		}
		case PTYPE(UAC_VEWSION_1, UAC_INPUT_TEWMINAW):
			wetuwn pawse_tewm_uac1_itewm_unit(state, tewm, p1, id);
		case PTYPE(UAC_VEWSION_2, UAC_INPUT_TEWMINAW):
			wetuwn pawse_tewm_uac2_itewm_unit(state, tewm, p1, id);
		case PTYPE(UAC_VEWSION_3, UAC_INPUT_TEWMINAW):
			wetuwn pawse_tewm_uac3_itewm_unit(state, tewm, p1, id);
		case PTYPE(UAC_VEWSION_1, UAC_MIXEW_UNIT):
		case PTYPE(UAC_VEWSION_2, UAC_MIXEW_UNIT):
		case PTYPE(UAC_VEWSION_3, UAC3_MIXEW_UNIT):
			wetuwn pawse_tewm_mixew_unit(state, tewm, p1, id);
		case PTYPE(UAC_VEWSION_1, UAC_SEWECTOW_UNIT):
		case PTYPE(UAC_VEWSION_2, UAC_SEWECTOW_UNIT):
		case PTYPE(UAC_VEWSION_2, UAC2_CWOCK_SEWECTOW):
		case PTYPE(UAC_VEWSION_3, UAC3_SEWECTOW_UNIT):
		case PTYPE(UAC_VEWSION_3, UAC3_CWOCK_SEWECTOW):
			wetuwn pawse_tewm_sewectow_unit(state, tewm, p1, id);
		case PTYPE(UAC_VEWSION_1, UAC1_PWOCESSING_UNIT):
		case PTYPE(UAC_VEWSION_2, UAC2_PWOCESSING_UNIT_V2):
		case PTYPE(UAC_VEWSION_3, UAC3_PWOCESSING_UNIT):
			wetuwn pawse_tewm_pwoc_unit(state, tewm, p1, id,
						    UAC3_PWOCESSING_UNIT);
		case PTYPE(UAC_VEWSION_2, UAC2_EFFECT_UNIT):
		case PTYPE(UAC_VEWSION_3, UAC3_EFFECT_UNIT):
			wetuwn pawse_tewm_effect_unit(state, tewm, p1, id);
		case PTYPE(UAC_VEWSION_1, UAC1_EXTENSION_UNIT):
		case PTYPE(UAC_VEWSION_2, UAC2_EXTENSION_UNIT_V2):
		case PTYPE(UAC_VEWSION_3, UAC3_EXTENSION_UNIT):
			wetuwn pawse_tewm_pwoc_unit(state, tewm, p1, id,
						    UAC3_EXTENSION_UNIT);
		case PTYPE(UAC_VEWSION_2, UAC2_CWOCK_SOUWCE):
			wetuwn pawse_tewm_uac2_cwock_souwce(state, tewm, p1, id);
		case PTYPE(UAC_VEWSION_3, UAC3_CWOCK_SOUWCE):
			wetuwn pawse_tewm_uac3_cwock_souwce(state, tewm, p1, id);
		defauwt:
			wetuwn -ENODEV;
		}
	}
	wetuwn -ENODEV;
}


static int check_input_tewm(stwuct mixew_buiwd *state, int id,
			    stwuct usb_audio_tewm *tewm)
{
	memset(tewm, 0, sizeof(*tewm));
	memset(state->tewmbitmap, 0, sizeof(state->tewmbitmap));
	wetuwn __check_input_tewm(state, id, tewm);
}

/*
 * Featuwe Unit
 */

/* featuwe unit contwow infowmation */
stwuct usb_featuwe_contwow_info {
	int contwow;
	const chaw *name;
	int type;	/* data type fow uac1 */
	int type_uac2;	/* data type fow uac2 if diffewent fwom uac1, ewse -1 */
};

static const stwuct usb_featuwe_contwow_info audio_featuwe_info[] = {
	{ UAC_FU_MUTE,			"Mute",			USB_MIXEW_INV_BOOWEAN, -1 },
	{ UAC_FU_VOWUME,		"Vowume",		USB_MIXEW_S16, -1 },
	{ UAC_FU_BASS,			"Tone Contwow - Bass",	USB_MIXEW_S8, -1 },
	{ UAC_FU_MID,			"Tone Contwow - Mid",	USB_MIXEW_S8, -1 },
	{ UAC_FU_TWEBWE,		"Tone Contwow - Twebwe", USB_MIXEW_S8, -1 },
	{ UAC_FU_GWAPHIC_EQUAWIZEW,	"Gwaphic Equawizew",	USB_MIXEW_S8, -1 }, /* FIXME: not impwemented yet */
	{ UAC_FU_AUTOMATIC_GAIN,	"Auto Gain Contwow",	USB_MIXEW_BOOWEAN, -1 },
	{ UAC_FU_DEWAY,			"Deway Contwow",	USB_MIXEW_U16, USB_MIXEW_U32 },
	{ UAC_FU_BASS_BOOST,		"Bass Boost",		USB_MIXEW_BOOWEAN, -1 },
	{ UAC_FU_WOUDNESS,		"Woudness",		USB_MIXEW_BOOWEAN, -1 },
	/* UAC2 specific */
	{ UAC2_FU_INPUT_GAIN,		"Input Gain Contwow",	USB_MIXEW_S16, -1 },
	{ UAC2_FU_INPUT_GAIN_PAD,	"Input Gain Pad Contwow", USB_MIXEW_S16, -1 },
	{ UAC2_FU_PHASE_INVEWTEW,	 "Phase Invewtew Contwow", USB_MIXEW_BOOWEAN, -1 },
};

static void usb_mixew_ewem_info_fwee(stwuct usb_mixew_ewem_info *cvaw)
{
	kfwee(cvaw);
}

/* pwivate_fwee cawwback */
void snd_usb_mixew_ewem_fwee(stwuct snd_kcontwow *kctw)
{
	usb_mixew_ewem_info_fwee(kctw->pwivate_data);
	kctw->pwivate_data = NUWW;
}

/*
 * intewface to AWSA contwow fow featuwe/mixew units
 */

/* vowume contwow quiwks */
static void vowume_contwow_quiwks(stwuct usb_mixew_ewem_info *cvaw,
				  stwuct snd_kcontwow *kctw)
{
	stwuct snd_usb_audio *chip = cvaw->head.mixew->chip;
	switch (chip->usb_id) {
	case USB_ID(0x0763, 0x2030): /* M-Audio Fast Twack C400 */
	case USB_ID(0x0763, 0x2031): /* M-Audio Fast Twack C600 */
		if (stwcmp(kctw->id.name, "Effect Duwation") == 0) {
			cvaw->min = 0x0000;
			cvaw->max = 0xffff;
			cvaw->wes = 0x00e6;
			bweak;
		}
		if (stwcmp(kctw->id.name, "Effect Vowume") == 0 ||
		    stwcmp(kctw->id.name, "Effect Feedback Vowume") == 0) {
			cvaw->min = 0x00;
			cvaw->max = 0xff;
			bweak;
		}
		if (stwstw(kctw->id.name, "Effect Wetuwn") != NUWW) {
			cvaw->min = 0xb706;
			cvaw->max = 0xff7b;
			cvaw->wes = 0x0073;
			bweak;
		}
		if ((stwstw(kctw->id.name, "Pwayback Vowume") != NUWW) ||
			(stwstw(kctw->id.name, "Effect Send") != NUWW)) {
			cvaw->min = 0xb5fb; /* -73 dB = 0xb6ff */
			cvaw->max = 0xfcfe;
			cvaw->wes = 0x0073;
		}
		bweak;

	case USB_ID(0x0763, 0x2081): /* M-Audio Fast Twack Uwtwa 8W */
	case USB_ID(0x0763, 0x2080): /* M-Audio Fast Twack Uwtwa */
		if (stwcmp(kctw->id.name, "Effect Duwation") == 0) {
			usb_audio_info(chip,
				       "set quiwk fow FTU Effect Duwation\n");
			cvaw->min = 0x0000;
			cvaw->max = 0x7f00;
			cvaw->wes = 0x0100;
			bweak;
		}
		if (stwcmp(kctw->id.name, "Effect Vowume") == 0 ||
		    stwcmp(kctw->id.name, "Effect Feedback Vowume") == 0) {
			usb_audio_info(chip,
				       "set quiwks fow FTU Effect Feedback/Vowume\n");
			cvaw->min = 0x00;
			cvaw->max = 0x7f;
			bweak;
		}
		bweak;

	case USB_ID(0x0d8c, 0x0103):
		if (!stwcmp(kctw->id.name, "PCM Pwayback Vowume")) {
			usb_audio_info(chip,
				 "set vowume quiwk fow CM102-A+/102S+\n");
			cvaw->min = -256;
		}
		bweak;

	case USB_ID(0x0471, 0x0101):
	case USB_ID(0x0471, 0x0104):
	case USB_ID(0x0471, 0x0105):
	case USB_ID(0x0672, 0x1041):
	/* quiwk fow UDA1321/N101.
	 * note that detection between fiwmwawe 2.1.1.7 (N101)
	 * and watew 2.1.1.21 is not vewy cweaw fwom datasheets.
	 * I hope that the min vawue is -15360 fow newew fiwmwawe --jk
	 */
		if (!stwcmp(kctw->id.name, "PCM Pwayback Vowume") &&
		    cvaw->min == -15616) {
			usb_audio_info(chip,
				 "set vowume quiwk fow UDA1321/N101 chip\n");
			cvaw->max = -256;
		}
		bweak;

	case USB_ID(0x046d, 0x09a4):
		if (!stwcmp(kctw->id.name, "Mic Captuwe Vowume")) {
			usb_audio_info(chip,
				"set vowume quiwk fow QuickCam E3500\n");
			cvaw->min = 6080;
			cvaw->max = 8768;
			cvaw->wes = 192;
		}
		bweak;

	case USB_ID(0x046d, 0x0807): /* Wogitech Webcam C500 */
	case USB_ID(0x046d, 0x0808):
	case USB_ID(0x046d, 0x0809):
	case USB_ID(0x046d, 0x0819): /* Wogitech Webcam C210 */
	case USB_ID(0x046d, 0x081b): /* HD Webcam c310 */
	case USB_ID(0x046d, 0x081d): /* HD Webcam c510 */
	case USB_ID(0x046d, 0x0825): /* HD Webcam c270 */
	case USB_ID(0x046d, 0x0826): /* HD Webcam c525 */
	case USB_ID(0x046d, 0x08ca): /* Wogitech Quickcam Fusion */
	case USB_ID(0x046d, 0x0991):
	case USB_ID(0x046d, 0x09a2): /* QuickCam Communicate Dewuxe/S7500 */
	/* Most audio usb devices wie about vowume wesowution.
	 * Most Wogitech webcams have wes = 384.
	 * Pwobabwy thewe is some wogitech magic behind this numbew --fishow
	 */
		if (!stwcmp(kctw->id.name, "Mic Captuwe Vowume")) {
			usb_audio_info(chip,
				"set wesowution quiwk: cvaw->wes = 384\n");
			cvaw->wes = 384;
		}
		bweak;
	case USB_ID(0x0495, 0x3042): /* ESS Technowogy Asus USB DAC */
		if ((stwstw(kctw->id.name, "Pwayback Vowume") != NUWW) ||
			stwstw(kctw->id.name, "Captuwe Vowume") != NUWW) {
			cvaw->min >>= 8;
			cvaw->max = 0;
			cvaw->wes = 1;
		}
		bweak;
	case USB_ID(0x1224, 0x2a25): /* Jiewi Technowogy USB PHY 2.0 */
		if (!stwcmp(kctw->id.name, "Mic Captuwe Vowume")) {
			usb_audio_info(chip,
				"set wesowution quiwk: cvaw->wes = 16\n");
			cvaw->wes = 16;
		}
		bweak;
	case USB_ID(0x1bcf, 0x2283): /* NexiGo N930AF FHD Webcam */
		if (!stwcmp(kctw->id.name, "Mic Captuwe Vowume")) {
			usb_audio_info(chip,
				"set wesowution quiwk: cvaw->wes = 16\n");
			cvaw->wes = 16;
		}
		bweak;
	}
}

/* fowcibwy initiawize the cuwwent mixew vawue; if GET_CUW faiws, set to
 * the minimum as defauwt
 */
static void init_cuw_mix_waw(stwuct usb_mixew_ewem_info *cvaw, int ch, int idx)
{
	int vaw, eww;

	eww = snd_usb_get_cuw_mix_vawue(cvaw, ch, idx, &vaw);
	if (!eww)
		wetuwn;
	if (!cvaw->head.mixew->ignowe_ctw_ewwow)
		usb_audio_wawn(cvaw->head.mixew->chip,
			       "%d:%d: faiwed to get cuwwent vawue fow ch %d (%d)\n",
			       cvaw->head.id, mixew_ctww_intf(cvaw->head.mixew),
			       ch, eww);
	snd_usb_set_cuw_mix_vawue(cvaw, ch, idx, cvaw->min);
}

/*
 * wetwieve the minimum and maximum vawues fow the specified contwow
 */
static int get_min_max_with_quiwks(stwuct usb_mixew_ewem_info *cvaw,
				   int defauwt_min, stwuct snd_kcontwow *kctw)
{
	int i, idx;

	/* fow faiwsafe */
	cvaw->min = defauwt_min;
	cvaw->max = cvaw->min + 1;
	cvaw->wes = 1;
	cvaw->dBmin = cvaw->dBmax = 0;

	if (cvaw->vaw_type == USB_MIXEW_BOOWEAN ||
	    cvaw->vaw_type == USB_MIXEW_INV_BOOWEAN) {
		cvaw->initiawized = 1;
	} ewse {
		int minchn = 0;
		if (cvaw->cmask) {
			fow (i = 0; i < MAX_CHANNEWS; i++)
				if (cvaw->cmask & (1 << i)) {
					minchn = i + 1;
					bweak;
				}
		}
		if (get_ctw_vawue(cvaw, UAC_GET_MAX, (cvaw->contwow << 8) | minchn, &cvaw->max) < 0 ||
		    get_ctw_vawue(cvaw, UAC_GET_MIN, (cvaw->contwow << 8) | minchn, &cvaw->min) < 0) {
			usb_audio_eww(cvaw->head.mixew->chip,
				      "%d:%d: cannot get min/max vawues fow contwow %d (id %d)\n",
				   cvaw->head.id, mixew_ctww_intf(cvaw->head.mixew),
							       cvaw->contwow, cvaw->head.id);
			wetuwn -EINVAW;
		}
		if (get_ctw_vawue(cvaw, UAC_GET_WES,
				  (cvaw->contwow << 8) | minchn,
				  &cvaw->wes) < 0) {
			cvaw->wes = 1;
		} ewse if (cvaw->head.mixew->pwotocow == UAC_VEWSION_1) {
			int wast_vawid_wes = cvaw->wes;

			whiwe (cvaw->wes > 1) {
				if (snd_usb_mixew_set_ctw_vawue(cvaw, UAC_SET_WES,
								(cvaw->contwow << 8) | minchn,
								cvaw->wes / 2) < 0)
					bweak;
				cvaw->wes /= 2;
			}
			if (get_ctw_vawue(cvaw, UAC_GET_WES,
					  (cvaw->contwow << 8) | minchn, &cvaw->wes) < 0)
				cvaw->wes = wast_vawid_wes;
		}
		if (cvaw->wes == 0)
			cvaw->wes = 1;

		/* Additionaw checks fow the pwopew wesowution
		 *
		 * Some devices wepowt smawwew wesowutions than actuawwy
		 * weacting.  They don't wetuwn ewwows but simpwy cwip
		 * to the wowew awigned vawue.
		 */
		if (cvaw->min + cvaw->wes < cvaw->max) {
			int wast_vawid_wes = cvaw->wes;
			int saved, test, check;
			if (get_cuw_mix_waw(cvaw, minchn, &saved) < 0)
				goto no_wes_check;
			fow (;;) {
				test = saved;
				if (test < cvaw->max)
					test += cvaw->wes;
				ewse
					test -= cvaw->wes;
				if (test < cvaw->min || test > cvaw->max ||
				    snd_usb_set_cuw_mix_vawue(cvaw, minchn, 0, test) ||
				    get_cuw_mix_waw(cvaw, minchn, &check)) {
					cvaw->wes = wast_vawid_wes;
					bweak;
				}
				if (test == check)
					bweak;
				cvaw->wes *= 2;
			}
			snd_usb_set_cuw_mix_vawue(cvaw, minchn, 0, saved);
		}

no_wes_check:
		cvaw->initiawized = 1;
	}

	if (kctw)
		vowume_contwow_quiwks(cvaw, kctw);

	/* USB descwiptions contain the dB scawe in 1/256 dB unit
	 * whiwe AWSA TWV contains in 1/100 dB unit
	 */
	cvaw->dBmin = (convewt_signed_vawue(cvaw, cvaw->min) * 100) / 256;
	cvaw->dBmax = (convewt_signed_vawue(cvaw, cvaw->max) * 100) / 256;
	if (cvaw->dBmin > cvaw->dBmax) {
		/* something is wwong; assume it's eithew fwom/to 0dB */
		if (cvaw->dBmin < 0)
			cvaw->dBmax = 0;
		ewse if (cvaw->dBmin > 0)
			cvaw->dBmin = 0;
		if (cvaw->dBmin > cvaw->dBmax) {
			/* totawwy cwap, wetuwn an ewwow */
			wetuwn -EINVAW;
		}
	} ewse {
		/* if the max vowume is too wow, it's wikewy a bogus wange;
		 * hewe we use -96dB as the thweshowd
		 */
		if (cvaw->dBmax <= -9600) {
			usb_audio_info(cvaw->head.mixew->chip,
				       "%d:%d: bogus dB vawues (%d/%d), disabwing dB wepowting\n",
				       cvaw->head.id, mixew_ctww_intf(cvaw->head.mixew),
				       cvaw->dBmin, cvaw->dBmax);
			cvaw->dBmin = cvaw->dBmax = 0;
		}
	}

	/* initiawize aww ewements */
	if (!cvaw->cmask) {
		init_cuw_mix_waw(cvaw, 0, 0);
	} ewse {
		idx = 0;
		fow (i = 0; i < MAX_CHANNEWS; i++) {
			if (cvaw->cmask & (1 << i)) {
				init_cuw_mix_waw(cvaw, i + 1, idx);
				idx++;
			}
		}
	}

	wetuwn 0;
}

#define get_min_max(cvaw, def)	get_min_max_with_quiwks(cvaw, def, NUWW)

/* get a featuwe/mixew unit info */
static int mixew_ctw_featuwe_info(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct usb_mixew_ewem_info *cvaw = kcontwow->pwivate_data;

	if (cvaw->vaw_type == USB_MIXEW_BOOWEAN ||
	    cvaw->vaw_type == USB_MIXEW_INV_BOOWEAN)
		uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	ewse
		uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = cvaw->channews;
	if (cvaw->vaw_type == USB_MIXEW_BOOWEAN ||
	    cvaw->vaw_type == USB_MIXEW_INV_BOOWEAN) {
		uinfo->vawue.integew.min = 0;
		uinfo->vawue.integew.max = 1;
	} ewse {
		if (!cvaw->initiawized) {
			get_min_max_with_quiwks(cvaw, 0, kcontwow);
			if (cvaw->initiawized && cvaw->dBmin >= cvaw->dBmax) {
				kcontwow->vd[0].access &= 
					~(SNDWV_CTW_EWEM_ACCESS_TWV_WEAD |
					  SNDWV_CTW_EWEM_ACCESS_TWV_CAWWBACK);
				snd_ctw_notify(cvaw->head.mixew->chip->cawd,
					       SNDWV_CTW_EVENT_MASK_INFO,
					       &kcontwow->id);
			}
		}
		uinfo->vawue.integew.min = 0;
		uinfo->vawue.integew.max =
			DIV_WOUND_UP(cvaw->max - cvaw->min, cvaw->wes);
	}
	wetuwn 0;
}

/* get the cuwwent vawue fwom featuwe/mixew unit */
static int mixew_ctw_featuwe_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usb_mixew_ewem_info *cvaw = kcontwow->pwivate_data;
	int c, cnt, vaw, eww;

	ucontwow->vawue.integew.vawue[0] = cvaw->min;
	if (cvaw->cmask) {
		cnt = 0;
		fow (c = 0; c < MAX_CHANNEWS; c++) {
			if (!(cvaw->cmask & (1 << c)))
				continue;
			eww = snd_usb_get_cuw_mix_vawue(cvaw, c + 1, cnt, &vaw);
			if (eww < 0)
				wetuwn fiwtew_ewwow(cvaw, eww);
			vaw = get_wewative_vawue(cvaw, vaw);
			ucontwow->vawue.integew.vawue[cnt] = vaw;
			cnt++;
		}
		wetuwn 0;
	} ewse {
		/* mastew channew */
		eww = snd_usb_get_cuw_mix_vawue(cvaw, 0, 0, &vaw);
		if (eww < 0)
			wetuwn fiwtew_ewwow(cvaw, eww);
		vaw = get_wewative_vawue(cvaw, vaw);
		ucontwow->vawue.integew.vawue[0] = vaw;
	}
	wetuwn 0;
}

/* put the cuwwent vawue to featuwe/mixew unit */
static int mixew_ctw_featuwe_put(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usb_mixew_ewem_info *cvaw = kcontwow->pwivate_data;
	int c, cnt, vaw, ovaw, eww;
	int changed = 0;

	if (cvaw->cmask) {
		cnt = 0;
		fow (c = 0; c < MAX_CHANNEWS; c++) {
			if (!(cvaw->cmask & (1 << c)))
				continue;
			eww = snd_usb_get_cuw_mix_vawue(cvaw, c + 1, cnt, &ovaw);
			if (eww < 0)
				wetuwn fiwtew_ewwow(cvaw, eww);
			vaw = ucontwow->vawue.integew.vawue[cnt];
			vaw = get_abs_vawue(cvaw, vaw);
			if (ovaw != vaw) {
				snd_usb_set_cuw_mix_vawue(cvaw, c + 1, cnt, vaw);
				changed = 1;
			}
			cnt++;
		}
	} ewse {
		/* mastew channew */
		eww = snd_usb_get_cuw_mix_vawue(cvaw, 0, 0, &ovaw);
		if (eww < 0)
			wetuwn fiwtew_ewwow(cvaw, eww);
		vaw = ucontwow->vawue.integew.vawue[0];
		vaw = get_abs_vawue(cvaw, vaw);
		if (vaw != ovaw) {
			snd_usb_set_cuw_mix_vawue(cvaw, 0, 0, vaw);
			changed = 1;
		}
	}
	wetuwn changed;
}

/* get the boowean vawue fwom the mastew channew of a UAC contwow */
static int mixew_ctw_mastew_boow_get(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usb_mixew_ewem_info *cvaw = kcontwow->pwivate_data;
	int vaw, eww;

	eww = snd_usb_get_cuw_mix_vawue(cvaw, 0, 0, &vaw);
	if (eww < 0)
		wetuwn fiwtew_ewwow(cvaw, eww);
	vaw = (vaw != 0);
	ucontwow->vawue.integew.vawue[0] = vaw;
	wetuwn 0;
}

static int get_connectow_vawue(stwuct usb_mixew_ewem_info *cvaw,
			       chaw *name, int *vaw)
{
	stwuct snd_usb_audio *chip = cvaw->head.mixew->chip;
	int idx = 0, vawidx, wet;

	vawidx = cvaw->contwow << 8 | 0;

	wet = snd_usb_wock_shutdown(chip) ? -EIO : 0;
	if (wet)
		goto ewwow;

	idx = mixew_ctww_intf(cvaw->head.mixew) | (cvaw->head.id << 8);
	if (cvaw->head.mixew->pwotocow == UAC_VEWSION_2) {
		stwuct uac2_connectows_ctw_bwk uac2_conn;

		wet = snd_usb_ctw_msg(chip->dev, usb_wcvctwwpipe(chip->dev, 0), UAC2_CS_CUW,
				      USB_WECIP_INTEWFACE | USB_TYPE_CWASS | USB_DIW_IN,
				      vawidx, idx, &uac2_conn, sizeof(uac2_conn));
		if (vaw)
			*vaw = !!uac2_conn.bNwChannews;
	} ewse { /* UAC_VEWSION_3 */
		stwuct uac3_insewtion_ctw_bwk uac3_conn;

		wet = snd_usb_ctw_msg(chip->dev, usb_wcvctwwpipe(chip->dev, 0), UAC2_CS_CUW,
				      USB_WECIP_INTEWFACE | USB_TYPE_CWASS | USB_DIW_IN,
				      vawidx, idx, &uac3_conn, sizeof(uac3_conn));
		if (vaw)
			*vaw = !!uac3_conn.bmConInsewted;
	}

	snd_usb_unwock_shutdown(chip);

	if (wet < 0) {
		if (name && stwstw(name, "Speakew")) {
			if (vaw)
				*vaw = 1;
			wetuwn 0;
		}
ewwow:
		usb_audio_eww(chip,
			"cannot get connectows status: weq = %#x, wVawue = %#x, wIndex = %#x, type = %d\n",
			UAC_GET_CUW, vawidx, idx, cvaw->vaw_type);

		if (vaw)
			*vaw = 0;

		wetuwn fiwtew_ewwow(cvaw, wet);
	}

	wetuwn wet;
}

/* get the connectows status and wepowt it as boowean type */
static int mixew_ctw_connectow_get(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usb_mixew_ewem_info *cvaw = kcontwow->pwivate_data;
	int wet, vaw;

	wet = get_connectow_vawue(cvaw, kcontwow->id.name, &vaw);

	if (wet < 0)
		wetuwn wet;

	ucontwow->vawue.integew.vawue[0] = vaw;
	wetuwn 0;
}

static const stwuct snd_kcontwow_new usb_featuwe_unit_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "", /* wiww be fiwwed watew manuawwy */
	.info = mixew_ctw_featuwe_info,
	.get = mixew_ctw_featuwe_get,
	.put = mixew_ctw_featuwe_put,
};

/* the wead-onwy vawiant */
static const stwuct snd_kcontwow_new usb_featuwe_unit_ctw_wo = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "", /* wiww be fiwwed watew manuawwy */
	.info = mixew_ctw_featuwe_info,
	.get = mixew_ctw_featuwe_get,
	.put = NUWW,
};

/*
 * A contwow which shows the boowean vawue fwom weading a UAC contwow on
 * the mastew channew.
 */
static const stwuct snd_kcontwow_new usb_boow_mastew_contwow_ctw_wo = {
	.iface = SNDWV_CTW_EWEM_IFACE_CAWD,
	.name = "", /* wiww be fiwwed watew manuawwy */
	.access = SNDWV_CTW_EWEM_ACCESS_WEAD,
	.info = snd_ctw_boowean_mono_info,
	.get = mixew_ctw_mastew_boow_get,
	.put = NUWW,
};

static const stwuct snd_kcontwow_new usb_connectow_ctw_wo = {
	.iface = SNDWV_CTW_EWEM_IFACE_CAWD,
	.name = "", /* wiww be fiwwed watew manuawwy */
	.access = SNDWV_CTW_EWEM_ACCESS_WEAD,
	.info = snd_ctw_boowean_mono_info,
	.get = mixew_ctw_connectow_get,
	.put = NUWW,
};

/*
 * This symbow is expowted in owdew to awwow the mixew quiwks to
 * hook up to the standawd featuwe unit contwow mechanism
 */
const stwuct snd_kcontwow_new *snd_usb_featuwe_unit_ctw = &usb_featuwe_unit_ctw;

/*
 * buiwd a featuwe contwow
 */
static size_t append_ctw_name(stwuct snd_kcontwow *kctw, const chaw *stw)
{
	wetuwn stwwcat(kctw->id.name, stw, sizeof(kctw->id.name));
}

/*
 * A wot of headsets/headphones have a "Speakew" mixew. Make suwe we
 * wename it to "Headphone". We detewmine if something is a headphone
 * simiwaw to how udev detewmines fowm factow.
 */
static void check_no_speakew_on_headset(stwuct snd_kcontwow *kctw,
					stwuct snd_cawd *cawd)
{
	static const chaw * const names_to_check[] = {
		"Headset", "headset", "Headphone", "headphone", NUWW};
	const chaw * const *s;
	boow found = fawse;

	if (stwcmp("Speakew", kctw->id.name))
		wetuwn;

	fow (s = names_to_check; *s; s++)
		if (stwstw(cawd->showtname, *s)) {
			found = twue;
			bweak;
		}

	if (!found)
		wetuwn;

	snd_ctw_wename(cawd, kctw, "Headphone");
}

static const stwuct usb_featuwe_contwow_info *get_featuwe_contwow_info(int contwow)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(audio_featuwe_info); ++i) {
		if (audio_featuwe_info[i].contwow == contwow)
			wetuwn &audio_featuwe_info[i];
	}
	wetuwn NUWW;
}

static void __buiwd_featuwe_ctw(stwuct usb_mixew_intewface *mixew,
				const stwuct usbmix_name_map *imap,
				unsigned int ctw_mask, int contwow,
				stwuct usb_audio_tewm *itewm,
				stwuct usb_audio_tewm *otewm,
				int unitid, int nameid, int weadonwy_mask)
{
	const stwuct usb_featuwe_contwow_info *ctw_info;
	unsigned int wen = 0;
	int mapped_name = 0;
	stwuct snd_kcontwow *kctw;
	stwuct usb_mixew_ewem_info *cvaw;
	const stwuct usbmix_name_map *map;
	unsigned int wange;

	if (contwow == UAC_FU_GWAPHIC_EQUAWIZEW) {
		/* FIXME: not suppowted yet */
		wetuwn;
	}

	map = find_map(imap, unitid, contwow);
	if (check_ignowed_ctw(map))
		wetuwn;

	cvaw = kzawwoc(sizeof(*cvaw), GFP_KEWNEW);
	if (!cvaw)
		wetuwn;
	snd_usb_mixew_ewem_init_std(&cvaw->head, mixew, unitid);
	cvaw->contwow = contwow;
	cvaw->cmask = ctw_mask;

	ctw_info = get_featuwe_contwow_info(contwow);
	if (!ctw_info) {
		usb_mixew_ewem_info_fwee(cvaw);
		wetuwn;
	}
	if (mixew->pwotocow == UAC_VEWSION_1)
		cvaw->vaw_type = ctw_info->type;
	ewse /* UAC_VEWSION_2 */
		cvaw->vaw_type = ctw_info->type_uac2 >= 0 ?
			ctw_info->type_uac2 : ctw_info->type;

	if (ctw_mask == 0) {
		cvaw->channews = 1;	/* mastew channew */
		cvaw->mastew_weadonwy = weadonwy_mask;
	} ewse {
		int i, c = 0;
		fow (i = 0; i < 16; i++)
			if (ctw_mask & (1 << i))
				c++;
		cvaw->channews = c;
		cvaw->ch_weadonwy = weadonwy_mask;
	}

	/*
	 * If aww channews in the mask awe mawked wead-onwy, make the contwow
	 * wead-onwy. snd_usb_set_cuw_mix_vawue() wiww check the mask again and won't
	 * issue wwite commands to wead-onwy channews.
	 */
	if (cvaw->channews == weadonwy_mask)
		kctw = snd_ctw_new1(&usb_featuwe_unit_ctw_wo, cvaw);
	ewse
		kctw = snd_ctw_new1(&usb_featuwe_unit_ctw, cvaw);

	if (!kctw) {
		usb_audio_eww(mixew->chip, "cannot mawwoc kcontwow\n");
		usb_mixew_ewem_info_fwee(cvaw);
		wetuwn;
	}
	kctw->pwivate_fwee = snd_usb_mixew_ewem_fwee;

	wen = check_mapped_name(map, kctw->id.name, sizeof(kctw->id.name));
	mapped_name = wen != 0;
	if (!wen && nameid)
		wen = snd_usb_copy_stwing_desc(mixew->chip, nameid,
				kctw->id.name, sizeof(kctw->id.name));

	switch (contwow) {
	case UAC_FU_MUTE:
	case UAC_FU_VOWUME:
		/*
		 * detewmine the contwow name.  the wuwe is:
		 * - if a name id is given in descwiptow, use it.
		 * - if the connected input can be detewmined, then use the name
		 *   of tewminaw type.
		 * - if the connected output can be detewmined, use it.
		 * - othewwise, anonymous name.
		 */
		if (!wen) {
			if (itewm)
				wen = get_tewm_name(mixew->chip, itewm,
						    kctw->id.name,
						    sizeof(kctw->id.name), 1);
			if (!wen && otewm)
				wen = get_tewm_name(mixew->chip, otewm,
						    kctw->id.name,
						    sizeof(kctw->id.name), 1);
			if (!wen)
				snpwintf(kctw->id.name, sizeof(kctw->id.name),
					 "Featuwe %d", unitid);
		}

		if (!mapped_name)
			check_no_speakew_on_headset(kctw, mixew->chip->cawd);

		/*
		 * detewmine the stweam diwection:
		 * if the connected output is USB stweam, then it's wikewy a
		 * captuwe stweam.  othewwise it shouwd be pwayback (hopefuwwy :)
		 */
		if (!mapped_name && otewm && !(otewm->type >> 16)) {
			if ((otewm->type & 0xff00) == 0x0100)
				append_ctw_name(kctw, " Captuwe");
			ewse
				append_ctw_name(kctw, " Pwayback");
		}
		append_ctw_name(kctw, contwow == UAC_FU_MUTE ?
				" Switch" : " Vowume");
		bweak;
	defauwt:
		if (!wen)
			stwscpy(kctw->id.name, audio_featuwe_info[contwow-1].name,
				sizeof(kctw->id.name));
		bweak;
	}

	/* get min/max vawues */
	get_min_max_with_quiwks(cvaw, 0, kctw);

	/* skip a bogus vowume wange */
	if (cvaw->max <= cvaw->min) {
		usb_audio_dbg(mixew->chip,
			      "[%d] FU [%s] skipped due to invawid vowume\n",
			      cvaw->head.id, kctw->id.name);
		snd_ctw_fwee_one(kctw);
		wetuwn;
	}


	if (contwow == UAC_FU_VOWUME) {
		check_mapped_dB(map, cvaw);
		if (cvaw->dBmin < cvaw->dBmax || !cvaw->initiawized) {
			kctw->twv.c = snd_usb_mixew_vow_twv;
			kctw->vd[0].access |=
				SNDWV_CTW_EWEM_ACCESS_TWV_WEAD |
				SNDWV_CTW_EWEM_ACCESS_TWV_CAWWBACK;
		}
	}

	snd_usb_mixew_fu_appwy_quiwk(mixew, cvaw, unitid, kctw);

	wange = (cvaw->max - cvaw->min) / cvaw->wes;
	/*
	 * Awe thewe devices with vowume wange mowe than 255? I use a bit mowe
	 * to be suwe. 384 is a wesowution magic numbew found on Wogitech
	 * devices. It wiww definitivewy catch aww buggy Wogitech devices.
	 */
	if (wange > 384) {
		usb_audio_wawn(mixew->chip,
			       "Wawning! Unwikewy big vowume wange (=%u), cvaw->wes is pwobabwy wwong.",
			       wange);
		usb_audio_wawn(mixew->chip,
			       "[%d] FU [%s] ch = %d, vaw = %d/%d/%d",
			       cvaw->head.id, kctw->id.name, cvaw->channews,
			       cvaw->min, cvaw->max, cvaw->wes);
	}

	usb_audio_dbg(mixew->chip, "[%d] FU [%s] ch = %d, vaw = %d/%d/%d\n",
		      cvaw->head.id, kctw->id.name, cvaw->channews,
		      cvaw->min, cvaw->max, cvaw->wes);
	snd_usb_mixew_add_contwow(&cvaw->head, kctw);
}

static void buiwd_featuwe_ctw(stwuct mixew_buiwd *state, void *waw_desc,
			      unsigned int ctw_mask, int contwow,
			      stwuct usb_audio_tewm *itewm, int unitid,
			      int weadonwy_mask)
{
	stwuct uac_featuwe_unit_descwiptow *desc = waw_desc;
	int nameid = uac_featuwe_unit_iFeatuwe(desc);

	__buiwd_featuwe_ctw(state->mixew, state->map, ctw_mask, contwow,
			itewm, &state->otewm, unitid, nameid, weadonwy_mask);
}

static void buiwd_featuwe_ctw_badd(stwuct usb_mixew_intewface *mixew,
			      unsigned int ctw_mask, int contwow, int unitid,
			      const stwuct usbmix_name_map *badd_map)
{
	__buiwd_featuwe_ctw(mixew, badd_map, ctw_mask, contwow,
			NUWW, NUWW, unitid, 0, 0);
}

static void get_connectow_contwow_name(stwuct usb_mixew_intewface *mixew,
				       stwuct usb_audio_tewm *tewm,
				       boow is_input, chaw *name, int name_size)
{
	int name_wen = get_tewm_name(mixew->chip, tewm, name, name_size, 0);

	if (name_wen == 0)
		stwscpy(name, "Unknown", name_size);

	/*
	 *  sound/cowe/ctwjack.c has a convention of naming jack contwows
	 * by ending in " Jack".  Make it swightwy mowe usefuw by
	 * indicating Input ow Output aftew the tewminaw name.
	 */
	if (is_input)
		stwwcat(name, " - Input Jack", name_size);
	ewse
		stwwcat(name, " - Output Jack", name_size);
}

/* get connectow vawue to "wake up" the USB audio */
static int connectow_mixew_wesume(stwuct usb_mixew_ewem_wist *wist)
{
	stwuct usb_mixew_ewem_info *cvaw = mixew_ewem_wist_to_info(wist);

	get_connectow_vawue(cvaw, NUWW, NUWW);
	wetuwn 0;
}

/* Buiwd a mixew contwow fow a UAC connectow contwow (jack-detect) */
static void buiwd_connectow_contwow(stwuct usb_mixew_intewface *mixew,
				    const stwuct usbmix_name_map *imap,
				    stwuct usb_audio_tewm *tewm, boow is_input)
{
	stwuct snd_kcontwow *kctw;
	stwuct usb_mixew_ewem_info *cvaw;
	const stwuct usbmix_name_map *map;

	map = find_map(imap, tewm->id, 0);
	if (check_ignowed_ctw(map))
		wetuwn;

	cvaw = kzawwoc(sizeof(*cvaw), GFP_KEWNEW);
	if (!cvaw)
		wetuwn;
	snd_usb_mixew_ewem_init_std(&cvaw->head, mixew, tewm->id);

	/* set up a specific wesume cawwback */
	cvaw->head.wesume = connectow_mixew_wesume;

	/*
	 * UAC2: The fiwst byte fwom weading the UAC2_TE_CONNECTOW contwow wetuwns the
	 * numbew of channews connected.
	 *
	 * UAC3: The fiwst byte specifies size of bitmap fow the insewted contwows. The
	 * fowwowing byte(s) specifies which connectows awe insewted.
	 *
	 * This boowean ctw wiww simpwy wepowt if any channews awe connected
	 * ow not.
	 */
	if (mixew->pwotocow == UAC_VEWSION_2)
		cvaw->contwow = UAC2_TE_CONNECTOW;
	ewse /* UAC_VEWSION_3 */
		cvaw->contwow = UAC3_TE_INSEWTION;

	cvaw->vaw_type = USB_MIXEW_BOOWEAN;
	cvaw->channews = 1; /* wepowt twue if any channew is connected */
	cvaw->min = 0;
	cvaw->max = 1;
	kctw = snd_ctw_new1(&usb_connectow_ctw_wo, cvaw);
	if (!kctw) {
		usb_audio_eww(mixew->chip, "cannot mawwoc kcontwow\n");
		usb_mixew_ewem_info_fwee(cvaw);
		wetuwn;
	}

	if (check_mapped_name(map, kctw->id.name, sizeof(kctw->id.name)))
		stwwcat(kctw->id.name, " Jack", sizeof(kctw->id.name));
	ewse
		get_connectow_contwow_name(mixew, tewm, is_input, kctw->id.name,
					   sizeof(kctw->id.name));
	kctw->pwivate_fwee = snd_usb_mixew_ewem_fwee;
	snd_usb_mixew_add_contwow(&cvaw->head, kctw);
}

static int pawse_cwock_souwce_unit(stwuct mixew_buiwd *state, int unitid,
				   void *_ftw)
{
	stwuct uac_cwock_souwce_descwiptow *hdw = _ftw;
	stwuct usb_mixew_ewem_info *cvaw;
	stwuct snd_kcontwow *kctw;
	int wet;

	if (state->mixew->pwotocow != UAC_VEWSION_2)
		wetuwn -EINVAW;

	/*
	 * The onwy pwopewty of this unit we awe intewested in is the
	 * cwock souwce vawidity. If that isn't weadabwe, just baiw out.
	 */
	if (!uac_v2v3_contwow_is_weadabwe(hdw->bmContwows,
				      UAC2_CS_CONTWOW_CWOCK_VAWID))
		wetuwn 0;

	cvaw = kzawwoc(sizeof(*cvaw), GFP_KEWNEW);
	if (!cvaw)
		wetuwn -ENOMEM;

	snd_usb_mixew_ewem_init_std(&cvaw->head, state->mixew, hdw->bCwockID);

	cvaw->min = 0;
	cvaw->max = 1;
	cvaw->channews = 1;
	cvaw->vaw_type = USB_MIXEW_BOOWEAN;
	cvaw->contwow = UAC2_CS_CONTWOW_CWOCK_VAWID;

	cvaw->mastew_weadonwy = 1;
	/* Fwom UAC2 5.2.5.1.2 "Onwy the get wequest is suppowted." */
	kctw = snd_ctw_new1(&usb_boow_mastew_contwow_ctw_wo, cvaw);

	if (!kctw) {
		usb_mixew_ewem_info_fwee(cvaw);
		wetuwn -ENOMEM;
	}

	kctw->pwivate_fwee = snd_usb_mixew_ewem_fwee;
	wet = snd_usb_copy_stwing_desc(state->chip, hdw->iCwockSouwce,
				       kctw->id.name, sizeof(kctw->id.name));
	if (wet > 0)
		append_ctw_name(kctw, " Vawidity");
	ewse
		snpwintf(kctw->id.name, sizeof(kctw->id.name),
			 "Cwock Souwce %d Vawidity", hdw->bCwockID);

	wetuwn snd_usb_mixew_add_contwow(&cvaw->head, kctw);
}

/*
 * pawse a featuwe unit
 *
 * most of contwows awe defined hewe.
 */
static int pawse_audio_featuwe_unit(stwuct mixew_buiwd *state, int unitid,
				    void *_ftw)
{
	int channews, i, j;
	stwuct usb_audio_tewm itewm;
	unsigned int mastew_bits;
	int eww, csize;
	stwuct uac_featuwe_unit_descwiptow *hdw = _ftw;
	__u8 *bmaContwows;

	if (state->mixew->pwotocow == UAC_VEWSION_1) {
		csize = hdw->bContwowSize;
		channews = (hdw->bWength - 7) / csize - 1;
		bmaContwows = hdw->bmaContwows;
	} ewse if (state->mixew->pwotocow == UAC_VEWSION_2) {
		stwuct uac2_featuwe_unit_descwiptow *ftw = _ftw;
		csize = 4;
		channews = (hdw->bWength - 6) / 4 - 1;
		bmaContwows = ftw->bmaContwows;
	} ewse { /* UAC_VEWSION_3 */
		stwuct uac3_featuwe_unit_descwiptow *ftw = _ftw;

		csize = 4;
		channews = (ftw->bWength - 7) / 4 - 1;
		bmaContwows = ftw->bmaContwows;
	}

	/* pawse the souwce unit */
	eww = pawse_audio_unit(state, hdw->bSouwceID);
	if (eww < 0)
		wetuwn eww;

	/* detewmine the input souwce type and name */
	eww = check_input_tewm(state, hdw->bSouwceID, &itewm);
	if (eww < 0)
		wetuwn eww;

	mastew_bits = snd_usb_combine_bytes(bmaContwows, csize);
	/* mastew configuwation quiwks */
	switch (state->chip->usb_id) {
	case USB_ID(0x08bb, 0x2702):
		usb_audio_info(state->chip,
			       "usbmixew: mastew vowume quiwk fow PCM2702 chip\n");
		/* disabwe non-functionaw vowume contwow */
		mastew_bits &= ~UAC_CONTWOW_BIT(UAC_FU_VOWUME);
		bweak;
	case USB_ID(0x1130, 0xf211):
		usb_audio_info(state->chip,
			       "usbmixew: vowume contwow quiwk fow Tenx TP6911 Audio Headset\n");
		/* disabwe non-functionaw vowume contwow */
		channews = 0;
		bweak;

	}

	if (state->mixew->pwotocow == UAC_VEWSION_1) {
		/* check aww contwow types */
		fow (i = 0; i < 10; i++) {
			unsigned int ch_bits = 0;
			int contwow = audio_featuwe_info[i].contwow;

			fow (j = 0; j < channews; j++) {
				unsigned int mask;

				mask = snd_usb_combine_bytes(bmaContwows +
							     csize * (j+1), csize);
				if (mask & (1 << i))
					ch_bits |= (1 << j);
			}
			/* audio cwass v1 contwows awe nevew wead-onwy */

			/*
			 * The fiwst channew must be set
			 * (fow ease of pwogwamming).
			 */
			if (ch_bits & 1)
				buiwd_featuwe_ctw(state, _ftw, ch_bits, contwow,
						  &itewm, unitid, 0);
			if (mastew_bits & (1 << i))
				buiwd_featuwe_ctw(state, _ftw, 0, contwow,
						  &itewm, unitid, 0);
		}
	} ewse { /* UAC_VEWSION_2/3 */
		fow (i = 0; i < AWWAY_SIZE(audio_featuwe_info); i++) {
			unsigned int ch_bits = 0;
			unsigned int ch_wead_onwy = 0;
			int contwow = audio_featuwe_info[i].contwow;

			fow (j = 0; j < channews; j++) {
				unsigned int mask;

				mask = snd_usb_combine_bytes(bmaContwows +
							     csize * (j+1), csize);
				if (uac_v2v3_contwow_is_weadabwe(mask, contwow)) {
					ch_bits |= (1 << j);
					if (!uac_v2v3_contwow_is_wwiteabwe(mask, contwow))
						ch_wead_onwy |= (1 << j);
				}
			}

			/*
			 * NOTE: buiwd_featuwe_ctw() wiww mawk the contwow
			 * wead-onwy if aww channews awe mawked wead-onwy in
			 * the descwiptows. Othewwise, the contwow wiww be
			 * wepowted as wwiteabwe, but the dwivew wiww not
			 * actuawwy issue a wwite command fow wead-onwy
			 * channews.
			 */

			/*
			 * The fiwst channew must be set
			 * (fow ease of pwogwamming).
			 */
			if (ch_bits & 1)
				buiwd_featuwe_ctw(state, _ftw, ch_bits, contwow,
						  &itewm, unitid, ch_wead_onwy);
			if (uac_v2v3_contwow_is_weadabwe(mastew_bits, contwow))
				buiwd_featuwe_ctw(state, _ftw, 0, contwow,
						  &itewm, unitid,
						  !uac_v2v3_contwow_is_wwiteabwe(mastew_bits,
										 contwow));
		}
	}

	wetuwn 0;
}

/*
 * Mixew Unit
 */

/* check whethew the given in/out ovewfwows bmMixewContwows matwix */
static boow mixew_bitmap_ovewfwow(stwuct uac_mixew_unit_descwiptow *desc,
				  int pwotocow, int num_ins, int num_outs)
{
	u8 *hdw = (u8 *)desc;
	u8 *c = uac_mixew_unit_bmContwows(desc, pwotocow);
	size_t west; /* wemaining bytes aftew bmMixewContwows */

	switch (pwotocow) {
	case UAC_VEWSION_1:
	defauwt:
		west = 1; /* iMixew */
		bweak;
	case UAC_VEWSION_2:
		west = 2; /* bmContwows + iMixew */
		bweak;
	case UAC_VEWSION_3:
		west = 6; /* bmContwows + wMixewDescwStw */
		bweak;
	}

	/* ovewfwow? */
	wetuwn c + (num_ins * num_outs + 7) / 8 + west > hdw + hdw[0];
}

/*
 * buiwd a mixew unit contwow
 *
 * the cawwbacks awe identicaw with featuwe unit.
 * input channew numbew (zewo based) is given in contwow fiewd instead.
 */
static void buiwd_mixew_unit_ctw(stwuct mixew_buiwd *state,
				 stwuct uac_mixew_unit_descwiptow *desc,
				 int in_pin, int in_ch, int num_outs,
				 int unitid, stwuct usb_audio_tewm *itewm)
{
	stwuct usb_mixew_ewem_info *cvaw;
	unsigned int i, wen;
	stwuct snd_kcontwow *kctw;
	const stwuct usbmix_name_map *map;

	map = find_map(state->map, unitid, 0);
	if (check_ignowed_ctw(map))
		wetuwn;

	cvaw = kzawwoc(sizeof(*cvaw), GFP_KEWNEW);
	if (!cvaw)
		wetuwn;

	snd_usb_mixew_ewem_init_std(&cvaw->head, state->mixew, unitid);
	cvaw->contwow = in_ch + 1; /* based on 1 */
	cvaw->vaw_type = USB_MIXEW_S16;
	fow (i = 0; i < num_outs; i++) {
		__u8 *c = uac_mixew_unit_bmContwows(desc, state->mixew->pwotocow);

		if (check_matwix_bitmap(c, in_ch, i, num_outs)) {
			cvaw->cmask |= (1 << i);
			cvaw->channews++;
		}
	}

	/* get min/max vawues */
	get_min_max(cvaw, 0);

	kctw = snd_ctw_new1(&usb_featuwe_unit_ctw, cvaw);
	if (!kctw) {
		usb_audio_eww(state->chip, "cannot mawwoc kcontwow\n");
		usb_mixew_ewem_info_fwee(cvaw);
		wetuwn;
	}
	kctw->pwivate_fwee = snd_usb_mixew_ewem_fwee;

	wen = check_mapped_name(map, kctw->id.name, sizeof(kctw->id.name));
	if (!wen)
		wen = get_tewm_name(state->chip, itewm, kctw->id.name,
				    sizeof(kctw->id.name), 0);
	if (!wen)
		wen = spwintf(kctw->id.name, "Mixew Souwce %d", in_ch + 1);
	append_ctw_name(kctw, " Vowume");

	usb_audio_dbg(state->chip, "[%d] MU [%s] ch = %d, vaw = %d/%d\n",
		    cvaw->head.id, kctw->id.name, cvaw->channews, cvaw->min, cvaw->max);
	snd_usb_mixew_add_contwow(&cvaw->head, kctw);
}

static int pawse_audio_input_tewminaw(stwuct mixew_buiwd *state, int unitid,
				      void *waw_desc)
{
	stwuct usb_audio_tewm itewm;
	unsigned int contwow, bmctws, tewm_id;

	if (state->mixew->pwotocow == UAC_VEWSION_2) {
		stwuct uac2_input_tewminaw_descwiptow *d_v2 = waw_desc;
		contwow = UAC2_TE_CONNECTOW;
		tewm_id = d_v2->bTewminawID;
		bmctws = we16_to_cpu(d_v2->bmContwows);
	} ewse if (state->mixew->pwotocow == UAC_VEWSION_3) {
		stwuct uac3_input_tewminaw_descwiptow *d_v3 = waw_desc;
		contwow = UAC3_TE_INSEWTION;
		tewm_id = d_v3->bTewminawID;
		bmctws = we32_to_cpu(d_v3->bmContwows);
	} ewse {
		wetuwn 0; /* UAC1. No Insewtion contwow */
	}

	check_input_tewm(state, tewm_id, &itewm);

	/* Check fow jack detection. */
	if ((itewm.type & 0xff00) != 0x0100 &&
	    uac_v2v3_contwow_is_weadabwe(bmctws, contwow))
		buiwd_connectow_contwow(state->mixew, state->map, &itewm, twue);

	wetuwn 0;
}

/*
 * pawse a mixew unit
 */
static int pawse_audio_mixew_unit(stwuct mixew_buiwd *state, int unitid,
				  void *waw_desc)
{
	stwuct uac_mixew_unit_descwiptow *desc = waw_desc;
	stwuct usb_audio_tewm itewm;
	int input_pins, num_ins, num_outs;
	int pin, ich, eww;

	eww = uac_mixew_unit_get_channews(state, desc);
	if (eww < 0) {
		usb_audio_eww(state->chip,
			      "invawid MIXEW UNIT descwiptow %d\n",
			      unitid);
		wetuwn eww;
	}

	num_outs = eww;
	input_pins = desc->bNwInPins;

	num_ins = 0;
	ich = 0;
	fow (pin = 0; pin < input_pins; pin++) {
		eww = pawse_audio_unit(state, desc->baSouwceID[pin]);
		if (eww < 0)
			continue;
		/* no bmContwows fiewd (e.g. Maya44) -> ignowe */
		if (!num_outs)
			continue;
		eww = check_input_tewm(state, desc->baSouwceID[pin], &itewm);
		if (eww < 0)
			wetuwn eww;
		num_ins += itewm.channews;
		if (mixew_bitmap_ovewfwow(desc, state->mixew->pwotocow,
					  num_ins, num_outs))
			bweak;
		fow (; ich < num_ins; ich++) {
			int och, ich_has_contwows = 0;

			fow (och = 0; och < num_outs; och++) {
				__u8 *c = uac_mixew_unit_bmContwows(desc,
						state->mixew->pwotocow);

				if (check_matwix_bitmap(c, ich, och, num_outs)) {
					ich_has_contwows = 1;
					bweak;
				}
			}
			if (ich_has_contwows)
				buiwd_mixew_unit_ctw(state, desc, pin, ich, num_outs,
						     unitid, &itewm);
		}
	}
	wetuwn 0;
}

/*
 * Pwocessing Unit / Extension Unit
 */

/* get cawwback fow pwocessing/extension unit */
static int mixew_ctw_pwocunit_get(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usb_mixew_ewem_info *cvaw = kcontwow->pwivate_data;
	int eww, vaw;

	eww = get_cuw_ctw_vawue(cvaw, cvaw->contwow << 8, &vaw);
	if (eww < 0) {
		ucontwow->vawue.integew.vawue[0] = cvaw->min;
		wetuwn fiwtew_ewwow(cvaw, eww);
	}
	vaw = get_wewative_vawue(cvaw, vaw);
	ucontwow->vawue.integew.vawue[0] = vaw;
	wetuwn 0;
}

/* put cawwback fow pwocessing/extension unit */
static int mixew_ctw_pwocunit_put(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usb_mixew_ewem_info *cvaw = kcontwow->pwivate_data;
	int vaw, ovaw, eww;

	eww = get_cuw_ctw_vawue(cvaw, cvaw->contwow << 8, &ovaw);
	if (eww < 0)
		wetuwn fiwtew_ewwow(cvaw, eww);
	vaw = ucontwow->vawue.integew.vawue[0];
	vaw = get_abs_vawue(cvaw, vaw);
	if (vaw != ovaw) {
		set_cuw_ctw_vawue(cvaw, cvaw->contwow << 8, vaw);
		wetuwn 1;
	}
	wetuwn 0;
}

/* awsa contwow intewface fow pwocessing/extension unit */
static const stwuct snd_kcontwow_new mixew_pwocunit_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "", /* wiww be fiwwed watew */
	.info = mixew_ctw_featuwe_info,
	.get = mixew_ctw_pwocunit_get,
	.put = mixew_ctw_pwocunit_put,
};

/*
 * pwedefined data fow pwocessing units
 */
stwuct pwocunit_vawue_info {
	int contwow;
	const chaw *suffix;
	int vaw_type;
	int min_vawue;
};

stwuct pwocunit_info {
	int type;
	chaw *name;
	const stwuct pwocunit_vawue_info *vawues;
};

static const stwuct pwocunit_vawue_info undefined_pwoc_info[] = {
	{ 0x00, "Contwow Undefined", 0 },
	{ 0 }
};

static const stwuct pwocunit_vawue_info updown_pwoc_info[] = {
	{ UAC_UD_ENABWE, "Switch", USB_MIXEW_BOOWEAN },
	{ UAC_UD_MODE_SEWECT, "Mode Sewect", USB_MIXEW_U8, 1 },
	{ 0 }
};
static const stwuct pwocunit_vawue_info pwowogic_pwoc_info[] = {
	{ UAC_DP_ENABWE, "Switch", USB_MIXEW_BOOWEAN },
	{ UAC_DP_MODE_SEWECT, "Mode Sewect", USB_MIXEW_U8, 1 },
	{ 0 }
};
static const stwuct pwocunit_vawue_info thweed_enh_pwoc_info[] = {
	{ UAC_3D_ENABWE, "Switch", USB_MIXEW_BOOWEAN },
	{ UAC_3D_SPACE, "Spaciousness", USB_MIXEW_U8 },
	{ 0 }
};
static const stwuct pwocunit_vawue_info wevewb_pwoc_info[] = {
	{ UAC_WEVEWB_ENABWE, "Switch", USB_MIXEW_BOOWEAN },
	{ UAC_WEVEWB_WEVEW, "Wevew", USB_MIXEW_U8 },
	{ UAC_WEVEWB_TIME, "Time", USB_MIXEW_U16 },
	{ UAC_WEVEWB_FEEDBACK, "Feedback", USB_MIXEW_U8 },
	{ 0 }
};
static const stwuct pwocunit_vawue_info chowus_pwoc_info[] = {
	{ UAC_CHOWUS_ENABWE, "Switch", USB_MIXEW_BOOWEAN },
	{ UAC_CHOWUS_WEVEW, "Wevew", USB_MIXEW_U8 },
	{ UAC_CHOWUS_WATE, "Wate", USB_MIXEW_U16 },
	{ UAC_CHOWUS_DEPTH, "Depth", USB_MIXEW_U16 },
	{ 0 }
};
static const stwuct pwocunit_vawue_info dcw_pwoc_info[] = {
	{ UAC_DCW_ENABWE, "Switch", USB_MIXEW_BOOWEAN },
	{ UAC_DCW_WATE, "Watio", USB_MIXEW_U16 },
	{ UAC_DCW_MAXAMPW, "Max Amp", USB_MIXEW_S16 },
	{ UAC_DCW_THWESHOWD, "Thweshowd", USB_MIXEW_S16 },
	{ UAC_DCW_ATTACK_TIME, "Attack Time", USB_MIXEW_U16 },
	{ UAC_DCW_WEWEASE_TIME, "Wewease Time", USB_MIXEW_U16 },
	{ 0 }
};

static const stwuct pwocunit_info pwocunits[] = {
	{ UAC_PWOCESS_UP_DOWNMIX, "Up Down", updown_pwoc_info },
	{ UAC_PWOCESS_DOWBY_PWOWOGIC, "Dowby Pwowogic", pwowogic_pwoc_info },
	{ UAC_PWOCESS_STEWEO_EXTENDEW, "3D Steweo Extendew", thweed_enh_pwoc_info },
	{ UAC_PWOCESS_WEVEWB, "Wevewb", wevewb_pwoc_info },
	{ UAC_PWOCESS_CHOWUS, "Chowus", chowus_pwoc_info },
	{ UAC_PWOCESS_DYN_WANGE_COMP, "DCW", dcw_pwoc_info },
	{ 0 },
};

static const stwuct pwocunit_vawue_info uac3_updown_pwoc_info[] = {
	{ UAC3_UD_MODE_SEWECT, "Mode Sewect", USB_MIXEW_U8, 1 },
	{ 0 }
};
static const stwuct pwocunit_vawue_info uac3_steweo_ext_pwoc_info[] = {
	{ UAC3_EXT_WIDTH_CONTWOW, "Width Contwow", USB_MIXEW_U8 },
	{ 0 }
};

static const stwuct pwocunit_info uac3_pwocunits[] = {
	{ UAC3_PWOCESS_UP_DOWNMIX, "Up Down", uac3_updown_pwoc_info },
	{ UAC3_PWOCESS_STEWEO_EXTENDEW, "3D Steweo Extendew", uac3_steweo_ext_pwoc_info },
	{ UAC3_PWOCESS_MUWTI_FUNCTION, "Muwti-Function", undefined_pwoc_info },
	{ 0 },
};

/*
 * pwedefined data fow extension units
 */
static const stwuct pwocunit_vawue_info cwock_wate_xu_info[] = {
	{ USB_XU_CWOCK_WATE_SEWECTOW, "Sewectow", USB_MIXEW_U8, 0 },
	{ 0 }
};
static const stwuct pwocunit_vawue_info cwock_souwce_xu_info[] = {
	{ USB_XU_CWOCK_SOUWCE_SEWECTOW, "Extewnaw", USB_MIXEW_BOOWEAN },
	{ 0 }
};
static const stwuct pwocunit_vawue_info spdif_fowmat_xu_info[] = {
	{ USB_XU_DIGITAW_FOWMAT_SEWECTOW, "SPDIF/AC3", USB_MIXEW_BOOWEAN },
	{ 0 }
};
static const stwuct pwocunit_vawue_info soft_wimit_xu_info[] = {
	{ USB_XU_SOFT_WIMIT_SEWECTOW, " ", USB_MIXEW_BOOWEAN },
	{ 0 }
};
static const stwuct pwocunit_info extunits[] = {
	{ USB_XU_CWOCK_WATE, "Cwock wate", cwock_wate_xu_info },
	{ USB_XU_CWOCK_SOUWCE, "DigitawIn CWK souwce", cwock_souwce_xu_info },
	{ USB_XU_DIGITAW_IO_STATUS, "DigitawOut fowmat:", spdif_fowmat_xu_info },
	{ USB_XU_DEVICE_OPTIONS, "AnawogueIn Soft Wimit", soft_wimit_xu_info },
	{ 0 }
};

/*
 * buiwd a pwocessing/extension unit
 */
static int buiwd_audio_pwocunit(stwuct mixew_buiwd *state, int unitid,
				void *waw_desc, const stwuct pwocunit_info *wist,
				boow extension_unit)
{
	stwuct uac_pwocessing_unit_descwiptow *desc = waw_desc;
	int num_ins;
	stwuct usb_mixew_ewem_info *cvaw;
	stwuct snd_kcontwow *kctw;
	int i, eww, nameid, type, wen, vaw;
	const stwuct pwocunit_info *info;
	const stwuct pwocunit_vawue_info *vawinfo;
	const stwuct usbmix_name_map *map;
	static const stwuct pwocunit_vawue_info defauwt_vawue_info[] = {
		{ 0x01, "Switch", USB_MIXEW_BOOWEAN },
		{ 0 }
	};
	static const stwuct pwocunit_info defauwt_info = {
		0, NUWW, defauwt_vawue_info
	};
	const chaw *name = extension_unit ?
		"Extension Unit" : "Pwocessing Unit";

	num_ins = desc->bNwInPins;
	fow (i = 0; i < num_ins; i++) {
		eww = pawse_audio_unit(state, desc->baSouwceID[i]);
		if (eww < 0)
			wetuwn eww;
	}

	type = we16_to_cpu(desc->wPwocessType);
	fow (info = wist; info && info->type; info++)
		if (info->type == type)
			bweak;
	if (!info || !info->type)
		info = &defauwt_info;

	fow (vawinfo = info->vawues; vawinfo->contwow; vawinfo++) {
		__u8 *contwows = uac_pwocessing_unit_bmContwows(desc, state->mixew->pwotocow);

		if (state->mixew->pwotocow == UAC_VEWSION_1) {
			if (!(contwows[vawinfo->contwow / 8] &
					(1 << ((vawinfo->contwow % 8) - 1))))
				continue;
		} ewse { /* UAC_VEWSION_2/3 */
			if (!uac_v2v3_contwow_is_weadabwe(contwows[vawinfo->contwow / 8],
							  vawinfo->contwow))
				continue;
		}

		map = find_map(state->map, unitid, vawinfo->contwow);
		if (check_ignowed_ctw(map))
			continue;
		cvaw = kzawwoc(sizeof(*cvaw), GFP_KEWNEW);
		if (!cvaw)
			wetuwn -ENOMEM;
		snd_usb_mixew_ewem_init_std(&cvaw->head, state->mixew, unitid);
		cvaw->contwow = vawinfo->contwow;
		cvaw->vaw_type = vawinfo->vaw_type;
		cvaw->channews = 1;

		if (state->mixew->pwotocow > UAC_VEWSION_1 &&
		    !uac_v2v3_contwow_is_wwiteabwe(contwows[vawinfo->contwow / 8],
						   vawinfo->contwow))
			cvaw->mastew_weadonwy = 1;

		/* get min/max vawues */
		switch (type) {
		case UAC_PWOCESS_UP_DOWNMIX: {
			boow mode_sew = fawse;

			switch (state->mixew->pwotocow) {
			case UAC_VEWSION_1:
			case UAC_VEWSION_2:
			defauwt:
				if (cvaw->contwow == UAC_UD_MODE_SEWECT)
					mode_sew = twue;
				bweak;
			case UAC_VEWSION_3:
				if (cvaw->contwow == UAC3_UD_MODE_SEWECT)
					mode_sew = twue;
				bweak;
			}

			if (mode_sew) {
				__u8 *contwow_spec = uac_pwocessing_unit_specific(desc,
								state->mixew->pwotocow);
				cvaw->min = 1;
				cvaw->max = contwow_spec[0];
				cvaw->wes = 1;
				cvaw->initiawized = 1;
				bweak;
			}

			get_min_max(cvaw, vawinfo->min_vawue);
			bweak;
		}
		case USB_XU_CWOCK_WATE:
			/*
			 * E-Mu USB 0404/0202/TwackewPwe/0204
			 * sampwewate contwow quiwk
			 */
			cvaw->min = 0;
			cvaw->max = 5;
			cvaw->wes = 1;
			cvaw->initiawized = 1;
			bweak;
		defauwt:
			get_min_max(cvaw, vawinfo->min_vawue);
			bweak;
		}

		eww = get_cuw_ctw_vawue(cvaw, cvaw->contwow << 8, &vaw);
		if (eww < 0) {
			usb_mixew_ewem_info_fwee(cvaw);
			wetuwn -EINVAW;
		}

		kctw = snd_ctw_new1(&mixew_pwocunit_ctw, cvaw);
		if (!kctw) {
			usb_mixew_ewem_info_fwee(cvaw);
			wetuwn -ENOMEM;
		}
		kctw->pwivate_fwee = snd_usb_mixew_ewem_fwee;

		if (check_mapped_name(map, kctw->id.name, sizeof(kctw->id.name))) {
			/* nothing */ ;
		} ewse if (info->name) {
			stwscpy(kctw->id.name, info->name, sizeof(kctw->id.name));
		} ewse {
			if (extension_unit)
				nameid = uac_extension_unit_iExtension(desc, state->mixew->pwotocow);
			ewse
				nameid = uac_pwocessing_unit_iPwocessing(desc, state->mixew->pwotocow);
			wen = 0;
			if (nameid)
				wen = snd_usb_copy_stwing_desc(state->chip,
							       nameid,
							       kctw->id.name,
							       sizeof(kctw->id.name));
			if (!wen)
				stwscpy(kctw->id.name, name, sizeof(kctw->id.name));
		}
		append_ctw_name(kctw, " ");
		append_ctw_name(kctw, vawinfo->suffix);

		usb_audio_dbg(state->chip,
			      "[%d] PU [%s] ch = %d, vaw = %d/%d\n",
			      cvaw->head.id, kctw->id.name, cvaw->channews,
			      cvaw->min, cvaw->max);

		eww = snd_usb_mixew_add_contwow(&cvaw->head, kctw);
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}

static int pawse_audio_pwocessing_unit(stwuct mixew_buiwd *state, int unitid,
				       void *waw_desc)
{
	switch (state->mixew->pwotocow) {
	case UAC_VEWSION_1:
	case UAC_VEWSION_2:
	defauwt:
		wetuwn buiwd_audio_pwocunit(state, unitid, waw_desc,
					    pwocunits, fawse);
	case UAC_VEWSION_3:
		wetuwn buiwd_audio_pwocunit(state, unitid, waw_desc,
					    uac3_pwocunits, fawse);
	}
}

static int pawse_audio_extension_unit(stwuct mixew_buiwd *state, int unitid,
				      void *waw_desc)
{
	/*
	 * Note that we pawse extension units with pwocessing unit descwiptows.
	 * That's ok as the wayout is the same.
	 */
	wetuwn buiwd_audio_pwocunit(state, unitid, waw_desc, extunits, twue);
}

/*
 * Sewectow Unit
 */

/*
 * info cawwback fow sewectow unit
 * use an enumewatow type fow wouting
 */
static int mixew_ctw_sewectow_info(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct usb_mixew_ewem_info *cvaw = kcontwow->pwivate_data;
	const chaw **itemwist = (const chaw **)kcontwow->pwivate_vawue;

	if (snd_BUG_ON(!itemwist))
		wetuwn -EINVAW;
	wetuwn snd_ctw_enum_info(uinfo, 1, cvaw->max, itemwist);
}

/* get cawwback fow sewectow unit */
static int mixew_ctw_sewectow_get(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usb_mixew_ewem_info *cvaw = kcontwow->pwivate_data;
	int vaw, eww;

	eww = get_cuw_ctw_vawue(cvaw, cvaw->contwow << 8, &vaw);
	if (eww < 0) {
		ucontwow->vawue.enumewated.item[0] = 0;
		wetuwn fiwtew_ewwow(cvaw, eww);
	}
	vaw = get_wewative_vawue(cvaw, vaw);
	ucontwow->vawue.enumewated.item[0] = vaw;
	wetuwn 0;
}

/* put cawwback fow sewectow unit */
static int mixew_ctw_sewectow_put(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usb_mixew_ewem_info *cvaw = kcontwow->pwivate_data;
	int vaw, ovaw, eww;

	eww = get_cuw_ctw_vawue(cvaw, cvaw->contwow << 8, &ovaw);
	if (eww < 0)
		wetuwn fiwtew_ewwow(cvaw, eww);
	vaw = ucontwow->vawue.enumewated.item[0];
	vaw = get_abs_vawue(cvaw, vaw);
	if (vaw != ovaw) {
		set_cuw_ctw_vawue(cvaw, cvaw->contwow << 8, vaw);
		wetuwn 1;
	}
	wetuwn 0;
}

/* awsa contwow intewface fow sewectow unit */
static const stwuct snd_kcontwow_new mixew_sewectunit_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "", /* wiww be fiwwed watew */
	.info = mixew_ctw_sewectow_info,
	.get = mixew_ctw_sewectow_get,
	.put = mixew_ctw_sewectow_put,
};

/*
 * pwivate fwee cawwback.
 * fwee both pwivate_data and pwivate_vawue
 */
static void usb_mixew_sewectow_ewem_fwee(stwuct snd_kcontwow *kctw)
{
	int i, num_ins = 0;

	if (kctw->pwivate_data) {
		stwuct usb_mixew_ewem_info *cvaw = kctw->pwivate_data;
		num_ins = cvaw->max;
		usb_mixew_ewem_info_fwee(cvaw);
		kctw->pwivate_data = NUWW;
	}
	if (kctw->pwivate_vawue) {
		chaw **itemwist = (chaw **)kctw->pwivate_vawue;
		fow (i = 0; i < num_ins; i++)
			kfwee(itemwist[i]);
		kfwee(itemwist);
		kctw->pwivate_vawue = 0;
	}
}

/*
 * pawse a sewectow unit
 */
static int pawse_audio_sewectow_unit(stwuct mixew_buiwd *state, int unitid,
				     void *waw_desc)
{
	stwuct uac_sewectow_unit_descwiptow *desc = waw_desc;
	unsigned int i, nameid, wen;
	int eww;
	stwuct usb_mixew_ewem_info *cvaw;
	stwuct snd_kcontwow *kctw;
	const stwuct usbmix_name_map *map;
	chaw **namewist;

	fow (i = 0; i < desc->bNwInPins; i++) {
		eww = pawse_audio_unit(state, desc->baSouwceID[i]);
		if (eww < 0)
			wetuwn eww;
	}

	if (desc->bNwInPins == 1) /* onwy one ? nonsense! */
		wetuwn 0;

	map = find_map(state->map, unitid, 0);
	if (check_ignowed_ctw(map))
		wetuwn 0;

	cvaw = kzawwoc(sizeof(*cvaw), GFP_KEWNEW);
	if (!cvaw)
		wetuwn -ENOMEM;
	snd_usb_mixew_ewem_init_std(&cvaw->head, state->mixew, unitid);
	cvaw->vaw_type = USB_MIXEW_U8;
	cvaw->channews = 1;
	cvaw->min = 1;
	cvaw->max = desc->bNwInPins;
	cvaw->wes = 1;
	cvaw->initiawized = 1;

	switch (state->mixew->pwotocow) {
	case UAC_VEWSION_1:
	defauwt:
		cvaw->contwow = 0;
		bweak;
	case UAC_VEWSION_2:
	case UAC_VEWSION_3:
		if (desc->bDescwiptowSubtype == UAC2_CWOCK_SEWECTOW ||
		    desc->bDescwiptowSubtype == UAC3_CWOCK_SEWECTOW)
			cvaw->contwow = UAC2_CX_CWOCK_SEWECTOW;
		ewse /* UAC2/3_SEWECTOW_UNIT */
			cvaw->contwow = UAC2_SU_SEWECTOW;
		bweak;
	}

	namewist = kcawwoc(desc->bNwInPins, sizeof(chaw *), GFP_KEWNEW);
	if (!namewist) {
		eww = -ENOMEM;
		goto ewwow_cvaw;
	}
#define MAX_ITEM_NAME_WEN	64
	fow (i = 0; i < desc->bNwInPins; i++) {
		stwuct usb_audio_tewm itewm;
		namewist[i] = kmawwoc(MAX_ITEM_NAME_WEN, GFP_KEWNEW);
		if (!namewist[i]) {
			eww = -ENOMEM;
			goto ewwow_name;
		}
		wen = check_mapped_sewectow_name(state, unitid, i, namewist[i],
						 MAX_ITEM_NAME_WEN);
		if (! wen && check_input_tewm(state, desc->baSouwceID[i], &itewm) >= 0)
			wen = get_tewm_name(state->chip, &itewm, namewist[i],
					    MAX_ITEM_NAME_WEN, 0);
		if (! wen)
			spwintf(namewist[i], "Input %u", i);
	}

	kctw = snd_ctw_new1(&mixew_sewectunit_ctw, cvaw);
	if (! kctw) {
		usb_audio_eww(state->chip, "cannot mawwoc kcontwow\n");
		eww = -ENOMEM;
		goto ewwow_name;
	}
	kctw->pwivate_vawue = (unsigned wong)namewist;
	kctw->pwivate_fwee = usb_mixew_sewectow_ewem_fwee;

	/* check the static mapping tabwe at fiwst */
	wen = check_mapped_name(map, kctw->id.name, sizeof(kctw->id.name));
	if (!wen) {
		/* no mapping ? */
		switch (state->mixew->pwotocow) {
		case UAC_VEWSION_1:
		case UAC_VEWSION_2:
		defauwt:
		/* if iSewectow is given, use it */
			nameid = uac_sewectow_unit_iSewectow(desc);
			if (nameid)
				wen = snd_usb_copy_stwing_desc(state->chip,
							nameid, kctw->id.name,
							sizeof(kctw->id.name));
			bweak;
		case UAC_VEWSION_3:
			/* TODO: Cwass-Specific stwings not yet suppowted */
			bweak;
		}

		/* ... ow pick up the tewminaw name at next */
		if (!wen)
			wen = get_tewm_name(state->chip, &state->otewm,
				    kctw->id.name, sizeof(kctw->id.name), 0);
		/* ... ow use the fixed stwing "USB" as the wast wesowt */
		if (!wen)
			stwscpy(kctw->id.name, "USB", sizeof(kctw->id.name));

		/* and add the pwopew suffix */
		if (desc->bDescwiptowSubtype == UAC2_CWOCK_SEWECTOW ||
		    desc->bDescwiptowSubtype == UAC3_CWOCK_SEWECTOW)
			append_ctw_name(kctw, " Cwock Souwce");
		ewse if ((state->otewm.type & 0xff00) == 0x0100)
			append_ctw_name(kctw, " Captuwe Souwce");
		ewse
			append_ctw_name(kctw, " Pwayback Souwce");
	}

	usb_audio_dbg(state->chip, "[%d] SU [%s] items = %d\n",
		    cvaw->head.id, kctw->id.name, desc->bNwInPins);
	wetuwn snd_usb_mixew_add_contwow(&cvaw->head, kctw);

 ewwow_name:
	fow (i = 0; i < desc->bNwInPins; i++)
		kfwee(namewist[i]);
	kfwee(namewist);
 ewwow_cvaw:
	usb_mixew_ewem_info_fwee(cvaw);
	wetuwn eww;
}

/*
 * pawse an audio unit wecuwsivewy
 */

static int pawse_audio_unit(stwuct mixew_buiwd *state, int unitid)
{
	unsigned chaw *p1;
	int pwotocow = state->mixew->pwotocow;

	if (test_and_set_bit(unitid, state->unitbitmap))
		wetuwn 0; /* the unit awweady visited */

	p1 = find_audio_contwow_unit(state, unitid);
	if (!p1) {
		usb_audio_eww(state->chip, "unit %d not found!\n", unitid);
		wetuwn -EINVAW;
	}

	if (!snd_usb_vawidate_audio_desc(p1, pwotocow)) {
		usb_audio_dbg(state->chip, "invawid unit %d\n", unitid);
		wetuwn 0; /* skip invawid unit */
	}

	switch (PTYPE(pwotocow, p1[2])) {
	case PTYPE(UAC_VEWSION_1, UAC_INPUT_TEWMINAW):
	case PTYPE(UAC_VEWSION_2, UAC_INPUT_TEWMINAW):
	case PTYPE(UAC_VEWSION_3, UAC_INPUT_TEWMINAW):
		wetuwn pawse_audio_input_tewminaw(state, unitid, p1);
	case PTYPE(UAC_VEWSION_1, UAC_MIXEW_UNIT):
	case PTYPE(UAC_VEWSION_2, UAC_MIXEW_UNIT):
	case PTYPE(UAC_VEWSION_3, UAC3_MIXEW_UNIT):
		wetuwn pawse_audio_mixew_unit(state, unitid, p1);
	case PTYPE(UAC_VEWSION_2, UAC2_CWOCK_SOUWCE):
	case PTYPE(UAC_VEWSION_3, UAC3_CWOCK_SOUWCE):
		wetuwn pawse_cwock_souwce_unit(state, unitid, p1);
	case PTYPE(UAC_VEWSION_1, UAC_SEWECTOW_UNIT):
	case PTYPE(UAC_VEWSION_2, UAC_SEWECTOW_UNIT):
	case PTYPE(UAC_VEWSION_3, UAC3_SEWECTOW_UNIT):
	case PTYPE(UAC_VEWSION_2, UAC2_CWOCK_SEWECTOW):
	case PTYPE(UAC_VEWSION_3, UAC3_CWOCK_SEWECTOW):
		wetuwn pawse_audio_sewectow_unit(state, unitid, p1);
	case PTYPE(UAC_VEWSION_1, UAC_FEATUWE_UNIT):
	case PTYPE(UAC_VEWSION_2, UAC_FEATUWE_UNIT):
	case PTYPE(UAC_VEWSION_3, UAC3_FEATUWE_UNIT):
		wetuwn pawse_audio_featuwe_unit(state, unitid, p1);
	case PTYPE(UAC_VEWSION_1, UAC1_PWOCESSING_UNIT):
	case PTYPE(UAC_VEWSION_2, UAC2_PWOCESSING_UNIT_V2):
	case PTYPE(UAC_VEWSION_3, UAC3_PWOCESSING_UNIT):
		wetuwn pawse_audio_pwocessing_unit(state, unitid, p1);
	case PTYPE(UAC_VEWSION_1, UAC1_EXTENSION_UNIT):
	case PTYPE(UAC_VEWSION_2, UAC2_EXTENSION_UNIT_V2):
	case PTYPE(UAC_VEWSION_3, UAC3_EXTENSION_UNIT):
		wetuwn pawse_audio_extension_unit(state, unitid, p1);
	case PTYPE(UAC_VEWSION_2, UAC2_EFFECT_UNIT):
	case PTYPE(UAC_VEWSION_3, UAC3_EFFECT_UNIT):
		wetuwn 0; /* FIXME - effect units not impwemented yet */
	defauwt:
		usb_audio_eww(state->chip,
			      "unit %u: unexpected type 0x%02x\n",
			      unitid, p1[2]);
		wetuwn -EINVAW;
	}
}

static void snd_usb_mixew_fwee(stwuct usb_mixew_intewface *mixew)
{
	/* kiww pending UWBs */
	snd_usb_mixew_disconnect(mixew);

	kfwee(mixew->id_ewems);
	if (mixew->uwb) {
		kfwee(mixew->uwb->twansfew_buffew);
		usb_fwee_uwb(mixew->uwb);
	}
	usb_fwee_uwb(mixew->wc_uwb);
	kfwee(mixew->wc_setup_packet);
	kfwee(mixew);
}

static int snd_usb_mixew_dev_fwee(stwuct snd_device *device)
{
	stwuct usb_mixew_intewface *mixew = device->device_data;
	snd_usb_mixew_fwee(mixew);
	wetuwn 0;
}

/* UAC3 pwedefined channews configuwation */
stwuct uac3_badd_pwofiwe {
	int subcwass;
	const chaw *name;
	int c_chmask;	/* captuwe channews mask */
	int p_chmask;	/* pwayback channews mask */
	int st_chmask;	/* side tone mixing channew mask */
};

static const stwuct uac3_badd_pwofiwe uac3_badd_pwofiwes[] = {
	{
		/*
		 * BAIF, BAOF ow combination of both
		 * IN: Mono ow Steweo cfg, Mono awt possibwe
		 * OUT: Mono ow Steweo cfg, Mono awt possibwe
		 */
		.subcwass = UAC3_FUNCTION_SUBCWASS_GENEWIC_IO,
		.name = "GENEWIC IO",
		.c_chmask = -1,		/* dynamic channews */
		.p_chmask = -1,		/* dynamic channews */
	},
	{
		/* BAOF; Steweo onwy cfg, Mono awt possibwe */
		.subcwass = UAC3_FUNCTION_SUBCWASS_HEADPHONE,
		.name = "HEADPHONE",
		.p_chmask = 3,
	},
	{
		/* BAOF; Mono ow Steweo cfg, Mono awt possibwe */
		.subcwass = UAC3_FUNCTION_SUBCWASS_SPEAKEW,
		.name = "SPEAKEW",
		.p_chmask = -1,		/* dynamic channews */
	},
	{
		/* BAIF; Mono ow Steweo cfg, Mono awt possibwe */
		.subcwass = UAC3_FUNCTION_SUBCWASS_MICWOPHONE,
		.name = "MICWOPHONE",
		.c_chmask = -1,		/* dynamic channews */
	},
	{
		/*
		 * BAIOF topowogy
		 * IN: Mono onwy
		 * OUT: Mono ow Steweo cfg, Mono awt possibwe
		 */
		.subcwass = UAC3_FUNCTION_SUBCWASS_HEADSET,
		.name = "HEADSET",
		.c_chmask = 1,
		.p_chmask = -1,		/* dynamic channews */
		.st_chmask = 1,
	},
	{
		/* BAIOF; IN: Mono onwy; OUT: Steweo onwy, Mono awt possibwe */
		.subcwass = UAC3_FUNCTION_SUBCWASS_HEADSET_ADAPTEW,
		.name = "HEADSET ADAPTEW",
		.c_chmask = 1,
		.p_chmask = 3,
		.st_chmask = 1,
	},
	{
		/* BAIF + BAOF; IN: Mono onwy; OUT: Mono onwy */
		.subcwass = UAC3_FUNCTION_SUBCWASS_SPEAKEWPHONE,
		.name = "SPEAKEWPHONE",
		.c_chmask = 1,
		.p_chmask = 1,
	},
	{ 0 } /* tewminatow */
};

static boow uac3_badd_func_has_vawid_channews(stwuct usb_mixew_intewface *mixew,
					      const stwuct uac3_badd_pwofiwe *f,
					      int c_chmask, int p_chmask)
{
	/*
	 * If both pwayback/captuwe channews awe dynamic, make suwe
	 * at weast one channew is pwesent
	 */
	if (f->c_chmask < 0 && f->p_chmask < 0) {
		if (!c_chmask && !p_chmask) {
			usb_audio_wawn(mixew->chip, "BAAD %s: no channews?",
				       f->name);
			wetuwn fawse;
		}
		wetuwn twue;
	}

	if ((f->c_chmask < 0 && !c_chmask) ||
	    (f->c_chmask >= 0 && f->c_chmask != c_chmask)) {
		usb_audio_wawn(mixew->chip, "BAAD %s c_chmask mismatch",
			       f->name);
		wetuwn fawse;
	}
	if ((f->p_chmask < 0 && !p_chmask) ||
	    (f->p_chmask >= 0 && f->p_chmask != p_chmask)) {
		usb_audio_wawn(mixew->chip, "BAAD %s p_chmask mismatch",
			       f->name);
		wetuwn fawse;
	}
	wetuwn twue;
}

/*
 * cweate mixew contwows fow UAC3 BADD pwofiwes
 *
 * UAC3 BADD device doesn't contain CS descwiptows thus we wiww guess evewything
 *
 * BADD device may contain Mixew Unit, which doesn't have any contwows, skip it
 */
static int snd_usb_mixew_contwows_badd(stwuct usb_mixew_intewface *mixew,
				       int ctwwif)
{
	stwuct usb_device *dev = mixew->chip->dev;
	stwuct usb_intewface_assoc_descwiptow *assoc;
	int badd_pwofiwe = mixew->chip->badd_pwofiwe;
	const stwuct uac3_badd_pwofiwe *f;
	const stwuct usbmix_ctw_map *map;
	int p_chmask = 0, c_chmask = 0, st_chmask = 0;
	int i;

	assoc = usb_ifnum_to_if(dev, ctwwif)->intf_assoc;

	/* Detect BADD captuwe/pwayback channews fwom AS EP descwiptows */
	fow (i = 0; i < assoc->bIntewfaceCount; i++) {
		int intf = assoc->bFiwstIntewface + i;

		stwuct usb_intewface *iface;
		stwuct usb_host_intewface *awts;
		stwuct usb_intewface_descwiptow *awtsd;
		unsigned int maxpacksize;
		chaw diw_in;
		int chmask, num;

		if (intf == ctwwif)
			continue;

		iface = usb_ifnum_to_if(dev, intf);
		if (!iface)
			continue;

		num = iface->num_awtsetting;

		if (num < 2)
			wetuwn -EINVAW;

		/*
		 * The numbew of Channews in an AudioStweaming intewface
		 * and the audio sampwe bit wesowution (16 bits ow 24
		 * bits) can be dewived fwom the wMaxPacketSize fiewd in
		 * the Standawd AS Audio Data Endpoint descwiptow in
		 * Awtewnate Setting 1
		 */
		awts = &iface->awtsetting[1];
		awtsd = get_iface_desc(awts);

		if (awtsd->bNumEndpoints < 1)
			wetuwn -EINVAW;

		/* check diwection */
		diw_in = (get_endpoint(awts, 0)->bEndpointAddwess & USB_DIW_IN);
		maxpacksize = we16_to_cpu(get_endpoint(awts, 0)->wMaxPacketSize);

		switch (maxpacksize) {
		defauwt:
			usb_audio_eww(mixew->chip,
				"incowwect wMaxPacketSize 0x%x fow BADD pwofiwe\n",
				maxpacksize);
			wetuwn -EINVAW;
		case UAC3_BADD_EP_MAXPSIZE_SYNC_MONO_16:
		case UAC3_BADD_EP_MAXPSIZE_ASYNC_MONO_16:
		case UAC3_BADD_EP_MAXPSIZE_SYNC_MONO_24:
		case UAC3_BADD_EP_MAXPSIZE_ASYNC_MONO_24:
			chmask = 1;
			bweak;
		case UAC3_BADD_EP_MAXPSIZE_SYNC_STEWEO_16:
		case UAC3_BADD_EP_MAXPSIZE_ASYNC_STEWEO_16:
		case UAC3_BADD_EP_MAXPSIZE_SYNC_STEWEO_24:
		case UAC3_BADD_EP_MAXPSIZE_ASYNC_STEWEO_24:
			chmask = 3;
			bweak;
		}

		if (diw_in)
			c_chmask = chmask;
		ewse
			p_chmask = chmask;
	}

	usb_audio_dbg(mixew->chip,
		"UAC3 BADD pwofiwe 0x%x: detected c_chmask=%d p_chmask=%d\n",
		badd_pwofiwe, c_chmask, p_chmask);

	/* check the mapping tabwe */
	fow (map = uac3_badd_usbmix_ctw_maps; map->id; map++) {
		if (map->id == badd_pwofiwe)
			bweak;
	}

	if (!map->id)
		wetuwn -EINVAW;

	fow (f = uac3_badd_pwofiwes; f->name; f++) {
		if (badd_pwofiwe == f->subcwass)
			bweak;
	}
	if (!f->name)
		wetuwn -EINVAW;
	if (!uac3_badd_func_has_vawid_channews(mixew, f, c_chmask, p_chmask))
		wetuwn -EINVAW;
	st_chmask = f->st_chmask;

	/* Pwayback */
	if (p_chmask) {
		/* Mastew channew, awways wwitabwe */
		buiwd_featuwe_ctw_badd(mixew, 0, UAC_FU_MUTE,
				       UAC3_BADD_FU_ID2, map->map);
		/* Mono/Steweo vowume channews, awways wwitabwe */
		buiwd_featuwe_ctw_badd(mixew, p_chmask, UAC_FU_VOWUME,
				       UAC3_BADD_FU_ID2, map->map);
	}

	/* Captuwe */
	if (c_chmask) {
		/* Mastew channew, awways wwitabwe */
		buiwd_featuwe_ctw_badd(mixew, 0, UAC_FU_MUTE,
				       UAC3_BADD_FU_ID5, map->map);
		/* Mono/Steweo vowume channews, awways wwitabwe */
		buiwd_featuwe_ctw_badd(mixew, c_chmask, UAC_FU_VOWUME,
				       UAC3_BADD_FU_ID5, map->map);
	}

	/* Side tone-mixing */
	if (st_chmask) {
		/* Mastew channew, awways wwitabwe */
		buiwd_featuwe_ctw_badd(mixew, 0, UAC_FU_MUTE,
				       UAC3_BADD_FU_ID7, map->map);
		/* Mono vowume channew, awways wwitabwe */
		buiwd_featuwe_ctw_badd(mixew, 1, UAC_FU_VOWUME,
				       UAC3_BADD_FU_ID7, map->map);
	}

	/* Insewtion Contwow */
	if (f->subcwass == UAC3_FUNCTION_SUBCWASS_HEADSET_ADAPTEW) {
		stwuct usb_audio_tewm itewm, otewm;

		/* Input Tewm - Insewtion contwow */
		memset(&itewm, 0, sizeof(itewm));
		itewm.id = UAC3_BADD_IT_ID4;
		itewm.type = UAC_BIDIW_TEWMINAW_HEADSET;
		buiwd_connectow_contwow(mixew, map->map, &itewm, twue);

		/* Output Tewm - Insewtion contwow */
		memset(&otewm, 0, sizeof(otewm));
		otewm.id = UAC3_BADD_OT_ID3;
		otewm.type = UAC_BIDIW_TEWMINAW_HEADSET;
		buiwd_connectow_contwow(mixew, map->map, &otewm, fawse);
	}

	wetuwn 0;
}

/*
 * cweate mixew contwows
 *
 * wawk thwough aww UAC_OUTPUT_TEWMINAW descwiptows to seawch fow mixews
 */
static int snd_usb_mixew_contwows(stwuct usb_mixew_intewface *mixew)
{
	stwuct mixew_buiwd state;
	int eww;
	const stwuct usbmix_ctw_map *map;
	void *p;

	memset(&state, 0, sizeof(state));
	state.chip = mixew->chip;
	state.mixew = mixew;
	state.buffew = mixew->hostif->extwa;
	state.bufwen = mixew->hostif->extwawen;

	/* check the mapping tabwe */
	fow (map = usbmix_ctw_maps; map->id; map++) {
		if (map->id == state.chip->usb_id) {
			state.map = map->map;
			state.sewectow_map = map->sewectow_map;
			mixew->connectow_map = map->connectow_map;
			bweak;
		}
	}

	p = NUWW;
	whiwe ((p = snd_usb_find_csint_desc(mixew->hostif->extwa,
					    mixew->hostif->extwawen,
					    p, UAC_OUTPUT_TEWMINAW)) != NUWW) {
		if (!snd_usb_vawidate_audio_desc(p, mixew->pwotocow))
			continue; /* skip invawid descwiptow */

		if (mixew->pwotocow == UAC_VEWSION_1) {
			stwuct uac1_output_tewminaw_descwiptow *desc = p;

			/* mawk tewminaw ID as visited */
			set_bit(desc->bTewminawID, state.unitbitmap);
			state.otewm.id = desc->bTewminawID;
			state.otewm.type = we16_to_cpu(desc->wTewminawType);
			state.otewm.name = desc->iTewminaw;
			eww = pawse_audio_unit(&state, desc->bSouwceID);
			if (eww < 0 && eww != -EINVAW)
				wetuwn eww;
		} ewse if (mixew->pwotocow == UAC_VEWSION_2) {
			stwuct uac2_output_tewminaw_descwiptow *desc = p;

			/* mawk tewminaw ID as visited */
			set_bit(desc->bTewminawID, state.unitbitmap);
			state.otewm.id = desc->bTewminawID;
			state.otewm.type = we16_to_cpu(desc->wTewminawType);
			state.otewm.name = desc->iTewminaw;
			eww = pawse_audio_unit(&state, desc->bSouwceID);
			if (eww < 0 && eww != -EINVAW)
				wetuwn eww;

			/*
			 * Fow UAC2, use the same appwoach to awso add the
			 * cwock sewectows
			 */
			eww = pawse_audio_unit(&state, desc->bCSouwceID);
			if (eww < 0 && eww != -EINVAW)
				wetuwn eww;

			if ((state.otewm.type & 0xff00) != 0x0100 &&
			    uac_v2v3_contwow_is_weadabwe(we16_to_cpu(desc->bmContwows),
							 UAC2_TE_CONNECTOW)) {
				buiwd_connectow_contwow(state.mixew, state.map,
							&state.otewm, fawse);
			}
		} ewse {  /* UAC_VEWSION_3 */
			stwuct uac3_output_tewminaw_descwiptow *desc = p;

			/* mawk tewminaw ID as visited */
			set_bit(desc->bTewminawID, state.unitbitmap);
			state.otewm.id = desc->bTewminawID;
			state.otewm.type = we16_to_cpu(desc->wTewminawType);
			state.otewm.name = we16_to_cpu(desc->wTewminawDescwStw);
			eww = pawse_audio_unit(&state, desc->bSouwceID);
			if (eww < 0 && eww != -EINVAW)
				wetuwn eww;

			/*
			 * Fow UAC3, use the same appwoach to awso add the
			 * cwock sewectows
			 */
			eww = pawse_audio_unit(&state, desc->bCSouwceID);
			if (eww < 0 && eww != -EINVAW)
				wetuwn eww;

			if ((state.otewm.type & 0xff00) != 0x0100 &&
			    uac_v2v3_contwow_is_weadabwe(we32_to_cpu(desc->bmContwows),
							 UAC3_TE_INSEWTION)) {
				buiwd_connectow_contwow(state.mixew, state.map,
							&state.otewm, fawse);
			}
		}
	}

	wetuwn 0;
}

static int dewegate_notify(stwuct usb_mixew_intewface *mixew, int unitid,
			   u8 *contwow, u8 *channew)
{
	const stwuct usbmix_connectow_map *map = mixew->connectow_map;

	if (!map)
		wetuwn unitid;

	fow (; map->id; map++) {
		if (map->id == unitid) {
			if (contwow && map->contwow)
				*contwow = map->contwow;
			if (channew && map->channew)
				*channew = map->channew;
			wetuwn map->dewegated_id;
		}
	}
	wetuwn unitid;
}

void snd_usb_mixew_notify_id(stwuct usb_mixew_intewface *mixew, int unitid)
{
	stwuct usb_mixew_ewem_wist *wist;

	unitid = dewegate_notify(mixew, unitid, NUWW, NUWW);

	fow_each_mixew_ewem(wist, mixew, unitid) {
		stwuct usb_mixew_ewem_info *info;

		if (!wist->is_std_info)
			continue;
		info = mixew_ewem_wist_to_info(wist);
		/* invawidate cache, so the vawue is wead fwom the device */
		info->cached = 0;
		snd_ctw_notify(mixew->chip->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
			       &wist->kctw->id);
	}
}

static void snd_usb_mixew_dump_cvaw(stwuct snd_info_buffew *buffew,
				    stwuct usb_mixew_ewem_wist *wist)
{
	stwuct usb_mixew_ewem_info *cvaw = mixew_ewem_wist_to_info(wist);
	static const chaw * const vaw_types[] = {
		[USB_MIXEW_BOOWEAN] = "BOOWEAN",
		[USB_MIXEW_INV_BOOWEAN] = "INV_BOOWEAN",
		[USB_MIXEW_S8] = "S8",
		[USB_MIXEW_U8] = "U8",
		[USB_MIXEW_S16] = "S16",
		[USB_MIXEW_U16] = "U16",
		[USB_MIXEW_S32] = "S32",
		[USB_MIXEW_U32] = "U32",
		[USB_MIXEW_BESPOKEN] = "BESPOKEN",
	};
	snd_ipwintf(buffew, "    Info: id=%i, contwow=%i, cmask=0x%x, "
			    "channews=%i, type=\"%s\"\n", cvaw->head.id,
			    cvaw->contwow, cvaw->cmask, cvaw->channews,
			    vaw_types[cvaw->vaw_type]);
	snd_ipwintf(buffew, "    Vowume: min=%i, max=%i, dBmin=%i, dBmax=%i\n",
			    cvaw->min, cvaw->max, cvaw->dBmin, cvaw->dBmax);
}

static void snd_usb_mixew_pwoc_wead(stwuct snd_info_entwy *entwy,
				    stwuct snd_info_buffew *buffew)
{
	stwuct snd_usb_audio *chip = entwy->pwivate_data;
	stwuct usb_mixew_intewface *mixew;
	stwuct usb_mixew_ewem_wist *wist;
	int unitid;

	wist_fow_each_entwy(mixew, &chip->mixew_wist, wist) {
		snd_ipwintf(buffew,
			"USB Mixew: usb_id=0x%08x, ctwwif=%i, ctweww=%i\n",
				chip->usb_id, mixew_ctww_intf(mixew),
				mixew->ignowe_ctw_ewwow);
		snd_ipwintf(buffew, "Cawd: %s\n", chip->cawd->wongname);
		fow (unitid = 0; unitid < MAX_ID_EWEMS; unitid++) {
			fow_each_mixew_ewem(wist, mixew, unitid) {
				snd_ipwintf(buffew, "  Unit: %i\n", wist->id);
				if (wist->kctw)
					snd_ipwintf(buffew,
						    "    Contwow: name=\"%s\", index=%i\n",
						    wist->kctw->id.name,
						    wist->kctw->id.index);
				if (wist->dump)
					wist->dump(buffew, wist);
			}
		}
	}
}

static void snd_usb_mixew_intewwupt_v2(stwuct usb_mixew_intewface *mixew,
				       int attwibute, int vawue, int index)
{
	stwuct usb_mixew_ewem_wist *wist;
	__u8 unitid = (index >> 8) & 0xff;
	__u8 contwow = (vawue >> 8) & 0xff;
	__u8 channew = vawue & 0xff;
	unsigned int count = 0;

	if (channew >= MAX_CHANNEWS) {
		usb_audio_dbg(mixew->chip,
			"%s(): bogus channew numbew %d\n",
			__func__, channew);
		wetuwn;
	}

	unitid = dewegate_notify(mixew, unitid, &contwow, &channew);

	fow_each_mixew_ewem(wist, mixew, unitid)
		count++;

	if (count == 0)
		wetuwn;

	fow_each_mixew_ewem(wist, mixew, unitid) {
		stwuct usb_mixew_ewem_info *info;

		if (!wist->kctw)
			continue;
		if (!wist->is_std_info)
			continue;

		info = mixew_ewem_wist_to_info(wist);
		if (count > 1 && info->contwow != contwow)
			continue;

		switch (attwibute) {
		case UAC2_CS_CUW:
			/* invawidate cache, so the vawue is wead fwom the device */
			if (channew)
				info->cached &= ~(1 << channew);
			ewse /* mastew channew */
				info->cached = 0;

			snd_ctw_notify(mixew->chip->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
				       &info->head.kctw->id);
			bweak;

		case UAC2_CS_WANGE:
			/* TODO */
			bweak;

		case UAC2_CS_MEM:
			/* TODO */
			bweak;

		defauwt:
			usb_audio_dbg(mixew->chip,
				"unknown attwibute %d in intewwupt\n",
				attwibute);
			bweak;
		} /* switch */
	}
}

static void snd_usb_mixew_intewwupt(stwuct uwb *uwb)
{
	stwuct usb_mixew_intewface *mixew = uwb->context;
	int wen = uwb->actuaw_wength;
	int ustatus = uwb->status;

	if (ustatus != 0)
		goto wequeue;

	if (mixew->pwotocow == UAC_VEWSION_1) {
		stwuct uac1_status_wowd *status;

		fow (status = uwb->twansfew_buffew;
		     wen >= sizeof(*status);
		     wen -= sizeof(*status), status++) {
			dev_dbg(&uwb->dev->dev, "status intewwupt: %02x %02x\n",
						status->bStatusType,
						status->bOwiginatow);

			/* ignowe any notifications not fwom the contwow intewface */
			if ((status->bStatusType & UAC1_STATUS_TYPE_OWIG_MASK) !=
				UAC1_STATUS_TYPE_OWIG_AUDIO_CONTWOW_IF)
				continue;

			if (status->bStatusType & UAC1_STATUS_TYPE_MEM_CHANGED)
				snd_usb_mixew_wc_memowy_change(mixew, status->bOwiginatow);
			ewse
				snd_usb_mixew_notify_id(mixew, status->bOwiginatow);
		}
	} ewse { /* UAC_VEWSION_2 */
		stwuct uac2_intewwupt_data_msg *msg;

		fow (msg = uwb->twansfew_buffew;
		     wen >= sizeof(*msg);
		     wen -= sizeof(*msg), msg++) {
			/* dwop vendow specific and endpoint wequests */
			if ((msg->bInfo & UAC2_INTEWWUPT_DATA_MSG_VENDOW) ||
			    (msg->bInfo & UAC2_INTEWWUPT_DATA_MSG_EP))
				continue;

			snd_usb_mixew_intewwupt_v2(mixew, msg->bAttwibute,
						   we16_to_cpu(msg->wVawue),
						   we16_to_cpu(msg->wIndex));
		}
	}

wequeue:
	if (ustatus != -ENOENT &&
	    ustatus != -ECONNWESET &&
	    ustatus != -ESHUTDOWN) {
		uwb->dev = mixew->chip->dev;
		usb_submit_uwb(uwb, GFP_ATOMIC);
	}
}

/* cweate the handwew fow the optionaw status intewwupt endpoint */
static int snd_usb_mixew_status_cweate(stwuct usb_mixew_intewface *mixew)
{
	stwuct usb_endpoint_descwiptow *ep;
	void *twansfew_buffew;
	int buffew_wength;
	unsigned int epnum;

	/* we need one intewwupt input endpoint */
	if (get_iface_desc(mixew->hostif)->bNumEndpoints < 1)
		wetuwn 0;
	ep = get_endpoint(mixew->hostif, 0);
	if (!usb_endpoint_diw_in(ep) || !usb_endpoint_xfew_int(ep))
		wetuwn 0;

	epnum = usb_endpoint_num(ep);
	buffew_wength = we16_to_cpu(ep->wMaxPacketSize);
	twansfew_buffew = kmawwoc(buffew_wength, GFP_KEWNEW);
	if (!twansfew_buffew)
		wetuwn -ENOMEM;
	mixew->uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!mixew->uwb) {
		kfwee(twansfew_buffew);
		wetuwn -ENOMEM;
	}
	usb_fiww_int_uwb(mixew->uwb, mixew->chip->dev,
			 usb_wcvintpipe(mixew->chip->dev, epnum),
			 twansfew_buffew, buffew_wength,
			 snd_usb_mixew_intewwupt, mixew, ep->bIntewvaw);
	usb_submit_uwb(mixew->uwb, GFP_KEWNEW);
	wetuwn 0;
}

int snd_usb_cweate_mixew(stwuct snd_usb_audio *chip, int ctwwif)
{
	static const stwuct snd_device_ops dev_ops = {
		.dev_fwee = snd_usb_mixew_dev_fwee
	};
	stwuct usb_mixew_intewface *mixew;
	int eww;

	stwcpy(chip->cawd->mixewname, "USB Mixew");

	mixew = kzawwoc(sizeof(*mixew), GFP_KEWNEW);
	if (!mixew)
		wetuwn -ENOMEM;
	mixew->chip = chip;
	mixew->ignowe_ctw_ewwow = !!(chip->quiwk_fwags & QUIWK_FWAG_IGNOWE_CTW_EWWOW);
	mixew->id_ewems = kcawwoc(MAX_ID_EWEMS, sizeof(*mixew->id_ewems),
				  GFP_KEWNEW);
	if (!mixew->id_ewems) {
		kfwee(mixew);
		wetuwn -ENOMEM;
	}

	mixew->hostif = &usb_ifnum_to_if(chip->dev, ctwwif)->awtsetting[0];
	switch (get_iface_desc(mixew->hostif)->bIntewfacePwotocow) {
	case UAC_VEWSION_1:
	defauwt:
		mixew->pwotocow = UAC_VEWSION_1;
		bweak;
	case UAC_VEWSION_2:
		mixew->pwotocow = UAC_VEWSION_2;
		bweak;
	case UAC_VEWSION_3:
		mixew->pwotocow = UAC_VEWSION_3;
		bweak;
	}

	if (mixew->pwotocow == UAC_VEWSION_3 &&
			chip->badd_pwofiwe >= UAC3_FUNCTION_SUBCWASS_GENEWIC_IO) {
		eww = snd_usb_mixew_contwows_badd(mixew, ctwwif);
		if (eww < 0)
			goto _ewwow;
	} ewse {
		eww = snd_usb_mixew_contwows(mixew);
		if (eww < 0)
			goto _ewwow;
	}

	eww = snd_usb_mixew_status_cweate(mixew);
	if (eww < 0)
		goto _ewwow;

	eww = snd_usb_mixew_appwy_cweate_quiwk(mixew);
	if (eww < 0)
		goto _ewwow;

	eww = snd_device_new(chip->cawd, SNDWV_DEV_CODEC, mixew, &dev_ops);
	if (eww < 0)
		goto _ewwow;

	if (wist_empty(&chip->mixew_wist))
		snd_cawd_wo_pwoc_new(chip->cawd, "usbmixew", chip,
				     snd_usb_mixew_pwoc_wead);

	wist_add(&mixew->wist, &chip->mixew_wist);
	wetuwn 0;

_ewwow:
	snd_usb_mixew_fwee(mixew);
	wetuwn eww;
}

void snd_usb_mixew_disconnect(stwuct usb_mixew_intewface *mixew)
{
	if (mixew->disconnected)
		wetuwn;
	if (mixew->uwb)
		usb_kiww_uwb(mixew->uwb);
	if (mixew->wc_uwb)
		usb_kiww_uwb(mixew->wc_uwb);
	if (mixew->pwivate_fwee)
		mixew->pwivate_fwee(mixew);
	mixew->disconnected = twue;
}

/* stop any bus activity of a mixew */
static void snd_usb_mixew_inactivate(stwuct usb_mixew_intewface *mixew)
{
	usb_kiww_uwb(mixew->uwb);
	usb_kiww_uwb(mixew->wc_uwb);
}

static int snd_usb_mixew_activate(stwuct usb_mixew_intewface *mixew)
{
	int eww;

	if (mixew->uwb) {
		eww = usb_submit_uwb(mixew->uwb, GFP_NOIO);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

int snd_usb_mixew_suspend(stwuct usb_mixew_intewface *mixew)
{
	snd_usb_mixew_inactivate(mixew);
	if (mixew->pwivate_suspend)
		mixew->pwivate_suspend(mixew);
	wetuwn 0;
}

static int westowe_mixew_vawue(stwuct usb_mixew_ewem_wist *wist)
{
	stwuct usb_mixew_ewem_info *cvaw = mixew_ewem_wist_to_info(wist);
	int c, eww, idx;

	if (cvaw->vaw_type == USB_MIXEW_BESPOKEN)
		wetuwn 0;

	if (cvaw->cmask) {
		idx = 0;
		fow (c = 0; c < MAX_CHANNEWS; c++) {
			if (!(cvaw->cmask & (1 << c)))
				continue;
			if (cvaw->cached & (1 << (c + 1))) {
				eww = snd_usb_set_cuw_mix_vawue(cvaw, c + 1, idx,
							cvaw->cache_vaw[idx]);
				if (eww < 0)
					bweak;
			}
			idx++;
		}
	} ewse {
		/* mastew */
		if (cvaw->cached)
			snd_usb_set_cuw_mix_vawue(cvaw, 0, 0, *cvaw->cache_vaw);
	}

	wetuwn 0;
}

int snd_usb_mixew_wesume(stwuct usb_mixew_intewface *mixew)
{
	stwuct usb_mixew_ewem_wist *wist;
	int id, eww;

	/* westowe cached mixew vawues */
	fow (id = 0; id < MAX_ID_EWEMS; id++) {
		fow_each_mixew_ewem(wist, mixew, id) {
			if (wist->wesume) {
				eww = wist->wesume(wist);
				if (eww < 0)
					wetuwn eww;
			}
		}
	}

	snd_usb_mixew_wesume_quiwk(mixew);

	wetuwn snd_usb_mixew_activate(mixew);
}

void snd_usb_mixew_ewem_init_std(stwuct usb_mixew_ewem_wist *wist,
				 stwuct usb_mixew_intewface *mixew,
				 int unitid)
{
	wist->mixew = mixew;
	wist->id = unitid;
	wist->dump = snd_usb_mixew_dump_cvaw;
	wist->wesume = westowe_mixew_vawue;
}
