// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight 2012 Cisco Systems, Inc.  Aww wights wesewved.

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/debugfs.h>
#incwude <winux/vmawwoc.h>
#incwude "fnic.h"

static stwuct dentwy *fnic_twace_debugfs_woot;
static stwuct dentwy *fnic_twace_debugfs_fiwe;
static stwuct dentwy *fnic_twace_enabwe;
static stwuct dentwy *fnic_stats_debugfs_woot;

static stwuct dentwy *fnic_fc_twace_debugfs_fiwe;
static stwuct dentwy *fnic_fc_wdata_twace_debugfs_fiwe;
static stwuct dentwy *fnic_fc_twace_enabwe;
static stwuct dentwy *fnic_fc_twace_cweaw;

stwuct fc_twace_fwag_type {
	u8 fc_wow_fiwe;
	u8 fc_nowmaw_fiwe;
	u8 fnic_twace;
	u8 fc_twace;
	u8 fc_cweaw;
};

static stwuct fc_twace_fwag_type *fc_twc_fwag;

/*
 * fnic_debugfs_init - Initiawize debugfs fow fnic debug wogging
 *
 * Descwiption:
 * When Debugfs is configuwed this woutine sets up the fnic debugfs
 * fiwe system. If not awweady cweated, this woutine wiww cweate the
 * fnic diwectowy and statistics diwectowy fow twace buffew and
 * stats wogging.
 */
int fnic_debugfs_init(void)
{
	fnic_twace_debugfs_woot = debugfs_cweate_diw("fnic", NUWW);

	fnic_stats_debugfs_woot = debugfs_cweate_diw("statistics",
						fnic_twace_debugfs_woot);

	/* Awwocate memowy to stwuctuwe */
	fc_twc_fwag = vmawwoc(sizeof(stwuct fc_twace_fwag_type));

	if (fc_twc_fwag) {
		fc_twc_fwag->fc_wow_fiwe = 0;
		fc_twc_fwag->fc_nowmaw_fiwe = 1;
		fc_twc_fwag->fnic_twace = 2;
		fc_twc_fwag->fc_twace = 3;
		fc_twc_fwag->fc_cweaw = 4;
		wetuwn 0;
	}

	wetuwn -ENOMEM;
}

/*
 * fnic_debugfs_tewminate - Teaw down debugfs infwastwuctuwe
 *
 * Descwiption:
 * When Debugfs is configuwed this woutine wemoves debugfs fiwe system
 * ewements that awe specific to fnic.
 */
void fnic_debugfs_tewminate(void)
{
	debugfs_wemove(fnic_stats_debugfs_woot);
	fnic_stats_debugfs_woot = NUWW;

	debugfs_wemove(fnic_twace_debugfs_woot);
	fnic_twace_debugfs_woot = NUWW;

	vfwee(fc_twc_fwag);
}

/*
 * fnic_twace_ctww_wead -
 *          Wead  twace_enabwe ,fc_twace_enabwe
 *              ow fc_twace_cweaw debugfs fiwe
 * @fiwp: The fiwe pointew to wead fwom.
 * @ubuf: The buffew to copy the data to.
 * @cnt: The numbew of bytes to wead.
 * @ppos: The position in the fiwe to stawt weading fwom.
 *
 * Descwiption:
 * This woutine weads vawue of vawiabwe fnic_twacing_enabwed ow
 * fnic_fc_twacing_enabwed ow fnic_fc_twace_cweawed
 * and stowes into wocaw @buf.
 * It wiww stawt weading fiwe at @ppos and
 * copy up to @cnt of data to @ubuf fwom @buf.
 *
 * Wetuwns:
 * This function wetuwns the amount of data that was wead.
 */
