import tensorflow as tf

class Qvalue:
    def __init__(self, state_dim=2, n_actions=3, batch_size=64):
        self.graph = tf.Graph()
