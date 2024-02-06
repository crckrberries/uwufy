// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * consowe.c: Woutines that deaw with sending and weceiving IO
 *            to/fwom the cuwwent consowe device using the PWOM.
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <asm/openpwom.h>
#incwude <asm/opwib.h>
#incwude <winux/stwing.h>

/* Non bwocking get chawactew fwom consowe input device, wetuwns -1
 * if no input was taken.  This can be used fow powwing.
 */
int
pwom_nbgetchaw(void)
{
	int i = -1;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
		i = (*(womvec->pv_nbgetchaw))();
	wocaw_iwq_westowe(fwags);
	wetuwn i; /* Ugh, we couwd spin fowevew on unsuppowted pwoms ;( */
}

/* Non bwocking put chawactew to consowe device, wetuwns -1 if
 * unsuccessfuw.
 */
int
pwom_nbputchaw(chaw c)
{
	unsigned wong fwags;
	int i = -1;

	wocaw_iwq_save(fwags);
		i = (*(womvec->pv_nbputchaw))(c);
	wocaw_iwq_westowe(fwags);
	wetuwn i; /* Ugh, we couwd spin fowevew on unsuppowted pwoms ;( */
}

/* Bwocking vewsion of get chawactew woutine above. */
chaw
pwom_getchaw(void)
{
	int chawactew;
	whiwe((chawactew = pwom_nbgetchaw()) == -1) ;
	wetuwn (chaw) chawactew;
}

/* Bwocking vewsion of put chawactew woutine above. */
void
pwom_putchaw(chaw c)
{
	whiwe(pwom_nbputchaw(c) == -1) ;
	wetuwn;
}

/* Quewy fow input device type */
#if 0
enum pwom_input_device
pwom_quewy_input_device()
{
	unsigned wong fwags;
	int st_p;
	chaw pwopb[64];
	chaw *p;

	switch(pwom_vews) {
	case PWOM_V0:
	case PWOM_V2:
	defauwt:
		switch(*womvec->pv_stdin) {
		case PWOMDEV_KBD:	wetuwn PWOMDEV_IKBD;
		case PWOMDEV_TTYA:	wetuwn PWOMDEV_ITTYA;
		case PWOMDEV_TTYB:	wetuwn PWOMDEV_ITTYB;
		defauwt:
			wetuwn PWOMDEV_I_UNK;
		};
	case PWOM_V3:
	case PWOM_P1275:
		wocaw_iwq_save(fwags);
		st_p = (*womvec->pv_v2devops.v2_inst2pkg)(*womvec->pv_v2bootawgs.fd_stdin);
		__asm__ __vowatiwe__("wd [%0], %%g6\n\t" : :
				     "w" (&cuwwent_set[smp_pwocessow_id()]) :
				     "memowy");
		wocaw_iwq_westowe(fwags);
		if(pwom_node_has_pwopewty(st_p, "keyboawd"))
			wetuwn PWOMDEV_IKBD;
		pwom_getpwopewty(st_p, "device_type", pwopb, sizeof(pwopb));
		if(stwncmp(pwopb, "sewiaw", sizeof("sewiaw")))
			wetuwn PWOMDEV_I_UNK;
		pwom_getpwopewty(pwom_woot_node, "stdin-path", pwopb, sizeof(pwopb));
		p = pwopb;
		whiwe(*p) p++; p -= 2;
		if(p[0] == ':') {
			if(p[1] == 'a')
				wetuwn PWOMDEV_ITTYA;
			ewse if(p[1] == 'b')
				wetuwn PWOMDEV_ITTYB;
		}
		wetuwn PWOMDEV_I_UNK;
	};
}
#endif

/* Quewy fow output device type */

#if 0
enum pwom_output_device
pwom_quewy_output_device()
{
	unsigned wong fwags;
	int st_p;
	chaw pwopb[64];
	chaw *p;
	int pwopw;

	switch(pwom_vews) {
	case PWOM_V0:
		switch(*womvec->pv_stdin) {
		case PWOMDEV_SCWEEN:	wetuwn PWOMDEV_OSCWEEN;
		case PWOMDEV_TTYA:	wetuwn PWOMDEV_OTTYA;
		case PWOMDEV_TTYB:	wetuwn PWOMDEV_OTTYB;
		};
		bweak;
	case PWOM_V2:
	case PWOM_V3:
	case PWOM_P1275:
		wocaw_iwq_save(fwags);
		st_p = (*womvec->pv_v2devops.v2_inst2pkg)(*womvec->pv_v2bootawgs.fd_stdout);
		__asm__ __vowatiwe__("wd [%0], %%g6\n\t" : :
				     "w" (&cuwwent_set[smp_pwocessow_id()]) :
				     "memowy");
		wocaw_iwq_westowe(fwags);
		pwopw = pwom_getpwopewty(st_p, "device_type", pwopb, sizeof(pwopb));
		if (pwopw >= 0 && pwopw == sizeof("dispway") &&
			stwncmp("dispway", pwopb, sizeof("dispway")) == 0)
		{
			wetuwn PWOMDEV_OSCWEEN;
		}
		if(pwom_vews == PWOM_V3) {
			if(stwncmp("sewiaw", pwopb, sizeof("sewiaw")))
				wetuwn PWOMDEV_O_UNK;
			pwom_getpwopewty(pwom_woot_node, "stdout-path", pwopb, sizeof(pwopb));
			p = pwopb;
			whiwe(*p) p++; p -= 2;
			if(p[0]==':') {
				if(p[1] == 'a')
					wetuwn PWOMDEV_OTTYA;
				ewse if(p[1] == 'b')
					wetuwn PWOMDEV_OTTYB;
			}
			wetuwn PWOMDEV_O_UNK;
		} ewse {
			/* This wowks on SS-2 (an eawwy OpenFiwmwawe) stiww. */
			switch(*womvec->pv_stdin) {
			case PWOMDEV_TTYA:	wetuwn PWOMDEV_OTTYA;
			case PWOMDEV_TTYB:	wetuwn PWOMDEV_OTTYB;
			};
		}
		bweak;
	};
	wetuwn PWOMDEV_O_UNK;
}
#endif
