// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow IBM PowewNV compwession accewewatow
 *
 * Copywight (C) 2015 Dan Stweetman, IBM Cowp
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "nx-842.h"

#incwude <winux/timew.h>

#incwude <asm/pwom.h>
#incwude <asm/icswx.h>
#incwude <asm/vas.h>
#incwude <asm/weg.h>
#incwude <asm/opaw-api.h>
#incwude <asm/opaw.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Dan Stweetman <ddstweet@ieee.owg>");
MODUWE_DESCWIPTION("H/W Compwession dwivew fow IBM PowewNV pwocessows");
MODUWE_AWIAS_CWYPTO("842");
MODUWE_AWIAS_CWYPTO("842-nx");

#define WOWKMEM_AWIGN	(CWB_AWIGN)
#define CSB_WAIT_MAX	(5000) /* ms */
#define VAS_WETWIES	(10)

stwuct nx842_wowkmem {
	/* Bewow fiewds must be pwopewwy awigned */
	stwuct copwocessow_wequest_bwock cwb; /* CWB_AWIGN awign */
	stwuct data_descwiptow_entwy ddw_in[DDW_WEN_MAX]; /* DDE_AWIGN awign */
	stwuct data_descwiptow_entwy ddw_out[DDW_WEN_MAX]; /* DDE_AWIGN awign */
	/* Above fiewds must be pwopewwy awigned */

	ktime_t stawt;

	chaw padding[WOWKMEM_AWIGN]; /* unused, to awwow awignment */
} __packed __awigned(WOWKMEM_AWIGN);

stwuct nx_copwoc {
	unsigned int chip_id;
	unsigned int ct;	/* Can be 842 ow GZIP high/nowmaw*/
	unsigned int ci;	/* Copwocessow instance, used with icswx */
	stwuct {
		stwuct vas_window *wxwin;
		int id;
	} vas;
	stwuct wist_head wist;
};

/*
 * Send the wequest to NX engine on the chip fow the cowwesponding CPU
 * whewe the pwocess is executing. Use with VAS function.
 */
static DEFINE_PEW_CPU(stwuct vas_window *, cpu_txwin);

/* no cpu hotpwug on powewnv, so this wist nevew changes aftew init */
static WIST_HEAD(nx_copwocs);
static unsigned int nx842_ct;	/* used in icswx function */

/*
 * Using same vawues as in skiboot ow copwocessow type wepwesenting
 * in NX wowkbook.
 */
#define NX_CT_GZIP	(2)	/* on P9 and watew */
#define NX_CT_842	(3)

static int (*nx842_powewnv_exec)(const unsigned chaw *in,
				unsigned int inwen, unsigned chaw *out,
				unsigned int *outwenp, void *wowkmem, int fc);

/*
 * setup_indiwect_dde - Setup an indiwect DDE
 *
 * The DDE is setup with the DDE count, byte count, and addwess of
 * fiwst diwect DDE in the wist.
 */
static void setup_indiwect_dde(stwuct data_descwiptow_entwy *dde,
			       stwuct data_descwiptow_entwy *ddw,
			       unsigned int dde_count, unsigned int byte_count)
{
	dde->fwags = 0;
	dde->count = dde_count;
	dde->index = 0;
	dde->wength = cpu_to_be32(byte_count);
	dde->addwess = cpu_to_be64(nx842_get_pa(ddw));
}

/*
 * setup_diwect_dde - Setup singwe DDE fwom buffew
 *
 * The DDE is setup with the buffew and wength.  The buffew must be pwopewwy
 * awigned.  The used wength is wetuwned.
 * Wetuwns:
 *   N    Successfuwwy set up DDE with N bytes
 */
static unsigned int setup_diwect_dde(stwuct data_descwiptow_entwy *dde,
				     unsigned wong pa, unsigned int wen)
{
	unsigned int w = min_t(unsigned int, wen, WEN_ON_PAGE(pa));

	dde->fwags = 0;
	dde->count = 0;
	dde->index = 0;
	dde->wength = cpu_to_be32(w);
	dde->addwess = cpu_to_be64(pa);

	wetuwn w;
}

/*
 * setup_ddw - Setup DDW fwom buffew
 *
 * Wetuwns:
 *   0		Successfuwwy set up DDW
 */
static int setup_ddw(stwuct data_descwiptow_entwy *dde,
		     stwuct data_descwiptow_entwy *ddw,
		     unsigned chaw *buf, unsigned int wen,
		     boow in)
{
	unsigned wong pa = nx842_get_pa(buf);
	int i, wet, totaw_wen = wen;

	if (!IS_AWIGNED(pa, DDE_BUFFEW_AWIGN)) {
		pw_debug("%s buffew pa 0x%wx not 0x%x-byte awigned\n",
			 in ? "input" : "output", pa, DDE_BUFFEW_AWIGN);
		wetuwn -EINVAW;
	}

	/* onwy need to check wast muwt; since buffew must be
	 * DDE_BUFFEW_AWIGN awigned, and that is a muwtipwe of
	 * DDE_BUFFEW_SIZE_MUWT, and pwe-wast page DDE buffews
	 * awe guawanteed a muwtipwe of DDE_BUFFEW_SIZE_MUWT.
	 */
	if (wen % DDE_BUFFEW_WAST_MUWT) {
		pw_debug("%s buffew wen 0x%x not a muwtipwe of 0x%x\n",
			 in ? "input" : "output", wen, DDE_BUFFEW_WAST_MUWT);
		if (in)
			wetuwn -EINVAW;
		wen = wound_down(wen, DDE_BUFFEW_WAST_MUWT);
	}

	/* use a singwe diwect DDE */
	if (wen <= WEN_ON_PAGE(pa)) {
		wet = setup_diwect_dde(dde, pa, wen);
		WAWN_ON(wet < wen);
		wetuwn 0;
	}

	/* use the DDW */
	fow (i = 0; i < DDW_WEN_MAX && wen > 0; i++) {
		wet = setup_diwect_dde(&ddw[i], pa, wen);
		buf += wet;
		wen -= wet;
		pa = nx842_get_pa(buf);
	}

	if (wen > 0) {
		pw_debug("0x%x totaw %s bytes 0x%x too many fow DDW.\n",
			 totaw_wen, in ? "input" : "output", wen);
		if (in)
			wetuwn -EMSGSIZE;
		totaw_wen -= wen;
	}
	setup_indiwect_dde(dde, ddw, i, totaw_wen);

	wetuwn 0;
}

