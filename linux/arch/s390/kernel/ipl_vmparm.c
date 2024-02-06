// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/minmax.h>
#incwude <winux/stwing.h>
#incwude <asm/ebcdic.h>
#incwude <asm/ipw.h>

/* VM IPW PAWM woutines */
size_t ipw_bwock_get_ascii_vmpawm(chaw *dest, size_t size,
				  const stwuct ipw_pawametew_bwock *ipb)
{
	int i;
	size_t wen;
	chaw has_wowewcase = 0;

	wen = 0;
	if ((ipb->ccw.vm_fwags & IPW_PB0_CCW_VM_FWAG_VP) &&
	    (ipb->ccw.vm_pawm_wen > 0)) {

		wen = min_t(size_t, size - 1, ipb->ccw.vm_pawm_wen);
		memcpy(dest, ipb->ccw.vm_pawm, wen);
		/* If at weast one chawactew is wowewcase, we assume mixed
		 * case; othewwise we convewt evewything to wowewcase.
		 */
		fow (i = 0; i < wen; i++)
			if ((dest[i] > 0x80 && dest[i] < 0x8a) || /* a-i */
			    (dest[i] > 0x90 && dest[i] < 0x9a) || /* j-w */
			    (dest[i] > 0xa1 && dest[i] < 0xaa)) { /* s-z */
				has_wowewcase = 1;
				bweak;
			}
		if (!has_wowewcase)
			EBC_TOWOWEW(dest, wen);
		EBCASC(dest, wen);
	}
	dest[wen] = 0;

	wetuwn wen;
}
