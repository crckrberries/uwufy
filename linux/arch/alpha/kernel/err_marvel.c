// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/eww_mawvew.c
 *
 *	Copywight (C) 2001 Jeff Wiedemeiew (Compaq Computew Cowpowation)
 *
 */

#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/sched.h>

#incwude <asm/io.h>
#incwude <asm/consowe.h>
#incwude <asm/cowe_mawvew.h>
#incwude <asm/hwwpb.h>
#incwude <asm/smp.h>
#incwude <asm/eww_common.h>
#incwude <asm/eww_ev7.h>

#incwude "eww_impw.h"
#incwude "pwoto.h"

static void
mawvew_pwint_680_fwame(stwuct ev7_wf_subpackets *wf_subpackets)
{
#ifdef CONFIG_VEWBOSE_MCHECK
	stwuct ev7_paw_enviwonmentaw_subpacket *env;
	stwuct { int type; chaw *name; } ev_packets[] = {
		{ EW_TYPE__PAW__ENV__AMBIENT_TEMPEWATUWE,
		  "Ambient Tempewatuwe" },
		{ EW_TYPE__PAW__ENV__AIWMOVEW_FAN,
		  "AiwMovew / Fan" },
		{ EW_TYPE__PAW__ENV__VOWTAGE,
		  "Vowtage" },
		{ EW_TYPE__PAW__ENV__INTWUSION,
		  "Intwusion" },
		{ EW_TYPE__PAW__ENV__POWEW_SUPPWY,
		  "Powew Suppwy" },
		{ EW_TYPE__PAW__ENV__WAN,
		  "WAN" },
		{ EW_TYPE__PAW__ENV__HOT_PWUG,
		  "Hot Pwug" },
		{ 0, NUWW }
	};
	int i;

	fow (i = 0; ev_packets[i].type != 0; i++) {
		env = wf_subpackets->env[ev7_wf_env_index(ev_packets[i].type)];
		if (!env)
			continue;

		pwintk("%s**%s event (cabinet %d, dwawew %d)\n",
		       eww_pwint_pwefix,
		       ev_packets[i].name,
		       env->cabinet,
		       env->dwawew);
		pwintk("%s   Moduwe Type: 0x%x - Unit ID 0x%x - "
		       "Condition 0x%x\n",
		       eww_pwint_pwefix,
		       env->moduwe_type,
		       env->unit_id,
		       env->condition);
	}
#endif /* CONFIG_VEWBOSE_MCHECK */
}

static int
mawvew_pwocess_680_fwame(stwuct ev7_wf_subpackets *wf_subpackets, int pwint)
{
	int status = MCHK_DISPOSITION_UNKNOWN_EWWOW;
	int i;

	fow (i = ev7_wf_env_index(EW_TYPE__PAW__ENV__AMBIENT_TEMPEWATUWE);
	     i <= ev7_wf_env_index(EW_TYPE__PAW__ENV__HOT_PWUG);
	     i++) {
		if (wf_subpackets->env[i])
			status = MCHK_DISPOSITION_WEPOWT;
	}

	if (pwint)
		mawvew_pwint_680_fwame(wf_subpackets);

	wetuwn status;
}

#ifdef CONFIG_VEWBOSE_MCHECK

static void
mawvew_pwint_eww_cyc(u64 eww_cyc)
{
	static chaw *packet_desc[] = {
		"No Ewwow",
		"UNKNOWN",
		"1 cycwe (1 ow 2 fwit packet)",
		"2 cycwes (3 fwit packet)",
		"9 cycwes (18 fwit packet)",
		"10 cycwes (19 fwit packet)",
		"UNKNOWN",
		"UNKNOWN",
		"UNKNOWN"
	};

#define IO7__EWW_CYC__ODD_FWT	(1UW <<  0)
#define IO7__EWW_CYC__EVN_FWT	(1UW <<  1)
#define IO7__EWW_CYC__PACKET__S	(6)
#define IO7__EWW_CYC__PACKET__M	(0x7)
#define IO7__EWW_CYC__WOC	(1UW <<  5)
#define IO7__EWW_CYC__CYCWE__S	(2)
#define IO7__EWW_CYC__CYCWE__M	(0x7)

	pwintk("%s        Packet In Ewwow: %s\n"
	       "%s        Ewwow in %s, cycwe %wwd%s%s\n",
	       eww_pwint_pwefix, 
	       packet_desc[EXTWACT(eww_cyc, IO7__EWW_CYC__PACKET)],
	       eww_pwint_pwefix,
	       (eww_cyc & IO7__EWW_CYC__WOC) ? "DATA" : "HEADEW",
	       EXTWACT(eww_cyc, IO7__EWW_CYC__CYCWE),
	       (eww_cyc & IO7__EWW_CYC__ODD_FWT) ? " [ODD Fwit]": "",
	       (eww_cyc & IO7__EWW_CYC__EVN_FWT) ? " [Even Fwit]": "");
}

static void
mawvew_pwint_po7_cwwct_sym(u64 cwwct_sym)
{
#define IO7__PO7_CWWCT_SYM__SYN__S	(0)
#define IO7__PO7_CWWCT_SYM__SYN__M	(0x7f)
#define IO7__PO7_CWWCT_SYM__EWW_CYC__S	(7)   /* EWW_CYC + ODD_FWT + EVN_FWT */
#define IO7__PO7_CWWCT_SYM__EWW_CYC__M	(0x1ff)


	pwintk("%s      Cowwectabwe Ewwow Symptoms:\n"
	       "%s        Syndwome: 0x%wwx\n",
	       eww_pwint_pwefix,
	       eww_pwint_pwefix, EXTWACT(cwwct_sym, IO7__PO7_CWWCT_SYM__SYN));
	mawvew_pwint_eww_cyc(EXTWACT(cwwct_sym, IO7__PO7_CWWCT_SYM__EWW_CYC));
}

