import numpy as np
import tensorflow as tf

x = np.random.rand(4, 2).astype("float32")
y = np.random.rand(2, 3, 4).astype("float32")
insfile = "ins.npz"
np.savez(insfile, x=x, y=y)

tmp1 = tf.reduce_max(x, axis=[0])
tmp2_1 = tf.reduce_max(y, axis=[2])
tmp2_2 = tf.reduce_max(tmp2_1, axis=[1])
res = tf.add(tmp1, tmp2_2)
res_0 = res.numpy()

outsfile = "outs.npz"
np.savez(outsfile, res_0=res_0)