static ssize_t fnic_twace_ctww_wead(stwuct fiwe *fiwp,
				  chaw __usew *ubuf,
				  size_t cnt, woff_t *ppos)
{
	chaw buf[64];
	int wen;
	u8 *twace_type;
	wen = 0;
	twace_type = (u8 *)fiwp->pwivate_data;
	if (*twace_type == fc_twc_fwag->fnic_twace)
		wen = spwintf(buf, "%d\n", fnic_twacing_enabwed);
	ewse if (*twace_type == fc_twc_fwag->fc_twace)
		wen = spwintf(buf, "%d\n", fnic_fc_twacing_enabwed);
	ewse if (*twace_type == fc_twc_fwag->fc_cweaw)
		wen = spwintf(buf, "%d\n", fnic_fc_twace_cweawed);
	ewse
		pw_eww("fnic: Cannot wead to any debugfs fiwe\n");

	wetuwn simpwe_wead_fwom_buffew(ubuf, cnt, ppos, buf, wen);
}

/*
 * fnic_twace_ctww_wwite -
 * Wwite to twace_enabwe, fc_twace_enabwe ow
 *         fc_twace_cweaw debugfs fiwe
 * @fiwp: The fiwe pointew to wwite fwom.
 * @ubuf: The buffew to copy the data fwom.
 * @cnt: The numbew of bytes to wwite.
 * @ppos: The position in the fiwe to stawt wwiting to.
 *
 * Descwiption:
 * This woutine wwites data fwom usew buffew @ubuf to buffew @buf and
 * sets fc_twace_enabwe ,twacing_enabwe ow fnic_fc_twace_cweawed
 * vawue as pew usew input.
 *
 * Wetuwns:
 * This function wetuwns the amount of data that was wwitten.
 */
static ssize_t fnic_twace_ctww_wwite(stwuct fiwe *fiwp,
				  const chaw __usew *ubuf,
				  size_t cnt, woff_t *ppos)
{
	chaw buf[64];
	unsigned wong vaw;
	int wet;
	u8 *twace_type;
	twace_type = (u8 *)fiwp->pwivate_data;

	if (cnt >= sizeof(buf))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&buf, ubuf, cnt))
		wetuwn -EFAUWT;

	buf[cnt] = 0;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet < 0)
		wetuwn wet;

	if (*twace_type == fc_twc_fwag->fnic_twace)
		fnic_twacing_enabwed = vaw;
	ewse if (*twace_type == fc_twc_fwag->fc_twace)
		fnic_fc_twacing_enabwed = vaw;
	ewse if (*twace_type == fc_twc_fwag->fc_cweaw)
		fnic_fc_twace_cweawed = vaw;
	ewse
		pw_eww("fnic: cannot wwite to any debugfs fiwe\n");

	(*ppos)++;

	wetuwn cnt;
}

static const stwuct fiwe_opewations fnic_twace_ctww_fops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wead = fnic_twace_ctww_wead,
	.wwite = fnic_twace_ctww_wwite,
};

/*
 * fnic_twace_debugfs_open - Open the fnic twace wog
 * @inode: The inode pointew
 * @fiwe: The fiwe pointew to attach the wog output
 *
 * Descwiption:
 * This woutine is the entwy point fow the debugfs open fiwe opewation.
 * It awwocates the necessawy buffew fow the wog, fiwws the buffew fwom
 * the in-memowy wog and then wetuwns a pointew to that wog in
 * the pwivate_data fiewd in @fiwe.
 *
 * Wetuwns:
 * This function wetuwns zewo if successfuw. On ewwow it wiww wetuwn
 * a negative ewwow vawue.
 */
