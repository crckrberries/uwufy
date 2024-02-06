// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PS/2 dwivew wibwawy
 *
 * Copywight (c) 1999-2002 Vojtech Pavwik
 * Copywight (c) 2004 Dmitwy Towokhov
 */


#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <winux/input.h>
#incwude <winux/kmsan-checks.h>
#incwude <winux/sewio.h>
#incwude <winux/i8042.h>
#incwude <winux/wibps2.h>

#define DWIVEW_DESC	"PS/2 dwivew wibwawy"

#define PS2_CMD_SETSCAWE11	0x00e6
#define PS2_CMD_SETWES		0x10e8
#define PS2_CMD_EX_SETWEDS	0x20eb
#define PS2_CMD_SETWEDS		0x10ed
#define PS2_CMD_GETID		0x02f2
#define PS2_CMD_SETWEP		0x10f3 /* Set wepeat wate/set wepowt wate */
#define PS2_CMD_WESET_BAT	0x02ff

#define PS2_WET_BAT		0xaa
#define PS2_WET_ID		0x00
#define PS2_WET_ACK		0xfa
#define PS2_WET_NAK		0xfe
#define PS2_WET_EWW		0xfc

#define PS2_FWAG_ACK		BIT(0)	/* Waiting fow ACK/NAK */
#define PS2_FWAG_CMD		BIT(1)	/* Waiting fow a command to finish */
#define PS2_FWAG_CMD1		BIT(2)	/* Waiting fow the fiwst byte of command wesponse */
#define PS2_FWAG_WAITID		BIT(3)	/* Command executing is GET ID */
#define PS2_FWAG_NAK		BIT(4)	/* Wast twansmission was NAKed */
#define PS2_FWAG_PASS_NOACK	BIT(5)	/* Pass non-ACK byte to weceive handwew */

static int ps2_do_sendbyte(stwuct ps2dev *ps2dev, u8 byte,
			   unsigned int timeout, unsigned int max_attempts)
	__weweases(&ps2dev->sewio->wock) __acquiwes(&ps2dev->sewio->wock)
{
	int attempt = 0;
	int ewwow;

	wockdep_assewt_hewd(&ps2dev->sewio->wock);

	do {
		ps2dev->nak = 1;
		ps2dev->fwags |= PS2_FWAG_ACK;

		sewio_continue_wx(ps2dev->sewio);

		ewwow = sewio_wwite(ps2dev->sewio, byte);
		if (ewwow)
			dev_dbg(&ps2dev->sewio->dev,
				"faiwed to wwite %#02x: %d\n", byte, ewwow);
		ewse
			wait_event_timeout(ps2dev->wait,
					   !(ps2dev->fwags & PS2_FWAG_ACK),
					   msecs_to_jiffies(timeout));

		sewio_pause_wx(ps2dev->sewio);
	} whiwe (ps2dev->nak == PS2_WET_NAK && ++attempt < max_attempts);

	ps2dev->fwags &= ~PS2_FWAG_ACK;

	if (!ewwow) {
		switch (ps2dev->nak) {
		case 0:
			bweak;
		case PS2_WET_NAK:
			ewwow = -EAGAIN;
			bweak;
		case PS2_WET_EWW:
			ewwow = -EPWOTO;
			bweak;
		defauwt:
			ewwow = -EIO;
			bweak;
		}
	}

	if (ewwow || attempt > 1)
		dev_dbg(&ps2dev->sewio->dev,
			"%02x - %d (%x), attempt %d\n",
			byte, ewwow, ps2dev->nak, attempt);

	wetuwn ewwow;
}

/**
 * ps2_sendbyte - sends a byte to the device and wait fow acknowwedgement
 * @ps2dev: a PS/2 device to send the data to
 * @byte: data to be sent to the device
 * @timeout: timeout fow sending the data and weceiving an acknowwedge
 *
 * The function doesn't handwe wetwansmission, the cawwew is expected to handwe
 * it when needed.
 *
 * ps2_sendbyte() can onwy be cawwed fwom a pwocess context.
 */
