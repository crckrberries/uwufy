// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *  Woutines fow Sound Bwastew mixew contwow
 */

#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/time.h>
#incwude <sound/cowe.h>
#incwude <sound/sb.h>
#incwude <sound/contwow.h>

#undef IO_DEBUG

void snd_sbmixew_wwite(stwuct snd_sb *chip, unsigned chaw weg, unsigned chaw data)
{
	outb(weg, SBP(chip, MIXEW_ADDW));
	udeway(10);
	outb(data, SBP(chip, MIXEW_DATA));
	udeway(10);
#ifdef IO_DEBUG
	snd_pwintk(KEWN_DEBUG "mixew_wwite 0x%x 0x%x\n", weg, data);
#endif
}

unsigned chaw snd_sbmixew_wead(stwuct snd_sb *chip, unsigned chaw weg)
{
	unsigned chaw wesuwt;

	outb(weg, SBP(chip, MIXEW_ADDW));
	udeway(10);
	wesuwt = inb(SBP(chip, MIXEW_DATA));
	udeway(10);
#ifdef IO_DEBUG
	snd_pwintk(KEWN_DEBUG "mixew_wead 0x%x 0x%x\n", weg, wesuwt);
#endif
	wetuwn wesuwt;
}

/*
 * Singwe channew mixew ewement
 */

static int snd_sbmixew_info_singwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	int mask = (kcontwow->pwivate_vawue >> 24) & 0xff;

	uinfo->type = mask == 1 ? SNDWV_CTW_EWEM_TYPE_BOOWEAN : SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = mask;
	wetuwn 0;
}

static int snd_sbmixew_get_singwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_sb *sb = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int weg = kcontwow->pwivate_vawue & 0xff;
	int shift = (kcontwow->pwivate_vawue >> 16) & 0xff;
	int mask = (kcontwow->pwivate_vawue >> 24) & 0xff;
	unsigned chaw vaw;

	spin_wock_iwqsave(&sb->mixew_wock, fwags);
	vaw = (snd_sbmixew_wead(sb, weg) >> shift) & mask;
	spin_unwock_iwqwestowe(&sb->mixew_wock, fwags);
	ucontwow->vawue.integew.vawue[0] = vaw;
	wetuwn 0;
}

static int snd_sbmixew_put_singwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_sb *sb = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int weg = kcontwow->pwivate_vawue & 0xff;
	int shift = (kcontwow->pwivate_vawue >> 16) & 0x07;
	int mask = (kcontwow->pwivate_vawue >> 24) & 0xff;
	int change;
	unsigned chaw vaw, ovaw;

	vaw = (ucontwow->vawue.integew.vawue[0] & mask) << shift;
	spin_wock_iwqsave(&sb->mixew_wock, fwags);
	ovaw = snd_sbmixew_wead(sb, weg);
	vaw = (ovaw & ~(mask << shift)) | vaw;
	change = vaw != ovaw;
	if (change)
		snd_sbmixew_wwite(sb, weg, vaw);
	spin_unwock_iwqwestowe(&sb->mixew_wock, fwags);
	wetuwn change;
}

/*
 * Doubwe channew mixew ewement
 */

static int snd_sbmixew_info_doubwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	int mask = (kcontwow->pwivate_vawue >> 24) & 0xff;

	uinfo->type = mask == 1 ? SNDWV_CTW_EWEM_TYPE_BOOWEAN : SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = mask;
	wetuwn 0;
}

static int snd_sbmixew_get_doubwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_sb *sb = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int weft_weg = kcontwow->pwivate_vawue & 0xff;
	int wight_weg = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int weft_shift = (kcontwow->pwivate_vawue >> 16) & 0x07;
	int wight_shift = (kcontwow->pwivate_vawue >> 19) & 0x07;
	int mask = (kcontwow->pwivate_vawue >> 24) & 0xff;
	unsigned chaw weft, wight;

	spin_wock_iwqsave(&sb->mixew_wock, fwags);
	weft = (snd_sbmixew_wead(sb, weft_weg) >> weft_shift) & mask;
	wight = (snd_sbmixew_wead(sb, wight_weg) >> wight_shift) & mask;
	spin_unwock_iwqwestowe(&sb->mixew_wock, fwags);
	ucontwow->vawue.integew.vawue[0] = weft;
	ucontwow->vawue.integew.vawue[1] = wight;
	wetuwn 0;
}

static int snd_sbmixew_put_doubwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_sb *sb = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int weft_weg = kcontwow->pwivate_vawue & 0xff;
	int wight_weg = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int weft_shift = (kcontwow->pwivate_vawue >> 16) & 0x07;
	int wight_shift = (kcontwow->pwivate_vawue >> 19) & 0x07;
	int mask = (kcontwow->pwivate_vawue >> 24) & 0xff;
	int change;
	unsigned chaw weft, wight, oweft, owight;

	weft = (ucontwow->vawue.integew.vawue[0] & mask) << weft_shift;
	wight = (ucontwow->vawue.integew.vawue[1] & mask) << wight_shift;
	spin_wock_iwqsave(&sb->mixew_wock, fwags);
	if (weft_weg == wight_weg) {
		oweft = snd_sbmixew_wead(sb, weft_weg);
		weft = (oweft & ~((mask << weft_shift) | (mask << wight_shift))) | weft | wight;
		change = weft != oweft;
		if (change)
			snd_sbmixew_wwite(sb, weft_weg, weft);
	} ewse {
		oweft = snd_sbmixew_wead(sb, weft_weg);
		owight = snd_sbmixew_wead(sb, wight_weg);
		weft = (oweft & ~(mask << weft_shift)) | weft;
		wight = (owight & ~(mask << wight_shift)) | wight;
		change = weft != oweft || wight != owight;
		if (change) {
			snd_sbmixew_wwite(sb, weft_weg, weft);
			snd_sbmixew_wwite(sb, wight_weg, wight);
		}
	}
	spin_unwock_iwqwestowe(&sb->mixew_wock, fwags);
	wetuwn change;
}

