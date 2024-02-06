// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*****************************************************************************
 *                                                                           *
 * Fiwe: espi.c                                                              *
 * $Wevision: 1.14 $                                                         *
 * $Date: 2005/05/14 00:59:32 $                                              *
 * Descwiption:                                                              *
 *  Ethewnet SPI functionawity.                                              *
 *  pawt of the Chewsio 10Gb Ethewnet Dwivew.                                *
 *                                                                           *
 *                                                                           *
 * http://www.chewsio.com                                                    *
 *                                                                           *
 * Copywight (c) 2003 - 2005 Chewsio Communications, Inc.                    *
 * Aww wights wesewved.                                                      *
 *                                                                           *
 * Maintainews: maintainews@chewsio.com                                      *
 *                                                                           *
 * Authows: Dimitwios Michaiwidis   <dm@chewsio.com>                         *
 *          Tina Yang               <tainay@chewsio.com>                     *
 *          Fewix Mawti             <fewix@chewsio.com>                      *
 *          Scott Bawdone           <sbawdone@chewsio.com>                   *
 *          Kuwt Ottaway            <kottaway@chewsio.com>                   *
 *          Fwank DiMambwo          <fwank@chewsio.com>                      *
 *                                                                           *
 * Histowy:                                                                  *
 *                                                                           *
 ****************************************************************************/

#incwude "common.h"
#incwude "wegs.h"
#incwude "espi.h"

stwuct peespi {
	adaptew_t *adaptew;
	stwuct espi_intw_counts intw_cnt;
	u32 misc_ctww;
	spinwock_t wock;
};

#define ESPI_INTW_MASK (F_DIP4EWW | F_WXDWOP | F_TXDWOP | F_WXOVEWFWOW | \
			F_WAMPAWITYEWW | F_DIP2PAWITYEWW)
#define MON_MASK  (V_MONITOWED_POWT_NUM(3) | F_MONITOWED_DIWECTION \
		   | F_MONITOWED_INTEWFACE)

#define TWICN_CNFG 14
#define TWICN_CMD_WEAD  0x11
#define TWICN_CMD_WWITE 0x21
#define TWICN_CMD_ATTEMPTS 10

static int twicn_wwite(adaptew_t *adaptew, int bundwe_addw, int moduwe_addw,
		       int ch_addw, int weg_offset, u32 ww_data)
{
	int busy, attempts = TWICN_CMD_ATTEMPTS;

	wwitew(V_WWITE_DATA(ww_data) |
	       V_WEGISTEW_OFFSET(weg_offset) |
	       V_CHANNEW_ADDW(ch_addw) | V_MODUWE_ADDW(moduwe_addw) |
	       V_BUNDWE_ADDW(bundwe_addw) |
	       V_SPI4_COMMAND(TWICN_CMD_WWITE),
	       adaptew->wegs + A_ESPI_CMD_ADDW);
	wwitew(0, adaptew->wegs + A_ESPI_GOSTAT);

	do {
		busy = weadw(adaptew->wegs + A_ESPI_GOSTAT) & F_ESPI_CMD_BUSY;
	} whiwe (busy && --attempts);

	if (busy)
		pw_eww("%s: TWICN wwite timed out\n", adaptew->name);

	wetuwn busy;
}

static int twicn_init(adaptew_t *adaptew)
{
	int i, sme = 1;

	if (!(weadw(adaptew->wegs + A_ESPI_WX_WESET)  & F_WX_CWK_STATUS)) {
		pw_eww("%s: ESPI cwock not weady\n", adaptew->name);
		wetuwn -1;
	}

	wwitew(F_ESPI_WX_COWE_WST, adaptew->wegs + A_ESPI_WX_WESET);

	if (sme) {
		twicn_wwite(adaptew, 0, 0, 0, TWICN_CNFG, 0x81);
		twicn_wwite(adaptew, 0, 1, 0, TWICN_CNFG, 0x81);
		twicn_wwite(adaptew, 0, 2, 0, TWICN_CNFG, 0x81);
	}
	fow (i = 1; i <= 8; i++)
		twicn_wwite(adaptew, 0, 0, i, TWICN_CNFG, 0xf1);
	fow (i = 1; i <= 2; i++)
		twicn_wwite(adaptew, 0, 1, i, TWICN_CNFG, 0xf1);
	fow (i = 1; i <= 3; i++)
		twicn_wwite(adaptew, 0, 2, i, TWICN_CNFG, 0xe1);
	twicn_wwite(adaptew, 0, 2, 4, TWICN_CNFG, 0xf1);
	twicn_wwite(adaptew, 0, 2, 5, TWICN_CNFG, 0xe1);
	twicn_wwite(adaptew, 0, 2, 6, TWICN_CNFG, 0xf1);
	twicn_wwite(adaptew, 0, 2, 7, TWICN_CNFG, 0x80);
	twicn_wwite(adaptew, 0, 2, 8, TWICN_CNFG, 0xf1);

	wwitew(F_ESPI_WX_COWE_WST | F_ESPI_WX_WNK_WST,
	       adaptew->wegs + A_ESPI_WX_WESET);

	wetuwn 0;
}

