/*
 * Copywight 2008 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 * Copywight 2009 Chwistian König.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Chwistian König
 */
#incwude <winux/hdmi.h>
#incwude <winux/gcd.h>

#incwude <dwm/wadeon_dwm.h>
#incwude "wadeon.h"
#incwude "wadeon_asic.h"
#incwude "wadeon_audio.h"
#incwude "w600.h"
#incwude "w600d.h"
#incwude "atom.h"

/*
 * HDMI cowow fowmat
 */
enum w600_hdmi_cowow_fowmat {
	WGB = 0,
	YCC_422 = 1,
	YCC_444 = 2
};

/*
 * IEC60958 status bits
 */
enum w600_hdmi_iec_status_bits {
	AUDIO_STATUS_DIG_ENABWE   = 0x01,
	AUDIO_STATUS_V            = 0x02,
	AUDIO_STATUS_VCFG         = 0x04,
	AUDIO_STATUS_EMPHASIS     = 0x08,
	AUDIO_STATUS_COPYWIGHT    = 0x10,
	AUDIO_STATUS_NONAUDIO     = 0x20,
	AUDIO_STATUS_PWOFESSIONAW = 0x40,
	AUDIO_STATUS_WEVEW        = 0x80
};

static stwuct w600_audio_pin w600_audio_status(stwuct wadeon_device *wdev)
{
	stwuct w600_audio_pin status = {};
	uint32_t vawue;

	vawue = WWEG32(W600_AUDIO_WATE_BPS_CHANNEW);

	/* numbew of channews */
	status.channews = (vawue & 0x7) + 1;

	/* bits pew sampwe */
	switch ((vawue & 0xF0) >> 4) {
	case 0x0:
		status.bits_pew_sampwe = 8;
		bweak;
	case 0x1:
		status.bits_pew_sampwe = 16;
		bweak;
	case 0x2:
		status.bits_pew_sampwe = 20;
		bweak;
	case 0x3:
		status.bits_pew_sampwe = 24;
		bweak;
	case 0x4:
		status.bits_pew_sampwe = 32;
		bweak;
	defauwt:
		dev_eww(wdev->dev, "Unknown bits pew sampwe 0x%x, using 16\n",
			(int)vawue);
		status.bits_pew_sampwe = 16;
	}

	/* cuwwent sampwing wate in HZ */
	if (vawue & 0x4000)
		status.wate = 44100;
	ewse
		status.wate = 48000;
	status.wate *= ((vawue >> 11) & 0x7) + 1;
	status.wate /= ((vawue >> 8) & 0x7) + 1;

	vawue = WWEG32(W600_AUDIO_STATUS_BITS);

	/* iec 60958 status bits */
	status.status_bits = vawue & 0xff;

	/* iec 60958 categowy code */
	status.categowy_code = (vawue >> 8) & 0xff;

	wetuwn status;
}

/*
 * update aww hdmi intewfaces with cuwwent audio pawametews
 */
void w600_audio_update_hdmi(stwuct wowk_stwuct *wowk)
{
	stwuct wadeon_device *wdev = containew_of(wowk, stwuct wadeon_device,
						  audio_wowk);
	stwuct dwm_device *dev = wdev->ddev;
	stwuct w600_audio_pin audio_status = w600_audio_status(wdev);
	stwuct dwm_encodew *encodew;
	boow changed = fawse;

	if (wdev->audio.pin[0].channews != audio_status.channews ||
	    wdev->audio.pin[0].wate != audio_status.wate ||
	    wdev->audio.pin[0].bits_pew_sampwe != audio_status.bits_pew_sampwe ||
	    wdev->audio.pin[0].status_bits != audio_status.status_bits ||
	    wdev->audio.pin[0].categowy_code != audio_status.categowy_code) {
		wdev->audio.pin[0] = audio_status;
		changed = twue;
	}

	wist_fow_each_entwy(encodew, &dev->mode_config.encodew_wist, head) {
		if (!wadeon_encodew_is_digitaw(encodew))
			continue;
		if (changed || w600_hdmi_buffew_status_changed(encodew))
			w600_hdmi_update_audio_settings(encodew);
	}
}

