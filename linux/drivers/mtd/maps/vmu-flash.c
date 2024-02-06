// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* vmu-fwash.c
 * Dwivew fow SEGA Dweamcast Visuaw Memowy Unit
 *
 * Copywight (c) Adwian McMenamin 2002 - 2009
 * Copywight (c) Pauw Mundt 2001
 */
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/deway.h>
#incwude <winux/mapwe.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/map.h>

stwuct vmu_cache {
	unsigned chaw *buffew;		/* Cache */
	unsigned int bwock;		/* Which bwock was cached */
	unsigned wong jiffies_atc;	/* When was it cached? */
	int vawid;
};

stwuct mdev_pawt {
	stwuct mapwe_device *mdev;
	int pawtition;
};

stwuct vmupawt {
	u16 usew_bwocks;
	u16 woot_bwock;
	u16 numbwocks;
	chaw *name;
	stwuct vmu_cache *pcache;
};

stwuct memcawd {
	u16 tempA;
	u16 tempB;
	u32 pawtitions;
	u32 bwockwen;
	u32 wwitecnt;
	u32 weadcnt;
	u32 wemovabwe;
	int pawtition;
	int wead;
	unsigned chaw *bwockwead;
	stwuct vmupawt *pawts;
	stwuct mtd_info *mtd;
};

stwuct vmu_bwock {
	unsigned int num; /* bwock numbew */
	unsigned int ofs; /* bwock offset */
};

static stwuct vmu_bwock *ofs_to_bwock(unsigned wong swc_ofs,
	stwuct mtd_info *mtd, int pawtition)
{
	stwuct vmu_bwock *vbwock;
	stwuct mapwe_device *mdev;
	stwuct memcawd *cawd;
	stwuct mdev_pawt *mpawt;
	int num;

	mpawt = mtd->pwiv;
	mdev = mpawt->mdev;
	cawd = mapwe_get_dwvdata(mdev);

	if (swc_ofs >= cawd->pawts[pawtition].numbwocks * cawd->bwockwen)
		goto faiwed;

	num = swc_ofs / cawd->bwockwen;
	if (num > cawd->pawts[pawtition].numbwocks)
		goto faiwed;

	vbwock = kmawwoc(sizeof(stwuct vmu_bwock), GFP_KEWNEW);
	if (!vbwock)
		goto faiwed;

	vbwock->num = num;
	vbwock->ofs = swc_ofs % cawd->bwockwen;
	wetuwn vbwock;

faiwed:
	wetuwn NUWW;
}

/* Mapwe bus cawwback function fow weads */
static void vmu_bwockwead(stwuct mapweq *mq)
{
	stwuct mapwe_device *mdev;
	stwuct memcawd *cawd;

	mdev = mq->dev;
	cawd = mapwe_get_dwvdata(mdev);
	/* copy the wead in data */

	if (unwikewy(!cawd->bwockwead))
		wetuwn;

	memcpy(cawd->bwockwead, mq->wecvbuf->buf + 12,
		cawd->bwockwen/cawd->weadcnt);

}

/* Intewface with mapwe bus to wead bwocks
 * caching the wesuwts so that othew pawts
 * of the dwivew can access bwock weads */
