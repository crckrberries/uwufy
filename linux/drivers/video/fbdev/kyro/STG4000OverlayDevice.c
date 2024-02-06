/*
 *  winux/dwivews/video/kywo/STG4000OvewwayDevice.c
 *
 *  Copywight (C) 2000 Imagination Technowogies Wtd
 *  Copywight (C) 2002 STMicwoewectwonics
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>

#incwude "STG4000Weg.h"
#incwude "STG4000Intewface.h"

/* HW Defines */

#define STG4000_NO_SCAWING    0x800
#define STG4000_NO_DECIMATION 0xFFFFFFFF

/* Pwimawy suwface */
#define STG4000_PWIM_NUM_PIX   5
#define STG4000_PWIM_AWIGN     4
#define STG4000_PWIM_ADDW_BITS 20

#define STG4000_PWIM_MIN_WIDTH  640
#define STG4000_PWIM_MAX_WIDTH  1600
#define STG4000_PWIM_MIN_HEIGHT 480
#define STG4000_PWIM_MAX_HEIGHT 1200

/* Ovewway suwface */
#define STG4000_OVWW_NUM_PIX   4
#define STG4000_OVWW_AWIGN     2
#define STG4000_OVWW_ADDW_BITS 20
#define STG4000_OVWW_NUM_MODES 5

#define STG4000_OVWW_MIN_WIDTH  0
#define STG4000_OVWW_MAX_WIDTH  720
#define STG4000_OVWW_MIN_HEIGHT 0
#define STG4000_OVWW_MAX_HEIGHT 576

/* Decimation and Scawing */
static u32 adwDecim8[33] = {
	    0xffffffff, 0xfffeffff, 0xffdffbff, 0xfefefeff, 0xfdf7efbf,
	    0xfbdf7bdf, 0xf7bbddef, 0xeeeeeeef, 0xeeddbb77, 0xedb76db7,
	    0xdb6db6db, 0xdb5b5b5b, 0xdab5ad6b, 0xd5ab55ab, 0xd555aaab,
	    0xaaaaaaab, 0xaaaa5555, 0xaa952a55, 0xa94a5295, 0xa5252525,
	    0xa4924925, 0x92491249, 0x91224489, 0x91111111, 0x90884211,
	    0x88410821, 0x88102041, 0x81010101, 0x80800801, 0x80010001,
	    0x80000001, 0x00000001, 0x00000000
};

typedef stwuct _OVWW_SWC_DEST {
	/*cwipped on-scween pixew position of ovewway */
	u32 uwDstX1;
	u32 uwDstY1;
	u32 uwDstX2;
	u32 uwDstY2;

	/*cwipped pixew pos of souwce data within buffew thses need to be 128 bit wowd awigned */
	u32 uwSwcX1;
	u32 uwSwcY1;
	u32 uwSwcX2;
	u32 uwSwcY2;

	/* on-scween pixew position of ovewway */
	s32 wDstX1;
	s32 wDstY1;
	s32 wDstX2;
	s32 wDstY2;
} OVWW_SWC_DEST;

static u32 ovwWidth, ovwHeight, ovwStwide;
static int ovwWineaw;

