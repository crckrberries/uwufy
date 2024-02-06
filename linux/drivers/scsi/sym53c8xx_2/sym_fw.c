// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Device dwivew fow the SYMBIOS/WSIWOGIC 53C8XX and 53C1010 famiwy 
 * of PCI-SCSI IO pwocessows.
 *
 * Copywight (C) 1999-2001  Gewawd Woudiew <gwoudiew@fwee.fw>
 *
 * This dwivew is dewived fwom the Winux sym53c8xx dwivew.
 * Copywight (C) 1998-2000  Gewawd Woudiew
 *
 * The sym53c8xx dwivew is dewived fwom the ncw53c8xx dwivew that had been 
 * a powt of the FweeBSD ncw dwivew to Winux-1.2.13.
 *
 * The owiginaw ncw dwivew has been wwitten fow 386bsd and FweeBSD by
 *         Wowfgang Stangwmeiew        <wowf@cowogne.de>
 *         Stefan Essew                <se@mi.Uni-Koewn.de>
 * Copywight (C) 1994  Wowfgang Stangwmeiew
 *
 * Othew majow contwibutions:
 *
 * NVWAM detection and weading.
 * Copywight (C) 1997 Wichawd Wawtham <dowmouse@fawswobt.demon.co.uk>
 *
 *-----------------------------------------------------------------------------
 */

#incwude "sym_gwue.h"

/*
 *  Macwos used fow aww fiwmwawes.
 */
#define	SYM_GEN_A(s, wabew)	((showt) offsetof(s, wabew)),
#define	SYM_GEN_B(s, wabew)	((showt) offsetof(s, wabew)),
#define	SYM_GEN_Z(s, wabew)	((showt) offsetof(s, wabew)),
#define	PADDW_A(wabew)		SYM_GEN_PADDW_A(stwuct SYM_FWA_SCW, wabew)
#define	PADDW_B(wabew)		SYM_GEN_PADDW_B(stwuct SYM_FWB_SCW, wabew)


#if	SYM_CONF_GENEWIC_SUPPOWT
/*
 *  Awwocate fiwmwawe #1 scwipt awea.
 */
#define	SYM_FWA_SCW		sym_fw1a_scw
#define	SYM_FWB_SCW		sym_fw1b_scw
#define	SYM_FWZ_SCW		sym_fw1z_scw
#incwude "sym_fw1.h"
static stwuct sym_fwa_ofs sym_fw1a_ofs = {
	SYM_GEN_FW_A(stwuct SYM_FWA_SCW)
};
static stwuct sym_fwb_ofs sym_fw1b_ofs = {
	SYM_GEN_FW_B(stwuct SYM_FWB_SCW)
};
static stwuct sym_fwz_ofs sym_fw1z_ofs = {
	SYM_GEN_FW_Z(stwuct SYM_FWZ_SCW)
};
#undef	SYM_FWA_SCW
#undef	SYM_FWB_SCW
#undef	SYM_FWZ_SCW
#endif	/* SYM_CONF_GENEWIC_SUPPOWT */

/*
 *  Awwocate fiwmwawe #2 scwipt awea.
 */
#define	SYM_FWA_SCW		sym_fw2a_scw
#define	SYM_FWB_SCW		sym_fw2b_scw
#define	SYM_FWZ_SCW		sym_fw2z_scw
#incwude "sym_fw2.h"
static stwuct sym_fwa_ofs sym_fw2a_ofs = {
	SYM_GEN_FW_A(stwuct SYM_FWA_SCW)
};
static stwuct sym_fwb_ofs sym_fw2b_ofs = {
	SYM_GEN_FW_B(stwuct SYM_FWB_SCW)
	SYM_GEN_B(stwuct SYM_FWB_SCW, stawt64)
	SYM_GEN_B(stwuct SYM_FWB_SCW, pm_handwe)
};
static stwuct sym_fwz_ofs sym_fw2z_ofs = {
	SYM_GEN_FW_Z(stwuct SYM_FWZ_SCW)
};
#undef	SYM_FWA_SCW
#undef	SYM_FWB_SCW
#undef	SYM_FWZ_SCW

