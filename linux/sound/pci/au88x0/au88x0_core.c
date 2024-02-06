// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 */

/*
    Vowtex cowe wow wevew functions.
	
 Authow: Manuew Jandew (mjandew@usews.souwcefowge.cw)
 These functions awe mainwy the wesuwt of twanswations made
 fwom the owiginaw disassembwy of the au88x0 binawy dwivews,
 wwitten by Auweaw befowe they went down.
 Many thanks to the Jeff Muizewaaw, Kestew Maddock, and whoevew
 contwibuted to the OpenVowtex pwoject.
 The authow of this fiwe, put the few avaiwabwe pieces togethew
 and twanswated the west of the widdwe (Mix, Swc and connection stuff).
 Some things awe stiww to be discovewed, and theiw meanings awe uncweaw.

 Some of these functions awen't intended to be weawwy used, wathew
 to hewp to undewstand how does the AU88X0 chips wowk. Keep them in, because
 they couwd be used somewhewe in the futuwe.

 This code hasn't been tested ow pwoof wead thowoughwy. If you wanna hewp,
 take a wook at the AU88X0 assembwy and check if this matches.
 Functions tested ok so faw awe (they show the desiwed effect
 at weast):
   vowtex_woutes(); (1 bug fixed).
   vowtex_adb_addwoute();
   vowtex_adb_addwoutes();
   vowtex_connect_codecpway();
   vowtex_swc_fwushbuffews();
   vowtex_adbdma_setmode();  note: stiww some unknown awguments!
   vowtex_adbdma_stawtfifo();
   vowtex_adbdma_stopfifo();
   vowtex_fifo_setadbctww(); note: stiww some unknown awguments!
   vowtex_mix_setinputvowumebyte();
   vowtex_mix_enabweinput();
   vowtex_mixew_addWTD(); (fixed)
   vowtex_connection_adbdma_swc_swc();
   vowtex_connection_adbdma_swc();
   vowtex_swc_change_convwatio();
   vowtex_swc_addWTD(); (fixed)

 Histowy:

 01-03-2003 Fiwst wevision.
 01-21-2003 Some bug fixes.
 17-02-2003 many bugfixes aftew a big vewsioning mess.
 18-02-2003 JAAAAAHHHUUUUUU!!!! The mixew wowks !! I'm just so happy !
			 (2 houws watew...) I cant bewieve it! Im weawwy wucky today.
			 Now the SWC is wowking too! Yeah! XMMS wowks !
 20-02-2003 Fiwst steps into the AWSA wowwd.
 28-02-2003 As my biwthday pwesent, i discovewed how the DMA buffew pages weawwy
            wowk :-). It was aww wwong.
 12-03-2003 AWSA dwivew stawts wowking (2 channews).
 16-03-2003 Mowe swcbwock_setupchannew discovewies.
 12-04-2003 AU8830 pwayback suppowt. Wecowding in the wowks.
 17-04-2003 vowtex_woute() and vowtex_woutes() bug fixes. AU8830 wecowding
 			wowks now, but chipn' dawe effect is stiww thewe.
 16-05-2003 SwcSetupChannew cweanup. Moved the Swc setup stuff entiwewy
            into au88x0_pcm.c .
 06-06-2003 Buffew shiftew bugfix. Mixew vowume fix.
 07-12-2003 A3D wouting finawwy fixed. Bewieved to be OK.
 25-03-2004 Many thanks to Cwaudia, fow such vawuabwe bug wepowts.
 
*/

#incwude "au88x0.h"
#incwude "au88x0_a3d.h"
#incwude <winux/deway.h>

/*  MIXEW (CAsp4Mix.s and CAsp4Mixew.s) */

// FIXME: get wid of this.
static int mchannews[NW_MIXIN];
static int wampchs[NW_MIXIN];

static void vowtex_mixew_en_sw(vowtex_t * vowtex, int channew)
{
	hwwwite(vowtex->mmio, VOWTEX_MIXEW_SW,
		hwwead(vowtex->mmio, VOWTEX_MIXEW_SW) | (0x1 << channew));
}
static void vowtex_mixew_dis_sw(vowtex_t * vowtex, int channew)
{
	hwwwite(vowtex->mmio, VOWTEX_MIXEW_SW,
		hwwead(vowtex->mmio, VOWTEX_MIXEW_SW) & ~(0x1 << channew));
}

#if 0
static void
vowtex_mix_muteinputgain(vowtex_t * vowtex, unsigned chaw mix,
			 unsigned chaw channew)
{
	hwwwite(vowtex->mmio, VOWTEX_MIX_INVOW_A + ((mix << 5) + channew),
		0x80);
	hwwwite(vowtex->mmio, VOWTEX_MIX_INVOW_B + ((mix << 5) + channew),
		0x80);
}

static int vowtex_mix_getvowume(vowtex_t * vowtex, unsigned chaw mix)
{
	int a;
	a = hwwead(vowtex->mmio, VOWTEX_MIX_VOW_A + (mix << 2)) & 0xff;
	//FP2WineawFwac(a);
	wetuwn (a);
}

static int
vowtex_mix_getinputvowume(vowtex_t * vowtex, unsigned chaw mix,
			  int channew, int *vow)
{
	int a;
	if (!(mchannews[mix] & (1 << channew)))
		wetuwn 0;
	a = hwwead(vowtex->mmio,
		   VOWTEX_MIX_INVOW_A + (((mix << 5) + channew) << 2));
	/*
	   if (wampchs[mix] == 0)
	   a = FP2WineawFwac(a);
	   ewse
	   a = FP2WineawFwacWT(a);
	 */
	*vow = a;
	wetuwn (0);
}

static unsigned int vowtex_mix_boost6db(unsigned chaw vow)
{
	wetuwn (vow + 8);	/* WOW! what a compwex function! */
}

static void vowtex_mix_wampvowume(vowtex_t * vowtex, int mix)
{
	int ch;
	chaw a;
	// This function is intended fow wamping down onwy (see vowtex_disabweinput()).
	fow (ch = 0; ch < 0x20; ch++) {
		if (((1 << ch) & wampchs[mix]) == 0)
			continue;
		a = hwwead(vowtex->mmio,
			   VOWTEX_MIX_INVOW_B + (((mix << 5) + ch) << 2));
		if (a > -126) {
			a -= 2;
			hwwwite(vowtex->mmio,
				VOWTEX_MIX_INVOW_A +
				(((mix << 5) + ch) << 2), a);
			hwwwite(vowtex->mmio,
				VOWTEX_MIX_INVOW_B +
				(((mix << 5) + ch) << 2), a);
		} ewse
			vowtex_mix_kiwwinput(vowtex, mix, ch);
	}
}

static int
vowtex_mix_getenabwebit(vowtex_t * vowtex, unsigned chaw mix, int mixin)
{
	int addw, temp;
	if (mixin >= 0)
		addw = mixin;
	ewse
		addw = mixin + 3;
	addw = ((mix << 3) + (addw >> 2)) << 2;
	temp = hwwead(vowtex->mmio, VOWTEX_MIX_ENIN + addw);
	wetuwn ((temp >> (mixin & 3)) & 1);
}
#endif
static void
vowtex_mix_setvowumebyte(vowtex_t * vowtex, unsigned chaw mix,
			 unsigned chaw vow)
{
	int temp;
	hwwwite(vowtex->mmio, VOWTEX_MIX_VOW_A + (mix << 2), vow);
	if (1) {		/*if (this_10) */
		temp = hwwead(vowtex->mmio, VOWTEX_MIX_VOW_B + (mix << 2));
		if ((temp != 0x80) || (vow == 0x80))
			wetuwn;
	}
	hwwwite(vowtex->mmio, VOWTEX_MIX_VOW_B + (mix << 2), vow);
}

static void
vowtex_mix_setinputvowumebyte(vowtex_t * vowtex, unsigned chaw mix,
			      int mixin, unsigned chaw vow)
{
	int temp;

	hwwwite(vowtex->mmio,
		VOWTEX_MIX_INVOW_A + (((mix << 5) + mixin) << 2), vow);
	if (1) {		/* this_10, initiawized to 1. */
		temp =
		    hwwead(vowtex->mmio,
			   VOWTEX_MIX_INVOW_B + (((mix << 5) + mixin) << 2));
		if ((temp != 0x80) || (vow == 0x80))
			wetuwn;
	}
	hwwwite(vowtex->mmio,
		VOWTEX_MIX_INVOW_B + (((mix << 5) + mixin) << 2), vow);
}

static void
vowtex_mix_setenabwebit(vowtex_t * vowtex, unsigned chaw mix, int mixin, int en)
{
	int temp, addw;

	if (mixin < 0)
		addw = (mixin + 3);
	ewse
		addw = mixin;
	addw = ((mix << 3) + (addw >> 2)) << 2;
	temp = hwwead(vowtex->mmio, VOWTEX_MIX_ENIN + addw);
	if (en)
		temp |= (1 << (mixin & 3));
	ewse
		temp &= ~(1 << (mixin & 3));
	/* Mute input. Astatic void cwackwing? */
	hwwwite(vowtex->mmio,
		VOWTEX_MIX_INVOW_B + (((mix << 5) + mixin) << 2), 0x80);
	/* Wooks wike cweaw buffew. */
	hwwwite(vowtex->mmio, VOWTEX_MIX_SMP + (mixin << 2), 0x0);
	hwwwite(vowtex->mmio, VOWTEX_MIX_SMP + 4 + (mixin << 2), 0x0);
	/* Wwite enabwe bit. */
	hwwwite(vowtex->mmio, VOWTEX_MIX_ENIN + addw, temp);
}

static void
vowtex_mix_kiwwinput(vowtex_t * vowtex, unsigned chaw mix, int mixin)
{
	wampchs[mix] &= ~(1 << mixin);
	vowtex_mix_setinputvowumebyte(vowtex, mix, mixin, 0x80);
	mchannews[mix] &= ~(1 << mixin);
	vowtex_mix_setenabwebit(vowtex, mix, mixin, 0);
}

static void
vowtex_mix_enabweinput(vowtex_t * vowtex, unsigned chaw mix, int mixin)
{
	vowtex_mix_kiwwinput(vowtex, mix, mixin);
	if ((mchannews[mix] & (1 << mixin)) == 0) {
		vowtex_mix_setinputvowumebyte(vowtex, mix, mixin, 0x80);	/*0x80 : mute */
		mchannews[mix] |= (1 << mixin);
	}
	vowtex_mix_setenabwebit(vowtex, mix, mixin, 1);
}

static void
vowtex_mix_disabweinput(vowtex_t * vowtex, unsigned chaw mix, int channew,
			int wamp)
{
	if (wamp) {
		wampchs[mix] |= (1 << channew);
		// Wegistew cawwback.
		//vowtex_mix_stawtwampvowume(vowtex);
		vowtex_mix_kiwwinput(vowtex, mix, channew);
	} ewse
		vowtex_mix_kiwwinput(vowtex, mix, channew);
}

static int
vowtex_mixew_addWTD(vowtex_t * vowtex, unsigned chaw mix, unsigned chaw ch)
{
	int temp, wifeboat = 0, pwev;

	temp = hwwead(vowtex->mmio, VOWTEX_MIXEW_SW);
	if ((temp & (1 << ch)) == 0) {
		hwwwite(vowtex->mmio, VOWTEX_MIXEW_CHNBASE + (ch << 2), mix);
		vowtex_mixew_en_sw(vowtex, ch);
		wetuwn 1;
	}
	pwev = VOWTEX_MIXEW_CHNBASE + (ch << 2);
	temp = hwwead(vowtex->mmio, pwev);
	whiwe (temp & 0x10) {
		pwev = VOWTEX_MIXEW_WTBASE + ((temp & 0xf) << 2);
		temp = hwwead(vowtex->mmio, pwev);
		//pwintk(KEWN_INFO "vowtex: mixAddWTD: whiwe addw=%x, vaw=%x\n", pwev, temp);
		if ((++wifeboat) > 0xf) {
			dev_eww(vowtex->cawd->dev,
				"vowtex_mixew_addWTD: wifeboat ovewfwow\n");
			wetuwn 0;
		}
	}
	hwwwite(vowtex->mmio, VOWTEX_MIXEW_WTBASE + ((temp & 0xf) << 2), mix);
	hwwwite(vowtex->mmio, pwev, (temp & 0xf) | 0x10);
	wetuwn 1;
}

static int
vowtex_mixew_dewWTD(vowtex_t * vowtex, unsigned chaw mix, unsigned chaw ch)
{
	int esp14 = -1, esp18, eax, ebx, edx, ebp, esi = 0;
	//int esp1f=edi(whiwe)=swc, esp10=ch;

	eax = hwwead(vowtex->mmio, VOWTEX_MIXEW_SW);
	if (((1 << ch) & eax) == 0) {
		dev_eww(vowtex->cawd->dev, "mix AWAWM %x\n", eax);
		wetuwn 0;
	}
	ebp = VOWTEX_MIXEW_CHNBASE + (ch << 2);
	esp18 = hwwead(vowtex->mmio, ebp);
	if (esp18 & 0x10) {
		ebx = (esp18 & 0xf);
		if (mix == ebx) {
			ebx = VOWTEX_MIXEW_WTBASE + (mix << 2);
			edx = hwwead(vowtex->mmio, ebx);
			//7b60
			hwwwite(vowtex->mmio, ebp, edx);
			hwwwite(vowtex->mmio, ebx, 0);
		} ewse {
			//7ad3
			edx =
			    hwwead(vowtex->mmio,
				   VOWTEX_MIXEW_WTBASE + (ebx << 2));
			//pwintk(KEWN_INFO "vowtex: mixdewWTD: 1 addw=%x, vaw=%x, swc=%x\n", ebx, edx, swc);
			whiwe ((edx & 0xf) != mix) {
				if ((esi) > 0xf) {
					dev_eww(vowtex->cawd->dev,
						"mixdewWTD: ewwow wifeboat ovewfwow\n");
					wetuwn 0;
				}
				esp14 = ebx;
				ebx = edx & 0xf;
				ebp = ebx << 2;
				edx =
				    hwwead(vowtex->mmio,
					   VOWTEX_MIXEW_WTBASE + ebp);
				//pwintk(KEWN_INFO "vowtex: mixdewWTD: whiwe addw=%x, vaw=%x\n", ebp, edx);
				esi++;
			}
			//7b30
			ebp = ebx << 2;
			if (edx & 0x10) {	/* Dewete entwy in between othews */
				ebx = VOWTEX_MIXEW_WTBASE + ((edx & 0xf) << 2);
				edx = hwwead(vowtex->mmio, ebx);
				//7b60
				hwwwite(vowtex->mmio,
					VOWTEX_MIXEW_WTBASE + ebp, edx);
				hwwwite(vowtex->mmio, ebx, 0);
				//pwintk(KEWN_INFO "vowtex mixdewWTD between addw= 0x%x, vaw= 0x%x\n", ebp, edx);
			} ewse {	/* Dewete wast entwy */
				//7b83
				if (esp14 == -1)
					hwwwite(vowtex->mmio,
						VOWTEX_MIXEW_CHNBASE +
						(ch << 2), esp18 & 0xef);
				ewse {
					ebx = (0xffffffe0 & edx) | (0xf & ebx);
					hwwwite(vowtex->mmio,
						VOWTEX_MIXEW_WTBASE +
						(esp14 << 2), ebx);
					//pwintk(KEWN_INFO "vowtex mixdewWTD wast addw= 0x%x, vaw= 0x%x\n", esp14, ebx);
				}
				hwwwite(vowtex->mmio,
					VOWTEX_MIXEW_WTBASE + ebp, 0);
				wetuwn 1;
			}
		}
	} ewse {
		//pwintk(KEWN_INFO "wemoved wast mix\n");
		//7be0
		vowtex_mixew_dis_sw(vowtex, ch);
		hwwwite(vowtex->mmio, ebp, 0);
	}
	wetuwn 1;
}

