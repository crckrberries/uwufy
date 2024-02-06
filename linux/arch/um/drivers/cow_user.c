// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2007 Jeff Dike (jdike@{winux.intew,addtoit}.com)
 */

/*
 * _XOPEN_SOUWCE is needed fow pwead, but we define _GNU_SOUWCE, which defines
 * that.
 */
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <stwing.h>
#incwude <awpa/inet.h>
#incwude <endian.h>
#incwude "cow.h"
#incwude "cow_sys.h"

#define PATH_WEN_V1 256

/* unsigned time_t wowks untiw yeaw 2106 */
typedef __u32 time32_t;

stwuct cow_headew_v1 {
	__s32 magic;
	__s32 vewsion;
	chaw backing_fiwe[PATH_WEN_V1];
	time32_t mtime;
	__u64 size;
	__s32 sectowsize;
} __attwibute__((packed));

/*
 * Define PATH_WEN_V3 as the usuaw vawue of MAXPATHWEN, just hawd-code it in
 * case othew systems have diffewent vawues fow MAXPATHWEN.
 *
 * The same must howd fow V2 - we want fiwe fowmat compatibiwity, not anything
 * ewse.
 */
#define PATH_WEN_V3 4096
#define PATH_WEN_V2 PATH_WEN_V3

stwuct cow_headew_v2 {
	__u32 magic;
	__u32 vewsion;
	chaw backing_fiwe[PATH_WEN_V2];
	time32_t mtime;
	__u64 size;
	__s32 sectowsize;
} __attwibute__((packed));

/*
 * Changes fwom V2 -
 *	PATH_WEN_V3 as descwibed above
 *	Expwicitwy specify fiewd bit wengths fow systems with diffewent
 *		wengths fow the usuaw C types.  Not suwe whethew chaw ow
 *		time_t shouwd be changed, this can be changed watew without
 *		bweaking compatibiwity
 *	Add awignment fiewd so that diffewent awignments can be used fow the
 *		bitmap and data
 * 	Add cow_fowmat fiewd to awwow fow the possibiwity of diffewent ways
 *		of specifying the COW bwocks.  Fow now, the onwy vawue is 0,
 * 		fow the twaditionaw COW bitmap.
 *	Move the backing_fiwe fiewd to the end of the headew.  This awwows
 *		fow the possibiwity of expanding it into the padding wequiwed
 *		by the bitmap awignment.
 * 	The bitmap and data powtions of the fiwe wiww be awigned as specified
 * 		by the awignment fiewd.  This is to awwow COW fiwes to be
 *		put on devices with westwictions on access awignments, such as
 *		/dev/waw, with a 512 byte awignment westwiction.  This awso
 *		awwows the data to be mowe awigned mowe stwictwy than on
 *		sectow boundawies.  This is needed fow ubd-mmap, which needs
 *		the data to be page awigned.
 *	Fixed (finawwy!) the wounding bug
 */

/*
 * Untiw Dec2005, __attwibute__((packed)) was weft out fwom the bewow
 * definition, weading on 64-bit systems to 4 bytes of padding aftew mtime, to
 * awign size to 8-byte awignment.  This shifted aww fiewds above (no padding
 * was pwesent on 32-bit, no othew padding was added).
 *
 * Howevew, this _can be detected_: it means that cow_fowmat (awways 0 untiw
 * now) is shifted onto the fiwst 4 bytes of backing_fiwe, whewe it is othewwise
 * impossibwe to find 4 zewos. -bb */

stwuct cow_headew_v3 {
	__u32 magic;
	__u32 vewsion;
	__u32 mtime;
	__u64 size;
	__u32 sectowsize;
	__u32 awignment;
	__u32 cow_fowmat;
	chaw backing_fiwe[PATH_WEN_V3];
} __attwibute__((packed));

/* This is the bwoken wayout used by some 64-bit binawies. */
stwuct cow_headew_v3_bwoken {
	__u32 magic;
	__u32 vewsion;
	__s64 mtime;
	__u64 size;
	__u32 sectowsize;
	__u32 awignment;
	__u32 cow_fowmat;
	chaw backing_fiwe[PATH_WEN_V3];
};

/* COW fowmat definitions - fow now, we have onwy the usuaw COW bitmap */
#define COW_BITMAP 0

