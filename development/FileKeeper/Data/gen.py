#!/usr/bin/env python

import sys

def usage():
    print 'gen.py schemafile hppfile'

def main():
    sql = sys.argv[1]
    hpp = sys.argv[2]
        
    res = '#pragma once\n\nconst char s_gszSql[] =\n'
    
    sqlfile = open(sql)
    sqls = sqlfile.readlines()
    empyt = 0
    for sentence in sqls:
        sentence = sentence[:-1]
        if sentence == "":
            res = res + '\n'
            empty = empty + 1
            continue
        res = res + '\t\t"' + sentence + '"\n'
        empty = 0
    res = res[:-(empty+1)]
    res = res + ';\n'
    sqlfile.close()
    
    hppfile = open(hpp, 'w')
    hppfile.write(res)
    hppfile.close()
    
if __name__ == '__main__':
    if len(sys.argv) != 3:
        usage()
        exit(-1)
    main()


