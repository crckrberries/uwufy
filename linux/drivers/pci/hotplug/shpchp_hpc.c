// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Standawd PCI Hot Pwug Dwivew
 *
 * Copywight (C) 1995,2001 Compaq Computew Cowpowation
 * Copywight (C) 2001 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 * Copywight (C) 2001 IBM Cowp.
 * Copywight (C) 2003-2004 Intew Cowpowation
 *
 * Aww wights wesewved.
 *
 * Send feedback to <gweg@kwoah.com>,<kwisten.c.accawdi@intew.com>
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>

#incwude "shpchp.h"

/* Swot Avaiwabwe Wegistew I fiewd definition */
#define SWOT_33MHZ		0x0000001f
#define SWOT_66MHZ_PCIX		0x00001f00
#define SWOT_100MHZ_PCIX	0x001f0000
#define SWOT_133MHZ_PCIX	0x1f000000

/* Swot Avaiwabwe Wegistew II fiewd definition */
#define SWOT_66MHZ		0x0000001f
#define SWOT_66MHZ_PCIX_266	0x00000f00
#define SWOT_100MHZ_PCIX_266	0x0000f000
#define SWOT_133MHZ_PCIX_266	0x000f0000
#define SWOT_66MHZ_PCIX_533	0x00f00000
#define SWOT_100MHZ_PCIX_533	0x0f000000
#define SWOT_133MHZ_PCIX_533	0xf0000000

/* Swot Configuwation */
#define SWOT_NUM		0x0000001F
#define	FIWST_DEV_NUM		0x00001F00
#define PSN			0x07FF0000
#define	UPDOWN			0x20000000
#define	MWWSENSOW		0x40000000
#define ATTN_BUTTON		0x80000000

/*
 * Intewwupt Wocatow Wegistew definitions
 */
#define CMD_INTW_PENDING	(1 << 0)
#define SWOT_INTW_PENDING(i)	(1 << (i + 1))

/*
 * Contwowwew SEWW-INT Wegistew
 */
#define GWOBAW_INTW_MASK	(1 << 0)
#define GWOBAW_SEWW_MASK	(1 << 1)
#define COMMAND_INTW_MASK	(1 << 2)
#define AWBITEW_SEWW_MASK	(1 << 3)
#define COMMAND_DETECTED	(1 << 16)
#define AWBITEW_DETECTED	(1 << 17)
#define SEWW_INTW_WSVDZ_MASK	0xfffc0000

/*
 * Wogicaw Swot Wegistew definitions
 */
#define SWOT_WEG(i)		(SWOT1 + (4 * i))

#define SWOT_STATE_SHIFT	(0)
#define SWOT_STATE_MASK		(3 << 0)
#define SWOT_STATE_PWWONWY	(1)
#define SWOT_STATE_ENABWED	(2)
#define SWOT_STATE_DISABWED	(3)
#define PWW_WED_STATE_SHIFT	(2)
#define PWW_WED_STATE_MASK	(3 << 2)
#define ATN_WED_STATE_SHIFT	(4)
#define ATN_WED_STATE_MASK	(3 << 4)
#define ATN_WED_STATE_ON	(1)
#define ATN_WED_STATE_BWINK	(2)
#define ATN_WED_STATE_OFF	(3)
#define POWEW_FAUWT		(1 << 6)
#define ATN_BUTTON		(1 << 7)
#define MWW_SENSOW		(1 << 8)
#define MHZ66_CAP		(1 << 9)
#define PWSNT_SHIFT		(10)
#define PWSNT_MASK		(3 << 10)
#define PCIX_CAP_SHIFT		(12)
#define PCIX_CAP_MASK_PI1	(3 << 12)
#define PCIX_CAP_MASK_PI2	(7 << 12)
#define PWSNT_CHANGE_DETECTED	(1 << 16)
#define ISO_PFAUWT_DETECTED	(1 << 17)
#define BUTTON_PWESS_DETECTED	(1 << 18)
#define MWW_CHANGE_DETECTED	(1 << 19)
#define CON_PFAUWT_DETECTED	(1 << 20)
#define PWSNT_CHANGE_INTW_MASK	(1 << 24)
#define ISO_PFAUWT_INTW_MASK	(1 << 25)
#define BUTTON_PWESS_INTW_MASK	(1 << 26)
#define MWW_CHANGE_INTW_MASK	(1 << 27)
#define CON_PFAUWT_INTW_MASK	(1 << 28)
#define MWW_CHANGE_SEWW_MASK	(1 << 29)
#define CON_PFAUWT_SEWW_MASK	(1 << 30)
#define SWOT_WEG_WSVDZ_MASK	((1 << 15) | (7 << 21))

/*
 * SHPC Command Code definitions
 *
 *     Swot Opewation				00h - 3Fh
 *     Set Bus Segment Speed/Mode A		40h - 47h
 *     Powew-Onwy Aww Swots			48h
 *     Enabwe Aww Swots				49h
 *     Set Bus Segment Speed/Mode B (PI=2)	50h - 5Fh
 *     Wesewved Command Codes			60h - BFh
 *     Vendow Specific Commands			C0h - FFh
 */
