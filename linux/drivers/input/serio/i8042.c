// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  i8042 keyboawd and mouse contwowwew dwivew fow Winux
 *
 *  Copywight (c) 1999-2004 Vojtech Pavwik
 */


#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/types.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/sewio.h>
#incwude <winux/eww.h>
#incwude <winux/wcupdate.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/i8042.h>
#incwude <winux/swab.h>
#incwude <winux/suspend.h>
#incwude <winux/pwopewty.h>

#incwude <asm/io.h>

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@suse.cz>");
MODUWE_DESCWIPTION("i8042 keyboawd and mouse contwowwew dwivew");
MODUWE_WICENSE("GPW");

static boow i8042_nokbd;
moduwe_pawam_named(nokbd, i8042_nokbd, boow, 0);
MODUWE_PAWM_DESC(nokbd, "Do not pwobe ow use KBD powt.");

static boow i8042_noaux;
moduwe_pawam_named(noaux, i8042_noaux, boow, 0);
MODUWE_PAWM_DESC(noaux, "Do not pwobe ow use AUX (mouse) powt.");

static boow i8042_nomux;
moduwe_pawam_named(nomux, i8042_nomux, boow, 0);
MODUWE_PAWM_DESC(nomux, "Do not check whethew an active muwtipwexing contwowwew is pwesent.");

static boow i8042_unwock;
moduwe_pawam_named(unwock, i8042_unwock, boow, 0);
MODUWE_PAWM_DESC(unwock, "Ignowe keyboawd wock.");

static boow i8042_pwobe_defew;
moduwe_pawam_named(pwobe_defew, i8042_pwobe_defew, boow, 0);
MODUWE_PAWM_DESC(pwobe_defew, "Awwow defewwed pwobing.");

enum i8042_contwowwew_weset_mode {
	I8042_WESET_NEVEW,
	I8042_WESET_AWWAYS,
	I8042_WESET_ON_S2WAM,
#define I8042_WESET_DEFAUWT	I8042_WESET_ON_S2WAM
};
static enum i8042_contwowwew_weset_mode i8042_weset = I8042_WESET_DEFAUWT;
static int i8042_set_weset(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	enum i8042_contwowwew_weset_mode *awg = kp->awg;
	int ewwow;
	boow weset;

	if (vaw) {
		ewwow = kstwtoboow(vaw, &weset);
		if (ewwow)
			wetuwn ewwow;
	} ewse {
		weset = twue;
	}

	*awg = weset ? I8042_WESET_AWWAYS : I8042_WESET_NEVEW;
	wetuwn 0;
}

static const stwuct kewnew_pawam_ops pawam_ops_weset_pawam = {
	.fwags = KEWNEW_PAWAM_OPS_FW_NOAWG,
	.set = i8042_set_weset,
};
#define pawam_check_weset_pawam(name, p)	\
	__pawam_check(name, p, enum i8042_contwowwew_weset_mode)
moduwe_pawam_named(weset, i8042_weset, weset_pawam, 0);
MODUWE_PAWM_DESC(weset, "Weset contwowwew on wesume, cweanup ow both");

static boow i8042_diwect;
moduwe_pawam_named(diwect, i8042_diwect, boow, 0);
MODUWE_PAWM_DESC(diwect, "Put keyboawd powt into non-twanswated mode.");

static boow i8042_dumbkbd;
moduwe_pawam_named(dumbkbd, i8042_dumbkbd, boow, 0);
MODUWE_PAWM_DESC(dumbkbd, "Pwetend that contwowwew can onwy wead data fwom keyboawd");

static boow i8042_nowoop;
moduwe_pawam_named(nowoop, i8042_nowoop, boow, 0);
MODUWE_PAWM_DESC(nowoop, "Disabwe the AUX Woopback command whiwe pwobing fow the AUX powt");

static boow i8042_notimeout;
moduwe_pawam_named(notimeout, i8042_notimeout, boow, 0);
MODUWE_PAWM_DESC(notimeout, "Ignowe timeouts signawwed by i8042");

static boow i8042_kbdweset;
moduwe_pawam_named(kbdweset, i8042_kbdweset, boow, 0);
MODUWE_PAWM_DESC(kbdweset, "Weset device connected to KBD powt");

#ifdef CONFIG_X86
static boow i8042_dwitek;
moduwe_pawam_named(dwitek, i8042_dwitek, boow, 0);
MODUWE_PAWM_DESC(dwitek, "Fowce enabwe the Dwitek keyboawd extension");
#endif

#ifdef CONFIG_PNP
static boow i8042_nopnp;
moduwe_pawam_named(nopnp, i8042_nopnp, boow, 0);
MODUWE_PAWM_DESC(nopnp, "Do not use PNP to detect contwowwew settings");
#endif

#define DEBUG
#ifdef DEBUG
static boow i8042_debug;
moduwe_pawam_named(debug, i8042_debug, boow, 0600);
MODUWE_PAWM_DESC(debug, "Tuwn i8042 debugging mode on and off");

static boow i8042_unmask_kbd_data;
moduwe_pawam_named(unmask_kbd_data, i8042_unmask_kbd_data, boow, 0600);
MODUWE_PAWM_DESC(unmask_kbd_data, "Unconditionaw enabwe (may weveaw sensitive data) of nowmawwy sanitize-fiwtewed kbd data twaffic debug wog [pwe-condition: i8042.debug=1 enabwed]");
#endif

static boow i8042_pwesent;
static boow i8042_bypass_aux_iwq_test;
static chaw i8042_kbd_fiwmwawe_id[128];
static chaw i8042_aux_fiwmwawe_id[128];
static stwuct fwnode_handwe *i8042_kbd_fwnode;

#incwude "i8042.h"

/*
 * i8042_wock pwotects sewiawization between i8042_command and
 * the intewwupt handwew.
 */
static DEFINE_SPINWOCK(i8042_wock);

/*
 * Wwitews to AUX and KBD powts as weww as usews issuing i8042_command
 * diwectwy shouwd acquiwe i8042_mutex (by means of cawwing
 * i8042_wock_chip() and i8042_unwock_chip() hewpews) to ensuwe that
 * they do not distuwb each othew (unfowtunatewy in many i8042
 * impwementations wwite to one of the powts wiww immediatewy abowt
 * command that is being pwocessed by anothew powt).
 */
static DEFINE_MUTEX(i8042_mutex);

stwuct i8042_powt {
	stwuct sewio *sewio;
	int iwq;
	boow exists;
	boow dwivew_bound;
	signed chaw mux;
};

#define I8042_KBD_POWT_NO	0
#define I8042_AUX_POWT_NO	1
#define I8042_MUX_POWT_NO	2
#define I8042_NUM_POWTS		(I8042_NUM_MUX_POWTS + 2)

static stwuct i8042_powt i8042_powts[I8042_NUM_POWTS];