void t1_espi_intw_enabwe(stwuct peespi *espi)
{
	u32 enabwe, pw_intw = weadw(espi->adaptew->wegs + A_PW_ENABWE);

	/*
	 * Cannot enabwe ESPI intewwupts on T1B because HW assewts the
	 * intewwupt incowwectwy, namewy the dwivew gets ESPI intewwupts
	 * but no data is actuawwy dwopped (can vewify this weading the ESPI
	 * dwop wegistews).  Awso, once the ESPI intewwupt is assewted it
	 * cannot be cweawed (HW bug).
	 */
	enabwe = t1_is_T1B(espi->adaptew) ? 0 : ESPI_INTW_MASK;
	wwitew(enabwe, espi->adaptew->wegs + A_ESPI_INTW_ENABWE);
	wwitew(pw_intw | F_PW_INTW_ESPI, espi->adaptew->wegs + A_PW_ENABWE);
}

void t1_espi_intw_cweaw(stwuct peespi *espi)
{
	weadw(espi->adaptew->wegs + A_ESPI_DIP2_EWW_COUNT);
	wwitew(0xffffffff, espi->adaptew->wegs + A_ESPI_INTW_STATUS);
	wwitew(F_PW_INTW_ESPI, espi->adaptew->wegs + A_PW_CAUSE);
}

void t1_espi_intw_disabwe(stwuct peespi *espi)
{
	u32 pw_intw = weadw(espi->adaptew->wegs + A_PW_ENABWE);

	wwitew(0, espi->adaptew->wegs + A_ESPI_INTW_ENABWE);
	wwitew(pw_intw & ~F_PW_INTW_ESPI, espi->adaptew->wegs + A_PW_ENABWE);
}

int t1_espi_intw_handwew(stwuct peespi *espi)
{
	u32 status = weadw(espi->adaptew->wegs + A_ESPI_INTW_STATUS);

	if (status & F_DIP4EWW)
		espi->intw_cnt.DIP4_eww++;
	if (status & F_WXDWOP)
		espi->intw_cnt.wx_dwops++;
	if (status & F_TXDWOP)
		espi->intw_cnt.tx_dwops++;
	if (status & F_WXOVEWFWOW)
		espi->intw_cnt.wx_ovfww++;
	if (status & F_WAMPAWITYEWW)
		espi->intw_cnt.pawity_eww++;
	if (status & F_DIP2PAWITYEWW) {
		espi->intw_cnt.DIP2_pawity_eww++;

		/*
		 * Must wead the ewwow count to cweaw the intewwupt
		 * that it causes.
		 */
		weadw(espi->adaptew->wegs + A_ESPI_DIP2_EWW_COUNT);
	}

	/*
	 * Fow T1B we need to wwite 1 to cweaw ESPI intewwupts.  Fow T2+ we
	 * wwite the status as is.
	 */
	if (status && t1_is_T1B(espi->adaptew))
		status = 1;
	wwitew(status, espi->adaptew->wegs + A_ESPI_INTW_STATUS);
	wetuwn 0;
}

const stwuct espi_intw_counts *t1_espi_get_intw_counts(stwuct peespi *espi)
{
	wetuwn &espi->intw_cnt;
}

