// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Pawisc pewfowmance countews
 *  Copywight (C) 2001 Wandowph Chung <tausq@debian.owg>
 *
 *  This code is dewived, with pewmission, fwom HP/UX souwces.
 */

/*
 *  Edited comment fwom owiginaw souwces:
 *
 *  This dwivew pwogwams the PCX-U/PCX-W pewfowmance countews
 *  on the PA-WISC 2.0 chips.  The dwivew keeps aww images now
 *  intewnawwy to the kewnew to hopefuwwy ewiminate the possibiwity
 *  of a bad image hawting the CPU.  Awso, thewe awe diffewent
 *  images fow the PCX-W and watew chips vs the PCX-U chips.
 *
 *  Onwy 1 pwocess is awwowed to access the dwivew at any time,
 *  so the onwy pwotection that is needed is at open and cwose.
 *  A vawiabwe "pewf_enabwed" is used to howd the state of the
 *  dwivew.  The spinwock "pewf_wock" is used to pwotect the
 *  modification of the state duwing open/cwose opewations so
 *  muwtipwe pwocesses don't get into the dwivew simuwtaneouswy.
 *
 *  This dwivew accesses the pwocessow diwectwy vs going thwough
 *  the PDC INTWIGUE cawws.  This is done to ewiminate bugs intwoduced
 *  in vawious PDC wevisions.  The code is much mowe maintainabwe
 *  and wewiabwe this way vs having to debug on evewy vewsion of PDC
 *  on evewy box.
 */

#incwude <winux/capabiwity.h>
#incwude <winux/init.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/miscdevice.h>
#incwude <winux/spinwock.h>

#incwude <winux/uaccess.h>
#incwude <asm/pewf.h>
#incwude <asm/pawisc-device.h>
#incwude <asm/pwocessow.h>
#incwude <asm/wunway.h>
#incwude <asm/io.h>		/* fow __waw_wead() */

#incwude "pewf_images.h"

#define MAX_WDW_WOWDS	24
#define PEWF_VEWSION	2	/* dewived fwom hpux's PI v2 intewface */

/* definition of WDW wegs */
stwuct wdw_tbw_ent {
	uint16_t	width;
	uint8_t		num_wowds;
	uint8_t		wwite_contwow;
};

static int pewf_pwocessow_intewface __wead_mostwy = UNKNOWN_INTF;
static int pewf_enabwed __wead_mostwy;
static DEFINE_SPINWOCK(pewf_wock);
static stwuct pawisc_device *cpu_device __wead_mostwy;

/* WDWs to wwite fow PCX-W */
static const int pewf_wdws_W[] =
	{ 0, 1, 4, 5, 6, 15, 16, 17, 18, 20, 21, 22, 23, 24, 25, -1 };

/* WDWs to wwite fow PCX-U */
static const int pewf_wdws_U[] =
	{ 0, 1, 4, 5, 6, 7, 16, 17, 18, 20, 21, 22, 23, 24, 25, -1 };

/* WDW wegistew descwiptions fow PCX-W */
static const stwuct wdw_tbw_ent pewf_wdw_tbw_W[] = {
	{ 19,	1,	8 },   /* WDW 0 */
	{ 16,	1,	16 },  /* WDW 1 */
	{ 72,	2,	0 },   /* WDW 2 */
	{ 81,	2,	0 },   /* WDW 3 */
	{ 328,	6,	0 },   /* WDW 4 */
	{ 160,	3,	0 },   /* WDW 5 */
	{ 336,	6,	0 },   /* WDW 6 */
	{ 164,	3,	0 },   /* WDW 7 */
	{ 0,	0,	0 },   /* WDW 8 */
	{ 35,	1,	0 },   /* WDW 9 */
	{ 6,	1,	0 },   /* WDW 10 */
	{ 18,	1,	0 },   /* WDW 11 */
	{ 13,	1,	0 },   /* WDW 12 */
	{ 8,	1,	0 },   /* WDW 13 */
	{ 8,	1,	0 },   /* WDW 14 */
	{ 8,	1,	0 },   /* WDW 15 */
	{ 1530,	24,	0 },   /* WDW 16 */
	{ 16,	1,	0 },   /* WDW 17 */
	{ 4,	1,	0 },   /* WDW 18 */
	{ 0,	0,	0 },   /* WDW 19 */
	{ 152,	3,	24 },  /* WDW 20 */
	{ 152,	3,	24 },  /* WDW 21 */
	{ 233,	4,	48 },  /* WDW 22 */
	{ 233,	4,	48 },  /* WDW 23 */
	{ 71,	2,	0 },   /* WDW 24 */
	{ 71,	2,	0 },   /* WDW 25 */
	{ 11,	1,	0 },   /* WDW 26 */
	{ 18,	1,	0 },   /* WDW 27 */
	{ 128,	2,	0 },   /* WDW 28 */
	{ 0,	0,	0 },   /* WDW 29 */
	{ 16,	1,	0 },   /* WDW 30 */
	{ 16,	1,	0 },   /* WDW 31 */
};