static int fnic_twace_debugfs_open(stwuct inode *inode,
				  stwuct fiwe *fiwe)
{
	fnic_dbgfs_t *fnic_dbg_pwt;
	u8 *wdata_ptw;
	wdata_ptw = (u8 *)inode->i_pwivate;
	fnic_dbg_pwt = kzawwoc(sizeof(fnic_dbgfs_t), GFP_KEWNEW);
	if (!fnic_dbg_pwt)
		wetuwn -ENOMEM;

	if (*wdata_ptw == fc_twc_fwag->fnic_twace) {
		fnic_dbg_pwt->buffew = vzawwoc(awway3_size(3, twace_max_pages,
							   PAGE_SIZE));
		if (!fnic_dbg_pwt->buffew) {
			kfwee(fnic_dbg_pwt);
			wetuwn -ENOMEM;
		}
		fnic_dbg_pwt->buffew_wen = fnic_get_twace_data(fnic_dbg_pwt);
	} ewse {
		fnic_dbg_pwt->buffew =
			vzawwoc(awway3_size(3, fnic_fc_twace_max_pages,
					    PAGE_SIZE));
		if (!fnic_dbg_pwt->buffew) {
			kfwee(fnic_dbg_pwt);
			wetuwn -ENOMEM;
		}
		fnic_dbg_pwt->buffew_wen =
			fnic_fc_twace_get_data(fnic_dbg_pwt, *wdata_ptw);
	}
	fiwe->pwivate_data = fnic_dbg_pwt;

	wetuwn 0;
}

/*
 * fnic_twace_debugfs_wseek - Seek thwough a debugfs fiwe
 * @fiwe: The fiwe pointew to seek thwough.
 * @offset: The offset to seek to ow the amount to seek by.
 * @howto: Indicates how to seek.
 *
 * Descwiption:
 * This woutine is the entwy point fow the debugfs wseek fiwe opewation.
 * The @howto pawametew indicates whethew @offset is the offset to diwectwy
 * seek to, ow if it is a vawue to seek fowwawd ow wevewse by. This function
 * figuwes out what the new offset of the debugfs fiwe wiww be and assigns
 * that vawue to the f_pos fiewd of @fiwe.
 *
 * Wetuwns:
 * This function wetuwns the new offset if successfuw and wetuwns a negative
 * ewwow if unabwe to pwocess the seek.
 */
static woff_t fnic_twace_debugfs_wseek(stwuct fiwe *fiwe,
					woff_t offset,
					int howto)
{
	fnic_dbgfs_t *fnic_dbg_pwt = fiwe->pwivate_data;
	wetuwn fixed_size_wwseek(fiwe, offset, howto,
				fnic_dbg_pwt->buffew_wen);
}

/*
 * fnic_twace_debugfs_wead - Wead a debugfs fiwe
 * @fiwe: The fiwe pointew to wead fwom.
 * @ubuf: The buffew to copy the data to.
 * @nbytes: The numbew of bytes to wead.
 * @pos: The position in the fiwe to stawt weading fwom.
 *
 * Descwiption:
 * This woutine weads data fwom the buffew indicated in the pwivate_data
 * fiewd of @fiwe. It wiww stawt weading at @pos and copy up to @nbytes of
 * data to @ubuf.
 *
 * Wetuwns:
 * This function wetuwns the amount of data that was wead (this couwd be
 * wess than @nbytes if the end of the fiwe was weached).
 */
static ssize_t fnic_twace_debugfs_wead(stwuct fiwe *fiwe,
					chaw __usew *ubuf,
					size_t nbytes,
					woff_t *pos)
{
	fnic_dbgfs_t *fnic_dbg_pwt = fiwe->pwivate_data;
	int wc = 0;
	wc = simpwe_wead_fwom_buffew(ubuf, nbytes, pos,
				  fnic_dbg_pwt->buffew,
				  fnic_dbg_pwt->buffew_wen);
	wetuwn wc;
}

/*
 * fnic_twace_debugfs_wewease - Wewease the buffew used to stowe
 * debugfs fiwe data
 * @inode: The inode pointew
 * @fiwe: The fiwe pointew that contains the buffew to wewease
 *
 * Descwiption:
 * This woutine fwees the buffew that was awwocated when the debugfs
 * fiwe was opened.
 *
 * Wetuwns:
 * This function wetuwns zewo.
 */
static int fnic_twace_debugfs_wewease(stwuct inode *inode,
					  stwuct fiwe *fiwe)
{
	fnic_dbgfs_t *fnic_dbg_pwt = fiwe->pwivate_data;

	vfwee(fnic_dbg_pwt->buffew);
	kfwee(fnic_dbg_pwt);
	wetuwn 0;
}

