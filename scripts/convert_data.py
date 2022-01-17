import sys
import struct


if len(sys.argv) != 4:
    print("Usage:", sys.argv[0], "mode(float, hexstr, int8, image, audio)", "value", "outfile")
    sys.exit(1)

mode = sys.argv[1]
val = sys.argv[2]

data = b""
if mode == "float":
    for f in val.split(","):
        data += struct.pack("f", float(f))
elif mode == "hexstr":
    data = val.encode("raw_unicode_escape").decode("unicode_escape").encode("raw_unicode_escape")
elif mode == "int8":
    for i in val.split(","):
        data += struct.pack("b", int(i))

with open(sys.argv[3], "wb") as f:
    f.write(data)
