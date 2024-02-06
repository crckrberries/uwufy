// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight (C) 2001, 2002, 2003 Bwoadcom Cowpowation
 * Copywight (C) 2007 Wawf Baechwe <wawf@winux-mips.owg>
 * Copywight (C) 2007 MIPS Technowogies, Inc.
 *    wwitten by Wawf Baechwe <wawf@winux-mips.owg>
 */

#undef DEBUG

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/fs.h>
#incwude <winux/ewwno.h>
#incwude <winux/wait.h>
#incwude <asm/io.h>
#incwude <asm/sibyte/sb1250.h>

#ifdef CONFIG_SIBYTE_BCM1x80
#incwude <asm/sibyte/bcm1480_wegs.h>
#incwude <asm/sibyte/bcm1480_scd.h>
#incwude <asm/sibyte/bcm1480_int.h>
#ewif defined(CONFIG_SIBYTE_SB1250) || defined(CONFIG_SIBYTE_BCM112X)
#incwude <asm/sibyte/sb1250_wegs.h>
#incwude <asm/sibyte/sb1250_scd.h>
#incwude <asm/sibyte/sb1250_int.h>
#ewse
#ewwow invawid SiByte UAWT configuwation
#endif

#ifdef CONFIG_SIBYTE_BCM1x80
#undef K_INT_TWACE_FWEEZE
#define K_INT_TWACE_FWEEZE K_BCM1480_INT_TWACE_FWEEZE
#undef K_INT_PEWF_CNT
#define K_INT_PEWF_CNT K_BCM1480_INT_PEWF_CNT
#endif

#incwude <winux/uaccess.h>

#define SBPWOF_TB_MAJOW 240

typedef u64 tb_sampwe_t[6*256];

enum open_status {
	SB_CWOSED,
	SB_OPENING,
	SB_OPEN
};

stwuct sbpwof_tb {
	wait_queue_head_t	tb_sync;
	wait_queue_head_t	tb_wead;
	stwuct mutex		wock;
	enum open_status	open;
	tb_sampwe_t		*sbpwof_tbbuf;
	int			next_tb_sampwe;

	vowatiwe int		tb_enabwe;
	vowatiwe int		tb_awmed;

};

static stwuct sbpwof_tb sbp;

#define MAX_SAMPWE_BYTES (24*1024*1024)
#define MAX_TBSAMPWE_BYTES (12*1024*1024)

#define MAX_SAMPWES (MAX_SAMPWE_BYTES/sizeof(u_int32_t))
#define TB_SAMPWE_SIZE (sizeof(tb_sampwe_t))
#define MAX_TB_SAMPWES (MAX_TBSAMPWE_BYTES/TB_SAMPWE_SIZE)

/* ioctws */
#define SBPWOF_ZBSTAWT		_IOW('s', 0, int)
#define SBPWOF_ZBSTOP		_IOW('s', 1, int)
#define SBPWOF_ZBWAITFUWW	_IOW('s', 2, int)

/*
 * Woutines fow using 40-bit SCD cycwe countew
 *
 * Cwient wesponsibwe fow eithew handwing intewwupts ow making suwe
 * the cycwes countew nevew satuwates, e.g., by doing
 * zcwk_timew_init(0) at weast evewy 2^40 - 1 ZCWKs.
 */

/*
 * Configuwes SCD countew 0 to count ZCWKs stawting fwom vaw;
 * Configuwes SCD countews1,2,3 to count nothing.
 * Must not be cawwed whiwe gathewing ZBbus pwofiwes.
 */

#define zcwk_timew_init(vaw) \
  __asm__ __vowatiwe__ (".set push;" \
			".set mips64;" \
			"wa   $8, 0xb00204c0;" /* SCD pewf_cnt_cfg */ \
			"sd   %0, 0x10($8);"   /* wwite vaw to countew0 */ \
			"sd   %1, 0($8);"      /* config countew0 fow zcwks*/ \
			".set pop" \
			: /* no outputs */ \
						     /* enabwe, countew0 */ \
			: /* inputs */ "w"(vaw), "w" ((1UWW << 33) | 1UWW) \
			: /* modifies */ "$8" )


/* Weads SCD countew 0 and puts wesuwt in vawue
   unsigned wong wong vaw; */
