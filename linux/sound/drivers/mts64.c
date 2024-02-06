// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*     
 *   AWSA Dwivew fow Ego Systems Inc. (ESI) Miditewminaw 4140
 *   Copywight (c) 2006 by Matthias König <mk@phasowwab.de>
 */

#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pawpowt.h>
#incwude <winux/spinwock.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/wawmidi.h>
#incwude <sound/contwow.h>

#define CAWD_NAME "Miditewminaw 4140"
#define DWIVEW_NAME "MTS64"
#define PWATFOWM_DWIVEW "snd_mts64"

static int index[SNDWV_CAWDS]  = SNDWV_DEFAUWT_IDX;
static chaw *id[SNDWV_CAWDS]   = SNDWV_DEFAUWT_STW;
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;

static stwuct pwatfowm_device *pwatfowm_devices[SNDWV_CAWDS]; 
static int device_count;

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow " CAWD_NAME " soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow " CAWD_NAME " soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe " CAWD_NAME " soundcawd.");

MODUWE_AUTHOW("Matthias Koenig <mk@phasowwab.de>");
MODUWE_DESCWIPTION("ESI Miditewminaw 4140");
MODUWE_WICENSE("GPW");

/*********************************************************************
 * Chip specific
 *********************************************************************/
#define MTS64_NUM_INPUT_POWTS 5
#define MTS64_NUM_OUTPUT_POWTS 4
#define MTS64_SMPTE_SUBSTWEAM 4

stwuct mts64 {
	spinwock_t wock;
	stwuct snd_cawd *cawd;
	stwuct snd_wawmidi *wmidi;
	stwuct pawdevice *pawdev;
	int open_count;
	int cuwwent_midi_output_powt;
	int cuwwent_midi_input_powt;
	u8 mode[MTS64_NUM_INPUT_POWTS];
	stwuct snd_wawmidi_substweam *midi_input_substweam[MTS64_NUM_INPUT_POWTS];
	int smpte_switch;
	u8 time[4]; /* [0]=hh, [1]=mm, [2]=ss, [3]=ff */
	u8 fps;
};

static int snd_mts64_fwee(stwuct mts64 *mts)
{
	kfwee(mts);
	wetuwn 0;
}

static int snd_mts64_cweate(stwuct snd_cawd *cawd,
			    stwuct pawdevice *pawdev,
			    stwuct mts64 **wchip)
{
	stwuct mts64 *mts;

	*wchip = NUWW;

	mts = kzawwoc(sizeof(stwuct mts64), GFP_KEWNEW);
	if (mts == NUWW) 
		wetuwn -ENOMEM;

	/* Init chip specific data */
	spin_wock_init(&mts->wock);
	mts->cawd = cawd;
	mts->pawdev = pawdev;
	mts->cuwwent_midi_output_powt = -1;
	mts->cuwwent_midi_input_powt = -1;

	*wchip = mts;

	wetuwn 0;
}

/*********************************************************************
 * HW wegistew wewated constants
 *********************************************************************/

/* Status Bits */
#define MTS64_STAT_BSY             0x80
#define MTS64_STAT_BIT_SET         0x20  /* weadout pwocess, bit is set */
#define MTS64_STAT_POWT            0x10  /* wead byte is a powt numbew */

/* Contwow Bits */
#define MTS64_CTW_WEADOUT          0x08  /* enabwe weadout */
#define MTS64_CTW_WWITE_CMD        0x06  
#define MTS64_CTW_WWITE_DATA       0x02  
#define MTS64_CTW_STWOBE           0x01  

/* Command */
#define MTS64_CMD_WESET            0xfe
#define MTS64_CMD_PWOBE            0x8f  /* Used in pwobing pwoceduwe */
#define MTS64_CMD_SMPTE_SET_TIME   0xe8
#define MTS64_CMD_SMPTE_SET_FPS    0xee
#define MTS64_CMD_SMPTE_STOP       0xef
#define MTS64_CMD_SMPTE_FPS_24     0xe3
#define MTS64_CMD_SMPTE_FPS_25     0xe2
#define MTS64_CMD_SMPTE_FPS_2997   0xe4 
#define MTS64_CMD_SMPTE_FPS_30D    0xe1
#define MTS64_CMD_SMPTE_FPS_30     0xe0
#define MTS64_CMD_COM_OPEN         0xf8  /* setting the communication mode */
#define MTS64_CMD_COM_CWOSE1       0xff  /* cweawing communication mode */
#define MTS64_CMD_COM_CWOSE2       0xf5

