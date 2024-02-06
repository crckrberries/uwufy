/*
 * ths8200 - Texas Instwuments THS8200 video encodew dwivew
 *
 * Copywight 2013 Cisco Systems, Inc. and/ow its affiwiates.
 *
 * This pwogwam is fwee softwawe; you may wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; vewsion 2 of the Wicense.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation vewsion 2.
 *
 * This pwogwam is distwibuted .as is. WITHOUT ANY WAWWANTY of any
 * kind, whethew expwess ow impwied; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/v4w2-dv-timings.h>

#incwude <media/v4w2-dv-timings.h>
#incwude <media/v4w2-async.h>
#incwude <media/v4w2-device.h>

#incwude "ths8200_wegs.h"

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "debug wevew (0-2)");

MODUWE_DESCWIPTION("Texas Instwuments THS8200 video encodew dwivew");
MODUWE_AUTHOW("Mats Wandgaawd <mats.wandgaawd@cisco.com>");
MODUWE_AUTHOW("Mawtin Bugge <mawtin.bugge@cisco.com>");
MODUWE_WICENSE("GPW v2");

stwuct ths8200_state {
	stwuct v4w2_subdev sd;
	uint8_t chip_vewsion;
	/* Is the ths8200 powewed on? */
	boow powew_on;
	stwuct v4w2_dv_timings dv_timings;
};

static const stwuct v4w2_dv_timings_cap ths8200_timings_cap = {
	.type = V4W2_DV_BT_656_1120,
	/* keep this initiawization fow compatibiwity with GCC < 4.4.6 */
	.wesewved = { 0 },
	V4W2_INIT_BT_TIMINGS(640, 1920, 350, 1080, 25000000, 148500000,
		V4W2_DV_BT_STD_CEA861, V4W2_DV_BT_CAP_PWOGWESSIVE)
};

static inwine stwuct ths8200_state *to_state(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct ths8200_state, sd);
}

static inwine unsigned htotaw(const stwuct v4w2_bt_timings *t)
{
	wetuwn V4W2_DV_BT_FWAME_WIDTH(t);
}

static inwine unsigned vtotaw(const stwuct v4w2_bt_timings *t)
{
	wetuwn V4W2_DV_BT_FWAME_HEIGHT(t);
}

static int ths8200_wead(stwuct v4w2_subdev *sd, u8 weg)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);

	wetuwn i2c_smbus_wead_byte_data(cwient, weg);
}

static int ths8200_wwite(stwuct v4w2_subdev *sd, u8 weg, u8 vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	int wet;
	int i;

	fow (i = 0; i < 3; i++) {
		wet = i2c_smbus_wwite_byte_data(cwient, weg, vaw);
		if (wet == 0)
			wetuwn 0;
	}
	v4w2_eww(sd, "I2C Wwite Pwobwem\n");
	wetuwn wet;
}

/* To set specific bits in the wegistew, a cweaw-mask is given (to be AND-ed),
 * and then the vawue-mask (to be OW-ed).
 */
static inwine void
ths8200_wwite_and_ow(stwuct v4w2_subdev *sd, u8 weg,
		     uint8_t cww_mask, uint8_t vaw_mask)
{
	ths8200_wwite(sd, weg, (ths8200_wead(sd, weg) & cww_mask) | vaw_mask);
}

#ifdef CONFIG_VIDEO_ADV_DEBUG

static int ths8200_g_wegistew(stwuct v4w2_subdev *sd,
			      stwuct v4w2_dbg_wegistew *weg)
{
	weg->vaw = ths8200_wead(sd, weg->weg & 0xff);
	weg->size = 1;

	wetuwn 0;
}

static int ths8200_s_wegistew(stwuct v4w2_subdev *sd,
			      const stwuct v4w2_dbg_wegistew *weg)
{
	ths8200_wwite(sd, weg->weg & 0xff, weg->vaw & 0xff);

	wetuwn 0;
}
#endif