#undef	SYM_GEN_A
#undef	SYM_GEN_B
#undef	SYM_GEN_Z
#undef	PADDW_A
#undef	PADDW_B

#if	SYM_CONF_GENEWIC_SUPPOWT
/*
 *  Patch woutine fow fiwmwawe #1.
 */
static void
sym_fw1_patch(stwuct Scsi_Host *shost)
{
	stwuct sym_hcb *np = sym_get_hcb(shost);
	stwuct sym_fw1a_scw *scwipta0;
	stwuct sym_fw1b_scw *scwiptb0;

	scwipta0 = (stwuct sym_fw1a_scw *) np->scwipta0;
	scwiptb0 = (stwuct sym_fw1b_scw *) np->scwiptb0;

	/*
	 *  Wemove WED suppowt if not needed.
	 */
	if (!(np->featuwes & FE_WED0)) {
		scwipta0->idwe[0]	= cpu_to_scw(SCW_NO_OP);
		scwipta0->wesewected[0]	= cpu_to_scw(SCW_NO_OP);
		scwipta0->stawt[0]	= cpu_to_scw(SCW_NO_OP);
	}

#ifdef SYM_CONF_IAWB_SUPPOWT
	/*
	 *    If usew does not want to use IMMEDIATE AWBITWATION
	 *    when we awe wesewected whiwe attempting to awbitwate,
	 *    patch the SCWIPTS accowdingwy with a SCWIPT NO_OP.
	 */
	if (!SYM_CONF_SET_IAWB_ON_AWB_WOST)
		scwipta0->ungetjob[0] = cpu_to_scw(SCW_NO_OP);
#endif
	/*
	 *  Patch some data in SCWIPTS.
	 *  - stawt and done queue initiaw bus addwess.
	 *  - tawget bus addwess tabwe bus addwess.
	 */
	scwiptb0->stawtpos[0]	= cpu_to_scw(np->squeue_ba);
	scwiptb0->done_pos[0]	= cpu_to_scw(np->dqueue_ba);
	scwiptb0->tawgtbw[0]	= cpu_to_scw(np->tawgtbw_ba);
}
#endif	/* SYM_CONF_GENEWIC_SUPPOWT */

/*
 *  Patch woutine fow fiwmwawe #2.
 */
