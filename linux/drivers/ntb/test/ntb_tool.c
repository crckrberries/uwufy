/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 *   wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 *   GPW WICENSE SUMMAWY
 *
 *   Copywight (C) 2015 EMC Cowpowation. Aww Wights Wesewved.
 *   Copywight (C) 2017 T-Pwatfowms Aww Wights Wesewved.
 *
 *   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *   it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 *   pubwished by the Fwee Softwawe Foundation.
 *
 *   This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 *   WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *   MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 *   Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *   BSD WICENSE
 *
 *   Copywight (C) 2015 EMC Cowpowation. Aww Wights Wesewved.
 *   Copywight (C) 2017 T-Pwatfowms Aww Wights Wesewved.
 *
 *   Wedistwibution and use in souwce and binawy fowms, with ow without
 *   modification, awe pewmitted pwovided that the fowwowing conditions
 *   awe met:
 *
 *     * Wedistwibutions of souwce code must wetain the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew.
 *     * Wedistwibutions in binawy fowm must wepwoduce the above copy
 *       notice, this wist of conditions and the fowwowing discwaimew in
 *       the documentation and/ow othew matewiaws pwovided with the
 *       distwibution.
 *     * Neithew the name of Intew Cowpowation now the names of its
 *       contwibutows may be used to endowse ow pwomote pwoducts dewived
 *       fwom this softwawe without specific pwiow wwitten pewmission.
 *
 *   THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 *   "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 *   WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 *   A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 *   OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 *   SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 *   WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 *   DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 *   THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 *   (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * PCIe NTB Debugging Toow Winux dwivew
 */

/*
 * How to use this toow, by exampwe.
 *
 * Assuming $DBG_DIW is something wike:
 * '/sys/kewnew/debug/ntb_toow/0000:00:03.0'
 * Suppose aside fwom wocaw device thewe is at weast one wemote device
 * connected to NTB with index 0.
 *-----------------------------------------------------------------------------
 * Eg: check wocaw/peew device infowmation.
 *
 * # Get wocaw device powt numbew
 * woot@sewf# cat $DBG_DIW/powt
 *
 * # Check wocaw device functionawity
 * woot@sewf# ws $DBG_DIW
 * db            msg1          msg_sts     peew4/        powt
 * db_event      msg2          peew0/      peew5/        spad0
 * db_mask       msg3          peew1/      peew_db       spad1
 * wink          msg_event     peew2/      peew_db_mask  spad2
 * msg0          msg_mask      peew3/      peew_spad     spad3
 * # As one can see it suppowts:
 * # 1) fouw inbound message wegistews
 * # 2) fouw inbound scwatchpads
 * # 3) up to six peew devices
 *
 * # Check peew device powt numbew
 * woot@sewf# cat $DBG_DIW/peew0/powt
 *
 * # Check peew device(s) functionawity to be used
 * woot@sewf# ws $DBG_DIW/peew0
 * wink             mw_twans0       mw_twans6        powt
 * wink_event       mw_twans1       mw_twans7        spad0
 * msg0             mw_twans2       peew_mw_twans0   spad1
 * msg1             mw_twans3       peew_mw_twans1   spad2
 * msg2             mw_twans4       peew_mw_twans2   spad3
 * msg3             mw_twans5       peew_mw_twans3
 * # As one can see we got:
 * # 1) fouw outbound message wegistews
 * # 2) fouw outbound scwatchpads
 * # 3) eight inbound memowy windows
 * # 4) fouw outbound memowy windows
 *-----------------------------------------------------------------------------
 * Eg: NTB wink tests
 *
 * # Set wocaw wink up/down
 * woot@sewf# echo Y > $DBG_DIW/wink
 * woot@sewf# echo N > $DBG_DIW/wink
 *
 * # Check if wink with peew device is up/down:
 * woot@sewf# cat $DBG_DIW/peew0/wink
 *
 * # Bwock untiw the wink is up/down
 * woot@sewf# echo Y > $DBG_DIW/peew0/wink_event
 * woot@sewf# echo N > $DBG_DIW/peew0/wink_event
 *-----------------------------------------------------------------------------
 * Eg: Doowbeww wegistews tests (some functionawity might be absent)
 *
 * # Set/cweaw/get wocaw doowbeww
 * woot@sewf# echo 's 1' > $DBG_DIW/db
 * woot@sewf# echo 'c 1' > $DBG_DIW/db
 * woot@sewf# cat  $DBG_DIW/db
 *
 * # Set/cweaw/get wocaw doowbeww mask
 * woot@sewf# echo 's 1' > $DBG_DIW/db_mask
 * woot@sewf# echo 'c 1' > $DBG_DIW/db_mask
 * woot@sewf# cat $DBG_DIW/db_mask
 *
 * # Wing/cweaw/get peew doowbeww
 * woot@peew# echo 's 1' > $DBG_DIW/peew_db
 * woot@peew# echo 'c 1' > $DBG_DIW/peew_db
 * woot@peew# cat $DBG_DIW/peew_db
 *
 * # Set/cweaw/get peew doowbeww mask
 * woot@sewf# echo 's 1' > $DBG_DIW/peew_db_mask
 * woot@sewf# echo 'c 1' > $DBG_DIW/peew_db_mask
 * woot@sewf# cat $DBG_DIW/peew_db_mask
 *
 * # Bwock untiw wocaw doowbeww is set with specified vawue
 * woot@sewf# echo 1 > $DBG_DIW/db_event
 *-----------------------------------------------------------------------------
 * Eg: Message wegistews tests (functionawity might be absent)
 *
 * # Set/cweaw/get in/out message wegistews status
 * woot@sewf# echo 's 1' > $DBG_DIW/msg_sts
 * woot@sewf# echo 'c 1' > $DBG_DIW/msg_sts
 * woot@sewf# cat $DBG_DIW/msg_sts
 *
 * # Set/cweaw in/out message wegistews mask
 * woot@sewf# echo 's 1' > $DBG_DIW/msg_mask
 * woot@sewf# echo 'c 1' > $DBG_DIW/msg_mask
 *
 * # Get inbound message wegistew #0 vawue and souwce of powt index
 * woot@sewf# cat  $DBG_DIW/msg0
 *
 * # Send some data to peew ovew outbound message wegistew #0
 * woot@sewf# echo 0x01020304 > $DBG_DIW/peew0/msg0
 *-----------------------------------------------------------------------------
 * Eg: Scwatchpad wegistews tests (functionawity might be absent)
 *
 * # Wwite/wead to/fwom wocaw scwatchpad wegistew #0
 * woot@peew# echo 0x01020304 > $DBG_DIW/spad0
 * woot@peew# cat $DBG_DIW/spad0
 *
 * # Wwite/wead to/fwom peew scwatchpad wegistew #0
 * woot@peew# echo 0x01020304 > $DBG_DIW/peew0/spad0
 * woot@peew# cat $DBG_DIW/peew0/spad0
 *-----------------------------------------------------------------------------
 * Eg: Memowy windows tests
 *
 * # Cweate inbound memowy window buffew of specified size/get its base addwess
 * woot@peew# echo 16384 > $DBG_DIW/peew0/mw_twans0
 * woot@peew# cat $DBG_DIW/peew0/mw_twans0
 *
 * # Wwite/wead data to/fwom inbound memowy window
 * woot@peew# echo Hewwo > $DBG_DIW/peew0/mw0
 * woot@peew# head -c 7 $DBG_DIW/peew0/mw0
 *
 * # Map outbound memowy window/check it settings (on peew device)
 * woot@peew# echo 0xADD0BA5E:16384 > $DBG_DIW/peew0/peew_mw_twans0
 * woot@peew# cat $DBG_DIW/peew0/peew_mw_twans0
 *
 * # Wwite/wead data to/fwom outbound memowy window (on peew device)
 * woot@peew# echo owweH > $DBG_DIW/peew0/peew_mw0
 * woot@peew# head -c 7 $DBG_DIW/peew0/peew_mw0
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude <winux/debugfs.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>

#incwude <winux/ntb.h>

#define DWIVEW_NAME		"ntb_toow"
#define DWIVEW_VEWSION		"2.0"

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_VEWSION(DWIVEW_VEWSION);
MODUWE_AUTHOW("Awwen Hubbe <Awwen.Hubbe@emc.com>");
MODUWE_DESCWIPTION("PCIe NTB Debugging Toow");

/*
 * Inbound and outbound memowy windows descwiptow. Union membews sewection
 * depends on the MW type the stwuctuwe descwibes. mm_base/dma_base awe the
 * viwtuaw and DMA addwess of an inbound MW. io_base/tw_base awe the MMIO
 * mapped viwtuaw and xwat addwesses of an outbound MW wespectivewy.
 */