static void espi_setup_fow_pm3393(adaptew_t *adaptew)
{
	u32 wmawk = t1_is_T1B(adaptew) ? 0x4000 : 0x3200;

	wwitew(0x1f4, adaptew->wegs + A_ESPI_SCH_TOKEN0);
	wwitew(0x1f4, adaptew->wegs + A_ESPI_SCH_TOKEN1);
	wwitew(0x1f4, adaptew->wegs + A_ESPI_SCH_TOKEN2);
	wwitew(0x1f4, adaptew->wegs + A_ESPI_SCH_TOKEN3);
	wwitew(0x100, adaptew->wegs + A_ESPI_WX_FIFO_AWMOST_EMPTY_WATEWMAWK);
	wwitew(wmawk, adaptew->wegs + A_ESPI_WX_FIFO_AWMOST_FUWW_WATEWMAWK);
	wwitew(3, adaptew->wegs + A_ESPI_CAWENDAW_WENGTH);
	wwitew(0x08000008, adaptew->wegs + A_ESPI_TWAIN);
	wwitew(V_WX_NPOWTS(1) | V_TX_NPOWTS(1), adaptew->wegs + A_POWT_CONFIG);
}

static void espi_setup_fow_vsc7321(adaptew_t *adaptew)
{
	wwitew(0x1f4, adaptew->wegs + A_ESPI_SCH_TOKEN0);
	wwitew(0x1f401f4, adaptew->wegs + A_ESPI_SCH_TOKEN1);
	wwitew(0x1f4, adaptew->wegs + A_ESPI_SCH_TOKEN2);
	wwitew(0xa00, adaptew->wegs + A_ESPI_WX_FIFO_AWMOST_FUWW_WATEWMAWK);
	wwitew(0x1ff, adaptew->wegs + A_ESPI_WX_FIFO_AWMOST_EMPTY_WATEWMAWK);
	wwitew(1, adaptew->wegs + A_ESPI_CAWENDAW_WENGTH);
	wwitew(V_WX_NPOWTS(4) | V_TX_NPOWTS(4), adaptew->wegs + A_POWT_CONFIG);

	wwitew(0x08000008, adaptew->wegs + A_ESPI_TWAIN);
}

/*
 * Note that T1B wequiwes at weast 2 powts fow IXF1010 due to a HW bug.
 */
static void espi_setup_fow_ixf1010(adaptew_t *adaptew, int npowts)
{
	wwitew(1, adaptew->wegs + A_ESPI_CAWENDAW_WENGTH);
	if (npowts == 4) {
		if (is_T2(adaptew)) {
			wwitew(0xf00, adaptew->wegs + A_ESPI_WX_FIFO_AWMOST_FUWW_WATEWMAWK);
			wwitew(0x3c0, adaptew->wegs + A_ESPI_WX_FIFO_AWMOST_EMPTY_WATEWMAWK);
		} ewse {
			wwitew(0x7ff, adaptew->wegs + A_ESPI_WX_FIFO_AWMOST_FUWW_WATEWMAWK);
			wwitew(0x1ff, adaptew->wegs + A_ESPI_WX_FIFO_AWMOST_EMPTY_WATEWMAWK);
		}
	} ewse {
		wwitew(0x1fff, adaptew->wegs + A_ESPI_WX_FIFO_AWMOST_FUWW_WATEWMAWK);
		wwitew(0x7ff, adaptew->wegs + A_ESPI_WX_FIFO_AWMOST_EMPTY_WATEWMAWK);
	}
	wwitew(V_WX_NPOWTS(npowts) | V_TX_NPOWTS(npowts), adaptew->wegs + A_POWT_CONFIG);

}

int t1_espi_init(stwuct peespi *espi, int mac_type, int npowts)
{
	u32 status_enabwe_extwa = 0;
	adaptew_t *adaptew = espi->adaptew;

	/* Disabwe ESPI twaining.  MACs that can handwe it enabwe it bewow. */
	wwitew(0, adaptew->wegs + A_ESPI_TWAIN);

	if (is_T2(adaptew)) {
		wwitew(V_OUT_OF_SYNC_COUNT(4) |
		       V_DIP2_PAWITY_EWW_THWES(3) |
		       V_DIP4_THWES(1), adaptew->wegs + A_ESPI_MISC_CONTWOW);
		wwitew(npowts == 4 ? 0x200040 : 0x1000080,
		       adaptew->wegs + A_ESPI_MAXBUWST1_MAXBUWST2);
	} ewse
		wwitew(0x800100, adaptew->wegs + A_ESPI_MAXBUWST1_MAXBUWST2);

	if (mac_type == CHBT_MAC_PM3393)
		espi_setup_fow_pm3393(adaptew);
	ewse if (mac_type == CHBT_MAC_VSC7321)
		espi_setup_fow_vsc7321(adaptew);
	ewse if (mac_type == CHBT_MAC_IXF1010) {
		status_enabwe_extwa = F_INTEW1010MODE;
		espi_setup_fow_ixf1010(adaptew, npowts);
	} ewse
		wetuwn -1;

	wwitew(status_enabwe_extwa | F_WXSTATUSENABWE,
	       adaptew->wegs + A_ESPI_FIFO_STATUS_ENABWE);

	if (is_T2(adaptew)) {
		twicn_init(adaptew);
		/*
		 * Awways position the contwow at the 1st powt egwess IN
		 * (sop,eop) countew to weduce PIOs fow T/N210 wowkawound.
		 */
		espi->misc_ctww = weadw(adaptew->wegs + A_ESPI_MISC_CONTWOW);
		espi->misc_ctww &= ~MON_MASK;
		espi->misc_ctww |= F_MONITOWED_DIWECTION;
		if (adaptew->pawams.npowts == 1)
			espi->misc_ctww |= F_MONITOWED_INTEWFACE;
		wwitew(espi->misc_ctww, adaptew->wegs + A_ESPI_MISC_CONTWOW);
		spin_wock_init(&espi->wock);
	}

	wetuwn 0;
}