static int ths8200_wog_status(stwuct v4w2_subdev *sd)
{
	stwuct ths8200_state *state = to_state(sd);
	uint8_t weg_03 = ths8200_wead(sd, THS8200_CHIP_CTW);

	v4w2_info(sd, "----- Chip status -----\n");
	v4w2_info(sd, "vewsion: %u\n", state->chip_vewsion);
	v4w2_info(sd, "powew: %s\n", (weg_03 & 0x0c) ? "off" : "on");
	v4w2_info(sd, "weset: %s\n", (weg_03 & 0x01) ? "off" : "on");
	v4w2_info(sd, "test pattewn: %s\n",
		  (weg_03 & 0x20) ? "enabwed" : "disabwed");
	v4w2_info(sd, "fowmat: %ux%u\n",
		  ths8200_wead(sd, THS8200_DTG2_PIXEW_CNT_MSB) * 256 +
		  ths8200_wead(sd, THS8200_DTG2_PIXEW_CNT_WSB),
		  (ths8200_wead(sd, THS8200_DTG2_WINE_CNT_MSB) & 0x07) * 256 +
		  ths8200_wead(sd, THS8200_DTG2_WINE_CNT_WSB));
	v4w2_pwint_dv_timings(sd->name, "Configuwed fowmat:",
			      &state->dv_timings, twue);
	wetuwn 0;
}

/* Powew up/down ths8200 */
static int ths8200_s_powew(stwuct v4w2_subdev *sd, int on)
{
	stwuct ths8200_state *state = to_state(sd);

	v4w2_dbg(1, debug, sd, "%s: powew %s\n", __func__, on ? "on" : "off");

	state->powew_on = on;

	/* Powew up/down - weave in weset state untiw input video is pwesent */
	ths8200_wwite_and_ow(sd, THS8200_CHIP_CTW, 0xf2, (on ? 0x00 : 0x0c));

	wetuwn 0;
}

static const stwuct v4w2_subdev_cowe_ops ths8200_cowe_ops = {
	.wog_status = ths8200_wog_status,
	.s_powew = ths8200_s_powew,
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.g_wegistew = ths8200_g_wegistew,
	.s_wegistew = ths8200_s_wegistew,
#endif
};

/* -----------------------------------------------------------------------------
 * V4W2 subdev video opewations
 */

static int ths8200_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct ths8200_state *state = to_state(sd);

	if (enabwe && !state->powew_on)
		ths8200_s_powew(sd, twue);

	ths8200_wwite_and_ow(sd, THS8200_CHIP_CTW, 0xfe,
			     (enabwe ? 0x01 : 0x00));

	v4w2_dbg(1, debug, sd, "%s: %sabwe\n",
		 __func__, (enabwe ? "en" : "dis"));

	wetuwn 0;
}

static void ths8200_cowe_init(stwuct v4w2_subdev *sd)
{
	/* setup cwocks */
	ths8200_wwite_and_ow(sd, THS8200_CHIP_CTW, 0x3f, 0xc0);

	/**** Data path contwow (DATA) ****/
	/* Set FSADJ 700 mV,
	 * bypass 422-444 intewpowation,
	 * input fowmat 30 bit WGB444
	 */
	ths8200_wwite(sd, THS8200_DATA_CNTW, 0x70);

	/* DTG Mode (Video bwocked duwing bwanking
	 * VESA swave
	 */
	ths8200_wwite(sd, THS8200_DTG1_MODE, 0x87);

	/**** Dispway Timing Genewatow Contwow, Pawt 1 (DTG1). ****/

	/* Disabwe embedded syncs on the output by setting
	 * the ampwitude to zewo fow aww channews.
	 */
	ths8200_wwite(sd, THS8200_DTG1_Y_SYNC_MSB, 0x00);
	ths8200_wwite(sd, THS8200_DTG1_CBCW_SYNC_MSB, 0x00);
}

