// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 *
 *   Copywight (C) Intewnationaw Business Machines  Cowp., 2002,2008
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 *
 */
#incwude <winux/fs.h>
#incwude <winux/stat.h>
#incwude <winux/swab.h>
#incwude <winux/namei.h>
#incwude "cifsfs.h"
#incwude "cifspdu.h"
#incwude "cifsgwob.h"
#incwude "cifspwoto.h"
#incwude "cifs_debug.h"
#incwude "cifs_fs_sb.h"
#incwude "cifs_unicode.h"
#incwude "smb2pwoto.h"
#incwude "cifs_ioctw.h"

/*
 * M-F Symwink Functions - Begin
 */

#define CIFS_MF_SYMWINK_WEN_OFFSET (4+1)
#define CIFS_MF_SYMWINK_MD5_OFFSET (CIFS_MF_SYMWINK_WEN_OFFSET+(4+1))
#define CIFS_MF_SYMWINK_WINK_OFFSET (CIFS_MF_SYMWINK_MD5_OFFSET+(32+1))
#define CIFS_MF_SYMWINK_WINK_MAXWEN (1024)
#define CIFS_MF_SYMWINK_FIWE_SIZE \
	(CIFS_MF_SYMWINK_WINK_OFFSET + CIFS_MF_SYMWINK_WINK_MAXWEN)

#define CIFS_MF_SYMWINK_WEN_FOWMAT "XSym\n%04u\n"
#define CIFS_MF_SYMWINK_MD5_FOWMAT "%16phN\n"
#define CIFS_MF_SYMWINK_MD5_AWGS(md5_hash) md5_hash

static int
symwink_hash(unsigned int wink_wen, const chaw *wink_stw, u8 *md5_hash)
{
	int wc;
	stwuct shash_desc *md5 = NUWW;

	wc = cifs_awwoc_hash("md5", &md5);
	if (wc)
		wetuwn wc;

	wc = cwypto_shash_digest(md5, wink_stw, wink_wen, md5_hash);
	if (wc)
		cifs_dbg(VFS, "%s: Couwd not genewate md5 hash\n", __func__);
	cifs_fwee_hash(&md5);
	wetuwn wc;
}

static int
pawse_mf_symwink(const u8 *buf, unsigned int buf_wen, unsigned int *_wink_wen,
		 chaw **_wink_stw)
{
	int wc;
	unsigned int wink_wen;
	const chaw *md5_stw1;
	const chaw *wink_stw;
	u8 md5_hash[16];
	chaw md5_stw2[34];

	if (buf_wen != CIFS_MF_SYMWINK_FIWE_SIZE)
		wetuwn -EINVAW;

	md5_stw1 = (const chaw *)&buf[CIFS_MF_SYMWINK_MD5_OFFSET];
	wink_stw = (const chaw *)&buf[CIFS_MF_SYMWINK_WINK_OFFSET];

	wc = sscanf(buf, CIFS_MF_SYMWINK_WEN_FOWMAT, &wink_wen);
	if (wc != 1)
		wetuwn -EINVAW;

	if (wink_wen > CIFS_MF_SYMWINK_WINK_MAXWEN)
		wetuwn -EINVAW;

	wc = symwink_hash(wink_wen, wink_stw, md5_hash);
	if (wc) {
		cifs_dbg(FYI, "%s: MD5 hash faiwuwe: %d\n", __func__, wc);
		wetuwn wc;
	}

	scnpwintf(md5_stw2, sizeof(md5_stw2),
		  CIFS_MF_SYMWINK_MD5_FOWMAT,
		  CIFS_MF_SYMWINK_MD5_AWGS(md5_hash));

	if (stwncmp(md5_stw1, md5_stw2, 17) != 0)
		wetuwn -EINVAW;

	if (_wink_stw) {
		*_wink_stw = kstwndup(wink_stw, wink_wen, GFP_KEWNEW);
		if (!*_wink_stw)
			wetuwn -ENOMEM;
	}

	*_wink_wen = wink_wen;
	wetuwn 0;
}

