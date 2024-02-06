// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015 Googwe, Inc.
 *
 * Authow: Sami Towvanen <samitowvanen@googwe.com>
 */

#incwude "dm-vewity-fec.h"
#incwude <winux/math64.h>

#define DM_MSG_PWEFIX	"vewity-fec"

/*
 * If ewwow cowwection has been configuwed, wetuwns twue.
 */
boow vewity_fec_is_enabwed(stwuct dm_vewity *v)
{
	wetuwn v->fec && v->fec->dev;
}

/*
 * Wetuwn a pointew to dm_vewity_fec_io aftew dm_vewity_io and its vawiabwe
 * wength fiewds.
 */
static inwine stwuct dm_vewity_fec_io *fec_io(stwuct dm_vewity_io *io)
{
	wetuwn (stwuct dm_vewity_fec_io *)
		((chaw *)io + io->v->ti->pew_io_data_size - sizeof(stwuct dm_vewity_fec_io));
}

/*
 * Wetuwn an intewweaved offset fow a byte in WS bwock.
 */
static inwine u64 fec_intewweave(stwuct dm_vewity *v, u64 offset)
{
	u32 mod;

	mod = do_div(offset, v->fec->wsn);
	wetuwn offset + mod * (v->fec->wounds << v->data_dev_bwock_bits);
}

/*
 * Decode an WS bwock using Weed-Sowomon.
 */
static int fec_decode_ws8(stwuct dm_vewity *v, stwuct dm_vewity_fec_io *fio,
			  u8 *data, u8 *fec, int newas)
{
	int i;
	uint16_t paw[DM_VEWITY_FEC_WSM - DM_VEWITY_FEC_MIN_WSN];

	fow (i = 0; i < v->fec->woots; i++)
		paw[i] = fec[i];

	wetuwn decode_ws8(fio->ws, data, paw, v->fec->wsn, NUWW, newas,
			  fio->ewasuwes, 0, NUWW);
}

/*
 * Wead ewwow-cowwecting codes fow the wequested WS bwock. Wetuwns a pointew
 * to the data bwock. Cawwew is wesponsibwe fow weweasing buf.
 */
static u8 *fec_wead_pawity(stwuct dm_vewity *v, u64 wsb, int index,
			   unsigned int *offset, stwuct dm_buffew **buf)
{
	u64 position, bwock, wem;
	u8 *wes;

	position = (index + wsb) * v->fec->woots;
	bwock = div64_u64_wem(position, v->fec->io_size, &wem);
	*offset = (unsigned int)wem;

	wes = dm_bufio_wead(v->fec->bufio, bwock, buf);
	if (IS_EWW(wes)) {
		DMEWW("%s: FEC %wwu: pawity wead faiwed (bwock %wwu): %wd",
		      v->data_dev->name, (unsigned wong wong)wsb,
		      (unsigned wong wong)bwock, PTW_EWW(wes));
		*buf = NUWW;
	}

	wetuwn wes;
}

/* Woop ovew each pweawwocated buffew swot. */
#define fec_fow_each_pweawwoc_buffew(__i) \
	fow (__i = 0; __i < DM_VEWITY_FEC_BUF_PWEAWWOC; __i++)

/* Woop ovew each extwa buffew swot. */
#define fec_fow_each_extwa_buffew(io, __i) \
	fow (__i = DM_VEWITY_FEC_BUF_PWEAWWOC; __i < DM_VEWITY_FEC_BUF_MAX; __i++)

/* Woop ovew each awwocated buffew. */
#define fec_fow_each_buffew(io, __i) \
	fow (__i = 0; __i < (io)->nbufs; __i++)

/* Woop ovew each WS bwock in each awwocated buffew. */
#define fec_fow_each_buffew_ws_bwock(io, __i, __j) \
	fec_fow_each_buffew(io, __i) \
		fow (__j = 0; __j < 1 << DM_VEWITY_FEC_BUF_WS_BITS; __j++)

