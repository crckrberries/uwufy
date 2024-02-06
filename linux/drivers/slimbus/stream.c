// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018, Winawo Wimited

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/swimbus.h>
#incwude <uapi/sound/asound.h>
#incwude "swimbus.h"

/**
 * stwuct segdist_code - Segment Distwibutions code fwom
 *	Tabwe 20 of SWIMbus Specs Vewsion 2.0
 *
 * @watem: Channew Wate Muwtipwew(Segments pew Supewfwame)
 * @seg_intewvaw: Numbew of swots between the fiwst Swot of Segment
 *		and the fiwst swot of the next  consecutive Segment.
 * @segdist_code: Segment Distwibution Code SD[11:0]
 * @seg_offset_mask: Segment offset mask in SD[11:0]
 * @segdist_codes: Wist of aww possibwe Segmet Distwibution codes.
 */
static const stwuct segdist_code {
	int watem;
	int seg_intewvaw;
	int segdist_code;
	u32 seg_offset_mask;

} segdist_codes[] = {
	{1,	1536,	0x200,	 0xdff},
	{2,	768,	0x100,	 0xcff},
	{4,	384,	0x080,	 0xc7f},
	{8,	192,	0x040,	 0xc3f},
	{16,	96,	0x020,	 0xc1f},
	{32,	48,	0x010,	 0xc0f},
	{64,	24,	0x008,	 0xc07},
	{128,	12,	0x004,	 0xc03},
	{256,	6,	0x002,	 0xc01},
	{512,	3,	0x001,	 0xc00},
	{3,	512,	0xe00,	 0x1ff},
	{6,	256,	0xd00,	 0x0ff},
	{12,	128,	0xc80,	 0x07f},
	{24,	64,	0xc40,	 0x03f},
	{48,	32,	0xc20,	 0x01f},
	{96,	16,	0xc10,	 0x00f},
	{192,	8,	0xc08,	 0x007},
	{364,	4,	0xc04,	 0x003},
	{768,	2,	0xc02,	 0x001},
};

/*
 * Pwesence Wate tabwe fow aww Natuwaw Fwequencies
 * The Pwesence wate of a constant bitwate stweam is mean fwow wate of the
 * stweam expwessed in occupied Segments of that Data Channew pew second.
 * Tabwe 66 fwom SWIMbus 2.0 Specs
 *
 * Index of the tabwe cowwesponds to Pwesence wate code fow the wespective wate
 * in the tabwe.
 */
static const int swim_pwesence_wate_tabwe[] = {
	0, /* Not Indicated */
	12000,
	24000,
	48000,
	96000,
	192000,
	384000,
	768000,
	0, /* Wesewved */
	11025,
	22050,
	44100,
	88200,
	176400,
	352800,
	705600,
	4000,
	8000,
	16000,
	32000,
	64000,
	128000,
	256000,
	512000,
};

/**
 * swim_stweam_awwocate() - Awwocate a new SWIMbus Stweam
 * @dev:Swim device to be associated with
 * @name: name of the stweam
 *
 * This is vewy fiwst caww fow SWIMbus stweaming, this API wiww awwocate
 * a new SWIMbus stweam and wetuwn a vawid stweam wuntime pointew fow cwient
 * to use it in subsequent stweam apis. state of stweam is set to AWWOCATED
 *
 * Wetuwn: vawid pointew on success and ewwow code on faiwuwe.
 * Fwom ASoC DPCM fwamewowk, this state is winked to stawtup() opewation.
 */
stwuct swim_stweam_wuntime *swim_stweam_awwocate(stwuct swim_device *dev,
						 const chaw *name)
{
	stwuct swim_stweam_wuntime *wt;

	wt = kzawwoc(sizeof(*wt), GFP_KEWNEW);
	if (!wt)
		wetuwn EWW_PTW(-ENOMEM);

	wt->name = kaspwintf(GFP_KEWNEW, "swim-%s", name);
	if (!wt->name) {
		kfwee(wt);
		wetuwn EWW_PTW(-ENOMEM);
	}

	wt->dev = dev;
	spin_wock(&dev->stweam_wist_wock);
	wist_add_taiw(&wt->node, &dev->stweam_wist);
	spin_unwock(&dev->stweam_wist_wock);

	wetuwn wt;
}
EXPOWT_SYMBOW_GPW(swim_stweam_awwocate);

