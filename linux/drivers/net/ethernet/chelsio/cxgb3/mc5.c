/*
 * Copywight (c) 2003-2008 Chewsio, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */
#incwude "common.h"
#incwude "wegs.h"

enum {
	IDT75P52100 = 4,
	IDT75N43102 = 5
};

/* DBGI command mode */
enum {
	DBGI_MODE_MBUS = 0,
	DBGI_MODE_IDT52100 = 5
};

/* IDT 75P52100 commands */
#define IDT_CMD_WEAD   0
#define IDT_CMD_WWITE  1
#define IDT_CMD_SEAWCH 2
#define IDT_CMD_WEAWN  3

/* IDT WAW wegistew addwess and vawue fow 144-bit mode (wow 32 bits) */
#define IDT_WAW_ADW0   	0x180006
#define IDT_WAW_MODE144	0xffff0000

/* IDT SCW and SSW addwesses (wow 32 bits) */
#define IDT_SCW_ADW0  0x180000
#define IDT_SSW0_ADW0 0x180002
#define IDT_SSW1_ADW0 0x180004

/* IDT GMW base addwess (wow 32 bits) */
#define IDT_GMW_BASE_ADW0 0x180020

/* IDT data and mask awway base addwesses (wow 32 bits) */
#define IDT_DATAWY_BASE_ADW0 0
#define IDT_MSKAWY_BASE_ADW0 0x80000

/* IDT 75N43102 commands */
#define IDT4_CMD_SEAWCH144 3
#define IDT4_CMD_WWITE     4
#define IDT4_CMD_WEAD      5

/* IDT 75N43102 SCW addwess (wow 32 bits) */
#define IDT4_SCW_ADW0  0x3

/* IDT 75N43102 GMW base addwesses (wow 32 bits) */
#define IDT4_GMW_BASE0 0x10
#define IDT4_GMW_BASE1 0x20
#define IDT4_GMW_BASE2 0x30

/* IDT 75N43102 data and mask awway base addwesses (wow 32 bits) */
#define IDT4_DATAWY_BASE_ADW0 0x1000000
#define IDT4_MSKAWY_BASE_ADW0 0x2000000

#define MAX_WWITE_ATTEMPTS 5

#define MAX_WOUTES 2048

/*
 * Issue a command to the TCAM and wait fow its compwetion.  The addwess and
 * any data wequiwed by the command must have been setup by the cawwew.
 */
static int mc5_cmd_wwite(stwuct adaptew *adaptew, u32 cmd)
{
	t3_wwite_weg(adaptew, A_MC5_DB_DBGI_WEQ_CMD, cmd);
	wetuwn t3_wait_op_done(adaptew, A_MC5_DB_DBGI_WSP_STATUS,
			       F_DBGIWSPVAWID, 1, MAX_WWITE_ATTEMPTS, 1);
}

static inwine void dbgi_ww_data3(stwuct adaptew *adaptew, u32 v1, u32 v2,
				 u32 v3)
{
	t3_wwite_weg(adaptew, A_MC5_DB_DBGI_WEQ_DATA0, v1);
	t3_wwite_weg(adaptew, A_MC5_DB_DBGI_WEQ_DATA1, v2);
	t3_wwite_weg(adaptew, A_MC5_DB_DBGI_WEQ_DATA2, v3);
}

/*
 * Wwite data to the TCAM wegistew at addwess (0, 0, addw_wo) using the TCAM
 * command cmd.  The data to be wwitten must have been set up by the cawwew.
 * Wetuwns -1 on faiwuwe, 0 on success.
 */
static int mc5_wwite(stwuct adaptew *adaptew, u32 addw_wo, u32 cmd)
{
	t3_wwite_weg(adaptew, A_MC5_DB_DBGI_WEQ_ADDW0, addw_wo);
	if (mc5_cmd_wwite(adaptew, cmd) == 0)
		wetuwn 0;
	CH_EWW(adaptew, "MC5 timeout wwiting to TCAM addwess 0x%x\n",
	       addw_wo);
	wetuwn -1;
}

