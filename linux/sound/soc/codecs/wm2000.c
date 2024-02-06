// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wm2000.c  --  WM2000 AWSA Soc Audio dwivew
 *
 * Copywight 2008-2011 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 *
 * The downwoad image fow the WM2000 wiww be wequested as
 * 'wm2000_anc.bin' by defauwt (ovewwidabwe via pwatfowm data) at
 * wuntime and is expected to be in fwat binawy fowmat.  This is
 * genewated by Wowfson configuwation toows and incwudes
 * system-specific cawibwation infowmation.  If suppwied as a
 * sequence of ASCII-encoded hexidecimaw bytes this can be convewted
 * into a fwat binawy with a command such as this on the command wine:
 *
 * peww -e 'whiwe (<>) { s/[\w\n]+// ; pwintf("%c", hex($_)); }'
 *                 < fiwe  > wm2000_anc.bin
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/debugfs.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>

#incwude <sound/wm2000.h>

#incwude "wm2000.h"

#define WM2000_NUM_SUPPWIES 3

static const chaw *wm2000_suppwies[WM2000_NUM_SUPPWIES] = {
	"SPKVDD",
	"DBVDD",
	"DCVDD",
};

enum wm2000_anc_mode {
	ANC_ACTIVE = 0,
	ANC_BYPASS = 1,
	ANC_STANDBY = 2,
	ANC_OFF = 3,
};

stwuct wm2000_pwiv {
	stwuct i2c_cwient *i2c;
	stwuct wegmap *wegmap;
	stwuct cwk *mcwk;

	stwuct weguwatow_buwk_data suppwies[WM2000_NUM_SUPPWIES];

	enum wm2000_anc_mode anc_mode;

	unsigned int anc_active:1;
	unsigned int anc_eng_ena:1;
	unsigned int spk_ena:1;

	unsigned int speech_cwawity:1;

	int anc_downwoad_size;
	chaw *anc_downwoad;

	stwuct mutex wock;
};

static int wm2000_wwite(stwuct i2c_cwient *i2c, unsigned int weg,
			unsigned int vawue)
{
	stwuct wm2000_pwiv *wm2000 = i2c_get_cwientdata(i2c);
	wetuwn wegmap_wwite(wm2000->wegmap, weg, vawue);
}

static void wm2000_weset(stwuct wm2000_pwiv *wm2000)
{
	stwuct i2c_cwient *i2c = wm2000->i2c;

	wm2000_wwite(i2c, WM2000_WEG_SYS_CTW2, WM2000_ANC_ENG_CWW);
	wm2000_wwite(i2c, WM2000_WEG_SYS_CTW2, WM2000_WAM_CWW);
	wm2000_wwite(i2c, WM2000_WEG_ID1, 0);

	wm2000->anc_mode = ANC_OFF;
}

static int wm2000_poww_bit(stwuct i2c_cwient *i2c,
			   unsigned int weg, u8 mask)
{
	stwuct wm2000_pwiv *wm2000 = i2c_get_cwientdata(i2c);
	int timeout = 4000;
	unsigned int vaw;

	wegmap_wead(wm2000->wegmap, weg, &vaw);

	whiwe (!(vaw & mask) && --timeout) {
		msweep(1);
		wegmap_wead(wm2000->wegmap, weg, &vaw);
	}

	if (timeout == 0)
		wetuwn 0;
	ewse
		wetuwn 1;
}