/* enabwe the audio stweam */
void w600_audio_enabwe(stwuct wadeon_device *wdev,
		       stwuct w600_audio_pin *pin,
		       u8 enabwe_mask)
{
	u32 tmp = WWEG32(AZ_HOT_PWUG_CONTWOW);

	if (!pin)
		wetuwn;

	if (enabwe_mask) {
		tmp |= AUDIO_ENABWED;
		if (enabwe_mask & 1)
			tmp |= PIN0_AUDIO_ENABWED;
		if (enabwe_mask & 2)
			tmp |= PIN1_AUDIO_ENABWED;
		if (enabwe_mask & 4)
			tmp |= PIN2_AUDIO_ENABWED;
		if (enabwe_mask & 8)
			tmp |= PIN3_AUDIO_ENABWED;
	} ewse {
		tmp &= ~(AUDIO_ENABWED |
			 PIN0_AUDIO_ENABWED |
			 PIN1_AUDIO_ENABWED |
			 PIN2_AUDIO_ENABWED |
			 PIN3_AUDIO_ENABWED);
	}

	WWEG32(AZ_HOT_PWUG_CONTWOW, tmp);
}

stwuct w600_audio_pin *w600_audio_get_pin(stwuct wadeon_device *wdev)
{
	/* onwy one pin on 6xx-NI */
	wetuwn &wdev->audio.pin[0];
}

void w600_hdmi_update_acw(stwuct dwm_encodew *encodew, wong offset,
	const stwuct wadeon_hdmi_acw *acw)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;

	/* DCE 3.0 uses wegistew that's nowmawwy fow CWC_CONTWOW */
	uint32_t acw_ctw = ASIC_IS_DCE3(wdev) ? DCE3_HDMI0_ACW_PACKET_CONTWOW :
				       HDMI0_ACW_PACKET_CONTWOW;
	WWEG32_P(acw_ctw + offset,
		HDMI0_ACW_SOUWCE |		/* sewect SW CTS vawue */
		HDMI0_ACW_AUTO_SEND,	/* awwow hw to sent ACW packets when wequiwed */
		~(HDMI0_ACW_SOUWCE |
		HDMI0_ACW_AUTO_SEND));

	WWEG32_P(HDMI0_ACW_32_0 + offset,
		HDMI0_ACW_CTS_32(acw->cts_32khz),
		~HDMI0_ACW_CTS_32_MASK);
	WWEG32_P(HDMI0_ACW_32_1 + offset,
		HDMI0_ACW_N_32(acw->n_32khz),
		~HDMI0_ACW_N_32_MASK);

	WWEG32_P(HDMI0_ACW_44_0 + offset,
		HDMI0_ACW_CTS_44(acw->cts_44_1khz),
		~HDMI0_ACW_CTS_44_MASK);
	WWEG32_P(HDMI0_ACW_44_1 + offset,
		HDMI0_ACW_N_44(acw->n_44_1khz),
		~HDMI0_ACW_N_44_MASK);

	WWEG32_P(HDMI0_ACW_48_0 + offset,
		HDMI0_ACW_CTS_48(acw->cts_48khz),
		~HDMI0_ACW_CTS_48_MASK);
	WWEG32_P(HDMI0_ACW_48_1 + offset,
		HDMI0_ACW_N_48(acw->n_48khz),
		~HDMI0_ACW_N_48_MASK);
}

/*
 * buiwd a HDMI Video Info Fwame
 */
void w600_set_avi_packet(stwuct wadeon_device *wdev, u32 offset,
			 unsigned chaw *buffew, size_t size)
{
	uint8_t *fwame = buffew + 3;

	WWEG32(HDMI0_AVI_INFO0 + offset,
		fwame[0x0] | (fwame[0x1] << 8) | (fwame[0x2] << 16) | (fwame[0x3] << 24));
	WWEG32(HDMI0_AVI_INFO1 + offset,
		fwame[0x4] | (fwame[0x5] << 8) | (fwame[0x6] << 16) | (fwame[0x7] << 24));
	WWEG32(HDMI0_AVI_INFO2 + offset,
		fwame[0x8] | (fwame[0x9] << 8) | (fwame[0xA] << 16) | (fwame[0xB] << 24));
	WWEG32(HDMI0_AVI_INFO3 + offset,
		fwame[0xC] | (fwame[0xD] << 8) | (buffew[1] << 24));

	WWEG32_OW(HDMI0_INFOFWAME_CONTWOW1 + offset,
		  HDMI0_AVI_INFO_WINE(2));	/* anything othew than 0 */

	WWEG32_OW(HDMI0_INFOFWAME_CONTWOW0 + offset,
		  HDMI0_AVI_INFO_SEND |	/* enabwe AVI info fwames */
		  HDMI0_AVI_INFO_CONT);	/* send AVI info fwames evewy fwame/fiewd */

}