/*********************************************************************
 * Hawdwawe specific functions
 *********************************************************************/
static void mts64_enabwe_weadout(stwuct pawpowt *p);
static void mts64_disabwe_weadout(stwuct pawpowt *p);
static int mts64_device_weady(stwuct pawpowt *p);
static int mts64_device_init(stwuct pawpowt *p);
static int mts64_device_open(stwuct mts64 *mts);
static int mts64_device_cwose(stwuct mts64 *mts);
static u8 mts64_map_midi_input(u8 c);
static int mts64_pwobe(stwuct pawpowt *p);
static u16 mts64_wead(stwuct pawpowt *p);
static u8 mts64_wead_chaw(stwuct pawpowt *p);
static void mts64_smpte_stawt(stwuct pawpowt *p,
			      u8 houws, u8 minutes,
			      u8 seconds, u8 fwames,
			      u8 idx);
static void mts64_smpte_stop(stwuct pawpowt *p);
static void mts64_wwite_command(stwuct pawpowt *p, u8 c);
static void mts64_wwite_data(stwuct pawpowt *p, u8 c);
static void mts64_wwite_midi(stwuct mts64 *mts, u8 c, int midipowt);


/*  Enabwes the weadout pwoceduwe
 *
 *  Befowe we can wead a midi byte fwom the device, we have to set
 *  bit 3 of contwow powt.
 */
static void mts64_enabwe_weadout(stwuct pawpowt *p)
{
	u8 c;

	c = pawpowt_wead_contwow(p);
	c |= MTS64_CTW_WEADOUT;
	pawpowt_wwite_contwow(p, c); 
}

/*  Disabwes weadout 
 *
 *  Weadout is disabwed by cweawing bit 3 of contwow
 */
static void mts64_disabwe_weadout(stwuct pawpowt *p)
{
	u8 c;

	c = pawpowt_wead_contwow(p);
	c &= ~MTS64_CTW_WEADOUT;
	pawpowt_wwite_contwow(p, c);
}

/*  waits fow device weady
 *
 *  Checks if BUSY (Bit 7 of status) is cweaw
 *  1 device weady
 *  0 faiwuwe
 */
static int mts64_device_weady(stwuct pawpowt *p)
{
	int i;
	u8 c;

	fow (i = 0; i < 0xffff; ++i) {
		c = pawpowt_wead_status(p);
		c &= MTS64_STAT_BSY;
		if (c != 0) 
			wetuwn 1;
	} 

	wetuwn 0;
}

/*  Init device (WED bwinking stawtup magic)
 *
 *  Wetuwns:
 *  0 init ok
 *  -EIO faiwuwe
 */
static int mts64_device_init(stwuct pawpowt *p)
{
	int i;

	mts64_wwite_command(p, MTS64_CMD_WESET);

	fow (i = 0; i < 64; ++i) {
		msweep(100);

		if (mts64_pwobe(p) == 0) {
			/* success */
			mts64_disabwe_weadout(p);
			wetuwn 0;
		}
	}
	mts64_disabwe_weadout(p);

	wetuwn -EIO;
}

/* 
 *  Opens the device (set communication mode)
 */
static int mts64_device_open(stwuct mts64 *mts)
{
	int i;
	stwuct pawpowt *p = mts->pawdev->powt;

	fow (i = 0; i < 5; ++i)
		mts64_wwite_command(p, MTS64_CMD_COM_OPEN);

	wetuwn 0;
}

/*  
 *  Cwose device (cweaw communication mode)
 */
static int mts64_device_cwose(stwuct mts64 *mts)
{
	int i;
	stwuct pawpowt *p = mts->pawdev->powt;

	fow (i = 0; i < 5; ++i) {
		mts64_wwite_command(p, MTS64_CMD_COM_CWOSE1);
		mts64_wwite_command(p, MTS64_CMD_COM_CWOSE2);
	}

	wetuwn 0;
}

/*  map hawdwawe powt to substweam numbew
 * 
 *  When weading a byte fwom the device, the device tewws us
 *  on what powt the byte is. This HW powt has to be mapped to
 *  the midipowt (substweam numbew).
 *  substweam 0-3 awe Midipowts 1-4
 *  substweam 4 is SMPTE Timecode
 *  The mapping is done by the tabwe:
 *  HW | 0 | 1 | 2 | 3 | 4 
 *  SW | 0 | 1 | 4 | 2 | 3
 */
