import tensorflow as tf
from tensorflow.contrib.layers import fully_connected


class Qvalue:
    def __init__(self, state_dim=2, n_actions=3, batch_size=64, h1_n=512, h2_n=256):
        learning_rate = 0.01
        self.graph = tf.Graph()
        with tf.name_scope("DNN"):
            # TODO:Replace None with batch_size
            # TODO: solve diff between predict for 1 & predict for batch
            self.x = tf.placeholder(tf.float32, shape=(None, state_dim), name="X")
            self.y = tf.placeholder(tf.float32, shape=(batch_size, n_actions), name="Y")

            self.hidden1 = fully_connected(self.x, h1_n, scope="Hdden1")
            self.hidden2 = fully_connected(self.hidden1, h2_n, scope="hidden2")
            self.logits = fully_connected(self.hidden2, self.y, scope="logits")

        with tf.name_scope("loss"):
            xentropy = tf.nn.sparse_softmax_cross_entropy_with_logits(labels=self.y, logits=self.logits)
            self.loss = tf.reduce_mean(xentropy, name="Loss")

        with tf.name_scope("train"):
            optimizer = tf.train.AdagradDAOptimizer(learning_rate)
            training_op = optimizer.minimize(loss=self.loss)

        self.init = tf.global_variables_initializer()
        self.saver = tf.train.Saver()
        self.session.run(self.init)

        self.session = None

    def inti_tf_session(self):
        if self.session is None:
            self.session = tf.Session(graph=self.graph)

    def predict(self, states):
        self.inti_tf_session()
        feed_dict = {self.x: states}

        return self.session.run(self.logits, feed_dict=feed_dict)

    def train(self, states, targets):
        self.inti_tf_session()
        feed_dict = {self.x: states, self.logits: targets}
        return self.session.run(self.loss, feed_dict=feed_dict)