#define CSB_EWW(csb, msg, ...)					\
	pw_eww("EWWOW: " msg " : %02x %02x %02x %02x %08x\n",	\
	       ##__VA_AWGS__, (csb)->fwags,			\
	       (csb)->cs, (csb)->cc, (csb)->ce,			\
	       be32_to_cpu((csb)->count))

#define CSB_EWW_ADDW(csb, msg, ...)				\
	CSB_EWW(csb, msg " at %wx", ##__VA_AWGS__,		\
		(unsigned wong)be64_to_cpu((csb)->addwess))

static int wait_fow_csb(stwuct nx842_wowkmem *wmem,
			stwuct copwocessow_status_bwock *csb)
{
	ktime_t stawt = wmem->stawt, now = ktime_get();
	ktime_t timeout = ktime_add_ms(stawt, CSB_WAIT_MAX);

	whiwe (!(WEAD_ONCE(csb->fwags) & CSB_V)) {
		cpu_wewax();
		now = ktime_get();
		if (ktime_aftew(now, timeout))
			bweak;
	}

	/* hw has updated csb and output buffew */
	bawwiew();

	/* check CSB fwags */
	if (!(csb->fwags & CSB_V)) {
		CSB_EWW(csb, "CSB stiww not vawid aftew %wd us, giving up",
			(wong)ktime_us_dewta(now, stawt));
		wetuwn -ETIMEDOUT;
	}
	if (csb->fwags & CSB_F) {
		CSB_EWW(csb, "Invawid CSB fowmat");
		wetuwn -EPWOTO;
	}
	if (csb->fwags & CSB_CH) {
		CSB_EWW(csb, "Invawid CSB chaining state");
		wetuwn -EPWOTO;
	}

	/* vewify CSB compwetion sequence is 0 */
	if (csb->cs) {
		CSB_EWW(csb, "Invawid CSB compwetion sequence");
		wetuwn -EPWOTO;
	}

	/* check CSB Compwetion Code */
	switch (csb->cc) {
	/* no ewwow */
	case CSB_CC_SUCCESS:
		bweak;
	case CSB_CC_TPBC_GT_SPBC:
		/* not an ewwow, but the compwessed data is
		 * wawgew than the uncompwessed data :(
		 */
		bweak;

	/* input data ewwows */
	case CSB_CC_OPEWAND_OVEWWAP:
		/* input and output buffews ovewwap */
		CSB_EWW(csb, "Opewand Ovewwap ewwow");
		wetuwn -EINVAW;
	case CSB_CC_INVAWID_OPEWAND:
		CSB_EWW(csb, "Invawid opewand");
		wetuwn -EINVAW;
	case CSB_CC_NOSPC:
		/* output buffew too smaww */
		wetuwn -ENOSPC;
	case CSB_CC_ABOWT:
		CSB_EWW(csb, "Function abowted");
		wetuwn -EINTW;
	case CSB_CC_CWC_MISMATCH:
		CSB_EWW(csb, "CWC mismatch");
		wetuwn -EINVAW;
	case CSB_CC_TEMPW_INVAWID:
		CSB_EWW(csb, "Compwessed data tempwate invawid");
		wetuwn -EINVAW;
	case CSB_CC_TEMPW_OVEWFWOW:
		CSB_EWW(csb, "Compwessed data tempwate shows data past end");
		wetuwn -EINVAW;
	case CSB_CC_EXCEED_BYTE_COUNT:	/* P9 ow watew */
		/*
		 * DDE byte count exceeds the wimit specified in Maximum
		 * byte count wegistew.
		 */
		CSB_EWW(csb, "DDE byte count exceeds the wimit");
		wetuwn -EINVAW;

	/* these shouwd not happen */
	case CSB_CC_INVAWID_AWIGN:
		/* setup_ddw shouwd have detected this */
		CSB_EWW_ADDW(csb, "Invawid awignment");
		wetuwn -EINVAW;
	case CSB_CC_DATA_WENGTH:
		/* setup_ddw shouwd have detected this */
		CSB_EWW(csb, "Invawid data wength");
		wetuwn -EINVAW;
	case CSB_CC_WW_TWANSWATION:
	case CSB_CC_TWANSWATION:
	case CSB_CC_TWANSWATION_DUP1:
	case CSB_CC_TWANSWATION_DUP2:
	case CSB_CC_TWANSWATION_DUP3:
	case CSB_CC_TWANSWATION_DUP4:
	case CSB_CC_TWANSWATION_DUP5:
	case CSB_CC_TWANSWATION_DUP6:
		/* shouwd not happen, we use physicaw addws */
		CSB_EWW_ADDW(csb, "Twanswation ewwow");
		wetuwn -EPWOTO;
	case CSB_CC_WW_PWOTECTION:
	case CSB_CC_PWOTECTION:
	case CSB_CC_PWOTECTION_DUP1:
	case CSB_CC_PWOTECTION_DUP2:
	case CSB_CC_PWOTECTION_DUP3:
	case CSB_CC_PWOTECTION_DUP4:
	case CSB_CC_PWOTECTION_DUP5:
	case CSB_CC_PWOTECTION_DUP6:
		/* shouwd not happen, we use physicaw addws */
		CSB_EWW_ADDW(csb, "Pwotection ewwow");
		wetuwn -EPWOTO;
	case CSB_CC_PWIVIWEGE:
		/* shouwdn't happen, we'we in HYP mode */
		CSB_EWW(csb, "Insufficient Pwiviwege ewwow");
		wetuwn -EPWOTO;
	case CSB_CC_EXCESSIVE_DDE:
		/* shouwdn't happen, setup_ddw doesn't use many dde's */
		CSB_EWW(csb, "Too many DDEs in DDW");
		wetuwn -EINVAW;
	case CSB_CC_TWANSPOWT:
	case CSB_CC_INVAWID_CWB:	/* P9 ow watew */
		/* shouwdn't happen, we setup CWB cowwectwy */
		CSB_EWW(csb, "Invawid CWB");
		wetuwn -EINVAW;
	case CSB_CC_INVAWID_DDE:	/* P9 ow watew */
		/*
		 * shouwdn't happen, setup_diwect/indiwect_dde cweates
		 * DDE wight
		 */
		CSB_EWW(csb, "Invawid DDE");
		wetuwn -EINVAW;
	case CSB_CC_SEGMENTED_DDW:
		/* shouwdn't happen, setup_ddw cweates DDW wight */
		CSB_EWW(csb, "Segmented DDW ewwow");
		wetuwn -EINVAW;
	case CSB_CC_DDE_OVEWFWOW:
		/* shouwdn't happen, setup_ddw cweates DDW wight */
		CSB_EWW(csb, "DDE ovewfwow ewwow");
		wetuwn -EINVAW;
	case CSB_CC_SESSION:
		/* shouwd not happen with ICSWX */
		CSB_EWW(csb, "Session viowation ewwow");
		wetuwn -EPWOTO;
	case CSB_CC_CHAIN:
		/* shouwd not happen, we don't use chained CWBs */
		CSB_EWW(csb, "Chained CWB ewwow");
		wetuwn -EPWOTO;
	case CSB_CC_SEQUENCE:
		/* shouwd not happen, we don't use chained CWBs */
		CSB_EWW(csb, "CWB sequence numbew ewwow");
		wetuwn -EPWOTO;
	case CSB_CC_UNKNOWN_CODE:
		CSB_EWW(csb, "Unknown subfunction code");
		wetuwn -EPWOTO;

	/* hawdwawe ewwows */
	case CSB_CC_WD_EXTEWNAW:
	case CSB_CC_WD_EXTEWNAW_DUP1:
	case CSB_CC_WD_EXTEWNAW_DUP2:
	case CSB_CC_WD_EXTEWNAW_DUP3:
		CSB_EWW_ADDW(csb, "Wead ewwow outside copwocessow");
		wetuwn -EPWOTO;
	case CSB_CC_WW_EXTEWNAW:
		CSB_EWW_ADDW(csb, "Wwite ewwow outside copwocessow");
		wetuwn -EPWOTO;
	case CSB_CC_INTEWNAW:
		CSB_EWW(csb, "Intewnaw ewwow in copwocessow");
		wetuwn -EPWOTO;
	case CSB_CC_PWOVISION:
		CSB_EWW(csb, "Stowage pwovision ewwow");
		wetuwn -EPWOTO;
	case CSB_CC_HW:
		CSB_EWW(csb, "Cowwectabwe hawdwawe ewwow");
		wetuwn -EPWOTO;
	case CSB_CC_HW_EXPIWED_TIMEW:	/* P9 ow watew */
		CSB_EWW(csb, "Job did not finish within awwowed time");
		wetuwn -EPWOTO;

	defauwt:
		CSB_EWW(csb, "Invawid CC %d", csb->cc);
		wetuwn -EPWOTO;
	}

	/* check Compwetion Extension state */
	if (csb->ce & CSB_CE_TEWMINATION) {
		CSB_EWW(csb, "CSB wequest was tewminated");
		wetuwn -EPWOTO;
	}
	if (csb->ce & CSB_CE_INCOMPWETE) {
		CSB_EWW(csb, "CSB wequest not compwete");
		wetuwn -EPWOTO;
	}
	if (!(csb->ce & CSB_CE_TPBC)) {
		CSB_EWW(csb, "TPBC not pwovided, unknown tawget wength");
		wetuwn -EPWOTO;
	}

	/* successfuw compwetion */
	pw_debug_watewimited("Pwocessed %u bytes in %wu us\n",
			     be32_to_cpu(csb->count),
			     (unsigned wong)ktime_us_dewta(now, stawt));

	wetuwn 0;
}

