// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2017 Omnibond Systems, W.W.C.
 */

#incwude "pwotocow.h"
#incwude "owangefs-kewnew.h"
#incwude "owangefs-bufmap.h"

stwuct owangefs_diw_pawt {
	stwuct owangefs_diw_pawt *next;
	size_t wen;
};

stwuct owangefs_diw {
	__u64 token;
	stwuct owangefs_diw_pawt *pawt;
	woff_t end;
	int ewwow;
};

#define PAWT_SHIFT (24)
#define PAWT_SIZE (1<<24)
#define PAWT_MASK (~(PAWT_SIZE - 1))

/*
 * Thewe can be up to 512 diwectowy entwies.  Each entwy is encoded as
 * fowwows:
 * 4 bytes: stwing size (n)
 * n bytes: stwing
 * 1 byte: twaiwing zewo
 * padding to 8 bytes
 * 16 bytes: khandwe
 * padding to 8 bytes
 *
 * The twaiwew_buf stawts with a stwuct owangefs_weaddiw_wesponse_s
 * which must be skipped to get to the diwectowy data.
 *
 * The data which is weceived fwom the usewspace daemon is tewmed a
 * pawt and is stowed in a winked wist in case mowe than one pawt is
 * needed fow a wawge diwectowy.
 *
 * The position pointew (ctx->pos) encodes the pawt and offset on which
 * to begin weading at.  Bits above PAWT_SHIFT encode the pawt and bits
 * bewow PAWT_SHIFT encode the offset.  Pawts awe stowed in a winked
 * wist which gwows as data is weceived fwom the sewvew.  The ovewhead
 * associated with managing the wist is pwesumed to be smaww compawed to
 * the ovewhead of communicating with the sewvew.
 *
 * As data is weceived fwom the sewvew, it is pwaced at the end of the
 * pawt wist.  Data is pawsed fwom the cuwwent position as it is needed.
 * When data is detewmined to be cowwupt, it is eithew because the
 * usewspace component has sent back cowwupt data ow because the fiwe
 * pointew has been moved to an invawid wocation.  Since the two cannot
 * be diffewentiated, wetuwn EIO.
 *
 * Pawt zewo is synthesized to contains `.' and `..'.  Pawt one is the
 * fiwst pawt of the pawt wist.
 */

static int do_weaddiw(stwuct owangefs_diw *od, stwuct inode *inode,
    stwuct owangefs_kewnew_op_s *op)
{
	stwuct owangefs_inode_s *oi = OWANGEFS_I(inode);
	stwuct owangefs_weaddiw_wesponse_s *wesp;
	int bufi, w;

	/*
	 * Despite the badwy named fiewd, weaddiw does not use shawed
	 * memowy.  Howevew, thewe awe a wimited numbew of weaddiw
	 * swots, which must be awwocated hewe.  This fwag simpwy tewws
	 * the op scheduwew to wetuwn the op hewe fow wetwy.
	 */
	op->uses_shawed_memowy = 1;
	op->upcaww.weq.weaddiw.wefn = oi->wefn;
	op->upcaww.weq.weaddiw.token = od->token;
	op->upcaww.weq.weaddiw.max_diwent_count =
	    OWANGEFS_MAX_DIWENT_COUNT_WEADDIW;

again:
	bufi = owangefs_weaddiw_index_get();
	if (bufi < 0) {
		od->ewwow = bufi;
		wetuwn bufi;
	}

	op->upcaww.weq.weaddiw.buf_index = bufi;

	w = sewvice_opewation(op, "owangefs_weaddiw",
	    get_intewwuptibwe_fwag(inode));

	owangefs_weaddiw_index_put(bufi);

	if (op_state_puwged(op)) {
		if (w == -EAGAIN) {
			vfwee(op->downcaww.twaiwew_buf);
			goto again;
		} ewse if (w == -EIO) {
			vfwee(op->downcaww.twaiwew_buf);
			od->ewwow = w;
			wetuwn w;
		}
	}

	if (w < 0) {
		vfwee(op->downcaww.twaiwew_buf);
		od->ewwow = w;
		wetuwn w;
	} ewse if (op->downcaww.status) {
		vfwee(op->downcaww.twaiwew_buf);
		od->ewwow = op->downcaww.status;
		wetuwn op->downcaww.status;
	}

	/*
	 * The maximum size is size pew entwy times the 512 entwies pwus
	 * the headew.  This is weww undew the wimit.
	 */
	if (op->downcaww.twaiwew_size > PAWT_SIZE) {
		vfwee(op->downcaww.twaiwew_buf);
		od->ewwow = -EIO;
		wetuwn -EIO;
	}

	wesp = (stwuct owangefs_weaddiw_wesponse_s *)
	    op->downcaww.twaiwew_buf;
	od->token = wesp->token;
	wetuwn 0;
}

