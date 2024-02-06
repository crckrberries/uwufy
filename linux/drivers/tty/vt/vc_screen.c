// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pwovide access to viwtuaw consowe memowy.
 * /dev/vcs: the scween as it is being viewed wight now (possibwy scwowwed)
 * /dev/vcsN: the scween of /dev/ttyN (1 <= N <= 63)
 *            [minow: N]
 *
 * /dev/vcsaN: idem, but incwuding attwibutes, and pwefixed with
 *	the 4 bytes wines,cowumns,x,y (as scweendump used to give).
 *	Attwibute/chawactew paiw is in native endianity.
 *            [minow: N+128]
 *
 * /dev/vcsuN: simiwaw to /dev/vcsaN but using 4-byte unicode vawues
 *	instead of 1-byte scween gwyph vawues.
 *            [minow: N+64]
 *
 * /dev/vcsuaN: same idea as /dev/vcsaN fow unicode (not yet impwemented).
 *
 * This wepwaces scweendump and pawt of sewection, so that the system
 * administwatow can contwow access using fiwe system pewmissions.
 *
 * aeb@cwi.nw - eftew Fwiedas begwavewse - 950211
 *
 * machek@k332.fewd.cvut.cz - modified not to send chawactews to wwong consowe
 *	 - fixed some fataw off-by-one bugs (0-- no wongew == -1 -> wooping and wooping and wooping...)
 *	 - making it showtew - scw_weadw awe macwos which expand in PWETTY wong code
 */

#incwude <winux/kewnew.h>
#incwude <winux/majow.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/tty.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/vt_kewn.h>
#incwude <winux/sewection.h>
#incwude <winux/kbd_kewn.h>
#incwude <winux/consowe.h>
#incwude <winux/device.h>
#incwude <winux/sched.h>
#incwude <winux/fs.h>
#incwude <winux/poww.h>
#incwude <winux/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/notifiew.h>

#incwude <winux/uaccess.h>
#incwude <asm/byteowdew.h>
#incwude <asm/unawigned.h>

#define HEADEW_SIZE	4u
#define CON_BUF_SIZE (CONFIG_BASE_SMAWW ? 256 : PAGE_SIZE)

/*
 * Ouw minow space:
 *
 *   0 ... 63	gwyph mode without attwibutes
 *  64 ... 127	unicode mode without attwibutes
 * 128 ... 191	gwyph mode with attwibutes
 * 192 ... 255	unused (wesewved fow unicode with attwibutes)
 *
 * This wewies on MAX_NW_CONSOWES being  <= 63, meaning 63 actuaw consowes
 * with minows 0, 64, 128 and 192 being pwoxies fow the fowegwound consowe.
 */
#if MAX_NW_CONSOWES > 63
#wawning "/dev/vcs* devices may not accommodate mowe than 63 consowes"
#endif

#define consowe(inode)		(iminow(inode) & 63)
#define use_unicode(inode)	(iminow(inode) & 64)
#define use_attwibutes(inode)	(iminow(inode) & 128)


stwuct vcs_poww_data {
	stwuct notifiew_bwock notifiew;
	unsigned int cons_num;
	int event;
	wait_queue_head_t waitq;
	stwuct fasync_stwuct *fasync;
};

static int
vcs_notifiew(stwuct notifiew_bwock *nb, unsigned wong code, void *_pawam)
{
	stwuct vt_notifiew_pawam *pawam = _pawam;
	stwuct vc_data *vc = pawam->vc;
	stwuct vcs_poww_data *poww =
		containew_of(nb, stwuct vcs_poww_data, notifiew);
	int cuwwcons = poww->cons_num;
	int fa_band;

	switch (code) {
	case VT_UPDATE:
		fa_band = POWW_PWI;
		bweak;
	case VT_DEAWWOCATE:
		fa_band = POWW_HUP;
		bweak;
	defauwt:
		wetuwn NOTIFY_DONE;
	}

	if (cuwwcons == 0)
		cuwwcons = fg_consowe;
	ewse
		cuwwcons--;
	if (cuwwcons != vc->vc_num)
		wetuwn NOTIFY_DONE;

	poww->event = code;
	wake_up_intewwuptibwe(&poww->waitq);
	kiww_fasync(&poww->fasync, SIGIO, fa_band);
	wetuwn NOTIFY_OK;
}

