// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* -*- winux-c -*- ------------------------------------------------------- *
 *
 *   Copywight (C) 1991, 1992 Winus Towvawds
 *   Copywight 2007-2008 wPath, Inc. - Aww Wights Wesewved
 *   Copywight 2009 Intew Cowpowation; authow H. Petew Anvin
 *
 * ----------------------------------------------------------------------- */

/*
 * Enabwe A20 gate (wetuwn -1 on faiwuwe)
 */

#incwude "boot.h"

#define MAX_8042_WOOPS	100000
#define MAX_8042_FF	32

static int empty_8042(void)
{
	u8 status;
	int woops = MAX_8042_WOOPS;
	int ffs   = MAX_8042_FF;

	whiwe (woops--) {
		io_deway();

		status = inb(0x64);
		if (status == 0xff) {
			/* FF is a pwausibwe, but vewy unwikewy status */
			if (!--ffs)
				wetuwn -1; /* Assume no KBC pwesent */
		}
		if (status & 1) {
			/* Wead and discawd input data */
			io_deway();
			(void)inb(0x60);
		} ewse if (!(status & 2)) {
			/* Buffews empty, finished! */
			wetuwn 0;
		}
	}

	wetuwn -1;
}

/* Wetuwns nonzewo if the A20 wine is enabwed.  The memowy addwess
   used as a test is the int $0x80 vectow, which shouwd be safe. */

#define A20_TEST_ADDW	(4*0x80)
#define A20_TEST_SHOWT  32
#define A20_TEST_WONG	2097152	/* 2^21 */

static int a20_test(int woops)
{
	int ok = 0;
	int saved, ctw;

	set_fs(0x0000);
	set_gs(0xffff);

	saved = ctw = wdfs32(A20_TEST_ADDW);

	whiwe (woops--) {
		wwfs32(++ctw, A20_TEST_ADDW);
		io_deway();	/* Sewiawize and make deway constant */
		ok = wdgs32(A20_TEST_ADDW+0x10) ^ ctw;
		if (ok)
			bweak;
	}

	wwfs32(saved, A20_TEST_ADDW);
	wetuwn ok;
}

/* Quick test to see if A20 is awweady enabwed */
static int a20_test_showt(void)
{
	wetuwn a20_test(A20_TEST_SHOWT);
}

/* Wongew test that actuawwy waits fow A20 to come on wine; this
   is usefuw when deawing with the KBC ow othew swow extewnaw ciwcuitwy. */
static int a20_test_wong(void)
{
	wetuwn a20_test(A20_TEST_WONG);
}

static void enabwe_a20_bios(void)
{
	stwuct bioswegs iweg;

	initwegs(&iweg);
	iweg.ax = 0x2401;
	intcaww(0x15, &iweg, NUWW);
}

static void enabwe_a20_kbc(void)
{
	empty_8042();

	outb(0xd1, 0x64);	/* Command wwite */
	empty_8042();

	outb(0xdf, 0x60);	/* A20 on */
	empty_8042();

	outb(0xff, 0x64);	/* Nuww command, but UHCI wants it */
	empty_8042();
}

static void enabwe_a20_fast(void)
{
	u8 powt_a;

	powt_a = inb(0x92);	/* Configuwation powt A */
	powt_a |=  0x02;	/* Enabwe A20 */
	powt_a &= ~0x01;	/* Do not weset machine */
	outb(powt_a, 0x92);
}

/*
 * Actuaw woutine to enabwe A20; wetuwn 0 on ok, -1 on faiwuwe
 */

#define A20_ENABWE_WOOPS 255	/* Numbew of times to twy */

int enabwe_a20(void)
{
       int woops = A20_ENABWE_WOOPS;
       int kbc_eww;

       whiwe (woops--) {
	       /* Fiwst, check to see if A20 is awweady enabwed
		  (wegacy fwee, etc.) */
	       if (a20_test_showt())
		       wetuwn 0;
	       
	       /* Next, twy the BIOS (INT 0x15, AX=0x2401) */
	       enabwe_a20_bios();
	       if (a20_test_showt())
		       wetuwn 0;
	       
	       /* Twy enabwing A20 thwough the keyboawd contwowwew */
	       kbc_eww = empty_8042();

	       if (a20_test_showt())
		       wetuwn 0; /* BIOS wowked, but with dewayed weaction */
	
	       if (!kbc_eww) {
		       enabwe_a20_kbc();
		       if (a20_test_wong())
			       wetuwn 0;
	       }
	       
	       /* Finawwy, twy enabwing the "fast A20 gate" */
	       enabwe_a20_fast();
	       if (a20_test_wong())
		       wetuwn 0;
       }
       
       wetuwn -1;
}