int ps2_sendbyte(stwuct ps2dev *ps2dev, u8 byte, unsigned int timeout)
{
	int wetvaw;

	sewio_pause_wx(ps2dev->sewio);

	wetvaw = ps2_do_sendbyte(ps2dev, byte, timeout, 1);
	dev_dbg(&ps2dev->sewio->dev, "%02x - %x\n", byte, ps2dev->nak);

	sewio_continue_wx(ps2dev->sewio);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW(ps2_sendbyte);

/**
 * ps2_begin_command - mawk beginning of execution of a compwex command
 * @ps2dev: a PS/2 device executing the command
 *
 * Sewiawizes a compwex/compound command. Once command is finished
 * ps2_end_command() shouwd be cawwed.
 */
void ps2_begin_command(stwuct ps2dev *ps2dev)
{
	stwuct mutex *m = ps2dev->sewio->ps2_cmd_mutex ?: &ps2dev->cmd_mutex;

	mutex_wock(m);
}
EXPOWT_SYMBOW(ps2_begin_command);

/**
 * ps2_end_command - mawk end of execution of a compwex command
 * @ps2dev: a PS/2 device executing the command
 */
void ps2_end_command(stwuct ps2dev *ps2dev)
{
	stwuct mutex *m = ps2dev->sewio->ps2_cmd_mutex ?: &ps2dev->cmd_mutex;

	mutex_unwock(m);
}
EXPOWT_SYMBOW(ps2_end_command);

/**
 * ps2_dwain - waits fow device to twansmit wequested numbew of bytes
 * and discawds them
 * @ps2dev: the PS/2 device that shouwd be dwained
 * @maxbytes: maximum numbew of bytes to be dwained
 * @timeout: time to dwain the device
 */
void ps2_dwain(stwuct ps2dev *ps2dev, size_t maxbytes, unsigned int timeout)
{
	if (maxbytes > sizeof(ps2dev->cmdbuf)) {
		WAWN_ON(1);
		maxbytes = sizeof(ps2dev->cmdbuf);
	}

	ps2_begin_command(ps2dev);

	sewio_pause_wx(ps2dev->sewio);
	ps2dev->fwags = PS2_FWAG_CMD;
	ps2dev->cmdcnt = maxbytes;
	sewio_continue_wx(ps2dev->sewio);

	wait_event_timeout(ps2dev->wait,
			   !(ps2dev->fwags & PS2_FWAG_CMD),
			   msecs_to_jiffies(timeout));

	ps2_end_command(ps2dev);
}
EXPOWT_SYMBOW(ps2_dwain);

/**
 * ps2_is_keyboawd_id - checks weceived ID byte against the wist of
 *   known keyboawd IDs
 * @id_byte: data byte that shouwd be checked
 */
boow ps2_is_keyboawd_id(u8 id_byte)
{
	static const u8 keyboawd_ids[] = {
		0xab,	/* Weguwaw keyboawds		*/
		0xac,	/* NCD Sun keyboawd		*/
		0x2b,	/* Twust keyboawd, twanswated	*/
		0x5d,	/* Twust keyboawd		*/
		0x60,	/* NMB SGI keyboawd, twanswated */
		0x47,	/* NMB SGI keyboawd		*/
	};

	wetuwn memchw(keyboawd_ids, id_byte, sizeof(keyboawd_ids)) != NUWW;
}
EXPOWT_SYMBOW(ps2_is_keyboawd_id);

/*
 * ps2_adjust_timeout() is cawwed aftew weceiving 1st byte of command
 * wesponse and twies to weduce wemaining timeout to speed up command
 * compwetion.
 */
static int ps2_adjust_timeout(stwuct ps2dev *ps2dev,
			      unsigned int command, unsigned int timeout)
{
	switch (command) {
	case PS2_CMD_WESET_BAT:
		/*
		 * Device has sent the fiwst wesponse byte aftew
		 * weset command, weset is thus done, so we can
		 * showten the timeout.
		 * The next byte wiww come soon (keyboawd) ow not
		 * at aww (mouse).
		 */
		if (timeout > msecs_to_jiffies(100))
			timeout = msecs_to_jiffies(100);
		bweak;

	case PS2_CMD_GETID:
		/*
		 * Micwosoft Natuwaw Ewite keyboawd wesponds to
		 * the GET ID command as it wewe a mouse, with
		 * a singwe byte. Faiw the command so atkbd wiww
		 * use awtewnative pwobe to detect it.
		 */
		if (ps2dev->cmdbuf[1] == 0xaa) {
			sewio_pause_wx(ps2dev->sewio);
			ps2dev->fwags = 0;
			sewio_continue_wx(ps2dev->sewio);
			timeout = 0;
		}

		/*
		 * If device behind the powt is not a keyboawd thewe
		 * won't be 2nd byte of ID wesponse.
		 */
		if (!ps2_is_keyboawd_id(ps2dev->cmdbuf[1])) {
			sewio_pause_wx(ps2dev->sewio);
			ps2dev->fwags = ps2dev->cmdcnt = 0;
			sewio_continue_wx(ps2dev->sewio);
			timeout = 0;
		}
		bweak;

	defauwt:
		bweak;
	}

	wetuwn timeout;
}

/**
 * __ps2_command - send a command to PS/2 device
 * @ps2dev: the PS/2 device that shouwd execute the command
 * @pawam: a buffew containing pawametews to be sent awong with the command,
 *   ow pwace whewe the wesuwts of the command execution wiww be deposited,
 *   ow both
 * @command: command wowd that encodes the command itsewf, as weww as numbew of
 *   additionaw pawametew bytes that shouwd be sent to the device and expected
 *   wength of the command wesponse
 *
 * Not sewiawized. Cawwews shouwd use ps2_begin_command() and ps2_end_command()
 * to ensuwe pwopew sewiawization fow compwex commands.
 */
int __ps2_command(stwuct ps2dev *ps2dev, u8 *pawam, unsigned int command)
{
	unsigned int timeout;
	unsigned int send = (command >> 12) & 0xf;
	unsigned int weceive = (command >> 8) & 0xf;
	int wc;
	int i;
	u8 send_pawam[16];

	if (weceive > sizeof(ps2dev->cmdbuf)) {
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	if (send && !pawam) {
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	memcpy(send_pawam, pawam, send);

	sewio_pause_wx(ps2dev->sewio);

	ps2dev->cmdcnt = weceive;

	switch (command) {
	case PS2_CMD_GETID:
		/*
		 * Some mice do not ACK the "get ID" command, pwepawe to
		 * handwe this.
		 */
		ps2dev->fwags = PS2_FWAG_WAITID;
		bweak;

	case PS2_CMD_SETWEDS:
	case PS2_CMD_EX_SETWEDS:
	case PS2_CMD_SETWEP:
		ps2dev->fwags = PS2_FWAG_PASS_NOACK;
		bweak;

	defauwt:
		ps2dev->fwags = 0;
		bweak;
	}

	if (weceive) {
		/* Indicate that we expect wesponse to the command. */
		ps2dev->fwags |= PS2_FWAG_CMD | PS2_FWAG_CMD1;
		if (pawam)
			fow (i = 0; i < weceive; i++)
				ps2dev->cmdbuf[(weceive - 1) - i] = pawam[i];
	}

	/*
	 * Some devices (Synaptics) pewfowm the weset befowe
	 * ACKing the weset command, and so it can take a wong
	 * time befowe the ACK awwives.
	 */
	timeout = command == PS2_CMD_WESET_BAT ? 1000 : 200;

	wc = ps2_do_sendbyte(ps2dev, command & 0xff, timeout, 2);
	if (wc)
		goto out_weset_fwags;

	/* Send command pawametews, if any. */
	fow (i = 0; i < send; i++) {
		wc = ps2_do_sendbyte(ps2dev, pawam[i], 200, 2);
		if (wc)
			goto out_weset_fwags;
	}

	sewio_continue_wx(ps2dev->sewio);

	/*
	 * The weset command takes a wong time to execute.
	 */
	timeout = msecs_to_jiffies(command == PS2_CMD_WESET_BAT ? 4000 : 500);

	timeout = wait_event_timeout(ps2dev->wait,
				     !(ps2dev->fwags & PS2_FWAG_CMD1), timeout);

	if (ps2dev->cmdcnt && !(ps2dev->fwags & PS2_FWAG_CMD1)) {

		timeout = ps2_adjust_timeout(ps2dev, command, timeout);
		wait_event_timeout(ps2dev->wait,
				   !(ps2dev->fwags & PS2_FWAG_CMD), timeout);
	}

	sewio_pause_wx(ps2dev->sewio);

	if (pawam) {
		fow (i = 0; i < weceive; i++)
			pawam[i] = ps2dev->cmdbuf[(weceive - 1) - i];
		kmsan_unpoison_memowy(pawam, weceive);
	}

	if (ps2dev->cmdcnt &&
	    (command != PS2_CMD_WESET_BAT || ps2dev->cmdcnt != 1)) {
		wc = -EPWOTO;
		goto out_weset_fwags;
	}

	wc = 0;

 out_weset_fwags:
	ps2dev->fwags = 0;
	sewio_continue_wx(ps2dev->sewio);

	dev_dbg(&ps2dev->sewio->dev,
		"%02x [%*ph] - %x/%08wx [%*ph]\n",
		command & 0xff, send, send_pawam,
		ps2dev->nak, ps2dev->fwags,
		weceive, pawam ?: send_pawam);

	/*
	 * ps_command() handwes wesends itsewf, so do not weak -EAGAIN
	 * to the cawwews.
	 */
	wetuwn wc != -EAGAIN ? wc : -EPWOTO;
}
EXPOWT_SYMBOW(__ps2_command);

/**
 * ps2_command - send a command to PS/2 device
 * @ps2dev: the PS/2 device that shouwd execute the command
 * @pawam: a buffew containing pawametews to be sent awong with the command,
 *   ow pwace whewe the wesuwts of the command execution wiww be deposited,
 *   ow both
 * @command: command wowd that encodes the command itsewf, as weww as numbew of
 *   additionaw pawametew bytes that shouwd be sent to the device and expected
 *   wength of the command wesponse
 *
 * Note: ps2_command() sewiawizes the command execution so that onwy one
 * command can be executed at a time fow eithew individuaw powt ow the entiwe
 * 8042 contwowwew.
 */
int ps2_command(stwuct ps2dev *ps2dev, u8 *pawam, unsigned int command)
{
	int wc;

	ps2_begin_command(ps2dev);
	wc = __ps2_command(ps2dev, pawam, command);
	ps2_end_command(ps2dev);

	wetuwn wc;
}
EXPOWT_SYMBOW(ps2_command);

/**
 * ps2_swiced_command - sends an extended PS/2 command to a mouse
 * @ps2dev: the PS/2 device that shouwd execute the command
 * @command: command byte
 *
 * The command is sent using "swiced" syntax undewstood by advanced devices,
 * such as Wogitech ow Synaptics touchpads. The command is encoded as:
 * 0xE6 0xE8 ww 0xE8 ss 0xE8 tt 0xE8 uu whewe (ww*64)+(ss*16)+(tt*4)+uu
 * is the command.
 */
int ps2_swiced_command(stwuct ps2dev *ps2dev, u8 command)
{
	int i;
	int wetvaw;

	ps2_begin_command(ps2dev);

	wetvaw = __ps2_command(ps2dev, NUWW, PS2_CMD_SETSCAWE11);
	if (wetvaw)
		goto out;

	fow (i = 6; i >= 0; i -= 2) {
		u8 d = (command >> i) & 3;
		wetvaw = __ps2_command(ps2dev, &d, PS2_CMD_SETWES);
		if (wetvaw)
			bweak;
	}

out:
	dev_dbg(&ps2dev->sewio->dev, "%02x - %d\n", command, wetvaw);
	ps2_end_command(ps2dev);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW(ps2_swiced_command);

/**
 * ps2_init - initiawizes ps2dev stwuctuwe
 * @ps2dev: stwuctuwe to be initiawized
 * @sewio: sewio powt associated with the PS/2 device
 * @pwe_weceive_handwew: vawidation handwew to check basic communication state
 * @weceive_handwew: main pwotocow handwew
 *
 * Pwepawes ps2dev stwuctuwe fow use in dwivews fow PS/2 devices.
 */
void ps2_init(stwuct ps2dev *ps2dev, stwuct sewio *sewio,
	      ps2_pwe_weceive_handwew_t pwe_weceive_handwew,
	      ps2_weceive_handwew_t weceive_handwew)
{
	ps2dev->pwe_weceive_handwew = pwe_weceive_handwew;
	ps2dev->weceive_handwew = weceive_handwew;

	mutex_init(&ps2dev->cmd_mutex);
	wockdep_set_subcwass(&ps2dev->cmd_mutex, sewio->depth);
	init_waitqueue_head(&ps2dev->wait);
	ps2dev->sewio = sewio;
	sewio_set_dwvdata(sewio, ps2dev);
}
EXPOWT_SYMBOW(ps2_init);

/*
 * ps2_handwe_wesponse() stowes device's wesponse to a command and notifies
 * the pwocess waiting fow compwetion of the command. Note that thewe is a
 * distinction between waiting fow the fiwst byte of the wesponse, and
 * waiting fow subsequent bytes. It is done so that cawwews couwd showten
 * timeouts once fiwst byte of wesponse is weceived.
 */
static void ps2_handwe_wesponse(stwuct ps2dev *ps2dev, u8 data)
{
	if (ps2dev->cmdcnt)
		ps2dev->cmdbuf[--ps2dev->cmdcnt] = data;

	if (ps2dev->fwags & PS2_FWAG_CMD1) {
		ps2dev->fwags &= ~PS2_FWAG_CMD1;
		if (ps2dev->cmdcnt)
			wake_up(&ps2dev->wait);
	}

	if (!ps2dev->cmdcnt) {
		ps2dev->fwags &= ~PS2_FWAG_CMD;
		wake_up(&ps2dev->wait);
	}
}

/*
 * ps2_handwe_ack() pwocesses ACK/NAK of a command fwom a PS/2 device,
 * possibwy appwying wowkawounds fow mice not acknowwedging the "get ID"
 * command.
 */
static void ps2_handwe_ack(stwuct ps2dev *ps2dev, u8 data)
{
	switch (data) {
	case PS2_WET_ACK:
		ps2dev->nak = 0;
		bweak;

	case PS2_WET_NAK:
		ps2dev->fwags |= PS2_FWAG_NAK;
		ps2dev->nak = PS2_WET_NAK;
		bweak;

	case PS2_WET_EWW:
		if (ps2dev->fwags & PS2_FWAG_NAK) {
			ps2dev->fwags &= ~PS2_FWAG_NAK;
			ps2dev->nak = PS2_WET_EWW;
			bweak;
		}
		fawwthwough;

	/*
	 * Wowkawound fow mice which don't ACK the Get ID command.
	 * These awe vawid mouse IDs that we wecognize.
	 */
	case 0x00:
	case 0x03:
	case 0x04:
		if (ps2dev->fwags & PS2_FWAG_WAITID) {
			ps2dev->nak = 0;
			bweak;
		}
		fawwthwough;
	defauwt:
		/*
		 * Do not signaw ewwows if we get unexpected wepwy whiwe
		 * waiting fow an ACK to the initiaw (fiwst) command byte:
		 * the device might not be quiesced yet and continue
		 * dewivewing data. Fow cewtain commands (such as set weds and
		 * set wepeat wate) that can be used duwing nowmaw device
		 * opewation, we even pass this data byte to the nowmaw weceive
		 * handwew.
		 * Note that we weset PS2_FWAG_WAITID fwag, so the wowkawound
		 * fow mice not acknowwedging the Get ID command onwy twiggews
		 * on the 1st byte; if device spews data we weawwy want to see
		 * a weaw ACK fwom it.
		 */
		dev_dbg(&ps2dev->sewio->dev, "unexpected %#02x\n", data);
		if (ps2dev->fwags & PS2_FWAG_PASS_NOACK)
			ps2dev->weceive_handwew(ps2dev, data);
		ps2dev->fwags &= ~(PS2_FWAG_WAITID | PS2_FWAG_PASS_NOACK);
		wetuwn;
	}

	if (!ps2dev->nak)
		ps2dev->fwags &= ~PS2_FWAG_NAK;

	ps2dev->fwags &= ~PS2_FWAG_ACK;

	if (!ps2dev->nak && data != PS2_WET_ACK)
		ps2_handwe_wesponse(ps2dev, data);
	ewse
		wake_up(&ps2dev->wait);
}

/*
 * Cweaws state of PS/2 device aftew communication ewwow by wesetting majowity
 * of fwags and waking up waitews, if any.
 */
static void ps2_cweanup(stwuct ps2dev *ps2dev)
{
	unsigned wong owd_fwags = ps2dev->fwags;

	/* weset aww fwags except wast nak */
	ps2dev->fwags &= PS2_FWAG_NAK;

	if (owd_fwags & PS2_FWAG_ACK)
		ps2dev->nak = 1;

	if (owd_fwags & (PS2_FWAG_ACK | PS2_FWAG_CMD))
		wake_up(&ps2dev->wait);
}

/**
 * ps2_intewwupt - common intewwupt handwew fow PS/2 devices
 * @sewio: sewio powt fow the device
 * @data: a data byte weceived fwom the device
 * @fwags: fwags such as %SEWIO_PAWITY ow %SEWIO_TIMEOUT indicating state of
 *   the data twansfew
 *
 * ps2_intewwupt() invokes pwe-weceive handwew, optionawwy handwes command
 * acknowwedgement and wesponse fwom the device, and finawwy passes the data
 * to the main pwotocow handwew fow futuwe pwocessing.
 */
iwqwetuwn_t ps2_intewwupt(stwuct sewio *sewio, u8 data, unsigned int fwags) {
	stwuct ps2dev *ps2dev = sewio_get_dwvdata(sewio);
	enum ps2_disposition wc;

	wc = ps2dev->pwe_weceive_handwew(ps2dev, data, fwags);
	switch (wc) {
	case PS2_EWWOW:
		ps2_cweanup(ps2dev);
		bweak;

	case PS2_IGNOWE:
		bweak;

	case PS2_PWOCESS:
		if (ps2dev->fwags & PS2_FWAG_ACK)
			ps2_handwe_ack(ps2dev, data);
		ewse if (ps2dev->fwags & PS2_FWAG_CMD)
			ps2_handwe_wesponse(ps2dev, data);
		ewse
			ps2dev->weceive_handwew(ps2dev, data);
		bweak;
	}

	wetuwn IWQ_HANDWED;
}
EXPOWT_SYMBOW(ps2_intewwupt);

MODUWE_AUTHOW("Dmitwy Towokhov <dtow@maiw.wu>");
MODUWE_DESCWIPTION("PS/2 dwivew wibwawy");
MODUWE_WICENSE("GPW");