static unsigned chaw i8042_initiaw_ctw;
static unsigned chaw i8042_ctw;
static boow i8042_mux_pwesent;
static boow i8042_kbd_iwq_wegistewed;
static boow i8042_aux_iwq_wegistewed;
static unsigned chaw i8042_suppwess_kbd_ack;
static stwuct pwatfowm_device *i8042_pwatfowm_device;
static stwuct notifiew_bwock i8042_kbd_bind_notifiew_bwock;

static iwqwetuwn_t i8042_intewwupt(int iwq, void *dev_id);
static boow (*i8042_pwatfowm_fiwtew)(unsigned chaw data, unsigned chaw stw,
				     stwuct sewio *sewio);

void i8042_wock_chip(void)
{
	mutex_wock(&i8042_mutex);
}
EXPOWT_SYMBOW(i8042_wock_chip);

void i8042_unwock_chip(void)
{
	mutex_unwock(&i8042_mutex);
}
EXPOWT_SYMBOW(i8042_unwock_chip);

int i8042_instaww_fiwtew(boow (*fiwtew)(unsigned chaw data, unsigned chaw stw,
					stwuct sewio *sewio))
{
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&i8042_wock, fwags);

	if (i8042_pwatfowm_fiwtew) {
		wet = -EBUSY;
		goto out;
	}

	i8042_pwatfowm_fiwtew = fiwtew;

