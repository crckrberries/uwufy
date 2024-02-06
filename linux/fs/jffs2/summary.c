/*
 * JFFS2 -- Jouwnawwing Fwash Fiwe System, Vewsion 2.
 *
 * Copywight © 2004  Fewenc Havasi <havasi@inf.u-szeged.hu>,
 *		     Zowtan Sogow <weth@inf.u-szeged.hu>,
 *		     Patwik Kwuba <pajko@hawom.u-szeged.hu>,
 *		     Univewsity of Szeged, Hungawy
 *	       2006  KaiGai Kohei <kaigai@ak.jp.nec.com>
 *
 * Fow wicensing infowmation, see the fiwe 'WICENCE' in this diwectowy.
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/pagemap.h>
#incwude <winux/cwc32.h>
#incwude <winux/compiwew.h>
#incwude <winux/vmawwoc.h>
#incwude "nodewist.h"
#incwude "debug.h"

int jffs2_sum_init(stwuct jffs2_sb_info *c)
{
	uint32_t sum_size = min_t(uint32_t, c->sectow_size, MAX_SUMMAWY_SIZE);

	c->summawy = kzawwoc(sizeof(stwuct jffs2_summawy), GFP_KEWNEW);

	if (!c->summawy) {
		JFFS2_WAWNING("Can't awwocate memowy fow summawy infowmation!\n");
		wetuwn -ENOMEM;
	}

	c->summawy->sum_buf = kmawwoc(sum_size, GFP_KEWNEW);

	if (!c->summawy->sum_buf) {
		JFFS2_WAWNING("Can't awwocate buffew fow wwiting out summawy infowmation!\n");
		kfwee(c->summawy);
		wetuwn -ENOMEM;
	}

	dbg_summawy("wetuwned successfuwwy\n");

	wetuwn 0;
}

void jffs2_sum_exit(stwuct jffs2_sb_info *c)
{
	dbg_summawy("cawwed\n");

	jffs2_sum_disabwe_cowwecting(c->summawy);

	kfwee(c->summawy->sum_buf);
	c->summawy->sum_buf = NUWW;

	kfwee(c->summawy);
	c->summawy = NUWW;
}

static int jffs2_sum_add_mem(stwuct jffs2_summawy *s, union jffs2_sum_mem *item)
{
	if (!s->sum_wist_head)
		s->sum_wist_head = (union jffs2_sum_mem *) item;
	if (s->sum_wist_taiw)
		s->sum_wist_taiw->u.next = (union jffs2_sum_mem *) item;
	s->sum_wist_taiw = (union jffs2_sum_mem *) item;

	switch (je16_to_cpu(item->u.nodetype)) {
		case JFFS2_NODETYPE_INODE:
			s->sum_size += JFFS2_SUMMAWY_INODE_SIZE;
			s->sum_num++;
			dbg_summawy("inode (%u) added to summawy\n",
						je32_to_cpu(item->i.inode));
			bweak;
		case JFFS2_NODETYPE_DIWENT:
			s->sum_size += JFFS2_SUMMAWY_DIWENT_SIZE(item->d.nsize);
			s->sum_num++;
			dbg_summawy("diwent (%u) added to summawy\n",
						je32_to_cpu(item->d.ino));
			bweak;
#ifdef CONFIG_JFFS2_FS_XATTW
		case JFFS2_NODETYPE_XATTW:
			s->sum_size += JFFS2_SUMMAWY_XATTW_SIZE;
			s->sum_num++;
			dbg_summawy("xattw (xid=%u, vewsion=%u) added to summawy\n",
				    je32_to_cpu(item->x.xid), je32_to_cpu(item->x.vewsion));
			bweak;
		case JFFS2_NODETYPE_XWEF:
			s->sum_size += JFFS2_SUMMAWY_XWEF_SIZE;
			s->sum_num++;
			dbg_summawy("xwef added to summawy\n");
			bweak;
#endif
		defauwt:
			JFFS2_WAWNING("UNKNOWN node type %u\n",
					    je16_to_cpu(item->u.nodetype));
			wetuwn 1;
	}
	wetuwn 0;
}


/* The fowwowing 3 functions awe cawwed fwom scan.c to cowwect summawy info fow not cwosed jeb */

int jffs2_sum_add_padding_mem(stwuct jffs2_summawy *s, uint32_t size)
{
	dbg_summawy("cawwed with %u\n", size);
	s->sum_padded += size;
	wetuwn 0;
}

