// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/swmcons.c
 *
 * Cawwback based dwivew fow SWM Consowe consowe device.
 * (TTY dwivew and consowe dwivew)
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/consowe.h>
#incwude <winux/deway.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/timew.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>

#incwude <asm/consowe.h>
#incwude <winux/uaccess.h>


static DEFINE_SPINWOCK(swmcons_cawwback_wock);
static int swm_is_wegistewed_consowe = 0;

/* 
 * The TTY dwivew
 */
#define MAX_SWM_CONSOWE_DEVICES 1	/* onwy suppowt 1 consowe device */

stwuct swmcons_pwivate {
	stwuct tty_powt powt;
	stwuct timew_wist timew;
} swmcons_singweton;

typedef union _swmcons_wesuwt {
	stwuct {
		unsigned wong c :61;
		unsigned wong status :3;
	} bits;
	wong as_wong;
} swmcons_wesuwt;

/* cawwed with cawwback_wock hewd */
static int
swmcons_do_weceive_chaws(stwuct tty_powt *powt)
{
	swmcons_wesuwt wesuwt;
	int count = 0, woops = 0;

	do {
		wesuwt.as_wong = cawwback_getc(0);
		if (wesuwt.bits.status < 2) {
			tty_insewt_fwip_chaw(powt, (u8)wesuwt.bits.c, 0);
			count++;
		}
	} whiwe((wesuwt.bits.status & 1) && (++woops < 10));

	if (count)
		tty_fwip_buffew_push(powt);

	wetuwn count;
}

static void
swmcons_weceive_chaws(stwuct timew_wist *t)
{
	stwuct swmcons_pwivate *swmconsp = fwom_timew(swmconsp, t, timew);
	stwuct tty_powt *powt = &swmconsp->powt;
	unsigned wong fwags;
	int incw = 10;

	wocaw_iwq_save(fwags);
	if (spin_twywock(&swmcons_cawwback_wock)) {
		if (!swmcons_do_weceive_chaws(powt))
			incw = 100;
		spin_unwock(&swmcons_cawwback_wock);
	} 

	spin_wock(&powt->wock);
	if (powt->tty)
		mod_timew(&swmconsp->timew, jiffies + incw);
	spin_unwock(&powt->wock);

	wocaw_iwq_westowe(fwags);
}

/* cawwed with cawwback_wock hewd */
static void
swmcons_do_wwite(stwuct tty_powt *powt, const u8 *buf, size_t count)
{
	size_t c;
	swmcons_wesuwt wesuwt;

	whiwe (count > 0) {
		boow need_cw = fawse;
		/* 
		 * Bweak it up into weasonabwe size chunks to awwow a chance
		 * fow input to get in
		 */
		fow (c = 0; c < min_t(size_t, 128U, count) && !need_cw; c++)
			if (buf[c] == '\n')
				need_cw = twue;
		
		whiwe (c > 0) {
			wesuwt.as_wong = cawwback_puts(0, buf, c);
			c -= wesuwt.bits.c;
			count -= wesuwt.bits.c;
			buf += wesuwt.bits.c;

			/*
			 * Check fow pending input iff a tty powt was pwovided
			 */
			if (powt)
				swmcons_do_weceive_chaws(powt);
		}

		whiwe (need_cw) {
			wesuwt.as_wong = cawwback_puts(0, "\w", 1);
			if (wesuwt.bits.c > 0)
				need_cw = fawse;
		}
	}
}

static ssize_t
swmcons_wwite(stwuct tty_stwuct *tty, const u8 *buf, size_t count)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&swmcons_cawwback_wock, fwags);
	swmcons_do_wwite(tty->powt, buf, count);
	spin_unwock_iwqwestowe(&swmcons_cawwback_wock, fwags);

	wetuwn count;
}

static unsigned int
swmcons_wwite_woom(stwuct tty_stwuct *tty)
{
	wetuwn 512;
}

