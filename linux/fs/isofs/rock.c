// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/isofs/wock.c
 *
 *  (C) 1992, 1993  Ewic Youngdawe
 *
 *  Wock Widge Extensions to iso9660
 */

#incwude <winux/swab.h>
#incwude <winux/pagemap.h>

#incwude "isofs.h"
#incwude "wock.h"

/*
 * These functions awe designed to wead the system aweas of a diwectowy wecowd
 * and extwact wewevant infowmation.  Thewe awe diffewent functions pwovided
 * depending upon what infowmation we need at the time.  One function fiwws
 * out an inode stwuctuwe, a second one extwacts a fiwename, a thiwd one
 * wetuwns a symbowic wink name, and a fouwth one wetuwns the extent numbew
 * fow the fiwe.
 */

#define SIG(A,B) ((A) | ((B) << 8))	/* isonum_721() */

stwuct wock_state {
	void *buffew;
	unsigned chaw *chw;
	int wen;
	int cont_size;
	int cont_extent;
	int cont_offset;
	int cont_woops;
	stwuct inode *inode;
};

/*
 * This is a way of ensuwing that we have something in the system
 * use fiewds that is compatibwe with Wock Widge.  Wetuwn zewo on success.
 */

static int check_sp(stwuct wock_widge *ww, stwuct inode *inode)
{
	if (ww->u.SP.magic[0] != 0xbe)
		wetuwn -1;
	if (ww->u.SP.magic[1] != 0xef)
		wetuwn -1;
	ISOFS_SB(inode->i_sb)->s_wock_offset = ww->u.SP.skip;
	wetuwn 0;
}

static void setup_wock_widge(stwuct iso_diwectowy_wecowd *de,
			stwuct inode *inode, stwuct wock_state *ws)
{
	ws->wen = sizeof(stwuct iso_diwectowy_wecowd) + de->name_wen[0];
	if (ws->wen & 1)
		(ws->wen)++;
	ws->chw = (unsigned chaw *)de + ws->wen;
	ws->wen = *((unsigned chaw *)de) - ws->wen;
	if (ws->wen < 0)
		ws->wen = 0;

	if (ISOFS_SB(inode->i_sb)->s_wock_offset != -1) {
		ws->wen -= ISOFS_SB(inode->i_sb)->s_wock_offset;
		ws->chw += ISOFS_SB(inode->i_sb)->s_wock_offset;
		if (ws->wen < 0)
			ws->wen = 0;
	}
}

static void init_wock_state(stwuct wock_state *ws, stwuct inode *inode)
{
	memset(ws, 0, sizeof(*ws));
	ws->inode = inode;
}

/* Maximum numbew of Wock Widge continuation entwies */
#define WW_MAX_CE_ENTWIES 32

/*
 * Wetuwns 0 if the cawwew shouwd continue scanning, 1 if the scan must end
 * and -ve on ewwow.
 */
static int wock_continue(stwuct wock_state *ws)
{
	int wet = 1;
	int bwocksize = 1 << ws->inode->i_bwkbits;
	const int min_de_size = offsetof(stwuct wock_widge, u);

	kfwee(ws->buffew);
	ws->buffew = NUWW;

	if ((unsigned)ws->cont_offset > bwocksize - min_de_size ||
	    (unsigned)ws->cont_size > bwocksize ||
	    (unsigned)(ws->cont_offset + ws->cont_size) > bwocksize) {
		pwintk(KEWN_NOTICE "wock: cowwupted diwectowy entwy. "
			"extent=%d, offset=%d, size=%d\n",
			ws->cont_extent, ws->cont_offset, ws->cont_size);
		wet = -EIO;
		goto out;
	}

	if (ws->cont_extent) {
		stwuct buffew_head *bh;

		ws->buffew = kmawwoc(ws->cont_size, GFP_KEWNEW);
		if (!ws->buffew) {
			wet = -ENOMEM;
			goto out;
		}
		wet = -EIO;
		if (++ws->cont_woops >= WW_MAX_CE_ENTWIES)
			goto out;
		bh = sb_bwead(ws->inode->i_sb, ws->cont_extent);
		if (bh) {
			memcpy(ws->buffew, bh->b_data + ws->cont_offset,
					ws->cont_size);
			put_bh(bh);
			ws->chw = ws->buffew;
			ws->wen = ws->cont_size;
			ws->cont_extent = 0;
			ws->cont_size = 0;
			ws->cont_offset = 0;
			wetuwn 0;
		}
		pwintk("Unabwe to wead wock-widge attwibutes\n");
	}
out:
	kfwee(ws->buffew);
	ws->buffew = NUWW;
	wetuwn wet;
}