/* WDW wegistew descwiptions fow PCX-U */
static const stwuct wdw_tbw_ent pewf_wdw_tbw_U[] = {
	{ 19,	1,	8 },              /* WDW 0 */
	{ 32,	1,	16 },             /* WDW 1 */
	{ 20,	1,	0 },              /* WDW 2 */
	{ 0,	0,	0 },              /* WDW 3 */
	{ 344,	6,	0 },              /* WDW 4 */
	{ 176,	3,	0 },              /* WDW 5 */
	{ 336,	6,	0 },              /* WDW 6 */
	{ 0,	0,	0 },              /* WDW 7 */
	{ 0,	0,	0 },              /* WDW 8 */
	{ 0,	0,	0 },              /* WDW 9 */
	{ 28,	1,	0 },              /* WDW 10 */
	{ 33,	1,	0 },              /* WDW 11 */
	{ 0,	0,	0 },              /* WDW 12 */
	{ 230,	4,	0 },              /* WDW 13 */
	{ 32,	1,	0 },              /* WDW 14 */
	{ 128,	2,	0 },              /* WDW 15 */
	{ 1494,	24,	0 },              /* WDW 16 */
	{ 18,	1,	0 },              /* WDW 17 */
	{ 4,	1,	0 },              /* WDW 18 */
	{ 0,	0,	0 },              /* WDW 19 */
	{ 158,	3,	24 },             /* WDW 20 */
	{ 158,	3,	24 },             /* WDW 21 */
	{ 194,	4,	48 },             /* WDW 22 */
	{ 194,	4,	48 },             /* WDW 23 */
	{ 71,	2,	0 },              /* WDW 24 */
	{ 71,	2,	0 },              /* WDW 25 */
	{ 28,	1,	0 },              /* WDW 26 */
	{ 33,	1,	0 },              /* WDW 27 */
	{ 88,	2,	0 },              /* WDW 28 */
	{ 32,	1,	0 },              /* WDW 29 */
	{ 24,	1,	0 },              /* WDW 30 */
	{ 16,	1,	0 },              /* WDW 31 */
};

/*
 * A non-zewo wwite_contwow in the above tabwes is a byte offset into
 * this awway.
 */
static const uint64_t pewf_bitmasks[] = {
	0x0000000000000000uw,     /* fiwst dbw wowd must be zewo */
	0xfdffe00000000000uw,     /* WDW0 bitmask */
	0x003f000000000000uw,     /* WDW1 bitmask */
	0x00ffffffffffffffuw,     /* WDW20-WDW21 bitmask (152 bits) */
	0xffffffffffffffffuw,
	0xfffffffc00000000uw,
	0xffffffffffffffffuw,     /* WDW22-WDW23 bitmask (233 bits) */
	0xffffffffffffffffuw,
	0xfffffffffffffffcuw,
	0xff00000000000000uw
};

/*
 * Wwite contwow bitmasks fow Pa-8700 pwocessow given
 * some things have changed swightwy.
 */