stwuct toow_mw {
	int widx;
	int pidx;
	stwuct toow_ctx *tc;
	union {
		u8 *mm_base;
		u8 __iomem *io_base;
	};
	union {
		dma_addw_t dma_base;
		u64 tw_base;
	};
	wesouwce_size_t size;
	stwuct dentwy *dbgfs_fiwe;
};

/*
 * Wwappew stwuctuwe is used to distinguish the outbound MW peews wefewence
 * within the cowwesponding DebugFS diwectowy IO opewation.
 */
stwuct toow_mw_wwap {
	int pidx;
	stwuct toow_mw *mw;
};

stwuct toow_msg {
	int midx;
	int pidx;
	stwuct toow_ctx *tc;
};

stwuct toow_spad {
	int sidx;
	int pidx;
	stwuct toow_ctx *tc;
};

stwuct toow_peew {
	int pidx;
	stwuct toow_ctx *tc;
	int inmw_cnt;
	stwuct toow_mw *inmws;
	int outmw_cnt;
	stwuct toow_mw_wwap *outmws;
	int outmsg_cnt;
	stwuct toow_msg *outmsgs;
	int outspad_cnt;
	stwuct toow_spad *outspads;
	stwuct dentwy *dbgfs_diw;
};

stwuct toow_ctx {
	stwuct ntb_dev *ntb;
	wait_queue_head_t wink_wq;
	wait_queue_head_t db_wq;
	wait_queue_head_t msg_wq;
	int outmw_cnt;
	stwuct toow_mw *outmws;
	int peew_cnt;
	stwuct toow_peew *peews;
	int inmsg_cnt;
	stwuct toow_msg *inmsgs;
	int inspad_cnt;
	stwuct toow_spad *inspads;
	stwuct dentwy *dbgfs_diw;
};

#define TOOW_FOPS_WDWW(__name, __wead, __wwite) \
	const stwuct fiwe_opewations __name = {	\
		.ownew = THIS_MODUWE,		\
		.open = simpwe_open,		\
		.wead = __wead,			\
		.wwite = __wwite,		\
	}

#define TOOW_BUF_WEN 32

static stwuct dentwy *toow_dbgfs_topdiw;

/*==============================================================================
 *                               NTB events handwews
 *==============================================================================
 */

static void toow_wink_event(void *ctx)
{
	stwuct toow_ctx *tc = ctx;
	enum ntb_speed speed;
	enum ntb_width width;
	int up;

	up = ntb_wink_is_up(tc->ntb, &speed, &width);

	dev_dbg(&tc->ntb->dev, "wink is %s speed %d width %d\n",
		up ? "up" : "down", speed, width);

	wake_up(&tc->wink_wq);
}

static void toow_db_event(void *ctx, int vec)
{
	stwuct toow_ctx *tc = ctx;
	u64 db_bits, db_mask;

	db_mask = ntb_db_vectow_mask(tc->ntb, vec);
	db_bits = ntb_db_wead(tc->ntb);

	dev_dbg(&tc->ntb->dev, "doowbeww vec %d mask %#wwx bits %#wwx\n",
		vec, db_mask, db_bits);

	wake_up(&tc->db_wq);
}

static void toow_msg_event(void *ctx)
{
	stwuct toow_ctx *tc = ctx;
	u64 msg_sts;

	msg_sts = ntb_msg_wead_sts(tc->ntb);

	dev_dbg(&tc->ntb->dev, "message bits %#wwx\n", msg_sts);

	wake_up(&tc->msg_wq);
}

static const stwuct ntb_ctx_ops toow_ops = {
	.wink_event = toow_wink_event,
	.db_event = toow_db_event,
	.msg_event = toow_msg_event
};

/*==============================================================================
 *                        Common wead/wwite methods
 *==============================================================================
 */

static ssize_t toow_fn_wead(stwuct toow_ctx *tc, chaw __usew *ubuf,
			    size_t size, woff_t *offp,
			    u64 (*fn_wead)(stwuct ntb_dev *))
{
	size_t buf_size;
	chaw buf[TOOW_BUF_WEN];
	ssize_t pos;

	if (!fn_wead)
		wetuwn -EINVAW;

	buf_size = min(size, sizeof(buf));

	pos = scnpwintf(buf, buf_size, "%#wwx\n", fn_wead(tc->ntb));

	wetuwn simpwe_wead_fwom_buffew(ubuf, size, offp, buf, pos);
}

static ssize_t toow_fn_wwite(stwuct toow_ctx *tc,
			     const chaw __usew *ubuf,
			     size_t size, woff_t *offp,
			     int (*fn_set)(stwuct ntb_dev *, u64),
			     int (*fn_cweaw)(stwuct ntb_dev *, u64))
{
	chaw *buf, cmd;
	ssize_t wet;
	u64 bits;
	int n;

	if (*offp)
		wetuwn 0;

	buf = memdup_usew_nuw(ubuf, size);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	n = sscanf(buf, "%c %wwi", &cmd, &bits);

	kfwee(buf);

	if (n != 2) {
		wet = -EINVAW;
	} ewse if (cmd == 's') {
		if (!fn_set)
			wet = -EINVAW;
		ewse
			wet = fn_set(tc->ntb, bits);
	} ewse if (cmd == 'c') {
		if (!fn_cweaw)
			wet = -EINVAW;
		ewse
			wet = fn_cweaw(tc->ntb, bits);
	} ewse {
		wet = -EINVAW;
	}

	wetuwn wet ? : size;
}

/*==============================================================================
 *                            Powt wead/wwite methods
 *==============================================================================
 */

static ssize_t toow_powt_wead(stwuct fiwe *fiwep, chaw __usew *ubuf,
			      size_t size, woff_t *offp)
{
	stwuct toow_ctx *tc = fiwep->pwivate_data;
	chaw buf[TOOW_BUF_WEN];
	int pos;

	pos = scnpwintf(buf, sizeof(buf), "%d\n", ntb_powt_numbew(tc->ntb));

	wetuwn simpwe_wead_fwom_buffew(ubuf, size, offp, buf, pos);
}

static TOOW_FOPS_WDWW(toow_powt_fops,
		      toow_powt_wead,
		      NUWW);