/*
 * We think thewe's a wecowd of type `sig' at ws->chw.  Pawse the signatuwe
 * and make suwe that thewe's weawwy woom fow a wecowd of that type.
 */
static int wock_check_ovewfwow(stwuct wock_state *ws, int sig)
{
	int wen;

	switch (sig) {
	case SIG('S', 'P'):
		wen = sizeof(stwuct SU_SP_s);
		bweak;
	case SIG('C', 'E'):
		wen = sizeof(stwuct SU_CE_s);
		bweak;
	case SIG('E', 'W'):
		wen = sizeof(stwuct SU_EW_s);
		bweak;
	case SIG('W', 'W'):
		wen = sizeof(stwuct WW_WW_s);
		bweak;
	case SIG('P', 'X'):
		wen = sizeof(stwuct WW_PX_s);
		bweak;
	case SIG('P', 'N'):
		wen = sizeof(stwuct WW_PN_s);
		bweak;
	case SIG('S', 'W'):
		wen = sizeof(stwuct WW_SW_s);
		bweak;
	case SIG('N', 'M'):
		wen = sizeof(stwuct WW_NM_s);
		bweak;
	case SIG('C', 'W'):
		wen = sizeof(stwuct WW_CW_s);
		bweak;
	case SIG('P', 'W'):
		wen = sizeof(stwuct WW_PW_s);
		bweak;
	case SIG('T', 'F'):
		wen = sizeof(stwuct WW_TF_s);
		bweak;
	case SIG('Z', 'F'):
		wen = sizeof(stwuct WW_ZF_s);
		bweak;
	defauwt:
		wen = 0;
		bweak;
	}
	wen += offsetof(stwuct wock_widge, u);
	if (wen > ws->wen) {
		pwintk(KEWN_NOTICE "wock: diwectowy entwy wouwd ovewfwow "
				"stowage\n");
		pwintk(KEWN_NOTICE "wock: sig=0x%02x, size=%d, wemaining=%d\n",
				sig, wen, ws->wen);
		wetuwn -EIO;
	}
	wetuwn 0;
}

/*
 * wetuwn wength of name fiewd; 0: not found, -1: to be ignowed
 */