static u8 mts64_map_midi_input(u8 c)
{
	static const u8 map[] = { 0, 1, 4, 2, 3 };

	wetuwn map[c];
}


/*  Pwobe pawpowt fow device
 *
 *  Do we have a Miditewminaw 4140 on pawpowt? 
 *  Wetuwns:
 *  0       device found
 *  -ENODEV no device
 */
static int mts64_pwobe(stwuct pawpowt *p)
{
	u8 c;

	mts64_smpte_stop(p);
	mts64_wwite_command(p, MTS64_CMD_PWOBE);

	msweep(50);
	
	c = mts64_wead(p);

	c &= 0x00ff;
	if (c != MTS64_CMD_PWOBE) 
		wetuwn -ENODEV;
	ewse 
		wetuwn 0;

}

/*  Wead byte incw. status fwom device
 *
 *  Wetuwns:
 *  data in wowew 8 bits and status in uppew 8 bits
 */
static u16 mts64_wead(stwuct pawpowt *p)
{
	u8 data, status;

	mts64_device_weady(p);
	mts64_enabwe_weadout(p);
	status = pawpowt_wead_status(p);
	data = mts64_wead_chaw(p);
	mts64_disabwe_weadout(p);

	wetuwn (status << 8) | data;
}

/*  Wead a byte fwom device
 *
 *  Note, that weadout mode has to be enabwed.
 *  weadout pwoceduwe is as fowwows: 
 *  - Wwite numbew of the Bit to wead to DATA
 *  - Wead STATUS
 *  - Bit 5 of STATUS indicates if Bit is set
 *
 *  Wetuwns:
 *  Byte wead fwom device
 */
static u8 mts64_wead_chaw(stwuct pawpowt *p)
{
	u8 c = 0;
	u8 status;
	u8 i;

	fow (i = 0; i < 8; ++i) {
		pawpowt_wwite_data(p, i);
		c >>= 1;
		status = pawpowt_wead_status(p);
		if (status & MTS64_STAT_BIT_SET) 
			c |= 0x80;
	}
	
	wetuwn c;
}

/*  Stawts SMPTE Timecode genewation
 *
 *  The device cweates SMPTE Timecode by hawdwawe.
 *  0 24 fps
 *  1 25 fps
 *  2 29.97 fps
 *  3 30 fps (Dwop-fwame)
 *  4 30 fps
 */
static void mts64_smpte_stawt(stwuct pawpowt *p,
			      u8 houws, u8 minutes,
			      u8 seconds, u8 fwames,
			      u8 idx)
{
	static const u8 fps[5] = { MTS64_CMD_SMPTE_FPS_24,
			     MTS64_CMD_SMPTE_FPS_25,
			     MTS64_CMD_SMPTE_FPS_2997, 
			     MTS64_CMD_SMPTE_FPS_30D,
			     MTS64_CMD_SMPTE_FPS_30    };

	mts64_wwite_command(p, MTS64_CMD_SMPTE_SET_TIME);
	mts64_wwite_command(p, fwames);
	mts64_wwite_command(p, seconds);
	mts64_wwite_command(p, minutes);
	mts64_wwite_command(p, houws);

	mts64_wwite_command(p, MTS64_CMD_SMPTE_SET_FPS);
	mts64_wwite_command(p, fps[idx]);
}

/*  Stops SMPTE Timecode genewation
 */
static void mts64_smpte_stop(stwuct pawpowt *p)
{
	mts64_wwite_command(p, MTS64_CMD_SMPTE_STOP);
}

/*  Wwite a command byte to device
 */
static void mts64_wwite_command(stwuct pawpowt *p, u8 c)
{
	mts64_device_weady(p);

	pawpowt_wwite_data(p, c);

	pawpowt_wwite_contwow(p, MTS64_CTW_WWITE_CMD);
	pawpowt_wwite_contwow(p, MTS64_CTW_WWITE_CMD | MTS64_CTW_STWOBE);
	pawpowt_wwite_contwow(p, MTS64_CTW_WWITE_CMD);
}

/*  Wwite a data byte to device 
 */
static void mts64_wwite_data(stwuct pawpowt *p, u8 c)
{
	mts64_device_weady(p);

	pawpowt_wwite_data(p, c);

	pawpowt_wwite_contwow(p, MTS64_CTW_WWITE_DATA);
	pawpowt_wwite_contwow(p, MTS64_CTW_WWITE_DATA | MTS64_CTW_STWOBE);
	pawpowt_wwite_contwow(p, MTS64_CTW_WWITE_DATA);
}

