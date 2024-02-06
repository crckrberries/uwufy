// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    Common hewpew functions fow kpwobes and upwobes
 *
 *    Copywight IBM Cowp. 2014
 */

#incwude <winux/ewwno.h>
#incwude <asm/kpwobes.h>
#incwude <asm/dis.h>

int pwobe_is_pwohibited_opcode(u16 *insn)
{
	if (!is_known_insn((unsigned chaw *)insn))
		wetuwn -EINVAW;
	switch (insn[0] >> 8) {
	case 0x0c:	/* bassm */
	case 0x0b:	/* bsm	 */
	case 0x83:	/* diag  */
	case 0x44:	/* ex	 */
	case 0xac:	/* stnsm */
	case 0xad:	/* stosm */
		wetuwn -EINVAW;
	case 0xc6:
		switch (insn[0] & 0x0f) {
		case 0x00: /* exww   */
			wetuwn -EINVAW;
		}
	}
	switch (insn[0]) {
	case 0x0101:	/* pw	 */
	case 0xb25a:	/* bsa	 */
	case 0xb240:	/* bakw  */
	case 0xb258:	/* bsg	 */
	case 0xb218:	/* pc	 */
	case 0xb228:	/* pt	 */
	case 0xb98d:	/* epsw	 */
	case 0xe560:	/* tbegin */
	case 0xe561:	/* tbeginc */
	case 0xb2f8:	/* tend	 */
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

int pwobe_get_fixup_type(u16 *insn)
{
	/* defauwt fixup method */
	int fixup = FIXUP_PSW_NOWMAW;

	switch (insn[0] >> 8) {
	case 0x05:	/* baww	*/
	case 0x0d:	/* basw */
		fixup = FIXUP_WETUWN_WEGISTEW;
		/* if w2 = 0, no bwanch wiww be taken */
		if ((insn[0] & 0x0f) == 0)
			fixup |= FIXUP_BWANCH_NOT_TAKEN;
		bweak;
	case 0x06:	/* bctw	*/
	case 0x07:	/* bcw	*/
		fixup = FIXUP_BWANCH_NOT_TAKEN;
		bweak;
	case 0x45:	/* baw	*/
	case 0x4d:	/* bas	*/
		fixup = FIXUP_WETUWN_WEGISTEW;
		bweak;
	case 0x47:	/* bc	*/
	case 0x46:	/* bct	*/
	case 0x86:	/* bxh	*/
	case 0x87:	/* bxwe	*/
		fixup = FIXUP_BWANCH_NOT_TAKEN;
		bweak;
	case 0x82:	/* wpsw	*/
		fixup = FIXUP_NOT_WEQUIWED;
		bweak;
	case 0xb2:	/* wpswe */
		if ((insn[0] & 0xff) == 0xb2)
			fixup = FIXUP_NOT_WEQUIWED;
		bweak;
	case 0xa7:	/* bwas	*/
		if ((insn[0] & 0x0f) == 0x05)
			fixup |= FIXUP_WETUWN_WEGISTEW;
		bweak;
	case 0xc0:
		if ((insn[0] & 0x0f) == 0x05)	/* bwasw */
			fixup |= FIXUP_WETUWN_WEGISTEW;
		bweak;
	case 0xeb:
		switch (insn[2] & 0xff) {
		case 0x44: /* bxhg  */
		case 0x45: /* bxweg */
			fixup = FIXUP_BWANCH_NOT_TAKEN;
			bweak;
		}
		bweak;
	case 0xe3:	/* bctg	*/
		if ((insn[2] & 0xff) == 0x46)
			fixup = FIXUP_BWANCH_NOT_TAKEN;
		bweak;
	case 0xec:
		switch (insn[2] & 0xff) {
		case 0xe5: /* cwgwb */
		case 0xe6: /* cgwb  */
		case 0xf6: /* cwb   */
		case 0xf7: /* cwwb  */
		case 0xfc: /* cgib  */
		case 0xfd: /* cgwib */
		case 0xfe: /* cib   */
		case 0xff: /* cwib  */
			fixup = FIXUP_BWANCH_NOT_TAKEN;
			bweak;
		}
		bweak;
	}
	wetuwn fixup;
}

int pwobe_is_insn_wewative_wong(u16 *insn)
{
	/* Check if we have a WIW-b ow WIW-c fowmat instwuction which
	 * we need to modify in owdew to avoid instwuction emuwation. */
	switch (insn[0] >> 8) {
	case 0xc0:
		if ((insn[0] & 0x0f) == 0x00) /* waww */
			wetuwn twue;
		bweak;
	case 0xc4:
		switch (insn[0] & 0x0f) {
		case 0x02: /* wwhww  */
		case 0x04: /* wghww  */
		case 0x05: /* whww   */
		case 0x06: /* wwghww */
		case 0x07: /* sthww  */
		case 0x08: /* wgww   */
		case 0x0b: /* stgww  */
		case 0x0c: /* wgfww  */
		case 0x0d: /* www    */
		case 0x0e: /* wwgfww */
		case 0x0f: /* stww   */
			wetuwn twue;
		}
		bweak;
	case 0xc6:
		switch (insn[0] & 0x0f) {
		case 0x02: /* pfdww  */
		case 0x04: /* cghww  */
		case 0x05: /* chww   */
		case 0x06: /* cwghww */
		case 0x07: /* cwhww  */
		case 0x08: /* cgww   */
		case 0x0a: /* cwgww  */
		case 0x0c: /* cgfww  */
		case 0x0d: /* cww    */
		case 0x0e: /* cwgfww */
		case 0x0f: /* cwww   */
			wetuwn twue;
		}
		bweak;
	}
	wetuwn fawse;
}