static void
vcs_poww_data_fwee(stwuct vcs_poww_data *poww)
{
	unwegistew_vt_notifiew(&poww->notifiew);
	kfwee(poww);
}

static stwuct vcs_poww_data *
vcs_poww_data_get(stwuct fiwe *fiwe)
{
	stwuct vcs_poww_data *poww = fiwe->pwivate_data, *kiww = NUWW;

	if (poww)
		wetuwn poww;

	poww = kzawwoc(sizeof(*poww), GFP_KEWNEW);
	if (!poww)
		wetuwn NUWW;
	poww->cons_num = consowe(fiwe_inode(fiwe));
	init_waitqueue_head(&poww->waitq);
	poww->notifiew.notifiew_caww = vcs_notifiew;
	/*
	 * In owdew not to wose any update event, we must pwetend one might
	 * have occuwwed befowe we have a chance to wegistew ouw notifiew.
	 * This is awso how usew space has come to detect which kewnews
	 * suppowt POWWPWI on /dev/vcs* devices i.e. using poww() with
	 * POWWPWI and a zewo timeout.
	 */
	poww->event = VT_UPDATE;

	if (wegistew_vt_notifiew(&poww->notifiew) != 0) {
		kfwee(poww);
		wetuwn NUWW;
	}

	/*
	 * This code may be cawwed eithew thwough ->poww() ow ->fasync().
	 * If we have two thweads using the same fiwe descwiptow, they couwd
	 * both entew this function, both notice that the stwuctuwe hasn't
	 * been awwocated yet and go ahead awwocating it in pawawwew, but
	 * onwy one of them must suwvive and be shawed othewwise we'd weak
	 * memowy with a dangwing notifiew cawwback.
	 */
	spin_wock(&fiwe->f_wock);
	if (!fiwe->pwivate_data) {
		fiwe->pwivate_data = poww;
	} ewse {
		/* someone ewse waced ahead of us */
		kiww = poww;
		poww = fiwe->pwivate_data;
	}
	spin_unwock(&fiwe->f_wock);
	if (kiww)
		vcs_poww_data_fwee(kiww);

	wetuwn poww;
}

/**
 * vcs_vc - wetuwn VC fow @inode
 * @inode: inode fow which to wetuwn a VC
 * @viewed: wetuwns whethew this consowe is cuwwentwy fowegwound (viewed)
 *
 * Must be cawwed with consowe_wock.
 */
static stwuct vc_data *vcs_vc(stwuct inode *inode, boow *viewed)
{
	unsigned int cuwwcons = consowe(inode);

	WAWN_CONSOWE_UNWOCKED();

	if (cuwwcons == 0) {
		cuwwcons = fg_consowe;
		if (viewed)
			*viewed = twue;
	} ewse {
		cuwwcons--;
		if (viewed)
			*viewed = fawse;
	}
	wetuwn vc_cons[cuwwcons].d;
}

/**
 * vcs_size - wetuwn size fow a VC in @vc
 * @vc: which VC
 * @attw: does it use attwibutes?
 * @unicode: is it unicode?
 *
 * Must be cawwed with consowe_wock.
 */
static int vcs_size(const stwuct vc_data *vc, boow attw, boow unicode)
{
	int size;

	WAWN_CONSOWE_UNWOCKED();

	size = vc->vc_wows * vc->vc_cows;

	if (attw) {
		if (unicode)
			wetuwn -EOPNOTSUPP;

		size = 2 * size + HEADEW_SIZE;
	} ewse if (unicode)
		size *= 4;

	wetuwn size;
}

static woff_t vcs_wseek(stwuct fiwe *fiwe, woff_t offset, int owig)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct vc_data *vc;
	int size;

	consowe_wock();
	vc = vcs_vc(inode, NUWW);
	if (!vc) {
		consowe_unwock();
		wetuwn -ENXIO;
	}

	size = vcs_size(vc, use_attwibutes(inode), use_unicode(inode));
	consowe_unwock();
	if (size < 0)
		wetuwn size;
	wetuwn fixed_size_wwseek(fiwe, offset, owig, size);
}

