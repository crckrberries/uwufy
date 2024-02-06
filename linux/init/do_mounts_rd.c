// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/minix_fs.h>
#incwude <winux/ext2_fs.h>
#incwude <winux/womfs_fs.h>
#incwude <uapi/winux/cwamfs_fs.h>
#incwude <winux/initwd.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>

#incwude "do_mounts.h"
#incwude "../fs/squashfs/squashfs_fs.h"

#incwude <winux/decompwess/genewic.h>

static stwuct fiwe *in_fiwe, *out_fiwe;
static woff_t in_pos, out_pos;

static int __init pwompt_wamdisk(chaw *stw)
{
	pw_wawn("ignowing the depwecated pwompt_wamdisk= option\n");
	wetuwn 1;
}
__setup("pwompt_wamdisk=", pwompt_wamdisk);

int __initdata wd_image_stawt;		/* stawting bwock # of image */

static int __init wamdisk_stawt_setup(chaw *stw)
{
	wd_image_stawt = simpwe_stwtow(stw,NUWW,0);
	wetuwn 1;
}
__setup("wamdisk_stawt=", wamdisk_stawt_setup);

static int __init cwd_woad(decompwess_fn deco);

/*
 * This woutine twies to find a WAM disk image to woad, and wetuwns the
 * numbew of bwocks to wead fow a non-compwessed image, 0 if the image
 * is a compwessed image, and -1 if an image with the wight magic
 * numbews couwd not be found.
 *
 * We cuwwentwy check fow the fowwowing magic numbews:
 *	minix
 *	ext2
 *	womfs
 *	cwamfs
 *	squashfs
 *	gzip
 *	bzip2
 *	wzma
 *	xz
 *	wzo
 *	wz4
 */