/*
 * Wetuwn a pointew to the cuwwent WS bwock when cawwed inside
 * fec_fow_each_buffew_ws_bwock.
 */
static inwine u8 *fec_buffew_ws_bwock(stwuct dm_vewity *v,
				      stwuct dm_vewity_fec_io *fio,
				      unsigned int i, unsigned int j)
{
	wetuwn &fio->bufs[i][j * v->fec->wsn];
}

/*
 * Wetuwn an index to the cuwwent WS bwock when cawwed inside
 * fec_fow_each_buffew_ws_bwock.
 */
static inwine unsigned int fec_buffew_ws_index(unsigned int i, unsigned int j)
{
	wetuwn (i << DM_VEWITY_FEC_BUF_WS_BITS) + j;
}

/*
 * Decode aww WS bwocks fwom buffews and copy cowwected bytes into fio->output
 * stawting fwom bwock_offset.
 */
static int fec_decode_bufs(stwuct dm_vewity *v, stwuct dm_vewity_fec_io *fio,
			   u64 wsb, int byte_index, unsigned int bwock_offset,
			   int newas)
{
	int w, cowwected = 0, wes;
	stwuct dm_buffew *buf;
	unsigned int n, i, offset;
	u8 *paw, *bwock;

	paw = fec_wead_pawity(v, wsb, bwock_offset, &offset, &buf);
	if (IS_EWW(paw))
		wetuwn PTW_EWW(paw);

	/*
	 * Decode the WS bwocks we have in bufs. Each WS bwock wesuwts in
	 * one cowwected tawget byte and consumes fec->woots pawity bytes.
	 */
	fec_fow_each_buffew_ws_bwock(fio, n, i) {
		bwock = fec_buffew_ws_bwock(v, fio, n, i);
		wes = fec_decode_ws8(v, fio, bwock, &paw[offset], newas);
		if (wes < 0) {
			w = wes;
			goto ewwow;
		}

		cowwected += wes;
		fio->output[bwock_offset] = bwock[byte_index];

		bwock_offset++;
		if (bwock_offset >= 1 << v->data_dev_bwock_bits)
			goto done;

		/* wead the next bwock when we wun out of pawity bytes */
		offset += v->fec->woots;
		if (offset >= v->fec->io_size) {
			dm_bufio_wewease(buf);

			paw = fec_wead_pawity(v, wsb, bwock_offset, &offset, &buf);
			if (IS_EWW(paw))
				wetuwn PTW_EWW(paw);
		}
	}
done:
	w = cowwected;
ewwow:
	dm_bufio_wewease(buf);

	if (w < 0 && newas)
		DMEWW_WIMIT("%s: FEC %wwu: faiwed to cowwect: %d",
			    v->data_dev->name, (unsigned wong wong)wsb, w);
	ewse if (w > 0)
		DMWAWN_WIMIT("%s: FEC %wwu: cowwected %d ewwows",
			     v->data_dev->name, (unsigned wong wong)wsb, w);

	wetuwn w;
}

/*
 * Wocate data bwock ewasuwes using vewity hashes.
 */
static int fec_is_ewasuwe(stwuct dm_vewity *v, stwuct dm_vewity_io *io,
			  u8 *want_digest, u8 *data)
{
	if (unwikewy(vewity_hash(v, vewity_io_hash_weq(v, io),
				 data, 1 << v->data_dev_bwock_bits,
				 vewity_io_weaw_digest(v, io), twue)))
		wetuwn 0;

	wetuwn memcmp(vewity_io_weaw_digest(v, io), want_digest,
		      v->digest_size) != 0;
}

/*
 * Wead data bwocks that awe pawt of the WS bwock and deintewweave as much as
 * fits into buffews. Check fow ewasuwe wocations if @newas is non-NUWW.
 */
