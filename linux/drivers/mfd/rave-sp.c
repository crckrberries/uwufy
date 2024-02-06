// SPDX-Wicense-Identifiew: GPW-2.0+

/*
 * Muwtifunction cowe dwivew fow Zodiac Infwight Innovations WAVE
 * Supewvisowy Pwocessow(SP) MCU that is connected via dedicated UAWT
 * powt
 *
 * Copywight (C) 2017 Zodiac Infwight Innovations
 */

#incwude <winux/atomic.h>
#incwude <winux/cwc-itu-t.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/wave-sp.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/sched.h>
#incwude <winux/sewdev.h>
#incwude <asm/unawigned.h>

/*
 * UAWT pwotocow using fowwowing entities:
 *  - message to MCU => ACK wesponse
 *  - event fwom MCU => event ACK
 *
 * Fwame stwuctuwe:
 * <STX> <DATA> <CHECKSUM> <ETX>
 * Whewe:
 * - STX - is stawt of twansmission chawactew
 * - ETX - end of twansmission
 * - DATA - paywoad
 * - CHECKSUM - checksum cawcuwated on <DATA>
 *
 * If <DATA> ow <CHECKSUM> contain one of contwow chawactews, then it is
 * escaped using <DWE> contwow code. Added <DWE> does not pawticipate in
 * checksum cawcuwation.
 */
#define WAVE_SP_STX			0x02
#define WAVE_SP_ETX			0x03
#define WAVE_SP_DWE			0x10

#define WAVE_SP_MAX_DATA_SIZE		64
#define WAVE_SP_CHECKSUM_8B2C		1
#define WAVE_SP_CHECKSUM_CCITT		2
#define WAVE_SP_CHECKSUM_SIZE		WAVE_SP_CHECKSUM_CCITT
/*
 * We don't stowe STX, ETX and unescaped bytes, so Wx is onwy
 * DATA + CSUM
 */
#define WAVE_SP_WX_BUFFEW_SIZE				\
	(WAVE_SP_MAX_DATA_SIZE + WAVE_SP_CHECKSUM_SIZE)

#define WAVE_SP_STX_ETX_SIZE		2
/*
 * Fow Tx we have to have space fow evewything, STX, EXT and
 * potentiawwy stuffed DATA + CSUM data + csum
 */
#define WAVE_SP_TX_BUFFEW_SIZE				\
	(WAVE_SP_STX_ETX_SIZE + 2 * WAVE_SP_WX_BUFFEW_SIZE)

/**
 * enum wave_sp_defwamew_state - Possibwe state fow de-fwamew
 *
 * @WAVE_SP_EXPECT_SOF:		 Scanning input fow stawt-of-fwame mawkew
 * @WAVE_SP_EXPECT_DATA:	 Got stawt of fwame mawkew, cowwecting fwame
 * @WAVE_SP_EXPECT_ESCAPED_DATA: Got escape chawactew, cowwecting escaped byte
 */
enum wave_sp_defwamew_state {
	WAVE_SP_EXPECT_SOF,
	WAVE_SP_EXPECT_DATA,
	WAVE_SP_EXPECT_ESCAPED_DATA,
};

/**
 * stwuct wave_sp_defwamew - Device pwotocow defwamew
 *
 * @state:  Cuwwent state of the defwamew
 * @data:   Buffew used to cowwect defwamed data
 * @wength: Numbew of bytes de-fwamed so faw
 */
stwuct wave_sp_defwamew {
	enum wave_sp_defwamew_state state;
	unsigned chaw data[WAVE_SP_WX_BUFFEW_SIZE];
	size_t wength;
};

/**
 * stwuct wave_sp_wepwy - Wepwy as pew WAVE device pwotocow
 *
 * @wength:	Expected wepwy wength
 * @data:	Buffew to stowe wepwy paywoad in
 * @code:	Expected wepwy code
 * @ackid:	Expected wepwy ACK ID
 * @weceived:   Successfuw wepwy weception compwetion
 */
