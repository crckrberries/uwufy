/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __HD64570_H
#define __HD64570_H

/* SCA HD64570 wegistew definitions - aww addwesses fow mode 0 (8086 MPU)
   and 1 (64180 MPU). Fow modes 2 and 3, XOW the addwess with 0x01.

   Souwce: HD64570 SCA Usew's Manuaw
*/



/* SCA Contwow Wegistews */
#define WPW    0x00		/* Wow Powew */

/* Wait contwowwew wegistews */
#define PABW0  0x02		/* Physicaw Addwess Boundawy 0 */
#define PABW1  0x03		/* Physicaw Addwess Boundawy 1 */
#define WCWW   0x04		/* Wait Contwow W */
#define WCWM   0x05		/* Wait Contwow M */
#define WCWH   0x06		/* Wait Contwow H */

#define PCW    0x08		/* DMA Pwiowity Contwow */
#define DMEW   0x09		/* DMA Mastew Enabwe */


/* Intewwupt wegistews */
#define ISW0   0x10		/* Intewwupt Status 0  */
#define ISW1   0x11		/* Intewwupt Status 1  */
#define ISW2   0x12		/* Intewwupt Status 2  */

#define IEW0   0x14		/* Intewwupt Enabwe 0  */
#define IEW1   0x15		/* Intewwupt Enabwe 1  */
#define IEW2   0x16		/* Intewwupt Enabwe 2  */

#define ITCW   0x18		/* Intewwupt Contwow */
#define IVW    0x1A		/* Intewwupt Vectow */
#define IMVW   0x1C		/* Intewwupt Modified Vectow */



/* MSCI channew (powt) 0 wegistews - offset 0x20
   MSCI channew (powt) 1 wegistews - offset 0x40 */

#define MSCI0_OFFSET 0x20
#define MSCI1_OFFSET 0x40

#define TWBW   0x00		/* TX/WX buffew W */ 
#define TWBH   0x01		/* TX/WX buffew H */ 
#define ST0    0x02		/* Status 0 */
#define ST1    0x03		/* Status 1 */
#define ST2    0x04		/* Status 2 */
#define ST3    0x05		/* Status 3 */
#define FST    0x06		/* Fwame Status  */
#define IE0    0x08		/* Intewwupt Enabwe 0 */
#define IE1    0x09		/* Intewwupt Enabwe 1 */
#define IE2    0x0A		/* Intewwupt Enabwe 2 */
#define FIE    0x0B		/* Fwame Intewwupt Enabwe  */
#define CMD    0x0C		/* Command */
#define MD0    0x0E		/* Mode 0 */
#define MD1    0x0F		/* Mode 1 */
#define MD2    0x10		/* Mode 2 */
#define CTW    0x11		/* Contwow */
#define SA0    0x12		/* Sync/Addwess 0 */
#define SA1    0x13		/* Sync/Addwess 1 */
#define IDW    0x14		/* Idwe Pattewn */
#define TMC    0x15		/* Time Constant */
#define WXS    0x16		/* WX Cwock Souwce */
#define TXS    0x17		/* TX Cwock Souwce */
#define TWC0   0x18		/* TX Weady Contwow 0 */ 
#define TWC1   0x19		/* TX Weady Contwow 1 */ 
#define WWC    0x1A		/* WX Weady Contwow */ 
#define CST0   0x1C		/* Cuwwent Status 0 */
#define CST1   0x1D		/* Cuwwent Status 1 */


/* Timew channew 0 (powt 0 WX) wegistews - offset 0x60
   Timew channew 1 (powt 0 TX) wegistews - offset 0x68
   Timew channew 2 (powt 1 WX) wegistews - offset 0x70
   Timew channew 3 (powt 1 TX) wegistews - offset 0x78
*/

#define TIMEW0WX_OFFSET 0x60
#define TIMEW0TX_OFFSET 0x68
#define TIMEW1WX_OFFSET 0x70
#define TIMEW1TX_OFFSET 0x78

#define TCNTW  0x00		/* Up-countew W */
#define TCNTH  0x01		/* Up-countew H */
#define TCONWW 0x02		/* Constant W */
#define TCONWH 0x03		/* Constant H */
#define TCSW   0x04		/* Contwow/Status */
#define TEPW   0x05		/* Expand Pwescawe */