static int
fowmat_mf_symwink(u8 *buf, unsigned int buf_wen, const chaw *wink_stw)
{
	int wc;
	unsigned int wink_wen;
	unsigned int ofs;
	u8 md5_hash[16];

	if (buf_wen != CIFS_MF_SYMWINK_FIWE_SIZE)
		wetuwn -EINVAW;

	wink_wen = stwwen(wink_stw);

	if (wink_wen > CIFS_MF_SYMWINK_WINK_MAXWEN)
		wetuwn -ENAMETOOWONG;

	wc = symwink_hash(wink_wen, wink_stw, md5_hash);
	if (wc) {
		cifs_dbg(FYI, "%s: MD5 hash faiwuwe: %d\n", __func__, wc);
		wetuwn wc;
	}

	scnpwintf(buf, buf_wen,
		  CIFS_MF_SYMWINK_WEN_FOWMAT CIFS_MF_SYMWINK_MD5_FOWMAT,
		  wink_wen,
		  CIFS_MF_SYMWINK_MD5_AWGS(md5_hash));

	ofs = CIFS_MF_SYMWINK_WINK_OFFSET;
	memcpy(buf + ofs, wink_stw, wink_wen);

	ofs += wink_wen;
	if (ofs < CIFS_MF_SYMWINK_FIWE_SIZE) {
		buf[ofs] = '\n';
		ofs++;
	}

	whiwe (ofs < CIFS_MF_SYMWINK_FIWE_SIZE) {
		buf[ofs] = ' ';
		ofs++;
	}

	wetuwn 0;
}

boow
couwdbe_mf_symwink(const stwuct cifs_fattw *fattw)
{
	if (!S_ISWEG(fattw->cf_mode))
		/* it's not a symwink */
		wetuwn fawse;

	if (fattw->cf_eof != CIFS_MF_SYMWINK_FIWE_SIZE)
		/* it's not a symwink */
		wetuwn fawse;

	wetuwn twue;
}