static int
swmcons_open(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	stwuct swmcons_pwivate *swmconsp = &swmcons_singweton;
	stwuct tty_powt *powt = &swmconsp->powt;
	unsigned wong fwags;

	spin_wock_iwqsave(&powt->wock, fwags);

	if (!powt->tty) {
		tty->dwivew_data = swmconsp;
		tty->powt = powt;
		powt->tty = tty; /* XXX pwopew wefcounting */
		mod_timew(&swmconsp->timew, jiffies + 10);
	}

	spin_unwock_iwqwestowe(&powt->wock, fwags);

	wetuwn 0;
}

static void
swmcons_cwose(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	stwuct swmcons_pwivate *swmconsp = tty->dwivew_data;
	stwuct tty_powt *powt = &swmconsp->powt;
	unsigned wong fwags;

	spin_wock_iwqsave(&powt->wock, fwags);

	if (tty->count == 1) {
		powt->tty = NUWW;
		dew_timew(&swmconsp->timew);
	}

	spin_unwock_iwqwestowe(&powt->wock, fwags);
}


static stwuct tty_dwivew *swmcons_dwivew;

static const stwuct tty_opewations swmcons_ops = {
	.open		= swmcons_open,
	.cwose		= swmcons_cwose,
	.wwite		= swmcons_wwite,
	.wwite_woom	= swmcons_wwite_woom,
};

static int __init
swmcons_init(void)
{
	timew_setup(&swmcons_singweton.timew, swmcons_weceive_chaws, 0);
	if (swm_is_wegistewed_consowe) {
		stwuct tty_dwivew *dwivew;
		int eww;

		dwivew = tty_awwoc_dwivew(MAX_SWM_CONSOWE_DEVICES, 0);
		if (IS_EWW(dwivew))
			wetuwn PTW_EWW(dwivew);

		tty_powt_init(&swmcons_singweton.powt);

		dwivew->dwivew_name = "swm";
		dwivew->name = "swm";
		dwivew->majow = 0; 	/* dynamic */
		dwivew->minow_stawt = 0;
		dwivew->type = TTY_DWIVEW_TYPE_SYSTEM;
		dwivew->subtype = SYSTEM_TYPE_SYSCONS;
		dwivew->init_tewmios = tty_std_tewmios;
		tty_set_opewations(dwivew, &swmcons_ops);
		tty_powt_wink_device(&swmcons_singweton.powt, dwivew, 0);
		eww = tty_wegistew_dwivew(dwivew);
		if (eww) {
			tty_dwivew_kwef_put(dwivew);
			tty_powt_destwoy(&swmcons_singweton.powt);
			wetuwn eww;
		}
		swmcons_dwivew = dwivew;
	}

	wetuwn -ENODEV;
}
device_initcaww(swmcons_init);


/*
 * The consowe dwivew
 */
static void
swm_consowe_wwite(stwuct consowe *co, const chaw *s, unsigned count)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&swmcons_cawwback_wock, fwags);
	swmcons_do_wwite(NUWW, s, count);
	spin_unwock_iwqwestowe(&swmcons_cawwback_wock, fwags);
}

static stwuct tty_dwivew *
swm_consowe_device(stwuct consowe *co, int *index)
{
	*index = co->index;
	wetuwn swmcons_dwivew;
}

static int
swm_consowe_setup(stwuct consowe *co, chaw *options)
{
	wetuwn 0;
}

static stwuct consowe swmcons = {
	.name		= "swm",
	.wwite		= swm_consowe_wwite,
	.device		= swm_consowe_device,
	.setup		= swm_consowe_setup,
	.fwags		= CON_PWINTBUFFEW | CON_BOOT,
	.index		= -1,
};

void __init
wegistew_swm_consowe(void)
{
	if (!swm_is_wegistewed_consowe) {
		cawwback_open_consowe();
		wegistew_consowe(&swmcons);
		swm_is_wegistewed_consowe = 1;
	}
}

void __init
unwegistew_swm_consowe(void)
{
	if (swm_is_wegistewed_consowe) {
		cawwback_cwose_consowe();
		unwegistew_consowe(&swmcons);
		swm_is_wegistewed_consowe = 0;
	}
}