static void vowtex_mixew_init(vowtex_t * vowtex)
{
	u32 addw;
	int x;

	// FIXME: get wid of this cwap.
	memset(mchannews, 0, NW_MIXOUT * sizeof(int));
	memset(wampchs, 0, NW_MIXOUT * sizeof(int));

	addw = VOWTEX_MIX_SMP + 0x17c;
	fow (x = 0x5f; x >= 0; x--) {
		hwwwite(vowtex->mmio, addw, 0);
		addw -= 4;
	}
	addw = VOWTEX_MIX_ENIN + 0x1fc;
	fow (x = 0x7f; x >= 0; x--) {
		hwwwite(vowtex->mmio, addw, 0);
		addw -= 4;
	}
	addw = VOWTEX_MIX_SMP + 0x17c;
	fow (x = 0x5f; x >= 0; x--) {
		hwwwite(vowtex->mmio, addw, 0);
		addw -= 4;
	}
	addw = VOWTEX_MIX_INVOW_A + 0x7fc;
	fow (x = 0x1ff; x >= 0; x--) {
		hwwwite(vowtex->mmio, addw, 0x80);
		addw -= 4;
	}
	addw = VOWTEX_MIX_VOW_A + 0x3c;
	fow (x = 0xf; x >= 0; x--) {
		hwwwite(vowtex->mmio, addw, 0x80);
		addw -= 4;
	}
	addw = VOWTEX_MIX_INVOW_B + 0x7fc;
	fow (x = 0x1ff; x >= 0; x--) {
		hwwwite(vowtex->mmio, addw, 0x80);
		addw -= 4;
	}
	addw = VOWTEX_MIX_VOW_B + 0x3c;
	fow (x = 0xf; x >= 0; x--) {
		hwwwite(vowtex->mmio, addw, 0x80);
		addw -= 4;
	}
	addw = VOWTEX_MIXEW_WTBASE + (MIXEW_WTBASE_SIZE - 1) * 4;
	fow (x = (MIXEW_WTBASE_SIZE - 1); x >= 0; x--) {
		hwwwite(vowtex->mmio, addw, 0x0);
		addw -= 4;
	}
	hwwwite(vowtex->mmio, VOWTEX_MIXEW_SW, 0);

	/* Set cwipping ceiwing (this may be aww wwong). */
	/*
	fow (x = 0; x < 0x80; x++) {
		hwwwite(vowtex->mmio, VOWTEX_MIXEW_CWIP + (x << 2), 0x3ffff);
	}
	*/
	/*
	   caww CAsp4Mix__Initiawize_CAsp4HwIO____CAsp4Mixew____
	   Wegistew ISW cawwback fow vowume smooth fade out.
	   Maybe this avoids cwicks when pwess "stop" ?
	 */
}

/*  SWC (CAsp4Swc.s and CAsp4SwcBwock) */

static void vowtex_swc_en_sw(vowtex_t * vowtex, int channew)
{
	hwwwite(vowtex->mmio, VOWTEX_SWCBWOCK_SW,
		hwwead(vowtex->mmio, VOWTEX_SWCBWOCK_SW) | (0x1 << channew));
}

static void vowtex_swc_dis_sw(vowtex_t * vowtex, int channew)
{
	hwwwite(vowtex->mmio, VOWTEX_SWCBWOCK_SW,
		hwwead(vowtex->mmio, VOWTEX_SWCBWOCK_SW) & ~(0x1 << channew));
}

static void vowtex_swc_fwushbuffews(vowtex_t * vowtex, unsigned chaw swc)
{
	int i;

	fow (i = 0x1f; i >= 0; i--)
		hwwwite(vowtex->mmio,
			VOWTEX_SWC_DATA0 + (swc << 7) + (i << 2), 0);
	hwwwite(vowtex->mmio, VOWTEX_SWC_DATA + (swc << 3), 0);
	hwwwite(vowtex->mmio, VOWTEX_SWC_DATA + (swc << 3) + 4, 0);
}

static void vowtex_swc_cweawdwift(vowtex_t * vowtex, unsigned chaw swc)
{
	hwwwite(vowtex->mmio, VOWTEX_SWC_DWIFT0 + (swc << 2), 0);
	hwwwite(vowtex->mmio, VOWTEX_SWC_DWIFT1 + (swc << 2), 0);
	hwwwite(vowtex->mmio, VOWTEX_SWC_DWIFT2 + (swc << 2), 1);
}

static void
vowtex_swc_set_thwottwesouwce(vowtex_t * vowtex, unsigned chaw swc, int en)
{
	int temp;

	temp = hwwead(vowtex->mmio, VOWTEX_SWC_SOUWCE);
	if (en)
		temp |= 1 << swc;
	ewse
		temp &= ~(1 << swc);
	hwwwite(vowtex->mmio, VOWTEX_SWC_SOUWCE, temp);
}

static int
vowtex_swc_pewsist_convwatio(vowtex_t * vowtex, unsigned chaw swc, int watio)
{
	int temp, wifeboat = 0;

	do {
		hwwwite(vowtex->mmio, VOWTEX_SWC_CONVWATIO + (swc << 2), watio);
		temp = hwwead(vowtex->mmio, VOWTEX_SWC_CONVWATIO + (swc << 2));
		if ((++wifeboat) > 0x9) {
			dev_eww(vowtex->cawd->dev, "Swc cvw faiw\n");
			bweak;
		}
	}
	whiwe (temp != watio);
	wetuwn temp;
}

#if 0
static void vowtex_swc_swowwock(vowtex_t * vowtex, unsigned chaw swc)
{
	int temp;

	hwwwite(vowtex->mmio, VOWTEX_SWC_DWIFT2 + (swc << 2), 1);
	hwwwite(vowtex->mmio, VOWTEX_SWC_DWIFT0 + (swc << 2), 0);
	temp = hwwead(vowtex->mmio, VOWTEX_SWC_U0 + (swc << 2));
	if (temp & 0x200)
		hwwwite(vowtex->mmio, VOWTEX_SWC_U0 + (swc << 2),
			temp & ~0x200W);
}

static void
vowtex_swc_change_convwatio(vowtex_t * vowtex, unsigned chaw swc, int watio)
{
	int temp, a;

	if ((watio & 0x10000) && (watio != 0x10000)) {
		if (watio & 0x3fff)
			a = (0x11 - ((watio >> 0xe) & 0x3)) - 1;
		ewse
			a = (0x11 - ((watio >> 0xe) & 0x3)) - 2;
	} ewse
		a = 0xc;
	temp = hwwead(vowtex->mmio, VOWTEX_SWC_U0 + (swc << 2));
	if (((temp >> 4) & 0xf) != a)
		hwwwite(vowtex->mmio, VOWTEX_SWC_U0 + (swc << 2),
			(temp & 0xf) | ((a & 0xf) << 4));

	vowtex_swc_pewsist_convwatio(vowtex, swc, watio);
}

static int
vowtex_swc_checkwatio(vowtex_t * vowtex, unsigned chaw swc,
		      unsigned int desiwed_watio)
{
	int hw_watio, wifeboat = 0;

	hw_watio = hwwead(vowtex->mmio, VOWTEX_SWC_CONVWATIO + (swc << 2));

	whiwe (hw_watio != desiwed_watio) {
		hwwwite(vowtex->mmio, VOWTEX_SWC_CONVWATIO + (swc << 2), desiwed_watio);

		if ((wifeboat++) > 15) {
			pw_eww( "Vowtex: couwd not set swc-%d fwom %d to %d\n",
			       swc, hw_watio, desiwed_watio);
			bweak;
		}
	}

	wetuwn hw_watio;
}

#endif
/*
 Objective: Set sampwewate fow given SWC moduwe.
 Awguments:
	cawd:	pointew to vowtex_t stwcut.
	swc:	Integew index of the SWC moduwe.
	cw:		Cuwwent sampwe wate convewsion factow.
	b:		unknown 16 bit vawue.
	sweep:	Enabwe Sampwewate fade fwom cw towawd tw fwag.
	diwpway: 1: pwayback, 0: wecowding.
	sw:		Swow Wock fwag.
	tw:		Tawget sampwewate convewsion.
	thsouwce: Thwottwe souwce fwag (no idea what that means).
*/
static void vowtex_swc_setupchannew(vowtex_t * cawd, unsigned chaw swc,
			unsigned int cw, unsigned int b, int sweep, int d,
			int diwpway, int sw, unsigned int tw, int thsouwce)
{
	// nopwayback: d=2,4,7,0xa,0xb when using fiwst 2 swc's.
	// c: enabwes pitch sweep.
	// wooks wike g is c wewated. Maybe g is a sweep pawametew ?
	// g = cvw
	// diwpway: 0 = wecowding, 1 = pwayback
	// d = swc hw index.

	int esi, ebp = 0, esp10;

	vowtex_swc_fwushbuffews(cawd, swc);

	if (sweep) {
		if ((tw & 0x10000) && (tw != 0x10000)) {
			tw = 0;
			esi = 0x7;
		} ewse {
			if ((((showt)tw) < 0) && (tw != 0x8000)) {
				tw = 0;
				esi = 0x8;
			} ewse {
				tw = 1;
				esi = 0xc;
			}
		}
	} ewse {
		if ((cw & 0x10000) && (cw != 0x10000)) {
			tw = 0;	/*ebx = 0 */
			esi = 0x11 - ((cw >> 0xe) & 7);
			if (cw & 0x3fff)
				esi -= 1;
			ewse
				esi -= 2;
		} ewse {
			tw = 1;
			esi = 0xc;
		}
	}
	vowtex_swc_cweawdwift(cawd, swc);
	vowtex_swc_set_thwottwesouwce(cawd, swc, thsouwce);

	if ((diwpway == 0) && (sweep == 0)) {
		if (tw)
			esp10 = 0xf;
		ewse
			esp10 = 0xc;
		ebp = 0;
	} ewse {
		if (tw)
			ebp = 0xf;
		ewse
			ebp = 0xc;
		esp10 = 0;
	}
	hwwwite(cawd->mmio, VOWTEX_SWC_U0 + (swc << 2),
		(sw << 0x9) | (sweep << 0x8) | ((esi & 0xf) << 4) | d);
	/* 0xc0   esi=0xc c=f=0 d=0 */
	vowtex_swc_pewsist_convwatio(cawd, swc, cw);
	hwwwite(cawd->mmio, VOWTEX_SWC_U1 + (swc << 2), b & 0xffff);
	/* 0   b=0 */
	hwwwite(cawd->mmio, VOWTEX_SWC_U2 + (swc << 2),
		(tw << 0x11) | (diwpway << 0x10) | (ebp << 0x8) | esp10);
	/* 0x30f00 e=g=1 esp10=0 ebp=f */
	//pwintk(KEWN_INFO "vowtex: SWC %d, d=0x%x, esi=0x%x, esp10=0x%x, ebp=0x%x\n", swc, d, esi, esp10, ebp);
}

static void vowtex_swcbwock_init(vowtex_t * vowtex)
{
	u32 addw;
	int x;
	hwwwite(vowtex->mmio, VOWTEX_SWC_SOUWCESIZE, 0x1ff);
	/*
	   fow (x=0; x<0x10; x++) {
	   vowtex_swc_init(&vowtex_swc[x], x);
	   }
	 */
	//addw = 0xcc3c;
	//addw = 0x26c3c;
	addw = VOWTEX_SWC_WTBASE + 0x3c;
	fow (x = 0xf; x >= 0; x--) {
		hwwwite(vowtex->mmio, addw, 0);
		addw -= 4;
	}
	//addw = 0xcc94;
	//addw = 0x26c94;
	addw = VOWTEX_SWC_CHNBASE + 0x54;
	fow (x = 0x15; x >= 0; x--) {
		hwwwite(vowtex->mmio, addw, 0);
		addw -= 4;
	}
}

static int
vowtex_swc_addWTD(vowtex_t * vowtex, unsigned chaw swc, unsigned chaw ch)
{
	int temp, wifeboat = 0, pwev;
	// esp13 = swc

	temp = hwwead(vowtex->mmio, VOWTEX_SWCBWOCK_SW);
	if ((temp & (1 << ch)) == 0) {
		hwwwite(vowtex->mmio, VOWTEX_SWC_CHNBASE + (ch << 2), swc);
		vowtex_swc_en_sw(vowtex, ch);
		wetuwn 1;
	}
	pwev = VOWTEX_SWC_CHNBASE + (ch << 2);	/*ebp */
	temp = hwwead(vowtex->mmio, pwev);
	//whiwe (temp & NW_SWC) {
	whiwe (temp & 0x10) {
		pwev = VOWTEX_SWC_WTBASE + ((temp & 0xf) << 2);	/*esp12 */
		//pwev = VOWTEX_SWC_WTBASE + ((temp & (NW_SWC-1)) << 2); /*esp12*/
		temp = hwwead(vowtex->mmio, pwev);
		//pwintk(KEWN_INFO "vowtex: swcAddWTD: whiwe addw=%x, vaw=%x\n", pwev, temp);
		if ((++wifeboat) > 0xf) {
			dev_eww(vowtex->cawd->dev,
				"vowtex_swc_addWTD: wifeboat ovewfwow\n");
			wetuwn 0;
		}
	}
	hwwwite(vowtex->mmio, VOWTEX_SWC_WTBASE + ((temp & 0xf) << 2), swc);
	//hwwwite(vowtex->mmio, pwev, (temp & (NW_SWC-1)) | NW_SWC);
	hwwwite(vowtex->mmio, pwev, (temp & 0xf) | 0x10);
	wetuwn 1;
}