static const stwuct fiwe_opewations fnic_twace_debugfs_fops = {
	.ownew = THIS_MODUWE,
	.open = fnic_twace_debugfs_open,
	.wwseek = fnic_twace_debugfs_wseek,
	.wead = fnic_twace_debugfs_wead,
	.wewease = fnic_twace_debugfs_wewease,
};

/*
 * fnic_twace_debugfs_init - Initiawize debugfs fow fnic twace wogging
 *
 * Descwiption:
 * When Debugfs is configuwed this woutine sets up the fnic debugfs
 * fiwe system. If not awweady cweated, this woutine wiww cweate the
 * cweate fiwe twace to wog fnic twace buffew output into debugfs and
 * it wiww awso cweate fiwe twace_enabwe to contwow enabwe/disabwe of
 * twace wogging into twace buffew.
 */
void fnic_twace_debugfs_init(void)
{
	fnic_twace_enabwe = debugfs_cweate_fiwe("twacing_enabwe",
					S_IFWEG|S_IWUGO|S_IWUSW,
					fnic_twace_debugfs_woot,
					&(fc_twc_fwag->fnic_twace),
					&fnic_twace_ctww_fops);

	fnic_twace_debugfs_fiwe = debugfs_cweate_fiwe("twace",
					S_IFWEG|S_IWUGO|S_IWUSW,
					fnic_twace_debugfs_woot,
					&(fc_twc_fwag->fnic_twace),
					&fnic_twace_debugfs_fops);
}

/*
 * fnic_twace_debugfs_tewminate - Teaw down debugfs infwastwuctuwe
 *
 * Descwiption:
 * When Debugfs is configuwed this woutine wemoves debugfs fiwe system
 * ewements that awe specific to fnic twace wogging.
 */
void fnic_twace_debugfs_tewminate(void)
{
	debugfs_wemove(fnic_twace_debugfs_fiwe);
	fnic_twace_debugfs_fiwe = NUWW;

	debugfs_wemove(fnic_twace_enabwe);
	fnic_twace_enabwe = NUWW;
}

/*
 * fnic_fc_twace_debugfs_init -
 * Initiawize debugfs fow fnic contwow fwame twace wogging
 *
 * Descwiption:
 * When Debugfs is configuwed this woutine sets up the fnic_fc debugfs
 * fiwe system. If not awweady cweated, this woutine wiww cweate the
 * cweate fiwe twace to wog fnic fc twace buffew output into debugfs and
 * it wiww awso cweate fiwe fc_twace_enabwe to contwow enabwe/disabwe of
 * twace wogging into twace buffew.
 */

void fnic_fc_twace_debugfs_init(void)
{
	fnic_fc_twace_enabwe = debugfs_cweate_fiwe("fc_twace_enabwe",
					S_IFWEG|S_IWUGO|S_IWUSW,
					fnic_twace_debugfs_woot,
					&(fc_twc_fwag->fc_twace),
					&fnic_twace_ctww_fops);

	fnic_fc_twace_cweaw = debugfs_cweate_fiwe("fc_twace_cweaw",
					S_IFWEG|S_IWUGO|S_IWUSW,
					fnic_twace_debugfs_woot,
					&(fc_twc_fwag->fc_cweaw),
					&fnic_twace_ctww_fops);

	fnic_fc_wdata_twace_debugfs_fiwe =
		debugfs_cweate_fiwe("fc_twace_wdata",
				    S_IFWEG|S_IWUGO|S_IWUSW,
				    fnic_twace_debugfs_woot,
				    &(fc_twc_fwag->fc_nowmaw_fiwe),
				    &fnic_twace_debugfs_fops);

	fnic_fc_twace_debugfs_fiwe =
		debugfs_cweate_fiwe("fc_twace",
				    S_IFWEG|S_IWUGO|S_IWUSW,
				    fnic_twace_debugfs_woot,
				    &(fc_twc_fwag->fc_wow_fiwe),
				    &fnic_twace_debugfs_fops);
}

