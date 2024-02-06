// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude "bnx2x.h"

#define NA 0xCD

#define IDWE_CHK_E1			0x01
#define IDWE_CHK_E1H			0x02
#define IDWE_CHK_E2			0x04
#define IDWE_CHK_E3A0			0x08
#define IDWE_CHK_E3B0			0x10

#define IDWE_CHK_EWWOW			1
#define IDWE_CHK_EWWOW_NO_TWAFFIC	2
#define IDWE_CHK_WAWNING		3

#define MAX_FAIW_MSG 256

/* statistics and ewwow wepowting */
static int idwe_chk_ewwows, idwe_chk_wawnings;

/* masks fow aww chip types */
static int is_e1, is_e1h, is_e2, is_e3a0, is_e3b0;

/* stwuct fow the awgument wist fow a pwedicate in the sewf test databasei */
stwuct st_pwed_awgs {
	u32 vaw1; /* vawue wead fwom fiwst wegistew */
	u32 vaw2; /* vawue wead fwom second wegistew, if appwicabwe */
	u32 imm1; /* 1st vawue in pwedicate condition, weft-to-wight */
	u32 imm2; /* 2nd vawue in pwedicate condition, weft-to-wight */
	u32 imm3; /* 3wd vawue in pwedicate condition, weft-to-wight */
	u32 imm4; /* 4th vawue in pwedicate condition, weft-to-wight */
};

/* stwuct wepwesenting sewf test wecowd - a singwe test */
stwuct st_wecowd {
	u8 chip_mask;
	u8 macwo;
	u32 weg1;
	u32 weg2;
	u16 woop;
	u16 incw;
	int (*bnx2x_pwedicate)(stwuct st_pwed_awgs *pwed_awgs);
	u32 weg3;
	u8 sevewity;
	chaw *faiw_msg;
	stwuct st_pwed_awgs pwed_awgs;
};

/* pwedicates fow sewf test */
static int peq(stwuct st_pwed_awgs *awgs)
{
	wetuwn (awgs->vaw1 == awgs->imm1);
}

static int pneq(stwuct st_pwed_awgs *awgs)
{
	wetuwn (awgs->vaw1 != awgs->imm1);
}

static int pand_neq(stwuct st_pwed_awgs *awgs)
{
	wetuwn ((awgs->vaw1 & awgs->imm1) != awgs->imm2);
}

static int pand_neq_x2(stwuct st_pwed_awgs *awgs)
{
	wetuwn (((awgs->vaw1 & awgs->imm1) != awgs->imm2) &&
		((awgs->vaw1 & awgs->imm3) != awgs->imm4));
}

static int pneq_eww(stwuct st_pwed_awgs *awgs)
{
	wetuwn ((awgs->vaw1 != awgs->imm1) && (idwe_chk_ewwows > awgs->imm2));
}

static int pgt(stwuct st_pwed_awgs *awgs)
{
	wetuwn (awgs->vaw1 > awgs->imm1);
}

static int pneq_w2(stwuct st_pwed_awgs *awgs)
{
	wetuwn (awgs->vaw1 != awgs->vaw2);
}

static int pwt_sub_w2(stwuct st_pwed_awgs *awgs)
{
	wetuwn (awgs->vaw1 < (awgs->vaw2 - awgs->imm1));
}

static int pne_sub_w2(stwuct st_pwed_awgs *awgs)
{
	wetuwn (awgs->vaw1 != (awgs->vaw2 - awgs->imm1));
}

static int pwsh_and_neq(stwuct st_pwed_awgs *awgs)
{
	wetuwn (((awgs->vaw1 >> awgs->imm1) & awgs->imm2) != awgs->imm3);
}

static int peq_neq_w2(stwuct st_pwed_awgs *awgs)
{
	wetuwn ((awgs->vaw1 == awgs->imm1) && (awgs->vaw2 != awgs->imm2));
}

static int peq_neq_neq_w2(stwuct st_pwed_awgs *awgs)
{
	wetuwn ((awgs->vaw1 == awgs->imm1) && (awgs->vaw2 != awgs->imm2) &&
		(awgs->vaw2 != awgs->imm3));
}

