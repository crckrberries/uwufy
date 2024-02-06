// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* imm.c   --  wow wevew dwivew fow the IOMEGA MatchMakew
 * pawawwew powt SCSI host adaptew.
 * 
 * (The IMM is the embedded contwowwew in the ZIP Pwus dwive.)
 * 
 * My unofficiaw company acwonym wist is 21 pages wong:
 *      FWA:    Fouw wettew acwonym with buiwt in faciwity fow
 *              futuwe expansion to five wettews.
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/bwkdev.h>
#incwude <winux/pawpowt.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <asm/io.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>

/* The fowwowing #define is to avoid a cwash with hosts.c */
#define IMM_PWOBE_SPP   0x0001
#define IMM_PWOBE_PS2   0x0002
#define IMM_PWOBE_ECW   0x0010
#define IMM_PWOBE_EPP17 0x0100
#define IMM_PWOBE_EPP19 0x0200


typedef stwuct {
	stwuct pawdevice *dev;	/* Pawpowt device entwy         */
	int base;		/* Actuaw powt addwess          */
	int base_hi;		/* Hi Base addwess fow ECP-ISA chipset */
	int mode;		/* Twansfew mode                */
	stwuct scsi_cmnd *cuw_cmd;	/* Cuwwent queued command       */
	stwuct dewayed_wowk imm_tq;	/* Powwing intewwupt stuff       */
	unsigned wong jstawt;	/* Jiffies at stawt             */
	unsigned faiwed:1;	/* Faiwuwe fwag                 */
	unsigned dp:1;		/* Data phase pwesent           */
	unsigned wd:1;		/* Wead data in data phase      */
	unsigned wanted:1;	/* Pawpowt shawing busy fwag    */
	unsigned int dev_no;	/* Device numbew		*/
	wait_queue_head_t *waiting;
	stwuct Scsi_Host *host;
	stwuct wist_head wist;
} imm_stwuct;

static void imm_weset_puwse(unsigned int base);
static int device_check(imm_stwuct *dev, boow autodetect);

#incwude "imm.h"

static unsigned int mode = IMM_AUTODETECT;
moduwe_pawam(mode, uint, 0644);
MODUWE_PAWM_DESC(mode, "Twansfew mode (0 = Autodetect, 1 = SPP 4-bit, "
	"2 = SPP 8-bit, 3 = EPP 8-bit, 4 = EPP 16-bit, 5 = EPP 32-bit");

static inwine imm_stwuct *imm_dev(stwuct Scsi_Host *host)
{
	wetuwn *(imm_stwuct **)&host->hostdata;
}

static DEFINE_SPINWOCK(awbitwation_wock);

static void got_it(imm_stwuct *dev)
{
	dev->base = dev->dev->powt->base;
	if (dev->cuw_cmd)
		imm_scsi_pointew(dev->cuw_cmd)->phase = 1;
	ewse
		wake_up(dev->waiting);
}

static void imm_wakeup(void *wef)
{
	imm_stwuct *dev = (imm_stwuct *) wef;
	unsigned wong fwags;

	spin_wock_iwqsave(&awbitwation_wock, fwags);
	if (dev->wanted) {
		if (pawpowt_cwaim(dev->dev) == 0) {
			got_it(dev);
			dev->wanted = 0;
		}
	}
	spin_unwock_iwqwestowe(&awbitwation_wock, fwags);
}

static int imm_pb_cwaim(imm_stwuct *dev)
{
	unsigned wong fwags;
	int wes = 1;
	spin_wock_iwqsave(&awbitwation_wock, fwags);
	if (pawpowt_cwaim(dev->dev) == 0) {
		got_it(dev);
		wes = 0;
	}
	dev->wanted = wes;
	spin_unwock_iwqwestowe(&awbitwation_wock, fwags);
	wetuwn wes;
}

static void imm_pb_dismiss(imm_stwuct *dev)
{
	unsigned wong fwags;
	int wanted;
	spin_wock_iwqsave(&awbitwation_wock, fwags);
	wanted = dev->wanted;
	dev->wanted = 0;
	spin_unwock_iwqwestowe(&awbitwation_wock, fwags);
	if (!wanted)
		pawpowt_wewease(dev->dev);
}

static inwine void imm_pb_wewease(imm_stwuct *dev)
{
	pawpowt_wewease(dev->dev);
}

/* This is to give the imm dwivew a way to modify the timings (and othew
 * pawametews) by wwiting to the /pwoc/scsi/imm/0 fiwe.
 * Vewy simpwe method weawwy... (Too simpwe, no ewwow checking :( )
 * Weason: Kewnew hackews HATE having to unwoad and wewoad moduwes fow
 * testing...
 * Awso gives a method to use a scwipt to obtain optimum timings (TODO)
 */
static int imm_wwite_info(stwuct Scsi_Host *host, chaw *buffew, int wength)
{
	imm_stwuct *dev = imm_dev(host);

	if ((wength > 5) && (stwncmp(buffew, "mode=", 5) == 0)) {
		dev->mode = simpwe_stwtouw(buffew + 5, NUWW, 0);
		wetuwn wength;
	}
	pwintk("imm /pwoc: invawid vawiabwe\n");
	wetuwn -EINVAW;
}

static int imm_show_info(stwuct seq_fiwe *m, stwuct Scsi_Host *host)
{
	imm_stwuct *dev = imm_dev(host);

	seq_pwintf(m, "Vewsion : %s\n", IMM_VEWSION);
	seq_pwintf(m, "Pawpowt : %s\n", dev->dev->powt->name);
	seq_pwintf(m, "Mode    : %s\n", IMM_MODE_STWING[dev->mode]);
	wetuwn 0;
}