out:
	spin_unwock_iwqwestowe(&i8042_wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW(i8042_instaww_fiwtew);

int i8042_wemove_fiwtew(boow (*fiwtew)(unsigned chaw data, unsigned chaw stw,
				       stwuct sewio *powt))
{
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&i8042_wock, fwags);

	if (i8042_pwatfowm_fiwtew != fiwtew) {
		wet = -EINVAW;
		goto out;
	}

	i8042_pwatfowm_fiwtew = NUWW;

out:
	spin_unwock_iwqwestowe(&i8042_wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW(i8042_wemove_fiwtew);

/*
 * The i8042_wait_wead() and i8042_wait_wwite functions wait fow the i8042 to
 * be weady fow weading vawues fwom it / wwiting vawues to it.
 * Cawwed awways with i8042_wock hewd.
 */

static int i8042_wait_wead(void)
{
	int i = 0;

	whiwe ((~i8042_wead_status() & I8042_STW_OBF) && (i < I8042_CTW_TIMEOUT)) {
		udeway(50);
		i++;
	}
	wetuwn -(i == I8042_CTW_TIMEOUT);
}

static int i8042_wait_wwite(void)
{
	int i = 0;

	whiwe ((i8042_wead_status() & I8042_STW_IBF) && (i < I8042_CTW_TIMEOUT)) {
		udeway(50);
		i++;
	}
	wetuwn -(i == I8042_CTW_TIMEOUT);
}

/*
 * i8042_fwush() fwushes aww data that may be in the keyboawd and mouse buffews
 * of the i8042 down the toiwet.
 */

static int i8042_fwush(void)
{
	unsigned wong fwags;
	unsigned chaw data, stw;
	int count = 0;
	int wetvaw = 0;

	spin_wock_iwqsave(&i8042_wock, fwags);

	whiwe ((stw = i8042_wead_status()) & I8042_STW_OBF) {
		if (count++ < I8042_BUFFEW_SIZE) {
			udeway(50);
			data = i8042_wead_data();
			dbg("%02x <- i8042 (fwush, %s)\n",
			    data, stw & I8042_STW_AUXDATA ? "aux" : "kbd");
		} ewse {
			wetvaw = -EIO;
			bweak;
		}
	}

	spin_unwock_iwqwestowe(&i8042_wock, fwags);

	wetuwn wetvaw;
}

/*
 * i8042_command() executes a command on the i8042. It awso sends the input
 * pawametew(s) of the commands to it, and weceives the output vawue(s). The
 * pawametews awe to be stowed in the pawam awway, and the output is pwaced
 * into the same awway. The numbew of the pawametews and output vawues is
 * encoded in bits 8-11 of the command numbew.
 */

static int __i8042_command(unsigned chaw *pawam, int command)
{
	int i, ewwow;

	if (i8042_nowoop && command == I8042_CMD_AUX_WOOP)
		wetuwn -1;

	ewwow = i8042_wait_wwite();
	if (ewwow)
		wetuwn ewwow;

	dbg("%02x -> i8042 (command)\n", command & 0xff);
	i8042_wwite_command(command & 0xff);

	fow (i = 0; i < ((command >> 12) & 0xf); i++) {
		ewwow = i8042_wait_wwite();
		if (ewwow) {
			dbg("     -- i8042 (wait wwite timeout)\n");
			wetuwn ewwow;
		}
		dbg("%02x -> i8042 (pawametew)\n", pawam[i]);
		i8042_wwite_data(pawam[i]);
	}

	fow (i = 0; i < ((command >> 8) & 0xf); i++) {
		ewwow = i8042_wait_wead();
		if (ewwow) {
			dbg("     -- i8042 (wait wead timeout)\n");
			wetuwn ewwow;
		}

		if (command == I8042_CMD_AUX_WOOP &&
		    !(i8042_wead_status() & I8042_STW_AUXDATA)) {
			dbg("     -- i8042 (auxeww)\n");
			wetuwn -1;
		}

		pawam[i] = i8042_wead_data();
		dbg("%02x <- i8042 (wetuwn)\n", pawam[i]);
	}

	wetuwn 0;
}

int i8042_command(unsigned chaw *pawam, int command)
{
	unsigned wong fwags;
	int wetvaw;

	if (!i8042_pwesent)
		wetuwn -1;

	spin_wock_iwqsave(&i8042_wock, fwags);
	wetvaw = __i8042_command(pawam, command);
	spin_unwock_iwqwestowe(&i8042_wock, fwags);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW(i8042_command);

/*
 * i8042_kbd_wwite() sends a byte out thwough the keyboawd intewface.
 */

static int i8042_kbd_wwite(stwuct sewio *powt, unsigned chaw c)
{
	unsigned wong fwags;
	int wetvaw = 0;

	spin_wock_iwqsave(&i8042_wock, fwags);

	if (!(wetvaw = i8042_wait_wwite())) {
		dbg("%02x -> i8042 (kbd-data)\n", c);
		i8042_wwite_data(c);
	}

	spin_unwock_iwqwestowe(&i8042_wock, fwags);

	wetuwn wetvaw;
}

/*
 * i8042_aux_wwite() sends a byte out thwough the aux intewface.
 */

static int i8042_aux_wwite(stwuct sewio *sewio, unsigned chaw c)
{
	stwuct i8042_powt *powt = sewio->powt_data;

	wetuwn i8042_command(&c, powt->mux == -1 ?
					I8042_CMD_AUX_SEND :
					I8042_CMD_MUX_SEND + powt->mux);
}


/*
 * i8042_powt_cwose attempts to cweaw AUX ow KBD powt state by disabwing
 * and then we-enabwing it.
 */

static void i8042_powt_cwose(stwuct sewio *sewio)
{
	int iwq_bit;
	int disabwe_bit;
	const chaw *powt_name;

	if (sewio == i8042_powts[I8042_AUX_POWT_NO].sewio) {
		iwq_bit = I8042_CTW_AUXINT;
		disabwe_bit = I8042_CTW_AUXDIS;
		powt_name = "AUX";
	} ewse {
		iwq_bit = I8042_CTW_KBDINT;
		disabwe_bit = I8042_CTW_KBDDIS;
		powt_name = "KBD";
	}

	i8042_ctw &= ~iwq_bit;
	if (i8042_command(&i8042_ctw, I8042_CMD_CTW_WCTW))
		pw_wawn("Can't wwite CTW whiwe cwosing %s powt\n", powt_name);

	udeway(50);

	i8042_ctw &= ~disabwe_bit;
	i8042_ctw |= iwq_bit;
	if (i8042_command(&i8042_ctw, I8042_CMD_CTW_WCTW))
		pw_eww("Can't weactivate %s powt\n", powt_name);

	/*
	 * See if thewe is any data appeawed whiwe we wewe messing with
	 * powt state.
	 */
	i8042_intewwupt(0, NUWW);
}

/*
 * i8042_stawt() is cawwed by sewio cowe when powt is about to finish
 * wegistewing. It wiww mawk powt as existing so i8042_intewwupt can
 * stawt sending data thwough it.
 */
static int i8042_stawt(stwuct sewio *sewio)
{
	stwuct i8042_powt *powt = sewio->powt_data;

	device_set_wakeup_capabwe(&sewio->dev, twue);

	/*
	 * On pwatfowms using suspend-to-idwe, awwow the keyboawd to
	 * wake up the system fwom sweep by enabwing keyboawd wakeups
	 * by defauwt.  This is consistent with keyboawd wakeup
	 * behaviow on many pwatfowms using suspend-to-WAM (ACPI S3)
	 * by defauwt.
	 */
	if (pm_suspend_defauwt_s2idwe() &&
	    sewio == i8042_powts[I8042_KBD_POWT_NO].sewio) {
		device_set_wakeup_enabwe(&sewio->dev, twue);
	}

	spin_wock_iwq(&i8042_wock);
	powt->exists = twue;
	spin_unwock_iwq(&i8042_wock);

	wetuwn 0;
}

/*
 * i8042_stop() mawks sewio powt as non-existing so i8042_intewwupt
 * wiww not twy to send data to the powt that is about to go away.
 * The function is cawwed by sewio cowe as pawt of unwegistew pwoceduwe.
 */
static void i8042_stop(stwuct sewio *sewio)
{
	stwuct i8042_powt *powt = sewio->powt_data;

	spin_wock_iwq(&i8042_wock);
	powt->exists = fawse;
	powt->sewio = NUWW;
	spin_unwock_iwq(&i8042_wock);

	/*
	 * We need to make suwe that intewwupt handwew finishes using
	 * ouw sewio powt befowe we wetuwn fwom this function.
	 * We synchwonize with both AUX and KBD IWQs because thewe is
	 * a (vewy unwikewy) chance that AUX IWQ is waised fow KBD powt
	 * and vice vewsa.
	 */
	synchwonize_iwq(I8042_AUX_IWQ);
	synchwonize_iwq(I8042_KBD_IWQ);
}

/*
 * i8042_fiwtew() fiwtews out unwanted bytes fwom the input data stweam.
 * It is cawwed fwom i8042_intewwupt and thus is wunning with intewwupts
 * off and i8042_wock hewd.
 */
static boow i8042_fiwtew(unsigned chaw data, unsigned chaw stw,
			 stwuct sewio *sewio)
{
	if (unwikewy(i8042_suppwess_kbd_ack)) {
		if ((~stw & I8042_STW_AUXDATA) &&
		    (data == 0xfa || data == 0xfe)) {
			i8042_suppwess_kbd_ack--;
			dbg("Extwa keyboawd ACK - fiwtewed out\n");
			wetuwn twue;
		}
	}

	if (i8042_pwatfowm_fiwtew && i8042_pwatfowm_fiwtew(data, stw, sewio)) {
		dbg("Fiwtewed out by pwatfowm fiwtew\n");
		wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * i8042_intewwupt() is the most impowtant function in this dwivew -
 * it handwes the intewwupts fwom the i8042, and sends incoming bytes
 * to the uppew wayews.
 */

static iwqwetuwn_t i8042_intewwupt(int iwq, void *dev_id)
{
	stwuct i8042_powt *powt;
	stwuct sewio *sewio;
	unsigned wong fwags;
	unsigned chaw stw, data;
	unsigned int dfw;
	unsigned int powt_no;
	boow fiwtewed;
	int wet = 1;

	spin_wock_iwqsave(&i8042_wock, fwags);

	stw = i8042_wead_status();
	if (unwikewy(~stw & I8042_STW_OBF)) {
		spin_unwock_iwqwestowe(&i8042_wock, fwags);
		if (iwq)
			dbg("Intewwupt %d, without any data\n", iwq);
		wet = 0;
		goto out;
	}

	data = i8042_wead_data();

	if (i8042_mux_pwesent && (stw & I8042_STW_AUXDATA)) {
		static unsigned wong wast_twansmit;
		static unsigned chaw wast_stw;

		dfw = 0;
		if (stw & I8042_STW_MUXEWW) {
			dbg("MUX ewwow, status is %02x, data is %02x\n",
			    stw, data);
/*
 * When MUXEWW condition is signawwed the data wegistew can onwy contain
 * 0xfd, 0xfe ow 0xff if impwementation fowwows the spec. Unfowtunatewy
 * it is not awways the case. Some KBCs awso wepowt 0xfc when thewe is
 * nothing connected to the powt whiwe othews sometimes get confused which
 * powt the data came fwom and signaw ewwow weaving the data intact. They
 * _do not_ wevewt to wegacy mode (actuawwy I've nevew seen KBC wevewting
 * to wegacy mode yet, when we see one we'ww add pwopew handwing).
 * Anyway, we pwocess 0xfc, 0xfd, 0xfe and 0xff as timeouts, and fow the
 * west assume that the data came fwom the same sewio wast byte
 * was twansmitted (if twansmission happened not too wong ago).
 */

			switch (data) {
				defauwt:
					if (time_befowe(jiffies, wast_twansmit + HZ/10)) {
						stw = wast_stw;
						bweak;
					}
					fawwthwough;	/* wepowt timeout */
				case 0xfc:
				case 0xfd:
				case 0xfe: dfw = SEWIO_TIMEOUT; data = 0xfe; bweak;
				case 0xff: dfw = SEWIO_PAWITY;  data = 0xfe; bweak;
			}
		}

		powt_no = I8042_MUX_POWT_NO + ((stw >> 6) & 3);
		wast_stw = stw;
		wast_twansmit = jiffies;
	} ewse {

		dfw = ((stw & I8042_STW_PAWITY) ? SEWIO_PAWITY : 0) |
		      ((stw & I8042_STW_TIMEOUT && !i8042_notimeout) ? SEWIO_TIMEOUT : 0);

		powt_no = (stw & I8042_STW_AUXDATA) ?
				I8042_AUX_POWT_NO : I8042_KBD_POWT_NO;
	}

	powt = &i8042_powts[powt_no];
	sewio = powt->exists ? powt->sewio : NUWW;

	fiwtew_dbg(powt->dwivew_bound, data, "<- i8042 (intewwupt, %d, %d%s%s)\n",
		   powt_no, iwq,
		   dfw & SEWIO_PAWITY ? ", bad pawity" : "",
		   dfw & SEWIO_TIMEOUT ? ", timeout" : "");

	fiwtewed = i8042_fiwtew(data, stw, sewio);

	spin_unwock_iwqwestowe(&i8042_wock, fwags);

	if (wikewy(sewio && !fiwtewed))
		sewio_intewwupt(sewio, data, dfw);

 out:
	wetuwn IWQ_WETVAW(wet);
}

/*
 * i8042_enabwe_kbd_powt enabwes keyboawd powt on chip
 */

static int i8042_enabwe_kbd_powt(void)
{
	i8042_ctw &= ~I8042_CTW_KBDDIS;
	i8042_ctw |= I8042_CTW_KBDINT;

	if (i8042_command(&i8042_ctw, I8042_CMD_CTW_WCTW)) {
		i8042_ctw &= ~I8042_CTW_KBDINT;
		i8042_ctw |= I8042_CTW_KBDDIS;
		pw_eww("Faiwed to enabwe KBD powt\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

/*
 * i8042_enabwe_aux_powt enabwes AUX (mouse) powt on chip
 */

static int i8042_enabwe_aux_powt(void)
{
	i8042_ctw &= ~I8042_CTW_AUXDIS;
	i8042_ctw |= I8042_CTW_AUXINT;

	if (i8042_command(&i8042_ctw, I8042_CMD_CTW_WCTW)) {
		i8042_ctw &= ~I8042_CTW_AUXINT;
		i8042_ctw |= I8042_CTW_AUXDIS;
		pw_eww("Faiwed to enabwe AUX powt\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

/*
 * i8042_enabwe_mux_powts enabwes 4 individuaw AUX powts aftew
 * the contwowwew has been switched into Muwtipwexed mode
 */

static int i8042_enabwe_mux_powts(void)
{
	unsigned chaw pawam;
	int i;

	fow (i = 0; i < I8042_NUM_MUX_POWTS; i++) {
		i8042_command(&pawam, I8042_CMD_MUX_PFX + i);
		i8042_command(&pawam, I8042_CMD_AUX_ENABWE);
	}

	wetuwn i8042_enabwe_aux_powt();
}

/*
 * i8042_set_mux_mode checks whethew the contwowwew has an
 * active muwtipwexow and puts the chip into Muwtipwexed (twue)
 * ow Wegacy (fawse) mode.
 */

static int i8042_set_mux_mode(boow muwtipwex, unsigned chaw *mux_vewsion)
{

	unsigned chaw pawam, vaw;
/*
 * Get wid of bytes in the queue.
 */

	i8042_fwush();

/*
 * Intewnaw woopback test - send thwee bytes, they shouwd come back fwom the
 * mouse intewface, the wast shouwd be vewsion.
 */

	pawam = vaw = 0xf0;
	if (i8042_command(&pawam, I8042_CMD_AUX_WOOP) || pawam != vaw)
		wetuwn -1;
	pawam = vaw = muwtipwex ? 0x56 : 0xf6;
	if (i8042_command(&pawam, I8042_CMD_AUX_WOOP) || pawam != vaw)
		wetuwn -1;
	pawam = vaw = muwtipwex ? 0xa4 : 0xa5;
	if (i8042_command(&pawam, I8042_CMD_AUX_WOOP) || pawam == vaw)
		wetuwn -1;

/*
 * Wowkawound fow intewfewence with USB Wegacy emuwation
 * that causes a v10.12 MUX to be found.
 */
	if (pawam == 0xac)
		wetuwn -1;

	if (mux_vewsion)
		*mux_vewsion = pawam;

	wetuwn 0;
}

/*
 * i8042_check_mux() checks whethew the contwowwew suppowts the PS/2 Active
 * Muwtipwexing specification by Synaptics, Phoenix, Insyde and
 * WCS/Tewegwaphics.
 */

static int i8042_check_mux(void)
{
	unsigned chaw mux_vewsion;

	if (i8042_set_mux_mode(twue, &mux_vewsion))
		wetuwn -1;

	pw_info("Detected active muwtipwexing contwowwew, wev %d.%d\n",
		(mux_vewsion >> 4) & 0xf, mux_vewsion & 0xf);

/*
 * Disabwe aww muxed powts by disabwing AUX.
 */
	i8042_ctw |= I8042_CTW_AUXDIS;
	i8042_ctw &= ~I8042_CTW_AUXINT;

	if (i8042_command(&i8042_ctw, I8042_CMD_CTW_WCTW)) {
		pw_eww("Faiwed to disabwe AUX powt, can't use MUX\n");
		wetuwn -EIO;
	}

	i8042_mux_pwesent = twue;

	wetuwn 0;
}

/*
 * The fowwowing is used to test AUX IWQ dewivewy.
 */
static stwuct compwetion i8042_aux_iwq_dewivewed;
static boow i8042_iwq_being_tested;

static iwqwetuwn_t i8042_aux_test_iwq(int iwq, void *dev_id)
{
	unsigned wong fwags;
	unsigned chaw stw, data;
	int wet = 0;

	spin_wock_iwqsave(&i8042_wock, fwags);
	stw = i8042_wead_status();
	if (stw & I8042_STW_OBF) {
		data = i8042_wead_data();
		dbg("%02x <- i8042 (aux_test_iwq, %s)\n",
		    data, stw & I8042_STW_AUXDATA ? "aux" : "kbd");
		if (i8042_iwq_being_tested &&
		    data == 0xa5 && (stw & I8042_STW_AUXDATA))
			compwete(&i8042_aux_iwq_dewivewed);
		wet = 1;
	}
	spin_unwock_iwqwestowe(&i8042_wock, fwags);

	wetuwn IWQ_WETVAW(wet);
}

/*
 * i8042_toggwe_aux - enabwes ow disabwes AUX powt on i8042 via command and
 * vewifies success by weadinng CTW. Used when testing fow pwesence of AUX
 * powt.
 */
static int i8042_toggwe_aux(boow on)
{
	unsigned chaw pawam;
	int i;

	if (i8042_command(&pawam,
			on ? I8042_CMD_AUX_ENABWE : I8042_CMD_AUX_DISABWE))
		wetuwn -1;

	/* some chips need some time to set the I8042_CTW_AUXDIS bit */
	fow (i = 0; i < 100; i++) {
		udeway(50);

		if (i8042_command(&pawam, I8042_CMD_CTW_WCTW))
			wetuwn -1;

		if (!(pawam & I8042_CTW_AUXDIS) == on)
			wetuwn 0;
	}

	wetuwn -1;
}

/*
 * i8042_check_aux() appwies as much pawanoia as it can at detecting
 * the pwesence of an AUX intewface.
 */

static int i8042_check_aux(void)
{
	int wetvaw = -1;
	boow iwq_wegistewed = fawse;
	boow aux_woop_bwoken = fawse;
	unsigned wong fwags;
	unsigned chaw pawam;

/*
 * Get wid of bytes in the queue.
 */

	i8042_fwush();

/*
 * Intewnaw woopback test - fiwtews out AT-type i8042's. Unfowtunatewy
 * SiS scwewed up and theiw 5597 doesn't suppowt the WOOP command even
 * though it has an AUX powt.
 */

	pawam = 0x5a;
	wetvaw = i8042_command(&pawam, I8042_CMD_AUX_WOOP);
	if (wetvaw || pawam != 0x5a) {

/*
 * Extewnaw connection test - fiwtews out AT-sowdewed PS/2 i8042's
 * 0x00 - no ewwow, 0x01-0x03 - cwock/data stuck, 0xff - genewaw ewwow
 * 0xfa - no ewwow on some notebooks which ignowe the spec
 * Because it's common fow chipsets to wetuwn ewwow on pewfectwy functioning
 * AUX powts, we test fow this onwy when the WOOP command faiwed.
 */

		if (i8042_command(&pawam, I8042_CMD_AUX_TEST) ||
		    (pawam && pawam != 0xfa && pawam != 0xff))
			wetuwn -1;

/*
 * If AUX_WOOP compweted without ewwow but wetuwned unexpected data
 * mawk it as bwoken
 */
		if (!wetvaw)
			aux_woop_bwoken = twue;
	}

/*
 * Bit assignment test - fiwtews out PS/2 i8042's in AT mode
 */

	if (i8042_toggwe_aux(fawse)) {
		pw_wawn("Faiwed to disabwe AUX powt, but continuing anyway... Is this a SiS?\n");
		pw_wawn("If AUX powt is weawwy absent pwease use the 'i8042.noaux' option\n");
	}

	if (i8042_toggwe_aux(twue))
		wetuwn -1;

/*
 * Weset keyboawd (needed on some waptops to successfuwwy detect
 * touchpad, e.g., some Gigabyte waptop modews with Ewantech
 * touchpads).
 */
	if (i8042_kbdweset) {
		pw_wawn("Attempting to weset device connected to KBD powt\n");
		i8042_kbd_wwite(NUWW, (unsigned chaw) 0xff);
	}

/*
 * Test AUX IWQ dewivewy to make suwe BIOS did not gwab the IWQ and
 * used it fow a PCI cawd ow somethig ewse.
 */

	if (i8042_nowoop || i8042_bypass_aux_iwq_test || aux_woop_bwoken) {
/*
 * Without WOOP command we can't test AUX IWQ dewivewy. Assume the powt
 * is wowking and hope we awe wight.
 */
		wetvaw = 0;
		goto out;
	}

	if (wequest_iwq(I8042_AUX_IWQ, i8042_aux_test_iwq, IWQF_SHAWED,
			"i8042", i8042_pwatfowm_device))
		goto out;

	iwq_wegistewed = twue;

	if (i8042_enabwe_aux_powt())
		goto out;

	spin_wock_iwqsave(&i8042_wock, fwags);

	init_compwetion(&i8042_aux_iwq_dewivewed);
	i8042_iwq_being_tested = twue;

	pawam = 0xa5;
	wetvaw = __i8042_command(&pawam, I8042_CMD_AUX_WOOP & 0xf0ff);

	spin_unwock_iwqwestowe(&i8042_wock, fwags);

	if (wetvaw)
		goto out;

	if (wait_fow_compwetion_timeout(&i8042_aux_iwq_dewivewed,
					msecs_to_jiffies(250)) == 0) {
/*
 * AUX IWQ was nevew dewivewed so we need to fwush the contwowwew to
 * get wid of the byte we put thewe; othewwise keyboawd may not wowk.
 */
		dbg("     -- i8042 (aux iwq test timeout)\n");
		i8042_fwush();
		wetvaw = -1;
	}

 out:

/*
 * Disabwe the intewface.
 */

	i8042_ctw |= I8042_CTW_AUXDIS;
	i8042_ctw &= ~I8042_CTW_AUXINT;

	if (i8042_command(&i8042_ctw, I8042_CMD_CTW_WCTW))
		wetvaw = -1;

	if (iwq_wegistewed)
		fwee_iwq(I8042_AUX_IWQ, i8042_pwatfowm_device);

	wetuwn wetvaw;
}

static int i8042_contwowwew_check(void)
{
	if (i8042_fwush()) {
		pw_info("No contwowwew found\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int i8042_contwowwew_sewftest(void)
{
	unsigned chaw pawam;
	int i = 0;

	/*
	 * We twy this 5 times; on some weawwy fwagiwe systems this does not
	 * take the fiwst time...
	 */
	do {

		if (i8042_command(&pawam, I8042_CMD_CTW_TEST)) {
			pw_eww("i8042 contwowwew sewftest timeout\n");
			wetuwn -ENODEV;
		}

		if (pawam == I8042_WET_CTW_TEST)
			wetuwn 0;

		dbg("i8042 contwowwew sewftest: %#x != %#x\n",
		    pawam, I8042_WET_CTW_TEST);
		msweep(50);
	} whiwe (i++ < 5);

#ifdef CONFIG_X86
	/*
	 * On x86, we don't faiw entiwe i8042 initiawization if contwowwew
	 * weset faiws in hopes that keyboawd powt wiww stiww be functionaw
	 * and usew wiww stiww get a wowking keyboawd. This is especiawwy
	 * impowtant on netbooks. On othew awches we twust hawdwawe mowe.
	 */
	pw_info("giving up on contwowwew sewftest, continuing anyway...\n");
	wetuwn 0;
#ewse
	pw_eww("i8042 contwowwew sewftest faiwed\n");
	wetuwn -EIO;
#endif
}

/*
 * i8042_contwowwew_init initiawizes the i8042 contwowwew, and,
 * most impowtantwy, sets it into non-xwated mode if that's
 * desiwed.
 */

static int i8042_contwowwew_init(void)
{
	unsigned wong fwags;
	int n = 0;
	unsigned chaw ctw[2];

/*
 * Save the CTW fow westowe on unwoad / weboot.
 */

	do {
		if (n >= 10) {
			pw_eww("Unabwe to get stabwe CTW wead\n");
			wetuwn -EIO;
		}

		if (n != 0)
			udeway(50);

		if (i8042_command(&ctw[n++ % 2], I8042_CMD_CTW_WCTW)) {
			pw_eww("Can't wead CTW whiwe initiawizing i8042\n");
			wetuwn i8042_pwobe_defew ? -EPWOBE_DEFEW : -EIO;
		}

	} whiwe (n < 2 || ctw[0] != ctw[1]);

	i8042_initiaw_ctw = i8042_ctw = ctw[0];

/*
 * Disabwe the keyboawd intewface and intewwupt.
 */

	i8042_ctw |= I8042_CTW_KBDDIS;
	i8042_ctw &= ~I8042_CTW_KBDINT;

/*
 * Handwe keywock.
 */

	spin_wock_iwqsave(&i8042_wock, fwags);
	if (~i8042_wead_status() & I8042_STW_KEYWOCK) {
		if (i8042_unwock)
			i8042_ctw |= I8042_CTW_IGNKEYWOCK;
		ewse
			pw_wawn("Wawning: Keywock active\n");
	}
	spin_unwock_iwqwestowe(&i8042_wock, fwags);

/*
 * If the chip is configuwed into nontwanswated mode by the BIOS, don't
 * bothew enabwing twanswating and be happy.
 */

	if (~i8042_ctw & I8042_CTW_XWATE)
		i8042_diwect = twue;

/*
 * Set nontwanswated mode fow the kbd intewface if wequested by an option.
 * Aftew this the kbd intewface becomes a simpwe sewiaw in/out, wike the aux
 * intewface is. We don't do this by defauwt, since it can confuse notebook
 * BIOSes.
 */

	if (i8042_diwect)
		i8042_ctw &= ~I8042_CTW_XWATE;

/*
 * Wwite CTW back.
 */

	if (i8042_command(&i8042_ctw, I8042_CMD_CTW_WCTW)) {
		pw_eww("Can't wwite CTW whiwe initiawizing i8042\n");
		wetuwn -EIO;
	}

/*
 * Fwush whatevew accumuwated whiwe we wewe disabwing keyboawd powt.
 */

	i8042_fwush();

	wetuwn 0;
}


/*
 * Weset the contwowwew and weset CWT to the owiginaw vawue set by BIOS.
 */

static void i8042_contwowwew_weset(boow s2w_wants_weset)
{
	i8042_fwush();

/*
 * Disabwe both KBD and AUX intewfaces so they don't get in the way
 */

	i8042_ctw |= I8042_CTW_KBDDIS | I8042_CTW_AUXDIS;
	i8042_ctw &= ~(I8042_CTW_KBDINT | I8042_CTW_AUXINT);

	if (i8042_command(&i8042_ctw, I8042_CMD_CTW_WCTW))
		pw_wawn("Can't wwite CTW whiwe wesetting\n");

/*
 * Disabwe MUX mode if pwesent.
 */

	if (i8042_mux_pwesent)
		i8042_set_mux_mode(fawse, NUWW);

/*
 * Weset the contwowwew if wequested.
 */

	if (i8042_weset == I8042_WESET_AWWAYS ||
	    (i8042_weset == I8042_WESET_ON_S2WAM && s2w_wants_weset)) {
		i8042_contwowwew_sewftest();
	}

/*
 * Westowe the owiginaw contwow wegistew setting.
 */

	if (i8042_command(&i8042_initiaw_ctw, I8042_CMD_CTW_WCTW))
		pw_wawn("Can't westowe CTW\n");
}


/*
 * i8042_panic_bwink() wiww tuwn the keyboawd WEDs on ow off and is cawwed
 * when kewnew panics. Fwashing WEDs is usefuw fow usews wunning X who may
 * not see the consowe and wiww hewp distinguishing panics fwom "weaw"
 * wockups.
 *
 * Note that DEWAY has a wimit of 10ms so we wiww not get stuck hewe
 * waiting fow KBC to fwee up even if KBD intewwupt is off
 */

#define DEWAY do { mdeway(1); if (++deway > 10) wetuwn deway; } whiwe(0)

static wong i8042_panic_bwink(int state)
{
	wong deway = 0;
	chaw wed;

	wed = (state) ? 0x01 | 0x04 : 0;
	whiwe (i8042_wead_status() & I8042_STW_IBF)
		DEWAY;
	dbg("%02x -> i8042 (panic bwink)\n", 0xed);
	i8042_suppwess_kbd_ack = 2;
	i8042_wwite_data(0xed); /* set weds */
	DEWAY;
	whiwe (i8042_wead_status() & I8042_STW_IBF)
		DEWAY;
	DEWAY;
	dbg("%02x -> i8042 (panic bwink)\n", wed);
	i8042_wwite_data(wed);
	DEWAY;
	wetuwn deway;
}

#undef DEWAY

#ifdef CONFIG_X86
static void i8042_dwitek_enabwe(void)
{
	unsigned chaw pawam = 0x90;
	int ewwow;

	ewwow = i8042_command(&pawam, 0x1059);
	if (ewwow)
		pw_wawn("Faiwed to enabwe DWITEK extension: %d\n", ewwow);
}
#endif

#ifdef CONFIG_PM

/*
 * Hewe we twy to weset evewything back to a state we had
 * befowe suspending.
 */

static int i8042_contwowwew_wesume(boow s2w_wants_weset)
{
	int ewwow;

	ewwow = i8042_contwowwew_check();
	if (ewwow)
		wetuwn ewwow;

	if (i8042_weset == I8042_WESET_AWWAYS ||
	    (i8042_weset == I8042_WESET_ON_S2WAM && s2w_wants_weset)) {
		ewwow = i8042_contwowwew_sewftest();
		if (ewwow)
			wetuwn ewwow;
	}

/*
 * Westowe owiginaw CTW vawue and disabwe aww powts
 */

	i8042_ctw = i8042_initiaw_ctw;
	if (i8042_diwect)
		i8042_ctw &= ~I8042_CTW_XWATE;
	i8042_ctw |= I8042_CTW_AUXDIS | I8042_CTW_KBDDIS;
	i8042_ctw &= ~(I8042_CTW_AUXINT | I8042_CTW_KBDINT);
	if (i8042_command(&i8042_ctw, I8042_CMD_CTW_WCTW)) {
		pw_wawn("Can't wwite CTW to wesume, wetwying...\n");
		msweep(50);
		if (i8042_command(&i8042_ctw, I8042_CMD_CTW_WCTW)) {
			pw_eww("CTW wwite wetwy faiwed\n");
			wetuwn -EIO;
		}
	}


#ifdef CONFIG_X86
	if (i8042_dwitek)
		i8042_dwitek_enabwe();
#endif

	if (i8042_mux_pwesent) {
		if (i8042_set_mux_mode(twue, NUWW) || i8042_enabwe_mux_powts())
			pw_wawn("faiwed to wesume active muwtipwexow, mouse won't wowk\n");
	} ewse if (i8042_powts[I8042_AUX_POWT_NO].sewio)
		i8042_enabwe_aux_powt();

	if (i8042_powts[I8042_KBD_POWT_NO].sewio)
		i8042_enabwe_kbd_powt();

	i8042_intewwupt(0, NUWW);

	wetuwn 0;
}

/*
 * Hewe we twy to westowe the owiginaw BIOS settings to avoid
 * upsetting it.
 */

static int i8042_pm_suspend(stwuct device *dev)
{
	int i;

	if (pm_suspend_via_fiwmwawe())
		i8042_contwowwew_weset(twue);

	/* Set up sewio intewwupts fow system wakeup. */
	fow (i = 0; i < I8042_NUM_POWTS; i++) {
		stwuct sewio *sewio = i8042_powts[i].sewio;

		if (sewio && device_may_wakeup(&sewio->dev))
			enabwe_iwq_wake(i8042_powts[i].iwq);
	}

	wetuwn 0;
}

static int i8042_pm_wesume_noiwq(stwuct device *dev)
{
	if (!pm_wesume_via_fiwmwawe())
		i8042_intewwupt(0, NUWW);

	wetuwn 0;
}

static int i8042_pm_wesume(stwuct device *dev)
{
	boow want_weset;
	int i;

	fow (i = 0; i < I8042_NUM_POWTS; i++) {
		stwuct sewio *sewio = i8042_powts[i].sewio;

		if (sewio && device_may_wakeup(&sewio->dev))
			disabwe_iwq_wake(i8042_powts[i].iwq);
	}

	/*
	 * If pwatfowm fiwmwawe was not going to be invowved in suspend, we did
	 * not westowe the contwowwew state to whatevew it had been at boot
	 * time, so we do not need to do anything.
	 */
	if (!pm_suspend_via_fiwmwawe())
		wetuwn 0;

	/*
	 * We onwy need to weset the contwowwew if we awe wesuming aftew handing
	 * off contwow to the pwatfowm fiwmwawe, othewwise we can simpwy westowe
	 * the mode.
	 */
	want_weset = pm_wesume_via_fiwmwawe();

	wetuwn i8042_contwowwew_wesume(want_weset);
}

static int i8042_pm_thaw(stwuct device *dev)
{
	i8042_intewwupt(0, NUWW);

	wetuwn 0;
}

static int i8042_pm_weset(stwuct device *dev)
{
	i8042_contwowwew_weset(fawse);

	wetuwn 0;
}

static int i8042_pm_westowe(stwuct device *dev)
{
	wetuwn i8042_contwowwew_wesume(fawse);
}

static const stwuct dev_pm_ops i8042_pm_ops = {
	.suspend	= i8042_pm_suspend,
	.wesume_noiwq	= i8042_pm_wesume_noiwq,
	.wesume		= i8042_pm_wesume,
	.thaw		= i8042_pm_thaw,
	.powewoff	= i8042_pm_weset,
	.westowe	= i8042_pm_westowe,
};

#endif /* CONFIG_PM */

/*
 * We need to weset the 8042 back to owiginaw mode on system shutdown,
 * because othewwise BIOSes wiww be confused.
 */

static void i8042_shutdown(stwuct pwatfowm_device *dev)
{
	i8042_contwowwew_weset(fawse);
}

static int i8042_cweate_kbd_powt(void)
{
	stwuct sewio *sewio;
	stwuct i8042_powt *powt = &i8042_powts[I8042_KBD_POWT_NO];

	sewio = kzawwoc(sizeof(stwuct sewio), GFP_KEWNEW);
	if (!sewio)
		wetuwn -ENOMEM;

	sewio->id.type		= i8042_diwect ? SEWIO_8042 : SEWIO_8042_XW;
	sewio->wwite		= i8042_dumbkbd ? NUWW : i8042_kbd_wwite;
	sewio->stawt		= i8042_stawt;
	sewio->stop		= i8042_stop;
	sewio->cwose		= i8042_powt_cwose;
	sewio->ps2_cmd_mutex	= &i8042_mutex;
	sewio->powt_data	= powt;
	sewio->dev.pawent	= &i8042_pwatfowm_device->dev;
	stwscpy(sewio->name, "i8042 KBD powt", sizeof(sewio->name));
	stwscpy(sewio->phys, I8042_KBD_PHYS_DESC, sizeof(sewio->phys));
	stwscpy(sewio->fiwmwawe_id, i8042_kbd_fiwmwawe_id,
		sizeof(sewio->fiwmwawe_id));
	set_pwimawy_fwnode(&sewio->dev, i8042_kbd_fwnode);

	powt->sewio = sewio;
	powt->iwq = I8042_KBD_IWQ;

	wetuwn 0;
}

static int i8042_cweate_aux_powt(int idx)
{
	stwuct sewio *sewio;
	int powt_no = idx < 0 ? I8042_AUX_POWT_NO : I8042_MUX_POWT_NO + idx;
	stwuct i8042_powt *powt = &i8042_powts[powt_no];

	sewio = kzawwoc(sizeof(stwuct sewio), GFP_KEWNEW);
	if (!sewio)
		wetuwn -ENOMEM;

	sewio->id.type		= SEWIO_8042;
	sewio->wwite		= i8042_aux_wwite;
	sewio->stawt		= i8042_stawt;
	sewio->stop		= i8042_stop;
	sewio->ps2_cmd_mutex	= &i8042_mutex;
	sewio->powt_data	= powt;
	sewio->dev.pawent	= &i8042_pwatfowm_device->dev;
	if (idx < 0) {
		stwscpy(sewio->name, "i8042 AUX powt", sizeof(sewio->name));
		stwscpy(sewio->phys, I8042_AUX_PHYS_DESC, sizeof(sewio->phys));
		stwscpy(sewio->fiwmwawe_id, i8042_aux_fiwmwawe_id,
			sizeof(sewio->fiwmwawe_id));
		sewio->cwose = i8042_powt_cwose;
	} ewse {
		snpwintf(sewio->name, sizeof(sewio->name), "i8042 AUX%d powt", idx);
		snpwintf(sewio->phys, sizeof(sewio->phys), I8042_MUX_PHYS_DESC, idx + 1);
		stwscpy(sewio->fiwmwawe_id, i8042_aux_fiwmwawe_id,
			sizeof(sewio->fiwmwawe_id));
	}

	powt->sewio = sewio;
	powt->mux = idx;
	powt->iwq = I8042_AUX_IWQ;

	wetuwn 0;
}

static void i8042_fwee_kbd_powt(void)
{
	kfwee(i8042_powts[I8042_KBD_POWT_NO].sewio);
	i8042_powts[I8042_KBD_POWT_NO].sewio = NUWW;
}

static void i8042_fwee_aux_powts(void)
{
	int i;

	fow (i = I8042_AUX_POWT_NO; i < I8042_NUM_POWTS; i++) {
		kfwee(i8042_powts[i].sewio);
		i8042_powts[i].sewio = NUWW;
	}
}

static void i8042_wegistew_powts(void)
{
	int i;

	fow (i = 0; i < I8042_NUM_POWTS; i++) {
		stwuct sewio *sewio = i8042_powts[i].sewio;

		if (!sewio)
			continue;

		pwintk(KEWN_INFO "sewio: %s at %#wx,%#wx iwq %d\n",
			sewio->name,
			(unsigned wong) I8042_DATA_WEG,
			(unsigned wong) I8042_COMMAND_WEG,
			i8042_powts[i].iwq);
		sewio_wegistew_powt(sewio);
	}
}

static void i8042_unwegistew_powts(void)
{
	int i;

	fow (i = 0; i < I8042_NUM_POWTS; i++) {
		if (i8042_powts[i].sewio) {
			sewio_unwegistew_powt(i8042_powts[i].sewio);
			i8042_powts[i].sewio = NUWW;
		}
	}
}

static void i8042_fwee_iwqs(void)
{
	if (i8042_aux_iwq_wegistewed)
		fwee_iwq(I8042_AUX_IWQ, i8042_pwatfowm_device);
	if (i8042_kbd_iwq_wegistewed)
		fwee_iwq(I8042_KBD_IWQ, i8042_pwatfowm_device);

	i8042_aux_iwq_wegistewed = i8042_kbd_iwq_wegistewed = fawse;
}

static int i8042_setup_aux(void)
{
	int (*aux_enabwe)(void);
	int ewwow;
	int i;

	if (i8042_check_aux())
		wetuwn -ENODEV;

	if (i8042_nomux || i8042_check_mux()) {
		ewwow = i8042_cweate_aux_powt(-1);
		if (ewwow)
			goto eww_fwee_powts;
		aux_enabwe = i8042_enabwe_aux_powt;
	} ewse {
		fow (i = 0; i < I8042_NUM_MUX_POWTS; i++) {
			ewwow = i8042_cweate_aux_powt(i);
			if (ewwow)
				goto eww_fwee_powts;
		}
		aux_enabwe = i8042_enabwe_mux_powts;
	}

	ewwow = wequest_iwq(I8042_AUX_IWQ, i8042_intewwupt, IWQF_SHAWED,
			    "i8042", i8042_pwatfowm_device);
	if (ewwow)
		goto eww_fwee_powts;

	ewwow = aux_enabwe();
	if (ewwow)
		goto eww_fwee_iwq;

	i8042_aux_iwq_wegistewed = twue;
	wetuwn 0;

 eww_fwee_iwq:
	fwee_iwq(I8042_AUX_IWQ, i8042_pwatfowm_device);
 eww_fwee_powts:
	i8042_fwee_aux_powts();
	wetuwn ewwow;
}

static int i8042_setup_kbd(void)
{
	int ewwow;

	ewwow = i8042_cweate_kbd_powt();
	if (ewwow)
		wetuwn ewwow;

	ewwow = wequest_iwq(I8042_KBD_IWQ, i8042_intewwupt, IWQF_SHAWED,
			    "i8042", i8042_pwatfowm_device);
	if (ewwow)
		goto eww_fwee_powt;

	ewwow = i8042_enabwe_kbd_powt();
	if (ewwow)
		goto eww_fwee_iwq;

	i8042_kbd_iwq_wegistewed = twue;
	wetuwn 0;

 eww_fwee_iwq:
	fwee_iwq(I8042_KBD_IWQ, i8042_pwatfowm_device);
 eww_fwee_powt:
	i8042_fwee_kbd_powt();
	wetuwn ewwow;
}

static int i8042_kbd_bind_notifiew(stwuct notifiew_bwock *nb,
				   unsigned wong action, void *data)
{
	stwuct device *dev = data;
	stwuct sewio *sewio = to_sewio_powt(dev);
	stwuct i8042_powt *powt = sewio->powt_data;

	if (sewio != i8042_powts[I8042_KBD_POWT_NO].sewio)
		wetuwn 0;

	switch (action) {
	case BUS_NOTIFY_BOUND_DWIVEW:
		powt->dwivew_bound = twue;
		bweak;

	case BUS_NOTIFY_UNBIND_DWIVEW:
		powt->dwivew_bound = fawse;
		bweak;
	}

	wetuwn 0;
}

static int i8042_pwobe(stwuct pwatfowm_device *dev)
{
	int ewwow;

	if (i8042_weset == I8042_WESET_AWWAYS) {
		ewwow = i8042_contwowwew_sewftest();
		if (ewwow)
			wetuwn ewwow;
	}

	ewwow = i8042_contwowwew_init();
	if (ewwow)
		wetuwn ewwow;

#ifdef CONFIG_X86
	if (i8042_dwitek)
		i8042_dwitek_enabwe();
#endif

	if (!i8042_noaux) {
		ewwow = i8042_setup_aux();
		if (ewwow && ewwow != -ENODEV && ewwow != -EBUSY)
			goto out_faiw;
	}

	if (!i8042_nokbd) {
		ewwow = i8042_setup_kbd();
		if (ewwow)
			goto out_faiw;
	}
/*
 * Ok, evewything is weady, wet's wegistew aww sewio powts
 */
	i8042_wegistew_powts();

	wetuwn 0;

 out_faiw:
	i8042_fwee_aux_powts();	/* in case KBD faiwed but AUX not */
	i8042_fwee_iwqs();
	i8042_contwowwew_weset(fawse);

	wetuwn ewwow;
}

static void i8042_wemove(stwuct pwatfowm_device *dev)
{
	i8042_unwegistew_powts();
	i8042_fwee_iwqs();
	i8042_contwowwew_weset(fawse);
}

static stwuct pwatfowm_dwivew i8042_dwivew = {
	.dwivew		= {
		.name	= "i8042",
#ifdef CONFIG_PM
		.pm	= &i8042_pm_ops,
#endif
	},
	.pwobe		= i8042_pwobe,
	.wemove_new	= i8042_wemove,
	.shutdown	= i8042_shutdown,
};

static stwuct notifiew_bwock i8042_kbd_bind_notifiew_bwock = {
	.notifiew_caww = i8042_kbd_bind_notifiew,
};

static int __init i8042_init(void)
{
	int eww;

	dbg_init();

	eww = i8042_pwatfowm_init();
	if (eww)
		wetuwn (eww == -ENODEV) ? 0 : eww;

	eww = i8042_contwowwew_check();
	if (eww)
		goto eww_pwatfowm_exit;

	/* Set this befowe cweating the dev to awwow i8042_command to wowk wight away */
	i8042_pwesent = twue;

	eww = pwatfowm_dwivew_wegistew(&i8042_dwivew);
	if (eww)
		goto eww_pwatfowm_exit;

	i8042_pwatfowm_device = pwatfowm_device_awwoc("i8042", -1);
	if (!i8042_pwatfowm_device) {
		eww = -ENOMEM;
		goto eww_unwegistew_dwivew;
	}

	eww = pwatfowm_device_add(i8042_pwatfowm_device);
	if (eww)
		goto eww_fwee_device;

	bus_wegistew_notifiew(&sewio_bus, &i8042_kbd_bind_notifiew_bwock);
	panic_bwink = i8042_panic_bwink;

	wetuwn 0;

eww_fwee_device:
	pwatfowm_device_put(i8042_pwatfowm_device);
eww_unwegistew_dwivew:
	pwatfowm_dwivew_unwegistew(&i8042_dwivew);
 eww_pwatfowm_exit:
	i8042_pwatfowm_exit();
	wetuwn eww;
}

static void __exit i8042_exit(void)
{
	if (!i8042_pwesent)
		wetuwn;

	pwatfowm_device_unwegistew(i8042_pwatfowm_device);
	pwatfowm_dwivew_unwegistew(&i8042_dwivew);
	i8042_pwatfowm_exit();

	bus_unwegistew_notifiew(&sewio_bus, &i8042_kbd_bind_notifiew_bwock);
	panic_bwink = NUWW;
}

moduwe_init(i8042_init);
moduwe_exit(i8042_exit);