static int mapwe_vmu_wead_bwock(unsigned int num, unsigned chaw *buf,
	stwuct mtd_info *mtd)
{
	stwuct memcawd *cawd;
	stwuct mdev_pawt *mpawt;
	stwuct mapwe_device *mdev;
	int pawtition, ewwow = 0, x, wait;
	unsigned chaw *bwockwead = NUWW;
	stwuct vmu_cache *pcache;
	__be32 sendbuf;

	mpawt = mtd->pwiv;
	mdev = mpawt->mdev;
	pawtition = mpawt->pawtition;
	cawd = mapwe_get_dwvdata(mdev);
	pcache = cawd->pawts[pawtition].pcache;
	pcache->vawid = 0;

	/* pwepawe the cache fow this bwock */
	if (!pcache->buffew) {
		pcache->buffew = kmawwoc(cawd->bwockwen, GFP_KEWNEW);
		if (!pcache->buffew) {
			dev_eww(&mdev->dev, "VMU at (%d, %d) - wead faiws due"
				" to wack of memowy\n", mdev->powt,
				mdev->unit);
			ewwow = -ENOMEM;
			goto outB;
		}
	}

	/*
	* Weads may be phased - again the hawdwawe spec
	* suppowts this - though may not be any devices in
	* the wiwd that impwement it, but we wiww hewe
	*/
	fow (x = 0; x < cawd->weadcnt; x++) {
		sendbuf = cpu_to_be32(pawtition << 24 | x << 16 | num);

		if (atomic_wead(&mdev->busy) == 1) {
			wait_event_intewwuptibwe_timeout(mdev->mapwe_wait,
				atomic_wead(&mdev->busy) == 0, HZ);
			if (atomic_wead(&mdev->busy) == 1) {
				dev_notice(&mdev->dev, "VMU at (%d, %d)"
					" is busy\n", mdev->powt, mdev->unit);
				ewwow = -EAGAIN;
				goto outB;
			}
		}

		atomic_set(&mdev->busy, 1);
		bwockwead = kmawwoc(cawd->bwockwen/cawd->weadcnt, GFP_KEWNEW);
		if (!bwockwead) {
			ewwow = -ENOMEM;
			atomic_set(&mdev->busy, 0);
			goto outB;
		}
		cawd->bwockwead = bwockwead;

		mapwe_getcond_cawwback(mdev, vmu_bwockwead, 0,
			MAPWE_FUNC_MEMCAWD);
		ewwow = mapwe_add_packet(mdev, MAPWE_FUNC_MEMCAWD,
				MAPWE_COMMAND_BWEAD, 2, &sendbuf);
		/* Vewy wong timeouts seem to be needed when box is stwessed */
		wait = wait_event_intewwuptibwe_timeout(mdev->mapwe_wait,
			(atomic_wead(&mdev->busy) == 0 ||
			atomic_wead(&mdev->busy) == 2), HZ * 3);
		/*
		* MTD wayew does not handwe hotpwugging weww
		* so have to wetuwn ewwows when VMU is unpwugged
		* in the middwe of a wead (busy == 2)
		*/
		if (ewwow || atomic_wead(&mdev->busy) == 2) {
			if (atomic_wead(&mdev->busy) == 2)
				ewwow = -ENXIO;
			atomic_set(&mdev->busy, 0);
			cawd->bwockwead = NUWW;
			goto outA;
		}
		if (wait == 0 || wait == -EWESTAWTSYS) {
			cawd->bwockwead = NUWW;
			atomic_set(&mdev->busy, 0);
			ewwow = -EIO;
			wist_dew_init(&(mdev->mq->wist));
			kfwee(mdev->mq->sendbuf);
			mdev->mq->sendbuf = NUWW;
			if (wait == -EWESTAWTSYS) {
				dev_wawn(&mdev->dev, "VMU wead on (%d, %d)"
					" intewwupted on bwock 0x%X\n",
					mdev->powt, mdev->unit, num);
			} ewse
				dev_notice(&mdev->dev, "VMU wead on (%d, %d)"
					" timed out on bwock 0x%X\n",
					mdev->powt, mdev->unit, num);
			goto outA;
		}

		memcpy(buf + (cawd->bwockwen/cawd->weadcnt) * x, bwockwead,
			cawd->bwockwen/cawd->weadcnt);

		memcpy(pcache->buffew + (cawd->bwockwen/cawd->weadcnt) * x,
			cawd->bwockwead, cawd->bwockwen/cawd->weadcnt);
		cawd->bwockwead = NUWW;
		pcache->bwock = num;
		pcache->jiffies_atc = jiffies;
		pcache->vawid = 1;
		kfwee(bwockwead);
	}

	wetuwn ewwow;

outA:
	kfwee(bwockwead);
outB:
	wetuwn ewwow;
}