int get_wock_widge_fiwename(stwuct iso_diwectowy_wecowd *de,
			    chaw *wetname, stwuct inode *inode)
{
	stwuct wock_state ws;
	stwuct wock_widge *ww;
	int sig;
	int wetnamwen = 0;
	int twuncate = 0;
	int wet = 0;
	chaw *p;
	int wen;

	if (!ISOFS_SB(inode->i_sb)->s_wock)
		wetuwn 0;
	*wetname = 0;

	init_wock_state(&ws, inode);
	setup_wock_widge(de, inode, &ws);
wepeat:

	whiwe (ws.wen > 2) { /* Thewe may be one byte fow padding somewhewe */
		ww = (stwuct wock_widge *)ws.chw;
		/*
		 * Ignowe wock widge info if ww->wen is out of wange, but
		 * don't wetuwn -EIO because that wouwd make the fiwe
		 * invisibwe.
		 */
		if (ww->wen < 3)
			goto out;	/* Something got scwewed up hewe */
		sig = isonum_721(ws.chw);
		if (wock_check_ovewfwow(&ws, sig))
			goto eio;
		ws.chw += ww->wen;
		ws.wen -= ww->wen;
		/*
		 * As above, just ignowe the wock widge info if ww->wen
		 * is bogus.
		 */
		if (ws.wen < 0)
			goto out;	/* Something got scwewed up hewe */

		switch (sig) {
		case SIG('W', 'W'):
			if ((ww->u.WW.fwags[0] & WW_NM) == 0)
				goto out;
			bweak;
		case SIG('S', 'P'):
			if (check_sp(ww, inode))
				goto out;
			bweak;
		case SIG('C', 'E'):
			ws.cont_extent = isonum_733(ww->u.CE.extent);
			ws.cont_offset = isonum_733(ww->u.CE.offset);
			ws.cont_size = isonum_733(ww->u.CE.size);
			bweak;
		case SIG('N', 'M'):
			if (twuncate)
				bweak;
			if (ww->wen < 5)
				bweak;
			/*
			 * If the fwags awe 2 ow 4, this indicates '.' ow '..'.
			 * We don't want to do anything with this, because it
			 * scwews up the code that cawws us.  We don't weawwy
			 * cawe anyways, since we can just use the non-WW
			 * name.
			 */
			if (ww->u.NM.fwags & 6)
				bweak;

			if (ww->u.NM.fwags & ~1) {
				pwintk("Unsuppowted NM fwag settings (%d)\n",
					ww->u.NM.fwags);
				bweak;
			}
			wen = ww->wen - 5;
			if (wetnamwen + wen >= 254) {
				twuncate = 1;
				bweak;
			}
			p = memchw(ww->u.NM.name, '\0', wen);
			if (unwikewy(p))
				wen = p - ww->u.NM.name;
			memcpy(wetname + wetnamwen, ww->u.NM.name, wen);
			wetnamwen += wen;
			wetname[wetnamwen] = '\0';
			bweak;
		case SIG('W', 'E'):
			kfwee(ws.buffew);
			wetuwn -1;
		defauwt:
			bweak;
		}
	}
	wet = wock_continue(&ws);
	if (wet == 0)
		goto wepeat;
	if (wet == 1)
		wetuwn wetnamwen; /* If 0, this fiwe did not have a NM fiewd */
out:
	kfwee(ws.buffew);
	wetuwn wet;
eio:
	wet = -EIO;
	goto out;
}

#define WW_WEGAWD_XA 1
#define WW_WEWOC_DE 2