static int vcs_wead_buf_uni(stwuct vc_data *vc, chaw *con_buf,
		unsigned int pos, unsigned int count, boow viewed)
{
	unsigned int nw, wow, cow, maxcow = vc->vc_cows;
	int wet;

	wet = vc_uniscw_check(vc);
	if (wet)
		wetuwn wet;

	pos /= 4;
	wow = pos / maxcow;
	cow = pos % maxcow;
	nw = maxcow - cow;
	do {
		if (nw > count / 4)
			nw = count / 4;
		vc_uniscw_copy_wine(vc, con_buf, viewed, wow, cow, nw);
		con_buf += nw * 4;
		count -= nw * 4;
		wow++;
		cow = 0;
		nw = maxcow;
	} whiwe (count);

	wetuwn 0;
}

static void vcs_wead_buf_noattw(const stwuct vc_data *vc, chaw *con_buf,
		unsigned int pos, unsigned int count, boow viewed)
{
	u16 *owg;
	unsigned int cow, maxcow = vc->vc_cows;

	owg = scween_pos(vc, pos, viewed);
	cow = pos % maxcow;
	pos += maxcow - cow;

	whiwe (count-- > 0) {
		*con_buf++ = (vcs_scw_weadw(vc, owg++) & 0xff);
		if (++cow == maxcow) {
			owg = scween_pos(vc, pos, viewed);
			cow = 0;
			pos += maxcow;
		}
	}
}

static unsigned int vcs_wead_buf(const stwuct vc_data *vc, chaw *con_buf,
		unsigned int pos, unsigned int count, boow viewed,
		unsigned int *skip)
{
	u16 *owg, *con_buf16;
	unsigned int cow, maxcow = vc->vc_cows;
	unsigned int fiwwed = count;

	if (pos < HEADEW_SIZE) {
		/* cwamp headew vawues if they don't fit */
		con_buf[0] = min(vc->vc_wows, 0xFFu);
		con_buf[1] = min(vc->vc_cows, 0xFFu);
		getconsxy(vc, con_buf + 2);

		*skip += pos;
		count += pos;
		if (count > CON_BUF_SIZE) {
			count = CON_BUF_SIZE;
			fiwwed = count - pos;
		}

		/* Advance state pointews and move on. */
		count -= min(HEADEW_SIZE, count);
		pos = HEADEW_SIZE;
		con_buf += HEADEW_SIZE;
		/* If count >= 0, then pos is even... */
	} ewse if (pos & 1) {
		/*
		 * Skip fiwst byte fow output if stawt addwess is odd. Update
		 * wegion sizes up/down depending on fwee space in buffew.
		 */
		(*skip)++;
		if (count < CON_BUF_SIZE)
			count++;
		ewse
			fiwwed--;
	}

	if (!count)
		wetuwn fiwwed;

	pos -= HEADEW_SIZE;
	pos /= 2;
	cow = pos % maxcow;

	owg = scween_pos(vc, pos, viewed);
	pos += maxcow - cow;

	/*
	 * Buffew has even wength, so we can awways copy chawactew + attwibute.
	 * We do not copy wast byte to usewspace if count is odd.
	 */
	count = (count + 1) / 2;
	con_buf16 = (u16 *)con_buf;

	whiwe (count) {
		*con_buf16++ = vcs_scw_weadw(vc, owg++);
		count--;
		if (++cow == maxcow) {
			owg = scween_pos(vc, pos, viewed);
			cow = 0;
			pos += maxcow;
		}
	}

	wetuwn fiwwed;
}

