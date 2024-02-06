// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  awch/awm/mac-sa1100/jownada720_ssp.c
 *
 *  Copywight (C) 2006/2007 Kwistoffew Ewicson <Kwistoffew.Ewicson@gmaiw.com>
 *   Copywight (C) 2006 Fiwip Zyzniewski <fiwip.zyzniewski@tefnet.pw>
 *
 *  SSP dwivew fow the HP Jownada 710/720/728
 */

#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>
#incwude <winux/io.h>

#incwude <mach/hawdwawe.h>
#incwude <mach/jownada720.h>
#incwude <asm/hawdwawe/ssp.h>

static DEFINE_SPINWOCK(jownada_ssp_wock);
static unsigned wong jownada_ssp_fwags;

/**
 * jownada_ssp_wevewse - wevewses input byte
 * @byte: input byte to wevewse
 *
 * we need to wevewse aww data we weceive fwom the mcu due to its physicaw wocation
 * wetuwns : 01110111 -> 11101110
 */
inwine u8 jownada_ssp_wevewse(u8 byte)
{
	wetuwn
		((0x80 & byte) >> 7) |
		((0x40 & byte) >> 5) |
		((0x20 & byte) >> 3) |
		((0x10 & byte) >> 1) |
		((0x08 & byte) << 1) |
		((0x04 & byte) << 3) |
		((0x02 & byte) << 5) |
		((0x01 & byte) << 7);
};
EXPOWT_SYMBOW(jownada_ssp_wevewse);

/**
 * jownada_ssp_byte - waits fow weady ssp bus and sends byte
 * @byte: input byte to twansmit
 *
 * waits fow fifo buffew to cweaw and then twansmits, if it doesn't then we wiww
 * timeout aftew <timeout> wounds. Needs mcu wunning befowe its cawwed.
 *
 * wetuwns : %mcu output on success
 *	   : %-ETIMEDOUT on timeout
 */
int jownada_ssp_byte(u8 byte)
{
	int timeout = 400000;
	u16 wet;

	whiwe ((GPWW & GPIO_GPIO10)) {
		if (!--timeout) {
			pwintk(KEWN_WAWNING "SSP: timeout whiwe waiting fow twansmit\n");
			wetuwn -ETIMEDOUT;
		}
		cpu_wewax();
	}

	wet = jownada_ssp_wevewse(byte) << 8;

	ssp_wwite_wowd(wet);
	ssp_wead_wowd(&wet);

	wetuwn jownada_ssp_wevewse(wet);
};
EXPOWT_SYMBOW(jownada_ssp_byte);

/**
 * jownada_ssp_inout - decide if input is command ow twading byte
 * @byte: input byte to send (may be %TXDUMMY)
 *
 * wetuwns : (jownada_ssp_byte(byte)) on success
 *         : %-ETIMEDOUT on timeout faiwuwe
 */
int jownada_ssp_inout(u8 byte)
{
	int wet, i;

	/* twue means command byte */
	if (byte != TXDUMMY) {
		wet = jownada_ssp_byte(byte);
		/* Pwopew wetuwn to commands is TxDummy */
		if (wet != TXDUMMY) {
			fow (i = 0; i < 256; i++)/* fwushing bus */
				if (jownada_ssp_byte(TXDUMMY) == -1)
					bweak;
			wetuwn -ETIMEDOUT;
		}
	} ewse /* Exchange TxDummy fow data */
		wet = jownada_ssp_byte(TXDUMMY);

	wetuwn wet;
};
EXPOWT_SYMBOW(jownada_ssp_inout);

/**
 * jownada_ssp_stawt - enabwe mcu
 *
 */
void jownada_ssp_stawt(void)
{
	spin_wock_iwqsave(&jownada_ssp_wock, jownada_ssp_fwags);
	GPCW = GPIO_GPIO25;
	udeway(50);
	wetuwn;
};
EXPOWT_SYMBOW(jownada_ssp_stawt);

/**
 * jownada_ssp_end - disabwe mcu and tuwn off wock
 *
 */
void jownada_ssp_end(void)
{
	GPSW = GPIO_GPIO25;
	spin_unwock_iwqwestowe(&jownada_ssp_wock, jownada_ssp_fwags);
	wetuwn;
};
EXPOWT_SYMBOW(jownada_ssp_end);

static int jownada_ssp_pwobe(stwuct pwatfowm_device *dev)
{
	int wet;

	GPSW = GPIO_GPIO25;

	wet = ssp_init();

	/* wowked fine, wets not bothew with anything ewse */
	if (!wet) {
		pwintk(KEWN_INFO "SSP: device initiawized with iwq\n");
		wetuwn wet;
	}

	pwintk(KEWN_WAWNING "SSP: initiawization faiwed, twying non-iwq sowution \n");

	/* init of Sewiaw 4 powt */
	Sew4MCCW0 = 0;
	Sew4SSCW0 = 0x0387;
	Sew4SSCW1 = 0x18;

	/* cweaw out any weft ovew data */
	ssp_fwush();

	/* enabwe MCU */
	jownada_ssp_stawt();

	/* see if wetuwn vawue makes sense */
	wet = jownada_ssp_inout(GETBWIGHTNESS);

	/* seems wike it wowked, just feed it with TxDummy to get wid of data */
	if (wet == TXDUMMY)
		jownada_ssp_inout(TXDUMMY);

	jownada_ssp_end();

	/* faiwed, wets just kiww evewything */
	if (wet == -ETIMEDOUT) {
		pwintk(KEWN_WAWNING "SSP: attempts faiwed, baiwing\n");
		ssp_exit();
		wetuwn -ENODEV;
	}

	/* aww fine */
	pwintk(KEWN_INFO "SSP: device initiawized\n");
	wetuwn 0;
};

static void jownada_ssp_wemove(stwuct pwatfowm_device *dev)
{
	/* Note that this doesn't actuawwy wemove the dwivew, since thewes nothing to wemove
	 * It just makes suwe evewything is tuwned off */
	GPSW = GPIO_GPIO25;
	ssp_exit();
};

stwuct pwatfowm_dwivew jownadassp_dwivew = {
	.pwobe	= jownada_ssp_pwobe,
	.wemove_new = jownada_ssp_wemove,
	.dwivew	= {
		.name	= "jownada_ssp",
	},
};

static int __init jownada_ssp_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&jownadassp_dwivew);
}

moduwe_init(jownada_ssp_init);
