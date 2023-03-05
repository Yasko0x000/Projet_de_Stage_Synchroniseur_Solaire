import spidev
import time

spi = spidev.SpiDev()
spi.open(0, 0)
spi.max_speed_hz = 1000000

def readadc(adcnum):
    if ((adcnum > 7) or (adcnum < 0)):
        return -1
    r = spi.xfer2([1, (8 + adcnum) << 4, 0])
    adcout = ((r[1] & 3) << 8) + r[2]
    return adcout

while True:
    value = readadc(0)
    voltage = value * 3.3 / 1024
    current = (voltage - 1.65) / 0.066
    print("Courant : {:.2f} A".format(current))
    time.sleep(1)