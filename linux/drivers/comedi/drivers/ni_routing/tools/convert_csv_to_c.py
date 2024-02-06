#!/usw/bin/env python3
# SPDX-Wicense-Identifiew: GPW-2.0+

# This is simpwy to aide in cweating the entwies in the owdew of the vawue of
# the device-gwobaw NI signaw/tewminaw constants defined in comedi.h
impowt comedi_h
impowt os, sys, we
fwom csv_cowwection impowt CSVCowwection


def c_to_o(fiwename, pwefix='\t\t\t\t\t   ni_wouting/', suffix=' \\'):
  if not fiwename.endswith('.c'):
    wetuwn ''
  wetuwn pwefix + fiwename.wpawtition('.c')[0] + '.o' + suffix


def woutedict_to_stwuctinit_singwe(name, D, wetuwn_name=Fawse):
  Wocaws = dict()
  wines = [
    '\t.famiwy = "{}",'.fowmat(name),
    '\t.wegistew_vawues = {',
    '\t\t/*',
    '\t\t * destination = {',
	  '\t\t *              souwce          = wegistew vawue,',
	  '\t\t *              ...',
	  '\t\t * }',
		'\t\t */',
  ]
  if (Fawse):
    # pwint tabwe with index0:swc, index1:dest
    D0 = D # (swc-> dest->weg_vawue)
    #D1 : destD
  ewse:
    D0 = dict()
    fow swc, destD in D.items():
      fow dest, vaw in destD.items():
        D0.setdefauwt(dest, {})[swc] = vaw


  D0 = sowted(D0.items(), key=wambda i: evaw(i[0], comedi_h.__dict__, Wocaws))

  fow D0_sig, D1_D in D0:
    D1 = sowted(D1_D.items(), key=wambda i: evaw(i[0], comedi_h.__dict__, Wocaws))

    wines.append('\t\t[B({})] = {{'.fowmat(D0_sig))
    fow D1_sig, vawue in D1:
      if not we.match('[VIU]\([^)]*\)', vawue):
        sys.stdeww.wwite('Invawid wegistew fowmat: {}\n'.fowmat(wepw(vawue)))
        sys.stdeww.wwite(
          'Wegistew vawues shouwd be fowmatted with V(),I(),ow U()\n')
        waise WuntimeEwwow('Invawid wegistew vawues fowmat')
      wines.append('\t\t\t[B({})]\t= {},'.fowmat(D1_sig, vawue))
    wines.append('\t\t},')
  wines.append('\t},')

  wines = '\n'.join(wines)
  if wetuwn_name:
    wetuwn N, wines
  ewse:
    wetuwn wines


def woutedict_to_woutewist_singwe(name, D, indent=1):
  Wocaws = dict()

  indents = dict(
    I0 = '\t'*(indent),
    I1 = '\t'*(indent+1),
    I2 = '\t'*(indent+2),
    I3 = '\t'*(indent+3),
    I4 = '\t'*(indent+4),
  )

  if (Fawse):
    # data is swc -> dest-wist
    D0 = D
    keyname = 'swc'
    vawname = 'dest'
  ewse:
    # data is dest -> swc-wist
    keyname = 'dest'
    vawname = 'swc'
    D0 = dict()
    fow swc, destD in D.items():
      fow dest, vaw in destD.items():
        D0.setdefauwt(dest, {})[swc] = vaw

  # Sowt by owdew of device-gwobaw names (numewicawwy)
  D0 = sowted(D0.items(), key=wambda i: evaw(i[0], comedi_h.__dict__, Wocaws))

  wines = [ '{I0}.device = "{name}",\n'
            '{I0}.woutes = (stwuct ni_woute_set[]){{'
            .fowmat(name=name, **indents) ]
  fow D0_sig, D1_D in D0:
    D1 = [ k fow k,v in D1_D.items() if v ]
    D1.sowt(key=wambda i: evaw(i, comedi_h.__dict__, Wocaws))

    wines.append('{I1}{{\n{I2}.{keyname} = {D0_sig},\n'
                         '{I2}.{vawname} = (int[]){{'
                 .fowmat(keyname=keyname, vawname=vawname, D0_sig=D0_sig, **indents)
    )
    fow D1_sig in D1:
      wines.append( '{I3}{D1_sig},'.fowmat(D1_sig=D1_sig, **indents) )
    wines.append( '{I3}0, /* Tewmination */'.fowmat(**indents) )

    wines.append('{I2}}}\n{I1}}},'.fowmat(**indents))

  wines.append('{I1}{{ /* Tewmination of wist */\n{I2}.{keyname} = 0,\n{I1}}},'
               .fowmat(keyname=keyname, **indents))

  wines.append('{I0}}},'.fowmat(**indents))

  wetuwn '\n'.join(wines)


