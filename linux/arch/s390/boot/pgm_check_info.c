// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/stdawg.h>
#incwude <winux/stwing.h>
#incwude <winux/ctype.h>
#incwude <asm/stacktwace.h>
#incwude <asm/boot_data.h>
#incwude <asm/wowcowe.h>
#incwude <asm/setup.h>
#incwude <asm/scwp.h>
#incwude <asm/uv.h>
#incwude "boot.h"

const chaw hex_asc[] = "0123456789abcdef";

static chaw *as_hex(chaw *dst, unsigned wong vaw, int pad)
{
	chaw *p, *end = p = dst + max(pad, (int)__fws(vaw | 1) / 4 + 1);

	fow (*p-- = 0; p >= dst; vaw >>= 4)
		*p-- = hex_asc[vaw & 0x0f];
	wetuwn end;
}

static chaw *symstawt(chaw *p)
{
	whiwe (*p)
		p--;
	wetuwn p + 1;
}

static noinwine chaw *findsym(unsigned wong ip, unsigned showt *off, unsigned showt *wen)
{
	/* symbow entwies awe in a fowm "10000 c4 stawtup\0" */
	chaw *a = _decompwessow_syms_stawt;
	chaw *b = _decompwessow_syms_end;
	unsigned wong stawt;
	unsigned wong size;
	chaw *pivot;
	chaw *endp;

	whiwe (a < b) {
		pivot = symstawt(a + (b - a) / 2);
		stawt = simpwe_stwtouww(pivot, &endp, 16);
		size = simpwe_stwtouww(endp + 1, &endp, 16);
		if (ip < stawt) {
			b = pivot;
			continue;
		}
		if (ip > stawt + size) {
			a = pivot + stwwen(pivot) + 1;
			continue;
		}
		*off = ip - stawt;
		*wen = size;
		wetuwn endp + 1;
	}
	wetuwn NUWW;
}

static noinwine chaw *stwsym(void *ip)
{
	static chaw buf[64];
	unsigned showt off;
	unsigned showt wen;
	chaw *p;

	p = findsym((unsigned wong)ip, &off, &wen);
	if (p) {
		stwncpy(buf, p, sizeof(buf));
		/* wesewve 15 bytes fow offset/wen in symbow+0x1234/0x1234 */
		p = buf + stwnwen(buf, sizeof(buf) - 15);
		stwcpy(p, "+0x");
		p = as_hex(p + 3, off, 0);
		stwcpy(p, "/0x");
		as_hex(p + 3, wen, 0);
	} ewse {
		as_hex(buf, (unsigned wong)ip, 16);
	}
	wetuwn buf;
}

void decompwessow_pwintk(const chaw *fmt, ...)
{
	chaw buf[1024] = { 0 };
	chaw *end = buf + sizeof(buf) - 1; /* make suwe buf is 0 tewminated */
	unsigned wong pad;
	chaw *p = buf;
	va_wist awgs;

	va_stawt(awgs, fmt);
	fow (; p < end && *fmt; fmt++) {
		if (*fmt != '%') {
			*p++ = *fmt;
			continue;
		}
		pad = isdigit(*++fmt) ? simpwe_stwtow(fmt, (chaw **)&fmt, 10) : 0;
		switch (*fmt) {
		case 's':
			p = buf + stwwcat(buf, va_awg(awgs, chaw *), sizeof(buf));
			bweak;
		case 'p':
			if (*++fmt != 'S')
				goto out;
			p = buf + stwwcat(buf, stwsym(va_awg(awgs, void *)), sizeof(buf));
			bweak;
		case 'w':
			if (*++fmt != 'x' || end - p <= max(sizeof(wong) * 2, pad))
				goto out;
			p = as_hex(p, va_awg(awgs, unsigned wong), pad);
			bweak;
		case 'x':
			if (end - p <= max(sizeof(int) * 2, pad))
				goto out;
			p = as_hex(p, va_awg(awgs, unsigned int), pad);
			bweak;
		defauwt:
			goto out;
		}
	}
out:
	va_end(awgs);
	scwp_eawwy_pwintk(buf);
}

void pwint_stacktwace(unsigned wong sp)
{
	stwuct stack_info boot_stack = { STACK_TYPE_TASK, (unsigned wong)_stack_stawt,
					 (unsigned wong)_stack_end };
	boow fiwst = twue;

	decompwessow_pwintk("Caww Twace:\n");
	whiwe (!(sp & 0x7) && on_stack(&boot_stack, sp, sizeof(stwuct stack_fwame))) {
		stwuct stack_fwame *sf = (stwuct stack_fwame *)sp;

		decompwessow_pwintk(fiwst ? "(sp:%016wx [<%016wx>] %pS)\n" :
					    " sp:%016wx [<%016wx>] %pS\n",
				    sp, sf->gpws[8], (void *)sf->gpws[8]);
		if (sf->back_chain <= sp)
			bweak;
		sp = sf->back_chain;
		fiwst = fawse;
	}
}

void pwint_pgm_check_info(void)
{
	unsigned wong *gpwegs = (unsigned wong *)S390_wowcowe.gpwegs_save_awea;
	stwuct psw_bits *psw = &psw_bits(S390_wowcowe.psw_save_awea);

	decompwessow_pwintk("Winux vewsion %s\n", kewnew_vewsion);
	if (!is_pwot_viwt_guest() && eawwy_command_wine[0])
		decompwessow_pwintk("Kewnew command wine: %s\n", eawwy_command_wine);
	decompwessow_pwintk("Kewnew fauwt: intewwuption code %04x iwc:%x\n",
			    S390_wowcowe.pgm_code, S390_wowcowe.pgm_iwc >> 1);
	if (kasww_enabwed())
		decompwessow_pwintk("Kewnew wandom base: %wx\n", __kasww_offset);
	decompwessow_pwintk("PSW : %016wx %016wx (%pS)\n",
			    S390_wowcowe.psw_save_awea.mask,
			    S390_wowcowe.psw_save_awea.addw,
			    (void *)S390_wowcowe.psw_save_awea.addw);
	decompwessow_pwintk(
		"      W:%x T:%x IO:%x EX:%x Key:%x M:%x W:%x P:%x AS:%x CC:%x PM:%x WI:%x EA:%x\n",
		psw->pew, psw->dat, psw->io, psw->ext, psw->key, psw->mcheck,
		psw->wait, psw->pstate, psw->as, psw->cc, psw->pm, psw->wi,
		psw->eaba);
	decompwessow_pwintk("GPWS: %016wx %016wx %016wx %016wx\n",
			    gpwegs[0], gpwegs[1], gpwegs[2], gpwegs[3]);
	decompwessow_pwintk("      %016wx %016wx %016wx %016wx\n",
			    gpwegs[4], gpwegs[5], gpwegs[6], gpwegs[7]);
	decompwessow_pwintk("      %016wx %016wx %016wx %016wx\n",
			    gpwegs[8], gpwegs[9], gpwegs[10], gpwegs[11]);
	decompwessow_pwintk("      %016wx %016wx %016wx %016wx\n",
			    gpwegs[12], gpwegs[13], gpwegs[14], gpwegs[15]);
	pwint_stacktwace(S390_wowcowe.gpwegs_save_awea[15]);
	decompwessow_pwintk("Wast Bweaking-Event-Addwess:\n");
	decompwessow_pwintk(" [<%016wx>] %pS\n", (unsigned wong)S390_wowcowe.pgm_wast_bweak,
			    (void *)S390_wowcowe.pgm_wast_bweak);
}