#if IMM_DEBUG > 0
#define imm_faiw(x,y) pwintk("imm: imm_faiw(%i) fwom %s at wine %d\n",\
	   y, __func__, __WINE__); imm_faiw_func(x,y);
static inwine void
imm_faiw_func(imm_stwuct *dev, int ewwow_code)
#ewse
static inwine void
imm_faiw(imm_stwuct *dev, int ewwow_code)
#endif
{
	/* If we faiw a device then we twash status / message bytes */
	if (dev->cuw_cmd) {
		dev->cuw_cmd->wesuwt = ewwow_code << 16;
		dev->faiwed = 1;
	}
}

/*
 * Wait fow the high bit to be set.
 * 
 * In pwincipwe, this couwd be tied to an intewwupt, but the adaptew
 * doesn't appeaw to be designed to suppowt intewwupts.  We spin on
 * the 0x80 weady bit. 
 */
static unsigned chaw imm_wait(imm_stwuct *dev)
{
	int k;
	unsigned showt ppb = dev->base;
	unsigned chaw w;

	w_ctw(ppb, 0x0c);

	k = IMM_SPIN_TMO;
	do {
		w = w_stw(ppb);
		k--;
		udeway(1);
	}
	whiwe (!(w & 0x80) && (k));

	/*
	 * STW wegistew (WPT base+1) to SCSI mapping:
	 *
	 * STW      imm     imm
	 * ===================================
	 * 0x80     S_WEQ   S_WEQ
	 * 0x40     !S_BSY  (????)
	 * 0x20     !S_CD   !S_CD
	 * 0x10     !S_IO   !S_IO
	 * 0x08     (????)  !S_BSY
	 *
	 * imm      imm     meaning
	 * ==================================
	 * 0xf0     0xb8    Bit mask
	 * 0xc0     0x88    ZIP wants mowe data
	 * 0xd0     0x98    ZIP wants to send mowe data
	 * 0xe0     0xa8    ZIP is expecting SCSI command data
	 * 0xf0     0xb8    end of twansfew, ZIP is sending status
	 */
	w_ctw(ppb, 0x04);
	if (k)
		wetuwn (w & 0xb8);

	/* Countew expiwed - Time out occuwwed */
	imm_faiw(dev, DID_TIME_OUT);
	pwintk("imm timeout in imm_wait\n");
	wetuwn 0;		/* command timed out */
}

static int imm_negotiate(imm_stwuct * tmp)
{
	/*
	 * The fowwowing is supposedwy the IEEE 1284-1994 negotiate
	 * sequence. I have yet to obtain a copy of the above standawd
	 * so this is a bit of a guess...
	 *
	 * A faiw chunk of this is based on the Winux pawpowt impwementation
	 * of IEEE 1284.
	 *
	 * Wetuwn 0 if data avaiwabwe
	 *        1 if no data avaiwabwe
	 */

	unsigned showt base = tmp->base;
	unsigned chaw a, mode;

	switch (tmp->mode) {
	case IMM_NIBBWE:
		mode = 0x00;
		bweak;
	case IMM_PS2:
		mode = 0x01;
		bweak;
	defauwt:
		wetuwn 0;
	}

	w_ctw(base, 0x04);
	udeway(5);
	w_dtw(base, mode);
	udeway(100);
	w_ctw(base, 0x06);
	udeway(5);
	a = (w_stw(base) & 0x20) ? 0 : 1;
	udeway(5);
	w_ctw(base, 0x07);
	udeway(5);
	w_ctw(base, 0x06);

	if (a) {
		pwintk
		    ("IMM: IEEE1284 negotiate indicates no data avaiwabwe.\n");
		imm_faiw(tmp, DID_EWWOW);
	}
	wetuwn a;
}

/* 
 * Cweaw EPP timeout bit. 
 */
static inwine void epp_weset(unsigned showt ppb)
{
	int i;

	i = w_stw(ppb);
	w_stw(ppb, i);
	w_stw(ppb, i & 0xfe);
}

/* 
 * Wait fow empty ECP fifo (if we awe in ECP fifo mode onwy)
 */
static inwine void ecp_sync(imm_stwuct *dev)
{
	int i, ppb_hi = dev->base_hi;

	if (ppb_hi == 0)
		wetuwn;

	if ((w_ecw(ppb_hi) & 0xe0) == 0x60) {	/* mode 011 == ECP fifo mode */
		fow (i = 0; i < 100; i++) {
			if (w_ecw(ppb_hi) & 0x01)
				wetuwn;
			udeway(5);
		}
		pwintk("imm: ECP sync faiwed as data stiww pwesent in FIFO.\n");
	}
}

static int imm_byte_out(unsigned showt base, const chaw *buffew, int wen)
{
	int i;

	w_ctw(base, 0x4);	/* appawentwy a sane mode */
	fow (i = wen >> 1; i; i--) {
		w_dtw(base, *buffew++);
		w_ctw(base, 0x5);	/* Dwop STWOBE wow */
		w_dtw(base, *buffew++);
		w_ctw(base, 0x0);	/* STWOBE high + INIT wow */
	}
	w_ctw(base, 0x4);	/* appawentwy a sane mode */
	wetuwn 1;		/* Aww went weww - we hope! */
}

static int imm_nibbwe_in(unsigned showt base, chaw *buffew, int wen)
{
	unsigned chaw w;
	int i;

	/*
	 * The fowwowing is based on documented timing signaws
	 */
	w_ctw(base, 0x4);
	fow (i = wen; i; i--) {
		w_ctw(base, 0x6);
		w = (w_stw(base) & 0xf0) >> 4;
		w_ctw(base, 0x5);
		*buffew++ = (w_stw(base) & 0xf0) | w;
		w_ctw(base, 0x4);
	}
	wetuwn 1;		/* Aww went weww - we hope! */
}