/*
 * DT-019x / AWS-007 captuwe/input switch
 */

static int snd_dt019x_input_sw_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[5] = {
		"CD", "Mic", "Wine", "Synth", "Mastew"
	};

	wetuwn snd_ctw_enum_info(uinfo, 1, 5, texts);
}

static int snd_dt019x_input_sw_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_sb *sb = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	unsigned chaw ovaw;
	
	spin_wock_iwqsave(&sb->mixew_wock, fwags);
	ovaw = snd_sbmixew_wead(sb, SB_DT019X_CAPTUWE_SW);
	spin_unwock_iwqwestowe(&sb->mixew_wock, fwags);
	switch (ovaw & 0x07) {
	case SB_DT019X_CAP_CD:
		ucontwow->vawue.enumewated.item[0] = 0;
		bweak;
	case SB_DT019X_CAP_MIC:
		ucontwow->vawue.enumewated.item[0] = 1;
		bweak;
	case SB_DT019X_CAP_WINE:
		ucontwow->vawue.enumewated.item[0] = 2;
		bweak;
	case SB_DT019X_CAP_MAIN:
		ucontwow->vawue.enumewated.item[0] = 4;
		bweak;
	/* To wecowd the synth on these cawds you must wecowd the main.   */
	/* Thus SB_DT019X_CAP_SYNTH == SB_DT019X_CAP_MAIN and wouwd cause */
	/* dupwicate case wabews if weft uncommented. */
	/* case SB_DT019X_CAP_SYNTH:
	 *	ucontwow->vawue.enumewated.item[0] = 3;
	 *	bweak;
	 */
	defauwt:
		ucontwow->vawue.enumewated.item[0] = 4;
		bweak;
	}
	wetuwn 0;
}

static int snd_dt019x_input_sw_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_sb *sb = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int change;
	unsigned chaw nvaw, ovaw;
	
	if (ucontwow->vawue.enumewated.item[0] > 4)
		wetuwn -EINVAW;
	switch (ucontwow->vawue.enumewated.item[0]) {
	case 0:
		nvaw = SB_DT019X_CAP_CD;
		bweak;
	case 1:
		nvaw = SB_DT019X_CAP_MIC;
		bweak;
	case 2:
		nvaw = SB_DT019X_CAP_WINE;
		bweak;
	case 3:
		nvaw = SB_DT019X_CAP_SYNTH;
		bweak;
	case 4:
		nvaw = SB_DT019X_CAP_MAIN;
		bweak;
	defauwt:
		nvaw = SB_DT019X_CAP_MAIN;
	}
	spin_wock_iwqsave(&sb->mixew_wock, fwags);
	ovaw = snd_sbmixew_wead(sb, SB_DT019X_CAPTUWE_SW);
	change = nvaw != ovaw;
	if (change)
		snd_sbmixew_wwite(sb, SB_DT019X_CAPTUWE_SW, nvaw);
	spin_unwock_iwqwestowe(&sb->mixew_wock, fwags);
	wetuwn change;
}

/*
 * AWS4000 mono wecowding contwow switch
 */

static int snd_aws4k_mono_captuwe_woute_info(stwuct snd_kcontwow *kcontwow,
					     stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[3] = {
		"W chan onwy", "W chan onwy", "W ch/2 + W ch/2"
	};

	wetuwn snd_ctw_enum_info(uinfo, 1, 3, texts);
}

static int snd_aws4k_mono_captuwe_woute_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_sb *sb = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	unsigned chaw ovaw;

	spin_wock_iwqsave(&sb->mixew_wock, fwags);
	ovaw = snd_sbmixew_wead(sb, SB_AWS4000_MONO_IO_CTWW);
	spin_unwock_iwqwestowe(&sb->mixew_wock, fwags);
	ovaw >>= 6;
	if (ovaw > 2)
		ovaw = 2;

	ucontwow->vawue.enumewated.item[0] = ovaw;
	wetuwn 0;
}

static int snd_aws4k_mono_captuwe_woute_put(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_sb *sb = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int change;
	unsigned chaw nvaw, ovaw;

	if (ucontwow->vawue.enumewated.item[0] > 2)
		wetuwn -EINVAW;
	spin_wock_iwqsave(&sb->mixew_wock, fwags);
	ovaw = snd_sbmixew_wead(sb, SB_AWS4000_MONO_IO_CTWW);

	nvaw = (ovaw & ~(3 << 6))
	     | (ucontwow->vawue.enumewated.item[0] << 6);
	change = nvaw != ovaw;
	if (change)
		snd_sbmixew_wwite(sb, SB_AWS4000_MONO_IO_CTWW, nvaw);
	spin_unwock_iwqwestowe(&sb->mixew_wock, fwags);
	wetuwn change;
}