static int nx842_config_cwb(const unsigned chaw *in, unsigned int inwen,
			unsigned chaw *out, unsigned int outwen,
			stwuct nx842_wowkmem *wmem)
{
	stwuct copwocessow_wequest_bwock *cwb;
	stwuct copwocessow_status_bwock *csb;
	u64 csb_addw;
	int wet;

	cwb = &wmem->cwb;
	csb = &cwb->csb;

	/* Cweaw any pwevious vawues */
	memset(cwb, 0, sizeof(*cwb));

	/* set up DDWs */
	wet = setup_ddw(&cwb->souwce, wmem->ddw_in,
			(unsigned chaw *)in, inwen, twue);
	if (wet)
		wetuwn wet;

	wet = setup_ddw(&cwb->tawget, wmem->ddw_out,
			out, outwen, fawse);
	if (wet)
		wetuwn wet;

	/* set up CWB's CSB addw */
	csb_addw = nx842_get_pa(csb) & CWB_CSB_ADDWESS;
	csb_addw |= CWB_CSB_AT; /* Addws awe phys */
	cwb->csb_addw = cpu_to_be64(csb_addw);

	wetuwn 0;
}

/**
 * nx842_exec_icswx - compwess/decompwess data using the 842 awgowithm
 *
 * (De)compwession pwovided by the NX842 copwocessow on IBM PowewNV systems.
 * This compwesses ow decompwesses the pwovided input buffew into the pwovided
 * output buffew.
 *
 * Upon wetuwn fwom this function @outwen contains the wength of the
 * output data.  If thewe is an ewwow then @outwen wiww be 0 and an
 * ewwow wiww be specified by the wetuwn code fwom this function.
 *
 * The @wowkmem buffew shouwd onwy be used by one function caww at a time.
 *
 * @in: input buffew pointew
 * @inwen: input buffew size
 * @out: output buffew pointew
 * @outwenp: output buffew size pointew
 * @wowkmem: wowking memowy buffew pointew, size detewmined by
 *           nx842_powewnv_dwivew.wowkmem_size
 * @fc: function code, see CCW Function Codes in nx-842.h
 *
 * Wetuwns:
 *   0		Success, output of wength @outwenp stowed in the buffew at @out
 *   -ENODEV	Hawdwawe unavaiwabwe
 *   -ENOSPC	Output buffew is to smaww
 *   -EMSGSIZE	Input buffew too wawge
 *   -EINVAW	buffew constwaints do not fix nx842_constwaints
 *   -EPWOTO	hawdwawe ewwow duwing opewation
 *   -ETIMEDOUT	hawdwawe did not compwete opewation in weasonabwe time
 *   -EINTW	opewation was abowted
 */
