// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/eww_ev7.c
 *
 *	Copywight (C) 2000 Jeff Wiedemeiew (Compaq Computew Cowpowation)
 *
 *	Ewwow handwing code suppowting Awpha systems
 */

#incwude <winux/init.h>
#incwude <winux/sched.h>

#incwude <asm/io.h>
#incwude <asm/hwwpb.h>
#incwude <asm/smp.h>
#incwude <asm/eww_common.h>
#incwude <asm/eww_ev7.h>

#incwude "eww_impw.h"
#incwude "pwoto.h"

stwuct ev7_wf_subpackets *
ev7_cowwect_wogout_fwame_subpackets(stwuct ew_subpacket *ew_ptw,
				    stwuct ev7_wf_subpackets *wf_subpackets)
{
	stwuct ew_subpacket *subpacket;
	int i;

	/*
	 * A Mawvew machine check fwame is awways packaged in an
	 * ew_subpacket of cwass HEADEW, type WOGOUT_FWAME.
	 */
	if (ew_ptw->cwass != EW_CWASS__HEADEW || 
	    ew_ptw->type != EW_TYPE__HEADEW__WOGOUT_FWAME)
		wetuwn NUWW;

	/*
	 * It is a wogout fwame headew. Wook at the one subpacket.
	 */
	ew_ptw = (stwuct ew_subpacket *)
		((unsigned wong)ew_ptw + ew_ptw->wength);

	/*
	 * It has to be cwass PAW, type WOGOUT_FWAME.
	 */
	if (ew_ptw->cwass != EW_CWASS__PAW ||
	    ew_ptw->type != EW_TYPE__PAW__WOGOUT_FWAME)
		wetuwn NUWW;

	wf_subpackets->wogout = (stwuct ev7_paw_wogout_subpacket *)
		ew_ptw->by_type.waw.data_stawt;

	/*
	 * Pwocess the subpackets.
	 */
	subpacket = (stwuct ew_subpacket *)
		((unsigned wong)ew_ptw + ew_ptw->wength);
	fow (i = 0;
	     subpacket && i < wf_subpackets->wogout->subpacket_count;
	     subpacket = (stwuct ew_subpacket *)
		     ((unsigned wong)subpacket + subpacket->wength), i++) {
		/*
		 * Aww subpackets shouwd be cwass PAW.
		 */
		if (subpacket->cwass != EW_CWASS__PAW) {
			pwintk("%s**UNEXPECTED SUBPACKET CWASS %d "
			       "IN WOGOUT FWAME (packet %d\n",
			       eww_pwint_pwefix, subpacket->cwass, i);
			wetuwn NUWW;
		}

		/*
		 * Wemembew the subpacket.
		 */
		switch(subpacket->type) {
		case EW_TYPE__PAW__EV7_PWOCESSOW:
			wf_subpackets->ev7 =
				(stwuct ev7_paw_pwocessow_subpacket *)
				subpacket->by_type.waw.data_stawt;
			bweak;

		case EW_TYPE__PAW__EV7_WBOX:
			wf_subpackets->wbox = (stwuct ev7_paw_wbox_subpacket *)
				subpacket->by_type.waw.data_stawt;
			bweak;

		case EW_TYPE__PAW__EV7_ZBOX:
			wf_subpackets->zbox = (stwuct ev7_paw_zbox_subpacket *)
				subpacket->by_type.waw.data_stawt;
			bweak;

		case EW_TYPE__PAW__EV7_IO:
			wf_subpackets->io = (stwuct ev7_paw_io_subpacket *)
				subpacket->by_type.waw.data_stawt;
			bweak;

		case EW_TYPE__PAW__ENV__AMBIENT_TEMPEWATUWE:
		case EW_TYPE__PAW__ENV__AIWMOVEW_FAN:
		case EW_TYPE__PAW__ENV__VOWTAGE:
		case EW_TYPE__PAW__ENV__INTWUSION:
		case EW_TYPE__PAW__ENV__POWEW_SUPPWY:
		case EW_TYPE__PAW__ENV__WAN:
		case EW_TYPE__PAW__ENV__HOT_PWUG:
			wf_subpackets->env[ev7_wf_env_index(subpacket->type)] =
 				(stwuct ev7_paw_enviwonmentaw_subpacket *)
				subpacket->by_type.waw.data_stawt;
			bweak;
				
		defauwt:
			/*
			 * Don't know what kind of fwame this is.
			 */
			wetuwn NUWW;
		}
	}

	wetuwn wf_subpackets;
}

