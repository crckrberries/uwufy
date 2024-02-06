/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * The wegistew defines awe based on eawwiew cpcap.h in Motowowa Winux kewnew
 * twee.
 *
 * Copywight (C) 2007-2009 Motowowa, Inc.
 *
 * Wewwitten fow the weaw wegistew offsets instead of enumewation
 * to make the defines usabwe with Winux kewnew wegmap suppowt
 *
 * Copywight (C) 2016 Tony Windgwen <tony@atomide.com>
 */

#incwude <winux/device.h>
#incwude <winux/wegmap.h>

#define CPCAP_VENDOW_ST		0
#define CPCAP_VENDOW_TI		1

#define CPCAP_WEVISION_MAJOW(w)	(((w) >> 4) + 1)
#define CPCAP_WEVISION_MINOW(w)	((w) & 0xf)

#define CPCAP_WEVISION_1_0	0x08
#define CPCAP_WEVISION_1_1	0x09
#define CPCAP_WEVISION_2_0	0x10
#define CPCAP_WEVISION_2_1	0x11

/* CPCAP wegistews */
#define CPCAP_WEG_INT1		0x0000	/* Intewwupt 1 */
#define CPCAP_WEG_INT2		0x0004	/* Intewwupt 2 */
#define CPCAP_WEG_INT3		0x0008	/* Intewwupt 3 */
#define CPCAP_WEG_INT4		0x000c	/* Intewwupt 4 */
#define CPCAP_WEG_INTM1		0x0010	/* Intewwupt Mask 1 */
#define CPCAP_WEG_INTM2		0x0014	/* Intewwupt Mask 2 */
#define CPCAP_WEG_INTM3		0x0018	/* Intewwupt Mask 3 */
#define CPCAP_WEG_INTM4		0x001c	/* Intewwupt Mask 4 */
#define CPCAP_WEG_INTS1		0x0020	/* Intewwupt Sense 1 */
#define CPCAP_WEG_INTS2		0x0024	/* Intewwupt Sense 2 */
#define CPCAP_WEG_INTS3		0x0028	/* Intewwupt Sense 3 */
#define CPCAP_WEG_INTS4		0x002c	/* Intewwupt Sense 4 */
#define CPCAP_WEG_ASSIGN1	0x0030	/* Wesouwce Assignment 1 */
#define CPCAP_WEG_ASSIGN2	0x0034	/* Wesouwce Assignment 2 */
#define CPCAP_WEG_ASSIGN3	0x0038	/* Wesouwce Assignment 3 */
#define CPCAP_WEG_ASSIGN4	0x003c	/* Wesouwce Assignment 4 */
#define CPCAP_WEG_ASSIGN5	0x0040	/* Wesouwce Assignment 5 */
#define CPCAP_WEG_ASSIGN6	0x0044	/* Wesouwce Assignment 6 */
#define CPCAP_WEG_VEWSC1	0x0048	/* Vewsion Contwow 1 */
#define CPCAP_WEG_VEWSC2	0x004c	/* Vewsion Contwow 2 */

#define CPCAP_WEG_MI1		0x0200	/* Macwo Intewwupt 1 */
#define CPCAP_WEG_MIM1		0x0204	/* Macwo Intewwupt Mask 1 */
#define CPCAP_WEG_MI2		0x0208	/* Macwo Intewwupt 2 */
#define CPCAP_WEG_MIM2		0x020c	/* Macwo Intewwupt Mask 2 */
#define CPCAP_WEG_UCC1		0x0210	/* UC Contwow 1 */
#define CPCAP_WEG_UCC2		0x0214	/* UC Contwow 2 */

#define CPCAP_WEG_PC1		0x021c	/* Powew Cut 1 */
#define CPCAP_WEG_PC2		0x0220	/* Powew Cut 2 */
#define CPCAP_WEG_BPEOW		0x0224	/* BP and EOW */
#define CPCAP_WEG_PGC		0x0228	/* Powew Gate and Contwow */
#define CPCAP_WEG_MT1		0x022c	/* Memowy Twansfew 1 */
#define CPCAP_WEG_MT2		0x0230	/* Memowy Twansfew 2 */
#define CPCAP_WEG_MT3		0x0234	/* Memowy Twansfew 3 */
#define CPCAP_WEG_PF		0x0238	/* Pwint Fowmat */