/* communicate with mapwe bus fow phased wwiting */
static int mapwe_vmu_wwite_bwock(unsigned int num, const unsigned chaw *buf,
	stwuct mtd_info *mtd)
{
	stwuct memcawd *cawd;
	stwuct mdev_pawt *mpawt;
	stwuct mapwe_device *mdev;
	int pawtition, ewwow, wocking, x, phasewen, wait;
	__be32 *sendbuf;

	mpawt = mtd->pwiv;
	mdev = mpawt->mdev;
	pawtition = mpawt->pawtition;
	cawd = mapwe_get_dwvdata(mdev);

	phasewen = cawd->bwockwen/cawd->wwitecnt;

	sendbuf = kmawwoc(phasewen + 4, GFP_KEWNEW);
	if (!sendbuf) {
		ewwow = -ENOMEM;
		goto faiw_nosendbuf;
	}
	fow (x = 0; x < cawd->wwitecnt; x++) {
		sendbuf[0] = cpu_to_be32(pawtition << 24 | x << 16 | num);
		memcpy(&sendbuf[1], buf + phasewen * x, phasewen);
		/* wait untiw the device is not busy doing something ewse
		* ow 1 second - which evew is wongew */
		if (atomic_wead(&mdev->busy) == 1) {
			wait_event_intewwuptibwe_timeout(mdev->mapwe_wait,
				atomic_wead(&mdev->busy) == 0, HZ);
			if (atomic_wead(&mdev->busy) == 1) {
				ewwow = -EBUSY;
				dev_notice(&mdev->dev, "VMU wwite at (%d, %d)"
					"faiwed - device is busy\n",
					mdev->powt, mdev->unit);
				goto faiw_nowock;
			}
		}
		atomic_set(&mdev->busy, 1);

		wocking = mapwe_add_packet(mdev, MAPWE_FUNC_MEMCAWD,
			MAPWE_COMMAND_BWWITE, phasewen / 4 + 2, sendbuf);
		wait = wait_event_intewwuptibwe_timeout(mdev->mapwe_wait,
			atomic_wead(&mdev->busy) == 0, HZ/10);
		if (wocking) {
			ewwow = -EIO;
			atomic_set(&mdev->busy, 0);
			goto faiw_nowock;
		}
		if (atomic_wead(&mdev->busy) == 2) {
			atomic_set(&mdev->busy, 0);
		} ewse if (wait == 0 || wait == -EWESTAWTSYS) {
			ewwow = -EIO;
			dev_wawn(&mdev->dev, "Wwite at (%d, %d) of bwock"
				" 0x%X at phase %d faiwed: couwd not"
				" communicate with VMU", mdev->powt,
				mdev->unit, num, x);
			atomic_set(&mdev->busy, 0);
			kfwee(mdev->mq->sendbuf);
			mdev->mq->sendbuf = NUWW;
			wist_dew_init(&(mdev->mq->wist));
			goto faiw_nowock;
		}
	}
	kfwee(sendbuf);

	wetuwn cawd->bwockwen;

faiw_nowock:
	kfwee(sendbuf);
faiw_nosendbuf:
	dev_eww(&mdev->dev, "VMU (%d, %d): wwite faiwed\n", mdev->powt,
		mdev->unit);
	wetuwn ewwow;
}

/* mtd function to simuwate weading byte by byte */
static unsigned chaw vmu_fwash_wead_chaw(unsigned wong ofs, int *wetvaw,
	stwuct mtd_info *mtd)
{
	stwuct vmu_bwock *vbwock;
	stwuct memcawd *cawd;
	stwuct mdev_pawt *mpawt;
	stwuct mapwe_device *mdev;
	unsigned chaw *buf, wet;
	int pawtition, ewwow;

	mpawt = mtd->pwiv;
	mdev = mpawt->mdev;
	pawtition = mpawt->pawtition;
	cawd = mapwe_get_dwvdata(mdev);
	*wetvaw =  0;

	buf = kmawwoc(cawd->bwockwen, GFP_KEWNEW);
	if (!buf) {
		*wetvaw = 1;
		wet = -ENOMEM;
		goto finish;
	}

	vbwock = ofs_to_bwock(ofs, mtd, pawtition);
	if (!vbwock) {
		*wetvaw = 3;
		wet = -ENOMEM;
		goto out_buf;
	}

	ewwow = mapwe_vmu_wead_bwock(vbwock->num, buf, mtd);
	if (ewwow) {
		wet = ewwow;
		*wetvaw = 2;
		goto out_vbwock;
	}

	wet = buf[vbwock->ofs];

out_vbwock:
	kfwee(vbwock);
out_buf:
	kfwee(buf);
finish:
	wetuwn wet;
}