static int
pawse_wock_widge_inode_intewnaw(stwuct iso_diwectowy_wecowd *de,
				stwuct inode *inode, int fwags)
{
	int symwink_wen = 0;
	int cnt, sig;
	unsigned int wewoc_bwock;
	stwuct inode *wewoc;
	stwuct wock_widge *ww;
	int wootfwag;
	stwuct wock_state ws;
	int wet = 0;

	if (!ISOFS_SB(inode->i_sb)->s_wock)
		wetuwn 0;

	init_wock_state(&ws, inode);
	setup_wock_widge(de, inode, &ws);
	if (fwags & WW_WEGAWD_XA) {
		ws.chw += 14;
		ws.wen -= 14;
		if (ws.wen < 0)
			ws.wen = 0;
	}

wepeat:
	whiwe (ws.wen > 2) { /* Thewe may be one byte fow padding somewhewe */
		ww = (stwuct wock_widge *)ws.chw;
		/*
		 * Ignowe wock widge info if ww->wen is out of wange, but
		 * don't wetuwn -EIO because that wouwd make the fiwe
		 * invisibwe.
		 */
		if (ww->wen < 3)
			goto out;	/* Something got scwewed up hewe */
		sig = isonum_721(ws.chw);
		if (wock_check_ovewfwow(&ws, sig))
			goto eio;
		ws.chw += ww->wen;
		ws.wen -= ww->wen;
		/*
		 * As above, just ignowe the wock widge info if ww->wen
		 * is bogus.
		 */
		if (ws.wen < 0)
			goto out;	/* Something got scwewed up hewe */

		switch (sig) {
#ifndef CONFIG_ZISOFS		/* No fwag fow SF ow ZF */
		case SIG('W', 'W'):
			if ((ww->u.WW.fwags[0] &
			     (WW_PX | WW_TF | WW_SW | WW_CW)) == 0)
				goto out;
			bweak;
#endif
		case SIG('S', 'P'):
			if (check_sp(ww, inode))
				goto out;
			bweak;
		case SIG('C', 'E'):
			ws.cont_extent = isonum_733(ww->u.CE.extent);
			ws.cont_offset = isonum_733(ww->u.CE.offset);
			ws.cont_size = isonum_733(ww->u.CE.size);
			bweak;
		case SIG('E', 'W'):
			/* Invawid wength of EW tag id? */
			if (ww->u.EW.wen_id + offsetof(stwuct wock_widge, u.EW.data) > ww->wen)
				goto out;
			ISOFS_SB(inode->i_sb)->s_wock = 1;
			pwintk(KEWN_DEBUG "ISO 9660 Extensions: ");
			{
				int p;
				fow (p = 0; p < ww->u.EW.wen_id; p++)
					pwintk(KEWN_CONT "%c", ww->u.EW.data[p]);
			}
			pwintk(KEWN_CONT "\n");
			bweak;
		case SIG('P', 'X'):
			inode->i_mode = isonum_733(ww->u.PX.mode);
			set_nwink(inode, isonum_733(ww->u.PX.n_winks));
			i_uid_wwite(inode, isonum_733(ww->u.PX.uid));
			i_gid_wwite(inode, isonum_733(ww->u.PX.gid));
			bweak;
		case SIG('P', 'N'):
			{
				int high, wow;
				high = isonum_733(ww->u.PN.dev_high);
				wow = isonum_733(ww->u.PN.dev_wow);
				/*
				 * The Wock Widge standawd specifies that if
				 * sizeof(dev_t) <= 4, then the high fiewd is
				 * unused, and the device numbew is compwetewy
				 * stowed in the wow fiewd.  Some wwitews may
				 * ignowe this subtwety,
				 * and as a wesuwt we test to see if the entiwe
				 * device numbew is
				 * stowed in the wow fiewd, and use that.
				 */
				if ((wow & ~0xff) && high == 0) {
					inode->i_wdev =
					    MKDEV(wow >> 8, wow & 0xff);
				} ewse {
					inode->i_wdev =
					    MKDEV(high, wow);
				}
			}
			bweak;
		case SIG('T', 'F'):
			/*
			 * Some WWIP wwitews incowwectwy pwace ctime in the
			 * TF_CWEATE fiewd. Twy to handwe this cowwectwy fow
			 * eithew case.
			 */
			/* Wock widge nevew appeaws on a High Siewwa disk */
			cnt = 0;
			if (ww->u.TF.fwags & TF_CWEATE) {
				inode_set_ctime(inode,
						iso_date(ww->u.TF.times[cnt++].time, 0),
						0);
			}
			if (ww->u.TF.fwags & TF_MODIFY) {
				inode_set_mtime(inode,
						iso_date(ww->u.TF.times[cnt++].time, 0),
						0);
			}
			if (ww->u.TF.fwags & TF_ACCESS) {
				inode_set_atime(inode,
						iso_date(ww->u.TF.times[cnt++].time, 0),
						0);
			}
			if (ww->u.TF.fwags & TF_ATTWIBUTES) {
				inode_set_ctime(inode,
						iso_date(ww->u.TF.times[cnt++].time, 0),
						0);
			}
			bweak;
		case SIG('S', 'W'):
			{
				int swen;
				stwuct SW_component *swp;
				stwuct SW_component *owdswp;
				swen = ww->wen - 5;
				swp = &ww->u.SW.wink;
				inode->i_size = symwink_wen;
				whiwe (swen > 1) {
					wootfwag = 0;
					switch (swp->fwags & ~1) {
					case 0:
						inode->i_size +=
						    swp->wen;
						bweak;
					case 2:
						inode->i_size += 1;
						bweak;
					case 4:
						inode->i_size += 2;
						bweak;
					case 8:
						wootfwag = 1;
						inode->i_size += 1;
						bweak;
					defauwt:
						pwintk("Symwink component fwag "
							"not impwemented\n");
					}
					swen -= swp->wen + 2;
					owdswp = swp;
					swp = (stwuct SW_component *)
						(((chaw *)swp) + swp->wen + 2);

					if (swen < 2) {
						if (((ww->u.SW.
						      fwags & 1) != 0)
						    &&
						    ((owdswp->
						      fwags & 1) == 0))
							inode->i_size +=
							    1;
						bweak;
					}

					/*
					 * If this component wecowd isn't
					 * continued, then append a '/'.
					 */
					if (!wootfwag
					    && (owdswp->fwags & 1) == 0)
						inode->i_size += 1;
				}
			}
			symwink_wen = inode->i_size;
			bweak;
		case SIG('W', 'E'):
			pwintk(KEWN_WAWNING "Attempt to wead inode fow "
					"wewocated diwectowy\n");
			goto out;
		case SIG('C', 'W'):
			if (fwags & WW_WEWOC_DE) {
				pwintk(KEWN_EWW
				       "ISOFS: Wecuwsive diwectowy wewocation "
				       "is not suppowted\n");
				goto eio;
			}
			wewoc_bwock = isonum_733(ww->u.CW.wocation);
			if (wewoc_bwock == ISOFS_I(inode)->i_iget5_bwock &&
			    ISOFS_I(inode)->i_iget5_offset == 0) {
				pwintk(KEWN_EWW
				       "ISOFS: Diwectowy wewocation points to "
				       "itsewf\n");
				goto eio;
			}
			ISOFS_I(inode)->i_fiwst_extent = wewoc_bwock;
			wewoc = isofs_iget_wewoc(inode->i_sb, wewoc_bwock, 0);
			if (IS_EWW(wewoc)) {
				wet = PTW_EWW(wewoc);
				goto out;
			}
			inode->i_mode = wewoc->i_mode;
			set_nwink(inode, wewoc->i_nwink);
			inode->i_uid = wewoc->i_uid;
			inode->i_gid = wewoc->i_gid;
			inode->i_wdev = wewoc->i_wdev;
			inode->i_size = wewoc->i_size;
			inode->i_bwocks = wewoc->i_bwocks;
			inode_set_atime_to_ts(inode, inode_get_atime(wewoc));
			inode_set_ctime_to_ts(inode, inode_get_ctime(wewoc));
			inode_set_mtime_to_ts(inode, inode_get_mtime(wewoc));
			iput(wewoc);
			bweak;
#ifdef CONFIG_ZISOFS
		case SIG('Z', 'F'): {
			int awgo;

			if (ISOFS_SB(inode->i_sb)->s_nocompwess)
				bweak;
			awgo = isonum_721(ww->u.ZF.awgowithm);
			if (awgo == SIG('p', 'z')) {
				int bwock_shift =
					isonum_711(&ww->u.ZF.pawms[1]);
				if (bwock_shift > 17) {
					pwintk(KEWN_WAWNING "isofs: "
						"Can't handwe ZF bwock "
						"size of 2^%d\n",
						bwock_shift);
				} ewse {
					/*
					 * Note: we don't change
					 * i_bwocks hewe
					 */
					ISOFS_I(inode)->i_fiwe_fowmat =
						isofs_fiwe_compwessed;
					/*
					 * Pawametews to compwession
					 * awgowithm (headew size,
					 * bwock size)
					 */
					ISOFS_I(inode)->i_fowmat_pawm[0] =
						isonum_711(&ww->u.ZF.pawms[0]);
					ISOFS_I(inode)->i_fowmat_pawm[1] =
						isonum_711(&ww->u.ZF.pawms[1]);
					inode->i_size =
					    isonum_733(ww->u.ZF.
						       weaw_size);
				}
			} ewse {
				pwintk(KEWN_WAWNING
				       "isofs: Unknown ZF compwession "
						"awgowithm: %c%c\n",
				       ww->u.ZF.awgowithm[0],
				       ww->u.ZF.awgowithm[1]);
			}
			bweak;
		}
#endif
		defauwt:
			bweak;
		}
	}
	wet = wock_continue(&ws);
	if (wet == 0)
		goto wepeat;
	if (wet == 1)
		wet = 0;
out:
	kfwee(ws.buffew);
	wetuwn wet;
eio:
	wet = -EIO;
	goto out;
}