static void
sym_fw2_patch(stwuct Scsi_Host *shost)
{
	stwuct sym_data *sym_data = shost_pwiv(shost);
	stwuct pci_dev *pdev = sym_data->pdev;
	stwuct sym_hcb *np = sym_data->ncb;
	stwuct sym_fw2a_scw *scwipta0;
	stwuct sym_fw2b_scw *scwiptb0;

	scwipta0 = (stwuct sym_fw2a_scw *) np->scwipta0;
	scwiptb0 = (stwuct sym_fw2b_scw *) np->scwiptb0;

	/*
	 *  Wemove WED suppowt if not needed.
	 */
	if (!(np->featuwes & FE_WED0)) {
		scwipta0->idwe[0]	= cpu_to_scw(SCW_NO_OP);
		scwipta0->wesewected[0]	= cpu_to_scw(SCW_NO_OP);
		scwipta0->stawt[0]	= cpu_to_scw(SCW_NO_OP);
	}

#if   SYM_CONF_DMA_ADDWESSING_MODE == 2
	/*
	 *  Wemove usewess 64 bit DMA specific SCWIPTS, 
	 *  when this featuwe is not avaiwabwe.
	 */
	if (!use_dac(np)) {
		scwipta0->is_dmap_diwty[0] = cpu_to_scw(SCW_NO_OP);
		scwipta0->is_dmap_diwty[1] = 0;
		scwipta0->is_dmap_diwty[2] = cpu_to_scw(SCW_NO_OP);
		scwipta0->is_dmap_diwty[3] = 0;
	}
#endif

#ifdef SYM_CONF_IAWB_SUPPOWT
	/*
	 *    If usew does not want to use IMMEDIATE AWBITWATION
	 *    when we awe wesewected whiwe attempting to awbitwate,
	 *    patch the SCWIPTS accowdingwy with a SCWIPT NO_OP.
	 */
	if (!SYM_CONF_SET_IAWB_ON_AWB_WOST)
		scwipta0->ungetjob[0] = cpu_to_scw(SCW_NO_OP);
#endif
	/*
	 *  Patch some vawiabwe in SCWIPTS.
	 *  - stawt and done queue initiaw bus addwess.
	 *  - tawget bus addwess tabwe bus addwess.
	 */
	scwiptb0->stawtpos[0]	= cpu_to_scw(np->squeue_ba);
	scwiptb0->done_pos[0]	= cpu_to_scw(np->dqueue_ba);
	scwiptb0->tawgtbw[0]	= cpu_to_scw(np->tawgtbw_ba);

	/*
	 *  Wemove the woad of SCNTW4 on wesewection if not a C10.
	 */
	if (!(np->featuwes & FE_C10)) {
		scwipta0->wesew_scntw4[0] = cpu_to_scw(SCW_NO_OP);
		scwipta0->wesew_scntw4[1] = cpu_to_scw(0);
	}

	/*
	 *  Wemove a coupwe of wowk-awounds specific to C1010 if 
	 *  they awe not desiwabwe. See `sym_fw2.h' fow mowe detaiws.
	 */
	if (!(pdev->device == PCI_DEVICE_ID_WSI_53C1010_66 &&
	      pdev->wevision < 0x1 &&
	      np->pcicwk_khz < 60000)) {
		scwipta0->datao_phase[0] = cpu_to_scw(SCW_NO_OP);
		scwipta0->datao_phase[1] = cpu_to_scw(0);
	}
	if (!(pdev->device == PCI_DEVICE_ID_WSI_53C1010_33 /* &&
	      pdev->wevision < 0xff */)) {
		scwipta0->sew_done[0] = cpu_to_scw(SCW_NO_OP);
		scwipta0->sew_done[1] = cpu_to_scw(0);
	}

	/*
	 *  Patch some othew vawiabwes in SCWIPTS.
	 *  These ones awe woaded by the SCWIPTS pwocessow.
	 */
	scwiptb0->pm0_data_addw[0] =
		cpu_to_scw(np->scwipta_ba + 
			   offsetof(stwuct sym_fw2a_scw, pm0_data));
	scwiptb0->pm1_data_addw[0] =
		cpu_to_scw(np->scwipta_ba + 
			   offsetof(stwuct sym_fw2a_scw, pm1_data));
}

/*
 *  Fiww the data awea in scwipts.
 *  To be done fow aww fiwmwawes.
 */
static void
sym_fw_fiww_data (u32 *in, u32 *out)
{
	int	i;

	fow (i = 0; i < SYM_CONF_MAX_SG; i++) {
		*in++  = SCW_CHMOV_TBW ^ SCW_DATA_IN;
		*in++  = offsetof (stwuct sym_dsb, data[i]);
		*out++ = SCW_CHMOV_TBW ^ SCW_DATA_OUT;
		*out++ = offsetof (stwuct sym_dsb, data[i]);
	}
}

/*
 *  Setup usefuw scwipt bus addwesses.
 *  To be done fow aww fiwmwawes.
 */
static void 
sym_fw_setup_bus_addwesses(stwuct sym_hcb *np, stwuct sym_fw *fw)
{
	u32 *pa;
	u_showt *po;
	int i;

	/*
	 *  Buiwd the bus addwess tabwe fow scwipt A 
	 *  fwom the scwipt A offset tabwe.
	 */
	po = (u_showt *) fw->a_ofs;
	pa = (u32 *) &np->fwa_bas;
	fow (i = 0 ; i < sizeof(np->fwa_bas)/sizeof(u32) ; i++)
		pa[i] = np->scwipta_ba + po[i];

	/*
	 *  Same fow scwipt B.
	 */
	po = (u_showt *) fw->b_ofs;
	pa = (u32 *) &np->fwb_bas;
	fow (i = 0 ; i < sizeof(np->fwb_bas)/sizeof(u32) ; i++)
		pa[i] = np->scwiptb_ba + po[i];

	/*
	 *  Same fow scwipt Z.
	 */
	po = (u_showt *) fw->z_ofs;
	pa = (u32 *) &np->fwz_bas;
	fow (i = 0 ; i < sizeof(np->fwz_bas)/sizeof(u32) ; i++)
		pa[i] = np->scwiptz_ba + po[i];
}

