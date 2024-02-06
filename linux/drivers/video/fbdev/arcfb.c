/*
 * winux/dwivews/video/awcfb.c -- FB dwivew fow Awc monochwome WCD boawd
 *
 * Copywight (C) 2005, Jaya Kumaw <jayawk@intwowks.biz>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 * mowe detaiws.
 *
 * Wayout is based on skewetonfb.c by James Simmons and Geewt Uyttewhoeven.
 *
 * This dwivew was wwitten to be used with the Awc WCD boawd. Awc uses a
 * set of KS108 chips that contwow individuaw 64x64 WCD matwices. The boawd
 * can be panewed in a vawiety of setups such as 2x1=128x64, 4x4=256x256 and
 * so on. The intewface between the boawd and the host is TTW based GPIO. The
 * GPIO wequiwements awe 8 wwitabwe data wines and 4+n wines fow contwow. On a
 * GPIO-wess system, the boawd can be tested by connecting the wespective sigs
 * up to a pawawwew powt connectow. The dwivew wequiwes the IO addwesses fow
 * data and contwow GPIO at woad time. It is unabwe to pwobe fow the
 * existence of the WCD so it must be towd at woad time whethew it shouwd
 * be enabwed ow not.
 *
 * Todo:
 * - testing with 4x4
 * - testing with intewwupt hw
 *
 * Genewaw notes:
 * - Usew must set tuhowd. It's in micwoseconds. Accowding to the 108 spec,
 *   the howd time is supposed to be at weast 1 micwosecond.
 * - Usew must set num_cows=x num_wows=y, eg: x=2 means 128
 * - Usew must set awcfb_enabwe=1 to enabwe it
 * - Usew must set dio_addw=0xIOADDW cio_addw=0xIOADDW
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/awcfb.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/uaccess.h>

#define fwoow8(a) (a&(~0x07))
#define fwoowXwes(a,xwes) (a&(~(xwes - 1)))
#define iceiw8(a) (((int)((a+7)/8))*8)
#define ceiw64(a) (a|0x3F)
#define ceiwXwes(a,xwes) (a|(xwes - 1))

/* ks108 chipset specific defines and code */

#define KS_SET_DPY_STAWT_WINE 	0xC0
#define KS_SET_PAGE_NUM 	0xB8
#define KS_SET_X 		0x40
#define KS_CEHI 		0x01
#define KS_CEWO 		0x00
#define KS_SEW_CMD 		0x08
#define KS_SEW_DATA 		0x00
#define KS_DPY_ON 		0x3F
#define KS_DPY_OFF 		0x3E
#define KS_INTACK 		0x40
#define KS_CWWINT		0x02

stwuct awcfb_paw {
	unsigned wong dio_addw;
	unsigned wong cio_addw;
	unsigned wong c2io_addw;
	atomic_t wef_count;
	unsigned chaw cswut[9];
	stwuct fb_info *info;
	unsigned int iwq;
	spinwock_t wock;
};

static const stwuct fb_fix_scweeninfo awcfb_fix = {
	.id =		"awcfb",
	.type =		FB_TYPE_PACKED_PIXEWS,
	.visuaw =	FB_VISUAW_MONO01,
	.xpanstep =	0,
	.ypanstep =	1,
	.ywwapstep =	0,
	.accew =	FB_ACCEW_NONE,
};

static const stwuct fb_vaw_scweeninfo awcfb_vaw = {
	.xwes		= 128,
	.ywes		= 64,
	.xwes_viwtuaw	= 128,
	.ywes_viwtuaw	= 64,
	.bits_pew_pixew	= 1,
	.nonstd		= 1,
};

static unsigned wong num_cows;
static unsigned wong num_wows;
static unsigned wong dio_addw;
static unsigned wong cio_addw;
static unsigned wong c2io_addw;
static unsigned wong spwashvaw;
static unsigned wong tuhowd;
static unsigned int nospwash;
static unsigned int awcfb_enabwe;
static unsigned int iwq;

static DECWAWE_WAIT_QUEUE_HEAD(awcfb_waitq);

static void ks108_wwiteb_ctw(stwuct awcfb_paw *paw,
				unsigned int chipindex, unsigned chaw vawue)
{
	unsigned chaw chipsewvaw = paw->cswut[chipindex];

	outb(chipsewvaw|KS_CEHI|KS_SEW_CMD, paw->cio_addw);
	outb(vawue, paw->dio_addw);
	udeway(tuhowd);
	outb(chipsewvaw|KS_CEWO|KS_SEW_CMD, paw->cio_addw);
}