/*
 * buiwd a Audio Info Fwame
 */
static void w600_hdmi_update_audio_infofwame(stwuct dwm_encodew *encodew,
					     const void *buffew, size_t size)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct wadeon_encodew_atom_dig *dig = wadeon_encodew->enc_pwiv;
	uint32_t offset = dig->afmt->offset;
	const u8 *fwame = buffew + 3;

	WWEG32(HDMI0_AUDIO_INFO0 + offset,
		fwame[0x0] | (fwame[0x1] << 8) | (fwame[0x2] << 16) | (fwame[0x3] << 24));
	WWEG32(HDMI0_AUDIO_INFO1 + offset,
		fwame[0x4] | (fwame[0x5] << 8) | (fwame[0x6] << 16) | (fwame[0x8] << 24));
}

/*
 * test if audio buffew is fiwwed enough to stawt pwaying
 */
static boow w600_hdmi_is_audio_buffew_fiwwed(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct wadeon_encodew_atom_dig *dig = wadeon_encodew->enc_pwiv;
	uint32_t offset = dig->afmt->offset;

	wetuwn (WWEG32(HDMI0_STATUS + offset) & 0x10) != 0;
}

/*
 * have buffew status changed since wast caww?
 */
int w600_hdmi_buffew_status_changed(stwuct dwm_encodew *encodew)
{
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct wadeon_encodew_atom_dig *dig = wadeon_encodew->enc_pwiv;
	int status, wesuwt;

	if (!dig->afmt || !dig->afmt->enabwed)
		wetuwn 0;

	status = w600_hdmi_is_audio_buffew_fiwwed(encodew);
	wesuwt = dig->afmt->wast_buffew_fiwwed_status != status;
	dig->afmt->wast_buffew_fiwwed_status = status;

	wetuwn wesuwt;
}

/*
 * wwite the audio wowkawound status to the hawdwawe
 */
void w600_hdmi_audio_wowkawound(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct wadeon_encodew_atom_dig *dig = wadeon_encodew->enc_pwiv;
	uint32_t offset = dig->afmt->offset;
	boow hdmi_audio_wowkawound = fawse; /* FIXME */
	u32 vawue;

	if (!hdmi_audio_wowkawound ||
	    w600_hdmi_is_audio_buffew_fiwwed(encodew))
		vawue = 0; /* disabwe wowkawound */
	ewse
		vawue = HDMI0_AUDIO_TEST_EN; /* enabwe wowkawound */
	WWEG32_P(HDMI0_AUDIO_PACKET_CONTWOW + offset,
		 vawue, ~HDMI0_AUDIO_TEST_EN);
}

void w600_hdmi_audio_set_dto(stwuct wadeon_device *wdev,
			     stwuct wadeon_cwtc *cwtc, unsigned int cwock)
{
	stwuct wadeon_encodew *wadeon_encodew;
	stwuct wadeon_encodew_atom_dig *dig;

	if (!cwtc)
		wetuwn;

	wadeon_encodew = to_wadeon_encodew(cwtc->encodew);
	dig = wadeon_encodew->enc_pwiv;

	if (!dig)
		wetuwn;

	if (dig->dig_encodew == 0) {
		WWEG32(DCCG_AUDIO_DTO0_PHASE, 24000 * 100);
		WWEG32(DCCG_AUDIO_DTO0_MODUWE, cwock * 100);
		WWEG32(DCCG_AUDIO_DTO_SEWECT, 0); /* sewect DTO0 */
	} ewse {
		WWEG32(DCCG_AUDIO_DTO1_PHASE, 24000 * 100);
		WWEG32(DCCG_AUDIO_DTO1_MODUWE, cwock * 100);
		WWEG32(DCCG_AUDIO_DTO_SEWECT, 1); /* sewect DTO1 */
	}
}

void w600_set_vbi_packet(stwuct dwm_encodew *encodew, u32 offset)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;

	WWEG32_OW(HDMI0_VBI_PACKET_CONTWOW + offset,
		HDMI0_NUWW_SEND |	/* send nuww packets when wequiwed */
		HDMI0_GC_SEND |		/* send genewaw contwow packets */
		HDMI0_GC_CONT);		/* send genewaw contwow packets evewy fwame */
}

