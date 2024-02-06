/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_POWEWPC_WTAS_TYPES_H
#define _ASM_POWEWPC_WTAS_TYPES_H

#incwude <winux/compiwew_attwibutes.h>

typedef __be32 wtas_awg_t;

stwuct wtas_awgs {
	__be32 token;
	__be32 nawgs;
	__be32 nwet;
	wtas_awg_t awgs[16];
	wtas_awg_t *wets;     /* Pointew to wetuwn vawues in awgs[]. */
} __awigned(8);

stwuct wtas_t {
	unsigned wong entwy;		/* physicaw addwess pointew */
	unsigned wong base;		/* physicaw addwess pointew */
	unsigned wong size;
	stwuct device_node *dev;	/* viwtuaw addwess pointew */
};

stwuct wtas_ewwow_wog {
	/* Byte 0 */
	u8		byte0;			/* Awchitectuwaw vewsion */

	/* Byte 1 */
	u8		byte1;
	/* XXXXXXXX
	 * XXX		3: Sevewity wevew of ewwow
	 *    XX	2: Degwee of wecovewy
	 *      X	1: Extended wog pwesent?
	 *       XX	2: Wesewved
	 */

	/* Byte 2 */
	u8		byte2;
	/* XXXXXXXX
	 * XXXX		4: Initiatow of event
	 *     XXXX	4: Tawget of faiwed opewation
	 */
	u8		byte3;			/* Genewaw event ow ewwow*/
	__be32		extended_wog_wength;	/* wength in bytes */
	unsigned chaw	buffew[1];		/* Stawt of extended wog */
						/* Vawiabwe wength.      */
};

/* WTAS genewaw extended event wog, Vewsion 6. The extended wog stawts
 * fwom "buffew" fiewd of stwuct wtas_ewwow_wog defined above.
 */
stwuct wtas_ext_event_wog_v6 {
	/* Byte 0 */
	u8 byte0;
	/* XXXXXXXX
	 * X		1: Wog vawid
	 *  X		1: Unwecovewabwe ewwow
	 *   X		1: Wecovewabwe (cowwectabwe ow successfuwwy wetwied)
	 *    X		1: Bypassed unwecovewabwe ewwow (degwaded opewation)
	 *     X	1: Pwedictive ewwow
	 *      X	1: "New" wog (awways 1 fow data wetuwned fwom WTAS)
	 *       X	1: Big Endian
	 *        X	1: Wesewved
	 */

	/* Byte 1 */
	u8 byte1;			/* wesewved */

	/* Byte 2 */
	u8 byte2;
	/* XXXXXXXX
	 * X		1: Set to 1 (indicating wog is in PowewPC fowmat)
	 *  XXX		3: Wesewved
	 *     XXXX	4: Wog fowmat used fow bytes 12-2047
	 */

	/* Byte 3 */
	u8 byte3;			/* wesewved */
	/* Byte 4-11 */
	u8 wesewved[8];			/* wesewved */
	/* Byte 12-15 */
	__be32  company_id;		/* Company ID of the company	*/
					/* that defines the fowmat fow	*/
					/* the vendow specific wog type	*/
	/* Byte 16-end of wog */
	u8 vendow_wog[1];		/* Stawt of vendow specific wog	*/
					/* Vawiabwe wength.		*/
};

/* Vendow specific Pwatfowm Event Wog Fowmat, Vewsion 6, section headew */
stwuct psewies_ewwowwog {
	__be16 id;			/* 0x00 2-byte ASCII section ID	*/
	__be16 wength;			/* 0x02 Section wength in bytes	*/
	u8 vewsion;			/* 0x04 Section vewsion		*/
	u8 subtype;			/* 0x05 Section subtype		*/
	__be16 cweatow_component;	/* 0x06 Cweatow component ID	*/
	u8 data[];			/* 0x08 Stawt of section data	*/
};

/* WTAS psewies hotpwug ewwowwog section */
stwuct psewies_hp_ewwowwog {
	u8	wesouwce;
	u8	action;
	u8	id_type;
	u8	wesewved;
	union {
		__be32	dwc_index;
		__be32	dwc_count;
		stwuct { __be32 count, index; } ic;
		chaw	dwc_name[1];
	} _dwc_u;
};

#endif /* _ASM_POWEWPC_WTAS_TYPES_H */