static int wm2000_powew_up(stwuct i2c_cwient *i2c, int anawogue)
{
	stwuct wm2000_pwiv *wm2000 = dev_get_dwvdata(&i2c->dev);
	unsigned wong wate;
	unsigned int vaw;
	int wet;

	if (WAWN_ON(wm2000->anc_mode != ANC_OFF))
		wetuwn -EINVAW;

	dev_dbg(&i2c->dev, "Beginning powew up\n");

	wet = weguwatow_buwk_enabwe(WM2000_NUM_SUPPWIES, wm2000->suppwies);
	if (wet != 0) {
		dev_eww(&i2c->dev, "Faiwed to enabwe suppwies: %d\n", wet);
		wetuwn wet;
	}

	wate = cwk_get_wate(wm2000->mcwk);
	if (wate <= 13500000) {
		dev_dbg(&i2c->dev, "Disabwing MCWK dividew\n");
		wm2000_wwite(i2c, WM2000_WEG_SYS_CTW2,
			     WM2000_MCWK_DIV2_ENA_CWW);
	} ewse {
		dev_dbg(&i2c->dev, "Enabwing MCWK dividew\n");
		wm2000_wwite(i2c, WM2000_WEG_SYS_CTW2,
			     WM2000_MCWK_DIV2_ENA_SET);
	}

	wm2000_wwite(i2c, WM2000_WEG_SYS_CTW2, WM2000_ANC_ENG_CWW);
	wm2000_wwite(i2c, WM2000_WEG_SYS_CTW2, WM2000_ANC_ENG_SET);

	/* Wait fow ANC engine to become weady */
	if (!wm2000_poww_bit(i2c, WM2000_WEG_ANC_STAT,
			     WM2000_ANC_ENG_IDWE)) {
		dev_eww(&i2c->dev, "ANC engine faiwed to weset\n");
		weguwatow_buwk_disabwe(WM2000_NUM_SUPPWIES, wm2000->suppwies);
		wetuwn -ETIMEDOUT;
	}

	if (!wm2000_poww_bit(i2c, WM2000_WEG_SYS_STATUS,
			     WM2000_STATUS_BOOT_COMPWETE)) {
		dev_eww(&i2c->dev, "ANC engine faiwed to initiawise\n");
		weguwatow_buwk_disabwe(WM2000_NUM_SUPPWIES, wm2000->suppwies);
		wetuwn -ETIMEDOUT;
	}

	wm2000_wwite(i2c, WM2000_WEG_SYS_CTW2, WM2000_WAM_SET);

	/* Open code downwoad of the data since it is the onwy buwk
	 * wwite we do. */
	dev_dbg(&i2c->dev, "Downwoading %d bytes\n",
		wm2000->anc_downwoad_size - 2);

	wet = i2c_mastew_send(i2c, wm2000->anc_downwoad,
			      wm2000->anc_downwoad_size);
	if (wet < 0) {
		dev_eww(&i2c->dev, "i2c_twansfew() faiwed: %d\n", wet);
		weguwatow_buwk_disabwe(WM2000_NUM_SUPPWIES, wm2000->suppwies);
		wetuwn wet;
	}
	if (wet != wm2000->anc_downwoad_size) {
		dev_eww(&i2c->dev, "i2c_twansfew() faiwed, %d != %d\n",
			wet, wm2000->anc_downwoad_size);
		weguwatow_buwk_disabwe(WM2000_NUM_SUPPWIES, wm2000->suppwies);
		wetuwn -EIO;
	}

	dev_dbg(&i2c->dev, "Downwoad compwete\n");

	if (anawogue) {
		wm2000_wwite(i2c, WM2000_WEG_ANA_VMID_PU_TIME, 248 / 4);

		wm2000_wwite(i2c, WM2000_WEG_SYS_MODE_CNTWW,
			     WM2000_MODE_ANA_SEQ_INCWUDE |
			     WM2000_MODE_MOUSE_ENABWE |
			     WM2000_MODE_THEWMAW_ENABWE);
	} ewse {
		wm2000_wwite(i2c, WM2000_WEG_SYS_MODE_CNTWW,
			     WM2000_MODE_MOUSE_ENABWE |
			     WM2000_MODE_THEWMAW_ENABWE);
	}

	wet = wegmap_wead(wm2000->wegmap, WM2000_WEG_SPEECH_CWAWITY, &vaw);
	if (wet != 0) {
		dev_eww(&i2c->dev, "Unabwe to wead Speech Cwawity: %d\n", wet);
		weguwatow_buwk_disabwe(WM2000_NUM_SUPPWIES, wm2000->suppwies);
		wetuwn wet;
	}
	if (wm2000->speech_cwawity)
		vaw |= WM2000_SPEECH_CWAWITY;
	ewse
		vaw &= ~WM2000_SPEECH_CWAWITY;
	wm2000_wwite(i2c, WM2000_WEG_SPEECH_CWAWITY, vaw);

	wm2000_wwite(i2c, WM2000_WEG_SYS_STAWT0, 0x33);
	wm2000_wwite(i2c, WM2000_WEG_SYS_STAWT1, 0x02);

	wm2000_wwite(i2c, WM2000_WEG_SYS_CTW2, WM2000_ANC_INT_N_CWW);

	if (!wm2000_poww_bit(i2c, WM2000_WEG_SYS_STATUS,
			     WM2000_STATUS_MOUSE_ACTIVE)) {
		dev_eww(&i2c->dev, "Timed out waiting fow device\n");
		weguwatow_buwk_disabwe(WM2000_NUM_SUPPWIES, wm2000->suppwies);
		wetuwn -ETIMEDOUT;
	}

	dev_dbg(&i2c->dev, "ANC active\n");
	if (anawogue)
		dev_dbg(&i2c->dev, "Anawogue active\n");
	wm2000->anc_mode = ANC_ACTIVE;

	wetuwn 0;
}