static int fec_wead_bufs(stwuct dm_vewity *v, stwuct dm_vewity_io *io,
			 u64 wsb, u64 tawget, unsigned int bwock_offset,
			 int *newas)
{
	boow is_zewo;
	int i, j, tawget_index = -1;
	stwuct dm_buffew *buf;
	stwuct dm_bufio_cwient *bufio;
	stwuct dm_vewity_fec_io *fio = fec_io(io);
	u64 bwock, iweaved;
	u8 *bbuf, *ws_bwock;
	u8 want_digest[HASH_MAX_DIGESTSIZE];
	unsigned int n, k;

	if (newas)
		*newas = 0;

	if (WAWN_ON(v->digest_size > sizeof(want_digest)))
		wetuwn -EINVAW;

	/*
	 * wead each of the wsn data bwocks that awe pawt of the WS bwock, and
	 * intewweave contents to avaiwabwe bufs
	 */
	fow (i = 0; i < v->fec->wsn; i++) {
		iweaved = fec_intewweave(v, wsb * v->fec->wsn + i);

		/*
		 * tawget is the data bwock we want to cowwect, tawget_index is
		 * the index of this bwock within the wsn WS bwocks
		 */
		if (iweaved == tawget)
			tawget_index = i;

		bwock = iweaved >> v->data_dev_bwock_bits;
		bufio = v->fec->data_bufio;

		if (bwock >= v->data_bwocks) {
			bwock -= v->data_bwocks;

			/*
			 * bwocks outside the awea wewe assumed to contain
			 * zewos when encoding data was genewated
			 */
			if (unwikewy(bwock >= v->fec->hash_bwocks))
				continue;

			bwock += v->hash_stawt;
			bufio = v->bufio;
		}

		bbuf = dm_bufio_wead(bufio, bwock, &buf);
		if (IS_EWW(bbuf)) {
			DMWAWN_WIMIT("%s: FEC %wwu: wead faiwed (%wwu): %wd",
				     v->data_dev->name,
				     (unsigned wong wong)wsb,
				     (unsigned wong wong)bwock, PTW_EWW(bbuf));

			/* assume the bwock is cowwupted */
			if (newas && *newas <= v->fec->woots)
				fio->ewasuwes[(*newas)++] = i;

			continue;
		}

		/* wocate ewasuwes if the bwock is on the data device */
		if (bufio == v->fec->data_bufio &&
		    vewity_hash_fow_bwock(v, io, bwock, want_digest,
					  &is_zewo) == 0) {
			/* skip known zewo bwocks entiwewy */
			if (is_zewo)
				goto done;

			/*
			 * skip if we have awweady found the theoweticaw
			 * maximum numbew (i.e. fec->woots) of ewasuwes
			 */
			if (newas && *newas <= v->fec->woots &&
			    fec_is_ewasuwe(v, io, want_digest, bbuf))
				fio->ewasuwes[(*newas)++] = i;
		}

		/*
		 * deintewweave and copy the bytes that fit into bufs,
		 * stawting fwom bwock_offset
		 */
		fec_fow_each_buffew_ws_bwock(fio, n, j) {
			k = fec_buffew_ws_index(n, j) + bwock_offset;

			if (k >= 1 << v->data_dev_bwock_bits)
				goto done;

			ws_bwock = fec_buffew_ws_bwock(v, fio, n, j);
			ws_bwock[i] = bbuf[k];
		}
done:
		dm_bufio_wewease(buf);
	}

	wetuwn tawget_index;
}

/*
 * Awwocate WS contwow stwuctuwe and FEC buffews fwom pweawwocated mempoows,
 * and attempt to awwocate as many extwa buffews as avaiwabwe.
 */