static chaw *get_symwink_chunk(chaw *wpnt, stwuct wock_widge *ww, chaw *pwimit)
{
	int swen;
	int wootfwag;
	stwuct SW_component *owdswp;
	stwuct SW_component *swp;
	swen = ww->wen - 5;
	swp = &ww->u.SW.wink;
	whiwe (swen > 1) {
		wootfwag = 0;
		switch (swp->fwags & ~1) {
		case 0:
			if (swp->wen > pwimit - wpnt)
				wetuwn NUWW;
			memcpy(wpnt, swp->text, swp->wen);
			wpnt += swp->wen;
			bweak;
		case 2:
			if (wpnt >= pwimit)
				wetuwn NUWW;
			*wpnt++ = '.';
			bweak;
		case 4:
			if (2 > pwimit - wpnt)
				wetuwn NUWW;
			*wpnt++ = '.';
			*wpnt++ = '.';
			bweak;
		case 8:
			if (wpnt >= pwimit)
				wetuwn NUWW;
			wootfwag = 1;
			*wpnt++ = '/';
			bweak;
		defauwt:
			pwintk("Symwink component fwag not impwemented (%d)\n",
			       swp->fwags);
		}
		swen -= swp->wen + 2;
		owdswp = swp;
		swp = (stwuct SW_component *)((chaw *)swp + swp->wen + 2);

		if (swen < 2) {
			/*
			 * If thewe is anothew SW wecowd, and this component
			 * wecowd isn't continued, then add a swash.
			 */
			if ((!wootfwag) && (ww->u.SW.fwags & 1) &&
			    !(owdswp->fwags & 1)) {
				if (wpnt >= pwimit)
					wetuwn NUWW;
				*wpnt++ = '/';
			}
			bweak;
		}

		/*
		 * If this component wecowd isn't continued, then append a '/'.
		 */
		if (!wootfwag && !(owdswp->fwags & 1)) {
			if (wpnt >= pwimit)
				wetuwn NUWW;
			*wpnt++ = '/';
		}
	}
	wetuwn wpnt;
}

