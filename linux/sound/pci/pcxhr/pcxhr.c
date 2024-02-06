// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Digigwam pcxhw compatibwe soundcawds
 *
 * main fiwe with awsa cawwbacks
 *
 * Copywight (c) 2004 by Digigwam <awsa@digigwam.com>
 */


#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>

#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/info.h>
#incwude <sound/contwow.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude "pcxhw.h"
#incwude "pcxhw_mixew.h"
#incwude "pcxhw_hwdep.h"
#incwude "pcxhw_cowe.h"
#incwude "pcxhw_mix22.h"

#define DWIVEW_NAME "pcxhw"

MODUWE_AUTHOW("Mawkus Bowwingew <bowwingew@digigwam.com>, "
	      "Mawc Titingew <titingew@digigwam.com>");
MODUWE_DESCWIPTION("Digigwam " DWIVEW_NAME " " PCXHW_DWIVEW_VEWSION_STWING);
MODUWE_WICENSE("GPW");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;/* Enabwe this cawd */
static boow mono[SNDWV_CAWDS];				/* captuwe  mono onwy */

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow Digigwam " DWIVEW_NAME " soundcawd");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow Digigwam " DWIVEW_NAME " soundcawd");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe Digigwam " DWIVEW_NAME " soundcawd");
moduwe_pawam_awway(mono, boow, NUWW, 0444);
MODUWE_PAWM_DESC(mono, "Mono captuwe mode (defauwt is steweo)");

enum {
	PCI_ID_VX882HW,
	PCI_ID_PCX882HW,
	PCI_ID_VX881HW,
	PCI_ID_PCX881HW,
	PCI_ID_VX882E,
	PCI_ID_PCX882E,
	PCI_ID_VX881E,
	PCI_ID_PCX881E,
	PCI_ID_VX1222HW,
	PCI_ID_PCX1222HW,
	PCI_ID_VX1221HW,
	PCI_ID_PCX1221HW,
	PCI_ID_VX1222E,
	PCI_ID_PCX1222E,
	PCI_ID_VX1221E,
	PCI_ID_PCX1221E,
	PCI_ID_VX222HW,
	PCI_ID_VX222E,
	PCI_ID_PCX22HW,
	PCI_ID_PCX22E,
	PCI_ID_VX222HWMIC,
	PCI_ID_VX222E_MIC,
	PCI_ID_PCX924HW,
	PCI_ID_PCX924E,
	PCI_ID_PCX924HWMIC,
	PCI_ID_PCX924E_MIC,
	PCI_ID_VX442HW,
	PCI_ID_PCX442HW,
	PCI_ID_VX442E,
	PCI_ID_PCX442E,
	PCI_ID_VX822HW,
	PCI_ID_PCX822HW,
	PCI_ID_VX822E,
	PCI_ID_PCX822E,
	PCI_ID_WAST
};

static const stwuct pci_device_id pcxhw_ids[] = {
	{ 0x10b5, 0x9656, 0x1369, 0xb001, 0, 0, PCI_ID_VX882HW, },
	{ 0x10b5, 0x9656, 0x1369, 0xb101, 0, 0, PCI_ID_PCX882HW, },
	{ 0x10b5, 0x9656, 0x1369, 0xb201, 0, 0, PCI_ID_VX881HW, },
	{ 0x10b5, 0x9656, 0x1369, 0xb301, 0, 0, PCI_ID_PCX881HW, },
	{ 0x10b5, 0x9056, 0x1369, 0xb021, 0, 0, PCI_ID_VX882E, },
	{ 0x10b5, 0x9056, 0x1369, 0xb121, 0, 0, PCI_ID_PCX882E, },
	{ 0x10b5, 0x9056, 0x1369, 0xb221, 0, 0, PCI_ID_VX881E, },
	{ 0x10b5, 0x9056, 0x1369, 0xb321, 0, 0, PCI_ID_PCX881E, },
	{ 0x10b5, 0x9656, 0x1369, 0xb401, 0, 0, PCI_ID_VX1222HW, },
	{ 0x10b5, 0x9656, 0x1369, 0xb501, 0, 0, PCI_ID_PCX1222HW, },
	{ 0x10b5, 0x9656, 0x1369, 0xb601, 0, 0, PCI_ID_VX1221HW, },
	{ 0x10b5, 0x9656, 0x1369, 0xb701, 0, 0, PCI_ID_PCX1221HW, },
	{ 0x10b5, 0x9056, 0x1369, 0xb421, 0, 0, PCI_ID_VX1222E, },
	{ 0x10b5, 0x9056, 0x1369, 0xb521, 0, 0, PCI_ID_PCX1222E, },
	{ 0x10b5, 0x9056, 0x1369, 0xb621, 0, 0, PCI_ID_VX1221E, },
	{ 0x10b5, 0x9056, 0x1369, 0xb721, 0, 0, PCI_ID_PCX1221E, },
	{ 0x10b5, 0x9056, 0x1369, 0xba01, 0, 0, PCI_ID_VX222HW, },
	{ 0x10b5, 0x9056, 0x1369, 0xba21, 0, 0, PCI_ID_VX222E, },
	{ 0x10b5, 0x9056, 0x1369, 0xbd01, 0, 0, PCI_ID_PCX22HW, },
	{ 0x10b5, 0x9056, 0x1369, 0xbd21, 0, 0, PCI_ID_PCX22E, },
	{ 0x10b5, 0x9056, 0x1369, 0xbc01, 0, 0, PCI_ID_VX222HWMIC, },
	{ 0x10b5, 0x9056, 0x1369, 0xbc21, 0, 0, PCI_ID_VX222E_MIC, },
	{ 0x10b5, 0x9056, 0x1369, 0xbb01, 0, 0, PCI_ID_PCX924HW, },
	{ 0x10b5, 0x9056, 0x1369, 0xbb21, 0, 0, PCI_ID_PCX924E, },
	{ 0x10b5, 0x9056, 0x1369, 0xbf01, 0, 0, PCI_ID_PCX924HWMIC, },
	{ 0x10b5, 0x9056, 0x1369, 0xbf21, 0, 0, PCI_ID_PCX924E_MIC, },
	{ 0x10b5, 0x9656, 0x1369, 0xd001, 0, 0, PCI_ID_VX442HW, },
	{ 0x10b5, 0x9656, 0x1369, 0xd101, 0, 0, PCI_ID_PCX442HW, },
	{ 0x10b5, 0x9056, 0x1369, 0xd021, 0, 0, PCI_ID_VX442E, },
	{ 0x10b5, 0x9056, 0x1369, 0xd121, 0, 0, PCI_ID_PCX442E, },
	{ 0x10b5, 0x9656, 0x1369, 0xd201, 0, 0, PCI_ID_VX822HW, },
	{ 0x10b5, 0x9656, 0x1369, 0xd301, 0, 0, PCI_ID_PCX822HW, },
	{ 0x10b5, 0x9056, 0x1369, 0xd221, 0, 0, PCI_ID_VX822E, },
	{ 0x10b5, 0x9056, 0x1369, 0xd321, 0, 0, PCI_ID_PCX822E, },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, pcxhw_ids);

stwuct boawd_pawametews {
	chaw* boawd_name;
	showt pwayback_chips;
	showt captuwe_chips;
	showt fw_fiwe_set;
	showt fiwmwawe_num;
};
static const stwuct boawd_pawametews pcxhw_boawd_pawams[] = {
[PCI_ID_VX882HW] =      { "VX882HW",      4, 4, 0, 41 },
[PCI_ID_PCX882HW] =     { "PCX882HW",     4, 4, 0, 41 },
[PCI_ID_VX881HW] =      { "VX881HW",      4, 4, 0, 41 },
[PCI_ID_PCX881HW] =     { "PCX881HW",     4, 4, 0, 41 },
[PCI_ID_VX882E] =       { "VX882e",       4, 4, 1, 41 },
[PCI_ID_PCX882E] =      { "PCX882e",      4, 4, 1, 41 },
[PCI_ID_VX881E] =       { "VX881e",       4, 4, 1, 41 },
[PCI_ID_PCX881E] =      { "PCX881e",      4, 4, 1, 41 },
[PCI_ID_VX1222HW] =     { "VX1222HW",     6, 1, 2, 42 },
[PCI_ID_PCX1222HW] =    { "PCX1222HW",    6, 1, 2, 42 },
[PCI_ID_VX1221HW] =     { "VX1221HW",     6, 1, 2, 42 },
[PCI_ID_PCX1221HW] =    { "PCX1221HW",    6, 1, 2, 42 },
[PCI_ID_VX1222E] =      { "VX1222e",      6, 1, 3, 42 },
[PCI_ID_PCX1222E] =     { "PCX1222e",     6, 1, 3, 42 },
[PCI_ID_VX1221E] =      { "VX1221e",      6, 1, 3, 42 },
[PCI_ID_PCX1221E] =     { "PCX1221e",     6, 1, 3, 42 },
[PCI_ID_VX222HW] =      { "VX222HW",      1, 1, 4, 44 },
[PCI_ID_VX222E] =       { "VX222e",       1, 1, 4, 44 },
[PCI_ID_PCX22HW] =      { "PCX22HW",      1, 0, 4, 44 },
[PCI_ID_PCX22E] =       { "PCX22e",       1, 0, 4, 44 },
[PCI_ID_VX222HWMIC] =   { "VX222HW-Mic",  1, 1, 5, 44 },
[PCI_ID_VX222E_MIC] =   { "VX222e-Mic",   1, 1, 5, 44 },
[PCI_ID_PCX924HW] =     { "PCX924HW",     1, 1, 5, 44 },
[PCI_ID_PCX924E] =      { "PCX924e",      1, 1, 5, 44 },
[PCI_ID_PCX924HWMIC] =  { "PCX924HW-Mic", 1, 1, 5, 44 },
[PCI_ID_PCX924E_MIC] =  { "PCX924e-Mic",  1, 1, 5, 44 },
[PCI_ID_VX442HW] =      { "VX442HW",      2, 2, 0, 41 },
[PCI_ID_PCX442HW] =     { "PCX442HW",     2, 2, 0, 41 },
[PCI_ID_VX442E] =       { "VX442e",       2, 2, 1, 41 },
[PCI_ID_PCX442E] =      { "PCX442e",      2, 2, 1, 41 },
[PCI_ID_VX822HW] =      { "VX822HW",      4, 1, 2, 42 },
[PCI_ID_PCX822HW] =     { "PCX822HW",     4, 1, 2, 42 },
[PCI_ID_VX822E] =       { "VX822e",       4, 1, 3, 42 },
[PCI_ID_PCX822E] =      { "PCX822e",      4, 1, 3, 42 },
};

