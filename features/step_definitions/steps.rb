require 'fileutils'
require 'rspec'

$DEFAULT_HEADER_FILE = "default_class_header.hpp"

After do
    File.delete $DEFAULT_HEADER_FILE if File.exists?($DEFAULT_HEADER_FILE)
    File.delete $OUTPUT_FILE_NAME if $OUTPUT_FILE_NAME && File.exists?($OUTPUT_FILE_NAME)
end

Given /^header file with:$/ do |content|
    File.open($DEFAULT_HEADER_FILE, "w") { |f| f.write content }
end

When /^I generate a mock for class "(.*?)"$/ do |class_name|
    $OUTPUT_FILE_NAME = class_name  + "Mock.hpp"
    gen_output = %x(./bin/gmockgen "#{$DEFAULT_HEADER_FILE}" "#{class_name}")
    $?.exitstatus.should eql(0), gen_output
end

Then /^output should begin with "(.*?)"$/ do |s|
    File.open($OUTPUT_FILE_NAME) { |f| f.read.should start_with(s.gsub(/\\n/, "\n")) }
end

Then /^output should end with "(.*?)"$/ do |s|
    File.open($OUTPUT_FILE_NAME) { |f| f.read.should end_with(s.gsub(/\\n/, "\n")) }
end

Then /^it should fail with error containing "(.*?)"$/ do |arg1|
  pending # express the regexp above with the code you wish you had
end

Then /^output should contain:$/ do |s|
    File.open($OUTPUT_FILE_NAME) { |f| f.read.should include(s) }
end

Then /^output should contain "(.*?)"$/ do |s|
    File.open($OUTPUT_FILE_NAME) { |f| f.read.should include(s) }
end

Then /^file "(.*?)" should exist$/ do |f|
    File.exists?(f).should be_true
end
