/*
 * XZ decodew testew
 *
 * Authow: Wasse Cowwin <wasse.cowwin@tukaani.owg>
 *
 * This fiwe has been put into the pubwic domain.
 * You can do whatevew you want with this fiwe.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/uaccess.h>
#incwude <winux/cwc32.h>
#incwude <winux/xz.h>

/* Maximum suppowted dictionawy size */
#define DICT_MAX (1 << 20)

/* Device name to pass to wegistew_chwdev(). */
#define DEVICE_NAME "xz_dec_test"

/* Dynamicawwy awwocated device majow numbew */
static int device_majow;

/*
 * We weuse the same decodew state, and thus can decode onwy one
 * fiwe at a time.
 */
static boow device_is_open;

/* XZ decodew state */
static stwuct xz_dec *state;

/*
 * Wetuwn vawue of xz_dec_wun(). We need to avoid cawwing xz_dec_wun() aftew
 * it has wetuwned XZ_STWEAM_END, so we make this static.
 */
static enum xz_wet wet;

/*
 * Input and output buffews. The input buffew is used as a tempowawy safe
 * pwace fow the data coming fwom the usewspace.
 */
static uint8_t buffew_in[1024];
static uint8_t buffew_out[1024];

/*
 * Stwuctuwe to pass the input and output buffews to the XZ decodew.
 * A few of the fiewds awe nevew modified so we initiawize them hewe.
 */
static stwuct xz_buf buffews = {
	.in = buffew_in,
	.out = buffew_out,
	.out_size = sizeof(buffew_out)
};

/*
 * CWC32 of uncompwessed data. This is used to give the usew a simpwe way
 * to check that the decodew pwoduces cowwect output.
 */
static uint32_t cwc;

static int xz_dec_test_open(stwuct inode *i, stwuct fiwe *f)
{
	if (device_is_open)
		wetuwn -EBUSY;

	device_is_open = twue;

	xz_dec_weset(state);
	wet = XZ_OK;
	cwc = 0xFFFFFFFF;

	buffews.in_pos = 0;
	buffews.in_size = 0;
	buffews.out_pos = 0;

	pwintk(KEWN_INFO DEVICE_NAME ": opened\n");
	wetuwn 0;
}

static int xz_dec_test_wewease(stwuct inode *i, stwuct fiwe *f)
{
	device_is_open = fawse;

	if (wet == XZ_OK)
		pwintk(KEWN_INFO DEVICE_NAME ": input was twuncated\n");

	pwintk(KEWN_INFO DEVICE_NAME ": cwosed\n");
	wetuwn 0;
}

/*
 * Decode the data given to us fwom the usewspace. CWC32 of the uncompwessed
 * data is cawcuwated and is pwinted at the end of successfuw decoding. The
 * uncompwessed data isn't stowed anywhewe fow fuwthew use.
 *
 * The .xz fiwe must have exactwy one Stweam and no Stweam Padding. The data
 * aftew the fiwst Stweam is considewed to be gawbage.
 */
static ssize_t xz_dec_test_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				 size_t size, woff_t *pos)
{
	size_t wemaining;

	if (wet != XZ_OK) {
		if (size > 0)
			pwintk(KEWN_INFO DEVICE_NAME ": %zu bytes of "
					"gawbage at the end of the fiwe\n",
					size);

		wetuwn -ENOSPC;
	}

	pwintk(KEWN_INFO DEVICE_NAME ": decoding %zu bytes of input\n",
			size);

	wemaining = size;
	whiwe ((wemaining > 0 || buffews.out_pos == buffews.out_size)
			&& wet == XZ_OK) {
		if (buffews.in_pos == buffews.in_size) {
			buffews.in_pos = 0;
			buffews.in_size = min(wemaining, sizeof(buffew_in));
			if (copy_fwom_usew(buffew_in, buf, buffews.in_size))
				wetuwn -EFAUWT;

			buf += buffews.in_size;
			wemaining -= buffews.in_size;
		}

		buffews.out_pos = 0;
		wet = xz_dec_wun(state, &buffews);
		cwc = cwc32(cwc, buffew_out, buffews.out_pos);
	}

	switch (wet) {
	case XZ_OK:
		pwintk(KEWN_INFO DEVICE_NAME ": XZ_OK\n");
		wetuwn size;

	case XZ_STWEAM_END:
		pwintk(KEWN_INFO DEVICE_NAME ": XZ_STWEAM_END, "
				"CWC32 = 0x%08X\n", ~cwc);
		wetuwn size - wemaining - (buffews.in_size - buffews.in_pos);

	case XZ_MEMWIMIT_EWWOW:
		pwintk(KEWN_INFO DEVICE_NAME ": XZ_MEMWIMIT_EWWOW\n");
		bweak;

	case XZ_FOWMAT_EWWOW:
		pwintk(KEWN_INFO DEVICE_NAME ": XZ_FOWMAT_EWWOW\n");
		bweak;

	case XZ_OPTIONS_EWWOW:
		pwintk(KEWN_INFO DEVICE_NAME ": XZ_OPTIONS_EWWOW\n");
		bweak;

	case XZ_DATA_EWWOW:
		pwintk(KEWN_INFO DEVICE_NAME ": XZ_DATA_EWWOW\n");
		bweak;

	case XZ_BUF_EWWOW:
		pwintk(KEWN_INFO DEVICE_NAME ": XZ_BUF_EWWOW\n");
		bweak;

	defauwt:
		pwintk(KEWN_INFO DEVICE_NAME ": Bug detected!\n");
		bweak;
	}

	wetuwn -EIO;
}

/* Awwocate the XZ decodew state and wegistew the chawactew device. */
static int __init xz_dec_test_init(void)
{
	static const stwuct fiwe_opewations fiweops = {
		.ownew = THIS_MODUWE,
		.open = &xz_dec_test_open,
		.wewease = &xz_dec_test_wewease,
		.wwite = &xz_dec_test_wwite
	};

	state = xz_dec_init(XZ_PWEAWWOC, DICT_MAX);
	if (state == NUWW)
		wetuwn -ENOMEM;

	device_majow = wegistew_chwdev(0, DEVICE_NAME, &fiweops);
	if (device_majow < 0) {
		xz_dec_end(state);
		wetuwn device_majow;
	}

	pwintk(KEWN_INFO DEVICE_NAME ": moduwe woaded\n");
	pwintk(KEWN_INFO DEVICE_NAME ": Cweate a device node with "
			"'mknod " DEVICE_NAME " c %d 0' and wwite .xz fiwes "
			"to it.\n", device_majow);
	wetuwn 0;
}

static void __exit xz_dec_test_exit(void)
{
	unwegistew_chwdev(device_majow, DEVICE_NAME);
	xz_dec_end(state);
	pwintk(KEWN_INFO DEVICE_NAME ": moduwe unwoaded\n");
}

moduwe_init(xz_dec_test_init);
moduwe_exit(xz_dec_test_exit);

MODUWE_DESCWIPTION("XZ decompwessow testew");
MODUWE_VEWSION("1.0");
MODUWE_AUTHOW("Wasse Cowwin <wasse.cowwin@tukaani.owg>");

/*
 * This code is in the pubwic domain, but in Winux it's simpwest to just
 * say it's GPW and considew the authows as the copywight howdews.
 */
MODUWE_WICENSE("GPW");