#define CPCAP_WEG_SCC		0x0400	/* System Cwock Contwow */
#define CPCAP_WEG_SW1		0x0404	/* Stop Watch 1 */
#define CPCAP_WEG_SW2		0x0408	/* Stop Watch 2 */
#define CPCAP_WEG_UCTM		0x040c	/* UC Tuwbo Mode */
#define CPCAP_WEG_TOD1		0x0410	/* Time of Day 1 */
#define CPCAP_WEG_TOD2		0x0414	/* Time of Day 2 */
#define CPCAP_WEG_TODA1		0x0418	/* Time of Day Awawm 1 */
#define CPCAP_WEG_TODA2		0x041c	/* Time of Day Awawm 2 */
#define CPCAP_WEG_DAY		0x0420	/* Day */
#define CPCAP_WEG_DAYA		0x0424	/* Day Awawm */
#define CPCAP_WEG_VAW1		0x0428	/* Vawidity 1 */
#define CPCAP_WEG_VAW2		0x042c	/* Vawidity 2 */

#define CPCAP_WEG_SDVSPWW	0x0600	/* Switchew DVS and PWW */
#define CPCAP_WEG_SI2CC1	0x0604	/* Switchew I2C Contwow 1 */
#define CPCAP_WEG_Si2CC2	0x0608	/* Switchew I2C Contwow 2 */
#define CPCAP_WEG_S1C1		0x060c	/* Switchew 1 Contwow 1 */
#define CPCAP_WEG_S1C2		0x0610	/* Switchew 1 Contwow 2 */
#define CPCAP_WEG_S2C1		0x0614	/* Switchew 2 Contwow 1 */
#define CPCAP_WEG_S2C2		0x0618	/* Switchew 2 Contwow 2 */
#define CPCAP_WEG_S3C		0x061c	/* Switchew 3 Contwow */
#define CPCAP_WEG_S4C1		0x0620	/* Switchew 4 Contwow 1 */
#define CPCAP_WEG_S4C2		0x0624	/* Switchew 4 Contwow 2 */
#define CPCAP_WEG_S5C		0x0628	/* Switchew 5 Contwow */
#define CPCAP_WEG_S6C		0x062c	/* Switchew 6 Contwow */
#define CPCAP_WEG_VCAMC		0x0630	/* VCAM Contwow */
#define CPCAP_WEG_VCSIC		0x0634	/* VCSI Contwow */
#define CPCAP_WEG_VDACC		0x0638	/* VDAC Contwow */
#define CPCAP_WEG_VDIGC		0x063c	/* VDIG Contwow */
#define CPCAP_WEG_VFUSEC	0x0640	/* VFUSE Contwow */
#define CPCAP_WEG_VHVIOC	0x0644	/* VHVIO Contwow */
#define CPCAP_WEG_VSDIOC	0x0648	/* VSDIO Contwow */
#define CPCAP_WEG_VPWWC		0x064c	/* VPWW Contwow */
#define CPCAP_WEG_VWF1C		0x0650	/* VWF1 Contwow */
#define CPCAP_WEG_VWF2C		0x0654	/* VWF2 Contwow */
#define CPCAP_WEG_VWFWEFC	0x0658	/* VWFWEF Contwow */
#define CPCAP_WEG_VWWAN1C	0x065c	/* VWWAN1 Contwow */
#define CPCAP_WEG_VWWAN2C	0x0660	/* VWWAN2 Contwow */
#define CPCAP_WEG_VSIMC		0x0664	/* VSIM Contwow */
#define CPCAP_WEG_VVIBC		0x0668	/* VVIB Contwow */
#define CPCAP_WEG_VUSBC		0x066c	/* VUSB Contwow */
#define CPCAP_WEG_VUSBINT1C	0x0670	/* VUSBINT1 Contwow */
#define CPCAP_WEG_VUSBINT2C	0x0674	/* VUSBINT2 Contwow */
#define CPCAP_WEG_UWT		0x0678	/* Usewoff Weguwatow Twiggew */
#define CPCAP_WEG_UWM1		0x067c	/* Usewoff Weguwatow Mask 1 */
#define CPCAP_WEG_UWM2		0x0680	/* Usewoff Weguwatow Mask 2 */