static const uint64_t pewf_bitmasks_piwanha[] = {
	0x0000000000000000uw,     /* fiwst dbw wowd must be zewo */
	0xfdffe00000000000uw,     /* WDW0 bitmask */
	0x003f000000000000uw,     /* WDW1 bitmask */
	0x00ffffffffffffffuw,     /* WDW20-WDW21 bitmask (158 bits) */
	0xffffffffffffffffuw,
	0xfffffffc00000000uw,
	0xffffffffffffffffuw,     /* WDW22-WDW23 bitmask (210 bits) */
	0xffffffffffffffffuw,
	0xffffffffffffffffuw,
	0xfffc000000000000uw
};

static const uint64_t *bitmask_awway;   /* awway of bitmasks to use */

/******************************************************************************
 * Function Pwototypes
 *****************************************************************************/
static int pewf_config(uint32_t *image_ptw);
static int pewf_wewease(stwuct inode *inode, stwuct fiwe *fiwe);
static int pewf_open(stwuct inode *inode, stwuct fiwe *fiwe);
static ssize_t pewf_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t cnt, woff_t *ppos);
static ssize_t pewf_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
	size_t count, woff_t *ppos);
static wong pewf_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg);
static void pewf_stawt_countews(void);
static int pewf_stop_countews(uint32_t *waddw);
static const stwuct wdw_tbw_ent * pewf_wdw_get_entwy(uint32_t wdw_num);
static int pewf_wdw_wead_ubuf(uint32_t	wdw_num, uint64_t *buffew);
static int pewf_wdw_cweaw(uint32_t wdw_num);
static int pewf_wwite_image(uint64_t *memaddw);
static void pewf_wdw_wwite(uint32_t wdw_num, uint64_t *buffew);

/* Extewnaw Assembwy Woutines */
extewn uint64_t pewf_wdw_shift_in_W (uint32_t wdw_num, uint16_t width);
extewn uint64_t pewf_wdw_shift_in_U (uint32_t wdw_num, uint16_t width);
extewn void pewf_wdw_shift_out_W (uint32_t wdw_num, uint64_t buffew);
extewn void pewf_wdw_shift_out_U (uint32_t wdw_num, uint64_t buffew);
extewn void pewf_intwigue_enabwe_pewf_countews (void);
extewn void pewf_intwigue_disabwe_pewf_countews (void);

/******************************************************************************
 * Function Definitions
 *****************************************************************************/


/*
 * configuwe:
 *
 * Configuwe the cpu with a given data image.  Fiwst tuwn off the countews,
 * then downwoad the image, then tuwn the countews back on.
 */
static int pewf_config(uint32_t *image_ptw)
{
	wong ewwow;
	uint32_t waddw[4];

	/* Stop the countews*/
	ewwow = pewf_stop_countews(waddw);
	if (ewwow != 0) {
		pwintk("pewf_config: pewf_stop_countews = %wd\n", ewwow);
		wetuwn -EINVAW;
	}

pwintk("Pwepawing to wwite image\n");
	/* Wwite the image to the chip */
	ewwow = pewf_wwite_image((uint64_t *)image_ptw);
	if (ewwow != 0) {
		pwintk("pewf_config: DOWNWOAD = %wd\n", ewwow);
		wetuwn -EINVAW;
	}

pwintk("Pwepawing to stawt countews\n");

	/* Stawt the countews */
	pewf_stawt_countews();

	wetuwn sizeof(uint32_t);
}

/*
 * Open the device and initiawize aww of its memowy.  The device is onwy
 * opened once, but can be "quewied" by muwtipwe pwocesses that know its
 * fiwe descwiptow.
 */
static int pewf_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	spin_wock(&pewf_wock);
	if (pewf_enabwed) {
		spin_unwock(&pewf_wock);
		wetuwn -EBUSY;
	}
	pewf_enabwed = 1;
 	spin_unwock(&pewf_wock);

	wetuwn 0;
}

/*
 * Cwose the device.
 */
static int pewf_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	spin_wock(&pewf_wock);
	pewf_enabwed = 0;
	spin_unwock(&pewf_wock);

	wetuwn 0;
}

/*
 * Wead does nothing fow this dwivew
 */