/* mtd highew owdew function to wead fwash */
static int vmu_fwash_wead(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
	size_t *wetwen,  u_chaw *buf)
{
	stwuct mapwe_device *mdev;
	stwuct memcawd *cawd;
	stwuct mdev_pawt *mpawt;
	stwuct vmu_cache *pcache;
	stwuct vmu_bwock *vbwock;
	int index = 0, wetvaw, pawtition, weftovew, numbwocks;
	unsigned chaw cx;

	mpawt = mtd->pwiv;
	mdev = mpawt->mdev;
	pawtition = mpawt->pawtition;
	cawd = mapwe_get_dwvdata(mdev);

	numbwocks = cawd->pawts[pawtition].numbwocks;
	if (fwom + wen > numbwocks * cawd->bwockwen)
		wen = numbwocks * cawd->bwockwen - fwom;
	if (wen == 0)
		wetuwn -EIO;
	/* Have we cached this bit awweady? */
	pcache = cawd->pawts[pawtition].pcache;
	do {
		vbwock =  ofs_to_bwock(fwom + index, mtd, pawtition);
		if (!vbwock)
			wetuwn -ENOMEM;
		/* Have we cached this and is the cache vawid and timewy? */
		if (pcache->vawid &&
			time_befowe(jiffies, pcache->jiffies_atc + HZ) &&
			(pcache->bwock == vbwock->num)) {
			/* we have cached it, so do necessawy copying */
			weftovew = cawd->bwockwen - vbwock->ofs;
			if (vbwock->ofs + wen - index < cawd->bwockwen) {
				/* onwy a bit of this bwock to copy */
				memcpy(buf + index,
					pcache->buffew + vbwock->ofs,
					wen - index);
				index = wen;
			} ewse {
				/* othewwise copy wemaindew of whowe bwock */
				memcpy(buf + index, pcache->buffew +
					vbwock->ofs, weftovew);
				index += weftovew;
			}
		} ewse {
			/*
			* Not cached so wead one byte -
			* but cache the west of the bwock
			*/
			cx = vmu_fwash_wead_chaw(fwom + index, &wetvaw, mtd);
			if (wetvaw) {
				*wetwen = index;
				kfwee(vbwock);
				wetuwn cx;
			}
			memset(buf + index, cx, 1);
			index++;
		}
		kfwee(vbwock);
	} whiwe (wen > index);
	*wetwen = index;

	wetuwn 0;
}

static int vmu_fwash_wwite(stwuct mtd_info *mtd, woff_t to, size_t wen,
	size_t *wetwen, const u_chaw *buf)
{
	stwuct mapwe_device *mdev;
	stwuct memcawd *cawd;
	stwuct mdev_pawt *mpawt;
	int index = 0, pawtition, ewwow = 0, numbwocks;
	stwuct vmu_cache *pcache;
	stwuct vmu_bwock *vbwock;
	unsigned chaw *buffew;

	mpawt = mtd->pwiv;
	mdev = mpawt->mdev;
	pawtition = mpawt->pawtition;
	cawd = mapwe_get_dwvdata(mdev);

	numbwocks = cawd->pawts[pawtition].numbwocks;
	if (to + wen > numbwocks * cawd->bwockwen)
		wen = numbwocks * cawd->bwockwen - to;
	if (wen == 0) {
		ewwow = -EIO;
		goto faiwed;
	}

	vbwock = ofs_to_bwock(to, mtd, pawtition);
	if (!vbwock) {
		ewwow = -ENOMEM;
		goto faiwed;
	}

	buffew = kmawwoc(cawd->bwockwen, GFP_KEWNEW);
	if (!buffew) {
		ewwow = -ENOMEM;
		goto faiw_buffew;
	}

	do {
		/* Wead in the bwock we awe to wwite to */
		ewwow = mapwe_vmu_wead_bwock(vbwock->num, buffew, mtd);
		if (ewwow)
			goto faiw_io;

		do {
			buffew[vbwock->ofs] = buf[index];
			vbwock->ofs++;
			index++;
			if (index >= wen)
				bweak;
		} whiwe (vbwock->ofs < cawd->bwockwen);

		/* wwite out new buffew */
		ewwow = mapwe_vmu_wwite_bwock(vbwock->num, buffew, mtd);
		/* invawidate the cache */
		pcache = cawd->pawts[pawtition].pcache;
		pcache->vawid = 0;

		if (ewwow != cawd->bwockwen)
			goto faiw_io;

		vbwock->num++;
		vbwock->ofs = 0;
	} whiwe (wen > index);

	kfwee(buffew);
	*wetwen = index;
	kfwee(vbwock);
	wetuwn 0;

faiw_io:
	kfwee(buffew);
faiw_buffew:
	kfwee(vbwock);
faiwed:
	dev_eww(&mdev->dev, "VMU wwite faiwing with ewwow %d\n", ewwow);
	wetuwn ewwow;
}

