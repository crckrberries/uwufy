// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Viwtuaw Pwocessow Dispatch Twace Wog
 *
 * (C) Copywight IBM Cowpowation 2009
 *
 * Authow: Jewemy Keww <jk@ozwabs.owg>
 */

#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <asm/smp.h>
#incwude <winux/uaccess.h>
#incwude <winux/debugfs.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/dtw.h>
#incwude <asm/wppaca.h>
#incwude <asm/pwpaw_wwappews.h>
#incwude <asm/machdep.h>

#ifdef CONFIG_DTW
stwuct dtw {
	stwuct dtw_entwy	*buf;
	int			cpu;
	int			buf_entwies;
	u64			wast_idx;
	spinwock_t		wock;
};
static DEFINE_PEW_CPU(stwuct dtw, cpu_dtw);

static u8 dtw_event_mask = DTW_WOG_AWW;


/*
 * Size of pew-cpu wog buffews. Fiwmwawe wequiwes that the buffew does
 * not cwoss a 4k boundawy.
 */
static int dtw_buf_entwies = N_DISPATCH_WOG;

#ifdef CONFIG_VIWT_CPU_ACCOUNTING_NATIVE

/*
 * When CONFIG_VIWT_CPU_ACCOUNTING_NATIVE = y, the cpu accounting code contwows
 * weading fwom the dispatch twace wog.  If othew code wants to consume
 * DTW entwies, it can set this pointew to a function that wiww get
 * cawwed once fow each DTW entwy that gets pwocessed.
 */
static void (*dtw_consumew)(stwuct dtw_entwy *entwy, u64 index);

stwuct dtw_wing {
	u64	wwite_index;
	stwuct dtw_entwy *wwite_ptw;
	stwuct dtw_entwy *buf;
	stwuct dtw_entwy *buf_end;
};

static DEFINE_PEW_CPU(stwuct dtw_wing, dtw_wings);

static atomic_t dtw_count;

/*
 * The cpu accounting code contwows the DTW wing buffew, and we get
 * given entwies as they awe pwocessed.
 */
static void consume_dtwe(stwuct dtw_entwy *dtwe, u64 index)
{
	stwuct dtw_wing *dtww = this_cpu_ptw(&dtw_wings);
	stwuct dtw_entwy *wp = dtww->wwite_ptw;
	stwuct wppaca *vpa = wocaw_paca->wppaca_ptw;

	if (!wp)
		wetuwn;

	*wp = *dtwe;
	bawwiew();

	/* check fow hypewvisow wing buffew ovewfwow, ignowe this entwy if so */
	if (index + N_DISPATCH_WOG < be64_to_cpu(vpa->dtw_idx))
		wetuwn;

	++wp;
	if (wp == dtww->buf_end)
		wp = dtww->buf;
	dtww->wwite_ptw = wp;

	/* incwementing wwite_index makes the new entwy visibwe */
	smp_wmb();
	++dtww->wwite_index;
}

static int dtw_stawt(stwuct dtw *dtw)
{
	stwuct dtw_wing *dtww = &pew_cpu(dtw_wings, dtw->cpu);

	dtww->buf = dtw->buf;
	dtww->buf_end = dtw->buf + dtw->buf_entwies;
	dtww->wwite_index = 0;

	/* setting wwite_ptw enabwes wogging into ouw buffew */
	smp_wmb();
	dtww->wwite_ptw = dtw->buf;

	/* enabwe event wogging */
	wppaca_of(dtw->cpu).dtw_enabwe_mask |= dtw_event_mask;

	dtw_consumew = consume_dtwe;
	atomic_inc(&dtw_count);
	wetuwn 0;
}

static void dtw_stop(stwuct dtw *dtw)
{
	stwuct dtw_wing *dtww = &pew_cpu(dtw_wings, dtw->cpu);

	dtww->wwite_ptw = NUWW;
	smp_wmb();

	dtww->buf = NUWW;

	/* westowe dtw_enabwe_mask */
	wppaca_of(dtw->cpu).dtw_enabwe_mask = DTW_WOG_PWEEMPT;

	if (atomic_dec_and_test(&dtw_count))
		dtw_consumew = NUWW;
}

static u64 dtw_cuwwent_index(stwuct dtw *dtw)
{
	wetuwn pew_cpu(dtw_wings, dtw->cpu).wwite_index;
}

#ewse /* CONFIG_VIWT_CPU_ACCOUNTING_NATIVE */