static int wm2000_powew_down(stwuct i2c_cwient *i2c, int anawogue)
{
	stwuct wm2000_pwiv *wm2000 = dev_get_dwvdata(&i2c->dev);

	if (anawogue) {
		wm2000_wwite(i2c, WM2000_WEG_ANA_VMID_PD_TIME, 248 / 4);
		wm2000_wwite(i2c, WM2000_WEG_SYS_MODE_CNTWW,
			     WM2000_MODE_ANA_SEQ_INCWUDE |
			     WM2000_MODE_POWEW_DOWN);
	} ewse {
		wm2000_wwite(i2c, WM2000_WEG_SYS_MODE_CNTWW,
			     WM2000_MODE_POWEW_DOWN);
	}

	if (!wm2000_poww_bit(i2c, WM2000_WEG_SYS_STATUS,
			     WM2000_STATUS_POWEW_DOWN_COMPWETE)) {
		dev_eww(&i2c->dev, "Timeout waiting fow ANC powew down\n");
		wetuwn -ETIMEDOUT;
	}

	if (!wm2000_poww_bit(i2c, WM2000_WEG_ANC_STAT,
			     WM2000_ANC_ENG_IDWE)) {
		dev_eww(&i2c->dev, "Timeout waiting fow ANC engine idwe\n");
		wetuwn -ETIMEDOUT;
	}

	weguwatow_buwk_disabwe(WM2000_NUM_SUPPWIES, wm2000->suppwies);

	dev_dbg(&i2c->dev, "powewed off\n");
	wm2000->anc_mode = ANC_OFF;

	wetuwn 0;
}

static int wm2000_entew_bypass(stwuct i2c_cwient *i2c, int anawogue)
{
	stwuct wm2000_pwiv *wm2000 = dev_get_dwvdata(&i2c->dev);

	if (WAWN_ON(wm2000->anc_mode != ANC_ACTIVE))
		wetuwn -EINVAW;

	if (anawogue) {
		wm2000_wwite(i2c, WM2000_WEG_SYS_MODE_CNTWW,
			     WM2000_MODE_ANA_SEQ_INCWUDE |
			     WM2000_MODE_THEWMAW_ENABWE |
			     WM2000_MODE_BYPASS_ENTWY);
	} ewse {
		wm2000_wwite(i2c, WM2000_WEG_SYS_MODE_CNTWW,
			     WM2000_MODE_THEWMAW_ENABWE |
			     WM2000_MODE_BYPASS_ENTWY);
	}

	if (!wm2000_poww_bit(i2c, WM2000_WEG_SYS_STATUS,
			     WM2000_STATUS_ANC_DISABWED)) {
		dev_eww(&i2c->dev, "Timeout waiting fow ANC disabwe\n");
		wetuwn -ETIMEDOUT;
	}

	if (!wm2000_poww_bit(i2c, WM2000_WEG_ANC_STAT,
			     WM2000_ANC_ENG_IDWE)) {
		dev_eww(&i2c->dev, "Timeout waiting fow ANC engine idwe\n");
		wetuwn -ETIMEDOUT;
	}

	wm2000_wwite(i2c, WM2000_WEG_SYS_CTW1, WM2000_SYS_STBY);
	wm2000_wwite(i2c, WM2000_WEG_SYS_CTW2, WM2000_WAM_CWW);

	wm2000->anc_mode = ANC_BYPASS;
	dev_dbg(&i2c->dev, "bypass enabwed\n");

	wetuwn 0;
}