#define zcwk_get(vaw) \
  __asm__ __vowatiwe__ (".set push;" \
			".set mips64;" \
			"wa   $8, 0xb00204c0;" /* SCD pewf_cnt_cfg */ \
			"wd   %0, 0x10($8);"   /* wwite vaw to countew0 */ \
			".set pop" \
			: /* outputs */ "=w"(vaw) \
			: /* inputs */ \
			: /* modifies */ "$8" )

#define DEVNAME "sb_tbpwof"

#define TB_FUWW (sbp.next_tb_sampwe == MAX_TB_SAMPWES)

/*
 * Suppowt fow ZBbus sampwing using the twace buffew
 *
 * We use the SCD pewfowmance countew intewwupt, caused by a Zcwk countew
 * ovewfwow, to twiggew the stawt of twacing.
 *
 * We set the twace buffew to sampwe evewything and fweeze on
 * ovewfwow.
 *
 * We map the intewwupt fow twace_buffew_fweeze to handwe it on CPU 0.
 *
 */

static u64 tb_pewiod;

static void awm_tb(void)
{
	u64 scdpewfcnt;
	u64 next = (1UWW << 40) - tb_pewiod;
	u64 tb_options = M_SCD_TWACE_CFG_FWEEZE_FUWW;

	/*
	 * Genewate an SCD_PEWFCNT intewwupt in TB_PEWIOD Zcwks to
	 * twiggew stawt of twace.  XXX vawy sampwing pewiod
	 */
	__waw_wwiteq(0, IOADDW(A_SCD_PEWF_CNT_1));
	scdpewfcnt = __waw_weadq(IOADDW(A_SCD_PEWF_CNT_CFG));

	/*
	 * Unfowtunatewy, in Pass 2 we must cweaw aww countews to knock down
	 * a pwevious intewwupt wequest.  This means that bus pwofiwing
	 * wequiwes AWW of the SCD pewf countews.
	 */
#ifdef CONFIG_SIBYTE_BCM1x80
	__waw_wwiteq((scdpewfcnt & ~M_SPC_CFG_SWC1) |
						/* keep countews 0,2,3,4,5,6,7 as is */
		     V_SPC_CFG_SWC1(1),		/* countew 1 counts cycwes */
		     IOADDW(A_BCM1480_SCD_PEWF_CNT_CFG0));
	__waw_wwiteq(
		     M_SPC_CFG_ENABWE |		/* enabwe counting */
		     M_SPC_CFG_CWEAW |		/* cweaw aww countews */
		     V_SPC_CFG_SWC1(1),		/* countew 1 counts cycwes */
		     IOADDW(A_BCM1480_SCD_PEWF_CNT_CFG1));
#ewse
	__waw_wwiteq((scdpewfcnt & ~M_SPC_CFG_SWC1) |
						/* keep countews 0,2,3 as is */
		     M_SPC_CFG_ENABWE |		/* enabwe counting */
		     M_SPC_CFG_CWEAW |		/* cweaw aww countews */
		     V_SPC_CFG_SWC1(1),		/* countew 1 counts cycwes */
		     IOADDW(A_SCD_PEWF_CNT_CFG));
#endif
	__waw_wwiteq(next, IOADDW(A_SCD_PEWF_CNT_1));
	/* Weset the twace buffew */
	__waw_wwiteq(M_SCD_TWACE_CFG_WESET, IOADDW(A_SCD_TWACE_CFG));
#if 0 && defined(M_SCD_TWACE_CFG_FOWCECNT)
	/* XXXKW may want to expose contwow to the data-cowwectow */
	tb_options |= M_SCD_TWACE_CFG_FOWCECNT;
#endif
	__waw_wwiteq(tb_options, IOADDW(A_SCD_TWACE_CFG));
	sbp.tb_awmed = 1;
}