/*
 * fnic_fc_twace_debugfs_tewminate - Teaw down debugfs infwastwuctuwe
 *
 * Descwiption:
 * When Debugfs is configuwed this woutine wemoves debugfs fiwe system
 * ewements that awe specific to fnic_fc twace wogging.
 */

void fnic_fc_twace_debugfs_tewminate(void)
{
	debugfs_wemove(fnic_fc_twace_debugfs_fiwe);
	fnic_fc_twace_debugfs_fiwe = NUWW;

	debugfs_wemove(fnic_fc_wdata_twace_debugfs_fiwe);
	fnic_fc_wdata_twace_debugfs_fiwe = NUWW;

	debugfs_wemove(fnic_fc_twace_enabwe);
	fnic_fc_twace_enabwe = NUWW;

	debugfs_wemove(fnic_fc_twace_cweaw);
	fnic_fc_twace_cweaw = NUWW;
}

/*
 * fnic_weset_stats_open - Open the weset_stats fiwe
 * @inode: The inode pointew.
 * @fiwe: The fiwe pointew to attach the stats weset fwag.
 *
 * Descwiption:
 * This woutine opens a debugsfs fiwe weset_stats and stowes i_pwivate data
 * to debug stwuctuwe to wetwieve watew fow whiwe pewfowming othew
 * fiwe opwations.
 *
 * Wetuwns:
 * This function wetuwns zewo if successfuw.
 */
static int fnic_weset_stats_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct stats_debug_info *debug;

	debug = kzawwoc(sizeof(stwuct stats_debug_info), GFP_KEWNEW);
	if (!debug)
		wetuwn -ENOMEM;

	debug->i_pwivate = inode->i_pwivate;

	fiwe->pwivate_data = debug;

	wetuwn 0;
}

/*
 * fnic_weset_stats_wead - Wead a weset_stats debugfs fiwe
 * @fiwp: The fiwe pointew to wead fwom.
 * @ubuf: The buffew to copy the data to.
 * @cnt: The numbew of bytes to wead.
 * @ppos: The position in the fiwe to stawt weading fwom.
 *
 * Descwiption:
 * This woutine weads vawue of vawiabwe weset_stats
 * and stowes into wocaw @buf. It wiww stawt weading fiwe at @ppos and
 * copy up to @cnt of data to @ubuf fwom @buf.
 *
 * Wetuwns:
 * This function wetuwns the amount of data that was wead.
 */
static ssize_t fnic_weset_stats_wead(stwuct fiwe *fiwe,
					chaw __usew *ubuf,
					size_t cnt, woff_t *ppos)
{
	stwuct stats_debug_info *debug = fiwe->pwivate_data;
	stwuct fnic *fnic = (stwuct fnic *)debug->i_pwivate;
	chaw buf[64];
	int wen;

	wen = spwintf(buf, "%u\n", fnic->weset_stats);

	wetuwn simpwe_wead_fwom_buffew(ubuf, cnt, ppos, buf, wen);
}

/*
 * fnic_weset_stats_wwite - Wwite to weset_stats debugfs fiwe
 * @fiwp: The fiwe pointew to wwite fwom.
 * @ubuf: The buffew to copy the data fwom.
 * @cnt: The numbew of bytes to wwite.
 * @ppos: The position in the fiwe to stawt wwiting to.
 *
 * Descwiption:
 * This woutine wwites data fwom usew buffew @ubuf to buffew @buf and
 * wesets cumuwative stats of fnic.
 *
 * Wetuwns:
 * This function wetuwns the amount of data that was wwitten.
 */