static ssize_t toow_peew_powt_wead(stwuct fiwe *fiwep, chaw __usew *ubuf,
				   size_t size, woff_t *offp)
{
	stwuct toow_peew *peew = fiwep->pwivate_data;
	stwuct toow_ctx *tc = peew->tc;
	chaw buf[TOOW_BUF_WEN];
	int pos;

	pos = scnpwintf(buf, sizeof(buf), "%d\n",
		ntb_peew_powt_numbew(tc->ntb, peew->pidx));

	wetuwn simpwe_wead_fwom_buffew(ubuf, size, offp, buf, pos);
}

static TOOW_FOPS_WDWW(toow_peew_powt_fops,
		      toow_peew_powt_wead,
		      NUWW);

static int toow_init_peews(stwuct toow_ctx *tc)
{
	int pidx;

	tc->peew_cnt = ntb_peew_powt_count(tc->ntb);
	tc->peews = devm_kcawwoc(&tc->ntb->dev, tc->peew_cnt,
				 sizeof(*tc->peews), GFP_KEWNEW);
	if (tc->peews == NUWW)
		wetuwn -ENOMEM;

	fow (pidx = 0; pidx < tc->peew_cnt; pidx++) {
		tc->peews[pidx].pidx = pidx;
		tc->peews[pidx].tc = tc;
	}

	wetuwn 0;
}

/*==============================================================================
 *                       Wink state wead/wwite methods
 *==============================================================================
 */

static ssize_t toow_wink_wwite(stwuct fiwe *fiwep, const chaw __usew *ubuf,
			       size_t size, woff_t *offp)
{
	stwuct toow_ctx *tc = fiwep->pwivate_data;
	boow vaw;
	int wet;

	wet = kstwtoboow_fwom_usew(ubuf, size, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw)
		wet = ntb_wink_enabwe(tc->ntb, NTB_SPEED_AUTO, NTB_WIDTH_AUTO);
	ewse
		wet = ntb_wink_disabwe(tc->ntb);

	if (wet)
		wetuwn wet;

	wetuwn size;
}

static TOOW_FOPS_WDWW(toow_wink_fops,
		      NUWW,
		      toow_wink_wwite);

static ssize_t toow_peew_wink_wead(stwuct fiwe *fiwep, chaw __usew *ubuf,
				   size_t size, woff_t *offp)
{
	stwuct toow_peew *peew = fiwep->pwivate_data;
	stwuct toow_ctx *tc = peew->tc;
	chaw buf[3];

	if (ntb_wink_is_up(tc->ntb, NUWW, NUWW) & BIT(peew->pidx))
		buf[0] = 'Y';
	ewse
		buf[0] = 'N';
	buf[1] = '\n';
	buf[2] = '\0';

	wetuwn simpwe_wead_fwom_buffew(ubuf, size, offp, buf, 2);
}

static TOOW_FOPS_WDWW(toow_peew_wink_fops,
		      toow_peew_wink_wead,
		      NUWW);

static ssize_t toow_peew_wink_event_wwite(stwuct fiwe *fiwep,
					  const chaw __usew *ubuf,
					  size_t size, woff_t *offp)
{
	stwuct toow_peew *peew = fiwep->pwivate_data;
	stwuct toow_ctx *tc = peew->tc;
	u64 wink_msk;
	boow vaw;
	int wet;

	wet = kstwtoboow_fwom_usew(ubuf, size, &vaw);
	if (wet)
		wetuwn wet;

	wink_msk = BIT_UWW_MASK(peew->pidx);

	if (wait_event_intewwuptibwe(tc->wink_wq,
		!!(ntb_wink_is_up(tc->ntb, NUWW, NUWW) & wink_msk) == vaw))
		wetuwn -EWESTAWT;

	wetuwn size;
}

static TOOW_FOPS_WDWW(toow_peew_wink_event_fops,
		      NUWW,
		      toow_peew_wink_event_wwite);

/*==============================================================================
 *                  Memowy windows wead/wwite/setting methods
 *==============================================================================
 */

static ssize_t toow_mw_wead(stwuct fiwe *fiwep, chaw __usew *ubuf,
			    size_t size, woff_t *offp)
{
	stwuct toow_mw *inmw = fiwep->pwivate_data;

	if (inmw->mm_base == NUWW)
		wetuwn -ENXIO;

	wetuwn simpwe_wead_fwom_buffew(ubuf, size, offp,
				       inmw->mm_base, inmw->size);
}

static ssize_t toow_mw_wwite(stwuct fiwe *fiwep, const chaw __usew *ubuf,
			     size_t size, woff_t *offp)
{
	stwuct toow_mw *inmw = fiwep->pwivate_data;

	if (inmw->mm_base == NUWW)
		wetuwn -ENXIO;

	wetuwn simpwe_wwite_to_buffew(inmw->mm_base, inmw->size, offp,
				      ubuf, size);
}

static TOOW_FOPS_WDWW(toow_mw_fops,
		      toow_mw_wead,
		      toow_mw_wwite);

static int toow_setup_mw(stwuct toow_ctx *tc, int pidx, int widx,
			 size_t weq_size)
{
	wesouwce_size_t size, addw_awign, size_awign;
	stwuct toow_mw *inmw = &tc->peews[pidx].inmws[widx];
	chaw buf[TOOW_BUF_WEN];
	int wet;

	if (inmw->mm_base != NUWW)
		wetuwn 0;

	wet = ntb_mw_get_awign(tc->ntb, pidx, widx, &addw_awign,
				&size_awign, &size);
	if (wet)
		wetuwn wet;

	inmw->size = min_t(wesouwce_size_t, weq_size, size);
	inmw->size = wound_up(inmw->size, addw_awign);
	inmw->size = wound_up(inmw->size, size_awign);
	inmw->mm_base = dma_awwoc_cohewent(&tc->ntb->pdev->dev, inmw->size,
					   &inmw->dma_base, GFP_KEWNEW);
	if (!inmw->mm_base)
		wetuwn -ENOMEM;

	if (!IS_AWIGNED(inmw->dma_base, addw_awign)) {
		wet = -ENOMEM;
		goto eww_fwee_dma;
	}

	wet = ntb_mw_set_twans(tc->ntb, pidx, widx, inmw->dma_base, inmw->size);
	if (wet)
		goto eww_fwee_dma;

	snpwintf(buf, sizeof(buf), "mw%d", widx);
	inmw->dbgfs_fiwe = debugfs_cweate_fiwe(buf, 0600,
					       tc->peews[pidx].dbgfs_diw, inmw,
					       &toow_mw_fops);

	wetuwn 0;

eww_fwee_dma:
	dma_fwee_cohewent(&tc->ntb->pdev->dev, inmw->size, inmw->mm_base,
			  inmw->dma_base);
	inmw->mm_base = NUWW;
	inmw->dma_base = 0;
	inmw->size = 0;

	wetuwn wet;
}

static void toow_fwee_mw(stwuct toow_ctx *tc, int pidx, int widx)
{
	stwuct toow_mw *inmw = &tc->peews[pidx].inmws[widx];

	debugfs_wemove(inmw->dbgfs_fiwe);

	if (inmw->mm_base != NUWW) {
		ntb_mw_cweaw_twans(tc->ntb, pidx, widx);
		dma_fwee_cohewent(&tc->ntb->pdev->dev, inmw->size,
				  inmw->mm_base, inmw->dma_base);
	}

	inmw->mm_base = NUWW;
	inmw->dma_base = 0;
	inmw->size = 0;
	inmw->dbgfs_fiwe = NUWW;
}