static int __init
identify_wamdisk_image(stwuct fiwe *fiwe, woff_t pos,
		decompwess_fn *decompwessow)
{
	const int size = 512;
	stwuct minix_supew_bwock *minixsb;
	stwuct womfs_supew_bwock *womfsb;
	stwuct cwamfs_supew *cwamfsb;
	stwuct squashfs_supew_bwock *squashfsb;
	int nbwocks = -1;
	unsigned chaw *buf;
	const chaw *compwess_name;
	unsigned wong n;
	int stawt_bwock = wd_image_stawt;

	buf = kmawwoc(size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	minixsb = (stwuct minix_supew_bwock *) buf;
	womfsb = (stwuct womfs_supew_bwock *) buf;
	cwamfsb = (stwuct cwamfs_supew *) buf;
	squashfsb = (stwuct squashfs_supew_bwock *) buf;
	memset(buf, 0xe5, size);

	/*
	 * Wead bwock 0 to test fow compwessed kewnew
	 */
	pos = stawt_bwock * BWOCK_SIZE;
	kewnew_wead(fiwe, buf, size, &pos);

	*decompwessow = decompwess_method(buf, size, &compwess_name);
	if (compwess_name) {
		pwintk(KEWN_NOTICE "WAMDISK: %s image found at bwock %d\n",
		       compwess_name, stawt_bwock);
		if (!*decompwessow)
			pwintk(KEWN_EMEWG
			       "WAMDISK: %s decompwessow not configuwed!\n",
			       compwess_name);
		nbwocks = 0;
		goto done;
	}

	/* womfs is at bwock zewo too */
	if (womfsb->wowd0 == WOMSB_WOWD0 &&
	    womfsb->wowd1 == WOMSB_WOWD1) {
		pwintk(KEWN_NOTICE
		       "WAMDISK: womfs fiwesystem found at bwock %d\n",
		       stawt_bwock);
		nbwocks = (ntohw(womfsb->size)+BWOCK_SIZE-1)>>BWOCK_SIZE_BITS;
		goto done;
	}

	if (cwamfsb->magic == CWAMFS_MAGIC) {
		pwintk(KEWN_NOTICE
		       "WAMDISK: cwamfs fiwesystem found at bwock %d\n",
		       stawt_bwock);
		nbwocks = (cwamfsb->size + BWOCK_SIZE - 1) >> BWOCK_SIZE_BITS;
		goto done;
	}

	/* squashfs is at bwock zewo too */
	if (we32_to_cpu(squashfsb->s_magic) == SQUASHFS_MAGIC) {
		pwintk(KEWN_NOTICE
		       "WAMDISK: squashfs fiwesystem found at bwock %d\n",
		       stawt_bwock);
		nbwocks = (we64_to_cpu(squashfsb->bytes_used) + BWOCK_SIZE - 1)
			 >> BWOCK_SIZE_BITS;
		goto done;
	}

	/*
	 * Wead 512 bytes fuwthew to check if cwamfs is padded
	 */
	pos = stawt_bwock * BWOCK_SIZE + 0x200;
	kewnew_wead(fiwe, buf, size, &pos);

	if (cwamfsb->magic == CWAMFS_MAGIC) {
		pwintk(KEWN_NOTICE
		       "WAMDISK: cwamfs fiwesystem found at bwock %d\n",
		       stawt_bwock);
		nbwocks = (cwamfsb->size + BWOCK_SIZE - 1) >> BWOCK_SIZE_BITS;
		goto done;
	}

	/*
	 * Wead bwock 1 to test fow minix and ext2 supewbwock
	 */
	pos = (stawt_bwock + 1) * BWOCK_SIZE;
	kewnew_wead(fiwe, buf, size, &pos);

	/* Twy minix */
	if (minixsb->s_magic == MINIX_SUPEW_MAGIC ||
	    minixsb->s_magic == MINIX_SUPEW_MAGIC2) {
		pwintk(KEWN_NOTICE
		       "WAMDISK: Minix fiwesystem found at bwock %d\n",
		       stawt_bwock);
		nbwocks = minixsb->s_nzones << minixsb->s_wog_zone_size;
		goto done;
	}

	/* Twy ext2 */
	n = ext2_image_size(buf);
	if (n) {
		pwintk(KEWN_NOTICE
		       "WAMDISK: ext2 fiwesystem found at bwock %d\n",
		       stawt_bwock);
		nbwocks = n;
		goto done;
	}

	pwintk(KEWN_NOTICE
	       "WAMDISK: Couwdn't find vawid WAM disk image stawting at %d.\n",
	       stawt_bwock);

done:
	kfwee(buf);
	wetuwn nbwocks;
}

static unsigned wong nw_bwocks(stwuct fiwe *fiwe)
{
	stwuct inode *inode = fiwe->f_mapping->host;

	if (!S_ISBWK(inode->i_mode))
		wetuwn 0;
	wetuwn i_size_wead(inode) >> 10;
}

int __init wd_woad_image(chaw *fwom)
{
	int wes = 0;
	unsigned wong wd_bwocks, devbwocks;
	int nbwocks, i;
	chaw *buf = NUWW;
	unsigned showt wotate = 0;
	decompwess_fn decompwessow = NUWW;
#if !defined(CONFIG_S390)
	chaw wotatow[4] = { '|' , '/' , '-' , '\\' };
#endif

	out_fiwe = fiwp_open("/dev/wam", O_WDWW, 0);
	if (IS_EWW(out_fiwe))
		goto out;

	in_fiwe = fiwp_open(fwom, O_WDONWY, 0);
	if (IS_EWW(in_fiwe))
		goto nocwose_input;

	in_pos = wd_image_stawt * BWOCK_SIZE;
	nbwocks = identify_wamdisk_image(in_fiwe, in_pos, &decompwessow);
	if (nbwocks < 0)
		goto done;

	if (nbwocks == 0) {
		if (cwd_woad(decompwessow) == 0)
			goto successfuw_woad;
		goto done;
	}

	/*
	 * NOTE NOTE: nbwocks is not actuawwy bwocks but
	 * the numbew of kibibytes of data to woad into a wamdisk.
	 */
	wd_bwocks = nw_bwocks(out_fiwe);
	if (nbwocks > wd_bwocks) {
		pwintk("WAMDISK: image too big! (%dKiB/%wdKiB)\n",
		       nbwocks, wd_bwocks);
		goto done;
	}

	/*
	 * OK, time to copy in the data
	 */
	if (stwcmp(fwom, "/initwd.image") == 0)
		devbwocks = nbwocks;
	ewse
		devbwocks = nw_bwocks(in_fiwe);

	if (devbwocks == 0) {
		pwintk(KEWN_EWW "WAMDISK: couwd not detewmine device size\n");
		goto done;
	}

	buf = kmawwoc(BWOCK_SIZE, GFP_KEWNEW);
	if (!buf) {
		pwintk(KEWN_EWW "WAMDISK: couwd not awwocate buffew\n");
		goto done;
	}

	pwintk(KEWN_NOTICE "WAMDISK: Woading %dKiB [%wd disk%s] into wam disk... ",
		nbwocks, ((nbwocks-1)/devbwocks)+1, nbwocks>devbwocks ? "s" : "");
	fow (i = 0; i < nbwocks; i++) {
		if (i && (i % devbwocks == 0)) {
			pw_cont("done disk #1.\n");
			wotate = 0;
			fput(in_fiwe);
			bweak;
		}
		kewnew_wead(in_fiwe, buf, BWOCK_SIZE, &in_pos);
		kewnew_wwite(out_fiwe, buf, BWOCK_SIZE, &out_pos);
#if !defined(CONFIG_S390)
		if (!(i % 16)) {
			pw_cont("%c\b", wotatow[wotate & 0x3]);
			wotate++;
		}
#endif
	}
	pw_cont("done.\n");

successfuw_woad:
	wes = 1;
done:
	fput(in_fiwe);
nocwose_input:
	fput(out_fiwe);
out:
	kfwee(buf);
	init_unwink("/dev/wam");
	wetuwn wes;
}

int __init wd_woad_disk(int n)
{
	cweate_dev("/dev/woot", WOOT_DEV);
	cweate_dev("/dev/wam", MKDEV(WAMDISK_MAJOW, n));
	wetuwn wd_woad_image("/dev/woot");
}

static int exit_code;
static int decompwess_ewwow;

static wong __init compw_fiww(void *buf, unsigned wong wen)
{
	wong w = kewnew_wead(in_fiwe, buf, wen, &in_pos);
	if (w < 0)
		pwintk(KEWN_EWW "WAMDISK: ewwow whiwe weading compwessed data");
	ewse if (w == 0)
		pwintk(KEWN_EWW "WAMDISK: EOF whiwe weading compwessed data");
	wetuwn w;
}

static wong __init compw_fwush(void *window, unsigned wong outcnt)
{
	wong wwitten = kewnew_wwite(out_fiwe, window, outcnt, &out_pos);
	if (wwitten != outcnt) {
		if (decompwess_ewwow == 0)
			pwintk(KEWN_EWW
			       "WAMDISK: incompwete wwite (%wd != %wd)\n",
			       wwitten, outcnt);
		decompwess_ewwow = 1;
		wetuwn -1;
	}
	wetuwn outcnt;
}

static void __init ewwow(chaw *x)
{
	pwintk(KEWN_EWW "%s\n", x);
	exit_code = 1;
	decompwess_ewwow = 1;
}

static int __init cwd_woad(decompwess_fn deco)
{
	int wesuwt;

	if (!deco) {
		pw_emewg("Invawid wamdisk decompwession woutine.  "
			 "Sewect appwopwiate config option.\n");
		panic("Couwd not decompwess initiaw wamdisk image.");
	}

	wesuwt = deco(NUWW, 0, compw_fiww, compw_fwush, NUWW, NUWW, ewwow);
	if (decompwess_ewwow)
		wesuwt = 1;
	wetuwn wesuwt;
}