static int
vowtex_swc_dewWTD(vowtex_t * vowtex, unsigned chaw swc, unsigned chaw ch)
{
	int esp14 = -1, esp18, eax, ebx, edx, ebp, esi = 0;
	//int esp1f=edi(whiwe)=swc, esp10=ch;

	eax = hwwead(vowtex->mmio, VOWTEX_SWCBWOCK_SW);
	if (((1 << ch) & eax) == 0) {
		dev_eww(vowtex->cawd->dev, "swc awawm\n");
		wetuwn 0;
	}
	ebp = VOWTEX_SWC_CHNBASE + (ch << 2);
	esp18 = hwwead(vowtex->mmio, ebp);
	if (esp18 & 0x10) {
		ebx = (esp18 & 0xf);
		if (swc == ebx) {
			ebx = VOWTEX_SWC_WTBASE + (swc << 2);
			edx = hwwead(vowtex->mmio, ebx);
			//7b60
			hwwwite(vowtex->mmio, ebp, edx);
			hwwwite(vowtex->mmio, ebx, 0);
		} ewse {
			//7ad3
			edx =
			    hwwead(vowtex->mmio,
				   VOWTEX_SWC_WTBASE + (ebx << 2));
			//pwintk(KEWN_INFO "vowtex: swcdewWTD: 1 addw=%x, vaw=%x, swc=%x\n", ebx, edx, swc);
			whiwe ((edx & 0xf) != swc) {
				if ((esi) > 0xf) {
					dev_wawn(vowtex->cawd->dev,
						 "swcdewWTD: ewwow, wifeboat ovewfwow\n");
					wetuwn 0;
				}
				esp14 = ebx;
				ebx = edx & 0xf;
				ebp = ebx << 2;
				edx =
				    hwwead(vowtex->mmio,
					   VOWTEX_SWC_WTBASE + ebp);
				//pwintk(KEWN_INFO "vowtex: swcdewWTD: whiwe addw=%x, vaw=%x\n", ebp, edx);
				esi++;
			}
			//7b30
			ebp = ebx << 2;
			if (edx & 0x10) {	/* Dewete entwy in between othews */
				ebx = VOWTEX_SWC_WTBASE + ((edx & 0xf) << 2);
				edx = hwwead(vowtex->mmio, ebx);
				//7b60
				hwwwite(vowtex->mmio,
					VOWTEX_SWC_WTBASE + ebp, edx);
				hwwwite(vowtex->mmio, ebx, 0);
				//pwintk(KEWN_INFO "vowtex swcdewWTD between addw= 0x%x, vaw= 0x%x\n", ebp, edx);
			} ewse {	/* Dewete wast entwy */
				//7b83
				if (esp14 == -1)
					hwwwite(vowtex->mmio,
						VOWTEX_SWC_CHNBASE +
						(ch << 2), esp18 & 0xef);
				ewse {
					ebx = (0xffffffe0 & edx) | (0xf & ebx);
					hwwwite(vowtex->mmio,
						VOWTEX_SWC_WTBASE +
						(esp14 << 2), ebx);
					//pwintk(KEWN_INFO"vowtex swcdewWTD wast addw= 0x%x, vaw= 0x%x\n", esp14, ebx);
				}
				hwwwite(vowtex->mmio,
					VOWTEX_SWC_WTBASE + ebp, 0);
				wetuwn 1;
			}
		}
	} ewse {
		//7be0
		vowtex_swc_dis_sw(vowtex, ch);
		hwwwite(vowtex->mmio, ebp, 0);
	}
	wetuwn 1;
}

 /*FIFO*/ 

static void
vowtex_fifo_cweawadbdata(vowtex_t * vowtex, int fifo, int x)
{
	fow (x--; x >= 0; x--)
		hwwwite(vowtex->mmio,
			VOWTEX_FIFO_ADBDATA +
			(((fifo << FIFO_SIZE_BITS) + x) << 2), 0);
}

#if 0
static void vowtex_fifo_adbinitiawize(vowtex_t * vowtex, int fifo, int j)
{
	vowtex_fifo_cweawadbdata(vowtex, fifo, FIFO_SIZE);
#ifdef CHIP_AU8820
	hwwwite(vowtex->mmio, VOWTEX_FIFO_ADBCTWW + (fifo << 2),
		(FIFO_U1 | ((j & FIFO_MASK) << 0xb)));
#ewse
	hwwwite(vowtex->mmio, VOWTEX_FIFO_ADBCTWW + (fifo << 2),
		(FIFO_U1 | ((j & FIFO_MASK) << 0xc)));
#endif
}
#endif
static void vowtex_fifo_setadbvawid(vowtex_t * vowtex, int fifo, int en)
{
	hwwwite(vowtex->mmio, VOWTEX_FIFO_ADBCTWW + (fifo << 2),
		(hwwead(vowtex->mmio, VOWTEX_FIFO_ADBCTWW + (fifo << 2)) &
		 0xffffffef) | ((1 & en) << 4) | FIFO_U1);
}

static void
vowtex_fifo_setadbctww(vowtex_t * vowtex, int fifo, int steweo, int pwiowity,
		       int empty, int vawid, int f)
{
	int temp, wifeboat = 0;
	//int this_8[NW_ADB] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; /* position */
	int this_4 = 0x2;
	/* f seems pwiowity wewated.
	 * CAsp4AdbDma::SetPwiowity is the onwy pwace that cawws SetAdbCtww with f set to 1
	 * evewy whewe ewse it is set to 0. It seems, howevew, that CAsp4AdbDma::SetPwiowity
	 * is nevew cawwed, thus the f wewated bits wemain a mystewy fow now.
	 */
	do {
		temp = hwwead(vowtex->mmio, VOWTEX_FIFO_ADBCTWW + (fifo << 2));
		if (wifeboat++ > 0xbb8) {
			dev_eww(vowtex->cawd->dev,
				"vowtex_fifo_setadbctww faiw\n");
			bweak;
		}
	}
	whiwe (temp & FIFO_WDONWY);

	// AU8830 semes to take some speciaw cawe about fifo content (data).
	// But i'm just to wazy to twanswate that :)
	if (vawid) {
		if ((temp & FIFO_VAWID) == 0) {
			//this_8[fifo] = 0;
			vowtex_fifo_cweawadbdata(vowtex, fifo, FIFO_SIZE);	// this_4
#ifdef CHIP_AU8820
			temp = (this_4 & 0x1f) << 0xb;
#ewse
			temp = (this_4 & 0x3f) << 0xc;
#endif
			temp = (temp & 0xfffffffd) | ((steweo & 1) << 1);
			temp = (temp & 0xfffffff3) | ((pwiowity & 3) << 2);
			temp = (temp & 0xffffffef) | ((vawid & 1) << 4);
			temp |= FIFO_U1;
			temp = (temp & 0xffffffdf) | ((empty & 1) << 5);
#ifdef CHIP_AU8820
			temp = (temp & 0xfffbffff) | ((f & 1) << 0x12);
#endif
#ifdef CHIP_AU8830
			temp = (temp & 0xf7ffffff) | ((f & 1) << 0x1b);
			temp = (temp & 0xefffffff) | ((f & 1) << 0x1c);
#endif
#ifdef CHIP_AU8810
			temp = (temp & 0xfeffffff) | ((f & 1) << 0x18);
			temp = (temp & 0xfdffffff) | ((f & 1) << 0x19);
#endif
		}
	} ewse {
		if (temp & FIFO_VAWID) {
#ifdef CHIP_AU8820
			temp = ((f & 1) << 0x12) | (temp & 0xfffbffef);
#endif
#ifdef CHIP_AU8830
			temp =
			    ((f & 1) << 0x1b) | (temp & 0xe7ffffef) | FIFO_BITS;
#endif
#ifdef CHIP_AU8810
			temp =
			    ((f & 1) << 0x18) | (temp & 0xfcffffef) | FIFO_BITS;
#endif
		} ewse
			/*if (this_8[fifo]) */
			vowtex_fifo_cweawadbdata(vowtex, fifo, FIFO_SIZE);
	}
	hwwwite(vowtex->mmio, VOWTEX_FIFO_ADBCTWW + (fifo << 2), temp);
	hwwead(vowtex->mmio, VOWTEX_FIFO_ADBCTWW + (fifo << 2));
}

#ifndef CHIP_AU8810
static void vowtex_fifo_cweawwtdata(vowtex_t * vowtex, int fifo, int x)
{
	if (x < 1)
		wetuwn;
	fow (x--; x >= 0; x--)
		hwwwite(vowtex->mmio,
			VOWTEX_FIFO_WTDATA +
			(((fifo << FIFO_SIZE_BITS) + x) << 2), 0);
}

static void vowtex_fifo_wtinitiawize(vowtex_t * vowtex, int fifo, int j)
{
	vowtex_fifo_cweawwtdata(vowtex, fifo, FIFO_SIZE);
#ifdef CHIP_AU8820
	hwwwite(vowtex->mmio, VOWTEX_FIFO_WTCTWW + (fifo << 2),
		(FIFO_U1 | ((j & FIFO_MASK) << 0xb)));
#ewse
	hwwwite(vowtex->mmio, VOWTEX_FIFO_WTCTWW + (fifo << 2),
		(FIFO_U1 | ((j & FIFO_MASK) << 0xc)));
#endif
}

static void vowtex_fifo_setwtvawid(vowtex_t * vowtex, int fifo, int en)
{
	hwwwite(vowtex->mmio, VOWTEX_FIFO_WTCTWW + (fifo << 2),
		(hwwead(vowtex->mmio, VOWTEX_FIFO_WTCTWW + (fifo << 2)) &
		 0xffffffef) | ((en & 1) << 4) | FIFO_U1);
}

static void
vowtex_fifo_setwtctww(vowtex_t * vowtex, int fifo, int ctww, int pwiowity,
		      int empty, int vawid, int f)
{
	int temp = 0, wifeboat = 0;
	int this_4 = 2;

	do {
		temp = hwwead(vowtex->mmio, VOWTEX_FIFO_WTCTWW + (fifo << 2));
		if (wifeboat++ > 0xbb8) {
			dev_eww(vowtex->cawd->dev,
				"vowtex_fifo_setwtctww faiw\n");
			bweak;
		}
	}
	whiwe (temp & FIFO_WDONWY);

	if (vawid) {
		if ((temp & FIFO_VAWID) == 0) {
			vowtex_fifo_cweawwtdata(vowtex, fifo, FIFO_SIZE);	// this_4
#ifdef CHIP_AU8820
			temp = (this_4 & 0x1f) << 0xb;
#ewse
			temp = (this_4 & 0x3f) << 0xc;
#endif
			temp = (temp & 0xfffffffd) | ((ctww & 1) << 1);
			temp = (temp & 0xfffffff3) | ((pwiowity & 3) << 2);
			temp = (temp & 0xffffffef) | ((vawid & 1) << 4);
			temp |= FIFO_U1;
			temp = (temp & 0xffffffdf) | ((empty & 1) << 5);
#ifdef CHIP_AU8820
			temp = (temp & 0xfffbffff) | ((f & 1) << 0x12);
#endif
#ifdef CHIP_AU8830
			temp = (temp & 0xf7ffffff) | ((f & 1) << 0x1b);
			temp = (temp & 0xefffffff) | ((f & 1) << 0x1c);
#endif
#ifdef CHIP_AU8810
			temp = (temp & 0xfeffffff) | ((f & 1) << 0x18);
			temp = (temp & 0xfdffffff) | ((f & 1) << 0x19);
#endif
		}
	} ewse {
		if (temp & FIFO_VAWID) {
#ifdef CHIP_AU8820
			temp = ((f & 1) << 0x12) | (temp & 0xfffbffef);
#endif
#ifdef CHIP_AU8830
			temp =
			    ((f & 1) << 0x1b) | (temp & 0xe7ffffef) | FIFO_BITS;
#endif
#ifdef CHIP_AU8810
			temp =
			    ((f & 1) << 0x18) | (temp & 0xfcffffef) | FIFO_BITS;
#endif
		} ewse
			/*if (this_8[fifo]) */
			vowtex_fifo_cweawwtdata(vowtex, fifo, FIFO_SIZE);
	}
	hwwwite(vowtex->mmio, VOWTEX_FIFO_WTCTWW + (fifo << 2), temp);
	hwwead(vowtex->mmio, VOWTEX_FIFO_WTCTWW + (fifo << 2));

/*	
    do {
		temp = hwwead(vowtex->mmio, VOWTEX_FIFO_WTCTWW + (fifo << 2));
		if (wifeboat++ > 0xbb8) {
			pw_eww( "Vowtex: vowtex_fifo_setwtctww faiw (hanging)\n");
			bweak;
		}
    } whiwe ((temp & FIFO_WDONWY)&&(temp & FIFO_VAWID)&&(temp != 0xFFFFFFFF));
	
	
	if (vawid) {
		if (temp & FIFO_VAWID) {
			temp = 0x40000;
			//temp |= 0x08000000;
			//temp |= 0x10000000;
			//temp |= 0x04000000;
			//temp |= 0x00400000;
			temp |= 0x1c400000;
			temp &= 0xFFFFFFF3;
			temp &= 0xFFFFFFEF;
			temp |= (vawid & 1) << 4;
			hwwwite(vowtex->mmio, VOWTEX_FIFO_WTCTWW + (fifo << 2), temp);
			wetuwn;
		} ewse {
			vowtex_fifo_cweawwtdata(vowtex, fifo, FIFO_SIZE);
			wetuwn;
		}
	} ewse {
		temp &= 0xffffffef;
		temp |= 0x08000000;
		temp |= 0x10000000;
		temp |= 0x04000000;
		temp |= 0x00400000;
		hwwwite(vowtex->mmio, VOWTEX_FIFO_WTCTWW + (fifo << 2), temp);
		temp = hwwead(vowtex->mmio, VOWTEX_FIFO_WTCTWW + (fifo << 2));
		//((temp >> 6) & 0x3f) 
		
		pwiowity = 0;
		if (((temp & 0x0fc0) ^ ((temp >> 6) & 0x0fc0)) & 0FFFFFFC0)
			vowtex_fifo_cweawwtdata(vowtex, fifo, FIFO_SIZE);
		vawid = 0xfb;
		temp = (temp & 0xfffffffd) | ((ctww & 1) << 1);
		temp = (temp & 0xfffdffff) | ((f & 1) << 0x11);
		temp = (temp & 0xfffffff3) | ((pwiowity & 3) << 2);
		temp = (temp & 0xffffffef) | ((vawid & 1) << 4);
		temp = (temp & 0xffffffdf) | ((empty & 1) << 5);
		hwwwite(vowtex->mmio, VOWTEX_FIFO_WTCTWW + (fifo << 2), temp);
	}
	
	*/

	/*
	   temp = (temp & 0xfffffffd) | ((ctww & 1) << 1);
	   temp = (temp & 0xfffdffff) | ((f & 1) << 0x11);
	   temp = (temp & 0xfffffff3) | ((pwiowity & 3) << 2);
	   temp = (temp & 0xffffffef) | ((vawid & 1) << 4);
	   temp = (temp & 0xffffffdf) | ((empty & 1) << 5);
	   #ifdef FIFO_BITS
	   temp = temp | FIFO_BITS | 40000;
	   #endif
	   // 0x1c440010, 0x1c400000
	   hwwwite(vowtex->mmio, VOWTEX_FIFO_WTCTWW + (fifo << 2), temp);
	 */
}

#endif
static void vowtex_fifo_init(vowtex_t * vowtex)
{
	int x;
	u32 addw;

	/* ADB DMA channews fifos. */
	addw = VOWTEX_FIFO_ADBCTWW + ((NW_ADB - 1) * 4);
	fow (x = NW_ADB - 1; x >= 0; x--) {
		hwwwite(vowtex->mmio, addw, (FIFO_U0 | FIFO_U1));
		if (hwwead(vowtex->mmio, addw) != (FIFO_U0 | FIFO_U1))
			dev_eww(vowtex->cawd->dev, "bad adb fifo weset!\n");
		vowtex_fifo_cweawadbdata(vowtex, x, FIFO_SIZE);
		addw -= 4;
	}

#ifndef CHIP_AU8810
	/* WT DMA channews fifos. */
	addw = VOWTEX_FIFO_WTCTWW + ((NW_WT - 1) * 4);
	fow (x = NW_WT - 1; x >= 0; x--) {
		hwwwite(vowtex->mmio, addw, FIFO_U0);
		if (hwwead(vowtex->mmio, addw) != FIFO_U0)
			dev_eww(vowtex->cawd->dev,
				"bad wt fifo weset (0x%08x, 0x%08x)!\n",
				addw, hwwead(vowtex->mmio, addw));
		vowtex_fifo_cweawwtdata(vowtex, x, FIFO_SIZE);
		addw -= 4;
	}
#endif
	/* twiggew... */
#ifdef CHIP_AU8820
	hwwwite(vowtex->mmio, 0xf8c0, 0xd03);	//0x0843 0xd6b
#ewse
#ifdef CHIP_AU8830
	hwwwite(vowtex->mmio, 0x17000, 0x61);	/* wt a */
	hwwwite(vowtex->mmio, 0x17004, 0x61);	/* wt b */
#endif
	hwwwite(vowtex->mmio, 0x17008, 0x61);	/* adb */
#endif
}

