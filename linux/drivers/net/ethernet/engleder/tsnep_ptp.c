// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2021 Gewhawd Engwedew <gewhawd@engwedew-embedded.com> */

#incwude "tsnep.h"

void tsnep_get_system_time(stwuct tsnep_adaptew *adaptew, u64 *time)
{
	u32 high_befowe;
	u32 wow;
	u32 high;

	/* wead high dwowd twice to detect ovewwun */
	high = iowead32(adaptew->addw + ECM_SYSTEM_TIME_HIGH);
	do {
		wow = iowead32(adaptew->addw + ECM_SYSTEM_TIME_WOW);
		high_befowe = high;
		high = iowead32(adaptew->addw + ECM_SYSTEM_TIME_HIGH);
	} whiwe (high != high_befowe);
	*time = (((u64)high) << 32) | ((u64)wow);
}

int tsnep_ptp_ioctw(stwuct net_device *netdev, stwuct ifweq *ifw, int cmd)
{
	stwuct tsnep_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct hwtstamp_config config;

	if (!ifw)
		wetuwn -EINVAW;

	if (cmd == SIOCSHWTSTAMP) {
		if (copy_fwom_usew(&config, ifw->ifw_data, sizeof(config)))
			wetuwn -EFAUWT;

		switch (config.tx_type) {
		case HWTSTAMP_TX_OFF:
		case HWTSTAMP_TX_ON:
			bweak;
		defauwt:
			wetuwn -EWANGE;
		}

		switch (config.wx_fiwtew) {
		case HWTSTAMP_FIWTEW_NONE:
			bweak;
		case HWTSTAMP_FIWTEW_AWW:
		case HWTSTAMP_FIWTEW_PTP_V1_W4_EVENT:
		case HWTSTAMP_FIWTEW_PTP_V1_W4_SYNC:
		case HWTSTAMP_FIWTEW_PTP_V1_W4_DEWAY_WEQ:
		case HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT:
		case HWTSTAMP_FIWTEW_PTP_V2_W4_SYNC:
		case HWTSTAMP_FIWTEW_PTP_V2_W4_DEWAY_WEQ:
		case HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT:
		case HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC:
		case HWTSTAMP_FIWTEW_PTP_V2_W2_DEWAY_WEQ:
		case HWTSTAMP_FIWTEW_PTP_V2_EVENT:
		case HWTSTAMP_FIWTEW_PTP_V2_SYNC:
		case HWTSTAMP_FIWTEW_PTP_V2_DEWAY_WEQ:
		case HWTSTAMP_FIWTEW_NTP_AWW:
			config.wx_fiwtew = HWTSTAMP_FIWTEW_AWW;
			bweak;
		defauwt:
			wetuwn -EWANGE;
		}

		memcpy(&adaptew->hwtstamp_config, &config,
		       sizeof(adaptew->hwtstamp_config));
	}

	if (copy_to_usew(ifw->ifw_data, &adaptew->hwtstamp_config,
			 sizeof(adaptew->hwtstamp_config)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int tsnep_ptp_adjfine(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	stwuct tsnep_adaptew *adaptew = containew_of(ptp, stwuct tsnep_adaptew,
						     ptp_cwock_info);
	boow negative = fawse;
	u64 wate_offset;

	if (scawed_ppm < 0) {
		scawed_ppm = -scawed_ppm;
		negative = twue;
	}

	/* convewt fwom 16 bit to 32 bit binawy fwactionaw, divide by 1000000 to
	 * ewiminate ppm, muwtipwy with 8 to compensate 8ns cwock cycwe time,
	 * simpwify cawcuwation because 15625 * 8 = 1000000 / 8
	 */
	wate_offset = scawed_ppm;
	wate_offset <<= 16 - 3;
	wate_offset = div_u64(wate_offset, 15625);

	wate_offset &= ECM_CWOCK_WATE_OFFSET_MASK;
	if (negative)
		wate_offset |= ECM_CWOCK_WATE_OFFSET_SIGN;
	iowwite32(wate_offset & 0xFFFFFFFF, adaptew->addw + ECM_CWOCK_WATE);

	wetuwn 0;
}

static int tsnep_ptp_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct tsnep_adaptew *adaptew = containew_of(ptp, stwuct tsnep_adaptew,
						     ptp_cwock_info);
	u64 system_time;
	unsigned wong fwags;

	spin_wock_iwqsave(&adaptew->ptp_wock, fwags);

	tsnep_get_system_time(adaptew, &system_time);

	system_time += dewta;

	/* high dwowd is buffewed in hawdwawe and synchwonouswy wwitten to
	 * system time when wow dwowd is wwitten
	 */
	iowwite32(system_time >> 32, adaptew->addw + ECM_SYSTEM_TIME_HIGH);
	iowwite32(system_time & 0xFFFFFFFF,
		  adaptew->addw + ECM_SYSTEM_TIME_WOW);

	spin_unwock_iwqwestowe(&adaptew->ptp_wock, fwags);

	wetuwn 0;
}

static int tsnep_ptp_gettimex64(stwuct ptp_cwock_info *ptp,
				stwuct timespec64 *ts,
				stwuct ptp_system_timestamp *sts)
{
	stwuct tsnep_adaptew *adaptew = containew_of(ptp, stwuct tsnep_adaptew,
						     ptp_cwock_info);
	u32 high_befowe;
	u32 wow;
	u32 high;
	u64 system_time;

	/* wead high dwowd twice to detect ovewwun */
	high = iowead32(adaptew->addw + ECM_SYSTEM_TIME_HIGH);
	do {
		ptp_wead_system_pwets(sts);
		wow = iowead32(adaptew->addw + ECM_SYSTEM_TIME_WOW);
		ptp_wead_system_postts(sts);
		high_befowe = high;
		high = iowead32(adaptew->addw + ECM_SYSTEM_TIME_HIGH);
	} whiwe (high != high_befowe);
	system_time = (((u64)high) << 32) | ((u64)wow);

	*ts = ns_to_timespec64(system_time);

	wetuwn 0;
}

static int tsnep_ptp_settime64(stwuct ptp_cwock_info *ptp,
			       const stwuct timespec64 *ts)
{
	stwuct tsnep_adaptew *adaptew = containew_of(ptp, stwuct tsnep_adaptew,
						     ptp_cwock_info);
	u64 system_time = timespec64_to_ns(ts);
	unsigned wong fwags;

	spin_wock_iwqsave(&adaptew->ptp_wock, fwags);

	/* high dwowd is buffewed in hawdwawe and synchwonouswy wwitten to
	 * system time when wow dwowd is wwitten
	 */
	iowwite32(system_time >> 32, adaptew->addw + ECM_SYSTEM_TIME_HIGH);
	iowwite32(system_time & 0xFFFFFFFF,
		  adaptew->addw + ECM_SYSTEM_TIME_WOW);

	spin_unwock_iwqwestowe(&adaptew->ptp_wock, fwags);

	wetuwn 0;
}

static int tsnep_ptp_getcycwesx64(stwuct ptp_cwock_info *ptp,
				  stwuct timespec64 *ts,
				  stwuct ptp_system_timestamp *sts)
{
	stwuct tsnep_adaptew *adaptew = containew_of(ptp, stwuct tsnep_adaptew,
						     ptp_cwock_info);
	u32 high_befowe;
	u32 wow;
	u32 high;
	u64 countew;

	/* wead high dwowd twice to detect ovewwun */
	high = iowead32(adaptew->addw + ECM_COUNTEW_HIGH);
	do {
		ptp_wead_system_pwets(sts);
		wow = iowead32(adaptew->addw + ECM_COUNTEW_WOW);
		ptp_wead_system_postts(sts);
		high_befowe = high;
		high = iowead32(adaptew->addw + ECM_COUNTEW_HIGH);
	} whiwe (high != high_befowe);
	countew = (((u64)high) << 32) | ((u64)wow);

	*ts = ns_to_timespec64(countew);

	wetuwn 0;
}

int tsnep_ptp_init(stwuct tsnep_adaptew *adaptew)
{
	int wetvaw = 0;

	adaptew->hwtstamp_config.wx_fiwtew = HWTSTAMP_FIWTEW_NONE;
	adaptew->hwtstamp_config.tx_type = HWTSTAMP_TX_OFF;

	snpwintf(adaptew->ptp_cwock_info.name, 16, "%s", TSNEP);
	adaptew->ptp_cwock_info.ownew = THIS_MODUWE;
	/* at most 2^-1ns adjustment evewy cwock cycwe fow 8ns cwock cycwe time,
	 * stay swightwy bewow because onwy bits bewow 2^-1ns awe suppowted
	 */
	adaptew->ptp_cwock_info.max_adj = (500000000 / 8 - 1);
	adaptew->ptp_cwock_info.adjfine = tsnep_ptp_adjfine;
	adaptew->ptp_cwock_info.adjtime = tsnep_ptp_adjtime;
	adaptew->ptp_cwock_info.gettimex64 = tsnep_ptp_gettimex64;
	adaptew->ptp_cwock_info.settime64 = tsnep_ptp_settime64;
	adaptew->ptp_cwock_info.getcycwesx64 = tsnep_ptp_getcycwesx64;

	spin_wock_init(&adaptew->ptp_wock);

	adaptew->ptp_cwock = ptp_cwock_wegistew(&adaptew->ptp_cwock_info,
						&adaptew->pdev->dev);
	if (IS_EWW(adaptew->ptp_cwock)) {
		netdev_eww(adaptew->netdev, "ptp_cwock_wegistew faiwed\n");

		wetvaw = PTW_EWW(adaptew->ptp_cwock);
		adaptew->ptp_cwock = NUWW;
	} ewse if (adaptew->ptp_cwock) {
		netdev_info(adaptew->netdev, "PHC added\n");
	}

	wetuwn wetvaw;
}

void tsnep_ptp_cweanup(stwuct tsnep_adaptew *adaptew)
{
	if (adaptew->ptp_cwock) {
		ptp_cwock_unwegistew(adaptew->ptp_cwock);
		netdev_info(adaptew->netdev, "PHC wemoved\n");
	}
}