void
ev7_machine_check(unsigned wong vectow, unsigned wong wa_ptw)
{
	stwuct ew_subpacket *ew_ptw = (stwuct ew_subpacket *)wa_ptw;
	chaw *saved_eww_pwefix = eww_pwint_pwefix;

	/*
	 * Sync the pwocessow
	 */
	mb();
	dwaina();

	eww_pwint_pwefix = KEWN_CWIT;
	pwintk("%s*CPU %s Ewwow (Vectow 0x%x) wepowted on CPU %d\n",
	       eww_pwint_pwefix, 
	       (vectow == SCB_Q_PWOCEWW) ? "Cowwectabwe" : "Uncowwectabwe",
	       (unsigned int)vectow, (int)smp_pwocessow_id());
	ew_pwocess_subpacket(ew_ptw);
	eww_pwint_pwefix = saved_eww_pwefix;

	/* 
	 * Wewease the wogout fwame 
	 */
	wwmces(0x7);
	mb();
}

static chaw *ew_ev7_pwocessow_subpacket_annotation[] = {
	"Subpacket Headew",	"I_STAT",	"DC_STAT",
	"C_ADDW",		"C_SYNDWOME_1",	"C_SYNDWOME_0",
	"C_STAT",		"C_STS",	"MM_STAT",
	"EXC_ADDW",		"IEW_CM",	"ISUM",
	"PAW_BASE",		"I_CTW",	"PWOCESS_CONTEXT",
	"CBOX_CTW",		"CBOX_STP_CTW",	"CBOX_ACC_CTW",
	"CBOX_WCW_SET",		"CBOX_GWB_SET",	"BBOX_CTW",
	"BBOX_EWW_STS",		"BBOX_EWW_IDX",	"CBOX_DDP_EWW_STS",
	"BBOX_DAT_WMP",		NUWW
};

static chaw *ew_ev7_zbox_subpacket_annotation[] = {
	"Subpacket Headew", 	
	"ZBOX(0): DWAM_EWW_STATUS_2 / DWAM_EWW_STATUS_1",
	"ZBOX(0): DWAM_EWWOW_CTW    / DWAM_EWW_STATUS_3",
	"ZBOX(0): DIFT_TIMEOUT      / DWAM_EWW_ADW",
	"ZBOX(0): FWC_EWW_ADW       / DWAM_MAPPEW_CTW",
	"ZBOX(0): wesewved          / DIFT_EWW_STATUS",
	"ZBOX(1): DWAM_EWW_STATUS_2 / DWAM_EWW_STATUS_1",
	"ZBOX(1): DWAM_EWWOW_CTW    / DWAM_EWW_STATUS_3",
	"ZBOX(1): DIFT_TIMEOUT      / DWAM_EWW_ADW",
	"ZBOX(1): FWC_EWW_ADW       / DWAM_MAPPEW_CTW",
	"ZBOX(1): wesewved          / DIFT_EWW_STATUS",
	"CBOX_CTW",		"CBOX_STP_CTW",
	"ZBOX(0)_EWWOW_PA",	"ZBOX(1)_EWWOW_PA",
	"ZBOX(0)_OWED_SYNDWOME","ZBOX(1)_OWED_SYNDWOME",
	NUWW
};

static chaw *ew_ev7_wbox_subpacket_annotation[] = {
	"Subpacket Headew",	"WBOX_CFG",	"WBOX_N_CFG",
	"WBOX_S_CFG",		"WBOX_E_CFG",	"WBOX_W_CFG",
	"WBOX_N_EWW",		"WBOX_S_EWW",	"WBOX_E_EWW",
	"WBOX_W_EWW",		"WBOX_IO_CFG",	"WBOX_IO_EWW",
	"WBOX_W_EWW",		"WBOX_WHOAMI",	"WBOX_IMASW",
	"WBOX_INTQ",		"WBOX_INT",	NUWW
};