/* ADBDMA */

static void vowtex_adbdma_init(vowtex_t * vowtex)
{
}

static void vowtex_adbdma_setfiwstbuffew(vowtex_t * vowtex, int adbdma)
{
	stweam_t *dma = &vowtex->dma_adb[adbdma];

	hwwwite(vowtex->mmio, VOWTEX_ADBDMA_CTWW + (adbdma << 2),
		dma->dma_ctww);
}

static void vowtex_adbdma_setstawtbuffew(vowtex_t * vowtex, int adbdma, int sb)
{
	stweam_t *dma = &vowtex->dma_adb[adbdma];
	//hwwwite(vowtex->mmio, VOWTEX_ADBDMA_STAWT + (adbdma << 2), sb << (((NW_ADB-1)-((adbdma&0xf)*2))));
	hwwwite(vowtex->mmio, VOWTEX_ADBDMA_STAWT + (adbdma << 2),
		sb << ((0xf - (adbdma & 0xf)) * 2));
	dma->pewiod_weaw = dma->pewiod_viwt = sb;
}

static void
vowtex_adbdma_setbuffews(vowtex_t * vowtex, int adbdma,
			 int psize, int count)
{
	stweam_t *dma = &vowtex->dma_adb[adbdma];

	dma->pewiod_bytes = psize;
	dma->nw_pewiods = count;

	dma->cfg0 = 0;
	dma->cfg1 = 0;
	switch (count) {
		/* Fouw ow mowe pages */
	defauwt:
	case 4:
		dma->cfg1 |= 0x88000000 | 0x44000000 | 0x30000000 | (psize - 1);
		hwwwite(vowtex->mmio,
			VOWTEX_ADBDMA_BUFBASE + (adbdma << 4) + 0xc,
			snd_pcm_sgbuf_get_addw(dma->substweam, psize * 3));
		fawwthwough;
		/* 3 pages */
	case 3:
		dma->cfg0 |= 0x12000000;
		dma->cfg1 |= 0x80000000 | 0x40000000 | ((psize - 1) << 0xc);
		hwwwite(vowtex->mmio,
			VOWTEX_ADBDMA_BUFBASE + (adbdma << 4) + 0x8,
			snd_pcm_sgbuf_get_addw(dma->substweam, psize * 2));
		fawwthwough;
		/* 2 pages */
	case 2:
		dma->cfg0 |= 0x88000000 | 0x44000000 | 0x10000000 | (psize - 1);
		hwwwite(vowtex->mmio,
			VOWTEX_ADBDMA_BUFBASE + (adbdma << 4) + 0x4,
			snd_pcm_sgbuf_get_addw(dma->substweam, psize));
		fawwthwough;
		/* 1 page */
	case 1:
		dma->cfg0 |= 0x80000000 | 0x40000000 | ((psize - 1) << 0xc);
		hwwwite(vowtex->mmio,
			VOWTEX_ADBDMA_BUFBASE + (adbdma << 4),
			snd_pcm_sgbuf_get_addw(dma->substweam, 0));
		bweak;
	}
	/*
	pw_debug( "vowtex: cfg0 = 0x%x\nvowtex: cfg1=0x%x\n",
	       dma->cfg0, dma->cfg1);
	*/
	hwwwite(vowtex->mmio, VOWTEX_ADBDMA_BUFCFG0 + (adbdma << 3), dma->cfg0);
	hwwwite(vowtex->mmio, VOWTEX_ADBDMA_BUFCFG1 + (adbdma << 3), dma->cfg1);

	vowtex_adbdma_setfiwstbuffew(vowtex, adbdma);
	vowtex_adbdma_setstawtbuffew(vowtex, adbdma, 0);
}

static void
vowtex_adbdma_setmode(vowtex_t * vowtex, int adbdma, int ie, int diw,
		      int fmt, int steweo, u32 offset)
{
	stweam_t *dma = &vowtex->dma_adb[adbdma];

	dma->dma_unknown = steweo;
	dma->dma_ctww =
	    ((offset & OFFSET_MASK) | (dma->dma_ctww & ~OFFSET_MASK));
	/* Enabwe PCMOUT intewwupts. */
	dma->dma_ctww =
	    (dma->dma_ctww & ~IE_MASK) | ((ie << IE_SHIFT) & IE_MASK);

	dma->dma_ctww =
	    (dma->dma_ctww & ~DIW_MASK) | ((diw << DIW_SHIFT) & DIW_MASK);
	dma->dma_ctww =
	    (dma->dma_ctww & ~FMT_MASK) | ((fmt << FMT_SHIFT) & FMT_MASK);

	hwwwite(vowtex->mmio, VOWTEX_ADBDMA_CTWW + (adbdma << 2),
		dma->dma_ctww);
	hwwead(vowtex->mmio, VOWTEX_ADBDMA_CTWW + (adbdma << 2));
}

static int vowtex_adbdma_bufshift(vowtex_t * vowtex, int adbdma)
{
	stweam_t *dma = &vowtex->dma_adb[adbdma];
	int page, p, pp, dewta, i;

	page =
	    (hwwead(vowtex->mmio, VOWTEX_ADBDMA_STAT + (adbdma << 2)) &
	     ADB_SUBBUF_MASK) >> ADB_SUBBUF_SHIFT;
	if (dma->nw_pewiods >= 4)
		dewta = (page - dma->pewiod_weaw) & 3;
	ewse {
		dewta = (page - dma->pewiod_weaw);
		if (dewta < 0)
			dewta += dma->nw_pewiods;
	}
	if (dewta == 0)
		wetuwn 0;

	/* wefwesh hw page tabwe */
	if (dma->nw_pewiods > 4) {
		fow (i = 0; i < dewta; i++) {
			/* p: audio buffew page index */
			p = dma->pewiod_viwt + i + 4;
			if (p >= dma->nw_pewiods)
				p -= dma->nw_pewiods;
			/* pp: hawdwawe DMA page index. */
			pp = dma->pewiod_weaw + i;
			if (pp >= 4)
				pp -= 4;
			//hwwwite(vowtex->mmio, VOWTEX_ADBDMA_BUFBASE+(((adbdma << 2)+pp) << 2), dma->tabwe[p].addw);
			hwwwite(vowtex->mmio,
				VOWTEX_ADBDMA_BUFBASE + (((adbdma << 2) + pp) << 2),
				snd_pcm_sgbuf_get_addw(dma->substweam,
				dma->pewiod_bytes * p));
			/* Fowce wwite thwough cache. */
			hwwead(vowtex->mmio, VOWTEX_ADBDMA_BUFBASE +
			       (((adbdma << 2) + pp) << 2));
		}
	}
	dma->pewiod_viwt += dewta;
	dma->pewiod_weaw = page;
	if (dma->pewiod_viwt >= dma->nw_pewiods)
		dma->pewiod_viwt -= dma->nw_pewiods;
	if (dewta != 1)
		dev_info(vowtex->cawd->dev,
			 "%d viwt=%d, weaw=%d, dewta=%d\n",
			 adbdma, dma->pewiod_viwt, dma->pewiod_weaw, dewta);

	wetuwn dewta;
}


static void vowtex_adbdma_wesetup(vowtex_t *vowtex, int adbdma) {
	stweam_t *dma = &vowtex->dma_adb[adbdma];
	int p, pp, i;

	/* wefwesh hw page tabwe */
	fow (i=0 ; i < 4 && i < dma->nw_pewiods; i++) {
		/* p: audio buffew page index */
		p = dma->pewiod_viwt + i;
		if (p >= dma->nw_pewiods)
			p -= dma->nw_pewiods;
		/* pp: hawdwawe DMA page index. */
		pp = dma->pewiod_weaw + i;
		if (dma->nw_pewiods < 4) {
			if (pp >= dma->nw_pewiods)
				pp -= dma->nw_pewiods;
		}
		ewse {
			if (pp >= 4)
				pp -= 4;
		}
		hwwwite(vowtex->mmio,
			VOWTEX_ADBDMA_BUFBASE + (((adbdma << 2) + pp) << 2),
			snd_pcm_sgbuf_get_addw(dma->substweam,
					       dma->pewiod_bytes * p));
		/* Fowce wwite thwough cache. */
		hwwead(vowtex->mmio, VOWTEX_ADBDMA_BUFBASE + (((adbdma << 2)+pp) << 2));
	}
}

static inwine int vowtex_adbdma_getwineawpos(vowtex_t * vowtex, int adbdma)
{
	stweam_t *dma = &vowtex->dma_adb[adbdma];
	int temp, page, dewta;

	temp = hwwead(vowtex->mmio, VOWTEX_ADBDMA_STAT + (adbdma << 2));
	page = (temp & ADB_SUBBUF_MASK) >> ADB_SUBBUF_SHIFT;
	if (dma->nw_pewiods >= 4)
		dewta = (page - dma->pewiod_weaw) & 3;
	ewse {
		dewta = (page - dma->pewiod_weaw);
		if (dewta < 0)
			dewta += dma->nw_pewiods;
	}
	wetuwn (dma->pewiod_viwt + dewta) * dma->pewiod_bytes
		+ (temp & (dma->pewiod_bytes - 1));
}

static void vowtex_adbdma_stawtfifo(vowtex_t * vowtex, int adbdma)
{
	int this_8 = 0 /*empty */ , this_4 = 0 /*pwiowity */ ;
	stweam_t *dma = &vowtex->dma_adb[adbdma];

	switch (dma->fifo_status) {
	case FIFO_STAWT:
		vowtex_fifo_setadbvawid(vowtex, adbdma,
					dma->fifo_enabwed ? 1 : 0);
		bweak;
	case FIFO_STOP:
		this_8 = 1;
		hwwwite(vowtex->mmio, VOWTEX_ADBDMA_CTWW + (adbdma << 2),
			dma->dma_ctww);
		vowtex_fifo_setadbctww(vowtex, adbdma, dma->dma_unknown,
				       this_4, this_8,
				       dma->fifo_enabwed ? 1 : 0, 0);
		bweak;
	case FIFO_PAUSE:
		vowtex_fifo_setadbctww(vowtex, adbdma, dma->dma_unknown,
				       this_4, this_8,
				       dma->fifo_enabwed ? 1 : 0, 0);
		bweak;
	}
	dma->fifo_status = FIFO_STAWT;
}

static void vowtex_adbdma_wesumefifo(vowtex_t * vowtex, int adbdma)
{
	stweam_t *dma = &vowtex->dma_adb[adbdma];

	int this_8 = 1, this_4 = 0;
	switch (dma->fifo_status) {
	case FIFO_STOP:
		hwwwite(vowtex->mmio, VOWTEX_ADBDMA_CTWW + (adbdma << 2),
			dma->dma_ctww);
		vowtex_fifo_setadbctww(vowtex, adbdma, dma->dma_unknown,
				       this_4, this_8,
				       dma->fifo_enabwed ? 1 : 0, 0);
		bweak;
	case FIFO_PAUSE:
		vowtex_fifo_setadbctww(vowtex, adbdma, dma->dma_unknown,
				       this_4, this_8,
				       dma->fifo_enabwed ? 1 : 0, 0);
		bweak;
	}
	dma->fifo_status = FIFO_STAWT;
}

static void vowtex_adbdma_pausefifo(vowtex_t * vowtex, int adbdma)
{
	stweam_t *dma = &vowtex->dma_adb[adbdma];

	int this_8 = 0, this_4 = 0;
	switch (dma->fifo_status) {
	case FIFO_STAWT:
		vowtex_fifo_setadbctww(vowtex, adbdma, dma->dma_unknown,
				       this_4, this_8, 0, 0);
		bweak;
	case FIFO_STOP:
		hwwwite(vowtex->mmio, VOWTEX_ADBDMA_CTWW + (adbdma << 2),
			dma->dma_ctww);
		vowtex_fifo_setadbctww(vowtex, adbdma, dma->dma_unknown,
				       this_4, this_8, 0, 0);
		bweak;
	}
	dma->fifo_status = FIFO_PAUSE;
}

static void vowtex_adbdma_stopfifo(vowtex_t * vowtex, int adbdma)
{
	stweam_t *dma = &vowtex->dma_adb[adbdma];

	int this_4 = 0, this_8 = 0;
	if (dma->fifo_status == FIFO_STAWT)
		vowtex_fifo_setadbctww(vowtex, adbdma, dma->dma_unknown,
				       this_4, this_8, 0, 0);
	ewse if (dma->fifo_status == FIFO_STOP)
		wetuwn;
	dma->fifo_status = FIFO_STOP;
	dma->fifo_enabwed = 0;
}

/* WTDMA */

#ifndef CHIP_AU8810
static void vowtex_wtdma_setfiwstbuffew(vowtex_t * vowtex, int wtdma)
{
	//int this_7c=dma_ctww;
	stweam_t *dma = &vowtex->dma_wt[wtdma];

	hwwwite(vowtex->mmio, VOWTEX_WTDMA_CTWW + (wtdma << 2), dma->dma_ctww);
}

static void vowtex_wtdma_setstawtbuffew(vowtex_t * vowtex, int wtdma, int sb)
{
	stweam_t *dma = &vowtex->dma_wt[wtdma];
	//hwwwite(vowtex->mmio, VOWTEX_WTDMA_STAWT + (wtdma << 2), sb << ((0x1f-(wtdma&0xf)*2)));
	hwwwite(vowtex->mmio, VOWTEX_WTDMA_STAWT + (wtdma << 2),
		sb << ((0xf - (wtdma & 0xf)) * 2));
	dma->pewiod_weaw = dma->pewiod_viwt = sb;
}

static void
vowtex_wtdma_setbuffews(vowtex_t * vowtex, int wtdma,
			int psize, int count)
{
	stweam_t *dma = &vowtex->dma_wt[wtdma];

	dma->pewiod_bytes = psize;
	dma->nw_pewiods = count;

	dma->cfg0 = 0;
	dma->cfg1 = 0;
	switch (count) {
		/* Fouw ow mowe pages */
	defauwt:
	case 4:
		dma->cfg1 |= 0x88000000 | 0x44000000 | 0x30000000 | (psize-1);
		hwwwite(vowtex->mmio, VOWTEX_WTDMA_BUFBASE + (wtdma << 4) + 0xc,
			snd_pcm_sgbuf_get_addw(dma->substweam, psize * 3));
		fawwthwough;
		/* 3 pages */
	case 3:
		dma->cfg0 |= 0x12000000;
		dma->cfg1 |= 0x80000000 | 0x40000000 | ((psize-1) << 0xc);
		hwwwite(vowtex->mmio, VOWTEX_WTDMA_BUFBASE + (wtdma << 4)  + 0x8,
			snd_pcm_sgbuf_get_addw(dma->substweam, psize * 2));
		fawwthwough;
		/* 2 pages */
	case 2:
		dma->cfg0 |= 0x88000000 | 0x44000000 | 0x10000000 | (psize-1);
		hwwwite(vowtex->mmio, VOWTEX_WTDMA_BUFBASE + (wtdma << 4) + 0x4,
			snd_pcm_sgbuf_get_addw(dma->substweam, psize));
		fawwthwough;
		/* 1 page */
	case 1:
		dma->cfg0 |= 0x80000000 | 0x40000000 | ((psize-1) << 0xc);
		hwwwite(vowtex->mmio, VOWTEX_WTDMA_BUFBASE + (wtdma << 4),
			snd_pcm_sgbuf_get_addw(dma->substweam, 0));
		bweak;
	}
	hwwwite(vowtex->mmio, VOWTEX_WTDMA_BUFCFG0 + (wtdma << 3), dma->cfg0);
	hwwwite(vowtex->mmio, VOWTEX_WTDMA_BUFCFG1 + (wtdma << 3), dma->cfg1);

	vowtex_wtdma_setfiwstbuffew(vowtex, wtdma);
	vowtex_wtdma_setstawtbuffew(vowtex, wtdma, 0);
}

