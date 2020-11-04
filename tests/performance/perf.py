#!/usr/bin/env python3
#
#
# How to use: cd to student directory, then run
# unbuffer ~/algoL2/inf301·git/Code-APPs/APP2-Curiosity/tests/performance/perf.py c | tee perf.log
#
#

import sys
import os
import subprocess
import json

import matplotlib.pyplot as plt

DEBUG=False

def debug(*args):
    if (DEBUG):
        print("".join(args))

if __name__ == "__main__":
    if len (sys.argv) == 1:
        print ("Usage: ", sys.argv[0], " c [t] (to test C implementation)")
        print ("    or ", sys.argv[0], " py [t] (to test Python implementation)")
        print ("    or ", sys.argv[0], " gen [t] (to generate standalone test files)")
        print ()
        print ("where [t] can be left empty or is one of base,long,nested,memfree,piiile")

        exit (1)

    gen = False

    if sys.argv[1] == "c":
        prog = "./main -silent "
    elif sys.argv[1] == "py":
        prog = "./main.py -ascii -silent "
    elif sys.argv[1] == "gen":
        gen = True
    else:
        print ("Error: bad argument", sys.argv[1])


to_test = None

if len (sys.argv) > 2:
    to_test = sys.argv[2]

perfdir=os.path.dirname(sys.argv[0])

# genprog = "./" + perfdir + "/gen-test.py"
genprog = os.path.join(perfdir, "gen-test.py")
drawprog = perfdir + "/make_plot.R"

os.system("[ -e fifo ] && rm fifo")

time = subprocess.check_output("which -a time | grep -v shell | tail -n 1", shell=True)
time = time.decode().rstrip()
# timecmd = " time -f '\tTemps: %es  Mémoire max: %MKb' "
timecmd = time + " -f '%e;%M' "
timeout = 60
# timeout = 1
timeoutcmd = "timeout " + str(timeout) + "s "

def drawgraph(x, temps, memoire=None, mode=None):
    plt.clf()
    fig, ax1 = plt.subplots()

    color = 'tab:red'
    ax1.set_xlabel('size')
    ax1.set_ylabel('time (s)', color=color)
    ax1.plot(x, temps, color=color)
    ax1.tick_params(axis='y', labelcolor=color)

    if memoire is not None:
        ax2 = ax1.twinx()  # instantiate a second axes that shares the same x-axis

        color = 'tab:green'
        ax2.set_ylabel('memoire (GB)', color=color)  # we already handled the x-label with ax1
        ax2.plot(x, memoire, color=color)
        ax2.tick_params(axis='y', labelcolor=color)

    fig.tight_layout()
    plt.savefig(mode + ".png")

def run_test(mode, message):
    msg =  "Running tests mode " + mode + " " + message
    print ("*" * len(msg))
    print (msg)

    size_curves = []
    temps_curves = []
    memoire_curves = []
    size = 1000

    ret = None
    while ret == None and size < 10000000:
        print ("Size ", "{:10}".format(size))

        if gen :
            f = "> perfs/test" + mode + str(size) + ".test"
        else:
            f = " > fifo &"

        os.system("mkfifo fifo")
        generation = "python3 " + genprog + " -s " + str(size) + " -m " + mode + f
        result = os.system(generation)
        debug("Executed: " + generation + " with result " + str(result))

        if not gen:

            ## old version with stderr problem
            # redirect stderr to stdout
            # ret = os.system(timecmd + timeoutcmd + " " + prog + " fifo 2>&1")

            command = timecmd + timeoutcmd + prog + "fifo"
            # # redirect stderr to stdout
            try:
                debug("Executing: ", command)
                # result = subprocess.check_output(command, shell=True, stderr=subprocess.STDOUT).decode()
                result = subprocess.check_output(command, shell=True, stderr=subprocess.STDOUT)
                result = result.decode().rstrip()
                parts = result.split(';', 2)
                temps = parts[0]
                memoire = str(int(parts[1]) / (1024*1024))
                print ("\tTemps: {}s  Mémoire max: {:.2f} GB".format(temps, float(memoire)))

                size_curves.append(size)
                temps_curves.append(temps)
                memoire_curves.append(memoire)
            except subprocess.CalledProcessError as e:
                print ("Error, return code", e.returncode)
                if e.returncode == 139:
                    ret = "Segmentation Fault"
                elif e.returncode == 134:
                    ret = "Assertion Failed"
                elif e.returncode == 127:
                    ret = "Command not found"
                else:
                    ret = "Timeout after "+ str(timeout) +"seconds"

        size*=2
        os.remove("fifo")

    if ret != None:
        print ("Problem with last size:", ret)
    drawgraph(size_curves, temps_curves, memoire_curves, mode)

all_tests = {
    "base": "(très long sans blocs)",
    "long": "(très long, beaucoup de blocs)",
    "nested": "(très long, beaucoup de blocs imbriqués)",
    "memfree": "(boucle exécutée de nombreuses fois)",
    "piiile": "(très grande pile)",
    }


if __name__ == "__main__":
    if to_test:
        if not to_test in all_tests:
            print ("Type de test inconnu:", to_test)
            print ("Allowed tests:")
            print (json.dumps(all_tests,indent=4))
            exit (1)
        run_test (to_test, all_tests[to_test])
    else:
        for t in all_tests:
            run_test (t, all_tests[t])

    # run_test ("base", "(très long sans blocs)")
    # run_test ("long", "(très long, beaucoup de blocs)")
    # run_test ("nested", "(très long, beaucoup de blocs imbriqués)")
    # run_test ("memfree", "(boucle exécutée de nombreuses fois)")
    # run_test ("piiile", "(très grande pile)")