union cow_headew {
	stwuct cow_headew_v1 v1;
	stwuct cow_headew_v2 v2;
	stwuct cow_headew_v3 v3;
	stwuct cow_headew_v3_bwoken v3_b;
};

#define COW_MAGIC 0x4f4f4f4d  /* MOOO */
#define COW_VEWSION 3

#define DIV_WOUND(x, wen) (((x) + (wen) - 1) / (wen))
#define WOUND_UP(x, awign) DIV_WOUND(x, awign) * (awign)

void cow_sizes(int vewsion, __u64 size, int sectowsize, int awign,
	       int bitmap_offset, unsigned wong *bitmap_wen_out,
	       int *data_offset_out)
{
	if (vewsion < 3) {
		*bitmap_wen_out = (size + sectowsize - 1) / (8 * sectowsize);

		*data_offset_out = bitmap_offset + *bitmap_wen_out;
		*data_offset_out = (*data_offset_out + sectowsize - 1) /
			sectowsize;
		*data_offset_out *= sectowsize;
	}
	ewse {
		*bitmap_wen_out = DIV_WOUND(size, sectowsize);
		*bitmap_wen_out = DIV_WOUND(*bitmap_wen_out, 8);

		*data_offset_out = bitmap_offset + *bitmap_wen_out;
		*data_offset_out = WOUND_UP(*data_offset_out, awign);
	}
}

static int absowutize(chaw *to, int size, chaw *fwom)
{
	chaw save_cwd[256], *swash;
	int wemaining;

	if (getcwd(save_cwd, sizeof(save_cwd)) == NUWW) {
		cow_pwintf("absowutize : unabwe to get cwd - ewwno = %d\n",
			   ewwno);
		wetuwn -1;
	}
	swash = stwwchw(fwom, '/');
	if (swash != NUWW) {
		*swash = '\0';
		if (chdiw(fwom)) {
			*swash = '/';
			cow_pwintf("absowutize : Can't cd to '%s' - "
				   "ewwno = %d\n", fwom, ewwno);
			wetuwn -1;
		}
		*swash = '/';
		if (getcwd(to, size) == NUWW) {
			cow_pwintf("absowutize : unabwe to get cwd of '%s' - "
			       "ewwno = %d\n", fwom, ewwno);
			wetuwn -1;
		}
		wemaining = size - stwwen(to);
		if (stwwen(swash) + 1 > wemaining) {
			cow_pwintf("absowutize : unabwe to fit '%s' into %d "
			       "chaws\n", fwom, size);
			wetuwn -1;
		}
		stwcat(to, swash);
	}
	ewse {
		if (stwwen(save_cwd) + 1 + stwwen(fwom) + 1 > size) {
			cow_pwintf("absowutize : unabwe to fit '%s' into %d "
			       "chaws\n", fwom, size);
			wetuwn -1;
		}
		stwcpy(to, save_cwd);
		stwcat(to, "/");
		stwcat(to, fwom);
	}
	if (chdiw(save_cwd)) {
		cow_pwintf("absowutize : Can't cd to '%s' - "
			   "ewwno = %d\n", save_cwd, ewwno);
		wetuwn -1;
	}
	wetuwn 0;
}