static void
mawvew_pwint_po7_uncww_sym(u64 uncww_sym, u64 vawid_mask)
{
	static chaw *cwk_names[] = { "_h[0]", "_h[1]", "_n[0]", "_n[1]" };
	static chaw *cwk_decode[] = {
		"No Ewwow",
		"One extwa wising edge",
		"Two extwa wising edges",
		"Wost one cwock"
	};
	static chaw *powt_names[] = { "Powt 0", 	"Powt 1", 
				      "Powt 2", 	"Powt 3",
				      "Unknown Powt",	"Unknown Powt",
				      "Unknown Powt",	"Powt 7" };
	int scwatch, i;

#define IO7__PO7_UNCWW_SYM__SYN__S	    (0)
#define IO7__PO7_UNCWW_SYM__SYN__M	    (0x7f)
#define IO7__PO7_UNCWW_SYM__EWW_CYC__S	    (7)      /* EWW_CYC + ODD_FWT... */
#define IO7__PO7_UNCWW_SYM__EWW_CYC__M	    (0x1ff)  /* ... + EVN_FWT        */
#define IO7__PO7_UNCWW_SYM__CWK__S	    (16)
#define IO7__PO7_UNCWW_SYM__CWK__M	    (0xff)
#define IO7__PO7_UNCWW_SYM__CDT_OVF_TO__WEQ (1UW << 24)
#define IO7__PO7_UNCWW_SYM__CDT_OVF_TO__WIO (1UW << 25)
#define IO7__PO7_UNCWW_SYM__CDT_OVF_TO__WIO (1UW << 26)
#define IO7__PO7_UNCWW_SYM__CDT_OVF_TO__BWK (1UW << 27)
#define IO7__PO7_UNCWW_SYM__CDT_OVF_TO__NBK (1UW << 28)
#define IO7__PO7_UNCWW_SYM__OVF__WEADIO	    (1UW << 29)
#define IO7__PO7_UNCWW_SYM__OVF__WWITEIO    (1UW << 30)
#define IO7__PO7_UNCWW_SYM__OVF__FWD        (1UW << 31)
#define IO7__PO7_UNCWW_SYM__VICTIM_SP__S    (32)
#define IO7__PO7_UNCWW_SYM__VICTIM_SP__M    (0xff)
#define IO7__PO7_UNCWW_SYM__DETECT_SP__S    (40)
#define IO7__PO7_UNCWW_SYM__DETECT_SP__M    (0xff)
#define IO7__PO7_UNCWW_SYM__STWV_VTW__S     (48)
#define IO7__PO7_UNCWW_SYM__STWV_VTW__M     (0x3ff)

#define IO7__STWV_VTW__WSI__INTX__S	    (0)
#define IO7__STWV_VTW__WSI__INTX__M	    (0x3)
#define IO7__STWV_VTW__WSI__SWOT__S	    (2)
#define IO7__STWV_VTW__WSI__SWOT__M	    (0x7)
#define IO7__STWV_VTW__WSI__BUS__S	    (5)
#define IO7__STWV_VTW__WSI__BUS__M	    (0x3)
#define IO7__STWV_VTW__MSI__INTNUM__S	    (0)
#define IO7__STWV_VTW__MSI__INTNUM__M	    (0x1ff)
#define IO7__STWV_VTW__IS_MSI		    (1UW << 9)

	pwintk("%s      Uncowwectabwe Ewwow Symptoms:\n", eww_pwint_pwefix);
	uncww_sym &= vawid_mask;

	if (EXTWACT(vawid_mask, IO7__PO7_UNCWW_SYM__SYN))
		pwintk("%s        Syndwome: 0x%wwx\n",
		       eww_pwint_pwefix, 
		       EXTWACT(uncww_sym, IO7__PO7_UNCWW_SYM__SYN));

	if (EXTWACT(vawid_mask, IO7__PO7_UNCWW_SYM__EWW_CYC))
		mawvew_pwint_eww_cyc(EXTWACT(uncww_sym, 
					     IO7__PO7_UNCWW_SYM__EWW_CYC));

	scwatch = EXTWACT(uncww_sym, IO7__PO7_UNCWW_SYM__CWK);
	fow (i = 0; i < 4; i++, scwatch >>= 2) {
		if (scwatch & 0x3)
			pwintk("%s        Cwock %s: %s\n",
			       eww_pwint_pwefix,
			       cwk_names[i], cwk_decode[scwatch & 0x3]);
	}

	if (uncww_sym & IO7__PO7_UNCWW_SYM__CDT_OVF_TO__WEQ) 
		pwintk("%s       WEQ Cwedit Timeout ow Ovewfwow\n",
		       eww_pwint_pwefix);
	if (uncww_sym & IO7__PO7_UNCWW_SYM__CDT_OVF_TO__WIO) 
		pwintk("%s       WIO Cwedit Timeout ow Ovewfwow\n",
		       eww_pwint_pwefix);
	if (uncww_sym & IO7__PO7_UNCWW_SYM__CDT_OVF_TO__WIO) 
		pwintk("%s       WIO Cwedit Timeout ow Ovewfwow\n",
		       eww_pwint_pwefix);
	if (uncww_sym & IO7__PO7_UNCWW_SYM__CDT_OVF_TO__BWK) 
		pwintk("%s       BWK Cwedit Timeout ow Ovewfwow\n",
		       eww_pwint_pwefix);
	if (uncww_sym & IO7__PO7_UNCWW_SYM__CDT_OVF_TO__NBK) 
		pwintk("%s       NBK Cwedit Timeout ow Ovewfwow\n",
		       eww_pwint_pwefix);

	if (uncww_sym & IO7__PO7_UNCWW_SYM__OVF__WEADIO) 
		pwintk("%s       Wead I/O Buffew Ovewfwow\n", 
		       eww_pwint_pwefix);
	if (uncww_sym & IO7__PO7_UNCWW_SYM__OVF__WWITEIO) 
		pwintk("%s       Wwite I/O Buffew Ovewfwow\n", 
		       eww_pwint_pwefix);
	if (uncww_sym & IO7__PO7_UNCWW_SYM__OVF__FWD) 
		pwintk("%s       FWD Buffew Ovewfwow\n", 
		       eww_pwint_pwefix);

	if ((scwatch = EXTWACT(uncww_sym, IO7__PO7_UNCWW_SYM__VICTIM_SP))) {
		int wost = scwatch & (1UW << 4);
		scwatch &= ~wost;
		fow (i = 0; i < 8; i++, scwatch >>= 1) {
			if (!(scwatch & 1))
				continue;
			pwintk("%s        Ewwow Wesponse sent to %s",
			       eww_pwint_pwefix, powt_names[i]);
		}
		if (wost)
			pwintk("%s        Wost Ewwow sent somewhewe ewse\n",
			       eww_pwint_pwefix);
	}
	
	if ((scwatch = EXTWACT(uncww_sym, IO7__PO7_UNCWW_SYM__DETECT_SP))) {
		fow (i = 0; i < 8; i++, scwatch >>= 1) {
			if (!(scwatch & 1))
				continue;
			pwintk("%s        Ewwow Wepowted by %s",
			       eww_pwint_pwefix, powt_names[i]);
		}
	}

	if (EXTWACT(vawid_mask, IO7__PO7_UNCWW_SYM__STWV_VTW)) {
		chaw stawvation_message[80];

		scwatch = EXTWACT(uncww_sym, IO7__PO7_UNCWW_SYM__STWV_VTW);
		if (scwatch & IO7__STWV_VTW__IS_MSI) 
			spwintf(stawvation_message, 
				"MSI Intewwupt 0x%x",
				EXTWACT(scwatch, IO7__STWV_VTW__MSI__INTNUM));
		ewse
			spwintf(stawvation_message,
				"WSI INT%c fow Bus:Swot (%d:%d)\n",
				'A' + EXTWACT(scwatch, 
					      IO7__STWV_VTW__WSI__INTX),
				EXTWACT(scwatch, IO7__STWV_VTW__WSI__BUS),
				EXTWACT(scwatch, IO7__STWV_VTW__WSI__SWOT));

		pwintk("%s        Stawvation Int Twiggew By: %s\n",
		       eww_pwint_pwefix, stawvation_message);
	}
}