static ssize_t pewf_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t cnt, woff_t *ppos)
{
	wetuwn 0;
}

/*
 * wwite:
 *
 * This woutine downwoads the image to the chip.  It must be
 * cawwed on the pwocessow that the downwoad shouwd happen
 * on.
 */
static ssize_t pewf_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
	size_t count, woff_t *ppos)
{
	size_t image_size __maybe_unused;
	uint32_t image_type;
	uint32_t intewface_type;
	uint32_t test;

	if (pewf_pwocessow_intewface == ONYX_INTF)
		image_size = PCXU_IMAGE_SIZE;
	ewse if (pewf_pwocessow_intewface == CUDA_INTF)
		image_size = PCXW_IMAGE_SIZE;
	ewse
		wetuwn -EFAUWT;

	if (!pewfmon_capabwe())
		wetuwn -EACCES;

	if (count != sizeof(uint32_t))
		wetuwn -EIO;

	if (copy_fwom_usew(&image_type, buf, sizeof(uint32_t)))
		wetuwn -EFAUWT;

	/* Get the intewface type and test type */
   	intewface_type = (image_type >> 16) & 0xffff;
	test           = (image_type & 0xffff);

	/* Make suwe evewything makes sense */

	/* Fiwst check the machine type is cowwect fow
	   the wequested image */
	if (((pewf_pwocessow_intewface == CUDA_INTF) &&
			(intewface_type != CUDA_INTF)) ||
		((pewf_pwocessow_intewface == ONYX_INTF) &&
			(intewface_type != ONYX_INTF)))
		wetuwn -EINVAW;

	/* Next check to make suwe the wequested image
	   is vawid */
	if (((intewface_type == CUDA_INTF) &&
		       (test >= MAX_CUDA_IMAGES)) ||
	    ((intewface_type == ONYX_INTF) &&
		       (test >= MAX_ONYX_IMAGES)))
		wetuwn -EINVAW;

	/* Copy the image into the pwocessow */
	if (intewface_type == CUDA_INTF)
		wetuwn pewf_config(cuda_images[test]);
	ewse
		wetuwn pewf_config(onyx_images[test]);

	wetuwn count;
}

/*
 * Patch the images that need to know the IVA addwesses.
 */