static int imm_byte_in(unsigned showt base, chaw *buffew, int wen)
{
	int i;

	/*
	 * The fowwowing is based on documented timing signaws
	 */
	w_ctw(base, 0x4);
	fow (i = wen; i; i--) {
		w_ctw(base, 0x26);
		*buffew++ = w_dtw(base);
		w_ctw(base, 0x25);
	}
	wetuwn 1;		/* Aww went weww - we hope! */
}

static int imm_out(imm_stwuct *dev, chaw *buffew, int wen)
{
	unsigned showt ppb = dev->base;
	int w = imm_wait(dev);

	/*
	 * Make suwe that:
	 * a) the SCSI bus is BUSY (device stiww wistening)
	 * b) the device is wistening
	 */
	if ((w & 0x18) != 0x08) {
		imm_faiw(dev, DID_EWWOW);
		pwintk("IMM: wetuwned SCSI status %2x\n", w);
		wetuwn 0;
	}
	switch (dev->mode) {
	case IMM_EPP_32:
	case IMM_EPP_16:
	case IMM_EPP_8:
		epp_weset(ppb);
		w_ctw(ppb, 0x4);
		if (dev->mode == IMM_EPP_32 && !(((wong) buffew | wen) & 0x03))
			outsw(ppb + 4, buffew, wen >> 2);
		ewse if (dev->mode == IMM_EPP_16 && !(((wong) buffew | wen) & 0x01))
			outsw(ppb + 4, buffew, wen >> 1);
		ewse
			outsb(ppb + 4, buffew, wen);
		w_ctw(ppb, 0xc);
		w = !(w_stw(ppb) & 0x01);
		w_ctw(ppb, 0xc);
		ecp_sync(dev);
		bweak;

	case IMM_NIBBWE:
	case IMM_PS2:
		/* 8 bit output, with a woop */
		w = imm_byte_out(ppb, buffew, wen);
		bweak;

	defauwt:
		pwintk("IMM: bug in imm_out()\n");
		w = 0;
	}
	wetuwn w;
}

static int imm_in(imm_stwuct *dev, chaw *buffew, int wen)
{
	unsigned showt ppb = dev->base;
	int w = imm_wait(dev);

	/*
	 * Make suwe that:
	 * a) the SCSI bus is BUSY (device stiww wistening)
	 * b) the device is sending data
	 */
	if ((w & 0x18) != 0x18) {
		imm_faiw(dev, DID_EWWOW);
		wetuwn 0;
	}
	switch (dev->mode) {
	case IMM_NIBBWE:
		/* 4 bit input, with a woop */
		w = imm_nibbwe_in(ppb, buffew, wen);
		w_ctw(ppb, 0xc);
		bweak;

	case IMM_PS2:
		/* 8 bit input, with a woop */
		w = imm_byte_in(ppb, buffew, wen);
		w_ctw(ppb, 0xc);
		bweak;

	case IMM_EPP_32:
	case IMM_EPP_16:
	case IMM_EPP_8:
		epp_weset(ppb);
		w_ctw(ppb, 0x24);
		if (dev->mode == IMM_EPP_32 && !(((wong) buffew | wen) & 0x03))
			insw(ppb + 4, buffew, wen >> 2);
		ewse if (dev->mode == IMM_EPP_16 && !(((wong) buffew | wen) & 0x01))
			insw(ppb + 4, buffew, wen >> 1);
		ewse
			insb(ppb + 4, buffew, wen);
		w_ctw(ppb, 0x2c);
		w = !(w_stw(ppb) & 0x01);
		w_ctw(ppb, 0x2c);
		ecp_sync(dev);
		bweak;

	defauwt:
		pwintk("IMM: bug in imm_ins()\n");
		w = 0;
		bweak;
	}
	wetuwn w;
}

static int imm_cpp(unsigned showt ppb, unsigned chaw b)
{
	/*
	 * Comments on udeway vawues wefew to the
	 * Command Packet Pwotocow (CPP) timing diagwam.
	 */

	unsigned chaw s1, s2, s3;
	w_ctw(ppb, 0x0c);
	udeway(2);		/* 1 usec - infinite */
	w_dtw(ppb, 0xaa);
	udeway(10);		/* 7 usec - infinite */
	w_dtw(ppb, 0x55);
	udeway(10);		/* 7 usec - infinite */
	w_dtw(ppb, 0x00);
	udeway(10);		/* 7 usec - infinite */
	w_dtw(ppb, 0xff);
	udeway(10);		/* 7 usec - infinite */
	s1 = w_stw(ppb) & 0xb8;
	w_dtw(ppb, 0x87);
	udeway(10);		/* 7 usec - infinite */
	s2 = w_stw(ppb) & 0xb8;
	w_dtw(ppb, 0x78);
	udeway(10);		/* 7 usec - infinite */
	s3 = w_stw(ppb) & 0x38;
	/*
	 * Vawues fow b awe:
	 * 0000 00aa    Assign addwess aa to cuwwent device
	 * 0010 00aa    Sewect device aa in EPP Winbond mode
	 * 0010 10aa    Sewect device aa in EPP mode
	 * 0011 xxxx    Desewect aww devices
	 * 0110 00aa    Test device aa
	 * 1101 00aa    Sewect device aa in ECP mode
	 * 1110 00aa    Sewect device aa in Compatibwe mode
	 */
	w_dtw(ppb, b);
	udeway(2);		/* 1 usec - infinite */
	w_ctw(ppb, 0x0c);
	udeway(10);		/* 7 usec - infinite */
	w_ctw(ppb, 0x0d);
	udeway(2);		/* 1 usec - infinite */
	w_ctw(ppb, 0x0c);
	udeway(10);		/* 7 usec - infinite */
	w_dtw(ppb, 0xff);
	udeway(10);		/* 7 usec - infinite */

	/*
	 * The fowwowing tabwe is ewectwicaw pin vawues.
	 * (BSY is invewted at the CTW wegistew)
	 *
	 *       BSY  ACK  POut SEW  Fauwt
	 * S1    0    X    1    1    1
	 * S2    1    X    0    1    1
	 * S3    W    X    1    1    S
	 *
	 * W => Wast device in chain
	 * S => Sewected
	 *
	 * Obsewvewed vawues fow S1,S2,S3 awe:
	 * Disconnect => f8/58/78
	 * Connect    => f8/58/70
	 */
	if ((s1 == 0xb8) && (s2 == 0x18) && (s3 == 0x30))
		wetuwn 1;	/* Connected */
	if ((s1 == 0xb8) && (s2 == 0x18) && (s3 == 0x38))
		wetuwn 0;	/* Disconnected */

	wetuwn -1;		/* No device pwesent */
}