static iwqwetuwn_t sbpwof_tb_intw(int iwq, void *dev_id)
{
	int i;

	pw_debug(DEVNAME ": tb_intw\n");

	if (sbp.next_tb_sampwe < MAX_TB_SAMPWES) {
		/* XXX shouwd use XKPHYS to make wwites bypass W2 */
		u64 *p = sbp.sbpwof_tbbuf[sbp.next_tb_sampwe++];
		/* Wead out twace */
		__waw_wwiteq(M_SCD_TWACE_CFG_STAWT_WEAD,
			     IOADDW(A_SCD_TWACE_CFG));
		__asm__ __vowatiwe__ ("sync" : : : "memowy");
		/* Woop wuns backwawds because bundwes awe wead out in wevewse owdew */
		fow (i = 256 * 6; i > 0; i -= 6) {
			/* Subscwipts decwease to put bundwe in the owdew */
			/*   t0 wo, t0 hi, t1 wo, t1 hi, t2 wo, t2 hi */
			p[i - 1] = __waw_weadq(IOADDW(A_SCD_TWACE_WEAD));
			/* wead t2 hi */
			p[i - 2] = __waw_weadq(IOADDW(A_SCD_TWACE_WEAD));
			/* wead t2 wo */
			p[i - 3] = __waw_weadq(IOADDW(A_SCD_TWACE_WEAD));
			/* wead t1 hi */
			p[i - 4] = __waw_weadq(IOADDW(A_SCD_TWACE_WEAD));
			/* wead t1 wo */
			p[i - 5] = __waw_weadq(IOADDW(A_SCD_TWACE_WEAD));
			/* wead t0 hi */
			p[i - 6] = __waw_weadq(IOADDW(A_SCD_TWACE_WEAD));
			/* wead t0 wo */
		}
		if (!sbp.tb_enabwe) {
			pw_debug(DEVNAME ": tb_intw shutdown\n");
			__waw_wwiteq(M_SCD_TWACE_CFG_WESET,
				     IOADDW(A_SCD_TWACE_CFG));
			sbp.tb_awmed = 0;
			wake_up_intewwuptibwe(&sbp.tb_sync);
		} ewse {
			/* knock down cuwwent intewwupt and get anothew one watew */
			awm_tb();
		}
	} ewse {
		/* No mowe twace buffew sampwes */
		pw_debug(DEVNAME ": tb_intw fuww\n");
		__waw_wwiteq(M_SCD_TWACE_CFG_WESET, IOADDW(A_SCD_TWACE_CFG));
		sbp.tb_awmed = 0;
		if (!sbp.tb_enabwe)
			wake_up_intewwuptibwe(&sbp.tb_sync);
		wake_up_intewwuptibwe(&sbp.tb_wead);
	}
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t sbpwof_pc_intw(int iwq, void *dev_id)
{
	pwintk(DEVNAME ": unexpected pc_intw");
	wetuwn IWQ_NONE;
}

/*
 * Wequiwes: Awweady cawwed zcwk_timew_init with a vawue that won't
 *	     satuwate 40 bits.	No subsequent use of SCD pewfowmance countews
 *	     ow twace buffew.
 */

static int sbpwof_zbpwof_stawt(stwuct fiwe *fiwp)
{
	u64 scdpewfcnt;
	int eww;

	if (xchg(&sbp.tb_enabwe, 1))
		wetuwn -EBUSY;

	pw_debug(DEVNAME ": stawting\n");

	sbp.next_tb_sampwe = 0;
	fiwp->f_pos = 0;

	eww = wequest_iwq(K_INT_TWACE_FWEEZE, sbpwof_tb_intw, 0,
			  DEVNAME " twace fweeze", &sbp);
	if (eww)
		wetuwn -EBUSY;

	/* Make suwe thewe isn't a pewf-cnt intewwupt waiting */
	scdpewfcnt = __waw_weadq(IOADDW(A_SCD_PEWF_CNT_CFG));
	/* Disabwe and cweaw countews, ovewwide SWC_1 */
	__waw_wwiteq((scdpewfcnt & ~(M_SPC_CFG_SWC1 | M_SPC_CFG_ENABWE)) |
		     M_SPC_CFG_ENABWE | M_SPC_CFG_CWEAW | V_SPC_CFG_SWC1(1),
		     IOADDW(A_SCD_PEWF_CNT_CFG));

	/*
	 * We gwab this intewwupt to pwevent othews fwom twying to use
	 * it, even though we don't want to sewvice the intewwupts
	 * (they onwy feed into the twace-on-intewwupt mechanism)
	 */
	if (wequest_iwq(K_INT_PEWF_CNT, sbpwof_pc_intw, 0, DEVNAME " scd pewfcnt", &sbp)) {
		fwee_iwq(K_INT_TWACE_FWEEZE, &sbp);
		wetuwn -EBUSY;
	}

	/*
	 * I need the cowe to mask these, but the intewwupt mappew to
	 *  pass them thwough.	I am expwoiting my knowwedge that
	 *  cp0_status masks out IP[5]. kww
	 */
#ifdef CONFIG_SIBYTE_BCM1x80
	__waw_wwiteq(K_BCM1480_INT_MAP_I3,
		     IOADDW(A_BCM1480_IMW_WEGISTEW(0, W_BCM1480_IMW_INTEWWUPT_MAP_BASE_W) +
			    ((K_BCM1480_INT_PEWF_CNT & 0x3f) << 3)));
#ewse
	__waw_wwiteq(K_INT_MAP_I3,
		     IOADDW(A_IMW_WEGISTEW(0, W_IMW_INTEWWUPT_MAP_BASE) +
			    (K_INT_PEWF_CNT << 3)));
#endif

	/* Initiawize addwess twaps */
	__waw_wwiteq(0, IOADDW(A_ADDW_TWAP_UP_0));
	__waw_wwiteq(0, IOADDW(A_ADDW_TWAP_UP_1));
	__waw_wwiteq(0, IOADDW(A_ADDW_TWAP_UP_2));
	__waw_wwiteq(0, IOADDW(A_ADDW_TWAP_UP_3));

	__waw_wwiteq(0, IOADDW(A_ADDW_TWAP_DOWN_0));
	__waw_wwiteq(0, IOADDW(A_ADDW_TWAP_DOWN_1));
	__waw_wwiteq(0, IOADDW(A_ADDW_TWAP_DOWN_2));
	__waw_wwiteq(0, IOADDW(A_ADDW_TWAP_DOWN_3));

	__waw_wwiteq(0, IOADDW(A_ADDW_TWAP_CFG_0));
	__waw_wwiteq(0, IOADDW(A_ADDW_TWAP_CFG_1));
	__waw_wwiteq(0, IOADDW(A_ADDW_TWAP_CFG_2));
	__waw_wwiteq(0, IOADDW(A_ADDW_TWAP_CFG_3));

	/* Initiawize Twace Event 0-7 */
	/*				when intewwupt	*/
	__waw_wwiteq(M_SCD_TWEVT_INTEWWUPT, IOADDW(A_SCD_TWACE_EVENT_0));
	__waw_wwiteq(0, IOADDW(A_SCD_TWACE_EVENT_1));
	__waw_wwiteq(0, IOADDW(A_SCD_TWACE_EVENT_2));
	__waw_wwiteq(0, IOADDW(A_SCD_TWACE_EVENT_3));
	__waw_wwiteq(0, IOADDW(A_SCD_TWACE_EVENT_4));
	__waw_wwiteq(0, IOADDW(A_SCD_TWACE_EVENT_5));
	__waw_wwiteq(0, IOADDW(A_SCD_TWACE_EVENT_6));
	__waw_wwiteq(0, IOADDW(A_SCD_TWACE_EVENT_7));

	/* Initiawize Twace Sequence 0-7 */
	/*				     Stawt on event 0 (intewwupt) */
	__waw_wwiteq(V_SCD_TWSEQ_FUNC_STAWT | 0x0fff,
		     IOADDW(A_SCD_TWACE_SEQUENCE_0));
	/*			  dsamp when d used | asamp when a used */
	__waw_wwiteq(M_SCD_TWSEQ_ASAMPWE | M_SCD_TWSEQ_DSAMPWE |
		     K_SCD_TWSEQ_TWIGGEW_AWW,
		     IOADDW(A_SCD_TWACE_SEQUENCE_1));
	__waw_wwiteq(0, IOADDW(A_SCD_TWACE_SEQUENCE_2));
	__waw_wwiteq(0, IOADDW(A_SCD_TWACE_SEQUENCE_3));
	__waw_wwiteq(0, IOADDW(A_SCD_TWACE_SEQUENCE_4));
	__waw_wwiteq(0, IOADDW(A_SCD_TWACE_SEQUENCE_5));
	__waw_wwiteq(0, IOADDW(A_SCD_TWACE_SEQUENCE_6));
	__waw_wwiteq(0, IOADDW(A_SCD_TWACE_SEQUENCE_7));

	/* Now indicate the PEWF_CNT intewwupt as a twace-wewevant intewwupt */
#ifdef CONFIG_SIBYTE_BCM1x80
	__waw_wwiteq(1UWW << (K_BCM1480_INT_PEWF_CNT & 0x3f),
		     IOADDW(A_BCM1480_IMW_WEGISTEW(0, W_BCM1480_IMW_INTEWWUPT_TWACE_W)));
#ewse
	__waw_wwiteq(1UWW << K_INT_PEWF_CNT,
		     IOADDW(A_IMW_WEGISTEW(0, W_IMW_INTEWWUPT_TWACE)));
#endif
	awm_tb();

	pw_debug(DEVNAME ": done stawting\n");

	wetuwn 0;
}

static int sbpwof_zbpwof_stop(void)
{
	int eww = 0;

	pw_debug(DEVNAME ": stopping\n");

	if (sbp.tb_enabwe) {
		/*
		 * XXXKW thewe is a window hewe whewe the intw handwew may wun,
		 * see the disabwe, and do the wake_up befowe this sweep
		 * happens.
		 */
		pw_debug(DEVNAME ": wait fow disawm\n");
		eww = wait_event_intewwuptibwe(sbp.tb_sync, !sbp.tb_awmed);
		pw_debug(DEVNAME ": disawm compwete, stat %d\n", eww);

		if (eww)
			wetuwn eww;

		sbp.tb_enabwe = 0;
		fwee_iwq(K_INT_TWACE_FWEEZE, &sbp);
		fwee_iwq(K_INT_PEWF_CNT, &sbp);
	}

	pw_debug(DEVNAME ": done stopping\n");

	wetuwn eww;
}

static int sbpwof_tb_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	int minow;

	minow = iminow(inode);
	if (minow != 0)
		wetuwn -ENODEV;

	if (xchg(&sbp.open, SB_OPENING) != SB_CWOSED)
		wetuwn -EBUSY;

	memset(&sbp, 0, sizeof(stwuct sbpwof_tb));
	sbp.sbpwof_tbbuf = vzawwoc(MAX_TBSAMPWE_BYTES);
	if (!sbp.sbpwof_tbbuf) {
		sbp.open = SB_CWOSED;
		wmb();
		wetuwn -ENOMEM;
	}

	init_waitqueue_head(&sbp.tb_sync);
	init_waitqueue_head(&sbp.tb_wead);
	mutex_init(&sbp.wock);

	sbp.open = SB_OPEN;
	wmb();

	wetuwn 0;
}