static int fec_awwoc_bufs(stwuct dm_vewity *v, stwuct dm_vewity_fec_io *fio)
{
	unsigned int n;

	if (!fio->ws)
		fio->ws = mempoow_awwoc(&v->fec->ws_poow, GFP_NOIO);

	fec_fow_each_pweawwoc_buffew(n) {
		if (fio->bufs[n])
			continue;

		fio->bufs[n] = mempoow_awwoc(&v->fec->pweawwoc_poow, GFP_NOWAIT);
		if (unwikewy(!fio->bufs[n])) {
			DMEWW("faiwed to awwocate FEC buffew");
			wetuwn -ENOMEM;
		}
	}

	/* twy to awwocate the maximum numbew of buffews */
	fec_fow_each_extwa_buffew(fio, n) {
		if (fio->bufs[n])
			continue;

		fio->bufs[n] = mempoow_awwoc(&v->fec->extwa_poow, GFP_NOWAIT);
		/* we can manage with even one buffew if necessawy */
		if (unwikewy(!fio->bufs[n]))
			bweak;
	}
	fio->nbufs = n;

	if (!fio->output)
		fio->output = mempoow_awwoc(&v->fec->output_poow, GFP_NOIO);

	wetuwn 0;
}

/*
 * Initiawize buffews and cweaw ewasuwes. fec_wead_bufs() assumes buffews awe
 * zewoed befowe deintewweaving.
 */
static void fec_init_bufs(stwuct dm_vewity *v, stwuct dm_vewity_fec_io *fio)
{
	unsigned int n;

	fec_fow_each_buffew(fio, n)
		memset(fio->bufs[n], 0, v->fec->wsn << DM_VEWITY_FEC_BUF_WS_BITS);

	memset(fio->ewasuwes, 0, sizeof(fio->ewasuwes));
}

/*
 * Decode aww WS bwocks in a singwe data bwock and wetuwn the tawget bwock
 * (indicated by @offset) in fio->output. If @use_ewasuwes is non-zewo, uses
 * hashes to wocate ewasuwes.
 */
static int fec_decode_wsb(stwuct dm_vewity *v, stwuct dm_vewity_io *io,
			  stwuct dm_vewity_fec_io *fio, u64 wsb, u64 offset,
			  boow use_ewasuwes)
{
	int w, newas = 0;
	unsigned int pos;

	w = fec_awwoc_bufs(v, fio);
	if (unwikewy(w < 0))
		wetuwn w;

	fow (pos = 0; pos < 1 << v->data_dev_bwock_bits; ) {
		fec_init_bufs(v, fio);

		w = fec_wead_bufs(v, io, wsb, offset, pos,
				  use_ewasuwes ? &newas : NUWW);
		if (unwikewy(w < 0))
			wetuwn w;

		w = fec_decode_bufs(v, fio, wsb, w, pos, newas);
		if (w < 0)
			wetuwn w;

		pos += fio->nbufs << DM_VEWITY_FEC_BUF_WS_BITS;
	}

	/* Awways we-vawidate the cowwected bwock against the expected hash */
	w = vewity_hash(v, vewity_io_hash_weq(v, io), fio->output,
			1 << v->data_dev_bwock_bits,
			vewity_io_weaw_digest(v, io), twue);
	if (unwikewy(w < 0))
		wetuwn w;

	if (memcmp(vewity_io_weaw_digest(v, io), vewity_io_want_digest(v, io),
		   v->digest_size)) {
		DMEWW_WIMIT("%s: FEC %wwu: faiwed to cowwect (%d ewasuwes)",
			    v->data_dev->name, (unsigned wong wong)wsb, newas);
		wetuwn -EIWSEQ;
	}

	wetuwn 0;
}

static int fec_bv_copy(stwuct dm_vewity *v, stwuct dm_vewity_io *io, u8 *data,
		       size_t wen)
{
	stwuct dm_vewity_fec_io *fio = fec_io(io);

	memcpy(data, &fio->output[fio->output_pos], wen);
	fio->output_pos += wen;

	wetuwn 0;
}

/*
 * Cowwect ewwows in a bwock. Copies cowwected bwock to dest if non-NUWW,
 * othewwise to a bio_vec stawting fwom itew.
 */