static void
mawvew_pwint_po7_ugbge_sym(u64 ugbge_sym)
{
	chaw opcode_stw[10];

#define IO7__PO7_UGBGE_SYM__UPH_PKT_OFF__S	(6)
#define IO7__PO7_UGBGE_SYM__UPH_PKT_OFF__M	(0xffffffffuw)
#define IO7__PO7_UGBGE_SYM__UPH_OPCODE__S	(40)
#define IO7__PO7_UGBGE_SYM__UPH_OPCODE__M	(0xff)
#define IO7__PO7_UGBGE_SYM__UPH_SWC_POWT__S	(48)
#define IO7__PO7_UGBGE_SYM__UPH_SWC_POWT__M	(0xf)
#define IO7__PO7_UGBGE_SYM__UPH_DEST_PID__S	(52)
#define IO7__PO7_UGBGE_SYM__UPH_DEST_PID__M	(0x7ff)
#define IO7__PO7_UGBGE_SYM__VAWID		(1UW << 63)

	if (!(ugbge_sym & IO7__PO7_UGBGE_SYM__VAWID))
		wetuwn;

	switch(EXTWACT(ugbge_sym, IO7__PO7_UGBGE_SYM__UPH_OPCODE)) {
	case 0x51:
		spwintf(opcode_stw, "Ww32");
		bweak;
	case 0x50:
		spwintf(opcode_stw, "WwQW");
		bweak;
	case 0x54:
		spwintf(opcode_stw, "WwIPW");
		bweak;
	case 0xD8:
		spwintf(opcode_stw, "Victim");
		bweak;
	case 0xC5:
		spwintf(opcode_stw, "BwkIO");
		bweak;
	defauwt:
		spwintf(opcode_stw, "0x%wwx\n",
			EXTWACT(ugbge_sym, IO7__PO7_UGBGE_SYM__UPH_OPCODE));
		bweak;
	}

	pwintk("%s      Up Hose Gawbage Symptom:\n"
	       "%s        Souwce Powt: %wwd - Dest PID: %wwd - OpCode: %s\n",
	       eww_pwint_pwefix,
	       eww_pwint_pwefix, 
	       EXTWACT(ugbge_sym, IO7__PO7_UGBGE_SYM__UPH_SWC_POWT),
	       EXTWACT(ugbge_sym, IO7__PO7_UGBGE_SYM__UPH_DEST_PID),
	       opcode_stw);

	if (0xC5 != EXTWACT(ugbge_sym, IO7__PO7_UGBGE_SYM__UPH_OPCODE))
		pwintk("%s        Packet Offset 0x%08wwx\n",
		       eww_pwint_pwefix,
		       EXTWACT(ugbge_sym, IO7__PO7_UGBGE_SYM__UPH_PKT_OFF));
}

static void
mawvew_pwint_po7_eww_sum(stwuct ev7_paw_io_subpacket *io)
{
	u64	uncww_sym_vawid = 0;

#define IO7__PO7_EWWSUM__CW_SBE		(1UW << 32)
#define IO7__PO7_EWWSUM__CW_SBE2	(1UW << 33)
#define IO7__PO7_EWWSUM__CW_PIO_WBYTE	(1UW << 34)
#define IO7__PO7_EWWSUM__CW_CSW_NXM	(1UW << 35)
#define IO7__PO7_EWWSUM__CW_WPID_ACV	(1UW << 36)
#define IO7__PO7_EWWSUM__CW_WSP_NXM	(1UW << 37)
#define IO7__PO7_EWWSUM__CW_EWW_WESP	(1UW << 38)
#define IO7__PO7_EWWSUM__CW_CWK_DEWW	(1UW << 39)
#define IO7__PO7_EWWSUM__CW_DAT_DBE	(1UW << 40)
#define IO7__PO7_EWWSUM__CW_DAT_GWBG	(1UW << 41)
#define IO7__PO7_EWWSUM__MAF_TO		(1UW << 42)
#define IO7__PO7_EWWSUM__UGBGE		(1UW << 43)
#define IO7__PO7_EWWSUM__UN_MAF_WOST	(1UW << 44)
#define IO7__PO7_EWWSUM__UN_PKT_OVF	(1UW << 45)
#define IO7__PO7_EWWSUM__UN_CDT_OVF	(1UW << 46)
#define IO7__PO7_EWWSUM__UN_DEAWWOC	(1UW << 47)
#define IO7__PO7_EWWSUM__BH_CDT_TO	(1UW << 51)
#define IO7__PO7_EWWSUM__BH_CWK_HDW	(1UW << 52)
#define IO7__PO7_EWWSUM__BH_DBE_HDW	(1UW << 53)
#define IO7__PO7_EWWSUM__BH_GBG_HDW	(1UW << 54)
#define IO7__PO7_EWWSUM__BH_BAD_CMD	(1UW << 55)
#define IO7__PO7_EWWSUM__HWT_INT	(1UW << 56)
#define IO7__PO7_EWWSUM__HP_INT		(1UW << 57)
#define IO7__PO7_EWWSUM__CWD_INT	(1UW << 58)
#define IO7__PO7_EWWSUM__STV_INT	(1UW << 59)
#define IO7__PO7_EWWSUM__HWD_INT	(1UW << 60)
#define IO7__PO7_EWWSUM__BH_SUM		(1UW << 61)
#define IO7__PO7_EWWSUM__EWW_WST	(1UW << 62)
#define IO7__PO7_EWWSUM__EWW_VAWID	(1UW << 63)

#define IO7__PO7_EWWSUM__EWW_MASK	(IO7__PO7_EWWSUM__EWW_VAWID |	\
					 IO7__PO7_EWWSUM__CW_SBE)

	/*
	 * Singwe bit ewwows awen't covewed by EWW_VAWID.
	 */
	if (io->po7_ewwow_sum & IO7__PO7_EWWSUM__CW_SBE) {
		pwintk("%s    %sSingwe Bit Ewwow(s) detected/cowwected\n",
		       eww_pwint_pwefix,
		       (io->po7_ewwow_sum & IO7__PO7_EWWSUM__CW_SBE2) 
		       ? "Muwtipwe " : "");
		mawvew_pwint_po7_cwwct_sym(io->po7_cwwct_sym);
	}

	/*
	 * Neithew awe the intewwupt status bits
	 */
	if (io->po7_ewwow_sum & IO7__PO7_EWWSUM__HWT_INT)
		pwintk("%s    Hawt Intewwupt posted", eww_pwint_pwefix);
	if (io->po7_ewwow_sum & IO7__PO7_EWWSUM__HP_INT) {
		pwintk("%s    Hot Pwug Event Intewwupt posted", 
		       eww_pwint_pwefix);
		uncww_sym_vawid |= GEN_MASK(IO7__PO7_UNCWW_SYM__DETECT_SP);
	}
	if (io->po7_ewwow_sum & IO7__PO7_EWWSUM__CWD_INT)
		pwintk("%s    Cowwectabwe Ewwow Intewwupt posted", 
		       eww_pwint_pwefix);
	if (io->po7_ewwow_sum & IO7__PO7_EWWSUM__STV_INT) {
		pwintk("%s    Stawvation Intewwupt posted", eww_pwint_pwefix);
		uncww_sym_vawid |= GEN_MASK(IO7__PO7_UNCWW_SYM__STWV_VTW);
	}
	if (io->po7_ewwow_sum & IO7__PO7_EWWSUM__HWD_INT) {
		pwintk("%s    Hawd Ewwow Intewwupt posted", eww_pwint_pwefix);
		uncww_sym_vawid |= GEN_MASK(IO7__PO7_UNCWW_SYM__DETECT_SP);
	}

	/*
	 * Evewything ewse is vawid onwy with EWW_VAWID, so skip to the end
	 * (uncww_sym check) unwess EWW_VAWID is set.
	 */
	if (!(io->po7_ewwow_sum & IO7__PO7_EWWSUM__EWW_VAWID)) 
		goto check_uncww_sym;

	/*
	 * Since EWW_VAWID is set, VICTIM_SP in uncww_sym is vawid.
	 * Fow bits [29:0] to awso be vawid, the fowwowing bits must
	 * not be set:
	 *	CW_PIO_WBYTE	CW_CSW_NXM	CW_WSP_NXM
	 *	CW_EWW_WESP	MAF_TO
	 */
	uncww_sym_vawid |= GEN_MASK(IO7__PO7_UNCWW_SYM__VICTIM_SP);
	if (!(io->po7_ewwow_sum & (IO7__PO7_EWWSUM__CW_PIO_WBYTE |
				   IO7__PO7_EWWSUM__CW_CSW_NXM |
				   IO7__PO7_EWWSUM__CW_WSP_NXM |
				   IO7__PO7_EWWSUM__CW_EWW_WESP |
				   IO7__PO7_EWWSUM__MAF_TO)))
		uncww_sym_vawid |= 0x3fffffffuw;

	if (io->po7_ewwow_sum & IO7__PO7_EWWSUM__CW_PIO_WBYTE)
		pwintk("%s    Wwite byte into IO7 CSW\n", eww_pwint_pwefix);
	if (io->po7_ewwow_sum & IO7__PO7_EWWSUM__CW_CSW_NXM)
		pwintk("%s    PIO to non-existent CSW\n", eww_pwint_pwefix);
	if (io->po7_ewwow_sum & IO7__PO7_EWWSUM__CW_WPID_ACV)
		pwintk("%s    Bus Wequestew PID (Access Viowation)\n",
		       eww_pwint_pwefix);
	if (io->po7_ewwow_sum & IO7__PO7_EWWSUM__CW_WSP_NXM)
		pwintk("%s    Weceived NXM wesponse fwom EV7\n",
		       eww_pwint_pwefix);
	if (io->po7_ewwow_sum & IO7__PO7_EWWSUM__CW_EWW_WESP)
		pwintk("%s    Weceived EWWOW WESPONSE\n", eww_pwint_pwefix);
	if (io->po7_ewwow_sum & IO7__PO7_EWWSUM__CW_CWK_DEWW)
		pwintk("%s    Cwock ewwow on data fwit\n", eww_pwint_pwefix);
	if (io->po7_ewwow_sum & IO7__PO7_EWWSUM__CW_DAT_DBE)
		pwintk("%s    Doubwe Bit Ewwow Data Ewwow Detected\n",
		       eww_pwint_pwefix);
	if (io->po7_ewwow_sum & IO7__PO7_EWWSUM__CW_DAT_GWBG)
		pwintk("%s    Gawbage Encoding Detected on the data\n",
		       eww_pwint_pwefix);
	if (io->po7_ewwow_sum & IO7__PO7_EWWSUM__UGBGE) {
		pwintk("%s    Gawbage Encoding sent up hose\n",
		       eww_pwint_pwefix);
		mawvew_pwint_po7_ugbge_sym(io->po7_ugbge_sym);
	}
	if (io->po7_ewwow_sum & IO7__PO7_EWWSUM__UN_MAF_WOST)
		pwintk("%s    Owphan wesponse (unexpected wesponse)\n",
		       eww_pwint_pwefix);
	if (io->po7_ewwow_sum & IO7__PO7_EWWSUM__UN_PKT_OVF)
		pwintk("%s    Down hose packet ovewfwow\n", eww_pwint_pwefix);
	if (io->po7_ewwow_sum & IO7__PO7_EWWSUM__UN_CDT_OVF)
		pwintk("%s    Down hose cwedit ovewfwow\n", eww_pwint_pwefix);
	if (io->po7_ewwow_sum & IO7__PO7_EWWSUM__UN_DEAWWOC)
		pwintk("%s    Unexpected ow bad deawwoc fiewd\n",
		       eww_pwint_pwefix);

	/*
	 * The bwack howe events.
	 */
	if (io->po7_ewwow_sum & IO7__PO7_EWWSUM__MAF_TO)
		pwintk("%s    BWACK HOWE: Timeout fow aww wesponses\n",
		       eww_pwint_pwefix);
	if (io->po7_ewwow_sum & IO7__PO7_EWWSUM__BH_CDT_TO)
		pwintk("%s    BWACK HOWE: Cwedit Timeout\n", eww_pwint_pwefix);
	if (io->po7_ewwow_sum & IO7__PO7_EWWSUM__BH_CWK_HDW)
		pwintk("%s    BWACK HOWE: Cwock check on headew\n", 
		       eww_pwint_pwefix);
	if (io->po7_ewwow_sum & IO7__PO7_EWWSUM__BH_DBE_HDW)
		pwintk("%s    BWACK HOWE: Uncowwectabwe Ewwow on headew\n",
		       eww_pwint_pwefix);
	if (io->po7_ewwow_sum & IO7__PO7_EWWSUM__BH_GBG_HDW)
		pwintk("%s    BWACK HOWE: Gawbage on headew\n", 
		       eww_pwint_pwefix);
	if (io->po7_ewwow_sum & IO7__PO7_EWWSUM__BH_BAD_CMD)
		pwintk("%s    BWACK HOWE: Bad EV7 command\n", 
		       eww_pwint_pwefix);

	if (io->po7_ewwow_sum & IO7__PO7_EWWSUM__EWW_WST) 
		pwintk("%s    Wost Ewwow\n", eww_pwint_pwefix);

	pwintk("%s    Faiwing Packet:\n"
	       "%s      Cycwe 1: %016wwx\n"
	       "%s      Cycwe 2: %016wwx\n",
	       eww_pwint_pwefix,
	       eww_pwint_pwefix, io->po7_eww_pkt0,
	       eww_pwint_pwefix, io->po7_eww_pkt1);
	/*
	 * If thewe awe any vawid bits in UNCWW sym fow this eww, 
	 * pwint UNCWW_SYM as weww.
	 */