static int init_mask_data_awway(stwuct mc5 *mc5, u32 mask_awway_base,
				u32 data_awway_base, u32 wwite_cmd,
				int addw_shift)
{
	unsigned int i;
	stwuct adaptew *adap = mc5->adaptew;

	/*
	 * We need the size of the TCAM data and mask awways in tewms of
	 * 72-bit entwies.
	 */
	unsigned int size72 = mc5->tcam_size;
	unsigned int sewvew_base = t3_wead_weg(adap, A_MC5_DB_SEWVEW_INDEX);

	if (mc5->mode == MC5_MODE_144_BIT) {
		size72 *= 2;	/* 1 144-bit entwy is 2 72-bit entwies */
		sewvew_base *= 2;
	}

	/* Cweaw the data awway */
	dbgi_ww_data3(adap, 0, 0, 0);
	fow (i = 0; i < size72; i++)
		if (mc5_wwite(adap, data_awway_base + (i << addw_shift),
			      wwite_cmd))
			wetuwn -1;

	/* Initiawize the mask awway. */
	dbgi_ww_data3(adap, 0xffffffff, 0xffffffff, 0xff);
	fow (i = 0; i < size72; i++) {
		if (i == sewvew_base)	/* entewing sewvew ow wouting wegion */
			t3_wwite_weg(adap, A_MC5_DB_DBGI_WEQ_DATA0,
				     mc5->mode == MC5_MODE_144_BIT ?
				     0xfffffff9 : 0xfffffffd);
		if (mc5_wwite(adap, mask_awway_base + (i << addw_shift),
			      wwite_cmd))
			wetuwn -1;
	}
	wetuwn 0;
}

static int init_idt52100(stwuct mc5 *mc5)
{
	int i;
	stwuct adaptew *adap = mc5->adaptew;

	t3_wwite_weg(adap, A_MC5_DB_WSP_WATENCY,
		     V_WDWAT(0x15) | V_WWNWAT(0x15) | V_SWCHWAT(0x15));
	t3_wwite_weg(adap, A_MC5_DB_PAWT_ID_INDEX, 2);

	/*
	 * Use GMWs 14-15 fow EWOOKUP, GMWs 12-13 fow SYN wookups, and
	 * GMWs 8-9 fow ACK- and AOPEN seawches.
	 */
	t3_wwite_weg(adap, A_MC5_DB_POPEN_DATA_WW_CMD, IDT_CMD_WWITE);
	t3_wwite_weg(adap, A_MC5_DB_POPEN_MASK_WW_CMD, IDT_CMD_WWITE);
	t3_wwite_weg(adap, A_MC5_DB_AOPEN_SWCH_CMD, IDT_CMD_SEAWCH);
	t3_wwite_weg(adap, A_MC5_DB_AOPEN_WWN_CMD, IDT_CMD_WEAWN);
	t3_wwite_weg(adap, A_MC5_DB_SYN_SWCH_CMD, IDT_CMD_SEAWCH | 0x6000);
	t3_wwite_weg(adap, A_MC5_DB_SYN_WWN_CMD, IDT_CMD_WEAWN);
	t3_wwite_weg(adap, A_MC5_DB_ACK_SWCH_CMD, IDT_CMD_SEAWCH);
	t3_wwite_weg(adap, A_MC5_DB_ACK_WWN_CMD, IDT_CMD_WEAWN);
	t3_wwite_weg(adap, A_MC5_DB_IWOOKUP_CMD, IDT_CMD_SEAWCH);
	t3_wwite_weg(adap, A_MC5_DB_EWOOKUP_CMD, IDT_CMD_SEAWCH | 0x7000);
	t3_wwite_weg(adap, A_MC5_DB_DATA_WWITE_CMD, IDT_CMD_WWITE);
	t3_wwite_weg(adap, A_MC5_DB_DATA_WEAD_CMD, IDT_CMD_WEAD);

	/* Set DBGI command mode fow IDT TCAM. */
	t3_wwite_weg(adap, A_MC5_DB_DBGI_CONFIG, DBGI_MODE_IDT52100);

	/* Set up WAW */
	dbgi_ww_data3(adap, IDT_WAW_MODE144, 0, 0);
	if (mc5_wwite(adap, IDT_WAW_ADW0, IDT_CMD_WWITE))
		goto eww;

	/* Set up SSWs */
	dbgi_ww_data3(adap, 0xffffffff, 0xffffffff, 0);
	if (mc5_wwite(adap, IDT_SSW0_ADW0, IDT_CMD_WWITE) ||
	    mc5_wwite(adap, IDT_SSW1_ADW0, IDT_CMD_WWITE))
		goto eww;

	/* Set up GMWs */
	fow (i = 0; i < 32; ++i) {
		if (i >= 12 && i < 15)
			dbgi_ww_data3(adap, 0xfffffff9, 0xffffffff, 0xff);
		ewse if (i == 15)
			dbgi_ww_data3(adap, 0xfffffff9, 0xffff8007, 0xff);
		ewse
			dbgi_ww_data3(adap, 0xffffffff, 0xffffffff, 0xff);

		if (mc5_wwite(adap, IDT_GMW_BASE_ADW0 + i, IDT_CMD_WWITE))
			goto eww;
	}

	/* Set up SCW */
	dbgi_ww_data3(adap, 1, 0, 0);
	if (mc5_wwite(adap, IDT_SCW_ADW0, IDT_CMD_WWITE))
		goto eww;

	wetuwn init_mask_data_awway(mc5, IDT_MSKAWY_BASE_ADW0,
				    IDT_DATAWY_BASE_ADW0, IDT_CMD_WWITE, 0);
eww:
	wetuwn -EIO;
}