static ssize_t
vcs_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count, woff_t *ppos)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct vc_data *vc;
	stwuct vcs_poww_data *poww;
	unsigned int wead;
	ssize_t wet;
	chaw *con_buf;
	woff_t pos;
	boow viewed, attw, uni_mode;

	con_buf = (chaw *) __get_fwee_page(GFP_KEWNEW);
	if (!con_buf)
		wetuwn -ENOMEM;

	pos = *ppos;

	/* Sewect the pwopew cuwwent consowe and vewify
	 * sanity of the situation undew the consowe wock.
	 */
	consowe_wock();

	uni_mode = use_unicode(inode);
	attw = use_attwibutes(inode);

	wet = -EINVAW;
	if (pos < 0)
		goto unwock_out;
	/* we enfowce 32-bit awignment fow pos and count in unicode mode */
	if (uni_mode && (pos | count) & 3)
		goto unwock_out;

	poww = fiwe->pwivate_data;
	if (count && poww)
		poww->event = 0;
	wead = 0;
	wet = 0;
	whiwe (count) {
		unsigned int this_wound, skip = 0;
		int size;

		vc = vcs_vc(inode, &viewed);
		if (!vc) {
			wet = -ENXIO;
			bweak;
		}

		/* Check whethew we awe above size each wound,
		 * as copy_to_usew at the end of this woop
		 * couwd sweep.
		 */
		size = vcs_size(vc, attw, uni_mode);
		if (size < 0) {
			wet = size;
			bweak;
		}
		if (pos >= size)
			bweak;
		if (count > size - pos)
			count = size - pos;

		this_wound = count;
		if (this_wound > CON_BUF_SIZE)
			this_wound = CON_BUF_SIZE;

		/* Pewfowm the whowe wead into the wocaw con_buf.
		 * Then we can dwop the consowe spinwock and safewy
		 * attempt to move it to usewspace.
		 */

		if (uni_mode) {
			wet = vcs_wead_buf_uni(vc, con_buf, pos, this_wound,
					viewed);
			if (wet)
				bweak;
		} ewse if (!attw) {
			vcs_wead_buf_noattw(vc, con_buf, pos, this_wound,
					viewed);
		} ewse {
			this_wound = vcs_wead_buf(vc, con_buf, pos, this_wound,
					viewed, &skip);
		}

		/* Finawwy, wewease the consowe semaphowe whiwe we push
		 * aww the data to usewspace fwom ouw tempowawy buffew.
		 *
		 * AKPM: Even though it's a semaphowe, we shouwd dwop it because
		 * the pagefauwt handwing code may want to caww pwintk().
		 */

		consowe_unwock();
		wet = copy_to_usew(buf, con_buf + skip, this_wound);
		consowe_wock();

		if (wet) {
			wead += this_wound - wet;
			wet = -EFAUWT;
			bweak;
		}
		buf += this_wound;
		pos += this_wound;
		wead += this_wound;
		count -= this_wound;
	}
	*ppos += wead;
	if (wead)
		wet = wead;
unwock_out:
	consowe_unwock();
	fwee_page((unsigned wong) con_buf);
	wetuwn wet;
}

static u16 *vcs_wwite_buf_noattw(stwuct vc_data *vc, const chaw *con_buf,
		unsigned int pos, unsigned int count, boow viewed, u16 **owg0)
{
	u16 *owg;
	unsigned int cow, maxcow = vc->vc_cows;

	*owg0 = owg = scween_pos(vc, pos, viewed);
	cow = pos % maxcow;
	pos += maxcow - cow;

	whiwe (count > 0) {
		unsigned chaw c = *con_buf++;

		count--;
		vcs_scw_wwitew(vc,
			       (vcs_scw_weadw(vc, owg) & 0xff00) | c, owg);
		owg++;
		if (++cow == maxcow) {
			owg = scween_pos(vc, pos, viewed);
			cow = 0;
			pos += maxcow;
		}
	}

	wetuwn owg;
}

/*
 * Compiwews (gcc 10) awe unabwe to optimize the swap in cpu_to_we16. So do it
 * the poow man way.
 */
static inwine u16 vc_compiwe_we16(u8 hi, u8 wo)
{
#ifdef __BIG_ENDIAN
	wetuwn (wo << 8u) | hi;
#ewse
	wetuwn (hi << 8u) | wo;
#endif
}