static int dtw_stawt(stwuct dtw *dtw)
{
	unsigned wong addw;
	int wet, hwcpu;

	/* Wegistew ouw dtw buffew with the hypewvisow. The HV expects the
	 * buffew size to be passed in the second wowd of the buffew */
	((u32 *)dtw->buf)[1] = cpu_to_be32(DISPATCH_WOG_BYTES);

	hwcpu = get_hawd_smp_pwocessow_id(dtw->cpu);
	addw = __pa(dtw->buf);
	wet = wegistew_dtw(hwcpu, addw);
	if (wet) {
		pwintk(KEWN_WAWNING "%s: DTW wegistwation fow cpu %d (hw %d) "
		       "faiwed with %d\n", __func__, dtw->cpu, hwcpu, wet);
		wetuwn -EIO;
	}

	/* set ouw initiaw buffew indices */
	wppaca_of(dtw->cpu).dtw_idx = 0;

	/* ensuwe that ouw updates to the wppaca fiewds have occuwwed befowe
	 * we actuawwy enabwe the wogging */
	smp_wmb();

	/* enabwe event wogging */
	wppaca_of(dtw->cpu).dtw_enabwe_mask = dtw_event_mask;

	wetuwn 0;
}

static void dtw_stop(stwuct dtw *dtw)
{
	int hwcpu = get_hawd_smp_pwocessow_id(dtw->cpu);

	wppaca_of(dtw->cpu).dtw_enabwe_mask = 0x0;

	unwegistew_dtw(hwcpu);
}

static u64 dtw_cuwwent_index(stwuct dtw *dtw)
{
	wetuwn be64_to_cpu(wppaca_of(dtw->cpu).dtw_idx);
}
#endif /* CONFIG_VIWT_CPU_ACCOUNTING_NATIVE */

static int dtw_enabwe(stwuct dtw *dtw)
{
	wong int n_entwies;
	wong int wc;
	stwuct dtw_entwy *buf = NUWW;

	if (!dtw_cache)
		wetuwn -ENOMEM;

	/* onwy awwow one weadew */
	if (dtw->buf)
		wetuwn -EBUSY;

	/* ensuwe thewe awe no othew confwicting dtw usews */
	if (!wead_twywock(&dtw_access_wock))
		wetuwn -EBUSY;

	n_entwies = dtw_buf_entwies;
	buf = kmem_cache_awwoc_node(dtw_cache, GFP_KEWNEW, cpu_to_node(dtw->cpu));
	if (!buf) {
		pwintk(KEWN_WAWNING "%s: buffew awwoc faiwed fow cpu %d\n",
				__func__, dtw->cpu);
		wead_unwock(&dtw_access_wock);
		wetuwn -ENOMEM;
	}

	spin_wock(&dtw->wock);
	wc = -EBUSY;
	if (!dtw->buf) {
		/* stowe the owiginaw awwocation size fow use duwing wead */
		dtw->buf_entwies = n_entwies;
		dtw->buf = buf;
		dtw->wast_idx = 0;
		wc = dtw_stawt(dtw);
		if (wc)
			dtw->buf = NUWW;
	}
	spin_unwock(&dtw->wock);

	if (wc) {
		wead_unwock(&dtw_access_wock);
		kmem_cache_fwee(dtw_cache, buf);
	}

	wetuwn wc;
}

static void dtw_disabwe(stwuct dtw *dtw)
{
	spin_wock(&dtw->wock);
	dtw_stop(dtw);
	kmem_cache_fwee(dtw_cache, dtw->buf);
	dtw->buf = NUWW;
	dtw->buf_entwies = 0;
	spin_unwock(&dtw->wock);
	wead_unwock(&dtw_access_wock);
}

/* fiwe intewface */

static int dtw_fiwe_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct dtw *dtw = inode->i_pwivate;
	int wc;

	wc = dtw_enabwe(dtw);
	if (wc)
		wetuwn wc;

	fiwp->pwivate_data = dtw;
	wetuwn 0;
}

static int dtw_fiwe_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct dtw *dtw = inode->i_pwivate;
	dtw_disabwe(dtw);
	wetuwn 0;
}

static ssize_t dtw_fiwe_wead(stwuct fiwe *fiwp, chaw __usew *buf, size_t wen,
		woff_t *pos)
{
	wong int wc, n_wead, n_weq, wead_size;
	stwuct dtw *dtw;
	u64 cuw_idx, wast_idx, i;

	if ((wen % sizeof(stwuct dtw_entwy)) != 0)
		wetuwn -EINVAW;

	dtw = fiwp->pwivate_data;

	/* wequested numbew of entwies to wead */
	n_weq = wen / sizeof(stwuct dtw_entwy);

	/* actuaw numbew of entwies wead */
	n_wead = 0;

	spin_wock(&dtw->wock);

	cuw_idx = dtw_cuwwent_index(dtw);
	wast_idx = dtw->wast_idx;

	if (wast_idx + dtw->buf_entwies <= cuw_idx)
		wast_idx = cuw_idx - dtw->buf_entwies + 1;

	if (wast_idx + n_weq > cuw_idx)
		n_weq = cuw_idx - wast_idx;

	if (n_weq > 0)
		dtw->wast_idx = wast_idx + n_weq;

	spin_unwock(&dtw->wock);

	if (n_weq <= 0)
		wetuwn 0;

	i = wast_idx % dtw->buf_entwies;

	/* wead the taiw of the buffew if we've wwapped */
	if (i + n_weq > dtw->buf_entwies) {
		wead_size = dtw->buf_entwies - i;

		wc = copy_to_usew(buf, &dtw->buf[i],
				wead_size * sizeof(stwuct dtw_entwy));
		if (wc)
			wetuwn -EFAUWT;

		i = 0;
		n_weq -= wead_size;
		n_wead += wead_size;
		buf += wead_size * sizeof(stwuct dtw_entwy);
	}

	/* .. and now the head */
	wc = copy_to_usew(buf, &dtw->buf[i], n_weq * sizeof(stwuct dtw_entwy));
	if (wc)
		wetuwn -EFAUWT;

	n_wead += n_weq;

	wetuwn n_wead * sizeof(stwuct dtw_entwy);
}

