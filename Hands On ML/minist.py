import tensorflow as tf
import numpy as np
from tensorflow.contrib.layers import fully_connected

from datetime import datetime
now = datetime.utcnow().strftime("%Y%m%d%H%M%S")
root_logdir = "tf_logs"
logdir = "{}/run-{}/".format(root_logdir, now)


# construction_phase##
n_inputs = 28 * 28
n_hidden1 = 300
n_hidden2 = 100
n_outputs = 10

X = tf.placeholder(tf.float32, shape=(None, n_inputs), name="X")
y = tf.placeholder(tf.int64, shape=(None), name="y")


# create layers just like fully_connected
def neuron_layer(X, n_neurons, name, activation=None):
    with tf.name_scope(name):
        n_inputs = int(X.shape()[1])
        stddev = 2 / np.sqrt(n_inputs)
        intit = tf.truncated_normal((n_inputs, n_neurons), stddev=stddev)

        w = tf.Variable(intit, name="Wieghts")
        b = tf.Variable(tf.zeros([n_neurons]), name="biases")
        z = tf.matmul(X, w) + b
        if activation == "relu":
            return tf.nn.relu(z)
        else:
            return


with tf.name_scope("DNN"):
    layer1 = fully_connected(X, n_hidden1, scope="hidden1")
    layer2 = fully_connected(layer1, n_hidden2, scope="hidden2")
    logits = fully_connected(layer2, n_outputs, scope="output", activation_fn=None)

with tf.name_scope("Loss"):
    xentropy = tf.nn.sparse_softmax_cross_entropy_with_logits(logits=logits, labels=y)
    loss = tf.reduce_mean(xentropy, name="loss")
learning_rate = 0.1

with tf.name_scope("train"):
    optimizer = tf.train.GradientDescentOptimizer(learning_rate)
    training_op = optimizer.minimize(loss)
with tf.name_scope("eval"):
    correct = tf.nn.in_top_k(logits, y, 1)
    accuracy = tf.reduce_mean(tf.cast(correct, tf.float32))

init = tf.initialize_all_variables()
saver = tf.train.Saver()

loss_summary = tf.summary.scalar('LOSS', loss)
summary_writer = tf.summary.FileWriter(logdir, tf.get_default_graph())

##

from tensorflow.examples.tutorials.mnist import input_data

mnist = input_data.read_data_sets("/tmp/data/")

# execution_phase##

n_epochs = 400
n_batches = 100
batch_size = 128
with tf.Session() as sess:
    init.run()
    for epoch in range(n_epochs):
        for iteration in range(mnist.train.num_examples // batch_size):
            X_batch, y_batch = mnist.train.next_batch(batch_size)

            if iteration % 10 == 0:
                summary_str = loss_summary.eval(feed_dict={X: X_batch, y: y_batch})
                step = epoch * n_batches + iteration
                summary_writer.add_summary(summary_str, step)

            sess.run(training_op, feed_dict={X: X_batch, y: y_batch})
        acc_train = accuracy.eval(feed_dict={X: X_batch, y: y_batch})
        acc_test = accuracy.eval(feed_dict={X: mnist.test.images,
                                            y: mnist.test.labels})
        print(epoch, "Train accuracy:", acc_train, "Test accuracy:", acc_test)
    summary_writer.close()
    save_path = saver.save(sess, "minist_model_final.ckpt")

# reuse the model ##
# construction phase stays the same ---#
# with tf.Session() as sess:
#     saver.restore(sess, "my_model_final.ckpt")
#     X_new_scaled = [...]  # some new images (scaled from 0 to 1)
#     z = logits.eval(feed_dict={X: X_new_scaled})
#     y_pred = tf.argmax(z, axis=1)