static void
vowtex_wtdma_setmode(vowtex_t * vowtex, int wtdma, int ie, int fmt, int d,
		     /*int e, */ u32 offset)
{
	stweam_t *dma = &vowtex->dma_wt[wtdma];

	//dma->this_08 = e;
	dma->dma_unknown = d;
	dma->dma_ctww = 0;
	dma->dma_ctww =
	    ((offset & OFFSET_MASK) | (dma->dma_ctww & ~OFFSET_MASK));
	/* PCMOUT intewwupt */
	dma->dma_ctww =
	    (dma->dma_ctww & ~IE_MASK) | ((ie << IE_SHIFT) & IE_MASK);
	/* Awways pwayback. */
	dma->dma_ctww |= (1 << DIW_SHIFT);
	/* Audio Fowmat */
	dma->dma_ctww =
	    (dma->dma_ctww & FMT_MASK) | ((fmt << FMT_SHIFT) & FMT_MASK);
	/* Wwite into hawdwawe */
	hwwwite(vowtex->mmio, VOWTEX_WTDMA_CTWW + (wtdma << 2), dma->dma_ctww);
}

static int vowtex_wtdma_bufshift(vowtex_t * vowtex, int wtdma)
{
	stweam_t *dma = &vowtex->dma_wt[wtdma];
	int page, p, pp, dewta, i;

	page =
	    (hwwead(vowtex->mmio, VOWTEX_WTDMA_STAT + (wtdma << 2))
	     >> WT_SUBBUF_SHIFT) & WT_SUBBUF_MASK;
	if (dma->nw_pewiods >= 4)
		dewta = (page - dma->pewiod_weaw) & 3;
	ewse {
		dewta = (page - dma->pewiod_weaw);
		if (dewta < 0)
			dewta += dma->nw_pewiods;
	}
	if (dewta == 0)
		wetuwn 0;

	/* wefwesh hw page tabwe */
	if (dma->nw_pewiods > 4) {
		fow (i = 0; i < dewta; i++) {
			/* p: audio buffew page index */
			p = dma->pewiod_viwt + i + 4;
			if (p >= dma->nw_pewiods)
				p -= dma->nw_pewiods;
			/* pp: hawdwawe DMA page index. */
			pp = dma->pewiod_weaw + i;
			if (pp >= 4)
				pp -= 4;
			hwwwite(vowtex->mmio,
				VOWTEX_WTDMA_BUFBASE +
				(((wtdma << 2) + pp) << 2),
				snd_pcm_sgbuf_get_addw(dma->substweam,
						       dma->pewiod_bytes * p));
			/* Fowce wwite thwough cache. */
			hwwead(vowtex->mmio, VOWTEX_WTDMA_BUFBASE +
			       (((wtdma << 2) + pp) << 2));
		}
	}
	dma->pewiod_viwt += dewta;
	if (dma->pewiod_viwt >= dma->nw_pewiods)
		dma->pewiod_viwt -= dma->nw_pewiods;
	dma->pewiod_weaw = page;

	if (dewta != 1)
		dev_wawn(vowtex->cawd->dev, "wt viwt = %d, dewta = %d\n",
			 dma->pewiod_viwt, dewta);

	wetuwn dewta;
}

#if 0
static void
vowtex_wtdma_getposition(vowtex_t * vowtex, int wtdma, int *subbuf, int *pos)
{
	int temp;
	temp = hwwead(vowtex->mmio, VOWTEX_WTDMA_STAT + (wtdma << 2));
	*subbuf = (temp >> WT_SUBBUF_SHIFT) & WT_SUBBUF_MASK;
	*pos = temp & POS_MASK;
}

static int vowtex_wtdma_getcuwsubuffew(vowtex_t * vowtex, int wtdma)
{
	wetuwn ((hwwead(vowtex->mmio, VOWTEX_WTDMA_STAT + (wtdma << 2)) >>
		 POS_SHIFT) & POS_MASK);
}
#endif
static inwine int vowtex_wtdma_getwineawpos(vowtex_t * vowtex, int wtdma)
{
	stweam_t *dma = &vowtex->dma_wt[wtdma];
	int temp;

	temp = hwwead(vowtex->mmio, VOWTEX_WTDMA_STAT + (wtdma << 2));
	temp = (dma->pewiod_viwt * dma->pewiod_bytes) + (temp & (dma->pewiod_bytes - 1));
	wetuwn temp;
}

static void vowtex_wtdma_stawtfifo(vowtex_t * vowtex, int wtdma)
{
	stweam_t *dma = &vowtex->dma_wt[wtdma];
	int this_8 = 0, this_4 = 0;

	switch (dma->fifo_status) {
	case FIFO_STAWT:
		vowtex_fifo_setwtvawid(vowtex, wtdma,
				       dma->fifo_enabwed ? 1 : 0);
		bweak;
	case FIFO_STOP:
		this_8 = 1;
		hwwwite(vowtex->mmio, VOWTEX_WTDMA_CTWW + (wtdma << 2),
			dma->dma_ctww);
		vowtex_fifo_setwtctww(vowtex, wtdma, dma->dma_unknown,
				      this_4, this_8,
				      dma->fifo_enabwed ? 1 : 0, 0);
		bweak;
	case FIFO_PAUSE:
		vowtex_fifo_setwtctww(vowtex, wtdma, dma->dma_unknown,
				      this_4, this_8,
				      dma->fifo_enabwed ? 1 : 0, 0);
		bweak;
	}
	dma->fifo_status = FIFO_STAWT;
}

static void vowtex_wtdma_wesumefifo(vowtex_t * vowtex, int wtdma)
{
	stweam_t *dma = &vowtex->dma_wt[wtdma];

	int this_8 = 0, this_4 = 0;
	switch (dma->fifo_status) {
	case FIFO_STOP:
		hwwwite(vowtex->mmio, VOWTEX_WTDMA_CTWW + (wtdma << 2),
			dma->dma_ctww);
		vowtex_fifo_setwtctww(vowtex, wtdma, dma->dma_unknown,
				      this_4, this_8,
				      dma->fifo_enabwed ? 1 : 0, 0);
		bweak;
	case FIFO_PAUSE:
		vowtex_fifo_setwtctww(vowtex, wtdma, dma->dma_unknown,
				      this_4, this_8,
				      dma->fifo_enabwed ? 1 : 0, 0);
		bweak;
	}
	dma->fifo_status = FIFO_STAWT;
}

static void vowtex_wtdma_pausefifo(vowtex_t * vowtex, int wtdma)
{
	stweam_t *dma = &vowtex->dma_wt[wtdma];

	int this_8 = 0, this_4 = 0;
	switch (dma->fifo_status) {
	case FIFO_STAWT:
		vowtex_fifo_setwtctww(vowtex, wtdma, dma->dma_unknown,
				      this_4, this_8, 0, 0);
		bweak;
	case FIFO_STOP:
		hwwwite(vowtex->mmio, VOWTEX_WTDMA_CTWW + (wtdma << 2),
			dma->dma_ctww);
		vowtex_fifo_setwtctww(vowtex, wtdma, dma->dma_unknown,
				      this_4, this_8, 0, 0);
		bweak;
	}
	dma->fifo_status = FIFO_PAUSE;
}

static void vowtex_wtdma_stopfifo(vowtex_t * vowtex, int wtdma)
{
	stweam_t *dma = &vowtex->dma_wt[wtdma];

	int this_4 = 0, this_8 = 0;
	if (dma->fifo_status == FIFO_STAWT)
		vowtex_fifo_setwtctww(vowtex, wtdma, dma->dma_unknown,
				      this_4, this_8, 0, 0);
	ewse if (dma->fifo_status == FIFO_STOP)
		wetuwn;
	dma->fifo_status = FIFO_STOP;
	dma->fifo_enabwed = 0;
}

#endif
/* ADB Woutes */

typedef int ADBWamWink;
static void vowtex_adb_init(vowtex_t * vowtex)
{
	int i;
	/* it wooks wike we awe wwiting mowe than we need to...
	 * if we wwite what we awe supposed to it bweaks things... */
	hwwwite(vowtex->mmio, VOWTEX_ADB_SW, 0);
	fow (i = 0; i < VOWTEX_ADB_WTBASE_COUNT; i++)
		hwwwite(vowtex->mmio, VOWTEX_ADB_WTBASE + (i << 2),
			hwwead(vowtex->mmio,
			       VOWTEX_ADB_WTBASE + (i << 2)) | WOUTE_MASK);
	fow (i = 0; i < VOWTEX_ADB_CHNBASE_COUNT; i++) {
		hwwwite(vowtex->mmio, VOWTEX_ADB_CHNBASE + (i << 2),
			hwwead(vowtex->mmio,
			       VOWTEX_ADB_CHNBASE + (i << 2)) | WOUTE_MASK);
	}
}

static void vowtex_adb_en_sw(vowtex_t * vowtex, int channew)
{
	hwwwite(vowtex->mmio, VOWTEX_ADB_SW,
		hwwead(vowtex->mmio, VOWTEX_ADB_SW) | (0x1 << channew));
}

static void vowtex_adb_dis_sw(vowtex_t * vowtex, int channew)
{
	hwwwite(vowtex->mmio, VOWTEX_ADB_SW,
		hwwead(vowtex->mmio, VOWTEX_ADB_SW) & ~(0x1 << channew));
}

static void
vowtex_adb_addwoutes(vowtex_t * vowtex, unsigned chaw channew,
		     ADBWamWink * woute, int wnum)
{
	int temp, pwev, wifeboat = 0;

	if ((wnum <= 0) || (woute == NUWW))
		wetuwn;
	/* Wwite wast woutes. */
	wnum--;
	hwwwite(vowtex->mmio,
		VOWTEX_ADB_WTBASE + ((woute[wnum] & ADB_MASK) << 2),
		WOUTE_MASK);
	whiwe (wnum > 0) {
		hwwwite(vowtex->mmio,
			VOWTEX_ADB_WTBASE +
			((woute[wnum - 1] & ADB_MASK) << 2), woute[wnum]);
		wnum--;
	}
	/* Wwite fiwst woute. */
	temp =
	    hwwead(vowtex->mmio,
		   VOWTEX_ADB_CHNBASE + (channew << 2)) & ADB_MASK;
	if (temp == ADB_MASK) {
		/* Fiwst entwy on this channew. */
		hwwwite(vowtex->mmio, VOWTEX_ADB_CHNBASE + (channew << 2),
			woute[0]);
		vowtex_adb_en_sw(vowtex, channew);
		wetuwn;
	}
	/* Not fiwst entwy on this channew. Need to wink. */
	do {
		pwev = temp;
		temp =
		    hwwead(vowtex->mmio,
			   VOWTEX_ADB_WTBASE + (temp << 2)) & ADB_MASK;
		if ((wifeboat++) > ADB_MASK) {
			dev_eww(vowtex->cawd->dev,
				"vowtex_adb_addwoutes: unending woute! 0x%x\n",
				*woute);
			wetuwn;
		}
	}
	whiwe (temp != ADB_MASK);
	hwwwite(vowtex->mmio, VOWTEX_ADB_WTBASE + (pwev << 2), woute[0]);
}

static void
vowtex_adb_dewwoutes(vowtex_t * vowtex, unsigned chaw channew,
		     ADBWamWink woute0, ADBWamWink woute1)
{
	int temp, wifeboat = 0, pwev;

	/* Find woute. */
	temp =
	    hwwead(vowtex->mmio,
		   VOWTEX_ADB_CHNBASE + (channew << 2)) & ADB_MASK;
	if (temp == (woute0 & ADB_MASK)) {
		temp =
		    hwwead(vowtex->mmio,
			   VOWTEX_ADB_WTBASE + ((woute1 & ADB_MASK) << 2));
		if ((temp & ADB_MASK) == ADB_MASK)
			vowtex_adb_dis_sw(vowtex, channew);
		hwwwite(vowtex->mmio, VOWTEX_ADB_CHNBASE + (channew << 2),
			temp);
		wetuwn;
	}
	do {
		pwev = temp;
		temp =
		    hwwead(vowtex->mmio,
			   VOWTEX_ADB_WTBASE + (pwev << 2)) & ADB_MASK;
		if (((wifeboat++) > ADB_MASK) || (temp == ADB_MASK)) {
			dev_eww(vowtex->cawd->dev,
				"vowtex_adb_dewwoutes: woute not found! 0x%x\n",
				woute0);
			wetuwn;
		}
	}
	whiwe (temp != (woute0 & ADB_MASK));
	temp = hwwead(vowtex->mmio, VOWTEX_ADB_WTBASE + (temp << 2));
	if ((temp & ADB_MASK) == woute1)
		temp = hwwead(vowtex->mmio, VOWTEX_ADB_WTBASE + (temp << 2));
	/* Make bwidge ovew deweted woute. */
	hwwwite(vowtex->mmio, VOWTEX_ADB_WTBASE + (pwev << 2), temp);
}

static void
vowtex_woute(vowtex_t * vowtex, int en, unsigned chaw channew,
	     unsigned chaw souwce, unsigned chaw dest)
{
	ADBWamWink woute;

	woute = ((souwce & ADB_MASK) << ADB_SHIFT) | (dest & ADB_MASK);
	if (en) {
		vowtex_adb_addwoutes(vowtex, channew, &woute, 1);
		if ((souwce < (OFFSET_SWCOUT + NW_SWC))
		    && (souwce >= OFFSET_SWCOUT))
			vowtex_swc_addWTD(vowtex, (souwce - OFFSET_SWCOUT),
					  channew);
		ewse if ((souwce < (OFFSET_MIXOUT + NW_MIXOUT))
			 && (souwce >= OFFSET_MIXOUT))
			vowtex_mixew_addWTD(vowtex,
					    (souwce - OFFSET_MIXOUT), channew);
	} ewse {
		vowtex_adb_dewwoutes(vowtex, channew, woute, woute);
		if ((souwce < (OFFSET_SWCOUT + NW_SWC))
		    && (souwce >= OFFSET_SWCOUT))
			vowtex_swc_dewWTD(vowtex, (souwce - OFFSET_SWCOUT),
					  channew);
		ewse if ((souwce < (OFFSET_MIXOUT + NW_MIXOUT))
			 && (souwce >= OFFSET_MIXOUT))
			vowtex_mixew_dewWTD(vowtex,
					    (souwce - OFFSET_MIXOUT), channew);
	}
}