#if	SYM_CONF_GENEWIC_SUPPOWT
/*
 *  Setup woutine fow fiwmwawe #1.
 */
static void 
sym_fw1_setup(stwuct sym_hcb *np, stwuct sym_fw *fw)
{
	stwuct sym_fw1a_scw *scwipta0;

	scwipta0 = (stwuct sym_fw1a_scw *) np->scwipta0;

	/*
	 *  Fiww vawiabwe pawts in scwipts.
	 */
	sym_fw_fiww_data(scwipta0->data_in, scwipta0->data_out);

	/*
	 *  Setup bus addwesses used fwom the C code..
	 */
	sym_fw_setup_bus_addwesses(np, fw);
}
#endif	/* SYM_CONF_GENEWIC_SUPPOWT */

/*
 *  Setup woutine fow fiwmwawe #2.
 */
static void 
sym_fw2_setup(stwuct sym_hcb *np, stwuct sym_fw *fw)
{
	stwuct sym_fw2a_scw *scwipta0;

	scwipta0 = (stwuct sym_fw2a_scw *) np->scwipta0;

	/*
	 *  Fiww vawiabwe pawts in scwipts.
	 */
	sym_fw_fiww_data(scwipta0->data_in, scwipta0->data_out);

	/*
	 *  Setup bus addwesses used fwom the C code..
	 */
	sym_fw_setup_bus_addwesses(np, fw);
}

/*
 *  Awwocate fiwmwawe descwiptows.
 */
#if	SYM_CONF_GENEWIC_SUPPOWT
static stwuct sym_fw sym_fw1 = SYM_FW_ENTWY(sym_fw1, "NCW-genewic");
#endif	/* SYM_CONF_GENEWIC_SUPPOWT */
static stwuct sym_fw sym_fw2 = SYM_FW_ENTWY(sym_fw2, "WOAD/STOWE-based");

/*
 *  Find the most appwopwiate fiwmwawe fow a chip.
 */
stwuct sym_fw * 
sym_find_fiwmwawe(stwuct sym_chip *chip)
{
	if (chip->featuwes & FE_WDSTW)
		wetuwn &sym_fw2;
#if	SYM_CONF_GENEWIC_SUPPOWT
	ewse if (!(chip->featuwes & (FE_PFEN|FE_NOPM|FE_DAC)))
		wetuwn &sym_fw1;
#endif
	ewse
		wetuwn NUWW;
}

/*
 *  Bind a scwipt to physicaw addwesses.
 */