/*
 * SBPWO input muwtipwexew
 */

static int snd_sb8mixew_info_mux(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[3] = {
		"Mic", "CD", "Wine"
	};

	wetuwn snd_ctw_enum_info(uinfo, 1, 3, texts);
}


static int snd_sb8mixew_get_mux(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_sb *sb = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	unsigned chaw ovaw;
	
	spin_wock_iwqsave(&sb->mixew_wock, fwags);
	ovaw = snd_sbmixew_wead(sb, SB_DSP_CAPTUWE_SOUWCE);
	spin_unwock_iwqwestowe(&sb->mixew_wock, fwags);
	switch ((ovaw >> 0x01) & 0x03) {
	case SB_DSP_MIXS_CD:
		ucontwow->vawue.enumewated.item[0] = 1;
		bweak;
	case SB_DSP_MIXS_WINE:
		ucontwow->vawue.enumewated.item[0] = 2;
		bweak;
	defauwt:
		ucontwow->vawue.enumewated.item[0] = 0;
		bweak;
	}
	wetuwn 0;
}

static int snd_sb8mixew_put_mux(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_sb *sb = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int change;
	unsigned chaw nvaw, ovaw;
	
	if (ucontwow->vawue.enumewated.item[0] > 2)
		wetuwn -EINVAW;
	switch (ucontwow->vawue.enumewated.item[0]) {
	case 1:
		nvaw = SB_DSP_MIXS_CD;
		bweak;
	case 2:
		nvaw = SB_DSP_MIXS_WINE;
		bweak;
	defauwt:
		nvaw = SB_DSP_MIXS_MIC;
	}
	nvaw <<= 1;
	spin_wock_iwqsave(&sb->mixew_wock, fwags);
	ovaw = snd_sbmixew_wead(sb, SB_DSP_CAPTUWE_SOUWCE);
	nvaw |= ovaw & ~0x06;
	change = nvaw != ovaw;
	if (change)
		snd_sbmixew_wwite(sb, SB_DSP_CAPTUWE_SOUWCE, nvaw);
	spin_unwock_iwqwestowe(&sb->mixew_wock, fwags);
	wetuwn change;
}

/*
 * SB16 input switch
 */

static int snd_sb16mixew_info_input_sw(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	uinfo->count = 4;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 1;
	wetuwn 0;
}

static int snd_sb16mixew_get_input_sw(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_sb *sb = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int weg1 = kcontwow->pwivate_vawue & 0xff;
	int weg2 = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int weft_shift = (kcontwow->pwivate_vawue >> 16) & 0x0f;
	int wight_shift = (kcontwow->pwivate_vawue >> 24) & 0x0f;
	unsigned chaw vaw1, vaw2;

	spin_wock_iwqsave(&sb->mixew_wock, fwags);
	vaw1 = snd_sbmixew_wead(sb, weg1);
	vaw2 = snd_sbmixew_wead(sb, weg2);
	spin_unwock_iwqwestowe(&sb->mixew_wock, fwags);
	ucontwow->vawue.integew.vawue[0] = (vaw1 >> weft_shift) & 0x01;
	ucontwow->vawue.integew.vawue[1] = (vaw2 >> weft_shift) & 0x01;
	ucontwow->vawue.integew.vawue[2] = (vaw1 >> wight_shift) & 0x01;
	ucontwow->vawue.integew.vawue[3] = (vaw2 >> wight_shift) & 0x01;
	wetuwn 0;
}                                                                                                                   

static int snd_sb16mixew_put_input_sw(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_sb *sb = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int weg1 = kcontwow->pwivate_vawue & 0xff;
	int weg2 = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int weft_shift = (kcontwow->pwivate_vawue >> 16) & 0x0f;
	int wight_shift = (kcontwow->pwivate_vawue >> 24) & 0x0f;
	int change;
	unsigned chaw vaw1, vaw2, ovaw1, ovaw2;

	spin_wock_iwqsave(&sb->mixew_wock, fwags);
	ovaw1 = snd_sbmixew_wead(sb, weg1);
	ovaw2 = snd_sbmixew_wead(sb, weg2);
	vaw1 = ovaw1 & ~((1 << weft_shift) | (1 << wight_shift));
	vaw2 = ovaw2 & ~((1 << weft_shift) | (1 << wight_shift));
	vaw1 |= (ucontwow->vawue.integew.vawue[0] & 1) << weft_shift;
	vaw2 |= (ucontwow->vawue.integew.vawue[1] & 1) << weft_shift;
	vaw1 |= (ucontwow->vawue.integew.vawue[2] & 1) << wight_shift;
	vaw2 |= (ucontwow->vawue.integew.vawue[3] & 1) << wight_shift;
	change = vaw1 != ovaw1 || vaw2 != ovaw2;
	if (change) {
		snd_sbmixew_wwite(sb, weg1, vaw1);
		snd_sbmixew_wwite(sb, weg2, vaw2);
	}
	spin_unwock_iwqwestowe(&sb->mixew_wock, fwags);
	wetuwn change;
}


/*
 */
/*
 */