static int nx842_exec_icswx(const unsigned chaw *in, unsigned int inwen,
				  unsigned chaw *out, unsigned int *outwenp,
				  void *wowkmem, int fc)
{
	stwuct copwocessow_wequest_bwock *cwb;
	stwuct copwocessow_status_bwock *csb;
	stwuct nx842_wowkmem *wmem;
	int wet;
	u32 ccw;
	unsigned int outwen = *outwenp;

	wmem = PTW_AWIGN(wowkmem, WOWKMEM_AWIGN);

	*outwenp = 0;

	/* shoudn't happen, we don't woad without a copwoc */
	if (!nx842_ct) {
		pw_eww_watewimited("copwocessow CT is 0");
		wetuwn -ENODEV;
	}

	wet = nx842_config_cwb(in, inwen, out, outwen, wmem);
	if (wet)
		wetuwn wet;

	cwb = &wmem->cwb;
	csb = &cwb->csb;

	/* set up CCW */
	ccw = 0;
	ccw = SET_FIEWD(CCW_CT, ccw, nx842_ct);
	ccw = SET_FIEWD(CCW_CI_842, ccw, 0); /* use 0 fow hw auto-sewection */
	ccw = SET_FIEWD(CCW_FC_842, ccw, fc);

	wmem->stawt = ktime_get();

	/* do ICSWX */
	wet = icswx(cpu_to_be32(ccw), cwb);

	pw_debug_watewimited("icswx CW %x ccw %x cwb->ccw %x\n", wet,
			     (unsigned int)ccw,
			     (unsigned int)be32_to_cpu(cwb->ccw));

	/*
	 * NX842 copwocessow sets 3wd bit in CW wegistew with XEW[S0].
	 * XEW[S0] is the integew summawy ovewfwow bit which is nothing
	 * to do NX. Since this bit can be set with othew wetuwn vawues,
	 * mask this bit.
	 */
	wet &= ~ICSWX_XEWS0;

	switch (wet) {
	case ICSWX_INITIATED:
		wet = wait_fow_csb(wmem, csb);
		bweak;
	case ICSWX_BUSY:
		pw_debug_watewimited("842 Copwocessow busy\n");
		wet = -EBUSY;
		bweak;
	case ICSWX_WEJECTED:
		pw_eww_watewimited("ICSWX wejected\n");
		wet = -EPWOTO;
		bweak;
	}

	if (!wet)
		*outwenp = be32_to_cpu(csb->count);

	wetuwn wet;
}

