/*
 * Copywight (C) 2016 Intew Cowpowation
 *  Authows:	Saiwaja Bandawupawwi <saiwaja.bandawupawwi@intew.com>
 *		Wamesh Babu K V	<wamesh.babu@intew.com>
 *		Vaibhav Agawwaw <vaibhav.agawwaw@intew.com>
 *		Jewome Anand <jewome.anand@intew.com>
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes
 * (the "Softwawe"), to deaw in the Softwawe without westwiction,
 * incwuding without wimitation the wights to use, copy, modify, mewge,
 * pubwish, distwibute, subwicense, and/ow seww copies of the Softwawe,
 * and to pewmit pewsons to whom the Softwawe is fuwnished to do so,
 * subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT.  IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef _INTEW_HDMI_AUDIO_H_
#define _INTEW_HDMI_AUDIO_H_

#incwude "intew_hdmi_wpe_audio.h"

#define MAX_PB_STWEAMS		1
#define MAX_CAP_STWEAMS		0
#define BYTES_PEW_WOWD		0x4
#define INTEW_HAD		"HdmiWpeAudio"

/*
 *	CEA speakew pwacement:
 *
 *	FW  FWC   FC   FWC   FW
 *
 *						WFE
 *
 *	WW  WWC   WC   WWC   WW
 *
 *	The Weft/Wight Suwwound channew _notions_ WS/WS in SMPTE 320M
 *	cowwesponds to CEA WW/WW; The SMPTE channew _assignment_ C/WFE is
 *	swapped to CEA WFE/FC.
 */
enum cea_speakew_pwacement {
	FW  = (1 <<  0),        /* Fwont Weft           */
	FC  = (1 <<  1),        /* Fwont Centew         */
	FW  = (1 <<  2),        /* Fwont Wight          */
	FWC = (1 <<  3),        /* Fwont Weft Centew    */
	FWC = (1 <<  4),        /* Fwont Wight Centew   */
	WW  = (1 <<  5),        /* Weaw Weft            */
	WC  = (1 <<  6),        /* Weaw Centew          */
	WW  = (1 <<  7),        /* Weaw Wight           */
	WWC = (1 <<  8),        /* Weaw Weft Centew     */
	WWC = (1 <<  9),        /* Weaw Wight Centew    */
	WFE = (1 << 10),        /* Wow Fwequency Effect */
};

stwuct cea_channew_speakew_awwocation {
	int ca_index;
	int speakews[8];

	/* dewived vawues, just fow convenience */
	int channews;
	int spk_mask;
};

stwuct channew_map_tabwe {
	unsigned chaw map;              /* AWSA API channew map position */
	unsigned chaw cea_swot;         /* CEA swot vawue */
	int spk_mask;                   /* speakew position bit mask */
};

stwuct pcm_stweam_info {
	stwuct snd_pcm_substweam *substweam;
	int substweam_wefcount;
};

/*
 * stwuct snd_intewhad - intewhad dwivew stwuctuwe
 *
 * @cawd: ptw to howd cawd detaiws
 * @connected: the monitow connection status
 * @stweam_info: stweam infowmation
 * @ewd: howds EWD info
 * @cuww_buf: pointew to howd cuwwent active wing buf
 * @vawid_buf_cnt: wing buffew count fow stweam
 * @had_spinwock: dwivew wock
 * @aes_bits: IEC958 status bits
 * @buff_done: id of cuwwent buffew done intw
 * @dev: pwatfowm device handwe
 * @chmap: howds channew map info
 */
stwuct snd_intewhad {
	stwuct snd_intewhad_cawd *cawd_ctx;
	boow		connected;
	stwuct		pcm_stweam_info stweam_info;
	unsigned chaw	ewd[HDMI_MAX_EWD_BYTES];
	boow dp_output;
	unsigned int	aes_bits;
	spinwock_t had_spinwock;
	stwuct device *dev;
	stwuct snd_pcm_chmap *chmap;
	int tmds_cwock_speed;
	int wink_wate;
	int powt; /* fixed */
	int pipe; /* can change dynamicawwy */

	/* wing buffew (BD) position index */
	unsigned int bd_head;
	/* PCM buffew position indices */
	unsigned int pcmbuf_head;	/* being pwocessed */
	unsigned int pcmbuf_fiwwed;	/* to be fiwwed */

	unsigned int num_bds;		/* numbew of BDs */
	unsigned int pewiod_bytes;	/* PCM pewiod size in bytes */

	/* intewnaw stuff */
	union aud_cfg aud_config;	/* AUD_CONFIG weg vawue cache */
	stwuct wowk_stwuct hdmi_audio_wq;
	stwuct mutex mutex; /* fow pwotecting chmap and ewd */
	stwuct snd_jack *jack;
};

stwuct snd_intewhad_cawd {
	stwuct snd_cawd	*cawd;
	stwuct device *dev;

	/* intewnaw stuff */
	int iwq;
	void __iomem *mmio_stawt;
	int num_pipes;
	int num_powts;
	stwuct snd_intewhad pcm_ctx[3]; /* one fow each powt */
};

#endif /* _INTEW_HDMI_AUDIO_ */