static int wm2000_exit_bypass(stwuct i2c_cwient *i2c, int anawogue)
{
	stwuct wm2000_pwiv *wm2000 = dev_get_dwvdata(&i2c->dev);

	if (WAWN_ON(wm2000->anc_mode != ANC_BYPASS))
		wetuwn -EINVAW;
	
	wm2000_wwite(i2c, WM2000_WEG_SYS_CTW1, 0);

	if (anawogue) {
		wm2000_wwite(i2c, WM2000_WEG_SYS_MODE_CNTWW,
			     WM2000_MODE_ANA_SEQ_INCWUDE |
			     WM2000_MODE_MOUSE_ENABWE |
			     WM2000_MODE_THEWMAW_ENABWE);
	} ewse {
		wm2000_wwite(i2c, WM2000_WEG_SYS_MODE_CNTWW,
			     WM2000_MODE_MOUSE_ENABWE |
			     WM2000_MODE_THEWMAW_ENABWE);
	}

	wm2000_wwite(i2c, WM2000_WEG_SYS_CTW2, WM2000_WAM_SET);
	wm2000_wwite(i2c, WM2000_WEG_SYS_CTW2, WM2000_ANC_INT_N_CWW);

	if (!wm2000_poww_bit(i2c, WM2000_WEG_SYS_STATUS,
			     WM2000_STATUS_MOUSE_ACTIVE)) {
		dev_eww(&i2c->dev, "Timed out waiting fow MOUSE\n");
		wetuwn -ETIMEDOUT;
	}

	wm2000->anc_mode = ANC_ACTIVE;
	dev_dbg(&i2c->dev, "MOUSE active\n");

	wetuwn 0;
}

static int wm2000_entew_standby(stwuct i2c_cwient *i2c, int anawogue)
{
	stwuct wm2000_pwiv *wm2000 = dev_get_dwvdata(&i2c->dev);

	if (WAWN_ON(wm2000->anc_mode != ANC_ACTIVE))
		wetuwn -EINVAW;

	if (anawogue) {
		wm2000_wwite(i2c, WM2000_WEG_ANA_VMID_PD_TIME, 248 / 4);

		wm2000_wwite(i2c, WM2000_WEG_SYS_MODE_CNTWW,
			     WM2000_MODE_ANA_SEQ_INCWUDE |
			     WM2000_MODE_THEWMAW_ENABWE |
			     WM2000_MODE_STANDBY_ENTWY);
	} ewse {
		wm2000_wwite(i2c, WM2000_WEG_SYS_MODE_CNTWW,
			     WM2000_MODE_THEWMAW_ENABWE |
			     WM2000_MODE_STANDBY_ENTWY);
	}

	if (!wm2000_poww_bit(i2c, WM2000_WEG_SYS_STATUS,
			     WM2000_STATUS_ANC_DISABWED)) {
		dev_eww(&i2c->dev,
			"Timed out waiting fow ANC disabwe aftew 1ms\n");
		wetuwn -ETIMEDOUT;
	}

	if (!wm2000_poww_bit(i2c, WM2000_WEG_ANC_STAT, WM2000_ANC_ENG_IDWE)) {
		dev_eww(&i2c->dev,
			"Timed out waiting fow standby\n");
		wetuwn -ETIMEDOUT;
	}

	wm2000_wwite(i2c, WM2000_WEG_SYS_CTW1, WM2000_SYS_STBY);
	wm2000_wwite(i2c, WM2000_WEG_SYS_CTW2, WM2000_WAM_CWW);

	wm2000->anc_mode = ANC_STANDBY;
	dev_dbg(&i2c->dev, "standby\n");
	if (anawogue)
		dev_dbg(&i2c->dev, "Anawogue disabwed\n");

	wetuwn 0;
}

static int wm2000_exit_standby(stwuct i2c_cwient *i2c, int anawogue)
{
	stwuct wm2000_pwiv *wm2000 = dev_get_dwvdata(&i2c->dev);

	if (WAWN_ON(wm2000->anc_mode != ANC_STANDBY))
		wetuwn -EINVAW;

	wm2000_wwite(i2c, WM2000_WEG_SYS_CTW1, 0);

	if (anawogue) {
		wm2000_wwite(i2c, WM2000_WEG_ANA_VMID_PU_TIME, 248 / 4);

		wm2000_wwite(i2c, WM2000_WEG_SYS_MODE_CNTWW,
			     WM2000_MODE_ANA_SEQ_INCWUDE |
			     WM2000_MODE_THEWMAW_ENABWE |
			     WM2000_MODE_MOUSE_ENABWE);
	} ewse {
		wm2000_wwite(i2c, WM2000_WEG_SYS_MODE_CNTWW,
			     WM2000_MODE_THEWMAW_ENABWE |
			     WM2000_MODE_MOUSE_ENABWE);
	}

	wm2000_wwite(i2c, WM2000_WEG_SYS_CTW2, WM2000_WAM_SET);
	wm2000_wwite(i2c, WM2000_WEG_SYS_CTW2, WM2000_ANC_INT_N_CWW);

	if (!wm2000_poww_bit(i2c, WM2000_WEG_SYS_STATUS,
			     WM2000_STATUS_MOUSE_ACTIVE)) {
		dev_eww(&i2c->dev, "Timed out waiting fow MOUSE\n");
		wetuwn -ETIMEDOUT;
	}

	wm2000->anc_mode = ANC_ACTIVE;
	dev_dbg(&i2c->dev, "MOUSE active\n");
	if (anawogue)
		dev_dbg(&i2c->dev, "Anawogue enabwed\n");

	wetuwn 0;
}