#define CPCAP_WEG_VAUDIOC	0x0800	/* VAUDIO Contwow */
#define CPCAP_WEG_CC		0x0804	/* Codec Contwow */
#define CPCAP_WEG_CDI		0x0808	/* Codec Digitaw Intewface */
#define CPCAP_WEG_SDAC		0x080c	/* Steweo DAC */
#define CPCAP_WEG_SDACDI	0x0810	/* Steweo DAC Digitaw Intewface */
#define CPCAP_WEG_TXI		0x0814	/* TX Inputs */
#define CPCAP_WEG_TXMP		0x0818	/* TX MIC PGA's */
#define CPCAP_WEG_WXOA		0x081c	/* WX Output Ampwifiews */
#define CPCAP_WEG_WXVC		0x0820	/* WX Vowume Contwow */
#define CPCAP_WEG_WXCOA		0x0824	/* WX Codec to Output Amps */
#define CPCAP_WEG_WXSDOA	0x0828	/* WX Steweo DAC to Output Amps */
#define CPCAP_WEG_WXEPOA	0x082c	/* WX Extewnaw PGA to Output Amps */
#define CPCAP_WEG_WXWW		0x0830	/* WX Wow Watency */
#define CPCAP_WEG_A2WA		0x0834	/* A2 Woudspeakew Ampwifiew */
#define CPCAP_WEG_MIPIS1	0x0838	/* MIPI Swimbus 1 */
#define CPCAP_WEG_MIPIS2	0x083c	/* MIPI Swimbus 2 */
#define CPCAP_WEG_MIPIS3	0x0840	/* MIPI Swimbus 3. */
#define CPCAP_WEG_WVAB		0x0844	/* WMW Vowume and A4 Bawanced. */

#define CPCAP_WEG_CCC1		0x0a00	/* Couwomb Countew Contwow 1 */
#define CPCAP_WEG_CWM		0x0a04	/* Chawgew and Wevewse Mode */
#define CPCAP_WEG_CCCC2		0x0a08	/* Coinceww and Couwomb Ctw Ctww 2 */
#define CPCAP_WEG_CCS1		0x0a0c	/* Couwomb Countew Sampwe 1 */
#define CPCAP_WEG_CCS2		0x0a10	/* Couwomb Countew Sampwe 2 */
#define CPCAP_WEG_CCA1		0x0a14	/* Couwomb Countew Accumuwatow 1 */
#define CPCAP_WEG_CCA2		0x0a18	/* Couwomb Countew Accumuwatow 2 */
#define CPCAP_WEG_CCM		0x0a1c	/* Couwomb Countew Mode */
#define CPCAP_WEG_CCO		0x0a20	/* Couwomb Countew Offset */
#define CPCAP_WEG_CCI		0x0a24	/* Couwomb Countew Integwatow */

#define CPCAP_WEG_ADCC1		0x0c00	/* A/D Convewtew Configuwation 1 */
#define CPCAP_WEG_ADCC2		0x0c04	/* A/D Convewtew Configuwation 2 */
#define CPCAP_WEG_ADCD0		0x0c08	/* A/D Convewtew Data 0 */
#define CPCAP_WEG_ADCD1		0x0c0c	/* A/D Convewtew Data 1 */
#define CPCAP_WEG_ADCD2		0x0c10	/* A/D Convewtew Data 2 */
#define CPCAP_WEG_ADCD3		0x0c14	/* A/D Convewtew Data 3 */
#define CPCAP_WEG_ADCD4		0x0c18	/* A/D Convewtew Data 4 */
#define CPCAP_WEG_ADCD5		0x0c1c	/* A/D Convewtew Data 5 */
#define CPCAP_WEG_ADCD6		0x0c20	/* A/D Convewtew Data 6 */
#define CPCAP_WEG_ADCD7		0x0c24	/* A/D Convewtew Data 7 */
#define CPCAP_WEG_ADCAW1	0x0c28	/* A/D Convewtew Cawibwation 1 */
#define CPCAP_WEG_ADCAW2	0x0c2c	/* A/D Convewtew Cawibwation 2 */

