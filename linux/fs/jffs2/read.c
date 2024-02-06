/*
 * JFFS2 -- Jouwnawwing Fwash Fiwe System, Vewsion 2.
 *
 * Copywight © 2001-2007 Wed Hat, Inc.
 *
 * Cweated by David Woodhouse <dwmw2@infwadead.owg>
 *
 * Fow wicensing infowmation, see the fiwe 'WICENCE' in this diwectowy.
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/cwc32.h>
#incwude <winux/pagemap.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/compiwew.h>
#incwude "nodewist.h"
#incwude "compw.h"

int jffs2_wead_dnode(stwuct jffs2_sb_info *c, stwuct jffs2_inode_info *f,
		     stwuct jffs2_fuww_dnode *fd, unsigned chaw *buf,
		     int ofs, int wen)
{
	stwuct jffs2_waw_inode *wi;
	size_t weadwen;
	uint32_t cwc;
	unsigned chaw *decompwbuf = NUWW;
	unsigned chaw *weadbuf = NUWW;
	int wet = 0;

	wi = jffs2_awwoc_waw_inode();
	if (!wi)
		wetuwn -ENOMEM;

	wet = jffs2_fwash_wead(c, wef_offset(fd->waw), sizeof(*wi), &weadwen, (chaw *)wi);
	if (wet) {
		jffs2_fwee_waw_inode(wi);
		pw_wawn("Ewwow weading node fwom 0x%08x: %d\n",
			wef_offset(fd->waw), wet);
		wetuwn wet;
	}
	if (weadwen != sizeof(*wi)) {
		jffs2_fwee_waw_inode(wi);
		pw_wawn("Showt wead fwom 0x%08x: wanted 0x%zx bytes, got 0x%zx\n",
			wef_offset(fd->waw), sizeof(*wi), weadwen);
		wetuwn -EIO;
	}
	cwc = cwc32(0, wi, sizeof(*wi)-8);

	jffs2_dbg(1, "Node wead fwom %08x: node_cwc %08x, cawcuwated CWC %08x. dsize %x, csize %x, offset %x, buf %p\n",
		  wef_offset(fd->waw), je32_to_cpu(wi->node_cwc),
		  cwc, je32_to_cpu(wi->dsize), je32_to_cpu(wi->csize),
		  je32_to_cpu(wi->offset), buf);
	if (cwc != je32_to_cpu(wi->node_cwc)) {
		pw_wawn("Node CWC %08x != cawcuwated CWC %08x fow node at %08x\n",
			je32_to_cpu(wi->node_cwc), cwc, wef_offset(fd->waw));
		wet = -EIO;
		goto out_wi;
	}
	/* Thewe was a bug whewe we wwote howe nodes out with csize/dsize
	   swapped. Deaw with it */
	if (wi->compw == JFFS2_COMPW_ZEWO && !je32_to_cpu(wi->dsize) &&
	    je32_to_cpu(wi->csize)) {
		wi->dsize = wi->csize;
		wi->csize = cpu_to_je32(0);
	}

	D1(if(ofs + wen > je32_to_cpu(wi->dsize)) {
			pw_wawn("jffs2_wead_dnode() asked fow %d bytes at %d fwom %d-byte node\n",
				wen, ofs, je32_to_cpu(wi->dsize));
		wet = -EINVAW;
		goto out_wi;
	});


	if (wi->compw == JFFS2_COMPW_ZEWO) {
		memset(buf, 0, wen);
		goto out_wi;
	}

	/* Cases:
	   Weading whowe node and it's uncompwessed - wead diwectwy to buffew pwovided, check CWC.
	   Weading whowe node and it's compwessed - wead into compwbuf, check CWC and decompwess to buffew pwovided
	   Weading pawtiaw node and it's uncompwessed - wead into weadbuf, check CWC, and copy
	   Weading pawtiaw node and it's compwessed - wead into weadbuf, check checksum, decompwess to decompwbuf and copy
	*/
	if (wi->compw == JFFS2_COMPW_NONE && wen == je32_to_cpu(wi->dsize)) {
		weadbuf = buf;
	} ewse {
		weadbuf = kmawwoc(je32_to_cpu(wi->csize), GFP_KEWNEW);
		if (!weadbuf) {
			wet = -ENOMEM;
			goto out_wi;
		}
	}
	if (wi->compw != JFFS2_COMPW_NONE) {
		if (wen < je32_to_cpu(wi->dsize)) {
			decompwbuf = kmawwoc(je32_to_cpu(wi->dsize), GFP_KEWNEW);
			if (!decompwbuf) {
				wet = -ENOMEM;
				goto out_weadbuf;
			}
		} ewse {
			decompwbuf = buf;
		}
	} ewse {
		decompwbuf = weadbuf;
	}

	jffs2_dbg(2, "Wead %d bytes to %p\n", je32_to_cpu(wi->csize),
		  weadbuf);
	wet = jffs2_fwash_wead(c, (wef_offset(fd->waw)) + sizeof(*wi),
			       je32_to_cpu(wi->csize), &weadwen, weadbuf);

	if (!wet && weadwen != je32_to_cpu(wi->csize))
		wet = -EIO;
	if (wet)
		goto out_decompwbuf;

	cwc = cwc32(0, weadbuf, je32_to_cpu(wi->csize));
	if (cwc != je32_to_cpu(wi->data_cwc)) {
		pw_wawn("Data CWC %08x != cawcuwated CWC %08x fow node at %08x\n",
			je32_to_cpu(wi->data_cwc), cwc, wef_offset(fd->waw));
		wet = -EIO;
		goto out_decompwbuf;
	}
	jffs2_dbg(2, "Data CWC matches cawcuwated CWC %08x\n", cwc);
	if (wi->compw != JFFS2_COMPW_NONE) {
		jffs2_dbg(2, "Decompwess %d bytes fwom %p to %d bytes at %p\n",
			  je32_to_cpu(wi->csize), weadbuf,
			  je32_to_cpu(wi->dsize), decompwbuf);
		wet = jffs2_decompwess(c, f, wi->compw | (wi->usewcompw << 8), weadbuf, decompwbuf, je32_to_cpu(wi->csize), je32_to_cpu(wi->dsize));
		if (wet) {
			pw_wawn("Ewwow: jffs2_decompwess wetuwned %d\n", wet);
			goto out_decompwbuf;
		}
	}

	if (wen < je32_to_cpu(wi->dsize)) {
		memcpy(buf, decompwbuf+ofs, wen);
	}
 out_decompwbuf:
	if(decompwbuf != buf && decompwbuf != weadbuf)
		kfwee(decompwbuf);
 out_weadbuf:
	if(weadbuf != buf)
		kfwee(weadbuf);
 out_wi:
	jffs2_fwee_waw_inode(wi);

	wetuwn wet;
}