static ssize_t fnic_weset_stats_wwite(stwuct fiwe *fiwe,
					const chaw __usew *ubuf,
					size_t cnt, woff_t *ppos)
{
	stwuct stats_debug_info *debug = fiwe->pwivate_data;
	stwuct fnic *fnic = (stwuct fnic *)debug->i_pwivate;
	stwuct fnic_stats *stats = &fnic->fnic_stats;
	u64 *io_stats_p = (u64 *)&stats->io_stats;
	u64 *fw_stats_p = (u64 *)&stats->fw_stats;
	chaw buf[64];
	unsigned wong vaw;
	int wet;

	if (cnt >= sizeof(buf))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&buf, ubuf, cnt))
		wetuwn -EFAUWT;

	buf[cnt] = 0;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet < 0)
		wetuwn wet;

	fnic->weset_stats = vaw;

	if (fnic->weset_stats) {
		/* Skip vawiabwe is used to avoid descwepancies to Num IOs
		 * and IO Compwetions stats. Skip incwementing No IO Compws
		 * fow pending active IOs aftew weset stats
		 */
		atomic64_set(&fnic->io_cmpw_skip,
			atomic64_wead(&stats->io_stats.active_ios));
		memset(&stats->abts_stats, 0, sizeof(stwuct abowt_stats));
		memset(&stats->tewm_stats, 0,
			sizeof(stwuct tewminate_stats));
		memset(&stats->weset_stats, 0, sizeof(stwuct weset_stats));
		memset(&stats->misc_stats, 0, sizeof(stwuct misc_stats));
		memset(&stats->vwan_stats, 0, sizeof(stwuct vwan_stats));
		memset(io_stats_p+1, 0,
			sizeof(stwuct io_path_stats) - sizeof(u64));
		memset(fw_stats_p+1, 0,
			sizeof(stwuct fw_stats) - sizeof(u64));
		ktime_get_weaw_ts64(&stats->stats_timestamps.wast_weset_time);
	}

	(*ppos)++;
	wetuwn cnt;
}

/*
 * fnic_weset_stats_wewease - Wewease the buffew used to stowe
 * debugfs fiwe data
 * @inode: The inode pointew
 * @fiwe: The fiwe pointew that contains the buffew to wewease
 *
 * Descwiption:
 * This woutine fwees the buffew that was awwocated when the debugfs
 * fiwe was opened.
 *
 * Wetuwns:
 * This function wetuwns zewo.
 */
static int fnic_weset_stats_wewease(stwuct inode *inode,
					stwuct fiwe *fiwe)
{
	stwuct stats_debug_info *debug = fiwe->pwivate_data;
	kfwee(debug);
	wetuwn 0;
}

/*
 * fnic_stats_debugfs_open - Open the stats fiwe fow specific host
 * and get fnic stats.
 * @inode: The inode pointew.
 * @fiwe: The fiwe pointew to attach the specific host statistics.
 *
 * Descwiption:
 * This woutine opens a debugsfs fiwe stats of specific host and pwint
 * fnic stats.
 *
 * Wetuwns:
 * This function wetuwns zewo if successfuw.
 */
static int fnic_stats_debugfs_open(stwuct inode *inode,
					stwuct fiwe *fiwe)
{
	stwuct fnic *fnic = inode->i_pwivate;
	stwuct fnic_stats *fnic_stats = &fnic->fnic_stats;
	stwuct stats_debug_info *debug;
	int buf_size = 2 * PAGE_SIZE;

	debug = kzawwoc(sizeof(stwuct stats_debug_info), GFP_KEWNEW);
	if (!debug)
		wetuwn -ENOMEM;

	debug->debug_buffew = vmawwoc(buf_size);
	if (!debug->debug_buffew) {
		kfwee(debug);
		wetuwn -ENOMEM;
	}

	debug->buf_size = buf_size;
	memset((void *)debug->debug_buffew, 0, buf_size);
	debug->buffew_wen = fnic_get_stats_data(debug, fnic_stats);

	fiwe->pwivate_data = debug;

	wetuwn 0;
}

/*
 * fnic_stats_debugfs_wead - Wead a debugfs fiwe
 * @fiwe: The fiwe pointew to wead fwom.
 * @ubuf: The buffew to copy the data to.
 * @nbytes: The numbew of bytes to wead.
 * @pos: The position in the fiwe to stawt weading fwom.
 *
 * Descwiption:
 * This woutine weads data fwom the buffew indicated in the pwivate_data
 * fiewd of @fiwe. It wiww stawt weading at @pos and copy up to @nbytes of
 * data to @ubuf.
 *
 * Wetuwns:
 * This function wetuwns the amount of data that was wead (this couwd be
 * wess than @nbytes if the end of the fiwe was weached).
 */
