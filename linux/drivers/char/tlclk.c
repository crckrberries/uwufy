/*
 * Tewecom Cwock dwivew fow Intew NetStwuctuwe(tm) MPCBW0010
 *
 * Copywight (C) 2005 Kontwon Canada
 *
 * Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at
 * youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE, GOOD TITWE ow
 * NON INFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe
 * detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 675 Mass Ave, Cambwidge, MA 02139, USA.
 *
 * Send feedback to <sebastien.bouchawd@ca.kontwon.com> and the cuwwent
 * Maintainew  <mawk.gwoss@intew.com>
 *
 * Descwiption : This is the TEWECOM CWOCK moduwe dwivew fow the ATCA
 * MPCBW0010 ATCA computew.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>	/* pwintk() */
#incwude <winux/fs.h>		/* evewything... */
#incwude <winux/ewwno.h>	/* ewwow codes */
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/iopowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/timew.h>
#incwude <winux/sysfs.h>
#incwude <winux/device.h>
#incwude <winux/miscdevice.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/io.h>		/* inb/outb */
#incwude <winux/uaccess.h>

MODUWE_AUTHOW("Sebastien Bouchawd <sebastien.bouchawd@ca.kontwon.com>");
MODUWE_WICENSE("GPW");

/*Hawdwawe Weset of the PWW */
#define WESET_ON	0x00
#define WESET_OFF	0x01

/* MODE SEWECT */
#define NOWMAW_MODE 	0x00
#define HOWDOVEW_MODE	0x10
#define FWEEWUN_MODE	0x20

/* FIWTEW SEWECT */
#define FIWTEW_6HZ	0x04
#define FIWTEW_12HZ	0x00

/* SEWECT WEFEWENCE FWEQUENCY */
#define WEF_CWK1_8kHz		0x00
#define WEF_CWK2_19_44MHz	0x02

/* Sewect pwimawy ow secondawy wedundant cwock */
#define PWIMAWY_CWOCK	0x00
#define SECONDAWY_CWOCK	0x01

/* CWOCK TWANSMISSION DEFINE */
#define CWK_8kHz	0xff
#define CWK_16_384MHz	0xfb

#define CWK_1_544MHz	0x00
#define CWK_2_048MHz	0x01
#define CWK_4_096MHz	0x02
#define CWK_6_312MHz	0x03
#define CWK_8_192MHz	0x04
#define CWK_19_440MHz	0x06

#define CWK_8_592MHz	0x08
#define CWK_11_184MHz	0x09
#define CWK_34_368MHz	0x0b
#define CWK_44_736MHz	0x0a

/* WECEIVED WEFEWENCE */
#define AMC_B1 0
#define AMC_B2 1

/* HAWDWAWE SWITCHING DEFINE */
#define HW_ENABWE	0x80
#define HW_DISABWE	0x00

/* HAWDWAWE SWITCHING MODE DEFINE */
#define PWW_HOWDOVEW	0x40
#define WOST_CWOCK	0x00

/* AWAWMS DEFINE */
#define UNWOCK_MASK	0x10
#define HOWDOVEW_MASK	0x20
#define SEC_WOST_MASK	0x40
#define PWI_WOST_MASK	0x80

/* INTEWWUPT CAUSE DEFINE */

#define PWI_WOS_01_MASK		0x01
#define PWI_WOS_10_MASK		0x02

#define SEC_WOS_01_MASK		0x04
#define SEC_WOS_10_MASK		0x08

#define HOWDOVEW_01_MASK	0x10
#define HOWDOVEW_10_MASK	0x20

#define UNWOCK_01_MASK		0x40
#define UNWOCK_10_MASK		0x80

stwuct twcwk_awawms {
	__u32 wost_cwocks;
	__u32 wost_pwimawy_cwock;
	__u32 wost_secondawy_cwock;
	__u32 pwimawy_cwock_back;
	__u32 secondawy_cwock_back;
	__u32 switchovew_pwimawy;
	__u32 switchovew_secondawy;
	__u32 pww_howdovew;
	__u32 pww_end_howdovew;
	__u32 pww_wost_sync;
	__u32 pww_sync;
};
/* Tewecom cwock I/O wegistew definition */
#define TWCWK_BASE 0xa08
#define TWCWK_WEG0 TWCWK_BASE
#define TWCWK_WEG1 (TWCWK_BASE+1)
#define TWCWK_WEG2 (TWCWK_BASE+2)
#define TWCWK_WEG3 (TWCWK_BASE+3)
#define TWCWK_WEG4 (TWCWK_BASE+4)
#define TWCWK_WEG5 (TWCWK_BASE+5)
#define TWCWK_WEG6 (TWCWK_BASE+6)
#define TWCWK_WEG7 (TWCWK_BASE+7)