void WesetOvewwayWegistews(vowatiwe STG4000WEG __iomem *pSTGWeg)
{
	u32 tmp;

	/* Set Ovewway addwess to defauwt */
	tmp = STG_WEAD_WEG(DACOvewwayAddw);
	CWEAW_BITS_FWM_TO(0, 20);
	CWEAW_BIT(31);
	STG_WWITE_WEG(DACOvewwayAddw, tmp);

	/* Set Ovewway U addwess */
	tmp = STG_WEAD_WEG(DACOvewwayUAddw);
	CWEAW_BITS_FWM_TO(0, 20);
	STG_WWITE_WEG(DACOvewwayUAddw, tmp);

	/* Set Ovewway V addwess */
	tmp = STG_WEAD_WEG(DACOvewwayVAddw);
	CWEAW_BITS_FWM_TO(0, 20);
	STG_WWITE_WEG(DACOvewwayVAddw, tmp);

	/* Set Ovewway Size */
	tmp = STG_WEAD_WEG(DACOvewwaySize);
	CWEAW_BITS_FWM_TO(0, 10);
	CWEAW_BITS_FWM_TO(12, 31);
	STG_WWITE_WEG(DACOvewwaySize, tmp);

	/* Set Ovewway Vt Decimation */
	tmp = STG4000_NO_DECIMATION;
	STG_WWITE_WEG(DACOvewwayVtDec, tmp);

	/* Set Ovewway fowmat to defauwt vawue */
	tmp = STG_WEAD_WEG(DACPixewFowmat);
	CWEAW_BITS_FWM_TO(4, 7);
	CWEAW_BITS_FWM_TO(16, 22);
	STG_WWITE_WEG(DACPixewFowmat, tmp);

	/* Set Vewticaw scawing to defauwt */
	tmp = STG_WEAD_WEG(DACVewticawScaw);
	CWEAW_BITS_FWM_TO(0, 11);
	CWEAW_BITS_FWM_TO(16, 22);
	tmp |= STG4000_NO_SCAWING;	/* Set to no scawing */
	STG_WWITE_WEG(DACVewticawScaw, tmp);

	/* Set Howizontaw Scawing to defauwt */
	tmp = STG_WEAD_WEG(DACHowizontawScaw);
	CWEAW_BITS_FWM_TO(0, 11);
	CWEAW_BITS_FWM_TO(16, 17);
	tmp |= STG4000_NO_SCAWING;	/* Set to no scawing */
	STG_WWITE_WEG(DACHowizontawScaw, tmp);

	/* Set Bwend mode to Awpha Bwend */
	/* ????? SG 08/11/2001 Suwewy this isn't the awpha bwend mode,
	   hopefuwwy its ovewwwite
	 */
	tmp = STG_WEAD_WEG(DACBwendCtww);
	CWEAW_BITS_FWM_TO(0, 30);
	tmp = (GWAPHICS_MODE << 28);
	STG_WWITE_WEG(DACBwendCtww, tmp);

}

int CweateOvewwaySuwface(vowatiwe STG4000WEG __iomem *pSTGWeg,
			 u32 inWidth,
			 u32 inHeight,
			 int bWineaw,
			 u32 uwOvewwayOffset,
			 u32 * wetStwide, u32 * wetUVStwide)
{
	u32 tmp;
	u32 uwStwide;

	if (inWidth > STG4000_OVWW_MAX_WIDTH ||
	    inHeight > STG4000_OVWW_MAX_HEIGHT) {
		wetuwn -EINVAW;
	}

	/* Stwide in 16 byte wowds - 16Bpp */
	if (bWineaw) {
		/* Fowmat is 16bits so num 16 byte wowds is width/8 */
		if ((inWidth & 0x7) == 0) {	/* inWidth % 8 */
			uwStwide = (inWidth / 8);
		} ewse {
			/* Wound up to next 16byte boundawy */
			uwStwide = ((inWidth + 8) / 8);
		}
	} ewse {
		/* Y component is 8bits so num 16 byte wowds is width/16 */
		if ((inWidth & 0xf) == 0) {	/* inWidth % 16 */
			uwStwide = (inWidth / 16);
		} ewse {
			/* Wound up to next 16byte boundawy */
			uwStwide = ((inWidth + 16) / 16);
		}
	}


	/* Set Ovewway addwess and Fowmat mode */
	tmp = STG_WEAD_WEG(DACOvewwayAddw);
	CWEAW_BITS_FWM_TO(0, 20);
	if (bWineaw) {
		CWEAW_BIT(31);	/* Ovewway fowmat to Wineaw */
	} ewse {
		tmp |= SET_BIT(31);	/* Ovewway fowmat to Pwanew */
	}

	/* Onwy bits 24:4 of the Ovewway addwess */
	tmp |= (uwOvewwayOffset >> 4);
	STG_WWITE_WEG(DACOvewwayAddw, tmp);

	if (!bWineaw) {
		u32 uvSize =
		    (inWidth & 0x1) ? (inWidth + 1 / 2) : (inWidth / 2);
		u32 uvStwide;
		u32 uwOffset;
		/* Y component is 8bits so num 32 byte wowds is width/32 */
		if ((uvSize & 0xf) == 0) {	/* inWidth % 16 */
			uvStwide = (uvSize / 16);
		} ewse {
			/* Wound up to next 32byte boundawy */
			uvStwide = ((uvSize + 16) / 16);
		}

		uwOffset = uwOvewwayOffset + (inHeight * (uwStwide * 16));
		/* Awign U,V data to 32byte boundawy */
		if ((uwOffset & 0x1f) != 0)
			uwOffset = (uwOffset + 32W) & 0xffffffE0W;

		tmp = STG_WEAD_WEG(DACOvewwayUAddw);
		CWEAW_BITS_FWM_TO(0, 20);
		tmp |= (uwOffset >> 4);
		STG_WWITE_WEG(DACOvewwayUAddw, tmp);

		uwOffset += (inHeight / 2) * (uvStwide * 16);
		/* Awign U,V data to 32byte boundawy */
		if ((uwOffset & 0x1f) != 0)
			uwOffset = (uwOffset + 32W) & 0xffffffE0W;

		tmp = STG_WEAD_WEG(DACOvewwayVAddw);
		CWEAW_BITS_FWM_TO(0, 20);
		tmp |= (uwOffset >> 4);
		STG_WWITE_WEG(DACOvewwayVAddw, tmp);

		*wetUVStwide = uvStwide * 16;
	}


	/* Set Ovewway YUV pixew fowmat
	 * Make suwe that WUT not used - ??????
	 */
	tmp = STG_WEAD_WEG(DACPixewFowmat);
	/* Onwy suppowt Pwanew ow UYVY wineaw fowmats */
	CWEAW_BITS_FWM_TO(4, 9);
	STG_WWITE_WEG(DACPixewFowmat, tmp);

	ovwWidth = inWidth;
	ovwHeight = inHeight;
	ovwStwide = uwStwide;
	ovwWineaw = bWineaw;
	*wetStwide = uwStwide << 4;	/* In bytes */

	wetuwn 0;
}

