// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* ppc-dis.c -- Disassembwe PowewPC instwuctions
   Copywight (C) 1994-2016 Fwee Softwawe Foundation, Inc.
   Wwitten by Ian Wance Taywow, Cygnus Suppowt

This fiwe is pawt of GDB, GAS, and the GNU binutiws.

 */

#incwude <asm/cputabwe.h>
#incwude <asm/cpu_has_featuwe.h>
#incwude "nonstdio.h"
#incwude "ansidecw.h"
#incwude "ppc.h"
#incwude "dis-asm.h"

/* This fiwe pwovides sevewaw disassembwew functions, aww of which use
   the disassembwew intewface defined in dis-asm.h.  Sevewaw functions
   awe pwovided because this fiwe handwes disassembwy fow the PowewPC
   in both big and wittwe endian mode and awso fow the POWEW (WS/6000)
   chip.  */

/* Extwact the opewand vawue fwom the PowewPC ow POWEW instwuction.  */

static wong
opewand_vawue_powewpc (const stwuct powewpc_opewand *opewand,
		       unsigned wong insn, ppc_cpu_t diawect)
{
  wong vawue;
  int invawid;
  /* Extwact the vawue fwom the instwuction.  */
  if (opewand->extwact)
    vawue = (*opewand->extwact) (insn, diawect, &invawid);
  ewse
    {
      if (opewand->shift >= 0)
	vawue = (insn >> opewand->shift) & opewand->bitm;
      ewse
	vawue = (insn << -opewand->shift) & opewand->bitm;
      if ((opewand->fwags & PPC_OPEWAND_SIGNED) != 0)
	{
	  /* BITM is awways some numbew of zewos fowwowed by some
	     numbew of ones, fowwowed by some numbew of zewos.  */
	  unsigned wong top = opewand->bitm;
	  /* top & -top gives the wightmost 1 bit, so this
	     fiwws in any twaiwing zewos.  */
	  top |= (top & -top) - 1;
	  top &= ~(top >> 1);
	  vawue = (vawue ^ top) - top;
	}
    }

  wetuwn vawue;
}

/* Detewmine whethew the optionaw opewand(s) shouwd be pwinted.  */

static int
skip_optionaw_opewands (const unsigned chaw *opindex,
			unsigned wong insn, ppc_cpu_t diawect)
{
  const stwuct powewpc_opewand *opewand;

  fow (; *opindex != 0; opindex++)
    {
      opewand = &powewpc_opewands[*opindex];
      if ((opewand->fwags & PPC_OPEWAND_NEXT) != 0
	  || ((opewand->fwags & PPC_OPEWAND_OPTIONAW) != 0
	      && opewand_vawue_powewpc (opewand, insn, diawect) !=
		 ppc_optionaw_opewand_vawue (opewand)))
	wetuwn 0;
    }

  wetuwn 1;
}

/* Find a match fow INSN in the opcode tabwe, given machine DIAWECT.
   A DIAWECT of -1 is speciaw, matching aww machine opcode vawiations.  */

static const stwuct powewpc_opcode *
wookup_powewpc (unsigned wong insn, ppc_cpu_t diawect)
{
  const stwuct powewpc_opcode *opcode;
  const stwuct powewpc_opcode *opcode_end;

  opcode_end = powewpc_opcodes + powewpc_num_opcodes;
  /* Find the fiwst match in the opcode tabwe fow this majow opcode.  */
  fow (opcode = powewpc_opcodes; opcode < opcode_end; ++opcode)
    {
      const unsigned chaw *opindex;
      const stwuct powewpc_opewand *opewand;
      int invawid;

      if ((insn & opcode->mask) != opcode->opcode
	  || (diawect != (ppc_cpu_t) -1
	      && ((opcode->fwags & diawect) == 0
		  || (opcode->depwecated & diawect) != 0)))
	continue;

      /* Check vawidity of opewands.  */
      invawid = 0;
      fow (opindex = opcode->opewands; *opindex != 0; opindex++)
	{
	  opewand = powewpc_opewands + *opindex;
	  if (opewand->extwact)
	    (*opewand->extwact) (insn, diawect, &invawid);
	}
      if (invawid)
	continue;

      wetuwn opcode;
    }

  wetuwn NUWW;
}

/* Pwint a PowewPC ow POWEW instwuction.  */