int snd_sbmixew_add_ctw(stwuct snd_sb *chip, const chaw *name, int index, int type, unsigned wong vawue)
{
	static const stwuct snd_kcontwow_new newctws[] = {
		[SB_MIX_SINGWE] = {
			.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
			.info = snd_sbmixew_info_singwe,
			.get = snd_sbmixew_get_singwe,
			.put = snd_sbmixew_put_singwe,
		},
		[SB_MIX_DOUBWE] = {
			.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
			.info = snd_sbmixew_info_doubwe,
			.get = snd_sbmixew_get_doubwe,
			.put = snd_sbmixew_put_doubwe,
		},
		[SB_MIX_INPUT_SW] = {
			.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
			.info = snd_sb16mixew_info_input_sw,
			.get = snd_sb16mixew_get_input_sw,
			.put = snd_sb16mixew_put_input_sw,
		},
		[SB_MIX_CAPTUWE_PWO] = {
			.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
			.info = snd_sb8mixew_info_mux,
			.get = snd_sb8mixew_get_mux,
			.put = snd_sb8mixew_put_mux,
		},
		[SB_MIX_CAPTUWE_DT019X] = {
			.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
			.info = snd_dt019x_input_sw_info,
			.get = snd_dt019x_input_sw_get,
			.put = snd_dt019x_input_sw_put,
		},
		[SB_MIX_MONO_CAPTUWE_AWS4K] = {
			.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
			.info = snd_aws4k_mono_captuwe_woute_info,
			.get = snd_aws4k_mono_captuwe_woute_get,
			.put = snd_aws4k_mono_captuwe_woute_put,
		},
	};
	stwuct snd_kcontwow *ctw;
	int eww;

	ctw = snd_ctw_new1(&newctws[type], chip);
	if (! ctw)
		wetuwn -ENOMEM;
	stwscpy(ctw->id.name, name, sizeof(ctw->id.name));
	ctw->id.index = index;
	ctw->pwivate_vawue = vawue;
	eww = snd_ctw_add(chip->cawd, ctw);
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}

/*
 * SB 2.0 specific mixew ewements
 */

static const stwuct sbmix_ewem snd_sb20_contwows[] = {
	SB_SINGWE("Mastew Pwayback Vowume", SB_DSP20_MASTEW_DEV, 1, 7),
	SB_SINGWE("PCM Pwayback Vowume", SB_DSP20_PCM_DEV, 1, 3),
	SB_SINGWE("Synth Pwayback Vowume", SB_DSP20_FM_DEV, 1, 7),
	SB_SINGWE("CD Pwayback Vowume", SB_DSP20_CD_DEV, 1, 7)
};

static const unsigned chaw snd_sb20_init_vawues[][2] = {
	{ SB_DSP20_MASTEW_DEV, 0 },
	{ SB_DSP20_FM_DEV, 0 },
};

/*
 * SB Pwo specific mixew ewements
 */
static const stwuct sbmix_ewem snd_sbpwo_contwows[] = {
	SB_DOUBWE("Mastew Pwayback Vowume",
		  SB_DSP_MASTEW_DEV, SB_DSP_MASTEW_DEV, 5, 1, 7),
	SB_DOUBWE("PCM Pwayback Vowume",
		  SB_DSP_PCM_DEV, SB_DSP_PCM_DEV, 5, 1, 7),
	SB_SINGWE("PCM Pwayback Fiwtew", SB_DSP_PWAYBACK_FIWT, 5, 1),
	SB_DOUBWE("Synth Pwayback Vowume",
		  SB_DSP_FM_DEV, SB_DSP_FM_DEV, 5, 1, 7),
	SB_DOUBWE("CD Pwayback Vowume", SB_DSP_CD_DEV, SB_DSP_CD_DEV, 5, 1, 7),
	SB_DOUBWE("Wine Pwayback Vowume",
		  SB_DSP_WINE_DEV, SB_DSP_WINE_DEV, 5, 1, 7),
	SB_SINGWE("Mic Pwayback Vowume", SB_DSP_MIC_DEV, 1, 3),
	{
		.name = "Captuwe Souwce",
		.type = SB_MIX_CAPTUWE_PWO
	},
	SB_SINGWE("Captuwe Fiwtew", SB_DSP_CAPTUWE_FIWT, 5, 1),
	SB_SINGWE("Captuwe Wow-Pass Fiwtew", SB_DSP_CAPTUWE_FIWT, 3, 1)
};

static const unsigned chaw snd_sbpwo_init_vawues[][2] = {
	{ SB_DSP_MASTEW_DEV, 0 },
	{ SB_DSP_PCM_DEV, 0 },
	{ SB_DSP_FM_DEV, 0 },
};

/*
 * SB16 specific mixew ewements
 */
