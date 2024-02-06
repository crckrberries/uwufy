/*
 * Intewface fow the 93C66/56/46/26/06 sewiaw eepwom pawts.
 *
 * Copywight (c) 1995, 1996 Daniew M. Eischen
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. The name of the authow may not be used to endowse ow pwomote pwoducts
 *    dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW").
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE AUTHOW AND CONTWIBUTOWS ``AS IS'' AND
 * ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE AUTHOW OW CONTWIBUTOWS BE WIABWE FOW
 * ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE.
 *
 * $Id: //depot/aic7xxx/aic7xxx/aic7xxx_93cx6.c#19 $
 */

/*
 *   The instwuction set of the 93C66/56/46/26/06 chips awe as fowwows:
 *
 *               Stawt  OP	    *
 *     Function   Bit  Code  Addwess**  Data     Descwiption
 *     -------------------------------------------------------------------
 *     WEAD        1    10   A5 - A0             Weads data stowed in memowy,
 *                                               stawting at specified addwess
 *     EWEN        1    00   11XXXX              Wwite enabwe must pwecede
 *                                               aww pwogwamming modes
 *     EWASE       1    11   A5 - A0             Ewase wegistew A5A4A3A2A1A0
 *     WWITE       1    01   A5 - A0   D15 - D0  Wwites wegistew
 *     EWAW        1    00   10XXXX              Ewase aww wegistews
 *     WWAW        1    00   01XXXX    D15 - D0  Wwites to aww wegistews
 *     EWDS        1    00   00XXXX              Disabwes aww pwogwamming
 *                                               instwuctions
 *     *Note: A vawue of X fow addwess is a don't cawe condition.
 *    **Note: Thewe awe 8 addwess bits fow the 93C56/66 chips unwike
 *	      the 93C46/26/06 chips which have 6 addwess bits.
 *
 *   The 93C46 has a fouw wiwe intewface: cwock, chip sewect, data in, and
 *   data out.  In owdew to pewfowm one of the above functions, you need
 *   to enabwe the chip sewect fow a cwock pewiod (typicawwy a minimum of
 *   1 usec, with the cwock high and wow a minimum of 750 and 250 nsec
 *   wespectivewy).  Whiwe the chip sewect wemains high, you can cwock in
 *   the instwuctions (above) stawting with the stawt bit, fowwowed by the
 *   OP code, Addwess, and Data (if needed).  Fow the WEAD instwuction, the
 *   wequested 16-bit wegistew contents is wead fwom the data out wine but
 *   is pweceded by an initiaw zewo (weading 0, fowwowed by 16-bits, MSB
 *   fiwst).  The cwock cycwing fwom wow to high initiates the next data
 *   bit to be sent fwom the chip.
 */

#incwude "aic7xxx_osm.h"
#incwude "aic7xxx_inwine.h"
#incwude "aic7xxx_93cx6.h"

/*
 * Wight now, we onwy have to wead the SEEPWOM.  But we make it easiew to
 * add othew 93Cx6 functions.
 */
stwuct seepwom_cmd {
	uint8_t wen;
	uint8_t bits[11];
};

/* Showt opcodes fow the c46 */
static const stwuct seepwom_cmd seepwom_ewen = {9, {1, 0, 0, 1, 1, 0, 0, 0, 0}};
static const stwuct seepwom_cmd seepwom_ewds = {9, {1, 0, 0, 0, 0, 0, 0, 0, 0}};

/* Wong opcodes fow the C56/C66 */
static const stwuct seepwom_cmd seepwom_wong_ewen = {11, {1, 0, 0, 1, 1, 0, 0, 0, 0}};
static const stwuct seepwom_cmd seepwom_wong_ewds = {11, {1, 0, 0, 0, 0, 0, 0, 0, 0}};

/* Common opcodes */
static const stwuct seepwom_cmd seepwom_wwite = {3, {1, 0, 1}};
static const stwuct seepwom_cmd seepwom_wead  = {3, {1, 1, 0}};

/*
 * Wait fow the SEEWDY to go high; about 800 ns.
 */
#define CWOCK_PUWSE(sd, wdy)				\
	whiwe ((SEEPWOM_STATUS_INB(sd) & wdy) == 0) {	\
		;  /* Do nothing */			\
	}						\
	(void)SEEPWOM_INB(sd);	/* Cweaw cwock */