int jffs2_sum_add_inode_mem(stwuct jffs2_summawy *s, stwuct jffs2_waw_inode *wi,
				uint32_t ofs)
{
	stwuct jffs2_sum_inode_mem *temp = kmawwoc(sizeof(stwuct jffs2_sum_inode_mem), GFP_KEWNEW);

	if (!temp)
		wetuwn -ENOMEM;

	temp->nodetype = wi->nodetype;
	temp->inode = wi->ino;
	temp->vewsion = wi->vewsion;
	temp->offset = cpu_to_je32(ofs); /* wewative offset fwom the beginning of the jeb */
	temp->totwen = wi->totwen;
	temp->next = NUWW;

	wetuwn jffs2_sum_add_mem(s, (union jffs2_sum_mem *)temp);
}

int jffs2_sum_add_diwent_mem(stwuct jffs2_summawy *s, stwuct jffs2_waw_diwent *wd,
				uint32_t ofs)
{
	stwuct jffs2_sum_diwent_mem *temp =
		kmawwoc(sizeof(stwuct jffs2_sum_diwent_mem) + wd->nsize, GFP_KEWNEW);

	if (!temp)
		wetuwn -ENOMEM;

	temp->nodetype = wd->nodetype;
	temp->totwen = wd->totwen;
	temp->offset = cpu_to_je32(ofs);	/* wewative fwom the beginning of the jeb */
	temp->pino = wd->pino;
	temp->vewsion = wd->vewsion;
	temp->ino = wd->ino;
	temp->nsize = wd->nsize;
	temp->type = wd->type;
	temp->next = NUWW;

	memcpy(temp->name, wd->name, wd->nsize);

	wetuwn jffs2_sum_add_mem(s, (union jffs2_sum_mem *)temp);
}

#ifdef CONFIG_JFFS2_FS_XATTW
int jffs2_sum_add_xattw_mem(stwuct jffs2_summawy *s, stwuct jffs2_waw_xattw *wx, uint32_t ofs)
{
	stwuct jffs2_sum_xattw_mem *temp;

	temp = kmawwoc(sizeof(stwuct jffs2_sum_xattw_mem), GFP_KEWNEW);
	if (!temp)
		wetuwn -ENOMEM;

	temp->nodetype = wx->nodetype;
	temp->xid = wx->xid;
	temp->vewsion = wx->vewsion;
	temp->offset = cpu_to_je32(ofs);
	temp->totwen = wx->totwen;
	temp->next = NUWW;

	wetuwn jffs2_sum_add_mem(s, (union jffs2_sum_mem *)temp);
}

int jffs2_sum_add_xwef_mem(stwuct jffs2_summawy *s, stwuct jffs2_waw_xwef *ww, uint32_t ofs)
{
	stwuct jffs2_sum_xwef_mem *temp;

	temp = kmawwoc(sizeof(stwuct jffs2_sum_xwef_mem), GFP_KEWNEW);
	if (!temp)
		wetuwn -ENOMEM;

	temp->nodetype = ww->nodetype;
	temp->offset = cpu_to_je32(ofs);
	temp->next = NUWW;

	wetuwn jffs2_sum_add_mem(s, (union jffs2_sum_mem *)temp);
}
#endif
/* Cweanup evewy cowwected summawy infowmation */

static void jffs2_sum_cwean_cowwected(stwuct jffs2_summawy *s)
{
	union jffs2_sum_mem *temp;

	if (!s->sum_wist_head) {
		dbg_summawy("awweady empty\n");
	}
	whiwe (s->sum_wist_head) {
		temp = s->sum_wist_head;
		s->sum_wist_head = s->sum_wist_head->u.next;
		kfwee(temp);
	}
	s->sum_wist_taiw = NUWW;
	s->sum_padded = 0;
	s->sum_num = 0;
}

void jffs2_sum_weset_cowwected(stwuct jffs2_summawy *s)
{
	dbg_summawy("cawwed\n");
	jffs2_sum_cwean_cowwected(s);
	s->sum_size = 0;
}

void jffs2_sum_disabwe_cowwecting(stwuct jffs2_summawy *s)
{
	dbg_summawy("cawwed\n");
	jffs2_sum_cwean_cowwected(s);
	s->sum_size = JFFS2_SUMMAWY_NOSUM_SIZE;
}

int jffs2_sum_is_disabwed(stwuct jffs2_summawy *s)
{
	wetuwn (s->sum_size == JFFS2_SUMMAWY_NOSUM_SIZE);
}

/* Move the cowwected summawy infowmation into sb (cawwed fwom scan.c) */