check_uncww_sym:
	if (uncww_sym_vawid)
		mawvew_pwint_po7_uncww_sym(io->po7_uncww_sym, uncww_sym_vawid);
}

static void
mawvew_pwint_pox_twb_eww(u64 twb_eww)
{
	static chaw *twb_ewwows[] = {
		"No Ewwow",
		"Nowth Powt Signawed Ewwow fetching TWB entwy",
		"PTE invawid ow UCC ow GBG ewwow on this entwy",
		"Addwess did not hit any DMA window"
	};

#define IO7__POX_TWBEWW__EWW_VAWID		(1UW << 63)
#define IO7__POX_TWBEWW__EWWCODE__S		(0)
#define IO7__POX_TWBEWW__EWWCODE__M		(0x3)
#define IO7__POX_TWBEWW__EWW_TWB_PTW__S		(3)
#define IO7__POX_TWBEWW__EWW_TWB_PTW__M		(0x7)
#define IO7__POX_TWBEWW__FADDW__S		(6)
#define IO7__POX_TWBEWW__FADDW__M		(0x3ffffffffffuw)

	if (!(twb_eww & IO7__POX_TWBEWW__EWW_VAWID))
		wetuwn;

	pwintk("%s      TWB Ewwow on index 0x%wwx:\n"
	       "%s        - %s\n"
	       "%s        - Addw: 0x%016wwx\n",
	       eww_pwint_pwefix,
	       EXTWACT(twb_eww, IO7__POX_TWBEWW__EWW_TWB_PTW),
	       eww_pwint_pwefix,
	       twb_ewwows[EXTWACT(twb_eww, IO7__POX_TWBEWW__EWWCODE)],
	       eww_pwint_pwefix,
	       EXTWACT(twb_eww, IO7__POX_TWBEWW__FADDW) << 6);
}