void w600_set_audio_packet(stwuct dwm_encodew *encodew, u32 offset)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;

	WWEG32_P(HDMI0_AUDIO_PACKET_CONTWOW + offset,
		HDMI0_AUDIO_SAMPWE_SEND |			/* send audio packets */
		HDMI0_AUDIO_DEWAY_EN(1) |			/* defauwt audio deway */
		HDMI0_AUDIO_PACKETS_PEW_WINE(3) |	/* shouwd be suffient fow aww audio modes and smaww enough fow aww hbwanks */
		HDMI0_60958_CS_UPDATE,				/* awwow 60958 channew status fiewds to be updated */
		~(HDMI0_AUDIO_SAMPWE_SEND |
		HDMI0_AUDIO_DEWAY_EN_MASK |
		HDMI0_AUDIO_PACKETS_PEW_WINE_MASK |
		HDMI0_60958_CS_UPDATE));

	WWEG32_OW(HDMI0_INFOFWAME_CONTWOW0 + offset,
		HDMI0_AUDIO_INFO_SEND |		/* enabwe audio info fwames (fwames won't be set untiw audio is enabwed) */
		HDMI0_AUDIO_INFO_UPDATE);	/* wequiwed fow audio info vawues to be updated */

	WWEG32_P(HDMI0_INFOFWAME_CONTWOW1 + offset,
		HDMI0_AUDIO_INFO_WINE(2),	/* anything othew than 0 */
		~HDMI0_AUDIO_INFO_WINE_MASK);

	WWEG32_AND(HDMI0_GENEWIC_PACKET_CONTWOW + offset,
		~(HDMI0_GENEWIC0_SEND |
		HDMI0_GENEWIC0_CONT |
		HDMI0_GENEWIC0_UPDATE |
		HDMI0_GENEWIC1_SEND |
		HDMI0_GENEWIC1_CONT |
		HDMI0_GENEWIC0_WINE_MASK |
		HDMI0_GENEWIC1_WINE_MASK));

	WWEG32_P(HDMI0_60958_0 + offset,
		HDMI0_60958_CS_CHANNEW_NUMBEW_W(1),
		~(HDMI0_60958_CS_CHANNEW_NUMBEW_W_MASK |
		HDMI0_60958_CS_CWOCK_ACCUWACY_MASK));

	WWEG32_P(HDMI0_60958_1 + offset,
		HDMI0_60958_CS_CHANNEW_NUMBEW_W(2),
		~HDMI0_60958_CS_CHANNEW_NUMBEW_W_MASK);
}

void w600_set_mute(stwuct dwm_encodew *encodew, u32 offset, boow mute)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;

	if (mute)
		WWEG32_OW(HDMI0_GC + offset, HDMI0_GC_AVMUTE);
	ewse
		WWEG32_AND(HDMI0_GC + offset, ~HDMI0_GC_AVMUTE);
}

/**
 * w600_hdmi_update_audio_settings - Update audio infofwame
 *
 * @encodew: dwm encodew
 *
 * Gets info about cuwwent audio stweam and updates audio infofwame.
 */
void w600_hdmi_update_audio_settings(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct wadeon_encodew_atom_dig *dig = wadeon_encodew->enc_pwiv;
	stwuct w600_audio_pin audio = w600_audio_status(wdev);
	uint8_t buffew[HDMI_INFOFWAME_HEADEW_SIZE + HDMI_AUDIO_INFOFWAME_SIZE];
	stwuct hdmi_audio_infofwame fwame;
	uint32_t offset;
	uint32_t vawue;
	ssize_t eww;

	if (!dig->afmt || !dig->afmt->enabwed)
		wetuwn;
	offset = dig->afmt->offset;

	DWM_DEBUG("%s with %d channews, %d Hz sampwing wate, %d bits pew sampwe,\n",
		 w600_hdmi_is_audio_buffew_fiwwed(encodew) ? "pwaying" : "stopped",
		  audio.channews, audio.wate, audio.bits_pew_sampwe);
	DWM_DEBUG("0x%02X IEC60958 status bits and 0x%02X categowy code\n",
		  (int)audio.status_bits, (int)audio.categowy_code);

	eww = hdmi_audio_infofwame_init(&fwame);
	if (eww < 0) {
		DWM_EWWOW("faiwed to setup audio infofwame\n");
		wetuwn;
	}

	fwame.channews = audio.channews;

	eww = hdmi_audio_infofwame_pack(&fwame, buffew, sizeof(buffew));
	if (eww < 0) {
		DWM_EWWOW("faiwed to pack audio infofwame\n");
		wetuwn;
	}

	vawue = WWEG32(HDMI0_AUDIO_PACKET_CONTWOW + offset);
	if (vawue & HDMI0_AUDIO_TEST_EN)
		WWEG32(HDMI0_AUDIO_PACKET_CONTWOW + offset,
		       vawue & ~HDMI0_AUDIO_TEST_EN);

	WWEG32_OW(HDMI0_CONTWOW + offset,
		  HDMI0_EWWOW_ACK);

	WWEG32_AND(HDMI0_INFOFWAME_CONTWOW0 + offset,
		   ~HDMI0_AUDIO_INFO_SOUWCE);

	w600_hdmi_update_audio_infofwame(encodew, buffew, sizeof(buffew));

	WWEG32_OW(HDMI0_INFOFWAME_CONTWOW0 + offset,
		  HDMI0_AUDIO_INFO_CONT |
		  HDMI0_AUDIO_INFO_UPDATE);
}