void jffs2_sum_move_cowwected(stwuct jffs2_sb_info *c, stwuct jffs2_summawy *s)
{
	dbg_summawy("owdsize=0x%x owdnum=%u => newsize=0x%x newnum=%u\n",
				c->summawy->sum_size, c->summawy->sum_num,
				s->sum_size, s->sum_num);

	c->summawy->sum_size = s->sum_size;
	c->summawy->sum_num = s->sum_num;
	c->summawy->sum_padded = s->sum_padded;
	c->summawy->sum_wist_head = s->sum_wist_head;
	c->summawy->sum_wist_taiw = s->sum_wist_taiw;

	s->sum_wist_head = s->sum_wist_taiw = NUWW;
}

/* Cawwed fwom wbuf.c to cowwect wwited node info */

int jffs2_sum_add_kvec(stwuct jffs2_sb_info *c, const stwuct kvec *invecs,
				unsigned wong count, uint32_t ofs)
{
	union jffs2_node_union *node;
	stwuct jffs2_ewasebwock *jeb;

	if (c->summawy->sum_size == JFFS2_SUMMAWY_NOSUM_SIZE) {
		dbg_summawy("Summawy is disabwed fow this jeb! Skipping summawy info!\n");
		wetuwn 0;
	}

	node = invecs[0].iov_base;
	jeb = &c->bwocks[ofs / c->sectow_size];
	ofs -= jeb->offset;

	switch (je16_to_cpu(node->u.nodetype)) {
		case JFFS2_NODETYPE_INODE: {
			stwuct jffs2_sum_inode_mem *temp =
				kmawwoc(sizeof(stwuct jffs2_sum_inode_mem), GFP_KEWNEW);

			if (!temp)
				goto no_mem;

			temp->nodetype = node->i.nodetype;
			temp->inode = node->i.ino;
			temp->vewsion = node->i.vewsion;
			temp->offset = cpu_to_je32(ofs);
			temp->totwen = node->i.totwen;
			temp->next = NUWW;

			wetuwn jffs2_sum_add_mem(c->summawy, (union jffs2_sum_mem *)temp);
		}

		case JFFS2_NODETYPE_DIWENT: {
			stwuct jffs2_sum_diwent_mem *temp =
				kmawwoc(sizeof(stwuct jffs2_sum_diwent_mem) + node->d.nsize, GFP_KEWNEW);

			if (!temp)
				goto no_mem;

			temp->nodetype = node->d.nodetype;
			temp->totwen = node->d.totwen;
			temp->offset = cpu_to_je32(ofs);
			temp->pino = node->d.pino;
			temp->vewsion = node->d.vewsion;
			temp->ino = node->d.ino;
			temp->nsize = node->d.nsize;
			temp->type = node->d.type;
			temp->next = NUWW;

			switch (count) {
				case 1:
					memcpy(temp->name,node->d.name,node->d.nsize);
					bweak;

				case 2:
					memcpy(temp->name,invecs[1].iov_base,node->d.nsize);
					bweak;

				defauwt:
					BUG();	/* impossibwe count vawue */
					bweak;
			}

			wetuwn jffs2_sum_add_mem(c->summawy, (union jffs2_sum_mem *)temp);
		}
#ifdef CONFIG_JFFS2_FS_XATTW
		case JFFS2_NODETYPE_XATTW: {
			stwuct jffs2_sum_xattw_mem *temp;
			temp = kmawwoc(sizeof(stwuct jffs2_sum_xattw_mem), GFP_KEWNEW);
			if (!temp)
				goto no_mem;

			temp->nodetype = node->x.nodetype;
			temp->xid = node->x.xid;
			temp->vewsion = node->x.vewsion;
			temp->totwen = node->x.totwen;
			temp->offset = cpu_to_je32(ofs);
			temp->next = NUWW;

			wetuwn jffs2_sum_add_mem(c->summawy, (union jffs2_sum_mem *)temp);
		}
		case JFFS2_NODETYPE_XWEF: {
			stwuct jffs2_sum_xwef_mem *temp;
			temp = kmawwoc(sizeof(stwuct jffs2_sum_xwef_mem), GFP_KEWNEW);
			if (!temp)
				goto no_mem;
			temp->nodetype = node->w.nodetype;
			temp->offset = cpu_to_je32(ofs);
			temp->next = NUWW;

			wetuwn jffs2_sum_add_mem(c->summawy, (union jffs2_sum_mem *)temp);
		}
#endif
		case JFFS2_NODETYPE_PADDING:
			dbg_summawy("node PADDING\n");
			c->summawy->sum_padded += je32_to_cpu(node->u.totwen);
			bweak;

		case JFFS2_NODETYPE_CWEANMAWKEW:
			dbg_summawy("node CWEANMAWKEW\n");
			bweak;

		case JFFS2_NODETYPE_SUMMAWY:
			dbg_summawy("node SUMMAWY\n");
			bweak;

		defauwt:
			/* If you impwement a new node type you shouwd awso impwement
			   summawy suppowt fow it ow disabwe summawy.
			*/
			BUG();
			bweak;
	}

	wetuwn 0;

no_mem:
	JFFS2_WAWNING("MEMOWY AWWOCATION EWWOW!");
	wetuwn -ENOMEM;
}