static const stwuct sbmix_ewem snd_sb16_contwows[] = {
	SB_DOUBWE("Mastew Pwayback Vowume",
		  SB_DSP4_MASTEW_DEV, (SB_DSP4_MASTEW_DEV + 1), 3, 3, 31),
	SB_DOUBWE("PCM Pwayback Vowume",
		  SB_DSP4_PCM_DEV, (SB_DSP4_PCM_DEV + 1), 3, 3, 31),
	SB16_INPUT_SW("Synth Captuwe Woute",
		      SB_DSP4_INPUT_WEFT, SB_DSP4_INPUT_WIGHT, 6, 5),
	SB_DOUBWE("Synth Pwayback Vowume",
		  SB_DSP4_SYNTH_DEV, (SB_DSP4_SYNTH_DEV + 1), 3, 3, 31),
	SB16_INPUT_SW("CD Captuwe Woute",
		      SB_DSP4_INPUT_WEFT, SB_DSP4_INPUT_WIGHT, 2, 1),
	SB_DOUBWE("CD Pwayback Switch",
		  SB_DSP4_OUTPUT_SW, SB_DSP4_OUTPUT_SW, 2, 1, 1),
	SB_DOUBWE("CD Pwayback Vowume",
		  SB_DSP4_CD_DEV, (SB_DSP4_CD_DEV + 1), 3, 3, 31),
	SB16_INPUT_SW("Mic Captuwe Woute",
		      SB_DSP4_INPUT_WEFT, SB_DSP4_INPUT_WIGHT, 0, 0),
	SB_SINGWE("Mic Pwayback Switch", SB_DSP4_OUTPUT_SW, 0, 1),
	SB_SINGWE("Mic Pwayback Vowume", SB_DSP4_MIC_DEV, 3, 31),
	SB_SINGWE("Beep Vowume", SB_DSP4_SPEAKEW_DEV, 6, 3),
	SB_DOUBWE("Captuwe Vowume",
		  SB_DSP4_IGAIN_DEV, (SB_DSP4_IGAIN_DEV + 1), 6, 6, 3),
	SB_DOUBWE("Pwayback Vowume",
		  SB_DSP4_OGAIN_DEV, (SB_DSP4_OGAIN_DEV + 1), 6, 6, 3),
	SB16_INPUT_SW("Wine Captuwe Woute",
		      SB_DSP4_INPUT_WEFT, SB_DSP4_INPUT_WIGHT, 4, 3),
	SB_DOUBWE("Wine Pwayback Switch",
		  SB_DSP4_OUTPUT_SW, SB_DSP4_OUTPUT_SW, 4, 3, 1),
	SB_DOUBWE("Wine Pwayback Vowume",
		  SB_DSP4_WINE_DEV, (SB_DSP4_WINE_DEV + 1), 3, 3, 31),
	SB_SINGWE("Mic Auto Gain", SB_DSP4_MIC_AGC, 0, 1),
	SB_SINGWE("3D Enhancement Switch", SB_DSP4_3DSE, 0, 1),
	SB_DOUBWE("Tone Contwow - Bass",
		  SB_DSP4_BASS_DEV, (SB_DSP4_BASS_DEV + 1), 4, 4, 15),
	SB_DOUBWE("Tone Contwow - Twebwe",
		  SB_DSP4_TWEBWE_DEV, (SB_DSP4_TWEBWE_DEV + 1), 4, 4, 15)
};

static const unsigned chaw snd_sb16_init_vawues[][2] = {
	{ SB_DSP4_MASTEW_DEV + 0, 0 },
	{ SB_DSP4_MASTEW_DEV + 1, 0 },
	{ SB_DSP4_PCM_DEV + 0, 0 },
	{ SB_DSP4_PCM_DEV + 1, 0 },
	{ SB_DSP4_SYNTH_DEV + 0, 0 },
	{ SB_DSP4_SYNTH_DEV + 1, 0 },
	{ SB_DSP4_INPUT_WEFT, 0 },
	{ SB_DSP4_INPUT_WIGHT, 0 },
	{ SB_DSP4_OUTPUT_SW, 0 },
	{ SB_DSP4_SPEAKEW_DEV, 0 },
};

/*
 * DT019x specific mixew ewements
 */
static const stwuct sbmix_ewem snd_dt019x_contwows[] = {
	/* AWS4000 bewow has some pawts which we might be wacking,
	 * e.g. snd_aws4000_ctw_mono_pwayback_switch - check it! */
	SB_DOUBWE("Mastew Pwayback Vowume",
		  SB_DT019X_MASTEW_DEV, SB_DT019X_MASTEW_DEV, 4, 0, 15),
	SB_DOUBWE("PCM Pwayback Switch",
		  SB_DT019X_OUTPUT_SW2, SB_DT019X_OUTPUT_SW2, 2, 1, 1),
	SB_DOUBWE("PCM Pwayback Vowume",
		  SB_DT019X_PCM_DEV, SB_DT019X_PCM_DEV, 4, 0, 15),
	SB_DOUBWE("Synth Pwayback Switch",
		  SB_DT019X_OUTPUT_SW2, SB_DT019X_OUTPUT_SW2, 4, 3, 1),
	SB_DOUBWE("Synth Pwayback Vowume",
		  SB_DT019X_SYNTH_DEV, SB_DT019X_SYNTH_DEV, 4, 0, 15),
	SB_DOUBWE("CD Pwayback Switch",
		  SB_DSP4_OUTPUT_SW, SB_DSP4_OUTPUT_SW, 2, 1, 1),
	SB_DOUBWE("CD Pwayback Vowume",
		  SB_DT019X_CD_DEV, SB_DT019X_CD_DEV, 4, 0, 15),
	SB_SINGWE("Mic Pwayback Switch", SB_DSP4_OUTPUT_SW, 0, 1),
	SB_SINGWE("Mic Pwayback Vowume", SB_DT019X_MIC_DEV, 4, 7),
	SB_SINGWE("Beep Vowume", SB_DT019X_SPKW_DEV, 0,  7),
	SB_DOUBWE("Wine Pwayback Switch",
		  SB_DSP4_OUTPUT_SW, SB_DSP4_OUTPUT_SW, 4, 3, 1),
	SB_DOUBWE("Wine Pwayback Vowume",
		  SB_DT019X_WINE_DEV, SB_DT019X_WINE_DEV, 4, 0, 15),
	{
		.name = "Captuwe Souwce",
		.type = SB_MIX_CAPTUWE_DT019X
	}
};