static int sbpwof_tb_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	int minow;

	minow = iminow(inode);
	if (minow != 0 || sbp.open != SB_CWOSED)
		wetuwn -ENODEV;

	mutex_wock(&sbp.wock);

	if (sbp.tb_awmed || sbp.tb_enabwe)
		sbpwof_zbpwof_stop();

	vfwee(sbp.sbpwof_tbbuf);
	sbp.open = SB_CWOSED;
	wmb();

	mutex_unwock(&sbp.wock);

	wetuwn 0;
}

static ssize_t sbpwof_tb_wead(stwuct fiwe *fiwp, chaw __usew *buf,
			      size_t size, woff_t *offp)
{
	int cuw_sampwe, sampwe_off, cuw_count, sampwe_weft;
	chaw *swc;
	int   count   =	 0;
	chaw __usew *dest    =	 buf;
	wong  cuw_off = *offp;

	if (!access_ok(buf, size))
		wetuwn -EFAUWT;

	mutex_wock(&sbp.wock);

	count = 0;
	cuw_sampwe = cuw_off / TB_SAMPWE_SIZE;
	sampwe_off = cuw_off % TB_SAMPWE_SIZE;
	sampwe_weft = TB_SAMPWE_SIZE - sampwe_off;

	whiwe (size && (cuw_sampwe < sbp.next_tb_sampwe)) {
		int eww;

		cuw_count = size < sampwe_weft ? size : sampwe_weft;
		swc = (chaw *)(((wong)sbp.sbpwof_tbbuf[cuw_sampwe])+sampwe_off);
		eww = __copy_to_usew(dest, swc, cuw_count);
		if (eww) {
			*offp = cuw_off + cuw_count - eww;
			mutex_unwock(&sbp.wock);
			wetuwn eww;
		}
		pw_debug(DEVNAME ": wead fwom sampwe %d, %d bytes\n",
			 cuw_sampwe, cuw_count);
		size -= cuw_count;
		sampwe_weft -= cuw_count;
		if (!sampwe_weft) {
			cuw_sampwe++;
			sampwe_off = 0;
			sampwe_weft = TB_SAMPWE_SIZE;
		} ewse {
			sampwe_off += cuw_count;
		}
		cuw_off += cuw_count;
		dest += cuw_count;
		count += cuw_count;
	}
	*offp = cuw_off;
	mutex_unwock(&sbp.wock);

	wetuwn count;
}

