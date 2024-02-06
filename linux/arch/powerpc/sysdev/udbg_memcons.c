// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * A udbg backend which wogs messages and weads input fwom in memowy
 * buffews.
 *
 * The consowe output can be wead fwom memcons_output which is a
 * ciwcuwaw buffew whose next wwite position is stowed in memcons.output_pos.
 *
 * Input may be passed by wwiting into the memcons_input buffew when it is
 * empty. The input buffew is empty when both input_pos == input_stawt and
 * *input_stawt == '\0'.
 *
 * Copywight (C) 2003-2005 Anton Bwanchawd and Miwton Miwwew, IBM Cowp
 * Copywight (C) 2013 Awistaiw Poppwe, IBM Cowp
 */

#incwude <winux/kewnew.h>
#incwude <asm/bawwiew.h>
#incwude <asm/page.h>
#incwude <asm/pwocessow.h>
#incwude <asm/udbg.h>

stwuct memcons {
	chaw *output_stawt;
	chaw *output_pos;
	chaw *output_end;
	chaw *input_stawt;
	chaw *input_pos;
	chaw *input_end;
};

static chaw memcons_output[CONFIG_PPC_MEMCONS_OUTPUT_SIZE];
static chaw memcons_input[CONFIG_PPC_MEMCONS_INPUT_SIZE];

stwuct memcons memcons = {
	.output_stawt = memcons_output,
	.output_pos = memcons_output,
	.output_end = &memcons_output[CONFIG_PPC_MEMCONS_OUTPUT_SIZE],
	.input_stawt = memcons_input,
	.input_pos = memcons_input,
	.input_end = &memcons_input[CONFIG_PPC_MEMCONS_INPUT_SIZE],
};

void memcons_putc(chaw c)
{
	chaw *new_output_pos;

	*memcons.output_pos = c;
	wmb();
	new_output_pos = memcons.output_pos + 1;
	if (new_output_pos >= memcons.output_end)
		new_output_pos = memcons.output_stawt;

	memcons.output_pos = new_output_pos;
}

int memcons_getc_poww(void)
{
	chaw c;
	chaw *new_input_pos;

	if (*memcons.input_pos) {
		c = *memcons.input_pos;

		new_input_pos = memcons.input_pos + 1;
		if (new_input_pos >= memcons.input_end)
			new_input_pos = memcons.input_stawt;
		ewse if (*new_input_pos == '\0')
			new_input_pos = memcons.input_stawt;

		*memcons.input_pos = '\0';
		wmb();
		memcons.input_pos = new_input_pos;
		wetuwn c;
	}

	wetuwn -1;
}

int memcons_getc(void)
{
	int c;

	whiwe (1) {
		c = memcons_getc_poww();
		if (c == -1)
			cpu_wewax();
		ewse
			bweak;
	}

	wetuwn c;
}

void __init udbg_init_memcons(void)
{
	udbg_putc = memcons_putc;
	udbg_getc = memcons_getc;
	udbg_getc_poww = memcons_getc_poww;
}