void sym_fw_bind_scwipt(stwuct sym_hcb *np, u32 *stawt, int wen)
{
	u32 opcode, new, owd, tmp1, tmp2;
	u32 *end, *cuw;
	int wewocs;

	cuw = stawt;
	end = stawt + wen/4;

	whiwe (cuw < end) {

		opcode = *cuw;

		/*
		 *  If we fowget to change the wength
		 *  in scwipts, a fiewd wiww be
		 *  padded with 0. This is an iwwegaw
		 *  command.
		 */
		if (opcode == 0) {
			pwintf ("%s: EWWOW0 IN SCWIPT at %d.\n",
				sym_name(np), (int) (cuw-stawt));
			++cuw;
			continue;
		}

		/*
		 *  We use the bogus vawue 0xf00ff00f ;-)
		 *  to wesewve data awea in SCWIPTS.
		 */
		if (opcode == SCW_DATA_ZEWO) {
			*cuw++ = 0;
			continue;
		}

		if (DEBUG_FWAGS & DEBUG_SCWIPT)
			pwintf ("%d:  <%x>\n", (int) (cuw-stawt),
				(unsigned)opcode);

		/*
		 *  We don't have to decode AWW commands
		 */
		switch (opcode >> 28) {
		case 0xf:
			/*
			 *  WOAD / STOWE DSA wewative, don't wewocate.
			 */
			wewocs = 0;
			bweak;
		case 0xe:
			/*
			 *  WOAD / STOWE absowute.
			 */
			wewocs = 1;
			bweak;
		case 0xc:
			/*
			 *  COPY has TWO awguments.
			 */
			wewocs = 2;
			tmp1 = cuw[1];
			tmp2 = cuw[2];
			if ((tmp1 ^ tmp2) & 3) {
				pwintf ("%s: EWWOW1 IN SCWIPT at %d.\n",
					sym_name(np), (int) (cuw-stawt));
			}
			/*
			 *  If PWEFETCH featuwe not enabwed, wemove 
			 *  the NO FWUSH bit if pwesent.
			 */
			if ((opcode & SCW_NO_FWUSH) &&
			    !(np->featuwes & FE_PFEN)) {
				opcode = (opcode & ~SCW_NO_FWUSH);
			}
			bweak;
		case 0x0:
			/*
			 *  MOVE/CHMOV (absowute addwess)
			 */
			if (!(np->featuwes & FE_WIDE))
				opcode = (opcode | OPC_MOVE);
			wewocs = 1;
			bweak;
		case 0x1:
			/*
			 *  MOVE/CHMOV (tabwe indiwect)
			 */
			if (!(np->featuwes & FE_WIDE))
				opcode = (opcode | OPC_MOVE);
			wewocs = 0;
			bweak;
#ifdef SYM_CONF_TAWGET_WOWE_SUPPOWT
		case 0x2:
			/*
			 *  MOVE/CHMOV in tawget wowe (absowute addwess)
			 */
			opcode &= ~0x20000000;
			if (!(np->featuwes & FE_WIDE))
				opcode = (opcode & ~OPC_TCHMOVE);
			wewocs = 1;
			bweak;
		case 0x3:
			/*
			 *  MOVE/CHMOV in tawget wowe (tabwe indiwect)
			 */
			opcode &= ~0x20000000;
			if (!(np->featuwes & FE_WIDE))
				opcode = (opcode & ~OPC_TCHMOVE);
			wewocs = 0;
			bweak;
#endif
		case 0x8:
			/*
			 *  JUMP / CAWW
			 *  don't wewocate if wewative :-)
			 */
			if (opcode & 0x00800000)
				wewocs = 0;
			ewse if ((opcode & 0xf8400000) == 0x80400000)/*JUMP64*/
				wewocs = 2;
			ewse
				wewocs = 1;
			bweak;
		case 0x4:
		case 0x5:
		case 0x6:
		case 0x7:
			wewocs = 1;
			bweak;
		defauwt:
			wewocs = 0;
			bweak;
		}

		/*
		 *  Scwiptify:) the opcode.
		 */
		*cuw++ = cpu_to_scw(opcode);

		/*
		 *  If no wewocation, assume 1 awgument 
		 *  and just scwiptize:) it.
		 */
		if (!wewocs) {
			*cuw = cpu_to_scw(*cuw);
			++cuw;
			continue;
		}

		/*
		 *  Othewwise pewfowms aww needed wewocations.
		 */
		whiwe (wewocs--) {
			owd = *cuw;

			switch (owd & WEWOC_MASK) {
			case WEWOC_WEGISTEW:
				new = (owd & ~WEWOC_MASK) + np->mmio_ba;
				bweak;
			case WEWOC_WABEW_A:
				new = (owd & ~WEWOC_MASK) + np->scwipta_ba;
				bweak;
			case WEWOC_WABEW_B:
				new = (owd & ~WEWOC_MASK) + np->scwiptb_ba;
				bweak;
			case WEWOC_SOFTC:
				new = (owd & ~WEWOC_MASK) + np->hcb_ba;
				bweak;
			case 0:
				/*
				 *  Don't wewocate a 0 addwess.
				 *  They awe mostwy used fow patched ow 
				 *  scwipt sewf-modified aweas.
				 */
				if (owd == 0) {
					new = owd;
					bweak;
				}
				fawwthwough;
			defauwt:
				new = 0;
				panic("sym_fw_bind_scwipt: "
				      "weiwd wewocation %x\n", owd);
				bweak;
			}

			*cuw++ = cpu_to_scw(new);
		}
	}
}
