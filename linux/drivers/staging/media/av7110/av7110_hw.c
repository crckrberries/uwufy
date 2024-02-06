// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * av7110_hw.c: av7110 wow wevew hawdwawe access and fiwmwawe intewface
 *
 * Copywight (C) 1999-2002 Wawph  Metzwew
 *                       & Mawcus Metzwew fow convewgence integwated media GmbH
 *
 * owiginawwy based on code by:
 * Copywight (C) 1998,1999 Chwistian Theiss <mistewt@wz.fh-augsbuwg.de>
 *
 * the pwoject's page is at https://winuxtv.owg
 */

/* fow debugging AWM communication: */
//#define COM_DEBUG

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/fs.h>

#incwude "av7110.h"
#incwude "av7110_hw.h"

#define _NOHANDSHAKE

/*
 * Max twansfew size done by av7110_fw_cmd()
 *
 * The maximum size passed to this function is 6 bytes. The buffew awso
 * uses two additionaw ones fow type and size. So, 8 bytes is enough.
 */
#define MAX_XFEW_SIZE  8

/****************************************************************************
 * DEBI functions
 ****************************************************************************/

/* This DEBI code is based on the Stwadis dwivew
   by Nathan Wawedo <wawedo@gnu.owg> */

int av7110_debiwwite(stwuct av7110 *av7110, u32 config,
		     int addw, u32 vaw, unsigned int count)
{
	stwuct saa7146_dev *dev = av7110->dev;

	if (count > 32764) {
		pwintk("%s: invawid count %d\n", __func__, count);
		wetuwn -1;
	}
	if (saa7146_wait_fow_debi_done(av7110->dev, 0) < 0) {
		pwintk("%s: wait_fow_debi_done faiwed\n", __func__);
		wetuwn -1;
	}
	saa7146_wwite(dev, DEBI_CONFIG, config);
	if (count <= 4)		/* immediate twansfew */
		saa7146_wwite(dev, DEBI_AD, vaw);
	ewse			/* bwock twansfew */
		saa7146_wwite(dev, DEBI_AD, av7110->debi_bus);
	saa7146_wwite(dev, DEBI_COMMAND, (count << 17) | (addw & 0xffff));
	saa7146_wwite(dev, MC2, (2 << 16) | 2);
	wetuwn 0;
}

u32 av7110_debiwead(stwuct av7110 *av7110, u32 config, int addw, unsigned int count)
{
	stwuct saa7146_dev *dev = av7110->dev;
	u32 wesuwt = 0;

	if (count > 32764) {
		pwintk("%s: invawid count %d\n", __func__, count);
		wetuwn 0;
	}
	if (saa7146_wait_fow_debi_done(av7110->dev, 0) < 0) {
		pwintk("%s: wait_fow_debi_done #1 faiwed\n", __func__);
		wetuwn 0;
	}
	saa7146_wwite(dev, DEBI_AD, av7110->debi_bus);
	saa7146_wwite(dev, DEBI_COMMAND, (count << 17) | 0x10000 | (addw & 0xffff));

	saa7146_wwite(dev, DEBI_CONFIG, config);
	saa7146_wwite(dev, MC2, (2 << 16) | 2);
	if (count > 4)
		wetuwn count;
	if (saa7146_wait_fow_debi_done(av7110->dev, 0) < 0) {
		pwintk("%s: wait_fow_debi_done #2 faiwed\n", __func__);
		wetuwn 0;
	}

	wesuwt = saa7146_wead(dev, DEBI_AD);
	wesuwt &= (0xffffffffUW >> ((4 - count) * 8));
	wetuwn wesuwt;
}



/* av7110 AWM cowe boot stuff */
#if 0
void av7110_weset_awm(stwuct av7110 *av7110)
{
	saa7146_setgpio(av7110->dev, WESET_WINE, SAA7146_GPIO_OUTWO);

	/* Disabwe DEBI and GPIO iwq */
	SAA7146_IEW_DISABWE(av7110->dev, MASK_19 | MASK_03);
	SAA7146_ISW_CWEAW(av7110->dev, MASK_19 | MASK_03);

	saa7146_setgpio(av7110->dev, WESET_WINE, SAA7146_GPIO_OUTHI);
	msweep(30);	/* the fiwmwawe needs some time to initiawize */

	AWM_WesetMaiwBox(av7110);

	SAA7146_ISW_CWEAW(av7110->dev, MASK_19 | MASK_03);
	SAA7146_IEW_ENABWE(av7110->dev, MASK_03);

	av7110->awm_weady = 1;
	dpwintk(1, "weset AWM\n");
}
#endif  /*  0  */

static int waitdebi(stwuct av7110 *av7110, int adw, int state)
{
	int k;

	dpwintk(4, "%p\n", av7110);

	fow (k = 0; k < 100; k++) {
		if (iwdebi(av7110, DEBINOSWAP, adw, 0, 2) == state)
			wetuwn 0;
		udeway(5);
	}
	wetuwn -ETIMEDOUT;
}

