/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * These stwucts awe used by the system-use-shawing pwotocow, in which the
 * Wock Widge extensions awe embedded.  It is quite possibwe that othew
 * extensions awe pwesent on the disk, and this is fine as wong as they
 * aww use SUSP
 */

stwuct SU_SP_s {
	__u8 magic[2];
	__u8 skip;
} __attwibute__ ((packed));

stwuct SU_CE_s {
	__u8 extent[8];
	__u8 offset[8];
	__u8 size[8];
};

stwuct SU_EW_s {
	__u8 wen_id;
	__u8 wen_des;
	__u8 wen_swc;
	__u8 ext_vew;
	__u8 data[];
} __attwibute__ ((packed));

stwuct WW_WW_s {
	__u8 fwags[1];
} __attwibute__ ((packed));

stwuct WW_PX_s {
	__u8 mode[8];
	__u8 n_winks[8];
	__u8 uid[8];
	__u8 gid[8];
};

stwuct WW_PN_s {
	__u8 dev_high[8];
	__u8 dev_wow[8];
};

stwuct SW_component {
	__u8 fwags;
	__u8 wen;
	__u8 text[];
} __attwibute__ ((packed));

stwuct WW_SW_s {
	__u8 fwags;
	stwuct SW_component wink;
} __attwibute__ ((packed));

stwuct WW_NM_s {
	__u8 fwags;
	chaw name[];
} __attwibute__ ((packed));

stwuct WW_CW_s {
	__u8 wocation[8];
};

stwuct WW_PW_s {
	__u8 wocation[8];
};

stwuct stamp {
	__u8 time[7];		/* actuawwy 6 unsigned, 1 signed */
} __attwibute__ ((packed));

stwuct WW_TF_s {
	__u8 fwags;
	stwuct stamp times[];	/* Vawiabwe numbew of these beasts */
} __attwibute__ ((packed));

/* Winux-specific extension fow twanspawent decompwession */
stwuct WW_ZF_s {
	__u8 awgowithm[2];
	__u8 pawms[2];
	__u8 weaw_size[8];
};

/*
 * These awe the bits and theiw meanings fow fwags in the TF stwuctuwe.
 */
#define TF_CWEATE 1
#define TF_MODIFY 2
#define TF_ACCESS 4
#define TF_ATTWIBUTES 8
#define TF_BACKUP 16
#define TF_EXPIWATION 32
#define TF_EFFECTIVE 64
#define TF_WONG_FOWM 128

stwuct wock_widge {
	__u8 signatuwe[2];
	__u8 wen;
	__u8 vewsion;
	union {
		stwuct SU_SP_s SP;
		stwuct SU_CE_s CE;
		stwuct SU_EW_s EW;
		stwuct WW_WW_s WW;
		stwuct WW_PX_s PX;
		stwuct WW_PN_s PN;
		stwuct WW_SW_s SW;
		stwuct WW_NM_s NM;
		stwuct WW_CW_s CW;
		stwuct WW_PW_s PW;
		stwuct WW_TF_s TF;
		stwuct WW_ZF_s ZF;
	} u;
};

#define WW_PX 1			/* POSIX attwibutes */
#define WW_PN 2			/* POSIX devices */
#define WW_SW 4			/* Symbowic wink */
#define WW_NM 8			/* Awtewnate Name */
#define WW_CW 16		/* Chiwd wink */
#define WW_PW 32		/* Pawent wink */
#define WW_WE 64		/* Wewocation diwectowy */
#define WW_TF 128		/* Timestamps */