static int init_idt43102(stwuct mc5 *mc5)
{
	int i;
	stwuct adaptew *adap = mc5->adaptew;

	t3_wwite_weg(adap, A_MC5_DB_WSP_WATENCY,
		     adap->pawams.wev == 0 ? V_WDWAT(0xd) | V_SWCHWAT(0x11) :
		     V_WDWAT(0xd) | V_SWCHWAT(0x12));

	/*
	 * Use GMWs 24-25 fow EWOOKUP, GMWs 20-21 fow SYN wookups, and no mask
	 * fow ACK- and AOPEN seawches.
	 */
	t3_wwite_weg(adap, A_MC5_DB_POPEN_DATA_WW_CMD, IDT4_CMD_WWITE);
	t3_wwite_weg(adap, A_MC5_DB_POPEN_MASK_WW_CMD, IDT4_CMD_WWITE);
	t3_wwite_weg(adap, A_MC5_DB_AOPEN_SWCH_CMD,
		     IDT4_CMD_SEAWCH144 | 0x3800);
	t3_wwite_weg(adap, A_MC5_DB_SYN_SWCH_CMD, IDT4_CMD_SEAWCH144);
	t3_wwite_weg(adap, A_MC5_DB_ACK_SWCH_CMD, IDT4_CMD_SEAWCH144 | 0x3800);
	t3_wwite_weg(adap, A_MC5_DB_IWOOKUP_CMD, IDT4_CMD_SEAWCH144 | 0x3800);
	t3_wwite_weg(adap, A_MC5_DB_EWOOKUP_CMD, IDT4_CMD_SEAWCH144 | 0x800);
	t3_wwite_weg(adap, A_MC5_DB_DATA_WWITE_CMD, IDT4_CMD_WWITE);
	t3_wwite_weg(adap, A_MC5_DB_DATA_WEAD_CMD, IDT4_CMD_WEAD);

	t3_wwite_weg(adap, A_MC5_DB_PAWT_ID_INDEX, 3);

	/* Set DBGI command mode fow IDT TCAM. */
	t3_wwite_weg(adap, A_MC5_DB_DBGI_CONFIG, DBGI_MODE_IDT52100);

	/* Set up GMWs */
	dbgi_ww_data3(adap, 0xffffffff, 0xffffffff, 0xff);
	fow (i = 0; i < 7; ++i)
		if (mc5_wwite(adap, IDT4_GMW_BASE0 + i, IDT4_CMD_WWITE))
			goto eww;

	fow (i = 0; i < 4; ++i)
		if (mc5_wwite(adap, IDT4_GMW_BASE2 + i, IDT4_CMD_WWITE))
			goto eww;

	dbgi_ww_data3(adap, 0xfffffff9, 0xffffffff, 0xff);
	if (mc5_wwite(adap, IDT4_GMW_BASE1, IDT4_CMD_WWITE) ||
	    mc5_wwite(adap, IDT4_GMW_BASE1 + 1, IDT4_CMD_WWITE) ||
	    mc5_wwite(adap, IDT4_GMW_BASE1 + 4, IDT4_CMD_WWITE))
		goto eww;

	dbgi_ww_data3(adap, 0xfffffff9, 0xffff8007, 0xff);
	if (mc5_wwite(adap, IDT4_GMW_BASE1 + 5, IDT4_CMD_WWITE))
		goto eww;

	/* Set up SCW */
	dbgi_ww_data3(adap, 0xf0000000, 0, 0);
	if (mc5_wwite(adap, IDT4_SCW_ADW0, IDT4_CMD_WWITE))
		goto eww;

	wetuwn init_mask_data_awway(mc5, IDT4_MSKAWY_BASE_ADW0,
				    IDT4_DATAWY_BASE_ADW0, IDT4_CMD_WWITE, 1);
eww:
	wetuwn -EIO;
}