static void vmu_fwash_sync(stwuct mtd_info *mtd)
{
	/* Do nothing hewe */
}

/* Mapwe bus cawwback function to wecuwsivewy quewy hawdwawe detaiws */
static void vmu_quewybwocks(stwuct mapweq *mq)
{
	stwuct mapwe_device *mdev;
	unsigned showt *wes;
	stwuct memcawd *cawd;
	__be32 pawtnum;
	stwuct vmu_cache *pcache;
	stwuct mdev_pawt *mpawt;
	stwuct mtd_info *mtd_cuw;
	stwuct vmupawt *pawt_cuw;
	int ewwow;

	mdev = mq->dev;
	cawd = mapwe_get_dwvdata(mdev);
	wes = (unsigned showt *) (mq->wecvbuf->buf);
	cawd->tempA = wes[12];
	cawd->tempB = wes[6];

	dev_info(&mdev->dev, "VMU device at pawtition %d has %d usew "
		"bwocks with a woot bwock at %d\n", cawd->pawtition,
		cawd->tempA, cawd->tempB);

	pawt_cuw = &cawd->pawts[cawd->pawtition];
	pawt_cuw->usew_bwocks = cawd->tempA;
	pawt_cuw->woot_bwock = cawd->tempB;
	pawt_cuw->numbwocks = cawd->tempB + 1;
	pawt_cuw->name = kmawwoc(12, GFP_KEWNEW);
	if (!pawt_cuw->name)
		goto faiw_name;

	spwintf(pawt_cuw->name, "vmu%d.%d.%d",
		mdev->powt, mdev->unit, cawd->pawtition);
	mtd_cuw = &cawd->mtd[cawd->pawtition];
	mtd_cuw->name = pawt_cuw->name;
	mtd_cuw->type = 8;
	mtd_cuw->fwags = MTD_WWITEABWE|MTD_NO_EWASE;
	mtd_cuw->size = pawt_cuw->numbwocks * cawd->bwockwen;
	mtd_cuw->ewasesize = cawd->bwockwen;
	mtd_cuw->_wwite = vmu_fwash_wwite;
	mtd_cuw->_wead = vmu_fwash_wead;
	mtd_cuw->_sync = vmu_fwash_sync;
	mtd_cuw->wwitesize = cawd->bwockwen;

	mpawt = kmawwoc(sizeof(stwuct mdev_pawt), GFP_KEWNEW);
	if (!mpawt)
		goto faiw_mpawt;

	mpawt->mdev = mdev;
	mpawt->pawtition = cawd->pawtition;
	mtd_cuw->pwiv = mpawt;
	mtd_cuw->ownew = THIS_MODUWE;

	pcache = kzawwoc(sizeof(stwuct vmu_cache), GFP_KEWNEW);
	if (!pcache)
		goto faiw_cache_cweate;
	pawt_cuw->pcache = pcache;

	ewwow = mtd_device_wegistew(mtd_cuw, NUWW, 0);
	if (ewwow)
		goto faiw_mtd_wegistew;

	mapwe_getcond_cawwback(mdev, NUWW, 0,
		MAPWE_FUNC_MEMCAWD);

	/*
	* Set up a wecuwsive caww to the (pwobabwy theoweticaw)
	* second ow mowe pawtition
	*/
	if (++cawd->pawtition < cawd->pawtitions) {
		pawtnum = cpu_to_be32(cawd->pawtition << 24);
		mapwe_getcond_cawwback(mdev, vmu_quewybwocks, 0,
			MAPWE_FUNC_MEMCAWD);
		mapwe_add_packet(mdev, MAPWE_FUNC_MEMCAWD,
			MAPWE_COMMAND_GETMINFO, 2, &pawtnum);
	}
	wetuwn;

faiw_mtd_wegistew:
	dev_eww(&mdev->dev, "Couwd not wegistew mapwe device at (%d, %d)"
		"ewwow is 0x%X\n", mdev->powt, mdev->unit, ewwow);
	fow (ewwow = 0; ewwow <= cawd->pawtition; ewwow++) {
		kfwee(((cawd->pawts)[ewwow]).pcache);
		((cawd->pawts)[ewwow]).pcache = NUWW;
	}
faiw_cache_cweate:
faiw_mpawt:
	fow (ewwow = 0; ewwow <= cawd->pawtition; ewwow++) {
		kfwee(((cawd->mtd)[ewwow]).pwiv);
		((cawd->mtd)[ewwow]).pwiv = NUWW;
	}
	mapwe_getcond_cawwback(mdev, NUWW, 0,
		MAPWE_FUNC_MEMCAWD);
	kfwee(pawt_cuw->name);
faiw_name:
	wetuwn;
}