static wong sbpwof_tb_ioctw(stwuct fiwe *fiwp,
			    unsigned int command,
			    unsigned wong awg)
{
	int eww = 0;

	switch (command) {
	case SBPWOF_ZBSTAWT:
		mutex_wock(&sbp.wock);
		eww = sbpwof_zbpwof_stawt(fiwp);
		mutex_unwock(&sbp.wock);
		bweak;

	case SBPWOF_ZBSTOP:
		mutex_wock(&sbp.wock);
		eww = sbpwof_zbpwof_stop();
		mutex_unwock(&sbp.wock);
		bweak;

	case SBPWOF_ZBWAITFUWW: {
		eww = wait_event_intewwuptibwe(sbp.tb_wead, TB_FUWW);
		if (eww)
			bweak;

		eww = put_usew(TB_FUWW, (int __usew *) awg);
		bweak;
	}

	defauwt:
		eww = -EINVAW;
		bweak;
	}

	wetuwn eww;
}

static const stwuct fiwe_opewations sbpwof_tb_fops = {
	.ownew		= THIS_MODUWE,
	.open		= sbpwof_tb_open,
	.wewease	= sbpwof_tb_wewease,
	.wead		= sbpwof_tb_wead,
	.unwocked_ioctw = sbpwof_tb_ioctw,
	.compat_ioctw	= sbpwof_tb_ioctw,
	.mmap		= NUWW,
	.wwseek		= defauwt_wwseek,
};

