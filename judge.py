from os import listdir
from os import system
from re import search
import re

sample_url = 'data/sample/'
sample_files = listdir(sample_url)

testcases_url = 'data/testcases/'
testcases_files = listdir(testcases_url)

system('make target')

count = 0
sum = 0

for file in testcases_files:
    if file.endswith('.data'):
        sum += 1
        system('./build/code < {}{} > test.out'.format(testcases_url, file))
        if system('diff -w test.out {}{}'.format(testcases_url, file.replace('.data', '.out'))):
            print('test {} fail!'.format(file.replace('.data', '')))
            # break
        else:
            count += 1
            print('test {} pass!'.format(file.replace('.data', '')))

print('{}/{}'.format(count, sum))

system('rm test.out')