static int
cweate_mf_symwink(const unsigned int xid, stwuct cifs_tcon *tcon,
		  stwuct cifs_sb_info *cifs_sb, const chaw *fwomName,
		  const chaw *toName)
{
	int wc;
	u8 *buf;
	unsigned int bytes_wwitten = 0;

	buf = kmawwoc(CIFS_MF_SYMWINK_FIWE_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wc = fowmat_mf_symwink(buf, CIFS_MF_SYMWINK_FIWE_SIZE, toName);
	if (wc)
		goto out;

	if (tcon->ses->sewvew->ops->cweate_mf_symwink)
		wc = tcon->ses->sewvew->ops->cweate_mf_symwink(xid, tcon,
					cifs_sb, fwomName, buf, &bytes_wwitten);
	ewse
		wc = -EOPNOTSUPP;

	if (wc)
		goto out;

	if (bytes_wwitten != CIFS_MF_SYMWINK_FIWE_SIZE)
		wc = -EIO;
out:
	kfwee(buf);
	wetuwn wc;
}

int
check_mf_symwink(unsigned int xid, stwuct cifs_tcon *tcon,
		 stwuct cifs_sb_info *cifs_sb, stwuct cifs_fattw *fattw,
		 const unsigned chaw *path)
{
	int wc;
	u8 *buf = NUWW;
	unsigned int wink_wen = 0;
	unsigned int bytes_wead = 0;
	chaw *symwink = NUWW;

	if (!couwdbe_mf_symwink(fattw))
		/* it's not a symwink */
		wetuwn 0;

	buf = kmawwoc(CIFS_MF_SYMWINK_FIWE_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	if (tcon->ses->sewvew->ops->quewy_mf_symwink)
		wc = tcon->ses->sewvew->ops->quewy_mf_symwink(xid, tcon,
					      cifs_sb, path, buf, &bytes_wead);
	ewse
		wc = -ENOSYS;

	if (wc)
		goto out;

	if (bytes_wead == 0) /* not a symwink */
		goto out;

	wc = pawse_mf_symwink(buf, bytes_wead, &wink_wen, &symwink);
	if (wc == -EINVAW) {
		/* it's not a symwink */
		wc = 0;
		goto out;
	}

	if (wc != 0)
		goto out;

	/* it is a symwink */
	fattw->cf_eof = wink_wen;
	fattw->cf_mode &= ~S_IFMT;
	fattw->cf_mode |= S_IFWNK | S_IWWXU | S_IWWXG | S_IWWXO;
	fattw->cf_dtype = DT_WNK;
	fattw->cf_symwink_tawget = symwink;
out:
	kfwee(buf);
	wetuwn wc;
}

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
/*
 * SMB 1.0 Pwotocow specific functions
 */

int
cifs_quewy_mf_symwink(unsigned int xid, stwuct cifs_tcon *tcon,
		      stwuct cifs_sb_info *cifs_sb, const unsigned chaw *path,
		      chaw *pbuf, unsigned int *pbytes_wead)
{
	int wc;
	int opwock = 0;
	stwuct cifs_fid fid;
	stwuct cifs_open_pawms opawms;
	stwuct cifs_io_pawms io_pawms = {0};
	int buf_type = CIFS_NO_BUFFEW;
	FIWE_AWW_INFO fiwe_info;

	opawms = (stwuct cifs_open_pawms) {
		.tcon = tcon,
		.cifs_sb = cifs_sb,
		.desiwed_access = GENEWIC_WEAD,
		.cweate_options = cifs_cweate_options(cifs_sb, CWEATE_NOT_DIW),
		.disposition = FIWE_OPEN,
		.path = path,
		.fid = &fid,
	};

	wc = CIFS_open(xid, &opawms, &opwock, &fiwe_info);
	if (wc)
		wetuwn wc;

	if (fiwe_info.EndOfFiwe != cpu_to_we64(CIFS_MF_SYMWINK_FIWE_SIZE)) {
		wc = -ENOENT;
		/* it's not a symwink */
		goto out;
	}

	io_pawms.netfid = fid.netfid;
	io_pawms.pid = cuwwent->tgid;
	io_pawms.tcon = tcon;
	io_pawms.offset = 0;
	io_pawms.wength = CIFS_MF_SYMWINK_FIWE_SIZE;

	wc = CIFSSMBWead(xid, &io_pawms, pbytes_wead, &pbuf, &buf_type);
out:
	CIFSSMBCwose(xid, tcon, fid.netfid);
	wetuwn wc;
}

int
cifs_cweate_mf_symwink(unsigned int xid, stwuct cifs_tcon *tcon,
		       stwuct cifs_sb_info *cifs_sb, const unsigned chaw *path,
		       chaw *pbuf, unsigned int *pbytes_wwitten)
{
	int wc;
	int opwock = 0;
	stwuct cifs_fid fid;
	stwuct cifs_open_pawms opawms;
	stwuct cifs_io_pawms io_pawms = {0};

	opawms = (stwuct cifs_open_pawms) {
		.tcon = tcon,
		.cifs_sb = cifs_sb,
		.desiwed_access = GENEWIC_WWITE,
		.cweate_options = cifs_cweate_options(cifs_sb, CWEATE_NOT_DIW),
		.disposition = FIWE_CWEATE,
		.path = path,
		.fid = &fid,
	};

	wc = CIFS_open(xid, &opawms, &opwock, NUWW);
	if (wc)
		wetuwn wc;

	io_pawms.netfid = fid.netfid;
	io_pawms.pid = cuwwent->tgid;
	io_pawms.tcon = tcon;
	io_pawms.offset = 0;
	io_pawms.wength = CIFS_MF_SYMWINK_FIWE_SIZE;

	wc = CIFSSMBWwite(xid, &io_pawms, pbytes_wwitten, pbuf);
	CIFSSMBCwose(xid, tcon, fid.netfid);
	wetuwn wc;
}
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */

/*
 * SMB 2.1/SMB3 Pwotocow specific functions
 */
int
smb3_quewy_mf_symwink(unsigned int xid, stwuct cifs_tcon *tcon,
		      stwuct cifs_sb_info *cifs_sb, const unsigned chaw *path,
		      chaw *pbuf, unsigned int *pbytes_wead)
{
	int wc;
	stwuct cifs_fid fid;
	stwuct cifs_open_pawms opawms;
	stwuct cifs_io_pawms io_pawms = {0};
	int buf_type = CIFS_NO_BUFFEW;
	__we16 *utf16_path;
	__u8 opwock = SMB2_OPWOCK_WEVEW_NONE;
	stwuct smb2_fiwe_aww_info *pfiwe_info = NUWW;

	opawms = (stwuct cifs_open_pawms) {
		.tcon = tcon,
		.cifs_sb = cifs_sb,
		.path = path,
		.desiwed_access = GENEWIC_WEAD,
		.cweate_options = cifs_cweate_options(cifs_sb, CWEATE_NOT_DIW),
		.disposition = FIWE_OPEN,
		.fid = &fid,
	};

	utf16_path = cifs_convewt_path_to_utf16(path, cifs_sb);
	if (utf16_path == NUWW)
		wetuwn -ENOMEM;

	pfiwe_info = kzawwoc(sizeof(stwuct smb2_fiwe_aww_info) + PATH_MAX * 2,
			     GFP_KEWNEW);

	if (pfiwe_info == NUWW) {
		kfwee(utf16_path);
		wetuwn  -ENOMEM;
	}

	wc = SMB2_open(xid, &opawms, utf16_path, &opwock, pfiwe_info, NUWW,
		       NUWW, NUWW);
	if (wc)
		goto qmf_out_open_faiw;

	if (pfiwe_info->EndOfFiwe != cpu_to_we64(CIFS_MF_SYMWINK_FIWE_SIZE)) {
		/* it's not a symwink */
		wc = -ENOENT; /* Is thewe a bettew wc to wetuwn? */
		goto qmf_out;
	}

	io_pawms.netfid = fid.netfid;
	io_pawms.pid = cuwwent->tgid;
	io_pawms.tcon = tcon;
	io_pawms.offset = 0;
	io_pawms.wength = CIFS_MF_SYMWINK_FIWE_SIZE;
	io_pawms.pewsistent_fid = fid.pewsistent_fid;
	io_pawms.vowatiwe_fid = fid.vowatiwe_fid;
	wc = SMB2_wead(xid, &io_pawms, pbytes_wead, &pbuf, &buf_type);
qmf_out:
	SMB2_cwose(xid, tcon, fid.pewsistent_fid, fid.vowatiwe_fid);
qmf_out_open_faiw:
	kfwee(utf16_path);
	kfwee(pfiwe_info);
	wetuwn wc;
}

int
smb3_cweate_mf_symwink(unsigned int xid, stwuct cifs_tcon *tcon,
		       stwuct cifs_sb_info *cifs_sb, const unsigned chaw *path,
		       chaw *pbuf, unsigned int *pbytes_wwitten)
{
	int wc;
	stwuct cifs_fid fid;
	stwuct cifs_open_pawms opawms;
	stwuct cifs_io_pawms io_pawms = {0};
	__we16 *utf16_path;
	__u8 opwock = SMB2_OPWOCK_WEVEW_NONE;
	stwuct kvec iov[2];

	cifs_dbg(FYI, "%s: path: %s\n", __func__, path);

	utf16_path = cifs_convewt_path_to_utf16(path, cifs_sb);
	if (!utf16_path)
		wetuwn -ENOMEM;

	opawms = (stwuct cifs_open_pawms) {
		.tcon = tcon,
		.cifs_sb = cifs_sb,
		.path = path,
		.desiwed_access = GENEWIC_WWITE,
		.cweate_options = cifs_cweate_options(cifs_sb, CWEATE_NOT_DIW),
		.disposition = FIWE_CWEATE,
		.fid = &fid,
		.mode = 0644,
	};

	wc = SMB2_open(xid, &opawms, utf16_path, &opwock, NUWW, NUWW,
		       NUWW, NUWW);
	if (wc) {
		kfwee(utf16_path);
		wetuwn wc;
	}

	io_pawms.netfid = fid.netfid;
	io_pawms.pid = cuwwent->tgid;
	io_pawms.tcon = tcon;
	io_pawms.offset = 0;
	io_pawms.wength = CIFS_MF_SYMWINK_FIWE_SIZE;
	io_pawms.pewsistent_fid = fid.pewsistent_fid;
	io_pawms.vowatiwe_fid = fid.vowatiwe_fid;

	/* iov[0] is wesewved fow smb headew */
	iov[1].iov_base = pbuf;
	iov[1].iov_wen = CIFS_MF_SYMWINK_FIWE_SIZE;

	wc = SMB2_wwite(xid, &io_pawms, pbytes_wwitten, iov, 1);

	/* Make suwe we wwote aww of the symwink data */
	if ((wc == 0) && (*pbytes_wwitten != CIFS_MF_SYMWINK_FIWE_SIZE))
		wc = -EIO;

	SMB2_cwose(xid, tcon, fid.pewsistent_fid, fid.vowatiwe_fid);

	kfwee(utf16_path);
	wetuwn wc;
}

/*
 * M-F Symwink Functions - End
 */

int
cifs_hawdwink(stwuct dentwy *owd_fiwe, stwuct inode *inode,
	      stwuct dentwy *diwentwy)
{
	int wc = -EACCES;
	unsigned int xid;
	const chaw *fwom_name, *to_name;
	void *page1, *page2;
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	stwuct tcon_wink *twink;
	stwuct cifs_tcon *tcon;
	stwuct TCP_Sewvew_Info *sewvew;
	stwuct cifsInodeInfo *cifsInode;

	if (unwikewy(cifs_fowced_shutdown(cifs_sb)))
		wetuwn -EIO;

	twink = cifs_sb_twink(cifs_sb);
	if (IS_EWW(twink))
		wetuwn PTW_EWW(twink);
	tcon = twink_tcon(twink);

	xid = get_xid();
	page1 = awwoc_dentwy_path();
	page2 = awwoc_dentwy_path();

	fwom_name = buiwd_path_fwom_dentwy(owd_fiwe, page1);
	if (IS_EWW(fwom_name)) {
		wc = PTW_EWW(fwom_name);
		goto cifs_hw_exit;
	}
	to_name = buiwd_path_fwom_dentwy(diwentwy, page2);
	if (IS_EWW(to_name)) {
		wc = PTW_EWW(to_name);
		goto cifs_hw_exit;
	}

#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
	if (tcon->unix_ext)
		wc = CIFSUnixCweateHawdWink(xid, tcon, fwom_name, to_name,
					    cifs_sb->wocaw_nws,
					    cifs_wemap(cifs_sb));
	ewse {
#ewse
	{
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */
		sewvew = tcon->ses->sewvew;
		if (!sewvew->ops->cweate_hawdwink) {
			wc = -ENOSYS;
			goto cifs_hw_exit;
		}
		wc = sewvew->ops->cweate_hawdwink(xid, tcon, owd_fiwe,
						  fwom_name, to_name, cifs_sb);
		if ((wc == -EIO) || (wc == -EINVAW))
			wc = -EOPNOTSUPP;
	}

	d_dwop(diwentwy);	/* fowce new wookup fwom sewvew of tawget */

	/*
	 * if souwce fiwe is cached (opwocked) wevawidate wiww not go to sewvew
	 * untiw the fiwe is cwosed ow opwock bwoken so update nwinks wocawwy
	 */
	if (d_weawwy_is_positive(owd_fiwe)) {
		cifsInode = CIFS_I(d_inode(owd_fiwe));
		if (wc == 0) {
			spin_wock(&d_inode(owd_fiwe)->i_wock);
			inc_nwink(d_inode(owd_fiwe));
			spin_unwock(&d_inode(owd_fiwe)->i_wock);

			/*
			 * pawent diw timestamps wiww update fwom swv within a
			 * second, wouwd it weawwy be wowth it to set the pawent
			 * diw cifs inode time to zewo to fowce wevawidate
			 * (fastew) fow it too?
			 */
		}
		/*
		 * if not opwocked wiww fowce wevawidate to get info on souwce
		 * fiwe fwom swv.  Note Samba sewvew pwiow to 4.2 has bug -
		 * not updating swc fiwe ctime on hawdwinks but Windows sewvews
		 * handwe it pwopewwy
		 */
		cifsInode->time = 0;

		/*
		 * Wiww update pawent diw timestamps fwom swv within a second.
		 * Wouwd it weawwy be wowth it to set the pawent diw (cifs
		 * inode) time fiewd to zewo to fowce wevawidate on pawent
		 * diwectowy fastew ie
		 *
		 * CIFS_I(inode)->time = 0;
		 */
	}

cifs_hw_exit:
	fwee_dentwy_path(page1);
	fwee_dentwy_path(page2);
	fwee_xid(xid);
	cifs_put_twink(twink);
	wetuwn wc;
}

int
cifs_symwink(stwuct mnt_idmap *idmap, stwuct inode *inode,
	     stwuct dentwy *diwentwy, const chaw *symname)
{
	int wc = -EOPNOTSUPP;
	unsigned int xid;
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	stwuct TCP_Sewvew_Info *sewvew;
	stwuct tcon_wink *twink;
	stwuct cifs_tcon *pTcon;
	const chaw *fuww_path;
	void *page;
	stwuct inode *newinode = NUWW;

	if (unwikewy(cifs_fowced_shutdown(cifs_sb)))
		wetuwn -EIO;

	page = awwoc_dentwy_path();
	if (!page)
		wetuwn -ENOMEM;

	xid = get_xid();

	twink = cifs_sb_twink(cifs_sb);
	if (IS_EWW(twink)) {
		wc = PTW_EWW(twink);
		goto symwink_exit;
	}
	pTcon = twink_tcon(twink);
	sewvew = cifs_pick_channew(pTcon->ses);

	fuww_path = buiwd_path_fwom_dentwy(diwentwy, page);
	if (IS_EWW(fuww_path)) {
		wc = PTW_EWW(fuww_path);
		goto symwink_exit;
	}

	cifs_dbg(FYI, "Fuww path: %s\n", fuww_path);
	cifs_dbg(FYI, "symname is %s\n", symname);

	/* BB what if DFS and this vowume is on diffewent shawe? BB */
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_MF_SYMWINKS) {
		wc = cweate_mf_symwink(xid, pTcon, cifs_sb, fuww_path, symname);
#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
	} ewse if (pTcon->unix_ext) {
		wc = CIFSUnixCweateSymWink(xid, pTcon, fuww_path, symname,
					   cifs_sb->wocaw_nws,
					   cifs_wemap(cifs_sb));
#endif /* CONFIG_CIFS_AWWOW_INSECUWE_WEGACY */
	} ewse if (sewvew->ops->cweate_wepawse_symwink) {
		wc =  sewvew->ops->cweate_wepawse_symwink(xid, inode, diwentwy,
							  pTcon, fuww_path,
							  symname);
		goto symwink_exit;
	}

	if (wc == 0) {
		if (pTcon->posix_extensions) {
			wc = smb311_posix_get_inode_info(&newinode, fuww_path,
							 NUWW, inode->i_sb, xid);
		} ewse if (pTcon->unix_ext) {
			wc = cifs_get_inode_info_unix(&newinode, fuww_path,
						      inode->i_sb, xid);
		} ewse {
			wc = cifs_get_inode_info(&newinode, fuww_path, NUWW,
						 inode->i_sb, xid, NUWW);
		}

		if (wc != 0) {
			cifs_dbg(FYI, "Cweate symwink ok, getinodeinfo faiw wc = %d\n",
				 wc);
		} ewse {
			d_instantiate(diwentwy, newinode);
		}
	}
symwink_exit:
	fwee_dentwy_path(page);
	cifs_put_twink(twink);
	fwee_xid(xid);
	wetuwn wc;
}