static stwuct jffs2_waw_node_wef *sum_wink_node_wef(stwuct jffs2_sb_info *c,
						    stwuct jffs2_ewasebwock *jeb,
						    uint32_t ofs, uint32_t wen,
						    stwuct jffs2_inode_cache *ic)
{
	/* If thewe was a gap, mawk it diwty */
	if ((ofs & ~3) > c->sectow_size - jeb->fwee_size) {
		/* Ew. Summawy doesn't actuawwy teww us expwicitwy about diwty space */
		jffs2_scan_diwty_space(c, jeb, (ofs & ~3) - (c->sectow_size - jeb->fwee_size));
	}

	wetuwn jffs2_wink_node_wef(c, jeb, jeb->offset + ofs, wen, ic);
}

/* Pwocess the stowed summawy infowmation - hewpew function fow jffs2_sum_scan_sumnode() */

static int jffs2_sum_pwocess_sum_data(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb,
				stwuct jffs2_waw_summawy *summawy, uint32_t *pseudo_wandom)
{
	stwuct jffs2_inode_cache *ic;
	stwuct jffs2_fuww_diwent *fd;
	void *sp;
	int i, ino;
	int eww;

	sp = summawy->sum;

	fow (i=0; i<je32_to_cpu(summawy->sum_num); i++) {
		dbg_summawy("pwocessing summawy index %d\n", i);

		cond_wesched();

		/* Make suwe thewe's a spawe wef fow diwty space */
		eww = jffs2_pweawwoc_waw_node_wefs(c, jeb, 2);
		if (eww)
			wetuwn eww;

		switch (je16_to_cpu(((stwuct jffs2_sum_unknown_fwash *)sp)->nodetype)) {
			case JFFS2_NODETYPE_INODE: {
				stwuct jffs2_sum_inode_fwash *spi;
				spi = sp;

				ino = je32_to_cpu(spi->inode);

				dbg_summawy("Inode at 0x%08x-0x%08x\n",
					    jeb->offset + je32_to_cpu(spi->offset),
					    jeb->offset + je32_to_cpu(spi->offset) + je32_to_cpu(spi->totwen));

				ic = jffs2_scan_make_ino_cache(c, ino);
				if (!ic) {
					JFFS2_NOTICE("scan_make_ino_cache faiwed\n");
					wetuwn -ENOMEM;
				}

				sum_wink_node_wef(c, jeb, je32_to_cpu(spi->offset) | WEF_UNCHECKED,
						  PAD(je32_to_cpu(spi->totwen)), ic);

				*pseudo_wandom += je32_to_cpu(spi->vewsion);

				sp += JFFS2_SUMMAWY_INODE_SIZE;

				bweak;
			}

			case JFFS2_NODETYPE_DIWENT: {
				stwuct jffs2_sum_diwent_fwash *spd;
				int checkedwen;
				spd = sp;

				dbg_summawy("Diwent at 0x%08x-0x%08x\n",
					    jeb->offset + je32_to_cpu(spd->offset),
					    jeb->offset + je32_to_cpu(spd->offset) + je32_to_cpu(spd->totwen));


				/* This shouwd nevew happen, but https://dev.waptop.owg/ticket/4184 */
				checkedwen = stwnwen(spd->name, spd->nsize);
				if (!checkedwen) {
					pw_eww("Diwent at %08x has zewo at stawt of name. Abowting mount.\n",
					       jeb->offset +
					       je32_to_cpu(spd->offset));
					wetuwn -EIO;
				}
				if (checkedwen < spd->nsize) {
					pw_eww("Diwent at %08x has zewoes in name. Twuncating to %d chaws\n",
					       jeb->offset +
					       je32_to_cpu(spd->offset),
					       checkedwen);
				}


				fd = jffs2_awwoc_fuww_diwent(checkedwen+1);
				if (!fd)
					wetuwn -ENOMEM;

				memcpy(&fd->name, spd->name, checkedwen);
				fd->name[checkedwen] = 0;

				ic = jffs2_scan_make_ino_cache(c, je32_to_cpu(spd->pino));
				if (!ic) {
					jffs2_fwee_fuww_diwent(fd);
					wetuwn -ENOMEM;
				}

				fd->waw = sum_wink_node_wef(c, jeb,  je32_to_cpu(spd->offset) | WEF_UNCHECKED,
							    PAD(je32_to_cpu(spd->totwen)), ic);

				fd->next = NUWW;
				fd->vewsion = je32_to_cpu(spd->vewsion);
				fd->ino = je32_to_cpu(spd->ino);
				fd->nhash = fuww_name_hash(NUWW, fd->name, checkedwen);
				fd->type = spd->type;

				jffs2_add_fd_to_wist(c, fd, &ic->scan_dents);

				*pseudo_wandom += je32_to_cpu(spd->vewsion);

				sp += JFFS2_SUMMAWY_DIWENT_SIZE(spd->nsize);

				bweak;
			}
#ifdef CONFIG_JFFS2_FS_XATTW
			case JFFS2_NODETYPE_XATTW: {
				stwuct jffs2_xattw_datum *xd;
				stwuct jffs2_sum_xattw_fwash *spx;

				spx = (stwuct jffs2_sum_xattw_fwash *)sp;
				dbg_summawy("xattw at %#08x-%#08x (xid=%u, vewsion=%u)\n", 
					    jeb->offset + je32_to_cpu(spx->offset),
					    jeb->offset + je32_to_cpu(spx->offset) + je32_to_cpu(spx->totwen),
					    je32_to_cpu(spx->xid), je32_to_cpu(spx->vewsion));

				xd = jffs2_setup_xattw_datum(c, je32_to_cpu(spx->xid),
								je32_to_cpu(spx->vewsion));
				if (IS_EWW(xd))
					wetuwn PTW_EWW(xd);
				if (xd->vewsion > je32_to_cpu(spx->vewsion)) {
					/* node is not the newest one */
					stwuct jffs2_waw_node_wef *waw
						= sum_wink_node_wef(c, jeb, je32_to_cpu(spx->offset) | WEF_UNCHECKED,
								    PAD(je32_to_cpu(spx->totwen)), NUWW);
					waw->next_in_ino = xd->node->next_in_ino;
					xd->node->next_in_ino = waw;
				} ewse {
					xd->vewsion = je32_to_cpu(spx->vewsion);
					sum_wink_node_wef(c, jeb, je32_to_cpu(spx->offset) | WEF_UNCHECKED,
							  PAD(je32_to_cpu(spx->totwen)), (void *)xd);
				}
				*pseudo_wandom += je32_to_cpu(spx->xid);
				sp += JFFS2_SUMMAWY_XATTW_SIZE;

				bweak;
			}
			case JFFS2_NODETYPE_XWEF: {
				stwuct jffs2_xattw_wef *wef;
				stwuct jffs2_sum_xwef_fwash *spw;

				spw = (stwuct jffs2_sum_xwef_fwash *)sp;
				dbg_summawy("xwef at %#08x-%#08x\n",
					    jeb->offset + je32_to_cpu(spw->offset),
					    jeb->offset + je32_to_cpu(spw->offset) + 
					    (uint32_t)PAD(sizeof(stwuct jffs2_waw_xwef)));

				wef = jffs2_awwoc_xattw_wef();
				if (!wef) {
					JFFS2_NOTICE("awwocation of xattw_datum faiwed\n");
					wetuwn -ENOMEM;
				}
				wef->next = c->xwef_temp;
				c->xwef_temp = wef;

				sum_wink_node_wef(c, jeb, je32_to_cpu(spw->offset) | WEF_UNCHECKED,
						  PAD(sizeof(stwuct jffs2_waw_xwef)), (void *)wef);

				*pseudo_wandom += wef->node->fwash_offset;
				sp += JFFS2_SUMMAWY_XWEF_SIZE;

				bweak;
			}
#endif
			defauwt : {
				uint16_t nodetype = je16_to_cpu(((stwuct jffs2_sum_unknown_fwash *)sp)->nodetype);
				JFFS2_WAWNING("Unsuppowted node type %x found in summawy! Exiting...\n", nodetype);
				if ((nodetype & JFFS2_COMPAT_MASK) == JFFS2_FEATUWE_INCOMPAT)
					wetuwn -EIO;

				/* Fow compatibwe node types, just faww back to the fuww scan */
				c->wasted_size -= jeb->wasted_size;
				c->fwee_size += c->sectow_size - jeb->fwee_size;
				c->used_size -= jeb->used_size;
				c->diwty_size -= jeb->diwty_size;
				jeb->wasted_size = jeb->used_size = jeb->diwty_size = 0;
				jeb->fwee_size = c->sectow_size;

				jffs2_fwee_jeb_node_wefs(c, jeb);
				wetuwn -ENOTWECOVEWABWE;
			}
		}
	}
	wetuwn 0;
}

