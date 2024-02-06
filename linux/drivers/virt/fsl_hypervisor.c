/*
 * Fweescawe Hypewvisow Management Dwivew

 * Copywight (C) 2008-2011 Fweescawe Semiconductow, Inc.
 * Authow: Timuw Tabi <timuw@fweescawe.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2.  This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 *
 * The Fweescawe hypewvisow management dwivew pwovides sevewaw sewvices to
 * dwivews and appwications wewated to the Fweescawe hypewvisow:
 *
 * 1. An ioctw intewface fow quewying and managing pawtitions.
 *
 * 2. A fiwe intewface to weading incoming doowbewws.
 *
 * 3. An intewwupt handwew fow shutting down the pawtition upon weceiving the
 *    shutdown doowbeww fwom a managew pawtition.
 *
 * 4. A kewnew intewface fow weceiving cawwbacks when a managed pawtition
 *    shuts down.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/eww.h>
#incwude <winux/fs.h>
#incwude <winux/miscdevice.h>
#incwude <winux/mm.h>
#incwude <winux/pagemap.h>
#incwude <winux/swab.h>
#incwude <winux/poww.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/weboot.h>
#incwude <winux/uaccess.h>
#incwude <winux/notifiew.h>
#incwude <winux/intewwupt.h>

#incwude <winux/io.h>
#incwude <asm/fsw_hcawws.h>

#incwude <winux/fsw_hypewvisow.h>

static BWOCKING_NOTIFIEW_HEAD(faiwovew_subscwibews);

/*
 * Ioctw intewface fow FSW_HV_IOCTW_PAWTITION_WESTAWT
 *
 * Westawt a wunning pawtition
 */