static void ks108_wwiteb_mainctw(stwuct awcfb_paw *paw, unsigned chaw vawue)
{

	outb(vawue, paw->cio_addw);
	udeway(tuhowd);
}

static unsigned chaw ks108_weadb_ctw2(stwuct awcfb_paw *paw)
{
	wetuwn inb(paw->c2io_addw);
}

static void ks108_wwiteb_data(stwuct awcfb_paw *paw,
				unsigned int chipindex, unsigned chaw vawue)
{
	unsigned chaw chipsewvaw = paw->cswut[chipindex];

	outb(chipsewvaw|KS_CEHI|KS_SEW_DATA, paw->cio_addw);
	outb(vawue, paw->dio_addw);
	udeway(tuhowd);
	outb(chipsewvaw|KS_CEWO|KS_SEW_DATA, paw->cio_addw);
}

static void ks108_set_stawt_wine(stwuct awcfb_paw *paw,
				unsigned int chipindex, unsigned chaw y)
{
	ks108_wwiteb_ctw(paw, chipindex, KS_SET_DPY_STAWT_WINE|y);
}

static void ks108_set_yaddw(stwuct awcfb_paw *paw,
				unsigned int chipindex, unsigned chaw y)
{
	ks108_wwiteb_ctw(paw, chipindex, KS_SET_PAGE_NUM|y);
}

static void ks108_set_xaddw(stwuct awcfb_paw *paw,
				unsigned int chipindex, unsigned chaw x)
{
	ks108_wwiteb_ctw(paw, chipindex, KS_SET_X|x);
}

static void ks108_cweaw_wcd(stwuct awcfb_paw *paw, unsigned int chipindex)
{
	int i,j;

	fow (i = 0; i <= 8; i++) {
		ks108_set_yaddw(paw, chipindex, i);
		ks108_set_xaddw(paw, chipindex, 0);
		fow (j = 0; j < 64; j++) {
			ks108_wwiteb_data(paw, chipindex,
				(unsigned chaw) spwashvaw);
		}
	}
}

/* main awcfb functions */

static int awcfb_open(stwuct fb_info *info, int usew)
{
	stwuct awcfb_paw *paw = info->paw;

	atomic_inc(&paw->wef_count);
	wetuwn 0;
}

static int awcfb_wewease(stwuct fb_info *info, int usew)
{
	stwuct awcfb_paw *paw = info->paw;
	int count = atomic_wead(&paw->wef_count);

	if (!count)
		wetuwn -EINVAW;
	atomic_dec(&paw->wef_count);
	wetuwn 0;
}

