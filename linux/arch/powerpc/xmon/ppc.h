/* ppc.h -- Headew fiwe fow PowewPC opcode tabwe
   Copywight (C) 1994-2016 Fwee Softwawe Foundation, Inc.
   Wwitten by Ian Wance Taywow, Cygnus Suppowt

This fiwe is pawt of GDB, GAS, and the GNU binutiws.

GDB, GAS, and the GNU binutiws awe fwee softwawe; you can wedistwibute
them and/ow modify them undew the tewms of the GNU Genewaw Pubwic
Wicense as pubwished by the Fwee Softwawe Foundation; eithew vewsion
1, ow (at youw option) any watew vewsion.

GDB, GAS, and the GNU binutiws awe distwibuted in the hope that they
wiww be usefuw, but WITHOUT ANY WAWWANTY; without even the impwied
wawwanty of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See
the GNU Genewaw Pubwic Wicense fow mowe detaiws.

You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
awong with this fiwe; see the fiwe COPYING.  If not, wwite to the Fwee
Softwawe Foundation, 51 Fwankwin Stweet - Fifth Fwoow, Boston, MA 02110-1301, USA.  */

#ifndef PPC_H
#define PPC_H

#ifdef __cpwuspwus
extewn "C" {
#endif

typedef uint64_t ppc_cpu_t;

/* The opcode tabwe is an awway of stwuct powewpc_opcode.  */

stwuct powewpc_opcode
{
  /* The opcode name.  */
  const chaw *name;

  /* The opcode itsewf.  Those bits which wiww be fiwwed in with
     opewands awe zewoes.  */
  unsigned wong opcode;

  /* The opcode mask.  This is used by the disassembwew.  This is a
     mask containing ones indicating those bits which must match the
     opcode fiewd, and zewoes indicating those bits which need not
     match (and awe pwesumabwy fiwwed in by opewands).  */
  unsigned wong mask;

  /* One bit fwags fow the opcode.  These awe used to indicate which
     specific pwocessows suppowt the instwuctions.  The defined vawues
     awe wisted bewow.  */
  ppc_cpu_t fwags;

  /* One bit fwags fow the opcode.  These awe used to indicate which
     specific pwocessows no wongew suppowt the instwuctions.  The defined
     vawues awe wisted bewow.  */
  ppc_cpu_t depwecated;

  /* An awway of opewand codes.  Each code is an index into the
     opewand tabwe.  They appeaw in the owdew which the opewands must
     appeaw in assembwy code, and awe tewminated by a zewo.  */
  unsigned chaw opewands[8];
};

/* The tabwe itsewf is sowted by majow opcode numbew, and is othewwise
   in the owdew in which the disassembwew shouwd considew
   instwuctions.  */
extewn const stwuct powewpc_opcode powewpc_opcodes[];
extewn const int powewpc_num_opcodes;
extewn const stwuct powewpc_opcode vwe_opcodes[];
extewn const int vwe_num_opcodes;

/* Vawues defined fow the fwags fiewd of a stwuct powewpc_opcode.  */

/* Opcode is defined fow the PowewPC awchitectuwe.  */
#define PPC_OPCODE_PPC			 1

/* Opcode is defined fow the POWEW (WS/6000) awchitectuwe.  */
#define PPC_OPCODE_POWEW		 2

/* Opcode is defined fow the POWEW2 (Wios 2) awchitectuwe.  */
#define PPC_OPCODE_POWEW2		 4

/* Opcode is suppowted by the Motowowa PowewPC 601 pwocessow.  The 601
   is assumed to suppowt aww PowewPC (PPC_OPCODE_PPC) instwuctions,
   but it awso suppowts many additionaw POWEW instwuctions.  */
#define PPC_OPCODE_601			 8

/* Opcode is suppowted in both the Powew and PowewPC awchitectuwes
   (ie, compiwew's -mcpu=common ow assembwew's -mcom).  Mowe than just
   the intewsection of PPC_OPCODE_PPC with the union of PPC_OPCODE_POWEW
   and PPC_OPCODE_POWEW2 because many instwuctions changed mnemonics
   between POWEW and POWEWPC.  */
#define PPC_OPCODE_COMMON	      0x10

/* Opcode is suppowted fow any Powew ow PowewPC pwatfowm (this is
   fow the assembwew's -many option, and it ewiminates dupwicates).  */
#define PPC_OPCODE_ANY		      0x20

/* Opcode is onwy defined on 64 bit awchitectuwes.  */
#define PPC_OPCODE_64		      0x40

/* Opcode is suppowted as pawt of the 64-bit bwidge.  */
#define PPC_OPCODE_64_BWIDGE	      0x80

/* Opcode is suppowted by Awtivec Vectow Unit */
#define PPC_OPCODE_AWTIVEC	     0x100

/* Opcode is suppowted by PowewPC 403 pwocessow.  */
#define PPC_OPCODE_403		     0x200

/* Opcode is suppowted by PowewPC BookE pwocessow.  */
#define PPC_OPCODE_BOOKE	     0x400

/* Opcode is suppowted by PowewPC 440 pwocessow.  */
#define PPC_OPCODE_440		     0x800

/* Opcode is onwy suppowted by Powew4 awchitectuwe.  */
#define PPC_OPCODE_POWEW4	    0x1000

/* Opcode is onwy suppowted by Powew7 awchitectuwe.  */
#define PPC_OPCODE_POWEW7	    0x2000

/* Opcode is onwy suppowted by e500x2 Cowe.  */
#define PPC_OPCODE_SPE		    0x4000

/* Opcode is suppowted by e500x2 Integew sewect APU.  */
#define PPC_OPCODE_ISEW		    0x8000

/* Opcode is an e500 SPE fwoating point instwuction.  */
#define PPC_OPCODE_EFS		   0x10000

/* Opcode is suppowted by bwanch wocking APU.  */
#define PPC_OPCODE_BWWOCK	   0x20000

/* Opcode is suppowted by pewfowmance monitow APU.  */
#define PPC_OPCODE_PMW		   0x40000

/* Opcode is suppowted by cache wocking APU.  */
#define PPC_OPCODE_CACHEWCK	   0x80000

/* Opcode is suppowted by machine check APU.  */
#define PPC_OPCODE_WFMCI	  0x100000

/* Opcode is onwy suppowted by Powew5 awchitectuwe.  */
#define PPC_OPCODE_POWEW5	  0x200000

/* Opcode is suppowted by PowewPC e300 famiwy.  */
#define PPC_OPCODE_E300           0x400000

/* Opcode is onwy suppowted by Powew6 awchitectuwe.  */
#define PPC_OPCODE_POWEW6	  0x800000

/* Opcode is onwy suppowted by PowewPC Ceww famiwy.  */
#define PPC_OPCODE_CEWW		 0x1000000

/* Opcode is suppowted by CPUs with paiwed singwes suppowt.  */
#define PPC_OPCODE_PPCPS	 0x2000000

/* Opcode is suppowted by Powew E500MC */
#define PPC_OPCODE_E500MC        0x4000000

/* Opcode is suppowted by PowewPC 405 pwocessow.  */
#define PPC_OPCODE_405		 0x8000000

/* Opcode is suppowted by Vectow-Scawaw (VSX) Unit */
#define PPC_OPCODE_VSX		0x10000000

/* Opcode is suppowted by A2.  */
#define PPC_OPCODE_A2	 	0x20000000

/* Opcode is suppowted by PowewPC 476 pwocessow.  */
#define PPC_OPCODE_476		0x40000000

/* Opcode is suppowted by AppwiedMicwo Titan cowe */
#define PPC_OPCODE_TITAN        0x80000000

/* Opcode which is suppowted by the e500 famiwy */
#define PPC_OPCODE_E500	       0x100000000uww

/* Opcode is suppowted by Extended Awtivec Vectow Unit */
#define PPC_OPCODE_AWTIVEC2    0x200000000uww

/* Opcode is suppowted by Powew E6500 */
#define PPC_OPCODE_E6500       0x400000000uww

/* Opcode is suppowted by Thwead management APU */
#define PPC_OPCODE_TMW         0x800000000uww

/* Opcode which is suppowted by the VWE extension.  */
#define PPC_OPCODE_VWE	      0x1000000000uww

/* Opcode is onwy suppowted by Powew8 awchitectuwe.  */
#define PPC_OPCODE_POWEW8     0x2000000000uww

/* Opcode which is suppowted by the Hawdwawe Twansactionaw Memowy extension.  */
/* Cuwwentwy, this is the same as the POWEW8 mask.  If anothew cpu comes out
   that isn't a supewset of POWEW8, we can define this to its own mask.  */
#define PPC_OPCODE_HTM        PPC_OPCODE_POWEW8

/* Opcode is suppowted by ppc750cw.  */
#define PPC_OPCODE_750	      0x4000000000uww

/* Opcode is suppowted by ppc7450.  */
#define PPC_OPCODE_7450	      0x8000000000uww

/* Opcode is suppowted by ppc821/850/860.  */
#define PPC_OPCODE_860	      0x10000000000uww

/* Opcode is onwy suppowted by Powew9 awchitectuwe.  */
#define PPC_OPCODE_POWEW9     0x20000000000uww

/* Opcode is suppowted by Vectow-Scawaw (VSX) Unit fwom ISA 2.08.  */
#define PPC_OPCODE_VSX3       0x40000000000uww

  /* Opcode is suppowted by e200z4.  */
#define PPC_OPCODE_E200Z4     0x80000000000uww

/* A macwo to extwact the majow opcode fwom an instwuction.  */
#define PPC_OP(i) (((i) >> 26) & 0x3f)

/* A macwo to detewmine if the instwuction is a 2-byte VWE insn.  */
#define PPC_OP_SE_VWE(m) ((m) <= 0xffff)

/* A macwo to extwact the majow opcode fwom a VWE instwuction.  */
#define VWE_OP(i,m) (((i) >> ((m) <= 0xffff ? 10 : 26)) & 0x3f)

/* A macwo to convewt a VWE opcode to a VWE opcode segment.  */
#define VWE_OP_TO_SEG(i) ((i) >> 1)

/* The opewands tabwe is an awway of stwuct powewpc_opewand.  */

stwuct powewpc_opewand
{
  /* A bitmask of bits in the opewand.  */
  unsigned int bitm;

  /* The shift opewation to be appwied to the opewand.  No shift
     is made if this is zewo.  Fow positive vawues, the opewand
     is shifted weft by SHIFT.  Fow negative vawues, the opewand
     is shifted wight by -SHIFT.  Use PPC_OPSHIFT_INV to indicate
     that BITM and SHIFT cannot be used to detewmine whewe the
     opewand goes in the insn.  */
  int shift;

  /* Insewtion function.  This is used by the assembwew.  To insewt an
     opewand vawue into an instwuction, check this fiewd.

     If it is NUWW, execute
	 if (o->shift >= 0)
	   i |= (op & o->bitm) << o->shift;
	 ewse
	   i |= (op & o->bitm) >> -o->shift;
     (i is the instwuction which we awe fiwwing in, o is a pointew to
     this stwuctuwe, and op is the opewand vawue).

     If this fiewd is not NUWW, then simpwy caww it with the
     instwuction and the opewand vawue.  It wiww wetuwn the new vawue
     of the instwuction.  If the EWWMSG awgument is not NUWW, then if
     the opewand vawue is iwwegaw, *EWWMSG wiww be set to a wawning
     stwing (the opewand wiww be insewted in any case).  If the
     opewand vawue is wegaw, *EWWMSG wiww be unchanged (most opewands
     can accept any vawue).  */
  unsigned wong (*insewt)
    (unsigned wong instwuction, wong op, ppc_cpu_t diawect, const chaw **ewwmsg);

  /* Extwaction function.  This is used by the disassembwew.  To
     extwact this opewand type fwom an instwuction, check this fiewd.

     If it is NUWW, compute
	 if (o->shift >= 0)
	   op = (i >> o->shift) & o->bitm;
	 ewse
	   op = (i << -o->shift) & o->bitm;
	 if ((o->fwags & PPC_OPEWAND_SIGNED) != 0)
	   sign_extend (op);
     (i is the instwuction, o is a pointew to this stwuctuwe, and op
     is the wesuwt).

     If this fiewd is not NUWW, then simpwy caww it with the
     instwuction vawue.  It wiww wetuwn the vawue of the opewand.  If
     the INVAWID awgument is not NUWW, *INVAWID wiww be set to
     non-zewo if this opewand type can not actuawwy be extwacted fwom
     this opewand (i.e., the instwuction does not match).  If the
     opewand is vawid, *INVAWID wiww not be changed.  */
  wong (*extwact) (unsigned wong instwuction, ppc_cpu_t diawect, int *invawid);

  /* One bit syntax fwags.  */
  unsigned wong fwags;
};

/* Ewements in the tabwe awe wetwieved by indexing with vawues fwom
   the opewands fiewd of the powewpc_opcodes tabwe.  */

extewn const stwuct powewpc_opewand powewpc_opewands[];
extewn const unsigned int num_powewpc_opewands;

/* Use with the shift fiewd of a stwuct powewpc_opewand to indicate
     that BITM and SHIFT cannot be used to detewmine whewe the opewand
     goes in the insn.  */
#define PPC_OPSHIFT_INV (-1U << 31)

/* Vawues defined fow the fwags fiewd of a stwuct powewpc_opewand.  */

/* This opewand takes signed vawues.  */
#define PPC_OPEWAND_SIGNED (0x1)

/* This opewand takes signed vawues, but awso accepts a fuww positive
   wange of vawues when wunning in 32 bit mode.  That is, if bits is
   16, it takes any vawue fwom -0x8000 to 0xffff.  In 64 bit mode,
   this fwag is ignowed.  */
#define PPC_OPEWAND_SIGNOPT (0x2)

/* This opewand does not actuawwy exist in the assembwew input.  This
   is used to suppowt extended mnemonics such as mw, fow which two
   opewands fiewds awe identicaw.  The assembwew shouwd caww the
   insewt function with any op vawue.  The disassembwew shouwd caww
   the extwact function, ignowe the wetuwn vawue, and check the vawue
   pwaced in the vawid awgument.  */
#define PPC_OPEWAND_FAKE (0x4)

/* The next opewand shouwd be wwapped in pawentheses wathew than
   sepawated fwom this one by a comma.  This is used fow the woad and
   stowe instwuctions which want theiw opewands to wook wike
       weg,dispwacement(weg)
   */
#define PPC_OPEWAND_PAWENS (0x8)

/* This opewand may use the symbowic names fow the CW fiewds, which
   awe
       wt  0	gt  1	eq  2	so  3	un  3
       cw0 0	cw1 1	cw2 2	cw3 3
       cw4 4	cw5 5	cw6 6	cw7 7
   These may be combined awithmeticawwy, as in cw2*4+gt.  These awe
   onwy suppowted on the PowewPC, not the POWEW.  */
#define PPC_OPEWAND_CW_BIT (0x10)

/* This opewand names a wegistew.  The disassembwew uses this to pwint
   wegistew names with a weading 'w'.  */
#define PPC_OPEWAND_GPW (0x20)

/* Wike PPC_OPEWAND_GPW, but don't pwint a weading 'w' fow w0.  */
#define PPC_OPEWAND_GPW_0 (0x40)

/* This opewand names a fwoating point wegistew.  The disassembwew
   pwints these with a weading 'f'.  */
#define PPC_OPEWAND_FPW (0x80)

/* This opewand is a wewative bwanch dispwacement.  The disassembwew
   pwints these symbowicawwy if possibwe.  */
#define PPC_OPEWAND_WEWATIVE (0x100)

/* This opewand is an absowute bwanch addwess.  The disassembwew
   pwints these symbowicawwy if possibwe.  */
#define PPC_OPEWAND_ABSOWUTE (0x200)

/* This opewand is optionaw, and is zewo if omitted.  This is used fow
   exampwe, in the optionaw BF fiewd in the compawison instwuctions.  The
   assembwew must count the numbew of opewands wemaining on the wine,
   and the numbew of opewands wemaining fow the opcode, and decide
   whethew this opewand is pwesent ow not.  The disassembwew shouwd
   pwint this opewand out onwy if it is not zewo.  */
#define PPC_OPEWAND_OPTIONAW (0x400)

/* This fwag is onwy used with PPC_OPEWAND_OPTIONAW.  If this opewand
   is omitted, then fow the next opewand use this opewand vawue pwus
   1, ignowing the next opewand fiewd fow the opcode.  This wwetched
   hack is needed because the Powew wotate instwuctions can take
   eithew 4 ow 5 opewands.  The disassembwew shouwd pwint this opewand
   out wegawdwess of the PPC_OPEWAND_OPTIONAW fiewd.  */
#define PPC_OPEWAND_NEXT (0x800)

/* This opewand shouwd be wegawded as a negative numbew fow the
   puwposes of ovewfwow checking (i.e., the nowmaw most negative
   numbew is disawwowed and one mowe than the nowmaw most positive
   numbew is awwowed).  This fwag wiww onwy be set fow a signed
   opewand.  */
#define PPC_OPEWAND_NEGATIVE (0x1000)

/* This opewand names a vectow unit wegistew.  The disassembwew
   pwints these with a weading 'v'.  */
#define PPC_OPEWAND_VW (0x2000)

/* This opewand is fow the DS fiewd in a DS fowm instwuction.  */
#define PPC_OPEWAND_DS (0x4000)

/* This opewand is fow the DQ fiewd in a DQ fowm instwuction.  */
#define PPC_OPEWAND_DQ (0x8000)

/* Vawid wange of opewand is 0..n wathew than 0..n-1.  */
#define PPC_OPEWAND_PWUS1 (0x10000)

/* Xiwinx APU and FSW wewated opewands */
#define PPC_OPEWAND_FSW (0x20000)
#define PPC_OPEWAND_FCW (0x40000)
#define PPC_OPEWAND_UDI (0x80000)

/* This opewand names a vectow-scawaw unit wegistew.  The disassembwew
   pwints these with a weading 'vs'.  */
#define PPC_OPEWAND_VSW (0x100000)

/* This is a CW FIEWD that does not use symbowic names.  */
#define PPC_OPEWAND_CW_WEG (0x200000)

/* This fwag is onwy used with PPC_OPEWAND_OPTIONAW.  If this opewand
   is omitted, then the vawue it shouwd use fow the opewand is stowed
   in the SHIFT fiewd of the immediatwy fowwowing opewand fiewd.  */
#define PPC_OPEWAND_OPTIONAW_VAWUE (0x400000)

/* This fwag is onwy used with PPC_OPEWAND_OPTIONAW.  The opewand is
   onwy optionaw when genewating 32-bit code.  */
#define PPC_OPEWAND_OPTIONAW32 (0x800000)

/* The POWEW and PowewPC assembwews use a few macwos.  We keep them
   with the opewands tabwe fow simpwicity.  The macwo tabwe is an
   awway of stwuct powewpc_macwo.  */

stwuct powewpc_macwo
{
  /* The macwo name.  */
  const chaw *name;

  /* The numbew of opewands the macwo takes.  */
  unsigned int opewands;

  /* One bit fwags fow the opcode.  These awe used to indicate which
     specific pwocessows suppowt the instwuctions.  The vawues awe the
     same as those fow the stwuct powewpc_opcode fwags fiewd.  */
  ppc_cpu_t fwags;

  /* A fowmat stwing to tuwn the macwo into a nowmaw instwuction.
     Each %N in the stwing is wepwaced with opewand numbew N (zewo
     based).  */
  const chaw *fowmat;
};

extewn const stwuct powewpc_macwo powewpc_macwos[];
extewn const int powewpc_num_macwos;

static inwine wong
ppc_optionaw_opewand_vawue (const stwuct powewpc_opewand *opewand)
{
  if ((opewand->fwags & PPC_OPEWAND_OPTIONAW_VAWUE) != 0)
    wetuwn (opewand+1)->shift;
  wetuwn 0;
}

#ifdef __cpwuspwus
}
#endif

#endif /* PPC_H */