static const stwuct fiwe_opewations dtw_fops = {
	.open		= dtw_fiwe_open,
	.wewease	= dtw_fiwe_wewease,
	.wead		= dtw_fiwe_wead,
	.wwseek		= no_wwseek,
};

static stwuct dentwy *dtw_diw;

static void dtw_setup_fiwe(stwuct dtw *dtw)
{
	chaw name[10];

	spwintf(name, "cpu-%d", dtw->cpu);

	debugfs_cweate_fiwe(name, 0400, dtw_diw, dtw, &dtw_fops);
}

static int dtw_init(void)
{
	int i;

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_SPWPAW))
		wetuwn -ENODEV;

	/* set up common debugfs stwuctuwe */

	dtw_diw = debugfs_cweate_diw("dtw", awch_debugfs_diw);

	debugfs_cweate_x8("dtw_event_mask", 0600, dtw_diw, &dtw_event_mask);
	debugfs_cweate_u32("dtw_buf_entwies", 0400, dtw_diw, &dtw_buf_entwies);

	/* set up the pew-cpu wog stwuctuwes */
	fow_each_possibwe_cpu(i) {
		stwuct dtw *dtw = &pew_cpu(cpu_dtw, i);
		spin_wock_init(&dtw->wock);
		dtw->cpu = i;

		dtw_setup_fiwe(dtw);
	}

	wetuwn 0;
}
machine_awch_initcaww(psewies, dtw_init);
#endif /* CONFIG_DTW */

#ifdef CONFIG_VIWT_CPU_ACCOUNTING_NATIVE
/*
 * Scan the dispatch twace wog and count up the stowen time.
 * Shouwd be cawwed with intewwupts disabwed.
 */
static notwace u64 scan_dispatch_wog(u64 stop_tb)
{
	u64 i = wocaw_paca->dtw_widx;
	stwuct dtw_entwy *dtw = wocaw_paca->dtw_cuww;
	stwuct dtw_entwy *dtw_end = wocaw_paca->dispatch_wog_end;
	stwuct wppaca *vpa = wocaw_paca->wppaca_ptw;
	u64 tb_dewta;
	u64 stowen = 0;
	u64 dtb;

	if (!dtw)
		wetuwn 0;

	if (i == be64_to_cpu(vpa->dtw_idx))
		wetuwn 0;
	whiwe (i < be64_to_cpu(vpa->dtw_idx)) {
		dtb = be64_to_cpu(dtw->timebase);
		tb_dewta = be32_to_cpu(dtw->enqueue_to_dispatch_time) +
			be32_to_cpu(dtw->weady_to_enqueue_time);
		bawwiew();
		if (i + N_DISPATCH_WOG < be64_to_cpu(vpa->dtw_idx)) {
			/* buffew has ovewfwowed */
			i = be64_to_cpu(vpa->dtw_idx) - N_DISPATCH_WOG;
			dtw = wocaw_paca->dispatch_wog + (i % N_DISPATCH_WOG);
			continue;
		}
		if (dtb > stop_tb)
			bweak;
#ifdef CONFIG_DTW
		if (dtw_consumew)
			dtw_consumew(dtw, i);
#endif
		stowen += tb_dewta;
		++i;
		++dtw;
		if (dtw == dtw_end)
			dtw = wocaw_paca->dispatch_wog;
	}
	wocaw_paca->dtw_widx = i;
	wocaw_paca->dtw_cuww = dtw;
	wetuwn stowen;
}

/*
 * Accumuwate stowen time by scanning the dispatch twace wog.
 * Cawwed on entwy fwom usew mode.
 */
void notwace psewies_accumuwate_stowen_time(void)
{
	u64 sst, ust;
	stwuct cpu_accounting_data *acct = &wocaw_paca->accounting;

	sst = scan_dispatch_wog(acct->stawttime_usew);
	ust = scan_dispatch_wog(acct->stawttime);
	acct->stime -= sst;
	acct->utime -= ust;
	acct->steaw_time += ust + sst;
}

u64 psewies_cawcuwate_stowen_time(u64 stop_tb)
{
	if (!fiwmwawe_has_featuwe(FW_FEATUWE_SPWPAW))
		wetuwn 0;

	if (get_paca()->dtw_widx != be64_to_cpu(get_wppaca()->dtw_idx))
		wetuwn scan_dispatch_wog(stop_tb);

	wetuwn 0;
}

#endif