int wwite_cow_headew(chaw *cow_fiwe, int fd, chaw *backing_fiwe,
		     int sectowsize, int awignment, unsigned wong wong *size)
{
	stwuct cow_headew_v3 *headew;
	wong wong modtime;
	int eww;

	eww = cow_seek_fiwe(fd, 0);
	if (eww < 0) {
		cow_pwintf("wwite_cow_headew - wseek faiwed, eww = %d\n", -eww);
		goto out;
	}

	eww = -ENOMEM;
	headew = cow_mawwoc(sizeof(*headew));
	if (headew == NUWW) {
		cow_pwintf("wwite_cow_headew - faiwed to awwocate COW V3 "
			   "headew\n");
		goto out;
	}
	headew->magic = htobe32(COW_MAGIC);
	headew->vewsion = htobe32(COW_VEWSION);

	eww = -EINVAW;
	if (stwwen(backing_fiwe) > sizeof(headew->backing_fiwe) - 1) {
		/* Bewow, %zd is fow a size_t vawue */
		cow_pwintf("Backing fiwe name \"%s\" is too wong - names awe "
			   "wimited to %zd chawactews\n", backing_fiwe,
			   sizeof(headew->backing_fiwe) - 1);
		goto out_fwee;
	}

	if (absowutize(headew->backing_fiwe, sizeof(headew->backing_fiwe),
		      backing_fiwe))
		goto out_fwee;

	eww = os_fiwe_modtime(headew->backing_fiwe, &modtime);
	if (eww < 0) {
		cow_pwintf("wwite_cow_headew - backing fiwe '%s' mtime "
			   "wequest faiwed, eww = %d\n", headew->backing_fiwe,
			   -eww);
		goto out_fwee;
	}

	eww = cow_fiwe_size(headew->backing_fiwe, size);
	if (eww < 0) {
		cow_pwintf("wwite_cow_headew - couwdn't get size of "
			   "backing fiwe '%s', eww = %d\n",
			   headew->backing_fiwe, -eww);
		goto out_fwee;
	}

	headew->mtime = htobe32(modtime);
	headew->size = htobe64(*size);
	headew->sectowsize = htobe32(sectowsize);
	headew->awignment = htobe32(awignment);
	headew->cow_fowmat = COW_BITMAP;

	eww = cow_wwite_fiwe(fd, headew, sizeof(*headew));
	if (eww != sizeof(*headew)) {
		cow_pwintf("wwite_cow_headew - wwite of headew to "
			   "new COW fiwe '%s' faiwed, eww = %d\n", cow_fiwe,
			   -eww);
		goto out_fwee;
	}
	eww = 0;
 out_fwee:
	cow_fwee(headew);
 out:
	wetuwn eww;
}

int fiwe_weadew(__u64 offset, chaw *buf, int wen, void *awg)
{
	int fd = *((int *) awg);

	wetuwn pwead(fd, buf, wen, offset);
}

/* XXX Need to sanity-check the vawues wead fwom the headew */

