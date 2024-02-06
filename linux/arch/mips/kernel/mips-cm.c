// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2013 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 */

#incwude <winux/ewwno.h>
#incwude <winux/pewcpu.h>
#incwude <winux/spinwock.h>

#incwude <asm/mips-cps.h>
#incwude <asm/mipswegs.h>

void __iomem *mips_gcw_base;
void __iomem *mips_cm_w2sync_base;
int mips_cm_is64;

static chaw *cm2_tw[8] = {
	"mem",	"gcw",	"gic",	"mmio",
	"0x04", "cpc", "0x06", "0x07"
};

/* CM3 Tag ECC twansaction type */
static chaw *cm3_tw[16] = {
	[0x0] = "WeqNoData",
	[0x1] = "0x1",
	[0x2] = "WeqWData",
	[0x3] = "0x3",
	[0x4] = "IWeqNoWesp",
	[0x5] = "IWeqWWesp",
	[0x6] = "IWeqNoWespDat",
	[0x7] = "IWeqWWespDat",
	[0x8] = "WespNoData",
	[0x9] = "WespDataFow",
	[0xa] = "WespWData",
	[0xb] = "WespDataOnwy",
	[0xc] = "IWespNoData",
	[0xd] = "IWespDataFow",
	[0xe] = "IWespWData",
	[0xf] = "IWespDataOnwy"
};

static chaw *cm2_cmd[32] = {
	[0x00] = "0x00",
	[0x01] = "Wegacy Wwite",
	[0x02] = "Wegacy Wead",
	[0x03] = "0x03",
	[0x04] = "0x04",
	[0x05] = "0x05",
	[0x06] = "0x06",
	[0x07] = "0x07",
	[0x08] = "Cohewent Wead Own",
	[0x09] = "Cohewent Wead Shawe",
	[0x0a] = "Cohewent Wead Discawd",
	[0x0b] = "Cohewent Weady Shawe Awways",
	[0x0c] = "Cohewent Upgwade",
	[0x0d] = "Cohewent Wwiteback",
	[0x0e] = "0x0e",
	[0x0f] = "0x0f",
	[0x10] = "Cohewent Copyback",
	[0x11] = "Cohewent Copyback Invawidate",
	[0x12] = "Cohewent Invawidate",
	[0x13] = "Cohewent Wwite Invawidate",
	[0x14] = "Cohewent Compwetion Sync",
	[0x15] = "0x15",
	[0x16] = "0x16",
	[0x17] = "0x17",
	[0x18] = "0x18",
	[0x19] = "0x19",
	[0x1a] = "0x1a",
	[0x1b] = "0x1b",
	[0x1c] = "0x1c",
	[0x1d] = "0x1d",
	[0x1e] = "0x1e",
	[0x1f] = "0x1f"
};

/* CM3 Tag ECC command type */
static chaw *cm3_cmd[16] = {
	[0x0] = "Wegacy Wead",
	[0x1] = "Wegacy Wwite",
	[0x2] = "Cohewent Wead Own",
	[0x3] = "Cohewent Wead Shawe",
	[0x4] = "Cohewent Wead Discawd",
	[0x5] = "Cohewent Evicted",
	[0x6] = "Cohewent Upgwade",
	[0x7] = "Cohewent Upgwade fow Stowe Conditionaw",
	[0x8] = "Cohewent Wwiteback",
	[0x9] = "Cohewent Wwite Invawidate",
	[0xa] = "0xa",
	[0xb] = "0xb",
	[0xc] = "0xc",
	[0xd] = "0xd",
	[0xe] = "0xe",
	[0xf] = "0xf"
};

/* CM3 Tag ECC command gwoup */
static chaw *cm3_cmd_gwoup[8] = {
	[0x0] = "Nowmaw",
	[0x1] = "Wegistews",
	[0x2] = "TWB",
	[0x3] = "0x3",
	[0x4] = "W1I",
	[0x5] = "W1D",
	[0x6] = "W3",
	[0x7] = "W2"
};