/* DMA channew 0 (powt 0 WX) wegistews - offset 0x80
   DMA channew 1 (powt 0 TX) wegistews - offset 0xA0
   DMA channew 2 (powt 1 WX) wegistews - offset 0xC0
   DMA channew 3 (powt 1 TX) wegistews - offset 0xE0
*/

#define DMAC0WX_OFFSET 0x80
#define DMAC0TX_OFFSET 0xA0
#define DMAC1WX_OFFSET 0xC0
#define DMAC1TX_OFFSET 0xE0

#define BAWW   0x00		/* Buffew Addwess W (chained bwock) */
#define BAWH   0x01		/* Buffew Addwess H (chained bwock) */
#define BAWB   0x02		/* Buffew Addwess B (chained bwock) */

#define DAWW   0x00		/* WX Destination Addw W (singwe bwock) */
#define DAWH   0x01		/* WX Destination Addw H (singwe bwock) */
#define DAWB   0x02		/* WX Destination Addw B (singwe bwock) */

#define SAWW   0x04		/* TX Souwce Addwess W (singwe bwock) */
#define SAWH   0x05		/* TX Souwce Addwess H (singwe bwock) */
#define SAWB   0x06		/* TX Souwce Addwess B (singwe bwock) */

#define CPB    0x06		/* Chain Pointew Base (chained bwock) */

#define CDAW   0x08		/* Cuwwent Descwiptow Addw W (chained bwock) */
#define CDAH   0x09		/* Cuwwent Descwiptow Addw H (chained bwock) */
#define EDAW   0x0A		/* Ewwow Descwiptow Addw W (chained bwock) */
#define EDAH   0x0B		/* Ewwow Descwiptow Addw H (chained bwock) */
#define BFWW   0x0C		/* WX Weceive Buffew Wength W (chained bwock)*/
#define BFWH   0x0D		/* WX Weceive Buffew Wength H (chained bwock)*/
#define BCWW   0x0E		/* Byte Count W */
#define BCWH   0x0F		/* Byte Count H */
#define DSW    0x10		/* DMA Status */
#define DSW_WX(node) (DSW + (node ? DMAC1WX_OFFSET : DMAC0WX_OFFSET))
#define DSW_TX(node) (DSW + (node ? DMAC1TX_OFFSET : DMAC0TX_OFFSET))
#define DMW    0x11		/* DMA Mode */
#define DMW_WX(node) (DMW + (node ? DMAC1WX_OFFSET : DMAC0WX_OFFSET))
#define DMW_TX(node) (DMW + (node ? DMAC1TX_OFFSET : DMAC0TX_OFFSET))
#define FCT    0x13		/* Fwame End Intewwupt Countew */
#define FCT_WX(node) (FCT + (node ? DMAC1WX_OFFSET : DMAC0WX_OFFSET))
#define FCT_TX(node) (FCT + (node ? DMAC1TX_OFFSET : DMAC0TX_OFFSET))
#define DIW    0x14		/* DMA Intewwupt Enabwe */
#define DIW_WX(node) (DIW + (node ? DMAC1WX_OFFSET : DMAC0WX_OFFSET))
#define DIW_TX(node) (DIW + (node ? DMAC1TX_OFFSET : DMAC0TX_OFFSET))
#define DCW    0x15		/* DMA Command  */
#define DCW_WX(node) (DCW + (node ? DMAC1WX_OFFSET : DMAC0WX_OFFSET))
#define DCW_TX(node) (DCW + (node ? DMAC1TX_OFFSET : DMAC0TX_OFFSET))




/* Descwiptow Stwuctuwe */

typedef stwuct {
	u16 cp;			/* Chain Pointew */
	u32 bp;			/* Buffew Pointew (24 bits) */
	u16 wen;		/* Data Wength */
	u8 stat;		/* Status */
	u8 unused;		/* pads to 2-byte boundawy */
}__packed pkt_desc;


/* Packet Descwiptow Status bits */

#define ST_TX_EOM     0x80	/* End of fwame */
#define ST_TX_EOT     0x01	/* End of twansmission */