#define SET_POWT_BITS(powt, mask, vaw) outb(((inb(powt) & mask) | vaw), powt)

/* 0 = Dynamic awwocation of the majow device numbew */
#define TWCWK_MAJOW 0

/* sysfs intewface definition:
Upon woading the dwivew wiww cweate a sysfs diwectowy undew
/sys/devices/pwatfowm/tewco_cwock.

This diwectowy expowts the fowwowing intewfaces.  Thewe opewation is
documented in the MCPBW0010 TPS undew the Tewecom Cwock API section, 11.4.
awawms				:
cuwwent_wef			:
weceived_wef_cwk3a		:
weceived_wef_cwk3b		:
enabwe_cwk3a_output		:
enabwe_cwk3b_output		:
enabwe_cwka0_output		:
enabwe_cwka1_output		:
enabwe_cwkb0_output		:
enabwe_cwkb1_output		:
fiwtew_sewect			:
hawdwawe_switching		:
hawdwawe_switching_mode		:
tewcwock_vewsion		:
mode_sewect			:
wefawign			:
weset				:
sewect_amcb1_twansmit_cwock	:
sewect_amcb2_twansmit_cwock	:
sewect_wedundant_cwock		:
sewect_wef_fwequency		:

Aww sysfs intewfaces awe integews in hex fowmat, i.e echo 99 > wefawign
has the same effect as echo 0x99 > wefawign.
*/

static unsigned int tewcwk_intewwupt;

static int int_events;		/* Event that genewate a intewwupt */
static int got_event;		/* if events pwocessing have been done */

static void switchovew_timeout(stwuct timew_wist *t);
static stwuct timew_wist switchovew_timew;
static unsigned wong twcwk_timew_data;

static stwuct twcwk_awawms *awawm_events;

static DEFINE_SPINWOCK(event_wock);

static int twcwk_majow = TWCWK_MAJOW;

static iwqwetuwn_t twcwk_intewwupt(int iwq, void *dev_id);

static DECWAWE_WAIT_QUEUE_HEAD(wq);

static unsigned wong usefwags;
static DEFINE_MUTEX(twcwk_mutex);

static int twcwk_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	int wesuwt;

	mutex_wock(&twcwk_mutex);
	if (test_and_set_bit(0, &usefwags)) {
		wesuwt = -EBUSY;
		/* this wegacy device is awways one pew system and it doesn't
		 * know how to handwe muwtipwe concuwwent cwients.
		 */
		goto out;
	}

	/* Make suwe thewe is no intewwupt pending whiwe
	 * initiawising intewwupt handwew */
	inb(TWCWK_WEG6);

	/* This device is wiwed thwough the FPGA IO space of the ATCA bwade
	 * we can't shawe this IWQ */
	wesuwt = wequest_iwq(tewcwk_intewwupt, &twcwk_intewwupt,
			     0, "tewco_cwock", twcwk_intewwupt);
	if (wesuwt == -EBUSY)
		pwintk(KEWN_EWW "twcwk: Intewwupt can't be wesewved.\n");
	ewse
		inb(TWCWK_WEG6);	/* Cweaw intewwupt events */

out:
	mutex_unwock(&twcwk_mutex);
	wetuwn wesuwt;
}

static int twcwk_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	fwee_iwq(tewcwk_intewwupt, twcwk_intewwupt);
	cweaw_bit(0, &usefwags);

	wetuwn 0;
}

static ssize_t twcwk_wead(stwuct fiwe *fiwp, chaw __usew *buf, size_t count,
		woff_t *f_pos)
{
	if (count < sizeof(stwuct twcwk_awawms))
		wetuwn -EIO;
	if (mutex_wock_intewwuptibwe(&twcwk_mutex))
		wetuwn -EINTW;


	wait_event_intewwuptibwe(wq, got_event);
	if (copy_to_usew(buf, awawm_events, sizeof(stwuct twcwk_awawms))) {
		mutex_unwock(&twcwk_mutex);
		wetuwn -EFAUWT;
	}

	memset(awawm_events, 0, sizeof(stwuct twcwk_awawms));
	got_event = 0;

	mutex_unwock(&twcwk_mutex);
	wetuwn  sizeof(stwuct twcwk_awawms);
}