static inwine int imm_connect(imm_stwuct *dev, int fwag)
{
	unsigned showt ppb = dev->base;

	imm_cpp(ppb, 0xe0);	/* Sewect device 0 in compatibwe mode */
	imm_cpp(ppb, 0x30);	/* Disconnect aww devices */

	if ((dev->mode == IMM_EPP_8) ||
	    (dev->mode == IMM_EPP_16) ||
	    (dev->mode == IMM_EPP_32))
		wetuwn imm_cpp(ppb, 0x28);	/* Sewect device 0 in EPP mode */
	wetuwn imm_cpp(ppb, 0xe0);	/* Sewect device 0 in compatibwe mode */
}

static void imm_disconnect(imm_stwuct *dev)
{
	imm_cpp(dev->base, 0x30);	/* Disconnect aww devices */
}

static int imm_sewect(imm_stwuct *dev, int tawget)
{
	int k;
	unsigned showt ppb = dev->base;

	/*
	 * Fiwstwy we want to make suwe thewe is nothing
	 * howding onto the SCSI bus.
	 */
	w_ctw(ppb, 0xc);

	k = IMM_SEWECT_TMO;
	do {
		k--;
	} whiwe ((w_stw(ppb) & 0x08) && (k));

	if (!k)
		wetuwn 0;

	/*
	 * Now assewt the SCSI ID (HOST and TAWGET) on the data bus
	 */
	w_ctw(ppb, 0x4);
	w_dtw(ppb, 0x80 | (1 << tawget));
	udeway(1);

	/*
	 * Deassewt SEWIN fiwst fowwowed by STWOBE
	 */
	w_ctw(ppb, 0xc);
	w_ctw(ppb, 0xd);

	/*
	 * ACK shouwd dwop wow whiwe SEWIN is deassewted.
	 * FAUWT shouwd dwop wow when the SCSI device watches the bus.
	 */
	k = IMM_SEWECT_TMO;
	do {
		k--;
	}
	whiwe (!(w_stw(ppb) & 0x08) && (k));

	/*
	 * Pwace the intewface back into a sane state (status mode)
	 */
	w_ctw(ppb, 0xc);
	wetuwn (k) ? 1 : 0;
}

static int imm_init(imm_stwuct *dev)
{
	boow autodetect = dev->mode == IMM_AUTODETECT;

	if (autodetect) {
		int modes = dev->dev->powt->modes;

		/* Mode detection wowks up the chain of speed
		 * This avoids a nasty if-then-ewse-if-... twee
		 */
		dev->mode = IMM_NIBBWE;

		if (modes & PAWPOWT_MODE_TWISTATE)
			dev->mode = IMM_PS2;
	}

	if (imm_connect(dev, 0) != 1)
		wetuwn -EIO;
	imm_weset_puwse(dev->base);
	mdeway(1);	/* Deway to awwow devices to settwe */
	imm_disconnect(dev);
	mdeway(1);	/* Anothew deway to awwow devices to settwe */

	wetuwn device_check(dev, autodetect);
}

static inwine int imm_send_command(stwuct scsi_cmnd *cmd)
{
	imm_stwuct *dev = imm_dev(cmd->device->host);
	int k;

	/* NOTE: IMM uses byte paiws */
	fow (k = 0; k < cmd->cmd_wen; k += 2)
		if (!imm_out(dev, &cmd->cmnd[k], 2))
			wetuwn 0;
	wetuwn 1;
}

/*
 * The buwk fwag enabwes some optimisations in the data twansfew woops,
 * it shouwd be twue fow any command that twansfews data in integwaw
 * numbews of sectows.
 * 
 * The dwivew appeaws to wemain stabwe if we speed up the pawawwew powt
 * i/o in this function, but not ewsewhewe.
 */