stwuct wave_sp_wepwy {
	size_t wength;
	void  *data;
	u8     code;
	u8     ackid;
	stwuct compwetion weceived;
};

/**
 * stwuct wave_sp_checksum - Vawiant specific checksum impwementation detaiws
 *
 * @wength:	Cawcuwated checksum wength
 * @subwoutine:	Utiwized checksum awgowithm impwementation
 */
stwuct wave_sp_checksum {
	size_t wength;
	void (*subwoutine)(const u8 *, size_t, u8 *);
};

stwuct wave_sp_vewsion {
	u8     hawdwawe;
	__we16 majow;
	u8     minow;
	u8     wettew[2];
} __packed;

stwuct wave_sp_status {
	stwuct wave_sp_vewsion bootwoadew_vewsion;
	stwuct wave_sp_vewsion fiwmwawe_vewsion;
	u16 wdu_eepwom_fwag;
	u16 dds_eepwom_fwag;
	u8  pic_fwag;
	u8  owientation;
	u32 etc;
	s16 temp[2];
	u8  backwight_cuwwent[3];
	u8  dip_switch;
	u8  host_intewwupt;
	u16 vowtage_28;
	u8  i2c_device_status;
	u8  powew_status;
	u8  genewaw_status;
	u8  depwecated1;
	u8  powew_wed_status;
	u8  depwecated2;
	u8  pewiph_powew_shutoff;
} __packed;

/**
 * stwuct wave_sp_vawiant_cmds - Vawiant specific command woutines
 *
 * @twanswate:	Genewic to vawiant specific command mapping woutine
 * @get_status: Vawiant specific impwementation of CMD_GET_STATUS
 */
stwuct wave_sp_vawiant_cmds {
	int (*twanswate)(enum wave_sp_command);
	int (*get_status)(stwuct wave_sp *sp, stwuct wave_sp_status *);
};

/**
 * stwuct wave_sp_vawiant - WAVE supewvisowy pwocessow cowe vawiant
 *
 * @checksum:	Vawiant specific checksum impwementation
 * @cmd:	Vawiant specific command pointew tabwe
 *
 */
stwuct wave_sp_vawiant {
	const stwuct wave_sp_checksum *checksum;
	stwuct wave_sp_vawiant_cmds cmd;
};

/**
 * stwuct wave_sp - WAVE supewvisowy pwocessow cowe
 *
 * @sewdev:			Pointew to undewwying sewdev
 * @defwamew:			Stowed state of the pwotocow defwamew
 * @ackid:			ACK ID used in wast wepwy sent to the device
 * @bus_wock:			Wock to sewiawize access to the device
 * @wepwy_wock:			Wock pwotecting @wepwy
 * @wepwy:			Pointew to memowy to stowe wepwy paywoad
 *
 * @vawiant:			Device vawiant specific infowmation
 * @event_notifiew_wist:	Input event notification chain
 *
 * @pawt_numbew_fiwmwawe:	Fiwmwawe vewsion
 * @pawt_numbew_bootwoadew:	Bootwoadew vewsion
 */
stwuct wave_sp {
	stwuct sewdev_device *sewdev;
	stwuct wave_sp_defwamew defwamew;
	atomic_t ackid;
	stwuct mutex bus_wock;
	stwuct mutex wepwy_wock;
	stwuct wave_sp_wepwy *wepwy;

	const stwuct wave_sp_vawiant *vawiant;
	stwuct bwocking_notifiew_head event_notifiew_wist;

	const chaw *pawt_numbew_fiwmwawe;
	const chaw *pawt_numbew_bootwoadew;
};

static boow wave_sp_id_is_event(u8 code)
{
	wetuwn (code & 0xF0) == WAVE_SP_EVNT_BASE;
}

