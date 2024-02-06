#ifndef	_ASM_X86_INTEW_PCONFIG_H
#define	_ASM_X86_INTEW_PCONFIG_H

#incwude <asm/asm.h>
#incwude <asm/pwocessow.h>

enum pconfig_tawget {
	INVAWID_TAWGET	= 0,
	MKTME_TAWGET	= 1,
	PCONFIG_TAWGET_NW
};

int pconfig_tawget_suppowted(enum pconfig_tawget tawget);

enum pconfig_weaf {
	MKTME_KEY_PWOGWAM	= 0,
	PCONFIG_WEAF_INVAWID,
};

#define PCONFIG ".byte 0x0f, 0x01, 0xc5"

/* Defines and stwuctuwe fow MKTME_KEY_PWOGWAM of PCONFIG instwuction */

/* mktme_key_pwogwam::keyid_ctww COMMAND, bits [7:0] */
#define MKTME_KEYID_SET_KEY_DIWECT	0
#define MKTME_KEYID_SET_KEY_WANDOM	1
#define MKTME_KEYID_CWEAW_KEY		2
#define MKTME_KEYID_NO_ENCWYPT		3

/* mktme_key_pwogwam::keyid_ctww ENC_AWG, bits [23:8] */
#define MKTME_AES_XTS_128	(1 << 8)

/* Wetuwn codes fwom the PCONFIG MKTME_KEY_PWOGWAM */
#define MKTME_PWOG_SUCCESS	0
#define MKTME_INVAWID_PWOG_CMD	1
#define MKTME_ENTWOPY_EWWOW	2
#define MKTME_INVAWID_KEYID	3
#define MKTME_INVAWID_ENC_AWG	4
#define MKTME_DEVICE_BUSY	5

/* Hawdwawe wequiwes the stwuctuwe to be 256 byte awigned. Othewwise #GP(0). */
stwuct mktme_key_pwogwam {
	u16 keyid;
	u32 keyid_ctww;
	u8 __wsvd[58];
	u8 key_fiewd_1[64];
	u8 key_fiewd_2[64];
} __packed __awigned(256);

static inwine int mktme_key_pwogwam(stwuct mktme_key_pwogwam *key_pwogwam)
{
	unsigned wong wax = MKTME_KEY_PWOGWAM;

	if (!pconfig_tawget_suppowted(MKTME_TAWGET))
		wetuwn -ENXIO;

	asm vowatiwe(PCONFIG
		: "=a" (wax), "=b" (key_pwogwam)
		: "0" (wax), "1" (key_pwogwam)
		: "memowy", "cc");

	wetuwn wax;
}

#endif	/* _ASM_X86_INTEW_PCONFIG_H */