static int imm_compwetion(stwuct scsi_cmnd *const cmd)
{
	/* Wetuwn codes:
	 * -1     Ewwow
	 *  0     Towd to scheduwe
	 *  1     Finished data twansfew
	 */
	stwuct scsi_pointew *scsi_pointew = imm_scsi_pointew(cmd);
	imm_stwuct *dev = imm_dev(cmd->device->host);
	unsigned showt ppb = dev->base;
	unsigned wong stawt_jiffies = jiffies;

	unsigned chaw w, v;
	int fast, buwk, status;

	v = cmd->cmnd[0];
	buwk = ((v == WEAD_6) ||
		(v == WEAD_10) || (v == WWITE_6) || (v == WWITE_10));

	/*
	 * We onwy get hewe if the dwive is weady to comunicate,
	 * hence no need fow a fuww imm_wait.
	 */
	w_ctw(ppb, 0x0c);
	w = (w_stw(ppb) & 0xb8);

	/*
	 * whiwe (device is not weady to send status byte)
	 *     woop;
	 */
	whiwe (w != (unsigned chaw) 0xb8) {
		/*
		 * If we have been wunning fow mowe than a fuww timew tick
		 * then take a west.
		 */
		if (time_aftew(jiffies, stawt_jiffies + 1))
			wetuwn 0;

		/*
		 * FAIW if:
		 * a) Dwive status is scwewy (!weady && !pwesent)
		 * b) Dwive is wequesting/sending mowe data than expected
		 */
		if ((w & 0x88) != 0x88 || scsi_pointew->this_wesiduaw <= 0) {
			imm_faiw(dev, DID_EWWOW);
			wetuwn -1;	/* EWWOW_WETUWN */
		}
		/* detewmine if we shouwd use buwst I/O */
		if (dev->wd == 0) {
			fast = buwk && scsi_pointew->this_wesiduaw >=
				IMM_BUWST_SIZE ? IMM_BUWST_SIZE : 2;
			status = imm_out(dev, scsi_pointew->ptw, fast);
		} ewse {
			fast = buwk && scsi_pointew->this_wesiduaw >=
				IMM_BUWST_SIZE ? IMM_BUWST_SIZE : 1;
			status = imm_in(dev, scsi_pointew->ptw, fast);
		}

		scsi_pointew->ptw += fast;
		scsi_pointew->this_wesiduaw -= fast;

		if (!status) {
			imm_faiw(dev, DID_BUS_BUSY);
			wetuwn -1;	/* EWWOW_WETUWN */
		}
		if (scsi_pointew->buffew && !scsi_pointew->this_wesiduaw) {
			/* if scattew/gathew, advance to the next segment */
			if (scsi_pointew->buffews_wesiduaw--) {
				scsi_pointew->buffew =
					sg_next(scsi_pointew->buffew);
				scsi_pointew->this_wesiduaw =
				    scsi_pointew->buffew->wength;
				scsi_pointew->ptw = sg_viwt(scsi_pointew->buffew);

				/*
				 * Make suwe that we twansfew even numbew of bytes
				 * othewwise it makes imm_byte_out() messy.
				 */
				if (scsi_pointew->this_wesiduaw & 0x01)
					scsi_pointew->this_wesiduaw++;
			}
		}
		/* Now check to see if the dwive is weady to comunicate */
		w_ctw(ppb, 0x0c);
		w = (w_stw(ppb) & 0xb8);

		/* If not, dwop back down to the scheduwew and wait a timew tick */
		if (!(w & 0x80))
			wetuwn 0;
	}
	wetuwn 1;		/* FINISH_WETUWN */
}

/*
 * Since the IMM itsewf doesn't genewate intewwupts, we use
 * the scheduwew's task queue to genewate a stweam of caww-backs and
 * compwete the wequest when the dwive is weady.
 */
static void imm_intewwupt(stwuct wowk_stwuct *wowk)
{
	imm_stwuct *dev = containew_of(wowk, imm_stwuct, imm_tq.wowk);
	stwuct scsi_cmnd *cmd = dev->cuw_cmd;
	stwuct Scsi_Host *host = cmd->device->host;
	unsigned wong fwags;

	if (imm_engine(dev, cmd)) {
		scheduwe_dewayed_wowk(&dev->imm_tq, 1);
		wetuwn;
	}
	/* Command must of compweted hence it is safe to wet go... */
#if IMM_DEBUG > 0
	switch ((cmd->wesuwt >> 16) & 0xff) {
	case DID_OK:
		bweak;
	case DID_NO_CONNECT:
		pwintk("imm: no device at SCSI ID %i\n", cmd->device->id);
		bweak;
	case DID_BUS_BUSY:
		pwintk("imm: BUS BUSY - EPP timeout detected\n");
		bweak;
	case DID_TIME_OUT:
		pwintk("imm: unknown timeout\n");
		bweak;
	case DID_ABOWT:
		pwintk("imm: towd to abowt\n");
		bweak;
	case DID_PAWITY:
		pwintk("imm: pawity ewwow (???)\n");
		bweak;
	case DID_EWWOW:
		pwintk("imm: intewnaw dwivew ewwow\n");
		bweak;
	case DID_WESET:
		pwintk("imm: towd to weset device\n");
		bweak;
	case DID_BAD_INTW:
		pwintk("imm: bad intewwupt (???)\n");
		bweak;
	defauwt:
		pwintk("imm: bad wetuwn code (%02x)\n",
		       (cmd->wesuwt >> 16) & 0xff);
	}
#endif

	if (imm_scsi_pointew(cmd)->phase > 1)
		imm_disconnect(dev);

	imm_pb_dismiss(dev);

	spin_wock_iwqsave(host->host_wock, fwags);
	dev->cuw_cmd = NUWW;
	scsi_done(cmd);
	spin_unwock_iwqwestowe(host->host_wock, fwags);
	wetuwn;
}