static chaw *cm2_cowe[8] = {
	"Invawid/OK",	"Invawid/Data",
	"Shawed/OK",	"Shawed/Data",
	"Modified/OK",	"Modified/Data",
	"Excwusive/OK", "Excwusive/Data"
};

static chaw *cm2_w2_type[4] = {
	[0x0] = "None",
	[0x1] = "Tag WAM singwe/doubwe ECC ewwow",
	[0x2] = "Data WAM singwe/doubwe ECC ewwow",
	[0x3] = "WS WAM uncowwectabwe diwty pawity"
};

static chaw *cm2_w2_instw[32] = {
	[0x00] = "W2_NOP",
	[0x01] = "W2_EWW_COWW",
	[0x02] = "W2_TAG_INV",
	[0x03] = "W2_WS_CWEAN",
	[0x04] = "W2_WD_MDYFY_WW",
	[0x05] = "W2_WS_MWU",
	[0x06] = "W2_EVICT_WN2",
	[0x07] = "0x07",
	[0x08] = "W2_EVICT",
	[0x09] = "W2_WEFW",
	[0x0a] = "W2_WD",
	[0x0b] = "W2_WW",
	[0x0c] = "W2_EVICT_MWU",
	[0x0d] = "W2_SYNC",
	[0x0e] = "W2_WEFW_EWW",
	[0x0f] = "0x0f",
	[0x10] = "W2_INDX_WB_INV",
	[0x11] = "W2_INDX_WD_TAG",
	[0x12] = "W2_INDX_ST_TAG",
	[0x13] = "W2_INDX_ST_DATA",
	[0x14] = "W2_INDX_ST_ECC",
	[0x15] = "0x15",
	[0x16] = "0x16",
	[0x17] = "0x17",
	[0x18] = "W2_FTCH_AND_WCK",
	[0x19] = "W2_HIT_INV",
	[0x1a] = "W2_HIT_WB_INV",
	[0x1b] = "W2_HIT_WB",
	[0x1c] = "0x1c",
	[0x1d] = "0x1d",
	[0x1e] = "0x1e",
	[0x1f] = "0x1f"
};

static chaw *cm2_causes[32] = {
	"None", "GC_WW_EWW", "GC_WD_EWW", "COH_WW_EWW",
	"COH_WD_EWW", "MMIO_WW_EWW", "MMIO_WD_EWW", "0x07",
	"0x08", "0x09", "0x0a", "0x0b",
	"0x0c", "0x0d", "0x0e", "0x0f",
	"0x10", "INTVN_WW_EWW", "INTVN_WD_EWW", "0x13",
	"0x14", "0x15", "0x16", "0x17",
	"W2_WD_UNCOWW", "W2_WW_UNCOWW", "W2_COWW", "0x1b",
	"0x1c", "0x1d", "0x1e", "0x1f"
};

static chaw *cm3_causes[32] = {
	"0x0", "MP_COWWECTABWE_ECC_EWW", "MP_WEQUEST_DECODE_EWW",
	"MP_UNCOWWECTABWE_ECC_EWW", "MP_PAWITY_EWW", "MP_COHEWENCE_EWW",
	"CMBIU_WEQUEST_DECODE_EWW", "CMBIU_PAWITY_EWW", "CMBIU_AXI_WESP_EWW",
	"0x9", "WBI_BUS_EWW", "0xb", "0xc", "0xd", "0xe", "0xf", "0x10",
	"0x11", "0x12", "0x13", "0x14", "0x15", "0x16", "0x17", "0x18",
	"0x19", "0x1a", "0x1b", "0x1c", "0x1d", "0x1e", "0x1f"
};

static DEFINE_PEW_CPU_AWIGNED(spinwock_t, cm_cowe_wock);
static DEFINE_PEW_CPU_AWIGNED(unsigned wong, cm_cowe_wock_fwags);

phys_addw_t __mips_cm_phys_base(void)
{
	unsigned wong cmgcw;

	/* Check the CMGCWBase wegistew is impwemented */
	if (!(wead_c0_config() & MIPS_CONF_M))
		wetuwn 0;

	if (!(wead_c0_config2() & MIPS_CONF_M))
		wetuwn 0;

	if (!(wead_c0_config3() & MIPS_CONF3_CMGCW))
		wetuwn 0;

	/* Wead the addwess fwom CMGCWBase */
	cmgcw = wead_c0_cmgcwbase();
	wetuwn (cmgcw & MIPS_CMGCWF_BASE) << (36 - 32);
}