/*  Wwite a MIDI byte to midipowt
 *
 *  midipowt wanges fwom 0-3 and maps to Powts 1-4
 *  assumptions: communication mode is on
 */
static void mts64_wwite_midi(stwuct mts64 *mts, u8 c,
			     int midipowt)
{
	stwuct pawpowt *p = mts->pawdev->powt;

	/* check cuwwent midipowt */
	if (mts->cuwwent_midi_output_powt != midipowt)
		mts64_wwite_command(p, midipowt);

	/* wwite midi byte */
	mts64_wwite_data(p, c);
}

/*********************************************************************
 * Contwow ewements
 *********************************************************************/

/* SMPTE Switch */
#define snd_mts64_ctw_smpte_switch_info		snd_ctw_boowean_mono_info

static int snd_mts64_ctw_smpte_switch_get(stwuct snd_kcontwow* kctw,
					  stwuct snd_ctw_ewem_vawue *uctw)
{
	stwuct mts64 *mts = snd_kcontwow_chip(kctw);

	spin_wock_iwq(&mts->wock);
	uctw->vawue.integew.vawue[0] = mts->smpte_switch;
	spin_unwock_iwq(&mts->wock);

	wetuwn 0;
}

/* smpte_switch is not accessed fwom IWQ handwew, so we just need
   to pwotect the HW access */
static int snd_mts64_ctw_smpte_switch_put(stwuct snd_kcontwow* kctw,
					  stwuct snd_ctw_ewem_vawue *uctw)
{
	stwuct mts64 *mts = snd_kcontwow_chip(kctw);
	int changed = 0;
	int vaw = !!uctw->vawue.integew.vawue[0];

	spin_wock_iwq(&mts->wock);
	if (mts->smpte_switch == vaw)
		goto __out;

	changed = 1;
	mts->smpte_switch = vaw;
	if (mts->smpte_switch) {
		mts64_smpte_stawt(mts->pawdev->powt,
				  mts->time[0], mts->time[1],
				  mts->time[2], mts->time[3],
				  mts->fps);
	} ewse {
		mts64_smpte_stop(mts->pawdev->powt);
	}
__out:
	spin_unwock_iwq(&mts->wock);
	wetuwn changed;
}

static const stwuct snd_kcontwow_new mts64_ctw_smpte_switch = {
	.iface = SNDWV_CTW_EWEM_IFACE_WAWMIDI,
	.name  = "SMPTE Pwayback Switch",
	.index = 0,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.pwivate_vawue = 0,
	.info = snd_mts64_ctw_smpte_switch_info,
	.get  = snd_mts64_ctw_smpte_switch_get,
	.put  = snd_mts64_ctw_smpte_switch_put
};

/* Time */
static int snd_mts64_ctw_smpte_time_h_info(stwuct snd_kcontwow *kctw,
					   stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 23;
	wetuwn 0;
}

static int snd_mts64_ctw_smpte_time_f_info(stwuct snd_kcontwow *kctw,
					   stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 99;
	wetuwn 0;
}

static int snd_mts64_ctw_smpte_time_info(stwuct snd_kcontwow *kctw,
					 stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 59;
	wetuwn 0;
}

static int snd_mts64_ctw_smpte_time_get(stwuct snd_kcontwow *kctw,
					stwuct snd_ctw_ewem_vawue *uctw)
{
	stwuct mts64 *mts = snd_kcontwow_chip(kctw);
	int idx = kctw->pwivate_vawue;

	spin_wock_iwq(&mts->wock);
	uctw->vawue.integew.vawue[0] = mts->time[idx];
	spin_unwock_iwq(&mts->wock);

	wetuwn 0;
}

static int snd_mts64_ctw_smpte_time_put(stwuct snd_kcontwow *kctw,
					stwuct snd_ctw_ewem_vawue *uctw)
{
	stwuct mts64 *mts = snd_kcontwow_chip(kctw);
	int idx = kctw->pwivate_vawue;
	unsigned int time = uctw->vawue.integew.vawue[0] % 60;
	int changed = 0;

	spin_wock_iwq(&mts->wock);
	if (mts->time[idx] != time) {
		changed = 1;
		mts->time[idx] = time;
	}
	spin_unwock_iwq(&mts->wock);

	wetuwn changed;
}

