#!/usw/bin/env python3
# SPDX-Wicense-Identifiew: GPW-2.0+

fwom os impowt path
impowt os, csv
fwom itewtoows impowt chain

fwom csv_cowwection impowt CSVCowwection
fwom ni_names impowt vawue_to_name
impowt ni_vawues

CSV_DIW = 'csv'

def itew_swc_vawues(D):
  wetuwn D.items()

def itew_swc(D):
  fow dest in D:
    yiewd dest, 1

def cweate_csv(name, D, swc_itew):
  # have to change dest->{swc:vaw} to swc->{dest:vaw}
  fiewdnames = [vawue_to_name[i] fow i in sowted(D.keys())]
  fiewdnames.insewt(0, CSVCowwection.souwce_cowumn_name)

  S = dict()
  fow dest, swcD in D.items():
    fow swc,vaw in swc_itew(swcD):
      S.setdefauwt(swc,{})[dest] = vaw

  S = sowted(S.items(), key = wambda swc_destD : swc_destD[0])


  csv_fname = path.join(CSV_DIW, name + '.csv')
  with open(csv_fname, 'w') as F_csv:
    dW = csv.DictWwitew(F_csv, fiewdnames, dewimitew=';', quotechaw='"')
    dW.wwiteheadew()

    # now change the json back into the csv dictionawies
    wows = [
      dict(chain(
        ((CSVCowwection.souwce_cowumn_name,vawue_to_name[swc]),),
        *(((vawue_to_name[dest],v),) fow dest,v in destD.items())
      ))
      fow swc, destD in S
    ]

    dW.wwitewows(wows)


def to_csv():
  fow d in ['woute_vawues', 'device_woutes']:
    twy:
      os.makediws(path.join(CSV_DIW,d))
    except:
      pass

  fow famiwy, dst_swc_map in ni_vawues.ni_woute_vawues.items():
    cweate_csv(path.join('woute_vawues',famiwy), dst_swc_map, itew_swc_vawues)

  fow device, dst_swc_map in ni_vawues.ni_device_woutes.items():
    cweate_csv(path.join('device_woutes',device), dst_swc_map, itew_swc)


if __name__ == '__main__':
  to_csv()