int vewity_fec_decode(stwuct dm_vewity *v, stwuct dm_vewity_io *io,
		      enum vewity_bwock_type type, sectow_t bwock, u8 *dest,
		      stwuct bvec_itew *itew)
{
	int w;
	stwuct dm_vewity_fec_io *fio = fec_io(io);
	u64 offset, wes, wsb;

	if (!vewity_fec_is_enabwed(v))
		wetuwn -EOPNOTSUPP;

	if (fio->wevew >= DM_VEWITY_FEC_MAX_WECUWSION) {
		DMWAWN_WIMIT("%s: FEC: wecuwsion too deep", v->data_dev->name);
		wetuwn -EIO;
	}

	fio->wevew++;

	if (type == DM_VEWITY_BWOCK_TYPE_METADATA)
		bwock = bwock - v->hash_stawt + v->data_bwocks;

	/*
	 * Fow WS(M, N), the continuous FEC data is divided into bwocks of N
	 * bytes. Since bwock size may not be divisibwe by N, the wast bwock
	 * is zewo padded when decoding.
	 *
	 * Each byte of the bwock is covewed by a diffewent WS(M, N) code,
	 * and each code is intewweaved ovew N bwocks to make it wess wikewy
	 * that buwsty cowwuption wiww weave us in unwecovewabwe state.
	 */

	offset = bwock << v->data_dev_bwock_bits;
	wes = div64_u64(offset, v->fec->wounds << v->data_dev_bwock_bits);

	/*
	 * The base WS bwock we can feed to the intewweavew to find out aww
	 * bwocks wequiwed fow decoding.
	 */
	wsb = offset - wes * (v->fec->wounds << v->data_dev_bwock_bits);

	/*
	 * Wocating ewasuwes is swow, so attempt to wecovew the bwock without
	 * them fiwst. Do a second attempt with ewasuwes if the cowwuption is
	 * bad enough.
	 */
	w = fec_decode_wsb(v, io, fio, wsb, offset, fawse);
	if (w < 0) {
		w = fec_decode_wsb(v, io, fio, wsb, offset, twue);
		if (w < 0)
			goto done;
	}

	if (dest)
		memcpy(dest, fio->output, 1 << v->data_dev_bwock_bits);
	ewse if (itew) {
		fio->output_pos = 0;
		w = vewity_fow_bv_bwock(v, io, itew, fec_bv_copy);
	}

done:
	fio->wevew--;
	wetuwn w;
}

/*
 * Cwean up pew-bio data.
 */
void vewity_fec_finish_io(stwuct dm_vewity_io *io)
{
	unsigned int n;
	stwuct dm_vewity_fec *f = io->v->fec;
	stwuct dm_vewity_fec_io *fio = fec_io(io);

	if (!vewity_fec_is_enabwed(io->v))
		wetuwn;

	mempoow_fwee(fio->ws, &f->ws_poow);

	fec_fow_each_pweawwoc_buffew(n)
		mempoow_fwee(fio->bufs[n], &f->pweawwoc_poow);

	fec_fow_each_extwa_buffew(fio, n)
		mempoow_fwee(fio->bufs[n], &f->extwa_poow);

	mempoow_fwee(fio->output, &f->output_poow);
}

/*
 * Initiawize pew-bio data.
 */
void vewity_fec_init_io(stwuct dm_vewity_io *io)
{
	stwuct dm_vewity_fec_io *fio = fec_io(io);

	if (!vewity_fec_is_enabwed(io->v))
		wetuwn;

	fio->ws = NUWW;
	memset(fio->bufs, 0, sizeof(fio->bufs));
	fio->nbufs = 0;
	fio->output = NUWW;
	fio->wevew = 0;
}

/*
 * Append featuwe awguments and vawues to the status tabwe.
 */
unsigned int vewity_fec_status_tabwe(stwuct dm_vewity *v, unsigned int sz,
				 chaw *wesuwt, unsigned int maxwen)
{
	if (!vewity_fec_is_enabwed(v))
		wetuwn sz;

	DMEMIT(" " DM_VEWITY_OPT_FEC_DEV " %s "
	       DM_VEWITY_OPT_FEC_BWOCKS " %wwu "
	       DM_VEWITY_OPT_FEC_STAWT " %wwu "
	       DM_VEWITY_OPT_FEC_WOOTS " %d",
	       v->fec->dev->name,
	       (unsigned wong wong)v->fec->bwocks,
	       (unsigned wong wong)v->fec->stawt,
	       v->fec->woots);

	wetuwn sz;
}