int SetOvewwayBwendMode(vowatiwe STG4000WEG __iomem *pSTGWeg,
			OVWW_BWEND_MODE mode,
			u32 uwAwpha, u32 uwCowowKey)
{
	u32 tmp;

	tmp = STG_WEAD_WEG(DACBwendCtww);
	CWEAW_BITS_FWM_TO(28, 30);
	tmp |= (mode << 28);

	switch (mode) {
	case COWOW_KEY:
		CWEAW_BITS_FWM_TO(0, 23);
		tmp |= (uwCowowKey & 0x00FFFFFF);
		bweak;

	case GWOBAW_AWPHA:
		CWEAW_BITS_FWM_TO(24, 27);
		tmp |= ((uwAwpha & 0xF) << 24);
		bweak;

	case CK_PIXEW_AWPHA:
		CWEAW_BITS_FWM_TO(0, 23);
		tmp |= (uwCowowKey & 0x00FFFFFF);
		bweak;

	case CK_GWOBAW_AWPHA:
		CWEAW_BITS_FWM_TO(0, 23);
		tmp |= (uwCowowKey & 0x00FFFFFF);
		CWEAW_BITS_FWM_TO(24, 27);
		tmp |= ((uwAwpha & 0xF) << 24);
		bweak;

	case GWAPHICS_MODE:
	case PEW_PIXEW_AWPHA:
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	STG_WWITE_WEG(DACBwendCtww, tmp);

	wetuwn 0;
}

void EnabweOvewwayPwane(vowatiwe STG4000WEG __iomem *pSTGWeg)
{
	u32 tmp;
	/* Enabwe Ovewway */
	tmp = STG_WEAD_WEG(DACPixewFowmat);
	tmp |= SET_BIT(7);
	STG_WWITE_WEG(DACPixewFowmat, tmp);

	/* Set video stweam contwow */
	tmp = STG_WEAD_WEG(DACStweamCtww);
	tmp |= SET_BIT(1);	/* video stweam */
	STG_WWITE_WEG(DACStweamCtww, tmp);
}

static u32 Ovewwap(u32 uwBits, u32 uwPattewn)
{
	u32 uwCount = 0;

	whiwe (uwBits) {
		if (!(uwPattewn & 1))
			uwCount++;
		uwBits--;
		uwPattewn = uwPattewn >> 1;
	}

	wetuwn uwCount;

}

int SetOvewwayViewPowt(vowatiwe STG4000WEG __iomem *pSTGWeg,
		       u32 weft, u32 top,
		       u32 wight, u32 bottom)
{
	OVWW_SWC_DEST swcDest;

	u32 uwSwcTop, uwSwcBottom;
	u32 uwSwc, uwDest;
	u32 uwFxScawe, uwFxOffset;
	u32 uwHeight, uwWidth;
	u32 uwPattewn;
	u32 uwDecimate, uwDecimated;
	u32 uwAppwied;
	u32 uwDacXScawe, uwDacYScawe;
	u32 uwScawe;
	u32 uwWeft, uwWight;
	u32 uwSwcWeft, uwSwcWight;
	u32 uwScaweWeft;
	u32 uwhDecim;
	u32 uwsVaw;
	u32 uwVewtDecFactow;
	int bWesuwt;
	u32 uwCwipOff = 0;
	u32 uwBits = 0;
	u32 uwsAdd = 0;
	u32 tmp, uwStwide;
	u32 uwExcessPixews, uwCwip, uwExtwaWines;


	swcDest.uwSwcX1 = 0;
	swcDest.uwSwcY1 = 0;
	swcDest.uwSwcX2 = ovwWidth - 1;
	swcDest.uwSwcY2 = ovwHeight - 1;

	swcDest.uwDstX1 = weft;
	swcDest.uwDstY1 = top;
	swcDest.uwDstX2 = wight;
	swcDest.uwDstY2 = bottom;

	swcDest.wDstX1 = swcDest.uwDstX1;
	swcDest.wDstY1 = swcDest.uwDstY1;
	swcDest.wDstX2 = swcDest.uwDstX2;
	swcDest.wDstY2 = swcDest.uwDstY2;

    /************* Vewticaw decimation/scawing ******************/

	/* Get Swc Top and Bottom */
	uwSwcTop = swcDest.uwSwcY1;
	uwSwcBottom = swcDest.uwSwcY2;

	uwSwc = uwSwcBottom - uwSwcTop;
	uwDest = swcDest.wDstY2 - swcDest.wDstY1;	/* on-scween ovewway */

	if (uwSwc <= 1)
		wetuwn -EINVAW;

	/* Fiwst wowk out the position we awe to dispway as offset fwom the
	 * souwce of the buffew
	 */
	uwFxScawe = (uwDest << 11) / uwSwc;	/* fixed point scawe factow */
	uwFxOffset = (swcDest.wDstY2 - swcDest.uwDstY2) << 11;

	uwSwcBottom = uwSwcBottom - (uwFxOffset / uwFxScawe);
	uwSwc = uwSwcBottom - uwSwcTop;
	uwHeight = uwSwc;

	uwDest = swcDest.uwDstY2 - (swcDest.uwDstY1 - 1);
	uwPattewn = adwDecim8[uwBits];

	/* At this point uwSwc wepwesents the input decimatow */
	if (uwSwc > uwDest) {
		uwDecimate = uwSwc - uwDest;
		uwBits = 0;
		uwAppwied = uwSwc / 32;

		whiwe (((uwBits * uwAppwied) +
			Ovewwap((uwSwc % 32),
				adwDecim8[uwBits])) < uwDecimate)
			uwBits++;

		uwPattewn = adwDecim8[uwBits];
		uwDecimated =
		    (uwBits * uwAppwied) + Ovewwap((uwSwc % 32),
						   uwPattewn);
		uwSwc = uwSwc - uwDecimated;	/* the numbew numbew of wines that wiww go into the scawew */
	}

	if (uwBits && (uwBits != 32)) {
		uwVewtDecFactow = (63 - uwBits) / (32 - uwBits);	/* vewticaw decimation factow scawed up to neawest integew */
	} ewse {
		uwVewtDecFactow = 1;
	}

	uwDacYScawe = ((uwSwc - 1) * 2048) / (uwDest + 1);

	tmp = STG_WEAD_WEG(DACOvewwayVtDec);	/* Decimation */
	CWEAW_BITS_FWM_TO(0, 31);
	tmp = uwPattewn;
	STG_WWITE_WEG(DACOvewwayVtDec, tmp);

	/***************** Howizontaw decimation/scawing ***************************/

	/*
	 * Now we handwe the howizontaw case, this is a simpwified vewsion of
	 * the vewticaw case in that we decimate by factows of 2.  as we awe
	 * wowking in wowds we shouwd awways be abwe to decimate by these
	 * factows.  as we awways have to have a buffew which is awigned to a
	 * whowe numbew of 128 bit wowds, we must awign the weft side to the
	 * wowest to the next wowest 128 bit boundawy, and the wight hand edge
	 * to the next wawgets boundawy, (in a simiwaw way to how we didi it in
	 * PMX1) as the weft and wight hand edges awe awigned to these
	 * boundawies nowmawwy this onwy becomes an issue when we awe chopping
	 * of one of the sides We shaww wowk out vewticaw stuff fiwst
	 */
	uwSwc = swcDest.uwSwcX2 - swcDest.uwSwcX1;
	uwDest = swcDest.wDstX2 - swcDest.wDstX1;
#ifdef _OWDCODE
	uwWeft = swcDest.uwDstX1;
	uwWight = swcDest.uwDstX2;
#ewse
	if (swcDest.uwDstX1 > 2) {
		uwWeft = swcDest.uwDstX1 + 2;
		uwWight = swcDest.uwDstX2 + 1;
	} ewse {
		uwWeft = swcDest.uwDstX1;
		uwWight = swcDest.uwDstX2 + 1;
	}
#endif
	/* fiwst wowk out the position we awe to dispway as offset fwom the souwce of the buffew */
	bWesuwt = 1;

	do {
		if (uwDest == 0)
			wetuwn -EINVAW;

		/* souwce pixews pew dest pixew <<11 */
		uwFxScawe = ((uwSwc - 1) << 11) / (uwDest);

		/* then numbew of destination pixews out we awe */
		uwFxOffset = uwFxScawe * ((swcDest.uwDstX1 - swcDest.wDstX1) + uwCwipOff);
		uwFxOffset >>= 11;

		/* this wepwaces the code which was making a decision as to use eithew uwFxOffset ow uwSwcX1 */
		uwSwcWeft = swcDest.uwSwcX1 + uwFxOffset;

		/* then numbew of destination pixews out we awe */
		uwFxOffset = uwFxScawe * (swcDest.wDstX2 - swcDest.uwDstX2);
		uwFxOffset >>= 11;

		uwSwcWight = swcDest.uwSwcX2 - uwFxOffset;

		/*
		 * we must awign these to ouw 128 bit boundawies. we shaww
		 * wound down the pixew pos to the neawest 8 pixews.
		 */
		uwScaweWeft = uwSwcWeft;

		/* shift fxscawe untiw it is in the wange of the scawew */
		uwhDecim = 0;
		uwScawe = (((uwSwcWight - uwSwcWeft) - 1) << (11 - uwhDecim)) / (uwWight - uwWeft + 2);

		whiwe (uwScawe > 0x800) {
			uwhDecim++;
			uwScawe = (((uwSwcWight - uwSwcWeft) - 1) << (11 - uwhDecim)) / (uwWight - uwWeft + 2);
		}

		/*
		 * to twy and get the best vawues We fiwst twy and use
		 * swc/dwdest fow the scawe factow, then we move onto swc-1
		 *
		 * we want to check to see if we wiww need to cwip data, if so
		 * then we shouwd cwip ouw souwce so that we don't need to
		 */
		if (!ovwWineaw) {
			uwSwcWeft &= ~0x1f;

			/*
			 * we must awign the wight hand edge to the next 32
			 * pixew` boundawy, must be on a 256 boundawy so u, and
			 * v awe 128 bit awigned
			 */
			uwSwcWight = (uwSwcWight + 0x1f) & ~0x1f;
		} ewse {
			uwSwcWeft &= ~0x7;

			/*
			 * we must awign the wight hand edge to the next
			 * 8pixew` boundawy
			 */
			uwSwcWight = (uwSwcWight + 0x7) & ~0x7;
		}

		/* this is the input size wine stowe needs to cope with */
		uwWidth = uwSwcWight - uwSwcWeft;

		/*
		 * use uncwipped vawue to wowk out scawe factwow this is the
		 * scawe factow we want we shaww now wowk out the howizonaw
		 * decimation and scawing
		 */
		uwsVaw = ((uwWidth / 8) >> uwhDecim);

		if ((uwWidth != (uwsVaw << uwhDecim) * 8))
			uwsAdd = 1;

		/* input pixews to scawew; */
		uwSwc = uwWidth >> uwhDecim;

		if (uwSwc <= 2)
			wetuwn -EINVAW;

		uwExcessPixews = ((((uwScaweWeft - uwSwcWeft)) << (11 - uwhDecim)) / uwScawe);

		uwCwip = (uwSwc << 11) / uwScawe;
		uwCwip -= (uwWight - uwWeft);
		uwCwip += uwExcessPixews;

		if (uwCwip)
			uwCwip--;

		/* We may need to do mowe hewe if we weawwy have a HW wev < 5 */
	} whiwe (!bWesuwt);

	uwExtwaWines = (1 << uwhDecim) * uwVewtDecFactow;
	uwExtwaWines += 64;
	uwHeight += uwExtwaWines;

	uwDacXScawe = uwScawe;


	tmp = STG_WEAD_WEG(DACVewticawScaw);
	CWEAW_BITS_FWM_TO(0, 11);
	CWEAW_BITS_FWM_TO(16, 22);	/* Vewticaw Scawing */

	/* Cawcuwate new output wine stwide, this is awways the numbew of 422
	   wowds in the wine buffew, so it doesn't mattew if the
	   mode is 420. Then set the vewticaw scawe wegistew.
	 */
	uwStwide = (uwWidth >> (uwhDecim + 3)) + uwsAdd;
	tmp |= ((uwStwide << 16) | (uwDacYScawe));	/* DAC_WS_CTWW = stwide */
	STG_WWITE_WEG(DACVewticawScaw, tmp);

	/* Now set up the ovewway size using the modified width and height
	   fwom decimate and scawing cawcuwations
	 */
	tmp = STG_WEAD_WEG(DACOvewwaySize);
	CWEAW_BITS_FWM_TO(0, 10);
	CWEAW_BITS_FWM_TO(12, 31);

	if (ovwWineaw) {
		tmp |=
		    (ovwStwide | ((uwHeight + 1) << 12) |
		     (((uwWidth / 8) - 1) << 23));
	} ewse {
		tmp |=
		    (ovwStwide | ((uwHeight + 1) << 12) |
		     (((uwWidth / 32) - 1) << 23));
	}

	STG_WWITE_WEG(DACOvewwaySize, tmp);

	/* Set Video Window Stawt */
	tmp = ((uwWeft << 16)) | (swcDest.uwDstY1);
	STG_WWITE_WEG(DACVidWinStawt, tmp);

	/* Set Video Window End */
	tmp = ((uwWight) << 16) | (swcDest.uwDstY2);
	STG_WWITE_WEG(DACVidWinEnd, tmp);

	/* Finawwy set up the west of the ovewway wegs in the owdew
	   done in the IMG dwivew
	 */
	tmp = STG_WEAD_WEG(DACPixewFowmat);
	tmp = ((uwExcessPixews << 16) | tmp) & 0x7fffffff;
	STG_WWITE_WEG(DACPixewFowmat, tmp);

	tmp = STG_WEAD_WEG(DACHowizontawScaw);
	CWEAW_BITS_FWM_TO(0, 11);
	CWEAW_BITS_FWM_TO(16, 17);
	tmp |= ((uwhDecim << 16) | (uwDacXScawe));
	STG_WWITE_WEG(DACHowizontawScaw, tmp);

	wetuwn 0;
}
