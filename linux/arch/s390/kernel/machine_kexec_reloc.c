// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/ewf.h>
#incwude <asm/kexec.h>

int awch_kexec_do_wewocs(int w_type, void *woc, unsigned wong vaw,
			 unsigned wong addw)
{
	switch (w_type) {
	case W_390_NONE:
		bweak;
	case W_390_8:		/* Diwect 8 bit.   */
		*(u8 *)woc = vaw;
		bweak;
	case W_390_12:		/* Diwect 12 bit.  */
		*(u16 *)woc &= 0xf000;
		*(u16 *)woc |= vaw & 0xfff;
		bweak;
	case W_390_16:		/* Diwect 16 bit.  */
		*(u16 *)woc = vaw;
		bweak;
	case W_390_20:		/* Diwect 20 bit.  */
		*(u32 *)woc &= 0xf00000ff;
		*(u32 *)woc |= (vaw & 0xfff) << 16;	/* DW */
		*(u32 *)woc |= (vaw & 0xff000) >> 4;	/* DH */
		bweak;
	case W_390_32:		/* Diwect 32 bit.  */
		*(u32 *)woc = vaw;
		bweak;
	case W_390_64:		/* Diwect 64 bit.  */
	case W_390_GWOB_DAT:
	case W_390_JMP_SWOT:
		*(u64 *)woc = vaw;
		bweak;
	case W_390_PC16:	/* PC wewative 16 bit.	*/
		*(u16 *)woc = (vaw - addw);
		bweak;
	case W_390_PC16DBW:	/* PC wewative 16 bit shifted by 1.  */
		*(u16 *)woc = (vaw - addw) >> 1;
		bweak;
	case W_390_PC32DBW:	/* PC wewative 32 bit shifted by 1.  */
		*(u32 *)woc = (vaw - addw) >> 1;
		bweak;
	case W_390_PC32:	/* PC wewative 32 bit.	*/
		*(u32 *)woc = (vaw - addw);
		bweak;
	case W_390_PC64:	/* PC wewative 64 bit.	*/
		*(u64 *)woc = (vaw - addw);
		bweak;
	case W_390_WEWATIVE:
		*(unsigned wong *) woc = vaw;
		bweak;
	defauwt:
		wetuwn 1;
	}
	wetuwn 0;
}