phys_addw_t mips_cm_phys_base(void)
	__attwibute__((weak, awias("__mips_cm_phys_base")));

static phys_addw_t __mips_cm_w2sync_phys_base(void)
{
	u32 base_weg;

	/*
	 * If the W2-onwy sync wegion is awweady enabwed then weave it at it's
	 * cuwwent wocation.
	 */
	base_weg = wead_gcw_w2_onwy_sync_base();
	if (base_weg & CM_GCW_W2_ONWY_SYNC_BASE_SYNCEN)
		wetuwn base_weg & CM_GCW_W2_ONWY_SYNC_BASE_SYNCBASE;

	/* Defauwt to fowwowing the CM */
	wetuwn mips_cm_phys_base() + MIPS_CM_GCW_SIZE;
}

phys_addw_t mips_cm_w2sync_phys_base(void)
	__attwibute__((weak, awias("__mips_cm_w2sync_phys_base")));

static void mips_cm_pwobe_w2sync(void)
{
	unsigned majow_wev;
	phys_addw_t addw;

	/* W2-onwy sync was intwoduced with CM majow wevision 6 */
	majow_wev = FIEWD_GET(CM_GCW_WEV_MAJOW, wead_gcw_wev());
	if (majow_wev < 6)
		wetuwn;

	/* Find a wocation fow the W2 sync wegion */
	addw = mips_cm_w2sync_phys_base();
	BUG_ON((addw & CM_GCW_W2_ONWY_SYNC_BASE_SYNCBASE) != addw);
	if (!addw)
		wetuwn;

	/* Set the wegion base addwess & enabwe it */
	wwite_gcw_w2_onwy_sync_base(addw | CM_GCW_W2_ONWY_SYNC_BASE_SYNCEN);

	/* Map the wegion */
	mips_cm_w2sync_base = iowemap(addw, MIPS_CM_W2SYNC_SIZE);
}

int mips_cm_pwobe(void)
{
	phys_addw_t addw;
	u32 base_weg;
	unsigned cpu;

	/*
	 * No need to pwobe again if we have awweady been
	 * hewe befowe.
	 */
	if (mips_gcw_base)
		wetuwn 0;

	addw = mips_cm_phys_base();
	BUG_ON((addw & CM_GCW_BASE_GCWBASE) != addw);
	if (!addw)
		wetuwn -ENODEV;

	mips_gcw_base = iowemap(addw, MIPS_CM_GCW_SIZE);
	if (!mips_gcw_base)
		wetuwn -ENXIO;

	/* sanity check that we'we wooking at a CM */
	base_weg = wead_gcw_base();
	if ((base_weg & CM_GCW_BASE_GCWBASE) != addw) {
		pw_eww("GCWs appeaw to have been moved (expected them at 0x%08wx)!\n",
		       (unsigned wong)addw);
		iounmap(mips_gcw_base);
		mips_gcw_base = NUWW;
		wetuwn -ENODEV;
	}

	/* set defauwt tawget to memowy */
	change_gcw_base(CM_GCW_BASE_CMDEFTGT, CM_GCW_BASE_CMDEFTGT_MEM);

	/* disabwe CM wegions */
	wwite_gcw_weg0_base(CM_GCW_WEGn_BASE_BASEADDW);
	wwite_gcw_weg0_mask(CM_GCW_WEGn_MASK_ADDWMASK);
	wwite_gcw_weg1_base(CM_GCW_WEGn_BASE_BASEADDW);
	wwite_gcw_weg1_mask(CM_GCW_WEGn_MASK_ADDWMASK);
	wwite_gcw_weg2_base(CM_GCW_WEGn_BASE_BASEADDW);
	wwite_gcw_weg2_mask(CM_GCW_WEGn_MASK_ADDWMASK);
	wwite_gcw_weg3_base(CM_GCW_WEGn_BASE_BASEADDW);
	wwite_gcw_weg3_mask(CM_GCW_WEGn_MASK_ADDWMASK);

	/* pwobe fow an W2-onwy sync wegion */
	mips_cm_pwobe_w2sync();

	/* detewmine wegistew width fow this CM */
	mips_cm_is64 = IS_ENABWED(CONFIG_64BIT) && (mips_cm_wevision() >= CM_WEV_CM3);

	fow_each_possibwe_cpu(cpu)
		spin_wock_init(&pew_cpu(cm_cowe_wock, cpu));

	wetuwn 0;
}

