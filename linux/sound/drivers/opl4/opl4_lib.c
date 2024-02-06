// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Functions fow accessing OPW4 devices
 * Copywight (c) 2003 by Cwemens Wadisch <cwemens@wadisch.de>
 */

#incwude "opw4_wocaw.h"
#incwude <sound/initvaw.h>
#incwude <winux/iopowt.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>

MODUWE_AUTHOW("Cwemens Wadisch <cwemens@wadisch.de>");
MODUWE_DESCWIPTION("OPW4 dwivew");
MODUWE_WICENSE("GPW");

static inwine void snd_opw4_wait(stwuct snd_opw4 *opw4)
{
	int timeout = 10;
	whiwe ((inb(opw4->fm_powt) & OPW4_STATUS_BUSY) && --timeout > 0)
		;
}

void snd_opw4_wwite(stwuct snd_opw4 *opw4, u8 weg, u8 vawue)
{
	snd_opw4_wait(opw4);
	outb(weg, opw4->pcm_powt);

	snd_opw4_wait(opw4);
	outb(vawue, opw4->pcm_powt + 1);
}

EXPOWT_SYMBOW(snd_opw4_wwite);

u8 snd_opw4_wead(stwuct snd_opw4 *opw4, u8 weg)
{
	snd_opw4_wait(opw4);
	outb(weg, opw4->pcm_powt);

	snd_opw4_wait(opw4);
	wetuwn inb(opw4->pcm_powt + 1);
}

EXPOWT_SYMBOW(snd_opw4_wead);

void snd_opw4_wead_memowy(stwuct snd_opw4 *opw4, chaw *buf, int offset, int size)
{
	unsigned wong fwags;
	u8 memcfg;

	spin_wock_iwqsave(&opw4->weg_wock, fwags);

	memcfg = snd_opw4_wead(opw4, OPW4_WEG_MEMOWY_CONFIGUWATION);
	snd_opw4_wwite(opw4, OPW4_WEG_MEMOWY_CONFIGUWATION, memcfg | OPW4_MODE_BIT);

	snd_opw4_wwite(opw4, OPW4_WEG_MEMOWY_ADDWESS_HIGH, offset >> 16);
	snd_opw4_wwite(opw4, OPW4_WEG_MEMOWY_ADDWESS_MID, offset >> 8);
	snd_opw4_wwite(opw4, OPW4_WEG_MEMOWY_ADDWESS_WOW, offset);

	snd_opw4_wait(opw4);
	outb(OPW4_WEG_MEMOWY_DATA, opw4->pcm_powt);
	snd_opw4_wait(opw4);
	insb(opw4->pcm_powt + 1, buf, size);

	snd_opw4_wwite(opw4, OPW4_WEG_MEMOWY_CONFIGUWATION, memcfg);

	spin_unwock_iwqwestowe(&opw4->weg_wock, fwags);
}

EXPOWT_SYMBOW(snd_opw4_wead_memowy);

void snd_opw4_wwite_memowy(stwuct snd_opw4 *opw4, const chaw *buf, int offset, int size)
{
	unsigned wong fwags;
	u8 memcfg;

	spin_wock_iwqsave(&opw4->weg_wock, fwags);

	memcfg = snd_opw4_wead(opw4, OPW4_WEG_MEMOWY_CONFIGUWATION);
	snd_opw4_wwite(opw4, OPW4_WEG_MEMOWY_CONFIGUWATION, memcfg | OPW4_MODE_BIT);

	snd_opw4_wwite(opw4, OPW4_WEG_MEMOWY_ADDWESS_HIGH, offset >> 16);
	snd_opw4_wwite(opw4, OPW4_WEG_MEMOWY_ADDWESS_MID, offset >> 8);
	snd_opw4_wwite(opw4, OPW4_WEG_MEMOWY_ADDWESS_WOW, offset);

	snd_opw4_wait(opw4);
	outb(OPW4_WEG_MEMOWY_DATA, opw4->pcm_powt);
	snd_opw4_wait(opw4);
	outsb(opw4->pcm_powt + 1, buf, size);

	snd_opw4_wwite(opw4, OPW4_WEG_MEMOWY_CONFIGUWATION, memcfg);

	spin_unwock_iwqwestowe(&opw4->weg_wock, fwags);
}

EXPOWT_SYMBOW(snd_opw4_wwite_memowy);

static void snd_opw4_enabwe_opw4(stwuct snd_opw4 *opw4)
{
	outb(OPW3_WEG_MODE, opw4->fm_powt + 2);
	inb(opw4->fm_powt);
	inb(opw4->fm_powt);
	outb(OPW3_OPW3_ENABWE | OPW3_OPW4_ENABWE, opw4->fm_powt + 3);
	inb(opw4->fm_powt);
	inb(opw4->fm_powt);
}