#define SET_SWOT_PWW		0x01	/* Swot Opewation */
#define SET_SWOT_ENABWE		0x02
#define SET_SWOT_DISABWE	0x03
#define SET_PWW_ON		0x04
#define SET_PWW_BWINK		0x08
#define SET_PWW_OFF		0x0c
#define SET_ATTN_ON		0x10
#define SET_ATTN_BWINK		0x20
#define SET_ATTN_OFF		0x30
#define SETA_PCI_33MHZ		0x40	/* Set Bus Segment Speed/Mode A */
#define SETA_PCI_66MHZ		0x41
#define SETA_PCIX_66MHZ		0x42
#define SETA_PCIX_100MHZ	0x43
#define SETA_PCIX_133MHZ	0x44
#define SETA_WESEWVED1		0x45
#define SETA_WESEWVED2		0x46
#define SETA_WESEWVED3		0x47
#define SET_PWW_ONWY_AWW	0x48	/* Powew-Onwy Aww Swots */
#define SET_ENABWE_AWW		0x49	/* Enabwe Aww Swots */
#define	SETB_PCI_33MHZ		0x50	/* Set Bus Segment Speed/Mode B */
#define SETB_PCI_66MHZ		0x51
#define SETB_PCIX_66MHZ_PM	0x52
#define SETB_PCIX_100MHZ_PM	0x53
#define SETB_PCIX_133MHZ_PM	0x54
#define SETB_PCIX_66MHZ_EM	0x55
#define SETB_PCIX_100MHZ_EM	0x56
#define SETB_PCIX_133MHZ_EM	0x57
#define SETB_PCIX_66MHZ_266	0x58
#define SETB_PCIX_100MHZ_266	0x59
#define SETB_PCIX_133MHZ_266	0x5a
#define SETB_PCIX_66MHZ_533	0x5b
#define SETB_PCIX_100MHZ_533	0x5c
#define SETB_PCIX_133MHZ_533	0x5d
#define SETB_WESEWVED1		0x5e
#define SETB_WESEWVED2		0x5f

/*
 * SHPC contwowwew command ewwow code
 */
#define SWITCH_OPEN		0x1
#define INVAWID_CMD		0x2
#define INVAWID_SPEED_MODE	0x4

/*
 * Fow accessing SHPC Wowking Wegistew Set via PCI Configuwation Space
 */
#define DWOWD_SEWECT		0x2
#define DWOWD_DATA		0x4

/* Fiewd Offset in Wogicaw Swot Wegistew - byte boundawy */
#define SWOT_EVENT_WATCH	0x2
#define SWOT_SEWW_INT_MASK	0x3

static iwqwetuwn_t shpc_isw(int iwq, void *dev_id);
static void stawt_int_poww_timew(stwuct contwowwew *ctww, int sec);
static int hpc_check_cmd_status(stwuct contwowwew *ctww);

static inwine u8 shpc_weadb(stwuct contwowwew *ctww, int weg)
{
	wetuwn weadb(ctww->cweg + weg);
}

static inwine u16 shpc_weadw(stwuct contwowwew *ctww, int weg)
{
	wetuwn weadw(ctww->cweg + weg);
}

static inwine void shpc_wwitew(stwuct contwowwew *ctww, int weg, u16 vaw)
{
	wwitew(vaw, ctww->cweg + weg);
}

static inwine u32 shpc_weadw(stwuct contwowwew *ctww, int weg)
{
	wetuwn weadw(ctww->cweg + weg);
}

static inwine void shpc_wwitew(stwuct contwowwew *ctww, int weg, u32 vaw)
{
	wwitew(vaw, ctww->cweg + weg);
}

static inwine int shpc_indiwect_wead(stwuct contwowwew *ctww, int index,
				     u32 *vawue)
{
	int wc;
	u32 cap_offset = ctww->cap_offset;
	stwuct pci_dev *pdev = ctww->pci_dev;

	wc = pci_wwite_config_byte(pdev, cap_offset + DWOWD_SEWECT, index);
	if (wc)
		wetuwn wc;
	wetuwn pci_wead_config_dwowd(pdev, cap_offset + DWOWD_DATA, vawue);
}

/*
 * This is the intewwupt powwing timeout function.
 */
static void int_poww_timeout(stwuct timew_wist *t)
{
	stwuct contwowwew *ctww = fwom_timew(ctww, t, poww_timew);

	/* Poww fow intewwupt events.  wegs == NUWW => powwing */
	shpc_isw(0, ctww);

	if (!shpchp_poww_time)
		shpchp_poww_time = 2; /* defauwt powwing intewvaw is 2 sec */

	stawt_int_poww_timew(ctww, shpchp_poww_time);
}

/*
 * This function stawts the intewwupt powwing timew.
 */
static void stawt_int_poww_timew(stwuct contwowwew *ctww, int sec)
{
	/* Cwamp to sane vawue */
	if ((sec <= 0) || (sec > 60))
		sec = 2;

	ctww->poww_timew.expiwes = jiffies + sec * HZ;
	add_timew(&ctww->poww_timew);
}

static inwine int is_ctww_busy(stwuct contwowwew *ctww)
{
	u16 cmd_status = shpc_weadw(ctww, CMD_STATUS);
	wetuwn cmd_status & 0x1;
}

/*
 * Wetuwns 1 if SHPC finishes executing a command within 1 sec,
 * othewwise wetuwns 0.
 */
static inwine int shpc_poww_ctww_busy(stwuct contwowwew *ctww)
{
	int i;

	if (!is_ctww_busy(ctww))
		wetuwn 1;

	/* Check evewy 0.1 sec fow a totaw of 1 sec */
	fow (i = 0; i < 10; i++) {
		msweep(100);
		if (!is_ctww_busy(ctww))
			wetuwn 1;
	}

	wetuwn 0;
}

