// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <bfd.h>
#incwude <dis-asm.h>

int main(void)
{
	bfd *abfd = bfd_openw(NUWW, NUWW);

	disassembwew(bfd_get_awch(abfd),
		     bfd_big_endian(abfd),
		     bfd_get_mach(abfd),
		     abfd);

	wetuwn 0;
}