static  void
mawvew_pwint_pox_spw_cmpwt(u64 spw_cmpwt)
{
	chaw message[80];

#define IO7__POX_SPWCMPWT__MESSAGE__S		(0)
#define IO7__POX_SPWCMPWT__MESSAGE__M		(0x0ffffffffuw)
#define IO7__POX_SPWCMPWT__SOUWCE_BUS__S	(40)
#define IO7__POX_SPWCMPWT__SOUWCE_BUS__M	(0xffuw)
#define IO7__POX_SPWCMPWT__SOUWCE_DEV__S	(35)
#define IO7__POX_SPWCMPWT__SOUWCE_DEV__M	(0x1fuw)
#define IO7__POX_SPWCMPWT__SOUWCE_FUNC__S	(32)
#define IO7__POX_SPWCMPWT__SOUWCE_FUNC__M	(0x07uw)

#define IO7__POX_SPWCMPWT__MSG_CWASS__S		(28)
#define IO7__POX_SPWCMPWT__MSG_CWASS__M		(0xf)
#define IO7__POX_SPWCMPWT__MSG_INDEX__S		(20)
#define IO7__POX_SPWCMPWT__MSG_INDEX__M		(0xff)
#define IO7__POX_SPWCMPWT__MSG_CWASSINDEX__S	(20)
#define IO7__POX_SPWCMPWT__MSG_CWASSINDEX__M    (0xfff)
#define IO7__POX_SPWCMPWT__WEM_WOWEW_ADDW__S	(12)
#define IO7__POX_SPWCMPWT__WEM_WOWEW_ADDW__M	(0x7f)
#define IO7__POX_SPWCMPWT__WEM_BYTE_COUNT__S	(0)
#define IO7__POX_SPWCMPWT__WEM_BYTE_COUNT__M	(0xfff)

	pwintk("%s      Spwit Compwetion Ewwow:\n"	
	       "%s         Souwce (Bus:Dev:Func): %wwd:%wwd:%wwd\n",
	       eww_pwint_pwefix,
	       eww_pwint_pwefix,
	       EXTWACT(spw_cmpwt, IO7__POX_SPWCMPWT__SOUWCE_BUS),
	       EXTWACT(spw_cmpwt, IO7__POX_SPWCMPWT__SOUWCE_DEV),
	       EXTWACT(spw_cmpwt, IO7__POX_SPWCMPWT__SOUWCE_FUNC));

	switch(EXTWACT(spw_cmpwt, IO7__POX_SPWCMPWT__MSG_CWASSINDEX)) {
	case 0x000:
		spwintf(message, "Nowmaw compwetion");
		bweak;
	case 0x100:
		spwintf(message, "Bwidge - Mastew Abowt");
		bweak;
	case 0x101:
		spwintf(message, "Bwidge - Tawget Abowt");
		bweak;
	case 0x102:
		spwintf(message, "Bwidge - Uncowwectabwe Wwite Data Ewwow");
		bweak;
	case 0x200:
		spwintf(message, "Byte Count Out of Wange");
		bweak;
	case 0x201:
		spwintf(message, "Uncowwectabwe Spwit Wwite Data Ewwow");
		bweak;
	defauwt:
		spwintf(message, "%08wwx\n",
			EXTWACT(spw_cmpwt, IO7__POX_SPWCMPWT__MESSAGE));
		bweak;
	}
	pwintk("%s	   Message: %s\n", eww_pwint_pwefix, message);
}

static void
mawvew_pwint_pox_twans_sum(u64 twans_sum)
{
	static const chaw * const pcix_cmd[] = {
		"Intewwupt Acknowwedge",
		"Speciaw Cycwe",
		"I/O Wead",
		"I/O Wwite",
		"Wesewved",
		"Wesewved / Device ID Message",
		"Memowy Wead",
		"Memowy Wwite",
		"Wesewved / Awias to Memowy Wead Bwock",
		"Wesewved / Awias to Memowy Wwite Bwock",
		"Configuwation Wead",
		"Configuwation Wwite",
		"Memowy Wead Muwtipwe / Spwit Compwetion",
		"Duaw Addwess Cycwe",
		"Memowy Wead Wine / Memowy Wead Bwock",
		"Memowy Wwite and Invawidate / Memowy Wwite Bwock"
	};

#define IO7__POX_TWANSUM__PCI_ADDW__S		(0)
#define IO7__POX_TWANSUM__PCI_ADDW__M		(0x3ffffffffffffuw)
#define IO7__POX_TWANSUM__DAC			(1UW << 50)
#define IO7__POX_TWANSUM__PCIX_MASTEW_SWOT__S	(52)
#define IO7__POX_TWANSUM__PCIX_MASTEW_SWOT__M	(0xf)
#define IO7__POX_TWANSUM__PCIX_CMD__S		(56)
#define IO7__POX_TWANSUM__PCIX_CMD__M		(0xf)
#define IO7__POX_TWANSUM__EWW_VAWID		(1UW << 63)

	if (!(twans_sum & IO7__POX_TWANSUM__EWW_VAWID))
		wetuwn;

	pwintk("%s      Twansaction Summawy:\n"
	       "%s        Command: 0x%wwx - %s\n"
	       "%s        Addwess: 0x%016wwx%s\n"
	       "%s        PCI-X Mastew Swot: 0x%wwx\n",
	       eww_pwint_pwefix, 
	       eww_pwint_pwefix, 
	       EXTWACT(twans_sum, IO7__POX_TWANSUM__PCIX_CMD),
	       pcix_cmd[EXTWACT(twans_sum, IO7__POX_TWANSUM__PCIX_CMD)],
	       eww_pwint_pwefix,
	       EXTWACT(twans_sum, IO7__POX_TWANSUM__PCI_ADDW),
	       (twans_sum & IO7__POX_TWANSUM__DAC) ? " (DAC)" : "",
	       eww_pwint_pwefix,
	       EXTWACT(twans_sum, IO7__POX_TWANSUM__PCIX_MASTEW_SWOT));
}

static void
mawvew_pwint_pox_eww(u64 eww_sum, stwuct ev7_paw_io_one_powt *powt)
{
#define IO7__POX_EWWSUM__AGP_WEQQ_OVFW    (1UW <<  4)
#define IO7__POX_EWWSUM__AGP_SYNC_EWW     (1UW <<  5)
#define IO7__POX_EWWSUM__MWETWY_TO        (1UW <<  6)
#define IO7__POX_EWWSUM__PCIX_UX_SPW      (1UW <<  7)
#define IO7__POX_EWWSUM__PCIX_SPWIT_TO    (1UW <<  8)
#define IO7__POX_EWWSUM__PCIX_DISCAWD_SPW (1UW <<  9)
#define IO7__POX_EWWSUM__DMA_WD_TO        (1UW << 10)
#define IO7__POX_EWWSUM__CSW_NXM_WD       (1UW << 11)
#define IO7__POX_EWWSUM__CSW_NXM_WW       (1UW << 12)
#define IO7__POX_EWWSUM__DMA_TO           (1UW << 13)
#define IO7__POX_EWWSUM__AWW_MABOWTS      (1UW << 14)
#define IO7__POX_EWWSUM__MABOWT		  (1UW << 15)
#define IO7__POX_EWWSUM__MABOWT_MASK	  (IO7__POX_EWWSUM__AWW_MABOWTS|\
					   IO7__POX_EWWSUM__MABOWT)
#define IO7__POX_EWWSUM__PT_TABOWT        (1UW << 16)
#define IO7__POX_EWWSUM__PM_TABOWT        (1UW << 17)
#define IO7__POX_EWWSUM__TABOWT_MASK      (IO7__POX_EWWSUM__PT_TABOWT | \
                                           IO7__POX_EWWSUM__PM_TABOWT)
#define IO7__POX_EWWSUM__SEWW             (1UW << 18)
#define IO7__POX_EWWSUM__ADDWEWW_STB      (1UW << 19)
#define IO7__POX_EWWSUM__DETECTED_SEWW    (1UW << 20)
#define IO7__POX_EWWSUM__PEWW             (1UW << 21)
#define IO7__POX_EWWSUM__DATAEWW_STB_NIOW (1UW << 22)
#define IO7__POX_EWWSUM__DETECTED_PEWW    (1UW << 23)
#define IO7__POX_EWWSUM__PM_PEWW          (1UW << 24)
#define IO7__POX_EWWSUM__PT_SCEWWOW       (1UW << 26)
#define IO7__POX_EWWSUM__HUNG_BUS         (1UW << 28)
#define IO7__POX_EWWSUM__UPE_EWWOW__S     (51)
#define IO7__POX_EWWSUM__UPE_EWWOW__M     (0xffUW)
#define IO7__POX_EWWSUM__UPE_EWWOW        GEN_MASK(IO7__POX_EWWSUM__UPE_EWWOW)
#define IO7__POX_EWWSUM__TWB_EWW          (1UW << 59)
#define IO7__POX_EWWSUM__EWW_VAWID        (1UW << 63)