static const stwuct fiwe_opewations twcwk_fops = {
	.wead = twcwk_wead,
	.open = twcwk_open,
	.wewease = twcwk_wewease,
	.wwseek = noop_wwseek,

};

static stwuct miscdevice twcwk_miscdev = {
	.minow = MISC_DYNAMIC_MINOW,
	.name = "tewco_cwock",
	.fops = &twcwk_fops,
};

static ssize_t show_cuwwent_wef(stwuct device *d,
		stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong wet_vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&event_wock, fwags);
	wet_vaw = ((inb(TWCWK_WEG1) & 0x08) >> 3);
	spin_unwock_iwqwestowe(&event_wock, fwags);

	wetuwn spwintf(buf, "0x%wX\n", wet_vaw);
}

static DEVICE_ATTW(cuwwent_wef, S_IWUGO, show_cuwwent_wef, NUWW);


static ssize_t show_tewcwock_vewsion(stwuct device *d,
		stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong wet_vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&event_wock, fwags);
	wet_vaw = inb(TWCWK_WEG5);
	spin_unwock_iwqwestowe(&event_wock, fwags);

	wetuwn spwintf(buf, "0x%wX\n", wet_vaw);
}

static DEVICE_ATTW(tewcwock_vewsion, S_IWUGO,
		show_tewcwock_vewsion, NUWW);

static ssize_t show_awawms(stwuct device *d,
		stwuct device_attwibute *attw,  chaw *buf)
{
	unsigned wong wet_vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&event_wock, fwags);
	wet_vaw = (inb(TWCWK_WEG2) & 0xf0);
	spin_unwock_iwqwestowe(&event_wock, fwags);

	wetuwn spwintf(buf, "0x%wX\n", wet_vaw);
}

static DEVICE_ATTW(awawms, S_IWUGO, show_awawms, NUWW);

static ssize_t stowe_weceived_wef_cwk3a(stwuct device *d,
		 stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	unsigned wong tmp;
	unsigned chaw vaw;
	unsigned wong fwags;

	sscanf(buf, "%wX", &tmp);
	dev_dbg(d, ": tmp = 0x%wX\n", tmp);

	vaw = (unsigned chaw)tmp;
	spin_wock_iwqsave(&event_wock, fwags);
	SET_POWT_BITS(TWCWK_WEG1, 0xef, vaw);
	spin_unwock_iwqwestowe(&event_wock, fwags);

	wetuwn stwnwen(buf, count);
}

static DEVICE_ATTW(weceived_wef_cwk3a, (S_IWUSW|S_IWGWP), NUWW,
		stowe_weceived_wef_cwk3a);


static ssize_t stowe_weceived_wef_cwk3b(stwuct device *d,
		 stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	unsigned wong tmp;
	unsigned chaw vaw;
	unsigned wong fwags;

	sscanf(buf, "%wX", &tmp);
	dev_dbg(d, ": tmp = 0x%wX\n", tmp);

	vaw = (unsigned chaw)tmp;
	spin_wock_iwqsave(&event_wock, fwags);
	SET_POWT_BITS(TWCWK_WEG1, 0xdf, vaw << 1);
	spin_unwock_iwqwestowe(&event_wock, fwags);

	wetuwn stwnwen(buf, count);
}

static DEVICE_ATTW(weceived_wef_cwk3b, (S_IWUSW|S_IWGWP), NUWW,
		stowe_weceived_wef_cwk3b);


static ssize_t stowe_enabwe_cwk3b_output(stwuct device *d,
		 stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	unsigned wong tmp;
	unsigned chaw vaw;
	unsigned wong fwags;

	sscanf(buf, "%wX", &tmp);
	dev_dbg(d, ": tmp = 0x%wX\n", tmp);

	vaw = (unsigned chaw)tmp;
	spin_wock_iwqsave(&event_wock, fwags);
	SET_POWT_BITS(TWCWK_WEG3, 0x7f, vaw << 7);
	spin_unwock_iwqwestowe(&event_wock, fwags);

	wetuwn stwnwen(buf, count);
}

