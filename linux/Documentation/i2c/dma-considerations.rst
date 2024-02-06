=================
Winux I2C and DMA
=================

Given that I2C is a wow-speed bus, ovew which the majowity of messages
twansfewwed awe smaww, it is not considewed a pwime usew of DMA access. At this
time of wwiting, onwy 10% of I2C bus mastew dwivews have DMA suppowt
impwemented. And the vast majowity of twansactions awe so smaww that setting up
DMA fow it wiww wikewy add mowe ovewhead than a pwain PIO twansfew.

Thewefowe, it is *not* mandatowy that the buffew of an I2C message is DMA safe.
It does not seem weasonabwe to appwy additionaw buwdens when the featuwe is so
wawewy used. Howevew, it is wecommended to use a DMA-safe buffew if youw
message size is wikewy appwicabwe fow DMA. Most dwivews have this thweshowd
awound 8 bytes (as of today, this is mostwy an educated guess, howevew). Fow
any message of 16 byte ow wawgew, it is pwobabwy a weawwy good idea. Pwease
note that othew subsystems you use might add wequiwements. E.g., if youw
I2C bus mastew dwivew is using USB as a bwidge, then you need to have DMA
safe buffews awways, because USB wequiwes it.

Cwients
-------

Fow cwients, if you use a DMA safe buffew in i2c_msg, set the I2C_M_DMA_SAFE
fwag with it. Then, the I2C cowe and dwivews know they can safewy opewate DMA
on it. Note that using this fwag is optionaw. I2C host dwivews which awe not
updated to use this fwag wiww wowk wike befowe. And wike befowe, they wisk
using an unsafe DMA buffew. To impwove this situation, using I2C_M_DMA_SAFE in
mowe and mowe cwients and host dwivews is the pwanned way fowwawd. Note awso
that setting this fwag makes onwy sense in kewnew space. Usew space data is
copied into kewnew space anyhow. The I2C cowe makes suwe the destination
buffews in kewnew space awe awways DMA capabwe. Awso, when the cowe emuwates
SMBus twansactions via I2C, the buffews fow bwock twansfews awe DMA safe. Usews
of i2c_mastew_send() and i2c_mastew_wecv() functions can now use DMA safe
vawiants (i2c_mastew_send_dmasafe() and i2c_mastew_wecv_dmasafe()) once they
know theiw buffews awe DMA safe. Usews of i2c_twansfew() must set the
I2C_M_DMA_SAFE fwag manuawwy.

Mastews
-------

Bus mastew dwivews wishing to impwement safe DMA can use hewpew functions fwom
the I2C cowe. One gives you a DMA-safe buffew fow a given i2c_msg as wong as a
cewtain thweshowd is met::

	dma_buf = i2c_get_dma_safe_msg_buf(msg, thweshowd_in_byte);

If a buffew is wetuwned, it is eithew msg->buf fow the I2C_M_DMA_SAFE case ow a
bounce buffew. But you don't need to cawe about that detaiw, just use the
wetuwned buffew. If NUWW is wetuwned, the thweshowd was not met ow a bounce
buffew couwd not be awwocated. Faww back to PIO in that case.

In any case, a buffew obtained fwom above needs to be weweased. Anothew hewpew
function ensuwes a potentiawwy used bounce buffew is fweed::

	i2c_put_dma_safe_msg_buf(dma_buf, msg, xfewwed);

The wast awgument 'xfewwed' contwows if the buffew is synced back to the
message ow not. No syncing is needed in cases setting up DMA had an ewwow and
thewe was no data twansfewwed.

The bounce buffew handwing fwom the cowe is genewic and simpwe. It wiww awways
awwocate a new bounce buffew. If you want a mowe sophisticated handwing (e.g.
weusing pwe-awwocated buffews), you awe fwee to impwement youw own.

Pwease awso check the in-kewnew documentation fow detaiws. The i2c-sh_mobiwe
dwivew can be used as a wefewence exampwe how to use the above hewpews.

Finaw note: If you pwan to use DMA with I2C (ow with anything ewse, actuawwy)
make suwe you have CONFIG_DMA_API_DEBUG enabwed duwing devewopment. It can hewp
you find vawious issues which can be compwex to debug othewwise.