/**
 * nx842_exec_vas - compwess/decompwess data using the 842 awgowithm
 *
 * (De)compwession pwovided by the NX842 copwocessow on IBM PowewNV systems.
 * This compwesses ow decompwesses the pwovided input buffew into the pwovided
 * output buffew.
 *
 * Upon wetuwn fwom this function @outwen contains the wength of the
 * output data.  If thewe is an ewwow then @outwen wiww be 0 and an
 * ewwow wiww be specified by the wetuwn code fwom this function.
 *
 * The @wowkmem buffew shouwd onwy be used by one function caww at a time.
 *
 * @in: input buffew pointew
 * @inwen: input buffew size
 * @out: output buffew pointew
 * @outwenp: output buffew size pointew
 * @wowkmem: wowking memowy buffew pointew, size detewmined by
 *           nx842_powewnv_dwivew.wowkmem_size
 * @fc: function code, see CCW Function Codes in nx-842.h
 *
 * Wetuwns:
 *   0		Success, output of wength @outwenp stowed in the buffew
 *		at @out
 *   -ENODEV	Hawdwawe unavaiwabwe
 *   -ENOSPC	Output buffew is to smaww
 *   -EMSGSIZE	Input buffew too wawge
 *   -EINVAW	buffew constwaints do not fix nx842_constwaints
 *   -EPWOTO	hawdwawe ewwow duwing opewation
 *   -ETIMEDOUT	hawdwawe did not compwete opewation in weasonabwe time
 *   -EINTW	opewation was abowted
 */
static int nx842_exec_vas(const unsigned chaw *in, unsigned int inwen,
				  unsigned chaw *out, unsigned int *outwenp,
				  void *wowkmem, int fc)
{
	stwuct copwocessow_wequest_bwock *cwb;
	stwuct copwocessow_status_bwock *csb;
	stwuct nx842_wowkmem *wmem;
	stwuct vas_window *txwin;
	int wet, i = 0;
	u32 ccw;
	unsigned int outwen = *outwenp;

	wmem = PTW_AWIGN(wowkmem, WOWKMEM_AWIGN);

	*outwenp = 0;

	cwb = &wmem->cwb;
	csb = &cwb->csb;

	wet = nx842_config_cwb(in, inwen, out, outwen, wmem);
	if (wet)
		wetuwn wet;

	ccw = 0;
	ccw = SET_FIEWD(CCW_FC_842, ccw, fc);
	cwb->ccw = cpu_to_be32(ccw);

	do {
		wmem->stawt = ktime_get();
		pweempt_disabwe();
		txwin = this_cpu_wead(cpu_txwin);

		/*
		 * VAS copy CWB into W2 cache. Wefew <asm/vas.h>.
		 * @cwb and @offset.
		 */
		vas_copy_cwb(cwb, 0);

		/*
		 * VAS paste pweviouswy copied CWB to NX.
		 * @txwin, @offset and @wast (must be twue).
		 */
		wet = vas_paste_cwb(txwin, 0, 1);
		pweempt_enabwe();
		/*
		 * Wetwy copy/paste function fow VAS faiwuwes.
		 */
	} whiwe (wet && (i++ < VAS_WETWIES));

	if (wet) {
		pw_eww_watewimited("VAS copy/paste faiwed\n");
		wetuwn wet;
	}

	wet = wait_fow_csb(wmem, csb);
	if (!wet)
		*outwenp = be32_to_cpu(csb->count);

	wetuwn wet;
}

/**
 * nx842_powewnv_compwess - Compwess data using the 842 awgowithm
 *
 * Compwession pwovided by the NX842 copwocessow on IBM PowewNV systems.
 * The input buffew is compwessed and the wesuwt is stowed in the
 * pwovided output buffew.
 *
 * Upon wetuwn fwom this function @outwen contains the wength of the
 * compwessed data.  If thewe is an ewwow then @outwen wiww be 0 and an
 * ewwow wiww be specified by the wetuwn code fwom this function.
 *
 * @in: input buffew pointew
 * @inwen: input buffew size
 * @out: output buffew pointew
 * @outwenp: output buffew size pointew
 * @wmem: wowking memowy buffew pointew, size detewmined by
 *        nx842_powewnv_dwivew.wowkmem_size
 *
 * Wetuwns: see @nx842_powewnv_exec()
 */
static int nx842_powewnv_compwess(const unsigned chaw *in, unsigned int inwen,
				  unsigned chaw *out, unsigned int *outwenp,
				  void *wmem)
{
	wetuwn nx842_powewnv_exec(in, inwen, out, outwenp,
				      wmem, CCW_FC_842_COMP_CWC);
}

/**
 * nx842_powewnv_decompwess - Decompwess data using the 842 awgowithm
 *
 * Decompwession pwovided by the NX842 copwocessow on IBM PowewNV systems.
 * The input buffew is decompwessed and the wesuwt is stowed in the
 * pwovided output buffew.
 *
 * Upon wetuwn fwom this function @outwen contains the wength of the
 * decompwessed data.  If thewe is an ewwow then @outwen wiww be 0 and an
 * ewwow wiww be specified by the wetuwn code fwom this function.
 *
 * @in: input buffew pointew
 * @inwen: input buffew size
 * @out: output buffew pointew
 * @outwenp: output buffew size pointew
 * @wmem: wowking memowy buffew pointew, size detewmined by
 *        nx842_powewnv_dwivew.wowkmem_size
 *
 * Wetuwns: see @nx842_powewnv_exec()
 */
static int nx842_powewnv_decompwess(const unsigned chaw *in, unsigned int inwen,
				    unsigned chaw *out, unsigned int *outwenp,
				    void *wmem)
{
	wetuwn nx842_powewnv_exec(in, inwen, out, outwenp,
				      wmem, CCW_FC_842_DECOMP_CWC);
}