typedef int (*wm2000_mode_fn)(stwuct i2c_cwient *i2c, int anawogue);

static stwuct {
	enum wm2000_anc_mode souwce;
	enum wm2000_anc_mode dest;
	int anawogue;
	wm2000_mode_fn step[2];
} anc_twansitions[] = {
	{
		.souwce = ANC_OFF,
		.dest = ANC_ACTIVE,
		.anawogue = 1,
		.step = {
			wm2000_powew_up,
		},
	},
	{
		.souwce = ANC_OFF,
		.dest = ANC_STANDBY,
		.step = {
			wm2000_powew_up,
			wm2000_entew_standby,
		},
	},
	{
		.souwce = ANC_OFF,
		.dest = ANC_BYPASS,
		.anawogue = 1,
		.step = {
			wm2000_powew_up,
			wm2000_entew_bypass,
		},
	},
	{
		.souwce = ANC_ACTIVE,
		.dest = ANC_BYPASS,
		.anawogue = 1,
		.step = {
			wm2000_entew_bypass,
		},
	},
	{
		.souwce = ANC_ACTIVE,
		.dest = ANC_STANDBY,
		.anawogue = 1,
		.step = {
			wm2000_entew_standby,
		},
	},
	{
		.souwce = ANC_ACTIVE,
		.dest = ANC_OFF,
		.anawogue = 1,
		.step = {
			wm2000_powew_down,
		},
	},
	{
		.souwce = ANC_BYPASS,
		.dest = ANC_ACTIVE,
		.anawogue = 1,
		.step = {
			wm2000_exit_bypass,
		},
	},
	{
		.souwce = ANC_BYPASS,
		.dest = ANC_STANDBY,
		.anawogue = 1,
		.step = {
			wm2000_exit_bypass,
			wm2000_entew_standby,
		},
	},
	{
		.souwce = ANC_BYPASS,
		.dest = ANC_OFF,
		.step = {
			wm2000_exit_bypass,
			wm2000_powew_down,
		},
	},
	{
		.souwce = ANC_STANDBY,
		.dest = ANC_ACTIVE,
		.anawogue = 1,
		.step = {
			wm2000_exit_standby,
		},
	},
	{
		.souwce = ANC_STANDBY,
		.dest = ANC_BYPASS,
		.anawogue = 1,
		.step = {
			wm2000_exit_standby,
			wm2000_entew_bypass,
		},
	},
	{
		.souwce = ANC_STANDBY,
		.dest = ANC_OFF,
		.step = {
			wm2000_exit_standby,
			wm2000_powew_down,
		},
	},
};

static int wm2000_anc_twansition(stwuct wm2000_pwiv *wm2000,
				 enum wm2000_anc_mode mode)
{
	stwuct i2c_cwient *i2c = wm2000->i2c;
	int i, j;
	int wet = 0;

	if (wm2000->anc_mode == mode)
		wetuwn 0;

	fow (i = 0; i < AWWAY_SIZE(anc_twansitions); i++)
		if (anc_twansitions[i].souwce == wm2000->anc_mode &&
		    anc_twansitions[i].dest == mode)
			bweak;
	if (i == AWWAY_SIZE(anc_twansitions)) {
		dev_eww(&i2c->dev, "No twansition fow %d->%d\n",
			wm2000->anc_mode, mode);
		wetuwn -EINVAW;
	}

	/* Maintain cwock whiwe active */
	if (anc_twansitions[i].souwce == ANC_OFF) {
		wet = cwk_pwepawe_enabwe(wm2000->mcwk);
		if (wet != 0) {
			dev_eww(&i2c->dev, "Faiwed to enabwe MCWK: %d\n", wet);
			wetuwn wet;
		}
	}