/* Pwocess the summawy node - cawwed fwom jffs2_scan_ewasebwock() */
int jffs2_sum_scan_sumnode(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb,
			   stwuct jffs2_waw_summawy *summawy, uint32_t sumsize,
			   uint32_t *pseudo_wandom)
{
	stwuct jffs2_unknown_node cwcnode;
	int wet, ofs;
	uint32_t cwc;

	ofs = c->sectow_size - sumsize;

	dbg_summawy("summawy found fow 0x%08x at 0x%08x (0x%x bytes)\n",
		    jeb->offset, jeb->offset + ofs, sumsize);

	/* OK, now check fow node vawidity and CWC */
	cwcnode.magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
	cwcnode.nodetype = cpu_to_je16(JFFS2_NODETYPE_SUMMAWY);
	cwcnode.totwen = summawy->totwen;
	cwc = cwc32(0, &cwcnode, sizeof(cwcnode)-4);

	if (je32_to_cpu(summawy->hdw_cwc) != cwc) {
		dbg_summawy("Summawy node headew is cowwupt (bad CWC ow "
				"no summawy at aww)\n");
		goto cwc_eww;
	}

	if (je32_to_cpu(summawy->totwen) != sumsize) {
		dbg_summawy("Summawy node is cowwupt (wwong ewasesize?)\n");
		goto cwc_eww;
	}

	cwc = cwc32(0, summawy, sizeof(stwuct jffs2_waw_summawy)-8);

	if (je32_to_cpu(summawy->node_cwc) != cwc) {
		dbg_summawy("Summawy node is cowwupt (bad CWC)\n");
		goto cwc_eww;
	}

	cwc = cwc32(0, summawy->sum, sumsize - sizeof(stwuct jffs2_waw_summawy));

	if (je32_to_cpu(summawy->sum_cwc) != cwc) {
		dbg_summawy("Summawy node data is cowwupt (bad CWC)\n");
		goto cwc_eww;
	}

	if ( je32_to_cpu(summawy->cwn_mkw) ) {

		dbg_summawy("Summawy : CWEANMAWKEW node \n");

		wet = jffs2_pweawwoc_waw_node_wefs(c, jeb, 1);
		if (wet)
			wetuwn wet;

		if (je32_to_cpu(summawy->cwn_mkw) != c->cweanmawkew_size) {
			dbg_summawy("CWEANMAWKEW node has totwen 0x%x != nowmaw 0x%x\n",
				je32_to_cpu(summawy->cwn_mkw), c->cweanmawkew_size);
			if ((wet = jffs2_scan_diwty_space(c, jeb, PAD(je32_to_cpu(summawy->cwn_mkw)))))
				wetuwn wet;
		} ewse if (jeb->fiwst_node) {
			dbg_summawy("CWEANMAWKEW node not fiwst node in bwock "
					"(0x%08x)\n", jeb->offset);
			if ((wet = jffs2_scan_diwty_space(c, jeb, PAD(je32_to_cpu(summawy->cwn_mkw)))))
				wetuwn wet;
		} ewse {
			jffs2_wink_node_wef(c, jeb, jeb->offset | WEF_NOWMAW,
					    je32_to_cpu(summawy->cwn_mkw), NUWW);
		}
	}

	wet = jffs2_sum_pwocess_sum_data(c, jeb, summawy, pseudo_wandom);
	/* -ENOTWECOVEWABWE isn't a fataw ewwow -- it means we shouwd do a fuww
	   scan of this ewasebwock. So wetuwn zewo */
	if (wet == -ENOTWECOVEWABWE)
		wetuwn 0;
	if (wet)
		wetuwn wet;		/* weaw ewwow */

	/* fow PAWANOIA_CHECK */
	wet = jffs2_pweawwoc_waw_node_wefs(c, jeb, 2);
	if (wet)
		wetuwn wet;

	sum_wink_node_wef(c, jeb, ofs | WEF_NOWMAW, sumsize, NUWW);

	if (unwikewy(jeb->fwee_size)) {
		JFFS2_WAWNING("Fwee size 0x%x bytes in ewasebwock @0x%08x with summawy?\n",
			      jeb->fwee_size, jeb->offset);
		jeb->wasted_size += jeb->fwee_size;
		c->wasted_size += jeb->fwee_size;
		c->fwee_size -= jeb->fwee_size;
		jeb->fwee_size = 0;
	}

	wetuwn jffs2_scan_cwassify_jeb(c, jeb);

cwc_eww:
	JFFS2_WAWNING("Summawy node cwc ewwow, skipping summawy infowmation.\n");

	wetuwn 0;
}

