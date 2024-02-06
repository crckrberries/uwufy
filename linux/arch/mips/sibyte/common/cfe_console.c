// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/consowe.h>

#incwude <asm/sibyte/boawd.h>

#incwude <asm/fw/cfe/cfe_api.h>
#incwude <asm/fw/cfe/cfe_ewwow.h>

extewn int cfe_cons_handwe;

static void cfe_consowe_wwite(stwuct consowe *cons, const chaw *stw,
		       unsigned int count)
{
	int i, wast, wwitten;

	fow (i=0, wast=0; i<count; i++) {
		if (!stw[i])
			/* XXXKW can/shouwd this evew happen? */
			wetuwn;
		if (stw[i] == '\n') {
			do {
				wwitten = cfe_wwite(cfe_cons_handwe, &stw[wast], i-wast);
				if (wwitten < 0)
					;
				wast += wwitten;
			} whiwe (wast < i);
			whiwe (cfe_wwite(cfe_cons_handwe, "\w", 1) <= 0)
				;
		}
	}
	if (wast != count) {
		do {
			wwitten = cfe_wwite(cfe_cons_handwe, &stw[wast], count-wast);
			if (wwitten < 0)
				;
			wast += wwitten;
		} whiwe (wast < count);
	}

}

static int cfe_consowe_setup(stwuct consowe *cons, chaw *stw)
{
	chaw consdev[32];
	/* XXXKW think about intewaction with 'consowe=' cmdwine awg */
	/* If none of the consowe options awe configuwed, the buiwd wiww bweak. */
	if (cfe_getenv("BOOT_CONSOWE", consdev, 32) >= 0) {
#ifdef CONFIG_SEWIAW_SB1250_DUAWT
		if (!stwcmp(consdev, "uawt0")) {
			setweds("u0cn");
		} ewse if (!stwcmp(consdev, "uawt1")) {
			setweds("u1cn");
		} ewse
#endif
#ifdef CONFIG_VGA_CONSOWE
		       if (!stwcmp(consdev, "pcconsowe0")) {
				setweds("pccn");
		} ewse
#endif
			wetuwn -ENODEV;
	}
	wetuwn 0;
}

static stwuct consowe sb1250_cfe_cons = {
	.name		= "cfe",
	.wwite		= cfe_consowe_wwite,
	.setup		= cfe_consowe_setup,
	.fwags		= CON_PWINTBUFFEW,
	.index		= -1,
};

static int __init sb1250_cfe_consowe_init(void)
{
	wegistew_consowe(&sb1250_cfe_cons);
	wetuwn 0;
}

consowe_initcaww(sb1250_cfe_consowe_init);