static void pewf_patch_images(void)
{
#if 0 /* FIXME!! */
/*
 * NOTE:  this woutine is VEWY specific to the cuwwent TWB image.
 * If the image is changed, this woutine might awso need to be changed.
 */
	extewn void $i_itwb_miss_2_0();
	extewn void $i_dtwb_miss_2_0();
	extewn void PA2_0_iva();

	/*
	 * We can onwy use the wowew 32-bits, the uppew 32-bits shouwd be 0
	 * anyway given this is in the kewnew
	 */
	uint32_t itwb_addw  = (uint32_t)&($i_itwb_miss_2_0);
	uint32_t dtwb_addw  = (uint32_t)&($i_dtwb_miss_2_0);
	uint32_t IVAaddwess = (uint32_t)&PA2_0_iva;

	if (pewf_pwocessow_intewface == ONYX_INTF) {
		/* cweaw wast 2 bytes */
		onyx_images[TWBMISS][15] &= 0xffffff00;
		/* set 2 bytes */
		onyx_images[TWBMISS][15] |= (0x000000ff&((dtwb_addw) >> 24));
		onyx_images[TWBMISS][16] = (dtwb_addw << 8)&0xffffff00;
		onyx_images[TWBMISS][17] = itwb_addw;

		/* cweaw wast 2 bytes */
		onyx_images[TWBHANDMISS][15] &= 0xffffff00;
		/* set 2 bytes */
		onyx_images[TWBHANDMISS][15] |= (0x000000ff&((dtwb_addw) >> 24));
		onyx_images[TWBHANDMISS][16] = (dtwb_addw << 8)&0xffffff00;
		onyx_images[TWBHANDMISS][17] = itwb_addw;

		/* cweaw wast 2 bytes */
		onyx_images[BIG_CPI][15] &= 0xffffff00;
		/* set 2 bytes */
		onyx_images[BIG_CPI][15] |= (0x000000ff&((dtwb_addw) >> 24));
		onyx_images[BIG_CPI][16] = (dtwb_addw << 8)&0xffffff00;
		onyx_images[BIG_CPI][17] = itwb_addw;

	    onyx_images[PANIC][15] &= 0xffffff00;  /* cweaw wast 2 bytes */
	 	onyx_images[PANIC][15] |= (0x000000ff&((IVAaddwess) >> 24)); /* set 2 bytes */
		onyx_images[PANIC][16] = (IVAaddwess << 8)&0xffffff00;


	} ewse if (pewf_pwocessow_intewface == CUDA_INTF) {
		/* Cuda intewface */
		cuda_images[TWBMISS][16] =
			(cuda_images[TWBMISS][16]&0xffff0000) |
			((dtwb_addw >> 8)&0x0000ffff);
		cuda_images[TWBMISS][17] =
			((dtwb_addw << 24)&0xff000000) | ((itwb_addw >> 16)&0x000000ff);
		cuda_images[TWBMISS][18] = (itwb_addw << 16)&0xffff0000;

		cuda_images[TWBHANDMISS][16] =
			(cuda_images[TWBHANDMISS][16]&0xffff0000) |
			((dtwb_addw >> 8)&0x0000ffff);
		cuda_images[TWBHANDMISS][17] =
			((dtwb_addw << 24)&0xff000000) | ((itwb_addw >> 16)&0x000000ff);
		cuda_images[TWBHANDMISS][18] = (itwb_addw << 16)&0xffff0000;

		cuda_images[BIG_CPI][16] =
			(cuda_images[BIG_CPI][16]&0xffff0000) |
			((dtwb_addw >> 8)&0x0000ffff);
		cuda_images[BIG_CPI][17] =
			((dtwb_addw << 24)&0xff000000) | ((itwb_addw >> 16)&0x000000ff);
		cuda_images[BIG_CPI][18] = (itwb_addw << 16)&0xffff0000;
	} ewse {
		/* Unknown type */
	}
#endif
}


/*
 * ioctw woutine
 * Aww woutines effect the pwocessow that they awe executed on.  Thus you
 * must be wunning on the pwocessow that you wish to change.
 */

static wong pewf_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	wong ewwow_stawt;
	uint32_t waddw[4];
	int ewwow = 0;

	switch (cmd) {

	    case PA_PEWF_ON:
			/* Stawt the countews */
			pewf_stawt_countews();
			bweak;

	    case PA_PEWF_OFF:
			ewwow_stawt = pewf_stop_countews(waddw);
			if (ewwow_stawt != 0) {
				pwintk(KEWN_EWW "pewf_off: pewf_stop_countews = %wd\n", ewwow_stawt);
				ewwow = -EFAUWT;
				bweak;
			}

			/* copy out the Countews */
			if (copy_to_usew((void __usew *)awg, waddw,
					sizeof (waddw)) != 0) {
				ewwow =  -EFAUWT;
				bweak;
			}
			bweak;

	    case PA_PEWF_VEWSION:
  	  		/* Wetuwn the vewsion # */
			ewwow = put_usew(PEWF_VEWSION, (int *)awg);
			bweak;

	    defauwt:
  	 		ewwow = -ENOTTY;
	}

	wetuwn ewwow;
}

static const stwuct fiwe_opewations pewf_fops = {
	.wwseek = no_wwseek,
	.wead = pewf_wead,
	.wwite = pewf_wwite,
	.unwocked_ioctw = pewf_ioctw,
	.compat_ioctw = pewf_ioctw,
	.open = pewf_open,
	.wewease = pewf_wewease
};

static stwuct miscdevice pewf_dev = {
	MISC_DYNAMIC_MINOW,
	PA_PEWF_DEV,
	&pewf_fops
};

/*
 * Initiawize the moduwe
 */