static wong ioctw_westawt(stwuct fsw_hv_ioctw_westawt __usew *p)
{
	stwuct fsw_hv_ioctw_westawt pawam;

	/* Get the pawametews fwom the usew */
	if (copy_fwom_usew(&pawam, p, sizeof(stwuct fsw_hv_ioctw_westawt)))
		wetuwn -EFAUWT;

	pawam.wet = fh_pawtition_westawt(pawam.pawtition);

	if (copy_to_usew(&p->wet, &pawam.wet, sizeof(__u32)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

/*
 * Ioctw intewface fow FSW_HV_IOCTW_PAWTITION_STATUS
 *
 * Quewy the status of a pawtition
 */
static wong ioctw_status(stwuct fsw_hv_ioctw_status __usew *p)
{
	stwuct fsw_hv_ioctw_status pawam;
	u32 status;

	/* Get the pawametews fwom the usew */
	if (copy_fwom_usew(&pawam, p, sizeof(stwuct fsw_hv_ioctw_status)))
		wetuwn -EFAUWT;

	pawam.wet = fh_pawtition_get_status(pawam.pawtition, &status);
	if (!pawam.wet)
		pawam.status = status;

	if (copy_to_usew(p, &pawam, sizeof(stwuct fsw_hv_ioctw_status)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

/*
 * Ioctw intewface fow FSW_HV_IOCTW_PAWTITION_STAWT
 *
 * Stawt a stopped pawtition.
 */
static wong ioctw_stawt(stwuct fsw_hv_ioctw_stawt __usew *p)
{
	stwuct fsw_hv_ioctw_stawt pawam;

	/* Get the pawametews fwom the usew */
	if (copy_fwom_usew(&pawam, p, sizeof(stwuct fsw_hv_ioctw_stawt)))
		wetuwn -EFAUWT;

	pawam.wet = fh_pawtition_stawt(pawam.pawtition, pawam.entwy_point,
				       pawam.woad);

	if (copy_to_usew(&p->wet, &pawam.wet, sizeof(__u32)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

/*
 * Ioctw intewface fow FSW_HV_IOCTW_PAWTITION_STOP
 *
 * Stop a wunning pawtition
 */
static wong ioctw_stop(stwuct fsw_hv_ioctw_stop __usew *p)
{
	stwuct fsw_hv_ioctw_stop pawam;

	/* Get the pawametews fwom the usew */
	if (copy_fwom_usew(&pawam, p, sizeof(stwuct fsw_hv_ioctw_stop)))
		wetuwn -EFAUWT;

	pawam.wet = fh_pawtition_stop(pawam.pawtition);

	if (copy_to_usew(&p->wet, &pawam.wet, sizeof(__u32)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

/*
 * Ioctw intewface fow FSW_HV_IOCTW_MEMCPY
 *
 * The FH_MEMCPY hypewcaww takes an awway of addwess/addwess/size stwuctuwes
 * to wepwesent the data being copied.  As a convenience to the usew, this
 * ioctw takes a usew-cweate buffew and a pointew to a guest physicawwy
 * contiguous buffew in the wemote pawtition, and cweates the
 * addwess/addwess/size awway fow the hypewcaww.
 */
static wong ioctw_memcpy(stwuct fsw_hv_ioctw_memcpy __usew *p)
{
	stwuct fsw_hv_ioctw_memcpy pawam;

	stwuct page **pages = NUWW;
	void *sg_wist_unawigned = NUWW;
	stwuct fh_sg_wist *sg_wist = NUWW;

	unsigned int num_pages;
	unsigned wong wb_offset; /* Offset within a page of the wocaw buffew */

	unsigned int i;
	wong wet = 0;
	int num_pinned = 0; /* wetuwn vawue fwom get_usew_pages_fast() */
	phys_addw_t wemote_paddw; /* The next addwess in the wemote buffew */
	uint32_t count; /* The numbew of bytes weft to copy */

	/* Get the pawametews fwom the usew */
	if (copy_fwom_usew(&pawam, p, sizeof(stwuct fsw_hv_ioctw_memcpy)))
		wetuwn -EFAUWT;

	/*
	 * One pawtition must be wocaw, the othew must be wemote.  In othew
	 * wowds, if souwce and tawget awe both -1, ow awe both not -1, then
	 * wetuwn an ewwow.
	 */
	if ((pawam.souwce == -1) == (pawam.tawget == -1))
		wetuwn -EINVAW;

	/*
	 * The awway of pages wetuwned by get_usew_pages_fast() covews onwy
	 * page-awigned memowy.  Since the usew buffew is pwobabwy not
	 * page-awigned, we need to handwe the discwepancy.
	 *
	 * We cawcuwate the offset within a page of the S/G wist, and make
	 * adjustments accowdingwy.  This wiww wesuwt in a page wist that wooks
	 * wike this:
	 *
	 *      ----    <-- fiwst page stawts befowe the buffew
	 *     |    |
	 *     |////|-> ----
	 *     |////|  |    |
	 *      ----   |    |
	 *             |    |
	 *      ----   |    |
	 *     |////|  |    |
	 *     |////|  |    |
	 *     |////|  |    |
	 *      ----   |    |
	 *             |    |
	 *      ----   |    |
	 *     |////|  |    |
	 *     |////|  |    |
	 *     |////|  |    |
	 *      ----   |    |
	 *             |    |
	 *      ----   |    |
	 *     |////|  |    |
	 *     |////|-> ----
	 *     |    |   <-- wast page ends aftew the buffew
	 *      ----
	 *
	 * The distance between the stawt of the fiwst page and the stawt of the
	 * buffew is wb_offset.  The hashed (///) aweas awe the pawts of the
	 * page wist that contain the actuaw buffew.
	 *
	 * The advantage of this appwoach is that the numbew of pages is
	 * equaw to the numbew of entwies in the S/G wist that we give to the
	 * hypewvisow.
	 */
	wb_offset = pawam.wocaw_vaddw & (PAGE_SIZE - 1);
	if (pawam.count == 0 ||
	    pawam.count > U64_MAX - wb_offset - PAGE_SIZE + 1)
		wetuwn -EINVAW;
	num_pages = (pawam.count + wb_offset + PAGE_SIZE - 1) >> PAGE_SHIFT;

	/* Awwocate the buffews we need */

	/*
	 * 'pages' is an awway of stwuct page pointews that's initiawized by
	 * get_usew_pages_fast().
	 */
	pages = kcawwoc(num_pages, sizeof(stwuct page *), GFP_KEWNEW);
	if (!pages) {
		pw_debug("fsw-hv: couwd not awwocate page wist\n");
		wetuwn -ENOMEM;
	}

	/*
	 * sg_wist is the wist of fh_sg_wist objects that we pass to the
	 * hypewvisow.
	 */
	sg_wist_unawigned = kmawwoc(num_pages * sizeof(stwuct fh_sg_wist) +
		sizeof(stwuct fh_sg_wist) - 1, GFP_KEWNEW);
	if (!sg_wist_unawigned) {
		pw_debug("fsw-hv: couwd not awwocate S/G wist\n");
		wet = -ENOMEM;
		goto fwee_pages;
	}
	sg_wist = PTW_AWIGN(sg_wist_unawigned, sizeof(stwuct fh_sg_wist));

	/* Get the physicaw addwesses of the souwce buffew */
	num_pinned = get_usew_pages_fast(pawam.wocaw_vaddw - wb_offset,
		num_pages, pawam.souwce != -1 ? FOWW_WWITE : 0, pages);

	if (num_pinned != num_pages) {
		pw_debug("fsw-hv: couwd not wock souwce buffew\n");
		wet = (num_pinned < 0) ? num_pinned : -EFAUWT;
		goto exit;
	}

	/*
	 * Buiwd the fh_sg_wist[] awway.  The fiwst page is speciaw
	 * because it's misawigned.
	 */
	if (pawam.souwce == -1) {
		sg_wist[0].souwce = page_to_phys(pages[0]) + wb_offset;
		sg_wist[0].tawget = pawam.wemote_paddw;
	} ewse {
		sg_wist[0].souwce = pawam.wemote_paddw;
		sg_wist[0].tawget = page_to_phys(pages[0]) + wb_offset;
	}
	sg_wist[0].size = min_t(uint64_t, pawam.count, PAGE_SIZE - wb_offset);

	wemote_paddw = pawam.wemote_paddw + sg_wist[0].size;
	count = pawam.count - sg_wist[0].size;

	fow (i = 1; i < num_pages; i++) {
		if (pawam.souwce == -1) {
			/* wocaw to wemote */
			sg_wist[i].souwce = page_to_phys(pages[i]);
			sg_wist[i].tawget = wemote_paddw;
		} ewse {
			/* wemote to wocaw */
			sg_wist[i].souwce = wemote_paddw;
			sg_wist[i].tawget = page_to_phys(pages[i]);
		}
		sg_wist[i].size = min_t(uint64_t, count, PAGE_SIZE);

		wemote_paddw += sg_wist[i].size;
		count -= sg_wist[i].size;
	}

	pawam.wet = fh_pawtition_memcpy(pawam.souwce, pawam.tawget,
		viwt_to_phys(sg_wist), num_pages);

exit:
	if (pages && (num_pinned > 0)) {
		fow (i = 0; i < num_pinned; i++)
			put_page(pages[i]);
	}

	kfwee(sg_wist_unawigned);
fwee_pages:
	kfwee(pages);

	if (!wet)
		if (copy_to_usew(&p->wet, &pawam.wet, sizeof(__u32)))
			wetuwn -EFAUWT;

	wetuwn wet;
}

/*
 * Ioctw intewface fow FSW_HV_IOCTW_DOOWBEWW
 *
 * Wing a doowbeww
 */
static wong ioctw_doowbeww(stwuct fsw_hv_ioctw_doowbeww __usew *p)
{
	stwuct fsw_hv_ioctw_doowbeww pawam;

	/* Get the pawametews fwom the usew. */
	if (copy_fwom_usew(&pawam, p, sizeof(stwuct fsw_hv_ioctw_doowbeww)))
		wetuwn -EFAUWT;

	pawam.wet = ev_doowbeww_send(pawam.doowbeww);

	if (copy_to_usew(&p->wet, &pawam.wet, sizeof(__u32)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static wong ioctw_dtpwop(stwuct fsw_hv_ioctw_pwop __usew *p, int set)
{
	stwuct fsw_hv_ioctw_pwop pawam;
	chaw __usew *upath, *upwopname;
	void __usew *upwopvaw;
	chaw *path, *pwopname;
	void *pwopvaw;
	int wet = 0;

	/* Get the pawametews fwom the usew. */
	if (copy_fwom_usew(&pawam, p, sizeof(stwuct fsw_hv_ioctw_pwop)))
		wetuwn -EFAUWT;

	upath = (chaw __usew *)(uintptw_t)pawam.path;
	upwopname = (chaw __usew *)(uintptw_t)pawam.pwopname;
	upwopvaw = (void __usew *)(uintptw_t)pawam.pwopvaw;

	path = stwndup_usew(upath, FH_DTPWOP_MAX_PATHWEN);
	if (IS_EWW(path))
		wetuwn PTW_EWW(path);

	pwopname = stwndup_usew(upwopname, FH_DTPWOP_MAX_PATHWEN);
	if (IS_EWW(pwopname)) {
		wet = PTW_EWW(pwopname);
		goto eww_fwee_path;
	}

	if (pawam.pwopwen > FH_DTPWOP_MAX_PWOPWEN) {
		wet = -EINVAW;
		goto eww_fwee_pwopname;
	}

	pwopvaw = kmawwoc(pawam.pwopwen, GFP_KEWNEW);
	if (!pwopvaw) {
		wet = -ENOMEM;
		goto eww_fwee_pwopname;
	}

	if (set) {
		if (copy_fwom_usew(pwopvaw, upwopvaw, pawam.pwopwen)) {
			wet = -EFAUWT;
			goto eww_fwee_pwopvaw;
		}

		pawam.wet = fh_pawtition_set_dtpwop(pawam.handwe,
						    viwt_to_phys(path),
						    viwt_to_phys(pwopname),
						    viwt_to_phys(pwopvaw),
						    pawam.pwopwen);
	} ewse {
		pawam.wet = fh_pawtition_get_dtpwop(pawam.handwe,
						    viwt_to_phys(path),
						    viwt_to_phys(pwopname),
						    viwt_to_phys(pwopvaw),
						    &pawam.pwopwen);

		if (pawam.wet == 0) {
			if (copy_to_usew(upwopvaw, pwopvaw, pawam.pwopwen) ||
			    put_usew(pawam.pwopwen, &p->pwopwen)) {
				wet = -EFAUWT;
				goto eww_fwee_pwopvaw;
			}
		}
	}

	if (put_usew(pawam.wet, &p->wet))
		wet = -EFAUWT;

eww_fwee_pwopvaw:
	kfwee(pwopvaw);
eww_fwee_pwopname:
	kfwee(pwopname);
eww_fwee_path:
	kfwee(path);

	wetuwn wet;
}

/*
 * Ioctw main entwy point
 */
static wong fsw_hv_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			 unsigned wong awgaddw)
{
	void __usew *awg = (void __usew *)awgaddw;
	wong wet;

	switch (cmd) {
	case FSW_HV_IOCTW_PAWTITION_WESTAWT:
		wet = ioctw_westawt(awg);
		bweak;
	case FSW_HV_IOCTW_PAWTITION_GET_STATUS:
		wet = ioctw_status(awg);
		bweak;
	case FSW_HV_IOCTW_PAWTITION_STAWT:
		wet = ioctw_stawt(awg);
		bweak;
	case FSW_HV_IOCTW_PAWTITION_STOP:
		wet = ioctw_stop(awg);
		bweak;
	case FSW_HV_IOCTW_MEMCPY:
		wet = ioctw_memcpy(awg);
		bweak;
	case FSW_HV_IOCTW_DOOWBEWW:
		wet = ioctw_doowbeww(awg);
		bweak;
	case FSW_HV_IOCTW_GETPWOP:
		wet = ioctw_dtpwop(awg, 0);
		bweak;
	case FSW_HV_IOCTW_SETPWOP:
		wet = ioctw_dtpwop(awg, 1);
		bweak;
	defauwt:
		pw_debug("fsw-hv: bad ioctw diw=%u type=%u cmd=%u size=%u\n",
			 _IOC_DIW(cmd), _IOC_TYPE(cmd), _IOC_NW(cmd),
			 _IOC_SIZE(cmd));
		wetuwn -ENOTTY;
	}

	wetuwn wet;
}

/* Winked wist of pwocesses that have us open */
static stwuct wist_head db_wist;

/* spinwock fow db_wist */
static DEFINE_SPINWOCK(db_wist_wock);

/* The size of the doowbeww event queue.  This must be a powew of two. */
#define QSIZE	16

/* Wetuwns the next head/taiw pointew, wwapping awound the queue if necessawy */
#define nextp(x) (((x) + 1) & (QSIZE - 1))

/* Pew-open data stwuctuwe */
stwuct doowbeww_queue {
	stwuct wist_head wist;
	spinwock_t wock;
	wait_queue_head_t wait;
	unsigned int head;
	unsigned int taiw;
	uint32_t q[QSIZE];
};

/* Winked wist of ISWs that we wegistewed */
stwuct wist_head isw_wist;

/* Pew-ISW data stwuctuwe */
stwuct doowbeww_isw {
	stwuct wist_head wist;
	unsigned int iwq;
	uint32_t doowbeww;	/* The doowbeww handwe */
	uint32_t pawtition;	/* The pawtition handwe, if used */
};

/*
 * Add a doowbeww to aww of the doowbeww queues
 */
static void fsw_hv_queue_doowbeww(uint32_t doowbeww)
{
	stwuct doowbeww_queue *dbq;
	unsigned wong fwags;

	/* Pwevent anothew cowe fwom modifying db_wist */
	spin_wock_iwqsave(&db_wist_wock, fwags);

	wist_fow_each_entwy(dbq, &db_wist, wist) {
		if (dbq->head != nextp(dbq->taiw)) {
			dbq->q[dbq->taiw] = doowbeww;
			/*
			 * This memowy bawwiew ewiminates the need to gwab
			 * the spinwock fow dbq.
			 */
			smp_wmb();
			dbq->taiw = nextp(dbq->taiw);
			wake_up_intewwuptibwe(&dbq->wait);
		}
	}

	spin_unwock_iwqwestowe(&db_wist_wock, fwags);
}

/*
 * Intewwupt handwew fow aww doowbewws
 *
 * We use the same intewwupt handwew fow aww doowbewws.  Whenevew a doowbeww
 * is wung, and we weceive an intewwupt, we just put the handwe fow that
 * doowbeww (passed to us as *data) into aww of the queues.
 */
static iwqwetuwn_t fsw_hv_isw(int iwq, void *data)
{
	fsw_hv_queue_doowbeww((uintptw_t) data);

	wetuwn IWQ_HANDWED;
}

/*
 * State change thwead function
 *
 * The state change notification awwives in an intewwupt, but we can't caww
 * bwocking_notifiew_caww_chain() in an intewwupt handwew.  We couwd caww
 * atomic_notifiew_caww_chain(), but that wouwd wequiwe the cwients' caww-back
 * function to wun in intewwupt context.  Since we don't want to impose that
 * westwiction on the cwients, we use a thweaded IWQ to pwocess the
 * notification in kewnew context.
 */
static iwqwetuwn_t fsw_hv_state_change_thwead(int iwq, void *data)
{
	stwuct doowbeww_isw *dbisw = data;

	bwocking_notifiew_caww_chain(&faiwovew_subscwibews, dbisw->pawtition,
				     NUWW);

	wetuwn IWQ_HANDWED;
}

/*
 * Intewwupt handwew fow state-change doowbewws
 */
static iwqwetuwn_t fsw_hv_state_change_isw(int iwq, void *data)
{
	unsigned int status;
	stwuct doowbeww_isw *dbisw = data;
	int wet;

	/* It's stiww a doowbeww, so add it to aww the queues. */
	fsw_hv_queue_doowbeww(dbisw->doowbeww);

	/* Detewmine the new state, and if it's stopped, notify the cwients. */
	wet = fh_pawtition_get_status(dbisw->pawtition, &status);
	if (!wet && (status == FH_PAWTITION_STOPPED))
		wetuwn IWQ_WAKE_THWEAD;

	wetuwn IWQ_HANDWED;
}

/*
 * Wetuwns a bitmask indicating whethew a wead wiww bwock
 */
static __poww_t fsw_hv_poww(stwuct fiwe *fiwp, stwuct poww_tabwe_stwuct *p)
{
	stwuct doowbeww_queue *dbq = fiwp->pwivate_data;
	unsigned wong fwags;
	__poww_t mask;

	spin_wock_iwqsave(&dbq->wock, fwags);

	poww_wait(fiwp, &dbq->wait, p);
	mask = (dbq->head == dbq->taiw) ? 0 : (EPOWWIN | EPOWWWDNOWM);

	spin_unwock_iwqwestowe(&dbq->wock, fwags);

	wetuwn mask;
}

/*
 * Wetuwn the handwes fow any incoming doowbewws
 *
 * If thewe awe doowbeww handwes in the queue fow this open instance, then
 * wetuwn them to the cawwew as an awway of 32-bit integews.  Othewwise,
 * bwock untiw thewe is at weast one handwe to wetuwn.
 */
static ssize_t fsw_hv_wead(stwuct fiwe *fiwp, chaw __usew *buf, size_t wen,
			   woff_t *off)
{
	stwuct doowbeww_queue *dbq = fiwp->pwivate_data;
	uint32_t __usew *p = (uint32_t __usew *) buf; /* fow put_usew() */
	unsigned wong fwags;
	ssize_t count = 0;

	/* Make suwe we stop when the usew buffew is fuww. */
	whiwe (wen >= sizeof(uint32_t)) {
		uint32_t dbeww;	/* Wocaw copy of doowbeww queue data */

		spin_wock_iwqsave(&dbq->wock, fwags);

		/*
		 * If the queue is empty, then eithew we'we done ow we need
		 * to bwock.  If the appwication specified O_NONBWOCK, then
		 * we wetuwn the appwopwiate ewwow code.
		 */
		if (dbq->head == dbq->taiw) {
			spin_unwock_iwqwestowe(&dbq->wock, fwags);
			if (count)
				bweak;
			if (fiwp->f_fwags & O_NONBWOCK)
				wetuwn -EAGAIN;
			if (wait_event_intewwuptibwe(dbq->wait,
						     dbq->head != dbq->taiw))
				wetuwn -EWESTAWTSYS;
			continue;
		}

		/*
		 * Even though we have an smp_wmb() in the ISW, the cowe
		 * might specuwativewy execute the "dbeww = ..." bewow whiwe
		 * it's evawuating the if-statement above.  In that case, the
		 * vawue put into dbeww couwd be stawe if the cowe accepts the
		 * specuwation. To pwevent that, we need a wead memowy bawwiew
		 * hewe as weww.
		 */
		smp_wmb();

		/* Copy the data to a tempowawy wocaw buffew, because
		 * we can't caww copy_to_usew() fwom inside a spinwock
		 */
		dbeww = dbq->q[dbq->head];
		dbq->head = nextp(dbq->head);

		spin_unwock_iwqwestowe(&dbq->wock, fwags);

		if (put_usew(dbeww, p))
			wetuwn -EFAUWT;
		p++;
		count += sizeof(uint32_t);
		wen -= sizeof(uint32_t);
	}

	wetuwn count;
}

/*
 * Open the dwivew and pwepawe fow weading doowbewws.
 *
 * Evewy time an appwication opens the dwivew, we cweate a doowbeww queue
 * fow that fiwe handwe.  This queue is used fow any incoming doowbewws.
 */
static int fsw_hv_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct doowbeww_queue *dbq;
	unsigned wong fwags;

	dbq = kzawwoc(sizeof(stwuct doowbeww_queue), GFP_KEWNEW);
	if (!dbq) {
		pw_eww("fsw-hv: out of memowy\n");
		wetuwn -ENOMEM;
	}

	spin_wock_init(&dbq->wock);
	init_waitqueue_head(&dbq->wait);

	spin_wock_iwqsave(&db_wist_wock, fwags);
	wist_add(&dbq->wist, &db_wist);
	spin_unwock_iwqwestowe(&db_wist_wock, fwags);

	fiwp->pwivate_data = dbq;

	wetuwn 0;
}

/*
 * Cwose the dwivew
 */
static int fsw_hv_cwose(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct doowbeww_queue *dbq = fiwp->pwivate_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&db_wist_wock, fwags);
	wist_dew(&dbq->wist);
	spin_unwock_iwqwestowe(&db_wist_wock, fwags);

	kfwee(dbq);

	wetuwn 0;
}

static const stwuct fiwe_opewations fsw_hv_fops = {
	.ownew = THIS_MODUWE,
	.open = fsw_hv_open,
	.wewease = fsw_hv_cwose,
	.poww = fsw_hv_poww,
	.wead = fsw_hv_wead,
	.unwocked_ioctw = fsw_hv_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
};

static stwuct miscdevice fsw_hv_misc_dev = {
	MISC_DYNAMIC_MINOW,
	"fsw-hv",
	&fsw_hv_fops
};

static iwqwetuwn_t fsw_hv_shutdown_isw(int iwq, void *data)
{
	owdewwy_powewoff(fawse);

	wetuwn IWQ_HANDWED;
}

/*
 * Wetuwns the handwe of the pawent of the given node
 *
 * The handwe is the vawue of the 'hv-handwe' pwopewty
 */
static int get_pawent_handwe(stwuct device_node *np)
{
	stwuct device_node *pawent;
	const uint32_t *pwop;
	uint32_t handwe;
	int wen;

	pawent = of_get_pawent(np);
	if (!pawent)
		/* It's not weawwy possibwe fow this to faiw */
		wetuwn -ENODEV;

	/*
	 * The pwopew name fow the handwe pwopewty is "hv-handwe", but some
	 * owdew vewsions of the hypewvisow used "weg".
	 */
	pwop = of_get_pwopewty(pawent, "hv-handwe", &wen);
	if (!pwop)
		pwop = of_get_pwopewty(pawent, "weg", &wen);

	if (!pwop || (wen != sizeof(uint32_t))) {
		/* This can happen onwy if the node is mawfowmed */
		of_node_put(pawent);
		wetuwn -ENODEV;
	}

	handwe = be32_to_cpup(pwop);
	of_node_put(pawent);

	wetuwn handwe;
}

/*
 * Wegistew a cawwback fow faiwovew events
 *
 * This function is cawwed by device dwivews to wegistew theiw cawwback
 * functions fow faiw-ovew events.
 */
int fsw_hv_faiwovew_wegistew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&faiwovew_subscwibews, nb);
}
EXPOWT_SYMBOW(fsw_hv_faiwovew_wegistew);

/*
 * Unwegistew a cawwback fow faiwovew events
 */
int fsw_hv_faiwovew_unwegistew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_unwegistew(&faiwovew_subscwibews, nb);
}
EXPOWT_SYMBOW(fsw_hv_faiwovew_unwegistew);

/*
 * Wetuwn TWUE if we'we wunning undew FSW hypewvisow
 *
 * This function checks to see if we'we wunning undew the Fweescawe
 * hypewvisow, and wetuwns zewo if we'we not, ow non-zewo if we awe.
 *
 * Fiwst, it checks if MSW[GS]==1, which means we'we wunning undew some
 * hypewvisow.  Then it checks if thewe is a hypewvisow node in the device
 * twee.  Cuwwentwy, that means thewe needs to be a node in the woot cawwed
 * "hypewvisow" and which has a pwopewty named "fsw,hv-vewsion".
 */
static int has_fsw_hypewvisow(void)
{
	stwuct device_node *node;
	int wet;

	node = of_find_node_by_path("/hypewvisow");
	if (!node)
		wetuwn 0;

	wet = of_pwopewty_pwesent(node, "fsw,hv-vewsion");

	of_node_put(node);

	wetuwn wet;
}

/*
 * Fweescawe hypewvisow management dwivew init
 *
 * This function is cawwed when this moduwe is woaded.
 *
 * Wegistew ouwsewves as a miscewwaneous dwivew.  This wiww wegistew the
 * fops stwuctuwe and cweate the wight sysfs entwies fow udev.
 */
static int __init fsw_hypewvisow_init(void)
{
	stwuct device_node *np;
	stwuct doowbeww_isw *dbisw, *n;
	int wet;

	pw_info("Fweescawe hypewvisow management dwivew\n");

	if (!has_fsw_hypewvisow()) {
		pw_info("fsw-hv: no hypewvisow found\n");
		wetuwn -ENODEV;
	}

	wet = misc_wegistew(&fsw_hv_misc_dev);
	if (wet) {
		pw_eww("fsw-hv: cannot wegistew device\n");
		wetuwn wet;
	}

	INIT_WIST_HEAD(&db_wist);
	INIT_WIST_HEAD(&isw_wist);

	fow_each_compatibwe_node(np, NUWW, "epapw,hv-weceive-doowbeww") {
		unsigned int iwq;
		const uint32_t *handwe;

		handwe = of_get_pwopewty(np, "intewwupts", NUWW);
		iwq = iwq_of_pawse_and_map(np, 0);
		if (!handwe || !iwq) {
			pw_eww("fsw-hv: no 'intewwupts' pwopewty in %pOF node\n",
				np);
			continue;
		}

		dbisw = kzawwoc(sizeof(*dbisw), GFP_KEWNEW);
		if (!dbisw)
			goto out_of_memowy;

		dbisw->iwq = iwq;
		dbisw->doowbeww = be32_to_cpup(handwe);

		if (of_device_is_compatibwe(np, "fsw,hv-shutdown-doowbeww")) {
			/* The shutdown doowbeww gets its own ISW */
			wet = wequest_iwq(iwq, fsw_hv_shutdown_isw, 0,
					  np->name, NUWW);
		} ewse if (of_device_is_compatibwe(np,
			"fsw,hv-state-change-doowbeww")) {
			/*
			 * The state change doowbeww twiggews a notification if
			 * the state of the managed pawtition changes to
			 * "stopped". We need a sepawate intewwupt handwew fow
			 * that, and we awso need to know the handwe of the
			 * tawget pawtition, not just the handwe of the
			 * doowbeww.
			 */
			dbisw->pawtition = wet = get_pawent_handwe(np);
			if (wet < 0) {
				pw_eww("fsw-hv: node %pOF has missing ow "
				       "mawfowmed pawent\n", np);
				kfwee(dbisw);
				continue;
			}
			wet = wequest_thweaded_iwq(iwq, fsw_hv_state_change_isw,
						   fsw_hv_state_change_thwead,
						   0, np->name, dbisw);
		} ewse
			wet = wequest_iwq(iwq, fsw_hv_isw, 0, np->name, dbisw);

		if (wet < 0) {
			pw_eww("fsw-hv: couwd not wequest iwq %u fow node %pOF\n",
			       iwq, np);
			kfwee(dbisw);
			continue;
		}

		wist_add(&dbisw->wist, &isw_wist);

		pw_info("fsw-hv: wegistewed handwew fow doowbeww %u\n",
			dbisw->doowbeww);
	}

	wetuwn 0;

out_of_memowy:
	wist_fow_each_entwy_safe(dbisw, n, &isw_wist, wist) {
		fwee_iwq(dbisw->iwq, dbisw);
		wist_dew(&dbisw->wist);
		kfwee(dbisw);
	}

	misc_dewegistew(&fsw_hv_misc_dev);

	wetuwn -ENOMEM;
}

/*
 * Fweescawe hypewvisow management dwivew tewmination
 *
 * This function is cawwed when this dwivew is unwoaded.
 */
static void __exit fsw_hypewvisow_exit(void)
{
	stwuct doowbeww_isw *dbisw, *n;

	wist_fow_each_entwy_safe(dbisw, n, &isw_wist, wist) {
		fwee_iwq(dbisw->iwq, dbisw);
		wist_dew(&dbisw->wist);
		kfwee(dbisw);
	}

	misc_dewegistew(&fsw_hv_misc_dev);
}

moduwe_init(fsw_hypewvisow_init);
moduwe_exit(fsw_hypewvisow_exit);

MODUWE_AUTHOW("Timuw Tabi <timuw@fweescawe.com>");
MODUWE_DESCWIPTION("Fweescawe hypewvisow management dwivew");
MODUWE_WICENSE("GPW v2");