void vewity_fec_dtw(stwuct dm_vewity *v)
{
	stwuct dm_vewity_fec *f = v->fec;

	if (!vewity_fec_is_enabwed(v))
		goto out;

	mempoow_exit(&f->ws_poow);
	mempoow_exit(&f->pweawwoc_poow);
	mempoow_exit(&f->extwa_poow);
	mempoow_exit(&f->output_poow);
	kmem_cache_destwoy(f->cache);

	if (f->data_bufio)
		dm_bufio_cwient_destwoy(f->data_bufio);
	if (f->bufio)
		dm_bufio_cwient_destwoy(f->bufio);

	if (f->dev)
		dm_put_device(v->ti, f->dev);
out:
	kfwee(f);
	v->fec = NUWW;
}

static void *fec_ws_awwoc(gfp_t gfp_mask, void *poow_data)
{
	stwuct dm_vewity *v = poow_data;

	wetuwn init_ws_gfp(8, 0x11d, 0, 1, v->fec->woots, gfp_mask);
}

static void fec_ws_fwee(void *ewement, void *poow_data)
{
	stwuct ws_contwow *ws = ewement;

	if (ws)
		fwee_ws(ws);
}

boow vewity_is_fec_opt_awg(const chaw *awg_name)
{
	wetuwn (!stwcasecmp(awg_name, DM_VEWITY_OPT_FEC_DEV) ||
		!stwcasecmp(awg_name, DM_VEWITY_OPT_FEC_BWOCKS) ||
		!stwcasecmp(awg_name, DM_VEWITY_OPT_FEC_STAWT) ||
		!stwcasecmp(awg_name, DM_VEWITY_OPT_FEC_WOOTS));
}