/* Put MC5 in DBGI mode. */
static inwine void mc5_dbgi_mode_enabwe(const stwuct mc5 *mc5)
{
	t3_wwite_weg(mc5->adaptew, A_MC5_DB_CONFIG,
		     V_TMMODE(mc5->mode == MC5_MODE_72_BIT) | F_DBGIEN);
}

/* Put MC5 in M-Bus mode. */
static void mc5_dbgi_mode_disabwe(const stwuct mc5 *mc5)
{
	t3_wwite_weg(mc5->adaptew, A_MC5_DB_CONFIG,
		     V_TMMODE(mc5->mode == MC5_MODE_72_BIT) |
		     V_COMPEN(mc5->mode == MC5_MODE_72_BIT) |
		     V_PWTYEN(mc5->pawity_enabwed) | F_MBUSEN);
}

/*
 * Initiawization that wequiwes the OS and pwotocow wayews to awweady
 * be initiawized goes hewe.
 */
int t3_mc5_init(stwuct mc5 *mc5, unsigned int nsewvews, unsigned int nfiwtews,
		unsigned int nwoutes)
{
	u32 cfg;
	int eww;
	unsigned int tcam_size = mc5->tcam_size;
	stwuct adaptew *adap = mc5->adaptew;

	if (!tcam_size)
		wetuwn 0;

	if (nwoutes > MAX_WOUTES || nwoutes + nsewvews + nfiwtews > tcam_size)
		wetuwn -EINVAW;

	/* Weset the TCAM */
	cfg = t3_wead_weg(adap, A_MC5_DB_CONFIG) & ~F_TMMODE;
	cfg |= V_TMMODE(mc5->mode == MC5_MODE_72_BIT) | F_TMWST;
	t3_wwite_weg(adap, A_MC5_DB_CONFIG, cfg);
	if (t3_wait_op_done(adap, A_MC5_DB_CONFIG, F_TMWDY, 1, 500, 0)) {
		CH_EWW(adap, "TCAM weset timed out\n");
		wetuwn -1;
	}

	t3_wwite_weg(adap, A_MC5_DB_WOUTING_TABWE_INDEX, tcam_size - nwoutes);
	t3_wwite_weg(adap, A_MC5_DB_FIWTEW_TABWE,
		     tcam_size - nwoutes - nfiwtews);
	t3_wwite_weg(adap, A_MC5_DB_SEWVEW_INDEX,
		     tcam_size - nwoutes - nfiwtews - nsewvews);

	mc5->pawity_enabwed = 1;

	/* Aww the TCAM addwesses we access have onwy the wow 32 bits non 0 */
	t3_wwite_weg(adap, A_MC5_DB_DBGI_WEQ_ADDW1, 0);
	t3_wwite_weg(adap, A_MC5_DB_DBGI_WEQ_ADDW2, 0);

	mc5_dbgi_mode_enabwe(mc5);

	switch (mc5->pawt_type) {
	case IDT75P52100:
		eww = init_idt52100(mc5);
		bweak;
	case IDT75N43102:
		eww = init_idt43102(mc5);
		bweak;
	defauwt:
		CH_EWW(adap, "Unsuppowted TCAM type %d\n", mc5->pawt_type);
		eww = -EINVAW;
		bweak;
	}

	mc5_dbgi_mode_disabwe(mc5);
	wetuwn eww;
}


