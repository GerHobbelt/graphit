#!/usr/local/bin/python

import unittest
import subprocess
import os
import shutil

class TestGraphitCompiler(unittest.TestCase):
    first_time_setup = True

    #NOTE: currently the tests can only work within the build/bin directory
    @classmethod
    def setUpClass(cls):
        build_dir = "../../build"
        if not os.path.isdir(build_dir):
            print "build the binaries"
            #shutil.rmtree("../../build_dir")
            os.mkdir(build_dir)
            os.chdir(build_dir)
            subprocess.call(["cmake", ".."])
            subprocess.call(["make"])
            os.chdir('./bin')
        else:
            # working directory is in the bin folder
            os.chdir(build_dir)
            os.chdir('./bin')

        cwd = os.getcwd()

        cls.root_test_input_dir = "../test/input/"
        cls.cpp_compiler = "g++"
        cls.compile_flags = "-std=c++11"
        cls.include_path = "../src/runtime_lib"
        cls.output_file_name = "test.cpp"
        cls.executable_file_name = "test.o"


    def setUp(self):
        self.clean_up()

        #def tearDown(self):
        #self.clean_up()

    def clean_up(self):
        #clean up previously generated files
        if os.path.isfile(self.output_file_name):
            os.remove(self.output_file_name)
        if os.path.isfile(self.executable_file_name):
            os.remove(self.executable_file_name)

    def basic_compile_test(self, input_file_name):
        input_with_schedule_path = '../../test/input_with_schedules/'
        print os.getcwd()
        compile_cmd = "python graphitc.py -f " + input_with_schedule_path + input_file_name + " -o test.cpp"
        print compile_cmd
        subprocess.check_call(compile_cmd, shell=True)

        # actual test cases

    def test_simple_splitting(self):
        self.basic_compile_test("simple_loop_index_split.gt")

    def test_pagerank_AoS(self):
        self.basic_compile_test("simple_pagerank_with_AoS.gt")

if __name__ == '__main__':
    # unittest.main()
    # used for enabling a specific test


    suite = unittest.TestSuite()
    suite.addTest(TestGraphitCompiler('test_pagerank_AoS'))
    unittest.TextTestRunner(verbosity=2).run(suite)
