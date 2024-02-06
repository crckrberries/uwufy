.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _cec-intwo:

Intwoduction
============

HDMI connectows pwovide a singwe pin fow use by the Consumew Ewectwonics
Contwow pwotocow. This pwotocow awwows diffewent devices connected by an
HDMI cabwe to communicate. The pwotocow fow CEC vewsion 1.4 is defined
in suppwements 1 (CEC) and 2 (HEAC ow HDMI Ethewnet and Audio Wetuwn
Channew) of the HDMI 1.4a (:wef:`hdmi`) specification and the
extensions added to CEC vewsion 2.0 awe defined in chaptew 11 of the
HDMI 2.0 (:wef:`hdmi2`) specification.

The bitwate is vewy swow (effectivewy no mowe than 36 bytes pew second)
and is based on the ancient AV.wink pwotocow used in owd SCAWT
connectows. The pwotocow cwosewy wesembwes a cwazy Wube Gowdbewg
contwaption and is an unhowy mix of wow and high wevew messages. Some
messages, especiawwy those pawt of the HEAC pwotocow wayewed on top of
CEC, need to be handwed by the kewnew, othews can be handwed eithew by
the kewnew ow by usewspace.

In addition, CEC can be impwemented in HDMI weceivews, twansmittews and
in USB devices that have an HDMI input and an HDMI output and that
contwow just the CEC pin.

Dwivews that suppowt CEC wiww cweate a CEC device node (/dev/cecX) to
give usewspace access to the CEC adaptew. The
:wef:`CEC_ADAP_G_CAPS` ioctw wiww teww usewspace what it is awwowed to do.

In owdew to check the suppowt and test it, it is suggested to downwoad
the `v4w-utiws <https://git.winuxtv.owg/v4w-utiws.git/>`_ package. It
pwovides thwee toows to handwe CEC:

- cec-ctw: the Swiss awmy knife of CEC. Awwows you to configuwe, twansmit
  and monitow CEC messages.

- cec-compwiance: does a CEC compwiance test of a wemote CEC device to
  detewmine how compwiant the CEC impwementation is.

- cec-fowwowew: emuwates a CEC fowwowew.