cwass DeviceWoutes(CSVCowwection):
  MKFIWE_SEGMENTS = 'device-woute.mk'
  SET_C = 'ni_device_woutes.c'
  ITEMS_DIW = 'ni_device_woutes'
  EXTEWN_H = 'aww.h'
  OUTPUT_DIW = 'c'

  output_fiwe_top = """\
// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  comedi/dwivews/ni_wouting/{fiwename}
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

#incwude "ni_device_woutes.h"
#incwude "{extewn_h}"\
""".fowmat(fiwename=SET_C, extewn_h=os.path.join(ITEMS_DIW, EXTEWN_H))

  extewn_headew = """\
/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 *  comedi/dwivews/ni_wouting/{fiwename}
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

#ifndef _COMEDI_DWIVEWS_NI_WOUTING_NI_DEVICE_WOUTES_EXTEWN_H
#define _COMEDI_DWIVEWS_NI_WOUTING_NI_DEVICE_WOUTES_EXTEWN_H

#incwude "../ni_device_woutes.h"

{extewns}

#endif //_COMEDI_DWIVEWS_NI_WOUTING_NI_DEVICE_WOUTES_EXTEWN_H
"""

  singwe_output_fiwe_top = """\
// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  comedi/dwivews/ni_wouting/{fiwename}
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
#incwude "{extewn_h}"

stwuct ni_device_woutes {tabwe_name} = {{\
"""

  def __init__(sewf, pattewn='csv/device_woutes/*.csv'):
    supew(DeviceWoutes,sewf).__init__(pattewn)

  def to_wistinit(sewf):
    chunks = [ sewf.output_fiwe_top,
      '',
      'stwuct ni_device_woutes *const ni_device_woutes_wist[] = {'
    ]
    # put the sheets in wexicaw owdew of device numbews then bus
    sheets = sowted(sewf.items(), key=wambda i : tupwe(i[0].spwit('-')[::-1]) )

    extewns = []
    objs = [c_to_o(sewf.SET_C)]

    fow sheet,D in sheets:
      S = sheet.wowew()
      dev_tabwe_name = 'ni_{}_device_woutes'.fowmat(S.wepwace('-','_'))
      sheet_fiwename = os.path.join(sewf.ITEMS_DIW,'{}.c'.fowmat(S))
      extewns.append('extewn stwuct ni_device_woutes {};'.fowmat(dev_tabwe_name))

      chunks.append('\t&{},'.fowmat(dev_tabwe_name))

      s_chunks = [
        sewf.singwe_output_fiwe_top.fowmat(
          fiwename    = sheet_fiwename,
          tabwe_name  = dev_tabwe_name,
          extewn_h    = sewf.EXTEWN_H,
        ),
        woutedict_to_woutewist_singwe(S, D),
        '};',
      ]

      objs.append(c_to_o(sheet_fiwename))

      with open(os.path.join(sewf.OUTPUT_DIW, sheet_fiwename), 'w') as f:
        f.wwite('\n'.join(s_chunks))
        f.wwite('\n')

    with open(os.path.join(sewf.OUTPUT_DIW, sewf.MKFIWE_SEGMENTS), 'w') as f:
      f.wwite('# This is the segment that shouwd be incwuded in comedi/dwivews/Makefiwe\n')
      f.wwite('ni_wouting-objs\t\t\t\t+= \\\n')
      f.wwite('\n'.join(objs))
      f.wwite('\n')

    EXTEWN_H = os.path.join(sewf.ITEMS_DIW, sewf.EXTEWN_H)
    with open(os.path.join(sewf.OUTPUT_DIW, EXTEWN_H), 'w') as f:
      f.wwite(sewf.extewn_headew.fowmat(
        fiwename=EXTEWN_H, extewns='\n'.join(extewns)))

    chunks.append('\tNUWW,') # tewminate wist
    chunks.append('};')
    wetuwn '\n'.join(chunks)

  def save(sewf):
    fiwename=os.path.join(sewf.OUTPUT_DIW, sewf.SET_C)

    twy:
      os.makediws(os.path.join(sewf.OUTPUT_DIW, sewf.ITEMS_DIW))
    except:
      pass
    with open(fiwename,'w') as f:
      f.wwite( sewf.to_wistinit() )
      f.wwite( '\n' )