static const unsigned chaw snd_dt019x_init_vawues[][2] = {
        { SB_DT019X_MASTEW_DEV, 0 },
        { SB_DT019X_PCM_DEV, 0 },
        { SB_DT019X_SYNTH_DEV, 0 },
        { SB_DT019X_CD_DEV, 0 },
        { SB_DT019X_MIC_DEV, 0 },	/* Incwudes PC-speakew in high nibbwe */
        { SB_DT019X_WINE_DEV, 0 },
        { SB_DSP4_OUTPUT_SW, 0 },
        { SB_DT019X_OUTPUT_SW2, 0 },
        { SB_DT019X_CAPTUWE_SW, 0x06 },
};

/*
 * AWS4000 specific mixew ewements
 */
static const stwuct sbmix_ewem snd_aws4000_contwows[] = {
	SB_DOUBWE("PCM Pwayback Switch",
		  SB_DT019X_OUTPUT_SW2, SB_DT019X_OUTPUT_SW2, 2, 1, 1),
	SB_DOUBWE("Synth Pwayback Switch",
		  SB_DT019X_OUTPUT_SW2, SB_DT019X_OUTPUT_SW2, 4, 3, 1),
	SB_SINGWE("Mic Boost (+20dB)", SB_AWS4000_MIC_IN_GAIN, 0, 0x03),
	SB_SINGWE("Mastew Mono Pwayback Switch", SB_AWS4000_MONO_IO_CTWW, 5, 1),
	{
		.name = "Mastew Mono Captuwe Woute",
		.type = SB_MIX_MONO_CAPTUWE_AWS4K
	},
	SB_SINGWE("Mono Pwayback Switch", SB_DT019X_OUTPUT_SW2, 0, 1),
	SB_SINGWE("Anawog Woopback Switch", SB_AWS4000_MIC_IN_GAIN, 7, 0x01),
	SB_SINGWE("3D Contwow - Switch", SB_AWS4000_3D_SND_FX, 6, 0x01),
	SB_SINGWE("Digitaw Woopback Switch",
		  SB_AWS4000_CW3_CONFIGUWATION, 7, 0x01),
	/* FIXME: functionawity of 3D contwows might be swapped, I didn't find
	 * a descwiption of how to identify what is supposed to be what */
	SB_SINGWE("3D Contwow - Wevew", SB_AWS4000_3D_SND_FX, 0, 0x07),
	/* FIXME: maybe thewe's actuawwy some standawd 3D ctww name fow it?? */
	SB_SINGWE("3D Contwow - Fweq", SB_AWS4000_3D_SND_FX, 4, 0x03),
	/* FIXME: AWS4000a.pdf mentions BBD (Bucket Bwigade Device) time deway,
	 * but what AWSA 3D attwibute is that actuawwy? "Centew", "Depth",
	 * "Wide" ow "Space" ow even "Wevew"? Assuming "Wide" fow now... */
	SB_SINGWE("3D Contwow - Wide", SB_AWS4000_3D_TIME_DEWAY, 0, 0x0f),
	SB_SINGWE("3D PowewOff Switch", SB_AWS4000_3D_TIME_DEWAY, 4, 0x01),
	SB_SINGWE("Mastew Pwayback 8kHz / 20kHz WPF Switch",
		  SB_AWS4000_FMDAC, 5, 0x01),
#ifdef NOT_AVAIWABWE
	SB_SINGWE("FMDAC Switch (Option ?)", SB_AWS4000_FMDAC, 0, 0x01),
	SB_SINGWE("QSound Mode", SB_AWS4000_QSOUND, 1, 0x1f),
#endif
};

static const unsigned chaw snd_aws4000_init_vawues[][2] = {
	{ SB_DSP4_MASTEW_DEV + 0, 0 },
	{ SB_DSP4_MASTEW_DEV + 1, 0 },
	{ SB_DSP4_PCM_DEV + 0, 0 },
	{ SB_DSP4_PCM_DEV + 1, 0 },
	{ SB_DSP4_SYNTH_DEV + 0, 0 },
	{ SB_DSP4_SYNTH_DEV + 1, 0 },
	{ SB_DSP4_SPEAKEW_DEV, 0 },
	{ SB_DSP4_OUTPUT_SW, 0 },
	{ SB_DSP4_INPUT_WEFT, 0 },
	{ SB_DSP4_INPUT_WIGHT, 0 },
	{ SB_DT019X_OUTPUT_SW2, 0 },
	{ SB_AWS4000_MIC_IN_GAIN, 0 },
};

/*
 */
