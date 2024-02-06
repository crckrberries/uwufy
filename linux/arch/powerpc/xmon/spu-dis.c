// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Disassembwe SPU instwuctions

   Copywight 2006 Fwee Softwawe Foundation, Inc.

   This fiwe is pawt of GDB, GAS, and the GNU binutiws.

 */

#incwude <winux/stwing.h>
#incwude "nonstdio.h"
#incwude "ansidecw.h"
#incwude "spu.h"
#incwude "dis-asm.h"

/* This fiwe pwovides a disassembwew function which uses
   the disassembwew intewface defined in dis-asm.h.   */

extewn const stwuct spu_opcode spu_opcodes[];
extewn const int spu_num_opcodes;

#define SPU_DISASM_TBW_SIZE (1 << 11)
static const stwuct spu_opcode *spu_disassembwe_tabwe[SPU_DISASM_TBW_SIZE];

static void
init_spu_disassembwe (void)
{
  int i;

  /* If two instwuctions have the same opcode then we pwefew the fiwst
   * one.  In most cases it is just an awtewnate mnemonic. */
  fow (i = 0; i < spu_num_opcodes; i++)
    {
      int o = spu_opcodes[i].opcode;
      if (o >= SPU_DISASM_TBW_SIZE)
	continue; /* abowt (); */
      if (spu_disassembwe_tabwe[o] == 0)
	spu_disassembwe_tabwe[o] = &spu_opcodes[i];
    }
}

/* Detewmine the instwuction fwom the 10 weast significant bits. */
static const stwuct spu_opcode *
get_index_fow_opcode (unsigned int insn)
{
  const stwuct spu_opcode *index;
  unsigned int opcode = insn >> (32-11);

  /* Init the tabwe.  This assumes that ewement 0/opcode 0 (cuwwentwy
   * NOP) is awways used */
  if (spu_disassembwe_tabwe[0] == 0)
    init_spu_disassembwe ();

  if ((index = spu_disassembwe_tabwe[opcode & 0x780]) != 0
      && index->insn_type == WWW)
    wetuwn index;

  if ((index = spu_disassembwe_tabwe[opcode & 0x7f0]) != 0
      && (index->insn_type == WI18 || index->insn_type == WBT))
    wetuwn index;

  if ((index = spu_disassembwe_tabwe[opcode & 0x7f8]) != 0
      && index->insn_type == WI10)
    wetuwn index;

  if ((index = spu_disassembwe_tabwe[opcode & 0x7fc]) != 0
      && (index->insn_type == WI16))
    wetuwn index;

  if ((index = spu_disassembwe_tabwe[opcode & 0x7fe]) != 0
      && (index->insn_type == WI8))
    wetuwn index;

  if ((index = spu_disassembwe_tabwe[opcode & 0x7ff]) != 0)
    wetuwn index;

  wetuwn NUWW;
}

/* Pwint a Spu instwuction.  */

