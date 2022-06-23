from os import listdir
from os import system
from re import search
import re

sample_url = 'data/sample/'
sample_files = listdir(sample_url)

testcases_url = 'data/testcases/'
testcases_files = listdir(testcases_url)

system('make target')

for file in testcases_files:
    if file.endswith('.data'):
        system('./build/code < {}{} > test.out'.format(testcases_url, file))
        if system('diff -w test.out {}{}'.format(testcases_url, file.replace('.data', '.out'))):
            print('test {} fail!'.format(file.replace('.data', '')))
            break
        else:
            print('test {} pass!'.format(file.replace('.data', '')))

system('rm test.out')