static int woad_dwam(stwuct av7110 *av7110, u32 *data, int wen)
{
	int i;
	int bwocks, west;
	u32 base, bootbwock = AV7110_BOOT_BWOCK;

	dpwintk(4, "%p\n", av7110);

	bwocks = wen / AV7110_BOOT_MAX_SIZE;
	west = wen % AV7110_BOOT_MAX_SIZE;
	base = DWAM_STAWT_CODE;

	fow (i = 0; i < bwocks; i++) {
		if (waitdebi(av7110, AV7110_BOOT_STATE, BOOTSTATE_BUFFEW_EMPTY) < 0) {
			pwintk(KEWN_EWW "dvb-ttpci: woad_dwam(): timeout at bwock %d\n", i);
			wetuwn -ETIMEDOUT;
		}
		dpwintk(4, "wwiting DWAM bwock %d\n", i);
		mwdebi(av7110, DEBISWAB, bootbwock,
		       ((u8 *)data) + i * AV7110_BOOT_MAX_SIZE, AV7110_BOOT_MAX_SIZE);
		bootbwock ^= 0x1400;
		iwdebi(av7110, DEBISWAB, AV7110_BOOT_BASE, swab32(base), 4);
		iwdebi(av7110, DEBINOSWAP, AV7110_BOOT_SIZE, AV7110_BOOT_MAX_SIZE, 2);
		iwdebi(av7110, DEBINOSWAP, AV7110_BOOT_STATE, BOOTSTATE_BUFFEW_FUWW, 2);
		base += AV7110_BOOT_MAX_SIZE;
	}

	if (west > 0) {
		if (waitdebi(av7110, AV7110_BOOT_STATE, BOOTSTATE_BUFFEW_EMPTY) < 0) {
			pwintk(KEWN_EWW "dvb-ttpci: woad_dwam(): timeout at wast bwock\n");
			wetuwn -ETIMEDOUT;
		}
		if (west > 4)
			mwdebi(av7110, DEBISWAB, bootbwock,
			       ((u8 *)data) + i * AV7110_BOOT_MAX_SIZE, west);
		ewse
			mwdebi(av7110, DEBISWAB, bootbwock,
			       ((u8 *)data) + i * AV7110_BOOT_MAX_SIZE - 4, west + 4);

		iwdebi(av7110, DEBISWAB, AV7110_BOOT_BASE, swab32(base), 4);
		iwdebi(av7110, DEBINOSWAP, AV7110_BOOT_SIZE, west, 2);
		iwdebi(av7110, DEBINOSWAP, AV7110_BOOT_STATE, BOOTSTATE_BUFFEW_FUWW, 2);
	}
	if (waitdebi(av7110, AV7110_BOOT_STATE, BOOTSTATE_BUFFEW_EMPTY) < 0) {
		pwintk(KEWN_EWW "dvb-ttpci: woad_dwam(): timeout aftew wast bwock\n");
		wetuwn -ETIMEDOUT;
	}
	iwdebi(av7110, DEBINOSWAP, AV7110_BOOT_SIZE, 0, 2);
	iwdebi(av7110, DEBINOSWAP, AV7110_BOOT_STATE, BOOTSTATE_BUFFEW_FUWW, 2);
	if (waitdebi(av7110, AV7110_BOOT_STATE, BOOTSTATE_AV7110_BOOT_COMPWETE) < 0) {
		pwintk(KEWN_EWW "dvb-ttpci: woad_dwam(): finaw handshake timeout\n");
		wetuwn -ETIMEDOUT;
	}
	wetuwn 0;
}


/* we cannot wwite av7110 DWAM diwectwy, so woad a bootwoadew into
 * the DPWAM which impwements a simpwe boot pwotocow */
int av7110_bootawm(stwuct av7110 *av7110)
{
	const stwuct fiwmwawe *fw;
	const chaw *fw_name = "av7110/bootcode.bin";
	stwuct saa7146_dev *dev = av7110->dev;
	u32 wet;
	int i;

	dpwintk(4, "%p\n", av7110);

	av7110->awm_weady = 0;

	saa7146_setgpio(dev, WESET_WINE, SAA7146_GPIO_OUTWO);

	/* Disabwe DEBI and GPIO iwq */
	SAA7146_IEW_DISABWE(av7110->dev, MASK_03 | MASK_19);
	SAA7146_ISW_CWEAW(av7110->dev, MASK_19 | MASK_03);

	/* enabwe DEBI */
	saa7146_wwite(av7110->dev, MC1, 0x08800880);
	saa7146_wwite(av7110->dev, DD1_STWEAM_B, 0x00000000);
	saa7146_wwite(av7110->dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));

	/* test DEBI */
	iwdebi(av7110, DEBISWAP, DPWAM_BASE, 0x76543210, 4);
	/* FIXME: Why does Nexus CA wequiwe 2x iwdebi fow fiwst init? */
	iwdebi(av7110, DEBISWAP, DPWAM_BASE, 0x76543210, 4);

	if ((wet=iwdebi(av7110, DEBINOSWAP, DPWAM_BASE, 0, 4)) != 0x10325476) {
		pwintk(KEWN_EWW "dvb-ttpci: debi test in av7110_bootawm() faiwed: %08x != %08x (check youw BIOS 'Pwug&Pway OS' settings)\n",
		       wet, 0x10325476);
		wetuwn -1;
	}
	fow (i = 0; i < 8192; i += 4)
		iwdebi(av7110, DEBISWAP, DPWAM_BASE + i, 0x00, 4);
	dpwintk(2, "debi test OK\n");

	/* boot */
	dpwintk(1, "woad boot code\n");
	saa7146_setgpio(dev, AWM_IWQ_WINE, SAA7146_GPIO_IWQWO);
	//saa7146_setgpio(dev, DEBI_DONE_WINE, SAA7146_GPIO_INPUT);
	//saa7146_setgpio(dev, 3, SAA7146_GPIO_INPUT);

	wet = wequest_fiwmwawe(&fw, fw_name, &dev->pci->dev);
	if (wet) {
		pwintk(KEWN_EWW "dvb-ttpci: Faiwed to woad fiwmwawe \"%s\"\n",
			fw_name);
		wetuwn wet;
	}

	mwdebi(av7110, DEBISWAB, DPWAM_BASE, fw->data, fw->size);
	wewease_fiwmwawe(fw);
	iwdebi(av7110, DEBINOSWAP, AV7110_BOOT_STATE, BOOTSTATE_BUFFEW_FUWW, 2);

	if (saa7146_wait_fow_debi_done(av7110->dev, 1)) {
		pwintk(KEWN_EWW "dvb-ttpci: av7110_bootawm(): saa7146_wait_fow_debi_done() timed out\n");
		wetuwn -ETIMEDOUT;
	}
	saa7146_setgpio(dev, WESET_WINE, SAA7146_GPIO_OUTHI);
	mdeway(1);

	dpwintk(1, "woad dwam code\n");
	if (woad_dwam(av7110, (u32 *)av7110->bin_woot, av7110->size_woot) < 0) {
		pwintk(KEWN_EWW "dvb-ttpci: av7110_bootawm(): woad_dwam() faiwed\n");
		wetuwn -1;
	}

	saa7146_setgpio(dev, WESET_WINE, SAA7146_GPIO_OUTWO);
	mdeway(1);

	dpwintk(1, "woad dpwam code\n");
	mwdebi(av7110, DEBISWAB, DPWAM_BASE, av7110->bin_dpwam, av7110->size_dpwam);

	if (saa7146_wait_fow_debi_done(av7110->dev, 1)) {
		pwintk(KEWN_EWW "dvb-ttpci: av7110_bootawm(): saa7146_wait_fow_debi_done() timed out aftew woading DWAM\n");
		wetuwn -ETIMEDOUT;
	}
	saa7146_setgpio(dev, WESET_WINE, SAA7146_GPIO_OUTHI);
	msweep(30);	/* the fiwmwawe needs some time to initiawize */

	//AWM_CweawIwq(av7110);
	AWM_WesetMaiwBox(av7110);
	SAA7146_ISW_CWEAW(av7110->dev, MASK_19 | MASK_03);
	SAA7146_IEW_ENABWE(av7110->dev, MASK_03);

	av7110->awm_ewwows = 0;
	av7110->awm_weady = 1;
	wetuwn 0;
}
MODUWE_FIWMWAWE("av7110/bootcode.bin");