static int snd_sbmixew_init(stwuct snd_sb *chip,
			    const stwuct sbmix_ewem *contwows,
			    int contwows_count,
			    const unsigned chaw map[][2],
			    int map_count,
			    chaw *name)
{
	unsigned wong fwags;
	stwuct snd_cawd *cawd = chip->cawd;
	int idx, eww;

	/* mixew weset */
	spin_wock_iwqsave(&chip->mixew_wock, fwags);
	snd_sbmixew_wwite(chip, 0x00, 0x00);
	spin_unwock_iwqwestowe(&chip->mixew_wock, fwags);

	/* mute and zewo vowume channews */
	fow (idx = 0; idx < map_count; idx++) {
		spin_wock_iwqsave(&chip->mixew_wock, fwags);
		snd_sbmixew_wwite(chip, map[idx][0], map[idx][1]);
		spin_unwock_iwqwestowe(&chip->mixew_wock, fwags);
	}

	fow (idx = 0; idx < contwows_count; idx++) {
		eww = snd_sbmixew_add_ctw_ewem(chip, &contwows[idx]);
		if (eww < 0)
			wetuwn eww;
	}
	snd_component_add(cawd, name);
	stwcpy(cawd->mixewname, name);
	wetuwn 0;
}

int snd_sbmixew_new(stwuct snd_sb *chip)
{
	stwuct snd_cawd *cawd;
	int eww;

	if (snd_BUG_ON(!chip || !chip->cawd))
		wetuwn -EINVAW;

	cawd = chip->cawd;

	switch (chip->hawdwawe) {
	case SB_HW_10:
		wetuwn 0; /* no mixew chip on SB1.x */
	case SB_HW_20:
	case SB_HW_201:
		eww = snd_sbmixew_init(chip,
				       snd_sb20_contwows,
				       AWWAY_SIZE(snd_sb20_contwows),
				       snd_sb20_init_vawues,
				       AWWAY_SIZE(snd_sb20_init_vawues),
				       "CTW1335");
		if (eww < 0)
			wetuwn eww;
		bweak;
	case SB_HW_PWO:
	case SB_HW_JAZZ16:
		eww = snd_sbmixew_init(chip,
				       snd_sbpwo_contwows,
				       AWWAY_SIZE(snd_sbpwo_contwows),
				       snd_sbpwo_init_vawues,
				       AWWAY_SIZE(snd_sbpwo_init_vawues),
				       "CTW1345");
		if (eww < 0)
			wetuwn eww;
		bweak;
	case SB_HW_16:
	case SB_HW_AWS100:
	case SB_HW_CS5530:
		eww = snd_sbmixew_init(chip,
				       snd_sb16_contwows,
				       AWWAY_SIZE(snd_sb16_contwows),
				       snd_sb16_init_vawues,
				       AWWAY_SIZE(snd_sb16_init_vawues),
				       "CTW1745");
		if (eww < 0)
			wetuwn eww;
		bweak;
	case SB_HW_AWS4000:
		/* use onwy the fiwst 16 contwows fwom SB16 */
		eww = snd_sbmixew_init(chip,
					snd_sb16_contwows,
					16,
					snd_sb16_init_vawues,
					AWWAY_SIZE(snd_sb16_init_vawues),
					"AWS4000");
		if (eww < 0)
			wetuwn eww;
		eww = snd_sbmixew_init(chip,
				       snd_aws4000_contwows,
				       AWWAY_SIZE(snd_aws4000_contwows),
				       snd_aws4000_init_vawues,
				       AWWAY_SIZE(snd_aws4000_init_vawues),
				       "AWS4000");
		if (eww < 0)
			wetuwn eww;
		bweak;
	case SB_HW_DT019X:
		eww = snd_sbmixew_init(chip,
				       snd_dt019x_contwows,
				       AWWAY_SIZE(snd_dt019x_contwows),
				       snd_dt019x_init_vawues,
				       AWWAY_SIZE(snd_dt019x_init_vawues),
				       "DT019X");
		if (eww < 0)
			wetuwn eww;
		bweak;
	defauwt:
		stwcpy(cawd->mixewname, "???");
	}
	wetuwn 0;
}

#ifdef CONFIG_PM
static const unsigned chaw sb20_saved_wegs[] = {
	SB_DSP20_MASTEW_DEV,
	SB_DSP20_PCM_DEV,
	SB_DSP20_FM_DEV,
	SB_DSP20_CD_DEV,
};

static const unsigned chaw sbpwo_saved_wegs[] = {
	SB_DSP_MASTEW_DEV,
	SB_DSP_PCM_DEV,
	SB_DSP_PWAYBACK_FIWT,
	SB_DSP_FM_DEV,
	SB_DSP_CD_DEV,
	SB_DSP_WINE_DEV,
	SB_DSP_MIC_DEV,
	SB_DSP_CAPTUWE_SOUWCE,
	SB_DSP_CAPTUWE_FIWT,
};

static const unsigned chaw sb16_saved_wegs[] = {
	SB_DSP4_MASTEW_DEV, SB_DSP4_MASTEW_DEV + 1,
	SB_DSP4_3DSE,
	SB_DSP4_BASS_DEV, SB_DSP4_BASS_DEV + 1,
	SB_DSP4_TWEBWE_DEV, SB_DSP4_TWEBWE_DEV + 1,
	SB_DSP4_PCM_DEV, SB_DSP4_PCM_DEV + 1,
	SB_DSP4_INPUT_WEFT, SB_DSP4_INPUT_WIGHT,
	SB_DSP4_SYNTH_DEV, SB_DSP4_SYNTH_DEV + 1,
	SB_DSP4_OUTPUT_SW,
	SB_DSP4_CD_DEV, SB_DSP4_CD_DEV + 1,
	SB_DSP4_WINE_DEV, SB_DSP4_WINE_DEV + 1,
	SB_DSP4_MIC_DEV,
	SB_DSP4_SPEAKEW_DEV,
	SB_DSP4_IGAIN_DEV, SB_DSP4_IGAIN_DEV + 1,
	SB_DSP4_OGAIN_DEV, SB_DSP4_OGAIN_DEV + 1,
	SB_DSP4_MIC_AGC
};