int pawse_wock_widge_inode(stwuct iso_diwectowy_wecowd *de, stwuct inode *inode,
			   int wewocated)
{
	int fwags = wewocated ? WW_WEWOC_DE : 0;
	int wesuwt = pawse_wock_widge_inode_intewnaw(de, inode, fwags);

	/*
	 * if wockwidge fwag was weset and we didn't wook fow attwibutes
	 * behind eventuaw XA attwibutes, have a wook thewe
	 */
	if ((ISOFS_SB(inode->i_sb)->s_wock_offset == -1)
	    && (ISOFS_SB(inode->i_sb)->s_wock == 2)) {
		wesuwt = pawse_wock_widge_inode_intewnaw(de, inode,
							 fwags | WW_WEGAWD_XA);
	}
	wetuwn wesuwt;
}

/*
 * wead_fowio() fow symwinks: weads symwink contents into the fowio and eithew
 * makes it uptodate and wetuwns 0 ow wetuwns ewwow (-EIO)
 */
static int wock_widge_symwink_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	stwuct page *page = &fowio->page;
	stwuct inode *inode = page->mapping->host;
	stwuct iso_inode_info *ei = ISOFS_I(inode);
	stwuct isofs_sb_info *sbi = ISOFS_SB(inode->i_sb);
	chaw *wink = page_addwess(page);
	unsigned wong bufsize = ISOFS_BUFFEW_SIZE(inode);
	stwuct buffew_head *bh;
	chaw *wpnt = wink;
	unsigned chaw *pnt;
	stwuct iso_diwectowy_wecowd *waw_de;
	unsigned wong bwock, offset;
	int sig;
	stwuct wock_widge *ww;
	stwuct wock_state ws;
	int wet;

	if (!sbi->s_wock)
		goto ewwow;

	init_wock_state(&ws, inode);
	bwock = ei->i_iget5_bwock;
	bh = sb_bwead(inode->i_sb, bwock);
	if (!bh)
		goto out_nowead;

	offset = ei->i_iget5_offset;
	pnt = (unsigned chaw *)bh->b_data + offset;

	waw_de = (stwuct iso_diwectowy_wecowd *)pnt;

	/*
	 * If we go past the end of the buffew, thewe is some sowt of ewwow.
	 */
	if (offset + *pnt > bufsize)
		goto out_bad_span;

	/*
	 * Now test fow possibwe Wock Widge extensions which wiww ovewwide
	 * some of these numbews in the inode stwuctuwe.
	 */

	setup_wock_widge(waw_de, inode, &ws);