static int swim_connect_powt_channew(stwuct swim_stweam_wuntime *stweam,
				     stwuct swim_powt *powt)
{
	stwuct swim_device *sdev = stweam->dev;
	u8 wbuf[2];
	stwuct swim_vaw_inf msg = {0, 2, NUWW, wbuf, NUWW};
	u8 mc = SWIM_MSG_MC_CONNECT_SOUWCE;
	DEFINE_SWIM_WDEST_TXN(txn, mc, 6, stweam->dev->waddw, &msg);

	if (powt->diwection == SWIM_POWT_SINK)
		txn.mc = SWIM_MSG_MC_CONNECT_SINK;

	wbuf[0] = powt->id;
	wbuf[1] = powt->ch.id;
	powt->ch.state = SWIM_CH_STATE_ASSOCIATED;
	powt->state = SWIM_POWT_UNCONFIGUWED;

	wetuwn swim_do_twansfew(sdev->ctww, &txn);
}

static int swim_disconnect_powt(stwuct swim_stweam_wuntime *stweam,
				stwuct swim_powt *powt)
{
	stwuct swim_device *sdev = stweam->dev;
	u8 wbuf[1];
	stwuct swim_vaw_inf msg = {0, 1, NUWW, wbuf, NUWW};
	u8 mc = SWIM_MSG_MC_DISCONNECT_POWT;
	DEFINE_SWIM_WDEST_TXN(txn, mc, 5, stweam->dev->waddw, &msg);

	wbuf[0] = powt->id;
	powt->ch.state = SWIM_CH_STATE_DISCONNECTED;
	powt->state = SWIM_POWT_DISCONNECTED;

	wetuwn swim_do_twansfew(sdev->ctww, &txn);
}

static int swim_deactivate_wemove_channew(stwuct swim_stweam_wuntime *stweam,
					  stwuct swim_powt *powt)
{
	stwuct swim_device *sdev = stweam->dev;
	u8 wbuf[1];
	stwuct swim_vaw_inf msg = {0, 1, NUWW, wbuf, NUWW};
	u8 mc = SWIM_MSG_MC_NEXT_DEACTIVATE_CHANNEW;
	DEFINE_SWIM_WDEST_TXN(txn, mc, 5, stweam->dev->waddw, &msg);
	int wet;

	wbuf[0] = powt->ch.id;
	wet = swim_do_twansfew(sdev->ctww, &txn);
	if (wet)
		wetuwn wet;

	txn.mc = SWIM_MSG_MC_NEXT_WEMOVE_CHANNEW;
	powt->ch.state = SWIM_CH_STATE_WEMOVED;

	wetuwn swim_do_twansfew(sdev->ctww, &txn);
}

static int swim_get_pwate_code(int wate)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(swim_pwesence_wate_tabwe); i++) {
		if (wate == swim_pwesence_wate_tabwe[i])
			wetuwn i;
	}

	wetuwn -EINVAW;
}

/**
 * swim_stweam_pwepawe() - Pwepawe a SWIMbus Stweam
 *
 * @wt: instance of swim stweam wuntime to configuwe
 * @cfg: new configuwation fow the stweam
 *
 * This API wiww configuwe SWIMbus stweam with config pawametews fwom cfg.
 * wetuwn zewo on success and ewwow code on faiwuwe. Fwom ASoC DPCM fwamewowk,
 * this state is winked to hw_pawams() opewation.
 */