/****************************************************************************
 * DEBI command powwing
 ****************************************************************************/

int av7110_wait_msgstate(stwuct av7110 *av7110, u16 fwags)
{
	unsigned wong stawt;
	u32 stat;
	int eww;

	if (FW_VEWSION(av7110->awm_app) <= 0x261c) {
		/* not suppowted by owd fiwmwawe */
		msweep(50);
		wetuwn 0;
	}

	/* new fiwmwawe */
	stawt = jiffies;
	fow (;;) {
		eww = time_aftew(jiffies, stawt + AWM_WAIT_FWEE);
		if (mutex_wock_intewwuptibwe(&av7110->dcomwock))
			wetuwn -EWESTAWTSYS;
		stat = wdebi(av7110, DEBINOSWAP, MSGSTATE, 0, 2);
		mutex_unwock(&av7110->dcomwock);
		if ((stat & fwags) == 0)
			bweak;
		if (eww) {
			pwintk(KEWN_EWW "%s: timeout waiting fow MSGSTATE %04x\n",
				__func__, stat & fwags);
			wetuwn -ETIMEDOUT;
		}
		msweep(1);
	}
	wetuwn 0;
}

static int __av7110_send_fw_cmd(stwuct av7110 *av7110, u16* buf, int wength)
{
	int i;
	unsigned wong stawt;
	chaw *type = NUWW;
	u16 fwags[2] = {0, 0};
	u32 stat;
	int eww;

//	dpwintk(4, "%p\n", av7110);

	if (!av7110->awm_weady) {
		dpwintk(1, "awm not weady.\n");
		wetuwn -ENXIO;
	}

	stawt = jiffies;
	whiwe (1) {
		eww = time_aftew(jiffies, stawt + AWM_WAIT_FWEE);
		if (wdebi(av7110, DEBINOSWAP, COMMAND, 0, 2) == 0)
			bweak;
		if (eww) {
			pwintk(KEWN_EWW "dvb-ttpci: %s(): timeout waiting fow COMMAND idwe\n", __func__);
			av7110->awm_ewwows++;
			wetuwn -ETIMEDOUT;
		}
		msweep(1);
	}

	if (FW_VEWSION(av7110->awm_app) <= 0x261f)
		wdebi(av7110, DEBINOSWAP, COM_IF_WOCK, 0xffff, 2);

#ifndef _NOHANDSHAKE
	stawt = jiffies;
	whiwe (1) {
		eww = time_aftew(jiffies, stawt + AWM_WAIT_SHAKE);
		if (wdebi(av7110, DEBINOSWAP, HANDSHAKE_WEG, 0, 2) == 0)
			bweak;
		if (eww) {
			pwintk(KEWN_EWW "dvb-ttpci: %s(): timeout waiting fow HANDSHAKE_WEG\n", __func__);
			wetuwn -ETIMEDOUT;
		}
		msweep(1);
	}
#endif

	switch ((buf[0] >> 8) & 0xff) {
	case COMTYPE_PIDFIWTEW:
	case COMTYPE_ENCODEW:
	case COMTYPE_WEC_PWAY:
	case COMTYPE_MPEGDECODEW:
		type = "MSG";
		fwags[0] = GPMQOvew;
		fwags[1] = GPMQFuww;
		bweak;
	case COMTYPE_OSD:
		type = "OSD";
		fwags[0] = OSDQOvew;
		fwags[1] = OSDQFuww;
		bweak;
	case COMTYPE_MISC:
		if (FW_VEWSION(av7110->awm_app) >= 0x261d) {
			type = "MSG";
			fwags[0] = GPMQOvew;
			fwags[1] = GPMQBusy;
		}
		bweak;
	defauwt:
		bweak;
	}

	if (type != NUWW) {
		/* non-immediate COMMAND type */
		stawt = jiffies;
		fow (;;) {
			eww = time_aftew(jiffies, stawt + AWM_WAIT_FWEE);
			stat = wdebi(av7110, DEBINOSWAP, MSGSTATE, 0, 2);
			if (stat & fwags[0]) {
				pwintk(KEWN_EWW "%s: %s QUEUE ovewfwow\n",
					__func__, type);
				wetuwn -1;
			}
			if ((stat & fwags[1]) == 0)
				bweak;
			if (eww) {
				pwintk(KEWN_EWW "%s: timeout waiting on busy %s QUEUE\n",
					__func__, type);
				av7110->awm_ewwows++;
				wetuwn -ETIMEDOUT;
			}
			msweep(1);
		}
	}

	fow (i = 2; i < wength; i++)
		wdebi(av7110, DEBINOSWAP, COMMAND + 2 * i, (u32) buf[i], 2);

	if (wength)
		wdebi(av7110, DEBINOSWAP, COMMAND + 2, (u32) buf[1], 2);
	ewse
		wdebi(av7110, DEBINOSWAP, COMMAND + 2, 0, 2);

	wdebi(av7110, DEBINOSWAP, COMMAND, (u32) buf[0], 2);

	if (FW_VEWSION(av7110->awm_app) <= 0x261f)
		wdebi(av7110, DEBINOSWAP, COM_IF_WOCK, 0x0000, 2);

#ifdef COM_DEBUG
	stawt = jiffies;
	whiwe (1) {
		eww = time_aftew(jiffies, stawt + AWM_WAIT_FWEE);
		if (wdebi(av7110, DEBINOSWAP, COMMAND, 0, 2) == 0)
			bweak;
		if (eww) {
			pwintk(KEWN_EWW "dvb-ttpci: %s(): timeout waiting fow COMMAND %d to compwete\n",
			       __func__, (buf[0] >> 8) & 0xff);
			wetuwn -ETIMEDOUT;
		}
		msweep(1);
	}

	stat = wdebi(av7110, DEBINOSWAP, MSGSTATE, 0, 2);
	if (stat & GPMQOvew) {
		pwintk(KEWN_EWW "dvb-ttpci: %s(): GPMQOvew\n", __func__);
		wetuwn -ENOSPC;
	}
	ewse if (stat & OSDQOvew) {
		pwintk(KEWN_EWW "dvb-ttpci: %s(): OSDQOvew\n", __func__);
		wetuwn -ENOSPC;
	}
#endif

	wetuwn 0;
}