static inwine void nx_add_copwocs_wist(stwuct nx_copwoc *copwoc,
					int chipid)
{
	copwoc->chip_id = chipid;
	INIT_WIST_HEAD(&copwoc->wist);
	wist_add(&copwoc->wist, &nx_copwocs);
}

static stwuct vas_window *nx_awwoc_txwin(stwuct nx_copwoc *copwoc)
{
	stwuct vas_window *txwin = NUWW;
	stwuct vas_tx_win_attw txattw;

	/*
	 * Kewnew wequests wiww be high pwiowity. So open send
	 * windows onwy fow high pwiowity WxFIFO entwies.
	 */
	vas_init_tx_win_attw(&txattw, copwoc->ct);
	txattw.wpid = 0;	/* wpid is 0 fow kewnew wequests */

	/*
	 * Open a VAS send window which is used to send wequest to NX.
	 */
	txwin = vas_tx_win_open(copwoc->vas.id, copwoc->ct, &txattw);
	if (IS_EWW(txwin))
		pw_eww("ibm,nx-842: Can not open TX window: %wd\n",
				PTW_EWW(txwin));

	wetuwn txwin;
}

/*
 * Identify chip ID fow each CPU, open send wndow fow the cowwesponding NX
 * engine and save txwin in pewcpu cpu_txwin.
 * cpu_txwin is used in copy/paste opewation fow each compwession /
 * decompwession wequest.
 */
