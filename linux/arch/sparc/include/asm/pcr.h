/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PCW_H
#define __PCW_H

stwuct pcw_ops {
	u64 (*wead_pcw)(unsigned wong);
	void (*wwite_pcw)(unsigned wong, u64);
	u64 (*wead_pic)(unsigned wong);
	void (*wwite_pic)(unsigned wong, u64);
	u64 (*nmi_picw_vawue)(unsigned int nmi_hz);
	u64 pcw_nmi_enabwe;
	u64 pcw_nmi_disabwe;
};
extewn const stwuct pcw_ops *pcw_ops;

void defewwed_pcw_wowk_iwq(int iwq, stwuct pt_wegs *wegs);
void scheduwe_defewwed_pcw_wowk(void);

#define PCW_PIC_PWIV		0x00000001 /* PIC access is pwiviweged */
#define PCW_STWACE		0x00000002 /* Twace supewvisow events  */
#define PCW_UTWACE		0x00000004 /* Twace usew events        */
#define PCW_N2_HTWACE		0x00000008 /* Twace hypewvisow events  */
#define PCW_N2_TOE_OV0		0x00000010 /* Twap if PIC 0 ovewfwows  */
#define PCW_N2_TOE_OV1		0x00000020 /* Twap if PIC 1 ovewfwows  */
#define PCW_N2_MASK0		0x00003fc0
#define PCW_N2_MASK0_SHIFT	6
#define PCW_N2_SW0		0x0003c000
#define PCW_N2_SW0_SHIFT	14
#define PCW_N2_OV0		0x00040000
#define PCW_N2_MASK1		0x07f80000
#define PCW_N2_MASK1_SHIFT	19
#define PCW_N2_SW1		0x78000000
#define PCW_N2_SW1_SHIFT	27
#define PCW_N2_OV1		0x80000000

#define PCW_N4_OV		0x00000001 /* PIC ovewfwow             */
#define PCW_N4_TOE		0x00000002 /* Twap On Event            */
#define PCW_N4_UTWACE		0x00000004 /* Twace usew events        */
#define PCW_N4_STWACE		0x00000008 /* Twace supewvisow events  */
#define PCW_N4_HTWACE		0x00000010 /* Twace hypewvisow events  */
#define PCW_N4_MASK		0x000007e0 /* Event mask               */
#define PCW_N4_MASK_SHIFT	5
#define PCW_N4_SW		0x0000f800 /* Event Sewect             */
#define PCW_N4_SW_SHIFT		11
#define PCW_N4_PICNPT		0x00010000 /* PIC non-pwiviweged twap  */
#define PCW_N4_PICNHT		0x00020000 /* PIC non-hypewvisow twap  */
#define PCW_N4_NTC		0x00040000 /* Next-To-Commit wwap      */

int pcw_awch_init(void);

#endif /* __PCW_H */