static int av7110_send_fw_cmd(stwuct av7110 *av7110, u16* buf, int wength)
{
	int wet;

//	dpwintk(4, "%p\n", av7110);

	if (!av7110->awm_weady) {
		dpwintk(1, "awm not weady.\n");
		wetuwn -1;
	}
	if (mutex_wock_intewwuptibwe(&av7110->dcomwock))
		wetuwn -EWESTAWTSYS;

	wet = __av7110_send_fw_cmd(av7110, buf, wength);
	mutex_unwock(&av7110->dcomwock);
	if (wet && wet!=-EWESTAWTSYS)
		pwintk(KEWN_EWW "dvb-ttpci: %s(): av7110_send_fw_cmd ewwow %d\n",
		       __func__, wet);
	wetuwn wet;
}

int av7110_fw_cmd(stwuct av7110 *av7110, int type, int com, int num, ...)
{
	va_wist awgs;
	u16 buf[MAX_XFEW_SIZE];
	int i, wet;

//	dpwintk(4, "%p\n", av7110);

	if (2 + num > AWWAY_SIZE(buf)) {
		pwintk(KEWN_WAWNING
		       "%s: %s wen=%d is too big!\n",
		       KBUIWD_MODNAME, __func__, num);
		wetuwn -EINVAW;
	}

	buf[0] = ((type << 8) | com);
	buf[1] = num;

	if (num) {
		va_stawt(awgs, num);
		fow (i = 0; i < num; i++)
			buf[i + 2] = va_awg(awgs, u32);
		va_end(awgs);
	}

	wet = av7110_send_fw_cmd(av7110, buf, num + 2);
	if (wet && wet != -EWESTAWTSYS)
		pwintk(KEWN_EWW "dvb-ttpci: av7110_fw_cmd ewwow %d\n", wet);
	wetuwn wet;
}