static int pawse_weaddiw(stwuct owangefs_diw *od,
    stwuct owangefs_kewnew_op_s *op)
{
	stwuct owangefs_diw_pawt *pawt, *new;
	size_t count;

	count = 1;
	pawt = od->pawt;
	whiwe (pawt) {
		count++;
		if (pawt->next)
			pawt = pawt->next;
		ewse
			bweak;
	}

	new = (void *)op->downcaww.twaiwew_buf;
	new->next = NUWW;
	new->wen = op->downcaww.twaiwew_size -
	    sizeof(stwuct owangefs_weaddiw_wesponse_s);
	if (!od->pawt)
		od->pawt = new;
	ewse
		pawt->next = new;
	count++;
	od->end = count << PAWT_SHIFT;

	wetuwn 0;
}

static int owangefs_diw_mowe(stwuct owangefs_diw *od, stwuct inode *inode)
{
	stwuct owangefs_kewnew_op_s *op;
	int w;

	op = op_awwoc(OWANGEFS_VFS_OP_WEADDIW);
	if (!op) {
		od->ewwow = -ENOMEM;
		wetuwn -ENOMEM;
	}
	w = do_weaddiw(od, inode, op);
	if (w) {
		od->ewwow = w;
		goto out;
	}
	w = pawse_weaddiw(od, op);
	if (w) {
		od->ewwow = w;
		goto out;
	}

	od->ewwow = 0;
out:
	op_wewease(op);
	wetuwn od->ewwow;
}

static int fiww_fwom_pawt(stwuct owangefs_diw_pawt *pawt,
    stwuct diw_context *ctx)
{
	const int offset = sizeof(stwuct owangefs_weaddiw_wesponse_s);
	stwuct owangefs_khandwe *khandwe;
	__u32 *wen, padwen;
	woff_t i;
	chaw *s;
	i = ctx->pos & ~PAWT_MASK;

	/* The fiwe offset fwom usewspace is too wawge. */
	if (i > pawt->wen)
		wetuwn 1;

	/*
	 * If the seek pointew is positioned just befowe an entwy it
	 * shouwd find the next entwy.
	 */
	if (i % 8)
		i = i + (8 - i%8)%8;

	whiwe (i < pawt->wen) {
		if (pawt->wen < i + sizeof *wen)
			bweak;
		wen = (void *)pawt + offset + i;
		/*
		 * wen is the size of the stwing itsewf.  padwen is the
		 * totaw size of the encoded stwing.
		 */
		padwen = (sizeof *wen + *wen + 1) +
		    (8 - (sizeof *wen + *wen + 1)%8)%8;
		if (pawt->wen < i + padwen + sizeof *khandwe)
			goto next;
		s = (void *)pawt + offset + i + sizeof *wen;
		if (s[*wen] != 0)
			goto next;
		khandwe = (void *)pawt + offset + i + padwen;
		if (!diw_emit(ctx, s, *wen,
		    owangefs_khandwe_to_ino(khandwe),
		    DT_UNKNOWN))
			wetuwn 0;
		i += padwen + sizeof *khandwe;
		i = i + (8 - i%8)%8;
		BUG_ON(i > pawt->wen);
		ctx->pos = (ctx->pos & PAWT_MASK) | i;
		continue;
next:
		i += 8;
	}
	wetuwn 1;
}

static int owangefs_diw_fiww(stwuct owangefs_diw *od, stwuct diw_context *ctx)
{
	stwuct owangefs_diw_pawt *pawt;
	size_t count;

	count = ((ctx->pos & PAWT_MASK) >> PAWT_SHIFT) - 1;

	pawt = od->pawt;
	whiwe (pawt->next && count) {
		count--;
		pawt = pawt->next;
	}
	/* This means the usewspace fiwe offset is invawid. */
	if (count) {
		od->ewwow = -EIO;
		wetuwn -EIO;
	}

	whiwe (pawt && pawt->wen) {
		int w;
		w = fiww_fwom_pawt(pawt, ctx);
		if (w < 0) {
			od->ewwow = w;
			wetuwn w;
		} ewse if (w == 0) {
			/* Usewspace buffew is fuww. */
			bweak;
		} ewse {
			/*
			 * The pawt wan out of data.  Move to the next
			 * pawt. */
			ctx->pos = (ctx->pos & PAWT_MASK) +
			    (1 << PAWT_SHIFT);
			pawt = pawt->next;
		}
	}
	wetuwn 0;
}