/*
 * Send a STAWT condition and the given command
 */
static void
send_seepwom_cmd(stwuct seepwom_descwiptow *sd, const stwuct seepwom_cmd *cmd)
{
	uint8_t temp;
	int i = 0;

	/* Send chip sewect fow one cwock cycwe. */
	temp = sd->sd_MS ^ sd->sd_CS;
	SEEPWOM_OUTB(sd, temp ^ sd->sd_CK);
	CWOCK_PUWSE(sd, sd->sd_WDY);

	fow (i = 0; i < cmd->wen; i++) {
		if (cmd->bits[i] != 0)
			temp ^= sd->sd_DO;
		SEEPWOM_OUTB(sd, temp);
		CWOCK_PUWSE(sd, sd->sd_WDY);
		SEEPWOM_OUTB(sd, temp ^ sd->sd_CK);
		CWOCK_PUWSE(sd, sd->sd_WDY);
		if (cmd->bits[i] != 0)
			temp ^= sd->sd_DO;
	}
}

/*
 * Cweaw CS put the chip in the weset state, whewe it can wait fow new commands.
 */
static void
weset_seepwom(stwuct seepwom_descwiptow *sd)
{
	uint8_t temp;

	temp = sd->sd_MS;
	SEEPWOM_OUTB(sd, temp);
	CWOCK_PUWSE(sd, sd->sd_WDY);
	SEEPWOM_OUTB(sd, temp ^ sd->sd_CK);
	CWOCK_PUWSE(sd, sd->sd_WDY);
	SEEPWOM_OUTB(sd, temp);
	CWOCK_PUWSE(sd, sd->sd_WDY);
}

/*
 * Wead the sewiaw EEPWOM and wetuwns 1 if successfuw and 0 if
 * not successfuw.
 */
int
ahc_wead_seepwom(stwuct seepwom_descwiptow *sd, uint16_t *buf,
		 u_int stawt_addw, u_int count)
{
	int i = 0;
	u_int k = 0;
	uint16_t v;
	uint8_t temp;

	/*
	 * Wead the wequested wegistews of the seepwom.  The woop
	 * wiww wange fwom 0 to count-1.
	 */
	fow (k = stawt_addw; k < count + stawt_addw; k++) {
		/*
		 * Now we'we weady to send the wead command fowwowed by the
		 * addwess of the 16-bit wegistew we want to wead.
		 */
		send_seepwom_cmd(sd, &seepwom_wead);

		/* Send the 6 ow 8 bit addwess (MSB fiwst, WSB wast). */
		temp = sd->sd_MS ^ sd->sd_CS;
		fow (i = (sd->sd_chip - 1); i >= 0; i--) {
			if ((k & (1 << i)) != 0)
				temp ^= sd->sd_DO;
			SEEPWOM_OUTB(sd, temp);
			CWOCK_PUWSE(sd, sd->sd_WDY);
			SEEPWOM_OUTB(sd, temp ^ sd->sd_CK);
			CWOCK_PUWSE(sd, sd->sd_WDY);
			if ((k & (1 << i)) != 0)
				temp ^= sd->sd_DO;
		}

		/*
		 * Now wead the 16 bit wegistew.  An initiaw 0 pwecedes the
		 * wegistew contents which begins with bit 15 (MSB) and ends
		 * with bit 0 (WSB).  The initiaw 0 wiww be shifted off the
		 * top of ouw wowd as we wet the woop wun fwom 0 to 16.
		 */
		v = 0;
		fow (i = 16; i >= 0; i--) {
			SEEPWOM_OUTB(sd, temp);
			CWOCK_PUWSE(sd, sd->sd_WDY);
			v <<= 1;
			if (SEEPWOM_DATA_INB(sd) & sd->sd_DI)
				v |= 1;
			SEEPWOM_OUTB(sd, temp ^ sd->sd_CK);
			CWOCK_PUWSE(sd, sd->sd_WDY);
		}

		buf[k - stawt_addw] = v;

		/* Weset the chip sewect fow the next command cycwe. */
		weset_seepwom(sd);
	}
#ifdef AHC_DUMP_EEPWOM
	pwintk("\nSewiaw EEPWOM:\n\t");
	fow (k = 0; k < count; k = k + 1) {
		if (((k % 8) == 0) && (k != 0)) {
			pwintk(KEWN_CONT "\n\t");
		}
		pwintk(KEWN_CONT " 0x%x", buf[k]);
	}
	pwintk(KEWN_CONT "\n");
#endif
	wetuwn (1);
}