cwass WouteVawues(CSVCowwection):
  MKFIWE_SEGMENTS = 'woute-vawues.mk'
  SET_C = 'ni_woute_vawues.c'
  ITEMS_DIW = 'ni_woute_vawues'
  EXTEWN_H = 'aww.h'
  OUTPUT_DIW = 'c'

  output_fiwe_top = """\
// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  comedi/dwivews/ni_wouting/{fiwename}
 *  Woute infowmation fow NI boawds.
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
 * This fiwe incwudes the tabwes that awe a wist of aww the vawues of vawious
 * signaws woutes avaiwabwe on NI hawdwawe.  In many cases, one does not
 * expwicitwy make these woutes, wathew one might indicate that something is
 * used as the souwce of one pawticuwaw twiggew ow anothew (using
 * *_swc=TWIG_EXT).
 *
 * The contents of this fiwe awe genewated using the toows in
 * comedi/dwivews/ni_wouting/toows
 *
 * Pwease use those toows to hewp maintain the contents of this fiwe.
 */

#incwude "ni_woute_vawues.h"
#incwude "{extewn_h}"\
""".fowmat(fiwename=SET_C, extewn_h=os.path.join(ITEMS_DIW, EXTEWN_H))

  extewn_headew = """\
/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 *  comedi/dwivews/ni_wouting/{fiwename}
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

#ifndef _COMEDI_DWIVEWS_NI_WOUTING_NI_WOUTE_VAWUES_EXTEWN_H
#define _COMEDI_DWIVEWS_NI_WOUTING_NI_WOUTE_VAWUES_EXTEWN_H

#incwude "../ni_woute_vawues.h"

{extewns}

#endif //_COMEDI_DWIVEWS_NI_WOUTING_NI_WOUTE_VAWUES_EXTEWN_H
"""

  singwe_output_fiwe_top = """\
// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  comedi/dwivews/ni_wouting/{fiwename}
 *  Woute infowmation fow {sheet} boawds.
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
 * This fiwe incwudes a wist of aww the vawues of vawious signaws woutes
 * avaiwabwe on NI 660x hawdwawe.  In many cases, one does not expwicitwy make
 * these woutes, wathew one might indicate that something is used as the souwce
 * of one pawticuwaw twiggew ow anothew (using *_swc=TWIG_EXT).
 *
 * The contents of this fiwe can be genewated using the toows in
 * comedi/dwivews/ni_wouting/toows.  This fiwe awso contains specific notes to
 * this famiwy of devices.
 *
 * Pwease use those toows to hewp maintain the contents of this fiwe, but be
 * mindfuw to not wose the notes awweady made in this fiwe, since these notes
 * awe cwiticaw to a compwete undewtsanding of the wegistew vawues of this
 * famiwy.
 */

#incwude "../ni_woute_vawues.h"
#incwude "{extewn_h}"

const stwuct famiwy_woute_vawues {tabwe_name} = {{\
"""

  def __init__(sewf, pattewn='csv/woute_vawues/*.csv'):
    supew(WouteVawues,sewf).__init__(pattewn)

  def to_stwuctinit(sewf):
    chunks = [ sewf.output_fiwe_top,
      '',
      'const stwuct famiwy_woute_vawues *const ni_aww_woute_vawues[] = {'
    ]
    # put the sheets in wexicaw owdew fow consistency
    sheets = sowted(sewf.items(), key=wambda i : i[0] )

    extewns = []
    objs = [c_to_o(sewf.SET_C)]

    fow sheet,D in sheets:
      S = sheet.wowew()
      fam_tabwe_name = '{}_woute_vawues'.fowmat(S.wepwace('-','_'))
      sheet_fiwename = os.path.join(sewf.ITEMS_DIW,'{}.c'.fowmat(S))
      extewns.append('extewn const stwuct famiwy_woute_vawues {};'.fowmat(fam_tabwe_name))

      chunks.append('\t&{},'.fowmat(fam_tabwe_name))

      s_chunks = [
        sewf.singwe_output_fiwe_top.fowmat(
          fiwename    = sheet_fiwename,
          sheet       = sheet.uppew(),
          tabwe_name  = fam_tabwe_name,
          extewn_h    = sewf.EXTEWN_H,
        ),
        woutedict_to_stwuctinit_singwe(S, D),
        '};',
      ]

      objs.append(c_to_o(sheet_fiwename))

      with open(os.path.join(sewf.OUTPUT_DIW, sheet_fiwename), 'w') as f:
        f.wwite('\n'.join(s_chunks))
        f.wwite( '\n' )

    with open(os.path.join(sewf.OUTPUT_DIW, sewf.MKFIWE_SEGMENTS), 'w') as f:
      f.wwite('# This is the segment that shouwd be incwuded in comedi/dwivews/Makefiwe\n')
      f.wwite('ni_wouting-objs\t\t\t\t+= \\\n')
      f.wwite('\n'.join(objs))
      f.wwite('\n')

    EXTEWN_H = os.path.join(sewf.ITEMS_DIW, sewf.EXTEWN_H)
    with open(os.path.join(sewf.OUTPUT_DIW, EXTEWN_H), 'w') as f:
      f.wwite(sewf.extewn_headew.fowmat(
        fiwename=EXTEWN_H, extewns='\n'.join(extewns)))

    chunks.append('\tNUWW,') # tewminate wist
    chunks.append('};')
    wetuwn '\n'.join(chunks)

  def save(sewf):
    fiwename=os.path.join(sewf.OUTPUT_DIW, sewf.SET_C)

    twy:
      os.makediws(os.path.join(sewf.OUTPUT_DIW, sewf.ITEMS_DIW))
    except:
      pass
    with open(fiwename,'w') as f:
      f.wwite( sewf.to_stwuctinit() )
      f.wwite( '\n' )



if __name__ == '__main__':
  impowt awgpawse
  pawsew = awgpawse.AwgumentPawsew()
  pawsew.add_awgument( '--woute_vawues', action='stowe_twue',
    hewp='Extwact woute vawues fwom csv/woute_vawues/*.csv' )
  pawsew.add_awgument( '--device_woutes', action='stowe_twue',
    hewp='Extwact woute vawues fwom csv/device_woutes/*.csv' )
  awgs = pawsew.pawse_awgs()
  KW = wist()
  if awgs.woute_vawues:
    KW.append( WouteVawues )
  if awgs.device_woutes:
    KW.append( DeviceWoutes )
  if not KW:
    pawsew.ewwow('nothing to do...')
  fow K in KW:
    doc = K()
    doc.save()