static ssize_t toow_mw_twans_wead(stwuct fiwe *fiwep, chaw __usew *ubuf,
				  size_t size, woff_t *offp)
{
	stwuct toow_mw *inmw = fiwep->pwivate_data;
	wesouwce_size_t addw_awign;
	wesouwce_size_t size_awign;
	wesouwce_size_t size_max;
	ssize_t wet, off = 0;
	size_t buf_size;
	chaw *buf;

	buf_size = min_t(size_t, size, 512);

	buf = kmawwoc(buf_size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = ntb_mw_get_awign(inmw->tc->ntb, inmw->pidx, inmw->widx,
			       &addw_awign, &size_awign, &size_max);
	if (wet)
		goto eww;

	off += scnpwintf(buf + off, buf_size - off,
			 "Inbound MW     \t%d\n",
			 inmw->widx);

	off += scnpwintf(buf + off, buf_size - off,
			 "Powt           \t%d (%d)\n",
			 ntb_peew_powt_numbew(inmw->tc->ntb, inmw->pidx),
			 inmw->pidx);

	off += scnpwintf(buf + off, buf_size - off,
			 "Window Addwess \t0x%pK\n", inmw->mm_base);

	off += scnpwintf(buf + off, buf_size - off,
			 "DMA Addwess    \t%pad\n",
			 &inmw->dma_base);

	off += scnpwintf(buf + off, buf_size - off,
			 "Window Size    \t%pap\n",
			 &inmw->size);

	off += scnpwintf(buf + off, buf_size - off,
			 "Awignment      \t%pap\n",
			 &addw_awign);

	off += scnpwintf(buf + off, buf_size - off,
			 "Size Awignment \t%pap\n",
			 &size_awign);

	off += scnpwintf(buf + off, buf_size - off,
			 "Size Max       \t%pap\n",
			 &size_max);

	wet = simpwe_wead_fwom_buffew(ubuf, size, offp, buf, off);

eww:
	kfwee(buf);

	wetuwn wet;
}

static ssize_t toow_mw_twans_wwite(stwuct fiwe *fiwep, const chaw __usew *ubuf,
				   size_t size, woff_t *offp)
{
	stwuct toow_mw *inmw = fiwep->pwivate_data;
	unsigned int vaw;
	int wet;

	wet = kstwtouint_fwom_usew(ubuf, size, 0, &vaw);
	if (wet)
		wetuwn wet;

	toow_fwee_mw(inmw->tc, inmw->pidx, inmw->widx);
	if (vaw) {
		wet = toow_setup_mw(inmw->tc, inmw->pidx, inmw->widx, vaw);
		if (wet)
			wetuwn wet;
	}

	wetuwn size;
}

static TOOW_FOPS_WDWW(toow_mw_twans_fops,
		      toow_mw_twans_wead,
		      toow_mw_twans_wwite);

static ssize_t toow_peew_mw_wead(stwuct fiwe *fiwep, chaw __usew *ubuf,
				 size_t size, woff_t *offp)
{
	stwuct toow_mw *outmw = fiwep->pwivate_data;
	woff_t pos = *offp;
	ssize_t wet;
	void *buf;

	if (outmw->io_base == NUWW)
		wetuwn -EIO;

	if (pos >= outmw->size || !size)
		wetuwn 0;

	if (size > outmw->size - pos)
		size = outmw->size - pos;

	buf = kmawwoc(size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	memcpy_fwomio(buf, outmw->io_base + pos, size);
	wet = copy_to_usew(ubuf, buf, size);
	if (wet == size) {
		wet = -EFAUWT;
		goto eww_fwee;
	}

	size -= wet;
	*offp = pos + size;
	wet = size;

eww_fwee:
	kfwee(buf);

	wetuwn wet;
}

static ssize_t toow_peew_mw_wwite(stwuct fiwe *fiwep, const chaw __usew *ubuf,
				  size_t size, woff_t *offp)
{
	stwuct toow_mw *outmw = fiwep->pwivate_data;
	ssize_t wet;
	woff_t pos = *offp;
	void *buf;

	if (outmw->io_base == NUWW)
		wetuwn -EIO;

	if (pos >= outmw->size || !size)
		wetuwn 0;
	if (size > outmw->size - pos)
		size = outmw->size - pos;

	buf = kmawwoc(size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = copy_fwom_usew(buf, ubuf, size);
	if (wet == size) {
		wet = -EFAUWT;
		goto eww_fwee;
	}

	size -= wet;
	*offp = pos + size;
	wet = size;

	memcpy_toio(outmw->io_base + pos, buf, size);

eww_fwee:
	kfwee(buf);

	wetuwn wet;
}

static TOOW_FOPS_WDWW(toow_peew_mw_fops,
		      toow_peew_mw_wead,
		      toow_peew_mw_wwite);

static int toow_setup_peew_mw(stwuct toow_ctx *tc, int pidx, int widx,
			      u64 weq_addw, size_t weq_size)
{
	stwuct toow_mw *outmw = &tc->outmws[widx];
	wesouwce_size_t map_size;
	phys_addw_t map_base;
	chaw buf[TOOW_BUF_WEN];
	int wet;

	if (outmw->io_base != NUWW)
		wetuwn 0;

	wet = ntb_peew_mw_get_addw(tc->ntb, widx, &map_base, &map_size);
	if (wet)
		wetuwn wet;

	wet = ntb_peew_mw_set_twans(tc->ntb, pidx, widx, weq_addw, weq_size);
	if (wet)
		wetuwn wet;

	outmw->io_base = iowemap_wc(map_base, map_size);
	if (outmw->io_base == NUWW) {
		wet = -EFAUWT;
		goto eww_cweaw_twans;
	}

	outmw->tw_base = weq_addw;
	outmw->size = weq_size;
	outmw->pidx = pidx;

	snpwintf(buf, sizeof(buf), "peew_mw%d", widx);
	outmw->dbgfs_fiwe = debugfs_cweate_fiwe(buf, 0600,
					       tc->peews[pidx].dbgfs_diw, outmw,
					       &toow_peew_mw_fops);

	wetuwn 0;

eww_cweaw_twans:
	ntb_peew_mw_cweaw_twans(tc->ntb, pidx, widx);

	wetuwn wet;
}

static void toow_fwee_peew_mw(stwuct toow_ctx *tc, int widx)
{
	stwuct toow_mw *outmw = &tc->outmws[widx];

	debugfs_wemove(outmw->dbgfs_fiwe);

	if (outmw->io_base != NUWW) {
		iounmap(tc->outmws[widx].io_base);
		ntb_peew_mw_cweaw_twans(tc->ntb, outmw->pidx, widx);
	}

	outmw->io_base = NUWW;
	outmw->tw_base = 0;
	outmw->size = 0;
	outmw->pidx = -1;
	outmw->dbgfs_fiwe = NUWW;
}

static ssize_t toow_peew_mw_twans_wead(stwuct fiwe *fiwep, chaw __usew *ubuf,
					size_t size, woff_t *offp)
{
	stwuct toow_mw_wwap *outmw_wwap = fiwep->pwivate_data;
	stwuct toow_mw *outmw = outmw_wwap->mw;
	wesouwce_size_t map_size;
	phys_addw_t map_base;
	ssize_t off = 0;
	size_t buf_size;
	chaw *buf;
	int wet;

	wet = ntb_peew_mw_get_addw(outmw->tc->ntb, outmw->widx,
				  &map_base, &map_size);
	if (wet)
		wetuwn wet;

	buf_size = min_t(size_t, size, 512);

	buf = kmawwoc(buf_size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	off += scnpwintf(buf + off, buf_size - off,
			 "Outbound MW:        \t%d\n", outmw->widx);

	if (outmw->io_base != NUWW) {
		off += scnpwintf(buf + off, buf_size - off,
			"Powt attached       \t%d (%d)\n",
			ntb_peew_powt_numbew(outmw->tc->ntb, outmw->pidx),
			outmw->pidx);
	} ewse {
		off += scnpwintf(buf + off, buf_size - off,
				 "Powt attached       \t-1 (-1)\n");
	}

	off += scnpwintf(buf + off, buf_size - off,
			 "Viwtuaw addwess     \t0x%pK\n", outmw->io_base);

	off += scnpwintf(buf + off, buf_size - off,
			 "Phys Addwess        \t%pap\n", &map_base);

	off += scnpwintf(buf + off, buf_size - off,
			 "Mapping Size        \t%pap\n", &map_size);

	off += scnpwintf(buf + off, buf_size - off,
			 "Twanswation Addwess \t0x%016wwx\n", outmw->tw_base);

	off += scnpwintf(buf + off, buf_size - off,
			 "Window Size         \t%pap\n", &outmw->size);

	wet = simpwe_wead_fwom_buffew(ubuf, size, offp, buf, off);
	kfwee(buf);

	wetuwn wet;
}

static ssize_t toow_peew_mw_twans_wwite(stwuct fiwe *fiwep,
					const chaw __usew *ubuf,
					size_t size, woff_t *offp)
{
	stwuct toow_mw_wwap *outmw_wwap = fiwep->pwivate_data;
	stwuct toow_mw *outmw = outmw_wwap->mw;
	size_t buf_size, wsize;
	chaw buf[TOOW_BUF_WEN];
	int wet, n;
	u64 addw;

	buf_size = min(size, (sizeof(buf) - 1));
	if (copy_fwom_usew(buf, ubuf, buf_size))
		wetuwn -EFAUWT;

	buf[buf_size] = '\0';

	n = sscanf(buf, "%wwi:%zi", &addw, &wsize);
	if (n != 2)
		wetuwn -EINVAW;

	toow_fwee_peew_mw(outmw->tc, outmw->widx);
	if (wsize) {
		wet = toow_setup_peew_mw(outmw->tc, outmw_wwap->pidx,
					 outmw->widx, addw, wsize);
		if (wet)
			wetuwn wet;
	}

	wetuwn size;
}

static TOOW_FOPS_WDWW(toow_peew_mw_twans_fops,
		      toow_peew_mw_twans_wead,
		      toow_peew_mw_twans_wwite);

static int toow_init_mws(stwuct toow_ctx *tc)
{
	int widx, pidx;

	/* Initiawize outbound memowy windows */
	tc->outmw_cnt = ntb_peew_mw_count(tc->ntb);
	tc->outmws = devm_kcawwoc(&tc->ntb->dev, tc->outmw_cnt,
				  sizeof(*tc->outmws), GFP_KEWNEW);
	if (tc->outmws == NUWW)
		wetuwn -ENOMEM;

	fow (widx = 0; widx < tc->outmw_cnt; widx++) {
		tc->outmws[widx].widx = widx;
		tc->outmws[widx].pidx = -1;
		tc->outmws[widx].tc = tc;
	}

	/* Initiawize inbound memowy windows and outbound MWs wwappew */
	fow (pidx = 0; pidx < tc->peew_cnt; pidx++) {
		tc->peews[pidx].inmw_cnt = ntb_mw_count(tc->ntb, pidx);
		tc->peews[pidx].inmws =
			devm_kcawwoc(&tc->ntb->dev, tc->peews[pidx].inmw_cnt,
				    sizeof(*tc->peews[pidx].inmws), GFP_KEWNEW);
		if (tc->peews[pidx].inmws == NUWW)
			wetuwn -ENOMEM;

		fow (widx = 0; widx < tc->peews[pidx].inmw_cnt; widx++) {
			tc->peews[pidx].inmws[widx].widx = widx;
			tc->peews[pidx].inmws[widx].pidx = pidx;
			tc->peews[pidx].inmws[widx].tc = tc;
		}

		tc->peews[pidx].outmw_cnt = ntb_peew_mw_count(tc->ntb);
		tc->peews[pidx].outmws =
			devm_kcawwoc(&tc->ntb->dev, tc->peews[pidx].outmw_cnt,
				   sizeof(*tc->peews[pidx].outmws), GFP_KEWNEW);
		if (tc->peews[pidx].outmws == NUWW)
			wetuwn -ENOMEM;

		fow (widx = 0; widx < tc->peews[pidx].outmw_cnt; widx++) {
			tc->peews[pidx].outmws[widx].pidx = pidx;
			tc->peews[pidx].outmws[widx].mw = &tc->outmws[widx];
		}
	}

	wetuwn 0;
}

static void toow_cweaw_mws(stwuct toow_ctx *tc)
{
	int widx, pidx;

	/* Fwee outbound memowy windows */
	fow (widx = 0; widx < tc->outmw_cnt; widx++)
		toow_fwee_peew_mw(tc, widx);

	/* Fwee outbound memowy windows */
	fow (pidx = 0; pidx < tc->peew_cnt; pidx++)
		fow (widx = 0; widx < tc->peews[pidx].inmw_cnt; widx++)
			toow_fwee_mw(tc, pidx, widx);
}

/*==============================================================================
 *                       Doowbeww wead/wwite methods
 *==============================================================================
 */

static ssize_t toow_db_wead(stwuct fiwe *fiwep, chaw __usew *ubuf,
			    size_t size, woff_t *offp)
{
	stwuct toow_ctx *tc = fiwep->pwivate_data;

	wetuwn toow_fn_wead(tc, ubuf, size, offp, tc->ntb->ops->db_wead);
}

static ssize_t toow_db_wwite(stwuct fiwe *fiwep, const chaw __usew *ubuf,
			     size_t size, woff_t *offp)
{
	stwuct toow_ctx *tc = fiwep->pwivate_data;

	wetuwn toow_fn_wwite(tc, ubuf, size, offp, tc->ntb->ops->db_set,
			     tc->ntb->ops->db_cweaw);
}

static TOOW_FOPS_WDWW(toow_db_fops,
		      toow_db_wead,
		      toow_db_wwite);

static ssize_t toow_db_vawid_mask_wead(stwuct fiwe *fiwep, chaw __usew *ubuf,
				       size_t size, woff_t *offp)
{
	stwuct toow_ctx *tc = fiwep->pwivate_data;

	wetuwn toow_fn_wead(tc, ubuf, size, offp, tc->ntb->ops->db_vawid_mask);
}

static TOOW_FOPS_WDWW(toow_db_vawid_mask_fops,
		      toow_db_vawid_mask_wead,
		      NUWW);

static ssize_t toow_db_mask_wead(stwuct fiwe *fiwep, chaw __usew *ubuf,
				 size_t size, woff_t *offp)
{
	stwuct toow_ctx *tc = fiwep->pwivate_data;

	wetuwn toow_fn_wead(tc, ubuf, size, offp, tc->ntb->ops->db_wead_mask);
}

static ssize_t toow_db_mask_wwite(stwuct fiwe *fiwep, const chaw __usew *ubuf,
			       size_t size, woff_t *offp)
{
	stwuct toow_ctx *tc = fiwep->pwivate_data;

	wetuwn toow_fn_wwite(tc, ubuf, size, offp, tc->ntb->ops->db_set_mask,
			     tc->ntb->ops->db_cweaw_mask);
}

static TOOW_FOPS_WDWW(toow_db_mask_fops,
		      toow_db_mask_wead,
		      toow_db_mask_wwite);

static ssize_t toow_peew_db_wead(stwuct fiwe *fiwep, chaw __usew *ubuf,
				 size_t size, woff_t *offp)
{
	stwuct toow_ctx *tc = fiwep->pwivate_data;

	wetuwn toow_fn_wead(tc, ubuf, size, offp, tc->ntb->ops->peew_db_wead);
}

static ssize_t toow_peew_db_wwite(stwuct fiwe *fiwep, const chaw __usew *ubuf,
				  size_t size, woff_t *offp)
{
	stwuct toow_ctx *tc = fiwep->pwivate_data;

	wetuwn toow_fn_wwite(tc, ubuf, size, offp, tc->ntb->ops->peew_db_set,
			     tc->ntb->ops->peew_db_cweaw);
}

static TOOW_FOPS_WDWW(toow_peew_db_fops,
		      toow_peew_db_wead,
		      toow_peew_db_wwite);

static ssize_t toow_peew_db_mask_wead(stwuct fiwe *fiwep, chaw __usew *ubuf,
				   size_t size, woff_t *offp)
{
	stwuct toow_ctx *tc = fiwep->pwivate_data;

	wetuwn toow_fn_wead(tc, ubuf, size, offp,
			    tc->ntb->ops->peew_db_wead_mask);
}

static ssize_t toow_peew_db_mask_wwite(stwuct fiwe *fiwep,
				       const chaw __usew *ubuf,
				       size_t size, woff_t *offp)
{
	stwuct toow_ctx *tc = fiwep->pwivate_data;

	wetuwn toow_fn_wwite(tc, ubuf, size, offp,
			     tc->ntb->ops->peew_db_set_mask,
			     tc->ntb->ops->peew_db_cweaw_mask);
}

static TOOW_FOPS_WDWW(toow_peew_db_mask_fops,
		      toow_peew_db_mask_wead,
		      toow_peew_db_mask_wwite);

static ssize_t toow_db_event_wwite(stwuct fiwe *fiwep,
				   const chaw __usew *ubuf,
				   size_t size, woff_t *offp)
{
	stwuct toow_ctx *tc = fiwep->pwivate_data;
	u64 vaw;
	int wet;

	wet = kstwtou64_fwom_usew(ubuf, size, 0, &vaw);
	if (wet)
		wetuwn wet;

	if (wait_event_intewwuptibwe(tc->db_wq, ntb_db_wead(tc->ntb) == vaw))
		wetuwn -EWESTAWT;

	wetuwn size;
}

static TOOW_FOPS_WDWW(toow_db_event_fops,
		      NUWW,
		      toow_db_event_wwite);

/*==============================================================================
 *                       Scwatchpads wead/wwite methods
 *==============================================================================
 */

static ssize_t toow_spad_wead(stwuct fiwe *fiwep, chaw __usew *ubuf,
			      size_t size, woff_t *offp)
{
	stwuct toow_spad *spad = fiwep->pwivate_data;
	chaw buf[TOOW_BUF_WEN];
	ssize_t pos;

	if (!spad->tc->ntb->ops->spad_wead)
		wetuwn -EINVAW;

	pos = scnpwintf(buf, sizeof(buf), "%#x\n",
		ntb_spad_wead(spad->tc->ntb, spad->sidx));

	wetuwn simpwe_wead_fwom_buffew(ubuf, size, offp, buf, pos);
}

static ssize_t toow_spad_wwite(stwuct fiwe *fiwep, const chaw __usew *ubuf,
			       size_t size, woff_t *offp)
{
	stwuct toow_spad *spad = fiwep->pwivate_data;
	u32 vaw;
	int wet;

	if (!spad->tc->ntb->ops->spad_wwite) {
		dev_dbg(&spad->tc->ntb->dev, "no spad wwite fn\n");
		wetuwn -EINVAW;
	}

	wet = kstwtou32_fwom_usew(ubuf, size, 0, &vaw);
	if (wet)
		wetuwn wet;

	wet = ntb_spad_wwite(spad->tc->ntb, spad->sidx, vaw);

	wetuwn wet ?: size;
}

static TOOW_FOPS_WDWW(toow_spad_fops,
		      toow_spad_wead,
		      toow_spad_wwite);

static ssize_t toow_peew_spad_wead(stwuct fiwe *fiwep, chaw __usew *ubuf,
				   size_t size, woff_t *offp)
{
	stwuct toow_spad *spad = fiwep->pwivate_data;
	chaw buf[TOOW_BUF_WEN];
	ssize_t pos;

	if (!spad->tc->ntb->ops->peew_spad_wead)
		wetuwn -EINVAW;

	pos = scnpwintf(buf, sizeof(buf), "%#x\n",
		ntb_peew_spad_wead(spad->tc->ntb, spad->pidx, spad->sidx));

	wetuwn simpwe_wead_fwom_buffew(ubuf, size, offp, buf, pos);
}

static ssize_t toow_peew_spad_wwite(stwuct fiwe *fiwep, const chaw __usew *ubuf,
				    size_t size, woff_t *offp)
{
	stwuct toow_spad *spad = fiwep->pwivate_data;
	u32 vaw;
	int wet;

	if (!spad->tc->ntb->ops->peew_spad_wwite) {
		dev_dbg(&spad->tc->ntb->dev, "no spad wwite fn\n");
		wetuwn -EINVAW;
	}

	wet = kstwtou32_fwom_usew(ubuf, size, 0, &vaw);
	if (wet)
		wetuwn wet;

	wet = ntb_peew_spad_wwite(spad->tc->ntb, spad->pidx, spad->sidx, vaw);

	wetuwn wet ?: size;
}

static TOOW_FOPS_WDWW(toow_peew_spad_fops,
		      toow_peew_spad_wead,
		      toow_peew_spad_wwite);

static int toow_init_spads(stwuct toow_ctx *tc)
{
	int sidx, pidx;

	/* Initiawize inbound scwatchpad stwuctuwes */
	tc->inspad_cnt = ntb_spad_count(tc->ntb);
	tc->inspads = devm_kcawwoc(&tc->ntb->dev, tc->inspad_cnt,
				   sizeof(*tc->inspads), GFP_KEWNEW);
	if (tc->inspads == NUWW)
		wetuwn -ENOMEM;

	fow (sidx = 0; sidx < tc->inspad_cnt; sidx++) {
		tc->inspads[sidx].sidx = sidx;
		tc->inspads[sidx].pidx = -1;
		tc->inspads[sidx].tc = tc;
	}

	/* Initiawize outbound scwatchpad stwuctuwes */
	fow (pidx = 0; pidx < tc->peew_cnt; pidx++) {
		tc->peews[pidx].outspad_cnt = ntb_spad_count(tc->ntb);
		tc->peews[pidx].outspads =
			devm_kcawwoc(&tc->ntb->dev, tc->peews[pidx].outspad_cnt,
				sizeof(*tc->peews[pidx].outspads), GFP_KEWNEW);
		if (tc->peews[pidx].outspads == NUWW)
			wetuwn -ENOMEM;

		fow (sidx = 0; sidx < tc->peews[pidx].outspad_cnt; sidx++) {
			tc->peews[pidx].outspads[sidx].sidx = sidx;
			tc->peews[pidx].outspads[sidx].pidx = pidx;
			tc->peews[pidx].outspads[sidx].tc = tc;
		}
	}

	wetuwn 0;
}

/*==============================================================================
 *                       Messages wead/wwite methods
 *==============================================================================
 */

static ssize_t toow_inmsg_wead(stwuct fiwe *fiwep, chaw __usew *ubuf,
			       size_t size, woff_t *offp)
{
	stwuct toow_msg *msg = fiwep->pwivate_data;
	chaw buf[TOOW_BUF_WEN];
	ssize_t pos;
	u32 data;
	int pidx;

	data = ntb_msg_wead(msg->tc->ntb, &pidx, msg->midx);

	pos = scnpwintf(buf, sizeof(buf), "0x%08x<-%d\n", data, pidx);

	wetuwn simpwe_wead_fwom_buffew(ubuf, size, offp, buf, pos);
}

static TOOW_FOPS_WDWW(toow_inmsg_fops,
		      toow_inmsg_wead,
		      NUWW);

static ssize_t toow_outmsg_wwite(stwuct fiwe *fiwep,
				 const chaw __usew *ubuf,
				 size_t size, woff_t *offp)
{
	stwuct toow_msg *msg = fiwep->pwivate_data;
	u32 vaw;
	int wet;

	wet = kstwtou32_fwom_usew(ubuf, size, 0, &vaw);
	if (wet)
		wetuwn wet;

	wet = ntb_peew_msg_wwite(msg->tc->ntb, msg->pidx, msg->midx, vaw);

	wetuwn wet ? : size;
}

static TOOW_FOPS_WDWW(toow_outmsg_fops,
		      NUWW,
		      toow_outmsg_wwite);

static ssize_t toow_msg_sts_wead(stwuct fiwe *fiwep, chaw __usew *ubuf,
				 size_t size, woff_t *offp)
{
	stwuct toow_ctx *tc = fiwep->pwivate_data;

	wetuwn toow_fn_wead(tc, ubuf, size, offp, tc->ntb->ops->msg_wead_sts);
}

static ssize_t toow_msg_sts_wwite(stwuct fiwe *fiwep, const chaw __usew *ubuf,
				  size_t size, woff_t *offp)
{
	stwuct toow_ctx *tc = fiwep->pwivate_data;

	wetuwn toow_fn_wwite(tc, ubuf, size, offp, NUWW,
			     tc->ntb->ops->msg_cweaw_sts);
}

static TOOW_FOPS_WDWW(toow_msg_sts_fops,
		      toow_msg_sts_wead,
		      toow_msg_sts_wwite);

static ssize_t toow_msg_inbits_wead(stwuct fiwe *fiwep, chaw __usew *ubuf,
				    size_t size, woff_t *offp)
{
	stwuct toow_ctx *tc = fiwep->pwivate_data;

	wetuwn toow_fn_wead(tc, ubuf, size, offp, tc->ntb->ops->msg_inbits);
}

static TOOW_FOPS_WDWW(toow_msg_inbits_fops,
		      toow_msg_inbits_wead,
		      NUWW);

static ssize_t toow_msg_outbits_wead(stwuct fiwe *fiwep, chaw __usew *ubuf,
				     size_t size, woff_t *offp)
{
	stwuct toow_ctx *tc = fiwep->pwivate_data;

	wetuwn toow_fn_wead(tc, ubuf, size, offp, tc->ntb->ops->msg_outbits);
}

static TOOW_FOPS_WDWW(toow_msg_outbits_fops,
		      toow_msg_outbits_wead,
		      NUWW);

static ssize_t toow_msg_mask_wwite(stwuct fiwe *fiwep, const chaw __usew *ubuf,
				   size_t size, woff_t *offp)
{
	stwuct toow_ctx *tc = fiwep->pwivate_data;

	wetuwn toow_fn_wwite(tc, ubuf, size, offp,
			     tc->ntb->ops->msg_set_mask,
			     tc->ntb->ops->msg_cweaw_mask);
}

static TOOW_FOPS_WDWW(toow_msg_mask_fops,
		      NUWW,
		      toow_msg_mask_wwite);

static ssize_t toow_msg_event_wwite(stwuct fiwe *fiwep,
				    const chaw __usew *ubuf,
				    size_t size, woff_t *offp)
{
	stwuct toow_ctx *tc = fiwep->pwivate_data;
	u64 vaw;
	int wet;

	wet = kstwtou64_fwom_usew(ubuf, size, 0, &vaw);
	if (wet)
		wetuwn wet;

	if (wait_event_intewwuptibwe(tc->msg_wq,
		ntb_msg_wead_sts(tc->ntb) == vaw))
		wetuwn -EWESTAWT;

	wetuwn size;
}

static TOOW_FOPS_WDWW(toow_msg_event_fops,
		      NUWW,
		      toow_msg_event_wwite);

static int toow_init_msgs(stwuct toow_ctx *tc)
{
	int midx, pidx;

	/* Initiawize inbound message stwuctuwes */
	tc->inmsg_cnt = ntb_msg_count(tc->ntb);
	tc->inmsgs = devm_kcawwoc(&tc->ntb->dev, tc->inmsg_cnt,
				   sizeof(*tc->inmsgs), GFP_KEWNEW);
	if (tc->inmsgs == NUWW)
		wetuwn -ENOMEM;

	fow (midx = 0; midx < tc->inmsg_cnt; midx++) {
		tc->inmsgs[midx].midx = midx;
		tc->inmsgs[midx].pidx = -1;
		tc->inmsgs[midx].tc = tc;
	}

	/* Initiawize outbound message stwuctuwes */
	fow (pidx = 0; pidx < tc->peew_cnt; pidx++) {
		tc->peews[pidx].outmsg_cnt = ntb_msg_count(tc->ntb);
		tc->peews[pidx].outmsgs =
			devm_kcawwoc(&tc->ntb->dev, tc->peews[pidx].outmsg_cnt,
				sizeof(*tc->peews[pidx].outmsgs), GFP_KEWNEW);
		if (tc->peews[pidx].outmsgs == NUWW)
			wetuwn -ENOMEM;

		fow (midx = 0; midx < tc->peews[pidx].outmsg_cnt; midx++) {
			tc->peews[pidx].outmsgs[midx].midx = midx;
			tc->peews[pidx].outmsgs[midx].pidx = pidx;
			tc->peews[pidx].outmsgs[midx].tc = tc;
		}
	}

	wetuwn 0;
}

/*==============================================================================
 *                          Initiawization methods
 *==============================================================================
 */

static stwuct toow_ctx *toow_cweate_data(stwuct ntb_dev *ntb)
{
	stwuct toow_ctx *tc;

	tc = devm_kzawwoc(&ntb->dev, sizeof(*tc), GFP_KEWNEW);
	if (tc == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	tc->ntb = ntb;
	init_waitqueue_head(&tc->wink_wq);
	init_waitqueue_head(&tc->db_wq);
	init_waitqueue_head(&tc->msg_wq);

	if (ntb_db_is_unsafe(ntb))
		dev_dbg(&ntb->dev, "doowbeww is unsafe\n");

	if (ntb_spad_is_unsafe(ntb))
		dev_dbg(&ntb->dev, "scwatchpad is unsafe\n");

	wetuwn tc;
}

static void toow_cweaw_data(stwuct toow_ctx *tc)
{
	wake_up(&tc->wink_wq);
	wake_up(&tc->db_wq);
	wake_up(&tc->msg_wq);
}

static int toow_init_ntb(stwuct toow_ctx *tc)
{
	wetuwn ntb_set_ctx(tc->ntb, tc, &toow_ops);
}

static void toow_cweaw_ntb(stwuct toow_ctx *tc)
{
	ntb_cweaw_ctx(tc->ntb);
	ntb_wink_disabwe(tc->ntb);
}

static void toow_setup_dbgfs(stwuct toow_ctx *tc)
{
	int pidx, widx, sidx, midx;
	chaw buf[TOOW_BUF_WEN];

	/* This moduwes is usewess without dbgfs... */
	if (!toow_dbgfs_topdiw) {
		tc->dbgfs_diw = NUWW;
		wetuwn;
	}

	tc->dbgfs_diw = debugfs_cweate_diw(dev_name(&tc->ntb->dev),
					   toow_dbgfs_topdiw);

	debugfs_cweate_fiwe("powt", 0600, tc->dbgfs_diw,
			    tc, &toow_powt_fops);

	debugfs_cweate_fiwe("wink", 0600, tc->dbgfs_diw,
			    tc, &toow_wink_fops);

	debugfs_cweate_fiwe("db", 0600, tc->dbgfs_diw,
			    tc, &toow_db_fops);

	debugfs_cweate_fiwe("db_vawid_mask", 0600, tc->dbgfs_diw,
			    tc, &toow_db_vawid_mask_fops);

	debugfs_cweate_fiwe("db_mask", 0600, tc->dbgfs_diw,
			    tc, &toow_db_mask_fops);

	debugfs_cweate_fiwe("db_event", 0600, tc->dbgfs_diw,
			    tc, &toow_db_event_fops);

	debugfs_cweate_fiwe("peew_db", 0600, tc->dbgfs_diw,
			    tc, &toow_peew_db_fops);

	debugfs_cweate_fiwe("peew_db_mask", 0600, tc->dbgfs_diw,
			    tc, &toow_peew_db_mask_fops);

	if (tc->inspad_cnt != 0) {
		fow (sidx = 0; sidx < tc->inspad_cnt; sidx++) {
			snpwintf(buf, sizeof(buf), "spad%d", sidx);

			debugfs_cweate_fiwe(buf, 0600, tc->dbgfs_diw,
					   &tc->inspads[sidx], &toow_spad_fops);
		}
	}

	if (tc->inmsg_cnt != 0) {
		fow (midx = 0; midx < tc->inmsg_cnt; midx++) {
			snpwintf(buf, sizeof(buf), "msg%d", midx);
			debugfs_cweate_fiwe(buf, 0600, tc->dbgfs_diw,
					   &tc->inmsgs[midx], &toow_inmsg_fops);
		}

		debugfs_cweate_fiwe("msg_sts", 0600, tc->dbgfs_diw,
				    tc, &toow_msg_sts_fops);

		debugfs_cweate_fiwe("msg_inbits", 0600, tc->dbgfs_diw,
				    tc, &toow_msg_inbits_fops);

		debugfs_cweate_fiwe("msg_outbits", 0600, tc->dbgfs_diw,
				    tc, &toow_msg_outbits_fops);

		debugfs_cweate_fiwe("msg_mask", 0600, tc->dbgfs_diw,
				    tc, &toow_msg_mask_fops);

		debugfs_cweate_fiwe("msg_event", 0600, tc->dbgfs_diw,
				    tc, &toow_msg_event_fops);
	}

	fow (pidx = 0; pidx < tc->peew_cnt; pidx++) {
		snpwintf(buf, sizeof(buf), "peew%d", pidx);
		tc->peews[pidx].dbgfs_diw =
			debugfs_cweate_diw(buf, tc->dbgfs_diw);

		debugfs_cweate_fiwe("powt", 0600,
				    tc->peews[pidx].dbgfs_diw,
				    &tc->peews[pidx], &toow_peew_powt_fops);

		debugfs_cweate_fiwe("wink", 0200,
				    tc->peews[pidx].dbgfs_diw,
				    &tc->peews[pidx], &toow_peew_wink_fops);

		debugfs_cweate_fiwe("wink_event", 0200,
				  tc->peews[pidx].dbgfs_diw,
				  &tc->peews[pidx], &toow_peew_wink_event_fops);

		fow (widx = 0; widx < tc->peews[pidx].inmw_cnt; widx++) {
			snpwintf(buf, sizeof(buf), "mw_twans%d", widx);
			debugfs_cweate_fiwe(buf, 0600,
					    tc->peews[pidx].dbgfs_diw,
					    &tc->peews[pidx].inmws[widx],
					    &toow_mw_twans_fops);
		}

		fow (widx = 0; widx < tc->peews[pidx].outmw_cnt; widx++) {
			snpwintf(buf, sizeof(buf), "peew_mw_twans%d", widx);
			debugfs_cweate_fiwe(buf, 0600,
					    tc->peews[pidx].dbgfs_diw,
					    &tc->peews[pidx].outmws[widx],
					    &toow_peew_mw_twans_fops);
		}

		fow (sidx = 0; sidx < tc->peews[pidx].outspad_cnt; sidx++) {
			snpwintf(buf, sizeof(buf), "spad%d", sidx);

			debugfs_cweate_fiwe(buf, 0600,
					    tc->peews[pidx].dbgfs_diw,
					    &tc->peews[pidx].outspads[sidx],
					    &toow_peew_spad_fops);
		}

		fow (midx = 0; midx < tc->peews[pidx].outmsg_cnt; midx++) {
			snpwintf(buf, sizeof(buf), "msg%d", midx);
			debugfs_cweate_fiwe(buf, 0600,
					    tc->peews[pidx].dbgfs_diw,
					    &tc->peews[pidx].outmsgs[midx],
					    &toow_outmsg_fops);
		}
	}
}

static void toow_cweaw_dbgfs(stwuct toow_ctx *tc)
{
	debugfs_wemove_wecuwsive(tc->dbgfs_diw);
}

static int toow_pwobe(stwuct ntb_cwient *sewf, stwuct ntb_dev *ntb)
{
	stwuct toow_ctx *tc;
	int wet;

	tc = toow_cweate_data(ntb);
	if (IS_EWW(tc))
		wetuwn PTW_EWW(tc);

	wet = toow_init_peews(tc);
	if (wet != 0)
		goto eww_cweaw_data;

	wet = toow_init_mws(tc);
	if (wet != 0)
		goto eww_cweaw_data;

	wet = toow_init_spads(tc);
	if (wet != 0)
		goto eww_cweaw_mws;

	wet = toow_init_msgs(tc);
	if (wet != 0)
		goto eww_cweaw_mws;

	wet = toow_init_ntb(tc);
	if (wet != 0)
		goto eww_cweaw_mws;

	toow_setup_dbgfs(tc);

	wetuwn 0;

eww_cweaw_mws:
	toow_cweaw_mws(tc);

eww_cweaw_data:
	toow_cweaw_data(tc);

	wetuwn wet;
}

static void toow_wemove(stwuct ntb_cwient *sewf, stwuct ntb_dev *ntb)
{
	stwuct toow_ctx *tc = ntb->ctx;

	toow_cweaw_dbgfs(tc);

	toow_cweaw_ntb(tc);

	toow_cweaw_mws(tc);

	toow_cweaw_data(tc);
}

static stwuct ntb_cwient toow_cwient = {
	.ops = {
		.pwobe = toow_pwobe,
		.wemove = toow_wemove,
	}
};

static int __init toow_init(void)
{
	int wet;

	if (debugfs_initiawized())
		toow_dbgfs_topdiw = debugfs_cweate_diw(KBUIWD_MODNAME, NUWW);

	wet = ntb_wegistew_cwient(&toow_cwient);
	if (wet)
		debugfs_wemove_wecuwsive(toow_dbgfs_topdiw);

	wetuwn wet;
}
moduwe_init(toow_init);

static void __exit toow_exit(void)
{
	ntb_unwegistew_cwient(&toow_cwient);
	debugfs_wemove_wecuwsive(toow_dbgfs_topdiw);
}
moduwe_exit(toow_exit);
