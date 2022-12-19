import smbus
import time
import mmap

address = 0x48
A0 = 0x40
bus = smbus.SMBus(1)

with open("shared_memory", "r+b") as f:
    # memory-map the file, size 0 means whole file
    shmem = mmap.mmap(f.fileno(), 0)

while True:
    bus.write_byte(address,A0)
    shmem[0] = bus.read_byte(address)
    #print(shmem[0])
    time.sleep(0.1)