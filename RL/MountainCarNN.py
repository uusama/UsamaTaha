import gym
import numpy as np
import random,sys
import tensorflow as tf
import matplotlib.pyplot as plt

env = gym.make('MountainCar-v0')
tf.reset_default_graph()

# These lines establish the feed-forward part of the network used to choose actions
inputs1 = tf.placeholder(shape=[1, 2], dtype=tf.float32)
W = tf.Variable(tf.random_uniform([2, 3], 0, 0.01))
Qout = tf.matmul(inputs1, W)
predict = tf.argmax(Qout, 1)

# Below we obtain the loss by taking the sum of squares difference between the target and prediction Q values.
nextQ = tf.placeholder(shape=[1, 3], dtype=tf.float32)
loss = tf.reduce_sum(tf.square(nextQ - Qout))
trainer = tf.train.GradientDescentOptimizer(learning_rate=0.1)
updateModel = trainer.minimize(loss)

init = tf.global_variables_initializer()

# Set learning parameters
y = .99
e = 0.1
lr = .8
num_episodes = 2000
# create lists to contain total rewards and steps per episode
jList = []
rList = []
with tf.Session() as sess:
    sess.run(init)
    for i in range(num_episodes):
        # Reset environment and get first new observation
        if (i + 1) % 100 == 0:
            print("\rEpisode {}/{}.".format(i + 1, num_episodes), end="")
            sys.stdout.flush()
        s = env.reset()
        rAll = 0
        d = False
        j = 0
        # The Q-Network
        while j < 200:
            j += 1
            env.render()
            # Choose an action by greedily (with e chance of random action) from the Q-network
            s = np.reshape(s, (-1, 2))
            a, allQ = sess.run([predict, Qout], feed_dict={inputs1: s})
            if np.random.rand(1) < e:
                a[0] = env.action_space.sample()
            # Get new state and reward from environment
            s1, r, d, _ = env.step(a[0])
            s1 = np.reshape(s1, (-1, 2))

            # Obtain the Q' values by feeding the new state through our network
            Q1 = sess.run(Qout, feed_dict={inputs1: s1})
            # Obtain maxQ' and set our target value for chosen action.
            maxQ1 = np.max(Q1)
            targetQ = allQ
            targetQ[0, a[0]] = r + y * maxQ1
            # targetQ[0, a[0]] += lr * (r + y * maxQ1 - targetQ[0, a[0]])
            # Train our network using target and predicted Q values
            sess.run([updateModel, W], feed_dict={inputs1: s, nextQ: targetQ})
            rAll += r
            s = s1
            if d == True:
                # Reduce chance of random action as we train the model.
                e = 1. / ((i / 50) + 10)

                break
        jList.append(j)
        rList.append(rAll)

print("Percent of succesful episodes: " + str(sum(rList) / num_episodes) + "%")

plt.plot(rList)
plt.show()

plt.plot(jList)
plt.show()