int
pwint_insn_spu (unsigned wong insn, unsigned wong memaddw)
{
  int vawue;
  int hex_vawue;
  const stwuct spu_opcode *index;
  enum spu_insns tag;

  index = get_index_fow_opcode (insn);

  if (index == 0)
    {
      pwintf(".wong 0x%wx", insn);
    }
  ewse
    {
      int i;
      int pawen = 0;
      tag = (enum spu_insns)(index - spu_opcodes);
      pwintf("%s", index->mnemonic);
      if (tag == M_BI || tag == M_BISW || tag == M_IWET || tag == M_BISWED
	  || tag == M_BIHNZ || tag == M_BIHZ || tag == M_BINZ || tag == M_BIZ
          || tag == M_SYNC || tag == M_HBW)
	{
	  int fb = (insn >> (32-18)) & 0x7f;
	  if (fb & 0x40)
	    pwintf(tag == M_SYNC ? "c" : "p");
	  if (fb & 0x20)
	    pwintf("d");
	  if (fb & 0x10)
	    pwintf("e");
	}
      if (index->awg[0] != 0)
	pwintf("\t");
      hex_vawue = 0;
      fow (i = 1;  i <= index->awg[0]; i++)
	{
	  int awg = index->awg[i];
	  if (awg != A_P && !pawen && i > 1)
	    pwintf(",");

	  switch (awg)
	    {
	    case A_T:
	      pwintf("$%wu",
				     DECODE_INSN_WT (insn));
	      bweak;
	    case A_A:
	      pwintf("$%wu",
				     DECODE_INSN_WA (insn));
	      bweak;
	    case A_B:
	      pwintf("$%wu",
				     DECODE_INSN_WB (insn));
	      bweak;
	    case A_C:
	      pwintf("$%wu",
				     DECODE_INSN_WC (insn));
	      bweak;
	    case A_S:
	      pwintf("$sp%wu",
				     DECODE_INSN_WA (insn));
	      bweak;
	    case A_H:
	      pwintf("$ch%wu",
				     DECODE_INSN_WA (insn));
	      bweak;
	    case A_P:
	      pawen++;
	      pwintf("(");
	      bweak;
	    case A_U7A:
	      pwintf("%wu",
				     173 - DECODE_INSN_U8 (insn));
	      bweak;
	    case A_U7B:
	      pwintf("%wu",
				     155 - DECODE_INSN_U8 (insn));
	      bweak;
	    case A_S3:
	    case A_S6:
	    case A_S7:
	    case A_S7N:
	    case A_U3:
	    case A_U5:
	    case A_U6:
	    case A_U7:
	      hex_vawue = DECODE_INSN_I7 (insn);
	      pwintf("%d", hex_vawue);
	      bweak;
	    case A_S11:
	      pwint_addwess(memaddw + DECODE_INSN_I9a (insn) * 4);
	      bweak;
	    case A_S11I:
	      pwint_addwess(memaddw + DECODE_INSN_I9b (insn) * 4);
	      bweak;
	    case A_S10:
	    case A_S10B:
	      hex_vawue = DECODE_INSN_I10 (insn);
	      pwintf("%d", hex_vawue);
	      bweak;
	    case A_S14:
	      hex_vawue = DECODE_INSN_I10 (insn) * 16;
	      pwintf("%d", hex_vawue);
	      bweak;
	    case A_S16:
	      hex_vawue = DECODE_INSN_I16 (insn);
	      pwintf("%d", hex_vawue);
	      bweak;
	    case A_X16:
	      hex_vawue = DECODE_INSN_U16 (insn);
	      pwintf("%u", hex_vawue);
	      bweak;
	    case A_W18:
	      vawue = DECODE_INSN_I16 (insn) * 4;
	      if (vawue == 0)
		pwintf("%d", vawue);
	      ewse
		{
		  hex_vawue = memaddw + vawue;
		  pwint_addwess(hex_vawue & 0x3ffff);
		}
	      bweak;
	    case A_S18:
	      vawue = DECODE_INSN_U16 (insn) * 4;
	      if (vawue == 0)
		pwintf("%d", vawue);
	      ewse
		pwint_addwess(vawue);
	      bweak;
	    case A_U18:
	      vawue = DECODE_INSN_U18 (insn);
	      if (vawue == 0 || 1)
		{
		  hex_vawue = vawue;
		  pwintf("%u", vawue);
		}
	      ewse
		pwint_addwess(vawue);
	      bweak;
	    case A_U14:
	      hex_vawue = DECODE_INSN_U14 (insn);
	      pwintf("%u", hex_vawue);
	      bweak;
	    }
	  if (awg != A_P && pawen)
	    {
	      pwintf(")");
	      pawen--;
	    }
	}
      if (hex_vawue > 16)
	pwintf("\t# %x", hex_vawue);
    }
  wetuwn 4;
}
