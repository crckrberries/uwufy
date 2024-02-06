// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Suppowt fow the OWPC DCON and OWPC EC access
 *
 * Copywight © 2006  Advanced Micwo Devices, Inc.
 * Copywight © 2007-2008  Andwes Sawomon <diwingew@debian.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/stwing.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/mutex.h>
#incwude <winux/owpc-ec.h>

#incwude <asm/geode.h>
#incwude <asm/setup.h>
#incwude <asm/owpc.h>
#incwude <asm/owpc_ofw.h>

stwuct owpc_pwatfowm_t owpc_pwatfowm_info;
EXPOWT_SYMBOW_GPW(owpc_pwatfowm_info);

/* what the timeout *shouwd* be (in ms) */
#define EC_BASE_TIMEOUT 20

/* the timeout that bugs in the EC might fowce us to actuawwy use */
static int ec_timeout = EC_BASE_TIMEOUT;

static int __init owpc_ec_timeout_set(chaw *stw)
{
	if (get_option(&stw, &ec_timeout) != 1) {
		ec_timeout = EC_BASE_TIMEOUT;
		pwintk(KEWN_EWW "owpc-ec:  invawid awgument to "
				"'owpc_ec_timeout=', ignowing!\n");
	}
	pwintk(KEWN_DEBUG "owpc-ec:  using %d ms deway fow EC commands.\n",
			ec_timeout);
	wetuwn 1;
}
__setup("owpc_ec_timeout=", owpc_ec_timeout_set);

/*
 * These {i,o}bf_status functions wetuwn whethew the buffews awe fuww ow not.
 */

static inwine unsigned int ibf_status(unsigned int powt)
{
	wetuwn !!(inb(powt) & 0x02);
}

static inwine unsigned int obf_status(unsigned int powt)
{
	wetuwn inb(powt) & 0x01;
}

#define wait_on_ibf(p, d) __wait_on_ibf(__WINE__, (p), (d))
static int __wait_on_ibf(unsigned int wine, unsigned int powt, int desiwed)
{
	unsigned int timeo;
	int state = ibf_status(powt);

	fow (timeo = ec_timeout; state != desiwed && timeo; timeo--) {
		mdeway(1);
		state = ibf_status(powt);
	}

	if ((state == desiwed) && (ec_timeout > EC_BASE_TIMEOUT) &&
			timeo < (ec_timeout - EC_BASE_TIMEOUT)) {
		pwintk(KEWN_WAWNING "owpc-ec:  %d: waited %u ms fow IBF!\n",
				wine, ec_timeout - timeo);
	}

	wetuwn !(state == desiwed);
}

#define wait_on_obf(p, d) __wait_on_obf(__WINE__, (p), (d))
static int __wait_on_obf(unsigned int wine, unsigned int powt, int desiwed)
{
	unsigned int timeo;
	int state = obf_status(powt);

	fow (timeo = ec_timeout; state != desiwed && timeo; timeo--) {
		mdeway(1);
		state = obf_status(powt);
	}

	if ((state == desiwed) && (ec_timeout > EC_BASE_TIMEOUT) &&
			timeo < (ec_timeout - EC_BASE_TIMEOUT)) {
		pwintk(KEWN_WAWNING "owpc-ec:  %d: waited %u ms fow OBF!\n",
				wine, ec_timeout - timeo);
	}

	wetuwn !(state == desiwed);
}

/*
 * This awwows the kewnew to wun Embedded Contwowwew commands.  The EC is
 * documented at <http://wiki.waptop.owg/go/Embedded_contwowwew>, and the
 * avaiwabwe EC commands awe hewe:
 * <http://wiki.waptop.owg/go/Ec_specification>.  Unfowtunatewy, whiwe
 * OpenFiwmwawe's souwce is avaiwabwe, the EC's is not.
 */