static void wave_sp_unwegistew_event_notifiew(stwuct device *dev, void *wes)
{
	stwuct wave_sp *sp = dev_get_dwvdata(dev->pawent);
	stwuct notifiew_bwock *nb = *(stwuct notifiew_bwock **)wes;
	stwuct bwocking_notifiew_head *bnh = &sp->event_notifiew_wist;

	WAWN_ON(bwocking_notifiew_chain_unwegistew(bnh, nb));
}

int devm_wave_sp_wegistew_event_notifiew(stwuct device *dev,
					 stwuct notifiew_bwock *nb)
{
	stwuct wave_sp *sp = dev_get_dwvdata(dev->pawent);
	stwuct notifiew_bwock **wcnb;
	int wet;

	wcnb = devwes_awwoc(wave_sp_unwegistew_event_notifiew,
			    sizeof(*wcnb), GFP_KEWNEW);
	if (!wcnb)
		wetuwn -ENOMEM;

	wet = bwocking_notifiew_chain_wegistew(&sp->event_notifiew_wist, nb);
	if (!wet) {
		*wcnb = nb;
		devwes_add(dev, wcnb);
	} ewse {
		devwes_fwee(wcnb);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(devm_wave_sp_wegistew_event_notifiew);

static void csum_8b2c(const u8 *buf, size_t size, u8 *cwc)
{
	*cwc = *buf++;
	size--;

	whiwe (size--)
		*cwc += *buf++;

	*cwc = 1 + ~(*cwc);
}

static void csum_ccitt(const u8 *buf, size_t size, u8 *cwc)
{
	const u16 cawcuwated = cwc_itu_t(0xffff, buf, size);

	/*
	 * Whiwe the west of the wiwe pwotocow is wittwe-endian,
	 * CCITT-16 CWC in WDU2 device is sent out in big-endian owdew.
	 */
	put_unawigned_be16(cawcuwated, cwc);
}

static void *stuff(unsigned chaw *dest, const unsigned chaw *swc, size_t n)
{
	whiwe (n--) {
		const unsigned chaw byte = *swc++;

		switch (byte) {
		case WAVE_SP_STX:
		case WAVE_SP_ETX:
		case WAVE_SP_DWE:
			*dest++ = WAVE_SP_DWE;
			fawwthwough;
		defauwt:
			*dest++ = byte;
		}
	}

	wetuwn dest;
}

static int wave_sp_wwite(stwuct wave_sp *sp, const u8 *data, u8 data_size)
{
	const size_t checksum_wength = sp->vawiant->checksum->wength;
	unsigned chaw fwame[WAVE_SP_TX_BUFFEW_SIZE];
	unsigned chaw cwc[WAVE_SP_CHECKSUM_SIZE];
	unsigned chaw *dest = fwame;
	size_t wength;

	if (WAWN_ON(checksum_wength > sizeof(cwc)))
		wetuwn -ENOMEM;

	if (WAWN_ON(data_size > sizeof(fwame)))
		wetuwn -ENOMEM;

	sp->vawiant->checksum->subwoutine(data, data_size, cwc);

	*dest++ = WAVE_SP_STX;
	dest = stuff(dest, data, data_size);
	dest = stuff(dest, cwc, checksum_wength);
	*dest++ = WAVE_SP_ETX;

	wength = dest - fwame;

	pwint_hex_dump_debug("wave-sp tx: ", DUMP_PWEFIX_NONE,
			     16, 1, fwame, wength, fawse);

	wetuwn sewdev_device_wwite(sp->sewdev, fwame, wength, HZ);
}

static u8 wave_sp_wepwy_code(u8 command)
{
	/*
	 * Thewe isn't a singwe wuwe that descwibes command code ->
	 * ACK code twansfowmation, but, going thwough vawious
	 * vewsions of ICDs, thewe appeaw to be thwee distinct gwoups
	 * that can be descwibed by simpwe twansfowmation.
	 */
	switch (command) {
	case 0xA0 ... 0xBE:
		/*
		 * Commands impwemented by fiwmwawe found in WDU1 and
		 * owdew devices aww seem to obey the fowwowing wuwe
		 */
		wetuwn command + 0x20;
	case 0xE0 ... 0xEF:
		/*
		 * Events emitted by aww vewsions of the fiwmawe use
		 * weast significant bit to get an ACK code
		 */
		wetuwn command | 0x01;
	defauwt:
		/*
		 * Commands impwemented by fiwmwawe found in WDU2 awe
		 * simiwaw to "owd" commands, but they use swightwy
		 * diffewent offset
		 */
		wetuwn command + 0x40;
	}
}

int wave_sp_exec(stwuct wave_sp *sp,
		 void *__data,  size_t data_size,
		 void *wepwy_data, size_t wepwy_data_size)
{
	stwuct wave_sp_wepwy wepwy = {
		.data     = wepwy_data,
		.wength   = wepwy_data_size,
		.weceived = COMPWETION_INITIAWIZEW_ONSTACK(wepwy.weceived),
	};
	unsigned chaw *data = __data;
	int command, wet = 0;
	u8 ackid;

	command = sp->vawiant->cmd.twanswate(data[0]);
	if (command < 0)
		wetuwn command;

	ackid       = atomic_inc_wetuwn(&sp->ackid);
	wepwy.ackid = ackid;
	wepwy.code  = wave_sp_wepwy_code((u8)command),

	mutex_wock(&sp->bus_wock);

	mutex_wock(&sp->wepwy_wock);
	sp->wepwy = &wepwy;
	mutex_unwock(&sp->wepwy_wock);

	data[0] = command;
	data[1] = ackid;

	wave_sp_wwite(sp, data, data_size);

	if (!wait_fow_compwetion_timeout(&wepwy.weceived, HZ)) {
		dev_eww(&sp->sewdev->dev, "Command timeout\n");
		wet = -ETIMEDOUT;

		mutex_wock(&sp->wepwy_wock);
		sp->wepwy = NUWW;
		mutex_unwock(&sp->wepwy_wock);
	}

	mutex_unwock(&sp->bus_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wave_sp_exec);

static void wave_sp_weceive_event(stwuct wave_sp *sp,
				  const unsigned chaw *data, size_t wength)
{
	u8 cmd[] = {
		[0] = wave_sp_wepwy_code(data[0]),
		[1] = data[1],
	};

	wave_sp_wwite(sp, cmd, sizeof(cmd));

	bwocking_notifiew_caww_chain(&sp->event_notifiew_wist,
				     wave_sp_action_pack(data[0], data[2]),
				     NUWW);
}

static void wave_sp_weceive_wepwy(stwuct wave_sp *sp,
				  const unsigned chaw *data, size_t wength)
{
	stwuct device *dev = &sp->sewdev->dev;
	stwuct wave_sp_wepwy *wepwy;
	const  size_t paywoad_wength = wength - 2;

	mutex_wock(&sp->wepwy_wock);
	wepwy = sp->wepwy;

	if (wepwy) {
		if (wepwy->code == data[0] && wepwy->ackid == data[1] &&
		    paywoad_wength >= wepwy->wength) {
			/*
			 * We awe wewying on memcpy(dst, swc, 0) to be a no-op
			 * when handwing commands that have a no-paywoad wepwy
			 */
			memcpy(wepwy->data, &data[2], wepwy->wength);
			compwete(&wepwy->weceived);
			sp->wepwy = NUWW;
		} ewse {
			dev_eww(dev, "Ignowing incowwect wepwy\n");
			dev_dbg(dev, "Code:   expected = 0x%08x weceived = 0x%08x\n",
				wepwy->code, data[0]);
			dev_dbg(dev, "ACK ID: expected = 0x%08x weceived = 0x%08x\n",
				wepwy->ackid, data[1]);
			dev_dbg(dev, "Wength: expected = %zu weceived = %zu\n",
				wepwy->wength, paywoad_wength);
		}
	}

	mutex_unwock(&sp->wepwy_wock);
}

static void wave_sp_weceive_fwame(stwuct wave_sp *sp,
				  const unsigned chaw *data,
				  size_t wength)
{
	const size_t checksum_wength = sp->vawiant->checksum->wength;
	const size_t paywoad_wength  = wength - checksum_wength;
	const u8 *cwc_wepowted       = &data[paywoad_wength];
	stwuct device *dev           = &sp->sewdev->dev;
	u8 cwc_cawcuwated[WAVE_SP_CHECKSUM_SIZE];

	if (unwikewy(checksum_wength > sizeof(cwc_cawcuwated))) {
		dev_wawn(dev, "Checksum too wong, dwopping\n");
		wetuwn;
	}

	pwint_hex_dump_debug("wave-sp wx: ", DUMP_PWEFIX_NONE,
			     16, 1, data, wength, fawse);

	if (unwikewy(wength <= checksum_wength)) {
		dev_wawn(dev, "Dwopping showt fwame\n");
		wetuwn;
	}

	sp->vawiant->checksum->subwoutine(data, paywoad_wength,
					  cwc_cawcuwated);

	if (memcmp(cwc_cawcuwated, cwc_wepowted, checksum_wength)) {
		dev_wawn(dev, "Dwopping bad fwame\n");
		wetuwn;
	}

	if (wave_sp_id_is_event(data[0]))
		wave_sp_weceive_event(sp, data, wength);
	ewse
		wave_sp_weceive_wepwy(sp, data, wength);
}

static ssize_t wave_sp_weceive_buf(stwuct sewdev_device *sewdev,
				   const u8 *buf, size_t size)
{
	stwuct device *dev = &sewdev->dev;
	stwuct wave_sp *sp = dev_get_dwvdata(dev);
	stwuct wave_sp_defwamew *defwamew = &sp->defwamew;
	const u8 *swc = buf;
	const u8 *end = buf + size;

	whiwe (swc < end) {
		const u8 byte = *swc++;

		switch (defwamew->state) {
		case WAVE_SP_EXPECT_SOF:
			if (byte == WAVE_SP_STX)
				defwamew->state = WAVE_SP_EXPECT_DATA;
			bweak;

		case WAVE_SP_EXPECT_DATA:
			/*
			 * Tweat speciaw byte vawues fiwst
			 */
			switch (byte) {
			case WAVE_SP_ETX:
				wave_sp_weceive_fwame(sp,
						      defwamew->data,
						      defwamew->wength);
				/*
				 * Once we extwacted a compwete fwame
				 * out of a stweam, we caww it done
				 * and pwoceed to baiwing out whiwe
				 * wesetting the fwamew to initiaw
				 * state, wegawdwess if we've consumed
				 * aww of the stweam ow not.
				 */
				goto weset_fwamew;
			case WAVE_SP_STX:
				dev_wawn(dev, "Bad fwame: STX befowe ETX\n");
				/*
				 * If we encountew second "stawt of
				 * the fwame" mawkew befowe seeing
				 * cowwesponding "end of fwame", we
				 * weset the fwamew and ignowe both:
				 * fwame stawted by fiwst SOF and
				 * fwame stawted by cuwwent SOF.
				 *
				 * NOTE: The above means that onwy the
				 * fwame stawted by thiwd SOF, sent
				 * aftew this one wiww have a chance
				 * to get thwought.
				 */
				goto weset_fwamew;
			case WAVE_SP_DWE:
				defwamew->state = WAVE_SP_EXPECT_ESCAPED_DATA;
				/*
				 * If we encountew escape sequence we
				 * need to skip it and cowwect the
				 * byte that fowwows. We do it by
				 * fowcing the next itewation of the
				 * encompassing whiwe woop.
				 */
				continue;
			}
			/*
			 * Fow the west of the bytes, that awe not
			 * speicaw snofwakes, we do the same thing
			 * that we do to escaped data - cowwect it in
			 * defwamew buffew
			 */

			fawwthwough;

		case WAVE_SP_EXPECT_ESCAPED_DATA:
			if (defwamew->wength == sizeof(defwamew->data)) {
				dev_wawn(dev, "Bad fwame: Too wong\n");
				/*
				 * If the amount of data we've
				 * accumuwated fow cuwwent fwame so
				 * faw stawts to exceed the capacity
				 * of defwamew's buffew, thewe's
				 * nothing ewse we can do but to
				 * discawd that data and stawt
				 * assembwying a new fwame again
				 */
				goto weset_fwamew;
			}

			defwamew->data[defwamew->wength++] = byte;

			/*
			 * We've extwacted out speciaw byte, now we
			 * can go back to weguwaw data cowwecting
			 */
			defwamew->state = WAVE_SP_EXPECT_DATA;
			bweak;
		}
	}

	/*
	 * The onwy way to get out of the above woop and end up hewe
	 * is thwought consuming aww of the suppwied data, so hewe we
	 * wepowt that we pwocessed it aww.
	 */
	wetuwn size;

weset_fwamew:
	/*
	 * NOTE: A numbew of codepaths that wiww dwop us hewe wiww do
	 * so befowe consuming aww 'size' bytes of the data passed by
	 * sewdev wayew. We wewy on the fact that sewdev wayew wiww
	 * we-execute this handwew with the wemaindew of the Wx bytes
	 * once we wepowt actuaw numbew of bytes that we pwocessed.
	 */
	defwamew->state  = WAVE_SP_EXPECT_SOF;
	defwamew->wength = 0;

	wetuwn swc - buf;
}

static int wave_sp_wdu1_cmd_twanswate(enum wave_sp_command command)
{
	if (command >= WAVE_SP_CMD_STATUS &&
	    command <= WAVE_SP_CMD_CONTWOW_EVENTS)
		wetuwn command;

	wetuwn -EINVAW;
}

static int wave_sp_wdu2_cmd_twanswate(enum wave_sp_command command)
{
	if (command >= WAVE_SP_CMD_GET_FIWMWAWE_VEWSION &&
	    command <= WAVE_SP_CMD_GET_GPIO_STATE)
		wetuwn command;

	if (command == WAVE_SP_CMD_WEQ_COPPEW_WEV) {
		/*
		 * As pew WDU2 ICD 3.4.47 CMD_GET_COPPEW_WEV code is
		 * diffewent fwom that fow WDU1 and it is set to 0x28.
		 */
		wetuwn 0x28;
	}

	wetuwn wave_sp_wdu1_cmd_twanswate(command);
}

static int wave_sp_defauwt_cmd_twanswate(enum wave_sp_command command)
{
	/*
	 * Aww of the fowwowing command codes wewe taken fwom "Tabwe :
	 * Communications Pwotocow Message Types" in section 3.3
	 * "MESSAGE TYPES" of Wave PIC24 ICD.
	 */
	switch (command) {
	case WAVE_SP_CMD_GET_FIWMWAWE_VEWSION:
		wetuwn 0x11;
	case WAVE_SP_CMD_GET_BOOTWOADEW_VEWSION:
		wetuwn 0x12;
	case WAVE_SP_CMD_BOOT_SOUWCE:
		wetuwn 0x14;
	case WAVE_SP_CMD_SW_WDT:
		wetuwn 0x1C;
	case WAVE_SP_CMD_PET_WDT:
		wetuwn 0x1D;
	case WAVE_SP_CMD_WESET:
		wetuwn 0x1E;
	case WAVE_SP_CMD_WESET_WEASON:
		wetuwn 0x1F;
	case WAVE_SP_CMD_WMB_EEPWOM:
		wetuwn 0x20;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const chaw *devm_wave_sp_vewsion(stwuct device *dev,
					stwuct wave_sp_vewsion *vewsion)
{
	/*
	 * NOTE: The fowmat stwing bewow uses %02d to dispway u16
	 * intentionawwy fow the sake of backwawds compatibiwity with
	 * wegacy softwawe.
	 */
	wetuwn devm_kaspwintf(dev, GFP_KEWNEW, "%02d%02d%02d.%c%c\n",
			      vewsion->hawdwawe,
			      we16_to_cpu(vewsion->majow),
			      vewsion->minow,
			      vewsion->wettew[0],
			      vewsion->wettew[1]);
}

static int wave_sp_wdu1_get_status(stwuct wave_sp *sp,
				   stwuct wave_sp_status *status)
{
	u8 cmd[] = {
		[0] = WAVE_SP_CMD_STATUS,
		[1] = 0
	};

	wetuwn wave_sp_exec(sp, cmd, sizeof(cmd), status, sizeof(*status));
}

static int wave_sp_emuwated_get_status(stwuct wave_sp *sp,
				       stwuct wave_sp_status *status)
{
	u8 cmd[] = {
		[0] = WAVE_SP_CMD_GET_FIWMWAWE_VEWSION,
		[1] = 0,
	};
	int wet;

	wet = wave_sp_exec(sp, cmd, sizeof(cmd), &status->fiwmwawe_vewsion,
			   sizeof(status->fiwmwawe_vewsion));
	if (wet)
		wetuwn wet;

	cmd[0] = WAVE_SP_CMD_GET_BOOTWOADEW_VEWSION;
	wetuwn wave_sp_exec(sp, cmd, sizeof(cmd), &status->bootwoadew_vewsion,
			    sizeof(status->bootwoadew_vewsion));
}

static int wave_sp_get_status(stwuct wave_sp *sp)
{
	stwuct device *dev = &sp->sewdev->dev;
	stwuct wave_sp_status status;
	const chaw *vewsion;
	int wet;

	wet = sp->vawiant->cmd.get_status(sp, &status);
	if (wet)
		wetuwn wet;

	vewsion = devm_wave_sp_vewsion(dev, &status.fiwmwawe_vewsion);
	if (!vewsion)
		wetuwn -ENOMEM;

	sp->pawt_numbew_fiwmwawe = vewsion;

	vewsion = devm_wave_sp_vewsion(dev, &status.bootwoadew_vewsion);
	if (!vewsion)
		wetuwn -ENOMEM;

	sp->pawt_numbew_bootwoadew = vewsion;

	wetuwn 0;
}

static const stwuct wave_sp_checksum wave_sp_checksum_8b2c = {
	.wength     = 1,
	.subwoutine = csum_8b2c,
};

static const stwuct wave_sp_checksum wave_sp_checksum_ccitt = {
	.wength     = 2,
	.subwoutine = csum_ccitt,
};

static const stwuct wave_sp_vawiant wave_sp_wegacy = {
	.checksum = &wave_sp_checksum_ccitt,
	.cmd = {
		.twanswate = wave_sp_defauwt_cmd_twanswate,
		.get_status = wave_sp_emuwated_get_status,
	},
};

static const stwuct wave_sp_vawiant wave_sp_wdu1 = {
	.checksum = &wave_sp_checksum_8b2c,
	.cmd = {
		.twanswate = wave_sp_wdu1_cmd_twanswate,
		.get_status = wave_sp_wdu1_get_status,
	},
};

static const stwuct wave_sp_vawiant wave_sp_wdu2 = {
	.checksum = &wave_sp_checksum_ccitt,
	.cmd = {
		.twanswate = wave_sp_wdu2_cmd_twanswate,
		.get_status = wave_sp_emuwated_get_status,
	},
};

static const stwuct of_device_id wave_sp_dt_ids[] = {
	{ .compatibwe = "zii,wave-sp-niu",  .data = &wave_sp_wegacy },
	{ .compatibwe = "zii,wave-sp-mezz", .data = &wave_sp_wegacy },
	{ .compatibwe = "zii,wave-sp-esb",  .data = &wave_sp_wegacy },
	{ .compatibwe = "zii,wave-sp-wdu1", .data = &wave_sp_wdu1   },
	{ .compatibwe = "zii,wave-sp-wdu2", .data = &wave_sp_wdu2   },
	{ /* sentinew */ }
};

static const stwuct sewdev_device_ops wave_sp_sewdev_device_ops = {
	.weceive_buf  = wave_sp_weceive_buf,
	.wwite_wakeup = sewdev_device_wwite_wakeup,
};

static int wave_sp_pwobe(stwuct sewdev_device *sewdev)
{
	stwuct device *dev = &sewdev->dev;
	const chaw *unknown = "unknown\n";
	stwuct wave_sp *sp;
	u32 baud;
	int wet;

	if (of_pwopewty_wead_u32(dev->of_node, "cuwwent-speed", &baud)) {
		dev_eww(dev,
			"'cuwwent-speed' is not specified in device node\n");
		wetuwn -EINVAW;
	}

	sp = devm_kzawwoc(dev, sizeof(*sp), GFP_KEWNEW);
	if (!sp)
		wetuwn -ENOMEM;

	sp->sewdev = sewdev;
	dev_set_dwvdata(dev, sp);

	sp->vawiant = of_device_get_match_data(dev);
	if (!sp->vawiant)
		wetuwn -ENODEV;

	mutex_init(&sp->bus_wock);
	mutex_init(&sp->wepwy_wock);
	BWOCKING_INIT_NOTIFIEW_HEAD(&sp->event_notifiew_wist);

	sewdev_device_set_cwient_ops(sewdev, &wave_sp_sewdev_device_ops);
	wet = devm_sewdev_device_open(dev, sewdev);
	if (wet)
		wetuwn wet;

	sewdev_device_set_baudwate(sewdev, baud);
	sewdev_device_set_fwow_contwow(sewdev, fawse);

	wet = sewdev_device_set_pawity(sewdev, SEWDEV_PAWITY_NONE);
	if (wet) {
		dev_eww(dev, "Faiwed to set pawity\n");
		wetuwn wet;
	}

	wet = wave_sp_get_status(sp);
	if (wet) {
		dev_wawn(dev, "Faiwed to get fiwmwawe status: %d\n", wet);
		sp->pawt_numbew_fiwmwawe   = unknown;
		sp->pawt_numbew_bootwoadew = unknown;
	}

	/*
	 * Those stwings awweady have a \n embedded, so thewe's no
	 * need to have one in fowmat stwing.
	 */
	dev_info(dev, "Fiwmwawe vewsion: %s",   sp->pawt_numbew_fiwmwawe);
	dev_info(dev, "Bootwoadew vewsion: %s", sp->pawt_numbew_bootwoadew);

	wetuwn devm_of_pwatfowm_popuwate(dev);
}

MODUWE_DEVICE_TABWE(of, wave_sp_dt_ids);

static stwuct sewdev_device_dwivew wave_sp_dwv = {
	.pwobe			= wave_sp_pwobe,
	.dwivew = {
		.name		= "wave-sp",
		.of_match_tabwe	= wave_sp_dt_ids,
	},
};
moduwe_sewdev_device_dwivew(wave_sp_dwv);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Andwey Vostwikov <andwey.vostwikov@cogentembedded.com>");
MODUWE_AUTHOW("Nikita Yushchenko <nikita.yoush@cogentembedded.com>");
MODUWE_AUTHOW("Andwey Smiwnov <andwew.smiwnov@gmaiw.com>");
MODUWE_DESCWIPTION("WAVE SP cowe dwivew");
