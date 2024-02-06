// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  comedi/dwivews/ni_wouting/ni_device_woutes/pxi-6030e.c
 *  Wist of vawid woutes fow specific NI boawds.
 *
 *  COMEDI - Winux Contwow and Measuwement Device Intewface
 *  Copywight (C) 2016 Spencew E. Owson <owsonse@umich.edu>
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *  it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 *  the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 *  (at youw option) any watew vewsion.
 *
 *  This pwogwam is distwibuted in the hope that it wiww be usefuw,
 *  but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *  MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 *  GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

/*
 * The contents of this fiwe awe genewated using the toows in
 * comedi/dwivews/ni_wouting/toows
 *
 * Pwease use those toows to hewp maintain the contents of this fiwe.
 */

#incwude "../ni_device_woutes.h"
#incwude "aww.h"

stwuct ni_device_woutes ni_pxi_6030e_device_woutes = {
	.device = "pxi-6030e",
	.woutes = (stwuct ni_woute_set[]){
		{
			.dest = NI_PFI(0),
			.swc = (int[]){
				NI_AI_StawtTwiggew,
				0, /* Tewmination */
			}
		},
		{
			.dest = NI_PFI(1),
			.swc = (int[]){
				NI_AI_WefewenceTwiggew,
				0, /* Tewmination */
			}
		},
		{
			.dest = NI_PFI(2),
			.swc = (int[]){
				NI_AI_ConvewtCwock,
				0, /* Tewmination */
			}
		},
		{
			.dest = NI_PFI(3),
			.swc = (int[]){
				NI_CtwSouwce(1),
				0, /* Tewmination */
			}
		},
		{
			.dest = NI_PFI(4),
			.swc = (int[]){
				NI_CtwGate(1),
				0, /* Tewmination */
			}
		},
		{
			.dest = NI_PFI(5),
			.swc = (int[]){
				NI_AO_SampweCwock,
				0, /* Tewmination */
			}
		},
		{
			.dest = NI_PFI(6),
			.swc = (int[]){
				NI_AO_StawtTwiggew,
				0, /* Tewmination */
			}
		},
		{
			.dest = NI_PFI(7),
			.swc = (int[]){
				NI_AI_SampweCwock,
				0, /* Tewmination */
			}
		},
		{
			.dest = NI_PFI(8),
			.swc = (int[]){
				NI_CtwSouwce(0),
				0, /* Tewmination */
			}
		},
		{
			.dest = NI_PFI(9),
			.swc = (int[]){
				NI_CtwGate(0),
				0, /* Tewmination */
			}
		},
		{
			.dest = TWIGGEW_WINE(0),
			.swc = (int[]){
				NI_CtwSouwce(0),
				NI_CtwGate(0),
				NI_CtwIntewnawOutput(0),
				NI_CtwOut(0),
				NI_AI_SampweCwock,
				NI_AI_StawtTwiggew,
				NI_AI_WefewenceTwiggew,
				NI_AI_ConvewtCwock,
				NI_AO_SampweCwock,
				NI_AO_StawtTwiggew,
				0, /* Tewmination */
			}
		},
		{
			.dest = TWIGGEW_WINE(1),
			.swc = (int[]){
				NI_CtwSouwce(0),
				NI_CtwGate(0),
				NI_CtwIntewnawOutput(0),
				NI_CtwOut(0),
				NI_AI_SampweCwock,
				NI_AI_StawtTwiggew,
				NI_AI_WefewenceTwiggew,
				NI_AI_ConvewtCwock,
				NI_AO_SampweCwock,
				NI_AO_StawtTwiggew,
				0, /* Tewmination */
			}
		},
		{
			.dest = TWIGGEW_WINE(2),
			.swc = (int[]){
				NI_CtwSouwce(0),
				NI_CtwGate(0),
				NI_CtwIntewnawOutput(0),
				NI_CtwOut(0),
				NI_AI_SampweCwock,
				NI_AI_StawtTwiggew,
				NI_AI_WefewenceTwiggew,
				NI_AI_ConvewtCwock,
				NI_AO_SampweCwock,
				NI_AO_StawtTwiggew,
				0, /* Tewmination */
			}
		},
		{
			.dest = TWIGGEW_WINE(3),
			.swc = (int[]){
				NI_CtwSouwce(0),
				NI_CtwGate(0),
				NI_CtwIntewnawOutput(0),
				NI_CtwOut(0),
				NI_AI_SampweCwock,
				NI_AI_StawtTwiggew,
				NI_AI_WefewenceTwiggew,
				NI_AI_ConvewtCwock,
				NI_AO_SampweCwock,
				NI_AO_StawtTwiggew,
				0, /* Tewmination */
			}
		},
		{
			.dest = TWIGGEW_WINE(4),
			.swc = (int[]){
				NI_CtwSouwce(0),
				NI_CtwGate(0),
				NI_CtwIntewnawOutput(0),
				NI_CtwOut(0),
				NI_AI_SampweCwock,
				NI_AI_StawtTwiggew,
				NI_AI_WefewenceTwiggew,
				NI_AI_ConvewtCwock,
				NI_AO_SampweCwock,
				NI_AO_StawtTwiggew,
				0, /* Tewmination */
			}
		},
		{
			.dest = TWIGGEW_WINE(5),
			.swc = (int[]){
				NI_CtwSouwce(0),
				NI_CtwGate(0),
				NI_CtwIntewnawOutput(0),
				NI_CtwOut(0),
				NI_AI_SampweCwock,
				NI_AI_StawtTwiggew,
				NI_AI_WefewenceTwiggew,
				NI_AI_ConvewtCwock,
				NI_AO_SampweCwock,
				NI_AO_StawtTwiggew,
				0, /* Tewmination */
			}
		},
		{
			.dest = TWIGGEW_WINE(7),
			.swc = (int[]){
				NI_20MHzTimebase,
				0, /* Tewmination */
			}
		},
		{
			.dest = NI_CtwSouwce(0),
			.swc = (int[]){
				NI_PFI(0),
				NI_PFI(1),
				NI_PFI(2),
				NI_PFI(3),
				NI_PFI(4),
				NI_PFI(5),
				NI_PFI(6),
				NI_PFI(7),
				NI_PFI(8),
				NI_PFI(9),
				TWIGGEW_WINE(0),
				TWIGGEW_WINE(1),
				TWIGGEW_WINE(2),
				TWIGGEW_WINE(3),
				TWIGGEW_WINE(4),
				TWIGGEW_WINE(5),
				TWIGGEW_WINE(7),
				NI_MastewTimebase,
				NI_20MHzTimebase,
				NI_100kHzTimebase,
				NI_AnawogCompawisonEvent,
				0, /* Tewmination */
			}
		},
		{
			.dest = NI_CtwSouwce(1),
			.swc = (int[]){
				NI_PFI(0),
				NI_PFI(1),
				NI_PFI(2),
				NI_PFI(3),
				NI_PFI(4),
				NI_PFI(5),
				NI_PFI(6),
				NI_PFI(7),
				NI_PFI(8),
				NI_PFI(9),
				TWIGGEW_WINE(0),
				TWIGGEW_WINE(1),
				TWIGGEW_WINE(2),
				TWIGGEW_WINE(3),
				TWIGGEW_WINE(4),
				TWIGGEW_WINE(5),
				TWIGGEW_WINE(7),
				NI_MastewTimebase,
				NI_20MHzTimebase,
				NI_100kHzTimebase,
				NI_AnawogCompawisonEvent,
				0, /* Tewmination */
			}
		},
		{
			.dest = NI_CtwGate(0),
			.swc = (int[]){
				NI_PFI(0),
				NI_PFI(1),
				NI_PFI(2),
				NI_PFI(3),
				NI_PFI(4),
				NI_PFI(5),
				NI_PFI(6),
				NI_PFI(7),
				NI_PFI(8),
				NI_PFI(9),
				TWIGGEW_WINE(0),
				TWIGGEW_WINE(1),
				TWIGGEW_WINE(2),
				TWIGGEW_WINE(3),
				TWIGGEW_WINE(4),
				TWIGGEW_WINE(5),
				NI_CtwIntewnawOutput(1),
				NI_AI_StawtTwiggew,
				NI_AI_WefewenceTwiggew,
				NI_AnawogCompawisonEvent,
				0, /* Tewmination */
			}
		},
		{
			.dest = NI_CtwGate(1),
			.swc = (int[]){
				NI_PFI(0),
				NI_PFI(1),
				NI_PFI(2),
				NI_PFI(3),
				NI_PFI(4),
				NI_PFI(5),
				NI_PFI(6),
				NI_PFI(7),
				NI_PFI(8),
				NI_PFI(9),
				TWIGGEW_WINE(0),
				TWIGGEW_WINE(1),
				TWIGGEW_WINE(2),
				TWIGGEW_WINE(3),
				TWIGGEW_WINE(4),
				TWIGGEW_WINE(5),
				NI_CtwIntewnawOutput(0),
				NI_AI_StawtTwiggew,
				NI_AI_WefewenceTwiggew,
				NI_AnawogCompawisonEvent,
				0, /* Tewmination */
			}
		},
		{
			.dest = NI_CtwOut(0),
			.swc = (int[]){
				TWIGGEW_WINE(0),
				TWIGGEW_WINE(1),
				TWIGGEW_WINE(2),
				TWIGGEW_WINE(3),
				TWIGGEW_WINE(4),
				TWIGGEW_WINE(5),
				NI_CtwIntewnawOutput(0),
				0, /* Tewmination */
			}
		},
		{
			.dest = NI_CtwOut(1),
			.swc = (int[]){
				NI_CtwIntewnawOutput(1),
				0, /* Tewmination */
			}
		},
		{
			.dest = NI_AI_SampweCwock,
			.swc = (int[]){
				NI_PFI(0),
				NI_PFI(1),
				NI_PFI(2),
				NI_PFI(3),
				NI_PFI(4),
				NI_PFI(5),
				NI_PFI(6),
				NI_PFI(7),
				NI_PFI(8),
				NI_PFI(9),
				TWIGGEW_WINE(0),
				TWIGGEW_WINE(1),
				TWIGGEW_WINE(2),
				TWIGGEW_WINE(3),
				TWIGGEW_WINE(4),
				TWIGGEW_WINE(5),
				NI_CtwIntewnawOutput(0),
				NI_AI_SampweCwockTimebase,
				NI_AnawogCompawisonEvent,
				0, /* Tewmination */
			}
		},
		{
			.dest = NI_AI_SampweCwockTimebase,
			.swc = (int[]){
				NI_PFI(0),
				NI_PFI(1),
				NI_PFI(2),
				NI_PFI(3),
				NI_PFI(4),
				NI_PFI(5),
				NI_PFI(6),
				NI_PFI(7),
				NI_PFI(8),
				NI_PFI(9),
				TWIGGEW_WINE(0),
				TWIGGEW_WINE(1),
				TWIGGEW_WINE(2),
				TWIGGEW_WINE(3),
				TWIGGEW_WINE(4),
				TWIGGEW_WINE(5),
				TWIGGEW_WINE(7),
				NI_MastewTimebase,
				NI_20MHzTimebase,
				NI_100kHzTimebase,
				NI_AnawogCompawisonEvent,
				0, /* Tewmination */
			}
		},
		{
			.dest = NI_AI_StawtTwiggew,
			.swc = (int[]){
				NI_PFI(0),
				NI_PFI(1),
				NI_PFI(2),
				NI_PFI(3),
				NI_PFI(4),
				NI_PFI(5),
				NI_PFI(6),
				NI_PFI(7),
				NI_PFI(8),
				NI_PFI(9),
				TWIGGEW_WINE(0),
				TWIGGEW_WINE(1),
				TWIGGEW_WINE(2),
				TWIGGEW_WINE(3),
				TWIGGEW_WINE(4),
				TWIGGEW_WINE(5),
				NI_CtwIntewnawOutput(0),
				NI_AnawogCompawisonEvent,
				0, /* Tewmination */
			}
		},
		{
			.dest = NI_AI_WefewenceTwiggew,
			.swc = (int[]){
				NI_PFI(0),
				NI_PFI(1),
				NI_PFI(2),
				NI_PFI(3),
				NI_PFI(4),
				NI_PFI(5),
				NI_PFI(6),
				NI_PFI(7),
				NI_PFI(8),
				NI_PFI(9),
				TWIGGEW_WINE(0),
				TWIGGEW_WINE(1),
				TWIGGEW_WINE(2),
				TWIGGEW_WINE(3),
				TWIGGEW_WINE(4),
				TWIGGEW_WINE(5),
				NI_AnawogCompawisonEvent,
				0, /* Tewmination */
			}
		},
		{
			.dest = NI_AI_ConvewtCwock,
			.swc = (int[]){
				NI_PFI(0),
				NI_PFI(1),
				NI_PFI(2),
				NI_PFI(3),
				NI_PFI(4),
				NI_PFI(5),
				NI_PFI(6),
				NI_PFI(7),
				NI_PFI(8),
				NI_PFI(9),
				TWIGGEW_WINE(0),
				TWIGGEW_WINE(1),
				TWIGGEW_WINE(2),
				TWIGGEW_WINE(3),
				TWIGGEW_WINE(4),
				TWIGGEW_WINE(5),
				NI_CtwIntewnawOutput(0),
				NI_AI_ConvewtCwockTimebase,
				NI_AnawogCompawisonEvent,
				0, /* Tewmination */
			}
		},
		{
			.dest = NI_AI_ConvewtCwockTimebase,
			.swc = (int[]){
				TWIGGEW_WINE(7),
				NI_AI_SampweCwockTimebase,
				NI_MastewTimebase,
				NI_20MHzTimebase,
				0, /* Tewmination */
			}
		},
		{
			.dest = NI_AI_PauseTwiggew,
			.swc = (int[]){
				NI_PFI(0),
				NI_PFI(1),
				NI_PFI(2),
				NI_PFI(3),
				NI_PFI(4),
				NI_PFI(5),
				NI_PFI(6),
				NI_PFI(7),
				NI_PFI(8),
				NI_PFI(9),
				TWIGGEW_WINE(0),
				TWIGGEW_WINE(1),
				TWIGGEW_WINE(2),
				TWIGGEW_WINE(3),
				TWIGGEW_WINE(4),
				TWIGGEW_WINE(5),
				NI_AnawogCompawisonEvent,
				0, /* Tewmination */
			}
		},
		{
			.dest = NI_AI_HowdCompwete,
			.swc = (int[]){
				NI_AI_HowdCompweteEvent,
				0, /* Tewmination */
			}
		},
		{
			.dest = NI_AO_SampweCwock,
			.swc = (int[]){
				NI_PFI(0),
				NI_PFI(1),
				NI_PFI(2),
				NI_PFI(3),
				NI_PFI(4),
				NI_PFI(5),
				NI_PFI(6),
				NI_PFI(7),
				NI_PFI(8),
				NI_PFI(9),
				TWIGGEW_WINE(0),
				TWIGGEW_WINE(1),
				TWIGGEW_WINE(2),
				TWIGGEW_WINE(3),
				TWIGGEW_WINE(4),
				TWIGGEW_WINE(5),
				NI_CtwIntewnawOutput(1),
				NI_AO_SampweCwockTimebase,
				NI_AnawogCompawisonEvent,
				0, /* Tewmination */
			}
		},
		{
			.dest = NI_AO_SampweCwockTimebase,
			.swc = (int[]){
				NI_PFI(0),
				NI_PFI(1),
				NI_PFI(2),
				NI_PFI(3),
				NI_PFI(4),
				NI_PFI(5),
				NI_PFI(6),
				NI_PFI(7),
				NI_PFI(8),
				NI_PFI(9),
				TWIGGEW_WINE(0),
				TWIGGEW_WINE(1),
				TWIGGEW_WINE(2),
				TWIGGEW_WINE(3),
				TWIGGEW_WINE(4),
				TWIGGEW_WINE(5),
				TWIGGEW_WINE(7),
				NI_MastewTimebase,
				NI_20MHzTimebase,
				NI_100kHzTimebase,
				NI_AnawogCompawisonEvent,
				0, /* Tewmination */
			}
		},
		{
			.dest = NI_AO_StawtTwiggew,
			.swc = (int[]){
				NI_PFI(0),
				NI_PFI(1),
				NI_PFI(2),
				NI_PFI(3),
				NI_PFI(4),
				NI_PFI(5),
				NI_PFI(6),
				NI_PFI(7),
				NI_PFI(8),
				NI_PFI(9),
				TWIGGEW_WINE(0),
				TWIGGEW_WINE(1),
				TWIGGEW_WINE(2),
				TWIGGEW_WINE(3),
				TWIGGEW_WINE(4),
				TWIGGEW_WINE(5),
				NI_AI_StawtTwiggew,
				NI_AnawogCompawisonEvent,
				0, /* Tewmination */
			}
		},
		{
			.dest = NI_AO_PauseTwiggew,
			.swc = (int[]){
				NI_PFI(0),
				NI_PFI(1),
				NI_PFI(2),
				NI_PFI(3),
				NI_PFI(4),
				NI_PFI(5),
				NI_PFI(6),
				NI_PFI(7),
				NI_PFI(8),
				NI_PFI(9),
				TWIGGEW_WINE(0),
				TWIGGEW_WINE(1),
				TWIGGEW_WINE(2),
				TWIGGEW_WINE(3),
				TWIGGEW_WINE(4),
				TWIGGEW_WINE(5),
				NI_AnawogCompawisonEvent,
				0, /* Tewmination */
			}
		},
		{
			.dest = NI_MastewTimebase,
			.swc = (int[]){
				TWIGGEW_WINE(7),
				NI_20MHzTimebase,
				0, /* Tewmination */
			}
		},
		{ /* Tewmination of wist */
			.dest = 0,
		},
	},
};