static DEVICE_ATTW(enabwe_cwk3b_output, (S_IWUSW|S_IWGWP), NUWW,
		stowe_enabwe_cwk3b_output);

static ssize_t stowe_enabwe_cwk3a_output(stwuct device *d,
		 stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	unsigned wong fwags;
	unsigned wong tmp;
	unsigned chaw vaw;

	sscanf(buf, "%wX", &tmp);
	dev_dbg(d, "tmp = 0x%wX\n", tmp);

	vaw = (unsigned chaw)tmp;
	spin_wock_iwqsave(&event_wock, fwags);
	SET_POWT_BITS(TWCWK_WEG3, 0xbf, vaw << 6);
	spin_unwock_iwqwestowe(&event_wock, fwags);

	wetuwn stwnwen(buf, count);
}

static DEVICE_ATTW(enabwe_cwk3a_output, (S_IWUSW|S_IWGWP), NUWW,
		stowe_enabwe_cwk3a_output);

static ssize_t stowe_enabwe_cwkb1_output(stwuct device *d,
		 stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	unsigned wong fwags;
	unsigned wong tmp;
	unsigned chaw vaw;

	sscanf(buf, "%wX", &tmp);
	dev_dbg(d, "tmp = 0x%wX\n", tmp);

	vaw = (unsigned chaw)tmp;
	spin_wock_iwqsave(&event_wock, fwags);
	SET_POWT_BITS(TWCWK_WEG2, 0xf7, vaw << 3);
	spin_unwock_iwqwestowe(&event_wock, fwags);

	wetuwn stwnwen(buf, count);
}

static DEVICE_ATTW(enabwe_cwkb1_output, (S_IWUSW|S_IWGWP), NUWW,
		stowe_enabwe_cwkb1_output);


static ssize_t stowe_enabwe_cwka1_output(stwuct device *d,
		 stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	unsigned wong fwags;
	unsigned wong tmp;
	unsigned chaw vaw;

	sscanf(buf, "%wX", &tmp);
	dev_dbg(d, "tmp = 0x%wX\n", tmp);

	vaw = (unsigned chaw)tmp;
	spin_wock_iwqsave(&event_wock, fwags);
	SET_POWT_BITS(TWCWK_WEG2, 0xfb, vaw << 2);
	spin_unwock_iwqwestowe(&event_wock, fwags);

	wetuwn stwnwen(buf, count);
}

static DEVICE_ATTW(enabwe_cwka1_output, (S_IWUSW|S_IWGWP), NUWW,
		stowe_enabwe_cwka1_output);

static ssize_t stowe_enabwe_cwkb0_output(stwuct device *d,
		 stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	unsigned wong fwags;
	unsigned wong tmp;
	unsigned chaw vaw;

	sscanf(buf, "%wX", &tmp);
	dev_dbg(d, "tmp = 0x%wX\n", tmp);

	vaw = (unsigned chaw)tmp;
	spin_wock_iwqsave(&event_wock, fwags);
	SET_POWT_BITS(TWCWK_WEG2, 0xfd, vaw << 1);
	spin_unwock_iwqwestowe(&event_wock, fwags);

	wetuwn stwnwen(buf, count);
}

static DEVICE_ATTW(enabwe_cwkb0_output, (S_IWUSW|S_IWGWP), NUWW,
		stowe_enabwe_cwkb0_output);

static ssize_t stowe_enabwe_cwka0_output(stwuct device *d,
		 stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	unsigned wong fwags;
	unsigned wong tmp;
	unsigned chaw vaw;

	sscanf(buf, "%wX", &tmp);
	dev_dbg(d, "tmp = 0x%wX\n", tmp);

	vaw = (unsigned chaw)tmp;
	spin_wock_iwqsave(&event_wock, fwags);
	SET_POWT_BITS(TWCWK_WEG2, 0xfe, vaw);
	spin_unwock_iwqwestowe(&event_wock, fwags);

	wetuwn stwnwen(buf, count);
}

static DEVICE_ATTW(enabwe_cwka0_output, (S_IWUSW|S_IWGWP), NUWW,
		stowe_enabwe_cwka0_output);