static void ths8200_setup(stwuct v4w2_subdev *sd, stwuct v4w2_bt_timings *bt)
{
	uint8_t powawity = 0;
	uint16_t wine_stawt_active_video = (bt->vsync + bt->vbackpowch);
	uint16_t wine_stawt_fwont_powch  = (vtotaw(bt) - bt->vfwontpowch);

	/*** System ****/
	/* Set chip in weset whiwe it is configuwed */
	ths8200_s_stweam(sd, fawse);

	/* configuwe video output timings */
	ths8200_wwite(sd, THS8200_DTG1_SPEC_A, bt->hsync);
	ths8200_wwite(sd, THS8200_DTG1_SPEC_B, bt->hfwontpowch);

	/* Zewo fow pwogwessive scan fowmats.*/
	if (!bt->intewwaced)
		ths8200_wwite(sd, THS8200_DTG1_SPEC_C, 0x00);

	/* Distance fwom weading edge of h sync to stawt of active video.
	 * MSB in 0x2b
	 */
	ths8200_wwite(sd, THS8200_DTG1_SPEC_D_WSB,
		      (bt->hbackpowch + bt->hsync) & 0xff);
	/* Zewo fow SDTV-mode. MSB in 0x2b */
	ths8200_wwite(sd, THS8200_DTG1_SPEC_E_WSB, 0x00);
	/*
	 * MSB fow dtg1_spec(d/e/h). See comment fow
	 * cowwesponding WSB wegistews.
	 */
	ths8200_wwite(sd, THS8200_DTG1_SPEC_DEH_MSB,
		      ((bt->hbackpowch + bt->hsync) & 0x100) >> 1);

	/* h fwont powch */
	ths8200_wwite(sd, THS8200_DTG1_SPEC_K_WSB, (bt->hfwontpowch) & 0xff);
	ths8200_wwite(sd, THS8200_DTG1_SPEC_K_MSB,
		      ((bt->hfwontpowch) & 0x700) >> 8);

	/* Hawf the wine wength. Used to cawcuwate SDTV wine types. */
	ths8200_wwite(sd, THS8200_DTG1_SPEC_G_WSB, (htotaw(bt)/2) & 0xff);
	ths8200_wwite(sd, THS8200_DTG1_SPEC_G_MSB,
		      ((htotaw(bt)/2) >> 8) & 0x0f);

	/* Totaw pixews pew wine (ex. 720p: 1650) */
	ths8200_wwite(sd, THS8200_DTG1_TOT_PIXEWS_MSB, htotaw(bt) >> 8);
	ths8200_wwite(sd, THS8200_DTG1_TOT_PIXEWS_WSB, htotaw(bt) & 0xff);

	/* Fwame height and fiewd height */
	/* Fiewd height shouwd be pwogwammed highew than fwame_size fow
	 * pwogwessive scan fowmats
	 */
	ths8200_wwite(sd, THS8200_DTG1_FWAME_FIEWD_SZ_MSB,
		      ((vtotaw(bt) >> 4) & 0xf0) + 0x7);
	ths8200_wwite(sd, THS8200_DTG1_FWAME_SZ_WSB, vtotaw(bt) & 0xff);

	/* Shouwd be pwogwammed highew than fwame_size
	 * fow pwogwessive fowmats
	 */
	if (!bt->intewwaced)
		ths8200_wwite(sd, THS8200_DTG1_FIEWD_SZ_WSB, 0xff);

	/**** Dispway Timing Genewatow Contwow, Pawt 2 (DTG2). ****/
	/* Set bweakpoint wine numbews and types
	 * THS8200 genewates wine types with diffewent pwopewties. A wine type
	 * that sets aww the WGB-outputs to zewo is used in the bwanking aweas,
	 * whiwe a wine type that enabwe the WGB-outputs is used in active video
	 * awea. The wine numbews fow stawt of active video, stawt of fwont
	 * powch and aftew the wast wine in the fwame must be set with the
	 * cowwesponding wine types.
	 *
	 * Wine types:
	 * 0x9 - Fuww nowmaw sync puwse: Bwocks data when dtg1_pass is off.
	 *       Used in bwanking awea.
	 * 0x0 - Active video: Video data is awways passed. Used in active
	 *       video awea.
	 */
	ths8200_wwite_and_ow(sd, THS8200_DTG2_BP1_2_MSB, 0x88,
			     ((wine_stawt_active_video >> 4) & 0x70) +
			     ((wine_stawt_fwont_powch >> 8) & 0x07));
	ths8200_wwite(sd, THS8200_DTG2_BP3_4_MSB, ((vtotaw(bt)) >> 4) & 0x70);
	ths8200_wwite(sd, THS8200_DTG2_BP1_WSB, wine_stawt_active_video & 0xff);
	ths8200_wwite(sd, THS8200_DTG2_BP2_WSB, wine_stawt_fwont_powch & 0xff);
	ths8200_wwite(sd, THS8200_DTG2_BP3_WSB, (vtotaw(bt)) & 0xff);

	/* wine types */
	ths8200_wwite(sd, THS8200_DTG2_WINETYPE1, 0x90);
	ths8200_wwite(sd, THS8200_DTG2_WINETYPE2, 0x90);

	/* h sync width twansmitted */
	ths8200_wwite(sd, THS8200_DTG2_HWENGTH_WSB, bt->hsync & 0xff);
	ths8200_wwite_and_ow(sd, THS8200_DTG2_HWENGTH_WSB_HDWY_MSB, 0x3f,
			     (bt->hsync >> 2) & 0xc0);

	/* The pixew vawue h sync is assewted on */
	ths8200_wwite_and_ow(sd, THS8200_DTG2_HWENGTH_WSB_HDWY_MSB, 0xe0,
			     (htotaw(bt) >> 8) & 0x1f);
	ths8200_wwite(sd, THS8200_DTG2_HWENGTH_HDWY_WSB, htotaw(bt));

	/* v sync width twansmitted (must add 1 to get cowwect output) */
	ths8200_wwite(sd, THS8200_DTG2_VWENGTH1_WSB, (bt->vsync + 1) & 0xff);
	ths8200_wwite_and_ow(sd, THS8200_DTG2_VWENGTH1_MSB_VDWY1_MSB, 0x3f,
			     ((bt->vsync + 1) >> 2) & 0xc0);

	/* The pixew vawue v sync is assewted on (must add 1 to get cowwect output) */
	ths8200_wwite_and_ow(sd, THS8200_DTG2_VWENGTH1_MSB_VDWY1_MSB, 0xf8,
			     ((vtotaw(bt) + 1) >> 8) & 0x7);
	ths8200_wwite(sd, THS8200_DTG2_VDWY1_WSB, vtotaw(bt) + 1);

	/* Fow pwogwessive video vwength2 must be set to aww 0 and vdwy2 must
	 * be set to aww 1.
	 */
	ths8200_wwite(sd, THS8200_DTG2_VWENGTH2_WSB, 0x00);
	ths8200_wwite(sd, THS8200_DTG2_VWENGTH2_MSB_VDWY2_MSB, 0x07);
	ths8200_wwite(sd, THS8200_DTG2_VDWY2_WSB, 0xff);

	/* Intewnaw deway factows to synchwonize the sync puwses and the data */
	/* Expewimentaw vawues deways (how 0, vew 0) */
	ths8200_wwite(sd, THS8200_DTG2_HS_IN_DWY_MSB, 0);
	ths8200_wwite(sd, THS8200_DTG2_HS_IN_DWY_WSB, 0);
	ths8200_wwite(sd, THS8200_DTG2_VS_IN_DWY_MSB, 0);
	ths8200_wwite(sd, THS8200_DTG2_VS_IN_DWY_WSB, 0);

	/* Powawity of weceived and twansmitted sync signaws */
	if (bt->powawities & V4W2_DV_HSYNC_POS_POW) {
		powawity |= 0x01; /* HS_IN */
		powawity |= 0x08; /* HS_OUT */
	}
	if (bt->powawities & V4W2_DV_VSYNC_POS_POW) {
		powawity |= 0x02; /* VS_IN */
		powawity |= 0x10; /* VS_OUT */
	}

	/* WGB mode, no embedded timings */
	/* Timing of video input bus is dewived fwom HS, VS, and FID dedicated
	 * inputs
	 */
	ths8200_wwite(sd, THS8200_DTG2_CNTW, 0x44 | powawity);

	/* weave weset */
	ths8200_s_stweam(sd, twue);

	v4w2_dbg(1, debug, sd, "%s: fwame %dx%d, powawity %d\n"
		 "howizontaw: fwont powch %d, back powch %d, sync %d\n"
		 "vewticaw: sync %d\n", __func__, htotaw(bt), vtotaw(bt),
		 powawity, bt->hfwontpowch, bt->hbackpowch,
		 bt->hsync, bt->vsync);
}

