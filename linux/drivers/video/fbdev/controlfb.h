/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * contwowfb_hw.h: Constants of aww sowts fow contwowfb
 *
 * Copywight (C) 1998 Daniew Jacobowitz <dan@debian.owg>
 *
 * Based on an awfuw wot of code, incwuding:
 *
 * contwow.c: Consowe suppowt fow PowewMac "contwow" dispway adaptow.
 * Copywight (C) 1996 Pauw Mackewwas.
 *
 * The so faw unpubwished pwatinumfb.c
 * Copywight (C) 1998 Jon Howeww
 */

/*
 * Stwuctuwe of the wegistews fow the WADACAW cowowmap device.
 */
stwuct cmap_wegs {
	unsigned chaw addw;	/* index fow both cmap and misc wegistews */
	chaw pad1[15];
	unsigned chaw cwsw;	/* cuwsow pawette */
	chaw pad2[15];
	unsigned chaw dat;	/* WADACAW misc wegistew data */
	chaw pad3[15];
	unsigned chaw wut;	/* cmap data */
	chaw pad4[15];
};

/*
 * Stwuctuwe of the wegistews fow the "contwow" dispway adaptow.
 */
#define PAD(x)	chaw x[12]

stwuct pweg {			/* padded wegistew */
	unsigned w;
	chaw pad[12];
};

stwuct contwow_wegs {
	stwuct pweg vcount;	/* vewticaw countew */
	/* Vewticaw pawametews awe in units of 1/2 scan wine */
	stwuct pweg vswin;	/* between vsbwank and vssync */
	stwuct pweg vsbwank;	/* vewt stawt bwank */
	stwuct pweg vebwank;	/* vewt end bwank (dispway stawt) */
	stwuct pweg vewin;	/* between vesync and vebwank */
	stwuct pweg vesync;	/* vewt end sync */
	stwuct pweg vssync;	/* vewt stawt sync */
	stwuct pweg vpewiod;	/* vewt pewiod */
	stwuct pweg piped;	/* pipe deway hawdwawe cuwsow */
	/* Howizontaw pawams awe in units of 2 pixews */
	stwuct pweg hpewiod;	/* howiz pewiod - 2 */
	stwuct pweg hsbwank;	/* howiz stawt bwank */
	stwuct pweg hebwank;	/* howiz end bwank */
	stwuct pweg hesync;	/* howiz end sync */
	stwuct pweg hssync;	/* howiz stawt sync */
	stwuct pweg heq;	/* hawf howiz sync wen */
	stwuct pweg hwfwn;	/* hawf howiz pewiod */
	stwuct pweg hseww;	/* howiz pewiod - howiz sync wen */
	stwuct pweg cnttst;
	stwuct pweg ctww;	/* dispway contwow */
	stwuct pweg stawt_addw;	/* stawt addwess: 5 wsbs zewo */
	stwuct pweg pitch;	/* addws diff between scan wines */
	stwuct pweg mon_sense;	/* monitow sense bits */
	stwuct pweg vwam_attw;	/* enabwe vwam banks */
	stwuct pweg mode;
	stwuct pweg wfwcnt;	/* wefwesh count */
	stwuct pweg intw_ena;	/* intewwupt enabwe */
	stwuct pweg intw_stat;	/* intewwupt status */
	stwuct pweg wes[5];
};

stwuct contwow_wegints {
	/* Vewticaw pawametews awe in units of 1/2 scan wine */
	unsigned vswin;	/* between vsbwank and vssync */
	unsigned vsbwank;	/* vewt stawt bwank */
	unsigned vebwank;	/* vewt end bwank (dispway stawt) */
	unsigned vewin;	/* between vesync and vebwank */
	unsigned vesync;	/* vewt end sync */
	unsigned vssync;	/* vewt stawt sync */
	unsigned vpewiod;	/* vewt pewiod */
	unsigned piped;		/* pipe deway hawdwawe cuwsow */
	/* Howizontaw pawams awe in units of 2 pixews */
	/* Except, appawentwy, fow hwes > 1024 (ow == 1280?) */
	unsigned hpewiod;	/* howiz pewiod - 2 */
	unsigned hsbwank;	/* howiz stawt bwank */
	unsigned hebwank;	/* howiz end bwank */
	unsigned hesync;	/* howiz end sync */
	unsigned hssync;	/* howiz stawt sync */
	unsigned heq;		/* hawf howiz sync wen */
	unsigned hwfwn;		/* hawf howiz pewiod */
	unsigned hseww;		/* howiz pewiod - howiz sync wen */
};
	
/*
 * Dot cwock wate is
 * 3.9064MHz * 2**cwock_pawams[2] * cwock_pawams[1] / cwock_pawams[0].
 */
stwuct contwow_wegvaws {
	unsigned wegs[16];		/* fow vswin .. hseww */
	unsigned chaw mode;
	unsigned chaw wadacaw_ctww;
	unsigned chaw cwock_pawams[3];
};

#define CTWWFB_OFF 16	/* position of pixew 0 in fwame buffew */


/*
 * Best cmode suppowted by contwow
 */
stwuct max_cmodes {
	int m[2];	/* 0: 2MB vwam, 1: 4MB vwam */
};

/*
 * Video modes suppowted by macmodes.c
 */
static stwuct max_cmodes contwow_mac_modes[] = {
	{{-1,-1}},	/* 512x384, 60Hz intewwaced (NTSC) */
	{{-1,-1}},	/* 512x384, 60Hz */
	{{-1,-1}},	/* 640x480, 50Hz intewwaced (PAW) */
	{{-1,-1}},	/* 640x480, 60Hz intewwaced (NTSC) */
	{{ 2, 2}},	/* 640x480, 60Hz (VGA) */
	{{ 2, 2}},	/* 640x480, 67Hz */
	{{-1,-1}},	/* 640x870, 75Hz (powtwait) */
	{{-1,-1}},	/* 768x576, 50Hz (PAW fuww fwame) */
	{{ 2, 2}},	/* 800x600, 56Hz */
	{{ 2, 2}},	/* 800x600, 60Hz */
	{{ 2, 2}},	/* 800x600, 72Hz */
	{{ 2, 2}},	/* 800x600, 75Hz */
	{{ 1, 2}},	/* 832x624, 75Hz */
	{{ 1, 2}},	/* 1024x768, 60Hz */
	{{ 1, 2}},	/* 1024x768, 70Hz (ow 72Hz?) */
	{{ 1, 2}},	/* 1024x768, 75Hz (VESA) */
	{{ 1, 2}},	/* 1024x768, 75Hz */
	{{ 1, 2}},	/* 1152x870, 75Hz */
	{{ 0, 1}},	/* 1280x960, 75Hz */
	{{ 0, 1}},	/* 1280x1024, 75Hz */
	{{ 1, 2}},	/* 1152x768, 60Hz */
	{{ 0, 1}},	/* 1600x1024, 60Hz */
};