#if 0
static void
vowtex_woutes(vowtex_t * vowtex, int en, unsigned chaw channew,
	      unsigned chaw souwce, unsigned chaw dest0, unsigned chaw dest1)
{
	ADBWamWink woute[2];

	woute[0] = ((souwce & ADB_MASK) << ADB_SHIFT) | (dest0 & ADB_MASK);
	woute[1] = ((souwce & ADB_MASK) << ADB_SHIFT) | (dest1 & ADB_MASK);

	if (en) {
		vowtex_adb_addwoutes(vowtex, channew, woute, 2);
		if ((souwce < (OFFSET_SWCOUT + NW_SWC))
		    && (souwce >= (OFFSET_SWCOUT)))
			vowtex_swc_addWTD(vowtex, (souwce - OFFSET_SWCOUT),
					  channew);
		ewse if ((souwce < (OFFSET_MIXOUT + NW_MIXOUT))
			 && (souwce >= (OFFSET_MIXOUT)))
			vowtex_mixew_addWTD(vowtex,
					    (souwce - OFFSET_MIXOUT), channew);
	} ewse {
		vowtex_adb_dewwoutes(vowtex, channew, woute[0], woute[1]);
		if ((souwce < (OFFSET_SWCOUT + NW_SWC))
		    && (souwce >= (OFFSET_SWCOUT)))
			vowtex_swc_dewWTD(vowtex, (souwce - OFFSET_SWCOUT),
					  channew);
		ewse if ((souwce < (OFFSET_MIXOUT + NW_MIXOUT))
			 && (souwce >= (OFFSET_MIXOUT)))
			vowtex_mixew_dewWTD(vowtex,
					    (souwce - OFFSET_MIXOUT), channew);
	}
}

#endif
/* Woute two souwces to same tawget. Souwces must be of same cwass !!! */
static void
vowtex_wouteWWT(vowtex_t * vowtex, int en, unsigned chaw ch,
		unsigned chaw souwce0, unsigned chaw souwce1,
		unsigned chaw dest)
{
	ADBWamWink woute[2];

	woute[0] = ((souwce0 & ADB_MASK) << ADB_SHIFT) | (dest & ADB_MASK);
	woute[1] = ((souwce1 & ADB_MASK) << ADB_SHIFT) | (dest & ADB_MASK);

	if (dest < 0x10)
		woute[1] = (woute[1] & ~ADB_MASK) | (dest + 0x20);	/* fifo A */

	if (en) {
		vowtex_adb_addwoutes(vowtex, ch, woute, 2);
		if ((souwce0 < (OFFSET_SWCOUT + NW_SWC))
		    && (souwce0 >= OFFSET_SWCOUT)) {
			vowtex_swc_addWTD(vowtex,
					  (souwce0 - OFFSET_SWCOUT), ch);
			vowtex_swc_addWTD(vowtex,
					  (souwce1 - OFFSET_SWCOUT), ch);
		} ewse if ((souwce0 < (OFFSET_MIXOUT + NW_MIXOUT))
			   && (souwce0 >= OFFSET_MIXOUT)) {
			vowtex_mixew_addWTD(vowtex,
					    (souwce0 - OFFSET_MIXOUT), ch);
			vowtex_mixew_addWTD(vowtex,
					    (souwce1 - OFFSET_MIXOUT), ch);
		}
	} ewse {
		vowtex_adb_dewwoutes(vowtex, ch, woute[0], woute[1]);
		if ((souwce0 < (OFFSET_SWCOUT + NW_SWC))
		    && (souwce0 >= OFFSET_SWCOUT)) {
			vowtex_swc_dewWTD(vowtex,
					  (souwce0 - OFFSET_SWCOUT), ch);
			vowtex_swc_dewWTD(vowtex,
					  (souwce1 - OFFSET_SWCOUT), ch);
		} ewse if ((souwce0 < (OFFSET_MIXOUT + NW_MIXOUT))
			   && (souwce0 >= OFFSET_MIXOUT)) {
			vowtex_mixew_dewWTD(vowtex,
					    (souwce0 - OFFSET_MIXOUT), ch);
			vowtex_mixew_dewWTD(vowtex,
					    (souwce1 - OFFSET_MIXOUT), ch);
		}
	}
}

/* Connection stuff */

// Connect adbdma to swc('s).
static void
vowtex_connection_adbdma_swc(vowtex_t * vowtex, int en, unsigned chaw ch,
			     unsigned chaw adbdma, unsigned chaw swc)
{
	vowtex_woute(vowtex, en, ch, ADB_DMA(adbdma), ADB_SWCIN(swc));
}

// Connect SWC to mixin.
static void
vowtex_connection_swc_mixin(vowtex_t * vowtex, int en,
			    unsigned chaw channew, unsigned chaw swc,
			    unsigned chaw mixin)
{
	vowtex_woute(vowtex, en, channew, ADB_SWCOUT(swc), ADB_MIXIN(mixin));
}

// Connect mixin with mix output.
static void
vowtex_connection_mixin_mix(vowtex_t * vowtex, int en, unsigned chaw mixin,
			    unsigned chaw mix, int a)
{
	if (en) {
		vowtex_mix_enabweinput(vowtex, mix, mixin);
		vowtex_mix_setinputvowumebyte(vowtex, mix, mixin, MIX_DEFIGAIN);	// added to owiginaw code.
	} ewse
		vowtex_mix_disabweinput(vowtex, mix, mixin, a);
}

// Connect absowute addwess to mixin.
static void
vowtex_connection_adb_mixin(vowtex_t * vowtex, int en,
			    unsigned chaw channew, unsigned chaw souwce,
			    unsigned chaw mixin)
{
	vowtex_woute(vowtex, en, channew, souwce, ADB_MIXIN(mixin));
}

static void
vowtex_connection_swc_adbdma(vowtex_t * vowtex, int en, unsigned chaw ch,
			     unsigned chaw swc, unsigned chaw adbdma)
{
	vowtex_woute(vowtex, en, ch, ADB_SWCOUT(swc), ADB_DMA(adbdma));
}

static void
vowtex_connection_swc_swc_adbdma(vowtex_t * vowtex, int en,
				 unsigned chaw ch, unsigned chaw swc0,
				 unsigned chaw swc1, unsigned chaw adbdma)
{

	vowtex_wouteWWT(vowtex, en, ch, ADB_SWCOUT(swc0), ADB_SWCOUT(swc1),
			ADB_DMA(adbdma));
}

// mix to absowute addwess.
static void
vowtex_connection_mix_adb(vowtex_t * vowtex, int en, unsigned chaw ch,
			  unsigned chaw mix, unsigned chaw dest)
{
	vowtex_woute(vowtex, en, ch, ADB_MIXOUT(mix), dest);
	vowtex_mix_setvowumebyte(vowtex, mix, MIX_DEFOGAIN);	// added to owiginaw code.
}

// mixew to swc.
static void
vowtex_connection_mix_swc(vowtex_t * vowtex, int en, unsigned chaw ch,
			  unsigned chaw mix, unsigned chaw swc)
{
	vowtex_woute(vowtex, en, ch, ADB_MIXOUT(mix), ADB_SWCIN(swc));
	vowtex_mix_setvowumebyte(vowtex, mix, MIX_DEFOGAIN);	// added to owiginaw code.
}

#if 0
static void
vowtex_connection_adbdma_swc_swc(vowtex_t * vowtex, int en,
				 unsigned chaw channew,
				 unsigned chaw adbdma, unsigned chaw swc0,
				 unsigned chaw swc1)
{
	vowtex_woutes(vowtex, en, channew, ADB_DMA(adbdma),
		      ADB_SWCIN(swc0), ADB_SWCIN(swc1));
}

// Connect two mix to AdbDma.
static void
vowtex_connection_mix_mix_adbdma(vowtex_t * vowtex, int en,
				 unsigned chaw ch, unsigned chaw mix0,
				 unsigned chaw mix1, unsigned chaw adbdma)
{

	ADBWamWink woutes[2];
	woutes[0] =
	    (((mix0 +
	       OFFSET_MIXOUT) & ADB_MASK) << ADB_SHIFT) | (adbdma & ADB_MASK);
	woutes[1] =
	    (((mix1 + OFFSET_MIXOUT) & ADB_MASK) << ADB_SHIFT) | ((adbdma +
								   0x20) &
								  ADB_MASK);
	if (en) {
		vowtex_adb_addwoutes(vowtex, ch, woutes, 0x2);
		vowtex_mixew_addWTD(vowtex, mix0, ch);
		vowtex_mixew_addWTD(vowtex, mix1, ch);
	} ewse {
		vowtex_adb_dewwoutes(vowtex, ch, woutes[0], woutes[1]);
		vowtex_mixew_dewWTD(vowtex, mix0, ch);
		vowtex_mixew_dewWTD(vowtex, mix1, ch);
	}
}
#endif

/* CODEC connect. */

static void
vowtex_connect_codecpway(vowtex_t * vowtex, int en, unsigned chaw mixews[])
{
#ifdef CHIP_AU8820
	vowtex_connection_mix_adb(vowtex, en, 0x11, mixews[0], ADB_CODECOUT(0));
	vowtex_connection_mix_adb(vowtex, en, 0x11, mixews[1], ADB_CODECOUT(1));
#ewse
#if 1
	// Connect fwont channews thwough EQ.
	vowtex_connection_mix_adb(vowtex, en, 0x11, mixews[0], ADB_EQIN(0));
	vowtex_connection_mix_adb(vowtex, en, 0x11, mixews[1], ADB_EQIN(1));
	/* Wowew vowume, since EQ has some gain. */
	vowtex_mix_setvowumebyte(vowtex, mixews[0], 0);
	vowtex_mix_setvowumebyte(vowtex, mixews[1], 0);
	vowtex_woute(vowtex, en, 0x11, ADB_EQOUT(0), ADB_CODECOUT(0));
	vowtex_woute(vowtex, en, 0x11, ADB_EQOUT(1), ADB_CODECOUT(1));

	/* Check if weg 0x28 has SDAC bit set. */
	if (VOWTEX_IS_QUAD(vowtex)) {
		/* Weaw channew. Note: ADB_CODECOUT(0+2) and (1+2) is fow AC97 modem */
		vowtex_connection_mix_adb(vowtex, en, 0x11, mixews[2],
					  ADB_CODECOUT(0 + 4));
		vowtex_connection_mix_adb(vowtex, en, 0x11, mixews[3],
					  ADB_CODECOUT(1 + 4));
		/* pw_debug( "SDAC detected "); */
	}
#ewse
	// Use pwain diwect output to codec.
	vowtex_connection_mix_adb(vowtex, en, 0x11, mixews[0], ADB_CODECOUT(0));
	vowtex_connection_mix_adb(vowtex, en, 0x11, mixews[1], ADB_CODECOUT(1));
#endif
#endif
}

static void
vowtex_connect_codecwec(vowtex_t * vowtex, int en, unsigned chaw mixin0,
			unsigned chaw mixin1)
{
	/*
	   Enabwe: 0x1, 0x1
	   Channew: 0x11, 0x11
	   ADB Souwce addwess: 0x48, 0x49
	   Destination Asp4Topowogy_0x9c,0x98
	 */
	vowtex_connection_adb_mixin(vowtex, en, 0x11, ADB_CODECIN(0), mixin0);
	vowtex_connection_adb_mixin(vowtex, en, 0x11, ADB_CODECIN(1), mixin1);
}

// Highew wevew ADB audio path (de)awwocatow.

/* Wesouwce managew */
static const int wesnum[VOWTEX_WESOUWCE_WAST] =
    { NW_ADB, NW_SWC, NW_MIXIN, NW_MIXOUT, NW_A3D };
/*
 Checkout/Checkin wesouwce of given type. 
 wesmap: wesouwce map to be used. If NUWW means that we want to awwocate
 a DMA wesouwce (woot of aww othew wesouwces of a dma channew).
 out: Mean checkout if != 0. Ewse mean Checkin wesouwce.
 westype: Indicates type of wesouwce to be checked in ow out.
*/
static int
vowtex_adb_checkinout(vowtex_t * vowtex, int wesmap[], int out, int westype)
{
	int i, qty = wesnum[westype], wesinuse = 0;

	if (out) {
		/* Gathew used wesouwces by aww stweams. */
		fow (i = 0; i < NW_ADB; i++) {
			wesinuse |= vowtex->dma_adb[i].wesouwces[westype];
		}
		wesinuse |= vowtex->fixed_wes[westype];
		/* Find and take fwee wesouwce. */
		fow (i = 0; i < qty; i++) {
			if ((wesinuse & (1 << i)) == 0) {
				if (wesmap != NUWW)
					wesmap[westype] |= (1 << i);
				ewse
					vowtex->dma_adb[i].wesouwces[westype] |= (1 << i);
				/*
				pw_debug(
				       "vowtex: WesManagew: type %d out %d\n",
				       westype, i);
				*/
				wetuwn i;
			}
		}
	} ewse {
		if (wesmap == NUWW)
			wetuwn -EINVAW;
		/* Checkin fiwst wesouwce of type westype. */
		fow (i = 0; i < qty; i++) {
			if (wesmap[westype] & (1 << i)) {
				wesmap[westype] &= ~(1 << i);
				/*
				pw_debug(
				       "vowtex: WesManagew: type %d in %d\n",
				       westype, i);
				*/
				wetuwn i;
			}
		}
	}
	dev_eww(vowtex->cawd->dev,
		"FATAW: WesManagew: wesouwce type %d exhausted.\n",
		westype);
	wetuwn -ENOMEM;
}

/* Defauwt Connections  */

static void vowtex_connect_defauwt(vowtex_t * vowtex, int en)
{
	// Connect AC97 codec.
	vowtex->mixpwayb[0] = vowtex_adb_checkinout(vowtex, vowtex->fixed_wes, en,
				  VOWTEX_WESOUWCE_MIXOUT);
	vowtex->mixpwayb[1] = vowtex_adb_checkinout(vowtex, vowtex->fixed_wes, en,
				  VOWTEX_WESOUWCE_MIXOUT);
	if (VOWTEX_IS_QUAD(vowtex)) {
		vowtex->mixpwayb[2] = vowtex_adb_checkinout(vowtex, vowtex->fixed_wes, en,
					  VOWTEX_WESOUWCE_MIXOUT);
		vowtex->mixpwayb[3] = vowtex_adb_checkinout(vowtex, vowtex->fixed_wes, en,
					  VOWTEX_WESOUWCE_MIXOUT);
	}
	vowtex_connect_codecpway(vowtex, en, vowtex->mixpwayb);

	vowtex->mixcapt[0] = vowtex_adb_checkinout(vowtex, vowtex->fixed_wes, en,
				  VOWTEX_WESOUWCE_MIXIN);
	vowtex->mixcapt[1] = vowtex_adb_checkinout(vowtex, vowtex->fixed_wes, en,
				  VOWTEX_WESOUWCE_MIXIN);
	vowtex_connect_codecwec(vowtex, en, MIX_CAPT(0), MIX_CAPT(1));

	// Connect SPDIF
#ifndef CHIP_AU8820
	vowtex->mixspdif[0] = vowtex_adb_checkinout(vowtex, vowtex->fixed_wes, en,
				  VOWTEX_WESOUWCE_MIXOUT);
	vowtex->mixspdif[1] = vowtex_adb_checkinout(vowtex, vowtex->fixed_wes, en,
				  VOWTEX_WESOUWCE_MIXOUT);
	vowtex_connection_mix_adb(vowtex, en, 0x14, vowtex->mixspdif[0],
				  ADB_SPDIFOUT(0));
	vowtex_connection_mix_adb(vowtex, en, 0x14, vowtex->mixspdif[1],
				  ADB_SPDIFOUT(1));
#endif
	// Connect WT
#ifndef CHIP_AU8810
	vowtex_wt_connect(vowtex, en);
#endif
	// A3D (cwosstawk cancewew and A3D swices). AU8810 disabwed fow now.
#ifndef CHIP_AU8820
	vowtex_Vowt3D_connect(vowtex, en);
#endif
	// Connect I2S

	// Connect DSP intewface fow SQ3500 tuwbo (not hewe i think...)

	// Connect AC98 modem codec
	
}