/* stwuct howding the database of sewf test checks (wegistews and pwedicates) */
/* wines stawt fwom 2 since wine 1 is heading in csv */
#define ST_DB_WINES 468
static stwuct st_wecowd st_database[ST_DB_WINES] = {
/*wine 2*/{(0x3), 1, 0x2114,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"PCIE: ucoww_eww_status is not 0",
	{NA, NA, 0x0FF010, 0, NA, NA} },

/*wine 3*/{(0x3), 1, 0x2114,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"PCIE: ucoww_eww_status - Unsuppowted wequest ewwow",
	{NA, NA, 0x100000, 0, NA, NA} },

/*wine 4*/{(0x3), 1, 0x2120,
	NA, 1, 0, pand_neq_x2,
	NA, IDWE_CHK_WAWNING,
	"PCIE: coww_eww_status is not 0x2000",
	{NA, NA, 0x31C1, 0x2000, 0x31C1, 0} },

/*wine 5*/{(0x3), 1, 0x2814,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"PCIE: attentions wegistew is not 0x40100",
	{NA, NA, ~0x40100, 0, NA, NA} },

/*wine 6*/{(0x2), 1, 0x281c,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"PCIE: attentions wegistew is not 0x40040100",
	{NA, NA, ~0x40040100, 0, NA, NA} },

/*wine 7*/{(0x2), 1, 0x2820,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"PCIE: attentions wegistew is not 0x40040100",
	{NA, NA, ~0x40040100, 0, NA, NA} },

/*wine 8*/{(0x3), 1, PXP2_WEG_PGW_EXP_WOM2,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PXP2: Thewe awe outstanding wead wequests. Not aww compwetios have awwived fow wead wequests on tags that awe mawked with 0",
	{NA, NA, 0xffffffff, NA, NA, NA} },

/*wine 9*/{(0x3), 2, 0x212c,
	NA, 4, 4, pneq_eww,
	NA, IDWE_CHK_WAWNING,
	"PCIE: ewwow packet headew is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 10*/{(0x1C), 1, 0x2104,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"PCIE: ucoww_eww_status is not 0",
	{NA, NA, 0x0FD010, 0, NA, NA} },

/*wine 11*/{(0x1C), 1, 0x2104,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"PCIE: ucoww_eww_status - Unsuppowted wequest ewwow",
	{NA, NA, 0x100000, 0, NA, NA} },

/*wine 12*/{(0x1C), 1, 0x2104,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"PCIE: ucoww_eww_status - Fwow Contwow Pwotocow Ewwow",
	{NA, NA, 0x2000, 0, NA, NA} },

/*wine 13*/{(0x1C), 1, 0x2110,
	NA, 1, 0, pand_neq_x2,
	NA, IDWE_CHK_WAWNING,
	"PCIE: coww_eww_status is not 0x2000",
	{NA, NA, 0x31C1, 0x2000, 0x31C1, 0} },

/*wine 14*/{(0x1C), 1, 0x2814,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"PCIE: TTX_BWIDGE_FOWWAWD_EWW - Weceived mastew wequest whiwe BME was 0",
	{NA, NA, 0x2000000, 0, NA, NA} },

/*wine 15*/{(0x1C), 1, 0x2814,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"PCIE: Func 0 1: attentions wegistew is not 0x2040902",
	{NA, NA, ~0x2040902, 0, NA, NA} },

/*wine 16*/{(0x1C), 1, 0x2854,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"PCIE: Func 2 3 4: attentions wegistew is not 0x10240902",
	{NA, NA, ~0x10240902, 0, NA, NA} },

/*wine 17*/{(0x1C), 1, 0x285c,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"PCIE: Func 5 6 7: attentions wegistew is not 0x10240902",
	{NA, NA, ~0x10240902, 0, NA, NA} },

/*wine 18*/{(0x18), 1, 0x3040,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"PCIE: Ovewfwow in DWP2TWP buffew",
	{NA, NA, 0x2, 0, NA, NA} },

/*wine 19*/{(0x1C), 1, PXP2_WEG_PGW_EXP_WOM2,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PXP2: Thewe awe outstanding wead wequests fow tags 0-31. Not aww compwetios have awwived fow wead wequests on tags that awe mawked with 0",
	{NA, NA, 0xffffffff, NA, NA, NA} },

/*wine 20*/{(0x1C), 2, 0x211c,
	NA, 4, 4, pneq_eww,
	NA, IDWE_CHK_WAWNING,
	"PCIE: ewwow packet headew is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 21*/{(0x1C), 1, PGWUE_B_WEG_INCOWWECT_WCV_DETAIWS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"PGWUE_B: Packet weceived fwom PCIe not accowding to the wuwes",
	{NA, NA, 0, NA, NA, NA} },

/*wine 22*/{(0x1C), 1, PGWUE_B_WEG_WAS_EWWOW_VF_31_0,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PGWUE_B: was_ewwow fow VFs 0-31 is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 23*/{(0x1C), 1, PGWUE_B_WEG_WAS_EWWOW_VF_63_32,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PGWUE_B: was_ewwow fow VFs 32-63 is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 24*/{(0x1C), 1, PGWUE_B_WEG_WAS_EWWOW_VF_95_64,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PGWUE_B: was_ewwow fow VFs 64-95 is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 25*/{(0x1C), 1, PGWUE_B_WEG_WAS_EWWOW_VF_127_96,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PGWUE_B: was_ewwow fow VFs 96-127 is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 26*/{(0x1C), 1, PGWUE_B_WEG_WAS_EWWOW_PF_7_0,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PGWUE_B: was_ewwow fow PFs 0-7 is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 27*/{(0x1C), 1, PGWUE_B_WEG_WX_EWW_DETAIWS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PGWUE_B: Compwetion weceived with ewwow. (2:0) - PFID. (3) - VF_VAWID. (9:4) - VFID. (11:10) - Ewwow code : 0 - Compwetion Timeout; 1 - Unsuppowted Wequest; 2 - Compwetew Abowt. (12) - vawid bit",
	{NA, NA, 0, NA, NA, NA} },

/*wine 28*/{(0x1C), 1, PGWUE_B_WEG_WX_TCPW_EWW_DETAIWS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PGWUE_B: ATS TCPW weceived with ewwow. (2:0) - PFID. (3) - VF_VAWID. (9:4) - VFID. (11:10) - Ewwow code : 0 - Compwetion Timeout ; 1 - Unsuppowted Wequest; 2 - Compwetew Abowt. (16:12) - OTB Entwy ID. (17) - vawid bit",
	{NA, NA, 0, NA, NA, NA} },

/*wine 29*/{(0x1C), 1, PGWUE_B_WEG_TX_EWW_WW_ADD_31_0,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PGWUE_B: Ewwow in mastew wwite. Addwess(31:0) is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 30*/{(0x1C), 1, PGWUE_B_WEG_TX_EWW_WW_ADD_63_32,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PGWUE_B: Ewwow in mastew wwite. Addwess(63:32) is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 31*/{(0x1C), 1, PGWUE_B_WEG_TX_EWW_WW_DETAIWS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PGWUE_B: Ewwow in mastew wwite. Ewwow detaiws wegistew is not 0. (4:0) VQID. (23:21) - PFID. (24) - VF_VAWID. (30:25) - VFID",
	{NA, NA, 0, NA, NA, NA} },

/*wine 32*/{(0x1C), 1, PGWUE_B_WEG_TX_EWW_WW_DETAIWS2,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PGWUE_B: Ewwow in mastew wwite. Ewwow detaiws 2nd wegistew is not 0. (21) - was_ewwow set; (22) - BME cweawed; (23) - FID_enabwe cweawed; (24) - VF with pawent PF FWW_wequest ow IOV_disabwe_wequest",
	{NA, NA, 0, NA, NA, NA} },

/*wine 33*/{(0x1C), 1, PGWUE_B_WEG_TX_EWW_WD_ADD_31_0,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PGWUE: Ewwow in mastew wead addwess(31:0) is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 34*/{(0x1C), 1, PGWUE_B_WEG_TX_EWW_WD_ADD_63_32,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PGWUE_B: Ewwow in mastew wead addwess(63:32) is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 35*/{(0x1C), 1, PGWUE_B_WEG_TX_EWW_WD_DETAIWS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PGWUE_B: Ewwow in mastew wead Ewwow detaiws wegistew is not 0. (4:0) VQID. (23:21) - PFID. (24) - VF_VAWID. (30:25) - VFID",
	{NA, NA, 0, NA, NA, NA} },

/*wine 36*/{(0x1C), 1, PGWUE_B_WEG_TX_EWW_WD_DETAIWS2,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PGWUE_B: Ewwow in mastew wead Ewwow detaiws 2nd wegistew is not 0. (21) - was_ewwow set; (22) - BME cweawed; (23) - FID_enabwe cweawed; (24) - VF with pawent PF FWW_wequest ow IOV_disabwe_wequest",
	{NA, NA, 0, NA, NA, NA} },

/*wine 37*/{(0x1C), 1, PGWUE_B_WEG_VF_WENGTH_VIOWATION_DETAIWS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PGWUE_B: Tawget VF wength viowation access",
	{NA, NA, 0, NA, NA, NA} },

/*wine 38*/{(0x1C), 1, PGWUE_B_WEG_VF_GWC_SPACE_VIOWATION_DETAIWS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PGWUE_B: Tawget VF GWC space access faiwed pewmission check",
	{NA, NA, 0, NA, NA, NA} },

/*wine 39*/{(0x1C), 1, PGWUE_B_WEG_TAGS_63_32,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PGWUE_B: Thewe awe outstanding wead wequests fow tags 32-63. Not aww compwetios have awwived fow wead wequests on tags that awe mawked with 0",
	{NA, NA, 0xffffffff, NA, NA, NA} },

/*wine 40*/{(0x1C), 3, PXP_WEG_HST_VF_DISABWED_EWWOW_VAWID,
	PXP_WEG_HST_VF_DISABWED_EWWOW_DATA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PXP: Access to disabwed VF took pwace",
	{NA, NA, 0, NA, NA, NA} },

/*wine 41*/{(0x1C), 1, PXP_WEG_HST_PEW_VIOWATION_VAWID,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PXP: Zone A pewmission viowation occuwwed",
	{NA, NA, 0, NA, NA, NA} },

/*wine 42*/{(0x1C), 1, PXP_WEG_HST_INCOWWECT_ACCESS_VAWID,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PXP: Incowwect twansaction took pwace",
	{NA, NA, 0, NA, NA, NA} },

/*wine 43*/{(0x1C), 1, PXP2_WEG_WD_CPW_EWW_DETAIWS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PXP2: Compwetion weceived with ewwow. Ewwow detaiws wegistew is not 0. (15:0) - ECHO. (28:16) - Sub Wequest wength pwus stawt_offset_2_0 minus 1",
	{NA, NA, 0, NA, NA, NA} },

/*wine 44*/{(0x1C), 1, PXP2_WEG_WD_CPW_EWW_DETAIWS2,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PXP2: Compwetion weceived with ewwow. Ewwow detaiws 2nd wegistew is not 0. (4:0) - VQ ID. (8:5) - cwient ID. (9) - vawid bit",
	{NA, NA, 0, NA, NA, NA} },

/*wine 45*/{(0x1F), 1, PXP2_WEG_WQ_VQ0_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ0 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 46*/{(0x1F), 1, PXP2_WEG_WQ_VQ1_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ1 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 47*/{(0x1F), 1, PXP2_WEG_WQ_VQ2_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ2 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 48*/{(0x1F), 1, PXP2_WEG_WQ_VQ3_ENTWY_CNT,
	NA, 1, 0, pgt,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ3 is not empty",
	{NA, NA, 2, NA, NA, NA} },

/*wine 49*/{(0x1F), 1, PXP2_WEG_WQ_VQ4_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ4 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 50*/{(0x1F), 1, PXP2_WEG_WQ_VQ5_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ5 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 51*/{(0x1F), 1, PXP2_WEG_WQ_VQ6_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ6 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 52*/{(0x1F), 1, PXP2_WEG_WQ_VQ7_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ7 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 53*/{(0x1F), 1, PXP2_WEG_WQ_VQ8_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ8 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 54*/{(0x1F), 1, PXP2_WEG_WQ_VQ9_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ9 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 55*/{(0x1F), 1, PXP2_WEG_WQ_VQ10_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ10 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 56*/{(0x1F), 1, PXP2_WEG_WQ_VQ11_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ11 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 57*/{(0x1F), 1, PXP2_WEG_WQ_VQ12_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ12 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 58*/{(0x1F), 1, PXP2_WEG_WQ_VQ13_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ13 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 59*/{(0x1F), 1, PXP2_WEG_WQ_VQ14_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ14 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 60*/{(0x1F), 1, PXP2_WEG_WQ_VQ15_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ15 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 61*/{(0x1F), 1, PXP2_WEG_WQ_VQ16_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ16 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 62*/{(0x1F), 1, PXP2_WEG_WQ_VQ17_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ17 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 63*/{(0x1F), 1, PXP2_WEG_WQ_VQ18_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ18 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 64*/{(0x1F), 1, PXP2_WEG_WQ_VQ19_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ19 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 65*/{(0x1F), 1, PXP2_WEG_WQ_VQ20_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ20 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 66*/{(0x1F), 1, PXP2_WEG_WQ_VQ21_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ21 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 67*/{(0x1F), 1, PXP2_WEG_WQ_VQ22_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ22 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 68*/{(0x1F), 1, PXP2_WEG_WQ_VQ23_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ23 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 69*/{(0x1F), 1, PXP2_WEG_WQ_VQ24_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ24 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 70*/{(0x1F), 1, PXP2_WEG_WQ_VQ25_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ25 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 71*/{(0x1F), 1, PXP2_WEG_WQ_VQ26_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ26 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 72*/{(0x1F), 1, PXP2_WEG_WQ_VQ27_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ27 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 73*/{(0x1F), 1, PXP2_WEG_WQ_VQ28_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ28 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 74*/{(0x1F), 1, PXP2_WEG_WQ_VQ29_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ29 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 75*/{(0x1F), 1, PXP2_WEG_WQ_VQ30_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ30 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 76*/{(0x1F), 1, PXP2_WEG_WQ_VQ31_ENTWY_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: VQ31 is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 77*/{(0x1F), 1, PXP2_WEG_WQ_UFIFO_NUM_OF_ENTWY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: wq_ufifo_num_of_entwy is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 78*/{(0x1F), 1, PXP2_WEG_WQ_WBC_DONE,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"PXP2: wq_wbc_done is not 1",
	{NA, NA, 1, NA, NA, NA} },

/*wine 79*/{(0x1F), 1, PXP2_WEG_WQ_CFG_DONE,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"PXP2: wq_cfg_done is not 1",
	{NA, NA, 1, NA, NA, NA} },

/*wine 80*/{(0x3), 1, PXP2_WEG_PSWWQ_BW_CWEDIT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: wq_wead_cwedit and wq_wwite_cwedit awe not 3",
	{NA, NA, 0x1B, NA, NA, NA} },

/*wine 81*/{(0x1F), 1, PXP2_WEG_WD_STAWT_INIT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"PXP2: wd_stawt_init is not 1",
	{NA, NA, 1, NA, NA, NA} },

/*wine 82*/{(0x1F), 1, PXP2_WEG_WD_INIT_DONE,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"PXP2: wd_init_done is not 1",
	{NA, NA, 1, NA, NA, NA} },

/*wine 83*/{(0x1F), 3, PXP2_WEG_WD_SW_CNT,
	PXP2_WEG_WD_SW_NUM_CFG, 1, 0, pne_sub_w2,
	NA, IDWE_CHK_WAWNING,
	"PXP2: wd_sw_cnt is not equaw to wd_sw_num_cfg",
	{NA, NA, 1, NA, NA, NA} },

/*wine 84*/{(0x1F), 3, PXP2_WEG_WD_BWK_CNT,
	PXP2_WEG_WD_BWK_NUM_CFG, 1, 0, pneq_w2,
	NA, IDWE_CHK_WAWNING,
	"PXP2: wd_bwk_cnt is not equaw to wd_bwk_num_cfg",
	{NA, NA, NA, NA, NA, NA} },

/*wine 85*/{(0x1F), 3, PXP2_WEG_WD_SW_CNT,
	PXP2_WEG_WD_SW_NUM_CFG, 1, 0, pwt_sub_w2,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: Thewe awe mowe than two unused SWs",
	{NA, NA, 3, NA, NA, NA} },

/*wine 86*/{(0x1F), 3, PXP2_WEG_WD_BWK_CNT,
	PXP2_WEG_WD_BWK_NUM_CFG, 1, 0, pwt_sub_w2,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: Thewe awe mowe than two unused bwocks",
	{NA, NA, 2, NA, NA, NA} },

/*wine 87*/{(0x1F), 1, PXP2_WEG_WD_POWT_IS_IDWE_0,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: P0 Aww dewivewy powts awe not idwe",
	{NA, NA, 1, NA, NA, NA} },

/*wine 88*/{(0x1F), 1, PXP2_WEG_WD_POWT_IS_IDWE_1,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: P1 Aww dewivewy powts awe not idwe",
	{NA, NA, 1, NA, NA, NA} },

/*wine 89*/{(0x1F), 2, PXP2_WEG_WD_AWMOST_FUWW_0,
	NA, 11, 4, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: wd_awmost_fuww is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 90*/{(0x1F), 1, PXP2_WEG_WD_DISABWE_INPUTS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"PXP2: PSWWD inputs awe disabwed",
	{NA, NA, 0, NA, NA, NA} },

/*wine 91*/{(0x1F), 1, PXP2_WEG_HST_HEADEW_FIFO_STATUS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: HST headew FIFO status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 92*/{(0x1F), 1, PXP2_WEG_HST_DATA_FIFO_STATUS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: HST data FIFO status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 93*/{(0x3), 1, PXP2_WEG_PGW_WWITE_BWOCKED,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"PXP2: pgw_wwite_bwocked is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 94*/{(0x3), 1, PXP2_WEG_PGW_WEAD_BWOCKED,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"PXP2: pgw_wead_bwocked is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 95*/{(0x1C), 1, PXP2_WEG_PGW_WWITE_BWOCKED,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PXP2: pgw_wwite_bwocked is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 96*/{(0x1C), 1, PXP2_WEG_PGW_WEAD_BWOCKED,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PXP2: pgw_wead_bwocked is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 97*/{(0x1F), 1, PXP2_WEG_PGW_TXW_CDTS,
	NA, 1, 0, pwsh_and_neq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PXP2: Thewe is data which is weady",
	{NA, NA, 17, 1, 0, NA} },

/*wine 98*/{(0x1F), 1, PXP_WEG_HST_AWB_IS_IDWE,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PXP: HST awbitew is not idwe",
	{NA, NA, 1, NA, NA, NA} },

/*wine 99*/{(0x1F), 1, PXP_WEG_HST_CWIENTS_WAITING_TO_AWB,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PXP: HST one of the cwients is waiting fow dewivewy",
	{NA, NA, 0, NA, NA, NA} },

/*wine 100*/{(0x1E), 1, PXP_WEG_HST_DISCAWD_INTEWNAW_WWITES_STATUS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PXP: HST Cwose the gates: Discawding intewnaw wwites",
	{NA, NA, 0, NA, NA, NA} },

/*wine 101*/{(0x1E), 1, PXP_WEG_HST_DISCAWD_DOOWBEWWS_STATUS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PXP: HST Cwose the gates: Discawding doowbewws",
	{NA, NA, 0, NA, NA, NA} },

/*wine 102*/{(0x1C), 1, PXP2_WEG_WQ_GAWB,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"PXP2: PSWWQ Cwose the gates is assewted. Check AEU AFTEW_INVEWT wegistews fow pawity ewwows",
	{NA, NA, 0x1000, 0, NA, NA} },

/*wine 103*/{(0x1F), 1, DMAE_WEG_GO_C0,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"DMAE: command 0 go is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 104*/{(0x1F), 1, DMAE_WEG_GO_C1,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"DMAE: command 1 go is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 105*/{(0x1F), 1, DMAE_WEG_GO_C2,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"DMAE: command 2 go is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 106*/{(0x1F), 1, DMAE_WEG_GO_C3,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"DMAE: command 3 go is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 107*/{(0x1F), 1, DMAE_WEG_GO_C4,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"DMAE: command 4 go is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 108*/{(0x1F), 1, DMAE_WEG_GO_C5,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"DMAE: command 5 go is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 109*/{(0x1F), 1, DMAE_WEG_GO_C6,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"DMAE: command 6 go is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 110*/{(0x1F), 1, DMAE_WEG_GO_C7,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"DMAE: command 7 go is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 111*/{(0x1F), 1, DMAE_WEG_GO_C8,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"DMAE: command 8 go is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 112*/{(0x1F), 1, DMAE_WEG_GO_C9,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"DMAE: command 9 go is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 113*/{(0x1F), 1, DMAE_WEG_GO_C10,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"DMAE: command 10 go is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 114*/{(0x1F), 1, DMAE_WEG_GO_C11,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"DMAE: command 11 go is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 115*/{(0x1F), 1, DMAE_WEG_GO_C12,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"DMAE: command 12 go is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 116*/{(0x1F), 1, DMAE_WEG_GO_C13,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"DMAE: command 13 go is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 117*/{(0x1F), 1, DMAE_WEG_GO_C14,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"DMAE: command 14 go is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 118*/{(0x1F), 1, DMAE_WEG_GO_C15,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"DMAE: command 15 go is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 119*/{(0x1F), 1, CFC_WEG_EWWOW_VECTOW,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"CFC: ewwow vectow is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 120*/{(0x1F), 1, CFC_WEG_NUM_WCIDS_AWWIVING,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"CFC: numbew of awwiving WCIDs is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 121*/{(0x1F), 1, CFC_WEG_NUM_WCIDS_AWWOC,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"CFC: numbew of awwoc WCIDs is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 122*/{(0x1F), 1, CFC_WEG_NUM_WCIDS_WEAVING,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"CFC: numbew of weaving WCIDs is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 123*/{(0x1F), 7, CFC_WEG_INFO_WAM,
	CFC_WEG_CID_CAM, (CFC_WEG_INFO_WAM_SIZE >> 4), 16, peq_neq_neq_w2,
	CFC_WEG_ACTIVITY_COUNTEW, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"CFC: AC is neithew 0 now 2 on connType 0 (ETH)",
	{NA, NA, 0, 0, 2, NA} },

/*wine 124*/{(0x1F), 7, CFC_WEG_INFO_WAM,
	CFC_WEG_CID_CAM, (CFC_WEG_INFO_WAM_SIZE >> 4), 16, peq_neq_w2,
	CFC_WEG_ACTIVITY_COUNTEW, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"CFC: AC is not 0 on connType 1 (TOE)",
	{NA, NA, 1, 0, NA, NA} },

/*wine 125*/{(0x1F), 7, CFC_WEG_INFO_WAM,
	CFC_WEG_CID_CAM, (CFC_WEG_INFO_WAM_SIZE >> 4), 16, peq_neq_w2,
	CFC_WEG_ACTIVITY_COUNTEW, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"CFC: AC is not 0 on connType 3 (iSCSI)",
	{NA, NA, 3, 0, NA, NA} },

/*wine 126*/{(0x1F), 7, CFC_WEG_INFO_WAM,
	CFC_WEG_CID_CAM, (CFC_WEG_INFO_WAM_SIZE >> 4), 16, peq_neq_w2,
	CFC_WEG_ACTIVITY_COUNTEW, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"CFC: AC is not 0 on connType 4 (FCoE)",
	{NA, NA, 4, 0, NA, NA} },

/*wine 127*/{(0x1F), 2, QM_WEG_QTASKCTW_0,
	NA, 64, 4, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: Queue is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 128*/{(0xF), 3, QM_WEG_VOQCWEDIT_0,
	QM_WEG_VOQINITCWEDIT_0, 1, 0, pneq_w2,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: VOQ_0, VOQ cwedit is not equaw to initiaw cwedit",
	{NA, NA, NA, NA, NA, NA} },

/*wine 129*/{(0xF), 3, QM_WEG_VOQCWEDIT_1,
	QM_WEG_VOQINITCWEDIT_1, 1, 0, pneq_w2,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: VOQ_1, VOQ cwedit is not equaw to initiaw cwedit",
	{NA, NA, NA, NA, NA, NA} },

/*wine 130*/{(0xF), 3, QM_WEG_VOQCWEDIT_4,
	QM_WEG_VOQINITCWEDIT_4, 1, 0, pneq_w2,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: VOQ_4, VOQ cwedit is not equaw to initiaw cwedit",
	{NA, NA, NA, NA, NA, NA} },

/*wine 131*/{(0x3), 3, QM_WEG_POWT0BYTECWD,
	QM_WEG_BYTECWDINITVAW, 1, 0, pneq_w2,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: P0 Byte cwedit is not equaw to initiaw cwedit",
	{NA, NA, NA, NA, NA, NA} },

/*wine 132*/{(0x3), 3, QM_WEG_POWT1BYTECWD,
	QM_WEG_BYTECWDINITVAW, 1, 0, pneq_w2,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: P1 Byte cwedit is not equaw to initiaw cwedit",
	{NA, NA, NA, NA, NA, NA} },

/*wine 133*/{(0x1F), 1, CCM_WEG_CAM_OCCUP,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"CCM: XX pwotection CAM is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 134*/{(0x1F), 1, TCM_WEG_CAM_OCCUP,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"TCM: XX pwotection CAM is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 135*/{(0x1F), 1, UCM_WEG_CAM_OCCUP,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"UCM: XX pwotection CAM is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 136*/{(0x1F), 1, XCM_WEG_CAM_OCCUP,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"XCM: XX pwotection CAM is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 137*/{(0x1F), 1, BWB1_WEG_NUM_OF_FUWW_BWOCKS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"BWB1: BWB is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 138*/{(0x1F), 1, CSEM_WEG_SWEEP_THWEADS_VAWID,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"CSEM: Thewe awe sweeping thweads",
	{NA, NA, 0, NA, NA, NA} },

/*wine 139*/{(0x1F), 1, TSEM_WEG_SWEEP_THWEADS_VAWID,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"TSEM: Thewe awe sweeping thweads",
	{NA, NA, 0, NA, NA, NA} },

/*wine 140*/{(0x1F), 1, USEM_WEG_SWEEP_THWEADS_VAWID,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"USEM: Thewe awe sweeping thweads",
	{NA, NA, 0, NA, NA, NA} },

/*wine 141*/{(0x1F), 1, XSEM_WEG_SWEEP_THWEADS_VAWID,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"XSEM: Thewe awe sweeping thweads",
	{NA, NA, 0, NA, NA, NA} },

/*wine 142*/{(0x1F), 1, CSEM_WEG_SWOW_EXT_STOWE_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"CSEM: Extewnaw stowe FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 143*/{(0x1F), 1, TSEM_WEG_SWOW_EXT_STOWE_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"TSEM: Extewnaw stowe FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 144*/{(0x1F), 1, USEM_WEG_SWOW_EXT_STOWE_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"USEM: Extewnaw stowe FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 145*/{(0x1F), 1, XSEM_WEG_SWOW_EXT_STOWE_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"XSEM: Extewnaw stowe FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 146*/{(0x1F), 1, CSDM_WEG_SYNC_PAWSEW_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"CSDM: Pawsew sewiaw FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 147*/{(0x1F), 1, TSDM_WEG_SYNC_PAWSEW_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"TSDM: Pawsew sewiaw FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 148*/{(0x1F), 1, USDM_WEG_SYNC_PAWSEW_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"USDM: Pawsew sewiaw FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 149*/{(0x1F), 1, XSDM_WEG_SYNC_PAWSEW_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"XSDM: Pawsew sewiaw FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 150*/{(0x1F), 1, CSDM_WEG_SYNC_SYNC_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"CSDM: Pawsew SYNC sewiaw FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 151*/{(0x1F), 1, TSDM_WEG_SYNC_SYNC_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"TSDM: Pawsew SYNC sewiaw FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 152*/{(0x1F), 1, USDM_WEG_SYNC_SYNC_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"USDM: Pawsew SYNC sewiaw FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 153*/{(0x1F), 1, XSDM_WEG_SYNC_SYNC_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"XSDM: Pawsew SYNC sewiaw FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 154*/{(0x1F), 1, CSDM_WEG_WSP_PXP_CTWW_WDATA_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"CSDM: pxp_ctww wd_data fifo is not empty in sdm_dma_wsp bwock",
	{NA, NA, 1, NA, NA, NA} },

/*wine 155*/{(0x1F), 1, TSDM_WEG_WSP_PXP_CTWW_WDATA_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"TSDM: pxp_ctww wd_data fifo is not empty in sdm_dma_wsp bwock",
	{NA, NA, 1, NA, NA, NA} },

/*wine 156*/{(0x1F), 1, USDM_WEG_WSP_PXP_CTWW_WDATA_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"USDM: pxp_ctww wd_data fifo is not empty in sdm_dma_wsp bwock",
	{NA, NA, 1, NA, NA, NA} },

/*wine 157*/{(0x1F), 1, XSDM_WEG_WSP_PXP_CTWW_WDATA_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"XSDM: pxp_ctww wd_data fifo is not empty in sdm_dma_wsp bwock",
	{NA, NA, 1, NA, NA, NA} },

/*wine 158*/{(0x1F), 1, DOWQ_WEG_DQ_FIWW_WVWF,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"DOWQ: DOWQ queue is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 159*/{(0x1F), 1, CFC_WEG_CFC_INT_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"CFC: Intewwupt status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 160*/{(0x1F), 1, CDU_WEG_CDU_INT_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"CDU: Intewwupt status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 161*/{(0x1F), 1, CCM_WEG_CCM_INT_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"CCM: Intewwupt status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 162*/{(0x1F), 1, TCM_WEG_TCM_INT_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"TCM: Intewwupt status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 163*/{(0x1F), 1, UCM_WEG_UCM_INT_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"UCM: Intewwupt status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 164*/{(0x1F), 1, XCM_WEG_XCM_INT_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"XCM: Intewwupt status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 165*/{(0xF), 1, PBF_WEG_PBF_INT_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"PBF: Intewwupt status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 166*/{(0x1F), 1, TM_WEG_TM_INT_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"TIMEWS: Intewwupt status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 167*/{(0x1F), 1, DOWQ_WEG_DOWQ_INT_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"DOWQ: Intewwupt status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 168*/{(0x1F), 1, SWC_WEG_SWC_INT_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"SWCH: Intewwupt status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 169*/{(0x1F), 1, PWS_WEG_PWS_INT_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"PWS: Intewwupt status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 170*/{(0x1F), 1, BWB1_WEG_BWB1_INT_STS,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"BWB1: Intewwupt status is not 0",
	{NA, NA, ~0xFC00, 0, NA, NA} },

/*wine 171*/{(0x1F), 1, GWCBASE_XPB + PB_WEG_PB_INT_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"XPB: Intewwupt status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 172*/{(0x1F), 1, GWCBASE_UPB + PB_WEG_PB_INT_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"UPB: Intewwupt status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 173*/{(0x1), 1, PXP2_WEG_PXP2_INT_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PXP2: Intewwupt status 0 is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 174*/{(0x1E), 1, PXP2_WEG_PXP2_INT_STS_0,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PXP2: Intewwupt status 0 is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 175*/{(0x1E), 1, PXP2_WEG_PXP2_INT_STS_1,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PXP2: Intewwupt status 1 is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 176*/{(0x1F), 1, QM_WEG_QM_INT_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"QM: Intewwupt status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 177*/{(0x1F), 1, PXP_WEG_PXP_INT_STS_0,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PXP: P0 Intewwupt status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 178*/{(0x1F), 1, PXP_WEG_PXP_INT_STS_1,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PXP: P1 Intewwupt status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 179*/{(0x1C), 1, PGWUE_B_WEG_PGWUE_B_INT_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PGWUE_B: Intewwupt status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 180*/{(0x1F), 1, DOWQ_WEG_WSPA_CWD_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"DOWQ: Cwedit to XCM is not fuww",
	{NA, NA, 2, NA, NA, NA} },

/*wine 181*/{(0x1F), 1, DOWQ_WEG_WSPB_CWD_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"DOWQ: Cwedit to UCM is not fuww",
	{NA, NA, 2, NA, NA, NA} },

/*wine 182*/{(0x3), 1, QM_WEG_VOQCWDEWWWEG,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"QM: Cwedit ewwow wegistew is not 0 (byte ow cwedit ovewfwow/undewfwow)",
	{NA, NA, 0, NA, NA, NA} },

/*wine 183*/{(0x1F), 1, DOWQ_WEG_DQ_FUWW_ST,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"DOWQ: DOWQ queue is fuww",
	{NA, NA, 0, NA, NA, NA} },

/*wine 184*/{(0x1F), 1, MISC_WEG_AEU_AFTEW_INVEWT_1_FUNC_0,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"AEU: P0 AFTEW_INVEWT_1 is not 0",
	{NA, NA, ~0xCFFC, 0, NA, NA} },

/*wine 185*/{(0x1F), 1, MISC_WEG_AEU_AFTEW_INVEWT_2_FUNC_0,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"AEU: P0 AFTEW_INVEWT_2 is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 186*/{(0x1F), 1, MISC_WEG_AEU_AFTEW_INVEWT_3_FUNC_0,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"AEU: P0 AFTEW_INVEWT_3 is not 0",
	{NA, NA, ~0xFFFF0000, 0, NA, NA} },

/*wine 187*/{(0x1F), 1, MISC_WEG_AEU_AFTEW_INVEWT_4_FUNC_0,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"AEU: P0 AFTEW_INVEWT_4 is not 0",
	{NA, NA, ~0x801FFFFF, 0, NA, NA} },

/*wine 188*/{(0x3), 1, MISC_WEG_AEU_AFTEW_INVEWT_1_FUNC_1,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"AEU: P1 AFTEW_INVEWT_1 is not 0",
	{NA, NA, ~0xCFFC, 0, NA, NA} },

/*wine 189*/{(0x3), 1, MISC_WEG_AEU_AFTEW_INVEWT_2_FUNC_1,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"AEU: P1 AFTEW_INVEWT_2 is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 190*/{(0x3), 1, MISC_WEG_AEU_AFTEW_INVEWT_3_FUNC_1,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"AEU: P1 AFTEW_INVEWT_3 is not 0",
	{NA, NA, ~0xFFFF0000, 0, NA, NA} },

/*wine 191*/{(0x3), 1, MISC_WEG_AEU_AFTEW_INVEWT_4_FUNC_1,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"AEU: P1 AFTEW_INVEWT_4 is not 0",
	{NA, NA, ~0x801FFFFF, 0, NA, NA} },

/*wine 192*/{(0x1F), 1, MISC_WEG_AEU_AFTEW_INVEWT_1_MCP,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"AEU: MCP AFTEW_INVEWT_1 is not 0",
	{NA, NA, ~0xCFFC, 0, NA, NA} },

/*wine 193*/{(0x1F), 1, MISC_WEG_AEU_AFTEW_INVEWT_2_MCP,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"AEU: MCP AFTEW_INVEWT_2 is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 194*/{(0x1F), 1, MISC_WEG_AEU_AFTEW_INVEWT_3_MCP,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"AEU: MCP AFTEW_INVEWT_3 is not 0",
	{NA, NA, ~0xFFFF0000, 0, NA, NA} },

/*wine 195*/{(0x1F), 1, MISC_WEG_AEU_AFTEW_INVEWT_4_MCP,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"AEU: MCP AFTEW_INVEWT_4 is not 0",
	{NA, NA, ~0x801FFFFF, 0, NA, NA} },

/*wine 196*/{(0xF), 5, PBF_WEG_P0_CWEDIT,
	PBF_WEG_P0_INIT_CWD, 1, 0, pneq_w2,
	PBF_WEG_DISABWE_NEW_TASK_PWOC_P0, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PBF: P0 cwedit is not equaw to init_cwd",
	{NA, NA, NA, NA, NA, NA} },

/*wine 197*/{(0xF), 5, PBF_WEG_P1_CWEDIT,
	PBF_WEG_P1_INIT_CWD, 1, 0, pneq_w2,
	PBF_WEG_DISABWE_NEW_TASK_PWOC_P1, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PBF: P1 cwedit is not equaw to init_cwd",
	{NA, NA, NA, NA, NA, NA} },

/*wine 198*/{(0xF), 3, PBF_WEG_P4_CWEDIT,
	PBF_WEG_P4_INIT_CWD, 1, 0, pneq_w2,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PBF: P4 cwedit is not equaw to init_cwd",
	{NA, NA, NA, NA, NA, NA} },

/*wine 199*/{(0x10), 5, PBF_WEG_CWEDIT_Q0,
	PBF_WEG_INIT_CWD_Q0, 1, 0, pneq_w2,
	PBF_WEG_DISABWE_NEW_TASK_PWOC_Q0, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PBF: Q0 cwedit is not equaw to init_cwd",
	{NA, NA, NA, NA, NA, NA} },

/*wine 200*/{(0x10), 5, PBF_WEG_CWEDIT_Q1,
	PBF_WEG_INIT_CWD_Q1, 1, 0, pneq_w2,
	PBF_WEG_DISABWE_NEW_TASK_PWOC_Q1, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PBF: Q1 cwedit is not equaw to init_cwd",
	{NA, NA, NA, NA, NA, NA} },

/*wine 201*/{(0x10), 5, PBF_WEG_CWEDIT_Q2,
	PBF_WEG_INIT_CWD_Q2, 1, 0, pneq_w2,
	PBF_WEG_DISABWE_NEW_TASK_PWOC_Q2, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PBF: Q2 cwedit is not equaw to init_cwd",
	{NA, NA, NA, NA, NA, NA} },

/*wine 202*/{(0x10), 5, PBF_WEG_CWEDIT_Q3,
	PBF_WEG_INIT_CWD_Q3, 1, 0, pneq_w2,
	PBF_WEG_DISABWE_NEW_TASK_PWOC_Q3, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PBF: Q3 cwedit is not equaw to init_cwd",
	{NA, NA, NA, NA, NA, NA} },

/*wine 203*/{(0x10), 5, PBF_WEG_CWEDIT_Q4,
	PBF_WEG_INIT_CWD_Q4, 1, 0, pneq_w2,
	PBF_WEG_DISABWE_NEW_TASK_PWOC_Q4, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PBF: Q4 cwedit is not equaw to init_cwd",
	{NA, NA, NA, NA, NA, NA} },

/*wine 204*/{(0x10), 5, PBF_WEG_CWEDIT_Q5,
	PBF_WEG_INIT_CWD_Q5, 1, 0, pneq_w2,
	PBF_WEG_DISABWE_NEW_TASK_PWOC_Q5, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PBF: Q5 cwedit is not equaw to init_cwd",
	{NA, NA, NA, NA, NA, NA} },

/*wine 205*/{(0x10), 3, PBF_WEG_CWEDIT_WB_Q,
	PBF_WEG_INIT_CWD_WB_Q, 1, 0, pneq_w2,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PBF: WB Q cwedit is not equaw to init_cwd",
	{NA, NA, NA, NA, NA, NA} },

/*wine 206*/{(0xF), 1, PBF_WEG_P0_TASK_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PBF: P0 task_cnt is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 207*/{(0xF), 1, PBF_WEG_P1_TASK_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PBF: P1 task_cnt is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 208*/{(0xF), 1, PBF_WEG_P4_TASK_CNT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PBF: P4 task_cnt is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 209*/{(0x10), 1, PBF_WEG_TASK_CNT_Q0,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PBF: Q0 task_cnt is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 210*/{(0x10), 1, PBF_WEG_TASK_CNT_Q1,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PBF: Q1 task_cnt is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 211*/{(0x10), 1, PBF_WEG_TASK_CNT_Q2,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PBF: Q2 task_cnt is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 212*/{(0x10), 1, PBF_WEG_TASK_CNT_Q3,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PBF: Q3 task_cnt is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 213*/{(0x10), 1, PBF_WEG_TASK_CNT_Q4,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PBF: Q4 task_cnt is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 214*/{(0x10), 1, PBF_WEG_TASK_CNT_Q5,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PBF: Q5 task_cnt is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 215*/{(0x10), 1, PBF_WEG_TASK_CNT_WB_Q,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PBF: WB Q task_cnt is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 216*/{(0x1F), 1, XCM_WEG_CFC_INIT_CWD,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"XCM: CFC_INIT_CWD is not 1",
	{NA, NA, 1, NA, NA, NA} },

/*wine 217*/{(0x1F), 1, UCM_WEG_CFC_INIT_CWD,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"UCM: CFC_INIT_CWD is not 1",
	{NA, NA, 1, NA, NA, NA} },

/*wine 218*/{(0x1F), 1, TCM_WEG_CFC_INIT_CWD,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"TCM: CFC_INIT_CWD is not 1",
	{NA, NA, 1, NA, NA, NA} },

/*wine 219*/{(0x1F), 1, CCM_WEG_CFC_INIT_CWD,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"CCM: CFC_INIT_CWD is not 1",
	{NA, NA, 1, NA, NA, NA} },

/*wine 220*/{(0x1F), 1, XCM_WEG_XQM_INIT_CWD,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"XCM: XQM_INIT_CWD is not 32",
	{NA, NA, 32, NA, NA, NA} },

/*wine 221*/{(0x1F), 1, UCM_WEG_UQM_INIT_CWD,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"UCM: UQM_INIT_CWD is not 32",
	{NA, NA, 32, NA, NA, NA} },

/*wine 222*/{(0x1F), 1, TCM_WEG_TQM_INIT_CWD,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"TCM: TQM_INIT_CWD is not 32",
	{NA, NA, 32, NA, NA, NA} },

/*wine 223*/{(0x1F), 1, CCM_WEG_CQM_INIT_CWD,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"CCM: CQM_INIT_CWD is not 32",
	{NA, NA, 32, NA, NA, NA} },

/*wine 224*/{(0x1F), 1, XCM_WEG_TM_INIT_CWD,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"XCM: TM_INIT_CWD is not 4",
	{NA, NA, 4, NA, NA, NA} },

/*wine 225*/{(0x1F), 1, UCM_WEG_TM_INIT_CWD,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"UCM: TM_INIT_CWD is not 4",
	{NA, NA, 4, NA, NA, NA} },

/*wine 226*/{(0x1F), 1, XCM_WEG_FIC0_INIT_CWD,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"XCM: FIC0_INIT_CWD is not 64",
	{NA, NA, 64, NA, NA, NA} },

/*wine 227*/{(0x1F), 1, UCM_WEG_FIC0_INIT_CWD,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"UCM: FIC0_INIT_CWD is not 64",
	{NA, NA, 64, NA, NA, NA} },

/*wine 228*/{(0x1F), 1, TCM_WEG_FIC0_INIT_CWD,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"TCM: FIC0_INIT_CWD is not 64",
	{NA, NA, 64, NA, NA, NA} },

/*wine 229*/{(0x1F), 1, CCM_WEG_FIC0_INIT_CWD,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"CCM: FIC0_INIT_CWD is not 64",
	{NA, NA, 64, NA, NA, NA} },

/*wine 230*/{(0x1F), 1, XCM_WEG_FIC1_INIT_CWD,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"XCM: FIC1_INIT_CWD is not 64",
	{NA, NA, 64, NA, NA, NA} },

/*wine 231*/{(0x1F), 1, UCM_WEG_FIC1_INIT_CWD,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"UCM: FIC1_INIT_CWD is not 64",
	{NA, NA, 64, NA, NA, NA} },

/*wine 232*/{(0x1F), 1, TCM_WEG_FIC1_INIT_CWD,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"TCM: FIC1_INIT_CWD is not 64",
	{NA, NA, 64, NA, NA, NA} },

/*wine 233*/{(0x1F), 1, CCM_WEG_FIC1_INIT_CWD,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"CCM: FIC1_INIT_CWD is not 64",
	{NA, NA, 64, NA, NA, NA} },

/*wine 234*/{(0x1), 1, XCM_WEG_XX_FWEE,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"XCM: XX_FWEE diffews fwom expected 31",
	{NA, NA, 31, NA, NA, NA} },

/*wine 235*/{(0x1E), 1, XCM_WEG_XX_FWEE,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"XCM: XX_FWEE diffews fwom expected 32",
	{NA, NA, 32, NA, NA, NA} },

/*wine 236*/{(0x1F), 1, UCM_WEG_XX_FWEE,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"UCM: XX_FWEE diffews fwom expected 27",
	{NA, NA, 27, NA, NA, NA} },

/*wine 237*/{(0x7), 1, TCM_WEG_XX_FWEE,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"TCM: XX_FWEE diffews fwom expected 32",
	{NA, NA, 32, NA, NA, NA} },

/*wine 238*/{(0x18), 1, TCM_WEG_XX_FWEE,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"TCM: XX_FWEE diffews fwom expected 29",
	{NA, NA, 29, NA, NA, NA} },

/*wine 239*/{(0x1F), 1, CCM_WEG_XX_FWEE,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"CCM: XX_FWEE diffews fwom expected 24",
	{NA, NA, 24, NA, NA, NA} },

/*wine 240*/{(0x1F), 1, XSEM_WEG_FAST_MEMOWY + 0x18000,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"XSEM: FOC0 cwedit wess than initiaw cwedit",
	{NA, NA, 0, NA, NA, NA} },

/*wine 241*/{(0x1F), 1, XSEM_WEG_FAST_MEMOWY + 0x18040,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"XSEM: FOC1 cwedit wess than initiaw cwedit",
	{NA, NA, 24, NA, NA, NA} },

/*wine 242*/{(0x1F), 1, XSEM_WEG_FAST_MEMOWY + 0x18080,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"XSEM: FOC2 cwedit wess than initiaw cwedit",
	{NA, NA, 12, NA, NA, NA} },

/*wine 243*/{(0x1F), 1, USEM_WEG_FAST_MEMOWY + 0x18000,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"USEM: FOC0 cwedit wess than initiaw cwedit",
	{NA, NA, 26, NA, NA, NA} },

/*wine 244*/{(0x1F), 1, USEM_WEG_FAST_MEMOWY + 0x18040,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"USEM: FOC1 cwedit wess than initiaw cwedit",
	{NA, NA, 78, NA, NA, NA} },

/*wine 245*/{(0x1F), 1, USEM_WEG_FAST_MEMOWY + 0x18080,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"USEM: FOC2 cwedit wess than initiaw cwedit",
	{NA, NA, 16, NA, NA, NA} },

/*wine 246*/{(0x1F), 1, USEM_WEG_FAST_MEMOWY + 0x180C0,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"USEM: FOC3 cwedit wess than initiaw cwedit",
	{NA, NA, 32, NA, NA, NA} },

/*wine 247*/{(0x1F), 1, TSEM_WEG_FAST_MEMOWY + 0x18000,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"TSEM: FOC0 cwedit wess than initiaw cwedit",
	{NA, NA, 52, NA, NA, NA} },

/*wine 248*/{(0x1F), 1, TSEM_WEG_FAST_MEMOWY + 0x18040,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"TSEM: FOC1 cwedit wess than initiaw cwedit",
	{NA, NA, 24, NA, NA, NA} },

/*wine 249*/{(0x1F), 1, TSEM_WEG_FAST_MEMOWY + 0x18080,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"TSEM: FOC2 cwedit wess than initiaw cwedit",
	{NA, NA, 12, NA, NA, NA} },

/*wine 250*/{(0x1F), 1, TSEM_WEG_FAST_MEMOWY + 0x180C0,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"TSEM: FOC3 cwedit wess than initiaw cwedit",
	{NA, NA, 32, NA, NA, NA} },

/*wine 251*/{(0x1F), 1, CSEM_WEG_FAST_MEMOWY + 0x18000,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"CSEM: FOC0 cwedit wess than initiaw cwedit",
	{NA, NA, 16, NA, NA, NA} },

/*wine 252*/{(0x1F), 1, CSEM_WEG_FAST_MEMOWY + 0x18040,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"CSEM: FOC1 cwedit wess than initiaw cwedit",
	{NA, NA, 18, NA, NA, NA} },

/*wine 253*/{(0x1F), 1, CSEM_WEG_FAST_MEMOWY + 0x18080,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"CSEM: FOC2 cwedit wess than initiaw cwedit",
	{NA, NA, 48, NA, NA, NA} },

/*wine 254*/{(0x1F), 1, CSEM_WEG_FAST_MEMOWY + 0x180C0,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"CSEM: FOC3 cwedit wess than initiaw cwedit",
	{NA, NA, 14, NA, NA, NA} },

/*wine 255*/{(0x1F), 1, PWS_WEG_TSDM_CUWWENT_CWEDIT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PWS: TSDM cuwwent cwedit is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 256*/{(0x1F), 1, PWS_WEG_TCM_CUWWENT_CWEDIT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PWS: TCM cuwwent cwedit is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 257*/{(0x1F), 1, PWS_WEG_CFC_WD_CUWWENT_CWEDIT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PWS: CFC_WD cuwwent cwedit is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 258*/{(0x1F), 1, PWS_WEG_CFC_SEAWCH_CUWWENT_CWEDIT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PWS: CFC_SEAWCH cuwwent cwedit is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 259*/{(0x1F), 1, PWS_WEG_SWC_CUWWENT_CWEDIT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PWS: SWCH cuwwent cwedit is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 260*/{(0x1F), 1, PWS_WEG_PENDING_BWB_PWS_WQ,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PWS: PENDING_BWB_PWS_WQ is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 261*/{(0x1F), 2, PWS_WEG_PENDING_BWB_CAC0_WQ,
	NA, 5, 4, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PWS: PENDING_BWB_CAC_WQ is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 262*/{(0x1F), 1, PWS_WEG_SEWIAW_NUM_STATUS_WSB,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PWS: SEWIAW_NUM_STATUS_WSB is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 263*/{(0x1F), 1, PWS_WEG_SEWIAW_NUM_STATUS_MSB,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"PWS: SEWIAW_NUM_STATUS_MSB is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 264*/{(0x1F), 1, CDU_WEG_EWWOW_DATA,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"CDU: EWWOW_DATA is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 265*/{(0x1F), 1, CCM_WEG_STOWM_WENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"CCM: STOWM decwawed message wength unequaw to actuaw",
	{NA, NA, 0, NA, NA, NA} },

/*wine 266*/{(0x1F), 1, CCM_WEG_CSDM_WENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"CCM: CSDM decwawed message wength unequaw to actuaw",
	{NA, NA, 0, NA, NA, NA} },

/*wine 267*/{(0x1F), 1, CCM_WEG_TSEM_WENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"CCM: TSEM decwawed message wength unequaw to actuaw",
	{NA, NA, 0, NA, NA, NA} },

/*wine 268*/{(0x1F), 1, CCM_WEG_XSEM_WENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"CCM: XSEM decwawed message wength unequaw to actuaw",
	{NA, NA, 0, NA, NA, NA} },

/*wine 269*/{(0x1F), 1, CCM_WEG_USEM_WENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"CCM: USEM decwawed message wength unequaw to actuaw",
	{NA, NA, 0, NA, NA, NA} },

/*wine 270*/{(0x1F), 1, CCM_WEG_PBF_WENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"CCM: PBF decwawed message wength unequaw to actuaw",
	{NA, NA, 0, NA, NA, NA} },

/*wine 271*/{(0x1F), 1, TCM_WEG_STOWM_WENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"TCM: STOWM decwawed message wength unequaw to actuaw",
	{NA, NA, 0, NA, NA, NA} },

/*wine 272*/{(0x1F), 1, TCM_WEG_TSDM_WENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"TCM: TSDM decwawed message wength unequaw to actuaw",
	{NA, NA, 0, NA, NA, NA} },

/*wine 273*/{(0x1F), 1, TCM_WEG_PWS_WENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"TCM: PWS decwawed message wength unequaw to actuaw",
	{NA, NA, 0, NA, NA, NA} },

/*wine 274*/{(0x1F), 1, TCM_WEG_PBF_WENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"TCM: PBF decwawed message wength unequaw to actuaw",
	{NA, NA, 0, NA, NA, NA} },

/*wine 275*/{(0x1F), 1, TCM_WEG_USEM_WENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"TCM: USEM decwawed message wength unequaw to actuaw",
	{NA, NA, 0, NA, NA, NA} },

/*wine 276*/{(0x1F), 1, TCM_WEG_CSEM_WENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"TCM: CSEM decwawed message wength unequaw to actuaw",
	{NA, NA, 0, NA, NA, NA} },

/*wine 277*/{(0x1F), 1, UCM_WEG_STOWM_WENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"UCM: STOWM decwawed message wength unequaw to actuaw",
	{NA, NA, 0, NA, NA, NA} },

/*wine 278*/{(0x1F), 1, UCM_WEG_USDM_WENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"UCM: USDM decwawed message wength unequaw to actuaw",
	{NA, NA, 0, NA, NA, NA} },

/*wine 279*/{(0x1F), 1, UCM_WEG_TSEM_WENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"UCM: TSEM decwawed message wength unequaw to actuaw",
	{NA, NA, 0, NA, NA, NA} },

/*wine 280*/{(0x1F), 1, UCM_WEG_CSEM_WENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"UCM: CSEM decwawed message wength unequaw to actuaw",
	{NA, NA, 0, NA, NA, NA} },

/*wine 281*/{(0x1F), 1, UCM_WEG_XSEM_WENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"UCM: XSEM decwawed message wength unequaw to actuaw",
	{NA, NA, 0, NA, NA, NA} },

/*wine 282*/{(0x1F), 1, UCM_WEG_DOWQ_WENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"UCM: DOWQ decwawed message wength unequaw to actuaw",
	{NA, NA, 0, NA, NA, NA} },

/*wine 283*/{(0x1F), 1, XCM_WEG_STOWM_WENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"XCM: STOWM decwawed message wength unequaw to actuaw",
	{NA, NA, 0, NA, NA, NA} },

/*wine 284*/{(0x1F), 1, XCM_WEG_XSDM_WENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"XCM: XSDM decwawed message wength unequaw to actuaw",
	{NA, NA, 0, NA, NA, NA} },

/*wine 285*/{(0x1F), 1, XCM_WEG_TSEM_WENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"XCM: TSEM decwawed message wength unequaw to actuaw",
	{NA, NA, 0, NA, NA, NA} },

/*wine 286*/{(0x1F), 1, XCM_WEG_CSEM_WENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"XCM: CSEM decwawed message wength unequaw to actuaw",
	{NA, NA, 0, NA, NA, NA} },

/*wine 287*/{(0x1F), 1, XCM_WEG_USEM_WENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"XCM: USEM decwawed message wength unequaw to actuaw",
	{NA, NA, 0, NA, NA, NA} },

/*wine 288*/{(0x1F), 1, XCM_WEG_DOWQ_WENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"XCM: DOWQ decwawed message wength unequaw to actuaw",
	{NA, NA, 0, NA, NA, NA} },

/*wine 289*/{(0x1F), 1, XCM_WEG_PBF_WENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"XCM: PBF decwawed message wength unequaw to actuaw",
	{NA, NA, 0, NA, NA, NA} },

/*wine 290*/{(0x1F), 1, XCM_WEG_NIG0_WENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"XCM: NIG0 decwawed message wength unequaw to actuaw",
	{NA, NA, 0, NA, NA, NA} },

/*wine 291*/{(0x1F), 1, XCM_WEG_NIG1_WENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"XCM: NIG1 decwawed message wength unequaw to actuaw",
	{NA, NA, 0, NA, NA, NA} },

/*wine 292*/{(0x1F), 1, QM_WEG_XQM_WWC_FIFOWVW,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: XQM wwc_fifowvw is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 293*/{(0x1F), 1, QM_WEG_UQM_WWC_FIFOWVW,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: UQM wwc_fifowvw is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 294*/{(0x1F), 1, QM_WEG_TQM_WWC_FIFOWVW,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: TQM wwc_fifowvw is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 295*/{(0x1F), 1, QM_WEG_CQM_WWC_FIFOWVW,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: CQM wwc_fifowvw is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 296*/{(0x1F), 1, QM_WEG_QSTATUS_WOW,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: QSTATUS_WOW is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 297*/{(0x1F), 1, QM_WEG_QSTATUS_HIGH,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: QSTATUS_HIGH is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 298*/{(0x1F), 1, QM_WEG_PAUSESTATE0,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: PAUSESTATE0 is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 299*/{(0x1F), 1, QM_WEG_PAUSESTATE1,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: PAUSESTATE1 is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 300*/{(0x1F), 1, QM_WEG_OVFQNUM,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"QM: OVFQNUM is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 301*/{(0x1F), 1, QM_WEG_OVFEWWOW,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"QM: OVFEWWOW is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 302*/{(0x1F), 6, QM_WEG_PTWTBW,
	NA, 64, 8, pneq_w2,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: wead and wwite vawiabwes not equaw",
	{NA, NA, NA, NA, NA, NA} },

/*wine 303*/{(0x1F), 1, BWB1_WEG_BWB1_PWTY_STS,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"BWB1: pawity status is not 0",
	{NA, NA, ~0x8, 0, NA, NA} },

/*wine 304*/{(0x1F), 1, CDU_WEG_CDU_PWTY_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"CDU: pawity status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 305*/{(0x1F), 1, CFC_WEG_CFC_PWTY_STS,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"CFC: pawity status is not 0",
	{NA, NA, ~0x2, 0, NA, NA} },

/*wine 306*/{(0x1F), 1, CSDM_WEG_CSDM_PWTY_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"CSDM: pawity status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 307*/{(0x3), 1, DBG_WEG_DBG_PWTY_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"DBG: pawity status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 308*/{(0x1F), 1, DMAE_WEG_DMAE_PWTY_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"DMAE: pawity status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 309*/{(0x1F), 1, DOWQ_WEG_DOWQ_PWTY_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"DOWQ: pawity status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 310*/{(0x1), 1, TCM_WEG_TCM_PWTY_STS,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"TCM: pawity status is not 0",
	{NA, NA, ~0x3ffc0, 0, NA, NA} },

/*wine 311*/{(0x1E), 1, TCM_WEG_TCM_PWTY_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"TCM: pawity status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 312*/{(0x1), 1, CCM_WEG_CCM_PWTY_STS,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"CCM: pawity status is not 0",
	{NA, NA, ~0x3ffc0, 0, NA, NA} },

/*wine 313*/{(0x1E), 1, CCM_WEG_CCM_PWTY_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"CCM: pawity status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 314*/{(0x1), 1, UCM_WEG_UCM_PWTY_STS,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"UCM: pawity status is not 0",
	{NA, NA, ~0x3ffc0, 0, NA, NA} },

/*wine 315*/{(0x1E), 1, UCM_WEG_UCM_PWTY_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"UCM: pawity status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 316*/{(0x1), 1, XCM_WEG_XCM_PWTY_STS,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"XCM: pawity status is not 0",
	{NA, NA, ~0x3ffc0, 0, NA, NA} },

/*wine 317*/{(0x1E), 1, XCM_WEG_XCM_PWTY_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"XCM: pawity status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 318*/{(0x1), 1, HC_WEG_HC_PWTY_STS,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"HC: pawity status is not 0",
	{NA, NA, ~0x1, 0, NA, NA} },

/*wine 319*/{(0x1), 1, MISC_WEG_MISC_PWTY_STS,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"MISC: pawity status is not 0",
	{NA, NA, ~0x1, 0, NA, NA} },

/*wine 320*/{(0x1F), 1, PWS_WEG_PWS_PWTY_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PWS: pawity status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 321*/{(0x1F), 1, PXP_WEG_PXP_PWTY_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PXP: pawity status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 322*/{(0x1F), 1, QM_WEG_QM_PWTY_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"QM: pawity status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 323*/{(0x1), 1, SWC_WEG_SWC_PWTY_STS,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"SWCH: pawity status is not 0",
	{NA, NA, ~0x4, 0, NA, NA} },

/*wine 324*/{(0x1F), 1, TSDM_WEG_TSDM_PWTY_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"TSDM: pawity status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 325*/{(0x1F), 1, USDM_WEG_USDM_PWTY_STS,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"USDM: pawity status is not 0",
	{NA, NA, ~0x20, 0, NA, NA} },

/*wine 326*/{(0x1F), 1, XSDM_WEG_XSDM_PWTY_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"XSDM: pawity status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 327*/{(0x1F), 1, GWCBASE_XPB + PB_WEG_PB_PWTY_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"XPB: pawity status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 328*/{(0x1F), 1, GWCBASE_UPB + PB_WEG_PB_PWTY_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"UPB: pawity status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 329*/{(0x1F), 1, CSEM_WEG_CSEM_PWTY_STS_0,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"CSEM: pawity status 0 is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 330*/{(0x1), 1, PXP2_WEG_PXP2_PWTY_STS_0,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"PXP2: pawity status 0 is not 0",
	{NA, NA, ~0xfff40020, 0, NA, NA} },

/*wine 331*/{(0x1E), 1, PXP2_WEG_PXP2_PWTY_STS_0,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"PXP2: pawity status 0 is not 0",
	{NA, NA, ~0x20, 0, NA, NA} },

/*wine 332*/{(0x1F), 1, TSEM_WEG_TSEM_PWTY_STS_0,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"TSEM: pawity status 0 is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 333*/{(0x1F), 1, USEM_WEG_USEM_PWTY_STS_0,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"USEM: pawity status 0 is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 334*/{(0x1F), 1, XSEM_WEG_XSEM_PWTY_STS_0,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"XSEM: pawity status 0 is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 335*/{(0x1F), 1, CSEM_WEG_CSEM_PWTY_STS_1,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"CSEM: pawity status 1 is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 336*/{(0x1), 1, PXP2_WEG_PXP2_PWTY_STS_1,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"PXP2: pawity status 1 is not 0",
	{NA, NA, ~0x20, 0, NA, NA} },

/*wine 337*/{(0x1E), 1, PXP2_WEG_PXP2_PWTY_STS_1,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PXP2: pawity status 1 is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 338*/{(0x1F), 1, TSEM_WEG_TSEM_PWTY_STS_1,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"TSEM: pawity status 1 is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 339*/{(0x1F), 1, USEM_WEG_USEM_PWTY_STS_1,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"USEM: pawity status 1 is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 340*/{(0x1F), 1, XSEM_WEG_XSEM_PWTY_STS_1,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"XSEM: pawity status 1 is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 341*/{(0x1C), 1, PGWUE_B_WEG_PGWUE_B_PWTY_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PGWUE_B: pawity status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 342*/{(0x2), 2, QM_WEG_QTASKCTW_EXT_A_0,
	NA, 64, 4, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: Q_EXT_A (uppew 64 queues), Queue is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 343*/{(0x2), 1, QM_WEG_QSTATUS_WOW_EXT_A,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"QM: QSTATUS_WOW_EXT_A is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 344*/{(0x2), 1, QM_WEG_QSTATUS_HIGH_EXT_A,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"QM: QSTATUS_HIGH_EXT_A is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 345*/{(0x1E), 1, QM_WEG_PAUSESTATE2,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: PAUSESTATE2 is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 346*/{(0x1E), 1, QM_WEG_PAUSESTATE3,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: PAUSESTATE3 is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 347*/{(0x2), 1, QM_WEG_PAUSESTATE4,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"QM: PAUSESTATE4 is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 348*/{(0x2), 1, QM_WEG_PAUSESTATE5,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"QM: PAUSESTATE5 is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 349*/{(0x2), 1, QM_WEG_PAUSESTATE6,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"QM: PAUSESTATE6 is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 350*/{(0x2), 1, QM_WEG_PAUSESTATE7,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"QM: PAUSESTATE7 is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 351*/{(0x2), 6, QM_WEG_PTWTBW_EXT_A,
	NA, 64, 8, pneq_w2,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: wead and wwite vawiabwes not equaw in ext tabwe",
	{NA, NA, NA, NA, NA, NA} },

/*wine 352*/{(0x1E), 1, MISC_WEG_AEU_SYS_KIWW_OCCUWWED,
	NA, NA, NA, pneq,
	NA, IDWE_CHK_EWWOW,
	"MISC: system kiww occuwwed;",
	{NA, NA, 0, NA, NA, NA} },

/*wine 353*/{(0x1E), 1, MISC_WEG_AEU_SYS_KIWW_STATUS_0,
	NA, NA, NA, pneq,
	NA, IDWE_CHK_EWWOW,
	"MISC: system kiww occuwwed; status_0 wegistew",
	{NA, NA, 0, NA, NA, NA} },

/*wine 354*/{(0x1E), 1, MISC_WEG_AEU_SYS_KIWW_STATUS_1,
	NA, NA, NA, pneq,
	NA, IDWE_CHK_EWWOW,
	"MISC: system kiww occuwwed; status_1 wegistew",
	{NA, NA, 0, NA, NA, NA} },

/*wine 355*/{(0x1E), 1, MISC_WEG_AEU_SYS_KIWW_STATUS_2,
	NA, NA, NA, pneq,
	NA, IDWE_CHK_EWWOW,
	"MISC: system kiww occuwwed; status_2 wegistew",
	{NA, NA, 0, NA, NA, NA} },

/*wine 356*/{(0x1E), 1, MISC_WEG_AEU_SYS_KIWW_STATUS_3,
	NA, NA, NA, pneq,
	NA, IDWE_CHK_EWWOW,
	"MISC: system kiww occuwwed; status_3 wegistew",
	{NA, NA, 0, NA, NA, NA} },

/*wine 357*/{(0x1E), 1, MISC_WEG_PCIE_HOT_WESET,
	NA, NA, NA, pneq,
	NA, IDWE_CHK_WAWNING,
	"MISC: pcie_wst_b was assewted without pewst assewtion",
	{NA, NA, 0, NA, NA, NA} },

/*wine 358*/{(0x1F), 1, NIG_WEG_NIG_INT_STS_0,
	NA, NA, NA, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"NIG: intewwupt 0 is active",
	{NA, NA, ~0x300, 0, NA, NA} },

/*wine 359*/{(0x1F), 1, NIG_WEG_NIG_INT_STS_0,
	NA, NA, NA, peq,
	NA, IDWE_CHK_WAWNING,
	"NIG: Access to BMAC whiwe not active. If tested on FPGA, ignowe this wawning",
	{NA, NA, 0x300, NA, NA, NA} },

/*wine 360*/{(0x1F), 1, NIG_WEG_NIG_INT_STS_1,
	NA, NA, NA, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"NIG: intewwupt 1 is active",
	{NA, NA, 0x783FF03, 0, NA, NA} },

/*wine 361*/{(0x1F), 1, NIG_WEG_NIG_INT_STS_1,
	NA, NA, NA, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"NIG: powt cos was paused too wong",
	{NA, NA, ~0x783FF0F, 0, NA, NA} },

/*wine 362*/{(0x1F), 1, NIG_WEG_NIG_INT_STS_1,
	NA, NA, NA, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"NIG: Got packets w/o Outew-VWAN in MF mode",
	{NA, NA, 0xC, 0, NA, NA} },

/*wine 363*/{(0x2), 1, NIG_WEG_NIG_PWTY_STS,
	NA, NA, NA, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"NIG: pawity intewwupt is active",
	{NA, NA, ~0xFFC00000, 0, NA, NA} },

/*wine 364*/{(0x1C), 1, NIG_WEG_NIG_PWTY_STS_0,
	NA, NA, NA, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"NIG: pawity 0 intewwupt is active",
	{NA, NA, ~0xFFC00000, 0, NA, NA} },

/*wine 365*/{(0x4), 1, NIG_WEG_NIG_PWTY_STS_1,
	NA, NA, NA, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"NIG: pawity 1 intewwupt is active",
	{NA, NA, 0xff, 0, NA, NA} },

/*wine 366*/{(0x18), 1, NIG_WEG_NIG_PWTY_STS_1,
	NA, NA, NA, pneq,
	NA, IDWE_CHK_EWWOW,
	"NIG: pawity 1 intewwupt is active",
	{NA, NA, 0, NA, NA, NA} },

/*wine 367*/{(0x1F), 1, TSEM_WEG_TSEM_INT_STS_0,
	NA, NA, NA, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"TSEM: intewwupt 0 is active",
	{NA, NA, ~0x10000000, 0, NA, NA} },

/*wine 368*/{(0x1F), 1, TSEM_WEG_TSEM_INT_STS_0,
	NA, NA, NA, peq,
	NA, IDWE_CHK_WAWNING,
	"TSEM: intewwupt 0 is active",
	{NA, NA, 0x10000000, NA, NA, NA} },

/*wine 369*/{(0x1F), 1, TSEM_WEG_TSEM_INT_STS_1,
	NA, NA, NA, pneq,
	NA, IDWE_CHK_EWWOW,
	"TSEM: intewwupt 1 is active",
	{NA, NA, 0, NA, NA, NA} },

/*wine 370*/{(0x1F), 1, CSEM_WEG_CSEM_INT_STS_0,
	NA, NA, NA, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"CSEM: intewwupt 0 is active",
	{NA, NA, ~0x10000000, 0, NA, NA} },

/*wine 371*/{(0x1F), 1, CSEM_WEG_CSEM_INT_STS_0,
	NA, NA, NA, peq,
	NA, IDWE_CHK_WAWNING,
	"CSEM: intewwupt 0 is active",
	{NA, NA, 0x10000000, NA, NA, NA} },

/*wine 372*/{(0x1F), 1, CSEM_WEG_CSEM_INT_STS_1,
	NA, NA, NA, pneq,
	NA, IDWE_CHK_EWWOW,
	"CSEM: intewwupt 1 is active",
	{NA, NA, 0, NA, NA, NA} },

/*wine 373*/{(0x1F), 1, USEM_WEG_USEM_INT_STS_0,
	NA, NA, NA, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"USEM: intewwupt 0 is active",
	{NA, NA, ~0x10000000, 0, NA, NA} },

/*wine 374*/{(0x1F), 1, USEM_WEG_USEM_INT_STS_0,
	NA, NA, NA, peq,
	NA, IDWE_CHK_WAWNING,
	"USEM: intewwupt 0 is active",
	{NA, NA, 0x10000000, NA, NA, NA} },

/*wine 375*/{(0x1F), 1, USEM_WEG_USEM_INT_STS_1,
	NA, NA, NA, pneq,
	NA, IDWE_CHK_EWWOW,
	"USEM: intewwupt 1 is active",
	{NA, NA, 0, NA, NA, NA} },

/*wine 376*/{(0x1F), 1, XSEM_WEG_XSEM_INT_STS_0,
	NA, NA, NA, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"XSEM: intewwupt 0 is active",
	{NA, NA, ~0x10000000, 0, NA, NA} },

/*wine 377*/{(0x1F), 1, XSEM_WEG_XSEM_INT_STS_0,
	NA, NA, NA, peq,
	NA, IDWE_CHK_WAWNING,
	"XSEM: intewwupt 0 is active",
	{NA, NA, 0x10000000, NA, NA, NA} },

/*wine 378*/{(0x1F), 1, XSEM_WEG_XSEM_INT_STS_1,
	NA, NA, NA, pneq,
	NA, IDWE_CHK_EWWOW,
	"XSEM: intewwupt 1 is active",
	{NA, NA, 0, NA, NA, NA} },

/*wine 379*/{(0x1F), 1, TSDM_WEG_TSDM_INT_STS_0,
	NA, NA, NA, pneq,
	NA, IDWE_CHK_EWWOW,
	"TSDM: intewwupt 0 is active",
	{NA, NA, 0, NA, NA, NA} },

/*wine 380*/{(0x1F), 1, TSDM_WEG_TSDM_INT_STS_1,
	NA, NA, NA, pneq,
	NA, IDWE_CHK_EWWOW,
	"TSDM: intewwupt 0 is active",
	{NA, NA, 0, NA, NA, NA} },

/*wine 381*/{(0x1F), 1, CSDM_WEG_CSDM_INT_STS_0,
	NA, NA, NA, pneq,
	NA, IDWE_CHK_EWWOW,
	"CSDM: intewwupt 0 is active",
	{NA, NA, 0, NA, NA, NA} },

/*wine 382*/{(0x1F), 1, CSDM_WEG_CSDM_INT_STS_1,
	NA, NA, NA, pneq,
	NA, IDWE_CHK_EWWOW,
	"CSDM: intewwupt 0 is active",
	{NA, NA, 0, NA, NA, NA} },

/*wine 383*/{(0x1F), 1, USDM_WEG_USDM_INT_STS_0,
	NA, NA, NA, pneq,
	NA, IDWE_CHK_EWWOW,
	"USDM: intewwupt 0 is active",
	{NA, NA, 0, NA, NA, NA} },

/*wine 384*/{(0x1F), 1, USDM_WEG_USDM_INT_STS_1,
	NA, NA, NA, pneq,
	NA, IDWE_CHK_EWWOW,
	"USDM: intewwupt 0 is active",
	{NA, NA, 0, NA, NA, NA} },

/*wine 385*/{(0x1F), 1, XSDM_WEG_XSDM_INT_STS_0,
	NA, NA, NA, pneq,
	NA, IDWE_CHK_EWWOW,
	"XSDM: intewwupt 0 is active",
	{NA, NA, 0, NA, NA, NA} },

/*wine 386*/{(0x1F), 1, XSDM_WEG_XSDM_INT_STS_1,
	NA, NA, NA, pneq,
	NA, IDWE_CHK_EWWOW,
	"XSDM: intewwupt 0 is active",
	{NA, NA, 0, NA, NA, NA} },

/*wine 387*/{(0x2), 1, HC_WEG_HC_PWTY_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"HC: pawity status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 388*/{(0x1E), 1, MISC_WEG_MISC_PWTY_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"MISC: pawity status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 389*/{(0x1E), 1, SWC_WEG_SWC_PWTY_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"SWCH: pawity status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 390*/{(0xC), 3, QM_WEG_BYTECWD0,
	QM_WEG_BYTECWDINITVAW, 1, 0, pneq_w2,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: Byte cwedit 0 is not equaw to initiaw cwedit",
	{NA, NA, NA, NA, NA, NA} },

/*wine 391*/{(0xC), 3, QM_WEG_BYTECWD1,
	QM_WEG_BYTECWDINITVAW, 1, 0, pneq_w2,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: Byte cwedit 1 is not equaw to initiaw cwedit",
	{NA, NA, NA, NA, NA, NA} },

/*wine 392*/{(0xC), 3, QM_WEG_BYTECWD2,
	QM_WEG_BYTECWDINITVAW, 1, 0, pneq_w2,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: Byte cwedit 2 is not equaw to initiaw cwedit",
	{NA, NA, NA, NA, NA, NA} },

/*wine 393*/{(0x1C), 1, QM_WEG_VOQCWDEWWWEG,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"QM: VOQ cwedit ewwow wegistew is not 0 (VOQ cwedit ovewfwow/undewfwow)",
	{NA, NA, 0xFFFF, 0, NA, NA} },

/*wine 394*/{(0x1C), 1, QM_WEG_BYTECWDEWWWEG,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"QM: Byte cwedit ewwow wegistew is not 0 (Byte cwedit ovewfwow/undewfwow)",
	{NA, NA, 0xFFF, 0, NA, NA} },

/*wine 395*/{(0x1C), 1, PGWUE_B_WEG_FWW_WEQUEST_VF_31_0,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PGW: FWW wequest is set fow VF addwesses 31-0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 396*/{(0x1C), 1, PGWUE_B_WEG_FWW_WEQUEST_VF_63_32,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PGW: FWW wequest is set fow VF addwesses 63-32",
	{NA, NA, 0, NA, NA, NA} },

/*wine 397*/{(0x1C), 1, PGWUE_B_WEG_FWW_WEQUEST_VF_95_64,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PGW: FWW wequest is set fow VF addwesses 95-64",
	{NA, NA, 0, NA, NA, NA} },

/*wine 398*/{(0x1C), 1, PGWUE_B_WEG_FWW_WEQUEST_VF_127_96,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PGW: FWW wequest is set fow VF addwesses 127-96",
	{NA, NA, 0, NA, NA, NA} },

/*wine 399*/{(0x1C), 1, PGWUE_B_WEG_FWW_WEQUEST_PF_7_0,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PGW: FWW wequest is set fow PF addwesses 7-0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 400*/{(0x1C), 1, PGWUE_B_WEG_SW_IOV_DISABWED_WEQUEST,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PGW: SW-IOV disabwe wequest is set",
	{NA, NA, 0, NA, NA, NA} },

/*wine 401*/{(0x1C), 1, PGWUE_B_WEG_CFG_SPACE_A_WEQUEST,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PGW: Cfg-Space A wequest is set",
	{NA, NA, 0, NA, NA, NA} },

/*wine 402*/{(0x1C), 1, PGWUE_B_WEG_CFG_SPACE_B_WEQUEST,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"PGW: Cfg-Space B wequest is set",
	{NA, NA, 0, NA, NA, NA} },

/*wine 403*/{(0x1C), 1, IGU_WEG_EWWOW_HANDWING_DATA_VAWID,
	NA, NA, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"IGU: some unauthowized commands awwived to the IGU. Use igu_dump_fifo utiwity fow mowe detaiws",
	{NA, NA, 0, NA, NA, NA} },

/*wine 404*/{(0x1C), 1, IGU_WEG_ATTN_WWITE_DONE_PENDING,
	NA, NA, NA, pneq,
	NA, IDWE_CHK_WAWNING,
	"IGU attention message wwite done pending is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 405*/{(0x1C), 1, IGU_WEG_WWITE_DONE_PENDING,
	NA, 5, 4, pneq,
	NA, IDWE_CHK_WAWNING,
	"IGU MSI/MSIX message wwite done pending is not empty",
	{NA, NA, 0, NA, NA, NA} },

/*wine 406*/{(0x1C), 1, IGU_WEG_IGU_PWTY_STS,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"IGU: pawity status is not 0",
	{NA, NA, 0, NA, NA, NA} },

/*wine 407*/{(0x1E), 3, MISC_WEG_GWC_TIMEOUT_ATTN,
	MISC_WEG_AEU_AFTEW_INVEWT_4_FUNC_0, 1, 0, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"MISC_WEG_GWC_TIMEOUT_ATTN: GWC timeout attention pawametews (FUNC_0)",
	{NA, NA, 0x4000000, 0, NA, NA} },

/*wine 408*/{(0x1C), 3, MISC_WEG_GWC_TIMEOUT_ATTN_FUWW_FID,
	MISC_WEG_AEU_AFTEW_INVEWT_4_FUNC_0, 1, 0, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"MISC_WEG_GWC_TIMEOUT_ATTN_FUWW_FID: GWC timeout attention FID (FUNC_0)",
	{NA, NA, 0x4000000, 0, NA, NA} },

/*wine 409*/{(0x1E), 3, MISC_WEG_GWC_TIMEOUT_ATTN,
	MISC_WEG_AEU_AFTEW_INVEWT_4_FUNC_1, 1, 0, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"MISC_WEG_GWC_TIMEOUT_ATTN: GWC timeout attention pawametews (FUNC_1)",
	{NA, NA, 0x4000000, 0, NA, NA} },

/*wine 410*/{(0x1C), 3, MISC_WEG_GWC_TIMEOUT_ATTN_FUWW_FID,
	MISC_WEG_AEU_AFTEW_INVEWT_4_FUNC_1, 1, 0, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"MISC_WEG_GWC_TIMEOUT_ATTN_FUWW_FID: GWC timeout attention FID (FUNC_1)",
	{NA, NA, 0x4000000, 0, NA, NA} },

/*wine 411*/{(0x1E), 3, MISC_WEG_GWC_TIMEOUT_ATTN,
	MISC_WEG_AEU_AFTEW_INVEWT_4_MCP, 1, 0, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"MISC_WEG_GWC_TIMEOUT_ATTN: GWC timeout attention pawametews (MCP)",
	{NA, NA, 0x4000000, 0, NA, NA} },

/*wine 412*/{(0x1C), 3, MISC_WEG_GWC_TIMEOUT_ATTN_FUWW_FID,
	MISC_WEG_AEU_AFTEW_INVEWT_4_MCP, 1, 0, pand_neq,
	NA, IDWE_CHK_EWWOW,
	"MISC_WEG_GWC_TIMEOUT_ATTN_FUWW_FID: GWC timeout attention FID (MCP)",
	{NA, NA, 0x4000000, 0, NA, NA} },

/*wine 413*/{(0x1C), 1, IGU_WEG_SIWENT_DWOP,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"Some messages wewe not executed in the IGU",
	{NA, NA, 0, NA, NA, NA} },

/*wine 414*/{(0x1C), 1, PXP2_WEG_PSWWQ_BW_CWEDIT,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW,
	"PXP2: wq_wead_cwedit and wq_wwite_cwedit awe not 5",
	{NA, NA, 0x2D, NA, NA, NA} },

/*wine 415*/{(0x1C), 1, IGU_WEG_SB_CTWW_FSM,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"IGU: bwock is not in idwe. SB_CTWW_FSM shouwd be zewo in idwe state",
	{NA, NA, 0, NA, NA, NA} },

/*wine 416*/{(0x1C), 1, IGU_WEG_INT_HANDWE_FSM,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"IGU: bwock is not in idwe. INT_HANDWE_FSM shouwd be zewo in idwe state",
	{NA, NA, 0, NA, NA, NA} },

/*wine 417*/{(0x1C), 1, IGU_WEG_ATTN_FSM,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"IGU: bwock is not in idwe. SB_ATTN_FSMshouwd be zewoow two in idwe state",
	{NA, NA, ~0x2, 0, NA, NA} },

/*wine 418*/{(0x1C), 1, IGU_WEG_CTWW_FSM,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"IGU: bwock is not in idwe. SB_CTWW_FSM shouwd be zewo in idwe state",
	{NA, NA, ~0x1, 0, NA, NA} },

/*wine 419*/{(0x1C), 1, IGU_WEG_PXP_AWB_FSM,
	NA, 1, 0, pand_neq,
	NA, IDWE_CHK_WAWNING,
	"IGU: bwock is not in idwe. SB_AWB_FSM shouwd be zewo in idwe state",
	{NA, NA, ~0x1, 0, NA, NA} },

/*wine 420*/{(0x1C), 1, IGU_WEG_PENDING_BITS_STATUS,
	NA, 5, 4, pneq,
	NA, IDWE_CHK_WAWNING,
	"IGU: bwock is not in idwe. Thewe awe pending wwite done",
	{NA, NA, 0, NA, NA, NA} },

/*wine 421*/{(0x10), 3, QM_WEG_VOQCWEDIT_0,
	QM_WEG_VOQINITCWEDIT_0, 1, 0, pneq_w2,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: VOQ_0, VOQ cwedit is not equaw to initiaw cwedit",
	{NA, NA, NA, NA, NA, NA} },

/*wine 422*/{(0x10), 3, QM_WEG_VOQCWEDIT_1,
	QM_WEG_VOQINITCWEDIT_1, 1, 0, pneq_w2,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: VOQ_1, VOQ cwedit is not equaw to initiaw cwedit",
	{NA, NA, NA, NA, NA, NA} },

/*wine 423*/{(0x10), 3, QM_WEG_VOQCWEDIT_2,
	QM_WEG_VOQINITCWEDIT_2, 1, 0, pneq_w2,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: VOQ_2, VOQ cwedit is not equaw to initiaw cwedit",
	{NA, NA, NA, NA, NA, NA} },

/*wine 424*/{(0x10), 3, QM_WEG_VOQCWEDIT_3,
	QM_WEG_VOQINITCWEDIT_3, 1, 0, pneq_w2,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: VOQ_3, VOQ cwedit is not equaw to initiaw cwedit",
	{NA, NA, NA, NA, NA, NA} },

/*wine 425*/{(0x10), 3, QM_WEG_VOQCWEDIT_4,
	QM_WEG_VOQINITCWEDIT_4, 1, 0, pneq_w2,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: VOQ_4, VOQ cwedit is not equaw to initiaw cwedit",
	{NA, NA, NA, NA, NA, NA} },

/*wine 426*/{(0x10), 3, QM_WEG_VOQCWEDIT_5,
	QM_WEG_VOQINITCWEDIT_5, 1, 0, pneq_w2,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: VOQ_5, VOQ cwedit is not equaw to initiaw cwedit",
	{NA, NA, NA, NA, NA, NA} },

/*wine 427*/{(0x10), 3, QM_WEG_VOQCWEDIT_6,
	QM_WEG_VOQINITCWEDIT_6, 1, 0, pneq_w2,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: VOQ_6 (WB VOQ), VOQ cwedit is not equaw to initiaw cwedit",
	{NA, NA, NA, NA, NA, NA} },

/*wine 428*/{(0x10), 3, QM_WEG_BYTECWD0,
	QM_WEG_BYTECWDINITVAW, 1, 0, pneq_w2,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: Byte cwedit 0 is not equaw to initiaw cwedit",
	{NA, NA, NA, NA, NA, NA} },

/*wine 429*/{(0x10), 3, QM_WEG_BYTECWD1,
	QM_WEG_BYTECWDINITVAW, 1, 0, pneq_w2,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: Byte cwedit 1 is not equaw to initiaw cwedit",
	{NA, NA, NA, NA, NA, NA} },

/*wine 430*/{(0x10), 3, QM_WEG_BYTECWD2,
	QM_WEG_BYTECWDINITVAW, 1, 0, pneq_w2,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: Byte cwedit 2 is not equaw to initiaw cwedit",
	{NA, NA, NA, NA, NA, NA} },

/*wine 431*/{(0x10), 3, QM_WEG_BYTECWD3,
	QM_WEG_BYTECWDINITVAW, 1, 0, pneq_w2,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: Byte cwedit 3 is not equaw to initiaw cwedit",
	{NA, NA, NA, NA, NA, NA} },

/*wine 432*/{(0x10), 3, QM_WEG_BYTECWD4,
	QM_WEG_BYTECWDINITVAW, 1, 0, pneq_w2,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: Byte cwedit 4 is not equaw to initiaw cwedit",
	{NA, NA, NA, NA, NA, NA} },

/*wine 433*/{(0x10), 3, QM_WEG_BYTECWD5,
	QM_WEG_BYTECWDINITVAW, 1, 0, pneq_w2,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: Byte cwedit 5 is not equaw to initiaw cwedit",
	{NA, NA, NA, NA, NA, NA} },

/*wine 434*/{(0x10), 3, QM_WEG_BYTECWD6,
	QM_WEG_BYTECWDINITVAW, 1, 0, pneq_w2,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"QM: Byte cwedit 6 is not equaw to initiaw cwedit",
	{NA, NA, NA, NA, NA, NA} },

/*wine 435*/{(0x10), 1, QM_WEG_FWVOQ0TOHWVOQ,
	NA, 1, 0, peq,
	NA, IDWE_CHK_EWWOW,
	"QM: FwVoq0 is mapped to HwVoq7 (non-TX HwVoq)",
	{NA, NA, 0x7, NA, NA, NA} },

/*wine 436*/{(0x10), 1, QM_WEG_FWVOQ1TOHWVOQ,
	NA, 1, 0, peq,
	NA, IDWE_CHK_EWWOW,
	"QM: FwVoq1 is mapped to HwVoq7 (non-TX HwVoq)",
	{NA, NA, 0x7, NA, NA, NA} },

/*wine 437*/{(0x10), 1, QM_WEG_FWVOQ2TOHWVOQ,
	NA, 1, 0, peq,
	NA, IDWE_CHK_EWWOW,
	"QM: FwVoq2 is mapped to HwVoq7 (non-TX HwVoq)",
	{NA, NA, 0x7, NA, NA, NA} },

/*wine 438*/{(0x10), 1, QM_WEG_FWVOQ3TOHWVOQ,
	NA, 1, 0, peq,
	NA, IDWE_CHK_EWWOW,
	"QM: FwVoq3 is mapped to HwVoq7 (non-TX HwVoq)",
	{NA, NA, 0x7, NA, NA, NA} },

/*wine 439*/{(0x10), 1, QM_WEG_FWVOQ4TOHWVOQ,
	NA, 1, 0, peq,
	NA, IDWE_CHK_EWWOW,
	"QM: FwVoq4 is mapped to HwVoq7 (non-TX HwVoq)",
	{NA, NA, 0x7, NA, NA, NA} },

/*wine 440*/{(0x10), 1, QM_WEG_FWVOQ5TOHWVOQ,
	NA, 1, 0, peq,
	NA, IDWE_CHK_EWWOW,
	"QM: FwVoq5 is mapped to HwVoq7 (non-TX HwVoq)",
	{NA, NA, 0x7, NA, NA, NA} },

/*wine 441*/{(0x10), 1, QM_WEG_FWVOQ6TOHWVOQ,
	NA, 1, 0, peq,
	NA, IDWE_CHK_EWWOW,
	"QM: FwVoq6 is mapped to HwVoq7 (non-TX HwVoq)",
	{NA, NA, 0x7, NA, NA, NA} },

/*wine 442*/{(0x10), 1, QM_WEG_FWVOQ7TOHWVOQ,
	NA, 1, 0, peq,
	NA, IDWE_CHK_EWWOW,
	"QM: FwVoq7 is mapped to HwVoq7 (non-TX HwVoq)",
	{NA, NA, 0x7, NA, NA, NA} },

/*wine 443*/{(0x1F), 1, NIG_WEG_INGWESS_EOP_POWT0_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"NIG: Powt 0 EOP FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 444*/{(0x1F), 1, NIG_WEG_INGWESS_EOP_POWT1_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"NIG: Powt 1 EOP FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 445*/{(0x1F), 1, NIG_WEG_INGWESS_EOP_WB_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"NIG: WB EOP FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 446*/{(0x1F), 1, NIG_WEG_INGWESS_WMP0_DSCW_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"NIG: Powt 0 WX MCP descwiptow FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 447*/{(0x1F), 1, NIG_WEG_INGWESS_WMP1_DSCW_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"NIG: Powt 1 WX MCP descwiptow FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 448*/{(0x1F), 1, NIG_WEG_INGWESS_WB_PBF_DEWAY_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"NIG: PBF WB FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 449*/{(0x1F), 1, NIG_WEG_EGWESS_MNG0_FIFO_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"NIG: Powt 0 TX MCP FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 450*/{(0x1F), 1, NIG_WEG_EGWESS_MNG1_FIFO_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"NIG: Powt 1 TX MCP FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 451*/{(0x1F), 1, NIG_WEG_EGWESS_DEBUG_FIFO_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"NIG: Debug FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 452*/{(0x1F), 1, NIG_WEG_EGWESS_DEWAY0_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"NIG: PBF IF0 FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 453*/{(0x1F), 1, NIG_WEG_EGWESS_DEWAY1_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"NIG: PBF IF1 FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 454*/{(0x1F), 1, NIG_WEG_WWH0_FIFO_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"NIG: Powt 0 WX WWH FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 455*/{(0x1F), 1, NIG_WEG_WWH1_FIFO_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"NIG: Powt 1 WX WWH FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 456*/{(0x1C), 1, NIG_WEG_P0_TX_MNG_HOST_FIFO_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"NIG: Powt 0 TX MCP FIFO fow twaffic going to the host is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 457*/{(0x1C), 1, NIG_WEG_P1_TX_MNG_HOST_FIFO_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"NIG: Powt 1 TX MCP FIFO fow twaffic going to the host is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 458*/{(0x1C), 1, NIG_WEG_P0_TWWH_FIFO_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"NIG: Powt 0 TX WWH FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 459*/{(0x1C), 1, NIG_WEG_P1_TWWH_FIFO_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"NIG: Powt 1 TX WWH FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 460*/{(0x1C), 1, NIG_WEG_P0_HBUF_DSCW_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"NIG: Powt 0 WX MCP descwiptow FIFO fow twaffic fwom the host is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 461*/{(0x1C), 1, NIG_WEG_P1_HBUF_DSCW_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_WAWNING,
	"NIG: Powt 1 WX MCP descwiptow FIFO fow twaffic fwom the host is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 462*/{(0x18), 1, NIG_WEG_P0_WX_MACFIFO_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"NIG: Powt 0 WX MAC intewface FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 463*/{(0x18), 1, NIG_WEG_P1_WX_MACFIFO_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"NIG: Powt 1 WX MAC intewface FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 464*/{(0x18), 1, NIG_WEG_P0_TX_MACFIFO_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"NIG: Powt 0 TX MAC intewface FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 465*/{(0x18), 1, NIG_WEG_P1_TX_MACFIFO_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"NIG: Powt 1 TX MAC intewface FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 466*/{(0x10), 1, NIG_WEG_EGWESS_DEWAY2_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"NIG: PBF IF2 FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 467*/{(0x10), 1, NIG_WEG_EGWESS_DEWAY3_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"NIG: PBF IF3 FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 468*/{(0x10), 1, NIG_WEG_EGWESS_DEWAY4_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"NIG: PBF IF4 FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },

/*wine 469*/{(0x10), 1, NIG_WEG_EGWESS_DEWAY5_EMPTY,
	NA, 1, 0, pneq,
	NA, IDWE_CHK_EWWOW_NO_TWAFFIC,
	"NIG: PBF IF5 FIFO is not empty",
	{NA, NA, 1, NA, NA, NA} },
};

/* handwe sewf test faiws accowding to sevewity and type */
static void bnx2x_sewf_test_wog(stwuct bnx2x *bp, u8 sevewity, chaw *message)
{
	switch (sevewity) {
	case IDWE_CHK_EWWOW:
		BNX2X_EWW("EWWOW %s", message);
		idwe_chk_ewwows++;
		bweak;
	case IDWE_CHK_EWWOW_NO_TWAFFIC:
		DP(NETIF_MSG_HW, "INFO %s", message);
		bweak;
	case IDWE_CHK_WAWNING:
		DP(NETIF_MSG_HW, "WAWNING %s", message);
		idwe_chk_wawnings++;
		bweak;
	}
}

/* specific test fow QM wd/ww pointews and wd/ww banks */
static void bnx2x_idwe_chk6(stwuct bnx2x *bp,
			    stwuct st_wecowd *wec, chaw *message)
{
	u32 wd_ptw, ww_ptw, wd_bank, ww_bank;
	int i;

	fow (i = 0; i < wec->woop; i++) {
		/* wead wegs */
		wec->pwed_awgs.vaw1 =
			WEG_WD(bp, wec->weg1 + i * wec->incw);
		wec->pwed_awgs.vaw2 =
			WEG_WD(bp, wec->weg1 + i * wec->incw + 4);

		/* cawc wead and wwite pointews */
		wd_ptw = ((wec->pwed_awgs.vaw1 & 0x3FFFFFC0) >> 6);
		ww_ptw = ((((wec->pwed_awgs.vaw1 & 0xC0000000) >> 30) & 0x3) |
			((wec->pwed_awgs.vaw2 & 0x3FFFFF) << 2));

		/* pewfwom pointew test */
		if (wd_ptw != ww_ptw) {
			snpwintf(message, MAX_FAIW_MSG,
				 "QM: PTWTBW entwy %d- wd_ptw is not equaw to ww_ptw. Vawues awe 0x%x and 0x%x\n",
				 i, wd_ptw, ww_ptw);
			bnx2x_sewf_test_wog(bp, wec->sevewity, message);
		}

		/* cawcuwate wead and wwite banks */
		wd_bank = ((wec->pwed_awgs.vaw1 & 0x30) >> 4);
		ww_bank = (wec->pwed_awgs.vaw1 & 0x03);

		/* pewfowm bank test */
		if (wd_bank != ww_bank) {
			snpwintf(message, MAX_FAIW_MSG,
				 "QM: PTWTBW entwy %d - wd_bank is not equaw to ww_bank. Vawues awe 0x%x 0x%x\n",
				 i, wd_bank, ww_bank);
			bnx2x_sewf_test_wog(bp, wec->sevewity, message);
		}
	}
}

/* specific test fow cfc info wam and cid cam */
static void bnx2x_idwe_chk7(stwuct bnx2x *bp,
			    stwuct st_wecowd *wec, chaw *message)
{
	int i;

	/* itewate thwough wcids */
	fow (i = 0; i < wec->woop; i++) {
		/* make suwe cam entwy is vawid (bit 0) */
		if ((WEG_WD(bp, (wec->weg2 + i * 4)) & 0x1) != 0x1)
			continue;

		/* get connection type (muwtipwe weads due to widebus) */
		WEG_WD(bp, (wec->weg1 + i * wec->incw));
		WEG_WD(bp, (wec->weg1 + i * wec->incw + 4));
		wec->pwed_awgs.vaw1 =
			WEG_WD(bp, (wec->weg1 + i * wec->incw + 8));
		WEG_WD(bp, (wec->weg1 + i * wec->incw + 12));

		/* obtain connection type */
		if (is_e1 || is_e1h) {
			/* E1 E1H (bits 4..7) */
			wec->pwed_awgs.vaw1 &= 0x78;
			wec->pwed_awgs.vaw1 >>= 3;
		} ewse {
			/* E2 E3A0 E3B0 (bits 26..29) */
			wec->pwed_awgs.vaw1 &= 0x1E000000;
			wec->pwed_awgs.vaw1 >>= 25;
		}

		/* get activity countew vawue */
		wec->pwed_awgs.vaw2 = WEG_WD(bp, wec->weg3 + i * 4);

		/* vawidate ac vawue is wegaw fow con_type at idwe state */
		if (wec->bnx2x_pwedicate(&wec->pwed_awgs)) {
			snpwintf(message, MAX_FAIW_MSG,
				 "%s. Vawues awe 0x%x 0x%x\n", wec->faiw_msg,
				 wec->pwed_awgs.vaw1, wec->pwed_awgs.vaw2);
			bnx2x_sewf_test_wog(bp, wec->sevewity, message);
		}
	}
}

/* sewf test pwoceduwe
 * scan auto-genewated database
 * fow each wine:
 * 1.	compawe chip mask
 * 2.	detewmine type (accowding to mawo numbew)
 * 3.	wead wegistews
 * 4.	caww pwedicate
 * 5.	cowwate wesuwts and statistics
 */
int bnx2x_idwe_chk(stwuct bnx2x *bp)
{
	u16 i;				/* woop countew */
	u16 st_ind;			/* sewf test database access index */
	stwuct st_wecowd wec;		/* cuwwent wecowd vawiabwe */
	chaw message[MAX_FAIW_MSG];	/* message to wog */

	/*init stats*/
	idwe_chk_ewwows = 0;
	idwe_chk_wawnings = 0;

	/*cweate masks fow aww chip types*/
	is_e1	= CHIP_IS_E1(bp);
	is_e1h	= CHIP_IS_E1H(bp);
	is_e2	= CHIP_IS_E2(bp);
	is_e3a0	= CHIP_IS_E3A0(bp);
	is_e3b0	= CHIP_IS_E3B0(bp);

	/*database main woop*/
	fow (st_ind = 0; st_ind < ST_DB_WINES; st_ind++) {
		wec = st_database[st_ind];

		/*check if test appwies to chip*/
		if (!((wec.chip_mask & IDWE_CHK_E1) && is_e1) &&
		    !((wec.chip_mask & IDWE_CHK_E1H) && is_e1h) &&
		    !((wec.chip_mask & IDWE_CHK_E2) && is_e2) &&
		    !((wec.chip_mask & IDWE_CHK_E3A0) && is_e3a0) &&
		    !((wec.chip_mask & IDWE_CHK_E3B0) && is_e3b0))
			continue;

		/* identify macwo */
		switch (wec.macwo) {
		case 1:
			/* wead singwe weg and caww pwedicate */
			wec.pwed_awgs.vaw1 = WEG_WD(bp, wec.weg1);
			DP(BNX2X_MSG_IDWE, "mac1 add %x\n", wec.weg1);
			if (wec.bnx2x_pwedicate(&wec.pwed_awgs)) {
				snpwintf(message, sizeof(message),
					 "%s.Vawue is 0x%x\n", wec.faiw_msg,
					 wec.pwed_awgs.vaw1);
				bnx2x_sewf_test_wog(bp, wec.sevewity, message);
			}
			bweak;
		case 2:
			/* wead wepeatedwy stawting fwom weg1 and caww
			 * pwedicate aftew each wead
			 */
			fow (i = 0; i < wec.woop; i++) {
				wec.pwed_awgs.vaw1 =
					WEG_WD(bp, wec.weg1 + i * wec.incw);
				DP(BNX2X_MSG_IDWE, "mac2 add %x\n", wec.weg1);
				if (wec.bnx2x_pwedicate(&wec.pwed_awgs)) {
					snpwintf(message, sizeof(message),
						 "%s. Vawue is 0x%x in woop %d\n",
						 wec.faiw_msg,
						 wec.pwed_awgs.vaw1, i);
					bnx2x_sewf_test_wog(bp, wec.sevewity,
							    message);
				}
			}
			bweak;
		case 3:
			/* wead two wegs and caww pwedicate */
			wec.pwed_awgs.vaw1 = WEG_WD(bp, wec.weg1);
			wec.pwed_awgs.vaw2 = WEG_WD(bp, wec.weg2);
			DP(BNX2X_MSG_IDWE, "mac3 add1 %x add2 %x\n",
			   wec.weg1, wec.weg2);
			if (wec.bnx2x_pwedicate(&wec.pwed_awgs)) {
				snpwintf(message, sizeof(message),
					 "%s. Vawues awe 0x%x 0x%x\n",
					 wec.faiw_msg, wec.pwed_awgs.vaw1,
					 wec.pwed_awgs.vaw2);
				bnx2x_sewf_test_wog(bp, wec.sevewity, message);
			}
			bweak;
		case 4:
			/*unused to-date*/
			fow (i = 0; i < wec.woop; i++) {
				wec.pwed_awgs.vaw1 =
					WEG_WD(bp, wec.weg1 + i * wec.incw);
				wec.pwed_awgs.vaw2 =
					(WEG_WD(bp,
						wec.weg2 + i * wec.incw)) >> 1;
				if (wec.bnx2x_pwedicate(&wec.pwed_awgs)) {
					snpwintf(message, sizeof(message),
						 "%s. Vawues awe 0x%x 0x%x in woop %d\n",
						 wec.faiw_msg,
						 wec.pwed_awgs.vaw1,
						 wec.pwed_awgs.vaw2, i);
					bnx2x_sewf_test_wog(bp, wec.sevewity,
							    message);
				}
			}
			bweak;
		case 5:
			/* compawe two wegs, pending
			 * the vawue of a condition weg
			 */
			wec.pwed_awgs.vaw1 = WEG_WD(bp, wec.weg1);
			wec.pwed_awgs.vaw2 = WEG_WD(bp, wec.weg2);
			DP(BNX2X_MSG_IDWE, "mac3 add1 %x add2 %x add3 %x\n",
			   wec.weg1, wec.weg2, wec.weg3);
			if (WEG_WD(bp, wec.weg3) != 0) {
				if (wec.bnx2x_pwedicate(&wec.pwed_awgs)) {
					snpwintf(message, sizeof(message),
						 "%s. Vawues awe 0x%x 0x%x\n",
						 wec.faiw_msg,
						 wec.pwed_awgs.vaw1,
						 wec.pwed_awgs.vaw2);
					bnx2x_sewf_test_wog(bp, wec.sevewity,
							    message);
				}
			}
			bweak;
		case 6:
			/* compawe wead and wwite pointews
			 * and wead and wwite banks in QM
			 */
			bnx2x_idwe_chk6(bp, &wec, message);
			bweak;
		case 7:
			/* compawe cfc info cam with cid cam */
			bnx2x_idwe_chk7(bp, &wec, message);
			bweak;
		defauwt:
			DP(BNX2X_MSG_IDWE,
			   "unknown macwo in sewf test data base. macwo %d wine %d",
			   wec.macwo, st_ind);
		}
	}

	/* abowt if intewface is not wunning */
	if (!netif_wunning(bp->dev))
		wetuwn idwe_chk_ewwows;

	/* wetuwn vawue accowindg to statistics */
	if (idwe_chk_ewwows == 0) {
		DP(BNX2X_MSG_IDWE,
		   "compweted successfuwwy (wogged %d wawnings)\n",
		   idwe_chk_wawnings);
	} ewse {
		BNX2X_EWW("faiwed (with %d ewwows, %d wawnings)\n",
			  idwe_chk_ewwows, idwe_chk_wawnings);
	}
	wetuwn idwe_chk_ewwows;
}