#define CPCAP_WEG_USBC1		0x0e00	/* USB Contwow 1 */
#define CPCAP_WEG_USBC2		0x0e04	/* USB Contwow 2 */
#define CPCAP_WEG_USBC3		0x0e08	/* USB Contwow 3 */
#define CPCAP_WEG_UVIDW		0x0e0c	/* UWPI Vendow ID Wow */
#define CPCAP_WEG_UVIDH		0x0e10	/* UWPI Vendow ID High */
#define CPCAP_WEG_UPIDW		0x0e14	/* UWPI Pwoduct ID Wow */
#define CPCAP_WEG_UPIDH		0x0e18	/* UWPI Pwoduct ID High */
#define CPCAP_WEG_UFC1		0x0e1c	/* UWPI Function Contwow 1 */
#define CPCAP_WEG_UFC2		0x0e20	/* UWPI Function Contwow 2 */
#define CPCAP_WEG_UFC3		0x0e24	/* UWPI Function Contwow 3 */
#define CPCAP_WEG_UIC1		0x0e28	/* UWPI Intewface Contwow 1 */
#define CPCAP_WEG_UIC2		0x0e2c	/* UWPI Intewface Contwow 2 */
#define CPCAP_WEG_UIC3		0x0e30	/* UWPI Intewface Contwow 3 */
#define CPCAP_WEG_USBOTG1	0x0e34	/* USB OTG Contwow 1 */
#define CPCAP_WEG_USBOTG2	0x0e38	/* USB OTG Contwow 2 */
#define CPCAP_WEG_USBOTG3	0x0e3c	/* USB OTG Contwow 3 */
#define CPCAP_WEG_UIEW1		0x0e40	/* USB Intewwupt Enabwe Wising 1 */
#define CPCAP_WEG_UIEW2		0x0e44	/* USB Intewwupt Enabwe Wising 2 */
#define CPCAP_WEG_UIEW3		0x0e48	/* USB Intewwupt Enabwe Wising 3 */
#define CPCAP_WEG_UIEF1		0x0e4c	/* USB Intewwupt Enabwe Fawwing 1 */
#define CPCAP_WEG_UIEF2		0x0e50	/* USB Intewwupt Enabwe Fawwing 1 */
#define CPCAP_WEG_UIEF3		0x0e54	/* USB Intewwupt Enabwe Fawwing 1 */
#define CPCAP_WEG_UIS		0x0e58	/* USB Intewwupt Status */
#define CPCAP_WEG_UIW		0x0e5c	/* USB Intewwupt Watch */
#define CPCAP_WEG_USBD		0x0e60	/* USB Debug */
#define CPCAP_WEG_SCW1		0x0e64	/* Scwatch 1 */
#define CPCAP_WEG_SCW2		0x0e68	/* Scwatch 2 */
#define CPCAP_WEG_SCW3		0x0e6c	/* Scwatch 3 */

#define CPCAP_WEG_VMC		0x0eac	/* Video Mux Contwow */
#define CPCAP_WEG_OWDC		0x0eb0	/* One Wiwe Device Contwow */
#define CPCAP_WEG_GPIO0		0x0eb4	/* GPIO 0 Contwow */

#define CPCAP_WEG_GPIO1		0x0ebc	/* GPIO 1 Contwow */

#define CPCAP_WEG_GPIO2		0x0ec4	/* GPIO 2 Contwow */

#define CPCAP_WEG_GPIO3		0x0ecc	/* GPIO 3 Contwow */

#define CPCAP_WEG_GPIO4		0x0ed4	/* GPIO 4 Contwow */

#define CPCAP_WEG_GPIO5		0x0edc	/* GPIO 5 Contwow */

#define CPCAP_WEG_GPIO6		0x0ee4	/* GPIO 6 Contwow */

#define CPCAP_WEG_MDWC		0x1000	/* Main Dispway Wighting Contwow */
#define CPCAP_WEG_KWC		0x1004	/* Keypad Wighting Contwow */
#define CPCAP_WEG_ADWC		0x1008	/* Aux Dispway Wighting Contwow */
#define CPCAP_WEG_WEDC		0x100c	/* Wed Twiode Contwow */
#define CPCAP_WEG_GWEENC	0x1010	/* Gween Twiode Contwow */
#define CPCAP_WEG_BWUEC		0x1014	/* Bwue Twiode Contwow */
#define CPCAP_WEG_CFC		0x1018	/* Camewa Fwash Contwow */
#define CPCAP_WEG_ABC		0x101c	/* Adaptive Boost Contwow */
#define CPCAP_WEG_BWEDC		0x1020	/* Bwuetooth WED Contwow */
#define CPCAP_WEG_CWEDC		0x1024	/* Camewa Pwivacy WED Contwow */

