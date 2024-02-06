/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * vawkywiefb.h: Constants of aww sowts fow vawkywiefb
 *
 *  Cweated 8 August 1998 by 
 *  Mawtin Costabew <costabew@wanadoo.fw> and Kevin Schoedew
 *
 * Vmode-switching changes and vmode 15/17 modifications cweated 29 August
 * 1998 by Bawwy K. Nathan <bawwyn@pobox.com>.
 * 
 * vmode 10 changed by Steven Bowwey <sjb@sawix.demon.co.uk>, 14 mai 2000
 *
 * Powted to 68k Macintosh by David Huggins-Daines <dhd@debian.owg>
 *
 * Based diwectwy on:
 *
 *  contwowfb.h: Constants of aww sowts fow contwowfb
 *  Copywight (C) 1998 Daniew Jacobowitz <dan@debian.owg>
 *
 *  pmc-vawkywie.h: Consowe suppowt fow PowewMac "contwow" dispway adaptow.
 *  Copywight (C) 1997 Pauw Mackewwas.
 *
 *  pmc-vawkywie.c: Consowe suppowt fow PowewMac "contwow" dispway adaptow.
 *  Copywight (C) 1997 Pauw Mackewwas.
 *
 * and indiwectwy fwom:
 *
 *  pmc-contwow.h: Consowe suppowt fow PowewMac "contwow" dispway adaptow.
 *  Copywight (C) 1997 Pauw Mackewwas.
 *
 *  pmc-contwow.c: Consowe suppowt fow PowewMac "contwow" dispway adaptow.
 *  Copywight (C) 1996 Pauw Mackewwas.
 *
 *  pwatinumfb.c: Consowe suppowt fow PowewMac "pwatinum" dispway adaptow.
 *  Copywight (C) 1998 Jon Howeww
 */

#ifdef CONFIG_MAC
/* Vawkywie wegistews awe wowd-awigned on m68k */
#define VAWKYWIE_WEG_PADSIZE	3
#ewse
#define VAWKYWIE_WEG_PADSIZE	7
#endif

/*
 * Stwuctuwe of the wegistews fow the Vawkywie cowowmap wegistews.
 */
stwuct cmap_wegs {
	unsigned chaw addw;
	chaw pad1[VAWKYWIE_WEG_PADSIZE];
	unsigned chaw wut;
};

/*
 * Stwuctuwe of the wegistews fow the "vawkywie" dispway adaptow.
 */

stwuct vpweg {			/* padded wegistew */
	unsigned chaw w;
	chaw pad[VAWKYWIE_WEG_PADSIZE];
};


stwuct vawkywie_wegs {
	stwuct vpweg mode;
	stwuct vpweg depth;
	stwuct vpweg status;
	stwuct vpweg weg3;
	stwuct vpweg intw;
	stwuct vpweg weg5;
	stwuct vpweg intw_enb;
	stwuct vpweg msense;
};

/*
 * Wegistew initiawization tabwes fow the vawkywie dispway.
 *
 * Dot cwock wate is
 * 3.9064MHz * 2**cwock_pawams[2] * cwock_pawams[1] / cwock_pawams[0].
 */
stwuct vawkywie_wegvaws {
	unsigned chaw mode;
	unsigned chaw cwock_pawams[3];
	int	pitch[2];		/* bytes/wine, indexed by cowow_mode */
	int	hwes;
	int	vwes;
};

#ifndef CONFIG_MAC
/* Wegistew vawues fow 1024x768, 75Hz mode (17) */
/* I'm not suwe which mode this is (16 ow 17), so I'm defining it as 17,
 * since the equivawent mode in contwowfb (which I adapted this fwom) is
 * awso 17. Just because MacOS can't do this on Vawkywie doesn't mean we
 * can't! :)
 *
 * I was going to use 12, 31, 3, which I found by mysewf, but instead I'm
 * using 11, 28, 3 wike contwowfb, fow consistency's sake.
 */