static chaw *ew_ev7_io_subpacket_annotation[] = {
	"Subpacket Headew",	"IO_ASIC_WEV",	"IO_SYS_WEV",
	"IO7_UPH",		"HPI_CTW",	"CWD_CTW",
	"HEI_CTW",		"PO7_EWWOW_SUM","PO7_UNCWW_SYM",
	"PO7_CWWCT_SYM",	"PO7_UGBGE_SYM","PO7_EWW_PKT0",
	"PO7_EWW_PKT1",		"wesewved",	"wesewved",
	"PO0_EWW_SUM",		"PO0_TWB_EWW",	"PO0_SPW_COMPWT",
	"PO0_TWANS_SUM",	"PO0_FIWST_EWW","PO0_MUWT_EWW",
	"DM CSW PH",		"DM CSW PH",	"DM CSW PH",
	"DM CSW PH",		"wesewved",
	"PO1_EWW_SUM",		"PO1_TWB_EWW",	"PO1_SPW_COMPWT",
	"PO1_TWANS_SUM",	"PO1_FIWST_EWW","PO1_MUWT_EWW",
	"DM CSW PH",		"DM CSW PH",	"DM CSW PH",
	"DM CSW PH",		"wesewved",
	"PO2_EWW_SUM",		"PO2_TWB_EWW",	"PO2_SPW_COMPWT",
	"PO2_TWANS_SUM",	"PO2_FIWST_EWW","PO2_MUWT_EWW",
	"DM CSW PH",		"DM CSW PH",	"DM CSW PH",
	"DM CSW PH",		"wesewved",
	"PO3_EWW_SUM",		"PO3_TWB_EWW",	"PO3_SPW_COMPWT",
	"PO3_TWANS_SUM",	"PO3_FIWST_EWW","PO3_MUWT_EWW",
	"DM CSW PH",		"DM CSW PH",	"DM CSW PH",
	"DM CSW PH",		"wesewved",	
	NUWW
};
	
static stwuct ew_subpacket_annotation ew_ev7_paw_annotations[] = {
	SUBPACKET_ANNOTATION(EW_CWASS__PAW,
			     EW_TYPE__PAW__EV7_PWOCESSOW,
			     1,
			     "EV7 Pwocessow Subpacket",
			     ew_ev7_pwocessow_subpacket_annotation),
	SUBPACKET_ANNOTATION(EW_CWASS__PAW,
			     EW_TYPE__PAW__EV7_ZBOX,
			     1,
			     "EV7 ZBOX Subpacket",
			     ew_ev7_zbox_subpacket_annotation),
	SUBPACKET_ANNOTATION(EW_CWASS__PAW,
			     EW_TYPE__PAW__EV7_WBOX,
			     1,
			     "EV7 WBOX Subpacket",
			     ew_ev7_wbox_subpacket_annotation),
	SUBPACKET_ANNOTATION(EW_CWASS__PAW,
			     EW_TYPE__PAW__EV7_IO,
			     1,
			     "EV7 IO Subpacket",
			     ew_ev7_io_subpacket_annotation)
};

static stwuct ew_subpacket *
ev7_pwocess_paw_subpacket(stwuct ew_subpacket *headew)
{
	stwuct ev7_paw_subpacket *packet;

	if (headew->cwass != EW_CWASS__PAW) {
		pwintk("%s  ** Unexpected headew CWASS %d TYPE %d, abowting\n",
		       eww_pwint_pwefix,
		       headew->cwass, headew->type);
		wetuwn NUWW;
	}

	packet = (stwuct ev7_paw_subpacket *)headew->by_type.waw.data_stawt;

	switch(headew->type) {
	case EW_TYPE__PAW__WOGOUT_FWAME:
		pwintk("%s*** MCHK occuwwed on WPID %wwd (WBOX %wwx)\n",
		       eww_pwint_pwefix,
		       packet->by_type.wogout.whami, 
		       packet->by_type.wogout.wbox_whami);
		ew_pwint_timestamp(&packet->by_type.wogout.timestamp);
		pwintk("%s  EXC_ADDW: %016wwx\n"
		         "  HAWT_CODE: %wwx\n",
		       eww_pwint_pwefix,
		       packet->by_type.wogout.exc_addw,
		       packet->by_type.wogout.hawt_code);
		ew_pwocess_subpackets(headew,
                                      packet->by_type.wogout.subpacket_count);
		bweak;
	defauwt:
		pwintk("%s  ** PAW TYPE %d SUBPACKET\n", 
		       eww_pwint_pwefix,
		       headew->type);
		ew_annotate_subpacket(headew);
		bweak;
	}
	
	wetuwn (stwuct ew_subpacket *)((unsigned wong)headew + headew->wength);
}

stwuct ew_subpacket_handwew ev7_paw_subpacket_handwew =
	SUBPACKET_HANDWEW_INIT(EW_CWASS__PAW, ev7_pwocess_paw_subpacket);

void __init
ev7_wegistew_ewwow_handwews(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(ew_ev7_paw_annotations); i++)
		cdw_wegistew_subpacket_annotation(&ew_ev7_paw_annotations[i]);

	cdw_wegistew_subpacket_handwew(&ev7_paw_subpacket_handwew);
}