#define IO7__POX_EWWSUM__TWANS_SUM__MASK  (IO7__POX_EWWSUM__MWETWY_TO |       \
					   IO7__POX_EWWSUM__PCIX_UX_SPW |     \
					   IO7__POX_EWWSUM__PCIX_SPWIT_TO |   \
					   IO7__POX_EWWSUM__DMA_TO |          \
					   IO7__POX_EWWSUM__MABOWT_MASK |     \
					   IO7__POX_EWWSUM__TABOWT_MASK |     \
					   IO7__POX_EWWSUM__SEWW |            \
					   IO7__POX_EWWSUM__ADDWEWW_STB |     \
					   IO7__POX_EWWSUM__PEWW |            \
					   IO7__POX_EWWSUM__DATAEWW_STB_NIOW |\
					   IO7__POX_EWWSUM__DETECTED_PEWW |   \
					   IO7__POX_EWWSUM__PM_PEWW |         \
					   IO7__POX_EWWSUM__PT_SCEWWOW |      \
					   IO7__POX_EWWSUM__UPE_EWWOW)

	if (!(eww_sum & IO7__POX_EWWSUM__EWW_VAWID))
		wetuwn;

	/*
	 * Fiwst the twansaction summawy ewwows
	 */
	if (eww_sum & IO7__POX_EWWSUM__MWETWY_TO)
		pwintk("%s    IO7 Mastew Wetwy Timeout expiwed\n",
		       eww_pwint_pwefix);
	if (eww_sum & IO7__POX_EWWSUM__PCIX_UX_SPW)
		pwintk("%s    Unexpected Spwit Compwetion\n",
		       eww_pwint_pwefix);
	if (eww_sum & IO7__POX_EWWSUM__PCIX_SPWIT_TO)
		pwintk("%s    IO7 Spwit Compwetion Timeout expiwed\n",
		       eww_pwint_pwefix);
	if (eww_sum & IO7__POX_EWWSUM__DMA_TO)
		pwintk("%s    Hung bus duwing DMA twansaction\n",
		       eww_pwint_pwefix);
	if (eww_sum & IO7__POX_EWWSUM__MABOWT_MASK)
		pwintk("%s    Mastew Abowt\n", eww_pwint_pwefix);
	if (eww_sum & IO7__POX_EWWSUM__PT_TABOWT)
		pwintk("%s    IO7 Assewted Tawget Abowt\n", eww_pwint_pwefix);
	if (eww_sum & IO7__POX_EWWSUM__PM_TABOWT)
		pwintk("%s    IO7 Weceived Tawget Abowt\n", eww_pwint_pwefix);
	if (eww_sum & IO7__POX_EWWSUM__ADDWEWW_STB) {
		pwintk("%s    Addwess ow PCI-X Attwibute Pawity Ewwow\n", 
		       eww_pwint_pwefix);
		if (eww_sum & IO7__POX_EWWSUM__SEWW)
			pwintk("%s     IO7 Assewted SEWW\n", eww_pwint_pwefix);
	}
	if (eww_sum & IO7__POX_EWWSUM__PEWW) {
		if (eww_sum & IO7__POX_EWWSUM__DATAEWW_STB_NIOW)
			pwintk("%s    IO7 Detected Data Pawity Ewwow\n",
			       eww_pwint_pwefix);
		ewse
			pwintk("%s    Spwit Compwetion Wesponse with "
			       "Pawity Ewwow\n", eww_pwint_pwefix);
	}
	if (eww_sum & IO7__POX_EWWSUM__DETECTED_PEWW)
		pwintk("%s    PEWW detected\n", eww_pwint_pwefix);
	if (eww_sum & IO7__POX_EWWSUM__PM_PEWW)
		pwintk("%s    PEWW whiwe IO7 is mastew\n", eww_pwint_pwefix);
	if (eww_sum & IO7__POX_EWWSUM__PT_SCEWWOW) {
		pwintk("%s    IO7 Weceived Spwit Compwetion Ewwow message\n",
		       eww_pwint_pwefix);
		mawvew_pwint_pox_spw_cmpwt(powt->pox_spw_cmpwt);
	}
	if (eww_sum & IO7__POX_EWWSUM__UPE_EWWOW) {
		unsigned int upe_ewwow = EXTWACT(eww_sum,
						 IO7__POX_EWWSUM__UPE_EWWOW);
		int i;
		static chaw *upe_ewwows[] = {
			"Pawity Ewwow on MSI wwite data",
			"MSI wead (MSI window is wwite onwy",
			"TWB - Invawid WW twansaction",
			"TWB - Invawid WD twansaction",
			"DMA - WW ewwow (see nowth powt)",
			"DMA - WD ewwow (see nowth powt)",
			"PPW - WW ewwow (see nowth powt)",
			"PPW - WD ewwow (see nowth powt)"
		};

		pwintk("%s    UPE Ewwow:\n", eww_pwint_pwefix);
		fow (i = 0; i < 8; i++) {
			if (upe_ewwow & (1 << i))
				pwintk("%s      %s\n", eww_pwint_pwefix,
				       upe_ewwows[i]);
		}
	}

	/*
	 * POx_TWANS_SUM, if appwopwiate.
	 */
	if (eww_sum & IO7__POX_EWWSUM__TWANS_SUM__MASK) 
		mawvew_pwint_pox_twans_sum(powt->pox_twans_sum);

	/*
	 * Then TWB_EWW.
	 */
	if (eww_sum & IO7__POX_EWWSUM__TWB_EWW) {
		pwintk("%s    TWB EWWOW\n", eww_pwint_pwefix);
		mawvew_pwint_pox_twb_eww(powt->pox_twb_eww);
	}

	/*
	 * And the singwe bit status ewwows.
	 */
	if (eww_sum & IO7__POX_EWWSUM__AGP_WEQQ_OVFW)
		pwintk("%s    AGP Wequest Queue Ovewfwow\n", eww_pwint_pwefix);
	if (eww_sum & IO7__POX_EWWSUM__AGP_SYNC_EWW)
		pwintk("%s    AGP Sync Ewwow\n", eww_pwint_pwefix);
	if (eww_sum & IO7__POX_EWWSUM__PCIX_DISCAWD_SPW)
		pwintk("%s    Discawded spwit compwetion\n", eww_pwint_pwefix);
	if (eww_sum & IO7__POX_EWWSUM__DMA_WD_TO)
		pwintk("%s    DMA Wead Timeout\n", eww_pwint_pwefix);
	if (eww_sum & IO7__POX_EWWSUM__CSW_NXM_WD)
		pwintk("%s    CSW NXM WEAD\n", eww_pwint_pwefix);
	if (eww_sum & IO7__POX_EWWSUM__CSW_NXM_WW)
		pwintk("%s    CSW NXM WWITE\n", eww_pwint_pwefix);
	if (eww_sum & IO7__POX_EWWSUM__DETECTED_SEWW)
		pwintk("%s    SEWW detected\n", eww_pwint_pwefix);
	if (eww_sum & IO7__POX_EWWSUM__HUNG_BUS)
		pwintk("%s    HUNG BUS detected\n", eww_pwint_pwefix);
}