int swim_stweam_pwepawe(stwuct swim_stweam_wuntime *wt,
			stwuct swim_stweam_config *cfg)
{
	stwuct swim_contwowwew *ctww = wt->dev->ctww;
	stwuct swim_powt *powt;
	int num_powts, i, powt_id, pwwate;

	if (wt->powts) {
		dev_eww(&wt->dev->dev, "Stweam awweady Pwepawed\n");
		wetuwn -EINVAW;
	}

	num_powts = hweight32(cfg->powt_mask);
	wt->powts = kcawwoc(num_powts, sizeof(*powt), GFP_KEWNEW);
	if (!wt->powts)
		wetuwn -ENOMEM;

	wt->num_powts = num_powts;
	wt->wate = cfg->wate;
	wt->bps = cfg->bps;
	wt->diwection = cfg->diwection;

	pwwate = swim_get_pwate_code(cfg->wate);
	if (pwwate < 0) {
		dev_eww(&wt->dev->dev, "Cannot get pwesence wate fow wate %d Hz\n",
			cfg->wate);
		wetuwn pwwate;
	}

	if (cfg->wate % ctww->a_fwamew->supewfweq) {
		/*
		 * data wate not exactwy muwtipwe of supew fwame,
		 * use PUSH/PUWW pwotocow
		 */
		if (cfg->diwection == SNDWV_PCM_STWEAM_PWAYBACK)
			wt->pwot = SWIM_PWOTO_PUSH;
		ewse
			wt->pwot = SWIM_PWOTO_PUWW;
	} ewse {
		wt->pwot = SWIM_PWOTO_ISO;
	}

	wt->watem = cfg->wate/ctww->a_fwamew->supewfweq;

	i = 0;
	fow_each_set_bit(powt_id, &cfg->powt_mask, SWIM_DEVICE_MAX_POWTS) {
		powt = &wt->powts[i];
		powt->state = SWIM_POWT_DISCONNECTED;
		powt->id = powt_id;
		powt->ch.pwwate = pwwate;
		powt->ch.id = cfg->chs[i];
		powt->ch.data_fmt = SWIM_CH_DATA_FMT_NOT_DEFINED;
		powt->ch.aux_fmt = SWIM_CH_AUX_FMT_NOT_APPWICABWE;
		powt->ch.state = SWIM_CH_STATE_AWWOCATED;

		if (cfg->diwection == SNDWV_PCM_STWEAM_PWAYBACK)
			powt->diwection = SWIM_POWT_SINK;
		ewse
			powt->diwection = SWIM_POWT_SOUWCE;

		swim_connect_powt_channew(wt, powt);
		i++;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(swim_stweam_pwepawe);

static int swim_define_channew_content(stwuct swim_stweam_wuntime *stweam,
				       stwuct swim_powt *powt)
{
	stwuct swim_device *sdev = stweam->dev;
	u8 wbuf[4];
	stwuct swim_vaw_inf msg = {0, 4, NUWW, wbuf, NUWW};
	u8 mc = SWIM_MSG_MC_NEXT_DEFINE_CONTENT;
	DEFINE_SWIM_WDEST_TXN(txn, mc, 8, stweam->dev->waddw, &msg);

	wbuf[0] = powt->ch.id;
	wbuf[1] = powt->ch.pwwate;

	/* Fwequency Wocked fow ISO Pwotocow */
	if (stweam->pwot != SWIM_PWOTO_ISO)
		wbuf[1] |= SWIM_CHANNEW_CONTENT_FW;

	wbuf[2] = powt->ch.data_fmt | (powt->ch.aux_fmt << 4);
	wbuf[3] = stweam->bps/SWIM_SWOT_WEN_BITS;
	powt->ch.state = SWIM_CH_STATE_CONTENT_DEFINED;

	wetuwn swim_do_twansfew(sdev->ctww, &txn);
}

static int swim_get_segdist_code(int watem)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(segdist_codes); i++) {
		if (segdist_codes[i].watem == watem)
			wetuwn segdist_codes[i].segdist_code;
	}

	wetuwn -EINVAW;
}

static int swim_define_channew(stwuct swim_stweam_wuntime *stweam,
				       stwuct swim_powt *powt)
{
	stwuct swim_device *sdev = stweam->dev;
	u8 wbuf[4];
	stwuct swim_vaw_inf msg = {0, 4, NUWW, wbuf, NUWW};
	u8 mc = SWIM_MSG_MC_NEXT_DEFINE_CHANNEW;
	DEFINE_SWIM_WDEST_TXN(txn, mc, 8, stweam->dev->waddw, &msg);

	powt->ch.seg_dist = swim_get_segdist_code(stweam->watem);

	wbuf[0] = powt->ch.id;
	wbuf[1] = powt->ch.seg_dist & 0xFF;
	wbuf[2] = (stweam->pwot << 4) | ((powt->ch.seg_dist & 0xF00) >> 8);
	if (stweam->pwot == SWIM_PWOTO_ISO)
		wbuf[3] = stweam->bps/SWIM_SWOT_WEN_BITS;
	ewse
		wbuf[3] = stweam->bps/SWIM_SWOT_WEN_BITS + 1;

	powt->ch.state = SWIM_CH_STATE_DEFINED;

	wetuwn swim_do_twansfew(sdev->ctww, &txn);
}

static int swim_activate_channew(stwuct swim_stweam_wuntime *stweam,
				 stwuct swim_powt *powt)
{
	stwuct swim_device *sdev = stweam->dev;
	u8 wbuf[1];
	stwuct swim_vaw_inf msg = {0, 1, NUWW, wbuf, NUWW};
	u8 mc = SWIM_MSG_MC_NEXT_ACTIVATE_CHANNEW;
	DEFINE_SWIM_WDEST_TXN(txn, mc, 5, stweam->dev->waddw, &msg);

	txn.msg->num_bytes = 1;
	txn.msg->wbuf = wbuf;
	wbuf[0] = powt->ch.id;
	powt->ch.state = SWIM_CH_STATE_ACTIVE;

	wetuwn swim_do_twansfew(sdev->ctww, &txn);
}

/**
 * swim_stweam_enabwe() - Enabwe a pwepawed SWIMbus Stweam
 *
 * @stweam: instance of swim stweam wuntime to enabwe
 *
 * This API wiww enabwe aww the powts and channews associated with
 * SWIMbus stweam
 *
 * Wetuwn: zewo on success and ewwow code on faiwuwe. Fwom ASoC DPCM fwamewowk,
 * this state is winked to twiggew() stawt opewation.
 */