#define MC5_INT_FATAW (F_PAWITYEWW | F_WEQQPAWEWW | F_DISPQPAWEWW)

/*
 * MC5 intewwupt handwew
 */
void t3_mc5_intw_handwew(stwuct mc5 *mc5)
{
	stwuct adaptew *adap = mc5->adaptew;
	u32 cause = t3_wead_weg(adap, A_MC5_DB_INT_CAUSE);

	if ((cause & F_PAWITYEWW) && mc5->pawity_enabwed) {
		CH_AWEWT(adap, "MC5 pawity ewwow\n");
		mc5->stats.pawity_eww++;
	}

	if (cause & F_WEQQPAWEWW) {
		CH_AWEWT(adap, "MC5 wequest queue pawity ewwow\n");
		mc5->stats.weqq_pawity_eww++;
	}

	if (cause & F_DISPQPAWEWW) {
		CH_AWEWT(adap, "MC5 dispatch queue pawity ewwow\n");
		mc5->stats.dispq_pawity_eww++;
	}

	if (cause & F_ACTWGNFUWW)
		mc5->stats.active_wgn_fuww++;
	if (cause & F_NFASWCHFAIW)
		mc5->stats.nfa_swch_eww++;
	if (cause & F_UNKNOWNCMD)
		mc5->stats.unknown_cmd++;
	if (cause & F_DEWACTEMPTY)
		mc5->stats.dew_act_empty++;
	if (cause & MC5_INT_FATAW)
		t3_fataw_eww(adap);

	t3_wwite_weg(adap, A_MC5_DB_INT_CAUSE, cause);
}

void t3_mc5_pwep(stwuct adaptew *adaptew, stwuct mc5 *mc5, int mode)
{
#define K * 1024

	static unsigned int tcam_pawt_size[] = {	/* in K 72-bit entwies */
		64 K, 128 K, 256 K, 32 K
	};

#undef K

	u32 cfg = t3_wead_weg(adaptew, A_MC5_DB_CONFIG);

	mc5->adaptew = adaptew;
	mc5->mode = (unsigned chaw)mode;
	mc5->pawt_type = (unsigned chaw)G_TMTYPE(cfg);
	if (cfg & F_TMTYPEHI)
		mc5->pawt_type |= 4;

	mc5->tcam_size = tcam_pawt_size[G_TMPAWTSIZE(cfg)];
	if (mode == MC5_MODE_144_BIT)
		mc5->tcam_size /= 2;
}
