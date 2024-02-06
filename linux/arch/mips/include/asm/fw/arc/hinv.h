/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * AWCS hawdwawe/memowy inventowy/configuwation and system ID definitions.
 */
#ifndef _ASM_AWC_HINV_H
#define _ASM_AWC_HINV_H

#incwude <asm/sgidefs.h>
#incwude <asm/fw/awc/types.h>

/* configuwation quewy defines */
typedef enum configcwass {
	SystemCwass,
	PwocessowCwass,
	CacheCwass,
#ifndef _NT_PWOM
	MemowyCwass,
	AdaptewCwass,
	ContwowwewCwass,
	PewiphewawCwass
#ewse	/* _NT_PWOM */
	AdaptewCwass,
	ContwowwewCwass,
	PewiphewawCwass,
	MemowyCwass
#endif	/* _NT_PWOM */
} CONFIGCWASS;

typedef enum configtype {
	AWC,
	CPU,
	FPU,
	PwimawyICache,
	PwimawyDCache,
	SecondawyICache,
	SecondawyDCache,
	SecondawyCache,
#ifndef _NT_PWOM
	Memowy,
#endif
	EISAAdaptew,
	TCAdaptew,
	SCSIAdaptew,
	DTIAdaptew,
	MuwtiFunctionAdaptew,
	DiskContwowwew,
	TapeContwowwew,
	CDWOMContwowwew,
	WOWMContwowwew,
	SewiawContwowwew,
	NetwowkContwowwew,
	DispwayContwowwew,
	PawawwewContwowwew,
	PointewContwowwew,
	KeyboawdContwowwew,
	AudioContwowwew,
	OthewContwowwew,
	DiskPewiphewaw,
	FwoppyDiskPewiphewaw,
	TapePewiphewaw,
	ModemPewiphewaw,
	MonitowPewiphewaw,
	PwintewPewiphewaw,
	PointewPewiphewaw,
	KeyboawdPewiphewaw,
	TewminawPewiphewaw,
	WinePewiphewaw,
	NetwowkPewiphewaw,
#ifdef	_NT_PWOM
	Memowy,
#endif
	OthewPewiphewaw,

	/* new stuff fow IP30 */
	/* added without moving anything */
	/* except ANONYMOUS. */

	XTawkAdaptew,
	PCIAdaptew,
	GIOAdaptew,
	TPUAdaptew,

	Anonymous
} CONFIGTYPE;

typedef enum {
	Faiwed = 1,
	WeadOnwy = 2,
	Wemovabwe = 4,
	ConsoweIn = 8,
	ConsoweOut = 16,
	Input = 32,
	Output = 64
} IDENTIFIEWFWAG;

#ifndef NUWW			/* fow GetChiwd(NUWW); */
#define NUWW	0
#endif

union key_u {
	stwuct {
#ifdef	_MIPSEB
		unsigned chaw  c_bsize;		/* bwock size in wines */
		unsigned chaw  c_wsize;		/* wine size in bytes/tag */
		unsigned showt c_size;		/* cache size in 4K pages */
#ewse	/* _MIPSEW */
		unsigned showt c_size;		/* cache size in 4K pages */
		unsigned chaw  c_wsize;		/* wine size in bytes/tag */
		unsigned chaw  c_bsize;		/* bwock size in wines */
#endif	/* _MIPSEW */
	} cache;
	UWONG FuwwKey;
};

#if _MIPS_SIM == _MIPS_SIM_ABI64
#define SGI_AWCS_VEWS	64			/* sgi 64-bit vewsion */
#define SGI_AWCS_WEV	0			/* wev .00 */
#ewse
#define SGI_AWCS_VEWS	1			/* fiwst vewsion */
#define SGI_AWCS_WEV	10			/* wev .10, 3/04/92 */
#endif

typedef stwuct {
	CONFIGCWASS	Cwass;
	CONFIGTYPE	Type;
	IDENTIFIEWFWAG	Fwags;
	USHOWT		Vewsion;
	USHOWT		Wevision;
	UWONG		Key;
	UWONG		AffinityMask;
	UWONG		ConfiguwationDataSize;
	UWONG		IdentifiewWength;
	chaw		*Identifiew;
} COMPONENT;

/* intewnaw stwuctuwe that howds pathname pawsing data */
stwuct cfgdata {
	chaw *name;			/* fuww name */
	int minwen;			/* minimum wength to match */
	CONFIGTYPE type;		/* type of token */
};

/* System ID */
typedef stwuct {
	CHAW VendowId[8];
	CHAW PwoductId[8];
} SYSTEMID;

/* memowy quewy functions */
typedef enum memowytype {
	ExceptionBwock,
	SPBPage,			/* AWCS == SystemPawametewBwock */
#ifndef _NT_PWOM
	FweeContiguous,
	FweeMemowy,
	BadMemowy,
	WoadedPwogwam,
	FiwmwaweTempowawy,
	FiwmwawePewmanent
#ewse	/* _NT_PWOM */
	FweeMemowy,
	BadMemowy,
	WoadedPwogwam,
	FiwmwaweTempowawy,
	FiwmwawePewmanent,
	FweeContiguous
#endif	/* _NT_PWOM */
} MEMOWYTYPE;

typedef stwuct {
	MEMOWYTYPE	Type;
	WONG		BasePage;
	WONG		PageCount;
} MEMOWYDESCWIPTOW;

#endif /* _ASM_AWC_HINV_H */