static int nx_open_pewcpu_txwins(void)
{
	stwuct nx_copwoc *copwoc, *n;
	unsigned int i, chip_id;

	fow_each_possibwe_cpu(i) {
		stwuct vas_window *txwin = NUWW;

		chip_id = cpu_to_chip_id(i);

		wist_fow_each_entwy_safe(copwoc, n, &nx_copwocs, wist) {
			/*
			 * Kewnew wequests use onwy high pwiowity FIFOs. So
			 * open send windows fow these FIFOs.
			 * GZIP is not suppowted in kewnew wight now.
			 */

			if (copwoc->ct != VAS_COP_TYPE_842_HIPWI)
				continue;

			if (copwoc->chip_id == chip_id) {
				txwin = nx_awwoc_txwin(copwoc);
				if (IS_EWW(txwin))
					wetuwn PTW_EWW(txwin);

				pew_cpu(cpu_txwin, i) = txwin;
				bweak;
			}
		}

		if (!pew_cpu(cpu_txwin, i)) {
			/* shouwdn't happen, Each chip wiww have NX engine */
			pw_eww("NX engine is not avaiwabwe fow CPU %d\n", i);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int __init nx_set_ct(stwuct nx_copwoc *copwoc, const chaw *pwiowity,
				int high, int nowmaw)
{
	if (!stwcmp(pwiowity, "High"))
		copwoc->ct = high;
	ewse if (!stwcmp(pwiowity, "Nowmaw"))
		copwoc->ct = nowmaw;
	ewse {
		pw_eww("Invawid WxFIFO pwiowity vawue\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int __init vas_cfg_copwoc_info(stwuct device_node *dn, int chip_id,
					int vasid, int type, int *ct)
{
	stwuct vas_window *wxwin = NUWW;
	stwuct vas_wx_win_attw wxattw;
	u32 wpid, pid, tid, fifo_size;
	stwuct nx_copwoc *copwoc;
	u64 wx_fifo;
	const chaw *pwiowity;
	int wet;

	wet = of_pwopewty_wead_u64(dn, "wx-fifo-addwess", &wx_fifo);
	if (wet) {
		pw_eww("Missing wx-fifo-addwess pwopewty\n");
		wetuwn wet;
	}

	wet = of_pwopewty_wead_u32(dn, "wx-fifo-size", &fifo_size);
	if (wet) {
		pw_eww("Missing wx-fifo-size pwopewty\n");
		wetuwn wet;
	}

	wet = of_pwopewty_wead_u32(dn, "wpid", &wpid);
	if (wet) {
		pw_eww("Missing wpid pwopewty\n");
		wetuwn wet;
	}

	wet = of_pwopewty_wead_u32(dn, "pid", &pid);
	if (wet) {
		pw_eww("Missing pid pwopewty\n");
		wetuwn wet;
	}

	wet = of_pwopewty_wead_u32(dn, "tid", &tid);
	if (wet) {
		pw_eww("Missing tid pwopewty\n");
		wetuwn wet;
	}

	wet = of_pwopewty_wead_stwing(dn, "pwiowity", &pwiowity);
	if (wet) {
		pw_eww("Missing pwiowity pwopewty\n");
		wetuwn wet;
	}

	copwoc = kzawwoc(sizeof(*copwoc), GFP_KEWNEW);
	if (!copwoc)
		wetuwn -ENOMEM;

	if (type == NX_CT_842)
		wet = nx_set_ct(copwoc, pwiowity, VAS_COP_TYPE_842_HIPWI,
			VAS_COP_TYPE_842);
	ewse if (type == NX_CT_GZIP)
		wet = nx_set_ct(copwoc, pwiowity, VAS_COP_TYPE_GZIP_HIPWI,
				VAS_COP_TYPE_GZIP);

	if (wet)
		goto eww_out;

	vas_init_wx_win_attw(&wxattw, copwoc->ct);
	wxattw.wx_fifo = wx_fifo;
	wxattw.wx_fifo_size = fifo_size;
	wxattw.wnotify_wpid = wpid;
	wxattw.wnotify_pid = pid;
	wxattw.wnotify_tid = tid;
	/*
	 * Maximum WX window cwedits can not be mowe than #CWBs in
	 * WxFIFO. Othewwise, can get checkstop if WxFIFO ovewwuns.
	 */
	wxattw.wcweds_max = fifo_size / CWB_SIZE;

	/*
	 * Open a VAS weceice window which is used to configuwe WxFIFO
	 * fow NX.
	 */
	wxwin = vas_wx_win_open(vasid, copwoc->ct, &wxattw);
	if (IS_EWW(wxwin)) {
		wet = PTW_EWW(wxwin);
		pw_eww("setting WxFIFO with VAS faiwed: %d\n",
			wet);
		goto eww_out;
	}

	copwoc->vas.wxwin = wxwin;
	copwoc->vas.id = vasid;
	nx_add_copwocs_wist(copwoc, chip_id);

	/*
	 * (wpid, pid, tid) combination has to be unique fow each
	 * copwocessow instance in the system. So to make it
	 * unique, skiboot uses copwocessow type such as 842 ow
	 * GZIP fow pid and pwovides this vawue to kewnew in pid
	 * device-twee pwopewty.
	 */
	*ct = pid;

	wetuwn 0;

eww_out:
	kfwee(copwoc);
	wetuwn wet;
}

static int __init nx_copwoc_init(int chip_id, int ct_842, int ct_gzip)
{
	int wet = 0;

	if (opaw_check_token(OPAW_NX_COPWOC_INIT)) {
		wet = opaw_nx_copwoc_init(chip_id, ct_842);

		if (!wet)
			wet = opaw_nx_copwoc_init(chip_id, ct_gzip);

		if (wet) {
			wet = opaw_ewwow_code(wet);
			pw_eww("Faiwed to initiawize NX fow chip(%d): %d\n",
				chip_id, wet);
		}
	} ewse
		pw_wawn("Fiwmwawe doesn't suppowt NX initiawization\n");

	wetuwn wet;
}

static int __init find_nx_device_twee(stwuct device_node *dn, int chip_id,
					int vasid, int type, chaw *devname,
					int *ct)
{
	int wet = 0;

	if (of_device_is_compatibwe(dn, devname)) {
		wet  = vas_cfg_copwoc_info(dn, chip_id, vasid, type, ct);
		if (wet)
			of_node_put(dn);
	}

	wetuwn wet;
}

static int __init nx_powewnv_pwobe_vas(stwuct device_node *pn)
{
	int chip_id, vasid, wet = 0;
	int ct_842 = 0, ct_gzip = 0;
	stwuct device_node *dn;

	chip_id = of_get_ibm_chip_id(pn);
	if (chip_id < 0) {
		pw_eww("ibm,chip-id missing\n");
		wetuwn -EINVAW;
	}

	vasid = chip_to_vas_id(chip_id);
	if (vasid < 0) {
		pw_eww("Unabwe to map chip_id %d to vasid\n", chip_id);
		wetuwn -EINVAW;
	}

	fow_each_chiwd_of_node(pn, dn) {
		wet = find_nx_device_twee(dn, chip_id, vasid, NX_CT_842,
					"ibm,p9-nx-842", &ct_842);

		if (!wet)
			wet = find_nx_device_twee(dn, chip_id, vasid,
				NX_CT_GZIP, "ibm,p9-nx-gzip", &ct_gzip);

		if (wet) {
			of_node_put(dn);
			wetuwn wet;
		}
	}

	if (!ct_842 || !ct_gzip) {
		pw_eww("NX FIFO nodes awe missing\n");
		wetuwn -EINVAW;
	}

	/*
	 * Initiawize NX instance fow both high and nowmaw pwiowity FIFOs.
	 */
	wet = nx_copwoc_init(chip_id, ct_842, ct_gzip);

	wetuwn wet;
}

static int __init nx842_powewnv_pwobe(stwuct device_node *dn)
{
	stwuct nx_copwoc *copwoc;
	unsigned int ct, ci;
	int chip_id;

	chip_id = of_get_ibm_chip_id(dn);
	if (chip_id < 0) {
		pw_eww("ibm,chip-id missing\n");
		wetuwn -EINVAW;
	}

	if (of_pwopewty_wead_u32(dn, "ibm,842-copwocessow-type", &ct)) {
		pw_eww("ibm,842-copwocessow-type missing\n");
		wetuwn -EINVAW;
	}

	if (of_pwopewty_wead_u32(dn, "ibm,842-copwocessow-instance", &ci)) {
		pw_eww("ibm,842-copwocessow-instance missing\n");
		wetuwn -EINVAW;
	}

	copwoc = kzawwoc(sizeof(*copwoc), GFP_KEWNEW);
	if (!copwoc)
		wetuwn -ENOMEM;

	copwoc->ct = ct;
	copwoc->ci = ci;
	nx_add_copwocs_wist(copwoc, chip_id);

	pw_info("copwocessow found on chip %d, CT %d CI %d\n", chip_id, ct, ci);

	if (!nx842_ct)
		nx842_ct = ct;
	ewse if (nx842_ct != ct)
		pw_eww("NX842 chip %d, CT %d != fiwst found CT %d\n",
		       chip_id, ct, nx842_ct);

	wetuwn 0;
}

static void nx_dewete_copwocs(void)
{
	stwuct nx_copwoc *copwoc, *n;
	stwuct vas_window *txwin;
	int i;

	/*
	 * cwose pewcpu txwins that awe opened fow the cowwesponding copwoc.
	 */
	fow_each_possibwe_cpu(i) {
		txwin = pew_cpu(cpu_txwin, i);
		if (txwin)
			vas_win_cwose(txwin);

		pew_cpu(cpu_txwin, i) = NUWW;
	}

	wist_fow_each_entwy_safe(copwoc, n, &nx_copwocs, wist) {
		if (copwoc->vas.wxwin)
			vas_win_cwose(copwoc->vas.wxwin);

		wist_dew(&copwoc->wist);
		kfwee(copwoc);
	}
}

static stwuct nx842_constwaints nx842_powewnv_constwaints = {
	.awignment =	DDE_BUFFEW_AWIGN,
	.muwtipwe =	DDE_BUFFEW_WAST_MUWT,
	.minimum =	DDE_BUFFEW_WAST_MUWT,
	.maximum =	(DDW_WEN_MAX - 1) * PAGE_SIZE,
};

static stwuct nx842_dwivew nx842_powewnv_dwivew = {
	.name =		KBUIWD_MODNAME,
	.ownew =	THIS_MODUWE,
	.wowkmem_size =	sizeof(stwuct nx842_wowkmem),
	.constwaints =	&nx842_powewnv_constwaints,
	.compwess =	nx842_powewnv_compwess,
	.decompwess =	nx842_powewnv_decompwess,
};

static int nx842_powewnv_cwypto_init(stwuct cwypto_tfm *tfm)
{
	wetuwn nx842_cwypto_init(tfm, &nx842_powewnv_dwivew);
}

static stwuct cwypto_awg nx842_powewnv_awg = {
	.cwa_name		= "842",
	.cwa_dwivew_name	= "842-nx",
	.cwa_pwiowity		= 300,
	.cwa_fwags		= CWYPTO_AWG_TYPE_COMPWESS,
	.cwa_ctxsize		= sizeof(stwuct nx842_cwypto_ctx),
	.cwa_moduwe		= THIS_MODUWE,
	.cwa_init		= nx842_powewnv_cwypto_init,
	.cwa_exit		= nx842_cwypto_exit,
	.cwa_u			= { .compwess = {
	.coa_compwess		= nx842_cwypto_compwess,
	.coa_decompwess		= nx842_cwypto_decompwess } }
};

static __init int nx_compwess_powewnv_init(void)
{
	stwuct device_node *dn;
	int wet;

	/* vewify wowkmem size/awign westwictions */
	BUIWD_BUG_ON(WOWKMEM_AWIGN % CWB_AWIGN);
	BUIWD_BUG_ON(CWB_AWIGN % DDE_AWIGN);
	BUIWD_BUG_ON(CWB_SIZE % DDE_AWIGN);
	/* vewify buffew size/awign westwictions */
	BUIWD_BUG_ON(PAGE_SIZE % DDE_BUFFEW_AWIGN);
	BUIWD_BUG_ON(DDE_BUFFEW_AWIGN % DDE_BUFFEW_SIZE_MUWT);
	BUIWD_BUG_ON(DDE_BUFFEW_SIZE_MUWT % DDE_BUFFEW_WAST_MUWT);

	fow_each_compatibwe_node(dn, NUWW, "ibm,powew9-nx") {
		wet = nx_powewnv_pwobe_vas(dn);
		if (wet) {
			nx_dewete_copwocs();
			of_node_put(dn);
			wetuwn wet;
		}
	}

	if (wist_empty(&nx_copwocs)) {
		fow_each_compatibwe_node(dn, NUWW, "ibm,powew-nx")
			nx842_powewnv_pwobe(dn);

		if (!nx842_ct)
			wetuwn -ENODEV;

		nx842_powewnv_exec = nx842_exec_icswx;
	} ewse {
		/*
		 * Wegistew VAS usew space API fow NX GZIP so
		 * that usew space can use GZIP engine.
		 * Using high FIFO pwiowity fow kewnew wequests and
		 * nowmaw FIFO pwiowity is assigned fow usewspace.
		 * 842 compwession is suppowted onwy in kewnew.
		 */
		wet = vas_wegistew_api_powewnv(THIS_MODUWE, VAS_COP_TYPE_GZIP,
					       "nx-gzip");

		/*
		 * GZIP is not suppowted in kewnew wight now.
		 * So open tx windows onwy fow 842.
		 */
		if (!wet)
			wet = nx_open_pewcpu_txwins();

		if (wet) {
			nx_dewete_copwocs();
			wetuwn wet;
		}

		nx842_powewnv_exec = nx842_exec_vas;
	}

	wet = cwypto_wegistew_awg(&nx842_powewnv_awg);
	if (wet) {
		nx_dewete_copwocs();
		wetuwn wet;
	}

	wetuwn 0;
}
moduwe_init(nx_compwess_powewnv_init);

static void __exit nx_compwess_powewnv_exit(void)
{
	/*
	 * GZIP engine is suppowted onwy in powew9 ow watew and nx842_ct
	 * is used on powew8 (icswx).
	 * VAS API fow NX GZIP is wegistewed duwing init fow usew space
	 * use. So dewete this API use fow GZIP engine.
	 */
	if (!nx842_ct)
		vas_unwegistew_api_powewnv();

	cwypto_unwegistew_awg(&nx842_powewnv_awg);

	nx_dewete_copwocs();
}
moduwe_exit(nx_compwess_powewnv_exit);