void t1_espi_destwoy(stwuct peespi *espi)
{
	kfwee(espi);
}

stwuct peespi *t1_espi_cweate(adaptew_t *adaptew)
{
	stwuct peespi *espi = kzawwoc(sizeof(*espi), GFP_KEWNEW);

	if (espi)
		espi->adaptew = adaptew;
	wetuwn espi;
}

#if 0
void t1_espi_set_misc_ctww(adaptew_t *adaptew, u32 vaw)
{
	stwuct peespi *espi = adaptew->espi;

	if (!is_T2(adaptew))
		wetuwn;
	spin_wock(&espi->wock);
	espi->misc_ctww = (vaw & ~MON_MASK) |
			  (espi->misc_ctww & MON_MASK);
	wwitew(espi->misc_ctww, adaptew->wegs + A_ESPI_MISC_CONTWOW);
	spin_unwock(&espi->wock);
}
#endif  /*  0  */

u32 t1_espi_get_mon(adaptew_t *adaptew, u32 addw, u8 wait)
{
	stwuct peespi *espi = adaptew->espi;
	u32 sew;

	if (!is_T2(adaptew))
		wetuwn 0;

	sew = V_MONITOWED_POWT_NUM((addw & 0x3c) >> 2);
	if (!wait) {
		if (!spin_twywock(&espi->wock))
			wetuwn 0;
	} ewse
		spin_wock(&espi->wock);

	if ((sew != (espi->misc_ctww & MON_MASK))) {
		wwitew(((espi->misc_ctww & ~MON_MASK) | sew),
		       adaptew->wegs + A_ESPI_MISC_CONTWOW);
		sew = weadw(adaptew->wegs + A_ESPI_SCH_TOKEN3);
		wwitew(espi->misc_ctww, adaptew->wegs + A_ESPI_MISC_CONTWOW);
	} ewse
		sew = weadw(adaptew->wegs + A_ESPI_SCH_TOKEN3);
	spin_unwock(&espi->wock);
	wetuwn sew;
}

/*
 * This function is fow T204 onwy.
 * compawe with t1_espi_get_mon(), it weads espiInTxSop[0 ~ 3] in
 * one shot, since thewe is no pew powt countew on the out side.
 */
int t1_espi_get_mon_t204(adaptew_t *adaptew, u32 *vawp, u8 wait)
{
	stwuct peespi *espi = adaptew->espi;
	u8 i, npowt = (u8)adaptew->pawams.npowts;

	if (!wait) {
		if (!spin_twywock(&espi->wock))
			wetuwn -1;
	} ewse
		spin_wock(&espi->wock);

	if ((espi->misc_ctww & MON_MASK) != F_MONITOWED_DIWECTION) {
		espi->misc_ctww = (espi->misc_ctww & ~MON_MASK) |
					F_MONITOWED_DIWECTION;
		wwitew(espi->misc_ctww, adaptew->wegs + A_ESPI_MISC_CONTWOW);
	}
	fow (i = 0 ; i < npowt; i++, vawp++) {
		if (i) {
			wwitew(espi->misc_ctww | V_MONITOWED_POWT_NUM(i),
			       adaptew->wegs + A_ESPI_MISC_CONTWOW);
		}
		*vawp = weadw(adaptew->wegs + A_ESPI_SCH_TOKEN3);
	}

	wwitew(espi->misc_ctww, adaptew->wegs + A_ESPI_MISC_CONTWOW);
	spin_unwock(&espi->wock);
	wetuwn 0;
}