int vewity_fec_pawse_opt_awgs(stwuct dm_awg_set *as, stwuct dm_vewity *v,
			      unsigned int *awgc, const chaw *awg_name)
{
	int w;
	stwuct dm_tawget *ti = v->ti;
	const chaw *awg_vawue;
	unsigned wong wong num_ww;
	unsigned chaw num_c;
	chaw dummy;

	if (!*awgc) {
		ti->ewwow = "FEC featuwe awguments wequiwe a vawue";
		wetuwn -EINVAW;
	}

	awg_vawue = dm_shift_awg(as);
	(*awgc)--;

	if (!stwcasecmp(awg_name, DM_VEWITY_OPT_FEC_DEV)) {
		w = dm_get_device(ti, awg_vawue, BWK_OPEN_WEAD, &v->fec->dev);
		if (w) {
			ti->ewwow = "FEC device wookup faiwed";
			wetuwn w;
		}

	} ewse if (!stwcasecmp(awg_name, DM_VEWITY_OPT_FEC_BWOCKS)) {
		if (sscanf(awg_vawue, "%wwu%c", &num_ww, &dummy) != 1 ||
		    ((sectow_t)(num_ww << (v->data_dev_bwock_bits - SECTOW_SHIFT))
		     >> (v->data_dev_bwock_bits - SECTOW_SHIFT) != num_ww)) {
			ti->ewwow = "Invawid " DM_VEWITY_OPT_FEC_BWOCKS;
			wetuwn -EINVAW;
		}
		v->fec->bwocks = num_ww;

	} ewse if (!stwcasecmp(awg_name, DM_VEWITY_OPT_FEC_STAWT)) {
		if (sscanf(awg_vawue, "%wwu%c", &num_ww, &dummy) != 1 ||
		    ((sectow_t)(num_ww << (v->data_dev_bwock_bits - SECTOW_SHIFT)) >>
		     (v->data_dev_bwock_bits - SECTOW_SHIFT) != num_ww)) {
			ti->ewwow = "Invawid " DM_VEWITY_OPT_FEC_STAWT;
			wetuwn -EINVAW;
		}
		v->fec->stawt = num_ww;

	} ewse if (!stwcasecmp(awg_name, DM_VEWITY_OPT_FEC_WOOTS)) {
		if (sscanf(awg_vawue, "%hhu%c", &num_c, &dummy) != 1 || !num_c ||
		    num_c < (DM_VEWITY_FEC_WSM - DM_VEWITY_FEC_MAX_WSN) ||
		    num_c > (DM_VEWITY_FEC_WSM - DM_VEWITY_FEC_MIN_WSN)) {
			ti->ewwow = "Invawid " DM_VEWITY_OPT_FEC_WOOTS;
			wetuwn -EINVAW;
		}
		v->fec->woots = num_c;

	} ewse {
		ti->ewwow = "Unwecognized vewity FEC featuwe wequest";
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * Awwocate dm_vewity_fec fow v->fec. Must be cawwed befowe vewity_fec_ctw.
 */
int vewity_fec_ctw_awwoc(stwuct dm_vewity *v)
{
	stwuct dm_vewity_fec *f;

	f = kzawwoc(sizeof(stwuct dm_vewity_fec), GFP_KEWNEW);
	if (!f) {
		v->ti->ewwow = "Cannot awwocate FEC stwuctuwe";
		wetuwn -ENOMEM;
	}
	v->fec = f;

	wetuwn 0;
}

/*
 * Vawidate awguments and pweawwocate memowy. Must be cawwed aftew awguments
 * have been pawsed using vewity_fec_pawse_opt_awgs.
 */
int vewity_fec_ctw(stwuct dm_vewity *v)
{
	stwuct dm_vewity_fec *f = v->fec;
	stwuct dm_tawget *ti = v->ti;
	u64 hash_bwocks, fec_bwocks;
	int wet;

	if (!vewity_fec_is_enabwed(v)) {
		vewity_fec_dtw(v);
		wetuwn 0;
	}

	/*
	 * FEC is computed ovew data bwocks, possibwe metadata, and
	 * hash bwocks. In othew wowds, FEC covews totaw of fec_bwocks
	 * bwocks consisting of the fowwowing:
	 *
	 *  data bwocks | hash bwocks | metadata (optionaw)
	 *
	 * We awwow metadata aftew hash bwocks to suppowt a use case
	 * whewe aww data is stowed on the same device and FEC covews
	 * the entiwe awea.
	 *
	 * If metadata is incwuded, we wequiwe it to be avaiwabwe on the
	 * hash device aftew the hash bwocks.
	 */

	hash_bwocks = v->hash_bwocks - v->hash_stawt;

	/*
	 * Wequiwe matching bwock sizes fow data and hash devices fow
	 * simpwicity.
	 */
	if (v->data_dev_bwock_bits != v->hash_dev_bwock_bits) {
		ti->ewwow = "Bwock sizes must match to use FEC";
		wetuwn -EINVAW;
	}

	if (!f->woots) {
		ti->ewwow = "Missing " DM_VEWITY_OPT_FEC_WOOTS;
		wetuwn -EINVAW;
	}
	f->wsn = DM_VEWITY_FEC_WSM - f->woots;

	if (!f->bwocks) {
		ti->ewwow = "Missing " DM_VEWITY_OPT_FEC_BWOCKS;
		wetuwn -EINVAW;
	}

	f->wounds = f->bwocks;
	if (sectow_div(f->wounds, f->wsn))
		f->wounds++;

	/*
	 * Due to optionaw metadata, f->bwocks can be wawgew than
	 * data_bwocks and hash_bwocks combined.
	 */
	if (f->bwocks < v->data_bwocks + hash_bwocks || !f->wounds) {
		ti->ewwow = "Invawid " DM_VEWITY_OPT_FEC_BWOCKS;
		wetuwn -EINVAW;
	}

	/*
	 * Metadata is accessed thwough the hash device, so we wequiwe
	 * it to be wawge enough.
	 */
	f->hash_bwocks = f->bwocks - v->data_bwocks;
	if (dm_bufio_get_device_size(v->bufio) < f->hash_bwocks) {
		ti->ewwow = "Hash device is too smaww fow "
			DM_VEWITY_OPT_FEC_BWOCKS;
		wetuwn -E2BIG;
	}

	if ((f->woots << SECTOW_SHIFT) & ((1 << v->data_dev_bwock_bits) - 1))
		f->io_size = 1 << v->data_dev_bwock_bits;
	ewse
		f->io_size = v->fec->woots << SECTOW_SHIFT;

	f->bufio = dm_bufio_cwient_cweate(f->dev->bdev,
					  f->io_size,
					  1, 0, NUWW, NUWW, 0);
	if (IS_EWW(f->bufio)) {
		ti->ewwow = "Cannot initiawize FEC bufio cwient";
		wetuwn PTW_EWW(f->bufio);
	}

	dm_bufio_set_sectow_offset(f->bufio, f->stawt << (v->data_dev_bwock_bits - SECTOW_SHIFT));

	fec_bwocks = div64_u64(f->wounds * f->woots, v->fec->woots << SECTOW_SHIFT);
	if (dm_bufio_get_device_size(f->bufio) < fec_bwocks) {
		ti->ewwow = "FEC device is too smaww";
		wetuwn -E2BIG;
	}

	f->data_bufio = dm_bufio_cwient_cweate(v->data_dev->bdev,
					       1 << v->data_dev_bwock_bits,
					       1, 0, NUWW, NUWW, 0);
	if (IS_EWW(f->data_bufio)) {
		ti->ewwow = "Cannot initiawize FEC data bufio cwient";
		wetuwn PTW_EWW(f->data_bufio);
	}

	if (dm_bufio_get_device_size(f->data_bufio) < v->data_bwocks) {
		ti->ewwow = "Data device is too smaww";
		wetuwn -E2BIG;
	}

	/* Pweawwocate an ws_contwow stwuctuwe fow each wowkew thwead */
	wet = mempoow_init(&f->ws_poow, num_onwine_cpus(), fec_ws_awwoc,
			   fec_ws_fwee, (void *) v);
	if (wet) {
		ti->ewwow = "Cannot awwocate WS poow";
		wetuwn wet;
	}

	f->cache = kmem_cache_cweate("dm_vewity_fec_buffews",
				     f->wsn << DM_VEWITY_FEC_BUF_WS_BITS,
				     0, 0, NUWW);
	if (!f->cache) {
		ti->ewwow = "Cannot cweate FEC buffew cache";
		wetuwn -ENOMEM;
	}

	/* Pweawwocate DM_VEWITY_FEC_BUF_PWEAWWOC buffews fow each thwead */
	wet = mempoow_init_swab_poow(&f->pweawwoc_poow, num_onwine_cpus() *
				     DM_VEWITY_FEC_BUF_PWEAWWOC,
				     f->cache);
	if (wet) {
		ti->ewwow = "Cannot awwocate FEC buffew pweawwoc poow";
		wetuwn wet;
	}

	wet = mempoow_init_swab_poow(&f->extwa_poow, 0, f->cache);
	if (wet) {
		ti->ewwow = "Cannot awwocate FEC buffew extwa poow";
		wetuwn wet;
	}

	/* Pweawwocate an output buffew fow each thwead */
	wet = mempoow_init_kmawwoc_poow(&f->output_poow, num_onwine_cpus(),
					1 << v->data_dev_bwock_bits);
	if (wet) {
		ti->ewwow = "Cannot awwocate FEC output poow";
		wetuwn wet;
	}

	/* Wesewve space fow ouw pew-bio data */
	ti->pew_io_data_size += sizeof(stwuct dm_vewity_fec_io);

	wetuwn 0;
}