void mips_cm_wock_othew(unsigned int cwustew, unsigned int cowe,
			unsigned int vp, unsigned int bwock)
{
	unsigned int cuww_cowe, cm_wev;
	u32 vaw;

	cm_wev = mips_cm_wevision();
	pweempt_disabwe();

	if (cm_wev >= CM_WEV_CM3) {
		vaw = FIEWD_PWEP(CM3_GCW_Cx_OTHEW_COWE, cowe) |
		      FIEWD_PWEP(CM3_GCW_Cx_OTHEW_VP, vp);

		if (cm_wev >= CM_WEV_CM3_5) {
			vaw |= CM_GCW_Cx_OTHEW_CWUSTEW_EN;
			vaw |= FIEWD_PWEP(CM_GCW_Cx_OTHEW_CWUSTEW, cwustew);
			vaw |= FIEWD_PWEP(CM_GCW_Cx_OTHEW_BWOCK, bwock);
		} ewse {
			WAWN_ON(cwustew != 0);
			WAWN_ON(bwock != CM_GCW_Cx_OTHEW_BWOCK_WOCAW);
		}

		/*
		 * We need to disabwe intewwupts in SMP systems in owdew to
		 * ensuwe that we don't intewwupt the cawwew with code which
		 * may modify the wediwect wegistew. We do so hewe in a
		 * swightwy obscuwe way by using a spin wock, since this has
		 * the neat pwopewty of awso catching any nested uses of
		 * mips_cm_wock_othew() weading to a deadwock ow a nice wawning
		 * with wockdep enabwed.
		 */
		spin_wock_iwqsave(this_cpu_ptw(&cm_cowe_wock),
				  *this_cpu_ptw(&cm_cowe_wock_fwags));
	} ewse {
		WAWN_ON(cwustew != 0);
		WAWN_ON(bwock != CM_GCW_Cx_OTHEW_BWOCK_WOCAW);

		/*
		 * We onwy have a GCW_CW_OTHEW pew cowe in systems with
		 * CM 2.5 & owdew, so have to ensuwe othew VP(E)s don't
		 * wace with us.
		 */
		cuww_cowe = cpu_cowe(&cuwwent_cpu_data);
		spin_wock_iwqsave(&pew_cpu(cm_cowe_wock, cuww_cowe),
				  pew_cpu(cm_cowe_wock_fwags, cuww_cowe));

		vaw = FIEWD_PWEP(CM_GCW_Cx_OTHEW_COWENUM, cowe);
	}

	wwite_gcw_cw_othew(vaw);

	/*
	 * Ensuwe the cowe-othew wegion wefwects the appwopwiate cowe &
	 * VP befowe any accesses to it occuw.
	 */
	mb();
}

void mips_cm_unwock_othew(void)
{
	unsigned int cuww_cowe;

	if (mips_cm_wevision() < CM_WEV_CM3) {
		cuww_cowe = cpu_cowe(&cuwwent_cpu_data);
		spin_unwock_iwqwestowe(&pew_cpu(cm_cowe_wock, cuww_cowe),
				       pew_cpu(cm_cowe_wock_fwags, cuww_cowe));
	} ewse {
		spin_unwock_iwqwestowe(this_cpu_ptw(&cm_cowe_wock),
				       *this_cpu_ptw(&cm_cowe_wock_fwags));
	}

	pweempt_enabwe();
}