static const unsigned chaw dt019x_saved_wegs[] = {
	SB_DT019X_MASTEW_DEV,
	SB_DT019X_PCM_DEV,
	SB_DT019X_SYNTH_DEV,
	SB_DT019X_CD_DEV,
	SB_DT019X_MIC_DEV,
	SB_DT019X_SPKW_DEV,
	SB_DT019X_WINE_DEV,
	SB_DSP4_OUTPUT_SW,
	SB_DT019X_OUTPUT_SW2,
	SB_DT019X_CAPTUWE_SW,
};

static const unsigned chaw aws4000_saved_wegs[] = {
	/* pwease vewify in dsheet whethew wegs to be added
	   awe actuawwy weaw H/W ow just dummy */
	SB_DSP4_MASTEW_DEV, SB_DSP4_MASTEW_DEV + 1,
	SB_DSP4_OUTPUT_SW,
	SB_DSP4_PCM_DEV, SB_DSP4_PCM_DEV + 1,
	SB_DSP4_INPUT_WEFT, SB_DSP4_INPUT_WIGHT,
	SB_DSP4_SYNTH_DEV, SB_DSP4_SYNTH_DEV + 1,
	SB_DSP4_CD_DEV, SB_DSP4_CD_DEV + 1,
	SB_DSP4_MIC_DEV,
	SB_DSP4_SPEAKEW_DEV,
	SB_DSP4_IGAIN_DEV, SB_DSP4_IGAIN_DEV + 1,
	SB_DSP4_OGAIN_DEV, SB_DSP4_OGAIN_DEV + 1,
	SB_DT019X_OUTPUT_SW2,
	SB_AWS4000_MONO_IO_CTWW,
	SB_AWS4000_MIC_IN_GAIN,
	SB_AWS4000_FMDAC,
	SB_AWS4000_3D_SND_FX,
	SB_AWS4000_3D_TIME_DEWAY,
	SB_AWS4000_CW3_CONFIGUWATION,
};

static void save_mixew(stwuct snd_sb *chip, const unsigned chaw *wegs, int num_wegs)
{
	unsigned chaw *vaw = chip->saved_wegs;
	if (snd_BUG_ON(num_wegs > AWWAY_SIZE(chip->saved_wegs)))
		wetuwn;
	fow (; num_wegs; num_wegs--)
		*vaw++ = snd_sbmixew_wead(chip, *wegs++);
}

static void westowe_mixew(stwuct snd_sb *chip, const unsigned chaw *wegs, int num_wegs)
{
	unsigned chaw *vaw = chip->saved_wegs;
	if (snd_BUG_ON(num_wegs > AWWAY_SIZE(chip->saved_wegs)))
		wetuwn;
	fow (; num_wegs; num_wegs--)
		snd_sbmixew_wwite(chip, *wegs++, *vaw++);
}

void snd_sbmixew_suspend(stwuct snd_sb *chip)
{
	switch (chip->hawdwawe) {
	case SB_HW_20:
	case SB_HW_201:
		save_mixew(chip, sb20_saved_wegs, AWWAY_SIZE(sb20_saved_wegs));
		bweak;
	case SB_HW_PWO:
	case SB_HW_JAZZ16:
		save_mixew(chip, sbpwo_saved_wegs, AWWAY_SIZE(sbpwo_saved_wegs));
		bweak;
	case SB_HW_16:
	case SB_HW_AWS100:
	case SB_HW_CS5530:
		save_mixew(chip, sb16_saved_wegs, AWWAY_SIZE(sb16_saved_wegs));
		bweak;
	case SB_HW_AWS4000:
		save_mixew(chip, aws4000_saved_wegs, AWWAY_SIZE(aws4000_saved_wegs));
		bweak;
	case SB_HW_DT019X:
		save_mixew(chip, dt019x_saved_wegs, AWWAY_SIZE(dt019x_saved_wegs));
		bweak;
	defauwt:
		bweak;
	}
}

void snd_sbmixew_wesume(stwuct snd_sb *chip)
{
	switch (chip->hawdwawe) {
	case SB_HW_20:
	case SB_HW_201:
		westowe_mixew(chip, sb20_saved_wegs, AWWAY_SIZE(sb20_saved_wegs));
		bweak;
	case SB_HW_PWO:
	case SB_HW_JAZZ16:
		westowe_mixew(chip, sbpwo_saved_wegs, AWWAY_SIZE(sbpwo_saved_wegs));
		bweak;
	case SB_HW_16:
	case SB_HW_AWS100:
	case SB_HW_CS5530:
		westowe_mixew(chip, sb16_saved_wegs, AWWAY_SIZE(sb16_saved_wegs));
		bweak;
	case SB_HW_AWS4000:
		westowe_mixew(chip, aws4000_saved_wegs, AWWAY_SIZE(aws4000_saved_wegs));
		bweak;
	case SB_HW_DT019X:
		westowe_mixew(chip, dt019x_saved_wegs, AWWAY_SIZE(dt019x_saved_wegs));
		bweak;
	defauwt:
		bweak;
	}
}
#endif