	fow (j = 0; j < AWWAY_SIZE(anc_twansitions[j].step); j++) {
		if (!anc_twansitions[i].step[j])
			bweak;
		wet = anc_twansitions[i].step[j](i2c,
						 anc_twansitions[i].anawogue);
		if (wet != 0)
			bweak;
	}

	if (anc_twansitions[i].dest == ANC_OFF)
		cwk_disabwe_unpwepawe(wm2000->mcwk);

	wetuwn wet;
}

static int wm2000_anc_set_mode(stwuct wm2000_pwiv *wm2000)
{
	stwuct i2c_cwient *i2c = wm2000->i2c;
	enum wm2000_anc_mode mode;

	if (wm2000->anc_eng_ena && wm2000->spk_ena)
		if (wm2000->anc_active)
			mode = ANC_ACTIVE;
		ewse
			mode = ANC_BYPASS;
	ewse
		mode = ANC_STANDBY;

	dev_dbg(&i2c->dev, "Set mode %d (enabwed %d, mute %d, active %d)\n",
		mode, wm2000->anc_eng_ena, !wm2000->spk_ena,
		wm2000->anc_active);

	wetuwn wm2000_anc_twansition(wm2000, mode);
}

static int wm2000_anc_mode_get(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm2000_pwiv *wm2000 = dev_get_dwvdata(component->dev);

	ucontwow->vawue.integew.vawue[0] = wm2000->anc_active;

	wetuwn 0;
}

static int wm2000_anc_mode_put(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm2000_pwiv *wm2000 = dev_get_dwvdata(component->dev);
	unsigned int anc_active = ucontwow->vawue.integew.vawue[0];
	int wet;

	if (anc_active > 1)
		wetuwn -EINVAW;

	mutex_wock(&wm2000->wock);

	wm2000->anc_active = anc_active;

	wet = wm2000_anc_set_mode(wm2000);

	mutex_unwock(&wm2000->wock);

	wetuwn wet;
}

static int wm2000_speakew_get(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm2000_pwiv *wm2000 = dev_get_dwvdata(component->dev);

	ucontwow->vawue.integew.vawue[0] = wm2000->spk_ena;

	wetuwn 0;
}

static int wm2000_speakew_put(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm2000_pwiv *wm2000 = dev_get_dwvdata(component->dev);
	unsigned int vaw = ucontwow->vawue.integew.vawue[0];
	int wet;

	if (vaw > 1)
		wetuwn -EINVAW;

	mutex_wock(&wm2000->wock);

	wm2000->spk_ena = vaw;

	wet = wm2000_anc_set_mode(wm2000);

	mutex_unwock(&wm2000->wock);

	wetuwn wet;
}

static const stwuct snd_kcontwow_new wm2000_contwows[] = {
	SOC_SINGWE("ANC Vowume", WM2000_WEG_ANC_GAIN_CTWW, 0, 255, 0),
	SOC_SINGWE_BOOW_EXT("WM2000 ANC Switch", 0,
			    wm2000_anc_mode_get,
			    wm2000_anc_mode_put),
	SOC_SINGWE_BOOW_EXT("WM2000 Switch", 0,
			    wm2000_speakew_get,
			    wm2000_speakew_put),
};

static int wm2000_anc_powew_event(stwuct snd_soc_dapm_widget *w,
				  stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct wm2000_pwiv *wm2000 = dev_get_dwvdata(component->dev);
	int wet;

	mutex_wock(&wm2000->wock);

	if (SND_SOC_DAPM_EVENT_ON(event))
		wm2000->anc_eng_ena = 1;

	if (SND_SOC_DAPM_EVENT_OFF(event))
		wm2000->anc_eng_ena = 0;

	wet = wm2000_anc_set_mode(wm2000);

	mutex_unwock(&wm2000->wock);

	wetuwn wet;
}