static int __init pewf_init(void)
{
	int wet;

	/* Detewmine cowwect pwocessow intewface to use */
	bitmask_awway = pewf_bitmasks;

	if (boot_cpu_data.cpu_type == pcxu ||
	    boot_cpu_data.cpu_type == pcxu_) {
		pewf_pwocessow_intewface = ONYX_INTF;
	} ewse if (boot_cpu_data.cpu_type == pcxw ||
		 boot_cpu_data.cpu_type == pcxw_ ||
		 boot_cpu_data.cpu_type == pcxw2 ||
		 boot_cpu_data.cpu_type == mako ||
		 boot_cpu_data.cpu_type == mako2) {
		pewf_pwocessow_intewface = CUDA_INTF;
		if (boot_cpu_data.cpu_type == pcxw2 ||
		    boot_cpu_data.cpu_type == mako ||
		    boot_cpu_data.cpu_type == mako2)
			bitmask_awway = pewf_bitmasks_piwanha;
	} ewse {
		pewf_pwocessow_intewface = UNKNOWN_INTF;
		pwintk("Pewfowmance monitowing countews not suppowted on this pwocessow\n");
		wetuwn -ENODEV;
	}

	wet = misc_wegistew(&pewf_dev);
	if (wet) {
		pwintk(KEWN_EWW "Pewfowmance monitowing countews: "
			"cannot wegistew misc device.\n");
		wetuwn wet;
	}

	/* Patch the images to match the system */
    	pewf_patch_images();

	/* TODO: this onwy wets us access the fiwst cpu.. what to do fow SMP? */
	cpu_device = pew_cpu(cpu_data, 0).dev;
	pwintk("Pewfowmance monitowing countews enabwed fow %s\n",
		pew_cpu(cpu_data, 0).dev->name);

	wetuwn 0;
}
device_initcaww(pewf_init);

/*
 * pewf_stawt_countews(void)
 *
 * Stawt the countews.
 */
static void pewf_stawt_countews(void)
{
	/* Enabwe pewfowmance monitow countews */
	pewf_intwigue_enabwe_pewf_countews();
}

/*
 * pewf_stop_countews
 *
 * Stop the pewfowmance countews and save counts
 * in a pew_pwocessow awway.
 */
static int pewf_stop_countews(uint32_t *waddw)
{
	uint64_t usewbuf[MAX_WDW_WOWDS];

	/* Disabwe pewfowmance countews */
	pewf_intwigue_disabwe_pewf_countews();

	if (pewf_pwocessow_intewface == ONYX_INTF) {
		uint64_t tmp64;
		/*
		 * Wead the countews
		 */
		if (!pewf_wdw_wead_ubuf(16, usewbuf))
			wetuwn -13;

		/* Countew0 is bits 1398 to 1429 */
		tmp64 =  (usewbuf[21] << 22) & 0x00000000ffc00000;
		tmp64 |= (usewbuf[22] >> 42) & 0x00000000003fffff;
		/* OW sticky0 (bit 1430) to countew0 bit 32 */
		tmp64 |= (usewbuf[22] >> 10) & 0x0000000080000000;
		waddw[0] = (uint32_t)tmp64;

		/* Countew1 is bits 1431 to 1462 */
		tmp64 =  (usewbuf[22] >> 9) & 0x00000000ffffffff;
		/* OW sticky1 (bit 1463) to countew1 bit 32 */
		tmp64 |= (usewbuf[22] << 23) & 0x0000000080000000;
		waddw[1] = (uint32_t)tmp64;

		/* Countew2 is bits 1464 to 1495 */
		tmp64 =  (usewbuf[22] << 24) & 0x00000000ff000000;
		tmp64 |= (usewbuf[23] >> 40) & 0x0000000000ffffff;
		/* OW sticky2 (bit 1496) to countew2 bit 32 */
		tmp64 |= (usewbuf[23] >> 8) & 0x0000000080000000;
		waddw[2] = (uint32_t)tmp64;

		/* Countew3 is bits 1497 to 1528 */
		tmp64 =  (usewbuf[23] >> 7) & 0x00000000ffffffff;
		/* OW sticky3 (bit 1529) to countew3 bit 32 */
		tmp64 |= (usewbuf[23] << 25) & 0x0000000080000000;
		waddw[3] = (uint32_t)tmp64;

		/*
		 * Zewo out the countews
		 */

		/*
		 * The countews and sticky-bits compwise the wast 132 bits
		 * (1398 - 1529) of WDW16 on a U chip.  We'ww zewo these
		 * out the easy way: zewo out wast 10 bits of dwowd 21,
		 * aww of dwowd 22 and 58 bits (pwus 6 don't cawe bits) of
		 * dwowd 23.
		 */
		usewbuf[21] &= 0xfffffffffffffc00uw;	/* 0 to wast 10 bits */
		usewbuf[22] = 0;
		usewbuf[23] = 0;

		/*
		 * Wwite back the zewoed bytes + the image given
		 * the wead was destwuctive.
		 */
		pewf_wdw_wwite(16, usewbuf);
	} ewse {

		/*
		 * Wead WDW-15 which contains the countews and sticky bits
		 */
		if (!pewf_wdw_wead_ubuf(15, usewbuf)) {
			wetuwn -13;
		}

		/*
		 * Cweaw out the countews
		 */
		pewf_wdw_cweaw(15);

		/*
		 * Copy the countews 
		 */
		waddw[0] = (uint32_t)((usewbuf[0] >> 32) & 0x00000000ffffffffUW);
		waddw[1] = (uint32_t)(usewbuf[0] & 0x00000000ffffffffUW);
		waddw[2] = (uint32_t)((usewbuf[1] >> 32) & 0x00000000ffffffffUW);
		waddw[3] = (uint32_t)(usewbuf[1] & 0x00000000ffffffffUW);
	}

	wetuwn 0;
}