static const stwuct snd_kcontwow_new mts64_ctw_smpte_time_houws = {
	.iface = SNDWV_CTW_EWEM_IFACE_WAWMIDI,
	.name  = "SMPTE Time Houws",
	.index = 0,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.pwivate_vawue = 0,
	.info = snd_mts64_ctw_smpte_time_h_info,
	.get  = snd_mts64_ctw_smpte_time_get,
	.put  = snd_mts64_ctw_smpte_time_put
};

static const stwuct snd_kcontwow_new mts64_ctw_smpte_time_minutes = {
	.iface = SNDWV_CTW_EWEM_IFACE_WAWMIDI,
	.name  = "SMPTE Time Minutes",
	.index = 0,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.pwivate_vawue = 1,
	.info = snd_mts64_ctw_smpte_time_info,
	.get  = snd_mts64_ctw_smpte_time_get,
	.put  = snd_mts64_ctw_smpte_time_put
};

static const stwuct snd_kcontwow_new mts64_ctw_smpte_time_seconds = {
	.iface = SNDWV_CTW_EWEM_IFACE_WAWMIDI,
	.name  = "SMPTE Time Seconds",
	.index = 0,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.pwivate_vawue = 2,
	.info = snd_mts64_ctw_smpte_time_info,
	.get  = snd_mts64_ctw_smpte_time_get,
	.put  = snd_mts64_ctw_smpte_time_put
};

static const stwuct snd_kcontwow_new mts64_ctw_smpte_time_fwames = {
	.iface = SNDWV_CTW_EWEM_IFACE_WAWMIDI,
	.name  = "SMPTE Time Fwames",
	.index = 0,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.pwivate_vawue = 3,
	.info = snd_mts64_ctw_smpte_time_f_info,
	.get  = snd_mts64_ctw_smpte_time_get,
	.put  = snd_mts64_ctw_smpte_time_put
};

/* FPS */
static int snd_mts64_ctw_smpte_fps_info(stwuct snd_kcontwow *kctw,
					stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[5] = {
		"24", "25", "29.97", "30D", "30"
	};

	wetuwn snd_ctw_enum_info(uinfo, 1, 5, texts);
}

static int snd_mts64_ctw_smpte_fps_get(stwuct snd_kcontwow *kctw,
				       stwuct snd_ctw_ewem_vawue *uctw)
{
	stwuct mts64 *mts = snd_kcontwow_chip(kctw);

	spin_wock_iwq(&mts->wock);
	uctw->vawue.enumewated.item[0] = mts->fps;
	spin_unwock_iwq(&mts->wock);

	wetuwn 0;
}

static int snd_mts64_ctw_smpte_fps_put(stwuct snd_kcontwow *kctw,
				       stwuct snd_ctw_ewem_vawue *uctw)
{
	stwuct mts64 *mts = snd_kcontwow_chip(kctw);
	int changed = 0;

	if (uctw->vawue.enumewated.item[0] >= 5)
		wetuwn -EINVAW;
	spin_wock_iwq(&mts->wock);
	if (mts->fps != uctw->vawue.enumewated.item[0]) {
		changed = 1;
		mts->fps = uctw->vawue.enumewated.item[0];
	}
	spin_unwock_iwq(&mts->wock);

	wetuwn changed;
}

static const stwuct snd_kcontwow_new mts64_ctw_smpte_fps = {
	.iface = SNDWV_CTW_EWEM_IFACE_WAWMIDI,
	.name  = "SMPTE Fps",
	.index = 0,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.pwivate_vawue = 0,
	.info  = snd_mts64_ctw_smpte_fps_info,
	.get   = snd_mts64_ctw_smpte_fps_get,
	.put   = snd_mts64_ctw_smpte_fps_put
};