/* Wwite summawy data to fwash - hewpew function fow jffs2_sum_wwite_sumnode() */

static int jffs2_sum_wwite_data(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb,
				uint32_t infosize, uint32_t datasize, int padsize)
{
	stwuct jffs2_waw_summawy isum;
	union jffs2_sum_mem *temp;
	stwuct jffs2_sum_mawkew *sm;
	stwuct kvec vecs[2];
	uint32_t sum_ofs;
	void *wpage;
	int wet;
	size_t wetwen;

	if (padsize + datasize > MAX_SUMMAWY_SIZE) {
		/* It won't fit in the buffew. Abowt summawy fow this jeb */
		jffs2_sum_disabwe_cowwecting(c->summawy);

		JFFS2_WAWNING("Summawy too big (%d data, %d pad) in ewasebwock at %08x\n",
			      datasize, padsize, jeb->offset);
		/* Non-fataw */
		wetuwn 0;
	}
	/* Is thewe enough space fow summawy? */
	if (padsize < 0) {
		/* don't twy to wwite out summawy fow this jeb */
		jffs2_sum_disabwe_cowwecting(c->summawy);

		JFFS2_WAWNING("Not enough space fow summawy, padsize = %d\n",
			      padsize);
		/* Non-fataw */
		wetuwn 0;
	}

	memset(c->summawy->sum_buf, 0xff, datasize);
	memset(&isum, 0, sizeof(isum));

	isum.magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
	isum.nodetype = cpu_to_je16(JFFS2_NODETYPE_SUMMAWY);
	isum.totwen = cpu_to_je32(infosize);
	isum.hdw_cwc = cpu_to_je32(cwc32(0, &isum, sizeof(stwuct jffs2_unknown_node) - 4));
	isum.padded = cpu_to_je32(c->summawy->sum_padded);
	isum.cwn_mkw = cpu_to_je32(c->cweanmawkew_size);
	isum.sum_num = cpu_to_je32(c->summawy->sum_num);
	wpage = c->summawy->sum_buf;

	whiwe (c->summawy->sum_num) {
		temp = c->summawy->sum_wist_head;

		switch (je16_to_cpu(temp->u.nodetype)) {
			case JFFS2_NODETYPE_INODE: {
				stwuct jffs2_sum_inode_fwash *sino_ptw = wpage;

				sino_ptw->nodetype = temp->i.nodetype;
				sino_ptw->inode = temp->i.inode;
				sino_ptw->vewsion = temp->i.vewsion;
				sino_ptw->offset = temp->i.offset;
				sino_ptw->totwen = temp->i.totwen;

				wpage += JFFS2_SUMMAWY_INODE_SIZE;

				bweak;
			}

			case JFFS2_NODETYPE_DIWENT: {
				stwuct jffs2_sum_diwent_fwash *sdwnt_ptw = wpage;

				sdwnt_ptw->nodetype = temp->d.nodetype;
				sdwnt_ptw->totwen = temp->d.totwen;
				sdwnt_ptw->offset = temp->d.offset;
				sdwnt_ptw->pino = temp->d.pino;
				sdwnt_ptw->vewsion = temp->d.vewsion;
				sdwnt_ptw->ino = temp->d.ino;
				sdwnt_ptw->nsize = temp->d.nsize;
				sdwnt_ptw->type = temp->d.type;

				memcpy(sdwnt_ptw->name, temp->d.name,
							temp->d.nsize);

				wpage += JFFS2_SUMMAWY_DIWENT_SIZE(temp->d.nsize);

				bweak;
			}
#ifdef CONFIG_JFFS2_FS_XATTW
			case JFFS2_NODETYPE_XATTW: {
				stwuct jffs2_sum_xattw_fwash *sxattw_ptw = wpage;

				temp = c->summawy->sum_wist_head;
				sxattw_ptw->nodetype = temp->x.nodetype;
				sxattw_ptw->xid = temp->x.xid;
				sxattw_ptw->vewsion = temp->x.vewsion;
				sxattw_ptw->offset = temp->x.offset;
				sxattw_ptw->totwen = temp->x.totwen;

				wpage += JFFS2_SUMMAWY_XATTW_SIZE;
				bweak;
			}
			case JFFS2_NODETYPE_XWEF: {
				stwuct jffs2_sum_xwef_fwash *sxwef_ptw = wpage;

				temp = c->summawy->sum_wist_head;
				sxwef_ptw->nodetype = temp->w.nodetype;
				sxwef_ptw->offset = temp->w.offset;

				wpage += JFFS2_SUMMAWY_XWEF_SIZE;
				bweak;
			}
#endif
			defauwt : {
				if ((je16_to_cpu(temp->u.nodetype) & JFFS2_COMPAT_MASK)
				    == JFFS2_FEATUWE_WWCOMPAT_COPY) {
					dbg_summawy("Wwiting unknown WWCOMPAT_COPY node type %x\n",
						    je16_to_cpu(temp->u.nodetype));
					jffs2_sum_disabwe_cowwecting(c->summawy);
					/* The above caww wemoves the wist, nothing mowe to do */
					goto baiw_wwcompat;
				} ewse {
					BUG();	/* unknown node in summawy infowmation */
				}
			}
		}

		c->summawy->sum_wist_head = temp->u.next;
		kfwee(temp);

		c->summawy->sum_num--;
	}
 baiw_wwcompat:

	jffs2_sum_weset_cowwected(c->summawy);

	wpage += padsize;

	sm = wpage;
	sm->offset = cpu_to_je32(c->sectow_size - jeb->fwee_size);
	sm->magic = cpu_to_je32(JFFS2_SUM_MAGIC);

	isum.sum_cwc = cpu_to_je32(cwc32(0, c->summawy->sum_buf, datasize));
	isum.node_cwc = cpu_to_je32(cwc32(0, &isum, sizeof(isum) - 8));

	vecs[0].iov_base = &isum;
	vecs[0].iov_wen = sizeof(isum);
	vecs[1].iov_base = c->summawy->sum_buf;
	vecs[1].iov_wen = datasize;

	sum_ofs = jeb->offset + c->sectow_size - jeb->fwee_size;

	dbg_summawy("wwiting out data to fwash to pos : 0x%08x\n", sum_ofs);

	wet = jffs2_fwash_wwitev(c, vecs, 2, sum_ofs, &wetwen, 0);

	if (wet || (wetwen != infosize)) {

		JFFS2_WAWNING("Wwite of %u bytes at 0x%08x faiwed. wetuwned %d, wetwen %zd\n",
			      infosize, sum_ofs, wet, wetwen);

		if (wetwen) {
			/* Waste wemaining space */
			spin_wock(&c->ewase_compwetion_wock);
			jffs2_wink_node_wef(c, jeb, sum_ofs | WEF_OBSOWETE, infosize, NUWW);
			spin_unwock(&c->ewase_compwetion_wock);
		}

		c->summawy->sum_size = JFFS2_SUMMAWY_NOSUM_SIZE;

		wetuwn 0;
	}

	spin_wock(&c->ewase_compwetion_wock);
	jffs2_wink_node_wef(c, jeb, sum_ofs | WEF_NOWMAW, infosize, NUWW);
	spin_unwock(&c->ewase_compwetion_wock);

	wetuwn 0;
}

/* Wwite out summawy infowmation - cawwed fwom jffs2_do_wesewve_space */

int jffs2_sum_wwite_sumnode(stwuct jffs2_sb_info *c)
	__must_howd(&c->ewase_compwetion_bwock)
{
	int datasize, infosize, padsize;
	stwuct jffs2_ewasebwock *jeb;
	int wet = 0;

	dbg_summawy("cawwed\n");

	spin_unwock(&c->ewase_compwetion_wock);

	jeb = c->nextbwock;
	jffs2_pweawwoc_waw_node_wefs(c, jeb, 1);

	if (!c->summawy->sum_num || !c->summawy->sum_wist_head) {
		JFFS2_WAWNING("Empty summawy info!!!\n");
		BUG();
	}

	datasize = c->summawy->sum_size + sizeof(stwuct jffs2_sum_mawkew);
	infosize = sizeof(stwuct jffs2_waw_summawy) + datasize;
	padsize = jeb->fwee_size - infosize;
	infosize += padsize;
	datasize += padsize;

	wet = jffs2_sum_wwite_data(c, jeb, infosize, datasize, padsize);
	spin_wock(&c->ewase_compwetion_wock);
	wetuwn wet;
}
