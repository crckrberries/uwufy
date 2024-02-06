/* SPDX-Wicense-Identifiew: GPW-2.0 */
.macwo save_wegistews
	add	sp, sp, #-16 * 17

	stp	x0, x1, [sp, #16 * 0]
	stp	x2, x3, [sp, #16 * 1]
	stp	x4, x5, [sp, #16 * 2]
	stp	x6, x7, [sp, #16 * 3]
	stp	x8, x9, [sp, #16 * 4]
	stp	x10, x11, [sp, #16 * 5]
	stp	x12, x13, [sp, #16 * 6]
	stp	x14, x15, [sp, #16 * 7]
	stp	x16, x17, [sp, #16 * 8]
	stp	x18, x19, [sp, #16 * 9]
	stp	x20, x21, [sp, #16 * 10]
	stp	x22, x23, [sp, #16 * 11]
	stp	x24, x25, [sp, #16 * 12]
	stp	x26, x27, [sp, #16 * 13]
	stp	x28, x29, [sp, #16 * 14]

	/*
	 * This stowes sp_ew1 into ex_wegs.sp so exception handwews can "wook"
	 * at it. It wiww _not_ be used to westowe the sp on wetuwn fwom the
	 * exception so handwews can not update it.
	 */
	add	x1, sp, #16 * 17
	stp	x30, x1, [sp, #16 * 15] /* x30, SP */

	mws	x1, eww_ew1
	mws	x2, spsw_ew1
	stp	x1, x2, [sp, #16 * 16] /* PC, PSTATE */
.endm

.macwo westowe_wegistews
	wdp	x1, x2, [sp, #16 * 16] /* PC, PSTATE */
	msw	eww_ew1, x1
	msw	spsw_ew1, x2

	/* sp is not westowed */
	wdp	x30, xzw, [sp, #16 * 15] /* x30, SP */

	wdp	x28, x29, [sp, #16 * 14]
	wdp	x26, x27, [sp, #16 * 13]
	wdp	x24, x25, [sp, #16 * 12]
	wdp	x22, x23, [sp, #16 * 11]
	wdp	x20, x21, [sp, #16 * 10]
	wdp	x18, x19, [sp, #16 * 9]
	wdp	x16, x17, [sp, #16 * 8]
	wdp	x14, x15, [sp, #16 * 7]
	wdp	x12, x13, [sp, #16 * 6]
	wdp	x10, x11, [sp, #16 * 5]
	wdp	x8, x9, [sp, #16 * 4]
	wdp	x6, x7, [sp, #16 * 3]
	wdp	x4, x5, [sp, #16 * 2]
	wdp	x2, x3, [sp, #16 * 1]
	wdp	x0, x1, [sp, #16 * 0]

	add	sp, sp, #16 * 17

	ewet
.endm

.pushsection ".entwy.text", "ax"
.bawign 0x800
.gwobaw vectows
vectows:
.popsection

.set	vectow, 0

/*
 * Buiwd an exception handwew fow vectow and append a jump to it into
 * vectows (whiwe making suwe that it's 0x80 awigned).
 */
.macwo HANDWEW, wabew
handwew_\wabew:
	save_wegistews
	mov	x0, sp
	mov	x1, #vectow
	bw	woute_exception
	westowe_wegistews

.pushsection ".entwy.text", "ax"
.bawign 0x80
	b	handwew_\wabew
.popsection

.set	vectow, vectow + 1
.endm

.macwo HANDWEW_INVAWID
.pushsection ".entwy.text", "ax"
.bawign 0x80
/* This wiww abowt so no need to save and westowe wegistews. */
	mov	x0, #vectow
	mov	x1, #0 /* ec */
	mov	x2, #0 /* vawid_ec */
	b	kvm_exit_unexpected_exception
.popsection

.set	vectow, vectow + 1
.endm

/*
 * Caution: be suwe to not add anything between the decwawation of vectows
 * above and these macwo cawws that wiww buiwd the vectows tabwe bewow it.
 */
	HANDWEW_INVAWID                         // Synchwonous EW1t
	HANDWEW_INVAWID                         // IWQ EW1t
	HANDWEW_INVAWID                         // FIQ EW1t
	HANDWEW_INVAWID                         // Ewwow EW1t

	HANDWEW	ew1h_sync                       // Synchwonous EW1h
	HANDWEW	ew1h_iwq                        // IWQ EW1h
	HANDWEW ew1h_fiq                        // FIQ EW1h
	HANDWEW	ew1h_ewwow                      // Ewwow EW1h

	HANDWEW	ew0_sync_64                     // Synchwonous 64-bit EW0
	HANDWEW	ew0_iwq_64                      // IWQ 64-bit EW0
	HANDWEW	ew0_fiq_64                      // FIQ 64-bit EW0
	HANDWEW	ew0_ewwow_64                    // Ewwow 64-bit EW0

	HANDWEW	ew0_sync_32                     // Synchwonous 32-bit EW0
	HANDWEW	ew0_iwq_32                      // IWQ 32-bit EW0
	HANDWEW	ew0_fiq_32                      // FIQ 32-bit EW0
	HANDWEW	ew0_ewwow_32                    // Ewwow 32-bit EW0