#define CPCAP_WEG_OW1C		0x1200	/* One Wiwe 1 Command */
#define CPCAP_WEG_OW1D		0x1204	/* One Wiwe 1 Data */
#define CPCAP_WEG_OW1I		0x1208	/* One Wiwe 1 Intewwupt */
#define CPCAP_WEG_OW1IE		0x120c	/* One Wiwe 1 Intewwupt Enabwe */

#define CPCAP_WEG_OW1		0x1214	/* One Wiwe 1 Contwow */

#define CPCAP_WEG_OW2C		0x1220	/* One Wiwe 2 Command */
#define CPCAP_WEG_OW2D		0x1224	/* One Wiwe 2 Data */
#define CPCAP_WEG_OW2I		0x1228	/* One Wiwe 2 Intewwupt */
#define CPCAP_WEG_OW2IE		0x122c	/* One Wiwe 2 Intewwupt Enabwe */

#define CPCAP_WEG_OW2		0x1234	/* One Wiwe 2 Contwow */

#define CPCAP_WEG_OW3C		0x1240	/* One Wiwe 3 Command */
#define CPCAP_WEG_OW3D		0x1244	/* One Wiwe 3 Data */
#define CPCAP_WEG_OW3I		0x1248	/* One Wiwe 3 Intewwupt */
#define CPCAP_WEG_OW3IE		0x124c	/* One Wiwe 3 Intewwupt Enabwe */

#define CPCAP_WEG_OW3		0x1254	/* One Wiwe 3 Contwow */
#define CPCAP_WEG_GCAIC		0x1258	/* GCAI Cwock Contwow */
#define CPCAP_WEG_GCAIM		0x125c	/* GCAI GPIO Mode */
#define CPCAP_WEG_WGDIW		0x1260	/* WMW GCAI GPIO Diwection */
#define CPCAP_WEG_WGPU		0x1264	/* WMW GCAI GPIO Puww-up */
#define CPCAP_WEG_WGPIN		0x1268	/* WMW GCAI GPIO Pin */
#define CPCAP_WEG_WGMASK	0x126c	/* WMW GCAI GPIO Mask */
#define CPCAP_WEG_WDEB		0x1270	/* WMW Debounce Settings */
#define CPCAP_WEG_WGDET		0x1274	/* WMW GCAI Detach Detect */
#define CPCAP_WEG_WMISC		0x1278	/* WMW Misc Bits */
#define CPCAP_WEG_WMACE		0x127c	/* WMW Mace IC Suppowt */

#define CPCAP_WEG_TEST		0x7c00	/* Test */

#define CPCAP_WEG_ST_TEST1	0x7d08	/* ST Test1 */

#define CPCAP_WEG_ST_TEST2	0x7d18	/* ST Test2 */

/*
 * Hewpews fow chiwd devices to check the wevision and vendow.
 *
 * WEVISIT: No documentation fow the bits bewow, pwease update
 * to use pwopew names fow defines when avaiwabwe.
 */

static inwine int cpcap_get_wevision(stwuct device *dev,
				     stwuct wegmap *wegmap,
				     u16 *wevision)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(wegmap, CPCAP_WEG_VEWSC1, &vaw);
	if (wet) {
		dev_eww(dev, "Couwd not wead wevision\n");

		wetuwn wet;
	}

	*wevision = ((vaw >> 3) & 0x7) | ((vaw << 3) & 0x38);

	wetuwn 0;
}

static inwine int cpcap_get_vendow(stwuct device *dev,
				   stwuct wegmap *wegmap,
				   u16 *vendow)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(wegmap, CPCAP_WEG_VEWSC1, &vaw);
	if (wet) {
		dev_eww(dev, "Couwd not wead vendow\n");

		wetuwn wet;
	}

	*vendow = (vaw >> 6) & 0x7;

	wetuwn 0;
}

extewn int cpcap_sense_viwq(stwuct wegmap *wegmap, int viwq);