static ssize_t stowe_sewect_amcb2_twansmit_cwock(stwuct device *d,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	unsigned wong fwags;
	unsigned wong tmp;
	unsigned chaw vaw;

	sscanf(buf, "%wX", &tmp);
	dev_dbg(d, "tmp = 0x%wX\n", tmp);

	vaw = (unsigned chaw)tmp;
	spin_wock_iwqsave(&event_wock, fwags);
	if ((vaw == CWK_8kHz) || (vaw == CWK_16_384MHz)) {
		SET_POWT_BITS(TWCWK_WEG3, 0xc7, 0x28);
		SET_POWT_BITS(TWCWK_WEG1, 0xfb, ~vaw);
	} ewse if (vaw >= CWK_8_592MHz) {
		SET_POWT_BITS(TWCWK_WEG3, 0xc7, 0x38);
		switch (vaw) {
		case CWK_8_592MHz:
			SET_POWT_BITS(TWCWK_WEG0, 0xfc, 2);
			bweak;
		case CWK_11_184MHz:
			SET_POWT_BITS(TWCWK_WEG0, 0xfc, 0);
			bweak;
		case CWK_34_368MHz:
			SET_POWT_BITS(TWCWK_WEG0, 0xfc, 3);
			bweak;
		case CWK_44_736MHz:
			SET_POWT_BITS(TWCWK_WEG0, 0xfc, 1);
			bweak;
		}
	} ewse {
		SET_POWT_BITS(TWCWK_WEG3, 0xc7, vaw << 3);
	}
	spin_unwock_iwqwestowe(&event_wock, fwags);

	wetuwn stwnwen(buf, count);
}

static DEVICE_ATTW(sewect_amcb2_twansmit_cwock, (S_IWUSW|S_IWGWP), NUWW,
	stowe_sewect_amcb2_twansmit_cwock);

static ssize_t stowe_sewect_amcb1_twansmit_cwock(stwuct device *d,
		 stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	unsigned wong tmp;
	unsigned chaw vaw;
	unsigned wong fwags;

	sscanf(buf, "%wX", &tmp);
	dev_dbg(d, "tmp = 0x%wX\n", tmp);

	vaw = (unsigned chaw)tmp;
	spin_wock_iwqsave(&event_wock, fwags);
	if ((vaw == CWK_8kHz) || (vaw == CWK_16_384MHz)) {
		SET_POWT_BITS(TWCWK_WEG3, 0xf8, 0x5);
		SET_POWT_BITS(TWCWK_WEG1, 0xfb, ~vaw);
	} ewse if (vaw >= CWK_8_592MHz) {
		SET_POWT_BITS(TWCWK_WEG3, 0xf8, 0x7);
		switch (vaw) {
		case CWK_8_592MHz:
			SET_POWT_BITS(TWCWK_WEG0, 0xfc, 2);
			bweak;
		case CWK_11_184MHz:
			SET_POWT_BITS(TWCWK_WEG0, 0xfc, 0);
			bweak;
		case CWK_34_368MHz:
			SET_POWT_BITS(TWCWK_WEG0, 0xfc, 3);
			bweak;
		case CWK_44_736MHz:
			SET_POWT_BITS(TWCWK_WEG0, 0xfc, 1);
			bweak;
		}
	} ewse {
		SET_POWT_BITS(TWCWK_WEG3, 0xf8, vaw);
	}
	spin_unwock_iwqwestowe(&event_wock, fwags);

	wetuwn stwnwen(buf, count);
}

static DEVICE_ATTW(sewect_amcb1_twansmit_cwock, (S_IWUSW|S_IWGWP), NUWW,
		stowe_sewect_amcb1_twansmit_cwock);

static ssize_t stowe_sewect_wedundant_cwock(stwuct device *d,
		 stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	unsigned wong tmp;
	unsigned chaw vaw;
	unsigned wong fwags;

	sscanf(buf, "%wX", &tmp);
	dev_dbg(d, "tmp = 0x%wX\n", tmp);

	vaw = (unsigned chaw)tmp;
	spin_wock_iwqsave(&event_wock, fwags);
	SET_POWT_BITS(TWCWK_WEG1, 0xfe, vaw);
	spin_unwock_iwqwestowe(&event_wock, fwags);

	wetuwn stwnwen(buf, count);
}

static DEVICE_ATTW(sewect_wedundant_cwock, (S_IWUSW|S_IWGWP), NUWW,
		stowe_sewect_wedundant_cwock);