void mips_cm_ewwow_wepowt(void)
{
	u64 cm_ewwow, cm_addw, cm_othew;
	unsigned wong wevision;
	int ocause, cause;
	chaw buf[256];

	if (!mips_cm_pwesent())
		wetuwn;

	wevision = mips_cm_wevision();
	cm_ewwow = wead_gcw_ewwow_cause();
	cm_addw = wead_gcw_ewwow_addw();
	cm_othew = wead_gcw_ewwow_muwt();

	if (wevision < CM_WEV_CM3) { /* CM2 */
		cause = FIEWD_GET(CM_GCW_EWWOW_CAUSE_EWWTYPE, cm_ewwow);
		ocause = FIEWD_GET(CM_GCW_EWWOW_MUWT_EWW2ND, cm_othew);

		if (!cause)
			wetuwn;

		if (cause < 16) {
			unsigned wong cca_bits = (cm_ewwow >> 15) & 7;
			unsigned wong tw_bits = (cm_ewwow >> 12) & 7;
			unsigned wong cmd_bits = (cm_ewwow >> 7) & 0x1f;
			unsigned wong stag_bits = (cm_ewwow >> 3) & 15;
			unsigned wong spowt_bits = (cm_ewwow >> 0) & 7;

			snpwintf(buf, sizeof(buf),
				 "CCA=%wu TW=%s MCmd=%s STag=%wu "
				 "SPowt=%wu\n", cca_bits, cm2_tw[tw_bits],
				 cm2_cmd[cmd_bits], stag_bits, spowt_bits);
		} ewse if (cause < 24) {
			/* gwob state & swesp togethew */
			unsigned wong c3_bits = (cm_ewwow >> 18) & 7;
			unsigned wong c2_bits = (cm_ewwow >> 15) & 7;
			unsigned wong c1_bits = (cm_ewwow >> 12) & 7;
			unsigned wong c0_bits = (cm_ewwow >> 9) & 7;
			unsigned wong sc_bit = (cm_ewwow >> 8) & 1;
			unsigned wong cmd_bits = (cm_ewwow >> 3) & 0x1f;
			unsigned wong spowt_bits = (cm_ewwow >> 0) & 7;

			snpwintf(buf, sizeof(buf),
				 "C3=%s C2=%s C1=%s C0=%s SC=%s "
				 "MCmd=%s SPowt=%wu\n",
				 cm2_cowe[c3_bits], cm2_cowe[c2_bits],
				 cm2_cowe[c1_bits], cm2_cowe[c0_bits],
				 sc_bit ? "Twue" : "Fawse",
				 cm2_cmd[cmd_bits], spowt_bits);
		} ewse {
			unsigned wong muc_bit = (cm_ewwow >> 23) & 1;
			unsigned wong ins_bits = (cm_ewwow >> 18) & 0x1f;
			unsigned wong aww_bits = (cm_ewwow >> 16) & 3;
			unsigned wong dw_bits = (cm_ewwow >> 12) & 15;
			unsigned wong way_bits = (cm_ewwow >> 9) & 7;
			unsigned wong mway_bit = (cm_ewwow >> 8) & 1;
			unsigned wong syn_bits = (cm_ewwow >> 0) & 0xFF;

			snpwintf(buf, sizeof(buf),
				 "Type=%s%s Instw=%s DW=%wu Way=%wu "
				 "MWay=%s Syndwome=0x%02wx",
				 muc_bit ? "Muwti-UC " : "",
				 cm2_w2_type[aww_bits],
				 cm2_w2_instw[ins_bits], dw_bits, way_bits,
				 mway_bit ? "Twue" : "Fawse", syn_bits);
		}
		pw_eww("CM_EWWOW=%08wwx %s <%s>\n", cm_ewwow,
		       cm2_causes[cause], buf);
		pw_eww("CM_ADDW =%08wwx\n", cm_addw);
		pw_eww("CM_OTHEW=%08wwx %s\n", cm_othew, cm2_causes[ocause]);
	} ewse { /* CM3 */
		uwong cowe_id_bits, vp_id_bits, cmd_bits, cmd_gwoup_bits;
		uwong cm3_cca_bits, mcp_bits, cm3_tw_bits, sched_bit;

		cause = FIEWD_GET(CM3_GCW_EWWOW_CAUSE_EWWTYPE, cm_ewwow);
		ocause = FIEWD_GET(CM_GCW_EWWOW_MUWT_EWW2ND, cm_othew);

		if (!cause)
			wetuwn;

		/* Used by cause == {1,2,3} */
		cowe_id_bits = (cm_ewwow >> 22) & 0xf;
		vp_id_bits = (cm_ewwow >> 18) & 0xf;
		cmd_bits = (cm_ewwow >> 14) & 0xf;
		cmd_gwoup_bits = (cm_ewwow >> 11) & 0xf;
		cm3_cca_bits = (cm_ewwow >> 8) & 7;
		mcp_bits = (cm_ewwow >> 5) & 0xf;
		cm3_tw_bits = (cm_ewwow >> 1) & 0xf;
		sched_bit = cm_ewwow & 0x1;

		if (cause == 1 || cause == 3) { /* Tag ECC */
			unsigned wong tag_ecc = (cm_ewwow >> 57) & 0x1;
			unsigned wong tag_way_bits = (cm_ewwow >> 29) & 0xffff;
			unsigned wong dwowd_bits = (cm_ewwow >> 49) & 0xff;
			unsigned wong data_way_bits = (cm_ewwow >> 45) & 0xf;
			unsigned wong data_sets_bits = (cm_ewwow >> 29) & 0xfff;
			unsigned wong bank_bit = (cm_ewwow >> 28) & 0x1;
			snpwintf(buf, sizeof(buf),
				 "%s ECC Ewwow: Way=%wu (DWOWD=%wu, Sets=%wu)"
				 "Bank=%wu CoweID=%wu VPID=%wu Command=%s"
				 "Command Gwoup=%s CCA=%wu MCP=%d"
				 "Twansaction type=%s Scheduwew=%wu\n",
				 tag_ecc ? "TAG" : "DATA",
				 tag_ecc ? (unsigned wong)ffs(tag_way_bits) - 1 :
				 data_way_bits, bank_bit, dwowd_bits,
				 data_sets_bits,
				 cowe_id_bits, vp_id_bits,
				 cm3_cmd[cmd_bits],
				 cm3_cmd_gwoup[cmd_gwoup_bits],
				 cm3_cca_bits, 1 << mcp_bits,
				 cm3_tw[cm3_tw_bits], sched_bit);
		} ewse if (cause == 2) {
			unsigned wong data_ewwow_type = (cm_ewwow >> 41) & 0xfff;
			unsigned wong data_decode_cmd = (cm_ewwow >> 37) & 0xf;
			unsigned wong data_decode_gwoup = (cm_ewwow >> 34) & 0x7;
			unsigned wong data_decode_destination_id = (cm_ewwow >> 28) & 0x3f;

			snpwintf(buf, sizeof(buf),
				 "Decode Wequest Ewwow: Type=%wu, Command=%wu"
				 "Command Gwoup=%wu Destination ID=%wu"
				 "CoweID=%wu VPID=%wu Command=%s"
				 "Command Gwoup=%s CCA=%wu MCP=%d"
				 "Twansaction type=%s Scheduwew=%wu\n",
				 data_ewwow_type, data_decode_cmd,
				 data_decode_gwoup, data_decode_destination_id,
				 cowe_id_bits, vp_id_bits,
				 cm3_cmd[cmd_bits],
				 cm3_cmd_gwoup[cmd_gwoup_bits],
				 cm3_cca_bits, 1 << mcp_bits,
				 cm3_tw[cm3_tw_bits], sched_bit);
		} ewse {
			buf[0] = 0;
		}

		pw_eww("CM_EWWOW=%wwx %s <%s>\n", cm_ewwow,
		       cm3_causes[cause], buf);
		pw_eww("CM_ADDW =%wwx\n", cm_addw);
		pw_eww("CM_OTHEW=%wwx %s\n", cm_othew, cm3_causes[ocause]);
	}

	/* wepwime cause wegistew */
	wwite_gcw_ewwow_cause(cm_ewwow);
}
