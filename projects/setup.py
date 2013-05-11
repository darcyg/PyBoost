#!/usr/bin/env python

import os
import sys
import getopt
import datetime
import time
import shlex
import shutil
from pprint import pprint


def create_dir(dirname):
    if os.path.exists(dirname):
        raise Exception("Directory %s already exists" %(str(project_name)))

    os.mkdir(dirname)
    return dirname

def sed(filename, rlist):
    tempfile = filename + ".tmp"
    f1 = open(filename, 'r')
    f2 = open(tempfile, 'w')
    for line in f1:
        for old, new in rlist:
            line = line.replace(old, new)
        f2.write(line)
    f1.close()
    f2.close()

    os.remove(filename)
    os.rename(tempfile, filename)

def process_files(project_name, files, names):
    for filename in files:
        rlist = [
                ("@@BINARY@@", names["binary"]),
                ("@@CPP@@", names["cpp"]),
                ("@@PYTHON@@", names["python"]),
                ("@@PROJECT@@", names["project"]),
                ]
        sed(filename, rlist)

def get_args():
    def usage():
        print "Command Line Interface for VFP Index and Query\n"
        print "SAMPLE USAGE: ./setup.py -p <project_name>"
        print "Ex: ./setup.py -p helloWorld\n"
        print "-p <project_name>"
        print ""

    try:
        opts, args = getopt.getopt(sys.argv[1:], "p:b:j:h", ["project=", "boostdir=", "bjamdir=", "help"])
    except:
        usage()
        exit()

    # init defaults
    project_name = None 
    boost_dir = "/Users/saratt/lm-vfp/intersect/thirdparty/boost_1_52_0"
    bjam_dir = None

    # parse cli args
    for o,a in opts:
        if o in ("-p", "--project"):
            project_name = a 
        if o in ("-b", "--boostdir"):
            boost_dir = a 
        if o in ("-j", "--bjamdir"):
            bjam_dir = a 
        elif o in ("-h", "--help"):
            usage()
            exit()

    # redeclare defaults if applicable
    if not bjam_dir:
        bjam_dir = os.path.join(boost_dir, "bjam")

    # check stuff
    if not project_name: raise Exception("Must Specify Project Name")
    assert os.path.exists(boost_dir), "Boost Directory '%s' doesn't exist" %(str(boost_dir))
    assert os.path.exists(bjam_dir), "Bjam Path '%s' doesn't exist" %(str(boost_dir))

    # return args in a dict
    results = {}
    results["project_name"] = project_name
    results["boost_dir"] = boost_dir
    results["bjam_dir"] = boost_dir
    return results

if __name__ == "__main__":
    
    args = get_args()
    project_name = args["project_name"]
    project_dir = create_dir(project_name)


    template_dir = ".template/"

    # copy jamroot
    orig_jamroot_file = os.path.join(template_dir, "Jamroot")
    jamroot_file = os.path.join(project_dir, "Jamroot")
    shutil.copy2(orig_jamroot_file, jamroot_file)

    # copy cpp
    old_file = os.path.join(template_dir, "template.cpp")
    cpp_file = os.path.join(project_dir, "%s.cpp" %(project_name))
    shutil.copy2(old_file, cpp_file)
    
    # copy python
    old_file = os.path.join(template_dir, "template.py")
    python_file = os.path.join(project_dir, "%s.py" %(project_name))
    shutil.copy2(old_file, python_file)

    # copy Makefile
    old_file = os.path.join(template_dir, "Makefile")
    makefile = os.path.join(project_dir, "Makefile")
    shutil.copy2(old_file, makefile)

    names = {}
    names["binary"] = project_name
    names["cpp"] = project_name
    names["python"] = project_name 
    names["project"] = project_name + "_project"

    files = [
            jamroot_file,
            cpp_file,
            python_file,
            makefile,
            ]
    process_files(project_name, files, names=names)

    