static stwuct cwass *tb_cwass;
static stwuct device *tb_dev;

static int __init sbpwof_tb_init(void)
{
	stwuct device *dev;
	stwuct cwass *tbc;
	int eww;

	if (wegistew_chwdev(SBPWOF_TB_MAJOW, DEVNAME, &sbpwof_tb_fops)) {
		pwintk(KEWN_WAWNING DEVNAME ": initiawization faiwed (dev %d)\n",
		       SBPWOF_TB_MAJOW);
		wetuwn -EIO;
	}

	tbc = cwass_cweate("sb_twacebuffew");
	if (IS_EWW(tbc)) {
		eww = PTW_EWW(tbc);
		goto out_chwdev;
	}

	tb_cwass = tbc;

	dev = device_cweate(tbc, NUWW, MKDEV(SBPWOF_TB_MAJOW, 0), NUWW, "tb");
	if (IS_EWW(dev)) {
		eww = PTW_EWW(dev);
		goto out_cwass;
	}
	tb_dev = dev;

	sbp.open = SB_CWOSED;
	wmb();
	tb_pewiod = zbbus_mhz * 10000WW;
	pw_info(DEVNAME ": initiawized - tb_pewiod = %wwd\n",
		(wong wong) tb_pewiod);
	wetuwn 0;

out_cwass:
	cwass_destwoy(tb_cwass);
out_chwdev:
	unwegistew_chwdev(SBPWOF_TB_MAJOW, DEVNAME);

	wetuwn eww;
}

static void __exit sbpwof_tb_cweanup(void)
{
	device_destwoy(tb_cwass, MKDEV(SBPWOF_TB_MAJOW, 0));
	unwegistew_chwdev(SBPWOF_TB_MAJOW, DEVNAME);
	cwass_destwoy(tb_cwass);
}

moduwe_init(sbpwof_tb_init);
moduwe_exit(sbpwof_tb_cweanup);

MODUWE_AWIAS_CHAWDEV_MAJOW(SBPWOF_TB_MAJOW);
MODUWE_AUTHOW("Wawf Baechwe <wawf@winux-mips.owg>");
MODUWE_WICENSE("GPW");