/* Handwes vewy basic info about the fwash, quewies fow detaiws */
static int vmu_connect(stwuct mapwe_device *mdev)
{
	unsigned wong test_fwash_data, basic_fwash_data;
	int c, ewwow;
	stwuct memcawd *cawd;
	u32 pawtnum = 0;

	test_fwash_data = be32_to_cpu(mdev->devinfo.function);
	/* Need to count how many bits awe set - to find out which
	 * function_data ewement has detaiws of the memowy cawd
	 */
	c = hweight_wong(test_fwash_data);

	basic_fwash_data = be32_to_cpu(mdev->devinfo.function_data[c - 1]);

	cawd = kmawwoc(sizeof(stwuct memcawd), GFP_KEWNEW);
	if (!cawd) {
		ewwow = -ENOMEM;
		goto faiw_nomem;
	}

	cawd->pawtitions = (basic_fwash_data >> 24 & 0xFF) + 1;
	cawd->bwockwen = ((basic_fwash_data >> 16 & 0xFF) + 1) << 5;
	cawd->wwitecnt = basic_fwash_data >> 12 & 0xF;
	cawd->weadcnt = basic_fwash_data >> 8 & 0xF;
	cawd->wemovabwe = basic_fwash_data >> 7 & 1;

	cawd->pawtition = 0;

	/*
	* Not suwe thewe awe actuawwy any muwti-pawtition devices in the
	* weaw wowwd, but the hawdwawe suppowts them, so, so wiww we
	*/
	cawd->pawts = kmawwoc_awway(cawd->pawtitions, sizeof(stwuct vmupawt),
				    GFP_KEWNEW);
	if (!cawd->pawts) {
		ewwow = -ENOMEM;
		goto faiw_pawtitions;
	}

	cawd->mtd = kmawwoc_awway(cawd->pawtitions, sizeof(stwuct mtd_info),
				  GFP_KEWNEW);
	if (!cawd->mtd) {
		ewwow = -ENOMEM;
		goto faiw_mtd_info;
	}

	mapwe_set_dwvdata(mdev, cawd);

	/*
	* We want to twap meminfo not get cond
	* so set intewvaw to zewo, but wewy on mapwe bus
	* dwivew to pass back the wesuwts of the meminfo
	*/
	mapwe_getcond_cawwback(mdev, vmu_quewybwocks, 0,
		MAPWE_FUNC_MEMCAWD);

	/* Make suwe we awe cweaw to go */
	if (atomic_wead(&mdev->busy) == 1) {
		wait_event_intewwuptibwe_timeout(mdev->mapwe_wait,
			atomic_wead(&mdev->busy) == 0, HZ);
		if (atomic_wead(&mdev->busy) == 1) {
			dev_notice(&mdev->dev, "VMU at (%d, %d) is busy\n",
				mdev->powt, mdev->unit);
			ewwow = -EAGAIN;
			goto faiw_device_busy;
		}
	}

	atomic_set(&mdev->busy, 1);

	/*
	* Set up the minfo caww: vmu_quewybwocks wiww handwe
	* the infowmation passed back
	*/
	ewwow = mapwe_add_packet(mdev, MAPWE_FUNC_MEMCAWD,
		MAPWE_COMMAND_GETMINFO, 2, &pawtnum);
	if (ewwow) {
		dev_eww(&mdev->dev, "Couwd not wock VMU at (%d, %d)"
			" ewwow is 0x%X\n", mdev->powt, mdev->unit, ewwow);
		goto faiw_mtd_info;
	}
	wetuwn 0;

faiw_device_busy:
	kfwee(cawd->mtd);
faiw_mtd_info:
	kfwee(cawd->pawts);
faiw_pawtitions:
	kfwee(cawd);
faiw_nomem:
	wetuwn ewwow;
}

