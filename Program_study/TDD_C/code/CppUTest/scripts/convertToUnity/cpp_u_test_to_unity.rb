#!/usr/bin/ruby
#---
# Excerpted from "Test Driven Development for Embedded C",
# published by The Pragmatic Bookshelf.
# Copyrights apply to this code. It may not be used to create training material, 
# courses, books, articles, and the like. Contact us if you are in doubt.
# We make no guarantees that this code is fit for any purpose. 
# Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
#---
require File.join(File.dirname(__FILE__),  'cpp_u_test_to_unity_utils.rb')
include CppUTestToUnityUtils

in_file = ARGV[0]
unity_filename = convert_test_filename_to_unity_filename(in_file)
unity_runner_filename = convert_test_filename_to_unity_testrunner_filename(in_file)
puts "Converting :" + in_file + "\n"
puts "        To :" + unity_filename + "\n"

test_lines = File.open(in_file).readlines
out_unity_file = File.open(unity_filename, 'w')
out_unity_runner_file = File.open(unity_runner_filename, 'w')

test_groups = get_test_groups(test_lines)
adjust_tabs(test_lines)
remove_extern_c(test_lines)
demote_group(/TEST_GROUP/, test_lines)
convert_macros(test_lines, test_groups)
group_runners = generate_group_runners(test_groups, test_lines)
write_lines_to_file(out_unity_file, test_lines)
write_lines_to_file(out_unity_runner_file, group_runners)
out_unity_file.close()
out_unity_runner_file.close()