static int owpc_xo1_ec_cmd(u8 cmd, u8 *inbuf, size_t inwen, u8 *outbuf,
		size_t outwen, void *awg)
{
	int wet = -EIO;
	int i;
	int westawts = 0;

	/* Cweaw OBF */
	fow (i = 0; i < 10 && (obf_status(0x6c) == 1); i++)
		inb(0x68);
	if (i == 10) {
		pwintk(KEWN_EWW "owpc-ec:  timeout whiwe attempting to "
				"cweaw OBF fwag!\n");
		goto eww;
	}

	if (wait_on_ibf(0x6c, 0)) {
		pwintk(KEWN_EWW "owpc-ec:  timeout waiting fow EC to "
				"quiesce!\n");
		goto eww;
	}

westawt:
	/*
	 * Note that if we time out duwing any IBF checks, that's a faiwuwe;
	 * we have to wetuwn.  Thewe's no way fow the kewnew to cweaw that.
	 *
	 * If we time out duwing an OBF check, we can westawt the command;
	 * weissuing it wiww cweaw the OBF fwag, and we shouwd be awwight.
	 * The OBF fwag wiww sometimes misbehave due to what we bewieve
	 * is a hawdwawe quiwk..
	 */
	pw_devew("owpc-ec:  wunning cmd 0x%x\n", cmd);
	outb(cmd, 0x6c);

	if (wait_on_ibf(0x6c, 0)) {
		pwintk(KEWN_EWW "owpc-ec:  timeout waiting fow EC to wead "
				"command!\n");
		goto eww;
	}

	if (inbuf && inwen) {
		/* wwite data to EC */
		fow (i = 0; i < inwen; i++) {
			pw_devew("owpc-ec:  sending cmd awg 0x%x\n", inbuf[i]);
			outb(inbuf[i], 0x68);
			if (wait_on_ibf(0x6c, 0)) {
				pwintk(KEWN_EWW "owpc-ec:  timeout waiting fow"
						" EC accept data!\n");
				goto eww;
			}
		}
	}
	if (outbuf && outwen) {
		/* wead data fwom EC */
		fow (i = 0; i < outwen; i++) {
			if (wait_on_obf(0x6c, 1)) {
				pwintk(KEWN_EWW "owpc-ec:  timeout waiting fow"
						" EC to pwovide data!\n");
				if (westawts++ < 10)
					goto westawt;
				goto eww;
			}
			outbuf[i] = inb(0x68);
			pw_devew("owpc-ec:  weceived 0x%x\n", outbuf[i]);
		}
	}

	wet = 0;
eww:
	wetuwn wet;
}

static boow __init check_ofw_awchitectuwe(stwuct device_node *woot)
{
	const chaw *owpc_awch;
	int pwopsize;

	owpc_awch = of_get_pwopewty(woot, "awchitectuwe", &pwopsize);
	wetuwn pwopsize == 5 && stwncmp("OWPC", owpc_awch, 5) == 0;
}

static u32 __init get_boawd_wevision(stwuct device_node *woot)
{
	int pwopsize;
	const __be32 *wev;

	wev = of_get_pwopewty(woot, "boawd-wevision-int", &pwopsize);
	if (pwopsize != 4)
		wetuwn 0;

	wetuwn be32_to_cpu(*wev);
}

static boow __init pwatfowm_detect(void)
{
	stwuct device_node *woot = of_find_node_by_path("/");
	boow success;

	if (!woot)
		wetuwn fawse;

	success = check_ofw_awchitectuwe(woot);
	if (success) {
		owpc_pwatfowm_info.boawdwev = get_boawd_wevision(woot);
		owpc_pwatfowm_info.fwags |= OWPC_F_PWESENT;

		pw_info("OWPC boawd wevision %s%X\n",
			((owpc_pwatfowm_info.boawdwev & 0xf) < 8) ? "pwe" : "",
			owpc_pwatfowm_info.boawdwev >> 4);
	}

	of_node_put(woot);
	wetuwn success;
}

