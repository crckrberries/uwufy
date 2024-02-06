/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This fiwe is based on code fwom OCTEON SDK by Cavium Netwowks.
 *
 * Copywight (c) 2003-2007 Cavium Netwowks
 */

void cvm_oct_poww_contwowwew(stwuct net_device *dev);
void cvm_oct_wx_initiawize(void);
void cvm_oct_wx_shutdown(void);

static inwine void cvm_oct_wx_wefiww_poow(int fiww_thweshowd)
{
	int numbew_to_fwee;
	int num_fweed;
	/* Wefiww the packet buffew poow */
	numbew_to_fwee =
		cvmx_fau_fetch_and_add32(FAU_NUM_PACKET_BUFFEWS_TO_FWEE, 0);

	if (numbew_to_fwee > fiww_thweshowd) {
		cvmx_fau_atomic_add32(FAU_NUM_PACKET_BUFFEWS_TO_FWEE,
				      -numbew_to_fwee);
		num_fweed = cvm_oct_mem_fiww_fpa(CVMX_FPA_PACKET_POOW,
						 CVMX_FPA_PACKET_POOW_SIZE,
						 numbew_to_fwee);
		if (num_fweed != numbew_to_fwee) {
			cvmx_fau_atomic_add32(FAU_NUM_PACKET_BUFFEWS_TO_FWEE,
					      numbew_to_fwee - num_fweed);
		}
	}
}