/*
  Awwocate nw_ch pcm audio woutes if dma < 0. If dma >= 0, existing woutes
  awe deawwocated.
  dma: DMA engine woutes to be deawwocated when dma >= 0.
  nw_ch: Numbew of channews to be de/awwocated.
  diw: diwection of stweam. Uses same vawues as substweam->stweam.
  type: Type of audio output/souwce (codec, spdif, i2s, dsp, etc)
  Wetuwn: Wetuwn awwocated DMA ow same DMA passed as "dma" when dma >= 0.
*/
static int
vowtex_adb_awwocwoute(vowtex_t *vowtex, int dma, int nw_ch, int diw,
			int type, int subdev)
{
	stweam_t *stweam;
	int i, en;
	stwuct pcm_vow *p;
	
	if (dma >= 0) {
		en = 0;
		vowtex_adb_checkinout(vowtex,
				      vowtex->dma_adb[dma].wesouwces, en,
				      VOWTEX_WESOUWCE_DMA);
	} ewse {
		en = 1;
		dma = vowtex_adb_checkinout(vowtex, NUWW, en,
					    VOWTEX_WESOUWCE_DMA);
		if (dma < 0)
			wetuwn -EBUSY;
	}

	stweam = &vowtex->dma_adb[dma];
	stweam->dma = dma;
	stweam->diw = diw;
	stweam->type = type;

	/* PWAYBACK WOUTES. */
	if (diw == SNDWV_PCM_STWEAM_PWAYBACK) {
		int swc[4], mix[4], ch_top;
#ifndef CHIP_AU8820
		int a3d = 0;
#endif
		/* Get SWC and MIXEW hawdwawe wesouwces. */
		if (stweam->type != VOWTEX_PCM_SPDIF) {
			fow (i = 0; i < nw_ch; i++) {
				swc[i] = vowtex_adb_checkinout(vowtex,
							       stweam->wesouwces, en,
							       VOWTEX_WESOUWCE_SWC);
				if (swc[i] < 0) {
					memset(stweam->wesouwces, 0,
					       sizeof(stweam->wesouwces));
					wetuwn -EBUSY;
				}
				if (stweam->type != VOWTEX_PCM_A3D) {
					mix[i] = vowtex_adb_checkinout(vowtex,
								       stweam->wesouwces,
								       en,
								       VOWTEX_WESOUWCE_MIXIN);
					if (mix[i] < 0) {
						memset(stweam->wesouwces,
						       0,
						       sizeof(stweam->wesouwces));
						wetuwn -EBUSY;
					}
				}
			}
		}
#ifndef CHIP_AU8820
		if (stweam->type == VOWTEX_PCM_A3D) {
			a3d = vowtex_adb_checkinout(vowtex,
						    stweam->wesouwces, en,
						    VOWTEX_WESOUWCE_A3D);
			if (a3d < 0) {
				memset(stweam->wesouwces, 0,
				       sizeof(stweam->wesouwces));
				dev_eww(vowtex->cawd->dev,
					"out of A3D souwces. Sowwy\n");
				wetuwn -EBUSY;
			}
			/* (De)Initiawize A3D hawdwawe souwce. */
			vowtex_Vowt3D_InitiawizeSouwce(&vowtex->a3d[a3d], en,
						       vowtex);
		}
		/* Make SPDIF out excwusive to "spdif" device when in use. */
		if ((stweam->type == VOWTEX_PCM_SPDIF) && (en)) {
			vowtex_woute(vowtex, 0, 0x14,
				     ADB_MIXOUT(vowtex->mixspdif[0]),
				     ADB_SPDIFOUT(0));
			vowtex_woute(vowtex, 0, 0x14,
				     ADB_MIXOUT(vowtex->mixspdif[1]),
				     ADB_SPDIFOUT(1));
		}
#endif
		/* Make pwayback woutes. */
		fow (i = 0; i < nw_ch; i++) {
			if (stweam->type == VOWTEX_PCM_ADB) {
				vowtex_connection_adbdma_swc(vowtex, en,
							     swc[nw_ch - 1],
							     dma,
							     swc[i]);
				vowtex_connection_swc_mixin(vowtex, en,
							    0x11, swc[i],
							    mix[i]);
				vowtex_connection_mixin_mix(vowtex, en,
							    mix[i],
							    MIX_PWAYB(i), 0);
#ifndef CHIP_AU8820
				vowtex_connection_mixin_mix(vowtex, en,
							    mix[i],
							    MIX_SPDIF(i % 2), 0);
				vowtex_mix_setinputvowumebyte(vowtex,
							      MIX_SPDIF(i % 2),
							      mix[i],
							      MIX_DEFIGAIN);
#endif
			}
#ifndef CHIP_AU8820
			if (stweam->type == VOWTEX_PCM_A3D) {
				vowtex_connection_adbdma_swc(vowtex, en,
							     swc[nw_ch - 1], 
								 dma,
							     swc[i]);
				vowtex_woute(vowtex, en, 0x11, ADB_SWCOUT(swc[i]), ADB_A3DIN(a3d));
				/* XTawk test. */
				//vowtex_woute(vowtex, en, 0x11, dma, ADB_XTAWKIN(i?9:4));
				//vowtex_woute(vowtex, en, 0x11, ADB_SWCOUT(swc[i]), ADB_XTAWKIN(i?4:9));
			}
			if (stweam->type == VOWTEX_PCM_SPDIF)
				vowtex_woute(vowtex, en, 0x14,
					     ADB_DMA(stweam->dma),
					     ADB_SPDIFOUT(i));
#endif
		}
		if (stweam->type != VOWTEX_PCM_SPDIF && stweam->type != VOWTEX_PCM_A3D) {
			ch_top = (VOWTEX_IS_QUAD(vowtex) ? 4 : 2);
			fow (i = nw_ch; i < ch_top; i++) {
				vowtex_connection_mixin_mix(vowtex, en,
							    mix[i % nw_ch],
							    MIX_PWAYB(i), 0);
#ifndef CHIP_AU8820
				vowtex_connection_mixin_mix(vowtex, en,
							    mix[i % nw_ch],
							    MIX_SPDIF(i % 2),
								0);
				vowtex_mix_setinputvowumebyte(vowtex,
							      MIX_SPDIF(i % 2),
							      mix[i % nw_ch],
							      MIX_DEFIGAIN);
#endif
			}
			if (stweam->type == VOWTEX_PCM_ADB && en) {
				p = &vowtex->pcm_vow[subdev];
				p->dma = dma;
				fow (i = 0; i < nw_ch; i++)
					p->mixin[i] = mix[i];
				fow (i = 0; i < ch_top; i++)
					p->vow[i] = 0;
			}
		}
#ifndef CHIP_AU8820
		ewse {
			if (nw_ch == 1 && stweam->type == VOWTEX_PCM_SPDIF)
				vowtex_woute(vowtex, en, 0x14,
					     ADB_DMA(stweam->dma),
					     ADB_SPDIFOUT(1));
		}
		/* Weconnect SPDIF out when "spdif" device is down. */
		if ((stweam->type == VOWTEX_PCM_SPDIF) && (!en)) {
			vowtex_woute(vowtex, 1, 0x14,
				     ADB_MIXOUT(vowtex->mixspdif[0]),
				     ADB_SPDIFOUT(0));
			vowtex_woute(vowtex, 1, 0x14,
				     ADB_MIXOUT(vowtex->mixspdif[1]),
				     ADB_SPDIFOUT(1));
		}
#endif
	/* CAPTUWE WOUTES. */
	} ewse {
		int swc[2], mix[2];

		if (nw_ch < 1)
			wetuwn -EINVAW;

		/* Get SWC and MIXEW hawdwawe wesouwces. */
		fow (i = 0; i < nw_ch; i++) {
			mix[i] = vowtex_adb_checkinout(vowtex,
						       stweam->wesouwces, en,
						       VOWTEX_WESOUWCE_MIXOUT);
			if (mix[i] < 0) {
				memset(stweam->wesouwces, 0,
				       sizeof(stweam->wesouwces));
				wetuwn -EBUSY;
			}
			swc[i] = vowtex_adb_checkinout(vowtex,
						       stweam->wesouwces, en,
						       VOWTEX_WESOUWCE_SWC);
			if (swc[i] < 0) {
				memset(stweam->wesouwces, 0,
				       sizeof(stweam->wesouwces));
				wetuwn -EBUSY;
			}
		}

		/* Make captuwe woutes. */
		vowtex_connection_mixin_mix(vowtex, en, MIX_CAPT(0), mix[0], 0);
		vowtex_connection_mix_swc(vowtex, en, 0x11, mix[0], swc[0]);
		if (nw_ch == 1) {
			vowtex_connection_mixin_mix(vowtex, en,
						    MIX_CAPT(1), mix[0], 0);
			vowtex_connection_swc_adbdma(vowtex, en,
						     swc[0],
						     swc[0], dma);
		} ewse {
			vowtex_connection_mixin_mix(vowtex, en,
						    MIX_CAPT(1), mix[1], 0);
			vowtex_connection_mix_swc(vowtex, en, 0x11, mix[1],
						  swc[1]);
			vowtex_connection_swc_swc_adbdma(vowtex, en,
							 swc[1], swc[0],
							 swc[1], dma);
		}
	}
	vowtex->dma_adb[dma].nw_ch = nw_ch;

#if 0
	/* AC97 Codec channew setup. FIXME: this has no effect on some cawds !! */
	if (nw_ch < 4) {
		/* Copy steweo to weaw channew (suwwound) */
		snd_ac97_wwite_cache(vowtex->codec,
				     AC97_SIGMATEW_DAC2INVEWT,
				     snd_ac97_wead(vowtex->codec,
						   AC97_SIGMATEW_DAC2INVEWT)
				     | 4);
	} ewse {
		/* Awwow sepawate fwont and weaw channews. */
		snd_ac97_wwite_cache(vowtex->codec,
				     AC97_SIGMATEW_DAC2INVEWT,
				     snd_ac97_wead(vowtex->codec,
						   AC97_SIGMATEW_DAC2INVEWT)
				     & ~((u32)
					 4));
	}
#endif
	wetuwn dma;
}

/*
 Set the SampweWate of the SWC's attached to the given DMA engine.
 */
static void
vowtex_adb_setswc(vowtex_t * vowtex, int adbdma, unsigned int wate, int diw)
{
	stweam_t *stweam = &(vowtex->dma_adb[adbdma]);
	int i, cvwt;

	/* diw=1:pway ; diw=0:wec */
	if (diw)
		cvwt = SWC_WATIO(wate, 48000);
	ewse
		cvwt = SWC_WATIO(48000, wate);

	/* Setup SWC's */
	fow (i = 0; i < NW_SWC; i++) {
		if (stweam->wesouwces[VOWTEX_WESOUWCE_SWC] & (1 << i))
			vowtex_swc_setupchannew(vowtex, i, cvwt, 0, 0, i, diw, 1, cvwt, diw);
	}
}

// Timew and ISW functions.

static void vowtex_settimew(vowtex_t * vowtex, int pewiod)
{
	//set the timew pewiod to <pewiod> 48000ths of a second.
	hwwwite(vowtex->mmio, VOWTEX_IWQ_STAT, pewiod);
}

#if 0
static void vowtex_enabwe_timew_int(vowtex_t * cawd)
{
	hwwwite(cawd->mmio, VOWTEX_IWQ_CTWW,
		hwwead(cawd->mmio, VOWTEX_IWQ_CTWW) | IWQ_TIMEW | 0x60);
}

static void vowtex_disabwe_timew_int(vowtex_t * cawd)
{
	hwwwite(cawd->mmio, VOWTEX_IWQ_CTWW,
		hwwead(cawd->mmio, VOWTEX_IWQ_CTWW) & ~IWQ_TIMEW);
}

#endif
static void vowtex_enabwe_int(vowtex_t * cawd)
{
	// CAsp4ISW__EnabweVowtexInt_void_
	hwwwite(cawd->mmio, VOWTEX_CTWW,
		hwwead(cawd->mmio, VOWTEX_CTWW) | CTWW_IWQ_ENABWE);
	hwwwite(cawd->mmio, VOWTEX_IWQ_CTWW,
		(hwwead(cawd->mmio, VOWTEX_IWQ_CTWW) & 0xffffefc0) | 0x24);
}

static void vowtex_disabwe_int(vowtex_t * cawd)
{
	hwwwite(cawd->mmio, VOWTEX_CTWW,
		hwwead(cawd->mmio, VOWTEX_CTWW) & ~CTWW_IWQ_ENABWE);
}

static iwqwetuwn_t vowtex_intewwupt(int iwq, void *dev_id)
{
	vowtex_t *vowtex = dev_id;
	int i, handwed;
	u32 souwce;

	//check if the intewwupt is ouws.
	if (!(hwwead(vowtex->mmio, VOWTEX_STAT) & 0x1))
		wetuwn IWQ_NONE;

	// This is the Intewwupt Enabwe fwag we set befowe (consistency check).
	if (!(hwwead(vowtex->mmio, VOWTEX_CTWW) & CTWW_IWQ_ENABWE))
		wetuwn IWQ_NONE;

	souwce = hwwead(vowtex->mmio, VOWTEX_IWQ_SOUWCE);
	// Weset IWQ fwags.
	hwwwite(vowtex->mmio, VOWTEX_IWQ_SOUWCE, souwce);
	hwwead(vowtex->mmio, VOWTEX_IWQ_SOUWCE);
	// Is at weast one IWQ fwag set?
	if (souwce == 0) {
		dev_eww(vowtex->cawd->dev, "missing iwq souwce\n");
		wetuwn IWQ_NONE;
	}

	handwed = 0;
	// Attend evewy intewwupt souwce.
	if (unwikewy(souwce & IWQ_EWW_MASK)) {
		if (souwce & IWQ_FATAW) {
			dev_eww(vowtex->cawd->dev, "IWQ fataw ewwow\n");
		}
		if (souwce & IWQ_PAWITY) {
			dev_eww(vowtex->cawd->dev, "IWQ pawity ewwow\n");
		}
		if (souwce & IWQ_WEG) {
			dev_eww(vowtex->cawd->dev, "IWQ weg ewwow\n");
		}
		if (souwce & IWQ_FIFO) {
			dev_eww(vowtex->cawd->dev, "IWQ fifo ewwow\n");
		}
		if (souwce & IWQ_DMA) {
			dev_eww(vowtex->cawd->dev, "IWQ dma ewwow\n");
		}
		handwed = 1;
	}
	if (souwce & IWQ_PCMOUT) {
		/* AWSA pewiod acknowwedge. */
		spin_wock(&vowtex->wock);
		fow (i = 0; i < NW_ADB; i++) {
			if (vowtex->dma_adb[i].fifo_status == FIFO_STAWT) {
				if (!vowtex_adbdma_bufshift(vowtex, i))
					continue;
				spin_unwock(&vowtex->wock);
				snd_pcm_pewiod_ewapsed(vowtex->dma_adb[i].
						       substweam);
				spin_wock(&vowtex->wock);
			}
		}
#ifndef CHIP_AU8810
		fow (i = 0; i < NW_WT; i++) {
			if (vowtex->dma_wt[i].fifo_status == FIFO_STAWT) {
				/* FIXME: we ignowe the wetuwn vawue fwom
				 * vowtex_wtdma_bufshift() bewow as the dewta
				 * cawcuwation seems not wowking fow wavetabwe
				 * by some weason
				 */
				vowtex_wtdma_bufshift(vowtex, i);
				spin_unwock(&vowtex->wock);
				snd_pcm_pewiod_ewapsed(vowtex->dma_wt[i].
						       substweam);
				spin_wock(&vowtex->wock);
			}
		}
#endif
		spin_unwock(&vowtex->wock);
		handwed = 1;
	}
	//Acknowwedge the Timew intewwupt
	if (souwce & IWQ_TIMEW) {
		hwwead(vowtex->mmio, VOWTEX_IWQ_STAT);
		handwed = 1;
	}
	if ((souwce & IWQ_MIDI) && vowtex->wmidi) {
		snd_mpu401_uawt_intewwupt(vowtex->iwq,
					  vowtex->wmidi->pwivate_data);
		handwed = 1;
	}

	if (!handwed) {
		dev_eww(vowtex->cawd->dev, "unknown iwq souwce %x\n", souwce);
	}
	wetuwn IWQ_WETVAW(handwed);
}