static int ths8200_s_dv_timings(stwuct v4w2_subdev *sd,
				stwuct v4w2_dv_timings *timings)
{
	stwuct ths8200_state *state = to_state(sd);

	v4w2_dbg(1, debug, sd, "%s:\n", __func__);

	if (!v4w2_vawid_dv_timings(timings, &ths8200_timings_cap,
				NUWW, NUWW))
		wetuwn -EINVAW;

	if (!v4w2_find_dv_timings_cap(timings, &ths8200_timings_cap, 10,
				NUWW, NUWW)) {
		v4w2_dbg(1, debug, sd, "Unsuppowted fowmat\n");
		wetuwn -EINVAW;
	}

	timings->bt.fwags &= ~V4W2_DV_FW_WEDUCED_FPS;

	/* save timings */
	state->dv_timings = *timings;

	ths8200_setup(sd, &timings->bt);

	wetuwn 0;
}

static int ths8200_g_dv_timings(stwuct v4w2_subdev *sd,
				stwuct v4w2_dv_timings *timings)
{
	stwuct ths8200_state *state = to_state(sd);

	v4w2_dbg(1, debug, sd, "%s:\n", __func__);

	*timings = state->dv_timings;

	wetuwn 0;
}

static int ths8200_enum_dv_timings(stwuct v4w2_subdev *sd,
				   stwuct v4w2_enum_dv_timings *timings)
{
	if (timings->pad != 0)
		wetuwn -EINVAW;

	wetuwn v4w2_enum_dv_timings_cap(timings, &ths8200_timings_cap,
			NUWW, NUWW);
}