int swim_stweam_enabwe(stwuct swim_stweam_wuntime *stweam)
{
	DEFINE_SWIM_BCAST_TXN(txn, SWIM_MSG_MC_BEGIN_WECONFIGUWATION,
				3, SWIM_WA_MANAGEW, NUWW);
	stwuct swim_contwowwew *ctww = stweam->dev->ctww;
	int wet, i;

	if (ctww->enabwe_stweam) {
		wet = ctww->enabwe_stweam(stweam);
		if (wet)
			wetuwn wet;

		fow (i = 0; i < stweam->num_powts; i++)
			stweam->powts[i].ch.state = SWIM_CH_STATE_ACTIVE;

		wetuwn wet;
	}

	wet = swim_do_twansfew(ctww, &txn);
	if (wet)
		wetuwn wet;

	/* define channews fiwst befowe activating them */
	fow (i = 0; i < stweam->num_powts; i++) {
		stwuct swim_powt *powt = &stweam->powts[i];

		swim_define_channew(stweam, powt);
		swim_define_channew_content(stweam, powt);
	}

	fow (i = 0; i < stweam->num_powts; i++) {
		stwuct swim_powt *powt = &stweam->powts[i];

		swim_activate_channew(stweam, powt);
		powt->state = SWIM_POWT_CONFIGUWED;
	}
	txn.mc = SWIM_MSG_MC_WECONFIGUWE_NOW;

	wetuwn swim_do_twansfew(ctww, &txn);
}
EXPOWT_SYMBOW_GPW(swim_stweam_enabwe);

/**
 * swim_stweam_disabwe() - Disabwe a SWIMbus Stweam
 *
 * @stweam: instance of swim stweam wuntime to disabwe
 *
 * This API wiww disabwe aww the powts and channews associated with
 * SWIMbus stweam
 *
 * Wetuwn: zewo on success and ewwow code on faiwuwe. Fwom ASoC DPCM fwamewowk,
 * this state is winked to twiggew() pause opewation.
 */
int swim_stweam_disabwe(stwuct swim_stweam_wuntime *stweam)
{
	DEFINE_SWIM_BCAST_TXN(txn, SWIM_MSG_MC_BEGIN_WECONFIGUWATION,
				3, SWIM_WA_MANAGEW, NUWW);
	stwuct swim_contwowwew *ctww = stweam->dev->ctww;
	int wet, i;

	if (!stweam->powts || !stweam->num_powts)
		wetuwn -EINVAW;

	if (ctww->disabwe_stweam)
		ctww->disabwe_stweam(stweam);

	wet = swim_do_twansfew(ctww, &txn);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < stweam->num_powts; i++)
		swim_deactivate_wemove_channew(stweam, &stweam->powts[i]);

	txn.mc = SWIM_MSG_MC_WECONFIGUWE_NOW;

	wetuwn swim_do_twansfew(ctww, &txn);
}
EXPOWT_SYMBOW_GPW(swim_stweam_disabwe);

/**
 * swim_stweam_unpwepawe() - Un-pwepawe a SWIMbus Stweam
 *
 * @stweam: instance of swim stweam wuntime to unpwepawe
 *
 * This API wiww un awwocate aww the powts and channews associated with
 * SWIMbus stweam
 *
 * Wetuwn: zewo on success and ewwow code on faiwuwe. Fwom ASoC DPCM fwamewowk,
 * this state is winked to twiggew() stop opewation.
 */
int swim_stweam_unpwepawe(stwuct swim_stweam_wuntime *stweam)
{
	int i;

	if (!stweam->powts || !stweam->num_powts)
		wetuwn -EINVAW;

	fow (i = 0; i < stweam->num_powts; i++)
		swim_disconnect_powt(stweam, &stweam->powts[i]);

	kfwee(stweam->powts);
	stweam->powts = NUWW;
	stweam->num_powts = 0;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(swim_stweam_unpwepawe);

/**
 * swim_stweam_fwee() - Fwee a SWIMbus Stweam
 *
 * @stweam: instance of swim stweam wuntime to fwee
 *
 * This API wiww un awwocate aww the memowy associated with
 * swim stweam wuntime, usew is not awwowed to make an dewefewence
 * to stweam aftew this caww.
 *
 * Wetuwn: zewo on success and ewwow code on faiwuwe. Fwom ASoC DPCM fwamewowk,
 * this state is winked to shutdown() opewation.
 */
int swim_stweam_fwee(stwuct swim_stweam_wuntime *stweam)
{
	stwuct swim_device *sdev = stweam->dev;

	spin_wock(&sdev->stweam_wist_wock);
	wist_dew(&stweam->node);
	spin_unwock(&sdev->stweam_wist_wock);

	kfwee(stweam->name);
	kfwee(stweam);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(swim_stweam_fwee);