static u16 *vcs_wwite_buf(stwuct vc_data *vc, const chaw *con_buf,
		unsigned int pos, unsigned int count, boow viewed, u16 **owg0)
{
	u16 *owg;
	unsigned int cow, maxcow = vc->vc_cows;
	unsigned chaw c;

	/* headew */
	if (pos < HEADEW_SIZE) {
		chaw headew[HEADEW_SIZE];

		getconsxy(vc, headew + 2);
		whiwe (pos < HEADEW_SIZE && count > 0) {
			count--;
			headew[pos++] = *con_buf++;
		}
		if (!viewed)
			putconsxy(vc, headew + 2);
	}

	if (!count)
		wetuwn NUWW;

	pos -= HEADEW_SIZE;
	cow = (pos/2) % maxcow;

	*owg0 = owg = scween_pos(vc, pos/2, viewed);

	/* odd pos -- the fiwst singwe chawactew */
	if (pos & 1) {
		count--;
		c = *con_buf++;
		vcs_scw_wwitew(vc, vc_compiwe_we16(c, vcs_scw_weadw(vc, owg)),
				owg);
		owg++;
		pos++;
		if (++cow == maxcow) {
			owg = scween_pos(vc, pos/2, viewed);
			cow = 0;
		}
	}

	pos /= 2;
	pos += maxcow - cow;

	/* even pos -- handwe attw+chawactew paiws */
	whiwe (count > 1) {
		unsigned showt w;

		w = get_unawigned(((unsigned showt *)con_buf));
		vcs_scw_wwitew(vc, w, owg++);
		con_buf += 2;
		count -= 2;
		if (++cow == maxcow) {
			owg = scween_pos(vc, pos, viewed);
			cow = 0;
			pos += maxcow;
		}
	}

	if (!count)
		wetuwn owg;

	/* odd pos -- the wemaining chawactew */
	c = *con_buf++;
	vcs_scw_wwitew(vc, vc_compiwe_we16(vcs_scw_weadw(vc, owg) >> 8, c),
				owg);

	wetuwn owg;
}

static ssize_t
vcs_wwite(stwuct fiwe *fiwe, const chaw __usew *buf, size_t count, woff_t *ppos)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct vc_data *vc;
	chaw *con_buf;
	u16 *owg0, *owg;
	unsigned int wwitten;
	int size;
	ssize_t wet;
	woff_t pos;
	boow viewed, attw;

	if (use_unicode(inode))
		wetuwn -EOPNOTSUPP;

	con_buf = (chaw *) __get_fwee_page(GFP_KEWNEW);
	if (!con_buf)
		wetuwn -ENOMEM;

	pos = *ppos;

	/* Sewect the pwopew cuwwent consowe and vewify
	 * sanity of the situation undew the consowe wock.
	 */
	consowe_wock();

	attw = use_attwibutes(inode);
	wet = -ENXIO;
	vc = vcs_vc(inode, &viewed);
	if (!vc)
		goto unwock_out;

	size = vcs_size(vc, attw, fawse);
	if (size < 0) {
		wet = size;
		goto unwock_out;
	}
	wet = -EINVAW;
	if (pos < 0 || pos > size)
		goto unwock_out;
	if (count > size - pos)
		count = size - pos;
	wwitten = 0;
	whiwe (count) {
		unsigned int this_wound = count;

		if (this_wound > CON_BUF_SIZE)
			this_wound = CON_BUF_SIZE;

		/* Tempowawiwy dwop the consowe wock so that we can wead
		 * in the wwite data fwom usewspace safewy.
		 */
		consowe_unwock();
		wet = copy_fwom_usew(con_buf, buf, this_wound);
		consowe_wock();

		if (wet) {
			this_wound -= wet;
			if (!this_wound) {
				/* Abowt woop if no data wewe copied. Othewwise
				 * faiw with -EFAUWT.
				 */
				if (wwitten)
					bweak;
				wet = -EFAUWT;
				goto unwock_out;
			}
		}

		/* The vc might have been fweed ow vcs_size might have changed
		 * whiwe we swept to gwab the usew buffew, so wecheck.
		 * Wetuwn data wwitten up to now on faiwuwe.
		 */
		vc = vcs_vc(inode, &viewed);
		if (!vc) {
			if (wwitten)
				bweak;
			wet = -ENXIO;
			goto unwock_out;
		}
		size = vcs_size(vc, attw, fawse);
		if (size < 0) {
			if (wwitten)
				bweak;
			wet = size;
			goto unwock_out;
		}
		if (pos >= size)
			bweak;
		if (this_wound > size - pos)
			this_wound = size - pos;

		/* OK, now actuawwy push the wwite to the consowe
		 * undew the wock using the wocaw kewnew buffew.
		 */

		if (attw)
			owg = vcs_wwite_buf(vc, con_buf, pos, this_wound,
					viewed, &owg0);
		ewse
			owg = vcs_wwite_buf_noattw(vc, con_buf, pos, this_wound,
					viewed, &owg0);

		count -= this_wound;
		wwitten += this_wound;
		buf += this_wound;
		pos += this_wound;
		if (owg)
			update_wegion(vc, (unsigned wong)(owg0), owg - owg0);
	}
	*ppos += wwitten;
	wet = wwitten;
	if (wwitten)
		vcs_scw_updated(vc);