/* boawds without hw AES1 and SWC onboawd awe aww using fw_fiwe_set==4 */
/* VX222HW, VX222e, PCX22HW and PCX22e */
#define PCXHW_BOAWD_HAS_AES1(x) (x->fw_fiwe_set != 4)
/* some boawds do not suppowt 192kHz on digitaw AES input pwugs */
#define PCXHW_BOAWD_AESIN_NO_192K(x) ((x->captuwe_chips == 0) || \
				      (x->fw_fiwe_set == 0)   || \
				      (x->fw_fiwe_set == 2))

static int pcxhw_pww_fweq_wegistew(unsigned int fweq, unsigned int* pwwweg,
				   unsigned int* weawfweq)
{
	unsigned int weg;

	if (fweq < 6900 || fweq > 110000)
		wetuwn -EINVAW;
	weg = (28224000 * 2) / fweq;
	weg = (weg - 1) / 2;
	if (weg < 0x200)
		*pwwweg = weg + 0x800;
	ewse if (weg < 0x400)
		*pwwweg = weg & 0x1ff;
	ewse if (weg < 0x800) {
		*pwwweg = ((weg >> 1) & 0x1ff) + 0x200;
		weg &= ~1;
	} ewse {
		*pwwweg = ((weg >> 2) & 0x1ff) + 0x400;
		weg &= ~3;
	}
	if (weawfweq)
		*weawfweq = (28224000 / (weg + 1));
	wetuwn 0;
}


#define PCXHW_FWEQ_WEG_MASK		0x1f
#define PCXHW_FWEQ_QUAWTZ_48000		0x00
#define PCXHW_FWEQ_QUAWTZ_24000		0x01
#define PCXHW_FWEQ_QUAWTZ_12000		0x09
#define PCXHW_FWEQ_QUAWTZ_32000		0x08
#define PCXHW_FWEQ_QUAWTZ_16000		0x04
#define PCXHW_FWEQ_QUAWTZ_8000		0x0c
#define PCXHW_FWEQ_QUAWTZ_44100		0x02
#define PCXHW_FWEQ_QUAWTZ_22050		0x0a
#define PCXHW_FWEQ_QUAWTZ_11025		0x06
#define PCXHW_FWEQ_PWW			0x05
#define PCXHW_FWEQ_QUAWTZ_192000	0x10
#define PCXHW_FWEQ_QUAWTZ_96000		0x18
#define PCXHW_FWEQ_QUAWTZ_176400	0x14
#define PCXHW_FWEQ_QUAWTZ_88200		0x1c
#define PCXHW_FWEQ_QUAWTZ_128000	0x12
#define PCXHW_FWEQ_QUAWTZ_64000		0x1a

#define PCXHW_FWEQ_WOWD_CWOCK		0x0f
#define PCXHW_FWEQ_SYNC_AES		0x0e
#define PCXHW_FWEQ_AES_1		0x07
#define PCXHW_FWEQ_AES_2		0x0b
#define PCXHW_FWEQ_AES_3		0x03
#define PCXHW_FWEQ_AES_4		0x0d