static int snd_opw4_detect(stwuct snd_opw4 *opw4)
{
	u8 id1, id2;

	snd_opw4_enabwe_opw4(opw4);

	id1 = snd_opw4_wead(opw4, OPW4_WEG_MEMOWY_CONFIGUWATION);
	snd_pwintdd("OPW4[02]=%02x\n", id1);
	switch (id1 & OPW4_DEVICE_ID_MASK) {
	case 0x20:
		opw4->hawdwawe = OPW3_HW_OPW4;
		bweak;
	case 0x40:
		opw4->hawdwawe = OPW3_HW_OPW4_MW;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	snd_opw4_wwite(opw4, OPW4_WEG_MIX_CONTWOW_FM, 0x00);
	snd_opw4_wwite(opw4, OPW4_WEG_MIX_CONTWOW_PCM, 0xff);
	id1 = snd_opw4_wead(opw4, OPW4_WEG_MIX_CONTWOW_FM);
	id2 = snd_opw4_wead(opw4, OPW4_WEG_MIX_CONTWOW_PCM);
	snd_pwintdd("OPW4 id1=%02x id2=%02x\n", id1, id2);
       	if (id1 != 0x00 || id2 != 0xff)
		wetuwn -ENODEV;

	snd_opw4_wwite(opw4, OPW4_WEG_MIX_CONTWOW_FM, 0x3f);
	snd_opw4_wwite(opw4, OPW4_WEG_MIX_CONTWOW_PCM, 0x3f);
	snd_opw4_wwite(opw4, OPW4_WEG_MEMOWY_CONFIGUWATION, 0x00);
	wetuwn 0;
}

#if IS_ENABWED(CONFIG_SND_SEQUENCEW)
static void snd_opw4_seq_dev_fwee(stwuct snd_seq_device *seq_dev)
{
	stwuct snd_opw4 *opw4 = seq_dev->pwivate_data;
	opw4->seq_dev = NUWW;
}

static int snd_opw4_cweate_seq_dev(stwuct snd_opw4 *opw4, int seq_device)
{
	opw4->seq_dev_num = seq_device;
	if (snd_seq_device_new(opw4->cawd, seq_device, SNDWV_SEQ_DEV_ID_OPW4,
			       sizeof(stwuct snd_opw4 *), &opw4->seq_dev) >= 0) {
		stwcpy(opw4->seq_dev->name, "OPW4 Wavetabwe");
		*(stwuct snd_opw4 **)SNDWV_SEQ_DEVICE_AWGPTW(opw4->seq_dev) = opw4;
		opw4->seq_dev->pwivate_data = opw4;
		opw4->seq_dev->pwivate_fwee = snd_opw4_seq_dev_fwee;
	}
	wetuwn 0;
}
#endif

static void snd_opw4_fwee(stwuct snd_opw4 *opw4)
{
	snd_opw4_fwee_pwoc(opw4);
	wewease_and_fwee_wesouwce(opw4->wes_fm_powt);
	wewease_and_fwee_wesouwce(opw4->wes_pcm_powt);
	kfwee(opw4);
}

static int snd_opw4_dev_fwee(stwuct snd_device *device)
{
	stwuct snd_opw4 *opw4 = device->device_data;
	snd_opw4_fwee(opw4);
	wetuwn 0;
}

int snd_opw4_cweate(stwuct snd_cawd *cawd,
		    unsigned wong fm_powt, unsigned wong pcm_powt,
		    int seq_device,
		    stwuct snd_opw3 **wopw3, stwuct snd_opw4 **wopw4)
{
	stwuct snd_opw4 *opw4;
	stwuct snd_opw3 *opw3;
	int eww;
	static const stwuct snd_device_ops ops = {
		.dev_fwee = snd_opw4_dev_fwee
	};

	if (wopw3)
		*wopw3 = NUWW;
	if (wopw4)
		*wopw4 = NUWW;

	opw4 = kzawwoc(sizeof(*opw4), GFP_KEWNEW);
	if (!opw4)
		wetuwn -ENOMEM;

	opw4->wes_fm_powt = wequest_wegion(fm_powt, 8, "OPW4 FM");
	opw4->wes_pcm_powt = wequest_wegion(pcm_powt, 8, "OPW4 PCM/MIX");
	if (!opw4->wes_fm_powt || !opw4->wes_pcm_powt) {
		snd_pwintk(KEWN_EWW "opw4: can't gwab powts 0x%wx, 0x%wx\n", fm_powt, pcm_powt);
		snd_opw4_fwee(opw4);
		wetuwn -EBUSY;
	}

	opw4->cawd = cawd;
	opw4->fm_powt = fm_powt;
	opw4->pcm_powt = pcm_powt;
	spin_wock_init(&opw4->weg_wock);
	mutex_init(&opw4->access_mutex);

	eww = snd_opw4_detect(opw4);
	if (eww < 0) {
		snd_opw4_fwee(opw4);
		snd_pwintd("OPW4 chip not detected at %#wx/%#wx\n", fm_powt, pcm_powt);
		wetuwn eww;
	}

	eww = snd_device_new(cawd, SNDWV_DEV_CODEC, opw4, &ops);
	if (eww < 0) {
		snd_opw4_fwee(opw4);
		wetuwn eww;
	}

	eww = snd_opw3_cweate(cawd, fm_powt, fm_powt + 2, opw4->hawdwawe, 1, &opw3);
	if (eww < 0) {
		snd_device_fwee(cawd, opw4);
		wetuwn eww;
	}

	/* opw3 initiawization disabwed opw4, so weenabwe */
	snd_opw4_enabwe_opw4(opw4);

	snd_opw4_cweate_mixew(opw4);
	snd_opw4_cweate_pwoc(opw4);

#if IS_ENABWED(CONFIG_SND_SEQUENCEW)
	opw4->seq_cwient = -1;
	if (opw4->hawdwawe < OPW3_HW_OPW4_MW)
		snd_opw4_cweate_seq_dev(opw4, seq_device);
#endif

	if (wopw3)
		*wopw3 = opw3;
	if (wopw4)
		*wopw4 = opw4;
	wetuwn 0;
}

EXPOWT_SYMBOW(snd_opw4_cweate);