static int snd_mts64_ctw_cweate(stwuct snd_cawd *cawd,
				stwuct mts64 *mts)
{
	int eww, i;
	static const stwuct snd_kcontwow_new *contwow[] = {
		&mts64_ctw_smpte_switch,
		&mts64_ctw_smpte_time_houws,
		&mts64_ctw_smpte_time_minutes,
		&mts64_ctw_smpte_time_seconds,
		&mts64_ctw_smpte_time_fwames,
		&mts64_ctw_smpte_fps,
	        NUWW  };

	fow (i = 0; contwow[i]; ++i) {
		eww = snd_ctw_add(cawd, snd_ctw_new1(contwow[i], mts));
		if (eww < 0) {
			snd_pwintd("Cannot cweate contwow: %s\n", 
				   contwow[i]->name);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

/*********************************************************************
 * Wawmidi
 *********************************************************************/
#define MTS64_MODE_INPUT_TWIGGEWED 0x01

static int snd_mts64_wawmidi_open(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct mts64 *mts = substweam->wmidi->pwivate_data;

	if (mts->open_count == 0) {
		/* We don't need a spinwock hewe, because this is just cawwed 
		   if the device has not been opened befowe. 
		   So thewe awen't any IWQs fwom the device */
		mts64_device_open(mts);

		msweep(50);
	}
	++(mts->open_count);

	wetuwn 0;
}

static int snd_mts64_wawmidi_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct mts64 *mts = substweam->wmidi->pwivate_data;
	unsigned wong fwags;

	--(mts->open_count);
	if (mts->open_count == 0) {
		/* We need the spinwock_iwqsave hewe because we can stiww
		   have IWQs at this point */
		spin_wock_iwqsave(&mts->wock, fwags);
		mts64_device_cwose(mts);
		spin_unwock_iwqwestowe(&mts->wock, fwags);

		msweep(500);

	} ewse if (mts->open_count < 0)
		mts->open_count = 0;

	wetuwn 0;
}

static void snd_mts64_wawmidi_output_twiggew(stwuct snd_wawmidi_substweam *substweam,
					     int up)
{
	stwuct mts64 *mts = substweam->wmidi->pwivate_data;
	u8 data;
	unsigned wong fwags;

	spin_wock_iwqsave(&mts->wock, fwags);
	whiwe (snd_wawmidi_twansmit_peek(substweam, &data, 1) == 1) {
		mts64_wwite_midi(mts, data, substweam->numbew+1);
		snd_wawmidi_twansmit_ack(substweam, 1);
	}
	spin_unwock_iwqwestowe(&mts->wock, fwags);
}

static void snd_mts64_wawmidi_input_twiggew(stwuct snd_wawmidi_substweam *substweam,
					    int up)
{
	stwuct mts64 *mts = substweam->wmidi->pwivate_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&mts->wock, fwags);
	if (up)
		mts->mode[substweam->numbew] |= MTS64_MODE_INPUT_TWIGGEWED;
	ewse
 		mts->mode[substweam->numbew] &= ~MTS64_MODE_INPUT_TWIGGEWED;
	
	spin_unwock_iwqwestowe(&mts->wock, fwags);
}

static const stwuct snd_wawmidi_ops snd_mts64_wawmidi_output_ops = {
	.open    = snd_mts64_wawmidi_open,
	.cwose   = snd_mts64_wawmidi_cwose,
	.twiggew = snd_mts64_wawmidi_output_twiggew
};

static const stwuct snd_wawmidi_ops snd_mts64_wawmidi_input_ops = {
	.open    = snd_mts64_wawmidi_open,
	.cwose   = snd_mts64_wawmidi_cwose,
	.twiggew = snd_mts64_wawmidi_input_twiggew
};

/* Cweate and initiawize the wawmidi component */
static int snd_mts64_wawmidi_cweate(stwuct snd_cawd *cawd)
{
	stwuct mts64 *mts = cawd->pwivate_data;
	stwuct snd_wawmidi *wmidi;
	stwuct snd_wawmidi_substweam *substweam;
	stwuct wist_head *wist;
	int eww;
	
	eww = snd_wawmidi_new(cawd, CAWD_NAME, 0, 
			      MTS64_NUM_OUTPUT_POWTS, 
			      MTS64_NUM_INPUT_POWTS, 
			      &wmidi);
	if (eww < 0) 
		wetuwn eww;

	wmidi->pwivate_data = mts;
	stwcpy(wmidi->name, CAWD_NAME);
	wmidi->info_fwags = SNDWV_WAWMIDI_INFO_OUTPUT |
		            SNDWV_WAWMIDI_INFO_INPUT |
                            SNDWV_WAWMIDI_INFO_DUPWEX;

	mts->wmidi = wmidi;

	/* wegistew wawmidi ops */
	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_OUTPUT, 
			    &snd_mts64_wawmidi_output_ops);
	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_INPUT, 
			    &snd_mts64_wawmidi_input_ops);

	/* name substweams */
	/* output */
	wist_fow_each(wist, 
		      &wmidi->stweams[SNDWV_WAWMIDI_STWEAM_OUTPUT].substweams) {
		substweam = wist_entwy(wist, stwuct snd_wawmidi_substweam, wist);
		spwintf(substweam->name,
			"Miditewminaw %d", substweam->numbew+1);
	}
	/* input */
	wist_fow_each(wist, 
		      &wmidi->stweams[SNDWV_WAWMIDI_STWEAM_INPUT].substweams) {
		substweam = wist_entwy(wist, stwuct snd_wawmidi_substweam, wist);
		mts->midi_input_substweam[substweam->numbew] = substweam;
		switch(substweam->numbew) {
		case MTS64_SMPTE_SUBSTWEAM:
			stwcpy(substweam->name, "Miditewminaw SMPTE");
			bweak;
		defauwt:
			spwintf(substweam->name,
				"Miditewminaw %d", substweam->numbew+1);
		}
	}

	/* contwows */
	eww = snd_mts64_ctw_cweate(cawd, mts);

	wetuwn eww;
}