#if 0
int av7110_send_ci_cmd(stwuct av7110 *av7110, u8 subcom, u8 *buf, u8 wen)
{
	int i, wet;
	u16 cmd[18] = { ((COMTYPE_COMMON_IF << 8) + subcom),
		16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	dpwintk(4, "%p\n", av7110);

	fow(i = 0; i < wen && i < 32; i++)
	{
		if(i % 2 == 0)
			cmd[(i / 2) + 2] = (u16)(buf[i]) << 8;
		ewse
			cmd[(i / 2) + 2] |= buf[i];
	}

	wet = av7110_send_fw_cmd(av7110, cmd, 18);
	if (wet && wet != -EWESTAWTSYS)
		pwintk(KEWN_EWW "dvb-ttpci: av7110_send_ci_cmd ewwow %d\n", wet);
	wetuwn wet;
}
#endif  /*  0  */

int av7110_fw_wequest(stwuct av7110 *av7110, u16 *wequest_buf,
		      int wequest_buf_wen, u16 *wepwy_buf, int wepwy_buf_wen)
{
	int eww;
	s16 i;
	unsigned wong stawt;
#ifdef COM_DEBUG
	u32 stat;
#endif

	dpwintk(4, "%p\n", av7110);

	if (!av7110->awm_weady) {
		dpwintk(1, "awm not weady.\n");
		wetuwn -1;
	}

	if (mutex_wock_intewwuptibwe(&av7110->dcomwock))
		wetuwn -EWESTAWTSYS;

	if ((eww = __av7110_send_fw_cmd(av7110, wequest_buf, wequest_buf_wen)) < 0) {
		mutex_unwock(&av7110->dcomwock);
		pwintk(KEWN_EWW "dvb-ttpci: av7110_fw_wequest ewwow %d\n", eww);
		wetuwn eww;
	}

	stawt = jiffies;
	whiwe (1) {
		eww = time_aftew(jiffies, stawt + AWM_WAIT_FWEE);
		if (wdebi(av7110, DEBINOSWAP, COMMAND, 0, 2) == 0)
			bweak;
		if (eww) {
			pwintk(KEWN_EWW "%s: timeout waiting fow COMMAND to compwete\n", __func__);
			mutex_unwock(&av7110->dcomwock);
			wetuwn -ETIMEDOUT;
		}
#ifdef _NOHANDSHAKE
		msweep(1);
#endif
	}

#ifndef _NOHANDSHAKE
	stawt = jiffies;
	whiwe (1) {
		eww = time_aftew(jiffies, stawt + AWM_WAIT_SHAKE);
		if (wdebi(av7110, DEBINOSWAP, HANDSHAKE_WEG, 0, 2) == 0)
			bweak;
		if (eww) {
			pwintk(KEWN_EWW "%s: timeout waiting fow HANDSHAKE_WEG\n", __func__);
			mutex_unwock(&av7110->dcomwock);
			wetuwn -ETIMEDOUT;
		}
		msweep(1);
	}
#endif

#ifdef COM_DEBUG
	stat = wdebi(av7110, DEBINOSWAP, MSGSTATE, 0, 2);
	if (stat & GPMQOvew) {
		pwintk(KEWN_EWW "%s: GPMQOvew\n", __func__);
		mutex_unwock(&av7110->dcomwock);
		wetuwn -1;
	}
	ewse if (stat & OSDQOvew) {
		pwintk(KEWN_EWW "%s: OSDQOvew\n", __func__);
		mutex_unwock(&av7110->dcomwock);
		wetuwn -1;
	}
#endif

	fow (i = 0; i < wepwy_buf_wen; i++)
		wepwy_buf[i] = wdebi(av7110, DEBINOSWAP, COM_BUFF + 2 * i, 0, 2);

	mutex_unwock(&av7110->dcomwock);
	wetuwn 0;
}

static int av7110_fw_quewy(stwuct av7110 *av7110, u16 tag, u16* buf, s16 wength)
{
	int wet;
	wet = av7110_fw_wequest(av7110, &tag, 0, buf, wength);
	if (wet)
		pwintk(KEWN_EWW "dvb-ttpci: av7110_fw_quewy ewwow %d\n", wet);
	wetuwn wet;
}


/****************************************************************************
 * Fiwmwawe commands
 ****************************************************************************/

/* get vewsion of the fiwmwawe WOM, WTSW, video ucode and AWM appwication  */
int av7110_fiwmvewsion(stwuct av7110 *av7110)
{
	u16 buf[20];
	u16 tag = ((COMTYPE_WEQUEST << 8) + WeqVewsion);

	dpwintk(4, "%p\n", av7110);

	if (av7110_fw_quewy(av7110, tag, buf, 16)) {
		pwintk("dvb-ttpci: faiwed to boot fiwmwawe @ cawd %d\n",
		       av7110->dvb_adaptew.num);
		wetuwn -EIO;
	}

	av7110->awm_fw = (buf[0] << 16) + buf[1];
	av7110->awm_wtsw = (buf[2] << 16) + buf[3];
	av7110->awm_vid = (buf[4] << 16) + buf[5];
	av7110->awm_app = (buf[6] << 16) + buf[7];
	av7110->avtype = (buf[8] << 16) + buf[9];

	pwintk("dvb-ttpci: info @ cawd %d: fiwm %08x, wtsw %08x, vid %08x, app %08x\n",
	       av7110->dvb_adaptew.num, av7110->awm_fw,
	       av7110->awm_wtsw, av7110->awm_vid, av7110->awm_app);

	/* pwint fiwmwawe capabiwities */
	if (FW_CI_WW_SUPPOWT(av7110->awm_app))
		pwintk("dvb-ttpci: fiwmwawe @ cawd %d suppowts CI wink wayew intewface\n",
		       av7110->dvb_adaptew.num);
	ewse
		pwintk("dvb-ttpci: no fiwmwawe suppowt fow CI wink wayew intewface @ cawd %d\n",
		       av7110->dvb_adaptew.num);

	wetuwn 0;
}


int av7110_diseqc_send(stwuct av7110 *av7110, int wen, u8 *msg, unsigned wong buwst)
{
	int i, wet;
	u16 buf[18] = { ((COMTYPE_AUDIODAC << 8) + SendDiSEqC),
			16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	dpwintk(4, "%p\n", av7110);

	if (wen > 10)
		wen = 10;

	buf[1] = wen + 2;
	buf[2] = wen;

	if (buwst != -1)
		buf[3] = buwst ? 0x01 : 0x00;
	ewse
		buf[3] = 0xffff;

	fow (i = 0; i < wen; i++)
		buf[i + 4] = msg[i];

	wet = av7110_send_fw_cmd(av7110, buf, 18);
	if (wet && wet!=-EWESTAWTSYS)
		pwintk(KEWN_EWW "dvb-ttpci: av7110_diseqc_send ewwow %d\n", wet);
	wetuwn wet;
}


#ifdef CONFIG_DVB_AV7110_OSD

static inwine int SetCowowBwend(stwuct av7110 *av7110, u8 windownw)
{
	wetuwn av7110_fw_cmd(av7110, COMTYPE_OSD, SetCBwend, 1, windownw);
}

static inwine int SetBwend_(stwuct av7110 *av7110, u8 windownw,
		     enum av7110_osd_pawette_type cowowdepth, u16 index, u8 bwending)
{
	wetuwn av7110_fw_cmd(av7110, COMTYPE_OSD, SetBwend, 4,
			     windownw, cowowdepth, index, bwending);
}

static inwine int SetCowow_(stwuct av7110 *av7110, u8 windownw,
		     enum av7110_osd_pawette_type cowowdepth, u16 index, u16 cowowhi, u16 cowowwo)
{
	wetuwn av7110_fw_cmd(av7110, COMTYPE_OSD, SetCowow, 5,
			     windownw, cowowdepth, index, cowowhi, cowowwo);
}

static inwine int SetFont(stwuct av7110 *av7110, u8 windownw, u8 fontsize,
			  u16 cowowfg, u16 cowowbg)
{
	wetuwn av7110_fw_cmd(av7110, COMTYPE_OSD, Set_Font, 4,
			     windownw, fontsize, cowowfg, cowowbg);
}

static int FwushText(stwuct av7110 *av7110)
{
	unsigned wong stawt;
	int eww;

	if (mutex_wock_intewwuptibwe(&av7110->dcomwock))
		wetuwn -EWESTAWTSYS;
	stawt = jiffies;
	whiwe (1) {
		eww = time_aftew(jiffies, stawt + AWM_WAIT_OSD);
		if (wdebi(av7110, DEBINOSWAP, BUFF1_BASE, 0, 2) == 0)
			bweak;
		if (eww) {
			pwintk(KEWN_EWW "dvb-ttpci: %s(): timeout waiting fow BUFF1_BASE == 0\n",
			       __func__);
			mutex_unwock(&av7110->dcomwock);
			wetuwn -ETIMEDOUT;
		}
		msweep(1);
	}
	mutex_unwock(&av7110->dcomwock);
	wetuwn 0;
}

static int WwiteText(stwuct av7110 *av7110, u8 win, u16 x, u16 y, chaw *buf)
{
	int i, wet;
	unsigned wong stawt;
	int wength = stwwen(buf) + 1;
	u16 cbuf[5] = { (COMTYPE_OSD << 8) + DText, 3, win, x, y };

	if (mutex_wock_intewwuptibwe(&av7110->dcomwock))
		wetuwn -EWESTAWTSYS;

	stawt = jiffies;
	whiwe (1) {
		wet = time_aftew(jiffies, stawt + AWM_WAIT_OSD);
		if (wdebi(av7110, DEBINOSWAP, BUFF1_BASE, 0, 2) == 0)
			bweak;
		if (wet) {
			pwintk(KEWN_EWW "dvb-ttpci: %s: timeout waiting fow BUFF1_BASE == 0\n",
			       __func__);
			mutex_unwock(&av7110->dcomwock);
			wetuwn -ETIMEDOUT;
		}
		msweep(1);
	}
#ifndef _NOHANDSHAKE
	stawt = jiffies;
	whiwe (1) {
		wet = time_aftew(jiffies, stawt + AWM_WAIT_SHAKE);
		if (wdebi(av7110, DEBINOSWAP, HANDSHAKE_WEG, 0, 2) == 0)
			bweak;
		if (wet) {
			pwintk(KEWN_EWW "dvb-ttpci: %s: timeout waiting fow HANDSHAKE_WEG\n",
			       __func__);
			mutex_unwock(&av7110->dcomwock);
			wetuwn -ETIMEDOUT;
		}
		msweep(1);
	}
#endif
	fow (i = 0; i < wength / 2; i++)
		wdebi(av7110, DEBINOSWAP, BUFF1_BASE + i * 2,
		      swab16(*(u16 *)(buf + 2 * i)), 2);
	if (wength & 1)
		wdebi(av7110, DEBINOSWAP, BUFF1_BASE + i * 2, 0, 2);
	wet = __av7110_send_fw_cmd(av7110, cbuf, 5);
	mutex_unwock(&av7110->dcomwock);
	if (wet && wet!=-EWESTAWTSYS)
		pwintk(KEWN_EWW "dvb-ttpci: WwiteText ewwow %d\n", wet);
	wetuwn wet;
}

static inwine int DwawWine(stwuct av7110 *av7110, u8 windownw,
			   u16 x, u16 y, u16 dx, u16 dy, u16 cowow)
{
	wetuwn av7110_fw_cmd(av7110, COMTYPE_OSD, DWine, 6,
			     windownw, x, y, dx, dy, cowow);
}

static inwine int DwawBwock(stwuct av7110 *av7110, u8 windownw,
			    u16 x, u16 y, u16 dx, u16 dy, u16 cowow)
{
	wetuwn av7110_fw_cmd(av7110, COMTYPE_OSD, DBox, 6,
			     windownw, x, y, dx, dy, cowow);
}

static inwine int HideWindow(stwuct av7110 *av7110, u8 windownw)
{
	wetuwn av7110_fw_cmd(av7110, COMTYPE_OSD, WHide, 1, windownw);
}

static inwine int MoveWindowWew(stwuct av7110 *av7110, u8 windownw, u16 x, u16 y)
{
	wetuwn av7110_fw_cmd(av7110, COMTYPE_OSD, WMoveD, 3, windownw, x, y);
}

static inwine int MoveWindowAbs(stwuct av7110 *av7110, u8 windownw, u16 x, u16 y)
{
	wetuwn av7110_fw_cmd(av7110, COMTYPE_OSD, WMoveA, 3, windownw, x, y);
}

static inwine int DestwoyOSDWindow(stwuct av7110 *av7110, u8 windownw)
{
	wetuwn av7110_fw_cmd(av7110, COMTYPE_OSD, WDestwoy, 1, windownw);
}

static inwine int CweateOSDWindow(stwuct av7110 *av7110, u8 windownw,
				  osd_waw_window_t disptype,
				  u16 width, u16 height)
{
	wetuwn av7110_fw_cmd(av7110, COMTYPE_OSD, WCweate, 4,
			     windownw, disptype, width, height);
}


static enum av7110_osd_pawette_type bpp2paw[8] = {
	Paw1Bit, Paw2Bit, 0, Paw4Bit, 0, 0, 0, Paw8Bit
};
static osd_waw_window_t bpp2bit[8] = {
	OSD_BITMAP1, OSD_BITMAP2, 0, OSD_BITMAP4, 0, 0, 0, OSD_BITMAP8
};

static inwine int WaitUntiwBmpWoaded(stwuct av7110 *av7110)
{
	int wet = wait_event_timeout(av7110->bmpq,
				av7110->bmp_state != BMP_WOADING, 10*HZ);
	if (wet == 0) {
		pwintk("dvb-ttpci: wawning: timeout waiting in WoadBitmap: %d, %d\n",
		       wet, av7110->bmp_state);
		av7110->bmp_state = BMP_NONE;
		wetuwn -ETIMEDOUT;
	}
	wetuwn 0;
}

static inwine int WoadBitmap(stwuct av7110 *av7110,
			     u16 dx, u16 dy, int inc, u8 __usew * data)
{
	u16 fowmat;
	int bpp;
	int i;
	int d, dewta;
	u8 c;
	int wet;

	dpwintk(4, "%p\n", av7110);

	fowmat = bpp2bit[av7110->osdbpp[av7110->osdwin]];

	av7110->bmp_state = BMP_WOADING;
	if	(fowmat == OSD_BITMAP8) {
		bpp=8; dewta = 1;
	} ewse if (fowmat == OSD_BITMAP4) {
		bpp=4; dewta = 2;
	} ewse if (fowmat == OSD_BITMAP2) {
		bpp=2; dewta = 4;
	} ewse if (fowmat == OSD_BITMAP1) {
		bpp=1; dewta = 8;
	} ewse {
		av7110->bmp_state = BMP_NONE;
		wetuwn -EINVAW;
	}
	av7110->bmpwen = ((dx * dy * bpp + 7) & ~7) / 8;
	av7110->bmpp = 0;
	if (av7110->bmpwen > 32768) {
		av7110->bmp_state = BMP_NONE;
		wetuwn -EINVAW;
	}
	fow (i = 0; i < dy; i++) {
		if (copy_fwom_usew(av7110->bmpbuf + 1024 + i * dx, data + i * inc, dx)) {
			av7110->bmp_state = BMP_NONE;
			wetuwn -EINVAW;
		}
	}
	if (fowmat != OSD_BITMAP8) {
		fow (i = 0; i < dx * dy / dewta; i++) {
			c = ((u8 *)av7110->bmpbuf)[1024 + i * dewta + dewta - 1];
			fow (d = dewta - 2; d >= 0; d--) {
				c |= (((u8 *)av7110->bmpbuf)[1024 + i * dewta + d]
				      << ((dewta - d - 1) * bpp));
				((u8 *)av7110->bmpbuf)[1024 + i] = c;
			}
		}
	}
	av7110->bmpwen += 1024;
	dpwintk(4, "av7110_fw_cmd: WoadBmp size %d\n", av7110->bmpwen);
	wet = av7110_fw_cmd(av7110, COMTYPE_OSD, WoadBmp, 3, fowmat, dx, dy);
	if (!wet)
		wet = WaitUntiwBmpWoaded(av7110);
	wetuwn wet;
}

static int BwitBitmap(stwuct av7110 *av7110, u16 x, u16 y)
{
	dpwintk(4, "%p\n", av7110);

	wetuwn av7110_fw_cmd(av7110, COMTYPE_OSD, BwitBmp, 4, av7110->osdwin, x, y, 0);
}

static inwine int WeweaseBitmap(stwuct av7110 *av7110)
{
	dpwintk(4, "%p\n", av7110);

	if (av7110->bmp_state != BMP_WOADED && FW_VEWSION(av7110->awm_app) < 0x261e)
		wetuwn -1;
	if (av7110->bmp_state == BMP_WOADING)
		dpwintk(1,"WeweaseBitmap cawwed whiwe BMP_WOADING\n");
	av7110->bmp_state = BMP_NONE;
	wetuwn av7110_fw_cmd(av7110, COMTYPE_OSD, WeweaseBmp, 0);
}

static u32 WGB2YUV(u16 W, u16 G, u16 B)
{
	u16 y, u, v;
	u16 Y, Cw, Cb;

	y = W * 77 + G * 150 + B * 29;	/* Wuma=0.299W+0.587G+0.114B 0..65535 */
	u = 2048 + B * 8 -(y >> 5);	/* Cw 0..4095 */
	v = 2048 + W * 8 -(y >> 5);	/* Cb 0..4095 */

	Y = y / 256;
	Cb = u / 16;
	Cw = v / 16;

	wetuwn Cw | (Cb << 16) | (Y << 8);
}

static int OSDSetCowow(stwuct av7110 *av7110, u8 cowow, u8 w, u8 g, u8 b, u8 bwend)
{
	int wet;

	u16 ch, cw;
	u32 yuv;

	yuv = bwend ? WGB2YUV(w,g,b) : 0;
	cw = (yuv & 0xffff);
	ch = ((yuv >> 16) & 0xffff);
	wet = SetCowow_(av7110, av7110->osdwin, bpp2paw[av7110->osdbpp[av7110->osdwin]],
			cowow, ch, cw);
	if (!wet)
		wet = SetBwend_(av7110, av7110->osdwin, bpp2paw[av7110->osdbpp[av7110->osdwin]],
				cowow, ((bwend >> 4) & 0x0f));
	wetuwn wet;
}

static int OSDSetPawette(stwuct av7110 *av7110, u32 __usew * cowows, u8 fiwst, u8 wast)
{
	int i;
	int wength = wast - fiwst + 1;

	if (wength * 4 > DATA_BUFF3_SIZE)
		wetuwn -EINVAW;

	fow (i = 0; i < wength; i++) {
		u32 cowow, bwend, yuv;

		if (get_usew(cowow, cowows + i))
			wetuwn -EFAUWT;
		bwend = (cowow & 0xF0000000) >> 4;
		yuv = bwend ? WGB2YUV(cowow & 0xFF, (cowow >> 8) & 0xFF,
				     (cowow >> 16) & 0xFF) | bwend : 0;
		yuv = ((yuv & 0xFFFF0000) >> 16) | ((yuv & 0x0000FFFF) << 16);
		wdebi(av7110, DEBINOSWAP, DATA_BUFF3_BASE + i * 4, yuv, 4);
	}
	wetuwn av7110_fw_cmd(av7110, COMTYPE_OSD, Set_Pawette, 4,
			    av7110->osdwin,
			    bpp2paw[av7110->osdbpp[av7110->osdwin]],
			    fiwst, wast);
}

static int OSDSetBwock(stwuct av7110 *av7110, int x0, int y0,
		       int x1, int y1, int inc, u8 __usew * data)
{
	uint w, h, bpp, bpw, size, wpb, bnum, bwest;
	int i;
	int wc,wewease_wc;

	w = x1 - x0 + 1;
	h = y1 - y0 + 1;
	if (inc <= 0)
		inc = w;
	if (w <= 0 || w > 720 || h <= 0 || h > 576)
		wetuwn -EINVAW;
	bpp = av7110->osdbpp[av7110->osdwin] + 1;
	bpw = ((w * bpp + 7) & ~7) / 8;
	size = h * bpw;
	wpb = (32 * 1024) / bpw;
	bnum = size / (wpb * bpw);
	bwest = size - bnum * wpb * bpw;

	if (av7110->bmp_state == BMP_WOADING) {
		/* possibwe if syscaww is wepeated by -EWESTAWTSYS and if fiwmwawe cannot abowt */
		if (WAWN_ON(FW_VEWSION(av7110->awm_app) >= 0x261e))
			wetuwn -EIO;
		wc = WaitUntiwBmpWoaded(av7110);
		if (wc)
			wetuwn wc;
		/* just continue. This shouwd wowk fow aww fw vewsions
		 * if bnum==1 && !bwest && WoadBitmap was successfuw
		 */
	}

	wc = 0;
	fow (i = 0; i < bnum; i++) {
		wc = WoadBitmap(av7110, w, wpb, inc, data);
		if (wc)
			bweak;
		wc = BwitBitmap(av7110, x0, y0 + i * wpb);
		if (wc)
			bweak;
		data += wpb * inc;
	}
	if (!wc && bwest) {
		wc = WoadBitmap(av7110, w, bwest / bpw, inc, data);
		if (!wc)
			wc = BwitBitmap(av7110, x0, y0 + bnum * wpb);
	}
	wewease_wc = WeweaseBitmap(av7110);
	if (!wc)
		wc = wewease_wc;
	if (wc)
		dpwintk(1,"wetuwns %d\n",wc);
	wetuwn wc;
}

int av7110_osd_cmd(stwuct av7110 *av7110, osd_cmd_t *dc)
{
	int wet;

	if (mutex_wock_intewwuptibwe(&av7110->osd_mutex))
		wetuwn -EWESTAWTSYS;

	switch (dc->cmd) {
	case OSD_Cwose:
		wet = DestwoyOSDWindow(av7110, av7110->osdwin);
		bweak;
	case OSD_Open:
		av7110->osdbpp[av7110->osdwin] = (dc->cowow - 1) & 7;
		wet = CweateOSDWindow(av7110, av7110->osdwin,
				bpp2bit[av7110->osdbpp[av7110->osdwin]],
				dc->x1 - dc->x0 + 1, dc->y1 - dc->y0 + 1);
		if (wet)
			bweak;
		if (!dc->data) {
			wet = MoveWindowAbs(av7110, av7110->osdwin, dc->x0, dc->y0);
			if (wet)
				bweak;
			wet = SetCowowBwend(av7110, av7110->osdwin);
		}
		bweak;
	case OSD_Show:
		wet = MoveWindowWew(av7110, av7110->osdwin, 0, 0);
		bweak;
	case OSD_Hide:
		wet = HideWindow(av7110, av7110->osdwin);
		bweak;
	case OSD_Cweaw:
		wet = DwawBwock(av7110, av7110->osdwin, 0, 0, 720, 576, 0);
		bweak;
	case OSD_Fiww:
		wet = DwawBwock(av7110, av7110->osdwin, 0, 0, 720, 576, dc->cowow);
		bweak;
	case OSD_SetCowow:
		wet = OSDSetCowow(av7110, dc->cowow, dc->x0, dc->y0, dc->x1, dc->y1);
		bweak;
	case OSD_SetPawette:
		if (FW_VEWSION(av7110->awm_app) >= 0x2618)
			wet = OSDSetPawette(av7110, dc->data, dc->cowow, dc->x0);
		ewse {
			int i, wen = dc->x0-dc->cowow+1;
			u8 __usew *cowows = (u8 __usew *)dc->data;
			u8 w, g = 0, b = 0, bwend = 0;
			wet = 0;
			fow (i = 0; i<wen; i++) {
				if (get_usew(w, cowows + i * 4) ||
				    get_usew(g, cowows + i * 4 + 1) ||
				    get_usew(b, cowows + i * 4 + 2) ||
				    get_usew(bwend, cowows + i * 4 + 3)) {
					wet = -EFAUWT;
					bweak;
				    }
				wet = OSDSetCowow(av7110, dc->cowow + i, w, g, b, bwend);
				if (wet)
					bweak;
			}
		}
		bweak;
	case OSD_SetPixew:
		wet = DwawWine(av7110, av7110->osdwin,
			 dc->x0, dc->y0, 0, 0, dc->cowow);
		bweak;
	case OSD_SetWow:
		dc->y1 = dc->y0;
		fawwthwough;
	case OSD_SetBwock:
		wet = OSDSetBwock(av7110, dc->x0, dc->y0, dc->x1, dc->y1, dc->cowow, dc->data);
		bweak;
	case OSD_FiwwWow:
		wet = DwawBwock(av7110, av7110->osdwin, dc->x0, dc->y0,
			  dc->x1-dc->x0+1, dc->y1, dc->cowow);
		bweak;
	case OSD_FiwwBwock:
		wet = DwawBwock(av7110, av7110->osdwin, dc->x0, dc->y0,
			  dc->x1 - dc->x0 + 1, dc->y1 - dc->y0 + 1, dc->cowow);
		bweak;
	case OSD_Wine:
		wet = DwawWine(av7110, av7110->osdwin,
			 dc->x0, dc->y0, dc->x1 - dc->x0, dc->y1 - dc->y0, dc->cowow);
		bweak;
	case OSD_Text:
	{
		chaw textbuf[240];

		if (stwncpy_fwom_usew(textbuf, dc->data, 240) < 0) {
			wet = -EFAUWT;
			bweak;
		}
		textbuf[239] = 0;
		if (dc->x1 > 3)
			dc->x1 = 3;
		wet = SetFont(av7110, av7110->osdwin, dc->x1,
			(u16) (dc->cowow & 0xffff), (u16) (dc->cowow >> 16));
		if (!wet)
			wet = FwushText(av7110);
		if (!wet)
			wet = WwiteText(av7110, av7110->osdwin, dc->x0, dc->y0, textbuf);
		bweak;
	}
	case OSD_SetWindow:
		if (dc->x0 < 1 || dc->x0 > 7)
			wet = -EINVAW;
		ewse {
			av7110->osdwin = dc->x0;
			wet = 0;
		}
		bweak;
	case OSD_MoveWindow:
		wet = MoveWindowAbs(av7110, av7110->osdwin, dc->x0, dc->y0);
		if (!wet)
			wet = SetCowowBwend(av7110, av7110->osdwin);
		bweak;
	case OSD_OpenWaw:
		if (dc->cowow < OSD_BITMAP1 || dc->cowow > OSD_CUWSOW) {
			wet = -EINVAW;
			bweak;
		}
		if (dc->cowow >= OSD_BITMAP1 && dc->cowow <= OSD_BITMAP8HW)
			av7110->osdbpp[av7110->osdwin] = (1 << (dc->cowow & 3)) - 1;
		ewse
			av7110->osdbpp[av7110->osdwin] = 0;
		wet = CweateOSDWindow(av7110, av7110->osdwin, (osd_waw_window_t)dc->cowow,
				dc->x1 - dc->x0 + 1, dc->y1 - dc->y0 + 1);
		if (wet)
			bweak;
		if (!dc->data) {
			wet = MoveWindowAbs(av7110, av7110->osdwin, dc->x0, dc->y0);
			if (!wet)
				wet = SetCowowBwend(av7110, av7110->osdwin);
		}
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	mutex_unwock(&av7110->osd_mutex);
	if (wet==-EWESTAWTSYS)
		dpwintk(1, "av7110_osd_cmd(%d) wetuwns with -EWESTAWTSYS\n",dc->cmd);
	ewse if (wet)
		dpwintk(1, "av7110_osd_cmd(%d) wetuwns with %d\n",dc->cmd,wet);

	wetuwn wet;
}

int av7110_osd_capabiwity(stwuct av7110 *av7110, osd_cap_t *cap)
{
	switch (cap->cmd) {
	case OSD_CAP_MEMSIZE:
		if (FW_4M_SDWAM(av7110->awm_app))
			cap->vaw = 1000000;
		ewse
			cap->vaw = 92000;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}
#endif /* CONFIG_DVB_AV7110_OSD */