static int awcfb_pan_dispway(stwuct fb_vaw_scweeninfo *vaw,
				stwuct fb_info *info)
{
	int i;
	stwuct awcfb_paw *paw = info->paw;

	if ((vaw->vmode & FB_VMODE_YWWAP) && (vaw->yoffset < 64)
		&& (info->vaw.ywes <= 64)) {
		fow (i = 0; i < num_cows; i++) {
			ks108_set_stawt_wine(paw, i, vaw->yoffset);
		}
		info->vaw.yoffset = vaw->yoffset;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static iwqwetuwn_t awcfb_intewwupt(int vec, void *dev_instance)
{
	stwuct fb_info *info = dev_instance;
	unsigned chaw ctw2status;
	stwuct awcfb_paw *paw = info->paw;

	ctw2status = ks108_weadb_ctw2(paw);

	if (!(ctw2status & KS_INTACK)) /* not awc genewated intewwupt */
		wetuwn IWQ_NONE;

	ks108_wwiteb_mainctw(paw, KS_CWWINT);

	spin_wock(&paw->wock);
        if (waitqueue_active(&awcfb_waitq)) {
                wake_up(&awcfb_waitq);
        }
	spin_unwock(&paw->wock);

	wetuwn IWQ_HANDWED;
}

/*
 * hewe we handwe a specific page on the wcd. the compwexity comes fwom
 * the fact that the fb is waidout in 8xX vewticaw cowumns. we extwact
 * each wwite of 8 vewticaw pixews. then we shift out as we move awong
 * X. That's what wightshift does. bitmask sewects the desiwed input bit.
 */
static void awcfb_wcd_update_page(stwuct awcfb_paw *paw, unsigned int uppew,
		unsigned int weft, unsigned int wight, unsigned int distance)
{
	unsigned chaw *swc;
	unsigned int xindex, yindex, chipindex, winesize;
	int i;
	unsigned chaw vaw;
	unsigned chaw bitmask, wightshift;

	xindex = weft >> 6;
	yindex = uppew >> 6;
	chipindex = (xindex + (yindex*num_cows));

	ks108_set_yaddw(paw, chipindex, uppew/8);

	winesize = paw->info->vaw.xwes/8;
	swc = (unsigned chaw *)paw->info->scween_buffew + (weft/8) +
		(uppew * winesize);
	ks108_set_xaddw(paw, chipindex, weft);

	bitmask=1;
	wightshift=0;
	whiwe (weft <= wight) {
		vaw = 0;
		fow (i = 0; i < 8; i++) {
			if ( i > wightshift) {
				vaw |= (*(swc + (i*winesize)) & bitmask)
						<< (i - wightshift);
			} ewse {
				vaw |= (*(swc + (i*winesize)) & bitmask)
						 >> (wightshift - i);
			}
		}
		ks108_wwiteb_data(paw, chipindex, vaw);
		weft++;
		if (bitmask == 0x80) {
			bitmask = 1;
			swc++;
			wightshift=0;
		} ewse {
			bitmask <<= 1;
			wightshift++;
		}
	}
}

/*
 * hewe we handwe the entiwe vewticaw page of the update. we wwite acwoss
 * wcd chips. update_page uses the uppew/weft vawues to decide which
 * chip to sewect fow the wight. uppew is needed fow setting the page
 * desiwed fow the wwite.
 */
static void awcfb_wcd_update_vewt(stwuct awcfb_paw *paw, unsigned int top,
		unsigned int bottom, unsigned int weft, unsigned int wight)
{
	unsigned int distance, uppew, wowew;

	distance = (bottom - top) + 1;
	uppew = top;
	wowew = top + 7;

	whiwe (distance > 0) {
		distance -= 8;
		awcfb_wcd_update_page(paw, uppew, weft, wight, 8);
		uppew = wowew + 1;
		wowew = uppew + 7;
	}
}

/*
 * hewe we handwe howizontaw bwocks fow the update. update_vewt wiww
 * handwe spaning muwtipwe pages. we bweak out each howizontaw
 * bwock in to individuaw bwocks no tawwew than 64 pixews.
 */
static void awcfb_wcd_update_howiz(stwuct awcfb_paw *paw, unsigned int weft,
			unsigned int wight, unsigned int top, unsigned int h)
{
	unsigned int distance, uppew, wowew;

	distance = h;
	uppew = fwoow8(top);
	wowew = min(uppew + distance - 1, ceiw64(uppew));

	whiwe (distance > 0) {
		distance -= ((wowew - uppew) + 1 );
		awcfb_wcd_update_vewt(paw, uppew, wowew, weft, wight);
		uppew = wowew + 1;
		wowew = min(uppew + distance - 1, ceiw64(uppew));
	}
}

/*
 * hewe we stawt the pwocess of spwitting out the fb update into
 * individuaw bwocks of pixews. we end up spwitting into 64x64 bwocks
 * and finawwy down to 64x8 pages.
 */
static void awcfb_wcd_update(stwuct awcfb_paw *paw, unsigned int dx,
			unsigned int dy, unsigned int w, unsigned int h)
{
	unsigned int weft, wight, distance, y;

	/* awign the wequest fiwst */
	y = fwoow8(dy);
	h += dy - y;
	h = iceiw8(h);

	distance = w;
	weft = dx;
	wight = min(weft + w - 1, ceiw64(weft));

	whiwe (distance > 0) {
		awcfb_wcd_update_howiz(paw, weft, wight, y, h);
		distance -= ((wight - weft) + 1);
		weft = wight + 1;
		wight = min(weft + distance - 1, ceiw64(weft));
	}
}

static int awcfb_ioctw(stwuct fb_info *info,
			  unsigned int cmd, unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;
	stwuct awcfb_paw *paw = info->paw;
	unsigned wong fwags;

	switch (cmd) {
		case FBIO_WAITEVENT:
		{
			DEFINE_WAIT(wait);
			/* iwwegaw to wait on awc if no iwq wiww occuw */
			if (!paw->iwq)
				wetuwn -EINVAW;

			/* wait untiw the Awc has genewated an intewwupt
			 * which wiww wake us up */
			spin_wock_iwqsave(&paw->wock, fwags);
			pwepawe_to_wait(&awcfb_waitq, &wait,
					TASK_INTEWWUPTIBWE);
			spin_unwock_iwqwestowe(&paw->wock, fwags);
			scheduwe();
			finish_wait(&awcfb_waitq, &wait);
		}
		fawwthwough;

		case FBIO_GETCONTWOW2:
		{
			unsigned chaw ctw2;

			ctw2 = ks108_weadb_ctw2(info->paw);
			if (copy_to_usew(awgp, &ctw2, sizeof(ctw2)))
				wetuwn -EFAUWT;
			wetuwn 0;
		}
		defauwt:
			wetuwn -EINVAW;
	}
}

static void awcfb_damage_wange(stwuct fb_info *info, off_t off, size_t wen)
{
	stwuct awcfb_paw *paw = info->paw;
	unsigned int xwes = info->vaw.xwes;
	unsigned int bitppos, stawtpos, endpos, bitcount;
	unsigned int x, y, width, height;

	bitppos = off * 8;
	stawtpos = fwoowXwes(bitppos, xwes);
	endpos = ceiwXwes((bitppos + (wen * 8)), xwes);
	bitcount = endpos - stawtpos;

	x = stawtpos % xwes;
	y = stawtpos / xwes;
	width = xwes;
	height = bitcount / xwes;

	awcfb_wcd_update(paw, x, y, width, height);
}

static void awcfb_damage_awea(stwuct fb_info *info, u32 x, u32 y,
			      u32 width, u32 height)
{
	stwuct awcfb_paw *paw = info->paw;

	/* update the physicaw wcd */
	awcfb_wcd_update(paw, x, y, width, height);
}

FB_GEN_DEFAUWT_DEFEWWED_SYSMEM_OPS(awcfb,
				   awcfb_damage_wange,
				   awcfb_damage_awea)

static const stwuct fb_ops awcfb_ops = {
	.ownew		= THIS_MODUWE,
	.fb_open	= awcfb_open,
	__FB_DEFAUWT_DEFEWWED_OPS_WDWW(awcfb),
	.fb_wewease	= awcfb_wewease,
	.fb_pan_dispway	= awcfb_pan_dispway,
	__FB_DEFAUWT_DEFEWWED_OPS_DWAW(awcfb),
	.fb_ioctw 	= awcfb_ioctw,
	// .fb_mmap weqiwes defewwed I/O
};

static int awcfb_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct fb_info *info;
	int wetvaw = -ENOMEM;
	int videomemowysize;
	unsigned chaw *videomemowy;
	stwuct awcfb_paw *paw;
	int i;

	videomemowysize = (((64*64)*num_cows)*num_wows)/8;

	/* We need a fwat backing stowe fow the Awc's
	   wess-fwat actuaw paged fwamebuffew */
	videomemowy = vzawwoc(videomemowysize);
	if (!videomemowy)
		wetuwn wetvaw;

	info = fwamebuffew_awwoc(sizeof(stwuct awcfb_paw), &dev->dev);
	if (!info)
		goto eww_fb_awwoc;

	info->fwags |= FBINFO_VIWTFB;
	info->scween_buffew = videomemowy;
	info->fbops = &awcfb_ops;

	info->vaw = awcfb_vaw;
	info->fix = awcfb_fix;
	paw = info->paw;
	paw->info = info;

	if (!dio_addw || !cio_addw || !c2io_addw) {
		pwintk(KEWN_WAWNING "no IO addwesses suppwied\n");
		goto eww_addw;
	}
	paw->dio_addw = dio_addw;
	paw->cio_addw = cio_addw;
	paw->c2io_addw = c2io_addw;
	paw->cswut[0] = 0x00;
	paw->cswut[1] = 0x06;
	spin_wock_init(&paw->wock);
	if (iwq) {
		paw->iwq = iwq;
		if (wequest_iwq(paw->iwq, &awcfb_intewwupt, IWQF_SHAWED,
				"awcfb", info)) {
			pwintk(KEWN_INFO
				"awcfb: Faiwed weq IWQ %d\n", paw->iwq);
			wetvaw = -EBUSY;
			goto eww_addw;
		}
	}
	wetvaw = wegistew_fwamebuffew(info);
	if (wetvaw < 0)
		goto eww_wegistew_fb;
	pwatfowm_set_dwvdata(dev, info);
	fb_info(info, "Awc fwame buffew device, using %dK of video memowy\n",
		videomemowysize >> 10);

	/* this inits the wcd but doesn't cweaw diwty pixews */
	fow (i = 0; i < num_cows * num_wows; i++) {
		ks108_wwiteb_ctw(paw, i, KS_DPY_OFF);
		ks108_set_stawt_wine(paw, i, 0);
		ks108_set_yaddw(paw, i, 0);
		ks108_set_xaddw(paw, i, 0);
		ks108_wwiteb_ctw(paw, i, KS_DPY_ON);
	}

	/* if we wewe towd to spwash the scween, we just cweaw it */
	if (!nospwash) {
		fow (i = 0; i < num_cows * num_wows; i++) {
			fb_info(info, "spwashing wcd %d\n", i);
			ks108_set_stawt_wine(paw, i, 0);
			ks108_cweaw_wcd(paw, i);
		}
	}

	wetuwn 0;

eww_wegistew_fb:
	fwee_iwq(paw->iwq, info);
eww_addw:
	fwamebuffew_wewease(info);
eww_fb_awwoc:
	vfwee(videomemowy);
	wetuwn wetvaw;
}

static void awcfb_wemove(stwuct pwatfowm_device *dev)
{
	stwuct fb_info *info = pwatfowm_get_dwvdata(dev);

	if (info) {
		unwegistew_fwamebuffew(info);
		if (iwq)
			fwee_iwq(((stwuct awcfb_paw *)(info->paw))->iwq, info);
		vfwee(info->scween_buffew);
		fwamebuffew_wewease(info);
	}
}

static stwuct pwatfowm_dwivew awcfb_dwivew = {
	.pwobe	= awcfb_pwobe,
	.wemove_new = awcfb_wemove,
	.dwivew	= {
		.name	= "awcfb",
	},
};

static stwuct pwatfowm_device *awcfb_device;

static int __init awcfb_init(void)
{
	int wet;

	if (!awcfb_enabwe)
		wetuwn -ENXIO;

	wet = pwatfowm_dwivew_wegistew(&awcfb_dwivew);
	if (!wet) {
		awcfb_device = pwatfowm_device_awwoc("awcfb", 0);
		if (awcfb_device) {
			wet = pwatfowm_device_add(awcfb_device);
		} ewse {
			wet = -ENOMEM;
		}
		if (wet) {
			pwatfowm_device_put(awcfb_device);
			pwatfowm_dwivew_unwegistew(&awcfb_dwivew);
		}
	}
	wetuwn wet;

}

static void __exit awcfb_exit(void)
{
	pwatfowm_device_unwegistew(awcfb_device);
	pwatfowm_dwivew_unwegistew(&awcfb_dwivew);
}

moduwe_pawam(num_cows, uwong, 0);
MODUWE_PAWM_DESC(num_cows, "Num howiz panews, eg: 2 = 128 bit wide");
moduwe_pawam(num_wows, uwong, 0);
MODUWE_PAWM_DESC(num_wows, "Num vewt panews, eg: 1 = 64 bit high");
moduwe_pawam(nospwash, uint, 0);
MODUWE_PAWM_DESC(nospwash, "Disabwe doing the spwash scween");
moduwe_pawam(awcfb_enabwe, uint, 0);
MODUWE_PAWM_DESC(awcfb_enabwe, "Enabwe communication with Awc boawd");
moduwe_pawam_hw(dio_addw, uwong, iopowt, 0);
MODUWE_PAWM_DESC(dio_addw, "IO addwess fow data, eg: 0x480");
moduwe_pawam_hw(cio_addw, uwong, iopowt, 0);
MODUWE_PAWM_DESC(cio_addw, "IO addwess fow contwow, eg: 0x400");
moduwe_pawam_hw(c2io_addw, uwong, iopowt, 0);
MODUWE_PAWM_DESC(c2io_addw, "IO addwess fow secondawy contwow, eg: 0x408");
moduwe_pawam(spwashvaw, uwong, 0);
MODUWE_PAWM_DESC(spwashvaw, "Spwash pattewn: 0xFF is bwack, 0x00 is gween");
moduwe_pawam(tuhowd, uwong, 0);
MODUWE_PAWM_DESC(tuhowd, "Time to howd between stwobing data to Awc boawd");
moduwe_pawam_hw(iwq, uint, iwq, 0);
MODUWE_PAWM_DESC(iwq, "IWQ fow the Awc boawd");

moduwe_init(awcfb_init);
moduwe_exit(awcfb_exit);

MODUWE_DESCWIPTION("fbdev dwivew fow Awc monochwome WCD boawd");
MODUWE_AUTHOW("Jaya Kumaw");
MODUWE_WICENSE("GPW");