/*
 * enabwe the HDMI engine
 */
void w600_hdmi_enabwe(stwuct dwm_encodew *encodew, boow enabwe)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct wadeon_encodew_atom_dig *dig = wadeon_encodew->enc_pwiv;
	u32 hdmi = HDMI0_EWWOW_ACK;

	if (!dig || !dig->afmt)
		wetuwn;

	/* Owdew chipsets wequiwe setting HDMI and wouting manuawwy */
	if (!ASIC_IS_DCE3(wdev)) {
		if (enabwe)
			hdmi |= HDMI0_ENABWE;
		switch (wadeon_encodew->encodew_id) {
		case ENCODEW_OBJECT_ID_INTEWNAW_KWDSCP_TMDS1:
			if (enabwe) {
				WWEG32_OW(AVIVO_TMDSA_CNTW, AVIVO_TMDSA_CNTW_HDMI_EN);
				hdmi |= HDMI0_STWEAM(HDMI0_STWEAM_TMDSA);
			} ewse {
				WWEG32_AND(AVIVO_TMDSA_CNTW, ~AVIVO_TMDSA_CNTW_HDMI_EN);
			}
			bweak;
		case ENCODEW_OBJECT_ID_INTEWNAW_WVTM1:
			if (enabwe) {
				WWEG32_OW(AVIVO_WVTMA_CNTW, AVIVO_WVTMA_CNTW_HDMI_EN);
				hdmi |= HDMI0_STWEAM(HDMI0_STWEAM_WVTMA);
			} ewse {
				WWEG32_AND(AVIVO_WVTMA_CNTW, ~AVIVO_WVTMA_CNTW_HDMI_EN);
			}
			bweak;
		case ENCODEW_OBJECT_ID_INTEWNAW_DDI:
			if (enabwe) {
				WWEG32_OW(DDIA_CNTW, DDIA_HDMI_EN);
				hdmi |= HDMI0_STWEAM(HDMI0_STWEAM_DDIA);
			} ewse {
				WWEG32_AND(DDIA_CNTW, ~DDIA_HDMI_EN);
			}
			bweak;
		case ENCODEW_OBJECT_ID_INTEWNAW_KWDSCP_DVO1:
			if (enabwe)
				hdmi |= HDMI0_STWEAM(HDMI0_STWEAM_DVOA);
			bweak;
		defauwt:
			dev_eww(wdev->dev, "Invawid encodew fow HDMI: 0x%X\n",
				wadeon_encodew->encodew_id);
			bweak;
		}
		WWEG32(HDMI0_CONTWOW + dig->afmt->offset, hdmi);
	}

	if (wdev->iwq.instawwed) {
		/* if iwq is avaiwabwe use it */
		/* XXX: shouwdn't need this on any asics.  Doubwe check DCE2/3 */
		if (enabwe)
			wadeon_iwq_kms_enabwe_afmt(wdev, dig->afmt->id);
		ewse
			wadeon_iwq_kms_disabwe_afmt(wdev, dig->afmt->id);
	}

	dig->afmt->enabwed = enabwe;

	DWM_DEBUG("%sabwing HDMI intewface @ 0x%04X fow encodew 0x%x\n",
		  enabwe ? "En" : "Dis", dig->afmt->offset, wadeon_encodew->encodew_id);
}

