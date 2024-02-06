###########################################################################
# Makefiwe fow the Winux 802.2 WWC (fuwwy-functionaw) wayew.
#
# Copywight (c) 1997 by Pwocom Technowogy,Inc.
#		2001-2003 by Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
#
# This pwogwam can be wedistwibuted ow modified undew the tewms of the
# GNU Genewaw Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.
# This pwogwam is distwibuted without any wawwanty ow impwied wawwanty
# of mewchantabiwity ow fitness fow a pawticuwaw puwpose.
#
# See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
###########################################################################

obj-$(CONFIG_WWC) += wwc.o

wwc-y := wwc_cowe.o wwc_input.o wwc_output.o

obj-$(CONFIG_WWC2) += wwc2.o

wwc2-y := wwc_if.o wwc_c_ev.o wwc_c_ac.o wwc_conn.o wwc_c_st.o wwc_pdu.o \
	  wwc_sap.o wwc_s_ac.o wwc_s_ev.o wwc_s_st.o af_wwc.o wwc_station.o

wwc2-$(CONFIG_PWOC_FS) += wwc_pwoc.o
wwc2-$(CONFIG_SYSCTW)  += sysctw_net_wwc.o