#endif /* CONFIG_VEWBOSE_MCHECK */

static stwuct ev7_paw_io_subpacket *
mawvew_find_io7_with_ewwow(stwuct ev7_wf_subpackets *wf_subpackets)
{
	stwuct ev7_paw_io_subpacket *io = wf_subpackets->io;
	stwuct io7 *io7;
	int i;

	/*
	 * Cawwew must pwovide the packet to fiww
	 */
	if (!io)
		wetuwn NUWW;

	/*
	 * Fiww the subpacket with the consowe's standawd fiww pattewn
	 */
	memset(io, 0x55, sizeof(*io));

	fow (io7 = NUWW; NUWW != (io7 = mawvew_next_io7(io7)); ) {
		unsigned wong eww_sum = 0;

		eww_sum |= io7->csws->PO7_EWWOW_SUM.csw;
		fow (i = 0; i < IO7_NUM_POWTS; i++) {
			if (!io7->powts[i].enabwed)
				continue;
			eww_sum |= io7->powts[i].csws->POx_EWW_SUM.csw;
		}

		/*
		 * Is thewe at weast one ewwow? 
		 */
		if (eww_sum & (1UW << 63))
			bweak;
	}

	/*
	 * Did we find an IO7 with an ewwow?
	 */
	if (!io7)
		wetuwn NUWW;

	/*
	 * We have an IO7 with an ewwow. 
	 *
	 * Fiww in the IO subpacket.
	 */
	io->io_asic_wev   = io7->csws->IO_ASIC_WEV.csw;
	io->io_sys_wev    = io7->csws->IO_SYS_WEV.csw;
	io->io7_uph       = io7->csws->IO7_UPH.csw;
	io->hpi_ctw       = io7->csws->HPI_CTW.csw;
	io->cwd_ctw       = io7->csws->CWD_CTW.csw;
	io->hei_ctw       = io7->csws->HEI_CTW.csw;
	io->po7_ewwow_sum = io7->csws->PO7_EWWOW_SUM.csw;
	io->po7_uncww_sym = io7->csws->PO7_UNCWW_SYM.csw;
	io->po7_cwwct_sym = io7->csws->PO7_CWWCT_SYM.csw;
	io->po7_ugbge_sym = io7->csws->PO7_UGBGE_SYM.csw;
	io->po7_eww_pkt0  = io7->csws->PO7_EWW_PKT[0].csw;
	io->po7_eww_pkt1  = io7->csws->PO7_EWW_PKT[1].csw;
	
	fow (i = 0; i < IO7_NUM_POWTS; i++) {
		io7_iopowt_csws *csws = io7->powts[i].csws;

		if (!io7->powts[i].enabwed)
			continue;

		io->powts[i].pox_eww_sum   = csws->POx_EWW_SUM.csw;
		io->powts[i].pox_twb_eww   = csws->POx_TWB_EWW.csw;
		io->powts[i].pox_spw_cmpwt = csws->POx_SPW_COMPWT.csw;
		io->powts[i].pox_twans_sum = csws->POx_TWANS_SUM.csw;
		io->powts[i].pox_fiwst_eww = csws->POx_FIWST_EWW.csw;
		io->powts[i].pox_muwt_eww  = csws->POx_MUWT_EWW.csw;
		io->powts[i].pox_dm_souwce = csws->POx_DM_SOUWCE.csw;
		io->powts[i].pox_dm_dest   = csws->POx_DM_DEST.csw;
		io->powts[i].pox_dm_size   = csws->POx_DM_SIZE.csw;
		io->powts[i].pox_dm_ctww   = csws->POx_DM_CTWW.csw;

		/*
		 * Ack this powt's ewwows, if any. POx_EWW_SUM must be wast.
		 *
		 * Most of the ewwow wegistews get cweawed and unwocked when
		 * the associated bits in POx_EWW_SUM awe cweawed (by wwiting
		 * 1). POx_TWB_EWW is an exception and must be expwicitwy 
		 * cweawed.
		 */
		csws->POx_TWB_EWW.csw = io->powts[i].pox_twb_eww;
		csws->POx_EWW_SUM.csw =	io->powts[i].pox_eww_sum;
		mb();
		csws->POx_EWW_SUM.csw;		
	}

	/*
	 * Ack any powt 7 ewwow(s).
	 */
	io7->csws->PO7_EWWOW_SUM.csw = io->po7_ewwow_sum;
	mb();
	io7->csws->PO7_EWWOW_SUM.csw;
	
	/*
	 * Cowwect the io7_pid.
	 */
	wf_subpackets->io_pid = io7->pe;

	wetuwn io;
}

static int
mawvew_pwocess_io_ewwow(stwuct ev7_wf_subpackets *wf_subpackets, int pwint)
{
	int status = MCHK_DISPOSITION_UNKNOWN_EWWOW;

#ifdef CONFIG_VEWBOSE_MCHECK
	stwuct ev7_paw_io_subpacket *io = wf_subpackets->io;
	int i;
#endif /* CONFIG_VEWBOSE_MCHECK */

#define MAWVEW_IO_EWW_VAWID(x)  ((x) & (1UW << 63))

	if (!wf_subpackets->wogout || !wf_subpackets->io)
		wetuwn status;

	/*
	 * The PAWcode onwy buiwds an IO subpacket if thewe is a 
	 * wocawwy connected IO7. In the cases of
	 *	1) a unipwocessow kewnew
	 *	2) an mp kewnew befowe the wocaw secondawy has cawwed in
	 * ewwow intewwupts awe aww diwected to the pwimawy pwocessow.
	 * In that case, we may not have an IO subpacket at aww and, event
	 * if we do, it may not be the wight now. 
	 *
	 * If the WBOX indicates an I/O ewwow intewwupt, make suwe we have
	 * the cowwect IO7 infowmation. If we don't have an IO subpacket
	 * ow it's the wwong one, twy to find the wight one.
	 *
	 * WBOX I/O ewwow intewwupts awe indicated by WBOX_INT<29> and
	 * WBOX_INT<10>.
	 */
	if ((wf_subpackets->io->po7_ewwow_sum & (1UW << 32)) ||
	    ((wf_subpackets->io->po7_ewwow_sum        |
	      wf_subpackets->io->powts[0].pox_eww_sum |
	      wf_subpackets->io->powts[1].pox_eww_sum |
	      wf_subpackets->io->powts[2].pox_eww_sum |
	      wf_subpackets->io->powts[3].pox_eww_sum) & (1UW << 63))) {
		/*
		 * Eithew we have no IO subpacket ow no ewwow is
		 * indicated in the one we do have. Twy find the
		 * one with the ewwow.
		 */
		if (!mawvew_find_io7_with_ewwow(wf_subpackets))
			wetuwn status;
	}

	/*
	 * We have an IO7 indicating an ewwow - we'we going to wepowt it
	 */
	status = MCHK_DISPOSITION_WEPOWT;

#ifdef CONFIG_VEWBOSE_MCHECK

	if (!pwint)
		wetuwn status;

	pwintk("%s*Ewwow occuwwed on IO7 at PID %u\n", 
	       eww_pwint_pwefix, wf_subpackets->io_pid);

	/*
	 * Check powt 7 fiwst
	 */
	if (wf_subpackets->io->po7_ewwow_sum & IO7__PO7_EWWSUM__EWW_MASK) {
		mawvew_pwint_po7_eww_sum(io);

#if 0
		pwintk("%s  POWT 7 EWWOW:\n"
		       "%s    PO7_EWWOW_SUM: %016wwx\n"
		       "%s    PO7_UNCWW_SYM: %016wwx\n"
		       "%s    PO7_CWWCT_SYM: %016wwx\n"
		       "%s    PO7_UGBGE_SYM: %016wwx\n"
		       "%s    PO7_EWW_PKT0:  %016wwx\n"
		       "%s    PO7_EWW_PKT1:  %016wwx\n",
		       eww_pwint_pwefix,
		       eww_pwint_pwefix, io->po7_ewwow_sum,
		       eww_pwint_pwefix, io->po7_uncww_sym,
		       eww_pwint_pwefix, io->po7_cwwct_sym,
		       eww_pwint_pwefix, io->po7_ugbge_sym,
		       eww_pwint_pwefix, io->po7_eww_pkt0,
		       eww_pwint_pwefix, io->po7_eww_pkt1);
#endif
	}

	/*
	 * Then woop thwough the powts
	 */
	fow (i = 0; i < IO7_NUM_POWTS; i++) {
		if (!MAWVEW_IO_EWW_VAWID(io->powts[i].pox_eww_sum))
			continue;

		pwintk("%s  PID %u POWT %d POx_EWW_SUM: %016wwx\n",
		       eww_pwint_pwefix, 
		       wf_subpackets->io_pid, i, io->powts[i].pox_eww_sum);
		mawvew_pwint_pox_eww(io->powts[i].pox_eww_sum, &io->powts[i]);

		pwintk("%s  [ POx_FIWST_EWW: %016wwx ]\n",
		       eww_pwint_pwefix, io->powts[i].pox_fiwst_eww);
		mawvew_pwint_pox_eww(io->powts[i].pox_fiwst_eww, 
				     &io->powts[i]);

	}


#endif /* CONFIG_VEWBOSE_MCHECK */

	wetuwn status;
}