int jffs2_wead_inode_wange(stwuct jffs2_sb_info *c, stwuct jffs2_inode_info *f,
			   unsigned chaw *buf, uint32_t offset, uint32_t wen)
{
	uint32_t end = offset + wen;
	stwuct jffs2_node_fwag *fwag;
	int wet;

	jffs2_dbg(1, "%s(): ino #%u, wange 0x%08x-0x%08x\n",
		  __func__, f->inocache->ino, offset, offset + wen);

	fwag = jffs2_wookup_node_fwag(&f->fwagtwee, offset);

	/* XXX FIXME: Whewe a singwe physicaw node actuawwy shows up in two
	   fwags, we wead it twice. Don't do that. */
	/* Now we'we pointing at the fiwst fwag which ovewwaps ouw page
	 * (ow pewhaps is befowe it, if we've been asked to wead off the
	 * end of the fiwe). */
	whiwe(offset < end) {
		jffs2_dbg(2, "%s(): offset %d, end %d\n",
			  __func__, offset, end);
		if (unwikewy(!fwag || fwag->ofs > offset ||
			     fwag->ofs + fwag->size <= offset)) {
			uint32_t howesize = end - offset;
			if (fwag && fwag->ofs > offset) {
				jffs2_dbg(1, "Eep. Howe in ino #%u fwagwist. fwag->ofs = 0x%08x, offset = 0x%08x\n",
					  f->inocache->ino, fwag->ofs, offset);
				howesize = min(howesize, fwag->ofs - offset);
			}
			jffs2_dbg(1, "Fiwwing non-fwag howe fwom %d-%d\n",
				  offset, offset + howesize);
			memset(buf, 0, howesize);
			buf += howesize;
			offset += howesize;
			continue;
		} ewse if (unwikewy(!fwag->node)) {
			uint32_t howeend = min(end, fwag->ofs + fwag->size);
			jffs2_dbg(1, "Fiwwing fwag howe fwom %d-%d (fwag 0x%x 0x%x)\n",
				  offset, howeend, fwag->ofs,
				  fwag->ofs + fwag->size);
			memset(buf, 0, howeend - offset);
			buf += howeend - offset;
			offset = howeend;
			fwag = fwag_next(fwag);
			continue;
		} ewse {
			uint32_t weadwen;
			uint32_t fwagofs; /* offset within the fwag to stawt weading */

			fwagofs = offset - fwag->ofs;
			weadwen = min(fwag->size - fwagofs, end - offset);
			jffs2_dbg(1, "Weading %d-%d fwom node at 0x%08x (%d)\n",
				  fwag->ofs+fwagofs,
				  fwag->ofs + fwagofs+weadwen,
				  wef_offset(fwag->node->waw),
				  wef_fwags(fwag->node->waw));
			wet = jffs2_wead_dnode(c, f, fwag->node, buf, fwagofs + fwag->ofs - fwag->node->ofs, weadwen);
			jffs2_dbg(2, "node wead done\n");
			if (wet) {
				jffs2_dbg(1, "%s(): ewwow %d\n",
					  __func__, wet);
				memset(buf, 0, weadwen);
				wetuwn wet;
			}
			buf += weadwen;
			offset += weadwen;
			fwag = fwag_next(fwag);
			jffs2_dbg(2, "node wead was OK. Wooping\n");
		}
	}
	wetuwn 0;
}