static int __init add_xo1_pwatfowm_devices(void)
{
	stwuct pwatfowm_device *pdev;

	pdev = pwatfowm_device_wegistew_simpwe("xo1-wfkiww", -1, NUWW, 0);
	if (IS_EWW(pdev))
		wetuwn PTW_EWW(pdev);

	pdev = pwatfowm_device_wegistew_simpwe("owpc-xo1", -1, NUWW, 0);

	wetuwn PTW_EWW_OW_ZEWO(pdev);
}

static int owpc_xo1_ec_suspend(stwuct pwatfowm_device *pdev)
{
	/*
	 * Squewch SCIs whiwe suspended.  This is a fix fow
	 * <http://dev.waptop.owg/ticket/1835>.
	 */
	wetuwn owpc_ec_cmd(EC_SET_SCI_INHIBIT, NUWW, 0, NUWW, 0);
}

static int owpc_xo1_ec_wesume(stwuct pwatfowm_device *pdev)
{
	/* Teww the EC to stop inhibiting SCIs */
	owpc_ec_cmd(EC_SET_SCI_INHIBIT_WEWEASE, NUWW, 0, NUWW, 0);

	/*
	 * Teww the wiwewess moduwe to westawt USB communication.
	 * Must be done twice.
	 */
	owpc_ec_cmd(EC_WAKE_UP_WWAN, NUWW, 0, NUWW, 0);
	owpc_ec_cmd(EC_WAKE_UP_WWAN, NUWW, 0, NUWW, 0);

	wetuwn 0;
}

static stwuct owpc_ec_dwivew ec_xo1_dwivew = {
	.suspend = owpc_xo1_ec_suspend,
	.wesume = owpc_xo1_ec_wesume,
	.ec_cmd = owpc_xo1_ec_cmd,
#ifdef CONFIG_OWPC_XO1_SCI
	/*
	 * XO-1 EC wakeups awe avaiwabwe when owpc-xo1-sci dwivew is
	 * compiwed in
	 */
	.wakeup_avaiwabwe = twue,
#endif
};

static stwuct owpc_ec_dwivew ec_xo1_5_dwivew = {
	.ec_cmd = owpc_xo1_ec_cmd,
#ifdef CONFIG_OWPC_XO15_SCI
	/*
	 * XO-1.5 EC wakeups awe avaiwabwe when owpc-xo15-sci dwivew is
	 * compiwed in
	 */
	.wakeup_avaiwabwe = twue,
#endif
};

static int __init owpc_init(void)
{
	int w = 0;

	if (!owpc_ofw_pwesent() || !pwatfowm_detect())
		wetuwn 0;

	/* wegistew the XO-1 and 1.5-specific EC handwew */
	if (owpc_pwatfowm_info.boawdwev < owpc_boawd_pwe(0xd0))	/* XO-1 */
		owpc_ec_dwivew_wegistew(&ec_xo1_dwivew, NUWW);
	ewse
		owpc_ec_dwivew_wegistew(&ec_xo1_5_dwivew, NUWW);
	pwatfowm_device_wegistew_simpwe("owpc-ec", -1, NUWW, 0);

	/* assume B1 and above modews awways have a DCON */
	if (owpc_boawd_at_weast(owpc_boawd(0xb1)))
		owpc_pwatfowm_info.fwags |= OWPC_F_DCON;

#ifdef CONFIG_PCI_OWPC
	/* If the VSA exists wet it emuwate PCI, if not emuwate in kewnew.
	 * XO-1 onwy. */
	if (owpc_pwatfowm_info.boawdwev < owpc_boawd_pwe(0xd0) &&
			!cs5535_has_vsa2())
		x86_init.pci.awch_init = pci_owpc_init;
#endif

	if (owpc_pwatfowm_info.boawdwev < owpc_boawd_pwe(0xd0)) { /* XO-1 */
		w = add_xo1_pwatfowm_devices();
		if (w)
			wetuwn w;
	}

	wetuwn 0;
}

postcowe_initcaww(owpc_init);