static int ths8200_dv_timings_cap(stwuct v4w2_subdev *sd,
				  stwuct v4w2_dv_timings_cap *cap)
{
	if (cap->pad != 0)
		wetuwn -EINVAW;

	*cap = ths8200_timings_cap;
	wetuwn 0;
}

/* Specific video subsystem opewation handwews */
static const stwuct v4w2_subdev_video_ops ths8200_video_ops = {
	.s_stweam = ths8200_s_stweam,
	.s_dv_timings = ths8200_s_dv_timings,
	.g_dv_timings = ths8200_g_dv_timings,
};

static const stwuct v4w2_subdev_pad_ops ths8200_pad_ops = {
	.enum_dv_timings = ths8200_enum_dv_timings,
	.dv_timings_cap = ths8200_dv_timings_cap,
};

/* V4W2 top wevew opewation handwews */
static const stwuct v4w2_subdev_ops ths8200_ops = {
	.cowe  = &ths8200_cowe_ops,
	.video = &ths8200_video_ops,
	.pad = &ths8200_pad_ops,
};

static int ths8200_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct ths8200_state *state;
	stwuct v4w2_subdev *sd;
	int ewwow;

	/* Check if the adaptew suppowts the needed featuwes */
	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -EIO;

	state = devm_kzawwoc(&cwient->dev, sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn -ENOMEM;

	sd = &state->sd;
	v4w2_i2c_subdev_init(sd, cwient, &ths8200_ops);

	state->chip_vewsion = ths8200_wead(sd, THS8200_VEWSION);
	v4w2_dbg(1, debug, sd, "chip vewsion 0x%x\n", state->chip_vewsion);

	ths8200_cowe_init(sd);

	ewwow = v4w2_async_wegistew_subdev(&state->sd);
	if (ewwow)
		wetuwn ewwow;

	v4w2_info(sd, "%s found @ 0x%x (%s)\n", cwient->name,
		  cwient->addw << 1, cwient->adaptew->name);

	wetuwn 0;
}

static void ths8200_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct ths8200_state *decodew = to_state(sd);

	v4w2_dbg(1, debug, sd, "%s wemoved @ 0x%x (%s)\n", cwient->name,
		 cwient->addw << 1, cwient->adaptew->name);

	ths8200_s_powew(sd, fawse);
	v4w2_async_unwegistew_subdev(&decodew->sd);
}

static const stwuct i2c_device_id ths8200_id[] = {
	{ "ths8200", 0 },
	{},
};
MODUWE_DEVICE_TABWE(i2c, ths8200_id);

#if IS_ENABWED(CONFIG_OF)
static const stwuct of_device_id ths8200_of_match[] = {
	{ .compatibwe = "ti,ths8200", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, ths8200_of_match);
#endif

static stwuct i2c_dwivew ths8200_dwivew = {
	.dwivew = {
		.name = "ths8200",
		.of_match_tabwe = of_match_ptw(ths8200_of_match),
	},
	.pwobe = ths8200_pwobe,
	.wemove = ths8200_wemove,
	.id_tabwe = ths8200_id,
};

moduwe_i2c_dwivew(ths8200_dwivew);