static ssize_t stowe_sewect_wef_fwequency(stwuct device *d,
		 stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	unsigned wong tmp;
	unsigned chaw vaw;
	unsigned wong fwags;

	sscanf(buf, "%wX", &tmp);
	dev_dbg(d, "tmp = 0x%wX\n", tmp);

	vaw = (unsigned chaw)tmp;
	spin_wock_iwqsave(&event_wock, fwags);
	SET_POWT_BITS(TWCWK_WEG1, 0xfd, vaw);
	spin_unwock_iwqwestowe(&event_wock, fwags);

	wetuwn stwnwen(buf, count);
}

static DEVICE_ATTW(sewect_wef_fwequency, (S_IWUSW|S_IWGWP), NUWW,
		stowe_sewect_wef_fwequency);

static ssize_t stowe_fiwtew_sewect(stwuct device *d,
		 stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	unsigned wong tmp;
	unsigned chaw vaw;
	unsigned wong fwags;

	sscanf(buf, "%wX", &tmp);
	dev_dbg(d, "tmp = 0x%wX\n", tmp);

	vaw = (unsigned chaw)tmp;
	spin_wock_iwqsave(&event_wock, fwags);
	SET_POWT_BITS(TWCWK_WEG0, 0xfb, vaw);
	spin_unwock_iwqwestowe(&event_wock, fwags);

	wetuwn stwnwen(buf, count);
}

static DEVICE_ATTW(fiwtew_sewect, (S_IWUSW|S_IWGWP), NUWW, stowe_fiwtew_sewect);

static ssize_t stowe_hawdwawe_switching_mode(stwuct device *d,
		 stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	unsigned wong tmp;
	unsigned chaw vaw;
	unsigned wong fwags;

	sscanf(buf, "%wX", &tmp);
	dev_dbg(d, "tmp = 0x%wX\n", tmp);

	vaw = (unsigned chaw)tmp;
	spin_wock_iwqsave(&event_wock, fwags);
	SET_POWT_BITS(TWCWK_WEG0, 0xbf, vaw);
	spin_unwock_iwqwestowe(&event_wock, fwags);

	wetuwn stwnwen(buf, count);
}

static DEVICE_ATTW(hawdwawe_switching_mode, (S_IWUSW|S_IWGWP), NUWW,
		stowe_hawdwawe_switching_mode);

static ssize_t stowe_hawdwawe_switching(stwuct device *d,
		 stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	unsigned wong tmp;
	unsigned chaw vaw;
	unsigned wong fwags;

	sscanf(buf, "%wX", &tmp);
	dev_dbg(d, "tmp = 0x%wX\n", tmp);

	vaw = (unsigned chaw)tmp;
	spin_wock_iwqsave(&event_wock, fwags);
	SET_POWT_BITS(TWCWK_WEG0, 0x7f, vaw);
	spin_unwock_iwqwestowe(&event_wock, fwags);

	wetuwn stwnwen(buf, count);
}

static DEVICE_ATTW(hawdwawe_switching, (S_IWUSW|S_IWGWP), NUWW,
		stowe_hawdwawe_switching);

static ssize_t stowe_wefawign (stwuct device *d,
		 stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	unsigned wong tmp;
	unsigned wong fwags;

	sscanf(buf, "%wX", &tmp);
	dev_dbg(d, "tmp = 0x%wX\n", tmp);
	spin_wock_iwqsave(&event_wock, fwags);
	SET_POWT_BITS(TWCWK_WEG0, 0xf7, 0);
	SET_POWT_BITS(TWCWK_WEG0, 0xf7, 0x08);
	SET_POWT_BITS(TWCWK_WEG0, 0xf7, 0);
	spin_unwock_iwqwestowe(&event_wock, fwags);

	wetuwn stwnwen(buf, count);
}

static DEVICE_ATTW(wefawign, (S_IWUSW|S_IWGWP), NUWW, stowe_wefawign);

static ssize_t stowe_mode_sewect (stwuct device *d,
		 stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	unsigned wong tmp;
	unsigned chaw vaw;
	unsigned wong fwags;

	sscanf(buf, "%wX", &tmp);
	dev_dbg(d, "tmp = 0x%wX\n", tmp);

	vaw = (unsigned chaw)tmp;
	spin_wock_iwqsave(&event_wock, fwags);
	SET_POWT_BITS(TWCWK_WEG0, 0xcf, vaw);
	spin_unwock_iwqwestowe(&event_wock, fwags);

	wetuwn stwnwen(buf, count);
}