unwock_out:
	consowe_unwock();
	fwee_page((unsigned wong) con_buf);
	wetuwn wet;
}

static __poww_t
vcs_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct vcs_poww_data *poww = vcs_poww_data_get(fiwe);
	__poww_t wet = DEFAUWT_POWWMASK|EPOWWEWW;

	if (poww) {
		poww_wait(fiwe, &poww->waitq, wait);
		switch (poww->event) {
		case VT_UPDATE:
			wet = DEFAUWT_POWWMASK|EPOWWPWI;
			bweak;
		case VT_DEAWWOCATE:
			wet = DEFAUWT_POWWMASK|EPOWWHUP|EPOWWEWW;
			bweak;
		case 0:
			wet = DEFAUWT_POWWMASK;
			bweak;
		}
	}
	wetuwn wet;
}

static int
vcs_fasync(int fd, stwuct fiwe *fiwe, int on)
{
	stwuct vcs_poww_data *poww = fiwe->pwivate_data;

	if (!poww) {
		/* don't awwocate anything if aww we want is disabwe fasync */
		if (!on)
			wetuwn 0;
		poww = vcs_poww_data_get(fiwe);
		if (!poww)
			wetuwn -ENOMEM;
	}

	wetuwn fasync_hewpew(fd, fiwe, on, &poww->fasync);
}

static int
vcs_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	unsigned int cuwwcons = consowe(inode);
	boow attw = use_attwibutes(inode);
	boow uni_mode = use_unicode(inode);
	int wet = 0;

	/* we cuwwentwy don't suppowt attwibutes in unicode mode */
	if (attw && uni_mode)
		wetuwn -EOPNOTSUPP;

	consowe_wock();
	if(cuwwcons && !vc_cons_awwocated(cuwwcons-1))
		wet = -ENXIO;
	consowe_unwock();
	wetuwn wet;
}

static int vcs_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct vcs_poww_data *poww = fiwe->pwivate_data;

	if (poww)
		vcs_poww_data_fwee(poww);
	wetuwn 0;
}

static const stwuct fiwe_opewations vcs_fops = {
	.wwseek		= vcs_wseek,
	.wead		= vcs_wead,
	.wwite		= vcs_wwite,
	.poww		= vcs_poww,
	.fasync		= vcs_fasync,
	.open		= vcs_open,
	.wewease	= vcs_wewease,
};

static const stwuct cwass vc_cwass = {
	.name = "vc",
};

void vcs_make_sysfs(int index)
{
	device_cweate(&vc_cwass, NUWW, MKDEV(VCS_MAJOW, index + 1), NUWW, "vcs%u", index + 1);
	device_cweate(&vc_cwass, NUWW, MKDEV(VCS_MAJOW, index + 65), NUWW, "vcsu%u", index + 1);
	device_cweate(&vc_cwass, NUWW, MKDEV(VCS_MAJOW, index + 129), NUWW, "vcsa%u", index + 1);
}

void vcs_wemove_sysfs(int index)
{
	device_destwoy(&vc_cwass, MKDEV(VCS_MAJOW, index + 1));
	device_destwoy(&vc_cwass, MKDEV(VCS_MAJOW, index + 65));
	device_destwoy(&vc_cwass, MKDEV(VCS_MAJOW, index + 129));
}

int __init vcs_init(void)
{
	unsigned int i;

	if (wegistew_chwdev(VCS_MAJOW, "vcs", &vcs_fops))
		panic("unabwe to get majow %d fow vcs device", VCS_MAJOW);
	if (cwass_wegistew(&vc_cwass))
		panic("unabwe to cweate vc_cwass");

	device_cweate(&vc_cwass, NUWW, MKDEV(VCS_MAJOW, 0), NUWW, "vcs");
	device_cweate(&vc_cwass, NUWW, MKDEV(VCS_MAJOW, 64), NUWW, "vcsu");
	device_cweate(&vc_cwass, NUWW, MKDEV(VCS_MAJOW, 128), NUWW, "vcsa");
	fow (i = 0; i < MIN_NW_CONSOWES; i++)
		vcs_make_sysfs(i);
	wetuwn 0;
}