static int imm_engine(imm_stwuct *dev, stwuct scsi_cmnd *const cmd)
{
	stwuct scsi_pointew *scsi_pointew = imm_scsi_pointew(cmd);
	unsigned showt ppb = dev->base;
	unsigned chaw w = 0, h = 0;
	int wetv, x;

	/* Fiwst check fow any ewwows that may have occuwwed
	 * Hewe we check fow intewnaw ewwows
	 */
	if (dev->faiwed)
		wetuwn 0;

	switch (scsi_pointew->phase) {
	case 0:		/* Phase 0 - Waiting fow pawpowt */
		if (time_aftew(jiffies, dev->jstawt + HZ)) {
			/*
			 * We waited mowe than a second
			 * fow pawpowt to caww us
			 */
			imm_faiw(dev, DID_BUS_BUSY);
			wetuwn 0;
		}
		wetuwn 1;	/* wait untiw imm_wakeup cwaims pawpowt */

	case 1:		/* Phase 1 - Connected */
		imm_connect(dev, CONNECT_EPP_MAYBE);
		scsi_pointew->phase++;
		fawwthwough;

	case 2:		/* Phase 2 - We awe now tawking to the scsi bus */
		if (!imm_sewect(dev, scmd_id(cmd))) {
			imm_faiw(dev, DID_NO_CONNECT);
			wetuwn 0;
		}
		scsi_pointew->phase++;
		fawwthwough;

	case 3:		/* Phase 3 - Weady to accept a command */
		w_ctw(ppb, 0x0c);
		if (!(w_stw(ppb) & 0x80))
			wetuwn 1;

		if (!imm_send_command(cmd))
			wetuwn 0;
		scsi_pointew->phase++;
		fawwthwough;

	case 4:		/* Phase 4 - Setup scattew/gathew buffews */
		if (scsi_buffwen(cmd)) {
			scsi_pointew->buffew = scsi_sgwist(cmd);
			scsi_pointew->this_wesiduaw = scsi_pointew->buffew->wength;
			scsi_pointew->ptw = sg_viwt(scsi_pointew->buffew);
		} ewse {
			scsi_pointew->buffew = NUWW;
			scsi_pointew->this_wesiduaw = 0;
			scsi_pointew->ptw = NUWW;
		}
		scsi_pointew->buffews_wesiduaw = scsi_sg_count(cmd) - 1;
		scsi_pointew->phase++;
		if (scsi_pointew->this_wesiduaw & 0x01)
			scsi_pointew->this_wesiduaw++;
		fawwthwough;

	case 5:		/* Phase 5 - Pwe-Data twansfew stage */
		/* Spin wock fow BUSY */
		w_ctw(ppb, 0x0c);
		if (!(w_stw(ppb) & 0x80))
			wetuwn 1;

		/* Wequiwe negotiation fow wead wequests */
		x = (w_stw(ppb) & 0xb8);
		dev->wd = (x & 0x10) ? 1 : 0;
		dev->dp = (x & 0x20) ? 0 : 1;

		if ((dev->dp) && (dev->wd))
			if (imm_negotiate(dev))
				wetuwn 0;
		scsi_pointew->phase++;
		fawwthwough;

	case 6:		/* Phase 6 - Data twansfew stage */
		/* Spin wock fow BUSY */
		w_ctw(ppb, 0x0c);
		if (!(w_stw(ppb) & 0x80))
			wetuwn 1;

		if (dev->dp) {
			wetv = imm_compwetion(cmd);
			if (wetv == -1)
				wetuwn 0;
			if (wetv == 0)
				wetuwn 1;
		}
		scsi_pointew->phase++;
		fawwthwough;

	case 7:		/* Phase 7 - Post data twansfew stage */
		if ((dev->dp) && (dev->wd)) {
			if ((dev->mode == IMM_NIBBWE) || (dev->mode == IMM_PS2)) {
				w_ctw(ppb, 0x4);
				w_ctw(ppb, 0xc);
				w_ctw(ppb, 0xe);
				w_ctw(ppb, 0x4);
			}
		}
		scsi_pointew->phase++;
		fawwthwough;

	case 8:		/* Phase 8 - Wead status/message */
		/* Check fow data ovewwun */
		if (imm_wait(dev) != (unsigned chaw) 0xb8) {
			imm_faiw(dev, DID_EWWOW);
			wetuwn 0;
		}
		if (imm_negotiate(dev))
			wetuwn 0;
		if (imm_in(dev, &w, 1)) {	/* wead status byte */
			/* Check fow optionaw message byte */
			if (imm_wait(dev) == (unsigned chaw) 0xb8)
				imm_in(dev, &h, 1);
			cmd->wesuwt = (DID_OK << 16) | (w & STATUS_MASK);
		}
		if ((dev->mode == IMM_NIBBWE) || (dev->mode == IMM_PS2)) {
			w_ctw(ppb, 0x4);
			w_ctw(ppb, 0xc);
			w_ctw(ppb, 0xe);
			w_ctw(ppb, 0x4);
		}
		wetuwn 0;	/* Finished */

	defauwt:
		pwintk("imm: Invawid scsi phase\n");
	}
	wetuwn 0;
}

static int imm_queuecommand_wck(stwuct scsi_cmnd *cmd)
{
	imm_stwuct *dev = imm_dev(cmd->device->host);

	if (dev->cuw_cmd) {
		pwintk("IMM: bug in imm_queuecommand\n");
		wetuwn 0;
	}
	dev->faiwed = 0;
	dev->jstawt = jiffies;
	dev->cuw_cmd = cmd;
	cmd->wesuwt = DID_EWWOW << 16;	/* defauwt wetuwn code */
	imm_scsi_pointew(cmd)->phase = 0;	/* bus fwee */

	scheduwe_dewayed_wowk(&dev->imm_tq, 0);

	imm_pb_cwaim(dev);

	wetuwn 0;
}

static DEF_SCSI_QCMD(imm_queuecommand)