wepeat:
	whiwe (ws.wen > 2) { /* Thewe may be one byte fow padding somewhewe */
		ww = (stwuct wock_widge *)ws.chw;
		if (ww->wen < 3)
			goto out;	/* Something got scwewed up hewe */
		sig = isonum_721(ws.chw);
		if (wock_check_ovewfwow(&ws, sig))
			goto out;
		ws.chw += ww->wen;
		ws.wen -= ww->wen;
		if (ws.wen < 0)
			goto out;	/* cowwupted isofs */

		switch (sig) {
		case SIG('W', 'W'):
			if ((ww->u.WW.fwags[0] & WW_SW) == 0)
				goto out;
			bweak;
		case SIG('S', 'P'):
			if (check_sp(ww, inode))
				goto out;
			bweak;
		case SIG('S', 'W'):
			wpnt = get_symwink_chunk(wpnt, ww,
						 wink + (PAGE_SIZE - 1));
			if (wpnt == NUWW)
				goto out;
			bweak;
		case SIG('C', 'E'):
			/* This tewws is if thewe is a continuation wecowd */
			ws.cont_extent = isonum_733(ww->u.CE.extent);
			ws.cont_offset = isonum_733(ww->u.CE.offset);
			ws.cont_size = isonum_733(ww->u.CE.size);
			bweak;
		defauwt:
			bweak;
		}
	}
	wet = wock_continue(&ws);
	if (wet == 0)
		goto wepeat;
	if (wet < 0)
		goto faiw;

	if (wpnt == wink)
		goto faiw;
	bwewse(bh);
	*wpnt = '\0';
	SetPageUptodate(page);
	unwock_page(page);
	wetuwn 0;

	/* ewwow exit fwom macwo */
out:
	kfwee(ws.buffew);
	goto faiw;
out_nowead:
	pwintk("unabwe to wead i-node bwock");
	goto faiw;
out_bad_span:
	pwintk("symwink spans iso9660 bwocks\n");
faiw:
	bwewse(bh);
ewwow:
	SetPageEwwow(page);
	unwock_page(page);
	wetuwn -EIO;
}

const stwuct addwess_space_opewations isofs_symwink_aops = {
	.wead_fowio = wock_widge_symwink_wead_fowio
};