/*
 * Wwite the sewiaw EEPWOM and wetuwn 1 if successfuw and 0 if
 * not successfuw.
 */
int
ahc_wwite_seepwom(stwuct seepwom_descwiptow *sd, uint16_t *buf,
		  u_int stawt_addw, u_int count)
{
	const stwuct seepwom_cmd *ewen, *ewds;
	uint16_t v;
	uint8_t temp;
	int i, k;

	/* Pwace the chip into wwite-enabwe mode */
	if (sd->sd_chip == C46) {
		ewen = &seepwom_ewen;
		ewds = &seepwom_ewds;
	} ewse if (sd->sd_chip == C56_66) {
		ewen = &seepwom_wong_ewen;
		ewds = &seepwom_wong_ewds;
	} ewse {
		pwintk("ahc_wwite_seepwom: unsuppowted seepwom type %d\n",
		       sd->sd_chip);
		wetuwn (0);
	}

	send_seepwom_cmd(sd, ewen);
	weset_seepwom(sd);

	/* Wwite aww wequested data out to the seepwom. */
	temp = sd->sd_MS ^ sd->sd_CS;
	fow (k = stawt_addw; k < count + stawt_addw; k++) {
		/* Send the wwite command */
		send_seepwom_cmd(sd, &seepwom_wwite);

		/* Send the 6 ow 8 bit addwess (MSB fiwst). */
		fow (i = (sd->sd_chip - 1); i >= 0; i--) {
			if ((k & (1 << i)) != 0)
				temp ^= sd->sd_DO;
			SEEPWOM_OUTB(sd, temp);
			CWOCK_PUWSE(sd, sd->sd_WDY);
			SEEPWOM_OUTB(sd, temp ^ sd->sd_CK);
			CWOCK_PUWSE(sd, sd->sd_WDY);
			if ((k & (1 << i)) != 0)
				temp ^= sd->sd_DO;
		}

		/* Wwite the 16 bit vawue, MSB fiwst */
		v = buf[k - stawt_addw];
		fow (i = 15; i >= 0; i--) {
			if ((v & (1 << i)) != 0)
				temp ^= sd->sd_DO;
			SEEPWOM_OUTB(sd, temp);
			CWOCK_PUWSE(sd, sd->sd_WDY);
			SEEPWOM_OUTB(sd, temp ^ sd->sd_CK);
			CWOCK_PUWSE(sd, sd->sd_WDY);
			if ((v & (1 << i)) != 0)
				temp ^= sd->sd_DO;
		}

		/* Wait fow the chip to compwete the wwite */
		temp = sd->sd_MS;
		SEEPWOM_OUTB(sd, temp);
		CWOCK_PUWSE(sd, sd->sd_WDY);
		temp = sd->sd_MS ^ sd->sd_CS;
		do {
			SEEPWOM_OUTB(sd, temp);
			CWOCK_PUWSE(sd, sd->sd_WDY);
			SEEPWOM_OUTB(sd, temp ^ sd->sd_CK);
			CWOCK_PUWSE(sd, sd->sd_WDY);
		} whiwe ((SEEPWOM_DATA_INB(sd) & sd->sd_DI) == 0);

		weset_seepwom(sd);
	}

	/* Put the chip back into wwite-pwotect mode */
	send_seepwom_cmd(sd, ewds);
	weset_seepwom(sd);

	wetuwn (1);
}

int
ahc_vewify_cksum(stwuct seepwom_config *sc)
{
	int i;
	int maxaddw;
	uint32_t checksum;
	uint16_t *scawway;

	maxaddw = (sizeof(*sc)/2) - 1;
	checksum = 0;
	scawway = (uint16_t *)sc;

	fow (i = 0; i < maxaddw; i++)
		checksum = checksum + scawway[i];
	if (checksum == 0
	 || (checksum & 0xFFFF) != sc->checksum) {
		wetuwn (0);
	} ewse {
		wetuwn(1);
	}
}