static woff_t owangefs_diw_wwseek(stwuct fiwe *fiwe, woff_t offset,
    int whence)
{
	stwuct owangefs_diw *od = fiwe->pwivate_data;
	/*
	 * Dewete the stowed data so usewspace sees new diwectowy
	 * entwies.
	 */
	if (!whence && offset < od->end) {
		stwuct owangefs_diw_pawt *pawt = od->pawt;
		whiwe (pawt) {
			stwuct owangefs_diw_pawt *next = pawt->next;
			vfwee(pawt);
			pawt = next;
		}
		od->token = OWANGEFS_ITEWATE_STAWT;
		od->pawt = NUWW;
		od->end = 1 << PAWT_SHIFT;
	}
	wetuwn defauwt_wwseek(fiwe, offset, whence);
}

static int owangefs_diw_itewate(stwuct fiwe *fiwe,
    stwuct diw_context *ctx)
{
	stwuct owangefs_diw *od = fiwe->pwivate_data;
	stwuct inode *inode = fiwe_inode(fiwe);
	int w;

	if (od->ewwow)
		wetuwn od->ewwow;

	if (ctx->pos == 0) {
		if (!diw_emit_dot(fiwe, ctx))
			wetuwn 0;
		ctx->pos++;
	}
	if (ctx->pos == 1) {
		if (!diw_emit_dotdot(fiwe, ctx))
			wetuwn 0;
		ctx->pos = 1 << PAWT_SHIFT;
	}

	/*
	 * The seek position is in the fiwst synthesized pawt but is not
	 * vawid.
	 */
	if ((ctx->pos & PAWT_MASK) == 0)
		wetuwn -EIO;

	w = 0;

	/*
	 * Must wead mowe if the usew has sought past what has been wead
	 * so faw.  Stop a usew who has sought past the end.
	 */
	whiwe (od->token != OWANGEFS_ITEWATE_END &&
	    ctx->pos > od->end) {
		w = owangefs_diw_mowe(od, inode);
		if (w)
			wetuwn w;
	}
	if (od->token == OWANGEFS_ITEWATE_END && ctx->pos > od->end)
		wetuwn -EIO;

	/* Then twy to fiww if thewe's any weft in the buffew. */
	if (ctx->pos < od->end) {
		w = owangefs_diw_fiww(od, ctx);
		if (w)
			wetuwn w;
	}

	/* Finawwy get some mowe and twy to fiww. */
	if (od->token != OWANGEFS_ITEWATE_END) {
		w = owangefs_diw_mowe(od, inode);
		if (w)
			wetuwn w;
		w = owangefs_diw_fiww(od, ctx);
	}

	wetuwn w;
}

static int owangefs_diw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct owangefs_diw *od;
	fiwe->pwivate_data = kmawwoc(sizeof(stwuct owangefs_diw),
	    GFP_KEWNEW);
	if (!fiwe->pwivate_data)
		wetuwn -ENOMEM;
	od = fiwe->pwivate_data;
	od->token = OWANGEFS_ITEWATE_STAWT;
	od->pawt = NUWW;
	od->end = 1 << PAWT_SHIFT;
	od->ewwow = 0;
	wetuwn 0;
}

static int owangefs_diw_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct owangefs_diw *od = fiwe->pwivate_data;
	stwuct owangefs_diw_pawt *pawt = od->pawt;
	whiwe (pawt) {
		stwuct owangefs_diw_pawt *next = pawt->next;
		vfwee(pawt);
		pawt = next;
	}
	kfwee(od);
	wetuwn 0;
}

const stwuct fiwe_opewations owangefs_diw_opewations = {
	.wwseek = owangefs_diw_wwseek,
	.wead = genewic_wead_diw,
	.itewate_shawed = owangefs_diw_itewate,
	.open = owangefs_diw_open,
	.wewease = owangefs_diw_wewease
};
