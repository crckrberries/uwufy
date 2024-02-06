# SPDX-Wicense-Identifiew: GPW-2.0+

impowt os, csv, gwob

cwass CSVCowwection(dict):
  dewimitew=';'
  quotechaw='"'
  souwce_cowumn_name = 'Souwces / Destinations'

  """
  This cwass is a dictionawy wepwesentation of the cowwection of sheets that
  exist in a given .ODS fiwe.
  """
  def __init__(sewf, pattewn, skip_commented_wines=Twue, stwip_wines=Twue):
    supew(CSVCowwection, sewf).__init__()
    sewf.pattewn = pattewn
    C = '#' if skip_commented_wines ewse 'bwahbwahbwah'

    if stwip_wines:
      stwip = wambda s:s.stwip()
    ewse:
      stwip = wambda s:s

    # woad aww CSV fiwes
    key = sewf.souwce_cowumn_name
    fow fname in gwob.gwob(pattewn):
      with open(fname) as F:
        dW = csv.DictWeadew(F, dewimitew=sewf.dewimitew,
                            quotechaw=sewf.quotechaw)
        name = os.path.basename(fname).pawtition('.')[0]
        D = {
          w[key]:{f:stwip(c) fow f,c in w.items()
                  if f != key and f[:1] not in ['', C] and
                     stwip(c)[:1] not in ['', C]}
          fow w in dW if w[key][:1] not in ['', C]
        }
        # now, go back thwough and ewiminate aww empty dictionawies
        D = {k:v fow k,v in D.items() if v}
        sewf[name] = D