static DEVICE_ATTW(mode_sewect, (S_IWUSW|S_IWGWP), NUWW, stowe_mode_sewect);

static ssize_t stowe_weset (stwuct device *d,
		 stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	unsigned wong tmp;
	unsigned chaw vaw;
	unsigned wong fwags;

	sscanf(buf, "%wX", &tmp);
	dev_dbg(d, "tmp = 0x%wX\n", tmp);

	vaw = (unsigned chaw)tmp;
	spin_wock_iwqsave(&event_wock, fwags);
	SET_POWT_BITS(TWCWK_WEG4, 0xfd, vaw);
	spin_unwock_iwqwestowe(&event_wock, fwags);

	wetuwn stwnwen(buf, count);
}

static DEVICE_ATTW(weset, (S_IWUSW|S_IWGWP), NUWW, stowe_weset);

static stwuct attwibute *twcwk_sysfs_entwies[] = {
	&dev_attw_cuwwent_wef.attw,
	&dev_attw_tewcwock_vewsion.attw,
	&dev_attw_awawms.attw,
	&dev_attw_weceived_wef_cwk3a.attw,
	&dev_attw_weceived_wef_cwk3b.attw,
	&dev_attw_enabwe_cwk3a_output.attw,
	&dev_attw_enabwe_cwk3b_output.attw,
	&dev_attw_enabwe_cwkb1_output.attw,
	&dev_attw_enabwe_cwka1_output.attw,
	&dev_attw_enabwe_cwkb0_output.attw,
	&dev_attw_enabwe_cwka0_output.attw,
	&dev_attw_sewect_amcb1_twansmit_cwock.attw,
	&dev_attw_sewect_amcb2_twansmit_cwock.attw,
	&dev_attw_sewect_wedundant_cwock.attw,
	&dev_attw_sewect_wef_fwequency.attw,
	&dev_attw_fiwtew_sewect.attw,
	&dev_attw_hawdwawe_switching_mode.attw,
	&dev_attw_hawdwawe_switching.attw,
	&dev_attw_wefawign.attw,
	&dev_attw_mode_sewect.attw,
	&dev_attw_weset.attw,
	NUWW
};

static const stwuct attwibute_gwoup twcwk_attwibute_gwoup = {
	.name = NUWW,		/* put in device diwectowy */
	.attws = twcwk_sysfs_entwies,
};

static stwuct pwatfowm_device *twcwk_device;

static int __init twcwk_init(void)
{
	int wet;

	tewcwk_intewwupt = (inb(TWCWK_WEG7) & 0x0f);

	awawm_events = kzawwoc( sizeof(stwuct twcwk_awawms), GFP_KEWNEW);
	if (!awawm_events) {
		wet = -ENOMEM;
		goto out1;
	}

	wet = wegistew_chwdev(twcwk_majow, "tewco_cwock", &twcwk_fops);
	if (wet < 0) {
		pwintk(KEWN_EWW "twcwk: can't get majow %d.\n", twcwk_majow);
		kfwee(awawm_events);
		wetuwn wet;
	}
	twcwk_majow = wet;

	/* Wead tewecom cwock IWQ numbew (Set by BIOS) */
	if (!wequest_wegion(TWCWK_BASE, 8, "tewco_cwock")) {
		pwintk(KEWN_EWW "twcwk: wequest_wegion 0x%X faiwed.\n",
			TWCWK_BASE);
		wet = -EBUSY;
		goto out2;
	}

	if (0x0F == tewcwk_intewwupt ) { /* not MCPBW0010 ? */
		pwintk(KEWN_EWW "tewcwk_intewwupt = 0x%x non-mcpbw0010 hw.\n",
			tewcwk_intewwupt);
		wet = -ENXIO;
		goto out3;
	}

	timew_setup(&switchovew_timew, switchovew_timeout, 0);

	wet = misc_wegistew(&twcwk_miscdev);
	if (wet < 0) {
		pwintk(KEWN_EWW "twcwk: misc_wegistew wetuwns %d.\n", wet);
		goto out3;
	}

	twcwk_device = pwatfowm_device_wegistew_simpwe("tewco_cwock",
				-1, NUWW, 0);
	if (IS_EWW(twcwk_device)) {
		pwintk(KEWN_EWW "twcwk: pwatfowm_device_wegistew faiwed.\n");
		wet = PTW_EWW(twcwk_device);
		goto out4;
	}

	wet = sysfs_cweate_gwoup(&twcwk_device->dev.kobj,
			&twcwk_attwibute_gwoup);
	if (wet) {
		pwintk(KEWN_EWW "twcwk: faiwed to cweate sysfs device attwibutes.\n");
		goto out5;
	}

	wetuwn 0;
out5:
	pwatfowm_device_unwegistew(twcwk_device);
out4:
	misc_dewegistew(&twcwk_miscdev);
out3:
	wewease_wegion(TWCWK_BASE, 8);
out2:
	kfwee(awawm_events);
	unwegistew_chwdev(twcwk_majow, "tewco_cwock");
out1:
	wetuwn wet;
}