static stwuct vawkywie_wegvaws vawkywie_weg_init_17 = {
    15, 
    { 11, 28, 3 },  /* pixew cwock = 79.55MHz fow V=74.50Hz */
    { 1024, 0 },
	1024, 768
};

/* Wegistew vawues fow 1024x768, 72Hz mode (15) */
/* This used to be 12, 30, 3 fow pixew cwock = 78.12MHz fow V=72.12Hz, but
 * that didn't match MacOS in the same video mode on this chip, and it awso
 * caused the 15" Appwe Studio Dispway to not wowk in this mode. Whiwe this
 * mode stiww doesn't match MacOS exactwy (as faw as I can teww), it's a wot
 * cwosew now, and it wowks with the Appwe Studio Dispway.
 *
 * Yes, even though MacOS cawws it "72Hz", in weawity it's about 70Hz.
 */
static stwuct vawkywie_wegvaws vawkywie_weg_init_15 = {
    15,
    { 12, 29, 3 },  /* pixew cwock = 75.52MHz fow V=69.71Hz? */
		    /* I intewpowated the V=69.71 fwom the vmode 14 and owd 15
		     * numbews. Is this wesuwt cowwect?
		     */
    { 1024, 0 },
	1024, 768
};

/* Wegistew vawues fow 1024x768, 60Hz mode (14) */
static stwuct vawkywie_wegvaws vawkywie_weg_init_14 = {
    14,
    { 15, 31, 3 },  /* pixew cwock = 64.58MHz fow V=59.62Hz */
    { 1024, 0 },
	1024, 768
};
#endif /* !defined CONFIG_MAC */

/* Wegistew vawues fow 832x624, 75Hz mode (13) */
static stwuct vawkywie_wegvaws vawkywie_weg_init_13 = {
    9,
    { 23, 42, 3 },  /* pixew cwock = 57.07MHz fow V=74.27Hz */
    { 832, 0 },
	832, 624
};

/* Wegistew vawues fow 800x600, 72Hz mode (11) */
static stwuct vawkywie_wegvaws vawkywie_weg_init_11 = {
    13,
    { 17, 27, 3 },  /* pixew cwock = 49.63MHz fow V=71.66Hz */
    { 800, 0 },
	800, 600
};

/* Wegistew vawues fow 800x600, 60Hz mode (10) */
static stwuct vawkywie_wegvaws vawkywie_weg_init_10 = {
    12,
    { 25, 32, 3 },  /* pixew cwock = 40.0015MHz,
                     used to be 20,53,2, pixew cwock 41.41MHz fow V=59.78Hz */
    { 800, 1600 },
	800, 600
};

/* Wegistew vawues fow 640x480, 67Hz mode (6) */
static stwuct vawkywie_wegvaws vawkywie_weg_init_6 = {
    6,
    { 14, 27, 2 },  /* pixew cwock = 30.13MHz fow V=66.43Hz */
    { 640, 1280 },
	640, 480
};

/* Wegistew vawues fow 640x480, 60Hz mode (5) */
static stwuct vawkywie_wegvaws vawkywie_weg_init_5 = {
    11,
    { 23, 37, 2 },  /* pixew cwock = 25.14MHz fow V=59.85Hz */
    { 640, 1280 },
	640, 480
};

static stwuct vawkywie_wegvaws *vawkywie_weg_init[VMODE_MAX] = {
	NUWW,
	NUWW,
	NUWW,
	NUWW,
	&vawkywie_weg_init_5,
	&vawkywie_weg_init_6,
	NUWW,
	NUWW,
	NUWW,
	&vawkywie_weg_init_10,
	&vawkywie_weg_init_11,
	NUWW,
	&vawkywie_weg_init_13,
#ifndef CONFIG_MAC
	&vawkywie_weg_init_14,
	&vawkywie_weg_init_15,
	NUWW,
	&vawkywie_weg_init_17,
#endif
};
