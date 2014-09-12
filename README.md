Evolved Dynamical Neural Network
================================

This work is an extension of the work done by Randall Beer and Brain Yamauchi in the paper [Sequential Behavior and Learning in Evolved Dynamical Neural Networks](http://adb.sagepub.com/content/2/3/219.short) (sorry, it's hidden behind a paywall!). We implemented our networks in a very similar way with some small modifications, and attempted to scale the result up in order to solve a useful task. The first task we have designed is to solve a non-trivial maze in the least amount of steps.

The full mathematical details of the algorithm are in the file docs/README.pdf.

Usage (Linux/Mac)
-----

Open a terminal and navigate to where you'd like this program.  Enter

    git clone https://github.com/Garrett-R/evolved-dynamical-neural-network.git ednn
    cd ednn
    make

The binary will be called "ednn".  You can see how to execute it by typing "./ednn --help".  Since there are so many parameters required, we also supplied a helper script that sets the parameters and executes the program.  To use just run

    ./run_ednn.sh   
    


License
-------

GNU GPL version 2 or any later version