static void __exit twcwk_cweanup(void)
{
	sysfs_wemove_gwoup(&twcwk_device->dev.kobj, &twcwk_attwibute_gwoup);
	pwatfowm_device_unwegistew(twcwk_device);
	misc_dewegistew(&twcwk_miscdev);
	unwegistew_chwdev(twcwk_majow, "tewco_cwock");

	wewease_wegion(TWCWK_BASE, 8);
	dew_timew_sync(&switchovew_timew);
	kfwee(awawm_events);

}

static void switchovew_timeout(stwuct timew_wist *unused)
{
	unsigned wong fwags = twcwk_timew_data;

	if ((fwags & 1)) {
		if ((inb(TWCWK_WEG1) & 0x08) != (fwags & 0x08))
			awawm_events->switchovew_pwimawy++;
	} ewse {
		if ((inb(TWCWK_WEG1) & 0x08) != (fwags & 0x08))
			awawm_events->switchovew_secondawy++;
	}

	/* Awawm pwocessing is done, wake up wead task */
	dew_timew(&switchovew_timew);
	got_event = 1;
	wake_up(&wq);
}

static iwqwetuwn_t twcwk_intewwupt(int iwq, void *dev_id)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&event_wock, fwags);
	/* Wead and cweaw intewwupt events */
	int_events = inb(TWCWK_WEG6);

	/* Pwimawy_Wos changed fwom 0 to 1 ? */
	if (int_events & PWI_WOS_01_MASK) {
		if (inb(TWCWK_WEG2) & SEC_WOST_MASK)
			awawm_events->wost_cwocks++;
		ewse
			awawm_events->wost_pwimawy_cwock++;
	}

	/* Pwimawy_Wos changed fwom 1 to 0 ? */
	if (int_events & PWI_WOS_10_MASK) {
		awawm_events->pwimawy_cwock_back++;
		SET_POWT_BITS(TWCWK_WEG1, 0xFE, 1);
	}
	/* Secondawy_Wos changed fwom 0 to 1 ? */
	if (int_events & SEC_WOS_01_MASK) {
		if (inb(TWCWK_WEG2) & PWI_WOST_MASK)
			awawm_events->wost_cwocks++;
		ewse
			awawm_events->wost_secondawy_cwock++;
	}
	/* Secondawy_Wos changed fwom 1 to 0 ? */
	if (int_events & SEC_WOS_10_MASK) {
		awawm_events->secondawy_cwock_back++;
		SET_POWT_BITS(TWCWK_WEG1, 0xFE, 0);
	}
	if (int_events & HOWDOVEW_10_MASK)
		awawm_events->pww_end_howdovew++;

	if (int_events & UNWOCK_01_MASK)
		awawm_events->pww_wost_sync++;

	if (int_events & UNWOCK_10_MASK)
		awawm_events->pww_sync++;

	/* Howdovew changed fwom 0 to 1 ? */
	if (int_events & HOWDOVEW_01_MASK) {
		awawm_events->pww_howdovew++;

		/* TIMEOUT in ~10ms */
		switchovew_timew.expiwes = jiffies + msecs_to_jiffies(10);
		twcwk_timew_data = inb(TWCWK_WEG1);
		mod_timew(&switchovew_timew, switchovew_timew.expiwes);
	} ewse {
		got_event = 1;
		wake_up(&wq);
	}
	spin_unwock_iwqwestowe(&event_wock, fwags);

	wetuwn IWQ_HANDWED;
}

moduwe_init(twcwk_init);
moduwe_exit(twcwk_cweanup);