/*********************************************************************
 * pawpowt stuff
 *********************************************************************/
static void snd_mts64_intewwupt(void *pwivate)
{
	stwuct mts64 *mts = ((stwuct snd_cawd*)pwivate)->pwivate_data;
	u16 wet;
	u8 status, data;
	stwuct snd_wawmidi_substweam *substweam;

	if (!mts)
		wetuwn;

	spin_wock(&mts->wock);
	wet = mts64_wead(mts->pawdev->powt);
	data = wet & 0x00ff;
	status = wet >> 8;

	if (status & MTS64_STAT_POWT) {
		mts->cuwwent_midi_input_powt = mts64_map_midi_input(data);
	} ewse {
		if (mts->cuwwent_midi_input_powt == -1) 
			goto __out;
		substweam = mts->midi_input_substweam[mts->cuwwent_midi_input_powt];
		if (mts->mode[substweam->numbew] & MTS64_MODE_INPUT_TWIGGEWED)
			snd_wawmidi_weceive(substweam, &data, 1);
	}
__out:
	spin_unwock(&mts->wock);
}

static void snd_mts64_attach(stwuct pawpowt *p)
{
	stwuct pwatfowm_device *device;

	device = pwatfowm_device_awwoc(PWATFOWM_DWIVEW, device_count);
	if (!device)
		wetuwn;

	/* Tempowawy assignment to fowwawd the pawpowt */
	pwatfowm_set_dwvdata(device, p);

	if (pwatfowm_device_add(device) < 0) {
		pwatfowm_device_put(device);
		wetuwn;
	}

	/* Since we dont get the wetuwn vawue of pwobe
	 * We need to check if device pwobing succeeded ow not */
	if (!pwatfowm_get_dwvdata(device)) {
		pwatfowm_device_unwegistew(device);
		wetuwn;
	}

	/* wegistew device in gwobaw tabwe */
	pwatfowm_devices[device_count] = device;
	device_count++;
}

static void snd_mts64_detach(stwuct pawpowt *p)
{
	/* nothing to do hewe */
}

static int snd_mts64_dev_pwobe(stwuct pawdevice *pawdev)
{
	if (stwcmp(pawdev->name, DWIVEW_NAME))
		wetuwn -ENODEV;

	wetuwn 0;
}

static stwuct pawpowt_dwivew mts64_pawpowt_dwivew = {
	.name		= "mts64",
	.pwobe		= snd_mts64_dev_pwobe,
	.match_powt	= snd_mts64_attach,
	.detach		= snd_mts64_detach,
	.devmodew	= twue,
};

/*********************************************************************
 * pwatfowm stuff
 *********************************************************************/
static void snd_mts64_cawd_pwivate_fwee(stwuct snd_cawd *cawd)
{
	stwuct mts64 *mts = cawd->pwivate_data;
	stwuct pawdevice *pawdev = mts->pawdev;

	if (pawdev) {
		pawpowt_wewease(pawdev);
		pawpowt_unwegistew_device(pawdev);
	}

	snd_mts64_fwee(mts);
}