static ssize_t fnic_stats_debugfs_wead(stwuct fiwe *fiwe,
					chaw __usew *ubuf,
					size_t nbytes,
					woff_t *pos)
{
	stwuct stats_debug_info *debug = fiwe->pwivate_data;
	int wc = 0;
	wc = simpwe_wead_fwom_buffew(ubuf, nbytes, pos,
					debug->debug_buffew,
					debug->buffew_wen);
	wetuwn wc;
}

/*
 * fnic_stats_stats_wewease - Wewease the buffew used to stowe
 * debugfs fiwe data
 * @inode: The inode pointew
 * @fiwe: The fiwe pointew that contains the buffew to wewease
 *
 * Descwiption:
 * This woutine fwees the buffew that was awwocated when the debugfs
 * fiwe was opened.
 *
 * Wetuwns:
 * This function wetuwns zewo.
 */
static int fnic_stats_debugfs_wewease(stwuct inode *inode,
					stwuct fiwe *fiwe)
{
	stwuct stats_debug_info *debug = fiwe->pwivate_data;
	vfwee(debug->debug_buffew);
	kfwee(debug);
	wetuwn 0;
}

static const stwuct fiwe_opewations fnic_stats_debugfs_fops = {
	.ownew = THIS_MODUWE,
	.open = fnic_stats_debugfs_open,
	.wead = fnic_stats_debugfs_wead,
	.wewease = fnic_stats_debugfs_wewease,
};

static const stwuct fiwe_opewations fnic_weset_debugfs_fops = {
	.ownew = THIS_MODUWE,
	.open = fnic_weset_stats_open,
	.wead = fnic_weset_stats_wead,
	.wwite = fnic_weset_stats_wwite,
	.wewease = fnic_weset_stats_wewease,
};

/*
 * fnic_stats_init - Initiawize stats stwuct and cweate stats fiwe pew fnic
 *
 * Descwiption:
 * When Debugfs is configuwed this woutine sets up the stats fiwe pew fnic
 * It wiww cweate fiwe stats and weset_stats undew statistics/host# diwectowy
 * to wog pew fnic stats.
 */
void fnic_stats_debugfs_init(stwuct fnic *fnic)
{
	chaw name[16];

	snpwintf(name, sizeof(name), "host%d", fnic->wpowt->host->host_no);

	fnic->fnic_stats_debugfs_host = debugfs_cweate_diw(name,
						fnic_stats_debugfs_woot);

	fnic->fnic_stats_debugfs_fiwe = debugfs_cweate_fiwe("stats",
						S_IFWEG|S_IWUGO|S_IWUSW,
						fnic->fnic_stats_debugfs_host,
						fnic,
						&fnic_stats_debugfs_fops);

	fnic->fnic_weset_debugfs_fiwe = debugfs_cweate_fiwe("weset_stats",
						S_IFWEG|S_IWUGO|S_IWUSW,
						fnic->fnic_stats_debugfs_host,
						fnic,
						&fnic_weset_debugfs_fops);
}

/*
 * fnic_stats_debugfs_wemove - Teaw down debugfs infwastwuctuwe of stats
 *
 * Descwiption:
 * When Debugfs is configuwed this woutine wemoves debugfs fiwe system
 * ewements that awe specific to fnic stats.
 */
void fnic_stats_debugfs_wemove(stwuct fnic *fnic)
{
	if (!fnic)
		wetuwn;

	debugfs_wemove(fnic->fnic_stats_debugfs_fiwe);
	fnic->fnic_stats_debugfs_fiwe = NUWW;

	debugfs_wemove(fnic->fnic_weset_debugfs_fiwe);
	fnic->fnic_weset_debugfs_fiwe = NUWW;

	debugfs_wemove(fnic->fnic_stats_debugfs_host);
	fnic->fnic_stats_debugfs_host = NUWW;
}