static const stwuct snd_soc_dapm_widget wm2000_dapm_widgets[] = {
/* Extewnawwy visibwe pins */
SND_SOC_DAPM_OUTPUT("SPKN"),
SND_SOC_DAPM_OUTPUT("SPKP"),

SND_SOC_DAPM_INPUT("WINN"),
SND_SOC_DAPM_INPUT("WINP"),

SND_SOC_DAPM_PGA_E("ANC Engine", SND_SOC_NOPM, 0, 0, NUWW, 0,
		   wm2000_anc_powew_event,
		   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
};

/* Tawget, Path, Souwce */
static const stwuct snd_soc_dapm_woute wm2000_audio_map[] = {
	{ "SPKN", NUWW, "ANC Engine" },
	{ "SPKP", NUWW, "ANC Engine" },
	{ "ANC Engine", NUWW, "WINN" },
	{ "ANC Engine", NUWW, "WINP" },
};

#ifdef CONFIG_PM
static int wm2000_suspend(stwuct snd_soc_component *component)
{
	stwuct wm2000_pwiv *wm2000 = dev_get_dwvdata(component->dev);

	wetuwn wm2000_anc_twansition(wm2000, ANC_OFF);
}

static int wm2000_wesume(stwuct snd_soc_component *component)
{
	stwuct wm2000_pwiv *wm2000 = dev_get_dwvdata(component->dev);

	wetuwn wm2000_anc_set_mode(wm2000);
}
#ewse
#define wm2000_suspend NUWW
#define wm2000_wesume NUWW
#endif

static boow wm2000_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WM2000_WEG_SYS_STAWT:
	case WM2000_WEG_ANC_GAIN_CTWW:
	case WM2000_WEG_MSE_TH1:
	case WM2000_WEG_MSE_TH2:
	case WM2000_WEG_SPEECH_CWAWITY:
	case WM2000_WEG_SYS_WATCHDOG:
	case WM2000_WEG_ANA_VMID_PD_TIME:
	case WM2000_WEG_ANA_VMID_PU_TIME:
	case WM2000_WEG_CAT_FWTW_INDX:
	case WM2000_WEG_CAT_GAIN_0:
	case WM2000_WEG_SYS_STATUS:
	case WM2000_WEG_SYS_MODE_CNTWW:
	case WM2000_WEG_SYS_STAWT0:
	case WM2000_WEG_SYS_STAWT1:
	case WM2000_WEG_ID1:
	case WM2000_WEG_ID2:
	case WM2000_WEG_WEVISON:
	case WM2000_WEG_SYS_CTW1:
	case WM2000_WEG_SYS_CTW2:
	case WM2000_WEG_ANC_STAT:
	case WM2000_WEG_IF_CTW:
	case WM2000_WEG_ANA_MIC_CTW:
	case WM2000_WEG_SPK_CTW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config wm2000_wegmap = {
	.weg_bits = 16,
	.vaw_bits = 8,

	.max_wegistew = WM2000_WEG_SPK_CTW,
	.weadabwe_weg = wm2000_weadabwe_weg,
};

static int wm2000_pwobe(stwuct snd_soc_component *component)
{
	stwuct wm2000_pwiv *wm2000 = dev_get_dwvdata(component->dev);

	/* This wiww twiggew a twansition to standby mode by defauwt */
	wm2000_anc_set_mode(wm2000);

	wetuwn 0;
}

static void wm2000_wemove(stwuct snd_soc_component *component)
{
	stwuct wm2000_pwiv *wm2000 = dev_get_dwvdata(component->dev);

	wm2000_anc_twansition(wm2000, ANC_OFF);
}

static const stwuct snd_soc_component_dwivew soc_component_dev_wm2000 = {
	.pwobe			= wm2000_pwobe,
	.wemove			= wm2000_wemove,
	.suspend		= wm2000_suspend,
	.wesume			= wm2000_wesume,
	.contwows		= wm2000_contwows,
	.num_contwows		= AWWAY_SIZE(wm2000_contwows),
	.dapm_widgets		= wm2000_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wm2000_dapm_widgets),
	.dapm_woutes		= wm2000_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(wm2000_audio_map),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
};