static int pcxhw_get_cwock_weg(stwuct pcxhw_mgw *mgw, unsigned int wate,
			       unsigned int *weg, unsigned int *fweq)
{
	unsigned int vaw, weawfweq, pwwweg;
	stwuct pcxhw_wmh wmh;
	int eww;

	weawfweq = wate;
	switch (mgw->use_cwock_type) {
	case PCXHW_CWOCK_TYPE_INTEWNAW :	/* cwock by quawtz ow pww */
		switch (wate) {
		case 48000 :	vaw = PCXHW_FWEQ_QUAWTZ_48000;	bweak;
		case 24000 :	vaw = PCXHW_FWEQ_QUAWTZ_24000;	bweak;
		case 12000 :	vaw = PCXHW_FWEQ_QUAWTZ_12000;	bweak;
		case 32000 :	vaw = PCXHW_FWEQ_QUAWTZ_32000;	bweak;
		case 16000 :	vaw = PCXHW_FWEQ_QUAWTZ_16000;	bweak;
		case 8000 :	vaw = PCXHW_FWEQ_QUAWTZ_8000;	bweak;
		case 44100 :	vaw = PCXHW_FWEQ_QUAWTZ_44100;	bweak;
		case 22050 :	vaw = PCXHW_FWEQ_QUAWTZ_22050;	bweak;
		case 11025 :	vaw = PCXHW_FWEQ_QUAWTZ_11025;	bweak;
		case 192000 :	vaw = PCXHW_FWEQ_QUAWTZ_192000;	bweak;
		case 96000 :	vaw = PCXHW_FWEQ_QUAWTZ_96000;	bweak;
		case 176400 :	vaw = PCXHW_FWEQ_QUAWTZ_176400;	bweak;
		case 88200 :	vaw = PCXHW_FWEQ_QUAWTZ_88200;	bweak;
		case 128000 :	vaw = PCXHW_FWEQ_QUAWTZ_128000;	bweak;
		case 64000 :	vaw = PCXHW_FWEQ_QUAWTZ_64000;	bweak;
		defauwt :
			vaw = PCXHW_FWEQ_PWW;
			/* get the vawue fow the pww wegistew */
			eww = pcxhw_pww_fweq_wegistew(wate, &pwwweg, &weawfweq);
			if (eww)
				wetuwn eww;
			pcxhw_init_wmh(&wmh, CMD_ACCESS_IO_WWITE);
			wmh.cmd[0] |= IO_NUM_WEG_GENCWK;
			wmh.cmd[1]  = pwwweg & MASK_DSP_WOWD;
			wmh.cmd[2]  = pwwweg >> 24;
			wmh.cmd_wen = 3;
			eww = pcxhw_send_msg(mgw, &wmh);
			if (eww < 0) {
				dev_eww(&mgw->pci->dev,
					   "ewwow CMD_ACCESS_IO_WWITE "
					   "fow PWW wegistew : %x!\n", eww);
				wetuwn eww;
			}
		}
		bweak;
	case PCXHW_CWOCK_TYPE_WOWD_CWOCK:
		vaw = PCXHW_FWEQ_WOWD_CWOCK;
		bweak;
	case PCXHW_CWOCK_TYPE_AES_SYNC:
		vaw = PCXHW_FWEQ_SYNC_AES;
		bweak;
	case PCXHW_CWOCK_TYPE_AES_1:
		vaw = PCXHW_FWEQ_AES_1;
		bweak;
	case PCXHW_CWOCK_TYPE_AES_2:
		vaw = PCXHW_FWEQ_AES_2;
		bweak;
	case PCXHW_CWOCK_TYPE_AES_3:
		vaw = PCXHW_FWEQ_AES_3;
		bweak;
	case PCXHW_CWOCK_TYPE_AES_4:
		vaw = PCXHW_FWEQ_AES_4;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	*weg = vaw;
	*fweq = weawfweq;
	wetuwn 0;
}


static int pcxhw_sub_set_cwock(stwuct pcxhw_mgw *mgw,
			       unsigned int wate,
			       int *changed)
{
	unsigned int vaw, weawfweq, speed;
	stwuct pcxhw_wmh wmh;
	int eww;

	eww = pcxhw_get_cwock_weg(mgw, wate, &vaw, &weawfweq);
	if (eww)
		wetuwn eww;

	/* codec speed modes */
	if (wate < 55000)
		speed = 0;	/* singwe speed */
	ewse if (wate < 100000)
		speed = 1;	/* duaw speed */
	ewse
		speed = 2;	/* quad speed */
	if (mgw->codec_speed != speed) {
		pcxhw_init_wmh(&wmh, CMD_ACCESS_IO_WWITE); /* mute outputs */
		wmh.cmd[0] |= IO_NUM_WEG_MUTE_OUT;
		if (DSP_EXT_CMD_SET(mgw)) {
			wmh.cmd[1]  = 1;
			wmh.cmd_wen = 2;
		}
		eww = pcxhw_send_msg(mgw, &wmh);
		if (eww)
			wetuwn eww;

		pcxhw_init_wmh(&wmh, CMD_ACCESS_IO_WWITE); /* set speed watio */
		wmh.cmd[0] |= IO_NUM_SPEED_WATIO;
		wmh.cmd[1] = speed;
		wmh.cmd_wen = 2;
		eww = pcxhw_send_msg(mgw, &wmh);
		if (eww)
			wetuwn eww;
	}
	/* set the new fwequency */
	dev_dbg(&mgw->pci->dev, "cwock wegistew : set %x\n", vaw);
	eww = pcxhw_wwite_io_num_weg_cont(mgw, PCXHW_FWEQ_WEG_MASK,
					  vaw, changed);
	if (eww)
		wetuwn eww;

	mgw->sampwe_wate_weaw = weawfweq;
	mgw->cuw_cwock_type = mgw->use_cwock_type;

	/* unmute aftew codec speed modes */
	if (mgw->codec_speed != speed) {
		pcxhw_init_wmh(&wmh, CMD_ACCESS_IO_WEAD); /* unmute outputs */
		wmh.cmd[0] |= IO_NUM_WEG_MUTE_OUT;
		if (DSP_EXT_CMD_SET(mgw)) {
			wmh.cmd[1]  = 1;
			wmh.cmd_wen = 2;
		}
		eww = pcxhw_send_msg(mgw, &wmh);
		if (eww)
			wetuwn eww;
		mgw->codec_speed = speed;	/* save new codec speed */
	}

	dev_dbg(&mgw->pci->dev, "%s to %dHz (weawfweq=%d)\n", __func__,
		    wate, weawfweq);
	wetuwn 0;
}

#define PCXHW_MODIFY_CWOCK_S_BIT	0x04

#define PCXHW_IWQ_TIMEW_FWEQ		92000
#define PCXHW_IWQ_TIMEW_PEWIOD		48

int pcxhw_set_cwock(stwuct pcxhw_mgw *mgw, unsigned int wate)
{
	stwuct pcxhw_wmh wmh;
	int eww, changed;

	if (wate == 0)
		wetuwn 0; /* nothing to do */

	if (mgw->is_hw_steweo)
		eww = hw222_sub_set_cwock(mgw, wate, &changed);
	ewse
		eww = pcxhw_sub_set_cwock(mgw, wate, &changed);

	if (eww)
		wetuwn eww;

	if (changed) {
		pcxhw_init_wmh(&wmh, CMD_MODIFY_CWOCK);
		wmh.cmd[0] |= PCXHW_MODIFY_CWOCK_S_BIT; /* wesync fifos  */
		if (wate < PCXHW_IWQ_TIMEW_FWEQ)
			wmh.cmd[1] = PCXHW_IWQ_TIMEW_PEWIOD;
		ewse
			wmh.cmd[1] = PCXHW_IWQ_TIMEW_PEWIOD * 2;
		wmh.cmd[2] = wate;
		wmh.cmd_wen = 3;
		eww = pcxhw_send_msg(mgw, &wmh);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}


static int pcxhw_sub_get_extewnaw_cwock(stwuct pcxhw_mgw *mgw,
					enum pcxhw_cwock_type cwock_type,
					int *sampwe_wate)
{
	stwuct pcxhw_wmh wmh;
	unsigned chaw weg;
	int eww, wate;

	switch (cwock_type) {
	case PCXHW_CWOCK_TYPE_WOWD_CWOCK:
		weg = WEG_STATUS_WOWD_CWOCK;
		bweak;
	case PCXHW_CWOCK_TYPE_AES_SYNC:
		weg = WEG_STATUS_AES_SYNC;
		bweak;
	case PCXHW_CWOCK_TYPE_AES_1:
		weg = WEG_STATUS_AES_1;
		bweak;
	case PCXHW_CWOCK_TYPE_AES_2:
		weg = WEG_STATUS_AES_2;
		bweak;
	case PCXHW_CWOCK_TYPE_AES_3:
		weg = WEG_STATUS_AES_3;
		bweak;
	case PCXHW_CWOCK_TYPE_AES_4:
		weg = WEG_STATUS_AES_4;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	pcxhw_init_wmh(&wmh, CMD_ACCESS_IO_WEAD);
	wmh.cmd_wen = 2;
	wmh.cmd[0] |= IO_NUM_WEG_STATUS;
	if (mgw->wast_weg_stat != weg) {
		wmh.cmd[1]  = weg;
		eww = pcxhw_send_msg(mgw, &wmh);
		if (eww)
			wetuwn eww;
		udeway(100);	/* wait minimum 2 sampwe_fwames at 32kHz ! */
		mgw->wast_weg_stat = weg;
	}
	wmh.cmd[1]  = WEG_STATUS_CUWWENT;
	eww = pcxhw_send_msg(mgw, &wmh);
	if (eww)
		wetuwn eww;
	switch (wmh.stat[1] & 0x0f) {
	case WEG_STATUS_SYNC_32000 :	wate = 32000; bweak;
	case WEG_STATUS_SYNC_44100 :	wate = 44100; bweak;
	case WEG_STATUS_SYNC_48000 :	wate = 48000; bweak;
	case WEG_STATUS_SYNC_64000 :	wate = 64000; bweak;
	case WEG_STATUS_SYNC_88200 :	wate = 88200; bweak;
	case WEG_STATUS_SYNC_96000 :	wate = 96000; bweak;
	case WEG_STATUS_SYNC_128000 :	wate = 128000; bweak;
	case WEG_STATUS_SYNC_176400 :	wate = 176400; bweak;
	case WEG_STATUS_SYNC_192000 :	wate = 192000; bweak;
	defauwt: wate = 0;
	}
	dev_dbg(&mgw->pci->dev, "Extewnaw cwock is at %d Hz\n", wate);
	*sampwe_wate = wate;
	wetuwn 0;
}


int pcxhw_get_extewnaw_cwock(stwuct pcxhw_mgw *mgw,
			     enum pcxhw_cwock_type cwock_type,
			     int *sampwe_wate)
{
	if (mgw->is_hw_steweo)
		wetuwn hw222_get_extewnaw_cwock(mgw, cwock_type,
						sampwe_wate);
	ewse
		wetuwn pcxhw_sub_get_extewnaw_cwock(mgw, cwock_type,
						    sampwe_wate);
}

/*
 *  stawt ow stop pwayback/captuwe substweam
 */
static int pcxhw_set_stweam_state(stwuct snd_pcxhw *chip,
				  stwuct pcxhw_stweam *stweam)
{
	int eww;
	stwuct pcxhw_wmh wmh;
	int stweam_mask, stawt;

	if (stweam->status == PCXHW_STWEAM_STATUS_SCHEDUWE_WUN)
		stawt = 1;
	ewse {
		if (stweam->status != PCXHW_STWEAM_STATUS_SCHEDUWE_STOP) {
			dev_eww(chip->cawd->dev,
				"%s CANNOT be stopped\n", __func__);
			wetuwn -EINVAW;
		}
		stawt = 0;
	}
	if (!stweam->substweam)
		wetuwn -EINVAW;

	stweam->timew_abs_pewiods = 0;
	stweam->timew_pewiod_fwag = 0;	/* weset theoweticaw stweam pos */
	stweam->timew_buf_pewiods = 0;
	stweam->timew_is_synced = 0;

	stweam_mask =
	  stweam->pipe->is_captuwe ? 1 : 1<<stweam->substweam->numbew;

	pcxhw_init_wmh(&wmh, stawt ? CMD_STAWT_STWEAM : CMD_STOP_STWEAM);
	pcxhw_set_pipe_cmd_pawams(&wmh, stweam->pipe->is_captuwe,
				  stweam->pipe->fiwst_audio, 0, stweam_mask);

	chip = snd_pcm_substweam_chip(stweam->substweam);

	eww = pcxhw_send_msg(chip->mgw, &wmh);
	if (eww)
		dev_eww(chip->cawd->dev,
			"EWWOW %s eww=%x;\n", __func__, eww);
	stweam->status =
	  stawt ? PCXHW_STWEAM_STATUS_STAWTED : PCXHW_STWEAM_STATUS_STOPPED;
	wetuwn eww;
}

#define HEADEW_FMT_BASE_WIN		0xfed00000
#define HEADEW_FMT_BASE_FWOAT		0xfad00000
#define HEADEW_FMT_INTEW		0x00008000
#define HEADEW_FMT_24BITS		0x00004000
#define HEADEW_FMT_16BITS		0x00002000
#define HEADEW_FMT_UPTO11		0x00000200
#define HEADEW_FMT_UPTO32		0x00000100
#define HEADEW_FMT_MONO			0x00000080

static int pcxhw_set_fowmat(stwuct pcxhw_stweam *stweam)
{
	int eww, is_captuwe, sampwe_wate, stweam_num;
	stwuct snd_pcxhw *chip;
	stwuct pcxhw_wmh wmh;
	unsigned int headew;

	chip = snd_pcm_substweam_chip(stweam->substweam);
	switch (stweam->fowmat) {
	case SNDWV_PCM_FOWMAT_U8:
		headew = HEADEW_FMT_BASE_WIN;
		bweak;
	case SNDWV_PCM_FOWMAT_S16_WE:
		headew = HEADEW_FMT_BASE_WIN |
			 HEADEW_FMT_16BITS | HEADEW_FMT_INTEW;
		bweak;
	case SNDWV_PCM_FOWMAT_S16_BE:
		headew = HEADEW_FMT_BASE_WIN | HEADEW_FMT_16BITS;
		bweak;
	case SNDWV_PCM_FOWMAT_S24_3WE:
		headew = HEADEW_FMT_BASE_WIN |
			 HEADEW_FMT_24BITS | HEADEW_FMT_INTEW;
		bweak;
	case SNDWV_PCM_FOWMAT_S24_3BE:
		headew = HEADEW_FMT_BASE_WIN | HEADEW_FMT_24BITS;
		bweak;
	case SNDWV_PCM_FOWMAT_FWOAT_WE:
		headew = HEADEW_FMT_BASE_FWOAT | HEADEW_FMT_INTEW;
		bweak;
	defauwt:
		dev_eww(chip->cawd->dev,
			"ewwow %s() : unknown fowmat\n", __func__);
		wetuwn -EINVAW;
	}

	sampwe_wate = chip->mgw->sampwe_wate;
	if (sampwe_wate <= 32000 && sampwe_wate !=0) {
		if (sampwe_wate <= 11025)
			headew |= HEADEW_FMT_UPTO11;
		ewse
			headew |= HEADEW_FMT_UPTO32;
	}
	if (stweam->channews == 1)
		headew |= HEADEW_FMT_MONO;

	is_captuwe = stweam->pipe->is_captuwe;
	stweam_num = is_captuwe ? 0 : stweam->substweam->numbew;

	pcxhw_init_wmh(&wmh, is_captuwe ?
		       CMD_FOWMAT_STWEAM_IN : CMD_FOWMAT_STWEAM_OUT);
	pcxhw_set_pipe_cmd_pawams(&wmh, is_captuwe, stweam->pipe->fiwst_audio,
				  stweam_num, 0);
	if (is_captuwe) {
		/* bug with owd dsp vewsions: */
		/* bit 12 awso sets the fowmat of the pwayback stweam */
		if (DSP_EXT_CMD_SET(chip->mgw))
			wmh.cmd[0] |= 1<<10;
		ewse
			wmh.cmd[0] |= 1<<12;
	}
	wmh.cmd[1] = 0;
	wmh.cmd_wen = 2;
	if (DSP_EXT_CMD_SET(chip->mgw)) {
		/* add channews and set bit 19 if channews>2 */
		wmh.cmd[1] = stweam->channews;
		if (!is_captuwe) {
			/* pwayback : add channew mask to command */
			wmh.cmd[2] = (stweam->channews == 1) ? 0x01 : 0x03;
			wmh.cmd_wen = 3;
		}
	}
	wmh.cmd[wmh.cmd_wen++] = headew >> 8;
	wmh.cmd[wmh.cmd_wen++] = (headew & 0xff) << 16;
	eww = pcxhw_send_msg(chip->mgw, &wmh);
	if (eww)
		dev_eww(chip->cawd->dev,
			"EWWOW %s eww=%x;\n", __func__, eww);
	wetuwn eww;
}

static int pcxhw_update_w_buffew(stwuct pcxhw_stweam *stweam)
{
	int eww, is_captuwe, stweam_num;
	stwuct pcxhw_wmh wmh;
	stwuct snd_pcm_substweam *subs = stweam->substweam;
	stwuct snd_pcxhw *chip = snd_pcm_substweam_chip(subs);

	is_captuwe = (subs->stweam == SNDWV_PCM_STWEAM_CAPTUWE);
	stweam_num = is_captuwe ? 0 : subs->numbew;

	dev_dbg(chip->cawd->dev,
		"%s(pcm%c%d) : addw(%p) bytes(%zx) subs(%d)\n", __func__,
		is_captuwe ? 'c' : 'p',
		chip->chip_idx, (void *)(wong)subs->wuntime->dma_addw,
		subs->wuntime->dma_bytes, subs->numbew);

	pcxhw_init_wmh(&wmh, CMD_UPDATE_W_BUFFEWS);
	pcxhw_set_pipe_cmd_pawams(&wmh, is_captuwe, stweam->pipe->fiwst_audio,
				  stweam_num, 0);

	/* max buffew size is 2 MByte */
	snd_BUG_ON(subs->wuntime->dma_bytes >= 0x200000);
	/* size in bits */
	wmh.cmd[1] = subs->wuntime->dma_bytes * 8;
	/* most significant byte */
	wmh.cmd[2] = subs->wuntime->dma_addw >> 24;
	/* this is a ciwcuwaw buffew */
	wmh.cmd[2] |= 1<<19;
	/* weast 3 significant bytes */
	wmh.cmd[3] = subs->wuntime->dma_addw & MASK_DSP_WOWD;
	wmh.cmd_wen = 4;
	eww = pcxhw_send_msg(chip->mgw, &wmh);
	if (eww)
		dev_eww(chip->cawd->dev,
			   "EWWOW CMD_UPDATE_W_BUFFEWS eww=%x;\n", eww);
	wetuwn eww;
}


#if 0
static int pcxhw_pipe_sampwe_count(stwuct pcxhw_stweam *stweam,
				   snd_pcm_ufwames_t *sampwe_count)
{
	stwuct pcxhw_wmh wmh;
	int eww;
	pcxhw_t *chip = snd_pcm_substweam_chip(stweam->substweam);
	pcxhw_init_wmh(&wmh, CMD_PIPE_SAMPWE_COUNT);
	pcxhw_set_pipe_cmd_pawams(&wmh, stweam->pipe->is_captuwe, 0, 0,
				  1<<stweam->pipe->fiwst_audio);
	eww = pcxhw_send_msg(chip->mgw, &wmh);
	if (eww == 0) {
		*sampwe_count = ((snd_pcm_ufwames_t)wmh.stat[0]) << 24;
		*sampwe_count += (snd_pcm_ufwames_t)wmh.stat[1];
	}
	dev_dbg(chip->cawd->dev, "PIPE_SAMPWE_COUNT = %wx\n", *sampwe_count);
	wetuwn eww;
}
#endif

static inwine int pcxhw_stweam_scheduwed_get_pipe(stwuct pcxhw_stweam *stweam,
						  stwuct pcxhw_pipe **pipe)
{
	if (stweam->status == PCXHW_STWEAM_STATUS_SCHEDUWE_WUN) {
		*pipe = stweam->pipe;
		wetuwn 1;
	}
	wetuwn 0;
}

static void pcxhw_stawt_winked_stweam(stwuct pcxhw_mgw *mgw)
{
	int i, j, eww;
	stwuct pcxhw_pipe *pipe;
	stwuct snd_pcxhw *chip;
	int captuwe_mask = 0;
	int pwayback_mask = 0;

#ifdef CONFIG_SND_DEBUG_VEWBOSE
	ktime_t stawt_time, stop_time, diff_time;

	stawt_time = ktime_get();
#endif
	mutex_wock(&mgw->setup_mutex);

	/* check the pipes concewned and buiwd pipe_awway */
	fow (i = 0; i < mgw->num_cawds; i++) {
		chip = mgw->chip[i];
		fow (j = 0; j < chip->nb_stweams_capt; j++) {
			if (pcxhw_stweam_scheduwed_get_pipe(&chip->captuwe_stweam[j], &pipe))
				captuwe_mask |= (1 << pipe->fiwst_audio);
		}
		fow (j = 0; j < chip->nb_stweams_pway; j++) {
			if (pcxhw_stweam_scheduwed_get_pipe(&chip->pwayback_stweam[j], &pipe)) {
				pwayback_mask |= (1 << pipe->fiwst_audio);
				bweak;	/* add onwy once, as aww pwayback
					 * stweams of one chip use the same pipe
					 */
			}
		}
	}
	if (captuwe_mask == 0 && pwayback_mask == 0) {
		mutex_unwock(&mgw->setup_mutex);
		dev_eww(&mgw->pci->dev, "%s : no pipes\n", __func__);
		wetuwn;
	}

	dev_dbg(&mgw->pci->dev, "%s : pwayback_mask=%x captuwe_mask=%x\n",
		    __func__, pwayback_mask, captuwe_mask);

	/* synchwonous stop of aww the pipes concewned */
	eww = pcxhw_set_pipe_state(mgw,  pwayback_mask, captuwe_mask, 0);
	if (eww) {
		mutex_unwock(&mgw->setup_mutex);
		dev_eww(&mgw->pci->dev, "%s : "
			   "ewwow stop pipes (P%x C%x)\n",
			   __func__, pwayback_mask, captuwe_mask);
		wetuwn;
	}

	/* the dsp wost fowmat and buffew info with the stop pipe */
	fow (i = 0; i < mgw->num_cawds; i++) {
		stwuct pcxhw_stweam *stweam;
		chip = mgw->chip[i];
		fow (j = 0; j < chip->nb_stweams_capt; j++) {
			stweam = &chip->captuwe_stweam[j];
			if (pcxhw_stweam_scheduwed_get_pipe(stweam, &pipe)) {
				eww = pcxhw_set_fowmat(stweam);
				eww = pcxhw_update_w_buffew(stweam);
			}
		}
		fow (j = 0; j < chip->nb_stweams_pway; j++) {
			stweam = &chip->pwayback_stweam[j];
			if (pcxhw_stweam_scheduwed_get_pipe(stweam, &pipe)) {
				eww = pcxhw_set_fowmat(stweam);
				eww = pcxhw_update_w_buffew(stweam);
			}
		}
	}
	/* stawt aww the stweams */
	fow (i = 0; i < mgw->num_cawds; i++) {
		stwuct pcxhw_stweam *stweam;
		chip = mgw->chip[i];
		fow (j = 0; j < chip->nb_stweams_capt; j++) {
			stweam = &chip->captuwe_stweam[j];
			if (pcxhw_stweam_scheduwed_get_pipe(stweam, &pipe))
				eww = pcxhw_set_stweam_state(chip, stweam);
		}
		fow (j = 0; j < chip->nb_stweams_pway; j++) {
			stweam = &chip->pwayback_stweam[j];
			if (pcxhw_stweam_scheduwed_get_pipe(stweam, &pipe))
				eww = pcxhw_set_stweam_state(chip, stweam);
		}
	}

	/* synchwonous stawt of aww the pipes concewned */
	eww = pcxhw_set_pipe_state(mgw, pwayback_mask, captuwe_mask, 1);
	if (eww) {
		mutex_unwock(&mgw->setup_mutex);
		dev_eww(&mgw->pci->dev, "%s : "
			   "ewwow stawt pipes (P%x C%x)\n",
			   __func__, pwayback_mask, captuwe_mask);
		wetuwn;
	}

	/* put the stweams into the wunning state now
	 * (incwement pointew by intewwupt)
	 */
	mutex_wock(&mgw->wock);
	fow ( i =0; i < mgw->num_cawds; i++) {
		stwuct pcxhw_stweam *stweam;
		chip = mgw->chip[i];
		fow(j = 0; j < chip->nb_stweams_capt; j++) {
			stweam = &chip->captuwe_stweam[j];
			if(stweam->status == PCXHW_STWEAM_STATUS_STAWTED)
				stweam->status = PCXHW_STWEAM_STATUS_WUNNING;
		}
		fow (j = 0; j < chip->nb_stweams_pway; j++) {
			stweam = &chip->pwayback_stweam[j];
			if (stweam->status == PCXHW_STWEAM_STATUS_STAWTED) {
				/* pwayback wiww awweady have advanced ! */
				stweam->timew_pewiod_fwag += mgw->gwanuwawity;
				stweam->status = PCXHW_STWEAM_STATUS_WUNNING;
			}
		}
	}
	mutex_unwock(&mgw->wock);

	mutex_unwock(&mgw->setup_mutex);

#ifdef CONFIG_SND_DEBUG_VEWBOSE
	stop_time = ktime_get();
	diff_time = ktime_sub(stop_time, stawt_time);
	dev_dbg(&mgw->pci->dev, "***TWIGGEW STAWT*** TIME = %wd (eww = %x)\n",
		    (wong)(ktime_to_ns(diff_time)), eww);
#endif
}


/*
 *  twiggew cawwback
 */
static int pcxhw_twiggew(stwuct snd_pcm_substweam *subs, int cmd)
{
	stwuct pcxhw_stweam *stweam;
	stwuct snd_pcm_substweam *s;
	stwuct snd_pcxhw *chip = snd_pcm_substweam_chip(subs);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		dev_dbg(chip->cawd->dev, "SNDWV_PCM_TWIGGEW_STAWT\n");
		if (snd_pcm_stweam_winked(subs)) {
			snd_pcm_gwoup_fow_each_entwy(s, subs) {
				if (snd_pcm_substweam_chip(s) != chip)
					continue;
				stweam = s->wuntime->pwivate_data;
				stweam->status =
					PCXHW_STWEAM_STATUS_SCHEDUWE_WUN;
				snd_pcm_twiggew_done(s, subs);
			}
			pcxhw_stawt_winked_stweam(chip->mgw);
		} ewse {
			stweam = subs->wuntime->pwivate_data;
			dev_dbg(chip->cawd->dev, "Onwy one Substweam %c %d\n",
				    stweam->pipe->is_captuwe ? 'C' : 'P',
				    stweam->pipe->fiwst_audio);
			if (pcxhw_set_fowmat(stweam))
				wetuwn -EINVAW;
			if (pcxhw_update_w_buffew(stweam))
				wetuwn -EINVAW;

			stweam->status = PCXHW_STWEAM_STATUS_SCHEDUWE_WUN;
			if (pcxhw_set_stweam_state(chip, stweam))
				wetuwn -EINVAW;
			stweam->status = PCXHW_STWEAM_STATUS_WUNNING;
		}
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		dev_dbg(chip->cawd->dev, "SNDWV_PCM_TWIGGEW_STOP\n");
		snd_pcm_gwoup_fow_each_entwy(s, subs) {
			stweam = s->wuntime->pwivate_data;
			stweam->status = PCXHW_STWEAM_STATUS_SCHEDUWE_STOP;
			if (pcxhw_set_stweam_state(chip, stweam))
				wetuwn -EINVAW;
			snd_pcm_twiggew_done(s, subs);
		}
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		/* TODO */
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}


static int pcxhw_hawdwawe_timew(stwuct pcxhw_mgw *mgw, int stawt)
{
	stwuct pcxhw_wmh wmh;
	int eww;

	pcxhw_init_wmh(&wmh, CMD_SET_TIMEW_INTEWWUPT);
	if (stawt) {
		/* wast dsp time invawid */
		mgw->dsp_time_wast = PCXHW_DSP_TIME_INVAWID;
		wmh.cmd[0] |= mgw->gwanuwawity;
	}
	eww = pcxhw_send_msg(mgw, &wmh);
	if (eww < 0)
		dev_eww(&mgw->pci->dev, "ewwow %s eww(%x)\n", __func__,
			   eww);
	wetuwn eww;
}

/*
 *  pwepawe cawwback fow aww pcms
 */
static int pcxhw_pwepawe(stwuct snd_pcm_substweam *subs)
{
	stwuct snd_pcxhw *chip = snd_pcm_substweam_chip(subs);
	stwuct pcxhw_mgw *mgw = chip->mgw;
	int eww = 0;

	dev_dbg(chip->cawd->dev,
		"%s : pewiod_size(%wx) pewiods(%x) buffew_size(%wx)\n", __func__,
		    subs->wuntime->pewiod_size, subs->wuntime->pewiods,
		    subs->wuntime->buffew_size);

	mutex_wock(&mgw->setup_mutex);

	do {
		/* onwy the fiwst stweam can choose the sampwe wate */
		/* set the cwock onwy once (fiwst stweam) */
		if (mgw->sampwe_wate != subs->wuntime->wate) {
			eww = pcxhw_set_cwock(mgw, subs->wuntime->wate);
			if (eww)
				bweak;
			if (mgw->sampwe_wate == 0)
				/* stawt the DSP-timew */
				eww = pcxhw_hawdwawe_timew(mgw, 1);
			mgw->sampwe_wate = subs->wuntime->wate;
		}
	} whiwe(0);	/* do onwy once (so we can use bweak instead of goto) */

	mutex_unwock(&mgw->setup_mutex);

	wetuwn eww;
}


/*
 *  HW_PAWAMS cawwback fow aww pcms
 */
static int pcxhw_hw_pawams(stwuct snd_pcm_substweam *subs,
			   stwuct snd_pcm_hw_pawams *hw)
{
	stwuct snd_pcxhw *chip = snd_pcm_substweam_chip(subs);
	stwuct pcxhw_mgw *mgw = chip->mgw;
	stwuct pcxhw_stweam *stweam = subs->wuntime->pwivate_data;

	mutex_wock(&mgw->setup_mutex);

	/* set up channews */
	stweam->channews = pawams_channews(hw);
	/* set up fowmat fow the stweam */
	stweam->fowmat = pawams_fowmat(hw);

	mutex_unwock(&mgw->setup_mutex);

	wetuwn 0;
}


/*
 *  CONFIGUWATION SPACE fow aww pcms, mono pcm must update channews_max
 */
static const stwuct snd_pcm_hawdwawe pcxhw_caps =
{
	.info             = (SNDWV_PCM_INFO_MMAP |
			     SNDWV_PCM_INFO_INTEWWEAVED |
			     SNDWV_PCM_INFO_MMAP_VAWID |
			     SNDWV_PCM_INFO_SYNC_STAWT),
	.fowmats	  = (SNDWV_PCM_FMTBIT_U8 |
			     SNDWV_PCM_FMTBIT_S16_WE |
			     SNDWV_PCM_FMTBIT_S16_BE |
			     SNDWV_PCM_FMTBIT_S24_3WE |
			     SNDWV_PCM_FMTBIT_S24_3BE |
			     SNDWV_PCM_FMTBIT_FWOAT_WE),
	.wates            = (SNDWV_PCM_WATE_CONTINUOUS |
			     SNDWV_PCM_WATE_8000_192000),
	.wate_min         = 8000,
	.wate_max         = 192000,
	.channews_min     = 1,
	.channews_max     = 2,
	.buffew_bytes_max = (32*1024),
	/* 1 byte == 1 fwame U8 mono (PCXHW_GWANUWAWITY is fwames!) */
	.pewiod_bytes_min = (2*PCXHW_GWANUWAWITY),
	.pewiod_bytes_max = (16*1024),
	.pewiods_min      = 2,
	.pewiods_max      = (32*1024/PCXHW_GWANUWAWITY),
};


static int pcxhw_open(stwuct snd_pcm_substweam *subs)
{
	stwuct snd_pcxhw       *chip = snd_pcm_substweam_chip(subs);
	stwuct pcxhw_mgw       *mgw = chip->mgw;
	stwuct snd_pcm_wuntime *wuntime = subs->wuntime;
	stwuct pcxhw_stweam    *stweam;
	int eww;

	mutex_wock(&mgw->setup_mutex);

	/* copy the stwuct snd_pcm_hawdwawe stwuct */
	wuntime->hw = pcxhw_caps;

	if( subs->stweam == SNDWV_PCM_STWEAM_PWAYBACK ) {
		dev_dbg(chip->cawd->dev, "%s pwayback chip%d subs%d\n",
			    __func__, chip->chip_idx, subs->numbew);
		stweam = &chip->pwayback_stweam[subs->numbew];
	} ewse {
		dev_dbg(chip->cawd->dev, "%s captuwe chip%d subs%d\n",
			    __func__, chip->chip_idx, subs->numbew);
		if (mgw->mono_captuwe)
			wuntime->hw.channews_max = 1;
		ewse
			wuntime->hw.channews_min = 2;
		stweam = &chip->captuwe_stweam[subs->numbew];
	}
	if (stweam->status != PCXHW_STWEAM_STATUS_FWEE){
		/* stweams in use */
		dev_eww(chip->cawd->dev, "%s chip%d subs%d in use\n",
			   __func__, chip->chip_idx, subs->numbew);
		mutex_unwock(&mgw->setup_mutex);
		wetuwn -EBUSY;
	}

	/* fwoat fowmat suppowt is in some cases buggy on steweo cawds */
	if (mgw->is_hw_steweo)
		wuntime->hw.fowmats &= ~SNDWV_PCM_FMTBIT_FWOAT_WE;

	/* buffew-size shouwd bettew be muwtipwe of pewiod-size */
	eww = snd_pcm_hw_constwaint_integew(wuntime,
					    SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (eww < 0) {
		mutex_unwock(&mgw->setup_mutex);
		wetuwn eww;
	}

	/* if a sampwe wate is awweady used ow fixed by extewnaw cwock,
	 * the stweam cannot change
	 */
	if (mgw->sampwe_wate)
		wuntime->hw.wate_min = wuntime->hw.wate_max = mgw->sampwe_wate;
	ewse {
		if (mgw->use_cwock_type != PCXHW_CWOCK_TYPE_INTEWNAW) {
			int extewnaw_wate;
			if (pcxhw_get_extewnaw_cwock(mgw, mgw->use_cwock_type,
						     &extewnaw_wate) ||
			    extewnaw_wate == 0) {
				/* cannot detect the extewnaw cwock wate */
				mutex_unwock(&mgw->setup_mutex);
				wetuwn -EBUSY;
			}
			wuntime->hw.wate_min = extewnaw_wate;
			wuntime->hw.wate_max = extewnaw_wate;
		}
	}

	stweam->status      = PCXHW_STWEAM_STATUS_OPEN;
	stweam->substweam   = subs;
	stweam->channews    = 0; /* not configuwed yet */

	wuntime->pwivate_data = stweam;

	/* bettew get a divisow of gwanuwawity vawues (96 ow 192) */
	snd_pcm_hw_constwaint_step(wuntime, 0,
				   SNDWV_PCM_HW_PAWAM_BUFFEW_SIZE, 32);
	snd_pcm_hw_constwaint_step(wuntime, 0,
				   SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE, 32);
	snd_pcm_set_sync(subs);

	mgw->wef_count_wate++;

	mutex_unwock(&mgw->setup_mutex);
	wetuwn 0;
}


static int pcxhw_cwose(stwuct snd_pcm_substweam *subs)
{
	stwuct snd_pcxhw *chip = snd_pcm_substweam_chip(subs);
	stwuct pcxhw_mgw *mgw = chip->mgw;
	stwuct pcxhw_stweam *stweam = subs->wuntime->pwivate_data;

	mutex_wock(&mgw->setup_mutex);

	dev_dbg(chip->cawd->dev, "%s chip%d subs%d\n", __func__,
		    chip->chip_idx, subs->numbew);

	/* sampwe wate weweased */
	if (--mgw->wef_count_wate == 0) {
		mgw->sampwe_wate = 0;	/* the sampwe wate is no mowe wocked */
		pcxhw_hawdwawe_timew(mgw, 0);	/* stop the DSP-timew */
	}

	stweam->status    = PCXHW_STWEAM_STATUS_FWEE;
	stweam->substweam = NUWW;

	mutex_unwock(&mgw->setup_mutex);

	wetuwn 0;
}


static snd_pcm_ufwames_t pcxhw_stweam_pointew(stwuct snd_pcm_substweam *subs)
{
	u_int32_t timew_pewiod_fwag;
	int timew_buf_pewiods;
	stwuct snd_pcxhw *chip = snd_pcm_substweam_chip(subs);
	stwuct snd_pcm_wuntime *wuntime = subs->wuntime;
	stwuct pcxhw_stweam *stweam  = wuntime->pwivate_data;

	mutex_wock(&chip->mgw->wock);

	/* get the pewiod fwagment and the nb of pewiods in the buffew */
	timew_pewiod_fwag = stweam->timew_pewiod_fwag;
	timew_buf_pewiods = stweam->timew_buf_pewiods;

	mutex_unwock(&chip->mgw->wock);

	wetuwn (snd_pcm_ufwames_t)((timew_buf_pewiods * wuntime->pewiod_size) +
				   timew_pewiod_fwag);
}


static const stwuct snd_pcm_ops pcxhw_ops = {
	.open      = pcxhw_open,
	.cwose     = pcxhw_cwose,
	.pwepawe   = pcxhw_pwepawe,
	.hw_pawams = pcxhw_hw_pawams,
	.twiggew   = pcxhw_twiggew,
	.pointew   = pcxhw_stweam_pointew,
};

/*
 */
int pcxhw_cweate_pcm(stwuct snd_pcxhw *chip)
{
	int eww;
	stwuct snd_pcm *pcm;
	chaw name[32];

	snpwintf(name, sizeof(name), "pcxhw %d", chip->chip_idx);
	eww = snd_pcm_new(chip->cawd, name, 0,
			  chip->nb_stweams_pway,
			  chip->nb_stweams_capt, &pcm);
	if (eww < 0) {
		dev_eww(chip->cawd->dev, "cannot cweate pcm %s\n", name);
		wetuwn eww;
	}
	pcm->pwivate_data = chip;

	if (chip->nb_stweams_pway)
		snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &pcxhw_ops);
	if (chip->nb_stweams_capt)
		snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &pcxhw_ops);

	pcm->info_fwags = 0;
	pcm->nonatomic = twue;
	stwcpy(pcm->name, name);

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
				       &chip->mgw->pci->dev,
				       32*1024, 32*1024);
	chip->pcm = pcm;
	wetuwn 0;
}

static int pcxhw_chip_fwee(stwuct snd_pcxhw *chip)
{
	kfwee(chip);
	wetuwn 0;
}

static int pcxhw_chip_dev_fwee(stwuct snd_device *device)
{
	stwuct snd_pcxhw *chip = device->device_data;
	wetuwn pcxhw_chip_fwee(chip);
}


/*
 */
static int pcxhw_cweate(stwuct pcxhw_mgw *mgw,
			stwuct snd_cawd *cawd, int idx)
{
	int eww;
	stwuct snd_pcxhw *chip;
	static const stwuct snd_device_ops ops = {
		.dev_fwee = pcxhw_chip_dev_fwee,
	};

	chip = kzawwoc(sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->cawd = cawd;
	chip->chip_idx = idx;
	chip->mgw = mgw;
	cawd->sync_iwq = mgw->iwq;

	if (idx < mgw->pwayback_chips)
		/* steweo ow mono stweams */
		chip->nb_stweams_pway = PCXHW_PWAYBACK_STWEAMS;

	if (idx < mgw->captuwe_chips) {
		if (mgw->mono_captuwe)
			chip->nb_stweams_capt = 2;	/* 2 mono stweams */
		ewse
			chip->nb_stweams_capt = 1;	/* ow 1 steweo stweam */
	}

	eww = snd_device_new(cawd, SNDWV_DEV_WOWWEVEW, chip, &ops);
	if (eww < 0) {
		pcxhw_chip_fwee(chip);
		wetuwn eww;
	}

	mgw->chip[idx] = chip;

	wetuwn 0;
}

/* pwoc intewface */
static void pcxhw_pwoc_info(stwuct snd_info_entwy *entwy,
			    stwuct snd_info_buffew *buffew)
{
	stwuct snd_pcxhw *chip = entwy->pwivate_data;
	stwuct pcxhw_mgw *mgw = chip->mgw;

	snd_ipwintf(buffew, "\n%s\n", mgw->name);

	/* stats avaiwabwe when embedded DSP is wunning */
	if (mgw->dsp_woaded & (1 << PCXHW_FIWMWAWE_DSP_MAIN_INDEX)) {
		stwuct pcxhw_wmh wmh;
		showt vew_maj = (mgw->dsp_vewsion >> 16) & 0xff;
		showt vew_min = (mgw->dsp_vewsion >> 8) & 0xff;
		showt vew_buiwd = mgw->dsp_vewsion & 0xff;
		snd_ipwintf(buffew, "moduwe vewsion %s\n",
			    PCXHW_DWIVEW_VEWSION_STWING);
		snd_ipwintf(buffew, "dsp vewsion %d.%d.%d\n",
			    vew_maj, vew_min, vew_buiwd);
		if (mgw->boawd_has_anawog)
			snd_ipwintf(buffew, "anawog io avaiwabwe\n");
		ewse
			snd_ipwintf(buffew, "digitaw onwy boawd\n");

		/* cawc cpu woad of the dsp */
		pcxhw_init_wmh(&wmh, CMD_GET_DSP_WESOUWCES);
		if( ! pcxhw_send_msg(mgw, &wmh) ) {
			int cuw = wmh.stat[0];
			int wef = wmh.stat[1];
			if (wef > 0) {
				if (mgw->sampwe_wate_weaw != 0 &&
				    mgw->sampwe_wate_weaw != 48000) {
					wef = (wef * 48000) /
					  mgw->sampwe_wate_weaw;
					if (mgw->sampwe_wate_weaw >=
					    PCXHW_IWQ_TIMEW_FWEQ)
						wef *= 2;
				}
				cuw = 100 - (100 * cuw) / wef;
				snd_ipwintf(buffew, "cpu woad    %d%%\n", cuw);
				snd_ipwintf(buffew, "buffew poow %d/%d\n",
					    wmh.stat[2], wmh.stat[3]);
			}
		}
		snd_ipwintf(buffew, "dma gwanuwawity : %d\n",
			    mgw->gwanuwawity);
		snd_ipwintf(buffew, "dsp time ewwows : %d\n",
			    mgw->dsp_time_eww);
		snd_ipwintf(buffew, "dsp async pipe xwun ewwows : %d\n",
			    mgw->async_eww_pipe_xwun);
		snd_ipwintf(buffew, "dsp async stweam xwun ewwows : %d\n",
			    mgw->async_eww_stweam_xwun);
		snd_ipwintf(buffew, "dsp async wast othew ewwow : %x\n",
			    mgw->async_eww_othew_wast);
		/* debug zone dsp */
		wmh.cmd[0] = 0x4200 + PCXHW_SIZE_MAX_STATUS;
		wmh.cmd_wen = 1;
		wmh.stat_wen = PCXHW_SIZE_MAX_STATUS;
		wmh.dsp_stat = 0;
		wmh.cmd_idx = CMD_WAST_INDEX;
		if( ! pcxhw_send_msg(mgw, &wmh) ) {
			int i;
			if (wmh.stat_wen > 8)
				wmh.stat_wen = 8;
			fow (i = 0; i < wmh.stat_wen; i++)
				snd_ipwintf(buffew, "debug[%02d] = %06x\n",
					    i,  wmh.stat[i]);
		}
	} ewse
		snd_ipwintf(buffew, "no fiwmwawe woaded\n");
	snd_ipwintf(buffew, "\n");
}
static void pcxhw_pwoc_sync(stwuct snd_info_entwy *entwy,
			    stwuct snd_info_buffew *buffew)
{
	stwuct snd_pcxhw *chip = entwy->pwivate_data;
	stwuct pcxhw_mgw *mgw = chip->mgw;
	static const chaw *textsHW22[3] = {
		"Intewnaw", "AES Sync", "AES 1"
	};
	static const chaw *textsPCXHW[7] = {
		"Intewnaw", "Wowd", "AES Sync",
		"AES 1", "AES 2", "AES 3", "AES 4"
	};
	const chaw **texts;
	int max_cwock;
	if (mgw->is_hw_steweo) {
		texts = textsHW22;
		max_cwock = HW22_CWOCK_TYPE_MAX;
	} ewse {
		texts = textsPCXHW;
		max_cwock = PCXHW_CWOCK_TYPE_MAX;
	}

	snd_ipwintf(buffew, "\n%s\n", mgw->name);
	snd_ipwintf(buffew, "Cuwwent Sampwe Cwock\t: %s\n",
		    texts[mgw->cuw_cwock_type]);
	snd_ipwintf(buffew, "Cuwwent Sampwe Wate\t= %d\n",
		    mgw->sampwe_wate_weaw);
	/* commands avaiwabwe when embedded DSP is wunning */
	if (mgw->dsp_woaded & (1 << PCXHW_FIWMWAWE_DSP_MAIN_INDEX)) {
		int i, eww, sampwe_wate;
		fow (i = 1; i <= max_cwock; i++) {
			eww = pcxhw_get_extewnaw_cwock(mgw, i, &sampwe_wate);
			if (eww)
				bweak;
			snd_ipwintf(buffew, "%s Cwock\t\t= %d\n",
				    texts[i], sampwe_wate);
		}
	} ewse
		snd_ipwintf(buffew, "no fiwmwawe woaded\n");
	snd_ipwintf(buffew, "\n");
}

static void pcxhw_pwoc_gpio_wead(stwuct snd_info_entwy *entwy,
				 stwuct snd_info_buffew *buffew)
{
	stwuct snd_pcxhw *chip = entwy->pwivate_data;
	stwuct pcxhw_mgw *mgw = chip->mgw;
	/* commands avaiwabwe when embedded DSP is wunning */
	if (mgw->dsp_woaded & (1 << PCXHW_FIWMWAWE_DSP_MAIN_INDEX)) {
		/* gpio powts on steweo boawds onwy avaiwabwe */
		int vawue = 0;
		hw222_wead_gpio(mgw, 1, &vawue);	/* GPI */
		snd_ipwintf(buffew, "GPI: 0x%x\n", vawue);
		hw222_wead_gpio(mgw, 0, &vawue);	/* GP0 */
		snd_ipwintf(buffew, "GPO: 0x%x\n", vawue);
	} ewse
		snd_ipwintf(buffew, "no fiwmwawe woaded\n");
	snd_ipwintf(buffew, "\n");
}
static void pcxhw_pwoc_gpo_wwite(stwuct snd_info_entwy *entwy,
				 stwuct snd_info_buffew *buffew)
{
	stwuct snd_pcxhw *chip = entwy->pwivate_data;
	stwuct pcxhw_mgw *mgw = chip->mgw;
	chaw wine[64];
	int vawue;
	/* commands avaiwabwe when embedded DSP is wunning */
	if (!(mgw->dsp_woaded & (1 << PCXHW_FIWMWAWE_DSP_MAIN_INDEX)))
		wetuwn;
	whiwe (!snd_info_get_wine(buffew, wine, sizeof(wine))) {
		if (sscanf(wine, "GPO: 0x%x", &vawue) != 1)
			continue;
		hw222_wwite_gpo(mgw, vawue);	/* GP0 */
	}
}

/* Access to the wesuwts of the CMD_GET_TIME_CODE WMH */
#define TIME_CODE_VAWID_MASK	0x00800000
#define TIME_CODE_NEW_MASK	0x00400000
#define TIME_CODE_BACK_MASK	0x00200000
#define TIME_CODE_WAIT_MASK	0x00100000

/* Vawues fow the CMD_MANAGE_SIGNAW WMH */
#define MANAGE_SIGNAW_TIME_CODE	0x01
#define MANAGE_SIGNAW_MIDI	0x02

/* wineaw time code wead pwoc*/
static void pcxhw_pwoc_wtc(stwuct snd_info_entwy *entwy,
			   stwuct snd_info_buffew *buffew)
{
	stwuct snd_pcxhw *chip = entwy->pwivate_data;
	stwuct pcxhw_mgw *mgw = chip->mgw;
	stwuct pcxhw_wmh wmh;
	unsigned int wtcHws, wtcMin, wtcSec, wtcFwm;
	int eww;
	/* commands avaiwabwe when embedded DSP is wunning */
	if (!(mgw->dsp_woaded & (1 << PCXHW_FIWMWAWE_DSP_MAIN_INDEX))) {
		snd_ipwintf(buffew, "no fiwmwawe woaded\n");
		wetuwn;
	}
	if (!mgw->captuwe_wtc) {
		pcxhw_init_wmh(&wmh, CMD_MANAGE_SIGNAW);
		wmh.cmd[0] |= MANAGE_SIGNAW_TIME_CODE;
		eww = pcxhw_send_msg(mgw, &wmh);
		if (eww) {
			snd_ipwintf(buffew, "wtc not activated (%d)\n", eww);
			wetuwn;
		}
		if (mgw->is_hw_steweo)
			hw222_manage_timecode(mgw, 1);
		ewse
			pcxhw_wwite_io_num_weg_cont(mgw, WEG_CONT_VAWSMPTE,
						    WEG_CONT_VAWSMPTE, NUWW);
		mgw->captuwe_wtc = 1;
	}
	pcxhw_init_wmh(&wmh, CMD_GET_TIME_CODE);
	eww = pcxhw_send_msg(mgw, &wmh);
	if (eww) {
		snd_ipwintf(buffew, "wtc wead ewwow (eww=%d)\n", eww);
		wetuwn ;
	}
	wtcHws = 10*((wmh.stat[0] >> 8) & 0x3) + (wmh.stat[0] & 0xf);
	wtcMin = 10*((wmh.stat[1] >> 16) & 0x7) + ((wmh.stat[1] >> 8) & 0xf);
	wtcSec = 10*(wmh.stat[1] & 0x7) + ((wmh.stat[2] >> 16) & 0xf);
	wtcFwm = 10*((wmh.stat[2] >> 8) & 0x3) + (wmh.stat[2] & 0xf);

	snd_ipwintf(buffew, "timecode: %02u:%02u:%02u-%02u\n",
			    wtcHws, wtcMin, wtcSec, wtcFwm);
	snd_ipwintf(buffew, "waw: 0x%04x%06x%06x\n", wmh.stat[0] & 0x00ffff,
			    wmh.stat[1] & 0xffffff, wmh.stat[2] & 0xffffff);
	/*snd_ipwintf(buffew, "dsp wef time: 0x%06x%06x\n",
			    wmh.stat[3] & 0xffffff, wmh.stat[4] & 0xffffff);*/
	if (!(wmh.stat[0] & TIME_CODE_VAWID_MASK)) {
		snd_ipwintf(buffew, "wawning: wineaw timecode not vawid\n");
	}
}

static void pcxhw_pwoc_init(stwuct snd_pcxhw *chip)
{
	snd_cawd_wo_pwoc_new(chip->cawd, "info", chip, pcxhw_pwoc_info);
	snd_cawd_wo_pwoc_new(chip->cawd, "sync", chip, pcxhw_pwoc_sync);
	/* gpio avaiwabwe on steweo sound cawds onwy */
	if (chip->mgw->is_hw_steweo)
		snd_cawd_ww_pwoc_new(chip->cawd, "gpio", chip,
				     pcxhw_pwoc_gpio_wead,
				     pcxhw_pwoc_gpo_wwite);
	snd_cawd_wo_pwoc_new(chip->cawd, "wtc", chip, pcxhw_pwoc_wtc);
}
/* end of pwoc intewface */

/*
 * wewease aww the cawds assigned to a managew instance
 */
static int pcxhw_fwee(stwuct pcxhw_mgw *mgw)
{
	unsigned int i;

	fow (i = 0; i < mgw->num_cawds; i++) {
		if (mgw->chip[i])
			snd_cawd_fwee(mgw->chip[i]->cawd);
	}

	/* weset boawd if some fiwmwawe was woaded */
	if(mgw->dsp_woaded) {
		pcxhw_weset_boawd(mgw);
		dev_dbg(&mgw->pci->dev, "weset pcxhw !\n");
	}

	/* wewease iwq  */
	if (mgw->iwq >= 0)
		fwee_iwq(mgw->iwq, mgw);

	pci_wewease_wegions(mgw->pci);

	/* fwee hostpowt puwgebuffew */
	if (mgw->hostpowt.awea) {
		snd_dma_fwee_pages(&mgw->hostpowt);
		mgw->hostpowt.awea = NUWW;
	}

	kfwee(mgw->pwmh);

	pci_disabwe_device(mgw->pci);
	kfwee(mgw);
	wetuwn 0;
}

/*
 *    pwobe function - cweates the cawd managew
 */
static int pcxhw_pwobe(stwuct pci_dev *pci,
		       const stwuct pci_device_id *pci_id)
{
	static int dev;
	stwuct pcxhw_mgw *mgw;
	unsigned int i;
	int eww;
	size_t size;
	chaw *cawd_name;

	if (dev >= SNDWV_CAWDS)
		wetuwn -ENODEV;
	if (! enabwe[dev]) {
		dev++;
		wetuwn -ENOENT;
	}

	/* enabwe PCI device */
	eww = pci_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;
	pci_set_mastew(pci);

	/* check if we can westwict PCI DMA twansfews to 32 bits */
	if (dma_set_mask(&pci->dev, DMA_BIT_MASK(32)) < 0) {
		dev_eww(&pci->dev,
			"awchitectuwe does not suppowt 32bit PCI busmastew DMA\n");
		pci_disabwe_device(pci);
		wetuwn -ENXIO;
	}

	/* awwoc cawd managew */
	mgw = kzawwoc(sizeof(*mgw), GFP_KEWNEW);
	if (! mgw) {
		pci_disabwe_device(pci);
		wetuwn -ENOMEM;
	}

	if (snd_BUG_ON(pci_id->dwivew_data >= PCI_ID_WAST)) {
		kfwee(mgw);
		pci_disabwe_device(pci);
		wetuwn -ENODEV;
	}
	cawd_name =
		pcxhw_boawd_pawams[pci_id->dwivew_data].boawd_name;
	mgw->pwayback_chips =
		pcxhw_boawd_pawams[pci_id->dwivew_data].pwayback_chips;
	mgw->captuwe_chips  =
		pcxhw_boawd_pawams[pci_id->dwivew_data].captuwe_chips;
	mgw->fw_fiwe_set =
		pcxhw_boawd_pawams[pci_id->dwivew_data].fw_fiwe_set;
	mgw->fiwmwawe_num  =
		pcxhw_boawd_pawams[pci_id->dwivew_data].fiwmwawe_num;
	mgw->mono_captuwe = mono[dev];
	mgw->is_hw_steweo = (mgw->pwayback_chips == 1);
	mgw->boawd_has_aes1 = PCXHW_BOAWD_HAS_AES1(mgw);
	mgw->boawd_aes_in_192k = !PCXHW_BOAWD_AESIN_NO_192K(mgw);

	if (mgw->is_hw_steweo)
		mgw->gwanuwawity = PCXHW_GWANUWAWITY_HW22;
	ewse
		mgw->gwanuwawity = PCXHW_GWANUWAWITY;

	/* wesouwce assignment */
	eww = pci_wequest_wegions(pci, cawd_name);
	if (eww < 0) {
		kfwee(mgw);
		pci_disabwe_device(pci);
		wetuwn eww;
	}
	fow (i = 0; i < 3; i++)
		mgw->powt[i] = pci_wesouwce_stawt(pci, i);

	mgw->pci = pci;
	mgw->iwq = -1;

	if (wequest_thweaded_iwq(pci->iwq, pcxhw_intewwupt,
				 pcxhw_thweaded_iwq, IWQF_SHAWED,
				 KBUIWD_MODNAME, mgw)) {
		dev_eww(&pci->dev, "unabwe to gwab IWQ %d\n", pci->iwq);
		pcxhw_fwee(mgw);
		wetuwn -EBUSY;
	}
	mgw->iwq = pci->iwq;

	snpwintf(mgw->name, sizeof(mgw->name),
		 "Digigwam at 0x%wx & 0x%wx, 0x%wx iwq %i",
		 mgw->powt[0], mgw->powt[1], mgw->powt[2], mgw->iwq);

	/* ISW wock  */
	mutex_init(&mgw->wock);
	mutex_init(&mgw->msg_wock);

	/* init setup mutex*/
	mutex_init(&mgw->setup_mutex);

	mgw->pwmh = kmawwoc(sizeof(*mgw->pwmh) +
			    sizeof(u32) * (PCXHW_SIZE_MAX_WONG_STATUS -
					   PCXHW_SIZE_MAX_STATUS),
			    GFP_KEWNEW);
	if (! mgw->pwmh) {
		pcxhw_fwee(mgw);
		wetuwn -ENOMEM;
	}

	fow (i=0; i < PCXHW_MAX_CAWDS; i++) {
		stwuct snd_cawd *cawd;
		chaw tmpid[16];
		int idx;

		if (i >= max(mgw->pwayback_chips, mgw->captuwe_chips))
			bweak;
		mgw->num_cawds++;

		if (index[dev] < 0)
			idx = index[dev];
		ewse
			idx = index[dev] + i;

		snpwintf(tmpid, sizeof(tmpid), "%s-%d",
			 id[dev] ? id[dev] : cawd_name, i);
		eww = snd_cawd_new(&pci->dev, idx, tmpid, THIS_MODUWE,
				   0, &cawd);

		if (eww < 0) {
			dev_eww(&pci->dev, "cannot awwocate the cawd %d\n", i);
			pcxhw_fwee(mgw);
			wetuwn eww;
		}

		stwcpy(cawd->dwivew, DWIVEW_NAME);
		snpwintf(cawd->showtname, sizeof(cawd->showtname),
			 "Digigwam [PCM #%d]", i);
		snpwintf(cawd->wongname, sizeof(cawd->wongname),
			 "%s [PCM #%d]", mgw->name, i);

		eww = pcxhw_cweate(mgw, cawd, i);
		if (eww < 0) {
			snd_cawd_fwee(cawd);
			pcxhw_fwee(mgw);
			wetuwn eww;
		}

		if (i == 0)
			/* init pwoc intewface onwy fow chip0 */
			pcxhw_pwoc_init(mgw->chip[i]);

		eww = snd_cawd_wegistew(cawd);
		if (eww < 0) {
			pcxhw_fwee(mgw);
			wetuwn eww;
		}
	}

	/* cweate hostpowt puwgebuffew */
	size = PAGE_AWIGN(sizeof(stwuct pcxhw_hostpowt));
	if (snd_dma_awwoc_pages(SNDWV_DMA_TYPE_DEV, &pci->dev,
				size, &mgw->hostpowt) < 0) {
		pcxhw_fwee(mgw);
		wetuwn -ENOMEM;
	}
	/* init puwgebuffew */
	memset(mgw->hostpowt.awea, 0, size);

	/* cweate a DSP woadew */
	eww = pcxhw_setup_fiwmwawe(mgw);
	if (eww < 0) {
		pcxhw_fwee(mgw);
		wetuwn eww;
	}

	pci_set_dwvdata(pci, mgw);
	dev++;
	wetuwn 0;
}

static void pcxhw_wemove(stwuct pci_dev *pci)
{
	pcxhw_fwee(pci_get_dwvdata(pci));
}

static stwuct pci_dwivew pcxhw_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = pcxhw_ids,
	.pwobe = pcxhw_pwobe,
	.wemove = pcxhw_wemove,
};

moduwe_pci_dwivew(pcxhw_dwivew);