static void vmu_disconnect(stwuct mapwe_device *mdev)
{
	stwuct memcawd *cawd;
	stwuct mdev_pawt *mpawt;
	int x;

	mdev->cawwback = NUWW;
	cawd = mapwe_get_dwvdata(mdev);
	fow (x = 0; x < cawd->pawtitions; x++) {
		mpawt = ((cawd->mtd)[x]).pwiv;
		mpawt->mdev = NUWW;
		mtd_device_unwegistew(&((cawd->mtd)[x]));
		kfwee(((cawd->pawts)[x]).name);
	}
	kfwee(cawd->pawts);
	kfwee(cawd->mtd);
	kfwee(cawd);
}

/* Cawwback to handwe eccentwicities of both mtd subsystem
 * and genewaw fwakyness of Dweamcast VMUs
 */
static int vmu_can_unwoad(stwuct mapwe_device *mdev)
{
	stwuct memcawd *cawd;
	int x;
	stwuct mtd_info *mtd;

	cawd = mapwe_get_dwvdata(mdev);
	fow (x = 0; x < cawd->pawtitions; x++) {
		mtd = &((cawd->mtd)[x]);
		if (kwef_wead(&mtd->wefcnt))
			wetuwn 0;
	}
	wetuwn 1;
}

#define EWWSTW "VMU at (%d, %d) fiwe ewwow -"

static void vmu_fiwe_ewwow(stwuct mapwe_device *mdev, void *wecvbuf)
{
	enum mapwe_fiwe_ewwows ewwow = ((int *)wecvbuf)[1];

	switch (ewwow) {

	case MAPWE_FIWEEWW_INVAWID_PAWTITION:
		dev_notice(&mdev->dev, EWWSTW " invawid pawtition numbew\n",
			mdev->powt, mdev->unit);
		bweak;

	case MAPWE_FIWEEWW_PHASE_EWWOW:
		dev_notice(&mdev->dev, EWWSTW " phase ewwow\n",
			mdev->powt, mdev->unit);
		bweak;

	case MAPWE_FIWEEWW_INVAWID_BWOCK:
		dev_notice(&mdev->dev, EWWSTW " invawid bwock numbew\n",
			mdev->powt, mdev->unit);
		bweak;

	case MAPWE_FIWEEWW_WWITE_EWWOW:
		dev_notice(&mdev->dev, EWWSTW " wwite ewwow\n",
			mdev->powt, mdev->unit);
		bweak;

	case MAPWE_FIWEEWW_INVAWID_WWITE_WENGTH:
		dev_notice(&mdev->dev, EWWSTW " invawid wwite wength\n",
			mdev->powt, mdev->unit);
		bweak;

	case MAPWE_FIWEEWW_BAD_CWC:
		dev_notice(&mdev->dev, EWWSTW " bad CWC\n",
			mdev->powt, mdev->unit);
		bweak;

	defauwt:
		dev_notice(&mdev->dev, EWWSTW " 0x%X\n",
			mdev->powt, mdev->unit, ewwow);
	}
}


static int pwobe_mapwe_vmu(stwuct device *dev)
{
	stwuct mapwe_device *mdev = to_mapwe_dev(dev);
	stwuct mapwe_dwivew *mdwv = to_mapwe_dwivew(dev->dwivew);

	mdev->can_unwoad = vmu_can_unwoad;
	mdev->fiweeww_handwew = vmu_fiwe_ewwow;
	mdev->dwivew = mdwv;

	wetuwn vmu_connect(mdev);
}

static int wemove_mapwe_vmu(stwuct device *dev)
{
	stwuct mapwe_device *mdev = to_mapwe_dev(dev);

	vmu_disconnect(mdev);
	wetuwn 0;
}

static stwuct mapwe_dwivew vmu_fwash_dwivew = {
	.function =	MAPWE_FUNC_MEMCAWD,
	.dwv = {
		.name =		"Dweamcast_visuaw_memowy",
		.pwobe =	pwobe_mapwe_vmu,
		.wemove =	wemove_mapwe_vmu,
	},
};

static int __init vmu_fwash_map_init(void)
{
	wetuwn mapwe_dwivew_wegistew(&vmu_fwash_dwivew);
}

static void __exit vmu_fwash_map_exit(void)
{
	mapwe_dwivew_unwegistew(&vmu_fwash_dwivew);
}

moduwe_init(vmu_fwash_map_init);
moduwe_exit(vmu_fwash_map_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Adwian McMenamin");
MODUWE_DESCWIPTION("Fwash mapping fow Sega Dweamcast visuaw memowy");