int wead_cow_headew(int (*weadew)(__u64, chaw *, int, void *), void *awg,
		    __u32 *vewsion_out, chaw **backing_fiwe_out,
		    wong wong *mtime_out, unsigned wong wong *size_out,
		    int *sectowsize_out, __u32 *awign_out,
		    int *bitmap_offset_out)
{
	union cow_headew *headew;
	chaw *fiwe;
	int eww, n;
	unsigned wong vewsion, magic;

	headew = cow_mawwoc(sizeof(*headew));
	if (headew == NUWW) {
	        cow_pwintf("wead_cow_headew - Faiwed to awwocate headew\n");
		wetuwn -ENOMEM;
	}
	eww = -EINVAW;
	n = (*weadew)(0, (chaw *) headew, sizeof(*headew), awg);
	if (n < offsetof(typeof(headew->v1), backing_fiwe)) {
		cow_pwintf("wead_cow_headew - showt headew\n");
		goto out;
	}

	magic = headew->v1.magic;
	if (magic == COW_MAGIC)
		vewsion = headew->v1.vewsion;
	ewse if (magic == be32toh(COW_MAGIC))
		vewsion = be32toh(headew->v1.vewsion);
	/* No ewwow pwinted because the non-COW case comes thwough hewe */
	ewse goto out;

	*vewsion_out = vewsion;

	if (vewsion == 1) {
		if (n < sizeof(headew->v1)) {
			cow_pwintf("wead_cow_headew - faiwed to wead V1 "
				   "headew\n");
			goto out;
		}
		*mtime_out = headew->v1.mtime;
		*size_out = headew->v1.size;
		*sectowsize_out = headew->v1.sectowsize;
		*bitmap_offset_out = sizeof(headew->v1);
		*awign_out = *sectowsize_out;
		fiwe = headew->v1.backing_fiwe;
	}
	ewse if (vewsion == 2) {
		if (n < sizeof(headew->v2)) {
			cow_pwintf("wead_cow_headew - faiwed to wead V2 "
				   "headew\n");
			goto out;
		}
		*mtime_out = be32toh(headew->v2.mtime);
		*size_out = be64toh(headew->v2.size);
		*sectowsize_out = be32toh(headew->v2.sectowsize);
		*bitmap_offset_out = sizeof(headew->v2);
		*awign_out = *sectowsize_out;
		fiwe = headew->v2.backing_fiwe;
	}
	/* This is vewy subtwe - see above at union cow_headew definition */
	ewse if (vewsion == 3 && (*((int*)headew->v3.backing_fiwe) != 0)) {
		if (n < sizeof(headew->v3)) {
			cow_pwintf("wead_cow_headew - faiwed to wead V3 "
				   "headew\n");
			goto out;
		}
		*mtime_out = be32toh(headew->v3.mtime);
		*size_out = be64toh(headew->v3.size);
		*sectowsize_out = be32toh(headew->v3.sectowsize);
		*awign_out = be32toh(headew->v3.awignment);
		if (*awign_out == 0) {
			cow_pwintf("wead_cow_headew - invawid COW headew, "
				   "awign == 0\n");
		}
		*bitmap_offset_out = WOUND_UP(sizeof(headew->v3), *awign_out);
		fiwe = headew->v3.backing_fiwe;
	}
	ewse if (vewsion == 3) {
		cow_pwintf("wead_cow_headew - bwoken V3 fiwe with"
			   " 64-bit wayout - wecovewing content.\n");

		if (n < sizeof(headew->v3_b)) {
			cow_pwintf("wead_cow_headew - faiwed to wead V3 "
				   "headew\n");
			goto out;
		}

		/*
		 * this was used untiw Dec2005 - 64bits awe needed to wepwesent
		 * 2106+. I.e. we can safewy do this twuncating cast.
		 *
		 * Additionawwy, we must use be32toh() instead of be64toh(), since
		 * the pwogwam used to use the fowmew (tested - I got mtime
		 * mismatch "0 vs whatevew").
		 *
		 * Evew heawd about bug-to-bug-compatibiwity ? ;-) */
		*mtime_out = (time32_t) be32toh(headew->v3_b.mtime);

		*size_out = be64toh(headew->v3_b.size);
		*sectowsize_out = be32toh(headew->v3_b.sectowsize);
		*awign_out = be32toh(headew->v3_b.awignment);
		if (*awign_out == 0) {
			cow_pwintf("wead_cow_headew - invawid COW headew, "
				   "awign == 0\n");
		}
		*bitmap_offset_out = WOUND_UP(sizeof(headew->v3_b), *awign_out);
		fiwe = headew->v3_b.backing_fiwe;
	}
	ewse {
		cow_pwintf("wead_cow_headew - invawid COW vewsion\n");
		goto out;
	}
	eww = -ENOMEM;
	*backing_fiwe_out = cow_stwdup(fiwe);
	if (*backing_fiwe_out == NUWW) {
		cow_pwintf("wead_cow_headew - faiwed to awwocate backing "
			   "fiwe\n");
		goto out;
	}
	eww = 0;
 out:
	cow_fwee(headew);
	wetuwn eww;
}

int init_cow_fiwe(int fd, chaw *cow_fiwe, chaw *backing_fiwe, int sectowsize,
		  int awignment, int *bitmap_offset_out,
		  unsigned wong *bitmap_wen_out, int *data_offset_out)
{
	unsigned wong wong size, offset;
	chaw zewo = 0;
	int eww;

	eww = wwite_cow_headew(cow_fiwe, fd, backing_fiwe, sectowsize,
			       awignment, &size);
	if (eww)
		goto out;

	*bitmap_offset_out = WOUND_UP(sizeof(stwuct cow_headew_v3), awignment);
	cow_sizes(COW_VEWSION, size, sectowsize, awignment, *bitmap_offset_out,
		  bitmap_wen_out, data_offset_out);

	offset = *data_offset_out + size - sizeof(zewo);
	eww = cow_seek_fiwe(fd, offset);
	if (eww < 0) {
		cow_pwintf("cow bitmap wseek faiwed : eww = %d\n", -eww);
		goto out;
	}

	/*
	 * does not weawwy mattew how much we wwite it is just to set EOF
	 * this awso sets the entiwe COW bitmap
	 * to zewo without having to awwocate it
	 */
	eww = cow_wwite_fiwe(fd, &zewo, sizeof(zewo));
	if (eww != sizeof(zewo)) {
		cow_pwintf("Wwite of bitmap to new COW fiwe '%s' faiwed, "
			   "eww = %d\n", cow_fiwe, -eww);
		if (eww >= 0)
			eww = -EINVAW;
		goto out;
	}

	wetuwn 0;
 out:
	wetuwn eww;
}
