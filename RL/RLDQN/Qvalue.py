import tensorflow as tf
from tensorflow.contrib.layers import fully_connected


class Qvalue:
    def __init__(self, state_dim=2, n_actions=3, batch_size=64, h1_n=512, h2_n=256):
        learning_rate = 0.01
        self.graph = tf.Graph()
        with tf.name_scope("DNN"):
            self.x = tf.placeholder(tf.float32, shape=(batch_size, state_dim), name="X")
            self.y = tf.placeholder(tf.float32, shape=(batch_size, n_actions), name="Y")

            self.hidden1 = fully_connected(self.x, h1_n, name="Hdden1")
            self.hidden2 = fully_connected(self.hidden1, h2_n, name="hidden2")
            self.logits = fully_connected(self.hidden2, self.y, name="logits")

        with tf.name_scope("loss"):
            xentropy = tf.nn.sparse_softmax_cross_entropy_with_logits(labels=self.y, logits=self.logits)
            loss = tf.reduce_mean(xentropy, name="Loss")

        with tf.name_scope("train"):
            optimizer = tf.train.AdagradDAOptimizer(learning_rate)
            training_op = optimizer.minimize(loss=loss)

        self.init = tf.global_variables_initializer()
        self.saver = tf.train.Saver()