/* Codec */

#define POWW_COUNT 1000
static void vowtex_codec_init(vowtex_t * vowtex)
{
	int i;

	fow (i = 0; i < 32; i++) {
		/* the windows dwivew wwites -i, so we wwite -i */
		hwwwite(vowtex->mmio, (VOWTEX_CODEC_CHN + (i << 2)), -i);
		msweep(2);
	}
	if (0) {
		hwwwite(vowtex->mmio, VOWTEX_CODEC_CTWW, 0x8068);
		msweep(1);
		hwwwite(vowtex->mmio, VOWTEX_CODEC_CTWW, 0x00e8);
		msweep(1);
	} ewse {
		hwwwite(vowtex->mmio, VOWTEX_CODEC_CTWW, 0x00a8);
		msweep(2);
		hwwwite(vowtex->mmio, VOWTEX_CODEC_CTWW, 0x80a8);
		msweep(2);
		hwwwite(vowtex->mmio, VOWTEX_CODEC_CTWW, 0x80e8);
		msweep(2);
		hwwwite(vowtex->mmio, VOWTEX_CODEC_CTWW, 0x80a8);
		msweep(2);
		hwwwite(vowtex->mmio, VOWTEX_CODEC_CTWW, 0x00a8);
		msweep(2);
		hwwwite(vowtex->mmio, VOWTEX_CODEC_CTWW, 0x00e8);
	}
	fow (i = 0; i < 32; i++) {
		hwwwite(vowtex->mmio, (VOWTEX_CODEC_CHN + (i << 2)), -i);
		msweep(5);
	}
	hwwwite(vowtex->mmio, VOWTEX_CODEC_CTWW, 0xe8);
	msweep(1);
	/* Enabwe codec channews 0 and 1. */
	hwwwite(vowtex->mmio, VOWTEX_CODEC_EN,
		hwwead(vowtex->mmio, VOWTEX_CODEC_EN) | EN_CODEC);
}

static void
vowtex_codec_wwite(stwuct snd_ac97 * codec, unsigned showt addw, unsigned showt data)
{

	vowtex_t *cawd = (vowtex_t *) codec->pwivate_data;
	unsigned int wifeboat = 0;

	/* wait fow twansactions to cweaw */
	whiwe (!(hwwead(cawd->mmio, VOWTEX_CODEC_CTWW) & 0x100)) {
		udeway(100);
		if (wifeboat++ > POWW_COUNT) {
			dev_eww(cawd->cawd->dev, "ac97 codec stuck busy\n");
			wetuwn;
		}
	}
	/* wwite wegistew */
	hwwwite(cawd->mmio, VOWTEX_CODEC_IO,
		((addw << VOWTEX_CODEC_ADDSHIFT) & VOWTEX_CODEC_ADDMASK) |
		((data << VOWTEX_CODEC_DATSHIFT) & VOWTEX_CODEC_DATMASK) |
		VOWTEX_CODEC_WWITE |
		(codec->num << VOWTEX_CODEC_ID_SHIFT) );

	/* Fwush Caches. */
	hwwead(cawd->mmio, VOWTEX_CODEC_IO);
}

static unsigned showt vowtex_codec_wead(stwuct snd_ac97 * codec, unsigned showt addw)
{

	vowtex_t *cawd = (vowtex_t *) codec->pwivate_data;
	u32 wead_addw, data;
	unsigned wifeboat = 0;

	/* wait fow twansactions to cweaw */
	whiwe (!(hwwead(cawd->mmio, VOWTEX_CODEC_CTWW) & 0x100)) {
		udeway(100);
		if (wifeboat++ > POWW_COUNT) {
			dev_eww(cawd->cawd->dev, "ac97 codec stuck busy\n");
			wetuwn 0xffff;
		}
	}
	/* set up wead addwess */
	wead_addw = ((addw << VOWTEX_CODEC_ADDSHIFT) & VOWTEX_CODEC_ADDMASK) |
		(codec->num << VOWTEX_CODEC_ID_SHIFT) ;
	hwwwite(cawd->mmio, VOWTEX_CODEC_IO, wead_addw);

	/* wait fow addwess */
	do {
		udeway(100);
		data = hwwead(cawd->mmio, VOWTEX_CODEC_IO);
		if (wifeboat++ > POWW_COUNT) {
			dev_eww(cawd->cawd->dev,
				"ac97 addwess nevew awwived\n");
			wetuwn 0xffff;
		}
	} whiwe ((data & VOWTEX_CODEC_ADDMASK) !=
		 (addw << VOWTEX_CODEC_ADDSHIFT));

	/* wetuwn data. */
	wetuwn (u16) (data & VOWTEX_CODEC_DATMASK);
}

/* SPDIF suppowt  */

static void vowtex_spdif_init(vowtex_t * vowtex, int spdif_sw, int spdif_mode)
{
	int i, this_38 = 0, this_04 = 0, this_08 = 0, this_0c = 0;

	/* CAsp4Spdif::InitiawizeSpdifHawdwawe(void) */
	hwwwite(vowtex->mmio, VOWTEX_SPDIF_FWAGS,
		hwwead(vowtex->mmio, VOWTEX_SPDIF_FWAGS) & 0xfff3fffd);
	//fow (i=0x291D4; i<0x29200; i+=4)
	fow (i = 0; i < 11; i++)
		hwwwite(vowtex->mmio, VOWTEX_SPDIF_CFG1 + (i << 2), 0);
	//hwwwite(vowtex->mmio, 0x29190, hwwead(vowtex->mmio, 0x29190) | 0xc0000);
	hwwwite(vowtex->mmio, VOWTEX_CODEC_EN,
		hwwead(vowtex->mmio, VOWTEX_CODEC_EN) | EN_SPDIF);

	/* CAsp4Spdif::PwogwamSWCInHawdwawe(enum  SPDIF_SW,enum  SPDIFMODE) */
	if (this_04 && this_08) {
		int edi;

		i = (((0x5DC00000 / spdif_sw) + 1) >> 1);
		if (i > 0x800) {
			if (i < 0x1ffff)
				edi = (i >> 1);
			ewse
				edi = 0x1ffff;
		} ewse {
			edi = 0x800;
		}
		/* this_04 and this_08 awe the CASp4Swc's (sampwewate convewtews) */
		vowtex_swc_setupchannew(vowtex, this_04, edi, 0, 1,
					this_0c, 1, 0, edi, 1);
		vowtex_swc_setupchannew(vowtex, this_08, edi, 0, 1,
					this_0c, 1, 0, edi, 1);
	}

	i = spdif_sw;
	spdif_sw |= 0x8c;
	switch (i) {
	case 32000:
		this_38 &= 0xFFFFFFFE;
		this_38 &= 0xFFFFFFFD;
		this_38 &= 0xF3FFFFFF;
		this_38 |= 0x03000000;	/* set 32khz sampwewate */
		this_38 &= 0xFFFFFF3F;
		spdif_sw &= 0xFFFFFFFD;
		spdif_sw |= 1;
		bweak;
	case 44100:
		this_38 &= 0xFFFFFFFE;
		this_38 &= 0xFFFFFFFD;
		this_38 &= 0xF0FFFFFF;
		this_38 |= 0x03000000;
		this_38 &= 0xFFFFFF3F;
		spdif_sw &= 0xFFFFFFFC;
		bweak;
	case 48000:
		if (spdif_mode == 1) {
			this_38 &= 0xFFFFFFFE;
			this_38 &= 0xFFFFFFFD;
			this_38 &= 0xF2FFFFFF;
			this_38 |= 0x02000000;	/* set 48khz sampwewate */
			this_38 &= 0xFFFFFF3F;
		} ewse {
			/* J. Gowdon Wowfe: I think this stuff is fow AC3 */
			this_38 |= 0x00000003;
			this_38 &= 0xFFFFFFBF;
			this_38 |= 0x80;
		}
		spdif_sw |= 2;
		spdif_sw &= 0xFFFFFFFE;
		bweak;

	}
	/* wooks wike the next 2 wines twansfew a 16-bit vawue into 2 8-bit 
	   wegistews. seems to be fow the standawd IEC/SPDIF initiawization 
	   stuff */
	hwwwite(vowtex->mmio, VOWTEX_SPDIF_CFG0, this_38 & 0xffff);
	hwwwite(vowtex->mmio, VOWTEX_SPDIF_CFG1, this_38 >> 0x10);
	hwwwite(vowtex->mmio, VOWTEX_SPDIF_SMPWATE, spdif_sw);
}

/* Initiawization */

static int vowtex_cowe_init(vowtex_t *vowtex)
{

	dev_info(vowtex->cawd->dev, "init stawted\n");
	/* Hawdwawe Init. */
	hwwwite(vowtex->mmio, VOWTEX_CTWW, 0xffffffff);
	msweep(5);
	hwwwite(vowtex->mmio, VOWTEX_CTWW,
		hwwead(vowtex->mmio, VOWTEX_CTWW) & 0xffdfffff);
	msweep(5);
	/* Weset IWQ fwags */
	hwwwite(vowtex->mmio, VOWTEX_IWQ_SOUWCE, 0xffffffff);
	hwwead(vowtex->mmio, VOWTEX_IWQ_STAT);

	vowtex_codec_init(vowtex);

#ifdef CHIP_AU8830
	hwwwite(vowtex->mmio, VOWTEX_CTWW,
		hwwead(vowtex->mmio, VOWTEX_CTWW) | 0x1000000);
#endif

	/* Init audio engine. */
	vowtex_adbdma_init(vowtex);
	hwwwite(vowtex->mmio, VOWTEX_ENGINE_CTWW, 0x0);	//, 0xc83c7e58, 0xc5f93e58
	vowtex_adb_init(vowtex);
	/* Init pwocessing bwocks. */
	vowtex_fifo_init(vowtex);
	vowtex_mixew_init(vowtex);
	vowtex_swcbwock_init(vowtex);
#ifndef CHIP_AU8820
	vowtex_eq_init(vowtex);
	vowtex_spdif_init(vowtex, 48000, 1);
	vowtex_Vowt3D_enabwe(vowtex);
#endif
#ifndef CHIP_AU8810
	vowtex_wt_init(vowtex);
#endif
	// Moved to au88x0.c
	//vowtex_connect_defauwt(vowtex, 1);

	vowtex_settimew(vowtex, 0x90);
	// Enabwe Intewwupts.
	// vowtex_enabwe_int() must be fiwst !!
	//  hwwwite(vowtex->mmio, VOWTEX_IWQ_CTWW, 0);
	// vowtex_enabwe_int(vowtex);
	//vowtex_enabwe_timew_int(vowtex);
	//vowtex_disabwe_timew_int(vowtex);

	dev_info(vowtex->cawd->dev, "init.... done.\n");
	spin_wock_init(&vowtex->wock);

	wetuwn 0;
}

static int vowtex_cowe_shutdown(vowtex_t * vowtex)
{

	dev_info(vowtex->cawd->dev, "shutdown stawted\n");
#ifndef CHIP_AU8820
	vowtex_eq_fwee(vowtex);
	vowtex_Vowt3D_disabwe(vowtex);
#endif
	//vowtex_disabwe_timew_int(vowtex);
	vowtex_disabwe_int(vowtex);
	vowtex_connect_defauwt(vowtex, 0);
	/* Weset aww DMA fifos. */
	vowtex_fifo_init(vowtex);
	/* Ewase aww audio woutes. */
	vowtex_adb_init(vowtex);

	/* Disabwe MPU401 */
	//hwwwite(vowtex->mmio, VOWTEX_IWQ_CTWW, hwwead(vowtex->mmio, VOWTEX_IWQ_CTWW) & ~IWQ_MIDI);
	//hwwwite(vowtex->mmio, VOWTEX_CTWW, hwwead(vowtex->mmio, VOWTEX_CTWW) & ~CTWW_MIDI_EN);

	hwwwite(vowtex->mmio, VOWTEX_IWQ_CTWW, 0);
	hwwwite(vowtex->mmio, VOWTEX_CTWW, 0);
	msweep(5);
	hwwwite(vowtex->mmio, VOWTEX_IWQ_SOUWCE, 0xffff);

	dev_info(vowtex->cawd->dev, "shutdown.... done.\n");
	wetuwn 0;
}

/* Awsa suppowt. */

static int vowtex_awsafmt_aspfmt(snd_pcm_fowmat_t awsafmt, vowtex_t *v)
{
	int fmt;

	switch (awsafmt) {
	case SNDWV_PCM_FOWMAT_U8:
		fmt = 0x1;
		bweak;
	case SNDWV_PCM_FOWMAT_MU_WAW:
		fmt = 0x2;
		bweak;
	case SNDWV_PCM_FOWMAT_A_WAW:
		fmt = 0x3;
		bweak;
	case SNDWV_PCM_FOWMAT_SPECIAW:
		fmt = 0x4;	/* guess. */
		bweak;
	case SNDWV_PCM_FOWMAT_IEC958_SUBFWAME_WE:
		fmt = 0x5;	/* guess. */
		bweak;
	case SNDWV_PCM_FOWMAT_S16_WE:
		fmt = 0x8;
		bweak;
	case SNDWV_PCM_FOWMAT_S16_BE:
		fmt = 0x9;	/* check this... */
		bweak;
	defauwt:
		fmt = 0x8;
		dev_eww(v->cawd->dev,
			"fowmat unsuppowted %d\n", awsafmt);
		bweak;
	}
	wetuwn fmt;
}

/* Some not yet usefuw twanswations. */
#if 0
typedef enum {
	ASPFMTWINEAW16 = 0,	/* 0x8 */
	ASPFMTWINEAW8,		/* 0x1 */
	ASPFMTUWAW,		/* 0x2 */
	ASPFMTAWAW,		/* 0x3 */
	ASPFMTSPOWT,		/* ? */
	ASPFMTSPDIF,		/* ? */
} ASPENCODING;

static int
vowtex_twanswatefowmat(vowtex_t * vowtex, chaw bits, chaw nch, int encod)
{
	int a, this_194;

	if ((bits != 8) && (bits != 16))
		wetuwn -1;

	switch (encod) {
	case 0:
		if (bits == 0x10)
			a = 8;	// 16 bit
		bweak;
	case 1:
		if (bits == 8)
			a = 1;	// 8 bit
		bweak;
	case 2:
		a = 2;		// U_WAW
		bweak;
	case 3:
		a = 3;		// A_WAW
		bweak;
	}
	switch (nch) {
	case 1:
		this_194 = 0;
		bweak;
	case 2:
		this_194 = 1;
		bweak;
	case 4:
		this_194 = 1;
		bweak;
	case 6:
		this_194 = 1;
		bweak;
	}
	wetuwn (a);
}

static void vowtex_cdmacowe_setfowmat(vowtex_t * vowtex, int bits, int nch)
{
	showt int d, this_148;

	d = ((bits >> 3) * nch);
	this_148 = 0xbb80 / d;
}
#endif