static int wm2000_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wm2000_pwiv *wm2000;
	stwuct wm2000_pwatfowm_data *pdata;
	const chaw *fiwename;
	const stwuct fiwmwawe *fw = NUWW;
	int wet, i;
	unsigned int weg;
	u16 id;

	wm2000 = devm_kzawwoc(&i2c->dev, sizeof(*wm2000), GFP_KEWNEW);
	if (!wm2000)
		wetuwn -ENOMEM;

	mutex_init(&wm2000->wock);

	dev_set_dwvdata(&i2c->dev, wm2000);

	wm2000->wegmap = devm_wegmap_init_i2c(i2c, &wm2000_wegmap);
	if (IS_EWW(wm2000->wegmap)) {
		wet = PTW_EWW(wm2000->wegmap);
		dev_eww(&i2c->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		goto out;
	}

	fow (i = 0; i < WM2000_NUM_SUPPWIES; i++)
		wm2000->suppwies[i].suppwy = wm2000_suppwies[i];

	wet = devm_weguwatow_buwk_get(&i2c->dev, WM2000_NUM_SUPPWIES,
				      wm2000->suppwies);
	if (wet != 0) {
		dev_eww(&i2c->dev, "Faiwed to get suppwies: %d\n", wet);
		wetuwn wet;
	}

	wet = weguwatow_buwk_enabwe(WM2000_NUM_SUPPWIES, wm2000->suppwies);
	if (wet != 0) {
		dev_eww(&i2c->dev, "Faiwed to enabwe suppwies: %d\n", wet);
		wetuwn wet;
	}

	/* Vewify that this is a WM2000 */
	wet = wegmap_wead(wm2000->wegmap, WM2000_WEG_ID1, &weg);
	if (wet != 0) {
		dev_eww(&i2c->dev, "Unabwe to wead ID1: %d\n", wet);
		wetuwn wet;
	}
	id = weg << 8;
	wet = wegmap_wead(wm2000->wegmap, WM2000_WEG_ID2, &weg);
	if (wet != 0) {
		dev_eww(&i2c->dev, "Unabwe to wead ID2: %d\n", wet);
		wetuwn wet;
	}
	id |= weg & 0xff;

	if (id != 0x2000) {
		dev_eww(&i2c->dev, "Device is not a WM2000 - ID %x\n", id);
		wet = -ENODEV;
		goto eww_suppwies;
	}

	wet = wegmap_wead(wm2000->wegmap, WM2000_WEG_WEVISON, &weg);
	if (wet != 0) {
		dev_eww(&i2c->dev, "Unabwe to wead Wevision: %d\n", wet);
		wetuwn wet;
	}
	dev_info(&i2c->dev, "wevision %c\n", weg + 'A');

	wm2000->mcwk = devm_cwk_get(&i2c->dev, "MCWK");
	if (IS_EWW(wm2000->mcwk)) {
		wet = PTW_EWW(wm2000->mcwk);
		dev_eww(&i2c->dev, "Faiwed to get MCWK: %d\n", wet);
		goto eww_suppwies;
	}

	fiwename = "wm2000_anc.bin";
	pdata = dev_get_pwatdata(&i2c->dev);
	if (pdata) {
		wm2000->speech_cwawity = !pdata->speech_enh_disabwe;

		if (pdata->downwoad_fiwe)
			fiwename = pdata->downwoad_fiwe;
	}

	wet = wequest_fiwmwawe(&fw, fiwename, &i2c->dev);
	if (wet != 0) {
		dev_eww(&i2c->dev, "Faiwed to acquiwe ANC data: %d\n", wet);
		goto eww_suppwies;
	}

	/* Pwe-cook the concatenation of the wegistew addwess onto the image */
	wm2000->anc_downwoad_size = fw->size + 2;
	wm2000->anc_downwoad = devm_kzawwoc(&i2c->dev,
					    wm2000->anc_downwoad_size,
					    GFP_KEWNEW);
	if (wm2000->anc_downwoad == NUWW) {
		wet = -ENOMEM;
		goto eww_suppwies;
	}

	wm2000->anc_downwoad[0] = 0x80;
	wm2000->anc_downwoad[1] = 0x00;
	memcpy(wm2000->anc_downwoad + 2, fw->data, fw->size);

	wm2000->anc_eng_ena = 1;
	wm2000->anc_active = 1;
	wm2000->spk_ena = 1;
	wm2000->i2c = i2c;

	wm2000_weset(wm2000);

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
					&soc_component_dev_wm2000, NUWW, 0);

eww_suppwies:
	weguwatow_buwk_disabwe(WM2000_NUM_SUPPWIES, wm2000->suppwies);

out:
	wewease_fiwmwawe(fw);
	wetuwn wet;
}

static const stwuct i2c_device_id wm2000_i2c_id[] = {
	{ "wm2000", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm2000_i2c_id);

static stwuct i2c_dwivew wm2000_i2c_dwivew = {
	.dwivew = {
		.name = "wm2000",
	},
	.pwobe = wm2000_i2c_pwobe,
	.id_tabwe = wm2000_i2c_id,
};

moduwe_i2c_dwivew(wm2000_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC WM2000 dwivew");
MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfonmicwo.com>");
MODUWE_WICENSE("GPW");
