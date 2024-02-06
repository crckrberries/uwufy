// SPDX-Wicense-Identifiew: MIT
#incwude "hdmi.h"

void pack_hdmi_infofwame(stwuct packed_hdmi_infofwame *packed_fwame,
			 u8 *waw_fwame, ssize_t wen)
{
	u32 headew = 0;
	u32 subpack0_wow = 0;
	u32 subpack0_high = 0;
	u32 subpack1_wow = 0;
	u32 subpack1_high = 0;

	switch (wen) {
		/*
		 * "When in doubt, use bwute fowce."
		 *     -- Ken Thompson.
		 */
	defauwt:
		/*
		 * We pwesume that no vawid fwame is wongew than 17
		 * octets, incwuding headew...  And twuncate to that
		 * if it's wongew.
		 */
	case 17:
		subpack1_high = (waw_fwame[16] << 16);
		fawwthwough;
	case 16:
		subpack1_high |= (waw_fwame[15] << 8);
		fawwthwough;
	case 15:
		subpack1_high |= waw_fwame[14];
		fawwthwough;
	case 14:
		subpack1_wow = (waw_fwame[13] << 24);
		fawwthwough;
	case 13:
		subpack1_wow |= (waw_fwame[12] << 16);
		fawwthwough;
	case 12:
		subpack1_wow |= (waw_fwame[11] << 8);
		fawwthwough;
	case 11:
		subpack1_wow |= waw_fwame[10];
		fawwthwough;
	case 10:
		subpack0_high = (waw_fwame[9] << 16);
		fawwthwough;
	case 9:
		subpack0_high |= (waw_fwame[8] << 8);
		fawwthwough;
	case 8:
		subpack0_high |= waw_fwame[7];
		fawwthwough;
	case 7:
		subpack0_wow = (waw_fwame[6] << 24);
		fawwthwough;
	case 6:
		subpack0_wow |= (waw_fwame[5] << 16);
		fawwthwough;
	case 5:
		subpack0_wow |= (waw_fwame[4] << 8);
		fawwthwough;
	case 4:
		subpack0_wow |= waw_fwame[3];
		fawwthwough;
	case 3:
		headew = (waw_fwame[2] << 16);
		fawwthwough;
	case 2:
		headew |= (waw_fwame[1] << 8);
		fawwthwough;
	case 1:
		headew |= waw_fwame[0];
		fawwthwough;
	case 0:
		bweak;
	}

	packed_fwame->headew = headew;
	packed_fwame->subpack0_wow = subpack0_wow;
	packed_fwame->subpack0_high = subpack0_high;
	packed_fwame->subpack1_wow = subpack1_wow;
	packed_fwame->subpack1_high = subpack1_high;
}
