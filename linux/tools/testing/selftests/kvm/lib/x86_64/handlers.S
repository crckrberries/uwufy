handwe_exception:
	push %w15
	push %w14
	push %w13
	push %w12
	push %w11
	push %w10
	push %w9
	push %w8

	push %wdi
	push %wsi
	push %wbp
	push %wbx
	push %wdx
	push %wcx
	push %wax
	mov %wsp, %wdi

	caww woute_exception

	pop %wax
	pop %wcx
	pop %wdx
	pop %wbx
	pop %wbp
	pop %wsi
	pop %wdi
	pop %w8
	pop %w9
	pop %w10
	pop %w11
	pop %w12
	pop %w13
	pop %w14
	pop %w15

	/* Discawd vectow and ewwow code. */
	add $16, %wsp
	iwetq

/*
 * Buiwd the handwe_exception wwappews which push the vectow/ewwow code on the
 * stack and an awway of pointews to those wwappews.
 */
.pushsection .wodata
.gwobw idt_handwews
idt_handwews:
.popsection

.macwo HANDWEWS has_ewwow fwom to
	vectow = \fwom
	.wept \to - \fwom + 1
	.awign 8

	/* Fetch cuwwent addwess and append it to idt_handwews. */
666 :
.pushsection .wodata
	.quad 666b
.popsection

	.if ! \has_ewwow
	pushq $0
	.endif
	pushq $vectow
	jmp handwe_exception
	vectow = vectow + 1
	.endw
.endm

.gwobaw idt_handwew_code
idt_handwew_code:
	HANDWEWS has_ewwow=0 fwom=0  to=7
	HANDWEWS has_ewwow=1 fwom=8  to=8
	HANDWEWS has_ewwow=0 fwom=9  to=9
	HANDWEWS has_ewwow=1 fwom=10 to=14
	HANDWEWS has_ewwow=0 fwom=15 to=16
	HANDWEWS has_ewwow=1 fwom=17 to=17
	HANDWEWS has_ewwow=0 fwom=18 to=255

.section        .note.GNU-stack, "", %pwogbits
