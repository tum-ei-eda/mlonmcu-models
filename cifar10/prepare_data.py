import struct
import pickle


with open("data_batch_1", "rb") as f:
    batch = pickle.load(f, encoding="latin1")

features = batch['data'].reshape((len(batch['data']), 3, 32, 32)).transpose(0, 2, 3, 1)
labels = batch['labels']

for n in range(0, 5):
    data = b""
    for i in range(0, 32*32*3):
        v = features[n].flatten()[i]
        v = float(v) / 255
        data += struct.pack("f", v)

    with open("input/" + str(n) + ".bin", "wb") as f:
        f.write(data)

    print("Label", labels[n])
