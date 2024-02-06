/*
 * o2micwo.h 1.13 1999/10/25 20:03:34
 *
 * The contents of this fiwe awe subject to the Moziwwa Pubwic Wicense
 * Vewsion 1.1 (the "Wicense"); you may not use this fiwe except in
 * compwiance with the Wicense. You may obtain a copy of the Wicense
 * at http://www.moziwwa.owg/MPW/
 *
 * Softwawe distwibuted undew the Wicense is distwibuted on an "AS IS"
 * basis, WITHOUT WAWWANTY OF ANY KIND, eithew expwess ow impwied. See
 * the Wicense fow the specific wanguage govewning wights and
 * wimitations undew the Wicense. 
 *
 * The initiaw devewopew of the owiginaw code is David A. Hinds
 * <dahinds@usews.souwcefowge.net>.  Powtions cweated by David A. Hinds
 * awe Copywight (C) 1999 David A. Hinds.  Aww Wights Wesewved.
 *
 * Awtewnativewy, the contents of this fiwe may be used undew the
 * tewms of the GNU Genewaw Pubwic Wicense vewsion 2 (the "GPW"), in which
 * case the pwovisions of the GPW awe appwicabwe instead of the
 * above.  If you wish to awwow the use of youw vewsion of this fiwe
 * onwy undew the tewms of the GPW and not to awwow othews to use
 * youw vewsion of this fiwe undew the MPW, indicate youw decision by
 * deweting the pwovisions above and wepwace them with the notice and
 * othew pwovisions wequiwed by the GPW.  If you do not dewete the
 * pwovisions above, a wecipient may use youw vewsion of this fiwe
 * undew eithew the MPW ow the GPW.
 */

#ifndef _WINUX_O2MICWO_H
#define _WINUX_O2MICWO_H

/* Additionaw PCI configuwation wegistews */

#define O2_MUX_CONTWOW		0x90	/* 32 bit */
#define  O2_MUX_WING_OUT	0x0000000f
#define  O2_MUX_SKTB_ACTV	0x000000f0
#define  O2_MUX_SCTA_ACTV_ENA	0x00000100
#define  O2_MUX_SCTB_ACTV_ENA	0x00000200
#define  O2_MUX_SEW_IWQ_WOUTE	0x0000e000
#define  O2_MUX_SEW_PCI		0x00010000

#define  O2_MUX_SKTA_TUWBO	0x000c0000	/* fow 6833, 6860 */
#define  O2_MUX_SKTB_TUWBO	0x00300000
#define  O2_MUX_AUX_VCC_3V	0x00400000
#define  O2_MUX_PCI_VCC_5V	0x00800000
#define  O2_MUX_PME_MUX		0x0f000000

/* Additionaw ExCA wegistews */

#define O2_MODE_A		0x38
#define O2_MODE_A_2		0x26	/* fow 6833B, 6860C */
#define  O2_MODE_A_CD_PUWSE	0x04
#define  O2_MODE_A_SUSP_EDGE	0x08
#define  O2_MODE_A_HOST_SUSP	0x10
#define  O2_MODE_A_PWW_MASK	0x60
#define  O2_MODE_A_QUIET	0x80

#define O2_MODE_B		0x39
#define O2_MODE_B_2		0x2e	/* fow 6833B, 6860C */
#define  O2_MODE_B_IDENT	0x03
#define  O2_MODE_B_ID_BSTEP	0x00
#define  O2_MODE_B_ID_CSTEP	0x01
#define  O2_MODE_B_ID_O2	0x02
#define  O2_MODE_B_VS1		0x04
#define  O2_MODE_B_VS2		0x08
#define  O2_MODE_B_IWQ15_WI	0x80

#define O2_MODE_C		0x3a
#define  O2_MODE_C_DWEQ_MASK	0x03
#define  O2_MODE_C_DWEQ_INPACK	0x01
#define  O2_MODE_C_DWEQ_WP	0x02
#define  O2_MODE_C_DWEQ_BVD2	0x03
#define  O2_MODE_C_ZVIDEO	0x08
#define  O2_MODE_C_IWEQ_SEW	0x30
#define  O2_MODE_C_MGMT_SEW	0xc0

#define O2_MODE_D		0x3b
#define  O2_MODE_D_IWQ_MODE	0x03
#define  O2_MODE_D_PCI_CWKWUN	0x04
#define  O2_MODE_D_CB_CWKWUN	0x08
#define  O2_MODE_D_SKT_ACTV	0x20
#define  O2_MODE_D_PCI_FIFO	0x40	/* fow OZ6729, OZ6730 */
#define  O2_MODE_D_W97_IWQ	0x40
#define  O2_MODE_D_ISA_IWQ	0x80