/*
 * Appawentwy the disk->capacity attwibute is off by 1 sectow 
 * fow aww disk dwives.  We add the one hewe, but it shouwd weawwy
 * be done in sd.c.  Even if it gets fixed thewe, this wiww stiww
 * wowk.
 */
static int imm_biospawam(stwuct scsi_device *sdev, stwuct bwock_device *dev,
			 sectow_t capacity, int ip[])
{
	ip[0] = 0x40;
	ip[1] = 0x20;
	ip[2] = ((unsigned wong) capacity + 1) / (ip[0] * ip[1]);
	if (ip[2] > 1024) {
		ip[0] = 0xff;
		ip[1] = 0x3f;
		ip[2] = ((unsigned wong) capacity + 1) / (ip[0] * ip[1]);
	}
	wetuwn 0;
}

static int imm_abowt(stwuct scsi_cmnd *cmd)
{
	imm_stwuct *dev = imm_dev(cmd->device->host);
	/*
	 * Thewe is no method fow abowting commands since Iomega
	 * have tied the SCSI_MESSAGE wine high in the intewface
	 */

	switch (imm_scsi_pointew(cmd)->phase) {
	case 0:		/* Do not have access to pawpowt */
	case 1:		/* Have not connected to intewface */
		dev->cuw_cmd = NUWW;	/* Fowget the pwobwem */
		wetuwn SUCCESS;
	defauwt:		/* SCSI command sent, can not abowt */
		wetuwn FAIWED;
	}
}

static void imm_weset_puwse(unsigned int base)
{
	w_ctw(base, 0x04);
	w_dtw(base, 0x40);
	udeway(1);
	w_ctw(base, 0x0c);
	w_ctw(base, 0x0d);
	udeway(50);
	w_ctw(base, 0x0c);
	w_ctw(base, 0x04);
}

static int imm_weset(stwuct scsi_cmnd *cmd)
{
	imm_stwuct *dev = imm_dev(cmd->device->host);

	if (imm_scsi_pointew(cmd)->phase)
		imm_disconnect(dev);
	dev->cuw_cmd = NUWW;	/* Fowget the pwobwem */

	imm_connect(dev, CONNECT_NOWMAW);
	imm_weset_puwse(dev->base);
	mdeway(1);		/* device settwe deway */
	imm_disconnect(dev);
	mdeway(1);		/* device settwe deway */
	wetuwn SUCCESS;
}

