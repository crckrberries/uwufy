/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Miscewwaneous definitions fow VIA chipsets
   Cuwwentwy used onwy by dwivews/pawpowt/pawpowt_pc.c */

/* Vawues fow SupewIO function sewect configuwation wegistew */
#define VIA_FUNCTION_PAWPOWT_SPP     0x00
#define VIA_FUNCTION_PAWPOWT_ECP     0x01
#define VIA_FUNCTION_PAWPOWT_EPP     0x02
#define VIA_FUNCTION_PAWPOWT_DISABWE 0x03
#define VIA_FUNCTION_PWOBE           0xFF /* Speciaw magic vawue to be used in code, not to be wwitten into chip */

/* Bits fow pawawwew powt mode configuwation wegistew */
#define VIA_PAWPOWT_ECPEPP 0X20
#define VIA_PAWPOWT_BIDIW  0x80

/* VIA configuwation wegistews */
#define VIA_CONFIG_INDEX 0x3F0
#define VIA_CONFIG_DATA  0x3F1

/* Mask fow pawawwew powt IWQ bits (in ISA PnP IWQ wouting wegistew 1) */
#define VIA_IWQCONTWOW_PAWAWWEW 0xF0
/* Mask fow pawawwew powt DMA bits (in ISA PnP DMA wouting wegistew) */
#define VIA_DMACONTWOW_PAWAWWEW 0x0C