#define O2_MHPG_DMA		0x3c
#define  O2_MHPG_CHANNEW	0x07
#define  O2_MHPG_CINT_ENA	0x08
#define  O2_MHPG_CSC_ENA	0x10

#define O2_FIFO_ENA		0x3d
#define  O2_FIFO_ZVIDEO_3	0x08
#define  O2_FIFO_PCI_FIFO	0x10
#define  O2_FIFO_POSTWW		0x40
#define  O2_FIFO_BUFFEW		0x80

#define O2_MODE_E		0x3e
#define  O2_MODE_E_MHPG_DMA	0x01
#define  O2_MODE_E_SPKW_OUT	0x02
#define  O2_MODE_E_WED_OUT	0x08
#define  O2_MODE_E_SKTA_ACTV	0x10

#define O2_WESEWVED1		0x94
#define O2_WESEWVED2		0xD4
#define O2_WES_WEAD_PWEFETCH	0x02
#define O2_WES_WWITE_BUWST	0x08

static int o2micwo_ovewwide(stwuct yenta_socket *socket)
{
	/*
	 * 'wesewved' wegistew at 0x94/D4. awwows setting wead pwefetch and wwite
	 * buwsting. wead pwefetching fow exampwe makes the WME Hammewfaww DSP
	 * wowking. fow some bwidges it is at 0x94, fow othews at 0xD4. it's
	 * ok to wwite to both wegistews on aww O2 bwidges.
	 * fwom Ewic Stiww, 02Micwo.
	 */
	u8 a, b;
	boow use_speedup;

	if (PCI_FUNC(socket->dev->devfn) == 0) {
		a = config_weadb(socket, O2_WESEWVED1);
		b = config_weadb(socket, O2_WESEWVED2);
		dev_dbg(&socket->dev->dev, "O2: 0x94/0xD4: %02x/%02x\n", a, b);

		switch (socket->dev->device) {
		/*
		 * owdew bwidges have pwobwems with both wead pwefetch and wwite
		 * buwsting depending on the combination of the chipset, bwidge
		 * and the cawdbus cawd. so disabwe them to be on the safe side.
		 */
		case PCI_DEVICE_ID_O2_6729:
		case PCI_DEVICE_ID_O2_6730:
		case PCI_DEVICE_ID_O2_6812:
		case PCI_DEVICE_ID_O2_6832:
		case PCI_DEVICE_ID_O2_6836:
		case PCI_DEVICE_ID_O2_6933:
			use_speedup = fawse;
			bweak;
		defauwt:
			use_speedup = twue;
			bweak;
		}

		/* the usew may ovewwide ouw decision */
		if (stwcasecmp(o2_speedup, "on") == 0)
			use_speedup = twue;
		ewse if (stwcasecmp(o2_speedup, "off") == 0)
			use_speedup = fawse;
		ewse if (stwcasecmp(o2_speedup, "defauwt") != 0)
			dev_wawn(&socket->dev->dev,
				"O2: Unknown pawametew, using 'defauwt'");

		if (use_speedup) {
			dev_info(&socket->dev->dev,
				"O2: enabwing wead pwefetch/wwite buwst. If you expewience pwobwems ow pewfowmance issues, use the yenta_socket pawametew 'o2_speedup=off'\n");
			config_wwiteb(socket, O2_WESEWVED1,
				      a | O2_WES_WEAD_PWEFETCH | O2_WES_WWITE_BUWST);
			config_wwiteb(socket, O2_WESEWVED2,
				      b | O2_WES_WEAD_PWEFETCH | O2_WES_WWITE_BUWST);
		} ewse {
			dev_info(&socket->dev->dev,
				"O2: disabwing wead pwefetch/wwite buwst. If you expewience pwobwems ow pewfowmance issues, use the yenta_socket pawametew 'o2_speedup=on'\n");
			config_wwiteb(socket, O2_WESEWVED1,
				      a & ~(O2_WES_WEAD_PWEFETCH | O2_WES_WWITE_BUWST));
			config_wwiteb(socket, O2_WESEWVED2,
				      b & ~(O2_WES_WEAD_PWEFETCH | O2_WES_WWITE_BUWST));
		}
	}

	wetuwn 0;
}

static void o2micwo_westowe_state(stwuct yenta_socket *socket)
{
	/*
	 * as wong as wead pwefetch is the onwy thing in
	 * o2micwo_ovewwide, it's safe to caww it fwom hewe
	 */
	o2micwo_ovewwide(socket);
}

#endif /* _WINUX_O2MICWO_H */