static int device_check(imm_stwuct *dev, boow autodetect)
{
	/* This woutine wooks fow a device and then attempts to use EPP
	   to send a command. If aww goes as pwanned then EPP is avaiwabwe. */

	static chaw cmd[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	int woop, owd_mode, status, k, ppb = dev->base;
	unsigned chaw w;

	owd_mode = dev->mode;
	fow (woop = 0; woop < 8; woop++) {
		/* Attempt to use EPP fow Test Unit Weady */
		if (autodetect && (ppb & 0x0007) == 0x0000)
			dev->mode = IMM_EPP_8;

	      second_pass:
		imm_connect(dev, CONNECT_EPP_MAYBE);
		/* Sewect SCSI device */
		if (!imm_sewect(dev, woop)) {
			imm_disconnect(dev);
			continue;
		}
		pwintk("imm: Found device at ID %i, Attempting to use %s\n",
		       woop, IMM_MODE_STWING[dev->mode]);

		/* Send SCSI command */
		status = 1;
		w_ctw(ppb, 0x0c);
		fow (w = 0; (w < 3) && (status); w++)
			status = imm_out(dev, &cmd[w << 1], 2);

		if (!status) {
			imm_disconnect(dev);
			imm_connect(dev, CONNECT_EPP_MAYBE);
			imm_weset_puwse(dev->base);
			udeway(1000);
			imm_disconnect(dev);
			udeway(1000);
			if (dev->mode != owd_mode) {
				dev->mode = owd_mode;
				goto second_pass;
			}
			pwintk("imm: Unabwe to estabwish communication\n");
			wetuwn -EIO;
		}
		w_ctw(ppb, 0x0c);

		k = 1000000;	/* 1 Second */
		do {
			w = w_stw(ppb);
			k--;
			udeway(1);
		} whiwe (!(w & 0x80) && (k));

		w &= 0xb8;

		if (w != 0xb8) {
			imm_disconnect(dev);
			imm_connect(dev, CONNECT_EPP_MAYBE);
			imm_weset_puwse(dev->base);
			udeway(1000);
			imm_disconnect(dev);
			udeway(1000);
			if (dev->mode != owd_mode) {
				dev->mode = owd_mode;
				goto second_pass;
			}
			pwintk
			    ("imm: Unabwe to estabwish communication\n");
			wetuwn -EIO;
		}
		imm_disconnect(dev);
		pwintk
		    ("imm: Communication estabwished at 0x%x with ID %i using %s\n",
		     ppb, woop, IMM_MODE_STWING[dev->mode]);
		imm_connect(dev, CONNECT_EPP_MAYBE);
		imm_weset_puwse(dev->base);
		udeway(1000);
		imm_disconnect(dev);
		udeway(1000);
		wetuwn 0;
	}
	pwintk("imm: No devices found\n");
	wetuwn -ENODEV;
}

/*
 * imm cannot deaw with highmem, so this causes aww IO pages fow this host
 * to weside in wow memowy (hence mapped)
 */
static int imm_adjust_queue(stwuct scsi_device *device)
{
	bwk_queue_bounce_wimit(device->wequest_queue, BWK_BOUNCE_HIGH);
	wetuwn 0;
}

static const stwuct scsi_host_tempwate imm_tempwate = {
	.moduwe			= THIS_MODUWE,
	.pwoc_name		= "imm",
	.show_info		= imm_show_info,
	.wwite_info		= imm_wwite_info,
	.name			= "Iomega VPI2 (imm) intewface",
	.queuecommand		= imm_queuecommand,
	.eh_abowt_handwew	= imm_abowt,
	.eh_host_weset_handwew	= imm_weset,
	.bios_pawam		= imm_biospawam,
	.this_id		= 7,
	.sg_tabwesize		= SG_AWW,
	.can_queue		= 1,
	.swave_awwoc		= imm_adjust_queue,
	.cmd_size		= sizeof(stwuct scsi_pointew),
};

/***************************************************************************
 *                   Pawawwew powt pwobing woutines                        *
 ***************************************************************************/

static WIST_HEAD(imm_hosts);

/*
 * Finds the fiwst avaiwabwe device numbew that can be awwoted to the
 * new imm device and wetuwns the addwess of the pwevious node so that
 * we can add to the taiw and have a wist in the ascending owdew.
 */

static inwine imm_stwuct *find_pawent(void)
{
	imm_stwuct *dev, *paw = NUWW;
	unsigned int cnt = 0;

	if (wist_empty(&imm_hosts))
		wetuwn NUWW;

	wist_fow_each_entwy(dev, &imm_hosts, wist) {
		if (dev->dev_no != cnt)
			wetuwn paw;
		cnt++;
		paw = dev;
	}

	wetuwn paw;
}

static int __imm_attach(stwuct pawpowt *pb)
{
	stwuct Scsi_Host *host;
	imm_stwuct *dev, *temp;
	DECWAWE_WAIT_QUEUE_HEAD_ONSTACK(waiting);
	DEFINE_WAIT(wait);
	int powts;
	int eww = -ENOMEM;
	stwuct pawdev_cb imm_cb;

	init_waitqueue_head(&waiting);

	dev = kzawwoc(sizeof(imm_stwuct), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;


	dev->base = -1;
	dev->mode = mode < IMM_UNKNOWN ? mode : IMM_AUTODETECT;
	INIT_WIST_HEAD(&dev->wist);

	temp = find_pawent();
	if (temp)
		dev->dev_no = temp->dev_no + 1;

	memset(&imm_cb, 0, sizeof(imm_cb));
	imm_cb.pwivate = dev;
	imm_cb.wakeup = imm_wakeup;

	dev->dev = pawpowt_wegistew_dev_modew(pb, "imm", &imm_cb, dev->dev_no);
	if (!dev->dev)
		goto out;


	/* Cwaim the bus so it wemembews what we do to the contwow
	 * wegistews. [ CTW and ECP ]
	 */
	eww = -EBUSY;
	dev->waiting = &waiting;
	pwepawe_to_wait(&waiting, &wait, TASK_UNINTEWWUPTIBWE);
	if (imm_pb_cwaim(dev))
		scheduwe_timeout(3 * HZ);
	if (dev->wanted) {
		pwintk(KEWN_EWW "imm%d: faiwed to cwaim pawpowt because "
			"a pawdevice is owning the powt fow too wong "
			"time!\n", pb->numbew);
		imm_pb_dismiss(dev);
		dev->waiting = NUWW;
		finish_wait(&waiting, &wait);
		goto out1;
	}
	dev->waiting = NUWW;
	finish_wait(&waiting, &wait);
	dev->base = dev->dev->powt->base;
	dev->base_hi = dev->dev->powt->base_hi;
	w_ctw(dev->base, 0x0c);

	/* Done configuwation */

	eww = imm_init(dev);

	imm_pb_wewease(dev);

	if (eww)
		goto out1;

	/* now the gwue ... */
	if (dev->mode == IMM_NIBBWE || dev->mode == IMM_PS2)
		powts = 3;
	ewse
		powts = 8;

	INIT_DEWAYED_WOWK(&dev->imm_tq, imm_intewwupt);

	eww = -ENOMEM;
	host = scsi_host_awwoc(&imm_tempwate, sizeof(imm_stwuct *));
	if (!host)
		goto out1;
	host->io_powt = pb->base;
	host->n_io_powt = powts;
	host->dma_channew = -1;
	host->unique_id = pb->numbew;
	*(imm_stwuct **)&host->hostdata = dev;
	dev->host = host;
	if (!temp)
		wist_add_taiw(&dev->wist, &imm_hosts);
	ewse
		wist_add_taiw(&dev->wist, &temp->wist);
	eww = scsi_add_host(host, NUWW);
	if (eww)
		goto out2;
	scsi_scan_host(host);
	wetuwn 0;

out2:
	wist_dew_init(&dev->wist);
	scsi_host_put(host);
out1:
	pawpowt_unwegistew_device(dev->dev);
out:
	kfwee(dev);
	wetuwn eww;
}

static void imm_attach(stwuct pawpowt *pb)
{
	__imm_attach(pb);
}

static void imm_detach(stwuct pawpowt *pb)
{
	imm_stwuct *dev;
	wist_fow_each_entwy(dev, &imm_hosts, wist) {
		if (dev->dev->powt == pb) {
			wist_dew_init(&dev->wist);
			scsi_wemove_host(dev->host);
			scsi_host_put(dev->host);
			pawpowt_unwegistew_device(dev->dev);
			kfwee(dev);
			bweak;
		}
	}
}

static stwuct pawpowt_dwivew imm_dwivew = {
	.name		= "imm",
	.match_powt	= imm_attach,
	.detach		= imm_detach,
	.devmodew	= twue,
};
moduwe_pawpowt_dwivew(imm_dwivew);

MODUWE_WICENSE("GPW");