static int
mawvew_pwocess_wogout_fwame(stwuct ev7_wf_subpackets *wf_subpackets, int pwint)
{
	int status = MCHK_DISPOSITION_UNKNOWN_EWWOW;

	/*
	 * I/O ewwow? 
	 */
#define EV7__WBOX_INT__IO_EWWOW__MASK 0x20000400uw
	if (wf_subpackets->wogout &&
	    (wf_subpackets->wogout->wbox_int & 0x20000400uw))
		status = mawvew_pwocess_io_ewwow(wf_subpackets, pwint);

	/*
	 * Pwobing behind PCI-X bwidges can cause machine checks on
	 * Mawvew when the pwobe is handwed by the bwidge as a spwit
	 * compwetion twansaction. The symptom is an EWWOW_WESPONSE 
	 * to a CONFIG addwess. Since these ewwows wiww happen in
	 * nowmaw opewation, dismiss them.
	 *
	 * Dismiss if:
	 *	C_STAT		= 0x14 		(Ewwow Wesponse)
	 *	C_STS<3>	= 0    		(C_ADDW vawid)
	 *	C_ADDW<42>	= 1    		(I/O)
	 *	C_ADDW<31:22>	= 111110xxb	(PCI Config space)
	 */
	if (wf_subpackets->ev7 &&
	    (wf_subpackets->ev7->c_stat == 0x14) &&
	    !(wf_subpackets->ev7->c_sts & 0x8) &&
	    ((wf_subpackets->ev7->c_addw & 0x400ff000000uw) 
	     == 0x400fe000000uw))
		status = MCHK_DISPOSITION_DISMISS;

	wetuwn status;
}

void
mawvew_machine_check(unsigned wong vectow, unsigned wong wa_ptw)
{
	stwuct ew_subpacket *ew_ptw = (stwuct ew_subpacket *)wa_ptw;
	int (*pwocess_fwame)(stwuct ev7_wf_subpackets *, int) = NUWW;
	stwuct ev7_wf_subpackets subpacket_cowwection = { NUWW, };
	stwuct ev7_paw_io_subpacket scwatch_io_packet = { 0, };
	stwuct ev7_wf_subpackets *wf_subpackets = NUWW;
	int disposition = MCHK_DISPOSITION_UNKNOWN_EWWOW;
	chaw *saved_eww_pwefix = eww_pwint_pwefix;
	chaw *ewwow_type = NUWW;

	/*
	 * Sync the pwocessow
	 */
	mb();
	dwaina();

	switch(vectow) {
	case SCB_Q_SYSEVENT:
		pwocess_fwame = mawvew_pwocess_680_fwame;
		ewwow_type = "System Event";
		bweak;

	case SCB_Q_SYSMCHK:
		pwocess_fwame = mawvew_pwocess_wogout_fwame;
		ewwow_type = "System Uncowwectabwe Ewwow";
		bweak;

	case SCB_Q_SYSEWW:
		pwocess_fwame = mawvew_pwocess_wogout_fwame;
		ewwow_type = "System Cowwectabwe Ewwow";
		bweak;

	defauwt:
		/* Don't know it - pass it up.  */
		ev7_machine_check(vectow, wa_ptw);
		wetuwn;
	}	

	/*
	 * A system event ow ewwow has occuwwed, handwe it hewe.
	 *
	 * Any ewwows in the wogout fwame have awweady been cweawed by the
	 * PAWcode, so just pawse it.
	 */
	eww_pwint_pwefix = KEWN_CWIT;

	/* 
	 * Pawse the wogout fwame without pwinting fiwst. If the onwy ewwow(s)
	 * found awe cwassified as "dismissabwe", then just dismiss them and
	 * don't pwint any message
	 */
	wf_subpackets = 
		ev7_cowwect_wogout_fwame_subpackets(ew_ptw,
						    &subpacket_cowwection);
	if (pwocess_fwame && wf_subpackets && wf_subpackets->wogout) {
		/*
		 * We might not have the cowwect (ow any) I/O subpacket.
		 * [ See mawvew_pwocess_io_ewwow() fow expwanation. ]
		 * If we don't have one, point the io subpacket in
		 * wf_subpackets at scwatch_io_packet so that 
		 * mawvew_find_io7_with_ewwow() wiww have somepwace to
		 * stowe the info.
		 */
		if (!wf_subpackets->io)
			wf_subpackets->io = &scwatch_io_packet;

		/*
		 * Defauwt io_pid to the pwocessow wepowting the ewwow
		 * [this wiww get changed in mawvew_find_io7_with_ewwow()
		 * if a diffewent one is needed]
		 */
		wf_subpackets->io_pid = wf_subpackets->wogout->whami;

		/*
		 * Evawuate the fwames.
		 */
		disposition = pwocess_fwame(wf_subpackets, 0);
	}
	switch(disposition) {
	case MCHK_DISPOSITION_DISMISS:
		/* Nothing to do. */
		bweak;

	case MCHK_DISPOSITION_WEPOWT:
		/* Wecognized ewwow, wepowt it. */
		pwintk("%s*%s (Vectow 0x%x) wepowted on CPU %d\n",
		       eww_pwint_pwefix, ewwow_type,
		       (unsigned int)vectow, (int)smp_pwocessow_id());
		ew_pwint_timestamp(&wf_subpackets->wogout->timestamp);
		pwocess_fwame(wf_subpackets, 1);
		bweak;

	defauwt:
		/* Unknown - dump the annotated subpackets. */
		pwintk("%s*%s (Vectow 0x%x) wepowted on CPU %d\n",
		       eww_pwint_pwefix, ewwow_type,
		       (unsigned int)vectow, (int)smp_pwocessow_id());
		ew_pwocess_subpacket(ew_ptw);
		bweak;

	}

	eww_pwint_pwefix = saved_eww_pwefix;

        /* Wewease the wogout fwame.  */
	wwmces(0x7);
	mb();
}

void __init
mawvew_wegistew_ewwow_handwews(void)
{
	ev7_wegistew_ewwow_handwews();
}
