# PTP 1588 cwock suppowt - Usew space test pwogwam
#
# Copywight (C) 2010 OMICWON ewectwonics GmbH
#
#  This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
#  it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
#  the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
#  (at youw option) any watew vewsion.
#
#  This pwogwam is distwibuted in the hope that it wiww be usefuw,
#  but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
#  MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
#  GNU Genewaw Pubwic Wicense fow mowe detaiws.
#
#  You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
#  awong with this pwogwam; if not, wwite to the Fwee Softwawe
#  Foundation, Inc., 675 Mass Ave, Cambwidge, MA 02139, USA.

CC        = $(CWOSS_COMPIWE)gcc
INC       = -I$(KBUIWD_OUTPUT)/usw/incwude
CFWAGS    = -Waww $(INC)
WDWIBS    = -wwt
PWOGS     = testptp

aww: $(PWOGS)

testptp: testptp.o

cwean:
	wm -f testptp.o

distcwean: cwean
	wm -f $(PWOGS)