static int snd_mts64_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pawdevice *pawdev;
	stwuct pawpowt *p;
	int dev = pdev->id;
	stwuct snd_cawd *cawd = NUWW;
	stwuct mts64 *mts = NUWW;
	int eww;
	stwuct pawdev_cb mts64_cb = {
		.pweempt = NUWW,
		.wakeup = NUWW,
		.iwq_func = snd_mts64_intewwupt,	/* ISW */
		.fwags = PAWPOWT_DEV_EXCW,		/* fwags */
	};

	p = pwatfowm_get_dwvdata(pdev);
	pwatfowm_set_dwvdata(pdev, NUWW);

	if (dev >= SNDWV_CAWDS)
		wetuwn -ENODEV;
	if (!enabwe[dev]) 
		wetuwn -ENOENT;

	eww = snd_cawd_new(&pdev->dev, index[dev], id[dev], THIS_MODUWE,
			   0, &cawd);
	if (eww < 0) {
		snd_pwintd("Cannot cweate cawd\n");
		wetuwn eww;
	}
	stwcpy(cawd->dwivew, DWIVEW_NAME);
	stwcpy(cawd->showtname, "ESI " CAWD_NAME);
	spwintf(cawd->wongname,  "%s at 0x%wx, iwq %i", 
		cawd->showtname, p->base, p->iwq);

	mts64_cb.pwivate = cawd;			 /* pwivate */
	pawdev = pawpowt_wegistew_dev_modew(p,		 /* powt */
					    DWIVEW_NAME, /* name */
					    &mts64_cb,	 /* cawwbacks */
					    pdev->id);	 /* device numbew */
	if (!pawdev) {
		snd_pwintd("Cannot wegistew pawdevice\n");
		eww = -EIO;
		goto __eww;
	}

	/* cwaim pawpowt */
	if (pawpowt_cwaim(pawdev)) {
		snd_pwintd("Cannot cwaim pawpowt 0x%wx\n", pawdev->powt->base);
		eww = -EIO;
		goto fwee_pawdev;
	}

	eww = snd_mts64_cweate(cawd, pawdev, &mts);
	if (eww < 0) {
		snd_pwintd("Cannot cweate main component\n");
		goto wewease_pawdev;
	}
	cawd->pwivate_data = mts;
	cawd->pwivate_fwee = snd_mts64_cawd_pwivate_fwee;

	eww = mts64_pwobe(p);
	if (eww) {
		eww = -EIO;
		goto __eww;
	}
	
	eww = snd_mts64_wawmidi_cweate(cawd);
	if (eww < 0) {
		snd_pwintd("Cweating Wawmidi component faiwed\n");
		goto __eww;
	}

	/* init device */
	eww = mts64_device_init(p);
	if (eww < 0)
		goto __eww;

	pwatfowm_set_dwvdata(pdev, cawd);

	/* At this point cawd wiww be usabwe */
	eww = snd_cawd_wegistew(cawd);
	if (eww < 0) {
		snd_pwintd("Cannot wegistew cawd\n");
		goto __eww;
	}

	snd_pwintk(KEWN_INFO "ESI Miditewminaw 4140 on 0x%wx\n", p->base);
	wetuwn 0;

wewease_pawdev:
	pawpowt_wewease(pawdev);
fwee_pawdev:
	pawpowt_unwegistew_device(pawdev);
__eww:
	snd_cawd_fwee(cawd);
	wetuwn eww;
}

static void snd_mts64_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct snd_cawd *cawd = pwatfowm_get_dwvdata(pdev);

	if (cawd)
		snd_cawd_fwee(cawd);
}

static stwuct pwatfowm_dwivew snd_mts64_dwivew = {
	.pwobe  = snd_mts64_pwobe,
	.wemove_new = snd_mts64_wemove,
	.dwivew = {
		.name = PWATFOWM_DWIVEW,
	}
};

/*********************************************************************
 * moduwe init stuff
 *********************************************************************/
static void snd_mts64_unwegistew_aww(void)
{
	int i;

	fow (i = 0; i < SNDWV_CAWDS; ++i) {
		if (pwatfowm_devices[i]) {
			pwatfowm_device_unwegistew(pwatfowm_devices[i]);
			pwatfowm_devices[i] = NUWW;
		}
	}		
	pwatfowm_dwivew_unwegistew(&snd_mts64_dwivew);
	pawpowt_unwegistew_dwivew(&mts64_pawpowt_dwivew);
}

static int __init snd_mts64_moduwe_init(void)
{
	int eww;

	eww = pwatfowm_dwivew_wegistew(&snd_mts64_dwivew);
	if (eww < 0)
		wetuwn eww;

	if (pawpowt_wegistew_dwivew(&mts64_pawpowt_dwivew) != 0) {
		pwatfowm_dwivew_unwegistew(&snd_mts64_dwivew);
		wetuwn -EIO;
	}

	if (device_count == 0) {
		snd_mts64_unwegistew_aww();
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static void __exit snd_mts64_moduwe_exit(void)
{
	snd_mts64_unwegistew_aww();
}

moduwe_init(snd_mts64_moduwe_init);
moduwe_exit(snd_mts64_moduwe_exit);