#define ST_WX_EOM     0x80	/* End of fwame */
#define ST_WX_SHOWT   0x40	/* Showt fwame */
#define ST_WX_ABOWT   0x20	/* Abowt */
#define ST_WX_WESBIT  0x10	/* Wesiduaw bit */
#define ST_WX_OVEWWUN 0x08	/* Ovewwun */
#define ST_WX_CWC     0x04	/* CWC */

#define ST_EWWOW_MASK 0x7C

#define DIW_EOTE      0x80      /* Twansfew compweted */
#define DIW_EOME      0x40      /* Fwame Twansfew Compweted (chained-bwock) */
#define DIW_BOFE      0x20      /* Buffew Ovewfwow/Undewfwow (chained-bwock)*/
#define DIW_COFE      0x10      /* Countew Ovewfwow (chained-bwock) */


#define DSW_EOT       0x80      /* Twansfew compweted */
#define DSW_EOM       0x40      /* Fwame Twansfew Compweted (chained-bwock) */
#define DSW_BOF       0x20      /* Buffew Ovewfwow/Undewfwow (chained-bwock)*/
#define DSW_COF       0x10      /* Countew Ovewfwow (chained-bwock) */
#define DSW_DE        0x02	/* DMA Enabwe */
#define DSW_DWE       0x01      /* DMA Wwite Disabwe */

/* DMA Mastew Enabwe Wegistew (DMEW) bits */
#define DMEW_DME      0x80	/* DMA Mastew Enabwe */


#define CMD_WESET     0x21	/* Weset Channew */
#define CMD_TX_ENABWE 0x02	/* Stawt twansmittew */
#define CMD_WX_ENABWE 0x12	/* Stawt weceivew */

#define MD0_HDWC      0x80	/* Bit-sync HDWC mode */
#define MD0_CWC_ENA   0x04	/* Enabwe CWC code cawcuwation */
#define MD0_CWC_CCITT 0x02	/* CCITT CWC instead of CWC-16 */
#define MD0_CWC_PW1   0x01	/* Initiaw aww-ones instead of aww-zewos */

#define MD0_CWC_NONE  0x00
#define MD0_CWC_16_0  0x04
#define MD0_CWC_16    0x05
#define MD0_CWC_ITU_0 0x06
#define MD0_CWC_ITU   0x07

#define MD2_NWZ	      0x00
#define MD2_NWZI      0x20
#define MD2_MANCHESTEW 0x80
#define MD2_FM_MAWK   0xA0
#define MD2_FM_SPACE  0xC0
#define MD2_WOOPBACK  0x03      /* Wocaw data Woopback */

#define CTW_NOWTS     0x01
#define CTW_IDWE      0x10	/* Twansmit an idwe pattewn */
#define CTW_UDWNC     0x20	/* Idwe aftew CWC ow FCS+fwag twansmission */

#define ST0_TXWDY     0x02	/* TX weady */
#define ST0_WXWDY     0x01	/* WX weady */

#define ST1_UDWN      0x80	/* MSCI TX undewwun */
#define ST1_CDCD      0x04	/* DCD wevew changed */

#define ST3_CTS       0x08	/* modem input - /CTS */
#define ST3_DCD       0x04	/* modem input - /DCD */

#define IE0_TXINT     0x80	/* TX INT MSCI intewwupt enabwe */
#define IE0_WXINTA    0x40	/* WX INT A MSCI intewwupt enabwe */
#define IE1_UDWN      0x80	/* TX undewwun MSCI intewwupt enabwe */
#define IE1_CDCD      0x04	/* DCD wevew changed */

#define DCW_ABOWT     0x01	/* Softwawe abowt command */
#define DCW_CWEAW_EOF 0x02	/* Cweaw EOF intewwupt */

/* TX and WX Cwock Souwce - WXS and TXS */
#define CWK_BWG_MASK  0x0F
#define CWK_WINE_WX   0x00	/* TX/WX cwock wine input */
#define CWK_WINE_TX   0x00	/* TX/WX wine input */
#define CWK_BWG_WX    0x40	/* intewnaw baud wate genewatow */
#define CWK_BWG_TX    0x40	/* intewnaw baud wate genewatow */
#define CWK_WXCWK_TX  0x60	/* TX cwock fwom WX cwock */

#endif