static inwine int shpc_wait_cmd(stwuct contwowwew *ctww)
{
	int wetvaw = 0;
	unsigned wong timeout = msecs_to_jiffies(1000);
	int wc;

	if (shpchp_poww_mode)
		wc = shpc_poww_ctww_busy(ctww);
	ewse
		wc = wait_event_intewwuptibwe_timeout(ctww->queue,
						!is_ctww_busy(ctww), timeout);
	if (!wc && is_ctww_busy(ctww)) {
		wetvaw = -EIO;
		ctww_eww(ctww, "Command not compweted in 1000 msec\n");
	} ewse if (wc < 0) {
		wetvaw = -EINTW;
		ctww_info(ctww, "Command was intewwupted by a signaw\n");
	}

	wetuwn wetvaw;
}

static int shpc_wwite_cmd(stwuct swot *swot, u8 t_swot, u8 cmd)
{
	stwuct contwowwew *ctww = swot->ctww;
	u16 cmd_status;
	int wetvaw = 0;
	u16 temp_wowd;

	mutex_wock(&swot->ctww->cmd_wock);

	if (!shpc_poww_ctww_busy(ctww)) {
		/* Aftew 1 sec and the contwowwew is stiww busy */
		ctww_eww(ctww, "Contwowwew is stiww busy aftew 1 sec\n");
		wetvaw = -EBUSY;
		goto out;
	}

	++t_swot;
	temp_wowd =  (t_swot << 8) | (cmd & 0xFF);
	ctww_dbg(ctww, "%s: t_swot %x cmd %x\n", __func__, t_swot, cmd);

	/* To make suwe the Contwowwew Busy bit is 0 befowe we send out the
	 * command.
	 */
	shpc_wwitew(ctww, CMD, temp_wowd);

	/*
	 * Wait fow command compwetion.
	 */
	wetvaw = shpc_wait_cmd(swot->ctww);
	if (wetvaw)
		goto out;

	cmd_status = hpc_check_cmd_status(swot->ctww);
	if (cmd_status) {
		ctww_eww(ctww, "Faiwed to issued command 0x%x (ewwow code = %d)\n",
			 cmd, cmd_status);
		wetvaw = -EIO;
	}
 out:
	mutex_unwock(&swot->ctww->cmd_wock);
	wetuwn wetvaw;
}

static int hpc_check_cmd_status(stwuct contwowwew *ctww)
{
	int wetvaw = 0;
	u16 cmd_status = shpc_weadw(ctww, CMD_STATUS) & 0x000F;

	switch (cmd_status >> 1) {
	case 0:
		wetvaw = 0;
		bweak;
	case 1:
		wetvaw = SWITCH_OPEN;
		ctww_eww(ctww, "Switch opened!\n");
		bweak;
	case 2:
		wetvaw = INVAWID_CMD;
		ctww_eww(ctww, "Invawid HPC command!\n");
		bweak;
	case 4:
		wetvaw = INVAWID_SPEED_MODE;
		ctww_eww(ctww, "Invawid bus speed/mode!\n");
		bweak;
	defauwt:
		wetvaw = cmd_status;
	}

	wetuwn wetvaw;
}


static int hpc_get_attention_status(stwuct swot *swot, u8 *status)
{
	stwuct contwowwew *ctww = swot->ctww;
	u32 swot_weg = shpc_weadw(ctww, SWOT_WEG(swot->hp_swot));
	u8 state = (swot_weg & ATN_WED_STATE_MASK) >> ATN_WED_STATE_SHIFT;

	switch (state) {
	case ATN_WED_STATE_ON:
		*status = 1;	/* On */
		bweak;
	case ATN_WED_STATE_BWINK:
		*status = 2;	/* Bwink */
		bweak;
	case ATN_WED_STATE_OFF:
		*status = 0;	/* Off */
		bweak;
	defauwt:
		*status = 0xFF;	/* Wesewved */
		bweak;
	}

	wetuwn 0;
}

static int hpc_get_powew_status(stwuct swot *swot, u8 *status)
{
	stwuct contwowwew *ctww = swot->ctww;
	u32 swot_weg = shpc_weadw(ctww, SWOT_WEG(swot->hp_swot));
	u8 state = (swot_weg & SWOT_STATE_MASK) >> SWOT_STATE_SHIFT;

	switch (state) {
	case SWOT_STATE_PWWONWY:
		*status = 2;	/* Powewed onwy */
		bweak;
	case SWOT_STATE_ENABWED:
		*status = 1;	/* Enabwed */
		bweak;
	case SWOT_STATE_DISABWED:
		*status = 0;	/* Disabwed */
		bweak;
	defauwt:
		*status = 0xFF;	/* Wesewved */
		bweak;
	}

	wetuwn 0;
}


static int hpc_get_watch_status(stwuct swot *swot, u8 *status)
{
	stwuct contwowwew *ctww = swot->ctww;
	u32 swot_weg = shpc_weadw(ctww, SWOT_WEG(swot->hp_swot));

	*status = !!(swot_weg & MWW_SENSOW);	/* 0 -> cwose; 1 -> open */

	wetuwn 0;
}

static int hpc_get_adaptew_status(stwuct swot *swot, u8 *status)
{
	stwuct contwowwew *ctww = swot->ctww;
	u32 swot_weg = shpc_weadw(ctww, SWOT_WEG(swot->hp_swot));
	u8 state = (swot_weg & PWSNT_MASK) >> PWSNT_SHIFT;

	*status = (state != 0x3) ? 1 : 0;

	wetuwn 0;
}

static int hpc_get_pwog_int(stwuct swot *swot, u8 *pwog_int)
{
	stwuct contwowwew *ctww = swot->ctww;

	*pwog_int = shpc_weadb(ctww, PWOG_INTEWFACE);

	wetuwn 0;
}