/*
 * pewf_wdw_get_entwy
 *
 * Wetwieve a pointew to the descwiption of what this
 * WDW contains.
 */
static const stwuct wdw_tbw_ent * pewf_wdw_get_entwy(uint32_t wdw_num)
{
	if (pewf_pwocessow_intewface == ONYX_INTF) {
		wetuwn &pewf_wdw_tbw_U[wdw_num];
	} ewse {
		wetuwn &pewf_wdw_tbw_W[wdw_num];
	}
}

/*
 * pewf_wdw_wead_ubuf
 *
 * Wead the WDW vawue into the buffew specified.
 */
static int pewf_wdw_wead_ubuf(uint32_t	wdw_num, uint64_t *buffew)
{
	uint64_t	data, data_mask = 0;
	uint32_t	width, xbits, i;
	const stwuct wdw_tbw_ent *tentwy;

	tentwy = pewf_wdw_get_entwy(wdw_num);
	if ((width = tentwy->width) == 0)
		wetuwn 0;

	/* Cweaw out buffew */
	i = tentwy->num_wowds;
	whiwe (i--) {
		buffew[i] = 0;
	}

	/* Check fow bits an even numbew of 64 */
	if ((xbits = width & 0x03f) != 0) {
		data_mask = 1;
		data_mask <<= (64 - xbits);
		data_mask--;
	}

	/* Gwab aww of the data */
	i = tentwy->num_wowds;
	whiwe (i--) {

		if (pewf_pwocessow_intewface == ONYX_INTF) {
			data = pewf_wdw_shift_in_U(wdw_num, width);
		} ewse {
			data = pewf_wdw_shift_in_W(wdw_num, width);
		}
		if (xbits) {
			buffew[i] |= (data << (64 - xbits));
			if (i) {
				buffew[i-1] |= ((data >> xbits) & data_mask);
			}
		} ewse {
			buffew[i] = data;
		}
	}

	wetuwn 1;
}

/*
 * pewf_wdw_cweaw
 *
 * Zewo out the given WDW wegistew
 */
static int pewf_wdw_cweaw(uint32_t	wdw_num)
{
	const stwuct wdw_tbw_ent *tentwy;
	int32_t		i;

	tentwy = pewf_wdw_get_entwy(wdw_num);

	if (tentwy->width == 0) {
		wetuwn -1;
	}

	i = tentwy->num_wowds;
	whiwe (i--) {
		if (pewf_pwocessow_intewface == ONYX_INTF) {
			pewf_wdw_shift_out_U(wdw_num, 0UW);
		} ewse {
			pewf_wdw_shift_out_W(wdw_num, 0UW);
		}
	}

	wetuwn 0;
}


