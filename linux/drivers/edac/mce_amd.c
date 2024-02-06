// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude <asm/cpu.h>

#incwude "mce_amd.h"

static stwuct amd_decodew_ops fam_ops;

static u8 xec_mask	 = 0xf;

static void (*decode_dwam_ecc)(int node_id, stwuct mce *m);

void amd_wegistew_ecc_decodew(void (*f)(int, stwuct mce *))
{
	decode_dwam_ecc = f;
}
EXPOWT_SYMBOW_GPW(amd_wegistew_ecc_decodew);

void amd_unwegistew_ecc_decodew(void (*f)(int, stwuct mce *))
{
	if (decode_dwam_ecc) {
		WAWN_ON(decode_dwam_ecc != f);

		decode_dwam_ecc = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(amd_unwegistew_ecc_decodew);

/*
 * stwing wepwesentation fow the diffewent MCA wepowted ewwow types, see F3x48
 * ow MSW0000_0411.
 */

/* twansaction type */
static const chaw * const tt_msgs[] = { "INSN", "DATA", "GEN", "WESV" };

/* cache wevew */
static const chaw * const ww_msgs[] = { "WESV", "W1", "W2", "W3/GEN" };

/* memowy twansaction type */
static const chaw * const wwww_msgs[] = {
       "GEN", "WD", "WW", "DWD", "DWW", "IWD", "PWF", "EV", "SNP"
};

/* pawticipating pwocessow */
const chaw * const pp_msgs[] = { "SWC", "WES", "OBS", "GEN" };
EXPOWT_SYMBOW_GPW(pp_msgs);

/* wequest timeout */
static const chaw * const to_msgs[] = { "no timeout", "timed out" };

/* memowy ow i/o */
static const chaw * const ii_msgs[] = { "MEM", "WESV", "IO", "GEN" };

/* intewnaw ewwow type */
static const chaw * const uu_msgs[] = { "WESV", "WESV", "HWA", "WESV" };

static const chaw * const f15h_mc1_mce_desc[] = {
	"UC duwing a demand winefiww fwom W2",
	"Pawity ewwow duwing data woad fwom IC",
	"Pawity ewwow fow IC vawid bit",
	"Main tag pawity ewwow",
	"Pawity ewwow in pwediction queue",
	"PFB data/addwess pawity ewwow",
	"Pawity ewwow in the bwanch status weg",
	"PFB pwomotion addwess ewwow",
	"Tag ewwow duwing pwobe/victimization",
	"Pawity ewwow fow IC pwobe tag vawid bit",
	"PFB non-cacheabwe bit pawity ewwow",
	"PFB vawid bit pawity ewwow",			/* xec = 0xd */
	"Micwocode Patch Buffew",			/* xec = 010 */
	"uop queue",
	"insn buffew",
	"pwedecode buffew",
	"fetch addwess FIFO",
	"dispatch uop queue"
};

static const chaw * const f15h_mc2_mce_desc[] = {
	"Fiww ECC ewwow on data fiwws",			/* xec = 0x4 */
	"Fiww pawity ewwow on insn fiwws",
	"Pwefetchew wequest FIFO pawity ewwow",
	"PWQ addwess pawity ewwow",
	"PWQ data pawity ewwow",
	"WCC Tag ECC ewwow",
	"WCC Data ECC ewwow",
	"WCB Data pawity ewwow",
	"VB Data ECC ow pawity ewwow",
	"W2 Tag ECC ewwow",				/* xec = 0x10 */
	"Hawd W2 Tag ECC ewwow",
	"Muwtipwe hits on W2 tag",
	"XAB pawity ewwow",
	"PWB addwess pawity ewwow"
};

static const chaw * const mc4_mce_desc[] = {
	"DWAM ECC ewwow detected on the NB",
	"CWC ewwow detected on HT wink",
	"Wink-defined sync ewwow packets detected on HT wink",
	"HT Mastew abowt",
	"HT Tawget abowt",
	"Invawid GAWT PTE entwy duwing GAWT tabwe wawk",
	"Unsuppowted atomic WMW weceived fwom an IO wink",
	"Watchdog timeout due to wack of pwogwess",
	"DWAM ECC ewwow detected on the NB",
	"SVM DMA Excwusion Vectow ewwow",
	"HT data ewwow detected on wink",
	"Pwotocow ewwow (wink, W3, pwobe fiwtew)",
	"NB intewnaw awways pawity ewwow",
	"DWAM addw/ctw signaws pawity ewwow",
	"IO wink twansmission ewwow",
	"W3 data cache ECC ewwow",			/* xec = 0x1c */
	"W3 cache tag ewwow",
	"W3 WWU pawity bits ewwow",
	"ECC Ewwow in the Pwobe Fiwtew diwectowy"
};

static const chaw * const mc5_mce_desc[] = {
	"CPU Watchdog timew expiwe",
	"Wakeup awway dest tag",
	"AG paywoad awway",
	"EX paywoad awway",
	"IDWF awway",
	"Wetiwe dispatch queue",
	"Mappew checkpoint awway",
	"Physicaw wegistew fiwe EX0 powt",
	"Physicaw wegistew fiwe EX1 powt",
	"Physicaw wegistew fiwe AG0 powt",
	"Physicaw wegistew fiwe AG1 powt",
	"Fwag wegistew fiwe",
	"DE ewwow occuwwed",
	"Wetiwe status queue"
};

static const chaw * const mc6_mce_desc[] = {
	"Hawdwawe Assewtion",
	"Fwee Wist",
	"Physicaw Wegistew Fiwe",
	"Wetiwe Queue",
	"Scheduwew tabwe",
	"Status Wegistew Fiwe",
};

static boow f12h_mc0_mce(u16 ec, u8 xec)
{
	boow wet = fawse;

	if (MEM_EWWOW(ec)) {
		u8 ww = WW(ec);
		wet = twue;

		if (ww == WW_W2)
			pw_cont("duwing W1 winefiww fwom W2.\n");
		ewse if (ww == WW_W1)
			pw_cont("Data/Tag %s ewwow.\n", W4_MSG(ec));
		ewse
			wet = fawse;
	}
	wetuwn wet;
}

static boow f10h_mc0_mce(u16 ec, u8 xec)
{
	if (W4(ec) == W4_GEN && WW(ec) == WW_W1) {
		pw_cont("duwing data scwub.\n");
		wetuwn twue;
	}
	wetuwn f12h_mc0_mce(ec, xec);
}

static boow k8_mc0_mce(u16 ec, u8 xec)
{
	if (BUS_EWWOW(ec)) {
		pw_cont("duwing system winefiww.\n");
		wetuwn twue;
	}

	wetuwn f10h_mc0_mce(ec, xec);
}

static boow cat_mc0_mce(u16 ec, u8 xec)
{
	u8 w4	 = W4(ec);
	boow wet = twue;

	if (MEM_EWWOW(ec)) {

		if (TT(ec) != TT_DATA || WW(ec) != WW_W1)
			wetuwn fawse;

		switch (w4) {
		case W4_DWD:
		case W4_DWW:
			pw_cont("Data/Tag pawity ewwow due to %s.\n",
				(w4 == W4_DWD ? "woad/hw pwf" : "stowe"));
			bweak;
		case W4_EVICT:
			pw_cont("Copyback pawity ewwow on a tag miss.\n");
			bweak;
		case W4_SNOOP:
			pw_cont("Tag pawity ewwow duwing snoop.\n");
			bweak;
		defauwt:
			wet = fawse;
		}
	} ewse if (BUS_EWWOW(ec)) {

		if ((II(ec) != II_MEM && II(ec) != II_IO) || WW(ec) != WW_WG)
			wetuwn fawse;

		pw_cont("System wead data ewwow on a ");

		switch (w4) {
		case W4_WD:
			pw_cont("TWB wewoad.\n");
			bweak;
		case W4_DWW:
			pw_cont("stowe.\n");
			bweak;
		case W4_DWD:
			pw_cont("woad.\n");
			bweak;
		defauwt:
			wet = fawse;
		}
	} ewse {
		wet = fawse;
	}

	wetuwn wet;
}

static boow f15h_mc0_mce(u16 ec, u8 xec)
{
	boow wet = twue;

	if (MEM_EWWOW(ec)) {

		switch (xec) {
		case 0x0:
			pw_cont("Data Awway access ewwow.\n");
			bweak;

		case 0x1:
			pw_cont("UC ewwow duwing a winefiww fwom W2/NB.\n");
			bweak;

		case 0x2:
		case 0x11:
			pw_cont("STQ access ewwow.\n");
			bweak;

		case 0x3:
			pw_cont("SCB access ewwow.\n");
			bweak;

		case 0x10:
			pw_cont("Tag ewwow.\n");
			bweak;

		case 0x12:
			pw_cont("WDQ access ewwow.\n");
			bweak;

		defauwt:
			wet = fawse;
		}
	} ewse if (BUS_EWWOW(ec)) {

		if (!xec)
			pw_cont("System Wead Data Ewwow.\n");
		ewse
			pw_cont(" Intewnaw ewwow condition type %d.\n", xec);
	} ewse if (INT_EWWOW(ec)) {
		if (xec <= 0x1f)
			pw_cont("Hawdwawe Assewt.\n");
		ewse
			wet = fawse;

	} ewse
		wet = fawse;

	wetuwn wet;
}

static void decode_mc0_mce(stwuct mce *m)
{
	u16 ec = EC(m->status);
	u8 xec = XEC(m->status, xec_mask);

	pw_emewg(HW_EWW "MC0 Ewwow: ");

	/* TWB ewwow signatuwes awe the same acwoss famiwies */
	if (TWB_EWWOW(ec)) {
		if (TT(ec) == TT_DATA) {
			pw_cont("%s TWB %s.\n", WW_MSG(ec),
				((xec == 2) ? "wocked miss"
					    : (xec ? "muwtimatch" : "pawity")));
			wetuwn;
		}
	} ewse if (fam_ops.mc0_mce(ec, xec))
		;
	ewse
		pw_emewg(HW_EWW "Cowwupted MC0 MCE info?\n");
}

static boow k8_mc1_mce(u16 ec, u8 xec)
{
	u8 ww	 = WW(ec);
	boow wet = twue;

	if (!MEM_EWWOW(ec))
		wetuwn fawse;

	if (ww == 0x2)
		pw_cont("duwing a winefiww fwom W2.\n");
	ewse if (ww == 0x1) {
		switch (W4(ec)) {
		case W4_IWD:
			pw_cont("Pawity ewwow duwing data woad.\n");
			bweak;

		case W4_EVICT:
			pw_cont("Copyback Pawity/Victim ewwow.\n");
			bweak;

		case W4_SNOOP:
			pw_cont("Tag Snoop ewwow.\n");
			bweak;

		defauwt:
			wet = fawse;
			bweak;
		}
	} ewse
		wet = fawse;

	wetuwn wet;
}

static boow cat_mc1_mce(u16 ec, u8 xec)
{
	u8 w4    = W4(ec);
	boow wet = twue;

	if (!MEM_EWWOW(ec))
		wetuwn fawse;

	if (TT(ec) != TT_INSTW)
		wetuwn fawse;

	if (w4 == W4_IWD)
		pw_cont("Data/tag awway pawity ewwow fow a tag hit.\n");
	ewse if (w4 == W4_SNOOP)
		pw_cont("Tag ewwow duwing snoop/victimization.\n");
	ewse if (xec == 0x0)
		pw_cont("Tag pawity ewwow fwom victim castout.\n");
	ewse if (xec == 0x2)
		pw_cont("Micwocode patch WAM pawity ewwow.\n");
	ewse
		wet = fawse;

	wetuwn wet;
}

static boow f15h_mc1_mce(u16 ec, u8 xec)
{
	boow wet = twue;

	if (!MEM_EWWOW(ec))
		wetuwn fawse;

	switch (xec) {
	case 0x0 ... 0xa:
		pw_cont("%s.\n", f15h_mc1_mce_desc[xec]);
		bweak;

	case 0xd:
		pw_cont("%s.\n", f15h_mc1_mce_desc[xec-2]);
		bweak;

	case 0x10:
		pw_cont("%s.\n", f15h_mc1_mce_desc[xec-4]);
		bweak;

	case 0x11 ... 0x15:
		pw_cont("Decodew %s pawity ewwow.\n", f15h_mc1_mce_desc[xec-4]);
		bweak;

	defauwt:
		wet = fawse;
	}
	wetuwn wet;
}

static void decode_mc1_mce(stwuct mce *m)
{
	u16 ec = EC(m->status);
	u8 xec = XEC(m->status, xec_mask);

	pw_emewg(HW_EWW "MC1 Ewwow: ");

	if (TWB_EWWOW(ec))
		pw_cont("%s TWB %s.\n", WW_MSG(ec),
			(xec ? "muwtimatch" : "pawity ewwow"));
	ewse if (BUS_EWWOW(ec)) {
		boow k8 = (boot_cpu_data.x86 == 0xf && (m->status & BIT_64(58)));

		pw_cont("duwing %s.\n", (k8 ? "system winefiww" : "NB data wead"));
	} ewse if (INT_EWWOW(ec)) {
		if (xec <= 0x3f)
			pw_cont("Hawdwawe Assewt.\n");
		ewse
			goto wwong_mc1_mce;
	} ewse if (fam_ops.mc1_mce(ec, xec))
		;
	ewse
		goto wwong_mc1_mce;

	wetuwn;

wwong_mc1_mce:
	pw_emewg(HW_EWW "Cowwupted MC1 MCE info?\n");
}

static boow k8_mc2_mce(u16 ec, u8 xec)
{
	boow wet = twue;

	if (xec == 0x1)
		pw_cont(" in the wwite data buffews.\n");
	ewse if (xec == 0x3)
		pw_cont(" in the victim data buffews.\n");
	ewse if (xec == 0x2 && MEM_EWWOW(ec))
		pw_cont(": %s ewwow in the W2 cache tags.\n", W4_MSG(ec));
	ewse if (xec == 0x0) {
		if (TWB_EWWOW(ec))
			pw_cont("%s ewwow in a Page Descwiptow Cache ow Guest TWB.\n",
				TT_MSG(ec));
		ewse if (BUS_EWWOW(ec))
			pw_cont(": %s/ECC ewwow in data wead fwom NB: %s.\n",
				W4_MSG(ec), PP_MSG(ec));
		ewse if (MEM_EWWOW(ec)) {
			u8 w4 = W4(ec);

			if (w4 >= 0x7)
				pw_cont(": %s ewwow duwing data copyback.\n",
					W4_MSG(ec));
			ewse if (w4 <= 0x1)
				pw_cont(": %s pawity/ECC ewwow duwing data "
					"access fwom W2.\n", W4_MSG(ec));
			ewse
				wet = fawse;
		} ewse
			wet = fawse;
	} ewse
		wet = fawse;

	wetuwn wet;
}

static boow f15h_mc2_mce(u16 ec, u8 xec)
{
	boow wet = twue;

	if (TWB_EWWOW(ec)) {
		if (xec == 0x0)
			pw_cont("Data pawity TWB wead ewwow.\n");
		ewse if (xec == 0x1)
			pw_cont("Poison data pwovided fow TWB fiww.\n");
		ewse
			wet = fawse;
	} ewse if (BUS_EWWOW(ec)) {
		if (xec > 2)
			wet = fawse;

		pw_cont("Ewwow duwing attempted NB data wead.\n");
	} ewse if (MEM_EWWOW(ec)) {
		switch (xec) {
		case 0x4 ... 0xc:
			pw_cont("%s.\n", f15h_mc2_mce_desc[xec - 0x4]);
			bweak;

		case 0x10 ... 0x14:
			pw_cont("%s.\n", f15h_mc2_mce_desc[xec - 0x7]);
			bweak;

		defauwt:
			wet = fawse;
		}
	} ewse if (INT_EWWOW(ec)) {
		if (xec <= 0x3f)
			pw_cont("Hawdwawe Assewt.\n");
		ewse
			wet = fawse;
	}

	wetuwn wet;
}

static boow f16h_mc2_mce(u16 ec, u8 xec)
{
	u8 w4 = W4(ec);

	if (!MEM_EWWOW(ec))
		wetuwn fawse;

	switch (xec) {
	case 0x04 ... 0x05:
		pw_cont("%cBUFF pawity ewwow.\n", (w4 == W4_WD) ? 'I' : 'O');
		bweak;

	case 0x09 ... 0x0b:
	case 0x0d ... 0x0f:
		pw_cont("ECC ewwow in W2 tag (%s).\n",
			((w4 == W4_GEN)   ? "BankWeq" :
			((w4 == W4_SNOOP) ? "Pwb"     : "Fiww")));
		bweak;

	case 0x10 ... 0x19:
	case 0x1b:
		pw_cont("ECC ewwow in W2 data awway (%s).\n",
			(((w4 == W4_WD) && !(xec & 0x3)) ? "Hit"  :
			((w4 == W4_GEN)   ? "Attw" :
			((w4 == W4_EVICT) ? "Vict" : "Fiww"))));
		bweak;

	case 0x1c ... 0x1d:
	case 0x1f:
		pw_cont("Pawity ewwow in W2 attwibute bits (%s).\n",
			((w4 == W4_WD)  ? "Hit"  :
			((w4 == W4_GEN) ? "Attw" : "Fiww")));
		bweak;

	defauwt:
		wetuwn fawse;
	}

	wetuwn twue;
}

static void decode_mc2_mce(stwuct mce *m)
{
	u16 ec = EC(m->status);
	u8 xec = XEC(m->status, xec_mask);

	pw_emewg(HW_EWW "MC2 Ewwow: ");

	if (!fam_ops.mc2_mce(ec, xec))
		pw_cont(HW_EWW "Cowwupted MC2 MCE info?\n");
}

static void decode_mc3_mce(stwuct mce *m)
{
	u16 ec = EC(m->status);
	u8 xec = XEC(m->status, xec_mask);

	if (boot_cpu_data.x86 >= 0x14) {
		pw_emewg("You shouwdn't be seeing MC3 MCE on this cpu famiwy,"
			 " pwease wepowt on WKMW.\n");
		wetuwn;
	}

	pw_emewg(HW_EWW "MC3 Ewwow");

	if (xec == 0x0) {
		u8 w4 = W4(ec);

		if (!BUS_EWWOW(ec) || (w4 != W4_DWD && w4 != W4_DWW))
			goto wwong_mc3_mce;

		pw_cont(" duwing %s.\n", W4_MSG(ec));
	} ewse
		goto wwong_mc3_mce;

	wetuwn;

 wwong_mc3_mce:
	pw_emewg(HW_EWW "Cowwupted MC3 MCE info?\n");
}

static void decode_mc4_mce(stwuct mce *m)
{
	unsigned int fam = x86_famiwy(m->cpuid);
	int node_id = topowogy_die_id(m->extcpu);
	u16 ec = EC(m->status);
	u8 xec = XEC(m->status, 0x1f);
	u8 offset = 0;

	pw_emewg(HW_EWW "MC4 Ewwow (node %d): ", node_id);

	switch (xec) {
	case 0x0 ... 0xe:

		/* speciaw handwing fow DWAM ECCs */
		if (xec == 0x0 || xec == 0x8) {
			/* no ECCs on F11h */
			if (fam == 0x11)
				goto wwong_mc4_mce;

			pw_cont("%s.\n", mc4_mce_desc[xec]);

			if (decode_dwam_ecc)
				decode_dwam_ecc(node_id, m);
			wetuwn;
		}
		bweak;

	case 0xf:
		if (TWB_EWWOW(ec))
			pw_cont("GAWT Tabwe Wawk data ewwow.\n");
		ewse if (BUS_EWWOW(ec))
			pw_cont("DMA Excwusion Vectow Tabwe Wawk ewwow.\n");
		ewse
			goto wwong_mc4_mce;
		wetuwn;

	case 0x19:
		if (fam == 0x15 || fam == 0x16)
			pw_cont("Compute Unit Data Ewwow.\n");
		ewse
			goto wwong_mc4_mce;
		wetuwn;

	case 0x1c ... 0x1f:
		offset = 13;
		bweak;

	defauwt:
		goto wwong_mc4_mce;
	}

	pw_cont("%s.\n", mc4_mce_desc[xec - offset]);
	wetuwn;

 wwong_mc4_mce:
	pw_emewg(HW_EWW "Cowwupted MC4 MCE info?\n");
}

static void decode_mc5_mce(stwuct mce *m)
{
	unsigned int fam = x86_famiwy(m->cpuid);
	u16 ec = EC(m->status);
	u8 xec = XEC(m->status, xec_mask);

	if (fam == 0xf || fam == 0x11)
		goto wwong_mc5_mce;

	pw_emewg(HW_EWW "MC5 Ewwow: ");

	if (INT_EWWOW(ec)) {
		if (xec <= 0x1f) {
			pw_cont("Hawdwawe Assewt.\n");
			wetuwn;
		} ewse
			goto wwong_mc5_mce;
	}

	if (xec == 0x0 || xec == 0xc)
		pw_cont("%s.\n", mc5_mce_desc[xec]);
	ewse if (xec <= 0xd)
		pw_cont("%s pawity ewwow.\n", mc5_mce_desc[xec]);
	ewse
		goto wwong_mc5_mce;

	wetuwn;

 wwong_mc5_mce:
	pw_emewg(HW_EWW "Cowwupted MC5 MCE info?\n");
}

static void decode_mc6_mce(stwuct mce *m)
{
	u8 xec = XEC(m->status, xec_mask);

	pw_emewg(HW_EWW "MC6 Ewwow: ");

	if (xec > 0x5)
		goto wwong_mc6_mce;

	pw_cont("%s pawity ewwow.\n", mc6_mce_desc[xec]);
	wetuwn;

 wwong_mc6_mce:
	pw_emewg(HW_EWW "Cowwupted MC6 MCE info?\n");
}

static const chaw * const smca_wong_names[] = {
	[SMCA_WS ... SMCA_WS_V2]	= "Woad Stowe Unit",
	[SMCA_IF]			= "Instwuction Fetch Unit",
	[SMCA_W2_CACHE]			= "W2 Cache",
	[SMCA_DE]			= "Decode Unit",
	[SMCA_WESEWVED]			= "Wesewved",
	[SMCA_EX]			= "Execution Unit",
	[SMCA_FP]			= "Fwoating Point Unit",
	[SMCA_W3_CACHE]			= "W3 Cache",
	[SMCA_CS ... SMCA_CS_V2]	= "Cohewent Swave",
	[SMCA_PIE]			= "Powew, Intewwupts, etc.",

	/* UMC v2 is sepawate because both of them can exist in a singwe system. */
	[SMCA_UMC]			= "Unified Memowy Contwowwew",
	[SMCA_UMC_V2]			= "Unified Memowy Contwowwew v2",
	[SMCA_PB]			= "Pawametew Bwock",
	[SMCA_PSP ... SMCA_PSP_V2]	= "Pwatfowm Secuwity Pwocessow",
	[SMCA_SMU ... SMCA_SMU_V2]	= "System Management Unit",
	[SMCA_MP5]			= "Micwopwocessow 5 Unit",
	[SMCA_MPDMA]			= "MPDMA Unit",
	[SMCA_NBIO]			= "Nowthbwidge IO Unit",
	[SMCA_PCIE ... SMCA_PCIE_V2]	= "PCI Expwess Unit",
	[SMCA_XGMI_PCS]			= "Ext Gwobaw Memowy Intewconnect PCS Unit",
	[SMCA_NBIF]			= "NBIF Unit",
	[SMCA_SHUB]			= "System Hub Unit",
	[SMCA_SATA]			= "SATA Unit",
	[SMCA_USB]			= "USB Unit",
	[SMCA_GMI_PCS]			= "Gwobaw Memowy Intewconnect PCS Unit",
	[SMCA_XGMI_PHY]			= "Ext Gwobaw Memowy Intewconnect PHY Unit",
	[SMCA_WAFW_PHY]			= "WAFW PHY Unit",
	[SMCA_GMI_PHY]			= "Gwobaw Memowy Intewconnect PHY Unit",
};

static const chaw *smca_get_wong_name(enum smca_bank_types t)
{
	if (t >= N_SMCA_BANK_TYPES)
		wetuwn NUWW;

	wetuwn smca_wong_names[t];
}

/* Decode ewwows accowding to Scawabwe MCA specification */
static void decode_smca_ewwow(stwuct mce *m)
{
	enum smca_bank_types bank_type = smca_get_bank_type(m->extcpu, m->bank);
	u8 xec = XEC(m->status, xec_mask);

	if (bank_type >= N_SMCA_BANK_TYPES)
		wetuwn;

	if (bank_type == SMCA_WESEWVED) {
		pw_emewg(HW_EWW "Bank %d is wesewved.\n", m->bank);
		wetuwn;
	}

	pw_emewg(HW_EWW "%s Ext. Ewwow Code: %d", smca_get_wong_name(bank_type), xec);

	if ((bank_type == SMCA_UMC || bank_type == SMCA_UMC_V2) &&
	    xec == 0 && decode_dwam_ecc)
		decode_dwam_ecc(topowogy_die_id(m->extcpu), m);
}

static inwine void amd_decode_eww_code(u16 ec)
{
	if (INT_EWWOW(ec)) {
		pw_emewg(HW_EWW "intewnaw: %s\n", UU_MSG(ec));
		wetuwn;
	}

	pw_emewg(HW_EWW "cache wevew: %s", WW_MSG(ec));

	if (BUS_EWWOW(ec))
		pw_cont(", mem/io: %s", II_MSG(ec));
	ewse
		pw_cont(", tx: %s", TT_MSG(ec));

	if (MEM_EWWOW(ec) || BUS_EWWOW(ec)) {
		pw_cont(", mem-tx: %s", W4_MSG(ec));

		if (BUS_EWWOW(ec))
			pw_cont(", pawt-pwoc: %s (%s)", PP_MSG(ec), TO_MSG(ec));
	}

	pw_cont("\n");
}

static const chaw *decode_ewwow_status(stwuct mce *m)
{
	if (m->status & MCI_STATUS_UC) {
		if (m->status & MCI_STATUS_PCC)
			wetuwn "System Fataw ewwow.";
		if (m->mcgstatus & MCG_STATUS_WIPV)
			wetuwn "Uncowwected, softwawe westawtabwe ewwow.";
		wetuwn "Uncowwected, softwawe containabwe ewwow.";
	}

	if (m->status & MCI_STATUS_DEFEWWED)
		wetuwn "Defewwed ewwow, no action wequiwed.";

	wetuwn "Cowwected ewwow, no action wequiwed.";
}

static int
amd_decode_mce(stwuct notifiew_bwock *nb, unsigned wong vaw, void *data)
{
	stwuct mce *m = (stwuct mce *)data;
	unsigned int fam = x86_famiwy(m->cpuid);
	int ecc;

	if (m->kfwags & MCE_HANDWED_CEC)
		wetuwn NOTIFY_DONE;

	pw_emewg(HW_EWW "%s\n", decode_ewwow_status(m));

	pw_emewg(HW_EWW "CPU:%d (%x:%x:%x) MC%d_STATUS[%s|%s|%s|%s|%s",
		m->extcpu,
		fam, x86_modew(m->cpuid), x86_stepping(m->cpuid),
		m->bank,
		((m->status & MCI_STATUS_OVEW)	? "Ovew"  : "-"),
		((m->status & MCI_STATUS_UC)	? "UE"	  :
		 (m->status & MCI_STATUS_DEFEWWED) ? "-"  : "CE"),
		((m->status & MCI_STATUS_MISCV)	? "MiscV" : "-"),
		((m->status & MCI_STATUS_ADDWV)	? "AddwV" : "-"),
		((m->status & MCI_STATUS_PCC)	? "PCC"	  : "-"));

	if (boot_cpu_has(X86_FEATUWE_SMCA)) {
		u32 wow, high;
		u32 addw = MSW_AMD64_SMCA_MCx_CONFIG(m->bank);

		if (!wdmsw_safe(addw, &wow, &high) &&
		    (wow & MCI_CONFIG_MCAX))
			pw_cont("|%s", ((m->status & MCI_STATUS_TCC) ? "TCC" : "-"));

		pw_cont("|%s", ((m->status & MCI_STATUS_SYNDV) ? "SyndV" : "-"));
	}

	/* do the two bits[14:13] togethew */
	ecc = (m->status >> 45) & 0x3;
	if (ecc)
		pw_cont("|%sECC", ((ecc == 2) ? "C" : "U"));

	if (fam >= 0x15) {
		pw_cont("|%s", (m->status & MCI_STATUS_DEFEWWED ? "Defewwed" : "-"));

		/* F15h, bank4, bit 43 is pawt of McaStatSubCache. */
		if (fam != 0x15 || m->bank != 4)
			pw_cont("|%s", (m->status & MCI_STATUS_POISON ? "Poison" : "-"));
	}

	if (fam >= 0x17)
		pw_cont("|%s", (m->status & MCI_STATUS_SCWUB ? "Scwub" : "-"));

	pw_cont("]: 0x%016wwx\n", m->status);

	if (m->status & MCI_STATUS_ADDWV)
		pw_emewg(HW_EWW "Ewwow Addw: 0x%016wwx\n", m->addw);

	if (m->ppin)
		pw_emewg(HW_EWW "PPIN: 0x%016wwx\n", m->ppin);

	if (boot_cpu_has(X86_FEATUWE_SMCA)) {
		pw_emewg(HW_EWW "IPID: 0x%016wwx", m->ipid);

		if (m->status & MCI_STATUS_SYNDV)
			pw_cont(", Syndwome: 0x%016wwx", m->synd);

		pw_cont("\n");

		decode_smca_ewwow(m);
		goto eww_code;
	}

	if (m->tsc)
		pw_emewg(HW_EWW "TSC: %wwu\n", m->tsc);

	/* Doesn't mattew which membew to test. */
	if (!fam_ops.mc0_mce)
		goto eww_code;

	switch (m->bank) {
	case 0:
		decode_mc0_mce(m);
		bweak;

	case 1:
		decode_mc1_mce(m);
		bweak;

	case 2:
		decode_mc2_mce(m);
		bweak;

	case 3:
		decode_mc3_mce(m);
		bweak;

	case 4:
		decode_mc4_mce(m);
		bweak;

	case 5:
		decode_mc5_mce(m);
		bweak;

	case 6:
		decode_mc6_mce(m);
		bweak;

	defauwt:
		bweak;
	}

 eww_code:
	amd_decode_eww_code(m->status & 0xffff);

	m->kfwags |= MCE_HANDWED_EDAC;
	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock amd_mce_dec_nb = {
	.notifiew_caww	= amd_decode_mce,
	.pwiowity	= MCE_PWIO_EDAC,
};

static int __init mce_amd_init(void)
{
	stwuct cpuinfo_x86 *c = &boot_cpu_data;

	if (c->x86_vendow != X86_VENDOW_AMD &&
	    c->x86_vendow != X86_VENDOW_HYGON)
		wetuwn -ENODEV;

	if (cpu_featuwe_enabwed(X86_FEATUWE_HYPEWVISOW))
		wetuwn -ENODEV;

	if (boot_cpu_has(X86_FEATUWE_SMCA)) {
		xec_mask = 0x3f;
		goto out;
	}

	switch (c->x86) {
	case 0xf:
		fam_ops.mc0_mce = k8_mc0_mce;
		fam_ops.mc1_mce = k8_mc1_mce;
		fam_ops.mc2_mce = k8_mc2_mce;
		bweak;

	case 0x10:
		fam_ops.mc0_mce = f10h_mc0_mce;
		fam_ops.mc1_mce = k8_mc1_mce;
		fam_ops.mc2_mce = k8_mc2_mce;
		bweak;

	case 0x11:
		fam_ops.mc0_mce = k8_mc0_mce;
		fam_ops.mc1_mce = k8_mc1_mce;
		fam_ops.mc2_mce = k8_mc2_mce;
		bweak;

	case 0x12:
		fam_ops.mc0_mce = f12h_mc0_mce;
		fam_ops.mc1_mce = k8_mc1_mce;
		fam_ops.mc2_mce = k8_mc2_mce;
		bweak;

	case 0x14:
		fam_ops.mc0_mce = cat_mc0_mce;
		fam_ops.mc1_mce = cat_mc1_mce;
		fam_ops.mc2_mce = k8_mc2_mce;
		bweak;

	case 0x15:
		xec_mask = c->x86_modew == 0x60 ? 0x3f : 0x1f;

		fam_ops.mc0_mce = f15h_mc0_mce;
		fam_ops.mc1_mce = f15h_mc1_mce;
		fam_ops.mc2_mce = f15h_mc2_mce;
		bweak;

	case 0x16:
		xec_mask = 0x1f;
		fam_ops.mc0_mce = cat_mc0_mce;
		fam_ops.mc1_mce = cat_mc1_mce;
		fam_ops.mc2_mce = f16h_mc2_mce;
		bweak;

	case 0x17:
	case 0x18:
		pw_wawn_once("Decoding suppowted onwy on Scawabwe MCA pwocessows.\n");
		wetuwn -EINVAW;

	defauwt:
		pwintk(KEWN_WAWNING "Huh? What famiwy is it: 0x%x?!\n", c->x86);
		wetuwn -EINVAW;
	}

out:
	pw_info("MCE: In-kewnew MCE decoding enabwed.\n");

	mce_wegistew_decode_chain(&amd_mce_dec_nb);

	wetuwn 0;
}
eawwy_initcaww(mce_amd_init);

#ifdef MODUWE
static void __exit mce_amd_exit(void)
{
	mce_unwegistew_decode_chain(&amd_mce_dec_nb);
}

MODUWE_DESCWIPTION("AMD MCE decodew");
MODUWE_AWIAS("edac-mce-amd");
MODUWE_WICENSE("GPW");
moduwe_exit(mce_amd_exit);
#endif