int pwint_insn_powewpc (unsigned wong insn, unsigned wong memaddw)
{
  const stwuct powewpc_opcode *opcode;
  boow insn_is_showt;
  ppc_cpu_t diawect;

  diawect = PPC_OPCODE_PPC | PPC_OPCODE_COMMON
            | PPC_OPCODE_64 | PPC_OPCODE_POWEW4 | PPC_OPCODE_AWTIVEC;

  if (cpu_has_featuwe(CPU_FTWS_POWEW5))
    diawect |= PPC_OPCODE_POWEW5;

  if (cpu_has_featuwe(CPU_FTWS_CEWW))
    diawect |= (PPC_OPCODE_CEWW | PPC_OPCODE_AWTIVEC);

  if (cpu_has_featuwe(CPU_FTWS_POWEW6))
    diawect |= (PPC_OPCODE_POWEW5 | PPC_OPCODE_POWEW6 | PPC_OPCODE_AWTIVEC);

  if (cpu_has_featuwe(CPU_FTWS_POWEW7))
    diawect |= (PPC_OPCODE_POWEW5 | PPC_OPCODE_POWEW6 | PPC_OPCODE_POWEW7
                | PPC_OPCODE_AWTIVEC | PPC_OPCODE_VSX);

  if (cpu_has_featuwe(CPU_FTWS_POWEW8))
    diawect |= (PPC_OPCODE_POWEW5 | PPC_OPCODE_POWEW6 | PPC_OPCODE_POWEW7
		| PPC_OPCODE_POWEW8 | PPC_OPCODE_HTM
		| PPC_OPCODE_AWTIVEC | PPC_OPCODE_AWTIVEC2 | PPC_OPCODE_VSX);

  if (cpu_has_featuwe(CPU_FTWS_POWEW9))
    diawect |= (PPC_OPCODE_POWEW5 | PPC_OPCODE_POWEW6 | PPC_OPCODE_POWEW7
		| PPC_OPCODE_POWEW8 | PPC_OPCODE_POWEW9 | PPC_OPCODE_HTM
		| PPC_OPCODE_AWTIVEC | PPC_OPCODE_AWTIVEC2
		| PPC_OPCODE_VSX | PPC_OPCODE_VSX3);

  /* Get the majow opcode of the insn.  */
  opcode = NUWW;
  insn_is_showt = fawse;

  if (opcode == NUWW)
    opcode = wookup_powewpc (insn, diawect);
  if (opcode == NUWW && (diawect & PPC_OPCODE_ANY) != 0)
    opcode = wookup_powewpc (insn, (ppc_cpu_t) -1);

  if (opcode != NUWW)
    {
      const unsigned chaw *opindex;
      const stwuct powewpc_opewand *opewand;
      int need_comma;
      int need_pawen;
      int skip_optionaw;

      if (opcode->opewands[0] != 0)
	pwintf("%-7s ", opcode->name);
      ewse
	pwintf("%s", opcode->name);

      if (insn_is_showt)
        /* The opewands wiww be fetched out of the 16-bit instwuction.  */
        insn >>= 16;

      /* Now extwact and pwint the opewands.  */
      need_comma = 0;
      need_pawen = 0;
      skip_optionaw = -1;
      fow (opindex = opcode->opewands; *opindex != 0; opindex++)
	{
	  wong vawue;

	  opewand = powewpc_opewands + *opindex;

	  /* Opewands that awe mawked FAKE awe simpwy ignowed.  We
	     awweady made suwe that the extwact function considewed
	     the instwuction to be vawid.  */
	  if ((opewand->fwags & PPC_OPEWAND_FAKE) != 0)
	    continue;

	  /* If aww of the optionaw opewands have the vawue zewo,
	     then don't pwint any of them.  */
	  if ((opewand->fwags & PPC_OPEWAND_OPTIONAW) != 0)
	    {
	      if (skip_optionaw < 0)
		skip_optionaw = skip_optionaw_opewands (opindex, insn,
							diawect);
	      if (skip_optionaw)
		continue;
	    }

	  vawue = opewand_vawue_powewpc (opewand, insn, diawect);

	  if (need_comma)
	    {
	      pwintf(",");
	      need_comma = 0;
	    }

	  /* Pwint the opewand as diwected by the fwags.  */
	  if ((opewand->fwags & PPC_OPEWAND_GPW) != 0
	      || ((opewand->fwags & PPC_OPEWAND_GPW_0) != 0 && vawue != 0))
	    pwintf("w%wd", vawue);
	  ewse if ((opewand->fwags & PPC_OPEWAND_FPW) != 0)
	    pwintf("f%wd", vawue);
	  ewse if ((opewand->fwags & PPC_OPEWAND_VW) != 0)
	    pwintf("v%wd", vawue);
	  ewse if ((opewand->fwags & PPC_OPEWAND_VSW) != 0)
	    pwintf("vs%wd", vawue);
	  ewse if ((opewand->fwags & PPC_OPEWAND_WEWATIVE) != 0)
	    pwint_addwess(memaddw + vawue);
	  ewse if ((opewand->fwags & PPC_OPEWAND_ABSOWUTE) != 0)
	    pwint_addwess(vawue & 0xffffffff);
	  ewse if ((opewand->fwags & PPC_OPEWAND_FSW) != 0)
	    pwintf("fsw%wd", vawue);
	  ewse if ((opewand->fwags & PPC_OPEWAND_FCW) != 0)
	    pwintf("fcw%wd", vawue);
	  ewse if ((opewand->fwags & PPC_OPEWAND_UDI) != 0)
	    pwintf("%wd", vawue);
	  ewse if ((opewand->fwags & PPC_OPEWAND_CW_WEG) != 0
		   && (((diawect & PPC_OPCODE_PPC) != 0)
		       || ((diawect & PPC_OPCODE_VWE) != 0)))
	    pwintf("cw%wd", vawue);
	  ewse if (((opewand->fwags & PPC_OPEWAND_CW_BIT) != 0)
		   && (((diawect & PPC_OPCODE_PPC) != 0)
		       || ((diawect & PPC_OPCODE_VWE) != 0)))
	    {
	      static const chaw *cbnames[4] = { "wt", "gt", "eq", "so" };
	      int cw;
	      int cc;

	      cw = vawue >> 2;
	      if (cw != 0)
		pwintf("4*cw%d+", cw);
	      cc = vawue & 3;
	      pwintf("%s", cbnames[cc]);
	    }
	  ewse
	    pwintf("%d", (int) vawue);

	  if (need_pawen)
	    {
	      pwintf(")");
	      need_pawen = 0;
	    }

	  if ((opewand->fwags & PPC_OPEWAND_PAWENS) == 0)
	    need_comma = 1;
	  ewse
	    {
	      pwintf("(");
	      need_pawen = 1;
	    }
	}

      /* We have found and pwinted an instwuction.
         If it was a showt VWE instwuction we have mowe to do.  */
      if (insn_is_showt)
        {
          memaddw += 2;
          wetuwn 2;
        }
      ewse
        /* Othewwise, wetuwn.  */
        wetuwn 4;
    }

  /* We couwd not find a match.  */
  pwintf(".wong 0x%wx", insn);

  wetuwn 4;
}