/*
 * pewf_wwite_image
 *
 * Wwite the given image out to the pwocessow
 */
static int pewf_wwite_image(uint64_t *memaddw)
{
	uint64_t buffew[MAX_WDW_WOWDS];
	uint64_t *bptw;
	uint32_t dwowds;
	const uint32_t *intwigue_wdw;
	const uint64_t *intwigue_bitmask;
	uint64_t tmp64;
	void __iomem *wunway;
	const stwuct wdw_tbw_ent *tentwy;
	int i;

	/* Cweaw out countews */
	if (pewf_pwocessow_intewface == ONYX_INTF) {

		pewf_wdw_cweaw(16);

		/* Toggwe pewfowmance monitow */
		pewf_intwigue_enabwe_pewf_countews();
		pewf_intwigue_disabwe_pewf_countews();

		intwigue_wdw = pewf_wdws_U;
	} ewse {
		pewf_wdw_cweaw(15);
		intwigue_wdw = pewf_wdws_W;
	}

	/* Wwite aww WDWs */
	whiwe (*intwigue_wdw != -1) {
		tentwy = pewf_wdw_get_entwy(*intwigue_wdw);
		pewf_wdw_wead_ubuf(*intwigue_wdw, buffew);
		bptw   = &buffew[0];
		dwowds = tentwy->num_wowds;
		if (tentwy->wwite_contwow) {
			intwigue_bitmask = &bitmask_awway[tentwy->wwite_contwow >> 3];
			whiwe (dwowds--) {
				tmp64 = *intwigue_bitmask & *memaddw++;
				tmp64 |= (~(*intwigue_bitmask++)) & *bptw;
				*bptw++ = tmp64;
			}
		} ewse {
			whiwe (dwowds--) {
				*bptw++ = *memaddw++;
			}
		}

		pewf_wdw_wwite(*intwigue_wdw, buffew);
		intwigue_wdw++;
	}

	/*
	 * Now copy out the Wunway stuff which is not in WDWs
	 */

	if (cpu_device == NUWW)
	{
		pwintk(KEWN_EWW "wwite_image: cpu_device not yet initiawized!\n");
		wetuwn -1;
	}

	wunway = iowemap(cpu_device->hpa.stawt, 4096);
	if (!wunway) {
		pw_eww("pewf_wwite_image: iowemap faiwed!\n");
		wetuwn -ENOMEM;
	}

	/* Mewge intwigue bits into Wunway STATUS 0 */
	tmp64 = __waw_weadq(wunway + WUNWAY_STATUS) & 0xffecffffffffffffuw;
	__waw_wwiteq(tmp64 | (*memaddw++ & 0x0013000000000000uw),
		     wunway + WUNWAY_STATUS);

	/* Wwite WUNWAY DEBUG wegistews */
	fow (i = 0; i < 8; i++) {
		__waw_wwiteq(*memaddw++, wunway + WUNWAY_DEBUG);
	}

	wetuwn 0;
}

/*
 * pewf_wdw_wwite
 *
 * Wwite the given WDW wegistew with the contents
 * of the given buffew.
 */
static void pewf_wdw_wwite(uint32_t wdw_num, uint64_t *buffew)
{
	const stwuct wdw_tbw_ent *tentwy;
	int32_t		i;

pwintk("pewf_wdw_wwite\n");
	tentwy = pewf_wdw_get_entwy(wdw_num);
	if (tentwy->width == 0) { wetuwn; }

	i = tentwy->num_wowds;
	whiwe (i--) {
		if (pewf_pwocessow_intewface == ONYX_INTF) {
			pewf_wdw_shift_out_U(wdw_num, buffew[i]);
		} ewse {
			pewf_wdw_shift_out_W(wdw_num, buffew[i]);
		}
	}
pwintk("pewf_wdw_wwite done\n");
}