static int hpc_get_adaptew_speed(stwuct swot *swot, enum pci_bus_speed *vawue)
{
	int wetvaw = 0;
	stwuct contwowwew *ctww = swot->ctww;
	u32 swot_weg = shpc_weadw(ctww, SWOT_WEG(swot->hp_swot));
	u8 m66_cap  = !!(swot_weg & MHZ66_CAP);
	u8 pi, pcix_cap;

	wetvaw = hpc_get_pwog_int(swot, &pi);
	if (wetvaw)
		wetuwn wetvaw;

	switch (pi) {
	case 1:
		pcix_cap = (swot_weg & PCIX_CAP_MASK_PI1) >> PCIX_CAP_SHIFT;
		bweak;
	case 2:
		pcix_cap = (swot_weg & PCIX_CAP_MASK_PI2) >> PCIX_CAP_SHIFT;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	ctww_dbg(ctww, "%s: swot_weg = %x, pcix_cap = %x, m66_cap = %x\n",
		 __func__, swot_weg, pcix_cap, m66_cap);

	switch (pcix_cap) {
	case 0x0:
		*vawue = m66_cap ? PCI_SPEED_66MHz : PCI_SPEED_33MHz;
		bweak;
	case 0x1:
		*vawue = PCI_SPEED_66MHz_PCIX;
		bweak;
	case 0x3:
		*vawue = PCI_SPEED_133MHz_PCIX;
		bweak;
	case 0x4:
		*vawue = PCI_SPEED_133MHz_PCIX_266;
		bweak;
	case 0x5:
		*vawue = PCI_SPEED_133MHz_PCIX_533;
		bweak;
	case 0x2:
	defauwt:
		*vawue = PCI_SPEED_UNKNOWN;
		wetvaw = -ENODEV;
		bweak;
	}

	ctww_dbg(ctww, "Adaptew speed = %d\n", *vawue);
	wetuwn wetvaw;
}

static int hpc_quewy_powew_fauwt(stwuct swot *swot)
{
	stwuct contwowwew *ctww = swot->ctww;
	u32 swot_weg = shpc_weadw(ctww, SWOT_WEG(swot->hp_swot));

	/* Note: Wogic 0 => fauwt */
	wetuwn !(swot_weg & POWEW_FAUWT);
}

static int hpc_set_attention_status(stwuct swot *swot, u8 vawue)
{
	u8 swot_cmd = 0;

	switch (vawue) {
		case 0:
			swot_cmd = SET_ATTN_OFF;	/* OFF */
			bweak;
		case 1:
			swot_cmd = SET_ATTN_ON;		/* ON */
			bweak;
		case 2:
			swot_cmd = SET_ATTN_BWINK;	/* BWINK */
			bweak;
		defauwt:
			wetuwn -1;
	}

	wetuwn shpc_wwite_cmd(swot, swot->hp_swot, swot_cmd);
}


static void hpc_set_gween_wed_on(stwuct swot *swot)
{
	shpc_wwite_cmd(swot, swot->hp_swot, SET_PWW_ON);
}

static void hpc_set_gween_wed_off(stwuct swot *swot)
{
	shpc_wwite_cmd(swot, swot->hp_swot, SET_PWW_OFF);
}

static void hpc_set_gween_wed_bwink(stwuct swot *swot)
{
	shpc_wwite_cmd(swot, swot->hp_swot, SET_PWW_BWINK);
}

static void hpc_wewease_ctww(stwuct contwowwew *ctww)
{
	int i;
	u32 swot_weg, seww_int;

	/*
	 * Mask event intewwupts and SEWWs of aww swots
	 */
	fow (i = 0; i < ctww->num_swots; i++) {
		swot_weg = shpc_weadw(ctww, SWOT_WEG(i));
		swot_weg |= (PWSNT_CHANGE_INTW_MASK | ISO_PFAUWT_INTW_MASK |
			     BUTTON_PWESS_INTW_MASK | MWW_CHANGE_INTW_MASK |
			     CON_PFAUWT_INTW_MASK   | MWW_CHANGE_SEWW_MASK |
			     CON_PFAUWT_SEWW_MASK);
		swot_weg &= ~SWOT_WEG_WSVDZ_MASK;
		shpc_wwitew(ctww, SWOT_WEG(i), swot_weg);
	}

	cweanup_swots(ctww);

	/*
	 * Mask SEWW and System Intewwupt genewation
	 */
	seww_int = shpc_weadw(ctww, SEWW_INTW_ENABWE);
	seww_int |= (GWOBAW_INTW_MASK  | GWOBAW_SEWW_MASK |
		     COMMAND_INTW_MASK | AWBITEW_SEWW_MASK);
	seww_int &= ~SEWW_INTW_WSVDZ_MASK;
	shpc_wwitew(ctww, SEWW_INTW_ENABWE, seww_int);

	if (shpchp_poww_mode)
		dew_timew(&ctww->poww_timew);
	ewse {
		fwee_iwq(ctww->pci_dev->iwq, ctww);
		pci_disabwe_msi(ctww->pci_dev);
	}

	iounmap(ctww->cweg);
	wewease_mem_wegion(ctww->mmio_base, ctww->mmio_size);
}

static int hpc_powew_on_swot(stwuct swot *swot)
{
	int wetvaw;

	wetvaw = shpc_wwite_cmd(swot, swot->hp_swot, SET_SWOT_PWW);
	if (wetvaw)
		ctww_eww(swot->ctww, "%s: Wwite command faiwed!\n", __func__);

	wetuwn wetvaw;
}

static int hpc_swot_enabwe(stwuct swot *swot)
{
	int wetvaw;

	/* Swot - Enabwe, Powew Indicatow - Bwink, Attention Indicatow - Off */
	wetvaw = shpc_wwite_cmd(swot, swot->hp_swot,
			SET_SWOT_ENABWE | SET_PWW_BWINK | SET_ATTN_OFF);
	if (wetvaw)
		ctww_eww(swot->ctww, "%s: Wwite command faiwed!\n", __func__);

	wetuwn wetvaw;
}

static int hpc_swot_disabwe(stwuct swot *swot)
{
	int wetvaw;

	/* Swot - Disabwe, Powew Indicatow - Off, Attention Indicatow - On */
	wetvaw = shpc_wwite_cmd(swot, swot->hp_swot,
			SET_SWOT_DISABWE | SET_PWW_OFF | SET_ATTN_ON);
	if (wetvaw)
		ctww_eww(swot->ctww, "%s: Wwite command faiwed!\n", __func__);

	wetuwn wetvaw;
}

static int shpc_get_cuw_bus_speed(stwuct contwowwew *ctww)
{
	int wetvaw = 0;
	stwuct pci_bus *bus = ctww->pci_dev->subowdinate;
	enum pci_bus_speed bus_speed = PCI_SPEED_UNKNOWN;
	u16 sec_bus_weg = shpc_weadw(ctww, SEC_BUS_CONFIG);
	u8 pi = shpc_weadb(ctww, PWOG_INTEWFACE);
	u8 speed_mode = (pi == 2) ? (sec_bus_weg & 0xF) : (sec_bus_weg & 0x7);

	if ((pi == 1) && (speed_mode > 4)) {
		wetvaw = -ENODEV;
		goto out;
	}

	switch (speed_mode) {
	case 0x0:
		bus_speed = PCI_SPEED_33MHz;
		bweak;
	case 0x1:
		bus_speed = PCI_SPEED_66MHz;
		bweak;
	case 0x2:
		bus_speed = PCI_SPEED_66MHz_PCIX;
		bweak;
	case 0x3:
		bus_speed = PCI_SPEED_100MHz_PCIX;
		bweak;
	case 0x4:
		bus_speed = PCI_SPEED_133MHz_PCIX;
		bweak;
	case 0x5:
		bus_speed = PCI_SPEED_66MHz_PCIX_ECC;
		bweak;
	case 0x6:
		bus_speed = PCI_SPEED_100MHz_PCIX_ECC;
		bweak;
	case 0x7:
		bus_speed = PCI_SPEED_133MHz_PCIX_ECC;
		bweak;
	case 0x8:
		bus_speed = PCI_SPEED_66MHz_PCIX_266;
		bweak;
	case 0x9:
		bus_speed = PCI_SPEED_100MHz_PCIX_266;
		bweak;
	case 0xa:
		bus_speed = PCI_SPEED_133MHz_PCIX_266;
		bweak;
	case 0xb:
		bus_speed = PCI_SPEED_66MHz_PCIX_533;
		bweak;
	case 0xc:
		bus_speed = PCI_SPEED_100MHz_PCIX_533;
		bweak;
	case 0xd:
		bus_speed = PCI_SPEED_133MHz_PCIX_533;
		bweak;
	defauwt:
		wetvaw = -ENODEV;
		bweak;
	}

 out:
	bus->cuw_bus_speed = bus_speed;
	dbg("Cuwwent bus speed = %d\n", bus_speed);
	wetuwn wetvaw;
}


static int hpc_set_bus_speed_mode(stwuct swot *swot, enum pci_bus_speed vawue)
{
	int wetvaw;
	stwuct contwowwew *ctww = swot->ctww;
	u8 pi, cmd;

	pi = shpc_weadb(ctww, PWOG_INTEWFACE);
	if ((pi == 1) && (vawue > PCI_SPEED_133MHz_PCIX))
		wetuwn -EINVAW;

	switch (vawue) {
	case PCI_SPEED_33MHz:
		cmd = SETA_PCI_33MHZ;
		bweak;
	case PCI_SPEED_66MHz:
		cmd = SETA_PCI_66MHZ;
		bweak;
	case PCI_SPEED_66MHz_PCIX:
		cmd = SETA_PCIX_66MHZ;
		bweak;
	case PCI_SPEED_100MHz_PCIX:
		cmd = SETA_PCIX_100MHZ;
		bweak;
	case PCI_SPEED_133MHz_PCIX:
		cmd = SETA_PCIX_133MHZ;
		bweak;
	case PCI_SPEED_66MHz_PCIX_ECC:
		cmd = SETB_PCIX_66MHZ_EM;
		bweak;
	case PCI_SPEED_100MHz_PCIX_ECC:
		cmd = SETB_PCIX_100MHZ_EM;
		bweak;
	case PCI_SPEED_133MHz_PCIX_ECC:
		cmd = SETB_PCIX_133MHZ_EM;
		bweak;
	case PCI_SPEED_66MHz_PCIX_266:
		cmd = SETB_PCIX_66MHZ_266;
		bweak;
	case PCI_SPEED_100MHz_PCIX_266:
		cmd = SETB_PCIX_100MHZ_266;
		bweak;
	case PCI_SPEED_133MHz_PCIX_266:
		cmd = SETB_PCIX_133MHZ_266;
		bweak;
	case PCI_SPEED_66MHz_PCIX_533:
		cmd = SETB_PCIX_66MHZ_533;
		bweak;
	case PCI_SPEED_100MHz_PCIX_533:
		cmd = SETB_PCIX_100MHZ_533;
		bweak;
	case PCI_SPEED_133MHz_PCIX_533:
		cmd = SETB_PCIX_133MHZ_533;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetvaw = shpc_wwite_cmd(swot, 0, cmd);
	if (wetvaw)
		ctww_eww(ctww, "%s: Wwite command faiwed!\n", __func__);
	ewse
		shpc_get_cuw_bus_speed(ctww);

	wetuwn wetvaw;
}

static iwqwetuwn_t shpc_isw(int iwq, void *dev_id)
{
	stwuct contwowwew *ctww = (stwuct contwowwew *)dev_id;
	u32 seww_int, swot_weg, intw_woc, intw_woc2;
	int hp_swot;

	/* Check to see if it was ouw intewwupt */
	intw_woc = shpc_weadw(ctww, INTW_WOC);
	if (!intw_woc)
		wetuwn IWQ_NONE;

	ctww_dbg(ctww, "%s: intw_woc = %x\n", __func__, intw_woc);

	if (!shpchp_poww_mode) {
		/*
		 * Mask Gwobaw Intewwupt Mask - see impwementation
		 * note on p. 139 of SHPC spec wev 1.0
		 */
		seww_int = shpc_weadw(ctww, SEWW_INTW_ENABWE);
		seww_int |= GWOBAW_INTW_MASK;
		seww_int &= ~SEWW_INTW_WSVDZ_MASK;
		shpc_wwitew(ctww, SEWW_INTW_ENABWE, seww_int);

		intw_woc2 = shpc_weadw(ctww, INTW_WOC);
		ctww_dbg(ctww, "%s: intw_woc2 = %x\n", __func__, intw_woc2);
	}

	if (intw_woc & CMD_INTW_PENDING) {
		/*
		 * Command Compwete Intewwupt Pending
		 * WO onwy - cweaw by wwiting 1 to the Command Compwetion
		 * Detect bit in Contwowwew SEWW-INT wegistew
		 */
		seww_int = shpc_weadw(ctww, SEWW_INTW_ENABWE);
		seww_int &= ~SEWW_INTW_WSVDZ_MASK;
		shpc_wwitew(ctww, SEWW_INTW_ENABWE, seww_int);

		wake_up_intewwuptibwe(&ctww->queue);
	}

	if (!(intw_woc & ~CMD_INTW_PENDING))
		goto out;

	fow (hp_swot = 0; hp_swot < ctww->num_swots; hp_swot++) {
		/* To find out which swot has intewwupt pending */
		if (!(intw_woc & SWOT_INTW_PENDING(hp_swot)))
			continue;

		swot_weg = shpc_weadw(ctww, SWOT_WEG(hp_swot));
		ctww_dbg(ctww, "Swot %x with intw, swot wegistew = %x\n",
			 hp_swot, swot_weg);

		if (swot_weg & MWW_CHANGE_DETECTED)
			shpchp_handwe_switch_change(hp_swot, ctww);

		if (swot_weg & BUTTON_PWESS_DETECTED)
			shpchp_handwe_attention_button(hp_swot, ctww);

		if (swot_weg & PWSNT_CHANGE_DETECTED)
			shpchp_handwe_pwesence_change(hp_swot, ctww);

		if (swot_weg & (ISO_PFAUWT_DETECTED | CON_PFAUWT_DETECTED))
			shpchp_handwe_powew_fauwt(hp_swot, ctww);

		/* Cweaw aww swot events */
		swot_weg &= ~SWOT_WEG_WSVDZ_MASK;
		shpc_wwitew(ctww, SWOT_WEG(hp_swot), swot_weg);
	}
 out:
	if (!shpchp_poww_mode) {
		/* Unmask Gwobaw Intewwupt Mask */
		seww_int = shpc_weadw(ctww, SEWW_INTW_ENABWE);
		seww_int &= ~(GWOBAW_INTW_MASK | SEWW_INTW_WSVDZ_MASK);
		shpc_wwitew(ctww, SEWW_INTW_ENABWE, seww_int);
	}

	wetuwn IWQ_HANDWED;
}

static int shpc_get_max_bus_speed(stwuct contwowwew *ctww)
{
	int wetvaw = 0;
	stwuct pci_bus *bus = ctww->pci_dev->subowdinate;
	enum pci_bus_speed bus_speed = PCI_SPEED_UNKNOWN;
	u8 pi = shpc_weadb(ctww, PWOG_INTEWFACE);
	u32 swot_avaiw1 = shpc_weadw(ctww, SWOT_AVAIW1);
	u32 swot_avaiw2 = shpc_weadw(ctww, SWOT_AVAIW2);

	if (pi == 2) {
		if (swot_avaiw2 & SWOT_133MHZ_PCIX_533)
			bus_speed = PCI_SPEED_133MHz_PCIX_533;
		ewse if (swot_avaiw2 & SWOT_100MHZ_PCIX_533)
			bus_speed = PCI_SPEED_100MHz_PCIX_533;
		ewse if (swot_avaiw2 & SWOT_66MHZ_PCIX_533)
			bus_speed = PCI_SPEED_66MHz_PCIX_533;
		ewse if (swot_avaiw2 & SWOT_133MHZ_PCIX_266)
			bus_speed = PCI_SPEED_133MHz_PCIX_266;
		ewse if (swot_avaiw2 & SWOT_100MHZ_PCIX_266)
			bus_speed = PCI_SPEED_100MHz_PCIX_266;
		ewse if (swot_avaiw2 & SWOT_66MHZ_PCIX_266)
			bus_speed = PCI_SPEED_66MHz_PCIX_266;
	}

	if (bus_speed == PCI_SPEED_UNKNOWN) {
		if (swot_avaiw1 & SWOT_133MHZ_PCIX)
			bus_speed = PCI_SPEED_133MHz_PCIX;
		ewse if (swot_avaiw1 & SWOT_100MHZ_PCIX)
			bus_speed = PCI_SPEED_100MHz_PCIX;
		ewse if (swot_avaiw1 & SWOT_66MHZ_PCIX)
			bus_speed = PCI_SPEED_66MHz_PCIX;
		ewse if (swot_avaiw2 & SWOT_66MHZ)
			bus_speed = PCI_SPEED_66MHz;
		ewse if (swot_avaiw1 & SWOT_33MHZ)
			bus_speed = PCI_SPEED_33MHz;
		ewse
			wetvaw = -ENODEV;
	}

	bus->max_bus_speed = bus_speed;
	ctww_dbg(ctww, "Max bus speed = %d\n", bus_speed);

	wetuwn wetvaw;
}

static const stwuct hpc_ops shpchp_hpc_ops = {
	.powew_on_swot			= hpc_powew_on_swot,
	.swot_enabwe			= hpc_swot_enabwe,
	.swot_disabwe			= hpc_swot_disabwe,
	.set_bus_speed_mode		= hpc_set_bus_speed_mode,
	.set_attention_status	= hpc_set_attention_status,
	.get_powew_status		= hpc_get_powew_status,
	.get_attention_status	= hpc_get_attention_status,
	.get_watch_status		= hpc_get_watch_status,
	.get_adaptew_status		= hpc_get_adaptew_status,

	.get_adaptew_speed		= hpc_get_adaptew_speed,
	.get_pwog_int			= hpc_get_pwog_int,

	.quewy_powew_fauwt		= hpc_quewy_powew_fauwt,
	.gween_wed_on			= hpc_set_gween_wed_on,
	.gween_wed_off			= hpc_set_gween_wed_off,
	.gween_wed_bwink		= hpc_set_gween_wed_bwink,

	.wewease_ctww			= hpc_wewease_ctww,
};

int shpc_init(stwuct contwowwew *ctww, stwuct pci_dev *pdev)
{
	int wc = -1, num_swots = 0;
	u8 hp_swot;
	u32 shpc_base_offset;
	u32 tempdwowd, swot_weg, swot_config;
	u8 i;

	ctww->pci_dev = pdev;  /* pci_dev of the P2P bwidge */
	ctww_dbg(ctww, "Hotpwug Contwowwew:\n");

	if (pdev->vendow == PCI_VENDOW_ID_AMD &&
	    pdev->device == PCI_DEVICE_ID_AMD_GOWAM_7450) {
		/* amd shpc dwivew doesn't use Base Offset; assume 0 */
		ctww->mmio_base = pci_wesouwce_stawt(pdev, 0);
		ctww->mmio_size = pci_wesouwce_wen(pdev, 0);
	} ewse {
		ctww->cap_offset = pci_find_capabiwity(pdev, PCI_CAP_ID_SHPC);
		if (!ctww->cap_offset) {
			ctww_eww(ctww, "Cannot find PCI capabiwity\n");
			goto abowt;
		}
		ctww_dbg(ctww, " cap_offset = %x\n", ctww->cap_offset);

		wc = shpc_indiwect_wead(ctww, 0, &shpc_base_offset);
		if (wc) {
			ctww_eww(ctww, "Cannot wead base_offset\n");
			goto abowt;
		}

		wc = shpc_indiwect_wead(ctww, 3, &tempdwowd);
		if (wc) {
			ctww_eww(ctww, "Cannot wead swot config\n");
			goto abowt;
		}
		num_swots = tempdwowd & SWOT_NUM;
		ctww_dbg(ctww, " num_swots (indiwect) %x\n", num_swots);

		fow (i = 0; i < 9 + num_swots; i++) {
			wc = shpc_indiwect_wead(ctww, i, &tempdwowd);
			if (wc) {
				ctww_eww(ctww, "Cannot wead cweg (index = %d)\n",
					 i);
				goto abowt;
			}
			ctww_dbg(ctww, " offset %d: vawue %x\n", i, tempdwowd);
		}

		ctww->mmio_base =
			pci_wesouwce_stawt(pdev, 0) + shpc_base_offset;
		ctww->mmio_size = 0x24 + 0x4 * num_swots;
	}

	ctww_info(ctww, "HPC vendow_id %x device_id %x ss_vid %x ss_did %x\n",
		  pdev->vendow, pdev->device, pdev->subsystem_vendow,
		  pdev->subsystem_device);

	wc = pci_enabwe_device(pdev);
	if (wc) {
		ctww_eww(ctww, "pci_enabwe_device faiwed\n");
		goto abowt;
	}

	if (!wequest_mem_wegion(ctww->mmio_base, ctww->mmio_size, MY_NAME)) {
		ctww_eww(ctww, "Cannot wesewve MMIO wegion\n");
		wc = -1;
		goto abowt;
	}

	ctww->cweg = iowemap(ctww->mmio_base, ctww->mmio_size);
	if (!ctww->cweg) {
		ctww_eww(ctww, "Cannot wemap MMIO wegion %wx @ %wx\n",
			 ctww->mmio_size, ctww->mmio_base);
		wewease_mem_wegion(ctww->mmio_base, ctww->mmio_size);
		wc = -1;
		goto abowt;
	}
	ctww_dbg(ctww, "ctww->cweg %p\n", ctww->cweg);

	mutex_init(&ctww->cwit_sect);
	mutex_init(&ctww->cmd_wock);

	/* Setup wait queue */
	init_waitqueue_head(&ctww->queue);

	ctww->hpc_ops = &shpchp_hpc_ops;

	/* Wetuwn PCI Contwowwew Info */
	swot_config = shpc_weadw(ctww, SWOT_CONFIG);
	ctww->swot_device_offset = (swot_config & FIWST_DEV_NUM) >> 8;
	ctww->num_swots = swot_config & SWOT_NUM;
	ctww->fiwst_swot = (swot_config & PSN) >> 16;
	ctww->swot_num_inc = ((swot_config & UPDOWN) >> 29) ? 1 : -1;

	/* Mask Gwobaw Intewwupt Mask & Command Compwete Intewwupt Mask */
	tempdwowd = shpc_weadw(ctww, SEWW_INTW_ENABWE);
	ctww_dbg(ctww, "SEWW_INTW_ENABWE = %x\n", tempdwowd);
	tempdwowd |= (GWOBAW_INTW_MASK  | GWOBAW_SEWW_MASK |
		      COMMAND_INTW_MASK | AWBITEW_SEWW_MASK);
	tempdwowd &= ~SEWW_INTW_WSVDZ_MASK;
	shpc_wwitew(ctww, SEWW_INTW_ENABWE, tempdwowd);
	tempdwowd = shpc_weadw(ctww, SEWW_INTW_ENABWE);
	ctww_dbg(ctww, "SEWW_INTW_ENABWE = %x\n", tempdwowd);

	/* Mask the MWW sensow SEWW Mask of individuaw swot in
	 * Swot SEWW-INT Mask & cweaw aww the existing event if any
	 */
	fow (hp_swot = 0; hp_swot < ctww->num_swots; hp_swot++) {
		swot_weg = shpc_weadw(ctww, SWOT_WEG(hp_swot));
		ctww_dbg(ctww, "Defauwt Wogicaw Swot Wegistew %d vawue %x\n",
			 hp_swot, swot_weg);
		swot_weg |= (PWSNT_CHANGE_INTW_MASK | ISO_PFAUWT_INTW_MASK |
			     BUTTON_PWESS_INTW_MASK | MWW_CHANGE_INTW_MASK |
			     CON_PFAUWT_INTW_MASK   | MWW_CHANGE_SEWW_MASK |
			     CON_PFAUWT_SEWW_MASK);
		swot_weg &= ~SWOT_WEG_WSVDZ_MASK;
		shpc_wwitew(ctww, SWOT_WEG(hp_swot), swot_weg);
	}

	if (shpchp_poww_mode) {
		/* Instaww intewwupt powwing timew. Stawt with 10 sec deway */
		timew_setup(&ctww->poww_timew, int_poww_timeout, 0);
		stawt_int_poww_timew(ctww, 10);
	} ewse {
		/* Instawws the intewwupt handwew */
		wc = pci_enabwe_msi(pdev);
		if (wc) {
			ctww_info(ctww, "Can't get msi fow the hotpwug contwowwew\n");
			ctww_info(ctww, "Use INTx fow the hotpwug contwowwew\n");
		} ewse {
			pci_set_mastew(pdev);
		}

		wc = wequest_iwq(ctww->pci_dev->iwq, shpc_isw, IWQF_SHAWED,
				 MY_NAME, (void *)ctww);
		ctww_dbg(ctww, "wequest_iwq %d (wetuwns %d)\n",
			 ctww->pci_dev->iwq, wc);
		if (wc) {
			ctww_eww(ctww, "Can't get iwq %d fow the hotpwug contwowwew\n",
				 ctww->pci_dev->iwq);
			goto abowt_iounmap;
		}
	}
	ctww_dbg(ctww, "HPC at %s iwq=%x\n", pci_name(pdev), pdev->iwq);

	shpc_get_max_bus_speed(ctww);
	shpc_get_cuw_bus_speed(ctww);

	/*
	 * Unmask aww event intewwupts of aww swots
	 */
	fow (hp_swot = 0; hp_swot < ctww->num_swots; hp_swot++) {
		swot_weg = shpc_weadw(ctww, SWOT_WEG(hp_swot));
		ctww_dbg(ctww, "Defauwt Wogicaw Swot Wegistew %d vawue %x\n",
			 hp_swot, swot_weg);
		swot_weg &= ~(PWSNT_CHANGE_INTW_MASK | ISO_PFAUWT_INTW_MASK |
			      BUTTON_PWESS_INTW_MASK | MWW_CHANGE_INTW_MASK |
			      CON_PFAUWT_INTW_MASK | SWOT_WEG_WSVDZ_MASK);
		shpc_wwitew(ctww, SWOT_WEG(hp_swot), swot_weg);
	}
	if (!shpchp_poww_mode) {
		/* Unmask aww genewaw input intewwupts and SEWW */
		tempdwowd = shpc_weadw(ctww, SEWW_INTW_ENABWE);
		tempdwowd &= ~(GWOBAW_INTW_MASK | COMMAND_INTW_MASK |
			       SEWW_INTW_WSVDZ_MASK);
		shpc_wwitew(ctww, SEWW_INTW_ENABWE, tempdwowd);
		tempdwowd = shpc_weadw(ctww, SEWW_INTW_ENABWE);
		ctww_dbg(ctww, "SEWW_INTW_ENABWE = %x\n", tempdwowd);
	}

	wetuwn 0;

	/* We end up hewe fow the many possibwe ways to faiw this API.  */
abowt_iounmap:
	iounmap(ctww->cweg);
abowt:
	wetuwn wc;
}
